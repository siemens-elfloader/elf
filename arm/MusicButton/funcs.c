#include "funcs.h"

void SendCmd(int player,int cmd)
{
  if(player==IVOPLAY)ipc_send.name_to=IPC_IVO;
  if(player==MAPLAYER){ipc_send.name_to=IPC_MAPLYER;ipc_send.name_from=IPC_CONTROL_NAME;}
  if(player==SPLAYER){ipc_send.name_to=IPC_TO_SPLAYER;ipc_send.name_from=IPC_FROM_SPLAYER;ipc_send.data=0;}
  GBS_SendMessage(MMI_CEPID,MSG_IPC,cmd,&ipc_send); 
}
void PlayPause()
{
  if(player0&&IsPlayerOn())MPlayer_Toggle();
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_PLAY_PAUSE);
  if(player2&&IsMaplayerOn)SendCmd(MAPLAYER,IPC_ENTER_BUTTON);
  if(player3&&IsSPlayerOn){SendCmd(SPLAYER,IPC_SPLAYER_ENTER);}
}
void Stop()
{
  if(player0&&IsPlayerOn())MPlayer_Stop();
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_STOP);
  if(player2&&IsMaplayerOn)SendCmd(MAPLAYER,IPC_SET_STOP);
  if(player3&&IsSPlayerOn)SendCmd(SPLAYER,IPC_SPLAYER_STOP);
}
void Prev()
{
  if(player0&&IsPlayerOn())MPlayer_Prev();
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_PREV);
  if(player2&&IsMaplayerOn)SendCmd(MAPLAYER,IPC_PREV);
  if(player3&&IsSPlayerOn)SendCmd(SPLAYER,IPC_SPLAYER_PREV);
}
void Next()
{
  if(player0&&IsPlayerOn())MPlayer_Next();
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_NEXT);
  if(player2&&IsMaplayerOn)SendCmd(MAPLAYER,IPC_NEXT);
  if(player3&&IsSPlayerOn)SendCmd(SPLAYER,IPC_SPLAYER_NEXT);
}
void Start(int player)
{
  if(player0&&player==STANDART)
  {
#ifdef NEWSGOLD
   MEDIA_PLAYLAST(); 
  }
#else
        addr = (unsigned int*)GetFunctionPointer("MEDIA_PLAYLAST"); 
    if (addr)
            {
              typedef void (*voidfunc)(); 
              voidfunc pp=(voidfunc)addr; 
              SUBPROC((void*)pp);
            }
}
#endif

   WSHDR *fws=AllocWS(256);
  if(player1&&player==IVOPLAY)
    {
    wsprintf(fws,PATH_IVO);
    ExecuteFile(fws,NULL,NULL);
    }
   if(player2&&player==MAPLAYER)
  {
    wsprintf(fws,PATH_MAPLAYER);
    ExecuteFile(fws,NULL,NULL);
  }
     if(player3&&player==SPLAYER)
  {
    wsprintf(fws,PATH_SPLAYER);
    ExecuteFile(fws,NULL,NULL);
  }
   FreeWS(fws);
  if(ena_lock)Lock();
}
void Close()
{
  if(player0&&IsPlayerOn())MPlayer_Shutdown();
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_KILL);
  if(player2&&IsMaplayerOn)SendCmd(MAPLAYER,IPC_CLOSE_PLAYER);
  if(player3&&IsSPlayerOn)SendCmd(SPLAYER,IPC_SPLAYER_STOP);
}
void VolUP()
{
  if(player0&&IsPlayerOn())MPlayer_VolChange(1);
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_VOLUP); 
  if(player2&&IsMaplayerOn)SendCmd(MAPLAYER,IPC_VOL_INC);
 // if(player3&&IsSPlayerOn)SendCmd(SPLAYER,IPC_VOLUP);
}
void VolDOWN()
{
  if(player0&&IsPlayerOn())MPlayer_VolChange(-1);
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_VOLDOWN);
  if(player2&&IsMaplayerOn)SendCmd(MAPLAYER,IPC_VOL_DEC);
  //if(player3&&IsSPlayerOn)SendCmd(SPLAYER,IPC_VOLDOWN);
}
void Mute()
{
  if(player0&&IsPlayerOn())MPlayer_Mute();
  if(player1&&IsIvoOn)SendCmd(IVOPLAY,CMD_MUTE);
 // if(player3&&IsSPlayerOn)SendCmd(SPLAYER,IPC_MUTE);
}
int HeadsetDisconnect()
{
  if(HeadsetDType==0) 
  {
    addr = (unsigned int*) GetFunctionPointer(SHORCUT1); 
    if (addr)
            {
              typedef void (*voidfunc)(); 
      #ifdef NEWSGOLD          
              voidfunc pp=(voidfunc)*(addr+4);
      #else 
              voidfunc pp=(voidfunc)addr; 
      #endif 
              SUBPROC((void*)pp);
            }
    return 1;
  }
  if(HeadsetDType==1)
  {
    WSHDR *fws=AllocWS(256);
    wsprintf(fws,SHORCUT1);
    ExecuteFile(fws,NULL,NULL);
    FreeWS(fws);
    return 1;
  }
  if(HeadsetDType==2)
  {
     switch(HeadsetDD)
    {
    case 0:Start(STANDART);break;
    case 1:Start(IVOPLAY);break;
    case 2:Start(MAPLAYER);break;
    case 3:Start(SPLAYER);break;
    case 4:Close();break;
    case 5:PlayPause();break;
    case 6:Stop();break;
    case 7:Next();break;
    case 8:Prev();break;
    case 9:VolUP();break;
    case 10:VolDOWN();break;
    case 11:Mute();break;
    }
    return 1;
   }
  return 0;
}

