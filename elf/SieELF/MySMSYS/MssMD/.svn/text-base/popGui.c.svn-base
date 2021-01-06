#include "..\..\inc\swilib.h"
#include "..\..\inc\mplayer.h"
#include "language.h"
#include "sms_dat.h"
#include "popGui.h"
#include "main.h"
#include "edGui.h"
#include "adrList.h"
#include "CodeShow.h" 
#include "config_data.h"
#include "lgp_pic.h"
#include "NewDatReader.h"
//int sndVolume=5;
short PLAY_ID=0;

int vibra_power=0;
int sound_vol=0;
void SetSoundVibraByProfile(void)
{
  int c=GetProfile()+1;
  switch(c)
  {
  case 1:
    vibra_power=CFG_VIBRA_POWER1;
    sound_vol=CFG_SOUND_VOL1;
    break;
  case 2:
    vibra_power=CFG_VIBRA_POWER2;
    sound_vol=CFG_SOUND_VOL2;
    break;
  case 3:
    vibra_power=CFG_VIBRA_POWER3;
    sound_vol=CFG_SOUND_VOL3;
    break;
  case 4:
    vibra_power=CFG_VIBRA_POWER4;
    sound_vol=CFG_SOUND_VOL4;
    break;
  case 5:
    vibra_power=CFG_VIBRA_POWER5;
    sound_vol=CFG_SOUND_VOL5;
    break;
  case 6:
    vibra_power=CFG_VIBRA_POWER6;
    sound_vol=CFG_SOUND_VOL6;
    break;
  case 7:
    vibra_power=CFG_VIBRA_POWER7;
    sound_vol=CFG_SOUND_VOL7;
    break;
  case 8:
    vibra_power=CFG_VIBRA_POWER8;
    sound_vol=CFG_SOUND_VOL8;
    break;
  default:
    vibra_power=0;
    sound_vol=0;
    break;
  }
}
void Play(const char *fname)
{
  PLAYFILE_OPT _sfo1;
  WSHDR *sndPath,sndPathn;
  WSHDR *sndFName,sndFNamen;
  unsigned short sndPathb[128];
  unsigned short sndFNameb[128];
  char s[128];
  const char *p;
  if(!IsFileExist(fname))
    return;
  sndPath=CreateLocalWS(&sndPathn, sndPathb, 128);
  sndFName=CreateLocalWS(&sndFNamen, sndFNameb, 128);
  p=strrchr(fname,'\\')+1;
  str_2ws(sndFName,p,128);
  strncpy(s,fname,p-fname);
  s[p-fname]='\0';
  str_2ws(sndPath,s,128);
  zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
  _sfo1.repeat_num=1;
  _sfo1.time_between_play=0;
  _sfo1.play_first=0;
  _sfo1.volume=sound_vol;//
#ifdef NEWSGOLD
  _sfo1.unk6=1;
  _sfo1.unk7=1;
  _sfo1.unk9=2;
  PLAY_ID=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
  _sfo1.unk4=0x80000000;
  _sfo1.unk5=1;
  PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
  _sfo1.unk5=1;
  PLAY_ID=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
}

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);

#pragma swi_number=0x80CB
__swi __arm char *RamRingtoneStatus(); //0 on, 1, off

const int popup_softkeys[]={0, 1, 2};
SOFTKEY_DESC popup_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,LGP_DOIT_PIC}
};
const SOFTKEYSTAB popup_skt={popup_sk, 0};

#ifdef ELKA
int pp_incoming_icons[]={0x282, 0};
int pp_showmsg_icons[]={0x52C, 0};
#else
int pp_incoming_icons[]={0x278, 0};
int pp_showmsg_icons[]={0x558, 0};
#endif

#define TIME_SECOND 216

int popup_onkey(void *data, GUI_MSG *msg)
{
  if((msg->keys==0x18)||(msg->keys==0x3D))
  {
    DLG_CSM *dlg_csm=GetPopupUserPointer(data);
    if(dlg_csm)
    {
      if(!(dlg_csm->gui_id=viewTheLastNew(dlg_csm)))
        dlg_csm->csm.state=-3; //close
	//dlg_csm->gui_id=CreateMainMenu(dlg_csm);
    }
    return 1;
  }
  if(msg->keys==0x1)
    return 1;
  if(msg->gbsmsg->msg==KEY_DOWN)
  {	 
    if(!IsUnlocked())
      TempLightOn(3, 0x7FFF);
    if(PLAY_ID)
    {
      PlayMelody_StopPlayback(PLAY_ID);
      PLAY_ID=0;
    }
    if(CFG_ENA_SOUND && IsPlayerOn() && !GetPlayStatus()) MPlayer_Start();
    SetVibration(0);
  }
  return 0;
}

