#include "C:\ARM_ALL\inc\swilib.h"
#include "conf_loader.h"

const int minus11=-11;

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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  void *canvasdata=BuildCanvas();
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
  extern const char *successed_config_filename;
  if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
  {
  extern const int ena_req;
  if (ena_req) ShowMSG(1,(int)"Конфиг BatNet'a обновлен!");
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
  extern const int ena_bat;
  extern const unsigned int x_bat;
  extern const unsigned int y_bat;
  extern const unsigned int pic_bat;
  unsigned short *cap=RamCap();
  if(ena_bat)
  {
  if(*cap==0) DrawImg(x_bat,y_bat,pic_bat);//0% батарея
  if(*cap>=1) DrawImg(x_bat,y_bat,pic_bat);//0% батарея
  if(*cap>=11) DrawImg(x_bat,y_bat,pic_bat+2);//10% батарея
  if(*cap>=21) DrawImg(x_bat,y_bat,pic_bat+3);//20% батарея
  if(*cap>=31) DrawImg(x_bat,y_bat,pic_bat+4);//30% батарея
  if(*cap>=41) DrawImg(x_bat,y_bat,pic_bat+5);//40% батарея
  if(*cap>=51) DrawImg(x_bat,y_bat,pic_bat+6);//50% батарея
  if(*cap>=61) DrawImg(x_bat,y_bat,pic_bat+7);//60% батарея
  if(*cap>=71) DrawImg(x_bat,y_bat,pic_bat+8);//70% батарея
  if(*cap>=81) DrawImg(x_bat,y_bat,pic_bat+9);//80% батарея
  if(*cap>=91) DrawImg(x_bat,y_bat,pic_bat+10);//90% батарея
  if(*cap>=95) DrawImg(x_bat,y_bat,pic_bat+1);//100% батарея
  }
  extern const int ena_net;
  extern const unsigned int x_net;
  extern const unsigned int y_net;
  extern const unsigned int pic_net;
  RAMNET *net=RamNet();
  if(ena_net)
  {
  if(net->power<=139) DrawImg(x_net,y_net,pic_net+2);//1 палочка
  if(net->power<=126) DrawImg(x_net,y_net,pic_net+5);//2 палочки
  if(net->power<=113) DrawImg(x_net,y_net,pic_net+8);//3 палочки
  if(net->power<=100) DrawImg(x_net,y_net,pic_net+11);//4 палочки
  if(net->power<=87) DrawImg(x_net,y_net,pic_net-1);//5 палочек
  if(net->power<=74) DrawImg(x_net,y_net,pic_net);//6 палочек
  }
  }
  return (1);
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"BatNet - (c) KIBER-DEMON");
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
  extern const int ena_msg;
  if (ena_msg) ShowMSG(1,(int)"BatNet\n(c) KIBER-DEMON");
}
