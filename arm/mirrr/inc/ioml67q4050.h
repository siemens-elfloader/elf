/***************************************************************************
 **
 **    This file defines the Special Function Registers for the
 **    Oki Semiconductors ML67Q4050
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.3 $
 **
 ***************************************************************************/

#ifndef __IOML67Q4051_H
#define __IOML67Q4051_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4f = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    ML67Q4051 SPECIAL FUNCTION REGISTERS
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

/* 4.3.3 Peripheral Clock Control Register (PECLKCTL) */
typedef struct{
__REG32 CKE_ADC     : 1;     
__REG32 CKE_I2C     : 1;     
__REG32 CKE_I2S     : 1;     
__REG32 CKE_UART0   : 1;     
__REG32 CKE_UART1   : 1;     
__REG32 CKE_SPI0    : 1;     
__REG32 CKE_SPI1    : 1;     
__REG32             : 1;     
__REG32 CKE_WDT     : 1;     
__REG32 CKE_TMR     : 1;     
__REG32             : 6;     
__REG32 CKE_GPIO0   : 1;     
__REG32 CKE_GPIO1   : 1;     
__REG32 CKE_GPIO2   : 1;     
__REG32 CKE_GPIO3   : 1;     
__REG32 CKE_GPIO4   : 1;     
__REG32 CKE_GPIO5   : 1;     
__REG32 CKE_GPIO6   : 1;     
__REG32 CKE_GPIO7   : 1;     
__REG32 CKE_GPIO8   : 1;     
__REG32 CKE_GPIO9   : 1;     
__REG32 CKE_GPIO19  : 1;     
__REG32 CKE_GPIO11  : 1;     
__REG32 CKE_GPIO12  : 1;     
__REG32 CKE_GPIO13  : 1;     
__REG32 CKE_GPIO14  : 1;     
__REG32             : 1;     
} __peclkctl_bits;

/* 4.3.4 Peripheral Reset Control Register (PERSTCTL) */
typedef struct{
__REG32 RST_ADC     : 1;     
__REG32 RST_I2C     : 1;     
__REG32 RST_I2S     : 1;     
__REG32 RST_UART0   : 1;     
__REG32 RST_UART1   : 1;     
__REG32 RST_SPI0    : 1;     
__REG32 RST_SPI1    : 1;     
__REG32             : 1;     
__REG32 RST_WDT     : 1;     
__REG32 RST_TMR     : 1;     
__REG32             : 6;     
__REG32 RST_GPIO0   : 1;     
__REG32 RST_GPIO1   : 1;     
__REG32 RST_GPIO2   : 1;     
__REG32 RST_GPIO3   : 1;     
__REG32 RST_GPIO4   : 1;     
__REG32 RST_GPIO5   : 1;     
__REG32 RST_GPIO6   : 1;     
__REG32 RST_GPIO7   : 1;     
__REG32 RST_GPIO8   : 1;     
__REG32 RST_GPIO9   : 1;     
__REG32 RST_GPIO19  : 1;     
__REG32 RST_GPIO11  : 1;     
__REG32 RST_GPIO12  : 1;     
__REG32 RST_GPIO13  : 1;     
__REG32 RST_GPIO14  : 1;     
__REG32             : 1;     
} __perstctl_bits;

/* 4.3.5 PLL Control Register 1 (PLL1) */
typedef struct{
__REG32 DVCOA  : 8;     
__REG32 DREFA  : 4;     
__REG32 SVCOA  : 2;     
__REG32        : 2;     
__REG32 DVCOB  : 8;     
__REG32 DREFB  : 4;     
__REG32 SVCOB  : 2;     
__REG32        : 2;     
} __pll1_bits;

/* 4.3.6 PLL Control Register 2 (PLL2) */
typedef struct{
__REG32 PLLDIVA  : 8;     
__REG32 PLLDIVB  : 8;     
__REG32 PLLDIVC  : 8;     
__REG32          : 8;     
} __pll2_bits;

/* 4.3.7 Clock Control Register (CLKCNT) */
typedef struct{
__REG32 PLLSEL     : 2;     
__REG32 CLKDIVA    : 3;     
__REG32 CLKDIVB    : 2;     
__REG32            : 1;     
__REG32 SRCSEL     : 2;     
__REG32 APBDIV     : 2;     
__REG32 AUDIOSEL   : 2;     
__REG32            : 2;     
__REG32 PLLENA     : 1;     
__REG32 PLLENB     : 1;     
__REG32 RINGOSCEN  : 1;     
__REG32 SYSCLKEN   : 1;     
__REG32 RTCCLKEN   : 1;     
__REG32            :11;     
} __clkcnt_bits;

/* 4.3.8 Clock Stop Control Register (CLKSTPCNT) */
typedef struct{
__REG32            :16;     
__REG32 PLLENA     : 1;     
__REG32 PLLENB     : 1;     
__REG32 RINGOSCEN  : 1;     
__REG32 SYSCLKEN   : 1;     
__REG32 RTCCLKEN   : 1;     
__REG32            :11;     
} __clkstpcnt_bits;

/* 4.3.9 Clock Supply Wait Time Control Register (CKWT) */
typedef struct{
__REG32 CKWTCMP  :12;     
__REG32          : 2;     
__REG32 CKWTSEL  : 2;     
__REG32          :16;     
} __ckwt_bits;

/* 5.2.1 DMA Control Register (DMARQCNT) */
typedef struct{
__REG32 CH0SEL  : 4;     
__REG32 CH1SEL  : 4;     
__REG32         :24;     
} __dmarqcnt_bits;

/* 5.2.2 LSI Control Register (LSICNT) */
typedef struct{
__REG32 I2SOUT   : 1;     
__REG32          : 3;     
__REG32 I2CNFON  : 1;     
__REG32          : 3;     
__REG32 JTAGE    : 1;     
__REG32          :23;     
} __lsicnt_bits;

/* 5.2.3 Port Control Register 1 (PORTSEL1) */
typedef struct{
__REG32      :12;     
__REG32 PA6  : 2;     
__REG32      : 2;     
__REG32 PB0  : 2;     
__REG32 PB1  : 2;     
__REG32 PB2  : 2;     
__REG32 PB3  : 2;     
__REG32 PB4  : 2;     
__REG32 PB5  : 2;     
__REG32      : 4;     
} __portsel1_bits;

/* 5.2.4 Port Control Register 2 (PORTSEL2) */
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
__REG32      : 6;     
} __portsel2_bits;

/* 5.2.5 Port Control Register 3 (PORTSEL3) */
typedef struct{
__REG32      : 6;     
__REG32 PE3  : 2;     
__REG32 PE4  : 2;     
__REG32 PE5  : 2;     
__REG32 PE6  : 2;     
__REG32      : 2;     
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
__REG32 XA0  : 1;     
__REG32      : 1;     
__REG32 XA1  : 2;     
__REG32 XD0  : 1;     
__REG32      : 1;     
__REG32 XD1  : 1;     
__REG32      :25;     
} __portsel4_bits;

/* 5.2.7 Port Control Register 5 (PORTSEL5) */
typedef struct{
__REG32 PN0_0  : 1;     
__REG32        : 1;     
__REG32 PN1_0  : 1;     
__REG32        : 1;     
__REG32 PN2_0  : 1;     
__REG32        : 1;     
__REG32 PN3_0  : 1;     
__REG32        : 1;     
__REG32 PN4_0  : 1;     
__REG32        : 1;     
__REG32 PN5_0  : 1;     
__REG32        : 1;     
__REG32 PN6_0  : 1;     
__REG32        : 1;     
__REG32 PN7_0  : 1;     
__REG32        : 1;     
__REG32 PO0    : 1;     
__REG32        : 1;     
__REG32 PO1    : 1;     
__REG32        :13;     
} __portsel5_bits;

