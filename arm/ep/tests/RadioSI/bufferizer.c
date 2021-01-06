
#include <swilib.h>
#include <spl/socket.h>
#include <spl/thread.h>
#include <spl/io.h>
#include <spl/pipe.h>
#include "bufferizer.h"


/**
    * Буфферизатор работающий в фоне, отдельным тредом, через пайп
*/

extern int state_bufferizing;
extern char buffer_status[56];

static int bufferizer_handle(void *d)
{
    struct BufferizedStream *i = d;
    int pipe_fd = i->pipe_fd;
    int fd = i->fd;
    int pfd = getStreamHandle(pipe_fd);
    size_t size = i->size;
    char data[2048+64];
    char *last_off = 0;
    int last_size = 0;

    i->status = 1;
    while(1) {

        //printf("In buffer available %d\n", availablePipeData(pfd));
        if(availablePipeData(pfd) >= (int)size) {
            waitForPipeReadyWrite(pfd);
        }

        int can_write = size - availablePipeData(pfd);
        if(can_write < 1)
            continue;

        if(can_write > (int)sizeof(data))
            can_write = sizeof(data);

        int sz = read(fd, data, can_write);
        if(sz < 1) {
            void report_bug(const char *text);
            report_bug("Bufferizer report error. No socket stream data available. ");
            break;
        }

        data[sz] = 0;
        write(pipe_fd, data, sz);

        if(state_bufferizing) {
            sprintf(buffer_status, "Bufferizing ... %d kb\n", availablePipeData(pfd)/1024);
            REDRAW();
        }
    }

    i->status = -1;
    printf("Bufferizer stoped\n");

    int flags = pipeStreamFlags(pfd);
    if(flags & PIPE_WAIT_FOR_READY_READ)
        flags &= ~PIPE_WAIT_FOR_READY_READ;

    setPipeStreamFlags(pfd, flags);
}


struct BufferizedStream *createBufferizedStream(int pipe_fd, int fd, int start)
{
    if( pipeBufferSize(getStreamHandle(pipe_fd)) < 2048 ) {
        //ShowMSG(1, (int)"pipe size < 2048 bytes\n");
        return 0;
    }

    struct BufferizedStream *i = malloc(sizeof *i);
    i->pipe_fd = pipe_fd;
    i->fd = fd;
    i->size = pipeBufferSize(getStreamHandle(pipe_fd));
    i->status = 0;

    TaskConf conf;
    initTaskConf(&conf);
    conf.prio = 100;
    conf.stack_size = 0x1000;
    conf.is_stack_freeable = 1;

    if( (i->thread = createConfigurableThread(&conf, bufferizer_handle, i, start)) < 0) {
        free(i);
        char d[128];
        sprintf(d, "Failed to create bufferized stream %d", i->thread);
        //ShowMSG(1, (int)d);
        return 0;
    }

    i->dt_id = addProcessDtors(getpid(), (void (*)(void*, void*))destroyBufferizedStream, i, 0);

    return i;
}


int destroyBufferizedStream(struct BufferizedStream *i)
{
    if(!i) return -1;

    eraseProcessDtor(getpid(), i->dt_id);
    destroyThread(i->thread);
    free(i);
}


int activateBufferizedStream(struct BufferizedStream *i)
{
    if(!i) return -1;
    return resumeThread(i->thread);
}
