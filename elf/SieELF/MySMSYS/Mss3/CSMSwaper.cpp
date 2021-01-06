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
      wcsm=(CSM_RAM *)top_csm->prev; //����ݧ��ѧ֧� ��֧�֧ާ֧�ѧ֧ާ�� CSM
    }
    else
    {
      wcsm=(CSM_RAM *)csm_q->csm.last;
    }
    ((CSM_RAM *)(wcsm->prev))->next=top_csm; //CSM ��֧�֧� ��֧�֧ާ֧�ѧ֧ާ�� ��֧�֧�� ��ܧѧ٧�ӧѧ֧� �ߧ� �ӧ֧��ߧڧ� CSM
    if (top_csm)
    {
      top_csm->prev=wcsm->prev; //prev �ӧ֧��ߧ֧ԧ� CSM ��ܧѧ٧�ӧѧ֧� �ߧ� CSM ��֧�֧� ��֧�֧ާ֧�ѧ֧ާ��
    }
    else
    {
      csm_q->csm.last=wcsm->prev;
    }
    //���֧�֧�� �ӧ��ѧӧݧ�֧� �� �ߧ�اߧ�� �ާ֧��� ��֧�֧ާ֧�ѧ֧ާ�� CSM
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
    //�����ҧ�֧ߧڧ� ��� ��ߧڧ���ا֧ߧڧ� �ߧ֧���֧��ӧ���֧ԧ� CSM, �ߧ֧�ҧ��էڧާ� �էݧ� ���ѧӧڧݧ�ߧ�� ��ѧҧ��� IdleCSM
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
  if (id==top_id) return; //���֧�֧ԧ�
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
