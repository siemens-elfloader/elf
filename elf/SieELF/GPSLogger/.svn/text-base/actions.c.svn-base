#include "../inc/swilib.h"
#include "actions.h"

GBSTMR tmr_vibra;
volatile int Vibra_Count;
#define TMR_SECOND 216


extern const unsigned int VIBRA_POWER;
extern const unsigned int VIBRA_COUNT;

void _start_vibra()
{
  void _stop_vibra(void);
  SetVibration(VIBRA_POWER);
  GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,_stop_vibra);
}

void _stop_vibra(void)
{
  SetVibration(0);
  if (--Vibra_Count)
  {
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,_start_vibra);
  }
}

void Vibrate(int Req_Vibra_Count)
{
  if(Vibra_Count)return;
  Vibra_Count = Req_Vibra_Count;
  if (!IsCalling()) _start_vibra();
}

void DoAction(char action_letter)
{
  //char w[40];
  //sprintf(w, "Action=%u", action_letter);
  //ShowMSG(1,(int)w);
  switch(action_letter)
  {
  case 'v': Vibrate(VIBRA_COUNT);  break;
  }
}

//EOL,EOF
