
#include <swilib.h>
#include <nu_swilib.h>
#include <spl/coreevent.h>
#include <spl/timer.h>
#include <spl/process.h>



typedef struct {
    CoreEvent head;
    void (*callback)(int, void *);
    void *userdata;
}TimerEvent __attribute__((aligned(4)));

struct TimerData {
    NU_TIMER timer;
    void (*callback)(int, void *);
    int pid;
    int sended;
    int dt_id;
    char last;
    void *userdata;
};

static struct TimerData timers[128] = {};


void timersInit()
{
    for(int i=0; i<128; ++i) {
        timers[i].pid = -1;
        timers[i].last = 0;
    }
}


void timersFini()
{

}


static int find_best_id()
{
    for(int i=0; i<128; ++i)
        if(timers[i].pid == -1)
            return i;
    return -1;
}


static void timer_displatcher(TimerEvent *event)
{
    if(timers[event->head.id].pid < 0)
        return;

    timers[event->head.id].sended --;
    if(timers[event->head.id].last) {
        timers[event->head.id].pid = -1;
        timers[event->head.id].last = 0;
        return;
    }

    event->callback(event->head.id, event->userdata);

}


static void timer_handle(unsigned long id) //?
{
    TimerEvent event;
    event.head.id = id;
    event.head.type = TIMER_EVENT;
    event.callback = timers[id].callback;
    event.head.dispatcher = (void (*)(void*))timer_displatcher;
    event.userdata = timers[id].userdata;

    timers[id].sended++;
    sendEvent(timers[id].pid, &event, sizeof event);
}


int timerStart(unsigned long time, void (*callback)(int, void *), void *userdata)
{
    int id = find_best_id(), err = 0; // get best id
    if(id < 0)
        return -1;

    int pid = getpid();
    enterProcessCriticalCode(pid);
    if(isProcessKilling(pid) == 1)
        return -1;

    struct TimerData *timer = &timers[id];

    timer->callback = callback;
    timer->pid = pid;
    timer->sended = 0;
    timer->last = 0;
    timer->userdata = userdata;


    err = NU_Create_Timer((NU_TIMER*)timer, "ololo", timer_handle, id, time, time, NU_ENABLE_TIMER);
    if(err != NU_SUCCESS) {
        printf("timerStart: err %d\n", err);
    } else
        timer->dt_id = addProcessDtors(timer->pid, (void (*)(void*, void*))timerStop, (void *)id, 0);

    leaveProcessCriticalCode(pid);

    return err == NU_SUCCESS?
            id : err;
}


int timerPause(int id)
{
    struct TimerData *timer = &timers[id];
    return NU_Control_Timer((NU_TIMER*)timer, NU_DISABLE_TIMER);
}


int timerResume(int id)
{
    struct TimerData *timer = &timers[id];
    return NU_Control_Timer((NU_TIMER*)timer, NU_ENABLE_TIMER);
}


int timerStop(int id)
{
    if(id < 0)
        return -1;

    struct TimerData *timer = &timers[id];
    if(timer->pid < 0 || timer->last)
        return -1;

    eraseProcessDtor(timer->pid, timer->dt_id);

    timerPause(id);
    NU_Control_Timer((NU_TIMER*)timer, NU_DISABLE_TIMER);
    int err = NU_Delete_Timer((NU_TIMER*)timer);

    if(timer->sended < 1)
        timer->pid = -1;
    else
        timer->last = 1;
    return err;
}




