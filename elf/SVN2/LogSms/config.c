#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Log file",0,127};
__root const char LOGFILE[128]=DEFAULT_DISK ":\\ZBin\\var\\Sms.log";