/* 5.2.8 FTM Control Register (FTMSEL) */
typedef struct{
__REG32 FTMCLK0  : 2;     
__REG32 FTMCLK1  : 2;     
__REG32          : 4;     
__REG32 FTMIN0   : 2;     
__REG32 FTMIN1   : 2;     
__REG32 FTMIN2   : 2;     
__REG32 FTMIN3   : 2;     
__REG32 FTMIN4   : 2;     
__REG32 FTMIN5   : 2;     
__REG32          :12;     
} __ftmsel_bits;

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
__REG32       : 1;     
__REG32       : 8;     
__REG32 ILR4  : 3;     
__REG32       : 1;     
__REG32       : 4;     
__REG32 ILR6  : 3;     
__REG32       : 1;     
__REG32       : 4;     
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

/* 6.5.10 Current IRQ Level Clear Register (CILCL) */
typedef struct{
__REG32 CILCL  :32;     
} __cilcl_bits;

/* 6.5.11 Current IRQ Encode Register (CILE) */
typedef struct{
__REG32 CILE  : 3;     
__REG32       :29;     
} __cile_bits;

/* 6.5.12 Extended Interrupt Size Register (EXIRS) */
typedef struct{
__REG32 EXIRS  : 8;     
__REG32        :24;     
} __exirs_bits;

/* 6.5.13 Extended Interrupt Clear Register (EXIRCL) */
typedef struct{
__REG32 EXIRCL  : 8;     
__REG32         :24;     
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
__REG32         : 2;     
__REG32 IDM34   : 1;     
__REG32 IDMP34  : 1;     
__REG32 IDM36   : 1;     
__REG32 IDMP36  : 1;     
__REG32 IDM38   : 1;     
__REG32 IDMP38  : 1;     
__REG32 IDM40   : 1;     
__REG32 IDMP40  : 1;     
__REG32 IDM42   : 1;     
__REG32 IDMP42  : 1;     
__REG32         :20;     
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
__REG32 FIDMP  : 1;     
__REG32        :30;     
} __exfidm_bits;

/* 7.4.1 Bus width Control Register (BWC) */
typedef struct{
__REG32        : 2;     
__REG32 ROMBW  : 2;     
__REG32 RAMBW  : 2;     
__REG32 IOBW0  : 2;     
__REG32 IOBW1  : 2;     
__REG32        :22;     
} __bwc_bits;

/* 7.4.2 ROM Access Control Register (ROMAC) */
typedef struct{
__REG32 ROMTYPE  : 3;     
__REG32          :29;     
} __romac_bits;

/* 7.4.3 SRAM Access Control Register (RAMAC) */
typedef struct{
__REG32 RAMTYPE  : 3;     
__REG32          :29;     
} __ramac_bits;

/* 7.4.4 External I/O0 Access Control Register (IO0AC) */
typedef struct{
__REG32 IO0TYPE  : 3;     
__REG32          :29;     
} __io0ac_bits;

/* 7.4.5 External I/O1 Access Control Register (IO1AC) */
typedef struct{
__REG32 IO1TYPE  : 3;     
__REG32          :29;     
} __io1ac_bits;

/* 8.4.1 Transmit/ReceiveBufferRegister (SIOBUF) */
typedef struct{
__REG32 SIOBUF  : 8;     
__REG32         :24;     
} __siobuf_bits;

/* 8.4.2 SIO Status Register (SIOSTA) */
typedef struct{
__REG32 FERR   : 1;     
__REG32 OERR   : 1;     
__REG32 PERR   : 1;     
__REG32        : 1;     
__REG32 RVIRQ  : 1;     
__REG32 TRIRQ  : 1;     
__REG32        :26;     
} __siosta_bits;

/* 8.4.3 SIO Control Register (SIOCON) */
typedef struct{
__REG32 LN    : 1;     
__REG32 PEN   : 1;     
__REG32 EVN   : 1;     
__REG32 TSTB  : 1;     
__REG32       :28;     
} __siocon_bits;

/* 8.4.4 Baud Rate Control Register (SIOBCN) */
typedef struct{
__REG32        : 4;     
__REG32 BGRUN  : 1;     
__REG32        :27;     
} __siobcn_bits;

/* 8.4.5 Baud Rate Timer Register (SIOBT) */
typedef struct{
__REG32 SIOBT  : 8;     
__REG32        :24;     
} __siobt_bits;

/* 8.4.6 SIO Test Control Register (SIOTCN) */
typedef struct{
__REG32 MFERR  : 1;     
__REG32 MPERR  : 1;     
__REG32        : 5;     
__REG32 LBTST  : 1;     
__REG32        :24;     
} __siotcn_bits;

/* 9.4.1 Timer Enable Register (TMEN) */
typedef struct{
__REG32 TCEN  : 1;     
__REG32       :31;     
} __tmen_bits;

/* 9.4.2 Timer Reload Register (TMRLR) */
typedef struct{
__REG32 TMRLR  :16;     
__REG32        :16;     
} __tmrlr_bits;

/* 9.4.3 OverflowRegister(TMOVF) */
typedef struct{
__REG32 OVF  : 1;     
__REG32      :31;     
} __tmovf_bits;

/* 10.4.1 DMA Mode Register (DMAMOD) */
typedef struct{
__REG32 PRI  : 1;     
__REG32      :31;     
} __dmamod_bits;

/* 10.4.2 Status Register (DMASTA) */
typedef struct{
__REG32 STA0  : 1;     
__REG32 STA1  : 1;     
__REG32       :30;     
} __dmasta_bits;

/* 10.4.3 DMA Completion Status Register (DMAINT) */
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
} __dmaint_bits;

/* 10.4.4 DMA Channel Mask Registers (DMACMSK0–1) */
typedef struct{
__REG32 MSK  : 1;     
__REG32      :31;     
} __dmacmsk_bits;

/* 10.4.5 DMA Transfer Mode Registers (DMACTMOD0–1) */
typedef struct{
__REG32 ARQ   : 1;     
__REG32 TSIZ  : 2;     
__REG32 SDP   : 1;     
__REG32 DDP   : 1;     
__REG32 BRQ   : 1;     
__REG32 IMK   : 1;     
__REG32       :25;     
} __dmactmod_bits;

/* 10.4.6 DMA Transfer Source Address Registers (DMACSAD0–1) */
typedef struct{
__REG32 CSAD  :32;     
} __dmacsad_bits;

/* 10.4.7 DMA Transfer Destination Address Registers (DMACDAD0–1) */
typedef struct{
__REG32 CDAD  :32;     
} __dmacdad_bits;

/* 10.4.8 DMA Transfer Count Registers (DMACSIZ0–1) */
typedef struct{
__REG32 CSIZ  :17;     
__REG32       :15;     
} __dmacsiz_bits;

/* 10.4.9 DMA Completion Status Clear Registers (DMACCINT0–1) */
typedef struct{
__REG32 CCINT  :32;     
} __dmaccint_bits;

/* 11.4.1 Watchdog Timer Control Register (WDTCON) */
typedef struct{
__REG8  WDTCON0  : 1;     
__REG8  WDTCON1  : 1;     
__REG8  WDTCON2  : 1;     
__REG8  WDTCON3  : 1;     
__REG8  WDTCON4  : 1;     
__REG8  WDTCON5  : 1;     
__REG8  WDTCON6  : 1;     
__REG8  WDTCON7  : 1;     
} __wdtcon_bits;

/* 11.4.2 Time Base Counter Control Register (TBGCON) */
typedef struct{
__REG8  WDCKS0     : 1;     
__REG8  WDCKS1     : 1;     
__REG8  WDCKS2     : 1;     
__REG8             : 3;     
__REG8  OFINTMODE  : 1;     
__REG8  WDHLT      : 1;     
} __tbgcon_bits;

/* 11.4.3 Interrupt Status Register (INTST) */
typedef struct{
__REG8  RSTSTATUS  : 1;     
__REG8             : 3;     
__REG8  WDTINT     : 1;     
__REG8             : 3;     
} __intst_bits;

/* 11.4.4 WDTOVFN Assert Register (OVFAST) */
typedef struct{
__REG8  OVFAST0  : 1;     
__REG8  OVFAST1  : 1;     
__REG8  OVFAST2  : 1;     
__REG8  OVFAST3  : 1;     
__REG8  OVFAST4  : 1;     
__REG8  OVFAST5  : 1;     
__REG8  OVFAST6  : 1;     
__REG8  OVFAST7  : 1;     
} __ovfast_bits;

