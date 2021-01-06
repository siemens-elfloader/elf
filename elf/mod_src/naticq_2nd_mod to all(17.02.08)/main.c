#include "../inc/swilib.h"
#include "../inc/cfg_items.h"
#include "../inc/pnglist.h"
#include "NatICQ.h"
#include "history.h"
#include "conf_loader.h"
#include "mainmenu.h"
#include "main.h"
#include "language.h"
#include "../inc/xtask_ipc.h"
#include "smiles.h"
#include "naticq_ipc.h"
#include "status_change.h"
#include "strings.h"
#include "manage_cl.h"
#include "cl_work.h"
#include "select_smile.h"
#include "revision.h"
#ifdef EVILFOX
#include "print.h"
#endif

#ifndef NEWSGOLD
#define SEND_TIMER
#endif

int total_unread;
#define EOP -10
int CurrentStatus;
int CurrentXStatus;
volatile CLIST *cltop;

#ifdef EVILFOX
//=========================mod definitions
#ifdef ELKA
#pragma swi_number=54
__swi __arm void SLI_SetState(unsigned char state);  //for sli usage
#endif
#ifdef NEWSGOLD
#pragma swi_number=0x0C5
__swi __arm int IsIdleUiOnTop(); //for check if idlegui
#endif
char upcoming[64]; //for nick that comes online
int total_unread2; //for total unread mesages
int total_c_online; //for count of contacts who just came online
#ifdef ELKA
int Is_SLI_On; //for checking if is active sli
GBSTMR mytmr; //timer for sli
#endif
//extern const int SLI_TYPE; //for check where to activate sli
int Is_ILU_On; // for ilumination use
int seconds; //sekundes
int minutes; //minuutes
int hours; //hours
GBSTMR ctmr; //time counter
char online_txt[18]; //online txt
extern const unsigned int ONTIME_X; //cordinates for online time ms
extern const unsigned int ONTIME_Y; //cordinates for online time ms
extern const int Pause_Time; // for time refresher
int align=0; //align for png font
extern const unsigned int fonto; // font number
extern const unsigned int spaco1; // space between letters in png font
extern const unsigned int spaco2; // space between letters in png font
extern const unsigned int system_color; //system font color
int spaco1r; //display
extern const char fontpath[64]; //font path for png
int time_draw; //refresh for mainscreen
void *canvasdata; //just canvasdata
int show_ping; //for autoping not show
int ping_sec; //for autoping engaging
extern const int Show_Ping; //do ping if 1
extern const unsigned int PING_X; //cordinates for ping ms
extern const unsigned int PING_Y; //cordinates for ping ms
char ping_txt[16]; // ping txt
extern const unsigned int UNREAD_X; //cordinates for unread ms
extern const unsigned int UNREAD_Y; //cordinates for unread ms
char unread_txt[16]; //unread msg txt
extern const int Is_Unread_On; //show/hide unread on ms
extern const int Is_Online_On; //show/hide online time on ms
int INC_show; //for popup sender counter
char show_nick[64]; //nick save for popup sender
int Is_INC_On; // show//hide popup sender
GBSTMR incs; // popup sendet timer
#ifdef ELKA
int font=9; // font for popup sender
#else
#ifdef NEWSGOLD
int font=11; // font for popup sender
#else
int font=7; // font for popup sender
#endif
#endif
//const char color[4]={255,255,255,100}; //  color for popup sender
int pp_color; //  color for popup sender
extern const int Is_DRAWMAIN_On; //show/hide main msg
int main_d; // refresher for main msg
extern const unsigned int MSG_Y; // cordinates for main msg
extern const unsigned int MSG_X; // cordinates for main msg
int paused_height; // vertical height of font
int in_count; // count incoming messages
int out_count; // count outgoing messages
#ifdef ELKA
char last_msg_buffer[3072]; // last message buffer
#endif
int comanda; //for check comand to add it to log
int msg_away_timer; // time for autostatus
extern const unsigned int AUTO_ENGADE; //time to start autostatus
int change_back_status; //to do changeback or not
int status_rem; //remember your status before change
char away_msg_time[64]; //away time char
char away_msg[256]; // away txt
int away_m; //use to check if auto time engaged
extern const int Auto_Status; //use autostatus or not to use
extern const char away_msg1[24]; //for hello msg in autostatus
extern const char away_msg2[64]; //for automsg txt
extern const int time_zone; //for time zone initialization
char tim_zone[24]; //timezone txt
int In_EXT_On; //to initialize extended sounds
char ext_sound[128]; //path to play or init ext sound
extern const char sndMsg2[64]; //path to extended sounds
int total_count; //counter for extender sound info display
int in_ext; //counter for extender sound info display
char LG_MENU2[32]; //moved menu name here for my needs
extern const unsigned int main_draw_l; // lenght of txt to draw on main
extern const int TIME_OR_MSG; // for check what to draw with main header
int icon_change; //for icon change on ms
int icon_change2; //for icon change on ms
extern int *XStatusesIconArray; // strange need but ok
char mod_info[]="2nd generation mod based on revision 1848! mod date: 19.02.08 14:02!"; //just info for mod info
//=========================end
#endif

#ifdef EVILFOX
//=========================modification functions
#ifdef ELKA
void SLI_Off(void);
void SLI_On()
{
  if (total_unread)
  {
  SLI_SetState(1);   
  GBS_StartTimerProc(&mytmr, 21, SLI_Off);
  }
  else
    SLI_SetState(0);
}

void SLI_Off()
{
  SLI_SetState(2);
  if (total_unread)
    GBS_StartTimerProc(&mytmr, 21, SLI_On); //26*SLI_time2
  else
    SLI_SetState(0);
}

void SLI_Timer()
{
  if(Is_SLI_On)
  GBS_StartTimerProc(&mytmr, 262, SLI_On); //262*SLI_time
}
#endif
//===============time count=========
void time_count()
{
  seconds++;
  if(seconds==60)
  {
    seconds=0;
    minutes++;
  }
  if(minutes==60)
  {
    minutes=0;
    hours++;
  }
}

void time_counter()
{
  if(connect_state==3)
  {
  time_count();
  GBS_StartTimerProc(&ctmr, 216, time_counter);
  }
  else
  {
    if(!Pause_Time)
    {
    seconds=0;
    minutes=0;
    hours=0;
    }
    GBS_StartTimerProc(&ctmr, 216, time_counter);
  }
  time_draw=1;
}
//=========================time count=====
//=========================mainscreen ping===============
static void PingToServer2(void)
{
  TPKT *p;
  p=malloc(sizeof(PKT)+sizeof(TTime));
  GetDateTime(NULL,(TTime *)p->data);
  p->pkt.uin=0;
  p->pkt.type=T_ECHO;
  p->pkt.data_len=sizeof(TTime);
  SUBPROC((void *)SendAnswer,0,p);
}
//=========================mainscreen ping==============

//=========================popup sender=========================
void show_pp_sender()
{
  if(INC_show>0)
  {
    WSHDR *ws=AllocWS(64);
    ascii2ws(ws,show_nick);
    DrawRectangle(0,0,Get_WS_width(ws,font)+2,GetFontYSIZE(font)+2,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
    DrawString(ws,1,1,1+Get_WS_width(ws,font)+2,1+GetFontYSIZE(font),font,0,GetPaletteAdrByColorIndex(pp_color),GetPaletteAdrByColorIndex(23));
    FreeWS(ws);
    INC_show--;
    GBS_StartTimerProc(&incs, 5, show_pp_sender);
  }
}
//==================================popup sender===============
//===========================main msg add===================
char a_txt[64];
char s_txt[64];
char d_txt[64];
char f_txt[64];
char g_txt[64];
             
static AddToMain(const char *nameu,const char *si)
{
  char de[64];
  char du[64];
  int text_l=0;
  int iz=0;
  int name_l=0;
  name_l=strlen(nameu);
  text_l=main_draw_l-name_l;
  
  if(strlen(si)>text_l)
  {
    strncpy(du,si,text_l);
    du[text_l]='\0';
    sprintf(de,"%s%s",du,"...");
  }
  else
    strcpy(de, si);
  iz=0;
  while(strlen(de)!=iz)
  {
    if((de[iz]==0x0D)||(de[iz]==0x0A)) de[iz]=0x20;
    iz++;
  }
  de[iz]='\0';
  strcpy(a_txt, s_txt);
  strcpy(s_txt, d_txt);
  strcpy(d_txt, f_txt);
  strcpy(f_txt, g_txt);
  sprintf(g_txt, "%s: %s", nameu,de);
  main_d=1;
}  
//=================================main msg add============
//==================================autostatus=============
void away_engage()
{
    TTime tt;
    GetDateTime(NULL,&tt);
    sprintf(away_msg_time, "(away since %02d : %02d ( %s ) )", tt.hour, tt.min, tim_zone);
    away_m=1;
    if(CurrentStatus!=2)
    {
      status_rem=CurrentStatus;
      CurrentStatus=2;
      set_my_status();
      change_back_status=1;
    }
}

int my_keyhook(int key, int m)
{
  if (m==KEY_DOWN)
       {
         if(change_back_status==1)
         {
           CurrentStatus=status_rem;
           set_my_status();
           change_back_status=0;
         }
#ifdef ELKA
         if ((key==VOL_DOWN_BUTTON)&&(IsIdleUiOnTop()))
         {
           msg_away_timer=AUTO_ENGADE;
           away_engage();
         }
         else
#endif
           msg_away_timer=away_m=0;
       }
  return 0;
}

void init_time_zone()
{
  switch(time_zone)
  {
  case 0:
    sprintf(tim_zone, "GMT -12:00");
    break;
  case 1:
    sprintf(tim_zone, "GMT -11:00");
    break;
  case 2:
    sprintf(tim_zone, "GMT -10:00");
    break;
  case 3:
    sprintf(tim_zone, "GMT -09:00");
    break;
  case 4:
    sprintf(tim_zone, "GMT -08:00");
    break;
  case 5:
    sprintf(tim_zone, "GMT -07:00");
    break;
  case 6:
    sprintf(tim_zone, "GMT -06:00");
    break;
  case 7:
    sprintf(tim_zone, "GMT -05:00");
    break;
  case 8:
    sprintf(tim_zone, "GMT -04:00");
    break;
  case 9:
    sprintf(tim_zone, "GMT -03:30");
    break;
  case 10:
    sprintf(tim_zone, "GMT -03:00");
    break;
  case 11:
    sprintf(tim_zone, "GMT -02:00");
    break;
  case 12:
    sprintf(tim_zone, "GMT -01:00");
    break;
  case 13:
    sprintf(tim_zone, "GMT 00:00");
    break;
  case 14:
    sprintf(tim_zone, "GMT +01:00");
    break;
  case 15:
    sprintf(tim_zone, "GMT +02:00");
    break;
  case 16:
    sprintf(tim_zone, "GMT +03:00");
    break;
  case 17:
    sprintf(tim_zone, "GMT +03:30");
    break;
  case 18:
    sprintf(tim_zone, "GMT +04:00");
    break;
  case 19:
    sprintf(tim_zone, "GMT +04:30");
    break;
  case 20:
    sprintf(tim_zone, "GMT +05:00");
    break;
  case 21:
    sprintf(tim_zone, "GMT +05:30");
    break;
  case 22:
    sprintf(tim_zone, "GMT +05:45");
    break;
  case 23:
    sprintf(tim_zone, "GMT +06:00");
    break;
  case 24:
    sprintf(tim_zone, "GMT +06:30");
    break;
  case 25:
    sprintf(tim_zone, "GMT +07:00");
    break;
  case 26:
    sprintf(tim_zone, "GMT +08:00");
    break;
  case 27:
    sprintf(tim_zone, "GMT +09:00");
    break;
  case 28:
    sprintf(tim_zone, "GMT +09:30");
    break;
  case 29:
    sprintf(tim_zone, "GMT +10:00");
    break;
  case 30:
    sprintf(tim_zone, "GMT +11:00");
    break;
  case 31:
    sprintf(tim_zone, "GMT +12:00");
    break;
  case 32:
    sprintf(tim_zone, "GMT +13:00");
    break;
  }
}
//==================================autostatus=============
//============================init extended sounds=============
void Init_Ext_Sounds(void)
{
  total_count=0;
  in_ext=0;
//  unsigned int uli;
  char msgboxer[64];
  CLIST *t;
  t=(CLIST *)(&cltop);
  while(t=(CLIST *)(t->next))
  {
    if(!t->isgroup)
    {
      total_count++;
      volatile int hFile_ex;
      unsigned int io_error_ex = 0;
      sprintf(ext_sound, "%s%d.wav", sndMsg2, t->uin);
      hFile_ex = fopen(ext_sound,A_ReadOnly + A_BIN,P_READ, &io_error_ex);
      if(hFile_ex!=-1)
      {
        in_ext++;
        t->ext_snd=1;
        fclose(hFile_ex, &io_error_ex);
      }
      else
        t->ext_snd=0;
    }
  }
  sprintf(msgboxer, "Complete!\n"
          "Enabled for:\n"
            "%d / %d contacts",
            in_ext, total_count);
  sprintf(LG_MENU2, "Меню <Ext:%d/%d>", in_ext, total_count);
  ShowMSG(1,(int)msgboxer);
}
//============================init extended sounds=============
//=========================end of modification functions
#endif

char hostname[128];
extern volatile int total_smiles;
extern volatile int total_xstatuses;
extern volatile int xstatuses_load;

#define USE_MLMENU

#define TMR_SECOND 216

//IPC
const char ipc_my_name[32]=IPC_NATICQ_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;


char elf_path[256];
int maincsm_id;
int maingui_id;

void SMART_REDRAW(void)
{
  int f;
  LockSched();
  f=IsGuiOnTop(maingui_id);
  UnlockSched();
  if (f) REDRAW();
}

//По 10 секунд
#ifdef EVILFOX
#define ACTIVE_TIME 30
#else
#define ACTIVE_TIME 360
#endif

//Максимальное количество сообщений в логе
#define MAXLOGMSG (20)

// Строковые описания статусов

const char S_OFFLINE[]="Offline";
const char S_INVISIBLE[]="Invisible";
const char S_AWAY[]="Away";
const char S_NA[]="N/A";
const char S_OCCUPIED[]="Occupied";
const char S_DND[]="DND";
const char S_ONLINE[]="Online";
const char S_FFC[]="FFC";

volatile int SENDMSGCOUNT;

int IsActiveUp=0;

int Is_Vibra_Enabled;
unsigned int Is_Sounds_Enabled;
int Is_Show_Offline;
int Is_Show_Groups;

int S_ICONS[TOTAL_ICONS+1];



WSHDR *ews;

extern const unsigned int UIN;
extern const char PASS[];

static const char * const icons_names[TOTAL_ICONS]=
{
  "offline.png",
  "invisible.png",
  "away.png",
  "na.png",
  "occupied.png",
  "dnd.png",
  "depression.png",
  "evil.png",
  "home.png",
  "lunch.png",
  "work.png",
  "online.png",
  "ffc.png",
  "message.png",
  "unknown.png",
  "groupon.png",
  "groupoff.png",
  "null.png",
  "addcont.png",
  "head.png",
  "logo.png",
  "ping.png",
  "settings.png",
  "vis1.png",
  "vis2.png",
  "vis3.png",
  "vis4.png",
  "vis5.png"
};

extern const char ICON_PATH[];

void setup_ICONS(void)
{
  int i=0;
  do
  {
    if (!S_ICONS[i]) S_ICONS[i]=(int)MakeGlobalString(ICON_PATH,'\\',icons_names[i]);
    i++;
  }
  while(i<TOTAL_ICONS);
  return;
}

void free_ICONS(void)
{
  int i=0;
  do
  {
    mfree((void*)S_ICONS[i]);
    S_ICONS[i]=0;
    i++;
  }
  while(i<TOTAL_ICONS);
  return;
}

extern const unsigned int IDLEICON_X;
extern const unsigned int IDLEICON_Y;

extern const unsigned int I_COLOR;
extern const unsigned int TO_COLOR;
extern const unsigned int X_COLOR;
extern const unsigned int O_I_COLOR;
extern const unsigned int O_TO_COLOR;
extern const unsigned int O_X_COLOR;

extern const unsigned int ED_FONT_SIZE;
extern const unsigned int ED_H_FONT_SIZE;
extern const unsigned int ED_X_FONT_SIZE;
extern const unsigned int O_ED_FONT_SIZE;
extern const unsigned int O_ED_H_FONT_SIZE;
extern const unsigned int O_ED_X_FONT_SIZE;

extern const unsigned int ACK_COLOR;
extern const unsigned int UNACK_COLOR;

extern const int ENA_AUTO_XTXT;
extern const int NOT_LOG_SAME_XTXT;
extern const int LOG_XTXT;

extern const int HISTORY_BUFFER;

const char percent_t[]="%t";
const char percent_d[]="%d";
const char empty_str[]="";
const char I_str[]="I";
const char x_status_change[]="X-Status change";

char logmsg[256];

//Illumination by BoBa 19.04.2007
///////////
extern const unsigned int ILL_DISP_RECV;
extern const unsigned int ILL_KEYS_RECV;
extern const unsigned int ILL_DISP_SEND;
extern const unsigned int ILL_KEYS_SEND;
extern const unsigned int ILL_SEND_TMR;
extern const unsigned int ILL_SEND_FADE;
extern const unsigned int ILL_RECV_TMR;
extern const unsigned int ILL_RECV_FADE;
extern const unsigned int ILL_OFF_FADE;

GBSTMR tmr_illumination;

void IlluminationOff(){
  SetIllumination(0,1,0,ILL_OFF_FADE);
  SetIllumination(1,1,0,ILL_OFF_FADE);
}

void IlluminationOn(const int disp, const int key, const int tmr, const int fade){
  if(!tmr) return;
  GBS_DelTimer(&tmr_illumination);
  SetIllumination(0,1,disp,fade);
  SetIllumination(1,1,key,fade);
  GBS_StartTimerProc(&tmr_illumination,tmr*216,IlluminationOff);
}

volatile int silenthide;    //by BoBa 25.06.07
volatile int disautorecconect;	//by BoBa 10.07
///////////
int Is_Vibra_Enabled;
unsigned int Is_Sounds_Enabled;
int Is_Show_Offline;
int Is_Show_Groups;
int CurrentStatus;
int CurrentXStatus;
int CurrentPrivateStatus;

//===================================================================
const char def_setting[]="%sdef_settings_%d";

void ReadDefSettings(void)
{
  DEF_SETTINGS def_set;
  int f;
  unsigned int err;
  char str[128];
  snprintf(str,127,def_setting,elf_path,UIN);
  if ((f=fopen(str,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
    fread(f,&def_set,sizeof(DEF_SETTINGS),&err);
    fclose(f,&err);
    Is_Vibra_Enabled=def_set.vibra_status;
    Is_Sounds_Enabled=def_set.sound_status;
    Is_Show_Offline=def_set.off_contacts;
    Is_Show_Groups=def_set.show_groups;
    CurrentStatus=def_set.def_status+1;
    CurrentXStatus=def_set.def_xstatus;
#ifdef EVILFOX
#ifdef ELKA
    Is_SLI_On=def_set.sli_state;
#endif
    Is_ILU_On=def_set.ilu_state;
    Is_INC_On=def_set.inc_state;
#endif
  }
  else
  {
    Is_Vibra_Enabled=0;
    Is_Sounds_Enabled=0;
    Is_Show_Offline=0;
    Is_Show_Groups=1;
    CurrentStatus=IS_ONLINE;
    CurrentXStatus=0;
#ifdef ELKA
    Is_SLI_On=1;
#endif
    Is_ILU_On=0;
    Is_INC_On=1;
  }
}

void WriteDefSettings(void)
{
  DEF_SETTINGS def_set;
  int f;
  unsigned int err;
  char str[128];
  snprintf(str,127,def_setting,elf_path,UIN);
  if ((f=fopen(str,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1)
  {
    def_set.vibra_status=Is_Vibra_Enabled;
    def_set.sound_status=Is_Sounds_Enabled;
    def_set.off_contacts=Is_Show_Offline;
    def_set.show_groups=Is_Show_Groups;
    def_set.def_status=CurrentStatus-1;
    def_set.def_xstatus=CurrentXStatus;
#ifdef EVILFOX
#ifdef ELKA
    def_set.sli_state=Is_SLI_On;
#endif
    def_set.ilu_state=Is_ILU_On;
    def_set.inc_state=Is_INC_On;
#endif
    fwrite(f,&def_set,sizeof(DEF_SETTINGS),&err);
    fclose(f,&err);
  }
}
//by KreN 27.09.2007
//===================================================================
extern S_SMILES *s_top;
extern DYNPNGICONLIST *SmilesImgList;
extern DYNPNGICONLIST *XStatusesImgList;

//=============================Проигрывание звука=======================
extern const char sndStartup[];
extern const char sndSrvMsg[];
extern const char sndGlobal[];
extern const char sndMsg[];
extern const char sndMsgSent[];
extern const unsigned int sndVolume;


void Play(const char *fname)
{
  if ((!IsCalling())&&Is_Sounds_Enabled)
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
      PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
  }
}

GBSTMR tmr_vibra;
volatile int vibra_count;

void start_vibra(void)
{
  extern const int VIBR_TYPE;
  void stop_vibra(void);
  if((Is_Vibra_Enabled)&&(!IsCalling()))
  {
    extern const unsigned int vibraPower;
    SetVibration(vibraPower);
    if(VIBR_TYPE)
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>2,stop_vibra);
    else
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,stop_vibra);
  }
}

void stop_vibra(void)
{
  extern const int VIBR_TYPE;
  SetVibration(0);
  if (--vibra_count)
  {
    if(VIBR_TYPE)
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>5,start_vibra);
    else
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,start_vibra);
  }
}

