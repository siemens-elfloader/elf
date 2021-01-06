//  ŒÕ‘»√!!!
#include "..\inc\cfg_items.h"
//#include "include.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif


__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8, "path to graphics", 0, 127};
__root const char IMG_PATH[128] = "0:\\ZBin\\pandemonium\\img\\";

__root const CFG_HDR cfghdr1={CFG_CBOX,"offer reboot",0,2};
__root const int ASK_FOR_REBOOT = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};
