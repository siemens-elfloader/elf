
#ifndef NU_SWILIB_H
#define NU_SWILIB_H

#include <swihelper.h>

/* Nucleus PLUS RTOS API LIB,  13.01.2012 */

#define NU_SWILIB_BEGIN_NUMBER  0x300

//Типы
typedef unsigned long           UNSIGNED;
typedef long                    SIGNED;
typedef unsigned char           DATA_ELEMENT;
typedef DATA_ELEMENT            OPTION;
typedef int                     STATUS;
typedef unsigned char           UNSIGNED_CHAR;
typedef char                    CHAR;
typedef int                     INT;
typedef unsigned long *         UNSIGNED_PTR;
typedef unsigned char *         BYTE_PTR;
typedef DATA_ELEMENT            BOOLEAN;
typedef unsigned int            UNSIGNED_INT;

#define VOID void


/* Define the padding required for usage of the DATA_ELEMENT type within
   Nucleus PLUS structures.  These values insure proper alignment for the
   next structure member.  */

#define         PAD_1                           3
#define         PAD_2                           2
#define         PAD_3                           1


/* Define constants that are target dependent and/or are used for internal
   purposes.  */

#define         NU_MIN_STACK_SIZE               240
#define         NU_MAX_NAME                     8
#define         NU_MAX_VECTORS                  64
#define         NU_MAX_LISRS                    8

//Cтруктуры

#define         NU_TASK_SIZE                    42 + 50
#define         NU_HISR_SIZE                    22 + 4
#define         NU_MAILBOX_SIZE                 13 + 4
#define         NU_QUEUE_SIZE                   18 + 50
#define         NU_PIPE_SIZE                    18 + 4
#define         NU_SEMAPHORE_SIZE               10 + 4
#define         NU_EVENT_GROUP_SIZE             9  + 4
#define         NU_PARTITION_POOL_SIZE          15 + 4
#define         NU_MEMORY_POOL_SIZE             17 + 4
#define         NU_TIMER_SIZE                   17 + 4
#define         NU_PROTECT_SIZE                 2  + 4
#define         NU_DRIVER_SIZE                  3  + 4

typedef struct NU_TASK_STRUCT
{
    UNSIGNED      words[NU_TASK_SIZE];
} NU_TASK;

typedef struct NU_MAILBOX_STRUCT
{
    UNSIGNED      words[NU_MAILBOX_SIZE];
} NU_MAILBOX;

typedef struct NU_QUEUE_STRUCT
{
    UNSIGNED      words[NU_QUEUE_SIZE];
} NU_QUEUE;

typedef struct NU_PIPE_STRUCT
{
    UNSIGNED      words[NU_PIPE_SIZE];
} NU_PIPE;

typedef struct NU_SEMAPHORE_STRUCT
{
    UNSIGNED      words[NU_SEMAPHORE_SIZE];
} NU_SEMAPHORE;

typedef struct NU_EVENT_GROUP_STRUCT
{
    UNSIGNED      words[NU_EVENT_GROUP_SIZE];
} NU_EVENT_GROUP;

typedef struct NU_PARTITION_POOL_STRUCT
{
    UNSIGNED       words[NU_PARTITION_POOL_SIZE];
} NU_PARTITION_POOL;

typedef struct NU_MEMORY_POOL_STRUCT
{
    UNSIGNED      words[NU_MEMORY_POOL_SIZE];
} NU_MEMORY_POOL;

typedef struct NU_HISR_STRUCT
{
    UNSIGNED      words[NU_HISR_SIZE];
} NU_HISR;

typedef struct NU_PROTECT_STRUCT
{
    UNSIGNED      words[NU_PROTECT_SIZE];
} NU_PROTECT;

typedef struct NU_TIMER_STRUCT
{
    UNSIGNED       words[NU_TIMER_SIZE];
} NU_TIMER;

/* Define I/O driver request structures.  */

struct NU_INITIALIZE_STRUCT
{
    VOID       *nu_io_address;              /* Base IO address          */
    UNSIGNED    nu_logical_units;           /* Number of logical units  */
    VOID       *nu_memory;                  /* Generic memory pointer   */
    INT         nu_vector;                  /* Interrupt vector number  */
};

struct NU_ASSIGN_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    INT         nu_assign_info;             /* Additional assign info   */
};

struct NU_RELEASE_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    INT         nu_release_info;            /* Additional release info  */
};

struct NU_INPUT_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    UNSIGNED    nu_offset;                  /* Offset of input          */
    UNSIGNED    nu_request_size;            /* Requested input size     */
    UNSIGNED    nu_actual_size;             /* Actual input size        */
    VOID       *nu_buffer_ptr;              /* Input buffer pointer     */
};

struct NU_OUTPUT_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    UNSIGNED    nu_offset;                  /* Offset of output         */
    UNSIGNED    nu_request_size;            /* Requested output size    */
    UNSIGNED    nu_actual_size;             /* Actual output size       */
    VOID       *nu_buffer_ptr;              /* Output buffer pointer    */
};

struct NU_STATUS_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    VOID       *nu_extra_status;            /* Additional status ptr    */
};