void ChangeVibra(void)
{
  if (!(Is_Vibra_Enabled=!(Is_Vibra_Enabled)))
    ShowMSG(1,(int)LG_MSGVIBRADIS);
  else
    ShowMSG(1,(int)LG_MSGVIBRAENA);
}

void ChangeSound(void)
{
  if (!(Is_Sounds_Enabled=!(Is_Sounds_Enabled)))
    ShowMSG(1,(int)LG_MSGSNDDIS);
  else
    ShowMSG(1,(int)LG_MSGSNDENA);
}

//===================================================================
//Templates
char *templates_chars; //Собственно файл
char **templates_lines; //Массив указателей на строки

void FreeTemplates(void)
{
  if (templates_lines) mfree(templates_lines);
  if (templates_chars) mfree(templates_chars);
  templates_lines=NULL;
  templates_chars=NULL;
}

extern const char TEMPLATES_PATH[];

int LoadTemplates(unsigned int uin)
{
  FSTATS stat;
  char fn[256];
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p;
  char *pp;
  int c;
  FreeTemplates();
  strcpy(fn,TEMPLATES_PATH);
  i=strlen(fn);
  sprintf(fn+i,"\\%d.txt",uin);
  if (GetFileStats(fn,&stat,&ul)==-1) goto L1;
  if ((fsize=stat.size)<=0) goto L1;
  if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1)
  {
  L1:
    strcpy(fn+i,"\\0.txt");
    if (GetFileStats(fn,&stat,&ul)==-1) return 0;
    if ((fsize=stat.size)<=0) return 0;
    f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul);
  }
  if (f==-1) return 0;
  p=templates_chars=malloc(fsize+1);
  p[fread(f,p,fsize,&ul)]=0;
  fclose(f,&ul);
  i=0;
  pp=p;
  for(;;)
  {
    c=*p;
    if (c<32)
    {
      if (pp&&(pp!=p))
      {
	templates_lines=realloc(templates_lines,(i+1)*sizeof(char *));
	templates_lines[i++]=pp;
      }
      pp=NULL;
      if (!c) break;
      *p=0;
    }
    else
    {
      if (pp==NULL) pp=p;
    }
    p++;
  }
  return i;
}


//===================================================================

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



int RXstate=EOP; //-sizeof(RXpkt)..-1 - receive header, 0..RXpkt.data_len - receive data

TPKT RXbuf;
TPKT TXbuf;

int connect_state=0;

int sock=-1;

volatile unsigned long TOTALRECEIVED;
volatile unsigned long TOTALSENDED;
volatile unsigned long ALLTOTALRECEIVED;	//by BoBa 10.07
volatile unsigned long ALLTOTALSENDED;

volatile int sendq_l=0; //Длинна очереди для send
volatile void *sendq_p=NULL; //указатель очереди

volatile int is_gprs_online=1;

GBSTMR reconnect_tmr;

extern void kill_data(void *p,void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}



//===============================================================================================
#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}
//===============================================================================================


volatile unsigned int GROUP_CACHE; //Текущая группа для добавления

volatile int contactlist_menu_id;

GBSTMR tmr_active;

volatile int edchat_id;

//Применяется для добавления сообщений
//CLIST *edcontact;
//void *edgui_data;

static int prev_clmenu_itemcount;

char clm_hdr_text[48];
static const char def_clm_hdr_text[] = LG_CLTITLE;
static const char key_clm_hdr_text[] = LG_CLT9INP;

static const HEADER_DESC contactlist_menuhdr = {0, 0, 0, 0, S_ICONS+ICON_HEAD, (int)clm_hdr_text, LGP_NULL};
static const int menusoftkeys[] = {0,1,2};
static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)LG_SELECT},
  {0x0001, 0x0000, (int)LG_CLOSE},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

char clmenu_sk_r[16];
static const char def_clmenu_sk_r[] = LG_CLOSE;
static const char key_clmenu_sk_r[] = LG_CLEAR;

static const SOFTKEY_DESC clmenu_sk[]=
{
  {0x0018, 0x0000, (int)LG_OPTIONS},
  {0x0001, 0x0000, (int)clmenu_sk_r},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const SOFTKEYSTAB clmenu_skt =
{
  clmenu_sk, 0
};

void contactlist_menu_ghook(void *data, int cmd);
int contactlist_menu_onkey(void *data, GUI_MSG *msg);
void contactlist_menu_iconhndl(void *data, int curitem, void *unk);

#ifdef USE_MLMENU
static const ML_MENU_DESC contactlist_menu=
{
  8,contactlist_menu_onkey,contactlist_menu_ghook,NULL,
  menusoftkeys,
  &clmenu_skt,
  0x11, //+0x400
  contactlist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1 //Добавочных строк
};
#else
static const MENU_DESC contactlist_menu=
{
  8,contactlist_menu_onkey,contactlist_menu_ghook,NULL,
  menusoftkeys,
  &clmenu_skt,
  0x11, //+0x400
  contactlist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};
#endif

//GBSTMR tmr_ping;
int tenseconds_to_ping;

LOGQ *NewLOGQ(const char *s)
{
  LOGQ *p=malloc(sizeof(LOGQ)+1+strlen(s));
  zeromem(p,sizeof(LOGQ));
  strcpy(p->text,s);
  return p;
}

LOGQ *LastLOGQ(LOGQ **pp)
{
  LOGQ *q=*pp;
  if (q)
  {
    while(q->next) q=q->next;
  }
  return(q);
}

//Уничтожить лог
void FreeLOGQ(LOGQ **pp)
{
  LOGQ *p=*pp;
  *pp=NULL; //Сразу обрежем
  while(p)
  {
    LOGQ *np=p->next;
    mfree(p);
    p=np;
  }
}

//Удалить элемент из лога
void RemoveLOGQ(LOGQ **queue, LOGQ *p)
{
  LOGQ *q=(LOGQ *)queue;
  LOGQ *qp;
  while(qp=q->next)
  {
    if (qp==p)
    {
      q->next=p->next;
      break;
    }
    q=qp;
  }
  mfree(p); //Если элемент вообще не в логе
}

//Добавить элемент в лог
int AddLOGQ(LOGQ **queue, LOGQ *p)
{
  LOGQ *q=(LOGQ *)queue;
  LOGQ *qp;
  int i=0;
  while(qp=q->next) {q=qp;i++;}
  p->next=NULL;
  q->next=p;
  return(i+1); //Теперь всего в логе элементов
}

//Получаем последний полученный X-статус
char *GetLastXTextLOGQ(CLIST *t)
{
  LOGQ *p = t->log;
  char *s = 0;
  if(!p) return 0;
  while(p->next)
  {
    if((p->type&0x0F)==3)
      s = p->text;
    p = p->next;
  }
  if((p->type&0x0F)==3)
    s = p->text;
  return s;
}

int GetIconIndex(CLIST *t)
{
  unsigned short s;
  if (t)
  {
    s=t->state;
    if (t->isgroup) return(IS_GROUP);
    if (t->isunread)
      return(IS_MSG);
    else
    {
      if (s==0xFFFF) return(IS_OFFLINE);
      if ((s&0xF000)==0x2000) return (IS_LUNCH);
      if ((s&0xF000)==0x3000) return (IS_EVIL);
      if ((s&0xF000)==0x4000) return (IS_DEPRESSION);
      if ((s&0xF000)==0x5000) return (IS_HOME);
      if ((s&0xF000)==0x6000) return (IS_WORK);
      if (s & 0x0020) return(IS_FFC);
      if (s & 0x0001) return(IS_AWAY);
      if (s & 0x0005) return(IS_NA);
      if (s & 0x0011) return(IS_OCCUPIED);
      if (s & 0x0013) return(IS_DND);
      if (s & 0x0002) return(IS_FFC);
      if (s & 0x0100) return(IS_INVISIBLE);
    }
  }
  else
  {
    return(IS_UNKNOWN);
  }
  return(IS_ONLINE);
}

LOGQ *FindContactLOGQByAck(TPKT *p)
{
  CLIST *t;
  LockSched();
  t=FindContactByUin(p->pkt.uin);
  UnlockSched();
  unsigned int id=*((unsigned short*)(p->data));
  LOGQ *q;
  if (!t) return NULL;
  LockSched();
  q=t->log;
  while(q)
  {
    if (q->ID==id) break;
    q=q->next;
  }
  UnlockSched();
  return q;
}


char ContactT9Key[32];

void UpdateCLheader(void)
{
  if (strlen(ContactT9Key))
  {
    strcpy(clm_hdr_text,key_clm_hdr_text);
    strcat(clm_hdr_text,ContactT9Key);
    strcpy(clmenu_sk_r,key_clmenu_sk_r);
  }
  else
  {
#ifdef EVILFOX
    if(TIME_OR_MSG)
    {
    if(total_c_online>0)
      sprintf(clm_hdr_text, "%s(%d/%d) On:%02d",def_clm_hdr_text,total_unread,total_unread2, total_c_online);
    else
    sprintf(clm_hdr_text, "%s(%d/%d)",def_clm_hdr_text,total_unread,total_unread2);
    }
    else
      {
        TTime the;
        GetDateTime(NULL,&the);
        if(total_c_online>0)
          sprintf(clm_hdr_text, "%s(%02d:%02d) On:%02d",def_clm_hdr_text, the.hour, the.min, total_c_online);
        else
        sprintf(clm_hdr_text, "%s(%02d:%02d)",def_clm_hdr_text,the.hour,the.min);
      }
#else
    strcpy(clm_hdr_text,def_clm_hdr_text);
#endif
    strcpy(clmenu_sk_r,def_clmenu_sk_r);
  }
}

void ClearContactT9Key(void)
{
  zeromem(ContactT9Key,sizeof(ContactT9Key));
}

void AddContactT9Key(int chr)
{
  int l=strlen(ContactT9Key);
  if (l<(sizeof(ContactT9Key)-1))
  {
    ContactT9Key[l]=chr;
  }
}

void BackSpaceContactT9(void)
{
  int l=strlen(ContactT9Key);
  if (l)
  {
    l--;
    ContactT9Key[l]=0;
  }
}

void create_contactlist_menu(void)
{
  int i;
  i=CountContacts();
  prev_clmenu_itemcount=i;
  UpdateCLheader();
  patch_header(&contactlist_menuhdr);
#ifdef USE_MLMENU
  contactlist_menu_id=CreateMultiLinesMenu(0,0,&contactlist_menu,&contactlist_menuhdr,0,i);
#else
  contactlist_menu_id=CreateMenu(0,0,&contactlist_menu,&contactlist_menuhdr,0,i,0,0);
#endif
}

void contactlist_menu_ghook(void *data, int cmd)
{
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    silenthide=0;
    pltop->dyn_pltop=XStatusesImgList;
    DisableIDLETMR();
  }
}

