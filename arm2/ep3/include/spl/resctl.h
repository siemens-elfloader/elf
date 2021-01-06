
#ifndef __RESCTL_H__
#define __RESCTL_H__


typedef struct
{
    int id;
    void *data;
}ResCtlData;


int createResCtl();
int destroyResCtl(int id);
int setupResCtl(int id, void *(*onCreate)(int _pid), void (*onClose)(ResCtlData *));


int attachResCtl(int _pid, ResCtlData **_attach_data);
int detachResCtl(int _pid, ResCtlData **_attach_data, int attached_cnt);





#endif
