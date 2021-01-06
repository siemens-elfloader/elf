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
#include "moods.h"

#define MAX_MMITEMS 15       // Максимальное количество пунктов меню

extern int Is_Sounds_Enabled;
extern int Is_Vibra_Enabled;
extern char Display_Offline;
extern int Is_Autostatus_Enabled;
extern int Is_Smiles_Enabled;

extern char My_Presence;

extern const char VERSION_VERS[];

#define MM_CONTACT     		1
#define MM_STATUS    		2
#define MM_MUC     		3
#define MM_BOOKMARK      	4
#define MM_ADDCONTACT     	5
#define MM_VIBRA_MODE       	6
#define MM_SOUND_MODE      	7
#define MM_OFFCONTACT_MODE      8
#define MM_MOODS      		9
#define MM_AUTOSTATUS_MODE  	10
#define MM_OPEN_CONFIG  	11
#define MM_OPEN_COLOR_CONFIG    12
#define MM_ABOUT      		13
#define MM_EXIT      		14
#define MM_SMILE_MODE  		15

void AboutDlg(void)
{
  char msg_tpl[]=LG_COPYRIGHT;
  int l;
  char *msg = malloc(l=strlen(msg_tpl)+20+1);
  snprintf(msg,l,msg_tpl, VERSION_VERS, __SVN_REVISION__, __DATE__);
  ShowMSG(0,(int)msg);
  mfree(msg);
};

char MMenu_Contents[MAX_MMITEMS-1];
int cmMS_ICONS[MAX_MMITEMS+1];
int MainMenu_ID;

//int Req_Close_Cont_Menu=0;
HEADER_DESC menuhdr={0,0,131,21,NULL,(int)LG_MENU,LGP_NULL};
int mmenusoftkeys[]={0,1,2};
int icon_array[2];

SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

void mmenu_ghook(void *data, int cmd);
int mmenu_keyhook(void *data, GUI_MSG *msg);
void menuitemhandler(void *data, int curitem, void *unk);

MENU_DESC tmenu=
{
  8,mmenu_keyhook,mmenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x11,
  menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  MAX_MMITEMS
};

void mmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

/*
Обработчик нажатий клавиш меню. Отсюда следует вызывать необходимые действия

*/

int mmenu_keyhook(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    switch(MMenu_Contents[i])
    {
    case MM_CONTACT:
      {
        Disp_Contact_Menu();
        break;
      }
    case MM_STATUS:
      {
      ShowStatusSelectMenu();
      break;
      }
    case MM_MUC:
      {
      Disp_MUC_Enter_Dialog(NULL,NULL,NULL);
      break;
      }
    case MM_BOOKMARK:
      {
      Get_Bookmarks_List();
      GeneralFuncF1(1);
      break;
      }
    case MM_ADDCONTACT:
      {
	Disp_JID_Enter_Dialog(NULL);
      break;
      }
    case MM_VIBRA_MODE:
      {
	Is_Vibra_Enabled=!(Is_Vibra_Enabled);
        cmMS_ICONS[MM_VIBRA_MODE]=(int)icon_array[Is_Vibra_Enabled];
	RefreshGUI();
      break;
      }
    case MM_SOUND_MODE:
      {
	Is_Sounds_Enabled=!(Is_Sounds_Enabled);
        cmMS_ICONS[MM_SOUND_MODE]=(int)icon_array[Is_Sounds_Enabled];
	RefreshGUI();
      break;
      }
    case MM_OFFCONTACT_MODE:
      {
	CList_ToggleOfflineDisplay();
        cmMS_ICONS[MM_OFFCONTACT_MODE]=(int)icon_array[Display_Offline];
	RefreshGUI();
      break;
      }
    case MM_AUTOSTATUS_MODE:
      {
        Is_Autostatus_Enabled=!(Is_Autostatus_Enabled);
        cmMS_ICONS[MM_AUTOSTATUS_MODE]=(int)icon_array[Is_Autostatus_Enabled];
	RefreshGUI();
	break;
	}
    case MM_OPEN_CONFIG:
      {
	OpenSettings();
	GeneralFuncF1(1);
      break;
      }
      
    case MM_OPEN_COLOR_CONFIG:
      {
       ShowSelectColorMenu();
        break;
      }
    case MM_ABOUT:
      {
        AboutDlg();
        break;
      }
    case MM_EXIT:
      {
	QuitCallbackProc(0);
        GeneralFuncF1(1);
        break;
      }      
    case MM_SMILE_MODE:
      {
        Is_Smiles_Enabled=!(Is_Smiles_Enabled);
        cmMS_ICONS[MM_SMILE_MODE]=(int)icon_array[Is_Smiles_Enabled];
	RefreshGUI();
        break;
      }
    case MM_MOODS:
      {
        Show_Moods_Menu();
        break;
      }
    default:
      {
        MsgBoxError(1,(int)LG_UNKACTION);
      }
    }
    return 0;
  }
  //  Req_Close_Cont_Menu = 1;
  return 0;
}

