#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "AdrList.h"
#include "NumList.h"
#include "EditGUI.h"
//#include "..\..\inc\mplayer.h"
#include "PopupGUI.h"
#include "CodeShow.h"
//short PLAY_ID=0;
//int vibra_power=0;
//int sound_vol=0;

/*
void PopupNewIn::Play(const char *fname, int sound_vol)
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
*/
SOFTKEY_DESC pni_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,LGP_DOIT_PIC}
};

const SOFTKEYSTAB pni_skt={pni_sk, 0};
//int PNI_ICONS[]={0x564, 0};
/*
void PopupNewIn::SetSoundVibraByProfile(void)
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
*/

PopupNewIn::PopupNewIn()
{
  this->popup.flag=8;
  this->popup.onkey=this->OnKey;
  this->popup.ghook=this->GHook;
  this->popup.proc3=NULL;
  this->popup._100=100;
  this->popup._101=101;
  this->popup.flags2=1;
  this->popup.font=FONT_MEDIUM;
  this->popup.icons=NULL; // icons
  this->popup.lgp_null=LGP_NULL;
  this->popup.softkeys=softkeys;
  this->popup.softkeystab=&pni_skt;
  this->popup.zero0=0;
  this->popup.time=CFG_NOTIFY_TIME*1300; //1300=1s
  this->cl=NULL;
}

PopupNewIn::~PopupNewIn()
{
}

int PopupNewIn::OnKey(void *data, GUI_MSG *msg)
{
  PopupNewIn *pni=(PopupNewIn *)GetPopupUserPointer(data);
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    //SDLIST *sdl;
    int id;
    //if((sdl=SMSDATA->FindSDL(pni->dat_index)))
    if(pni->sdl && SMSDATA->IsExistSDL(pni->sdl))
    {
      EditGUI *edg=new EditGUI;
      id=edg->CreateEditGUI(pni->dlg_csm, pni->sdl, ED_VIEW, pni->sdl->type, 0);
      if(id) pni->dlg_csm->gui_id=id;
    }
    return 1;
  }
  if(msg->keys==0x1)
    return 1;
  if(msg->gbsmsg->msg==KEY_DOWN)
  {	 
    if(!IsUnlocked())
      TempLightOn(3, 0x7FFF);
    //if(PLAY_ID)
    //{
    //  PlayMelody_StopPlayback(PLAY_ID);
    //  PLAY_ID=0;
    //}
    //if(CFG_ENA_SOUND && IsPlayerOn() && !GetPlayStatus()) MPlayer_Start();
    //SetVibration(0);
    //pni->SendIpc(SMSYS_IPC_SOUND_STOP);
    //pni->SendIpc(SMSYS_IPC_VIBRA_STOP);
    SendMyIpc(SMSYS_IPC_SOUND_STOP);
    SendMyIpc(SMSYS_IPC_VIBRA_STOP);
  }
  return 0;
}

