
#include <swilib.h>
#include <stdlib.h>
#include <stdarg.h>
#include <spl/coreevent.h>


void _init()
{
    void NU_ExceptionsInit();
    //NU_ExceptionsInit();

    void bridgeInit();
    bridgeInit();

    void initWaitCond();
    initWaitCond();

    void resCtlInit();
    resCtlInit();

    void fdsInit();
    fdsInit();

    void memCtlInit();
    memCtlInit();

    void createIOResCtl();
    createIOResCtl();

    void socketsInit();
    socketsInit();

    void queueInit();
    queueInit();

    void pipeInit();
    pipeInit();

    void helperProcInit();
    helperProcInit();

    void processInit();
    processInit();

    void coreThreadsInit();
    coreThreadsInit();

    void asyncPrintInit();
    asyncPrintInit();

    void timersInit();
    timersInit();

    void csmInit();
    csmInit();

    void guiInit();
    guiInit();

    extern void *__ex;
    Elf32_Exec *ex = (Elf32_Exec*)&__ex;

    int i = _open("4:\\elf\\coretest\\start.txt", A_Create | A_Truncate | A_WriteOnly | A_BIN, P_WRITE, 0);

    char s[56];
    int l = sprintf(s, "Lib Range: %X - %X\n", ex->body, ex->body+ex->bin_size);
    _write(i, s, l, 0);
    _close(i, 0);
}



void _fini()
{
    void asyncPrintFini();
    asyncPrintFini();

    void processFini();
    processFini();

    void coreThreadsFini();
    coreThreadsFini();

    void csmFini();
    csmFini();

    void socketsFini();
    socketsFini();

    void closeIOResCtl();
    closeIOResCtl();

    void pipeFini();
    pipeFini();

    void fdsFini();
    fdsFini();

    void memCtlFini();
    memCtlFini();

    void timersFini();
    timersFini();

    void bridgeFini();
    bridgeFini();

    void helperProcFini();
    helperProcFini();

    void NU_ExceptionsDeInit();
    //NU_ExceptionsDeInit();
}

