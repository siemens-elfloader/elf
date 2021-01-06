#include "..\inc\swilib.h"
#include "pmb8876_reg.h"
#include "pmb8876_uart.h"

#define USART0 0
//#define USART1 1


unsigned char usart_rx_byte=0;
char mes[256];

int il=10;

GBSTMR tmr;
RAMNET *data;

static void Killer(void)
{
  if(IsTimerProc(&tmr))GBS_StopTimer (&tmr);
  GBS_DelTimer(&tmr);
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


void TMRPROC()
{
  //uart_poll_tx_string(USART1,"It's WORK!!!");
  
  
 // il--;
 // if(il)GBS_StartTimerProc(&tmr, 216, TMRPROC);
 // else SUBPROC((void *)Killer);
}
unsigned char answer=0;

void S(unsigned char s)
{
  char str[256];
  sprintf(str,"Answer: %x",s);
  ShowMSG(1,(int)str);
}
int main()
{
   uart_set_speed(USART0,USART_1228800); //set speed

//answer=uart_poll_rx_byte(USART0);
//S(answer);
  return 0;
}
