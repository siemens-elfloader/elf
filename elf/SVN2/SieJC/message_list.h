/*
    SieNatJabber Project
    Функции показа сообщений контактов
*/
#ifndef _MESSAGE_LIST_H_
  #define _MESSAGE_LIST_H_

// Смещение, начиная с которого рисовать хистори
#define HIST_DISP_OFS 14

// Нечто, что будет использоваться для вывода строк
typedef struct
{
  MESS_TYPE mtype;
  unsigned short log_mess_number;
  WSHDR* mess;
  int line_height;
  void* next;
}DISP_MESSAGE;

// Отобразить список сообщений
void Display_Message_List(TRESOURCE* ContEx);

// Открыть окно написания нового сообщения
void Init_Message(TRESOURCE* ContEx, char *init_text);

void ParseMessagesIntoList(TRESOURCE* ContEx);
#endif
