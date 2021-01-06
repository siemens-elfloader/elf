#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"Picture Quality",0,4};
__root const int PIC_QUALITY=2;
__root const CFG_CBOX_ITEM cfgcbox0[]={"None","Text","Low","High"};

__root const CFG_HDR cfghdr1={CFG_UINT,"History depth",0,128};
__root const int HISTORY_DEPTH=20;

__root const CFG_HDR cfghdr2={CFG_UINT,"Java Heap value(kb)",0,16384};
#ifdef NEWSGOLD
#ifdef ELKA
__root const int JAVA_HEAP_SIZE=3072;
#else
__root const int JAVA_HEAP_SIZE=3072;
#endif
#else
__root const int JAVA_HEAP_SIZE=768;
#endif

__root const CFG_HDR cfghdr3={CFG_LEVEL,"Server",1,0};

__root const CFG_HDR cfghdr3_1={CFG_STR_WIN1251,"Host",0,31};
__root const char OM_POST_HOST[32]="80.232.117.10";

__root const CFG_HDR cfghdr3_2={CFG_UINT,"Port",0,65535};
__root const unsigned int OM_POST_PORT=80;

__root const CFG_HDR cfghdr3_end={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"Default launch parameter",0,127};
__root const char DEFAULT_PARAM[128]="bookmarks";
