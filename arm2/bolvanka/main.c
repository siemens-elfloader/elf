
#include "C:\arm\inc\swilib.h"

void ElfKiller()
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
GBSTMR tmr;
int seconds=0;
void Timer5seconds()
{
  seconds++;
  SetIllumination(0,1,100,0); 
  if(seconds==5)
  {
    seconds=0;
    SetIllumination(0,0,100,0); 
    GBS_DelTimer(&tmr);
  }
  GBS_StartTimerProc(&tmr,216,Timer5seconds);
}

int main(char *exename, char *fname)
{
  Timer5seconds();
  SUBPROC((void *)ElfKiller);
  return 0;
}
