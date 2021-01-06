
#include <spl/process.h>
#include <spl/coreevent.h>
#include <spl/csm.h>
#include <spl/thread.h>

char data[20] = {0x34, 0x34, 0x34, 0x34, 0x34};

int thread_handle(void *d)
{
    //((void (*)())data)();
    kill(getpid(), 0);
    return 0;
}

__inl
int __open(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber)
__def( 10, int, cFileName, iFileFlags, iFileMode, ErrorNumber)

int main()
{
    initUsart();
    printf(" [+] main: pid: %d\n", getpid());

    createThread(96, thread_handle, 0, 1);
    //((void (*)())data)();
    /*int fd =  __open("4:\\file", A_Create | A_ReadWrite, P_READ | P_WRITE, 0);

    _close(fd, 0);*/
    processEvents();
    return 0;
}





