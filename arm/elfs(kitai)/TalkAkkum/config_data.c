#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif 

__root const CFG_HDR cfghdr0={CFG_CBOX,"Озв. пром-е уровни зарядки",0,2};
__root const int say_levels_up=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Нет","Да"};

__root const CFG_HDR cfghdr3={CFG_CBOX,"Озв. пром-е уровни разрядки",0,2};
__root const int say_levels_down=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Нет","Да"};

__root const CFG_HDR cfghdr4={CFG_UINT,"если уровень менее, %",0,90};
__root const unsigned int begin_from=20;

//---------------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Настройки звука",1,0};

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Путь к звукам",0,127};
__root const char folder_path[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TalkAkkum\\";

__root const CFG_HDR cfghdr1={CFG_UINT,"Громкость",0,6};
__root const unsigned int volume=6;

//__root const CFG_HDR cfghdr14 = {CFG_UINT, "Доп. пауза (тиков)", 0, 100};
//__root const unsigned int dop_delay = 50; 

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Предупр. о низкой темп. аккум-ра",1,0};

__root const CFG_HDR cfghdr5={CFG_CBOX,"Сообщать о низкой темп. аккум-ра",0,2};
__root const int warn_temp=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Нет","Да"};

__root const CFG_HDR cfghdr6 = {CFG_UINT, "при значении менее, °C", 0, 50};
__root const unsigned int warn_temp_value = 5;

__root const CFG_HDR cfghdr7 = {CFG_UINT, "Кол-во вибраций", 0, 100};
__root const unsigned int vibra_count = 5;

__root const CFG_HDR cfghdr8 = {CFG_UINT, "Мощность вибраций", 0, 100};
__root const unsigned int vibra_power = 50;

__root const CFG_HDR cfghdr9 = {CFG_UINT, "Интервал повтор. предупр., сек", 0, 1000};
__root const unsigned int warn_interr = 10;

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Настройки времени работы",1,0};

__root const CFG_HDR cfghdr10={CFG_TIME,"Начиная с",0,0};
__root const TTime TimeFrom={8,0};

__root const CFG_HDR cfghdr11={CFG_TIME,"Заканчивая",0,0};
__root const TTime TimeTo={22,0};

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_41={CFG_LEVEL,"Настройки отображения иконки",1,0};

__root const CFG_HDR cfghdr12={CFG_CBOX,"Показывать иконку",0,2};
__root const int show_icon=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"Нет","Да"};

__root const CFG_HDR cfghdr13={CFG_COORDINATES,"Позиция иконки",0,0};
__root const unsigned int cfgX=0;
__root const unsigned int cfgY=55; 

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
//---------------------------------------------------------------------------------------
