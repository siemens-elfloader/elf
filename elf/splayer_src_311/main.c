#include "../inc/swilib.h"
#include "../inc/cfg_items.h"
#include "../inc/stdbool.h"
#include "../inc/playsound.h"
#include "../inc/obs.h"
#include "conf_loader.h"
#include "main.h"
#include "mainmenu.h"
#include "sets_menu.h"
#include "playlist.h"
#include "lang.h"
#include "langpack.h"
#include "SPlayer_ipc.h"
#include "mylib.h" 
#include "../inc/xtask_ipc.h"

/*
typedef struct {
 unsigned short type; //00 
 WSHDR *wfilename; //04 
 int unk_08 ; //08 
 int unk_0C; //0C 
 int unk_10 ; //10 
 int unk_14 ; //14 
 long length; //18 <-- return 
 int unk_1C; //1C 
 int unk_20 ; //20 
} TWavLen;*/

#pragma swi_number=0x45 
#ifdef NEWSGOLD 
__swi __arm int GetWavLen(char *filename); 
#else 
__swi __arm int GetWavLen(TWavLen *wl);
#endif

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

void Log(int dummy, char *txt)
{
  unsigned int ul;
  int f=fopen("0:\\SPlayer.log",A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,txt,strlen(txt),&ul);
  }
  fclose(f,&ul);
}

const int minus11=-11; // стремная константа =)

unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

//IPC   AAA
const char ipc_my_name[32]=IPC_SPLAYER_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
const char ipc_grantee_name[]=IPC_GRANTEE_NAME;
const char ipc_control_name[]=IPC_CONTROL_NAME;
const char ipc_editor_name[]=IPC_EDITOR_NAME;
IPC_REQ gipc;

WSHDR* SPerrs;

extern short ModeRew;
extern short ModeMove;
extern short SpeedMove;
extern bool stop; // 1, если останавливаем листание   AAA
bool copy=0; // 1, если копируем   AAA
bool move=0; // 1, если перемещаем   AAA
bool EditPL=0; // 1, если редактируем   AAA
bool mode=0; // 1, если длинное нажатие боковой клавиши
bool KeyLock=0; // 1, если заблокирована;
unsigned short Stat_keypressed = 0; // нажата ли клавиша изменения статуса?
unsigned short Mode_keypressed = 0; // нажата ли клавиша изменения режима проигрывания?
unsigned short N_keypressed = 0;
unsigned short P_keypressed = 0;
bool IPC_COPY=0;          // Открыли копию или нет?    AAA

///////////////////////////////////////////////////////////////////////////////
unsigned short coord[ncoord];
char COLOR[ncolor][4];

/*
//--- Собственно, переменные координат AAA ---
unsigned short VOLmy_x;
unsigned short VOLmy_y;
unsigned short STATmy_x;
unsigned short STATmy_y;
unsigned short CTmy_x;  // Координаты CurrentTrack
unsigned short CTmy_y;
unsigned short s;     // Смещение по вертикали
unsigned short NUMmy_x;
unsigned short NUMmy_y;
unsigned short RANDmy_x;
unsigned short RANDmy_y;
unsigned short KeyLock_x;
unsigned short KeyLock_y;
unsigned short Next_x;
unsigned short Next_y;
unsigned short Prev_x;
unsigned short Prev_y;
// Полоса прокрутки
extern unsigned short BR_x;
extern unsigned short BR1_y;
extern unsigned short BR2_y;
extern unsigned short BR_w;
extern unsigned short BRC_x;
extern unsigned short BRC_w;
// Время
unsigned short time_x;
unsigned short time_y;
// Длительность
unsigned short length_x;
unsigned short length_y;
// Прогрессбар
unsigned short progress_x;
unsigned short progress_y;
unsigned short progress_x2;
unsigned short progress_y2;

//--- Собственно, переменные координат AAA ---

//--- Цвета AAA ---
char COLOR_TEXT[4];
char LINE_COLOR[4];
char COLOR_BG[4];
char COLOR_BG_CURSOR[4];
char COLOR_TEXT_CURSOR[4];
char COLOR_TEXT_PLAY[4];
char COLOR_BANDROLL[4];
char COLOR_BANDROLL_C[4];
char COLOR_PROG_BG[4];               // Фон прогрессбара
char COLOR_PROG_BG_FRAME[4];               // Ободок
char COLOR_PROG_MAIN[4];             // Сам прогресс
char COLOR_PROG_MAIN_FRAME[4];             // Ободок
//--- Цвета AAA ---
*/
/////////////////////////////////////////////////////////////////////////////////

//--- настройки из конфига ---
extern const char PIC_DIR[];
extern const char PLAYLISTS[];
extern const char SETS_PATH[];
extern const char DEFAULT_PLAYLIST[];
extern const char DEFAULT_PLAYLIST1[];
extern const char DEFAULT_PLAYLIST2[];
extern const unsigned int IDLE_X;
extern const unsigned int IDLE_Y;
extern const unsigned int SHOW_NAMES;
extern const unsigned int PlayMode;
extern const unsigned int soundvolume;
extern const unsigned int SizeOfFont;  // Шрифт   AAA
extern const unsigned int FnameIPC;    // Отправлять или нет   AAA
extern const unsigned int AUTO_EXIT_MIN;  // Время до автозакрытия   AAA
extern const unsigned int SHOW_POPUP;
extern const unsigned int SAVE_SETS;
//--- настройки из конфига ---

//--- Переменные ---
extern WSHDR *playlist_lines[TCPL][512];
char *Playlists[TCPL];
extern short phandle;  // Для определения конца воспр.  AAA
#ifdef OBS
HObj gObj=NULL;
#else
void* pha;               // Для Obs   AAA
#endif
extern unsigned short PlayingStatus;
extern int CurrentPL;
extern int PlayedPL;
extern unsigned int TC[TCPL];
extern int CurrentTrack[TCPL];
extern int PlayedTrack[TCPL];
char Quit_Required = 0;     // Флаг необходимости завершить работу
char list[256];
char sfname[256];
extern unsigned short SoundVolume;
unsigned short playmode;     // 0 - играем все, 1 - повторить все, 2 - перемешать, 3 - повторять один  AAA
extern unsigned short ShowNamesNoConst;
const char p_w[]="%w";
const char p_2s[]="%s%s";
const char p_3s[]="%s%s%s";
const char p_4s[]="%s%s%s%s";
#ifndef NO_PNG
bool pngloadcomp=0;
unsigned short Npng=0;
#else
bool pngloadcomp=1;
#endif

GBSTMR offtm;     // Таймер автоотключения   AAA       удаляется при остановке
GBSTMR lvtm;      // Длительность/громкость правим   AAA         удаляется после запуска

// Переписываем время... DemonGloom
TWavLen wl;
GBSTMR mytmr;
// Сделал иначе   AAA
int tm=0;    // Время
int ln=0;    // Длительность
bool tm_er=0;// Случился посторонний звук или нет

//--- Переменные ---

void UpdateCSMname(WSHDR * tname);

//--- Инициализация ленгпака --- Vedan
char *lgpData[LGP_DATA_NUM];
int lgpLoaded;


void initSetsMenuLangPack();
void initItemInfoLangPack();
void initMainMenuLangPack();

void InitLangPack()
{
        initItemInfoLangPack();
        initSetsMenuLangPack();
        initMainMenuLangPack();
}


