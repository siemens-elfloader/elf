#include "C:/arm/inc/swilib.h"
//#include "elfsubmainmenu.h"
#include "elfgroop.h"
#include "main.h"
#define LEVELS_NUM 6
int GroopMainMenu_ID;

//==============================================================================

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

//==============================================================================

void  System(GUI *data){Sys();};
void  Internet(GUI *data){Int();};
void  Games(GUI *data){Gam();};
void  Utilities(GUI *data){Uti();};
void  Multimedia(GUI *data){Mlt();};

#ifdef ELKA
int mnu_icon[]={0x358,0};
int sys_icon[]={0x352,0};
int int_icon[]={0x2C7,0};
int gam_icon[]={0x3CA,0};
int uti_icon[]={0x2C9,0};
int mlt_icon[]={0x045,0};
#else
#ifdef NEWSGOLD
int mnu_icon[]={0x33B,0};
int sys_icon[]={0x148,0};
int int_icon[]={0x22C,0};
int gam_icon[]={0x3E9,0};
int uti_icon[]={0x22E,0};
int mlt_icon[]={0x062,0};
#else
int mnu_icon[]={0xFA0,0};
int sys_icon[]={0xFA0,0};
int int_icon[]={0xFA0,0};
int gam_icon[]={0xFA0,0};
int uti_icon[]={0xFA0,0};
int mlt_icon[]={0xFA0,0};
#endif
#endif

int gimmenusoftkeys[]={0,1,2};
HEADER_DESC gimenuhdr={0,0,131,21,mnu_icon,(int)"Группы:",0x7FFFFFFF};

static const MENUPROCS_DESC menuprocs[LEVELS_NUM]=
{
System,
Internet,
Games,
Utilities,
Multimedia
};

void gimmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int immenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const SOFTKEY_DESC immenu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Назад"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB immenu_skt={immenu_sk,0};

MENUITEM_DESC gmenuitems[LEVELS_NUM]=
{
{sys_icon,(int)"Системные",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{int_icon,(int)"Интернет",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{gam_icon,(int)"Игры",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{uti_icon,(int)"Утилиты",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
{mlt_icon,(int)"Мультимедиа",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

static const MENU_DESC itmenu=
{
  8,immenu_keyhook,gimmenu_ghook,NULL,
  gimmenusoftkeys,
  &immenu_skt,
  1,
  NULL,
  gmenuitems, 
  menuprocs, 
  LEVELS_NUM
};

void GetGroopMenu()
{
  patch_header(&gimenuhdr);
  GroopMainMenu_ID = CreateMenu(0,0,&itmenu,&gimenuhdr,0,LEVELS_NUM ,0,0);
};
