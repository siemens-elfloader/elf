#include "cfg_items.h"


 __root const CFG_HDR cfghdr0={CFG_STR_UTF8,"output path",0,127};
 __root const char CFG_OUTPUT_PATH[128]="4:\\Zbin\\Shots\\";

__root const CFG_HDR cfghdr_5={CFG_UINT,"global hotkey",0,100};
__root const int CFG_HOTKEY = 11;
 
__root const CFG_HDR cfghdr10={CFG_CBOX,"output format",0,2};
__root const int CFG_OUTPUT_FORMAT = 0;
__root const CFG_CBOX_ITEM cfgcbox10[2]={"jpg","png"};

__root const CFG_HDR cfghdr_40={CFG_UINT,"jpeglib quality level",0,100};
__root const int CFG_JPEG_CLEVEL = 80;

__root const CFG_HDR cfghdr60={CFG_CBOX,"shot message",0,2};
__root const int CFG_ENABLE_MSG = 1;
__root const CFG_CBOX_ITEM cfgcbox60[2]={"disable","enable"};
