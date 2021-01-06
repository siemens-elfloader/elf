
#include <spl/process.h>
#include <spl/thread.h>
#include <spl/coreevent.h>
#include <spl/waitcondition.h>



int _tid[25] = {-1};
int csz = 20;



int thread_main(void *d)
{
    printf("thread_main: pid: %d | tid: %d\n", getpid(), gettid());
    return 0;
}



int main()
{
    initUsart();
    printf(" [+] main: pid: %d\n", getpid());

    for(int i=0; i<csz; ++i) {
        _tid[i] = createThread(94, thread_main, 0, 1);
    }

    for(int i=0; i<csz; ++i)
        waitForThreadFinished(_tid[i], 0);

    printf("All threads finished\n");
    printf("Ram %d\n", GetFreeRamAvail());
    return 0;
}





