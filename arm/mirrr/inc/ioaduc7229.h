/***************************************************************************
===============================================                    														
  ADuC7229 HEADER FILE REV 1.1                            														
  REV 1.1- Updated DAC Registers														
  REV 0.7- Removed ID register        														
              -  Renamed REF0CON to REFCON														
              -  Renamed ADCCHNP to ADCCP														
              -  Renamed ADCCHNN to ADCCN														
              -  Renamed UART0 and UART1 registers
              -  Added I2C0ADR2 and I2C1ADR2 
              -  Removed I2C0DIVL I2C0DIVH I2C1DIVL I2C1DIVH
              -  Removed FEE0PAR FEE1PAR
              -  Corrected QENCLR and QENSET addresses
  REV 0.6- Comment removals        
  REV 0.5- Fixed  COM0DIVL COM0DIVH COM1DIVL COM1DIVH I2C0DIVL I2C0DIVH I2C1DIVL & I2C1DIVH        
  REV 0.4 - Added FEExPAR and corrected FEExSIGN registers         
  REV 0.3 - General update based on Rev 1.2                        
            Corrected REF0CON name                                 
            Removed GP2PAR                                         
            Added GP4CLR GP4PAR I2C0CCNT I2C0FSTA I2C1CCNT I2C1FSTA
            Corrected ADCCHNP ADCCHNN names            
            Add interrupt definitions - IAR
  REV 0.2 - Fixed typos                                            
  REV 0.1 - Initial                                                
===============================================                    														
***************************************************************************/

#ifndef __IOADI7229_H
#define __IOADI7229_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    ADuC7229 SPECIAL FUNCTION REGISTERS
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
 ** INTERRUPT CONTROLLER
 **
 ***************************************************************************/

__IO_REG32(IRQBASE, 0xFFFF0000,__READ_WRITE);
#define IRQSTA IRQBASE
__IO_REG32(IRQSIG, 0xFFFF0004,__READ);
__IO_REG32(IRQEN, 0xFFFF0008,__READ_WRITE);
__IO_REG32(IRQCLR, 0xFFFF000C,__WRITE);
__IO_REG32(SWICFG, 0xFFFF0010,__WRITE);
__IO_REG32(FIQSTA, 0xFFFF0100,__READ);
__IO_REG32(FIQSIG, 0xFFFF0104,__READ);
__IO_REG32(FIQEN, 0xFFFF0108,__READ_WRITE);
__IO_REG32(FIQCLR, 0xFFFF010C,__WRITE);

/***************************************************************************
 **
 ** REMAP AND SYSTEM CONTROL
 **
 ***************************************************************************/

__IO_REG32(REMAPBASE, 0xFFFF0200,__READ_WRITE);
__IO_REG32(REMAP, 0xFFFF0220,__READ_WRITE);
__IO_REG32(RSTSET, 0xFFFF0230,__WRITE);
#define RSTSTA RSTSET
__IO_REG32(RSTCLR, 0xFFFF0234,__WRITE);

/***************************************************************************
 **
 ** TIMER 0
 **
 ***************************************************************************/

__IO_REG32(T0BASE, 0xFFFF0300,__READ_WRITE);
#define T0LD T0BASE
__IO_REG32(T0VAL0, 0xFFFF0304,__READ);
__IO_REG32(T0VAL1, 0xFFFF0308,__READ);
__IO_REG32(T0CON, 0xFFFF030C,__READ_WRITE);
__IO_REG32(T0ICLR, 0xFFFF0310,__WRITE);
__IO_REG32(T0CAP, 0xFFFF0314,__READ);

/***************************************************************************
 **
 ** GENERAL PURPOSE TIMER
 **
 ***************************************************************************/

__IO_REG32(T1BASE, 0xFFFF0320,__READ_WRITE);
#define T1LD T1BASE
__IO_REG32(T1VAL, 0xFFFF0324,__READ);
__IO_REG32(T1CON, 0xFFFF0328,__READ_WRITE);
__IO_REG32(T1ICLR, 0xFFFF032C,__WRITE);
__IO_REG32(T1CAP, 0xFFFF0330,__READ);

