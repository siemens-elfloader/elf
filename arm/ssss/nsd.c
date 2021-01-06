#include "..\inc\swilib.h"
const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;


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
 
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{
 
}

extern void StartGUI();
extern int mode;
int my_keyhook(int key, int m)
{
     if (key=='0'&&mode==0) 
       {
         StartGUI();
       }
  
  return 0;
}

static void Killer(void)
{
  RemoveKeybMsgHook((void *)my_keyhook);  
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
  0,
  0,
  0,
  0,
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



static void UpdateCSMDname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"nsd");
}

void CreateNSD()
{
  mode=0;
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMDname();  
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();  
  AddKeybMsgHook((void *)my_keyhook);
}
