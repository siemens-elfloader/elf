#include "c:\ARM\inc\swilib.h"
#include "C:\ARM\inc\cfg_items.h"
#include "conf_loader.h"
#include "mainmenu.h"
#include "connect.h"
#include "main.h"

//-----------------------------------Создал-------------------------------------

/*
(c) VedaN and KIBER-DEMON
*/

//-----------------------------------Учетные данные-----------------------------

typedef struct{CSM_RAM csm;int gui_id;}MAIN_CSM;
typedef struct{GUI gui;WSHDR *ws1;WSHDR *ws2;int i1;}MAIN_GUI;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
const int minus11=-11;
int StartMenu(void);
int color=23;
char name[256];
void InitConfig();

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

//------------------------------------Считывание конфига------------------------

void RereadSettings(void)
{
   LockSched();
    InitConfig();
   UnlockSched();
}

//Соединение--------------------------------------------------------------------

void GetInetInfo(void)
{
  Connect();
}

//-----------------------------Разное-------------------------------------------

extern void kill_data(void *p,void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{   
  #ifdef ELKA
  DrawRoundedFrame(0,0,239,319,0,0,0,GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(color));
  #else
  DrawRoundedFrame(0,0,131,175,0,0,0,GetPaletteAdrByColorIndex(23),GetPaletteAdrByColorIndex(color));
  #endif
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
  StartMenu();
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{ 
  data->gui.state=2;
  GeneralFuncF1(1); // рубим верхний гуй. И приложение закрывается.
  DisableIDLETMR();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
     return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
         }
  }
  return(0);
}

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,    //method7,//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

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
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"ElfLibraryInfo config updated!");
      InitConfig();
    }
  }
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
  }
  return(1);
}

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

//-----------------------------CSM Имя------------------------------------------

static void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ElfLibraryInfo");
  FreeWS(ws);
}

//-------------------------------Сам мэйн---------------------------------------

int main(void)
{
  RereadSettings();
  CSM_RAM main_csm;  
  UpdateCSMname(); 
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  return 0;
}

//---------------------------------Конец----------------------------------------
