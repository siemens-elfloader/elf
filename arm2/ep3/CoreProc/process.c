#include <swilib.h>
#include <nu_swilib.h>
#include <limits.h>
#include <spl/coreevent.h>
#include <spl/process.h>
#include <spl/thread.h>
#include <spl/mutex.h>
#include <spl/waitcondition.h>
#include <spl/gbs_tweak.h>
#include "helperproc.h"


#define MAX_PROCESS_ID 256
typedef struct
{
    void (*h)(void *, void *);
    void *d[2];
}TorsList;

char *_strdup(const char *str);
static CoreProcess core_process[MAX_PROCESS_ID];
static CoreMutex pb_mutex;


void processInit()
{
    createMutex(&pb_mutex);
    for(int i =0; i<MAX_PROCESS_ID; ++i) {
        core_process[i].t.id = -1;
        core_process[i].t.task = 0;
    }
}


void processFini()
{
    char name[64];
    unsigned char status, prio, preemt;
    unsigned long sched_cnt, time_slice, stack_sz, min_stack;
    void *stack_base;

    for(int i =0; i<MAX_PROCESS_ID; ++i) {

        if(!core_process[i].t.task)
            continue;

        int err = NU_Task_Information(core_process[i].t.task, name, &status, &sched_cnt, &prio,
                            &preemt, &time_slice, &stack_base, &stack_sz, &min_stack);

        if(err == NU_SUCCESS) {
            char d[128];
            sprintf(d, "Task '%s' not killed", name);
            ShowMSG(1, (int)d);
        }
    }


    destroyMutex(&pb_mutex);
}



CoreProcess *coreProcessData(short _pid) {
    if(_pid >= MAX_PROCESS_ID || _pid < 0)
        return 0;

    return &core_process[_pid];
}


static short emptyPid()
{
    for(short i =0; i<MAX_PROCESS_ID; ++i)
    {
        if(core_process[i].t.id < 0)
            return i;
    }

    return -1;
}


CoreProcess *newCoreProcessData()
{
    lockMutex(&pb_mutex);

    short _pid;
    CoreProcess *proc = coreProcessData((_pid = emptyPid()));
    if(proc) {
        proc->t.id = _pid;
        unlockMutex(&pb_mutex);

        proc->t.events = 0;
        proc->t.event_stop = 0;
        proc->t.mem = 0;
        proc->t.stack = 0;
        proc->t.stack_size = 0;
        proc->t.task = 0;
        proc->t.type = 0;

        proc->kill_mode =  proc->terminated = 0;
        proc->kostil.kik = 0;
        proc->kostil.d = 0;
        proc->ppid = -1;
        proc->start_wait_cond = -1;
        proc->exit_wait_cond = -1;
    } else
        unlockMutex(&pb_mutex);

    return proc;
}


int freeCoreProcessData(int _pid)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id != _pid)
        return -1;

    proc->t.task = 0;
    proc->t.id = -1;
    return 0;
}


int sendEvent(int pid, void *event, size_t size)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || !proc->t.events)
        return -1;

    return NU_Send_To_Queue(proc->t.events, event, size, NU_NO_SUSPEND);
}


int getppid()
{
    CoreProcess *proc = coreProcessData(getpid());
    if(!proc)
        return 0;

    return proc->ppid;
}



int pidByTask(NU_TASK *task)
{
    if(!task)
        return -1;

    /* небольшой костылик дл€ увеличени€ скорости определени€ pid,
     * в поле argc мы пишем не количество параметров, а id процесса.
     * “аким образом мы можем просто выт€нуть из структуры argc
     * и проверить его на валидность, в случае фейла, ищем старым способом
    */
    short _pid = ((MYTASK*)task)->tc_argc;
    CoreProcess *proc = coreProcessData(_pid);
    if( proc && proc->t.id > -1 && proc->t.id == _pid && proc->t.task == task)
        return _pid;

    for(int i =0; i<256; ++i) {
        if(core_process[i].t.id > -1 && core_process[i].t.task == task)
            return i;
    }

    return -1;
}


