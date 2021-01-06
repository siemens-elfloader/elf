#ifndef _COLOR_H_
#define _COLOR_H_

#include "main.h"
#include "jabber_util.h"

extern char * cur_color_name; // ��� �������� ����� �������� �����

typedef struct
{
  char r;
  char g;
  char b;
  char a;
}RGBA;

//=============��������� �����====================

extern RGBA MAINBG_NOT_CONNECTED;
extern RGBA MAINBG_CONNECTED;
extern RGBA MAINBG_ERROR;
extern RGBA MAINFONT_NOT_CONNECTED;
extern RGBA MAINFONT_CONNECTED;
extern RGBA MAINFONT_ERROR;
extern RGBA MESSAGEWIN_BGCOLOR; // ����� ���
extern RGBA MESSAGEWIN_TITLE_BGCOLOR; // ��� ���������
extern RGBA MESSAGEWIN_TITLE_FONT; // ���� ������ ���������
extern RGBA MESSAGEWIN_MY_BGCOLOR; // ���� ���� ��������� ���������
extern RGBA MESSAGEWIN_CH_BGCOLOR; // ���� ���� ��������� ���������
extern RGBA MESSAGEWIN_CURSOR_BGCOLOR; // ���� ���� �������
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_1; // �����������: ���� ���� ��������� ����������� 1
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_2; // �����������: ���� ���� ��������� ����������� 2
extern RGBA MESSAGEWIN_SYS_BGCOLOR;  // ���� ���� ��������� �����������
extern RGBA MESSAGEWIN_STATUS_BGCOLOR;  // ���� ���� ��������� ����� �������
extern RGBA MESSAGEWIN_CHAT_FONT; // ���� ������ ���������
extern RGBA CURSOR; // ���� �������
extern RGBA CURSOR_BORDER; // ���� ������ �������
extern RGBA CLIST_F_COLOR_0; // ���� ������
extern RGBA CLIST_F_COLOR_1; // ���� ������ (���� ���������)
extern RGBA CONTACT_BG_0; // �����������: ���� ���� 1
extern RGBA CONTACT_BG_1; // �����������: ���� ���� 2
extern RGBA lineColor; // ���� ������� �������
extern RGBA borderColor; // ���� ������ ������� �������

extern RGBA OnlineColor;
extern RGBA ChatColor;
extern RGBA AwayColor;
extern RGBA XAColor;
extern RGBA DNDColor;
extern RGBA InvisibleColor;
extern RGBA OfflineColor;
extern RGBA ErrorColor;
extern RGBA SubscribeColor;
extern RGBA SubscribedColor;
extern RGBA UnsubscribeColor;
extern RGBA UnsubscribedColor;

extern RGBA PRES_COLORS[PRES_COUNT] ;

int ReadColor(const char * fname);
void ShowSelectColorMenu();

#endif
