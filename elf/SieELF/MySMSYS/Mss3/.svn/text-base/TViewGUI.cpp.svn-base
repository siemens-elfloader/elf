// TViewGUI.cpp: implementation of the TViewGUI class.
//
//////////////////////////////////////////////////////////////////////
#include "include.h"
#include "TViewGUI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#define TViewGetGUI (0xA09AE59E+1) //void *TViewGetGUI(void *malloc_adr, void *mfree_adr)
//#define TViewSetDefinition (0xA09AEB90+1) //void TViewSetDefinition(void *gui, const TVIEW_DESC *)
//#define TViewSetText (0xA09AEB1A+1) //void TViewSetText(void *gui, WSHDR *text, void *malloc_adr, void *mfree_adr)
//#define TViewSetUserPointer (0xA09AEBBE+1) //void TViewSetUserPointer(void *gui,void *user_pointer)
//#define TViewGetUserPointer (0xA09AEBC4+1) //void *TViewGetUserPointer(void *gui)



#pragma inline
void patch_tview(const TVIEW_DESC* tv)
{
  ((TVIEW_DESC*)tv)->rc.x=0;
  ((TVIEW_DESC*)tv)->rc.y=HeaderH()+1+YDISP;
  ((TVIEW_DESC*)tv)->rc.x2=ScreenW()-1;
  ((TVIEW_DESC*)tv)->rc.y2=ScreenH()-SoftkeyH()-1;
}

SOFTKEY_DESC tview_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB tview_skt=
{
  tview_sk,0
};

HEADER_DESC tview_hdr={0, 0, 0, 0, NULL, LGP_NULL, LGP_NULL};
TVIEW_DESC TViewGUI::tview=
{
  8,
    TViewGUI::OnKey,
    TViewGUI::GHook,
    TViewGUI::locret,
    softkeys,
    &tview_skt,
  {0,0,0,0},
  FONT_SMALL,
  0x64,
  0x65,
  0,
  0
};

TViewGUI::TViewGUI()
{
  this->gui_id=0;
}

TViewGUI::~TViewGUI()
{

}
int TViewGUI::OnKey(void *data, GUI_MSG *msg)
{
  if(msg->keys==0x1
    ||msg->keys==0x18
    ||msg->keys==0x3D
    )
    return 1;
  return 0;
}

void TViewGUI::GHook(void *data, int cmd)
{
  if(cmd==3)
  {
    //TViewGUI *tv=(TViewGUI *)(((void *(*)(void *))TViewGetUserPointer)(data));
    TViewGUI *tv=(TViewGUI *)TViewGetUserPointer(data);
    delete tv;
  }
}

void TViewGUI::locret()
{

}

int TViewGUI::CreateTViewGUI(WSHDR *text, WSHDR *hdr_t)
{
  if(!text)
  {
    delete this;
    return 0;
  }
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  //void *gui=((void *(*)(void *, void *))TViewGetGUI)(ma, mf);
  //((void (*)(void *, const TVIEW_DESC *))TViewSetDefinition)(gui, &this->tview);
  //((void (*)(void *, WSHDR *, void *, void *))TViewSetText)(gui, text, ma, mf);
  //((void (*)(void *,void *))TViewSetUserPointer)(gui, this);
  void *gui=TViewGetGUI(ma, mf);
  TViewSetDefinition(gui, &this->tview);
  TViewSetText(gui, text, ma, mf);
  TViewSetUserPointer(gui, this);
  patch_header(&tview_hdr);
  SetHeaderToMenu(gui, &tview_hdr, ma);
  if(hdr_t) SetHeaderText(GetHeaderPointer(gui), hdr_t, ma, mf);
  patch_tview(&this->tview);
  this->gui_id=CreateGUI(gui);
  return this->gui_id;
}
