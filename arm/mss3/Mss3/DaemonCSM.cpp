#include "include.h"

#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "SmsListMenu.h"
#include "DialogCSM.h"
#include "Vibra.h"
#include "PlaySound.h"
//#include "ShortVibra.h"

#include "SendList.h"
#include "CSMswaper.h"
#include "DaemonCSM.h"

#include "AdrList.h"
#include "CodeShow.h"
#include "..\..\inc\playsound.h"
#include "..\..\inc\mplayer.h"
#include "Mss3App.h"
#include "KeyHook.h"
/*
const CSM_DESC DaemonCSM::csm_desc_tpl=
{
  DaemonCSM::OnMessage,
  DaemonCSM::OnCreate,
#ifdef NEWSGOLD
  0,0,0,0,
#endif
  DaemonCSM::OnClose,
  sizeof(DAEMON_CSM),
  1,
  &minus11
};
*/
DaemonCSM::DaemonCSM()
{
  daemon_csm_desc.csm_desc.onMessage=OnMessage;
  daemon_csm_desc.csm_desc.onCreate=OnCreate;
  daemon_csm_desc.csm_desc.onClose=OnClose;
#ifdef NEWSGOLD
  daemon_csm_desc.csm_desc.zero1=0;
  daemon_csm_desc.csm_desc.zero2=0;
  daemon_csm_desc.csm_desc.zero3=0;
  daemon_csm_desc.csm_desc.zero4=0;
#endif
  daemon_csm_desc.csm_desc.datasize=sizeof(DAEMON_CSM);
  daemon_csm_desc.csm_desc.statesize=1;
  daemon_csm_desc.csm_desc.states=&minus11;
  //memcpy(&daemon_csm_desc.csm_desc, &DaemonCSM::csm_desc_tpl, sizeof(CSM_DESC));
  daemon_csm_desc.csm_name.wsbody=this->csm_name_body;
  daemon_csm_desc.csm_name.ws_malloc=NAMECSM_MAGIC1;
  daemon_csm_desc.csm_name.ws_mfree=NAMECSM_MAGIC2;
  daemon_csm_desc.csm_name.isbody_allocated=0;
  daemon_csm_desc.csm_name.maxlen=DAEMON_NAME_LEN;
  zeromem(this->DLGCSM_IDS, sizeof(this->DLGCSM_IDS));
  this->is_new_proc=0;
  this->temp_tmr_index=0;
  //this->PLAY_ID=0;
#ifdef ICONBAR
  strcpy(this->daemon_csm_desc.iconbar_handler.check_name, "IconBar");
  this->daemon_csm_desc.iconbar_handler.addr=(int)this->AddIconBar;
#endif
  this->vibra=new Vibra;
  this->playsound=new PlaySouNd;
  this->sndlst=new SendList;
  //this->shortvibra=new ShortVibra;
}

DaemonCSM::~DaemonCSM()
{
  delete this->vibra;
  delete this->playsound;
  delete this->sndlst;
  //delete this->shortvibra;
}

