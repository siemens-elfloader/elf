#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_UINT,"Town ID(weatherd)",0,0xFFFFFFFF};
__root const unsigned int TID=33929;

__root const CFG_HDR cfghdr1 = {CFG_STR_WIN1251, "city name", 0, 63};
__root const char city_name[64] = "My_City";

__root const CFG_HDR cfghdr3={CFG_UINT,"run key(long press)",0,65535};
__root const unsigned int CALL_BUTTON=1;

__root const CFG_HDR cfghdr9={CFG_UINT,"missed event key(short press)",0,65535};
__root const unsigned int CALL_BUTTON2=13;

__root const CFG_HDR cfghdr4_4={CFG_CBOX,"use naticq plugin",0,2};
__root const int use_plugin = 0;
__root const CFG_CBOX_ITEM cfgcbox4_4[2]={"No","Yes"};

__root const CFG_HDR cfghdr7 = {CFG_STR_WIN1251, "link1 name", 0, 63};
__root const char link1_name[64] = "Naticq";

__root const CFG_HDR cfghdr2 = {CFG_STR_WIN1251, "link1 path", 0, 63};
__root const char link1[64] = "4:\\zbin\\naticq\\naticq.elf";

__root const CFG_HDR cfghdr8 = {CFG_STR_WIN1251, "link2 name", 0, 63};
__root const char link2_name[64] = "Ballet";

__root const CFG_HDR cfghdr4 = {CFG_STR_WIN1251, "link2 path", 0, 63};
__root const char link2[64] = "4:\\Zbin\\balletmini\\BalletMini.elf";

__root const CFG_HDR cfghdr5 = {CFG_STR_WIN1251, "link3 name", 0, 63};
__root const char link3_name[64] = "SieJC";

__root const CFG_HDR cfghdr6 = {CFG_STR_WIN1251, "link3 path", 0, 63};
__root const char link3[64] = "4:\\Zbin\\siejc\\siejc.elf";

