
#include <spl/process.h>
#include <spl/mutex.h>




int createMutex(CoreMutex *mutex)
{
    if(!mutex || mutex->used)
        return -1;

    mutex->used = 1;
    mutex->pid = getpid();
    mutex->dt_id = addProcessDtors(mutex->pid, (void*)destroyMutex, mutex, 0);
    mutex->locks = 0;
    return NU_Create_Semaphore((NU_SEMAPHORE *)mutex, "s", 0, NU_PRIORITY);
}


int destroyMutex(CoreMutex *mutex)
{
    if(!mutex || !mutex->used)
        return -1;

    eraseProcessDtor(mutex->pid, mutex->dt_id);
    int s = NU_Delete_Semaphore((NU_SEMAPHORE *)mutex);
    mutex->used = 0;
    return s;
}


int lockMutex(CoreMutex *mutex)
{
    if(!mutex || !mutex->used)
        return -1;

    int status;

    if(mutex->locks > 0) {
        mutex->locks++;
        status = NU_Obtain_Semaphore((NU_SEMAPHORE *)mutex, NU_SUSPEND);
        if(status != NU_SUCCESS)
            mutex->locks--;
        return status;
    } else {

        mutex->locks++;
        return 0;
    }
}


int tryLockMutex(CoreMutex *mutex)
{
    if(!mutex || !mutex->used)
        return -1;

    int status;

    if(mutex->locks < 1)
    {
        mutex->locks++;
        status = 0;
    } else {
        status = -1;
    }

    return status;
}


int unlockMutex(CoreMutex *mutex)
{
    if(!mutex || !mutex->used)
        return -1;

    int status = 0;

    if( mutex->locks > 1 )
        status = NU_Release_Semaphore((NU_SEMAPHORE *)mutex);
    else
        status = NU_SUCCESS;

    if(status == NU_SUCCESS)
        mutex->locks--;
    return status;
}









