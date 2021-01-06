#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"



//Координаты
__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8, "Папка приложения", 1, 127};
__root const char fname[128] = "4:\\Maps\\";

__root const CFG_HDR cfghdr1 = {CFG_STR_UTF8, "Сервер", 1, 127};
__root const char HOST[128] = "213.138.73.90";

__root const CFG_HDR cfghdr2={CFG_UINT,"Порт",0,999};
__root const unsigned int PORT = 80;

__root const CFG_HDR cfghdr61={CFG_UINT,"Начальное приближение",0,19};
__root const int Zoom = 13;

__root const CFG_HDR cfghdr65={CFG_CBOX,"Тип карты",0,5};
__root const int map_type = 1;
__root const CFG_CBOX_ITEM cfgcbox2[5]={"roadmap","mobile","satellite", "terrain", "hybrid"};
