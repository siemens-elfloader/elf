#include "C:\arm\inc\swilib.h"
#include "conf_loader.h"
#include "obs/obs.c"

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

GBSTMR tmr;


int char8to16(int c)
{
  if (c<168) return (c);
  c-=168;
  if (!c)  c=1;
  else if (c<24) 
  {
    if (c==2) c=4;
    else if (c==10) c=6;
    else if (c==11) c=0x56;
    else if (c==16) c=0x51;
    else if (c==18) c=0x54;
    else if (c==23) c=0x57;
    else return (c);
  }
  else if (c>87) return (c);
    else c-=8;
  c+=0x400;
  return (c); 
}

void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
}

void DrawProgress();
char stroka[256];
static void OnRedraw(MAIN_GUI *data)//Перерисовка во время загрузки
{
 DrawProgress();
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
char name[128];
  TDate d;
  TTime t;
char amr[3]="amr";
HObj obj;
void e()
{
  WSHDR *ws=AllocWS(256);
  wsprintf(ws,"amr");
  int uid=GetExtUid_ws(ws);
  
  obj=Obs_CreateObject(uid,0x34,2,0xB034,1,0,0);
  wsprintf(ws,"0:\\1.amr");
  Obs_SetInput_File(obj,0,ws);
  Obs_Mam_SetPurpose(obj,0x16);
  Obs_Sound_SetVolumeEx(obj, 1, 1);
  Obs_Prepare(obj);
  
  FreeWS(ws);
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
    
    
  case '4':
   e();
    break;
    case '6':
   Obs_Start(obj);
    break;
   case GREEN_BUTTON:
     
   switch(action)
  {
  case AMR_NOT_CREATED:case AMR_STOP:
  

  GetDateTime(&d,&t);
  sprintf(name,"%d-%d-%u_%d-%d-%d_mode%d_bit%d.amr",d.day,d.month,d.year,t.hour,t.min,t.sec,amrmode,bitrate);
  Obs_CreateAmrFile(name);
    
    break;
  }
     
     
     break;
  case LEFT_SOFT:openconf(); break;
   case RIGHT_SOFT: 
      switch(action)
      {
      case AMR_WRITE:case AMR_PAUSE:Obs_StopAmrWrite();Obs_DeleteObj();break;
      default: return 1;
      }
        
       
  case '5':case ENTER_BUTTON:
  switch(action)
  {
  case AMR_CREATED:Obs_StartAmrWrite();break;
  case AMR_WRITE:  Obs_PauseAmrWrite();break;
  case AMR_PAUSE:  Obs_ResumeAmrWrite();break;
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
   GBS_DelTimer(&tmr);
  Obs_DeleteObj();
  
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
    InitConfig();
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Dictophone");
}
RECT pb={10,220,230,240};


double t1=0;

void DrawProgress()
{
  DrawRectangle(0,0,239,319,1,GetPaletteAdrByColorIndex (0),GetPaletteAdrByColorIndex (0));
  WSHDR *ws=AllocWS(256);
  
  switch(action)
  {
  case AMR_NOT_CREATED:case AMR_STOP: ascii2ws(ws,"Нажмите зеленую кнопку, \nчтобы создать файл\nПравый софт для выхода\n");break;
  case AMR_CREATED: ascii2ws(ws,"Нажмите 5, чтобы начать запись\nПравый софт для выхода");break;
  case AMR_WRITE: ascii2ws(ws,"Нажмите 5, чтобы приостановить запись\nПравый софт для остановки записи");break;
  case AMR_PAUSE: ascii2ws(ws,"Нажмите 5, чтобы продолжить запись\nПравый софт для остановки записи");break;
  }
 DrawString (ws, 0, 0, 239, 100, 9, 2, GetPaletteAdrByColorIndex (1),0);
 if(action==AMR_WRITE){wsprintf(ws,"%d/%d %s",Obs_GetRealSize()/1024,size,folder[strlen(folder)-1]);
 DrawString (ws, 0, 200, 239, 220, 9, 2, GetPaletteAdrByColorIndex (1),0);}
  

  

  DrawRectangle(pb.x,pb.y,pb.x2,pb.y2,1,GetPaletteAdrByColorIndex (14),GetPaletteAdrByColorIndex (23));
  
  DrawRectangle(pb.x+1,pb.y+1,pb.x+1+t1,pb.y2-1,1,GetPaletteAdrByColorIndex (23),GetPaletteAdrByColorIndex (14));

  
  FreeWS(ws);
}

void Proc()
{
  
  if(action==AMR_WRITE){t1=(pb.x2-pb.x-2)*Obs_Percente();DirectRedrawGUI();}
  GBS_StartTimerProc(&tmr,100,Proc);
}

int main(char *exename, char *fname)
{
  InitConfig();
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  Proc();
  return 0;
}
