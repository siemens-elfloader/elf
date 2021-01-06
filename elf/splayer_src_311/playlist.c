#include "../inc/swilib.h"
#include "../inc/cfg_items.h"
#include "../inc/stdbool.h"
#include "main.h"
#include "playlist.h"
#include "mylib.h" 
#include "langpack.h"
#include "FM.h"

WSHDR *playlist_lines[TCPL][TClines];  // Массив указателей на имена файлов в пл   Mr. Anderstand: Воплотим мечту в жизнь!
extern char *Playlists[TCPL];

// Из конфига
extern const unsigned int SHOW_NAMES;
extern const char PLAYLISTS[];
extern const char PIC_DIR[];                // Для курсора AAA
extern const unsigned int EXT;              // Расширение по умолчанию
extern const unsigned int soundvolume;      // Громкость
extern const unsigned int SizeOfFont;       // Шрифт AAA
extern const unsigned int SCROLL_MULT;      // Скорость листания   перенес в конфиг  AAA
extern const unsigned int STEP_SCROLL_MULT; // Шаг быстрого листания   AAA
extern const unsigned int SPEED_REW;        // Скорость перемотки  AAA
extern const unsigned int STEP_REW;         // Шаг перемотки   AAA
extern const unsigned int SPEED_MOVE;       // Скорость перелистывания пл  AAA
extern const unsigned int SPEED_OPEN_MOVE;  // Скорость открытия пл  AAA

// Мои переменные
unsigned short SoundVolume;           // Громкость
unsigned short SVforToggle = 0;       // Прежняя громкость
unsigned short PlayingStatus = 0;     // Статус плеера (0 - стоп, 1 - пауза, 2 - играем)   // Было char стало unsigned short! :D   AAA
short phandle = -1;                   // Что играем

#ifdef OBS
extern HObj gObj;
#else
extern void* pha;
#endif

int CurrentTrack[TCPL];                 // Текущий трек
int PlayedTrack[TCPL];                  // Проигрываемый трек   AAA
int CurrentPL=0;                        // Текущий пл   AAA
int PlayedPL=0;                         // Пл воспроизведения   AAA
unsigned int TC[TCPL];                  // Количество треков в пл 
bool ready[TCPL];
extern const unsigned int LinesInPL_C; // Количество треков (макс)
//unsigned int LinesInPL;
unsigned short NextPlayedTrack[2];     // № трека и пл в очереди
unsigned short ShowNamesNoConst;       // В константе не получается изменять   AAA
extern const char p_3s[];

extern unsigned short coord[ncoord];
extern char COLOR[ncolor][4];
/*
extern char COLOR_TEXT[];
extern char COLOR_TEXT_CURSOR[]; //Еще добавил  AAA
extern char COLOR_TEXT_PLAY[];   //И еще AAA
extern char COLOR_BANDROLL[];    //Цвет полосы прокрутки
extern char COLOR_BANDROLL_C[];

extern unsigned short CTmy_x;     // Координаты CurrentTrack
extern unsigned short CTmy_y;
extern unsigned short s;          // Смещение по вертикали
extern unsigned short NUMmy_x;    // Номера
extern unsigned short NUMmy_y;
// Полоса прокрутки
unsigned short BR_x;  //=129;
unsigned short BR1_y;  //=50;
unsigned short BR2_y;  //=152;
unsigned short BR_w;  //=1;
unsigned short BRC_x;  //=128;
unsigned short BRC_w;  //=2;
// Полоса прокрутки
*/
// Всякие "мелкие" переменные
extern unsigned int playmode;
extern bool copy;
extern const unsigned int GrafOn;     // 1,если включены эффекты типа скролла   AAA
extern const unsigned int GrafOn1;    // 1,если включена анимация   AAA
extern const unsigned int InfoOn;     // 1,если включен показ информации   Vedan
extern const unsigned int SHOW_POPUP; // 1,если включены попапы   AAA
extern const unsigned int ALLTRACK;   // 1,если включено отображение всех треков    AAA
extern const unsigned int SAVE_SETS;  // 1,если включено сохранение настроек   AAA
bool stop=1;                          // 1,если останавливаем листание   AAA
extern unsigned short Stat_keypressed;
bool FM_o=0;
extern bool tm_er;                    // 1,если случился посторонний звук или нет   AAA
short ModeRew;  // Режим перемотки (-1 - назад, +1 - вперед)
short ModeMove;
short SpeedMove;
// Всякие "мелкие" переменные

extern unsigned int MAINGUI_ID;

// --- Скроллинг ---

#define TMR_SEC 216*2
GBSTMR tmr_scroll;
GBSTMR tmr_displacement;
GBSTMR tmr_cursor_move;
GBSTMR tmr_pl_move;
GBSTMR tmr_rew;
GBSTMR tmr_opan;
volatile int scroll_disp;
volatile int max_scroll_disp;

void DisableScroll(void)
{
  GBS_DelTimer(&tmr_scroll);
  max_scroll_disp=0;
  scroll_disp=0;
}

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

// --- Скроллинг ---
/*
// Поднимаем громкость
void VolumeUp()
{
#ifdef NEWSGOLD
  if(SoundVolume<5)SoundVolume++;
#else
  if(SoundVolume<14)SoundVolume++;
#endif
  if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  REDRAW();
}

// Опускаем громкость
void VolumeDown()
{
  if(SoundVolume>0)SoundVolume--;
  if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  REDRAW();
}

// Громкость на ноль
void ToggleVolume()
{
  if(SVforToggle!=0)
  {
    SoundVolume = SVforToggle;
    SVforToggle = 0;
    if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  } else 
  {
    SVforToggle = SoundVolume;
    SoundVolume = 0;
    if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
  }
  REDRAW();
}
*/
// Поднимаем громкость
void VolumeUp()
{
#ifdef NEWSGOLD

  if(SoundVolume<15)SoundVolume++;
#ifndef OBS
  if(phandle!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], SoundVolume, 1);
#else
  Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif

#else

#ifndef OBS
  if(SoundVolume<14)SoundVolume++;
  if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
#else
  if(SoundVolume<15)SoundVolume++;
  Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif

#endif
  REDRAW();
}

