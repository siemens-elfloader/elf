#include "..\..\inc\swilib.h"
#include "main.h"
#include "sms_dat.h"
#include "rect_patcher.h"
#include "guiIdMan.h"
#include "MySMSYS_ipc.h"
#include "smsList.h"
#include "config_data.h"

#define TAB_N 5

int TabIcons[5][4]=
{
  0x5C7,0x5C7,0x5C7,0x5C7,
  0x5C7,0x5C7,0x5C7,0x5C7,
  0x5C7,0x5C7,0x5C7,0x5C7,
  0x5C7,0x5C7,0x5C7,0x5C7,
  0x5C7,0x5C7,0x5C7,0x5C7,
};

int TabGuiOnKey(void *gui, GUI_MSG *msg)
{
  return 0;
}

void TabGuiGHook(void *gui, int cmd)
{
  if(cmd==0x18)
  {
    //redraw
    //REDRAW();
    int n=GetCursorTab(gui);
    if(n)
    {
      int type, cnt, cur;
      void *m_gui;
      switch(n)
      {
      case 1: type=TYPE_IN_ALL;break;
      case 2: type=TYPE_OUT;break;
      case 3: type=TYPE_DRAFT;break;
      case 4: type=TYPE_FILTER;break;
      default : type=0;
      }
      m_gui=GetGuiByTab(gui, n);
      if(m_gui)
      {
        cnt=getCountByType(type);
        cur=GetCurMenuItem(m_gui);
        if(cur>=cnt) SetCursorToMenuItem(m_gui, 0);
        Menu_SetItemCountDyn(m_gui, cnt);
        //SendSimpleIpcMsg(SMSYS_IPC_SMS_DATA_UPDATE);
      }
    }
    void **methods=((GUI *)gui)->methods;
    ((void (*)(void *))methods[0])(gui);
  }
  else if(cmd==0xA)
  {
    DisableIDLETMR();
  }
}

void TabGuiLocret(void)
{
}

const TABGUI_DESC TabGui=
{
  8,
  TabGuiOnKey,
  TabGuiGHook,
  (void *)TabGuiLocret,
  NULL,
  NULL
};

int CreateTabMenu(void *dlg_csm)
{
  void *m_gui;
  void *ma=malloc_adr();
  void *mf=mfree_adr();
  void *tab_gui=GetTabGUI(ma, mf);
  int n, gui_id;
  //mainmenu
  extern const MENU_DESC main_menu;
  extern HEADER_DESC main_menuhdr;
  
  SetGUIDefinition(tab_gui, &TabGui);
  
#define MAIN_MENU_N 6
  m_gui=GetMenuGUI(ma, mf);
  SetMenuToGUI(m_gui, &main_menu);
  SetMenuItemCount(m_gui, MAIN_MENU_N);
  MenuSetUserPointer(m_gui, dlg_csm);
  SetCursorToMenuItem(m_gui, 0);
  patch_header(&main_menuhdr);
  SetHeaderToMenu(m_gui, &main_menuhdr, ma);
  SetGUIToTabGUI(tab_gui, 0, TabIcons[0], m_gui);
  //sms list
  extern const HEADER_DESC sms_menuhdr;
  extern const ML_MENU_DESC sms_menu;
  patch_header(&sms_menuhdr);
  for(n=1; n<TAB_N; n++)
  {
    void *so;
    int type;
    m_gui=GetMultiLinesMenuGUI(ma, mf);
    switch(n)
    {
    case 1: type=TYPE_IN_ALL;break;
    case 2: type=TYPE_OUT;break;
    case 3: type=TYPE_DRAFT;break;
    //case 4: type=0;break;
    case 4: type=TYPE_FILTER;break;
    }
    so=GetSLUserPointer(dlg_csm, type, 1);
    //so=malloc(sizeof(SML_OP));
    //so->type=type;
    //so->is_tab=1;
    //so->dlg_csm=dlg_csm;
    SetMenuToGUI(m_gui, &sms_menu);
    SetMenuItemCount(m_gui, getCountByType(type));
    MenuSetUserPointer(m_gui, so);
    SetCursorToMenuItem(m_gui, 0);
    SetHeaderToMenu(m_gui, &sms_menuhdr, ma);
    SetGUIToTabGUI(tab_gui, n, TabIcons[n], m_gui);
  }
  SetCursorTab(tab_gui, CFG_DEFAULT_TAB);
  UpdateTab1stItem(tab_gui, 0);
  gui_id=CreateGUI(tab_gui);
  pushGS(dlg_csm, gui_id);
  return gui_id;
}


