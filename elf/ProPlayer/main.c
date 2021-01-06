#include "C:\ARM_ALL\inc\swilib.h"
#include "C:\ARM_ALL\inc\playsound.h"
#include "C:\ARM_ALL\inc\xtask_ipc.h"
#include "conf_loader.h"
#include "rect_patcher.h"
#include "filelist.h"
#include "play_list.h"
#include "lang.h"
#include "history.h"
#include "menu.h"
#include "main.h"
#include "print.h"  //========addon for png font by evilfox

//-----------------------------------Создали------------------------------------

/*
(c) VedaN, KIBER-DEMON, Eraser, EvilFox
*/

//-----------------------------------Учетные данные-----------------------------
//-----------------------------------Прочее-------------------------------------

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

extern const char Prozrachnost[4]={0,0,0,0};
const char ipc_xtask_name[]=IPC_XTASK_NAME;
const char ipc_my_name[32]="ProPlayer";
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
#define TIME_SECOND 216
IPC_REQ gipc;

//-----------------------------------Основное-----------------------------------

extern void kill_data(void *p, void (*func_p)(void *));
extern const char *successed_config_filename;
extern const char Player_folder[128];
char name[256];
extern int SONG_ALL;
extern int SONG_NUM_NOW;
extern const RECT name_pos;
extern const unsigned int name_font;
extern const char name_col[4];
extern const char frame_col[4];
extern const char round_frame_col[4];
extern const RECT gui_name_pos;
extern const unsigned int gui_name_font;
extern const char gui_name_col[4];
extern const char gui_frame_col[4];
extern const char gui_round_frame_col[4];
extern const unsigned int gui_sta_x;
extern const unsigned int gui_sta_y;
extern const unsigned int gui_sta_font;
extern const char gui_sta_col[4];
extern const char gui_sta_frame_col[4];
extern const unsigned int sk_font;
extern const char sk_col[4];
extern const unsigned int defau_scroll_speed;
extern const unsigned int scroll_wait_time;
extern const unsigned int auto_exit_time;
extern const int exit_type;
extern const unsigned int song_num_lst;
extern const char lst_song_col[4];
extern const char lst_this_song_col[4];
extern const char lst_song_frame_col[4];
extern const char lst_round_frame_col[4];
extern const unsigned int lst_song_x;
extern const unsigned int lst_song_y;
extern const unsigned int song_lst_w;
extern const unsigned int lst_song_font;
//-Конфиг
extern const unsigned int num_pos_x;
extern const unsigned int num_pos_y;
extern const unsigned int num_font;
extern const char num_col[4];
extern const char num_frame_col[4];
//Время-Конфиг
extern const int enable_clock;
extern const int enable_sec;
extern const unsigned int clock_font;
extern const unsigned int clock_x;
extern const unsigned int clock_y;
extern const char clock_col[4];
extern const char clock_frame_col[4];
//Громкость-Конфиг
extern const unsigned int vol_x;
extern const unsigned int vol_y;
extern const unsigned int vol_font;
extern const unsigned int def_vol;
extern const char vol_col[4];
extern const char vol_frame_col[4];
//Статус-Конфиг
extern const unsigned int sts_x;
extern const unsigned int sts_y;
extern const unsigned int sts_font;
extern const char sts_col[4];
extern const char sts_frame_col[4];
//Режим-Конфиг
extern const unsigned int mod_x;
extern const unsigned int mod_y;
extern const unsigned int mod_font;
extern const char mod_col[4];
extern const char mod_frame_col[4];
//Эквалайзер-Конфиг
extern const unsigned int eqs_x;
extern const unsigned int eqs_y;
extern const unsigned int eqs_font;
extern const char eqs_col[4];
extern const char eqs_frame_col[4];
//Прогрессбар-Конфиг
extern const unsigned int bar_x;
extern const unsigned int bar_y;
extern const unsigned int bar_x2;
extern const unsigned int bar_y2;
extern const char bar_col[4];
extern const char bar_frame_col[4];
//===================png font by evilfox====================
extern const char fontpath[64];
int font=1;
const int align=0;
extern const unsigned int space;
extern const int fullfont;
void *canvasdata;
extern const unsigned int idle_X;
extern const unsigned int idle_Y;
//===================end pngfont by evilfox=================

