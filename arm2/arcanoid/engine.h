#include "lcd/liblcd.h"

#define MAX_WIDTH 15
#define MAX_HEIGHT 32

#ifndef ELKA
#define W 133
#define H 177
#define FONT_SM 7
#define FONT_MD 5
#define FONT_LG 4
#else
#define W 240
#define H 320
#define FONT_SM 8
#define FONT_MD 7
#define FONT_LG 5
#endif



typedef struct
{
  char sign[4];
  char version[4]; //new
  char bg_num; //номер фона для текущего уровня
  char snd_num; //номер песни
  char type; //0=normal;1=boss.
  char boss_diff; //new
  char boss_lives;
}MAP;

extern int PLAY_ID;


extern short sw,sh;
extern GBSTMR gametimer;
extern IMGHDR *level_bg;
extern IMGHDR *load_screen;
extern char lgn[];
extern MAP map; //структ с некоторыми параметрами мапы
extern char total_levels; //сколько левелов нашли

extern char perc_t[];
extern char perc_s[];
extern char perc_d[];



void TimerRedrawScreen(void);
int Keyhook(GUI_MSG *msg);
void Init(void);
void LoadScreen(void);
void FreeMemory(void);
int fopen(const char * filename, unsigned int fileflags, unsigned int filemode, unsigned int *errornumber);
void Settings(void);
void About(void);
void ifree(IMGHDR *img);
void DrwImg(IMGHDR *img, int x, int y);



void SetDefaultGameParameters();
void PlayMusic(char id);
char PrepareLevel(char levelnum);
void StartVibra(char value,char len);



extern FSTATS fstats;
extern unsigned int err;












#define BON_USER_BIG 0
#define BON_USER_SMALL 1
#define BON_USER_FREEZE 2
#define BON_BALL_INCREASE 3
#define BON_BALL_DECREASE 4
#define BON_LIFE 5
#define BON_BALL_MEGA 6
#define BON_BALL_GHOST 7
#define BON_SHELLS 8
#define BON_ROCKETS 9
#define BON_SLIME 10
#define BON_DEFENSE 11
#define BON_BALL_BIG 12
#define BON_BALL_SMALL 13
#define BON_UNKNOWN 14
#define BON_100POINTS 15












#define MENU_MUSIC 0
#define GAME_MUSIC 1
#define LOSE_MUSIC 2
#define WIN_MUSIC 3
#define END_MUSIC 4

#define DIFF_EASY 0
#define DIFF_NORMAL 1
#define DIFF_HARD 2



#define STATE_GAME -1
#define STATE_MENU 0
#define STATE_SLEVEL 1
#define STATE_SETTINGS 2
#define STATE_RECORDS 3
#define STATE_ABOUT 4
#define STATE_PRESS 5
#define STATE_DBG_SETBALL 6



#define TYPE_NORMAL 0
#define TYPE_BOSS 1


#define PRESS_NEWLEVEL 0
#define PRESS_GAMEOVER 1
#define PRESS_LOSELIFE 2
#define PRESS_BOSSLOSE 3