struct NU_TERMINATE_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
};


typedef  union NU_REQUEST_INFO_UNION
{
    struct NU_INITIALIZE_STRUCT     nu_initialize;
    struct NU_ASSIGN_STRUCT         nu_assign;
    struct NU_RELEASE_STRUCT        nu_release;
    struct NU_INPUT_STRUCT          nu_input;
    struct NU_OUTPUT_STRUCT         nu_output;
    struct NU_STATUS_STRUCT         nu_status;
    struct NU_TERMINATE_STRUCT      nu_terminate;
} nu_request_info_union;

typedef struct NU_DRIVER_REQUEST_STRUCT
{
    INT                   nu_function;                /* I/O request function     */
    UNSIGNED              nu_timeout;                 /* Timeout on request       */
    STATUS                nu_status;                  /* Status of request        */
    UNSIGNED              nu_supplemental;            /* Supplemental information */
    VOID                 *nu_supplemental_ptr;        /* Supplemental info pointer*/
    nu_request_info_union nu_request_info;

} NU_DRIVER_REQUEST;

typedef struct NU_DRIVER_STRUCT
{
    UNSIGNED       words[NU_DRIVER_SIZE];      /* CS_NODE_STRUCT */
    CHAR           nu_driver_name[NU_MAX_NAME];
    VOID          *nu_info_ptr;
    UNSIGNED       nu_driver_id;
    VOID           (*nu_driver_entry)(struct NU_DRIVER_STRUCT *,
                                                NU_DRIVER_REQUEST *);
} NU_DRIVER;


/* Define task suspension constants.  */

#define         NU_DRIVER_SUSPEND               10
#define         NU_EVENT_SUSPEND                7
#define         NU_FINISHED                     11
#define         NU_MAILBOX_SUSPEND              3
#define         NU_MEMORY_SUSPEND               9
#define         NU_PARTITION_SUSPEND            8
#define         NU_PIPE_SUSPEND                 5
#define         NU_PURE_SUSPEND                 1
#define         NU_QUEUE_SUSPEND                4
#define         NU_READY                        0
#define         NU_SEMAPHORE_SUSPEND            6
#define         NU_SLEEP_SUSPEND                2
#define         NU_TERMINATED                   12

/* Define constants for use in service parameters.  */

#define         NU_AND                          2
#define         NU_AND_CONSUME                  3
#define         NU_DISABLE_TIMER                4
#define         NU_ENABLE_TIMER                 5
#define         NU_FALSE                        0
#define         NU_FIFO                         6
#define         NU_FIXED_SIZE                   7
#define         NU_NO_PREEMPT                   8
#define         NU_NO_START                     9
#define         NU_NO_SUSPEND                   0
#define         NU_NULL                         0
#define         NU_OR                           0
#define         NU_OR_CONSUME                   1
#define         NU_PREEMPT                      10
#define         NU_PRIORITY                     11
#define         NU_START                        12
#define         NU_SUSPEND                      0xFFFFFFFFUL
#define         NU_TRUE                         1
#define         NU_VARIABLE_SIZE                13

/* Define service completion status constants.  */

#define         NU_SUCCESS                      0
#define         NU_END_OF_LOG                   -1
#define         NU_GROUP_DELETED                -2
#define         NU_INVALID_DELETE               -3
#define         NU_INVALID_DRIVER               -4
#define         NU_INVALID_ENABLE               -5
#define         NU_INVALID_ENTRY                -6
#define         NU_INVALID_FUNCTION             -7
#define         NU_INVALID_GROUP                -8
#define         NU_INVALID_HISR                 -9
#define         NU_INVALID_MAILBOX              -10
#define         NU_INVALID_MEMORY               -11
#define         NU_INVALID_MESSAGE              -12
#define         NU_INVALID_OPERATION            -13
#define         NU_INVALID_PIPE                 -14
#define         NU_INVALID_POINTER              -15
#define         NU_INVALID_POOL                 -16
#define         NU_INVALID_PREEMPT              -17
#define         NU_INVALID_PRIORITY             -18
#define         NU_INVALID_QUEUE                -19
#define         NU_INVALID_RESUME               -20
#define         NU_INVALID_SEMAPHORE            -21
#define         NU_INVALID_SIZE                 -22
#define         NU_INVALID_START                -23
#define         NU_INVALID_SUSPEND              -24
#define         NU_INVALID_TASK                 -25
#define         NU_INVALID_TIMER                -26
#define         NU_INVALID_VECTOR               -27
#define         NU_MAILBOX_DELETED              -28
#define         NU_MAILBOX_EMPTY                -29
#define         NU_MAILBOX_FULL                 -30
#define         NU_MAILBOX_RESET                -31
#define         NU_NO_MEMORY                    -32
#define         NU_NO_MORE_LISRS                -33
#define         NU_NO_PARTITION                 -34
#define         NU_NOT_DISABLED                 -35
#define         NU_NOT_PRESENT                  -36
#define         NU_NOT_REGISTERED               -37
#define         NU_NOT_TERMINATED               -38
#define         NU_PIPE_DELETED                 -39
#define         NU_PIPE_EMPTY                   -40
#define         NU_PIPE_FULL                    -41
#define         NU_PIPE_RESET                   -42
#define         NU_POOL_DELETED                 -43
#define         NU_QUEUE_DELETED                -44
#define         NU_QUEUE_EMPTY                  -45
#define         NU_QUEUE_FULL                   -46
#define         NU_QUEUE_RESET                  -47
#define         NU_SEMAPHORE_DELETED            -48
#define         NU_SEMAPHORE_RESET              -49
#define         NU_TIMEOUT                      -50
#define         NU_UNAVAILABLE                  -51
#define         NU_INVALID_DESCRIPTION          -52
#define         NU_INVALID_REGION               -53
#define         NU_MEMORY_CORRUPT               -54
#define         NU_INVALID_DEBUG_ALLOCATION     -55
#define         NU_EMPTY_DEBUG_ALLOCATION_LIST  -56

