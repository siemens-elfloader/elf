#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "spysok.h"
#include "conf_loader.h"
#include "mediafiles_base.h"
#include "tagmenu.h"
#include "rect_patcher.h"

extern char LastPlaylist[256];
extern const char playerfolder[128];

char *MakeGlobalString(const char *first, int breakchar, const char *last)
{
  int l;
  char *p;
  p=malloc((l=strlen(first))+strlen(last)+2);
  strcpy(p,first);
  if (breakchar)
    p[l++]=breakchar;
  strcpy(p+l,last);
  return p;
}

void About()
{
  ShowMSG(0,(int)LG_COPYRIGHT);
}

extern char now_play[256];

void Menu_EditTag(GUI *data)
{
  if(now_play!=0)//Только для музыки и плейлистов
  {
    CreateTagMenu();//Открываем окно редактора
    GeneralFuncF1(1);//Закрываем окошко меню
  }
  else ShowMSG(1,(int)"Файл не загружен!");//Если файл не загружен выводим соответствуещее сообщение
}

void CreateNewPlaylist()
{
  CLOSECURENTCSM();
  sprintf(LastPlaylist,"1.new");
  WriteLastPlaylist();
  WSHDR* w=AllocWS(128);
  wsprintf(w,"%sivoplay.elf",playerfolder);
  ExecuteFile(w,0,0);
  FreeWS(w);
}

IPC_REQ JaLiuBlIuJuliu;
void JaLiuBLiuPYVo()
{
   char ipcc[128];
   sprintf(ipcc,"%s%s","player_folder,menu\\playlist.png");
    JaLiuBlIuJuliu.name_from="Ivoplay";   
#ifdef NEWSGOLD
    JaLiuBlIuJuliu.name_to="control_panel|add_point|Ivoplay|ipcc|";
#else
    JaLiuBlIuJuliu.name_to="control_panel|add_point|Ivoplay|0:\\Zbin\\Ivoplay\\menu\\playlist.png|";
#endif
    JaLiuBlIuJuliu.data=0;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&JaLiuBlIuJuliu);
}


int menu_icons[10];
char menu_fold[256];
CSM_RAM *data;
int MainMenu_ID;

#ifndef VOVKA
  #define NUMITEMS 7
#else
  #define NUMITEMS 6
#endif

static const HEADER_DESC menuhdr={0,0,0,0,NULL,(int)LG_MENU,LGP_NULL};

static const int mmenusoftkeys[]={0,1,2};

static const char * const menutexts[NUMITEMS]=
{
  (char *)LG_MEDIAFILES,
  (char *)LG_ID3_EDITOR,
  (char *)LG_SELECT_PLAYLIST,
  (char *)LG_NEW_PLAYLIST,
  //LG_MEDIALIBRARY,
 (char *) LG_SKINS,
#ifndef VOVKA
  (char *)LG_ABOUT,
#endif
  (char *)LG_EXIT,
};

static const void *menuprocs[NUMITEMS]=
{
  (void *)CreateBaseOfMediafiles,
  (void *)Menu_EditTag,
  (void *)CreateMenuFindPlaylist,
  (void *)CreateNewPlaylist,
  //(void *)CreateMenuLibrary,
  (void *)CreateMenuSkins,
#ifndef VOVKA  
  (void *)About,
#endif
  (void *)CLOSECURENTCSM,
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
    SetMenuItemIconArray(data,item,menu_icons);
    break;
    case 1:
    SetMenuItemIconArray(data,item,menu_icons+1);
    break;
    case 2:
    SetMenuItemIconArray(data,item,menu_icons+2);
    break;
    case 3:
    SetMenuItemIconArray(data,item,menu_icons+3);
    break;
    /*case 4:
    SetMenuItemIconArray(data,item,icon_mediateka);
    break;*/
    case 4:
    SetMenuItemIconArray(data,item,menu_icons+4);
    break;
    case 5:
    SetMenuItemIconArray(data,item,menu_icons+5);
    break;
    case 6:
    SetMenuItemIconArray(data,item,menu_icons+6);
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
  sprintf(menu_fold,"%smenu",playerfolder);
  menu_icons[0]=(int)MakeGlobalString(menu_fold,'\\',"mediateka.png");
  menu_icons[1]=(int)MakeGlobalString(menu_fold,'\\',"tagedit.png");
  menu_icons[2]=(int)MakeGlobalString(menu_fold,'\\',"playlist.png");
  menu_icons[3]=(int)MakeGlobalString(menu_fold,'\\',"new_playlist.png");
  menu_icons[4]=(int)MakeGlobalString(menu_fold,'\\',"skins.png");
  menu_icons[5]=(int)MakeGlobalString(menu_fold,'\\',"about.png");
  menu_icons[6]=(int)MakeGlobalString(menu_fold,'\\',"exit.png");
  patch_header(&menuhdr);
  MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,NUMITEMS,0,0);
}
