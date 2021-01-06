// SWFMovieDefinition.cpp: load a SWF definition
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

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h" // USE_SWFTREE
#endif

#include "SWFMovieDefinition.h"

#include <boost/bind.hpp>
#include <boost/version.hpp>
#include <boost/thread.hpp>
#include <iomanip>
#include <memory>
#include <string>
#include <algorithm> // std::make_pair

#include "GnashSleep.h"
#include "smart_ptr.h" // GNASH_USE_GC
#include "movie_definition.h" // for inheritance
#include "zlib_adapter.h"
#include "IOChannel.h" // for use
#include "SWFStream.h"
#include "GnashImageJpeg.h"
#include "RunResources.h"
#include "Font.h"
#include "VM.h"
#include "log.h"
#include "SWFMovie.h"
#include "GnashException.h" // for parser exception
#include "ControlTag.h"
#include "sound_definition.h" // for sound_sample
#include "GnashAlgorithm.h"
#include "SWFParser.h"
#include "Global_as.h"
#include "namedStrings.h"
#include "as_function.h"
#include "CachedBitmap.h"

// Debug frames load
#undef DEBUG_FRAMES_LOAD

// Define this this to load movies using a separate thread
// (undef and it will fully load a movie before starting to play it)
#define LOAD_MOVIES_IN_A_SEPARATE_THREAD 1

// Debug threads locking
//#undef DEBUG_THREADS_LOCKING

// Define this to get debugging output for symbol library use
//#define DEBUG_EXPORTS

