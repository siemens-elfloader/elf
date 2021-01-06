#include "..\inc\swilib.h"
#include "..\inc\pnglist.h"

#pragma swi_number=0x07F
__swi	__arm	int IsPlayerOn();

void clear_cache()
{
  PNGTOP_DESC *ptop=PNG_TOP();
  PNGLIST *pl;
  LockSched();
  pl=ptop->pltop;
  ptop->pltop=0;
  UnlockSched();
  while(pl)
  {
    PNGLIST *pl_prev;
    pl_prev=pl;
    pl=pl->next;
    mfree(pl_prev->pngname);
    if(pl_prev->img)
    {
      mfree(pl_prev->img->bitmap);
      mfree(pl_prev->img);
    }
    mfree(pl_prev);
  }
  REDRAW();
}

void clear_bitmap()
{
  PNGTOP_DESC *ptop=PNG_TOP();
  char *bitmap;
  if ((bitmap=ptop->bitmap))
  {
    LockSched();
    zeromem(bitmap,20000/8*2);
    UnlockSched();
  }
}

GBSTMR mytmr;
void playing(void);

void check()
{
  if(IsPlayerOn())
  {
    GBS_StartTimerProc(&mytmr, 262, playing);
  }
  else
    GBS_StartTimerProc(&mytmr, 262, check);
}

void cleaning()
{
  clear_bitmap();
  clear_cache();
  GBS_StartTimerProc(&mytmr, 262, check);
}

void playing()
{
  if(IsPlayerOn())
  {
    GBS_StartTimerProc(&mytmr, 262, playing);
  }
  else
  {
    cleaning();
  }
}



void main()
{
  check();
}