int CurentVolume=3;
int PLAY_ID=0xFFFF;
int RingOff=0;
int screenw;
int screenh;
int playhandle=0;
int play_flag=0;//0:stop, 1:play, 2:pause
int play_mode=0;//0:t2b, 1:b2t, 2:shuf
int play_equaliser=0;//0:Classical, 1:Club, 2:Dance, 3:Bass, 4:MegaBass, 5:Treble, 6:Party, 7:Pop, 8:Reggae, 9:Rock, 10:Soft
char procfile[128];
char song_name[128];
unsigned int sndVolume=6;
WSHDR *ws_song_name;
char *list_text;
GBSTMR mytmr;
int scroll_pos=0;
int is_idle_gui=0;
LIST_SONG_NAME *name_list;
int is_auto_exit_started=0;
int is_drawname_tmr=0;
int exit_time;
WSHDR *ws_exit_time;
char *ch_exit_time;
GBSTMR exit_d_tmr;

void Exit(void)
{
  //if(is_drawname_tmr) GBS_DelTimer( &mytmr );
  //if(is_auto_exit_started) GBS_DelTimer( &exit_d_tmr );
  if(playhandle) PlayMelody_StopPlayback(playhandle);
  CloseCSM(MAINCSM_ID);
}

void exit_switch(void)
{
  //GBS_DelTimer(&exit_tmr);
  if(exit_type)
  SwitchPhoneOff();
  else
  Exit();
}

void exit_time_draw_proc(void)
{
  if(is_auto_exit_started)
  {
  if(exit_type)
  sprintf(ch_exit_time,LNG_SWITCHOFF_TIME"%d:%d",exit_time/60,exit_time%60);
  else
  sprintf(ch_exit_time,LNG_EXIT_TIME"%d:%d",exit_time/60,exit_time%60);
  utf8_2ws(ws_exit_time,ch_exit_time,strlen(ch_exit_time));
  if(IsGuiOnTop(MAINGUI_ID))
  {
  //DrawRectangle(0,gui_sta_y+3*GetFontYSIZE(gui_sta_font),screenw,gui_sta_y+4*GetFontYSIZE(gui_sta_font)+1,0,gui_main_bg_col,gui_main_bg_col);
  DrawString(ws_exit_time,gui_sta_x,gui_sta_y+3*GetFontYSIZE(gui_sta_font),screenw,screenh,gui_sta_font,TEXT_OUTLINE,gui_sta_col,gui_sta_frame_col); 
  }
  if(exit_time==0)
  {
  is_auto_exit_started=0;
  exit_switch();
  }
  else
  {
  exit_time--;
  GBS_StartTimerProc(&exit_d_tmr,TIME_SECOND,exit_time_draw_proc);
  }
  }
}

void stop_auto_exit(void)
{
  if(is_auto_exit_started)
  {
  //GBS_DelTimer(&exit_tmr);
  is_auto_exit_started=0;
  exit_time=auto_exit_time*60;
  }
  else
  ShowMSG(0,(int)"Auto Exit have not started!");
}

void start_auto_exit(void)
{
  if(is_auto_exit_started==0)
  {
  is_auto_exit_started=1;
  //GBS_StartTimerProc(&exit_tmr,TIME_SECOND*60*auto_exit_time,exit);
  exit_time_draw_proc();
  }
  else
  ShowMSG(0,(int)"Auto Exit is already started!");
}

