
#ifndef __BUFFERIZER_H__
#define __BUFFERIZER_H__





struct BufferizedStream
{
    int pipe_fd, fd;
    size_t size;
    int status;
    int thread;
    int dt_id;
};


struct BufferizedStream *createBufferizedStream(int pipe_fd, int fd, int start);
int destroyBufferizedStream(struct BufferizedStream *i);
int activateBufferizedStream(struct BufferizedStream *i);


#endif

