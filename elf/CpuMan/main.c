#include "..\inc\swilib.h"
#include "local_ipc.h"
#include "../inc/xtask_ipc.h"
#include "main.h"
#include "conf_loader.h"


extern void kill_data(void *p, void (*func_p)(void *));

const char ipc_my_name[]=IPC_TEXTINFO_NAME;
const IPC_REQ gipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

#define TMR_SECOND 216

#pragma inline=forced
int toupper(int c)
{
	if ((c>='a')&&(c<='z')) c+='A'-'a';
	return(c);
}

//----------------------------------------------------------------//

#pragma swi_number=0x221
__swi __arm int SetCpuClockLow();

#pragma swi_number=0x222
__swi __arm int SetCpuClockTempHi();

#pragma swi_number=0x0C5
__swi __arm int IsIdleUiOnTop();



int cpumode=1;
GBSTMR mytmr;
int active=0;

void CpuUse()
{  
  if(IsScreenSaver()) cpumode=0;
  if(cpumode) SetCpuClockTempHi(2);
  else SetCpuClockLow(2);
 
  GBS_StartTimerProc(&mytmr, 50, CpuUse);
} 

int mode;
int mode_enter;
extern const int ACTIVE_KEY_1;
extern const int ACTIVE_KEY_STYLE;

int my_keyhook(int submsg, int msg)
{
  if(submsg==ACTIVE_KEY_1 && ACTIVE_KEY_STYLE!=2 && !active)
    {
      switch(msg)
      {
        case KEY_DOWN:
          if (!ACTIVE_KEY_STYLE)
          {
            if(IsUnlocked())
               {
                cpumode=!cpumode;
                if(cpumode) ShowMSG(2,(int)"208");
                else ShowMSG(2,(int)"52");
               }
            return(2);
          }
          else
          {
            if (mode_enter==2)
            {
              GBS_SendMessage(MMI_CEPID,KEY_UP,ACTIVE_KEY_1);
              return (0);
            }
            mode_enter=0;
            return (2);
          }          
        case KEY_UP:
          if (ACTIVE_KEY_STYLE)
          {
            if (mode_enter==0)
            {
              mode_enter=2;
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,ACTIVE_KEY_1);
              return (2);
            }
            if (mode_enter==2)
            {
              mode_enter=0;
              return (0);
            }
            mode_enter=0;
            return (2);
          }          
        case LONG_PRESS:
          if (ACTIVE_KEY_STYLE)
          {
            mode_enter=1;
             if(IsUnlocked())
               {
                  cpumode=!cpumode;
               }            
          }
         break;
      }
    }
  else
  {
  // * + # implementation
  if ((ACTIVE_KEY_STYLE==2) && !active)
  {
    if (msg==KEY_UP)
    {
      mode=0;
      return KEYHOOK_NEXT;
    }
    if (msg==KEY_DOWN)
    {
      switch (submsg)
      {
      case '*':
        mode=1;
        return (0);
      case '#':
        if (mode==1)
        {
           if(IsUnlocked())
                {
                  cpumode=!cpumode;
                }
              else mode=0;
        }
        else { active=0; return KEYHOOK_NEXT; }
      }
     }
    }
   }  
return 0;
}

//---------------------------------------------------------------------------//

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

void maincsm_oncreate(CSM_RAM *data)
{
   GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"CpuMan config updated!");
      InitConfig();
    }
  }
  return 1;// csm_result;  
}



void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&mytmr);
  RemoveKeybMsgHook((void *)my_keyhook);
  SUBPROC((void *)ElfKiller);
}



#pragma swi_number=0x27 
__swi __arm void AddIconToIconBar(int pic, short *num);

int hmm;
int ggg;

void addIconBar(short* num)
{
  if(!cpumode) return;
  AddIconToIconBar( 6700, num);  
}

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


void SetIconBarHandler()
{
  MAINCSM.iconbar_handler.addr = (int)addIconBar;
}

CSM_DESC icsmd;

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"CpuManD");
}

int main()
{ 
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  InitConfig();
  UpdateCSMname();
  LockSched();

  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  my_csm_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  
  SetIconBarHandler();
  AddKeybMsgHook((void *)my_keyhook);
  CpuUse();  

  ShowMSG(1,(int)"start");

  return 0;
}
