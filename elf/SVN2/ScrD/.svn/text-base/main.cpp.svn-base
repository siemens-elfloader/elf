#include "../inc/swilib.h"
#include "main.h"


hProc PTable[32];
int tProc=0;
char APP_PATH[254];

#define IPC_UPDATE_STAT 0
const char ipc_my_name[]="IdleUpd";
const IPC_REQ gipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

#pragma segment="ELFBEGIN"
void kill_data( void * p, void(*fptr)(void *))
{
  asm("BX R1");
}


void RegHandle(hProc pProc)
{
  if(tProc<=32)
  {
   PTable[tProc]=pProc;
   tProc++;
  }
  else
    MsgBoxError(1,(int)"Function stack overflow!");
}
void DelHandle(hProc pProc)
{
  for(int a=0;a<tProc;a++)
  {
    if(PTable[a]==pProc)
    {
      memmove((PTable+a),(PTable+a+1),4);
    }
  }
  tProc--;
}

void RedrawProc()
{
  void (*pF)();
  for(int a=0;a<tProc;a++)
  {
    pF=(void(*)())PTable[a];
    pF();
  }
   // Перерисовываем эльфы, заточенные под IdleDisp
   GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
}



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

int maincsm_onmessage(CSM_RAM* data, GBS_MSG* msg)
{  
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ELF_NAME)==0)
      {
        switch (msg->submess)
        {
         case 0: RegHandle((hProc)(ipc->data));
              break; 
         case 1: DelHandle((hProc)(ipc->data));
              break;
          
        }
      }
    }
  }
 
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  int* pRam=(int*)(RamMenuAnywhere()+7);
  char * path = (char *)malloc(strlen(APP_PATH) + strlen("Scr\\*.elf") + 32);
  sprintf(path, "%s%s", APP_PATH, "Scr\\*.elf");
  
  DIR_ENTRY dE; 
  unsigned int err;
   WSHDR*wS;
  
  LockSched();
  *pRam=(int)RedrawProc;
  UnlockSched();
  
  char * d_path = (char *)malloc(strlen(APP_PATH) + strlen("Scr") + 32);
  sprintf(d_path, "%s%s", APP_PATH, "Scr");
  
  if(isdir(d_path,&err)==0)
  {
    mkdir(d_path,&err);
    return;
  }
 
 wS=AllocWS(196);
if (FindFirstFile(&dE,path,&err))
{
  do
 {
    wsprintf(wS,"%s\\%s",dE.folder_name,dE.file_name);
    ExecuteFile(wS,0,0);
 }while(FindNextFile(&dE,&err));
}
FindClose(&dE,&err);
FreeWS(wS);

}

static void maincsm_onclose(CSM_RAM *csm)
{
  int* pRam=(int*)(RamMenuAnywhere()+7);
  LockSched();
  *pRam=0;
  UnlockSched();
  exit();
}

static unsigned short maincsm_name_body[140];
const int minus11=-11;

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
  }
};



int main(const char *exename, const char *filename)
{
  // Пишем путь к папке с эльфом в APP_PATH
  char *path=strrchr(exename,'\\');
  int l;
  if (!path) return 0; //Фигня какая-то
  path++;
  l=path-exename;
  memcpy(APP_PATH,exename,l);
  // Создаем CSM
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  UpdateCSMname();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();  
  return (0);
}
