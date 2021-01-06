//Параметры оптимизации - максимальная оптимизация по скорости, при этом все флаги выключены. Иначе может быть кака
#include "mainmenu.h"
#include "..\inc\swilib.h"
#include "..\inc\playsound.h"
#include "..\inc\xtask_ipc.h"
#include "conf_loader.h"
#include "language.h"
#include "main.h"
#include "playlists.h"
#include "../inc/stdbool.h"
#include "mainmenu.h"
#include "swilib2.h"
#include "snd_buffers.h"
#include "mediafiles_base.h"
#include "rect_patcher.h"
#include "libr.h"
#include "ipc.h"
#include "..\inc\pnglist.h"
#include "headers.h"


extern int (*OBS_Test)(HObj gObj,int);

#ifdef OBS
HObj gObj;
#else
void* pha;
#endif

#ifdef OBS
#define MSG_Report  0xB034
void KillObj(){
 if (!gObj) return;
  Obs_DestroyObject(gObj);
  gObj=NULL;
}
#endif

unsigned short playing;
short ModeRew;
int ln=0;    // Длительность
int tm=0;
unsigned short sttmr=0;  // Почему-то неверно начинал счет   AAA
bool tm_er=0;

extern const unsigned int IDLEICON_X,IDLEICON_Y,EnableIconOnIdle;
#ifdef X75
#define MAXVOLUME 14
#else

#ifdef NEWSGOLD
#ifdef OBS
#define MAXVOLUME 15
#else
#define MAXVOLUME 5
#endif
#else
#define MAXVOLUME 4
#endif
#endif

FILEPRP flprp;
IMGHDR *img_o;
bool IPC_COPY=0;          // Открыли копию или нет?    AAA
int TagMenu_ID;
int Quit_Required = 0;     // Флаг необходимости завершить работу
int cp=0,WhatToView=0;
char spysok[2][256][128];//Максимальное количество песен - 255 (1 байт при сохранении)
int pisniashchozberigaetsia=0,identyfikator;
const char ipc_my_name[32]=IPC_MY_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
GBSTMR PlayerMenu,PlayNextTimer,tags,mytmr;
//GBSTMR statmr;
int CanPlayNext=1;
int VIEW=1;
int disk=1;
IPC_REQ gipc;
IPC_REQ eipc;
int top,bottom,selected,shukajuchas=0;
int spysokselected[256];
long timelength[256];
int curskin=0;// Текущий скин
char ArrayOfSkins[100][20];//Скинов 100 максимум
int playlistmode=0;//0-запуск файла без параметрів, 1- зі списком ipl, 2 - з m3u, 3 - режим медіатеки, 4 - з мс
char LastPlaylist[256],playlistname[256];
int notplayed[256];//Масив. Отмечается, какая песня игралась, а какая нет (при случайном порядке)
char calbum[128]=" ",ctrack[128]=" ",cartist[128]=" "; //Теги
char NameOfCurentTrack[128]="";
int random=0,NumberOfSkins=0;
int timehms[3];//Time:hour,minute,second
int timesec=0,timemin=0,JaPerekliuchyvPisniu=0,NeedToStop=0;
int NumberOfTracks=0,CurentVolume=4,ringoff=0,pracuje=0;
int PLAY_ID=0xFFFF;
extern const char playerfolder[128],folder[128],folder_scan[128];
extern const char format_1[4],format_2[4],format_3[4],format_4[4];
extern const int Key1,Key2,Key3,Key4,Key5,Key6,Key7,Key8,Key9,Key0,KeyZ,KeyR;//Настройки клавиш. Лучше бы их в файл вынести, но пока так
extern const unsigned int RedrawTime;//Время перерисовки
extern const unsigned int profile1,profile2,profile3,profile4,profile5,profile6,profile7,profile8;
extern const unsigned int autoexit_time_play;
extern const unsigned int autoexit_time_pause;
extern const unsigned int autoexit_time_stop;
extern const unsigned int over_font;
extern const unsigned int over_align;
extern const unsigned int over_ena;
#ifdef NEWSGOLD
extern const int ena_vol;
extern const unsigned int vol_icon;
#endif
extern const int ena_art;
extern const int ena_tag;
extern const int ena_aexit;
extern const int ena_bit;
extern const int ena_ch;
extern const int ena_fr;
extern const int ena_mp;
extern const int ena_lay;
char getvol;


const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
extern const int EnableHook;

extern const RECT over;
extern const RECT tagS;
extern const char TRACK_COL[4];
extern const char bg_over_color[4];
extern const char over_col[4];
char PlaylistToSave[255];
int rew_flag;//флаг завершения перемотки
GBSTMR play_exit,pause_exit,stop_exit;

void ElfKiller(void);
void PlayerOff(void)
{
  if(IsTimerProc(&play_exit)) GBS_DelTimer(&play_exit);
  if(IsTimerProc(&pause_exit)) GBS_DelTimer(&pause_exit);
  if(IsTimerProc(&stop_exit)) GBS_DelTimer(&stop_exit);
  //SUBPROC((void*)ElfKiller);
  GeneralFuncF1(1);
}

void ExitTime()//Отсчитываем время авто выхода
{
  if(ena_aexit==1)
  {
    switch(playing)
    {
    case 0:
      GBS_StartTimerProc(&stop_exit,216*60*autoexit_time_stop,PlayerOff);
      if(IsTimerProc(&play_exit)) GBS_DelTimer(&play_exit);
      if(IsTimerProc(&pause_exit)) GBS_DelTimer(&pause_exit);
      break;
    case 1:
      GBS_StartTimerProc(&play_exit,216*60*autoexit_time_play,PlayerOff);
      if(IsTimerProc(&stop_exit)) GBS_DelTimer(&stop_exit);
      if(IsTimerProc(&pause_exit)) GBS_DelTimer(&pause_exit);
      break; 
    case 2:
      GBS_StartTimerProc(&pause_exit,216*60*autoexit_time_pause,PlayerOff);
      if(IsTimerProc(&stop_exit)) GBS_DelTimer(&stop_exit);
      if(IsTimerProc(&play_exit)) GBS_DelTimer(&play_exit);
      break;  
    }
  }
  else
  {
    if(IsTimerProc(&play_exit)) GBS_DelTimer(&play_exit);
    if(IsTimerProc(&pause_exit)) GBS_DelTimer(&pause_exit);
    if(IsTimerProc(&stop_exit)) GBS_DelTimer(&stop_exit);
  }
}
       
void StartRewindToBegin()
{
  extern unsigned int IsRewind;
  if(playing==0||IsRewind)return;
  ModeRew=-1;
  StartRewind();
}

void StartRewindToEnd()
{
  extern unsigned int IsRewind;
  if(playing==0||IsRewind)return;
  ModeRew=1;
  StartRewind();
}

typedef struct
{
  WSHDR *ws1;
  WSHDR *ws2;
}rr;
rr wss,ows;
void clear_cache()
{
  PNGTOP_DESC *ptop=PNG_TOP();
  PNGLIST *pl;
  LockSched();
  pl=ptop->pltop;
  ptop->pltop=0;
  UnlockSched();
  while(pl)
  {
    PNGLIST *pl_prev;
    pl_prev=pl;
    pl=pl->next;
    mfree(pl_prev->pngname);
    if(pl_prev->img)
    {
      mfree(pl_prev->img->bitmap);
      mfree(pl_prev->img);
    }
    mfree(pl_prev);
  }
  //SUBPROC((void *)ElfKiller);
  //REDRAW();
}
void CLOSECURENTCSM()
{
  CloseCSM(MAINCSM_ID);
}

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

/*typedef struct
{
  char *backgroundname;
  int progressbarconst;
  char *progressbarname;
  WSHDR *PLAYLIST;
  WSHDR *TRACK;
  WSHDR *NUMBEROFTRACKS;
  char *offname;
  char *randomname;
  char *plusname;
  char *minusname;
  char *stopname;
  char *playname;
  char *prevname;
  char *nextname;
}RedrawStruct;
RedrawStruct pisnia;*/

void EXT_REDRAW()
{
  if(/*IsGuiOnTop(MAINGUI_ID)&&*/WhatToView==0) REDRAW();
 // GetPlayObjPosition((void*)gObj,&tm);   // Лагает   AAA
 // tm/=1000;
  if(tm||sttmr) {tm++;}
  else {sttmr=1;}
  GBS_StartTimerProc(&mytmr,216,EXT_REDRAW);
}

void StopTMR(unsigned short s)
{
  GBS_DelTimer(&mytmr);
  if(s==1) {tm=0; ln=0; sttmr=0;}
  if(s==2) {tm=0;}
}

int timelist;
int spysokx1=1,spysoky1=90,spysokx2=240,spysoky2=320,spysokfont=8,spysoktextattribute=2,spysoktextcolor=0,spysoktextbackground=23;   //здесь нигде не 0, а то почему-то не читает из файла правильно
int timex1=1,timey1=240,timex2=240,timey2=320,timefont=7,timetextattribute=2,timetextcolor=1,timetextbackground=23;
int songx1=1,songy1=120,songx2=240,songy2=320,songfont=7,songtextattribute=1,songtextcolor=1,songtextbackground=23;
int tracksx1=1,tracksy1=1,tracksx2=240,tracksy2=320,tracksfont=7,trackstextattribute=4,trackstextcolor=1,trackstextbackground=23;
char chanel[8],freq[8],bitrate[8];
int chanx1=1,chany1=1,chanx2=240,chany2=320,chanfont=7,chanatr=4,chancolor=1;
int freqx1=1,freqy1=1,freqx2=240,freqy2=320,freqfont=7,freqatr=4,freqcolor=1;
int bitx1=1,bity1=1,bitx2=240,bity2=320,bitfont=7,bitatr=4,bitcolor=1;
int mpgx1=1,mpgy1=1,mpgx2=240,mpgy2=320,mpgfont=7,mpgatr=4,mpgcolor=1;
int lax1=1,lay1=1,lax2=240,lay2=320,lafont=7,laatr=4,lacolor=1;
int artx=80,arty=80,art_wh=120;
static const char percent_t[]="%t";
static const char percent_d[]="%d";
static const char tt[]="...";
//static const char percent_s[]="%s";
int volumex=1,volumey=282;
int randomx=4,randomy=4;
int ringoffx=45,ringoffy=4;
int prevx=80,prevy=32;
int nextx=133,nexty=32;
int volpx=110,volpy=9;
int volmx=110,volmy=54;
int play_stopx=112,play_stopy=34;
#ifdef ELKA
int progressbarx1=2,progressbary1=165,progressbarx2=240,progressbarcolour=20;
#else
int progressbarx1=2,progressbary1=165,progressbarx2=132,progressbarcolour=20;
#endif
int katalogbackgroundcolour=9,katalogfontcolour=9,katalogselectedcolour=14,katalogfont=1,katalogxotstup=4;
char name[256];
int CanRewind=0;//разрешение перемотки
int picflag;

void readskinparamsfromfile()
{
  int f;
  char list[20000];
  sprintf(name,"%sskins\\%s\\params.txt",playerfolder,ArrayOfSkins[curskin]);
  unsigned int err;
  f=fopen(name, A_ReadOnly+A_BIN/*+A_MMCStream*/, P_READ, & err );
  if (f!=-1)
  {
  DIR_ENTRY de;
  FindFirstFile(&de,name,&err);
  fread(f,list,de.file_size,&err);
  char num[5];
  sprintf(num,pp);
  int i=0;
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;} //список
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysokx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoky1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysokx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoky2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysokfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoktextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoktextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&spysoktextbackground);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//список
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timex1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timey1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timex2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timey2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timefont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timetextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timetextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&timetextbackground);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//песня
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songy1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songy2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songtextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songtextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&songtextbackground);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//список
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksy1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksy2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&tracksfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&trackstextattribute);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&trackstextcolor);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&trackstextbackground);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//громкость
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volumex);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volumey);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//рандом
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&randomx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&randomy);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//беззвучный
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&ringoffx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&ringoffy);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//след трек
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&prevx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&prevy);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//предыдущ трек
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&nextx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&nexty);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//гром+
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volpx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volpy);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//гром-
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volmx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&volmy);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//пауза.плей
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&play_stopx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&play_stopy);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//треки
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbarx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbary1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbarx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&progressbarcolour);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//каталоги
  i=i+2;
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogbackgroundcolour);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogfontcolour);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogselectedcolour);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&katalogxotstup);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//канал
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&chanx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&chany1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&chanx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&chany2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&chanatr);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&chanfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&chancolor);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//треки
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&freqx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&freqy1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&freqx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&freqy2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&freqatr);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&freqfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&freqcolor);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//треки
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&bitx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&bity1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&bitx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&bity2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&bitatr);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&bitfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&bitcolor);
  i=i+2;
  sprintf(num,pp);
    while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//MPEG
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&mpgx1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&mpgy1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&mpgx2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&mpgy2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&mpgatr);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&mpgfont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&mpgcolor);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//LAYER
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&lax1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&lay1);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&lax2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&lay2);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&laatr);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&lafont);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&lacolor);
  i=i+2;
  sprintf(num,pp);
  while ((i<de.file_size)&&(list[i]!=0x0D)) {i++;}//треки
  i=i+2;  
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&artx);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&arty);
  i=i+2;
  sprintf(num,pp);
while ((i<de.file_size)&&(list[i]!=0x0D)) {sprintf(num,"%s%c",num,list[i]);i++;}
  sscanf(num,p_i,&art_wh);
  i=i+2;
  sprintf(num,pp);  
  FindClose(&de,&err);
  }
  fclose(f,&err);
}

/*void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}*/

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

int sf_inp_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF)
  {
    EDITCONTROL ec;
    ExtractEditControl(data,1,&ec);
    ws_2str(ec.pWS,PlaylistToSave,255);
    SUBPROC((void *)SavePlaylist);
    return(1); //Close
  }
  return(0);
}

void sf_inp_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)LG_SAVE};
  EDITCONTROL ec;
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,1,&ec);
  }
}

void sf_inp_locret(void){}

HEADER_DESC sf_inp_hdr={0,0,0,0,NULL,(int)LG_ENTER_NAME,LGP_NULL};

INPUTDIA_DESC sf_inp_desc=
{
  1,
  sf_inp_onkey,
  sf_inp_ghook,
  (void *)sf_inp_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void CreateSaveAsDialog(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  utf8_2ws(wss.ws2,PlaylistToSave,126);
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,wss.ws2,128);
  AddEditControlToEditQend(eq,&ec,ma);
  
  patch_header(&sf_inp_hdr);
  patch_input(&sf_inp_desc);
  CreateInputTextDialog(&sf_inp_desc,&sf_inp_hdr,eq,1,0);
}

void VporiadkuvatySpysok()
{
  for (int i=0;i<NumberOfTracks-1;i++)
  {
    for (int j=i+1;j<NumberOfTracks;j++)
    {
      if (strcmp(spysok[1][i],spysok[1][j])>0)
      {
        sprintf(name,spysok[0][i]);
        sprintf(spysok[0][i],spysok[0][j]);
        sprintf(spysok[0][j],name);
        sprintf(name,spysok[1][i]);
        sprintf(spysok[1][i],spysok[1][j]);
        sprintf(spysok[1][j],name);
      }
    }
  }
}
    
int GetKatalogfontcolour()
{
  return(katalogfontcolour);
}

int GetKatalogXotstup()
{
  return(katalogxotstup);
}

