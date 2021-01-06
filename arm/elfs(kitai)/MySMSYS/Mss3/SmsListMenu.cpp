#include "include.h"

#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "SmsListMenu.h"
#include "TabGUI.h"

#include "AdrList.h"
#include "NumList.h"
#include "EditGUI.h"

#include "PopupGUI.h"

#include "NativeAddressbook.h"
#include "CodeShow.h"

SOFTKEY_DESC sms_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB sms_menu_skt=
{
  sms_menu_sk,0
};

const HEADER_DESC sms_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

SmsListMenu::~SmsListMenu()
{
}

SmsListMenu::SmsListMenu()
{
  menu.flag=8;
  menu.onkey=OnKey;
  menu.ghook=GHook;
  menu.proc3=NULL;
  menu.softkeys=softkeys;
  menu.softkeystab=&sms_menu_skt;
  menu.flags2=0x11; //icon
  menu.itemproc=ItemProc;
  menu.items=NULL;
  menu.procs=NULL;
  menu.n_items=0;
  menu.n_lines=1; //2
}

int SmsListMenu::OnKey(void *data, GUI_MSG *msg)
{
  SmsListMenu *slm=(SmsListMenu *)MenuGetUserPointer(data);
  int cur=GetCurMenuItem(data);
  SDLIST *sdl=SMSDATA->FindSDL(slm->type, cur);
  if(msg->keys==1)
    return 1;
  if(!sdl) return 0;
  if(msg->keys==0x3D)
  {
    {
      EditGUI *edg=new EditGUI;
      edg->CreateEditGUI(slm->dlg_csm, sdl, ED_VIEW, slm->type, 0);
    }
  }
  else if (msg->keys==0x5)
  {
    {
      EditGUI *edg=new EditGUI;
      edg->CreateEditGUI(slm->dlg_csm, sdl, ED_REPLY, slm->type, 0);
    }
  }
  else if (msg->keys==0x18)
  {
    {
      SmsOptionMenu *sop=new SmsOptionMenu;
      sop->CreateSmsOptionMenu(slm->dlg_csm, slm->gui_id, slm->type, sdl);
    }
  }
  else if (msg->keys==0x14)
  {
#ifdef LANG_CN
    unsigned short wscsb[32];
    WSHDR *wmsg, *wscs, _wscs;
    wmsg=AllocWS(150);
    wscs=CreateLocalWS(&_wscs, wscsb, 32);
    CodeShow::GetProvAndCity(wscs->wsbody, sdl->number);
    wsprintf(wmsg, "%s\n%t:\n%w",
      sdl->number,
      LGP->lgp.LGP_CODESHOW,
      wscs
      );
    MyShowMsg::MyShow(1, wmsg);
#else
    MyShowMsg::MyShow(1, sdl->number);
#endif
    //{
    //  ShowMSG(1, (int)(sdl->number));
    //}
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
    if(key=='7') //delete
    {
      if(SMSDATA->DeleteMessage(sdl))
      {
	slm->ReCreateMe(data);
	return 1;
      }
    }
    else if (key=='4') //move to archive
    {
      if (SMSDATA->MoveToArchive(sdl))
      {
	slm->ReCreateMe(data);
	return 1;
      }
    }
  }
  return 0;
}

int SLM_HDR_LGPS[]={LGP_NULL,LGP_NULL,LGP_NULL,LGP_NULL,LGP_NULL,LGP_NULL,LGP_NULL};

void SmsListMenu::GHook(void *data, int cmd)
{
  SmsListMenu *slm=(SmsListMenu *)MenuGetUserPointer(data);
  if(cmd==0xA)
  {
    int n=SMSDATA->GetSMSCount(slm->type);
    int cur=GetCurMenuItem(data);
    if(cur>=n) SetCursorToMenuItem(data, 0);
    Menu_SetItemCountDyn(data, n);
    DisableIDLETMR();
  }
  else if(cmd==0x2)
  {
    WSHDR *hdr_t=AllocWS(64);
    void *hdr_p=GetHeaderPointer(data);
    void *ma=malloc_adr();
    void *mf=mfree_adr();
    wsprintf(hdr_t, PERCENT_T, SLM_HDR_LGPS[slm->type<6?slm->type:0]);
    SetHeaderText(hdr_p, hdr_t, ma, mf);
  }
  else if(cmd==0x3)
  {
    delete slm;
  }
  else if (cmd==0x5)
  {
    const char *lgpN;
    switch(slm->type)
    {
    case 0:
      lgpN=LGP->lgp.LGP_ALL;
      break;
    case TYPE_IN_R:
      lgpN=LGP->lgp.LGP_IN_R;
      break;
    case TYPE_IN_N:
      lgpN=LGP->lgp.LGP_IN_N;
      break;
    case TYPE_SENT:
      lgpN=LGP->lgp.LGP_SENT;
      break;
    case TYPE_DRAFT:
      lgpN=LGP->lgp.LGP_DRAFT;
      break;
    case TYPE_IN_ALL:
      lgpN=LGP->lgp.LGP_IN_A;
      break;
    case TYPE_FILTER:
      lgpN=LGP->lgp.LGP_FILTER;
      break;
    default:
      lgpN=0;
    }
    slm->UpdateCSMName(slm->dlg_csm, (int)lgpN);
  }
}

