#include "..\inc\swilib.h"

int mx=243;
int my=0;
int alt_state;
int freeze_time;
GBSTMR missedt;
int me;
/*
IMGHDR screen2={0,0,8,""};

void DrwImg3(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void DoScreen2()
{
    int ScrH=ScreenH();
    int ScrW=ScreenW();
    char *ms=RamScreenBuffer();
    screen2.w=ScrW;
    screen2.h=ScrH;
    screen2.bitmap=malloc(ScrW*ScrH*2);
    memcpy(screen2.bitmap, ms, ScrW*ScrH*2);
}

*/
void redraw_data()
{
//  DrwImg3(&screen2, 0, 0, NULL, NULL);
  DrawImg(mx, my, (int)"4:\\zbin\\miosd\\img9.png");
  WSHDR *ws=AllocWS(64);
  me=GetMissedEventCount(1);
#ifdef EVILFOX
  wsprintf(ws, "Calls: %d", me);
#else
  wsprintf(ws, "%t: %d", "вызовы", me);
#endif
  DrawString(ws,mx+5,my+5,mx+Get_WS_width(ws,9)+5,my+GetFontYSIZE(9)+5,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  me=GetMissedEventCount(2);
#ifdef EVILFOX
  wsprintf(ws, "SMS: %d", me);
#else
  wsprintf(ws, "%t: %d", "сообшения", me);
#endif
  DrawString(ws,mx+5,my+23,mx+Get_WS_width(ws,9)+5,my+GetFontYSIZE(9)+23,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  me=GetMissedEventCount(3);
#ifdef EVILFOX
  wsprintf(ws, "Other: %d", me);
#else
  wsprintf(ws, "%t: %d", "разное", me);
#endif
  DrawString(ws,mx+5,my+41,mx+Get_WS_width(ws,9)+3,my+GetFontYSIZE(9)+41,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
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
  if((mx>100)&&(alt_state))
  {
    mx=mx-2;
    if(mx<100) 
    {
      freeze_time=100;
      alt_state=0;
    }
    redraw_data();
    GBS_StartTimerProc(&missedt, 5, process_missed);
  }
  else
/*  if(mx<245)
  {
    mx=mx+2;
    redraw_data();
    GBS_StartTimerProc(&missedt, 5, process_missed);
  }
  else*/
  {
    mx=243;
//    mfree(screen2.bitmap);
    if(!IsIdleUiOnTop())
    RefreshGUI();
    GBS_StartTimerProc(&missedt, 60*216, check_it_again);
  }
}

void start_timerize()
{
//  DoScreen2();
  alt_state=1;
  process_missed();
}


