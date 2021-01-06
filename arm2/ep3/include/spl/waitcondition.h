
#ifndef __WAIT_COND_H__
#define __WAIT_COND_H__


int createAdvWaitCond(const char *name, int proc_dependence);
int createWaitCond(const char *name);
int destroyWaitCond(int wid);
int waitCondition(int wid);
int wakeOneWaitCond(int wid);
int wakeAllWaitConds(int wid);
int resetWaitConditions(int wid);

#endif
