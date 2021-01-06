#include "..\inc\cfg_items.h"
#include "language.h"

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,LG_FFP,0,127};
__root const char folder[128]="4:\\Sounds";
/////////////////////////////
      __root const CFG_HDR cfghdr_m10={CFG_LEVEL,LG_ICON_ON_IDLE,1,0};

__root const CFG_HDR cfghdr1={CFG_CHECKBOX,LG_ENABLE_ICON_ON_IDLE,0,2};
__root const unsigned int EnableIconOnIdle=0;

__root const CFG_HDR cfghdr2={CFG_COORDINATES,LG_IDLE_ICON_POSITION,0,0};
__root const unsigned int IDLEICON_X=1;
__root const unsigned int IDLEICON_Y=147;


     __root const CFG_HDR cfghdr_m11={CFG_LEVEL,"",0,0};
///////////////////////////
     
///////////////////////////     
      __root const CFG_HDR cfghdr_m20={CFG_LEVEL,LG_FORMATS,1,0};

__root const CFG_HDR cfghdr6={CFG_STR_WIN1251,LG_F1,0,3};
__root const char format_1[4]="mp3";

__root const CFG_HDR cfghdr7={CFG_STR_WIN1251,LG_F2,0,3};
__root const char format_2[4]="mid";

__root const CFG_HDR cfghdr8={CFG_STR_WIN1251,LG_F3,0,3};
__root const char format_3[4]="wav";

__root const CFG_HDR cfghdr9={CFG_STR_WIN1251,LG_F4,0,3};
__root const char format_4[4]="aac";


     __root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};
///////////////////////////

     
///////////////////////////     
      __root const CFG_HDR cfghdr_m30={CFG_LEVEL,LG_TIME,1,0};

__root const CFG_HDR cfghdr4={CFG_CHECKBOX,LG_DRAW_TRACK_TIME,0,2};
__root const int entime=1;

__root const CFG_HDR cfghdr5 = {CFG_UINT, LG_DRAW_TRACK_TIME_TIMER, 10, 267};
__root const unsigned int RedrawTime = 26;

     __root const CFG_HDR cfghdr_m31={CFG_LEVEL,"",0,0};
///////////////////////////
  
__root const CFG_HDR cfghdr12={CFG_CBOX,"Key-hook",0,3};
__root const int EnableHook=0;
__root const CFG_CBOX_ITEM cfgcbox11[3]={LG_ALLWAYS,
                                         LG_IFUNLOCK,
                                         LG_NEVER};
     
/////////////////////////// 
     
      __root const CFG_HDR cfghdr_m50={CFG_LEVEL,"Keys",1,0};

__root const CFG_HDR cfghdr23={CFG_CBOX,"KEY '1'",0,21};
__root const int Key1=20;
__root const CFG_CBOX_ITEM cfgcbox14[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr24={CFG_CBOX,"KEY '2'",0,21};
__root const int Key2=2;
__root const CFG_CBOX_ITEM cfgcbox15[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr25={CFG_CBOX,"KEY '3'",0,21};
__root const int Key3=4;
__root const CFG_CBOX_ITEM cfgcbox16[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr26={CFG_CBOX,"KEY '4'",0,21};
__root const int Key4=7;
__root const CFG_CBOX_ITEM cfgcbox17[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr27={CFG_CBOX,"KEY '5'",0,21};
__root const int Key5=0;
__root const CFG_CBOX_ITEM cfgcbox18[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr28={CFG_CBOX,"KEY '6'",0,21};
__root const int Key6=8;
__root const CFG_CBOX_ITEM cfgcbox19[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr29={CFG_CBOX,"KEY '7'",0,21};
__root const int Key7=16;
__root const CFG_CBOX_ITEM cfgcbox20[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr30={CFG_CBOX,"KEY '8'",0,21};
__root const int Key8=3;
__root const CFG_CBOX_ITEM cfgcbox21[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr31={CFG_CBOX,"KEY '9'",0,21};
__root const int Key9=6;
__root const CFG_CBOX_ITEM cfgcbox22[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr32={CFG_CBOX,"KEY '*'",0,21};
__root const int KeyZ=11;
__root const CFG_CBOX_ITEM cfgcbox23[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr33={CFG_CBOX,"KEY '0'",0,21};
__root const int Key0=9;
__root const CFG_CBOX_ITEM cfgcbox24[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};

__root const CFG_HDR cfghdr34={CFG_CBOX,"KEY '#'",0,21};
__root const int KeyR=14;
__root const CFG_CBOX_ITEM cfgcbox25[21]={LG_STOPRESUME,
                                          LG_STOP,
                                          LG_VOLUMEUP,
                                          LG_VOLUMEDOWN,
                                          LG_RANDOM,
                                          LG_PREVIOUSSKIN,
                                          LG_NEXTSKIN,
                                          LG_PREVIOUSTRACK,
                                          LG_NEXTTRACK,
                                          LG_CONFIG,
                                          LG_PLAYLISTMENU,
                                          LG_MUTE,
                                          LG_BLOCKKEYBOARD,
                                          LG_EXIT,
                                          LG_NOTHING,
                                          LG_MENU,
                                          LG_DOIDLE,
                                          LG_KEYBLOCK,
                                          LG_CONFIG4,
                                          LG_PLAY_ONCE_MORE_OR_PREVIOUS,
                                          LG_TRACK_INFO};


     __root const CFG_HDR cfghdr_m51={CFG_LEVEL,"",0,0};
    
     
__root const CFG_HDR cfghdr35={CFG_STR_UTF8,LG_PF,0,127};
__root const char playerfolder[128]="0:\\Zbin\\Ivoplay\\";
//////////////////////////
//  __root const CFG_HDR cfghdr10={CFG_COLOR,"Cash Progressbar 1",0,0};
//  __root const char COLOR_CASHPB1[4]={0xFF,0x00,0x00,0x32};


///////////////////////////     
      __root const CFG_HDR cfghdr_m40={CFG_LEVEL,ILLU_IN_PROFILES,1,0};

__root const CFG_HDR cfghdr36 = {CFG_UINT, "1", 0, 100};
__root const unsigned int profile1 = 50;

__root const CFG_HDR cfghdr37 = {CFG_UINT, "2", 0, 100};
__root const unsigned int profile2 = 30;

__root const CFG_HDR cfghdr38 = {CFG_UINT, "3", 0, 100};
__root const unsigned int profile3 = 10;

__root const CFG_HDR cfghdr39 = {CFG_UINT, "4", 0, 100};
__root const unsigned int profile4 = 50;

__root const CFG_HDR cfghdr40 = {CFG_UINT, "5", 0, 100};
__root const unsigned int profile5 = 40;

__root const CFG_HDR cfghdr41 = {CFG_UINT, "6", 0, 100};
__root const unsigned int profile6 = 50;

__root const CFG_HDR cfghdr42 = {CFG_UINT, "7", 0, 100};
__root const unsigned int profile7 = 50;

__root const CFG_HDR cfghdr43 = {CFG_UINT, "8", 0, 100};
__root const unsigned int profile8 = 50;

     __root const CFG_HDR cfghdr_m41={CFG_LEVEL,"",0,0};
///////////////////////////