char katalog[256][128];
int kataloglength,katalogcurent;
int katalogselected[256];
char curentfolder[255]="4:";
/*
char folders[128][128];
int kfolders;
char files[128][128];
int kfiles;

void VporiadkuvatyKatalog()
{
  if (kfiles>1)
  {
    for (int i=0;i<kfiles-1;i++)
    {
      for (int j=i+1;j<kfiles;j++)
      {
        if (strcmp(files[i],files[j])>0)
        {
          sprintf(name,files[i]);
          sprintf(files[i],files[j]);
          sprintf(files[j],name);
        }
      }
    }
  }
  if (kfolders>1)
  {
    for (int i=0;i<kfolders-1;i++)
    {
      for (int j=i+1;j<kfolders;j++)
      {
        if (strcmp(folders[i],folders[j])>0)
        {
          sprintf(name,folders[i]);
          sprintf(folders[i],folders[j]);
          sprintf(folders[j],name);
        }
      }
    }
  }
}
*/
void ZapovnytyTaVidsortuvatyKatalog(char *folder)
{
  DIR_ENTRY de;
  unsigned int err;
  char path[256];
  kataloglength=1;
  sprintf(katalog[0],"..");
  /*kfolders=0;
  kfiles=0;*/
  sprintf(path,"%s\\*",folder);
  katalogcurent=0;
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      char extension[3];
      char file_name[128];
      sprintf(file_name,de.file_name);
      if (IsFile(file_name))
      {
        sprintf(extension,"%c%c%c",file_name[strlen(file_name)-3],file_name[strlen(file_name)-2],file_name[strlen(file_name)-1]);
        if (((strcmp(extension,format_1))==0)||((strcmp(extension,format_2))==0)||((strcmp(extension,format_3))==0)||((strcmp(extension,format_4))==0))
        {
          sprintf(katalog[kataloglength],file_name);
          kataloglength++;
        }
      }
      else
      {
        sprintf(katalog[kataloglength],file_name);
        kataloglength++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  /*for (int i=1;i<kataloglength;i++)
  {
    if (IsFile(katalog[i]))
      {
        sprintf(files[kfiles],katalog[i]);
        kfiles++;
      }
      else
      {
        sprintf(folders[kfolders],katalog[i]);
        kfolders++;
      }
  }
  VporiadkuvatyKatalog();
  kataloglength=1+kfolders+kfiles;
  for (int i=1;i<kfolders+1;i++)
  {
    sprintf(katalog[i],folders[i+1]);
  }
  for (int i=kfolders+1;i<kataloglength;i++)
  {
    sprintf(katalog[i],files[i+1-kfolders]);
  }
  sprintf(name," %i %i",kfiles,kfolders);
  ShowMSG(1,(int)name);*/
  if (kataloglength>1) {katalogcurent=1;}
  
  if (kataloglength>2)
  {
    for (int i=1;i<kataloglength-1;i++)
    {
      for (int j=i+1;j<kataloglength;j++)
      {
        if (strcmp_nocase(katalog[i],katalog[j])>0)
        {
          sprintf(name,katalog[i]);
          sprintf(katalog[i],katalog[j]);
          sprintf(katalog[j],name);
        }
      }
    }
  }
}
    

const char color1[4]={0x50,0x00,0x00,0x20};
const char color2[4]={0x99,0x99,0x99,0x50};
GBSTMR MessageTimer;
int toview=0;
char texttoview[256];
void ShowMess()
{
  if (toview)
  {
    int textfontsize;
#ifdef NEWSGOLD
#ifdef ELKA
    textfontsize=FONT_MEDIUM;
#else
    textfontsize=5;
#endif
#endif
    
#ifdef ELKA
    DrawRectangle(0,0,240,320,0,color1,color1);
    DrawRectangle(18,18,216,300,0,GetPaletteAdrByColorIndex(1),color2);
#else
    DrawRectangle(0,0,132,176,0,color1,color1);
    DrawRectangle(10,10,120,166,0,GetPaletteAdrByColorIndex(1),color2);
#endif
    utf8_2ws(wss.ws1,texttoview,256);
    if ((Get_WS_width(wss.ws1,7))==0){wsprintf(wss.ws1,"%t",texttoview);}
#ifdef ELKA
    DrawString(wss.ws1,21,74,216,295,textfontsize,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),color2);
#else
    DrawString(wss.ws1,12,52,120,164,textfontsize,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),color2);
#endif   
  }
}

void MessStop()
{
  if (toview)
  {
    toview=0;
    if (IsGuiOnTop(MAINGUI_ID)==1)
    {
      REDRAW();
    }
  }
}

void Message(char *text)
{
  toview=1;
  sprintf(texttoview,text);
  GBS_StartTimerProc(&MessageTimer,1000,MessStop);
  if (IsGuiOnTop(MAINGUI_ID)==1)
    {
      REDRAW();
    }
}

void RunShowInfo()
{
  timelength[cp]=ln;
  char info[256];
  sprintf(info,"%s:\r%s%s\r%s: %02i:%02i\r%s\r%s\r%s",LG_FULL_NAME,spysok[0][cp],spysok[1][cp],LG_FULL_TIME,timelength[selected]/60,timelength[selected]%60,flprp.bitrate,flprp.freq,flprp.chanl);
  Message(info);
  sprintf(info,pp);
}
void ZerMemStruct();
void RunShowInfo_1()
{
  ZerMemStruct();
  char s[256];
  sprintf(s,"%s%s",spysok[0][selected],spysok[1][selected]);
  GetBit(s);
  char info[256];
  if (timelength[selected]!=-1)
    sprintf(info,"%s:\r%s%s\r%s: %02i:%02i\r%s\r%s\r%s",LG_FULL_NAME,spysok[0][selected],spysok[1][selected],LG_FULL_TIME,timelength[selected]/60,timelength[selected]%60,flprp.bitrate,flprp.freq,flprp.chanl);
  else
    sprintf(info,"%s:\r%s%s\r%s: 00:00\r%s\r%s\r%s",LG_FULL_NAME,spysok[0][selected],spysok[1][selected],LG_FULL_TIME,flprp.bitrate,flprp.freq,flprp.chanl);
  Message(info);
  sprintf(info,pp);
}

char *GetFon()
{
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\fon.png");
  return(name);
}

int GetKatalogbackgroundcolour()
{
  return(katalogbackgroundcolour);
}

int GetKatalogFont()
{
  return(katalogfont);
}

int yy1,yy2;
volatile int scroll_disp;
volatile int max_scroll_disp;
GBSTMR tmr_scroll;
#define TMR_SEC 216*3

void DisableScroll(void)
{
  if(IsTimerProc(&tmr_scroll)) GBS_DelTimer(&tmr_scroll);
  max_scroll_disp=0;
  scroll_disp=0;
}
#ifndef VOVKA
void scroll_timer_proc(void)
{
  int i=max_scroll_disp;
  if (i&&IsGuiOnTop(MAINGUI_ID))
  {
    if (scroll_disp>=i)
    {
      scroll_disp=0;
      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
    }
    else
    {
     scroll_disp=scroll_disp+5;
     if(IsGuiOnTop(MAINGUI_ID)) GBS_StartTimerProc(&tmr_scroll,scroll_disp!=i?TMR_SEC>>4:TMR_SEC,scroll_timer_proc);  //scroll_disp!=i?TMR_SEC>>5:TMR_SEC
    }
    REDRAW();
  }
  else
  {
    DisableScroll();
  }
}
#endif

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

int numitems;
int politems;
int tlen;
int tochlen;
int scrolflag;
int xrshift,yrshift,xlshift,ylshift;
int lsoft=0,rsoft=0;
int prevfl=0;
int nextfl=0;
int longpress=0;
int format;
IMGHDR *backk=0,*fonn=0,*minus=0,*off=0,*next=0,*play=0,*plus=0,*prev=0,*progressbar=0,*rand=0,*stop=0,*playstop=0;
IMGHDR *vol[16];

void deleteIMGHDR(IMGHDR *img)
{
  mfree(img->bitmap);
  mfree(img); 
}

