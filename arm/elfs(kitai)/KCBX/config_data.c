#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//==============
__root const CFG_HDR cfghdr31 = {CFG_DATE,"开始年份:",0,0};
__root const TDate ymd={2009,2,8};
//==============
__root const CFG_HDR cfghdr_m1_1={CFG_LEVEL,"文本颜色",1,0};

__root const CFG_HDR cfghdr10={CFG_COLOR,"标题字色",0,0};
__root const char FNT_COLOR[4]={0,0,0,100};

__root const CFG_HDR cfghdr12={CFG_COLOR,"周次字色",0,0};
__root const char FNW_COLOR[4]={0,0,255,100};;

__root const CFG_HDR cfghdr14={CFG_COLOR,"时间字色",0,0};
__root const char FNM_COLOR[4]={0,0,0,100};

__root const CFG_HDR cfghdr15={CFG_COLOR,"课程字色",0,0};  //
__root const char FNC_COLOR[4]={0,0,0,100};

__root const CFG_HDR cfghdr16={CFG_COLOR,"今天字色",0,0};
__root const char FND_COLOR[4]={255,0,0,100};

__root const CFG_HDR cfghdr_m1_2={CFG_LEVEL,"",0,0};
//==============
__root const CFG_HDR cfghdr_m2_1={CFG_LEVEL,"背景参数",1,0};

__root const CFG_HDR cfghdr21={CFG_COLOR,"界面底色",0,0};
__root const char BGA_COLOR[4]={255,255,255,100};

__root const CFG_HDR cfghdr18={CFG_COLOR,"线条颜色",0,0};
__root const char FNL_COLOR[4]={0,0,255,100};

__root const CFG_HDR cfghdr20={CFG_COLOR,"选中底色",0,0}; //
__root const char BGC_COLOR[4]={255,96,0,100};

__root const CFG_HDR cfghdr22={CFG_COLOR,"周次底色",0,0};
__root const char BGW_COLOR[4]={255,208,255,100};

__root const CFG_HDR cfghdr23={CFG_COLOR,"时间底色",0,0};
__root const char BGT_COLOR[4]={104,255,104,100};

__root const CFG_HDR cfghdr24={CFG_COLOR,"上午底色",0,0};
__root const char BGM_COLOR[4]={255,255,100,32};

__root const CFG_HDR cfghdr25={CFG_COLOR,"下午底色",0,0};
__root const char BGP_COLOR[4]={255,255,100,64};

__root const CFG_HDR cfghdr26={CFG_COLOR,"晚上底色",0,0};
__root const char BGN_COLOR[4]={255,255,100,100};

__root const CFG_HDR cfghdr_m2_2={CFG_LEVEL,"",0,0};
//===============
__root const CFG_HDR cfghdr103={CFG_STR_UTF8,"数据文件",3,63};
__root const char cData[64]="4:\\ZBin\\KCB\\KCB.TXT";
