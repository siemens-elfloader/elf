#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

//英文配置为config_data2.c


#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif 

__root const CFG_HDR cfghdr0={CFG_CBOX,"锁键盘运行",0,2};
__root const int ENA_LOCK=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"否","是"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"默认指令",0,3};
__root const int MODE=0;
__root const CFG_CBOX_ITEM cfgcbox2[3]={"休眠","关机","重启",};

__root const CFG_HDR cfghdr12={CFG_CBOX,"直接解锁",0,2};
__root const int DIRECT=1;
__root const CFG_CBOX_ITEM cfgcbox12[2]={"是","否"};

__root const CFG_HDR cfghdr_m1_1={CFG_LEVEL,"按键设置",1,0};

__root const CFG_HDR cfghdr1_1={CFG_UINT,"关闭按键",0,65535};
__root const unsigned int CLOSE_BTN=RIGHT_SOFT;

__root const CFG_HDR cfghdr1_2={CFG_UINT,"呼出按键",0,65535};
__root const unsigned int CALL_BTN=RED_BUTTON;

__root const CFG_HDR cfghdr1_3={CFG_CBOX,"按键形式",0,3};
__root const int MODE_KBD=0;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"按下","松开","长按"};

__root const CFG_HDR cfghdr1_4={CFG_UINT,"锁键盘时呼出按键",0,65535};
__root const unsigned int CALL_BTN2=RED_BUTTON;

__root const CFG_HDR cfghdr1_5={CFG_CBOX,"锁键盘时按键形式",0,3};
__root const int MODE_KBD2=0;
__root const CFG_CBOX_ITEM cfgcbox5[3]={"按下","松开","长按"};

__root const CFG_HDR cfghdr_m1_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m2_1={CFG_LEVEL,"图标设置",1,0};

__root const CFG_HDR cfghdr2_0={CFG_STR_UTF8,"关闭图标",0,127};
__root const char ICONS_SD[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\off.png";

__root const CFG_HDR cfghdr2_1={CFG_STR_UTF8,"重启图标",0,127};
__root const char ICONS_RB[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\reboot.png";

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"休眠图标",0,127};
__root const char ICONS_SR[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\sleep.png";

__root const CFG_HDR cfghdr2_3={CFG_STR_UTF8,"解锁图标",0,127};
__root const char ICONS_UL[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\unlock.png";

__root const CFG_HDR cfghdr_m2_0={CFG_LEVEL,"",0,0};