void lgpInitLangPack(void)
{
  extern const char LANGFILE[128];
  unsigned int err=NULL;
  int f;
  
  for (int i = 0; i < LGP_DATA_NUM; i ++)
    lgpData[i] = NULL;
  lgpLoaded=0;
  
  char * buf;
  FSTATS fstat;
  if (GetFileStats(LANGFILE, &fstat, &err)!=-1)
  {
    if((f=fopen(LANGFILE, A_ReadOnly + A_BIN, P_READ, &err))!=-1)
    {
      if (buf =(char *)malloc(fstat.size+1))
      {
        buf[fread(f, buf, fstat.size, &err)]=NULL;
        fclose(f, &err);
        char line[128];
        int lineSize=NULL;
        int lp_id=NULL;
        int buf_pos = NULL;
        while(buf[buf_pos] && buf_pos < fstat.size && lp_id < LGP_DATA_NUM)
        {
          if (buf[buf_pos]=='\n' || buf[buf_pos]=='\r')
          {
            if (lineSize > 0)
            {
              lgpData[lp_id] = (char *)malloc(lineSize+1);
              memcpy(lgpData[lp_id], line, lineSize);
              lgpData[lp_id][lineSize]=NULL;
              lp_id++;
              lineSize=NULL;
            }
          }
          else
            line[lineSize++]=buf[buf_pos];
          buf_pos++;
        }
        if (lineSize > 0 && lp_id < LGP_DATA_NUM) // eof
        {
          lgpData[lp_id] = (char *)malloc(lineSize+1);
          memcpy(lgpData[lp_id], line, lineSize);
          lgpData[lp_id][lineSize]=NULL;
          lp_id++;
          lineSize=NULL;
        }
        mfree(buf);
        InitLangPack();
        lgpLoaded=1;
        
        // old langpack
        if (strlen(lgpData[LGP_LangCode])>2)
        {
          mfree(lgpData[LGP_LangCode]);
          lgpData[LGP_LangCode]=(char *)malloc(3);
          strcpy(lgpData[LGP_LangCode],"ru");
        }
        for (int i = 0; i < LGP_DATA_NUM; i ++)
        {
          if (!lgpData[i])
          {
            lgpData[i] = (char *)malloc(32);
            strcpy(lgpData[i], "Error! Update lang.txt!");
          }
        }
        return;
      }
      fclose(f, &err);
    }
  }
  ///////////MainMenu///////////
  lgpData[LGP_Menu]=                 "Menu";
  lgpData[LGP_SetNextPlayed]=        "SetNextTrack";
  lgpData[LGP_ShowID3]=              "ShowID3";
  lgpData[LGP_FM]=                   "FileManager";
  lgpData[LGP_Settings]=             "Settings";
  lgpData[LGP_AboutDlg]=             "AboutDlg";
  lgpData[LGP_Exit_SPlayer]=         "Exit";
  lgpData[LGP_SELECT]=               "Select";
  lgpData[LGP_BACK]=                 "Back";
  ///////////Menu 1///////////
  lgpData[LGP_Sets_Menu]=            "Instruments";
  lgpData[LGP_SetEditPL]=            "EditPList";
  lgpData[LGP_Coordinates]=          "Coordinates";
  lgpData[LGP_Colours]=              "Colours";
  lgpData[LGP_Refresh]=              "Refresh";
  ///////////Attributes///////////
  lgpData[LGP_ID3_Tag_Info]=         "ID3_Tag_Info";
  lgpData[LGP_Full_name]=            "Full_name";
  lgpData[LGP_Size]=                 "Size";
  lgpData[LGP_Title]=                "Title";
  lgpData[LGP_Artist]=               "Artist";
  lgpData[LGP_Album]=                "Album";
  lgpData[LGP_Year]=                 "Year";
  lgpData[LGP_Comment]=              "Comment";
  lgpData[LGP_Number]=               "Number";
  lgpData[LGP_Genre]=                "Genre";
  ///////////Config///////////
  ///////////ShowMSG/MsgBoxError///////////
  lgpData[LGP_Can_not_find_file]=    "Can not find file!";
  lgpData[LGP_Load_a_playlist]=      "Load a playlist!";
  lgpData[LGP_Keypad_Unlock]=        "Keypad Unlock";
  lgpData[LGP_Keypad_Lock]=          "Keypad Lock";
  lgpData[LGP_Config_Updated]=       "SPlayer Config Updated!";
  lgpData[LGP_PL_Saved]=             "PlayList Saved!";
  lgpData[LGP_Exit]=                 "Exit?";
  lgpData[LGP_Is_not_selected]=      "Is not selected!";
  lgpData[LGP_No_Tags]=              "No Tags!";
  lgpData[LGP_Already_Started]=      "Already Started!";
  lgpData[LGP_Error_1]=              "Error_1!";
  lgpData[LGP_Error_2]=              "Error_2!";
  lgpData[LGP_Spkeys_er]=            "Spkeys error!";
  lgpData[LGP_PNG_er]=               " png-files are absent. It can reduce speed of work";
  lgpData[LGP_eoPL]=                 "Playlist is overflown!";
  lgpData[LGP_Error_cfg_file]=       "Error of cfg-file!";
  lgpData[LGP_No_cfg_file]=          "No cfg-file!";
  lgpData[LGP_LangCode]=             "en";
  InitLangPack();
}

void lgpFreeLangPack(void)
{
  if (!lgpLoaded) return;
  for (int i=0;i<LGP_DATA_NUM;i++)
  {
    if (lgpData[i])
      mfree(lgpData[i]);
  }
}

void InitLanguage()
{
  lgpFreeLangPack();
  lgpInitLangPack();
}
//---------------------------------------------