void RecountMenu(CLIST *req, int needfocus)
{
  int i;
  int j;
  void *data;
  UpdateCLheader();
  if (!contactlist_menu_id) return; //Нечего считать
  data=FindGUIbyId(contactlist_menu_id,NULL);
  if (req==NULL)
  {
    j=0;
  }
  else
  {
    j=FindContactByContact(req);
  }
  i=CountContacts();
  if (j>=i) j=i-1;
  if (j<0) j=0;
  if (i!=prev_clmenu_itemcount)
  {
    prev_clmenu_itemcount=i;
    Menu_SetItemCountDyn(data,i);
  }
  if(needfocus) SetCursorToMenuItem(data,j);
  if (IsGuiOnTop(contactlist_menu_id)) RefreshGUI();
}

int contactlist_menu_onkey(void *data, GUI_MSG *msg)
{
  CLIST *t;
  int i;
  i=GetCurMenuItem(data);
  t=FindContactByN(i);
  if (msg->keys==0x18)
  {
    ShowMainMenu();
    return(-1);
  }
  if (msg->keys==0x3D)
  {
    if (t)
    {
      if (t->isgroup)
      {
	t->state^=0xFFFF;
	RecountMenu(t, 1);
	return(-1);
      }
      if (strlen(ContactT9Key))
      {
	ClearContactT9Key();
	RecountMenu(NULL, 1);
      }
      if(!t->isactive && HISTORY_BUFFER) GetHistory(t, 64<<HISTORY_BUFFER);
      CreateEditChat(t);
    }
    return(-1);
  }
  if (msg->keys==1)
  {
    if (strlen(ContactT9Key))
    {
      BackSpaceContactT9();
      RecountMenu(NULL, 1);
      return(-1);
    }
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
#ifdef EVILFOX
    if ((key>='0')&&(key<='9'))
#else
    if (((key>='0')&&(key<='9'))||(key=='#')||(key=='*'))
#endif
    {
      AddContactT9Key(key);
      RecountMenu(NULL, 1);
      return(-1);
    }
    if (key==VOL_UP_BUTTON)
    {
      char *small_info=malloc(256);
      sprintf(small_info, "Online time:\n"
              "%02d:%02d:%02d\n"
                "Server:\n"
                  "%s"
                , hours, minutes, seconds, hostname);
      ShowMSG(1,(int)small_info);
      mfree(small_info);
    }
    if (key==LEFT_BUTTON)
    {
#ifdef EVILFOX
      while(t=(CLIST *)(t->next))
       {
         if (t->isunread) goto doit;
       }
      t=(CLIST *)(&cltop);
      while(t=(CLIST *)(t->next))
      {
        if (t->isunread) goto doit;
      }
      t=(CLIST *)(&cltop);
      if(Is_Show_Groups)
      {
        while(t=(CLIST *)(t->next))
        {
          if (t->isgroup)
          {
            if(!t->state)
	    t->state^=0xFFFF;
          }
        }
      }
      goto doit2;
    doit:
      {
      CLIST *g=FindGroupByID(t->group);
      if (g)
      {
	if (g->state)
	{
	  g->state=0;
	}
      }
      }
    doit2:
      RecountMenu(t, 1);
#else
      IsActiveUp=!IsActiveUp;
      RecountMenu(NULL, 1);
#endif
      return(-1);
    }
#ifdef EVILFOX
    if (key=='*')
    {
      while(t=(CLIST *)(t->next))
       {
         if (t->just_now) goto doit3;
       }
      t=(CLIST *)(&cltop);
      while(t=(CLIST *)(t->next))
      {
        if (t->just_now) goto doit3;
      }
      return(-1);
    doit3:
      {
      CLIST *g=FindGroupByID(t->group);
      if (g)
      {
	if (g->state)
	{
	  g->state=0;
	}
      }
      }
      RecountMenu(t, 1);
      return(-1);
    }
    if (key=='#')
    {
      while(t=(CLIST *)(t->next))
       {
         if (t->isactive) goto doit4;
       }
      t=(CLIST *)(&cltop);
      while(t=(CLIST *)(t->next))
      {
        if (t->isactive) goto doit4;
      }
      return(-1);
    doit4:
      {
      CLIST *g=FindGroupByID(t->group);
      if (g)
      {
	if (g->state)
	{
	  g->state=0;
	}
      }
      }
      RecountMenu(t, 1);
      return(-1);
    }
#endif
    if (key==RIGHT_BUTTON)
    {
      //Послать запрос текста XStatus
      if (t)
      {
	if (!t->isgroup)
	{
	  FreeXText(t);
          t->req_xtext=0;
          RequestXText(t->uin);
	  RefreshGUI();
	  return(-1);
	}
      }
    }
    if (key==GREEN_BUTTON)
    {
#ifdef EVILFOX
      IsActiveUp=!IsActiveUp;
      RecountMenu(NULL, 1);
#else
      if (t && Is_Show_Groups) {//есть контакт и показываем группы?
       if (!t->isgroup)
        t=FindGroupByID(t->group);
       if (t && !t->state) {//группа нашлась и она открыта?
        t->state^=0xFFFF;
        RecountMenu(t, 1);
       }
      }
#endif
      return(-1);
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    if (msg->gbsmsg->submess=='#')
    {
      ClearContactT9Key();
      RecountMenu(NULL, 1);
      gipc.name_to=ipc_xtask_name;
      gipc.name_from=ipc_my_name;
      gipc.data=0;
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
      if (IsUnlocked())
      {
        KbdLock();
      }
      return(-1);
    }
    if (msg->gbsmsg->submess=='*'){
      ClearContactT9Key();
      RecountMenu(NULL, 1);
      silenthide=1;
      gipc.name_to=ipc_xtask_name;
      gipc.name_from=ipc_my_name;
      gipc.data=0;
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
    }
  }
  return(0);
}

void GetOnTotalContact(int group_id,int *_onlinetotal)
{
  CLIST *t;
  t=(CLIST *)&cltop;
  int online=0,total=0;
  while((t=t->next))
  {
    if(t->group==group_id && !t->isgroup)
    {
      total++;
      if (t->state!=0xFFFF) online++;
    }
  }
  _onlinetotal[0]=online;
  _onlinetotal[1]=total;
}


void contactlist_menu_iconhndl(void *data, int curitem, void *unk)
{
  CLIST *t;
#ifdef USE_MLMENU
  void *item=AllocMLMenuItem(data);
#else
  void *item=AllocMenuItem(data);
#endif
  int icon;

  WSHDR *ws2;
#ifdef USE_MLMENU
  WSHDR *ws4;
#endif
  WSHDR ws1loc, *ws1;
  unsigned short num[128];
  ws1=CreateLocalWS(&ws1loc,num,128);
#ifdef USE_MLMENU
  WSHDR ws3loc, *ws3;
  unsigned short num3[128];
  ws3=CreateLocalWS(&ws3loc,num3,128);
  char s[64];
#endif
  t=FindContactByN(curitem);
  if (t)
  {
    icon=GetIconIndex(t);
    if (icon!=IS_GROUP)
    {
#ifdef EVILFOX
      if(t->just_now)
      {
//        char *test=malloc(64);
        sprintf(upcoming, ">> %s <<", t->name);
        wsprintf(ws1,percent_t,upcoming);
//        mfree(test);
      }
      else
      wsprintf(ws1,percent_t,t->name);
      if (t->just_now)
      {
        wsInsertChar(ws1,0x0004,1);
        wsInsertChar(ws1,0xE008,1);
      }
      else
#else
      wsprintf(ws1,percent_t,t->name);
#endif
      if (t->isactive)
      {
        wsInsertChar(ws1,0x0002,1);
        wsInsertChar(ws1,0xE008,1);
      }
#ifdef USE_MLMENU
      if (t->xtext && t->xtext[0]!=0)
      {
	int i;
	zeromem(s,64);
	i=t->xtext[0];
	if (i>63) i=63;
	strncpy(s,t->xtext+1,i);
	wsprintf(ws3,"%c%t",0xE012,s);
      }
      else
	wsprintf(ws3,percent_d,t->uin);
      if ((t->xstate<total_xstatuses)&&(t->xstate))
      {
	wsInsertChar(ws3,FIRST_UCS2_BITMAP+t->xstate,1);
      }
#endif
    }
    else
    {
      int onlinetotal[2];
      GetOnTotalContact(t->group,onlinetotal);
#ifdef USE_MLMENU
      wsprintf(ws1,percent_t,t->name);
      wsprintf(ws3,"(%d/%d)",onlinetotal[0],onlinetotal[1]);
#else
      wsprintf(ws1,"%t%c%c(%d/%d)",t->name,0xE01D,0xE012,onlinetotal[0],onlinetotal[1]);
#endif
      if (t->state) icon++; //Модификация иконки группы
    }
  }
  else
  {
    wsprintf(ws1, LG_CLERROR);
  }
  ws2=AllocMenuWS(data,ws1->wsbody[0]);
  wstrcpy(ws2,ws1);

  SetMenuItemIconArray(data, item, S_ICONS+icon);
#ifdef USE_MLMENU
  ws4=AllocMenuWS(data,ws3->wsbody[0]);
  wstrcpy(ws4,ws3);
  SetMLMenuItemText(data, item, ws2, ws4, curitem);
#else
  SetMenuItemText(data, item, ws2, curitem);
#endif
}

//===============================================================================================
int DNR_ID=0;
int DNR_TRIES=3;

extern const char NATICQ_HOST[];
extern const unsigned int NATICQ_PORT;

int host_counter = 0;

//---------------------------------------------------------------------------
const char *GetHost(int cnt, const char *str, char *buf)
{
  const char *tmp = str, *begin, *end;
  if(cnt)
  {
    for(;cnt;cnt--)
    {
      for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
      if(!*str) str = tmp;
      for(;(*str==';' || *str==' ' || *str=='\x0D' || *str=='\x0A') && *str; str++);
      if(!*str) str = tmp;
    }
  }
  tmp = buf;
  begin = str;
  for(;*str!=';' && *str!=':' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
  end = str;
  for(;begin<end; *buf = *begin, begin++, buf++);
  *buf = 0;
  return tmp;
}
//---------------------------------------------------------------------------
int atoi(char *attr)
{
  int ret=0;
  int neg=1;
  for (int k=0; ; k++)
  {
    if ( attr[k]>0x2F && attr[k]<0x3A) {ret=ret*10+attr[k]-0x30;} else { if ( attr[k]=='-') {neg=-1;} else {return(ret*neg);}}
  }
}
//---------------------------------------------------------------------------
int GetPort(int cnt, const char *str)
{
  const char *tmp = str;
  char numbuf[6], numcnt = 0;
  if(cnt)
  {
    for(;cnt;cnt--)
    {
      for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
      if(!*str) str = tmp;
      for(;(*str==';' || *str==' ' || *str=='\x0D' || *str=='\x0A') && *str; str++);
      if(!*str) str = tmp;
    }
  }
  for(;*str!=';' && *str!=':' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
  if(*str!=':') return NATICQ_PORT;
  str++;
  numbuf[5] = 0;
  for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str && numcnt<5; numbuf[numcnt] = *str, str++, numcnt++);
  numbuf[numcnt] = 0;
  return atoi(numbuf);

}
//---------------------------------------------------------------------------
int GetHostsCount(const char *str)
{
  char cnt = 1;
  for(;cnt;cnt++)
  {
    for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
    if(!*str) return cnt;
    for(;(*str==';' || *str==' ' || *str=='\x0D' || *str=='\x0A') && *str; str++);
    if(!*str) return cnt;
  }
  return 0;

}
//---------------------------------------------------------------------------

void create_connect(void)
{
  char hostbuf[128];
  int hostport;
  int ***p_res=NULL;
  void do_reconnect(void);
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state = 0;
  int err;
  unsigned int ip;
  GBS_DelTimer(&reconnect_tmr);
  if (!IsGPRSEnabled())
  {
    is_gprs_online=0;
    strcpy(logmsg,LG_GRWAITFORGPRS);
    SMART_REDRAW();
    return;
  }
  DNR_ID=0;
  *socklasterr()=0;

  if(host_counter > GetHostsCount(NATICQ_HOST)-1) host_counter = 0;
  GetHost(host_counter, NATICQ_HOST, hostbuf);
  hostport = GetPort(host_counter, NATICQ_HOST);
  host_counter++;

//  sprintf(hostname, "%s:%d", hostbuf, hostport);
  strcpy(hostname, hostbuf);

  SMART_REDRAW();

  ip=str2ip(hostbuf);
  if (ip!=0xFFFFFFFF)
  {
    sa.ip=ip;
    strcpy(logmsg,"\nConnect by IP!");
    SMART_REDRAW();
    goto L_CONNECT;
  }
  strcpy(logmsg,LG_GRSENDDNR);
  SMART_REDRAW();
  err=async_gethostbyname(hostbuf,&p_res,&DNR_ID); //03461351 3<70<19<81
  if (err)
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (DNR_ID)
      {
        host_counter--;
	return; //Ждем готовности DNR
      }
    }
    else
    {
      snprintf(logmsg,255,LG_GRDNRERROR,err);
      SMART_REDRAW();
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
      return;
    }
  }
  if (p_res)
  {
    if (p_res[3])
    {
      strcpy(logmsg,LG_GRDNROK);
      SMART_REDRAW();
      DNR_TRIES=0;
      sa.ip=p_res[3][0][0];
    L_CONNECT:
      sock=socket(1,1,0);
      if (sock!=-1)
      {
	sa.family=1;
	sa.port=htons(hostport);
	//    sa.ip=htonl(IP_ADDR(82,207,89,182));
	if (connect(sock,&sa,sizeof(sa))!=-1)
	{
	  connect_state=1;
	  TOTALRECEIVED=0;
	  TOTALSENDED=0;
	  SMART_REDRAW();
	}
	else
	{
	  closesocket(sock);
	  sock=-1;
	  LockSched();
	  ShowMSG(1,(int)LG_MSGCANTCONN);
	  UnlockSched();
	  GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
	}
      }
      else
      {
	LockSched();
	ShowMSG(1,(int)LG_MSGCANTCRSC);
	UnlockSched();
	//Не осилили создания сокета, закрываем GPRS-сессию
	GPRS_OnOff(0,1);
      }
    }
  }
  else
  {
    DNR_TRIES--;
    LockSched();
    ShowMSG(1,(int)LG_MSGHOSTNFND);
    UnlockSched();
  }
}

#ifdef SEND_TIMER
GBSTMR send_tmr;
#endif