/***************************************************************************
 **
 ** WAKE UP TIMER
 **
 ***************************************************************************/

__IO_REG32(T2BASE, 0xFFFF0340,__READ_WRITE);
#define T2LD T2BASE
__IO_REG32(T2VAL, 0xFFFF0344,__READ);
__IO_REG32(T2CON, 0xFFFF0348,__READ_WRITE);
__IO_REG32(T2ICLR, 0xFFFF034C,__WRITE);

/***************************************************************************
 **
 ** WATCHDOG TIMER
 **
 ***************************************************************************/

__IO_REG32(T3BASE, 0xFFFF0360,__READ_WRITE);
#define T3LD T3BASE
__IO_REG32(T3VAL, 0xFFFF0364,__READ);
__IO_REG32(T3CON, 0xFFFF0368,__READ_WRITE);
__IO_REG32(T3ICLR, 0xFFFF036C,__WRITE);

/***************************************************************************
 **
 ** GENERAL PURPOSE TIMER 4
 **
 ***************************************************************************/

__IO_REG32(T4BASE, 0xFFFF0380,__READ_WRITE);
#define T4LD T4BASE
__IO_REG32(T4VAL, 0xFFFF0384,__READ);
__IO_REG32(T4CON, 0xFFFF0388,__READ_WRITE);
__IO_REG32(T4ICLR, 0xFFFF038C,__WRITE);
__IO_REG32(T4CAP, 0xFFFF0390,__READ_WRITE);

/***************************************************************************
 **
 ** PLL AND OSCILLATOR CONTROL
 **
 ***************************************************************************/

__IO_REG32(PLLBASE, 0xFFFF0400,__READ_WRITE);
__IO_REG32(POWKEY1, 0xFFFF0404,__WRITE);
__IO_REG32(POWCON, 0xFFFF0408,__READ_WRITE);
__IO_REG32(POWKEY2, 0xFFFF040C,__WRITE);
__IO_REG32(PLLKEY1, 0xFFFF0410,__WRITE);
__IO_REG32(PLLCON, 0xFFFF0414,__READ_WRITE);
__IO_REG32(PLLKEY2, 0xFFFF0418,__WRITE);

/***************************************************************************
 **
 ** POWER SUPPLY MONITOR
 **
 ***************************************************************************/

__IO_REG32(PSMBASE, 0xFFFF0440,__READ_WRITE);
#define PSMCON PSMBASE
__IO_REG32(CMPCON, 0xFFFF0444,__READ_WRITE);

/***************************************************************************
 **
 ** Band Gap Reference
 **
 ***************************************************************************/

__IO_REG32(REFBASE, 0xFFFF0480,__READ_WRITE);
__IO_REG32(REFCON, 0xFFFF048C,__READ_WRITE);

