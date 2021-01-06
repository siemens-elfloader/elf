#include <swilib.h>
#include <spl/process.h>
#include <spl/memctl.h>
#include <spl/resctl.h>
#include <spl/corearray.h>
#include <spl/io.h>
#include <spl/mutex.h>

/* TODO
 * Протестировать.
 */

typedef struct
{
    CoreMutex mutex;
    CoreArray array;
}ioProcessStreamData;

static int ioCtlID = -1;


static void *onCreate(int _pid)
{
    UNUSED(_pid);

    ioProcessStreamData *data = malloc(sizeof(ioProcessStreamData));
    memset(data, 0, sizeof(ioProcessStreamData));
    corearray_init(&data->array, (void*)0);
    createMutex(&data->mutex);
    return data;
}


static void onClose(ResCtlData *_data)
{
    //printf("mem: onClose %X\n", data);
    if(!_data)
        return;

    ioProcessStreamData *data = _data->data;

    CoreArray *array = &data->array;
    int pid = getpid();
    int id, it = 0;
    idStream *is;

    corearray_foreach(idStream *, is, array, it) {
        id = is->id;
        //corearray_store_cell(array, it, (void*)0);
        if(id > -1) {
            printf("\033[1m\033[31mpid: %d - close leak fd: %d\033[0m\n", pid, id);
            close(id);
        }
    }

    corearray_release(array);
    destroyMutex(&data->mutex);
    free(data);
}


void fdsInit()
{
    ioCtlID = createResCtl();
    setupResCtl(ioCtlID, onCreate, onClose);
}

void fdsFini()
{
    destroyResCtl(ioCtlID);
}


static void stub(){}
static idStream *create_process_fd(int pid)
{
    ResCtlData *res = dataOfResCtl(pid, ioCtlID);
    if(!res || !res->data)
        return 0;

    ioProcessStreamData *data = res->data;

    CoreArray *array = &data->array;
    int it = 0;
    idStream *is;
    lockMutex(&data->mutex);
    if(array->size > 0) {
        corearray_foreach(idStream *, is, array, it) {
            if(!is)
            {
                printf("IO: %d Founded empty cell %d\n", array->size, it);
setup:
                is = malloc(sizeof *is);
                is->id = it;

                is->read = (ssize_t (*)(int, void*, size_t))stub;
                is->write = (ssize_t (*)(int, const void*, size_t))stub;
                is->close = (int (*)(int))stub;
                is->flush = (int (*)(int))stub;
                is->lseek = (off_t (*)(int, off_t, int))stub;
                is->pid = getpid();
                corearray_store_cell(array, it, is);
                unlockMutex(&data->mutex);
                return is;
            }
        }
    }

    it = corearray_push_back(array, 0);
    printf("corearray_push_back: %d\n", it);
    if(it < 0)
        return 0;
    goto setup;

    return is; /* never been */
}


idStream *getStreamData(int pid, int fd)
{
    ResCtlData *res = dataOfResCtl(pid, ioCtlID);
    if(!res || !res->data)
        return 0;

    ioProcessStreamData *data = res->data;
    idStream *s = corearray_cell(&data->array, fd);
    return s;
}


int open_fd()
{
    idStream *is = create_process_fd(getpid());
    if(!is)
        return -1;

    return is->id;
}


int close_fd(int fd)
{
    ResCtlData *res = dataOfResCtl(getpid(), ioCtlID);
    if(!res || !res->data)
        return 0;

    ioProcessStreamData *data = res->data;
    idStream *s = corearray_cell(&data->array, fd);
    if(!s)
        return -1;

    printf("close_fd(%d)\n", fd);

    int r = s->close? s->close(fd) : 0;
    s->id = -1;
    free(s);

    corearray_store_cell(&data->array, fd, 0);
    printf("close_fd(%d) done\n", fd);
    return r;
}



ssize_t read(int fd, void *buf, size_t len)
{
    idStream *s = getStreamData(getpid(), fd);
    if(!s)
        return -1;

    return s->read(fd, buf, len);
}



ssize_t write(int fd, const void *buf, size_t len)
{
    idStream *s = getStreamData(getpid(), fd);

    if(!s)
        return -1;

    return s->write(fd, buf, len);
}



int close(int fd)
{
    idStream *s = getStreamData(getpid(), fd);

    if(!s)
        return -1;

    return close_fd(fd);
}


int flush(int fd)
{
    idStream *s = getStreamData(getpid(), fd);

    if(!s)
        return -1;

    return s->flush(fd);
}


off_t lseek(int fd, off_t offset, int whence)
{
    idStream *s = getStreamData(getpid(), fd);

    if(!s)
        return -1;

    return s->lseek(fd, offset, whence);
}




