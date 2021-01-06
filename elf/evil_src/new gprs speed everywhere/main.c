#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

#pragma swi_number=0x0C5
__swi __arm int IsIdleUiOnTop();

const int minus11=-11;
extern const unsigned int date_X;
extern const unsigned int date_Y;
extern const unsigned int IDLEICON_X;
extern const unsigned int IDLEICON_Y;
extern const int fullfont;
extern const int IKONA;
extern const int TEKSTS;
int janko;
char heh[32];
char heh2[32];
char heh3[32];
char buf[64];
char ICON[128];
extern const int msg;
extern const char str1[64];
extern const char str2[64];
extern const char str3[64];
extern const char str4[64];
extern const char str5[64];
extern const char cone[64];
extern const char fontpath[64];
int font=1;
extern const int align;
extern const unsigned int space;
void *canvasdata;
int refresh;
int start_traffic;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

extern void kill_data(void *p, void (*func_p)(void *));

#pragma inline=forced

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

GBSTMR mytmr;
GBSTMR startt;
int hmm;
int ggg;
int show_not_main;
extern const int evrey;
int session;
int first_run;

GBSTMR mytmr2;
const char color[4]={255,255,255,100};
int font2 = 9;

void check()
{
  if((!IsIdleUiOnTop())&&(show_not_main>0)) 
  {
    WSHDR *ws=AllocWS(256);
    wsprintf(ws,heh2);
    show_not_main--;
    DrawRectangle(0,319-GetFontYSIZE(font2),240,320,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
    DrawString(ws,1,319-GetFontYSIZE(font2),1+Get_WS_width(ws,font2)+2,320,font2,0,( char*) color,GetPaletteAdrByColorIndex(23));
    wsprintf(ws,heh3);
    DrawString(ws,240-Get_WS_width(ws,font2)-2,319-GetFontYSIZE(font2),240,320,font2,0,( char*) color,GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    GBS_StartTimerProc(&mytmr2, 5, check);
  }
  else
  {
    show_not_main=0;
  }
}

void Counter()
{
  if(IsGPRSConnected())
  {
    RefreshGPRSTraffic();
    int *traf = GetGPRSTrafficPointer();
    session=(*traf-start_traffic)/1024;
    hmm=*traf-ggg;
    sprintf(heh,"%s%dB/s", str5, hmm);
    sprintf(heh2,"Sp:%dB/s", hmm);
    ggg=*traf;
    if(evrey)
    {
    if((hmm>0)&&(janko==1))
    { 
      sprintf(heh3,"Se:%dKb", session);
      int csm_oncreate_addr = ((int*)(((CSM_RAM*)(CSM_root()->csm_q->csm.last))->constr))[1] - 1;
      char java_oncreate_pattern[8] = {0xB0, 0xB5, 0x04, 0x1C, 0x00, 0x25, 0x05, 0x61};
      if (memcmp((void*)csm_oncreate_addr, java_oncreate_pattern, 8))
      {
        show_not_main=70;
        check();
      }
    }
    }
  }
  else
    strcpy(heh, cone);
  if(hmm>=500)
      {
      sprintf(ICON, "%s",str1);
      }
      else
      {
        if(hmm>=1)
        {
          sprintf(ICON, "%s",str2);
        }
        else
        {
        if(IsGPRSConnected())
        {
          sprintf(ICON, "%s",str3);
        }
        else
          sprintf(ICON, "%s",str4);
        }
      }
  janko=1;
  refresh=1;
  GBS_StartTimerProc(&mytmr, 216, Counter);
}

extern const int FAST_REF;

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"GprsSpeed2 config updated!");
      FontPathFree();
      InitConfig();
      FontPathInit(font,(char *)fontpath, fullfont, 1);
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver()) //Если IdleGui на самом верху
    {
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
        if(strlen(fontpath)>5)
        {
                if((janko==1)&&(refresh==1))
                {
	canvasdata=BuildCanvas();   
      if(IKONA)
      {
	DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)ICON)-1,IDLEICON_Y+GetImgHeight((int)ICON)-1,1);
	DrawImg(IDLEICON_X,IDLEICON_Y,(int)ICON);
      }
      if(TEKSTS) PrintField(date_X,date_Y, heh, align, font, space);
      if(!FAST_REF) refresh=0;
      }
      }
      }
    }
    else
      refresh=1;
  return (1);  
}



static void maincsm_oncreate(CSM_RAM *data)
{
//  LockSched();
  RefreshGPRSTraffic();
  int *traf = GetGPRSTrafficPointer();
  start_traffic=*traf;
//  UnlockSched();
}

static void Killer(void)
{
  FontPathFree();
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&mytmr2);
  GBS_DelTimer(&startt);
  extern void *ELF_BEGIN;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"GprsSpeed2 - (c)Evilfox");
}

int main()
{
  InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname(); 
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  FontPathInit(font,(char *)fontpath, fullfont, 1);
  if(msg)
    ShowMSG(1,(int)"GprsSpeed2 (c)Evilfox");
  Counter();
  return 0;
}
