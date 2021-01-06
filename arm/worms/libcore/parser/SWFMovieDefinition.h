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

// The SWFMovieDefinition is the 'root' definition of a SWF movie, including
// movies loaded into another SWF file. Each self-contained SWF file has exactly
// one SWFMovieDefinition.

#ifndef GNASH_SWF_MOVIE_DEFINITION_H
#define GNASH_SWF_MOVIE_DEFINITION_H

#ifdef HAVE_CONFIG_H
#include "gnashconfig.h" // for USE_SWFTREE
#endif

#include "smart_ptr.h" // GNASH_USE_GC
#include "GnashImageJpeg.h"
#include "movie_definition.h" // for inheritance
#include "DefinitionTag.h" // for boost::intrusive_ptr visibility of dtor
#include "StringPredicates.h" 
#include "SWFRect.h"
#include "GnashNumeric.h"
#include "GnashAlgorithm.h"

#include <boost/intrusive_ptr.hpp>
#include <vector>
#include <map> // for CharacterDictionary
#include <set> // for _importSources
#include <string>
#include <memory> // for auto_ptr
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/barrier.hpp>
#include <boost/scoped_ptr.hpp>

// Forward declarations
namespace gnash {
    class SWFMovieDefinition;
    class SWFStream;
    class movie_root;
    class MovieClip;
    class SWFMovie;
    class RunResources;
    class Font;
}

namespace gnash {

/// Helper class handling start and execution of a loading thread
class SWFMovieLoader
{
public:

    SWFMovieLoader(SWFMovieDefinition& md);

    ~SWFMovieLoader();

    /// Start loading thread.
    //
    /// The associated SWFMovieDefinition instance
    /// is expected to have already read the SWF
    /// header and applied a zlib adapter if needed.
    ///
    bool start();

    /// Return true if the loader thread was started
    bool started() const;

    /// Return true if called from the loader thread.
    bool isSelfThread() const;

private:

    SWFMovieDefinition& _movie_def;

    mutable boost::mutex _mutex;
    std::auto_ptr<boost::thread> _thread;

    // Barrier to ensure that _thread
    // is initialized before the loader thread
    // continues execution
    boost::barrier _barrier;

    /// Entry point for the actual thread
    static void execute(SWFMovieLoader& ml, SWFMovieDefinition* md);

};

/// The Characters dictionary associated with each SWF file.
//
/// This is a set of Characters defined by define tags and
/// getting assigned a unique ID. 
///
class CharacterDictionary
{
public:

    /// The container used by this dictionary
    //
    /// It contains pairs of 'int' and 'boost::intrusive_ptr<DefinitionTag>'
    ///
    typedef std::map<int, boost::intrusive_ptr<SWF::DefinitionTag> >
        CharacterContainer;

    typedef CharacterContainer::iterator CharacterIterator;

    typedef CharacterContainer::const_iterator CharacterConstIterator;

    /// Get the Character with the given id
    //
    /// returns a NULL if the id is unknown.
    ///
    boost::intrusive_ptr<SWF::DefinitionTag> getDisplayObject(int id) const;

    /// Add a Character assigning it the given id
    //
    /// replaces any existing DisplayObject with the same id
    ///
    void addDisplayObject(int id, boost::intrusive_ptr<SWF::DefinitionTag> c);
      
    /// Return an iterator to the first dictionary element
    CharacterIterator begin() { return _map.begin(); }

    /// Return a const_iterator to the first dictionary element
    CharacterConstIterator begin() const { return _map.begin(); }

    /// Return an iterator to one-past last dictionary element
    CharacterIterator end() { return _map.end(); }

    /// Return a const_iterator to one-past last dictionary element
    CharacterConstIterator end() const { return _map.end(); }

    friend std::ostream& operator<<(std::ostream& o,
            const CharacterDictionary& cd);

private:

    CharacterContainer _map;

};


/// Immutable definition of a SWF movie's contents.
//
/// It cannot be played directly, and does not hold
/// current state; for that you need to call createMovie()
/// to get a movie instance 
class SWFMovieDefinition : public movie_definition
{
public:

