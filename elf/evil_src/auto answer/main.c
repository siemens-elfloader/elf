#include "..\inc\swilib.h"
#include "conf_loader.h"
#pragma swi_number=0x0C5	
__swi __arm int IsIdleUiOnTop();
int DictatingMachine();
int DictatingMachine2();
extern const int zajebalo;
extern const int zajebalo2;
extern const int aija[128];
//extern const int sudinji;
const int minus11=-11;
int sndVolume = 6;
//extern const char sound_wav[];
unsigned short maincsm_name_body[140];
extern void kill_data(void *p, void (*func_p)(void *));
GBSTMR mytmr;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

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


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"AutoAnswer config updated!");
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
  GBS_StopTimer(&mytmr);
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"CallWriter(alfa) - (c)Evilfox");
}
/*
void Play(const char *fname)
{
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      
      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=sndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
}
*/
void dictate(void);
void Check3(void);
void Check(void);

void dictate3()
{
 GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON); 
 GBS_SendMessage(MMI_CEPID,KEY_UP,ENTER_BUTTON);
 GBS_StartTimerProc(&mytmr, 50, dictate);
}

void dictate2()
{
   GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON); 
 GBS_SendMessage(MMI_CEPID,KEY_UP,ENTER_BUTTON);
  GBS_StartTimerProc(&mytmr, 50, dictate3);
}
void save(void);
void dictate()
{
 if (GetTypeOfCall(1))
 GBS_StartTimerProc(&mytmr, 262, dictate);
 else
 {
   GBS_StartTimerProc(&mytmr, 50, Check3);
 }
}

#define MMI_CEPID 0x4209
void Check3()
{
  if (IsIdleUiOnTop())
    GBS_StartTimerProc(&mytmr, 262, Check);
  else
  {
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT); 
    GBS_SendMessage(MMI_CEPID,KEY_UP,RIGHT_SOFT);   
    GBS_StartTimerProc(&mytmr, 100, Check3);
  }
}

void Check()
{
  if (GetTypeOfCall(1))
  {
//    Play(sound_wav);
    DictatingMachine();
    GBS_StartTimerProc(&mytmr, 100, dictate2);
  }
 else
   GBS_StartTimerProc(&mytmr, 262, Check);
}

int main()
{
//  InitConfig();
  if(zajebalo)
  {
    ShowMSG(1,(int)"Callwriter(alfa) - (c)Evilfox");
    }
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
 Check();
}
