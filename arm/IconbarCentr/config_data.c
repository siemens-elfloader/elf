#include "C:\ARM\inc\cfg_items.h"
#include "define.h"
//Конфигурация

#ifdef CONFIG_EL
enum icons
{
  ICO_BT_nvis=0x1C5,
  ICO_BT_vis=0x1C6,
  ICO_BT_ntrans=0x1C7,
  ICO_BT_trans=0x1C8,
  ICO_BT_headset=0x1C9,
  ICO_headset=0x1F0,

  ICO_non=0x0
};
#endif

__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Вкл. текст приветствия?",0,0};
__root const int ena_msg=0;

__root const CFG_HDR cfghdr1={CFG_CHECKBOX,"Вкл. сообщение о реконфигурации?",0,0};
__root const int ena_req=0;





//------------------------------Bluetooth---------------------------------------

__root const CFG_HDR cfghdr_m151={CFG_LEVEL,"Bluetooth",1,0};

__root const CFG_HDR cfghdr15_1={CFG_CHECKBOX,"Вкл. иконку?",0,0};
__root const int bt=1;

__root const CFG_HDR cfghdr15_2={CFG_CBOX,"Отображать при",0,3};
__root const int ena_gui_bt=0;
__root const CFG_CBOX_ITEM cfgcbox15_2_1[3]={"Везде","ГЭ","Кроме ГЭ"};

__root const CFG_HDR cfghdr15_3={CFG_UINT,"Номер картинки вкл. BT(видимый)",0,0xFFF};
__root const unsigned int bt_vis_icon=ICO_BT_vis;

__root const CFG_HDR cfghdr15_4={CFG_UINT,"Вкл. BT(невидимый)",0,0xFFF};
__root const unsigned int bt_nvis_icon=ICO_BT_nvis;

__root const CFG_HDR cfghdr15_5={CFG_UINT,"Вкл. BT(передача)",0,0xFFF};
__root const unsigned int bt_trans_icon=ICO_BT_trans;

__root const CFG_HDR cfghdr15_6={CFG_UINT,"Вкл. BT(невидимая передача)",0,0xFFF};
__root const unsigned int bt_ntrans_icon=ICO_BT_ntrans;

__root const CFG_HDR cfghdr15_7={CFG_UINT,"Вкл. BT(гарнитура)",0,0xFFF};
__root const unsigned int bt_headset_icon=ICO_headset;

__root const CFG_HDR cfghdr15_8={CFG_CHECKBOX,"Отображать иконку выкл. BT?",0,0};
__root const int bt_off=0;

__root const CFG_HDR cfghdr15_9={CFG_UINT,"Номер картинки выкл. BT",0,0xFFF};
__root const unsigned int bt_off_icon=ICO_non;

__root const CFG_HDR cfghdr_m150={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------
