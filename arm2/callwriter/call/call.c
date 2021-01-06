#include "call.h"
extern unsigned long strtoul(const char*,char**,int);
void func(const char *adr)
{
  if(adr!=0)
  {
typedef void (*voidfunc)(); 
unsigned int addr=strtoul(adr,0,16); 
voidfunc pp=(voidfunc)addr; 
SUBPROC((void*)pp);
  }
}

void OpenCall()
{
    if(is_call!=CALL_OUTW&&is_call!=CALL_INW&&is_call!=CALL_AUTOW)
  {
  GetDateTime(&d,&t);
  sprintf(name,"unknown_%d-%d-%u_%d-%d-%d.amr",d.day,d.month,d.year,t.hour,t.min,t.sec);
  if(is_call==CALL_AUTO){strcpy(name,"auto\\");real_time.sec=0;real_time.min=0;Close();autocall++;is_call=CALL_AUTOW;}
  if(is_call==CALL_OUT){out++;strcpy(name,"out\\");is_call=CALL_OUTW;}
  if(is_call==CALL_IN){in++;strcpy(name,"in\\");is_call=CALL_INW;}
  sprintf(name,"%s%d-%d-%u_%d-%d-%d.amr",name,d.day,d.month,d.year,t.hour,t.min,t.sec);
  Obs_CreateAmrFile(name);
  Obs_StartAmrWrite();
  if(is_call==CALL_AUTOW)func(mic);
  if((is_call==CALL_OUTW||is_call==CALL_INW)&&ena_loud)func(loud);
  
  }
}

void CloseCall()
{
  if(is_call==CALL_OUTW||is_call==CALL_INW||is_call==CALL_AUTOW)
  {
     Obs_StopAmrWrite();
     is_call=CALL_NULL;
     UpdateCSMname();
  }
}

void Close()
{
  if(time_off_off)
{
  if(real_time.sec++>=60)real_time.min++;
  if(real_time.sec>=time_off_sec+1&&real_time.min>=time_off_min)
  {
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,RED_BUTTON);
    return;
  }
  GBS_StartTimerProc(&tmr,SEC,Close);
}
}

void Auto()
{
    if(time_on_on)
{
  if(real_time.sec++>=60)real_time.min++;
  if(real_time.sec>=time_on_sec+1&&real_time.min>=time_on_min)
  {
    is_call=CALL_AUTO;
    GBS_SendMessage(MMI_CEPID,KEY_DOWN,GREEN_BUTTON);
    return;
  }
  if(is_call==CALL_IN)GBS_StartTimerProc(&tmr,SEC,Auto);
}
}