int getpid()
{
    NU_TASK *task = NU_Current_Task_Pointer();
    if(!task) {
        return -1;
    }

    int tid = tidByTask(task);
    if(tid > -1) {
        return getptid(tid);
    }

    return pidByTask(task);
}



typedef struct
{
    CoreEvent head;
    void *data;
}CoreEventProcess;


static void kill_process(int _pid)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id != _pid)
        return;

    int err = 0;

    NU_Suspend_Task(proc->t.task);
    if( NU_Terminate_Task(proc->t.task) != NU_SUCCESS) {
        printf("Cant kill task! %d\n", _pid);
        ShowMSG(1, (int)"Ќемогу убить таск!");
    }

    if( (err = NU_Delete_Task(proc->t.task)) != NU_SUCCESS) {
        printf("Cant delete task! %d\n", _pid);
        ShowMSG(1, (int)"Ќемогу удалить таск!");
    }

    destroyMutex(&proc->critical_code.mutex);

    if(!err) {
        if(proc->t.is_stack_freeable)
            free(proc->t.stack);
        proc->t.stack = 0;

        free(proc->t.task);
        proc->t.task = 0;
    }

    if(proc->kostil.kik)
        proc->kostil.kik(proc->kostil.d);

    printf("process %d destroyed\n", proc->t.id);
    //SetVibration(40);
    //NU_Sleep(30);
    //SetVibration(0);

    freeCoreProcessData(_pid);
}


static void kill_impl(int _pid, int tid, int code, int lock)
{
    printf("%s(%d, %d, %d, %d)\n", __FUNCTION__, _pid, tid, code, lock);
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id != _pid)
        return;

    /*if(!proc->hisr_call)
        proc->hisr_call = NU_Current_Task_Pointer() == ? 1 : 0;*/

    if(!proc->hisr_call) {
        if(proc->terminated == 2)
            return;
    } else
         printf("Hisr killing...\n");



    proc->terminated = 2;
    proc->retcode = code;
    proc->kill_tryes ++;

    printf("Try number %d\n Kill state: %d\n", proc->kill_tryes, proc->kill_state);

    // безнадЄжный процесс...
    if(proc->kill_tryes > 14) {
        return;
    }

    printf("State: 0\n");
    if(proc->kill_state == 0) {
        if(lock) {
            lockMutex(&proc->critical_code.mutex);
            proc->critical_code.pid = _pid;
            proc->critical_code.tid = tid;
        }
        proc->kill_state = 1;
    }


    printf("State: 1\n");
    if(proc->kill_state == 1) {
        NU_Delete_Queue(proc->t.events);
        free(proc->t.mem);
        proc->t.events = 0;
        proc->t.mem = 0;
        proc->kill_state ++;
    }

    printf("State: 2\n");
    if(proc->kill_state == 2) {
        while(--proc->argc > -1)
            free(proc->argv[proc->argc]);
        free(proc->argv);
        proc->kill_state++;
    }


    printf("State: 3\n");
    if(proc->kill_state == 3) {
        struct CoreListInode *inode = proc->process.list.first;
        while(inode)
        {
            int __pid = (int)inode->self;
            printf("Destroying process %d...\n", __pid);
            kill(__pid, 0);
	    waitForProcessFinished(__pid, 0);
            printf("process %d destroyed\n", __pid);

            if(inode != proc->process.list.first)
                inode = proc->process.list.first;
            else
                inode = inode->next;
        }
        proc->kill_state++;
    }

    printf("State: 4\n");
    if(proc->kill_state == 4) {
        struct CoreListInode *inode = proc->threads.list.first;
        while(inode)
        {
            int tid = (int)inode->self;
            printf("Destroying thread %d...\n", tid);
            destroyThread(tid);
            printf("Thread %d destroyed\n", tid);

            if(inode != proc->threads.list.first)
                inode = proc->threads.list.first;
            else
                inode = inode->next;
        }
        proc->kill_state++;
    }


    printf("State: 5\n");
    if(proc->kill_state == 5) {
        printf("Dtors run\n");
        TorsList *val;
        CoreArray *array = &proc->dtors;
        int i = 0;
        corearray_foreach(TorsList *, val, array, i) {
            corearray_store_cell(array, i, NULL);

            if(val) {
                val->h(val->d[0], val->d[1]);
                free(val);
            }
        }
        proc->kill_state++;
        printf("Dtors complete\n");

    }

    printf("State: 6\n");
    if(proc->kill_state == 6) {
        corearray_release(&proc->ctors);
        corearray_release(&proc->dtors);
        corearray_release(&proc->idUsersData);

        destroyMutex(&proc->m_ctor);
        destroyMutex(&proc->m_dtor);
        destroyMutex(&proc->process.mutex);
        destroyMutex(&proc->threads.mutex);

        proc->kill_state ++;
    }

    printf("State: 7\n");
    if(proc->kill_state == 7) {
        printf("detachResCtl ...\n");
        detachResCtl(_pid, &proc->resData, proc->resAttached);
        printf("detachResCtl complete!\n");
        proc->kill_state ++;
    }

    printf("Free proc name\n");
    if(proc->name) {
        void *d = proc->name;
        proc->name = 0;
        free(d);
    }

    printf("State: 8\n");
    if(proc->kill_state == 8) {
        printf("kill_process(%d)\n", _pid);
        SUBPROC(kill_process, _pid);
        proc->kill_state ++;
    }

    printf("State: 9 : %d\n", proc->kill_state);
    if(proc->kill_state == 9) {
        if(proc->ppid_inode) {
            delProcessFromParent(proc->ppid, proc->ppid_inode);
            proc->kill_state ++;
        }
    }

    int ex_wc = proc->exit_wait_cond;
    proc->exit_wait_cond = -1;
    wakeAllWaitConds(ex_wc);
    destroyWaitCond(ex_wc);

    helperproc_schedule((void *)kill_process, (void *)_pid, 0, 0);

    while(1)
        NU_Sleep(30);
}


