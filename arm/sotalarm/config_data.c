#include "Z:\home\kostett\IAR\ARM\INC\cfg_items.h"
#include "Z:\home\kostett\IAR\ARM\INC\swilib.h"
//Конфигурация

__root const CFG_HDR cfghdr00={CFG_CBOX,"Сообщение приветствия",0,2};
__root const int BCFG_HELLOMSG=1;
__root const CFG_CBOX_ITEM cfgcbox01[2]={"Выключено","Включено"};

__root const CFG_HDR cfghdr1_rfr1={CFG_UINT,"Таймер проверки (сек)",0,65535};
__root const unsigned int BCFG_REFRESHTIME=30;

__root const CFG_HDR cfghdr2234={CFG_LEVEL,"Кнопки",1,0};

__root const CFG_HDR cfghdr0_1={CFG_KEYCODE,"Клавиша включения слежения",0,100};
__root const unsigned int BCFG_ON_BTN=RIGHT_SOFT;
  
__root const CFG_HDR cfghdr100500={CFG_CBOX,"Тип нажатия этой клавиши",0,2};
__root const unsigned int BCFG_KEYON_TYPE = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Краткое нажатие","Удержание"};

__root const CFG_HDR cfghdr_msgstart105005={CFG_CHECKBOX,"Включить сообщение",0,1};
__root const int BCFG_ON_MSG_ENA=1;

__root const CFG_HDR cfghdr0_3={CFG_KEYCODE,"Кнопка выключения слежения",0,100};
__root const unsigned int BCFG_OFF_BTN=LEFT_SOFT;

__root const CFG_HDR cfghdr0_2={CFG_CBOX,"Тип нажатия этой клавиши",0,2};
__root const unsigned int BCFG_KEYOFF_TYPE = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Краткое нажатие","Удержание"};

__root const CFG_HDR cfghdr_msgstart1050={CFG_CHECKBOX,"Включить сообщение",0,1};
__root const int BCFG_OFF_MSG_ENA=1;

__root const CFG_HDR cfghdr2234433={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr2223434={CFG_LEVEL,"Сеть",1,0};

__root const CFG_HDR cfghdr_msgs1af005={CFG_CHECKBOX,"Реагировать на БС #1",0,1};
__root const int BCFG_ENA_1ST_NET=1;

__root const CFG_HDR cfghdr1_98eri={CFG_UINT,"LAC #1",0,65535};
__root const unsigned int BCFG_LAC=35400;

__root const CFG_HDR cfghdr1_rgrsdf={CFG_UINT,"CI #1",0,65535};
__root const unsigned int BCFG_CI=1571;

__root const CFG_HDR cfghdr_mstart1af005={CFG_CHECKBOX,"Реагировать на БС #2",0,1};
__root const int BCFG_ENA_2ND_NET=1;

__root const CFG_HDR cfghdr1_98wei={CFG_UINT,"LAC #2",0,65535};
__root const unsigned int BCFG_LAC2=35400;

__root const CFG_HDR cfghdr1_rfdf={CFG_UINT,"CI #2",0,65535};
__root const unsigned int BCFG_CI2=1574;

__root const CFG_HDR cfghdr_msstartaf005={CFG_CHECKBOX,"Реагировать на БС #3",0,1};
__root const int BCFG_ENA_3RD_NET=0;

__root const CFG_HDR cfghdr1_9wei={CFG_UINT,"LAC #3",0,65535};
__root const unsigned int BCFG_LAC3=35400;

__root const CFG_HDR cfghdr1_r56frsdf={CFG_UINT,"CI #3",0,65535};
__root const unsigned int BCFG_CI3=1571;

__root const CFG_HDR cfghdr_ms5tart1af005={CFG_CHECKBOX,"Реагировать на БС #4",0,1};
__root const int BCFG_ENA_4TH_NET=0;

__root const CFG_HDR cfghdr1_9867ri={CFG_UINT,"LAC #4",0,65535};
__root const unsigned int BCFG_LAC4=35400;

__root const CFG_HDR cfghdr1_rf56rsdf={CFG_UINT,"CI #4",0,65535};
__root const unsigned int BCFG_CI4=1571;

__root const CFG_HDR cfghdr_msgs56art1af005={CFG_CHECKBOX,"Реагировать на БС #5",0,1};
__root const int BCFG_ENA_5TH_NET=0;

__root const CFG_HDR cfghdr1_98we33i={CFG_UINT,"LAC #5",0,65535};
__root const unsigned int BCFG_LAC5=35400;

__root const CFG_HDR cfghdr1_rfr33f={CFG_UINT,"CI #5",0,65535};
__root const unsigned int BCFG_CI5=1571;

//__root const CFG_HDR cfghdr1_rfrsf={CFG_UINT,"TA",0,65535};
//__root const unsigned int BCFG_TA=1;
//
__root const CFG_HDR cfghdr2234243={CFG_LEVEL,"",0,0};

__root const CFG_HDR chjdsgfyenb={CFG_LEVEL,"Сигнализация",1,0};

#ifndef NEWSGOLD

__root const CFG_HDR cfghdfhfdjsu={CFG_CBOX,"Тип сигнализации",0,3};
__root const int BCFG_TYPE=0;
__root const CFG_CBOX_ITEM cfgcbox100500[3]={"Не оповещать","Пуск файла","Стандартный будильник"};

#else

__root const CFG_HDR cfghdfhfdjsu={CFG_CBOX,"Тип сигнализации",0,2};
__root const int BCFG_TYPE=0;
__root const CFG_CBOX_ITEM cfgcbox100500[2]={"Не оповещать","Пуск файла"};

#endif

__root const CFG_HDR asdacfghdr_msgstart105005={CFG_CHECKBOX,"Popup при нахождении",0,1};
__root const int BCFG_FOUND_MSG_ENA=1;

__root const CFG_HDR cfghdfgfdr2_1={CFG_STR_UTF8,"Файл для запуска",0,127};
__root const char BCFG_START_FILE[128]="0:\\ZBin\\Utilites\\alarm2_ring.elf";

__root const CFG_HDR cfghdr223424sad3={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfgh34={CFG_LEVEL,"Отображение в XTask",1,0};

__root const CFG_HDR cfghdr1_rf={CFG_COLOR,"Цвет в XTask'е при активности",0,65535};
__root const unsigned char BCFG_TSKNAME_COLOR_ON[4]={0,255,0,100};

__root const CFG_HDR cfghdr1_rf234={CFG_COLOR,"Цвет в XTask'е при неактивности",0,65535};
__root const unsigned char BCFG_TSKNAME_COLOR_OFF[4]={255,0,0,100};

__root const CFG_HDR cfghdr1_rff={CFG_STR_WIN1251,"Имя в XTask'е",0,63};
__root const char BCFG_TSKNAME_NAME[64]="sotalarm";

__root const CFG_HDR cfghd34={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_msgstart105fsdf005={CFG_CHECKBOX,"Дебаг в консоль",0,1};
__root const int BCFG_DEBUG_ENA=0;