void delImghdr()
{
  int a=13;
  for(int i=0; i<13; i++)
  {
  a--;
  if(a==12){deleteIMGHDR(backk);}
  if(a==11){deleteIMGHDR(fonn);}
  if(a==10){deleteIMGHDR(minus);}
  if(a==9){deleteIMGHDR(off);}
  if(a==8){deleteIMGHDR(next);}
  if(a==7){deleteIMGHDR(play);}
  if(a==6){deleteIMGHDR(plus);}
  if(a==5){deleteIMGHDR(prev);}
  if(a==4){deleteIMGHDR(progressbar);}
  if(a==3){deleteIMGHDR(rand);}
  if(a==2){deleteIMGHDR(stop);}
}
  a=13;
   for(int i=0;i<16;i++)
  {
    deleteIMGHDR(vol[i]);
  }
}
int progress;
void crtIMGHDR()
{
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\background.png");
  backk=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\fon.png");
  fonn=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\minus.png");
  minus=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\next.png");
  next=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\off.png");
  off=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\play.png");
  play=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\plus.png");
  plus=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\prev.png");
  prev=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\progressbar.png");
  progressbar=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\random.png");
  rand=CreateIMGHDRFromPngFile(name, 3);
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\stop.png");
  stop=CreateIMGHDRFromPngFile(name, 3);
  for(int i=0;i<16;i++)
  {
    sprintf(name,"%sskins\\%s\\vol%i.png",playerfolder,ArrayOfSkins[curskin],i);
    vol[i]=CreateIMGHDRFromPngFile(name, 3);
  }
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  switch(WhatToView)
  {
case 0:
  
  if (IsUnlocked())
  {
  //  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\background.png");
  //  DrawImg(0,0,(int)name);
    DrwImg(backk,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
    if(ena_art)
     if(picflag)
      DrwImg(img_o,artx,arty,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
  //  sprintf(name,"%sskins\\%s\\VOL%i.png",playerfolder,ArrayOfSkins[curskin],CurentVolume);
  //  DrawImg(volumex,volumey,(int)name);
    DrwImg(vol[CurentVolume],volumex,volumey,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
    utf8_2ws(wss.ws1,playlistname,256);
    DrawString(wss.ws1,spysokx1,spysoky1,spysokx2,spysoky2,spysokfont,spysoktextattribute,
    GetPaletteAdrByColorIndex(spysoktextcolor),GetPaletteAdrByColorIndex(spysoktextbackground));
  //utf8_2ws(wss.ws1,NameOfCurentTrack,320);
  sprintf(name,"%s\r%s\r%s",ctrack,cartist,calbum);
  utf8_2ws(wss.ws1,name,320);
  if (name[0]!=' ')
  {
    wsprintf(wss.ws2,"%t\r%t\r%t",ctrack,cartist,calbum);
  }
  else
    {
      wsprintf(wss.ws2,pp);
    }
  if (Get_WS_width(wss.ws1,7)<Get_WS_width(wss.ws2,7))
  {
  DrawString(wss.ws2,songx1,songy1,songx2,songy2,songfont,songtextattribute,
    GetPaletteAdrByColorIndex(songtextcolor),GetPaletteAdrByColorIndex(songtextbackground));
  }
  else
  {
  DrawString(wss.ws1,songx1,songy1,songx2,songy2,songfont,songtextattribute,
    GetPaletteAdrByColorIndex(songtextcolor),GetPaletteAdrByColorIndex(songtextbackground));
  }
  if(NumberOfTracks==0)
    wsprintf(wss.ws1,"0%c%i",'/',NumberOfTracks);
  else
    wsprintf(wss.ws1,"%i%c%i",cp+1,'/',NumberOfTracks);
  DrawString(wss.ws1,tracksx1,tracksy1,tracksx2,tracksy2,tracksfont,trackstextattribute,
  GetPaletteAdrByColorIndex(trackstextcolor),GetPaletteAdrByColorIndex(trackstextbackground));  
    if (playing==1)
    {
      //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\stop.png");
      DrwImg(stop,play_stopx,play_stopy,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
    }
    else
    {
      //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\play.png");
      DrwImg(play,play_stopx,play_stopy,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
    }
    //DrawImg(play_stopx,play_stopy,(int)name);

  if (random==1)
  {
    //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\random.png");
    //DrawImg(randomx,randomy,(int)name);
    DrwImg(rand,randomx,randomy,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));    
  }
  if (ringoff!=0)
  {
    //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\off.png");
    //DrawImg(ringoffx,ringoffy,(int)name);
    DrwImg(off,ringoffx,ringoffy,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
  }
  else
   {
    //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\plus.png");
    if (CurentVolume<MAXVOLUME)
    {
      //DrawImg(volpx,volpy,(int)name);
      DrwImg(plus,volpx,volpy,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
    }
    //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\minus.png");
    if (CurentVolume>0)
    {
      //DrawImg(volmx,volmy,(int)name);
      DrwImg(minus,volmx,volmy,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
    }
   }
    int y;
    sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\progressbar.png");
    if (timelength[cp]!=0)
    {
      if (tm<=timelength[cp]) 
      {
        y=progressbarx1+((progressbarx2-progressbarx1-GetImgWidth((int)name))*tm)/timelength[cp];
      }
      else 
      {
        y=progressbarx2-progressbarx1-GetImgWidth((int)name);
      }
      DrawRectangle(progressbarx1,progressbary1+GetImgHeight((int)name)/2-1,y/*-GetImgWidth((int)name)*/,progressbary1+GetImgHeight((int)name)/2+1,0,
      GetPaletteAdrByColorIndex(progressbarcolour),GetPaletteAdrByColorIndex(progressbarcolour));
      //DrawImg(y,progressbary1+1,(int)name);
      DrwImg(progressbar,y,progressbary1+1,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
    }    
  if (timelength[cp]>0)
  {
    wsprintf(wss.ws1,"%02i:%02i/%02i:%02i",tm/60,tm%60,timelength[cp]/60,timelength[cp]%60);
    DrawString(wss.ws1,timex1,timey1,timex2,timey2,timefont,timetextattribute,
    GetPaletteAdrByColorIndex(timetextcolor),GetPaletteAdrByColorIndex(timetextbackground));
  }
  else
  {
  wsprintf(wss.ws1,"%02i:%02i/00:00",tm/60,tm%60);
  DrawString(wss.ws1,timex1,timey1,timex2,timey2,timefont,timetextattribute,
  GetPaletteAdrByColorIndex(timetextcolor),GetPaletteAdrByColorIndex(timetextbackground));
  }
  if(prevfl)
  {
    //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\prev.png");
    //DrawImg(prevx,prevy,(int)name);
    DrwImg(prev,prevx,prevy,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
  }
  if(nextfl)
  {
    //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\next.png");
    //DrawImg(nextx,nexty,(int)name);
    DrwImg(next,nextx,nexty,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
  }
  sprintf(name,pp);
if(format==3){  
if(playing){  
if(ena_bit){  
  wsprintf(wss.ws1,one_s,flprp.bitrate);                                                                                                                                      
  DrawString(wss.ws1,bitx1,bity1,bitx2,bity2,bitfont,bitatr,GetPaletteAdrByColorIndex(bitcolor),GetPaletteAdrByColorIndex(23));
  }
if(ena_fr){    
  wsprintf(wss.ws1,one_s,flprp.freq);
  DrawString(wss.ws1,freqx1,freqy1,freqx2,freqy2,freqfont,freqatr,GetPaletteAdrByColorIndex(freqcolor),GetPaletteAdrByColorIndex(23));
  }
if(ena_ch){  
  wsprintf(wss.ws1,one_s,flprp.chanl);
  DrawString(wss.ws1,chanx1,chany1,chanx2,chany2,chanfont,chanatr,GetPaletteAdrByColorIndex(chancolor),GetPaletteAdrByColorIndex(23));
  }
if(ena_mp){  
  wsprintf(wss.ws1,one_s,flprp.mpg_ver);
  DrawString(wss.ws1,mpgx1,mpgy1,mpgx2,mpgy2,mpgfont,mpgatr,GetPaletteAdrByColorIndex(mpgcolor),GetPaletteAdrByColorIndex(23));
  }
if(ena_lay){  
  wsprintf(wss.ws1,one_s,flprp.layer);
  DrawString(wss.ws1,lax1,lay1,lax2,lay2,lafont,laatr,GetPaletteAdrByColorIndex(lacolor),GetPaletteAdrByColorIndex(23));
  }
}
}
else{
  if(format==29)
    if(ena_mp){  
  wsprintf(wss.ws1,one_s,"AAC");
  DrawString(wss.ws1,mpgx1,mpgy1,mpgx2,mpgy2,mpgfont,mpgatr,GetPaletteAdrByColorIndex(mpgcolor),GetPaletteAdrByColorIndex(23));
  }
}
}
 
  else
    {
#ifdef ELKA
      DrawRectangle(0,0,240,320,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
#else
      DrawRectangle(0,0,132,176,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
#endif
      TTime ktime;
      TDate date;
      GetDateTime(&date,&ktime);
      wsprintf(wss.ws1,"%i:%i%i",ktime.hour,ktime.min/10,ktime.min%10);
#ifdef ELKA
      DrawString(wss.ws1,0,158,240,320,FONT_LARGE_BOLD,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
#else
      DrawString(wss.ws1,0,88,132,176,FONT_LARGE_BOLD,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
#endif      
      
      
      sprintf(name,"%s\r%s\r%s",ctrack,cartist,calbum);
      utf8_2ws(wss.ws1,name,320);
      if (name[0]!=' ')
      {
        wsprintf(wss.ws2,"%t\r%t\r%t",ctrack,cartist,calbum);
      }
      else
      {
        wsprintf(wss.ws2,pp);
      }
      if (Get_WS_width(wss.ws1,7)<Get_WS_width(wss.ws2,7))
      {
#ifdef ELKA
        DrawString(wss.ws2,2,4,234,158,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
#else
        DrawString(wss.ws2,2,2,130,88,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
#endif        
      }
      else
      {
#ifdef ELKA
        DrawString(wss.ws1,2,2,234,158,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
#else
        DrawString(wss.ws1,2,2,130,88,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
#endif          
      }
    }
  break;
case 1: //Плейлист
  {
    //DrawImg(0,0,(int)GetFon());
    DrwImg(fonn,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));  

/*#ifndef VOVKA
    DrwImg(fonn,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));  
#else
    DrawRectangle(0,0,240,320,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
#endif*/
    int font=katalogfont;
    numitems=(320-23-(GetFontYSIZE(font)+4))/GetFontYSIZE(font)-1;
    politems=numitems/2;
    if (NumberOfTracks>numitems)
    {
    if((selected-politems)>=0){top=selected-politems;}else{top=0;}
    if (top+numitems+1<NumberOfTracks){bottom=NumberOfTracks;}
    bottom=top+numitems+1;
    if(bottom>NumberOfTracks)
    {
      while (bottom!=NumberOfTracks) {bottom--;top--;}
    }
    }
    else
    {
      top=0;
      bottom=NumberOfTracks;
    }
    if (NumberOfTracks!=0)
    {
    for (int i=top;i<bottom;i++)
    {
      char t[256];
      //int j;                 
      /*if (spysok[1][i][0]==0x1F)
      {
        j=240;
        sprintf(t,spysok[1][i]);
        t[0]=' ';
      }
      else
      {
        j=240;
        sprintf(t,pp_s,spysok[1][i]);
      }*/
      
      sprintf(t,spysok[1][i]);
      t[strlen(t)-4]='\0';//убираем расширение 
      ////////////////////////
        int colour=katalogfontcolour;
        if (spysokselected[i]==1){colour=katalogselectedcolour;}
        //utf8_2ws(wss.ws2,t,320);
       // if(i==top) {yy1=24;yy2=24+GetFontYSIZE(font);}else {yy1=24+(i-top)*(GetFontYSIZE(font)); yy2=24+(i-top+1)*(GetFontYSIZE(font));}
      if (timelength[i]!=-1/*||timelength[i]!=0*/)
      {wsprintf(ows.ws1,"%02i:%02i",timelength[i]/60,timelength[i]%60);}
      else
      {wsprintf(ows.ws1,"...");}
      if(i==top) {yy1=24;yy2=24+GetFontYSIZE(font);}else {yy1=24+(i-top)*(GetFontYSIZE(font)); yy2=24+(i-top+1)*(GetFontYSIZE(font));}

        wsprintf(wss.ws1,"00:00");
        tlen=(Get_WS_width(wss.ws1,font));
        wsprintf(wss.ws1,tt);
        tochlen=(Get_WS_width(wss.ws1,font));
        str_2ws(wss.ws1,t,strlen(t));
        str_2ws(wss.ws2,t,strlen(t));
#ifndef VOVKA
        if(i==selected&&(Get_WS_width(wss.ws1,font)<=236-tlen))
        {
          scrolflag=0;
          goto a;
        }
        if(i==selected&&(Get_WS_width(wss.ws1,font)>236-tlen))
        {
          scrolflag=1;
          goto a;
        }
#endif
        if((Get_WS_width(wss.ws1,font)<=236-tlen))
           goto a;           
        while(Get_WS_width(wss.ws1,font)>236-tlen-tochlen)
        {
          t[strlen(t)-1]='\0';
          str_2ws(wss.ws1,t,strlen(t));
        }
        if((Get_WS_width(wss.ws1,font)<=236-tlen-tochlen))
         {
           wsprintf(wss.ws2,tt);
           wstrcat(wss.ws1,wss.ws2);
         }
    a:
        if (i!=selected)
        {
        /*utf8_2ws(wss.ws1,t,j);
#ifdef ELKA        
        if ((Get_WS_width(wss.ws1,font ))!=(Get_WS_width(wss.ws2,font )))
#else
        if ((Get_WS_width(wss.ws1,FONT_SMALL))!=(Get_WS_width(wss.ws2,FONT_SMALL)))
#endif
        {
          wsprintf(wss.ws2,"...");
          wstrcat(wss.ws1,wss.ws2);
          //utf8_2ws(wss.ws2,t,320);
          //if ((Get_WS_width(wss.ws1,FONT_SMALL))>=(Get_WS_width(wss.ws2,FONT_SMALL))){wss.ws1=wss.ws2;}
        }*/
        DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-4-tlen,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(23));
        DrawString(ows.ws1,ScreenW()-2-(tlen+4),yy1,ScreenW()-2,yy2,font,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
       }
      else
      {
#ifndef VOVKA
        if(longpress==1)
          DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-4-tlen,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
        else
        if(scrolflag==0)
          DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-4-tlen,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
        else
        { 
          int i=Get_WS_width(wss.ws1,font);  //Определяет кол-во пикселей при этом шрифте (или что то вроде того...)
	  i-=(ScreenW()-9-tlen);   //До куда докручивать
	  if (i<0)
	  {
	    DisableScroll();
	  }else{
	    if (!max_scroll_disp)
	    {
	      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
	    }
	    max_scroll_disp=i;
	  }
          //scrooltext(wss.ws1,1);
          DrawScrollString(wss.ws1,katalogxotstup,yy1,ScreenW()-4-tlen,yy2,scroll_disp+1,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
        }
#else
        DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-4-tlen,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
        DrawString(ows.ws1,ScreenW()-2-(tlen+4),yy1,ScreenW()-2,yy2,font,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
#endif
    }
    }
    /*for (int i=top;i<bottom;i++)
    {
      if (timelength[i]!=-1)
      {wsprintf(wss.ws1,"%02i:%02i",timelength[i]/60,timelength[i]%60);}
      else
      {wsprintf(wss.ws1,"...");}
      if (i==selected)
      {
        bkcolor=katalogbackgroundcolour;
      }
      else
      {
        bkcolor=23;
      }
     if(i==top) {yy1=24;yy2=24+GetFontYSIZE(font);}else {yy1=24+(i-top)*(GetFontYSIZE(font)); yy2=24+(i-top+1)*(GetFontYSIZE(font));}
      DrawString(wss.ws1,ScreenW()-2-(tlen+4),yy1,ScreenW()-2,yy2,font,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(bkcolor));
    }*/
    }
    wsprintf(wss.ws1,"%i%c%i",(NumberOfTracks==0) ? selected : selected+1,'/',NumberOfTracks);
    DrawString(wss.ws1,1,3,ScreenW()-2,ScreenH(),FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23)); 
    utf8_2ws(wss.ws1,playlistname,ScreenH());
    DrawString(wss.ws1,5,3,179,23,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    wsprintf(wss.ws1,pt,LG_REMOVE);
    DrawString(wss.ws1,5+xlshift,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+ylshift,234,320,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    wsprintf(wss.ws1,pt,LG_ADD);
    DrawString(wss.ws1,1,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+yrshift,234-xrshift,320,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    if(timelist>=3600)
      {
        wsprintf(wss.ws1,"%02i:%02i:%02i",timelist/3600,(timelist%3600)/60,(timelist%3600)%60);
        DrawString(wss.ws1,0,3,188,23,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
      }
    else
      {
        wsprintf(wss.ws1,"%02i:%02i",timelist/60,timelist%60);
        DrawString(wss.ws1,0,3,188,23,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
      }

  }
  break;
  case 2:
    {
      DrawRectangle(0,0,ScreenW(),ScreenH(),0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
      utf8_2ws(wss.ws1,playlistname,320);
      DrawString(wss.ws1,1,5,ScreenH()-6,72,FONT_SMALL,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      utf8_2ws(wss.ws1,spysok[1][pisniashchozberigaetsia],100);
      DrawString(wss.ws1,1,50,ScreenW()-6,144,FONT_SMALL,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      DrawRectangle(0,155,ScreenW()-1,165,0,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      DrawRectangle(2,157,(ScreenW()-6)*(pisniashchozberigaetsia+1)/NumberOfTracks,163,0,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(12));
      wsprintf(wss.ws1,"%i%c%i",pisniashchozberigaetsia+1,'/',NumberOfTracks);
      DrawString(wss.ws1,0,100,ScreenW(),180,FONT_SMALL,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(12));
   }
    break;
case 3:
  {
    //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\fon.png");
    //DrawImg(0,0,(int)name);
    DrwImg(fonn,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));  
/*#ifndef VOVKA
    DrwImg(fonn,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));  
#else
    DrawRectangle(0,0,240,320,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
#endif*/
    int font=katalogfont;
    numitems=(320-23-(GetFontYSIZE(font)+4))/GetFontYSIZE(font)-1;
    politems=numitems/2;
    if(VIEW==1)
    {
    if (kataloglength>numitems)
    {
    if((katalogcurent-politems)>=0){top=katalogcurent-politems;}else{top=0;}
    if (top+numitems+1<kataloglength){bottom=kataloglength;}
    bottom=top+numitems+1;
    if(bottom>kataloglength)
    {
      while (bottom!=kataloglength) {bottom--;top--;}
    }
    }
    else
    {
      top=0;
      bottom=kataloglength;
    }
    for (int i=top;i<bottom;i++)
    {
      char t[256];
      /*int j;
      if (katalog[i][0]==0x1F)
      {
        j=60;
        sprintf(t,katalog[i]);
        t[0]=' ';
      }
      else
      {
        j=60;
        sprintf(t,pp_s,katalog[i]);
      }*/
      ////////////////////////
      if(i==top) {yy1=24;yy2=24+GetFontYSIZE(font);}else {yy1=24+(i-top)*(GetFontYSIZE(font)); yy2=24+(i-top+1)*(GetFontYSIZE(font));}
      sprintf(t,katalog[i]);
      wsprintf(wss.ws1,tt);
      tochlen=(Get_WS_width(wss.ws1,font));
      str_2ws(wss.ws1,t,strlen(t));
      str_2ws(wss.ws2,t,strlen(t));
#ifndef VOVKA      
      if(i==katalogcurent&&(Get_WS_width(wss.ws1,font)<=236-tlen))
        {
          scrolflag=0;
          goto b;
        }
        if(i==katalogcurent&&(Get_WS_width(wss.ws1,font)>236-tlen))
        {
          scrolflag=1;
          goto b;
        }
#endif
      if((Get_WS_width(wss.ws1,font)<=236))
         goto b;           
      while(Get_WS_width(wss.ws1,font)>236-tochlen)
       {
         t[strlen(t)-1]='\0';
         str_2ws(wss.ws1,t,strlen(t));
       }
      if
        (Get_WS_width(wss.ws1,font)<=236-tochlen)
       {
          wsprintf(wss.ws2,tt);
          wstrcat(wss.ws1,wss.ws2);
        }
      int colour;
    b:
      if (katalogselected[i]==1){colour=katalogselectedcolour;}else{colour=katalogfontcolour;};
        if (i!=katalogcurent)
        {
        /*utf8_2ws(wss.ws1,t,j);
#ifdef ELKA        
        if ((Get_WS_width(wss.ws1,FONT_SMALL_BOLD))!=(Get_WS_width(wss.ws2,FONT_SMALL_BOLD)))
#else
        if ((Get_WS_width(wss.ws1,FONT_SMALL))!=(Get_WS_width(wss.ws2,FONT_SMALL)))
#endif
        {
          wsprintf(wss.ws2,"...");
          wstrcat(wss.ws1,wss.ws2);
          //utf8_2ws(wss.ws2,t,320);
          //if ((Get_WS_width(wss.ws1,7))>=(Get_WS_width(wss.ws2,7))){wss.ws1=wss.ws2;}
        }*/
        DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-2,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(23));
        }
        else
      {
#ifndef VOVKA
        if(longpress==1)
          DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-2,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
        else
        if(scrolflag==0)
          DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-2,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
        else
        {
          int i=Get_WS_width(wss.ws1,font);  //Определяет кол-во пикселей при этом шрифте (или что то вроде того...)
	  i-=(ScreenW()-9);   //До куда докручивать
	  if (i<0)
	  {
	    DisableScroll();
	  }else{
	    if (!max_scroll_disp)
	    {
	      GBS_StartTimerProc(&tmr_scroll,TMR_SEC,scroll_timer_proc);
	    }
	    max_scroll_disp=i;
	  }
          DrawScrollString(wss.ws1,katalogxotstup,yy1,ScreenW()-2,yy2,scroll_disp+1,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
        }
#else
        DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-2,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(colour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));
#endif
    }
    }
  }
  else
  {
    for(int i=0;i<2;i++)
    {
      if(i==0) {yy1=24;yy2=24+GetFontYSIZE(font);}else {yy1=24+(GetFontYSIZE(font)); yy2=24+2*(GetFontYSIZE(font));}
      if(i==0) wsprintf(wss.ws1,"0:\\");
      else     wsprintf(wss.ws1,"4:\\");
      if(i==disk)
        DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-2,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
      else
        DrawString(wss.ws1,katalogxotstup,yy1,ScreenW()-2,yy2,font,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogselectedcolour),GetPaletteAdrByColorIndex(katalogbackgroundcolour));

    }
  }
    //utf8_2ws(wss.ws1,playlistname,320);
    //DrawString(wss.ws1,1,3,90,15,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(color),GetPaletteAdrByColorIndex(background));
    wsprintf(wss.ws1,pt,LG_SELECT);
    DrawString(wss.ws1,5+xlshift,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+ylshift,234,320,FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    wsprintf(wss.ws1,"OK");
    DrawString(wss.ws1,1,ScreenH()-GetFontYSIZE(FONT_SMALL_BOLD)-2+yrshift,234-xrshift,320,FONT_SMALL_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
    //DrawLine(0,23,240,23,0,GetPaletteAdrByColorIndex(katalogfontcolour));
    //DrawLine(0,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,240,320-GetFontYSIZE(FONT_SMALL_BOLD)-4,0,GetPaletteAdrByColorIndex(katalogfontcolour));
    wsprintf(wss.ws1,pt,"Проводник");
    DrawString(wss.ws1,5,3,ScreenW()-6,ScreenH(),FONT_SMALL_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(katalogfontcolour),GetPaletteAdrByColorIndex(23));
 }
 break;
  }
  ShowMess();
}

void SaveOnlyPlaylistParams(char *playy)
{
  int f;
  char g[3];
  unsigned int err;
  g[0]=NumberOfTracks;
  g[1]=random;
  g[2]=cp;
  f=fopen(playy, A_ReadWrite/*+A_MMCStream*/, P_READ+P_WRITE, & err );
  if ( f==-1 ) 
  {
    //ShowMSG(1,(int)"Can't open test.txt");
    fclose( f, & err ); 
  }
  fwrite(f,g,3,&err);
  fclose(f,&err);
}

void SavePlaylist(void)
{
  int f;
  WhatToView=2;
  char s[1]="*";
  char g[5];
  char h[3];
  sprintf(h,"%c%c",0x0D,0x0A);
  char ss[1]="/";
  char tracklist[16];
  unsigned int err;
  if((f=fopen(PlaylistToSave, A_ReadWrite+/*A_MMCStream+*/A_Create, P_READ+P_WRITE, & err ))!=-1)
  {
    sprintf(g,"%c%c%c%c%c",NumberOfTracks,random,cp,0x0D,0x0A);
    fwrite(f,g,5,&err);
    for (pisniashchozberigaetsia=0;pisniashchozberigaetsia<NumberOfTracks;pisniashchozberigaetsia++)
    {
      fwrite(f,spysok[0][pisniashchozberigaetsia],strlen(spysok[0][pisniashchozberigaetsia]),&err);
      fwrite(f,s,1,&err);
      fwrite(f,spysok[1][pisniashchozberigaetsia],strlen(spysok[1][pisniashchozberigaetsia]),&err);
      fwrite(f,ss,1,&err);
      sprintf(tracklist,"%d",timelength[pisniashchozberigaetsia]);
      tracklist[strlen(tracklist)]='\0';
      fwrite(f,tracklist,strlen(tracklist),&err);
      fwrite(f,h,2,&err);
      if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==2)) {REDRAW();}
    }
    fclose(f,&err);
    playlistmode=1;
    const char *p=strrchr(LastPlaylist,'\\')+1;
    sprintf(playlistname,p);
    sprintf(LastPlaylist,PlaylistToSave);
    Message(WAS_SAVED);
  }
  else
  {
    fclose(f,&err);
    Message(LG_ERROR_CREATE_PLAYLIST);
  }
  pisniashchozberigaetsia=0;
  WhatToView=1;
  if (IsGuiOnTop(MAINGUI_ID)==1){REDRAW();}
}
#ifndef OBS
int findmp3length(char *playy)
{
   int file_len;
   #ifdef NEWSGOLD 
   file_len=(GetWavLen(playy)/1000);  
   return (file_len);
   #else
   TWavLen wl;
   zeromem(&wl, sizeof(wl));
   wl.type=0x2000;
   wl.wfilename=AllocWS(128);
   str_2ws(wl.wfilename,playy,128); 
   GetWavLen(&wl);
   file_len=wl.length/1000;
   return (file_len);
   #endif 
}
#endif

void findtegs()
{
  int f;
  char file[128];
  unsigned int err;
  sprintf(name,"%s%s",spysok[0][cp],spysok[1][cp]);
  FSTATS stat; 
  f=fopen(name, A_ReadOnly, P_READ, &err); 
  GetFileStats(name, &stat, &err); 
  lseek(f,(stat.size-128), 0, &err, &err); 
  fread(f, file, 128, &err);
  fclose(f, &err);

  sprintf(calbum,pp);
  sprintf(ctrack,pp);
  sprintf(cartist,pp);
  if ((file[0]=='T')&&(file[1]=='A')&&(file[2]=='G'))
  {
  int i;
  for (i=3;(file[i]!=0)&&(i<33);i++)
    {
      sprintf(ctrack,"%s%c",ctrack,file[i]);
    }
  for (i=33;(file[i]!=0)&&(i<63);i++)
    {
      sprintf(cartist,"%s%c",cartist,file[i]);
    }
  for (i=63;(file[i]!=0)&&(i<93);i++)
    {
      sprintf(calbum,"%s%c",calbum,file[i]);
    }
  }
  if (strlen(ctrack)==0)
  {
    sprintf(ctrack,spysok[1][cp]);
    if (ctrack[0]==0x1F){ctrack[0]=' ';}
    ctrack[strlen(ctrack)-4]=0;
  }
  
  /*f=fopen("0:\\1.txt", A_WriteOnly+A_Create, P_WRITE, &err); 
  fwrite(f, file, 128, &err);
  fclose(f, &err);*/
}

int str2int(const char *str)
{
  int n = 0;
  sscanf(str, percent_d, &n);
  return(n);
}
//GBSTMR mytmr1;
char now_play[256];
/*void GetBit()
{
        sprintf(bitrate,pp);
        FILE_PROP wl;
        char s[128];
        WSHDR* sndPath=AllocWS(128);
        WSHDR* sndFName=AllocWS(128);
        const char *p=strrchr(now_play,'\\')+1;
        str_2ws(sndFName,p,128);
        const char *p1=strrchr(now_play,'\\')+1;
        strncpy(s,now_play,p1-now_play);
        s[p1-now_play]='\0';
        str_2ws(sndPath,s,128);
        WSHDR *ws1 = AllocWS (128);
        str_2ws(ws1,now_play,128);
        zeromem(&wl, sizeof(wl)); // жз для чего. но только так работает
       
        wl.type = 0x1800; // тип файла 
        wl.filename = ws1; // сдесь должен быть полный путь к файлу
        wl.bitrate_ws = AllocWS (128); // задаем длину для параметра (без него хз почему но выдает ноль)
        GetFileProp(&wl,sndFName,sndPath); // получаем инфу 
        
        ws_2str(wl.bitrate_ws,bitrate,128);
        zeromem(s,128);
        FreeWS(wl.bitrate_ws);
        FreeWS(sndPath);
        FreeWS(sndFName);
        FreeWS(ws1);
       // GBS_DelTimer(&mytmr1);
}*/

int GetTM(char *fname1)
{
  int dur;
  int min=0,sec=0;
        FILE_PROP wl;
        char *d;
        char s[128];
        char tmp[3];
        WSHDR* sndPath=AllocWS(128);
        WSHDR* sndFName=AllocWS(128);
        const char *p=strrchr(fname1,'\\')+1;
        str_2ws(sndFName,p,128);
        const char *p1=strrchr(fname1,'\\')+1;
        strncpy(s,fname1,p1-fname1);
        s[p1-fname1]='\0';
        str_2ws(sndPath,s,128);
        WSHDR *ws1 = AllocWS (128);
        str_2ws(ws1,fname1,128);
        zeromem(&wl, sizeof(wl)); // жз для чего. но только так работает
        wl.type = 0x1800; // тип файла 
        wl.filename = ws1; // сдесь должен быть полный путь к файлу
        wl.duration_mp3_ws = AllocWS (128);
        GetFileProp(&wl,sndFName,sndPath); // получаем инфу 
        ws_2str(wl.duration_mp3_ws,s,128);
        d=strrchr(s,':');
          if(d)
          {
             strncpy(tmp, d+1,2);
             tmp[2]='\0';
             sec=str2int(tmp);
             strncpy(tmp, d-2,2);
             tmp[2]='\0';
             min=str2int(tmp);
             dur=min*60+sec;
          }
        else return 0;
        zeromem(s,128);
        FreeWS(wl.duration_mp3_ws);
        FreeWS(sndPath);
        FreeWS(sndFName);
        FreeWS(ws1);
        return dur;
}

IMGHDR* CreateImgHdrByAnyFile (WSHDR * path,short width, short height/*, int rot*/){
  unsigned int err=0;
  float sz;
  int msz,uid;
  int scal;
  HObj mypicObj;
  IMGHDR *tmpimg,*myimg=NULL;  
  WSHDR *ext;
  short pos;
  int len;
  if (!path) goto exit0;
  len=wstrlen(path); 
  pos= wstrrchr(path,len,'.'); 
  if (!pos) goto exit0;

  ext=AllocWS(len-pos);
  wstrcpybypos(ext,path,pos+1,len-pos);
  uid=GetExtUid_ws(ext);      
  FreeWS(ext);
  mypicObj=Obs_CreateObject(uid,0x2d,0x02,0x80A8,1,1,&err);    
   if (err)  return 0;
  err=Obs_SetInput_File(mypicObj,0,path);
    if (err)  goto exit1;  
  if (width!=0){ 
    /*unsigned*/ short w/*=width*/;  
    /*unsigned*/ short h/*=height*/;
    
    err=Obs_GetInfo(mypicObj,0);    
      if (err)  goto exit1;  
    err=Obs_GetInputImageSize(mypicObj,&w,&h);    
      if (err)  goto exit1;
    if(w>h)
      if(w<width)
      {
        sz=(float)(width/w);
        scal=sz;
        if(scal>=3)scal=2;
      }
      else scal=0;
    else
      if(h<height)
      {
        sz=(float)(height/h);
        scal=sz;
        if(scal>=3)scal=2;
      }
      else scal=0;        
    err=Obs_SetOutputImageSize(mypicObj,width,height);
      if (err)  goto exit1;      
    /*if (rot){  
      err= Obs_SetRotation(mypicObj,rot);
        if (err)  goto exit1;      
    }*/
    err=Obs_SetScaling(mypicObj,1+scal);
      if (err)  goto exit1;          
  }
  err=Obs_Start(mypicObj);
    if (err)  goto exit1;            
  err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
    if (err)  goto exit1;             
  msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
  myimg=malloc(sizeof(IMGHDR));
  myimg->w=tmpimg->w;
  myimg->h=tmpimg->h;
  myimg->bpnum=tmpimg->bpnum;
  myimg->bitmap=malloc(msz);
  memcpy(myimg->bitmap,tmpimg->bitmap,msz);
exit1:
  Obs_DestroyObject(mypicObj);
exit0:
  picflag=1;  
  return myimg;
}
int readskin;
char tmpfolder[256];
void CreateIMGHDR(/*char *fname*/)
{
  char fname[256];
  strcpy(fname,now_play);
  FSTATS stat;
  char folder[12]/*="folder.jpg"*/;
  sprintf(folder,"folder.jpg");
  char cover[12]/*="cover.jpg"*/;
  sprintf(cover,"cover.jpg");
  unsigned int ul;
  char filename[256];
  char s[128];
  WSHDR *mws=AllocWS(256);
  const char *p1=strrchr(fname,'\\')+1;
  strncpy(s,fname,p1-fname);
  s[p1-fname]='\0';
  if(readskin==1){readskin=0;goto b;}
  if(strcmp(s,tmpfolder)==0) return;
  else
  if(picflag==1)
  {
    picflag=0;
    mfree(img_o->bitmap);
    mfree(img_o);
  }  
b:
  strcpy(tmpfolder,s);
  tmpfolder[strlen(tmpfolder)]='\0';
  strcpy(filename,s);
  strcat(filename,cover);
  if (GetFileStats(filename,&stat,&ul)!=-1) goto a;
  strcpy(filename,s);
  strcat(filename,folder);
  if (GetFileStats(filename,&stat,&ul)==-1)
  {
    FreeWS(mws);
    if(picflag==1)
    {
      picflag=0;
      mfree(img_o->bitmap);
      mfree(img_o);
    }  
    return;
  }
a:
  str_2ws(mws,filename,256);
  DrawString(mws,0,0,240,320,3,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  img_o=CreateImgHdrByAnyFile(mws,art_wh,art_wh);
  FreeWS(mws);
}

int play_flag;
int show_tags=0;
int onfokus=0;
void tagstm()
{
  wsprintf(ows.ws1,pp);
  wsprintf(ows.ws2,pp);
  show_tags=0;
  GBS_DelTimer(&tags);
  DirectRedrawGUI();
}

void SendStatus(void);
void Play(char *fname1)
{ 
  play_flag=1;
  CanRewind=0;
  DIR_ENTRY de;
            unsigned int err;
            char s[256];
            sprintf(s,fname1);
            if(FindFirstFile(&de,s,&err))
{
  if (!IsCalling())
  {
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname1,&fstats,&err)!=-1)
    {
      StopTMR(1);
#ifdef OBS
      unsigned int err=0;
      KillObj();
      WSHDR *ext;      
      char *extch;
      int uid;
      short pos;
      int len;
      WSHDR* fname=AllocWS(256);
      str_2ws(fname,fname1,256);
      if (!fname)goto exit0;
      len=wstrlen(fname); 
      pos=wstrrchr(fname,len,'.'); 
      if (!pos)goto exit0;

      ext=AllocWS(len-pos);
      wstrcpybypos(ext,fname,pos+1,len-pos);
      // В нижний регистр
      extch = malloc(wstrlen(ext) * 2 + 1);
      ws_2utf8(ext, extch, &len, wstrlen(ext) * 2 + 1);
      strtolower(extch, extch, -1);
      wsprintf(ext,percent_t,extch);
      mfree(extch);
      // В нижний регистр
      uid=GetExtUid_ws(ext);
      FreeWS(ext);
      gObj=Obs_CreateObject(uid,0x34,2,MSG_Report,1,0,&err);
      err=Obs_SetInput_File(gObj,0,fname);
      if (err)  goto exit1;
#ifdef NEWSGOLD
#ifndef ELKA
      Obs_Sound_SetPurpose(gObj,0x16);
#else
      Obs_Mam_SetPurpose(gObj,0x16);
#endif
#else
      Obs_Mam_SetPurpose(gObj,0x16);
#endif
      if (ringoff==1) Obs_Sound_SetVolumeEx(gObj, 0, 1);
      else Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
        Obs_Prepare(gObj);
        /*int lnnn;
        char fff[64];
        GetPlayObjDuration((void*)gObj, &lnnn);
        sprintf(fff,"%d",lnnn);
        ShowMSG(1,(int)fff);*/
      //Obs_Start(gObj);
      //EXT_REDRAW();
  sprintf(now_play,fname1);
  format=uid;
  if(uid!=29) //не AAC
  {}  //if(WhatToView==0) GetBit(fname1);//лучше через сабпрок, и пусть рисуется через 2-3 секунды, чем песни пеключаются не сразу  
  else sprintf(bitrate,pp);
  goto exit0;
 
exit1:
 // ShowMSG(1,(int)"ЫЫЫЫ");
  Obs_DestroyObject(gObj);
  gObj=NULL;
exit0:
#else  
     PLAYFILE_OPT pfopt;
     char s[128];
     WSHDR* sndPath=AllocWS(128);
     WSHDR* sndFName=AllocWS(128);
     const char *p=strrchr(fname1,'\\')+1;
     str_2ws(sndFName,p,128);
     
      const char *p1=strrchr(fname1,'\\')+1;
      strncpy(s,fname1,p1-fname1);
      s[p1-fname1]='\0';
      str_2ws(sndPath,s,128);
      zeromem(&pfopt,sizeof(PLAYFILE_OPT));
      pfopt.repeat_num=1;
      pfopt.time_between_play=0;
      pfopt.play_first=0;
      pfopt.volume=0;//GetVolLevel();

#ifdef NEWSGOLD
      pfopt.unk6=1;
      pfopt.unk7=1;
      pfopt.unk9=2;
      PLAY_ID=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt); // Вместо 0xC было 0x10 ... Пробуйте так!!
#else 
      pfopt.unk4=0x80000000;
      pfopt.unk5=1;
      PLAY_ID=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt);
      FreeWS(sndPath);
      FreeWS(sndFName);
#endif
#endif
#ifndef OBS
      CanPlayNext=0;
#endif
       if ((timelength[cp]==-1)||(timelength[cp]==0))
        {
          timelength[cp]=ln;
        }
      FreeWS(fname);
      TTime ktime;
      TDate date;
      GetDateTime(&date,&ktime);
      timehms[2]=ktime.sec;
     /* if (ringoff==0)
      {
#ifndef OBS
    if(PLAY_ID!=-1)PlayMelody_ChangeVolume(PLAY_ID,0);
#else
    Obs_Sound_SetVolumeEx(gObj, 0, 1);
#endif
      }*/
      findtegs();
      if(ena_art)SUBPROC((void*)CreateIMGHDR/*(fname1)*/);
      SendStatus();
        if(ena_tag)
        {
          char tags[256];
          sprintf(tags,"%s\r%s\r%s",ctrack,cartist,calbum);
          tags[strlen(tags)]='\0';
          //ShowMSG(1,(int)tags);
          eipc.name_to=ipc_extraplay;
          eipc.name_from=ipc_my_name;
          eipc.data=(void*)tags;
          GBS_SendMessage(MMI_CEPID,MSG_IPC,50,&eipc);
        }
      //CreateIMGHDR();
      
        
      sprintf(NameOfCurentTrack,"%s - %s - %s",ctrack,cartist,calbum);
      UpdateCSMname();
      if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0)){REDRAW();}
    }
  }
}
       else 
       {
         tm=0;
         PlayNext();
       }
   FindClose(&de,&err);
   //sprintf(now_play,fname1);
   //SUBPROC((void*)GetBit);//лучше через сабпрок, и пусть рисуется через 2-3 секунды, чем песни пеключаются не сразу
      //   GBS_StartTimerProc(&mytmr1,262,GetBit); //через таймер получается хуйня, вермя начинает отсчитываться только через 2-3 секунды
   //CanRewind=1;
}

void LoadPlaylist(char *playy)
{
  int f,count=0;
  char list[20000];
  char t[1];
  unsigned int err;
  char ddd[128];
  sprintf(ddd,playy);
  
  f=fopen(ddd, A_ReadOnly, P_READ, & err );
  DIR_ENTRY de;
  FindFirstFile(&de,ddd,&err);
  fread(f,list,de.file_size,&err);
  fclose(f,&err);
  FindClose(&de,&err);
  NumberOfTracks=list[0];
  random=list[1];
  cp=list[2];
  t[0]=list[5];
  char tracktime[16];
  count=5;
  for (int i=0;i<NumberOfTracks;i++)//Вот так грузится ipl
  {
  while (t[0]!='*')
  {
    sprintf(spysok[0][i],"%s%c",spysok[0][i],t[0]);
    count++;
    t[0]=list[count];
  }
  count++;t[0]=list[count];
  while (t[0]!='/')
  {
    sprintf(spysok[1][i],"%s%c",spysok[1][i],t[0]);
    count++;
    t[0]=list[count];
  }
  count++;
  t[0]=list[count];
  sprintf(tracktime,pp);
  while (t[0]!=0x0D)
  {
    //if(t[0]==0x2D) {flag=0;break;}
    sprintf(tracktime,"%s%c",tracktime,t[0]);
    count++;
    t[0]=list[count];
  }
  timelength[i]=str2int(tracktime); 
  count++;
  count++;
  t[0]=list[count];
  }
}

void LoadM3uPlaylist(char *playy)
{
  int f,count=0;
  char list[20000];
  char t[1];
  unsigned int err;
  char ddd[128];
  sprintf(ddd,playy);
  
  f=fopen(ddd, A_ReadOnly/*+A_MMCStream*/, P_READ, & err );
  DIR_ENTRY de;
  FindFirstFile(&de,playy,&err);
  fread(f,list,de.file_size,&err);
  fclose(f,&err);
  t[0]=list[9];
  count=9;
  char temp[400]="";

  //А так м3у
  for (int i=0;(count<de.file_size);i++)
  {
    sprintf(temp,pp);//Обнуляем
  while (t[0]!=0x0D)
  {
    sprintf(temp,"%s%c",temp,t[0]);
    count++;
    t[0]=list[count];
  }
  count++;
  count++;
  
  
      char s[128];
      const char *p=strrchr(temp,'\\')+1;
      sprintf(spysok[1][i],p);
      strncpy(s,temp,p-temp);
      s[p-temp]='\0';
      sprintf(spysok[0][i],s,128);
      
  t[0]=list[count];
  NumberOfTracks=i+1;
  }
  FindClose(&de,&err);
}

int whattoplaynext()
{
  int neprograni=0;
  for (int i=0;i<NumberOfTracks;i++) {if (notplayed[i]==0){neprograni++;}}
  if (neprograni>0)
  {
    TTime time;
    TDate date;
    GetDateTime(&date,&time);
    int l=time.min*5+time.sec;//Типа случайно :)
    while (neprograni<l){l=l-neprograni;}
    //l=l%neprograni;//Чомусь це пікає O_о
    neprograni=0;
    for (int i=0;i<NumberOfTracks;i++)
    {
      if (notplayed[i]==0)
      {
        neprograni++;
        if (l==neprograni)
        {
          notplayed[i]=cp;
          if (notplayed[cp]==0) 
          {
            notplayed[cp]=10000;
          }
          return(i);
        }
      }
    }
  }
  else 
  {
    for (int i=0;i<NumberOfTracks;i++){notplayed[i]=0;}
    return(whattoplaynext());
    //Все песни проиграны
  }
  return(255);
}

int whattoplayprev()
{
  if(notplayed[cp]!=10000)
  {
    return(notplayed[cp]);
  }
  else
  {
    return(whattoplaynext());
  }
}

void r()
{
  REDRAW();
}

/*void showvolume()
{
  //sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\plus.png");
  if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0)&&(IsUnlocked()))
  {
    //sprintf(name,"%sskins\\%s\\VOL%i.png",playerfolder,ArrayOfSkins[curskin],CurentVolume);
    //DrawImg(volumex,volumey,(int)name);
    //DrwImg(vol[CurentVolume],volumex,volumey,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));

    REDRAW();
  }
  else
  {
    GBS_StartTimerProc(&RedrawTimer,216,r);
  }
}*/

void PlayNext()
{
#ifndef OBS
  if ((CanPlayNext)&&(NumberOfTracks!=0))
#else
  if ((NumberOfTracks!=0)) 
#endif
  {
  if (random==0)
     {
       if (cp>NumberOfTracks-2)
        {
          cp=0;
        }
       else 
         {
           cp++;
         }
     }
  else 
    {
      cp=whattoplaynext();
    }
  char s[256];
  sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
  playing=1;
  JaPerekliuchyvPisniu=1;
#ifndef OBS
  if(PLAY_ID!=-1)PlayMelody_StopPlayback(PLAY_ID);
#else
  Obs_Stop (gObj);
#endif  
  Play(s);
  }
  else
  {
    if (NumberOfTracks!=0)
    {
      GBS_StartTimerProc(&PlayNextTimer,30,PlayNext);
    }
  }
}

void PlayPrevious()
{
#ifndef OBS
  if ((CanPlayNext)&&(NumberOfTracks!=0))
#else
  if ((NumberOfTracks!=0)) 
#endif
  {
  if (random==0)
   {
     if (cp<1) 
       {
         cp=NumberOfTracks-1;
       }
     else 
       {
         cp--;
       }
   }
  else
    {
      cp=whattoplayprev();
    }
    char s[256];
    sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
    playing=1;
    JaPerekliuchyvPisniu=1;
#ifndef OBS
  if(PLAY_ID!=-1)PlayMelody_StopPlayback(PLAY_ID);
#else
  Obs_Stop (gObj);
#endif      
    Play(s);
  }
  else
  {
   if (NumberOfTracks!=0){GBS_StartTimerProc(&PlayNextTimer,30,PlayPrevious);}
  }
}



void VolumeDown()
{
  ringoff=0;
  if (CurentVolume>0)
    {
      CurentVolume--;
#ifdef NEWSGOLD
#ifndef OBS
    if(PLAY_ID!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], CurentVolume, 1);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#else
#ifndef OBS
    if(PLAY_ID!=-1)PlayMelody_ChangeVolume(phandle,CurentVolume);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#endif
    }
  else
  {
    CurentVolume=0;
  }
  getvol=CurentVolume;
  //showvolume();
}

void VolumeMute()
{
  if (ringoff==0)
    {
#ifdef NEWSGOLD
#ifndef OBS
    if(PLAY_ID!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], 0, 1);
#else
    Obs_Sound_SetVolumeEx(gObj, 0, 1);
#endif
#else
#ifndef OBS
    if(PLAY_ID!=-1)PlayMelody_ChangeVolume(phandle,0);
#else
    Obs_Sound_SetVolumeEx(gObj, 0, 1);
#endif
#endif
      ringoff=1;
      REDRAW();
    }
  else
    {
#ifdef NEWSGOLD
#ifndef OBS
    if(PLAY_ID!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], CurentVolume, 1);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#else
#ifndef OBS
    if(PLAY_ID!=-1)PlayMelody_ChangeVolume(phandle,CurentVolume);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#endif
      ringoff=0;
      REDRAW();
    }
  getvol=CurentVolume;
}

void VolumeUp()
{
  ringoff=0;
  if(CurentVolume<MAXVOLUME)
    {
      CurentVolume++;
#ifdef NEWSGOLD
#ifndef OBS
    if(PLAY_ID!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], CurentVolume, 1);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#else
#ifndef OBS
    if(PLAY_ID!=-1)PlayMelody_ChangeVolume(phandle,CurentVolume);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#endif
    }
  else
  {
    CurentVolume=MAXVOLUME;
#ifdef NEWSGOLD
#ifndef OBS
    if(PLAY_ID!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], CurentVolume, 1);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#else
#ifndef OBS
    if(PLAY_ID!=-1)PlayMelody_ChangeVolume(phandle,CurentVolume);
#else
    Obs_Sound_SetVolumeEx(gObj, CurentVolume, 1);
#endif
#endif
  }
  getvol=CurentVolume;
  //showvolume();
}
////////////////////////////////////////////////////
/*void OnRedraw2(MAIN_GUI *data) // OnRedraw
{
  sprintf(name,"%sskins\\%s%s",playerfolder,ArrayOfSkins[curskin],"\\background.png");
  DrawImg(0,0,(int)name);
}*/

void onCreate2(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose2(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  data->gui.state=0;
}

void onFocus2(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
#ifdef ELKA
  DisableIconBar(1);
#endif  
  data->gui.state=2;
  WhatToView=0;
  DisableIDLETMR();
}

void onUnfocus2(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
#ifdef ELKA
  DisableIconBar(0);
#endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int PLAYERGUI_ID;
void CloseGUI()
{
  GeneralFunc_flag1 (PLAYERGUI_ID,1);
}

int MenuKeys(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if ((msg->gbsmsg->msg==KEY_DOWN))
  {
    switch(msg->gbsmsg->submess)
    {
    case '1':{WhatToDo(Key1);}break;
    case '2':{WhatToDo(Key2);}break;
    case '3':{WhatToDo(Key3);}break;
    case '4':{WhatToDo(Key4);}break;
    case '5':{WhatToDo(Key5);}break;
    case '6':{WhatToDo(Key6);}break;
    case '7':{WhatToDo(Key7);}break;
    case '8':{WhatToDo(Key8);}break;
    case '9':{WhatToDo(Key9);}break;
    case '0':{WhatToDo(Key0);}break;
    case '*':{WhatToDo(KeyZ);}break;
    case '#':{WhatToDo(KeyR);}break;
#ifdef NEWSGOLD
    case RIGHT_SOFT:
#endif
    case RED_BUTTON:

      CloseGUI();break;
    }
    GBS_StartTimerProc(&PlayerMenu,500,CloseGUI);
    REDRAW();
  }
  return(0);
}
extern void kill_data(void *p, void (*func_p)(void *));
int method(void){return(0);}

const void * const gui_methods2[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate2,	//Create
  (void *)onClose2,	//Close
  (void *)onFocus2,	//Focus
  (void *)onUnfocus2,	//Unfocus
  (void *)MenuKeys,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method,
  (void *)method,
  0
};
#ifdef ELKA
const RECT Canvas={0,0,239,319};
#else
const RECT Canvas={0,0,131,175};
#endif
void ShowPlayerMenu()
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods2;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  PLAYERGUI_ID=CreateGUI(main_gui);
  GBS_StartTimerProc(&PlayerMenu,500,CloseGUI);
}


void SaveParams()
{
  int f;
  char h[3];
  sprintf(h,"%c%c",CurentVolume,curskin);
 // mfree(h);
  unsigned int err;
  sprintf(name,"%sparams.txt",playerfolder);
  f=fopen(name, A_ReadWrite+A_Create,P_READ+P_WRITE, & err );
  if ( f==-1 ) 
  {
    //ShowMSG(1,(int)"Can't open test.txt");
    fclose( f, & err ); 
  }
  fwrite(f,h,2,&err);
  fclose(f,&err);
}

void WriteLastPlaylist()
{
  int f;
  char h[300];
  sprintf(h,"%c%c%c%s",random+1,(cp+1)%256,strlen(LastPlaylist),LastPlaylist);
  unsigned int err;
  sprintf(name,"%slastplaylist.cfg",playerfolder);
  if ((f=fopen(name, A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE, & err ))!=-1)
  {
    fwrite(f,h,strlen(h),&err);
  }
  fclose(f,&err);
}

void ReadLastPlaylist()
{
  int f,f_1;
  char h[300];
  unsigned int err;
  sprintf(name,"%slastplaylist.cfg",playerfolder);
  if ((f=fopen(name, A_ReadOnly, P_READ, & err ))!=-1)
  {
    DIR_ENTRY de;
    FindFirstFile(&de,name,&err);
    if (de.file_size!=0)
    {
      fread(f,h,de.file_size,&err);
      random=h[0]-1;
      cp=h[1]-1;
      sprintf(LastPlaylist,pp);
      for (int i=0;i<h[2];i++)
      {
        sprintf(LastPlaylist,"%s%c",LastPlaylist,h[i+3]);
      }
    }
    FindClose(&de,&err);
    if ((f_1=fopen(LastPlaylist, A_ReadOnly, P_READ, & err ))==-1)
        sprintf(LastPlaylist,"1.new");
      fclose(f_1,&err);
  }
  fclose(f,&err);
}

void LoadParams()
{
  int f;
  char h[2];
  unsigned int err;
  sprintf(name,"%sparams.txt",playerfolder);
  f=fopen(name, A_ReadOnly, P_READ, & err );
  if (f>-1)
  {
    fread(f,h,2,&err);
    CurentVolume=h[0];
    curskin=h[1];
  }
  fclose(f,&err);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
#ifdef ELKA
  DisableIconBar(1);
#endif  
  data->gui.state=2;
  DisableIDLETMR();
  eipc.name_to=ipc_extraplay;
  eipc.name_from=ipc_my_name;
  //gipc.data=(void*)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,45,&eipc);
  onfokus=1;
}

void rereadskin()
{
  readskin=1;
  if(picflag==1)
  {
    picflag=0;
    mfree(img_o->bitmap);
    mfree(img_o);
  }  
  if(playing) if(ena_art)SUBPROC((void*)CreateIMGHDR/*(fname1)*/);
}
void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
#ifdef ELKA
  DisableIconBar(0);
#endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
  eipc.name_to=ipc_extraplay;
  eipc.name_from=ipc_my_name;
  //gipc.data=(void*)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,46,&eipc);
  onfokus=0;
}
void sskin()
{
  delImghdr();
  readskinparamsfromfile();
  rereadskin();
  crtIMGHDR();
}
const char *percc="%t";
int openconf()//Для чтения настроек с конфига
{
WSHDR *fws=AllocWS(256);
extern const char *successed_config_filename;
wsprintf(fws,percc,successed_config_filename);
ExecuteFile(fws,NULL,NULL);
FreeWS(fws);
return 0;
}

void QuitCallbackProc(int decision)
{
  if(decision==0)Quit_Required = 1;
}

void WhatToDo(int param)
{
  switch (param)
  {
  case 1:if (playing!=0)
  {
#ifndef OBS
    if(PLAY_ID!=-1)PlayMelody_StopPlayback(PLAY_ID);
#else
    Obs_Stop (gObj);
#endif
    StopTMR(2);
    REDRAW();
    playing=0;
    break;
  }
        else
  case 0:Play_PauseResume();break;
  case 2:VolumeUp();break;
  case 3:VolumeDown();break;
  case 4:{random=1-random;REDRAW();};break;
  case 5:{if (curskin>0){curskin--;}else{curskin=NumberOfSkins-1;}
  sskin();
  REDRAW();};break;
  case 6:{if (curskin<NumberOfSkins-1){curskin++;}else{curskin=0;}
  sskin();
  REDRAW();};break;
  case 7:PlayPrevious();break;
  case 8:PlayNext();break;
  case 9:{openconf();}break;
  case 10:{CreateMenuFindPlaylist();}break;
  case 11:VolumeMute();break;
  case 12:{gipc.name_to=ipc_xtask_name;
           gipc.name_from=ipc_my_name;
           gipc.data=(void *)MAINCSM_ID;
           GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
           if (IsUnlocked()) {KbdLock();}
          }break;
  case 13:MsgBoxYesNo(1,(int)LG_EXIT_Q,QuitCallbackProc);break;
  case 15:ShowMainMenu();break;
  case 16:{gipc.name_to=ipc_xtask_name;
           gipc.name_from=ipc_my_name;
           gipc.data=(void *)MAINCSM_ID;
           GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
          }break;
  case 17:
    if (IsUnlocked()) 
    {
      KbdLock();
    }
    else 
  {
    KbdUnlock();
      int z;
      switch(GetProfile()+1)
      {
      case 1:z=profile1;break;
      case 2:z=profile2;break;
      case 3:z=profile3;break;
      case 4:z=profile4;break;
      case 5:z=profile5;break;
      case 6:z=profile6;break;
      case 7:z=profile7;break;
      case 8:z=profile8;break;
      }
      SetIllumination(0,1,z,0);
  }
  REDRAW();
  break;
  case 18:{ShowMSG(1,(int)"Пусто пока-что)");}break;
  case 19:{if ((tm/60==0)&&(tm%60<5)){PlayPrevious();}else
                                                           {
                                                             char s[256];
                                                             sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
                                                             playing=1;
                                                             JaPerekliuchyvPisniu=1;
                                                             Play(s);
                                                           }
          }break;
  case 20:
    {
      RunShowInfo();
    };break;
  case 22:
    {
      ShowPlayerMenu();
    }break;
  case 21:CreateBaseOfMediafiles();break;
    
  }
}

int IsFile(char *name)
{ int i;
i=0;
while(i<200){
if(name[i]==0)break;
if(name[i]=='.')return(1);  
i++; 
}
return(0);  
}

extern const char zir[]="*";

void CreatePlaylist(char *foldder)//Прочесываем папки рекурсивно
{
  DIR_ENTRY de;
  unsigned int err;
  char path[128];
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  NumberOfTracks=0;
  /*  
  strcat(name,zir);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      if (!IsFile(name)){CreatePlaylist(name);}
    }
    while(FindNextFile(&de,&err));
  }
*/
  char format[5];
  if (strlen(format_1)!=0)
  {
  sprintf(format,"*.%s",format_1);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }
  
  if (strlen(format_2)!=0)
  {
  sprintf(format,"*.%s",format_2);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }

  if (strlen(format_3)!=0)
  {
  sprintf(format,"*.%s",format_3);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }
  
  if (strlen(format_4)!=0)
  {
  sprintf(format,"*.%s",format_4);
  
  sprintf(path,"%s%c",foldder,'\\');
  strcpy(name,path);
  
  strcat(name,format);
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,path);
      strcat(name,de.file_name);
      sprintf(spysok[1][NumberOfTracks],de.file_name);
      sprintf(spysok[0][NumberOfTracks],path);
      NumberOfTracks++;
    }
    while(FindNextFile(&de,&err));
  }
  }
  
  FindClose(&de,&err);
}

void findalllisttime()//время всего списка
{
  timelist=0;
  for(int i=0;i<NumberOfTracks+1;i++)
  {
    if(timelength[i]!=-1)
      {
        timelist+=timelength[i];
      }
  }
}
//int times=0;
void findlisttime()//время песен
{
 // if(times<NumberOfTracks)
  //{
  char s[256];
  for (int i=top;(i<bottom)&&(pracuje)&&(shukajuchas);i++)
  {
    sprintf(s,"%s%s",spysok[0][i],spysok[1][i]);
    if (timelength[i]==-1||timelength[i]==0)
    {
#ifdef NEWSGOLD
      if(strstr(spysok[1][i],"mp3"))
      {
        ZerMemStruct();
        timelength[i]=GetTime(s);
    //    times++;
      }
      else
      {
        timelength[i]=GetTM(s);//ShowMSG(1,(int)"jhkhkhjkh");
      }
      findalllisttime();
#else
      timelength[i]=findmp3length(s);
#endif
      //if (WhatToView==1){REDRAW();}
    }
  }
  //}
 /* else  
  {
    if(times>NumberOfTracks)
      times=0;
    ShowMSG(1,(int)"dsfsdfsdf");
  }*/
}


int mode1=0;
char bass=1,mid=1,treble=1,balance=1;
char msgss[256];
int aaaa=0;
int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
    if (!toview)
    {
    switch(WhatToView)
      {
      case 0:///////////////////////////Проигрывание
      {
  if(Quit_Required)return 1; //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI

  if ((msg->gbsmsg->msg==KEY_UP)&&(IsUnlocked()))
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON: MsgBoxYesNo(1,(int)LG_EXIT_Q,QuitCallbackProc);break;
    case RIGHT_SOFT:if (playing!=0)WhatToDo(1);else MsgBoxYesNo(1,(int)LG_EXIT_Q,QuitCallbackProc);break;
    case ENTER_BUTTON:WhatToDo(0);break;
    case '1':aaaa=OBS_Test(gObj,1);sprintf(msgss,perc2_d,aaaa);ShowMSG(1,(int)msgss);break;//{if(Key1==7||Key1==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key1);}break;
    case '2':{if(Key2==7||Key2==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key2);}break;
    case '3':{if(Key3==7||Key3==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key3);}break;
    case '4':{if(Key4==7||Key4==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key4);}break;
    case '5':{if(Key5==7||Key5==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key5);}break;
    case '6':{if(Key6==7||Key6==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key6);}break;
    case '7':{if(Key7==7||Key7==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key7);}break;
    case '8':{if(Key8==7||Key8==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key8);}break;
    case '9':{if(Key9==7||Key9==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key9);}break;
    case '0':{if(Key0==7||Key0==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(Key0);}break;
    case '*':{if(KeyZ==7||KeyZ==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(KeyZ);}break;
    case '#':{if(KeyR==7||KeyR==8) {prevfl=0;nextfl=0;REDRAW();}WhatToDo(KeyR);}break;
    case UP_BUTTON:VolumeUp();REDRAW();break;
    case DOWN_BUTTON:VolumeDown();REDRAW();break;
#ifdef OBS    
    case LEFT_BUTTON:prevfl=0;REDRAW();if(longpress==0){PlayPrevious();}else {StopRewind();longpress=0;}break;
    case RIGHT_BUTTON:nextfl=0;REDRAW();if(longpress==0){PlayNext();}else {StopRewind();longpress=0;}break;
#else
    case LEFT_BUTTON:PlayPrevious();break;
    case RIGHT_BUTTON:PlayNext();break;
#endif
    case LEFT_SOFT:{ShowMainMenu();}break;
    case GREEN_BUTTON: 
      //DrawImg(0,0,(int)GetFon());
      WhatToView=1;
      selected=cp;
      for (int i=0;i<256;i++){spysokselected[i]=0;}
      /*xdispnapriamok=-3;
      GBS_StartTimerProc(&Scroll,50,Scrolling);*/
      REDRAW();
      shukajuchas=1;
      timelist=0;
      findalllisttime();
      if(playing==1)
        SUBPROC((void *)findlisttime);
      else
        findlisttime();
      //SUBPROC((void *)findlisttime);
      break;
    }
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    longpress=0;
    switch(msg->gbsmsg->submess)
    {
    case LEFT_BUTTON:prevfl=1;REDRAW();break;
    case RIGHT_BUTTON:nextfl=1;REDRAW();break;
    case '1':{if(Key1==7) prevfl=1;if(Key1==8)nextfl=1;REDRAW();}break;
    case '2':{if(Key2==7) prevfl=1;if(Key2==8)nextfl=1;REDRAW();}break;
    case '3':{if(Key3==7) prevfl=1;if(Key3==8)nextfl=1;REDRAW();}break;
    case '4':{if(Key4==7) prevfl=1;if(Key4==8)nextfl=1;REDRAW();}break;
    case '5':{if(Key5==7) prevfl=1;if(Key5==8)nextfl=1;REDRAW();}break;
    case '6':{if(Key6==7) prevfl=1;if(Key6==8)nextfl=1;REDRAW();}break;
    case '7':{if(Key7==7) prevfl=1;if(Key7==8)nextfl=1;REDRAW();}break;
    case '8':{if(Key8==7) prevfl=1;if(Key8==8)nextfl=1;REDRAW();}break;
    case '9':{if(Key9==7) prevfl=1;if(Key9==8)nextfl=1;REDRAW();}break;
    case '0':{if(Key0==7) prevfl=1;if(Key0==8)nextfl=1;REDRAW();}break;
    case '*':{if(KeyZ==7) prevfl=1;if(KeyZ==8)nextfl=1;REDRAW();}break;
    case '#':{if(KeyR==7) prevfl=1;if(KeyR==8)nextfl=1;REDRAW();}break;
    }
    
}
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    if (!IsUnlocked())
  {
      int z;
      switch(GetProfile()+1)
      {
      case 1:z=profile1;break;
      case 2:z=profile2;break;
      case 3:z=profile3;break;
      case 4:z=profile4;break;
      case 5:z=profile5;break;
      case 6:z=profile6;break;
      case 7:z=profile7;break;
      case 8:z=profile8;break;
      }
      SetIllumination(0,1,z,0);
      SetIllumination(0,1,0,2000);
  }
  else 
  {
  }
    switch(msg->gbsmsg->submess)
    {
      case'#':
        {
          if (longpress!=1){WhatToDo(17);}
           longpress=1;
       }break;
    }
#ifdef OBS
    switch(msg->gbsmsg->submess)
    {
      case RIGHT_BUTTON:
        { 
          nextfl=1;
          if(CanRewind)
          if (longpress==0)
            {
            //  if (longpress!=1) 
                //if(CanRewind)
                  StartRewindToEnd();
              //longpress=1; 
              longpress=1;
            }
       }break;
    }
        switch(msg->gbsmsg->submess)
    {
    case LEFT_BUTTON:
        { 
          prevfl=1;
          if(CanRewind)
          if (longpress==0)
            {
             // if (longpress!=1)
                   StartRewindToBegin();
             // longpress=1;
              longpress=1;
            }
       }break;
    }
#endif
  }
    }
  break;
  case 1:///////////////////////////Медиатека
    {
      if (msg->gbsmsg->msg==KEY_DOWN)
      {
        //longpress=0;
        switch(msg->gbsmsg->submess)
         {
    case RIGHT_SOFT:
      {
        xrshift=2;
        yrshift=2; 
        REDRAW();
      }break;
    case LEFT_SOFT:
      {
        xlshift=2;
        ylshift=2; 
        REDRAW();
      }break;      
      case UP_BUTTON: {
        selected--;
        if(selected<0){selected=NumberOfTracks-1;}
        scroll_disp=0;
        /*xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);*/
        shukajuchas=1;
        REDRAW();
        }break;
      case DOWN_BUTTON:
        {
        selected++;
        if(NumberOfTracks==0) {selected=0;}
        if(selected>NumberOfTracks-1){selected=0;}
        scroll_disp=0;
        /*xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);*/
        shukajuchas=1;
        REDRAW();
        }break;
      case '3': {
        selected-=numitems;
        if(selected<0){selected=0;}
        scroll_disp=0;
        /*xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);*/
        shukajuchas=1;
        REDRAW();
        }break;
      case '9':
        {
        selected+=numitems;
        if(NumberOfTracks==0) {selected=0;}
        if(selected>NumberOfTracks-1){selected=NumberOfTracks-1;}
        scroll_disp=0;
        /*xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);*/
        shukajuchas=1;
        REDRAW();
        }break;
    }break;
    
      }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON:    
      {
        longpress=1;
#ifndef VOVKA
        DisableScroll();
#endif
        if (longpress==1)
         {   
        selected--;
        if(selected<0){selected=NumberOfTracks-1;}
        scroll_disp=0;
        /*xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);*/
        shukajuchas=1;
        REDRAW();
         }       
      }break;
  case DOWN_BUTTON:
    {
      longpress=1;
#ifndef VOVKA
      DisableScroll();
#endif
        if (longpress==1)
        {  
        selected++;
        if(selected>NumberOfTracks-1){selected=0;}
        scroll_disp=0;
        /*xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);*/
        shukajuchas=1;
        REDRAW();
        }
    }break;
    }
  }    
  if ((msg->gbsmsg->msg==KEY_UP)&&(IsUnlocked()))
  {
    longpress=0;
      switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON: {
        if(playing)
          SUBPROC((void *)findlisttime);
        else
          findlisttime();
        REDRAW();
         }break;
      case DOWN_BUTTON:
        {
        if(playing)
          SUBPROC((void *)findlisttime);
        else
          findlisttime();
        REDRAW();
        }break;
#ifdef NEWSGOLD
    case LEFT_BUTTON:
#endif
    case RED_BUTTON:case GREEN_BUTTON:
      {
        WhatToView=0;
        REDRAW();
        shukajuchas=0;
      }break;
      case '*':
      {
        switch(playlistmode)
        {
        case 0:
          {
            sprintf(PlaylistToSave,"%splaylists\\standart.ipl",playerfolder);
            CreateSaveAsDialog();
          };break;
        case 1:
          {
            sprintf(PlaylistToSave,LastPlaylist);
            CreateSaveAsDialog();
          };break;
        case 2:
          {
            sprintf(PlaylistToSave,"%splaylists\\%s.ipl",playerfolder,playlistname);
            CreateSaveAsDialog();
          };break;
        case 3:
          {
            sprintf(PlaylistToSave,"%splaylists\\%s.ipl",playerfolder,playlistname);
            CreateSaveAsDialog();
          };break;
        }
      }break;
    case '5':
      {
        spysokselected[selected]=1-spysokselected[selected];
        selected++;
        if(selected>NumberOfTracks-1){selected=0;}
        /*xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,Scrolling);*/
        REDRAW();
      }break;
    case '7':
      {
        str_2ws(wss.ws1,spysok[0][selected],strlen(spysok[0][selected])-1);
        str_2ws(wss.ws2,spysok[1][selected],strlen(spysok[1][selected]));
        MediaSendCSM_Open(wss.ws2, wss.ws1);
        REDRAW();
      }break;
    case '1':
      {
        RunShowInfo_1();
        //REDRAW();
      }break;  
    case '2':
      {
        int y=0;
        for (int i=0;(i<NumberOfTracks)&&(!y);i++){if(spysokselected[i]){y=1;}}
          if (!y)
          {
            int j=selected;
            selected--;
            if(selected<0){selected=NumberOfTracks-1;}
            sprintf(name,spysok[0][selected]);
            sprintf(spysok[0][selected],spysok[0][j]);
            sprintf(spysok[0][j],name);
            sprintf(name,spysok[1][selected]);
            sprintf(spysok[1][selected],spysok[1][j]);
            sprintf(spysok[1][j],name);
            long y=timelength[selected];
            timelength[selected]=timelength[j];
            timelength[j]=y;
            y=notplayed[selected];
            notplayed[selected]=notplayed[j];
            notplayed[j]=y;
            if (cp==j){cp=selected;}
            else
            {
              if (cp==selected){cp=j;}
            }
          }
          else
          {
            for (int i=0;i<NumberOfTracks;i++)
            {
              if(spysokselected[i])
              {
                int j=i;
                int t=i-1;
                if (t<0){t=NumberOfTracks-1;}
                sprintf(name,spysok[0][t]);
                sprintf(spysok[0][t],spysok[0][j]);
                sprintf(spysok[0][j],name);
                sprintf(name,spysok[1][t]);
                sprintf(spysok[1][t],spysok[1][j]);
                sprintf(spysok[1][j],name);
                long y=timelength[t];
                timelength[t]=timelength[j];
                timelength[j]=y;
                y=notplayed[t];
                notplayed[t]=notplayed[j];
                notplayed[j]=y;
                y=spysokselected[t];
                spysokselected[t]=spysokselected[j];
                spysokselected[j]=y;
                if (cp==j){cp=i;}
                else
                {
                  if (cp==t){cp=j;}
                }
              }
            }
          }
          /* xdisp=1;
           xdispnapriamok=-3;
           GBS_StartTimerProc(&Scroll,50,Scrolling);*/
           REDRAW();
      };break;
    case '8':
      {
        int y=0;
        for (int i=0;(i<NumberOfTracks)&&(!y);i++){if(spysokselected[i]){y=1;}}
          if (!y)
          {
            int j=selected;
            selected++;
            if(selected>NumberOfTracks-1){selected=0;}
            sprintf(name,spysok[0][selected]);
            sprintf(spysok[0][selected],spysok[0][j]);
            sprintf(spysok[0][j],name);
            sprintf(name,spysok[1][selected]);
            sprintf(spysok[1][selected],spysok[1][j]);
            sprintf(spysok[1][j],name);
            long y=timelength[selected];
            timelength[selected]=timelength[j];
            timelength[j]=y;
            y=notplayed[selected];
            notplayed[selected]=notplayed[j];
            notplayed[j]=y;
            if (cp==j){cp=selected;}
            else
            {
              if (cp==selected){cp=j;}
            }
          }
          else
          {
            for (int i=0;i<NumberOfTracks;i++)
            {
              if(spysokselected[i])
              {
                int j=i;
                int t=i+1;
                if (t>NumberOfTracks-1){t=0;}
                sprintf(name,spysok[0][t]);
                sprintf(spysok[0][t],spysok[0][j]);
                sprintf(spysok[0][j],name);
                sprintf(name,spysok[1][t]);
                sprintf(spysok[1][t],spysok[1][j]);
                sprintf(spysok[1][j],name);
                long y=timelength[t];
                timelength[t]=timelength[j];
                timelength[j]=y;
                y=notplayed[t];
                notplayed[t]=notplayed[j];
                notplayed[j]=y;
                y=spysokselected[t];
                spysokselected[t]=spysokselected[j];
                spysokselected[j]=y;
                if (cp==j){cp=i;}
                else
                {
                  if (cp==t){cp=j;}
                }
              }
            }
          }
          /* xdisp=1;
           xdispnapriamok=-3;
           GBS_StartTimerProc(&Scroll,50,Scrolling);*/
           REDRAW();
      };break;
    case '0':Message(LG_PLAYLIST_HELP);break;
      case RIGHT_SOFT:
        {
          ZapovnytyTaVidsortuvatyKatalog(curentfolder);
          for (int i=0;i<256;i++){katalogselected[i]=0;}
          WhatToView=3;
          //rsoft=0;
          xrshift=0;
          yrshift=0;
          REDRAW();  
        }break;
      case LEFT_SOFT:
      {
        if(NumberOfTracks==0)
        {
          Message("Нет композиций для удаления!");
          break;
        }
        if (NumberOfTracks!=1)
        {
        for (int i=selected;i<NumberOfTracks;i++)
        {
          sprintf(spysok[0][i],spysok[0][i+1]);
          sprintf(spysok[1][i],spysok[1][i+1]);
          timelength[i]=timelength[i+1];
          notplayed[i]=notplayed[i+1];
        }
        timelength[NumberOfTracks]=-1;
        sprintf(spysok[1][NumberOfTracks],pp);
        sprintf(spysok[0][NumberOfTracks],pp);
        if (cp==selected)
        {
        cp--;
        char s[256];
        sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
        playing=1;
        JaPerekliuchyvPisniu=1;
        Play(s);
        }
        if (cp>selected){cp--;}
        if (selected!=0){selected--;}
        NumberOfTracks--;
        timelist=0;
        findalllisttime();
        //lsoft=0;
        xlshift=0;
        ylshift=0;
        REDRAW();
        }
        else
        {
          Message(LG_CANT_REMOVE_LAST_FILE);
        }
      }break;
    case ENTER_BUTTON:
      {
        tm=0;
        char s[256];
        cp=selected;
        sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
        playing=1;
        JaPerekliuchyvPisniu=1;
        Play(s);
        WhatToView=0;
        REDRAW();
      }break;
    case '#':
      {
        char s[256];
        cp=selected;
        sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
        playing=1;
        JaPerekliuchyvPisniu=1;
        Play(s);
      }break;
    }
  }
      }
  break;
  case 3:///////////////////////////Файлменеджер
    {
      if (msg->gbsmsg->msg==KEY_DOWN)
      {
        //longpress=0;
        switch(msg->gbsmsg->submess)
         {  
         case RIGHT_SOFT:
           {
             xrshift=2;
             yrshift=2; 
             REDRAW();
           }break;
         case LEFT_SOFT:
           {
             xlshift=2;
             ylshift=2; 
             REDRAW();
           }break; 
         }
      }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON:
      {
        longpress=1;
#ifndef VOVKA
        DisableScroll();
#endif
        if(longpress==1)
        {
        katalogcurent--;
        if(katalogcurent<0){katalogcurent=kataloglength-1;}
        scroll_disp=0;
        /*xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,ScrollingInFile);*/
        REDRAW();
        }
      }break;
      
      case DOWN_BUTTON:
      {
        longpress=1;
#ifndef VOVKA
        DisableScroll();
#endif
        if(longpress==1)
        {
        katalogcurent++;
        if(katalogcurent>kataloglength-1){katalogcurent=0;}
        scroll_disp=0;
        /*xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,ScrollingInFile);*/
        REDRAW();
        }
      }break;
    }
  }    
  if ((msg->gbsmsg->msg==KEY_UP)&&(IsUnlocked()))
  {
    longpress=0;
      switch(msg->gbsmsg->submess)
    {
#ifdef NEWSGOLD
    case LEFT_BUTTON:
#endif
    case RED_BUTTON:
      {
        SUBPROC((void *)findlisttime);
        WhatToView=1;
        REDRAW();
      }break;
      
      case UP_BUTTON:
      {
        if(VIEW==1)
        {
        katalogcurent--;
        if(katalogcurent<0){katalogcurent=kataloglength-1;}
        scroll_disp=0;
        /*xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,ScrollingInFile);*/
        }
        else
        {
          disk--;
          if(disk<0)disk=1;
        }
        REDRAW();
      }break;
      
      case DOWN_BUTTON:
      {
        if(VIEW==1)
        {
        katalogcurent++;
        if(katalogcurent>kataloglength-1){katalogcurent=0;}
        scroll_disp=0;
        /*xdisp=1;
        xdispnapriamok=-3;
        GBS_StartTimerProc(&Scroll,50,ScrollingInFile);*/
        }
        else
        {
          disk++;
          if(disk>1)disk=0;
        }
        REDRAW();
      }break;
      
    //case '9':ShowMSG(1,(int)curentfolder);break;
      
    case LEFT_SOFT:
      {
        xlshift=0;
        ylshift=0;
        if ((katalogcurent!=0)&&(IsFile(katalog[katalogcurent])))
        {
          katalogselected[katalogcurent]=1-katalogselected[katalogcurent];
          katalogcurent++;
          if(katalogcurent>kataloglength-1){katalogcurent=0;}
          /*xdisp=1;
          xdispnapriamok=-3;
          GBS_StartTimerProc(&Scroll,50,ScrollingInFile);*/

          //REDRAW();
        }
        REDRAW();
      }break;
      
    case RIGHT_SOFT:
      {
        for (int i=1;i<kataloglength;i++)
        {
          if (katalogselected[i]==1)
          {
            sprintf(spysok[0][NumberOfTracks],"%s\\",curentfolder);
            sprintf(spysok[1][NumberOfTracks],katalog[i]);
            NumberOfTracks++;
          }
        }
        //SUBPROC((void *)findlisttime);
        xrshift=0;
        yrshift=0;
        REDRAW();
        for (int i=0;i<256;i++){katalogselected[i]=0;}
        Message(LG_ADDED);
      }break;
    
    case GREEN_BUTTON:
      {
        for (int i=1;i<kataloglength;i++)
        {
          if (IsFile(katalog[i]))
          {
            katalogselected[i]=1-katalogselected[i];
          }
        }
        REDRAW();
      }break;
      
    case ENTER_BUTTON:
      {
        if (katalogcurent!=0||VIEW==0)
        {
          char t[255];
          if(VIEW==0)
          {
            if(disk==1)
              sprintf(t,"0:");
            if(disk==0)
              sprintf(t,"4:");
            VIEW=1;
          }
          else
          {
          sprintf(t,"%s\\%s",curentfolder,katalog[katalogcurent]);
          }
          if(!IsFile(t))
          {
            sprintf(curentfolder,t);
            for (int i=0;i<256;i++){katalogselected[i]=0;}
            ZapovnytyTaVidsortuvatyKatalog(curentfolder);
            //GBS_StartTimerProc(&Scroll,50,ScrollingInFile);   
          }
          else
          {
            katalogselected[katalogcurent]=1-katalogselected[katalogcurent];
          }
          
        }
        else
        {
          int i;
          for (i=strlen(curentfolder);(curentfolder[i]!='\\')&&(i!=0);i--);
          curentfolder[i]=0;
          if(curentfolder[0]==0)
          {
            VIEW=0;
          }
          else
          {
          ZapovnytyTaVidsortuvatyKatalog(curentfolder);
          for (int i=0;i<256;i++){katalogselected[i]=0;}
          //GBS_StartTimerProc(&Scroll,50,ScrollingInFile);
          VIEW=1;
          }
        }
        REDRAW();
      }break;
      
    }
  }
    }
  break;
  }
    }
    else
    {
      if (msg->gbsmsg->msg==KEY_UP)
      {
        switch(msg->gbsmsg->submess)
        {
#ifdef NEWSGOLD
        case LEFT_BUTTON:
#endif
        //case RED_BUTTON:

          case ENTER_BUTTON:case RIGHT_SOFT:
          {
            sprintf(texttoview,pp);
            toview=0;
            REDRAW();
          }break;
        }
      }
    }
  return(0);
}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method,
  (void *)method,
  0
};
void stoped(){
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name; //твое имя
  gipc.data=(void*)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,PLAYER_CLOSE,&gipc);
}
void started(){
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name; //твое имя
  gipc.data=(void*)MAINCSM_ID;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,PLAYER_RUN,&gipc);
}
int medialibrary=0;
void maincsm_oncreate(CSM_RAM *data)
{
#ifdef ELKA
  if(allowbuf)SetupBuffers((buff_size+(buff_nof*256)));
#endif
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
  wss.ws1=AllocWS(256);
  wss.ws2=AllocWS(256);
  ows.ws1=AllocWS(256);
  ows.ws2=AllocWS(256);
  started();
  if(medialibrary==1) {CreateBaseOfMediafiles();medialibrary=0;}
}

void PersheShchoStuknuloVGolovu()
{
  gipc.name_from="IVOPLAY";
  gipc.name_to="control_panel|remove_point|";
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,2,&gipc);
}