static void handle(int argc, void *argv)
{
    UNUSED(argc);
    UNUSED(argc);

    CoreProcess *proc;

    if(argv)
        proc = (CoreProcess *)argv;
    else
        proc = coreProcessData(getpid());

    short mpid = proc->t.id;
    if(proc->kill_mode)
    {
        kill_impl(mpid, proc->sig_from_tid, proc->retcode, 0);
        return;
    }

    char *mem = malloc( 128 * (28*4) );
    NU_QUEUE queue;
    /*int err = */NU_Create_Queue(&queue, "ololo", mem, 128 * 28, NU_VARIABLE_SIZE, 128, NU_FIFO);

    proc->t.event_stop = 0;
    proc->t.events = &queue;
    proc->t.mem = mem;

    corelist_init(&proc->threads.list);
    corelist_init(&proc->process.list);
    corearray_init(&proc->idUsersData, NULL);
    proc->resAttached = attachResCtl(mpid, &proc->resData);

    TorsList *val;
    CoreArray *array = &proc->ctors;
    int i = 0;
    corearray_foreach(TorsList *, val, array, i) {
        val->h(val->d[0], val->d[1]);
        free(val);
    }

    corearray_release(&proc->ctors);

    int swc = proc->start_wait_cond;
    proc->start_wait_cond = -1;

    wakeAllWaitConds(swc);
    destroyWaitCond(swc);

    proc->retcode = proc->main(proc->argc, proc->argv);

    kill_impl(mpid, -1, proc->retcode, 1);
}


static void process_bump(CoreEventProcess *event) {
    UNUSED(event);
    coreProcessData(getpid())->t.event_stop = 1;
}


void quit()
{
    CoreEventProcess event;
    event.head.id = SIGKILL;
    event.head.type = CORE_EVENT_PROCESS;
    event.head.dispatcher = (void(*)(void*))process_bump;
    sendEvent(getpid(), &event, sizeof event);
}


