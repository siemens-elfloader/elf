/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung S3F445HX
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.4 $
 **
 ***************************************************************************/

#ifndef __S3F445HX_H
#define __S3F445HX_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3F445HX SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* System Configuration register (SYSCFG) */
typedef struct {
  __REG32 ST    :1; /* Stall enable */
  __REG32       :3; /* Reserved */  
  __REG32 SFRSA :9; /* SYSCFG Address(SFRs Start Address) */
  __REG32       :19;
} __syscfg_bits;


/* SM: Memory Control register (MEMCONx) */
typedef struct {
  __REG32 DW   :1; /* Data Bus Width */
  __REG32 MT   :1; /* Memory Type */
  __REG32 Tcos :2; /* Setup time of nCS before nOE */
  __REG32 Tacs :2; /* Address Set-up time before nCS */
  __REG32 Tcoh :2; /* Hold time of nCS after nOE  */
  __REG32 Tacc :4; /* Access cycle */
  __REG32 BAP  :9; /* Memory bank Base Address Pointer */
  __REG32 EAP  :9; /* Memory bank End Address Pointer */
  __REG32      :2; /* Reserved     */
} __memcon_bits;


/* Flash Memory User Programming Control register (FMUCON) */
typedef struct {
  __REG8 OSE   :1; /* Chip Erase Enable */
  __REG8 NSE   :1; /* Normal Sector Erase Enable */
  __REG8 OSP   :1; /* Option(protection/smart option) Sector Program Enable */
  __REG8 NSP   :1; /* Normal Sector Program Enable */
  __REG8       :3; /* Reserved */
  __REG8 START :1; /* Operation Start/Stop */
} __fmucon_bits;


/* Flash Memory Error register (FMERR) */
typedef struct {
  __REG8 CL     :1; /* Clear FMKEY /FMUCON register */
  __REG8        :6; /* Reserved */
  __REG8 CFGERR :1; /* Configuration error */
} __fmerr_bits;


/* Flash Memory Access control register (FMACON) */
typedef struct {
  __REG8 TACC  :2; /* Flash memory access cycles */
  __REG8       :5; /* Reserved */
  __REG8 HFO   :1; /* CPU hold during Flash operation */
} __fmacon_bits;


/* Port0 data/pulldown register (PDAT0, PDR0) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8 P7 :1;
} __port0_bits;


/* Port0 control register (PCON0) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16 P7 :2;
} __pcon0_bits;


/* Port1 data/pulldown register (PDAT1, PDR1) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8 P7 :1;
} __port1_bits;


/* Port1 control register (PCON1) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16 P7 :2;
} __pcon1_bits;


/* Port2 data/pulldown register (PDAT2, PDR2) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8    :1;
  __REG8    :1;
} __port2_bits;


/* Port2 control register (PCON2) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16    :2;
  __REG16    :2;
} __pcon2_bits;


/* Port3 data/pullup register (PDAT3, PUR3) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8 P7 :1;
} __port3_bits;


/* Port3 control register (PCON3) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16 P7 :2;
} __pcon3_bits;


/* Port4 data/pullup register (PDAT4, PUR4) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8 P7 :1;
} __port4_bits;


/* Port4 control register (PCON4) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16 P7 :2;
} __pcon4_bits;


/* Port5 data/pullup register (PDAT5, PUR5) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8 P7 :1;
} __port5_bits;


/* Port5 control register (PCON5) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16 P7 :2;
} __pcon5_bits;


/* Port6 data/pullup register (PDAT6, PUR6) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8    :1;
} __port6_bits;


/* Port6 control register (PCON6) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16    :2;
} __pcon6_bits;


/* Port7 data/pullup register (PDAT7, PUR7) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8    :1;
  __REG8    :1;
} __port7_bits;


/* Port7 control register (PCON7) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16    :2;
  __REG16    :2;
} __pcon7_bits;


/* Port8 data/pullup register (PDAT8, PUR8) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8 P7 :1;
} __port8_bits;


/* Port8 control register (PCON8) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16 P7 :2;
} __pcon8_bits;


/* Port9 data/pullup register (PDAT9, PUR9) */
typedef struct {
  __REG8 P0 :1;
  __REG8 P1 :1;
  __REG8 P2 :1;
  __REG8 P3 :1;
  __REG8 P4 :1;
  __REG8 P5 :1;
  __REG8 P6 :1;
  __REG8 P7 :1;
} __port9_bits;


