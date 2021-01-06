
#include <spl/coreevent.h>
#include <spl/process.h>
#include "editctl.h"
#include "static_data_base.h"


typedef struct
{
    INPUTDIA_DESC input_dia;

    int id;
    int gui_id;
    char released, closed, removed_from_task;
    void *userdata;
    int pid;
    int dt_id;
    int soft_ret_action[15][3];
    void (*onkey)(int id, GUI *gui, GUI_MSG *gmsg);
    void (*ghook)(int id, GUI *gui, int cmd);

}EditControl;

typedef struct {
    CoreEvent head;
    void (*callback_onkey)(int id, GUI *gui, GUI_MSG *gmsg);
    void (*callback_onghook)(int id, GUI *gui, int cmd);
    EditControl *ec;
    GUI_MSG gmsg;
    GBS_MSG msg;
    GUI gui;
    int cmd;

}CoreEditControlEvent __attribute__((aligned(4)));


#define MAX_EC 128

declare_static_db(EditControl, editControl, MAX_EC);

__attribute_constructor
void ohloh()
{
    editControlInit();
}


void editControl_unk(){
}


static int editControlOnKey(GUI *gui, GUI_MSG *gmsg)
{
    EditControl *ec = (EditControl*)EDIT_GetUserPointer(gui);
    if(!ec) {
        printf("%s: How you do that?!\n", __FUNCTION__);
        return 0;
    }

    int id = gmsg->gbsmsg->submess;
    uint32_t type = (uint32_t)gmsg->gbsmsg->data0;
    uint32_t command = (uint32_t)gmsg->gbsmsg->data1;

    if(id == ec->id)
    {
        switch(type)
        {
            case 0xFFFFDEAD:
                printf("Received message 0xDEAD\n");
                return 1;

            case 1:
                if(command == -100) {
                    printf("Received message 1  -100\n");
                    return -1;
                }
                break;
        }
    }


    void onkey_dispatcher(CoreEditControlEvent *event) {
        event->gmsg.gbsmsg = &event->msg;
        event->ec->onkey(event->ec->id, &event->gui, &event->gmsg);
    }

    if(ec->onkey) {

        CoreEditControlEvent event;
        memset(&event, 0, sizeof(CoreEditControlEvent));

        event.head.id = ec->id;
        event.head.type = GUI_EVENT;
        event.head.dispatcher = (void (*)(void *))onkey_dispatcher;
        event.ec = ec;

        memcpy(&event.gmsg, gmsg, sizeof(GUI_MSG));
        memcpy(&event.msg, gmsg->gbsmsg, sizeof(GBS_MSG));
        memcpy(&event.gui, gui, sizeof(GUI));

        sendEvent(ec->pid, &event, sizeof(event));
    }

    /*if(gmsg->keys) {
        //printout("recv message %d\n", gmsg->keys);
        for(int i=0; i<10; ++i)
        {
            if(ec->soft_ret_action[i][2] == gmsg->gbsmsg->msg &&
               ec->soft_ret_action[i][0] == gmsg->keys) {

                //printout("found, send %d\n", ec->soft_ret_action[i][1]);
                return ec->soft_ret_action[i][1];
            }
        }
    }*/

    return 0;
}



void editControlOnGhook(GUI *gui, int cmd)
{
    EditControl *ec = (EditControl*)EDIT_GetUserPointer(gui);
    if(!ec) {
        printf("%s: How you do that?!\n", __FUNCTION__);
        return;
    }


    void onghook_dispatcher(CoreEditControlEvent *event) {
        event->ec->ghook(event->ec->id, &event->gui, event->cmd);
    }


    if(ec->ghook) {
        CoreEditControlEvent event;
        memset(&event, 0, sizeof(CoreEditControlEvent));

        event.head.id = ec->id;
        event.head.type = GUI_EVENT;
        event.head.dispatcher = (void (*)(void *))onghook_dispatcher;
        event.ec = ec;

        event.cmd = cmd;
        memcpy(&event.gui, gui, sizeof(GUI));

        sendEvent(ec->pid, &event, sizeof event);
    }

    if (cmd == 3) {
        ec->closed = 1;
    }


}




int createEditControl(CSM_RAM *cram, RECT *rc, int font,
                       int soft_position_type, const SOFTKEYSTAB *soft_tab,
                       HEADER_DESC *header, void *eq, int do_free,
                       void (*onkey)(int id, GUI *gui, GUI_MSG *gmsg),
                       void (*ghook)(int id, GUI *gui, int cmd), void *userdata)
{
    int pid = getpid();
    enterProcessCriticalCode(pid);

    EditControl *data = newEditControlData();
    if(!data) {
        leaveProcessCriticalCode(pid);
        return -1;
    }

    //getCoreCSMData(csm_id);

    data->pid = pid;
    data->input_dia.one = 1;
    data->input_dia.onKey = editControlOnKey;
    data->input_dia.global_hook_proc = editControlOnGhook;
    data->input_dia.locret = editControl_unk;
    data->input_dia.zero1 = 0;
    data->input_dia.softkeystab = soft_tab;
    memcpy(&data->input_dia.rc, rc, sizeof(RECT));
    data->input_dia.font = font;
    data->input_dia._100 = 100;
    data->input_dia._101 = 101;
    data->input_dia.zero2 = 0;
    data->input_dia.zero3 = 0;
    data->input_dia._0x40000000 = soft_position_type;
    data->userdata = userdata;
    data->released = data->closed = data->removed_from_task = 0;
    memset(data->soft_ret_action, 0, sizeof(data->soft_ret_action));

    data->ghook = ghook;
    data->onkey = onkey;

    /*ExtCSM_RAM *ecr = (ExtCSM_RAM *)cram;
    cram->state = 0;
    cram->unk1 = 0;*/

    int gid = CreateInputTextDialog(&data->input_dia, header, eq, do_free, data);

    if(gid < 0) {
        freeEditControlData(data->id);
        leaveProcessCriticalCode(pid);
        return -1;
    }

    data->gui_id = gid;
    data->dt_id = addProcessDtors(pid, (void *)destroyEditControl, (void*)data->id, 0);
    leaveProcessCriticalCode(pid);
    return data->id;
}



int destroyEditControl(int id)
{
    EditControl *ec = checkEditControlData(id);
    if(!ec)
        return -1;

    if(ec->released) return -2;
    ec->released = 1;

    if(!ec->closed)
        closeEditControl(ec->id);

    eraseProcessDtor(ec->pid, ec->dt_id);
    return 0;
}


int setEditControlSoftReturnAction(int id, unsigned char key, int type, int code, int ret)
{
    EditControl *ec = checkEditControlData(id);
    if(!ec)
        return -1;

    if(key > 15) return -1;
    ec->soft_ret_action[key][0] = code;
    ec->soft_ret_action[key][1] = ret;
    ec->soft_ret_action[key][2] = type;
    return 0;
}


int closeEditControl(int id)
{
    EditControl *ec = checkEditControlData(id);
    if(!ec)
        return -1;

    GBS_SendMessage(MMI_CEPID, KEY_DOWN, ec->id, 0xFFFFDEAD);
    return 0;
}


int redrawEditControl(int id)
{
    EditControl *ec = checkEditControlData(id);
    if(!ec)
        return -1;

    GBS_SendMessage(MMI_CEPID, KEY_DOWN, (void*)ec->id, 1, -100);
    return 0;
}


int getEditControlGUIid(int id)
{
    EditControl *ec = checkEditControlData(id);
    if(!ec)
        return -1;

    return ec->gui_id;
}

