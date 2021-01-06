#include "..\inc\swilib.h"


void ElfKiller(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

GBSTMR tmr;
RAMNET *data;






void TMRPROC()
{
  char buffer[200];
  sprintf(buffer, "ch=%d; ci=%d;\r\nlac=%d; pwr=%d;\r\nc1=%d; c2=%d;\r\nu1=%d; u2=%d\r\n" ,
          data->ch_number, data->ci, data->lac, data->power,
          data->c1, data->c2, data->unk, data->unk2);

  tx_str(buffer);
  GBS_StartTimerProc(&tmr, 216, TMRPROC);
}

void main(char *exename, char *fname)
{
  SetSpeed(baud_115200);
  data = RamNet();
  TMRPROC();
}

