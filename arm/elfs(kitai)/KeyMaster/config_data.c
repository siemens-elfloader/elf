#include "..\inc\cfg_items.h"
//Конфигурация

__root const CFG_HDR cfghdr0={CFG_CBOX,"允许锁键盘时使用",0,2};
__root const int ENA_LOCK=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"否","是"};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"提示信息",1,0};

__root const CFG_HDR cfghdr1={CFG_CBOX,"允许欢迎信息",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"否","是"};

__root const CFG_HDR cfghdr2={CFG_CBOX,"允许Key2Joy信息",0,2};
__root const int ENA_K2J_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"否","是"};

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"播放控制",1,0};
#ifndef NEWSGOLD
__root const CFG_HDR cfghdr3={CFG_CBOX,"允许播放控制",0,2};
__root const int ENA_MEDIAC=0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"否","是"};

__root const CFG_HDR cfghdr4={CFG_CBOX,"Start player on HandsFree button",0,3};
__root const int ENA_PLAYER=1;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"否","是,Elf播放器","是,默认播放器"};
#else 
__root const CFG_HDR cfghdr4={CFG_CBOX,"Start player on HandsFree button",0,2};
__root const int ENA_PLAYER=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"否","是,Elf播放器"};
#endif

__root const CFG_HDR cfghdr5={CFG_STR_UTF8,"Elf播放器路径",3,127};
__root const char player_path[128]="2:\\Misc\\Data inbox\\SPlayer.elf";

__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"ELF播放器播放列表",3,127};
__root const char playlist_path[128]="0:\\Sounds\\ Best.m3u";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Key2Joy",1,0};

__root const CFG_HDR cfghdr6={CFG_CBOX,"使用Key2Joy",0,4};
__root const int ENA_KEY2JOY=2;
__root const CFG_CBOX_ITEM cfgcbox6[4]={"否","是","左右键7,9","左右键1,3"};

__root const CFG_HDR cfghdr7={CFG_UINT,"Key2Joy键",0,99};
__root const int Key2Joy_KEY=11;

__root const CFG_HDR cfghdr8={CFG_CBOX,"激活模式",0,2};
__root const int Key2Joy_KEY_LONG_PRESS=1;
__root const CFG_CBOX_ITEM cfgcbox8[2]={"短按","长按"};

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr9={CFG_CBOX,"MenuD替换",0,2};
__root const int ENA_NATIVE=1;
__root const CFG_CBOX_ITEM cfgcbox9[2]={"否","是"};

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"红键设置",1,0};

__root const CFG_HDR cfghdr10={CFG_CBOX,"允许桌面使用红键",0,2};
__root const int ENA_RBM=1;
__root const CFG_CBOX_ITEM cfgcbox10[2]={"否","是"};

__root const CFG_HDR cfghdr11={CFG_CBOX,"长按红键模式",0,2};
__root const int RED_BUT_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox11[2]={"和通常一样","隐藏所有任务"};

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
#endif

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"侧键设置",1,0};

__root const CFG_HDR cfghdr112={CFG_CBOX,"侧键当导航键",0,4};
__root const int SIDE_STYLE=3;
__root const CFG_CBOX_ITEM cfgcbox12[4]={"否","是,上和下","是,左和右","ExtMode"};

__root const CFG_HDR cfghdr13={CFG_UINT,"侧上长按",0,99};
__root const int SideUPL=0x0C;

__root const CFG_HDR cfghdr14={CFG_UINT,"侧上短按",0,99};
__root const int SideUPS=0x3B;

__root const CFG_HDR cfghdr15={CFG_UINT,"侧下长按",0,99};
__root const int SideDNL=0x1A;

__root const CFG_HDR cfghdr16={CFG_UINT,"侧下短按",0,99};
__root const int SideDNS=0x3C;

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};
