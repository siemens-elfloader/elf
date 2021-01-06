#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "RANDOM.H"
//#pragma swi_number=0x09B
//__swi __arm int CameraLightOnOff();
//        defadr  CameraLightOnOff,0xA06F6617
          
#pragma swi_number=0x09E
__swi __arm int GetMissedEventCount(unsigned int Event);
int CameraLightOnOff();
/*
extern const unsigned int lenght;
extern const unsigned int lenght2;
extern const unsigned int lenght3;
extern const unsigned int lenght4;
extern const unsigned int lenght_call;
extern const unsigned int lenght2_call;
extern const unsigned int lenght3_call;
extern const unsigned int lenght4_call;
extern const unsigned int lenght_sms;
extern const unsigned int lenght2_sms;
extern const unsigned int lenght3_sms;
extern const unsigned int lenght4_sms;
extern const int zajebalo;
extern const int Calling_Mode;
extern const int Talking_Mode;
extern const int Missed_Mode;
extern const int Blinks_Mode;
extern const int Randomed;
extern const int sudinji;
int ra;
*/
const int minus11=-11;
unsigned short maincsm_name_body[140];
extern void kill_data(void *p, void (*func_p)(void *));
GBSTMR mytmr;

//defadr CameraLightOnOff,0xA1234567
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
      ShowMSG(1,(int)"SMS Informer config updated!");
      InitConfig();
    }
  }  

  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
