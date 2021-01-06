#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "obs/obs.c"
#include "call/call.c"



const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

char elfname[24];

int my_keyhook(int submsg, int msg);

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

CSM_RAM *icsm;

extern void kill_data(void *p, void (*func_p)(void *));
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);


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

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  csm_result=old_icsm_onMessage(data,msg);
  if(profile==0||profile==GetProfile())
  {
  if (msg->msg==MSG_INCOMMING_CALL&&is_call==CALL_NULL){is_call=CALL_IN;Auto();}

  if (((msg->msg==MSG_STATE_OF_CALL)&&(msg->submess==1)&&((int)msg->data0==2))&&is_call!=CALL_OUTW&&is_call!=CALL_INW)
  {
    if(is_call==CALL_NULL)is_call=CALL_OUT;
    if(opmod == 0)OpenCall();
  }
  if(msg->msg == MSG_END_CALL)
  {
     CloseCall();
     real_time.sec=0;
     real_time.min=0;
     is_call=CALL_NULL;
  }
  }
  return(csm_result);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
   if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      char msg[36];
      sprintf(msg,"%s обновлен!",elfname);
      ShowMSG(1,(int)msg);
      InitConfig(elfname);
    }
  }
  return (1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  AddKeybMsgHook((void *)my_keyhook);

}
static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  #ifdef DBG
  DHS_removeProc(TimeDraw);
  #endif
  ((CSM_DESC*)icsm->constr)->onMessage=old_icsm_onMessage;
  GBS_DelTimer(&tmr);
#ifdef DBG
  GBS_DelTimer(&tmr2);
#endif
  RemoveKeybMsgHook((void *)my_keyhook);
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
#ifdef DBG
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"in:%d out:%d auto:%d DBG is_call:%d",in,out,autom,is_call);
#else
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"in:%d out:%d auto:%d",in,out,autom);
#endif
}




void key()
{
if(is_call==CALL_OUT||is_call==CALL_IN)OpenCall();
else if(is_call==CALL_OUTW||is_call==CALL_INW){CloseCall();is_call=CALL_INW;}
}

int my_keyhook(int submsg, int msg)
{
char mode=0;
  if(opmod==1&&is_call!=CALL_NULL)
  {
    if((Key1Type==0&&msg==KEY_DOWN&&submsg==Key1)||(Key2Type==0&&msg==KEY_DOWN&&submsg==Key2)||
    (Key1Type==1&&msg==LONG_PRESS&&submsg==Key1)||(Key2Type==1&&msg==LONG_PRESS&&submsg==Key2))
    {key();return(2);}

     if(Key1Type==2&&Key2Type==2)
    {

  if(msg==KEY_UP)mode=0;
  if(msg==KEY_DOWN)
  {if(submsg==Key1)mode=1;else if(submsg==Key2 && mode==1){key();return(2);}}

    }
  }
  return (0);
}



int main(char *arg,char *arg2)
{
  strcpy(elfname,strrchr(arg,'\\')+1);
  InitConfig(elfname);
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  icsm=FindCSMbyID(CSM_root()->idle_id);
  old_icsm_onMessage=((CSM_DESC*)icsm->constr)->onMessage;
  ((CSM_DESC*)icsm->constr)->onMessage=MyIDLECSM_onMessage;
  #ifdef DBG
  DHS_addProc(TimeDraw);
  CREDRAW();
#endif
  return 0;
}
