/*******************************************************************************
FastRun 2 (c) The_ZeN, (r) Shadows, vanek, feanor
*******************************************************************************/

#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "fastrun_ipc.h"
#include "fastrun.c"
#include "language.h"
#include "bookmarks.c"
#include "menus.c"
#include "keyhooks.c"
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



void RedrawScreen() // Рисуем на идле
{
  CSM_RAM *data=FindCSMbyID(CSM_root()->idle_id);
  if(IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if (igui) //И он существует
    {
      void *canvasdata;
#ifdef ELKA
      {
#else
      void *idata;
      idata=GetDataOfItemByID(igui,2);
      if (idata)
      {
#endif
#ifdef ELKA
	if(IDLE_ENA)canvasdata=BuildCanvas();
#else
        if(IDLE_ENA)canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif
        if(IDLE_ENA)
        {
          if ( NumOfItems_idle > 0)
          {
            DrawIdleMenu();
          }
          else
          {
            WSHDR * ws = AllocWS( 256 );
            DrawCanvas( canvasdata , x1,  y1, x1+LEN_ID, y1 + 4 + (GetFontYSIZE(TEXT_FONT))*2, 1 );
            DrawRoundedFrame( x1,  y1, x1+LEN_ID , y1 + 4 + (GetFontYSIZE(TEXT_FONT))*2, 0, 0, 0, cfgPanBGCol_ID_dis, cfgPanBGCol_ID_dis );
            wsprintf(ws, percent_t, LG_SETBOOKS_IDLE_1);
            DrawString( ws, x1,  y1 + 2, x1+LEN_ID,  y1 + 2 + GetFontYSIZE(TEXT_FONT), TEXT_FONT, 2, cfgFontCol_ID, GetPaletteAdrByColorIndex( 23 ) );
            wsprintf(ws, percent_t, LG_SETBOOKS_IDLE_2);
            DrawString( ws, x1,  y1 + 2 + GetFontYSIZE(TEXT_FONT), x1+LEN_ID,  y1 + 4 + (GetFontYSIZE(TEXT_FONT))*2, TEXT_FONT, 2, cfgFontCol_ID, GetPaletteAdrByColorIndex( 23 ) );
            FreeWS(ws);
          }
        }
        if(ConfigUpdated)
        {
          ShowMSG(1,(int)LG_INITCFG);
          ConfigUpdated=0;
        }
      }
    }
  }
}

void TimerProc()// Перерисовка по таймеру
{
    RedrawScreen();
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ConfigUpdated=1;
      InitConfig();
      if (!FASTRUN_ENA)
      {
        if (FR_KEYHOOK_ENA)
        {
          RemoveKeybMsgHook((void *)FastRun_KeyHook);
          FR_KEYHOOK_ENA=0;
        }
      }
      else
      {
        if (!FR_KEYHOOK_ENA)
        {
          AddKeybMsgHook((void *)FastRun_KeyHook);
          FR_KEYHOOK_ENA=1;
        }
      }
      if (!IDLE_ENA)
      {
        if(IDLE_KEYHOOK_ENA)
        {
          RemoveKeybMsgHook((void *)IDLE_KeyHook);
          IDLE_KEYHOOK_ENA=0;
        }
      }
      else
      {
        if (!IDLE_KEYHOOK_ENA)
        {
          AddKeybMsgHook((void *)IDLE_KeyHook);
          IDLE_KEYHOOK_ENA=1;
        }
      }
      MenuInit();
    }
  }
  if (msg->msg==MSG_IPC)// IPC
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)// Если приняли собственное сообщение
      {
        switch (msg->submess)
        {
        case IPC_UPDATE_STAT:
          GBS_StartTimerProc(&idle_timer, 10*TMR_SECOND/10, TimerProc);
        }
      }
    }
  }
  return(1);
}
  


static void maincsm_oncreate(CSM_RAM *data)
{
 if (FASTRUN_ENA) 
 {
   AddKeybMsgHook((void *)FastRun_KeyHook);
   FR_KEYHOOK_ENA=1;
 }
 else FR_KEYHOOK_ENA=0;
 if (IDLE_ENA) 
 {
   AddKeybMsgHook((void *)IDLE_KeyHook);
   IDLE_KEYHOOK_ENA=1;
 }
 else IDLE_KEYHOOK_ENA=0;
 MenuInit();
 InitFastRunMenu();
 GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  if (FR_KEYHOOK_ENA) RemoveKeybMsgHook((void *)FastRun_KeyHook);
  if (IDLE_KEYHOOK_ENA) RemoveKeybMsgHook((void *)IDLE_KeyHook);
  GBS_DelTimer(&idle_timer);
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
  sizeof(CSM_RAM),
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


static void UpdateCSMname(void)// Имя эльфа в таске
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"FastRun2");
}
// ----------------------------------------------------------------------------


int main(const char *exename, const char *filename)
{
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  InitConfig();
  UpdateCSMname();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return (0);
}
