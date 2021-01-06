#include "..\inc\cfg_items.h"
#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

/*
__root const CFG_HDR cfghdr0={CFG_INT,"׀אחלונ רנטפעא",0,99};
__root const int size_font=1;
*//*
__root const CFG_HDR cfghdr0={CFG_INT,"ײגוע רנטפעא",0,99};
__root const int pen_font=0;*/

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Path to sMenu",0,127};
__root const char smenu_path[128]=DEFAULT_DISK":\\zbin\\smenu\\data\\images\\";

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Shortcats file",0,127};
__root const char SHORTCUTS_FILE[128]="";
/*
__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Shortcats file",0,127};
__root const char ENTRYPOINTS_FILE[128]="";*/
