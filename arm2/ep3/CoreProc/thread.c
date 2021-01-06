
#include <swilib.h>
#include <spl/gbs_tweak.h>
#include <spl/thread.h>
#include <spl/task.h>
#include <spl/mutex.h>
#include <spl/waitcondition.h>
#include <spl/process.h>
#include <spl/mutex.h>


typedef struct
{
    CoreTask t;
    int ppid;
    char *name;
    int (*handle)(void *);
    void *data;
    int retcode;
    int start_wait_cond,
        exit_wait_cond;
    struct CoreListInode *ppid_list_inode;

}CoreThread;


static CoreThread threads[128];
static CoreMutex tb_mutex;


void coreThreadsInit()
{
    createMutex(&tb_mutex);
    for(int i=0; i<128; ++i)
        threads[i].t.id = -1;
}


void coreThreadsFini()
{
    destroyMutex(&tb_mutex);
}


static short get_best_thread_id()
{
    for(int i=0; i<128; ++i)
        if(threads[i].t.id < 0)
            return i;
    return -1;
}

static CoreThread *getThreadData(short id)
{
    if(id < 0 || id > 128-1)
        return 0;

    return &threads[id];
}



CoreThread *newCoreThreadData()
{
    lockMutex(&tb_mutex);

    short _tid;
    CoreThread *thread = getThreadData((_tid = get_best_thread_id()));
    if(thread) {
        thread->t.id = _tid;
        unlockMutex(&tb_mutex);

        thread->t.events = 0;
        thread->t.event_stop = 0;
        thread->t.mem = 0;
        thread->t.stack = 0;
        thread->t.stack_size = 0;
        thread->t.task = 0;
        thread->t.type = 0;

        thread->exit_wait_cond = -1;
        thread->start_wait_cond = -1;
    } else
        unlockMutex(&tb_mutex);

    return thread;
}


int freeCoreThreadData(int _tid)
{
    CoreThread *thread = getThreadData(_tid);
    if(!thread || thread->t.id < 0)
        return -1;


    thread->t.task = 0;
    thread->t.id = -1;
    return 0;
}



int tidByTask(NU_TASK *task)
{
    if(!task)
        return -1;

    short _tid = ((MYTASK*)task)->tc_argc;
    CoreThread *thread = getThreadData(_tid);
    if( thread && thread->t.id == _tid && thread->t.task == task)
        return _tid;

    for(int i =0; i<128; ++i) {
        if(threads[i].t.id > -1 && threads[i].t.task == task)
            //printf("tidByTask: can`t take fast tid\n");
            return i;
    }
    return -1;
}


int gettid()
{
    NU_TASK *task = NU_Current_Task_Pointer();
    return tidByTask(task);
}


int getptid(int tid)
{
    CoreThread *thread = getThreadData(tid);
    if(!thread)
        return -1;

    return thread->ppid;
}


static void thread_handle(int argc, void *argv)
{
    CoreThread *thread;
    if(argv)
        thread = (CoreThread *)argv;
    thread = getThreadData(argc);

    CoreProcess *parent = coreProcessData(thread->ppid);
    thread->t.id = argc;

    if(parent->t.id < 0)
        thread->t.events = 0;
    else
        thread->t.events = parent->t.events;


    int swc = thread->start_wait_cond;
    thread->start_wait_cond = -1;
    int ewc = thread->exit_wait_cond;

    wakeAllWaitConds(swc);
    destroyWaitCond(swc);

    thread->retcode = thread->handle(thread->data);

    thread->exit_wait_cond = -1;
    wakeAllWaitConds(ewc);
    destroyWaitCond(ewc);
}


int createThread(int prio, int (*handle)(void *), void *data, int run)
{
    TaskConf conf;
    initTaskConf(&conf);

    conf.prio = prio;
    return createConfigurableThread(&conf, handle, data, run);
}


