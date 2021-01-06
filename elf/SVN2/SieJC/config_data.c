#include "..\inc\cfg_items.h"
#include "lang.h"
//Конфигурация

#ifdef NEWSGOLD
#define DEFAULT_DISK_CFG "4"
#else
#define DEFAULT_DISK_CFG "0"
#endif

// connect settings
__root const CFG_HDR cfghdr_CONNECT_LEVEL={CFG_LEVEL,LG_SETUPCONECT,1,0};

__root const CFG_HDR cfghdr0={CFG_UTF8_STRING,LG_LOGIN,0,31};
__root const char USERNAME[32]="";

__root const CFG_HDR cfghdr1={CFG_UTF8_STRING_PASS,LG_PASSWORD,0,31};
__root const char PASSWORD[32]="";

__root const CFG_HDR cfghdr2={CFG_STR_WIN1251,LG_SERVER,0,127};
__root const char JABBER_SERVER[128]="jabber.ru";

__root const CFG_HDR cfghdr3={CFG_STR_WIN1251,LG_HOST,0,127};
__root const char JABBER_HOST[128]="jabber.ru";

__root const CFG_HDR cfghdr3_1={CFG_CBOX,LG_HOSTTYPE,0,2};
__root const int IS_IP = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={LG_HOSTNAME,LG_IPADRESS};

__root const CFG_HDR cfghdr4={CFG_UINT,LG_PORT,0,65535};
__root const unsigned int JABBER_PORT=5222;

__root const CFG_HDR cfghdr5={CFG_CBOX,LG_AUTHTYPE,0,2};
__root const int USE_SASL = 0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Simple","SASL"};

__root const CFG_HDR cfghdr6={CFG_CBOX,LG_ZLIBUSE,0,2};
__root const int USE_ZLIB = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={LG_NO,LG_YES};

__root const CFG_HDR cfghdr7={CFG_UTF8_STRING,LG_RES,0,29};
__root const char RESOURCE[30] = "SieJC";

__root const CFG_HDR cfghdr_CONNECT_LEVEL_END={CFG_LEVEL,"",0,0};
// end connect settings

__root const CFG_HDR cfghdr8={CFG_CBOX,LG_HISTORY,0,2};
__root const int WRITE_HISTORY = 0;
__root const CFG_CBOX_ITEM cfgcbox1435[2]={LG_DISABLED,LG_ENABLED};

__root const CFG_HDR cfghdr9={CFG_CBOX,LG_MUCHIST,0,2};
__root const int WRITE_MUC_HISTORY = 0;
__root const CFG_CBOX_ITEM cfgcbox36546[2]={LG_DISABLED,LG_ENABLED};

__root const CFG_HDR cfghdr10={CFG_UTF8_STRING,LG_MUCDEF,0,63};
__root const char DEFAULT_MUC[64]="siepatchdb@conference.jabber.ru";

__root const CFG_HDR cfghdr11={CFG_UTF8_STRING,LG_MUCDEFNIK,0,63};
__root const char DEFAULT_MUC_NICK[64]="";

__root const CFG_HDR cfghdr59={CFG_UINT,LG_MUCDEFMSGCOUNT,0,20};
__root const unsigned int DEFAULT_MUC_MSGCOUNT=20;

__root const CFG_HDR cfghdr60={CFG_CHECKBOX,LG_AUTO_JOIN,0,2};
__root const int MUC_AUTOJOIN=0;

__root const CFG_HDR cfghdrshowii={CFG_CHECKBOX, LG_SHOWIDLEICON, 0, 2};
__root const int IDLE_ICON=1;

__root const CFG_HDR cfghdr12={CFG_COORDINATES,LG_IDLEICON,0,0};
__root const unsigned int IDLE_ICON_X=0;
__root const unsigned int IDLE_ICON_Y=50;

__root const CFG_HDR cfghdr17657={CFG_CHECKBOX,LG_POPUPDIS,0,2};
__root const int DISPLAY_POPUPS=1;

__root const CFG_HDR cfghdr17658={CFG_CHECKBOX,LG_FIRST_LETTER,0,2};
__root const int FIRST_LETTER = 0;

__root const CFG_HDR cfghdr13={CFG_CHECKBOX,LG_COMPOSEV,0,2};
__root const int COMPOSING_EVENTS=1;

__root const CFG_HDR cfghdr15345={CFG_CHECKBOX,LG_DELIVREP,0,2};
__root const int DELIVERY_EVENTS=1;

