#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "gprs_write.h"
#include "string_works.h"
#include "missed_events.h"
#include "language.h"


extern const int use_plugin;
extern const char COLORfont1[4];
extern const char COLORfont2[4];
extern const unsigned int font1;
extern const unsigned int font2;
int naticq_plugin;
char naticq_time[16];
char naticq_ping[16]="none";


extern const int engade_mis;
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

extern const char linksound[64];
GBSTMR rs_tmr;


CSM_DESC icsmd;
int ker_state;

int r_s=20;
int r_m;
int r_h;
int mode_enter;
int mode;
int pos=1;
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
char start_g2[32];
int monthc;
char month[10];
int hmm;
int ggg;
int trafiks;
int start_traffic;
GBSTMR mytmr2;
int ffq;
char gpinfo[32];
int isfile;
extern int result3;
int switch_gprs_info;
int do_st=3;
extern const char link1_name[64];
extern const char link2_name[64];
extern const char link3_name[64];
extern const char link1[64];
extern const char link2[64];
extern const char link3[64];
int con;
int charge_m;
int charge_s;
GBSTMR charger;
int g_min;
int g_sec;
int g_hour;
GBSTMR gipi;
#define IPC_RECIEVE_MSG 55
const char ipc_my_name[]="MioSD";
extern GBSTMR missedt;
int rem_mis;
extern int alt_state;
extern const unsigned int CALL_BUTTON;
extern const unsigned int CALL_BUTTON2;




int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

unsigned short maincsm_name_body[140];
const int minus11=-11;
int MAINCSM_ID;
int first_con=1;
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


IMGHDR screen={0,0,8,""};

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
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
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
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
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
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
        pos_msg_y=pos_link_y-34;
        pos_link2_y=pos_msg_y+24;
        pos_link2_x=pos_msg_x-12+(app_pos*20);
        phase=7;
      }
      else
      phase=3;
    }
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
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
        pos_msg_y=pos_link_y-34;
        pos_link2_y=pos_msg_y+24;
        pos_link2_x=pos_msg_x-12+(app_pos*20);
        phase=7;
      }
      else
      phase=3;
    }
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
    }
  }
  break;