/* Port9 control register (PCON9) */
typedef struct {
  __REG16 P0 :2;
  __REG16 P1 :2;
  __REG16 P2 :2;
  __REG16 P3 :2;
  __REG16 P4 :2;
  __REG16 P5 :2;
  __REG16 P6 :2;
  __REG16 P7 :2;
} __pcon9_bits;


/* External interrupt control register (EXTINT) */
typedef struct {
  __REG32 EINT0 :3;
  __REG32       :1; 
  __REG32 EINT1 :3; /* EINT1 enable */
  __REG32       :1;
  __REG32 EINT2 :3; /* EINT2 enable */
  __REG32       :1;
  __REG32 EINT3 :3; /* EINT3 enable */
  __REG32       :1;
  __REG32 EINT4 :3; /* EINT4 enable */
  __REG32       :1;
  __REG32 EINT5 :3; /* EINT5 enable */
  __REG32       :1;
  __REG32 EINT6 :3; /* EINT6 enable */
  __REG32       :1;
  __REG32 EINT7 :3; /* EINT7 enable */
  __REG32       :1;  
} __extint_bits;


/* Timer control register A TCON 0,1,2 */
typedef struct {
  __REG8       :2; /* Reserved */
  __REG8 ICS   :1; /* Timer Input Clock Selection */
  __REG8 OMS   :3; /* Timer Operation Mode Selection */
  __REG8 CL    :1; /* Timer Counter Clear */
  __REG8 TEN   :1; /* Timer Enable */
}__tcona_bits;


/* Timer control register B TCON 3,4,5 */
typedef struct {
  __REG8       :1; /* Reserved */
  __REG8 IVT   :1; /* Phase Invert Selection */
  __REG8 ICS   :1; /* Timer Input Clock Selection */
  __REG8 OMS   :3; /* Timer Operation Mode Selection */
  __REG8 CL    :1; /* Timer Counter Clear */
  __REG8 TEN   :1; /* Timer Enable */
}__tconb_bits;


/* Uart Line Control Register (ULCON0, ULCON1) */
typedef struct {
  __REG8 WL  :2; /* Word Length */
  __REG8 SB  :1; /* Number of Stop Bit */
  __REG8 PMD :3; /* Parity mode */
  __REG8 IRM :1; /* Infra-Red Mode */
  __REG8     :1; /* Reserved */
} __ulcon_bits;


/* Uart control register (UCON0, UCON1) */
typedef struct {
  __REG8 RM   :2; /* Receive mode */
  __REG8 RSIE :1; /* Rx status interrupt enable */
  __REG8 TM   :2; /* Transmit mode */
  __REG8      :1; /* Reserved */
  __REG8 SBS  :1; /* Send Break signal */
  __REG8 LBM  :1; /* Loop Back Mode */
} __ucon_bits;


/* Uart status register (USTAT0, USTAT1) */
typedef struct {
  __REG8 OE   :1; /* Overrun Error */
  __REG8 PE   :1; /* Parity Error */
  __REG8 FE   :1; /* Frame Error */
  __REG8 BD   :1; /* Break Detect */
  __REG8      :1; /* Reserved */  
  __REG8 RDDR :1; /* Receive Buffer Data Ready */
  __REG8 TBE  :1; /* Transmit Buffer Register Empty */
  __REG8 TSE  :1; /* Transmit Shift Register Empty */  
} __ustat_bits;


