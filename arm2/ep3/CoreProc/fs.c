
#include <spl/fs.h>
#include <spl/processbridge.h>
#include <spl/process.h>


#include <fcntl.h>
#include <swilib.h>
#include <errno.h>



static inline int getfilesize(const char *file)
{
    FSTATS ft;
    if(sync_GetFileStats(file, &ft, 0)  == -1) return -1;
    return ft.size;
}


static int __open(const char *file, int flags, ...)
{
    int flag = 0, mode = P_READ, i = 0, sgold = (isnewSGold() == 0), fsz = 0;
    unsigned int err;

    /* костыль для сименс-криво-апи, в режиме трункейт на существующем нулевом файле */
    /* опен напроч отказывается открывать файл */
    fsz = getfilesize(file);

    /* только запись */
    if( flags & O_WRONLY ) flag |= A_WriteOnly;

    //Если MMC и SGold-платформа, то чтение/запись в любом случае
    if( sgold && file[0] == '4' ) flag = A_ReadWrite;

    /* чтение/запись */
    //Если MMC и SGold-платформа, то ничего нужного не затрёт
    if( flags & O_RDWR ) flag |= A_ReadWrite;

    /* создать файл если не существует */
    if( flags & O_CREAT ) flag |= A_Create;

    /* хз :-D */
    if( flags & O_EXCL ) flag |= A_Exclusive;

    /* очистить файл */
    if( flags & O_TRUNC && fsz > 0 ) flag |= A_Truncate;

    /* записывать в конец */
    if( flags & O_APPEND ) flag |= A_Append;

    if( flag & A_WriteOnly || flag & A_ReadWrite ) mode |= P_WRITE;

    if( !(flags & A_TXT) )
        flag |= A_BIN;

    i = sync_open(file, flag, mode, &err);
    return i;
}



static ssize_t __read(int fd, void *data, size_t size)
{
    idStream *s = getStreamData(getpid(), fd);
    if(!s) {
        return -1;
    }

    return sync_read(s->fd, data, size, 0);
}


static ssize_t __write(int fd, const void *data, size_t size)
{
    idStream *s = getStreamData(getpid(), fd);
    if(!s) {
        return -1;
    }

    return sync_write(s->fd, data, size, 0);
}


static int __close(int fd)
{
    idStream *s = getStreamData(getpid(), fd);
    if(!s) {
        return -1;
    }

    return sync_close(s->fd, 0);
}


static int __flush(int fd)
{
    idStream *s = getStreamData(getpid(), fd);
    if(!s) {
        return -1;
    }

    return sync_flush(s->fd, 0);
}


static off_t __lseek(int fd, off_t offset, int whence)
{
    idStream *s = getStreamData(getpid(), fd);
    if(!s) {
        return -1;
    }

    return sync_lseek(s->fd, offset, whence, 0, 0);
}



int open(const char *file, int flags, ...)
{
    int stream = open_fd();
    if(stream < 0)
        return stream;

    int fd = __open(file, flags);
    if(fd < 0) {
        close_fd(stream);
        return fd;
    }

    idStream *s = getStreamData(getpid(), stream);
    if(!s) {
        close_fd(stream);
        sync_close(fd, 0);
        return fd;
    }

    s->fd = fd;
    s->type = FS_STREAM;
    s->mode = flags;
    s->read = __read;
    s->write = __write;
    s->close = __close;
    s->flush = __flush;
    s->lseek = __lseek;

    return stream;
}

















