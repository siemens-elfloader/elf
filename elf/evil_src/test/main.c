#include "../inc/swilib.h"

GBSTMR mytmr;
int top_gui;
char show_txt[128];

void Check()
{
  if(IsGuiOnTop(top_gui))
  {
    sprintf(show_txt, "java_id=%d", top_gui);
    ShowMSG(1,(int)show_txt); 
  }
  else
  {
    top_gui++;
    GBS_StartTimerProc(&mytmr, 5, Check);
  }
}

void main()       
{
  top_gui=0;
  GBS_StartTimerProc(&mytmr, 216*5, Check);
}                  

