/***************************************************************************
 **
 **    This file defines the Special Function Registers for the
 **    Oki Semiconductors ML675050
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.1 $
 **
 ***************************************************************************/

#ifndef __IOML675050_H
#define __IOML675050_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4f = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    ML675050 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

/* 3.5.1 Remap Control Register (RMPCON) */
typedef struct{
__REG32 RMPM  : 4;     
__REG32       :28;     
} __rmpcon_bits;

/* 3.5.2 AHBRAM Extended Area Control Register (AHBRAMCNT) */
typedef struct{
__REG32 USBRAM  : 1;
__REG32 LCDCRAM : 1;
__REG32         :30;
} __ahbramcnt_bits;

/* 4.3.1 ID Register (IDR) */
typedef struct{
__REG32 ID  : 8;     
__REG32     :24;     
} __idr_bits;

/* 4.3.2 Clock Stop Register (CLKSTP) */
typedef struct{
__REG32 SIO   : 1;     
__REG32 TIC   : 1;     
__REG32 CPUG  : 1;     
__REG32       : 4;     
__REG32 STOP  : 1;     
__REG32       :24;     
} __clkstp_bits;

/* 4.3.3 Peripheral Clock Control Register (PECLKCNT) */
typedef struct{
__REG32 CKE_ADC     : 1;     
__REG32 CKE_WDT     : 1;     
__REG32 CKE_FTM     : 1;     
__REG32 CKE_LCDC    : 1;     
__REG32 CKE_UART0   : 1;     
__REG32 CKE_UART1   : 1;     
__REG32 CKE_SPI0    : 1;     
__REG32 CKE_SPI1    : 1;     
__REG32 CKE_USBD    : 1;     
__REG32 CKE_USBH    : 1;     
__REG32 CKE_I2C0    : 1;     
__REG32 CKE_I2C1    : 1;     
__REG32 CKE_SIMIF0  : 1;     
__REG32 CKE_SIMIF1  : 1;     
__REG32 CKE_EXEC    : 1;     
__REG32             : 1;     
__REG32 CKE_GPIO0   : 1;     
__REG32 CKE_GPIO1   : 1;     
__REG32 CKE_GPIO2   : 1;     
__REG32 CKE_GPIO3   : 1;     
__REG32 CKE_GPIO4   : 1;     
__REG32 CKE_GPIO5   : 1;     
__REG32 CKE_GPIO6   : 1;     
__REG32 CKE_GPIO7   : 1;     
__REG32 CKE_DMAC0   : 1;     
__REG32 CKE_DMAC1   : 1;     
__REG32 CKE_DRAMC   : 1;     
__REG32             : 5;     
} __peclkcnt_bits;

/* 4.3.4 Peripheral Reset Control Register (PERSTCNT) */
typedef struct{
__REG32 RST_ADC     : 1;     
__REG32 RST_WDT     : 1;     
__REG32 RST_FTM     : 1;     
__REG32 RST_LCDC    : 1;     
__REG32 RST_UART0   : 1;     
__REG32 RST_UART1   : 1;     
__REG32 RST_SPI0    : 1;     
__REG32 RST_SPI1    : 1;     
__REG32 RST_USBD    : 1;     
__REG32 RST_USBH    : 1;     
__REG32 RST_I2C0    : 1;     
__REG32 RST_I2C1    : 1;     
__REG32 RST_SIMIF0  : 1;     
__REG32 RST_SIMIF1  : 1;     
__REG32 RST_EXEC    : 1;     
__REG32             : 1;     
__REG32 RST_GPIO0   : 1;     
__REG32 RST_GPIO1   : 1;     
__REG32 RST_GPIO2   : 1;     
__REG32 RST_GPIO3   : 1;     
__REG32 RST_GPIO4   : 1;     
__REG32 RST_GPIO5   : 1;     
__REG32 RST_GPIO6   : 1;     
__REG32 RST_GPIO7   : 1;     
__REG32 RST_DMAC0   : 1;     
__REG32 RST_DMAC1   : 1;     
__REG32 RST_DRAMC   : 1;     
__REG32             : 5;     
} __perstcnt_bits;

/* 4.3.7 Clock Control Register (CLKCNT) */
typedef struct{
__REG32 CLKDIV     : 3;     
__REG32 SYSCLKSEL  : 1;
__REG32 PLLAVCO    : 2;     
__REG32            : 1;     
__REG32 PLLSEL     : 1;     
__REG32 APBDIV     : 2;     
__REG32 SIOCLKSEL  : 1;     
__REG32            : 5;     
__REG32 PLLENA     : 1;     
__REG32 PLLENB     : 1;     
__REG32 SYSCLKEN   : 1;     
__REG32 RTCCLKEN   : 1;     
__REG32            :12;     
} __clkcnt_bits;

/* 4.3.6 Clock Stop Control Register (CLKSTPCNT) */
typedef struct{
__REG32            :16;     
__REG32 PLLENA     : 1;     
__REG32 PLLENB     : 1;     
__REG32 SYSCLKEN   : 1;     
__REG32 RTCCLKEN   : 1;     
__REG32            :12;     
} __clkstpcnt_bits;

/* 4.3.7 Clock Supply Wait Time Control Register (CKWT) */
typedef struct{
__REG32 CKWTCMP  :12;     
__REG32          : 3;     
__REG32 CKWTSEL  : 1;     
__REG32          :16;     
} __ckwt_bits;

/* 5.2.1 DMA Control -A Register (DMAARQCNT) */
typedef struct{
__REG32 CH0SEL    : 5;     
__REG32           : 3;     
__REG32 CH1SEL    : 5;     
__REG32           : 3;     
__REG32 CH2SEL    : 5;     
__REG32           : 3;     
__REG32 CH3SEL    : 5;     
__REG32           : 3;     
} __dmaarqcnt_bits;

/* 5.2.2 DMA Control -B Register (DMABRQCNT) */
typedef struct{
__REG32 CH0SEL    : 5;     
__REG32           : 3;     
__REG32 CH1SEL    : 5;     
__REG32           :19;     
} __dmabrqcnt_bits;

/* 5.2.3 I2C input noise filter setting register (I2CNF) */
typedef struct{
__REG8  I2CNF0    : 1;     
__REG8  I2CNF1    : 1;     
__REG8            : 6;     
} __i2cnf_bits;

/* 5.2.5 FTM Control Register (FTMSEL) */
typedef struct{
__REG32 FTMCLK0  : 1;     
__REG32          : 1;     
__REG32 FTMCLK1  : 1;     
__REG32          : 5;     
__REG32 FTMIN0   : 1;     
__REG32          : 1;     
__REG32 FTMIN1   : 1;     
__REG32          : 1;     
__REG32 FTMIN2   : 1;     
__REG32          : 1;     
__REG32 FTMIN3   : 1;     
__REG32          : 1;     
__REG32 FTMIN4   : 1;     
__REG32          : 1;     
__REG32 FTMIN5   : 1;     
__REG32          :13;     
} __ftmsel_bits;

/* 5.2.6 External DMA Control Register (EXDMACNT) */
typedef struct{
__REG32 EXREQ0   : 1;     
__REG32 EXACK0   : 1;     
__REG32 EXREQ1   : 1;     
__REG32 EXACK1   : 1;     
__REG32          :28;     
} __exdmacnt_bits;

/* 5.2.7 Port Control Register 1 (PORTSEL1)*/
typedef struct{
__REG32 PA0 : 2;     
__REG32 PA1 : 2;     
__REG32 PA2 : 2;     
__REG32 PA3 : 2;     
__REG32 PA4 : 2;     
__REG32 PA5 : 2;     
__REG32 PA6 : 2;     
__REG32 PA7 : 2;     
__REG32 PB0 : 2;     
__REG32 PB1 : 2;     
__REG32 PB2 : 2;     
__REG32 PB3 : 2;     
__REG32 PB4 : 2;     
__REG32 PB5 : 2;     
__REG32 PB6 : 2;     
__REG32 PB7 : 2;     
} __portsel1_bits;

/* 5.2.8 Port Control Register 2 (PORTSEL2)) */
typedef struct{
__REG32 PC0  : 2;     
__REG32 PC1  : 2;     
__REG32 PC2  : 2;     
__REG32 PC3  : 2;     
__REG32 PC4  : 2;     
__REG32 PC5  : 2;     
__REG32 PC6  : 2;     
__REG32 PC7  : 2;     
__REG32 PD0  : 2;     
__REG32 PD1  : 2;     
__REG32 PD2  : 2;     
__REG32 PD3  : 2;     
__REG32 PD4  : 2;     
__REG32 PD5  : 2;     
__REG32 PD6  : 2;     
__REG32 PD7  : 2;     
} __portsel2_bits;

/* 5.2.5 Port Control Register 3 (PORTSEL3) */
typedef struct{
__REG32 PE0  : 2;     
__REG32 PE1  : 2;     
__REG32 PE2  : 2;     
__REG32 PE3  : 2;     
__REG32 PE4  : 2;     
__REG32 PE5  : 2;     
__REG32 PE6  : 2;     
__REG32 PE7  : 2;     
__REG32 PF0  : 2;     
__REG32 PF1  : 2;     
__REG32 PF2  : 2;     
__REG32 PF3  : 2;     
__REG32 PF4  : 2;     
__REG32 PF5  : 2;     
__REG32      : 4;     
} __portsel3_bits;

/* 5.2.6 Port Control Register 4 (PORTSEL4) */
typedef struct{
__REG32 PG0  : 2;     
__REG32 PG1  : 2;     
__REG32 PG2  : 2;     
__REG32 PG3  : 2;     
__REG32 PG4  : 2;     
__REG32 PG5  : 2;     
__REG32 PG6  : 2;     
__REG32 PG7  : 2;     
__REG32 PH0  : 2;     
__REG32 PH1  : 2;     
__REG32 PH2  : 2;     
__REG32 PH3  : 2;     
__REG32 PH4  : 2;     
__REG32 PH5  : 2;     
__REG32 PH6  : 2;     
__REG32 PH7  : 2;     
} __portsel4_bits;

/* 6.5.1 IRQ Register (IRQ) */
typedef struct{
__REG32 IRQ0   : 1;     
__REG32 IRQ1   : 1;     
__REG32 IRQ2   : 1;     
__REG32 IRQ3   : 1;     
__REG32 IRQ4   : 1;     
__REG32 IRQ5   : 1;     
__REG32 IRQ6   : 1;     
__REG32 IRQ7   : 1;     
__REG32 IRQ8   : 1;     
__REG32 IRQ9   : 1;     
__REG32 IRQ10  : 1;     
__REG32 IRQ11  : 1;     
__REG32 IRQ12  : 1;     
__REG32 IRQ13  : 1;     
__REG32 IRQ14  : 1;     
__REG32 IRQ15  : 1;     
__REG32        :16;     
} __irq_bits;

/* 6.5.2 IRQ Software Register (IRQS) */
typedef struct{
__REG32       : 1;     
__REG32 IRQS  : 1;     
__REG32       :30;     
} __irqs_bits;

/* 6.5.3 FIQ Register (FIQ) */
typedef struct{
__REG32 FIQ  : 1;     
__REG32      :31;     
} __fiq_bits;

/* 6.5.4 FIQRAW Register (FIQRAW) */
typedef struct{
__REG32 FIQRAW  : 1;     
__REG32         :31;     
} __fiqraw_bits;

/* 6.5.5 FIQ Enable Register (FIQEN) */
typedef struct{
__REG32 FIQEN  : 1;     
__REG32        :31;     
} __fiqen_bits;

/* 6.5.6 IRQ Number Register (IRN) */
typedef struct{
__REG32 IRN  : 6;     
__REG32      :26;     
} __irn_bits;

/* 6.5.7 Current IRQ Level Register (CIL) */
typedef struct{
__REG32       : 1;     
__REG32 CIL1  : 1;     
__REG32 CIL2  : 1;     
__REG32 CIL3  : 1;     
__REG32 CIL4  : 1;     
__REG32 CIL5  : 1;     
__REG32 CIL6  : 1;     
__REG32 CIL7  : 1;     
__REG32       :24;     
} __cil_bits;

/* 6.5.8 IRQ Level Control Register 0 (ILC0) */
typedef struct{
__REG32 ILR0  : 3;     
__REG32       : 1;     
__REG32 ILR1  : 3;     
__REG32       : 9;     
__REG32 ILR4  : 3;     
__REG32       : 5;     
__REG32 ILR6  : 3;     
__REG32       : 5;     
} __ilc0_bits;

/* 6.5.9 IRQ Level Control Register 1 (ILC1) */
typedef struct{
__REG32 ILR8   : 3;     
__REG32        : 1;     
__REG32 ILR9   : 3;     
__REG32        : 1;     
__REG32 ILR10  : 3;     
__REG32        : 1;     
__REG32 ILR11  : 3;     
__REG32        : 1;     
__REG32 ILR12  : 3;     
__REG32        : 1;     
__REG32 ILR13  : 3;     
__REG32        : 1;     
__REG32 ILR14  : 3;     
__REG32        : 1;     
__REG32 ILR15  : 3;     
__REG32        : 1;     
} __ilc1_bits;

/* 6.5.11 Current IRQ Encode Register (CILE) */
typedef struct{
__REG32 CILE  : 3;     
__REG32       :29;     
} __cile_bits;

/* 6.5.12 Extended Interrupt Size Register (EXIRS) */
typedef struct{
__REG32 EXIRS  : 6;     
__REG32        :26;     
} __exirs_bits;

/* 6.5.13 Extended Interrupt Clear Register (EXIRCL) */
typedef struct{
__REG32 EXIRCL  : 6;     
__REG32         :26;     
} __exircl_bits;

/* 6.5.14 Extended Interrupt IRQ Registers A to C (EXIRQA to C) */
typedef struct{
__REG32 IRQ16  : 1;     
__REG32 IRQ17  : 1;     
__REG32 IRQ18  : 1;     
__REG32 IRQ19  : 1;     
__REG32 IRQ20  : 1;     
__REG32 IRQ21  : 1;     
__REG32 IRQ22  : 1;     
__REG32 IRQ23  : 1;     
__REG32 IRQ24  : 1;     
__REG32 IRQ25  : 1;     
__REG32 IRQ26  : 1;     
__REG32 IRQ27  : 1;     
__REG32 IRQ28  : 1;     
__REG32 IRQ29  : 1;     
__REG32 IRQ30  : 1;     
__REG32 IRQ31  : 1;     
__REG32        :16;     
} __exirqa_bits;

