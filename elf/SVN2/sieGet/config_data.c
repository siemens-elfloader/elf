//  ŒÕ‘»√!!!
#include "..\inc\cfg_items.h"
#include "include.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#define MAX_VOLUME 6
#else
#define DEFAULT_DISK "0"
#define MAX_VOLUME 4
#endif

/* Paths setup */
__root const CFG_HDR cfghdr0 = {CFG_LEVEL, "Paths setup", 1, 0};

__root const CFG_HDR cfghdr0_1 = {CFG_STR_UTF8, "SieGet folder", 3, 127};
__root const char CFG_SIEGET_FOLDER[128] = DEFAULT_DISK ":\\ZBin\\SieGet\\";

__root const CFG_HDR cfghdr0_2 = {CFG_STR_UTF8, "Downloads folder", 3, 127};
__root const char CFG_DOWNLOADS_FOLDER[128] = DEFAULT_DISK ":\\ZBin\\SieGet\\Downloads\\";

__root const CFG_HDR cfghdr0_3 = {CFG_LEVEL, "", 0, 0};

/* Notify setup */
__root const CFG_HDR cfghdr1 = {CFG_LEVEL, "Notify setup", 1, 0};

__root const CFG_HDR cfghdr1_1 = {CFG_UINT, "Sound volume", 0, MAX_VOLUME};
__root const unsigned int CFG_SOUNDS_VOLUME = MAX_VOLUME;

__root const CFG_HDR cfghdr1_2 = {CFG_UINT, "Vibra power", 0, 100};
__root const unsigned int CFG_VIBRA_POWER = 10;

__root const CFG_HDR cfghdr1_3 = {CFG_LEVEL, "", 0, 0};

/* Logs setup */
__root const CFG_HDR cfghdr2 = {CFG_LEVEL, "Logs setup", 1, 0};

__root const CFG_HDR cfghdr2_1 = {CFG_CHECKBOX, "Save logs to files", 0, 3};
__root const int CFG_LOG_TO_FILE = 0;

__root const CFG_HDR cfghdr2_2 = {CFG_CHECKBOX, "Log date/time", 0, 3};
__root const int CFG_LOG_DATE_TIME = 1;

__root const CFG_HDR cfghdr2_3 = {CFG_LEVEL, "", 0, 0};

/* IDLE icon setup */
__root const CFG_HDR cfghdr3 = {CFG_LEVEL, "Icon setup", 1, 0};

__root const CFG_HDR cfghdr3_1 = {CFG_CHECKBOX, "Show icon on IDLE", 0, 3};
__root const int CFG_SHOW_IDLE_ICON = 1;

__root const CFG_HDR cfghdr3_2 = {CFG_COORDINATES, "IDLE icon position", 0, 0};
__root const unsigned int CFG_IDLE_ICON_X = 0;
__root const unsigned int CFG_IDLE_ICON_Y = 35;

#ifdef NEWSGOLD  
__root const CFG_HDR cfghdr3_3 = {CFG_CHECKBOX, "Show icon in iconbar", 0, 3};
__root const int CFG_SHOW_TRAY_ICON = 0;

__root const CFG_HDR cfghdr3_4={CFG_UINT,"Normal icon",0,10000};
__root const unsigned int TRAY_ICON_OFF=2500;

__root const CFG_HDR cfghdr3_5={CFG_UINT,"Download icon",0,10000};
__root const unsigned int TRAY_ICON_ON=2501;
#endif

__root const CFG_HDR cfghdr3_6 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr4 = {CFG_CHECKBOX, "Close GUI after add", 0, 3};
__root const int CFG_CLOSE_GUI = 1;

__root const CFG_HDR cfghdr5 = {CFG_CHECKBOX, "Realtime write", 0, 3};
__root const int CFG_FFLUSH = 0;
