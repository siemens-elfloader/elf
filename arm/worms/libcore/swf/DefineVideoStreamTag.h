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

#ifndef GNASH_SWF_DEFINEVIDEOSTREAMTAG_H
#define GNASH_SWF_DEFINEVIDEOSTREAMTAG_H

#include "DefinitionTag.h"
#include "SWF.h"
#include "SWFRect.h" // for composition
#include "MediaParser.h" // for videoFrameType and videoCodecType enums

#include <boost/shared_array.hpp>
#include <boost/thread/mutex.hpp>

#include <memory> // for composition (auto_ptr)
#include <vector> // for composition

// Forward declarations
namespace gnash {
    class movie_definition;
    class SWFStream;
    class RunResources;
}

namespace gnash {

/// Class used to store data for the undecoded embedded video frames.
/// Contains the data, the data size and the type of the frame
class VideoData
{
public:
	VideoData(boost::shared_array<boost::uint8_t> data, boost::uint32_t size,
            media::videoFrameType ft)
		:
		videoData(data),
		dataSize(size),
		frameType(ft)
	{
	}

	~VideoData()
	{
	}

	boost::shared_array<boost::uint8_t> videoData;
	boost::uint32_t dataSize;
	media::videoFrameType frameType;
};

namespace SWF {

class DefineVideoStreamTag : public DefinitionTag
{
public:
	
    /// The undecoded video frames and its size, using the swf-frame number
    /// as key
	//
	/// Elements of this vector are owned by this instance, and will be deleted 
	/// at instance destruction time.
	///
	typedef std::vector<media::EncodedVideoFrame*> EmbeddedFrames;

	~DefineVideoStreamTag();

	DisplayObject* createDisplayObject(Global_as& gl, DisplayObject* parent)
        const;

	/// Read tag SWF::DEFINEVIDEOSTREAM 
	//
	/// The DisplayObject_id is assumed to have been already read by caller.
	///
	/// This function is allowed to be called only *once* for each
	/// instance of this class.
	///
	static void loader(SWFStream& in, SWF::TagType tag, movie_definition& m,
            const RunResources& r);


	/// Read tag SWF::VIDEOFRAME
	//
	/// The DisplayObject_id (used to find this instance in the DisplayObject's
    /// dictionary) is assumed to have been already read.
	///
	/// This function is allowed to be called zero or more times, as long
	/// as readDefineVideoStream was read before.
	void readDefineVideoFrame(SWFStream& in, SWF::TagType tag,
            movie_definition& m);

	/// Return local video bounds in twips
	const SWFRect&	bounds() const
	{
		return m_bound;
	}

	/// Get info about video embedded in this definition
	//
	/// May return NULL if there's no embedded video
	/// (ActionScript created definition - new Video)
	///
	media::VideoInfo* getVideoInfo() const { return _videoInfo.get(); }

	/// Get a slice of encoded video frames
	//
	/// @param from
	///	Frame number of first frame to get
	/// 
	/// @param to
	///	Frame number of last frame to get
	///
	/// @param ret
	///	The vector to push defined elements onto. Ownership of elements
	///	is left to callee.
	///
	/// NOTE: video definition can have gaps, so you may get NO frames
	///       if you ask for frames from 1 to 2 when available frames
	///	  are 0,3,6
	///
	void getEncodedFrameSlice(boost::uint32_t from, boost::uint32_t to,
		std::vector<media::EncodedVideoFrame*>& ret) const;

    
    void addVideoFrameTag(std::auto_ptr<media::EncodedVideoFrame> frame);

private:

	/// Construct a video stream definition with given ID
	//
	/// NOTE: for dynamically created definitions (ActionScript Video class
    ///       instances) you can use an id of -1. See DefinitionTag
    ///       constructor, as that's the one which will eventually get passed
    ///       the id.
    /// NOTE: What dynamically created definitions?
	DefineVideoStreamTag(SWFStream& in, boost::uint16_t id);

	void read(SWFStream& in);

	/// Reserved flags read from DEFINEVIDEOSTREAM tag
	boost::uint8_t m_reserved_flags;

	/// Flags read from DEFINEVIDEOSTREAM tag
	boost::uint8_t m_deblocking_flags;

	/// Smoothing flag, as read from DEFINEVIDEOSTREAM tag
	bool m_smoothing_flags;

	/// Frame in which the DEFINEVIDEOSTREAM was found
	//boost::uint16_t m_start_frame;

	/// Number of frames in the embedded video, as reported
	/// by the DEFINEVIDEOSTREAM tag
	///
	boost::uint16_t m_num_frames;

	/// Codec ID as read from DEFINEVIDEOSTREAM tag
	//
	/// 0: extern file
	/// 2: H.263
	/// 3: screen video (Flash 7+ only)
	/// 4: VP6
	/// 5: VP6 video with alpha
	///
	media::videoCodecType m_codec_id;

	/// Bounds of the video, as read from the DEFINEVIDEOSTREAM tag.
	SWFRect m_bound;

    // Mutable for locking in const member functions.
	mutable boost::mutex _video_mutex;
	
	EmbeddedFrames _video_frames;

	/// Width of the video
	boost::uint32_t _width;

	/// Height of the video
	boost::uint32_t _height;

	/// Info about embedded video
	//
	/// TODO: drop _width/_height/m_codec_id leaving all in this member
    /// instead ?
	std::auto_ptr<media::VideoInfo> _videoInfo;

};

} // namespace SWF
} // namespace gnash


#endif // GNASH_VIDEO_STREAM_DEF_H