// Опускаем громкость
void VolumeDown()
{
  if(SoundVolume>0)SoundVolume--;
#ifdef NEWSGOLD
#ifndef OBS
  if(phandle!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], SoundVolume, 1);
#else
  Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif
#else
#ifndef OBS
  if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
#else
  Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif
#endif
  REDRAW();
}

// Громкость на ноль
void ToggleVolume()
{
  if(SVforToggle!=0)
  {
    SoundVolume = SVforToggle;
    SVforToggle = 0;
#ifdef NEWSGOLD
#ifndef OBS
    if(phandle!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], SoundVolume, 1);
#else
    Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif
#else
#ifndef OBS
    if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
#else
    Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif
#endif
  } else 
  {
    SVforToggle = SoundVolume;
    SoundVolume = 0;
#ifdef NEWSGOLD
#ifndef OBS
    if(phandle!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], SoundVolume, 1);
#else
    Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif
#else
#ifndef OBS
    if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
#else
    Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
#endif
#endif
  }
  REDRAW();
}

int random(int dummy,int max)
{
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  return((dummy*time.sec + 
          time.hour + 
           time.min*time.sec + 
            time.millisec + 
             date.day + 
              date.month +
               date.year +
                 time.millisec*time.sec)%max+1);
}



// Случайный трек DemonGloom
void RandTrack() 
{
  if(ready[PlayedPL])
  {
     extern int tm;
#ifndef OBS
   if(phandle!=-1)PlayMelody_StopPlayback(phandle);
#else
   Obs_Stop (gObj);
#endif
   if(NextPlayedTrack[1]){PlaySetTrack();}
   else
   {
     int prevtrack=PlayedTrack[PlayedPL];
     while (PlayedTrack[PlayedPL]==prevtrack) 
     {
       PlayedTrack[PlayedPL]=random(tm+prevtrack,TC[PlayedPL]);
     }
  
     if(PlayedTrack[PlayedPL]>TC[PlayedPL])PlayedTrack[PlayedPL]=1;
     if (CurrentPL==PlayedPL)
     {
       if (CurrentTrack[CurrentPL]==prevtrack)
       {  // Перенос курсора на следующую песню
        CurrentTrack[CurrentPL]=PlayedTrack[PlayedPL];
       }
       
       if (0==prevtrack)
       {  // Перенос курсора на следующую песню
        CurrentTrack[CurrentPL]=PlayedTrack[PlayedPL];
       }
    }
  }
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

//Повторяющийся трек       Ничего умнее не придумал...  AAA
void RepeatTrack()
{
  if(ready[PlayedPL]){
#ifndef OBS
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
#else
  Obs_Stop (gObj);
#endif
  if(NextPlayedTrack[1]){PlaySetTrack();}
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

// Для plamode==1       Ничего умнее не придумал...  AAA // Не понял я этого режима... DG
void NextTrackX()
{
  if(ready[PlayedPL]){
#ifndef OBS
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
#else
  Obs_Stop (gObj);
#endif
  
  if(PlayedTrack[PlayedPL]<TC[PlayedPL]||NextPlayedTrack[1])
  {
    if(NextPlayedTrack[1]){PlaySetTrack();}
    else {PlayedTrack[PlayedPL]++;}
    PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
  }
  else
  {
    StopTMR(1);
    PlayingStatus=0;
    PlayedTrack[PlayedPL]=1;
  }
  }
}

// Следующий трек пл AAA
void NextTrack()
{
  if(ready[PlayedPL]){
#ifndef OBS
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
#else
  Obs_Stop (gObj);
#endif
//  if (CurrentTrack==(PlayedTrack-1)){// Перенос курсора на следующую песню  // И зачем? То пытаемся не повторять ошибок
//    CurrentTrack=PlayedTrack;        // встроенного плеера, а тут... И Где логика если у следующей функции нет аналогичного свойства??  AAA
//    if(PlayedTrack>TC) CurrentTrack=1;
//    }
  if(NextPlayedTrack[1]){PlaySetTrack();}
  else{
  if(PlayedTrack[PlayedPL]<TC[PlayedPL]) {PlayedTrack[PlayedPL]++;}
  else {PlayedTrack[PlayedPL]=1;}
  }
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

// Предыдущий трек пл AAA
void PreviousTrack()
{
  if(ready[PlayedPL]){
#ifndef OBS
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
#else
  Obs_Stop (gObj);
#endif
  if(PlayedTrack[PlayedPL]>1) {PlayedTrack[PlayedPL]--;}
  else {PlayedTrack[PlayedPL]=TC[PlayedPL];}
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));}
}

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
    PlayMelody_SetPosition(phandle, mlsc);
#else
    Obs_SetPosition (gObj, mlsc);
    Obs_Resume (gObj);
#endif
    PlayingStatus = 2;
    EXT_REDRAW();
    IsRewind = 0;
    GBS_DelTimer(&tmr_rew);
  }
}

// Слегка подправил   AAA
void DoRewinded()
{
  DisableScroll();
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
  switch(PlayingStatus)
  {
  case 1:
    // Если пауза - перематываем :) ...
#ifndef OBS
    if (phandle==-1)return;
#endif
      IsRewind=1;
      DoRewinded();
    break;
  case 2:
    // Если играет, ставим паузу и перематываем !! :)
#ifndef OBS
    if (phandle==-1)return;
#endif
      IsRewind=1;
#ifndef OBS
      PlayMelody_PausePlayback(phandle);
#else
      Obs_Pause (gObj);
#endif
      StopTMR(0);
     // PlayingStatus = 1;
      DoRewinded();
    break;
  }
}
//------------------------------------------------------------------------------


// Пауза/Воспроизведение
void TogglePlayback()
{
  Stat_keypressed = 1;
  switch(PlayingStatus)
  {
  case 0:
    // Если стоп, то воспроизводим текущий...
    if(ready[PlayedPL]) {PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL] = 1)); PlayingStatus = 2;} //Чуток изменил   AAA
    break;
  case 1:
    // Если пауза - продолжаем воспроизведение...
    if(tm_er)
    {
      tm_er=0;
      /*Obs_Stop(gObj);
      Obs_Start(gObj);
      Obs_Pause(gObj);*/
#ifdef OBS
      Obs_SetPosition (gObj, tm);
#endif
     // Obs_Resume (gObj);
    }
#ifndef OBS
      if (phandle==-1)return;
      PlayMelody_ResumePlayBack(phandle);
      PlayMelody_ChangeVolume(phandle,SoundVolume);
#else
      Obs_Resume (gObj);
#endif
      EXT_REDRAW();
      PlayingStatus = 2;
    break;
  case 2:
    // Если играет - ставим паузу...
#ifndef OBS
    if (phandle==-1)return;
      PlayMelody_PausePlayback(phandle);
#else
      Obs_Pause (gObj);
#endif
      StopTMR(0);
      PlayingStatus = 1;
    break;
  }
}

