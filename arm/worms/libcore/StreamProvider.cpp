// StreamProvider.cpp:  ActionScript file: or http: stream reader, for Gnash.
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

#include "GnashFileUtilities.h"
#include "StreamProvider.h"
#include "URL.h"
#include "tu_file.h"
#include "NetworkAdapter.h"
#include "URLAccessManager.h"
#include "log.h"
#include "rc.h" // for rcfile
#include "NamingPolicy.h"

#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace gnash {

StreamProvider::StreamProvider(std::auto_ptr<NamingPolicy> np)
    :
    _namingPolicy(np)
{
}


std::auto_ptr<IOChannel>
StreamProvider::getStream(const URL& url, bool namedCacheFile) const
{

    std::auto_ptr<IOChannel> stream;

	if (url.protocol() == "file")
	{
		std::string path = url.path();
		if ( path == "-" )
		{
            // TODO: only allow this as the *very first* call ?
            //       Rationale is a movie might request load of
            //       standard input, being a security issue.
            //       Note also that the FB gui will use stdin
            //       for key events.
            //
			FILE *newin = fdopen(dup(0), "rb");

			// Close on destruction.
			stream.reset(new tu_file(newin, true));
			return stream;
		}
		else
		{
            // check security here !!
		    if (!URLAccessManager::allow(url)) return stream;

			FILE *newin = std::fopen(path.c_str(), "rb");
			if (!newin)  { 
				return stream;
			}
			// Close on destruction
			stream.reset(new tu_file(newin, true));
			return stream;
		}
	}
	else
	{
		if (URLAccessManager::allow(url)) {
			stream = NetworkAdapter::makeStream(url.str(), 
                    namedCacheFile ? namingPolicy()(url) : "");
		}

        // Will return 0 auto_ptr if not allowed.
		return stream;
	}
}

std::auto_ptr<IOChannel>
StreamProvider::getStream(const URL& url, const std::string& postdata,
        const NetworkAdapter::RequestHeaders& headers, bool namedCacheFile)
        const
{

    if (url.protocol() == "file")
    {
        if (!headers.empty())
        {
            log_error("Request Headers discarded while getting stream "
                    "from file: uri");
        }
        return getStream(url, postdata);
    }

	if ( URLAccessManager::allow(url) ) {
		return NetworkAdapter::makeStream(url.str(), postdata, headers,
                    namedCacheFile ? namingPolicy()(url) : "");
	}

	return std::auto_ptr<IOChannel>();

}

std::auto_ptr<IOChannel>
StreamProvider::getStream(const URL& url, const std::string& postdata,
       bool namedCacheFile) const
{

    std::auto_ptr<IOChannel> stream;

	if (url.protocol() == "file")
	{
        if (!postdata.empty())
        {    
		    log_error(_("POST data discarded while getting a stream "
                        "from file: uri"));
        }
		std::string path = url.path();
		if ( path == "-" )
		{
			FILE *newin = fdopen(dup(0), "rb");
			stream.reset(new tu_file(newin, false));
			return stream;
		}
		else
		{
			if ( ! URLAccessManager::allow(url) ) return stream;

			FILE *newin = std::fopen(path.c_str(), "rb");
			if (!newin)  { 
				return stream;
			}
			stream.reset(new tu_file(newin, false));
			return stream;
		}
	}
	else
	{
		if (URLAccessManager::allow(url)) {
			stream = NetworkAdapter::makeStream(url.str(), postdata,
                    namedCacheFile ? namingPolicy()(url) : "");
		}
        // Will return 0 auto_ptr if not allowed.
		return stream;		

	}
}


} // namespace gnash