/* Define system errors.  */

#define         NU_ERROR_CREATING_TIMER_HISR    1
#define         NU_ERROR_CREATING_TIMER_TASK    2
#define         NU_STACK_OVERFLOW               3
#define         NU_UNHANDLED_INTERRUPT          4


/* Define I/O driver constants.  */

#define         NU_IO_ERROR                     -1
#define         NU_INITIALIZE                   1
#define         NU_ASSIGN                       2
#define         NU_RELEASE                      3
#define         NU_INPUT                        4
#define         NU_OUTPUT                       5
#define         NU_STATUS                       6
#define         NU_TERMINATE                    7


/* Define history entry IDs.  */

#define         NU_USER_ID                      1
#define         NU_CREATE_TASK_ID               2
#define         NU_DELETE_TASK_ID               3
#define         NU_RESET_TASK_ID                4
#define         NU_TERMINATE_TASK_ID            5
#define         NU_RESUME_TASK_ID               6
#define         NU_SUSPEND_TASK_ID              7
#define         NU_RELINQUISH_ID                8
#define         NU_SLEEP_ID                     9
#define         NU_CHANGE_PRIORITY_ID           10
#define         NU_CHANGE_PREEMPTION_ID         11
#define         NU_CREATE_MAILBOX_ID            12
#define         NU_DELETE_MAILBOX_ID            13
#define         NU_RESET_MAILBOX_ID             14
#define         NU_SEND_TO_MAILBOX_ID           15
#define         NU_BROADCAST_TO_MAILBOX_ID      16
#define         NU_RECEIVE_FROM_MAILBOX_ID      17
#define         NU_CREATE_QUEUE_ID              18
#define         NU_DELETE_QUEUE_ID              19
#define         NU_RESET_QUEUE_ID               20
#define         NU_SEND_TO_FRONT_OF_QUEUE_ID    21
#define         NU_SEND_TO_QUEUE_ID             22
#define         NU_BROADCAST_TO_QUEUE_ID        23
#define         NU_RECEIVE_FROM_QUEUE_ID        24
#define         NU_CREATE_PIPE_ID               25
#define         NU_DELETE_PIPE_ID               26
#define         NU_RESET_PIPE_ID                27
#define         NU_SEND_TO_FRONT_OF_PIPE_ID     28
#define         NU_SEND_TO_PIPE_ID              29
#define         NU_BROADCAST_TO_PIPE_ID         30
#define         NU_RECEIVE_FROM_PIPE_ID         31
#define         NU_CREATE_SEMAPHORE_ID          32
#define         NU_DELETE_SEMAPHORE_ID          33
#define         NU_RESET_SEMAPHORE_ID           34
#define         NU_OBTAIN_SEMAPHORE_ID          35
#define         NU_RELEASE_SEMAPHORE_ID         36
#define         NU_CREATE_EVENT_GROUP_ID        37
#define         NU_DELETE_EVENT_GROUP_ID        38
#define         NU_SET_EVENTS_ID                39
#define         NU_RETRIEVE_EVENTS_ID           40
#define         NU_CREATE_PARTITION_POOL_ID     41
#define         NU_DELETE_PARTITION_POOL_ID     42
#define         NU_ALLOCATE_PARTITION_ID        43
#define         NU_DEALLOCATE_PARTITION_ID      44
#define         NU_CREATE_MEMORY_POOL_ID        45
#define         NU_DELETE_MEMORY_POOL_ID        46
#define         NU_ALLOCATE_MEMORY_ID           47
#define         NU_DEALLOCATE_MEMORY_ID         48
#define         NU_CONTROL_SIGNALS_ID           49
#define         NU_RECEIVE_SIGNALS_ID           50
#define         NU_REGISTER_SIGNAL_HANDLER_ID   51
#define         NU_SEND_SIGNALS_ID              52
#define         NU_REGISTER_LISR_ID             53
#define         NU_CREATE_HISR_ID               54
#define         NU_DELETE_HISR_ID               55
#define         NU_CREATE_TIMER_ID              56
#define         NU_DELETE_TIMER_ID              57
#define         NU_CONTROL_TIMER_ID             58
#define         NU_RESET_TIMER_ID               59
#define         NU_CREATE_DRIVER_ID             60
#define         NU_DELETE_DRIVER_ID             61
#define         NU_REQUEST_DRIVER_ID            62
#define         NU_RESUME_DRIVER_ID             63
#define         NU_SUSPEND_DRIVER_ID            64
#define         NU_CHANGE_TIME_SLICE_ID         65
#define         NU_ASSERT_ID                    66
#define         NU_ALLOCATE_ALIGNED_ID          67



