/* bit_res.h

	Declarations for Bit Reservoir for Layer III

   Adapted from the public c code by Jeff Tsay. */

#ifndef BIT_RES_H
#define BIT_RES_H

#include "all.h"

#define BUFSIZE 4096

class Bit_Reserve {

public:

	Bit_Reserve();
	~Bit_Reserve();

	uint32 hsstell() const { return(totbit); }
	uint32 hgetbits(uint32 N);
	uint32 hget1bit();
	void hputbuf(int32 val);

	void rewindNbits(int32 N);
	void rewindNbytes(int32 N);

private:

	uint32 offset, totbit, buf_byte_idx;
	uint32 *buf;
	uint32 buf_bit_idx;
   uint32 *putmask;

};

#endif
