// PropertyList.cpp:  ActionScript property lists, for Gnash.
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

#include "PropertyList.h"
#include "Property.h" 
#include "as_environment.h"
#include "log.h"
#include "as_function.h"
#include "as_value.h" // for enumerateValues
#include "VM.h" // For string_table
#include "string_table.h"
#include "GnashAlgorithm.h"

#include <utility> // for std::make_pair
#include <boost/bind.hpp> 

// Define the following to enable printing address of each property added
//#define DEBUG_PROPERTY_ALLOC

// Define this to get verbosity of properties insertion and flags setting
//#define GNASH_DEBUG_PROPERTY 1

namespace gnash {

namespace {

inline
PropertyList::const_iterator
iterator_find(const PropertyList::container& p, const ObjectURI& uri, VM& vm)
{
    
    const bool caseless = vm.getSWFVersion() < 7;

    if (!caseless) {
        return p.project<0>(p.get<1>().find(uri));
    }
        
    string_table& st = vm.getStringTable();
    const string_table::key nocase = st.noCase(uri.name);
    return p.project<0>(p.get<2>().find(nocase));
}

}

bool
PropertyList::setValue(const ObjectURI& uri, const as_value& val,
        const PropFlags& flagsIfMissing)
{
	const_iterator found = iterator_find(_props, uri, getVM(_owner));
	
    string_table& st = getStringTable(_owner);

	if (found == _props.end())
	{
		// create a new member
		Property a(uri, val, flagsIfMissing);
		// Non slot properties are negative ordering in insertion order
		_props.push_back(std::make_pair(a, st.noCase(uri.name)));
#ifdef GNASH_DEBUG_PROPERTY
        ObjectURI::Logger l(getStringTable(_owner));
		log_debug("Simple AS property %s inserted with flags %s",
			l(uri), a.getFlags());
#endif
		return true;
	}

	const Property& prop = found->first;
	if (readOnly(prop) && ! prop.isDestructive())
	{
        ObjectURI::Logger l(getStringTable(_owner));
		log_error(_("Property %s is read-only %s, not setting it to %s"), 
			l(uri), prop.getFlags(), val);
		return false;
	}

	prop.setValue(_owner, val);

	return true;
}

void
PropertyList::setFlags(const ObjectURI& uri, int setFlags, int clearFlags)
{
	iterator found = iterator_find(_props, uri, getVM(_owner));
	if (found == _props.end()) return;
    PropFlags f = found->first.getFlags();
    f.set_flags(setFlags, clearFlags);
	found->first.setFlags(f);

}

void
PropertyList::setFlagsAll(int setFlags, int clearFlags)
{
    for (const_iterator it = _props.begin(); it != _props.end(); ++it) {
        PropFlags f = it->first.getFlags();
        f.set_flags(setFlags, clearFlags);
        it->first.setFlags(f);
    }
}

Property*
PropertyList::getProperty(const ObjectURI& uri) const
{
	iterator found = iterator_find(_props, uri, getVM(_owner));
	if (found == _props.end()) return 0;
	return const_cast<Property*>(&(found->first));
}

std::pair<bool,bool>
PropertyList::delProperty(const ObjectURI& uri)
{
	//GNASH_REPORT_FUNCTION;
	iterator found = iterator_find(_props, uri, getVM(_owner));
	if (found == _props.end()) {
		return std::make_pair(false, false);
	}

	// check if member is protected from deletion
	if (found->first.getFlags().get_dont_delete()) {
		return std::make_pair(true, false);
	}

	_props.erase(found);
	return std::make_pair(true, true);
}

void
PropertyList::dump(std::map<std::string, as_value>& to) 
{
    ObjectURI::Logger l(getStringTable(_owner));

	for (const_iterator i=_props.begin(), ie=_props.end();
            i != ie; ++i)
	{
		to.insert(std::make_pair(l(i->first.uri()), i->first.getValue(_owner)));
	}
}

void
PropertyList::enumerateKeys(as_environment& env, PropertyTracker& donelist)
    const
{
	string_table& st = getStringTable(_owner);

    // We should enumerate in order of creation, not lexicographically.
	for (const_iterator i = _props.begin(),
            ie = _props.end(); i != ie; ++i) {

		if (i->first.getFlags().get_dont_enum()) continue;

        const ObjectURI& uri = i->first.uri();

		if (donelist.insert(uri).second) {
            const std::string& qname = st.value(getName(uri));
			env.push(qname);
		}
	}
}

void
PropertyList::dump()
{
    ObjectURI::Logger l(getStringTable(_owner));
	for (const_iterator it=_props.begin(), itEnd=_props.end();
            it != itEnd; ++it) {
		log_debug("  %s: %s", l(it->first.uri()), it->first.getValue(_owner));
	}
}

bool
PropertyList::addGetterSetter(const ObjectURI& uri, as_function& getter,
	as_function* setter, const as_value& cacheVal,
	const PropFlags& flagsIfMissing)
{
	Property a(uri, &getter, setter, flagsIfMissing);
	iterator found = iterator_find(_props, uri, getVM(_owner));
    
    string_table& st = getStringTable(_owner);
	if (found != _props.end())
	{
		// copy flags from previous member (even if it's a normal member ?)
		a.setFlags(found->first.getFlags());
		a.setCache(found->first.getCache());
		_props.replace(found, std::make_pair(a, st.noCase(uri.name)));

#ifdef GNASH_DEBUG_PROPERTY
        ObjectURI::Logger l(getStringTable(_owner));
		log_debug("AS GetterSetter %s replaced copying flags %s", l(uri),
                a.getFlags());
#endif

	}
	else
	{
		a.setCache(cacheVal);
		_props.push_back(std::make_pair(a, st.noCase(uri.name)));
#ifdef GNASH_DEBUG_PROPERTY
        ObjectURI::Logger l(getStringTable(_owner));
		log_debug("AS GetterSetter %s inserted with flags %s", l(uri),
                a.getFlags());
#endif
	}

	return true;
}

bool
PropertyList::addGetterSetter(const ObjectURI& uri, as_c_function_ptr getter,
	as_c_function_ptr setter, const PropFlags& flagsIfMissing)
{
	Property a(uri, getter, setter, flagsIfMissing);

    string_table& st = getStringTable(_owner);
	const_iterator found = iterator_find(_props, uri, getVM(_owner));
	if (found != _props.end())
	{
		// copy flags from previous member (even if it's a normal member ?)
		a.setFlags(found->first.getFlags());
		_props.replace(found, std::make_pair(a, st.noCase(uri.name)));

#ifdef GNASH_DEBUG_PROPERTY
        ObjectURI::Logger l(getStringTable(_owner));
		log_debug("Native GetterSetter %s replaced copying flags %s", l(uri),
                a.getFlags());
#endif

	}
	else
	{
		_props.push_back(std::make_pair(a, st.noCase(uri.name)));
#ifdef GNASH_DEBUG_PROPERTY
		string_table& st = getStringTable(_owner);
		log_debug("Native GetterSetter %s in namespace %s inserted with "
                "flags %s", st.value(key), st.value(nsId), a.getFlags());
#endif
	}

	return true;
}

bool
PropertyList::addDestructiveGetter(const ObjectURI& uri, as_function& getter, 
	const PropFlags& flagsIfMissing)
{
	const_iterator found = iterator_find(_props, uri, getVM(_owner));
	if (found != _props.end())
	{
        ObjectURI::Logger l(getStringTable(_owner));
		log_error("Property %s already exists, can't addDestructiveGetter",
                l(uri));
		return false; // Already exists.
	}

	// destructive getter don't need a setter
	Property a(uri, &getter, (as_function*)0, flagsIfMissing, true);

    string_table& st = getStringTable(_owner);
	_props.push_back(std::make_pair(a, st.noCase(uri.name)));

#ifdef GNASH_DEBUG_PROPERTY
    ObjectURI::Logger l(getStringTable(_owner));
	log_debug("Destructive AS property %s inserted with flags %s",
            l(uri), a.getFlags());
#endif

	return true;
}

bool
PropertyList::addDestructiveGetter(const ObjectURI& uri,
	as_c_function_ptr getter, const PropFlags& flagsIfMissing)
{
	iterator found = iterator_find(_props, uri, getVM(_owner));
	if (found != _props.end()) return false; 

	// destructive getter don't need a setter
	Property a(uri, getter, (as_c_function_ptr)0, flagsIfMissing, true);
    string_table& st = getStringTable(_owner);
	_props.push_back(std::make_pair(a, st.noCase(uri.name)));

#ifdef GNASH_DEBUG_PROPERTY
    ObjectURI::Logger l(getStringTable(_owner));
	log_debug("Destructive native property %s with flags %s", l(uri),
            a.getFlags());
#endif
	return true;
}

void
PropertyList::clear()
{
	_props.clear();
}

void
PropertyList::setReachable() const
{
    foreachFirst(_props.begin(), _props.end(),
            boost::mem_fn(&Property::setReachable));
}

} // namespace gnash