void DaemonCSM::CreateDaemonCSM(void)
{
  CSM_RAM *save_cmpc;
  CSMROOT *csmr;
  DAEMON_CSM daemon_csm;
  zeromem(&daemon_csm, sizeof(DAEMON_CSM));
  daemon_csm.daemon=this;
  //csm name
  wsprintf(&daemon_csm_desc.csm_name, "%t", ELFFNAMED);
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=(CSM_RAM *)csmr->csm_q->csm.first;
  CreateCSM(&daemon_csm_desc.csm_desc,&daemon_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
}

void DaemonCSM::OnCreate(CSM_RAM *data)
{
  LGP=new LangPack;
  IP=new IconPack;
  ADRLST=new AdrList;
  SMSDATA=new SmsData;
  KeyHook::Create();
  //CodeShow::LoadDB();
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}


int DaemonCSM::OnMessage(CSM_RAM *data, GBS_MSG *msg)
{
#ifdef NEWSGOLD

#ifdef ELKA
#define MSG_EMS_FFS_WRITE 0x6105
#else
#define MSG_EMS_FFS_WRITE 0x61CB
#endif

#ifdef ELKA
#define MSG_EMS_INCOMING 0x6106 //ELKA,À´×Ôsmsman
#else
#define MSG_EMS_INCOMING 0x61CC
#define MSG_EMS_INCOMING_2 0x61D6
#endif

#endif

  DAEMON_CSM *daemon_csm=(DAEMON_CSM *)data;
  DaemonCSM *daemon=daemon_csm->daemon;
  if (msg->msg==MSG_EMS_FFS_WRITE)
  {
    if ((int)msg->data1==0x8 || (int)msg->data1==0x408)
    {
      if (SMSDATA->IsNewSMS((int)msg->data0))
      {
	if(IsTimerProc(&daemon->chktmr)) GBS_DelTimer(&daemon->chktmr);
	daemon->is_new_proc=1;
	daemon->temp_tmr_index=(int)msg->data0;
	GBS_StartTimerProc(&daemon->chktmr, 216/2, daemon->DoNewProc);
      }
      else goto CHK_IT;
    }
    else
    {
    CHK_IT:
      int chk_res;
      chk_res=SMSDATA->CheckSMS((int)msg->data0);
      if(chk_res==2)
      {
	if(daemon->IsOnTopMyCSM())
	  RefreshGUI();
      }
      else if(chk_res==1)
      {
	if(!daemon->is_new_proc)
	{
	  if(IsTimerProc(&daemon->chktmr)) GBS_DelTimer(&daemon->chktmr);
	  daemon->temp_tmr_index=(int)msg->data0;
	  GBS_StartTimerProc(&daemon->chktmr, 216/2, daemon->UpdateNProc);
	}
      }
    }
    if((!(SMSDATA->n_new=SMSDATA->GetSMSCount(TYPE_IN_N)))&&(CFG_ENA_NOTIFY))
    {
      daemon->vibra->VibraStop();
      //if(daemon->PLAY_ID)
      //{
	//PlayMelody_StopPlayback(daemon->PLAY_ID);
	//daemon->PLAY_ID=0;
      //}
      daemon->playsound->PlayStop();
    }
  }
  if(msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if((ipc=(IPC_REQ *)msg->data0))
    {
      if(!strcmp(ipc->name_to, IPC_NAME))
      {
	switch(msg->submess)
	{
	case SMSYS_IPC_SMS_DATA_UPDATE:
	  if(daemon->IsOnTopMyCSM())
	    RefreshGUI();
	  break;
	case SMSYS_IPC_UPDATE_CLIST:
	  SUBPROC((void *)ADRLST->ConstructListFRC, ADRLST);
	  break;
	case SMSYS_IPC_READ_NEW:
	  if (daemon->temp_tmr_index)
	  {
	    if (SMSDATA->ReadMessageOne(daemon->temp_tmr_index))
	    {
	      if (CFG_ENA_NOTIFY) SendMyIpc(SMSYS_IPC_NEW_IN_ME, (void *)daemon->temp_tmr_index);//myipc.SendIpc(SMSYS_IPC_NEW_IN_WIN, (void *)daemon->temp_tmr_index);
	      else if (daemon->IsOnTopMyCSM()) RefreshGUI();
	    }
	    daemon->temp_tmr_index=0;
	  }
	  daemon->is_new_proc=0;
	  break;
	case SMSYS_IPC_READ_SMS:
	  if (daemon->temp_tmr_index)
	  {
	    if (SMSDATA->ReadMessageOne(daemon->temp_tmr_index))
	    {
	      if (daemon->IsOnTopMyCSM()) RefreshGUI();
	    }
	    daemon->temp_tmr_index=0;
	  }
	  break;
	//case SMSYS_IPC_NAB_CREATE:
	case SMSYS_IPC_ADD_CSMID:
	  if(ipc->data)
	  {
	    if(!daemon->AddDlgCsmID((int)ipc->data))
	      daemon->AddDlgCsmID_Forced0((int)ipc->data);
	  //  ipc->data=NULL;
	  }
	  break;
	case SMSYS_IPC_ARCHIVE:
	  extern void OpenArchive(void); //othmenu.cpp
	  SUBPROC((void *)OpenArchive);
	  break;
	case SMSYS_IPC_VIBRA_START:
	  daemon->vibra->VibraStart();
	  break;
	case SMSYS_IPC_VIBRA_STOP:
	  daemon->vibra->VibraStop();
	  break;
	case SMSYS_IPC_VIBRA_NEXT:
	  daemon->vibra->VibraNext();
	  break;
	case SMSYS_IPC_SOUND_PLAY:
	  if(ipc->data && CFG_ENA_SOUND && !(*(RamRingtoneStatus())) && CFG_NOTIFY_TIME && !IsCalling())
	  {
	    if(GetPlayStatus()) MPlayer_Stop();
	    SUBPROC((void *)PlaySouNd::PlayStart, daemon->playsound, ipc->data);
	    //if(daemon->PLAY_ID)
	    //{
	    //  PlayMelody_StopPlayback(daemon->PLAY_ID);
	    //  daemon->PLAY_ID=0;
	    //}
	    //SUBPROC((void *)daemon->PlayNotifySound, daemon, (char *)ipc->data);
	  //  ipc->data=NULL;
	  }
	  break;
	case SMSYS_IPC_SOUND_STOP:
	  {
	    //if(daemon->PLAY_ID)
	    //{
	    //  PlayMelody_StopPlayback(daemon->PLAY_ID);
	    //  daemon->PLAY_ID=0;
	    //}
	    daemon->playsound->PlayStop();
	    if(CFG_ENA_SOUND && IsPlayerOn() && !GetPlayStatus()) MPlayer_Start();
	  }
	  break;
	case SMSYS_IPC_SEND_LIST:
	  {
	    if(ipc->data)
	    {
	      daemon->sndlst->CatList((SNDLST *)ipc->data);
	    //  ipc->data=NULL;
	    }
	    SUBPROC((void *)SendList::Send, daemon->sndlst);
            //if(CFG_ENA_SNED_ON_BG)
            //  daemon->sndlst->SendStart();
            //else
            //  SUBPROC((void *)daemon->sndlst->SendOnTop, daemon->sndlst);
	  }
	  break;
	default:
	  {
	    //int id;
	    //DialogCSM *dlg=new DialogCSM;
	    //id=dlg->CreateDialogCSM(msg->submess, ipc->data);
	    //if(!daemon->AddDlgCsmID(id))
	    //  daemon->AddDlgCsmID_Forced0(id);
	    SUBPROC((void *)DaemonCSM::StartDialog, msg->submess, ipc->data);
	    //if(ipc->data
	    //  && ((unsigned int)ipc>>27)==0x15
	    //  )
	    //{
	    //  ipc->data=NULL;
	    //}
	  }
	  break;
	}
      }
    }
  }
  if(msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    extern void InitSetting(void); //main.cpp
    if(!strcmp_nocase(successed_config_filename,(char *)msg->data0))
    {
      Mss3App::InitSetting();
      ShowMSG(1,(int)LGP->lgp.LGP_CONFIG_UPDATE);
      ADRLST->ConstructListCFGUPD();
      daemon->vibra->ReInitThythm();
    }
  }
  if(msg->msg==MSG_CSM_DESTROYED)
  {
    if(daemon->sndlst->SendEnd((int)msg->data0))
    {
      //daemon->shortvibra->Start();
    }
    SUBPROC((void *)SendList::Send, daemon->sndlst);
    //if(CFG_ENA_SNED_ON_BG)
    //  daemon->sndlst->SendStart();
    //else
    //  SUBPROC((void *)daemon->sndlst->SendOnTop, daemon->sndlst);
    daemon->DelDlgCsmID((int)msg->data0);
  }
  //if(msg->msg==MSG_GUI_DESTROYED)
  //{
  //  daemon->sndlst->SendGUIDesMSG(msg);
  //}
  if(/*daemon->PLAY_ID && */(msg->msg==MSG_INCOMMING_CALL || IsCalling()))
  {
    daemon->playsound->PlayStop();
    //PlayMelody_StopPlayback(daemon->PLAY_ID);
    //daemon->PLAY_ID=0;
  }
  if(msg->msg==MSG_PLAYFILE_REPORT/* && daemon->PLAY_ID*/) 
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    //if(pmsg->handler==daemon->PLAY_ID)
    if(pmsg->handler==daemon->playsound->GetHandle())
    {
      if(pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE)
	daemon->playsound->PlayDone();
	//daemon->PLAY_ID=0;
    }
  }
  return 1;
}

