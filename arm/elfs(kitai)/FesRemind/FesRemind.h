#ifndef _FESREMIND_H_
  #define _FESREMIND_H_

#define TMR_SECOND 216
#define AgainCN "左对齐", "居中", "右对齐"
#define FontSyCN "大号字体","大号加粗","大号斜体","大号粗斜","中号字体","中号加粗","中号倾斜","中号粗斜","小号字体","小号加粗","小号斜体","小号粗斜","小号数体","小号数粗","最小数体","大号数体","中号数体"
#define IPC_UPDATE_STAT 1
#define IPC_FESREMIND_NAME "FesRemind"
//显示文本
 extern const int  TEXT_ENA;
 extern const unsigned int TEXT_XT;
 extern const unsigned int TEXT_X;
 extern const unsigned int TEXT_Y;
 extern const char TEXT_CS[];
 extern const char TEXT_CB[];
 extern const unsigned int TEXT_FONT;
 extern const char TEXT_FMT[];
//星期
extern const int WEEK_ENA;
 extern const unsigned int WEEK_XT;
extern const unsigned int WEEK_X;
extern const unsigned int WEEK_Y;
extern const char WEEK_COLORS[];
extern const unsigned int WEEK_FONT;
extern const char WEEK_FRINGING_COLORS[];
extern const int WEEK_STYLE;
//显示农历年
 extern const int  CYEAR_ENA;
 extern const unsigned int CYEAR_XT;
 extern const unsigned int CYEAR_X;
 extern const unsigned int CYEAR_Y;
 extern const char CYEAR_CS[];
 extern const char CYEAR_CB[];
 extern const unsigned int CYEAR_FONT;
//显示农历月日
 extern const int  CDATE_ENA;
 extern const unsigned int CDATE_XT;
 extern const unsigned int CDATE_X;
 extern const unsigned int CDATE_Y;
 extern const char CDATE_CS[];
 extern const char CDATE_CB[];
 extern const unsigned int CDATE_FONT;

 extern const int  BIR_ENA;
 extern const unsigned int OBIR_XT;
 extern const unsigned int OBIR_X;
 extern const unsigned int OBIR_Y;
 extern const char OBIR_CS[];
 extern const char OBIR_CB[];
 extern const unsigned int OBIR_FONT;
//定义重要记事
 extern const unsigned int SPEED;
 extern const unsigned int APP_X;
 extern const unsigned int APP_Y;
 extern const char APP_CS[];
 extern const char APP_CB[];
 extern const unsigned int APP_FONT;
 extern const char frmmain_color[4];
 extern const char frmbg_color[4];
 extern const unsigned int xrnd;
 extern const unsigned int yrnd;
 extern const int fstyle;
 
extern const int cfgShowIn;
extern const char BIRS_FILE[];
#endif
