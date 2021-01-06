// Color.cpp:  ActionScript class for colors, for Gnash.
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

#include "Color_as.h"
#include "as_object.h" // for inheritance
#include "log.h"
#include "fn_call.h"
#include "Global_as.h"
#include "smart_ptr.h" // for boost intrusive_ptr
#include "builtin_function.h" // need builtin_function
#include "NativeFunction.h" 
#include "cxform.h" // for composition
#include "VM.h"
#include "MovieClip.h"

#include "namedStrings.h"
#include <sstream>


namespace gnash {

// Forward declarations.
namespace {
    as_value color_getrgb(const fn_call& fn);
    as_value color_gettransform(const fn_call& fn);
    as_value color_setrgb(const fn_call& fn);
    as_value color_settransform(const fn_call& fn);
    as_value color_ctor(const fn_call& fn);

    void attachColorInterface(as_object& o);
    inline void parseColorTransProp(as_object& obj, string_table::key key,
            boost::int16_t& target, bool scale);
    inline MovieClip* getTarget(as_object* obj, const fn_call& fn);
}

void
registerColorNative(as_object& o)
{
	VM& vm = getVM(o);

	vm.registerNative(color_setrgb, 700, 0);
	vm.registerNative(color_settransform, 700, 1);
	vm.registerNative(color_getrgb, 700, 2);
	vm.registerNative(color_gettransform, 700, 3);
}

// extern (used by Global.cpp)
void
color_class_init(as_object& where, const ObjectURI& uri)
{
    as_object* cl = registerBuiltinClass(where, color_ctor,
            attachColorInterface, 0, uri);

    as_object* proto =
        cl->getMember(NSV::PROP_PROTOTYPE).to_object(getGlobal(where));

    if (!proto) return;

    const int protect = as_object::DefaultFlags | PropFlags::readOnly;
    proto->set_member_flags(NSV::PROP_uuPROTOuu, protect); 
    proto->set_member_flags(NSV::PROP_CONSTRUCTOR, protect); 

}


namespace {

void
attachColorInterface(as_object& o)
{
	VM& vm = getVM(o);

    const int flags = PropFlags::dontEnum |
                      PropFlags::dontDelete |
                      PropFlags::readOnly;

	o.init_member("setRGB", vm.getNative(700, 0), flags);
	o.init_member("setTransform", vm.getNative(700, 1), flags);
	o.init_member("getRGB", vm.getNative(700, 2), flags);
	o.init_member("getTransform", vm.getNative(700, 3), flags);

}

as_value
color_getrgb(const fn_call& fn)
{
	as_object* obj = ensure<ValidThis>(fn);

    MovieClip* sp = getTarget(obj, fn);
    if (!sp) return as_value();

	const cxform& trans = sp->get_cxform();

    const int r = trans.rb;
    const int g = trans.gb;
    const int b = trans.bb;

    const boost::int32_t rgb = (r<<16) | (g<<8) | b;

	return as_value(rgb);
}

as_value
color_gettransform(const fn_call& fn)
{
	as_object* obj = ensure<ValidThis>(fn);

    MovieClip* sp = getTarget(obj, fn);
    if (!sp) return as_value();

	const cxform& cx = sp->get_cxform();

	// Convert to as_object

    Global_as& gl = getGlobal(fn);
	as_object* ret = gl.createObject();

	ret->init_member("ra", double(cx.ra / 2.56));
	ret->init_member("ga", double(cx.ga / 2.56));
	ret->init_member("ba", double(cx.ba / 2.56));
	ret->init_member("aa", double(cx.aa / 2.56));

	ret->init_member("rb", int(cx.rb));
	ret->init_member("gb", int(cx.gb));
	ret->init_member("bb", int(cx.bb));
	ret->init_member("ab", int(cx.ab));

	return ret;
}

as_value
color_setrgb(const fn_call& fn)
{
	as_object* obj = ensure<ValidThis>(fn);
	
    if (!fn.nargs) {
		IF_VERBOSE_ASCODING_ERRORS(
		log_aserror(_("Color.setRGB() : missing argument"));
		);
		return as_value();
	}

    MovieClip* sp = getTarget(obj, fn);
    if (!sp) return as_value();

	boost::int32_t color = toInt(fn.arg(0));

	const int r = (color & 0xff0000) >> 16;
	const int g = (color & 0x00ff00) >> 8;
	const int b = (color & 0x0000ff);

	cxform newTrans = sp->get_cxform();
	newTrans.rb = static_cast<boost::int16_t>(r);
	newTrans.gb = static_cast<boost::int16_t>(g);
	newTrans.bb = static_cast<boost::int16_t>(b);
	newTrans.ra = 0;
	newTrans.ga = 0;
	newTrans.ba = 0;

    sp->set_cxform(newTrans);

	return as_value();
}
as_value
color_settransform(const fn_call& fn)
{
	as_object* obj = ensure<ValidThis>(fn);

	if (!fn.nargs) {
		IF_VERBOSE_ASCODING_ERRORS(
		log_aserror(_("Color.setTransform() : missing argument"));
		);
		return as_value();
	}

	as_object* trans = fn.arg(0).to_object(getGlobal(fn));

    if (!trans) {
		IF_VERBOSE_ASCODING_ERRORS(
            std::ostringstream ss; fn.dump_args(ss);
            log_aserror(_("Color.setTransform(%s) : first argument doesn't "
                                "cast to an object"), ss.str());
		);
		return as_value();
	}

    MovieClip* sp = getTarget(obj, fn);
    if (!sp) return as_value();

	string_table& st = getStringTable(*obj);

	cxform newTrans = sp->get_cxform();

	// multipliers
	parseColorTransProp(*trans, st.find("ra"), newTrans.ra, true);
	parseColorTransProp(*trans, st.find("ga"), newTrans.ga, true);
	parseColorTransProp(*trans, st.find("ba"), newTrans.ba, true);
	parseColorTransProp(*trans, st.find("aa"), newTrans.aa, true);

	// offsets
	parseColorTransProp(*trans, st.find("rb"), newTrans.rb, false);
	parseColorTransProp(*trans, st.find("gb"), newTrans.gb, false);
	parseColorTransProp(*trans, st.find("bb"), newTrans.bb, false);
	parseColorTransProp(*trans, st.find("ab"), newTrans.ab, false);

	sp->set_cxform(newTrans);

	return as_value();
}

/// The first argument is set as the target property.
//
/// The target property is used to change the MovieClip's color.
/// The pp calls ASSetPropFlags on all Color properties during construction,
/// adding the readOnly flag. Because Gnash adds the __constructor__ property
/// during construction, we have no control over its flags.
as_value
color_ctor(const fn_call& fn)
{
	
    as_object* obj = ensure<ValidThis>(fn);
    
    as_value target;
    if (fn.nargs) target = fn.arg(0);

    const int flags = as_object::DefaultFlags | PropFlags::readOnly;

    obj->init_member(NSV::PROP_TARGET, target, flags); 

    Global_as& gl = getGlobal(fn);
    as_object* null = 0;
    callMethod(&gl, NSV::PROP_AS_SET_PROP_FLAGS, obj, null, 7);

	return as_value(); 
}

inline void
parseColorTransProp (as_object& obj, string_table::key key, boost::int16_t&
        target, bool scale)
{
	as_value tmp;
	if (!obj.get_member(key, &tmp)) return;
    
	const double d = tmp.to_number();
	if ( scale ) {   
        target = static_cast<boost::int16_t>(d * 2.56);
    }
	else {
        target = static_cast<boost::int16_t>(d);
    }
}

// First try to convert target to a MovieClip. If that fails, convert to 
// a string and look up the target.
inline MovieClip*
getTarget(as_object* obj, const fn_call& fn)
{
    const as_value& target = obj->getMember(NSV::PROP_TARGET);
    MovieClip* sp = target.toMovieClip();
    if (sp) return sp;
    DisplayObject* o = fn.env().find_target(target.to_string());
    if (o) return o->to_movie();
    return 0;
}

} // anonymous namespace 
} // end of gnash namespace
