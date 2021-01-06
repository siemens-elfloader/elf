#include "pmb8876_reg.h"
#include "pmb8876_uart.h"

void
uart_set_speed(unsigned int uart, unsigned int speed)
{
    unsigned int i = 0;

    if(!uart) {
	i = PMB8876_REG(USART0_BG) & 0xFF;
	i |= (speed >> 16);
	PMB8876_REG_SET_MASK(USART0_BG, i);
	
	i = ((speed << 16) >> 16);
	PMB8876_REG_SET_MASK(USART0_FDV, i);
    }
    else{
	i = PMB8876_REG(USART1_BG) & 0xFF;
	i |= (speed >> 16);
	PMB8876_REG_SET_MASK(USART1_BG, i);
	
	i = ((speed << 16) >> 16);
	PMB8876_REG_SET_MASK(USART1_FDV, i);
    }	
}

unsigned char
uart_poll_rx_byte(unsigned int uart)
{
    if(!uart) {
	while(!(PMB8876_REG(USART0_FCSTAT) & 4));
	PMB8876_REG_SET_BIT(USART0_ICR, 4);
	return(PMB8876_REG(USART0_RXB) & 0xFF);
    }
    else {
	while(!(PMB8876_REG(USART1_FCSTAT) & 4));
	PMB8876_REG_SET_BIT(USART1_ICR, 4);
	return(PMB8876_REG(USART1_RXB) & 0xFF);
    }
}

void
uart_poll_tx_byte(unsigned int uart, unsigned char byte)
{
    unsigned int data;

    if(!uart) {
	data = (PMB8876_REG(USART0_TXB) & ~0xFF) | byte;
	PMB8876_REG_SET_MASK(USART0_TXB, data);
	while(!(PMB8876_REG(USART0_FCSTAT) & 2))
	PMB8876_REG_SET_BIT(USART0_ICR, 2);

      
    }
    else {
	data = (PMB8876_REG(USART1_TXB) & ~0xFF) | byte;
	PMB8876_REG_SET_MASK(USART1_TXB, data);
	while(!(PMB8876_REG(USART1_FCSTAT) & 2));
	PMB8876_REG_SET_BIT(USART1_ICR, 2);
    }
}

void
uart_poll_tx_string(unsigned int uart, const char *msg)
{
    while(*msg) {
	uart_poll_tx_byte(uart, *msg);
	msg++;
    }
}
