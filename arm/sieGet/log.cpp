#include "include.h"
#include "string_util.h"
#include "log.h"
#include "dialog.h"
#include "log_widget.h"
#include "file_works.h"

void Log::PrintToFile(const char *str)
{
  unsigned int io_error = 0;
  if (hFile == -1)
    hFile = fopen(filename, A_ReadWrite + A_Create + A_Append + A_BIN, P_WRITE, &io_error); 
  if(!io_error)
  {
    fwrite(hFile, str, strlen(str), &io_error);
    fwrite(hFile, "\r\n", 2, &io_error);
  }
}

void Log::ChangeFileName(char * fname)
{
  unsigned int io_error = 0;
  
  char * logs_path = getSymbolicPath("$logs\\");
  
  char * name = new char[strlen(fname) + 1];
  strcpy(name, fname);
  remove_bad_chars(name);
  char * new_fname = new char[strlen(logs_path) + strlen(name) + 9];
  sprintf(new_fname, "%s%s.log", logs_path, name);
  unlink(new_fname, &io_error);
  fmove(filename, new_fname, &io_error);
  delete filename;
  delete logs_path;
  filename = new_fname;
}

Log::Log()
{
  hFile = -1;
  unsigned int io_error = 0;
  
  char * logs_path = getSymbolicPath("$logs\\");
  filename = new char[strlen(logs_path) + 32];
  strcpy(filename, logs_path);
  delete logs_path;
  strcat(filename, "temp.log");
  log_start = NULL;
  
  unlink(filename, &io_error);
}

Log::~Log()
{
  CloseFile();
  
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
    if (CFG_LOG_DATE_TIME)
    {
      TTime time;
      TDate date;
      GetDateTime(&date, &time);
      char * tmp_str = new char[len + 32];
      sprintf(tmp_str, "[%02d.%02d.%02d-%02d:%02d:%02d] %s", date.day, date.month, date.year, time.hour, time.min, time.sec, str);
      PrintToFile(tmp_str);
      delete tmp_str;
    }
    else
      PrintToFile(str);
  }
  if (LogWidget::Active)
    LogWidget::Active->Redraw();
}

void Log::DeleteFile()
{
  unsigned int io_error = 0;
  if (hFile != -1)
    fclose(hFile, &io_error);
  hFile = -1;
  unlink(filename, &io_error);
}

void Log::CloseFile()
{
  unsigned int io_error = 0;
  if (hFile != -1)
    fclose(hFile, &io_error);
  hFile = -1;
}
