// dlist.cpp:    Display lists, for Gnash.
// 
//     Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010 Free Software
//     Foundation, Inc
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA    02110-1301    USA
//

#include "smart_ptr.h" // GNASH_USE_GC
#include "DisplayList.h"
#include "log.h"
#include "Renderer.h"
#include "StringPredicates.h"
#include "MovieClip.h"

#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cassert>
#include <boost/bind.hpp>

namespace gnash {

// Forward declarations
namespace {
	/// Return an iterator to the first element of the container NOT
    /// in the "removed" depth zone
    DisplayList::iterator beginNonRemoved(DisplayList::container_type& c);

	/// Return an constant iterator to the first element of the
    /// container NOT in the "removed" depth zone
    DisplayList::const_iterator beginNonRemoved(
            const DisplayList::container_type& c);

	/// Return an iterator succeeding the last element in zone
    /// (-16384, 0xffff-16384)
    DisplayList::iterator dlistTagsEffectiveZoneEnd(
            DisplayList::container_type& c);
	
	/// Return an constant iterator succeeding the last element
    /// in (-16384, 0xffff-16384)
    DisplayList::const_iterator dlistTagsEffectiveZoneEnd(
            const DisplayList::container_type& c);
}

/// Anonymous namespace for generic algorithm functors.
namespace {

class DepthEquals
{
public:

    DepthEquals(int depth) : _depth(depth) {}

    bool operator() (const DisplayObject* item) {
        if (!item) return false;
        return item->get_depth() == _depth;
    }

private:
    int _depth;
};

struct DepthGreaterThan
{
    bool operator()(const DisplayObject* a, const DisplayObject* b) {
        return a->get_depth() > b->get_depth();
    }
};

struct DepthLessThan
{
    bool operator()(const DisplayObject* a, const DisplayObject* b) {
        return a->get_depth() < b->get_depth();
    }
};

class DepthGreaterOrEqual
{
public:

    DepthGreaterOrEqual(int depth) : _depth(depth) {}

    bool operator() (const DisplayObject* item) {
        if (!item) return false;
        return item->get_depth() >= _depth;
    }
private:
    int _depth;
};


class NameEquals
{
public:
    NameEquals(string_table& st, string_table::key name, bool caseless)
        :
        _st(st),
        _caseless(caseless),
        _name(caseless ? _st.noCase(name) : name)
    {}