// Избавляемся от тормозов   AAA
void LoadPng()
{
#ifndef NO_PNG
  unsigned int err;
  FSTATS fstat;
  unsigned int i;
  unsigned int l=0;
  sprintf(sfname,p_3s,PIC_DIR,items1[15],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  Npng++;
  sprintf(sfname,p_3s,PIC_DIR,items1[0],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  else{DrawImg(0,0,(int)sfname);}
  Npng++;
  sprintf(sfname,p_3s,PIC_DIR,items1[12],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  else{DrawImg(0,0,(int)sfname);}
  Npng++;
  sprintf(sfname,p_3s,PIC_DIR,items1[1],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  else{DrawImg(0,0,(int)sfname);}
  Npng++;REDRAW();
  sprintf(sfname,"%s%s1%s",PIC_DIR,items1[1],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  else{DrawImg(0,0,(int)sfname);}
  Npng++;
  
  for(i=0; i<TOTAL_ITEMS; i++)
  {
    sprintf(sfname,p_3s,PIC_DIR,items[i],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;REDRAW();
  }
  for(i=0; i<TOTAL_ITEMS_2; i++)
  {
    sprintf(sfname,p_3s,PIC_DIR,items2[i],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;REDRAW();
  }
  for(i=2; i<5; i++)
  {
    sprintf(sfname,p_3s,PIC_DIR,items1[i],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;
    sprintf(sfname,p_4s,PIC_DIR,items1[i],items1[13],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;
    sprintf(sfname,p_4s,PIC_DIR,items1[i],items1[14],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;REDRAW();
  }
  for(i=5; i<9; i++)
  {
    sprintf(sfname,p_3s,PIC_DIR,items1[i],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;
    sprintf(sfname,p_4s,PIC_DIR,items1[i],items1[13],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;REDRAW();
  }
  for(i=9;i<11;i++)
  {
    sprintf(sfname,p_4s,PIC_DIR,items1[i],items1[13],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;
    sprintf(sfname,p_3s,PIC_DIR,items1[i],PNGEXT);
    if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
    else{DrawImg(0,0,(int)sfname);}
    Npng++;REDRAW();
  }
  sprintf(sfname,p_3s,PIC_DIR,items1[11],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  else{DrawImg(0,0,(int)sfname);}
  Npng++;
  sprintf(sfname,p_3s,PIC_DIR,items1[16],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  else{DrawImg(0,0,(int)sfname);}
  Npng++;
  sprintf(sfname,p_3s,PIC_DIR,items1[17],PNGEXT);
  if (GetFileStats(sfname, &fstat, &err)==-1) {l++;}
  else{DrawImg(0,0,(int)sfname);}
  Npng++;
  pngloadcomp=1;
  REDRAW();
  if(l){
  sprintf(sfname,"%d%s",l,lgpData[LGP_PNG_er]);
  if(SHOW_POPUP) ShowMSG(1,(int)sfname);}
#endif
}


// Отсчет времени. Теперь по-моему и вроде без глюков+приведено к общему виду для удобства использования   AAA
unsigned short sttmr=0;  // Почему-то неверно начинал счет   AAA
void EXT_REDRAW()
{
  if(IsGuiOnTop(MAINGUI_ID)) REDRAW();
 // GetPlayObjPosition((void*)gObj,&tm);   // Лагает   AAA
 // tm/=1000;
  if(tm||sttmr) {tm++;}
  else {sttmr=1;}
  GBS_StartTimerProc(&mytmr,216,EXT_REDRAW);
}

void StopTMR(unsigned short s)
{
  GBS_DelTimer(&mytmr);
  if(s) {tm=0; ln=0; sttmr=0;}
}

int findmp3length(char *playy) { 
  #ifdef NEWSGOLD 
  return ((GetWavLen(playy))/1000); 
  #else
  TWavLen wl;
  zeromem(&wl, sizeof(wl));
  wl.type=0x2000;
  wl.wfilename=AllocWS(128);
  str_2ws(wl.wfilename,playy,128); 
  GetWavLen(&wl); 
  return (wl.length/1000);
  #endif 
}
/*
unsigned short setdur=0, time_refr=40;
void SetDV()
{
  switch(setdur){
  case 0:
    setdur=1;
    pha=GetPlayObjById(phandle);
    GBS_StartTimerProc(&lvtm,time_refr,SetDV);
    break;
  case 1:
    setdur=2;
    GetPlayObjDuration((( int**)pha)[0x3d0/4], &ln);
    ln/=1000;
    GBS_StartTimerProc(&lvtm,time_refr,SetDV);
    break;
  case 2:
    setdur=0;
    Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], SoundVolume, 1);
    time_refr+=30;
    if(time_refr<200&&!ln)GBS_StartTimerProc(&lvtm,time_refr,SetDV);
    else GBS_DelTimer(&lvtm);
    break;
  }
}*/
#ifdef OBS
#define MSG_Report  0xB034
void KillObj(){
 if (!gObj) return;
  Obs_DestroyObject(gObj);
  gObj=NULL;
}
#endif

// Играем MP3 файл
void PlayMP3File(WSHDR * fname)
{
if(TC[PlayedPL]>0)            // Теперь не рубится при отсутствии загруженного пл   AAA
{
  if (!IsCalling()) // Нет ли звонка
  {
    FSTATS fstats;
    unsigned int err;

    char * fnamech=malloc(256);
    ws_2str(fname,fnamech,256);
    if (GetFileStats(fnamech,&fstats,&err)!=-1) // Проверка файла на существование
    {
      StopTMR(1);
     // EXT_REDRAW();
      WSHDR* sndFName=AllocWS(128);
      const char *p=strrchr(fnamech,'\\')+1;
      str_2ws(sndFName,p,128);
#ifdef OBS
      unsigned int err=0;
      KillObj();
      WSHDR *ext;

      char *extch;
      int uid;
      short pos;
      int len;
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
      wsprintf(ext,"%t",extch);
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
      Obs_Sound_SetVolumeEx(gObj, SoundVolume, 1);
      Obs_Prepare(gObj);
     // Obs_Start(gObj);
     // EXT_REDRAW();
      
  goto exit0;
 
exit1:
 // ShowMSG(1,(int)"ЫЫЫЫ");
  Obs_DestroyObject(gObj);
  gObj=NULL;
exit0:
#else
      PLAYFILE_OPT pfopt;
      WSHDR* sndPath=AllocWS(128);
      
      char s[128];
      
    //  short p=wstrrchr(fname,wstrlen(fname),'\\')+1;
    //  wstrncpy(sndFName,fname,p);
    //  wstrncpy(sndPath,fname,p-strlen(fname));
      
      const char *p1=strrchr(fnamech,'\\')+1;
      strncpy(s,fnamech,p1-fnamech);
      s[p1-fnamech]='\0';
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
      SetPHandle(PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt)); // Вместо 0xC было 0x10 ... Пробуйте так!!
#else 
      pfopt.unk4=0x80000000;
      pfopt.unk5=1;
      SetPHandle(PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &pfopt));
      char *pp=strrchr(fnamech,':')-1;
      ln=findmp3length(pp);
#endif
#endif
      
      SetPlayingStatus(2);
      UpdateCSMname(sndFName); // Покажем что играем XTask Blind007
      // Покажем что играем тем кому нужно :)))   AAA
      if(FnameIPC)
      {
        // Вылавливаем имя трека   AAA
        if(FnameIPC==2)
        {
          char *trackname=malloc(256);
          ID3TAGDATA *StatTag;
          StatTag=malloc(sizeof(ID3TAGDATA));
          ReadID3v1(GetPlayedTrack(PlayedTrack[PlayedPL]), StatTag);
          if(strlen(StatTag->artist)&&strlen(StatTag->title)) {sprintf(trackname,"%s - %s",StatTag->artist,StatTag->title);}
          mfree(StatTag);
          
          //ShowMSG(1,(int));
          
          WSHDR *ws1 = AllocWS(strlen(trackname) + 1);
          wsprintf(ws1, "%t", trackname);
          
          char *name = malloc(wstrlen(ws1) * 2 + 1);
          int len;
          ws_2utf8(ws1, name, &len, wstrlen(ws1) * 2 + 1);
          name[strlen(name)]='\0';
          
          gipc.name_to=ipc_grantee_name;
          gipc.name_from=ipc_my_name;
          gipc.data=(void*)name;
          GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc);
          
          mfree(name);
          FreeWS(ws1);
          mfree(trackname);
        }else{
          WSHDR * ws1=AllocWS(128);
          FullpathToFilename(fname, ws1);
          
          char *name = malloc(wstrlen(ws1) * 2 + 1);
          int len;
          ws_2utf8(ws1, name, &len, wstrlen(ws1) * 2 + 1);
          name[strlen(name)]='\0';
        //  ShowMSG(1,(int));
          
          gipc.name_to=ipc_grantee_name;
          gipc.name_from=ipc_my_name;
          gipc.data=(void*)name;
          GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc);
          
          FreeWS(ws1);
          mfree(name);
        }
      }
//      BeginTime = SetBeginTime(); // Время начала играния файла Blind007
     // FreeWS(sndPath);
      FreeWS(sndFName);
    } else {
      // Если нет такого файла!
      if(IsUnlocked()){
      if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Can_not_find_file]);
      ToDevelop();}
      NextTrackX();
    }
    mfree(fnamech);
  }
}
else
{
  if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Load_a_playlist]);
}
}

// Грузим координаты из skin.cfg AAA
void load_skin(char const * fname)              // Извращенец... Такое создать... DG
{
  unsigned short i=0, j=0, k=0, num=3;
  char *data, *pp; 
  unsigned int err;
  int handle, fsize;
  FSTATS fstats;
  if (GetFileStats(fname,&fstats,&err)!=-1) // Проверка файла на существование
  {
    fsize=fstats.size;
    handle=fopen(fname, A_ReadOnly, P_READ,&err); // x65-75 for read MMC instead P_READ - 0
    if(handle!=-1)
    {
      data=malloc(fsize);
      if(data)
      {
        fread(handle,data,fsize,&err); // Экономим память! :)  Пошли вы куда подальше... Сами же забываете добавлять!!! DG
        switch(data[2])
        {
        case 0x01:
          coord[0]=data[3];
          coord[1]=data[4]+data[5];
          coord[2]=data[6]+data[7];
          coord[3]=data[8];
          coord[4]=data[9];
          coord[5]=data[10];
          // Полоса прокрутки
          coord[6]=data[11];
          i=7;
          j=12;
          while(1)
          {
            coord[i++]=data[j++];
            coord[i++]=data[j]+data[j+1];
            j+=2;
            if(i==ncoord)break;
          }
          break;
        case 0x02:
          for(i=0;i<ncolor;i++)
          {
            for(j=0;j<4;j++)
            {
              COLOR[i][j]=data[num++];
            }
          }
          break;
        case 0x03:
          CurrentPL=data[3];
          CurrentTrack[CurrentPL]=data[4]*100+data[5];
          PlayedPL=data[6];
          PlayedTrack[PlayedPL]=data[7]*100+data[8];
         // tm=data[9]*60+data[10];
          SoundVolume=data[11];
          playmode=data[12];
          break;
        case 0x04:
          pp=malloc(256);
          zeromem(pp,256);
          i=3;
          while(i<fsize)
          {
            if(data[i]!=0x0D&&data[i+1]!=0x0A) {pp[j++]=data[i];}
            else
            {
             // fix(pp);
              if(strlen(pp)>2)strcpy(Playlists[k],pp);
              else zeromem(Playlists[k],256);
              k++;
              i++;
              j=0;
              zeromem(pp,256);
            }
            if(k==5)break;
            i++;
          }
          mfree(pp);
          break;
        default:
          WriteSPerr(SPerr1);
          if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Error_cfg_file]);
          break;
        }
      }
      mfree(data);
    }
    fclose(handle,&err);
  }
  else
  {
    WriteSPerr(SPerr2);
    if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_No_cfg_file]);
  }
}

/*
// Грузим координаты из skin.cfg AAA
void load_skin(char const* cfgname)              // Извращенец... Такое создать... DG
{
  char *data; 
  unsigned int err; 
  int handle; 
  handle=fopen(cfgname, A_ReadOnly, P_READ,&err); 
  if(handle!=-1)
  {
    data=malloc(0xFF);
    if(data!=0)
      {
        fread(handle,data,0xFF,&err); // Экономим память! :)  Пошли вы куда подальше... Сами же забываете добавлять!!! DG
        if(data[2]==0x01)
        {
        // Полоса прокрутки
        BR_x=data[3];
        BR1_y=data[4]+data[5];
        BR2_y=data[6]+data[7];
        BR_w=data[8];
        BRC_x=data[9];
        BRC_w=data[10];
        // Полоса прокрутки
        s=data[11];
        CTmy_x=data[12];
        CTmy_y=data[13]+data[14];
        VOLmy_x=data[15];
        VOLmy_y=data[16]+data[17];
        STATmy_x=data[18];
        STATmy_y=data[19]+data[20];
        NUMmy_x=data[21];
        NUMmy_y=data[22]+data[23];
        RANDmy_x=data[24];
        RANDmy_y=data[25]+data[26];
        KeyLock_x=data[27];
        KeyLock_y=data[28]+data[29];
        Next_x=data[30];
        Next_y=data[31]+data[32];
        Prev_x=data[33];
        Prev_y=data[34]+data[35];
        // Время
        time_x=data[36];
        time_y=data[37]+data[38];
        // Длительность песни
        length_x=data[39];
        length_y=data[40]+data[41];
        // Прогрессбар
        progress_x=data[42];
        progress_y=data[43]+data[44];
        progress_x2=data[45];
        progress_y2=data[46]+data[47];
        }
        else
        {
          COLOR_TEXT[0]=data[3];
          COLOR_TEXT[1]=data[4];
          COLOR_TEXT[2]=data[5];
          COLOR_TEXT[3]=data[6];
          LINE_COLOR[0]=data[7];
          LINE_COLOR[1]=data[8];
          LINE_COLOR[2]=data[9];
          LINE_COLOR[3]=data[10];
          COLOR_BG[0]=data[11];
          COLOR_BG[1]=data[12];
          COLOR_BG[2]=data[13];
          COLOR_BG[3]=data[14];
          COLOR_BG_CURSOR[0]=data[15];
          COLOR_BG_CURSOR[1]=data[16];
          COLOR_BG_CURSOR[2]=data[17];
          COLOR_BG_CURSOR[3]=data[18];
          COLOR_TEXT_CURSOR[0]=data[19];
          COLOR_TEXT_CURSOR[1]=data[20];
          COLOR_TEXT_CURSOR[2]=data[21];
          COLOR_TEXT_CURSOR[3]=data[22];
          COLOR_TEXT_PLAY[0]=data[23];
          COLOR_TEXT_PLAY[1]=data[24];
          COLOR_TEXT_PLAY[2]=data[25];
          COLOR_TEXT_PLAY[3]=data[26];
          COLOR_BANDROLL[0]=data[27];
          COLOR_BANDROLL[1]=data[28];
          COLOR_BANDROLL[2]=data[29];
          COLOR_BANDROLL[3]=data[30];
          COLOR_BANDROLL_C[0]=data[31];
          COLOR_BANDROLL_C[1]=data[32];
          COLOR_BANDROLL_C[2]=data[33];
          COLOR_BANDROLL_C[3]=data[34];
          
          COLOR_PROG_BG[0]=data[35];
          COLOR_PROG_BG[1]=data[36];
          COLOR_PROG_BG[2]=data[37];
          COLOR_PROG_BG[3]=data[38];
          COLOR_PROG_BG_FRAME[0]=data[39];
          COLOR_PROG_BG_FRAME[1]=data[40];
          COLOR_PROG_BG_FRAME[2]=data[41];
          COLOR_PROG_BG_FRAME[3]=data[42];
          COLOR_PROG_MAIN[0]=data[43];
          COLOR_PROG_MAIN[1]=data[44];
          COLOR_PROG_MAIN[2]=data[45];
          COLOR_PROG_MAIN[3]=data[46];
          COLOR_PROG_MAIN_FRAME[0]=data[47];
          COLOR_PROG_MAIN_FRAME[1]=data[48];
          COLOR_PROG_MAIN_FRAME[2]=data[49];
          COLOR_PROG_MAIN_FRAME[3]=data[50];
        }
      }
    mfree(data);
    fclose(handle,&err);
  }
}
*/

// Сохраняем координаты в skin.cfg AAA
void save_sets(char const * fname, unsigned short rd)
{
  char *data;
  unsigned int err;
  int handle;
  handle=fopen(fname,A_ReadWrite+A_Create+A_BIN,P_READ+P_WRITE,&err);  //+A_Create создать если нет||+A_BIN в двойчном коде||+A_Append дописать в конец||+A_Truncate хз
  if(handle!=-1)
  {
    if(rd)
    {
      data=malloc(13);
      if(data)
      {
        data[2]=0x03;
        data[3]=CurrentPL;
        data[4]=CurrentTrack[CurrentPL]/100;
        data[5]=CurrentTrack[CurrentPL]%100;
        data[6]=PlayedPL;
        data[7]=PlayedTrack[PlayedPL]/100;
        data[8]=PlayedTrack[PlayedPL]%100;
        data[9]=tm/60;
        data[10]=tm%60;
        data[11]=SoundVolume;
        data[12]=playmode;
        
        fwrite(handle,data,13,&err);
      }
      mfree(data);
    }else{
      char s[]={0x0D,0x0A};
      char p[]={0x00,0x00,0x04};
      fwrite(handle,p,3,&err);
      for (unsigned int i=0;i<TCPL;i++)
      {
        if(Playlists[i])fwrite(handle,Playlists[i],strlen(Playlists[i]),&err);
        fwrite(handle,s,2,&err);
      }
    }
  }
  fclose(handle,&err);
}

void SendNULL()   // Послать по окончании воспр.   AAA
{
    if(FnameIPC)
      {
        gipc.name_to=ipc_grantee_name;
        gipc.name_from=ipc_my_name;
        gipc.data=NULL;
        GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc);
      }
}

void ToDevelop()   // Развернуть   AAA
{
  if(!IsGuiOnTop(MAINGUI_ID))
  {
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)MAINCSM_ID;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
  }
}

void CheckDoubleRun(void)   // При открытии копии   AAA
{
  int csm_id;
  if ((csm_id=(int)(gipc.data))!=-1)
  {
    IPC_COPY=1;
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)csm_id;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
    LockSched();
    CloseCSM(MAINCSM_ID);
    if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Already_Started]);
    UnlockSched();
  }
  else
  {
    gipc.name_to=ipc_grantee_name;
    gipc.name_from=ipc_my_name;
    gipc.data=NULL;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SPLAYER_STARTED,&gipc);   // Это чтобы всех послать :) , при открытии копии не посылает   AAA
    
    SUBPROC((void*)LoadPng); // Загрузка пнг   AAA
    ToDevelop();             // Чтобы не вызывался в фон при установленном патче на вызов SPlayer'a по горячей клавише   AAA
  }
}

