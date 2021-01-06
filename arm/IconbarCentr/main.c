#include "C:\ARM\inc\swilib.h"
#include "C:\ARM\inc\xtask_ipc.h"
#include "conf_loader.h"
#include "local_ipc.h"
#include "define.h"
#include "mylib.h"

const char ipc_my_name[32]=IPC_ICONBARCENTR_NAME;
const char ipc_grantee_name[]=IPC_GRANTEE_NAME;
const char ipc_control_name[]=IPC_CONTROL_NAME;
IPC_REQ gipc;

extern void kill_data(void *p, void (*func_p)(void *));
unsigned int oldHandlerAddr;
unsigned int* handlerAddr;
typedef void (*func)(short* num);
#pragma segment="ELFBEGIN"
const int minus11=-11;
CSM_RAM *under_idle;
GBSTMR timer;
GUI *datagui;
CSM_RAM *csm;
char s[40];
short* num;
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

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

typedef  unsigned short word;
extern unsigned long strtoul(const char *nptr,char **endptr,int base);

extern const int allcsm;
extern const int csm1;
extern const unsigned int csm1_icon;
extern const char csm1_name[64];
void taimer()
{
  int c;
  csm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next;
  do
  {
    CSM_DESC *desc=csm->constr;
    sprintf(s,"%08X",desc);
  }
  while((csm=csm->next)&&(s!=csm1_name));
  c=strcmp(s,csm1_name);
  if((CSM_root()->csm_q->current_msg_processing_csm==csm))
  {
    if(c==0)
    {
      datagui=GetTopGUI();
      if(datagui)
      {
        if(csm1)
        {
          AddIconToIconBar(csm1_icon,num);
        }
      }
    }
  }
  GBS_StartTimerProc(&timer,50,taimer);
}




static void addIconBar(short* num)//Добавляем иконки в иконбар
{

  #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
 
  //Bluetooth
  extern const int bt;
  extern const int bt_off;
  extern const unsigned int bt_vis_icon;
  extern const unsigned int bt_nvis_icon;
  extern const unsigned int bt_trans_icon;
  extern const unsigned int bt_ntrans_icon;
  extern const unsigned int bt_headset_icon;
  extern const unsigned int bt_off_icon;
  extern const int ena_gui_bt;
  
  //Bluetooth
  if(bt)
  {
    if(!GetCurrAudioPath())
    {
      AddIconToIconBar(bt_headset_icon,num);
    }
    else
    {
      if(BT_GetLocVisibility()==0)
      {
        if(GetPeripheryState(0,1)||GetPeripheryState(0,2))
        {
          AddIconToIconBar(bt_nvis_icon,num);
        }
        else
          if(GetPeripheryState(0,4))
          {
            AddIconToIconBar(bt_ntrans_icon,num);
          }
          else
            if(bt_off)
            {
              AddIconToIconBar(bt_off_icon,num);
            }
      }
      if(BT_GetLocVisibility()==1)
      {
        if(GetPeripheryState(0,1)||GetPeripheryState(0,2))
        {
          AddIconToIconBar(bt_vis_icon,num);
        }
        else
          if(GetPeripheryState(0,4))
          {
            AddIconToIconBar(bt_trans_icon,num);
          }
          else
            if(bt_off)
            {
              AddIconToIconBar(bt_off_icon,num);
            }
      }
    }
  }
  
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
 
  {
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp(ipc->name_to,ipc_my_name)==0)//strcmp_nocase
      {
        switch (msg->submess)
        {
         
        
        }
      }
    }
  }
  }
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      extern const int ena_req;
      if(ena_req) ShowMSG(1,(int)"Конфиг IconbarCentr обновлен!");
      InitConfig();
    }
  }
  return (1);
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

typedef struct
{
  char check_name[8];
  int addr;
}ICONBAR_H;

struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
  ICONBAR_H iconbar_handler;
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
  },
  {
    "IconBar"
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"BTler");
}

void SetIconBarHandler()
{
  MAINCSM.iconbar_handler.addr=(int)addIconBar;
}

int main()
{  
  InitConfig();
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  UpdateCSMname();
  SetIconBarHandler();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  extern const int ena_msg;
  if (ena_msg) ShowMSG(1,(int)"BTler установлен!");
  return 0;
}