/* Работа с задачами / Define task control functions */

__inl
int NU_Create_Task(NU_TASK *task, CHAR *name,
                                    void (*task_entry)(int, void *), unsigned long argc,
                                    void *argv, void *stack_address, unsigned long stack_size,
                                    OPTION priority, unsigned long time_slice,
                                    OPTION preempt, OPTION auto_start)
__def( NU_SWILIB_BEGIN_NUMBER+0x00, int, task, name, task_entry, argc, argv, stack_address, stack_size, priority, time_slice, preempt, auto_start)

__inl
int NU_Delete_Task(NU_TASK *task)
__def( NU_SWILIB_BEGIN_NUMBER+0x01, int, task)

__inl
int NU_Reset_Task(NU_TASK *task, unsigned long argc, void *argv)
__def( NU_SWILIB_BEGIN_NUMBER+0x02, int, task, argc, argv)

__inl
int NU_Terminate_Task(NU_TASK *task)
__def( NU_SWILIB_BEGIN_NUMBER+0x03, int, task)

__inl
int NU_Resume_Task(NU_TASK *task)
__def( NU_SWILIB_BEGIN_NUMBER+0x04, int, task)

__inl
int NU_Suspend_Task(NU_TASK *task)
__def( NU_SWILIB_BEGIN_NUMBER+0x05, int, task)

__inl
void NU_Relinquish(void)
__defn( NU_SWILIB_BEGIN_NUMBER+0x06)

__inl
void NU_Sleep(unsigned long ticks)
__defn( NU_SWILIB_BEGIN_NUMBER+0x07, ticks)

__inl
OPTION NU_Change_Priority(NU_TASK *task, OPTION new_priority)
__def( NU_SWILIB_BEGIN_NUMBER+0x08, OPTION, task, new_priority)

__inl
OPTION NU_Change_Preemption(OPTION preempt)
__def( NU_SWILIB_BEGIN_NUMBER+0x09, OPTION, preempt)

__inl
unsigned long NU_Change_Time_Slice(NU_TASK *task, unsigned long time_slice)
__def( NU_SWILIB_BEGIN_NUMBER+0x0A, unsigned long, task, time_slice)

__inl
unsigned long NU_Check_Stack(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x0B, unsigned long)

__inl
NU_TASK  *NU_Current_Task_Pointer(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x0C, NU_TASK  *)

__inl
unsigned long NU_Established_Tasks(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x0D, unsigned long)

__inl
int NU_Task_Information(NU_TASK *task, CHAR *name,
                                          DATA_ELEMENT *status, unsigned long *scheduled_count,
                                          OPTION *priority, OPTION *preempt,
                                          unsigned long *time_slice, void **stack_base,
                                          unsigned long *stack_size, unsigned long *minimum_stack)
__def( NU_SWILIB_BEGIN_NUMBER+0x0E, int, task, name, status, scheduled_count, priority, preempt,
      time_slice, stack_base, stack_size, minimum_stack)

__inl
unsigned long NU_Task_Pointers(NU_TASK **pointer_list,
                                       unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x0F, unsigned long, pointer_list, maximum_pointers)



/* Работа с почтовыми ящиками / Define Mailbox management functions */

__inl
int NU_Create_Mailbox(NU_MAILBOX *mailbox, CHAR *name, OPTION suspend_type)
__def( NU_SWILIB_BEGIN_NUMBER+0x10, int, mailbox, name, suspend_type)

__inl
int NU_Delete_Mailbox(NU_MAILBOX *mailbox)
__def( NU_SWILIB_BEGIN_NUMBER+0x11, int, mailbox)

__inl
int NU_Reset_Mailbox(NU_MAILBOX *mailbox)
__def( NU_SWILIB_BEGIN_NUMBER+0x12, int, mailbox)

__inl
int NU_Send_To_Mailbox(NU_MAILBOX *mailbox, void *message,
                                         unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x13, int, mailbox, message, suspend)

__inl
int NU_Broadcast_To_Mailbox(NU_MAILBOX *mailbox, void *message,
                                              unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x14, int, mailbox, message, suspend)

__inl
int NU_Receive_From_Mailbox(NU_MAILBOX *mailbox, void *message,
                                              unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x15, int, mailbox, message, suspend)

__inl
unsigned long NU_Established_Mailboxes(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x16, unsigned long)

__inl
int NU_Mailbox_Information(NU_MAILBOX *mailbox, CHAR *name,
                                             OPTION *suspend_type, OPTION *message_present,
                                             unsigned long *tasks_waiting, NU_TASK **first_task)
