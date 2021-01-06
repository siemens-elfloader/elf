#include "C:\ARM_ALL\inc\cfg_items.h"
#include "C:\ARM_ALL\inc\swilib.h"

#ifdef ELKA
#define scrh  319
#define scrw  239
#else
#define scrh  175
#define scrw  131
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Путь к папке с картинками",3,127};
__root const char Player_folder[128]="4:\\ZBin\\ProPlayer\\Skins";

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Путь к папке с историей",3,127};
__root const char History_folder[128]="4:\\ZBin\\ProPlayer\\History";

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Idle Screen Setup",1,0};

__root const CFG_HDR cfghdr2={CFG_RECT, "Name Position", 0, 239};
__root const RECT name_pos={0,scrh/2,scrw,scrh/2+20};

__root const CFG_HDR cfghdr3={CFG_UINT,"Name Font",0,16};
__root const unsigned int name_font=FONT_SMALL;

__root const CFG_HDR cfghdr4={CFG_COLOR,"Name Color",0,0};
__root const char name_col[4]={0,0,0,100};

__root const CFG_HDR cfghdr5={CFG_COLOR,"Name Frame Color",0,0};
__root const char frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr6={CFG_COLOR,"Name Rounded Frame Color",0,0};
__root const char round_frame_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//========================4to za bardak tut? (by evilfox)======================

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"GUI Song Name Setup",1,0};

__root const CFG_HDR cfghdr7={CFG_RECT,"Name Position",0,0};
__root const RECT gui_name_pos={1,scrh/2-30,scrw-1,scrh/2};

__root const CFG_HDR cfghdr8={CFG_UINT,"Name Font",0,16};
__root const unsigned int gui_name_font=FONT_SMALL;

__root const CFG_HDR cfghdr9={CFG_COLOR,"Name Color",0,0};
__root const char gui_name_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr10={CFG_COLOR,"Name Frame Color",0,0};
__root const char gui_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr11={CFG_COLOR,"Name Rounded Frame Color",0,0};
__root const char gui_round_frame_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};
//========================4to za bardak tut? (by evilfox)======================

//======================added by evilfox=============================
__root const CFG_HDR cfghdr_m130={CFG_LEVEL,"Idle (mainsrceen) png",1,0};

__root const CFG_HDR cfghdr57 = {CFG_STR_UTF8, "font path", 0, 63};
__root const char fontpath[64] = "4:\\";

__root const CFG_HDR cfghdr58 = {CFG_UINT, "Pixels between letters", 0, 10};
__root const unsigned int space = 1;

__root const CFG_HDR cfghdr59 = {CFG_CBOX, "fullfont use", 0, 2};
__root const int fullfont = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr60 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int idle_X = 0;
__root const unsigned int idle_Y = 100;

__root const CFG_HDR cfghdr_m131={CFG_LEVEL,"",0,0};
//======================end of add====================================
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"Громкость",1,0};

__root const CFG_HDR cfghdr12={CFG_COORDINATES,"Position",0,0};
__root const unsigned int vol_x=0;
__root const unsigned int vol_y=10;

__root const CFG_HDR cfghdr13={CFG_UINT,"Font",0,16};
__root const unsigned int vol_font=FONT_SMALL;

__root const CFG_HDR cfghdr14={CFG_UINT,"Default Volume",0,16};
__root const unsigned int def_vol=3;

__root const CFG_HDR cfghdr15={CFG_COLOR,"Color",0,0};
__root const char vol_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr16={CFG_COLOR,"Frame Color",0,0};
__root const char vol_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"Статус",1,0};

__root const CFG_HDR cfghdr17={CFG_COORDINATES,"Position",0,0};
__root const unsigned int sts_x=0;
__root const unsigned int sts_y=20;

__root const CFG_HDR cfghdr18={CFG_UINT,"Font",0,16};
__root const unsigned int sts_font=FONT_SMALL;

__root const CFG_HDR cfghdr19={CFG_COLOR,"Color",0,0};
__root const char sts_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr20={CFG_COLOR,"Frame Color",0,0};
__root const char sts_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"Режим воспр.",1,0};

__root const CFG_HDR cfghdr21={CFG_COORDINATES,"Position",0,0};
__root const unsigned int mod_x=0;
__root const unsigned int mod_y=30;

__root const CFG_HDR cfghdr22={CFG_UINT,"Font",0,16};
__root const unsigned int mod_font=FONT_SMALL;

__root const CFG_HDR cfghdr23={CFG_COLOR,"Color",0,0};
__root const char mod_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr24={CFG_COLOR,"Frame Color",0,0};
__root const char mod_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"GUI Song List Setup",1,0};

__root const CFG_HDR cfghdr25={CFG_UINT,"Songs in list",0,999};
__root const unsigned int song_num_lst=5;

__root const CFG_HDR cfghdr26={CFG_UINT,"List song font",0,999};
__root const unsigned int lst_song_font=FONT_SMALL;

