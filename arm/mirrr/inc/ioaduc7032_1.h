/***************************************************************************
===============================================															
ADuC7032 HEADER FILE REV 1.2															
===============================================															
***************************************************************************/

#ifndef __IOADI7032_H
#define __IOADI7032_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    ADuC7032 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#endif /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 ** Interrupt Controller
 **
 ***************************************************************************/

__IO_REG32(INTBASE, 0xFFFF0000,__READ_WRITE);
#define IRQSTA INTBASE
__IO_REG32(IRQSIG, 0xFFFF0004,__READ_WRITE);
__IO_REG32(IRQEN, 0xFFFF0008,__READ_WRITE);
__IO_REG32(IRQCLR, 0xFFFF000C,__READ_WRITE);
__IO_REG32(SWICFG, 0xFFFF0010,__READ_WRITE);
__IO_REG32(FIQSTA, 0xFFFF0100,__READ_WRITE);
__IO_REG32(FIQSIG, 0xFFFF0104,__READ_WRITE);
__IO_REG32(FIQEN, 0xFFFF0108,__READ_WRITE);
__IO_REG32(FIQCLR, 0xFFFF010C,__READ_WRITE);

/***************************************************************************
 **
 ** Remap and System Control
 **
 ***************************************************************************/

__IO_REG32(REMAPBASE, 0xFFFF0200,__READ_WRITE);
__IO_REG32(SYSMAP0, 0xFFFF0220,__READ_WRITE);
__IO_REG32(RSTSTA, 0xFFFF0230,__READ_WRITE);
__IO_REG32(RSTCLR, 0xFFFF0234,__READ_WRITE);
__IO_REG32(SYSSER0, 0xFFFF0238,__READ_WRITE);
__IO_REG32(SYSSER1, 0xFFFF023C,__READ_WRITE);
__IO_REG32(SYSCHK, 0xFFFF0240,__READ_WRITE);

/***************************************************************************
 **
 ** 48bit General Purpose Timer 0
 **
 ***************************************************************************/

__IO_REG32(TIMER0BASE, 0xFFFF0300,__READ_WRITE);
#define T0LD TIMER0BASE
__IO_REG32(T0VAL0, 0xFFFF0304,__READ_WRITE);
__IO_REG32(T0VAL1, 0xFFFF0308,__READ_WRITE);
__IO_REG32(T0CON, 0xFFFF030C,__READ_WRITE);
__IO_REG32(T0CLRI, 0xFFFF0310,__READ_WRITE);
__IO_REG32(T0CAP, 0xFFFF0314,__READ_WRITE);

/***************************************************************************
 **
 ** General Purpose Timer 1
 **
 ***************************************************************************/

__IO_REG32(TIMER1BASE, 0xFFFF0320,__READ_WRITE);
#define T1LD TIMER1BASE
__IO_REG32(T1VAL, 0xFFFF0324,__READ_WRITE);
__IO_REG32(T1CON, 0xFFFF0328,__READ_WRITE);
__IO_REG32(T1CLRI, 0xFFFF032C,__READ_WRITE);
__IO_REG32(T1CAP, 0xFFFF0330,__READ_WRITE);

/***************************************************************************
 **
 ** Wake Up Timer
 **
 ***************************************************************************/

__IO_REG32(TIMER2BASE, 0xFFFF0340,__READ_WRITE);
#define T2LD TIMER2BASE
__IO_REG32(T2VAL, 0xFFFF0344,__READ_WRITE);
__IO_REG32(T2CON, 0xFFFF0348,__READ_WRITE);
__IO_REG32(T2CLRI, 0xFFFF034C,__READ_WRITE);

/***************************************************************************
 **
 ** Watchdog Timer
 **
 ***************************************************************************/

__IO_REG32(TIMER3BASE, 0xFFFF0360,__READ_WRITE);
#define T3LD TIMER3BASE
__IO_REG32(T3VAL, 0xFFFF0364,__READ_WRITE);
__IO_REG32(T3CON, 0xFFFF0368,__READ_WRITE);
__IO_REG32(T3CLRI, 0xFFFF036C,__READ_WRITE);

/***************************************************************************
 **
 ** PLL and Oscillator Control
 **
 ***************************************************************************/

