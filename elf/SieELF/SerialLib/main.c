#include "..\inc\swilib.h"
#include "serial.h"

void ElfKiller(void){ 
extern void *ELF_BEGIN; 
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

GBSTMR tmr;
RAMNET *data;

void tx_str(char *str)
{
  int len = strlen(str);
  for (int i=0; i<len; i++)
    Tx_byte(str[i]);
}

void TMRPROC()
{
  char buffer[200];
  sprintf(buffer, "ch=%d; ci=%d;\r\nlac=%d; pwr=%d;\r\nc1=%d; c2=%d;\r\nu1=%d; u2=%d\r\n" , 
          data->ch_number, data->ci, data->lac, data->power,
          data->c1, data->c2, data->unk, data->unk2);
  tx_str("---------------------\r\n");
  tx_str(buffer);
  GBS_StartTimerProc(&tmr, 216, TMRPROC);
}

void main(char *exename, char *fname)
{
  SetSpeed(1);
  data = RamNet();
  GBS_StartTimerProc(&tmr, 216, TMRPROC);
}

