#include "E:\ARM\swilib.h"

CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);

WSHDR *ws1;

int xxx;
int yyy;


int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
#define idlegui_id (((int *)data)[0x2C/4])

  csm_result=old_icsm_onMessage(data,msg);

  if (IsGuiOnTop(idlegui_id))
  {
    GUI *igui=GetTopGUI();
    if (igui)
    {
      wsprintf(ws1,"ILDEHOOKv1.0 %d %d",++xxx,yyy);
      DrawFrameInNativeMenu(4,100,127,130,3,3,0,
			    GetPaletteAdrByColorIndex(1),
			    GetPaletteAdrByColorIndex(7));
      DrawString(ws1,8,108,123,125,11,0x20,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
    }
  }
  return(csm_result);
}


int main(void)
{
  ws1=AllocWS(256);
//  old_idleguimethods=0;
//  yyy=xxx=0;
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsm->constr=&icsmd;
  return 0;
}