namespace gnash
{

SWFMovieLoader::SWFMovieLoader(SWFMovieDefinition& md)
    :
    _movie_def(md),
    _thread(NULL),
    _barrier(2) // us and the main thread..
{
}

SWFMovieLoader::~SWFMovieLoader()
{
    // we should assert _movie_def._loadingCanceled
    // but we're not friend yet (anyone introduce us ?)
    if ( _thread.get() )
    {
        //cout << "Joining thread.." << endl;
        _thread->join();
    }
}

bool
SWFMovieLoader::started() const
{
    boost::mutex::scoped_lock lock(_mutex);

    return _thread.get() != NULL;
}

bool
SWFMovieLoader::isSelfThread() const
{
    boost::mutex::scoped_lock lock(_mutex);

    if (!_thread.get()) {
        return false;
    }
#if BOOST_VERSION < 103500
    boost::thread this_thread;
    return this_thread == *_thread;
#else
    return boost::this_thread::get_id() == _thread->get_id();
#endif

}

// static..
void
SWFMovieLoader::execute(SWFMovieLoader& ml, SWFMovieDefinition* md)
{
    ml._barrier.wait(); // let _thread assignment happen before going on
    md->read_all_swf();
}

bool
SWFMovieLoader::start()
{
#ifndef LOAD_MOVIES_IN_A_SEPARATE_THREAD
    std::abort();
#endif
    // don't start SWFMovieLoader thread() which rely
    // on boost::thread() returning before they are executed. Therefore,
    // we must employ locking.
    // Those tests do seem a bit redundant, though...
    boost::mutex::scoped_lock lock(_mutex);

    _thread.reset(new boost::thread(boost::bind(
                    execute, boost::ref(*this), &_movie_def)));

    _barrier.wait(); // let execution start befor returning

    return true;
}


//
// SWFMovieDefinition
//

SWFMovieDefinition::SWFMovieDefinition(const RunResources& runResources)
    :
    m_frame_rate(30.0f),
    m_frame_count(0u),
    m_version(0),
    _frames_loaded(0u),
    _waiting_for_frame(0),
    m_loading_sound_stream(-1),
    m_file_length(0),
    m_jpeg_in(0),
    _loader(*this),
    _loadingCanceled(false),
    _runResources(runResources),
    _as3(false)
{
}

SWFMovieDefinition::~SWFMovieDefinition()
{
    // Request cancelation of the loading thread
    _loadingCanceled = true;
}

void
SWFMovieDefinition::addDisplayObject(boost::uint16_t id, SWF::DefinitionTag* c)
{
    assert(c);
    boost::mutex::scoped_lock lock(_dictionaryMutex);
    _dictionary.addDisplayObject(id, c);
    addControlTag(c);
}

SWF::DefinitionTag*
SWFMovieDefinition::getDefinitionTag(boost::uint16_t id) const
{

    boost::mutex::scoped_lock lock(_dictionaryMutex);

    boost::intrusive_ptr<SWF::DefinitionTag> ch = 
        _dictionary.getDisplayObject(id);
#ifndef GNASH_USE_GC
    assert(ch == NULL || ch->get_ref_count() > 1);
#endif 
    return ch.get(); 
}

void
SWFMovieDefinition::add_font(int font_id, Font* f)
{
    assert(f);
    m_fonts.insert(std::make_pair(font_id, boost::intrusive_ptr<Font>(f)));
}

Font*
SWFMovieDefinition::get_font(int font_id) const
{

    FontMap::const_iterator it = m_fonts.find(font_id);
    if ( it == m_fonts.end() ) return NULL;
    boost::intrusive_ptr<Font> f = it->second;
    assert(f->get_ref_count() > 1);
    return f.get();
}

Font*
SWFMovieDefinition::get_font(const std::string& name, bool bold, bool italic)
    const
{

    for (FontMap::const_iterator it=m_fonts.begin(), itEnd=m_fonts.end(); it != itEnd; ++it)
    {
       Font* f = it->second.get();
       if ( f->matches(name, bold, italic) ) return f;
    }
    return 0;
}

CachedBitmap*
SWFMovieDefinition::getBitmap(int id) const
{
    const Bitmaps::const_iterator it = _bitmaps.find(id);
    if (it == _bitmaps.end()) return 0;
    return it->second.get();
}

void
SWFMovieDefinition::addBitmap(int id, boost::intrusive_ptr<CachedBitmap> im)
{
    assert(im);
    _bitmaps.insert(std::make_pair(id, im));
}

sound_sample*
SWFMovieDefinition::get_sound_sample(int id) const
{
    SoundSampleMap::const_iterator it = m_sound_samples.find(id);
    if ( it == m_sound_samples.end() ) return 0;

    boost::intrusive_ptr<sound_sample> ch = it->second;
#ifndef GNASH_USE_GC
    assert(ch->get_ref_count() > 1);
#endif 

    return ch.get();
}

void SWFMovieDefinition::add_sound_sample(int id, sound_sample* sam)
{
    assert(sam);
    IF_VERBOSE_PARSE(
    log_parse(_("Add sound sample %d assigning id %d"),
        id, sam->m_sound_handler_id);
    )
    m_sound_samples.insert(std::make_pair(id,
                boost::intrusive_ptr<sound_sample>(sam)));
}

// Read header and assign url
bool
SWFMovieDefinition::readHeader(std::auto_ptr<IOChannel> in,
        const std::string& url)
{

    _in = in;

    // we only read a movie once
    assert(!_str.get());

    _url = url.empty() ? "<anonymous>" : url;

    boost::uint32_t file_start_pos = _in->tell();
    boost::uint32_t header = _in->read_le32();
    m_file_length = _in->read_le32();
    _swf_end_pos = file_start_pos + m_file_length;

    m_version = (header >> 24) & 255;
    if ((header & 0x0FFFFFF) != 0x00535746
        && (header & 0x0FFFFFF) != 0x00535743)
        {
        // ERROR
        log_error(_("gnash::SWFMovieDefinition::read() -- "
            "file does not start with a SWF header"));
        return false;
        }
    const bool compressed = (header & 255) == 'C';

    IF_VERBOSE_PARSE(
        log_parse(_("version: %d, file_length: %d"), m_version, m_file_length);
    )

    if (m_version > 7)
    {
        log_unimpl(_("SWF%d is not fully supported, trying anyway "
            "but don't expect it to work"), m_version);
    }

    if (compressed) {
#ifndef HAVE_ZLIB_H
        log_error(_("SWFMovieDefinition::read(): unable to read "
            "zipped SWF data; gnash was compiled without zlib support"));
        return false;
#else
        IF_VERBOSE_PARSE(
            log_parse(_("file is compressed"));
        );

        // Uncompress the input as we read it.
        _in = zlib_adapter::make_inflater(_in);
#endif
    }

    assert(_in.get());

    _str.reset(new SWFStream(_in.get()));

    m_frame_size.read(*_str);
    // If the SWFRect is malformed, SWFRect::read would already 
    // print an error. We check again here just to give 
    // the error are better context.
    if ( m_frame_size.is_null() )
    {
        IF_VERBOSE_MALFORMED_SWF(
        log_swferror("non-finite movie bounds");
        );
    }

    _str->ensureBytes(2 + 2); // frame rate, frame count.
    m_frame_rate = _str->read_u16() / 256.0f;
    if (!m_frame_rate) {
        m_frame_rate = std::numeric_limits<boost::uint16_t>::max();
    }

    m_frame_count = _str->read_u16();

    // TODO: This seems dangerous, check closely
    if (!m_frame_count) ++m_frame_count;

    IF_VERBOSE_PARSE(
        log_parse(_("frame size = %s, frame rate = %f, frames = %d"),
            m_frame_size, m_frame_rate, m_frame_count);
    );

    setBytesLoaded(_str->tell());
    return true;
}

// Fire up the loading thread
bool
SWFMovieDefinition::completeLoad()
{

    // should call this only once
    assert( ! _loader.started() );

    // should call readHeader before this
    assert(_str.get());

#ifdef LOAD_MOVIES_IN_A_SEPARATE_THREAD

    // Start the loading frame
    if ( ! _loader.start() )
    {
        log_error(_("Could not start loading thread"));
        return false;
    }

    // Wait until 'startup_frames' have been loaded
#if 1
    size_t startup_frames = 0;
#else
    size_t startup_frames = m_frame_count;
#endif
    ensure_frame_loaded(startup_frames);

#else // undef LOAD_MOVIES_IN_A_SEPARATE_THREAD

    read_all_swf();
#endif

    return true;
}


// 1-based frame number
bool
SWFMovieDefinition::ensure_frame_loaded(size_t framenum) const
{
    boost::mutex::scoped_lock lock(_frames_loaded_mutex);

#ifndef LOAD_MOVIES_IN_A_SEPARATE_THREAD
    return (framenum <= _frames_loaded);
#endif

    if ( framenum <= _frames_loaded ) return true;

    _waiting_for_frame = framenum;

    // TODO: return false on timeout
    _frame_reached_condition.wait(lock);

    return ( framenum <= _frames_loaded );
}

Movie*
SWFMovieDefinition::createMovie(Global_as& gl, DisplayObject* parent)
{
    as_object* o = getObjectWithPrototype(gl, NSV::CLASS_MOVIE_CLIP);
    return new SWFMovie(o, this, parent);
}


//
// CharacterDictionary
//

std::ostream&
operator<<(std::ostream& o, const CharacterDictionary& cd)
{

       for (CharacterDictionary::CharacterConstIterator it = cd.begin(), 
            endIt = cd.end(); it != endIt; it++)
       {
           o << std::endl
             << "Character: " << it->first
             << " at address: " << static_cast<void*>(it->second.get());
       }
       
       return o;
}

boost::intrusive_ptr<SWF::DefinitionTag>
CharacterDictionary::getDisplayObject(int id) const
{
    CharacterConstIterator it = _map.find(id);
    if ( it == _map.end() )
    {
        IF_VERBOSE_PARSE(
            log_parse(_("Could not find char %d, dump is: %s"), id, *this);
        );
        return boost::intrusive_ptr<SWF::DefinitionTag>();
    }
    
    return it->second;
}

void
CharacterDictionary::addDisplayObject(int id,
        boost::intrusive_ptr<SWF::DefinitionTag> c)
{
    _map[id] = c;
}


void
SWFMovieDefinition::read_all_swf()
{
    assert(_str.get());

#ifdef LOAD_MOVIES_IN_A_SEPARATE_THREAD
    assert( _loader.isSelfThread() );
    assert( _loader.started() );
#else
    assert( ! _loader.started() );
    assert( ! _loader.isSelfThread() );
#endif

    SWFParser parser(*_str, this, _runResources);

    const size_t startPos = _str->tell();
    assert (startPos <= _swf_end_pos);

    size_t left = _swf_end_pos - startPos;

    const size_t chunkSize = 65535;

    try {
        while (left) {

            if (_loadingCanceled) {
                log_debug("Loading thread cancelation requested, "
                        "returning from read_all_swf");
                return;
            }
            if (!parser.read(std::min<size_t>(left, chunkSize))) break;
            
            left -= parser.bytesRead();
            setBytesLoaded(startPos + parser.bytesRead());
        }

        // Make sure we won't leave any pending writers
        // on any eventual fd-based IOChannel.
        _str->consumeInput();
    
    }
    catch (const ParserException& e) {
        // This is a fatal parser error.
        log_error(_("Error while parsing SWF stream."));
    }

    // Set bytesLoaded to the current stream position unless it's greater
    // than the reported length. TODO: should we be trying to continue
    // parsing after an exception?
    setBytesLoaded(std::min<size_t>(_str->tell(), _swf_end_pos));

    size_t floaded = get_loading_frame();
    if (!m_playlist[floaded].empty())
    {
        IF_VERBOSE_MALFORMED_SWF(
        log_swferror(_("%d control tags are NOT followed by"
            " a SHOWFRAME tag"), m_playlist[floaded].size());
        );
    }

    if ( m_frame_count > floaded )
    {
        IF_VERBOSE_MALFORMED_SWF(
        log_swferror(_("%d frames advertised in header, but only %d "
                "SHOWFRAME tags found in stream. Pretending we loaded "
                "all advertised frames"), m_frame_count, floaded);
        );
        boost::mutex::scoped_lock lock(_frames_loaded_mutex);
        _frames_loaded = m_frame_count;
        // Notify any thread waiting on frame reached condition
        _frame_reached_condition.notify_all();
    }
}

size_t
SWFMovieDefinition::get_loading_frame() const
{
    boost::mutex::scoped_lock lock(_frames_loaded_mutex);
    return _frames_loaded;
}

void
SWFMovieDefinition::incrementLoadedFrames()
{
    boost::mutex::scoped_lock lock(_frames_loaded_mutex);

    ++_frames_loaded;

    if ( _frames_loaded > m_frame_count )
    {
        IF_VERBOSE_MALFORMED_SWF(
            log_swferror(_("number of SHOWFRAME tags "
                "in SWF stream '%s' (%d) exceeds "
                "the advertised number in header (%d)."),
                get_url(), _frames_loaded,
                m_frame_count);
        )
    }

#ifdef DEBUG_FRAMES_LOAD
    log_debug(_("Loaded frame %u/%u"), _frames_loaded, m_frame_count);
#endif

    // signal load of frame if anyone requested it
    // FIXME: _waiting_for_frame needs mutex ?
    if (_waiting_for_frame && _frames_loaded >= _waiting_for_frame )
    {
        // or should we notify_one ?
        // See: http://boost.org/doc/html/condition.html
        _frame_reached_condition.notify_all();
    }

}

void
SWFMovieDefinition::registerExport(const std::string& symbol,
        boost::uint16_t id)
{
    assert(id);

    boost::mutex::scoped_lock lock(_exportedResourcesMutex);
#ifdef DEBUG_EXPORTS
    log_debug("%s registering export %s, %s", get_url(), symbol, id);
#endif
    _exportTable[symbol] = id;
}


void
SWFMovieDefinition::add_frame_name(const std::string& n)
{
    boost::mutex::scoped_lock lock1(_namedFramesMutex);
    boost::mutex::scoped_lock lock2(_frames_loaded_mutex);

    _namedFrames.insert(std::make_pair(n, _frames_loaded));
}

bool
SWFMovieDefinition::get_labeled_frame(const std::string& label,
        size_t& frame_number) const
{
    boost::mutex::scoped_lock lock(_namedFramesMutex);
    NamedFrameMap::const_iterator it = _namedFrames.find(label);
    if (it == _namedFrames.end()) return false;
    frame_number = it->second;
    return true;
}


boost::uint16_t
SWFMovieDefinition::exportID(const std::string& symbol) const
{
    boost::mutex::scoped_lock lock(_exportedResourcesMutex);
    Exports::const_iterator it = _exportTable.find(symbol);
    return (it == _exportTable.end()) ? 0 : it->second;
}


void
SWFMovieDefinition::importResources(
        boost::intrusive_ptr<movie_definition> source, const Imports& imports)
{
    size_t importedSyms = 0;

    // Mutex scope.

    for (Imports::const_iterator i = imports.begin(), e = imports.end(); i != e;
            ++i) {
    
        size_t new_loading_frame = source->get_loading_frame();
        
        // 0.1 seconds.
        const size_t naptime = 100000;

        // Timeout after two seconds of NO frames progress
        const size_t timeout_ms = 2000000;
        const size_t def_timeout = timeout_ms / naptime; 

        size_t timeout = def_timeout;
        size_t loading_frame = (size_t)-1; // used to keep track of advancements

        const int id = i->first;
        const std::string& symbolName = i->second;

#ifdef DEBUG_EXPORTS
        log_debug("%s importing %s from %s", get_url(), symbolName,
                source->get_url());
#endif
        boost::uint16_t targetID;

        while(!(targetID = source->exportID(symbolName))) {
            
            // We checked last (or past-last) advertised frame. 
            // TODO: this check should really be for a parser
            //       process being active or not, as SWF
            //       might advertise less frames then actually
            //       found in it...
            //
            if (new_loading_frame >= source->get_frame_count()) {
                // Update of loading_frame is
                // really just for the latter debugging output
                loading_frame = new_loading_frame;
                break;
            }

            // There's more frames to parse, go ahead
            // TODO: this is still based on *advertised*
            //       number of frames, if SWF advertises
            //       more then actually found we'd be
            //       keep trying till timeout, see the
            //       other TODO above.

            // We made frame progress since last iteration
            // so sleep some and try again
            if (new_loading_frame != loading_frame) {
#ifdef DEBUG_EXPORTS
                log_debug(_("looking for exported resource: frame load "
                            "advancement (from %d to %d)"),
                    loading_frame, new_loading_frame);
#endif
                loading_frame = new_loading_frame;
                timeout = def_timeout+1;
            }
            else if (!--timeout) {
                // no progress since last run, and 
                // timeout reached: give up
                break;
            }

            // take a breath to give other threads more time to advance
            gnashSleep(naptime);

        }

        // timed out
        if (!timeout) {
            log_error("Timeout (%d milliseconds) seeking export "
                "symbol %s in movie %s. Frames loaded %d/%d",
                timeout_ms / 1000, symbolName,
                source->get_url(), loading_frame, source->get_frame_count());
            continue;
        }
        else {
            // eof
            //assert(loading_frame >= m_frame_count);
            log_error("No export symbol %s found in movie %s. "
                "Frames loaded %d/%d",
                symbolName, source->get_url(), loading_frame,
                source->get_frame_count());
        }

        boost::intrusive_ptr<SWF::DefinitionTag> res =
            source->getDefinitionTag(targetID);
        if (res) {
            // It's a character import.
            addDisplayObject(id, res.get());
            registerExport(symbolName, id);
            ++importedSyms;
            continue;
        }

        Font* f = source->get_font(id);
        if (f) {
            // It's a font import
            add_font(id, f);
            registerExport(symbolName, id);
            ++importedSyms;
            continue;
        }
        log_error(_("import error: could not find resource '%s' in "
                    "movie '%s'"), symbolName, source->get_url());
    }

    if (importedSyms) {
        _importSources.insert(source);
    }
}

} // namespace gnash
