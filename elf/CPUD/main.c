#include "..\inc\swilib.h"
/*
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
*/
CSM_DESC icsmd;

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

GBSTMR mytmr;
/*
extern const int Mode1;
extern const int Mode2;
extern const int Mode3;
extern const int Mode4;
extern const int Mode5;
extern const int Mode6;
extern const int Mode7;
extern const int Mode8;
extern const int Welcome;
extern const int global;
extern const unsigned int hiusg;
extern const unsigned int lousg;
extern const unsigned int lowakku;

void ShowWelcome(void)
{
  if(Welcome==1)
    ShowMSG(1,(int)"CPUD started!");
}

void Check(void);
*/
#pragma swi_number=0x221
__swi __arm int SetCpuClockLow();

#pragma swi_number=0x222
__swi __arm int SetCpuClockTempHi();

#pragma swi_number=0x0C5
__swi __arm int IsIdleUiOnTop();
/*
void Auto(void)
{  
  if(lowakku>0)
  {
    int cap_akku = *RamCap();
    if(cap_akku>lowakku)
    {
#ifdef NEWSGOLD
    if(IsIdleUiOnTop()==1)
#else
    int result= * RamStby();
    if(result==1)
#endif
       {
        SetCpuClockLow(2);
        GBS_StartTimerProc(&mytmr, 64, Check);
       }
    else
       {
        SetCpuClockTempHi(2);
        GBS_StartTimerProc(&mytmr, 64, Check);
       }
    }
    else
       {
        SetCpuClockLow(2);
        GBS_StartTimerProc(&mytmr, 64, Check);
       }
  }
  else
    {
#ifdef NEWSGOLD
    if(IsIdleUiOnTop()==1)
#else
    int result= * RamStby();
    if(result==1)
#endif
       {
        SetCpuClockLow(2);
        GBS_StartTimerProc(&mytmr, 64, Check);
       }
    else
       {
        SetCpuClockTempHi(2);
        GBS_StartTimerProc(&mytmr, 64, Check);
       }
    }
}

void set52(void)
{
   SetCpuClockLow(2);
   GBS_StartTimerProc(&mytmr, 32, Check);
}

void set208(void)
{
   SetCpuClockTempHi(2);
   GBS_StartTimerProc(&mytmr, 32, Check);
}

void Off(void)
{
   GBS_StartTimerProc(&mytmr, 32, Check);
}

int zet;
GBSTMR mytmr2;

void evil_add(void)
{
  if (zet>0)
  {
    SetCpuClockTempHi(2);
    zet--;
   GBS_StartTimerProc(&mytmr2, 32, evil_add);
  }
}

void evil_add2(void)
{
  if (zet>0)
  {
    SetCpuClockLow(2);
    zet--;
   GBS_StartTimerProc(&mytmr2, 32, evil_add);
  }
}
    

void Smart(void)
{
   int load=GetCPULoad();
   int clk=GetCPUClock();
     
       if (load>hiusg)
         {
            if (clk<=52)SetCpuClockTempHi(2);
#ifdef ELKA
            if (clk<=104)SetCpuClockTempHi(2);
            zet=33;
            GBS_StartTimerProc(&mytmr2, 32, evil_add);
#endif
         }
       else 
         {
            if (load<lousg)
            if(clk==104)SetCpuClockLow(2);
#ifdef ELKA
            if(clk==208)SetCpuClockLow(2);
            zet=33;
            GBS_StartTimerProc(&mytmr2, 32, evil_add2);
#endif
         }
   
       GBS_StartTimerProc(&mytmr, 216*5, Check);
}

void Check(void)
{
  char Mode;
if(global)
  Mode = Mode1;
else
 {
  char profile = GetProfile();
if(profile==0)
  Mode = Mode1;
if(profile==1)
  Mode = Mode2;
if(profile==2)
  Mode = Mode3;
if(profile==3)
  Mode = Mode4;
if(profile==4)
  Mode = Mode5;
if(profile==5)
  Mode = Mode6;
if(profile==6)
  Mode = Mode7;
if(profile==7)
  Mode = Mode8;
 }
  
  if(Mode==0)
     {Auto();}
  if(Mode==1)
     {set52();}
  if(Mode==2)
     {set208();}
  if(Mode==3)
     {Smart();}
}
*/
void Check2()
{
  if(IsIdleUiOnTop()) SetCpuClockLow(2);
  else
  SetCpuClockTempHi(2);
  GBS_StartTimerProc(&mytmr, 40, Check2);
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
  Check2();
  /*
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"CPUD config updated!");
      InitConfig();
    }
  }
//  SetCpuClockTempHi(2);
  */
  return (1);  
  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
//  GBS_DelTimer(&mytmr2);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"CPUD-Mini");
}

int main(void)
{
//  InitConfig();

  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname(); 
  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched(); 
//  ShowWelcome();
  
//  Check();
  Check2();
  return 0;
}
