
#ifndef __STREAM_H__
#define __STREAM_H__

#include <string.h>

#define INET_STREAM 0x01
#define FS_STREAM 0x02

int open_stream(int type, const char *location);
int seek_stream(uint32_t to, int type);
int read_stream(void *data, size_t size);
int size_stream();
void close_stream();
int data_stream_bufferized();

#endif
