#include "cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_UINT,"x",0,130};
__root const int cfgx=5;

__root const CFG_HDR cfghdr1={CFG_UINT,"y",0,175};
__root const int cfgy=70;

__root const CFG_HDR cfghdr2={CFG_UINT,"color",0,24};
__root const int cfgcolor=0;

__root const CFG_HDR cfghdr3={CFG_UINT,"canvas color",0,24};
__root const int cfgcvcolor=23;

__root const CFG_HDR cfghdr4={CFG_UINT,"font",0,15};
__root const int cfgfont=7;

__root const CFG_HDR cfghdr5={CFG_UINT,"text attribute",0,512};
__root const int cfgtext_attribute=32;

__root const CFG_HDR cfghdr6={CFG_STR_UTF8,"gps dir",3,127};
__root const char gps_dir[128]="0:\\Misc\\gps";

__root const CFG_HDR cfghdr8={CFG_CBOX,"write log",0,2};
__root const int wrlog=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"no","yes"};

__root const CFG_HDR cfghdr12={CFG_CBOX,"locations in log",0,2};
__root const int wrloclog=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"no","yes"};

__root const CFG_HDR cfghdr9={CFG_UINT,"update time(sec)",0,300};
__root const int cfgupdate_time=5;

__root const CFG_HDR cfghdr14={CFG_UINT,"redraw time(sec)",0,300};
__root const int cfgupdate_screen=1;

