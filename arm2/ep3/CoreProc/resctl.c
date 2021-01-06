
#include <swilib.h>
#include <spl/resctl.h>


typedef struct
{
    short id;
    void *(*onCreate)(int _pid);
    void (*onClose)(ResCtlData *);
    char used;
}ResCtl;



static ResCtl resctl[512];
static int used_cnt = 0;


void resCtlInit()
{
    for(int i=0; i<512; ++i) {
        resctl[i].used = 0;
    }
}


static int bestId()
{
    for(int i=0; i<512; ++i) {
        if(resctl[i].used == 0)
            return i;
    }
    return -1;
}


static ResCtl *getResCtlData(int id)
{
    if(id < 0 || id > 511)
        return 0;

    return &resctl[id];
}


static ResCtl *newResCtl()
{
    int id = bestId();
    ResCtl *res = getResCtlData(id);
    if(!res)
        return 0;

    res->id = id;
    res->used = 1;
    used_cnt++;
    return res;
}



int freeResCtl(int id)
{
    ResCtl *res = getResCtlData(id);
    if(!res || !res->used)
        return -1;

    res->id = -1;
    res->used = 0;
    used_cnt--;
    return 0;
}


int createResCtl()
{
    ResCtl *res = newResCtl();
    if(!res)
        return -1;

    return res->id;
}


int destroyResCtl(int id)
{
    return freeResCtl(id);
}


int setupResCtl(int id, void *(*onCreate)(int _pid), void (*onClose)(ResCtlData *data))
{
    ResCtl *res = getResCtlData(id);
    if(!res)
        return -1;

    res->onCreate = onCreate;
    res->onClose = onClose;
    return 0;
}


int attachResCtl(int _pid, ResCtlData **_attach_data)
{
    int attached = 0;

    if(used_cnt < 1) {
        *_attach_data = 0;
        return 0;
    }

    ResCtlData *attach_data = (ResCtlData*)malloc(used_cnt * sizeof(ResCtlData));

    for(int i=0; i<512; ++i) {
        if(resctl[i].used == 0)
            break;

        attach_data[attached].data = resctl[i].onCreate(_pid);
        attach_data[attached].id = i;

        attached++;
        if(attached >= used_cnt)
            break;
    }

    *_attach_data = attach_data;
    return attached;
}



int detachResCtl(int _pid, ResCtlData **_attach_data, int attached_cnt)
{
    UNUSED(_pid);
    if(attached_cnt < 1 || !*_attach_data) {
        return 0;
    }

    ResCtlData *attach_data = *_attach_data;

    for(int i=0; i<attached_cnt; ++i) {
        resctl[i].onClose(&attach_data[i]);
    }

    mfree(attach_data);
    *_attach_data = 0;
    return 0;
}












