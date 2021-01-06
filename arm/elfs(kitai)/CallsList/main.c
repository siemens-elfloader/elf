#include "..\inc\swilib.h"

CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

int (*old_ed_onkey)(GUI *gui, GUI_MSG *msg);
void (*old_ed_ghook)(GUI *gui, int cmd);
void (*old_ed_redraw)(void *data);

void (*old_icsm_onClose)(CSM_RAM*);

int my_ed_onkey(GUI *gui, GUI_MSG *msg)
{
  int key=msg->gbsmsg->submess;
  int m=msg->gbsmsg->msg;
  int r;
  if (IsUnlocked()&&(m==KEY_DOWN)&&(key==GREEN_BUTTON))
  {
    ShowCallList(2, 0);
    ShowCallList(1, 0);
//    ShowCallList(0, 0);
    r=0;
  }
  else    
    r=old_ed_onkey(gui,msg);
  return(r);
}

void DoSplices(GUI *gui)
{
  static INPUTDIA_DESC my_ed;
  memcpy(&my_ed,gui->definition,sizeof(INPUTDIA_DESC));
  if (my_ed.onKey != my_ed_onkey)
  {
    old_ed_onkey=my_ed.onKey;
    my_ed.onKey=my_ed_onkey;
    gui->definition=&my_ed;
  }
}

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result=0;

  csm_result=old_icsm_onMessage(data,msg); //Вызываем старый обработчик событий

#define idlegui_id (((int *)data)[DISPLACE_OF_IDLEGUI_ID/4])  
  
  if (IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if (igui) //И он существует (а не в проекте ;))
    {
      DoSplices(igui);
    }
  }
  return(csm_result);
}

void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}


int main(void)
{
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
//  old_icsm_onClose=icsmd.onClose;
//  icsmd.onClose=MyIDLECSM_onClose;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsm->constr=&icsmd;
  UnlockSched();
  return 0;
}
