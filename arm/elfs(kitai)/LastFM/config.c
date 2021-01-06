#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

//Координаты
__root const CFG_HDR cfghdr0 = {CFG_RECT, "Tags Area", 0, 0};
__root const RECT cfgArea = {0,67,131,93};

//Выравнивание
__root const CFG_HDR cfghdr1 = {CFG_CBOX,"Tags Text Alignment",0,3};
__root const int cfgAlign = 1;
__root const CFG_CBOX_ITEM cfgcbox0[3]={"Left","Center","Right"};

__root const CFG_HDR cfghdr4 = {CFG_STR_WIN1251,"Mediaplayer CSM addr",1,8};
__root const char CSMADR[9]="A068A8D4";

__root const CFG_HDR cfghdr5 = {CFG_STR_UTF8,"Temp file",0,127};
__root const char TEMP_FILE[128]="4:\\ZBin\\Var\\LastFMcache.tmp";

__root const CFG_HDR cfghdr6 = {CFG_CBOX,"TimeZone sign",0,2};
__root const int TIMEZONESIGN = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"-","+"};

__root const CFG_HDR cfghdr7 = {CFG_UINT, "TimeZone value", 0, 12};
__root const unsigned int TIMEZONE = 2;

__root const CFG_HDR cfghdr8={CFG_UTF8_STRING,"Username",0,31};
__root const char USERNAME[32]="";

__root const CFG_HDR cfghdr9={CFG_STR_PASS,"Password",0,31};
__root const char PASSWORD[32]="";
