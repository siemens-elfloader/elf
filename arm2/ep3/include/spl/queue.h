
#ifndef __COREQUEUE_H__
#define __COREQUEUE_H__

#include <nu_swilib.h>



int createQueue(const char *name, void *start_address, unsigned long queue_size,
                                  unsigned char message_type, unsigned long message_size,
                                  unsigned char suspend_type);


int destroyQueue(int id);
NU_QUEUE *getQueueDataByID(int id);




#endif
