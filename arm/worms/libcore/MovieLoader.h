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

#ifndef GNASH_MOVIE_LOADER_H
#define GNASH_MOVIE_LOADER_H

#include "URL.h"
#include "as_object.h" 
#include "MovieClip.h" 

#include <boost/intrusive_ptr.hpp>
#include <list>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/barrier.hpp>

// Forward declarations
namespace gnash {
    class movie_root;
    class movie_definition;
}

namespace gnash {

/// Movie loader
//
/// All public functions are intended to be called by the main thread
/// Hide the asynchonous mechanism of movies loading.
/// Currently implemented using threads, could be refactored to use
/// non-blocking reads.
///
class DSOEXPORT MovieLoader : boost::noncopyable {

public:

    MovieLoader(movie_root& mr);

    ~MovieLoader();

    /// Queue a request for loading a movie
    //
    /// This function constructs the URL and, if required, the postdata
    /// from the arguments. The variables to send should *not* be appended
    /// to @param urlstr before calling this function.
    //
    /// @param urlstr   The url exactly as requested. This may already
    ///                 contain a query string.
    /// @param target   Target for request.
    /// @param data     The variables data to send, URL encoded in
    ///                 key/value pairs
    /// @param method   The VariablesMethod to use for sending the data. If
    ///                 MovieClip::METHOD_NONE, no data will be sent.
    /// @param handler  An object which will be signalled of load
    ///                 events (onLoadStart, onLoadComplete, onLoadInit,
    ///                 onLoadError). Can be null if caller doesn't care.
    ///                 
    void loadMovie(const std::string& url, const std::string& target,
            const std::string& data, MovieClip::VariablesMethod method,
            as_object* handler=0);

    /// Drop all requests and kill the thread
    void clear();

    /// Process all completed movie load requests.
    void processCompletedRequests();

    void setReachable() const;

private:

    /// A movie load request
    class Request : boost::noncopyable {
    public:
        /// @param postdata
        ///   If not null POST method will be used for HTTP.
        ///
        Request(const URL& u, const std::string& t,
                const std::string* postdata, as_object* handler)
                :
                _target(t),
                _url(u),
                _usePost(false),
                _mdef(0),
                _mutex(),
                _handler(handler),
                _completed(false)
        {
            if ( postdata )
            {
                _postData = *postdata;
                _usePost = true;
            }
        }

        const std::string& getTarget() const { return _target; }
        const URL& getURL() const { return _url; }
        const std::string& getPostData() const { return _postData; }
        bool usePost() const { return _usePost; }
        as_object* getHandler() const { return _handler; }
        void setReachable() const {
            if (_handler) _handler->setReachable();
        }

        /// Get the loaded movie definition, if any
        //
        /// @param md the loaded movie_definition is copied here
        ///           if it was impossible to create one.
        ///
        /// @return true if the request was completed, false otherwise.
        ///
        /// RULE: if return is FALSE param 'md' will be set to 0.
        /// RULE: if return is TRUE  param 'md' may be set to 0 or non 0.
        /// RULE: if parameter 'md' is set to non 0, TRUE must be returned.
        ///
        /// locks _mutex
        ///
        bool getCompleted(boost::intrusive_ptr<movie_definition>& md) const
        {
            boost::mutex::scoped_lock lock(_mutex);
            md = _mdef;
            return _completed;
        }

        /// Only check if request is completed
        bool pending() const
        {
            boost::mutex::scoped_lock lock(_mutex);
            return !_completed;
        }

        /// Only check if request is completed
        bool completed() const
        {
            boost::mutex::scoped_lock lock(_mutex);
            return _completed;
        }

        /// Complete the request
        //
        /// @param md the loaded movie_definition, or 0 if
        ///           it was impossible to create one.
        ///
        /// locks _mutex
        ///
        void setCompleted(boost::intrusive_ptr<movie_definition> md)
        {
            boost::mutex::scoped_lock lock(_mutex);
            _mdef = md;
            _completed = true;
        }

    private:
        std::string _target;
        URL _url;
        bool _usePost;
        std::string _postData;
        boost::intrusive_ptr<movie_definition> _mdef;
        mutable boost::mutex _mutex;
        as_object* _handler;
        bool _completed;
    };

    /// Load requests
    typedef std::list<Request*> Requests;
    Requests _requests;

	mutable boost::mutex _requestsMutex;

    void processRequests();
    void processRequest(Request& r);
    void clearRequests();

    /// Check a Request and process if completed.
    //
    /// @return true if the request was completely processed.
    ///
    bool processCompletedRequest(const Request& r);

    /// Was thread kill requested ?
    bool killed();

    bool _killed;

	boost::mutex _killMutex;

    boost::condition _wakeup;

    /// needed for some facilities like find_character_by_target
    movie_root& _movieRoot;

    std::auto_ptr<boost::thread> _thread;

	// Barrier to ensure that _thread
	// is initialized before the loader thread
	// continues execution
	boost::barrier _barrier;

};

} // namespace gnash

#endif // GNASH_MOVIE_LOADER_H
