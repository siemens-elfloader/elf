#include "..\inc\cfg_items.h"


__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Dir of \"paste.tmo\"",3,127};
__root const char root_dir[128]="0:\\Misc";

__root const CFG_HDR cfghdr1={CFG_COORDINATES,"Upper-Left Position",0,0};
__root const unsigned int cfgx=10;
__root const unsigned int cfgy=114;

__root const CFG_HDR cfghdr2={CFG_COORDINATES,"Lower-Right Position",0,0};
__root const unsigned int cfgx2=122;
__root const unsigned int cfgy2=146;

__root const CFG_HDR cfghdr3={CFG_UINT,"Font",0,15};
__root const unsigned int cfgfont=3;

__root const CFG_HDR cfghdr4={CFG_UINT,"Color",0,24};
__root const int unsigned cfgcolor=0;

__root const CFG_HDR cfghdr5={CFG_UINT,"Border Color",0,24};
__root const int unsigned cfgbordercolor=9;

__root const CFG_HDR cfghdr6={CFG_CBOX,"Text align",0,3};
__root const unsigned int cfgalign=1;
__root const CFG_CBOX_ITEM cfgcbox0[3]={"left", "middle", "right"};

/*
__root const CFG_HDR cfghdr5={CFG_CBOX,"Font Size",0,3};
__root const unsigned int cfgfontsize=1;
__root const CFG_CBOX_ITEM cfgcbox1[3]={"big","medium","small"};

__root const CFG_HDR cfghdr6={CFG_CBOX,"Bold Font For English",0,2};
__root const unsigned int cfgfontbold=0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"no","yes"};
*/

__root const CFG_HDR cfghdr7={CFG_UINT,"Refresh time, 1/10 sec",0,600};
__root const unsigned int REFRESH=20;


__root const CFG_HDR cfghdr8={CFG_CBOX,"Enable FreePaste",0,2};
__root const unsigned int cfgenable=1;
__root const CFG_CBOX_ITEM cfgcbox1[3]={"disable", "enable"};


