#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8,"Function list file", 0, 127};
__root const char FUNC_FILE_NAME[128] = DEFAULT_DISK ":\\ZBin\\etc\\DialExt.txt";

__root const CFG_HDR cfghdr1 = {CFG_STR_UTF8,"Refresh set", 0, 10};
__root const char REFRESH[11] = "*#90#";

__root const CFG_HDR cfghdr2 = {CFG_STR_UTF8,"Quit application", 0, 10};
__root const char QUIT[11] = "*#91#";

__root const CFG_HDR cfghdr3 = {CFG_STR_UTF8,"Reboot phone", 0, 10};
__root const char REBOOT[11] = "*#98#";

__root const CFG_HDR cfghdr4 = {CFG_STR_UTF8,"Switch phone off", 0, 10};
__root const char SHUTOFF[11] = "*#99#";

__root const CFG_HDR cfghdr5 = {CFG_CBOX,"Show welcome message", 0, 2};
__root const int START_FLAG = 1;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"no", "yes"};
