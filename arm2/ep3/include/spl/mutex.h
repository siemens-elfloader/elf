
#ifndef __CORE_MUTEX_H__
#define __CORE_MUTEX_H__

#include <swilib.h>
#include <nu_swilib.h>


typedef struct
{
    NU_SEMAPHORE sema;
    int locks;
    int dt_id;
    int pid;
    int used;
} CoreMutex;



int createMutex(CoreMutex *mutex);
int destroyMutex(CoreMutex *mutex);
int lockMutex(CoreMutex *mutex);
int tryLockMutex(CoreMutex *mutex);
int unlockMutex(CoreMutex *mutex);


#endif
