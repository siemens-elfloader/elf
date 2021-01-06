/*
* PlayersControl
* (c) Danil_e71
* Идея Snoop-Cat
* 2010-2011
* http://team-sc.ru/viewtopic.php?t=6022
*/
#include "conf_loader.h"//кфг
#include "main.h"//константы
#include "funcs.c"//основные функции
#include "funcs.h"//описание функций


#define VERSION "1.0"


int MyFunc(int key1,int key2,int key1type,int key2type,int msg,int submsg,void ptr(),int number,int param0)
{
  
  if((key1type!=KEY_NOT_USE||key2type!=KEY_NOT_USE)&&msg!=KEY_DOWN)
  {
  if((key1type==KEY_DOUBLE_CLICK&&msg==KEY_UP&&submsg==key1)||(key2type==KEY_DOUBLE_CLICK&&msg==KEY_UP&&submsg==key2))
  {
     doublekey[number]++;if(submsg==key1)TmrSec(key1);else TmrSec(key2);
     if(doublekey[number]==DOUBLE_SECOND){if(param0!=-1)ptr(param0); else ptr();doublekey[number]=DOUBLE_NULL;} 
      return 1;  
  }
 if((key1type==KEY_TWO&&key2type==KEY_TWO&&msg==KEY_UP)&&(submsg==key1||submsg==key2))
  {    
    if(submsg==key2&&(int)*RamPressedKey()==key1)if(param0!=-1)ptr(param0); else ptr();
    
  return 1;
  }
    if((submsg==key1&&((key1type==KEY_LONG_PRESS&&msg==LONG_PRESS)||(key1type==KEY_ONE_CLICK&&msg==KEY_UP)))||(submsg==key2&&((key2type==KEY_LONG_PRESS&&msg==LONG_PRESS)||(key2type==KEY_ONE_CLICK&&msg==KEY_UP))))
  {
    if(param0!=-1)ptr(param0);
    else ptr();
    return 1;
  }
  return -1;
  }
    return -1;
}


int MyTmrFunc(int key,int keytype,int msg,int submsg,void ptr(),int number)
{
  if(keytype!=3&&msg!=KEY_DOWN&&submsg==key)
  {  
  if((keytype==KEY_DOUBLE_CLICK&&msg==KEY_UP))
  {
    doublekey[number]++;TmrSec(key);
    if(doublekey[number]==DOUBLE_SECOND)
    {
      ptr();
      doublekey[number]=DOUBLE_NULL;
      return 1;
  }   
  return 1;
  } 
    if((keytype==KEY_LONG_PRESS&&msg==LONG_PRESS)||(keytype==KEY_ONE_CLICK&&msg==KEY_UP))
  {
   ptr();
   return 1;
  }
  return -1;
    }
  return -1;
}