void kill_hisr_chek(int _pid, int tid, int code, int hisr)
{
    printf("%s(%d, %d)\n", __FUNCTION__, _pid, tid);
    if(_pid < 0 && _pid >= MAX_PROCESS_ID)
        return;


    if(_pid == getpid()) { // self kill
        if(tid > -1 && tid == gettid())
            goto reset_and_kill;
        kill_impl(_pid, tid, code, 1);

    } else {

        reset_and_kill: {

        CoreProcess *proc = coreProcessData(_pid);
        if(proc->t.id < 0)
            return;

        if(proc->terminated != 2) {
            lockMutex(&proc->critical_code.mutex);
            proc->critical_code.pid = _pid;
            proc->critical_code.tid = tid;
        }

        printf("Finish him!\n");

        proc->hisr_call = hisr;
        proc->sig_from_tid = tid;
        proc->kill_mode = 1;
        proc->terminated = 1;
        proc->retcode = code;

        int r = NU_Terminate_Task(proc->t.task);
        printf("Term: %d\n", r);

        r = NU_Reset_Task(proc->t.task, _pid, proc);
        printf("Reset: %d\n", r);

        r = NU_Resume_Task(proc->t.task);
        //printf("Resume: %d\n", r);
        }
    }
}


void kill(int _pid, int code)
{
    kill_hisr_chek(_pid, gettid(), code, 0);
}


void processEvents()
{
    CoreProcess *proc = coreProcessData(getpid());
    NU_QUEUE *queue = proc->t.events;
    unsigned long actual_size;
    int event[128];
    int err = 0;

    while((err = NU_Receive_From_Queue(queue, (void*)event, 128, &actual_size, NU_SUSPEND)) == NU_SUCCESS)
    {
        if(actual_size > sizeof(event)) {
            // Warning!!!
        }

        CoreEvent *e = (CoreEvent*)event;
        e->dispatcher(e);

        if(proc->t.event_stop)
            break;
    }
}


int createProcess(const char *name, int prio, int (*_main)(int, char**), int argc, char **argv, int run)
{
    TaskConf conf;
    initTaskConf(&conf);

    conf.prio = prio;
    return createConfigurableProcess(&conf, name, _main, argc, argv, run);
}


int createConfigurableProcess(TaskConf *conf, const char *name, int (*_main)(int, char**), int argc, char **argv, int run)
{
    CoreProcess *proc = newCoreProcessData();
    if(!proc)
        return -1;

    static TaskConf defaults = {
        .prio = DEFAULT_PRIO,
        .stack_size = DEFAULT_STACK_SIZE,
        .stack = 0,
        .is_stack_freeable = 1
    };

    if(!conf)
        conf = &defaults;

    if(conf->stack && conf->stack_size < 1) {
        printf("Invalid stack size\n");
        return -3;
    }

    if(createMutex(&proc->critical_code.mutex)) {
        freeCoreProcessData(proc->t.id);
        return -1;
    }

    int prio = conf->prio? conf->prio : DEFAULT_PRIO;
    int stack_size = conf->stack_size? conf->stack_size : DEFAULT_STACK_SIZE;
    void *stack = conf->stack? conf->stack : malloc(stack_size);
    conf->is_stack_freeable = conf->stack? conf->is_stack_freeable : 1;
    short _pid = proc->t.id;
    int err = 0;

    NU_TASK *task = malloc(sizeof *task);
    memset(task, 0, sizeof *task);
    proc->critical_code.locks = 0;
    proc->critical_code.pid = proc->critical_code.tid = -1;
    proc->t.task = task;
    proc->t.stack = stack;
    proc->t.stack_size = stack_size;
    proc->argc = argc;
    proc->argv = argv;
    proc->t.type = 1;
    proc->t.is_stack_freeable = conf->is_stack_freeable;
    proc->ppid = getpid();
    proc->name = _strdup(name);
    proc->main = _main;
    proc->retcode = 0;
    proc->hisr_call = 0;
    proc->kill_state = 0;
    proc->kill_tryes = 0;
    proc->sig_from_tid = -1;


    if( (err = NU_Create_Task(task, (char *)name, handle, _pid, proc, stack, stack_size, prio, 0, NU_PREEMPT, NU_NO_START)) != NU_SUCCESS )
    {
        free(task);

        if(proc->t.is_stack_freeable)
            free(stack);

        if(proc->name)
            free(proc->name);

        while(--proc->argc > -1)
            free(proc->argv[proc->argc]);
        free(argv);

        destroyMutex(&proc->critical_code.mutex);

        freeCoreProcessData(_pid);
        //char d[128];
        //sprintf(d, "Creating process failed %d\n", err);
        //ShowMSG(1, (int)d);
        return err;
    }

    corearray_init(&proc->ctors, NULL);
    corearray_init(&proc->dtors, NULL);
    createMutex(&proc->m_ctor);
    createMutex(&proc->m_dtor);
    createMutex(&proc->process.mutex);
    createMutex(&proc->threads.mutex);

    proc->start_wait_cond = createAdvWaitCond("proc_wait", 0);
    proc->exit_wait_cond = createAdvWaitCond("proc_wait", 0);

    addProcessToParent(proc->ppid, _pid);

    if(run)
        NU_Resume_Task(task);

    return _pid;
}



