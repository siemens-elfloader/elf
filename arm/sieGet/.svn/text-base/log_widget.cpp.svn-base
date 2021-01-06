
#include "include.h"
#include "rect_patcher.h"
#include "log_widget.h"
#include "url_input.h"
#include "daemon.h"
#include "langpack.h"


/*******************************************************************************
 LogInput
*******************************************************************************/

int loginput_onkey(GUI *gui, GUI_MSG *msg)
{
  LogInput * li = (LogInput *)EDIT_GetUserPointer(gui);
  return li->onKey(gui, msg);
}

void loginput_ghook(GUI *gui, int cmd)
{
  LogInput * li = (LogInput *)EDIT_GetUserPointer(gui);
  li->gHook(gui, cmd);
}

void loginput_locret(void) {};

SOFTKEY_DESC loginput_sk[]=
{
  {0x0018,0x0000,(int)"OK"},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB loginput_skt=
{
  loginput_sk,0
};

HEADER_DESC loginput_hdr={0,0,0,0,NULL, NULL,LGP_NULL};

INPUTDIA_DESC loginput_desc=
{
  1,
  loginput_onkey,
  loginput_ghook,
  (void *)loginput_locret,
  0,
  &loginput_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// Поменять софт-кнопки
};

int  LogInput::onKey(GUI *gui, GUI_MSG *msg)
{
  return (GUI_RESULT_OK);
}

void LogInput::gHook(GUI *gui, int cmd)
{
  if (cmd==TI_CMD_DESTROY)
  {
    delete this;
  }
}

void LogInput::Show(Log::LogLine * first_line, Log::LogLine * last_line, int lines_n)
{
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  void * ma = malloc_adr();
  void * eq;

  eq = AllocEQueue(ma, mfree_adr());
  
  LockSched();
  while (last_line->next->index>last_line->index && last_line->next->index - first_line->index < lines_n - 1)
    last_line = last_line->next;
  UnlockSched();

  int total_len=0;
  
  Log::LogLine * curr_line = first_line;
  for (int i = first_line->index; i <= last_line->index; i++)
  {
    total_len += wstrlen(curr_line->str) + 1;
    curr_line = curr_line->next;
  }
  WSHDR * ws = AllocWS(total_len);
  curr_line = first_line;
  for (int i = first_line->index; i<=last_line->index; i++)
  {
    wstrcat(ws, curr_line->str);
    curr_line = curr_line->next;
  }
  PrepareEditControl(&ec);
  PrepareEditCOptions(&ec_options);
  SetFontToEditCOptions(&ec_options, 1);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, total_len);
  CopyOptionsToEditControl(&ec, &ec_options);
  AddEditControlToEditQend(eq, &ec, ma);

  FreeWS(ws);
  patch_header(&loginput_hdr, NULL, (int)LangPack::Active->data[LGP_ViewLog]);
  patch_input(&loginput_desc);
  CreateInputTextDialog(&loginput_desc,&loginput_hdr,eq,1,this);
}

/*******************************************************************************
 LogWidget
*******************************************************************************/

char clLOGWIDGETBG  [4] = {0x0, 0x0, 0x0, 0x64};
char clLOGWIDGETTEXT[4] = {0xFF, 0xFF, 0xFF, 0x64};
char clLOGWIDGETSCROLLBAR[4] = {0xFF, 0xFF, 0xFF, 0x64};

LogWidget * LogWidget::Active = NULL;