// Останавливаем проигрывание
void StopAllPlayback()
{
  SendNULL();
  StopTMR(1);
  Stat_keypressed = 1;
  if(PlayingStatus==0)return;
#ifndef OBS
  if (phandle==-1)return;
    PlayMelody_StopPlayback(phandle);
#else
    Obs_Stop (gObj);
#endif
    PlayingStatus = 0;
}

// Постановка в очередь   AAA
void SetNextPlayed()
{
  NextPlayedTrack[0]=CurrentPL;
  NextPlayedTrack[1]=CurrentTrack[CurrentPL];
}

// Воспроизведение поставленного в очередь   AAA
void PlaySetTrack()
{
  PlayedTrack[PlayedPL]=0;
  PlayedPL=NextPlayedTrack[0];
  PlayedTrack[PlayedPL]=NextPlayedTrack[1];
  CurrentTrack[PlayedPL]=PlayedTrack[PlayedPL];
  NextPlayedTrack[0]=NULL;
  NextPlayedTrack[1]=NULL;
}

volatile unsigned short s=0, op=0;
// Сходим с ума по гламуру :)   AAA
void Disable_OpenAnim(void)
{
  GBS_DelTimer(&tmr_opan);
  s=0;
  REDRAW();
  op=0;
}

void OpenAnim(void)
{
  if(op<6&&GrafOn1)
  {
    s++;
    op++;
    REDRAW();
    GBS_StartTimerProc(&tmr_opan,SPEED_OPEN_MOVE,OpenAnim);
  }
  else
  {
    if(op) Disable_OpenAnim();
  }
}

unsigned short imove=0;
short PL_move_L[6];

void Disable_PL_mp(void)
{
  GBS_DelTimer(&tmr_cursor_move);
   /* for(unsigned short i=0; i<6; i++)
    {
      PL_move_L[i]=0;
    }*/
  REDRAW();
  imove=0;
}

void PL_mp(void)
{
  if(imove<8&&GrafOn1)
  {
    for(unsigned short i=0; i<6; i++)
    {
      PL_move_L[i]=(3*(8-imove)*(8-imove)-15*(5-i))*ModeMove;
      if((ModeMove>=0&&PL_move_L[i]<=coord[7])||(ModeMove<=0&&PL_move_L[i]>=coord[7])||imove==7) {PL_move_L[i]=0;}
    }
  //  coord7=(132-real[imove]/*30*imove*/)*ModeMove;
    imove++;
    REDRAW();
    GBS_StartTimerProc(&tmr_pl_move,SPEED_MOVE,PL_mp);
  }
  else
  {
    if(imove) Disable_PL_mp();
  }
}

void MovePL()
{
  DisableScroll();
  
  if(0<=(CurrentPL+ModeMove)&&(CurrentPL+ModeMove)<TCPL)
  {
    CurrentPL+=ModeMove;
  }else{
    if(ModeMove>0) {CurrentPL=0;}
    else {CurrentPL=TCPL-1;}
  }
  PL_mp();
  REDRAW();
}

// Потребовалось для исправления глюка AAA
void CTtoFirst()
{
  if(CurrentTrack[CurrentPL]!=1)CurrentTrack[CurrentPL] = 1;
}

// Сделал в две для удобства AAA
void PTtoFirst()
{
  if(PlayedPL==CurrentPL&&PlayedTrack[PlayedPL]!=0)PlayedTrack[PlayedPL] = 0;
}


// Фторопях, неидеально, с небольшими недочетами   AAA
short p, p1, p3;
short n, d, v, v1, v2;
volatile unsigned short i;
void Disable_PL(void)
{
    p1=0;
    p3=0;
    p=0;
    REDRAW();
    GBS_DelTimer(&tmr_cursor_move);
    d=0;
    n=0;
    i=0;
}

void PL(void)
{
 // unsigned short i=0;
 // unsigned short n=0;
  if(i<4&&GrafOn1)
  {
    i++;
    n-=coord[6]/4;
    p=n;
    p3=n;
    
    d-=coord[6]/2;
    p1=d;
    
    REDRAW();
    GBS_StartTimerProc(&tmr_cursor_move,10,PL);
    
  }else{
    if(i)Disable_PL();
  }
}

//Пробуем листание вниз AAA
void CTDown()
{
  DisableScroll();
  v=-1;
  v1=0;
  v2=1;
  PL();
  if (CurrentTrack[CurrentPL]<TC[CurrentPL])
  {
    CurrentTrack[CurrentPL]++;
  }
  else
  {
    CurrentTrack[CurrentPL] = 1;
  }
}

//Пробуем листание вверх AAA
void CTUp()
{
  DisableScroll();
  v=1;
  v1=1;
  v2=0;
  PL();
  if (CurrentTrack[CurrentPL]>1)
  {
    CurrentTrack[CurrentPL]--;
  }
  else
  {
    CurrentTrack[CurrentPL] = TC[CurrentPL];
  }
}

void Disable_CTSpeed(void)
{
  stop=1;
  GBS_DelTimer(&tmr_displacement);
}