TDate date; TTime time;
void WriteLog (char *string)
{
  char *t=malloc(512);
  sprintf(t,"%slog.cfg",playerfolder);
  int logfile=fopen(t,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,0);
  mfree(t);
  char *data=malloc(4096);
  GetDateTime(&date,&time);
  sprintf(data,">%d:%02d:%02d/%02d-%02d-%04d< >kernel<   %s\n",time.hour,time.min,time.sec,date.day, date.month,date.year,string);
  lseek(logfile, 0x0, S_END, 0, 0);
  fwrite(logfile,data,strlen(data),0);
  mfree(data);
  fclose(logfile,0);
}

extern void kill_data(void *p, void (*func_p)(void *));
void FreeData();
void ElfKiller(void)
{ 
  WriteLastPlaylist();
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void KillTimers()
{
  
  if(IsTimerProc(&MessageTimer))  GBS_DelTimer(&MessageTimer);
  if(IsTimerProc(&PlayerMenu))    GBS_DelTimer(&PlayerMenu);
  if(IsTimerProc(&PlayNextTimer)) GBS_DelTimer(&PlayNextTimer);
  if(IsTimerProc(&mytmr))         GBS_DelTimer(&mytmr);
  if(IsTimerProc(&tmr_scroll))    GBS_DelTimer(&tmr_scroll);
  if(IsTimerProc(&play_exit))     GBS_DelTimer(&play_exit);
  if(IsTimerProc(&pause_exit))    GBS_DelTimer(&pause_exit);
  if(IsTimerProc(&stop_exit))     GBS_DelTimer(&stop_exit);
  if(IsTimerProc(&tags))          GBS_DelTimer(&tags);
}
void MfreeObl()
{
  if(picflag==1)
  {
    mfree(img_o->bitmap);
    mfree(img_o);
  }
}

void FWS()
{
  FreeWS(wss.ws1);
  FreeWS(wss.ws2); 
  FreeWS(ows.ws1);
  FreeWS(ows.ws2);
}
void FreeData()
{  
  MfreeObl();
  delImghdr();
  FWS();
#ifdef ELKA
  if(allowbuf)if (oldAudValue)SetupBuffers(oldAudValue);
#endif
  stoped();
  PersheShchoStuknuloVGolovu();
  RemoveKeybMsgHook((void *)my_keyhook);
  if (playlistmode==1){SaveOnlyPlaylistParams(LastPlaylist);/*WriteLog("SaveOnlyPlaylistParams Succesfull");*/}
  pracuje=0;
}
void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void*)KillTimers);
  if (playing!=0)
{
#ifndef OBS
  if(PLAY_ID!=-1)PlayMelody_StopPlayback(PLAY_ID);
#else
  Obs_Stop (gObj);
#endif
}
#ifdef OBS
  KillObj();
