#include "C:\ARM_ALL\inc\cfg_items.h"
//Конфигурация

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_CBOX,"Вкл. текст приветствия?",0,2};
__root const int ena_msg=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Вкл. сообщение о реконфигурации?",0,2};
__root const int ena_req=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2={CFG_UINT,"Время таймера",1,65535};
__root const unsigned int time_timer=1;

__root const CFG_HDR cfghdr3={CFG_CBOX,"Действие по истечению времени?",0,7};
__root const int deistvie_net=4;
__root const CFG_CBOX_ITEM cfgcbox2[7]={"Заблокировать клавиатуру","Проиграть звук","Проиграть звук из прошивки","Переключить профиль","Вывести сообщение","Выключить телефон","Отключить поиск сети"};

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"Путь к звуку",0,127};
__root const char sounds[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\AutoNet\\search_net.wav";

__root const CFG_HDR cfghdr5={CFG_UINT,"Громкость",1,6};
__root const unsigned int sndvolume=4;

__root const CFG_HDR cfghdr6={CFG_UINT,"Звук из прошивки",1,130};
__root const unsigned int pischalka=1;

__root const CFG_HDR cfghdr7={CFG_UINT,"Профиль",1,8};
__root const unsigned int profile=6;