//  Randomize();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_StopTimer(&mytmr);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SMS Informer - (c)Evilfox");
}
/*
void Check(void);
void Calling_Off(void);
void Calling_Off2(void);
void Timer_Off(void);
void Calling_Off2_Calling(void);
void Calling_Off_Calling(void);

void Calling_Off_Talking()
{
  if (!GetTypeOfCall(1))
  {
    if(Randomed)
       {
         ra = Random();
    GBS_StartTimerProc(&mytmr, ra, Calling_Off_Talking);
       }
       else
         GBS_StartTimerProc(&mytmr, 262, Calling_Off_Talking);
  }
  else
    Calling_Off();
}

void Calling_On_Calling()
{
   CameraLightOnOff();
         if(Randomed)
       {
         ra = Random();
   GBS_StartTimerProc(&mytmr, ra, Calling_Off2_Calling);
       }
       else
         GBS_StartTimerProc(&mytmr, 10*lenght2, Calling_Off2_Calling);
}

void Calling_On2_Calling()
{
   CameraLightOnOff();
         if(Randomed)
       {
         ra = Random();
   GBS_StartTimerProc(&mytmr, ra, Calling_Off_Calling);
       }
            else
              GBS_StartTimerProc(&mytmr, 10*lenght4, Calling_Off_Calling);
}

void Calling_Off_Calling()
{
  if (!GetTypeOfCall(1))
  {
    CameraLightOnOff();
          if(Randomed)
       {
         ra = Random();
    GBS_StartTimerProc(&mytmr, ra, Calling_On_Calling);
       }
       else
         GBS_StartTimerProc(&mytmr, 10*lenght2, Calling_On_Calling);
  }
  else
    GBS_StartTimerProc(&mytmr, 262, Check);
}

void Calling_Off2_Calling()
{
  CameraLightOnOff();
    if(Randomed)
       {
         ra = Random();
  GBS_StartTimerProc(&mytmr, ra, Calling_On2_Calling);
       }
  else
    GBS_StartTimerProc(&mytmr, 10*lenght3, Calling_On2_Calling);
}

void Calling_On()
{
   CameraLightOnOff();
         if(Randomed)
       {
         ra = Random();
   GBS_StartTimerProc(&mytmr, ra, Calling_Off2);
       }
   else
     GBS_StartTimerProc(&mytmr, 10*lenght2, Calling_Off2);
}

void Calling_On2()
{
   CameraLightOnOff();
         if(Randomed)
       {
         ra = Random();
   GBS_StartTimerProc(&mytmr, ra, Calling_Off);
       }
            else
              GBS_StartTimerProc(&mytmr, 10*lenght4, Calling_Off);
}

void Calling_Off()
{
  if (IsCalling())
  {
    CameraLightOnOff();
          if(Randomed)
       {
         ra = Random();
    GBS_StartTimerProc(&mytmr, ra, Calling_On);
    }
    else
      GBS_StartTimerProc(&mytmr, 10*lenght2, Calling_On);
  }
  else
    GBS_StartTimerProc(&mytmr, 262, Check);
}

void Calling_Off2()
{
  CameraLightOnOff();
        if(Randomed)
       {
         ra = Random();
  GBS_StartTimerProc(&mytmr, ra, Calling_On2);
  }
           else
             GBS_StartTimerProc(&mytmr, 10*lenght3, Calling_On2);
             
}

void Timer_Off(void);
void Timer_Off2(void);

void Timer_On()
{
  if ((Blinks_Mode)&&(GetMissedEventCount(1)>0))
  {
    
      CameraLightOnOff();
                        if(Randomed)
       {
         ra = Random();
  GBS_StartTimerProc(&mytmr, ra, Timer_Off2);
       }
  else
    GBS_StartTimerProc(&mytmr, 10*lenght_call, Timer_Off2);
  }
  else 
  {
    if ((Blinks_Mode)&&(GetMissedEventCount(2)>0))
    {
        CameraLightOnOff();
                          if(Randomed)
       {
         ra = Random();
    GBS_StartTimerProc(&mytmr, ra, Timer_Off2);
       }
       else
         GBS_StartTimerProc(&mytmr, 10*lenght_sms, Timer_Off2);
    }
     else
       {
           CameraLightOnOff();
                             if(Randomed)
       {
         ra = Random();
         GBS_StartTimerProc(&mytmr, ra, Timer_Off2);
       }
         else
           GBS_StartTimerProc(&mytmr, 10*lenght, Timer_Off2);
  }
}
}

void Timer_On2()
{
  if ((Blinks_Mode)&&(GetMissedEventCount(1)>0))
  {
    
      CameraLightOnOff();
                        if(Randomed)
       {
         ra = Random();
  GBS_StartTimerProc(&mytmr, ra, Timer_Off);
       }
  else
    GBS_StartTimerProc(&mytmr, 10*lenght_call, Timer_Off);
  }
  else 
  {
    if ((Blinks_Mode)&&(GetMissedEventCount(2)>0))
    {
        CameraLightOnOff();
                          if(Randomed)
       {
         ra = Random();
    GBS_StartTimerProc(&mytmr, ra, Timer_Off);
       }
       else
         GBS_StartTimerProc(&mytmr, 10*lenght_sms, Timer_Off);
    }
     else
       {
           CameraLightOnOff();
                             if(Randomed)
       {
         ra = Random();
         GBS_StartTimerProc(&mytmr, ra, Timer_Off);
       }
         else
           GBS_StartTimerProc(&mytmr, 10*lenght, Timer_Off);
  }
}
}

void Timer_Off()
{
  if (GetMissedEventCount(0)>0)
  {
    if(Missed_Mode)
    {
      if ((Blinks_Mode)&&(GetMissedEventCount(1)>0))
      {
        CameraLightOnOff();
                  if(Randomed)
       {
         ra = Random();
        GBS_StartTimerProc(&mytmr, ra, Timer_On);
      }
      else
        GBS_StartTimerProc(&mytmr, 10*lenght_call, Timer_On);
      }
      else 
      {
        if ((Blinks_Mode)&&(GetMissedEventCount(2)>0))
        {
          CameraLightOnOff();
                    if(Randomed)
       {
         ra = Random();
          GBS_StartTimerProc(&mytmr, ra, Timer_On);
        }
        else
          GBS_StartTimerProc(&mytmr, 10*lenght_sms, Timer_On);
        }
        else
          if (GetMissedEventCount(sudinji)>0)
          {
            CameraLightOnOff();
                      if(Randomed)
       {
         ra = Random();
            GBS_StartTimerProc(&mytmr, ra, Timer_On);
          }
          else
            GBS_StartTimerProc(&mytmr, 10*lenght, Timer_On);
          }
          else
            GBS_StartTimerProc(&mytmr, 262, Check);
      }
    }
    else
      if(Missed_Mode)
      {
        if (GetMissedEventCount(sudinji)>0)
        {
          CameraLightOnOff();
                    if(Randomed)
       {
         ra = Random();
          GBS_StartTimerProc(&mytmr, ra, Timer_On);
        }
        else
          GBS_StartTimerProc(&mytmr, 10*lenght, Timer_On);
        }
        else
          GBS_StartTimerProc(&mytmr, 262, Check);
      }
      else
          GBS_StartTimerProc(&mytmr, 262, Check);
  }
  else
    if (IsCalling())
    {
      if((Calling_Mode)&&(Talking_Mode))
        Calling_Off();
      else
      {
        if(Calling_Mode)
          Calling_Off_Calling();
        else
        {
          if(Talking_Mode)
            Calling_Off_Talking();
          else
            GBS_StartTimerProc(&mytmr, 262, Check);
        }
      }
    }
    else
      GBS_StartTimerProc(&mytmr, 262, Check);
}
void Timer_Off2()
{
  if ((Blinks_Mode)&&(GetMissedEventCount(1)>0))
  {
      CameraLightOnOff();
                if(Randomed)
       {
         ra = Random();
  GBS_StartTimerProc(&mytmr, ra, Timer_On2);
  }
  else
    GBS_StartTimerProc(&mytmr, 10*lenght_call, Timer_On2);
  }
  else 
  {
    if ((Blinks_Mode)&&(GetMissedEventCount(2)>0))
    {
        CameraLightOnOff();
                  if(Randomed)
       {
         ra = Random();
    GBS_StartTimerProc(&mytmr, ra, Timer_On2);
    }
    else
      GBS_StartTimerProc(&mytmr, 10*lenght_sms, Timer_On2);
    }
     else
       {
           CameraLightOnOff();
                     if(Randomed)
       {
         ra = Random();
         GBS_StartTimerProc(&mytmr, ra, Timer_On2);
       }
       else
         GBS_StartTimerProc(&mytmr, 10*lenght, Timer_On2);
       }
  }
}

void Check()
{
  if ((GetMissedEventCount(0)>0)||(IsCalling()))
  {
    Timer_Off();
  }
  else
  {
    GBS_StartTimerProc(&mytmr, 262, Check);
  }
}
*/ 
/*
int sndVolume = 6;

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
extern const int zajebalo;
int BlinkCount;
int INFO;

void Check(void);

void Start_Blink()
{
  if(BlinkCount!=0)
  {
    BlinkCount--;
    CameraLightOnOff();
    GBS_StartTimerProc(&mytmr, 40, Start_Blink);
  }
  else
    GBS_StartTimerProc(&mytmr, 262, Check);
}
/*
int timings;
int timings2;
TDate date;
TTime time;
*/
extern const char sound[64];

void Check()
{
  /*
  GetDateTime(&date, &time);
  timings=time.min;
  if(GetMissedEventCount(2)>0)
  {
    if(timings!=timings2)
    {
      timings2=timings;
      Play(sound);
    }
  }
  */
  if(GetMissedEventCount(2)!=INFO)
  {
    if(GetMissedEventCount(2)<INFO)
    {
      INFO=GetMissedEventCount(2);
      GBS_StartTimerProc(&mytmr, 262, Check);
    }
    else
    if(GetMissedEventCount(2)>INFO)
    {
      INFO=GetMissedEventCount(2);
      BlinkCount=6;
      Start_Blink();
    }
  }
  else
  GBS_StartTimerProc(&mytmr, 262, Check);
}

int main()
{
  InitConfig();
  if(zajebalo)
  {
    ShowMSG(1,(int)"SMS Informer - (c)Evilfox");
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

