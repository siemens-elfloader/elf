
#include <spl/process.h>
#include <spl/processbridge.h>
#include <spl/coreevent.h>
#include <spl/waitcondition.h>



int _pid[25] = {-1};
int csz = 20;



int proc_main(int argc, char **argv)
{
    printf("proc_main: ppid: %d | pid: %d\n", getppid(), getpid());
    NU_Sleep(90);
    return 0;
}



int main()
{
    initUsart();
    printf(" [+] main: pid: %d\n", getpid());


    for(int i=0; i<csz; ++i)
        _pid[i] = createProcess("Ololo", 94, proc_main, 0, 0, 1);

    for(int i=0; i<csz; ++i) {
        waitForProcessFinished(_pid[i], 0);
        printf(" - %d finished\n", _pid[i]);
    }

    printf("All process finished\n");
    return 0;
}