__def( NU_SWILIB_BEGIN_NUMBER+0x17, int, mailbox, name, suspend_type, message_present, tasks_waiting, first_task)

__inl
unsigned long NU_Mailbox_Pointers(NU_MAILBOX **pointer_list,  unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x18, unsigned long, pointer_list, maximum_pointers)



/* Работа с очередьми / Define Queue management functions */

__inl
int NU_Create_Queue(NU_QUEUE *queue, CHAR *name,
                                      void *start_address, unsigned long queue_size,
                                      OPTION message_type, unsigned long message_size,
                                      OPTION suspend_type)
__def( NU_SWILIB_BEGIN_NUMBER+0x19, int, queue, name, start_address, queue_size, message_type, message_size, suspend_type)

__inl
int NU_Delete_Queue(NU_QUEUE *queue)
__def( NU_SWILIB_BEGIN_NUMBER+0x1A, int, queue)

__inl
int NU_Reset_Queue(NU_QUEUE *queue)
__def( NU_SWILIB_BEGIN_NUMBER+0x1B, int, queue)

__inl
int NU_Send_To_Front_Of_Queue(NU_QUEUE *queue, void *message,
                                                unsigned long size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x1C, int, queue, message, size, suspend)

__inl
int NU_Send_To_Queue(NU_QUEUE *queue, void *message,
                                       unsigned long size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x1D, int, queue, message, size, suspend)

__inl
int NU_Broadcast_To_Queue(NU_QUEUE *queue, void *message,
                                            unsigned long size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x1E, int, queue, message, size, suspend)

__inl
int NU_Receive_From_Queue(NU_QUEUE *queue, void *message,
                                            unsigned long size, unsigned long *actual_size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x1F, int, queue, message, size, actual_size, suspend)

__inl
unsigned long NU_Established_Queues(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x20, unsigned long)

__inl
int NU_Queue_Information(NU_QUEUE *queue, CHAR *name,
                                           void **start_address, unsigned long *queue_size,
                                           unsigned long *available, unsigned long *messages,
                                           OPTION *message_type, unsigned long *message_size,
                                           OPTION *suspend_type, unsigned long *tasks_waiting,
                                           NU_TASK **first_task)
__def( NU_SWILIB_BEGIN_NUMBER+0x21, int, queue, name, start_address, queue_size, available, messages, message_type, message_size, suspend_type, tasks_waiting, first_task)

__inl
unsigned long NU_Queue_Pointers(NU_QUEUE **pointer_list,
                                         unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x22, unsigned long, pointer_list, maximum_pointers)



/* Работа с каналами / Define Pipe management functions */
/*
__inl
int NU_Create_Pipe(NU_PIPE *pipe, CHAR *name,
                                     void *start_address, unsigned long pipe_size,
                                     OPTION message_type, unsigned long message_size,
                                     OPTION suspend_type)
__def( NU_SWILIB_BEGIN_NUMBER+0x23, int, pipe, name, start_address, pipe_size, message_type, message_size, suspend_type)

__inl
int NU_Delete_Pipe(NU_PIPE *pipe)
__def( NU_SWILIB_BEGIN_NUMBER+0x24, int, pipe)

__inl
int NU_Reset_Pipe(NU_PIPE *pipe)
__def( NU_SWILIB_BEGIN_NUMBER+0x25, int, pipe)

__inl
int NU_Send_To_Front_Of_Pipe(NU_PIPE *pipe, void *message,
                                               unsigned long size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x26, int, pipe, message, size, suspend)

__inl
int NU_Send_To_Pipe(NU_PIPE *pipe, void *message,
                                      unsigned long size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x27, int, pipe, message, size, suspend)

__inl
int NU_Broadcast_To_Pipe(NU_PIPE *pipe, void *message,
                                           unsigned long size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x28, int, pipe, message, size, suspend)

__inl
int NU_Receive_From_Pipe(NU_PIPE *pipe, void *message,
                                           unsigned long size, unsigned long *actual_size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x29, int, pipe, message, size, actual_size, suspend)

__inl
unsigned long NU_Established_Pipes(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x2A, unsigned long)

__inl
int NU_Pipe_Information(NU_PIPE *pipe, CHAR *name,
                                          void **start_address, unsigned long *pipe_size,
                                          unsigned long *available, unsigned long *messages,
                                          OPTION *message_type, unsigned long *message_size,
                                          OPTION *suspend_type, unsigned long *tasks_waiting,
                                          NU_TASK **first_task)
__def( NU_SWILIB_BEGIN_NUMBER+0x2B, int, pipe, name, start_address, pipe_size, available, messages, message_type, message_size, suspend_type, tasks_waiting, first_task)

__inl
unsigned long NU_Pipe_Pointers(NU_PIPE **pointer_list,
                                                unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x2C, unsigned long, pointer_list, maximum_pointers)
*/


/* Работа с cемафорами / Define Semaphore management functions */

__inl
int NU_Create_Semaphore(NU_SEMAPHORE *semaphore, CHAR *name,
                                          unsigned long initial_count, OPTION suspend_type)
