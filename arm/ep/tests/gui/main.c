
#include <swilib.h>
#include <spl/process.h>
#include <spl/coreevent.h>
#include <spl/csm.h>
#include <spl/gui.h>
#include <spl/lcd_primitives.h>


int csm_id, gui_id;
RECT canvas;
LCDLAYER *mmi_layer;


void onRedrawGUI(int id)
{
    printf("%s(%d)\n", __FUNCTION__, id);

    uint32_t red = 0xFF0000FF;
    lcd_draw_fillrect(mmi_layer, 0, 0, canvas.x2, canvas.y2, (char*)&red);

    displayLayer(mmi_layer);
}


void onCreateGUI(int id)
{
    printf("%s(%d)\n", __FUNCTION__, id);
    mmi_layer = *RamMMILCDLayer();
}


void onCloseGUI(int id)
{
    printf("%s(%d)\n", __FUNCTION__, id);
}


void onFocusGUI(int id)
{
    printf("%s(%d)\n", __FUNCTION__, id);
}


void onUnfocusGUI(int id)
{
    printf("%s(%d)\n", __FUNCTION__, id);
}


void onKeyGUI(int id, GUI_MSG *msg)
{
    if ((msg->gbsmsg->msg == KEY_DOWN || msg->gbsmsg->msg == LONG_PRESS))
    {
        switch(msg->gbsmsg->submess)
        {
        case RIGHT_SOFT:
            closeGUI(id);
            return;

        case LEFT_SOFT:
            *(int *)0xE5000000 = 0;
        }
    }
}



void onCreateCSM(int id, CSM_RAM *ram)
{
    canvas.x = 0;
    canvas.y = 0;
    canvas.x2 = ScreenW();
    canvas.y2 = ScreenH();

    gui_id = createGUI(&canvas, onRedrawGUI,
                       onCreateGUI,
                       onCloseGUI,
                       onFocusGUI,
                       onUnfocusGUI,
                       onKeyGUI,
                       NULL);

    printf("csm_id: %d | gui_id: %d\n", csm_id, gui_id);
    bindGUIToCSM(csm_id, getGUIid(gui_id));
}


void onCloseCSM(int id, CSM_RAM *ram)
{
    quit();
}




int main()
{
    initUsart();
    printf(" [+] main: pid: %d\n", getpid());

    csm_id = createCSM("test", CoreCSM_GUI, onCreateCSM, onCloseCSM, 0);

    processEvents();
    return 0;
}