/* 11.4.5 WDT Counter Register (WDTCNT) */
typedef struct{
__REG16 WDTCNT0   : 1;     
__REG16 WDTCNT1   : 1;     
__REG16 WDTCNT2   : 1;     
__REG16 WDTCNT3   : 1;     
__REG16 WDTCNT4   : 1;     
__REG16 WDTCNT5   : 1;     
__REG16 WDTCNT6   : 1;     
__REG16 WDTCNT7   : 1;     
__REG16 WDTCNT8   : 1;     
__REG16 WDTCNT9   : 1;     
__REG16 WDTCNT10  : 1;     
__REG16 WDTCNT11  : 1;     
__REG16 WDTCNT12  : 1;     
__REG16 WDTCNT13  : 1;     
__REG16 WDTCNT14  : 1;     
__REG16 WDTCNT15  : 1;     
} __wdtcnt_bits;

/* 12.4.1 A/D Converter Control 0 Register (ADCON0) */
typedef struct{
__REG16 ADSNM  : 2;     
__REG16        : 2;     
__REG16 ADRUN  : 1;     
__REG16        : 1;     
__REG16 SCNC   : 1;     
__REG16        : 9;     
} __adcon0_bits;

/* 12.4.2 A/D Converter Control 1 Register (ADCON1) */
typedef struct{
__REG16 ADSTM  : 2;     
__REG16        : 2;     
__REG16 STS    : 1;     
__REG16        :11;     
} __adcon1_bits;

/* 12.4.3 A/D Converter Control 2 Register (ADCON2) */
typedef struct{
__REG16 ACKSEL  : 3;     
__REG16         :13;     
} __adcon2_bits;

/* 12.4.4 A/D Conversion Interrupt Control Register (ADINT) */
typedef struct{
__REG16 INTSN   : 1;     
__REG16 INTST   : 1;     
__REG16 ADSNIE  : 1;     
__REG16 ADSTIE  : 1;     
__REG16         :12;     
} __adint_bits;

/* 12.4.5 A/D Converter Forced Interrupt Generation Register (ADFINT) */
typedef struct{
__REG16 ADFAS  : 1;     
__REG16        :15;     
} __adfint_bits;

/* 12.4.6 A/D Conversion Result (0–3) Registers (ADR0–ADR3) */
typedef struct{
__REG16 DT  :10;     
__REG16     : 6;     
} __adr_bits;

/* 13.4.1 GPIO Port Output Register n (POn: n = 0 to 14) */
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

/* 13.4.2 GPIO Port Input Register n (PIn: n = 0 to 14) */
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

/* 13.4.3 GPIO Port Mode Register n (PMn: n = 0 to 14) */
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

/* 13.4.4 GPIO Interrupt Enable Register n (IEn: n = 0 to 14) */
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

/* 13.4.5 GPIO Interrupt Mode Register n (IMn: n = 0 to 14) */
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

/* 13.4.6 GPIO Interrupt Status Register n (ISn: n = 0 to 14) */
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

/* 14.4.1 I2C Slave Address Register (I2CSADR) */
typedef struct{
__REG16          : 1;     
__REG16 I2CSADR  :10;     
__REG16          : 5;     
} __i2csadr_bits;

/* 14.4.2 I2C Control Register (I2CCTL) */
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
__REG16               : 1;     
__REG16 I2CSTPIE      : 1;     
__REG16 I2C_DR_LDEN   : 1;     
__REG16 I2CCS         : 1;     
__REG16               : 2;     
} __i2cctl_bits;

/* 14.4.3 I2C Status Register (I2CSR) */
typedef struct{
__REG16 I2CRXAK   : 1;     
__REG16 I2CMIF    : 1;     
__REG16 I2CSRW    : 1;     
__REG16 I2CDR_LD  : 1;     
__REG16 I2CMAL    : 1;     
__REG16 I2CMBB    : 1;     
__REG16 I2CMAAS   : 1;     
__REG16 I2CMCF    : 1;     
__REG16           : 1;     
__REG16 I2CSTP    : 1;     
__REG16           : 6;     
} __i2csr_bits;

/* 14.4.4 I2C Data Register (I2CDR) */
typedef struct{
__REG16 I2CDA  : 8;     
__REG16        : 8;     
} __i2cdr_bits;

/* 14.4.5 I2C Bus Monitor Register (I2CMON) */
typedef struct{
__REG16 I2CSCL  : 1;     
__REG16 I2CSDA  : 1;     
__REG16         :14;     
} __i2cmon_bits;

/* 14.4.6 I2C Bus Transfer Rate Setup Counter(I2CBC) */
typedef struct{
__REG16 I2CBC  : 7;     
__REG16        : 9;     
} __i2cbc_bits;

/* 15.4.1 I2S FIFO Output Register (I2SFIFOO) */
typedef struct{
__REG32 tmain_wd  :16;     
__REG32           : 8;     
__REG32           : 8;     
} __i2sfifoo_bits;

/* 15.4.2 I2S Control Output Direction (I2SCONO) */
typedef struct{
__REG32 tset_issfso  : 2;     
__REG32 tset_ismsb   : 1;     
__REG32 tset_iswsl   : 1;     
__REG32 tset_isdly   : 1;     
__REG32 tset_isrun   : 1;     
__REG32 tset_issfo   : 2;     
__REG32 tset_issckf  : 1;     
__REG32 tset_isbit   : 2;     
__REG32 tset_afo     : 2;     
__REG32 tset_sdstop  : 1;     
__REG32              :10;     
__REG32              : 8;     
} __i2scono_bits;

/* 15.4.3 I2S CLK Control Output Direction (I2SCLKO) */
typedef struct{
__REG32 tset_isclr  : 1;     
__REG32             : 1;     
__REG32 tset_ismst  : 1;     
__REG32             :21;     
__REG32             : 8;     
} __i2sclko_bits;

/* 15.4.4 I2S Almost Full Register Output Direction (I2SAFRO) */
typedef struct{
__REG32 tset_isr0  : 6;     
__REG32            :18;     
__REG32            : 8;     
} __i2safro_bits;

/* 15.4.5 I2S Almost Empty Register Output Direction (I2SAERO) */
typedef struct{
__REG32 tset_isr1  : 6;     
__REG32            :18;     
__REG32            : 8;     
} __i2saero_bits;

/* 15.4.6 I2S Interrupt Mask Register Output Direction (I2SIMRO) */
typedef struct{
__REG32 tset_isfm   : 1;     
__REG32 tset_isafm  : 1;     
__REG32 tset_isem   : 1;     
__REG32 tset_isaem  : 1;     
__REG32 tset_dmam   : 1;     
__REG32             :19;     
__REG32             : 8;     
} __i2simro_bits;

/* 15.4.7 I2S Interrupt Status Register Output Direction (I2SISTO) */
typedef struct{
__REG32 tset_isfs   : 1;     
__REG32 tset_isafs  : 1;     
__REG32 tset_ises   : 1;     
__REG32 tset_isaes  : 1;     
__REG32             :20;     
__REG32             : 8;     
} __i2sisto_bits;

/* 15.4.8 I2S Left/Right Status & FIFO LEVEL Register Output Direction (I2SLRSO) */
typedef struct{
__REG32 tmon_lr   : 1;     
__REG32           : 7;     
__REG32 tfifolvl  : 9;     
__REG32           : 7;     
__REG32           : 8;     
} __i2slrso_bits;

/* 15.5.1 I2S FIFO Input Register (I2SFIFOI) */
typedef struct{
__REG32 rmain_rd  :16;     
__REG32           : 8;     
__REG32           : 8;     
} __i2sfifoi_bits;

/* 15.5.2 I2S Control Input Direction (I2SCONI) */
typedef struct{
__REG32 rset_issfso  : 2;     
__REG32 rset_ismsb   : 1;     
__REG32 rset_iswsl   : 1;     
__REG32 rset_isdly   : 1;     
__REG32 rset_isrun   : 1;     
__REG32 rset_issfo   : 2;     
__REG32 rset_issckf  : 1;     
__REG32 rset_isbit   : 2;     
__REG32 rset_afo     : 2;     
__REG32 rset_rdstop  : 1;     
__REG32              :10;     
__REG32              : 8;     
} __i2sconi_bits;

