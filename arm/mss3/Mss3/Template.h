#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

typedef struct _TPLIST
{
  _TPLIST *next;
  WSHDR *text;
}TPLIST;

class TplMenu :
  public CFile
{
public:
  TplMenu();
  ~TplMenu();
  int CreateTplMenu(void *edgui);
private:
  MENU_DESC menu;
  void *edgui;
  TPLIST *tpltop;
  TPLIST *AllocTPList(void);
  void AddToTPList(TPLIST *tpl);
  void FreeTPList(void);
  int ReadTpl(void);
  TPLIST *GetTpl(int n);
  static int OnKey(void *data, GUI_MSG *msg);
  static void GHook(void *data, int cmd);
  static void ItemProc(void *data, int curitem, void *user_pointer);
};

#endif