__def( NU_SWILIB_BEGIN_NUMBER+0x2D, int, semaphore, name, initial_count, suspend_type)

__inl
int NU_Delete_Semaphore(NU_SEMAPHORE *semaphore)
__def( NU_SWILIB_BEGIN_NUMBER+0x2E, int, semaphore)

__inl
int NU_Reset_Semaphore(NU_SEMAPHORE *semaphore, unsigned long initial_count)
__def( NU_SWILIB_BEGIN_NUMBER+0x2F, int, semaphore, initial_count)

__inl
int NU_Obtain_Semaphore(NU_SEMAPHORE *semaphore, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x30, int, semaphore, suspend)

__inl
int NU_Release_Semaphore(NU_SEMAPHORE *semaphore)
__def( NU_SWILIB_BEGIN_NUMBER+0x31, int, semaphore)

__inl
unsigned long NU_Established_Semaphores(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x32, unsigned long)

__inl
int NU_Semaphore_Information(NU_SEMAPHORE *semaphore, CHAR *name,
                                               unsigned long *current_count, OPTION *suspend_type,
                                               unsigned long *tasks_waiting, NU_TASK **first_task)
__def( NU_SWILIB_BEGIN_NUMBER+0x33, int, semaphore, name, current_count, suspend_type, tasks_waiting, first_task)

__inl
unsigned long NU_Semaphore_Pointers(NU_SEMAPHORE **pointer_list,
                                                unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x34, unsigned long, pointer_list, maximum_pointers)



/* Работа с группами событий / Define Event Group management functions */

__inl
int NU_Create_Event_Group(NU_EVENT_GROUP *group, CHAR *name)
__def( NU_SWILIB_BEGIN_NUMBER+0x35, int, group, name)

__inl
int NU_Delete_Event_Group(NU_EVENT_GROUP *group)
__def( NU_SWILIB_BEGIN_NUMBER+0x36, int, group)

__inl
int NU_Set_Events(NU_EVENT_GROUP *group, unsigned long events, OPTION operation)
__def( NU_SWILIB_BEGIN_NUMBER+0x37, int, group, events, operation)

__inl
int NU_Retrieve_Events(NU_EVENT_GROUP *group,
                                         unsigned long requested_flags, OPTION operation,
                                         unsigned long *retrieved_flags, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x38, int, group, requested_flags, operation, retrieved_flags, suspend)

__inl
unsigned long NU_Established_Event_Groups(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x39, unsigned long)

__inl
int NU_Event_Group_Information(NU_EVENT_GROUP *group, CHAR *name,
                                                 unsigned long *event_flags, unsigned long *tasks_waiting,
                                                 NU_TASK **first_task)
__def( NU_SWILIB_BEGIN_NUMBER+0x3A, int, group, name, event_flags, tasks_waiting, first_task)

__inl
unsigned long NU_Event_Group_Pointers(NU_EVENT_GROUP **pointer_list,
                                              unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x3B, unsigned long, pointer_list, maximum_pointers)



/* Работа с сигналами / Define Signal processing functions */

__inl
unsigned long NU_Control_Signals(unsigned long signal_enable_mask)
__def( NU_SWILIB_BEGIN_NUMBER+0x3C, unsigned long, signal_enable_mask)

__inl
unsigned long NU_Receive_Signals(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x3D, unsigned long)

__inl
STATUS NU_Register_Signal_Handler(void (*signal_handler)(unsigned long))
__def( NU_SWILIB_BEGIN_NUMBER+0x3E, STATUS, signal_handler)

__inl
STATUS NU_Send_Signals(NU_TASK *task, unsigned long signals)
__def( NU_SWILIB_BEGIN_NUMBER+0x3F, STATUS, task, signals)



/* Работа с областями фрагментного захвата памяти / Define Partition memory management functions */

__inl
int NU_Create_Partition_Pool(NU_PARTITION_POOL *pool, CHAR *name,
                                               void *start_address, unsigned long pool_size,
                                               unsigned long partition_size, OPTION suspend_type)
__def( NU_SWILIB_BEGIN_NUMBER+0x40, int, pool, name, start_address, pool_size, partition_size, suspend_type)

__inl
int NU_Delete_Partition_Pool(NU_PARTITION_POOL *pool)
__def( NU_SWILIB_BEGIN_NUMBER+0x41, int, pool)

__inl
int NU_Allocate_Partition(NU_PARTITION_POOL *pool,
                                            void **return_pointer, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x42, int, pool, return_pointer, suspend)

__inl
int NU_Deallocate_Partition(void *partition)
__def( NU_SWILIB_BEGIN_NUMBER+0x43, int, partition)

__inl
unsigned long NU_Established_Partition_Pools(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x44, unsigned long)

__inl
int NU_Partition_Pool_Information(NU_PARTITION_POOL *pool,
                                                    CHAR *name,
                                                    void **start_address, unsigned long *pool_size,
                                                    unsigned long *partition_size, unsigned long *available,
                                                    unsigned long *allocated, OPTION *suspend_type,
                                                    unsigned long *tasks_waiting, NU_TASK **first_task)