typedef struct{
__REG32 IRQ32  : 1;     
__REG32 IRQ33  : 1;     
__REG32 IRQ34  : 1;     
__REG32 IRQ35  : 1;     
__REG32 IRQ36  : 1;     
__REG32 IRQ37  : 1;     
__REG32 IRQ38  : 1;     
__REG32 IRQ39  : 1;     
__REG32 IRQ40  : 1;     
__REG32 IRQ41  : 1;     
__REG32 IRQ42  : 1;     
__REG32 IRQ43  : 1;     
__REG32 IRQ44  : 1;     
__REG32 IRQ45  : 1;     
__REG32 IRQ46  : 1;     
__REG32 IRQ47  : 1;     
__REG32        :16;     
} __exirqb_bits;

typedef struct{
__REG32 IRQ48  : 1;     
__REG32 IRQ49  : 1;     
__REG32 IRQ50  : 1;     
__REG32 IRQ51  : 1;     
__REG32 IRQ52  : 1;     
__REG32 IRQ53  : 1;     
__REG32 IRQ54  : 1;     
__REG32 IRQ55  : 1;     
__REG32 IRQ56  : 1;     
__REG32 IRQ57  : 1;     
__REG32 IRQ58  : 1;     
__REG32 IRQ59  : 1;     
__REG32 IRQ60  : 1;     
__REG32 IRQ61  : 1;     
__REG32 IRQ62  : 1;     
__REG32 IRQ63  : 1;     
__REG32        :16;     
} __exirqc_bits;

/* 6.5.15 Extended Interrupt Detection Mode Setting Register (EXIDM) */
typedef struct{
__REG32 IDM32   : 1;     
__REG32         : 1;     
__REG32 IDM34   : 1;     
__REG32         : 1;     
__REG32 IDM36   : 1;     
__REG32         : 1;     
__REG32 IDM38   : 1;     
__REG32         : 1;     
__REG32 IDM40   : 1;     
__REG32         : 1;     
__REG32 IDM42   : 1;     
__REG32         : 1;     
__REG32 IDM44   : 1;     
__REG32         :19;     
} __exidm_bits;

/* 6.5.16 Extended Interrupt IRQ Level Control Registers A to C (EXILCA to C) */
typedef struct{
__REG32 ILC16  : 3;     
__REG32        : 1;     
__REG32 ILC18  : 3;     
__REG32        : 1;     
__REG32 ILC20  : 3;     
__REG32        : 1;     
__REG32 ILC22  : 3;     
__REG32        : 1;     
__REG32 ILC24  : 3;     
__REG32        : 1;     
__REG32 ILC26  : 3;     
__REG32        : 1;     
__REG32 ILC28  : 3;     
__REG32        : 1;     
__REG32 ILC30  : 3;     
__REG32        : 1;     
} __exilca_bits;

typedef struct{
__REG32 ILC32  : 3;     
__REG32        : 1;     
__REG32 ILC34  : 3;     
__REG32        : 1;     
__REG32 ILC36  : 3;     
__REG32        : 1;     
__REG32 ILC38  : 3;     
__REG32        : 1;     
__REG32 ILC40  : 3;     
__REG32        : 1;     
__REG32 ILC42  : 3;     
__REG32        : 1;     
__REG32 ILC44  : 3;     
__REG32        : 1;     
__REG32 ILC46  : 3;     
__REG32        : 1;     
} __exilcb_bits;

typedef struct{
__REG32 ILC48  : 3;     
__REG32        : 1;     
__REG32 ILC50  : 3;     
__REG32        : 1;     
__REG32 ILC52  : 3;     
__REG32        : 1;     
__REG32 ILC54  : 3;     
__REG32        : 1;     
__REG32 ILC56  : 3;     
__REG32        : 1;     
__REG32 ILC58  : 3;     
__REG32        : 1;     
__REG32 ILC60  : 3;     
__REG32        : 1;     
__REG32 ILC62  : 3;     
__REG32        : 1;     
} __exilcc_bits;

/* 6.5.17 Extended Interrupt IRQ Status Registers A to C (EXIRQSA to C) */
typedef struct{
__REG32 IRQ16  : 1;     
__REG32 IRQ17  : 1;     
__REG32 IRQ18  : 1;     
__REG32 IRQ19  : 1;     
__REG32 IRQ20  : 1;     
__REG32 IRQ21  : 1;     
__REG32 IRQ22  : 1;     
__REG32 IRQ23  : 1;     
__REG32 IRQ24  : 1;     
__REG32 IRQ25  : 1;     
__REG32 IRQ26  : 1;     
__REG32 IRQ27  : 1;     
__REG32 IRQ28  : 1;     
__REG32 IRQ29  : 1;     
__REG32 IRQ30  : 1;     
__REG32 IRQ31  : 1;     
__REG32        :16;     
} __exirqsa_bits;

typedef struct{
__REG32 IRQ32  : 1;     
__REG32 IRQ33  : 1;     
__REG32 IRQ34  : 1;     
__REG32 IRQ35  : 1;     
__REG32 IRQ36  : 1;     
__REG32 IRQ37  : 1;     
__REG32 IRQ38  : 1;     
__REG32 IRQ39  : 1;     
__REG32 IRQ40  : 1;     
__REG32 IRQ41  : 1;     
__REG32 IRQ42  : 1;     
__REG32 IRQ43  : 1;     
__REG32 IRQ44  : 1;     
__REG32 IRQ45  : 1;     
__REG32 IRQ46  : 1;     
__REG32 IRQ47  : 1;     
__REG32        :16;     
} __exirqsb_bits;

typedef struct{
__REG32 IRQ48  : 1;     
__REG32 IRQ49  : 1;     
__REG32 IRQ50  : 1;     
__REG32 IRQ51  : 1;     
__REG32 IRQ52  : 1;     
__REG32 IRQ53  : 1;     
__REG32 IRQ54  : 1;     
__REG32 IRQ55  : 1;     
__REG32 IRQ56  : 1;     
__REG32 IRQ57  : 1;     
__REG32 IRQ58  : 1;     
__REG32 IRQ59  : 1;     
__REG32 IRQ60  : 1;     
__REG32 IRQ61  : 1;     
__REG32 IRQ62  : 1;     
__REG32 IRQ63  : 1;     
__REG32        :16;     
} __exirqsc_bits;

/* 6.5.18 Extended Interrupt FIQ Register (EXFIQ) */
typedef struct{
__REG32 EXFIQ  : 1;     
__REG32        :31;     
} __exfiq_bits;

/* 6.5.19 Extended Interrupt FIQ Detection Setting Register (EXFIDM) */
typedef struct{
__REG32 FIDM   : 1;     
__REG32        :31;     
} __exfidm_bits;

/* 6.5.20 Extended interrupt FIQ detection mode setting register (EXINTCNT) */
typedef struct{
__REG32 EXINT0 : 1;     
__REG32 EXINT1 : 1;     
__REG32 EXINT2 : 1;     
__REG32 EXINT3 : 1;     
__REG32 EXINT4 : 1;     
__REG32 EXINT5 : 1;     
__REG32 EXINT6 : 1;     
__REG32        :25;     
} __exintcnt_bits;

/* 7.2.1 Cache Lock Control Register (CON) */
typedef struct{
__REG32         :25;     
__REG32 LCK     : 2;     
__REG32 F       : 1;     
__REG32 BNK     : 2;     
__REG32         : 2;     
} __con_bits;

/* 7.2.2 Cacheable Register (CACHE) */
typedef struct{
__REG32 C8      : 1;     
__REG32 C9      : 1;     
__REG32 C10     : 1;     
__REG32 C11     : 1;     
__REG32 C12     : 1;     
__REG32 C13     : 1;     
__REG32 C14     : 1;     
__REG32 C15     : 1;     
__REG32 C24     : 1;     
__REG32 C25     : 1;     
__REG32 C26     : 1;     
__REG32 C27     : 1;     
__REG32 C28     : 1;     
__REG32 C29     : 1;     
__REG32 C30     : 1;     
__REG32 C31     : 1;     
__REG32 C0      : 1;     
__REG32         :15;     
} __cache_bits;

/* 7.4.1 Bus width Control Register (BWC) */
typedef struct{
__REG32        : 2;     
__REG32 ROMBW  : 2;     
__REG32 RAMBW  : 2;     
__REG32 IOBW   : 2;     
__REG32        :24;     
} __bwc_bits;

/* 8.4.2 ROM Access Control Register (ROMAC) */
typedef struct{
__REG32 ROMTYPE  : 3;     
__REG32          : 1;     
__REG32 ROMBRST  : 1;     
__REG32          :27;     
} __romac_bits;

/* 8.4.3 SRAM Access Control Register (RAMAC) */
typedef struct{
__REG32 RAMTYPE  : 3;     
__REG32          : 1;     
__REG32 RAMBRST  : 1;     
__REG32          :27;     
} __ramac_bits;

/* 8.4.4 IO Access Control Register (IOAC) */
typedef struct{
__REG32 IOTYPE    : 3;     
__REG32           :29;     
} __ioac_bits;

/* 9.4.1 Transmit/Receive Buffer Register (SIOBUF) */
typedef struct{
__REG32 SIOBUF  : 8;     
__REG32         :24;     
} __siobuf_bits;

/* 9.4.2 SIO Status Register (SIOSTA) */
typedef struct{
__REG32 FERR   : 1;     
__REG32 OERR   : 1;     
__REG32 PERR   : 1;     
__REG32        : 1;     
__REG32 RVIRQ  : 1;     
__REG32 TRIRQ  : 1;     
__REG32        :26;     
} __siosta_bits;

/* 9.4.3 SIO Control Register (SIOCON) */
typedef struct{
__REG32 LN    : 1;     
__REG32 PEN   : 1;     
__REG32 EVN   : 1;     
__REG32 TSTB  : 1;     
__REG32       :28;     
} __siocon_bits;

/* 9.4.4 Baud Rate Control Register (SIOBCN) */
typedef struct{
__REG32        : 4;     
__REG32 BGRUN  : 1;     
__REG32        :27;     
} __siobcn_bits;

/* 9.4.5 Baud Rate Timer Register (SIOBT) */
typedef struct{
__REG32 SIOBT  : 8;     
__REG32        :24;     
} __siobt_bits;

/* SIO Test Control Register (SIOTCN) */
typedef struct{
__REG32 MFERR  : 1;     
__REG32 MPERR  : 1;     
__REG32        : 5;     
__REG32 LBTST  : 1;     
__REG32        :24;     
} __siotcn_bits;

/* 10.4.1 Timer Enable Register (TMEN) */
typedef struct{
__REG32 TCEN  : 1;     
__REG32       :31;     
} __tmen_bits;

/* 10.4.3 Overflow Register (TMOVF) */
typedef struct{
__REG32 OVF  : 1;     
__REG32      :31;     
} __tmovf_bits;

/* 11.6.1 DRAM Bus Width Control Register (DBWC) */
typedef struct{
__REG32 BWDRAM  : 2;     
__REG32         :30;     
} __dbwc_bits;

/* 11.6.2 DRAM Control Register (DRMC) */
typedef struct{
__REG32 AMUX    : 2;     
__REG32 ARCH    : 1;     
__REG32         : 1;     
__REG32 PRELAT  : 1;     
__REG32         : 1;     
__REG32 PDWN    : 1;     
__REG32 RFRSH   : 1;     
__REG32         :24;     
} __drmc_bits;

/* 11.6.3 DRAM Characteristic Parameter Control Register (DRPC) */
typedef struct{
__REG32 DRAMSPEC  : 4;     
__REG32           :28;     
} __drpc_bits;

/* 11.6.4 SDRAM Mode Register (SDMD) */
typedef struct{
__REG32 LTMODE    : 1;     
__REG32           : 6;     
__REG32 MODEWR    : 1;     
__REG32           :24;     
} __sdmd_bits;

/* 11.6.5 DRAM Command Register (DCMD) */
typedef struct{
__REG32 DRCMD     : 3;     
__REG32           :29;     
} __dcmd_bits;

/* 11.6.6 External Input Refresh Cycle Control Register (RFSH) */
typedef struct{
__REG32 RCCON     : 1;     
__REG32           :31;     
} __rfsh_bits;

/* 11.6.7 SDRAM Power-Down Mode Control Register (PDWC) */
typedef struct{
__REG32 PDCNT     : 4;     
__REG32           :28;     
} __pdwc_bits;

/* 11.6.8 Internal Generation Refresh Cycle Control Register (RFGC) */
typedef struct{
__REG32 RFSEL     :13;     
__REG32           :19;     
} __rfgc_bits;

/* 12.4.1 DMA Mode Register (DMAMOD) */
typedef struct{
__REG32 PRI  : 1;     
__REG32      :31;     
} __dmamod_bits;

/* 12.4.2 Status Register (DMAASTA) */
typedef struct{
__REG32 STA0  : 1;     
__REG32 STA1  : 1;     
__REG32 STA2  : 1;     
__REG32 STA3  : 1;     
__REG32       :28;     
} __dmaasta_bits;

typedef struct{
__REG32 STA0  : 1;     
__REG32 STA1  : 1;     
__REG32       :30;     
} __dmabsta_bits;

/* 12.4.3 DMA Completion Status Register (DMAINT) */
typedef struct{
__REG32 IREQ0  : 1;     
__REG32 IREQ1  : 1;     
__REG32 IREQ2  : 1;     
__REG32 IREQ3  : 1;     
__REG32        : 4;     
__REG32 ISTA0  : 1;     
__REG32 ISTA1  : 1;     
__REG32 ISTA2  : 1;     
__REG32 ISTA3  : 1;     
__REG32        : 4;     
__REG32 ISTP0  : 1;     
__REG32 ISTP1  : 1;     
__REG32 ISTP2  : 1;     
__REG32 ISTP3  : 1;     
__REG32        :12;     
} __dmaaint_bits;

typedef struct{
__REG32 IREQ0  : 1;     
__REG32 IREQ1  : 1;     
__REG32        : 6;     
__REG32 ISTA0  : 1;     
__REG32 ISTA1  : 1;     
__REG32        : 6;     
__REG32 ISTP0  : 1;     
__REG32 ISTP1  : 1;     
__REG32        :14;     
} __dmabint_bits;

