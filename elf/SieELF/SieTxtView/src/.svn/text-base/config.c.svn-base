#include "..\..\inc\cfg_items.h"
#include "..\..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0 = {CFG_CBOX,"字符编码", 0, 5};
__root const int charset = 0;
__root const CFG_CBOX_ITEM cfgcbox1[5] = {"自动", "ANSI", "UNICODE LE", "UNICDOE BE", "UTF8"};

__root const CFG_HDR cfghdr1 = {CFG_UINT, "历史最大条数", 0, 999};
__root const unsigned int maxhis = 20;

__root const CFG_HDR cfghdr_m10 = {CFG_LEVEL, "字体设置", 1, 0};

__root const CFG_HDR cfghdr10 = {CFG_INT, "行间距", 0, 50};
__root const int rowsplit = 2;

__root const CFG_HDR cfghdr11 = {CFG_INT, "列间距", 0, 50};
__root const int colsplit = 2;

__root const CFG_HDR cfghdr12 = {CFG_INT, "字体", 0, 12};
__root const int font = FONT_SMALL;

__root const CFG_HDR cfghdr13 = {CFG_INT, "状态栏字体", 0, 12};
__root const int statfont = FONT_SMALL;

__root const CFG_HDR cfghdr_m11 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr_m20 = {CFG_LEVEL, "颜色设置", 1, 0};
__root const CFG_HDR cfghdr20 = {CFG_COLOR, "文本颜色", 0, 0};
__root const char fontcolor[4] = { 0xFF, 0xFF, 0xFF, 0x64 };
__root const CFG_HDR cfghdr21 = {CFG_COLOR, "背景颜色", 0, 0};
__root const char bgcolor[4] = { 0x0, 0x0, 0x0, 0x64 };
__root const CFG_HDR cfghdr22 = {CFG_COLOR, "状态栏文本颜色", 0, 0};
__root const char statfontcolor[4] = { 0xC9, 0x97, 0xD7, 0x64 };
__root const CFG_HDR cfghdr23 = {CFG_COLOR, "状态栏背景色", 0, 0};
__root const char statbgcolor[4] = { 0x0, 0x0, 0x0, 0x40 };
__root const CFG_HDR cfghdr24 = {CFG_COLOR, "滑块颜色", 0, 0};
__root const char scrollindcolor[4] = { 0xC9, 0x97, 0x76, 0x64 };
__root const CFG_HDR cfghdr25 = {CFG_COLOR, "滑块背景色", 0, 0};
__root const char scrollbgcolor[4] = { 0x0, 0x0, 0x0, 0x64 };
__root const CFG_HDR cfghdr_m21 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr_m30 = {CFG_LEVEL, "控制设置", 1, 0};
__root const CFG_HDR cfghdr30 = {CFG_CHECKBOX, "显示滑块", 0, 2};
__root const int scroll = 1;
__root const CFG_HDR cfghdr31 = {CFG_CHECKBOX, "显示状态栏", 0, 2};
__root const int status = 1;
__root const CFG_HDR cfghdr32 = {CFG_CBOX, "创建书签", 0, 3};
__root const int acbm = 1;
__root const CFG_CBOX_ITEM cfgcbox2[3] = {"默认", "一直", "从来不"};
__root const CFG_HDR cfghdr_m31 = {CFG_LEVEL, "", 0, 0};
/*
 __root const CFG_HDR cfghdr_m40 = {CFG_LEVEL, "Map file path", 1, 0};
 __root const CFG_HDR cfghdr40 = {CFG_STR_UTF8, "gb2uc.map", 0, 127};
 __root const char MAP0[128] = DEFAULT_DISK ":\\ZBin\\SieTxtView\\map\\gb2uc.map";
 __root const CFG_HDR cfghdr41 = {CFG_STR_UTF8, "uc2gb.map", 0, 127};
 __root const char MAP1[128] = DEFAULT_DISK ":\\ZBin\\SieTxtView\\map\\uc2gb.map";
 __root const CFG_HDR cfghdr_m41 = {CFG_LEVEL, "", 0, 0};

 */
