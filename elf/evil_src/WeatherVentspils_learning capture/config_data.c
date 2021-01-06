#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Show copyright text at startup", 0, 2};
__root const int msg = 0;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr1 = {CFG_STR_UTF8, "font path", 0, 63};
__root const char fontpath[64] = "4:\\zbin\\img\\font\\";

__root const CFG_HDR cfghdr2 = {CFG_STR_UTF8, "icon path", 0, 63};
__root const char icopath[64] = "4:\\zbin\\ventspilsw\\img\\";

__root const CFG_HDR cfghdr3 = {CFG_CBOX, "fullfont use", 0, 2};
__root const int fullfont = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr4 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int date_X = 3;
__root const unsigned int date_Y = 40;

__root const CFG_HDR cfghdr5 = {CFG_COORDINATES,"Icon position",0,0};
__root const unsigned int weather_X = 79;
__root const unsigned int weather_Y = 53;

__root const CFG_HDR cfghdr6 = {CFG_STR_UTF8, "sound path", 0, 63};
__root const char soundpath[64] = "4:\\zbin\\ventspilsw\\wav\\";

__root const CFG_HDR cfghdr7 = {CFG_CBOX, "Enable talk in update", 0, 2};
__root const int ENA_TALK = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr8 = {CFG_UINT, "Morning time", 0, 23};
__root const unsigned int minimum = 10;

__root const CFG_HDR cfghdr9 = {CFG_UINT, "Evening time", 0, 23};
__root const unsigned int maximum = 22;
