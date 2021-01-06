/*
* amr2wav 
* 2011
*/

#include "frmbtord2.h"

short* table0__7[8] ;

void InitFrameBitOrder()
{
	int i ; 
	for( i = 0 ; i < 16; i  ++ )
		bit_Byte_Number[i][1] = (bit_Byte_Number[i][0]+7)/8 ;		
	
	table0__7[0] =(short*) BitOrderOfMR475 ;
	table0__7[1] =(short*) BitOrderOfMR515 ;
	table0__7[2] =(short*) BitOrderOfMR590 ;
	table0__7[3] =(short*) BitOrderOfMR670 ;
	table0__7[4] =(short*) BitOrderOfMR740 ;
	table0__7[5] =(short*) BitOrderOfMR795 ;
	table0__7[6] =(short*) BitOrderOfMR1020 ;
	table0__7[7] =(short*) BitOrderOfMR1220 ;
}