    /// Construct a SWF movie.
    //
    /// @param runResources      A RunResources containing information used for
    ///                          parsing.
    SWFMovieDefinition(const RunResources& runResources);

    ~SWFMovieDefinition();

    /// Return total number of frames advertised for the SWFMovie.
    size_t get_frame_count() const {
        return m_frame_count;
    }
    
    /// Return frame rate advertised for the SWFMovie.
    float get_frame_rate() const {
        return m_frame_rate;
    }
    
    /// Return dimensions of the SWFMovie.
    const SWFRect& get_frame_size() const {
        return m_frame_size;
    }

    size_t get_width_pixels() const {
        return std::ceil(twipsToPixels(m_frame_size.width()));
    }

    size_t get_height_pixels() const {
        return std::ceil(twipsToPixels(m_frame_size.height()));
    }

    /// Call this to inform callers that tags should be executed using AVM2
    void setAS3() {
        _as3 = true;
    }
    
    /// Check whether tags should be executed using AVM2
    bool isAS3() const {
        return _as3;
    }

    /// Return the advertised version for the SWFMovie.
    //
    /// This is stored and used in AS interpretation for some version-based
    /// behaviour.
    virtual int get_version() const { return m_version; }

    /// Get the number of fully loaded frames
    //
    /// The number returned is also the index
    /// of the frame currently being loaded/parsed,
    /// except when parsing finishes, in which case
    /// it an index to on-past-last frame.
    ///
    /// NOTE: this method locks _frames_loaded_mutex
    ///
    virtual size_t get_loading_frame() const;

    /// Get number of bytes loaded from input stream
    //
    /// NOTE: this method locks _bytes_loaded_mutex
    ///
    size_t get_bytes_loaded() const {
        boost::mutex::scoped_lock lock(_bytes_loaded_mutex);
        return _bytes_loaded;
    }

    /// Get total number of bytes as parsed from the SWF header
    size_t get_bytes_total() const {
        return m_file_length;
    }

    virtual void importResources(boost::intrusive_ptr<movie_definition> source,
            const Imports& imports);

    virtual void addDisplayObject(boost::uint16_t id, SWF::DefinitionTag* c);

    /// Return a DisplayObject from the dictionary
    SWF::DefinitionTag* getDefinitionTag(boost::uint16_t id) const;

    // See dox in movie_definition
    //
    // locks _namedFramesMutex
    bool get_labeled_frame(const std::string& label, size_t& frame_number)
        const;

    void add_font(int font_id, Font* f);

    Font* get_font(int font_id) const;

    Font* get_font(const std::string& name, bool bold, bool italic) const;

    // See dox in movie_definition.h
    CachedBitmap* getBitmap(int DisplayObject_id) const;

    // See dox in movie_definition.h
    void addBitmap(int DisplayObject_id, boost::intrusive_ptr<CachedBitmap> im);

    // See dox in movie_definition.h
    sound_sample* get_sound_sample(int DisplayObject_id) const;

    // See dox in movie_definition.h
    virtual void add_sound_sample(int DisplayObject_id, sound_sample* sam);

    // See dox in movie_definition.h
    virtual void set_loading_sound_stream_id(int id) {
        m_loading_sound_stream = id;
    }

    // See dox in movie_definition.h
    int get_loading_sound_stream_id() const {
        return m_loading_sound_stream;
    }

    // See dox in movie_definition.h
    void addControlTag(SWF::ControlTag* tag) {
        assert(tag);
        boost::mutex::scoped_lock lock(_frames_loaded_mutex);
        m_playlist[_frames_loaded].push_back(tag);
    }

    // See dox in movie_definition.h
    //
    // locks _namedFramesMutex and _frames_loaded_mutex
    //
    void add_frame_name(const std::string& name);

