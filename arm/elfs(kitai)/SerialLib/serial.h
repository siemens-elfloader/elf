#ifndef _SERIAL_H_
#define _SERIAL_H_

void SetSpeed(int speed);
// 0=57600,  1=115200, 2=230400, 3=460800,
// 4=614400, 5=921600, 6=1228800, 7=1600000

void Tx_byte(char data);

char Rx_byte();

#endif
