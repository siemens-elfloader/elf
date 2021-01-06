#include "..\inc\swilib.h"
#include "gui.h"
#include "ed_gui.h"
#include "rect_patcher.h"

extern int is_ed_started;

#ifdef NEWSGOLD
#define LGP_SEL 0x3B
#define LGP_BACK 0x3FC
#else
#define LGP_SEL 0x1A0
#define LGP_BACK 0x411
#endif

const int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_skm[]=
{
  {0x0018,0x0000,(int)LGP_SEL},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_sktm=
{
  menu_skm,0
};

#define ITEMS_N 4

MENUITEM_DESC menu_items[ITEMS_N]=
{
  {NULL,(int)"Input",         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Options",       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"About",         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Exit",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

void input(GUI *data)
{
  create_ed();
}

void options(GUI *data)
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(128);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

void v_about(GUI *data)
{
  is_ed_started=0;
  create_gui();
}

void exit(GUI *data)
{
  quit();
}

const MENUPROCS_DESC menu_hndls[ITEMS_N]=
{
  input,
  options,
  v_about,
  exit,
};

HEADER_DESC mm_menuhdr={0,0,0,0,NULL,(int)"ECDict",LGP_NULL};

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

void create_menu(void)
{
  patch_header(&mm_menuhdr);
  CreateMenu(0,0,&mm_menu,&mm_menuhdr,0,ITEMS_N,0,0);
}

