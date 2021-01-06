

#include "include.h"
#include "mem.h"

Buffer::Buffer()
{
  size = 0;
  memsize = 1024;
  data = (char *)malloc(memsize);
}

Buffer::~Buffer()
{
  mfree(data);
}

void Buffer::Write(char *tdata, int tsize)
{
  int new_memsize = memsize;
  while (size+tsize>new_memsize-16)
    new_memsize *= 2;
  if (memsize!=new_memsize)
  {
    memsize = new_memsize;
    data = (char *)realloc(data, memsize);
  }
  memcpy(data+size, tdata, tsize);
  size += tsize;
}

void Buffer::Clean()
{
  size = 0;
}

