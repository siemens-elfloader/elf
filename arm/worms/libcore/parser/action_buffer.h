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

#ifndef GNASH_ACTION_BUFFER_H
#define GNASH_ACTION_BUFFER_H

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/cstdint.hpp> // for boost::uint8_t
#include <vector> // for composition

#include "GnashException.h"
#include "log.h" // For gettext macro

// Forward declarations
namespace gnash {
	class as_environment;
	class as_value;
	class movie_definition;
	class SWFStream; // for read signature
}


namespace gnash {

class ActionExec;

double convert_double_wacky(const void *p);

/// A code segment.
//
/// This currently holds the actions in a memory
/// buffer, but I'm workin toward making this unneeded
/// so to eventually use a gnash::stream directly and
/// avoid full loads. (not before profiling!).
//
/// Good, would make jumping to other tags possible.
class action_buffer : boost::noncopyable
{
public:
	friend class ActionExec;

	action_buffer(const movie_definition& md);

	/// Read action bytes from input stream up to but not including endPos
	//
	/// @param endPos
	///	One past last valid-to-read byte position.
	///	Make sure it's > then in.tell() and
	///	<= in.get_tag_end_position() or an assertion will
	///	fail.
	///
	void read(SWFStream& in, unsigned long endPos);

	size_t size() const { return m_buffer.size(); }

	boost::uint8_t operator[] (size_t off) const
	{
		if (off >= m_buffer.size()) {
		    throw ActionParserException (_("Attempt to read outside "
		    		    "action buffer"));
		}
		return m_buffer[off];
	}

	/// Disassemble instruction at given offset and return as a string
	std::string disasm(size_t pc) const;

	/// Get a null-terminated string from given offset
	//
	/// Useful to hide complexity of underlying buffer access.
	///
	const char* read_string(size_t pc) const
	{
		assert(pc <= m_buffer.size() );
        if (pc == m_buffer.size())
        {
            throw ActionParserException(_("Asked to read string when only "
                "1 byte remains in the buffer"));
        }
		return reinterpret_cast<const char*>(&m_buffer[pc]);
	}

    /// Get a pointer to the current instruction within the code
	const unsigned char* getFramePointer(size_t pc) const
	{
	    assert (pc < m_buffer.size());
		return reinterpret_cast<const unsigned char*>(&m_buffer.at(pc));
	}

	/// Get a signed integer value from given offset
	//
	/// Useful to hide complexity of underlying buffer access.
	///
	boost::int16_t read_int16(size_t pc) const
	{
	    if (pc + 1 >= m_buffer.size()) {
	        throw ActionParserException(_("Attempt to read outside action buffer limits"));
	    }
		boost::int16_t ret = (m_buffer[pc] | (m_buffer[pc + 1] << 8));
		return ret;
	}

	/// Get an unsigned short integer value from given offset
    /// read_int16 should check buffer boundaries.
	boost::uint16_t read_uint16(size_t pc) const
	{
		return static_cast<boost::uint16_t>(read_int16(pc));
	}

	/// Read a 32-bit integer starting at given offset.
	//
	/// Useful to hide complexity of underlying buffer access.
	///
	boost::int32_t read_int32(size_t pc) const
	{
		if (pc + 3 >= m_buffer.size()) {
	        throw ActionParserException(_("Attempt to read outside action buffer limits"));
	    }
	    
		boost::int32_t	val = m_buffer[pc]
		      | (m_buffer[pc + 1] << 8)
		      | (m_buffer[pc + 2] << 16)
		      | (m_buffer[pc + 3] << 24);
		return val;
	}

	/// Read a little-endian 32-bit float starting at given offset
	//
	/// Useful to hide complexity of underlying buffer access.
	///
	float read_float_little(size_t pc) const;

	/// Read a 64-bit double starting at given offset.
	//
	/// wacky format: 45670123
	/// Useful to hide complexity of underlying buffer access.
	///
	double read_double_wacky(size_t pc) const;

	/// Return number of entries in the constant pool
	size_t dictionary_size() const
	{
		return m_dictionary.size();
	}

	/// Return a value from the constant pool
	const char* dictionary_get(size_t n) const
	{
	    assert (n < m_dictionary.size());
		return m_dictionary[n];
	}

	/// Interpret the SWF::ACTION_CONSTANTPOOL opcode. 
	//
	/// Don't read stop_pc or later. 
	///
	/// A dictionary is a table of indexed strings to be
	/// used in action blocks to reduce their size.
	///
	/// NOTE: Normally the dictionary is declared as the first
	/// action in an action buffer, but I've seen what looks like
	/// some form of copy protection that amounts to:
	///
	/// |start of action buffer|
	///          push true
	///          branch_if_true label
	///          decl_dict   [0]   // this is never executed, but has lots of orphan data declared in the opcode
	/// label:   // (embedded inside the previous opcode; looks like an invalid jump)
	///          ... "protected" code here, including the real decl_dict opcode ...
	///          <end of the dummy decl_dict [0] opcode>
	///
	/// Note also that the dictionary may be overridden multiple times.
	/// See testsuite/misc-swfmill.all/dict_override.xml
	///
	void process_decl_dict(size_t start_pc, size_t stop_pc) const;

    /// Return url of the SWF this action block was found in
	const std::string& getDefinitionURL() const;

    /// Return version of the SWF this action block was found in
	int getDefinitionVersion() const;

    const movie_definition& getMovieDefinition() const {
        return _src;
    }

private:

	/// the code itself, as read from the SWF
	std::vector<boost::uint8_t> m_buffer;

	/// The dictionary
	mutable std::vector<const char*> m_dictionary;

	/// FIXME: move to ActionExec
	mutable int m_decl_dict_processed_at;

	/// The movie_definition containing this action buffer
	//
	/// This pointer will be used to determine domain-based
	/// permissions to grant to the action code.
	/// 
	const movie_definition& _src;
};


}	// end namespace gnash


#endif // GNASH_ACTION_BUFFER_H


// Local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
