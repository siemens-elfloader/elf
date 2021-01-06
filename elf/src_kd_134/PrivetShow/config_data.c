#include "D:\ARM_ALL\inc\swilib.h"
#include "D:\ARM_ALL\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"Вкл. текст автора?",0,2};
__root const int ena_hel=0;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"Вкл. текст загрузки?",0,2};
__root const int ena_msg=0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Нет","Да"};

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Текст загрузки",0,127};
__root const char text_patch[128]="Все эльфы загружены";

__root const CFG_HDR cfghdr3={CFG_CBOX,"Вкл. мелодию?",0,2};
__root const int ena_snd=0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"Нет","Да"};

__root const CFG_HDR cfghdr4={CFG_STR_UTF8,"Путь к папке с мелодией",3,127};
__root const char sound_patch[128]="4:\\ZBin\\PrivetShow.wav";

__root const CFG_HDR cfghdr5={CFG_UINT,"Громкость",0,16};
__root const unsigned int def_vol=3;

__root const CFG_HDR cfghdr6={CFG_CBOX,"Вкл. иконку?",0,2};
__root const int ena_pic=0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"Нет","Да"};

__root const CFG_HDR cfghdr7={CFG_COORDINATES,"Позиция иконки",0,0};
__root const unsigned int icon_x=0;
__root const unsigned int icon_y=0;

__root const CFG_HDR cfghdr8={CFG_STR_UTF8,"Путь к иконке",3,127};
__root const char icon_patch[128]="4:\\ZBin\\1.png";