void ClearSendQ(void)
{
  mfree((void *)sendq_p);
  sendq_p=NULL;
  sendq_l=NULL;
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

#ifdef SEND_TIMER
static void resend(void)
{
  void SendAnswer(int dummy, TPKT *p);
  SUBPROC((void*)SendAnswer,0,0);
}
#endif

void SendAnswer(int dummy, TPKT *p)
{
  int i;
  int j;
  if (connect_state<2)
  {
    mfree(p);
    return;
  }
  if (p)
  {
    j=sizeof(PKT)+p->pkt.data_len; //Размер пакета
    TOTALSENDED+=j;
    ALLTOTALSENDED+=j;			//by BoBa 10.07
    //Проверяем, не надо ли добавить в очередь
    if (sendq_p)
    {
      //Есть очередь, добавляем в нее
      sendq_p=realloc((void *)sendq_p,sendq_l+j);
      memcpy((char *)sendq_p+sendq_l,p,j);
      mfree(p);
      sendq_l+=j;
      return;
    }
    sendq_p=p;
    sendq_l=j;
  }
  //Отправляем уже существующее в очереди
  while((i=sendq_l)!=0)
  {
    if (i>0x400) i=0x400;
    j=send(sock,(void *)sendq_p,i,0);
    snprintf(logmsg,255,"send res %d",j);
    SMART_REDRAW();
    if (j<0)
    {
      j=*socklasterr();
      if ((j==0xC9)||(j==0xD6))
      {
	//Передали что хотели
	strcpy(logmsg,"Send delayed...");
	return; //Видимо, надо ждать сообщения ENIP_BUFFER_FREE
      }
      else
      {
	//Ошибка
	LockSched();
	ShowMSG(1,(int)"Send error!");
	UnlockSched();
	end_socket();
	return;
      }
    }
    memcpy((void *)sendq_p,(char *)sendq_p+j,sendq_l-=j); //Удалили переданное
    if (j<i)
    {
      //Передали меньше чем заказывали
#ifdef SEND_TIMER
      GBS_StartTimerProc(&send_tmr,216*5,resend);
#endif
      return; //Ждем сообщения ENIP_BUFFER_FREE1
    }
    tenseconds_to_ping=0; //Чего-то послали, можно начинать отсчет времени до пинга заново
  }
  mfree((void *)sendq_p);
  sendq_p=NULL;
}

void send_login(int dummy, TPKT *p)
{
  connect_state=2;
  char rev[16];
  //Кто будет менять в этом месте идентификатор клиента, буду банить на уровне сервера!!!
  //А Вова будет банить на форуме!
  snprintf(rev,9,"Sie_%04d",__SVN_REVISION__);

  TPKT *p2=malloc(sizeof(PKT)+8);
  p2->pkt.uin=UIN;
  p2->pkt.type=T_SETCLIENT_ID;
  p2->pkt.data_len=8;
  memcpy(p2->data,rev,8);
  SendAnswer(0,p2);
  SendAnswer(dummy,p);
  RXstate=-(int)sizeof(PKT);
}

void do_ping(void)
{
  TPKT *pingp=malloc(sizeof(PKT));
  pingp->pkt.uin=UIN;
  pingp->pkt.type=0;
  pingp->pkt.data_len=0;
  SendAnswer(0,pingp);
}

void SendMSGACK(int i)
{
  TPKT *ackp=malloc(sizeof(PKT));
  ackp->pkt.uin=i;
  ackp->pkt.type=T_MSGACK;
  ackp->pkt.data_len=0;
  SendAnswer(0,ackp);
}

void RequestXText(unsigned int uin)
{
  TPKT *p=malloc(sizeof(PKT));
  p->pkt.uin=uin;
  p->pkt.type=T_XTEXT_REQ;
  p->pkt.data_len=0;
  SUBPROC((void *)SendAnswer,0,p);
}

void get_answer(void)
{
  void *p;
  int i=RXstate;
  int j;
  int n;
  char rb[1024];
  char *rp=rb;
  if (connect_state<2) return;
  if (i==EOP) return;
  j=recv(sock,rb,sizeof(rb),0);
  while(j>0)
  {
    if (i<0)
    {
      //Принимаем заголовок
      n=-i; //Требуемое количество байт
      if (j<n) n=j; //полученное<требуемое?
      memcpy(RXbuf.data+i,rp,n); //Копируем
      i+=n;
      j-=n;
      rp+=n;
    }
    if (i>=0)
    {
      //Принимаем тельце ;)
      n=RXbuf.pkt.data_len; //Всего в тельце
      if (n>16383)
      {
	//Слишком много
	strcpy(logmsg,LG_GRBADPACKET);
	end_socket();
	RXstate=EOP;
	return;
      }
      n-=i; //Количество требуемых байт (общая длинна тельца-текущая позиция)
      if (n>0)
      {
	if (j<n) n=j; //полученное<требуемое?
	memcpy(RXbuf.data+i,rp,n);
	i+=n;
	j-=n;
	rp+=n;
      }
      if (RXbuf.pkt.data_len==i)
      {
	//Пакет полностью получен
	TOTALRECEIVED+=(i+8);
	ALLTOTALRECEIVED+=(i+8);			//by BoBa 10.07
	//Пакет удачно принят, можно разбирать...
	RXbuf.data[i]=0; //Конец строки
	switch(RXbuf.pkt.type)
	{
	case T_LOGIN:
	  //Удачно залогинились
	  //Посылаем в MMI
	  n=i+sizeof(PKT)+1;
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  Play(sndStartup);
	  //        GBS_StartTimerProc(&tmr_ping,120*TMR_SECOND,call_ping);
	  snprintf(logmsg,255,LG_GRLOGINMSG,RXbuf.data);
	  connect_state=3;
          host_counter--; //Если уж законнектились, будем сидеть на этом сервере
	  SMART_REDRAW();
	  break;
	case T_XTEXT_ACK:
	case T_GROUPID:
	case T_GROUPFOLLOW:
	case T_CLENTRY:
	  //Посылаем в MMI
	  n=i+sizeof(PKT)+1;
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  //snprintf(logmsg,255,"CL: %s",RXbuf.data);
	  break;
	case T_STATUSCHANGE:
	  n=i+sizeof(PKT);
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  snprintf(logmsg,255,LG_GRSTATUSCHNG,RXbuf.pkt.uin,*((unsigned short *)(RXbuf.data)));
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  break;
	case T_ERROR:
	  snprintf(logmsg,255,LG_GRERROR,RXbuf.data);
	  SMART_REDRAW();
	  break;
	case T_RECVMSG:
	  n=i+sizeof(PKT)+1;
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  {
	    char *s=p;
	    s+=sizeof(PKT);
	    int c;
	    while((c=*s))
	    {
	      if (c<3) *s=' ';
	      s++;
	    }
	  }
	  snprintf(logmsg,255,LG_GRRECVMSG,RXbuf.pkt.uin,RXbuf.data);
	  SendMSGACK(TOTALRECEIVED);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  SMART_REDRAW();
#ifdef EVILFOX
#else
	  Play(sndMsg);
#endif
	  break;
	case T_SSLRESP:
	  LockSched();
	  ShowMSG(1,(int)RXbuf.data);
	  UnlockSched();
	  break;
	case T_SRV_ACK:
	  if (FindContactLOGQByAck(&RXbuf)) Play(sndMsgSent);
	case T_CLIENT_ACK:
	  p=malloc(sizeof(PKT)+2);
	  memcpy(p,&RXbuf,sizeof(PKT)+2);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  break;
	case T_ECHORET:
	  {
	    TDate d;
	    TTime t;
	    TTime *pt=(TTime *)(RXbuf.data);
	    int s1;
	    int s2;
	    GetDateTime(&d,&t);
	    s1=t.hour*3600+t.min*60+t.sec;
	    s2=pt->hour*3600+pt->min*60+pt->sec;
	    s1-=s2;
	    if (s1<0) s1+=86400;
	    snprintf(logmsg,255,"Ping %d-%d seconds!",s1,s1+1);
            sprintf(ping_txt, "Ping: %dsec",s1);
	    LockSched();
            if (show_ping==1)
            {
	    ShowMSG(1,(int)logmsg);
            show_ping=0;
            }
	    UnlockSched();
	  }
	  break;
        case T_LASTPRIVACY:
          n=i+sizeof(PKT);
          p=malloc(n);
          memcpy(p,&RXbuf,n);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  break;
	}
	i=-(int)sizeof(PKT); //А может еще есть данные
      }
    }
  }
  RXstate=i;
  //  GBS_StartTimerProc(&tmr_dorecv,3000,dorecv);
  //  SMART_REDRAW();
}

void AddStringToLog(CLIST *t, int code, char *s, const char *name, unsigned int IDforACK)
{
  char hs[128], *lastX;
  TTime tt;
  TDate d;
  GetDateTime(&d,&tt);
  int i;

  if (code==3 && NOT_LOG_SAME_XTXT)
  {
    if(!t->isactive && HISTORY_BUFFER) GetHistory(t, 64<<HISTORY_BUFFER);
    lastX = GetLastXTextLOGQ(t);
    if(lastX)
      if(strcmp(lastX, s) == 0) return;
  }

  snprintf(hs,127,"%02d:%02d %02d-%02d %s:\r\n",tt.hour,tt.min,d.day,d.month,name);
  if(code != 3 || LOG_XTXT) //Нужно сохранять иксстатус
    Add2History(t, hs, s, code); // Запись хистори
  LOGQ *p=NewLOGQ(s);
  snprintf(p->hdr,79,"%02d:%02d %02d-%02d %s:",tt.hour,tt.min,d.day,d.month,name);
  p->type=code;
  p->ID=IDforACK;  //0-32767
  i=AddLOGQ(&t->log,p);
  while(i>MAXLOGMSG)
  {
    if (t->log==t->last_log) t->last_log=t->last_log->next;
    RemoveLOGQ(&t->log,t->log);
    i--;
  }
  t->msg_count=i;
  if (!t->last_log) t->last_log=p;
  if (code==3)
  {
    if (edchat_id)
    {
      void *data=FindGUIbyId(edchat_id,NULL);
      if (data)
      {
	EDCHAT_STRUCT *ed_struct;
	ed_struct=EDIT_GetUserPointer(data);
	if (ed_struct)
	{
	  if (ed_struct->ed_contact==t)
	  {
	    goto L_INC;
	  }
	}
      }
    }
    goto L_NOINC;
  }
L_INC:
  if (!t->isunread) total_unread++;
#ifdef EVILFOX
  t->unread_msg++;
  total_unread2++;
#endif
  t->isunread=1;
L_NOINC:
  ChangeContactPos(t);
  time_draw=1;
}

void ParseAnswer(WSHDR *ws, const char *s);

int time_to_stop_t9;

void ParseXStatusText(WSHDR *ws, const char *s, int color)
{
  int c;
  int flag=0;
  CutWSTR(ws,0);
  if (strlen(s)==1) return;
  wsAppendChar(ws,0xE008);
  wsAppendChar(ws,color);
  wsAppendChar(ws,0xE013);
  while((c=*s++))
  {
    if (c==13)
    {
      if (!flag)
      {
        flag=1;
        wsAppendChar(ws,0xE012);
        c=' ';
      }
    }
    wsAppendChar(ws,char8to16(c));
  }
}
//Добавление итемов в чат при получении нового сообщения
void AddMsgToChat(void *data)
{
  LOGQ *p;
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  EDCHAT_STRUCT *ed_struct;
  int j;
  int color, font, type;
  int zc;
  if (!data) return;
  ed_struct=EDIT_GetUserPointer(data);
  if (!ed_struct) return;
  if (!ed_struct->ed_contact->isunread) return;


  p=ed_struct->ed_contact->last_log;
  if (p)
  {
    while(p)
    {
      font = ED_H_FONT_SIZE;
      if ((zc=p->acked&3))
      {
	if (zc==1)
	  color=ACK_COLOR; //Зеленый
	else
	  color=I_COLOR;
      }
      else
      {
	if (p->ID==0xFFFFFFFF)
        {
          type = p->type&0x0F;
          if(p->type&0x10)
          {
            color = (type==1)?O_I_COLOR:((type==3)?O_X_COLOR:O_TO_COLOR);
            font = (type==3)?O_ED_X_FONT_SIZE:O_ED_H_FONT_SIZE;
          }
          else
          {
            color = (type==1)?I_COLOR:((type==3)?X_COLOR:TO_COLOR);
            font = (type==3)?ED_X_FONT_SIZE:ED_H_FONT_SIZE;
          }
        }
        else
	  color=UNACK_COLOR; //Серый
      }
      PrepareEditControl(&ec);
      if ((p->type&0x0F)!=3)
      {
        ascii2ws(ews,p->hdr);
        ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
      }
      else
        ConstructEditControl(&ec,ECT_HEADER,ECF_DELSTR,ews,0);
      PrepareEditCOptions(&ec_options);
      SetPenColorToEditCOptions(&ec_options,color);
      SetFontToEditCOptions(&ec_options,font);
      CopyOptionsToEditControl(&ec,&ec_options);
      //AddEditControlToEditQend(eq,&ec,ma);
      EDIT_InsertEditControl(data,ed_struct->ed_answer-1,&ec);
      ed_struct->ed_answer++;
      if ((p->type&0x0F)!=3)
      {
        ParseAnswer(ews,p->text);
      }
      else
      {
        ParseXStatusText(ews, p->text, (p->type&0x10)?O_X_COLOR:X_COLOR);
      }
      PrepareEditControl(&ec);
      ConstructEditControl(&ec,
                           ECT_NORMAL_TEXT,
                           ews->wsbody[0] ? ECF_APPEND_EOL|ECF_DISABLE_T9 : ECF_DELSTR,
                           ews,ews->wsbody[0]);
      PrepareEditCOptions(&ec_options);
//#ifdef M75
      if ((p->type&0x0F)!=3)
      {
        SetFontToEditCOptions(&ec_options,(p->type&0x10)?O_ED_FONT_SIZE:ED_FONT_SIZE);
      }
      else
      {
        SetPenColorToEditCOptions(&ec_options,(p->type&0x10)?O_X_COLOR:X_COLOR);
        SetFontToEditCOptions(&ec_options,(p->type&0x10)?O_ED_X_FONT_SIZE:ED_X_FONT_SIZE);
      }
//#else
//      SetFontToEditCOptions(&ec_options,(p->type&0x10)?O_ED_FONT_SIZE:ED_FONT_SIZE);
//#endif
      CopyOptionsToEditControl(&ec,&ec_options);
      EDIT_InsertEditControl(data,ed_struct->ed_answer-1,&ec);
      ed_struct->ed_answer++;
      p=p->next;
    }
    j=((ed_struct->ed_contact->msg_count+1)*2); //Ожидаемый ed_answer
    while(j<ed_struct->ed_answer)
    {
      EDIT_RemoveEditControl(ed_struct->ed_chatgui,1);
      ed_struct->ed_answer--;
    }
  }
  ed_struct->ed_contact->last_log=NULL;
  if (IsGuiOnTop(edchat_id))
    total_unread--;
  else
    ed_struct->requested_decrement_total_unread++;
  ed_struct->ed_contact->isunread=0;
#ifdef EVILFOX
  total_unread2=total_unread2-ed_struct->ed_contact->unread_msg;
  ed_struct->ed_contact->unread_msg=0;
#endif
  ChangeContactPos(ed_struct->ed_contact);
  //  EDIT_SetFocus(data,ed_struct->ed_answer);
}

//Рисуем подтверждения непосредственно
void DrawAck(void *data)
{
  LOGQ *p;
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  EDCHAT_STRUCT *ed_struct;
  int j;
  int color;
  int dorefresh=0;
  if (!data) return;
  ed_struct=EDIT_GetUserPointer(data);
  if (!ed_struct) return;
  p=ed_struct->ed_contact->log;
  j=ed_struct->ed_answer;
  j-=(ed_struct->ed_contact->msg_count*2)+1; //Номер собственно хедера верхнего итема
  while(p)
  {
    if (j>=1) //Пока возможно лишнее
    {
      if (!(p->acked&4))
      {
	ExtractEditControl(data,j,&ec);
	PrepareEditCOptions(&ec_options);
	if (p->acked)
	{
	  if (p->acked==1)
	    color=ACK_COLOR; //Зеленый
	  else
	    color=I_COLOR;
	}
	else
	{
	  if (p->ID==0xFFFFFFFF)
	    color=(p->type&0x10)?(((p->type&0x0F)==1)?O_I_COLOR:O_TO_COLOR):(((p->type&0x0F)==1)?I_COLOR:TO_COLOR);
	  else
	    color=UNACK_COLOR; //Серый
	}
	SetPenColorToEditCOptions(&ec_options,color/*p->type==1?I_COLOR:TO_COLOR*/);
	SetFontToEditCOptions(&ec_options,(p->type&0x10)?O_ED_H_FONT_SIZE:ED_H_FONT_SIZE);
	CopyOptionsToEditControl(&ec,&ec_options);
	StoreEditControl(data,j,&ec);
	p->acked|=4; //Обработали
	dorefresh=1;
      }
    }
    j+=2;
    p=p->next;
  }
  if (IsGuiOnTop(edchat_id)&&dorefresh) RefreshGUI();
}

void ask_my_info(void)
{
  /*  TPKT *p;
  CLIST *t;
  p=malloc(sizeof(PKT));
  p->pkt.uin=UIN;
  p->pkt.type=T_REQINFOSHORT;
  p->pkt.data_len=0;
  //  AddStringToLog(t,0x01,"Request info...",I_str);
  SUBPROC((void *)SendAnswer,0,p);*/
}

void set_my_status(void)
{
  TPKT *p;
  p=malloc(sizeof(PKT)+1);
  p->pkt.uin=0;               // Никому; поле нужно проигнорировать на сервере
  p->pkt.type=T_MY_STATUS_CH; // Тип пакета: изменение статуса
  p->pkt.data_len=1;          // Длина пакета: 1 байт
  p->data[0]=CurrentStatus;
  SUBPROC((void *)SendAnswer,0,p);
}

void set_my_xstatus(void)
{
  TPKT *p;
  char *s1;
  char *s2;
  int l1;
  int l2;
  p=malloc(sizeof(PKT)+1);
  p->pkt.uin=0;               // Никому; поле нужно проигнорировать на сервере
  p->pkt.type=T_MY_XSTATUS_CH; // Тип пакета: изменение статуса
  p->pkt.data_len=1;          // Длина пакета: 1 байт
  p->data[0]=CurrentXStatus;
  SUBPROC((void *)SendAnswer,0,p);
  s1=GetXStatusStr(CurrentXStatus*3+1,&l1);
  s2=GetXStatusStr(CurrentXStatus*3+2,&l2);
  if ((!s1)||(!s2)) return;
  p=malloc(sizeof(PKT)+l1+l2+1);
  p->pkt.uin=0;
  p->pkt.type=T_XTEXT_SET;
  p->pkt.data_len=l1+l2+1;
  strncpy(p->data+0,s1,l1);
  p->data[l1]=0;
  strncpy(p->data+l1+1,s2,l2);
  SUBPROC((void *)SendAnswer,0,p);
}

void to_develop(void)
{
  if (silenthide) return;
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)maincsm_id;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
}

