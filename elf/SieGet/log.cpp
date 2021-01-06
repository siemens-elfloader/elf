
#include "include.h"
#include "string_util.h"
#include "log.h"
#include "dialog.h"

Log *Log::Active = NULL;

extern "C"
{
  void _C_LOG(const char *str)
  {
    if (Log::Active)
      Log::Active->PrintLn(str);
  }
}

#ifdef LOG_TO_FILE
void PrintToFile(const char *str)
{
  volatile int hFile;
  unsigned int io_error = 0;
  char fullname[] ="4:\\ZBin\\var\\SieGET.log";
  hFile = fopen(fullname, A_ReadWrite+A_Create+A_Append+A_BIN, P_READ+P_WRITE, &io_error);
  if(!io_error)
  {
    fwrite(hFile, str, strlen(str), &io_error);
    fwrite(hFile, "\r\n", 2, &io_error);
    fclose(hFile, &io_error);
  }
}
#endif

Log::Log()
{
  char welcome_str[] = "--- LOG START ---";
  log_start = new LogLine;
  log_start->index = 0;
  log_start->str = AllocWS(256);
  ascii2ws(log_start->str, welcome_str);
  log_start->next = log_start;
  log_start->prev = log_start;
  Active = this;

  PrintToFile(welcome_str);
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
}

void Log::_add_line(WSHDR *ws)
{
  LogLine *tmp = new LogLine;
  tmp->str = ws;
  GetDateTime(&tmp->date, &tmp->time);
  LockSched();
  tmp->index = log_start->prev->index+1;
  tmp->prev = log_start->prev;
  log_start->prev->next = tmp;
  tmp->next = log_start;
  log_start->prev = tmp;
  UnlockSched();
}

void Log::PrintLn(const char *str)
{
  WSHDR *ws = AllocWS(strlen(str)+4);
  ascii2ws(ws, str);
  _add_line(ws);

#ifdef LOG_TO_FILE
  PrintToFile(str);
#endif

  if (SieGetDialog::Active)
    SieGetDialog::Active->Redraw(2);
}
