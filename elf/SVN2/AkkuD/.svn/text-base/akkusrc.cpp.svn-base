#include "../inc/swilib.h"
#include "time.h"

unsigned char atab_remap[256];

void LoadATAB()
{
extern char ATAB[128];
if(ATAB[0]==0) goto defaultl;

//load block  
unsigned int err;
int handle;

handle=fopen(ATAB,A_ReadOnly+A_BIN,P_READ,&err);
if(handle==-1) goto defaultl;

if(fread(handle,&atab_remap,256,&err)!=256)
  {   
  fclose(handle,&err);  
  goto defaultl;
  };
fclose(handle,&err);
return;

defaultl:
  for(unsigned int i=0;i<256;i++) atab_remap[i]=i;
};

char AkkuCapacity()
{
  extern int AKKUSRC;
  extern int GETAKKUPARAM1;
  extern int GETAKKUPARAM2;
  switch(AKKUSRC)
    {
    case 0:return atab_remap[(unsigned int)(GetAkkuCapacity())&0xFF];
    case 1:return atab_remap[(unsigned int)(GetAkku(GETAKKUPARAM1,GETAKKUPARAM2))&0xFF];
    case 2:return atab_remap[(unsigned int)(*RamCap())&0xFF];
    default:return 0;    };
 };
