#include "include.h"
#include "csm.h"
#include "gui.h"

extern "C"
{
  extern void kill_data(void *p, void (*func_p)(void *));
}

void Killer(void){
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

//---------------------------------------------------------------

class MyGUI: public AbstractGUI
{
  virtual void onRedraw();
  virtual void onCreate();
  virtual void onFocus();
  virtual void onUnFocus();
  virtual void onClose();
  virtual int  onKey(char key_code, int key_msg, short keys);
};

void MyGUI::onRedraw()
{
  WSHDR *ws = AllocWS(200);
  wsprintf(ws, "%t", "Hello World");
  DrawString(ws, Canvas.x, Canvas.y, Canvas.x2, Canvas.y2, FONT_LARGE, 0, GetPaletteAdrByColorIndex(0), NULL);
  FreeWS(ws);
}

void MyGUI::onCreate()
{
}

void MyGUI::onFocus()
{
}

void MyGUI::onUnFocus()
{
}

void MyGUI::onClose()
{
}

int MyGUI::onKey(char key_code, int key_msg, short keys)
{
  if (key_code==RIGHT_SOFT)
    return GUI_RESULT_CLOSE;
  return GUI_RESULT_REDRAW;
}

//---------------------------------------------------------------


class MyDialogCSM: public DialogCSM
{
  virtual void onCreate();
  virtual int onMessage(GBS_MSG *msg);
  virtual void onClose();
  virtual ~MyDialogCSM();

  MyGUI *gui;
};

void MyDialogCSM::onCreate()
{
  SetName("CPPTEST");
  gui = new MyGUI();
  gui->Create();
}

void MyDialogCSM::onClose()
{
  delete gui;
  delete this;
  SUBPROC((void *)Killer);
}

int MyDialogCSM::onMessage(GBS_MSG *msg)
{
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==gui->gui_id))
  {
    data->state=-3;
    gui->gui_id = 0;
  }
  return(1);
}

MyDialogCSM::~MyDialogCSM()
{
}

MyDialogCSM *csm;

int main(char *exename, char *fname)
{
  csm = new MyDialogCSM();
  csm->Create();
  return 0;
}
