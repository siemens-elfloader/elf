
#include "include.h"
#include "string_util.h"
#include "log.h"
#include "dialog.h"
#include "log_widget.h"
#include "file_works.h"

void Log::PrintToFile(const char *str)
{
  volatile int hFile;
  unsigned int io_error = 0;
  hFile = fopen(filename, A_ReadWrite+A_Create+A_Append+A_BIN, P_READ+P_WRITE, &io_error); 
  if(!io_error)
  {
    fwrite(hFile, str, strlen(str), &io_error);
    fwrite(hFile, "\r\n", 2, &io_error);
    fclose(hFile, &io_error);
  }
}

void Log::ChangeFileName(char * fname)
{
  char logs_path[256];
  unsigned int io_error = 0;
  
  getSymbolicPath(logs_path, "$logs\\");
  char * name = new char[strlen(fname)+1];
  strcpy(name, fname);
  remove_bad_chars(name);
  char * new_fname = new char[strlen(logs_path) + strlen(name) + 9];
  sprintf(new_fname, "%s%s.log", logs_path, name);
  unlink(new_fname, &io_error);
  fmove(filename, new_fname, &io_error);
  delete filename;
  filename = new_fname;
}

Log::Log()
{
  char logs_path[256];
  unsigned int io_error = 0;
  
  getSymbolicPath(logs_path, "$logs\\");
  filename = new char[strlen(logs_path) + 32];
  strcpy(filename, logs_path);
  strcat(filename, "temp.log");
  log_start = NULL;
  
  unlink(filename, &io_error);
}

Log::~Log()
{
  LogLine *tmp = log_start;
  while (tmp->next!=tmp)
  {
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    FreeWS(tmp->str);
    LogLine *tmp2 = tmp;
    tmp = tmp->next;
    delete tmp2;
  }
  FreeWS(tmp->str);
  delete tmp;
  delete filename;
}

void Log::_add_line(WSHDR *ws, CLR_ID color)
{
  LogLine * tmp = new LogLine;
  tmp->str = ws;
  tmp->color = color;
  LockSched();
  if(log_start)
  {
    tmp->index = log_start->prev->index+1;
    tmp->prev = log_start->prev;
    log_start->prev->next = tmp;
    tmp->next = log_start;
    log_start->prev = tmp;
  }
  else
  {
    tmp->index = 0;
    log_start = tmp;
    log_start->next = log_start;
    log_start->prev = log_start;
  }
  UnlockSched();
}

void Log::Print(const char * str, CLR_ID color)
{
  int len = strlen(str);
  
  WSHDR * ws = AllocWS(len + 6);
  ascii2ws(ws, str);
  if(str[len]!='\r' && str[len]!='\n')
    wsInsertChar(ws, '\n', len + 1);
  _add_line(ws, color);
  
  if (CFG_LOG_TO_FILE)
  {
    TTime time;
    TDate date;
    GetDateTime(&date, &time);
    char * _str = new char[len + 32];
    sprintf(_str, "[%02d.%02d.%02d-%02d:%02d:%02d] %s", date.day, date.month, date.year, time.hour, time.min, time.sec, str);
    PrintToFile(_str);
    delete _str;
  }
  if (LogWidget::Active)
    LogWidget::Active->Redraw();
}