__root const CFG_HDR cfghdr15346={CFG_CHECKBOX,LG_USEATTENTION,0,2};
__root const int USE_ATTENTION=0;

__root const CFG_HDR cfghdr18001={CFG_CHECKBOX,LG_SHOWSTAT_MUCINOUT,0,2};
__root const int SHOWSTAT_MUCINOUT=1;

__root const CFG_HDR cfghdr18002={CFG_CHECKBOX,LG_SHOWSTAT_MUCCHANGESTAT,0,2};
__root const int SHOWSTAT_MUCCHANGESTAT=1;

__root const CFG_HDR cfghdr18003={CFG_CHECKBOX,LG_BOLDNICKINMUC,0,2};
__root const int BOLD_NICK_INMUC=0;

__root const CFG_HDR cfghdr18004={CFG_CHECKBOX,LG_EXT_VERSION_INFO,0,2};
__root const int EXT_VERSION_INFO=0;

// Настройка сигналов
__root const CFG_HDR cfghdr_SOUNDS_SETUP={CFG_LEVEL,LG_SETUPSND,1,0};

__root const CFG_HDR cfghdr130={CFG_UINT,LG_SETUPVIBRPWR,10,100};
__root const unsigned int vibraPower=10;

__root const CFG_HDR cfghdr14={CFG_UINT,LG_SNDVOL,0,6};
__root const unsigned int sndVolume=6;

