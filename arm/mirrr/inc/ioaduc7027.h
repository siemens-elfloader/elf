/***************************************************************************
===============================================																			
ADuC7027 HEADER FILE REV 1.2																			
===============================================																			
***************************************************************************/

#ifndef __IOADI7027_H
#define __IOADI7027_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    ADuC7027 SPECIAL FUNCTION REGISTERS
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
#define FIQ_SOURCE_BIT       0x00000001
#define SWI_BIT              0x00000002
#define RTOS_TIMER_BIT       0x00000004
#define GP_TIMER_BIT         0x00000008
#define WAKEUP_TIMER_BIT     0x00000010
#define WATCHDOG_TIMER_BIT   0x00000020
#define FLASHCON_BIT         0x00000040
#define ADC_BIT              0x00000080
#define PLL_LOCK_BIT         0x00000100
#define SM_SLAVE_BIT         0x00000200
#define SM_MASTER0_BIT       0x00000400
#define SM_MASTER1_BIT       0x00000800
#define SPI_SLAVE_BIT        0x00001000
#define SPI_MASTER_BIT       0x00002000
#define UART_BIT             0x00004000
#define XIRQ0_BIT            0x00008000
#define MONITOR_BIT          0x00010000
#define PSM_BIT              0x00020000
#define XIRQ1_BIT            0x00040000
#define PLA_IRQ0_BIT         0x00080000
#define PLA_IRQ1_BIT         0x00100000
#define SPM4_IO_BIT          0x00200000
#define SPM5_IO_BIT          0x00400000
#define PWM_TRIP_BIT         0x00800000
#define PWM_SYNC_BIT         0x01000000
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
__IO_REG32(RSTSTA, 0xFFFF0230,__READ_WRITE);
__IO_REG32(RSTCLR, 0xFFFF0234,__WRITE);

/***************************************************************************
 **
 ** TIMER 0
 **
 ***************************************************************************/

__IO_REG32(T0BASE, 0xFFFF0300,__READ_WRITE);
#define T0LD T0BASE
__IO_REG32(T0VAL, 0xFFFF0304,__READ);
__IO_REG32(T0CON, 0xFFFF0308,__READ_WRITE);
__IO_REG32(T0CLRI, 0xFFFF030C,__WRITE);

/***************************************************************************
 **
 ** GENERAL PURPOSE TIMER
 **
 ***************************************************************************/

__IO_REG32(T1BASE, 0xFFFF0320,__READ_WRITE);
#define T1LD T1BASE
__IO_REG32(T1VAL, 0xFFFF0324,__READ);
__IO_REG32(T1CON, 0xFFFF0328,__READ_WRITE);
__IO_REG32(T1CLRI, 0xFFFF032C,__WRITE);
__IO_REG32(T1CAP, 0xFFFF0330,__READ_WRITE);

/***************************************************************************
 **
 ** WAKE UP TIMER
 **
 ***************************************************************************/

__IO_REG32(T2BASE, 0xFFFF0340,__READ_WRITE);
#define T2LD T2BASE
__IO_REG32(T2VAL, 0xFFFF0344,__READ);
__IO_REG32(T2CON, 0xFFFF0348,__READ_WRITE);
__IO_REG32(T2CLRI, 0xFFFF034C,__WRITE);

/***************************************************************************
 **
 ** WATCHDOG TIMER
 **
 ***************************************************************************/

__IO_REG32(T3BASE, 0xFFFF0360,__READ_WRITE);
#define T3LD T3BASE
__IO_REG32(T3VAL, 0xFFFF0364,__READ);
__IO_REG32(T3CON, 0xFFFF0368,__READ_WRITE);
__IO_REG32(T3CLRI, 0xFFFF036C,__WRITE);

/***************************************************************************
 **
 ** PLL AND OSCILLATOR CONTROL
 **
 ***************************************************************************/

__IO_REG32(PLLBASE, 0xFFFF0400,__READ_WRITE);
#define PLLSTA PLLBASE
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
__IO_REG32(ADCSTA, 0xFFFF050C,__READ);
__IO_REG32(ADCDAT, 0xFFFF0510,__READ);
__IO_REG32(ADCRST, 0xFFFF0514,__READ_WRITE);
__IO_REG32(ADCGN, 0xFFFF0530,__READ_WRITE);
__IO_REG32(ADCOF, 0xFFFF0534,__READ_WRITE);

/***************************************************************************
 **
 ** DAC INTERFACE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(DACBASE, 0xFFFF0600,__READ_WRITE);

/***************************************************************************
 **
 ** EXTERNAL MEMORY REGISTERS
 **
 ***************************************************************************/

