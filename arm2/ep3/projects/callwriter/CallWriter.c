#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "obs/obs.c"
#include "call/call.c"



char *elfname;

int my_keyhook(int submsg, int msg);


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
  int csm_result=old_icsm_onMessage(data,msg);

  if(profile==0||profile==GetProfile())
  {
//входящий
  if (msg->msg==MSG_INCOMMING_CALL&&is_call[0]==CALL_N)
      {
      is_call[0]=CALL_I;
      Auto();
      }

//снятие трубки
  if (((msg->msg==MSG_STATE_OF_CALL)&&(msg->submess==1)&&((int)msg->data0==2))&&is_call[1]==CALL_W)
  {
    if(is_call[0]==CALL_N)is_call[0]=CALL_O;//если исходящий
    if(opmod == 0)OpenCall();//если автоснятие
  }

  if(msg->msg == MSG_END_CALL)
  {
     CloseCall();
     real_time.sec=0;
     real_time.min=0;
     is_call[0]=CALL_N;
   }
  }
  return(csm_result);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
 /* extern const char *successed_config_filename;
  if(msg->msg == MSG_RECONFIGURE_REQ&&strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
  InitConfig(elfname);*/
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
  ((CSM_DESC*)icsm->constr)->onMessage=old_icsm_onMessage;
  GBS_DelTimer(&tmr);
  if(elfname!=0)mfree(elfname);
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
wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"in:%d out:%d auto:%d",in,out,autocall);
}

void key()
{
int temp=0;
if(is_call[0]!=CALL_N)OpenCall();
else if(is_call[1]==CALL_W){temp=is_call;CloseCall();is_call=temp;}
}


int my_keyhook(int submsg, int msg)
{
  char mode=0;
  if(opmod==1&&is_call[0]=CALL_N)
  {
    if((Key1Type==0&&msg==KEY_DOWN&&submsg==Key1)||(Key2Type==0&&msg==KEY_DOWN&&submsg==Key2)||
    (Key1Type==1&&msg==LONG_PRESS&&submsg==Key1)||(Key2Type==1&&msg==LONG_PRESS&&submsg==Key2))
    {
      key();
      return(2);
    }

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
  elfname=malloc(strlen(strrchr(arg,'\\')+1)+1);
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
  return 0;
}
