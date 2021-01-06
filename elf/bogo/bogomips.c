/*
 *                Standalone BogoMips program
 *
 * Based on code Linux kernel code in init/main.c and
 * include/linux/delay.h
 *
 * For more information on interpreting the results, see the BogoMIPS
 * Mini-HOWTO document.
 *
 * version: 1.3 
 *  author: Jeff Tranter (Jeff_Tranter@Mitel.COM)
 *
 * version for Siemens ARM phones by Rst7/CBSIE
 */

#include "..\inc\swilib.h"

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

#pragma optimize=no_inline
/* portable version */
volatile static void delay(int loops)
{
  long i;
  for (i = loops; i >= 0 ; i--)
    ;
}

int
main(void)
{
  unsigned long loops_per_sec = 1;
  unsigned long long ticks;

//Compute CLOKS_PER_SEC
  unsigned long long CLOCKS_PER_SEC;
  TTime t;
  TDate d;
  unsigned int i;
  char s[256];
  LockSched();
  GetDateTime(&d,&t);
  i=t.param;
  do GetDateTime(&d,&t); while(i==t.param);
  i=t.param;
  StartCpuUsageCount();
  CLOCKS_PER_SEC=getCpuUsedTime_if_ena();
  do GetDateTime(&d,&t); while(i==t.param);
  StartCpuUsageCount();
  CLOCKS_PER_SEC=getCpuUsedTime_if_ena()-CLOCKS_PER_SEC;
  //Original BogoMips
  while ((loops_per_sec <<= 1)) {
    StartCpuUsageCount();
    ticks = getCpuUsedTime_if_ena();
    delay(loops_per_sec);
    StartCpuUsageCount();
    ticks = getCpuUsedTime_if_ena() - ticks;
    if (ticks >= CLOCKS_PER_SEC) {
      loops_per_sec = (loops_per_sec / ticks) * CLOCKS_PER_SEC;
      sprintf(s,"%lu.%02lu BogoMips\n",
 	     loops_per_sec/500000,
	     (loops_per_sec/5000) % 100
	     );
      ShowMSG(1,(int)s);
      UnlockSched();
      SUBPROC((void *)ElfKiller);
      return 0;
    }
  }
  ShowMSG(1,(int)"BogoMips failed!");
  UnlockSched();
  SUBPROC((void *)ElfKiller);
  return -1;
}
