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

//==============================================================================
int MainMenu_ID;

extern int CurrentStatus;
extern int CurrentXStatus;
extern DYNPNGICONLIST *XStatusesImgList;
extern int *XStatusesIconArray;
extern  int S_ICONS[];
extern const SOFTKEYSTAB menu_skt;

#ifdef EVILFOX
extern int Is_SLI_On;
extern int Is_ILU_On;
extern int Is_INC_On;
extern int in_count;
extern int out_count;

static void ChangeSLIMode(void)
{
  Is_SLI_On=!(Is_SLI_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static void ChangeILUMode(void)
{
  Is_ILU_On=!(Is_ILU_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static void ChangeINCMode(void)
{
  Is_INC_On=!(Is_INC_On);
  SUBPROC((void*)WriteDefSettings);
  RefreshGUI();
}

static void ShowMSGCount(void)
{
  char *msg_c=malloc(64);
  sprintf(msg_c, "Recv: %d \n"
                  "Sent: %d", in_count, out_count);
  ShowMSG(1,(int)msg_c);
  mfree(msg_c);
}

static void InitSnd(void)
{
  Init_Ext_Sounds();
}

static void Save_zzz(void)
{
  Save_Contacts_file();
}
#endif



extern int Is_Vibra_Enabled;
extern unsigned int Is_Sounds_Enabled; 
extern int Is_Show_Offline;
extern int Is_Show_Groups;
#ifdef EVILFOX
extern int show_ping;
#endif


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
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
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
#ifdef EVILFOX
  show_ping=1;
#endif
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

extern char LG_MENU2[32];
static const HEADER_DESC menuhdr={0,0,0,0,NULL,(int)LG_MENU2,LGP_NULL};

static const int mmenusoftkeys[]={0,1,2};

#ifdef EVILFOX
static const char * const menutexts[17]=
#else
static const char * const menutexts[11]=
#endif
{
  LG_MNUSTATUS,
  LG_MNUXSTATUS,
  LG_MANAGELIST,
  LG_MNUVIBRA,
  LG_MNUSOUND,
#ifdef EVILFOX
  LG_SLION,
  LG_ILUON,
  LG_INCON,
#endif
  LG_MNUSHOWOFF,
  LG_MNUSHOWGROUP,
  LG_MNUEDCFG,
#ifdef EVILFOX
  LG_INITSND,
  LG_SAVECL,
#endif
  LG_MNUDISCONNECT,
  LG_MSGINFO,
  LG_MNUPING,
  LG_MNUABOUT
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

#ifdef EVILFOX
static const void *menuprocs[17]=
#else
static const void *menuprocs[11]=
#endif
{
  (void *)DispStatusChangeMenu,
  (void *)DispXStatusChangeMenu,
  (void *)CreateManageCLMenu,
  (void *)ChangeVibraMode,
  (void *)ChangeSoundMode,
#ifdef EVILFOX
  (void *)ChangeSLIMode,
  (void *)ChangeILUMode,
  (void *)ChangeINCMode,
#endif
  (void *)ChangeShowOfflineMode,
  (void *)ChangeShowGroupsMode,
  (void *)EditConfig,
#ifdef EVILFOX
  (void *)InitSnd,
  (void *)Save_zzz,
#endif
  (void *)Disconnect,
  (void *)ShowMSGCount,
  (void *)PingToServer,
  (void *)AboutDlg,
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
    SetMenuItemIconArray(data,item,icon_array+(Is_SLI_On?0:1));
    break;
  case 6:
    SetMenuItemIconArray(data,item,icon_array+(Is_ILU_On?0:1));
    break;
  case 7:
    SetMenuItemIconArray(data,item,icon_array+(Is_INC_On?0:1));
    break;
  case 8:
    SetMenuItemIconArray(data,item,icon_array+(Is_Show_Offline?0:1));
    break;
  case 9:
    SetMenuItemIconArray(data,item,icon_array+(Is_Show_Groups?0:1));
    break;    
  case 10:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_SETTINGS);
    break;
  case 11:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_SETTINGS);
    break;
  case 12:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_SETTINGS);
    break;  
  case 13:
    SetMenuItemIconArray(data,item,S_ICONS+IS_OFFLINE);
    break;
  case 14:
    SetMenuItemIconArray(data,item,S_ICONS+IS_UNKNOWN);
    break;
  case 15:
    SetMenuItemIconArray(data,item,S_ICONS+ICON_PING);
    break;
  case 16:
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
#ifdef EVILFOX
  17
#else
  11
#endif
};

void ShowMainMenu()
{
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  *((int **)(&menuhdr.icon))=S_ICONS+IS_ONLINE;
  patch_header(&menuhdr);
#ifdef EVILFOX
  MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,17,0,0);
#else
  MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,11,0,0);
#endif
}
