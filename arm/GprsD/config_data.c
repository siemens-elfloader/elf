#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"Enable GprsD",0,2};
__root const int ENA_GPRSD = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr6={CFG_STR_WIN1251,"NAP internal name (as in wbxml)",0,39};
__root const char cfgINTNAME[40]="NAP2";

__root const CFG_HDR cfghdr5={CFG_STR_WIN1251,"NAP name (as in phone)",0,19};
__root const char cfgNAME[20]="Life:)";

__root const CFG_HDR cfghdr1={CFG_STR_WIN1251,"APN",0,29};
//__root const char cfgAPN[20]="internet.mts.ru";
__root const char cfgAPN[30]="internet";

__root const CFG_HDR cfghdr2={CFG_STR_WIN1251,"Username",0,19};
//__root const char cfgUSER[20]="mts";
__root const char cfgUSER[20]="";

__root const CFG_HDR cfghdr3={CFG_STR_WIN1251,"Password",0,19};
//__root const char cfgPASS[20]="mts";
__root const char cfgPASS[20]="";

__root const CFG_HDR cfghdr4={CFG_UINT,"Net timeout",0,0xFFFFFFFF};
__root const unsigned int cfgTimeout=0x5F5E0FF; // 99999999 секунд =)

__root const CFG_HDR cfghdr7={CFG_STR_WIN1251,"DNS",0,19};
__root const char cfgDNS[20]="8.8.8.8";