void Play(const char *fname)
{
  FSTATS fstats;
  unsigned int err;
  if (GetFileStats(fname,&fstats,&err)!=-1)
  {
  PLAYFILE_OPT _sfo1;
  WSHDR* sndPath=AllocWS(128);
  WSHDR* sndFName=AllocWS(128);
  char s[128];
  const char *p=strrchr(fname,'\\')+1;
  str_2ws(sndFName,p,128);
  strncpy(s,fname,p-fname);
  s[p-fname]='\0';
  str_2ws(sndPath,s,128);
  zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
  _sfo1.repeat_num=1;
  _sfo1.time_between_play=0;
  _sfo1.play_first=0;
  _sfo1.volume=sndVolume;
  #ifdef NEWSGOLD
  _sfo1.unk6=1;
  _sfo1.unk7=1;
  _sfo1.unk9=2;
  playhandle=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  #ifdef X75
  _sfo1.unk4=0x80000000;
  _sfo1.unk5=1;
  playhandle=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  _sfo1.unk5=1;
  playhandle=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
  #endif
  #endif
  FreeWS(sndPath);
  FreeWS(sndFName);
  }
  else ShowMSG(1,(int)"Can't find file!");
}

void VolumeMute()
{
  if (RingOff==0)
    {
      PlayMelody_ChangeVolume(PLAY_ID,0);
      RingOff=1;
      REDRAW();
    }
  else
    {
      PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
      RingOff=0;
      REDRAW();
    }
}

void soft_key(void)
{
  WSHDR *wsl = AllocWS(16);
  WSHDR *wsr = AllocWS(16);
  utf8_2ws(wsr,LNG_STOP,strlen(LNG_STOP));
  utf8_2ws(wsl,LNG_MENU,strlen(LNG_MENU));
  DrawString(wsr,screenw-Get_WS_width(wsr,sk_font)-4,screenh-GetFontYSIZE(sk_font)-2,screenw,screenh,sk_font,32,sk_col,GetPaletteAdrByColorIndex(23)); 
  DrawString(wsl,2,screenh-GetFontYSIZE(sk_font)-2,screenw,screenh,sk_font,32,sk_col,GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsr);
  FreeWS(wsl);
}

int getMaxChars(unsigned short *wsbody, int len, int font)
{
  int ii,width=0;
  for(ii=0;ii<len;ii++)
  {
  width+=GetSymbolWidth(wsbody[ii], font);
  if (width>=gui_name_pos.x2-gui_name_pos.x) break;
  }
  return ii;
}

/*int findmp3length(char *playy)
{
   #ifdef NEWSGOLD 
   return(GetWavLen(filename)); 
   #else
   TWavLen wl;
   zeromem(&wl, sizeof(wl));
   wl.type=0x2000;
   wl.wfilename=AllocWS(128);
   str_2ws(wl.wfilename,playy,128); 
   GetWavLen(&wl); 
   #endif 
   return (wl.length/1000);
}*/

void draw_song_list(void)
{
  WSHDR *ws=AllocWS(64);
  int c;
  int k=0;
  char ss[128];
  int j=SONG_NUM_NOW-song_num_lst/2;
  if(j<0)
  j=0;
  DrawRoundedFrame(lst_song_x,lst_song_y,lst_song_x+song_lst_w,lst_song_y+song_num_lst*GetFontYSIZE(lst_song_font)+4,0,0,0,lst_round_frame_col,Prozrachnost);
  for(;j<SONG_NUM_NOW+song_num_lst/2+song_num_lst%2;j++)
  {
  if(j>SONG_ALL)
  break;
  char *p;
  p=(name_list+j)->p_name;
  int i=0;
  int is_1st_utf8=0;
  while((*p!=0)&&(*p!='\n'))
  {
  c=*p;
  if(c>=' ')
  {
  if((is_1st_utf8==0)&&(c>0x80))
  {
  ss[i]=0x1F;
  i++;
  is_1st_utf8=1;
  }
  if (i<(sizeof(ss)-1)) ss[i]=c;
  i++;
  }
  p++;
  }
  ss[i-4]='\0';
  char *pp=strrchr(ss,'\\')+1;
  str_2ws(ws,pp,64);
  if(Get_WS_width(ws, lst_song_font)>song_lst_w)
  {
  *(pp+getMaxChars(ws->wsbody, song_lst_w, gui_name_font)-1)='\0';
  str_2ws(ws,pp,64);
  }
  if(j==SONG_NUM_NOW)
  DrawString(ws,lst_song_x+2,lst_song_y+k*GetFontYSIZE(gui_name_font),lst_song_x+song_lst_w,screenh,lst_song_font,TEXT_OUTLINE,lst_this_song_col,lst_song_frame_col); 
  else
  DrawString(ws,lst_song_x+2,lst_song_y+k*GetFontYSIZE(gui_name_font),lst_song_x+song_lst_w,screenh,lst_song_font,TEXT_OUTLINE,lst_song_col,lst_song_frame_col);
  k++;
  }
  FreeWS(ws);
}

