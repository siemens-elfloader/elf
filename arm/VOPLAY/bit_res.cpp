/* bit_res.cpp

	Implementation of Bit Reservoir for Layer III

   Adapted from the public c code by Jeff Tsay. */

#include "all.h"
#include "bit_res.h"

Bit_Reserve::Bit_Reserve()
{
	uint32 shifted_one = 1;

	offset       = 0;
   totbit		 = 0;
   buf_byte_idx = 0;
	buf          = new uint32[BUFSIZE];
	buf_bit_idx  = 8;
	putmask      = new uint32[32];

   putmask[0] = 0;

   for (int32 i=1; i<32; i++)
   {
   	putmask[i] = putmask[i-1] + shifted_one;
      shifted_one <<= 1;
   }
}

Bit_Reserve::~Bit_Reserve ()
{
	delete [] putmask;
	delete [] buf;
}

uint32 Bit_Reserve::hgetbits(uint32 N)
// read N bits from the bit stream
{
   totbit += N;

   uint32 val = 0;
   int32 j = N;

   while (j > 0) {

	  if (buf_bit_idx == 0) {
   	  buf_bit_idx = 8;
	     buf_byte_idx++;
/*	if (buf_byte_idx > offset)
	  { printf("Buffer overflow !!\n");exit(3); } */
     }

	  int32 k = (j < buf_bit_idx) ? j : buf_bit_idx;

   // BUFSIZE = 4096 = 2^12, so
   // buf_byte_idx%BUFSIZE == buf_byte_idx & 0xfff
     int32 tmp = buf[buf_byte_idx & 0xfff] & putmask[buf_bit_idx];
     buf_bit_idx -= k;
	  tmp = tmp >> buf_bit_idx;
     j -=k;
     val |= tmp << j;
   }
   return val;
}

uint32 Bit_Reserve::hget1bit()
// read 1 bit from the bit stream
{
   uint32 val;

   totbit++;

	if (buf_bit_idx == 0) {
     buf_bit_idx = 8;
	  buf_byte_idx++;
   }

   // BUFSIZE = 4096 = 2^12, so
   // buf_byte_idx%BUFSIZE == buf_byte_idx & 0xfff
   val = buf[buf_byte_idx & 0xfff] & putmask[buf_bit_idx];
   buf_bit_idx--;
	val = val >> buf_bit_idx;

   return val;
}

void Bit_Reserve::hputbuf(int32 val)
// write 8 bits into the bit stream
{
   buf[offset] = val;
   offset = (offset + 1) & 0xfff;
}

void Bit_Reserve::rewindNbits(int32 N)
{
	totbit -= N;
	buf_bit_idx += N;
	while(buf_bit_idx >= 8) {
   	buf_bit_idx -= 8;
		buf_byte_idx--;
	}
}

void Bit_Reserve::rewindNbytes(int32 N)
{
   totbit -= (N << 3);
	buf_byte_idx -= N;
}