__root const CFG_HDR cfghdr15={CFG_STR_UTF8,LG_SNDMSGSND,0,63};
__root const char sndMsgSend[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Sounds\\send.wav";

__root const CFG_HDR cfghdr16={CFG_STR_UTF8,LG_SNDMSGMUC,0,63};
__root const char sndConf[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Sounds\\conf.wav";

__root const CFG_HDR cfghdr17={CFG_STR_UTF8,LG_SNDMSGPM,0,63};
__root const char sndPM[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Sounds\\message.wav";

__root const CFG_HDR cfghdrsnd1={CFG_STR_UTF8,LG_SNDONLINE,0,63};
__root const char sndOnline[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Sounds\\online.wav";

__root const CFG_HDR cfghdrsnd2={CFG_STR_UTF8,LG_SNDOFFLINE,0,63};
__root const char sndOffline[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Sounds\\offline.wav";

__root const CFG_HDR cfghdrsnd3={CFG_STR_UTF8,LG_SNDCOMPOSING,0,63};
__root const char sndComposing[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Sounds\\composing.wav";

__root const CFG_HDR cfghdr_SOUNDS_SETUP_END={CFG_LEVEL,"",0,0};

// Пути
__root const CFG_HDR cfghdr_PATHS_LEVEL={CFG_LEVEL,LG_SETUPPATH,1,0};

__root const CFG_HDR cfghdr18={CFG_STR_UTF8,LG_PATHHIST,0,127};
__root const char HIST_PATH[128]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\history\\";

__root const CFG_HDR cfghdr19={CFG_STR_UTF8,LG_PATHPIC,0,127};
__root const char PATH_TO_PIC[128]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\img\\";

__root const CFG_HDR cfghdr34={CFG_STR_UTF8,LG_PATHAVATARS,0,127};
__root const char PATH_TO_AVATARS[128]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\avatars\\";

__root const CFG_HDR cfghdr20={CFG_STR_UTF8,LG_PATHCMD,0,63};
__root const char COMMANDS_PATH[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Templates\\commands.txt";

__root const CFG_HDR cfghdr21={CFG_STR_UTF8,LG_PATHMESG,0,63};
__root const char MESSAGES_PATH[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Templates\\Messages.txt";

__root const CFG_HDR cfghdr22={CFG_STR_UTF8,LG_PATHKNOWF,0,63};
__root const char KNOW_FEATURES_PATH[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Templates\\known_features.txt";

__root const CFG_HDR cfghdr23={CFG_STR_UTF8,LG_PATHSMILECFG,0,63};
__root const char SMILE_FILE[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\smiles.cfg";

__root const CFG_HDR cfghdr233={CFG_STR_UTF8,LG_PATHSMILEDIR,0,63};
__root const char SMILE_PATH[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\smiles\\";

__root const CFG_HDR cfghdr244={CFG_STR_UTF8, LG_COLORPATH,0, 63};
__root const char color_PATH[64]=DEFAULT_DISK_CFG ":\\ZBin\\SieJC\\Color\\";

__root const CFG_HDR cfghdr24={CFG_STR_WIN1251,LG_DEFAULTDISK,0,127};
__root const char DEFAULT_DISC[128]=DEFAULT_DISK_CFG;

__root const CFG_HDR cfghdr_PATHS_LEVEL_END={CFG_LEVEL,"",0,0};

// Default text in status
__root const CFG_HDR cfghdr_DEFTEXTSTAT_LEVEL={CFG_LEVEL,LG_TEXTSTATUS,1,0};

__root const CFG_HDR cfghdr25={CFG_UTF8_STRING,LG_STONLINE,0,255};
__root const char DEFTEX_ONLINE[256]="Online";

__root const CFG_HDR cfghdr26={CFG_UTF8_STRING,LG_STCHAT,0,255};
__root const char DEFTEX_CHAT[256]="Chat";

__root const CFG_HDR cfghdr27={CFG_UTF8_STRING,LG_STAWAY,0,255};
__root const char DEFTEX_AWAY[256]="Away";

__root const CFG_HDR cfghdr28={CFG_UTF8_STRING,LG_STXA,0,255};
__root const char DEFTEX_XA[256]="Xa";

__root const CFG_HDR cfghdr29={CFG_UTF8_STRING,LG_STDND,0,255};
__root const char DEFTEX_DND[256]="DND";

__root const CFG_HDR cfghdr30={CFG_UTF8_STRING,LG_STINVIS,0,255};
__root const char DEFTEX_INVISIBLE[256]="Invisible";

__root const CFG_HDR cfghdr31={CFG_UTF8_STRING,LG_STOFFLINE,0,255};
__root const char DEFTEX_OFFLINE[256]="Offline";

__root const CFG_HDR cfghdr142={CFG_UTF8_STRING,"MUC offline",0,255};
__root const char DEFTEX_MUCOFFLINE[256]="";

__root const CFG_HDR cfghdr_DEFTEXTSTAT_LEVEL_END={CFG_LEVEL,"",0,0};
///////////////
__root const CFG_HDR cfghdr_AUTOSTATUS={CFG_LEVEL, LG_AUTOSTATUS, 1,0};

__root const CFG_HDR cfghdr40={CFG_CHECKBOX,LG_AS_ENABLED,0,2};
__root const int AUTOSTATUS_ENABLED = 0;

__root const CFG_HDR cfghdr41={CFG_UINT,LG_AS_TIME,1,60};
__root const unsigned int AUTOSTATUS_TIME = 5;

__root const CFG_HDR cfghdr42={CFG_UTF8_STRING, LG_AS_TEXT, 0, 255};
__root const char DEFTEX_AUTOSTATUS[256]="Auto away:";

__root const CFG_HDR cfghdr_AUTOSTATUS_END={CFG_LEVEL,"",0,0};

//Шрифты
__root const CFG_HDR cfghdr_FONTS={CFG_LEVEL,LG_VIEW,1,0};

__root const CFG_HDR cfghdr36={CFG_CBOX,LG_ROSTER_FONT,0,6};
__root const int ROSTER_FONT = 0;
__root const CFG_CBOX_ITEM cfgcbox_font_roster[6]={
  LG_SMALL_NORMAL_FONT,
  LG_SMALL_BOLD_FONT,
  LG_MID_NORMAL_FONT,
  LG_MID_BOLD_FONT,
  LG_LARGE_NORMAL_FONT,
  LG_LARGE_BOLD_FONT
};

__root const CFG_HDR cfghdr37={CFG_CBOX,LG_CHATS_FONT,0,6};
__root const int MESSAGES_FONT = 0;
__root const CFG_CBOX_ITEM cfgcbox_font_msgwin[6]={
  LG_SMALL_NORMAL_FONT,
  LG_SMALL_BOLD_FONT,
  LG_MID_NORMAL_FONT,
  LG_MID_BOLD_FONT,
  LG_LARGE_NORMAL_FONT,
  LG_LARGE_BOLD_FONT
};

__root const CFG_HDR cfghdr38={CFG_CBOX,LG_UNDERLINING,0,2};
__root const int pod_mess = 0;
__root const CFG_CBOX_ITEM cfgcbox10[2]={LG_NO,LG_YES};

__root const CFG_HDR cfghdr_FONTS_END={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr39={CFG_CBOX,LG_KBD_LAYOUT,0,2};
__root const int KBD_LAYOUT = 0;
__root const CFG_CBOX_ITEM cfgcboxkbd[2]={
  LG_KBD1,
  LG_KBD2
};
__root const CFG_HDR cfghdr35={CFG_UINT,LG_SKROLL,0,12};
__root const unsigned int DEF_SKR=10;
// EOL, EOF
