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


#include "RunResources.h"
#include "DefineVideoStreamTag.h"
#include "VideoFrameTag.h"
#include "VideoDecoder.h"
#include "SWFStream.h" // for read()
#include "movie_definition.h"
#include "utility.h"
#include "smart_ptr.h"

#include <algorithm>

namespace gnash {
namespace SWF {


void
VideoFrameTag::loader(SWFStream& in, SWF::TagType tag, movie_definition& m,
        const RunResources& /*r*/)
{
    assert(tag == SWF::VIDEOFRAME);

    in.ensureBytes(2);
    boost::uint16_t id = in.read_u16();
    DefinitionTag* chdef = m.getDefinitionTag(id);

    if (!chdef)
    {
        IF_VERBOSE_MALFORMED_SWF(
            log_swferror(_("VideoFrame tag refers to unknown video "
                    "stream id %d"), id);
        );
        return;
    }

    DefineVideoStreamTag* vs = dynamic_cast<DefineVideoStreamTag*> (chdef);
    if (!vs)
    {
        IF_VERBOSE_MALFORMED_SWF(
        log_swferror(_("VideoFrame tag refers to a non-video DisplayObject "
                "%d (%s)"), id, typeName(*chdef));
        );
        return;
    }

	// TODO: skip if there's no MediaHandler registered ?

    const unsigned short padding = 8;

	in.ensureBytes(2);
	unsigned int frameNum = in.read_u16(); 
	
	const unsigned int dataLength = in.get_tag_end_position() - in.tell();

    // FIXME: catch bad_alloc
	boost::uint8_t* buffer = new boost::uint8_t[dataLength + padding]; 

	const size_t bytesRead = in.read(reinterpret_cast<char*>(buffer),
            dataLength);

    if (bytesRead < dataLength)
    {
        throw ParserException(_("Could not read enough bytes when parsing "
                                "VideoFrame tag. Perhaps we reached the "
                                "end of the stream!"));
    }	
	
    std::fill_n(buffer + bytesRead, padding, 0);

	using namespace media;

    std::auto_ptr<EncodedVideoFrame> frame(
            new EncodedVideoFrame(buffer, dataLength, frameNum));

	vs->addVideoFrameTag(frame);
}

} // namespace SWF
} // namespace gnash

