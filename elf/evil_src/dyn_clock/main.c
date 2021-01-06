#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

#pragma swi_number=0x0C5
__swi __arm int IsIdleUiOnTop();

const int minus11=-11;
extern const unsigned int date_X0;
extern const unsigned int date_Y0;
extern const char txt0[64];
extern const char txt1[64];
extern const char txt2[64];
extern const char txt3[64];
extern const char txt4[64];
extern const char txt5[64];
extern const char txt6[64];
extern const char txt7[64];
extern const char txt8[64];
extern const char txt9[64];
/*
extern const unsigned int IDLEICON_X;
extern const unsigned int IDLEICON_Y;

extern const int IKONA;
extern const int TEKSTS;
int janko;
char heh[32];
char buf[64];
char ICON[128];

*/
extern const int msg;
extern const char fontpath[64];
int font=1;
extern const int fullfont;
extern const int align;
extern const unsigned int space;
void *canvasdata;
int refresh;

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

char the_time[16];
int minutes;
int font_c;
GBSTMR taimeris;
char fontings[64];
extern const unsigned int max_font;
int counteritis;


void timer()
{
  TTime tt;
  GetDateTime(NULL,&tt);
  sprintf(the_time, "%02d:%02d", tt.hour, tt.min);
  minutes=tt.min;
  counteritis=counteritis+2;
  if(counteritis==20)
  {
    if(font_c==max_font) font_c=0;
    font_c++;
    counteritis=0;
    goto L1;
  }
  refresh=1;
  GBS_StartTimerProc(&taimeris, 432, timer);
  return;
L1:
  if(font_c==1) strcpy(fontings, txt0);
  if(font_c==2) strcpy(fontings, txt1);
  if(font_c==3) strcpy(fontings, txt2);
  if(font_c==4) strcpy(fontings, txt3);
  if(font_c==5) strcpy(fontings, txt4);
  if(font_c==6) strcpy(fontings, txt5);
  if(font_c==7) strcpy(fontings, txt6);
  if(font_c==8) strcpy(fontings, txt7);
  if(font_c==9) strcpy(fontings, txt8);
  if(font_c==10) strcpy(fontings, txt9);
  FontPathFree();
  FontPathInit(font, fontings, fullfont, 1);
  refresh=1;
  GBS_StartTimerProc(&taimeris, 432, timer);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"dyn info config updated!");
      FontPathFree();
      InitConfig();
      FontPathInit(font, fontings, fullfont, 1);
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver()) //Если IdleGui на самом верху
    {
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
        if((strlen(fontings)>5)&&(refresh==1))
        {
	canvasdata=BuildCanvas(); 
        ClearScreen();
        PrintField(date_X0,date_Y0, the_time, align, font, space);
        refresh=0;
        }
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
  FontPathFree();
  GBS_DelTimer(&taimeris);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Dyn Clock (c)Evilfox");
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
  if(msg)
    ShowMSG(1,(int)"dyn clock (c)Evilfox");
  strcpy(fontings, txt0);
  FontPathInit(font, fontings, fullfont, 1);
  timer();
  return 0;
}
