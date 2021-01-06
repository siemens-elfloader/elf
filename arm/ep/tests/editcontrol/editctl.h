
#ifndef __NU_INPUT_TEXT_H__
#define __NU_INPUT_TEXT_H__

#include <swilib.h>




int createEditControl(CSM_RAM *cram, RECT *rc, int font,
                       int soft_position_type, const SOFTKEYSTAB *soft_tab,
                       HEADER_DESC *header, void *eq, int do_free,
                       void (*onkey)(int id, GUI *gui, GUI_MSG *gmsg),
                       void (*ghook)(int id, GUI *gui, int cmd), void *userdata);


int destroyEditControl(int ec_id);
int closeEditControl(int ec_id);
int redrawEditControl(int ec_id);
int setEditControlSoftReturnAction(int ec_id, unsigned char key, int type, int code, int ret);
int getEditControlGUIid(int id);

#endif