void drawnameproc(void)
{
  if(IsGuiOnTop(MAINGUI_ID))
  {
  //WSHDR *ws_song_name=AllocWS(64);
  int font_h=GetFontYSIZE(gui_name_font);
  char bScroll=Get_WS_width(ws_song_name, gui_name_font)>=(gui_name_pos.x2-gui_name_pos.x);
  DrawRoundedFrame(gui_name_pos.x,gui_name_pos.y,gui_name_pos.x2,gui_name_pos.y2,0,0,0,gui_round_frame_col,Prozrachnost);
  if(bScroll && defau_scroll_speed)
  {
  int sc=getMaxChars(&ws_song_name->wsbody[scroll_pos+1], ws_song_name->wsbody[0]-scroll_pos, gui_name_font);
  WSHDR* txt = AllocWS(sc+1);
  txt->wsbody[0]=sc;
  for(int ii=1;ii<sc+1;ii++)
  txt->wsbody[ii]=ws_song_name->wsbody[ii+scroll_pos];
  DrawString(txt,gui_name_pos.x,(gui_name_pos.y2+gui_name_pos.y-font_h)/2,/*gui_name_pos.x2*/512,gui_name_pos.y2,gui_name_font,TEXT_ALIGNLEFT+TEXT_OUTLINE,gui_name_col,gui_frame_col); 
  scroll_pos++;
  int rest_len=0;
  int i;
  for (i=scroll_pos+1;i<ws_song_name->wsbody[0];i++)
  {
  rest_len+=GetSymbolWidth(ws_song_name->wsbody[i], gui_name_font);
  }
  //if(sc == 0)
  if (rest_len<=(gui_name_pos.x2-gui_name_pos.x-0x40))
  {
  scroll_pos = 0;
  }
  is_drawname_tmr=1;
  if(scroll_pos==1)
  GBS_StartTimerProc(&mytmr,scroll_wait_time,drawnameproc);
  else
  GBS_StartTimerProc(&mytmr,defau_scroll_speed,drawnameproc);
  FreeWS(txt);
  }
  else
  {
  is_drawname_tmr=0;
  scroll_pos = 0;
  DrawString(ws_song_name,gui_name_pos.x,(gui_name_pos.y2+gui_name_pos.y-font_h)/2,gui_name_pos.x2,gui_name_pos.y2,gui_name_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,gui_name_col,gui_frame_col); 
  }
  //FreeWS(ws_song_name);
  //REDRAW();
  }    
  else is_drawname_tmr=0;
}

void draw_name(void)
{
  const char *p_name=strrchr(procfile,'\\')+1;
  str_2ws(ws_song_name,p_name,64);
  drawnameproc();
}

void Clock()
{
  if (enable_clock)
 {
  void *canvasdata=BuildCanvas();
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  WSHDR *ws_clock = AllocWS(256);
  if (enable_sec)
  {
  wsprintf(ws_clock,"%i:%02i:%02i",time.hour,time.min,time.sec);
  DrawString(ws_clock,clock_x-8,clock_y,screenw,screenh,clock_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,clock_col,clock_frame_col);
  FreeWS(ws_clock);
  }
  else
  {
  wsprintf(ws_clock,"%i:%02i",time.hour,time.min);
  DrawString(ws_clock,clock_x,clock_y,screenw,screenh,clock_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,clock_col,clock_frame_col);
  FreeWS(ws_clock);
  }
  }
}

void Volume()
{
  char *vol=malloc(256);
  WSHDR *ws_vol=AllocWS(256);
  sprintf(vol,LNG_VOL": %d",sndVolume);
  utf8_2ws(ws_vol,vol,strlen(vol));
  DrawString(ws_vol,vol_x,vol_y,screenw,screenh,vol_font,TEXT_OUTLINE,vol_col,vol_frame_col); 
  mfree(vol);
  FreeWS(ws_vol);
}

