#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_UINT,"time update (sec)",0,0xFFFFFFFF};
__root const unsigned int TID=60;

__root const CFG_HDR cfghdr3={CFG_UINT,"run key(long press)",0,65535};
__root const unsigned int CALL_BUTTON=1;

__root const CFG_HDR cfghdr9={CFG_UINT,"missed event key(short press)",0,65535};
__root const unsigned int CALL_BUTTON2=13;

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "Шрифт заголовка", 0, 23};
__root const unsigned int font1 = 12;

__root const CFG_HDR cfghdr2_5 = {CFG_UINT, "Шрифт информации", 0, 23};
__root const unsigned int font2 = 11;

__root const CFG_HDR cfghdr10={CFG_COLOR,"цвет заголовка",0,0};
__root const char COLORfont1[4]={0xFF,0x00,0x00,0x64};

__root const CFG_HDR cfghdr11={CFG_COLOR,"цвет информации",0,0};
__root const char COLORfont2[4]={0x00,0xFF,0x00,0x64};

__root const CFG_HDR cfghdr4_4={CFG_CBOX,"use naticq plugin",0,2};
__root const int use_plugin = 0;
__root const CFG_CBOX_ITEM cfgcbox4_4[2]={"No","Yes"};

__root const CFG_HDR cfghdr4_6={CFG_CBOX,"auto missed",0,2};
__root const int engade_mis = 0;
__root const CFG_CBOX_ITEM cfgcbox4_6[2]={"No","Yes"};

__root const CFG_HDR cfghdr7 = {CFG_STR_WIN1251, "link1 name", 0, 63};
__root const char link1_name[64] = "Naticq";

__root const CFG_HDR cfghdr2 = {CFG_STR_WIN1251, "link1 path", 0, 63};
__root const char link1[64] = "0:\\zbin\\naticq\\naticq.elf";

__root const CFG_HDR cfghdr8 = {CFG_STR_WIN1251, "link2 name", 0, 63};
__root const char link2_name[64] = "Ballet";

__root const CFG_HDR cfghdr4 = {CFG_STR_WIN1251, "link2 path", 0, 63};
__root const char link2[64] = "0:\\Zbin\\balletmini\\BalletMini.elf";

__root const CFG_HDR cfghdr5 = {CFG_STR_WIN1251, "link3 name", 0, 63};
__root const char link3_name[64] = "SieJC";

__root const CFG_HDR cfghdr6 = {CFG_STR_WIN1251, "link3 path", 0, 63};
__root const char link3[64] = "0:\\Zbin\\siejc\\siejc.elf";


__root const CFG_HDR cfghdr31 = {CFG_STR_WIN1251, "Sound path", 0, 63};
__root const char linksound[64] = "0:\\zbin\\miosd\\s1.mp3";
