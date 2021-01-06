#include "c:\arm\inc\swilib.h"
#include "conf_loader.h"
#define MIN_UPTIME 1
#define MAX(a,b) (a)>(b)?(a):(b)
void StartWorkTimer();
void InitSettings();

GBSTMR timer;
GBSTMR tmr_vibra;
extern const int ENA_WAV;
extern const int ENA_HELLO_MSG;
const int minus11=-11;
extern const unsigned int cfgUpTime;
unsigned int uiUpdateTime;
extern const char unlockfname[128];
extern const char lockfname[128];
extern const unsigned int MelVolume;
extern const unsigned int vibra_count;
extern const unsigned int vibra_power;
unsigned int vibra_count1;
unsigned int volume;

int m=0;

typedef struct
{CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline=forced

int toupper(int c)
{if ((c>='a')&&(c<='z')) c+='A'-'a';
 return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{int i,c;
 while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
 return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{if(msg->msg == MSG_RECONFIGURE_REQ) 
  {extern const char *successed_config_filename;
    if(strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {ShowMSG(1,(int)"Vibralocker settings updated!");
     InitConfig();
    }
  }
 return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void Killer(void)
{extern void *ELF_BEGIN;
 GBS_DelTimer(&timer);
 GBS_DelTimer(&tmr_vibra);
 kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{CSM_DESC maincsm;
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
{wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Vibralocker - (c)SimaFish");
}

void Play(const char *fname)
{
  if (!IsCalling())
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
      _sfo1.volume=volume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      /*PLAY_ID=*/PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      /*PLAY_ID=*/PlayFile(0xC, sndPath, sndFName, 0,MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      /*PLAY_ID=*/PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
  }
}

void start_vibra(void)
{void stop_vibra(void);
  if(!IsCalling())
  {SetVibration(vibra_power);
   GBS_StartTimerProc(&tmr_vibra,216>>1,stop_vibra);
  }  
}

void stop_vibra(void)
{SetVibration(0);
 if (--vibra_count1) GBS_StartTimerProc(&tmr_vibra,216>>1,start_vibra); 
}

void StartWorkTimer()
{if((!IsUnlocked())&&(m==0))
 {start_vibra();
  volume=MelVolume;
  if(ENA_WAV) Play(lockfname);
  vibra_count1=vibra_count;
  m=1;
 }
 if((IsUnlocked())&&(m==1))
 {start_vibra();
  volume=MelVolume;
  if(ENA_WAV) Play(unlockfname);
  vibra_count1=vibra_count;  
  m=0;
 }  
 GBS_StartTimerProc(&timer, uiUpdateTime, StartWorkTimer);
}

void InitSettings()
{InitConfig();
 if(ENA_HELLO_MSG) ShowMSG(1,(int)"Vibralocker installed!                (c)SimaFish");
 uiUpdateTime = MAX(((216*cfgUpTime)/10),MIN_UPTIME);
 StartWorkTimer();
}

void main()
{ 
  InitSettings();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();  
}