char c_sts[16];
void Status()
{
  switch(play_flag)
  {
  case 0:
  sprintf(c_sts,LNG_STOP);
  break;
  case 1:
  sprintf(c_sts,LNG_PLAYING);
  break;
  case 2:
  sprintf(c_sts,LNG_PAUSE);
  break;
  }
  char *sts=malloc(256);
  WSHDR *ws_sts=AllocWS(256);
  sprintf(sts,LNG_STATUS": %s",c_sts);
  utf8_2ws(ws_sts,sts,strlen(sts));
  DrawString(ws_sts,sts_x,sts_y,screenw,screenh,sts_font,TEXT_OUTLINE,sts_col,sts_frame_col); 
  mfree(sts);
  FreeWS(ws_sts);
}

char c_mode[16];
void Mode()
{
  switch(play_mode)
  {
  case 0:
  sprintf(c_mode,LNG_MODE_T2B);
  break;
  case 1:
  sprintf(c_mode,LNG_MODE_B2T);
  break;
  case 2:
  sprintf(c_mode,LNG_MODE_SHUF);
  break;
  }
  char *mod=malloc(256);
  WSHDR *ws_mod=AllocWS(256);
  sprintf(mod,LNG_PLAYMODE": %s",c_mode);
  utf8_2ws(ws_mod,mod,strlen(mod));
  DrawString(ws_mod,mod_x,mod_y,screenw,screenh,mod_font,TEXT_OUTLINE,mod_col,mod_frame_col); 
  mfree(mod);
  FreeWS(ws_mod);
}

char c_equaliser[16];
void Equaliser()
{
  switch(play_equaliser)
  {
  case 0:
  sprintf(c_equaliser,LNG_EQUALISER_CLASSICAL);
  break;
  case 1:
  sprintf(c_equaliser,LNG_EQUALISER_CLUB);
  break;
  case 2:
  sprintf(c_equaliser,LNG_EQUALISER_DANCE);
  break;
  case 3:
  sprintf(c_equaliser,LNG_EQUALISER_BASS);
  break;
  case 4:
  sprintf(c_equaliser,LNG_EQUALISER_MEGABASS);
  break;
  case 5:
  sprintf(c_equaliser,LNG_EQUALISER_TREBLE);
  break;
  case 6:
  sprintf(c_equaliser,LNG_EQUALISER_PARTY);
  break;
  case 7:
  sprintf(c_equaliser,LNG_EQUALISER_POP);
  break;
  case 8:
  sprintf(c_equaliser,LNG_EQUALISER_REGGAE);
  break;
  case 9:
  sprintf(c_equaliser,LNG_EQUALISER_ROCK);
  break;
  case 10:
  sprintf(c_equaliser,LNG_EQUALISER_SOFT);
  break;
  }
  char *eqs=malloc(256);
  WSHDR *ws_eqs=AllocWS(256);
  sprintf(eqs,LNG_EQUALISER": %s",c_equaliser);
  utf8_2ws(ws_eqs,eqs,strlen(eqs));
  DrawString(ws_eqs,eqs_x,eqs_y,screenw,screenh,eqs_font,TEXT_OUTLINE,eqs_col,eqs_frame_col); 
  mfree(eqs);
  FreeWS(ws_eqs);
}

void NumTrek()
{
  char *num=malloc(256);
  WSHDR *ws_num=AllocWS(16);
  wsprintf(ws_num,"%d/%d", SONG_NUM_NOW+1, SONG_ALL+1);
  DrawString(ws_num,num_pos_x,num_pos_y,screenw,screenh,num_font,TEXT_OUTLINE,num_col,num_frame_col);
  mfree(num);
  FreeWS(ws_num);
}