// Быстрое листание AAA
void CTSpeed(void)
{
  DisableScroll();
  if(stop==0)
  {
    if (CurrentTrack[CurrentPL]+SpeedMove*STEP_SCROLL_MULT>=1&&CurrentTrack[CurrentPL]+SpeedMove*STEP_SCROLL_MULT<=TC[CurrentPL])
    {
      CurrentTrack[CurrentPL]+=SpeedMove*STEP_SCROLL_MULT;
    }
    else
    {
      if(SpeedMove>0) {CurrentTrack[CurrentPL] = 1;}
      else {CurrentTrack[CurrentPL] = TC[CurrentPL];}
    }
    REDRAW();
    GBS_StartTimerProc(&tmr_displacement,10*SCROLL_MULT,CTSpeed);
  }
}

//Листание шопестец вниз AAA
void CTDownSix()
{
  DisableScroll();
  if ((TC[CurrentPL]>6)&&(CurrentTrack[CurrentPL]+6<TC[CurrentPL]+1))
  {
    CurrentTrack[CurrentPL] = CurrentTrack[CurrentPL]+6;
  }
  else
  {
    CurrentTrack[CurrentPL] = TC[CurrentPL];
  }
}

//Листание шопестец вверх AAA
void CTUpSix()
{
  DisableScroll();
  if ((TC[CurrentPL]>6)&&(CurrentTrack[CurrentPL]-6>0))
  {
    CurrentTrack[CurrentPL] = CurrentTrack[CurrentPL]-6;
  }
  else
  {
    CurrentTrack[CurrentPL] = 1;
  }
}

//Воспроизвести AAA
void PlayTrackUnderC()
{
  if(ready[CurrentPL]){
  Stat_keypressed = 1;
#ifndef OBS
  if(phandle!=-1)PlayMelody_StopPlayback(phandle);
#else
  Obs_Stop (gObj);
#endif
  if(PlayedPL!=CurrentPL)
  {
    PlayedTrack[PlayedPL] = 0;
    PlayedPL=CurrentPL;
  }
  PlayedTrack[PlayedPL] = CurrentTrack[CurrentPL];
  PlayMP3File(GetPlayedTrack(PlayedTrack[PlayedPL]));
  }else{
    char p[256];
    ws_2str(GetCurrentTrack(CurrentTrack[CurrentPL]),p,256);
    LoadingPlaylist(p);
    OpenAnim();
  }
}

// Выдаем текущий статус
char GetPlayingStatus()
{
  return PlayingStatus;
}

// Громкость
unsigned short GetVolLevel()
{
  return SoundVolume;
}

// Устанавливаем статус
void SetPlayingStatus(char PS)
{
  PlayingStatus = PS;
}

// Установим указатель на проигрываемую мелодию...
void SetPHandle(short ph)
{
  phandle = ph;
}

// Возвращает кол-во треков в загруженном пл
int GetTC()
{
  return TC[CurrentPL];
}

/*
 Работаем с mp3-файлами
*/
/*
// Возвращаем структуру mp3-тега
int GetMP3Tag_v1(const char * fname, MP3Tagv1 * tag)
{
  int fh = -1;
  unsigned int err;
  if ((fh=fopen(fname,A_TXT+A_ReadOnly,P_READ,&err))!=-1)
  {
    unsigned int size = lseek(fh,0,S_END,&err,&err);
    lseek(fh,size-128,S_SET,&err,&err);
    zeromem(&tag,sizeof(MP3Tagv1));
    fread(fh,tag->id,3,&err);
    if (tag->id=="TAG")
    {
      fread(fh,tag->title,30,&err);
      fread(fh,tag->artist,30,&err);
      fread(fh,tag->album,30,&err);
      fread(fh,tag->year,4,&err);
      fread(fh,tag->comment,30,&err);
      return 1;
    }
    fclose(fh,&err);
  }
  return 0;
}
*/
/*
 Здесь собственно работа с плейлистом...
*/
/*
// Выделим память   AAA
void Memory()
{
 // LinesInPL=LinesInPL_C;
  for(unsigned int i=0;i<5;i++)
  {
    for(unsigned int j=0;j<256;j++)
    {
      playlist_lines[i][j]=AllocWS(256);
    }
  }
}
*/
// Свобода пл!
void FreePlaylist(void)
{
   // for(unsigned int i=0;i<5;i++)
   // {
   //   for(unsigned int j=0;j<256;j++)
   //   {
   //     FreeWS(playlist_lines[i][j]);
   //     playlist_lines[i][j]=NULL;
  //    }
 //   }
  for(unsigned int i=0; i<TCPL; i++) {
  while(TC[CurrentPL]>0)
        {
          DeleteLine();
        }
    if(CurrentPL<TCPL-1) {CurrentPL++;}
    else {CurrentPL=0;}
  }
}


unsigned int char8to16(int c)
{
  if (c==0xA8) c=0x401;
  if (c==0xAA) c=0x404;
  if (c==0xAF) c=0x407;
  if (c==0xB8) c=0x451;
  if (c==0xBA) c=0x454;
  if (c==0xBF) c=0x457;
  if (c==0xB2) c=0x406;
  if (c==0xB3) c=0x456;
  if ((c==0xC0)&&(c==0x100)) c+=0x350;
  return c;
}