/* 12.4.4 DMA Channel Mask Registers (DMACMSKn DMAC-A: n = 0 to 3, DMAC-B: n = 0 and 1) */
typedef struct{
__REG32 MSK  : 1;     
__REG32      :31;     
} __dmacmsk_bits;

/* 12.4.5 DMA Transfer Mode Registers (DMACTMODn DMAC-A: n = 0 to 3, DMAC-B: n = 0 and 1) */
typedef struct{
__REG32 ARQ   : 1;     
__REG32 TSIZ  : 2;     
__REG32 SDP   : 1;     
__REG32 DDP   : 1;     
__REG32 BRQ   : 1;     
__REG32 IMK   : 1;     
__REG32       :25;     
} __dmactmod_bits;

/* 12.4.8 DMA Transfer Count Registers (DMACSIZn DMAC-A: n = 0 to 3, DMAC-B: n = 0 and 1) */
typedef struct{
__REG32 CSIZ  :17;     
__REG32       :15;     
} __dmacsiz_bits;

/* 13.4.1 SIM Card Select Register (SIMCSR) */
typedef struct{
__REG8  SC1   : 1;
__REG8        : 2;
__REG8  RIU   : 1;
__REG8        : 1;
__REG8  SC6   : 1;
__REG8        : 2;
} __simcsr_bits;

/* 13.4.2 SIM Clock Configuration Register (SIMCCR) */
typedef struct{
__REG8  AC    : 3;
__REG8        : 1;
__REG8  CST   : 1;
__REG8  SHL   : 1;
__REG8        : 2;
} __simccr_bits;

/* 13.4.4 SIM UART Configuration Register 2 (SIMUCR2) */
typedef struct{
__REG8  PSC       : 1;
__REG8            : 1;
__REG8  AUTOCOV   : 1;
__REG8            : 3;
__REG8  DISTBERBF : 1;
__REG8  DISCRDDET : 1;
} __simucr2_bits;

/* 13.4.6 SIM UART Configuration Register 1 (SIMUCR1) */
typedef struct{
__REG8  CONV      : 1;
__REG8  SS        : 1;
__REG8  LCT       : 1;
__REG8  T_R       : 1;
__REG8  PROT      : 1;
__REG8            : 1;
__REG8  FIP       : 1;
__REG8            : 1;
} __simucr1_bits;

/* 13.4.7 SIM Power Control Register (SIMPCR) */
typedef struct{
__REG8  START     : 1;
__REG8            : 1;
__REG8  RSTIN     : 1;
__REG8            : 1;
__REG8  VCCL      : 2;
__REG8            : 2;
} __simpcr_bits;

/* 13.4.12 SIM Mixed Status Register (SIMMSR) */
/* 13.4.13 SIM FIFO Control Register (SIMFCR) */
typedef union{
  // SIMMSRx
  struct{
  __REG8  TBE_RBF   : 1;
  __REG8  EDCER     : 1;
  __REG8            : 2;
  __REG8  CRED      : 1;
  __REG8  BGT       : 1;
  __REG8  FE        : 1;
  __REG8  CRDLVL    : 1;
  };
  // SIMFCRx
  struct{
  __REG8            : 4;
  __REG8  PEC       : 3;
  __REG8            : 1;
  };
} __simmsr_bits;

/* 13.4.16 SIM UART Status Register (SIMUSR) */
typedef struct{
__REG8  TBE_RBF   : 1;
__REG8  FER       : 1;
__REG8  OVR       : 1;
__REG8  PE        : 1;
__REG8  EA        : 1;
__REG8  TO1       : 1;
__REG8  CRDDET    : 1;
__REG8  TO3       : 1;
} __simusr_bits;

/* 13.4.17 SIM Error Detection Code Register (SIMEDC) */
typedef struct{
__REG8            : 4;
__REG8  EDCEN     : 1;
__REG8  EDCSEL    : 1;
__REG8  EDCTX     : 1;
__REG8            : 1;
} __simedc_bits;

/* 14.4.1 LCD Timing Register 1 (LCDCTMG1) */
typedef struct{
__REG32 ADT     : 9;
__REG32 LPW     : 4;
__REG32         : 3;
__REG32 HFP     : 8;
__REG32 HBP     : 8;
} __lcdctmg1_bits;

/* 14.4.2 LCD Timing Register 2 (LCDCTMG2) */
typedef struct{
__REG32 LPP     : 9;
__REG32 FPW     : 4;
__REG32         : 3;
__REG32 VFP     : 6;
__REG32         : 2;
__REG32 VBP     : 6;
__REG32         : 2;
} __lcdctmg2_bits;

/* 14.4.3 LCD Timing Register 3 (LCDCTMG3) */
typedef struct{
__REG32 RCD     : 5;
__REG32 LCLKON  : 1;
__REG32 FPPOL   : 1;
__REG32 LPPOL   : 1;
__REG32 CPPOL   : 1;
__REG32 DFF     : 1;
__REG32 DF      : 5;
__REG32 OEPOL   : 1;
__REG32 CPBLK   : 1;
__REG32 LPBLK   : 1;
__REG32         :14;
} __lcdctmg3_bits;

/* 14.4.4 LCD Control Register (LCDCCTRL) */
typedef struct{
__REG32 LCDEN   : 1;
__REG32         :13;
__REG32 DPDMOD  : 1;
__REG32         :17;
} __lcdcctlr_bits;

/* 14.4.5 Status Register (LCDCSTS) */
typedef struct{
__REG32 VBLANK  : 1;
__REG32 VSYNC   : 1;
__REG32 HBLANK  : 1;
__REG32 HSYNC   : 1;
__REG32         :28;
} __lcdcsts_bits;

/* 14.4.6 Interrupt Source Register (LCDCINT) */
typedef struct{
__REG32 VBNKINT : 1;
__REG32 VSINT   : 1;
__REG32         :30;
} __lcdcint_bits;

/* 14.4.7 Mask Register(LCDCMASK) */
typedef struct{
__REG32 VBMASK  : 1;
__REG32 VSMASK  : 1;
__REG32         :30;
} __lcdcmask_bits;

/* 14.4.8 Interrupt Clear Register (LCDCINTCLR) */
typedef struct{
__REG32 VBCLR   : 1;
__REG32 VSCLR   : 1;
__REG32         :30;
} __lcdcintclr_bits;

/* 15.6.1 USB Configuration Register (USBConfig) */
typedef struct{
__REG32 FFBUFSELN0  : 1;
__REG32             : 1;
__REG32 EXBUFENB0   : 1;
__REG32             : 1;
__REG32 TRMODE      : 2;
__REG32             :26;
} __usbcfg_bits;

/* 15.6.2 DMA Control Register (DMACtl) */
typedef struct{
__REG32             : 8;
__REG32 DREQltvl    : 4;
__REG32             :20;
} __dmactrl_bits;

/* 15.6.3 Reset Power Down Control Register (RstPDownCtl) */
typedef struct{
__REG32 SOFTRST     : 1;
__REG32 CLKSTOP     : 1;
__REG32 BUSY        : 1;
__REG32             :29;
} __rstpdownctrl_bits;

/* 15.6.4 Host Control Register (HostCtl) */
typedef struct{
__REG32 DMAIRQMASK  : 1;
__REG32 OHCIIRQMASK : 1;
__REG32             :30;
} __hostctrl_bits;

/* 15.6.5 Interrupt Status Register (SttTrnsCnt) */
typedef struct{
__REG32 DMAIRQ      : 1;
__REG32 OHCIIRQ     : 1;
__REG32             :30;
} __stttrnsctrl_bits;

/* 15.6.6 Packet Data Transfer Request Register (PktDataTrnsReq) */
typedef struct{
__REG32 DMADIR      : 1;
__REG32             : 1;
__REG32 DMASTART    :30;
} __pktdatatrnsreq_bits;

/* 15.6.7 Internal RAM Address Setup Register (RamAdr) */
typedef struct{
__REG32               :12;
__REG32 IRAMBASE13_12 : 2;
__REG32 IRAMBASE      :18;
} __ramadr_bits;

/* 15.6.9 USB Port Monitor Register (USBPortMon) */
typedef struct{
__REG32 PORT0ENB      : 1;
__REG32 PORT0IN       : 2;
__REG32               :29;
} __usbportmon_bits;

/* 15.6.10 USB Port Control Register (USBPortCtl) */
typedef struct{
__REG32 GN_SE_ENB     : 1;
__REG32 GN_SE_VAL     : 1;
__REG32               : 2;
__REG32 PCONTN_ENB    : 1;
__REG32 PCONTN_VAL    : 1;
__REG32               :26;
} __usbportctrl_bits;

/* HcRevision Register */
typedef struct {
  __REG32 REV               : 8;
  __REG32                   :24;
} __HcRevision_bits;

/* HcControl Register */
typedef struct {
  __REG32 CBSR              : 2;
  __REG32 PLE               : 1;
  __REG32 IE                : 1;
  __REG32 CLE               : 1;
  __REG32 BLE               : 1;
  __REG32 HCFS              : 2;
  __REG32 IR                : 1;
  __REG32 WC                : 1;
  __REG32 RWE               : 1;
  __REG32                   :21;
} __HcControl_bits;

/* HcCommandStatus Register */
typedef struct {
  __REG32 HCR               : 1;
  __REG32 CLF               : 1;
  __REG32 BLF               : 1;
  __REG32 OCR               : 1;
  __REG32                   :12;
  __REG32 SOC               : 2;
  __REG32                   :14;
} __HcCommandStatus_bits;

/* HcInterruptStatus Register */
typedef struct {
  __REG32 SO                : 1;
  __REG32 WDH               : 1;
  __REG32 SF                : 1;
  __REG32 RD                : 1;
  __REG32 UE                : 1;
  __REG32 FNO               : 1;
  __REG32 RHSC              : 1;
  __REG32                   :23;
  __REG32 OC                : 1;
  __REG32                   : 1;
} __HcInterruptStatus_bits;

/* HcInterruptEnable Register
   HcInterruptDisable Register */
typedef struct {
  __REG32 SO                : 1;
  __REG32 WDH               : 1;
  __REG32 SF                : 1;
  __REG32 RD                : 1;
  __REG32 UE                : 1;
  __REG32 FNO               : 1;
  __REG32 RHSC              : 1;
  __REG32                   :23;
  __REG32 OC                : 1;
  __REG32 MIE               : 1;
} __HcInterruptEnable_bits;

/* HcHCCA Register */
typedef struct {
  __REG32                   : 8;
  __REG32 HCCA              :24;
} __HcHCCA_bits;

/* HcPeriodCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 PCED              :28;
} __HcPeriodCurrentED_bits;

/* HcControlHeadED Registerr */
typedef struct {
  __REG32                   : 4;
  __REG32 CHED              :28;
} __HcControlHeadED_bits;

/* HcControlCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 CCED              :28;
} __HcControlCurrentED_bits;

/* HcBulkHeadED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 BHED              :28;
} __HcBulkHeadED_bits;

/* HcBulkCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 BCED              :28;
} __HcBulkCurrentED_bits;

/* HcDoneHead Register */
typedef struct {
  __REG32                   : 4;
  __REG32 DH                :28;
} __HcDoneHead_bits;

/* HcFmInterval Register */
typedef struct {
  __REG32 FI                :14;
  __REG32                   : 2;
  __REG32 FSMPS             :15;
  __REG32 FIT               : 1;
} __HcFmInterval_bits;

/* HcFmRemaining Register */
typedef struct {
  __REG32 FR                :14;
  __REG32                   :17;
  __REG32 FRT               : 1;
} __HcFmRemaining_bits;

/* HcPeriodicStart Register */
typedef struct {
  __REG32 PS                :14;
  __REG32                   :18;
} __HcPeriodicStart_bits;

/* HcLSThreshold Register */
typedef struct {
  __REG32 LST               :12;
  __REG32                   :20;
} __HcLSThreshold_bits;

/* HcRhDescriptorA Register */
typedef struct {
  __REG32 NDP               : 8;
  __REG32 PSM               : 1;
  __REG32 NPS               : 1;
  __REG32 DT                : 1;
  __REG32 OCPM              : 1;
  __REG32 NOCP              : 1;
  __REG32                   :11;
  __REG32 POTPGT            : 8;
} __HcRhDescriptorA_bits;

/* HcRhDescriptorB Register */
typedef struct {
  __REG32                   : 1;
  __REG32 DR                : 1;
  __REG32                   :15;
  __REG32 PPCM              : 1;
  __REG32                   :14;
} __HcRhDescriptorB_bits;

/* HcRhStatus Register */
typedef struct {
  __REG32 LPS               : 1;
  __REG32 OCI               : 1;
  __REG32                   :13;
  __REG32 DRWE              : 1;
  __REG32 LPSC              : 1;
  __REG32 CCIC              : 1;
  __REG32                   :13;
  __REG32 CRWE              : 1;
} __HcRhStatus_bits;

/* HcRhPortStatus Register */
typedef struct {
  __REG32 CCS               : 1;
  __REG32 PES               : 1;
  __REG32 PSS               : 1;
  __REG32 POCI              : 1;
  __REG32 PRS               : 1;
  __REG32                   : 3;
  __REG32 PPS               : 1;
  __REG32 LSDA              : 1;
  __REG32                   : 6;
  __REG32 CSC               : 1;
  __REG32 PESC              : 1;
  __REG32 PSSC              : 1;
  __REG32 OCIC              : 1;
  __REG32 PRSC              : 1;
  __REG32                   :11;
} __HcRhPortStatus_bits;

/* 16.4.1 bmRequestType Set-up Register (bmRequestType) */
typedef struct {
  __REG8 RECIPIENT  : 5;
  __REG8 TYPE       : 2;
  __REG8 DIR        : 1;
}__bmRequestType_bits;

/* 16.4.9 Device address register (DVCADR) */
typedef struct {
  __REG8 DVCADR     : 7;
  __REG8            : 1;
}__dvcadr_bits;

/* 16.4.10 Interrupt Status Register 1 (INTSTAT1) */
typedef struct {
  __REG8 SURIS      : 1;
  __REG8 EP1PRIS    : 1;
  __REG8 EP2PRIS    : 1;
  __REG8 EP3PRIS    : 1;
  __REG8 EP4PRIS    : 1;
  __REG8 EP5PRIS    : 1;
  __REG8 EP0RPRIS   : 1;
  __REG8 EP0TPRIS   : 1;
} __intstat1_bits;

