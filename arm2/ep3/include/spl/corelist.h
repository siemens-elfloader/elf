

#ifndef __EXT_LIST_H__
#define __EXT_LIST_H__


#include <string.h>
#include <stdlib.h>


struct CoreListInode
{
    struct CoreListInode *prev;
    struct CoreListInode *next;
    void *self;
};


typedef struct
{
    struct CoreListInode *first;
    struct CoreListInode *last;
    size_t size;
}CoreList;


#define corelist_foreach(inode, first_inode)                     \
            for(inode = first_inode; inode; inode = inode->next)

#define corelist_back_foreach(inode, last_inode)                 \
            for(inode = last_inode; inode; inode = inode->prev)


#define corelist_clean_foreach_begin(inode, first_inode)   if(1) {               \
        struct CoreListInode *pinode = first_inode;                              \
        int i = 0;                                                              \
        for(inode = first_inode; inode; pinode = inode, inode = inode->next, ++i) {


#define corelist_clean_foreach_end(list)                \
            if(i && pinode)                                         \
                corelist_del_inode(list, pinode);                    \
        }                                                           \
        if(pinode)                                                  \
            corelist_del_inode(list, pinode);                        \
    }


//void extlist_init(CoreList *list);
void corelist_init_deb(CoreList *list, const char *, int);
void corelist_del_inode_db(CoreList *list, struct CoreListInode *inode, const char *file, int line);

#define corelist_init(list) corelist_init_deb(list, __FILE__, __LINE__)
#define corelist_del_inode(list, inode) corelist_del_inode_db(list, inode, __FILE__, __LINE__)

void corelist_release(CoreList *list);
struct CoreListInode *corelist_push_back(CoreList *list, void *val);
struct CoreListInode *corelist_insert(CoreList *list, struct CoreListInode *inode_from, void *val);
//void corelist_del_inode(CoreList *list, struct CoreListInode *inode);
int corelist_pop(CoreList *list, void *value);
void corelist_lock(CoreList *list);
void corelist_unlock(CoreList *list);
CoreList *corelist_fork(CoreList *list);

#endif
