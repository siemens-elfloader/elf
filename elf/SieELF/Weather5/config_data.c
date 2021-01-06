#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_UINT,"Town ID",0,0xFFFFFFFF};
__root const unsigned int TID=0;

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Icon path",0,127};
__root const char ICON_PATH[128]="0:\\ZBin\\Weather\\img\\";

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Towns list path",0,127};
__root const char TOWNS_PATH[128]="0:\\ZBin\\Weather\\towns.txt";

__root const CFG_HDR cfghdr3={CFG_UINT,"Font size date string",0,100};
__root const unsigned int FONT_SIZE_DATE=2;

__root const CFG_HDR cfghdr4={CFG_UINT,"Font color date string",0,100};
__root const unsigned int FONT_DATE_COLOR=3;

__root const CFG_HDR cfghdr5={CFG_UINT,"Font size data",0,100};
__root const unsigned int FONT_SIZE_DATA=1;

__root const CFG_HDR cfghdr6={CFG_UINT,"Font color data",0,100};
__root const unsigned int FONT_DATA_COLOR=1;
