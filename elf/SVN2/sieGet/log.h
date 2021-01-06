#ifndef _LOG_H_
#define _LOG_H_

enum CLR_ID // Цвета из прошивки
{
  /* Красный */
  CLR_Red=2,
  CLR_DarkRed=14,
  CLR_LightRed=8,
  /* Синий */
  CLR_Blue=6,
  CLR_DarkBlue=3,
  CLR_LightBlue=9,
  /* Зеленый */
  CLR_Green=4,
  CLR_DarkGreen=16,
  CLR_LightGreen=10,
  /* Фиолетовый */
  CLR_Violet=5,
  CLR_DarkViolet=17,
  CLR_LightViolet=11,
  /* Желтый */
  CLR_Yellow=7,
  CLR_DarkYellow=19,
  CLR_LightYellow=13,
  /* Серый */
  CLR_Grey=21,
  CLR_DarkGrey=20,
  CLR_LightGrey=22
};

class Log
{
public:
  void Print(const char * str, CLR_ID color);
  void PrintToFile(const char * str);
  void ChangeFileName(char * fname); 
  Log();
  ~Log();
  struct LogLine
  {
    int index;
    CLR_ID color;
    WSHDR * str;
    LogLine * next;
    LogLine * prev;
  };
  LogLine * log_start;
  char * filename;

  void DeleteFile();
  void CloseFile();
private:
  int hFile;
  void _add_line(WSHDR *ws, CLR_ID color);
};

#endif
