#include "..\inc\swilib.h"
extern int main_clock;
GBSTMR clocktmr;


void EngadeClock()
{
  if(IsIdleUiOnTop())
  {
    WSHDR *ws=AllocWS(64);
    TTime time;
    GetDateTime(NULL, &time);
    wsprintf(ws, "%02d:%02d:%02d", time.hour, time.min, time.sec);  
    void *canvasdata = BuildCanvas();
    DrawCanvas(canvasdata,128-Get_WS_width(ws,11),162,130,162+GetFontYSIZE(11)+3,1);
    DrawString(ws,130-Get_WS_width(ws,11),162,130,162+GetFontYSIZE(11)+3,11,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    GBS_StartTimerProc(&clocktmr, 216, EngadeClock);
  }
  else
    main_clock=0;
}


