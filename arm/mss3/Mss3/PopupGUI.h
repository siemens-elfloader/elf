#ifndef _POPUPGUI_H_
#define _POPUPGUI_H_

class PopupNewIn// :
//  public CFile
{
public:
  PopupNewIn();
  ~PopupNewIn();
  int CreatePopupNewIn(DLG_CSM *dlg_csm, SDLIST *sdl);
private:
  static void UpdateCSMName(DLG_CSM *dlg_csm, int lgp);
  POPUP_DESC popup;
  DLG_CSM *dlg_csm;
  SDLIST *sdl;
  CLIST *cl;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
};

class MyShowMsg
{
public:
  static int MyShow(int flag, WSHDR *msg);
  static int MyShow(int flag, char *msg);
private:
  static POPUP_DESC popup;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
};
#endif



