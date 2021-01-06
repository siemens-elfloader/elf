#include "..\inc\cfg_items.h"
//Конфигурация

__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Show copyright text at startup", 0, 2};
__root const int msg = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr12 = {CFG_CBOX, "show text ms", 0, 2};
__root const int TEKSTS = 0;
__root const CFG_CBOX_ITEM cfgcbox4[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr34 = {CFG_CBOX, "show(non-java friendly)", 0, 2};
__root const int evrey = 1;
__root const CFG_CBOX_ITEM cfgcbox9[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr9 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int date_X = 30;
__root const unsigned int date_Y = 264;

__root const CFG_HDR cfghdr13 = {CFG_CBOX, "show icon", 0, 2};
__root const int IKONA = 0;
__root const CFG_CBOX_ITEM cfgcbox5[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr2 = {CFG_COORDINATES,"Icon position",0,0};
__root const unsigned int IDLEICON_X = 0;
__root const unsigned int IDLEICON_Y = 245;

__root const CFG_HDR cfghdr3={CFG_STR_UTF8,"active icon(high)",0,63};
__root const char str1[64]="4:\\ZBin\\gprsspeed\\active2.png";

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"active icon(low)",0,63};
__root const char str2[64]="4:\\ZBin\\gprsspeed\\active.png";

__root const CFG_HDR cfghdr5={CFG_STR_UTF8,"inactive icon",0,63};
__root const char str3[64]="4:\\ZBin\\gprsspeed\\inactive.png";

__root const CFG_HDR cfghdr6={CFG_STR_UTF8,"no session",0,63};
__root const char str4[64]="4:\\ZBin\\gprsspeed\\off.png";

__root const CFG_HDR cfghdr7={CFG_STR_WIN1251,"Text(session)",0,63};
__root const char str5[64]="Speed: ";

__root const CFG_HDR cfghdr10={CFG_STR_WIN1251,"Text(no session)",0,63};
__root const char cone[64]="no connection";

__root const CFG_HDR cfghdr8 = {CFG_STR_UTF8, "font path", 0, 63};
__root const char fontpath[64] = "2:\\";

__root const CFG_HDR cfghdr11 = {CFG_CBOX, "fullfont use", 0, 2};
__root const int fullfont = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr22 = {CFG_CBOX, "Align", 0, 3};
__root const int align = 0;
__root const CFG_CBOX_ITEM cfgcbox6[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "Pixels between letters", 0, 10};
__root const unsigned int space = 0;

__root const CFG_HDR cfghdr67 = {CFG_CBOX, "Fast Refresh", 0, 2};
__root const int FAST_REF = 0;
__root const CFG_CBOX_ITEM cfgcbox7[2] = {"No", "Yes"};