void onRedraw(MAIN_GUI *data)
{
  sprintf(name,"%s%s",Player_folder,"\\background.png");
  DrawImg(0,0,(int)name);
  DrawRectangle(bar_x,bar_y,bar_x2,bar_y2,0,bar_col,bar_frame_col);
  soft_key();
  //drawnameproc();
  draw_name();
  WSHDR *ws_song_name=AllocWS(64);
  const char *p=strrchr(procfile,'\\')+1;
  str_2ws(ws_song_name,p,64);
  DrawRoundedFrame(gui_name_pos.x-1,gui_name_pos.y-1,gui_name_pos.x2+1,gui_name_pos.y2+3,0,0,0,GetPaletteAdrByColorIndex(7),GetPaletteAdrByColorIndex(23));
  DrawString(ws_song_name,gui_name_pos.x,gui_name_pos.y,gui_name_pos.x2,gui_name_pos.y2,gui_name_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,gui_name_col,gui_frame_col);            
  //str_2ws(ws_song_name,procfile,128);
  //if(is_auto_exit_started)
  //{
  //if(exit_type)
  //sprintf(sta,LNG_VOL": %d\n"LNG_STATUS": %s\n"LNG_PLAYMODE": %s\n"LNG_AUTO_SHUTDOWN, sndVolume, c_sta, c_mode);
  //else
  //sprintf(sta,LNG_VOL": %d\n"LNG_STATUS": %s\n"LNG_PLAYMODE": %s\n"LNG_AUTO_QUIT, sndVolume, c_sta, c_mode);
  //}
  //else
  Clock();
  Volume();
  Status();
  Mode();
  Equaliser();
  NumTrek();
  draw_song_list();
}

void Control(int type)
{
  //type 0:play, 1: Pause, 2:Resume, 3: Stop, 4:change vol
  switch(type)
  {
  case 0:
  if(playhandle&&(play_flag!=0)) PlayMelody_StopPlayback(playhandle);
  if(play_flag!=0)
  {
  Play(procfile);
  play_flag=1;
  }
  break;
  case 1:
  if(playhandle) PlayMelody_PausePlayback(playhandle);
  play_flag=2;
  break;
  case 2:
  if(playhandle) PlayMelody_ResumePlayBack(playhandle);
  play_flag=1;
  break;
  case 3:
  if(playhandle) PlayMelody_StopPlayback(playhandle);
  play_flag=0;
  break;
  case 4:
  if(playhandle) PlayMelody_ChangeVolume(playhandle,sndVolume);
  break;
  }
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
  {
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
  switch(msg->gbsmsg->submess)
  {
  case '*':
  VolumeMute();
  REDRAW();
  break;
  case '#':
  if (IsUnlocked()){KbdLock();}else{KbdUnlock();}
  REDRAW();
  break;
  case VOL_UP_BUTTON:
  play_next();
  REDRAW();
  break;
  case VOL_DOWN_BUTTON:
  play_prev();
  REDRAW();
  break;
  }
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
  int i=msg->gbsmsg->submess;
  //DirectRedrawGUI();
  switch(i)
  {
  case RIGHT_SOFT:
  Control(3);
  REDRAW();
  break;
  case LEFT_SOFT:
  ShowMainMenu();
  REDRAW();
  break;
  case ENTER_BUTTON:
  case '5':
  if(play_flag==0)
  {
  play_flag=1;
  Control(0);
  REDRAW();
  break;
  }
  if(play_flag==1)
  {
  Control(1);
  REDRAW();
  break;
  }
  if(play_flag==2) Control(2);
  REDRAW();
  break;
  case LEFT_BUTTON:
  case VOL_DOWN_BUTTON:
  case '4':
  if(sndVolume)
  {
  sndVolume--;
  Control(4);
  }
  REDRAW();
  break;
  case RIGHT_BUTTON:
  case VOL_UP_BUTTON:
  case '6':
  if(sndVolume!=5)
  {
  sndVolume++;
  Control(4);
  }
  REDRAW();
  break;
  case UP_BUTTON:
  case '2':
  play_prev();
  REDRAW();
  break;
  case DOWN_BUTTON:
  case '8':
  play_next();
  REDRAW();
  break;
  case '3':
  play_shuff();
  REDRAW();
  break;
  default: 
  REDRAW();
  break;
  }
  }
  return(0);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]=
{
  (void *)onRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};
