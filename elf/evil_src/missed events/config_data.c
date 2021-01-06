#include "..\inc\cfg_items.h"
//Конфигурация

__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Show copyright text at startup", 0, 2};
__root const int msg = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr9 = {CFG_COORDINATES,"First Text position",0,0};
__root const unsigned int date_X = 166;
__root const unsigned int date_Y = 230;

__root const CFG_HDR cfghdr2 = {CFG_COORDINATES,"background position",0,0};
__root const unsigned int IDLEICON_X = 149;
__root const unsigned int IDLEICON_Y = 226;

__root const CFG_HDR cfghdr3={CFG_STR_UTF8,"background",0,63};
__root const char str1[64]="4:\\ZBin\\missedevents\\background.png";

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"calls",0,63};
__root const char str2[64]="4:\\ZBin\\missedevents\\calls.png";

__root const CFG_HDR cfghdr5={CFG_STR_UTF8,"sms",0,63};
__root const char str3[64]="4:\\ZBin\\missedevents\\sms.png";

__root const CFG_HDR cfghdr6={CFG_STR_UTF8,"other",0,63};
__root const char str4[64]="4:\\ZBin\\missedevents\\other.png";

//__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"first missed",0,63};
//__root const char str2[64]="4:\\ZBin\\gprsspeed\\active.png";

__root const CFG_HDR cfghdr8 = {CFG_STR_UTF8, "font path", 0, 63};
__root const char fontpath[64] = "4:\\";

__root const CFG_HDR cfghdr11 = {CFG_CBOX, "fullfont use", 0, 2};
__root const int fullfont = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr22 = {CFG_CBOX, "Align", 0, 3};
__root const int align = 0;
__root const CFG_CBOX_ITEM cfgcbox6[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "Pixels between letters", 0, 10};
__root const unsigned int space = 1;

__root const CFG_HDR cfghdr79 = {CFG_UINT, "benlux add-on(space vertical)", 0, 10};
__root const unsigned int luki = 2;
