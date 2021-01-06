
#include <swilib.h>
#include <spl/resctl.h>
#include <spl/corelist.h>
#include <spl/process.h>
#include <spl/io.h>



static int IOResCtlID = -1;

static void *onCreate(int _pid);
static void onClose(ResCtlData *data);


void createIOResCtl()
{
    IOResCtlID = createResCtl();
    setupResCtl(IOResCtlID, onCreate, onClose);
}


void closeIOResCtl()
{
    destroyResCtl(IOResCtlID);
}



static void *onCreate(int _pid)
{
    UNUSED(_pid);
    CoreList *list = malloc(sizeof *list);
    corelist_init(list);
    return list;
}


static void onClose(ResCtlData *data)
{
    if(!data)
        return;

    printf("ioresctl enter \n");
    CoreList *list = corelist_fork(data->data);

    struct CoreListInode *inode;
    corelist_clean_foreach_begin(inode, list->first) {
        if((int)inode->self > -1) {
            printf("\033[1m\033[31mpid: %d - close leak fd: %X\033[0m\n", getpid(), inode->self);
            close((int)inode->self);
            printf("Close done\n");
        }
        inode->self = (void*)-1;
    }
    corelist_clean_foreach_end(list)

    corelist_release(list);
    free(list);


    if(((CoreList *)data->data)->first)
        printf("data list is not fully cleaned!");

    corelist_release(data->data);
    free(data->data);

    printf("ioresctl leave \n");
}



struct CoreListInode *IOStreamCreate(int _pid, int fd)
{
    if(fd < 0)
        return 0;

    ResCtlData *res = dataOfResCtl(_pid, IOResCtlID);
    if(!res || !res->data)
        return 0;

    CoreList *list = res->data;

    struct CoreListInode *inode = corelist_push_back(list, (void*)fd);
    return inode;
}



int IOStreamClose(int _pid, struct CoreListInode *inode, int fd)
{
    if(fd < 0 || !inode)
        return -1;

    ResCtlData *res = dataOfResCtl(_pid, IOResCtlID);
    if(!res || !res->data)
        return -1;

    CoreList *list = res->data;
    corelist_del_inode(list, inode);
    return 0;
}