void ascii2ws(char *s, WSHDR *ws)
{
  int c;
  while ((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

// Сохраняем пл!     Пока так оставлю :)   AAA
void SavePlaylist(char *fn)
{
  int j=0;
  int f;
  char m[256];
  char s[]={0x0D,0x0A}; // Сделал совместимость с m3u 
  if(EXT==0){sprintf(m,"%s%s",fn,".spl");}
  else{sprintf(m,"%s%s",fn,".m3u");}                      // ----------- 
  FSTATS fstats;
  unsigned int err;
  while (GetFileStats(m,&fstats,&err)!=-1)       // Проверка файла на существование
  {
    j++;
    if(EXT==0){sprintf(m,"%s%i%s",fn,j,".spl");}
    else{sprintf(m,"%s%i%s",fn,j,".m3u");}
  }
  f=fopen(m,A_ReadWrite/*+A_MMCStream*/+A_Create+A_BIN,P_READ+P_WRITE,&err);
  if(EXT==1){fwrite(f,"#EXTM3U",7,&err); fwrite(f,s,2,&err);}
  for (unsigned int i=0;i<TC[CurrentPL];i++)
  {
    char *p = malloc(wstrlen(playlist_lines[CurrentPL][i+1]) * 2 + 1);
    int len;
    ws_2utf8(playlist_lines[CurrentPL][i+1], p, &len, wstrlen(playlist_lines[CurrentPL][i+1]) * 2 + 1);
    fwrite(f,p,strlen(p),&err);
    fwrite(f,s,2,&err);
    mfree(p);
  }
  fclose(f,&err);
  if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_PL_Saved]);
}

/////////////////////////////////////////////////////<<<РЕДАКТИРОВАНИЕ ПЛ>>>/////////////////////////////////////////////////////////
// Добавляем строку в пл   AAA
void PastLine(WSHDR *p, unsigned short i) // Добавляем главно не с [0][0], а [0][1] почему-то... Работать должно тем не менее   AAA
{
  if(TC[CurrentPL]==TClines-1) {ShowMSG(1,(int)lgpData[LGP_eoPL]); return;}
  playlist_lines[CurrentPL][TC[CurrentPL]+1]=AllocWS(256);
  wstrcpy(playlist_lines[CurrentPL][TC[CurrentPL]+1],p);
  TC[CurrentPL]++;
  if(i) {CurrentTrack[CurrentPL]=TC[CurrentPL];}
}

// Копируем строку в пл   AAA
void CopyLine(WSHDR *p)
{
  TC[CurrentPL]++;
  for(int i=TC[CurrentPL];i>CurrentTrack[CurrentPL]-1;i--)
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i-1]);
    }
  wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]],p);
  if(PlayedTrack[PlayedPL]>CurrentTrack[CurrentPL]-1) {PlayedTrack[PlayedPL]++;}
  copy=0;
}

// Удаляем строку из пл   AAA
void DeleteLine()  // Стираем однако тоже до [0][1] и поэтому я считаю беспокоиться не стоит.   AAA
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0&&TC[CurrentPL]>0)
  {
  if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=0;}
  else{if(CurrentTrack[CurrentPL]<PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}}
  
  int i=CurrentTrack[CurrentPL];
  if(i!=TC[CurrentPL])
  {
    while(i<TC[CurrentPL])
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i+1]);
      i++;
    }
  }
  else
  {
    if(CurrentTrack[CurrentPL]>1) {CurrentTrack[CurrentPL]--;}   // Не хочу рыть весь код, подстрахуюсь так   AAA
  }
  FreeWS(playlist_lines[CurrentPL][TC[CurrentPL]]);
  playlist_lines[CurrentPL][TC[CurrentPL]]=NULL;
  TC[CurrentPL]--;
  }
}

// Перемещаем строку в пл вверх   AAA
void MoveLineUp()
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0)
  {
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy)
  {
    CopyLine(p);
    
  }else{
    
  if(CurrentTrack[CurrentPL]!=1)
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}
    else{if(CurrentTrack[CurrentPL]-1==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]++;}}
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]],playlist_lines[CurrentPL][CurrentTrack[CurrentPL]-1]);
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]-1],p);
    CurrentTrack[CurrentPL]--;
  }
  else
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=TC[CurrentPL];}
    else{if(PlayedTrack[PlayedPL]!=0) {PlayedTrack[PlayedPL]--;}}
    for(int i=1;i<TC[CurrentPL];i++)
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i+1]);
    }
    wstrcpy(playlist_lines[CurrentPL][TC[CurrentPL]],p);
    CurrentTrack[CurrentPL]=TC[CurrentPL];
  }
  }
  FreeWS(p);
  }
}

// Перемещаем строку в пл вниз   AAA
void MoveLineDown()
{
  DisableScroll();
  if(CurrentTrack[CurrentPL]>0)
  {
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy)
  {
    CopyLine(p);
    
  }else{
    
  if(CurrentTrack[CurrentPL]!=TC[CurrentPL])
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]++;}
    else{if(CurrentTrack[CurrentPL]+1==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]--;}}
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]],playlist_lines[CurrentPL][CurrentTrack[CurrentPL]+1]);
    wstrcpy(playlist_lines[CurrentPL][CurrentTrack[CurrentPL]+1],p);
    CurrentTrack[CurrentPL]++;
  }
  else
  {
    if(CurrentTrack[CurrentPL]==PlayedTrack[PlayedPL]&&CurrentPL==PlayedPL) {PlayedTrack[PlayedPL]=1;}
    else {if(PlayedTrack[PlayedPL]!=0) {PlayedTrack[PlayedPL]++;}}
    for(int i=TC[CurrentPL];i>1;i--)
    {
      wstrcpy(playlist_lines[CurrentPL][i],playlist_lines[CurrentPL][i-1]);
    }
    wstrcpy(playlist_lines[CurrentPL][1],p);
    CurrentTrack[CurrentPL]=1;
  }
  }
  FreeWS(p);
  }
}

// Перемещаем строку в следующий пл   AAA
void MoveLineRight()
{
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy==0) {DeleteLine();}
  else {copy=0; DisableScroll();}
  NextPL();
  PastLine(p, 1);
  FreeWS(p);
}

// Перемещаем строку в предыдущий пл   AAA
void MoveLineLeft()
{
  WSHDR *p=AllocWS(256);
  wstrcpy(p,playlist_lines[CurrentPL][CurrentTrack[CurrentPL]]);
  if(copy==0) {DeleteLine();}
  else {copy=0; DisableScroll();}
  PrevPL();
  PastLine(p, 1);
  FreeWS(p);
}
/////////////////////////////////////////////////////<<<РЕДАКТИРОВАНИЕ ПЛ>>>/////////////////////////////////////////////////////////

