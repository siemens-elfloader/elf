#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#include "FesRemind.h"

__root const CFG_HDR cfghdr0 = {CFG_CBOX, "显示时机", 0, 3};
__root const int cfgShowIn = 1;
__root const CFG_CBOX_ITEM cfgcbox1_0[3] = {"锁键盘", "未锁键盘", "锁键盘+未锁键盘"};

// -------------------------------------------------------------------------- 
//显示自定义文本
__root const CFG_HDR cfghdr_mTSI11={CFG_LEVEL,"文本选项",1,0};
__root const CFG_HDR cfghdrTSI1_1={CFG_CHECKBOX, "屏显", 0, 2};
__root const int TEXT_ENA=1;

__root const CFG_HDR cfghdrTSI1_2={CFG_COORDINATES,"位置",0,0};
__root const unsigned int TEXT_X=20;
__root const unsigned int TEXT_Y=70;

__root const CFG_HDR cfghdrTSI1_7={CFG_CBOX,"对齐",0,3};
__root const unsigned int TEXT_XT=1;
__root const CFG_CBOX_ITEM cfgcboxTSI12[3]={AgainCN};

__root const CFG_HDR cfghdrTSI1_3={CFG_STR_GB,"文字",0,31};
__root const char TEXT_FMT[32]="中国移不动通信";

__root const CFG_HDR cfghdrTSI1_4={CFG_COLOR,"文字颜色",0,0};
__root const char TEXT_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrTSI1_5={CFG_COLOR,"边框颜色",0,0};
__root const char TEXT_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrTSI1_6={CFG_CBOX,"字体",0,17};
__root const unsigned int TEXT_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxTSI11[17]={FontSyCN};
__root const CFG_HDR cfghdr_mTSI10={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"星期",1,0};

__root const CFG_HDR cfghdr9_1 = {CFG_CHECKBOX, "显示", 0, 2};
__root const int WEEK_ENA = 1;

__root const CFG_HDR cfghdr9_2={CFG_COORDINATES,"位置坐标",0,0};
__root const unsigned int WEEK_X=40;
__root const unsigned int WEEK_Y=140;

__root const CFG_HDR cfghdrTSI5_7={CFG_CBOX,"对齐",0,3};
__root const unsigned int WEEK_XT=1;
__root const CFG_CBOX_ITEM cfgcboxTSI53[3]={AgainCN};

__root const CFG_HDR cfghdr9_3={CFG_COLOR,"文字颜色",0,0};
__root const char WEEK_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr9_6={CFG_COLOR,"边框颜色",0,0};
__root const char WEEK_FRINGING_COLORS[4]={0,0,0,100};

__root const CFG_HDR cfghdr9_4={CFG_CBOX,"字体",0,17};
__root const unsigned int WEEK_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxWeek[17]={FontSyCN};

__root const CFG_HDR cfghdr9_7={CFG_CBOX,"样式",0,2};
__root const int WEEK_STYLE = 1;
__root const CFG_CBOX_ITEM cfgcbox9_0[2] = {"MON", "星期一"};

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //
//显示农历年份
__root const CFG_HDR cfghdr_mTSI81={CFG_LEVEL,"农历年份",1,0};
__root const CFG_HDR cfghdrTSI8_1={CFG_CHECKBOX, "屏显", 0, 2};
__root const int CYEAR_ENA=1;

__root const CFG_HDR cfghdrTSI8_2={CFG_COORDINATES,"位置",0,0};
__root const unsigned int CYEAR_X=128;
__root const unsigned int CYEAR_Y=20;

__root const CFG_HDR cfghdrTSI8_7={CFG_CBOX,"对齐",0,3};
__root const unsigned int CYEAR_XT=2;
__root const CFG_CBOX_ITEM cfgcboxTSI82[3]={AgainCN};

__root const CFG_HDR cfghdrTSI8_3={CFG_COLOR,"文字颜色",0,0};
__root const char CYEAR_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrTSI8_4={CFG_COLOR,"边框颜色",0,0};
__root const char CYEAR_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrTSI8_5={CFG_CBOX,"字体",0,17};
__root const unsigned int CYEAR_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxTSI81[17]={FontSyCN};