/* ===========================removed by evilfox
void drawidlenameproc(void)
{
  if(is_idle_gui)
  {
    int font_h=GetFontYSIZE(gui_name_font);
    char bScroll=Get_WS_width(ws_song_name, name_font)>=(name_pos.x2-name_pos.x);
    DrawRoundedFrame(name_pos.x,name_pos.y,name_pos.x2,name_pos.y2,0,0,0,round_frame_col,GetPaletteAdrByColorIndex(23));
    if(bScroll && defau_scroll_speed)
    {
      int sc=getMaxChars(&ws_song_name->wsbody[scroll_pos+1], ws_song_name->wsbody[0]-scroll_pos, name_font);
      WSHDR* txt = AllocWS(sc+1);
      txt->wsbody[0]=sc;
      for(int ii=1;ii<sc+1;ii++)
        txt->wsbody[ii]=ws_song_name->wsbody[ii+scroll_pos];
      DrawString(txt,name_pos.x,(name_pos.y2+name_pos.y-font_h)/2,512,name_pos.y2,name_font,TEXT_ALIGNLEFT+TEXT_OUTLINE,name_col,frame_col); 
      scroll_pos++;
      int rest_len=0;
      int i;
      for (i=scroll_pos+1;i<ws_song_name->wsbody[0];i++)
      {
        rest_len+=GetSymbolWidth(ws_song_name->wsbody[i], name_font);
      }
      //if(sc == 0)
      if (rest_len<=(name_pos.x2-name_pos.x-0x40))
      {
        scroll_pos = 0;
      }
      is_drawname_tmr=1; 
      if(scroll_pos==1)
        GBS_StartTimerProc(&mytmr,scroll_wait_time,drawidlenameproc);
      else
        GBS_StartTimerProc(&mytmr,defau_scroll_speed,drawidlenameproc);
      FreeWS(txt);
    }
    else
    {
      is_drawname_tmr=0; 
      scroll_pos = 0;
      DrawString(ws_song_name,name_pos.x,(name_pos.y2+name_pos.y-font_h)/2,name_pos.x2,name_pos.y2,name_font,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,name_col,frame_col); 
    }
  }   
  else is_drawname_tmr=0; 
}
*/ //====================removed by evilfox

void draw_idle_name(void)
{
  const char *p_name=strrchr(procfile,'\\')+1;
//  str_2ws(ws_song_name,p_name,64);  //removed by evilfox
//  drawidlenameproc();               //removed by evilfox
  PrintField( idle_X, idle_Y,(char *)p_name, align, font, space);  //added_by evilfox
}

void play_mode_switch(void)
{
  switch(play_mode)
  {
    case 0:
      play_next();
      break;
    case 1:
      play_prev();
      break;
    case 2:
      play_shuff();
      break;
  }
}

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  ws_song_name=AllocWS(64);
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm=(MAIN_CSM *)data;
  zeromem(main_gui,sizeof(MAIN_GUI));	
  patch_rect((RECT*)&Canvas,0,0,screenw-1,screenh-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

int is_call_pause=0;
#define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  void *icsm;
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)ELF_NAME" config updated!");
      FontPathFree();              //==================added by evilfox
      InitConfig();
      FontPathInit(font,(char *)fontpath, fullfont); //==================added by evilfox
      if(is_auto_exit_started==0) exit_time=auto_exit_time*60;
    }
  }
  if((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if(msg->msg==MSG_INCOMMING_CALL)
  {
    is_call_pause=1;
    Control(1);
  }
  if(msg->msg==MSG_END_CALL)
  {
    if(is_call_pause)
      Control(2);
    is_call_pause=0;
  }
  if(msg->msg==MSG_PLAYFILE_REPORT) 
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==playhandle)
    {
      if (pmsg->cmd==M_SAE_PLAYBACK_ERROR)
      {
        Control(3);
      }
      if (pmsg->cmd==M_SAE_PLAYBACK_DONE)
      {
        if(play_flag!=0) 
          play_mode_switch();
      }
    }
    //else control(3);
  }
  icsm=FindCSMbyID(CSM_root()->idle_id);
  if (icsm)
  {
    if (IsGuiOnTop(idlegui_id(icsm)))
    {
      GUI *igui=GetTopGUI();
      {
        if (igui)
        {
/* //===============================removed by evilfox
#ifdef ELKA
          void *canvasdata = BuildCanvas();
          {
#else
          void *idata = GetDataOfItemByID(igui, 2);
          if (idata)
          {
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
            is_idle_gui=1;
            DrawCanvas(canvasdata,name_pos.x,name_pos.y,name_pos.x2,name_pos.y2,1);
            draw_idle_name();
          }
*/ //================================removed by evilfox
//===========addon by evilfox
          canvasdata=BuildCanvas(); 
          draw_idle_name();
//===========addon by evilfox
        }
      }
    }
//    is_idle_gui=0;  //====removed by evilfox
  }
  return(1);
}

