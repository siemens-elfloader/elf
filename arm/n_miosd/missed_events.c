#include "..\inc\swilib.h"

int mx=135;
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
 // DrwImg3(&screen2, 0, 0, NULL, NULL);
  DrawImg(mx, my, (int)"0:\\zbin\\miosd\\img9.png");
  WSHDR *ws=AllocWS(64);
  me=GetMissedEventCount(1);
#ifdef EVILFOX
  wsprintf(ws, "Calls: %d", me);
#else
  wsprintf(ws, "%t: %d", "������", me);
#endif
  DrawString(ws,mx+3,my+3,mx+Get_WS_width(ws,11)+3,my+GetFontYSIZE(11)+3,11,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  me=GetMissedEventCount(2);
#ifdef EVILFOX
  wsprintf(ws, "SMS: %d", me);
#else
  wsprintf(ws, "%t: %d", "���������", me);
#endif
  DrawString(ws,mx+3,my+13,mx+Get_WS_width(ws,11)+3,my+GetFontYSIZE(11)+13,11,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  me=GetMissedEventCount(3);
#ifdef EVILFOX
  wsprintf(ws, "Other: %d", me);
#else
  wsprintf(ws, "%t: %d", "������", me);
#endif
  DrawString(ws,mx+3,my+23,mx+Get_WS_width(ws,11)+3,my+GetFontYSIZE(11)+23,11,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
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
/*  if(mx<137)
  {
    mx=mx+2;
    redraw_data();
    GBS_StartTimerProc(&missedt, 5, process_missed);
  }
  else*/
  {
    mx=135;
//    mfree(screen2.bitmap);
//    if(!IsIdleUiOnTop())
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


