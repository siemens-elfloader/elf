#include "..\inc\swilib.h"
#include "conf_loader.h"

const int minus11=-11;

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
      ShowMSG(1,(int)"[A]den elf config updated!");
      InitConfig();
    }
  }
  return (1);  
}

static void maincsm_oncreate(CSM_RAM *data)
{

}
GBSTMR mytmr;

static void Killer(void)
{
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

void DoRename(char *path, char *name1, char *name2)
{
    unsigned int err;
    char a[256],b[256];

      sprintf(a,"%s%s",path,name1);
      sprintf(b,"%s%s",path,name2);
      fmove(a,b,&err);
}

extern const char path2[256];
//char rms_path[256];



void renamer()
{
  char *path=malloc(256);
  strcpy(path,path2);
//  volatile int hFile;
//  unsigned int io_error = 0;
//  unsigned int ul;
//  FSTATS stat;
//  sprintf(rms_path, "%s%s", path2, "fifth.mp3");
//  GetFileStats(rms_path,&stat,&ul);
//  if(stat.size==0)
//  {
  DoRename(path,"first.mp3","fifth.mp3");
  DoRename(path,"second.mp3","first.mp3");
  DoRename(path,"third.mp3","second.mp3");
  DoRename(path,"forth.mp3","third.mp3");
  DoRename(path,"fifth.mp3","forth.mp3");
//  }
//  else
//  {
//  DoRename(path,"first.mp3","forth.mp3");
//  DoRename(path,"second.mp3","first.mp3");
//  DoRename(path,"third.mp3","second.mp3");
//  DoRename(path,"fifth.mp3","third.mp3");
//  }
//  ShowMSG(1,(int)"Done");
  mfree(path);
}

void Check(void);

void WaitToRemake()
{
  if(IsCalling())
  {
    GBS_StartTimerProc(&mytmr, 216, WaitToRemake);
  }
  else
  {
    renamer();
    GBS_StartTimerProc(&mytmr, 216, Check);
  }
}

void Check()
{
  if(IsCalling())
  {
    WaitToRemake();
  }
  else
    GBS_StartTimerProc(&mytmr, 216, Check);
}

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"[A]den elf - (c)Evilfox");
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
  if (ENA_HELLO_MSG) ShowMSG(1,(int)"[A]den elf - (c)Evilfox");  
  Check();
//  renamer();
  return 0;
}