void InitMMenuArray()
{
  for(int i=0;i<MAX_MMITEMS;i++)MMenu_Contents[i]=0;
}

/*
Обработчик появления пунктов динамического меню
Тут мы сами создаём каждый пункт, указывая для него иконку и текст.
При создании мы опираемся на данные массива MMenu_Contents, в котором описано,
какие пункты и в каком порядке необходимо создать.
*/
void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  char test_str[48];
  void *item=AllocMenuItem(data);
  strcpy(test_str,"(ошибка)");

  switch(MMenu_Contents[curitem])
  {
    case MM_CONTACT:
      {
      strcpy(test_str,LG_CONTACT);
        break;
      }
    case MM_STATUS:
      {
      strcpy(test_str,LG_STATUS);
        break;
      }
    case MM_MUC:
      {
      strcpy(test_str,LG_MUC);
        break;
      }
    case MM_BOOKMARK:
      {
      strcpy(test_str,LG_BOOKMARK);
        break;
      }
    case MM_ADDCONTACT:
      {
      strcpy(test_str,LG_ADDCONTACT);
        break;
      }
    case MM_VIBRA_MODE:
      {
      strcpy(test_str,LG_MVIBRA);
        break;
      }
    case MM_SOUND_MODE:
      {
      strcpy(test_str,LG_MSOUND);
        break;
      }
  case MM_OFFCONTACT_MODE:
      {
      strcpy(test_str,LG_MOFFLINE);
        break;
      }
    case MM_AUTOSTATUS_MODE:
      {
      strcpy(test_str,LG_AUTOSTATUS);
        break;
      }
    case MM_OPEN_CONFIG:
      {
      strcpy(test_str,LG_SETTINGS);
        break;
      }
    case MM_OPEN_COLOR_CONFIG:
      {
      strcpy(test_str,LG_COLOR);
        break;
      }
    case MM_ABOUT:
      {
      strcpy(test_str,LG_ABOUT);
        break;
      }
    case MM_EXIT:
      {
      strcpy(test_str,LG_EXIT);
        break;
      }
    case MM_SMILE_MODE:
      {
      strcpy(test_str,LG_SMILE);
        break;
      }
    case MM_MOODS:
      {
      strcpy(test_str,LG_MOODS);
        break;
      }
  }

  ws=AllocMenuWS(data,strlen(test_str));
  ascii2ws(ws, test_str);

  SetMenuItemIconArray(data,item,cmMS_ICONS+MMenu_Contents[curitem]);
  SetMenuItemText(data,item,ws,curitem);
};

extern const char PATH_TO_PIC[128];
char ICON_INFO[128];
char ICON_STATUS[128];
char ICON_MUCM[128];
char ICON_BOOKMARK[128];
char ICON_ADDCONT[128];
//char ICON_VIBRA[128];
//char ICON_SOUND[128];
//char ICON_OFFCONTACT[128];
//char ICON_IPCSTSTUS[128];
//char ICON_AUTOSTATUS[128];
//char ICON_SMILE[128];
//char ICON_MOODS[128];
char ICON_SETTING[128];
char ICON_COLOR[128];
char ICON_ABOUT[128];
char ICON_EXIT[128];

