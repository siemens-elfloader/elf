#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "AKKUSRC.h"

#include "lograph.h"
#include "crashprotect.h"

#define MAX(a,b) (a)>(b)?(a):(b)
#define abs(a) (a>0?(a):-(a))

int prev_cap=-1;

extern int INTERVAL;

GBSTMR timer;
TLograph* lograph=0;
char scrstring[16]="N/A";
WSHDR *ws=0;

extern int ENABLED;

void RefreshValue()
{
    if(ENABLED)
    {
     int cap=AkkuCapacity();
     if(cap!=prev_cap)
        {
        prev_cap=cap;
        lograph->PushCurrentPoint();
        };
     float est=lograph->EstimateElapsedTime();
     if(est<=0) strcpy(scrstring,lograph->LastNAmsg);
     else if(est>24.0) sprintf(scrstring,"%1.1fd",est/24.0);
     else sprintf(scrstring,"%.0fh",est);        
  };
};

void Watch()
{
  RefreshValue();
  GBS_StartTimerProc(&timer,INTERVAL*216,Watch);
};


const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

extern "C" {void kill_data(void *p, void (*func_p)(void *));};

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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"AkkuD2 config updated!");
      InitConfig();
      RefreshValue();
    }
  }
 
  int fShow; 
  extern int cfgShowIn;
  switch (cfgShowIn)
  {
  case 0:
    fShow = !IsUnlocked();
    break;
  case 1:
    fShow = IsUnlocked();
    break;
  default:
    fShow = 1;
    break;
  }
  
  if(!fShow) return 1;
  
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])  
  CSM_RAM *  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm)))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
#ifdef ELKA
        {
          void *canvasdata = BuildCanvas();
#else
        void *idata = GetDataOfItemByID(igui, 2);
        if (idata)
        {
          void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif      
          extern char ICON[128];
          
          extern char TEXTCOLOR[4];
          extern char FRINGCOLOR[4];
          
          wsprintf(ws,"%t",scrstring);
          
          int ww=GetImgWidth((int)ICON);
          int hh=GetImgHeight((int)ICON);
          int h=GetFontYSIZE(FONT_SMALL);
          int w=ww+Get_WS_width(ws,FONT_SMALL);
             
          int qh=MAX(h,hh);
          int dy=abs(h-hh)/2;
          
          extern unsigned int XCOORD;
          extern unsigned int YCOORD;          
                    
          DrawCanvas(canvasdata, XCOORD,YCOORD,XCOORD+w,YCOORD+qh, 1);
          DrawImg(XCOORD,YCOORD,(int)ICON);
          DrawString(ws, XCOORD+ww,YCOORD+dy, XCOORD+w+1,YCOORD+qh+1+dy, FONT_SMALL,
                       FRINGCOLOR[3] ? TEXT_OUTLINE : 0+TEXT_NOFORMAT,
                       TEXTCOLOR,
                       FRINGCOLOR[3] ? FRINGCOLOR : 0);          
        }
      }
    }
  }
  

static int q=32;
if(q>0) q--; else CrashProtect::CorrectlyTerminate();  

return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  Watch();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  if(IsTimerProc(&timer))GBS_StopTimer(&timer);
  if(lograph)delete lograph;
  FreeWS(ws);  
  CrashProtect::CorrectlyTerminate();
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"AkkuD2");
}

int main(char* self)
{
  InitConfig();
  
  CrashProtect::ZBinDrive=self[0];
  CrashProtect::ElfName="AkkuD2";
  if(!CrashProtect::CanStart()) {SUBPROC((void *)Killer);return 0;};
  CrashProtect::Start();
  
  
  lograph=new TLograph();
  ws=AllocWS(32);
  
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=(CSM_RAM*)(CSM_root()->csm_q->csm.first);
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return 0;
}


