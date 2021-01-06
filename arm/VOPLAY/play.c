#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "conf_loader.h"
#include "../inc/stdbool.h"

#ifdef OBS
extern HObj gObj;
#else
extern void* pha;
#endif
int playing;
GBSTMR tmr_rew;
short ModeRew;
extern const unsigned int SPEED_REW;        // Скорость перемотки  AAA
extern const unsigned int STEP_REW;         // Шаг перемотки   AAA
extern bool tm_er;  
unsigned int MAINGUI_ID = 0;
int cp=0,WhatToView=0;
char spysok[2][256][128];//Максимальное количество песен - 255 (1 байт при сохранении)

//--------------------------------Перемока--------------------------------Vedan
extern int tm,         // Время
           ln;         // Длительность
unsigned int mlsc=0,   // Миллисекунды
             StopCount=0,
             IsRewind=0;

void StopRewind()       // Остановка перемотки :) 
{
  if(IsRewind)
  {
    StopCount = 0;
#ifndef OBS
    PlayMelody_SetPosition(PLAY_ID, mlsc);
#else
    Obs_SetPosition (gObj, mlsc);
    Obs_Resume (gObj);
#endif
    playing = 1;
    EXT_REDRAW();
    IsRewind = 0;
    GBS_DelTimer(&tmr_rew);
  }
}

// Слегка подправил   AAA
void DoRewinded()
{
  //DisableScroll();
  if(!StopCount) {
    mlsc=tm*1000+1000*ModeRew*STEP_REW;
    tm=mlsc/1000;      
    if(tm<=0) {
      tm=mlsc=0;
      StopCount=1;
    }
    if(tm>=ln) {
      tm=ln;
      StopCount=1;
    }
    REDRAW();
    GBS_StartTimerProc(&tmr_rew,SPEED_REW,DoRewinded);
  } else {
    StopRewind();
  }
}

// Перемотка   // Оптимизировал   AAA
void StartRewind()
{
  switch(playing)
  {
  case 2:
    // Если пауза - перематываем :) ...
#ifndef OBS
    if (PLAY_ID==-1)return;
#endif
      IsRewind=1;
      DoRewinded();
    break;
  case 1:
    // Если играет, ставим паузу и перематываем !! :)
#ifndef OBS
    if (PLAY_ID==-1)return;
#endif
      IsRewind=1;
#ifndef OBS
      PlayMelody_PausePlayback(PLAY_ID);
#else
      Obs_Pause (gObj);
#endif
      StopTMR(0);
     // PlayingStatus = 1;
      DoRewinded();
    break;
  }
}

void Play_PauseResume()
{
  if (playing==1)
    {
#ifndef OBS
    if (PLAY_ID==-1)return;
      PlayMelody_PausePlayback(PLAY_ID);
#else
      Obs_Pause (gObj);
#endif    
      StopTMR(0);
      playing=2;
    }
  else
    {
      if (playing==0)
        {
          char s[256];
          sprintf(s,"%s%s",spysok[0][cp],spysok[1][cp]);
          playing=1;
          Play(s);
        }
      else
        {
          if (playing==2)
            {
if(tm_er)
    {
      tm_er=0;
#ifdef OBS
      Obs_SetPosition (gObj, tm);
#endif
     // Obs_Resume (gObj);
    }
#ifndef OBS
      if (PLAY_ID==-1)return;
      PlayMelody_ResumePlayBack(PLAY_ID);
#else
      Obs_Resume (gObj);
#endif
      EXT_REDRAW();
              //if (entime==1){GBS_StartTimerProc(&TimeTimer,RedrawTime,timepp);}
              playing=1;
            }
        }
    }
  if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0)){REDRAW();}
}