#endif 
  SaveParams();
  FreeData();
  WriteLastPlaylist();
  SUBPROC((void *)ElfKiller);
}


//////////////////////////
void CheckDoubleRun(void)
{
  int csm_id;
  if ((csm_id=(int)(gipc.data))!=-1)
  {
    gipc.name_to=ipc_my_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)csm_id;
    TTime ktime;
    TDate date;
    GetDateTime(&date,&ktime);
    GBS_SendMessage(MMI_CEPID,MSG_IPC,ktime.min*60+ktime.sec,&gipc);  
    /*(LockSched();
    CloseCSM(MAINCSM_ID);
    UnlockSched();*/
  }
  else
  {
    ShowMSG(1,(int)"dsfgg");
  }
}
/////////////////////////////////


#ifdef OBS
int obFrameUpd(HObj hobj,int error){
  //ShowMSG(1,(int)"Upd");
  return 0;
}

int obError(HObj hobj,int error){
  //ShowMSG(1,(int)"Destroj");
  Obs_DestroyObject(hobj);
  return 0;
};

int obPrep(HObj hobj,int error){
  //ShowMSG(1,(int)"Prepared");
  //CanRewind=0;
  Obs_Start(hobj);  
  return 0;
  
};
int obStop(HObj hobj,int pl, int error)
{
  //ShowMSG(1,(int)"Stopcon");
  ExitTime();
  return 0;
}
int obResumeInd(HObj hobj,int pl, int error)
{
  //ShowMSG(1,(int)"PauseInd");
  return 0;
}
int obDestroy(HObj hobj,int err)
{
  //ShowMSG(1,(int)"Destr");
  return 0;
}

