
#include <swilib.h>
#include <spl/coreevent.h>
#include <spl/process.h>
#include <spl/csm.h>
#include <spl/gui.h>
#include <spl/mutex.h>
#include <spl/timer.h>


typedef struct {
    CoreEvent head;
    void (*callback)(int id, CSM_RAM *, GBS_MSG *);
    CSM_RAM cram;
    GBS_MSG msg;
}CoreCSMEvent __attribute__((aligned(4)));


typedef struct {
    CSM_DESC maincsm;
    WSHDR maincsm_name;

    int id;
    int csmID;
    int guiId;
    int dt_id;
    int used;
    int pid;
    int minus11;
    unsigned short name_body[128];
    int can_kill;

    void (*onCreate)(int id, CSM_RAM *);
    void (*onClose)(int id, CSM_RAM *);
    void (*onMessage)(int id, CSM_RAM *, GBS_MSG *);
}CoreCSM;



#define getCoreCSMFormRam(csmram)  \
           ((CoreCSM *)csmram->constr)

static CoreCSM csm_list[128];
static CoreMutex mutex;

void csmInit()
{
    createMutex(&mutex);
    for(int i=0; i<128; ++i) {
        csm_list[i].id = -1;
        csm_list[i].used = 0;
    }
}


void csmFini()
{
    destroyMutex(&mutex);
}


static CoreCSM *getCoreCSMData(int id)
{
    if(id < 0 || id > 128)
        return 0;

    return &csm_list[id];
}



static int find_best_id()
{
    for(int i=0; i<128; ++i)
        if(csm_list[i].id < 0 && !csm_list[i].used)
            return i;
    return -1;
}


static int new_csm_id()
{
    lockMutex(&mutex);
    int id = find_best_id();
    CoreCSM *c = getCoreCSMData(id);

    if(!c) {
        unlockMutex(&mutex);
        return -1;
    }

    c->id = id;
    unlockMutex(&mutex);
    return id;
}


static int free_csm_id(int id)
{
    CoreCSM *c = getCoreCSMData(id);

    if(!c || c->id != id) {
        return -1;
    }

    c->id = -1;
    c->pid = -1;
    c->used = 0;
    return 0;
}


void core_csm_create(CSM_RAM *data)
{
    void core_csm_create_disp(CoreCSMEvent *event)
    {
        event->callback(event->head.id, &event->cram, 0);
    }

    CoreCSM *c = getCoreCSMFormRam(data);
    c->can_kill = 1;
    if(!c->onCreate)
        return;

    CoreCSMEvent event;

    event.head.id = c->id;
    event.head.type = (int)CSM_EVENT;
    event.head.dispatcher = (void (*)(void *))core_csm_create_disp;
    event.callback = (void (*)(int id, CSM_RAM *, GBS_MSG *))c->onCreate;
    memcpy(&event.cram, data, sizeof *data);

    data->state = 0;
    data->unk1 = 0;

    sendEvent(c->pid, &event, sizeof event);
}


void core_csm_destroy(CSM_RAM *data)
{
    void core_csm_destroy_disp(CoreCSMEvent *event)
    {
        event->callback(event->head.id, &event->cram, 0);
    }

    CoreCSM *c = getCoreCSMFormRam(data);

    if(!c->onClose) {
        free_csm_id(c->id);
        return;
    }

    CoreCSMEvent event;

    event.head.id = c->id;
    event.head.type = (int)CSM_EVENT;
    event.head.dispatcher = (void (*)(void *))core_csm_destroy_disp;
    event.callback = (void (*)(int id, CSM_RAM *, GBS_MSG *))c->onClose;
    memcpy(&event.cram, data, sizeof *data);

    sendEvent(c->pid, &event, sizeof event);
    free_csm_id(c->id);
}



