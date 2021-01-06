
#include <spl/task.h>



void initTaskConf(TaskConf *conf)
{
    conf->prio = 0;
    conf->stack = 0;
    conf->stack_size = 0;
    conf->is_stack_freeable = 0;
}


void setTaskConfigStackSize(TaskConf *conf, unsigned int sz)
{
    conf->stack_size = sz;
}