int obInfo(HObj hobj,int error){
  //ShowMSG(1,(int)"Info");
  return 0;
};
void gtb()
{
  GetBit(now_play);
}

void ZerMemStruct()
{
  zeromem(flprp.mpg_ver,12);
  zeromem(flprp.layer,12);
  zeromem(flprp.bitrate,12);
  zeromem(flprp.chanl,16);
  zeromem(flprp.freq,16);
}

int obResumeCon(HObj hobj,int error)  //начало воспроизведения
{
  //ShowMSG(1,(int)"Resumed");
  EXT_REDRAW();   //начало отсчёта только после начала воспроизведения
  playing=1;
  if(play_flag==1)
  {
    GetPlayObjDuration((void*)hobj, &ln);
    ln/=1000;
    ln=ln+1;
    if(WhatToView==0) timelength[cp]=ln;
    if(format==3) {ZerMemStruct(); SUBPROC((void*)gtb);}
    if(onfokus!=1||IsGuiOnTop(MAINGUI_ID)!=1) {show_tags=1;}
    else {show_tags=0;}
    GBS_StartTimerProc(&tags,1000,tagstm);
    play_flag=0;
  }
  CanRewind=1;
  ExitTime();
  return 0;
};

int obParam (HObj hobj,int pl, int error){
  //ShowMSG(1,(int)"Param");
  if(rew_flag==1) {Obs_Resume(hobj); rew_flag=0;}
  return 0;
};


