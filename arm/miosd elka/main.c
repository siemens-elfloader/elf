#include "..\inc\swilib.h"
//#include "..\inc\cfg_items.h"
#ifdef EVILFOX
#else
#include "conf_loader.h"
#endif
//#include "IdleLinks.h"
#include "gprs_write.h"
#include "string_works.h"
#include "missed_events.h"
#include "language.h"
#ifdef EVILFOX
#include "clock.h"
int main_clock;
#endif

#ifdef EVILFOX
#define BUFSIZE 5000
#else
#define BUFSIZE 10000
#endif

#ifdef NATICQ
#ifdef EVILFOX
#else
extern const int use_plugin;
#endif
int naticq_plugin;
char naticq_time[16];
char naticq_ping[16]="none";
#endif

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

CSM_DESC icsmd;
int ker_state;

int r_s=20;
int r_m;
int r_h;
//int r_d;


int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

unsigned short maincsm_name_body[140];
const int minus11=-11;
int MAINCSM_ID;
int first_con;
int key_mode;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

int pos;
int phase;
int pos_main_x;
int pos_main_y;
int lock_keys;
GBSTMR mytmr;
int pos_link_x;
int pos_link_y;
int pos_msg_x;
int pos_msg_y;
char chinfo[32];
char start_g[32];
char start_g2[32];

//=================weather
char temp[32];
#ifdef EVILFOX
char vejsh[32];
#endif
char temp2[32];
char vejsh2[32];
char weather_time[32];
#ifdef EVILFOX
char s_icon1[32];
#else
extern const char city_name[64];
extern const unsigned int TID;
char pressure[64];
char pressure2[64];
char wind[64];
#endif
int engade_weather;
//================weather

IMGHDR screen={0,0,8,""};

