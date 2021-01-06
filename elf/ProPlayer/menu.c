#include "C:\ARM_ALL\inc\swilib.h"
#include "rect_patcher.h"
#include "play_list.h"
#include "filelist.h"
#include "tagmenu.h"
#include "main.h"
#include "lang.h"

extern const char *successed_config_filename;
int menu_icon[]={0x33B,0};
extern int play_equaliser;
extern int play_mode;
extern int sub_menu;

char tag_file_path[128];

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

HEADER_DESC mm_menuhdr={0,0,0,0,menu_icon,(int)ELF_NAME,LGP_NULL};

#define TAIMER_ITEMS_N 2

MENUITEM_DESC taimer_menu_items[TAIMER_ITEMS_N]=
{
  {NULL,(int)LGP_START_AUTOEXIT,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_STOP_AUTOEXIT,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
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

const MENUPROCS_DESC taimer_menu_hndls[TAIMER_ITEMS_N]=
{
  start_autoexit,
  stop_autoexit
};

const MENU_DESC taimer_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  taimer_menu_items,
  taimer_menu_hndls,
  TAIMER_ITEMS_N
};

void menu_auto_exit(GUI *data)
{ 
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&taimer_menu,&mm_menuhdr,0,TAIMER_ITEMS_N,0,0);
  GeneralFuncF1(1);
}

#define OPEN_ITEMS_N 2

void OpenFille(GUI *data)
{
  open_select_file_gui(1,0);
  GeneralFuncF1(1);
}

void OpenPlaylist(GUI *data)
{
  open_select_file_gui(1,1);
  GeneralFuncF1(1);
}

MENUITEM_DESC open_menu_items[OPEN_ITEMS_N]=
{
  {NULL,(int)LGP_OPENFILLE,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_OPENPLAYLIST,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC open_menu_hndls[OPEN_ITEMS_N]=
{
  OpenFille,
  OpenPlaylist
};

const MENU_DESC open_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  open_menu_items,
  open_menu_hndls,
  OPEN_ITEMS_N
};

void Menu_Open(GUI *data)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&open_menu,&mm_menuhdr,0,OPEN_ITEMS_N,0,0);
  GeneralFuncF1(1);
}

#define EQUALISER_ITEMS_N 11

MENUITEM_DESC equaliser_menu_items[EQUALISER_ITEMS_N]=
{
  {NULL,(int)LNG_EQUALISER_CLASSICAL,LGP_NULL,0,NULL, MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_CLUB,LGP_NULL,0,NULL, MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_DANCE,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_BASS,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_MEGABASS,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_TREBLE,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_PARTY,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_POP,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_REGGAE,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_ROCK,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LNG_EQUALISER_SOFT,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

void Classical(GUI *data) 
{
  play_equaliser=0;
  GeneralFuncF1(1);
}

void Club(GUI *data) 
{
  play_equaliser=1;
  GeneralFuncF1(1);
}

void Dance(GUI *data) 
{
  play_equaliser=2;
  GeneralFuncF1(1);
}

void Bass(GUI *data) 
{
  play_equaliser=3;
  GeneralFuncF1(1);
}

void MegaBass(GUI *data) 
{
  play_equaliser=4;
  GeneralFuncF1(1);
}

void Treble(GUI *data) 
{
  play_equaliser=5;
  GeneralFuncF1(1);
}

void Party(GUI *data) 
{
  play_equaliser=6;
  GeneralFuncF1(1);
}

void Pop(GUI *data) 
{
  play_equaliser=7;
  GeneralFuncF1(1);
}

void Reggae(GUI *data) 
{
  play_equaliser=8;
  GeneralFuncF1(1);
}

void Rock(GUI *data) 
{
  play_equaliser=9;
  GeneralFuncF1(1);
}

void Soft(GUI *data) 
{
  play_equaliser=10;
  GeneralFuncF1(1);
}

const MENUPROCS_DESC equaliser_menu_hndls[EQUALISER_ITEMS_N]=
{
  Classical,
  Club,
  Dance,
  Bass,
  MegaBass,
  Treble,
  Party,
  Pop,
  Reggae,
  Rock,
  Soft
};

const MENU_DESC equaliser_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  equaliser_menu_items,
  equaliser_menu_hndls,
  EQUALISER_ITEMS_N
};

void Menu_Equaliser(GUI *data)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&equaliser_menu,&mm_menuhdr,0,EQUALISER_ITEMS_N,0,0);
  GeneralFuncF1(1);
}

#define MODE_ITEMS_N 3

MENUITEM_DESC mode_menu_items[MODE_ITEMS_N]=
{
  {NULL,(int)LGP_CYCLETOP2BOTTOM,LGP_NULL,0,NULL, MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_CYCLEBOTTOM2TOP,LGP_NULL,0,NULL, MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_SHUFFLE,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
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

const MENUPROCS_DESC mode_menu_hndls[MODE_ITEMS_N]=
{
  mode_t2b,
  mode_b2t,
  mode_shuf
};

const MENU_DESC mode_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  mode_menu_items,
  mode_menu_hndls,
  MODE_ITEMS_N
};

void Menu_Mode(GUI *data)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&mode_menu,&mm_menuhdr,0,MODE_ITEMS_N,0,0);
  GeneralFuncF1(1);
}

#define SUBMENU_ITEMS_N 2

MENUITEM_DESC submenu_menu_items[MODE_ITEMS_N]=
{
  {NULL,(int)LGP_HELP,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_RESPECTS,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

void Help(GUI *data)
{
  ShowMSG(1, (int)LGP_HELP);
}

void Respects(GUI *data)
{
  ShowMSG(1, (int)LGP_RESPECTS);
}

const MENUPROCS_DESC submenu_menu_hndls[MODE_ITEMS_N]=
{
  Help,
  Respects
};

const MENU_DESC submenu_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  submenu_menu_items,
  submenu_menu_hndls,
  SUBMENU_ITEMS_N
};

void Menu_SubMenu(GUI *data)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&submenu_menu,&mm_menuhdr,0,SUBMENU_ITEMS_N,0,0);
  GeneralFuncF1(1);
}

#define ITEMS_N 9

MENUITEM_DESC menu_items[ITEMS_N]=
{
  {NULL,(int)LGP_OPEN,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_PLAYMODE,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_POSITIONING,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_EQUALISER,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_EDITTAG,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_OPTIONS,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_SUBMENU,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_ABOUT,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LGP_EXIT,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

extern char procfile[128];

void Menu_Positioning(GUI *data)
{
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

void Menu_EditTag(GUI *data)
{
  //копируем путь к файлу, чтобы сохранить тег в нужный файл
  strcpy(tag_file_path,procfile);
  CreateTagMenu();
  GeneralFuncF1(1);
}

void Menu_Settings(GUI *data)
{
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

void Menu_About(GUI *data)
{
  ShowMSG(2, (int)COPYRIGHT);
  GeneralFuncF1(1);
}

void Menu_Exit(GUI *data)
{
  Exit();
}

const MENUPROCS_DESC menu_hndls[ITEMS_N]=
{
  Menu_Open,
  Menu_Mode,
  Menu_Positioning,
  Menu_Equaliser,
  Menu_EditTag,
  Menu_Settings,
  Menu_SubMenu,
  Menu_About,
  Menu_Exit,
};

const MENU_DESC mm_menu=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_sktm,
  0,
  NULL,
  menu_items,
  menu_hndls,
  ITEMS_N
};

void ShowMainMenu(void)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&mm_menu,&mm_menuhdr,0,ITEMS_N,0,0);
}