__def( NU_SWILIB_BEGIN_NUMBER+0x45, int, pool, name, start_address, pool_size, partition_size, available, allocated, suspend_type, tasks_waiting, first_task)

__inl
unsigned long NU_Partition_Pool_Pointers(NU_PARTITION_POOL **pointer_list,
                                                 unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x46, unsigned long, pointer_list, maximum_pointers)



/* Работа с областями динамического захвата памяти /  Define Dynamic memory management functions */

__inl
int NU_Create_Memory_Pool(NU_MEMORY_POOL *pool, CHAR *name,
                                            void *start_address, unsigned long pool_size,
                                            unsigned long min_allocation, OPTION suspend_type)
__def( NU_SWILIB_BEGIN_NUMBER+0x47, int, pool, name, start_address, pool_size, min_allocation, suspend_type)

__inl
int NU_Delete_Memory_Pool(NU_MEMORY_POOL *pool)
__def( NU_SWILIB_BEGIN_NUMBER+0x48, int, pool)

__inl
int NU_Allocate_Memory(NU_MEMORY_POOL *pool, void **return_pointer,
                                         unsigned long size, unsigned long suspend)
__def( NU_SWILIB_BEGIN_NUMBER+0x49, int, pool, return_pointer, size, suspend)

__inl
int NU_Deallocate_Memory(void *memory)
__def( NU_SWILIB_BEGIN_NUMBER+0x4A, int, memory)

__inl
unsigned long NU_Established_Memory_Pools(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x4B, unsigned long)

__inl
int NU_Memory_Pool_Information(NU_MEMORY_POOL *pool, CHAR *name,
                                                 void **start_address, unsigned long *pool_size,
                                                 unsigned long *min_allocation, unsigned long *available,
                                                 OPTION *suspend_type, unsigned long *tasks_waiting,
                                                 NU_TASK **first_task)
__def( NU_SWILIB_BEGIN_NUMBER+0x4C, int, pool, name, start_address, pool_size, min_allocation, available, suspend_type, tasks_waiting, first_task)

__inl
unsigned long NU_Memory_Pool_Pointers(NU_MEMORY_POOL **pointer_list,
                                              unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x4D, unsigned long, pointer_list, maximum_pointers)



/* Работа с прерываниями / Define Interrupt management functions */

__inl
int NU_Control_Interrupts(INT new_level)
__def( NU_SWILIB_BEGIN_NUMBER+0x4E, int, new_level)

__inl
int NU_Local_Control_Interrupts(INT new_level)
__def( NU_SWILIB_BEGIN_NUMBER+0x4F, int, new_level)

__inl
void NU_Restore_Interrupts(void)
__defn( NU_SWILIB_BEGIN_NUMBER+0x50)

__inl
void *NU_Setup_Vector(INT vector, void *new_vector)
__def( NU_SWILIB_BEGIN_NUMBER+0x51, void *, vector, new_vector)

__inl
int NU_Register_LISR(INT vector, void (*new_lisr)(INT),  void (**old_lisr)(INT))
__def( NU_SWILIB_BEGIN_NUMBER+0x52, int, vector, new_lisr, old_lisr)

__inl
int NU_Activate_HISR(NU_HISR *hisr)
__def( NU_SWILIB_BEGIN_NUMBER+0x53, int, hisr)

__inl
int NU_Create_HISR(NU_HISR *hisr, CHAR *name, void (*hisr_entry)(void), OPTION priority,
                                     void *stack_address, unsigned long stack_size)
__def( NU_SWILIB_BEGIN_NUMBER+0x54, int, hisr, name, hisr_entry, priority, stack_address, stack_size)

__inl
int NU_Delete_HISR(NU_HISR *hisr)
__def( NU_SWILIB_BEGIN_NUMBER+0x55, int, hisr)

__inl
NU_HISR  *NU_Current_HISR_Pointer(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x56, NU_HISR  *)

__inl
unsigned long NU_Established_HISRs(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x57, unsigned long)

__inl
int NU_HISR_Information(NU_HISR *hisr, CHAR *name,
                                          unsigned long *scheduled_count, DATA_ELEMENT *priority,
                                          void **stack_base, unsigned long *stack_size,
                                          unsigned long *minimum_stack)
__def( NU_SWILIB_BEGIN_NUMBER+0x58, int, hisr, name, scheduled_count, priority, stack_base, stack_size, minimum_stack)

__inl
unsigned long NU_HISR_Pointers(NU_HISR **pointer_list,  unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x59, unsigned long, pointer_list, maximum_pointers)

__inl
void NU_Protect(NU_PROTECT *protect_struct)
__defn( NU_SWILIB_BEGIN_NUMBER+0x5A, protect_struct)

__inl
void NU_Unprotect(void)
__defn( NU_SWILIB_BEGIN_NUMBER+0x5B)



/* Работа с таймерами  / Timer management functions */

__inl
int NU_Create_Timer(NU_TIMER *timer, CHAR *name,
                                  void (*expiration_routine)(unsigned long), unsigned long id,
                                  unsigned long initial_time, unsigned long reschedule_time,
                                  OPTION enable)
