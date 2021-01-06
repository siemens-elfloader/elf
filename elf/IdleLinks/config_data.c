#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_UINT,"Клавиша вызова",0,100};
__root const unsigned int CALL_BTN=RIGHT_SOFT;

__root const CFG_HDR cfghdr10={CFG_UINT,"Клавиша закрытия",0,100};
__root const unsigned int CLOSE_BTN=RIGHT_SOFT;

__root const CFG_HDR cfghdr1_1={CFG_CHECKBOX,"Активен",0,2};
__root const int active=1;

__root const CFG_HDR cfghdr222={CFG_CBOX,"Выводить на экран при",0,3};
__root const unsigned int KBD_STATE=1;
__root const CFG_CBOX_ITEM cfgcbox33[3]={"Забл. клав.","Разбл. клав.", "Всегда"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Кол-во ярлычков",0,15};
__root const int count=0;
__root const CFG_CBOX_ITEM cfgcbox2[15]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};

////////////
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Ярлык 1",1,0};

__root const CFG_HDR cfghdr11_1={CFG_CBOX,"Тип",0,3};
__root const int type1=2;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"файл","шорткат","адрес"};


__root const CFG_HDR cfghdr2_1={CFG_STR_UTF8,"Иконка 1",0,127};
__root const char pic1[128]="1246";

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"Файл 1/шорткат/aдрес",0,127};
__root const char file1[128]="A063B07B";

__root const CFG_HDR cfghdr2_3={7,"Координаты 1",0,0};
__root const unsigned int x1=110;
__root const unsigned int y1=295;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};
/////////////////

__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"Ярлык 2",1,0};

__root const CFG_HDR cfghdr12_1={CFG_CBOX,"Тип",0,3};
__root const int type2=0;
__root const CFG_CBOX_ITEM cfgcbox5[3]={"файл","шорткат","адрес"};


__root const CFG_HDR cfghdr3_1={CFG_STR_UTF8,"Иконка 2",0,127};
__root const char pic2[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\tc.png";

__root const CFG_HDR cfghdr3_2={CFG_STR_UTF8,"Файл 2/шорткат/aдрес",0,127};
__root const char file2[128]=DEFAULT_DISK ":\\ZBin\\screensavers\\screensaver.elf";

__root const CFG_HDR cfghdr3_3={7,"Координаты 2",0,0};
__root const unsigned int x2=21;
__root const unsigned int y2=60;

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};
///////////////////
__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"Ярлык 3",1,0};

