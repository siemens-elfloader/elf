#ifndef _LIST_H_
#define _LIST_H_

#include "include.h"

class ListOptions
{
public:
  ListOptions();
  ~ListOptions();
  
  void Show();
  void gHook(void * data, int cmd);

  int gui_id;
  
  static TDaemonList * DaemonList;
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
  TDaemonList * dl;  
};

#endif

