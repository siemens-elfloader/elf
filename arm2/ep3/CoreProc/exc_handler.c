
#include <spl/exc_handler.h>
#include <spl/process.h>
#include <spl/coreevent.h>
#include "helperproc.h"


/*
 * NOTE
 * Весь интерфейс, отвечающий за отлов исключений был написан Dimadze
 */

/* Область стеков и переменнных для указателей на стандартные обработчики */

unsigned int da_def_handler = 0;
unsigned int pa_def_handler = 0;
unsigned int ui_def_handler = 0;

unsigned int swi2_def_jumper = 0;
unsigned int swi3_def_jumper = 0;

char abt_stack[ABORT_STACK_SIZE];
char und_stack[UND_STACK_SIZE];

/* Очередь исключений */

EXC_QUEUE exc_queue[EXC_QUEUE_MAX_SIZE];
unsigned int exc_queue_count = 0;
void kill_hisr_chek(int _pid, int tid, int code, int hisr);

/* Постановка в очередь нового исключений */
int AddToExcQueue(int pid, int tid, unsigned int lr, unsigned int cpsr, int type, char *string)
{
    for (int i = 0; i < EXC_QUEUE_MAX_SIZE; i++)
    {
        if (exc_queue[i].type == 0x00)
        {
            exc_queue[i].pid     =  pid;
            exc_queue[i].tid     =  tid;
            exc_queue[i].lr      =  lr;
            exc_queue[i].cpsr    =  cpsr;
            exc_queue[i].type    =  type;
            memcpy(exc_queue[i].string, string, 0x20);
            exc_queue[i].string[0x20-1] = '\0';
            exc_queue_count++;
            return 1;
        }
    }
    return 0;
}

/* Получаем элемент из очереди исключений */
int GetExcQueueElement(EXC_QUEUE *exc_que)
{
    if (!exc_que) return -1;
    for (int i = 0; i < EXC_QUEUE_MAX_SIZE; i++)
    {
        if (exc_queue[i].type != 0x00)
        {
            exc_que->pid     =  exc_queue[i].pid;
            exc_que->tid     =  exc_queue[i].tid;
            exc_que->lr      =  exc_queue[i].lr;
            exc_que->cpsr    =  exc_queue[i].cpsr;
            exc_que->type    =  exc_queue[i].type;
            memcpy(exc_que->string, exc_queue[i].string, 0x20);
            return i;
        }
    }
    return -1;
}

/* Удаляем элемент из очереди исключений */
void RemoveFromExcQueueElement(int id)
{
    if (id >= EXC_QUEUE_MAX_SIZE) return;

    exc_queue[id].pid     = -1;
    exc_queue[id].tid     = -1;
    exc_queue[id].lr      = 0;
    exc_queue[id].cpsr    = 0;
    exc_queue[id].type    = 0;
    memset(exc_queue[id].string, 0, 0x20);
    exc_queue_count--;
}


//Пока оставим, нам нужен адрес этой ф-ии, а если испоьзовать через SWI
//то ничего не выйдет
NU_TASK  *(*NU_Current_Task_Pointer_ptr)();



/* Работа с HISR'ом исключений и различных ошибок в программах */

NU_HISR nu_exc_handler;
char nu_exc_handler_stack[EXC_HANDLER_STACK_SIZE];


const char store_string[]="Unknown";


void *get_stack_pointer_from_proc(int pid)
{
    CoreProcess *proc = coreProcessData(pid);
    if(!proc)
        return 0;

    return (void *)((int)proc->t.stack + proc->t.stack_size);
}

/* Общий обработчик исключений и ошибок */
void AbortCommonHandler(int id, unsigned long lr, unsigned long cpsr, int type)
{
    // передал нахер через 1н регистр...
    int pid = id >> 16 & 0xffff;
    int tid = id & 0xffff;
    char *s = 0, *ss = 0;

    //Выключаем вытеснение (многозадачность)
    NU_Change_Preemption(NU_NO_PREEMPT);

    //Обработка названия ошибки
    s  = RamLastStoreString(); ss = s;
    if (s == (char *)-1) s = (char *)store_string;
    else if (s[0] == '\0') s = (char *)store_string;

    //Добавим новое исключение в очередь для обработки
    AddToExcQueue(pid, tid, lr, cpsr, type, s);

    //Очистим место, где название ошибки
    if (ss != (char *)-1) memset(ss, 0, 0x20);

    //Активируем HISR обработчика исключения
    NU_Activate_HISR(&nu_exc_handler);

    //Включаем вытеснение (многозадачность)
    NU_Change_Preemption(NU_PREEMPT);

    //Останавливаем текущий таск и всех его потомковых тредов
    fullProcessSuspend(pid);
}



/* Шаблон сообщения об ошибке */
const char msg_pat[]=
    "%s\n"
    "%s(pid: %d; tid: %d)\n"
    "CPSR=%08X\n"
    "LR=%08X\n";

const char msg_pat_sexit[]=
    "(S)Exit: %s\n"
    "(pid: %d; tid: %d)\n"
    "%s\n"
    "LR=%08X\n";


