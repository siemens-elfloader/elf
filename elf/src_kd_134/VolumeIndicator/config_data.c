#include "D:\ARM_ALL\inc\cfg_items.h"
#include "D:\ARM_ALL\inc\swilib.h"
//Конфигурация

__root const CFG_HDR cfghdr0={CFG_CBOX,"Тип отображения",1,2};
__root const int type_pic=0;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"DrawImg","DrawFrame"};

__root const CFG_HDR cfghdr1={CFG_UINT,"Время обновления",1,10};
__root const unsigned int refresh=2;

__root const CFG_HDR cfghdr2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui=2;
__root const CFG_CBOX_ITEM cfgcbox2[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr3={CFG_CHECKBOX,"Отображать на фоне плеера?",0,0};
__root const int ena_fon=0;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"DrawImg",1,0};

__root const CFG_HDR cfghdr1_1={CFG_COORDINATES,"Позиция",0,0};
__root const unsigned int icon_x=0;
__root const unsigned int icon_y=0;

__root const CFG_HDR cfghdr1_2={CFG_STR_UTF8,"Путь к папке с картинками",3,127};
__root const char icon_folder[128]="4:\\ZBin\\img\\VolumeIndicator\\";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"DrawFrame",1,0};

#ifdef ELKA
__root const CFG_HDR cfghdr2_1={CFG_RECT,"Позиция",0,239};
__root const RECT position={0,26,239,36};
#else
__root const CFG_HDR cfghdr2_1={CFG_RECT,"Позиция",0,131};
__root const RECT position={0,0,131,19};
#endif
 
__root const CFG_HDR cfghdr2_2={CFG_COLOR,"Цвет индикатора",0,0};
__root const char color[4]={0,255,0,100};

__root const CFG_HDR cfghdr2_3={CFG_COLOR,"Цвет рамки",0,0};
__root const char colorR[4]={255,255,255,100};

__root const CFG_HDR cfghdr2_4={CFG_COLOR,"Цвет фона",0,0};
__root const char colorF[4]={0,0,0,100};

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