void Refresh()
{
  char cfgname[256];
  sprintf(cfgname,"%s%s",PIC_DIR,"skin.cfg");
  load_skin(cfgname);
  sprintf(cfgname,"%s%s",PIC_DIR,"colour.cfg");
  load_skin(cfgname);
}

void WriteSPerr(char* err)
{
  if(wstrlen(SPerrs)) wsprintf(SPerrs,"%w, %t",SPerrs,err);
  else {
    SPerrs=AllocWS(128);
    wsprintf(SPerrs,"%t %t","Error:",err);
  }
}

void ShowLongTXT(unsigned short scr, unsigned short left, unsigned short top, unsigned short w)
{
  if(wstrlen(SPerrs))
  {
    unsigned short wi=left+Get_WS_width(SPerrs,FONT_SMALL);
    DrawScrollString(SPerrs,left,top+scr/w*GetFontYSIZE(FONT_SMALL),w,top+(scr/w+1)*GetFontYSIZE(FONT_SMALL),scr+1,FONT_SMALL,0,GetPaletteAdrByColorIndex(2),0);
    if(wi-scr>w)
    {
      scr+=w;
      ShowLongTXT(scr, left, top, w);
    }
  }
}
//////////////Автовыход   AAA//////////////
int AutoExitCounter;