__IO_REG32(XMBASE, 0xFFFFF000,__READ_WRITE);
#define XMCFG XMBASE
__IO_REG32(XM0CON, 0xFFFFF010,__READ_WRITE);
__IO_REG32(XM1CON, 0xFFFFF014,__READ_WRITE);
__IO_REG32(XM2CON, 0xFFFFF018,__READ_WRITE);
__IO_REG32(XM3CON, 0xFFFFF01C,__READ_WRITE);
__IO_REG32(XM0PAR, 0xFFFFF020,__READ_WRITE);
__IO_REG32(XM1PAR, 0xFFFFF024,__READ_WRITE);
__IO_REG32(XM2PAR, 0xFFFFF028,__READ_WRITE);
__IO_REG32(XM3PAR, 0xFFFFF02C,__READ_WRITE);

/***************************************************************************
 **
 ** 450 COMPATIABLE UART CORE REGISTERS
 **
 ***************************************************************************/

__IO_REG32(UARTBASE, 0xFFFF0700,__READ_WRITE);
#define COMTX UARTBASE
#define COMRX UARTBASE
#define COMDIV0 UARTBASE
__IO_REG32(COMIEN0, 0xFFFF0704,__READ_WRITE);
#define COMDIV1 COMIEN0
__IO_REG32(COMIID0, 0xFFFF0708,__READ);
__IO_REG32(COMCON0, 0xFFFF070C,__READ_WRITE);
__IO_REG32(COMCON1, 0xFFFF0710,__READ_WRITE);
__IO_REG32(COMSTA0, 0xFFFF0714,__READ);
__IO_REG32(COMSTA1, 0xFFFF0718,__READ);
__IO_REG32(COMSCR, 0xFFFF071C,__READ_WRITE);
__IO_REG32(COMIEN1, 0xFFFF0720,__READ_WRITE);
__IO_REG32(COMIID1, 0xFFFF0724,__READ);
__IO_REG32(COMADR, 0xFFFF0728,__READ_WRITE);
__IO_REG32(COMDIV2, 0xFFFF072C,__READ_WRITE);

/***************************************************************************
 **
 ** I2C BUS PERIPHERAL DEVICE 0
 **
 ***************************************************************************/

__IO_REG32(I2C0BASE, 0xFFFF0800,__READ_WRITE);
#define I2C0MSTA I2C0BASE
#define I2CMSTA I2C0BASE
__IO_REG32(I2C0SSTA, 0xFFFF0804,__READ);
#define I2CSSTA I2C0SSTA
__IO_REG32(I2C0SRX, 0xFFFF0808,__READ);
#define I2CSRX I2C0SRX
__IO_REG32(I2C0STX, 0xFFFF080C,__WRITE);
#define I2CSTX I2C0STX
__IO_REG32(I2C0MRX, 0xFFFF0810,__READ);
#define I2CMRX I2C0MRX
__IO_REG32(I2C0MTX, 0xFFFF0814,__WRITE);
#define I2CMTX I2C0MTX
__IO_REG32(I2C0CNT, 0xFFFF0818,__READ_WRITE);
#define I2CCNT I2C0CNT
__IO_REG32(I2C0ADR, 0xFFFF081C,__READ_WRITE);
#define I2CADR I2C0ADR
__IO_REG32(I2C0BYTE, 0xFFFF0824,__READ_WRITE);
#define I2CBYTE I2C0BYTE
__IO_REG32(I2C0ALT, 0xFFFF0828,__READ_WRITE);
#define I2CALT I2C0ALT
__IO_REG32(I2C0CFG, 0xFFFF082C,__READ_WRITE);
#define I2CCFG I2C0CFG
__IO_REG32(I2C0DIV, 0xFFFF0830,__READ_WRITE);
#define I2CDIV I2C0DIV
__IO_REG32(I2C0ID0, 0xFFFF0838,__READ_WRITE);
#define I2CID0 I2C0ID0
__IO_REG32(I2C0ID1, 0xFFFF083C,__READ_WRITE);
#define I2CID1 I2C0ID1
__IO_REG32(I2C0ID2, 0xFFFF0840,__READ_WRITE);
#define I2CID2 I2C0ID2
__IO_REG32(I2C0ID3, 0xFFFF0844,__READ_WRITE);
#define I2CID3 I2C0ID3
__IO_REG32(I2C0CCNT, 0xFFFF0848,__READ_WRITE);
#define I2CCCNT I2C0CCNT
__IO_REG32(I2C0FSTA, 0xFFFF084C,__READ);
#define I2CFSTA I2C0FSTA

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
__IO_REG32(I2C1BYTE, 0xFFFF0924,__READ_WRITE);
__IO_REG32(I2C1ALT, 0xFFFF0928,__READ_WRITE);
__IO_REG32(I2C1CFG, 0xFFFF092C,__READ_WRITE);
__IO_REG32(I2C1DIV, 0xFFFF0930,__READ_WRITE);
__IO_REG32(I2C1ID0, 0xFFFF0938,__READ_WRITE);
__IO_REG32(I2C1ID1, 0xFFFF093C,__READ_WRITE);
__IO_REG32(I2C1ID2, 0xFFFF0940,__READ_WRITE);
__IO_REG32(I2C1ID3, 0xFFFF0944,__READ_WRITE);
__IO_REG32(I2C1CCNT, 0xFFFF0948,__READ_WRITE);
__IO_REG32(I2C1FSTA, 0xFFFF094C,__READ);

