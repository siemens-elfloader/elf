#include "..\inc\cfg_items.h"
#include "language.h"
#include "..\inc\swilib.h"
__root const CFG_HDR cfghdr0={CFG_STR_UTF8,LG_PF,0,127};
#ifdef NEWSGOLD
__root const char playerfolder[128]="4:\\Zbin\\Ivoplay\\";
#else
__root const char playerfolder[128]="0:\\Zbin\\Ivoplay\\";
#endif
//Папки
__root const CFG_HDR cfg_m11={CFG_LEVEL,LG_VIS_FOL,1,0};
__root const CFG_HDR cfghdr_m01={CFG_LEVEL,LG_FOLDERS,1,0};
__root const CFG_HDR cfghdr0_1={CFG_STR_UTF8,LG_FFP,0,127};
__root const char folder[128]="4:\\Sounds";

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,LG_FMEDIA,0,127};
__root const char folder_scan[128]="4:\\";


__root const CFG_HDR cfghdr_m00={CFG_LEVEL,"",0,0};

//Лабуда всякая
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,LG_VISUAL,1,0};
//IDLE------
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,LG_ICON_ON_IDLE,1,0};
__root const CFG_HDR cfghdr1_2={CFG_CHECKBOX,LG_ENABLE_ICON_ON_IDLE,0,2};
__root const unsigned int EnableIconOnIdle=1;

__root const CFG_HDR cfghdr2={CFG_COORDINATES,LG_IDLE_ICON_POSITION,0,0};
__root const unsigned int IDLEICON_X=1;
__root const unsigned int IDLEICON_Y=147;

__root const CFG_HDR cfghdr3={CFG_RECT,LG_TEXT,0,0};
__root const RECT tagS = {0,67,131,93};

__root const CFG_HDR cfghdr4={CFG_COLOR,LG_FONT_COLOR,0,0};
__root const char TRACK_COL[4]={0x00,0x00,0x00,0x64};
__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};
//------------
//Overlay-----
__root const CFG_HDR cfghdr_m31={CFG_LEVEL,LG_OVERLAY,1,0};
__root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"Включить?",0,2};
__root const unsigned int over_ena=1;

__root const CFG_HDR cfghdr5_1={CFG_RECT,LG_TEXT,0,0};
__root const RECT over = {0,67,131,93};

__root const CFG_HDR cfghdr5_2={CFG_UINT,LG_OV_FONT,0,12};
__root const unsigned int over_font=1;

__root const CFG_HDR cfghdr5_3={CFG_UINT,LG_OV_ALIGN,0,100};
__root const unsigned int over_align=1;

__root const CFG_HDR cfghdr5_4={CFG_COLOR,LG_COL,0,0};
__root const char over_col[4]={0x00,0x00,0x00,0x64};

__root const CFG_HDR cfghdr5_5={CFG_COLOR,LG_BG_COL,0,0};
__root const char bg_over_color[4]={0xFF,0xFF,0xFF,0x64};
__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};
//------------
__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};
//Иконбар
#ifdef NEWSGOLD
__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"Иконбар",1,0};
__root const CFG_HDR ch4={CFG_CHECKBOX,"Вкл. иконку громкости?",0,0};
__root const int ena_vol=1;

__root const CFG_HDR ch5={CFG_UINT,"Номер картинки громкости",0,0xFFF};
__root const unsigned int vol_icon=0x6A5;
__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};
#endif

//Инфа
__root const CFG_HDR cfghdr_m101={CFG_LEVEL,"Инфа mp3",1,0};

__root const CFG_HDR ch7={CFG_CHECKBOX,"Битрейт",0,0};
__root const int ena_bit=1;

__root const CFG_HDR ch8_1={CFG_CHECKBOX,"Канал",0,0};
__root const int ena_ch=1;

__root const CFG_HDR ch9={CFG_CHECKBOX,"Частота",0,0};
__root const int ena_fr=1;

__root const CFG_HDR ch10={CFG_CHECKBOX,"Версия MPEG",0,0};
__root const int ena_mp=1;

__root const CFG_HDR ch11={CFG_CHECKBOX,"Версия Layer",0,0};
__root const int ena_lay=1;
__root const CFG_HDR cfghdr_m100={CFG_LEVEL,"",0,0};

//Обложка
//__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"Обложка",1,0};
__root const CFG_HDR ch6={CFG_CHECKBOX,"Обложка",0,0};
__root const int ena_art=1;
__root const CFG_HDR cfg_m10={CFG_LEVEL,"",0,0};

//Formats
__root const CFG_HDR cfghdr_m41={CFG_LEVEL,LG_FORMATS,1,0};
__root const CFG_HDR cfghdr6={CFG_STR_WIN1251,LG_F1,0,3};
__root const char format_1[4]="mp3";

__root const CFG_HDR cfghdr7={CFG_STR_WIN1251,LG_F2,0,3};
__root const char format_2[4]="mid";

__root const CFG_HDR cfghdr8={CFG_STR_WIN1251,LG_F3,0,3};
__root const char format_3[4]="wav";

__root const CFG_HDR cfghdr9={CFG_STR_WIN1251,LG_F4,0,3};
__root const char format_4[4]="aac";
__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr12={CFG_CBOX,"Key-hook",0,3};
__root const int EnableHook=0;
__root const CFG_CBOX_ITEM cfgcbox11[3]={LG_ALLWAYS,
                                         LG_IFUNLOCK,
                                         LG_NEVER};
     