void ReqAddMsgToChat(CLIST *t)
{
  if (edchat_id)
  {
    void *data=FindGUIbyId(edchat_id,NULL);
    {
      EDCHAT_STRUCT *ed_struct;
      ed_struct=EDIT_GetUserPointer(data);
      if (ed_struct)
      {
        if (ed_struct->ed_contact==t)
        {
          if (EDIT_IsBusy(data))
          {
            t->req_add=1;
            time_to_stop_t9=3;
          }
          else
          {
            AddMsgToChat(data);
            DirectRedrawGUI_ID(edchat_id);
	  }
	}
      }
    }
  }
}

void CheckComand(char *txt, CLIST *t, char *ddd)
{
  comanda=1;
  if(!strcmp(txt, "GET_ONLINE_TIME"))
  {
    comanda=0;
    TPKT *p;
    sprintf(online_txt, "online: %02d:%02d:%02d \nServer: %s", hours, minutes, seconds, hostname);
    p=malloc(sizeof(PKT)+strlen(online_txt)+1);
    p->pkt.uin=t->uin;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(online_txt);
    strcpy(p->data,online_txt);
    SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
    return;
  }
  if(!strcmp(txt, "GET_MSG_INFO"))
  {
    comanda=0;
    TPKT *p;
    char *send_txt=malloc(64);
    sprintf(send_txt, "sent: %d \n"
            "recieved: %d"
              , out_count, in_count);
    p=malloc(sizeof(PKT)+strlen(send_txt)+1);
    p->pkt.uin=t->uin;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(send_txt);
    strcpy(p->data,send_txt);
    SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
    mfree(send_txt);
    return;
  }
  if(!strcmp(txt, "GET_MOD_INFO"))
  {
    comanda=0;
    TPKT *p;
    char *send_txt=malloc(256);
    strcpy(send_txt, mod_info);
    p=malloc(sizeof(PKT)+strlen(send_txt)+1);
    p->pkt.uin=t->uin;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(send_txt);
    strcpy(p->data,send_txt);
      SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
    mfree(send_txt);
    return;
  }
  if(!strcmp(txt, "GET_BAT_INFO"))
  {
    comanda=0;
    TPKT *p;
    int bat;
    bat=*RamCap();
    char *send_txt=malloc(64);
    sprintf(send_txt, "battery: %d percents", bat);
    p=malloc(sizeof(PKT)+21+1);
    p->pkt.uin=t->uin;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(send_txt);
    strcpy(p->data,send_txt);
    SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
    mfree(send_txt);
    return;
  }
  if(away_m==1)
  {
    TPKT *p;
    sprintf(away_msg, "AutoMsg: %s %s! im not here! %s %s",away_msg1, t->name, away_msg2, away_msg_time);
    p=malloc(sizeof(PKT)+strlen(away_msg)+1);
    p->pkt.uin=t->uin;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(away_msg);
    strcpy(p->data,away_msg);
    SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
  }
}

