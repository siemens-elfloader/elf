#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

//Конфигурация
__root const CFG_HDR cfghdr0={CFG_UINT,"Ink color",0,22};
__root const unsigned int INK=0;

__root const CFG_HDR cfghdr1={CFG_UINT,"Paper color",0,22};
__root const unsigned int PAPER=1;

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Files path",0,63};
__root const char ted_path[64]=DEFAULT_DISK ":\\ZBin\\TED\\";

__root const CFG_HDR cfghdr3={CFG_UINT,"Display light",0,100};
__root const unsigned int DISPLAY_LIGHT=10;

__root const CFG_HDR cfghdr4={CFG_CBOX,"Adjust light",0,2};
__root const int ADJ_LIGHT=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"No","Yes"};

__root const CFG_HDR cfghdr5={CFG_CBOX,"Enable autoformat",0,2};
__root const int ENA_AUTOF=0;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"No","Yes"};

__root const CFG_HDR cfghdr6={CFG_CBOX,"Auto format",0,3};
__root const int AUTOF_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox6[3]={"Direct","DOS","Win"};

__root const CFG_HDR cfghdr7={CFG_UINT,"Default font",4,100};
__root const int AUTOF_FONT=14;

