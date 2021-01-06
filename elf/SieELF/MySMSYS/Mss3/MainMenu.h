#ifndef _MAINMENU_H_
#define _MAINMENU_H_
class MainMenu
{
public:
  void * GetMainMenuGUI(DLG_CSM *dlg_csm, int cur);
  MainMenu();
  ~MainMenu();
  int CreateMainMenu(DLG_CSM *dlg_csm);
private:
  MENU_DESC menu;
  int gui_id;
  DLG_CSM *dlg_csm;
  void UpdateCSMName(DLG_CSM *dlg_csm, int lgp);
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void ItemProc(void *data, int curitem, void *user_pointer);
};

#endif

