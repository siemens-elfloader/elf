
#ifndef __CORE_CSM_H__
#define __CORE_CSM_H__

#include <swilib.h>

#define CoreCSM_GUI 1
#define CoreCSM_IDLE 2


int createCSM(const char *name, int type,
              void (*onCreate)(int id, CSM_RAM *),
              void (*onClose)(int id, CSM_RAM *),
              void (*onMessage)(int id, CSM_RAM *, GBS_MSG *));

int closeCSM(int id);
int bindGUIToCSM(int id, int gui_id);
int setNameCSM(int id, const char *name);

#endif