void ResetAutoExit() 
{
  AutoExitCounter=0;
}

void AutoExit()
{
  if(AUTO_EXIT_MIN) {AutoExitCounter++; GBS_StartTimerProc(&offtm, 216 * 15, AutoExit);
  if(AutoExitCounter*15>AUTO_EXIT_MIN*60) {CloseCSM(MAINCSM_ID);}}
}
//////////////Автовыход   AAA//////////////

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  if(IsGuiOnTop(MAINGUI_ID))
  {
  unsigned short w = ScreenW();
  unsigned short h = ScreenH();
  unsigned short left = 0;
#ifdef ELKA
  unsigned short top = 24;
#else
  unsigned short top = 0;
#endif
    if(pngloadcomp==1)
    {
      DrawRoundedFrame(left,top,w-1,h-1,0,0,0,GetPaletteAdrByColorIndex(1),COLOR[2]);  // Поселим это сюда   AAA
#ifndef NO_PNG                         // Сделаем режим без скина - DG
  // --- Делаем типа скин ---
  sprintf(sfname,p_3s,PIC_DIR,items1[0],PNGEXT);
  DrawImg(left,top,(int)sfname);  // Рисуем фон
  // Громкость
#ifdef NEWSGOLD
  unsigned short nvol=15;
#else
  unsigned short nvol=14;
#endif
  sprintf(sfname,p_3s,PIC_DIR,items1[1],PNGEXT);
  DrawImg(coord[9],coord[10],(int)sfname);
  unsigned short wi=GetImgWidth((int)sfname);
  unsigned short hi=GetImgHeight((int)sfname);
  sprintf(sfname,"%s%s1%s",PIC_DIR,items1[1],PNGEXT);
  if(wi>hi)
  {
    unsigned short pos=(wi-GetImgWidth((int)sfname)-2)*GetVolLevel()/nvol+1;
    DrawImg(coord[9]+pos,coord[10]+hi*3/5,(int)sfname);
  }else{
    unsigned short pos=(hi-GetImgHeight((int)sfname)-2)*(nvol-GetVolLevel())/nvol+1;
    DrawImg(coord[9]+wi/5,coord[10]+pos,(int)sfname);
  }

  // Статус плеера
  if (Stat_keypressed==1)
  {
    switch(GetPlayingStatus())
    {
    case 0:
      sprintf(sfname,p_4s,PIC_DIR,items1[2],items1[13],PNGEXT);
      break;
    case 1:
      sprintf(sfname,p_4s,PIC_DIR,items1[3],items1[13],PNGEXT);
      break;
    case 2:
      sprintf(sfname,p_4s,PIC_DIR,items1[4],items1[13],PNGEXT);
      break;
    }
  } else {
    switch(GetPlayingStatus())
    {
    case 0:
      sprintf(sfname,p_3s,PIC_DIR,items1[2],PNGEXT);
      break;
    case 1:
      sprintf(sfname,p_3s,PIC_DIR,items1[3],PNGEXT);
      break;
    case 2:
      sprintf(sfname,p_3s,PIC_DIR,items1[4],PNGEXT);
      break;
    }
  }
  DrawImg(coord[11],coord[12],(int)sfname);
  // Режим воспроизв   AAA
  if (Mode_keypressed==1)
  {
    switch(playmode)
    {
    case 0:
      sprintf(sfname,p_4s,PIC_DIR,items1[5],items1[13],PNGEXT);
      break;
    case 1:
      sprintf(sfname,p_4s,PIC_DIR,items1[6],items1[13],PNGEXT);
      break;
    case 2:
      sprintf(sfname,p_4s,PIC_DIR,items1[7],items1[13],PNGEXT);
      break;
    case 3:
      sprintf(sfname,p_4s,PIC_DIR,items1[8],items1[13],PNGEXT);
      break;
    }
  } else {
    switch(playmode)
    {
    case 0:
      sprintf(sfname,p_3s,PIC_DIR,items1[5],PNGEXT);
      break;
    case 1:
      sprintf(sfname,p_3s,PIC_DIR,items1[6],PNGEXT);
      break;
    case 2:
      sprintf(sfname,p_3s,PIC_DIR,items1[7],PNGEXT);
      break;
    case 3:
      sprintf(sfname,p_3s,PIC_DIR,items1[8],PNGEXT);
      break;
    }
  }
  DrawImg(coord[15],coord[16],(int)sfname);  // Позиционируем все что видим!   AAA
  // Иконка пред/след трек   AAA
  switch(N_keypressed)
    {
    case 0:
      sprintf(sfname,p_3s,PIC_DIR,items1[9],PNGEXT);
      break;
    case 1:
      sprintf(sfname,p_4s,PIC_DIR,items1[9],items1[13],PNGEXT);
      break;
    case 2:
      sprintf(sfname,p_3s,PIC_DIR,items1[17],PNGEXT);
      break;
    }
  DrawImg(coord[19],coord[20],(int)sfname);
  
  switch(P_keypressed)
    {
    case 0:
      sprintf(sfname,p_3s,PIC_DIR,items1[10],PNGEXT);
      break;
    case 1:
      sprintf(sfname,p_4s,PIC_DIR,items1[10],items1[13],PNGEXT);
      break;
    case 2:
      sprintf(sfname,p_3s,PIC_DIR,items1[16],PNGEXT);
      break;
    }
  DrawImg(coord[21],coord[22],(int)sfname);
  // Если заблокировано DemonGloom
  if (KeyLock){
    sprintf(sfname,p_3s,PIC_DIR,items1[11],PNGEXT);
    DrawImg(coord[17],coord[18],(int)sfname);
  }
#else
    // Громкость
  unsigned short nvol=15;
  unsigned short pos=(30-4-2)*GetVolLevel()/nvol+1;
  DrawRoundedFrame(coord[9],coord[10],coord[9]+30,coord[10]+13,4,4,0,GetPaletteAdrByColorIndex(1),COLOR[2]);
  DrawRoundedFrame(coord[9]+pos,coord[10]+13*3/5,coord[9]+4+pos,coord[10]+13*4/5,4,4,0,GetPaletteAdrByColorIndex(0),COLOR[2]);
#endif
                                     // Здесь будут универсальные строки, одинаковые как для png, так и для их отсутствия


  /*
    WSHDR*mws=AllocWS(256);
    wsprintf(mws,"%s","0:\\1.png");
    IMGHDR *img;
    img=CreateImgHdrByAnyFile(mws,140,180,90);
    DrwImg2(img,0,20);
    mfree(img->bitmap);
    mfree(img);
    FreeWS(mws);
  
    */
    // Прогрессбар DG
    DrawRoundedFrame(coord[27],coord[28],coord[29],coord[30],2,2,0,COLOR[9],COLOR[8]);
    int ii=(coord[29]-coord[27]-1)*tm;
    ii=ii/ln;
    if(ii)DrawRoundedFrame(coord[27]+1,coord[28],ii+coord[27],coord[30],2,2,0,COLOR[11],COLOR[10]);  
  
  
    WSHDR * time_disp = AllocWS(32);
    wsprintf(time_disp,"%02i:%02i",tm/60,tm%60);
    DrawString(time_disp,coord[23],coord[24],coord[23]+Get_WS_width(time_disp,FONT_SMALL),coord[24]+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,COLOR[1],0);
    
    wsprintf(time_disp,"%02i:%02i",ln/60,ln%60);
    DrawString(time_disp,coord[25],coord[26],coord[25]+Get_WS_width(time_disp,FONT_SMALL),coord[26]+GetFontYSIZE(FONT_SMALL),FONT_SMALL,0,COLOR[1],0);
    FreeWS(time_disp);
  
    PL_Redraw(playlist_lines[CurrentPL],CurrentTrack,PlayedTrack,0,TC,CurrentPL,PlayedPL);
    CrPopup();
    ShowLongTXT(0, left, top, w);
   // if(wstrlen(SPerrs))DrawString(SPerrs,left,top,left+Get_WS_width(SPerrs,FONT_SMALL),top+GetFontYSIZE(FONT_SMALL),FONT_SMALL,2,GetPaletteAdrByColorIndex(3),0);
    }
#ifndef NO_PNG
    else{
      WSHDR*SP=AllocWS(64);
      str_2ws(SP,LG_Version,strlen(LG_Version));
      unsigned int Width=Get_WS_width(SP,FONT_SMALL);
      DrawRoundedFrame(left,top,w-1,h-1,0,0,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));  // Поселим это сюда   AAA
      
      sprintf(sfname,p_3s,PIC_DIR,items1[15],PNGEXT);
      DrawImg(left,top,(int)sfname);
      
      DrawRoundedFrame(0,h-6,w-Width-2,h,4,4,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));
      int ii=(w-Width-4)*Npng/ALLPNG;
      DrawRoundedFrame(2,h-4,ii,h-2,4,4,0,0,GetPaletteAdrByColorIndex(1));
      
      DrawString(SP,left,h-GetFontYSIZE(FONT_SMALL),w-2,h,FONT_SMALL,4,GetPaletteAdrByColorIndex(0),0);
      FreeWS(SP);
    }