int core_csm_message(CSM_RAM *data, GBS_MSG *msg)
{
    CoreCSM *c = getCoreCSMFormRam(data);
    if(!c) // это может быть? о_О
        return 1;

    if (msg->msg == MSG_GUI_DESTROYED && (int)msg->data0 == c->guiId) {
        data->state = -3;
    }

    void core_csm_message_disp(CoreCSMEvent *event) {
        event->callback(event->head.id, &event->cram, &event->msg);
    }

    if(!c->onMessage)
        return 1;


    CoreCSMEvent event;

    event.head.id = c->id;
    event.head.type = (int)CSM_EVENT;
    event.head.dispatcher = (void (*)(void *))core_csm_message_disp;
    event.callback = (void (*)(int id, CSM_RAM *, GBS_MSG *))c->onMessage;
    memcpy(&event.cram, data, sizeof *data);
    memcpy(&event.msg, msg, sizeof *msg);

    sendEvent(c->pid, &event, sizeof event);
    return 1;
}



int createCSM(const char *name, int type,
              void (*onCreate)(int id, CSM_RAM *),
              void (*onClose)(int id, CSM_RAM *),
              void (*onMessage)(int id, CSM_RAM *, GBS_MSG *))
{
    int pid = getpid();
    if(isProcessKilling(pid) == 1)
        return -1;

    enterProcessCriticalCode(pid);

    int id = new_csm_id();
    CoreCSM *data = getCoreCSMData(id);
    if(!data)
        return -1;

    memset(data, 0, sizeof *data);
    data->used = 1;

    data->onCreate = onCreate;
    data->onClose = onClose;
    data->onMessage = onMessage;
    data->maincsm.onMessage = core_csm_message;
    data->maincsm.onCreate = core_csm_create;
    data->minus11 = -11;
    data->pid = getpid();
    data->dt_id = -1;
    data->can_kill = 0;

#ifdef NEWSGOLD
    data->maincsm.zero1 = 0;
    data->maincsm.zero2 = 0;
    data->maincsm.zero3 = 0;
    data->maincsm.zero4 = 0;
#endif

    data->maincsm.onClose = core_csm_destroy;
    data->maincsm.datasize = sizeof(CoreCSM);
    data->maincsm.statesize = 1;
    data->maincsm.states = &data->minus11;

    data->maincsm_name.wsbody = data->name_body;
    data->maincsm_name.ws_malloc = NAMECSM_MAGIC1;
    data->maincsm_name.ws_mfree = NAMECSM_MAGIC2;
    data->maincsm_name.isbody_allocated = 0;
    data->maincsm_name.maxlen = 128;
    data->maincsm_name.unk1 = 0;


    wsprintf(&data->maincsm_name, "%t", name);

    CoreCSM main_csm;
    LockSched();

    if(type == CoreCSM_GUI)
        data->csmID = CreateCSM((CSM_DESC*)data, &main_csm, 0);
    else {
        CSM_RAM *save_cmpc = CSM_root()->csm_q->current_msg_processing_csm;
        CSM_root()->csm_q->current_msg_processing_csm = (CSM_RAM*)CSM_root()->csm_q->csm.first;
        data->csmID = CreateCSM((CSM_DESC*)data, &main_csm, 0);
        CSM_root()->csm_q->current_msg_processing_csm = save_cmpc;
    }

    UnlockSched();

    if(data->csmID < 0) {
        data->used = 0;
        id = -1;
        free_csm_id(id);
    } else {
        data->dt_id = addProcessDtors(data->pid, (void (*)(void*, void*))closeCSM, (void *)id, 0);

        // хак, если сразу вызвать клосксм - он не убивается,
        // а это может понадобится если процесс умрёт не естественной смертью сразу после создания.
        //data->check_tmr_id = timerStart(20, csm_kill_time_check, data);
    }
    leaveProcessCriticalCode(pid);

    return id;
}


int closeCSM(int id)
{
    CoreCSM *csm = getCoreCSMData(id);
    if(!csm || !csm->used)
        return -1;

    if(csm->id < 0)
        return -2;

    eraseProcessDtor(csm->pid, csm->dt_id);

    if(csm->csmID) {
        while(csm->can_kill == 0)
            NU_Sleep(2);
        CloseCSM(csm->csmID);
    }
    csm->used = 0;

    return 0;
}


int bindGUIToCSM(int id, int real_gui_id)
{
    CoreCSM *csm = getCoreCSMData(id);
    if(!csm)
        return -1;

    return csm->guiId = real_gui_id;
}


int setNameCSM(int id, const char *name)
{
    CoreCSM *csm = getCoreCSMData(id);
    if(!csm)
        return -1;

    wsprintf(&csm->maincsm_name, "%t", name);
    return 0;
}
