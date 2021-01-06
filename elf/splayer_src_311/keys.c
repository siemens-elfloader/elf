#include "../inc/swilib.h"
#include "main.h"
#include "mainmenu.h"
#include "playlist.h"
#include "FM.h"

/*
  Будующий конфиг клавиш. Blind007
  Респект авторам MC :)
  То что в комментариях, не удаляйте, может пригодиться!
 */

extern const unsigned int LOAD_KEYS; // Грузить ли из файла
//extern const char KEYCFG_PATH[];      // Откуда грузятся настройки
extern const char SETS_PATH[];      // Откуда грузятся настройки

typedef void (*KEY_PROC) ();

/*
typedef struct {
  void (*ondown) ();
  void (*onup) ();
} KEY_PROC;
*/

typedef struct {
  int key;
  char* name;
} KEY_MAP;

const KEY_MAP keynames[] = {
 // KEY_DOWN
 {LEFT_SOFT, "lsoft"},
 {RIGHT_SOFT, "rsoft"},
 {GREEN_BUTTON, "green"},
 {RED_BUTTON, "red"},
 {ENTER_BUTTON, "enter"},
 {UP_BUTTON, "up"},
 {DOWN_BUTTON, "down"},
 {LEFT_BUTTON, "left"},
 {RIGHT_BUTTON, "right"},
 {VOL_UP_BUTTON, "volup"},
 {VOL_DOWN_BUTTON, "voldown"},
 {'0', "0"},
 {'1', "1"},
 {'2', "2"},
 {'3', "3"},
 {'4', "4"},
 {'5', "5"},
 {'6', "6"},
 {'7', "7"},
 {'8', "8"},
 {'9', "9"},
 {'*', "*"},
 {'#', "#"},
 // LONG_PRESS
 {LEFT_SOFT, "lsoft_lp"},
 {RIGHT_SOFT, "rsoft_lp"},
 {GREEN_BUTTON, "green_lp"},
 {RED_BUTTON, "red_lp"},
 {ENTER_BUTTON, "enter_lp"},
 {UP_BUTTON, "up_lp"},
 {DOWN_BUTTON, "down_lp"},
 {LEFT_BUTTON, "left_lp"},
 {RIGHT_BUTTON, "right_lp"},
 {VOL_UP_BUTTON, "volup_lp"},
 {VOL_DOWN_BUTTON, "voldown_lp"},
 {'0', "0_lp"},
 {'1', "1_lp"},
 {'2', "2_lp"},
 {'3', "3_lp"},
 {'4', "4_lp"},
 {'5', "5_lp"},
 {'6', "6_lp"},
 {'7', "7_lp"},
 {'8', "8_lp"},
 {'9', "9_lp"},
 {'*', "*_lp"},
 {'#', "#_lp"}
};

#define MAX_KEY_DOWN_NUM 22

KEY_PROC procmap[] = {
  MM_Show,
  DoExit,
  LoadDefPlaylist,
  DoExit,
  PlayTrackUnderC,
  CTUp,
  CTDown,
  PrevPL,
  NextPL,
  VolumeUp,
  VolumeDown,
  StopAllPlayback,
  StartRewindToBegin,
  CTUpSix,
  StartRewindToEnd,
  PrevTrackDown,
  TogglePlayback,
  NextTrackDown,
  CleanPlaylist,
  CTDownSix,
  ShowFM,
  ToggleVolume,
  SwitchPlayModeDown,
  SetNextPlayed,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

#define KEYS_COUNT (sizeof(procmap)/sizeof(procmap[0]))

void DoKey(int key)
{
  int startkn;
  int finishkn;
  if (key>LONG_PRESS_DIFF) {
    // Длинное нажатие
    startkn = MAX_KEY_DOWN_NUM+1;
    finishkn = KEYS_COUNT;
    key -= LONG_PRESS_DIFF;
  } else {
    // Короткое нажатие
    startkn = 0;
    finishkn = MAX_KEY_DOWN_NUM;
  }
  for(int cc=startkn;cc<=finishkn;cc++)
    if(keynames[cc].key==key) {
      if(procmap[cc])procmap[cc]();
      return;
    }
}

typedef struct {
  char* name;
  KEY_PROC proc;
} PROC_MAP;

const PROC_MAP keyprocs[] = {
  {"none", NULL},
  {"mainmenu", MM_Show},
  {"exit", DoExit},
  {"loaddefpl", LoadDefPlaylist},
  {"playtrack", PlayTrackUnderC},
  {"goup", CTUp},
  {"godown", CTDown},
  {"go6up", CTUpSix},
  {"go6down", CTDownSix},
  {"nextpl", NextPL},
  {"prevpl", PrevPL},
  {"volup", VolumeUp},
  {"voldown", VolumeDown},
  {"togglevolume", ToggleVolume},
  {"togglepb", TogglePlayback},
  {"stopall", StopAllPlayback},
  {"nexttrack", NextTrackDown},
  {"prevtrack", PrevTrackDown},
  {"switchmode", SwitchPlayModeDown},
  {"fm", ShowFM},
  {"nextplayed", SetNextPlayed},
  {"cleanpl", CleanPlaylist},
  {"rewindtoend", StartRewindToEnd},
  {"rewindtobegin", StartRewindToBegin},
  {"savepl", SavePL},
  {"goupspeed", CTUpSpeed},
  {"godownspeed", CTDownSpeed}
};

void KeysProc(char *name, char *value)
{
  strtolower(name, name, -1);
  strtolower(value, value, -1);

  int inkey=-1;
  KEY_PROC keyproc = DoErrKey;
  
  for(int cc=0;cc<KEYS_COUNT;cc++)
   if(strcmp(keynames[cc].name,name)==0)
   {
     inkey=cc;
     break;
   }
  if(inkey==-1) return;

  for(int cc=0;cc<sizeof(keyprocs)/sizeof(keyprocs[0]);cc++)
   if(strcmp(keyprocs[cc].name,value)==0)
   {
     keyproc=keyprocs[cc].proc;
     break;
   }
  
  procmap[inkey] = keyproc;    
}

void LoadKeys()
{
  char fname[256];
  sprintf(fname,"%s%s",SETS_PATH,"spkeys.cfg");
  if(LOAD_KEYS)
  EnumIni(1,(char*)&fname,KeysProc);
}
