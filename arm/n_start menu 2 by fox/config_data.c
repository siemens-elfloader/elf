#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0 = {CFG_STR_WIN1251, "menu file path", 0, 127};
__root const char path[128] = "0:\\Zbin\\fox_menu\\";

