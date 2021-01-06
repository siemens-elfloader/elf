#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "SmsListMenu.h"
#include "AdrList.h"
#include "NumList.h"
#include "EditGUI.h"
#include "OthersMenu.h"
#include "MainMenu.h"


SOFTKEY_DESC main_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB main_menu_skt=
{
  main_menu_sk,0
};

HEADER_DESC main_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

MainMenu::MainMenu()
{
  menu.flag=8;
  menu.onkey=this->OnKey;
  menu.ghook=this->GHook;
  menu.proc3=NULL;
  menu.softkeys=softkeys;
  menu.softkeystab=&main_menu_skt;
  menu.flags2=0x11; //icon
  menu.itemproc=this->ItemProc;
  menu.items=NULL;
  menu.procs=NULL;
  menu.n_items=0;
}

MainMenu::~MainMenu()
{
}

#define MAINMENU_N 6
int MainMenu::CreateMainMenu(DLG_CSM *dlg_csm)
{
  this->dlg_csm=dlg_csm;
  this->gui_id=CreateMenu(&this->menu, &main_menuhdr, 0, MAINMENU_N, this);
  return this->gui_id;
}

int MainMenu::OnKey(void *data, GUI_MSG *msg)
{
  int n;
  MainMenu *mm=(MainMenu *)MenuGetUserPointer(data);
  if(msg->keys==0x1)
    return 1;
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    n=GetCurMenuItem(data);
  DO_ITEM:
    switch(n)
    {
    case 0:
      {
	SDLIST *sdl=SMSDATA->AllocSDL();
	EditGUI *edg=new EditGUI;
	edg->CreateEditGUI(mm->dlg_csm, sdl, ED_REPLY, 0, 1);
      }
      break;
    case 1:
      {
	SmsListMenu *slm=new SmsListMenu;
	slm->CreateSmsListMenu(TYPE_IN_N, 0, mm->dlg_csm);
	break;
      }
    case 2:
      {
	SmsListMenu *slm=new SmsListMenu;
	slm->CreateSmsListMenu(TYPE_IN_ALL, 0, mm->dlg_csm);
	break;
      }
    case 3:
      {
	SmsListMenu *slm=new SmsListMenu;
	slm->CreateSmsListMenu(TYPE_SENT, 0, mm->dlg_csm);
	break;
      }
    case 4:
      {
	SmsListMenu *slm=new SmsListMenu;
	slm->CreateSmsListMenu(TYPE_DRAFT, 0, mm->dlg_csm);
	break;
      }
    case 5:
      {
	OthMenu *oth=new OthMenu;
	oth->CreateOthMenu(mm->dlg_csm);
      }
      break;
    default:
      break;
    }
    return 0;
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    n=msg->gbsmsg->submess;
    if(n>='1' && n<='9')
    {
      n-='1';
      goto DO_ITEM;
    }
  }
  return 0;
}

void MainMenu::GHook(void *data, int cmd)
{
  MainMenu *mm=(MainMenu *)MenuGetUserPointer(data);
  if(cmd==0x3)
  {
    delete mm;
  }
  else if(cmd==0xA)
  {
    DisableIDLETMR();
  }
  else if (cmd==0x5)
  {
    mm->UpdateCSMName(mm->dlg_csm, (int)LGP->lgp.LGP_MSS_MAINMENU);
  }
}

int MM_ITEM_LGPS[MAINMENU_N]={LGP_NULL,LGP_NULL,LGP_NULL,LGP_NULL,LGP_NULL,LGP_NULL};
int MM_ITEM_ICONS[MAINMENU_N+1]={ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,0};
const char MM_FORMAT[]="%t%c%d";
void MainMenu::ItemProc(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  switch(curitem)
  {
  case 0:
  case 5:
    wsprintf(ws, PERCENT_T, MM_ITEM_LGPS[curitem]);
    break;
  case 1:
    wsprintf(ws, MM_FORMAT, MM_ITEM_LGPS[curitem], 0xE01D, SMSDATA->GetSMSCount(TYPE_IN_N));
    break;
  case 2:
    wsprintf(ws, MM_FORMAT, MM_ITEM_LGPS[curitem], 0xE01D, SMSDATA->GetSMSCount(TYPE_IN_ALL));
    break;
  case 3:
    wsprintf(ws, MM_FORMAT, MM_ITEM_LGPS[curitem], 0xE01D, SMSDATA->GetSMSCount(TYPE_SENT));
    break;
  case 4:
    wsprintf(ws, MM_FORMAT, MM_ITEM_LGPS[curitem], 0xE01D, SMSDATA->GetSMSCount(TYPE_DRAFT));
    break;
  default:
    wsprintf(ws, PERCENT_T, LGP->lgp.LGP_ERR);
    break;
  }
  SetMenuItemIconArray(data, item, MM_ITEM_ICONS);
  SetMenuItemIcon(data, curitem, curitem);
  SetMenuItemText(data, item, ws, curitem);
}
/*
void *MainMenu::GetMainMenuGUI(DLG_CSM *dlg_csm)
{
  void *m_gui;
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  this->dlg_csm=dlg_csm;
  this->gui_id=0;
  m_gui=GetMenuGUI(ma, mf);
  SetMenuToGUI(m_gui, &this->menu);
  SetMenuItemCount(m_gui, MAINMENU_N);
  MenuSetUserPointer(m_gui, this);
  SetCursorToMenuItem(m_gui, 0);
  patch_header(&main_menuhdr);
  SetHeaderToMenu(m_gui, &main_menuhdr, ma);
  return m_gui;
}
*/




void MainMenu::UpdateCSMName(DLG_CSM *dlg_csm, int lgp)
{
  wsprintf(&((DLGCSM_DESC *)dlg_csm->csm_ram.constr)->csm_name, PERCENT_T, lgp);
}

void * MainMenu::GetMainMenuGUI(DLG_CSM *dlg_csm, int cur)
{
  void *m_gui;
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  this->dlg_csm=dlg_csm;
  this->gui_id=0;
  m_gui=GetMenuGUI(ma, mf);
  SetMenuToGUI(m_gui, &this->menu);
  SetMenuItemCount(m_gui, MAINMENU_N);
  MenuSetUserPointer(m_gui, this);
  SetCursorToMenuItem(m_gui, cur);
  patch_header(&main_menuhdr);
  SetHeaderToMenu(m_gui, &main_menuhdr, ma);
  return m_gui;
}