/* 16.4.11 Interrupt Status Register 2 (INTSTAT2) */
typedef struct {
  __REG8 SOFIS      : 1;
  __REG8 BRAIS      : 1;
  __REG8 BRDIS      : 1;
  __REG8 DSSIS      : 1;
  __REG8 DASIS      : 1;
  __REG8            : 3;
} __intstat2_bits;

/* 16.4.12 Interrupt Enable Register 1 (INTENBL1) */
typedef struct {
  __REG8 SURIE      : 1;
  __REG8 EP1PRIE    : 1;
  __REG8 EP2PRIE    : 1;
  __REG8 EP3PRIE    : 1;
  __REG8 EP4PRIE    : 1;
  __REG8 EP5PRIE    : 1;
  __REG8 EP0RPRIE   : 1;
  __REG8 EP0TPRIE   : 1;
} __intenbl1_bits;

/* 16.4.13 Interrupt Enable Register 2 (INTENBL2) */
typedef struct {
  __REG8 SOFIE      : 1;
  __REG8 BRAIE      : 1;
  __REG8 BRDIE      : 1;
  __REG8 DSSIE      : 1;
  __REG8 DASIE      : 1;
  __REG8            : 3;
} __intenbl2_bits;

/* 16.4.14 ISO Mode Select Register (ISOMODESEL) */
typedef struct {
  __REG8            : 4;
  __REG8 EP4ISO     : 1;
  __REG8 EP5ISO     : 1;
  __REG8            : 2;
} __isomodesel_bits;

/* 16.4.16 Frame Number Register MSB (FRAMEMSB) */
typedef struct {
  __REG8 FRAMEMSB   : 3;
  __REG8            : 5;
} __framemsb_bits;

/* 16.4.17 System Control Register (SYSCON) */
typedef struct {
  __REG8 SOFTRST    : 1;
  __REG8 POWERDOWN  : 1;
  __REG8 EPMODE     : 1;
  __REG8 PUCTL      : 1;
  __REG8 REMOTEWU   : 1;
  __REG8            : 3;
} __syscon_bits;

/* 16.4.18 Polarity Select Register (POLSEL) */
typedef struct {
  __REG8            : 4;
  __REG8 USBINTNPOL : 1;
  __REG8            : 3;
} __polsel_bits;

/* 16.4.19 EP0 Configuration Register (EP0CONF) */
typedef struct {
  __REG8 EPTYPE     : 2;
  __REG8            : 2;
  __REG8 RDY        : 1;
  __REG8            : 3;
} __ep0conf_bits;

/* 16.4.20 EP1, 2, 3, 4, 5 Configuration Register (EP1, 2, 3, 4, 5CONF) */
typedef struct {
  __REG8 EPTYPE     : 2;
  __REG8            : 2;
  __REG8 RDY        : 1;
  __REG8            : 2;
  __REG8 DIR       : 1;
} __epconf_bits;

/* 16.4.21 EP0 Control Register (EP0CONT) */
typedef struct {
  __REG8 STALL      : 1;
  __REG8 RXTOGGLE   : 1;
  __REG8            : 2;
  __REG8 TXTOGGLE   : 1;
  __REG8            : 3;
} __ep0cont_bits;

/* 16.4.22 EP1, 2, 3, 4, 5 Control Register (EP1, 2, 3, 4, 5CONT) */
typedef struct {
  __REG8 STALL      : 1;
  __REG8 TOGGLE     : 1;
  __REG8 FIFOCLR    : 1;
  __REG8            : 5;
} __epcont_bits;

/* 16.4.23 EP0 Payload Register (EP0PLD) */
typedef struct {
  __REG8 SIZE       : 6;
  __REG8            : 2;
} __ep0pld_bits;

/* 16.4.24 EP1, 2 Payload Register (EP1, 2PLD) */
typedef struct {
  __REG8 SIZE       : 7;
  __REG8            : 1;
} __eppld_bits;

/* 16.4.27 EP0 Receive Byte Counter (EP0RXCNT) */
typedef struct {
  __REG8 SIZE       : 6;
  __REG8            : 2;
} __ep0rxcnt_bits;

/* 16.4.28 EP1, 2 Receive Byte Counter (EP1, 2RXCNT) */
typedef struct {
  __REG8 SIZE       : 7;
  __REG8            : 1;
} __eprxcnt_bits;

/* 16.4.31 EP0 Status Register (EP0STAT) */
typedef struct {
  __REG8 RPR        : 1;
  __REG8 TPR        : 1;
  __REG8 SR         : 1;
  __REG8            : 1;
  __REG8 STATE      : 2;
  __REG8            : 2;
} __ep0stat_bits;

/* 16.4.32 EP1, 2, 4, 5 Status Register (EP1, 2, 4, 5STAT) */
typedef struct {
  __REG8 RPR        : 1;
  __REG8 TPR        : 1;
  __REG8            : 6;
} __epstat_bits;

/* 18.4.2 Time Base Counter Control Register (TBGCON) */
typedef struct{
__REG8  WDCKS      : 3;     
__REG8             : 3;     
__REG8  OFINTMODE  : 1;     
__REG8  WDHLT      : 1;     
} __tbgcon_bits;

/* 18.4.3 Interrupt Status Register (INTST) */
typedef struct{
__REG8  RSTSTATUS  : 1;     
__REG8             : 3;     
__REG8  WDTINT     : 1;     
__REG8             : 3;     
} __intst_bits;

/* 19.4.1 A/D Converter Control 0 Register (ADCON0) */
typedef struct{
__REG16 ADSNM  : 3;     
__REG16        : 1;     
__REG16 ADRUN  : 1;     
__REG16        : 1;     
__REG16 SCNC   : 1;     
__REG16        : 9;     
} __adcon0_bits;

/* 19.4.2 A/D Converter Control 1 Register (ADCON1) */
typedef struct{
__REG16 ADSTM  : 3;     
__REG16        : 1;     
__REG16 STS    : 1;     
__REG16        :11;     
} __adcon1_bits;

/* 19.4.3 A/D Converter Control 2 Register (ADCON2) */
typedef struct{
__REG16 ACKSEL  : 2;     
__REG16         :14;     
} __adcon2_bits;

/* 19.4.4 A/D Conversion Interrupt Control Register (ADINT) */
typedef struct{
__REG16 INTSN   : 1;     
__REG16 INTST   : 1;     
__REG16 ADSNIE  : 1;     
__REG16 ADSTIE  : 1;     
__REG16         :12;     
} __adint_bits;

/* 19.4.5 A/D Converter Forced Interrupt Generation Register (ADFINT) */
typedef struct{
__REG16 ADFAS  : 1;     
__REG16        :15;     
} __adfint_bits;

/* 19.4.6 A/D Conversion Result (0–7) Registers (ADR0–ADR7) */
typedef struct{
__REG16 DT  :12;     
__REG16     : 4;     
} __adr_bits;

/* 20.4.1 GPIO Port Output Register n (POn: n = 0 to 7) */
typedef struct{
__REG8  PO0  : 1;     
__REG8  PO1  : 1;     
__REG8  PO2  : 1;     
__REG8  PO3  : 1;     
__REG8  PO4  : 1;     
__REG8  PO5  : 1;     
__REG8  PO6  : 1;     
__REG8  PO7  : 1;     
} __po_bits;

/* 20.4.2 GPIO Port Input Register n (PIn: n = 0 to 7) */
typedef struct{
__REG8  PI0  : 1;     
__REG8  PI1  : 1;     
__REG8  PI2  : 1;     
__REG8  PI3  : 1;     
__REG8  PI4  : 1;     
__REG8  PI5  : 1;     
__REG8  PI6  : 1;     
__REG8  PI7  : 1;     
} __pi_bits;

/* 20.4.3 GPIO Port Mode Register n (PMn: n = 0 to 7) */
typedef struct{
__REG8  PM0  : 1;     
__REG8  PM1  : 1;     
__REG8  PM2  : 1;     
__REG8  PM3  : 1;     
__REG8  PM4  : 1;     
__REG8  PM5  : 1;     
__REG8  PM6  : 1;     
__REG8  PM7  : 1;     
} __pm_bits;

/* 20.4.4 GPIO Interrupt Enable Register n (IEn: n = 0 to 7) */
typedef struct{
__REG8  IE0  : 1;     
__REG8  IE1  : 1;     
__REG8  IE2  : 1;     
__REG8  IE3  : 1;     
__REG8  IE4  : 1;     
__REG8  IE5  : 1;     
__REG8  IE6  : 1;     
__REG8  IE7  : 1;     
} __ie_bits;

/* 20.4.5 GPIO Interrupt Mode Register n (IMn: n = 0 to 7) */
typedef struct{
__REG32 IMR0  : 3;     
__REG32       : 1;     
__REG32 IMR1  : 3;     
__REG32       : 1;     
__REG32 IMR2  : 3;     
__REG32       : 1;     
__REG32 IMR3  : 3;     
__REG32       : 1;     
__REG32 IMR4  : 3;     
__REG32       : 1;     
__REG32 IMR5  : 3;     
__REG32       : 1;     
__REG32 IMR6  : 3;     
__REG32       : 1;     
__REG32 IMR7  : 3;     
__REG32       : 1;     
} __im_bits;

/* 20.4.6 GPIO Interrupt Status Register n (ISn: n = 0 to 7) */
typedef struct{
__REG8  IS0  : 1;     
__REG8  IS1  : 1;     
__REG8  IS2  : 1;     
__REG8  IS3  : 1;     
__REG8  IS4  : 1;     
__REG8  IS5  : 1;     
__REG8  IS6  : 1;     
__REG8  IS7  : 1;     
} __is_bits;

/* 21.4.1 I2C Slave Address Register (I2CSADR0–1) */
typedef struct{
__REG16          : 1;     
__REG16 I2CSADR  :10;     
__REG16          : 5;     
} __i2csadr_bits;

/* 21.4.2 I2C Control Register (I2CCTL0–1) */
typedef struct{
__REG16 I2CMD         : 2;     
__REG16 I2CRSTA       : 1;     
__REG16 I2CTXAK       : 1;     
__REG16 I2CMTX        : 1;     
__REG16 I2CMSTA       : 1;     
__REG16 I2CAASIE      : 1;     
__REG16 I2CMEN        : 1;     
__REG16 I2CALIE       : 1;     
__REG16 I2CCFIE       : 1;     
__REG16 I2CNKARB      : 1;     
__REG16 I2CSTPIE      : 1;     
__REG16 I2C_DR_LDEN   : 1;     
__REG16 I2CCS         : 1;     
__REG16 I2CNSTPIE     : 1;     
__REG16 I2CISTPIE     : 1;     
} __i2cctl_bits;

/* 21.4.3 I2C Status Register (I2CSR0–1) */
typedef struct{
__REG16 I2CRXAK   : 1;     
__REG16 I2CMIF    : 1;     
__REG16 I2CSRW    : 1;     
__REG16 I2CDR_LD  : 1;     
__REG16 I2CMAL    : 1;     
__REG16 I2CMBB    : 1;     
__REG16 I2CMAAS   : 1;     
__REG16 I2CMCF    : 1;     
__REG16 I2CRBUF   : 1;     
__REG16 I2CSTP    : 1;     
__REG16 I2CDRSTA  : 1;
__REG16 I2CAKMON  : 1;
__REG16           : 2;
__REG16 I2CNSTP   : 1;
__REG16 I2CISTP   : 1;
} __i2csr_bits;

/* 21.4.4 I2C Data Register (I2CDR0–1) */
typedef struct{
__REG16 I2CDA  : 8;     
__REG16        : 8;     
} __i2cdr_bits;

/* 21.4.5 I2C Bus Monitor Register (I2CMON0–1) */
typedef struct{
__REG16 I2CSCL  : 1;     
__REG16 I2CSDA  : 1;     
__REG16         : 2;     
__REG16 DBMON1  : 4;     
__REG16 DBMON2  : 4;     
__REG16 DBMON3  : 4;     
} __i2cmon_bits;

/* 21.4.6 I2C Bus Transfer Rate Setup Counter (I2CBC0–1) */
typedef struct{
__REG16 I2CBC  : 7;     
__REG16        : 9;     
} __i2cbc_bits;

/* 22.4.2 1-Second Digit Register (S1) */
typedef struct{
__REG8  s1  : 4;     
__REG8      : 4;     
} __s1_bits;

/* 22.4.3 10-Second Digit Register (S10) */
typedef struct{
__REG8  s10  : 3;     
__REG8       : 5;     
} __s10_bits;

/* 22.4.4 1-Minute Digit Register (M1) */
typedef struct{
__REG8  m1  : 4;     
__REG8      : 4;     
} __m1_bits;

/* 22.4.5 10-Minute Digit Register (M10) */
typedef struct{
__REG8  m10  : 3;     
__REG8       : 5;     
} __m10_bits;

/* 22.4.6 1-Hour Digit Register (H1) */
typedef struct{
__REG8  h1  : 4;     
__REG8      : 4;     
} __h1_bits;

/* 22.4.7 PM/AM 10-Hour Digit Register (H10) */
typedef struct{
__REG8  h10    : 2;     
__REG8  PM_AM  : 1;     
__REG8         : 5;     
} __h10_bits;

/* 22.4.8 1-Day Digit Register (D1) */
typedef struct{
__REG8  d1  : 4;     
__REG8      : 4;     
} __d1_bits;

/* 22.4.9 10-Day Digit Register (D10) */
typedef struct{
__REG8  d10  : 2;     
__REG8       : 6;     
} __d10_bits;

/* 22.4.10 1-Month Digit Register (MO1) */
typedef struct{
__REG8  mo1  : 4;     
__REG8       : 4;     
} __mo1_bits;

/* 22.4.11 10-Month Digit Register (MO10) */
typedef struct{
__REG8  mo10  : 1;     
__REG8        : 7;     
} __mo10_bits;

/* 22.4.12 1-Year Digit Register (Y1) */
typedef struct{
__REG8  y1  : 4;     
__REG8      : 4;     
} __y1_bits;

/* 22.4.13 10-Year Digit Register (Y10) */
typedef struct{
__REG8  y10  : 4;     
__REG8       : 4;     
} __y10_bits;

