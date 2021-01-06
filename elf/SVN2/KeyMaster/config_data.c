#include "..\inc\cfg_items.h"
//Конфигурация

__root const CFG_HDR cfghdr0={CFG_CBOX,"Enable if keyboard locked",0,2};
__root const int ENA_LOCK=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Messages",1,0};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Enable hello message",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr2={CFG_CBOX,"Enable Key2Joy message message",0,2};
__root const int ENA_K2J_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Media Control",1,0};
#ifndef NEWSGOLD
__root const CFG_HDR cfghdr3={CFG_CBOX,"Enable MediaControl",0,2};
__root const int ENA_MEDIAC=0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"No","Yes"};

__root const CFG_HDR cfghdr4={CFG_CBOX,"Start player on HandsFree button",0,3};
__root const int ENA_PLAYER=1;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"No","Yes,Elf player","Yes,Default player"};
#else 
__root const CFG_HDR cfghdr4={CFG_CBOX,"Start player on HandsFree button",0,2};
__root const int ENA_PLAYER=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"No","Yes,Elf player"};
#endif

__root const CFG_HDR cfghdr5={CFG_STR_UTF8,"Path to Elf player",3,127};
__root const char player_path[128]="0:\\ZBin\\SPlayer\\SPlayer.elf";

__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"Playlist for Elf player",3,127};
__root const char playlist_path[128]="";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Key2Joy",1,0};

__root const CFG_HDR cfghdr6={CFG_CBOX,"Enable  Key2Joy",0,4};
__root const int ENA_KEY2JOY=2;
__root const CFG_CBOX_ITEM cfgcbox6[4]={"No","Yes","With soft keys on 7,9","With soft keys on 1,3"};

__root const CFG_HDR cfghdr7={CFG_UINT,"Key2Joy key",0,99};
__root const int Key2Joy_KEY=11;

__root const CFG_HDR cfghdr8={CFG_CBOX,"Activation on",0,2};
__root const int Key2Joy_KEY_LONG_PRESS=1;
__root const CFG_CBOX_ITEM cfgcbox8[2]={"ShortPress","LongPress"};

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr9={CFG_CBOX,"MenuD replacement",0,2};
__root const int ENA_NATIVE=1;
__root const CFG_CBOX_ITEM cfgcbox9[2]={"No","Yes"};

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Red button settings",1,0};

__root const CFG_HDR cfghdr10={CFG_CBOX,"Enable Red button menu on IDLE",0,2};
__root const int ENA_RBM=1;
__root const CFG_CBOX_ITEM cfgcbox10[2]={"No","Yes"};

__root const CFG_HDR cfghdr18={CFG_CBOX,"Block Red Btn longpress on IDLE",0,3};
__root const int BLOCK_RBLP=0;
__root const CFG_CBOX_ITEM cfgcbox18[3]={"No","Yes","Yes, Show Menu"};

__root const CFG_HDR cfghdr11={CFG_CBOX,"Red button longpress mode",0,2};
__root const int RED_BUT_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox11[2]={"As in FW","Hide all tasks"};

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
#endif

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"SideButtons settings",1,0};

__root const CFG_HDR cfghdr112={CFG_CBOX,"Side buttons as joypad",0,4};
__root const int SIDE_STYLE=3;
__root const CFG_CBOX_ITEM cfgcbox12[4]={"No","Yes,Up&Down","Yes,Left&Right","ExtMode"};

__root const CFG_HDR cfghdr13={CFG_UINT,"SideUp longpress",0,99};
__root const int SideUPL=0x0C;

__root const CFG_HDR cfghdr14={CFG_UINT,"SideUp shortpress",0,99};
__root const int SideUPS=0x3B;

__root const CFG_HDR cfghdr15={CFG_UINT,"SideDown longpress",0,99};
__root const int SideDNL=0x1A;

__root const CFG_HDR cfghdr16={CFG_UINT,"SideDown shortpress",0,99};
__root const int SideDNS=0x3C;

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};
