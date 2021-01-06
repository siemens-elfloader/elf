#ifndef _COLOR_H_
#define _COLOR_H_

#include "main.h"
#include "jabber_util.h"

extern char * cur_color_name; // »м€ текущего файла цветовой схемы

typedef struct
{
  char r;
  char g;
  char b;
  char a;
}RGBA;

//=============Ќекоторые цвета====================

extern RGBA MAINBG_NOT_CONNECTED;
extern RGBA MAINBG_CONNECTED;
extern RGBA MAINBG_ERROR;
extern RGBA MAINFONT_NOT_CONNECTED;
extern RGBA MAINFONT_CONNECTED;
extern RGBA MAINFONT_ERROR;
extern RGBA MESSAGEWIN_BGCOLOR; // ќбщий фон месаж листа
extern RGBA MESSAGEWIN_TITLE_BGCOLOR; // ‘он заголовка
extern RGBA MESSAGEWIN_TITLE_FONT; // ÷вет шрифта заголовка
extern RGBA MESSAGEWIN_MY_BGCOLOR; // ÷вет фона исход€щих приватных сообщений
extern RGBA MESSAGEWIN_CH_BGCOLOR; // ÷вет фона приватных сообщений
extern RGBA MESSAGEWIN_CURSOR_BGCOLOR; // ÷вет фона курсора
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_1; // „ередование: ÷вет фона сообщений конференции 1
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_2; // „ередование: ÷вет фона сообщений конференции 2
extern RGBA MESSAGEWIN_SYS_BGCOLOR;  // ÷вет фона сообщений уведомлений
extern RGBA MESSAGEWIN_STATUS_BGCOLOR;  // ÷вет фона сообщений смены статуса
extern RGBA MESSAGEWIN_CHAT_FONT; // ÷вет шрифта сообщений
extern RGBA CURSOR; // ÷вет курсора
extern RGBA CURSOR_BORDER; // ÷вет ободка курсора
extern RGBA CLIST_F_COLOR_0; // ÷вет шрифта
extern RGBA CLIST_F_COLOR_1; // ÷вет шрифта (есть сообщени€)
extern RGBA CONTACT_BG_0; // „ередование линий контакт листа: цвет фона 1
extern RGBA CONTACT_BG_1; // „ередование линий контакт листа: цвет фона 2
extern RGBA lineColor; // ÷вет текущей строчки \\ дублируетс€ CURSOR!!!
extern RGBA borderColor; // ÷вет ободка текущей строчки \\ дублируетс€ CURSOR_BORDER!!!

extern RGBA PRES_COLORS[PRES_COUNT] ;

void ShowSelectColorMenu();
int InitColorSet(const char *fname);
#endif
