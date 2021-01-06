#include <swilib.h>
#include <unistd.h>
#include <conf_loader.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "call/call.h"
#include <conf_loader.h>
/*
    Для отключение прямого вызова сви-функци добавьте дефайн __NO_DIRECT_SWI (Нужен пропатченный гцц)
    Может быть полезным если нужно уменьшить размер эльфа.
*/


GBSTMR tmr;






CSM_RAM *icsm;

unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
const int minus11=-11;
int my_csm_id=0;

typedef struct
{
    CSM_RAM csm;
} MAIN_CSM;



int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result=old_icsm_onMessage(data,msg);

  if(profile==0||profile==GetProfile())
  {

//входящий
  if (msg->msg==MSG_INCOMMING_CALL&&is_call[0]==CALL_N)
      {

      is_call[0]=CALL_I;
      Auto(&tmr);
      }

//снятие трубки
  if (((msg->msg==MSG_STATE_OF_CALL)&&(msg->submess==1)&&((int)msg->data0==2))&&is_call[1]!=CALL_W)
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




extern "C" void kill_data(void *p, void (*func_p)(void *));



void key()
{
int temp[2]={0};
if(is_call[0]!=CALL_N)OpenCall();
else if(is_call[1]==CALL_W){temp[0]=is_call[0];temp[1]=is_call[1];CloseCall();is_call[0]=temp[0];temp[1]=is_call[1];}
}


int my_keyhook(int submsg, int msg)
{
  char mode=0;
  if(opmod==1&&is_call[0]==CALL_N)
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

static void maincsm_oncreate(CSM_RAM *data)
{
AddKeybMsgHook((void *)my_keyhook);
}
void ElfKiller(void)
{
    kill_elf();
}

static void maincsm_onclose(CSM_RAM *csm)
{
//delete socket;
    //GBS_StopTimer(&tmr);
    RemoveKeybMsgHook((void *)my_keyhook);
    ((CSM_DESC*)icsm->constr)->onMessage=old_icsm_onMessage;
    SUBPROC((void *)ElfKiller);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
   // MAIN_CSM *csm=(MAIN_CSM*)data;

    return(1);
}




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

void UpdateCSMname(void)
{
   wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"in:%d out:%d auto:%d",in,out,autocall);
}


int main(const char *exename, const char *fname)
{
    InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=(CSM_RAM*)CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  icsm=FindCSMbyID(CSM_root()->idle_id);
  old_icsm_onMessage=((CSM_DESC*)icsm->constr)->onMessage;
  ((CSM_DESC*)icsm->constr)->onMessage=MyIDLECSM_onMessage;
    return 0;
}

