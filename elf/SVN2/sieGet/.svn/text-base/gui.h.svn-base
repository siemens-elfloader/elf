#ifndef _GUI_H_
#define _GUI_H_

#include "include.h"

#define GUI_RESULT_REDRAW (-1)
#define GUI_RESULT_CLOSE  ( 1)
#define GUI_RESULT_OK     ( 0)

class AbstractGUI
{
public:
  GUI gui;

  int gui_id;
  RECT Canvas;

  virtual void onRedraw()  = 0;
  virtual void onCreate()  = 0;
  virtual void onFocus()   = 0;
  virtual void onUnFocus() = 0;
  virtual void onClose()   = 0;
  virtual int  onKey(char key_code, int key_msg, short keys) = 0;

  void Create();
  void Close();

  AbstractGUI();
  ~AbstractGUI();
};

#endif