/* 22.4.14 Day-of-the-Week Register (W) */
typedef struct{
__REG8  w  : 3;     
__REG8     : 5;     
} __w_bits;

/* 22.4.15 Control Register D (CD) */
typedef struct{
__REG8  HOLD     : 1;     
__REG8  BUSY     : 1;     
__REG8  IRQFLAG  : 1;     
__REG8  _30sADJ  : 1;     
__REG8           : 4;     
} __cd_bits;

/* 22.4.16 Control Register E (CE) */
typedef struct{
__REG8  MASK        : 1;     
__REG8  ITRPT_STND  : 1;     
__REG8  T           : 2;     
__REG8              : 4;     
} __ce_bits;

/* 22.4.17 Control Register F (CF) */
typedef struct{
__REG8  REST    : 1;     
__REG8  STOP    : 1;     
__REG8  _24_12  : 1;     
__REG8  TEST    : 1;     
__REG8          : 4;     
} __cf_bits;

/* 23.4.9 UART Interrupt Enable Register n (UARTIERn: n = 0, 1) */
typedef struct {
__REG8  ERBFI  : 1;     
__REG8  ETBEI  : 1;     
__REG8  ELSI   : 1;     
__REG8  EDSSI  : 1;     
__REG8         : 4;     
} __uartier_bits;

/* 23.4.5 UART FIFO Control Register n (UARTFCRn: n = 0, 1)
   23.4.8 UART Interrupt Identification Register n (UARTIIRn: n = 0, 1) */
typedef union{
  //UARTIIRx
  struct {
__REG8  INTP     : 1;     
__REG8  INTID    : 2;     
__REG8  TOI      : 1;     
__REG8           : 2;     
__REG8  FIFOEN   : 2;     
  };
  //UARTFCRx
  struct {
__REG8  FIFOE    : 1;     
__REG8  RFR      : 1;     
__REG8  TFR      : 1;     
__REG8  DMS      : 1;     
__REG8  OVRmask  : 1;     
__REG8           : 1;     
__REG8  RFTL     : 2;     
  };
  // UARTDLHx
  struct {
__REG8  DV       : 2;     
__REG8           : 6;     
  };
} __uartfcriir_bits;

/* 23.4.3 UART Line Control Register n (UARTLCRn: n = 0, 1) */
typedef struct{
__REG8  WLS   : 2;     
__REG8  SBS   : 1;     
__REG8  PE    : 1;     
__REG8  EPS   : 1;     
__REG8  SP    : 1;     
__REG8  BC    : 1;     
__REG8  DLAB  : 1;     
} __uartlcr_bits;

/* 23.4.4 UART Line Status Register n (UARTLSRn: n = 0, 1) */
typedef struct{
__REG8  DR    : 1;     
__REG8  OE    : 1;     
__REG8  PE    : 1;     
__REG8  FE    : 1;     
__REG8  BI    : 1;     
__REG8  THRE  : 1;     
__REG8  TEMT  : 1;     
__REG8  RFE   : 1;     
} __uartlsr_bits;

/* 23.4.6 UART Modem Control Register n (UARTMCRn: n = 0, 1) */
typedef struct{
__REG8  DTR   : 1;     
__REG8  RTS   : 1;     
__REG8        : 2;     
__REG8  LOOP  : 1;     
__REG8        : 3;     
} __uartmcr_bits;

/* 23.4.7 UART Modem Status Register n (UARTMSRn: n = 0, 1) */
typedef struct{
__REG8  DCTS  : 1;     
__REG8  DDSR  : 1;     
__REG8  TERI  : 1;     
__REG8  DDCD  : 1;     
__REG8  CTS   : 1;     
__REG8  DSR   : 1;     
__REG8  RI    : 1;     
__REG8  DCD   : 1;     
} __uartmsr_bits;


/* 24.4.1 SPI Control Register (SPCRn: n = 0, 1) */
typedef struct{
__REG32 SPE     : 1;     
__REG32 MSTR    : 1;     
__REG32         : 1;     
__REG32 MODFEN  : 1;     
__REG32 LSBF    : 1;     
__REG32 CPHA    : 1;     
__REG32 CPOL    : 1;     
__REG32         : 1;     
__REG32 TFIE    : 1;     
__REG32 RFIE    : 1;     
__REG32 FIE     : 1;     
__REG32 ORIE    : 1;     
__REG32 MDFIE   : 1; 
__REG32         : 3;
__REG32 TFIC    : 4;     
__REG32 RFIC    : 4;     
__REG32 FICLR   : 1;     
__REG32 SSZ     : 1;     
__REG32 SOZ     : 1;     
__REG32 MOZ     : 1;     
__REG32         : 4;     
} __spcr_bits;

/* 24.4.2 SPI Baud Rate Register (SPBRRn: n = 0, 1) */
typedef struct{
__REG32 SPBR  :10;     
__REG32 SIZE  : 1;     
__REG32       : 1;     
__REG32 LEAD  : 2;     
__REG32 LAG   : 2;     
__REG32 DTL   : 9;     
__REG32       : 7;     
} __spbrr_bits;

/* 24.4.3 SPI Status Register (SPSRn: n = 0, 1) */
typedef struct{
__REG32 TFI   : 1;     
__REG32 RFI   : 1;     
__REG32 FI    : 1;     
__REG32 ORF   : 1;     
__REG32 MDF   : 1;     
__REG32 SPIF  : 1;     
__REG32 TFD   : 5;     
__REG32 RFD   : 5;     
__REG32 WOF   : 1;     
__REG32 TFF   : 1;     
__REG32 TFE   : 1;     
__REG32 RFF   : 1;     
__REG32 RFE   : 1;     
__REG32       :11;     
} __spsr_bits;

/* 24.4.4 SPI Write Data Register (SPDWRn: n = 0, 1) */
typedef struct{
__REG32 DATA  :16;     
__REG32       :16;     
} __spdwr_bits;

/* 24.4.5 SPI Read Data Register (SPDRRn: n = 0, 1) */
typedef struct{
__REG32 DATA  :16;     
__REG32       :16;     
} __spdrr_bits;

/* 25.4.1 Timer Control Register n (FTMnCON: n = 0 to 5) */
typedef struct{
__REG16 FTMCLK  : 3;     
__REG16 MOD     : 2;     
__REG16         :11;     
} __ftmcon_bits;

/* 25.4.2 Timer Status Register n (FTMnST: n = 0 to 5) */
typedef struct{
__REG16 CM_CAPEV  : 1;     
__REG16 OVF       : 1;     
__REG16           :14;     
} __ftmst_bits;

/* 25.4.6 Timer Input/Output Level Register n (FTMnIOLV: n = 0 to 5) */
typedef struct{
__REG16 IOLV  : 2;     
__REG16       :14;     
} __ftmiolv_bits;

/* 25.4.7 Timer Output Level Register n (FTMnOUT: n = 0 to 5) */
typedef struct{
__REG16 FTMOUT  : 1;     
__REG16         :15;     
} __ftmout_bits;

/* 25.4.8 Timer Interrupt Enable Register n (FTMnIER: n = 0 to 5) */
typedef struct{
__REG16 CMOIE_CAPIE  : 1;     
__REG16 OVFIE        : 1;     
__REG16              :14;     
} __ftmier_bits;

/* 25.4.9 Timer Enable (FTMEN) Register */
typedef struct{
__REG16 FTMEN   : 6;     
__REG16         :10;     
} __ftmen_bits;

/* 25.4.10 Timer Disable (FTMDIS) Register */
typedef struct{
__REG16 FTMDIS    : 6;     
__REG16           :10;     
} __ftmdis_bits;

/* 27.4.1 Mask Status Register (MASK) */
typedef struct{
__REG8  MASK      : 1;     
__REG8            : 7;     
} __mask_bits;

/* 27.4.2 Core-Power Return Condition Register (INTPC) */
typedef struct{
__REG8  INTPC0    : 2;     
__REG8  INTPC1    : 1;     
__REG8            : 5;     
} __intpc_bits;

/* 27.4.3 CKE Control Register for SDRAM at Standby (SDRAMCKE) */
typedef struct{
__REG8  SDRAMCKE  : 1;
__REG8            : 7;
} __sdramcke_bits;

/* 27.4.4 Core-Power Return Input Latch Clear Register (PLCLR) */
typedef struct{
__REG8  LCLR      : 1;
__REG8            : 7;
} __plclr_bits;

/* 27.4.5 Core-Power Return Input Status Latch (INTPCS) */
typedef struct{
__REG8  INTPCS0   : 1;
__REG8  INTPCS1   : 1;
__REG8            : 6;
} __intpcs_bits;

/* 27.4.6 Core-Power Return Input Status (RESUMEIN) */
typedef struct{
__REG8  RESUME    : 1;
__REG8  RTCINT    : 1;
__REG8            : 6;
} __resumein_bits;

/* 27.4.7 CS Control Register during Standby (STBCS) */
typedef struct{
__REG8  ROMCSO    : 1;
__REG8  RAMCSO    : 1;
__REG8  IOCS0O    : 1;
__REG8  IOCS1O    : 1;
__REG8  ROMCSM    : 1;
__REG8  RAMCSM    : 1;
__REG8  IOCS0M    : 1;
__REG8  IOCS1M    : 1;
} __stbcs_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 ** Memory Control
 **
 ***************************************************************************/
__IO_REG32_BIT(RMPCON,                0xB8000010,__READ_WRITE ,__rmpcon_bits);

/***************************************************************************
 **
 ** Clock/Reset
 **
 ***************************************************************************/
__IO_REG32_BIT(IDR,                   0xB8000000,__READ       ,__idr_bits);
__IO_REG32_BIT(CLKSTP,                0xB8000004,__READ_WRITE ,__clkstp_bits);
__IO_REG32_BIT(PECLKCNT,              0xB7000000,__READ_WRITE ,__peclkcnt_bits);
__IO_REG32_BIT(PERSTCNT,              0xB7000004,__READ_WRITE ,__perstcnt_bits);
__IO_REG32_BIT(CLKCNT,                0xB7000010,__READ_WRITE ,__clkcnt_bits);
__IO_REG32_BIT(CLKSTPCNT,             0xB7000014,__READ_WRITE ,__clkstpcnt_bits);
__IO_REG32_BIT(CKWT,                  0xB7000018,__READ_WRITE ,__ckwt_bits);

/***************************************************************************
 **
 ** LSI Control Functions
 **
 ***************************************************************************/
__IO_REG32_BIT(DMAARQCNT,             0xB7000020,__READ_WRITE ,__dmaarqcnt_bits);
__IO_REG32_BIT(DMABRQCNT,             0xB7000024,__READ_WRITE ,__dmabrqcnt_bits);
__IO_REG8_BIT( I2CNF,                 0xB7000028,__READ_WRITE ,__i2cnf_bits);
__IO_REG32_BIT(AHBRAMCNT,             0xB700002C,__READ_WRITE ,__ahbramcnt_bits);
__IO_REG32_BIT(FTMSEL,                0xB7000030,__READ_WRITE ,__ftmsel_bits);
__IO_REG32_BIT(EXDMACNT,              0xB700003C,__READ_WRITE ,__exdmacnt_bits);
__IO_REG32_BIT(PORTSEL1,              0xB7000040,__READ_WRITE ,__portsel1_bits);
__IO_REG32_BIT(PORTSEL2,              0xB7000044,__READ_WRITE ,__portsel2_bits);
__IO_REG32_BIT(PORTSEL3,              0xB7000048,__READ_WRITE ,__portsel3_bits);
__IO_REG32_BIT(PORTSEL4,              0xB700004C,__READ_WRITE ,__portsel4_bits);

/***************************************************************************
 **
 ** Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQ,                   0x78000000,__READ       ,__irq_bits);
__IO_REG32_BIT(IRQS,                  0x78000004,__READ_WRITE ,__irqs_bits);
__IO_REG32_BIT(FIQ,                   0x78000008,__READ       ,__fiq_bits);
__IO_REG32_BIT(FIQRAW,                0x7800000C,__READ       ,__fiqraw_bits);
__IO_REG32_BIT(FIQEN,                 0x78000010,__READ_WRITE ,__fiqen_bits);
__IO_REG32_BIT(IRN,                   0x78000014,__READ       ,__irn_bits);
__IO_REG32_BIT(CIL,                   0x78000018,__READ_WRITE ,__cil_bits);
__IO_REG32_BIT(ILC0,                  0x78000020,__READ_WRITE ,__ilc0_bits);
__IO_REG32_BIT(ILC1,                  0x78000024,__READ_WRITE ,__ilc1_bits);
__IO_REG32(    CILCL,                 0x78000028,__WRITE);    
__IO_REG32_BIT(CILE,                  0x7800002C,__READ       ,__cile_bits);
__IO_REG32_BIT(EXIRS,                 0x7BF00000,__READ       ,__exirs_bits);
__IO_REG32_BIT(EXIRCL,                0x7BF00004,__WRITE      ,__exircl_bits);
__IO_REG32_BIT(EXIRQA,                0x7BF00010,__READ       ,__exirqa_bits);
__IO_REG32_BIT(EXILCA,                0x7BF00018,__READ_WRITE ,__exilca_bits);
__IO_REG32_BIT(EXIRQSA,               0x7BF0001C,__READ       ,__exirqsa_bits);
__IO_REG32_BIT(EXIRQB,                0x7BF00020,__READ_WRITE ,__exirqb_bits);
__IO_REG32_BIT(EXIDM,                 0x7BF00024,__READ_WRITE ,__exidm_bits);
__IO_REG32_BIT(EXILCB,                0x7BF00028,__READ_WRITE ,__exilcb_bits);
__IO_REG32_BIT(EXIRQSB,               0x7BF0002C,__READ_WRITE ,__exirqsb_bits);
__IO_REG32_BIT(EXIRQC,                0x7BF00030,__READ       ,__exirqc_bits);
__IO_REG32_BIT(EXILCC,                0x7BF00038,__READ_WRITE ,__exilcc_bits);
__IO_REG32_BIT(EXIRQSC,               0x7BF0003C,__READ       ,__exirqsc_bits);
__IO_REG32_BIT(EXFIQ,                 0x7BF00080,__READ_WRITE ,__exfiq_bits);
__IO_REG32_BIT(EXFIDM,                0x7BF00084,__READ_WRITE ,__exfidm_bits);
__IO_REG32_BIT(EXINTCNT,              0xB7000034,__READ_WRITE ,__exintcnt_bits);

/***************************************************************************
 **
 ** Cache Memory
 **
 ***************************************************************************/
