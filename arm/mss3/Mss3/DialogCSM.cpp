#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "SmsListMenu.h"
#include "MainMenu.h"
#include "TabGUI.h"
#include "DialogCSM.h"
#include "AdrList.h"
#include "NumList.h"
#include "EditGUI.h"
#include "PopupGUI.h"

DialogCSM::DialogCSM()
{
  dlg_csm_desc.csm_desc.onMessage=OnMessage;
  dlg_csm_desc.csm_desc.onCreate=OnCreate;
  dlg_csm_desc.csm_desc.onClose=OnClose;
#ifdef NEWSGOLD
  dlg_csm_desc.csm_desc.zero1=0;
  dlg_csm_desc.csm_desc.zero2=0;
  dlg_csm_desc.csm_desc.zero3=0;
  dlg_csm_desc.csm_desc.zero4=0;
#endif
  dlg_csm_desc.csm_desc.datasize=sizeof(DLG_CSM);
  dlg_csm_desc.csm_desc.statesize=1;
  dlg_csm_desc.csm_desc.states=&minus11;
  dlg_csm_desc.csm_name.wsbody=this->csm_name_body;
  dlg_csm_desc.csm_name.ws_malloc=NAMECSM_MAGIC1;
  dlg_csm_desc.csm_name.ws_mfree=NAMECSM_MAGIC2;
  dlg_csm_desc.csm_name.isbody_allocated=0;
  dlg_csm_desc.csm_name.maxlen=DLGCSM_NAME_LEN;
  //SUBPROC((void *)SMSDATA->CheckAllCHK, SMSDATA);
}

DialogCSM::~DialogCSM()
{
}


int DialogCSM::OnMessage(CSM_RAM *data, GBS_MSG *msg)
{
  DLG_CSM *dlg_csm=(DLG_CSM *)data;
  if(msg->msg==MSG_GUI_DESTROYED)
  {
    if((int)msg->data0==dlg_csm->gui_id)
      dlg_csm->csm_ram.state=-3;
  }
  return 1;
}