#endif
  }
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Тут можно освободить выделяемую память
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
  DisableIDLETMR(); //Дабы не закрывался сам AAA
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
  DisableIDLETMR(); //Дабы не закрывался сам AAA
}

void QuitCallbackProc(int decision)
{
  if(decision==0)Quit_Required = 1;
}

/* Блок функций. Неоходимо для конфига клавиш. */
void DoErrKey() {
  WriteSPerr(SPerr4);
  if(SHOW_POPUP) ShowMSG(1, (int)lgpData[LGP_Error_2]);
}

void DoExit() {
  MsgBoxYesNo(1,(int)lgpData[LGP_Exit],QuitCallbackProc);
}

void LoadDefPlaylist() {
  CTtoFirst();
  PTtoFirst();
  LoadingPlaylist(DEFAULT_PLAYLIST);
}

void PrevTrackDown() {
  P_keypressed = 1;
  PreviousTrack();
}

void NextTrackDown() {
  N_keypressed = 1;
  if (playmode==2) RandTrack(); else NextTrack();
}

void SwitchPlayModeDown() {
  if (playmode<3) {playmode+=1;}
  else {playmode=0;}
  Mode_keypressed = 1;
}

void SavePL()
{
  sprintf(list,"%s%s",PLAYLISTS,"playlist");
  SavePlaylist(list);
}

void StartRewindToBegin()
{
  extern unsigned int IsRewind;
  if(PlayingStatus==0||IsRewind)return;
  ModeRew=-1;
  P_keypressed = 2;
  StartRewind();
}

void StartRewindToEnd()
{
  extern unsigned int IsRewind;
  if(PlayingStatus==0||IsRewind)return;
  ModeRew=1;
  N_keypressed = 2;
  StartRewind();
}

void PrevPL()
{
  ModeMove=-1;
  MovePL();
}

void NextPL()
{
  ModeMove=1;
  MovePL();
}

void CTDownSpeed(void)
{
  if(stop==0)return;
  stop=0;
  SpeedMove=1;
  CTSpeed();
}

void CTUpSpeed(void)
{
  if(stop==0)return;
  stop=0;
  SpeedMove=-1;
  CTSpeed();
}
/* Блок функций. Неоходимо для конфига клавиш. */


/*
  Обработчик нажатий клавиш. Сюда передаются нажатия клавиш
  в виде сообщения GUI_MSG, пример декодирования ниже.
*/
int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if(IsGuiOnTop(MAINGUI_ID)) {ResetAutoExit();}
  if(Quit_Required)return 1; //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
  if ((msg->gbsmsg->msg==LONG_PRESS)&&(msg->gbsmsg->submess=='#')){
    if (KeyLock)
    {
      KbdUnlock();
      if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Keypad_Unlock]);
    }
    else
    {
      KbdLock();
      if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Keypad_Lock]);
    }
     KeyLock=(KeyLock+1)%2;
     REDRAW();
     return 0;
     }
  else{ if (!(KeyLock)){
if(!EditPL)         //  Mr. Anderstand: самому не оч нравится такой вариант...
{
  if (msg->gbsmsg->msg==KEY_UP) {
     Disable_An(0,1,0,0,0,1);
     Stat_keypressed = 0;
     P_keypressed = 0;
     N_keypressed = 0;
     Mode_keypressed = 0;
     REDRAW();
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    DoKey(msg->gbsmsg->submess);
    REDRAW();
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    DoKey(msg->gbsmsg->submess+LONG_PRESS_DIFF);
    REDRAW();
  }
}else{
    
  if (msg->gbsmsg->msg==KEY_UP)
  {
    switch(msg->gbsmsg->submess)
    {
    case UP_BUTTON:
      if(move==0) {Disable_An(0,0,0,0,0,1);}
      break;
    case DOWN_BUTTON:
      if(move==0) {Disable_An(0,0,0,0,0,1);}
      break;
    }
    REDRAW();
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      MsgBoxYesNo(1,(int)lgpData[LGP_Exit],QuitCallbackProc);
      break;
    case RED_BUTTON:
      MsgBoxYesNo(1,(int)lgpData[LGP_Exit],QuitCallbackProc);
      break;
    case LEFT_SOFT:
      MM_Show();
      break;
    case GREEN_BUTTON:
      CTtoFirst();
      PTtoFirst();
      LoadingPlaylist(DEFAULT_PLAYLIST);
      break;
    case ENTER_BUTTON:
      move=!(move);
      break;
    case UP_BUTTON:
      if(move==0) {CTUp();}
      else {MoveLineUp();}
      break;
    case DOWN_BUTTON:
      if(move==0) {CTDown();}
      else {MoveLineDown();}
      break;
    case RIGHT_BUTTON:
      if(move==0) {NextPL();}
      else {MoveLineRight();}
      break;
    case LEFT_BUTTON:
      if(move==0) {PrevPL();}
      else {MoveLineLeft();}
      break;
    case '0':
      DeleteLine();
      break;
    case '2':
      if(move==0) {CTUpSix();}
      break;
    case '5':
      move=1;
      copy=1;
      break;
    case '8':
      if(move==0) {CTDownSix();}
      break;
    case '*':
      EditPL=0;
      break;
    }
    REDRAW();
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
      case UP_BUTTON:
        if(move==0) {CTUpSpeed();}
        else {MoveLineUp();}
      break;
      case DOWN_BUTTON:
        if(move==0) {CTDownSpeed();}
        else {MoveLineDown();}
      break;
      case '2':
        CTUpSix();
      break;
      case '8':
        CTDownSix();
      break;
    }
    REDRAW();
  }
  }
  }
  }
  return(0);
}