    /// Set an input object for later loading DefineBits
    /// images (JPEG images without the table info).
    void set_jpeg_loader(std::auto_ptr<JpegImageInput> j_in) {
        if (m_jpeg_in.get()) {
            /// There should be only one JPEGTABLES tag in an SWF (see: 
            /// http://www.m2osw.com/en/swf_alexref.html#tag_jpegtables)
            /// Discard any subsequent attempts to set the jpeg loader
            /// to avoid crashing on very malformed SWFs. (No conclusive tests
            /// for pp behaviour, though one version also crashes out on the
            /// malformed SWF that triggers this assert in Gnash).
            log_swferror(_("More than one JPEGTABLES tag found: not "
                        "resetting JPEG loader"));
            return;
        }
        m_jpeg_in = j_in;
    }

    // See dox in movie_definition.h
    JpegImageInput* get_jpeg_loader() const {
        return m_jpeg_in.get();
    }

    virtual const PlayList* getPlaylist(size_t frame_number) const {

#ifndef NDEBUG
        boost::mutex::scoped_lock lock(_frames_loaded_mutex);
        assert(frame_number <= _frames_loaded);
#endif

        PlayListMap::const_iterator it = m_playlist.find(frame_number);
        if ( it == m_playlist.end() ) return NULL;
        else return &(it->second);
    }

    /// Read the header of the SWF file
    //
    /// This function only reads the header of the SWF
    /// stream and assigns the movie an URL.
    /// Call completeLoad() to fire up the loader thread.
    ///
    /// @param in the IOChannel from which to read SWF
    /// @param url the url associated with the input
    /// @return false if SWF header could not be parsed
    bool readHeader(std::auto_ptr<IOChannel> in, const std::string& url);

    /// Complete load of the SWF file
    //
    /// This function completes parsing of the SWF stream
    /// engaging a separate thread.
    /// Make sure you called readHeader before this!
    ///
    /// @return false if the loading thread could not be started.
    bool completeLoad();

    /// \brief
    /// Ensure that frame number 'framenum' (1-based offset)
    /// has been loaded (load on demand).
    bool ensure_frame_loaded(size_t framenum) const;

    /// Read and parse all the SWF stream (blocking until load is finished)
    //
    /// This function uses a private TagLoadersTable
    /// to interpret specific tag types.
    /// Currently the TagLoadersTable in use is the
    /// TagLoadersTable singleton.
    void read_all_swf();

    /// Create an instance of this movie.
    //
    /// TOCHECK:
    /// Make sure you called completeLoad() before this
    /// function is invoked (calling read() will do that for you).
    ///
    /// TOCHECK:
    /// The _root reference of the newly created movie_root
    /// will be set to a newly created Movie.
    Movie* createMovie(Global_as& gl, DisplayObject* parent = 0);

    virtual DisplayObject* createDisplayObject(Global_as&, DisplayObject*)
        const {
        return 0;
    }

    virtual const std::string& get_url() const { return _url; }
    
    /// Get the id that corresponds to a symbol.
    //
    /// This function is thread-safe.
    //
    /// @param symbol   The symbol to lookup in the table.
    /// @return         The id corresponding to the passed symbol. 0 is not a
    ///                 valid id and signifies that the symbol was not (yet)
    ///                 exported.
    boost::uint16_t exportID(const std::string& symbol) const;
    
    /// Register a symbol to refer to a character id
    //
    /// This function is thread safe.
    //
    /// @param id       The id of the character to map to the symbol. NB: this
    ///                 must never be 0!
    /// @param symbol   The symbol to map to the id.
    void registerExport(const std::string& symbol, boost::uint16_t id);

    
#ifdef USE_SWFTREE

    // These methods attach the contents of the METADATA tag
    // to a movie_definition.
    virtual void storeDescriptiveMetadata(const std::string& data) {
        _metadata = data;
    }

    virtual const std::string& getDescriptiveMetadata() const {
        return _metadata;
    }    

#endif

private:

#ifdef USE_SWFTREE
    // For storing descriptive metadata (information only)
    std::string _metadata;
#endif

    /// Characters Dictionary
    CharacterDictionary    _dictionary;

