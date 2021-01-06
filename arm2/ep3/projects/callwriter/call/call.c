#include <swilib.h>
#include "../obs/obs.h"
#include "call.h"
amr *file;

void OpenCall()
{
    if(is_call[1]!=CALL_W)//если не пишется
  {



  if(is_call[0]==CALL_A)
  {
      autocall++;
      strcpy(name,"auto\\");
      real_time.sec=0;
      real_time.min=0;
      Close();
   }





  if(is_call[0]==CALL_O)
  {
      out++;
      strcpy(name,"out\\");
  }



  if(is_call[0]==CALL_I)
  {
      in++;
      strcpy(name,"in\\");
  }

  is_call[1]=CALL_W;

  GetDateTime(&d,&t);
  sprintf(name,"%s%d-%d-%u_%d-%d-%d.amr",name,d.day,d.month,d.year,t.hour,t.min,t.sec);
  file=new amr(name,amrmode,bitrate);//запись
  //if(is_call==CALL_AUTOW)func(mic);
  //if((is_call==CALL_OUTW||is_call==CALL_INW)&&ena_loud)func(loud);

  }
}

void CloseCall()
{
  if(is_call==CALL_OUTW||is_call==CALL_INW||is_call==CALL_AUTOW)
  {
     delete []file;
     is_call=CALL_NULL;
     UpdateCSMname();
  }
}

void Close()
{
  if(time_off_off)
{
  if(real_time.sec++>=60)real_time.min++;
  if(real_time.sec==time_off_sec&&real_time.min==time_off_min)
  {
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT);
    return;
  }
  GBS_StartTimerProc(&tmr,SEC,Close);
}
}

void Auto()
{
    if(time_on_on)//если снимать трубку
{
  if(real_time.sec++>=60)real_time.min++;
  if(real_time.sec==time_on_sec&&real_time.min==time_on_min)
  {
    is_call[0]=CALL_A;
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,GREEN_BUTTON);
    return;
  }
  if(is_call[0]==CALL_I)GBS_StartTimerProc(&tmr,SEC,Auto);
}
}
