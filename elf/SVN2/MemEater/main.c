#include "..\inc\swilib.h"

void ElfKiller(void){ 
extern void *ELF_BEGIN; 
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void main(char *exename, char *fname)
{
  int * a=malloc(128*1024);
  if(a==0)
    {
    for(int i=0;i<128;i++) 
        a=malloc(1024);
    }
}

