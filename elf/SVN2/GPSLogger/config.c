#include "..\inc\cfg_items.h"

// Флаг необходимости сброса кеша
__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Clear cache on settings update",0,2};
__root const int Req_Clear_Cache=0;

// Флаг записи неизвестных сот
__root const CFG_HDR cfghdr1={CFG_CHECKBOX,"Log unknown cells",0,2};
__root const int LOG_UNKNOWN_CELLS=0;


////////////////////////////////////////////////////////////////////////////////
__root const CFG_HDR cfghdr_TEXT_CFG_LEVEL_B={CFG_LEVEL,"Display configuration",1,0};

// Когда показывать (лок, нелок, всегда)
__root const CFG_HDR cfghdrt545={CFG_CBOX,"Show in",0,3};
__root const int SHOW_IN = 0;
__root const CFG_CBOX_ITEM cfgcbox2[3]={"Unlock","Lock", "Both"};

//Координаты X, Y вывода надписи
__root const CFG_HDR cfghdrioykh={CFG_COORDINATES,"Text position",0,0};
__root const unsigned int TXT_X=50;
__root const unsigned int TXT_Y=50;

__root const CFG_HDR cfghdr4346={CFG_CBOX,"Text align",0,2};
__root const int CENTER_TEXT = 0;
__root const CFG_CBOX_ITEM cfgcbox1435[2]={"Normal","Centered"};

// Шрифт текста
__root const CFG_HDR cfghdr8o7yo0 = {CFG_UINT, "Font", 0, 11};
#ifdef NEWSGOLD
__root const unsigned int TXT_FONT = 11;
#else
__root const unsigned int TXT_FONT = 8;
#endif

// Цвет текста
__root const CFG_HDR cfghdr5={CFG_COLOR,"Font Color",0,0};
__root const char TXT_COLOR[4]={0xFF,0xFF,0,0x64};

// Атрибуты текста
__root const CFG_HDR cfghdrplkjhl = {CFG_UINT, "Txt attr", 0, 128};
__root const unsigned int TXT_ATTR = 0x20;

// Флаг показа неизвестных сот
__root const CFG_HDR cfghdrere1={CFG_CHECKBOX,"Display unknown cells",0,2};
__root const int DISP_UNKNOWN_CELLS=0;

__root const CFG_HDR cfghdr_TEXT_CFG_LEVEL_E={CFG_LEVEL,"",0,0};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
__root const CFG_HDR cfghdr_ACTIONS_CFG_LEVEL_B={CFG_LEVEL,"Actions configuration",1,0};

// Вибрация
__root const CFG_HDR cfghdr98789={CFG_UINT,"Vibra strength",0,100};
__root const unsigned int VIBRA_POWER=10;

__root const CFG_HDR cfghdr243={CFG_UINT,"Vibra count",1,5};
__root const unsigned int VIBRA_COUNT=1;

__root const CFG_HDR cfghdr_ACTIONS_CFG_LEVEL_E={CFG_LEVEL,"",0,0};
////////////////////////////////////////////////////////////////////////////////


// Размер кеша сот
__root const CFG_HDR cfghdito89 = {CFG_UINT, "Cell cache size", 2, 10};
__root const unsigned int CACHE_SIZE = 10;

// Путь к базе данных
__root const CFG_HDR cfghdr0lkjhlre={CFG_STR_UTF8,"MiniGPS base dir",3,127};
__root const char MGPS_DB[128]="0:\\Misc\\gps";

// Путь к лог-файлу
__root const CFG_HDR cfghdr456re={CFG_STR_UTF8,"Log file path",3,127};
__root const char LOGFILE[128]="0:\\Misc\\gps\\gpslog.txt";

//EOL,EOF
