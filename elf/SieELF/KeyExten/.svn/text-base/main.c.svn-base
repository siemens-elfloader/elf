#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

CSM_DESC icsmd;
//int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
//void (*old_icsm_onClose)(CSM_RAM*);
int e=2;
const int minus11=-11;
extern void kill_data(void *p, void (*func_p)(void *));

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

extern const unsigned int K1ST;
extern const unsigned int K1;
extern const unsigned int K2ST;
extern const unsigned int K2;
extern const unsigned int K3ST;
extern const unsigned int K3;
extern const unsigned int K4ST;
extern const unsigned int K4;
extern const unsigned int K5ST;
extern const unsigned int K5;
extern const unsigned int K6ST;
extern const unsigned int K6;
extern const unsigned int KENTER;
extern const unsigned int KSL;
extern const unsigned int KSR;
extern const unsigned int KG;
extern const unsigned int KR;
extern const unsigned int KUP;
extern const unsigned int KDN;
extern const unsigned int KL;
extern const unsigned int KRI;
extern const unsigned int K_1;
extern const unsigned int K_2;
extern const unsigned int K_3;
extern const unsigned int K_4;
extern const unsigned int K_5;
extern const unsigned int K_6;
extern const unsigned int K_7;
extern const unsigned int K_8;
extern const unsigned int K_9;
extern const unsigned int KX;
extern const unsigned int K_0;
extern const unsigned int KJ;
extern const unsigned int KVU;
extern const unsigned int KVD;
extern const unsigned int ENA_M_B;



int my_keyhook(int submsg, int msg)
{
 extern const char *successed_config_filename;
 int MYKST[29]={0x1A,0x01,0x04,0x3B,0x3C,0x3D,0x3E,0x0C,K1ST,K2ST,K3ST,K4ST,0x0D,0x0E,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x0B,0x2A,0x23,K5ST,K6ST};
 int MYK[29]={KENTER,KSL,KSR,KUP,KDN,KL,KRI,KR,K1,K2,K3,K4,KVU,KVD,K_0,K_1,K_2,K_3,K_4,K_5,K_6,K_7,K_8,K_9,KG,KX,KJ,K5,K6};
 int i;
 WSHDR *ws;
 if (submsg==ENA_M_B)
 {
  switch(msg)
  {
  case KEY_DOWN:
    break;
  case KEY_UP:
    e=e+1;
    break;
  case LONG_PRESS:
    ws=AllocWS(150);
    str_2ws(ws,successed_config_filename, 128);
    ExecuteFile(ws, 0, 0);
    FreeWS(ws);
    break;
  }
  return(2);
 }
 if (e%2!=0) return(0);
 for(i=0;i<29;i++)
 {
  if (submsg==MYK[i])
  {
   switch(msg)
   {
  case KEY_DOWN:
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,MYKST[i]);
    break;
  case KEY_UP:
    GBS_SendMessage(MMI_CEPID,KEY_UP,MYKST[i]);
    break;
  case LONG_PRESS:
    GBS_SendMessage(MMI_CEPID,LONG_PRESS,MYKST[i]);
    break;
   }
   return(2);
  }
 }
 return (0);
}



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
int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
 int csm_result;
 csm_result = old_icsm_onMessage(data, msg);
 
 if(msg->msg == MSG_RECONFIGURE_REQ) 
 {
  extern const char *successed_config_filename;
  if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
  {
   ShowMSG(1,(int)"KeyExten config updated!");
   InitConfig();
  }
 }
 return csm_result;
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
 extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
 extern void *ELF_BEGIN;
 RemoveKeybMsgHook((void *)my_keyhook);
 seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}
*/
int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"KeyExten config updated!");
      InitConfig();
    }
  }
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  //extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  RemoveKeybMsgHook((void *)my_keyhook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
  //seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"KeyExtern");
}

int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();
  LockSched();
  
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  AddKeybMsgHook((void *)my_keyhook);
  
  UnlockSched();
  return 0;
}