/* Synchronous I/O Control Register (SIOCON0, SIOCON1) */
typedef struct {
  __REG8      :3; /* Reserved */
  __REG8 SB   :1; /* SIO Start */
  __REG8 CES  :1; /* Clock Edge Select */
  __REG8 TRS  :1; /* Transmit/Receive Selection */
  __REG8 DD   :1; /* Data Direction */  
  __REG8 CS   :1; /* SIO Clock Source Selection */
} __siocon_bits;


/* Interrupt mode/pending/mask register (INTMOD, INTPND, INTMSK) */
typedef struct {
  __REG32 EINT0    :1;
  __REG32 EINT1    :1;
  __REG32 EINT2    :1;
  __REG32 EINT3    :1;
  __REG32 INT_URX0 :1;
  __REG32 INT_UTX0 :1;
  __REG32 INT_UERR0:1;
  __REG32 INT_URX1 :1;
  __REG32 INT_UTX1 :1;
  __REG32 INT_UERR1:1;
  __REG32 INT_TOF0 :1;
  __REG32 INT_TMC0 :1;
  __REG32 INT_TOF1 :1;
  __REG32 INT_TMC1 :1;
  __REG32 INT_TOF2 :1;
  __REG32 INT_TMC2 :1;
  __REG32 INT_TOF3 :1;
  __REG32 INT_TMC3 :1;
  __REG32 INT_TOF4 :1;
  __REG32 INT_TMC4 :1;
  __REG32 INT_TOF5 :1;
  __REG32 INT_TMC5 :1;
  __REG32 INT_BT   :1;
  __REG32 INT_SIO0 :1;
  __REG32 INT_SIO1 :1;
  __REG32 EINT4    :1;
  __REG32 EINT5    :1;
  __REG32 INT_ADC  :1;
  __REG32 EINT6    :1;    
  __REG32 EINT7    :1;
  __REG32          :2; /* Reserved */
} __int_bits;


/* Interrupt Priority register (INTPRI0) */
typedef struct {
  __REG32 PRIORITY0  :5; /* Number of interrupt source */
  __REG32            :3;
  __REG32 PRIORITY1  :5;
  __REG32            :3;
  __REG32 PRIORITY2  :5;
  __REG32            :3;
  __REG32 PRIORITY3  :5;
  __REG32 en         :3; /* Disable/Enable hard-wired branch */
} __intpri0_bits;


/* Interrupt Priority register (INTPRI1) */
typedef struct {
  __REG32 PRIORITY4  :5;
  __REG32            :3;
  __REG32 PRIORITY5  :5;
  __REG32            :3;
  __REG32 PRIORITY6  :5;
  __REG32            :3;
  __REG32 PRIORITY7  :5;
  __REG32            :3;
} __intpri1_bits;


/* Interrupt Priority register (INTPRI2) */
typedef struct {
  __REG32 PRIORITY8  :5;
  __REG32            :3;
  __REG32 PRIORITY9  :5;
  __REG32            :3;
  __REG32 PRIORITY10 :5;
  __REG32            :3;
  __REG32 PRIORITY11 :5;
  __REG32            :3;
} __intpri2_bits;


/* Interrupt Priority register (INTPRI3) */
typedef struct {
  __REG32 PRIORITY12 :5;
  __REG32            :3;
  __REG32 PRIORITY13 :5;
  __REG32            :3;
  __REG32 PRIORITY14 :5;
  __REG32            :3;
  __REG32 PRIORITY15 :5;
  __REG32            :3;
} __intpri3_bits;


/* Interrupt Priority register (INTPRI4) */
typedef struct {
  __REG32 PRIORITY16 :5;
  __REG32            :3;
  __REG32 PRIORITY17 :5;
  __REG32            :3;
  __REG32 PRIORITY18 :5;
  __REG32            :3;
  __REG32 PRIORITY19 :5;
  __REG32            :3;
} __intpri4_bits;


/* Interrupt Priority register (INTPRI5) */
typedef struct {
  __REG32 PRIORITY20 :5;
  __REG32            :3;
  __REG32 PRIORITY21 :5;
  __REG32            :3;
  __REG32 PRIORITY22 :5;
  __REG32            :3;
  __REG32 PRIORITY23 :5;
  __REG32            :3;
} __intpri5_bits;


