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

int main(char *exename, char *fname)
{
  char *filename;
//  IPC_REQ *myipc;
  if(fname)
  {
    if(fname[0]<'0' || fname[0]>'4' || fname[1]!=':' || strlen(fname)>128)
      goto EXIT;
//    myipc=malloc(sizeof(IPC_REQ));
    filename=malloc(strlen(fname)+2);
    strcpy(filename, fname);
    myipc.data=filename;
//    myipc->data=filename;
//    myipc->name_to=my_ipcname;
//    myipc->name_from=my_ipcname;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_FVIEW,&myipc);
  }
EXIT:
  SUBPROC((void *)ElfKiller);
  return 0;
}
