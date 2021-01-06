#include "..\..\inc\swilib.h"

__no_init char ChanRXL[] @ "RXLVLS";

typedef struct CHAN_BAN_Q
{
  struct CHAN_BAN_Q *next;
  unsigned int (__interwork*proc)(int chan, unsigned int lvl);
}CHAN_BAN_Q;


void StoreVal(int chan, unsigned int lvl)
{
  CHAN_BAN_Q *p=DATA_N_SFB()->ChanBannerQ;
  while(p)
  {
    lvl=p->proc(chan,lvl);
    p=p->next;
  }
  ChanRXL[chan]=lvl;
}

void Patch_GlobalScan(int chan, unsigned int lvl)
{
  if (lvl==0xFFFF) return;
  if (chan>971) return;
  lvl+=2;
  lvl>>=2;
  StoreVal(chan,lvl);
}

void Patch_WorkScan(int r0, unsigned int lvl, char *base, int chan)
{
  StoreVal(chan,lvl);
}
		  