/////////////////////////// 
     
__root const CFG_HDR cfghdr_m141={CFG_LEVEL,"Keys",1,0};

__root const CFG_HDR cfghdr23={CFG_CBOX,"KEY '1'",0,22};
__root const int Key1=20;
__root const CFG_CBOX_ITEM cfgcbox14[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr24={CFG_CBOX,"KEY '2'",0,22};
__root const int Key2=2;
__root const CFG_CBOX_ITEM cfgcbox15[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr25={CFG_CBOX,"KEY '3'",0,22};
__root const int Key3=4;
__root const CFG_CBOX_ITEM cfgcbox16[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr26={CFG_CBOX,"KEY '4'",0,22};
__root const int Key4=7;
__root const CFG_CBOX_ITEM cfgcbox17[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr27={CFG_CBOX,"KEY '5'",0,22};
__root const int Key5=0;
__root const CFG_CBOX_ITEM cfgcbox18[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr28={CFG_CBOX,"KEY '6'",0,22};
__root const int Key6=8;
__root const CFG_CBOX_ITEM cfgcbox19[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr29={CFG_CBOX,"KEY '7'",0,22};
__root const int Key7=16;
__root const CFG_CBOX_ITEM cfgcbox20[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr30={CFG_CBOX,"KEY '8'",0,22};
__root const int Key8=3;
__root const CFG_CBOX_ITEM cfgcbox21[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr31={CFG_CBOX,"KEY '9'",0,22};
__root const int Key9=6;
__root const CFG_CBOX_ITEM cfgcbox22[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr32={CFG_CBOX,"KEY '*'",0,22};
__root const int KeyZ=11;
__root const CFG_CBOX_ITEM cfgcbox23[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr33={CFG_CBOX,"KEY '0'",0,22};
#ifdef NEWSGOLD
__root const int Key0=18;
#else
__root const int Key0=9;
#endif
__root const CFG_CBOX_ITEM cfgcbox24[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};

__root const CFG_HDR cfghdr34={CFG_CBOX,"KEY '#'",0,22};
__root const int KeyR=14;
__root const CFG_CBOX_ITEM cfgcbox25[22]={LG_STOPRESUME,
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
                                          LG_TRACK_INFO,
                                          LG_MEDIABASE};


     __root const CFG_HDR cfghdr_m140={CFG_LEVEL,"",0,0};
//////////////////////////
//  __root const CFG_HDR cfghdr10={CFG_COLOR,"Cash Progressbar 1",0,0};
//  __root const char COLOR_CASHPB1[4]={0xFF,0x00,0x00,0x32};


///////////////////////////     
__root const CFG_HDR cfghdr_m51={CFG_LEVEL,ILLU_IN_PROFILES,1,0};

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

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"Автовыход",1,0};

__root const CFG_HDR ch4444={CFG_CHECKBOX,"Включить?",0,0};
__root const int ena_aexit=1;

__root const CFG_HDR cfghdr55555={CFG_UINT,"Автовыход(мин.) при проигр",0,999};
__root const unsigned int autoexit_time_play=60;

__root const CFG_HDR cfghdr55555_1={CFG_UINT,"При паузе",0,999};
__root const unsigned int autoexit_time_pause=60;

__root const CFG_HDR cfghdr55555_2={CFG_UINT,"При стопе",0,999};
__root const unsigned int autoexit_time_stop=60;

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

///////////////////////////
#ifdef NEWSGOLD     
// Level 3
__root const CFG_HDR cfghdr_m61={CFG_LEVEL,LG_Set_Speed,1,0};

__root const CFG_HDR cfghdr45 = {CFG_UINT,LG_Speed_Rewind,0,60};
__root const unsigned int SPEED_REW=20;

__root const CFG_HDR cfghdr46 = {CFG_UINT,LG_Step_Rewind,0,60};
__root const unsigned int STEP_REW=1;

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};
#endif

#ifdef ELKA
//AudioBuffer
__root const CFG_HDR cfghdr_m71={CFG_LEVEL,"AudioBuffer",1,0};

__root const CFG_HDR ch0={CFG_CBOX,"Enable AudioBuffer config",0,2};
__root const unsigned int allowbuf=1;
__root const CFG_CBOX_ITEM cb1[2]={"Disable","Enable"};

__root const CFG_HDR ch1={CFG_UINT,"RAM AudBufOffset",0x00000000,0xFFFFFFFF};
__root const unsigned int audcfg=0x0;
//__root const unsigned int audcfg=0xA8F5798C;
__root const CFG_HDR ch2={CFG_UINT,"Nof Buffers:",0,10};
__root const unsigned int buff_nof=5;

__root const CFG_HDR ch3={CFG_UINT,"Buffer Size: x10",0,30};
__root const unsigned  int buff_size=20;

__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"",0,0};
#endif
//__root const CFG_HDR ch7={CFG_UINT,"Размеры(x*x)",0,200};
//__root const unsigned int art_wh=120;

//__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

__root const CFG_HDR ch8={CFG_CHECKBOX,"Посылать тэги?",0,0};
__root const int ena_tag=1;