ProcessPacket(TPKT *p)
{
  extern const int VIBR_TYPE, VIBR_ON_CONNECT;
  CLIST *t;
  LOGQ *q;
  char s[256];
  switch(p->pkt.type)
  {
  case T_LOGIN:
    set_my_status();
    set_my_xstatus();
    break;
  case T_CLENTRY:
    if (p->pkt.uin)
    {
      if ((t=FindContactByUin(p->pkt.uin)))
      {
	//        t->state=0xFFFF;
        strncpy(t->name,p->data,63);
	t->group=GROUP_CACHE;
	ChangeContactPos(t);
	RecountMenu(t, 1);
      }
      else
      {
        RecountMenu(AddContact(p->pkt.uin,p->data), 1);
      }
    }
    else
    {
      if(VIBR_ON_CONNECT)
      {
        vibra_count=1;
        start_vibra();
      }
      GROUP_CACHE=0;
      ask_my_info();
      if (contactlist_menu_id)
      {
	RecountMenu(NULL, 1);
      }
      else
        create_contactlist_menu();
    }
    break;
  case T_GROUPID:
    if (t=FindGroupByID(GROUP_CACHE=p->pkt.uin))
    {
      strncpy(t->name,p->data,63);
      ChangeContactPos(t);
      RecountMenu(t, 1);
    }
    else
    {
      RecountMenu(AddGroup(p->pkt.uin,p->data), 1);
    }
    break;
  case T_GROUPFOLLOW:
    GROUP_CACHE=p->pkt.uin;
    break;
  case T_STATUSCHANGE:
    t=FindContactByUin(p->pkt.uin);
    if (t)
    {
      int i=t->state;
      CLIST *oldt=NULL;
      if (t->xstate!=p->data[2])  // Если картинка икс статуса сменилась
      {
        t->xstate=p->data[2];
        FreeXText(t);
        if (t->xstate && ENA_AUTO_XTXT)   // Если установлен икс статус и можно запрашивать по смене икс статуса :)
        {
          t->req_xtext=1;
          if (edchat_id)   // Если открыт чат
          {
            void *data=FindGUIbyId(edchat_id,NULL);
            if (data)
            {
              EDCHAT_STRUCT *ed_struct=EDIT_GetUserPointer(data);
              if (ed_struct)
              {
                if (ed_struct->ed_contact==t)   // Если наш чат то запрашиваем текст статуса
                {
                  t->req_xtext=0;
                  RequestXText(t->uin);
                }
              }
	    }
	  }
	}
        else  // Если икс статус не установлен то на всякий случай снимаем флаг получения текста
        {
          t->req_xtext=0;
        }
      }
      if (contactlist_menu_id)
      {
	oldt=FindContactByN(GetCurMenuItem(FindGUIbyId(contactlist_menu_id,NULL)));
      }
      t->state=*((unsigned short *)(p->data));
      LogStatusChange(t);
      ChangeContactPos(t);
      RecountMenu(oldt, 1);
      if ((t->state!=0xFFFF)&&(i==0xFFFF))//Звук
      {
#ifdef EVILFOX
        if(!t->just_now)
        {
          total_c_online++;
          UpdateCLheader();
          if (IsGuiOnTop(contactlist_menu_id)) RefreshGUI();
        }
        if(Is_INC_On)
        {     
          strcpy(show_nick, t->name);
#ifdef NEWSGOLD
          if(!IsIdleUiOnTop()) 
#else
          #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
          CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
          if (!IsGuiOnTop(idlegui_id))
#endif
          {
            int csm_oncreate_addr = ((int*)(((CSM_RAM*)(CSM_root()->csm_q->csm.last))->constr))[1] - 1;
            char java_oncreate_pattern[8] = {0xB0, 0xB5, 0x04, 0x1C, 0x00, 0x25, 0x05, 0x61};
            if (memcmp((void*)csm_oncreate_addr, java_oncreate_pattern, 8))
            {
              INC_show=15;
              pp_color=2;
              show_pp_sender();
            }
          }
        }
        t->just_now=2;
        
#endif
	Play(sndGlobal);
      }
      if ((i!=0xFFFF)&&(t->state==0xFFFF))//Звук
      {
	Play(sndSrvMsg);
      }
    }
    if (edchat_id)
    {
      void *data=FindGUIbyId(edchat_id,NULL);
      {
	EDCHAT_STRUCT *ed_struct;
	ed_struct=EDIT_GetUserPointer(data);
	if (ed_struct)
	{
	  if (ed_struct->ed_contact==t)
	  {
	    DirectRedrawGUI_ID(edchat_id);
	  }
	}
      }
    }
    break;
  case T_RECVMSG:
    t=FindContactByUin(p->pkt.uin);
    if (!t)
    {
      sprintf(s,percent_d,p->pkt.uin);
      t=AddContact(p->pkt.uin,s);
    }
    if(!t->isactive && HISTORY_BUFFER) GetHistory(t, 64<<HISTORY_BUFFER);
    t->isactive=ACTIVE_TIME;
#ifdef EVILFOX
    if(t->ext_snd)
    {
      sprintf(ext_sound, "%s%d.wav", sndMsg2, t->uin);
      Play(ext_sound);
    }
    else
    Play(sndMsg);
#endif
#ifdef ELKA
      SLI_Timer();
#endif    
    if(VIBR_TYPE)
      vibra_count=2;
    else
      vibra_count=1;
    start_vibra();
#ifdef EVILFOX
    if(Is_ILU_On)
#endif
    IlluminationOn(ILL_DISP_RECV,ILL_KEYS_RECV,ILL_RECV_TMR,ILL_RECV_FADE); //Illumination by BoBa 19.04.2007
    if (t->name[0]=='#')
    {
      //Если это конференция, патчим имя
      char *s=strchr(p->data,'>');
      //Если нашли символ > и после него пробел и ник короче 16 символов
      if (s)
      {
	if ((s[1]==' ')&&((s-p->data)<16))
	{
	  *s=0; //Режем строку
	  AddStringToLog(t,0x02,s+2,p->data,0xFFFFFFFF); //Добавляем имя из текста сообщения
	  goto L1;
	}
      }
    }
#ifdef EVILFOX
    CheckComand(p->data, t, t->name);
    if(comanda)
    {
#endif
    AddStringToLog(t,0x02,p->data,t->name,0xFFFFFFFF);
    in_count++;
#ifdef EVILFOX
    if(Is_INC_On)
      {     
        strcpy(show_nick, t->name);
#ifdef NEWSGOLD
        if(!IsIdleUiOnTop()) 
#else
        #define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
        CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
        if (!IsGuiOnTop(idlegui_id))
#endif
        {
          int csm_oncreate_addr = ((int*)(((CSM_RAM*)(CSM_root()->csm_q->csm.last))->constr))[1] - 1;
          char java_oncreate_pattern[8] = {0xB0, 0xB5, 0x04, 0x1C, 0x00, 0x25, 0x05, 0x61};
          if (memcmp((void*)csm_oncreate_addr, java_oncreate_pattern, 8))
          {
            INC_show=15;
            pp_color=0;
            show_pp_sender();
          }
        }
      }
    if(Is_DRAWMAIN_On)
      AddToMain(t->name,p->data);
    }
#endif
    L1:
    //Разворачиваем группу, в которой пришло сообщение
    {
      CLIST *g=FindGroupByID(t->group);
      if (g)
      {
	if (g->state)
	{
	  g->state=0;
	}
      }
    }
    ReqAddMsgToChat(t);
    RecountMenu(t, 1);
    extern const int DEVELOP_IF;
    switch (DEVELOP_IF)
    {
    case 0:
      if ((((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=maincsm_id)) to_develop();
      break;
    case 1:
      if ((((CSM_RAM *)(CSM_root()->csm_q->csm.last))->id!=maincsm_id)&&(IsUnlocked())) to_develop();
      break;
    case 2:
      break;
    }
    break;
  case T_SRV_ACK:
  case T_CLIENT_ACK:
    q=FindContactLOGQByAck(p);
    if (q&&(p->pkt.type==T_SRV_ACK)&&Is_ILU_On) IlluminationOn(ILL_DISP_SEND,ILL_KEYS_SEND,ILL_SEND_TMR,ILL_RECV_FADE); //Illumination by BoBa 19.04.2007
/*    if ((
	IsGuiOnTop(contactlist_menu_id)||
	  IsGuiOnTop(edchat_id)
	    )&&(q))
    {
      DrawRoundedFrame(ScreenW()-8,YDISP,ScreenW()-1,YDISP+7,0,0,0,
		       GetPaletteAdrByColorIndex(0),
		       GetPaletteAdrByColorIndex(p->pkt.type==T_SRV_ACK?3:4));
    }*/
    if (q)
    {
      q->acked=p->pkt.type==T_SRV_ACK?1:2;
      t=FindContactByUin(p->pkt.uin);
      if (edchat_id)
      {
	void *data=FindGUIbyId(edchat_id,NULL);
	if (data)
	{
	  EDCHAT_STRUCT *ed_struct;
	  ed_struct=EDIT_GetUserPointer(data);
	  if (ed_struct)
	  {
	    if (ed_struct->ed_contact==t)
	    {
	      if (EDIT_IsBusy(data))
	      {
		t->req_drawack=1;
		time_to_stop_t9=3;
	      }
	      else
		DrawAck(data);
	    }
	  }
	}
      }
    }
    break;
  case T_XTEXT_ACK:
    t=FindContactByUin(p->pkt.uin);
    if (t)
    {
      int i;
      int j;
      FreeXText(t);
      i=p->pkt.data_len;
      memcpy(t->xtext=malloc(i),p->data,i);
      zeromem(s,256);
      strcpy(s,t->name);
      strcat(s,":\n");
      i=strlen(s);
      j=p->data[0];
      if (j>(255-i)) j=255-i;
      strncpy(s+i,p->data+1,j);
      i+=j;
      if (i<255)
      {
	s[i]='\n';
	i++;
	j=p->pkt.data_len-p->data[0]-1;
	if (j>(255-i)) j=255-i;
	strncpy(s+i,p->data+p->data[0]+1,j);
      }
#ifdef EVILFOX
#else
//      if (IsGuiOnTop(contactlist_menu_id)) RefreshGUI();
      if (!edchat_id &&           // Только если редактор не наверху
          strlen(p->data))       // и x-status не пустой
          ShowMSG(0,(int)s);
#endif
      zeromem(s,256);
      i=0;
      j=p->data[0];
      if (j>(255-i)) j=255-i;
      strncpy(s,p->data+1,j);
      i+=j;
      if (i<255)
      {
	s[i++]=13;
	j=p->pkt.data_len-p->data[0]-1;
	if (j>(255-i)) j=255-i;
	strncpy(s+i,p->data+p->data[0]+1,j);
      }
      AddStringToLog(t,0x03,s,x_status_change,0xFFFFFFFF);
      ReqAddMsgToChat(t);
      if (strlen(p->data))       // Если x-status не пустой
        RecountMenu(t, 1);
      else
        RecountMenu(NULL, 0);
    }
    break;
  case T_LASTPRIVACY:
    CurrentPrivateStatus=p->data[0];
    break;
  }
  mfree(p);
}


IPC_REQ tmr_gipc;
void process_active_timer(void)
{
#ifdef EVILFOX
  msg_away_timer++;
  if((msg_away_timer==AUTO_ENGADE)&&(Auto_Status==1))
    away_engage();
#endif
  if (connect_state>2)
  {
    if (++tenseconds_to_ping>12)
    {
      tenseconds_to_ping=0;
      SUBPROC((void *)do_ping);
    }
  }
#ifdef EVILFOX
  if((ping_sec>=6)&&(Show_Ping))
  {
    ping_sec=0;
    PingToServer2();
  }
  else
    ping_sec++;
#endif
  tmr_gipc.name_to=ipc_my_name;
  tmr_gipc.name_from=ipc_my_name;
  tmr_gipc.data=NULL;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_TENSECONDS,&tmr_gipc);
  GBS_StartTimerProc(&tmr_active,TMR_SECOND*10,process_active_timer);
}

//===============================================================================================
void method0(MAIN_GUI *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();
/*  DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(20));*/

  DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,
		   GetPaletteAdrByColorIndex(1),
		   GetPaletteAdrByColorIndex(1));
#ifdef EVILFOX_2
#else
  DrawImg(0,0,S_ICONS[ICON_LOGO]);
#endif
  unsigned long RX=ALLTOTALRECEIVED; unsigned long TX=ALLTOTALSENDED;			//by BoBa 10.07
  wsprintf(data->ws1,LG_GRSTATESTRING,connect_state,RXstate,RX,TX,sendq_l,hostname,logmsg);
  if (total_smiles)
  {
    wstrcatprintf(data->ws1,"\nLoaded %d smiles",total_smiles);
  }
  if (xstatuses_load)
  {
    wstrcatprintf(data->ws1,"\nLoaded %d xstatus",total_xstatuses);
  }
  DrawString(data->ws1,3,3+YDISP,scr_w-4,scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
	     FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(data->ws2,percent_t,LG_GRSKEYEXIT);
#else
  wsprintf(data->ws2,percent_t,cltop?LG_GRSKEYCLIST:empty_str);
#endif
  DrawString(data->ws2,(scr_w >> 1),scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
	     scr_w-4,scr_h-4,FONT_MEDIUM_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(data->ws2,percent_t,cltop?LG_GRSKEYCLIST:empty_str);
#else  
  wsprintf(data->ws2,percent_t,LG_GRSKEYEXIT);
#endif
  DrawString(data->ws2,3,scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
	     scr_w>>1,scr_h-4,FONT_MEDIUM_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX_2
  DrawImg(15,220,(int)"4:\\zbin\\naticq\\img\\smiles_logo.png");
#endif
#ifdef EVILFOX 
  wsprintf(data->ws2,percent_t,"Mod by Evilfox 2nd");
  DrawString(data->ws2,3,scr_h-8-GetFontYSIZE(FONT_MEDIUM_BOLD)-GetFontYSIZE(FONT_MEDIUM_BOLD),
	     scr_w-4,scr_h-4,FONT_MEDIUM_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#endif
}

void method1(MAIN_GUI *data,void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void method2(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void method3(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void method4(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

int method5(MAIN_GUI *data,GUI_MSG *msg)
{
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case LEFT_SOFT:
#ifdef EVILFOX
      if (cltop) create_contactlist_menu();
      break;
#else
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
#endif
    case RIGHT_SOFT:
#ifdef EVILFOX
      return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
#else
      if (cltop) create_contactlist_menu();
      break;
#endif
    case GREEN_BUTTON:
      disautorecconect=0;
      if ((connect_state==0)&&(sock==-1))
      {
        GBS_DelTimer(&reconnect_tmr);
	DNR_TRIES=3;
        SUBPROC((void *)create_connect);
      }
      break;
    case '0':
      SUBPROC((void*)end_socket);
      GBS_DelTimer(&reconnect_tmr);
      DNR_TRIES=3;
      SUBPROC((void *)create_connect);
      break;
    }
  }
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,  //Redraw
  (void *)method1,  //Create
  (void *)method2,  //Close
  (void *)method3,  //Focus
  (void *)method4,  //Unfocus
  (void *)method5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  strcpy(LG_MENU2, "Меню");
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
//  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  maingui_id=csm->gui_id=CreateGUI(main_gui);
  ews=AllocWS(16384);
  //  MutexCreate(&contactlist_mtx);
  DNR_TRIES=3;
  //  SUBPROC((void *)InitSmiles);
  //  SUBPROC((void *)create_connect);
  GBS_StartTimerProc(&tmr_active,TMR_SECOND*10,process_active_timer);
  sprintf((char *)ipc_my_name+6,percent_d,UIN);
  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
}

void maincsm_onclose(CSM_RAM *csm)
{
  WriteDefSettings();
  //  SaveConfigData(successed_config_filename);

/*
  #pragma segment="CONFIG_C"
  unsigned int ul;
  int f;
  extern const CFG_HDR cfghdr0; //first var in CONFIG
  void *cfg=(void*)&cfghdr0;
  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if ((f=fopen("4:\\ZBin\\etc\\NATICQ.bcfg",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))==-1){
   f=fopen("0:\\ZBin\\etc\\NATICQ.bcfg",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul);
  }
  fwrite(f,cfg,len,&ul);
  fclose(f,&ul);
*/

  //  GBS_DelTimer(&tmr_dorecv);
  GBS_DelTimer(&tmr_active);
//  GBS_DelTimer(&tmr_ping);
#ifdef EVILFOX
#ifdef ELKA
  GBS_DelTimer(&mytmr);
#endif
  GBS_DelTimer(&ctmr);
  GBS_DelTimer(&incs);
  RemoveKeybMsgHook((void *)my_keyhook);
#endif
  GBS_DelTimer(&tmr_vibra);
  GBS_DelTimer(&reconnect_tmr);
  GBS_DelTimer(&tmr_illumination);
  SetVibration(0);
  FreeTemplates();
  FreeCLIST();
  free_ICONS();
  //  FreeSmiles();
  FreeWS(ews);
  FreeXStatusText();
  //  MutexDestroy(&contactlist_mtx);
  SUBPROC((void *)FreeSmiles);
  SUBPROC((void *)FreeXStatusesImg);
  SUBPROC((void *)end_socket);
  SUBPROC((void *)ClearSendQ);
  SUBPROC((void *)ElfKiller);
}

void do_reconnect(void)
{
  if (is_gprs_online)
  {
    DNR_TRIES=3;
    SUBPROC((void*)create_connect);
  }
}

void CheckDoubleRun(void)
{
  int csm_id;
  if ((csm_id=(int)(gipc.data))!=-1)
  {
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)csm_id;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
    LockSched();
    CloseCSM(maincsm_id);
    //ShowMSG(1,(int)LG_ALREADY_STARTED);
    UnlockSched();
  }
  else
  {
    InitXStatusesImg();
    //InitSmiles(); Это вызовется из InitXStatusesImg
    create_connect();
  }
}

int maincsm_onmessage(CSM_RAM *data,GBS_MSG *msg)
{
  extern const int VIBR_ON_CONNECT;

  //  char ss[100];
  MAIN_CSM *csm=(MAIN_CSM*)data;
  {
    //IPC
    if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
	if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
	{
	  switch (msg->submess)
	  {
	  case IPC_CHECK_DOUBLERUN:
	    //Если приняли свое собственное сообщение, значит запускаем чекер
	    if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
            else ipc->data=(void *)maincsm_id;
	    break;
	  case IPC_SMILE_PROCESSED:
	    //Только собственные смайлы ;)
	    if (ipc->name_from==ipc_my_name) SUBPROC((void *)ProcessNextSmile);
	    SMART_REDRAW();
	    break;
	  case IPC_XSTATUSIMG_PROCESSED:
	    //Только собственные иксстатусы ;)
	    if (ipc->name_from==ipc_my_name) SUBPROC((void *)ProcessNextXStatImg);
	    SMART_REDRAW();
	    break;
	  case IPC_TENSECONDS:
	    //Только свое сообщение
	    if (ipc->name_from==ipc_my_name)
	    {
	      CLIST *t=(CLIST *)cltop;
	      int f=0;
	      while(t)
	      {
                if(t->just_now)
                {
                  if (!(--(t->just_now))) {
                    f=1;
#ifdef EVILFOX
                    total_c_online--;
#endif
                  }
                }
		if (t->isactive)
		{
		  if (!(--(t->isactive))) f=1; //Если дошли до 0 хотя бы один раз - надо перерисовать меню
		}
		t=(CLIST *)(t->next);
	      }
	      if (f)
	      {
		CLIST *oldt=NULL;
		if (contactlist_menu_id)
		{
		  oldt=FindContactByN(GetCurMenuItem(FindGUIbyId(contactlist_menu_id,NULL)));
		}
		RecountMenu(oldt, 1);
	      }
	      if (time_to_stop_t9)
	      {
		if (!(--time_to_stop_t9))
		{
		  if (IsGuiOnTop(edchat_id)) RefreshGUI();
		}
	      }
	    }
	    break;
#ifdef EVILFOX
#else
     	  case IPC_SENDMSG: ;                                   //IPC_SENDMSG by BoBa 26.06.07
            int l=strlen(((IPCMsg *)(ipc->data))->msg);
            TPKT *msg=malloc(sizeof(PKT)+l);
            msg->pkt.uin=((IPCMsg *)(ipc->data))->uin;
            msg->pkt.type=T_SENDMSG;
            msg->pkt.data_len=l;
            memcpy(msg->data,((IPCMsg *)(ipc->data))->msg,l);
            //slientsend=1;
	    SENDMSGCOUNT++; //Номер сообщения
            SUBPROC((void *)SendAnswer,0,msg);
            break;
#endif
	  }
	}
      }
    }
    //Нарисуем иконочку моего статуса
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop(idlegui_id)/*&&IsUnlocked()*/) //Если IdleGui на самом верху
    {
      GUI *igui=GetTopGUI();
      if (igui) //И он существует
      {
////	void *canvasdata=BuildCanvas();
        canvasdata=BuildCanvas();
	int icn;
#ifdef EVILFOX
        if(time_draw)
        {
#endif
	if (total_unread)
	  icn=IS_MSG;
	else
	{
	  switch(connect_state)
	  {
	  case 0:
	    icn=IS_OFFLINE; break;
	  case 3:
	    icn=CurrentStatus; //IS_ONLINE;
	    break;
	  default:
	    icn=IS_UNKNOWN; break;
	  }
	}

	//Тут трохи поменял
	// by Rainmaker: Рисуем канву только для иконки и выводим в своих координатах
        if((icon_change)||(total_unread)||(connect_state!=3))
        {
	DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)S_ICONS[icn])-1,
		   IDLEICON_Y+GetImgHeight((int)S_ICONS[icn])-1,1);
	DrawImg(IDLEICON_X,IDLEICON_Y,S_ICONS[icn]);
        }
        else
        {
          PNGTOP_DESC *pltop=PNG_TOP();
          pltop->dyn_pltop=XStatusesImgList;
          DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)XStatusesIconArray[CurrentXStatus])-1,
		   IDLEICON_Y+GetImgHeight((int)XStatusesIconArray[CurrentXStatus])-1,1);
	  DrawImg(IDLEICON_X,IDLEICON_Y,XStatusesIconArray[CurrentXStatus]);
        }
#ifdef EVILFOX_2
          DrawImg(IDLEICON_X-1,IDLEICON_Y-8,(int)"4:\\zbin\\naticq\\img\\naticq_ms.png");
#endif
#ifdef EVILFOX
          if(connect_state==3)
          sprintf(online_txt, "online: %02d:%02d:%02d", hours, minutes, seconds);
          else
            sprintf(online_txt ,"Offline");
          if(Is_Online_On)
          PrintField(ONTIME_X,ONTIME_Y, online_txt, align, fonto, spaco1r);
          if(Show_Ping)
            PrintField(PING_X,PING_Y, ping_txt, align, fonto, spaco1r);
          if(Is_Unread_On)
          {
            sprintf(unread_txt, "Unread: %d", total_unread2);
            PrintField(UNREAD_X,UNREAD_Y, unread_txt, align, fonto, spaco1r);
          }
          if(Is_DRAWMAIN_On&&main_d)
          {
            if(fonto==1)
            {
            PrintField(MSG_X,MSG_Y, a_txt, align, fonto, spaco2);
            PrintField(MSG_X,MSG_Y+paused_height+1, s_txt, align, fonto, spaco2);
            PrintField(MSG_X,MSG_Y+(2*paused_height)+2, d_txt, align, fonto, spaco2);
            PrintField(MSG_X,MSG_Y+(3*paused_height)+3, f_txt, align, fonto, spaco2);
            PrintField(MSG_X,MSG_Y+(4*paused_height)+4, g_txt, align, fonto, spaco2);
            }
            else
            {
              PrintField(MSG_X,MSG_Y, a_txt, align, fonto, spaco1r);
              PrintField(MSG_X,MSG_Y+GetFontYSIZE(paused_height)+1, s_txt, align, fonto, spaco1r);
              PrintField(MSG_X,MSG_Y+(2*GetFontYSIZE(paused_height))+2, d_txt, align, fonto, spaco1r);
              PrintField(MSG_X,MSG_Y+(3*GetFontYSIZE(paused_height))+3, f_txt, align, fonto, spaco1r);
              PrintField(MSG_X,MSG_Y+(4*GetFontYSIZE(paused_height))+4, g_txt, align, fonto, spaco1r);
            }
            main_d=0;
          }
          icon_change2=!(icon_change2);
          if(icon_change2)
          icon_change=!(icon_change);
          time_draw=0;
        }
#endif
      }
    }
#ifdef EVILFOX
    else
    {
      time_draw=1;
      main_d=1;
    }
#endif
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"NatICQ config updated!");
      InitConfig();
#ifdef EVILFOX
      FontPathFree();
      FontPathInit(fonto,(char *)fontpath, 0);
      if(fonto==1)
      {
        spaco1r=spaco1;
        char *heght=malloc(64);
        sprintf(heght, "%s2240.png", fontpath);
        paused_height=GetImgHeight((int)heght);
        mfree(heght);
      }
      else
      {
        spaco1r=10001+(system_color*100);
        paused_height=fonto-100;
      }
      init_time_zone();
#endif
      free_ICONS();
      setup_ICONS();
      ResortCL();
      RecountMenu(NULL, 1);
      //      InitSmiles();
    }
  }
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    if ((int)msg->data0==contactlist_menu_id)
    {
      contactlist_menu_id=0;
      prev_clmenu_itemcount=0;
    }
    if ((int)msg->data0==edchat_id)
    {
      edchat_id=0;
    }
  }
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    switch((int)msg->data0)
    {
    case LMAN_DISCONNECT_IND:
      is_gprs_online=0;
      return(1);
    case LMAN_CONNECT_CNF:
      vibra_count=1;
      start_vibra();
      is_gprs_online=1;
      strcpy(logmsg,LG_GRGPRSUP);
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
      return(1);
    case ENIP_DNR_HOST_BY_NAME:
      if ((int)msg->data1==DNR_ID)
      {
	if (DNR_TRIES) SUBPROC((void *)create_connect);
      }
      return(1);
    }
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      if ((((unsigned int)msg->data0)>>28)==0xA)
      {
	//Принят пакет
	ProcessPacket((TPKT *)msg->data0);
	return(0);
      }
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
	if (connect_state==1)
	{
	  if(VIBR_ON_CONNECT)
            vibra_count=2;
          else
            vibra_count=1;
	  start_vibra();
	  //Соединение установленно, посылаем пакет login
	  strcpy(logmsg, LG_GRTRYLOGIN);
	  {
	    int i=strlen(PASS);
	    TPKT *p=malloc(sizeof(PKT)+i);
	    p->pkt.uin=UIN;
	    p->pkt.type=T_REQLOGIN;
	    p->pkt.data_len=i;
	    memcpy(p->data,PASS,i);
	    SUBPROC((void *)send_login,0,p);
	  }
	  GROUP_CACHE=0;
	  SENDMSGCOUNT=0; //Начинаем отсчет
	  if (!FindGroupByID(0)) AddGroup(0,LG_GROUPNOTINLIST);
	  if (!FindContactByUin(UIN)) AddContact(UIN, LG_CLLOOPBACK);
	  SMART_REDRAW();
	}
	else
	{
	  ShowMSG(1,(int)LG_MSGILLEGMSGCON);
	}
	break;
      case ENIP_SOCK_DATA_READ:
	if (connect_state>=2)
	{
	  //Если посылали send
	  SUBPROC((void *)get_answer);
	  //SMART_REDRAW();
	}
	else
	{
	  ShowMSG(1,(int)LG_MSGILLEGMSGREA);
	}
	break;
      case ENIP_BUFFER_FREE:
      case ENIP_BUFFER_FREE1:
	SUBPROC((void *)SendAnswer,0,0);
	break;
      case ENIP_SOCK_REMOTE_CLOSED:
	//Закрыт со стороны сервера
	if (connect_state)
	  SUBPROC((void *)end_socket);
	break;
      case ENIP_SOCK_CLOSED:
	//strcpy(logmsg, "No connection");
	//Dump not received