int resetProcess(int pid, int argc, char **argv)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id < 0)
        return -1;

    proc->argc = argc;
    proc->argv = argv;

    NU_Suspend_Task(proc->t.task);
    NU_Terminate_Task(proc->t.task);
    NU_Reset_Task(proc->t.task, 0, 0);

    return 0;
}


int suspendProcess(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id < 0)
        return -1;

    return NU_Suspend_Task(proc->t.task);
}


int fullProcessSuspend(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id < 0)
        return -1;

    struct CoreListInode *inode = 0;
    corelist_foreach(inode, proc->threads.list.first) {
        int tid = (int)inode->self;
        suspendThread(tid);
    }

    return NU_Suspend_Task(proc->t.task);
}


int resumeProcess(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id < 0)
        return -1;

    return NU_Resume_Task(proc->t.task);
}


int fullProcessResume(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id < 0)
        return -1;

    struct CoreListInode *inode = 0;
    corelist_foreach(inode, proc->threads.list.first) {
        int tid = (int)inode->self;
        resumeThread(tid);
    }

    return NU_Resume_Task(proc->t.task);
}


static int addProcessTors(CoreArray *arr, void (*h)(void *, void *), void *data1, void *data2)
{
    int too;
    TorsList *t = malloc(sizeof *t);

    t->h = h;
    t->d[0] = data1;
    t->d[1] = data2;

    if(( too = corearray_push_back(arr, t)) < 0)
    {
        free(t);
        return -2;
    }

    return too;
}


int eraseProcessCtor(int pid, int at)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id < 0)
        return -1;

    if(at < 0 || at >= (int)proc->ctors.size)
        return -1;

    TorsList *l = corearray_cell(&proc->ctors, at);
    corearray_store_cell(&proc->ctors, at, NULL);

    if(l)
        free(l);

    return 0;
}


int eraseProcessDtor(int pid, int at)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id < 0)
        return -1;

    if(at < 0 || at >= (int)proc->dtors.size)
        return -1;

    TorsList *l = corearray_cell(&proc->dtors, at);
    corearray_store_cell(&proc->dtors, at, NULL);

    if(l)
        free(l);

    return 0;
}

int addProcessCtors(int _pid, void (*h)(void *, void *), void *data1, void *data2)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0)
        return -1;

    lockMutex(&proc->m_ctor);
    int r = addProcessTors(&proc->ctors, h, data1, data2);
    unlockMutex(&proc->m_ctor);
    return r;
}


int addProcessDtors(int _pid, void (*h)(void *, void *), void *data1, void *data2)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id != _pid)
        return -1;

    lockMutex(&proc->m_dtor);
    int r = addProcessTors(&proc->dtors, h, data1, data2);
    unlockMutex(&proc->m_dtor);
    return r;
}


