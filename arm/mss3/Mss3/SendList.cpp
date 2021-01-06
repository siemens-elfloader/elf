#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "SendList.h"
#include "Vibra.h"
#include "PlaySound.h"
//#include "ShortVibra.h"
#include "DaemonCSM.h"
#include "CSMswaper.h"
#include "..\..\inc\xtask_ipc.h"


SNDLST * SendList::AllocSL()
{
  SNDLST *sl=new SNDLST;
  zeromem(sl, sizeof(SNDLST));
  return sl;
}

void SendList::FreeList()
{
  SNDLST *sl;
  SNDLST *sl0;
  LockSched();
  sl=this->sltop;
  this->sltop=NULL;
  UnlockSched();
  while(sl)
  {
    sl0=sl->next;
    if(sl->text)
      FreeWS(sl->text);
    delete sl;
    sl=sl0;
  }
}

SendList::SendList()
{
  this->sltop=NULL;
}

SendList::~SendList()
{
  this->FreeList();
}

void SendList::AddToList(SNDLST *sl) //end
{
  if(!sl) return;
  LockSched();
  if(!this->sltop)
  {
    this->sltop=sl;
  }
  else
  {
    SNDLST *s0=this->sltop;
    while(s0->next)
      s0=s0->next;
    s0->next=sl;
    sl->prev=s0;
  }
  UnlockSched();
}

void SendList::AddToList(const char *number, WSHDR *text)
{
  int wlen;
  SNDLST *sl;
  if(!number || !strlen(number) || !text || !(wlen=text->wsbody[0]))
    return;
  sl=AllocSL();
  strcpy(sl->number, number);
  sl->text=AllocWS(wlen);
  wstrcpy(sl->text, text);
  AddToList(sl);
}

void SendList::DeleteSL(SNDLST *sl)
{
  if(!sl) return;
  LockSched();
  if(sl==this->sltop)
  {
    this->sltop=this->sltop->next;
    if(this->sltop) this->sltop->prev=NULL;
  }
  else
  {
    sl->prev->next=sl->next;
    if(sl->next) sl->next->prev=sl->prev;
  }
  UnlockSched();
  if(sl->text) FreeWS(sl->text);
  delete sl;
}

SNDLST * SendList::FindSL(int csm_id)
{
  SNDLST *sl;
  if(!csm_id) return 0;
  sl=this->sltop;
  while(sl)
  {
    if(sl->csm_id==csm_id)
      return sl;
    sl=sl->next;
  }
  return 0;
}


int SendList::IsSending()
{
  SNDLST *sl=this->sltop;
  while(sl)
  {
    if(sl->csm_id)
      return 1;
    sl=sl->next;
  }
  return 0;
}

int SendList::SendStart()
{
  int len;
  int csm_id;
  SNDLST *sl;
  WSHDR *ws;
  if(IsSending())
    return 0;
  sl=this->sltop;
  if(
    !sl
    ||!strlen(sl->number)
    ||!sl->text
    ||!(len=sl->text->wsbody[0])
    )
    return 0;
  ws=AllocWS(len+4);
  wstrcpy(ws, sl->text);
  csm_id=SendSMS(ws, sl->number, MMI_CEPID, MSG_SMS_RX-1, 6);
  sl->csm_id=csm_id;
  return csm_id;
}


int SendList::SendEnd(int csm_id)
{
  SNDLST *sl;
  if(!csm_id
    || !(sl=FindSL(csm_id))
    )
    return 0;
  if(CFG_ENA_SAVE_SENT/* && !sl->send_fail*/)
  {
    SMSDATA->SaveMss(sl->text, sl->number, NULL, TYPE_SENT, 2);
    SendMyIpc(SMSYS_IPC_SMS_DATA_UPDATE);
  }
  DeleteSL(sl);
  return 1;
}


int SendList::IsSendCSM(int csm_id)
{
  SNDLST *sl=this->sltop;
  while(sl)
  {
    if(sl->csm_id==csm_id)
      return 1;
    sl=sl->next;
  }
  return 0;
}

void SendList::CatList(SNDLST *sl)
{
  if(!sl)
    return;
  LockSched();
  if(!this->sltop)
  {
    this->sltop=sl;
  }
  else
  {
    SNDLST *s0=this->sltop;
    while(s0->next)
      s0=s0->next;
    s0->next=sl;
    sl->prev=s0;
  }
  UnlockSched();
}


void SendList::SendOnTop(SendList *sndlst)
{
  sndlst->SendStart();
}

void SendList::Send(SendList *sndlst)
{
  CSM_RAM *tcsm;
  tcsm=DaemonCSM::GetTopCSM();
  if(
    sndlst
    && sndlst->SendStart()
    && CFG_ENA_SNED_ON_BG
    && tcsm
    && tcsm->id
    )
  {
    CsmToTop(tcsm->id);
    //CSMSwaper::CSMtoTop(tcsm->id, -1);
  }
}


//DEL void SendList::SendGUIDesMSG(GBS_MSG *msg)
//DEL {
//DEL   CSM_RAM *icsm;
//DEL   SNDLST *sl;
//DEL   sl=this->sltop;
//DEL   while(sl)
//DEL   {
//DEL     if(sl->csm_id
//DEL       && (icsm=FindCSMbyID(sl->csm_id))
//DEL       )
//DEL     {
//DEL       GetCPUClock();
//DEL       if((int)msg->data0 == ((int*)icsm)[0x30/4])
//DEL       {
//DEL 	if((int)msg->data1==1) //cancal
//DEL 	  sl->send_fail=0;
//DEL 	else
//DEL 	  sl->send_fail=1;
//DEL 	return;
//DEL       }
//DEL     }
//DEL     sl=sl->next;
//DEL   }
//DEL }
IPC_REQ SendList::ipc_xtask=
{
  IPC_XTASK_NAME,
  IPC_NAME,
  NULL
};

void SendList::CsmToTop(int csm_id)
{
  LockSched();
  ipc_xtask.data=(void *)csm_id;
  GBS_SendMessage(MMI_CEPID, MSG_IPC, IPC_XTASK_SHOW_CSM, &ipc_xtask);
  UnlockSched();
}