__IO_REG32_BIT(CON,                   0x78200004,__READ_WRITE ,__con_bits);
__IO_REG32_BIT(CACHE,                 0x78200008,__READ_WRITE ,__cache_bits);
__IO_REG32(    FLUSH,                 0x7820001C,__WRITE);

/***************************************************************************
 **
 ** External Memory Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(BWC,                   0x78100000,__READ_WRITE ,__bwc_bits);
__IO_REG32_BIT(ROMAC,                 0x78100004,__READ_WRITE ,__romac_bits);
__IO_REG32_BIT(RAMAC,                 0x78100008,__READ_WRITE ,__ramac_bits);
__IO_REG32_BIT(IOAC,                  0x7810000C,__READ_WRITE ,__ioac_bits);

/***************************************************************************
 **
 ** SIO (in µPLAT)
 **
 ***************************************************************************/
__IO_REG32_BIT(SIOBUF,                0xB8002000,__READ_WRITE ,__siobuf_bits);
__IO_REG32_BIT(SIOSTA,                0xB8002004,__READ_WRITE ,__siosta_bits);
__IO_REG32_BIT(SIOCON,                0xB8002008,__READ_WRITE ,__siocon_bits);
__IO_REG32_BIT(SIOBCN,                0xB800200C,__READ_WRITE ,__siobcn_bits);
__IO_REG32_BIT(SIOBT,                 0xB8002014,__READ_WRITE ,__siobt_bits);
__IO_REG32_BIT(SIOTCN,                0xB8002018,__READ_WRITE ,__siotcn_bits);

/***************************************************************************
 **
 ** System Timer
 **
 ***************************************************************************/
__IO_REG32_BIT(TMEN,                  0xB8001004,__READ_WRITE ,__tmen_bits);
__IO_REG16(    TMRLR,                 0xB8001008,__READ_WRITE);
__IO_REG32_BIT(TMOVF,                 0xB8001010,__READ_WRITE ,__tmovf_bits);

/***************************************************************************
 **
 ** DRAMC
 **
 ***************************************************************************/
__IO_REG32_BIT(DBWC,                  0x78180000,__READ_WRITE ,__dbwc_bits);
__IO_REG32_BIT(DRMC,                  0x78180004,__READ_WRITE ,__drmc_bits);
__IO_REG32_BIT(DRPC,                  0x78180008,__READ_WRITE ,__drpc_bits);
__IO_REG32_BIT(SDMD,                  0x7818000C,__READ_WRITE ,__sdmd_bits);
__IO_REG32_BIT(DCMD,                  0x78180010,__READ_WRITE ,__dcmd_bits);
__IO_REG32_BIT(RFSH,                  0x78180014,__READ_WRITE ,__rfsh_bits);
__IO_REG32_BIT(PDWC,                  0x78180018,__READ_WRITE ,__pdwc_bits);
__IO_REG32_BIT(RFGC,                  0x7818001C,__READ_WRITE ,__rfgc_bits);

/***************************************************************************
 **
 ** DMAC
 **
 ***************************************************************************/
__IO_REG32_BIT(DMAAMOD,               0x7BE00000,__READ_WRITE ,__dmamod_bits);
__IO_REG32_BIT(DMAASTA,               0x7BE00004,__READ       ,__dmaasta_bits);
__IO_REG32_BIT(DMAAINT,               0x7BE00008,__READ       ,__dmaaint_bits);
__IO_REG32_BIT(DMAACMSK0,             0x7BE00100,__READ_WRITE ,__dmacmsk_bits);
__IO_REG32_BIT(DMAACTMOD0,            0x7BE00104,__READ_WRITE ,__dmactmod_bits);
__IO_REG32(    DMAACSAD0,             0x7BE00108,__READ_WRITE);
__IO_REG32(    DMAACDAD0,             0x7BE0010C,__READ_WRITE);
__IO_REG32_BIT(DMAACSIZ0,             0x7BE00110,__READ_WRITE ,__dmacsiz_bits);
__IO_REG32(    DMAACCINT0,            0x7BE00114,__WRITE);
__IO_REG32_BIT(DMAACMSK1,             0x7BE00200,__READ_WRITE ,__dmacmsk_bits);
__IO_REG32_BIT(DMAACTMOD1,            0x7BE00204,__READ_WRITE ,__dmactmod_bits);
__IO_REG32(    DMAACSAD1,             0x7BE00208,__READ_WRITE);
__IO_REG32(    DMAACDAD1,             0x7BE0020C,__READ_WRITE);
__IO_REG32_BIT(DMAACSIZ1,             0x7BE00210,__READ_WRITE ,__dmacsiz_bits);
__IO_REG32(    DMAACCINT1,            0x7BE00214,__WRITE);
__IO_REG32_BIT(DMAACMSK2,             0x7BE00300,__READ_WRITE ,__dmacmsk_bits);
__IO_REG32_BIT(DMAACTMOD2,            0x7BE00304,__READ_WRITE ,__dmactmod_bits);
__IO_REG32(    DMAACSAD2,             0x7BE00308,__READ_WRITE);
__IO_REG32(    DMAACDAD2,             0x7BE0030C,__READ_WRITE);
__IO_REG32_BIT(DMAACSIZ2,             0x7BE00310,__READ_WRITE ,__dmacsiz_bits);
__IO_REG32(    DMAACCINT2,            0x7BE00314,__WRITE);
__IO_REG32_BIT(DMAACMSK3,             0x7BE00400,__READ_WRITE ,__dmacmsk_bits);
__IO_REG32_BIT(DMAACTMOD3,            0x7BE00404,__READ_WRITE ,__dmactmod_bits);
__IO_REG32(    DMAACSAD3,             0x7BE00408,__READ_WRITE);
__IO_REG32(    DMAACDAD3,             0x7BE0040C,__READ_WRITE);
__IO_REG32_BIT(DMAACSIZ3,             0x7BE00410,__READ_WRITE ,__dmacsiz_bits);
__IO_REG32(    DMAACCINT3,            0x7BE00414,__WRITE);
__IO_REG32_BIT(DMABMOD,               0x7BE10000,__READ_WRITE ,__dmamod_bits);
__IO_REG32_BIT(DMABSTA,               0x7BE10004,__READ       ,__dmabsta_bits);
__IO_REG32_BIT(DMABINT,               0x7BE10008,__READ       ,__dmabint_bits);
__IO_REG32_BIT(DMABCMSK0,             0x7BE10100,__READ_WRITE ,__dmacmsk_bits);
__IO_REG32_BIT(DMABCTMOD0,            0x7BE10104,__READ_WRITE ,__dmactmod_bits);
__IO_REG32(    DMABCSAD0,             0x7BE10108,__READ_WRITE);
__IO_REG32(    DMABCDAD0,             0x7BE1010C,__READ_WRITE);
__IO_REG32_BIT(DMABCSIZ0,             0x7BE10110,__READ_WRITE ,__dmacsiz_bits);
__IO_REG32(    DMABCCINT0,            0x7BE10114,__WRITE);
__IO_REG32_BIT(DMABCMSK1,             0x7BE10200,__READ_WRITE ,__dmacmsk_bits);
__IO_REG32_BIT(DMABCTMOD1,            0x7BE10204,__READ_WRITE ,__dmactmod_bits);
__IO_REG32(    DMABCSAD1,             0x7BE10208,__READ_WRITE);
__IO_REG32(    DMABCDAD1,             0x7BE1020C,__READ_WRITE);
__IO_REG32_BIT(DMABCSIZ1,             0x7BE10210,__READ_WRITE ,__dmacsiz_bits);
__IO_REG32(    DMABCCINT1,            0x7BE10214,__WRITE);

/***************************************************************************
 **
 ** SIM I/F
 **
 ***************************************************************************/
__IO_REG8_BIT( SIMCSR0,               0xB7100000,__READ_WRITE ,__simcsr_bits);
__IO_REG8_BIT( SIMCCR0,               0xB7100004,__READ_WRITE ,__simccr_bits);
__IO_REG8(     SIMPDR0,               0xB7100008,__READ_WRITE);
__IO_REG8_BIT( SIMUCR20,              0xB710000C,__READ_WRITE ,__simucr2_bits);
__IO_REG8(     SIMGTR0,               0xB7100014,__READ_WRITE);
__IO_REG8_BIT( SIMUCR10,              0xB7100018,__READ_WRITE ,__simucr1_bits);
__IO_REG8_BIT( SIMPCR0,               0xB710001C,__READ_WRITE ,__simpcr_bits);
__IO_REG8(     SIMTOC0,               0xB7100020,__READ_WRITE);
__IO_REG8(     SIMTOR10,              0xB7100024,__READ_WRITE);
__IO_REG8(     SIMTOR20,              0xB7100028,__READ_WRITE);
__IO_REG8(     SIMTOR30,              0xB710002C,__READ_WRITE);
__IO_REG8_BIT( SIMMSR0,               0xB7100030,__READ_WRITE ,__simmsr_bits);
#define SIMFCR0     SIMMSR0
#define SIMFCR0_bit SIMMSR0_bit
__IO_REG8(     SIMUTR0,               0xB7100034,__READ_WRITE);
#define SIMURR0     SIMUTR0
__IO_REG8_BIT( SIMUSR0,               0xB7100038,__READ       ,__simusr_bits);
__IO_REG8_BIT( SIMEDC0,               0xB710003C,__READ_WRITE ,__simedc_bits);
__IO_REG8_BIT( SIMCSR1,               0xB7101000,__READ_WRITE ,__simcsr_bits);
__IO_REG8_BIT( SIMCCR1,               0xB7101004,__READ_WRITE ,__simccr_bits);
__IO_REG8(     SIMPDR1,               0xB7101008,__READ_WRITE);
__IO_REG8_BIT( SIMUCR21,              0xB710100C,__READ_WRITE ,__simucr2_bits);
__IO_REG8(     SIMGTR1,               0xB7101014,__READ_WRITE);
__IO_REG8_BIT( SIMUCR11,              0xB7101018,__READ_WRITE ,__simucr1_bits);
__IO_REG8_BIT( SIMPCR1,               0xB710101C,__READ_WRITE ,__simpcr_bits);
__IO_REG8(     SIMTOC1,               0xB7101020,__READ_WRITE);
__IO_REG8(     SIMTOR11,              0xB7101024,__READ_WRITE);
__IO_REG8(     SIMTOR21,              0xB7101028,__READ_WRITE);
__IO_REG8(     SIMTOR31,              0xB710102C,__READ_WRITE);
__IO_REG8_BIT( SIMMSR1,               0xB7101030,__READ_WRITE ,__simmsr_bits);
#define SIMFCR1     SIMMSR1
#define SIMFCR1_bit SIMMSR1_bit
__IO_REG8(     SIMUTR1,               0xB7101034,__READ_WRITE);
#define SIMURR1     SIMUTR1
__IO_REG8_BIT( SIMUSR1,               0xB7101038,__READ       ,__simusr_bits);
__IO_REG8_BIT( SIMEDC1,               0xB710103C,__READ_WRITE ,__simedc_bits);

/***************************************************************************
 **
 ** LCDC
 **
 ***************************************************************************/
__IO_REG32_BIT(LCDCTMG1,              0x7C000000,__READ_WRITE ,__lcdctmg1_bits);
__IO_REG32_BIT(LCDCTMG2,              0x7C000004,__READ_WRITE ,__lcdctmg2_bits);
__IO_REG32_BIT(LCDCTMG3,              0x7C000008,__READ_WRITE ,__lcdctmg3_bits);
__IO_REG32_BIT(LCDCCTLR,              0x7C00000C,__READ_WRITE ,__lcdcctlr_bits);
__IO_REG32_BIT(LCDCSTS,               0x7C000010,__READ       ,__lcdcsts_bits);
__IO_REG32_BIT(LCDCINT,               0x7C000014,__READ       ,__lcdcint_bits);
__IO_REG32_BIT(LCDCMASK,              0x7C000018,__READ_WRITE ,__lcdcmask_bits);
__IO_REG32_BIT(LCDCINTCLR,            0x7C00001C,__WRITE      ,__lcdcintclr_bits);

/***************************************************************************
 **
 ** USB Host
 **
 ***************************************************************************/
