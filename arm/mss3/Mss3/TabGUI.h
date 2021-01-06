#ifndef _TABGUI_H_
#define _TABGUI_H_
class TabGUI
{
public:
  int ReCreateTabGUI(DLG_CSM *dlg_csm);
  TabGUI();
  ~TabGUI();
  int CreateTabGUI(DLG_CSM *dlg_csm);
private:
  TABGUI_DESC *tab_desc;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void Locret(void);
};
#endif