__root const CFG_HDR cfghdr13_1={CFG_CBOX,"Тип",0,3};
__root const int type3=0;
__root const CFG_CBOX_ITEM cfgcbox6[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr4_1={CFG_STR_UTF8,"Иконка 3",0,127};
__root const char pic3[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\ms.png";

__root const CFG_HDR cfghdr4_2={CFG_STR_UTF8,"Файл 3/шорткат/aдрес",0,127};
__root const char file3[128]=DEFAULT_DISK ":\\ZBin\\MyStuff\\Stuff.elf";

__root const CFG_HDR cfghdr4_3={7,"Координаты 3",0,0};
__root const unsigned int x3=41;
__root const unsigned int y3=60;

__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"",0,0};
////////////////
__root const CFG_HDR cfghdr_m18={CFG_LEVEL,"Ярлык 4",1,0};

__root const CFG_HDR cfghdr14_1={CFG_CBOX,"Тип",0,3};
__root const int type4=0;
__root const CFG_CBOX_ITEM cfgcbox7[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr5_1={CFG_STR_UTF8,"Иконка 4",0,127};
__root const char pic4[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\sj.png";

__root const CFG_HDR cfghdr5_2={CFG_STR_UTF8,"Файл 4/шорткат/aдрес",0,127};
__root const char file4[128]=DEFAULT_DISK ":\\ZBin\\SieJC\\SieJC.elf";

__root const CFG_HDR cfghdr5_3={7,"Координаты 4",0,0};
__root const unsigned int x4=61;
__root const unsigned int y4=60;

__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"Ярлык 5",1,0};

__root const CFG_HDR cfghdr15_1={CFG_CBOX,"Тип",0,3};
__root const int type5=1;
__root const CFG_CBOX_ITEM cfgcbox8[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr6_1={CFG_STR_UTF8,"Иконка 5",0,127};
__root const char pic5[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\ir.png";

__root const CFG_HDR cfghdr6_2={CFG_STR_UTF8,"Файл 5/шорткат/aдрес",0,127};
__root const char file5[128]="STUP_CONCT_IRDA";

__root const CFG_HDR cfghdr6_3={7,"Координаты 5",0,0};
__root const unsigned int x5=81;
__root const unsigned int y5=60;

__root const CFG_HDR cfghdr_m19={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m22={CFG_LEVEL,"Ярлык 6",1,0};


__root const CFG_HDR cfghdr16_1={CFG_CBOX,"Тип",0,3};
__root const int type6=1;
__root const CFG_CBOX_ITEM cfgcbox9[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr7_1={CFG_STR_UTF8,"Иконка 6",0,127};
__root const char pic6[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr7_2={CFG_STR_UTF8,"Файл 6/шорткат/aдрес",0,127};
__root const char file6[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr7_3={7,"Координаты 6",0,0};
__root const unsigned int x6=1;
__root const unsigned int y6=80;

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};
/////////
__root const CFG_HDR cfghdr_m26={CFG_LEVEL,"Ярлык 7",1,0};


__root const CFG_HDR cfghdr17_1={CFG_CBOX,"Тип",0,3};
__root const int type7=1;
__root const CFG_CBOX_ITEM cfgcbox10[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr8_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic7[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr8_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file7[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr8_3={7,"Координаты ",0,0};
__root const unsigned int x7=21;
__root const unsigned int y7=80;

__root const CFG_HDR cfghdr_m25={CFG_LEVEL,"",0,0};

/////////////
__root const CFG_HDR cfghdr_m28={CFG_LEVEL,"Ярлык 8",1,0};


__root const CFG_HDR cfghdr18_1={CFG_CBOX,"Тип",0,3};
__root const int type8=1;
__root const CFG_CBOX_ITEM cfgcbox11[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr9_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic8[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr9_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file8[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr9_3={7,"Координаты ",0,0};
__root const unsigned int x8=41;
__root const unsigned int y8=80;

__root const CFG_HDR cfghdr_m27={CFG_LEVEL,"",0,0};

/////////
__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"Ярлык 9",1,0};


__root const CFG_HDR cfghdr19_1={CFG_CBOX,"Тип",0,3};
__root const int type9=1;
__root const CFG_CBOX_ITEM cfgcbox12[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr10_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic9[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr10_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file9[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr10_3={7,"Координаты ",0,0};
__root const unsigned int x9=61;
__root const unsigned int y9=80;

__root const CFG_HDR cfghdr_m29={CFG_LEVEL,"",0,0};


///////
__root const CFG_HDR cfghdr_m32={CFG_LEVEL,"Ярлык 10",1,0};


__root const CFG_HDR cfghdr20_1={CFG_CBOX,"Тип",0,3};
__root const int type10=1;
__root const CFG_CBOX_ITEM cfgcbox13[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr21_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic10[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr21_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file10[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr21_3={7,"Координаты ",0,0};
__root const unsigned int x10=81;
__root const unsigned int y10=80;

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"",0,0};
////////

__root const CFG_HDR cfghdr_m34={CFG_LEVEL,"Ярлык 11",1,0};


__root const CFG_HDR cfghdr22_5={CFG_CBOX,"Тип",0,3};
__root const int type11=1;
__root const CFG_CBOX_ITEM cfgcbox14[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr22_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic11[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr22_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file11[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr22_3={7,"Координаты ",0,0};
__root const unsigned int x11=1;
__root const unsigned int y11=100;

__root const CFG_HDR cfghdr_m33={CFG_LEVEL,"",0,0};

////////
__root const CFG_HDR cfghdr_m36={CFG_LEVEL,"Ярлык 12",1,0};


__root const CFG_HDR cfghdr23_5={CFG_CBOX,"Тип",0,3};
__root const int type12=1;
__root const CFG_CBOX_ITEM cfgcbox15[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr23_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic12[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr23_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file12[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr23_3={7,"Координаты ",0,0};
__root const unsigned int x12=21;
__root const unsigned int y12=100;

__root const CFG_HDR cfghdr_m35={CFG_LEVEL,"",0,0};
////////
__root const CFG_HDR cfghdr_m38={CFG_LEVEL,"Ярлык 13",1,0};


__root const CFG_HDR cfghdr24_5={CFG_CBOX,"Тип",0,3};
__root const int type13=1;
__root const CFG_CBOX_ITEM cfgcbox16[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr24_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic13[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr24_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file13[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr24_3={7,"Координаты ",0,0};
__root const unsigned int x13=41;
__root const unsigned int y13=100;

__root const CFG_HDR cfghdr_m37={CFG_LEVEL,"",0,0};

///////
__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"Ярлык 14",1,0};


__root const CFG_HDR cfghdr25_5={CFG_CBOX,"Тип",0,3};
__root const int type14=1;
__root const CFG_CBOX_ITEM cfgcbox17[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr25_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic14[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr25_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file14[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr25_3={7,"Координаты ",0,0};
__root const unsigned int x14=61;
__root const unsigned int y14=100;

__root const CFG_HDR cfghdr_m39={CFG_LEVEL,"",0,0};
///////////
__root const CFG_HDR cfghdr_m42={CFG_LEVEL,"Ярлык 15",1,0};


__root const CFG_HDR cfghdr26_5={CFG_CBOX,"Тип",0,3};
__root const int type15=1;
__root const CFG_CBOX_ITEM cfgcbox18[3]={"файл","шорткат","адрес"};

__root const CFG_HDR cfghdr26_1={CFG_STR_UTF8,"Иконка",0,127};
__root const char pic15[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr26_2={CFG_STR_UTF8,"Файл/шорткат/aдрес",0,127};
__root const char file15[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr26_3={7,"Координаты ",0,0};
__root const unsigned int x15=81;
__root const unsigned int y15=100;

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"",0,0};

/////
__root const CFG_HDR cfghdr_m24={CFG_LEVEL,"Настройка выбора",1,0};
__root const CFG_HDR cfghdr8={CFG_CBOX,"Выбор",0,2};
__root const int vybor=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Цветом","Картинкой"};

__root const CFG_HDR cfghdr51={CFG_STR_UTF8,"Картинка выбора",0,127};
__root const char chpic[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\choose.png";

__root const CFG_HDR cfghdr121={8,"Цвет выбора",0,0};
__root const char cl[4]={185,113,13,50};

__root const CFG_HDR cfghdr122={8,"Цвет рамки",0,0};
__root const char frcol[4]={255,255,255,100};

__root const CFG_HDR cfghdr_m23={CFG_LEVEL,"",0,0};





/////
  /*
  0-Left_SOFT
  1-Right_soft
  2-up
  3-down
  4-left
  5-right
  6-vol up
  7-vol down
  */
