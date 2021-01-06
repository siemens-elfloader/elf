#include "..\inc\swilib.h"
#include "conf_loader.h"

const int minus11=-11;

char left[64];
char right[64];
char up[64];
char down[64];
extern const char path[64];
extern const int SSSS;
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
extern const int everywhere;
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
void start()
{
  if (str1==1)
  {
    str1=2;
    sprintf(left, "%sleft1.png", path);
    sprintf(right, "%sright1.png", path);
    sprintf(up, "%sup1.png", path);
    sprintf(down, "%sdown1.png", path);
    GBS_StartTimerProc(&mytmr, 216, start);
  }
  else
  {
    str1=1;
    sprintf(left, "%sleft2.png", path);
    sprintf(right, "%sright2.png", path);
    sprintf(up, "%sup2.png", path);
    sprintf(down, "%sdown2.png", path);
    GBS_StartTimerProc(&mytmr, 216, start);
  }
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  void *canvasdata=BuildCanvas();
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"lampo4ki config updated!");
      InitConfig();
    }
  }
  #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
	void *canvasdata=BuildCanvas();
      }
      if(!SSSS)
      {
      DrawImg(0,0,(int)left);
      DrawImg(240-GetImgWidth((int)right),0,(int)right);
      DrawImg(GetImgWidth((int)left),0,(int)up);
      DrawImg(GetImgWidth((int)left),320-GetImgHeight((int)down),(int)down);
      }
      else
        {
      DrawImg(0,0,(int)left);
      DrawImg(132-GetImgWidth((int)right),0,(int)right);
      DrawImg(GetImgWidth((int)left),0,(int)up);
      DrawImg(GetImgWidth((int)left),176-GetImgHeight((int)down),(int)down);
      }
      }
    else
      if(everywhere)
    {
      if(!SSSS)
      {
      DrawImg(0,0,(int)left);
      DrawImg(240-GetImgWidth((int)right),0,(int)right);
      DrawImg(GetImgWidth((int)left),0,(int)up);
      DrawImg(GetImgWidth((int)left),320-GetImgHeight((int)down),(int)down);
      }
      else
        {
      DrawImg(0,0,(int)left);
      DrawImg(132-GetImgWidth((int)right),0,(int)right);
      DrawImg(GetImgWidth((int)left),0,(int)up);
      DrawImg(GetImgWidth((int)left),176-GetImgHeight((int)down),(int)down);
      }
    }
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"lampo4ki - (c)Evilfox");
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
  if (ENA_HELLO_MSG) ShowMSG(1,(int)"lampo4ki - (c)Evilfox"); 
  str1=1;
  start();
}
