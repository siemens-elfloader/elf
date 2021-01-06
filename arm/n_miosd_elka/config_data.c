#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_UINT,"Town ID(weatherd)",0,0xFFFFFFFF};
__root const unsigned int TID=26314;

__root const CFG_HDR cfghdr1 = {CFG_STR_WIN1251, "city name", 0, 63};
__root const char city_name[64] = "my_city";

__root const CFG_HDR cfghdr2={CFG_UINT,"run key(long press)",0,65535};
__root const unsigned int CALL_BUTTON=1;

__root const CFG_HDR cfghdr4 = {CFG_STR_WIN1251, "miosd2 file path", 0, 127};
__root const char path[128] = "4:\\Zbin\\miosd2\\";

__root const CFG_HDR cfghdr57 = {CFG_COLOR, "title color", 0, 0};
__root const char title[4]={255,0,0,100};

__root const CFG_HDR cfghdr58 = {CFG_COLOR, "info color", 0, 0};
__root const char info[4]={240,180,0,100};