int my_keyhook(int submsg,int msg)
{
  if(IsGuiOnTop(MAINGUI_ID)) {ResetAutoExit();}
#ifdef ELKA
  if (submsg==POC_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {StopAllPlayback(); mode=1;  REDRAW(); return 2;}
    case KEY_UP: if (mode==0) TogglePlayback(); else {mode=0;  REDRAW(); return 2;}
    }}
  // А чем пл загружать?? AAA
/*#else
  if (submsg==GREEN_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {StopAllPlayback(); mode=1;  REDRAW(); return 2;}
    case KEY_UP: if (mode==0) TogglePlayback(); else {mode=0;  REDRAW(); return 2;}
    }}*/
#endif
  if (submsg==VOL_UP_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS:  if (mode==0) {if (playmode==2) RandTrack(); else NextTrack(); mode=1; }  N_keypressed = 1; REDRAW(); return 2;  // Следующий трек
      case KEY_UP: if (mode==0) VolumeUp(); else mode=0;  N_keypressed = 0; REDRAW(); return 2; // Громкость выше
    }}
  if (submsg==VOL_DOWN_BUTTON){
    switch (msg){
      case KEY_DOWN : return 2;
      case LONG_PRESS: if (mode==0) {PreviousTrack(); mode=1; }  P_keypressed = 1; REDRAW(); return 2;  // Предыдущий трек
      case KEY_UP: if (mode==0) VolumeDown(); else mode=0;  P_keypressed = 0; REDRAW(); return 2;  // Громкость ниже
    }}
  
  if ((submsg==0x27)){//&& !(IsCalling())){  // Если кнопка гарнитуры и не звонок
    switch (msg){
    case (KEY_DOWN): return 2;
    case (LONG_PRESS):  if (mode==0) {if (playmode==2) RandTrack(); else NextTrack(); mode=1; }  N_keypressed = 1; REDRAW(); return 2;  // Следующий трек
    case (KEY_UP): if (mode==0) {TogglePlayback(); Stat_keypressed = 0;}else mode=0; N_keypressed = 0; REDRAW(); return 2;  // Переключение pause/play 
    }
  }
  
  return(0);
}


// Destroy
extern void kill_data(void *p, void (*func_p)(void *));

// Всё ясно из названия ;) оставить как есть
static void ElfKiller(void)      //Добавил static не знаю зачем, главное - работает! :)  AAA
{
  if(SAVE_SETS)
  {
    sprintf(sfname,"%s%s",SETS_PATH,"pls.cfg");
    save_sets(sfname,0);
    sprintf(sfname,"%s%s",SETS_PATH,"sets.cfg");
    save_sets(sfname,1);
    for(unsigned int i=0;i<TCPL;i++) mfree(Playlists[i]);
  }
  GBS_DelTimer(&offtm);
  GBS_DelTimer(&mytmr);
  StopAllPlayback();
#ifdef OBS
  KillObj();
#endif
  MemoryFree();
  lgpFreeLangPack();                                   //Очисть память, выделенную под язык - Vedan
  RemoveKeybMsgHook((void *)my_keyhook);               //НАДО!!  AAA . Надо :) DemonGloom
  FreeWS(wl.wfilename);
  if(SPerrs) FreeWS(SPerrs);
  
  if(!IPC_COPY){
  gipc.name_to=ipc_grantee_name;                       // Это чтобы всех послать :)   AAA
  gipc.name_from=ipc_my_name;
  gipc.data=NULL;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_SPLAYER_CLOSED,&gipc);}
  
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

//===============================================================================================
// ELKA Compatibility
#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}
//===============================================================================================

// Оставить как есть
int method8(void){return(0);}

// Оставить как есть
int method9(void){return(0);}

// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

// Канвас для основного GUI
const RECT Canvas={0,0,0,0};

// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
  
  if(AUTO_EXIT_MIN) {AutoExit();}
  
  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
}

// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

#ifdef OBS
int obFrameUpd(HObj hobj,int error){
  
  return 0;
}

int obError(HObj hobj,int error){
  Obs_DestroyObject(hobj);
  return 0;
};

int obPrep(HObj hobj,int error){
  Obs_Start(hobj);
  EXT_REDRAW();
  GetPlayObjDuration((void*)hobj, &ln);
  ln/=1000;
 //Obs_GetInfo(hobj,0);    
  return 0;
};

int obDestroy(HObj hobj,int err)
{
  
 // if (flag_nextsong)CallSomeToPlayNextSong();
 // else ; //nothing when stop
  return 0;
}

/*
int obInfo(HObj hobj,int error){

  return 0;
};
*/

int obResumeCon(HObj hobj,int error){
  return 0;
};

int obParam (HObj hobj,int pl, int error){
    //  if (pl==2)obFrameUpd(hobj);
    //  if (pl==1)Obs_Resume(hobj);
  return 0;
};

int obSetPause(HObj hobj,int err)
{
  // Имитируем паузу
  StopTMR(0);
  PlayingStatus = 1;
  // Ловим время
  GetPlayObjPosition((void*)hobj,&tm);
  tm/=1000;
  tm_er=1;
  return 0;
}

int obSetStop(HObj hobj,int err)
{
  return 0;
}

int obNext(HObj hobj,int err)
{
  switch(playmode)
        {
          case 0:
            NextTrackX();         //Тупо, не спорю, если придумаете лучше...  AAA
            break;
          case 1:
            NextTrack();
            break;
          case 2:
            RandTrack();
            break;
          case 3:
            RepeatTrack();
            break;
        }
        REDRAW();
  return 0;
}

//int pint=0;
int obPause (HObj hobj,int pl, int error){
  
    /*  if (pint==1){
        int r;
          GetPlayObjPosition((void*)gObj,&r);
          Obs_SetPosition(gObj,r);
          pint--;
      }*/
  return 0;
};
/*
OBSevent ObsEventsHandlers[]={
  OBS_EV_FrameUpdate,(void*)obFrameUpd,
  OBS_EV_Error,(void*)obError,
  OBS_EV_PauseCon,(void*)obPause,
  OBS_EV_ParamChanged,(void*)obParam,
  OBS_EV_PrepareCon,(void*)obPrep,
  OBS_EV_destroy,(void*)obDestroy,
  OBS_EV_EndList,NULL
};*/

OBSevent ObsEventsHandlers[]={
  OBS_EV_FrameUpdate,(void*)obFrameUpd,
  OBS_EV_Error,(void*)obError,
  //OBS_EV_GetInfoCon,(void*)obInfo,
  OBS_EV_PauseCon,(void*)obPause,
  OBS_EV_ParamChanged,(void*)obParam,
  OBS_EV_ResumeCon,(void*)obResumeCon,
  OBS_EV_PauseInd,(void*)obSetPause,
  OBS_EV_StopInd,(void*)obSetStop,
  OBS_EV_LoopUpdate,(void*)obNext,
  OBS_EV_PrepareCon,(void*)obPrep,
  OBS_EV_ConvDestroyed,(void*)obDestroy,
  OBS_EV_EndList,NULL
};
#endif

