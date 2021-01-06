#ifndef _SETMENU_H_
  #define _SETMENU_H_
#include "..\multisim_ipc.h"
#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif
// Показать главное меню
#pragma once
int ShowSetMenu(void);

#endif
