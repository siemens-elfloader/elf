#ifdef ICONBAR
#include "..\inc\cfg_items.h"
#include "lang.h"
//Конфигурация иконок в иконбар
__root const CFG_HDR cfghdr_IBI={CFG_CHECKBOX, LG_ICONBAR_SI, 0, 2};
__root const int SHOW_ICONBAR_ICON = 1;

__root const CFG_HDR cfghdr_IBI1={CFG_UINT,"Online icon",0,10000};
__root const unsigned int IB_ONLINE=2200;

__root const CFG_HDR cfghdr_IBI2={CFG_UINT,"Chat icon",0,10000};
__root const unsigned int IB_CHAT=2201;

__root const CFG_HDR cfghdr_IBI3={CFG_UINT,"Away icon",0,10000};
__root const unsigned int IB_AWAY=2202;

__root const CFG_HDR cfghdr_IBI4={CFG_UINT,"Xa icon",0,10000};
__root const unsigned int IB_XA=2203;

__root const CFG_HDR cfghdr_IBI5={CFG_UINT,"Dnd icon",0,10000};
__root const unsigned int IB_DND=2204;

__root const CFG_HDR cfghdr_IBI6={CFG_UINT,"Invisible icon",0,10000};
__root const unsigned int IB_INVISIBLE=2205;

__root const CFG_HDR cfghdr_IBI7={CFG_UINT,"Offline icon",0,10000};
__root const unsigned int IB_OFFLINE=2206;

__root const CFG_HDR cfghdr_IBI8={CFG_UINT,"Message icon",0,10000};
__root const unsigned int IB_NEWMESSAGE=2207;
#endif
// EOL, EOF
