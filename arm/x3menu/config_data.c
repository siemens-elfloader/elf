#include "..\inc\cfg_items.h"
#include "main.h"

//Конфигурация

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_CBOX,"Приветствие",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Да","Нет"};

// -------------------------------------------------------------------------- //

  __root const CFG_HDR cfghdr1_4 = {CFG_UINT, "Rows", 0, 5};
  __root const unsigned int Rows = 4;

  __root const CFG_HDR cfghdr1_5 = {CFG_UINT, "Colunms", 0, 5};
  __root const unsigned int Columns = 3;

  __root const CFG_HDR cfghdr1_6 = {CFG_UINT, "OffsetX", 0, 5};
  __root const unsigned int OffsetX = 3;

  __root const CFG_HDR cfghdr1_7 = {CFG_UINT, "OffsetY", 0, 5};
  __root const unsigned int OffsetY = 3;
  
  __root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"PAth menu",0,63};
  __root const char MENU_PATH[128]=DEFAULT_DISK ":\\ZBin\\Menu\\Menu.cfg";
  
  __root const CFG_HDR cfghdr2_3={CFG_STR_UTF8,"PAth cursor",0,63};
  __root const char CURSOR_PATH[128]=DEFAULT_DISK ":\\ZBin\\Menu\\cursor.png";