/***************************************************************************
 **
 ** ADC INTERFACE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(ADCBASE, 0xFFFF0500,__READ_WRITE);
#define ADCCON ADCBASE
__IO_REG32(ADCCP, 0xFFFF0504,__READ_WRITE);
__IO_REG32(ADCCN, 0xFFFF0508,__READ_WRITE);
__IO_REG32(ADCSTA, 0xFFFF050C,__READ_WRITE);
__IO_REG32(ADCDAT, 0xFFFF0510,__READ);
__IO_REG32(ADCRST, 0xFFFF0514,__READ_WRITE);
__IO_REG32(ADCGN, 0xFFFF0530,__READ_WRITE);
__IO_REG32(ADCOF, 0xFFFF0534,__READ_WRITE);

/***************************************************************************
 **
 ** DAC INTERFACE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(DACBASE, 0xFFFF0670,__READ_WRITE);
#define DACCON DACBASE
__IO_REG32(DACDAT, 0xFFFF06B4,__READ_WRITE);

/***************************************************************************
 **
 ** DDS INTERFACE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(DDSBASE, 0xFFFF0690,__READ_WRITE);
#define DDSCON DDSBASE
__IO_REG32(DDSFRQ, 0xFFFF0694,__READ_WRITE);
__IO_REG32(DDSPHS, 0xFFFF0698,__READ_WRITE);
__IO_REG32(DACKEY0, 0xFFFF06A4,__READ_WRITE);
__IO_REG32(DACEN, 0xFFFF06B8,__READ_WRITE);
__IO_REG32(DACKEY1, 0xFFFF06BC,__READ_WRITE);

/***************************************************************************
 **
 ** PLM INTERFACE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(PLMBASE, 0xFFFF06C0,__READ_WRITE);
#define PLMCON1 PLMBASE
__IO_REG32(PLMCON2, 0xFFFF06C4,__READ_WRITE);
__IO_REG32(PLMCFG1, 0xFFFF06C8,__READ_WRITE);
__IO_REG32(PLMCFG2, 0xFFFF06CC,__READ_WRITE);
__IO_REG32(PLMRND, 0xFFFF06D0,__READ_WRITE);
__IO_REG32(PLMCFG3, 0xFFFF06D4,__READ_WRITE);
__IO_REG32(PLMSTA3, 0xFFFF06D8,__READ_WRITE);
__IO_REG32(PLMSTA1, 0xFFFF06DC,__READ_WRITE);
__IO_REG32(PLMSTA2, 0xFFFF06E0,__READ_WRITE);
__IO_REG32(PLMSTA4, 0xFFFF06E4,__READ_WRITE);

/***************************************************************************
 **
 ** 450 COMPATIABLE UART 0 CORE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(UART0BASE, 0xFFFF0700,__READ_WRITE);
#define COM0TX UART0BASE
#define COM0RX UART0BASE
#define COM0DIV0 UART0BASE
__IO_REG32(COM0IEN0, 0xFFFF0704,__READ_WRITE);
#define COM0DIV1 COM0IEN0
__IO_REG32(COM0IID0, 0xFFFF0708,__READ);
__IO_REG32(COM0CON0, 0xFFFF070C,__READ_WRITE);
__IO_REG32(COM0CON1, 0xFFFF0710,__READ_WRITE);
__IO_REG32(COM0STA0, 0xFFFF0714,__READ);
__IO_REG32(COM0STA1, 0xFFFF0718,__READ);
__IO_REG32(COM0SCR, 0xFFFF071C,__READ_WRITE);
__IO_REG32(COM0IEN1, 0xFFFF0720,__READ_WRITE);
__IO_REG32(COM0IID1, 0xFFFF0724,__READ);
__IO_REG32(COM0ADR, 0xFFFF0728,__READ_WRITE);
__IO_REG32(COM0DIV2, 0xFFFF072C,__READ_WRITE);

/***************************************************************************
 **
 ** 450 COMPATIABLE UART 1 CORE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(UART1BASE, 0xFFFF0740,__READ_WRITE);
#define COM1TX UART1BASE
#define COM1RX UART1BASE
#define COM1DIV0 UART1BASE
__IO_REG32(COM1IEN0, 0xFFFF0744,__READ_WRITE);
#define COM1DIV1 COM1IEN0
__IO_REG32(COM1IID0, 0xFFFF0748,__READ);
__IO_REG32(COM1CON0, 0xFFFF074C,__READ_WRITE);
__IO_REG32(COM1CON1, 0xFFFF0750,__READ_WRITE);
__IO_REG32(COM1STA0, 0xFFFF0754,__READ);
__IO_REG32(COM1STA1, 0xFFFF0758,__READ);
__IO_REG32(COM1SCR, 0xFFFF075C,__READ_WRITE);
__IO_REG32(COM1IEN1, 0xFFFF0760,__READ_WRITE);
__IO_REG32(COM1IID1, 0xFFFF0764,__READ);
__IO_REG32(COM1ADR, 0xFFFF0768,__READ_WRITE);
__IO_REG32(COM1DIV2, 0xFFFF076C,__READ_WRITE);

/***************************************************************************
 **
 ** I2C BUS PERIPHERAL DEVICE 0
 **
 ***************************************************************************/

