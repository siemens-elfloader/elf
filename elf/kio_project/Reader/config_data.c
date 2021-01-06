#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_UINT,"Background colour",0,23};
__root const unsigned int col_bg=1;
__root const CFG_HDR cfghdr1={CFG_UINT,"Text colour.",0,23};
__root const unsigned int col_tx=0;
__root const CFG_HDR cfghdr2={CFG_UINT,"Vertical space",0,15};
__root const unsigned int v_s=1;
__root const CFG_HDR cfghdr3={CFG_CBOX,"Warping",0,3};
__root const int words=2;
__root const CFG_CBOX_ITEM cfgcbox0[3]={"No","Word","Itellectual"};
__root const CFG_HDR cfghdr4={CFG_CBOX,"Remove empty lines",0,2};
__root const int rem_rcr=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};
__root const CFG_HDR cfghdr5={CFG_CBOX,"Width align",0,2};
__root const unsigned int width=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};
__root const CFG_HDR cfghdr6={CFG_CBOX,"Paragraph indent",0,2};
__root const unsigned int parag=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"No","Yes"};
__root const CFG_HDR cfghdr7={CFG_CBOX,"Paragraph reformat",0,2};
__root const int rem_cr=0;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"No","Yes"};
__root const CFG_HDR cfghdr8={CFG_CBOX,"Status",0,3};
__root const unsigned int status=1;
__root const CFG_CBOX_ITEM cfgcbox9[3]={"No","Top","Buttom"};
__root const CFG_HDR cfghdr9={CFG_UINT,"Max space length",0,25};
__root const unsigned int space_lim=15;