#define MENU_MAX_TXT 50
int SLM_ICONS[8]={ICON_BLANK, ICON_BLANK, ICON_BLANK, ICON_BLANK, ICON_BLANK, ICON_BLANK, ICON_BLANK, 0};
void SmsListMenu::ItemProc(void *data, int curitem, void *user_pointer)
{
  SDLIST *sdl;
  void *item=AllocMLMenuItem(data);
  WSHDR *ws1=AllocMenuWS(data, MENU_MAX_TXT);
  WSHDR *ws2=AllocMenuWS(data, 150);
  SmsListMenu *slm=(SmsListMenu *)MenuGetUserPointer(data);
  if((sdl=SMSDATA->FindSDL(slm->type, curitem)))
  {
    if(sdl->text) wstrncpy(ws1, sdl->text, MENU_MAX_TXT);
    else goto SL_ERR;
    if(!strlen(sdl->number))
      CutWSTR(ws2, 0);
    else
    {
      if(!ADRLST->FindName(ws2, sdl->number))
	wsprintf(ws2, PERCENT_S, sdl->number);
    }
  }
  else
  {
  SL_ERR:
    wsprintf(ws1, PERCENT_T, LGP->lgp.LGP_ERR);
    CutWSTR(ws2, 0);
  }
  SetMenuItemIconArray(data, item, SLM_ICONS);
  SetMenuItemIcon(data, curitem, (sdl)?(sdl->type):0);
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

int SmsListMenu::CreateSmsListMenu(int type, int is_tab, DLG_CSM *dlg_csm)
{
  this->type=type;
  this->is_tab=is_tab;
  this->dlg_csm=dlg_csm;
  this->gui_id=CreateMenu(&menu, &sms_menuhdr, 0, SMSDATA->GetSMSCount(type), this);
  return this->gui_id;
}
/*
void *SmsListMenu::GetSmsListMenuGUI(int type, int is_tab, DLG_CSM *dlg_csm)
{
  void *m_gui;
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  this->type=type;
  this->dlg_csm=dlg_csm;
  this->gui_id=0;
  this->is_tab=is_tab;
  m_gui=GetMultiLinesMenuGUI(ma, mf);
  SetMenuToGUI(m_gui, &this->menu);
  SetMenuItemCount(m_gui, SMSDATA->GetSMSCount(type));
  MenuSetUserPointer(m_gui, this);
  SetCursorToMenuItem(m_gui, 0);
  patch_header(&sms_menuhdr);
  SetHeaderToMenu(m_gui, &sms_menuhdr, ma);
  return m_gui;
}
*/
void * SmsListMenu::GetSmsListMenuGUI(int type, int is_tab, DLG_CSM *dlg_csm, int cur)
{
  void *m_gui;
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  this->type=type;
  this->dlg_csm=dlg_csm;
  this->gui_id=0;
  this->is_tab=is_tab;
  m_gui=GetMultiLinesMenuGUI(ma, mf);
  SetMenuToGUI(m_gui, &this->menu);
  SetMenuItemCount(m_gui, SMSDATA->GetSMSCount(type));
  MenuSetUserPointer(m_gui, this);
  SetCursorToMenuItem(m_gui, cur);
  patch_header(&sms_menuhdr);
  SetHeaderToMenu(m_gui, &sms_menuhdr, ma);
  return m_gui;
}
/*
SOFTKEY_DESC sop_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB sop_menu_skt=
{
  sop_menu_sk,0
};
*/
const HEADER_DESC sop_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

#define SOP_MENU_ITEM_N 7
SmsOptionMenu::SmsOptionMenu()
{
  this->menu.flag=8;
  this->menu.onkey=this->OnKey;
  this->menu.ghook=this->GHook;
  this->menu.proc3=NULL;
  this->menu.softkeys=softkeys;
  this->menu.softkeystab=&sel_menu_skt;
  this->menu.flags2=0x11; //icon
  this->menu.itemproc=this->ItemProc;
  this->menu.items=NULL;
  this->menu.procs=NULL;
  this->menu.n_items=0;
}

SmsOptionMenu::~SmsOptionMenu()
{
}

int SmsOptionMenu::OnKey(void *data, GUI_MSG *msg)
{
  SmsOptionMenu *sop=(SmsOptionMenu *)MenuGetUserPointer(data);
  int cur=GetCurMenuItem(data);
  if(msg->keys==1)
    return 1;
  if(msg->keys==0x3D || msg->keys==0x18)
  {
DO_OP:
    switch(cur)
    {
    case 0:
      {
	EditGUI *edg=new EditGUI;
	edg->CreateEditGUI(sop->dlg_csm, sop->sdl, ED_REPLY, sop->list_type, 0);
      }
      break;
    case 1:
      {
	EditGUI *edg=new EditGUI;
	edg->CreateEditGUI(sop->dlg_csm, sop->sdl, ED_EDIT, sop->list_type, 0);
      }
      break;
    case 2:
      SMSDATA->DeleteMessage(sop->sdl);
      break;
    case 3:
      if (sop->sdl)
      {
	NAbCSM *nab=new NAbCSM;
	nab->CreateNAbCSM(NULL, 0, sop->sdl->number, NAB_SAVE);
      }
      break;
    case 4:
      if (sop->sdl
	&& strlen(sop->sdl->number)
	)
      {
	MakeVoiceCall(sop->sdl->number,0x10,0x2FFF);
      }
      break;
    case 5:
      SMSDATA->MoveToArchive(sop->sdl);
      break;
    case 6:
      if(!sop->slm_id) GeneralFunc_flag1(sop->dlg_csm->gui_id, 1);
      else GeneralFunc_flag1(sop->slm_id, 1);
      break;
    }
    return 1;
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    cur=msg->gbsmsg->submess;
    if(cur>='1' && cur<='9')
    {
      cur-='1';
      goto DO_OP;
    }
  }
  return 0;
}

void SmsOptionMenu::GHook(void *data, int cmd)
{
  SmsOptionMenu *sop=(SmsOptionMenu *)MenuGetUserPointer(data);
  if(cmd==0xA)
  {
    DisableIDLETMR();
  }
  else if (cmd==0x3)
  {
    delete sop;
  }
  else if (cmd==0x2)
  {
    WSHDR *hdr_t=AllocWS(32);
    wsprintf(hdr_t, PERCENT_T, LGP->lgp.LGP_OPTIONS);
    SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
  }
}

int SOP_ITEM_LGPS[SOP_MENU_ITEM_N]=
{
  LGP_NULL, //reply
    LGP_NULL, //edit
    LGP_NULL, //delete
    LGP_SAVE_TO_AB,
    LGP_NULL, //call
    LGP_NULL, //move to archive
    LGP_NULL, //leave
};

const int SOP_ITEM_ICONS[]={ICON_BLANK,0};
void SmsOptionMenu::ItemProc(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  wsprintf(ws, PERCENT_T, SOP_ITEM_LGPS[curitem]);
  SetMenuItemIconArray(data, item, SOP_ITEM_ICONS);
  SetMenuItemIcon(data, curitem, 0);
  SetMenuItemText(data, item, ws, curitem);
}

int SmsOptionMenu::CreateSmsOptionMenu(DLG_CSM *dlg_csm, int slm_id, int list_type, SDLIST *sdl)
{
  this->dlg_csm=dlg_csm;
  this->sdl=sdl;
  this->slm_id=slm_id;
  this->list_type=list_type;
  return CreateMenu30or2(&this->menu, &sop_menuhdr, 0, SOP_MENU_ITEM_N, this);
}




void SmsListMenu::UpdateCSMName(DLG_CSM *dlg_csm, int lgp)
{
  wsprintf(&((DLGCSM_DESC *)dlg_csm->csm_ram.constr)->csm_name, PERCENT_T, lgp);
}

/*
int SmsListMenu::ReCreateMe(void *data)
{
  int cur;
  SmsListMenu *slm;
  if(!data)
    return 0;
  cur=GetCurMenuItem(data);
  slm=new SmsListMenu;
  slm->dlg_csm=this->dlg_csm;
  slm->is_tab=this->is_tab;
  slm->type=this->type;
  slm->gui_id=CreateMenu(&slm->menu, &sms_menuhdr, cur, SMSDATA->GetSMSCount(slm->type), slm);
  return slm->gui_id;
}

int SmsListMenu::ReCreateTab(void *data)
{
}
*/

void SmsListMenu::ReCreateMe(void *data)
{
  if(this->is_tab)
  {
    int id=0;
    TabGUI tab;
    id=tab.ReCreateTabGUI(this->dlg_csm);
    if(id) this->dlg_csm->gui_id=id;
  }
  else
  {
    //SmsListMenu *sl=new SmsListMenu;
    //id=sl->CreateSmsListMenu(this->type, GetCurMenuItem(data), this->dlg_csm);
    SmsListMenu *sl=new SmsListMenu;
    sl->type=this->type;
    sl->is_tab=this->is_tab;
    sl->dlg_csm=this->dlg_csm;
    sl->gui_id=CreateMenu(&sl->menu, &sms_menuhdr, GetCurMenuItem(data), SMSDATA->GetSMSCount(this->type), sl);
    if(this->dlg_csm->gui_id == this->gui_id && sl->gui_id)
      this->dlg_csm->gui_id=sl->gui_id;
  }
}