__IO_REG32(I2C0BASE, 0xFFFF0800,__READ_WRITE);
#define I2C0MSTA I2C0BASE
__IO_REG32(I2C0SSTA, 0xFFFF0804,__READ);
__IO_REG32(I2C0SRX, 0xFFFF0808,__READ);
__IO_REG32(I2C0STX, 0xFFFF080C,__WRITE);
__IO_REG32(I2C0MRX, 0xFFFF0810,__READ);
__IO_REG32(I2C0MTX, 0xFFFF0814,__WRITE);
__IO_REG32(I2C0CNT, 0xFFFF0818,__READ_WRITE);
__IO_REG32(I2C0ADR, 0xFFFF081C,__READ_WRITE);
__IO_REG32(I2C0BYT, 0xFFFF0824,__READ_WRITE);
__IO_REG32(I2C0ALT, 0xFFFF0828,__READ_WRITE);
__IO_REG32(I2C0CFG, 0xFFFF082C,__READ_WRITE);
__IO_REG32(I2C0DIV, 0xFFFF0830,__READ_WRITE);
__IO_REG32(I2C0ID0, 0xFFFF0838,__READ_WRITE);
__IO_REG32(I2C0ID1, 0xFFFF083C,__READ_WRITE);
__IO_REG32(I2C0ID2, 0xFFFF0840,__READ_WRITE);
__IO_REG32(I2C0ID3, 0xFFFF0844,__READ_WRITE);
__IO_REG32(I2C0SSC, 0xFFFF0848,__READ_WRITE);
__IO_REG32(I2C0FIF, 0xFFFF084C,__READ_WRITE);

/***************************************************************************
 **
 ** I2C BUS PERIPHERAL DEVICE 1
 **
 ***************************************************************************/

__IO_REG32(I2C1BASE, 0xFFFF0900,__READ_WRITE);
#define I2C1MSTA I2C1BASE
__IO_REG32(I2C1SSTA, 0xFFFF0904,__READ);
__IO_REG32(I2C1SRX, 0xFFFF0908,__READ);
__IO_REG32(I2C1STX, 0xFFFF090C,__WRITE);
__IO_REG32(I2C1MRX, 0xFFFF0910,__READ);
__IO_REG32(I2C1MTX, 0xFFFF0914,__WRITE);
__IO_REG32(I2C1CNT, 0xFFFF0918,__READ_WRITE);
__IO_REG32(I2C1ADR, 0xFFFF091C,__READ_WRITE);
__IO_REG32(I2C1BYT, 0xFFFF0924,__READ_WRITE);
__IO_REG32(I2C1ALT, 0xFFFF0928,__READ_WRITE);
__IO_REG32(I2C1CFG, 0xFFFF092C,__READ_WRITE);
__IO_REG32(I2C1DIV, 0xFFFF0930,__READ_WRITE);
__IO_REG32(I2C1ID0, 0xFFFF0938,__READ_WRITE);
__IO_REG32(I2C1ID1, 0xFFFF093C,__READ_WRITE);
__IO_REG32(I2C1ID2, 0xFFFF0940,__READ_WRITE);
__IO_REG32(I2C1ID3, 0xFFFF0944,__READ_WRITE);
__IO_REG32(I2C1SSC, 0xFFFF0948,__READ_WRITE);
__IO_REG32(I2C1FIF, 0xFFFF094C,__READ_WRITE);

/***************************************************************************
 **
 ** SERIAL PERIPHERAL INTERFACE
 **
 ***************************************************************************/

__IO_REG32(SPIBASE, 0xFFFF0A00,__READ_WRITE);
#define SPISTA SPIBASE
__IO_REG32(SPIRX, 0xFFFF0A04,__READ);
__IO_REG32(SPITX, 0xFFFF0A08,__WRITE);
__IO_REG32(SPIDIV, 0xFFFF0A0C,__READ_WRITE);
__IO_REG32(SPICON, 0xFFFF0A10,__READ_WRITE);

/***************************************************************************
 **
 ** PROGRAMABLE LOGIC ARRAY
 **
 ***************************************************************************/

