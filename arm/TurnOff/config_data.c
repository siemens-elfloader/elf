#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif 

__root const CFG_HDR cfghdr0={CFG_UINT,"Close button",0,65535};
__root const unsigned int CLOSE_BTN=RIGHT_SOFT;

#ifdef DAEMON
__root const CFG_HDR cfghdr1={CFG_UINT,"Call button",0,65535};
__root const unsigned int CALL_BTN=RED_BUTTON;

__root const CFG_HDR cfghdr2={CFG_CBOX,"Режим нажатия клавиш",0,3};
__root const int MODE_KBD=0;
__root const CFG_CBOX_ITEM cfgcbox1[3]={"KEY_DOWN","KEY_UP","LONG_PRESS"};
#endif

__root const CFG_HDR cfghdr3={CFG_CBOX,"Действие по умолчанию",0,3};
__root const int MODE=1;
__root const CFG_CBOX_ITEM cfgcbox2[3]={"Ждущий режим","Выключение","Перезагрузка"};

__root const CFG_HDR cfghdr4={CFG_CBOX,"Ждущий режим",0,2};
__root const int WHAT_DO=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Профиль","Блок. клав."};

__root const CFG_HDR cfghdr5={CFG_UINT,"Профиль",1,9};
__root const unsigned int PROFILE=8;

__root const CFG_HDR cfghdr_m1_1={CFG_LEVEL,"Настройки иконок",1,0};

__root const CFG_HDR cfghdr1_0={CFG_STR_UTF8,"Икаонка выключения",0,127};
__root const char ICONS_SD[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\off.png";

__root const CFG_HDR cfghdr1_1={CFG_STR_UTF8,"Икаонка перезагрузки",0,127};
__root const char ICONS_RB[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\reboot.png";

__root const CFG_HDR cfghdr1_2={CFG_STR_UTF8,"Иконка жд. режима",0,127};
__root const char ICONS_SR[128]=DEFAULT_DISK ":\\ZBin\\img\\TurnOff\\sleep.png";

__root const CFG_HDR cfghdr_m1_0={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m2_1={CFG_LEVEL,"Настройки звуков",1,0};

__root const CFG_HDR cfghdr2_0={CFG_CBOX,"Звуки",0,2};
__root const int SND_ENA=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2_1={CFG_UINT,"Громкость",0,6};
__root const unsigned int VOLUME=1;

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"Звук выключения",0,127};
__root const char SND_SD[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TurnOff\\off.wav";

__root const CFG_HDR cfghdr2_3={CFG_STR_UTF8,"Звук перезагрузки",0,127};
__root const char SND_RB[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TurnOff\\reboot.wav";

__root const CFG_HDR cfghdr2_4={CFG_STR_UTF8,"Звук жд. режима",0,127};
__root const char SND_SR[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TurnOff\\sleep.wav";

__root const CFG_HDR cfghdr_m2_0={CFG_LEVEL,"",0,0};