// Возвращает имя файла по полному пути...
void FullpathToFilename(WSHDR * fnamews, WSHDR * wsFName)
{
      int len=wstrlen(fnamews);                     // Сделал так. Старая версия пусть тоже живет как пример   AAA
      short pos=wstrrchr(fnamews,len,'\\'); 
      short pos2=wstrrchr(fnamews,len,'.'); 
      wstrcpybypos(wsFName,fnamews,pos+1,pos2-pos-1);
/*
  char *fname = malloc(wstrlen(fnamews) * 2 + 1);
  int len;
  ws_2utf8(fnamews, fname, &len, wstrlen(fnamews) * 2 + 1);
  const char *p=strrchr(fname,'\\')+1;
  int length=strrchr(fname,'.')-strrchr(fname,'\\')-1;
  utf8_2ws(wsFName,p,length);
  mfree(fname);*/

     /* const char *p=strrchr(fname,0x1f)+1;
      const char *p2=strrchr(fname,'\\')+1;                         // Фикс для убирания этого странного символа... Теперь русский стал нормально
       if (p2>p){
         int length=strrchr(fname,'.')-strrchr(fname,'\\')-1;
         utf8_2ws(wsFName,p2,length);
       }else{
         int length=strrchr(fname,'.')-strrchr(fname,'\\')-2;
         utf8_2ws(wsFName,p,length);
       }*/
}

// Возвращает имя файла с расширением. // Теперь быстрее работает. // Снова переделал   AAA
void FullpathToFile(WSHDR * fnamews, WSHDR * wsFName)
{
  char *fname = malloc(wstrlen(fnamews) * 2 + 1);
  int len1;
  ws_2utf8(fnamews, fname, &len1, wstrlen(fnamews) * 2 + 1);
  unsigned int len=strlen(fname);

  if(fname[len-1]=='\\') {fname[len]=0; fname[len-1]='\0';}

  const char *p=strrchr(fname,'\\')+1;
  utf8_2ws(wsFName,p,strlen(p)+1);
  if(fname[len-1]=='\0') {wsprintf(wsFName,"%w\\",wsFName);}
  
  mfree(fname);
}

void fix(char* p)  // Убираем странный символ (всвязи с переходом на WSHDR)   AAA
{
  unsigned short j=0;
  char* p1=malloc(256);
  for(unsigned short i=0;i<256;i++)
  {
    if(p[i]!=0x1f) {p1[j++]=p[i];}
  }
  strcpy(p,p1);
  mfree(p1);
}

// Возвращется трек по номеру в пл
WSHDR * GetCurrentTrack()
{
  return playlist_lines[CurrentPL][CurrentTrack[CurrentPL]];
}

WSHDR * GetPlayedTrack()
{
  return playlist_lines[PlayedPL][PlayedTrack[PlayedPL]];
}

// Возвращает имя воспроизводимого по номеру в пл
WSHDR * GetTrackByNumber(WSHDR**mass, int number)
{
  return mass[number];
}
/*
GBSTMR sctm;
WSHDR* wsfile=NULL;
short tggl=1;
short pos=0;
short wait=0;

void DrwName()
{
	if (wsfile && IsGuiOnTop(MAINGUI_ID))
	{
          if(!wait)
          {
            int len=wstrlen(wsfile);                     // Сделал так. Старая версия пусть тоже живет как пример   AAA
           // short pos2=wstrrchr(fnamews,len,'.');
            pos+=tggl;
            if(pos==len-10||pos==0) {tggl*=-1; wait=10;}
          }else{
            wait--;
          }
            WSHDR* txt = AllocWS(256);
            wstrcpybypos(txt,wsfile,pos+1,pos+10);//pos2-pos-1);
           //  wstrcpybypos(txt,scfile,pos+1,pos2-pos-1);
            DrawRoundedFrame(2,70,100,70+GetFontYSIZE(SizeOfFont),0,0,1,0,GetPaletteAdrByColorIndex(1));
	    DrawString(txt,2,70,100,70+GetFontYSIZE(SizeOfFont),SizeOfFont,0,COLOR[0],0);
	    FreeWS(txt);
	}
	GBS_StartTimerProc(&sctm,15,DrwName);
}*/