int obSetPause(HObj hobj,int err)
{
  //ShowMSG(1,(int)"Paused1");
  StopTMR(0);
  playing=2;
  return 0;
}

int obSetStop(HObj hobj,int err)
{
  //ShowMSG(1,(int)"StopInd");
  return 0;
}

int obNext(HObj hobj,int err)
{
PlayNext();
//REDRAW();
return 0;
}

int obPause (HObj hobj,int pl, int error){
  //ShowMSG(1,(int)"Paused2");
  ExitTime();
  return 0;
}

int obStatusChanged(HObj hobj,int error)
{
  //ShowMSG(1,(int)"StatusChanged");
  return 0;
}

int obStatusUpdated(HObj hobj,int error)
{
  //ShowMSG(1,(int)"StatusUpdated");
  return 0;
}

/*int obMMStop(HObj hobj,int error)
{
  //ShowMSG(1,(int)"MMStop");
  return 0;
}*/
OBSevent ObsEventsHandlers[]={
  OBS_EV_StatusChanged,(void*)obStatusChanged,
  OBS_EV_StatusUpdated,(void*)obStatusUpdated,
  OBS_EV_Error,(void*)obError,
  OBS_EV_GetInfoCon,(void*)obInfo,
  OBS_EV_PauseCon,(void*)obPause,
  OBS_EV_ParamChanged,(void*)obParam,
  OBS_EV_ResumeCon,(void*)obResumeCon,
  OBS_EV_PauseInd,(void*)obSetPause,
  OBS_EV_StopInd,(void*)obSetStop,
  OBS_EV_LoopUpdate,(void*)obNext,
  OBS_EV_PrepareCon,(void*)obPrep,
  OBS_EV_ConvDestroyed,(void*)obDestroy,
  OBS_EV_ResumeInd,(void*)obResumeInd,
  OBS_EV_StopCon,(void*)obStop,
  /*OBS_MM_Stop,(void*)obMMStop,*/
  OBS_EV_EndList,NULL
};
#endif

void SendStatus()
{
   eipc.name_to=ipc_extraplay;
   eipc.name_from=ipc_my_name; //твое имя
   if(playing) GBS_SendMessage(MMI_CEPID,MSG_IPC,21,&eipc);
   else GBS_SendMessage(MMI_CEPID,MSG_IPC,20,&eipc);
} 

/*void TmrStatus()
{
  SendStatus();
  GBS_StartTimerProc(&statmr,262*3,TmrStatus);
}  */

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{  
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (Quit_Required)
  {
    csm->csm.state=-3;
  }
#ifdef ELKA
  if (msg->msg==0x15680){
    if ((   ((char *)(((int *)msg->data1)[6]))[0x11]  )==0)
    {
      if (allowbuf)SetupBuffers((buff_size+(buff_nof*256)));
    }

    if ((   ((char *)(((int *)msg->data1)[6]))[0x11]  )==1){
      if (oldAudValue)SetupBuffers(oldAudValue);}}
#endif
/////////////////////
  if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
        /*if ((ipc->name_to[0]=='I')&&(ipc->name_to[1]=='v'))
        {
          ShowMSG(1,(int)ipc->name_to);*/
          /*if (!strcmp("control_panel|punkt1",ipc->name_from))
          {
            Play_PauseResume();
            //ShowMSG(1,(int)ipc->name_to);
          }
        }*/
        if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
        {     
          switch (msg->submess)
          {
          case CMD_NEXT:{
                PlayNext();
                SendStatus();
                break;}
          case CMD_PREV: {    
                PlayPrevious();
                SendStatus();
                break;}
          case CMD_PLAY_PAUSE:{
                Play_PauseResume();
                SendStatus();
                break;}
          case CMD_VOLUP:{
                VolumeUp();
                break;}
          case CMD_VOLDOWN:  {   
                VolumeDown();
                break;}
          case CMD_MUTE:{
                VolumeMute();
                break;}
          case CMD_STOP:{
                WhatToDo(1);
                SendStatus();
                break;     }
          case CMD_KILL:{
                Quit_Required=1;
                break;      }  
          }
                /*if(msg->submess==1)
          {
            if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
            else ipc->data=(void *)MAINCSM_ID;
          }*/
          if (strcmp_nocase(ipc->name_from,"XTask")==0)
          {
              //WhatToDo(msg->submess);
              switch(msg->submess)
              {
              /*case PLAYER_IDLE:
                {
                  gipc.name_to=ipc_xtask_name;
                  gipc.name_from=ipc_my_name;
                  gipc.data=(void *)MAINCSM_ID;
                  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
                  break;
                }
              case PLAYER_SHOW:
                {
                  gipc.name_to=ipc_xtask_name;
                  gipc.name_from=ipc_my_name;
                  gipc.data=(void *)MAINCSM_ID;
                  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
                  break;
                }*/
              case PLAYER_PAUSE:
                {
                Play_PauseResume();
                break;
                }
              }
          }
          if (strcmp_nocase(ipc->name_from,"control_panel")==0)
          {
              gipc.name_to=ipc_xtask_name;
              gipc.name_from=ipc_my_name;
              gipc.data=(void *)MAINCSM_ID;
              GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
          }
	if ((msg->submess)!=-identyfikator)
	{
	  if (((msg->submess)!=identyfikator)&&((msg->submess)>0))
          {
            GBS_SendMessage(MMI_CEPID,MSG_IPC,-identyfikator,&gipc);  
          }
          else
          {
            if ((msg->submess)<0)
            {
              CloseCSM(MAINCSM_ID);
                int csm_id;
                if (((csm_id=(int)(gipc.data))!=-1)&&((playlistmode==3)||(playlistmode==4)))
                {
                  //ShowMSG(1,(int)"123456");
                  char *s="ffff";
                  sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
                  char *r=s;
                  gipc.name_to=r;
                  gipc.name_from="pLay";
                  gipc.data=(void *)csm_id;
                  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc); 
                }
            }
          }
        }
        else
        {
          if((ipc->name_from[0]=='p')&&(ipc->name_from[1]=='L')&&(ipc->name_from[2]=='a')&&(ipc->name_from[3]=='y'))
          {
            //ShowMSG(1,(int)"123456");
            char u[256];
            for (int i=0;i<strlen(ipc->name_to);i++)
            {
              sprintf(u,"%s%c",u,ipc->name_to[i]);
            }
            DIR_ENTRY de;
            unsigned int err;
            if(FindFirstFile(&de,u,&err))
            {
              cp=NumberOfTracks;
              NumberOfTracks++;
              sprintf(playlistname,"Mixed");
              //playlistname=LG_MIXED;
      const char *o=strrchr(u,'\\')+1;
      sprintf(spysok[1][cp],o);
      strncpy(spysok[0][cp],u,o-u);
      spysok[0][cp][o-u]='\0';
      JaPerekliuchyvPisniu=1;
            Play(u);
  gipc.name_to=ipc_xtask_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)MAINCSM_ID;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
      ShowMSG(1,(int)u);
            }
            else
            {
              sprintf(playlistname,"Not found!");
              sprintf(spysok[1][0],"File not found!");
            }
            FindClose(&de,&err);
          }
        }
        }
      }
    }

/////////////////////
if(over_ena)
if(onfokus==0)
  if(show_tags)
  {   
      sprintf(name,"%s\r%s\r%s",ctrack,cartist,calbum);
      utf8_2ws(ows.ws1,name,320);
      if (name[0]!=' ')
      {
        wsprintf(ows.ws2,"%t\r%t\r%t",ctrack,cartist,calbum);
      }
      else
      {
        wsprintf(ows.ws2,pp);
      }
      if (Get_WS_width(ows.ws1,over_font)<Get_WS_width(ows.ws2,over_font))
      {
        DrawString(ows.ws2,over.x,over.y,over.x2,over.y2,over_font,over_align,over_col,bg_over_color);
      }
      else
      {
        DrawString(ows.ws1,over.x,over.y,over.x2,over.y2,over_font,over_align,over_col,bg_over_color);
      }
  }