    /// Mutex protecting _dictionary
    mutable boost::mutex _dictionaryMutex;

    typedef std::map<int, boost::intrusive_ptr<Font> > FontMap;
    FontMap m_fonts;

    typedef std::map<int, boost::intrusive_ptr<CachedBitmap> > Bitmaps;
    Bitmaps _bitmaps;

    typedef std::map<int, boost::intrusive_ptr<sound_sample> > SoundSampleMap;
    SoundSampleMap m_sound_samples;

    typedef std::map<size_t, PlayList> PlayListMap;

    /// Movie control events for each frame.
    PlayListMap m_playlist;

    /// 0-based frame #'s
    typedef std::map<std::string, size_t, StringNoCaseLessThan> NamedFrameMap;
    NamedFrameMap _namedFrames;

    // Mutex protecting access to _namedFrames
    mutable boost::mutex _namedFramesMutex;

    /// Allow mapping symbol to id case insensitively.
    typedef std::map<std::string, boost::uint16_t,
            StringNoCaseLessThan> Exports;

    /// A map of symbol to character id.
    Exports _exportTable;

    // Mutex protecting access to the export map.
    mutable boost::mutex _exportedResourcesMutex;

    /// Movies we import from; hold a ref on these,
    /// to keep them alive
    typedef std::vector<boost::intrusive_ptr<movie_definition> > ImportVect;
    ImportVect m_import_source_movies;

    SWFRect    m_frame_size;
    float    m_frame_rate;
    size_t    m_frame_count;
    int    m_version;

    /// Number of fully loaded frames
    size_t    _frames_loaded;

    /// A mutex protecting access to _frames_loaded
    //
    /// This is needed because the loader thread will
    /// increment this number, while the virtual machine
    /// thread will read it.
    mutable boost::mutex _frames_loaded_mutex;

    /// A semaphore to signal load of a specific frame
    mutable boost::condition _frame_reached_condition;

    /// Set this to trigger signaling of loaded frame
    //
    /// Make sure you _frames_loaded_mutex is locked
    /// when accessing this member !
    mutable size_t _waiting_for_frame;

    /// Number bytes loaded / parsed
    unsigned long _bytes_loaded;

    /// A mutex protecting access to _bytes_loaded
    //
    /// This is needed because the loader thread will
    /// increment this number, while the virtual machine
    /// thread will read it.
    mutable boost::mutex _bytes_loaded_mutex;

    int m_loading_sound_stream;

    boost::uint32_t m_file_length;

    std::auto_ptr<JpegImageInput> m_jpeg_in;

    std::string _url;

    /// Non transferable stream.
    boost::scoped_ptr<SWFStream> _str;

    std::auto_ptr<IOChannel> _in;

    /// swf end position (as read from header)
    size_t _swf_end_pos;

    /// asyncronous SWF loader and parser
    SWFMovieLoader _loader;

    /// \brief
    /// Increment loaded frames count, signaling frame reached condition if
    /// any thread is waiting for that. See ensure_frame_loaded().
    ///
    /// NOTE: this method locks _frames_loaded_mutex
    ///
    /// @return the new value of _frames_loaded
    virtual void incrementLoadedFrames();

    /// Set number of bytes loaded from input stream
    //
    /// NOTE: this method locks _bytes_loaded_mutex
    void setBytesLoaded(unsigned long bytes)
    {
        boost::mutex::scoped_lock lock(_bytes_loaded_mutex);
        _bytes_loaded=bytes;
    }

    /// A flag set to true when load cancelation is requested
    bool _loadingCanceled;

    /// Movies we import resources from
    std::set< boost::intrusive_ptr<movie_definition> > _importSources;

private:

    /// Used to retrieve the sound::sound_handler and other resources
    /// for parsing.
    //
    /// @todo   Add to base class? This would make it available for other
    ///         kinds of movies (e.g. FLV) and make it easier to initialize
    ///         movie_root with the same RunResources as its first definition.
    const RunResources& _runResources;

    bool _as3;

};

} // namespace gnash

#endif 