/*	if (RXstate>(-(int)sizeof(PKT)))
	{
	  unsigned int err;
	  int f=fopen("4:\\NATICQ.dump",A_ReadWrite+A_Create+A_Truncate+A_BIN,P_READ+P_WRITE,&err);
	  if (f!=-1)
	  {
	    fwrite(f,&RXbuf,RXstate+sizeof(PKT),&err);
	    fclose(f,&err);
	  }
	}*/
	FillAllOffline();
	RecountMenu(NULL, 1);
	connect_state=0;
	sock=-1;
        if(VIBR_ON_CONNECT)
          vibra_count=4;
        else
          vibra_count=1;

	start_vibra();
	if (sendq_p)
	{
	  snprintf(logmsg,255,"Disconnected, %d bytes not sended!",sendq_l);
	}
	SMART_REDRAW();
	SUBPROC((void *)ClearSendQ);
	if (!disautorecconect)
        {
          GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
          snprintf(logmsg,255,"%s\nReconect after 10 second...",logmsg);
        }
	break;
      }
    }
  }
  return(1);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "NATICQ: %d",UIN);
}


int main(char *filename)
{
  MAIN_CSM main_csm;
  char *s;
  int len;
  extern const char *successed_config_filename;
  WSHDR *ws;

  InitConfig();
  s=strrchr(filename,'\\');
  len=(s-filename)+1;
  strncpy(elf_path,filename,len);
  elf_path[len]=0;
  if (!UIN)
  {
    LockSched();
    ShowMSG(1,(int)LG_MSGNOUINPASS);
    ws=AllocWS(150);
    str_2ws(ws,successed_config_filename,128);
    ExecuteFile(ws,0,0);
    UnlockSched();
    SUBPROC((void *)ElfKiller);
    return 0;
  }
  ReadDefSettings();
  setup_ICONS();
  LoadXStatusText();
  UpdateCSMname();
  LockSched();
  maincsm_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
#ifdef EVILFOX
  time_counter();
  FontPathInit(fonto,(char *)fontpath, 1);
  if(fonto==1)
    {
      spaco1r=spaco1;
      char *heght=malloc(64);
      sprintf(heght, "%s2240.png", fontpath);
      paused_height=GetImgHeight((int)heght);
      mfree(heght);
    }
    else
    {
      spaco1r=10001+(system_color*100);
      paused_height=fonto-100;
    }
  sprintf(ping_txt, "Ping: none");
  init_time_zone();
  AddKeybMsgHook((void *)my_keyhook); 
#endif
  return 0;
}

//===========================================================
// Edit chat
//===========================================================
void edchat_locret(void){}

char *ExtractAnswer(WSHDR *ws)
{
  S_SMILES *t;
  int c;
  int len=0;
  int scur;
  char *msg=NULL;
  unsigned short *wsbody=ws->wsbody;
  int wslen=wsbody[0];
  if (wslen)
  {
    for (int i=0; i<wslen; i++) // Посчитаем общую длину будущей строки
    {
      c=wsbody[i+1];
      if (c>=0xE100)
      {
        t=FindSmileByUni(c);
        if (t)
        {
          if (t->lines)
          {
            len+=strlen(t->lines->text);
          }
        }
        else  len++;
      }
      else  len++;
    }

    msg=malloc(len+1);
    scur=0;
    for (int wcur=0; wcur<wslen && scur<len; wcur++)
    {
      c=wsbody[wcur+1];
      if (c==10) c=13;
      if (c>=0xE100)
      {
        t=FindSmileByUni(c);
        if (t)
        {
          int w;
          char *s;
          if (t->lines)
          {
            s=t->lines->text;
            while ((w=*s++) && scur<len)
            {
              msg[scur]=w;
              scur++;
            }
          }
        }
        else
        {
          msg[scur]=char16to8(c);
          scur++;
        }
      }
      else
      {
        msg[scur]=char16to8(c);
        scur++;
      }
    }
    msg[scur]=0;
  }
  return msg;
}

CLIST *FindNextActiveContact(CLIST *t)
{
  while(t=(CLIST *)(t->next))
  {
    if (t->isactive) return t;
  }
  t=(CLIST *)(&cltop);
  while(t=(CLIST *)(t->next))
  {
    if (t->isactive) return t;
  }
  return NULL;
}

CLIST *FindPrevActiveContact(CLIST *t)
{
  CLIST *cl;
  CLIST *cl_active=NULL;
  cl=(CLIST *)(&cltop);


  while(cl=cl->next)
  {
    if (cl==t)
    {
      if (cl_active==NULL) break;
      else return (cl_active);
    }
    else
    {
      if (cl->isactive) cl_active=cl;
    }
  }
  while(t)
  {
    if (t->isactive) cl_active=t;
    t=t->next;
  }
  return cl_active;
}


void ed_options_handler(USR_MENU_ITEM *item)
{
  EDCHAT_STRUCT *ed_struct=item->user_pointer;
  CLIST *t;
  int i=item->cur_item;
  if (item->type==0)
  {
    switch(i)
    {
    case 0:
      ascii2ws(item->ws,LG_MNUEDNEXTACT);
      break;
    case 1:
      ascii2ws(item->ws,LG_MNUEDPREVACT);
      break;
    default:
      i-=2;
      if (i<ed_struct->loaded_templates) ascii2ws(item->ws,templates_lines[i]);
      break;
    }
  }
  if (item->type==1)
  {
    switch(i)
    {
    case 0:
      t=FindNextActiveContact(ed_struct->ed_contact);
      if (t && t!=ed_struct->ed_contact)
      {
        GeneralFunc_flag1(edchat_id,1);
        CreateEditChat(t);
      }
      break;
    case 1:
      t=FindPrevActiveContact(ed_struct->ed_contact);
      if (t && t!=ed_struct->ed_contact)
      {
        GeneralFunc_flag1(edchat_id,1);
        CreateEditChat(t);
      }
      break;
    default:
      i-=2;
      if (i<ed_struct->loaded_templates)
      {
	EDITCONTROL ec;
	WSHDR *ed_ws;
	int c;
	char *p=templates_lines[i];
	ExtractEditControl(ed_struct->ed_chatgui,ed_struct->ed_answer,&ec);
	ed_ws=AllocWS(ec.pWS->wsbody[0]+strlen(p));
	wstrcpy(ed_ws,ec.pWS);
        if (EDIT_GetFocus(ed_struct->ed_chatgui)==ed_struct->ed_answer)
        {
          int pos=EDIT_GetCursorPos(ed_struct->ed_chatgui);
          while(c=*p++)
          {
            wsInsertChar(ed_ws,char8to16(c),pos++);
          }
          EDIT_SetTextToEditControl(ed_struct->ed_chatgui,ed_struct->ed_answer,ed_ws);
          EDIT_SetCursorPos(ed_struct->ed_chatgui,pos);
        }
        else
        {
          while(c=*p++)
          {
            wsAppendChar(ed_ws,char8to16(c));
          }
          EDIT_SetTextToEditControl(ed_struct->ed_chatgui,ed_struct->ed_answer,ed_ws);
        }
	FreeWS(ed_ws);
      }
      break;
    }
  }
}

void ParseAnswer(WSHDR *ws, const char *s)
{
  S_SMILES *t;
  S_SMILES *t_root=(S_SMILES *)s_top;
  STXT_SMILES *st;
  unsigned int wchar;
  unsigned int ulb=s[0]+(s[1]<<8)+(s[2]<<16)+(s[3]<<24);
  CutWSTR(ws,0);
  int i;
  while(wchar=*s)
  {
    t=t_root;
    while(t)
    {
      st=t->lines;
      while(st)
      {
	if ((ulb&st->mask)==st->key)
	{
	  if (!strncmp(s,st->text,strlen(st->text))) goto L1;
	}
	st=st->next;
      }
      t=t->next;
    }
  L1:
    if (t)
    {
      wchar=t->uni_smile;
      s+=strlen(st->text);
      ulb=s[0]+(s[1]<<8)+(s[2]<<16)+(s[3]<<24);
    }
    else
    {
      wchar=char8to16(wchar);
      s++;
      ulb>>=8;
      ulb+=s[3]<<24;
    }
    if (wchar!=10) wsAppendChar(ws,wchar);
  }
  i=ws->wsbody[0];
  while(i>1)
  {
    if (ws->wsbody[i--]!=13) break;
    ws->wsbody[0]=i;
  }
}

void SaveAnswer(CLIST *cl, WSHDR *ws)
{
  char *p=ExtractAnswer(ws);
  mfree(cl->answer);
  cl->answer=p;
}

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
  GBS_DelTimer(&tmr_illumination);
  CLIST *t;
  TPKT *p;
  EDITCONTROL ec;
  int len;
  char *s;
  int l=msg->gbsmsg->submess;
  EDCHAT_STRUCT *ed_struct=EDIT_GetUserPointer(data);

  if (msg->keys==0xFFF)
  {
    void ec_menu(EDCHAT_STRUCT *);
    ec_menu(ed_struct);
    return(-1);
  }
  if (msg->keys==0xFF0)  return (1);
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
#ifdef ELKA
    if (l==VOL_DOWN_BUTTON)
    {
      WSHDR *ws;
      ExtractEditControl(data,ed_struct->ed_answer,&ec);
      if(wstrlen(ec.pWS)>0)
      {
        ws=AllocWS(1);
        CutWSTR(ws,0);
  
        EDIT_SetFocus(data,ed_struct->ed_answer);
        EDIT_SetTextToFocused(ed_struct->ed_chatgui,ws); 
    
        FreeWS(ws);
        RefreshGUI();  
      }
    }
    if (l==VOL_UP_BUTTON)
    {
//      WSHDR *ws=AllocWS(strlen(ed_struct->ed_contact->last_msg_buffer)+1);
//      ascii2ws(ws,ed_struct->ed_contact->last_msg_buffer);
      WSHDR *ws=AllocWS(strlen(last_msg_buffer)+1);
      ascii2ws(ws,last_msg_buffer);
      EDIT_SetFocus(ed_struct->ed_chatgui,ed_struct->ed_answer);
      EDIT_SetTextToFocused(ed_struct->ed_chatgui,ws);
      FreeWS(ws);
      RefreshGUI();
    }
#else
    if (l==RIGHT_BUTTON)
    {
      if (EDIT_GetFocus(data)==ed_struct->ed_answer)
      {
	ExtractEditControl(data,ed_struct->ed_answer,&ec);
	if (ec.pWS->wsbody[0]==(EDIT_GetCursorPos(data)-1))
	{
	  t=FindNextActiveContact(ed_struct->ed_contact);
	  if (t && t!=ed_struct->ed_contact)
	  {
	    CreateEditChat(t);
	    return(1);
	  }
	}
      }
    }
#endif
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if ((l>='0')&&(l<='9'))
    {
      if (EDIT_GetFocus(data)!=ed_struct->ed_answer)
	EDIT_SetFocus(data,ed_struct->ed_answer);
    }
    if (l==GREEN_BUTTON)
    {
      if (connect_state==3)
      {
	if ((t=ed_struct->ed_contact))
	{
          ExtractEditControl(data,ed_struct->ed_answer,&ec);
          SaveAnswer(t,ec.pWS);
	  if ((s=t->answer))
	  {
	    if ((len=strlen(s)))
	    {
	      t->isactive=ACTIVE_TIME;
	      p=malloc(sizeof(PKT)+len+1);
	      p->pkt.uin=t->uin;
	      p->pkt.type=T_SENDMSG;
	      p->pkt.data_len=len;
	      strcpy(p->data,s);
#ifdef ELKA
              strcpy(last_msg_buffer, s);
#endif
	      AddStringToLog(t,0x01,p->data,I_str,(++SENDMSGCOUNT)&0x7FFF); //Номер сообщения
              out_count++;
	      SUBPROC((void *)SendAnswer,0,p);
	      mfree(t->answer);
	      t->answer=NULL;
	      //        request_remake_edchat=1;
	      EDIT_SetFocus(data,ed_struct->ed_answer);
	      CutWSTR(ews,0);
	      EDIT_SetTextToFocused(data,ews);
	      AddMsgToChat(data);
	      RecountMenu(t, 1);
	      return(-1);
	    }
	  }
	}
      }
    }
    if (l==ENTER_BUTTON)
    {
      //      t=FindNextActiveContact(ed_struct->ed_contact);
      //      if ((t!=ed_struct->ed_contact) && t)
      {
	int i=ed_struct->loaded_templates=LoadTemplates(ed_struct->ed_contact->uin);
        EDIT_OpenOptionMenuWithUserItems(data,ed_options_handler,ed_struct,i+2);
        return (-1);
      }
    }
    if (l==VOL_UP_BUTTON)
    {
      int pos;

      if ((pos=EDIT_GetFocus(data)-2)>=2)
      {
        EDIT_SetFocus(data, pos);
        EDIT_SetCursorPos(data, 1);
      }
      return (-1);
    }
    if (l==VOL_DOWN_BUTTON)
    {
      int pos;

      if ((pos=EDIT_GetFocus(data)+2)<=ed_struct->ed_answer)
      {
        EDIT_SetFocus(data, pos);
        EDIT_SetCursorPos(data, 1);
      }
      return (-1);
    }
  }
  return(0); //Do standart keys
  //1: close
}

static const HEADER_DESC edchat_hdr={0,0,NULL,NULL,NULL,0,LGP_NULL};

void (*old_ed_redraw)(void *data);
void my_ed_redraw(void *data)
{
  void *edchat_gui;
  EDCHAT_STRUCT *ed_struct;
  if (old_ed_redraw) old_ed_redraw(data);
  edchat_gui=FindGUIbyId(edchat_id,NULL);
  if (edchat_gui)
  {
    ed_struct=EDIT_GetUserPointer(edchat_gui);
    if (ed_struct)
    {
      int icon, width;
#ifndef	NEWSGOLD
      icon=*(S_ICONS+GetIconIndex(ed_struct->ed_contact));
      ((HEADER_DESC *)&edchat_hdr)->rc.x2=ScreenW()-1-(width=GetImgWidth(icon));
      DrawImg(ScreenW()-1-width,1,icon);
#else
      icon=*(S_ICONS+GetIconIndex(ed_struct->ed_contact));
      width=GetImgWidth(icon);
      DrawImg(2,((HeaderH()-width)>>1)+YDISP,icon);
/*      DrawRoundedFrame(ScreenW()-8,YDISP,ScreenW()-1,YDISP+7,0,0,0,
		       GetPaletteAdrByColorIndex(0),
		       GetPaletteAdrByColorIndex(EDIT_IsBusy(edchat_gui)?3:4));*/
#endif
    }
  }
}

