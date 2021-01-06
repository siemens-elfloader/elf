#ifndef _EDITGUI_H_
#define _EDITGUI_H_

#define ED_VIEW 1 //00000001
#define ED_EDIT 2 //00000010
#define ED_REPLY 4 //00000100 //new = reply, num=0
#define ND_FREE 128 //10000000

class EditGUI
{
public:
	int AddNumberBlank(void *data);
	int SetNumber(void *data, char*number);
	int InsertNumber(void *data, char *number);
	int SaveDraft(WSHDR *text);
	int EditSendSMS(WSHDR *text);
	int InsertNumber(void *data, WSHDR *number);
	int SetNumber(void *data, WSHDR *number);
	int InsertText(void *data, WSHDR *text);
	int CreateEditGUI(DLG_CSM *dlg_csm, const char *nums);
  int n_focus;
  NumList *nlst;
  EditGUI();
  ~EditGUI();
  int CreateEditGUI(DLG_CSM *dlg_csm, SDLIST *sdl, int gui_prop, int list_type, int need_free);
private:
  void UpdateCSMName(DLG_CSM *dlg_csm, int lgp);
  INPUTDIA_DESC edit;
  int gui_prop;
  int gui_id;
  int list_type;
  SDLIST *sdl;
  DLG_CSM *dlg_csm;
//  CLIST *cl;
//  char number[50];
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void Locret(void);
  static void DoSmsWorkBG(void *ed_gui, int gui_id);
  static void EdOpUserItem(USR_MENU_ITEM *item);
};

class EditOptionMenu
{
public:
  EditOptionMenu();
  ~EditOptionMenu();
  int CreateEditOptionMenu(DLG_CSM *dlg_csm, SDLIST *sdl, int edit_id, int list_type, int nd_free);
private:
  MENU_DESC menu;
  int edit_id;
  SDLIST *sdl;
  DLG_CSM *dlg_csm;
  int nd_free;
  int list_type;
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void ItemProc(void *data, int curitem, void *user_pointer);
};
#endif

