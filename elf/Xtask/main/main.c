#include "E:\ARM\swilib.h"
#include "E:\ARM\cfg_items.h"
#include "conf_loader.h"
#include "E:\ARM\xtask_ipc.h"

#ifdef NEWSGOLD
#define USE_ONE_KEY
#endif

CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

WSHDR *ws_nogui;

CSM_RAM *under_idle;

extern const int RED_BUT_MODE;
extern const int ENA_LONG_PRESS;
extern const int ENA_LOCK;

extern int my_csm_id;

extern void show_csm(int csmid);

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  FreeWS(ws_nogui);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

extern void do_gui(int, int);

// -1 - XTask GUI present
// 0 - XTask GUI absent
// 1 - IBUT longpressed, ready for exit
int mode;

// 0 - no press
// 1 - long press REDBUT
int mode_red;

// 0 - no press
// 1 - long press ENTER_BUTTON
// 2 - disable KEY_UP process
int mode_enter;
int BUTTON=0x11;//Нужная клавиша в HEX
int my_keyhook(int submsg, int msg)
{
#ifdef USE_ONE_KEY
#ifdef ELKA
  if (submsg!=POC_BUTTON) return(0);
#else
  if (submsg!=INTERNET_BUTTON) return(0);
#endif
 if (my_csm_id)
  { if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
    { CloseCSM(my_csm_id);
    }
    if (msg==KEY_UP)
    {
      GBS_SendMessage(MMI_CEPID,KEY_UP,BUTTON);
    }
    return(2);
  }
  switch(msg)
  {
  case KEY_DOWN: break;
  case KEY_UP:
    if (IsUnlocked()||ENA_LOCK)
    { do_gui(0,0); } break;
  case LONG_PRESS:  break;
  }
  return(1);
#else
  if (submsg!=BUTTON) return(0);
  if (my_csm_id)
  {
    if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
    {
      CloseCSM(my_csm_id);
    }
    return(0);
  }
  switch(msg)
  {
  case KEY_DOWN:
  mode_enter=1;
    if (IsUnlocked()||ENA_LOCK)
    {
      do_gui(0,0);
    }
    mode=0;
    break;
  case KEY_UP:
    if (mode_enter==0)
    { mode_enter=2;
      GBS_SendMessage(MMI_CEPID,KEY_UP,BUTTON);
      return (2);
    }
    if (mode_enter==2)
    {
      mode_enter=0;
      return (0);
    }
    mode_enter=0;
    return (2);      
  case LONG_PRESS:
    mode_enter=1;
    if (IsUnlocked()||ENA_LOCK)
    {
      do_gui(0,0);
    }
    mode=0;
    break;
  }
  return(2);
#endif
}

volatile int callhide_mode=0;

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

const char my_ipc_name[]=IPC_XTASK_NAME;

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  int icgui_id;
  
  csm_result = old_icsm_onMessage(data, msg); //Вызываем старый обработчик событий
  icgui_id=((int *)data)[DISPLACE_OF_INCOMMINGGUI/4];
  if (!icgui_id) callhide_mode=0;
  
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"XTask config updated!");
      InitConfig();
    }
  }
  //IPC
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp(ipc->name_to,my_ipc_name)==0)
      {
	switch (msg->submess)
	{
	case IPC_XTASK_SHOW_CSM:
	  if (!IsCalling()) do_gui(1,(int)(ipc->data));
	  break;
	case IPC_XTASK_IDLE:
	  if (!IsCalling()) do_gui(1,0);
	  break;
	}
      }
    }
  }
  if (msg->msg==MSG_INCOMMING_CALL)
  {
    callhide_mode=1;
  }
  if (callhide_mode)
  {
    if (IsGuiOnTop(icgui_id))
    {
      extern void RotateCSMs(CSM_RAM *ucsm, void *selcsm);
      RotateCSMs(CSM_root()->csm_q->csm.last,FindCSMbyID(CSM_root()->idle_id));
      callhide_mode=0;
    }
  }
  return csm_result;  
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  FreeWS(ws_nogui);
  RemoveKeybMsgHook((void *)my_keyhook);
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

void main(void)
{
  mode=0;
  InitConfig();
  LockSched();
  if (!AddKeybMsgHook_end((void *)my_keyhook))
  {
    ShowMSG(1,(int)"Невозможно зарегистрировать обработчик!");
    SUBPROC((void *)ElfKiller);
  }
  else
  {
    extern const int ENA_HELLO_MSG;
    if (ENA_HELLO_MSG) ShowMSG(1,(int)"XTask2.0 установлен!");
    {
      CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
      memcpy(&icsmd,icsm->constr,sizeof(icsmd));
      old_icsm_onClose=icsmd.onClose;
      old_icsm_onMessage=icsmd.onMessage;
      icsmd.onClose=MyIDLECSM_onClose;
      icsmd.onMessage=MyIDLECSM_onMessage;
      icsm->constr=&icsmd;
    }
    ws_nogui=AllocWS(256);
    wsprintf(ws_nogui,"%t","Нет GUI!");
    under_idle=(FindCSMbyID(CSM_root()->idle_id))->prev; //Ищем idle_dialog
  }
  UnlockSched();
}
