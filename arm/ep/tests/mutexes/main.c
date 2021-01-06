
#include <spl/process.h>
#include <spl/processbridge.h>
#include <spl/coreevent.h>
#include <spl/thread.h>
#include <spl/mutex.h>
#include <spl/waitcondition.h>



CoreMutex mutex;
char dd[128] = "";
int th_cnt = 3;
int wid1 = -1;
int mtid1 = -1, mtid2 = -1, mtid3 = -1;


int thread_main1(void *d)
{
    printf("thread_main1\n");

    lockMutex(&mutex);
    NU_Sleep(100); // если даже мы будем спать, все равно второй тред не влезет перд нами *trollface*
    printf("1: tid: %d\n", gettid());
    unlockMutex(&mutex);

    wakeOneWaitCond(wid1);
    return 0;
}


int thread_main2(void *d)
{
    printf("thread_main2\n");

    lockMutex(&mutex);
    printf("2: tid: %d\n", gettid());
    unlockMutex(&mutex);

    wakeOneWaitCond(wid1);
    return 0;
}


int thread_main3(void *d)
{
    printf("thread_main3\n");
    //NU_Sleep(15); // ≈сли баласт не сбросить - мы опоздаем(

    if( !tryLockMutex(&mutex) ) {
        printf("had!\n");
        printf("3: tid: %d\n", gettid());
        unlockMutex(&mutex);
    } else {
        printf("late...\n");
    }

    wakeOneWaitCond(wid1);
    return 0;
}



int main()
{
    initUsart();

    createMutex(&mutex);
    wid1 = createWaitCond("wait");

    printf("pid: %d\n", getpid());

    mtid3 = createThread(95, thread_main3, 0, 1); // создадим тред с трулоком

    lockMutex(&mutex); // лочим мютекс
    mtid1 = createThread(95, thread_main1, 0, 1);
    mtid2 = createThread(95, thread_main2, 0, 1);

    printf("My Firts!\n"); // ... но эта запись будет перва€
    unlockMutex(&mutex);

    // Wait for exit
    waitCondition(wid1);
    printf("Thread destroyed 1\n");

    waitCondition(wid1);
    printf("Thread destroyed 2\n");

    waitCondition(wid1);
    printf("Thread destroyed 3\n");

    destroyThread(mtid1);
    destroyThread(mtid2);
    destroyThread(mtid3);
    destroyMutex(&mutex);
    destroyWaitCond(wid1);
    printf("Ram: %d\n", GetFreeRamAvail());
    return 0;
}





