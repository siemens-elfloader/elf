#include "../inc/swilib.h"
#include "main.h"
#include "roster_icons.h"
#include "mainmenu.h"
#include "status_change.h"
#include "bookmarks.h"
#include "jabber_util.h"
#include "MUC_Enter_UI.h"
#include "JID_Enter_UI.h"
#include "cont_menu.h"
#include "revision.h"
#include "lang.h"
#include "clist_util.h"
#include "string_util.h"
#include "color.h"
#include "rect_patcher.h"

#define N_ITEMS 15

extern int Is_Sounds_Enabled;
extern int Is_Vibra_Enabled;
extern char Display_Offline;
extern int Is_Autostatus_Enabled;
extern int Is_Playerstatus_Enabled;
extern int Is_Smiles_Enabled;

int MainMenu_ID;

extern char My_Presence;

extern const char VERSION_VERS[];

void AboutDlg(GUI *data)
{
  char msg_tpl[]=LG_COPYRIGHT;
  int l;
  char *msg = malloc(l=strlen(msg_tpl)+20+1);
  snprintf(msg,l,msg_tpl, VERSION_VERS, __SVN_REVISION__, __DATE__);
  ShowMSG(0,(int)msg);
  mfree(msg);
};

void Dummy(GUI *data)
{
  ShowMSG(1,(int)"正在建设中 :)");
};

// Ad, сюда напиши номера, которые сочтёшь нужным!
int icon[]={0x3DB,0};
int about_icon[]={0x4DB,0};
int dummy_icon[] = {0x50E,0};

HEADER_DESC menuhdr={0,0,131,21,NULL,(int)LG_MENU,LGP_NULL};

int mmenusoftkeys[]={0,1,2};

int icon_array[2];
extern JABBER_STATE Jabber_state; 

void ChangeVibraMode(GUI *data)
{
  Is_Vibra_Enabled=!(Is_Vibra_Enabled);
  RefreshGUI();
}

void ChangeSoundMode(GUI *data)
{
  Is_Sounds_Enabled=!(Is_Sounds_Enabled);
  RefreshGUI();
}

void ChangeAutostatusMode(GUI *data)
{
  Is_Autostatus_Enabled=!(Is_Autostatus_Enabled);
  RefreshGUI();
}

void ChangePlayerstatusMode(GUI *data)
{
  Is_Playerstatus_Enabled=!(Is_Playerstatus_Enabled);
  RefreshGUI();
}

void ChangeSmilesMode(GUI *data)
{
  Is_Smiles_Enabled=!(Is_Smiles_Enabled);
  RefreshGUI();
}

void ChangeOffContMode(GUI *data)
{
  CList_ToggleOfflineDisplay();
  RefreshGUI();
}

void OpenSettings_(GUI *data)
{
  OpenSettings();
  GeneralFuncF1(1);
}

void AddContact(GUI *data)
{
 if(Jabber_state==JS_ONLINE)
 {
  Disp_JID_Enter_Dialog(NULL);
 }
}

void OpenBookmarks_List(GUI *data)
{
  if(Jabber_state==JS_ONLINE)
  {
  Get_Bookmarks_List();
  }
}
void OpenDisp_MUC_Enter_Dialog(GUI *data)
{
  if(Jabber_state==JS_ONLINE)
  {
    Disp_MUC_Enter_Dialog();
  }
}

void Exit_SieJC(GUI *data)
{
  QuitCallbackProc(0);
  GeneralFuncF1(1);
}

static const char * const menutexts[N_ITEMS]=
{
  LG_CONTACT,
  LG_STATUS,
  LG_MUC,
  LG_BOOKMARK,
  LG_ADDCONTACT,
  LG_MVIBRA,
  LG_MSOUND,
  LG_MOFFLINE,
  LG_AUTOSTATUS,
  LG_PLAYER_STATUS,
  LG_SMILE,
  LG_SETTINGS,
  LG_COLOR,
  LG_ABOUT,
  LG_EXIT,
  
};


//MENUITEM_DESC menuitems[N_ITEMS]=
//{
//  {dummy_icon,(int)"Контакт",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//  {dummy_icon,(int)"Статус",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//  {dummy_icon,(int)"Конференция",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//  {dummy_icon,(int)"Закладки",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//  {icon_array,(int)"Режим вибры",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//  {icon_array,(int)"Режим звука",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//  {dummy_icon,(int)"Об эльфе...",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//  {dummy_icon,(int)"Выход",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//};

static const MENUPROCS_DESC menuprocs[N_ITEMS]={
                          Disp_Contact_Menu,
                          DispStatusChangeMenu,
                          OpenDisp_MUC_Enter_Dialog,
                          OpenBookmarks_List,
                          AddContact,
                          ChangeVibraMode,
                          ChangeSoundMode,
                          ChangeOffContMode,
                          ChangeAutostatusMode,
                          ChangePlayerstatusMode,
                          ChangeSmilesMode,
                          OpenSettings_,
                          ShowSelectColorMenu,
                          AboutDlg,
                          Exit_SieJC
                         };

