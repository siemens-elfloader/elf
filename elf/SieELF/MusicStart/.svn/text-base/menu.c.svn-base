#include "..\inc\swilib.h"
#include "lang.h"
#include "rect_patcher.h"
#include "filelist.h"
#include "play_list.h"
#include "main.h"

extern const char *successed_config_filename;
extern int play_mode;

const int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_skm[]=
{
  {0x0018,0x0000,(int)LGP_SELECT},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_sktm=
{
  menu_skm,0
};

HEADER_DESC mm_menuhdr={0,0,0,0,NULL,(int)ELF_NAME,LGP_NULL};

#define maeITEMS_N 2

MENUITEM_DESC maemenu_items[maeITEMS_N]=
{
  {NULL,(int)LGP_START_AUTOEXIT,      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_STOP_AUTOEXIT,       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

void start_autoexit(GUI *data)
{
  start_auto_exit();
  GeneralFuncF1(1);
}

void stop_autoexit(GUI *data)
{
  stop_auto_exit();
  GeneralFuncF1(1);
}

const MENUPROCS_DESC maemenu_hndls[maeITEMS_N]=
{
  start_autoexit,
  stop_autoexit
};

const MENU_DESC mae_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  maemenu_items,   //Items
  maemenu_hndls,   //Procs
  maeITEMS_N   //n
};

void menu_auto_exit(GUI *data)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&mae_menu,&mm_menuhdr,0,maeITEMS_N,0,0);
  GeneralFuncF1(1);
}

#define pmITEMS_N 3

MENUITEM_DESC pmmenu_items[pmITEMS_N]=
{
  {NULL,(int)LGP_CYCLETOP2BOTTOM,      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_CYCLEBOTTOM2TOP,      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_SHUFFLE,              LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

void mode_t2b(GUI *data) 
{
  play_mode=0;
  GeneralFuncF1(1);
}

void mode_b2t(GUI *data) 
{
  play_mode=1;
  GeneralFuncF1(1);
}

void mode_shuf(GUI *data) 
{
  play_mode=2;
  GeneralFuncF1(1);
}

const MENUPROCS_DESC pmmenu_hndls[pmITEMS_N]=
{
  mode_t2b,
  mode_b2t,
  mode_shuf
};

const MENU_DESC pm_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  pmmenu_items,   //Items
  pmmenu_hndls,   //Procs
  pmITEMS_N   //n
};

void menu_play_mode(GUI *data)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&pm_menu,&mm_menuhdr,0,pmITEMS_N,0,0);
  GeneralFuncF1(1);
}

#define ITEMS_N 7

MENUITEM_DESC menu_items[ITEMS_N]=
{
  {NULL,(int)LGP_OPEN,          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_PLAYMODE,      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_PLAYLIST,      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_ATUOEXIT,      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_OPTIONS,       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_ABOUT,         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_EXIT,          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};


void menu_open(GUI *data) 
{
  open_select_file_gui(1,0);
  GeneralFuncF1(1);
}

void menu_select_list(GUI *data)
{
  select_list_gui();
  GeneralFuncF1(1);
}




void menu_options(GUI *data)
{
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

void menu_about(GUI *data) 
{
  ShowMSG(1, (int)COPYRIGHT);
  GeneralFuncF1(1);
}

void menu_exit(GUI *data)
{
  exit();
}


const MENUPROCS_DESC menu_hndls[ITEMS_N]=
{
  menu_open,
  menu_play_mode,
  menu_select_list,
  menu_auto_exit,
  menu_options,
  menu_about,
  menu_exit,
};




const MENU_DESC mm_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  menu_items,   //Items
  menu_hndls,   //Procs
  ITEMS_N   //n
};

void create_main_menu(void)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&mm_menu,&mm_menuhdr,0,ITEMS_N,0,0);
}



