#include "../inc/swilib.h"
#include "medialibrary.h"
#include "language.h"
#include "main.h"
#include "conf_loader.h"

extern const char folder[128];
const char my_ipc_name[32]="Ivoplay";
void CreateMEDIALibrary()
{
  char t[128];
  sprintf(t,folder);
  CreateMediaLibrary(t);
}

void PerevirkaVidpovidnosti()
{
  char t[128];
  sprintf(t,folder);
  BEER(t);
}



CSM_RAM *data_library;
int LibraryMenu_ID;

int icon_create[] = {(int)"0:\\1.png",0};
int icon_gy[] = {(int)"0:\\2.png",0};
//int icon3[] = {(int)"0:\\3.png",0};


#define NUMITEMS 2

static void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()-1+YDISP;
}



static const HEADER_DESC menuhdr={0,0,0,0,NULL,(int)LG_MEDIALIBRARY,LGP_NULL};

static const int mmenusoftkeys[]={0,1,2};

static const char * const menutexts[NUMITEMS]=
{
  LG_CREATE_MEDIALIBRARY,
  LG_PEREVIRYTY,
  //"ร่",
};

static const void *menuprocs[NUMITEMS]=
{
  (void *)CreateMEDIALibrary,
  (void *)PerevirkaVidpovidnosti,
  //(void *)CreateRemotePlayerControler,
};

static const SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

void tmenu_ghook_library(void *data_library, int cmd)
{
  //PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    //pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    //pltop->dyn_pltop=XStatusesImgList;
    DisableIDLETMR();
  }
}
//static int icon_array[2];

static void menuitemhandler(void *data_library, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data_library);
  ws=AllocMenuWS(data_library,strlen(menutexts[curitem]));
  wsprintf(ws,pt,menutexts[curitem]);
  switch(curitem)
  {
    case 0:
    SetMenuItemIconArray(data_library,item,icon_create);
    break;
    case 1:
    SetMenuItemIconArray(data_library,item,icon_gy);
    break;
    /*case 2:
    SetMenuItemIconArray(data_library,item,icon3);
    break;*/
  }
  SetMenuItemText(data_library, item, ws, curitem);
}

static int tmenu_keyhook(void *data_library, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data_library)]))();
  }
  return(0);
}


static const MENU_DESC tmenu=
{
  8,tmenu_keyhook,tmenu_ghook_library,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x11,//MENU_FLAG,
  menuitemhandler,
  NULL,//menuitems,
  NULL,//menuprocs,
  NUMITEMS
};

void CreateMenuLibrary()
{
  patch_header(&menuhdr);
  LibraryMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,NUMITEMS,0,0);
}