/* 15.5.3 I2S CLK Control Input Direction (I2SCLKI) */
typedef struct{
__REG32 rset_isclr  : 1;     
__REG32             : 1;     
__REG32 rset_ismst  : 1;     
__REG32             :21;     
__REG32             : 8;     
} __i2sclki_bits;

/* 15.5.4 I2S Almost Full Register Input Direction (I2SAFRI) */
typedef struct{
__REG32 rset_isr0  : 6;     
__REG32            :18;     
__REG32            : 8;     
} __i2safri_bits;

/* 15.5.5 I2S Almost Empty Register Input Direction (I2SAERI) */
typedef struct{
__REG32 rset_isr1  : 6;     
__REG32            :18;     
__REG32            : 8;     
} __i2saeri_bits;

/* 15.5.6 I2S Interrupt Mask Register Input Direction (I2SIMRI) */
typedef struct{
__REG32 rset_isfm   : 1;     
__REG32 rset_isafm  : 1;     
__REG32 rset_isem   : 1;     
__REG32 rset_isaem  : 1;     
__REG32 rset_dmam   : 1;     
__REG32             :19;     
__REG32             : 8;     
} __i2simri_bits;

/* 15.5.7 I2S Interrupt Status Register Input Direction (I2SISTI) */
typedef struct{
__REG32 rset_isfs   : 1;     
__REG32 rset_isafs  : 1;     
__REG32 rset_ises   : 1;     
__REG32 rset_isaes  : 1;     
__REG32             :20;     
__REG32             : 8;     
} __i2sisti_bits;

/* 15.5.8 I2S Left/Right Status & FIFO LEVEL Register Input Direction (I2SLRSI) */
typedef struct{
__REG32 rmon_lr   : 1;     
__REG32           : 7;     
__REG32 rfifolvl  : 9;     
__REG32           : 7;     
__REG32           : 8;     
} __i2slrsi_bits;

/* 16.4.2 1-Second Digit Register (S1) */
typedef struct{
__REG8  s1  : 4;     
__REG8      : 4;     
} __s1_bits;

/*16.4.3 10-Second Digit Register (S10) */
typedef struct{
__REG8  s10  : 4;     
__REG8       : 4;     
} __s10_bits;

/* 16.4.4 1-Minute Digit Register (M1) */
typedef struct{
__REG8  m1  : 4;     
__REG8      : 4;     
} __m1_bits;

/* 16.4.5 10-Minute Digit Register (M10) */
typedef struct{
__REG8  m10  : 4;     
__REG8       : 4;     
} __m10_bits;

/* 16.4.6 1-Hour Digit Register (H1) */
typedef struct{
__REG8  h1  : 4;     
__REG8      : 4;     
} __h1_bits;

/* 16.4.7 PM/AM 10-Hour Digit Register (H10) */
typedef struct{
__REG8  h10    : 2;     
__REG8  PM_AM  : 1;     
__REG8         : 5;     
} __h10_bits;

/* 16.4.8 1-Day Digit Register (D1) */
typedef struct{
__REG8  d1  : 4;     
__REG8      : 4;     
} __d1_bits;

/* 16.4.9 10-Day Digit Register (D10) */
typedef struct{
__REG8  d10  : 2;     
__REG8       : 6;     
} __d10_bits;

/* 16.4.10 1-Month Digit Register (MO1) */
typedef struct{
__REG8  mo1  : 4;     
__REG8       : 4;     
} __mo1_bits;

/* 16.4.11 10-Month Digit Register (MO10) */
typedef struct{
__REG8  mo10  : 1;     
__REG8        : 7;     
} __mo10_bits;

/* 16.4.12 1-Year Digit Register (Y1) */
typedef struct{
__REG8  y1  : 4;     
__REG8      : 4;     
} __y1_bits;

/* 16.4.13 10-Year Digit Register (Y10) */
typedef struct{
__REG8  y10  : 4;     
__REG8       : 4;     
} __y10_bits;

/* 16.4.14 Day-of-the-Week Register (W) */
typedef struct{
__REG8  w  : 3;     
__REG8     : 5;     
} __w_bits;

/* 16.4.15 Control Register D (CD) */
typedef struct{
__REG8  HOLD     : 1;     
__REG8  BUSY     : 1;     
__REG8  IRQFLAG  : 1;     
__REG8  _30sADJ  : 1;     
__REG8           : 4;     
} __cd_bits;

/* 16.4.16 Control Register E (CE) */
typedef struct{
__REG8  MASK        : 1;     
__REG8  ITRPT_STND  : 1;     
__REG8  T           : 2;     
__REG8              : 4;     
} __ce_bits;

/* 16.4.17 Control Register F (CF) */
typedef struct{
__REG8  REST    : 1;     
__REG8  STOP    : 1;     
__REG8  _24_12  : 1;     
__REG8  TEST    : 1;     
__REG8          : 4;     
} __cf_bits;


/* 17.4.9 UART Interrupt Enable Register n (UARTIERn: n = 0, 1) */
typedef struct {
__REG8  ERBFI  : 1;     
__REG8  ETBEI  : 1;     
__REG8  ELSI   : 1;     
__REG8  EDSSI  : 1;     
__REG8         : 4;     
} __uartier_bits;

/* 17.4.5 UART FIFO Control Register n (UARTFCRn: n = 0, 1)
   17.4.8 UART Interrupt Identification Register n (UARTIIRn: n = 0, 1) */
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
} __uartfcriir_bits;

/* 17.4.3 UART Line Control Register n (UARTLCRn: n = 0, 1) */
typedef struct{
__REG8  WLS   : 2;     
__REG8  SBS   : 1;     
__REG8  PE    : 1;     
__REG8  EPS   : 1;     
__REG8  SP    : 1;     
__REG8  BC    : 1;     
__REG8  DLAB  : 1;     
} __uartlcr_bits;

/* 17.4.4 UART Line Status Register n (UARTLSRn: n = 0, 1) */
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

/* 17.4.6 UART Modem Control Register n (UARTMCRn: n = 0, 1) */
typedef struct{
__REG8  DTR   : 1;     
__REG8  RTS   : 1;     
__REG8        : 2;     
__REG8  LOOP  : 1;     
__REG8        : 3;     
} __uartmcr_bits;

/* 17.4.7 UART Modem Status Register n (UARTMSRn: n = 0, 1) */
typedef struct{
__REG8  DCTS  : 1;     
__REG8  DDSR  : 1;     
__REG8  TERI  : 1;     
__REG8  DDCD  : 1;     
__REG8  CTS   : 1;     
__REG8  DSR   : 1;     
__REG8  RI    : 1;     
__REG8  RLSD  : 1;     
} __uartmsr_bits;


/* 18.4.1 SPI Control Register (SPCRn: n = 0, 1) */
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

/* 18.4.2 SPI Baud Rate Register (SPBRRn: n = 0, 1) */
typedef struct{
__REG32 SPBR  :10;     
__REG32 SIZE  : 1;     
__REG32       : 1;     
__REG32 LEAD  : 2;     
__REG32 LAG   : 2;     
__REG32 DTL   : 9;     
__REG32       : 7;     
} __spbrr_bits;

/* 18.4.3 SPI Status Register (SPSRn: n = 0, 1) */
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

/* 18.4.4 SPI Write Data Register (SPDWRn: n = 0, 1) */
typedef struct{
__REG32 DATA  :16;     
__REG32       :16;     
} __spdwr_bits;

/* 18.4.5 SPI Read Data Register (SPDRRn: n = 0, 1) */
typedef struct{
__REG32 DATA  :16;     
__REG32       :16;     
} __spdrr_bits;

/* 19.4.1 Timer Control Register n (FTMnCON: n = 0 to 5) */
typedef struct{
__REG16 FTMCLK  : 3;     
__REG16 MOD     : 2;     
__REG16         :11;     
} __ftmcon_bits;

/* 19.4.2 Timer Status Register n (FTMnST: n = 0 to 5) */
typedef struct{
__REG16 CM_CAPEV  : 1;     
__REG16 OVF       : 1;     
__REG16           :14;     
} __ftmst_bits;

