
#include <swilib.h>
#include <nu_swilib.h>
#include <spl/coreevent.h>
#include <spl/process.h>
#include <spl/memctl.h>
#include <spl/gbs_tweak.h>



extern int entry(int, char **);

char *strdup(const char *str)
{
    size_t sz = strlen(str);
    char *r = memoryAlloc(getpid(), sz+1);

    if(r) {
        memcpy(r, str, sz);
        r[sz] = 0;
    }

    return r;
}

char *_strdup(const char *str)
{
    size_t sz = strlen(str);
    char *r = malloc(sz+1);

    if(r) {
        memcpy(r, str, sz);
        r[sz] = 0;
    }

    return r;
}


/*

int main(char *exe, char *fname)
{
    char **argv = 0;
    int argc = 1;

    if(fname)
        argc++;

    argv = malloc(argc * sizeof(void*));
    argv[0] = strdup(exe);

    if(fname)
        argv[1] = strdup(fname);

    int pid = processCreate(strrchr(exe, '\\')+1, 90, entry, argc, argv, 0);

    if(pid > -1) {
        setProcessDieAction(pid, (void (*)(void *))kill_elf, 0); // kill_elf hack
        resumeProcess(pid);
    } else {

        ShowMSG(1, (int)"Can`t create process");
        kill_elf();
    }

    return 0;
}
*/