int my_keyhook(int submsg, int msg)
{
    
if((MainType==TYPE_ONLY_UNLOCK&&!IsUnlocked())||(MainType==TYPE_ONLY_LOCK&&!IsUnlocked())||MainType==TYPE_BOTH) 
  {
    if(!IsPlayerOn()&&!IsIvoOn&&!IsMaplayerOn&&!IsSPlayerOn)
    {
    if(MyFunc(StartKey1_1,StartKey1_2,StartKey1_1Type,StartKey1_2Type,msg,submsg,Start,0,STANDART)==1)return KEYHOOK_BREAK;
    if(MyFunc(StartKey2_1,StartKey2_2,StartKey2_1Type,StartKey2_2Type,msg,submsg,Start,1,IVOPLAY)==1)return KEYHOOK_BREAK;
    if(MyFunc(StartKey3_1,StartKey3_2,StartKey3_1Type,StartKey3_2Type,msg,submsg,Start,2,MAPLAYER)==1)return KEYHOOK_BREAK;
    if(MyFunc(StartKey4_1,StartKey4_2,StartKey4_1Type,StartKey4_2Type,msg,submsg,Start,3,SPLAYER)==1)return KEYHOOK_BREAK;
    }


    
    
   if(IsPlayerOn()||IsIvoOn||IsMaplayerOn||IsSPlayerOn)
  { 
  if(MyFunc(PlayPauseKey_1,PlayPauseKey_2,PlayPauseKey_1Type,PlayPauseKey_2Type,msg,submsg,PlayPause,4,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(CloseKey_1,CloseKey_2,CloseKey_1Type,CloseKey_2Type,msg,submsg,Close,5,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(StopKey_1,StopKey_2,StopKey_1Type,StopKey_2Type,msg,submsg,Stop,6,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(NextKey_1,NextKey_2,NextKey_1Type,NextKey_2Type,msg,submsg,Next,7,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(PrevKey_1,PrevKey_2,PrevKey_1Type,PrevKey_2Type,msg,submsg,Prev,8,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(VolUPKey_1,VolUPKey_2,VolUPKey_1Type,VolUPKey_2Type,msg,submsg,VolUP,9,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(VolDOWNKey_1,VolDOWNKey_2,VolDOWNKey_1Type,VolDOWNKey_2Type,msg,submsg,VolDOWN,10,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(MuteKey_1,MuteKey_2,MuteKey_1Type,MuteKey_2Type,msg,submsg,Mute,11,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyFunc(LockKey_1,LockKey_2,LockKey_1Type,LockKey_2Type,msg,submsg,Lock,12,NULL_PARAM)==1)return KEYHOOK_BREAK;
  if(MyTmrFunc(TimerOnKey,TimerOnKeyType,msg,submsg,StartCloseTimer,13)==1)return KEYHOOK_BREAK;
  if(MyTmrFunc(TimerOffKey,TimerOffKeyType,msg,submsg,StopCloseTimer,14)==1)return KEYHOOK_BREAK;


    
  }
 
  }
 
  return KEYHOOK_NEXT;
}
//-------------------------

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  

      if (msg->msg==MSG_RECONFIGURE_REQ&&strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Конфиг изменен!");
      InitConfig();
    }  

   if (msg->msg==MSG_IPC&&(ipc_recv=(IPC_REQ*)msg->data0))
   {
     if(!strcmp_nocase(ipc_recv->name_from,IPC_MAPLYER))
     {
       if(msg->submess==IPC_OUT_PLAYER_START){IsMaplayerOn=1;SendCmd(MAPLAYER,IPC_GET_INFO);}
       if(msg->submess==IPC_OUT_PLAYER_CLOSE)IsMaplayerOn=0;
      }

     if (!strcmp_nocase(ipc_recv->name_to,ipc_my_name)&&!strcmp_nocase(ipc_recv->name_from,IPC_IVO))
     {
       IsIvoOn=1;
     }
       if(!strcmp_nocase(ipc_recv->name_from,IPC_TO_SPLAYER))
         {
           if(msg->submess==IPC_SPLAYER_STARTED)IsSPlayerOn=1;
           if(msg->submess==IPC_SPLAYER_CLOSED)IsSPlayerOn=0;
          }
  }
  //respect tridog:)
  #ifdef NEWSGOLD
#ifdef ELKA
  if (msg->msg==0x15680)
#else
  if (msg->msg==0x15682)
#endif 
  {
    if ((   ((char *)(((int *)msg->data1)[6]))[0x11]  )==0)
    {
      //  Аксесуар подключен
      HeadsetConnect();  
    }
    if ((   ((char *)(((int *)msg->data1)[6]))[0x11]  )==1)
    {
      //  Аксесуар отключен
      HeadsetDisconnect();  
    }
  }
#endif
  return (1);
}
//-------------------------
static void maincsm_oncreate(CSM_RAM *data)
{
  AddKeybMsgHook((void *)my_keyhook);
}
//-------------------------
static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
//-------------------------
static void maincsm_onclose(CSM_RAM *csm)
{
  if(IsTimerProc(&KeyTmr))GBS_DelTimer(&KeyTmr);
  if(IsTimerProc(&close_timer))GBS_DelTimer(&close_timer);
  RemoveKeybMsgHook((void *)my_keyhook);
  SUBPROC((void *)Killer);
}

//-------------------------
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
  },

};

//-------------------------
static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),perc_ss,"PlayersControl",VERSION);
}
//-------------------------
int main()
{
  InitConfig();
  int acc=GetAccessoryType();
  if(!Head_On)if((acc==19||acc==18||acc==21))HeadsetConnect();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return 0;
}
