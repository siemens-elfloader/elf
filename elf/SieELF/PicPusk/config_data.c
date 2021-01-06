#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0 = {CFG_UINT, "Цвет", 0, 23};
__root const unsigned int color = 0;

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Настройки обводки",1,0};

__root const CFG_HDR cfghdr1_1={CFG_CBOX,"Обводка шрифта",0,2};
__root const unsigned int FRINGING_ENA=0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1_2 = {CFG_UINT, "Цвет обводки", 0, 23};
__root const unsigned int FRINGING_color = 22;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Отображение даты",1,0};

__root const CFG_HDR cfghdr2_1={CFG_CBOX,"Показывать дату",0,2};
__root const unsigned int DATE_ENA=0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "Шрифт даты", 0, 23};
__root const unsigned int date_font = 3;

__root const CFG_HDR cfghdr2_3={CFG_COORDINATES,"Позиция даты",0,0};
__root const unsigned int date_X=72;
__root const unsigned int date_Y=140;

__root const CFG_HDR cfghdr2_4={CFG_STR_WIN1251,"Формат строки даты",0,15};
__root const char DATE_FMT[16]="%t %02d %t";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Отображение времени",1,0};

__root const CFG_HDR cfghdr3_1={CFG_CBOX,"Показывать время",0,2};
__root const unsigned int TIME_ENA=0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Нет","Да"};

__root const CFG_HDR cfghdr3_2 = {CFG_UINT, "Шрифт времени", 0, 23};
__root const unsigned int time_font = 1;

__root const CFG_HDR cfghdr8={CFG_COORDINATES,"Позиция времени",0,0};
__root const unsigned int time_X=78;
__root const unsigned int time_Y=154;

__root const CFG_HDR cfghdr3_3={CFG_STR_WIN1251,"Формат строки времени",0,15};
__root const char TIME_FMT[16]="%02d:%02d";

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Отображение кнопки",1,0};

__root const CFG_HDR cfghdr4_1={CFG_CBOX,"Показывать кнопку",0,2};
__root const unsigned int BUT_ENA=0;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"Нет","Да"};

__root const CFG_HDR cfghdr4_2={CFG_COORDINATES,"Позиция кнопки",0,0};
__root const unsigned int but_X=0;
__root const unsigned int but_Y=159;

__root const CFG_HDR cfghdr4_3={CFG_STR_WIN1251,"Путь к иконке",0,127};
__root const char pic_path[128]="0:\\ZBin\\sMenu\\pic\\pusk2.png";

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
