#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"Каталог",1,127};
__root const char folder[128]="0:\\ZBin\\CallRecorder\\";

__root const CFG_HDR cfghdr1={CFG_CBOX,"Профиль",0,9};
__root const  int profile=0;
__root const CFG_CBOX_ITEM cfgcbox1[]={"Все","1","2","3","4","5","6","7","8"};

__root const CFG_HDR cfghdr2={CFG_CBOX,"Битрейт",0,3};
__root const  int bitrate=2;
__root const CFG_CBOX_ITEM cfgcbox2[]={"4.750","7.400","12.200"};

__root const CFG_HDR cfghdr3={CFG_CBOX,"Amr mode",0,3};
__root const  int amrmode=2;
__root const CFG_CBOX_ITEM cfgcbox3[]={"0","4","7"};

__root const CFG_HDR cfghdr4={CFG_CBOX,"Режим",0,2};
__root const  int opmod=0;
__root const CFG_CBOX_ITEM cfgcbox4[]={"Авто","Кейхук"};

__root const CFG_HDR cfghdr5={CFG_STR_UTF8,"Энтрик(гр. связь)",1,8};
__root const char loud[9]="A06629A5";

__root const CFG_HDR cfghdr6={CFG_CHECKBOX,"вкл. гр. связь?",0,1};
__root const  int ena_loud=1;

__root const CFG_HDR cfghdr7={CFG_STR_UTF8,"Энтрик(микр.)",1,8};
__root const char mic[9]="A06629B1";

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Время ожидания до снятия",1,0};

__root const CFG_HDR cfghdr8={CFG_CHECKBOX,"Снимать?",0,1};
__root const int time_on_on=1;

__root const CFG_HDR cfghdr9={CFG_UINT,"Секунды",0,59};
__root const int time_on_sec=40;

__root const CFG_HDR cfghdr10={CFG_UINT,"Минуты",0,59};
__root const int time_on_min=0;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Время ожидания до сброса",1,0};

__root const CFG_HDR cfghdr11={CFG_CHECKBOX,"Сбрасывать?",0,1};
__root const int time_off_off=1;

__root const CFG_HDR cfghdr12={CFG_UINT,"Секунды",0,59};
__root const int time_off_sec=10;

__root const CFG_HDR cfghdr13={CFG_UINT,"Минуты",0,59};
__root const int time_off_min=0;
//20
__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Кейхук",1,0};

__root const CFG_HDR cfghdr14={CFG_KEYCODE,"Кнопка 1",0,100};
__root const unsigned int Key1='*';

__root const CFG_HDR cfghdr15={CFG_CBOX,"Метод",0,3};
__root const unsigned int Key1Type=2;
__root const CFG_CBOX_ITEM cfgcbox15[]={"Короткое","Длинное","Обе одновременно"};

__root const CFG_HDR cfghdr16={CFG_KEYCODE,"Кнопка 2",0,100};
__root const unsigned int Key2='#';

__root const CFG_HDR cfghdr17={CFG_CBOX,"Метод",0,4};
__root const unsigned int Key2Type=2;
__root const CFG_CBOX_ITEM cfgcbox17[]={"Одинарное","Длинное","Обе одновременно","Не использовать"};

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Номера",1,0};

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