// Обработчик событий главного CSM
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  {
  if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
        if (strcmp(ipc->name_to,ipc_my_name)==0)//strcmp_nocase
        {
          switch (msg->submess)
          {
          case IPC_CHECK_DOUBLERUN:
            //Если приняли свое собственное сообщение, значит запускаем чекер
	    if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
            else ipc->data=(void *)MAINCSM_ID;
            break;
          case IPC_REFRESH:
            if (strcmp(ipc->name_from,ipc_editor_name)==0) {Refresh();}
            break;
          case IPC_PLAY_PAUSE:
          //  ipc->data=(void *)((int)(ipc->data)+1);
	    if (strcmp(ipc->name_from,ipc_control_name)==0) {TogglePlayback();}
            break;
          case IPC_STOP:
          //  ipc->data=(void *)((int)(ipc->data)+1);
	    if (strcmp(ipc->name_from,ipc_control_name)==0) {StopAllPlayback();}
            break;
          case IPC_NEXT_TRACK:
          //  ipc->data=(void *)((int)(ipc->data)+1);
	    if (strcmp(ipc->name_from,ipc_control_name)==0) {NextTrack();}
            break;
          case IPC_PREV_TRACK:
          //  ipc->data=(void *)((int)(ipc->data)+1);
	    if (strcmp(ipc->name_from,ipc_control_name)==0) {PreviousTrack();}
            break;
          }
        }
      }
     // if (ipc->name_to==ipc_grantee_name) {ShowMSG(1,(int)ipc->data);}
    }
  if (Quit_Required)
  {
    csm->csm.state=-3;
  }
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  // Нарисуем иконку статуса на IDLESCREEN
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(idlegui_id)) //Если IdleGui на самом верху
  {
    GUI *igui=GetTopGUI();
    if (igui) //И он существует
    {
#ifdef ELKA
	void *canvasdata=BuildCanvas();
#else
	void *idata=GetDataOfItemByID(igui,2);
	if (idata)
	{
	  void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif

#ifndef NO_PNG     
        switch(GetPlayingStatus())
	{
        case 0:
          sprintf(sfname,p_4s,PIC_DIR,items1[2],items1[14],PNGEXT);
          break;
        case 1:
          sprintf(sfname,p_4s,PIC_DIR,items1[3],items1[14],PNGEXT);
          break;
        case 2:
          sprintf(sfname,p_4s,PIC_DIR,items1[4],items1[14],PNGEXT);
          break;
	}
        DrawCanvas(canvasdata,IDLE_X,IDLE_Y,IDLE_X+GetImgWidth((int)sfname)-1,IDLE_Y+GetImgHeight((int)sfname)-1,1); // Сделаем так   AAA
	DrawImg(IDLE_X,IDLE_Y,(int)sfname);
#else
        DrawCanvas(canvasdata,IDLE_X,IDLE_Y,IDLE_X+16,IDLE_Y+16,1); // Сделаем так   AAA
#endif
        
#ifdef ELKA
#else
	}
#endif
    }
  }
  }
  // если реконфиг
  
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      Refresh();
      LoadKeys();
      InitLanguage();
      ShowNamesNoConst=SHOW_NAMES;
      
      if(!IsTimerProc(&offtm)) {AutoExit();}
      ResetAutoExit();
      
      if(SHOW_POPUP) ShowMSG(1,(int)lgpData[LGP_Config_Updated]);
    }
  }
#ifdef NEWSGOLD
  // Если вход.звонок или звонок закончился Blind007
  // У кого руки такие кривые??
  // Blind007: А что не так?
  // Ы! В самом начале писал, что не пашет, так не пашет и теперь... AAA
  if (((msg->msg==MSG_INCOMMING_CALL)&&(PlayingStatus==2)) || ((msg->msg==MSG_END_CALL)&&(PlayingStatus==1)))
  {
    TogglePlayback();
  }
#else 
//  if (IsCalling()&&(PlayingStatus==2))
//  {
//    TogglePlayback();
//  }
#endif
#ifndef OBS
  if (msg->msg==MSG_PLAYFILE_REPORT)   // Для определения конца воспр.  AAA
  {
    GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
    if (pmsg->handler==phandle)
    {
      if (pmsg->cmd==M_SAE_PLAYBACK_DONE)//||pmsg->cmd==M_SAE_PLAYBACK_ERROR)  // А зачем на следующий при ошибке?
      {
        switch(playmode)
        {
          case 0:
            NextTrackX();         //Тупо, не спорю, если придумаете лучше...  AAA
            break;
          case 1:
            NextTrack();
            break;
          case 2:
            RandTrack();
            break;
          case 3:
            RepeatTrack();
            break;
        }
        REDRAW();
      }
      if (pmsg->cmd==M_SAE_PLAYBACK_STARTED)
      {
        EXT_REDRAW();
#ifdef NEWSGOLD
        pha=GetPlayObjById(phandle);
        if(phandle!=-1)Obs_Sound_SetVolumeEx((( int*)pha)[0x3d0/4], SoundVolume, 1);
        GetPlayObjDuration((( int**)pha)[0x3d0/4], &ln);
        ln/=1000;
#else
        if(phandle!=-1)PlayMelody_ChangeVolume(phandle,SoundVolume);
#endif
      }
//      if (pmsg->cmd==M_SAE_HANDSFREE_UPDATED)
//      {
//        GetAccessoryType();
//      }
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
    return 0;
  }
  //if (key==stop){obs_destroyobj() flag_nextsong=false}
  //if (key==next){obs_destroyobj(); flag_nextsong=true}
#endif
  return(1);
}

// Инициализация структуры MAINCSM
const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
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
  }
};

// Функция, которая устанавливает название этого CSM для X-Task.
// Покажем в XTask'e что играем! Blind007
void UpdateCSMname(WSHDR * tname)
{
  if (tname) {
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"%s - %w","SPlayer",tname);
  } else {
    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SPlayer");
  }
}


// Основная процедура. Она первой получает управление при старте эльфа.
int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  InitConfig();
  Refresh();
  lgpInitLangPack(); //Загрузка языка - Vedan
  SUBPROC((void*)LoadKeys);
  SUBPROC((void*)LoadPng); // Загрузка пнг   AAA
  ShowNamesNoConst=SHOW_NAMES;
 // extern WSHDR* wsfile;
 // wsfile=AllocWS(256);
  wl.wfilename=AllocWS(128);
  // Если что-то передали в параметре - загружаем...
  unsigned int err;
  FSTATS fstats;
  if (GetFileStats(fname,&fstats,&err)!=-1)     // Если плей-лист существует
  {    
    LoadingPlaylist(fname);
  }
  if(SAVE_SETS)
  {
    for(unsigned int i=0;i<TCPL;i++) Playlists[i]=malloc(256);
    sprintf(sfname,"%s%s",SETS_PATH,"pls.cfg");
    load_skin(sfname);
    for(unsigned int i=0;i<TCPL;i++)
    {
      CurrentPL=i;
      if(Playlists[i])LoadingPlaylist(Playlists[i]);
    }
    CurrentPL=0;
    sprintf(sfname,"%s%s",SETS_PATH,"sets.cfg");
    load_skin(sfname);
    
  }else{
  playmode = PlayMode;
  SoundVolume = soundvolume;
  if(TC[CurrentPL]==0){ // если плейлист из параметра пустой или нет параметров-> грузим стандарт
    if (DEFAULT_PLAYLIST!="")
    {
      LoadingPlaylist(DEFAULT_PLAYLIST);
      CurrentPL++;
      LoadingPlaylist(DEFAULT_PLAYLIST1);
      CurrentPL++;
      LoadingPlaylist(DEFAULT_PLAYLIST2);
      CurrentPL=0;
    }
  }
  }
  UpdateCSMname(NULL);
  LockSched();
  phandle=-1;
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  AddKeybMsgHook((void *)my_keyhook);
  UnlockSched();
  return 0;
}