void popup_ghook(void *data, int cmd)
{
/*  if(cmd==2) //Create
  {
    TempLightOn(3, 0x7FFF);
    if(CFG_NOTIFY_TIME && !IsCalling())
    {
      SetSoundVibraByProfile();
      if(CFG_ENA_SOUND&& sound_vol && !(*(RamRingtoneStatus())) && IsFileExist(CFG_SOUND_PATH))
      {
	if(GetPlayStatus()) MPlayer_Stop();
	if(!PLAY_ID)
	{
	  Play(CFG_SOUND_PATH);
	}
      }
      SetVibration(vibra_power);
    }
  }
  else*/
  if(cmd==3) //Close
  {
    POPUP_DESC *pd;
    if(PLAY_ID)
    {
      PlayMelody_StopPlayback(PLAY_ID);
      PLAY_ID=0;
    }
    if(CFG_ENA_SOUND && IsPlayerOn() && !GetPlayStatus()) MPlayer_Start();
    SetVibration(0);
    //get POPUP_DESC
    pd=(POPUP_DESC *)(((void **)data)[8/4]);
    mfree(pd);
  }
}

const POPUP_DESC popup=
{
  8,
  popup_onkey,
  popup_ghook,
  NULL,
  popup_softkeys,
  &popup_skt,
  0x1,
  LGP_NULL,
  pp_incoming_icons,//popup_icons,
  0,
  FONT_MEDIUM,
  100,
  101,
  0
};
int ShowMSG_report(void *dlg_csm, SMS_DATA *sd);
int StartIncomingWin(void *dlg_csm)
{
  SMS_DATA *sd;
  WSHDR *ws;
//  WSHDR wsloc, *wn;
//  unsigned short wsb[150];
  POPUP_DESC *pd;
  CLIST *cl;
  const char *melody_filepath;
  extern unsigned int DlgCsmIDs[]; //main.c
  extern int IsNoDlg(unsigned int *id_pool); //main.c
  //if(IsNoDlg(DlgCsmIDs))
  //  sd=GetTheLastNew(1);
  //else
  //{
  //  readAllSMS();
  //  sd=GetTheLastNew(0);
  //}
  sd=GetTheLastNew(0);
  if(!sd) return 0;
  if(!CFG_NOTIFY_TIME) return 0;
  if((sd->msg_type&ISREPORT)) return (ShowMSG_report(dlg_csm, sd));
  ws=AllocWS(150);
//  wn=CreateLocalWS(&wsloc,wsb,150);
#ifndef LANG_CN
  cl=FindClByNum(sd->Number);
  if(cl)
  {
    wsprintf(ws, "%t\n%t:\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, cl->name);
  }
  else
  {
    wsprintf(ws, "%t\n%t:\n%s", lgp.LGP_NEW_MSG, lgp.LGP_FROM, sd->Number);
  }
#else
  char num[32];
  int is_fetion=0;
  WSHDR csloc, *cs;
  unsigned short csb[30];
  cs=CreateLocalWS(&csloc,csb,30);
  if(!strncmp(num_fetion, sd->Number, 5)) is_fetion=1;
  strcpy(num, is_fetion?(sd->Number+5):sd->Number);
  cl=FindClByNum(num);
  GetProvAndCity(cs->wsbody, num);
  if(cl)
  {
    if(is_fetion) wsprintf(ws, "%t\n%t:\n%w (%t)\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, cl->name, lgp.LGP_FETION, cs);
    else wsprintf(ws, "%t\n%t:\n%w\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, cl->name, cs);
  }
  else
  {
    wsprintf(ws, "%t\n%t:\n%s\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, sd->Number, cs);
  }
#endif
  //---------------------- notify
  TempLightOn(3, 0x7FFF);
  if(CFG_NOTIFY_TIME && !IsCalling())
  {
    SetSoundVibraByProfile();
    if(!cl || !cl->sms_melody_filepath) melody_filepath=CFG_SOUND_PATH;
    else melody_filepath=cl->sms_melody_filepath;
    if(CFG_ENA_SOUND&& sound_vol && !(*(RamRingtoneStatus())) && IsFileExist(melody_filepath))
    {
      if(GetPlayStatus()) MPlayer_Stop();
      if(!PLAY_ID)
      {
	Play(melody_filepath);
      }
    }
    SetVibration(vibra_power);
  }
  //---------------------
/*  if(sd)
  {
#ifdef NO_CS 
    if(findNameByNum(wn, sd->Number))
      wsprintf(ws, "%t\n%t:\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, wn);
    else
      wsprintf(ws, "%t\n%t:\n%s", lgp.LGP_NEW_MSG, lgp.LGP_FROM, sd->Number);
#else
    char num[32];
    int is_fetion=0;
    if(!strncmp(num_fetion, sd->Number, 5)) is_fetion=1;
    strcpy(num, is_fetion?(sd->Number+5):sd->Number);
    GetProvAndCity(cs->wsbody, num);
    if(findNameByNum(wn, is_fetion?(sd->Number+5):sd->Number))
    {
      if(is_fetion) wsprintf(ws, "%t\n%t:\n%w (%t)\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, wn, lgp.LGP_FETION, cs);
      else wsprintf(ws, "%t\n%t:\n%w\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, wn, cs);
    }
    else
      wsprintf(ws, "%t\n%t:\n%s\n%w", lgp.LGP_NEW_MSG, lgp.LGP_FROM, sd->Number, cs);
#endif
  }*/
  pd=malloc(sizeof(POPUP_DESC));
  memcpy(pd, &popup, sizeof(POPUP_DESC));
  pd->time=CFG_NOTIFY_TIME*1300; //1300=1s
  UpdateDlgCsmName(dlg_csm, lgp.LGP_NEW_MSG);
  return (CreatePopupGUI_ws(1, dlg_csm, pd, ws));
}

SOFTKEY_DESC msg_popup_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NONE_PIC},
  {0x003D,0x0000,LGP_DOIT_PIC}
};
const SOFTKEYSTAB msg_popup_skt={msg_popup_sk, 0};

int msg_popup_onkey(void *data, GUI_MSG *msg)
{
  if((msg->keys==0x18)||(msg->keys==0x3D))
    return 1;
  return 0;
}
const POPUP_DESC msg_popup=
{
  8,
  msg_popup_onkey,
  NULL,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  pp_showmsg_icons,
  0, // pos, 0:left, 1:top mid, 2:top right, 3: top left
  FONT_MEDIUM,
  100,
  101,
  0x7D0 //flag2 ? auto off time?
};

/*
// pos, 0:left, 1:top mid, 2:top right, 3: top left
// p, t
0: left, right
1: mid top, left
2: top right, left top
3: top left, left top
*/
int ShowMSG_ws(int flag, WSHDR *msg)
{
  return (CreatePopupGUI_ws(flag, 0, &msg_popup, msg));
}


int offproc_popup_onkey(void *data, GUI_MSG *msg)
{
  if((msg->keys==0x18)||(msg->keys==0x3D))
    return 1;
  return 0;
}
void offproc_popup_ghook(void *data, int cmd)
{
  if(cmd==3)
  {
    void *proc=GetPopupUserPointer(data);
    ((void (*)(void))proc)();
  }
}
const POPUP_DESC offproc_popup=
{
  0,
  offproc_popup_onkey,
  offproc_popup_ghook,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  pp_showmsg_icons,
  0,
  FONT_MEDIUM,
  100,
  101,
  0x7D0 //flag2 ? auto off time?
};

int ShowMSG_offproc(int flag, const char *msg, void proc(void))
{
  return (CreatePopupGUI(flag, (void *)proc, &offproc_popup, (int)msg));
}

const POPUP_DESC msg_noff_popup=
{
  0,
  msg_popup_onkey,
  NULL,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  NULL,
  0,
  FONT_MEDIUM,
  100,
  101,
  0 //flag2 ? auto off time?
};

int ShowMSG_noff(int flag, const char *msg)
{
  return (CreatePopupGUI(flag, 0, &msg_noff_popup, (int)msg));
}

void report_popup_ghook(void *data, int cmd)
{
  if(cmd==3)
  {
    SMS_DATA *sd=GetPopupUserPointer(data);
    if(CFG_ENA_AUTO_DEL_RP && IsSdInList(sd) && deleteDat(sd, 0))
      delSDList(sd);
  }
}

const POPUP_DESC msg_report=
{
  0,
  msg_popup_onkey,
  report_popup_ghook,
  NULL,
  popup_softkeys,
  &msg_popup_skt,
  0x1,
  LGP_NULL,
  NULL,
  0,
  FONT_MEDIUM,
  100,
  101,
  0x7D0 //flag2 ? auto off time?
};

int ShowMSG_report(void *dlg_csm, SMS_DATA *sd)
{
  WSHDR wsloc, *wn;
  unsigned short wsb[150];
  WSHDR *ws=AllocWS(256);
  wn=CreateLocalWS(&wsloc,wsb,150);
#ifdef NO_CS 
  if(findNameByNum(wn, sd->Number))
    wsprintf(ws, "%w\n%t:\n%w", sd->SMS_TEXT, lgp.LGP_FROM, wn);
  else
    wsprintf(ws, "%w\n%t:\n%s", sd->SMS_TEXT, lgp.LGP_FROM, sd->Number);
#else
  char num[32];
  int is_fetion=0;
  WSHDR csloc, *cs;
  unsigned short csb[30];
  cs=CreateLocalWS(&csloc,csb,30);
  if(!strncmp(num_fetion, sd->Number, 5)) is_fetion=1;
  strcpy(num, sd->Number);
  GetProvAndCity(cs->wsbody, num);
  if(findNameByNum(wn, is_fetion?(sd->Number+5):sd->Number))
  {
    if(is_fetion) wsprintf(ws, "%w\n%t:\n%w(%t)\n%w", sd->SMS_TEXT, lgp.LGP_FROM, wn, lgp.LGP_FETION, cs);
    else wsprintf(ws, "%w\n%t:\n%w\n%w", sd->SMS_TEXT, lgp.LGP_FROM, wn, cs);
  }
  else
    wsprintf(ws, "%w\n%t:\n%s\n%w", sd->SMS_TEXT, lgp.LGP_FROM, sd->Number, cs);
#endif
  UpdateDlgCsmName(dlg_csm, lgp.LGP_MSG_REPORT);
  return (CreatePopupGUI_ws(0, sd, &msg_report, ws));
}