int setProcessDieAction(int _pid, void (*h)(void *), void *d)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0)
        return -1;

    proc->kostil.d = d;
    proc->kostil.kik = h;

    return 0;
}


struct CoreListInode *addProcessThread(int _pid, int tid)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0)
        return 0;

    lockMutex(&proc->threads.mutex);
    struct CoreListInode *r = corelist_push_back(&proc->threads.list, (void *)tid);
    unlockMutex(&proc->threads.mutex);
    return r;
}


int delProcessThread(int _pid, struct CoreListInode *inode)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0 || !inode)
        return -1;

    lockMutex(&proc->threads.mutex);
    corelist_del_inode(&proc->threads.list, inode);
    unlockMutex(&proc->threads.mutex);
    return 0;
}


struct CoreListInode *addProcessToParent(int ppid, int pid)
{
    CoreProcess *proc = coreProcessData(ppid);
    if(!proc || proc->t.id != ppid)
        return 0;

    lockMutex(&proc->process.mutex);
    struct CoreListInode *r = corelist_push_back(&proc->process.list, (void *)pid);
    unlockMutex(&proc->process.mutex);
    return r;
}


int delProcessFromParent(int ppid, struct CoreListInode *inode)
{
    CoreProcess *proc = coreProcessData(ppid);
    if(!proc || proc->t.id != ppid || !inode)
        return -1;

    lockMutex(&proc->process.mutex);
    corelist_del_inode(&proc->threads.list, inode);
    unlockMutex(&proc->process.mutex);
    return 0;
}


const char *pidName(int _pid)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0)
        return 0;

    return proc->name;
}


int setProcessUserdata(int _pid, void *d)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0)
        return -1;

    proc->userdata = d;
    return 0;
}


int waitForProcessFinished(int _pid, int *retcode)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0)
        return -1;

    waitCondition(proc->exit_wait_cond);

    if(*retcode)
        *retcode = proc->retcode;

    return 0;
}


int attachProcessIdUserData(int _pid, void *userData)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id < 0)
        return -1;

    if(!userData)
        return -2;

    return corearray_push_back(&proc->idUsersData, userData);
}



ResCtlData *dataOfResCtl(int _pid, int id)
{
    CoreProcess *proc = coreProcessData(_pid);
    if(!proc || proc->t.id != _pid)
        return 0;

    if(id < 0 || id >= proc->resAttached) {
        return 0;
    }

    return &proc->resData[id];
}



int enterProcessCriticalCode(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id != pid)
        return -1;

    /*if(proc->terminated == 2)
        return -2;*/

    int _pid = getpid();
    int _tid = gettid();

    proc->critical_code.locks++;
    if(proc->critical_code.locks == 1) {

        // если мы уже залочили тред
        if(proc->critical_code.tid > -1){
            // и оп€ть его же лочим
            if(proc->critical_code.tid == _tid)
                // то выходим нафиг
                return 0;
        }

        // если тред не лочили, а лочили процесс
        if(proc->critical_code.pid > -1){
            // и оп€ть его же лочим
            if(proc->critical_code.pid == _pid)
                // то выходим нафиг
                return 0;
        }

        //printf("enterProcessCriticalCode: locking(%d, %d) (%d, %d)... \n", proc->critical_code.pid,
        //       proc->critical_code.tid, _pid, _tid);

        lockMutex(&proc->critical_code.mutex);
        proc->critical_code.pid = _pid;
        proc->critical_code.tid = _tid;
    }

    return 0;
}


int leaveProcessCriticalCode(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id != pid)
        return -1;

    /*if(proc->terminated == 2)
        return -2;*/

    proc->critical_code.locks --;
    if(proc->critical_code.locks <= 0) {
        unlockMutex(&proc->critical_code.mutex);
        proc->critical_code.pid = -1;
        proc->critical_code.tid = -1;
    }

    return 0;
}


int isProcessKilling(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc || proc->t.id != pid)
        return -1;

    return proc->terminated > 0;
}







