#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "print.h"

#pragma swi_number=0x09E
__swi __arm int GetMissedEventCount(unsigned int Event);

const int minus11=-11;
extern const unsigned int date_X;
extern const unsigned int date_Y;
int date_Y02;
int date_Y03;
int zvani;
int sms;
int citi;
char calls[64];
char message[64];
char other[64];
extern const unsigned int IDLEICON_X;
extern const unsigned int IDLEICON_Y;
extern const int fullfont;
char ICON[128];
extern const char str1[64];
extern const char str2[64];
extern const char str3[64];
extern const char str4[64];
extern const int msg;
extern const char fontpath[64];
char lielims[64];
int font=1;
extern const int align;
extern const unsigned int space;
void *canvasdata;
int refresh;
char PATH[128];

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

extern const unsigned int luki;

void init_pos()
{
  date_Y02=date_Y+GetImgHeight((int)lielims)+luki;
  date_Y03=date_Y02+GetImgHeight((int)lielims)+luki;
}

GBSTMR mytmr;

void counter()
{
  zvani=GetMissedEventCount(1);
  sms=GetMissedEventCount(2);
  citi=GetMissedEventCount(3);
  sprintf(calls, "Calls: %d", zvani);
  sprintf(message, "SMS:   %d", sms);
  sprintf(other, "Other: %d", citi);
  refresh=1;
  GBS_StartTimerProc(&mytmr, 216, counter);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"MissedEvents config updated!");
      FontPathFree();
      InitConfig();
      FontPathInit(font,(char *)fontpath, fullfont, 1);
      sprintf(lielims, "%s2135.png", fontpath);
      init_pos();
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver()) //Если IdleGui на самом верху
    {
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
        if((GetMissedEventCount(0)>0)&&(refresh==1)&&(strlen(fontpath)>4))
        {
          canvasdata=BuildCanvas();
	DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)str1)-1,IDLEICON_Y+GetImgHeight((int)str1)-1,1);
	DrawImg(IDLEICON_X,IDLEICON_Y,(int)str1);
        DrawCanvas(canvasdata,date_X-GetImgHeight((int)lielims)-1,date_Y,date_X-GetImgHeight((int)lielims)-1+GetImgWidth((int)str2)-1,date_Y+GetImgHeight((int)str2)-1,1);
	DrawImg(date_X-GetImgHeight((int)lielims)-1,date_Y,(int)str2);
        DrawCanvas(canvasdata,date_X-GetImgHeight((int)lielims)-1,date_Y02,date_X-GetImgHeight((int)lielims)-1+GetImgWidth((int)str3)-1,date_Y02+GetImgHeight((int)str3)-1,1);
	DrawImg(date_X-GetImgHeight((int)lielims)-1,date_Y02,(int)str3);
        DrawCanvas(canvasdata,date_X-GetImgHeight((int)lielims)-1,date_Y03,date_X-GetImgHeight((int)lielims)-1+GetImgWidth((int)str4)-1,date_Y03+GetImgHeight((int)str4)-1,1);
	DrawImg(date_X-GetImgHeight((int)lielims)-1,date_Y03,(int)str4);
      PrintField(date_X,date_Y, calls, align, font, space);
      PrintField(date_X,date_Y02, message, align, font, space);
      PrintField(date_X,date_Y03, other, align, font, space);
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
  GBS_DelTimer(&mytmr);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Missed events - (c)Evilfox");
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
  sprintf(lielims, "%s2135.png", fontpath);
  if(msg)
    ShowMSG(1,(int)"Missed events (c)Evilfox");
  init_pos();
  counter();
  return 0;
}
