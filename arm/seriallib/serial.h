#ifndef _SERIAL_H_
#define _SERIAL_H_


#define baud_57600   0 
#define baud_115200  1 
#define baud_230400  2 
#define baud_460800  3 
#define baud_614400  4 
#define baud_921600  5 
#define baud_1228800 6 
#define baud_1600000 7 

void SetSpeed(int speed);
// 0=57600,  1=115200, 2=230400, 3=460800,
// 4=614400, 5=921600, 6=1228800, 7=1600000

void Tx_byte(char data);

char Rx_byte();

#endif