__def( NU_SWILIB_BEGIN_NUMBER+0x5C, int, timer, name, expiration_routine, id, initial_time, reschedule_time, enable)

__inl
int NU_Delete_Timer(NU_TIMER *timer)
__def( NU_SWILIB_BEGIN_NUMBER+0x5D, int, timer)

__inl
int NU_Reset_Timer(NU_TIMER *timer,
                                 void (*expiration_routine)(unsigned long),
                                 unsigned long initial_time, unsigned long reschedule_timer,
                                 OPTION enable)
__def( NU_SWILIB_BEGIN_NUMBER+0x5E, int, timer, expiration_routine, initial_time, reschedule_timer, enable)

__inl
int NU_Control_Timer(NU_TIMER *timer, OPTION enable)
__def( NU_SWILIB_BEGIN_NUMBER+0x5F, int, timer, enable)

__inl
unsigned long  NU_Established_Timers(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x60, unsigned long )

__inl
int NU_Timer_Information(NU_TIMER *timer, CHAR *name,
                                       OPTION *enable, unsigned long *expirations, unsigned long *id,
                                       unsigned long *initial_time, unsigned long *reschedule_time)
__def( NU_SWILIB_BEGIN_NUMBER+0x61, int, timer, name, enable, expirations, id, initial_time, reschedule_time)

__inl
unsigned long NU_Timer_Pointers(NU_TIMER **pointer_list,
                                    unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x62, unsigned long, pointer_list, maximum_pointers)

__inl
void  NU_Set_Clock(unsigned long new_value)
__defn( NU_SWILIB_BEGIN_NUMBER+0x63, new_value)

__inl
unsigned long NU_Retrieve_Clock(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x64, unsigned long)



/* Различные ф-ии для разработчиков / Development support functions */

__inl
char *NU_Release_Information(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x65, char *)

__inl
char *NU_License_Information(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x66, char *)

__inl
void NU_Disable_History_Saving(void)
__defn( NU_SWILIB_BEGIN_NUMBER+0x67)

__inl
void NU_Enable_History_Saving(void)
__defn( NU_SWILIB_BEGIN_NUMBER+0x68)

__inl
void NU_Make_History_Entry(unsigned long param1, unsigned long param2, unsigned long param3)
__defn( NU_SWILIB_BEGIN_NUMBER+0x69, param1, param2, param3)

__inl
int NU_Retrieve_History_Entry(DATA_ELEMENT *id,
                                                 unsigned long *param1, unsigned long *param2, unsigned long *param3,
                                                 unsigned long *time, NU_TASK **task, NU_HISR **hisr)
__def( NU_SWILIB_BEGIN_NUMBER+0x6A, int, id, param1, param2, param3, time, task, hisr)



/* Работа с драйверами / Input/Output Driver functions */

__inl
int NU_Create_Driver(NU_DRIVER *driver, CHAR *name,
                                       void (*driver_entry)(NU_DRIVER *, NU_DRIVER_REQUEST *))
__def( NU_SWILIB_BEGIN_NUMBER+0x6B, int, driver, name, driver_entry)

__inl
int NU_Delete_Driver(NU_DRIVER *driver)
__def( NU_SWILIB_BEGIN_NUMBER+0x6C, int, driver)

__inl
int NU_Request_Driver(NU_DRIVER *driver,  NU_DRIVER_REQUEST *request)
__def( NU_SWILIB_BEGIN_NUMBER+0x6D, int, driver, request)

__inl
int NU_Resume_Driver(NU_TASK *task)
__def( NU_SWILIB_BEGIN_NUMBER+0x6E, int, task)

__inl
int NU_Suspend_Driver(void (*terminate_routine)(void *),
                                        void *information, unsigned long timeout)
__def( NU_SWILIB_BEGIN_NUMBER+0x6F, int, terminate_routine, information, timeout)

__inl
unsigned long NU_Established_Drivers(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x70, unsigned long)

__inl
unsigned long NU_Driver_Pointers(NU_DRIVER **pointer_list,
                                                unsigned long maximum_pointers)
__def( NU_SWILIB_BEGIN_NUMBER+0x71, unsigned long, pointer_list, maximum_pointers)



/* Установка управляющего и пользовательского режимом / Define Supervisor and User mode functions */

__inl
unsigned long NU_IS_SUPERVISOR_MODE()
__def( NU_SWILIB_BEGIN_NUMBER+0x72, unsigned long)

__inl
void NU_SUPERVISOR_MODE(unsigned long nu_svc_usr_var)
__defn( NU_SWILIB_BEGIN_NUMBER+0x73, nu_svc_usr_var)

__inl
void NU_USER_MODE(unsigned long nu_svc_usr_var)
__defn( NU_SWILIB_BEGIN_NUMBER+0x74, nu_svc_usr_var)

__inl
unsigned long NU_SUPERV_USER_VARIABLES(void)
__def( NU_SWILIB_BEGIN_NUMBER+0x8075, unsigned long)


#endif
