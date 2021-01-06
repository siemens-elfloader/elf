#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "spysok.h"
#include "conf_loader.h"
#include "mediafiles_base.h"

extern const char playerfolder[128];

void About()
{
  ShowMSG(0,(int)LG_COPYRIGHT);
}


void CreateNewPlaylist()
{
  CLOSECURENTCSM();
  WSHDR* w=AllocWS(128);
  wsprintf(w,"%sivoplay.elf",playerfolder);
  ExecuteFile(w,0,"1.new");
  FreeWS(w);
}
IPC_REQ JaLiuBlIuJuliu;
void JaLiuBLiuPYVo()
{
    JaLiuBlIuJuliu.name_from="Ivoplay";    
    JaLiuBlIuJuliu.name_to="control_panel|add_point|Ivoplay|0:\\Zbin\\Ivoplay\\menu\\playlist.png|";
    JaLiuBlIuJuliu.data=0;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&JaLiuBlIuJuliu);
}

void Cleaner()
{
  WSHDR* w=AllocWS(128);
  wsprintf(w,"%scleaner.elf",playerfolder);
  ExecuteFile(w,0,"");
  FreeWS(w);
}

CSM_RAM *data;
int MainMenu_ID;

int icon_mediateka[] = {(int)"0:\\Zbin\\Ivoplay\\menu\\mediateka.png",0};
int icon_playlist[] = {(int)"0:\\Zbin\\Ivoplay\\menu\\playlist.png",0};
int icon_new_playlist[] = {(int)"0:\\Zbin\\Ivoplay\\menu\\new_playlist.png",0};
int icon_about[] = {(int)"0:\\Zbin\\Ivoplay\\menu\\about.png",0};



#define NUMITEMS 5

static void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()-1+YDISP;
}



static const HEADER_DESC menuhdr={0,0,0,0,NULL,(int)LG_MENU,LGP_NULL};

static const int mmenusoftkeys[]={0,1,2};

static const char * const menutexts[NUMITEMS]=
{
  LG_MEDIALIBRARY,
  LG_SELECT_PLAYLIST,
  LG_NEW_PLAYLIST,
  LG_ABOUT,
  LG_MEDIAFILES,
};

static const void *menuprocs[NUMITEMS]=
{
  (void *)CreateMenuLibrary,
  (void *)CreateMenuFindPlaylist,
  (void *)CreateNewPlaylist,
  (void *)About,
  (void *)CreateBaseOfMediafiles,
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

void tmenu_ghook(void *data, int cmd)
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

static void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws,pt,menutexts[curitem]);
  switch(curitem)
  {
    case 0:
    SetMenuItemIconArray(data,item,icon_mediateka);
    break;
    case 1:
    SetMenuItemIconArray(data,item,icon_playlist);
    break;
    case 2:
    SetMenuItemIconArray(data,item,icon_new_playlist);
    break;
    case 3:
    SetMenuItemIconArray(data,item,icon_about);
    break;
    case 4:
    SetMenuItemIconArray(data,item,icon_mediateka);
    break;
  }
  SetMenuItemText(data, item, ws, curitem);
}

static int tmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
    if (GetCurMenuItem(data)==2) {return(1);}
  }
  return(0);
}


static const MENU_DESC tmenu=
{
  8,tmenu_keyhook,tmenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x11,//MENU_FLAG,
  menuitemhandler,
  NULL,//menuitems,
  NULL,//menuprocs,
  NUMITEMS
};

void CloseMAINMENU()
{
  GeneralFunc_flag1 (MainMenu_ID,1);
}

void ShowMainMenu()
{
  patch_header(&menuhdr);
  MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,NUMITEMS,0,0);
}
