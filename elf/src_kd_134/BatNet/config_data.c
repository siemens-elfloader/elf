#include "C:\ARM_ALL\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Вкл. текст приветствия?",0,2};
__root const int ena_msg=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Вкл. сообщение о реконфигурации?",0,2};
__root const int ena_req=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Нет","Да"};

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Настройки отображения батареи",1,0};

__root const CFG_HDR cfghdr1_1={CFG_CBOX,"Отображать батарею?",0,2};
__root const int ena_bat=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1_2={CFG_COORDINATES,"Координаты батареи",0,0};
__root const unsigned int x_bat=112;
__root const unsigned int y_bat=0;

__root const CFG_HDR cfghdr1_3={CFG_UINT,"Начальная картинка батареи",0,0xFFF};
__root const unsigned int pic_bat=0x204;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Настройки отображения сети",1,0};

__root const CFG_HDR cfghdr2_1={CFG_CBOX,"Отображать сеть?",0,2};
__root const int ena_net=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2_2={CFG_COORDINATES,"Координаты сети",0,0};
__root const unsigned int x_net=79;
__root const unsigned int y_net=0;

__root const CFG_HDR cfghdr2_3={CFG_UINT,"Начальная картинка сети",0,0xFFF};
__root const unsigned int pic_net=0x23B;

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------




