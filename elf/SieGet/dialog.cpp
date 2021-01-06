
#include "include.h"
#include "dialog.h"
#include "log.h"

char percent_t[] = "%t";

char clBG[4] = {72, 72, 72, 100};
char clLine[4] = {255, 255, 255, 100};
char clText[4] = {255, 255, 255, 100};
char clBMsel[4] = {0, 0, 0, 100};

//---------------------------------------------------------------//
//                            SieGetGUI                          //
//---------------------------------------------------------------//

void SieGetGUI::onRedraw()
{
  WSHDR *ws = AllocWS(256);
  tabs[bm_current]->onRedraw();

  if (bm_current==0)
  {
    DrawRectangle(Canvas.x, Canvas.y2-tabs_h, Canvas.x+tab_w-1, Canvas.y2, 0, clLine, clBMsel);
    DrawLine(Canvas.x, Canvas.y2-tabs_h, Canvas.x+tab_w-1, Canvas.y2-tabs_h, 0, clBMsel);
  }
  else
    DrawRectangle(Canvas.x, Canvas.y2-tabs_h, Canvas.x+tab_w-1, Canvas.y2, 0, clLine, clBG);
  if (bm_current==1)
  {
    DrawRectangle(Canvas.x+tab_w, Canvas.y2-tabs_h, Canvas.x2-tab_w, Canvas.y2, 0, clLine, clBMsel);
    DrawLine(Canvas.x+tab_w, Canvas.y2-tabs_h, Canvas.x2-tab_w, Canvas.y2-tabs_h, 0, clBMsel);
  }
  else
    DrawRectangle(Canvas.x+tab_w, Canvas.y2-tabs_h, Canvas.x2-tab_w, Canvas.y2, 0, clLine, clBG);
  if (bm_current==2)
  {
    DrawRectangle(Canvas.x2-tab_w+1, Canvas.y2-tabs_h, Canvas.x2, Canvas.y2, 0, clLine, clBMsel);
    DrawLine(Canvas.x2-tab_w+1, Canvas.y2-tabs_h, Canvas.x2, Canvas.y2-tabs_h, 0, clBMsel);
  }
  else
    DrawRectangle(Canvas.x2-tab_w+1, Canvas.y2-tabs_h, Canvas.x2, Canvas.y2, 0, clLine, clBG);

  wsprintf(ws, percent_t, "Info");
  DrawString(ws, Canvas.x, Canvas.y2-tabs_h+1, Canvas.x+tab_w-1, Canvas.y2-1, FONT_SMALL, TEXT_ALIGNMIDDLE, clText, 0);
  wsprintf(ws, percent_t, "List");
  DrawString(ws, Canvas.x+tab_w, Canvas.y2-tabs_h+1, Canvas.x2-tab_w, Canvas.y2-1, FONT_SMALL, TEXT_ALIGNMIDDLE, clText, 0);
  wsprintf(ws, percent_t, "Log");
  DrawString(ws, Canvas.x2-tab_w+1, Canvas.y2-tabs_h+1, Canvas.x2, Canvas.y2-1, FONT_SMALL, TEXT_ALIGNMIDDLE, clText, 0);

  FreeWS(ws);
}

void SieGetGUI::onCreate()
{

}

void SieGetGUI::onFocus()
{
  tabs[bm_current]->onFocus();
}

void SieGetGUI::onUnFocus()
{
  tabs[bm_current]->onUnFocus();
}

void SieGetGUI::onClose()
{

}

int  SieGetGUI::onKey(char key_code, int key_msg, short keys)
{
  if (key_msg==KEY_DOWN)
    switch (key_code)
    {
    case RED_BUTTON:
    case RIGHT_SOFT:
      return GUI_RESULT_CLOSE;

    case '*':
      tabs[bm_current]->onUnFocus();
      bm_current = 0;
      tabs[bm_current]->onFocus();
      break;
    case '0':
      tabs[bm_current]->onUnFocus();
      bm_current = 1;
      tabs[bm_current]->onFocus();
      break;
    case '#':
      tabs[bm_current]->onUnFocus();
      bm_current = 2;
      tabs[bm_current]->onFocus();
      break;
    }
  REDRAW();
  tabs[bm_current]->onKey(key_code, key_msg);
  return GUI_RESULT_OK;
}

void SieGetGUI::Redraw(int bm)
{
  if (bm_current==bm)
    REDRAW();
}

SieGetGUI::SieGetGUI()
{
  bm_current = 0;
  tabs_h = GetFontYSIZE(FONT_SMALL)+2;
  tab_w = (Canvas.x2-Canvas.x)/3;

  tabs[0] = new InfoWidget;
  tabs[1] = new ListWidget;
  tabs[2] = new LogWidget;

  tabs[0]->Resize(Canvas.x, Canvas.y, Canvas.x2, Canvas.y2-tabs_h-1);
  tabs[1]->Resize(Canvas.x, Canvas.y, Canvas.x2, Canvas.y2-tabs_h-1);
  tabs[2]->Resize(Canvas.x, Canvas.y, Canvas.x2, Canvas.y2-tabs_h-1);
}

SieGetGUI::~SieGetGUI()
{
  delete tabs[0];
  delete tabs[1];
  delete tabs[2];
}

//---------------------------------------------------------------//
//                            SieGetDialog                       //
//---------------------------------------------------------------//

SieGetDialog *SieGetDialog::Active = NULL;

void SieGetDialog::onCreate()
{
  SetName(DIALOG_CSM_NAME);
  gui->Create();
  Log::Active->PrintLn("Dialog created!");
}

int SieGetDialog::onMessage(GBS_MSG *msg)
{
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==gui->gui_id))
  {
    data->state=-3;
    gui->gui_id = 0;
    Close();
  }
  return CSM_MSG_RESULT_CONTINUE;
}

void SieGetDialog::onClose()
{
  Log::Active->PrintLn("Dialog closed!");
}

void SieGetDialog::Redraw(int bm)
{
  if (gui->gui_id && IsGuiOnTop(gui->gui_id))
  {
    gui->Redraw(bm);
  }
}

SieGetDialog::SieGetDialog()
{
  gui = new SieGetGUI;
  Active = this;
}

SieGetDialog::~SieGetDialog()
{
  delete gui;
}

