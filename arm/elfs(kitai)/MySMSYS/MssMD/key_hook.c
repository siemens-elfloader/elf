#include "..\..\inc\swilib.h"
#include "language.h"
#include "MySMSYS_ipc.h"
#include "main.h"
#include "config_data.h"

IPC_REQ kh_ipc=
{
  my_ipc_name,
  my_ipc_name,
  NULL
};

int mode=0;

int MyKeyHook(int submsg, int msg)
{
#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);
  if(msg==KEY_UP)
    mode=0;
  if(msg==KEY_DOWN)
  {
    if(submsg==KEY1)
      mode=1;
    else if(submsg==KEY2 && mode==1)
    {
      if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
      GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_MAIN,&kh_ipc);
      return KEYHOOK_BREAK;
    }
/*    switch(submsg)
    {
    case KEY1:
      mode=1;
      break;
    case KEY2:
      if(mode==1)
      {
	if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
	GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_MAIN,&kh_ipc);
      }
      break;
    default:
      break;
    }*/
  }
  if(!IsSSOnTop() && IsUnlocked()) return KEYHOOK_NEXT;
  if(msg==KEY_DOWN && submsg==LEFT_SOFT && new_sms_n>0)
  {
    if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
    GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_IN_ALL,&kh_ipc);
    return KEYHOOK_BREAK;
  }
  return KEYHOOK_NEXT;
}



