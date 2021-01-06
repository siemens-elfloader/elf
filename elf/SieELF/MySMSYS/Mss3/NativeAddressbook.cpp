#include "include.h"
#include "SiemensPDU.h"
#include "MyIpcMessage.h"
#include "File.h"
#include "SmsData.h"
#include "CreateMenu.h"
#include "AdrList.h"
#include "NumList.h"
#include "EditGUI.h"
#include "NativeAddressbook.h"

NAbCSM::NAbCSM()
{
  this->nab_csm_desc.csm_desc.datasize=sizeof(NAb_CSM);
  this->nab_csm_desc.csm_desc.onClose=this->OnClose;
  this->nab_csm_desc.csm_desc.onCreate=this->OnCreate;
  this->nab_csm_desc.csm_desc.onMessage=this->OnMessage;
  this->nab_csm_desc.csm_desc.states=&minus11;
  this->nab_csm_desc.csm_desc.statesize=1;
#ifdef NEWSGOLD
  this->nab_csm_desc.csm_desc.zero1=0;
  this->nab_csm_desc.csm_desc.zero2=0;
  this->nab_csm_desc.csm_desc.zero3=0;
  this->nab_csm_desc.csm_desc.zero4=0;
#endif
  this->nab_csm_desc.csm_name.maxlen=NAB_CSM_NAME_LEN;
  this->nab_csm_desc.csm_name.ws_malloc=NAMECSM_MAGIC1;
  this->nab_csm_desc.csm_name.ws_mfree=NAMECSM_MAGIC2;
  this->nab_csm_desc.csm_name.isbody_allocated=0;
  this->nab_csm_desc.csm_name.wsbody=this->csm_name_body;
}

NAbCSM::~NAbCSM()
{
}

int NAbCSM::OnMessage(CSM_RAM *data, GBS_MSG *msg)
{
  NativeAbData *nabd;
  NAb_CSM *nabcsm=(NAb_CSM *)data;
  void *ed_gui;
  WSHDR *wn;
  EditGUI *edg;
  if((msg->msg==MSG_CSM_DESTROYED)&&((int)msg->data0==nabcsm->ab_csm_id))
  {
    if(!(nabd=nabcsm->nabd))
      goto CLOSE_CSM;
    if(nabcsm->type!=NAB_SAVE && (ed_gui=FindGUIbyId(nabcsm->ed_gui_id, NULL)))
    {
      if(nabcsm->ed_gui==ed_gui 
	&& ((GUI *)nabcsm->ed_gui)->methods==((GUI *)ed_gui)->methods 
	&& ((GUI *)nabcsm->ed_gui)->definition==((GUI *)ed_gui)->definition
	&& (edg=(EditGUI *)EDIT_GetUserPointer(ed_gui))
	)
      {
	if(nabcsm->type==NAB_TEXT)
	{
	  if(
	     GetNativeAbDataStatus(nabd, 0)!=9
	    && (wn=GetNumFromNativeAbData(nabd, GetNativeAbDataType(nabd, 0), 0))
	    && EDIT_GetFocus(ed_gui)==edg->n_focus
	    )
	  {
	    edg->InsertText(ed_gui, wn);
	    FreeWS(wn);
	  }
	}
	else if (
	  (nabcsm->type==NAB_SETC
	  || nabcsm->type==NAB_INSN)
	  && EDIT_GetFocus(ed_gui) < edg->n_focus-1)
	{
	  int n;
	  int z=0;
	  int k=0;
	  PKT_NUM *pkt;
	  char *buf=new char[50];
	  n=GetFilledNAbDataCount(nabd);
	  for(;k<n;k++)
	  {
	    if(
	      GetNativeAbDataStatus(nabd, k)==1
	      && GetNativeAbDataType(nabd, k)!=0xFF
	      && (pkt=(PKT_NUM *)GetDataFromNAbData(nabd, k))
	      )
	    {
	      UnpackNumPkt(pkt, buf, 49);
	      if(nabcsm->type==NAB_SETC
		&& z==0)
	      {
		if(edg->SetNumber(ed_gui, buf) > 0)
		  z++;
	      }
	      else
	      {
		edg->InsertNumber(ed_gui, buf);
	      }
	    }
	  }
	  delete buf;
	}
      }
    }
    FreeNativeAbData(nabd);
    nabcsm->nabd=0;
  CLOSE_CSM:
    data->state=-3;
    nabcsm->ab_csm_id=0;
  }
  return 1;
}

void NAbCSM::OnCreate(CSM_RAM *data)
{
  NAb_CSM *nabcsm=(NAb_CSM *)data;
  nabcsm->nabd=AllocNativeAbData();
  if(nabcsm->type==NAB_SAVE)
  {
    WSHDR *wloc, wlocn;
    unsigned short wlocb[50];
    wloc=CreateLocalWS(&wlocn, wlocb, 50);
    num_2ws(wloc, nabcsm->number, 50);
    SetNumToNativeAbData(nabcsm->nabd, 0x1D, wloc);
    nabcsm->ab_csm_id=OpenNativeAddressbook(6, 0, 0, nabcsm->nabd);
  }
  else if (nabcsm->type==NAB_TEXT)
  {
    nabcsm->ab_csm_id=OpenNativeAddressbook(0xB, 0, 0, nabcsm->nabd);
  }
  else if (nabcsm->type==NAB_SETC || nabcsm->type==NAB_INSN)
  {
    //nabcsm->ab_csm_id=OpenNativeAddressbook(4, 1, 0, nabcsm->nabd);
    nabcsm->ab_csm_id=OpenNativeAddressbook(5, 1, 0, nabcsm->nabd);
  }
  else data->state=-3; //close
}

void NAbCSM::OnClose(CSM_RAM *data)
{
  NAb_CSM *nabcsm=(NAb_CSM *)data;
  if(nabcsm->nabd)
  {
    FreeNativeAbData(nabcsm->nabd);
    nabcsm->nabd=NULL;
  }
  if(nabcsm->number)
  {
    delete nabcsm->number;
    nabcsm->number=NULL;
  }
  if(nabcsm->ab_csm_id) CloseCSM(nabcsm->ab_csm_id);
  delete nabcsm->nab;
}

int NAbCSM::CreateNAbCSM(void *ed_gui, int ed_gui_id, char *number, int type)
{
  int csm_id;
  NAb_CSM nabcsm;
  if(type==NAB_SAVE)
  {
    if(!number)
    {
      delete this;
      return 0;
    }
  }
  else
  {
    if(!ed_gui || !ed_gui_id)
    {
      delete this;
      return 0;
    }
  }
  zeromem(&nabcsm, sizeof(NAb_CSM));
  nabcsm.ed_gui=ed_gui;
  nabcsm.ed_gui_id=ed_gui_id;
  nabcsm.number=new char[strlen(number)+2];
  strcpy(nabcsm.number, number);
  nabcsm.type=type;
  nabcsm.nab=this;
  wsprintf(&this->nab_csm_desc.csm_name, PERCENT_T, LGP->lgp.LGP_CALL_ADDRESSBOOK);
  csm_id=CreateCSM(&this->nab_csm_desc.csm_desc, &nabcsm, 2);
  SendMyIpc(SMSYS_IPC_ADD_CSMID, (void *)csm_id);
  return csm_id;
}