__root const CFG_HDR cfghdr27={CFG_COLOR,"List Song Color",0,0};
__root const char lst_song_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr28={CFG_COLOR,"List This Song Color",0,0};
__root const char lst_this_song_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr29={CFG_COLOR,"List Song Frame Color",0,0};
__root const char lst_song_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr30={CFG_COLOR,"List Rounded Frame Color",0,0};
__root const char lst_round_frame_col[4]={255,255,0,100};

__root const CFG_HDR cfghdr31={CFG_COORDINATES,"Song List Top_left Pos",0,0};
__root const unsigned int lst_song_x=1;
__root const unsigned int lst_song_y=scrh/2+4;

__root const CFG_HDR cfghdr32={CFG_UINT,"Songs List Wide",0,999};
__root const unsigned int song_lst_w=scrw-1;

__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"GUI Number Setup",1,0};

__root const CFG_HDR cfghdr33={CFG_COORDINATES,"Number Pos",0,0};
__root const unsigned int num_pos_x=scrw*7/10;
__root const unsigned int num_pos_y=20;

__root const CFG_HDR cfghdr34={CFG_UINT,"Number Font",0,999};
__root const unsigned int num_font=FONT_SMALL;

__root const CFG_HDR cfghdr35={CFG_COLOR,"Number Color",0,0};
__root const char num_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr36={CFG_COLOR,"Number Frame Color",0,0};
__root const char num_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m71={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"Auto Exit Setup",1,0};

__root const CFG_HDR cfghdr37={CFG_UINT,"Auto Exit Time (min)",0,999};
__root const unsigned int auto_exit_time=1;

__root const CFG_HDR cfghdr38={CFG_CBOX, "Exit Type", 0, 2};
__root const int exit_type = 0;
__root const CFG_CBOX_ITEM cfgcbox0[2] = {"Quit Elf", "Shutdown"};

__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"Часы",1,0};

__root const CFG_HDR cfghdr39={CFG_CBOX,"Включить?",0,2};
__root const int enable_clock=1;
__root const CFG_CBOX_ITEM cfgcbox41[2]={"Нет","Да"};

__root const CFG_HDR cfghdr40={CFG_CBOX,"Пок. секунды?",0,2};
__root const int enable_sec=1;
__root const CFG_CBOX_ITEM cfgcbox43[2]={"Нет","Да"};

__root const CFG_HDR cfghdr41={CFG_COORDINATES,"Позиция",0,0};
__root const unsigned int clock_x=0;
__root const unsigned int clock_y=0;

__root const CFG_HDR cfghdr42={CFG_UINT,"Шрифт",0,999};
__root const unsigned int clock_font=FONT_SMALL;

__root const CFG_HDR cfghdr43={CFG_COLOR,"Цвет",0,0};
__root const char clock_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr44={CFG_COLOR,"Цвет обводки",0,0};
__root const char clock_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m100={CFG_LEVEL,"Эквалайзер",1,0};

__root const CFG_HDR cfghdr45={CFG_COORDINATES,"Позиция",0,0};
__root const unsigned int eqs_x=0;
__root const unsigned int eqs_y=40;

__root const CFG_HDR cfghdr46={CFG_UINT,"Шрифт",0,999};
__root const unsigned int eqs_font=FONT_SMALL;

__root const CFG_HDR cfghdr47={CFG_COLOR,"Цвет",0,0};
__root const char eqs_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr48={CFG_COLOR,"Цвет обводки",0,0};
__root const char eqs_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m101={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m110={CFG_LEVEL,"Прогрессбар",1,0};

__root const CFG_HDR cfghdr49={CFG_COORDINATES,"Позиция-1",0,0};
__root const unsigned int bar_x=1;
__root const unsigned int bar_y=139;

__root const CFG_HDR cfghdr50={CFG_COORDINATES,"Позиция-2",0,0};
__root const unsigned int bar_x2=130;
__root const unsigned int bar_y2=149;

__root const CFG_HDR cfghdr51={CFG_COLOR,"Цвет",0,0};
__root const char bar_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr52={CFG_COLOR,"Цвет обводки",0,0};
__root const char bar_frame_col[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m111={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m120={CFG_LEVEL,"Other Setup",1,0};

__root const CFG_HDR cfghdr53={CFG_UINT,"Scroll Speed",0,999};
__root const unsigned int defau_scroll_speed=80;

__root const CFG_HDR cfghdr54={CFG_UINT,"Scroll Wait Time",0,999};
__root const unsigned int scroll_wait_time=108;

__root const CFG_HDR cfghdr55={CFG_UINT,"SoftKey Font",0,16};
__root const unsigned int sk_font=FONT_MEDIUM;

__root const CFG_HDR cfghdr56={CFG_COLOR,"SoftKey Color",0,0};
__root const char sk_col[4]={255,255,255,100};

__root const CFG_HDR cfghdr_m121={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