void long_press_switch(int key)
{
  switch(key)
  {
    case 0://2
      play_prev();
      break;
    case 1://8
      play_next();
      break;
    case 2://4
      if(sndVolume>0)
      {
        sndVolume--;
        Control(4);
      }
      break;
    case 3://6
      if(sndVolume<6)
      {
        sndVolume++;
        Control(4);
      }
      break;
    case 4://5
      if(play_flag==0)
      {
        play_flag=1;
        Control(0);
        break;
      }
      if(play_flag==1)
      {
        Control(1);
        break;
      }
      if(play_flag==2) 
      Control(2);
      break;
    case 5://3
      play_shuff();
      break;
  }
}

int hot_key_mode=0;
int my_keyhook(int submsg, int msg)
{
  if(!IsGuiOnTop(MAINGUI_ID))
  {
  int i;
  int hot_keys[6]={'2','8','4','6','5','3'};
  for(i=0;i<6;i++)
  {
  if(submsg==hot_keys[i])
  {
  switch(msg)
  {
  case KEY_DOWN:
  if(hot_key_mode==2)
  {
  GBS_SendMessage(MMI_CEPID,KEY_UP,hot_keys[i]);
  return KEYHOOK_NEXT;
  }
  hot_key_mode=0;
  return KEYHOOK_BREAK;
  case KEY_UP:
  if(hot_key_mode==0)
  {
  hot_key_mode=2;
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,hot_keys[i]);
  return KEYHOOK_BREAK;
  }
  if (hot_key_mode==2)
  {
  hot_key_mode=0;
  return KEYHOOK_NEXT;
  }
  hot_key_mode=0;
  return KEYHOOK_BREAK;
  case LONG_PRESS:
  hot_key_mode=1;
  long_press_switch(i);
  break;
  }
  }
  }
  }
  return KEYHOOK_NEXT;
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  FontPathFree();        //=========addon by evilfox
  if(is_drawname_tmr) GBS_DelTimer( &mytmr );
  if(is_auto_exit_started) GBS_DelTimer( &exit_d_tmr );
  if(playhandle) PlayMelody_StopPlayback(playhandle);
  FreeWS(ws_song_name);
  save_his();
  mfree(list_text);
  mfree(name_list);
  FreeWS(ws_exit_time);
  mfree(ch_exit_time);
  RemoveKeybMsgHook((void *)my_keyhook);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

const int minus11=-11;
unsigned short maincsm_name_body[140];

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

void UpdateCSMname(void) 
{
  const char *p_xname=strrchr(procfile,'\\')+1;
  utf8_2ws((WSHDR *)(&MAINCSM.maincsm_name),p_xname,64);
}

int main(char *initday)
{
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  list_text=malloc(16384);
  name_list=malloc(1024*sizeof(LIST_SONG_NAME));
  ws_exit_time=AllocWS(32);
  ch_exit_time=malloc(32);
  sndVolume=def_vol;
  screenw=ScreenW()-1;
  screenh=ScreenH()-1;
  exit_time=auto_exit_time*60; 
  load_list(load_history());
  UpdateCSMname();
//=====================add by evilfox
  FontPathInit(font,(char *)fontpath, fullfont); 
//=====================end of add
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();
  return 0;
}
