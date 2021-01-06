#include "..\inc\swilib.h"
#include "gui.h"
#include "utils.h"

int GetPresTypeCode()
{
  extern const unsigned int BCFG_CALL_TYPE;
  if (BCFG_CALL_TYPE)
  {
    return LONG_PRESS;
  }
  else
  {
    return KEY_DOWN;
  }
}

int hook_proc(int key, int m)
{

  extern const unsigned int BCFG_CALL_BTN;
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==GetPresTypeCode())&&(!IsScreenSaver()))
     if (key==BCFG_CALL_BTN) 
       {
         // Делаем  скрин ГЭ
         GetScreenShot(); 
         // Вызываем гуй выбора
         CreateMainCSM();
       }
  
  return 0;
}

void SetHook()
{
  AddKeybMsgHook((void *)hook_proc);
}

void DestroyHook()
{
  RemoveKeybMsgHook((void *)hook_proc);   
}


