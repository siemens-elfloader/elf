#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"show title",0,2};
__root const int show = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr0asd0={CFG_CBOX,"Do not allow >1 copies of macros",0,2};
__root const int use_mutex_byte = 0;
__root const CFG_CBOX_ITEM cfgcbox2sdf[2]={"No","Yes"};


__root const CFG_HDR cfghdr00={CFG_CBOX,"break by any key",0,2};
__root const int bak = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};

__root const CFG_HDR cfghdr0000={CFG_UINT,"break key code",0,65530};
__root const int breakeycode=RED_BUTTON;


__root const CFG_HDR cfghdr000={CFG_UINT,"watch_delay",5,65530};
__root const int watch_delay=50;

__root const CFG_HDR cfghdr1={CFG_UINT,"paint_delay",5,65530};
__root const int paint_delay=100;

__root const CFG_HDR cfghdr2={CFG_UINT,"pre_delay",5,65530};
__root const int pre_delay=400;

__root const CFG_HDR cfghdr3={CFG_UINT,"delay_longpause(P)",5,65530};
__root const int delay_longpause=1000;

__root const CFG_HDR cfghdr4={CFG_UINT,"delay_smallpause( )",5,65530};
__root const int delay_smallpause=241;

__root const CFG_HDR cfghdr5={CFG_UINT,"delay_keybreak",0,65530};
__root const int delay_keybreak=85;

__root const CFG_HDR cfghdr6={CFG_UINT,"delay_wait_1",5,65530};
__root const int delay_wait_1=60;

__root const CFG_HDR cfghdr7={CFG_UINT,"delay_wait_2",5,65530};
__root const int delay_wait_2=121;

__root const CFG_HDR cfghdr8={CFG_UINT,"delay_wait_3",5,65530};
__root const int delay_wait_3=60;

__root const CFG_HDR cfghdr9={CFG_UINT,"CPU wait threshold,%",5,100};
__root const int wait_threshold=85;

__root const CFG_HDR cfghdrA={CFG_STR_WIN1251,"ShowNativeMenu() address",1,8};
//__root const char ShowNativeMenu_[9]="A08DF43B";
__root const char ShowNativeMenu_[9]="0";