__IO_REG32(PLLBASE, 0xFFFF0400,__READ_WRITE);
#define PLLSTA PLLBASE
__IO_REG32(POWKEY0, 0xFFFF0404,__READ_WRITE);
__IO_REG32(POWCON, 0xFFFF0408,__READ_WRITE);
__IO_REG32(POWKEY1, 0xFFFF040C,__READ_WRITE);
__IO_REG32(PLLKEY0, 0xFFFF0410,__READ_WRITE);
__IO_REG32(PLLCON, 0xFFFF0414,__READ_WRITE);
__IO_REG32(PLLKEY1, 0xFFFF0418,__READ_WRITE);
__IO_REG32(OSC0TRM, 0xFFFF042C,__READ_WRITE);
__IO_REG32(OSC0CON, 0xFFFF0440,__READ_WRITE);
__IO_REG32(OSC0STA, 0xFFFF0444,__READ_WRITE);
__IO_REG32(OSC0VAL0, 0xFFFF0448,__READ_WRITE);
__IO_REG32(OSC0VAL1, 0xFFFF044C,__READ_WRITE);

/***************************************************************************
 **
 ** ADC interface registers
 **
 ***************************************************************************/

__IO_REG32(ADCBASE, 0xFFFF0500,__READ_WRITE);
#define ADCSTA ADCBASE
__IO_REG32(ADCMSKI, 0xFFFF0504,__READ_WRITE);
__IO_REG32(ADCMDE, 0xFFFF0508,__READ_WRITE);
__IO_REG32(ADC0CON, 0xFFFF050C,__READ_WRITE);
__IO_REG32(ADC1CON, 0xFFFF0510,__READ_WRITE);
__IO_REG32(ADC2CON, 0xFFFF0514,__READ_WRITE);
__IO_REG32(ADCFLT, 0xFFFF0518,__READ_WRITE);
__IO_REG32(ADCCFG, 0xFFFF051C,__READ_WRITE);
__IO_REG32(ADC0DAT, 0xFFFF0520,__READ_WRITE);
__IO_REG32(ADC1DAT, 0xFFFF0524,__READ_WRITE);
__IO_REG32(ADC2DAT, 0xFFFF0528,__READ_WRITE);
__IO_REG32(ADCFIFO, 0xFFFF052C,__READ_WRITE);
__IO_REG32(ADC0OF, 0xFFFF0530,__READ_WRITE);
__IO_REG32(ADC1OF, 0xFFFF0534,__READ_WRITE);
__IO_REG32(ADC2OF, 0xFFFF0538,__READ_WRITE);
__IO_REG32(ADC0GN, 0xFFFF053C,__READ_WRITE);
__IO_REG32(ADC1GN, 0xFFFF0540,__READ_WRITE);
__IO_REG32(ADC2GN, 0xFFFF0544,__READ_WRITE);
__IO_REG32(ADC0RCL, 0xFFFF0548,__READ_WRITE);
__IO_REG32(ADC0RCV, 0xFFFF054C,__READ_WRITE);
__IO_REG32(ADC0TH, 0xFFFF0550,__READ_WRITE);
__IO_REG32(ADC0TCL, 0xFFFF0554,__READ_WRITE);
__IO_REG32(ADC0THV, 0xFFFF0558,__READ_WRITE);
__IO_REG32(ADC0ACC, 0xFFFF055C,__READ_WRITE);
__IO_REG32(ADC0ATH, 0xFFFF0560,__READ_WRITE);
__IO_REG32(ADCREF, 0xFFFF057C,__READ_WRITE);

/***************************************************************************
 **
 ** 450 Compatible UART core registers
 **
 ***************************************************************************/

__IO_REG32(UARTBASE, 0xFFFF0700,__READ_WRITE);
#define COMTX UARTBASE
#define COMRX UARTBASE
#define COMDIV0 UARTBASE
__IO_REG32(COMIEN0, 0xFFFF0704,__READ_WRITE);
#define COMDIV1 COMIEN0
__IO_REG32(COMIID0, 0xFFFF0708,__READ_WRITE);
__IO_REG32(COMCON0, 0xFFFF070C,__READ_WRITE);
__IO_REG32(COMCON1, 0xFFFF0710,__READ_WRITE);
__IO_REG32(COMSTA0, 0xFFFF0714,__READ_WRITE);
__IO_REG32(COMSTA1, 0xFFFF0718,__READ_WRITE);
__IO_REG32(COMSCR, 0xFFFF071C,__READ_WRITE);
__IO_REG32(COMIEN1, 0xFFFF0720,__READ_WRITE);
__IO_REG32(COMIID1, 0xFFFF0724,__READ_WRITE);
__IO_REG32(COMADR, 0xFFFF0728,__READ_WRITE);
__IO_REG32(COMDIV2, 0xFFFF072C,__READ_WRITE);

/***************************************************************************
 **
 ** LIN Hardware SYNC Registers.
 **
 ***************************************************************************/