__root const CFG_HDR cfghdr_mTSI80={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------
//显示农历日期
__root const CFG_HDR cfghdr_mTSI91={CFG_LEVEL,"农历日期",1,0};
__root const CFG_HDR cfghdrTSI9_1={CFG_CHECKBOX, "屏显", 0, 2};
__root const int CDATE_ENA=1;

__root const CFG_HDR cfghdrTSI9_2={CFG_COORDINATES,"位置",0,0};
__root const unsigned int CDATE_X=2;
__root const unsigned int CDATE_Y=20;

__root const CFG_HDR cfghdrTSI9_7={CFG_CBOX,"对齐",0,3};
__root const unsigned int CDATE_XT=0;
__root const CFG_CBOX_ITEM cfgcboxTSI92[3]={AgainCN};

__root const CFG_HDR cfghdrTSI9_3={CFG_COLOR,"文字颜色",0,0};
__root const char CDATE_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrTSI9_4={CFG_COLOR,"边框颜色",0,0};
__root const char CDATE_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrTSI9_5={CFG_CBOX,"字体",0,17};
__root const unsigned int CDATE_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxTSI91[17]={FontSyCN};

__root const CFG_HDR cfghdr_mTSI90={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_mFESTA1={CFG_LEVEL,"节日提醒",1,0};

__root const CFG_HDR cfghdrFESTA={CFG_CHECKBOX, "屏显", 0, 2};
__root const int BIR_ENA=1;

__root const CFG_HDR cfghdrBIRFILE={CFG_STR_UTF8,"数据文件",0,63};
__root const char BIRS_FILE[64]="0:\\ZBin\\etc\\day.txt";

__root const CFG_HDR cfghdrOBIR_1={CFG_COORDINATES,"位置",0,0};
__root const unsigned int OBIR_X=2;
__root const unsigned int OBIR_Y=36;

__root const CFG_HDR cfghdrOBIR_7={CFG_CBOX,"对齐",0,3};
__root const unsigned int OBIR_XT=0;
__root const CFG_CBOX_ITEM cfgcboxOBIR2[3]={AgainCN};

__root const CFG_HDR cfghdrOBIR_2={CFG_COLOR,"文字颜色",0,0};
__root const char OBIR_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrOBIR_3={CFG_COLOR,"边框颜色",0,0};
__root const char OBIR_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrOBIR_4={CFG_CBOX,"字体",0,17};
__root const unsigned int OBIR_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxOBIR1[17]={FontSyCN};

__root const CFG_HDR cfghdr_mFESTA0={CFG_LEVEL,"",0,0};

//--------------------------------------------------------------

__root const CFG_HDR cfghdr_mAPP1={CFG_LEVEL,"重要记事",1,0};

__root const CFG_HDR cfghdrAPP_5={CFG_UINT,"滚动速度",0,100};
__root const unsigned int SPEED = 10;

__root const CFG_HDR cfghdrAPP_1={CFG_COORDINATES,"位置",0,0};
__root const unsigned int APP_X=2;
__root const unsigned int APP_Y=122;

__root const CFG_HDR cfghdrAPP_2={CFG_COLOR,"文字颜色",0,0};
__root const char APP_CS[4]={255,255,255,100};

__root const CFG_HDR cfghdrAPP_3={CFG_COLOR,"边框颜色",0,0};
__root const char APP_CB[4]={0,0,0,100};

__root const CFG_HDR cfghdrAPP_4={CFG_CBOX,"字体",0,17};
__root const unsigned int APP_FONT=5;
__root const CFG_CBOX_ITEM cfgcboxAPP1[17]={FontSyCN};

__root const CFG_HDR cfghdr10={CFG_COLOR,"边框前景色",0,0};
__root const char frmmain_color[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr12={CFG_COLOR,"边框背景色", 0, 0};
__root const char frmbg_color[4]={255, 255, 255, 0};

__root const CFG_HDR cfghdr13={CFG_UINT,"X弯曲", 0, 512};
__root const unsigned int xrnd=2;

__root const CFG_HDR cfghdr14={CFG_UINT,"Y弯曲", 0, 512};
__root const unsigned int yrnd=2;

__root const CFG_HDR cfghdr15={CFG_CBOX,"边框样式", 0, 2};
__root const int fstyle=0;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"实线","虚线"};

__root const CFG_HDR cfghdr_mAPP0={CFG_LEVEL,"",0,0};