static const SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

int S_ICONS[N_ITEMS];

void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  ascii2ws(ws, menutexts[curitem]);
  switch(curitem)
  {
  case 0: SetMenuItemIconArray(data,item,S_ICONS+0); break;
  case 1: SetMenuItemIconArray(data,item,S_ICONS+1); break;
  case 2: SetMenuItemIconArray(data,item,S_ICONS+2); break;
  case 3: SetMenuItemIconArray(data,item,S_ICONS+3); break;
  case 4: SetMenuItemIconArray(data,item,S_ICONS+4); break;
  case 5: SetMenuItemIconArray(data,item,icon_array+(Is_Vibra_Enabled?0:1)); break;
  case 6:
    SetMenuItemIconArray(data,item,icon_array+(Is_Sounds_Enabled?0:1));
    break;
  case 7:
    SetMenuItemIconArray(data,item,icon_array+(Display_Offline?0:1));
    break;
  case 8:
    SetMenuItemIconArray(data,item,icon_array+(Is_Autostatus_Enabled?0:1));
    break;
  case 9:
    SetMenuItemIconArray(data,item,icon_array+(Is_Playerstatus_Enabled?0:1));
    break;
  case 10:
    SetMenuItemIconArray(data,item,icon_array+(Is_Smiles_Enabled?0:1));
    break;
  case 11:
    SetMenuItemIconArray(data,item,S_ICONS+6);
    break;
  case 12:
    SetMenuItemIconArray(data,item,S_ICONS+9);
    break;
  case 13:
    SetMenuItemIconArray(data,item,S_ICONS+7);
    break;  
  case 14:
    SetMenuItemIconArray(data,item,S_ICONS+8);
    break;
  }
  SetMenuItemText(data, item, ws, curitem);
}

void mmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int mmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC tmenu=
{
  8,mmenu_keyhook,mmenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x11,
  menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  N_ITEMS
};
extern const char PATH_TO_PIC[128], png_t[];
char mypic[128];
char confpic[128];
char exitpic[128];
char infopic[128];
char settpic[128];
char aboutpic[128];
char color_icon[128];
extern const char conference_t[];
const char exit_t[] = "exit";
const char info_t[] = "info";
const char about_t[] = "about";
const char sett_t[] = "settings";
const char coloricon[] = "coloricon";


void MM_Show()
{
#ifdef USE_PNG_EXT
  // Контакт
  strcpy(infopic, PATH_TO_PIC);
  strcat(infopic,info_t);
  strcat(infopic,png_t);
  S_ICONS[0] = (int)infopic;

  // Статус
  Roster_getIconByStatus(mypic, My_Presence);
  S_ICONS[1] = (int)mypic;

  //Конференция...
  strcpy(confpic, PATH_TO_PIC);
  strcat(confpic,conference_t);
  strcat(confpic,png_t);
  S_ICONS[2] = (int)confpic;

  // Закладки
  S_ICONS[3] = (int)confpic;

  // Add Contact
  S_ICONS[4] = (int)confpic;

  // Режим звука
  // S_ICONS[5]

  // Настройки
  strcpy(settpic, PATH_TO_PIC);
  strcat(settpic,sett_t);
  strcat(settpic,png_t);
  S_ICONS[6] = (int)settpic;  

  //цвета
  strcpy(color_icon, PATH_TO_PIC);
  strcat(color_icon,coloricon);
  strcat(color_icon,png_t);
  S_ICONS[9] =(int)color_icon;
  // Об эльфе...
  strcpy(aboutpic, PATH_TO_PIC);
  strcat(aboutpic,about_t);
  strcat(aboutpic,png_t);
  S_ICONS[7] = (int)aboutpic;

  // Выход
  strcpy(exitpic, PATH_TO_PIC);
  strcat(exitpic,exit_t);
  strcat(exitpic,png_t);
  S_ICONS[8] = (int)exitpic;

//  menuitems[0].icon = S_ICONS+0;
//  menuitems[1].icon = S_ICONS+1;
//  menuitems[2].icon = S_ICONS+2;
//  menuitems[3].icon = S_ICONS+3;
//  menuitems[6].icon = S_ICONS+6;
//  menuitems[7].icon = S_ICONS+7;


#else
  S_ICONS[0] = Roster_getIconByStatus(My_Presence);
//  menuitems[1].icon = S_ICONS;
#endif

  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);

  patch_header(&menuhdr);
  MainMenu_ID = CreateMenu(0,0,&tmenu,&menuhdr,0,N_ITEMS,0,0);
}
