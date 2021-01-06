
#include <spl/process.h>
#include <spl/coreevent.h>
#include <spl/csm.h>
#include "editctl.h"

int ec_id;
HEADER_DESC header = {{0, 0, 131, 21}, 0, (int)"–едактор", LGP_NULL};

SOFTKEY_DESC menu_sk[]=
{
    {0x001A, 0x0000,(int)"Ћев"},
    {0x0001, 0x0000,(int)"ѕрав"},
    {0x003D, 0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
    menu_sk,0
};



void input_ghook(int id, GUI *gui, int cmd)
{

}


void input_key(int id, GUI *gui, GUI_MSG *msg)
{
    if (msg->gbsmsg->msg == KEY_DOWN || msg->gbsmsg->msg == LONG_PRESS)
    {
        if(msg->gbsmsg->submess == GREEN_BUTTON)
        {
            ShowMSG(1, (int)"o_O");
        }
    }
}



void onCreateCSM(int id, CSM_RAM *ram)
{
    static RECT canvas = {0,22,131,153};


    void *ma = malloc_adr();
    void *eq = 0;
    EDITCONTROL ec;

    PrepareEditControl(&ec);
    eq = AllocEQueue(ma, mfree_adr());

    WSHDR *ews = AllocWS(128);

    wsprintf(ews, "%08X", (unsigned int)eq);
    ConstructEditControl(&ec, 1, 0x40, ews, 256);
    AddEditControlToEditQend(eq, &ec, ma);

    wsprintf(ews, "%t", "ќбычна€ строка:");
    ConstructEditControl(&ec, 1, 0x40, ews, 256);
    AddEditControlToEditQend(eq, &ec, ma);

    wsprintf(ews, "%t", "ћедвед!!!");
    ConstructEditControl(&ec, 3, 0x40, ews, 256);
    AddEditControlToEditQend(eq, &ec, ma);

    FreeWS(ews);

    ec_id = createEditControl(ram, &canvas, 4, 0x40000000,
                      &menu_skt, &header, eq, 1, input_key, input_ghook, 0);

    // биндим к цсм-му id гу€(а не id едитконтрол€ и т.п.)
    // чтобы при закрытии гу€ закрылс€ цсм
    bindGUIToCSM(id, getEditControlGUIid(ec_id));
}



void onCloseCSM(int id, CSM_RAM *ram)
{
    destroyEditControl(ec_id);
    quit();
}



int main()
{
    initUsart();
    printf(" [+] main: pid: %d\n", getpid());

    createCSM("editcontrol", CoreCSM_GUI, onCreateCSM, onCloseCSM, 0);

    processEvents();
    return 0;
}





