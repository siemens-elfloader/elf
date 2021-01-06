
#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "task.h"
#include "corearray.h"
#include "corelist.h"
#include "resctl.h"
#include "mutex.h"


typedef struct
{
    CoreTask t;

    CoreArray ctors, dtors;
    CoreMutex m_ctor, m_dtor;
    char kill_mode, terminated;

    struct {
        void (*kik)(void *);
        void *d;
    } kostil;

    struct {
        CoreList list;
        CoreMutex mutex;
    } process;

    struct {
        CoreList list;
        CoreMutex mutex;
    } threads;

    ResCtlData *resData;
    int resAttached;
    CoreArray idUsersData;

    int start_wait_cond,
        exit_wait_cond;
    char *name;
    void *userdata;
    short ppid;
    char hisr_call;
    int kill_state, kill_tryes;
    int sig_from_tid;
    struct CoreListInode *ppid_inode;

    struct {
        CoreMutex mutex;
        int locks;
        int pid, tid;
    } critical_code;

    int (*main)(int, char**);
    int argc;
    char **argv;
    int retcode;

}CoreProcess;

int isProcessKilling(int pid);
int enterProcessCriticalCode(int pid);
int leaveProcessCriticalCode(int pid);

CoreProcess *coreProcessData(short pid);
int sendEvent(int pid, void *event, size_t size);
void initProcessConf(TaskConf *conf);

int createConfigurableProcess(TaskConf *conf, const char *name, int (*_main)(int, char**), int argc, char **argv, int run);
int createProcess(const char *name, int prio, int (*_main)(int, char**), int argc, char **argv, int run);
int resetProcess(int pid, int argc, char **argv);

int getpid(void);
int getppid(void);
int getParentPid(int pid);
const char *pidName();

void kill(int pid, int code);
void exit(int code);
void quit();

struct CoreListInode *addProcessThread(int pid, int tid);
int delProcessThread(int pid, struct CoreListInode *inode);

struct CoreListInode *addProcessToParent(int ppid, int pid);
int delProcessFromParent(int ppid, struct CoreListInode *inode);

int fullProcessSuspend(int pid);
int fullProcessResume(int pid);
int suspendProcess(int pid);
int resumeProcess(int pid);

int setProcessUserdata(int pid, void *d);

int addProcessCtors(int pid, void (*h)(void *, void *), void *data1, void *data2);
int addProcessDtors(int pid, void (*h)(void *, void *), void *data1, void *data2);
int setProcessDieAction(int pid, void (*h)(void *), void *d);

int eraseProcessCtor(int pid, int at);
int eraseProcessDtor(int pid, int at);

int waitForProcessStarted(int _pid);
int waitForProcessFinished(int _pid, int *retcode);

int attachProcessIdUserData(int _pid, void *userData);

ResCtlData *dataOfResCtl(int _pid, int id);
#endif
