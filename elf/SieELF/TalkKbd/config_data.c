#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Озвучивать нажатия",0,2};
__root const int on_off=1;

__root const CFG_HDR cfghdr1={CFG_UINT,"Громкость",0,6};
__root const unsigned int volume=1;

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Путь к папке с *.wav",0,127};
__root const char folder_path[128]="0:\\ZBin\\sndElfs\\TalkKbd\\";

__root const CFG_HDR cfghdr3={CFG_TIME,"Начиная с",0,0};
__root const TTime TimeFrom={8,0};

__root const CFG_HDR cfghdr4={CFG_TIME,"Заканчивая",0,0};
__root const TTime TimeTo={22,0};
