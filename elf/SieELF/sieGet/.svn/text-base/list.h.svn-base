#ifndef _LIST_H_
#define _LIST_H_

#include "include.h"
#include "inet.h"

class ListOptions
{
public:
  ListOptions();
  ~ListOptions();
  
  void Show(Download * _dl);
  void gHook(void * data, int cmd);

  int gui_id;
  Download * dl;
};

class List
{
public:
  List();
  ~List();
  
  void Show();
  int onKey(void * data, GUI_MSG * msg);
  void gHook(void * data, int cmd);
  void ItemHandler(void * data, int curitem, void * unk);
  int gui_id;
  
  static List * Active;
private:
  void wsprintf_bytes(WSHDR * ws, int bytes);
  void wsprintf_bytes(WSHDR * ws, int bytes1, int bytes2);
};

#endif