void DrwImg2(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void DoScreen()
{
    int ScrH=ScreenH();
    int ScrW=ScreenW();
    char *ms=RamScreenBuffer();
    screen.w=ScrW;
    screen.h=ScrH;
    screen.bitmap=malloc(ScrW*ScrH*2);
    memcpy(screen.bitmap, ms, ScrW*ScrH*2);
}

int app_pos=1;
int pos_link2_x;
int pos_link2_y;

void DoShowIt()
{
  switch(phase)
  {
case 1:
  {
    if(key_mode==1)
    {
    if(pos_main_x<0)
    {
      pos_main_x++;
    }
    else
      phase=2;
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
    if(key_mode==2)
    {
    if(pos_main_x>112)
    {
      pos_main_x--;
    }
    else
      phase=2;
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
  }
  break;
case 2:
  {
    if(key_mode==1)
    {
    if(pos_link_x<20)
    {
      pos_link_x++;
      DirectRedrawGUI();
    }
    else
    {
      DirectRedrawGUI();
      if(pos==5)
      {
        pos_msg_y=pos_link_y-34; //elka
        pos_link2_y=pos_msg_y+24;
        pos_link2_x=pos_msg_x-12+(app_pos*20);
        phase=7;
      }
      else
      phase=3;
    }
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
    if(key_mode==2)
    {
    if(pos_link_x>102)
    {
      pos_link_x--;
      DirectRedrawGUI();
    }
    else
    {
      DirectRedrawGUI();
      if(pos==5)
      {
        pos_msg_y=pos_link_y-34; //elka
        pos_link2_y=pos_msg_y+24;
        pos_link2_x=pos_msg_x-12+(app_pos*20);
        phase=7;
      }
      else
      phase=3;
    }
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
  }
  break;
case 3:
  {
    if(pos==5)
    {
      pos_msg_y=pos_link_y-34; //elak
    }
    else
    pos_msg_y=pos_link_y-56; //elak
    lock_keys=1;
    DirectRedrawGUI();
  }
  break;
case 4:
  {
    if(key_mode==1)
    {
    if(pos_link_x>10)
    {
      pos_link_x--;
    }
    else
    {
      pos_link_y=pos_main_y-12+(pos*20);
      phase=2;
    }
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
    if(key_mode==2)
    {
    if(pos_link_x<112)
    {
      pos_link_x++;
    }
    else
    {
      pos_link_y=pos_main_y-12+(pos*20);
      phase=2;
    }
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
  }
  break;
case 5:
  {
    if(key_mode==1)
    {
    if(pos_link_x>10)
      pos_link_x--;
    else
      phase=6;
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
    if(key_mode==2)
    {
    if(pos_link_x<112)
      pos_link_x++;
    else
      phase=6;
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
  }
  break;
case 6:
  {
    if(key_mode==1)
    {
    if(pos_main_x>-20)
    {
      pos_main_x--;
      DirectRedrawGUI();
      GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
    else
      CloseCSM(MAINCSM_ID);
    }
    if(key_mode==2)
    {
    if(pos_main_x<132)
    {
      pos_main_x++;
      DirectRedrawGUI();
      GBS_StartTimerProc(&mytmr, 5, DoShowIt);
    }
    else
      CloseCSM(MAINCSM_ID);
    }
  }
  break;
case 7:
  {
    if(pos_link2_y>(pos_msg_y+14))
    {
      pos_link2_y--;
    }
    else
      phase=3;
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
  }
  break;
case 8:
  {
    {
    if(pos_link2_y<pos_msg_y+24)
    {
      pos_link2_y++;
    }
    else
    {
      phase=7;
      pos_link2_x=pos_msg_x-12+(app_pos*20);
    }
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
  }
  }
  break;
  }
}

#ifdef EVILFOX
void DrawWeatherLog()
{
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "Weather: Ventspils");
  DrawString(ws,pos_msg_x+5,pos_msg_y+8,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+8,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  if(engade_weather)
  {
    wsprintf(ws, "On: %s", weather_time);
    DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    wsprintf(ws, temp2);
    DrawString(ws,pos_msg_x+5,pos_msg_y+53,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+53,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    wsprintf(ws, vejsh2);
    DrawString(ws,pos_msg_x+5,pos_msg_y+71,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+71,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    wsprintf(ws, s_icon1);
    DrawString(ws,pos_msg_x+5,pos_msg_y+89,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+89,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  else
  {
    wsprintf(ws, "No Data Yet");
    DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  FreeWS(ws);
}
#else
void DrawWeatherLog()
{
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "[%t: %t]", LG_WET, city_name);
  DrawString(ws,pos_msg_x+5,pos_msg_y+8,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+8,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  if(engade_weather)
  {
    wsprintf(ws, "On: %s", weather_time);
    DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    ascii2ws(ws, temp2);
    DrawString(ws,pos_msg_x+5,pos_msg_y+53,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+53,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    ascii2ws(ws, vejsh2);
    //wsprintf(ws, vejsh2);
    DrawString(ws,pos_msg_x+5,pos_msg_y+71,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+71,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    ascii2ws(ws, pressure2);
   // wsprintf(ws, pressure2);
    DrawString(ws,pos_msg_x+5,pos_msg_y+89,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+89,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  else
  {
    wsprintf(ws, "No Data Yet");
    DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  FreeWS(ws);
}
#endif

int battery;

void DrawBatteryLog()
{
  battery = *RamCap();
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "[%t]", LG_BATI);
  DrawString(ws,pos_msg_x+5,pos_msg_y+8,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+8,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%t: %d%", LG_BCAP, battery);
  DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  if(GetAccessoryType()==13) wsprintf(ws, "%t: On", LG_BCON); else wsprintf(ws, "%t: Off", LG_BCON);
  DrawString(ws,pos_msg_x+5,pos_msg_y+53,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+53,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  wsprintf(ws, "%t:", LG_CLCH);
  DrawString(ws,pos_msg_x+5,pos_msg_y+71,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+71,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  wsprintf(ws, chinfo);
  DrawString(ws,pos_msg_x+30,pos_msg_y+89,pos_msg_x+Get_WS_width(ws,9)+30,pos_msg_y+GetFontYSIZE(9)+89,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

#pragma swi_number=0x41
__swi __arm char GetProvider(WSHDR *ws, int zero); //for provider info
int monthc;
char month[5];

void get_month()
{
  TDate date;
  GetDateTime(&date, NULL);
  if(date.month==1) strcpy(month, "jan");
  if(date.month==2) strcpy(month, "feb");
  if(date.month==3) strcpy(month, "mar");
  if(date.month==4) strcpy(month, "apr");
  if(date.month==5) strcpy(month, "may");
  if(date.month==6) strcpy(month, "jun");
  if(date.month==7) strcpy(month, "jul");
  if(date.month==8) strcpy(month, "aug");
  if(date.month==9) strcpy(month, "sep");
  if(date.month==10) strcpy(month, "oct");
  if(date.month==11) strcpy(month, "nov");
  if(date.month==12) strcpy(month, "dec");
  monthc=date.month;
}

void DrawSystemLog()
{
  //ttttttt
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "[%t]", LG_SYSI);
  DrawString(ws,pos_msg_x+5,pos_msg_y+8,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+8,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  TTime time;
  TDate date;
  GetDateTime(&date, &time);
  if(monthc!=date.month) get_month();
  wsprintf(ws, "%02d%s, %02d:%02d:%02d", date.day, month, time.hour, time.min, time.sec);
  DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  GetProvider(ws,0);
  DrawString(ws,pos_msg_x+5,pos_msg_y+53,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+53,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  wsprintf(ws, "%t: %02d:%02d:%02d", LG_SRUN, r_h, r_m, r_s);
  DrawString(ws,pos_msg_x+5,pos_msg_y+71,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+71,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%t: %dKb", LG_SRAM, ram);
  DrawString(ws,pos_msg_x+5,pos_msg_y+89,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+89,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}
#ifdef NATICQ
void DrawNaticqLog()
{
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "[Naticq plugin]");
  DrawString(ws,pos_msg_x+3,pos_msg_y+3,pos_msg_x+Get_WS_width(ws,9)+3,pos_msg_y+GetFontYSIZE(9)+3,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  if(!naticq_plugin)
  {
  wsprintf(ws, "Naticq not running or wrong version");
  DrawString(ws,pos_msg_x+3,pos_msg_y+25,pos_msg_x+80,pos_msg_y+50+25,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  else
  {
    wsprintf(ws, "Online: %s", naticq_time);
    DrawString(ws,pos_msg_x+3,pos_msg_y+25,pos_msg_x+Get_WS_width(ws,9)+3,pos_msg_y+GetFontYSIZE(9)+25,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    wsprintf(ws, "Ping: %s", naticq_ping);
    DrawString(ws,pos_msg_x+3,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+3,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
 // DrawString(ws,pos_msg_x+3,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,11)+3,pos_msg_y+GetFontYSIZE(11)+35,11,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
 // wsprintf(ws, "Runtime: %02d:%02d:%02d", r_h, r_m, r_s);
 // DrawString(ws,pos_msg_x+3,pos_msg_y+45,pos_msg_x+Get_WS_width(ws,11)+3,pos_msg_y+GetFontYSIZE(11)+45,11,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
 // wsprintf(ws,"FreeRam: %dKb", ram);
 // DrawString(ws,pos_msg_x+3,pos_msg_y+55,pos_msg_x+Get_WS_width(ws,11)+3,pos_msg_y+GetFontYSIZE(11)+55,11,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}
#endif

int hmm;
int ggg;
int trafiks;
int start_traffic;
GBSTMR mytmr2;

void reboot_ref()
{
  DirectRedrawGUI();
}

int ffq;
char gpinfo[32];
int isfile;
extern int result3;
int switch_gprs_info;
int do_st=3;

void DrawGPRSLog()
{
  WSHDR *ws=AllocWS(64);
  if(IsGPRSConnected())
  {
    RefreshGPRSTraffic();
    int *traf = GetGPRSTrafficPointer();
    hmm=*traf-ggg;
#ifdef Evilfox
    wsprintf(ws,start_g2);
#else
    ascii2ws(ws, start_g2);
#endif
    DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    if(ffq) 
    {
      hmm=0;
      ffq=0;
    }
    wsprintf(ws, "%t: %dB/s", LG_GSPE, hmm);
    DrawString(ws,pos_msg_x+5,pos_msg_y+53,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+53,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    ggg=*traf;
    trafiks=(*traf-start_traffic)/1024;
    wsprintf(ws, "%t: %dKb", LG_GSES, trafiks);
    DrawString(ws,pos_msg_x+5,pos_msg_y+71,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+71,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    if(!do_st) 
    {
      switch_gprs_info=(!switch_gprs_info);
      do_st=3;
    }
    else
      do_st--;
    if(!switch_gprs_info)
    {
      if(isfile)
      wsprintf(ws, "%t: %sKb", LG_GLAS, gpinfo);
      else
        wsprintf(ws, "%t: %s", LG_GLAS, gpinfo);
    }
    else
      wsprintf(ws, "%t: %dKb", LG_GTOT, result3);
      DrawString(ws,pos_msg_x+5,pos_msg_y+89,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+89,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));    
  }
  else
  {
    wsprintf(ws, "%t ", LG_GPOF);
    DrawString(ws,pos_msg_x+5,pos_msg_y+35,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+35,9,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  wsprintf(ws, "[%t]", LG_GINF);
  DrawString(ws,pos_msg_x+5,pos_msg_y+8,pos_msg_x+Get_WS_width(ws,9)+5,pos_msg_y+GetFontYSIZE(9)+8,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

#ifdef EVILFOX
#else
extern const char link1_name[64];
extern const char link2_name[64];
extern const char link3_name[64];
extern const char link1[64];
extern const char link2[64];
extern const char link3[64];
#endif

void DrawAppLog()
{
  WSHDR *ws=AllocWS(64);
  switch(app_pos)
  {
  case 1:
    {
#ifdef EVILFOX
    wsprintf(ws, "Naticq");
#else
    wsprintf(ws, link1_name);
#endif
    DrawString(ws,pos_link2_x-7,pos_link2_y-24,pos_link2_x+Get_WS_width(ws,9)-7,pos_link2_y+GetFontYSIZE(9)-24,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    }
    break;
  case 2:
   // WSHDR *ws=AllocWS(64);
#ifdef EVILFOX
    wsprintf(ws, "Ballet");
#else
    wsprintf(ws, link2_name);
#endif
    DrawString(ws,pos_link2_x-17,pos_link2_y-20,pos_link2_x+Get_WS_width(ws,9)-17,pos_link2_y+GetFontYSIZE(9)-20,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    break;
  case 3:
  //  WSHDR *ws=AllocWS(64);
#ifdef EVILFOX
    wsprintf(ws, "SieJC");
#else
    wsprintf(ws, link3_name);
#endif
    DrawString(ws,pos_link2_x-17,pos_link2_y-20,pos_link2_x+Get_WS_width(ws,9)-17,pos_link2_y+GetFontYSIZE(9)-20,9,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    break;
  }
}



void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  DrwImg2(&screen, 0, 0, NULL, NULL);
  void *canvasdata = BuildCanvas();
  switch(phase)
  {
  case 1:
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif
    break;
  case 2:
    DrawImg(pos_link_x, pos_link_y, (int)"4:\\zbin\\miosd\\img2.png");
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif   
    break;
  case 3:
    if(pos==5)
    {
      DrawImg(pos_link_x, pos_link_y, (int)"4:\\zbin\\miosd\\img2.png");
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif
      DrawImg(pos_link2_x, pos_link2_y, (int)"4:\\zbin\\miosd\\img6.png");
      if(app_pos==1)
        DrawImg(pos_link2_x-10, pos_link2_y-24, (int)"4:\\zbin\\miosd\\img7.png");
      else
        DrawImg(pos_link2_x-20, pos_link2_y-24, (int)"4:\\zbin\\miosd\\img7.png");
      DrawAppLog();
      DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img4.png"); 
    }
    else
    {
      DrawImg(pos_link_x, pos_link_y, (int)"4:\\zbin\\miosd\\img2.png");
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
      DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
      DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif 
      DrawImg(pos_msg_x, pos_msg_y, (int)"4:\\zbin\\miosd\\img3.png");
    }
    switch(pos)
    {
#ifdef NATICQ
    case 0:
      DrawNaticqLog();
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
#endif
    case 1:
      DrawWeatherLog();
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 2:
      DrawBatteryLog();
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 3:
      DrawGPRSLog();
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 4:
      DrawSystemLog();
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 5: 
      switch(app_pos)
      {
      case 1:
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app3.png");
        GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
        break;
      case 2:
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app3.png"); 
        GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
        break;
      case 3:
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img5.png");
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app3.png");
        GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
        break;
      }
      break;
    }
    break;
  case 4:
    DrawImg(pos_link_x, pos_link_y, (int)"4:\\zbin\\miosd\\img2.png");
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif   
    break;
  case 5:
    DrawImg(pos_link_x, pos_link_y, (int)"4:\\zbin\\miosd\\img2.png");
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif  
    break;
  case 6:
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif
    break;
  case 7:
  case 8:
    DrawImg(pos_link_x, pos_link_y, (int)"4:\\zbin\\miosd\\img2.png");
#ifdef NATICQ
#ifdef EVILFOX
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#else
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"4:\\zbin\\miosd\\img8.png");
#endif
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#else
    DrawImg(pos_main_x, pos_main_y, (int)"4:\\zbin\\miosd\\img1.png");
#endif 
    DrawImg(pos_link2_x, pos_link2_y, (int)"4:\\zbin\\miosd\\img6.png"); 
    DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img4.png"); 
    switch(app_pos)
      {
      case 1:
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app3.png"); 
        break;
      case 2:
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app3.png"); 
        break;
      case 3:
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\img5.png");
        DrawImg(pos_msg_x, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+20, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+40, pos_msg_y+24, (int)"4:\\zbin\\miosd\\app3.png");
        break;
      }
    break;
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  data->gui.state=1;
//  pos=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  ker_state=0;
  mfree(screen.bitmap);
  // Тут можно освободить выделяемую память
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  CloseCSM(MAINCSM_ID);
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void create_connect(void);

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if(lock_keys)
  {
    DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {          
    switch(msg->gbsmsg->submess)
    {
    case 0x35:
      if(pos==1)
      {
        ffq=1;
        GBS_DelTimer(&mytmr2);
      engade_weather=0;
      SUBPROC((void *)create_connect);
      DirectRedrawGUI();
      }
/*      if(pos==3)
      {
        switch_gprs_info=(!switch_gprs_info);
        DirectRedrawGUI();
      }*/
      break;
      case RIGHT_SOFT:
      if(key_mode==1) goto set1;
      else goto set2;
      case LEFT_BUTTON:
        if((pos==5)&&(app_pos>1))
        {
          app_pos--;
          lock_keys=0;
          phase=8;
          DoShowIt();
       //   DirectRedrawGUI();
        }
        else
        {
        set1:
          ffq=1;
          GBS_DelTimer(&mytmr2);
          if(key_mode==1)
          {
      lock_keys=0;
      phase=5;
      DoShowIt();
          }
        }
      break;
      case RIGHT_BUTTON:
        if(pos==5)
        {
          app_pos++;
          if(app_pos==4) app_pos--;
          else
          {
            lock_keys=0;
            phase=8;
            DoShowIt();
     //       DirectRedrawGUI();
          }
        }
        else
        {
        set2:
          ffq=1;
          GBS_DelTimer(&mytmr2);
          if(key_mode==2)
          {
      lock_keys=0;
      phase=5;
      DoShowIt();
          }
        }
      break;
    case ENTER_BUTTON:
      if(pos==5)
      {
        WSHDR *elfname=AllocWS(256);
        switch(app_pos)
        {
        case 1:
          app_pos=1;
#ifdef EVILFOX
          wsprintf(elfname,(char*)"4:\\zbin\\naticq\\naticq.elf");
#else
          wsprintf(elfname, link1);
#endif
          ExecuteFile(elfname,NULL,NULL);
          FreeWS(elfname);
          return(1);
//          break;
        case 2:
          app_pos=1;
#ifdef EVILFOX
          wsprintf(elfname,(char*)"4:\\Zbin\\balletmini\\BalletMini.elf");
#else
          wsprintf(elfname, link2);
#endif
          ExecuteFile(elfname,NULL,NULL);
          FreeWS(elfname);
          return(1);
//          break;
        case 3:
          app_pos=1;
#ifdef EVILFOX
          wsprintf(elfname,(char*)"4:\\Zbin\\siejc\\siejc.elf");
#else
          wsprintf(elfname, link3);
#endif
          ExecuteFile(elfname,NULL,NULL);
          FreeWS(elfname);
          return(1);
//          break;
        }
      }
      break;
    case DOWN_BUTTON:
      {
        ffq=1;
        GBS_DelTimer(&mytmr2);
        pos++;
#ifdef NATICQ
#ifdef EVILFOX
        if (pos==6) pos=0;
#else
        if(use_plugin)
        {
        if (pos==6) pos=0;
        }
        else
        {
          if (pos==6) pos=1;
        }
#endif
#else
        if (pos==6) pos=1;
#endif
        lock_keys=0;
        phase=4;
        DoShowIt();
      }
        break;
    case UP_BUTTON:
       {
         ffq=1;
         GBS_DelTimer(&mytmr2);
          pos--;
#ifdef NATICQ
#ifdef EVILFOX
          if (pos==-1) pos=5;
#else
          if(use_plugin)
          {
          if (pos==-1) pos=5;
          }
          else
          {
            if (pos==0) pos=5;
          }
#endif
#else
          if (pos==0) pos=5;
#endif
          lock_keys=0;
          phase=4;
          DoShowIt();
       }
        break;        
    }
  }
  }
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

extern void kill_data(void *p,void (*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

// Канвас для основного GUI
const RECT Canvas={0,0,0,0};

// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)

#pragma inline
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose(CSM_RAM *csm)
{
  //SUBPROC((void *)ElfKiller);
}

// Обработчик событий главного CSM
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
   if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  } 
  return(1); 
}

// Инициализация структуры MAINCSM
const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

// Функция, которая устанавливает название этого CSM для X-Task.
void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MIOSD");
}


void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int con;
#ifdef EVILFOX
//=================================================================weather
int sock;
int connect_state=0;
char buf[BUFSIZE+1];
int pbuf=0;
int traf=0;
GBSTMR mytmr3;

void start_again(void);

void create_connect(void)
{
  SOCK_ADDR sa;
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
      sa.ip=htonl(IP_ADDR(194,8,25,206));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
    }
    else
    {
      closesocket(sock);
      GBS_StartTimerProc(&mytmr3, 2160, start_again);
    }
  }
  else
  GBS_StartTimerProc(&mytmr3, 2160, start_again);
}

void start_again()
{
  if(IsGPRSConnected())
  {
  SUBPROC((void *)create_connect);
  }
  else
  GBS_StartTimerProc(&mytmr3, 2160, start_again);
}

void send_req(void)
{
  char *req_buf=malloc(500);
  sprintf(req_buf,"GET /wap/weatherr.php?city=ventspils HTTP/1.1\n"
            "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: www.118.lv\n"
                    "Connection: Close\n"
                      "\n"
                        );
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
  mfree(req_buf);
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
    connect_state=0;
  }
}

void get_answer(void)
{
  int i=pbuf;
  if (i==BUFSIZE)
    end_socket();
  else
  {
    traf+=i=recv(sock,buf+i,BUFSIZE-i,0);
    if (i>=0)
    {
      pbuf+=i;
    }
    else
    {
      end_socket();
    }
  }
}

int Parsing()
{
  char p1[]="<p>Paslaik: ";
  char p2[]="<br/>";
  char *s,*s1,*s2;
  int len, i ,j;
  if((s1=strstr(buf,p1))>0)
  {
    s1+=strlen(p1);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1;
      s=malloc(len+1);
      strncpy(s,s1,len);
      s[len]='\0';
      i=0;
      j=0;
      while(s[i]!=',')
      {
        temp[i]=s[i];
        i++;
      }
      temp[i]='\0';
      sprintf(temp2, "%s: %s", LG_TEMP, temp);
      i++;
      while(i<len)
      {
        vejsh[j]=s[i];
        j++;
        i++;
      }
      vejsh[j]='\0';
      sprintf(vejsh2, "%s: %s", LG_WIND, vejsh);
      mfree(s);

  char p1_1[]="http://www.118.lv/images/icons/weather/";
  char p2_1[]=".gif";
  char *s_icon;
  if((s1=strstr(buf,p1_1))>0)
  {
    s1+=strlen(p1_1);
    if((s2=strstr(s1,p2_1))>0)
    {
      len=s2-s1;
      s_icon=malloc(len+1);
      strncpy(s_icon,s1,len);
      s_icon[len]='\0';
//      strcpy(icon_name, s_icon);
      int k=0;
      int l=0;
      int y=0;
      while(k<len)
      {
        if(s_icon[k]=='_')
          l=k;
        k++;
      }
      if(l>0)
      l++;
      while(l<len)
      {
        s_icon1[y]=s_icon[l];
        l++;
        y++;
      }
      s_icon1[y]='\0';
      TTime time;
      TDate date;
      GetDateTime(&date, &time);
      sprintf(weather_time, "%02d-%02d at %02d:%02d", date.month, date.day, time.hour, time.min);
      engade_weather=1;
      DirectRedrawGUI();
      return 1;
    }
  }
    }
  }
  
  return 0;
}
//=================================================================weather
#else
//=================================================================weather
int sock;
int connect_state;
char buf[BUFSIZE+1];
int pbuf;
int traf;
GBSTMR mytmr3;

void start_again(void);

void create_connect(void)
{
  SOCK_ADDR sa;
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
      sa.ip=htonl(IP_ADDR(212,48,138,20));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
    }
    else
    {
      closesocket(sock);
      GBS_StartTimerProc(&mytmr3, 2160, start_again);
    }
  }
  else
  GBS_StartTimerProc(&mytmr3, 2160, start_again);
}

void start_again()
{
  if(IsGPRSConnected())
  {
  SUBPROC((void *)create_connect);
  }
  else
  GBS_StartTimerProc(&mytmr3, 2160, start_again);
}

char req_buf[256];

void send_req(void)
{
      sprintf(req_buf,"GET /wap2/towns/%i.wap2"
         " HTTP/1.0\r\nHost: wap.gismeteo.ru\r\n\r\n",TID);  
 
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
}

void get_answer(void)
{
  int i=pbuf;
  if (i==65535)
    end_socket();
  else
  {
    i=recv(sock,buf+i,65535-i,0);
    if (i>=0)
    {
      pbuf+=i;
    }
    else
    {
      end_socket();
    }
  }
}

char tempz[10];

void Parsing()
{  
    char *fcstr;
    int i;  
      
    fcstr=strstr(buf,"</table>");
      
    //????????kartinka
    fcstr=strstr(fcstr,"/images/")+strlen ("/images/");
/*    for (i=0;fcstr[i]!='.'&&(i<strlen (fcstr));i++);
      strncpy(weath.Pic, fcstr, i+1);
    weath.Pic[i]=0; 
    strcat(weath.Pic, ".png");*/
    
    //???????????temperatura
    fcstr=strstr(fcstr,"<b>")+strlen ("<b>");
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(temp, fcstr, i+1);
      temp[i]=0;
      i=0;
      while(temp[i]!='.')
      {
        tempz[i]=temp[i];
        i++;
      }
      tempz[i]='\0';
      sprintf(temp2, "%s: %s",LG_TEMP, tempz);
      
    //????????davlenie
    fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
    fcstr=strstr(fcstr,">")+18;
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(pressure, fcstr, i+1);
    pressure[i]='\0';  
    utf82win(pressure,(const char *)pressure);
    sprintf(pressure2, "%s: %s", LG_PRES, pressure);
    
    //?????veter
    fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
    fcstr=strstr(fcstr,">")+12;
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(wind, fcstr, i+1);
    wind[i]='\0'; 
    utf82win(wind,(const char *)wind);
    sprintf(vejsh2, "%s: %s", LG_WIND, wind);
    
    TTime time;
      TDate date;
      GetDateTime(&date, &time);
      sprintf(weather_time, "%02d-%02d at %02d:%02d", date.month, date.day, time.hour, time.min);
      engade_weather=1;
      DirectRedrawGUI();
    
    //?????????vlazhnostj
/*    fcstr=strstr(fcstr,"<tr><td")+strlen ("<tr><td");
    fcstr=strstr(fcstr,">")+20;
    for (i=0;fcstr[i]!='<'&&(i<strlen (fcstr));i++);
      strncpy(weath.Rewlet, fcstr, i+1);
    weath.Rewlet[i]='\n';  */  
    
    //SUBPROC((void *)log_data, buf);
}
//=================================================================weather
#endif
int charge_m;
int charge_s;
GBSTMR charger;

void charger_c()
{
  charge_s++;
  if (charge_s==60)
  {
    charge_s=0;
    charge_m++;
  }
  GBS_StartTimerProc(&charger, 216, charger_c);
}

int g_min;
int g_sec;
int g_hour;
GBSTMR gipi;

void write_log(int zzz)
{
  volatile int hFile;
      unsigned int io_error = 0;
      unsigned int ul;
      FSTATS stat;
      GetFileStats("4:\\zbin\\miosd\\miosd2.file",&stat,&ul);
      hFile = fopen("4:\\zbin\\miosd\\miosd2.file",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
      if(hFile!=-1)
      {
        char *writer=malloc(32);
        sprintf(writer, "%d", zzz);
        fwrite(hFile, writer, strlen(writer), &io_error);
        fclose(hFile, &io_error);
      }
}

int rewriter;

void Count_GPRS()
{
  g_sec++;
  if (g_sec==60)
  {
    g_sec=0;
    g_min++;
  }
  if(g_min==60)
  {
    g_min=0;
    g_hour++;
  }
  int r=g_min;
  while(r>0)
    r=r-2;
  if((r==0)&&(g_min!=0)&&(rewriter!=g_min)) 
  {
    int *trafik2 = GetGPRSTrafficPointer();
    int trafiks2=(*trafik2-start_traffic)/1024;
    SUBPROC((void *)write_log,trafiks2);   //latest fix
   // write_log(trafiks2);
    rewriter=g_min;
  }
//  sprintf(start_g2, "%s(%dm)", start_g, g_min);
#ifdef EVILFOX
  sprintf(start_g2, "Active: %02d:%02d:%02d", g_hour, g_min, g_sec);
#else
  sprintf(start_g2, "вр. сес.: %02d:%02d:%02d", g_hour, g_min, g_sec);
#endif
  GBS_StartTimerProc(&gipi, 216, Count_GPRS);
}

#ifdef NATICQ
#define IPC_RECIEVE_MSG 55
const char ipc_my_name[]="MioSD";
#endif
extern GBSTMR missedt;
int rem_mis;
  

int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  int csm_result;
  csm_result=old_icsm_onMessage(data,msg);
  
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
 //     void RereadSettings(void);
 //     RereadSettings();
#ifdef EVILFOX
#else
      InitConfig();
#endif
      ShowMSG(1,(int)"MIOSD 1.5 config updated!");
    }
  }
  //=========================================weather
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data1==sock)
    {
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
          SUBPROC((void *)send_req);        
        }
        else
          {
          SUBPROC((void *)create_connect); 
          }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
          SUBPROC((void *)get_answer);
        }
        else
        {
          SUBPROC((void *)create_connect);
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
        if (connect_state) SUBPROC((void *)end_socket);
        connect_state=3;
        Parsing();
        sock=-1;
        GBS_StartTimerProc(&mytmr3, 12960*60, start_again);
        break;
      }
    }
  }
  //==========================================weather
#ifdef NATICQ
  //==========================================ipc naticq
  if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
	if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
	{
	  switch (msg->submess)
	  {
	  case IPC_RECIEVE_MSG:
            {
              char test[64];
              int len=strlen(ipc->data);
              sprintf(test,"%s",ipc->data);
              test[len]='\0';
              if(test[0]!='0')
              {
                if(test[0]=='1') naticq_plugin=1;
                if(test[0]=='2') 
                {
                  naticq_plugin=0;
                  sprintf(naticq_ping, "none");
                }
              }
              if(naticq_plugin)
              {
                if(test[1]!='0')
                {
                  if(test[1]=='1');
                  {
                    strncpy(naticq_time,test+2,8);
                    naticq_time[8]='\0';
                  }
                  if(test[1]=='2')
                  {
                    strncpy(naticq_time,test+2,8);
                    naticq_time[8]='\0';
                    strncpy(naticq_ping,test+10,6);
                    naticq_ping[6]='\0';
                  }
                }
              }
            }
	    break;
          }
        }
      }
    }
  //==========================================ipc naticq
#endif
#ifdef EVILFOX
  if((!main_clock)&&(IsIdleUiOnTop()))
  {
    EngadeClock();
    main_clock=1;
  }
#endif
  if(rem_mis!=GetMissedEventCount(0))
  {
    if(GetMissedEventCount(0)<rem_mis) rem_mis=GetMissedEventCount(0);
    else
    {
      rem_mis=GetMissedEventCount(0);
      GBS_StartTimerProc(&missedt, 216*3, start_timerize);
    }
  }
  if((IsGPRSConnected())&&(first_con))
  {
  int *trafik = GetGPRSTrafficPointer();
  start_traffic=*trafik;
/*  TTime time;
  TDate date;
  GetDateTime(&date, &time);
  sprintf(start_g, "%02d:%02d %02d-%02d", time.hour, time.min, date.month, date.day);*/
  g_min=0;
  g_sec=0;
  g_hour=0;
  GBS_DelTimer(&gipi);
  Count_GPRS();
  first_con=0;
  }
  if(!IsGPRSConnected()) first_con=1;
  if(GetAccessoryType()==13) 
  {
    if(!con) 
    {
      charge_s=0;
      charge_m=0;
      charger_c();
      con=1;
    }
    sprintf(chinfo, "Charging(%dmin)", charge_m);
  }
  else 
  {
    if(con)
    {
      GBS_DelTimer(&charger);
      TTime time;
      TDate date;
      GetDateTime(&date, &time);
      sprintf(chinfo, "%02d:%02d, %02d-%02d", time.hour, time.min, date.month, date.day);
      volatile int hFile;
      unsigned int io_error = 0;
      unsigned int ul;
      FSTATS stat;
      GetFileStats("4:\\zbin\\miosd\\miosd.file",&stat,&ul);
      hFile = fopen("4:\\zbin\\miosd\\miosd.file",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error);
      if(hFile!=-1)
      {
        fwrite(hFile, chinfo, strlen(chinfo), &io_error);
        fclose(hFile, &io_error);
      }
      con=0;
    }
  }
  return(csm_result);
}  

/*
int my_keyhook(int key, int m)
{
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==KEY_DOWN)&&(!IsScreenSaver()))
  {
     if (key==RIGHT_BUTTON)||(key==LEFT_BUTTON)) 
       {
       doit:
         LockSched();
         char dummy[sizeof(MAIN_CSM)];
         UpdateCSMname();
         MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,2);
         UnlockSched();
         lock_keys=0;
         phase=1;
        // pos=1;
         if((key==RIGHT_BUTTON)||((key==0x0D)&&(LONG_PRESS)&&(!ker_state)))
         {
           ker_state=1;
           pos_main_x=-20;
           pos_main_y=50;
           pos_link_x=0;
         //  pos_link_y=pos_main_y+8;
           pos_link_y=pos_main_y-12+(pos*20);
           pos_msg_x=29;
           key_mode=1;
         }
         if(key==LEFT_BUTTON)
         {
           ker_state=1;
           pos_main_x=132;
           pos_main_y=50;
           pos_link_x=112;
          // pos_link_y=pos_main_y+8;
           pos_link_y=pos_main_y-12+(pos*20);
           pos_msg_x=6;
           key_mode=2;
         }
         DoScreen();
         DoShowIt();
       }
  }
  else
    if((key==0x0D)&&(m==LONG_PRESS)&&(!ker_state)&&(!IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])))
      goto doit;
  
  return 0;
}*/

int mode_enter;
int mode;
#ifdef EVILFOX
int CALL_BUTTON=1;
#else
extern const unsigned int CALL_BUTTON;
extern const unsigned int CALL_BUTTON2;
#endif

void Execute()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,2);
  UnlockSched();
  lock_keys=0;
  phase=1;
  ker_state=1;
  pos_main_x=-20;
  pos_main_y=50;
  pos_link_x=0;
  pos_link_y=pos_main_y-12+(pos*20);
  pos_msg_x=29;
  key_mode=1;
  DoScreen();
  DoShowIt();
}

extern int alt_state;

int my_keyhook(int submsg, int msg)
{
  if((submsg==62)&&(IsIdleUiOnTop())&&(IsUnlocked())) Execute();
#ifdef EVILFOX
#else
  if(submsg==CALL_BUTTON2) {
 //   DoScreen2();
    alt_state=1;
    process_missed();
  }
#endif
  if (submsg!=CALL_BUTTON) return(0);
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
    if (mode==1)mode=0;
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
    if(mode==0)
    {
      if (IsUnlocked()) Execute();
    }
    mode=1;
    break;
  }
return(2); 
}

void check_battery()
{
  volatile int hFile_ex;
  unsigned int io_error_ex = 0;
  hFile_ex = fopen("4:\\zbin\\miosd\\miosd.file",A_ReadOnly + A_BIN,P_READ, &io_error_ex);
  if(hFile_ex!=-1)
  {
     fclose(hFile_ex, &io_error_ex);
     int f;
    int fsize;
    FSTATS stat;
    unsigned int ul;
    GetFileStats("4:\\zbin\\miosd\\miosd.file",&stat,&ul);
    if(stat.size>0)
    {
      f=fopen("4:\\zbin\\miosd\\miosd.file",A_ReadOnly+A_BIN,P_READ,&ul);
      fsize=stat.size;
      char *p=malloc(fsize);
      p[fread(f,p,fsize,&ul)];
      fclose(f,&ul);
      strcpy(chinfo, p);
      chinfo[fsize]='\0';
      mfree(p);
    }
  }
  else
    sprintf(chinfo, "Never");
}

void check_gprs()
{
  volatile int hFile_ex;
  unsigned int io_error_ex = 0;
  hFile_ex = fopen("4:\\zbin\\miosd\\miosd2.file",A_ReadOnly + A_BIN,P_READ, &io_error_ex);
  if(hFile_ex!=-1)
  {
     fclose(hFile_ex, &io_error_ex);
     int f;
    int fsize;
    FSTATS stat;
    unsigned int ul;
    GetFileStats("4:\\zbin\\miosd\\miosd2.file",&stat,&ul);
    if(stat.size>0)
    {
      f=fopen("4:\\zbin\\miosd\\miosd2.file",A_ReadOnly+A_BIN,P_READ,&ul);
      fsize=stat.size;
      char *p=malloc(fsize);
      p[fread(f,p,fsize,&ul)];
      fclose(f,&ul);
      strcpy(gpinfo, p);
      gpinfo[fsize]='\0';
      mfree(p);
      isfile=1;
      write_total();
    }
  }
  else
    sprintf(gpinfo, "Unknown");
}

GBSTMR rs_tmr;

void runtime_count()
{
  r_s++;
  if(r_s==60) 
  {
    r_s=0;
    r_m++;
  }
  if(r_m==60)
  {
    r_m=0;
    r_h++;
  }
/*  if(r_h==24)
  {
    r_h=0;
    r_d++;
  }*/
  GBS_StartTimerProc(&rs_tmr, 216, runtime_count);
}
// Основная процедура. Она первой получает управление при старте эльфа.
int main(void)
{
  LockSched();
#ifdef EVILFOX
#else
  InitConfig();
#endif
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  old_icsm_onClose=icsmd.onClose;
  icsmd.onClose=MyIDLECSM_onClose;  
  icsm->constr=&icsmd;  
  
  AddKeybMsgHook((void *)my_keyhook);

  UnlockSched();
  check_battery();
  check_gprs();
  start_again();
  runtime_count();
  first_con=1;
  pos=1;
#ifdef EVILFOX
#else
  ShowMSG(1,(int)"MIOSD running (c)Evilfox");
#endif
  
  return 0;
}
