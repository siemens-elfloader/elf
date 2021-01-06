#include "../../inc/swilib.h"
#include "CSMswaper.h"
#include "main.h"
#include "config_data.h"

CSM_RAM *under_idle=0;

static int do_CSMtoTop(CSMQ *csm_q, void *_cmd)
{
//  static const char my_color[]={0x00,0x00,0x00,0x32};
  MMICMD *cmd=_cmd;
  int *gui;
  CSM_RAM *wcsm;
  CSM_RAM *top_csm=FindCSM(csm_q,cmd->parent_id);
  CSM_RAM *bot_csm=under_idle;
  if (!bot_csm) return 1;
#ifdef NEWSGOLD
  CSM_RAM *work_csm=FindCSM(csm_q,cmd->id);
#else
  CSM_RAM *work_csm=FindCSM(csm_q,(int)(cmd->cmd_csm));
#endif
  if (!work_csm) return 1;
  if (work_csm==bot_csm) return 1;
  if (work_csm==top_csm) return 1;
  if (work_csm==(top_csm?top_csm->prev:csm_q->csm.last)) return 1;
  if (!top_csm) UnfocusGUI();
//
  do
  {
    if (top_csm)
    {
      wcsm=(CSM_RAM *)top_csm->prev; //§±§à§İ§å§é§Ñ§Ö§Ş §á§Ö§â§Ö§Ş§Ö§ë§Ñ§Ö§Ş§í§Û CSM
    }
    else
    {
      wcsm=csm_q->csm.last;
    }
    ((CSM_RAM *)(wcsm->prev))->next=top_csm; //CSM §á§Ö§â§Ö§Õ §á§Ö§â§Ö§Ş§Ö§ë§Ñ§Ö§Ş§í§Ş §ä§Ö§á§Ö§â§î §å§Ü§Ñ§Ù§í§Ó§Ñ§Ö§ä §ß§Ñ §Ó§Ö§â§ç§ß§Ú§Û CSM
    if (top_csm)
    {
      top_csm->prev=wcsm->prev; //prev §Ó§Ö§â§ç§ß§Ö§Ô§à CSM §å§Ü§Ñ§Ù§í§Ó§Ñ§Ö§ä §ß§Ñ CSM §á§Ö§â§Ö§Õ §á§Ö§â§Ö§Ş§Ö§ë§Ñ§Ö§Ş§í§Ş
    }
    else
    {
      csm_q->csm.last=wcsm->prev;
    }
    //§´§Ö§á§Ö§â§î §Ó§ã§ä§Ñ§Ó§İ§ñ§Ö§Ş §Ó §ß§å§Ø§ß§à§Ö §Ş§Ö§ã§ä§à §á§Ö§â§Ö§Ş§Ö§ë§Ñ§Ö§Ş§í§Û CSM
    ((CSM_RAM *)(wcsm->next=bot_csm->next))->prev=wcsm;
    bot_csm->next=wcsm;
    wcsm->prev=bot_csm;
  }
  while((top_csm?top_csm->prev:csm_q->csm.last)!=work_csm);
//  
/*  DrawRectangle(0,0+YDISP,ScreenW()-1,ScreenH()-1,0,
			my_color,
			my_color);*/

  if (!top_csm)
  {
    if ((gui=((CSM_RAM *)(csm_q->csm.last))->gui_ll.last))
    {
      FocusGUI(gui[3]);
    }
    //§³§à§à§Ò§ë§Ö§ß§Ú§Ö §à§Ò §å§ß§Ú§é§ä§à§Ø§Ö§ß§Ú§Ú §ß§Ö§ã§å§ë§Ö§ã§ä§Ó§å§ğ§ë§Ö§Ô§à CSM, §ß§Ö§à§Ò§ç§à§Õ§Ú§Ş§à §Õ§İ§ñ §á§â§Ñ§Ó§Ú§İ§î§ß§à§Û §â§Ñ§Ò§à§ä§í IdleCSM
    GBS_SendMessage(MMI_CEPID,MSG_CSM_DESTROYED,0,30002,0);
  }
  return 1;
}

#pragma optimize=no_inline
__thumb static void LLaddToEnd(LLQ *ll, void *data)
{
  LLIST *d=data;
  d->next=NULL;
  d->prev=ll->last;
  if (ll->last)
  {
    ((LLIST *)ll->last)->next=d;
  }
  else
  {
    ll->first=d;
  }
  ll->last=d;
}

//Move CSM with "id" on top
//Top is under CSM with "top_id" - may be -1
void CSMtoTop(int id, int top_id)
{
  CSMQ *csm_q=CSM_root()->csm_q;
  MMICMD *cmd;
  if (!FindCSMbyID(id)) return;
  if (id==top_id) return; //§¯§Ö§é§Ö§Ô§à
  cmd=malloc(sizeof(MMICMD));
  cmd->csm_q=csm_q;

  cmd->flag1=5;
#ifdef NEWSGOLD
  cmd->prio=0;
  cmd->id=id;
#else
  cmd->cmd_csm=(CSM_RAM*)id;
#endif
  cmd->parent_id=top_id;
  cmd->proc=do_CSMtoTop;
  LLaddToEnd(&csm_q->cmd,cmd);
}

void InitUnderIdleCSM(void)
{
  under_idle=(FindCSMbyID(CSM_root()->idle_id))->prev;
}


void DoSendBackGround(void *dialog_csm)
{
  CSM_RAM *csm;
  DLG_CSM *dlg_csm;
  if(!CFG_ENA_SNED_ON_BG) return;
  dlg_csm=(DLG_CSM *)dialog_csm;
  if(dlg_csm->gstop) CSMtoTop(dlg_csm->csm.id, -1);
  else
  {
    csm=&(dlg_csm->csm);
    if(csm->prev)
    {
      csm=csm->prev;
      CSMtoTop(csm->id, -1);
    }
  }
}


