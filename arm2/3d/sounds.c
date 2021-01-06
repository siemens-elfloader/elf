#include "../inc/swilib.h"
#include "sounds.h"

char *sounds[]={"ak47.wav"};
//

int PLAY_ID=0xFFF;
int number=1;

void Play()//Функция для воспроизведения звуков\музыки
{

    WSHDR* sndPath=AllocWS(128);
    WSHDR* sndFName=AllocWS(128);


   wsprintf(sndFName, sounds[0]);
  

  wsprintf(sndPath,"0:\\sounds");
  PLAYFILE_OPT _sfo1;
  zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
  _sfo1.repeat_num=number;
  _sfo1.time_between_play=0;
  _sfo1.play_first=0;
  _sfo1.volume=5;
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
