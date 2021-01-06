#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#define MIN_UPTIME 1
#define MAX(a,b) (a)>(b)?(a):(b)

GBSTMR timer;
extern const int ENA_HELLO_MSG;
const int minus11=-11;

extern const int dis;
extern const int key;
extern const int lig;
extern const int dyn;

extern const int lockdis;
extern const int lockkey;
extern const int locklig;
extern const int lockdyn;

extern const unsigned int light;
extern const unsigned int delay;
unsigned int uiUpdateTime;
extern const unsigned int cfgUpTime;
extern const int key_patch;

char b[256];
int prespace0, space0, 
    prespace1, space1,
    prespace2, space2,
    prespace4, space4, count, Oldillum;

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
    {ShowMSG(1,(int)"Write flasher settings refreshed!");
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
{wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Write flasher - (c)SimaFish");
}

void StartWorkTimer(void);
void InitSettings();
void LightOn();
void LightOff();

void LightOn()
{if(IsUnlocked())
 {if(key) SetIllumination(1,1,light,0); 
  if(dis) SetIllumination(0,1,light,0);
  if(dyn) SetIllumination(2,1,light,0);
  if(lig) SetIllumination(4,1,100,0);
 }
 if(!IsUnlocked())
 {if(lockkey) SetIllumination(1,1,light,0); 
  if(lockdis) SetIllumination(0,1,light,0);
  if(lockdyn) SetIllumination(2,1,light,0);
  if(locklig) SetIllumination(4,1,100,0);
 }
 GBS_StartTimerProc(&timer,delay,LightOff);
}

void LightOff(void)
{if(IsUnlocked())
 {if(key) SetIllumination(1,1,0,0);
  if(dis) SetIllumination(0,1,0,0);
  if(dyn) SetIllumination(2,1,0,0);
  if(lig) SetIllumination(4,1,0,0);
 }
 if(!IsUnlocked())
 {if(lockkey) SetIllumination(1,1,0,0);
  if(lockdis) SetIllumination(0,1,0,0);
  if(lockdyn) SetIllumination(2,1,0,0);
  if(locklig) SetIllumination(4,1,0,0);
 }
 count--;
 if (count>0)
 {GBS_StartTimerProc(&timer,delay,LightOn);
 }
 else 
 {SetIllumination(0,1,Oldillum,0);
  if(!key_patch) SetIllumination(1,1,Oldillum,0);
  GBS_StartTimerProc(&timer, uiUpdateTime, StartWorkTimer);
 }
}

void StartWorkTimer(void)
{ Oldillum=GetIlluminationDataTable()[3];
  space0=GetFreeFlexSpace(0,0);
  space1=GetFreeFlexSpace(1,0);
  space2=GetFreeFlexSpace(2,0);
  space4=GetFreeFlexSpace(4,0);
  if(prespace0!=space0)
  {if((key||dis||lig||dyn)&&(!IsCalling())) LightOn();
   prespace0=space0;
  }   
  else
  if(prespace1!=space1)
  {if((key||dis||lig||dyn)&&(!IsCalling())) LightOn();
   prespace1=space1;
  }   
  else
  if(prespace2!=space2)
  {if((key||dis||lig||dyn)&&(!IsCalling())) LightOn();
   prespace2=space2;
  }  
  else
  if(prespace4!=space4)
  {if((key||dis||lig||dyn)&&(!IsCalling())) LightOn();
   prespace4=space4;
  }
  else GBS_StartTimerProc(&timer, uiUpdateTime, StartWorkTimer);
}

void InitSettings()
{InitConfig();
 uiUpdateTime = MAX(((216*cfgUpTime)/10),MIN_UPTIME);
 prespace0=GetFreeFlexSpace(0,0);
 prespace1=GetFreeFlexSpace(1,0);
 prespace2=GetFreeFlexSpace(2,0);
 prespace4=GetFreeFlexSpace(4,0);
 if(ENA_HELLO_MSG) ShowMSG(1,(int)"Write flasher installed!                   (c)SimaFish!");
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