    bool operator() (const DisplayObject* item) {
        assert (item);

        // TODO: this is necessary because destroy() is called in
        // movie_root, leaving destroyed items on the DisplayList. They
        // shouldn't be found. A better fix would be to stop destroying
        // objects there and add to the invariant that there are never
        // destroyed DisplayObjects in the DisplayList.
        if (item->isDestroyed()) return false;
        
        const string_table::key itname =
            _caseless ? _st.noCase(item->get_name()) : item->get_name();

        return itname == _name;

    }

private:
    string_table& _st;
    const bool _caseless;
    const string_table::key _name;
};

} // anonymous namespace

int
DisplayList::getNextHighestDepth() const
{
    testInvariant();

    int nexthighestdepth=0;
    for (const_iterator it = _charsByDepth.begin(),
            itEnd = _charsByDepth.end(); it != itEnd; ++it) {

        DisplayObject* ch = *it;

        int chdepth = ch->get_depth();
        if (chdepth >= nexthighestdepth) {
            nexthighestdepth = chdepth+1;
        }
    }
    return nexthighestdepth;
}

DisplayObject*
DisplayList::getDisplayObjectAtDepth(int depth) const
{
    testInvariant();

    for (const_iterator it = _charsByDepth.begin(), itEnd = _charsByDepth.end();
        it != itEnd; ++it) {

        DisplayObject* ch = *it;

        // Should not be there!
        if (ch->isDestroyed()) continue;

        // found
        if (ch->get_depth() == depth) return ch;

        // non-existent (chars are ordered by depth)
        if (ch->get_depth() > depth) return 0;
    }

    return 0;

}


DisplayObject*
DisplayList::getDisplayObjectByName(string_table& st, string_table::key name,
        bool caseless) const
{
    testInvariant();

    const container_type::const_iterator e = _charsByDepth.end();

    container_type::const_iterator it =
        std::find_if(_charsByDepth.begin(), e, NameEquals(st, name, caseless));

    if (it == e) return 0;
    
    return *it;

}

void
DisplayList::placeDisplayObject(DisplayObject* ch, int depth)
{
    assert(!ch->unloaded());
    ch->set_invalidated();
    ch->set_depth(depth);

    container_type::iterator it =
        std::find_if( _charsByDepth.begin(), _charsByDepth.end(),
                DepthGreaterOrEqual(depth));

    if (it == _charsByDepth.end() || (*it)->get_depth() != depth) {
        // add the new char
        _charsByDepth.insert(it, ch);
    }
    else {
        // remember bounds of old char
        InvalidatedRanges old_ranges; 
        (*it)->add_invalidated_bounds(old_ranges, true);    

        // make a copy (before replacing)
        DisplayObject* oldCh = *it;

        // replace existing char (before calling unload!)
        *it = ch;
    
        if (oldCh->unload()) {
            // reinsert removed DisplayObject if needed
            reinsertRemovedCharacter(oldCh);
        }
        else oldCh->destroy();
        
        // extend invalidated bounds
        ch->extend_invalidated_bounds(old_ranges);                
    }

    testInvariant();
}

void
DisplayList::add(DisplayObject* ch, bool replace)
{
    int depth = ch->get_depth();

    container_type::iterator it =
        std::find_if(_charsByDepth.begin(), _charsByDepth.end(),
                DepthGreaterOrEqual(depth));

    if (it == _charsByDepth.end() || (*it)->get_depth() != depth) {
        _charsByDepth.insert(it, ch);
    }
    else if (replace) *it = ch;

    testInvariant();
}

void
DisplayList::replaceDisplayObject(DisplayObject* ch, int depth,
        bool use_old_cxform, bool use_old_matrix)
{
    testInvariant();

    //GNASH_REPORT_FUNCTION;
    assert(!ch->unloaded());

    ch->set_invalidated();
    ch->set_depth(depth);

    container_type::iterator it =
        std::find_if(_charsByDepth.begin(), _charsByDepth.end(),
            DepthGreaterOrEqual(depth));

    if (it == _charsByDepth.end() || (*it)->get_depth() != depth) {
        _charsByDepth.insert(it, ch);
    }
    else {
        // Make a copy (before replacing)
        DisplayObject* oldch = *it;

        InvalidatedRanges old_ranges;
    
        if (use_old_cxform) {
            // Use the cxform from the old DisplayObject.
            ch->set_cxform(oldch->get_cxform());
        }

        if (use_old_matrix) {
            // Use the SWFMatrix from the old DisplayObject.
            ch->setMatrix(oldch->getMatrix(), true); 
        }
        
        // remember bounds of old char
        oldch->add_invalidated_bounds(old_ranges, true);        

        // replace existing char (before calling unload)
        *it = ch;

        // Unload old char
        if (oldch->unload()) {
            // reinsert removed DisplayObject if needed
            reinsertRemovedCharacter(oldch);
        }
        else oldch->destroy();
        
        // extend invalidated bounds
        // WARNING: when a new Button DisplayObject is added,
        //          the invalidated bounds computation will likely
        //          be bogus, as the actual DisplayObject shown is not
        //          instantiated until stagePlacementCallback for buttons
        //          (I'd say this is a bug in Button). 
        ch->extend_invalidated_bounds(old_ranges);                

    }

    testInvariant();
}
    
    
// Updates the transform properties of the DisplayObject at
// the specified depth.
void
DisplayList::moveDisplayObject( int depth, const cxform* color_xform,
        const SWFMatrix* mat, int* ratio, int* /* clip_depth */)
{
    testInvariant();

    DisplayObject* ch = getDisplayObjectAtDepth(depth);
    if (! ch) {
        // FIXME, should this be log_aserror?
        IF_VERBOSE_MALFORMED_SWF(
        log_swferror(_("moveDisplayObject() -- can't find object at depth %d"),
            depth);
        );
        return;
    }

    if (ch->unloaded()) {
        log_error("Request to move an unloaded DisplayObject");
        assert(!ch->unloaded());
    }

    // TODO: is sign of depth related to accepting anim moves ?
    if (!ch->get_accept_anim_moves()) {
        // This DisplayObject is rejecting anim moves.    This happens after it
        // has been manipulated by ActionScript.
        return;
    }

    if (color_xform) ch->set_cxform(*color_xform);
    if (mat) ch->setMatrix(*mat, true);
    if (ratio) ch->set_ratio(*ratio);

    testInvariant();
}
    
    
// Removes the object at the specified depth.
void
DisplayList::removeDisplayObject(int depth)
{
    //GNASH_REPORT_FUNCTION;

    testInvariant();

#ifndef NDEBUG
    container_type::size_type size = _charsByDepth.size();
#endif

    // TODO: would it be legal to call removeDisplayObject with a depth
    //             in the "removed" zone ?
    // TODO: optimize to take by-depth order into account
    container_type::iterator it = 
        std::find_if( _charsByDepth.begin(), _charsByDepth.end(),
            DepthEquals(depth));

    if (it != _charsByDepth.end()) {
        // Make a copy (before erasing)
        DisplayObject* oldCh = *it;

        // Erase (before calling unload)
        _charsByDepth.erase(it);

        if (oldCh->unload()) {
            // reinsert removed DisplayObject if needed
            // NOTE: could be optimized if we knew exactly how
            //             to handle the case in which the target depth
            //             (after the shift) is occupied already
            //
            reinsertRemovedCharacter(oldCh);
        }
        else oldCh->destroy();
    }

    assert(size >= _charsByDepth.size());

    testInvariant();

}

// TODO: take DisplayObject by ref ?
void
DisplayList::swapDepths(DisplayObject* ch1, int newdepth)
{
    testInvariant();

    if (newdepth < DisplayObject::staticDepthOffset) {
        IF_VERBOSE_ASCODING_ERRORS(
        log_aserror("%s.swapDepth(%d) : ignored call with target depth "
            "less then %d", ch1->getTarget(), newdepth,
            DisplayObject::staticDepthOffset);
        );
        return;
    }

    const int srcdepth = ch1->get_depth();

    // what if source char is at a lower depth ?
    assert(srcdepth >= DisplayObject::staticDepthOffset);

    assert(srcdepth != newdepth);

    // TODO: optimize this scan by taking ch1 depth into account ?
    container_type::iterator it1 =
        std::find(_charsByDepth.begin(), _charsByDepth.end(), ch1);

    // upper bound ...
    container_type::iterator it2 =
        std::find_if(_charsByDepth.begin(), _charsByDepth.end(),
            DepthGreaterOrEqual(newdepth));

    if (it1 == _charsByDepth.end()) {
        log_error("First argument to DisplayList::swapDepth() "
                "is NOT a DisplayObject in the list. Call ignored.");
        return;
    }

    // Found another DisplayObject at the given depth
    if (it2 != _charsByDepth.end() && (*it2)->get_depth() == newdepth)
    {
        DisplayObject* ch2 = *it2;

        ch2->set_depth(srcdepth);

        // TODO: we're not actually invalidated ourselves, rather 
        // our parent is...
        ch2->set_invalidated();

        // We won't accept static transforms after a depth swap.
        // See displaylist_depths_test6.swf for more info.
        ch2->transformedByScript();

        std::iter_swap(it1, it2);
    }

    // No DisplayObject found at the given depth
    else {
        // Move the DisplayObject to the new position
        // NOTE: insert *before* erasing, in case the list is
        //             the only referer of the ref-counted DisplayObject
        _charsByDepth.insert(it2, ch1);
        _charsByDepth.erase(it1);
    }

    // don't change depth before the iter_swap case above, as
    // we'll need it to assign to the new DisplayObject
    ch1->set_depth(newdepth);

    // TODO: we're not actually invalidated ourselves, rather our parent is...
    //             UdoG ? Want to verify this ?
    ch1->set_invalidated();

    // We won't accept static transforms after a depth swap.
    // See displaylist_depths_test6.swf for more info.
    ch1->transformedByScript();

    testInvariant();

}

DisplayObject*
DisplayList::removeDisplayObjectAt(int index)
{
    container_type::iterator it =
        std::find_if(_charsByDepth.begin(), _charsByDepth.end(),
                DepthEquals(index));

    if (it == _charsByDepth.end()) return 0;
   
    DisplayObject* obj = *it;
    _charsByDepth.erase(it);
    return obj;
}

void
DisplayList::removeDisplayObject(DisplayObject* obj)
{
    container_type::iterator it = std::find(_charsByDepth.begin(),
            _charsByDepth.end(), obj);
    
    if (it != _charsByDepth.end()) {
        _charsByDepth.erase(it);
    }
}

void
DisplayList::insertDisplayObject(DisplayObject* obj, int index)
{
    testInvariant();

    assert(!obj->unloaded());

    obj->set_invalidated();
    obj->set_depth(index);

    // Find the first index greater than or equal to the required index
    container_type::iterator it =
        std::find_if(_charsByDepth.begin(), _charsByDepth.end(),
            DepthGreaterOrEqual(index));
        
    // Insert the DisplayObject before that position
    _charsByDepth.insert(it, obj);

    // Shift depths upwards until no depths are duplicated. No DisplayObjects
    // are removed!
    while (it != _charsByDepth.end() && (*it)->get_depth() == index) {
        (*it)->set_depth(index + 1);
        ++index, ++it;
    }

    testInvariant();

}

void
DisplayList::addDisplayObject(DisplayObject* obj)
{
    testInvariant();

    assert(!obj->unloaded());

    obj->set_invalidated();

    int index;

    if (_charsByDepth.empty()) {
        index = 0;
    }
    else {
        container_type::const_reverse_iterator it = _charsByDepth.rbegin();
        index = (*it)->get_depth() + 1;
    }

    obj->set_depth(index);

    // Insert the DisplayObject at the end
    _charsByDepth.insert(_charsByDepth.end(), obj);

    testInvariant();

}


bool
DisplayList::unload()
{
    testInvariant();

    bool unloadHandler = false;

    // All children with an unload handler should be unloaded. As soon as
    // the first unload handler is encountered, subsequent children should
    // not be destroyed or removed from the display list. This affects
    // children without an unload handler.
    for (iterator it = beginNonRemoved(_charsByDepth),
            itEnd = _charsByDepth.end(); it != itEnd; )
    {
        // make a copy
        DisplayObject* di = *it;

        // Destroyed objects should not be there!
        assert(!di->isDestroyed());

        // Destroy those with a handler anyway?
        if (di->unload()) {
            unloadHandler = true;
            ++it;
            continue;
        }

        if (!unloadHandler) {
            di->destroy();
            it = _charsByDepth.erase(it);
        }
        else ++it;

    }

    testInvariant();

    return unloadHandler;

}


void
DisplayList::destroy()
{
    //GNASH_REPORT_FUNCTION;

    testInvariant();

    for (iterator it = _charsByDepth.begin(), itEnd = _charsByDepth.end();
            it != itEnd; ) {

        // make a copy
        DisplayObject* di = *it;

        // skip if already unloaded
        if ( di->isDestroyed() ) {
            ++it;
            continue;
        }

        di->destroy();
        it = _charsByDepth.erase(it); 
    }
    testInvariant();
}

// Display the referenced DisplayObjects. Lower depths
// are obscured by higher depths.
void
DisplayList::display(Renderer& renderer)
{
    testInvariant();

    std::stack<int> clipDepthStack;
    
    // We only display DisplayObjects which are out of the "removed" zone
    // (or should we check unloaded?)
    iterator it = beginNonRemoved(_charsByDepth);
    for (iterator endIt = _charsByDepth.end(); it != endIt; ++it)
    {
        DisplayObject* ch = *it;
        assert(!ch->isDestroyed());

        DisplayObject* mask = ch->getMask();
        if (mask && ch->visible() && ! mask->unloaded())
        {
            renderer.begin_submit_mask();
            
            if (mask->boundsInClippingArea(renderer)) mask->display(renderer);
            else mask->omit_display();
              
            renderer.end_submit_mask();
            
            if (ch->boundsInClippingArea(renderer)) ch->display(renderer);
            else ch->omit_display();
              
            renderer.disable_mask();
            
            continue;
        }

        // Don't display dynamic masks
        if (ch->isDynamicMask()) continue;

        assert(!ch->unloaded()); // we don't advance unloaded chars

        // Check if this charater or any of its parents is a mask.
        // Characters acting as masks should always be rendered to the
        // mask buffer despite their visibility.
        //
        DisplayObject* parent = ch->get_parent();
        bool renderAsMask = ch->isMaskLayer();

        while (!renderAsMask && parent) {
            renderAsMask = parent->isMaskLayer();
            parent = parent->get_parent();
        }
        
        // check for non-mask hiden DisplayObjects
        if (!renderAsMask && (!ch->visible())) {
            ch->omit_display();
            // Don't display non-mask hidden DisplayObjects
            continue;
        }
    
        int depth = ch->get_depth();
        // Discard useless masks
        while (!clipDepthStack.empty() && (depth > clipDepthStack.top())) {
            clipDepthStack.pop();
            renderer.disable_mask();
        }

        // Push a new mask to the masks stack
    	if (ch->isMaskLayer()) {
            int clipDepth = ch->get_clip_depth();
            clipDepthStack.push(clipDepth);
            renderer.begin_submit_mask();
        }
        
        if (ch->boundsInClippingArea(renderer)) ch->display(renderer);
        else ch->omit_display();
        
        // Notify the renderer that mask drawing has finished.
        if (ch->isMaskLayer()) renderer.end_submit_mask();
    } 

    // Discard any remaining masks
    while (!clipDepthStack.empty()) {
        clipDepthStack.pop();
        renderer.disable_mask();
    }
    
    
}

void
DisplayList::omit_display()
{
    iterator it = beginNonRemoved(_charsByDepth);
    for (iterator endIt = _charsByDepth.end(); it != endIt; ++it) {
        DisplayObject* ch = *it;
        ch->omit_display();
    }
}

void
DisplayList::dump() const
{
    //testInvariant();

    int num=0;
    for (const_iterator it = _charsByDepth.begin(),
            endIt = _charsByDepth.end(); it != endIt; ++it) {

        const DisplayObject* dobj = *it;
        log_debug(_("Item %d(%s) at depth %d (char name %s, type %s)"
                    "Destroyed: %s, unloaded: %s"),
            num, dobj, dobj->get_depth(), dobj->get_name(), typeName(*dobj),
            dobj->isDestroyed(), dobj->unloaded());
        num++;
    }
}


void 
DisplayList::add_invalidated_bounds(InvalidatedRanges& ranges, bool force)
{
    testInvariant();
    
    // This function generally has nothing else to do than calling the 
    // add_invalidated_bounds() function of all items in the display list.
    // However, special optimization is included for masks, which makes it 
    // look a bit more complicated. We want to avoid that a masked DisplayObject
    // invalidates an area where the DisplayObject is invisible because of it's
    // mask (which is quite common). For example, think of a large bitmap that
    // covers the entire stage and is masked by a very small circle in the
    // middle of the stage (ie. it's only visible there). Changes in the 
    // bitmap sprite would invalidate the whole stage even if only the small 
    // masked portion in the middle really needs to be drawn again.
    // 
    // So, like display(), we keep a stack of masks. Instead of drawing the
    // mask we keep a separate list of InvalidatedRanges for the masks which
    // later are intersected with the masked DisplayObjects' InvalidatedRanges.
    // 
    // The code is much based on the display() function, so some references
    // in comments have been added for convenience.
    // 
    // For a simpler implementation (that doesn't care about masks, but 
    // still produces correct results) see CVS revision 1.96        

    // TODO: review this function to take "dynamic" mask and maskees
    // into account
    
    std::stack<int> clipDepthStack; // same method used in display()
    std::stack<InvalidatedRanges> rangesStack;
    bool drawing_mask = false;

    iterator it = beginNonRemoved(_charsByDepth);
    for (iterator endIt = _charsByDepth.end(); it != endIt; ++it) {
        DisplayObject* dobj = *it;
        
#ifndef GNASH_USE_GC
        assert(dobj->get_ref_count() > 0);
#endif // ndef GNASH_USE_GC


        const int depth = dobj->get_depth();        

        // Discard useless masks
        while (!clipDepthStack.empty() && (depth > clipDepthStack.top())) {
            clipDepthStack.pop();
            rangesStack.pop();    // disable_mask() equivalent
            
        }
        
        // Push a new mask to the masks stack
        if (dobj->isMaskLayer()) {

            const int clipDepth = dobj->get_clip_depth();
            clipDepthStack.push(clipDepth);
            
            drawing_mask = true; // begin_submit_mask equivalent
            
            if (rangesStack.empty()) {
                InvalidatedRanges item;
                rangesStack.push(item);
            }
            else {
                // copy the top mask
                rangesStack.push(rangesStack.top()); 
            }
        }
        
        if (drawing_mask) {
        
            // --> The child is part of a mask, so add ranges to our 
            // mask ranges stack
            
            assert(!rangesStack.empty());
            dobj->add_invalidated_bounds(rangesStack.top(), true);                    
            
            // need to call add_invalidated_bounds again because the previous
            // call needs force==true. Changes to the mask itself may also
            // require re-rendering of the mask area, so we have to
            // add the mask itself to the global ranges, but this time
            // with normal "force" value...
            // As long the mask has not been invalidated and force==false this
            // call won't modify the "ranges" list.
            dobj->add_invalidated_bounds(ranges, force);
            
        }
        else {
            
            if (rangesStack.empty()) {
            
                // --> normal case for unmasked DisplayObjects
                dobj->add_invalidated_bounds(ranges, force);
                
            }
            else {
            
                // --> DisplayObject is masked, so intersect with "mask"
                
                // first get the ranges of the child in a separate list
                InvalidatedRanges childRanges;
                childRanges.inheritConfig(ranges);
                
                dobj->add_invalidated_bounds(childRanges, force);
                
                // then intersect ranges with topmost "mask"
                childRanges.intersect(rangesStack.top());
                
                // add result to the global ranges
                ranges.add(childRanges);
            
            }
            
        } // not drawing mask 
        
        // <== end of display() equivalent
        
        
        // Mask "drawing" has finished
        if (dobj->isMaskLayer()) {
            // end_submit_mask equivalent
            drawing_mask = false; 
        }
    }
    
    
}

void
DisplayList::sort()
{
    _charsByDepth.sort(DepthLessThan());
}

void
DisplayList::mergeDisplayList(DisplayList & newList)
{
    testInvariant();

    iterator itOld = beginNonRemoved(_charsByDepth);
    iterator itNew = beginNonRemoved(newList._charsByDepth);

    iterator itOldEnd = dlistTagsEffectiveZoneEnd(_charsByDepth);
    iterator itNewEnd = newList._charsByDepth.end(); 
    assert(itNewEnd == dlistTagsEffectiveZoneEnd(newList._charsByDepth) );

    // step1. 
    // starting scanning both lists.
    while (itOld != itOldEnd)
    {
        iterator itOldBackup = itOld;
        
        DisplayObject* chOld = *itOldBackup;
        int depthOld = chOld->get_depth();

        while (itNew != itNewEnd) {
            iterator itNewBackup = itNew;
            
            DisplayObject* chNew = *itNewBackup;
            int depthNew = chNew->get_depth();
            
            // depth in old list is occupied, and empty in new list.
            if (depthOld < depthNew) {

                itOld++;
                // unload the DisplayObject if it's in static zone(-16384,0)
                if (depthOld < 0) {
                    _charsByDepth.erase(itOldBackup);

                     if (chOld->unload()) reinsertRemovedCharacter(chOld);
                     else chOld->destroy();
                }

                break;
            }
            // depth is occupied in both lists
            
            if (depthOld == depthNew) {
                ++itOld;
                ++itNew;
                
                bool is_ratio_compatible = 
                    (chOld->get_ratio() == chNew->get_ratio());

                if (!is_ratio_compatible || chOld->isDynamic() ||
                        !isReferenceable(*chOld)) {
                    // replace the DisplayObject in old list with
                    // corresponding DisplayObject in new list
                    _charsByDepth.insert(itOldBackup, *itNewBackup);
                    _charsByDepth.erase(itOldBackup);
                    
                    // unload the old DisplayObject
                    if (chOld->unload()) reinsertRemovedCharacter(chOld); 
                    else chOld->destroy();
                }
                else {
                    newList._charsByDepth.erase(itNewBackup);

                    // replace the transformation SWFMatrix if the old
                    // DisplayObject accepts static transformation.
                    if (chOld->get_accept_anim_moves()) {
                        chOld->setMatrix(chNew->getMatrix(), true); 
                        chOld->set_cxform(chNew->get_cxform());
                    }
                    chNew->unload();
                    chNew->destroy();
                }

                break;
            }

            // depth in old list is empty, but occupied in new list.
            ++ itNew;
            // add the new DisplayObject to the old list.
            _charsByDepth.insert(itOldBackup, *itNewBackup );
        }

        // break if finish scanning the new list
        if (itNew == itNewEnd) break;
    }

    // step2(only required if scanning of new list finished earlier in step1).
    // continue to scan the static zone of the old list.
    // unload remaining DisplayObjects directly.
    while((itOld != itOldEnd) && ((*itOld)->get_depth() < 0)) {

        DisplayObject* chOld = *itOld;
        itOld = _charsByDepth.erase(itOld);

        if (chOld->unload()) reinsertRemovedCharacter(chOld);
        else chOld->destroy();
    }

    // step3(only required if scanning of old list finished earlier in step1).
    // continue to scan the new list.
    // add remaining DisplayObjects directly.
    if (itNew != itNewEnd) _charsByDepth.insert(itOld, itNew, itNewEnd);

    // step4.
    // Copy all unloaded DisplayObjects from the new display list to the
    // old display list, and clear the new display list
    for (itNew = newList._charsByDepth.begin(); itNew != itNewEnd; ++itNew) {

        DisplayObject* chNew = *itNew;
        int depthNew = chNew->get_depth();

        if (chNew->unloaded()) {
            iterator it =
                std::find_if(_charsByDepth.begin(), _charsByDepth.end(),
                    DepthGreaterOrEqual(depthNew));
            
            _charsByDepth.insert(it, *itNew);
        }
    }

    // clear the new display list after merge
    // ASSERT:
    //     - Any element in newList._charsByDepth is either marked as unloaded
    //    or found in this list
#if GNASH_PARANOIA_LEVEL > 1
    for (iterator i = newList._charsByDepth.begin(),
            e = newList._charsByDepth.end(); i != e; ++i) {

        DisplayObject* ch = *i;
        if (!ch->unloaded()) {

            iterator found =
                std::find(_charsByDepth.begin(), _charsByDepth.end(), ch);
            
            if (found == _charsByDepth.end())
            {
                log_error("mergeDisplayList: DisplayObject %s (%s at depth "
                        "%d [%d]) about to be discarded in given display list"
                        " is not marked as unloaded and not found in the"
                        " merged current displaylist",
                        ch->getTarget(), typeName(*ch), ch->get_depth(),
                        ch->get_depth()-DisplayObject::staticDepthOffset);
                std::abort();
            }
        }
    }
#endif
    newList._charsByDepth.clear();

    testInvariant();
}


void
DisplayList::reinsertRemovedCharacter(DisplayObject* ch)
{
    assert(ch->unloaded());
    assert(!ch->isDestroyed());
    testInvariant();

    // TODO: have this done by DisplayObject::unload() instead ?
    int oldDepth = ch->get_depth();
    int newDepth = DisplayObject::removedDepthOffset - oldDepth;
    ch->set_depth(newDepth);

    // TODO: optimize this by searching from the end(lowest depth).
    container_type::iterator it =
        std::find_if(_charsByDepth.begin(), _charsByDepth.end(),
                DepthGreaterOrEqual(newDepth));

    _charsByDepth.insert(it, ch);

    testInvariant();
}

void
DisplayList::removeUnloaded()
{
    testInvariant();

    _charsByDepth.remove_if(boost::mem_fn(&DisplayObject::unloaded));

    testInvariant();
}

bool
DisplayList::isSorted() const
{
    if (_charsByDepth.empty()) return true;
    return std::adjacent_find(_charsByDepth.begin(), _charsByDepth.end(),
            DepthGreaterThan()) == _charsByDepth.end();
}


#if GNASH_PARANOIA_LEVEL > 1 && !defined(NDEBUG)
DisplayList::const_iterator
DisplayList::nonRemoved() const
{
    return beginNonRemoved(_charsByDepth);
}
#endif

namespace {

DisplayList::iterator
beginNonRemoved(DisplayList::container_type& c)
{
    const int depth = DisplayObject::removedDepthOffset -
        DisplayObject::staticDepthOffset;
    
    return std::find_if(c.begin(), c.end(), DepthGreaterOrEqual(depth));
}

DisplayList::const_iterator
beginNonRemoved(const DisplayList::container_type& c)
{
    const int depth = DisplayObject::removedDepthOffset -
        DisplayObject::staticDepthOffset;

    return std::find_if(c.begin(), c.end(), DepthGreaterOrEqual(depth));
}

DisplayList::iterator
dlistTagsEffectiveZoneEnd(DisplayList::container_type& c)
{
    return std::find_if(c.begin(), c.end(), 
             DepthGreaterOrEqual(0xffff + DisplayObject::staticDepthOffset));
}

DisplayList::const_iterator
dlistTagsEffectiveZoneEnd(const DisplayList::container_type& c)
{
    return std::find_if(c.begin(), c.end(), 
             DepthGreaterOrEqual(0xffff + DisplayObject::staticDepthOffset));
}

} // anonymous namespace


std::ostream&
operator<< (std::ostream& os, const DisplayList& dl)
{
    os << "By depth: ";
    for (DisplayList::const_iterator it = dl._charsByDepth.begin(),
            itEnd = dl._charsByDepth.end(); it != itEnd; ++it) {

        const DisplayObject* item = *it; 
        if (it != dl._charsByDepth.begin()) os << " | ";
        os << " name:" << item->get_name()
           << " depth:" << item->get_depth();
    }

    return os;
}

} // namespace gnash


// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
