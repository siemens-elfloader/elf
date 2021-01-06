#include "..\inc\cfg_items.h"
#include "lang.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,LG_Default_playlist,3,127};
__root const char DEFAULT_PLAYLIST[128] = "0:\\Sounds\\Playlist.m3u";

__root const CFG_HDR cfghdr01={CFG_STR_UTF8,LG_Default_playlist_2,3,127};
__root const char DEFAULT_PLAYLIST1[128] = "0:\\Sounds\\Playlist2.m3u";

__root const CFG_HDR cfghdr02={CFG_STR_UTF8,LG_Default_playlist_3,3,127};
__root const char DEFAULT_PLAYLIST2[128] = "0:\\Sounds\\Playlist3.m3u";

__root const CFG_HDR cfghdr03={CFG_COORDINATES,LG_Idle_coordinates,0,0};
__root const unsigned int IDLE_X = 5;
__root const unsigned int IDLE_Y = 120;

__root const CFG_HDR cfghdr04 = {CFG_UINT,LG_Auto_Exit_Min,0,2000};
__root const unsigned int AUTO_EXIT_MIN=0;

//Level 1
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,LG_Sets,1,0};

__root const CFG_HDR cfghdr12={CFG_CBOX,LG_Show_full_names,0,3};
__root const unsigned int SHOW_NAMES = 2;
__root const CFG_CBOX_ITEM cfgcbox1[3]={"Tags(don't work)","Full","Name"};

__root const CFG_HDR cfghdr13={CFG_CHECKBOX,LG_Show_effects,0,2};
__root const unsigned int GrafOn = 1;

__root const CFG_HDR cfghdr14={CFG_CHECKBOX,LG_Show_Anim,0,2};
__root const unsigned int GrafOn1 = 1;

__root const CFG_HDR cfghdr15={CFG_CHECKBOX,LG_Show_info,0,2};  //Показывать информацию или нет - Vedan
#ifdef NEWSGOLD
__root const unsigned int InfoOn = 1;
#else
__root const unsigned int InfoOn = 0;
#endif

__root const CFG_HDR cfghdr16={CFG_CHECKBOX,LG_Show_Popup,0,2};  //Показывать попапы   AAA
__root const unsigned int SHOW_POPUP = 1;

__root const CFG_HDR cfghdr16_0={CFG_CHECKBOX,LG_Save_Sets,0,2};  //Сохранять настройки   AAA
__root const unsigned int SAVE_SETS = 1;

__root const CFG_HDR cfghdr16_1={CFG_CHECKBOX,LG_Show_All_Track,0,2};  // Показывать все/один трек. Сделано хитрожописто,
__root const unsigned int ALLTRACK=1;                              // кто будет менять - подумайте!   AAA

__root const CFG_HDR cfghdr16_2={CFG_CHECKBOX,LG_LoadKeys,0,2};
__root const unsigned int LOAD_KEYS = 1;

__root const CFG_HDR cfghdr17={CFG_CBOX,LG_Playmode,0,4};  // Временно убрал варинг Blind007
__root const unsigned int PlayMode = 0;
__root const CFG_CBOX_ITEM cfgcbox3[4]={LG_Play_all,LG_Repeat_all,LG_Random,LG_Repeat_one};

__root const CFG_HDR cfghdr18={CFG_CBOX,LG_Extension_of_playlist,0,2};
__root const unsigned int EXT = 0;
__root const CFG_CBOX_ITEM cfgcbox4[2]={LG_spl,LG_m3u};

__root const CFG_HDR cfghdr19={CFG_UINT,LG_Default_volume,0,15};
__root const unsigned int soundvolume=6;

__root const CFG_HDR cfghdr20 = {CFG_UINT,LG_Size_Of_Font,0,20};
#ifdef NEWSGOLD
__root const unsigned int SizeOfFont = 11;
#else
__root const unsigned int SizeOfFont = 7;
#endif


__root const CFG_HDR cfghdr21={CFG_CBOX,LG_Send_fname,0,3};
__root const unsigned int FnameIPC = 0;
__root const CFG_CBOX_ITEM cfgcbox5[3]={LG_No,"Name","ID3 Tag"};

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//Level 2
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,LG_Paths,1,0};

__root const CFG_HDR cfghdr22={CFG_STR_UTF8,LG_Picture_folder,3,127};
__root const char PIC_DIR[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\img\\";

__root const CFG_HDR cfghdr23={CFG_STR_UTF8,LG_Playlist_folder,3,127};
__root const char PLAYLISTS[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Playlists\\";

__root const CFG_HDR cfghdr24={CFG_STR_UTF8,LG_Music_folder,3,127};
__root const char MUSIC[128] = "0:\\Sounds\\";

__root const CFG_HDR cfghdr25={CFG_STR_UTF8,LG_Path_To_SCE,3,127};
__root const char EXENAME[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\SPlayer cfg editor.elf";

__root const CFG_HDR cfghdr26={CFG_STR_UTF8,LG_Path_To_Lang,3,127};
__root const char LANGFILE[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Files\\RU.txt"; //Путь к текстовому файлу - Vedan

__root const CFG_HDR cfghdr27={CFG_STR_UTF8,LG_Sets_Path,3,127};
__root const char SETS_PATH[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Files\\";

/*
__root const CFG_HDR cfghdr27={CFG_STR_UTF8,LG_KeySet_Path,3,127};
__root const char KEYCFG_PATH[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Files\\spkeys.cfg";

__root const CFG_HDR cfghdr28={CFG_STR_UTF8,LG_Sets_File,3,127};
__root const char SETS[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Files\\sets.cfg";

__root const CFG_HDR cfghdr29={CFG_STR_UTF8,LG_Sets_File,3,127};
__root const char PLS[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Files\\pls.cfg";
*/
__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};
/*
// Level 3
__root const CFG_HDR cfghdr_m31={CFG_LEVEL,LG_Key_Settings,1,0};

__root const CFG_HDR cfghdr32={CFG_CBOX,LG_LoadKeys,0,2};
__root const unsigned int LOAD_KEYS = 1;
__root const CFG_CBOX_ITEM cfgcbox6[2]={LG_No,LG_Yes};

__root const CFG_HDR cfghdr33={CFG_STR_UTF8,LG_KeySet_Path,3,127};
__root const char KEYCFG_PATH[128] = DEFAULT_DISK ":\\ZBin\\SPlayer\\Files\\spkeys.cfg";

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};
*/
// Level 3
__root const CFG_HDR cfghdr_m31={CFG_LEVEL,LG_Set_Speed,1,0};

__root const CFG_HDR cfghdr32 = {CFG_UINT,LG_Speed_Moving,0,30};
#ifdef NEWSGOLD
__root const unsigned int SCROLL_MULT=2;
#else
__root const unsigned int SCROLL_MULT=10;
#endif

__root const CFG_HDR cfghdr33 = {CFG_UINT,LG_Step_Moving,0,30};
__root const unsigned int STEP_SCROLL_MULT=1;

__root const CFG_HDR cfghdr34 = {CFG_UINT,LG_Speed_Rewind,0,60};
__root const unsigned int SPEED_REW=20;

__root const CFG_HDR cfghdr35 = {CFG_UINT,LG_Step_Rewind,0,60};
__root const unsigned int STEP_REW=1;

__root const CFG_HDR cfghdr36 = {CFG_UINT,LG_Speed_Moving_PL,0,40};
__root const unsigned int SPEED_MOVE=10;

__root const CFG_HDR cfghdr37 = {CFG_UINT,LG_Speed_Open_Moving,0,40};
__root const unsigned int SPEED_OPEN_MOVE=10;

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};
