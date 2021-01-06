#include "..\inc\swilib.h"

extern const int minus11;
unsigned short maincsm_name_body[140];
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM_GUI;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;
extern int mode;

extern void kill_data(void *p, void (*func_p)(void *));


int MAINCSM_ID=0;


void DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}
#pragma swi_number=0x0190
__swi __arm void MutexCreate(MUTEX *mtx);
//arm
//pattern=

#pragma swi_number=0x0191
__swi __arm void MutexDestroy(MUTEX *mtx);
//arm
//pattern=

#pragma swi_number=0x0192
__swi __arm void MutexLock(MUTEX *mtx);
//arm
//pattern=

#pragma swi_number=0x0193
__swi __arm void MutexLockEx(MUTEX *mtx, int flag);
//arm
//pattern=

#pragma swi_number=0x0194
__swi __arm void MutexUnlock(MUTEX *mtx);
void Init()
{
  //panel=CreateIMGHDRFromPngFile("0:\\panel.png",3);
}

void method0(MAIN_GUI *data)
{
 // DrawRoundedFrame(0,0,239,319,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  //DrwImg(panel,4,50);
  //wsprintf(data->ws1,"%d",data);
 // DrawString(data->ws1,0,0,240,100,2,9,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
}
void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  #ifdef ELKA
  DisableIconBar(1);
  #endif
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  #ifdef ELKA
  DisableIconBar(0);
  #endif
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}
int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();

  switch(msg->gbsmsg->submess)
  {
  case RIGHT_SOFT:return 1;
  }
  return(0);
}


void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
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
  mode=0;
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
void StartGUI()
{
  mode=1;
  LockSched();
  UpdateCSMname();
  char dummy[sizeof(MAIN_CSM_GUI)];
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,2);
  UnlockSched();
}