void PopupNewIn::GHook(void *data, int cmd)
{
  PopupNewIn *pni=(PopupNewIn *)GetPopupUserPointer(data);
  if (cmd==0x3)
  {
/*    if(PLAY_ID)
    {
      PlayMelody_StopPlayback(PLAY_ID);
      PLAY_ID=0;
    }
    if(CFG_ENA_SOUND && IsPlayerOn() && !GetPlayStatus()) MPlayer_Start();
    SetVibration(0);*/
    //pni->SendIpc(SMSYS_IPC_SOUND_STOP);
    //pni->SendIpc(SMSYS_IPC_VIBRA_STOP);
    SendMyIpc(SMSYS_IPC_SOUND_STOP);
    SendMyIpc(SMSYS_IPC_VIBRA_STOP);
    delete pni;
  }
  else if (cmd==0x2)
  {
    const char *melody_filepath;
    int sound_vol;
    TempLightOn(3, 0x7FFF);
    if(CFG_NOTIFY_TIME && !IsCalling())
    {
      sound_vol=GetProfileVolumeSetting(GetProfile(), VOLUME);//pni->GetSoundVol();
      if(!pni->cl || !pni->cl->sms_melody_filepath) melody_filepath=CFG_SOUND_PATH;
      else melody_filepath=pni->cl->sms_melody_filepath;
      if(CFG_ENA_SOUND&& sound_vol && !(*(RamRingtoneStatus()))/* && pni->IsFileExist(melody_filepath)*/)
      {
	//if(GetPlayStatus()) MPlayer_Stop();
	//pni->SendIpc(SMSYS_IPC_SOUND_PLAY, (void *)melody_filepath);
	SendMyIpc(SMSYS_IPC_SOUND_PLAY, (void *)melody_filepath);
	//if(!PLAY_ID)
	//{
	//  pni->Play(melody_filepath, sound_vol);
	//}
      }
      if(CFG_ENA_VIBRA) SendMyIpc(SMSYS_IPC_VIBRA_START);//pni->SendIpc(SMSYS_IPC_VIBRA_START);
      //SetVibration(CFG_VIBRA_POWER);
    }
  }
  else if (cmd==0x5)
  {
    pni->UpdateCSMName(pni->dlg_csm, (int)LGP->lgp.LGP_NEW_MSG);
    if(!SMSDATA->IsExistSDL(pni->sdl))
    {
      GeneralFuncF1(1);
    }
  }
}

int PopupNewIn::CreatePopupNewIn(DLG_CSM *dlg_csm, SDLIST *sdl)
{
  WSHDR *ws;
  if(!sdl || !CFG_NOTIFY_TIME)
  {
    delete this;
    return 0;
  }
  this->dlg_csm=dlg_csm;
  this->sdl=sdl;
  //this->dat_index=dat_index;
  ws=AllocWS(150);
#ifdef LANG_CN
  unsigned short wscs_b[32];
  WSHDR *wscs, _wscs;
  wscs=CreateLocalWS(&_wscs, wscs_b, 32);
  CodeShow::GetProvAndCity(wscs->wsbody, sdl->number);
#endif
  if(!(this->cl=ADRLST->FindCList(sdl->number)))
  {
#ifdef LANG_CN
    wsprintf(ws, "%t\n%t:\n%s\n%t:\n%w",
      LGP->lgp.LGP_NEW_MSG,
      LGP->lgp.LGP_FROM,
      sdl->number,
      LGP->lgp.LGP_CODESHOW,
      wscs
      );
#else
    wsprintf(ws, "%t\n%t:\n%s", LGP->lgp.LGP_NEW_MSG, LGP->lgp.LGP_FROM, sdl->number);
#endif
  }
  else
  {
#ifdef LANG_CN
    wsprintf(ws, "%t\n%t:\n%w\n%t:\n%w",
      LGP->lgp.LGP_NEW_MSG,
      LGP->lgp.LGP_FROM,
      this->cl->name,
      LGP->lgp.LGP_CODESHOW,
      wscs
      );
#else
    wsprintf(ws, "%t\n%t:\n%w", LGP->lgp.LGP_NEW_MSG, LGP->lgp.LGP_FROM, this->cl->name);
#endif
  }
  return CreatePopupGUI_ws(1, this, &this->popup, ws);
}

  /*
int PopupNewIn::GetSoundVol(void)
{

#define BUF_SIZE (16*1024)
  int fin, size;
  char *buf;
  const char *cache_pd="1:\\default\\userprofiles.pd";
  const char *config_pd="2:\\Default\\PD\\userprofiles.pd";
  int profile=GetProfile();
  char temp[256];
  char *pp;
  int res=0;
  int is_OK=0;
  GetCPUClock();
  buf=new char[BUF_SIZE];
  if((fin=FOpen(cache_pd, A_ReadOnly, P_READ)!=-1))
  {
    //size=LSeek(fin, 0, S_END);
    //if(size)
    {
      //buf=new char[size+4];
      //LSeek(fin, 0, S_SET);
      size=FRead(fin, buf, BUF_SIZE);
      if(size>0)
      {
	buf[size]=0;
	sprintf(temp, "USERPROFILE_%02d.VOLUME=", profile);
	if((pp=strstr(buf, temp)))
	{
	  res=*(pp+strlen(temp))-'0';
	  is_OK=1;
	}
      }
      //delete buf;
    }
    FClose(fin);
  }
  //if(is_OK && res>=0) return res;
  //else is_OK=0;
  if((!is_OK || res<0)&&(fin=FOpen(config_pd, A_ReadOnly, P_READ)!=-1))
  {
    //size=LSeek(fin, 0, S_END);
    //if(size)
    {
      //buf=new char[size+4];
      //LSeek(fin, 0, S_SET);
      //if(FRead(fin, buf, size)!=size)
      size=FRead(fin, buf, BUF_SIZE);
      if(size>0)
      {
	buf[size]=0;
	sprintf(temp, "USERPROFILE_%02d.VOLUME=", profile);
	if((pp=strstr(buf, temp)))
	{
	  res=*(pp+strlen(temp))-'0';
	  is_OK=1;
	}
      }
      //delete buf;
    }
    FClose(fin);
  }
  //if(is_OK && res>=0) return res;
  if(!is_OK || res<0) res=0;
  delete buf;
  return res;
#define VOLUME 0x12
#define VOLUME_ALARMCLOCK 0xD
#define VOLUME_INCALL 2

#define TONESETTINGCALLS 0
#define TONESETTINGCALLS 1
#define TONESETTINGWTCALLS 3
#define TONESETTINGSMSMMS 5
#define TONESETTINGSMSMMS 6
#define TONESETTINGSMSMMS 7
#define TONESETTINGCBS 8
#define TONESETTINGEMAIL 0xA
#define TONESETTINGORGANISER 0xE
#define TONESETTINGIMPS 9
#define TONESETTINGGAMES 0x18
#define TONESETTING_ALARMCLOCK 0xD

#define GetPrfileVolumeSetting_adr (0xA028B142+1)//int GetPrfileVolumeSetting(int profile, int type)
//  GetCPUClock();
  return (((int (*)(int, int))GetPrfileVolumeSetting_adr)(GetProfile(), VOLUME));
}*/

