#include "..\inc\swilib.h"
#include "main.h"
#include "conf_loader.h"
#include "keyhook.h"
#include "revision.h"
#include "utils.h"
#include "idle.h"
#include "editor.h"
#include "conf_ex.h"
#include "IdleLinks.h"

char *MY_IPC_NAME = "IL";
#define UTF16_ALIGN_RIGHT (0xE01D)
#define IPC_CHECK_DOUBLERUN 91089

IPC_REQ gipc;

int temp;

int b_dooble = 0;

const int minus11=-11;

unsigned short NSD_name_body[140];

void NSD_CheckDoubleRun(void)
{
  if ((int)(gipc.data)!=-1)
  {
    b_dooble = 1;
    EDITOR_Create(); // Запускаем гуевый едитор ярлычков
    CloseCSM(temp); // Прибиваем повторно запустившийся NSD демон
  }
}

void NSD_onCreate(CSM_RAM *data)
{
  LockSched();
  SetHook();
  gipc.name_to=MY_IPC_NAME;
  gipc.name_from=MY_IPC_NAME;
  gipc.data=(void *)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
  UnlockSched();
}

void NSD_DrawInIdle()
{
  
  extern const unsigned int BCFG_KBD_STATE;
  
  if ((BCFG_KBD_STATE==0) && (IsUnlocked())) return;
  if ((BCFG_KBD_STATE==1) && (!IsUnlocked())) return;

  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&(!IsScreenSaver()))
  {
    extern TLabelData *TLabels;
    if (TLabels)
    {
      TLabelData *CurrentLabel = TLabels;
      Draw_NSD(CurrentLabel);
      while(CurrentLabel->next)
      {
        CurrentLabel = CurrentLabel->next;
        Draw_NSD(CurrentLabel);
      }
    }
  }  
}

int NSD_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  // Проверка на повторный запуск
  if (msg->msg==MSG_IPC)
  {
   IPC_REQ *ipc;
   if ((ipc=(IPC_REQ*)msg->data0))
   {
     if (msg->submess == IPC_CHECK_DOUBLERUN)
     {
       if (ipc->name_from==MY_IPC_NAME) SUBPROC((void *)NSD_CheckDoubleRun);
       else ipc->data=(void *)temp;
     }
     // Точим  под IdleDisp
     if (stricmp(ipc->name_to,"IdleUpd")==0)
     {
       NSD_DrawInIdle();
     }
   }
  }
  

  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    InitConfig();
    FreeBcfgs();
    LoadBcfgs();
    DestroyHook();
    SetHook();
  }
 
  //redraw
  return 1;
}  

void NSD_onClose(CSM_RAM *data)
{
  DestroyHook();
  if (!b_dooble)
  {
    SUBPROC((void *)ElfKiller);
  }
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}NSDCSM =
{
  {
  NSD_onMessage,  
  NSD_onCreate, 
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  NSD_onClose, 
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    NSD_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void NSD_SetName(void)
{
  wsprintf((WSHDR *)(&NSDCSM.maincsm_name),"IdleLinks %cr%d",UTF16_ALIGN_RIGHT, __SVN_REVISION__);
}

int NSD_Create()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  temp = CreateCSM(&NSDCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  NSD_SetName();
  return temp;
}



