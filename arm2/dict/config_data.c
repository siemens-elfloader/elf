/*
* Ping-Pong 2009 - 2010
* keys
* (c) Danil_e71
*/

#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"


__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"File Output",1,127};
__root const char amr[128]="0:\\rec.amr";

__root const CFG_HDR cfghdr3={CFG_UINT,"Макс. hазмер(кб)",1,1014*1024};
__root const unsigned int size=1024*7;

__root const CFG_HDR cfghdr4={CFG_UINT,"UID",0,0xFFFF};
__root const unsigned int buid=0x00;