void PopupNewIn::UpdateCSMName(DLG_CSM *dlg_csm, int lgp)
{
  wsprintf(&((DLGCSM_DESC *)dlg_csm->csm_ram.constr)->csm_name, PERCENT_T, lgp);
}


const SOFTKEY_DESC msm_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,LGP_DOIT_PIC}
};

const SOFTKEYSTAB msm_skt={msm_sk, 0};

POPUP_DESC MyShowMsg::popup=
{
  8,
    MyShowMsg::OnKey,
    MyShowMsg::GHook,
    NULL,
    softkeys,
    &msm_skt,
    0x1,
    LGP_NULL,
    NULL,
    0,
    FONT_MEDIUM,
    100,
    101,
    0x7D4
};

void MyShowMsg::GHook(void *data, int cmd)
{
//  if(cmd==0x3)
//  {
//    MyShowMsg *p=(MyShowMsg *)GetPopupUserPointer(data);
//    delete p;
//  }
}

int MyShowMsg::OnKey(void *data, GUI_MSG *msg)
{
  if(msg->keys==1
    || msg->keys==0x18
    || msg->keys==0x3D
    )
    return 1;
  return 0;
}

int MyShowMsg::MyShow(int flag, WSHDR *msg)
{
  if(!msg) return 0;
  return CreatePopupGUI_ws(flag, NULL, &MyShowMsg::popup, msg);
}

int MyShowMsg::MyShow(int flag, char *msg)
{
  if(!msg) return 0;
  return CreatePopupGUI(flag, NULL, &MyShowMsg::popup, (int)msg);
}


