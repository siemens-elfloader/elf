#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "include.h"
#include "log.h"
#include "gui.h"

class LogInput
{
public:
  void Show(Log::LogLine * first_line, Log::LogLine * last_line, int lines_n);
  int onKey(GUI * gui, GUI_MSG * msg);
  void gHook(GUI * gui, int cmd);
};

class LogWidget: public AbstractGUI
{
public:
  virtual void onRedraw();
  virtual void onCreate();
  virtual void onFocus();
  virtual void onUnFocus();
  virtual void onClose();
  virtual int  onKey(char key_code, int key_msg, short keys);

  LogWidget(Log * show_log);
  ~LogWidget();
  
  static LogWidget * Active;
  void Redraw();
  
  void ScrollUp();
  void ScrollDown();
  void PrevPage();
  void NextPage();
  
private:
  Log * log;
  Log::LogLine * first_line, * last_line;
  int line_height;
  int line_offset;
  int lines_on_page;
  int isFocused;
};

#endif

