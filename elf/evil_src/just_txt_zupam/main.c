#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

#pragma swi_number=0x0C5
__swi __arm int IsIdleUiOnTop();

const int minus11=-11;
extern const unsigned int date_X0;
extern const unsigned int date_Y0;
extern const unsigned int date_X1;
extern const unsigned int date_Y1;
extern const unsigned int date_X2;
extern const unsigned int date_Y2;
extern const unsigned int date_X3;
extern const unsigned int date_Y3;
extern const unsigned int date_X4;
extern const unsigned int date_Y4;
extern const unsigned int date_X5;
extern const unsigned int date_Y5;
extern const unsigned int date_X6;
extern const unsigned int date_Y6;
extern const unsigned int date_X7;
extern const unsigned int date_Y7;
extern const unsigned int date_X8;
extern const unsigned int date_Y8;
extern const unsigned int date_X9;
extern const unsigned int date_Y9;
extern const int TEKSTS0;
extern const int TEKSTS1;
extern const int TEKSTS2;
extern const int TEKSTS3;
extern const int TEKSTS4;
extern const int TEKSTS5;
extern const int TEKSTS6;
extern const int TEKSTS7;
extern const int TEKSTS8;
extern const int TEKSTS9;
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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"text zupam config updated!");
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
        if((strlen(fontpath)>5)&&(refresh==1))
        {
	canvasdata=BuildCanvas();   
        if(TEKSTS0) PrintField(date_X0,date_Y0,(char *)txt0, align, font, space);
        if(TEKSTS1) PrintField(date_X1,date_Y1,(char *)txt1, align, font, space);
        if(TEKSTS2) PrintField(date_X2,date_Y2,(char *)txt2, align, font, space);
        if(TEKSTS3) PrintField(date_X3,date_Y3,(char *)txt3, align, font, space);
        if(TEKSTS4) PrintField(date_X4,date_Y4,(char *)txt4, align, font, space);
        if(TEKSTS5) PrintField(date_X5,date_Y5,(char *)txt5, align, font, space);
        if(TEKSTS6) PrintField(date_X6,date_Y6,(char *)txt6, align, font, space);
        if(TEKSTS7) PrintField(date_X7,date_Y7,(char *)txt7, align, font, space);
        if(TEKSTS8) PrintField(date_X8,date_Y8,(char *)txt8, align, font, space);
        if(TEKSTS9) PrintField(date_X9,date_Y9,(char *)txt9, align, font, space);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"text zupam (c)Evilfox");
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
    ShowMSG(1,(int)"text zupam (c)Evilfox");
  return 0;
}
