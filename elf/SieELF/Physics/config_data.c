#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#include "code.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Address",3,63};
__root const char cnfont[64]=DEFAULT_DISK":\\zbin\\utilities\\cnfont.dat";



