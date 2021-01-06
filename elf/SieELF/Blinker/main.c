#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

#define TICK 216
#define IN_TICKS(sec) (sec * TICK)

#define CFGUPD_INTV 5

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;


// Импорт переменных
extern const int cfgEvents;
extern const unsigned int cfgMaxEv;
extern const unsigned int cfgInterval;
extern const int cfgLockOnly;
extern const unsigned int cfgPeriod;
extern const unsigned int cfgBright;

extern const int use_vib;
extern const unsigned int vibra_pow;
extern const int use_snd;
extern const unsigned int sndNum;
extern const char snd_file[128];
extern const int sound_type;
extern const unsigned int sndVolume;

extern const int cfgKbd;
extern const int cfgDispl;
#ifndef NEWSGOLD
extern const int cfgDyn;
#else
extern const int cfgLighter;
#endif

int count = 0;
//int cycl_cnt = 0;

GBSTMR mytmr;

void LightOff(void);
void Check(void);

//SetIllumination(unsigned char dev,unsigned long param1,unsigned short bright,unsigned long delay);
//0 - диспле? 1 - клавиатура, 2 - динамический свет (x65)
void LightOn()
{
	if (cfgDispl)
		SetIllumination(0, 1, cfgBright, 0);
	if (cfgKbd)
		SetIllumination(1, 1, cfgBright, 0);   
#ifndef NEWSGOLD
	if (cfgDyn)
		SetIllumination(2, 1, cfgBright, 0);
#else
	if (cfgLighter)
		SetIllumination(4, 1, cfgBright, 0);
#endif
  if (use_vib)
    SetVibration(vibra_pow);    
  
	GBS_StartTimerProc(&mytmr, IN_TICKS(cfgPeriod) / 20, LightOff);
}

void LightOff()
{
	if (cfgDispl)
		SetIllumination(0, 1, 0, 0);
	if (cfgKbd)
		SetIllumination(1, 1, 0, 0);   
#ifndef NEWSGOLD
	if (cfgDyn)
		SetIllumination(2, 1, 0, 0);
#else
	if (cfgLighter)
		SetIllumination(4, 1, 0, 0);
#endif
  if (use_vib)
    SetVibration(0); 
  
	if (--count)
		GBS_StartTimerProc(&mytmr, IN_TICKS(cfgPeriod) / 20, LightOn);
	else
		GBS_StartTimerProc(&mytmr, IN_TICKS(cfgInterval), Check); 
}
#ifdef NEWSGOLD
#pragma swi_number=0x9E
__swi __arm GetMissedEventCount(unsigned int Event);
#endif

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

void play_sound(void)
{
  if(sound_type)
    Play(snd_file);
  else PlaySound(0, 0, 0, sndNum, 0);
}

void Check(void)
{
	if (!(IsUnlocked() && cfgLockOnly))
	{
#ifdef NEWSGOLD          
		if ((count = GetMissedEventCount(cfgEvents)) > 0
#else
                if (cfgEvents==0 || cfgEvents==2)
                     count=GetMissedCallsCount();
                if ((cfgEvents==1 || cfgEvents==2) && HasNewSMS())
                      count++;
                if ((count) > 0
#endif
			&& (cfgDispl || cfgKbd || 
#ifndef NEWSGOLD
				cfgDyn)
#else
				cfgLighter)
#endif
			)
		{
			if (count > cfgMaxEv)
				count = cfgMaxEv;
			LightOn();
                        if (use_snd)
                          play_sound();
			return;
		}
	}

	GBS_StartTimerProc(&mytmr, IN_TICKS(cfgInterval), Check);
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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Blinker config updated!");
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
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Blinker");
}

int main(void)
{
  //ShowMSG(1, (int)"Blinker started!");
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();  
  UpdateCSMname();

  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();        
        
  Check();
  return 0;
}
