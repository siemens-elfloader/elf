/*
* Ping-Pong 2009 - 2010
* other
* (c) Danil_e71
*/

#include "other.h"

void deltimers()
{
  if(IsTimerProc(&tmr))GBS_DelTimer(&tmr);//Убиваем таймеры
  if(IsTimerProc(&vibr))GBS_DelTimer(&vibr);
}
void Play(int mod)//Функция для воспроизведения звуков\музыки
{
  int soun;
 if (on_off_sound!=0)
  {
    WSHDR* sndPath=AllocWS(128);
    WSHDR* sndFName=AllocWS(128);
   if(mod==1)
  {
   soun=1;
   wsprintf(sndFName, "kick.mid");
  }
  if(mod==2)
  {
   soun=999;
   wsprintf(sndFName, "game.mid");
  }
  wsprintf(sndPath,per_s,folder,"Sounds\\");
  PLAYFILE_OPT _sfo1;
  zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
  _sfo1.repeat_num=soun;
  _sfo1.time_between_play=0;
  _sfo1.play_first=0;
  _sfo1.volume=def_vol;
  #ifdef NEWSGOLD
  _sfo1.unk6=1;
  _sfo1.unk7=1;
  _sfo1.unk9=2;
  PLAY_ID = PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  #ifdef X75
  _sfo1.unk4=0x80000000;
  _sfo1.unk5=1;
  PLAY_ID = PlayFile(0xC, sndPath, sndFName, 0,MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  _sfo1.unk5=1;
  PLAY_ID = PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #endif
  #endif 
  FreeWS(sndPath);
  FreeWS(sndFName);
  }
}
int openconf()//Для чтения настроек с конфига
{
extern const char *successed_config_filename;
WSHDR *fws=AllocWS(strlen(successed_config_filename)+1);
wsprintf(fws,perc_t,successed_config_filename);
ExecuteFile(fws,NULL,NULL);
FreeWS(fws);
return 0;
}
void startcont()
{
  switch(game_new_cont)
  {
  case 1:case 2:
    setgame(1);
    Time.min=Time.hour=Time.mymsec=Time.sec=0;
     break;
  case 3:
    status=game;
    running=0;
    break;
  }
  if(on_off_sound==2)Play(2); 
}
void exit(){exiting=1;}
