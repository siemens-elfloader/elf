// dlist.h:  Display list definitions, for Gnash.
// 
//   Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010 Free Software
//   Foundation, Inc
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef GNASH_DLIST_H
#define GNASH_DLIST_H

#include "snappingrange.h"
#include "DisplayObject.h"

#include <string>
#include <list>
#include <iosfwd>
#if GNASH_PARANOIA_LEVEL > 1 && !defined(NDEBUG)
#include <set>  // for testInvariant
#include "log.h"
#endif

// GNASH_PARANOIA_LEVEL:
// 0 : (not unimplemented)
// 1 : quick assertions
// 2 : add testInvariant
//
#ifndef GNASH_PARANOIA_LEVEL
# define GNASH_PARANOIA_LEVEL 1
#endif

namespace gnash {
	class cxform;
	class Renderer;
}

namespace gnash {

/// A list of on-stage DisplayObjects, ordered by depth
//
/// Any MovieClip has an associated DisplayList
/// that may change from frame to frame due to control
/// tags instructing when to add or remove DisplayObjects
/// from the stage.
///
class DisplayList
{

public:

	typedef std::list<DisplayObject*> container_type;
	typedef container_type::iterator iterator;
	typedef container_type::const_iterator const_iterator;
	typedef container_type::reverse_iterator reverse_iterator;
	typedef container_type::const_reverse_iterator const_reverse_iterator;

    DisplayList() {}
    ~DisplayList() {}

    /// Output operator
	friend std::ostream& operator<< (std::ostream&, const DisplayList&);

	/// \brief
	/// Place a new DisplayObject at the specified depth,
	/// replacing any existing DisplayObject at the same depth.
	//
	/// If a DisplayObject is replaced, it's unload() method
	/// is invoked.
	///
	/// If applicable, the event_id::LOAD event
	/// associated with the given DisplayObject
	/// is called as last step of addition. 
	///
	/// @param ch 
	///	the new DisplayObject to be added into the list.
	///
	/// @param depth 
	///	depth at which the new DisplayObject is placed.
    void placeDisplayObject(DisplayObject* ch, int depth);

	/// \brief
	/// Replace the old DisplayObject at the specified depth with
	/// the given new DisplayObject.
	//
	/// Calls unload on the removed DisplayObject.
	///
	/// @param ch 
	///	the new DisplayObject to be put
	///
	/// @param depth 
	///	depth to be replaced
	///
	/// @param use_old_cxform
	/// true:  set the new DisplayObject's cxform to the old one.
	/// false: keep the new DisplayObject's cxform.
	///
	/// @param use_old_matrix
	/// true:  set the new DisplayObject's transformation SWFMatrix to the old one.
	/// false: keep the new DisplayObject's transformation SWFMatrix.
	void replaceDisplayObject(DisplayObject* ch, int depth, bool use_old_cxform,
		bool use_old_matrix);

	/// \brief
	/// Change depth of the given DisplayObjects in the list,
	/// swapping with any existing DisplayObject at target depth.
	//
	/// List ordering will be maintained by this function.
	///
	/// Any DisplayObject affected by this operation (none on invalid call,
	/// 1 if new depth is not occupied, 2 otherwise) will be:
	///	- bounds invalidated (see DisplayObject::set_invalidated)
	///	- marked as script-transformed (see DisplayObject::transformedByScript)
	/// 
	/// @param ch
	///	The DisplayObject to apply depth swapping to.
	///	If not found in the list, an error is raised
	///	and no other action is taken.
	///
	/// @param depth
	///	The new depth to assign to the given DisplayObject.
	///	If occupied by another DisplayObject, the target DisplayObject
	///	will get the current depth of the first.
	///	If target depth equals the current depth of DisplayObject, an
	///	assertion fails, as I think the caller should check this instead.
	///
	void swapDepths(DisplayObject* ch, int depth);

	/// \brief
	/// Updates the transform properties of the object at the
	/// specified depth, unless its get_accept_anim_moves() returns false.
	//
	///  See DisplayObject::get_accept_anim_moves()
	///
	/// @param color_xform
	///	The color tranform to assign to the DisplayObject at the given depth.
	///	If NULL the orignial color transform will be kept.
	//
	/// @param mat
	///	The SWFMatrix tranform to assign to the DisplayObject at the given depth.
	///	If NULL the orignial SWFMatrix will be kept.
	///
	/// @param ratio
	/// The new ratio value to assign to the DisplayObject at the given depth.
	/// If NULL the original ratio will be kept.
	///
	/// @clip_depth
	/// Not used at the moment.
	/// 
	void moveDisplayObject( int depth, const cxform* color_xform,
            const SWFMatrix* mat, int* ratio, int* clip_depth);

