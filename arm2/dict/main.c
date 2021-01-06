#include "..\inc\swilib.h"
#include "conf_loader.h"


const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  WSHDR *ws5;
  int i1;
}MAIN_GUI;

extern const char amr[128];
extern const unsigned int size;
extern const unsigned int buid;


int uid=0;
int MSG_Report;
WSHDR *ws_main;
HObj object=0;
GBSTMR Tmr;
int filesize=0;
char name[256];

#define NOT_CREATED -1
#define RECORDING 1
#define PAUSED 2
int mode=NOT_CREATED;
void CreateFile();
void StartRecord();
void StopRecord();
void PauseRecord();
void ResumeRecord();
void MyTmr();


char pt[8] = "%t";
static void OnRedraw(MAIN_GUI *data)//Перерисовка во время загрузки
{
  DrawRectangle(0,0,132,176,1,GetPaletteAdrByColorIndex (0),GetPaletteAdrByColorIndex (0));
  WSHDR *ws=AllocWS(256);
   switch(mode)
    {
    case NOT_CREATED:wsprintf(ws, pt, "Нажмите 5 или enter для начала записи");break;
    case RECORDING:wsprintf(ws,"%d/%d kb\n%t",filesize/1024,size, "Нажмите 5 или enter для паузы\nПравый софт для окончания записи");break;
    case PAUSED:wsprintf(ws,"%d/%d kb\n%t",filesize/1024,size, "Нажмите 5 или enter для продолжения записи\nПравый софт для окончания записи");break;
    }
    DrawString (ws, 0, 0, 132, 176, 11, 2, GetPaletteAdrByColorIndex (1),0);
    FreeWS(ws);
}
static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))//Тут делаем что либо при создании гуи
{
  #ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
  #endif
  data->ws1=AllocWS(256);//Выделяем память под строку
  data->gui.state=1;
}
static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))//Сдесь делаем что нить при закрытии гуи:)
{
  data->gui.state=0;
  FreeWS(data->ws1);//например, освобождаем память
  FreeWS(data->ws5);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
    #ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
  #endif
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}
int openconf()//Для чтения настроек с конфига
{
extern const char *successed_config_filename;
WSHDR *fws=AllocWS(strlen(successed_config_filename)+1);
wsprintf(fws,"%t",successed_config_filename);
ExecuteFile(fws,NULL,NULL);
FreeWS(fws);
return 0;
}
static int OnKey(MAIN_GUI *data, GUI_MSG *msg)//Ну это кей хук
{

  switch(msg->gbsmsg->msg)
  {      
  case KEY_UP: break;
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
      
 switch(msg->gbsmsg->submess)
  {
   case GREEN_BUTTON:break;
  case LEFT_SOFT:openconf(); break;
   case RIGHT_SOFT: 
        if(mode==RECORDING||mode==PAUSED)StopRecord();
        else return 1;
        break;
  case '5':case ENTER_BUTTON:
    switch(mode)
    {
    case NOT_CREATED:CreateFile();StartRecord();break;
    case RECORDING:PauseRecord();break;
    case PAUSED:ResumeRecord();break;
    }
    
    break;
  }
  

  }
     DirectRedrawGUI();
      
  return(0);
}











extern void kill_data(void *p, void (*func_p)(void *));

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

static void maincsm_oncreate(CSM_RAM *data)
{
  
static const RECT Canvas={0,0,239,319};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ws_main);
  Obs_Stop(object);
  if(IsTimerProc(&Tmr))GBS_DelTimer(&Tmr);
  Obs_DestroyObject(object);
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{

  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
 if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    
  }
  return(1);
}


static const struct
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
void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Test");
}

FSTATS fs;

void MyTmr()
{
      switch(mode)
    {
    case NOT_CREATED:
      filesize=0;
      break;
      
      
    case RECORDING:
      
      GetFileStats(name,&fs,0);
      filesize=fs.size;
      if(filesize>=size*1024)StopRecord();
      DirectRedrawGUI();
      break;
      
      
    case PAUSED:
      
      break;
    }
  
  GBS_StartTimerProc(&Tmr,100,MyTmr);
}






void CreateFile()
{

  wsprintf(ws_main,"amr");
  uid=GetExtUid_ws(ws_main);
#ifndef NEWSGOLD
  if (buid == 0)
  object=Obs_CreateObject(0x30,uid,2,MSG_Report,1,0,0);
  else 
  object=Obs_CreateObject(0x30,buid,2,MSG_Report,1,0,0);
#else
  if (buid == 0)
  object=Obs_CreateObject(0x34,uid,2,0x70A3,0,0,0);
  else 
  object=Obs_CreateObject(0x34,buid,2,0x70A3,0,0,0);
#endif
  
  wsprintf(ws_main, "%s", amr);
  Obs_SetOutput_File(object, ws_main);
  
  Obs_Sound_SetMaxFileSize(object,size*1024);
  Obs_Sound_SetNofChannels(object, 1);
  Obs_Sound_SetFIsRecording(object, 1);
  Obs_Sound_SetAMRDTX(object, 0);
  Obs_Sound_SetBitrate(object, NORMAL_BITRATE);
  Obs_Sound_SetAMRMode(object, 0x4);
  Obs_Sound_SetAMRFormat(object, 0);
  Obs_Sound_SetAMRFrmPrBuf(object, 0xA0);
  Obs_Sound_SetRecordingMode(object, 0);
  Obs_Sound_SetPurpose(object, 0xC);
  
}


void StartRecord()
{
  Obs_Start(object);
  mode=RECORDING;
}

void StopRecord()
{
  Obs_Stop(object);
  mode=NOT_CREATED;
}
void PauseRecord()
{
  Obs_Pause(object);
  mode=PAUSED;
}
void ResumeRecord()
{
  Obs_Resume(object);
  mode=RECORDING;
}
int main(char *exename, char *fname)
{
   
  
  
  InitConfig();
  ws_main=AllocWS(256);
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  MyTmr();
  return 0;
}



