#ifndef _OTHERSMENU_H_
#define _OTHERSMENU_H_

class OthMenu
{
public:
	int CreateOthMenu(DLG_CSM *dlg_csm);
	OthMenu();
	~OthMenu();
private:
	void DelAllMss();
	void ExportTxtAll();
	void ShowHelp(void);
	void ShowAbout(void);
	void MoveAllMss(void);
	void OpenArchiveOTH();
	DLG_CSM * dlg_csm;
	void OpenCfgFile(void);
	static void ItemProc(void *data, int curitem, void *user_pointer);
	static void GHook(void *data, int cmd);
	static int OnKey(void *data, GUI_MSG *msg);
	MENU_DESC menu;
};
#endif