void edchat_ghook(GUI *data, int cmd)
{
  static const SOFTKEY_DESC sk={0x0FFF,0x0000,(int)LG_MENU};
  static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LG_CLOSE};
  //  static SOFTKEY_DESC sk={0x0018,0x0000,(int)"Menu"};
  int j;
  EDITCONTROL ec;
  EDCHAT_STRUCT *ed_struct=EDIT_GetUserPointer(data);
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    GBS_DelTimer(&tmr_illumination);          //by BoBa 25.06.07
    pltop->dyn_pltop=NULL;
  }
  if (cmd==2)
  {
    ed_struct->ed_chatgui=data;
//    edgui_data=data;
    EDIT_SetFocus(data,ed_struct->ed_answer);

    static void *methods[16];
    void **m=GetDataOfItemByID(data,2);
    if (m)
    {
      if (m[1])
      {
        memcpy(methods,m[1],sizeof(methods));
        old_ed_redraw=(void (*)(void *))(methods[0]);
        methods[0]=(void *)my_ed_redraw;
        m[1]=methods;
      }
    }
  }
  if (cmd==3)
  {
//    if (edgui_data==data) edgui_data=NULL;
    if (ed_struct->ed_contact)
    {
      ExtractEditControl(data,ed_struct->ed_answer,&ec);
      SaveAnswer(ed_struct->ed_contact,ec.pWS);
    }
    RecountMenu(ed_struct->ed_contact, 1);
    mfree(ed_struct);
  }
  if (cmd==0x0A)
  {
    pltop->dyn_pltop=SmilesImgList;
    DisableIDLETMR();
    total_unread-=ed_struct->requested_decrement_total_unread;
    ed_struct->requested_decrement_total_unread=0;
/*    if (request_close_edchat)
    {
      request_close_edchat=0;
      GeneralFunc_flag1(edchat_id,1);
      return;
    }*/
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,ed_struct->ed_answer,&ec);
    if (ec.pWS->wsbody[0]==0)
      SetSoftKey(data,&sk_cancel,SET_SOFT_KEY_N==0?1:0);
    if (!EDIT_IsBusy(data))
    {
      time_to_stop_t9=0;
      if (ed_struct->ed_contact->req_add)
      {
	ed_struct->ed_contact->req_add=0;
	AddMsgToChat(data);
	RecountMenu(ed_struct->ed_contact, 1);
      }
      if (ed_struct->ed_contact->req_drawack)
      {
	ed_struct->ed_contact->req_drawack=0;
	DrawAck(data);
      }
    }
  }
  if (cmd==0x0C)
  {
    j=EDIT_GetFocus(data);
    if ((EDIT_GetUnFocus(data)<j)&&(j!=ed_struct->ed_answer))
      EDIT_SetCursorPos(data,1);
  }
}



static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};

void CreateEditChat(CLIST *t)
{
  extern const int FIRST_LETTER;
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  int color, font, type;
  int zc;

  LOGQ *lp;
  int edchat_toitem;
//  edcontact=t;

  *((int *)(&edchat_hdr.lgp_id))=(int)t->name;
//  *((int **)(&edchat_hdr.icon))=(int *)S_ICONS+GetIconIndex(t);
  *((int **)(&edchat_hdr.icon))=(int *)S_ICONS+IS_NULLICON;

  eq=AllocEQueue(ma,mfree_adr());


  lp=t->log;

  while(lp)
  {
    font = ED_H_FONT_SIZE;
    if ((zc=lp->acked&3))
    {
      if (zc==1)
	color=ACK_COLOR; //Зеленый
      else
	color=I_COLOR;
    }
    else
    {
      if (lp->ID==0xFFFFFFFF)
      {
        type = lp->type&0x0F;
        if(lp->type&0x10)
        {
          color = (type==1)?O_I_COLOR:((type==3)?O_X_COLOR:O_TO_COLOR);
          font = (type==3)?O_ED_X_FONT_SIZE:O_ED_H_FONT_SIZE;
        }
        else
        {
          color = (type==1)?I_COLOR:((type==3)?X_COLOR:TO_COLOR);
          font = (type==3)?ED_X_FONT_SIZE:ED_H_FONT_SIZE;
        }
      }
      else
	color=UNACK_COLOR; //Серый
    }
    PrepareEditControl(&ec);
    if ((lp->type&0x0F)!=3)
    {
      ascii2ws(ews,lp->hdr);
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
    }
    else
      ConstructEditControl(&ec,ECT_HEADER,ECF_DELSTR,ews,0);
    PrepareEditCOptions(&ec_options);
    SetPenColorToEditCOptions(&ec_options,color);
    SetFontToEditCOptions(&ec_options,font);
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);
    if ((lp->type&0x0F)!=3)
    {
      ParseAnswer(ews,lp->text);
    }
    else
    {
      ParseXStatusText(ews,lp->text,(lp->type&0x10)?O_X_COLOR:X_COLOR);
    }
    PrepareEditControl(&ec);
    ConstructEditControl(&ec,
                         ECT_NORMAL_TEXT,
                         ews->wsbody[0] ? ECF_APPEND_EOL|ECF_DISABLE_T9 : ECF_DELSTR,
                         ews,ews->wsbody[0]);
    PrepareEditCOptions(&ec_options);
//#ifdef M75
    if ((lp->type&0x0F)!=3)
    {
      SetFontToEditCOptions(&ec_options,(lp->type&0x10)?O_ED_FONT_SIZE:ED_FONT_SIZE);
    }
    else
    {
      SetPenColorToEditCOptions(&ec_options,(lp->type&0x10)?O_X_COLOR:X_COLOR);
      SetFontToEditCOptions(&ec_options,(lp->type&0x10)?O_ED_X_FONT_SIZE:ED_X_FONT_SIZE);
    }
//#else
//    SetFontToEditCOptions(&ec_options,(lp->type&0x10)?O_ED_FONT_SIZE:ED_FONT_SIZE);
//#endif
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);
    lp=lp->next;
  }
  if (t->isunread) total_unread--;
  t->isunread=0;
#ifdef EVILFOX
  total_unread2=total_unread2-t->unread_msg;
  t->unread_msg=0;
#endif
  ChangeContactPos(t);
  wsprintf(ews, "-------");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  PrepareEditCOptions(&ec_options);
  SetFontToEditCOptions(&ec_options,ED_FONT_SIZE);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);

  if (t->answer) ParseAnswer(ews,t->answer);
  else  CutWSTR(ews,0);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,3,(FIRST_LETTER)?ECF_DEFAULT_BIG_LETTER:0,ews,1024);

  PrepareEditCOptions(&ec_options);
  SetFontToEditCOptions(&ec_options,ED_FONT_SIZE);
  CopyOptionsToEditControl(&ec,&ec_options);
  edchat_toitem=AddEditControlToEditQend(eq,&ec,ma);

  if (t->req_xtext)
  {
    FreeXText(t);
    t->req_xtext=0;
    RequestXText(t->uin);
  }

  EDCHAT_STRUCT *ed_struct=malloc(sizeof(EDCHAT_STRUCT));
  ed_struct->ed_contact=t;
  ed_struct->ed_answer=edchat_toitem;
  ed_struct->requested_decrement_total_unread=0;
  t->req_add=0;
  t->last_log=NULL;

  //  int scr_w=ScreenW();
  //  int scr_h=ScreenH();
  //  int head_h=HeaderH();

  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);
  //  edchat_desc.font=ED_FONT_SIZE;
  edchat_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,ed_struct);
}

//-----------------------------------------------------------------------------
#define EC_MNU_MAX 8

void Quote(GUI *data)
{
  int q_n;
  EDITCONTROL ec, ec_hdr;
  EDITCONTROL ec_ed;
  WSHDR *ed_ws;
  WSHDR *ws;

  EDCHAT_STRUCT *ed_struct;
  ed_struct=MenuGetUserPointer(data);

  q_n=EDIT_GetFocus(ed_struct->ed_chatgui);
  ExtractEditControl(ed_struct->ed_chatgui,q_n,&ec);
  ExtractEditControl(ed_struct->ed_chatgui,q_n-1,&ec_hdr);
  ExtractEditControl(ed_struct->ed_chatgui,ed_struct->ed_answer,&ec_ed);

  ed_ws=AllocWS((ec_ed.maxlen<<1) + 1);
  if(wstrlen(ec_hdr.pWS))
  {
    wstrcpy(ed_ws,ec_hdr.pWS);
    wsAppendChar(ed_ws,'\r');
  }
  else
    CutWSTR(ed_ws,0);
  if (EDIT_IsMarkModeActive(ed_struct->ed_chatgui))
  {
    EDIT_GetMarkedText(ed_struct->ed_chatgui,ed_ws);
  }
  else
  {
    wstrcat(ed_ws,ec.pWS);
  }
  int ed_pos=0;
  do
  {
    ed_pos++;
    wsInsertChar(ed_ws,'>',ed_pos++);
    wsInsertChar(ed_ws,' ',ed_pos);
  }
  while((ed_pos=wstrchr(ed_ws,ed_pos,'\r'))!=0xFFFF);
  wsAppendChar(ed_ws,'\r');
  wsAppendChar(ed_ws,'\r');
  ws=AllocWS(ec_ed.pWS->wsbody[0]+ed_ws->wsbody[0]);
  wstrcpy(ws,ec_ed.pWS);
  wstrcat(ws,ed_ws);
  FreeWS(ed_ws);
  CutWSTR(ws,ec_ed.maxlen);
  EDIT_SetFocus(ed_struct->ed_chatgui,ed_struct->ed_answer);
  EDIT_SetTextToFocused(ed_struct->ed_chatgui,ws);
  FreeWS(ws);
  GeneralFuncF1(1);
}


void GetShortInfo(GUI *data)
{
  EDCHAT_STRUCT *ed_struct;
  ed_struct=MenuGetUserPointer(data);

  TPKT *p;
  CLIST *t;
  if ((t=ed_struct->ed_contact)&&(connect_state==3))
  {
    p=malloc(sizeof(PKT));
    p->pkt.uin=t->uin;
    p->pkt.type=T_REQINFOSHORT;
    p->pkt.data_len=0;
    AddStringToLog(t, 0x01, "Request info...", I_str,0xFFFFFFFF);
    AddMsgToChat(ed_struct->ed_chatgui);
    RecountMenu(t, 1);
    SUBPROC((void *)SendAnswer,0,p);
  }
  GeneralFuncF1(1);
}

void AskNickAndAddContact(EDCHAT_STRUCT *);
void AddCurContact(GUI *data)
{
  EDCHAT_STRUCT *ed_struct;
  ed_struct=MenuGetUserPointer(data);

  if ((ed_struct->ed_contact)&&(connect_state==3)) AskNickAndAddContact(ed_struct);
  GeneralFuncF1(1);
}

void SendAuthReq(GUI *data)
{
  EDCHAT_STRUCT *ed_struct;
  ed_struct=MenuGetUserPointer(data);

  TPKT *p;
  CLIST *t;
  int l;
  const char s[]=LG_AUTHREQ;
  if ((t=ed_struct->ed_contact)&&(connect_state==3))
  {
    p=malloc(sizeof(PKT)+(l=strlen(s))+1);
    p->pkt.uin=t->uin;
    p->pkt.type=T_AUTHREQ;
    p->pkt.data_len=l;
    strcpy(p->data,s);
    AddStringToLog(t,0x01,p->data,I_str,0xFFFFFFFF);
    AddMsgToChat(ed_struct->ed_chatgui);
    RecountMenu(t, 1);
    SUBPROC((void *)SendAnswer,0,p);
  }
  GeneralFuncF1(1);
}

void SendAuthGrant(GUI *data)
{
  EDCHAT_STRUCT *ed_struct;
  ed_struct=MenuGetUserPointer(data);

  TPKT *p;
  CLIST *t;
  int l;
  const char s[]=LG_AUTHGRANT;
  if ((t=ed_struct->ed_contact)&&(connect_state==3))
  {
    p=malloc(sizeof(PKT)+(l=strlen(s))+1);
    p->pkt.uin=t->uin;
    p->pkt.type=T_AUTHGRANT;
    p->pkt.data_len=l;
    strcpy(p->data,s);
    AddStringToLog(t,0x01,p->data,I_str,0xFFFFFFFF);
    AddMsgToChat(ed_struct->ed_chatgui);
    RecountMenu(t, 1);
    SUBPROC((void *)SendAnswer,0,p);
  }
  GeneralFuncF1(1);
}

void OpenLogfile(GUI *data)
{
  EDCHAT_STRUCT *ed_struct;
  ed_struct=MenuGetUserPointer(data);

  extern const char HIST_PATH[64];
#ifdef EVILFOX_2
#else
  extern const int HISTORY_TYPE;
#endif
  CLIST *t;
  WSHDR *ws=AllocWS(256);
  if ((t=ed_struct->ed_contact))
  {
#ifdef EVILFOX_2
    wsprintf(ws,"%s\\%u\\%s.txt",HIST_PATH,UIN,t->name);  
#else
    if (HISTORY_TYPE)
      wsprintf(ws,"%s\\%u\\%u.txt",HIST_PATH,UIN, t->uin);
    else
      wsprintf(ws,"%s\\%u.txt",HIST_PATH, t->uin);
#endif
    ExecuteFile(ws,NULL,NULL);
  }
  FreeWS(ws);
  GeneralFuncF1(1);
}

void ClearLog(GUI *data/*,void *dummy*/)
{
  EDITCONTROL ec;
  EDCHAT_STRUCT *ed_struct;
  WSHDR *ws;
  CLIST *t;

  ed_struct=MenuGetUserPointer(data);

  ExtractEditControl(ed_struct->ed_chatgui,ed_struct->ed_answer,&ec);
  if(wstrlen(ec.pWS)>0)
  {
    ws=AllocWS(1);
    CutWSTR(ws,0);

    EDIT_SetFocus(ed_struct->ed_chatgui,ed_struct->ed_answer);
    EDIT_SetTextToFocused(ed_struct->ed_chatgui,ws);

    FreeWS(ws);
    GeneralFuncF1(1);
  }
  else
  {

    if ((t=ed_struct->ed_contact))
    {
      if (t->log)
      {
        FreeLOGQ(&t->log);
        t->msg_count=0;
        if (ed_struct->ed_answer>=2&&ed_struct->ed_chatgui)
        {
          while(ed_struct->ed_answer!=2)
          {
            EDIT_RemoveEditControl(ed_struct->ed_chatgui,1);
            ed_struct->ed_answer--;
          }
        }
      }
      t->isactive=0;		//by BoBa  18.06.07
      RecountMenu(t, 1);
      GeneralFuncF1(1);
    }
  }
}

void ecmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static const MENUITEM_DESC ecmenu_ITEMS[EC_MNU_MAX]=
{
  {NULL,(int)LG_MNUQUOTE,    LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_MNUADDSML,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_MNUSHINFO,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_MNUADDREN,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_MNUSAUTHREQ, LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_MNUSAUTHGRT, LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_MNUOPENLOG,  LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_MNUCLEARCHT, LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

extern void AddSmile(GUI *data);
static const MENUPROCS_DESC ecmenu_HNDLS[EC_MNU_MAX]=
{
  Quote,
  AddSmile,
  GetShortInfo,
  AddCurContact,
  SendAuthReq,
  SendAuthGrant,
  OpenLogfile,
  ClearLog,
};

char ecm_contactname[64];

static const HEADER_DESC ecmenu_HDR={0,0,NULL,NULL,NULL,(int)ecm_contactname,LGP_NULL};

static const MENU_DESC ecmenu_STRUCT=
{
  8,NULL,ecmenu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  ecmenu_ITEMS,
  ecmenu_HNDLS,
  EC_MNU_MAX
};

void ec_menu(EDCHAT_STRUCT *ed_struct)
{
  CLIST *t;
  int to_remove[EC_MNU_MAX+1];
  int remove=0;
  if ((t=ed_struct->ed_contact))
  {
    if (t->name)
    {
      strncpy(ecm_contactname,t->name,63);
    }
    else
    {
      sprintf(ecm_contactname,"%u",t->uin);
    }
    if (EDIT_GetFocus(ed_struct->ed_chatgui)==ed_struct->ed_answer)
    {
      to_remove[++remove]=0;
    }
    else
    {
      to_remove[++remove]=1;
    }

    if (ed_struct->ed_answer<=2) to_remove[++remove]=7;
    if (!ed_struct->ed_contact || connect_state!=3)
    {
      to_remove[++remove]=2;
      to_remove[++remove]=3;
      to_remove[++remove]=4;
      to_remove[++remove]=5;
    }

    patch_header(&ecmenu_HDR);
    to_remove[0]=remove;
    CreateMenu(0,0,&ecmenu_STRUCT,&ecmenu_HDR,0,EC_MNU_MAX,ed_struct,to_remove);
  }
}


void AskNickAndAddContact(EDCHAT_STRUCT *ed_struct)
{
  CreateAddContactGrpDialog(ed_struct->ed_contact);
}

void AddSmile(GUI *data)
{
  EDCHAT_STRUCT *ed_struct=MenuGetUserPointer(data);
  CreateSmileSelectGUI(ed_struct);
  GeneralFuncF1(1);
}
