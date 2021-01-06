#ifndef _LOG_H_
#define _LOG_H_

#define DEBUG(arg) Log::Active->PrintLn(arg);

#define LOG_TO_FILE

class Log
{
public:
  void PrintLn(const char *str);
  Log();
  ~Log();
  struct LogLine
  {
    int index;
    WSHDR *str;
    TTime time;
    TDate date;
    LogLine *next;
    LogLine *prev;
  };
  LogLine *log_start;

  static Log *Active;
private:
  void _add_line(WSHDR *ws);
};

#endif
