#include "..\inc\swilib.h"

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

//==============================================================================
// Гуй
//==============================================================================
/*
extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;

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
  int i1;
}MAIN_GUI;

void method0(MAIN_GUI *data)
{
  DrawRoundedFrame(0,0,ScreenH()-1,ScreenW()-1,0,0,0,
			GetPaletteAdrByColorIndex(23),
			GetPaletteAdrByColorIndex(23));
}

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
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
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:
      return(1); 
    }//Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
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

const RECT Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  //SUBPROC((void *)ELF_KILLER);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

unsigned short maincsm_name_body[140];

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

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"KeyMaster");
}

void ShowRedBtnMenu()
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
}
*/
//
//==============================================================================
// Uptime counter
//==============================================================================


TDate date;
TTime time; 
int sh;
int sm;
int ss;
int sd;
int nh;
int nm;
int ns;
int nd;

char resstr;

void count_uptime()
{
GetDateTime(&date,&time);
  ns=time.sec-ss;
  if (ns<0){
    ns=60+ns;
    time.min--;
  }
  nm=time.min-sm;
  if (nm<0){
    nm=60+nm;
    time.hour--;
  }
  nh=time.hour-sh;
  if (nh<0){
    nh=24+nh;
    date.day--;
  }
  nd=date.day-sd;
  if (nd<0){
    nd=0;
  }
  if (nd==0) sprintf(&resstr,"Uptime %02i:%02i",nh,nm);
       else sprintf(&resstr,"Uptime %i Days, %02i:%02i",nh,nm);
}
//==============================================================================
// Меню
//==============================================================================
#define MENU_ITEMS_NUM 4

char hdr[64];
char hdr2;
static const HEADER_DESC rb_menuhdr = {0, 0,NULL,NULL,NULL, (int) hdr, LGP_NULL};

static void mp1()
{
  SwitchPhoneOff();
  GeneralFuncF1(1);
}

static void mp2()
{
  RebootPhone();
  GeneralFuncF1(1);
}

static void mp3()
{
  KbdLock();
  GeneralFuncF1(1);
}

static void mp4()
{
  SetProfile(8);
  GeneralFuncF1(1);
}

static const char * const menutexts[MENU_ITEMS_NUM]=
{
  "关机",
  "重启",
  "锁键盘",
  "关机无闹铃"
};

static const void *menuprocs[MENU_ITEMS_NUM]=
{
  (void *)mp1,
  (void *)mp2,
  (void *)mp3,
  (void *)mp4,
};

static const int menusoftkeys[] = {0,1,2};
static const SOFTKEY_DESC menu_sk[]=
{
  {0x0018, 0x0000, (int)"选择"},
  {0x0001, 0x0000, (int)"关闭"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

int rb_menu_onkey(void *data, GUI_MSG *msg)
{
//  count_uptime();
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(&hdr2,"菜单  %02d:%02d",t.hour,t.min);
  strncpy(hdr,&hdr2,63);
  
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
  }  
  return(0);
}

void rb_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

void rb_menu_iconhndl(void *data, int curitem, void *unk)
{
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(&hdr2,"菜单  %02d:%02d",t.hour,t.min);
  strncpy(hdr,&hdr2,63);
//  count_uptime();
  
  WSHDR *ws;
  WSHDR *ws2;
  void *item=AllocMLMenuItem(data);
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  ws2=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws, "%t", menutexts[curitem]);
  wsprintf(ws2, "%s", resstr);

  SetMLMenuItemText(data, item, ws, ws2, curitem);
}

static const ML_MENU_DESC rb_menu=
{
  8,rb_menu_onkey,rb_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x10,
  rb_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  MENU_ITEMS_NUM,   //n
  0 //Добавочных строк  
};

void CreateRBMenu(void)
{
  patch_header(&rb_menuhdr);
  sprintf(&resstr,"");
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(&hdr2,"%i kb RAM %02d:%02d",GetFreeRamAvail()/1024,t.hour,t.min);
  strncpy(hdr,&hdr2,63);
  CreateMultiLinesMenu(0,0,&rb_menu,&rb_menuhdr,0,MENU_ITEMS_NUM);
}