//Процедура (Энтрик) HISR'a
void exception_handler()
{
    EXC_QUEUE *eq = malloc(sizeof(EXC_QUEUE));
    char msg[256] = {0};
    int rem_id = GetExcQueueElement(eq);
    short pid = eq->pid;
    short tid = eq->tid;
    const char *task_name = pidName(pid);

    if(!task_name)
        task_name = "UNK";

    switch (eq->type)
    {
    case EXC_TYPE_DATA_ABORT:
        sprintf(msg, msg_pat, "Data Abort!",
                task_name,
                pid, tid,
                eq->cpsr,
                eq->lr
               );
        ShowMSG(2, (int)msg);
        break;
    case EXC_TYPE_PREFETCH_ABORT:
        sprintf(msg, msg_pat, "Prefetch Abt!",
                task_name,
                pid, tid,
                eq->cpsr,
                eq->lr
               );
        ShowMSG(2, (int)msg);
        break;
    case EXC_TYPE_UND_INSTR:
        sprintf(msg, msg_pat, "Und. Instruct.!",
                task_name,
                pid, tid,
                eq->cpsr,
                eq->lr
               );
        ShowMSG(2, (int)msg);
        break;
    case EXC_TYPE_SEXIT: case 5:
        sprintf(msg, msg_pat_sexit,
                eq->string,
                pid, tid,
                task_name,
                eq->lr
               );
        ShowMSG(2, (int)msg);
        break;

    }


    free(eq);
    printf_nlock("\033[1m\033[31mException: %s\033[0m\n", msg);

    kill_hisr_chek(pid, tid, -1, 1);

    RemoveFromExcQueueElement(rem_id);
}


void exc_handler_entry() {
    helperproc_schedule(exception_handler, 0, 0, 0);
    //SUBPROC(exception_handler);
}


unsigned long get_NU_Current_Task_Pointer()
__def( NU_SWILIB_BEGIN_NUMBER+0x800C, unsigned long)


/* Установка обработчиков ошибок */
void NU_ExceptionsInit()
{
    int is_nsg = isnewSGold();

    //Прописываем адреса для стандартных обработчиков
    if (!is_nsg)
    {
        //Исключения
        da_def_handler = DA_DEF_HANDLER_SG;
        pa_def_handler = PA_DEF_HANDLER_SG;
        ui_def_handler = UI_DEF_HANDLER_SG;

        //Другие прошивочные ошибки
        swi2_def_jumper = SWI2_DEF_HANDLER_SG;
        swi3_def_jumper = SWI3_DEF_HANDLER_SG;
    }
    else
    {
        //Исключения
        da_def_handler = DA_DEF_HANDLER_NSG;
        pa_def_handler = PA_DEF_HANDLER_NSG;
        ui_def_handler = UI_DEF_HANDLER_NSG;

        //Другие прошивочные ошибки
        swi2_def_jumper = SWI2_DEF_HANDLER_NSG;
        swi3_def_jumper = SWI3_DEF_HANDLER_NSG;
    }


    //Открываем доступ, выклчаем прерывания
    UnLockAllAccess();
    DisableInterrupts();

    //Установка

    //Исключения
    data_abort_reg(da_handler_vector);
    prefetch_abort_reg(pa_handler_vector);
    und_instruct_reg(ui_handler_vector);

    //Другие ошибки
    if (!is_nsg)
    {
        swi2_reg_sg(swi2_vector);
        swi3_reg_sg(swi3_vector);
    }
    else
    {
        swi2_reg_nsg(swi2_vector);
        swi3_reg_nsg(swi3_vector);
    }

    //Закрываем доступ, вклчаем прерывания
    EnableInterrupts();
    LockAllAccess();

    //Это пока оставим, на случай SWI компиляции, нельзя просто сви в LISR обработчике использовать
    NU_Current_Task_Pointer_ptr = (NU_TASK *(*)())get_NU_Current_Task_Pointer();


    //Создаём HISR обработчика, приоритет минимальный
    NU_Create_HISR(&nu_exc_handler, EXC_HANDLER_NAME, exc_handler_entry, 2,
                   (void *)nu_exc_handler_stack, EXC_HANDLER_STACK_SIZE);


}


/* Удаление обработчиков ошибок */
void NU_ExceptionsDeInit()
{
    int is_nsg = isnewSGold();

    //Открываем доступ, выклчаем прерывания
    UnLockAllAccess();
    DisableInterrupts();

    //Исключения
    data_abort_reg(da_def_handler);
    prefetch_abort_reg(pa_def_handler);
    und_instruct_reg(ui_def_handler);

    //Другие ошибки
    if (!is_nsg)
    {
        swi2_reg_sg(swi2_def_jumper);
        swi3_reg_sg(swi3_def_jumper);
    }
    else
    {
        swi2_reg_nsg(swi2_def_jumper);
        swi3_reg_nsg(swi3_def_jumper);
    }

    //Закрываем доступ, вклчаем прерывания
    EnableInterrupts();
    LockAllAccess();

    //Удаляем HISR обработчика
    NU_Delete_HISR(&nu_exc_handler);
}



