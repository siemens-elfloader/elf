
#include <spl/process.h>
#include <spl/coreevent.h>
#include <spl/csm.h>



void onCreateCSM(int id, CSM_RAM *ram)
{
    printf("%s: pid: %d\n", __FUNCTION__, getpid());
}


void onCloseCSM(int id, CSM_RAM *ram)
{
    printf("%s: pid: %d\n", __FUNCTION__, getpid());
    quit();
}


void onMessageCSM(int id, CSM_RAM *ram, GBS_MSG *msg)
{
    printf("%s: pid: %d\n", __FUNCTION__, getpid());

    printf("msg: %X\n"
           "pid_from: %X\n"
           "submess: %X\n", msg->msg, msg->pid_from, msg->submess);
}



int main()
{
    initUsart();
    printf(" [+] main: pid: %d\n", getpid());

    csmCreate("test", CoreCSM_IDLE, onCreateCSM, onCloseCSM, onMessageCSM);

    processEvents();
    return 0;
}





