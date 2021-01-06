// ContextMenu_as.cpp:  ActionScript "ContextMenu" class, for Gnash.
//
//   Copyright (C) 2009, 2010 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//


#include "ContextMenu_as.h"
#include "as_object.h" 
#include "log.h"
#include "fn_call.h"
#include "Global_as.h"
#include "smart_ptr.h" 
#include "builtin_function.h" 
#include "namedStrings.h"
#include "Array_as.h"

namespace gnash {

// Forward declarations
namespace {
    as_value contextmenu_hideBuiltInItems(const fn_call& fn);
    as_value contextmenu_copy(const fn_call& fn);
    as_value contextmenu_ctor(const fn_call& fn);

    void attachContextMenuInterface(as_object& o);
    void setBuiltInItems(as_object& o, bool setting);

}

// extern (used by Global.cpp)
void
contextmenu_class_init(as_object& where, const ObjectURI& uri)
{
    registerBuiltinClass(where, contextmenu_ctor, attachContextMenuInterface,
            0, uri);
}


namespace {

/// Functor to implement ContextMenu.copy for the customItems array.
//
/// This pushes the return of copy() called on each array element to the new
/// customItems array.
class CopyMenuItems
{
public:
    CopyMenuItems(string_table::key c, as_object& nc) : _c(c), _target(nc) {}

    void operator()(const as_value& val) {
        Global_as& gl = getGlobal(_target);
        as_object* obj = val.to_object(gl);
        as_value cp = callMethod(obj, _c);
        callMethod(&_target, NSV::PROP_PUSH, cp);
    }
private:
    const string_table::key _c;
    as_object& _target;
};


void
setBuiltInItems(as_object& o, bool setting)
{
    const int flags = 0;
    string_table& st = getStringTable(o);
    o.set_member(st.find("print"), setting, flags);
    o.set_member(st.find("forward_back"), setting, flags);
    o.set_member(st.find("rewind"), setting, flags);
    o.set_member(st.find("loop"), setting, flags);
    o.set_member(st.find("play"), setting, flags);
    o.set_member(st.find("quality"), setting, flags);
    o.set_member(st.find("zoom"), setting, flags);
    o.set_member(st.find("save"), setting, flags);
}


void
attachContextMenuInterface(as_object& o)
{
    const int flags = PropFlags::dontDelete |
                      PropFlags::dontEnum |
                      PropFlags::onlySWF7Up;

    Global_as& gl = getGlobal(o);
    o.init_member("hideBuiltInItems",
            gl.createFunction(contextmenu_hideBuiltInItems), flags);
    o.init_member("copy", gl.createFunction(contextmenu_copy), flags);
}

as_value
contextmenu_hideBuiltInItems(const fn_call& fn)
{
    as_object* ptr = ensure<ValidThis>(fn);
    string_table& st = getStringTable(fn);

    Global_as& gl = getGlobal(fn);
    as_object* builtIns = gl.createObject();
    setBuiltInItems(*builtIns, false);
    ptr->set_member(st.find("builtInItems"), builtIns);
    return as_value();
}


as_value
contextmenu_copy(const fn_call& fn)
{
    as_object* ptr = ensure<ValidThis>(fn);

    Global_as& gl = getGlobal(fn);

    as_function* ctor = gl.getMember(NSV::CLASS_CONTEXTMENU).to_function();
    if (!ctor) {
        return as_value();
    }

    fn_call::Args args;
    as_object* o = constructInstance(*ctor, fn.env(), args);

    if (!o) return as_value();
    
    string_table& st = getStringTable(fn);
    as_value onSelect, builtInItems;
    as_value customItems = gl.createArray();

    ptr->get_member(NSV::PROP_ON_SELECT, &onSelect);
    ptr->get_member(st.find("builtInItems"), &builtInItems);
    ptr->get_member(st.find("customItems"), &customItems);

    // The onSelect and the builtInItems property are simple copies, which
    // means the new object has a reference to the same object.
    o->set_member(NSV::PROP_ON_SELECT, onSelect);
    o->set_member(st.find("builtInItems"), builtInItems);

    // The customItems object is a deep copy that works by calling
    // the copy property of each array member.

    as_value nc;

    // Call new Array(), not []
    as_function* arrayctor = getClassConstructor(fn, "Array");
    if (arrayctor) {
        fn_call::Args args;
        as_object* arr = constructInstance(*arrayctor, fn.env(), args);
        if (arr) {
            as_object* customs;
            if (customItems.is_object() &&
                    (customs = customItems.to_object(getGlobal(fn)))) {
                string_table::key copykey = getStringTable(fn).find("copy");
                CopyMenuItems c(copykey, *arr);
                foreachArray(*customs, c);
            }
            nc = arr;
        }
    }

    o->set_member(st.find("customItems"), nc);

    return as_value(o);
}

as_value
contextmenu_ctor(const fn_call& fn)
{

    as_object* obj = fn.this_ptr;

    // There is always an onSelect member, but it may be undefined.
    const as_value& callback = fn.nargs ? fn.arg(0) : as_value();
    obj->set_member(NSV::PROP_ON_SELECT, callback);
    
    string_table& st = getStringTable(fn);
    Global_as& gl = getGlobal(fn);
    as_object* builtInItems = gl.createObject();
    setBuiltInItems(*builtInItems, true);
    obj->set_member(st.find("builtInItems"), builtInItems);

    // There is an empty customItems array.
    as_object* customItems = gl.createArray();
    obj->set_member(st.find("customItems"), customItems);

    return as_value();
}

} // anonymous namespace 
} // gnash namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:

