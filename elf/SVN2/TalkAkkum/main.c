#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "..\inc\playsound.h"
#include "conf_loader.h"
#include "TalkAkkum.h"

#define TMR_SECOND 216

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int IDLECSM_ID=-1;

GBSTMR update_tmr;

// Глобальные переменные
unsigned int found_full_empty[3]={0,0,0}; //0-found, 1-full, 3-empty
unsigned int levels_up[9]   ={0,0,0,0,0,0,0,0};//0-10,...,8-90
unsigned int levels_down[10]={0,0,0,0,0,0,0,0,0};//0-5,...,9-90
unsigned int flag=0;
unsigned int vibra_count1;

//=============================Проигрывание звука===============================
int PLAY_ID;
unsigned int NEXT_PLAY_FUNK=0, ENA_SAY_LEVELS=1;
/*
0 - ничего
1 - SayLevel
2 - SayPercent
*/

int IsMediaActive(void)
{
  char s[40];
  sprintf(s,RamMediaIsPlaying());
#ifdef NEWSGOLD
  if (s[0]==1) return 1;
#else
  if (s[0]==2) return 1;// для SGOLD s[0]!=2    
#endif 
  return 0;
}

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

//==============================================================================

GBSTMR tmr_vibra;

void start_vibra(void)
{
  void stop_vibra(void);
  
  SetVibration(vibra_power);
  GBS_StartTimerProc(&tmr_vibra, 50, stop_vibra);
}

void stop_vibra(void)
{
  SetVibration(0);
  if (--vibra_count1)
  {
    GBS_StartTimerProc(&tmr_vibra, 50, start_vibra);
  }
}

//==============================================================================

//Уровни
void SayPercent(void)
{
  Play(folder_path, "percent.wav");
  NEXT_PLAY_FUNK=0;
}

void SayLevel(void)
{
  char level[6];
  sprintf(level, "%d.wav", *RamCap());
  Play(folder_path, level);
  NEXT_PLAY_FUNK=2;
}

void SayUp(void)
{
  if (!IsMediaActive()) Play(folder_path, "up.wav");
  NEXT_PLAY_FUNK=1;
}

void SayDown(void)
{
  if (!IsMediaActive()) Play(folder_path, "down.wav");
  NEXT_PLAY_FUNK=1;
}

GBSTMR temp_tmr;
void SayTemp(void)
{
  if (!IsCalling())
    {
      if (!IsMediaActive()) Play(folder_path, "temp.wav");
  
      vibra_count1=vibra_count;
      start_vibra();
    }  
  
  if (flag==1) GBS_StartTimerProc(&temp_tmr, warn_interr*216, SayTemp);
}
// ----------------------------------------------------------------------------

void Check(void)
{
  TDate CurDate;
  TTime CurTime;
  
  GetDateTime(&CurDate, &CurTime);
   if (((CurTime.hour*60+CurTime.min)<=(TimeTo.hour*60+TimeTo.min))&&
         ((CurTime.hour*60+CurTime.min)>=(TimeFrom.hour*60+TimeFrom.min))&&
           (!IsCalling()))
    {
      unsigned int state, cap_akku;
      
      LockSched();
      state=*RamLS();
      cap_akku=*RamCap();
      UnlockSched();
      
      //state 0-разрядка
      //      1-промежуточное значение
      //      2-зарядка
      //      3-полный  
      
      
      //unsigned int found_full_empty[3] //0-found, 1-full, 2-empty
      
      switch (state)
      {
        case 0:
          if (found_full_empty[0]||found_full_empty[1]) 
            {
              if (!IsMediaActive()) Play(folder_path, "out.wav");
              ENA_SAY_LEVELS=0;
              NEXT_PLAY_FUNK=0;              
          
              found_full_empty[0]=0;
              found_full_empty[1]=0;
          
              unsigned int i;
              for (i=0; i<=8; i++) {levels_up[i]=0;}              
            }
          
          if ((say_levels_down)&&(cap_akku<=begin_from)&&(ENA_SAY_LEVELS))
            {//Говорить промежуточные уовни разрядки
              //unsigned int levels_down[10]={0,0,0,0,0,0,0,0,0};//0-5,...,9-90
              switch (cap_akku)
              {
                case 10:
                  if (!levels_down[1]) {levels_down[1]=1; SayDown();}
                break;
                case 20:
                  if (!levels_down[2]) {levels_down[2]=1; SayDown();}
                break;
                case 30:
                  if (!levels_down[3]) {levels_down[3]=1; SayDown();}
                break;
                case 40:
                  if (!levels_down[4]) {levels_down[4]=1; SayDown();}
                break;
                case 50:
                  if (!levels_down[5]) {levels_down[5]=1; SayDown();}
                break;
                case 60:
                  if (!levels_down[6]) {levels_down[6]=1; SayDown();}
                break;
                case 70:
                  if (!levels_down[7]) {levels_down[7]=1; SayDown();}
                break;
                case 80:
                  if (!levels_down[8]) {levels_down[8]=1; SayDown();}
                break;
                case 90:
                  if (!levels_down[9]) {levels_down[9]=1; SayDown();}
                break;
              }          
            } /*Говорить промежуточные уовни разрядки*/ 
          
          
          if ((!levels_down[0])&&(cap_akku==5))
            {//-5% Говорить в любом случае
              levels_down[0]=1;
              SayDown();
            }
      
          if ((!found_full_empty[2])&&(cap_akku==0))
            {//0% Говорить в любом случае
              found_full_empty[2]=1;
              Play(folder_path, "0.wav");
            }
        break;
        
        case 2:
          if (!found_full_empty[0])
            {// Найден источник

              if (!IsMediaActive()) Play(folder_path, "found.wav");
              ENA_SAY_LEVELS=0;
              NEXT_PLAY_FUNK=0;
              
              found_full_empty[0]=1;
              
              //Обнуление флагов
              found_full_empty[1]=0;
              
              unsigned int i;
              for (i=0; i<=8; i++) {levels_up[i]=0;}
              for (i=0; i<=9; i++) {levels_down[i]=0;}
              
            }// Найден источник
          
          if ((found_full_empty[0])&&(say_levels_up)&&(ENA_SAY_LEVELS))
            {//Говорить промежуточные уровни зарядки
              switch (cap_akku)
              {
                case 10:
                  if (!levels_up[0]) {levels_up[0]=1; SayUp();}
                break;
                case 20:
                  if (!levels_up[1]) {levels_up[1]=1; SayUp();}
                break;
                case 30:
                  if (!levels_up[2]) {levels_up[2]=1; SayUp();}
                break;
                case 40:
                  if (!levels_up[3]) {levels_up[3]=1; SayUp();}
                break;
                case 50:
                  if (!levels_up[4]) {levels_up[4]=1; SayUp();}
                break;
                case 60:
                  if (!levels_up[5]) {levels_up[5]=1; SayUp();}
                break;
                case 70:
                  if (!levels_up[6]) {levels_up[6]=1; SayUp();}
                break;
                case 80:
                  if (!levels_up[7]) {levels_up[7]=1; SayUp();}
                break;
                case 90:
                  if (!levels_up[8]) {levels_up[8]=1; SayUp();}
                break;
              }
            }/*Говорить промежуточные уровни зарядки*/
        break;
        
        case 3:
          {
          if (!found_full_empty[0]) found_full_empty[0]=1;
          if ((!found_full_empty[1])&&(found_full_empty[0]))
            {// Энергия восстановлена
              found_full_empty[1]=1;

              if (!IsMediaActive()) Play(folder_path, "full.wav");
          
              //Обнуление флагов
              found_full_empty[0]=0;
              found_full_empty[2]=0;
              
              unsigned int i;
              for (i=0; i<=9; i++) {levels_down[i]=0;}          
            }// Энергия восстановлена   
          }
        break;  
      }
      
    }//if ((time.hour>=from_h)&&(time.hour<=to_h))

      // Температура
      if (warn_temp)
        {
          if (((GetAkku(1,3)-0xAAA+15)/10)<(warn_temp_value) && (flag==0) )
            {
              flag=1;
              SayTemp();
            }
        }
      
      if  (flag==1)
        {
          if (((GetAkku(1,3)-0xAAA+15)/10)>=(warn_temp_value)) 
            {
              flag=0;
            }
        }
       //   
}

// ----------------------------------------------------------------------------

const char ipc_my_name[]="TalkAkkum";
#define IPC_UPDATE_STAT 1

const IPC_REQ gipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

void TimerProc(void)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
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

#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  CSM_RAM *icsm;
  
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      ShowMSG(1,(int)"TalkAkkum config updated!");
    }
  }

  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
          if (ipc->name_from==ipc_my_name) 
          {
            Check();
            GBS_StartTimerProc(&update_tmr, TMR_SECOND*3, TimerProc);
          }
        }
      }
    }
  }  
  
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
          ENA_SAY_LEVELS=1;
          break;
          
        case 1:
          ENA_SAY_LEVELS=0;
          SayLevel();
          break;
          
        case 2:
          ENA_SAY_LEVELS=0;
          SayPercent();
          break;
        }
      }
    }
  }
  
  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {  
    if ((IsGuiOnTop(idlegui_id))&&(show_icon)) //Если IdleGui на самом верху
      {
        GUI *igui=GetTopGUI();
        if (igui) //И он существует
        {
#ifdef ELKA

	  void *canvasdata = BuildCanvas();
#else
	  void *idata = GetDataOfItemByID(igui, 2);
	  if (idata)
	  {
	    void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
            char pic_path[128];
            strcpy(pic_path, folder_path);
            strcat(pic_path, "TalkAkkum.png");            
            DrawCanvas(canvasdata, cfgX, cfgY, cfgX + GetImgWidth((int)pic_path), cfgY + GetImgHeight((int)pic_path), 1);
	    DrawImg(cfgX, cfgY, (int)pic_path);
#ifdef ELKA
#else
	  }
#endif
        }
      }
  }    
  
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&update_tmr);
  GBS_DelTimer(&tmr_vibra);
  GBS_DelTimer(&temp_tmr); 
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TalkAkkum");
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
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  return 0;
}
