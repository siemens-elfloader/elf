
#ifndef __IORESCTL_H__
#define __IORESCTL_H__




struct CoreListInode *IOStreamCreate(int _pid, int fd);
int IOStreamClose(int _pid, struct CoreListInode *inode, int fd);



#endif
