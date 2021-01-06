
#include <swilib.h>
#include <stdlib.h>
#include <spl/static_data_base.h>
#include <spl/process.h>
#include <spl/waitcondition.h>
#include <spl/io.h>
#include <fcntl.h>
#include <spl/pipe.h>


typedef struct
{
    int id;
    char *memory;
    int offset;
    int seek;
    int size;
    int flags;

    CoreMutex locker;
    int ready_read_wid;
    int ready_write_wid;
    int fully_flushed_wid;
    int fully_empty_wid;
} Spipe;

#define MAX_PIPE_ID 256
declare_static_db(Spipe, pipe, MAX_PIPE_ID)



int closePipe(int pipe);
int writePipe(int pipe, const void *data, size_t size);
int readPipe(int pipe, void *data, size_t size);

ssize_t __pread(int fd, void *data, size_t size) {
    idStream *is = getStreamData(getpid(), fd);
    if(!is)
        return -1;
    return readPipe(is->fd, data, size);
}


ssize_t __pwrite(int fd, const void *data, size_t size) {
    idStream *is = getStreamData(getpid(), fd);
    if(!is)
        return -1;
    return writePipe(is->fd, data, size);
}


off_t __plseek(int fd, off_t offset, int whence) {
    idStream *is = getStreamData(getpid(), fd);
    if(!is)
        return -1;

    UNUSED(offset);
    UNUSED(whence);
    return /*lseek(is->fd, offset, whence)*/-1;
}


int __pflush(int fd) {
    idStream *is = getStreamData(getpid(), fd);
    if(!is)
        return -1;
    return 0;
}


int __pclose(int fd) {
    idStream *is = getStreamData(getpid(), fd);
    if(!is)
        return -1;
    return closePipe(is->fd);
}


int createPipe(int size, int flags)
{
    Spipe *p = newSpipeData();
    if(!p)
        return -1;
    int pid = getpid();

    enterProcessCriticalCode(pid);
    int fd = open_fd();
    if(fd < 0)
        return fd;
    idStream *is = getStreamData(getpid(), fd);

    createMutex(&p->locker);
    p->memory = malloc(size+4);
    p->seek = 0;
    p->offset = 0;
    p->size = size;
    p->ready_read_wid = createAdvWaitCond("waiter", 0);
    p->ready_write_wid = createAdvWaitCond("waiter", 0);
    p->fully_flushed_wid = createAdvWaitCond("waiter", 0);
    p->fully_empty_wid = createAdvWaitCond("waiter", 0);
    p->flags = flags;

    is->fd = p->id;
    is->type = PIPE_STREAM;
    is->mode = O_RDWR;
    is->pid = pid;
    is->read = __pread;
    is->write = __pwrite;
    is->flush = __pflush;
    is->lseek = __plseek;
    is->close = __pclose;

    wakeOneWaitCond(p->ready_write_wid);
    leaveProcessCriticalCode(pid);

    return fd;
}


int closePipe(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    int pid = getpid();

    enterProcessCriticalCode(pid);
    // лочим мютекс, блокируем io операции над пайпом
    lockMutex(&p->locker);
    free(p->memory);
    p->memory = 0;

    destroyWaitCond(p->ready_read_wid);
    destroyWaitCond(p->ready_write_wid);
    destroyWaitCond(p->fully_flushed_wid);
    destroyWaitCond(p->fully_empty_wid);
    unlockMutex(&p->locker);
    destroyMutex(&p->locker);

    freeSpipeData(p->id);
    leaveProcessCriticalCode(pid);

    return 0;
}


static int offsetPipeFlush(Spipe *p)
{
    if(p->offset > 0 && p->seek > 0)
    {
        p->seek -= p->offset;

        if(p->seek > 0)
            memmove(p->memory, p->memory+p->offset, p->seek);
        p->offset = 0;
        return 0;
    }

    return 0;
}



int writePipeUnlocked(int pipe, const void *data, size_t size)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p || !p->memory)
        return -1;

    offsetPipeFlush(p);
    int write_sz = (int)p->size - p->seek < (int)size? (int)p->size - p->seek : (int)size;

    if(write_sz > 0) {
        memcpy(p->memory + p->seek, data, write_sz);
        p->seek += write_sz;

        if(p->seek == p->size) {
            wakeAllWaitConds(p->fully_flushed_wid);
        }
    }

    return write_sz > 0? write_sz : -1;
}


int writePipe(int pipe, const void *data, size_t size)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    if( p->flags & PIPE_WAIT_FOR_READY_WRITE ) {
        waitForPipeReadyWrite(pipe);
    }

    lockMutex(&p->locker);
    int r = writePipeUnlocked(pipe, data, size);
    unlockMutex(&p->locker);

    if(r > 0)
        wakeOneWaitCond(p->ready_read_wid);
    return r;
}


int readPipeUnlocked(int pipe, void *data, size_t size)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p || !p->memory)
        return -1;

    int read_sz = p->seek-p->offset < (int)size? p->seek-p->offset : (int)size;

    if(read_sz > 0) {
        memcpy(data, p->memory + p->offset, read_sz);
        p->offset += read_sz;
        if(p->offset == p->size || p->seek == 0)
            wakeOneWaitCond(p->fully_empty_wid);
        wakeOneWaitCond(p->ready_write_wid);
    }

    return read_sz > 0? read_sz : -1;
}


int readPipe(int pipe, void *data, size_t size)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    if( p->flags & PIPE_WAIT_FOR_READY_READ ) {
        waitForPipeReadyRead(pipe);
    }

    lockMutex(&p->locker);
    int r = readPipeUnlocked(pipe, data, size);
    unlockMutex(&p->locker);

    return r;
}


int waitForPipeFullyFlushed(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    if(p->seek - p->offset < p->size) {
        waitCondition(p->fully_flushed_wid);
    }

    return p->seek;
}


int waitForPipeFullyEmpty(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    waitCondition(p->fully_empty_wid);
    return p->seek - p->offset;
}


int availablePipeData(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    return p->seek - p->offset;
}


int waitForPipeReadyRead(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    waitCondition(p->ready_read_wid);
    return p->seek - p->offset;
}


int waitForPipeReadyWrite(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    waitCondition(p->ready_write_wid);
    return p->seek - p->offset;
}


int pipeBufferSize(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    return p->size;
}


int pipeStreamFlags(int pipe)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    return p->flags;
}


int setPipeStreamFlags(int pipe, int flags)
{
    Spipe *p = checkSpipeData(pipe);
    if(!p)
        return -1;

    return p->flags = flags;
}

