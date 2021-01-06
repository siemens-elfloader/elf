#include "../inc/swilib.h"
#include "swaper.h"

/*extern */CSM_RAM *under_idle;

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
      wcsm=(CSM_RAM *)top_csm->prev; //ѕолучаем перемещаемый CSM
    }
    else
    {
      wcsm=csm_q->csm.last;
    }
    ((CSM_RAM *)(wcsm->prev))->next=top_csm; //CSM перед перемещаемым теперь указывает на верхний CSM
    if (top_csm)
    {
      top_csm->prev=wcsm->prev; //prev верхнего CSM указывает на CSM перед перемещаемым
    }
    else
    {
      csm_q->csm.last=wcsm->prev;
    }
    //“еперь вставл€ем в нужное место перемещаемый CSM
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
    //—ообщение об уничтожении несуществующего CSM, необходимо дл€ правильной работы IdleCSM
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
  if (id==top_id) return; //Ќечего
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