__IO_REG8(     VCRSCNT,               0xB7000038,__READ_WRITE);
__IO_REG32_BIT(USBConfig,             0x7BC00000,__READ_WRITE ,__usbcfg_bits);
__IO_REG32_BIT(DMACtl,                0x7BC00004,__READ_WRITE ,__dmactrl_bits);
__IO_REG32_BIT(RstPDownCtl,           0x7BC00008,__READ_WRITE ,__rstpdownctrl_bits);
__IO_REG32_BIT(HostCtl,               0x7BC00020,__READ_WRITE ,__hostctrl_bits);
__IO_REG32_BIT(SttTrnsCnt,            0x7BC00024,__READ_WRITE ,__stttrnsctrl_bits);
__IO_REG32_BIT(PktDataTrnsReq,        0x7BC00028,__READ_WRITE ,__pktdatatrnsreq_bits);
__IO_REG32_BIT(RamAdr,                0x7BC00030,__READ_WRITE ,__ramadr_bits);
__IO_REG32(    FifoAcc,               0x7BC00040,__READ_WRITE);
__IO_REG32_BIT(USBPortMon,            0x7BC000A0,__READ_WRITE ,__usbportmon_bits);
__IO_REG32_BIT(USBPortCtl,            0x7BC000B0,__READ_WRITE ,__usbportctrl_bits);
__IO_REG32_BIT(HcRevision,            0x7BC00100,__READ       ,__HcRevision_bits);
__IO_REG32_BIT(HcControl,             0x7BC00104,__READ_WRITE ,__HcControl_bits);
__IO_REG32_BIT(HcCommandStatus,       0x7BC00108,__READ_WRITE ,__HcCommandStatus_bits);
__IO_REG32_BIT(HcInterruptStatus,     0x7BC0010C,__READ_WRITE ,__HcInterruptStatus_bits);
__IO_REG32_BIT(HcInterruptEnable,     0x7BC00110,__READ_WRITE ,__HcInterruptEnable_bits);
__IO_REG32_BIT(HcInterruptDisable,    0x7BC00114,__READ_WRITE ,__HcInterruptEnable_bits);
__IO_REG32_BIT(HcHCCA,                0x7BC00118,__READ_WRITE ,__HcHCCA_bits);
__IO_REG32_BIT(HcPeriodCurrentED,     0x7BC0011C,__READ_WRITE ,__HcPeriodCurrentED_bits);
__IO_REG32_BIT(HcControlHeadED,       0x7BC00120,__READ_WRITE ,__HcControlHeadED_bits);
__IO_REG32_BIT(HcControlCurrentED,    0x7BC00124,__READ_WRITE ,__HcControlCurrentED_bits);
__IO_REG32_BIT(HcBulkHeadED,          0x7BC00128,__READ_WRITE ,__HcBulkHeadED_bits);
__IO_REG32_BIT(HcBulkCurrentED,       0x7BC0012C,__READ_WRITE ,__HcBulkCurrentED_bits);
__IO_REG32_BIT(HcDoneHead,            0x7BC00130,__READ_WRITE ,__HcDoneHead_bits);
__IO_REG32_BIT(HcFmInterval,          0x7BC00134,__READ_WRITE ,__HcFmInterval_bits);
__IO_REG32_BIT(HcFmRemaining,         0x7BC00138,__READ_WRITE ,__HcFmRemaining_bits);
__IO_REG16(    HcFmNumber,            0x7BC0013C,__READ_WRITE);
__IO_REG32_BIT(HcPeriodicStart,       0x7BC00140,__READ_WRITE ,__HcPeriodicStart_bits);
__IO_REG32_BIT(HcLSThreshold,         0x7BC00144,__READ_WRITE ,__HcLSThreshold_bits);
__IO_REG32_BIT(HcRhDescriptorA,       0x7BC00148,__READ_WRITE ,__HcRhDescriptorA_bits);
__IO_REG32_BIT(HcRhDescriptorB,       0x7BC0014C,__READ_WRITE ,__HcRhDescriptorB_bits);
__IO_REG32_BIT(HcRhStatus,            0x7BC00150,__READ_WRITE ,__HcRhStatus_bits);
__IO_REG32_BIT(HcRhPortStatus,        0x7BC00154,__READ_WRITE ,__HcRhPortStatus_bits);

/***************************************************************************
 **
 ** USB Device
 **
 ***************************************************************************/
__IO_REG8_BIT( bmRequestType,         0xB7700000,__READ       ,__bmRequestType_bits);
__IO_REG8(     bRequest,              0xB7700004,__READ);
__IO_REG8(     wValueLSB,             0xB7700008,__READ);
__IO_REG8(     wValueMSB,             0xB770000C,__READ);
__IO_REG8(     wIndexLSB,             0xB7700010,__READ);
__IO_REG8(     wIndexMSB,             0xB7700014,__READ);
__IO_REG8(     wLengthLSB,            0xB7700018,__READ);
__IO_REG8(     wLengthMSB,            0xB770001C,__READ);
__IO_REG8_BIT( DVCADR,                0xB7700080,__READ_WRITE ,__dvcadr_bits);
__IO_REG8_BIT( INTSTAT1,              0xB7700084,__READ       ,__intstat1_bits);
__IO_REG8_BIT( INTSTAT2,              0xB7700088,__READ_WRITE ,__intstat2_bits);
__IO_REG8_BIT( INTENBL1,              0xB7700090,__READ_WRITE ,__intenbl1_bits);
__IO_REG8_BIT( INTENBL2,              0xB7700094,__READ_WRITE ,__intenbl2_bits);
__IO_REG8_BIT( ISOMODESEL,            0xB77000B0,__READ_WRITE ,__isomodesel_bits);
__IO_REG8(     FRAMELSB,              0xB77000B4,__READ);
__IO_REG8_BIT( FRAMEMSB,              0xB77000B8,__READ       ,__framemsb_bits);
__IO_REG8_BIT( SYSCON,                0xB77000BC,__READ_WRITE ,__syscon_bits);
__IO_REG8_BIT( POLSEL,                0xB77000C0,__READ_WRITE ,__polsel_bits);
__IO_REG8_BIT( EP0CONF,               0xB7700100,__READ_WRITE ,__ep0conf_bits);
__IO_REG8_BIT( EP1CONF,               0xB7700104,__READ_WRITE ,__epconf_bits);
__IO_REG8_BIT( EP2CONF,               0xB7700108,__READ_WRITE ,__epconf_bits);
__IO_REG8_BIT( EP3CONF,               0xB770010C,__READ_WRITE ,__epconf_bits);
__IO_REG8_BIT( EP4CONF,               0xB7700110,__READ_WRITE ,__epconf_bits);
__IO_REG8_BIT( EP5CONF,               0xB7700114,__READ_WRITE ,__epconf_bits);
__IO_REG8_BIT( EP0CONT,               0xB7700120,__READ_WRITE ,__ep0cont_bits);
__IO_REG8_BIT( EP1CONT,               0xB7700124,__READ_WRITE ,__epcont_bits);
__IO_REG8_BIT( EP2CONT,               0xB7700128,__READ_WRITE ,__epcont_bits);
__IO_REG8_BIT( EP3CONT,               0xB770012C,__READ_WRITE ,__epcont_bits);
__IO_REG8_BIT( EP4CONT,               0xB7700130,__READ_WRITE ,__epcont_bits);
__IO_REG8_BIT( EP5CONT,               0xB7700134,__READ_WRITE ,__epcont_bits);
__IO_REG8_BIT( EP0PLD,                0xB7700140,__READ_WRITE ,__ep0pld_bits);
__IO_REG8_BIT( EP1PLD,                0xB7700144,__READ_WRITE ,__eppld_bits);
__IO_REG8_BIT( EP2PLD,                0xB7700148,__READ_WRITE ,__eppld_bits);
__IO_REG8_BIT( EP3PLD,                0xB770014C,__READ_WRITE ,__ep0pld_bits);
__IO_REG8(     EP4PLD,                0xB7700150,__READ_WRITE);
__IO_REG8_BIT( EP5PLD,                0xB7700154,__READ_WRITE ,__eppld_bits);
__IO_REG8_BIT( EP0RXCNT,              0xB7700160,__READ       ,__ep0rxcnt_bits);
__IO_REG8_BIT( EP1RXCNT,              0xB7700164,__READ       ,__eprxcnt_bits);
__IO_REG8_BIT( EP2RXCNT,              0xB7700168,__READ       ,__eprxcnt_bits);
__IO_REG8_BIT( EP3RXCNT,              0xB770016C,__READ       ,__ep0rxcnt_bits);
__IO_REG8(     EP4RXCNT,              0xB7700170,__READ);
__IO_REG8(     EP5RXCNT,              0xB7700174,__READ);
__IO_REG8_BIT( EP0STAT,               0xB7700180,__READ_WRITE ,__ep0stat_bits);
__IO_REG8_BIT( EP1STAT,               0xB7700184,__READ_WRITE ,__epstat_bits);
__IO_REG8_BIT( EP2STAT,               0xB7700188,__READ_WRITE ,__epstat_bits);
__IO_REG8_BIT( EP3STAT,               0xB770018C,__READ_WRITE ,__epstat_bits);
__IO_REG8_BIT( EP4STAT,               0xB7700190,__READ_WRITE ,__epstat_bits);
__IO_REG8_BIT( EP5STAT,               0xB7700194,__READ_WRITE ,__epstat_bits);
__IO_REG32(    EP0TXFIFO,             0xB77001C0,__WRITE     );
__IO_REG32(    EP0RXFIFO,             0xB77001E0,__READ      );
__IO_REG32(    EP1FIFO,               0xB77001E4,__READ_WRITE);
__IO_REG32(    EP2FIFO,               0xB77001E8,__READ_WRITE);
__IO_REG32(    EP3FIFO,               0xB77001EC,__READ_WRITE);
__IO_REG32(    EP4FIFO,               0xB77001F0,__READ_WRITE);
__IO_REG32(    EP5FIFO,               0xB77001F4,__READ_WRITE);

/***************************************************************************
 **
 ** WDT
 **
 ***************************************************************************/
__IO_REG8(     WDTCON,                0xB7E00000,__WRITE);
__IO_REG8_BIT( TBGCON,                0xB7E00004,__READ_WRITE ,__tbgcon_bits);
__IO_REG8_BIT( INTST,                 0xB7E00008,__READ_WRITE ,__intst_bits);
__IO_REG8(     OVFAST,                0xB7E0000C,__READ_WRITE);
__IO_REG16(    WDTCNT,                0xB7E00010,__READ_WRITE);

/***************************************************************************
 **
 ** A/D Converter
 **
 ***************************************************************************/