void DialogCSM::OnCreate(CSM_RAM *data)
{
  int submsg;
  DLG_CSM *dlg_csm=(DLG_CSM *)data;
  DialogCSM *dlg=dlg_csm->dlg;
  dlg_csm->dlg->UpdateNameDlgCSM(dlg_csm, (int)ELFFNAME);
  submsg=dlg_csm->dlg->submsg;
  switch(submsg)
  {
  case SMSYS_IPC_MAIN:
    {
      TabGUI tab;
      dlg_csm->gui_id=tab.CreateTabGUI((::DLG_CSM *)dlg_csm);
    }
    break;
  case SMSYS_IPC_NEW_IN_WIN:
    {
      SDLIST *sdl;
      if((sdl=SMSDATA->FindLastNew()))
      {
	PopupNewIn *pni=new PopupNewIn;
	dlg_csm->gui_id=pni->CreatePopupNewIn((::DLG_CSM *)dlg_csm, sdl);
      }
      //else dlg_csm->gui_id=0;
    }
    break;
  case SMSYS_IPC_NEW_IN_ME:
    {
      SDLIST *sdl;
      if((sdl=SMSDATA->FindSDL((int)dlg->ipc_data)))
      {
	PopupNewIn *pni=new PopupNewIn;
	dlg_csm->gui_id=pni->CreatePopupNewIn((::DLG_CSM *)dlg_csm, sdl);
      }
      //else dlg_csm->gui_id=0;
    }
    break;
  case SMSYS_IPC_NEWSMS:
    {
      SDLIST *sdl=SMSDATA->AllocSDL();
      EditGUI *edg=new EditGUI;
      dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_REPLY, 0, 1);
    }
    break;
  case SMSYS_IPC_IN_NEW:
    {
      SmsListMenu *slm=new SmsListMenu;
      dlg_csm->gui_id=slm->CreateSmsListMenu(TYPE_IN_N, 0, (::DLG_CSM *)dlg_csm);
    }
    break;
  case SMSYS_IPC_IN_RD:
    {
      SmsListMenu *slm=new SmsListMenu;
      dlg_csm->gui_id=slm->CreateSmsListMenu(TYPE_IN_R, 0, (::DLG_CSM *)dlg_csm);
    }
    break;
  case SMSYS_IPC_OUT:
    {
      SmsListMenu *slm=new SmsListMenu;
      dlg_csm->gui_id=slm->CreateSmsListMenu(TYPE_SENT, 0, (::DLG_CSM *)dlg_csm);
    }
    break;
  case SMSYS_IPC_DRAFT:
    {
      SmsListMenu *slm=new SmsListMenu;
      dlg_csm->gui_id=slm->CreateSmsListMenu(TYPE_DRAFT, 0, (::DLG_CSM *)dlg_csm);
    }
    break;
  case SMSYS_IPC_ALL:
    {
      SmsListMenu *slm=new SmsListMenu;
      dlg_csm->gui_id=slm->CreateSmsListMenu(0, 0, (::DLG_CSM *)dlg_csm);
    }
    break;
  case SMSYS_IPC_IN_ALL:
    {
      SmsListMenu *slm=new SmsListMenu;
      dlg_csm->gui_id=slm->CreateSmsListMenu(TYPE_IN_ALL, 0, (::DLG_CSM *)dlg_csm);
    }
    break;
  case SMSYS_IPC_NEWSMS_NUM:
    {
      if(dlg->ipc_data)
      {
	//SDLIST *sdl=SMSDATA->AllocSDL();
	EditGUI *edg=new EditGUI;
	//strcpy(sdl->number, (char *)dlg->ipc_data);
	//dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_REPLY, 0, 1);
	dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, (char *)dlg->ipc_data);
	delete dlg->ipc_data;
      }
      //else dlg_csm->csm_ram.state=-3;
    }
    break;
  case SMSYS_IPC_SEND_UTF8:
    {
      if(dlg->ipc_data)
      {
	SDLIST *sdl=SMSDATA->AllocSDL();
	EditGUI *edg=new EditGUI;
	WSHDR *ws=AllocWS(strlen((char *)dlg->ipc_data));
	sdl->text=ws;
	utf8_2ws(ws, (char *)dlg->ipc_data, strlen((char *)dlg->ipc_data));
	dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_EDIT, 0, 1);
	delete dlg->ipc_data;
      }
      //else dlg_csm->csm_ram.state=-3;
    }
    break;
  case SMSYS_IPC_QR_OPMSG:
  case SMSYS_IPC_QN_OPMSG:
    {
      SDLIST *sdl;
      if(dlg->ipc_data && (sdl=SMSDATA->FindOpmsgSDL((int)dlg->ipc_data)))
      {
	EditGUI *edg=new EditGUI;
	dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_EDIT, TYPE_IN_ALL, 0);
      }
      //else dlg_csm->csm_ram.state=-3;
    }
    break;
  case SMSYS_IPC_VIEW_OPMSG:
    {
      SDLIST *sdl;
      if(dlg->ipc_data && (sdl=SMSDATA->FindOpmsgSDL((int)dlg->ipc_data)))
      {
	EditGUI *edg=new EditGUI;
	dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_VIEW, TYPE_IN_ALL, 0);
      }
      //else dlg_csm->csm_ram.state=-3;
    }
    break;
  case SMSYS_IPC_REPLY_OPMSG:
    {
      SDLIST *sdl;
      if(dlg->ipc_data && (sdl=SMSDATA->FindOpmsgSDL((int)dlg->ipc_data)))
      {
	EditGUI *edg=new EditGUI;
	dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_REPLY, TYPE_IN_ALL, 0);
      }
      //else dlg_csm->csm_ram.state=-3;
    }
    break;
  case SMSYS_IPC_SEND_WS:
    {
      if(dlg->ipc_data)
      {
	SDLIST *sdl=SMSDATA->AllocSDL();
	EditGUI *edg=new EditGUI;
	WSHDR *ws=AllocWS(wstrlen((WSHDR *)dlg->ipc_data)+2);
	sdl->text=ws;
	wstrcpy(ws, (WSHDR *)dlg->ipc_data);
	dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_EDIT, 0, 1);
	FreeWS((WSHDR *)dlg->ipc_data);
      }
      //else dlg_csm->csm_ram.state=-3;
    }
    break;
  case SMSYS_IPC_FVIEW:
    {
      if(dlg->ipc_data)
      {
	SDLIST *sdl=SMSDATA->AllocSDL();
	if(SMSDATA->ReadMss((char *)dlg->ipc_data, sdl))
	{
	  EditGUI *edg=new EditGUI;
	  dlg_csm->gui_id=edg->CreateEditGUI((::DLG_CSM *)dlg_csm, sdl, ED_VIEW, 0, 1);
	}
	//else dlg_csm->csm_ram.state=-3;
	delete dlg->ipc_data;
      }
      //else dlg_csm->csm_ram.state=-3;
    }
    break;
  default:
    //dlg_csm->csm_ram.state=-3;
    break;
  }
  dlg->ipc_data=NULL;
  if(!dlg_csm->gui_id) dlg_csm->csm_ram.state=-3;
}

void DialogCSM::OnClose(CSM_RAM *data)
{
  DLG_CSM *dlg_csm=(DLG_CSM *)data;
  delete dlg_csm->dlg;
}


int DialogCSM::CreateDialogCSM(int submsg, void *ipc_data)
{
  DLG_CSM dlg_csm;
  zeromem(&dlg_csm, sizeof(DLG_CSM));
  this->submsg=submsg;
  this->ipc_data=ipc_data;
  dlg_csm.dlg=this;
  if(submsg==SMSYS_IPC_MAIN
    ||submsg==SMSYS_IPC_IN_NEW
    ||submsg==SMSYS_IPC_IN_RD
    ||submsg==SMSYS_IPC_OUT
    ||submsg==SMSYS_IPC_DRAFT
    ||submsg==SMSYS_IPC_ALL
    ||submsg==SMSYS_IPC_IN_ALL
    )
    SUBPROC((void *)SMSDATA->CheckAllCHK, SMSDATA);
  return (CreateCSM(&dlg_csm_desc.csm_desc, &dlg_csm, 0));
}

void DialogCSM::UpdateNameDlgCSM(DLG_CSM *dlg_csm, int lgp)
{
  DLGCSM_DESC *dlg_csm_desc=(DLGCSM_DESC *)dlg_csm->csm_ram.constr;
  wsprintf(&dlg_csm_desc->csm_name, PERCENT_T, lgp);
}