__IO_REG32(PLABASE, 0xFFFF0B00,__READ_WRITE);
#define PLAELM0 PLABASE
__IO_REG32(PLAELM1, 0xFFFF0B04,__READ_WRITE);
__IO_REG32(PLAELM2, 0xFFFF0B08,__READ_WRITE);
__IO_REG32(PLAELM3, 0xFFFF0B0C,__READ_WRITE);
__IO_REG32(PLAELM4, 0xFFFF0B10,__READ_WRITE);
__IO_REG32(PLAELM5, 0xFFFF0B14,__READ_WRITE);
__IO_REG32(PLAELM6, 0xFFFF0B18,__READ_WRITE);
__IO_REG32(PLAELM7, 0xFFFF0B1C,__READ_WRITE);
__IO_REG32(PLAELM8, 0xFFFF0B20,__READ_WRITE);
__IO_REG32(PLAELM9, 0xFFFF0B24,__READ_WRITE);
__IO_REG32(PLAELM10, 0xFFFF0B28,__READ_WRITE);
__IO_REG32(PLAELM11, 0xFFFF0B2C,__READ_WRITE);
__IO_REG32(PLAELM12, 0xFFFF0B30,__READ_WRITE);
__IO_REG32(PLAELM13, 0xFFFF0B34,__READ_WRITE);
__IO_REG32(PLAELM14, 0xFFFF0B38,__READ_WRITE);
__IO_REG32(PLAELM15, 0xFFFF0B3C,__READ_WRITE);
__IO_REG32(PLACLK, 0xFFFF0B40,__READ_WRITE);
__IO_REG32(PLAIRQ, 0xFFFF0B44,__READ_WRITE);
__IO_REG32(PLAADC, 0xFFFF0B48,__READ_WRITE);
__IO_REG32(PLADIN, 0xFFFF0B4C,__READ_WRITE);
__IO_REG32(PLAOUT, 0xFFFF0B50,__READ);

/***************************************************************************
 **
 ** GPIO AND SERIAL PORT MUX
 **
 ***************************************************************************/

__IO_REG32(GPIOBASE, 0xFFFF0D00,__READ_WRITE);
#define GP0CON GPIOBASE
__IO_REG32(GP1CON, 0xFFFF0D04,__READ_WRITE);
__IO_REG32(GP2CON, 0xFFFF0D08,__READ_WRITE);
__IO_REG32(GP3CON, 0xFFFF0D0C,__READ_WRITE);
__IO_REG32(GP4CON, 0xFFFF0D10,__READ_WRITE);
__IO_REG32(GP0DAT, 0xFFFF0D20,__READ_WRITE);
__IO_REG32(GP0SET, 0xFFFF0D24,__WRITE);
__IO_REG32(GP0CLR, 0xFFFF0D28,__WRITE);
__IO_REG32(GP0PAR, 0xFFFF0D2C,__READ_WRITE);
__IO_REG32(GP1DAT, 0xFFFF0D30,__READ_WRITE);
__IO_REG32(GP1SET, 0xFFFF0D34,__WRITE);
__IO_REG32(GP1CLR, 0xFFFF0D38,__WRITE);
__IO_REG32(GP1PAR, 0xFFFF0D3C,__READ_WRITE);
__IO_REG32(GP2DAT, 0xFFFF0D40,__READ_WRITE);
__IO_REG32(GP2SET, 0xFFFF0D44,__WRITE);
__IO_REG32(GP2CLR, 0xFFFF0D48,__WRITE);
__IO_REG32(GP3DAT, 0xFFFF0D50,__READ_WRITE);
__IO_REG32(GP3SET, 0xFFFF0D54,__WRITE);
__IO_REG32(GP3CLR, 0xFFFF0D58,__WRITE);
__IO_REG32(GP3PAR, 0xFFFF0D5C,__READ_WRITE);
__IO_REG32(GP4DAT, 0xFFFF0D60,__READ_WRITE);
__IO_REG32(GP4SET, 0xFFFF0D64,__WRITE);
__IO_REG32(GP4CLR, 0xFFFF0D68,__WRITE);
__IO_REG32(GP4PAR, 0xFFFF0D6C,__READ_WRITE);

