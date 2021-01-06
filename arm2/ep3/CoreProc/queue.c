
#include <swilib.h>
#include <spl/resctl.h>
#include <spl/corelist.h>
#include <spl/process.h>
#include <spl/queue.h>


typedef struct  {
    int id;
    NU_QUEUE queue;
    int pid;
    int dt_id;
}idQueue;

#define MAX_QUEUE_ID 256
static idQueue queue_db[MAX_QUEUE_ID];


void queueInit()
{
    for(int i=0; i<MAX_QUEUE_ID; ++i)
        queue_db[i].id = -1;
}


idQueue *coreQueueData(short id) {
    if(id >= MAX_QUEUE_ID || id < 0)
        return 0;

    return &queue_db[id];
}


static short emptyQueue()
{
    for(int i =0; i<MAX_QUEUE_ID; ++i)
    {
        if(queue_db[i].id < 0)
            return i;
    }

    return -1;
}



int createQueue(const char *name, void *start_address, unsigned long queue_size,
                                  unsigned char message_type, unsigned long message_size,
                                  unsigned char suspend_type)
{
    int id = emptyQueue();
    idQueue *q = coreQueueData(id);
    if(!q) {
        return -1;
    }
    q->id = id;
    q->pid = getpid();
    memset(&q->queue, 0, sizeof(q->queue));

    int status;
    if( (status = NU_Create_Queue(&q->queue, (CHAR*)name, start_address, queue_size, message_type, message_size, suspend_type)) != NU_SUCCESS ) {
        q->id = -1;
        return status;
    }

    q->dt_id = addProcessDtors(q->pid, (void*)destroyQueue, (void*)id, 0);
    return id;
}


int destroyQueue(int id)
{
    idQueue *q = coreQueueData(id);
    if(!q || q->id != id)
        return -1;

    NU_Delete_Queue(&q->queue);
    eraseProcessDtor(q->pid, q->dt_id);
    q->id = -1;
    return 0;
}


NU_QUEUE *getQueueDataByID(int id)
{
    idQueue *q = coreQueueData(id);
    if(!q || q->id != id)
        return 0;

    return &q->queue;
}













