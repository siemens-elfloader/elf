
#include <spl/process.h>
#include <spl/processbridge.h>
#include <spl/coreevent.h>
#include <spl/thread.h>
#include <spl/mutex.h>
#include <spl/waitcondition.h>


#define MAX_TEST 256
CoreMutex mutexses[MAX_TEST];
int mtid = -1;


int thread_main(void *d)
{
    printf("Thread start\n");
    int destroyed = 0;
    for(int i=0; i<MAX_TEST; ++i)
        destroyed += destroyMutex(&mutexses[i]) < 0? 0 : 1;

    printf("destroyed %d mutexes\n", destroyed);
    return 0;
}


int main()
{
    initUsart();

    mtid = createThread(96, thread_main, 0, 1);
    waitForThreadStarted(mtid);
    printf("Thread started\n");

    for(int i=0; i<MAX_TEST; ++i)
        createMutex(&mutexses[i]);

    waitForThreadFinished(mtid, 0);
    printf("Ram: %d\n", GetFreeRamAvail());
    return 0;
}