void DaemonCSM::OnClose(CSM_RAM *data)
{
  DAEMON_CSM *daemon_csm=(DAEMON_CSM *)data;
  daemon_csm->daemon->CloseAllDlgCSM();
  GBS_DelTimer(&daemon_csm->daemon->chktmr);
  delete LGP;
  delete IP;
  delete ADRLST;
  delete SMSDATA;
  KeyHook::Remove();
  //CodeShow::UnloadDB();
  delete daemon_csm->daemon;
  extern void ElfKiller(void); //main.cpp
  SUBPROC((void *)Mss3App::Killer);
}


int DaemonCSM::AddDlgCsmID(int id)
{
  int i;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(!this->DLGCSM_IDS[i])
    {
      this->DLGCSM_IDS[i]=id;
      return 1;
    }
  }
  return 0;
}

void DaemonCSM::AddDlgCsmID_Forced0(int id)
{
  CloseCSM(this->DLGCSM_IDS[0]);
  this->DLGCSM_IDS[0]=id;
}

void DaemonCSM::CloseAllDlgCSM(void)
{
  int i;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(this->DLGCSM_IDS[i])
    {
      CloseCSM(this->DLGCSM_IDS[i]);
      this->DLGCSM_IDS[i]=0;
    }
  }
}

void DaemonCSM::DelDlgCsmID(int id)
{
  int i;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(this->DLGCSM_IDS[i]==id)
    {
      this->DLGCSM_IDS[i]=0;
      return;
    }
  }
}

