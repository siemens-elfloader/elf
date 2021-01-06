// CSMSwaper.cpp: implementation of the CCSMSwaper class.
//
//////////////////////////////////////////////////////////////////////

#include "include.h"
#include "CSMSwaper.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMSwaper::CSMSwaper()
{

}

CSMSwaper::~CSMSwaper()
{

}

CSM_RAM *CSMSwaper::under_idle=NULL;

int CSMSwaper::do_CSMtoTop(CSMQ *csm_q, void *_cmd)
{
  MMICMD *cmd=(MMICMD *)_cmd;
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
      wcsm=(CSM_RAM *)top_csm->prev; //妤抉抖批折忘快技 扭快把快技快投忘快技抑抄 CSM
    }
    else
    {
      wcsm=(CSM_RAM *)csm_q->csm.last;
    }
    ((CSM_RAM *)(wcsm->prev))->next=top_csm; //CSM 扭快把快忱 扭快把快技快投忘快技抑技 找快扭快把抆 批抗忘戒抑志忘快找 扶忘 志快把抒扶我抄 CSM
    if (top_csm)
    {
      top_csm->prev=wcsm->prev; //prev 志快把抒扶快忍抉 CSM 批抗忘戒抑志忘快找 扶忘 CSM 扭快把快忱 扭快把快技快投忘快技抑技
    }
    else
    {
      csm_q->csm.last=wcsm->prev;
    }
    //妥快扭快把抆 志扼找忘志抖攸快技 志 扶批忪扶抉快 技快扼找抉 扭快把快技快投忘快技抑抄 CSM
    ((CSM_RAM *)(wcsm->next=bot_csm->next))->prev=wcsm;
    bot_csm->next=wcsm;
    wcsm->prev=bot_csm;
  }
  while((top_csm?top_csm->prev:csm_q->csm.last)!=work_csm);
//  

  if (!top_csm)
  {
    if ((gui=(int *)((CSM_RAM *)(csm_q->csm.last))->gui_ll.last))
    {
      FocusGUI(gui[3]);
    }
    //妊抉抉忌投快扶我快 抉忌 批扶我折找抉忪快扶我我 扶快扼批投快扼找志批攻投快忍抉 CSM, 扶快抉忌抒抉忱我技抉 忱抖攸 扭把忘志我抖抆扶抉抄 把忘忌抉找抑 IdleCSM
    GBS_SendMessage(MMI_CEPID,MSG_CSM_DESTROYED,0,30002,0);
  }
  return 1;
}

#pragma optimize=no_inline
__thumb void CSMSwaper::LLaddToEnd(LLQ *ll, void *data)
{
  LLIST *d=(LLIST *)data;
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

void CSMSwaper::CSMtoTop(int id, int top_id)
{
  CSMQ *csm_q=CSM_root()->csm_q;
  MMICMD *cmd;
  if (!FindCSMbyID(id)) return;
  if (id==top_id) return; //妖快折快忍抉
  cmd=(MMICMD *)malloc(sizeof(MMICMD));
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

void CSMSwaper::InitUnderIdleCSM()
{
	under_idle=(CSM_RAM *)(FindCSMbyID(CSM_root()->idle_id))->prev;
}
