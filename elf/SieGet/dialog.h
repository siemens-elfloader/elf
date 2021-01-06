#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "include.h"
#include "csm.h"
#include "gui.h"
#include "widget.h"

#define DIALOG_CSM_NAME "SieGet"

class SieGetGUI: public AbstractGUI
{
public:
  virtual void onRedraw();
  virtual void onCreate();
  virtual void onFocus();
  virtual void onUnFocus();
  virtual void onClose();
  virtual int  onKey(char key_code, int key_msg, short keys);

  SieGetGUI();
  virtual ~SieGetGUI();
  void Redraw(int bm);
private:
  int bm_current;

  //Geometry
  int tabs_h;
  int tab_w;

  //Widgets

  Widget *tabs[3];
};


class SieGetDialog: public DialogCSM
{
public:
  virtual void onCreate();
  virtual int onMessage(GBS_MSG *msg);
  virtual void onClose();

  SieGetDialog();
  ~SieGetDialog();
  SieGetGUI *gui;

  static SieGetDialog *Active;
  void Redraw(int bm);
};

#endif