int DaemonCSM::IsOnTopMyCSM(void)
{
  int i;
  CSM_RAM *icsm;
  if(!(icsm=this->GetTopCSM()) || !icsm->id)
    return 0;
  for(i=0;i<DLGCSM_ID_MAX;i++)
  {
    if(this->DLGCSM_IDS[i]==icsm->id)
      return 1;
  }
  return 0;
}

void DaemonCSM::DoNewProc(void)
{
  SendMyIpc(SMSYS_IPC_READ_NEW);
}

void DaemonCSM::UpdateNProc()
{
  SendMyIpc(SMSYS_IPC_READ_SMS);
}

#ifdef ICONBAR
void DaemonCSM::AddIconBar(short* num)
{
  if(CFG_ENA_IB && SMSDATA->n_new) AddIconToIconBar(CFG_ICON_IB, num);
}
#endif
//DEL void DaemonCSM::PlayNotifySound(DaemonCSM *daemon, char *filepath)
//DEL {
//DEL   PLAYFILE_OPT _sfo1;
//DEL   WSHDR *sndPath,sndPathn;
//DEL   WSHDR *sndFName,sndFNamen;
//DEL   unsigned short sndPathb[128];
//DEL   unsigned short sndFNameb[128];
//DEL   char s[128];
//DEL   const char *p;
//DEL   CFile file;
//DEL   int snd_vol;
//DEL   if(
//DEL     !daemon
//DEL     || !filepath
//DEL     || !file.IsFileExist(filepath)
//DEL     || !CFG_ENA_SOUND
//DEL     || !(snd_vol=GetProfileVolumeSetting(GetProfile(), VOLUME))
//DEL     )
//DEL     return;
//DEL   sndPath=CreateLocalWS(&sndPathn, sndPathb, 128);
//DEL   sndFName=CreateLocalWS(&sndFNamen, sndFNameb, 128);
//DEL   p=strrchr(filepath,'\\')+1;
//DEL   str_2ws(sndFName,p,128);
//DEL   strncpy(s,filepath,p-filepath);
//DEL   s[p-filepath]='\0';
//DEL   str_2ws(sndPath,s,128);
//DEL   zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
//DEL   _sfo1.repeat_num=1;
//DEL   _sfo1.time_between_play=0;
//DEL   _sfo1.play_first=0;
//DEL   _sfo1.volume=snd_vol;//
//DEL #ifdef NEWSGOLD
//DEL   _sfo1.unk6=1;
//DEL   _sfo1.unk7=1;
//DEL   _sfo1.unk9=2;
//DEL   daemon->PLAY_ID=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
//DEL #else
//DEL #ifdef X75
//DEL   _sfo1.unk4=0x80000000;
//DEL   _sfo1.unk5=1;
//DEL   daemon->PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
//DEL #else
//DEL   _sfo1.unk5=1;
//DEL   daemon->PLAY_ID=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
//DEL #endif
//DEL #endif
//DEL }


CSM_RAM * DaemonCSM::GetTopCSM()
{
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if(!icsm) return 0;
  while(icsm->next) icsm=(CSM_RAM *)icsm->next;
  return icsm;
}

void DaemonCSM::StartDialog(int submess, void *data)
{
  int id;
  DialogCSM *dlg=new DialogCSM;
  id=dlg->CreateDialogCSM(submess, data);
  if(id) SendMyIpc(SMSYS_IPC_ADD_CSMID, (void *)id);
}
