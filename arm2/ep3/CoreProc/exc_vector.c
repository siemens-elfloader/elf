
#include <spl/exc_handler.h>
#include <spl/process.h>
#include <spl/thread.h>


void AbortCommonHandler(int pid, int tid, unsigned long lr, unsigned long cpsr, int type);

extern char abt_stack[ABORT_STACK_SIZE];
extern char und_stack[UND_STACK_SIZE];

extern unsigned int da_def_handler;
extern unsigned int pa_def_handler;
extern unsigned int ui_def_handler;

extern unsigned int swi2_def_jumper;
extern unsigned int swi3_def_jumper;


__attribute__((naked))
void handler_vector(int type)
{
    register int _lr asm("lr");
    volatile unsigned  int lr = _lr-4;
    volatile unsigned int cpsr;

    asm volatile("MRS %0, SPSR" :"=r"(cpsr));

    int pid = getpid();

    if(pid == -1) {
        switch(type)
        {
        case 1:
            asm("MOV PC, %0"::"r"(da_def_handler));
        case 2:
            asm("MOV PC, %0"::"r"(pa_def_handler));
        case 3:
            asm("MOV PC, %0"::"r"(ui_def_handler));
        }
        //((void(*)())da_def_handler)();
    }


    asm volatile("MOV SP, %1\n"
                 "BIC %0, %2, #0xC0\n"
                 "MSR CPSR_c, %2": "=r"(cpsr) :"r"(get_stack_pointer_from_proc(pid)), "r"(cpsr));

    //AbortCommonHandler(pid, gettid(), lr, cpsr, type);
    asm("MOV R3, %3\n"
        "MOV R2, %2\n"
        "MOV R1, %1\n"
        "MOV R0, %0\n"
        "MOV R4, %4\n"
        "STR R4, [SP]\n"
        "B   AbortCommonHandler"
        :
        :"r"(pid), "r"(gettid()), "r"(lr), "r"(cpsr), "r"(type));
}



__attribute__((naked))
void handler_swi_vector(int type, int cpsr, unsigned int lr)
{
    int pid = getpid();

    if(pid == -1) {
        switch(type)
        {
        case 4:
            asm("MOV PC, %0"::"r"(swi2_def_jumper));
        case 5:
            asm("MOV PC, %0"::"r"(swi3_def_jumper));
        }
    }


    asm volatile("MOV SP, %1\n"
                 "BIC %0, %2, #0xC0\n"
                 "MSR CPSR_c, %2": "=r"(cpsr) :"r"(get_stack_pointer_from_proc(pid)), "r"(cpsr));

    //AbortCommonHandler(pid, gettid(), lr, cpsr, type);
    asm("MOV R3, %3\n"
        "MOV R2, %2\n"
        "MOV R1, %1\n"
        "MOV R0, %0\n"
        "MOV R4, %4\n"
        "STR R4, [SP]\n"
        "B   AbortCommonHandler"
        :
        :"r"(pid), "r"(gettid()), "r"(lr), "r"(cpsr), "r"(type));
}