int createConfigurableThread(TaskConf *conf, int (*handle)(void *), void *data, int run)
{
    int pid = getpid();
    enterProcessCriticalCode(pid);
    if(isProcessKilling(pid) == 1)
        return -1;

    short id;
    CoreThread *thread = newCoreThreadData();
    if(!thread) {
        leaveProcessCriticalCode(pid);
        return -1;
    }



    static TaskConf defaults = {
        .prio = DEFAULT_PRIO,
        .stack_size = DEFAULT_STACK_SIZE,
        .stack = 0,
        .is_stack_freeable = 1
    };

    if(!conf)
        conf = &defaults;

    id = thread->t.id;

    if(conf->stack && conf->stack_size < 1) {
        printf("Invalid stack size\n");
        return -3;
    }

    int prio = conf->prio? conf->prio : DEFAULT_PRIO;
    int stack_size = conf->stack_size? conf->stack_size : DEFAULT_STACK_SIZE;
    void *stack = conf->stack? conf->stack : malloc(stack_size);
    conf->is_stack_freeable = conf->stack? conf->is_stack_freeable : 1;

    NU_TASK *task = malloc(sizeof(*task));
    memset(task, 0, sizeof *task);
    thread->t.task = task;
    thread->t.stack = stack;
    thread->t.stack_size = stack_size;
    thread->ppid = pid;
    thread->t.type = 2;
    thread->t.is_stack_freeable = conf->is_stack_freeable;
    thread->handle = handle;
    thread->data = data;
    thread->retcode = 0;
    thread->ppid_list_inode = addProcessThread(thread->ppid, id);

    thread->name = malloc(15);
    sprintf(thread->name, "thread_%d", id);

    if( NU_Create_Task(thread->t.task, thread->name,
                       thread_handle, id, thread,
                       stack, stack_size, prio, 0,
                       NU_PREEMPT, NU_NO_START) != NU_SUCCESS )

    {
        free(task);
        if(conf->is_stack_freeable)
            free(stack);

        freeCoreThreadData(thread->t.id);
        leaveProcessCriticalCode(pid);
        return -2;
    }

    thread->start_wait_cond = createAdvWaitCond("thread_wait", 0);
    thread->exit_wait_cond = createAdvWaitCond("thread_wait", 0);

    if(run)
        NU_Resume_Task(task);

    leaveProcessCriticalCode(pid);
    return id;
}


int destroyThread(int tid)
{
    CoreThread *thread = getThreadData(tid);
    if(!thread || thread->t.id < 0)
        return -1;

    int pid = getpid();

    printf("Entering process critical code...\n");
    enterProcessCriticalCode(pid);
    printf("Entered\n");

    NU_Suspend_Task(thread->t.task);
    NU_Terminate_Task(thread->t.task);
    NU_Delete_Task(thread->t.task);

    void *d = thread->t.stack;
    thread->t.stack = 0;
    if(thread->t.is_stack_freeable)
        free(d);

    d = thread->t.task;
    thread->t.task = 0;
    free(d);

    d = thread->name;
    thread->name = 0;
    free(d);

    void *i = thread->ppid_list_inode;
    thread->ppid_list_inode = 0;
        delProcessThread(thread->ppid, i);

    freeCoreThreadData(thread->t.id);

    leaveProcessCriticalCode(pid);
    return 0;
}


int suspendThread(int tid)
{
    CoreThread *thread = getThreadData(tid);
    if(!thread || thread->t.id < 0)
        return -1;

    return NU_Suspend_Task(thread->t.task);
}


int resumeThread(int tid)
{
    CoreThread *thread = getThreadData(tid);
    if(!thread || thread->t.id < 0)
        return -1;

    return NU_Resume_Task(thread->t.task);
}


int waitForThreadStarted(int _tid)
{
    CoreThread *thread = getThreadData(_tid);
    if(!thread || thread->t.id < 0)
        return -1;

    waitCondition(thread->start_wait_cond);
    return 0;
}



int waitForThreadFinished(int _tid, int *retcode)
{
    CoreThread *thread = getThreadData(_tid);
    if(!thread || thread->t.id != _tid)
        return -1;

    waitCondition(thread->exit_wait_cond);

    if(*retcode)
        *retcode = thread->retcode;

    return 0;
}