// Нет функциям океренной величины!!   AAA
void PL_Redraw(WSHDR** mass, int* CurLine, int* MarkLine, int* MarkLines, unsigned int* AllLines, int CurList, int MarkList)
{
  unsigned short w = ScreenW();
  unsigned short my_x;
  unsigned short my_y;
  unsigned short k;
  unsigned short interval;
  short p2=0;
  short v3=1;
  unsigned short c = 0;  // Координаты  AAA
  int i;
 // char* str;
 // ID3TAGDATA *ShowTag;
  
  
  // Имя файла...
  if (AllLines[CurList]>0)
  {
    //---- Информация о воспроизводящемся файле (формат, канал, частота дискретизации), вывод закошен под AIMP, просьба не менять  - Vedan
    WSHDR * info_pf = AllocWS(32); 
    if(InfoOn)
  {
// Ддя информации
char chanel[8],
       freq[8],
     format[8];
//Определение Канала 
    if(*RamChannel()==0)strcpy(chanel," mono"); else strcpy(chanel," stereo");   
//Определение формата 
    switch (*RamFormatTrack())
    {
    case 0xA: strcpy(format,"MP3 ::"); break;
    case 0x8: strcpy(format,"WAV ::"); break;
    case 0x4: strcpy(format,"MID ::"); break;
    case 0x2: strcpy(format,"3GP ::"); break;
    default:  strcpy(format," - "); 
    }
//Определение частоты
    switch (*RamFreq())
    {
    case 0x4: strcpy(freq,", 22 kHz"); break;
    case 0x5: strcpy(freq,", 32 kHz"); break;
    case 0x7: strcpy(freq,", 44 kHz"); break;
    case 0x8: strcpy(freq,", 48 kHz"); break;
    default:  strcpy(freq," - "); 
    }
    //strcpy(format,null);
    //strcpy(freq,null);
    //strcpy(chanel,null);
    
    wsprintf(info_pf,"%t%t%t",format,chanel,freq); //Строка информации (фомат, канал, частота)
  }
  
    my_x = coord[7];
    my_y = coord[8];
    if(ALLTRACK) {interval=coord[6];}
    else {interval=0;}

    WSHDR * out_ws = AllocWS(128);
/*
    switch(CurrentTrack[CurrentPL])
    {
    case 1:
      k=0;
      break;
    case 2:
      k=1;
      break;
    case TC[CurrentPL]-2:
      k=3;
      break;
    case TC[CurrentPL]-1:
      k=4;
      break;
    case TC[CurrentPL]:
      k=5;
      break;
    case default:
      k=2;
      break;
    }
*/
    if (AllLines[CurList]>5)
    {
      switch(CurLine[CurList])
      {
      case 1:
        k=0;
        v3=0;
        break;
      case 2:
        k=1;
        v3=0;
        break;
      default:
        if(CurLine[CurList]==AllLines[CurList]-2) {k=3; v3=0;}
        else{ if(CurLine[CurList]==AllLines[CurList]-1) {k=4; v3=0;}
        else{ if(CurLine[CurList]==AllLines[CurList]) {k=5; v3=0;} else {k=2;}}}
        break;
      }
   /* if(CurLine[CurList]==1) {k=0; v3=0;}
    else{ if(CurLine[CurList]==2) {k=1; v3=0;}
    else{ if(CurLine[CurList]==AllLines[CurList]-2) {k=3; v3=0;}
    else{ if(CurLine[CurList]==AllLines[CurList]-1) {k=4; v3=0;}
    else{ if(CurLine[CurList]==AllLines[CurList]) {k=5; v3=0;} else {k=2;}}}}}*/
    }else{
      switch(CurLine[CurList])
      {
      case 1:
        k=0;
        v3=0;
        break;
      case 2:
        k=1;
        v3=0;
        break;
      case 3:
        k=2;
        v3=0;
        break;
      case 4:
        k=3;
        v3=0;
        break;
      case 5:
        k=4;
        v3=0;
        break;
      }
    }
    
    for(int l=0;l<6;l++)
    {
    i = CurLine[CurList]+l-k;
    if(AllLines[CurList]>l)
    {
      switch(ShowNamesNoConst)
      {
      case 0:// На будущее  AAA
       /* ShowTag=malloc(sizeof(ID3TAGDATA));
        str=malloc(256);
        ReadID3v1(GetTrackByNumber(i), ShowTag);
        
        if(strlen(ShowTag->artist)&&strlen(ShowTag->title))
        {
          sprintf(str,"%s - %s",ShowTag->artist,ShowTag->title);
          utf8_2ws(out_ws,str,strlen(str));
          
        }else{
          utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
        }
        mfree(ShowTag);
        mfree(str);*/
        break;
      case 1:
        wstrcpy(out_ws,GetTrackByNumber(mass, i));
       // utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
        break;
      case 2:
        FullpathToFilename(GetTrackByNumber(mass, i),out_ws);
        break;
      case 3:
        FullpathToFile(GetTrackByNumber(mass, i),out_ws);
        break;
      }
        /*
        if (SHOW_FULLNAMES)
        {
          utf8_2ws(out_ws,GetTrackByNumber(i),strlen(GetTrackByNumber(i)));
        
        }else{
        
        FullpathToFilename(GetTrackByNumber(i),out_ws);
        }*/
    if(k!=l)
    {
    // Делаем другой цвет для не текущего трека...
    if (MarkLine[CurList]==i||MarkLines[i]==1)
    {
      if(ALLTRACK) {DrawScrollString(out_ws,my_x+PL_move_L[l],my_y+c+(p2-p3*v)*v3,/*my_x+125*/w-7,my_y+GetFontYSIZE(SizeOfFont)+c+(p2-p3*v)*v3,
                                     1,SizeOfFont,0,COLOR[5],0);}
    }else{
      if(ALLTRACK) {DrawScrollString(out_ws,my_x+PL_move_L[l],my_y+c+(p2-p3*v)*v3,/*my_x+125*/w-7,my_y+GetFontYSIZE(SizeOfFont)+c+(p2-p3*v)*v3,
                                     1,SizeOfFont,0,COLOR[4],0);}
    }
    p2=0;
    }else{

      short v4=1;
      if(v3!=0) {v4=0;}
#ifndef NO_PNG
      char sfname[256];
      sprintf(sfname,p_3s,PIC_DIR,items1[12],PNGEXT);
      DrawImg(my_x-1+PL_move_L[l],my_y+c-3+p*v*v4,(int)sfname);
#else
      DrawRoundedFrame(my_x-1+PL_move_L[l],my_y+c-3+p*v*v4,my_x+127,my_y+coord[6]*2+c-3+p*v*v4,4,4,0,GetPaletteAdrByColorIndex(1),COLOR[2]);
#endif
      p2=-p1*v1;
      
    if (MarkLine[CurList]==CurLine[CurList]||MarkLines[CurLine[CurList]]==1)
    {
      if(GrafOn)
      {
          int i=Get_WS_width(out_ws,SizeOfFont);  //Определяет кол-во пикселей при этом шрифте (или что то вроде того...)
	  i-=(w-9);   //До куда докручивать
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
      }
      DrawScrollString(out_ws,my_x+PL_move_L[l],my_y+c-(p1*v2+p3*v1)*v3*v,/*my_x+125*/w-7,my_y+GetFontYSIZE(SizeOfFont)+c-(p1*v2+p3*v1)*v3*v,
                   scroll_disp+1,SizeOfFont,0,COLOR[5],0);
      if(InfoOn&&MarkLine&&p==0)
     {
        DrawString(info_pf,my_x+PL_move_L[l],my_y+c-(p1*v2+p3*v1)*v3*v+coord[6],/*my_x+125*/w-7,my_y+c-(p1*v2+p3*v1)*v3*v+coord[6]*2,SizeOfFont,0,COLOR[5],0);
     }
      
      
    }else{
	if(GrafOn)
        {
          int i=Get_WS_width(out_ws,SizeOfFont);
	  i-=(w-9);
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
        }
      DrawScrollString(out_ws,my_x+PL_move_L[l],my_y+c-(p1*v2+p3*v1)*v3*v,/*my_x+125*/w-7,my_y+GetFontYSIZE(SizeOfFont)+c-(p1*v2+p3*v1)*v3*v,
                  scroll_disp+1,SizeOfFont,0,COLOR[0],0);
      
    /*  wstrcpy(wsfile,out_ws);
      tggl=1;
      pos=0;
      GBS_StartTimerProc(&sctm,20,DrwName);
      */
    }
      if(s){
        if(s>1) {c+=interval;}
        else {c+=interval/4;}
      }else{
        c+=interval;
      }
    }
      if(s){
        if(c/interval>l&&s>l+2&&s>2) {c+=interval;}
        else {c+=interval/4;}
      }else{
        c+=interval;
      }
    }
    }
    if(n==0) {n=interval;}
    if(d==0) {d=2*interval;}
    FreeWS(out_ws);
    FreeWS(info_pf);
  }else{
    if(!FM_o) {LoadPlaylists(PLAYLISTS);}
  }
  // Плейлист
  WSHDR * pl_c = AllocWS(64);
  if(MarkLine){
  wsprintf(pl_c,"%i/%i/%i;%i/%i",CurLine[CurList],AllLines[CurList],CurList+1,MarkLine[MarkList],MarkList+1);
  }else{
  unsigned int nLines=0;
  for(unsigned int i=1; i<AllLines[CurList]+1; i++) {if(MarkLines[i]==1) {nLines++;}}
  wsprintf(pl_c,"%i/%i;%i(%i)",CurLine[CurList],AllLines[CurList],nLines,TC[CurrentPL]);
  }
  DrawString(pl_c,coord[13],coord[14],w,coord[14]+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,COLOR[1],0);
  FreeWS(pl_c);
  BandRoll(CurLine[CurList], AllLines[CurList]);
}