/***************************************************************************
 **
 ** SERIAL PORT INTERFACE PERIPHERAL
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
__IO_REG32(PLADOUT, 0xFFFF0B50,__READ);
__IO_REG32(PLALCK, 0xFFFF0B54,__WRITE);
#define PLADLCK PLALCK

/***************************************************************************
 **
 ** GPIO AND SERIAL PORT MUX
 **
 ***************************************************************************/

__IO_REG32(GPIOBASE, 0xFFFFF400,__READ_WRITE);
#define GP0CON GPIOBASE
__IO_REG32(GP1CON, 0xFFFFF404,__READ_WRITE);
__IO_REG32(GP2CON, 0xFFFFF408,__READ_WRITE);
__IO_REG32(GP3CON, 0xFFFFF40C,__READ_WRITE);
__IO_REG32(GP4CON, 0xFFFFF410,__READ_WRITE);
__IO_REG32(GP0DAT, 0xFFFFF420,__READ_WRITE);
__IO_REG32(GP0SET, 0xFFFFF424,__WRITE);
__IO_REG32(GP0CLR, 0xFFFFF428,__WRITE);
__IO_REG32(GP0PAR, 0xFFFFF42C,__WRITE);
__IO_REG32(GP1DAT, 0xFFFFF430,__READ_WRITE);
__IO_REG32(GP1SET, 0xFFFFF434,__WRITE);
__IO_REG32(GP1CLR, 0xFFFFF438,__WRITE);
__IO_REG32(GP1PAR, 0xFFFFF43C,__WRITE);
__IO_REG32(GP2DAT, 0xFFFFF440,__READ_WRITE);
__IO_REG32(GP2SET, 0xFFFFF444,__WRITE);
__IO_REG32(GP2CLR, 0xFFFFF448,__WRITE);
__IO_REG32(GP3DAT, 0xFFFFF450,__READ_WRITE);
__IO_REG32(GP3SET, 0xFFFFF454,__WRITE);
__IO_REG32(GP3CLR, 0xFFFFF458,__WRITE);
__IO_REG32(GP3PAR, 0xFFFFF45C,__WRITE);
__IO_REG32(GP4DAT, 0xFFFFF460,__READ_WRITE);
__IO_REG32(GP4SET, 0xFFFFF464,__WRITE);
__IO_REG32(GP4CLR, 0xFFFFF468,__WRITE);

/***************************************************************************
 **
 ** FLASH CONTROL INTERFACE
 **
 ***************************************************************************/

__IO_REG32(FLASHBASE, 0xFFFFF800,__READ_WRITE);
#define FEESTA FLASHBASE
__IO_REG32(FEEMOD, 0xFFFFF804,__READ_WRITE);
__IO_REG32(FEECON, 0xFFFFF808,__READ_WRITE);
#define READ_HALF_WORD       0x00000001
#define WRITE_HALF_WORD      0x00000002
#define ERASE_WRITE          0x00000003
#define VERIFY_HALF_WORD     0x00000004
#define ERASE_PAGE           0x00000005
#define MASS_ERASE           0x00000006
#define READ_BURST           0x00000007
#define WRITE_BURST          0x00000008
#define ERASE_BURST_WRITE    0x00000009
#define USR_SIGN             0x0000000B
#define FEE_PROT             0x0000000C
__IO_REG32(FEEDAT, 0xFFFFF80C,__READ_WRITE);
__IO_REG32(FEEADR, 0xFFFFF810,__READ_WRITE);
__IO_REG32(FEESIGN, 0xFFFFF818,__READ);
__IO_REG32(FEEPRO, 0xFFFFF81C,__READ_WRITE);
__IO_REG32(FEEHIDE, 0xFFFFF820,__READ_WRITE);

/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/

__IO_REG32(PWMBASE, 0xFFFFFC00,__READ_WRITE);
#define PWMCON PWMBASE
__IO_REG32(PWMSTA, 0xFFFFFC04,__READ_WRITE);
#define PWMSTA0 PWMSTA
__IO_REG32(PWMDAT0, 0xFFFFFC08,__READ_WRITE);
__IO_REG32(PWMDAT1, 0xFFFFFC0C,__READ_WRITE);
__IO_REG32(PWMCFG, 0xFFFFFC10,__READ_WRITE);
__IO_REG32(PWMCH0, 0xFFFFFC14,__READ_WRITE);
__IO_REG32(PWMCH1, 0xFFFFFC18,__READ_WRITE);
__IO_REG32(PWMCH2, 0xFFFFFC1C,__READ_WRITE);
__IO_REG32(PWMEN, 0xFFFFFC20,__READ_WRITE);
__IO_REG32(PWMDAT2, 0xFFFFFC24,__READ_WRITE);


/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 ***************************************************************************/

#endif // __IOADI7027_H
