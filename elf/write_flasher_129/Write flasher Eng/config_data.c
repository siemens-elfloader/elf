#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"Enable hello message",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr1 = {CFG_UINT, "Refresh rate (1/10 sec):", 0, 50};
__root const unsigned int cfgUpTime=1;

__root const CFG_HDR cfghdr2={CFG_UINT,"Frequency:",0,1048};
__root const unsigned int delay=10;

__root const CFG_HDR cfghdr3={CFG_LEVEL,"UnLock mode",1,0};

__root const CFG_HDR cfghdr5_1={CFG_CBOX,"Display",0,2};
__root const int dis=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Off","On"};

__root const CFG_HDR cfghdr5_2={CFG_CBOX,"Keyboard",0,2};
__root const int key=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Off","On"};

__root const CFG_HDR cfghdr5_3={CFG_CBOX,"Lighter",0,2};
__root const int lig=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Off","On"};

__root const CFG_HDR cfghdr5_4={CFG_CBOX,"Dynamic light",0,2};
__root const int dyn=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"Off","On"};

__root const CFG_HDR cfghdr5_5={CFG_UINT,"Brightness:",0,100};
__root const unsigned int light=100;

__root const CFG_HDR cfghdr4={CFG_LEVEL,"",0,0};
//----------------------------------------------

__root const CFG_HDR cfghdr6={CFG_LEVEL,"Lock mode",1,0};

__root const CFG_HDR cfghdr8_1={CFG_CBOX,"Display",0,2};
__root const int lockdis=1;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"Off","On"};

__root const CFG_HDR cfghdr8_2={CFG_CBOX,"Keyboard",0,2};
__root const int lockkey=1;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"Off","On"};

__root const CFG_HDR cfghdr8_3={CFG_CBOX,"Lighter",0,2};
__root const int locklig=1;
__root const CFG_CBOX_ITEM cfgcbox7[2]={"Off","On"};

__root const CFG_HDR cfghdr8_4={CFG_CBOX,"Dynamic light",0,2};
__root const int lockdyn=1;
__root const CFG_CBOX_ITEM cfgcbox8[2]={"Off","On"};

__root const CFG_HDR cfghdr8_5={CFG_UINT,"Brightness:",0,100};
__root const unsigned int locklight=100;

__root const CFG_HDR cfghdr7={CFG_LEVEL,"",0,0};
//----------------------------------------------

__root const CFG_HDR cfghdr9={CFG_CBOX,"Disable keypad light patch",0,2};
__root const int key_patch=0;
__root const CFG_CBOX_ITEM cfgcbox9[2]={"Not installed","Installed"};





