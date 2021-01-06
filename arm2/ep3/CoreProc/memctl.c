
#include <swilib.h>
#include <spl/process.h>
#include <spl/memctl.h>
#include <spl/resctl.h>
#include <spl/corelist.h>


typedef struct
{
    CoreList list;
    CoreMutex mutex;
}memory_blocked_data;


typedef struct
{
    int pid;
    void *ptr;
    void *ud;
    void (*destroy)(int pid, void *ptr, void *ud);
}memory_block;


/* TODO
 * Протестировать.
 */


static int memAllocID = -1;
int _memoryFree(int _pid, void *ptr, int nodel);

static void *onCreate(int _pid)
{
    UNUSED(_pid);

    memory_blocked_data *mblock = malloc(sizeof *mblock);
    corelist_init(&mblock->list);
    createMutex(&mblock->mutex);
    //printf("mem: onCreate %d %X\n", _pid, list);
    return mblock;
}


static void onClose(ResCtlData *data)
{
    //printf("mem: onClose %X\n", data);
    if(!data)
        return;

    memory_blocked_data *mblock = data->data;
    CoreList *list = corelist_fork(&mblock->list);
    int pid = getpid();
    struct CoreListInode *inode;

    corelist_clean_foreach_begin(inode, list->first) {
        memory_block *d = inode->self;
        if(d) {
            printf("\033[1m\033[31mpid: %d - free leak ptr: %X\033[0m\n", pid, d->ptr);
            d->destroy(d->pid, d->ptr, d->ud);
        }
    }
    corelist_clean_foreach_end(list)

    if(list->first)
        printf("memctl: list not fully freed!\n");

    corelist_release(list);
    corelist_release(&mblock->list);
    destroyMutex(&mblock->mutex);
    free(mblock);
}


void memCtlInit()
{
    memAllocID = createResCtl();
    setupResCtl(memAllocID, onCreate, onClose);
}

void memCtlFini()
{
    destroyResCtl(memAllocID);
}


static struct CoreListInode *findPtrInode(CoreList *list, void *ptr)
{
    struct CoreListInode *inode = 0;

    corelist_back_foreach(inode, list->last)
    {
        memory_block *b = inode->self;
        if(b->ptr == ptr) {
            return inode;
        }
    }

    return 0;
}


void *memoryAlloc(int pid, size_t size)
{
    if(size < 1)
        return 0;

    if(pid < 0)
        return malloc(size);

    ResCtlData *res = dataOfResCtl(pid, memAllocID);
    if(!res || !res->data)
        return 0;

    memory_blocked_data *mblock = res->data;
    CoreList *list = &mblock->list;

    char *ptr = malloc(size);
    memory_block *b = malloc(sizeof *b);

    b->destroy = (void (*)(int, void *, void *))memoryFree;
    b->pid = pid;
    b->ptr = ptr;

    lockMutex(&mblock->mutex);
    corelist_push_back(list, b);
    unlockMutex(&mblock->mutex);
    return ptr;
}



void *memoryRealloc(int pid, void *ptr, size_t size)
{
    if(size < 1)
        return 0;

    if(pid < 0)
        return realloc(ptr, size);

    if(!ptr)
        return memoryAlloc(pid, size);

    ResCtlData *res = dataOfResCtl(pid, memAllocID);
    if(!res || !res->data)
        return 0;

    memory_blocked_data *mblock = res->data;
    CoreList *list = &mblock->list;

    lockMutex(&mblock->mutex);
    struct CoreListInode *inode = findPtrInode(list, ptr);

    if(!inode) {
        printf("realloc BUG: memory ptr(0x%X) can not be found\n", ptr);
        inode = corelist_push_back(list, ptr);
        inode->self = malloc(sizeof(memory_block));
    }

    memory_block *b = inode->self;
    ptr = realloc(ptr, size);
    b->ptr = ptr;
    unlockMutex(&mblock->mutex);
    return ptr;
}



int memoryFree(int _pid, void *ptr)
{
    if(!ptr)
        return -1;

    if(_pid < 0) {
        free(ptr);
        return 0;
    }

    ResCtlData *res = dataOfResCtl(_pid, memAllocID);
    if(!res || !res->data)
        return -1;

    memory_blocked_data *mblock = res->data;
    CoreList *list = &mblock->list;

    lockMutex(&mblock->mutex);
    struct CoreListInode *inode = findPtrInode(list, ptr);
    if(!inode) {
        printf("free BUG: memory ptr(0x%X) can not be found\n", ptr);
    }
    else {
        memory_block *b = inode->self;
        free(b);
    }

    free(ptr);
    corelist_del_inode(list, inode);
    unlockMutex(&mblock->mutex);

    return 0;
}



WSHDR *alloc_ws(int pid, size_t size)
{
    if(size < 1)
        return 0;

    if(pid < 0)
        return AllocWS(size);

    ResCtlData *res = dataOfResCtl(pid, memAllocID);
    if(!res || !res->data)
        return 0;

    WSHDR *ws = AllocWS(size);
    if(!ws)
        return 0;

    memory_blocked_data *mblock = res->data;
    CoreList *list = &mblock->list;
    memory_block *b = malloc(sizeof *b);

    int free_ws(int pid, WSHDR *ws);
    b->destroy = (void (*)(int, void *, void *))free_ws;
    b->pid = pid;
    b->ptr = ws;

    lockMutex(&mblock->mutex);
    corelist_push_back(list, b);
    unlockMutex(&mblock->mutex);
    return ws;
}


int free_ws(int pid, WSHDR *ws)
{
    if(!ws)
        return -1;

    if(pid < 0) {
        FreeWS(ws);
        return 0;
    }


    ResCtlData *res = dataOfResCtl(pid, memAllocID);
    if(!res || !res->data)
        return -1;

    memory_blocked_data *mblock = res->data;
    CoreList *list = &mblock->list;

    lockMutex(&mblock->mutex);
    struct CoreListInode *inode = findPtrInode(list, ws);
    if(!inode) {
        printf("free BUG: memory ptr(0x%X) can not be found\n", ws);
    }
    else {
        memory_block *b = inode->self;
        free(b);
        inode->self = 0;
    }

    FreeWS(ws);
    corelist_del_inode(list, inode);
    unlockMutex(&mblock->mutex);
    return 0;
}




