#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0= {CFG_UINT,"Вкладка",1,20};
__root const int POS = 2;

__root const CFG_HDR cfghdr0_1={CFG_STR_UTF8,"Включи gprs",0,127};
__root const char ERR1[128]="Enable gprs!";

__root const CFG_HDR cfghdr0_2={CFG_STR_UTF8,"Запусти gprsd!!!!",0,127};
__root const char ERR2[128]="Launch Gprs.elf!!!";

__root const CFG_HDR cfghdr11= {CFG_LEVEL,"Весь трафик",1,0};

__root const CFG_HDR cfghdr1= {CFG_CBOX,"Выводить?",0,2};
__root const int ENA_NET = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2] = {"Нет", "Да"};



__root const CFG_HDR cfghdr2= {CFG_RECT,"Позиция",0,0};
__root const RECT RC = {149,1,239,30};

__root const CFG_HDR cfghdr3= {CFG_UINT,"Шрифт",0,25};
__root const unsigned int FONT = 9;


__root const CFG_HDR cfghdr4= {CFG_CBOX, "Формат", 1, 3};
__root const  int ALIGN = 2;
__root const CFG_CBOX_ITEM cfgcbox4[3] = {"TEXT_ALIGNLEFT", "TEXT_ALIGNMIDDLE","TEXT_ALIGNRIGHT"};

__root const CFG_HDR cfghdr5={CFG_COLOR,"Цвет",0,255};
__root const char COLOR[4]={21,21,21,21};

__root const CFG_HDR cfghdr6= {CFG_CBOX, "Формат", 0, 2};
__root const  int SZ = 0;
__root const CFG_CBOX_ITEM cfgcbox6[2] = {"кб", "мб"};

__root const CFG_HDR cfghdr7={CFG_STR_UTF8,"Формат",0,127};
__root const char FORMAT[128]="All Traf %d kb";

__root const CFG_HDR cfghdr10= {CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr21= {CFG_LEVEL,"За сессию",1,0};

__root const CFG_HDR cfghdr7_1= {CFG_CBOX,"Выводить?",0,2};
__root const int ENA_PROV = 0;
__root const CFG_CBOX_ITEM cfgcbox7_1[2] = {"Нет", "Да"};


__root const CFG_HDR cfghdr8= {CFG_RECT,"Позиция",0,0};
__root const RECT RC2 = {149,1,239,30};

__root const CFG_HDR cfghdr9= {CFG_UINT,"Шрифт",0,25};
__root const unsigned int FONT2 = 9;


__root const CFG_HDR cfghdr12= {CFG_CBOX, "Формат", 1, 3};
__root const  int ALIGN2 = 2;
__root const CFG_CBOX_ITEM cfgcbox9[3] = {"TEXT_ALIGNLEFT", "TEXT_ALIGNMIDDLE","TEXT_ALIGNRIGHT"};

__root const CFG_HDR cfghdr13={CFG_COLOR,"Цвет",0,255};
__root const char COLOR2[4]={21,21,21,21};

__root const CFG_HDR cfghdr14= {CFG_CBOX, "Формат", 0, 2};
__root const  int SZ2 = 0;
__root const CFG_CBOX_ITEM cfgcbox14[2] = {"кб", "мб"};

__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"Формат",0,127};
__root const char FORMAT2[128]="Session Traf %d kb";



__root const CFG_HDR cfghdr20= {CFG_LEVEL,"",0,0};