	/// Removes the object at the specified depth.
	//
	/// Calls unload on the removed DisplayObject.
	void removeDisplayObject(int depth);

	/// Remove all unloaded DisplayObject from the list
	//
	/// Removed DisplayObjects still in the list are those
	/// on which onUnload event handlers were defined..
	///
	/// NOTE: we don't call the function recursively in the 
	///       contained elements, as that should not be needed
	///	  (ie: any inned thing will not be accessible anyway)
	void removeUnloaded();

	/// Unload the DisplayObjects in this DisplayList removing
	/// all but the ones with on onUnload event defined
	/// (checked by calling ::unload on them) and keeping
	/// the others, w/out depth-shifting them.
	///
	/// Return true if any child was kept (as they had onUnload defined)
	bool unload();

	/// destroy all DisplayObjects in this DisplayList
	void destroy();

	/// Add a DisplayObject in the list, maintaining depth-order
	//
	///
	/// @param ch
	///	The DisplayObject to add
	///
	/// @param replace
	///	If true the given DisplayObject would replace any
	///	pre-existing DisplayObject at the same depth.
	void add(DisplayObject* ch, bool replace);

    /// Removes the specified DisplayObject
    //
    /// Other DisplayObjects are left untouched.
    /// This implements AS3 DisplayObjectContainer.removeChild().
    //
    /// @param obj      The DisplayObject to remove.
    void removeDisplayObject(DisplayObject* obj);

    /// Removes the DisplayObject at the specified index
    //
    /// Other DisplayObjects are left untouched.
    /// This implements AS3 DisplayObjectContainer.removeChildAt().
    //
    /// @param index    The index from which to remove the DisplayObject.
    /// @return         The DisplayObject removed, or 0 if none was removed.
    DisplayObject* removeDisplayObjectAt(int index);

    /// Inserts a DisplayObject at the specified index (depth)
    //
    /// If a DisplayObject is already at that index, it is moved up.
    /// This implements AS3 DisplayObjectContainer.addChildAt().
    //
    /// @param obj      The DisplayObject to insert. This should already be
    ///                 removed from any other DisplayLists. It should not be
    ///                 the owner of this DisplayList or any parent of that
    ///                 owner.
    /// @param index    The index at which to insert the DisplayObject.
    void insertDisplayObject(DisplayObject* obj, int index);

    /// Adds a DisplayObject at the top of the DisplayList.
    //
    /// This implements AS3 DisplayObjectContainer.addChild().
    //
    /// @param obj      The DisplayObject to insert. This should already be
    ///                 removed from any other DisplayLists. It should not be
    ///                 the owner of this DisplayList or any parent of that
    ///                 owner.
    void addDisplayObject(DisplayObject* obj);

	/// \brief
	/// Display the referenced DisplayObjects.
	/// Lower depths are obscured by higher depths.
	void display(Renderer& renderer);
	
	void omit_display();

	/// May return NULL.
	DisplayObject* getDisplayObjectAtDepth(int depth) const;

	/// If there are multiples, returns the *first* match only!
	DisplayObject* getDisplayObjectByName(string_table& st,
            string_table::key name, bool caseless) const;

	/// \brief 
	/// Visit each DisplayObject in the list in depth order
	/// (lower depth first).
	//
	/// The visitor functor will 
	/// receive a DisplayObject pointer; must return true if
	/// it wants next item or false to exit the loop.
	///
	/// NOTE: all elements in the list are visited, even
	///       the removed ones (unloaded)
	/// TODO: inspect if worth providing an arg to skip removed
	template <class V> inline void visitForward(V& visitor);

	/// \brief 
	/// Visit each DisplayObject in the list in reverse depth
	/// order (higher depth first).
	//
	/// The visitor functor
	/// will receive a DisplayObject pointer; must return true if
	/// it wants next item or false
	/// to exit the loop.
	///
	/// NOTE: all elements in the list are visited, even
	///       the removed ones (unloaded)
	/// TODO: inspect if worth providing an arg to skip removed
	template <class V> inline void visitBackward(V& visitor);
    template <class V> inline void visitBackward(V& visitor) const;

