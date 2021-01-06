// Mss3App.cpp: implementation of the Mss3App class.
//
//////////////////////////////////////////////////////////////////////
#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "SmsListMenu.h"
#include "DialogCSM.h"
#include "LangPack.h"
#include "Vibra.h"
#include "PlaySound.h"
//#include "ShortVibra.h"
#include "SendList.h"
#include "DaemonCSM.h"
#include "CSMswaper.h"
#include "Mss3App.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//DEL Mss3App::Mss3App()
//DEL {
//DEL 
//DEL }

//DEL Mss3App::~Mss3App()
//DEL {
//DEL 
//DEL }
extern "C"
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void InitConfig(void);
}

int Mss3App::Start(char *exename, char *fname)
{
  if(IsAlreadyRuning())
  {
    if(!fname)
      SendMyIpc(SMSYS_IPC_MAIN);
    else if (fname[0] >= '0' && fname[0] <= '4' && fname[1] == ':' && strlen(fname) < 128)
    {
      char *filename=new char[128];
      strcpy(filename, fname);
      SendMyIpc(SMSYS_IPC_FVIEW, filename);
    }
    SUBPROC((void *)Mss3App::Killer);
    return 0;
  }
  InitSetting();
  DaemonCSM *daemon=new DaemonCSM;
  daemon->CreateDaemonCSM();
  //CSMSwaper::InitUnderIdleCSM();
  return 0;
}

void Mss3App::InitSetting()
{
  InitConfig();
  InitDatPath();
}

void Mss3App::InitDatPath()
{
  int x, xl;
  strcpy(sms_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(sms_dat))>0)
  {
    x=sms_dat[xl-1];
    if((x!='\\')&&(x!='/'))
    {
      sms_dat[xl]='\\';
      sms_dat[xl+1]=0;
    }
    strcat(sms_dat, "SMS\\SMS.dat");
  }
  extern const char CFG_MAIN_FOLDER[128];
  strcpy(main_folder, CFG_MAIN_FOLDER);
  if((xl=strlen(main_folder))>0)
  {
    x=main_folder[xl-1];
    if((x!='\\')&&(x!='/'))
    {
      main_folder[xl]='\\';
      main_folder[xl+1]=0;
    }
  }
}

void Mss3App::Killer()
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int Mss3App::IsAlreadyRuning()
{
  CSM_RAM *icsm;
  WSHDR *ws, wsn;
  unsigned short wsb[16];
  ws=CreateLocalWS(&wsn, wsb, 16);
  wsprintf(ws, ELFFNAMED);
  icsm=(CSM_RAM *)((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next;
  while(((unsigned int)(icsm->constr)>>27)==0x15)
  {
    WSHDR *tws=(WSHDR *)(((char *)icsm->constr)+sizeof(CSM_DESC));
    if((tws->ws_malloc==NAMECSM_MAGIC1)&&(tws->ws_mfree==NAMECSM_MAGIC2))
    {
      if(!wstrncmp_nocase(tws, ws, sizeof(ELFFNAMED)))
        return 1;
    }
    icsm=(CSM_RAM *)icsm->next;
  }
  return 0;
}