/***************************************************************************
 **
 ** FLASH CONTROL INTERFACE 0
 **
 ***************************************************************************/

__IO_REG32(FLASH0BASE, 0xFFFF0E00,__READ_WRITE);
#define FEE0STA FLASH0BASE
__IO_REG32(FEE0MOD, 0xFFFF0E04,__READ_WRITE);
__IO_REG32(FEE0CON, 0xFFFF0E08,__READ_WRITE);
__IO_REG32(FEE0DAT, 0xFFFF0E0C,__READ_WRITE);
__IO_REG32(FEE0ADR, 0xFFFF0E10,__READ_WRITE);
__IO_REG32(FEE0SGN, 0xFFFF0E18,__READ);
__IO_REG32(FEE0PRO, 0xFFFF0E1C,__READ_WRITE);
__IO_REG32(FEE0HID, 0xFFFF0E20,__READ_WRITE);

/***************************************************************************
 **
 ** FLASH CONTROL INTERFACE 1
 **
 ***************************************************************************/

__IO_REG32(FLASH1BASE, 0xFFFF0E80,__READ_WRITE);
#define FEE1STA FLASH1BASE
__IO_REG32(FEE1MOD, 0xFFFF0E84,__READ_WRITE);
__IO_REG32(FEE1CON, 0xFFFF0E88,__READ_WRITE);
__IO_REG32(FEE1DAT, 0xFFFF0E8C,__READ_WRITE);
__IO_REG32(FEE1ADR, 0xFFFF0E90,__READ_WRITE);
__IO_REG32(FEE1SGN, 0xFFFF0E98,__READ);
__IO_REG32(FEE1PRO, 0xFFFF0E9C,__READ_WRITE);
__IO_REG32(FEE1HID, 0xFFFF0EA0,__READ_WRITE);

/***************************************************************************
 **
 ** Quadrature Encoder
 **
 ***************************************************************************/

__IO_REG32(QENBASE, 0xFFFF0F00,__READ_WRITE);
#define QENCON QENBASE
__IO_REG32(QENSTA, 0xFFFF0F04,__READ);
__IO_REG32(QENDAT, 0xFFFF0F08,__READ_WRITE);
__IO_REG32(QENVAL, 0xFFFF0F0C,__READ);
__IO_REG32(QENCLR, 0xFFFF0F14,__WRITE);
__IO_REG32(QENSET, 0xFFFF0F18,__WRITE);

/***************************************************************************
 **
 ** Pulse Width Modulator
 **
 ***************************************************************************/

__IO_REG32(PWMBASE, 0xFFFF0F80,__READ_WRITE);
#define PWMCON1 PWMBASE
__IO_REG32(PWM1COM1, 0xFFFF0F84,__READ_WRITE);
__IO_REG32(PWM1COM2, 0xFFFF0F88,__READ_WRITE);
__IO_REG32(PWM1COM3, 0xFFFF0F8C,__READ_WRITE);
__IO_REG32(PWM1LEN, 0xFFFF0F90,__READ_WRITE);
__IO_REG32(PWM2COM1, 0xFFFF0F94,__READ_WRITE);
__IO_REG32(PWM2COM2, 0xFFFF0F98,__READ_WRITE);
__IO_REG32(PWM2COM3, 0xFFFF0F9C,__READ_WRITE);
__IO_REG32(PWM2LEN, 0xFFFF0FA0,__READ_WRITE);
__IO_REG32(PWM3COM1, 0xFFFF0FA4,__READ_WRITE);
__IO_REG32(PWM3COM2, 0xFFFF0FA8,__READ_WRITE);
__IO_REG32(PWM3COM3, 0xFFFF0FAC,__READ_WRITE);
__IO_REG32(PWM3LEN, 0xFFFF0FB0,__READ_WRITE);
__IO_REG32(PWMCON2, 0xFFFF0FB4,__READ_WRITE);
__IO_REG32(PWMICLR, 0xFFFF0FB8,__WRITE);


/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 ***************************************************************************/

#endif // __IOADI7229_H