case 3:
  {
    pos_msg_y=pos_link_y-34;
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
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
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
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
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
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
    }
    if(key_mode==2)
    {
    if(pos_link_x<112)
      pos_link_x++;
    else
      phase=6;
    DirectRedrawGUI();
    GBS_StartTimerProc(&mytmr, 3, DoShowIt);
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
      GBS_StartTimerProc(&mytmr, 3, DoShowIt);
    }
    else
      CloseCSM(MAINCSM_ID);
    }
    if(key_mode==2)
    {
    if(pos_main_x<240)
    {
      pos_main_x++;
      DirectRedrawGUI();
      GBS_StartTimerProc(&mytmr, 3, DoShowIt);
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



void DrawBatteryLog()
{
  int battery = *RamCap();
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "[%t]", LG_BATI);
  DrawString(ws,pos_msg_x+113,pos_msg_y+13,pos_msg_x+Get_WS_width(ws,font1)+113,pos_msg_y+GetFontYSIZE(font1)+13,font1,0,COLORfont1,GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%t: %d%", LG_BCAP, battery);
  DrawString(ws,pos_msg_x+113,pos_msg_y+28,pos_msg_x+Get_WS_width(ws,font2)+113,pos_msg_y+GetFontYSIZE(font2)+28,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  if(GetAccessoryType()==13) wsprintf(ws, "%t: On", LG_BCON); else wsprintf(ws, "%t: Off", LG_BCON);
  DrawString(ws,pos_msg_x+113,pos_msg_y+38,pos_msg_x+Get_WS_width(ws,font2)+113,pos_msg_y+GetFontYSIZE(font2)+38,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  wsprintf(ws, "%t:", LG_CLCH);
  DrawString(ws,pos_msg_x+113,pos_msg_y+48,pos_msg_x+Get_WS_width(ws,font2)+113,pos_msg_y+GetFontYSIZE(font2)+48,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  wsprintf(ws, chinfo);
  DrawString(ws,pos_msg_x+1118,pos_msg_y+58,pos_msg_x+Get_WS_width(ws,font2)+1118,pos_msg_y+GetFontYSIZE(font2)+58,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}

#pragma swi_number=0x41
__swi __arm char GetProvider(WSHDR *ws, int zero);


void get_month()
{
  TDate date;
  GetDateTime(&date, NULL);
  if(date.month==1) strcpy(month, " января");
  if(date.month==2) strcpy(month, " февраля");
  if(date.month==3) strcpy(month, " марта");
  if(date.month==4) strcpy(month, " апреля");
  if(date.month==5) strcpy(month, " мая");
  if(date.month==6) strcpy(month, " июня");
  if(date.month==7) strcpy(month, " июля");
  if(date.month==8) strcpy(month, " августа");
  if(date.month==9) strcpy(month, " сентября");
  if(date.month==10) strcpy(month, " октября");
  if(date.month==11) strcpy(month, " ноября");
  if(date.month==12) strcpy(month, " декабря");
  monthc=date.month;
}

void DrawSystemLog()
{
  int ram = GetFreeRamAvail();
  ram=ram/1024;
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "[%t]", LG_SYSI);
  DrawString(ws,pos_msg_x+16,pos_msg_y+73,pos_msg_x+Get_WS_width(ws,font1)+16,pos_msg_y+GetFontYSIZE(font1)+73,font1,0,COLORfont1,GetPaletteAdrByColorIndex(23));
  TTime time;
  TDate date;
  GetDateTime(&date, &time);
  if(monthc!=date.month) get_month();
  RAMNET *net_data;
  net_data=RamNet();
  wsprintf(ws,"%t %d db",LG_NET, net_data->power); 
  DrawString(ws,pos_msg_x+16,pos_msg_y+88,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+88,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
   
  int freemem0 = GetFreeFlexSpace(0, 0)/1024;
  int freemem4 = GetFreeFlexSpace(4, 0)/1024; 
  wsprintf(ws,"0:= %d Kb",freemem0);
  DrawString(ws,pos_msg_x+16,pos_msg_y+98,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+98,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"4:= %d Kb",freemem4);
  DrawString(ws,pos_msg_x+16,pos_msg_y+108,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+108,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%t: %dKb", LG_SRAM, ram);
  DrawString(ws,pos_msg_x+16,pos_msg_y+118,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+118,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
  
}
void DrawNaticqLog()
{
  WSHDR *ws=AllocWS(64);
  wsprintf(ws, "[Naticq plugin]");
  DrawString(ws,pos_msg_x+3,pos_msg_y+3,pos_msg_x+Get_WS_width(ws,font2)+3,pos_msg_y+GetFontYSIZE(font2)+3,font2,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  if(!naticq_plugin)
  {
  wsprintf(ws, "Naticq not running or wrong version");
  DrawString(ws,pos_msg_x+3,pos_msg_y+25,pos_msg_x+80,pos_msg_y+50+25,font2,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  else
  {
    wsprintf(ws, "Online: %s", naticq_time);
    DrawString(ws,pos_msg_x+3,pos_msg_y+20,pos_msg_x+Get_WS_width(ws,font2)+3,pos_msg_y+GetFontYSIZE(font2)+25,font2,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
    wsprintf(ws, "Ping: %s", naticq_ping);
    DrawString(ws,pos_msg_x+3,pos_msg_y+30,pos_msg_x+Get_WS_width(ws,font2)+3,pos_msg_y+GetFontYSIZE(font2)+35,font2,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(23));
  }
  FreeWS(ws);
}





void reboot_ref()
{
  DirectRedrawGUI();
}





void DrawGPRSLog()
{
  WSHDR *ws=AllocWS(64);
  if(IsGPRSConnected())
  {
    RefreshGPRSTraffic();
    int *traf = GetGPRSTrafficPointer();
    hmm=*traf-ggg;
    ascii2ws(ws, start_g2);
    DrawString(ws,pos_msg_x+16,pos_msg_y+28,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+28,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
    if(ffq) 
    {
      hmm=0;
      ffq=0;
    }
    wsprintf(ws, "%t: %dB/s", LG_GSPE, hmm);
    DrawString(ws,pos_msg_x+16,pos_msg_y+38,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+38,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
    ggg=*traf;
    trafiks=(*traf-start_traffic)/1024;
    wsprintf(ws, "%t: %dKb", LG_GSES, trafiks);
    DrawString(ws,pos_msg_x+16,pos_msg_y+48,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+48,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
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
      DrawString(ws,pos_msg_x+16,pos_msg_y+58,pos_msg_x+Get_WS_width(ws,font2)+16,pos_msg_y+GetFontYSIZE(font2)+58,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));    
  }
  else
  {
    wsprintf(ws, "%t ", LG_GPOF);
    DrawString(ws,pos_msg_x+16,pos_msg_y+28,pos_msg_x+Get_WS_width(ws, font2)+16,pos_msg_y+GetFontYSIZE(font2)+28,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
  }
  wsprintf(ws, "[%t]", LG_GINF);
  DrawString(ws,pos_msg_x+16,pos_msg_y+13,pos_msg_x+Get_WS_width(ws, font1)+16,pos_msg_y+GetFontYSIZE(font1)+13,font1,0,COLORfont1,GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
}





void DrawAppLog()
{
  WSHDR *ws=AllocWS(64);
  switch(app_pos)
  {
  case 1:
    {
    wsprintf(ws, link1_name);
    DrawString(ws,pos_link2_x+3,pos_link2_y-14,pos_link2_x+Get_WS_width(ws,font2)+3,pos_link2_y+GetFontYSIZE(font2)-14,font2,0, COLORfont2,GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    }
    break;
  case 2:
    wsprintf(ws, link2_name);
    DrawString(ws,pos_link2_x-7,pos_link2_y-14,pos_link2_x+Get_WS_width(ws,font2)-7,pos_link2_y+GetFontYSIZE(font2)-14,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    break;
  case 3:
    wsprintf(ws, link3_name);
    DrawString(ws,pos_link2_x-7,pos_link2_y-14,pos_link2_x+Get_WS_width(ws,font2)-7,pos_link2_y+GetFontYSIZE(font2)-14,font2,0,COLORfont2,GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    break;
  }
}



void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  DrwImg(&screen, 0, 0, NULL, NULL);
  void *canvasdata = BuildCanvas();
  switch(phase)
  {
  case 1:
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
    DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
    break;
  case 2:
    DrawImg(pos_link_x, pos_link_y, (int)"0:\\zbin\\miosd\\img2.png");
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
    DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
   break;
  case 3:
    if(pos==5)
    {
      DrawImg(pos_link_x, pos_link_y, (int)"0:\\zbin\\miosd\\img2.png");
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
    DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
    DrawImg(pos_link2_x+10, pos_link2_y, (int)"0:\\zbin\\miosd\\img6.png");
    if(app_pos==1)DrawImg(pos_link2_x, pos_link2_y-17, (int)"0:\\zbin\\miosd\\img7.png");
    else DrawImg(pos_link2_x-10, pos_link2_y-17, (int)"0:\\zbin\\miosd\\img7.png");
    DrawAppLog();
    DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img4.png"); 
    }
    else
    {
      DrawImg(pos_link_x, pos_link_y, (int)"0:\\zbin\\miosd\\img2.png");
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
      DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
      DrawImg(pos_msg_x+10, pos_msg_y, (int)"0:\\zbin\\miosd\\img3.png");
    }
    switch(pos)
    {
    case 0:
      DrawNaticqLog();
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 1:
      DrawImg(pos_msg_x+10, pos_msg_y+10, (int)"0:\\zbin\\miosd\\1.png");
      DrawBatteryLog();
      DrawSystemLog();
      DrawGPRSLog();
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 2:
      DrawImg(pos_msg_x+10, pos_msg_y, (int)"0:\\zbin\\miosd\\2.png");
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 3:
      DrawImg(pos_msg_x+10, pos_msg_y, (int)"0:\\zbin\\miosd\\3.png");
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 4:
      DrawImg(pos_msg_x+10, pos_msg_y, (int)"0:\\zbin\\miosd\\4.png");
      GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
      break;
    case 5: 
      switch(app_pos)
      {
      case 1:
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app3.png");
        GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
        break;
      case 2:
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app3.png"); 
        GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
        break;
      case 3:
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img5.png");
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app3.png");
        GBS_StartTimerProc(&mytmr2, 216, reboot_ref);
        break;
      }
      break;
    }
    break;
  case 4:
    DrawImg(pos_link_x, pos_link_y, (int)"0:\\zbin\\miosd\\img2.png");
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
    DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
    break;
  case 5:
    DrawImg(pos_link_x, pos_link_y, (int)"0:\\zbin\\miosd\\img2.png");
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
    DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
    break;
  case 6:
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
    DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
    break;
  case 7:
  case 8:
    DrawImg(pos_link_x, pos_link_y, (int)"0:\\zbin\\miosd\\img2.png");
    if(use_plugin)
    DrawImg(pos_main_x, pos_main_y-20, (int)"0:\\zbin\\miosd\\img8.png");
    DrawImg(pos_main_x, pos_main_y, (int)"0:\\zbin\\miosd\\img1.png");
    DrawImg(pos_link2_x+10, pos_link2_y, (int)"0:\\zbin\\miosd\\img6.png"); 
    DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img4.png"); 
    switch(app_pos)
      {
      case 1:
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app3.png"); 
        break;
      case 2:
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img5.png"); 
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app3.png"); 
        break;
      case 3:
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\img5.png");
        DrawImg(pos_msg_x+10, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app1.png"); 
        DrawImg(pos_msg_x+30, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app2.png"); 
        DrawImg(pos_msg_x+50, pos_msg_y+24, (int)"0:\\zbin\\miosd\\app3.png");
        break;
      }
    break;
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  GBS_DelTimer(&rs_tmr);
  mfree(screen.bitmap);
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

      DirectRedrawGUI();
      }
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
          wsprintf(elfname, link1);
          ExecuteFile(elfname,NULL,NULL);
          FreeWS(elfname);
          return(1);
        case 2:
          app_pos=1;
          wsprintf(elfname, link2);
          ExecuteFile(elfname,NULL,NULL);
          FreeWS(elfname);
          return(1);
        case 3:
          app_pos=1;
          wsprintf(elfname, link3);
          ExecuteFile(elfname,NULL,NULL);
          FreeWS(elfname);
          return(1);
        }
      }
      break;
    case DOWN_BUTTON:
      {
        ffq=1;
        GBS_DelTimer(&mytmr2);
        pos++;
        if(use_plugin)
        {
        if (pos==6) pos=0;
        }
        else
        {
          if (pos==6) pos=1;
        }
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
          if(use_plugin)
          {
          if (pos==-1) pos=5;
          }
          else
          {
            if (pos==0) pos=5;
          }
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


void charger_c()
{
  charge_s++;
  if(charge_s==60){charge_s=0;charge_m++;}
  GBS_StartTimerProc(&charger, 216, charger_c);
}




void write_log(int number)
{
      volatile int hFile = fopen("0:\\zbin\\miosd\\miosd2.file",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, 0);
      if(hFile!=-1)
      {
        char writer[32];
        sprintf(writer, "%d", number);
        fwrite(hFile, writer, strlen(writer), 0);
        fclose(hFile, 0);
      }
}


void Count_GPRS()
{
  int rewriter=0;
  g_sec++;
  if (g_sec==60){g_sec=0;g_min++;}
  if(g_min==60){g_min=0;g_hour++;}
  int r=g_min;
  while(r>0)r-=2;
  if((r==0)&&(g_min!=0)&&(rewriter!=g_min)) 
  {
    int *trafik2 = GetGPRSTrafficPointer();
    int trafiks2=(*trafik2-start_traffic)/1024;
    SUBPROC((void *)write_log,trafiks2);   //latest fix
    rewriter=g_min;
  }
  sprintf(start_g2, "вр. сес.: %02d:%02d:%02d", g_hour, g_min, g_sec);
  GBS_StartTimerProc(&gipi, 216, Count_GPRS);
}



int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  int csm_result;
  csm_result=old_icsm_onMessage(data,msg);
  
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      ShowMSG(1,(int)"MIOSD_mod update");
    }
  }

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
  if(rem_mis!=GetMissedEventCount(0))
  {
    if(GetMissedEventCount(0)<rem_mis) rem_mis=GetMissedEventCount(0);
    else
    {
      rem_mis=GetMissedEventCount(0);
      if(engade_mis) GBS_StartTimerProc(&missedt, 216*3, start_timerize);
    }
  }
  if((IsGPRSConnected())&&(first_con))
  {
  int *trafik = GetGPRSTrafficPointer();
  start_traffic=*trafik;

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
      FSTATS stat;
      GetFileStats("0:\\zbin\\miosd\\miosd.file",&stat,0);
      volatile int hFile = fopen("0:\\zbin\\miosd\\miosd.file",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, 0);
      if(hFile!=-1)
      {
        fwrite(hFile, chinfo, strlen(chinfo), 0);
        fclose(hFile, 0);
      }
      con=0;
    }
  }
  return(csm_result);
}  





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
  pos_msg_x=21;
  key_mode=1;
  DoScreen();
  DoShowIt();
}



int my_keyhook(int submsg, int msg)
{
  if((submsg==9)&&(IsIdleUiOnTop())&&(IsUnlocked()))Execute();
  if(submsg==CALL_BUTTON2) 
  {
    alt_state=1;
    process_missed();
  }
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
    if (!mode_enter)
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
    if (!mode&&IsUnlocked()&&(!MAINCSM_ID)&&(!IsIdleUiOnTop())) Execute();
    mode=1;
    break;
  }
return(2); 
}

void check_battery()
{
  volatile int hFile_ex = fopen("0:\\zbin\\miosd\\miosd.file",A_ReadOnly + A_BIN,P_READ, 0);
  if(hFile_ex!=-1)
  {
   fclose(hFile_ex, 0);
    FSTATS stat;
    GetFileStats("0:\\zbin\\miosd\\miosd.file",&stat,0);
    if(stat.size>0)
    {
      int f=fopen("0:\\zbin\\miosd\\miosd.file",A_ReadOnly+A_BIN,P_READ,0);
      char *p=malloc(stat.size);
      p[fread(f,p,stat.size,0)];
      fclose(f,0);
      strcpy(chinfo, p);
      chinfo[stat.size]='\0';
      mfree(p);
    }
  }
  else
    sprintf(chinfo, "Never");
}

void check_gprs()
{
  volatile int hFile_ex = fopen("0:\\zbin\\miosd\\miosd2.file",A_ReadOnly + A_BIN,P_READ, 0);
  if(hFile_ex!=-1)
  {
   fclose(hFile_ex, 0);
    FSTATS stat;
    GetFileStats("0:\\zbin\\miosd\\miosd2.file",&stat,0);
    if(stat.size>0)
    {
      int f=fopen("0:\\zbin\\miosd\\miosd2.file",A_ReadOnly+A_BIN,P_READ,0);
      char *p=malloc(stat.size);
      p[fread(f,p,stat.size,0)];
      fclose(f,0);
      strcpy(gpinfo, p);
      gpinfo[stat.size]='\0';
      mfree(p);
      isfile=1;
      write_total();
    }
  }
  else
    sprintf(gpinfo, "Unknown");
}



void runtime_count()
{
  r_s++;
 if(r_s>=60){r_s=0;r_m++;}
 if(r_m>=60){r_m=0;r_h++;}
 GBS_StartTimerProc(&rs_tmr, 216, runtime_count);
}
// Основная процедура. Она первой получает управление при старте эльфа.
int main()
{
  LockSched();
  InitConfig();
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
  runtime_count();
  return 0;
}
