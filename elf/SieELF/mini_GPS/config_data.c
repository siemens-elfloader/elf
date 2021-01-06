#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_UINT,"x1",0,130};
__root const int cfgx=20;

__root const CFG_HDR cfghdr1={CFG_UINT,"y1",0,175};
__root const int cfgy=30;

__root const CFG_HDR cfghdr12={CFG_UINT,"x2",0,130};
__root const int cfgx2=112;

__root const CFG_HDR cfghdr13={CFG_UINT,"y2",0,175};
__root const int cfgy2=40;

__root const CFG_HDR cfghdr2={CFG_UINT,"color",0,24};
__root const int cfgcolor=7;

__root const CFG_HDR cfghdr3={CFG_UINT,"canvas color",0,24};
__root const int cfgcvcolor=23;

__root const CFG_HDR cfghdr4={CFG_UINT,"font",0,15};
__root const int cfgfont=7;

__root const CFG_HDR cfghdr5={CFG_CBOX,"string align",0,3};
__root const int cfgtext_attribute=1;
__root const CFG_CBOX_ITEM cfgcbox5[3]={"left","middle","right"};

__root const CFG_HDR cfghdr6={CFG_STR_UTF8,"gps dir",3,127};
__root const char gps_dir[128]="0:\\Misc\\gps";

__root const CFG_HDR cfghdr7={CFG_CBOX,"skip 2word",0,2};
__root const int skwd=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"no","yes"};

__root const CFG_HDR cfghdr8={CFG_CBOX,"write log",0,2};
__root const int wrlog=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"no","yes"};

__root const CFG_HDR cfghdr10={CFG_CBOX,"create new id",0,2};
__root const int wrnew=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"no","yes"};

__root const CFG_HDR cfghdr11={CFG_CBOX,"clear old log when start",0,2};
__root const int clrlog=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"no","yes"};

__root const CFG_HDR cfghdr9={CFG_UINT,"update time(sec)",0,300};
__root const int cfgupdate_time=5;
