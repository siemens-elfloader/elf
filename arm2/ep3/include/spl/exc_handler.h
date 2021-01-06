

#ifndef __EXC_HANDLER_H__
#define __EXC_HANDLER_H__

#include <swilib.h>
#include <nu_swilib.h>


typedef struct {
    int pid, tid;
    unsigned int lr;
    unsigned int cpsr;
    unsigned int type;
    char         string[0x20];
}EXC_QUEUE;


#define EXC_QUEUE_MAX_SIZE      100

void *get_stack_pointer_from_proc(int pid);

int  AddToExcQueue(int pid, int tid, unsigned int lr, unsigned int cpsr, int type, char *string);
int  GetExcQueueElement(EXC_QUEUE *exc_que);
void RemoveFromExcQueueElement(int id);


void da_handler_vector();
void pa_handler_vector();
void ui_handler_vector();

extern void swi2_vector();
extern void swi3_vector();

extern void UnLockAllAccess();
extern void LockAllAccess();

extern void EnableInterrupts();
extern void DisableInterrupts();



#define EXC_TYPE_NULL            0
#define EXC_TYPE_DATA_ABORT      1
#define EXC_TYPE_PREFETCH_ABORT  2
#define EXC_TYPE_UND_INSTR       3
#define EXC_TYPE_SEXIT           4

#define EXC_HANDLER_NAME        "EXC_HISR"
#define EXC_HANDLER_STACK_SIZE  0x1000

#define ABORT_STACK_SIZE        0x1000
#define UND_STACK_SIZE          0x1000



//Real Exceptions Installers
#define data_abort_reg(da)      *( (unsigned long *) (0x30) ) = (unsigned long)da
#define prefetch_abort_reg(pa)  *( (unsigned long *) (0x2C) ) = (unsigned long)pa
#define und_instruct_reg(ui)    *( (unsigned long *) (0x24) ) = (unsigned long)ui

//Default Exceptions addresses
#define DA_DEF_HANDLER_SG       0x00000040
#define PA_DEF_HANDLER_SG       0x000000A4
#define UI_DEF_HANDLER_SG       0x000001B4

#define DA_DEF_HANDLER_NSG      0x00000040
#define PA_DEF_HANDLER_NSG      0x00000124
#define UI_DEF_HANDLER_NSG      0x00000374


//Some (S)Exits Installers
#define swi2_reg_sg(swi2)       *( (unsigned long *) (0x140) ) = (unsigned long)swi2
#define swi3_reg_sg(swi3)       *( (unsigned long *) (0x144) ) = (unsigned long)swi3

#define swi2_reg_nsg(swi2)      *( (unsigned long *) (0x2B0) ) = (unsigned long)swi2
#define swi3_reg_nsg(swi3)      *( (unsigned long *) (0x2B4) ) = (unsigned long)swi3


//Default SWI2 && SWI3 Handlers addresses
#define SWI2_DEF_HANDLER_SG       0x00000168
#define SWI3_DEF_HANDLER_SG       0x0000017C

#define SWI2_DEF_HANDLER_NSG      0x00000310
#define SWI3_DEF_HANDLER_NSG      0x00000324

#endif

