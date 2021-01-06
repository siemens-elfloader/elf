#include "../inc/swilib.h"
#include "csm_work.h"
#include "conf_loader.h"
#include "minigps_logger.h"

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
const int minus11=-11;

static void maincsm_oncreate(CSM_RAM *data)
{

}

extern void kill_data(void *p, void (*func_p)(void *));
static unsigned short maincsm_name_body[140];
extern int MyCSM_onMessage(CSM_RAM* data,GBS_MSG* msg);
extern WSHDR *Out_WS;
extern GBSTMR mytmr;


static void Killer(void)
{
  extern void *ELF_BEGIN;
  GBS_DelTimer(&mytmr);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  KillRamNetCache();
  FreeWS(Out_WS);
  SUBPROC((void *)Killer);
}

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  MyCSM_onMessage,
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

void PatchCSMQueue()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"GPSLogger");
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();          
}
//EOL,EOF