/* Interrupt Priority register (INTPRI6) */
typedef struct {
  __REG32 PRIORITY24 :5;
  __REG32            :3;
  __REG32 PRIORITY25 :5;
  __REG32            :3;
  __REG32 PRIORITY26 :5;
  __REG32            :3;
  __REG32 PRIORITY27 :5;
  __REG32            :3;
} __intpri6_bits;


/* Interrupt Priority register (INTPRI7) */
typedef struct {
  __REG32 PRIORITY28 :5;
  __REG32            :3;
  __REG32 PRIORITY29 :5;
  __REG32            :3;
  __REG32            :5;
  __REG32            :3;
  __REG32            :5;
  __REG32            :3;
} __intpri7_bits;


/* Interrupt Offset register (INTOFFSET) */
typedef struct {
  __REG8 DATA :7; /* Interrupt offset address */
  __REG8      :1; /* Reserved */
} __intoffset_bits;


/* ADC: Control register (ADCCON) */
typedef struct {
  __REG16 ADEN      :1; /* A/D Enable */
  __REG16 READ_START:1; /* A/D conversion start by read */
  __REG16 STBY      :1; /* Standby Mode */
  __REG16 ASEL      :3; /* Analog Input Select */
  __REG16 PRSCVL    :8; /* Value of prescaler */
  __REG16 PRSCEN    :1; /* Prescaler enable */
  __REG16 FLAG      :1; /* Flag bit */
} __adcon_bits;


/* ADC: Data register (ADCDAT) */
typedef struct {
  __REG16 DATA :10;
  __REG16      :6;
} __addata_bits;


/* BTWDT: Basic Timer Control register (BTCON) */
typedef struct {
  __REG16 WDTC :1; /* Watch-Dog Timer Clear */
  __REG16 BTC  :1; /* Basic Timer Clear */
  __REG16 CS   :2; /* Clock Source Select */
  __REG16      :4; /* Reserved */
  __REG16 WDTE :8; /* Watch-Dog Timer Enable */
} __btcon_bits;


/* System control register (SYSCON) */
typedef struct {
  __REG16 STOP   :1; /* STOP Control */
  __REG16 IDLE   :1; /* IDLE Ccontrol */
  __REG16        :1; /* Reserved */
  __REG16 CLKDIV :3; /* Clock Select */
  __REG16 CLKSRC :1; /* Clock Source Select */
  __REG16 PLLON  :1; /* PLL ON/OFF */
  __REG16 GIE    :1; /* Global Interrupt Enable */
  __REG16        :7; /* Reserved */
} __syscon_bits;


/* pll control register (PLLCON) */
typedef struct {
  __REG32 SDIV :2; /* Main divider control */
  __REG32      :2; /* Reserved */
  __REG32 PDIV :6; /* Pre divider control */
  __REG32      :2; /* Reserved */
  __REG32 MDIV :8; /* Post divider control */
  __REG32      :12; /* Reserved */
} __pllcon_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  CPU WRAPPER Special register
 **
 ***************************************************************************/
__IO_REG32_BIT(SYSCFG,0x01ff4000,__READ_WRITE,__syscfg_bits);

/***************************************************************************
 **
 **  4. Memory Controller special registers
 **
 ***************************************************************************/
