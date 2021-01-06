#include <swilib.h>
#include "../obs/obs.h"
#include "call.h"

unsigned int in=0,out=0,autocall=0;
char name[256];
TDate d;
TTime real_time,t;
int is_call[2]={0,0};
amr *file;

void OpenCall()
{

    if(is_call[1]!=CALL_W)//если не пишется
  {

  strcpy(name,folder);

  if(is_call[0]==CALL_A)
  {
      autocall++;
      strcat(name,"auto\\");
      real_time.sec=0;
      real_time.min=0;
      Close(&tmr);
   }


  if(is_call[0]==CALL_O)
  {
      out++;
      strcat(name,"out\\");
  }



  if(is_call[0]==CALL_I)
  {
      in++;
      strcat(name,"in\\");
  }
  if(!isdir(name,0))_mkdir(name,0);
  is_call[1]=CALL_W;

  GetDateTime(&d,&t);
  sprintf(name,"%s%d%d%lu\\",name,d.day,d.month,d.year);
  if(!isdir(name,0))_mkdir(name,0);
  sprintf(name,"%s%d%d%d.amr",name,t.hour,t.min,t.sec);



  file=new amr(name,amrmode,bitrate);//запись
  //if(is_call==CALL_AUTOW)func(mic);
  //if((is_call==CALL_OUTW||is_call==CALL_INW)&&ena_loud)func(loud);

  }
}

void CloseCall()
{

  if(is_call[1]==CALL_W)
  {
     ShowMSG(1,(int)"close");
     delete file;
     is_call[0]=CALL_N;
     is_call[1]=CALL_N;
     UpdateCSMname();
  }
}

void Close(GBSTMR *t)
{
  if(time_off_off)
{
  if(real_time.sec++>=60)real_time.min++;
  if(real_time.sec==time_off_sec&&real_time.min==time_off_min)
  {
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_SOFT);
    return;
  }
  GBS_StartTimerProc(&tmr,216,Close);
}
}

void Auto(GBSTMR *t)
{
    if(time_on_on)//если снимать трубку
{
  if(real_time.sec++==60)real_time.min++;
  if(real_time.sec==time_on_sec&&real_time.min==time_on_min)
  {
    is_call[0]=CALL_A;
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,GREEN_BUTTON);
    return;
  }
  if(is_call[0]==CALL_I)GBS_StartTimerProc(&tmr,216,Auto);
}
}
