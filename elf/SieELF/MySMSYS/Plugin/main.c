#include "..\..\inc\swilib.h"
#include "..\MySMSYS_ipc.h"


extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


const char my_ipcname[]=MY_SMSYS_IPC_NAME;

IPC_REQ myipc=
{
  my_ipcname,
  my_ipcname,
  NULL
};

#ifdef MAIN
#define SUBMSG SMSYS_IPC_MAIN
#endif
#ifdef CREATE_NEW
#define SUBMSG SMSYS_IPC_NEWSMS
#endif
#ifdef IN_NEW
#define SUBMSG SMSYS_IPC_IN_NEW
#endif
#ifdef IN_READ
#define SUBMSG SMSYS_IPC_IN_RD
#endif
#ifdef SENT
#define SUBMSG SMSYS_IPC_OUT
#endif
#ifdef DRAFT
#define SUBMSG SMSYS_IPC_DRAFT
#endif
#ifdef IN_ALL
#define SUBMSG SMSYS_IPC_IN_ALL
#endif
//#ifdef LAST
//#define SUBMSG SMSYS_IPC_TLAST
//#endif
#ifdef ALL
#define SUBMSG SMSYS_IPC_ALL
#endif

#ifdef ARCHIVE
#define SUBMSG SMSYS_IPC_ARCHIVE
#endif

int main(void)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SUBMSG,&myipc);
  SUBPROC((void *)ElfKiller);
  return 0;
}
