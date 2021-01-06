#include "..\inc\swilib.h"
#include "conf_loader.h"

const int minus11=-11;

extern const unsigned int REFRESH;
extern const unsigned int IDLEICON_X;
extern const unsigned int IDLEICON_Y;
char ICON_PATH[64];
extern const char path[64];
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
extern const unsigned int PNG;
CSM_RAM *under_idle;
int str1;
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
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
void *canvasdata;

void start()
{
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id)&&!IsScreenSaver())
  {
  if (str1==PNG)
  {
    str1=1;
    sprintf(ICON_PATH, "%s%d.png", path, str1);
    canvasdata=BuildCanvas();
    DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)ICON_PATH)-1,
		   IDLEICON_Y+GetImgHeight((int)ICON_PATH)-1,1);
	DrawImg(IDLEICON_X,IDLEICON_Y,(int)ICON_PATH);
    GBS_StartTimerProc(&mytmr, REFRESH, start);
  }
  else
  {
    str1=str1+1;
    sprintf(ICON_PATH, "%s%d.png", path, str1);
    canvasdata=BuildCanvas();
    DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)ICON_PATH)-1,
		   IDLEICON_Y+GetImgHeight((int)ICON_PATH)-1,1);
	DrawImg(IDLEICON_X,IDLEICON_Y,(int)ICON_PATH);
    GBS_StartTimerProc(&mytmr, REFRESH, start);
  }
  }
  else 
    GBS_StartTimerProc(&mytmr, REFRESH, start);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
//  char *ICON_PATH;
//  ICON_PATH = ("4:\\zbin\\anime\\",str1,".png"); // лучше сделать так
//  char *ICON_PATH=malloc(500);
//  sprintf(ICON_PATH, "4:\\zbin\\anima\\%s.png",str1);
  void *canvasdata=BuildCanvas();
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"PNG animation config updated!");
      InitConfig();
    }
  }
  /*
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
    {
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
	void *canvasdata=BuildCanvas();
      }
	//Тут трохи поменял
	// by Rainmaker: Рисуем канву только для иконки и выводим в своих координатах
	DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)ICON_PATH)-1,
		   IDLEICON_Y+GetImgHeight((int)ICON_PATH)-1,1);
	DrawImg(IDLEICON_X,IDLEICON_Y,(int)ICON_PATH);
      }
  */
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  GBS_StopTimer(&mytmr);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"PNG Animation - (c)Evilfox");
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
  extern const int ENA_HELLO_MSG;
  if (ENA_HELLO_MSG) ShowMSG(1,(int)"PNG animation - (c)Evilfox"); 
  str1=1;
  start();
}
