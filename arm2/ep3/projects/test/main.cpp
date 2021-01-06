#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "process/process.h"

pid_t map_proc[25]={0};

int numer_of_process=0;
int max_num=0;
int dey=0;
int create()
{
  if(++numer_of_process>=max_num)return 0;
  Process *d_proc=new Process();
  d_proc->create(create);
  map_proc[numer_of_process]=d_proc->id();
  switch(dey)
  {
      case 0:d_proc->run();

  }
  return 1;
}

void create_procs(int num,int d)
{
    max_num=num;
    dey=d;
    Process *proc=new Process();
    proc->create(create);
    proc->run();
}

int main()
{

  return 1;
}
