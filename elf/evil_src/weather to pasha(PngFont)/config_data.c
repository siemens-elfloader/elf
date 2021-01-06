#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Show copyright text at startup",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr3 = {CFG_UINT, "Время обновления(min)", 0, 120};
__root const unsigned int refresh = 60;

__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"температурa",1,0};

__root const CFG_HDR cfghdr4={CFG_CBOX,"Показывать температуру",0,2};
__root const int show_temp=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr5 = {CFG_COORDINATES,"позиц. темп.",0,0};
__root const unsigned int date_X = 0;
__root const unsigned int date_Y = 40;

__root const CFG_HDR cfghdr6={CFG_STR_WIN1251,"темп. текст",0,127};
__root const char str[128]="темп: ";

__root const CFG_HDR cfghdr40={CFG_CBOX,"где показать инфу",0,3};
__root const int chekeris1=1;
__root const CFG_CBOX_ITEM cfgcbox10[3]={"everywhere","unlocked","locked"};

__root const CFG_HDR cfghdr22_1 = {CFG_CBOX, "Align", 0, 3};
__root const int align1 = 0;
__root const CFG_CBOX_ITEM cfgcbox6_1[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"скорость ветра",1,0};

__root const CFG_HDR cfghdr7={CFG_CBOX,"Показывать скорость ветра",0,2};
__root const int show_speed=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};

__root const CFG_HDR cfghdr15 = {CFG_COORDINATES,"позиц. скорость",0,0};
__root const unsigned int date_X2 = 0;
__root const unsigned int date_Y2 = 50;

__root const CFG_HDR cfghdr41={CFG_CBOX,"где показать инфу",0,3};
__root const int chekeris2=1;
__root const CFG_CBOX_ITEM cfgcbox11[3]={"everywhere","unlocked","locked"};

__root const CFG_HDR cfghdr22_2 = {CFG_CBOX, "Align", 0, 3};
__root const int align2 = 0;
__root const CFG_CBOX_ITEM cfgcbox6_2[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"погода",1,0};

__root const CFG_HDR cfghdr8={CFG_CBOX,"Показывать погоду",0,2};
__root const int show_prognoze=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"No","Yes"};

__root const CFG_HDR cfghdr9 = {CFG_COORDINATES,"позиц. погоды",0,0};
__root const unsigned int date_X3 = 0;
__root const unsigned int date_Y3 = 60;

__root const CFG_HDR cfghdr43={CFG_CBOX,"где показать инфу",0,3};
__root const int chekeris3=1;
__root const CFG_CBOX_ITEM cfgcbox13[3]={"everywhere","unlocked","locked"};

__root const CFG_HDR cfghdr22_3 = {CFG_CBOX, "Align", 0, 3};
__root const int align3 = 0;
__root const CFG_CBOX_ITEM cfgcbox6_3[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"давление",1,0};

__root const CFG_HDR cfghdr10={CFG_CBOX,"Показывать давление",0,2};
__root const int show_otrais=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"No","Yes"};

__root const CFG_HDR cfghdr11 = {CFG_COORDINATES,"Позиц. давление",0,0};
__root const unsigned int date_X4 = 0;
__root const unsigned int date_Y4 = 70;

__root const CFG_HDR cfghdr16={CFG_STR_WIN1251,"Давления текст",0,127};
__root const char otrajam[128]="давление: ";

__root const CFG_HDR cfghdr44={CFG_CBOX,"где показать инфу",0,3};
__root const int chekeris4=1;
__root const CFG_CBOX_ITEM cfgcbox14[3]={"everywhere","unlocked","locked"};

__root const CFG_HDR cfghdr22_4 = {CFG_CBOX, "Align", 0, 3};
__root const int align4 = 0;
__root const CFG_CBOX_ITEM cfgcbox6_4[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"влажность",1,0};

__root const CFG_HDR cfghdr12={CFG_CBOX,"Показывать влажность",0,2};
__root const int show_treshais=1;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"No","Yes"};

__root const CFG_HDR cfghdr13 = {CFG_COORDINATES,"Позиц. влажность",0,0};
__root const unsigned int date_X5 = 0;
__root const unsigned int date_Y5 = 80;

__root const CFG_HDR cfghdr17={CFG_STR_WIN1251,"Влажность текст",0,127};
__root const char treshajam[128]="влажность: ";

__root const CFG_HDR cfghdr45={CFG_CBOX,"где показать инфу",0,3};
__root const int chekeris5=1;
__root const CFG_CBOX_ITEM cfgcbox15[3]={"everywhere","unlocked","locked"};

__root const CFG_HDR cfghdr22_5 = {CFG_CBOX, "Align", 0, 3};
__root const int align5 = 0;
__root const CFG_CBOX_ITEM cfgcbox6_5[3] = {"Left", "Center", "Right"};

__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr14={CFG_STR_UTF8,"ид город",0,63};
__root const char pilseeta[64]="3887";

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"img",1,0};

__root const CFG_HDR cfghdr20={CFG_STR_UTF8,"img path",0,63};
__root const char weather_img_path[64]="4:\\zbin\\mailweather\\";

__root const CFG_HDR cfghdr21 = {CFG_COORDINATES,"img pos",0,0};
__root const unsigned int weather_X = 0;
__root const unsigned int weather_Y = 90;

__root const CFG_HDR cfghdr22={CFG_CBOX,"show img",0,2};
__root const int IKONA=0;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"font",1,0};

__root const CFG_HDR cfghdr23 = {CFG_STR_UTF8, "png font path", 0, 63};
__root const char fontpath[64] = "4:\\";

__root const CFG_HDR cfghdr28={CFG_CBOX,"full font mode",0,2};
__root const int fullfont=0;
__root const CFG_CBOX_ITEM cfgcbox7[2]={"No","Yes"};

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, "Pixels between letters", 0, 10};
__root const unsigned int space = 1;

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"sound",1,0};

__root const CFG_HDR cfghdr1_1 = {CFG_STR_UTF8, "sound path", 0, 63};
__root const char soundpath[64] = "4:\\zbin\\mailweather\\wav\\";

__root const CFG_HDR cfghdr1_2 = {CFG_CBOX, "Enable talk", 0, 2};
__root const int ENA_TALK = 0;
__root const CFG_CBOX_ITEM cfgcbox19[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr1_6 = {CFG_UINT, "Volume", 0, 10};
__root const unsigned int sndVolume = 6;

__root const CFG_HDR cfghdr1_3 = {CFG_UINT, "Morning time", 0, 23};
__root const unsigned int minimum = 0;

__root const CFG_HDR cfghdr1_4 = {CFG_UINT, "Evening time", 0, 23};
__root const unsigned int maximum = 23;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};
