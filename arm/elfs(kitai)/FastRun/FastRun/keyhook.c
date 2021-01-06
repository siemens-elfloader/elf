#include "swilib.h"
int my_keyhook(int submsg, int msg)
{
  if (submsg!=CALL_BUTTON) return(0);
  if (my_csm_id)
  {
    if (((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=my_csm_id)
    {
      CloseCSM(my_csm_id);
    }
    return(0);
  }
  switch(msg)
  {
  case KEY_DOWN:
    if (mode_enter==2)
    {
      GBS_SendMessage(MMI_CEPID,KEY_UP,CALL_BUTTON);
      return (0);
    }
     
    mode_enter=0;
    return (2);
  case KEY_UP:
    if (mode_enter==0)
    {
      mode_enter=2;
      GBS_SendMessage(MMI_CEPID,KEY_DOWN,CALL_BUTTON);
      return (2);
    }
    if (mode_enter==2)
    {
      mode_enter=0;
      return (0);
    }
    mode_enter=0;
    return (2);      
  case LONG_PRESS:
    mode_enter=1;
    if (IsUnlocked()||ENA_LOCK)
    {
      do_gui(0,0);
    }
    mode=0;
    break;
  }
 
return(2);
}