__IO_REG32(LSBASE, 0xFFFF0780,__READ_WRITE);
#define LHSSTA LSBASE
__IO_REG32(LHSCON0, 0xFFFF0784,__READ_WRITE);
__IO_REG32(LHSVAL0, 0xFFFF0788,__READ_WRITE);
__IO_REG32(LHSCON1, 0xFFFF078C,__READ_WRITE);
__IO_REG32(LHSVAL1, 0xFFFF0790,__READ_WRITE);

/***************************************************************************
 **
 ** 2-Wire Interface registers to HV die.
 **
 ***************************************************************************/

__IO_REG32(HVBASE, 0xFFFF0800,__READ_WRITE);
__IO_REG32(HVCON, 0xFFFF0804,__READ_WRITE);
__IO_REG32(HVDAT, 0xFFFF080C,__READ_WRITE);

/***************************************************************************
 **
 ** Serial Port Interface Peripheral
 **
 ***************************************************************************/

__IO_REG32(SPIBASE, 0xFFFF0A00,__READ_WRITE);
#define SPISTA SPIBASE
__IO_REG32(SPIRX, 0xFFFF0A04,__READ_WRITE);
__IO_REG32(SPITX, 0xFFFF0A08,__READ_WRITE);
__IO_REG32(SPIDIV, 0xFFFF0A0C,__READ_WRITE);
__IO_REG32(SPICON, 0xFFFF0A10,__READ_WRITE);

/***************************************************************************
 **
 ** GPIO + Serial Port Mux (AHB bus)
 **
 ***************************************************************************/

__IO_REG32(GPIOBASE, 0xFFFF0D00,__READ_WRITE);
#define GP0CON GPIOBASE
__IO_REG32(GP1CON, 0xFFFF0D04,__READ_WRITE);
__IO_REG32(GP2CON, 0xFFFF0D08,__READ_WRITE);
__IO_REG32(GP0DAT, 0xFFFF0D20,__READ_WRITE);
__IO_REG32(GP0SET, 0xFFFF0D24,__READ_WRITE);
__IO_REG32(GP0CLR, 0xFFFF0D28,__READ_WRITE);
__IO_REG32(GP1DAT, 0xFFFF0D30,__READ_WRITE);
__IO_REG32(GP1SET, 0xFFFF0D34,__READ_WRITE);
__IO_REG32(GP1CLR, 0xFFFF0D38,__READ_WRITE);
__IO_REG32(GP2DAT, 0xFFFF0D40,__READ_WRITE);
__IO_REG32(GP2SET, 0xFFFF0D44,__READ_WRITE);
__IO_REG32(GP2CLR, 0xFFFF0D48,__READ_WRITE);

/***************************************************************************
 **
 ** Flash Control Interface 32Kbytes (AHB bus)
 **
 ***************************************************************************/

__IO_REG32(FLASH0BASE, 0xFFFF0E00,__READ_WRITE);
#define FEE0STA FLASH0BASE
__IO_REG32(FEE0MOD, 0xFFFF0E04,__READ_WRITE);
__IO_REG32(FEE0CON, 0xFFFF0E08,__READ_WRITE);
__IO_REG32(FEE0DAT, 0xFFFF0E0C,__READ_WRITE);
__IO_REG32(FEE0ADR, 0xFFFF0E10,__READ_WRITE);
__IO_REG32(FEE0SIG, 0xFFFF0E18,__READ_WRITE);
__IO_REG32(FEE0PRO, 0xFFFF0E1C,__READ_WRITE);
__IO_REG32(FEE0HID, 0xFFFF0E20,__READ_WRITE);

/***************************************************************************
 **
 ** Flash Control Interface 64Kbytes(AHB bus)
 **
 ***************************************************************************/

__IO_REG32(FLASH1BASE, 0xFFFF0E80,__READ_WRITE);
#define FEE1STA FLASH1BASE
__IO_REG32(FEE1MOD, 0xFFFF0E84,__READ_WRITE);
__IO_REG32(FEE1CON, 0xFFFF0E88,__READ_WRITE);
__IO_REG32(FEE1DAT, 0xFFFF0E8C,__READ_WRITE);
__IO_REG32(FEE1ADR, 0xFFFF0E90,__READ_WRITE);
__IO_REG32(FEE1SIG, 0xFFFF0E98,__READ_WRITE);
__IO_REG32(FEE1PRO, 0xFFFF0E9C,__READ_WRITE);
__IO_REG32(FEE1HID, 0xFFFF0EA0,__READ_WRITE);


/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 ***************************************************************************/

#endif // __IOADI7032_H
