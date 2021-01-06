#ifndef _MAINMENU_H_
  #define _MAINMENU_H_
//#define ELF_NAME "MulitiSimElf"

#include "..\multisim_ipc.h"
#include "setmenu.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK_CFG "4"
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define DEFAULT_DISK_CFG "0"
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif
// Показать главное меню
int ShowMainMenu();

#endif
