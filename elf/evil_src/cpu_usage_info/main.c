#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

const int minus11=-11;

extern const unsigned int date_X;
extern const unsigned int date_Y;
extern const unsigned int date_X2;
extern const unsigned int date_Y2;
extern const unsigned int date_X3;
extern const unsigned int date_Y3;
extern const int msg;
extern const int fullfont;
extern const char fontpath[64];
char lielims[128];
char fontpath2[64];
int font=1;
int align=0;
extern const unsigned int space;
void *canvasdata;

int test;
int test2;
int test3;
char heh[20];
char hah[20];
char huh[20];
int refresh;
GBSTMR mytmr;

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

void Checker()
{
  test = GetCPUClock();
  sprintf(heh, "Cpu clock: %dmhz", test);
  test2 = GetCPULoad();
//  sprintf(huh, "Cpu Usage: %d", test2);
  if(test==208)
  {
    test3=(208/100)*test2;
    sprintf(hah, "Cpu mhz: %dmhz", test3);
  }
  if(test==104)
  {
    test3=(104/100)*test2;
    sprintf(hah, "Cpu mhz: %dmhz", test3);
  }
  if(test==52)
  {
    test3=(52/100)*test2;
    sprintf(hah, "Cpu mhz: %dmhz", test3);
  }
  refresh=1;
  GBS_StartTimerProc(&mytmr, 216, Checker);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"CPU Info config updated!");
      FontPathFree();
      InitConfig();
      strcpy(fontpath2, fontpath);
      FontPathInit(font,fontpath2, fullfont ,1);
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver()) //???? IdleGui ?? ????? ?????
    {
      GUI *igui=GetTopGUI();
      if ((igui)&&(refresh==1)) //? ?? ??????????
      {
	canvasdata=BuildCanvas();
        ClearScreen();
//      PrintField(date_X,date_Y, huh, align, font, space);
      PrintField(date_X2,date_Y2, hah, align, font, space);
      PrintField(date_X3,date_Y3, heh, align, font, space);
      refresh=0;
      }
      
    }
    else
      refresh=1;
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  GBS_StopTimer(&mytmr);
  FontPathFree();
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"CpuInfo - (c)Evilfox");
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
//  sprintf(buf, "0");
  strcpy(fontpath2, fontpath);
  FontPathInit(font,fontpath2, fullfont ,1);
  if(msg)
    ShowMSG(1,(int)"CpuInfo (c)Evilfox");
  Checker();
  return 0;
}
