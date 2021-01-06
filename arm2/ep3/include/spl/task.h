
#ifndef __CORETASK_H__
#define __CORETASK_H__

#include <nu_swilib.h>
#include <stddef.h>

#define DEFAULT_STACK_SIZE 0x4000
#define DEFAULT_PRIO 90

typedef struct
{
    NU_TASK *task;
    void *stack;
    char is_stack_freeable;
    unsigned int stack_size;
    NU_QUEUE *events;
    void *mem;
    char event_stop, type;
    short id;
}CoreTask;



typedef struct
{
    int prio;
    unsigned int stack_size;
    void *stack;
    char is_stack_freeable;
}TaskConf;


void initTaskConf(TaskConf *conf);
void setTaskConfigStackSize(TaskConf *conf, unsigned int sz);

static inline
short getShort(const char *data)
{
#ifndef __ASM_OPT
    short val1;
    asm(
        "mov     r0, %1 \n"
        "ldrb    r1, [r0, #1] \n"
        "lsl     r1, #8 \n"
        "ldrb    r0, [r0, #0] \n"
        "orr     %0, r0, r1 \n"
        :"=r"(val1)
        :"r"(data)
        :"r0", "r1", "r2"
    );
    return val1;
#else
    return data[1] << 8 | data[0];
#endif
}


#ifndef printf
extern void print(int, const char *);
#define printf(fmt, ...) { extern char _debug_data[4*1024]; extern void printLock(); extern void printUnLock(); \
 printLock(); int __sz__ = sprintf(_debug_data, fmt, ##__VA_ARGS__); print(__sz__, _debug_data); printUnLock(); }
#endif



typedef struct  CS_NODE_STRUCT
{
    struct CS_NODE_STRUCT  *cs_previous;
    struct CS_NODE_STRUCT  *cs_next;
    DATA_ELEMENT            cs_priority;

#if     PAD_1
    DATA_ELEMENT            cs_padding[PAD_1];
#endif

}  CS_NODE;

typedef struct
{
    CS_NODE             ololo;
    UNSIGNED            tc_id;                 /* Internal TCB ID        */
    CHAR                tc_name[NU_MAX_NAME];  /* Task name              */
    DATA_ELEMENT        tc_status;             /* Task status            */
    BOOLEAN             tc_delayed_suspend;    /* Delayed task suspension*/
    DATA_ELEMENT        tc_priority;           /* Task priority          */
    BOOLEAN             tc_preemption;         /* Task preemption enable */
    UNSIGNED            tc_scheduled;          /* Task scheduled count   */
    UNSIGNED            tc_cur_time_slice;     /* Current time slice     */
    VOID               *tc_stack_start;        /* Stack starting address */
    VOID               *tc_stack_end;          /* Stack ending address   */
    VOID               *tc_stack_pointer;      /* Task stack pointer     */
    UNSIGNED            tc_stack_size;         /* Task stack's size      */
    UNSIGNED            tc_stack_minimum;      /* Minimum stack size     */
    struct TC_PROTECT_STRUCT
                       *tc_current_protect;    /* Current protection     */
    VOID               *tc_saved_stack_ptr;    /* Previous stack pointer */
    UNSIGNED            tc_time_slice;         /* Task time slice value  */

    /* Information after this point is not used in the target dependent
       portion of this component.  Hence, changes in the following section
       should not impact assembly language routines.  */
    struct TC_TCB_STRUCT
                       *tc_ready_previous,     /* Previously ready TCB   */
                       *tc_ready_next;         /* next and previous ptrs */

    /* Task control information follows.  */

    UNSIGNED            tc_priority_group;     /* Priority group mask bit*/
    struct TC_TCB_STRUCT
                      **tc_priority_head;      /* Pointer to list head   */
    DATA_ELEMENT       *tc_sub_priority_ptr;   /* Pointer to sub-group   */
    DATA_ELEMENT        tc_sub_priority;       /* Mask of sub-group bit  */
    DATA_ELEMENT        tc_saved_status;       /* Previous task status   */
    BOOLEAN             tc_signal_active;      /* Signal active flag     */

#if     PAD_3
    DATA_ELEMENT        tc_padding[PAD_3];
#endif

                                               /* Task entry function    */
    VOID                (*tc_entry)(UNSIGNED, VOID *);
    UNSIGNED            tc_argc;               /* Optional task argument */
    VOID               *tc_argv;               /* Optional task argument */
} MYTASK;


#endif

