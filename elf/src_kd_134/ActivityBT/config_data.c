#include "C:\ARM_ALL\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Вкл. текст приветствия?",0,2};
__root const int ena_msg=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Вкл. сообщение о реконфигурации?",0,2};
__root const int ena_req=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2={CFG_CBOX,"Отображать при",0,3};
__root const int show_in=2;
__root const CFG_CBOX_ITEM cfgcbox2[3]={"Блокировке","Разблокировке","Все случаи"};

__root const CFG_HDR cfghdr3={CFG_CBOX,"Тип текста",0,2};
__root const int type_txt=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"DrawString","PNG"};

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Настройки текста",1,0};

__root const CFG_HDR cfghdr1_1={CFG_CBOX,"Отображать текст?",0,2};
__root const int ena_text=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"Нет","Да"};

__root const CFG_HDR cfghdrm1_2={CFG_COORDINATES,"Позиция",0,0};
__root const unsigned int text_x=0;
__root const unsigned int text_y=0;

__root const CFG_HDR cfghdrm1_3={CFG_STR_WIN1251,"Текст выкл. БТ",1,127};
__root const char text_bt_off[128]="БТ выключен";

__root const CFG_HDR cfghdrm1_4={CFG_STR_WIN1251,"Текст вкл. БТ",1,127};
__root const char text_bt_on[128]="БТ включен";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Настройки картинок",1,0};

__root const CFG_HDR cfghdr2_1={CFG_CBOX,"Отображать картинки?",0,2};
__root const int ena_img=1;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2_2={CFG_COORDINATES,"Позиция",0,0};
__root const unsigned int img_x=0;
__root const unsigned int img_y=0;

__root const CFG_HDR cfghdr2_3={CFG_STR_UTF8,"Путь к иконке выкл. БТ",1,127};
__root const char img_bt_off[128]="4:\\ZBin\\img\\ActivityBT\\bt_off.png";

__root const CFG_HDR cfghdr2_4={CFG_STR_UTF8,"Путь к иконке вкл. БТ",1,127};
__root const char img_bt_on[128]="4:\\ZBin\\img\\ActivityBT\\bt_on.png";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Настройки PNG",1,0};

__root const CFG_HDR cfghdr4_1={CFG_STR_UTF8,"Шрифт",1,127};
__root const char fontpatch[128]="4:\\ZBin\\img\\";

__root const CFG_HDR cfghdr4_2={CFG_CBOX,"Использовать полный шрифт",0,2};
__root const int fullfont=0;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"Нет","Да"};

__root const CFG_HDR cfghdr4_3={CFG_CBOX,"Выравнивать по",0,3};
__root const int align=0;
__root const CFG_CBOX_ITEM cfgcbox7[3]={"Леву","Центру","Праву"};

__root const CFG_HDR cfghdr4_4={CFG_UINT, "Отступ от символов",0,10};
__root const unsigned int space=1;

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"Настройки DrawString",1,0};

__root const CFG_HDR cfghdr5_1={CFG_UINT,"Шрифт",0,16};
__root const unsigned int font_txt=11;

__root const CFG_HDR cfghdr5_2={CFG_COLOR,"Цвет",0,0};
__root const char color[4]={0,0,0,100};

__root const CFG_HDR cfghdr5_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char frame_color[4]={255,255,255,0};

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------