#ifndef OBS  
  if (msg->msg==MSG_PLAYFILE_REPORT)
    {
      switch(msg->submess&0xFFFF)
      {
      case M_SAE_PLAYBACK_STARTED: 
        {
          CanPlayNext=1;
          tm=0;
          EXT_REDRAW();
#ifdef NEWSGOLD
        pha=GetPlayObjById(PLAY_ID);
        if(PLAY_ID!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], CurentVolume, 1);
        GetPlayObjDuration((( int**)pha)[0x3d0/4], &ln);
        ln/=1000;
#else
        if(PLAY_ID!=-1)PlayMelody_ChangeVolume(PLAY_ID,CurentVolume);
#endif         
        }break;
#ifdef NEWSGOLD
      case M_SAE_PLAYBACK_ERROR:
#else
      case M_SAE_PLAYBACK_DONE:
#endif
        {
            tm=0;
            PLAY_ID=0;
            if (playing==1)
              {
                PlayNext();
              }
        }
        break;
        
      case M_SAE_AUDIO_EVENT_RESUMED: if (playing!=0) 
      {
        if (JaPerekliuchyvPisniu==0)
        {
          playing=0;
        }
        else 
        {
          JaPerekliuchyvPisniu=0;
        }
      }
        break;
      }
    }
#else
  if (msg->msg==MSG_Report)
  {
   // char *s=(char*)malloc(100);
   // sprintf(s,"myrep %08X %08X %08X\r\n",msg->submess,msg->data0,msg->data1);
   // SUBPROC((void *)Log,0,s);
//    void *msg_internal;
//    GBS_MsgConv ((int)&msg_internal,msg);
//    Obs_TranslateMessage((int)&msg_internal,ObsEventsHandlers);
//    GBS_ConvKill((int)&msg_internal);
    Obs_TranslateMessageGBS(msg,ObsEventsHandlers);
    //очень важно чтоб далее шел выход из функции, по краине мере не было обращений к msg так как оно очищается

   // return 0;
}
#endif
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      Message(LG_CONFIG_UPDATED);
      InitConfig();
      ExitTime();
    }
  }

 if (EnableIconOnIdle)
 {
    CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
    if (IsGuiOnTop((((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
	void *canvasdata=BuildCanvas();
        DrawCanvas(canvasdata,IDLEICON_X,IDLEICON_Y,IDLEICON_X+GetImgWidth((int)name)-1,IDLEICON_Y+GetImgHeight((int)name)-1,1);
	if (playing!=1) 
        {
          DrwImg(stop,IDLEICON_X,IDLEICON_Y,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
        }
        else 
        {
          DrwImg(play,IDLEICON_X,IDLEICON_Y,GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
        }
      DrawCanvas(canvasdata,tagS.x,tagS.y,tagS.x2,tagS.y2,1);
      sprintf(name,"%s\r%s\r%s",ctrack,cartist,calbum);
      utf8_2ws(wss.ws1,name,320);
      
 
      if (name[0]!=' ')
      {
        wsprintf(wss.ws2,"%t\r%t\r%t",ctrack,cartist,calbum);
      }
      else
      {
        wsprintf(wss.ws2,pp);
      }
      if (Get_WS_width(wss.ws1,7)<Get_WS_width(wss.ws2,7))
      {
        DrawString(wss.ws2,tagS.x,tagS.y,tagS.x2,tagS.y2,FONT_SMALL,TEXT_ALIGNMIDDLE,TRACK_COL,GetPaletteAdrByColorIndex(23));
      }
      else
      {
        DrawString(wss.ws1,tagS.x,tagS.y,tagS.x2,tagS.y2,FONT_SMALL,TEXT_ALIGNMIDDLE,TRACK_COL,GetPaletteAdrByColorIndex(23));
      }
      }
    }
 }
  return(1);  
}

static void addIconBar(short* num)
{
  //Obs_Sound_GetVolume(gObj,&getvol);
  //getvol=CurentVolume;
  if(ena_vol)
  {
    if(getvol==0)AddIconToIconBar(vol_icon,num);
    if(getvol==1)AddIconToIconBar(vol_icon+1,num);
    if(getvol==2)AddIconToIconBar(vol_icon+2,num);
    if(getvol==3)AddIconToIconBar(vol_icon+3,num);
    if(getvol==4)AddIconToIconBar(vol_icon+4,num);
    if(getvol==5)AddIconToIconBar(vol_icon+5,num);
    if(getvol==6)AddIconToIconBar(vol_icon+6,num);
    if(getvol==7)AddIconToIconBar(vol_icon+7,num);
    if(getvol==8)AddIconToIconBar(vol_icon+8,num);
    if(getvol==9)AddIconToIconBar(vol_icon+9,num);
    if(getvol==10)AddIconToIconBar(vol_icon+10,num);
    if(getvol==11)AddIconToIconBar(vol_icon+11,num);
    if(getvol==12)AddIconToIconBar(vol_icon+12,num);
    if(getvol==13)AddIconToIconBar(vol_icon+13,num);
    if(getvol==14)AddIconToIconBar(vol_icon+14,num);
    if(getvol==15)AddIconToIconBar(vol_icon+15,num);
  }
}

typedef struct
{
  char check_name[8];
  int addr;
}ICONBAR_H;

struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
  ICONBAR_H iconbar_handler;
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
  },
  {
    "IconBar"
  }
};

void SetIconBarHandler()
{
  MAINCSM.iconbar_handler.addr=(int)addIconBar;
}

////////////////////////
int press=0;//0-отпущена,1-нажата коротко,2-зажата
int double_press=0;
GBSTMR doubl;
void func()
{
  double_press=0;
  Play_PauseResume();
  GBS_DelTimer(&doubl);
}
int my_keyhook(int submsg, int msg)
{
  if ((submsg!=VOL_UP_BUTTON && submsg!=VOL_DOWN_BUTTON &&  submsg!=0x27)||(EnableHook==2)||((!IsUnlocked())&&(EnableHook==1))) return(0);//Хук на кнопку гарнитуры и боковые кнопки
  switch(msg)
  {
    case(KEY_UP):
      {
        switch(submsg)
            {
           case VOL_UP_BUTTON: 
             if (press==1)
             {
               VolumeUp();
               REDRAW();
             }
             else 
             {
               if(IsGuiOnTop(TagMenu_ID)!=1)
               if (press<5)
               {
                 PlayNext();
               }
             };break;//Верхня
           case VOL_DOWN_BUTTON: 
             if (press==1)
             {
               VolumeDown();
               REDRAW();
             }
             else 
             {
               if(IsGuiOnTop(TagMenu_ID)!=1)
               if (press<5)
               {
                 PlayPrevious();
               }
             }
             break;//Нижня
            case 0x27:
             /* if (press==1&&double_press==1&&playing==2)
              {
                Play_PauseResume();
                double_press=0;
              }else{*/
              if (press==1&&double_press==1&&playing)
              {
                GBS_StartTimerProc(&doubl,100,func);
              }
              else 
              {
                if(IsGuiOnTop(TagMenu_ID)!=1)
                {
                  if (press>4)
                  {
                    PlayNext();
                    double_press=0;
                  }
                  //if(press<=4&&press==1) double_press=0;
                }
              }    // }         
              if(press==1&&double_press==2)
              {
                if(IsTimerProc(&doubl)) GBS_DelTimer(&doubl);
                PlayPrevious();
                double_press=0;
              }
            break;//Гарнітура
            }
      }
      break;    
  case(KEY_DOWN):
    {
      double_press++;
      press=1;      
    }break;
  case(LONG_PRESS):
    {
      press++;
      if (press==8)
      {
        if (submsg==VOL_UP_BUTTON)
        {
          gipc.name_to=ipc_xtask_name;
          gipc.name_from=ipc_my_name;
          gipc.data=(void *)MAINCSM_ID;
          GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
        }
        else
        {
          if (submsg==VOL_DOWN_BUTTON)
          {
            /*char dummy[sizeof(MAIN_CSM)];
            UpdateCSMname();
            MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);*/
            if (IsUnlocked()){ShowPlayerMenu();}
          }
        }
      }
      
    }break;
  }
  return(2);
}

void UpdateCSMname(void)
{
      /*sprintf(name,"%s - %s - %s",ctrack,cartist,calbum);
      utf8_2ws(wss.ws1,name,320);
      if (name[0]!=' ')
      {
        wsprintf(wss.ws2,"%t - %t - %t",ctrack,cartist,calbum);
      }
      else
      {
        wsprintf(wss.ws2,pp);
      }
      if (Get_WS_width(wss.ws1,7)<Get_WS_width(wss.ws2,7))
      {
        DrawString(wss.ws2,2,2,130,88,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      }
      else
      {
        DrawString(wss.ws1,2,2,130,88,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));
      }
      DrawString(wss.ws1,2,2,130,88,FONT_MEDIUM,TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(12),GetPaletteAdrByColorIndex(1));*/

  utf8_2ws((WSHDR *)(&MAINCSM.maincsm_name),NameOfCurentTrack,320);
  if (Get_WS_width((WSHDR *)(&MAINCSM.maincsm_name),7)==0)
  {
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"%t - %t - %t",ctrack,cartist,calbum);
  }
}

void skins()
{
  DIR_ENTRY de;
  NumberOfSkins=0;
  unsigned int err;
  char path[128];
  sprintf(path,"%sskins\\",playerfolder);
  strcpy(name,path);
  strcat(name,zir);
  if (FindFirstFile(&de,name,&err))
  {
    
    do
    {
      if((de.file_attr&FA_DIRECTORY))
      {
        sprintf(ArrayOfSkins[NumberOfSkins],de.file_name);
        NumberOfSkins++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}


int main(char *exename, char *fname)
{
  
  int iplpls=0;
  InitConfig();
  ExitTime();
  SetIconBarHandler();
  LockSched();
#ifdef ELKA  
  if (allowbuf&&!audcfg){
    if (autosearch())
      ShowMSG(1,(int)"Entry point for Buffer change found.");
    else{
      ShowMSG(1,(int)"Entry point not found :(");    
      UnlockSched();        
      return -1;
    }
  }
#endif
  UnlockSched();
  if (!pracuje)
  {
    GBS_StartTimerProc(&PlayerMenu,250,JaLiuBLiuPYVo);
    pracuje=1;
    LastPlaylist[0]='\0';
    sprintf(LastPlaylist,fname);
  //InitConfig();
    TTime ktime;
    TDate date;
    GetDateTime(&date,&ktime);
    identyfikator=ktime.min*60+ktime.sec;
  CheckDoubleRun();
  SendStatus();
  LoadParams();
  skins();
  readskinparamsfromfile();
  crtIMGHDR();
  REDRAW();
#ifdef NEWSGOLD
  AddKeybMsgHook((void *)my_keyhook);
#else
  AddKeybMsgHook_end((void *)my_keyhook);
#endif
mitka:
  if (LastPlaylist[0]=='1'&&LastPlaylist[1]=='.'&&LastPlaylist[2]=='m'&&LastPlaylist[3]=='e'&&LastPlaylist[4]=='d')
  {
    medialibrary=1;
  }
  //else{
  if ((LastPlaylist[0]=='0')||(LastPlaylist[0]=='4'))
  {
      char extension[3];
      sprintf(extension,"%c%c%c",LastPlaylist[strlen(LastPlaylist)-3],LastPlaylist[strlen(LastPlaylist)-2],LastPlaylist[strlen(LastPlaylist)-1]);
      if (strcmp_nocase(extension,"ipl")==0)
      {
      iplpls=1;  
      playlistmode=1;
      LoadPlaylist(LastPlaylist);
      const char *p=strrchr(LastPlaylist,'\\')+1;
      sprintf(playlistname,p);
      char s[256];
      sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
      if(medialibrary==0) 
      { 
        playing=1;
        Play(s);
      }
      }
      else 
    {
        if (((extension[0]=='M')||(extension[0]=='m'))&&((extension[2]=='u')||(extension[2]=='U')))
      {
          playlistmode=2;
          LoadM3uPlaylist(LastPlaylist);
          const char *p=strrchr(LastPlaylist,'\\')+1;
          sprintf(playlistname,p);
          char s[256];
          sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
          if(medialibrary==0)
          {
            playing=1;
            Play(s);
          }
      } else
      {
        if (strcmp_nocase(extension,"imy")==0)
          {
            playlistmode=3;
            char s[256];
            sprintf(s,LastPlaylist);
            NumberOfTracks=1;
            if(medialibrary==0) playing=1;
            s[strlen(s)-4]=0;
            s[0]='4';
            DIR_ENTRY de;
            unsigned int err;
            if(FindFirstFile(&de,s,&err))
            {
              CreatePlaylist(de.folder_name);
              VporiadkuvatySpysok();
              cp=0;
              while (strcmp(spysok[1][cp],de.file_name)!=0)
              {
                cp++;
              }
              const char *p=strrchr(de.folder_name,'\\')+1;
                          sprintf(playlistname,p);
            if(medialibrary==0) Play(s);
            }
            else
            {
              sprintf(playlistname,"Not found!    ");
              sprintf(spysok[1][0],"File not found!");
            }
            FindClose(&de,&err);
          }
        else
        {
          if (strcmp_nocase(extension,"new")==0)
          {
            Message(LG_CREATE_PLAYLIST_PLEASE);
            ZapovnytyTaVidsortuvatyKatalog(curentfolder);
            playlistmode=0;
            WhatToView=3;
            for (int i=0;i<256;i++){katalogselected[i]=0;}
          }else
        {
          if ((strcmp_nocase(extension,format_1)==0)||(strcmp_nocase(extension,format_2)==0)||(strcmp_nocase(extension,format_3)==0)||(strcmp_nocase(extension,format_4)==0))
          {
            playlistmode=4;
            NumberOfTracks=1;
            if(medialibrary==0) playing=1;
            DIR_ENTRY de;
            unsigned int err;
            if(FindFirstFile(&de,LastPlaylist,&err))
            {
              CreatePlaylist(de.folder_name);
              VporiadkuvatySpysok();
              cp=0;
              while (strcmp(spysok[1][cp],de.file_name)!=0)
              {
                cp++;
              }
              const char *p=strrchr(de.folder_name,'\\')+1;
                          sprintf(playlistname,p);
            if(medialibrary==0) Play(LastPlaylist);
            }
            else
            {
              sprintf(playlistname,"Not found!    ");
              sprintf(spysok[1][0],"File not found!");
            }
            FindClose(&de,&err);
          }
        }
        }
      }
    }
  }
  else
  {
          ReadLastPlaylist();
          if ((LastPlaylist[0]=='0')||(LastPlaylist[0]=='4')){goto mitka;}
          else
          {
            Message(LG_CREATE_PLAYLIST_PLEASE);
            ZapovnytyTaVidsortuvatyKatalog(curentfolder);
            playlistmode=0;
            WhatToView=3;
            for (int i=0;i<256;i++){katalogselected[i]=0;}
          }
  }
  //}
  for (int i=0;i<255;i++){notplayed[i]=0;if(!iplpls) timelength[i]=-1;}
  if (playlistname[0]==0x1F){playlistname[0]=' ';}
  if (playlistmode!=3) {playlistname[strlen(playlistname)-4]=0;}
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  //SUBPROC((void *)findlisttime);
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  started();
  }
  else
  {
    for (int i=0;i<255;i++)
    {
      sprintf(spysok[0][i],pp);
      sprintf(spysok[1][i],pp);
    }
    NumberOfTracks=0;
    sprintf(LastPlaylist,fname);
      char extension[3];
      sprintf(extension,"%c%c%c",LastPlaylist[strlen(LastPlaylist)-3],LastPlaylist[strlen(LastPlaylist)-2],LastPlaylist[strlen(LastPlaylist)-1]);
      if (strcmp_nocase(extension,"ipl")==0)
      {
      iplpls=1;  
      playlistmode=1;
      LoadPlaylist(LastPlaylist);
      sprintf(playlistname,"media");
      //for (int i=strlen(LastPlaylist)-1;LastPlaylist[i]!='\\';i--){sprintf(playlistname,"%c%s",LastPlaylist[i],playlistname);}
      char s[256];
      sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
      playing=1;
      JaPerekliuchyvPisniu=1;
      Play(s);
      }
      else 
        if (((extension[0]=='M')||(extension[0]=='m'))&&((extension[2]=='u')||(extension[2]=='U')))
      {
          playlistmode=2;
          LoadM3uPlaylist(LastPlaylist);
          const char *p=strrchr(LastPlaylist,'\\')+1;
          sprintf(playlistname,p);
          char s[256];
          sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
          playing=1;
          JaPerekliuchyvPisniu=1;
          Play(s);
      }
  for (int i=0;i<255;i++){notplayed[i]=0;if(!iplpls) timelength[i]=-1;}
  if (playlistname[0]==0x1F){playlistname[0]=' ';}
  UpdateCSMname();
  started();
  //SUBPROC((void *)findlisttime);
  }
  return 0;
}
