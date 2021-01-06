#include "..\lib\swilib.h"
#define EXT_BUTTON 0x63
CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
    if  (msg->msg==439) {
    
      switch (msg->submess) {
      case 1:
        GBS_SendMessage(MMI_CEPID,LONG_PRESS,EXT_BUTTON);
        break;
      case 2:
        GBS_SendMessage(MMI_CEPID,KEY_UP,EXT_BUTTON);
        break;
      default: ShowMSG(1,(int)"unknown");
      }

    } else {
      csm_result=old_icsm_onMessage(data,msg);
    }
  return(csm_result);
}
int main(void)
{
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsm->constr=&icsmd;
  UnlockSched();
  return 0;
}