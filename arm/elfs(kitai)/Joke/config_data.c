#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef ELKA
#define scrw 239
#define scrh 319
#else
#define scrw 131
#define scrh 175
#endif

__root const CFG_HDR cfghdr0={CFG_STR_PASS,"Password",0,31};
__root const char realpass[32]="1111";

__root const CFG_HDR cfghdr1={CFG_UTF8_STRING,"TOP Warning String",0,127};
__root const char top_warning_str[128]="冰哥的手机你玩不懂~^_^";

__root const CFG_HDR cfghdr01= {CFG_RECT, "Top String Position", 0, 239};
__root const RECT top_str_pos={0,0,scrw,scrh/10};

__root const CFG_HDR cfghdr3={CFG_COLOR,"TOP Backround Color",0,0};
__root const char top_bg_color[4]={0,0,0,100};

__root const CFG_HDR cfghdr4={CFG_COLOR,"TOP String Color",0,0};
__root const char top_str_color[4]={0xFF,0,0,100};

__root const CFG_HDR cfghdr5={CFG_UINT,"Top String Font",0,16};
__root const unsigned int top_str_font=FONT_SMALL;

__root const CFG_HDR cfghdr6={CFG_UTF8_STRING,"GUI Warning String",0,127};
__root const char warning_str[128]="赶紧输入密码，手机要爆炸了！";

__root const CFG_HDR cfghdr7={CFG_COLOR,"GUI Backround Color",0,0};
__root const char gui_bg_color[4]={0,0,0,100};

__root const CFG_HDR cfghdr8={CFG_COLOR,"GUI Warning String Color",0,65535};
__root const char gui_warning_color[4]={0xFF,0,0,100};

__root const CFG_HDR cfghdr9={CFG_UINT,"GUI Warning String Font",0,16};
__root const unsigned int gui_warning_font=FONT_MEDIUM;

__root const CFG_HDR cfghdr10={CFG_COLOR,"Password Color",0,65535};
__root const char password_color[4]={0xFF,0xFF,0XFF,100};

__root const CFG_HDR cfghdr11={CFG_UINT,"Password Font",0,16};
__root const unsigned int password_font=FONT_SMALL;

__root const CFG_HDR cfghdr12={CFG_COLOR,"Softkey Color",0,65535};
__root const char sk_color[4]={0xFF,0xFF,0XFF,100};

__root const CFG_HDR cfghdr13={CFG_UINT,"Hot Key",0,100};
__root const unsigned int hot_key='#';

