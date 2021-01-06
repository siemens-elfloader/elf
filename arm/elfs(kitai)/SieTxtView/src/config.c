#include "..\..\inc\cfg_items.h"
#include "..\..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0 = {CFG_CBOX,"�ַ�����", 0, 5};
__root const int charset = 0;
__root const CFG_CBOX_ITEM cfgcbox1[5] = {"�Զ�", "ANSI", "UNICODE LE", "UNICDOE BE", "UTF8"};

__root const CFG_HDR cfghdr1 = {CFG_UINT, "��ʷ�������", 0, 999};
__root const unsigned int maxhis = 20;

__root const CFG_HDR cfghdr_m10 = {CFG_LEVEL, "��������", 1, 0};

__root const CFG_HDR cfghdr10 = {CFG_INT, "�м��", 0, 50};
__root const int rowsplit = 2;

__root const CFG_HDR cfghdr11 = {CFG_INT, "�м��", 0, 50};
__root const int colsplit = 2;

__root const CFG_HDR cfghdr12 = {CFG_INT, "����", 0, 12};
__root const int font = FONT_SMALL;

__root const CFG_HDR cfghdr13 = {CFG_INT, "״̬������", 0, 12};
__root const int statfont = FONT_SMALL;

__root const CFG_HDR cfghdr_m11 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr_m20 = {CFG_LEVEL, "��ɫ����", 1, 0};
__root const CFG_HDR cfghdr20 = {CFG_COLOR, "�ı���ɫ", 0, 0};
__root const char fontcolor[4] = { 0xFF, 0xFF, 0xFF, 0x64 };
__root const CFG_HDR cfghdr21 = {CFG_COLOR, "������ɫ", 0, 0};
__root const char bgcolor[4] = { 0x0, 0x0, 0x0, 0x64 };
__root const CFG_HDR cfghdr22 = {CFG_COLOR, "״̬���ı���ɫ", 0, 0};
__root const char statfontcolor[4] = { 0xC9, 0x97, 0xD7, 0x64 };
__root const CFG_HDR cfghdr23 = {CFG_COLOR, "״̬������ɫ", 0, 0};
__root const char statbgcolor[4] = { 0x0, 0x0, 0x0, 0x40 };
__root const CFG_HDR cfghdr24 = {CFG_COLOR, "������ɫ", 0, 0};
__root const char scrollindcolor[4] = { 0xC9, 0x97, 0x76, 0x64 };
__root const CFG_HDR cfghdr25 = {CFG_COLOR, "���鱳��ɫ", 0, 0};
__root const char scrollbgcolor[4] = { 0x0, 0x0, 0x0, 0x64 };
__root const CFG_HDR cfghdr_m21 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr_m30 = {CFG_LEVEL, "��������", 1, 0};
__root const CFG_HDR cfghdr30 = {CFG_CHECKBOX, "��ʾ����", 0, 2};
__root const int scroll = 1;
__root const CFG_HDR cfghdr31 = {CFG_CHECKBOX, "��ʾ״̬��", 0, 2};
__root const int status = 1;
__root const CFG_HDR cfghdr32 = {CFG_CBOX, "������ǩ", 0, 3};
__root const int acbm = 1;
__root const CFG_CBOX_ITEM cfgcbox2[3] = {"Ĭ��", "һֱ", "������"};
__root const CFG_HDR cfghdr_m31 = {CFG_LEVEL, "", 0, 0};
/*
 __root const CFG_HDR cfghdr_m40 = {CFG_LEVEL, "Map file path", 1, 0};
 __root const CFG_HDR cfghdr40 = {CFG_STR_UTF8, "gb2uc.map", 0, 127};
 __root const char MAP0[128] = DEFAULT_DISK ":\\ZBin\\SieTxtView\\map\\gb2uc.map";
 __root const CFG_HDR cfghdr41 = {CFG_STR_UTF8, "uc2gb.map", 0, 127};
 __root const char MAP1[128] = DEFAULT_DISK ":\\ZBin\\SieTxtView\\map\\uc2gb.map";
 __root const CFG_HDR cfghdr_m41 = {CFG_LEVEL, "", 0, 0};

 */
