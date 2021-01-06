#include "..\inc\swilib.h"
#include "..\inc\playsound.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "TalkPhone.h"

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;

unsigned int vibra_count1;
int MAINCSM_ID;

TTime CurTime;
TDate date;

//=============================Проигрывание звука===============================
int PLAY_ID=0;
unsigned int NEXT_PLAY_FUNK=0;
/*
0 - ничего
//1 - SayTime
1 - SayHourDig
2 - SayHourVoice
3 - SayMinAllDig
4 - SayMinDig
5 - SayMinVoice
*/

void Play(const char *fpath, const char *fname)
{
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);

      wsprintf(sndPath, fpath);
      wsprintf(sndFName, fname);
  

      PLAYFILE_OPT _sfo1;
      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=volume;
    
      #ifdef NEWSGOLD
        _sfo1.unk6=1;
        _sfo1.unk7=1;
        _sfo1.unk9=2;
        PLAY_ID=PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
      #else
          #ifdef X75
            _sfo1.unk4=0x80000000;
            _sfo1.unk5=1;
            PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
          #else
            _sfo1.unk5=1;
            PLAY_ID=PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
          #endif
      #endif 

      FreeWS(sndPath);
      FreeWS(sndFName);
}

//++++++++++++++++++++++++++++++Проговаривание времени+++++++++++++++++++++++++++++++++

//-----------------------------------------------------------
GBSTMR tmr_vibra;

void start_vibra(void)
{
  void stop_vibra(void);
  if ((Is_Vibra_Enabled)&&(!IsCalling()))
  {
    SetVibration(vibra_power);
    GBS_StartTimerProc(&tmr_vibra,216>>1,stop_vibra);
  }  
}

void stop_vibra(void)
{
  SetVibration(0);
  if (--vibra_count1)
  {
    GBS_StartTimerProc(&tmr_vibra,216>>1,start_vibra);
  }
}
//----------------------------------------------------------


void SayMinVoice()
{
    if (CurTime.min>=10 && CurTime.min<=19) Play(folder_path, "min3.wav");
      else
        {
          switch (CurTime.min%10)
            {
              case 1:
                Play(folder_path, "min2.wav");
              break;
              case 2: case 3: case 4:
                Play(folder_path, "min1.wav");
              break;
              case 0: case 5: case 6: case 7: case 8: case 9: 
                Play(folder_path, "min3.wav");
              break;  
            }
        }
    NEXT_PLAY_FUNK=0;
}

//-------------------------------- Минуты -------------------------------------
void SayMinDig()
{
    if (CurTime.min!=0)
      {
        if (CurTime.min%10==1) 
          {
            Play(folder_path, "1_2.wav");
            NEXT_PLAY_FUNK=5;
          }
          else
        if (CurTime.min%10==2) 
          {
            Play(folder_path, "2_1.wav");          
            NEXT_PLAY_FUNK=5;
          }
          else
            {
              char s[5];
              sprintf(s, "%d.wav", CurTime.min%10);            
              Play(folder_path, s);  
              NEXT_PLAY_FUNK=5;
            }
      }
    else
      {
        Play(folder_path, "xxx.wav");
        NEXT_PLAY_FUNK=0;
      }
}

//////////////////////////////////////////////////////////////////////////////
void SayMinAllDig()
{
      switch (CurTime.min)
        {
          case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
            SayMinDig();
          break;
          
          case 10: case 11: case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
          case 20: case 30: case 40: case 50:   
            { 
              char s[6];
              sprintf(s, "%d.wav", CurTime.min);            
              Play(folder_path, s);
              NEXT_PLAY_FUNK=5;
            }
          break;  
          
          case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29:
            Play(folder_path, "20.wav");
            NEXT_PLAY_FUNK=4;
          break;

          case 31: case 32: case 33: case 34: case 35: case 36: case 37: case 38: case 39:
            Play(folder_path, "30.wav");
            NEXT_PLAY_FUNK=4;
          break;

          case 41: case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49: 
            Play(folder_path, "40.wav");
            NEXT_PLAY_FUNK=4;
          break;

          case 51: case 52: case 53: case 54: case 55: case 56: case 57: case 58: case 59: 
            Play(folder_path, "50.wav");
            NEXT_PLAY_FUNK=4;
          break;
        }      
}
//------------------------------ /*Минуты*/ -----------------------------------

void SayHourVoice()
{
        switch (CurTime.hour)
          {
            case 1: case 21:
              Play(folder_path, "hour2.wav");
              NEXT_PLAY_FUNK=3;
            break;
          
            case 2: case 3: case 4: case 22: case 23:
              Play(folder_path, "hour3.wav");
              NEXT_PLAY_FUNK=3;
            break;
          
            case 0: case 5: case 6: case 7: case 8: case 9: case 10: 
            case 11: case 12: case 13: case 14: case 15: case 16: 
            case 17: case 18: case 19: case 20:
              Play(folder_path, "hour1.wav");
              NEXT_PLAY_FUNK=3;
            break;  
          }    
}

void SayHourDig()
{
      if (CurTime.hour==1) 
        {
          Play(folder_path, "1_1.wav");
          NEXT_PLAY_FUNK=2;
        }
        else
      if (CurTime.hour==2) 
        {
          Play(folder_path, "2_2.wav");          
          NEXT_PLAY_FUNK=2;
        }
        else
          {
            char s[6];
            sprintf(s, "%d.wav", CurTime.hour);            
            Play(folder_path, s);
            NEXT_PLAY_FUNK=2;
          }
}


void SayTime(int param)
{
  //param==0 Куранты
  //param==1 Всё
  start_vibra();
  vibra_count1=vibra_count;
  
  if (param) 
      {
        Play(folder_path, "x.wav");
        NEXT_PLAY_FUNK=1;
      }
      else
        {
          char s[128];
          const char *p=strrchr(kurant_path,'\\')+1;
          strncpy(s,kurant_path,p-kurant_path);
          s[p-kurant_path]='\0';
          
          Play(s, p);
          NEXT_PLAY_FUNK=0;
        }
}

//++++++++++++++++++++++++++++++/*Проговаривание времени*/+++++++++++++++++++++++++++++++++

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if (msg->msg==MSG_PLAYFILE_REPORT)
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==PLAY_ID)
    {
      if (pmsg->cmd==M_SAE_PLAYBACK_ERROR || pmsg->cmd==M_SAE_PLAYBACK_DONE)
      {
            switch (NEXT_PLAY_FUNK)
              {
                case 0:
                  PLAY_ID=-1;
                  CloseCSM(MAINCSM_ID);
                break;
  
                case 1:
                  SayHourDig();
                break;

                case 2:
                  SayHourVoice();
                break;

                case 3:
                  SayMinAllDig();
                break;

                case 4:
                  SayMinDig();
                break;
                
                case 5:
                  SayMinVoice();
                break;
        }
      }
    }
        else
          PLAY_ID=-1;    
  }
  
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  GetDateTime(&date,&CurTime);
  SUBPROC((void*)SayTime, PLAY_PARAM);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&tmr_vibra);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TalkPhoneND");
}

int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  UpdateCSMname();

  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  
  return 0;
}
