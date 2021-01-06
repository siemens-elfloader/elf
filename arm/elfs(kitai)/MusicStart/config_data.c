#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#define scrh  319
#define scrw  239
#else 
#define DEFAULT_DISK "0"
#define scrh  175
#define scrw  131
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"General Path",3,127};
__root const char g_path[128]=DEFAULT_DISK":\\ZBin\\MusicStart\\";


__root const CFG_HDR cfghdr_0_0={CFG_LEVEL,"Idle Screen Setup",1,0};

__root const CFG_HDR cfghdr01= {CFG_RECT, "Name Position", 0, 239};
__root const RECT name_pos = {0,scrh/2,scrw,scrh/2+20};

__root const CFG_HDR cfghdr02={CFG_UINT,"Name Font",0,16};
__root const unsigned int name_font=FONT_SMALL;

__root const CFG_HDR cfghdr03={CFG_COLOR,"Name Color",0,0};
__root const char name_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr04={CFG_COLOR,"Name Frame Color",0,0};
__root const char frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr05={CFG_COLOR,"Name Rounded Frame Color",0,0};
__root const char round_frame_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_1={CFG_LEVEL,"GUI Song Name Setup",1,0};

__root const CFG_HDR cfghdr10={CFG_COLOR,"Main Backround Color",0,0};
__root const char gui_main_bg_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr11={CFG_RECT,"Name Position",0,0};
__root const RECT gui_name_pos={1,scrh/2-30,scrw-1,scrh/2};

__root const CFG_HDR cfghdr12={CFG_UINT,"Name Font",0,16};
__root const unsigned int gui_name_font=FONT_SMALL;

__root const CFG_HDR cfghdr13={CFG_COLOR,"Name Color",0,0};
__root const char gui_name_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr14={CFG_COLOR,"Name Frame Color",0,0};
__root const char gui_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr1b={CFG_COLOR,"Name Rounded Frame Color",0,0};
__root const char gui_round_frame_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr_1_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_4={CFG_LEVEL,"GUI Status Setup",1,0};

__root const CFG_HDR cfghdr40={CFG_COORDINATES,"Status Position",0,0};
__root const unsigned int gui_sta_x=20;
__root const unsigned int gui_sta_y=20;

__root const CFG_HDR cfghdr41={CFG_UINT,"Status Font",0,16};
__root const unsigned int gui_sta_font=FONT_SMALL;

__root const CFG_HDR cfghdr42={CFG_COLOR,"Status Color",0,0};
__root const char gui_sta_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr43={CFG_COLOR,"Status Frame Color",0,0};
__root const char gui_sta_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_4_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_5={CFG_LEVEL,"GUI Song List Setup",1,0};

__root const CFG_HDR cfghdr50={CFG_UINT,"Songs in list",0,999};
__root const unsigned int song_num_lst=5;

__root const CFG_HDR cfghdr56={CFG_UINT,"List song font",0,999};
__root const unsigned int lst_song_font=FONT_SMALL;

__root const CFG_HDR cfghdr51={CFG_COLOR,"List Song Color",0,0};
__root const char lst_song_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr57={CFG_COLOR,"List This Song Color",0,0};
__root const char lst_this_song_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr52={CFG_COLOR,"List Song Frame Color",0,0};
__root const char lst_song_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr55={CFG_COLOR,"List Rounded Frame Color",0,0};
__root const char lst_round_frame_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr53={CFG_COORDINATES,"Song List Top_left Pos",0,0};
__root const unsigned int lst_song_x=1;
__root const unsigned int lst_song_y=scrh/2+4;

__root const CFG_HDR cfghdr54={CFG_UINT,"Songs List Wide",0,999};
__root const unsigned int song_lst_w=scrw-1;

__root const CFG_HDR cfghdr_5_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_6={CFG_LEVEL,"GUI Number Setup",1,0};

__root const CFG_HDR cfghdr60={CFG_COORDINATES,"Number Pos",0,0};
__root const unsigned int num_pos_x=scrw*7/10;
__root const unsigned int num_pos_y=20;

__root const CFG_HDR cfghdr61={CFG_UINT,"Number Font",0,999};
__root const unsigned int num_font=FONT_SMALL;

__root const CFG_HDR cfghdr632={CFG_COLOR,"Number Color",0,0};
__root const char num_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr63={CFG_COLOR,"Number Frame Color",0,0};
__root const char num_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_6_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_3={CFG_LEVEL,"Auto Exit Setup",1,0};

__root const CFG_HDR cfghdr30={CFG_UINT,"Auto Exit Time (min)",0,999};
__root const unsigned int auto_exit_time=1;

__root const CFG_HDR cfghdr31={CFG_CBOX, "Exit Type", 0, 2};
__root const int exit_type = 0;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"Quit Elf", "Shutdown"};

__root const CFG_HDR cfghdr_3_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_2={CFG_LEVEL,"Other Setup",1,0};

__root const CFG_HDR cfghdr20={CFG_UINT,"Default Vol",0,6};
__root const unsigned int defau_vol=3;

__root const CFG_HDR cfghdr21={CFG_UINT,"Scroll Speed",0,999};
__root const unsigned int defau_scroll_speed=80;

__root const CFG_HDR cfghdr22={CFG_UINT,"Scroll Wait Time",0,999};
__root const unsigned int scroll_wait_time=108;

__root const CFG_HDR cfghdr19={CFG_UINT,"SoftKey Font",0,16};
__root const unsigned int sk_font=FONT_MEDIUM;

__root const CFG_HDR cfghdr1a={CFG_COLOR,"SoftKey Color",0,0};
__root const char sk_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr_2_0={CFG_LEVEL,"",0,0};

