#ifndef _CONFLOADER_H_
#define _CONFLOADER_H_
extern const int charset;
extern const int font; //字体
extern const int statfont; //字体
extern const int rowsplit;
extern const int colsplit; //行/列间距
extern const char fontcolor[]; //字体颜色
extern const char bgcolor[]; //背景颜色
extern const char statfontcolor[];
extern const char statbgcolor[];
extern const char scrollindcolor[];
extern const char scrollbgcolor[];
extern const int scroll;
extern const int status;
extern const int acbm;
extern const unsigned int maxhis;
void InitConfig();

#endif
