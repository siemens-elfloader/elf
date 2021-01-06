

#define MAX_RECORDS 10
typedef struct
{
  char name[32];
  char use;
}RECORDS;
typedef struct
{
  char difficulty; //normal
  char opened_levels; //сколько уровней сейчас пройдено
  char recs_autosave;
  char SoundsEnable;
  char SndEnable;
  short StdSnd_user;
  short StdSnd_brick;
  char VibraEnable;
  char SndVolume;
  char VibraVolume;
  short VibraCount;
  char tmr_speed; //скорость таймера
  RECORDS recs[MAX_RECORDS];
}SAVE_DATA;

extern SAVE_DATA savedata;
extern void saveSettings();
extern void loadSettings();
extern void SetDefaultSettings();