	/// \brief 
	/// Visit each and all DisplayObject in the list.
	//
	/// Scan happens in arbitrary order, if order is
	/// important use visitBackward or visitForward
	///
	/// The visitor functor will receive a DisplayObject pointer,
	/// it's return value is not used so can return void.
	///
	/// NOTE: all elements in the list are visited, even
	///       the removed ones (unloaded)
	/// TODO: inspect if worth providing an arg to skip removed
	template <class V> inline void visitAll(V& visitor);
	template <class V> inline void visitAll(V& visitor) const;

	/// dump list to logfile/stderr
	void dump() const;

    /// Like DisplayObject_instance::add_invalidated_bounds() this method calls the
    /// method with the same name of all childs.	
	void add_invalidated_bounds(InvalidatedRanges& ranges, bool force);	
	
	/// Return number of elements in the list
	size_t size() const { 
		return _charsByDepth.size();
	}

	/// Return true if the list contains no elements 
	bool empty() const {
		return _charsByDepth.empty();
	}

	/// Return the next highest available depth
	//
	/// Placing an object at the depth returned by
	/// this function should result in a DisplayObject
	/// that is displayd above all others
	///
	int getNextHighestDepth() const;

	/// Sort list by depth (lower depths first)
	//
	/// You only need calling this method if depth
	/// of DisplayObjects on the list has been externally
	/// changed. Usually it is DisplayList itself
	/// assigning depths, so won't need to call it.
	///
	/// A notable use for this is backing up a specific
	/// state and restoring it later. Restore step would
	/// need reordering.
	void sort();
	
	/// \brief
	/// merge the given display list
	void mergeDisplayList(DisplayList& newList);

	bool operator==(const DisplayList& other) const {
        return _charsByDepth == other._charsByDepth;
    }

	bool operator!=(const DisplayList& other) const {
        return _charsByDepth != other._charsByDepth;
    }
	
#if GNASH_PARANOIA_LEVEL > 1 && !defined(NDEBUG)
    DisplayList::const_iterator nonRemoved() const;

    void testInvariant() const
	{
		DisplayList sorted = *this;

        // check no duplicated depths above non-removed zone.
		std::set<int> depths;
		for (const_iterator it = nonRemoved(),
                itEnd = _charsByDepth.end(); it != itEnd; ++it) {

			DisplayObject* ch = *it;
			int depth = ch->get_depth();
			if (!depths.insert(depth).second) {
				log_debug("Depth %d is duplicated in DisplayList %p",
                        depth, (const void*)this);
                std::abort();
			}
		}
		assert(isSorted()); // check we didn't screw up ordering
	}
#else
    void testInvariant() const {}
#endif 

private:

	/// Re-insert a removed-from-stage DisplayObject after appropriately
	/// shifting its depth based on the DisplayObject::removedDepthOffset
	/// value.
	//
	/// PRE-CONDITIONS 
	///	- ch::isUnloaded() returns true (assertion fails otherwise)
	///	- ch is not already in the list (assertion fails otherwise)
	///
	/// TODO: inspect what should happen if the target depth is already
    /// occupied
	void reinsertRemovedCharacter(DisplayObject* ch);

	container_type _charsByDepth;

	/// Check that the list is sorted by depth
	bool isSorted() const;
};

template <class V>
void
DisplayList::visitForward(V& visitor)
{
	for (iterator it = _charsByDepth.begin(), itEnd = _charsByDepth.end();
		it != itEnd; ++it) {
		if (!visitor(*it)) break;
	}
}

template <class V>
void
DisplayList::visitBackward(V& visitor)
{
	for (reverse_iterator it = _charsByDepth.rbegin(),
			itEnd = _charsByDepth.rend(); it != itEnd; ++it) {
		if (!visitor(*it)) break;
	}
}

template <class V>
void
DisplayList::visitBackward(V& visitor) const
{
	for (const_reverse_iterator it = _charsByDepth.rbegin(),
			itEnd = _charsByDepth.rend(); it != itEnd; ++it) {
		if (!visitor(*it)) break;
	}
}

template <class V>
void
DisplayList::visitAll(V& visitor)
{
	for (iterator it = _charsByDepth.begin(), itEnd = _charsByDepth.end();
		it != itEnd; ++it) {

		visitor(*it);
	}
}

template <class V>
void
DisplayList::visitAll(V& visitor) const
{
	for (const_iterator it = _charsByDepth.begin(),
            itEnd = _charsByDepth.end(); it != itEnd; ++it) {

		visitor(*it);
	}
}

std::ostream& operator<< (std::ostream&, const DisplayList&);

} // namespace gnash


#endif // GNASH_DLIST_H



// Local Variables:
// mode: C++
// c-basic-offset: 8 
// tab-width: 8
// indent-tabs-mode: t
// End:
