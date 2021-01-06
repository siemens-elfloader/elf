#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK_CFG "4"
#else
#define DEFAULT_DISK_CFG "0"
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"chan_ban DIR:",0,127};
__root const char chanbantab_dir[128]=DEFAULT_DISK_CFG":\\Zbin\\var\\";