int HeadsetConnect()
{
  if(HeadsetCType==0) 
  {
    addr = (unsigned int*)GetFunctionPointer(SHORCUT2); 
    if (addr)
            {
              typedef void (*voidfunc)(); 
      #ifdef NEWSGOLD          
              voidfunc pp=(voidfunc)*(addr+4);
      #else 
              voidfunc pp=(voidfunc)addr; 
      #endif 
              SUBPROC((void*)pp);
            }
    return 1;
  }
  if(HeadsetCType==1)
  {
    WSHDR *fws=AllocWS(256);
    wsprintf(fws,SHORCUT2);
    ExecuteFile(fws,NULL,NULL);
    FreeWS(fws);
    return 1;
  }
  if(HeadsetCType==2)
  {
    switch(HeadsetCD)
    {
    case 0:Start(STANDART);break;
    case 1:Start(IVOPLAY);break;
    case 2:Start(MAPLAYER);break;
    case 3:Start(SPLAYER);break;
    case 4:Close();break;
    case 5:PlayPause();break;
    case 6:Stop();break;
    case 7:Next();break;
    case 8:Prev();break;
    case 9:VolUP();break;
    case 10:VolDOWN();break;
    case 11:Mute();break;
    }
    return 1;
   }
  return 0;
}
void ShowMessage(char * message)//Задатки билдера))))
{
  ShowMSG(1,(int)message);
}
void TmrSec()
{
 if(timer<2){timer++;GBS_StartTimerProc(&KeyTmr,key_timer,TmrSec);}
 else{for(int i=0;i<15;i++)doublekey[i]=DOUBLE_NULL;timer=0;}
}



void Lock()
{
           gipc.name_to=IPC_XTASK_NAME;
           gipc.name_from=ipc_my_name;
           gipc.data=(void *)MAINCSM_ID;
           GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
  KbdLock();
}
void StartCloseTimer()
{
  sec=0;min=0;hour=0;
  CloseTimer(); 
}
void StopCloseTimer()
{
  GBS_StopTimer(&close_timer);
}

void CloseTimer()
{
if(TimerHour>0||TimerMin>0)
 {
  sec++;
  if(TimerVibr){if(sec<2) SetVibration(10);else SetVibration(0);}//Повибрируем вначале)))
  if(sec>59){min++;sec=0;}if(min>59){hour++;min=0;}
  if(hour==TimerHour&&min==TimerMin){Close();Lock();GBS_StopTimer(&close_timer);}
  else GBS_StartTimerProc(&close_timer,216,CloseTimer);
 }
}
