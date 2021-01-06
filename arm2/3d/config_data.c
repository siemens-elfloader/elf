#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"






__root const CFG_HDR cfghdr0={CFG_INT,"Speed",10,200};//ֲגמהטל צטפנû, 
__root const int dTime1=100;

__root const CFG_HDR cfghdr5={CFG_CBOX,"Render Sprites",0,2};
__root const int Render_Sprites = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr6={CFG_CBOX,"Render Floor",0,2};
__root const int Render_Floor = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};

__root const CFG_HDR cfghdr7={CFG_CBOX,"Show FPS",0,2};
__root const int Show_FPS = 1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"No","Yes"};

__root const CFG_HDR cfghdr8={CFG_INT,"NPC Speed",1,10};//ֲגמהטל צטפנû, 
__root const int dTime2=5;