__IO_REG16_BIT(ADCON0,                0xB6000000,__READ_WRITE ,__adcon0_bits);
__IO_REG16_BIT(ADCON1,                0xB6000004,__READ_WRITE ,__adcon1_bits);
__IO_REG16_BIT(ADCON2,                0xB6000008,__READ_WRITE ,__adcon2_bits);
__IO_REG16_BIT(ADINT,                 0xB600000C,__READ_WRITE ,__adint_bits);
__IO_REG16_BIT(ADFINT,                0xB6000010,__READ_WRITE ,__adfint_bits);
__IO_REG16_BIT(ADR0,                  0xB6000014,__READ_WRITE ,__adr_bits);
__IO_REG16_BIT(ADR1,                  0xB6000018,__READ_WRITE ,__adr_bits);
__IO_REG16_BIT(ADR2,                  0xB600001C,__READ_WRITE ,__adr_bits);
__IO_REG16_BIT(ADR3,                  0xB6000020,__READ_WRITE ,__adr_bits);
__IO_REG16_BIT(ADR4,                  0xB6000024,__READ_WRITE ,__adr_bits);
__IO_REG16_BIT(ADR5,                  0xB6000028,__READ_WRITE ,__adr_bits);
__IO_REG16_BIT(ADR6,                  0xB600002C,__READ_WRITE ,__adr_bits);
__IO_REG16_BIT(ADR7,                  0xB6000030,__READ_WRITE ,__adr_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG8_BIT( PO0,                   0xB7A00000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI0,                   0xB7A00004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM0,                   0xB7A00008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE0,                   0xB7A0000C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM0,                   0xB7A00010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS0,                   0xB7A00018,__READ_WRITE ,__is_bits);
__IO_REG8_BIT( PO1,                   0xB7A01000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI1,                   0xB7A01004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM1,                   0xB7A01008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE1,                   0xB7A0100C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM1,                   0xB7A01010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS1,                   0xB7A01018,__READ_WRITE ,__is_bits);
__IO_REG8_BIT( PO2,                   0xB7A02000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI2,                   0xB7A02004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM2,                   0xB7A02008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE2,                   0xB7A0200C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM2,                   0xB7A02010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS2,                   0xB7A02018,__READ_WRITE ,__is_bits);
__IO_REG8_BIT( PO3,                   0xB7A03000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI3,                   0xB7A03004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM3,                   0xB7A03008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE3,                   0xB7A0300C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM3,                   0xB7A03010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS3,                   0xB7A03018,__READ_WRITE ,__is_bits);
__IO_REG8_BIT( PO4,                   0xB7A04000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI4,                   0xB7A04004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM4,                   0xB7A04008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE4,                   0xB7A0400C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM4,                   0xB7A04010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS4,                   0xB7A04018,__READ_WRITE ,__is_bits);
__IO_REG8_BIT( PO5,                   0xB7A05000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI5,                   0xB7A05004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM5,                   0xB7A05008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE5,                   0xB7A0500C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM5,                   0xB7A05010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS5,                   0xB7A05018,__READ_WRITE ,__is_bits);
__IO_REG8_BIT( PO6,                   0xB7A06000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI6,                   0xB7A06004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM6,                   0xB7A06008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE6,                   0xB7A0600C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM6,                   0xB7A06010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS6,                   0xB7A06018,__READ_WRITE ,__is_bits);
__IO_REG8_BIT( PO7,                   0xB7A07000,__READ_WRITE ,__po_bits);
__IO_REG8_BIT( PI7,                   0xB7A07004,__READ       ,__pi_bits);
__IO_REG8_BIT( PM7,                   0xB7A07008,__READ_WRITE ,__pm_bits);
__IO_REG8_BIT( IE7,                   0xB7A0700C,__READ_WRITE ,__ie_bits);
__IO_REG32_BIT(IM7,                   0xB7A07010,__READ_WRITE ,__im_bits);
__IO_REG8_BIT( IS7,                   0xB7A07018,__READ_WRITE ,__is_bits);

/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG16_BIT(I2CSADR0,              0xB7800000,__READ_WRITE ,__i2csadr_bits);
__IO_REG16_BIT(I2CCTL0,               0xB7800004,__READ_WRITE ,__i2cctl_bits);
__IO_REG16_BIT(I2CSR0,                0xB7800008,__READ_WRITE ,__i2csr_bits);
__IO_REG16_BIT(I2CDR0,                0xB780000C,__READ_WRITE ,__i2cdr_bits);
__IO_REG16_BIT(I2CMON0,               0xB7800010,__READ       ,__i2cmon_bits);
__IO_REG16_BIT(I2CBC0,                0xB7800014,__READ_WRITE ,__i2cbc_bits);
__IO_REG16_BIT(I2CSADR1,              0xB7801000,__READ_WRITE ,__i2csadr_bits);
__IO_REG16_BIT(I2CCTL1,               0xB7801004,__READ_WRITE ,__i2cctl_bits);
__IO_REG16_BIT(I2CSR1,                0xB7801008,__READ_WRITE ,__i2csr_bits);
__IO_REG16_BIT(I2CDR1,                0xB780100C,__READ_WRITE ,__i2cdr_bits);
__IO_REG16_BIT(I2CMON1,               0xB7801010,__READ       ,__i2cmon_bits);
__IO_REG16_BIT(I2CBC1,                0xB7801014,__READ_WRITE ,__i2cbc_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG8_BIT( S1,                    0xB7C00000,__READ_WRITE ,__s1_bits);
__IO_REG8_BIT( S10,                   0xB7C00004,__READ_WRITE ,__s10_bits);
__IO_REG8_BIT( M1,                    0xB7C00008,__READ_WRITE ,__m1_bits);
__IO_REG8_BIT( M10,                   0xB7C0000C,__READ_WRITE ,__m10_bits);
__IO_REG8_BIT( H1,                    0xB7C00010,__READ_WRITE ,__h1_bits);
__IO_REG8_BIT( H10,                   0xB7C00014,__READ_WRITE ,__h10_bits);
__IO_REG8_BIT( D1,                    0xB7C00018,__READ_WRITE ,__d1_bits);
__IO_REG8_BIT( D10,                   0xB7C0001C,__READ_WRITE ,__d10_bits);
__IO_REG8_BIT( MO1,                   0xB7C00020,__READ_WRITE ,__mo1_bits);
__IO_REG8_BIT( MO10,                  0xB7C00024,__READ_WRITE ,__mo10_bits);
__IO_REG8_BIT( Y1,                    0xB7C00028,__READ_WRITE ,__y1_bits);
__IO_REG8_BIT( Y10,                   0xB7C0002C,__READ_WRITE ,__y10_bits);
__IO_REG8_BIT( W,                     0xB7C00030,__READ_WRITE ,__w_bits);
__IO_REG8_BIT( CD,                    0xB7C00034,__READ_WRITE ,__cd_bits);
__IO_REG8_BIT( CE,                    0xB7C00038,__READ_WRITE ,__ce_bits);
__IO_REG8_BIT( CF,                    0xB7C0003C,__READ_WRITE ,__cf_bits);

/***************************************************************************
 **
 ** UART 0
 **
 ***************************************************************************/
/* UARTDLL0, UARTRBR0 and UARTTHR0 share the same address */
__IO_REG8(     UARTRBRTHR0,           0xB7B00000,__READ_WRITE);
#define UARTDLL0 UARTRBRTHR0
#define UARTRBR0 UARTRBRTHR0
#define UARTTHR0 UARTRBRTHR0

/* UARTDLM0 and UARTIER0 share the same address */
__IO_REG8_BIT( UARTIER0,              0xB7B00004,__READ_WRITE ,__uartier_bits);
#define UARTDLM0     UARTIER0

/* UARTFCR0 and UARTIIR0 share the same address */
__IO_REG8_BIT( UARTFCRIIR0,           0xB7B00008,__READ_WRITE ,__uartfcriir_bits);
#define UARTFCR0     UARTFCRIIR0
#define UARTFCR0_bit UARTFCRIIR0_bit
#define UARTIIR0     UARTFCRIIR0
#define UARTIIR0_bit UARTFCRIIR0_bit
#define UARTDLH0     UARTFCRIIR0
#define UARTDLH0_bit UARTFCRIIR0_bit

__IO_REG8_BIT( UARTLCR0,              0xB7B0000C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( UARTMCR0,              0xB7B00010,__READ_WRITE ,__uartmcr_bits);
__IO_REG8_BIT( UARTLSR0,              0xB7B00014,__READ_WRITE ,__uartlsr_bits);
__IO_REG8_BIT( UARTMSR0,              0xB7B00018,__READ_WRITE ,__uartmsr_bits);
__IO_REG8(     UARTSCR0,              0xB7B0001C,__READ_WRITE);

/***************************************************************************
 **
 ** UART 1
 **
 ***************************************************************************/
/* UARTDLL1, UARTRBR1 and UARTTHR1 share the same address */
__IO_REG8(     UARTRBRTHR1,           0xB7B01000,__READ_WRITE);
#define UARTDLL1 UARTRBRTHR1
#define UARTRBR1 UARTRBRTHR1
#define UARTTHR1 UARTRBRTHR1

/* UARTDLM1 and UARTIER1 share the same address */
__IO_REG8_BIT( UARTIER1,              0xB7B01004,__READ_WRITE ,__uartier_bits);
#define UARTDLM1     UARTIER1

/* UARTFCR0 and UARTIIR0 share the same address */
__IO_REG8_BIT( UARTFCRIIR1,           0xB7B01008,__READ_WRITE ,__uartfcriir_bits);
#define UARTFCR1     UARTFCRIIR1
#define UARTFCR1_bit UARTFCRIIR1_bit
#define UARTIIR1     UARTFCRIIR1
#define UARTIIR1_bit UARTFCRIIR1_bit
#define UARTDLH1     UARTFCRIIR1
#define UARTDLH1_bit UARTFCRIIR1_bit

__IO_REG8_BIT( UARTLCR1,              0xB7B0100C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( UARTMCR1,              0xB7B01010,__READ_WRITE ,__uartmcr_bits);
__IO_REG8_BIT( UARTLSR1,              0xB7B01014,__READ_WRITE ,__uartlsr_bits);
__IO_REG8_BIT( UARTMSR1,              0xB7B01018,__READ_WRITE ,__uartmsr_bits);
__IO_REG8(     UARTSCR1,              0xB7B0101C,__READ_WRITE);

/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(SPCR0,                 0xB7B02000,__READ_WRITE ,__spcr_bits);
__IO_REG32_BIT(SPBRR0,                0xB7B02004,__READ_WRITE ,__spbrr_bits);
__IO_REG32_BIT(SPSR0,                 0xB7B02008,__READ_WRITE ,__spsr_bits);
__IO_REG32_BIT(SPDWR0,                0xB7B0200C,__READ_WRITE ,__spdwr_bits);
__IO_REG32_BIT(SPDRR0,                0xB7B02010,__READ       ,__spdrr_bits);
__IO_REG32_BIT(SPCR1,                 0xB7B03000,__READ_WRITE ,__spcr_bits);
__IO_REG32_BIT(SPBRR1,                0xB7B03004,__READ_WRITE ,__spbrr_bits);
__IO_REG32_BIT(SPSR1,                 0xB7B03008,__READ_WRITE ,__spsr_bits);
__IO_REG32_BIT(SPDWR1,                0xB7B0300C,__READ_WRITE ,__spdwr_bits);
__IO_REG32_BIT(SPDRR1,                0xB7B03010,__READ       ,__spdrr_bits);

/***************************************************************************
 **
 ** FTM
 **
 ***************************************************************************/
__IO_REG16_BIT(FTM0CON,               0xB7F00000,__READ_WRITE ,__ftmcon_bits);
__IO_REG16_BIT(FTM0ST,                0xB7F00004,__READ_WRITE ,__ftmst_bits);
__IO_REG16(    FTM0C,                 0xB7F00008,__READ_WRITE);
__IO_REG16(    FTM0R,                 0xB7F0000C,__READ_WRITE);
__IO_REG16(    FTM0GR,                0xB7F00010,__READ_WRITE);
__IO_REG16_BIT(FTM0IOLV,              0xB7F00014,__READ_WRITE ,__ftmiolv_bits);
__IO_REG16_BIT(FTM0OUT,               0xB7F00018,__READ_WRITE ,__ftmout_bits);
__IO_REG16_BIT(FTM0IER,               0xB7F0001C,__READ_WRITE ,__ftmier_bits);
__IO_REG16_BIT(FTM1CON,               0xB7F00020,__READ_WRITE ,__ftmcon_bits);
__IO_REG16_BIT(FTM1ST,                0xB7F00024,__READ_WRITE ,__ftmst_bits);
__IO_REG16(    FTM1C,                 0xB7F00028,__READ_WRITE);
__IO_REG16(    FTM1R,                 0xB7F0002C,__READ_WRITE);
__IO_REG16(    FTM1GR,                0xB7F00030,__READ_WRITE);
__IO_REG16_BIT(FTM1IOLV,              0xB7F00034,__READ_WRITE ,__ftmiolv_bits);
__IO_REG16_BIT(FTM1OUT,               0xB7F00038,__READ_WRITE ,__ftmout_bits);
__IO_REG16_BIT(FTM1IER,               0xB7F0003C,__READ_WRITE ,__ftmier_bits);
__IO_REG16_BIT(FTM2CON,               0xB7F00040,__READ_WRITE ,__ftmcon_bits);
__IO_REG16_BIT(FTM2ST,                0xB7F00044,__READ_WRITE ,__ftmst_bits);
__IO_REG16(    FTM2C,                 0xB7F00048,__READ_WRITE);
__IO_REG16(    FTM2R,                 0xB7F0004C,__READ_WRITE);
__IO_REG16(    FTM2GR,                0xB7F00050,__READ_WRITE);
__IO_REG16_BIT(FTM2IOLV,              0xB7F00054,__READ_WRITE ,__ftmiolv_bits);
__IO_REG16_BIT(FTM2OUT,               0xB7F00058,__READ_WRITE ,__ftmout_bits);
__IO_REG16_BIT(FTM2IER,               0xB7F0005C,__READ_WRITE ,__ftmier_bits);
__IO_REG16_BIT(FTM3CON,               0xB7F00060,__READ_WRITE ,__ftmcon_bits);
__IO_REG16_BIT(FTM3ST,                0xB7F00064,__READ_WRITE ,__ftmst_bits);
__IO_REG16(    FTM3C,                 0xB7F00068,__READ_WRITE);
__IO_REG16(    FTM3R,                 0xB7F0006C,__READ_WRITE);
__IO_REG16(    FTM3GR,                0xB7F00070,__READ_WRITE);
__IO_REG16_BIT(FTM3IOLV,              0xB7F00074,__READ_WRITE ,__ftmiolv_bits);
__IO_REG16_BIT(FTM3OUT,               0xB7F00078,__READ_WRITE ,__ftmout_bits);
__IO_REG16_BIT(FTM3IER,               0xB7F0007C,__READ_WRITE ,__ftmier_bits);
__IO_REG16_BIT(FTM4CON,               0xB7F00080,__READ_WRITE ,__ftmcon_bits);
__IO_REG16_BIT(FTM4ST,                0xB7F00084,__READ_WRITE ,__ftmst_bits);
__IO_REG16(    FTM4C,                 0xB7F00088,__READ_WRITE);
__IO_REG16(    FTM4R,                 0xB7F0008C,__READ_WRITE);
__IO_REG16(    FTM4GR,                0xB7F00090,__READ_WRITE);
__IO_REG16_BIT(FTM4IOLV,              0xB7F00094,__READ_WRITE ,__ftmiolv_bits);
__IO_REG16_BIT(FTM4OUT,               0xB7F00098,__READ_WRITE ,__ftmout_bits);
__IO_REG16_BIT(FTM4IER,               0xB7F0009C,__READ_WRITE ,__ftmier_bits);
__IO_REG16_BIT(FTM5CON,               0xB7F000A0,__READ_WRITE ,__ftmcon_bits);
__IO_REG16_BIT(FTM5ST,                0xB7F000A4,__READ_WRITE ,__ftmst_bits);
__IO_REG16(    FTM5C,                 0xB7F000A8,__READ_WRITE);
__IO_REG16(    FTM5R,                 0xB7F000AC,__READ_WRITE);
__IO_REG16(    FTM5GR,                0xB7F000B0,__READ_WRITE);
__IO_REG16_BIT(FTM5IOLV,              0xB7F000B4,__READ_WRITE ,__ftmiolv_bits);
__IO_REG16_BIT(FTM5OUT,               0xB7F000B8,__READ_WRITE ,__ftmout_bits);
__IO_REG16_BIT(FTM5IER,               0xB7F000BC,__READ_WRITE ,__ftmier_bits);
__IO_REG16_BIT(FTMEN,                 0xB7F000C0,__READ_WRITE ,__ftmen_bits);
__IO_REG16_BIT(FTMDIS,                0xB7F000C4,__WRITE      ,__ftmdis_bits);

/***************************************************************************
 **
 ** Standby Function
 **
 ***************************************************************************/
__IO_REG8_BIT( MASK,                  0xB6400000,__READ_WRITE ,__mask_bits);
__IO_REG8_BIT( INTPC,                 0xB6400004,__READ_WRITE ,__intpc_bits);
__IO_REG8_BIT( SDRAMCKE,              0xB6400008,__READ_WRITE ,__sdramcke_bits);
__IO_REG8_BIT( PLCLR,                 0xB640000C,__READ_WRITE ,__plclr_bits);
__IO_REG8_BIT( INTPCS,                0xB6400010,__READ_WRITE ,__intpcs_bits);
__IO_REG8_BIT( RESUMEIN,              0xB6400014,__READ       ,__resumein_bits);
__IO_REG8_BIT( STBCS,                 0xB6400018,__READ_WRITE ,__stbcs_bits);

/* Assembler specific declarations  ****************************************/
#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **   ML675050 interrupt sources
 **
 ***************************************************************************/
#define INT_SYSTIMER        0
#define INT_WDT             1
// #define RESERVE          2
// #define RESERVE          3
#define INT_GPIO0           4
#define INT_GPIO1           5
#define INT_GPIO2           6
#define INT_GPIO3           7
#define INT_SOFT            8
#define INT_USBH            9
#define INT_SIO             10
#define INT_ADC             11
#define INT_USBD            12
#define INT_EXEC            13
#define INT_LCDC            14
#define INT_I2C0            15
#define INT_FTM0            16
#define INT_FTM1            17
#define INT_FTM2            18
#define INT_FTM3            19
#define INT_FTM4            20
#define INT_FTM5            21
// #define RESERVE          22
// #define RESERVE          23
// #define RESERVE          24
// #define RESERVE          25
#define INT_RTC             26
// #define RESERVE          27
#define INT_GPIO4           28
#define INT_GPIO5           29
#define INT_GPIO6           30
#define INT_GPIO7           31
#define INT_EXINT0          32
// #define RESERVE          33
#define INT_EXINT1          34
// #define RESERVE          35
#define INT_EXINT2          36
// #define RESERVE          37
#define INT_EXINT3          38
// #define RESERVE          39
#define INT_EXINT4          40
// #define RESERVE          41
#define INT_EXINT5          42
// #define RESERVE          43
#define INT_EXINT6          44
// #define RESERVE          45
// #define RESERVE          46
// #define RESERVE          47
#define INT_UART0           48
#define INT_UART1           49
#define INT_SIMIF0          50
#define INT_SIMIF1          51
#define INT_SPI0            52
#define INT_SPI1            53
#define INT_I2C1            54
// #define RESERVE          55
#define INT_DMAC_A0         56
#define INT_DMAC_A1         57
#define INT_DMAC_A2         58
#define INT_DMAC_A3         59
#define INT_DMAC_B0         60
#define INT_DMAC_B1         61
// #define RESERVE          62
// #define RESERVE          63

#endif    /* __IOML675050_H */