void Init_MMIcon_array()
{
  strcpy(ICON_INFO, PATH_TO_PIC);strcat(ICON_INFO, "info.png");
  strcpy(ICON_MUCM, PATH_TO_PIC);strcat(ICON_MUCM, "conference.png");
  strcpy(ICON_BOOKMARK, PATH_TO_PIC);strcat(ICON_BOOKMARK, "conference.png");
  strcpy(ICON_ADDCONT, PATH_TO_PIC);strcat(ICON_ADDCONT, "conference.png");
/* ICON_VIBRA
  ICON_SOUND
  ICON_OFFCONTACT
  ICON_IPCSTSTUS
  ICON_AUTOSTATUS
  ICON_SMILE
  ICON_MOODS*/
  strcpy(ICON_SETTING, PATH_TO_PIC);strcat(ICON_SETTING, "settings.png");
  strcpy(ICON_COLOR, PATH_TO_PIC);strcat(ICON_COLOR, "coloricon.png");
  strcpy(ICON_ABOUT, PATH_TO_PIC);strcat(ICON_ABOUT, "about.png");
  strcpy(ICON_EXIT, PATH_TO_PIC);strcat(ICON_EXIT, "exit.png");
  Roster_getIconByStatus(ICON_STATUS, My_Presence);
  
  for(int i=0;i<=MAX_MMITEMS;i++)cmMS_ICONS[i]=0;

  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  cmMS_ICONS[MM_VIBRA_MODE]=(int)icon_array[Is_Vibra_Enabled];
  cmMS_ICONS[MM_SOUND_MODE]=(int)icon_array[Is_Sounds_Enabled];
  cmMS_ICONS[MM_OFFCONTACT_MODE]=(int)icon_array[Display_Offline];
  cmMS_ICONS[MM_AUTOSTATUS_MODE]=(int)icon_array[Is_Autostatus_Enabled];
  cmMS_ICONS[MM_SMILE_MODE]=(int)icon_array[Is_Smiles_Enabled];

  cmMS_ICONS[MM_CONTACT]=(int)ICON_INFO;
  cmMS_ICONS[MM_STATUS]=(int)ICON_STATUS;
  cmMS_ICONS[MM_MUC]=(int)ICON_MUCM;
  cmMS_ICONS[MM_BOOKMARK]=(int)ICON_BOOKMARK;
  cmMS_ICONS[MM_ADDCONTACT]=(int)ICON_ADDCONT;
  cmMS_ICONS[MM_OPEN_CONFIG]=(int)ICON_SETTING;
  cmMS_ICONS[MM_OPEN_COLOR_CONFIG]=(int)ICON_COLOR;
  cmMS_ICONS[MM_ABOUT]=(int)ICON_ABOUT;
  cmMS_ICONS[MM_EXIT]=(int)ICON_EXIT;
  cmMS_ICONS[MM_MOODS]=(int)ICON_STATUS;
}

void MM_Show()
{
  extern const int AUTOSTATUS_ENABLED;
  extern JABBER_STATE Jabber_state; 
  int n_items=0;
  InitMMenuArray();
  Init_MMIcon_array();
  if(Jabber_state==JS_ONLINE)
  {  
  MMenu_Contents[n_items++]=MM_CONTACT;
  MMenu_Contents[n_items++]=MM_STATUS;
  MMenu_Contents[n_items++]=MM_MOODS;
  MMenu_Contents[n_items++]=MM_MUC;
  MMenu_Contents[n_items++]=MM_BOOKMARK;
  MMenu_Contents[n_items++]=MM_ADDCONTACT;
  }
  MMenu_Contents[n_items++]=MM_VIBRA_MODE;
  MMenu_Contents[n_items++]=MM_SOUND_MODE;
  MMenu_Contents[n_items++]=MM_OFFCONTACT_MODE;
  if(AUTOSTATUS_ENABLED) MMenu_Contents[n_items++]=MM_AUTOSTATUS_MODE;
  MMenu_Contents[n_items++]=MM_SMILE_MODE;
  MMenu_Contents[n_items++]=MM_OPEN_CONFIG;
  MMenu_Contents[n_items++]=MM_OPEN_COLOR_CONFIG;
  MMenu_Contents[n_items++]=MM_ABOUT;
  MMenu_Contents[n_items++]=MM_EXIT;

  if(n_items)
  {
    patch_rect(&menuhdr.rc,0,YDISP,ScreenW()-1,HeaderH()+YDISP);
    MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,n_items,0,0);
  }
}
//EOL,EOF
