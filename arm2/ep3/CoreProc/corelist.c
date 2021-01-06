
#include <swilib.h>
#include <stdio.h>
#include <spl/coreevent.h>
#include <spl/corelist.h>


void corelist_init_deb(CoreList *list, const char *file, int line)
{
    UNUSED(file);
    UNUSED(line);
    memset(list, 0, sizeof(*list));
}


void corelist_release(CoreList *list)
{
    if(list->size)
        printf("List(%X) not freed fully!\n", (uint32_t)list);
}


struct CoreListInode *corelist_push_back(CoreList *list, void *val)
{
    struct CoreListInode *inode = 0;
    if(list->first)
    {
        inode = malloc(sizeof(struct CoreListInode));
        inode->self = val;
        inode->next = 0;
        inode->prev = list->last;

        list->last->next = inode;
        list->last = inode;

        list->size++;

    } else {

        inode = list->first = malloc(sizeof(struct CoreListInode));
        list->first->next = 0;
        list->first->prev = 0;
        list->first->self = val;

        list->last = list->first;
        list->size = 1;
    }
    return inode;
}


struct CoreListInode *corelist_insert(CoreList *list, struct CoreListInode *inode_from, void *val)
{
    struct CoreListInode *inode = malloc(sizeof(struct CoreListInode));
    inode->self = val;
    inode->next = inode_from->next;
    inode->prev = inode_from;
    inode_from->next = inode;
    list->size++;
    return inode;
}


int corelist_check_inode(CoreList *list, struct CoreListInode *_inode)
{
    struct CoreListInode *inode = 0;
    corelist_foreach(inode, list->first)
    {
        if(inode == _inode){
            return 1;
        }
    }
    return 0;
}


void corelist_del_inode_db(CoreList *list, struct CoreListInode *inode, const char *file, int line)
{
    UNUSED(file);
    UNUSED(line);

    if(!list || !inode) {
        //printout("%s[%d]: WARNING: list(%X) or inode(%X) has null value!\n", file, line, list, inode);
        return;
    }

    //printout("%s[%d]: %s(%X, %X)\n", file, line, __FUNCTION__, list, inode);

    if(!corelist_check_inode(list, inode)){
        //printout("Inode not exist in list!\n");
        return;
    }

    //printout("prev: %X, next: %X\n", inode->prev, inode->next);

    struct CoreListInode *prev = inode->prev;
    struct CoreListInode *next = inode->next;

    if(inode == list->last)
    {
        if(prev)
            prev->next = 0;
        else
            list->first = 0;

        list->last = prev;
    } else {

        if(prev) {
            prev->next = next;
            next->prev = prev;
        }
        else {
            list->first = next;
            next->prev = 0;
        }
    }

    //printout("Freeing...\n");
    free(inode);
    //printout("Done\n");

    list->size--;
}


int corelist_pop(CoreList *list, void *value)
{
    struct CoreListInode *inode = 0;
    corelist_foreach(inode, list->first)
    {
        if(inode->self == value)
        {
            corelist_del_inode(list, inode);
            return 0;
        }
    }
    return -1;
}


CoreList *corelist_fork(CoreList *list)
{
    CoreList *l = malloc(sizeof(*l));
    if(!l)
        return 0;

    corelist_init(l);

    struct CoreListInode *inode = 0;
    corelist_foreach(inode, list->first)
    {
        corelist_push_back(l, inode->self);
    }

    return l;
}


void corelist_lock(CoreList *list)
{
    UNUSED(list);
}


void corelist_unlock(CoreList *list)
{
    UNUSED(list);
}