/* 19.4.3 Timer Counter n (FTMnC: n = 0 to 5) */
typedef struct{
__REG16 FTMC  :16;     
} __ftmc_bits;

/* 19.4.4 Timer Register n (FTMnR: n = 0 to 5) */
typedef struct{
__REG16 FTMR  :16;     
} __ftmr_bits;

/* 19.4.5 General-Purpose Timer Register n (FTMnGR: n = 0 to 5) */
typedef struct{
__REG16 FTMGR  :16;     
} __ftmgr_bits;

/* 19.4.6 Timer Input/Output Level Register n (FTMnIOLV: n = 0 to 5) */
typedef struct{
__REG16 IOLV  : 2;     
__REG16       :14;     
} __ftmiolv_bits;

/* 19.4.7 Timer Output Level Register n (FTMnOUT: n = 0 to 5) */
typedef struct{
__REG16 FTMOUT  : 1;     
__REG16         :15;     
} __ftmout_bits;

/* 19.4.8 Timer Interrupt Enable Register n (FTMnIER: n = 0 to 5) */
typedef struct{
__REG16 CMOIE_CAPIE  : 1;     
__REG16 OVFIE        : 1;     
__REG16              :14;     
} __ftmier_bits;

/* 19.4.9 Timer Enable (FTMEN) Register */
typedef struct{
__REG16 FTMEN0  : 1;     
__REG16 FTMEN1  : 1;     
__REG16 FTMEN2  : 1;     
__REG16 FTMEN3  : 1;     
__REG16 FTMEN4  : 1;     
__REG16 FTMEN5  : 1;     
__REG16         :10;     
} __ftmen_bits;

/* 19.4.10 Timer Disable (FTMDIS) Register */
typedef struct{
__REG16 FTMDIS0  : 1;     
__REG16 FTMDIS1  : 1;     
__REG16 FTMDIS2  : 1;     
__REG16 FTMDIS3  : 1;     
__REG16 FTMDIS4  : 1;     
__REG16 FTMDIS5  : 1;     
__REG16          :10;     
} __ftmdis_bits;

/* 20.4.1 Flash ROM Control Register (FLACON) */
typedef struct{
__REG32 FLWE     : 1;     
__REG32 FWEND    : 1;     
__REG32 BUSY     : 1;     
__REG32 BUSYNVW  : 1;     
__REG32 SEQMD    : 1;     
__REG32 SEQM     : 1;     
__REG32 FLRST    : 1;     
__REG32          :25;     
} __flacon_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 ** Memory Control
 **
 ***************************************************************************/
__IO_REG32_BIT(RMPCON,    0xB8000010,__READ_WRITE,__rmpcon_bits);

/***************************************************************************
 **
 ** Clock/Reset
 **
 ***************************************************************************/
__IO_REG32_BIT(IDR,       0xB8000000,__READ      ,__idr_bits);
__IO_REG32_BIT(CLKSTP,    0xB8000004,__READ_WRITE,__clkstp_bits);
__IO_REG32_BIT(PECLKCTL,  0xB7000000,__READ_WRITE,__peclkctl_bits);
__IO_REG32_BIT(PERSTCTL,  0xB7000004,__READ_WRITE,__perstctl_bits);
__IO_REG32_BIT(PLL1,      0xB7000008,__READ_WRITE,__pll1_bits);
__IO_REG32_BIT(PLL2,      0xB700000C,__READ_WRITE,__pll2_bits);
__IO_REG32_BIT(CLKCNT,    0xB7000010,__READ_WRITE,__clkcnt_bits);
__IO_REG32_BIT(CLKSTPCNT, 0xB7000014,__READ_WRITE,__clkstpcnt_bits);
__IO_REG32_BIT(CKWT,      0xB7000044,__READ_WRITE,__ckwt_bits);

/***************************************************************************
 **
 ** LSI Control Functions
 **
 ***************************************************************************/
__IO_REG32_BIT(DMARQCNT,  0xB700001C,__READ_WRITE,__dmarqcnt_bits);
__IO_REG32_BIT(LSICNT,    0xB7000020,__READ_WRITE,__lsicnt_bits);
__IO_REG32_BIT(PORTSEL1,  0xB7000024,__READ_WRITE,__portsel1_bits);
__IO_REG32_BIT(PORTSEL2,  0xB7000028,__READ_WRITE,__portsel2_bits);
__IO_REG32_BIT(PORTSEL3,  0xB700002C,__READ_WRITE,__portsel3_bits);
__IO_REG32_BIT(PORTSEL4,  0xB7000030,__READ_WRITE,__portsel4_bits);
__IO_REG32_BIT(PORTSEL5,  0xB7000034,__READ_WRITE,__portsel5_bits);
__IO_REG32_BIT(FTMSEL,    0xB7000040,__READ_WRITE,__ftmsel_bits);

/***************************************************************************
 **
 ** Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQ,       0x78000000,__READ      ,__irq_bits);
__IO_REG32_BIT(IRQS,      0x78000004,__READ_WRITE,__irqs_bits);
__IO_REG32_BIT(FIQ,       0x78000008,__READ      ,__fiq_bits);
__IO_REG32_BIT(FIQRAW,    0x7800000C,__READ      ,__fiqraw_bits);
__IO_REG32_BIT(FIQEN,     0x78000010,__READ_WRITE,__fiqen_bits);
__IO_REG32_BIT(IRN,       0x78000014,__READ      ,__irn_bits);
__IO_REG32_BIT(CIL,       0x78000018,__READ_WRITE,__cil_bits);
__IO_REG32_BIT(ILC0,      0x78000020,__READ_WRITE,__ilc0_bits);
__IO_REG32_BIT(ILC1,      0x78000024,__READ_WRITE,__ilc1_bits);
__IO_REG32_BIT(CILCL,     0x78000028,__WRITE     ,__cilcl_bits);
__IO_REG32_BIT(CILE,      0x7800002C,__READ      ,__cile_bits);
__IO_REG32_BIT(EXIRS,     0x7BF00000,__READ      ,__exirs_bits);
__IO_REG32_BIT(EXIRCL,    0x7BF00004,__WRITE     ,__exircl_bits);
__IO_REG32_BIT(EXIRQA,    0x7BF00010,__READ      ,__exirqa_bits);
__IO_REG32_BIT(EXILCA,    0x7BF00018,__READ_WRITE,__exilca_bits);
__IO_REG32_BIT(EXIRQSA,   0x7BF0001C,__READ      ,__exirqsa_bits);
__IO_REG32_BIT(EXIRQB,    0x7BF00020,__READ_WRITE,__exirqb_bits);
__IO_REG32_BIT(EXIDM,     0x7BF00024,__READ_WRITE,__exidm_bits);
__IO_REG32_BIT(EXILCB,    0x7BF00028,__READ_WRITE,__exilcb_bits);
__IO_REG32_BIT(EXIRQSB,   0x7BF0002C,__READ_WRITE,__exirqsb_bits);
__IO_REG32_BIT(EXIRQC,    0x7BF00030,__READ      ,__exirqc_bits);
__IO_REG32_BIT(EXILCC,    0x7BF00038,__READ_WRITE,__exilcc_bits);
__IO_REG32_BIT(EXIRQSC,   0x7BF0003C,__READ      ,__exirqsc_bits);
__IO_REG32_BIT(EXFIQ,     0x7BF00080,__READ_WRITE,__exfiq_bits);
__IO_REG32_BIT(EXFIDM,    0x7BF00084,__READ_WRITE,__exfidm_bits);

/***************************************************************************
 **
 ** External Memory Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(BWC,       0x78100000,__READ_WRITE,__bwc_bits);
__IO_REG32_BIT(ROMAC,     0x78100004,__READ_WRITE,__romac_bits);
__IO_REG32_BIT(RAMAC,     0x78100008,__READ_WRITE,__ramac_bits);
__IO_REG32_BIT(IO0AC,     0x7810000C,__READ_WRITE,__io0ac_bits);
__IO_REG32_BIT(IO1AC,     0x78100010,__READ_WRITE,__io1ac_bits);

/***************************************************************************
 **
 ** SIO (in µPLAT)
 **
 ***************************************************************************/
