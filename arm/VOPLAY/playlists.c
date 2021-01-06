#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "mainmenu.h"
#include "conf_loader.h"
#include "../inc/stdbool.h"
#include "../inc/cfg_items.h"
#include "rect_patcher.h"

#ifdef OBS
extern HObj gObj;
#else
extern void* pha;
#endif
extern unsigned short playing;
GBSTMR tmr_rew;
extern short ModeRew;
extern const unsigned int SPEED_REW;        // Скорость перемотки  AAA
       // Шаг перемотки   AAA
extern int cp,WhatToView;
extern char spysok[2][256][128];//Максимальное количество песен - 255 (1 байт при сохранении)
extern unsigned int MAINGUI_ID;
extern bool tm_er;
extern int PLAY_ID;
//--------------------------------Перемока--------------------------------Vedan
extern int tm,         // Время
           rew_flag,
           pause_flag,
           ln;         // Длительность
unsigned int mlsc=0,   // Миллисекунды
             StopCount=0,
             IsRewind=0;

void StopRewind()       // Остановка перемотки :) 
{
  if(IsRewind)
  {
    rew_flag=1;
    StopCount = 0;
#ifndef OBS
    PlayMelody_SetPosition(PLAY_ID, mlsc);
    tm=mlsc/1000;
#else
    Obs_SetPosition (gObj, mlsc);
  //  Obs_Resume (gObj);
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
extern int CanRewind;
// Перемотка   // Оптимизировал   AAA
void StartRewind()
{
  //if(pause_flag==1) {playing=1; pause_flag=0;}
  rew_flag=0;
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
      DoRewinded();
    break;
  }
}

void Play_PauseResume()
{
  //if(pause_flag==1) {playing=1; pause_flag=0;}
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
/*if(tm_er)
    {
      tm_er=0;
#ifdef OBS
      Obs_SetPosition (gObj, tm);
#endif
     // Obs_Resume (gObj);
    }*/
#ifndef OBS
      if (PLAY_ID==-1)return;
      PlayMelody_ResumePlayBack(PLAY_ID);
#else
      Obs_Resume (gObj);
#endif
      //EXT_REDRAW();
              //if (entime==1){GBS_StartTimerProc(&TimeTimer,RedrawTime,timepp);}
              playing=1;
            }
        }
    }
  if ((IsGuiOnTop(MAINGUI_ID)==1)&&(WhatToView==0)){REDRAW();}
}

extern const char playerfolder[128];

typedef struct
{
  void *next;
  char cfgname[64];
  char fullpath[128];
}SEL_IPL;

int selipl_menu_onkey(void *gui, GUI_MSG *msg)
{
  SEL_IPL *sbtop=MenuGetUserPointer(gui);
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    int i=GetCurMenuItem(gui);
    for (int n=0; n!=i; n++) sbtop=sbtop->next;
    if (sbtop)
    {
      /*
      //Закрываем плеер и запускаем снова с новым плейлистом
      CLOSECURENTCSM();
      WSHDR* ws=AllocWS(128);
      wsprintf(ws,"%sivoplay.elf",playerfolder);
      ExecuteFile(ws,0,sbtop->fullpath);  
      FreeWS(ws);
      //Пока так, а там посмотрим...
      */
      char shliah[255];
      sprintf(shliah,"%sivoplay.elf",playerfolder);
      main(shliah,sbtop->fullpath);
      return (1);
    }
  }
  return (0);
}

void selipl_menu_ghook(void *gui, int cmd)
{
  SEL_IPL *sbtop=MenuGetUserPointer(gui);
  if (cmd==3)
  {
    while(sbtop)
    {
      SEL_IPL *sb=sbtop;
      sbtop=sbtop->next;
      mfree(sb);
    }    
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

int selipl_softkeys[]={0,1,2};
SOFTKEY_DESC selipl_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB selipl_skt=
{
  selipl_sk,0
};

void selipl_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  SEL_IPL *sbtop=user_pointer;
  WSHDR *ws;
  int len;
  for (int n=0; n!=cur_item; n++) sbtop=sbtop->next;
  void *item=AllocMenuItem(gui);
  if (sbtop)
  {
    len=strlen(sbtop->cfgname);
    ws=AllocMenuWS(gui,len+4);
    utf8_2ws(ws,sbtop->cfgname,320);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,pt,LG_ERROR);
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

MENU_DESC selipl_STRUCT=
{
  8,selipl_menu_onkey,selipl_menu_ghook,NULL,
  selipl_softkeys,
  &selipl_skt,
  0x10,
  selipl_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

HEADER_DESC selipl_HDR={0,0,0,0,NULL,(int)LG_SELECT_PLAYLIST,LGP_NULL};


int CreateMenuFindPlaylist()
{
  CloseMAINMENU();
  unsigned int err;
  DIR_ENTRY de;
  char e[256];
  sprintf(e,"%splaylists\\",playerfolder);
  const char *s=e;
  SEL_IPL *sbtop=0;
  SEL_IPL *sb;
  int n_ipl=0;
  char str[128];
  strcpy(str,s);
  strcat(str,"*.ipl");
  if (FindFirstFile(&de,str,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY))
      {
        extern int strcmp_nocase(const char *s, const char *d);
        sb=malloc(sizeof(SEL_IPL));
        strcpy(sb->fullpath,s);
        strcat(sb->fullpath,de.file_name);
        strcpy(sb->cfgname,de.file_name);
        sb->cfgname[strlen(de.file_name)-4]=0;
        sb->next=0;
        if (sbtop)
        {
          SEL_IPL *sbr, *sbt;
          sbr=(SEL_IPL *)&sbtop;
          sbt=sbtop;
          while(strcmp_nocase(sbt->cfgname,sb->cfgname)<0)
          {
            sbr=sbt;
            sbt=sbt->next;
            if (!sbt) break;
          }
          sb->next=sbt;
          sbr->next=sb;
        }
        else
        {
          sbtop=sb;
        }
        n_ipl++;        
      }
    }
    while(FindNextFile(&de,&err));
  }
  ////mfree(sb);
  FindClose(&de,&err);
  patch_header(&selipl_HDR);
  return CreateMenu(0,0,&selipl_STRUCT,&selipl_HDR,0,n_ipl,sbtop,0);
}
