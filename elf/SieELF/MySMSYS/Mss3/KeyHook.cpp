// KeyHook.cpp: implementation of the KeyHook class.
//
//////////////////////////////////////////////////////////////////////
#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "AdrList.h"
#include "SmsData.h"
#include "config_data.h"
#include "KeyHook.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//DEL KeyHook::KeyHook()
//DEL {
//DEL 
//DEL }

//DEL KeyHook::~KeyHook()
//DEL {
//DEL 
//DEL }
int KeyHook::mode=0;

void KeyHook::Create()
{
  AddKeybMsgHook((void *)HookProc);
}

int KeyHook::HookProc(int submsg, int msg)
{
  if(msg==KEY_UP)
    mode=0;
  if(msg==KEY_DOWN)
  {
    if(submsg==KEY1)
      mode=1;
    else if(submsg==KEY2 && mode==1)
    {
      if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
      SendMyIpc(SMSYS_IPC_MAIN);
      return KEYHOOK_BREAK;
    }
  }
  if(SMSDATA->n_new
    && msg==KEY_DOWN
    && submsg==LEFT_SOFT
    &&(IsSS() || (!IsUnlocked() && IsIdle()))
    )
  {
    if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
    SendMyIpc(SMSYS_IPC_IN_ALL);
    return KEYHOOK_BREAK;
  }
  return KEYHOOK_NEXT;
}

void KeyHook::Remove()
{
  RemoveKeybMsgHook((void *)HookProc);
}

int KeyHook::IsSS()
{
  SS_RAM *ss_ram;
  if(!(ss_ram=GetScreenSaverRAM())) return 0;
  if((ss_ram->ss_gui_id) && IsGuiOnTop(ss_ram->ss_gui_id))
    return 1;
  if((ss_ram->keylock_gui_id) && IsGuiOnTop(ss_ram->keylock_gui_id))
    return 1;
  return 0;
}

int KeyHook::IsIdle()
{
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if(icsm && IsGuiOnTop(idlegui_id))
    return 1;
  return 0;
}
