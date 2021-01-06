#include "../inc/swilib.h"
#include "../inc/cfg_items.h"
#include "../inc/pnglist.h"
#include "NatICQ.h"
#include "history.h"
#include "mainmenu.h"
#include "main.h"
#include "conf_loader.h"
#include "status_change.h"
#include "language.h"
#include "revision.h"
#include "manage_cl.h"
#include "rect_patcher.h"
#include "cl_work.h"
#include "lang.h"

extern char *successed_config_filename;

//==============================================================================
int MainMenu_ID;

extern int CurrentStatus;
extern int CurrentXStatus;
extern DYNPNGICONLIST *XStatusesImgList;
extern int *XStatusesIconArray;
extern  int S_ICONS[];
extern const SOFTKEYSTAB menu_skt;

extern int Is_Vibra_Enabled;
extern int Is_Sounds_Enabled; 
extern int Is_Show_Offline;
extern int Is_Show_Groups;

static void ChangeVibraMode(void)
{
  Is_Vibra_Enabled=!(Is_Vibra_Enabled);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}
  
static void ChangeSoundMode(void)
{
  Is_Sounds_Enabled=!(Is_Sounds_Enabled);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static void ChangeShowOfflineMode(void)
{
  void RecountMenu(CLIST *req, int needfocus);
  Is_Show_Offline=!(Is_Show_Offline);
  SUBPROC((void*)WriteDefSettings);
  RecountMenu(NULL, 1);
  RefreshGUI();
}

static void ChangeShowGroupsMode(void)
{
  void RecountMenu(CLIST *req, int needfocus);
  Is_Show_Groups=!(Is_Show_Groups);
  SUBPROC((void*)WriteDefSettings);
  ResortCL();
  RecountMenu(NULL, 1);
  RefreshGUI();
}

static void EditConfig(void)
{
  OpenConfig();
}

static void Disconnect(void)
{
  extern volatile int disautorecconect;
  disautorecconect=1;
  extern void end_socket(void);
  SUBPROC((void*)end_socket);
  GeneralFuncF1(1);
}

static void PingToServer(void)
{
  TPKT *p;
  p=malloc(sizeof(PKT)+sizeof(TTime));
  GetDateTime(NULL,(TTime *)p->data);
  p->pkt.uin=0;
  p->pkt.type=T_ECHO;
  p->pkt.data_len=sizeof(TTime);
  SUBPROC((void *)SendAnswer,0,p);
}

static void AboutDlg()
{
  char s[256];
  snprintf(s,255,LG_COPYRIGHT,__SVN_REVISION__);
  ShowMSG(2, (int)s);
}

static HEADER_DESC menuhdr={0,0,0,0,NULL,NULL,LGP_NULL};

static const int mmenusoftkeys[]={0,1,2};

static char * menutexts[11]=
{
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

/*MENUITEM_DESC menuitems[7]=
{
  {S_ICONS,    (int)LG_MNUSTATUS,  LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,       (int)LG_MNUADDCONT, LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {icon_array, (int)LG_MNUVIBRA,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {icon_array, (int)LG_MNUSOUND,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,       (int)LG_MNUEDCFG,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,       (int)LG_MNUPING ,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {S_ICONS,    (int)LG_MNUABOUT,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};*/

static const void *menuprocs[11]=
{
  (void *)DispStatusChangeMenu,
  (void *)DispXStatusChangeMenu,
  (void *)CreateManageCLMenu,
  (void *)ChangeVibraMode,
  (void *)ChangeSoundMode,
  (void *)ChangeShowOfflineMode,
  (void *)ChangeShowGroupsMode,
  (void *)EditConfig,
  (void *)Disconnect,
  (void *)PingToServer,
  (void *)AboutDlg,
};

static SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

void tmenu_ghook(void *data, int cmd)
{
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    pltop->dyn_pltop=XStatusesImgList;
    DisableIDLETMR();
  }
}

static int icon_array[2];

static void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  extern const char percent_t[];
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws,percent_t,menutexts[curitem]);
  switch(curitem)
  {
  case 0:
    SetMenuItemIconArray(data,item,S_ICONS+CurrentStatus);
    break;
  case 1:
    SetMenuItemIconArray(data,item,XStatusesIconArray+CurrentXStatus);
    break;
  case 2:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_ADDCONTACT);
    break;
  case 3:
    SetMenuItemIconArray(data,item,icon_array+(Is_Vibra_Enabled?0:1));
    break;
  case 4:
    SetMenuItemIconArray(data,item,icon_array+(Is_Sounds_Enabled?0:1));
    break;
  case 5:
    SetMenuItemIconArray(data,item,icon_array+(Is_Show_Offline?0:1));
    break;
  case 6:
    SetMenuItemIconArray(data,item,icon_array+(Is_Show_Groups?0:1));
    break;    
  case 7:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_SETTINGS);
    break;
  case 8:
    SetMenuItemIconArray(data,item,S_ICONS+IS_OFFLINE);
    break;
  case 9:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_PING);
    break;
  case 10:
    SetMenuItemIconArray(data,item,S_ICONS+IS_UNKNOWN);
    break;
  }
  SetMenuItemText(data, item, ws, curitem);
}

static int tmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
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
  11
};

void ShowMainMenu()
{
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);

  //Инициализация ленгпака
  menuhdr.lgp_id=(int)lgpData[LGP_Menu];
  
  mmenu_sk[0].lgp_id=(int)lgpData[LGP_Select];
  mmenu_sk[1].lgp_id=(int)lgpData[LGP_Back];
  
  menutexts[0]=(char *)lgpData[LGP_MnuStatus];
  menutexts[1]=(char *)lgpData[LGP_MnuXStatus];
  menutexts[2]=(char *)lgpData[LGP_ManageList];
  menutexts[3]=(char *)lgpData[LGP_MnuVibra];
  menutexts[4]=(char *)lgpData[LGP_MnuSound];
  menutexts[5]=(char *)lgpData[LGP_MnuShowOff];
  menutexts[6]=(char *)lgpData[LGP_MnuShowGroup];
  menutexts[7]=(char *)lgpData[LGP_MnuEdCfg];
  menutexts[8]=(char *)lgpData[LGP_MnuDisconnect];
  menutexts[9]=(char *)lgpData[LGP_MnuPing];
  menutexts[10]=(char *)lgpData[LGP_MnuAbout];
  
  *((int **)(&menuhdr.icon))=S_ICONS+IS_ONLINE;
  patch_header(&menuhdr);
  MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,11,0,0);
}
