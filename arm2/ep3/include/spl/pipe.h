
#ifndef __PIPE_H__
#define __PIPE_H__


enum {

    PIPE_WAIT_FOR_READY_READ = (1 << 1),
    PIPE_WAIT_FOR_READY_WRITE = (1 << 2)
};


/** NOTE
  *  createPipe returning stream fd, not pipe fd.
  *  For use pipe functions, use getStreamHandle(fd) for
  *  getting pipe stream

*/

int createPipe(int size, int flags);


/** NOTE
  *  use close, write, read
int closePipe(int pipe);
int writePipe(int pipe, const void *data, size_t size);
int readPipe(int pipe, void *data, size_t size);
*/

int waitForPipeFullyFlushed(int pipe);
int waitForPipeFullyEmpty(int pipe);
int availablePipeData(int pipe);
int pipeBufferSize(int pipe);
int waitForPipeReadyWrite(int pipe);
int waitForPipeReadyRead(int pipe);
int pipeStreamFlags(int pipe);
int setPipeStreamFlags(int pipe, int flags);

#endif