// Полоса прокрутки   AAA
void BandRoll(int CurLine, int AllLines)
{
  if(AllLines>6)
  {
    int yy=CurLine*(coord[2]-coord[1])/AllLines;
    DrawRoundedFrame(coord[0],coord[1],coord[0]+coord[3]-1,coord[2],0,0,0,0,COLOR[6]);
    DrawRoundedFrame(coord[4],coord[1]+yy-(coord[2]-coord[1])/AllLines,coord[4]+coord[5]-1,coord[1]+yy,0,0,0,0,COLOR[7]);
  }
}

// Чистим массив   AAA
//void NULLchar(char* p, unsigned int imax) {for(unsigned int i=0; i<imax+1; i++) {p[i]=0;}}  //{unsigned int i=0; while(p[i]!='\0') {p[i]=0; i++;} p[i]=0;}

// Загружаем пл!
int LoadPlaylist(const char * fn)  // Переделал. Нет утечкам и глюкам!    AAA
{
  FSTATS stat;
  unsigned int ul, i=0, j=0 ,k=0;
  int f, fsize;
  char *pp=malloc(256);
  zeromem(pp,256);
  char *p;

  if (GetFileStats(fn,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;

  p=malloc(fsize+1);
  fread(f,p,fsize,&ul);
  fclose(f,&ul);
  while(i<fsize)
  {
    if(p[i]!=0x0D&&p[i+1]!=0x0A) {pp[j++]=p[i];}
    else
    {
      fix(pp);
      if(pp[0]!='#')
      {
        WSHDR* ppp=AllocWS(256);
        utf8_2ws(ppp,pp,strlen(pp));
        PastLine(ppp, 0);
        FreeWS(ppp);
        ppp=NULL;
        k++;
      }
      i++;
      j=0;
      zeromem(pp,256);
    }
    i++;
  }
  /*if(p)*/mfree(p);
  /*if(pp)*/mfree(pp);
  return k;
}

// Для загрузки пл из главного модуля
void LoadingPlaylist(const char * fn)
{
  /*  if(TC[CurrentPL]>0)
    {
      MsgBoxYesNo(1,(int)"Заменить?",Change);
      if(change)
      {
        CTtoFirst();
        PTtoFirst();
        while(TC[CurrentPL]>0)
        {
          DeleteLine();
        }
      }
    }else{
      CTtoFirst();
    }*/
  CTtoFirst();
  PTtoFirst();
  CleanPlaylist();
  
  unsigned int err;
  if(isdir(fn,&err)) {void LoadDaemonList(const char* path, unsigned short re, unsigned short toPL); LoadDaemonList(fn, 1, 1);}
  else LoadPlaylist(fn);
  
  if(SAVE_SETS)strcpy(Playlists[CurrentPL],fn);
  ready[CurrentPL]=1;
}

// Чистим пл   AAA
void CleanPlaylist()
{
  while(TC[CurrentPL]>0)
        {
          DeleteLine();
        }
}

//LoadDaemonList(" 4:\\Doc\\");
void LoadPlaylists(const char* path) // Для еще одной фичи   AAA
{
  DIR_ENTRY de;
  unsigned int err;
  char name[256];
  strcpy(name,path);
  strcat(name,"*");
  if(FindFirstFile(&de,name,&err))
  {
    do
    {
      char* p1=malloc(256);
      WSHDR* p=AllocWS(256);
      strcpy(name,path);
      strcat(name,de.file_name);
      
      if (!isdir(name, &err))//(de.file_attr&FA_DIRECTORY)
      {
        if(IsExt(1, de.file_name))  // Перерываем форматы   AAA
        {
          strcpy(p1,name);
          fix(p1);
          utf8_2ws(p,p1,256);
          PastLine(p, 0);
        }
      }
      else
      {
        strcat(name,"\\"); LoadPlaylists(name);
      }
      FreeWS(p);
      mfree(p1);
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  if(TC[CurrentPL]>0) {CTtoFirst(); PTtoFirst();}
  if(SAVE_SETS)zeromem(Playlists[CurrentPL],256);
  ready[CurrentPL]=0;
}

// Эта зверюга замочит что угодно!   AAA
void Disable_An(unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4, unsigned short i5, unsigned short i6/*, unsigned short i7*/)
{
  if(i1)DisableScroll();
  if(i2)StopRewind();
  if(i3)Disable_OpenAnim();
  if(i4)Disable_PL_mp();
  if(i5)Disable_PL();
  if(i6)Disable_CTSpeed();
  /*if(i7)StopAllPlayback();*/    // Че т шикарно через чур :D но если сильно потребуется...
}

// Утечка памяти в самом деле достала...   AAA
void MemoryFree()
{
  GBS_DelTimer(&tmr_scroll);
  GBS_DelTimer(&tmr_displacement);
  GBS_DelTimer(&tmr_cursor_move);
  GBS_DelTimer(&tmr_pl_move);
  GBS_DelTimer(&tmr_opan);
 // FreeWS(wsfile);
  FreePlaylist();
}
