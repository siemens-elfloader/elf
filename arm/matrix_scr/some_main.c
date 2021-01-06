#include "G:\ARM\swilib.h"
char col[]={140,50,195,30};
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int my_keyhook(int submsg, int msg)
{
  if (submsg!='#') return(0);
  if (submsg=='*') 
  {
    ShowMSG(1,(int)"exiting!");
    SUBPROC((void *)ElfKiller);
  }
  /*if (IsUnlocked())
  {
    if (msg==KEY_DWON)
    {
      GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON);
    }
    return(2);
  }*/
  switch(msg)
  {
  case KEY_DOWN:
    //GBS_DelTimer(&matrix);
    DrawroundedFrame(0,0,132,176,0,0,0,col,col);
    break;
  /*case KEY_UP:
    if (mode==1)
    {
      RemoveKeybMsgHook((void *)my_keyhook);
      ShowMSG(1,(int)"XTask отлючен!");
      SUBPROC((void *)ElfKiller);
      break;
    }
    break;*/
  }
  return(2);
}

void main(void)
{
  LockSched();
  if (!AddKeybMsgHook_end((void *)my_keyhook))
  {
    ShowMSG(1,(int)"Невозможно зарегистрировать обработчик!");
    SUBPROC((void *)ElfKiller);
  }
  else
  {
    ShowMSG(1,(int)"The Matrix has You..");
  }
  UnlockSched();
}