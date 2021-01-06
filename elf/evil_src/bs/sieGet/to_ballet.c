#include "..\inc\swilib.h"
#include "..\inc\xtask_ipc.h"
//#include "string_util.h"
#include "../inc/sieget_ipc.h"

const char ipc_my_name[]=SIEGET_IPC_NAME;
const char ipc_xtask_name[]=IPC_BALLETMINI_NAME;
IPC_REQ gipc;

void SendToBallet(char *name, int total, int recieved, int flag, char *filename)
{
  if(flag==1)
  {
  char download2[48];
  char send[128];
  int i=0;
  if(strlen(name)<16)
  {
    strcpy(download2, name);
  }
  else
  {
  while(i<16)
  {
    download2[i]=name[i];
    i++;
  }
  download2[i]='\0';
  }
  sprintf(send, "(%dkb/%dkb)%s", recieved/1024, total/1024, download2);
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=send;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_TOBALLET,&gipc);
  }
  else
  if(flag==2)
  {
    
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=0;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_TOBALLET3,&gipc);
  }
  else
  {
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=filename;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_TOBALLET2,&gipc);
  }
}
