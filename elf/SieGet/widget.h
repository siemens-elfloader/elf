#ifndef _WIDGET_H_
#define _WIDGET_H_

#include "include.h"
#include "log.h"

class Widget
{
public:
  RECT Canvas;
  virtual void onKey(int key_code, int key_msg) {};
  virtual void onRedraw() {};
  virtual void onFocus() {};
  virtual void onUnFocus() {};
  virtual void onResize() {};

  Widget();

  void Resize();
  void Resize(RECT *rc);
  void Resize(int x, int y, int x2, int y2);
};

//---------------------------------------------------------------

class LogWidget: public Widget
{
public:
  virtual void onKey(int key_code, int key_msg);
  virtual void onRedraw();
  virtual void onFocus();
  virtual void onUnFocus();

  LogWidget();
  LogWidget(RECT *rc);
  LogWidget(int x, int y, int x2, int y2);
  ~LogWidget();

  void ScrollDown();
  void ScrollUp();
private:
  Log *log;
  Log::LogLine *first_line, *last_line;
  int lines_on_page;
  int line_height;
  int line_offset;
  int isFocused;
};

class ListWidget: public Widget
{
public:
  virtual void onKey(int key_code, int key_msg);
  virtual void onRedraw();

  ListWidget();
  ListWidget(RECT *rc);
  ListWidget(int x, int y, int x2, int y2);
  ~ListWidget();
};

class InfoWidget: public Widget
{
public:
  virtual void onKey(int key_code, int key_msg);
  virtual void onRedraw();

  InfoWidget();
  InfoWidget(RECT *rc);
  InfoWidget(int x, int y, int x2, int y2);
  ~InfoWidget();
};

#endif

