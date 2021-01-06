
#ifndef __CORE_GUI_H__
#define __CORE_GUI_H__

#include <swilib.h>



int createGUI(RECT *canvas,
              void (*onRedraw)(int id),
              void (*onCreate)(int id),
              void (*onClose)(int id),
              void (*onFocus)(int id),
              void (*onUnfocus)(int id),
              void (*onKey)(int id, GUI_MSG *),
               void *userdata);

int closeGUI(int id);
int getGUIid(int id);


#endif
