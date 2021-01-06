#include "include.h"
#include "notify.h"
#include "file_works.h"

/*int IsMediaActive(void)
{
  char s[40];
  sprintf(s, RamMediaIsPlaying());
#ifdef NEWSGOLD
  if (s[0]==1) return 1;
#else
  if (s[0]==2) return 1;// для SGOLD s[0]!=2    
#endif 
  return 0;
}*/

void Play_Sound(const char * filename)
{
  if (!IsCalling()/* && !IsMediaActive()*/ && CFG_SOUNDS_VOLUME)
  {
    char full_filename[256];
    getSymbolicPath(full_filename, filename);
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(full_filename, &fstats, &err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR * sndPath = AllocWS(128);
      WSHDR * sndFName = AllocWS(128);
      char s[128];
      const char * p = strrchr(full_filename, '\\') + 1;
      str_2ws(sndFName, p, 128);
      strncpy(s, full_filename, p - full_filename);
      s[p - full_filename] = '\0';
      str_2ws(sndPath, s, 128);

      zeromem(&_sfo1, sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num = 1;
      _sfo1.time_between_play = 0;
      _sfo1.play_first = 0;
      _sfo1.volume = CFG_SOUNDS_VOLUME;
#ifdef NEWSGOLD
      _sfo1.unk6 = 1;
      _sfo1.unk7 = 1;
      _sfo1.unk9 = 2;
      PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4 = 0x80000000;
      _sfo1.unk5 = 1;
      PlayFile(0xC, sndPath, sndFName, 0, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5 = 1;
      PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
  }
}

GBSTMR VibraTimer;
int vibra_count;

void _vibra(void)
{
  StartVibra(vibra_count);
}

void StartVibra(int count)
{
  vibra_count = count;
  if(CFG_VIBRA_POWER && !IsCalling())
  {
    SetVibration(CFG_VIBRA_POWER);
    GBS_StartTimerProc(&VibraTimer, 216 >> 2, StopVibra);
  }
}

void StopVibra(void)
{
  SetVibration(0);
  if (--vibra_count)
    GBS_StartTimerProc(&VibraTimer, 216/40, _vibra);
}