__IO_REG32_BIT(SIOBUF,    0xB8002000,__READ_WRITE,__siobuf_bits);
__IO_REG32_BIT(SIOSTA,    0xB8002004,__READ_WRITE,__siosta_bits);
__IO_REG32_BIT(SIOCON,    0xB8002008,__READ_WRITE,__siocon_bits);
__IO_REG32_BIT(SIOBCN,    0xB800200C,__READ_WRITE,__siobcn_bits);
__IO_REG32_BIT(SIOBT,     0xB8002014,__READ_WRITE,__siobt_bits);
__IO_REG32_BIT(SIOTCN,    0xB8002018,__READ_WRITE,__siotcn_bits);

/***************************************************************************
 **
 ** System Timer
 **
 ***************************************************************************/
__IO_REG32_BIT(TMEN,      0xB8001004,__READ_WRITE,__tmen_bits);
__IO_REG32_BIT(TMRLR,     0xB8001008,__READ_WRITE,__tmrlr_bits);
__IO_REG32_BIT(TMOVF,     0xB8001010,__READ_WRITE,__tmovf_bits);

/***************************************************************************
 **
 ** DMAC
 **
 ***************************************************************************/
__IO_REG32_BIT(DMAMOD,    0x7BE00000,__READ_WRITE,__dmamod_bits);
__IO_REG32_BIT(DMASTA,    0x7BE00004,__READ      ,__dmasta_bits);
__IO_REG32_BIT(DMAINT,    0x7BE00008,__READ      ,__dmaint_bits);
__IO_REG32_BIT(DMACMSK0,  0x7BE00100,__READ_WRITE,__dmacmsk_bits);
__IO_REG32_BIT(DMACTMOD0, 0x7BE00104,__READ_WRITE,__dmactmod_bits);
__IO_REG32_BIT(DMACSAD0,  0x7BE00108,__READ_WRITE,__dmacsad_bits);
__IO_REG32_BIT(DMACDAD0,  0x7BE0010C,__READ_WRITE,__dmacdad_bits);
__IO_REG32_BIT(DMACSIZ0,  0x7BE00110,__READ_WRITE,__dmacsiz_bits);
__IO_REG32_BIT(DMACCINT0, 0x7BE00114,__WRITE     ,__dmaccint_bits);
__IO_REG32_BIT(DMACMSK1,  0x7BE00200,__READ_WRITE,__dmacmsk_bits);
__IO_REG32_BIT(DMACTMOD1, 0x7BE00204,__READ_WRITE,__dmactmod_bits);
__IO_REG32_BIT(DMACSAD1,  0x7BE00208,__READ_WRITE,__dmacsad_bits);
__IO_REG32_BIT(DMACDAD1,  0x7BE0020C,__READ_WRITE,__dmacdad_bits);
__IO_REG32_BIT(DMACSIZ1,  0x7BE00210,__READ_WRITE,__dmacsiz_bits);
__IO_REG32_BIT(DMACCINT1, 0x7BE00214,__WRITE     ,__dmaccint_bits);

/***************************************************************************
 **
 ** WDT
 **
 ***************************************************************************/
__IO_REG8_BIT( WDTCON,    0xB7E00000,__WRITE     ,__wdtcon_bits);
__IO_REG8_BIT( TBGCON,    0xB7E00004,__READ_WRITE,__tbgcon_bits);
__IO_REG8_BIT( INTST,     0xB7E00008,__READ_WRITE,__intst_bits);
__IO_REG8_BIT( OVFAST,    0xB7E0000C,__READ_WRITE,__ovfast_bits);
__IO_REG16_BIT(WDTCNT,    0xB7E00010,__READ_WRITE,__wdtcnt_bits);

/***************************************************************************
 **
 ** A/D Converter
 **
 ***************************************************************************/
