// filereference_as.cpp:  ActionScript "FileReference" class, for Gnash.
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
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//


#include "FileReference_as.h"
#include "as_object.h" // for inheritance
#include "log.h"
#include "fn_call.h"
#include "Global_as.h"
#include "smart_ptr.h" // for boost intrusive_ptr
#include "builtin_function.h" // need builtin_function
#include "GnashException.h" // for ActionException
#include "VM.h"

#include <sstream>

namespace gnash {

static as_value filereference_addListener(const fn_call& fn);
static as_value filereference_browse(const fn_call& fn);
static as_value filereference_cancel(const fn_call& fn);
static as_value filereference_download(const fn_call& fn);
static as_value filereference_removeListener(const fn_call& fn);
static as_value filereference_upload(const fn_call& fn);
static as_value filereference_creationDate(const fn_call& fn);
static as_value filereference_creator(const fn_call& fn);
static as_value filereference_modificationDate(const fn_call& fn);
static as_value filereference_name(const fn_call& fn);
static as_value filereference_size(const fn_call& fn);
static as_value filereference_type(const fn_call& fn);
as_value filereference_ctor(const fn_call& fn);

void attachFileReferenceStaticInterface(as_object& /*o*/)
{

}

static void
attachFileReferenceInterface(as_object& o)
{
    Global_as& gl = getGlobal(o);
    o.init_member("addListener", gl.createFunction(filereference_addListener));
    o.init_member("browse", gl.createFunction(filereference_browse));
    o.init_member("cancel", gl.createFunction(filereference_cancel));
    o.init_member("download", gl.createFunction(filereference_download));
    o.init_member("removeListener", gl.createFunction(filereference_removeListener));
    o.init_member("upload", gl.createFunction(filereference_upload));
    o.init_property("creationDate", filereference_creationDate, filereference_creationDate);
    o.init_property("creator", filereference_creator, filereference_creator);
    o.init_property("modificationDate", filereference_modificationDate, filereference_modificationDate);
    o.init_property("name", filereference_name, filereference_name);
    o.init_property("size", filereference_size, filereference_size);
    o.init_property("type", filereference_type, filereference_type);
}

static as_value
filereference_addListener(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_browse(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_cancel(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_download(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_removeListener(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_upload(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_creationDate(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_creator(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_modificationDate(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_name(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_size(const fn_call& /*fn*/)
{
    return as_value();
}

static as_value
filereference_type(const fn_call& /*fn*/)
{
    return as_value();
}



as_value
filereference_ctor(const fn_call& fn)
{
    if (fn.nargs) {
        std::stringstream ss;
        fn.dump_args(ss);
        LOG_ONCE(
            log_unimpl("FileReference(%s): %s", ss.str(),
                _("arguments discarded"))
        );
    }

    return as_value();
}

// extern 
void
filereference_class_init(as_object& where, const ObjectURI& uri)
{
    registerBuiltinClass(where, filereference_ctor,
            attachFileReferenceInterface, 
            attachFileReferenceStaticInterface, uri);
}

} // end of gnash namespace
