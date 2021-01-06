#include "..\..\inc\cfg_items.h"

#ifdef NEWSGOLD
#ifdef S68
#define DEFAULT_DISK "0"
#else
#define DEFAULT_DISK "4"
#endif

#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Address",3,63};
__root const char cnfont[64]=DEFAULT_DISK":\\zbin\\utilities\\cnfont.dat";




