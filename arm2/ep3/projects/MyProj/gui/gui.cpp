#include "gui.h"


void MYGUI::OnRedraw(MAIN_GUI *data)
{
DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,clrBlack,clrWhite);
}
void MYGUI::onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
    data->ws = AllocWS(128);
    data->gui.state=1;
}


void MYGUI::onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    data->gui.state=0;
    FreeWS( data->ws );
}

void MYGUI::onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
    data->gui.state=2;
    DisableIDLETMR();
#ifdef ELKA
    DisableIconBar(1);
#endif
}

void MYGUI::onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
    if (data->gui.state!=2) return;
    data->gui.state=1;
}
int MYGUI::method8(void)
{
    return(0);
}
int MYGUI::method9(void)
{
    return(0);
}
int MYGUI::OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
    if ((msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS))
    {
        switch(msg->gbsmsg->submess)
        {
        case RIGHT_SOFT:
            return (1);

        case '5':

            break;
        }
    }
    //REDRAW();
    return(0);
}

void * gui_methods[11]=
{
    (void *)MYGUI::OnRedraw,
    (void *)MYGUI::onCreate,
    (void *)MYGUI::onClose,
    (void *)MYGUI::onFocus,
    (void *)MYGUI::onUnfocus,
    (void *)MYGUI::OnKey,
    0,
    (void *)kill_data,
    (void *)MYGUI::method8,
    (void *)MYGUI::method9,
    0
};



void MYGUI::maincsm_oncreate(CSM_RAM *data)
{
    scr_w=ScreenW()-1;
    scr_h=ScreenH()-1;
    MAIN_CSM *csm=(MAIN_CSM*)data;
    MAIN_GUI *main_gui = new MAIN_GUI;
    zeromem(main_gui,sizeof(MAIN_GUI));
    main_gui->gui.canvas=(RECT *)(&Canvas);
//    main_gui->gui.methods=(void *)gui_methods;
    main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
    csm->csm.state=0;
    csm->csm.unk1=0;
    my_csm_id=csm->gui_id=CreateGUI(main_gui);
}

void MYGUI::ElfKiller(void)
{
    kill_elf();
}

void MYGUI::maincsm_onclose(CSM_RAM *csm)
{
    //SUBPROC((void *)ElfKiller);
}

int MYGUI::maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
    MAIN_CSM *csm=(MAIN_CSM*)data;
    if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
    {
        csm->csm.state=-3;
    }
    return(1);
}

/*
static const struct
{
    CSM_DESC maincsm;
    WSHDR maincsm_name;
} MAINCSM =
{
    {
        maincsm_onmessage,
        maincsm_oncreate,
#ifdef NEWSGOLD
        0,
        0,
        0,
        0,
#endif
        maincsm_onclose,
        sizeof(MAIN_CSM),
        1,
        &minus11
    },
    {
        maincsm_name_body,
        NAMECSM_MAGIC1,
        NAMECSM_MAGIC2,
        0x0,
        139,
        0
    }
};
*/

void MYGUI::UpdateCSMname(void)
{
//    wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"NatAlarm");
}


MYGUI::MYGUI(char*WindowName))
{

}

MYGUI::~MYGUI()
{

}
//};

