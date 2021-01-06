#include "C:\ARM_ALL\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Вкл. текст приветствия?",0,2};
__root const int ena_msg=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Вкл. сообщение о реконфигурации?",0,2};
__root const int ena_req=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui=0;
__root const CFG_CBOX_ITEM cfgcbox2[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr3={CFG_STR_UTF8,"Путь к шрифту",0,63};
__root const char ICON_PATH[64]="4:\\ZBin\\img\\IconbarClock\\";

__root const CFG_HDR cfghdr4={CFG_CBOX,"Диск для создания картинок",0,2};
__root const int disk=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"0","4"};

__root const CFG_HDR cfghdr5={CFG_UINT,"Номер временной иконки",0,19999};
__root const unsigned int ICON_N=9999;

__root const CFG_HDR cfghdr6={CFG_UINT,"Номер пустой иконки",0,19999};
__root const unsigned int NULL_ICON_N=9998;

