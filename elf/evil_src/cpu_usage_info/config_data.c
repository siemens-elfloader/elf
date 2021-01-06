#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Show copyright text at startup", 0, 2};
__root const int msg = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"No", "Yes"};
/*
__root const CFG_HDR cfghdr1 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int date_X = 0;
__root const unsigned int date_Y = 30;
*/
__root const CFG_HDR cfghdr4 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int date_X2 = 0;
__root const unsigned int date_Y2 = 30;

__root const CFG_HDR cfghdr5 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int date_X3 = 0;
__root const unsigned int date_Y3 = 30;

__root const CFG_HDR cfghdr2 = {CFG_STR_UTF8, "font path", 0, 63};
__root const char fontpath[64] = "4:\\zbin\\img\\font\\";

__root const CFG_HDR cfghdr3 = {CFG_CBOX, "fullfont use", 0, 2};
__root const int fullfont = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "Pixels between letters", 0, 10};
__root const unsigned int space = 1;

