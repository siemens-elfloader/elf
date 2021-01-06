#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"CSM list file",3,127};
#ifdef NEWSGOLD
__root const char csmlist_fname[128]="4:\\ZBin\\etc\\CSMlist.txt";
#else 
__root const char csmlist_fname[128]="0:\\ZBin\\etc\\CSMlist.txt";
#endif

__root const CFG_HDR cfghdr1={CFG_COORDINATES,"CSM position",0,0};
__root const unsigned int CSM_X=10;
__root const unsigned int CSM_Y=54;

__root const CFG_HDR cfghdr2={CFG_COLOR,"CSM color",0,0};
__root const char CSM_COLORS[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr3={CFG_COLOR,"CSM frame color",0,0};
__root const char CSM_FRAME_COLORS[4]={0xFF,0xFF,0xFF,0x0};

__root const CFG_HDR cfghdr4={CFG_UINT,"CSM font",0,65535};
__root const unsigned int CSM_FONT=8;

__root const CFG_HDR cfghdr5={CFG_CBOX,"Show NewStyleDaemons",0,2};
__root const int SHOW_DAEMONS=1;
__root const CFG_CBOX_ITEM cfgcbox33[2]={"No","Yes"};

__root const CFG_HDR cfghdr6={CFG_UTF8_STRING,"Beginning String",0,15};
__root const char begin_str[16]="%d) ";

