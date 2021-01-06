#include "..\inc\swilib.h"

int mx=60;
int my=60;
int alt_state;
int freeze_time;
GBSTMR missedt;
int me;
extern const unsigned int font2;
extern const char COLORfont2[4];

void redraw_data()
{
  DrawImg(mx, my, (int)"0:\\zbin\\miosd\\0.png");
  WSHDR *ws=AllocWS(64);
  me=GetMissedEventCount(1);
  wsprintf(ws, "%t: %d", "вызовы", me);
  DrawString(ws,mx+3,my+3,mx+Get_WS_width(ws,font2)+3,my+GetFontYSIZE(font2)+3,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  me=GetMissedEventCount(2);
  wsprintf(ws, "%t: %d", "сообшения", me);
  DrawString(ws,mx+3,my+13,mx+Get_WS_width(ws,font2)+3,my+GetFontYSIZE(font2)+13,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  me=GetMissedEventCount(3);
  wsprintf(ws, "%t: %d", "разное", me);
  DrawString(ws,mx+3,my+23,mx+Get_WS_width(ws,font2)+3,my+GetFontYSIZE(font2)+23,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  me=GetMissedEventCount(4);
  FreeWS(ws);
}

void start_timerize(void);

void check_it_again()
{
  if(GetMissedEventCount(0)>0) start_timerize();
}


void process_missed()
{
  if(freeze_time)
  {
    freeze_time--;
    redraw_data();
    GBS_StartTimerProc(&missedt, 5, process_missed);
  }
  else
  if((mx>64)&&(alt_state))
  {
    mx=mx-2;
    if(mx<64) 
    {
      freeze_time=100;
      alt_state=0;
    }
    redraw_data();
    GBS_StartTimerProc(&missedt, 5, process_missed);
  }
  else
  {
    mx=135;
    RefreshGUI();
    GBS_StartTimerProc(&missedt, 60*216, check_it_again);
  }
}

void start_timerize()
{
  alt_state=1;
  process_missed();
}