__IO_REG32_BIT(MEMCON0,0x01ff5000,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(MEMCON1,0x01ff5004,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(MEMCON2,0x01ff5008,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(MEMCON3,0x01ff500c,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(MEMCON4,0x01ff5010,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(MEMCON5,0x01ff5014,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(MEMCON6,0x01ff5018,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(MEMCON7,0x01ff501c,__READ_WRITE,__memcon_bits);

/***************************************************************************
 **
 **  5. FLASH Memory special registers
 **
 ***************************************************************************/
__IO_REG8(FMKEY0,0x01ff4010,__WRITE);
__IO_REG8(FMKEY1,0x01ff4011,__WRITE);
__IO_REG8(FMKEY2,0x01ff4012,__WRITE);
__IO_REG8(FMKEY3,0x01ff4013,__WRITE);
__IO_REG16(FMADDR,0x01ff4014,__WRITE);
__IO_REG16(FMDATA,0x01ff4018,__WRITE);

__IO_REG8_BIT(FMUCON,0x01ff401f,__READ_WRITE,__fmucon_bits);
__IO_REG8_BIT(FMERR,0x01ff4023,__READ_WRITE,__fmerr_bits);
__IO_REG8_BIT(FMACON,0x01ff4027,__READ_WRITE,__fmacon_bits);

/***************************************************************************
 **
 **  6. PORT CONTROL registers
 **
 ***************************************************************************/
__IO_REG8_BIT(PDAT0,0x01ffd000,__READ_WRITE, __port0_bits);
__IO_REG8_BIT(PDAT1,0x01ffd001,__READ_WRITE, __port1_bits);
__IO_REG8_BIT(PDAT2,0x01ffd002,__READ_WRITE, __port2_bits);
__IO_REG8_BIT(PDAT3,0x01ffd003,__READ_WRITE, __port3_bits);
__IO_REG8_BIT(PDAT4,0x01ffd004,__READ_WRITE, __port4_bits);
__IO_REG8_BIT(PDAT5,0x01ffd005,__READ_WRITE, __port5_bits);
__IO_REG8_BIT(PDAT6,0x01ffd006,__READ_WRITE, __port6_bits);
__IO_REG8_BIT(PDAT7,0x01ffd007,__READ_WRITE, __port7_bits);
__IO_REG8_BIT(PDAT8,0x01ffd008,__READ_WRITE, __port8_bits);
__IO_REG8_BIT(PDAT9,0x01ffd009,__READ_WRITE, __port9_bits);

__IO_REG16_BIT(PCON0,0x01ffd010,__READ_WRITE,__pcon0_bits);
__IO_REG16_BIT(PCON1,0x01ffd012,__READ_WRITE,__pcon1_bits);
__IO_REG16_BIT(PCON2,0x01ffd014,__READ_WRITE,__pcon2_bits);
__IO_REG16_BIT(PCON3,0x01ffd016,__READ_WRITE,__pcon3_bits);
__IO_REG16_BIT(PCON4,0x01ffd018,__READ_WRITE,__pcon4_bits);
__IO_REG16_BIT(PCON5,0x01ffd01a,__READ_WRITE,__pcon5_bits);
__IO_REG16_BIT(PCON6,0x01ffd01c,__READ_WRITE,__pcon6_bits);
__IO_REG16_BIT(PCON7,0x01ffd01e,__READ_WRITE,__pcon7_bits);
__IO_REG16_BIT(PCON8,0x01ffd020,__READ_WRITE,__pcon8_bits);
__IO_REG16_BIT(PCON9,0x01ffd022,__READ_WRITE,__pcon9_bits);

__IO_REG8_BIT(PDR0,0x01ffd024,__READ_WRITE,__port0_bits);
__IO_REG8_BIT(PDR1,0x01ffd025,__READ_WRITE,__port1_bits);
__IO_REG8_BIT(PDR2,0x01ffd026,__READ_WRITE,__port2_bits);
__IO_REG8_BIT(PUR3,0x01ffd027,__READ_WRITE,__port3_bits);
__IO_REG8_BIT(PUR4,0x01ffd028,__READ_WRITE,__port4_bits);
__IO_REG8_BIT(PUR5,0x01ffd029,__READ_WRITE,__port5_bits);
__IO_REG8_BIT(PUR6,0x01ffd02a,__READ_WRITE,__port6_bits);
__IO_REG8_BIT(PUR7,0x01ffd02b,__READ_WRITE,__port7_bits);
__IO_REG8_BIT(PUR8,0x01ffd02c,__READ_WRITE,__port8_bits);
__IO_REG8_BIT(PUR9,0x01ffd02d,__READ_WRITE,__port9_bits);

__IO_REG32_BIT(EXTINT,0x01ffd030,__READ_WRITE,__extint_bits);


/***************************************************************************
 **
 **  7. TIMER CONTROL registers
 **
 ***************************************************************************/
__IO_REG16(TDAT0,0x01ffb000,__READ_WRITE);
__IO_REG16(TDAT1,0x01ffb010,__READ_WRITE);
__IO_REG16(TDAT2,0x01ffb020,__READ_WRITE);
__IO_REG16(TDAT3,0x01ffb030,__READ_WRITE);
__IO_REG16(TDAT4,0x01ffb040,__READ_WRITE);
__IO_REG16(TDAT5,0x01ffb050,__READ_WRITE);

__IO_REG16(TCNT0,0x01ffb006,__READ);
__IO_REG16(TCNT1,0x01ffb016,__READ);
__IO_REG16(TCNT2,0x01ffb026,__READ);
__IO_REG16(TCNT3,0x01ffb036,__READ);
__IO_REG16(TCNT4,0x01ffb046,__READ);
__IO_REG16(TCNT5,0x01ffb056,__READ);

__IO_REG8(TPRE0,0x01ffb002,__READ_WRITE);
__IO_REG8_BIT(TCON0,0x01ffb003,__READ_WRITE,__tcona_bits);
__IO_REG8(TPRE1,0x01ffb012,__READ_WRITE);
__IO_REG8_BIT(TCON1,0x01ffb013,__READ_WRITE,__tcona_bits);
__IO_REG8(TPRE2,0x01ffb022,__READ_WRITE);
__IO_REG8_BIT(TCON2,0x01ffb023,__READ_WRITE,__tcona_bits);
__IO_REG8(TPRE3,0x01ffb032,__READ_WRITE);
__IO_REG8_BIT(TCON3,0x01ffb033,__READ_WRITE,__tconb_bits);
__IO_REG8(TPRE4,0x01ffb042,__READ_WRITE);
__IO_REG8_BIT(TCON4,0x01ffb043,__READ_WRITE,__tconb_bits);
__IO_REG8(TPRE5,0x01ffb052,__READ_WRITE);
__IO_REG8_BIT(TCON5,0x01ffb053,__READ_WRITE,__tconb_bits);

/***************************************************************************
 **
 **  8. UART registers
 **
 ***************************************************************************/
__IO_REG8_BIT(ULCON0,0x01ff6003,__READ_WRITE,__ulcon_bits);
__IO_REG8_BIT(UCON0,0x01ff6007,__READ_WRITE,__ucon_bits);
__IO_REG8_BIT(USTAT0,0x01ff600b,__READ,__ustat_bits);
__IO_REG8(UTXH0,0x01ff600f,__WRITE);
__IO_REG8(URXH0,0x01ff6013,__WRITE);
__IO_REG16(UBRDIV0,0x01ff6016,__READ_WRITE);

__IO_REG8_BIT(ULCON1,0x01ff7003,__READ_WRITE,__ulcon_bits);
__IO_REG8_BIT(UCON1,0x01ff7007,__READ_WRITE,__ucon_bits);
__IO_REG8_BIT(USTAT1,0x01ff700b,__READ,__ustat_bits);
__IO_REG8(UTXH1,0x01ff700f,__WRITE);
__IO_REG8(URXH1,0x01ff7013,__WRITE);
__IO_REG16(UBRDIV1,0x01ff7016,__READ_WRITE);


/***************************************************************************
 **
 **  9. SIO registers
 **
 ***************************************************************************/
__IO_REG8(SBRDR0,0x01ff8001,__READ_WRITE);
__IO_REG8(SIODAT0,0x01ff8002,__READ_WRITE);
__IO_REG8_BIT(SIOCON0,0x01ff8003,__READ_WRITE,__siocon_bits);

__IO_REG8(SBRDR1,0x01ff9001,__READ_WRITE);
__IO_REG8(SIODAT1,0x01ff9002,__READ_WRITE);
__IO_REG8_BIT(SIOCON1,0x01ff9003,__READ_WRITE,__siocon_bits);


/***************************************************************************
 **
 **   10. INTERRUPT CONTROLLER registers
 **
 ***************************************************************************/
__IO_REG32_BIT(INTMOD,0x01ffe000,__READ_WRITE,__int_bits);
__IO_REG32_BIT(INTPND,0x01ffe004,__READ_WRITE,__int_bits);
__IO_REG32_BIT(INTMSK,0x01ffe008,__READ_WRITE,__int_bits);

__IO_REG32_BIT(INTPRI0,0x01ffe00c,__READ_WRITE,__intpri0_bits);
__IO_REG32_BIT(INTPRI1,0x01ffe010,__READ_WRITE,__intpri1_bits);
__IO_REG32_BIT(INTPRI2,0x01ffe014,__READ_WRITE,__intpri2_bits);
__IO_REG32_BIT(INTPRI3,0x01ffe018,__READ_WRITE,__intpri3_bits);
__IO_REG32_BIT(INTPRI4,0x01ffe01c,__READ_WRITE,__intpri4_bits);
__IO_REG32_BIT(INTPRI5,0x01ffe020,__READ_WRITE,__intpri5_bits);
__IO_REG32_BIT(INTPRI6,0x01ffe024,__READ_WRITE,__intpri6_bits);
__IO_REG32_BIT(INTPRI7,0x01ffe028,__READ_WRITE,__intpri7_bits);

__IO_REG8_BIT(INTOFFSET,0x01ffe030,__READ,__intoffset_bits);


/***************************************************************************
 **
 **  11. A/D CONVERTER SPECIAL registers
 **
 ***************************************************************************/
__IO_REG16_BIT(ADCCON,0x01ffa002,__READ_WRITE,__adcon_bits);
__IO_REG16_BIT(ADCDAT,0x01ffa006,__READ_WRITE,__addata_bits);


/***************************************************************************
 **
 **  12. BASIC TIMER & WATCH-DOG TIMER  SPECIAL registers
 **
 ***************************************************************************/
__IO_REG16_BIT(BTCON,0x01ffc002,__READ_WRITE,__btcon_bits);
__IO_REG8(BTCNT,0x01ffc007,__READ);



/***************************************************************************
 **
 **  13. CLOCK & POWER MANAGEMENT registers
 **
 ***************************************************************************/
__IO_REG16_BIT(SYSCON,0x01fff002,__READ_WRITE,__syscon_bits);
__IO_REG32_BIT(PLLCON,0x01fff004,__READ_WRITE,__pllcon_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3F445HX interrupt vector table
 **
 ***************************************************************************/
#define VECT_EINT0       0x00000020 /* External interrupt 0                  */
#define VECT_EINT1       0x00000024 /* External interrupt 1                  */
#define VECT_EINT2       0x00000028 /* External interrupt 2                  */
#define VECT_EINT3       0x0000002c /* External interrupt 3                  */
#define VECT_INT_URX0    0x00000030 /* UART receive interrupt for channel 0  */
#define VECT_INT_UTX0    0x00000034 /* UART transmit interrupt for channel 0 */
#define VECT_INT_UERR0   0x00000038 /* UART error interrupt for channel 0    */
#define VECT_INT_URX1    0x0000003c /* UART receive interrupt for channel 1  */
#define VECT_INT_UTX1    0x00000040 /* UART transmit interrupt for channel 1 */
#define VECT_INT_UERR1   0x00000044 /* UART error interrupt for channel 1    */
#define VECT_INT_TOF0    0x00000048 /* Timer 0 overflow interrupt            */
#define VECT_INT_TMC0    0x0000004c /* Timer 0 match/capture interrupt       */
#define VECT_INT_TOF1    0x00000050 /* Timer 1 overflow interrupt            */
#define VECT_INT_TMC1    0x00000054 /* Timer 1 match/capture interrupt       */
#define VECT_INT_TOF2    0x00000058 /* Timer 2 overflow interrupt            */
#define VECT_INT_TMC2    0x0000005c /* Timer 2 match/capture interrupt       */
#define VECT_INT_TOF3    0x00000060 /* Timer 3 overflow interrupt            */
#define VECT_INT_TMC3    0x00000064 /* Timer 3 match/capture interrupt       */
#define VECT_INT_TOF4    0x00000068 /* Timer 4 overflow interrupt            */
#define VECT_INT_TMC4    0x0000006c /* Timer 4 match/capture interrupt       */
#define VECT_INT_TOF5    0x00000070 /* Timer 5 overflow interrupt            */
#define VECT_INT_TMC5    0x00000074 /* Timer 5 match/capture interrupt       */
#define VECT_INT_BT      0x00000078 /* Basic Timer interrupt                 */
#define VECT_INT_SIO0    0x0000007c /* SIO0 interrupt                        */
#define VECT_INT_SIO1    0x00000080 /* SIO1 interrupt                        */
#define VECT_EINT4       0x00000084 /* External interrupt 4                  */
#define VECT_EINT5       0x00000088 /* External interrupt 5                  */
#define VECT_INT_ADC     0x0000008c /* ADC interrupt                         */
#define VECT_EINT6       0x00000090 /* External interrupt 6                  */
#define VECT_EINT7       0x00000094 /* External interrupt 7                  */


/***************************************************************************
 **
 **  S3F445HX interrupt source number
 **
 ***************************************************************************/
#define INO_EINT0      0x00    /* External interrupt 0                  */
#define INO_EINT1      0x01    /* External interrupt 1                  */
#define INO_EINT2      0x02    /* External interrupt 2                  */
#define INO_EINT3      0x03    /* External interrupt 3                  */
#define INO_INT_URX0   0x04    /* UART receive interrupt for channel 0  */
#define INO_INT_UTX0   0x05    /* UART transmit interrupt for channel 0 */
#define INO_INT_UERR0  0x06    /* UART error interrupt for channel 0    */
#define INO_INT_URX1   0x07    /* UART receive interrupt for channel 1  */
#define INO_INT_UTX1   0x08    /* UART transmit interrupt for channel 1 */
#define INO_INT_UERR1  0x09    /* UART error interrupt for channel 1    */
#define INO_INT_TOF0   0x0a    /* Timer 0 overflow interrupt            */
#define INO_INT_TMC0   0x0b    /* Timer 0 match/capture interrupt       */
#define INO_INT_TOF1   0x0c    /* Timer 1 overflow interrupt            */
#define INO_INT_TMC1   0x0d    /* Timer 1 match/capture interrupt       */
#define INO_INT_TOF2   0x0e    /* Timer 2 overflow interrupt            */
#define INO_INT_TMC2   0x0f    /* Timer 2 match/capture interrupt       */
#define INO_INT_TOF3   0x10    /* Timer 3 overflow interrupt            */
#define INO_INT_TMC3   0x11    /* Timer 3 match/capture interrupt       */
#define INO_INT_TOF4   0x12    /* Timer 4 overflow interrupt            */
#define INO_INT_TMC4   0x13    /* Timer 4 match/capture interrupt       */
#define INO_INT_TOF5   0x14    /* Timer 5 overflow interrupt            */
#define INO_INT_TMC5   0x15    /* Timer 5 match/capture interrupt       */
#define INO_INT_BT     0x16    /* Basic Timer interrupt                 */
#define INO_INT_SIO0   0x17    /* SIO0 interrupt                        */
#define INO_INT_SIO1   0x18    /* SIO1 interrupt                        */
#define INO_EINT4      0x19    /* External interrupt 4                  */
#define INO_EINT5      0x1a    /* External interrupt 5                  */
#define INO_INT_ADC    0x1b    /* ADC interrupt                         */
#define INO_EINT6      0x1c    /* External interrupt 6                  */
#define INO_EINT7      0x1d    /* External interrupt 7                  */

#endif    /* __S3F445HX_H */


