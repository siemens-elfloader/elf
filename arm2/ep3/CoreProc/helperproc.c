
#include <swilib.h>
#include <usart.h>
#include <spl/process.h>
#include <spl/mutex.h>
#include <spl/queue.h>
#include <spl/memctl.h>
#include "helperproc.h"


#if 1
void helperProcInit(){}
void helperProcFini(){}
void helperproc_schedule(void *func, void *d1, void *d2, void *d3) {
    SUBPROC(func, d1, d2, d3);
}

#else
typedef struct {
    void (*run)(void *, void *, void *);
    void *data[3];
}helper_data __attribute__((aligned(4)));

#define message_size sizeof(helper_data)/4

static NU_QUEUE help_queue;
static NU_TASK helper_task;
static void helperproc_handle(int argc, void *argv);
static void *mem = 0;
static char *stack = 0;
static int stack_size = 0x4000;


void helperProcInit()
{
    memset(&help_queue, 0, sizeof(help_queue));
    mem = malloc(sizeof(helper_data) * 128);
    stack = malloc(stack_size);
    NU_Create_Queue(&help_queue, "helperproc", mem, message_size * 128, NU_FIXED_SIZE, message_size, NU_FIFO);
    NU_Create_Task(&helper_task, "helperproc", helperproc_handle, 0, 0, stack, stack_size, 95, 0, NU_PREEMPT, NU_START);
}


void helperProcFini()
{
    NU_Suspend_Task(&helper_task);
    NU_Terminate_Task(&helper_task);
    NU_Delete_Task(&helper_task);

    NU_Delete_Queue(&help_queue);
    free(mem);
    free(stack);
}



void helperproc_schedule(void *func, void *d1, void *d2, void *d3)
{
    helper_data event;
    event.run = func;
    event.data[0] = d1;
    event.data[1] = d2;
    event.data[2] = d3;

    NU_Send_To_Queue(&help_queue, (void*)&event, message_size, NU_NO_SUSPEND);
}


void helperproc_handle(int argc, void *argv)
{
    UNUSED(argc);
    UNUSED(argv);

    unsigned long asize;
    helper_data event = {0,{1,2,3}};
    while(1)
    {
        if(NU_Receive_From_Queue(&help_queue, &event, message_size, &asize, NU_SUSPEND) != NU_SUCCESS)
            break;
        //if(asize != message_size)
        //    continue;

        /*char d[256] = {0};
        sprintf(d, "%X\n%d\n %d - %d", event.run, event.data[0], asize, message_size);
        ShowMSG(1, (int)d);*/

        printf("helper: asize %d (%X, %X, %X)\n", asize, event.data[0], event.data[1], event.data[2]);

        if(event.run)
            event.run(event.data[0], event.data[1], event.data[2]);
    }
}
#endif
