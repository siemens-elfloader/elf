#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Show copyright text",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr8 = {CFG_STR_UTF8, "font path", 0, 63};
__root const char fontpath[64] = "4:\\";

__root const CFG_HDR cfghdr11 = {CFG_CBOX, "fullfont use", 0, 2};
__root const int fullfont = 0;
__root const CFG_CBOX_ITEM cfgcbox3[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr12 = {CFG_STR_UTF8, "icon path", 0, 63};
__root const char iconpath[64] = "4:\\zbin\\ReminderMS\\img\\";

__root const CFG_HDR cfghdr13 = {CFG_COORDINATES,"position",0,0};
__root const unsigned int IDLEICON_X = 0;
__root const unsigned int IDLEICON_Y_C = 100;

__root const CFG_HDR cfghdr16={CFG_STR_UTF8,"wav",0,63};
__root const char sound_wav[64]="4:\\zbin\\ReminderMS\\sound.wav";

__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"mrs file path",0,63};
__root const char rms_file[64]="4:\\zbin\\ReminderMS\\";

__root const CFG_HDR cfghdr19 = {CFG_UINT, "Pixels between letters", 0, 10};
__root const unsigned int space = 1;

__root const CFG_HDR cfghdr20 = {CFG_STR_WIN1251, "Main txt", 0, 31};
__root const char todo[32]="To Do Today:";

__root const CFG_HDR cfghdr99 = {CFG_STR_WIN1251, "No apointment txt", 0, 31};
__root const char no_zadach[32]="no appointment";

__root const CFG_HDR cfghdr21={CFG_CBOX,"Hide Completed",0,2};
__root const int HIDE_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox8[2]={"No","Yes"};

__root const CFG_HDR cfghdr78={CFG_CBOX,"Show only next app. in day",0,2};
__root const int APP_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox78[2]={"No","Yes"};

__root const CFG_HDR cfghdr79 = {CFG_UINT, "for benlux add-on", 0, 10};
__root const unsigned int luki = 2;


