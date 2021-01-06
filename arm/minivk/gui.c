#include "..\inc\swilib.h"
#include "main.h"
#include "gui.h"
#include "internet.h"



void OnRedraw(MAIN_GUI *data)
{
  DrawRoundedFrame(0,0,239,319,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  wsprintf(data->ws1,"log: %s",logmsg);
  DrawString(data->ws1,20,20,220,300,9,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void OnCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  #ifdef ELKA
  DisableIconBar(1);
  #endif
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void OnClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  #ifdef ELKA
  DisableIconBar(0);
  #endif
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void OnFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  #ifdef ELKA
  DisableIconBar(1);
  #endif
  data->gui.state=2;
}

void OnUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  #ifdef ELKA
  DisableIconBar(0);
  #endif
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  
  if(msg->gbsmsg->msg==KEY_UP)
  switch(msg->gbsmsg->submess)
  {
  case RIGHT_SOFT:return 1;
  case GREEN_BUTTON:create_connect();break;
  }
  //DirectRedrawGUI();
  return(0);
}

void OnDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}



const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)OnCreate,	//Create
  (void *)OnClose,	//Close
  (void *)OnFocus,	//Focus
  (void *)OnUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)OnDestroy,	//Destroy
  (void *)0,
  (void *)0,
  0
};

const RECT Canvas={0, 0, 0, 0};

void maincsm_oncreate_GUI(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM_GUI*csm=(MAIN_CSM_GUI*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  gui_mode=1;
}

int maincsm_onmessage_GUI(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM_GUI *csm=(MAIN_CSM_GUI*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

void maincsm_onclose_GUI(CSM_RAM *csm)
{
  gui_mode=0;
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name_GUI;
}MAINCSM =
{
  {
    maincsm_onmessage_GUI,
    maincsm_oncreate_GUI,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose_GUI,
sizeof(MAIN_CSM_GUI),
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name_GUI),"gui");
}

void Create_GUI()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM_GUI)];
  CreateCSM(&MAINCSM.maincsm,dummy,2);
  UnlockSched();
  UpdateCSMname();
}