void LogWidget::onRedraw()
{
  DrawRectangle(Canvas.x, Canvas.y, Canvas.x2, Canvas.y2, 0, 0, clLOGWIDGETBG);
  if (!log || !first_line)
  {
    WSHDR * ws = AllocWS(32);
    ascii2ws(ws, "No log...");
    DrawString(ws, Canvas.x, Canvas.y, Canvas.x2, Canvas.y2, FONT_SMALL, 0, clLOGWIDGETTEXT, 0);
    FreeWS(ws);
    return;
  }
  LockSched();
  while ((last_line->next->index > last_line->index) && ((last_line->next->index - first_line->index) < lines_on_page))
    last_line = last_line->next;
  UnlockSched();

  int y = Canvas.y;
  Log::LogLine * curr_line=first_line;
  for (int i = first_line->index; i<=last_line->index; i++)
  {
    DrawScrollString(curr_line->str, Canvas.x, y, Canvas.x2-6, y+line_height, line_offset+1, FONT_SMALL, 0, GetPaletteAdrByColorIndex(curr_line->color), 0);
    y += line_height;
    curr_line = curr_line->next;
  }
  
  DrawLine(Canvas.x2-2, Canvas.y+1, Canvas.x2-2, Canvas.y2-1, 0, clLOGWIDGETSCROLLBAR);
  if (log->log_start->prev->index - log->log_start->index)
  {
    int ys1 = (first_line->index *(Canvas.y2 - Canvas.y - 2)) /
              (log->log_start->prev->index - log->log_start->index);
    int ys2 = (last_line->index * (Canvas.y2 - Canvas.y - 2)) /
              (log->log_start->prev->index - log->log_start->index);
    DrawRectangle(Canvas.x2-3, Canvas.y+ys1+2, Canvas.x2-1, Canvas.y+ys2-1, 0, 0, clLOGWIDGETSCROLLBAR);
  }
}

void LogWidget::onCreate()
{

}

void LogWidget::onFocus()
{
  isFocused = 1;
}

void LogWidget::onUnFocus()
{
  isFocused = 0;
}

void LogWidget::onClose()
{
  delete this;
}

int  LogWidget::onKey(char key_code, int key_msg, short keys)
{
  if (key_msg == KEY_DOWN || key_msg == LONG_PRESS)
  {
    switch (key_code)
    {
    case RED_BUTTON:
    case RIGHT_SOFT:
      return GUI_RESULT_CLOSE;
    case ENTER_BUTTON:
      if (log && first_line)
      {
        LogInput * li = new LogInput;
        li->Show(first_line, last_line, lines_on_page);
      }
      return GUI_RESULT_OK;
    case LEFT_BUTTON:
      line_offset -= 50;
      if (line_offset < 0)
        line_offset = 0;
      Redraw();
      return GUI_RESULT_OK;
    case RIGHT_BUTTON:
      line_offset += 50;
      Redraw();
      return GUI_RESULT_OK;
    case UP_BUTTON:
    case '2':
      if (key_msg == KEY_DOWN)
        ScrollUp();
      if (key_msg == LONG_PRESS)
        PrevPage();
      return GUI_RESULT_OK;
    case DOWN_BUTTON:
    case '8':
      if (key_msg == KEY_DOWN)
        ScrollDown();
      if (key_msg == LONG_PRESS)
        NextPage();
      return GUI_RESULT_OK;
    case '4':
      PrevPage();
      return GUI_RESULT_OK;
    case '6':
      NextPage();
      return GUI_RESULT_OK;
    }
  }
  return GUI_RESULT_OK;
}

void LogWidget::Redraw()
{
  if (isFocused)
    REDRAW();
}

void LogWidget::ScrollUp()
{
  if (log && first_line)
  {
    if (first_line->index > first_line->prev->index)
    {
      last_line = last_line->prev;
      first_line = first_line->prev;
      Redraw();
    }
  }
}

void LogWidget::ScrollDown()
{
  if (log && first_line)
  {
    if (last_line->index < last_line->next->index)
    {
      last_line = last_line->next;
      first_line = first_line->next;
      Redraw();
    }
  }
}

void LogWidget::PrevPage()
{
  if (log && first_line)
  {
    for(int i = 0; i < lines_on_page; i ++)
    {
      if (first_line->index > first_line->prev->index)
      {
        last_line = last_line->prev;
        first_line = first_line->prev;
      }
    }
    Redraw();
  }
}

void LogWidget::NextPage()
{
  if (log && first_line)
  {
    for(int i = 0; i < lines_on_page; i ++)
    {
      if (last_line->index < last_line->next->index)
      {
        last_line = last_line->next;
        first_line = first_line->next;
      }
    }
    Redraw();
  }
}

LogWidget::LogWidget(Log * show_log)
{
  Active = this;
  log = show_log;
  first_line = log->log_start;
  last_line = first_line;
  line_height = GetFontYSIZE(FONT_SMALL) + 2;
  lines_on_page = (Canvas.y2-Canvas.y) / line_height;
  line_offset = 0;
}

LogWidget::~LogWidget()
{
}