__IO_REG16_BIT(ADCON0,    0xB6000000,__READ_WRITE,__adcon0_bits);
__IO_REG16_BIT(ADCON1,    0xB6000004,__READ_WRITE,__adcon1_bits);
__IO_REG16_BIT(ADCON2,    0xB6000008,__READ_WRITE,__adcon2_bits);
__IO_REG16_BIT(ADINT,     0xB600000C,__READ_WRITE,__adint_bits);
__IO_REG16_BIT(ADFINT,    0xB6000010,__READ_WRITE,__adfint_bits);
__IO_REG16_BIT(ADR0,      0xB6000014,__READ_WRITE,__adr_bits);
__IO_REG16_BIT(ADR1,      0xB6000018,__READ_WRITE,__adr_bits);
__IO_REG16_BIT(ADR2,      0xB600001C,__READ_WRITE,__adr_bits);
__IO_REG16_BIT(ADR3,      0xB6000020,__READ_WRITE,__adr_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG8_BIT( PO0,       0xB7A00000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI0,       0xB7A00004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM0,       0xB7A00008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE0,       0xB7A0000C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM0,       0xB7A00010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS0,       0xB7A00018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO1,       0xB7A01000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI1,       0xB7A01004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM1,       0xB7A01008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE1,       0xB7A0100C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM1,       0xB7A01010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS1,       0xB7A01018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO2,       0xB7A02000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI2,       0xB7A02004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM2,       0xB7A02008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE2,       0xB7A0200C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM2,       0xB7A02010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS2,       0xB7A02018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO3,       0xB7A03000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI3,       0xB7A03004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM3,       0xB7A03008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE3,       0xB7A0300C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM3,       0xB7A03010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS3,       0xB7A03018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO4,       0xB7A04000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI4,       0xB7A04004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM4,       0xB7A04008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE4,       0xB7A0400C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM4,       0xB7A04010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS4,       0xB7A04018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO5,       0xB7A05000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI5,       0xB7A05004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM5,       0xB7A05008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE5,       0xB7A0500C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM5,       0xB7A05010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS5,       0xB7A05018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO6,       0xB7A06000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI6,       0xB7A06004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM6,       0xB7A06008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE6,       0xB7A0600C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM6,       0xB7A06010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS6,       0xB7A06018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO7,       0xB7A07000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI7,       0xB7A07004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM7,       0xB7A07008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE7,       0xB7A0700C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM7,       0xB7A07010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS7,       0xB7A07018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO8,       0xB7A08000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI8,       0xB7A08004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM8,       0xB7A08008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE8,       0xB7A0800C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM8,       0xB7A08010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS8,       0xB7A08018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO9,       0xB7A09000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI9,       0xB7A09004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM9,       0xB7A09008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE9,       0xB7A0900C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM9,       0xB7A09010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS9,       0xB7A09018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO10,      0xB7A0A000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI10,      0xB7A0A004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM10,      0xB7A0A008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE10,      0xB7A0A00C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM10,      0xB7A0A010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS10,      0xB7A0A018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO11,      0xB7A0B000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI11,      0xB7A0B004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM11,      0xB7A0B008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE11,      0xB7A0B00C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM11,      0xB7A0B010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS11,      0xB7A0B018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO12,      0xB7A0C000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI12,      0xB7A0C004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM12,      0xB7A0C008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE12,      0xB7A0C00C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM12,      0xB7A0C010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS12,      0xB7A0C018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO13,      0xB7A0D000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI13,      0xB7A0D004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM13,      0xB7A0D008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE13,      0xB7A0D00C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM13,      0xB7A0D010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS13,      0xB7A0D018,__READ_WRITE,__is_bits);
__IO_REG8_BIT( PO14,      0xB7A0E000,__READ_WRITE,__po_bits);
__IO_REG8_BIT( PI14,      0xB7A0E004,__READ      ,__pi_bits);
__IO_REG8_BIT( PM14,      0xB7A0E008,__READ_WRITE,__pm_bits);
__IO_REG8_BIT( IE14,      0xB7A0E00C,__READ_WRITE,__ie_bits);
__IO_REG32_BIT(IM14,      0xB7A0E010,__READ_WRITE,__im_bits);
__IO_REG8_BIT( IS14,      0xB7A0E018,__READ_WRITE,__is_bits);

/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG16_BIT(I2CSADR,   0xB7800C00,__READ_WRITE,__i2csadr_bits);
__IO_REG16_BIT(I2CCTL,    0xB7800C04,__READ_WRITE,__i2cctl_bits);
__IO_REG16_BIT(I2CSR,     0xB7800C08,__READ_WRITE,__i2csr_bits);
__IO_REG16_BIT(I2CDR,     0xB7800C0C,__READ_WRITE,__i2cdr_bits);
__IO_REG16_BIT(I2CMON,    0xB7800C10,__READ      ,__i2cmon_bits);
__IO_REG16_BIT(I2CBC,     0xB7800C14,__READ_WRITE,__i2cbc_bits);

/***************************************************************************
 **
 ** I2S
 **
 ***************************************************************************/
__IO_REG32_BIT(I2SFIFOO,  0xB7900000,__READ_WRITE,__i2sfifoo_bits);
__IO_REG32_BIT(I2SCONO,   0xB7900004,__READ_WRITE,__i2scono_bits);
__IO_REG32_BIT(I2SCLKO,   0xB7900008,__READ_WRITE,__i2sclko_bits);
__IO_REG32_BIT(I2SAFRO,   0xB790000C,__READ_WRITE,__i2safro_bits);
__IO_REG32_BIT(I2SAERO,   0xB7900010,__READ_WRITE,__i2saero_bits);
__IO_REG32_BIT(I2SIMRO,   0xB7900014,__READ_WRITE,__i2simro_bits);
__IO_REG32_BIT(I2SISTO,   0xB7900018,__READ_WRITE,__i2sisto_bits);
__IO_REG32_BIT(I2SLRSO,   0xB790001C,__READ      ,__i2slrso_bits);
__IO_REG32_BIT(I2SFIFOI,  0xB7900020,__READ      ,__i2sfifoi_bits);
__IO_REG32_BIT(I2SCONI,   0xB7900024,__READ_WRITE,__i2sconi_bits);
__IO_REG32_BIT(I2SCLKI,   0xB7900028,__READ_WRITE,__i2sclki_bits);
__IO_REG32_BIT(I2SAFRI,   0xB790002C,__READ_WRITE,__i2safri_bits);
__IO_REG32_BIT(I2SAERI,   0xB7900030,__READ_WRITE,__i2saeri_bits);
__IO_REG32_BIT(I2SIMRI,   0xB7900034,__READ_WRITE,__i2simri_bits);
__IO_REG32_BIT(I2SISTI,   0xB7900038,__READ_WRITE,__i2sisti_bits);
__IO_REG32_BIT(I2SLRSI,   0xB790003C,__READ      ,__i2slrsi_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG8_BIT( S1,        0xB7C00000,__READ_WRITE,__s1_bits);
__IO_REG8_BIT( S10,       0xB7C00004,__READ_WRITE,__s10_bits);
__IO_REG8_BIT( M1,        0xB7C00008,__READ_WRITE,__m1_bits);
__IO_REG8_BIT( M10,       0xB7C0000C,__READ_WRITE,__m10_bits);
__IO_REG8_BIT( H1,        0xB7C00010,__READ_WRITE,__h1_bits);
__IO_REG8_BIT( H10,       0xB7C00014,__READ_WRITE,__h10_bits);
__IO_REG8_BIT( D1,        0xB7C00018,__READ_WRITE,__d1_bits);
__IO_REG8_BIT( D10,       0xB7C0001C,__READ_WRITE,__d10_bits);
__IO_REG8_BIT( MO1,       0xB7C00020,__READ_WRITE,__mo1_bits);
__IO_REG8_BIT( MO10,      0xB7C00024,__READ_WRITE,__mo10_bits);
__IO_REG8_BIT( Y1,        0xB7C00028,__READ_WRITE,__y1_bits);
__IO_REG8_BIT( Y10,       0xB7C0002C,__READ_WRITE,__y10_bits);
__IO_REG8_BIT( W,         0xB7C00030,__READ_WRITE,__w_bits);
__IO_REG8_BIT( CD,        0xB7C00034,__READ_WRITE,__cd_bits);
__IO_REG8_BIT( CE,        0xB7C00038,__READ_WRITE,__ce_bits);
__IO_REG8_BIT( CF,        0xB7C0003C,__READ_WRITE,__cf_bits);

/***************************************************************************
 **
 ** UART 0
 **
 ***************************************************************************/

/* UARTDLL0, UARTRBR0 and UARTTHR0 share the same address */
__IO_REG8(UARTRBRTHR0, 0xB7B00000,__READ_WRITE);
#define UARTDLL0 UARTRBRTHR0
#define UARTRBR0 UARTRBRTHR0
#define UARTTHR0 UARTRBRTHR0

/* UARTDLM0 and UARTIER0 share the same address */
__IO_REG8_BIT(UARTIER0, 0xB7B00004,__READ_WRITE,__uartier_bits);
#define UARTDLM0     UARTIER0

/* UARTFCR0 and UARTIIR0 share the same address */
__IO_REG8_BIT(UARTFCRIIR0, 0xB7B00008,__READ_WRITE,__uartfcriir_bits);
#define UARTFCR0     UARTFCRIIR0
#define UARTFCR0_bit UARTFCRIIR0_bit
#define UARTIIR0     UARTFCRIIR0
#define UARTIIR0_bit UARTFCRIIR0_bit

__IO_REG8_BIT(UARTLCR0, 0xB7B0000C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(UARTMCR0, 0xB7B00010,__READ_WRITE,__uartmcr_bits);
__IO_REG8_BIT(UARTLSR0, 0xB7B00014,__READ_WRITE,__uartlsr_bits);
__IO_REG8_BIT(UARTMSR0, 0xB7B00018,__READ_WRITE,__uartmsr_bits);
__IO_REG8(UARTSCR0, 0xB7B0001C,__READ_WRITE);

/***************************************************************************
 **
 ** UART 1
 **
 ***************************************************************************/

/* UARTDLL1, UARTRBR1 and UARTTHR1 share the same address */
__IO_REG8(UARTRBRTHR1, 0xB7B01000,__READ_WRITE);
#define UARTDLL1 UARTRBRTHR1
#define UARTRBR1 UARTRBRTHR1
#define UARTTHR1 UARTRBRTHR1

/* UARTDLM1 and UARTIER1 share the same address */
__IO_REG8_BIT(UARTIER1, 0xB7B01004,__READ_WRITE,__uartier_bits);
#define UARTDLM1     UARTIER1

/* UARTFCR0 and UARTIIR0 share the same address */
__IO_REG8_BIT(UARTFCRIIR1, 0xB7B01008,__READ_WRITE,__uartfcriir_bits);
#define UARTFCR1     UARTFCRIIR1
#define UARTFCR1_bit UARTFCRIIR1_bit
#define UARTIIR1     UARTFCRIIR1
#define UARTIIR1_bit UARTFCRIIR1_bit

__IO_REG8_BIT(UARTLCR1, 0xB7B0100C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(UARTMCR1, 0xB7B01010,__READ_WRITE,__uartmcr_bits);
__IO_REG8_BIT(UARTLSR1, 0xB7B01014,__READ_WRITE,__uartlsr_bits);
__IO_REG8_BIT(UARTMSR1, 0xB7B01018,__READ_WRITE,__uartmsr_bits);
__IO_REG8(UARTSCR1, 0xB7B0101C,__READ_WRITE);



/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(SPCR0,     0xB7B02000,__READ_WRITE,__spcr_bits);
__IO_REG32_BIT(SPBRR0,    0xB7B02004,__READ_WRITE,__spbrr_bits);
__IO_REG32_BIT(SPSR0,     0xB7B02008,__READ_WRITE,__spsr_bits);
__IO_REG32_BIT(SPDWR0,    0xB7B0200C,__READ_WRITE,__spdwr_bits);
__IO_REG32_BIT(SPDRR0,    0xB7B02010,__READ      ,__spdrr_bits);
__IO_REG32(    TEST0,     0xB7B02014,__READ      );
__IO_REG32_BIT(SPCR1,     0xB7B03000,__READ_WRITE,__spcr_bits);
__IO_REG32_BIT(SPBRR1,    0xB7B03004,__READ_WRITE,__spbrr_bits);
__IO_REG32_BIT(SPSR1,     0xB7B03008,__READ_WRITE,__spsr_bits);
__IO_REG32_BIT(SPDWR1,    0xB7B0300C,__READ_WRITE,__spdwr_bits);
__IO_REG32_BIT(SPDRR1,    0xB7B03010,__READ      ,__spdrr_bits);
__IO_REG32(    TEST1,     0xB7B03014,__READ      );

/***************************************************************************
 **
 ** FTM
 **
 ***************************************************************************/
__IO_REG16_BIT(FTM0CON,   0xB7F00000,__READ_WRITE,__ftmcon_bits);
__IO_REG16_BIT(FTM0ST,    0xB7F00004,__READ_WRITE,__ftmst_bits);
__IO_REG16_BIT(FTM0C,     0xB7F00008,__READ_WRITE,__ftmc_bits);
__IO_REG16_BIT(FTM0R,     0xB7F0000C,__READ_WRITE,__ftmr_bits);
__IO_REG16_BIT(FTM0GR,    0xB7F00010,__READ_WRITE,__ftmgr_bits);
__IO_REG16_BIT(FTM0IOLV,  0xB7F00014,__READ_WRITE,__ftmiolv_bits);
__IO_REG16_BIT(FTM0OUT,   0xB7F00018,__READ_WRITE,__ftmout_bits);
__IO_REG16_BIT(FTM0IER,   0xB7F0001C,__READ_WRITE,__ftmier_bits);
__IO_REG16_BIT(FTM1CON,   0xB7F00020,__READ_WRITE,__ftmcon_bits);
__IO_REG16_BIT(FTM1ST,    0xB7F00024,__READ_WRITE,__ftmst_bits);
__IO_REG16_BIT(FTM1C,     0xB7F00028,__READ_WRITE,__ftmc_bits);
__IO_REG16_BIT(FTM1R,     0xB7F0002C,__READ_WRITE,__ftmr_bits);
__IO_REG16_BIT(FTM1GR,    0xB7F00030,__READ_WRITE,__ftmgr_bits);
__IO_REG16_BIT(FTM1IOLV,  0xB7F00034,__READ_WRITE,__ftmiolv_bits);
__IO_REG16_BIT(FTM1OUT,   0xB7F00038,__READ_WRITE,__ftmout_bits);
__IO_REG16_BIT(FTM1IER,   0xB7F0003C,__READ_WRITE,__ftmier_bits);
__IO_REG16_BIT(FTM2CON,   0xB7F00040,__READ_WRITE,__ftmcon_bits);
__IO_REG16_BIT(FTM2ST,    0xB7F00044,__READ_WRITE,__ftmst_bits);
__IO_REG16_BIT(FTM2C,     0xB7F00048,__READ_WRITE,__ftmc_bits);
__IO_REG16_BIT(FTM2R,     0xB7F0004C,__READ_WRITE,__ftmr_bits);
__IO_REG16_BIT(FTM2GR,    0xB7F00050,__READ_WRITE,__ftmgr_bits);
__IO_REG16_BIT(FTM2IOLV,  0xB7F00054,__READ_WRITE,__ftmiolv_bits);
__IO_REG16_BIT(FTM2OUT,   0xB7F00058,__READ_WRITE,__ftmout_bits);
__IO_REG16_BIT(FTM2IER,   0xB7F0005C,__READ_WRITE,__ftmier_bits);
__IO_REG16_BIT(FTM3CON,   0xB7F00060,__READ_WRITE,__ftmcon_bits);
__IO_REG16_BIT(FTM3ST,    0xB7F00064,__READ_WRITE,__ftmst_bits);
__IO_REG16_BIT(FTM3C,     0xB7F00068,__READ_WRITE,__ftmc_bits);
__IO_REG16_BIT(FTM3R,     0xB7F0006C,__READ_WRITE,__ftmr_bits);
__IO_REG16_BIT(FTM3GR,    0xB7F00070,__READ_WRITE,__ftmgr_bits);
__IO_REG16_BIT(FTM3IOLV,  0xB7F00074,__READ_WRITE,__ftmiolv_bits);
__IO_REG16_BIT(FTM3OUT,   0xB7F00078,__READ_WRITE,__ftmout_bits);
__IO_REG16_BIT(FTM3IER,   0xB7F0007C,__READ_WRITE,__ftmier_bits);
__IO_REG16_BIT(FTM4CON,   0xB7F00080,__READ_WRITE,__ftmcon_bits);
__IO_REG16_BIT(FTM4ST,    0xB7F00084,__READ_WRITE,__ftmst_bits);
__IO_REG16_BIT(FTM4C,     0xB7F00088,__READ_WRITE,__ftmc_bits);
__IO_REG16_BIT(FTM4R,     0xB7F0008C,__READ_WRITE,__ftmr_bits);
__IO_REG16_BIT(FTM4GR,    0xB7F00090,__READ_WRITE,__ftmgr_bits);
__IO_REG16_BIT(FTM4IOLV,  0xB7F00094,__READ_WRITE,__ftmiolv_bits);
__IO_REG16_BIT(FTM4OUT,   0xB7F00098,__READ_WRITE,__ftmout_bits);
__IO_REG16_BIT(FTM4IER,   0xB7F0009C,__READ_WRITE,__ftmier_bits);
__IO_REG16_BIT(FTM5CON,   0xB7F000A0,__READ_WRITE,__ftmcon_bits);
__IO_REG16_BIT(FTM5ST,    0xB7F000A4,__READ_WRITE,__ftmst_bits);
__IO_REG16_BIT(FTM5C,     0xB7F000A8,__READ_WRITE,__ftmc_bits);
__IO_REG16_BIT(FTM5R,     0xB7F000AC,__READ_WRITE,__ftmr_bits);
__IO_REG16_BIT(FTM5GR,    0xB7F000B0,__READ_WRITE,__ftmgr_bits);
__IO_REG16_BIT(FTM5IOLV,  0xB7F000B4,__READ_WRITE,__ftmiolv_bits);
__IO_REG16_BIT(FTM5OUT,   0xB7F000B8,__READ_WRITE,__ftmout_bits);
__IO_REG16_BIT(FTM5IER,   0xB7F000BC,__READ_WRITE,__ftmier_bits);
__IO_REG16_BIT(FTMEN,     0xB7F000C0,__READ_WRITE,__ftmen_bits);
__IO_REG16_BIT(FTMDIS,    0xB7F000C4,__WRITE     ,__ftmdis_bits);

/***************************************************************************
 **
 ** Built-in Flash ROM Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(FLACON,    0xB7000100,__READ_WRITE,__flacon_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */




/***************************************************************************
 **
 **   ML674051 interrupt sources
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
#define INT_UART0           9
#define INT_SIO0            10
#define INT_ADC             11
#define INT_UART1           12
#define INT_SPI0            13
#define INT_SPI1            14
#define INT_I2C             15
#define INT_TIMER0          16
#define INT_TIMER1          17
#define INT_TIMER2          18
#define INT_TIMER3          19
#define INT_TIMER4          20
#define INT_TIMER5          21
#define INT_I2S             22
// #define RESERVE          23
#define INT_DMA0            24
#define INT_DMA1            25
#define INT_RTC             26
// #define RESERVE          27
#define INT_GPIO4           28
#define INT_GPIO5           29
// #define RESERVE          30
// #define RESERVE          31
// #define RESERVE          32
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
#define INT_GPIO6           44
#define INT_GPIO7           45
#define INT_GPIO8           46
#define INT_GPIO9           47
#define INT_GPIO10          48
#define INT_GPIO11          49
#define INT_GPIO12          50
#define INT_GPIO13          51
#define INT_GPIO14          52
// #define RESERVE          53
// #define RESERVE          54
// #define RESERVE          55
// #define RESERVE          56
// #define RESERVE          57
// #define RESERVE          58
// #define RESERVE          59
// #define RESERVE          60
// #define RESERVE          61
// #define RESERVE          62
// #define RESERVE          63

#endif    /* __ML674001_H */
