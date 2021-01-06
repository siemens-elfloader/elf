/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Sharp Semiconductors LH7A400
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2003
 **
 **    $Revision: 1.7.2.1 $
 **
 ***************************************************************************/

#ifndef __LH7A400_H
#define __LH7A400_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    LH7A400 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* SMC Bank Configuration Registers  */
typedef struct {
  __REG32 IDCY                : 4;
  __REG32                     : 1;
  __REG32 WST1                : 5;
  __REG32                     : 1;
  __REG32 WST2                : 5;
  __REG32                     : 10;
  __REG32 WP                  : 1;
  __REG32 PME                 : 1;
  __REG32 MW                  : 2;
  __REG32                     : 2;
} __SMC_BCR_bits;

/* SMC PC Card Attribute Space Registers  */
typedef struct {
  __REG32 PA                  : 8;
  __REG32 HT                  : 4;
  __REG32                     : 4;
  __REG32 AA                  : 8;
  __REG32                     : 7;
  __REG32 WA                  : 1;
} __SMC_PCxATTRIB_bits;

/* SMC PC Card Common Memory Space Registers  */
typedef struct {
  __REG32 PC                  : 8;
  __REG32 HT                  : 4;
  __REG32                     : 4;
  __REG32 AC                  : 8;
  __REG32                     : 7;
  __REG32 WC                  : 1;
} __SMC_PCxCOM_bits;

/* SMC PC Card I/O Space Registers  */
typedef struct {
  __REG32 PI                  : 8;
  __REG32 HT                  : 4;
  __REG32                     : 4;
  __REG32 AI                  : 8;
  __REG32                     : 7;
  __REG32 WI                  : 1;
} __SMC_PCxIO_bits;

/* SMC PCMCIA Control Register  */
typedef struct {
  __REG32 PC12EN              : 2;
  __REG32 PC1RST              : 1;
  __REG32 PC2RST              : 1;
  __REG32 WEN1                : 1;
  __REG32 WEN2                : 1;
  __REG32                     : 2;
  __REG32 MPREG               : 1;
  __REG32                     : 23;
} __SMC_PCMCIACON_bits;


/* SDRAMC Synchronous Domain Chip Select Configuration Registers  */
typedef struct {
  __REG32                     : 2;
  __REG32 EBW                 : 1;
  __REG32 BankCount           : 1;
  __REG32 SROM512             : 1;
  __REG32 SROMLL              : 1;
  __REG32 _2KPAGE             : 1;
  __REG32                     : 9;
  __REG32 CasLat              : 3;
  __REG32 WBL                 : 1;
  __REG32 RasToCas            : 2;
  __REG32                     : 2;
  __REG32 AutoPrecharge       : 1;
  __REG32                     : 7;
} __SDRAMC_SDCSC_bits;

/* SDRAMC Global Configuration Register  */
typedef struct {
  __REG32 Initialize          : 1;
  __REG32 MRS                 : 1;
  __REG32                     : 3;
  __REG32 SMEMBust            : 1;
  __REG32 LCR                 : 1;
  __REG32                     : 23;
  __REG32 CKSD                : 1;
  __REG32 CKE                 : 1;
} __SDRAMC_GBLCNFG_bits;

/* SDRAMC Refresh Timer Register  */
typedef struct {
  __REG32 REFCNT              : 16;
  __REG32                     : 16;
} __SDRAMC_RFSHTMR_bits;

/* SDRAMC Boot Status Register  */
typedef struct {
  __REG32 Width0              : 1;
  __REG32 Width1              : 1;
  __REG32 MEDCHG              : 1;
  __REG32                     : 29;
} __SDRAMC_BOOTSTAT_bits;

/* CSC Power Reset Register  */
typedef struct {
  __REG32 RTCDIV              : 6;
  __REG32 MCDR                : 1;
  __REG32 DCDET               : 1;
  __REG32 WUDR                : 1;
  __REG32 WUON                : 1;
  __REG32 NBFLG               : 1;
  __REG32 RSTFLG              : 1;
  __REG32 PFFLG               : 1;
  __REG32 CLDFLG              : 1;
  __REG32 LCKFLG              : 1;
  __REG32                     : 1;
  __REG32 CHIPID              : 8;
  __REG32 CHIPMAN             : 8;
} __CSC_PWRSR_bits;

/* CSC Power Control Register  */
typedef struct {
  __REG32 WDTSEL              : 1;
  __REG32 WAKEDIS             : 1;
  __REG32                     : 6;
  __REG32 PGMCLK              : 8;
  __REG32 DMAM2PCH0           : 1;
  __REG32 DMAM2PCH1           : 1;
  __REG32 DMAM2PCH2           : 1;
  __REG32 DMAM2PCH3           : 1;
  __REG32 DMAM2PCH4           : 1;
  __REG32 DMAM2PCH5           : 1;
  __REG32 DMAM2PCH6           : 1;
  __REG32 DMAM2PCH7           : 1;
  __REG32 DMAM2PCH8           : 1;
  __REG32 DMAM2PCH9           : 1;
  __REG32 DMAM2MCH0           : 1;
  __REG32 DMAM2MCH1           : 1;
  __REG32 USHEN               : 1;
  __REG32 UARTBAUD            : 1;
  __REG32                     : 2;
} __CSC_PWRCNT_bits;

/* CSC Clock Set Register  */
typedef struct {
  __REG32 HCLKDIV             : 2;
  __REG32 PREDIV              : 5;
  __REG32 MAINDIV1            : 4;
  __REG32 MAINDIV2            : 5;
  __REG32 PCLKDIV             : 2;
  __REG32 PS                  : 2;
  __REG32                     : 4;
  __REG32 SMCROM              : 1;
  __REG32                     : 6;
  __REG32 PLLType             : 1;
} __CSC_CLKSET_bits;

/* CSC USB Reset Register  */
typedef struct {
  __REG32 IORESETREG          : 1;
  __REG32 APBRESETREG         : 1;
  __REG32                     : 30;
} __CSC_USBRESET_bits;


/* Interrupt Controller Status Register  */
typedef struct {
  __REG32 GPIO0FIQ            : 1;
  __REG32 BLINT               : 1;
  __REG32 WDINTR              : 1;
  __REG32 MCINT               : 1;
  __REG32 ACIINTR             : 1;
  __REG32 GPIO1INTR           : 1;
  __REG32 GPIO2INTR           : 1;
  __REG32 GPIO3INTR           : 1;
  __REG32 TC1OI               : 1;
  __REG32 TC2OI               : 1;
  __REG32 RTCINTR             : 1;
  __REG32 TINTR               : 1;
  __REG32 UART1INTR           : 1;
  __REG32 UART2INTR           : 1;
  __REG32 LCDINTR             : 1;
  __REG32 SSPINTR             : 1;
  __REG32 UART3INTR           : 1;
  __REG32 SCIINTR             : 1;
  __REG32 AC97INTR            : 1;
  __REG32 MMCINTR             : 1;
  __REG32 USBINTR             : 1;
  __REG32 DMAINTR             : 1;
  __REG32 TC3OI               : 1;
  __REG32 GPIO4INTR           : 1;
  __REG32 GPIO5INTR           : 1;
  __REG32 GPIO6INTR           : 1;
  __REG32 GPIO7INTR           : 1;
  __REG32 BMIINTR             : 1;
  __REG32                     : 4;
} __IC_INTSR_bits;


/* DMA control register   */
typedef struct {
  __REG32 STALLIntEn          : 1;
  __REG32 NFBIntEn            : 1;
  __REG32                     : 1;
  __REG32 ChErrorIntEn        : 1;
  __REG32 ENABLE              : 1;
  __REG32 ABORT               : 1;
  __REG32 ICE                 : 1;
  __REG32                     : 25;
} __DMA_CONTROL_bits;

/* DMA interrupt register   */
typedef struct {
  __REG32 STALLInt            : 1;
  __REG32 NFBInt              : 1;
  __REG32                     : 1;
  __REG32 ChErrorInt          : 1;
  __REG32                     : 28;
} __DMA_INTERRUPT_bits;

/* DMA status register   */
typedef struct {
  __REG32 STALL               : 1;
  __REG32 NFB                 : 1;
  __REG32                     : 1;
  __REG32 ChError             : 1;
  __REG32 CurrentState        : 2;
  __REG32 NextBuffer          : 1;
  __REG32 BYTES               : 5;
  __REG32                     : 20;
} __DMA_STATUS_bits;

/* DMA Channel bytes remaining register */
typedef struct {
  __REG32 Remain              : 16;
  __REG32                     : 16;
} __DMA_REMAIN_bits;

/* DMA Maximum byte count register */
typedef struct {
  __REG32 MAXCNT              : 16;
  __REG32                     : 16;
} __DMA_MAXCNT_bits;

/* DMA Global interrupt register */
typedef struct {
  __REG32 USBTXINT            : 1;
  __REG32 USBRXINT            : 1;
  __REG32 MMCTXINT            : 1;
  __REG32 MMCRXINT            : 1;
  __REG32 AC97RX0INT          : 1;
  __REG32 AC97TX0INT          : 1;
  __REG32 AC97RX1INT          : 1;
  __REG32 AC97TX1INT          : 1;
  __REG32 AC97RX2INT          : 1;
  __REG32 AC97TX2INT          : 1;
  __REG32                     : 22;
} __DMA_GINT_bits;


/* LCD Timing 0 Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 PPL                 : 6;
  __REG32 HSW                 : 8;
  __REG32 HFP                 : 8;
  __REG32 HBP                 : 8;
} __LCD_TIMING0_bits;

/* LCD Timing 1 Register  */
typedef struct {
  __REG32 LPP                 : 10;
  __REG32 VSW                 : 6;
  __REG32 VFP                 : 8;
  __REG32 VBP                 : 8;
} __LCD_TIMING1_bits;

/* LCD Timing 2 Register  */
typedef struct {
  __REG32 PCD                 : 5;
  __REG32 CSEL                : 1;
  __REG32 ACB                 : 5;
  __REG32 IVS                 : 1;
  __REG32 IHS                 : 1;
  __REG32 IPC                 : 1;
  __REG32 IOE                 : 1;
  __REG32                     : 1;
  __REG32 CPL                 : 10;
  __REG32 BCD                 : 1;
  __REG32                     : 5;
} __LCD_TIMING2_bits;

/* LCD Timing 3 Register  */
typedef struct {
  __REG32 LED                 : 7;
  __REG32                     : 9;
  __REG32 LEE                 : 1;
  __REG32                     : 15;
} __LCD_TIMING3_bits;

/* LCD Upper Panel Base Address Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 UPBASE              : 30;
} __LCD_UPBASE_bits;

/* LCD Lower Panel Base Address Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 LPBASE              : 30;
} __LCD_LPBASE_bits;

/* LCD Interrupt Enable Register  */
typedef struct {
  __REG32 FUFUEN              : 1;
  __REG32 FUFLEN              : 1;
  __REG32 NBUEN               : 1;
  __REG32 VCOMEN              : 1;
  __REG32 BUSEREN             : 1;
  __REG32                     : 27;
} __LCD_INTREN_bits;

/* LCD Control Register  */
typedef struct {
  __REG32 LCDEN               : 1;
  __REG32 BPP                 : 3;
  __REG32 BW                  : 1;
  __REG32 TFT                 : 1;
  __REG32 MONO8               : 1;
  __REG32 DUAL                : 1;
  __REG32 BGR                 : 1;
  __REG32 BEBO                : 1;
  __REG32 BEPO                : 1;
  __REG32 PWR                 : 1;
  __REG32 VCI                 : 2;
  __REG32                     : 2;
  __REG32 WATERMARK           : 1;
  __REG32                     : 15;
} __LCD_CONTROL_bits;

/* LCD Status Register  */
typedef struct {
  __REG32 FUFU                : 1;
  __REG32 FUFL                : 1;
  __REG32 NBU                 : 1;
  __REG32 VCOM                : 1;
  __REG32 BUSER               : 1;
  __REG32                     : 27;
} __LCD_STATUS_bits;

/* LCD Interrupt Register  */
typedef struct {
  __REG32 FUFUINTR            : 1;
  __REG32 FUFLINTR            : 1;
  __REG32 NBUINTR             : 1;
  __REG32 VCOMINTR            : 1;
  __REG32 BUSERINTR           : 1;
  __REG32                     : 27;
} __LCD_INTERRUPT_bits;

/* LCD Overflow Register  */
typedef struct {
  __REG32                     : 12;
  __REG32 OVERFLOW            : 20;
} __LCD_OVERFLOW_bits;

/* LCD HRTFTC Setup Register  */
typedef struct {
  __REG32 CR                  : 2;
  __REG32                     : 2;
  __REG32 PPL                 : 9;
  __REG32 ALIEN               : 1;
  __REG32                     : 18;
} __LCD_HRSETUP_bits;

/* LCD HRTFTC Control Register  */
typedef struct {
  __REG32 LCDSPSEN            : 1;
  __REG32 LCDCLSEN            : 1;
  __REG32                     : 30;
} __LCD_HRCON_bits;

/* LCD HRTFTC Timing 1 Register  */
typedef struct {
  __REG32 LPDEL               : 4;
  __REG32 REVDEL              : 4;
  __REG32 PSCLS               : 4;
  __REG32                     : 20;
} __LCD_HRTIMING1_bits;

/* LCD HRTFTC Timing 2 Register  */
typedef struct {
  __REG32 PS2CLS2             : 9;
  __REG32 SPLDEL              : 7;
  __REG32                     : 16;
} __LCD_HRTIMING2_bits;


/* Timer Load Registers  */
typedef struct {
  __REG32 LOAD                : 16;
  __REG32                     : 16;
} __TIMER_LOAD_bits;

/* Timer Value Registers  */
typedef struct {
  __REG32 VALUE               : 16;
  __REG32                     : 16;
} __TIMER_VALUE_bits;

/* Timer Control 1 & 2 Registers  */
typedef struct {
  __REG32                     : 3;
  __REG32 CLKSEL              : 1;
  __REG32                     : 2;
  __REG32 MODE                : 1;
  __REG32 ENABLE              : 1;
  __REG32                     : 24;
} __TIMER_CONTROL12_bits;

/* Timer Control 3 Register  */
typedef struct {
  __REG32                     : 6;
  __REG32 MODE                : 1;
  __REG32 ENABLE              : 1;
  __REG32                     : 24;
} __TIMER_CONTROL3_bits;

/* Timer Buzzer Count Register  */
typedef struct {
  __REG32 BZTOG               : 1;
  __REG32 BZMOD               : 1;
  __REG32                     : 30;
} __TIMER_BZCON_bits;


/* WDT Control Register  */
typedef struct {
  __REG32 EN                  : 1;
  __REG32 IF                  : 2;
  __REG32 FRZ                 : 1;
  __REG32 TOC                 : 4;
  __REG32                     : 24;
} __WDT_CTL_bits;

/* WDT Counter Reset Register  */
typedef struct {
  __REG32 RST                 : 16;
  __REG32                     : 16;
} __WDT_RST_bits;

/* WDT Status Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 IF                  : 2;
  __REG32 RST                 : 1;
  __REG32 FIQ                 : 1;
  __REG32                     : 24;
} __WDT_STATUS_bits;

/* WDT Current Watchdog Count Registers  */
typedef struct {
  __REG32 COUNT               : 8;
  __REG32                     : 24;
} __WDT_COUNT_bits;


/* RTC Interrupt Status and Interrupt clear Register  */
typedef union {
  //RTCSTAT
  struct {
    __REG32 RTCINTR             : 1;
    __REG32                     : 31;
  };
  //RTCEOI
  struct {
    __REG32 RTCEOI              : 32;
  };
} __RTCSTATCEOI_bits;

/* RTC Control Register  */
typedef struct {
  __REG32 MIE                 : 1;
  __REG32                     : 31;
} __RTCCR_bits;

/* SSP Control 0 Register  */
typedef struct {
  __REG32 DSS                 : 4;
  __REG32 FRF                 : 2;
  __REG32                     : 1;
  __REG32 SSE                 : 1;
  __REG32 SCR                 : 8;
  __REG32                     : 16;
} __SSP_CR0_bits;

/* SSP Control 1 Register  */
typedef struct {
  __REG32 RXSIEN              : 1;
  __REG32 TXSIEN              : 1;
  __REG32 LBM                 : 1;
  __REG32 SPO                 : 1;
  __REG32 SPH                 : 1;
  __REG32 RXOIEN              : 1;
  __REG32 FEN                 : 1;
  __REG32 TXIIEN              : 1;
  __REG32                     : 24;
} __SSP_CR1_bits;

/* SSP Interrupt Identification Register  */
typedef union {
  //SSP_IIR
  struct {
    __REG32 RXSI                : 1;
    __REG32 TXSI                : 1;
    __REG32                     : 4;
    __REG32 RXOI                : 1;
    __REG32 TXII                : 1;
    __REG32                     : 24;
  };
  //SSP_ROEOI
  struct {
    __REG32 RXEOI               : 32;
  };
} __SSP_IIR_bits;

/* SSP Data Register  */
typedef struct {
  __REG32 DATA                : 16;
  __REG32                     : 16;
} __SSP_DR_bits;

/* SSP Clock Prescale Register  */
typedef struct {
  __REG32 DVSR                : 8;
  __REG32                     : 24;
} __SSP_CPR_bits;

/* SSP Status Register  */
typedef struct {
  __REG32                     : 1;
  __REG32 TNF                 : 1;
  __REG32 RNE                 : 1;
  __REG32 BSY                 : 1;
  __REG32 THE                 : 1;
  __REG32 RHF                 : 1;
  __REG32 ROR                 : 1;
  __REG32 TFE                 : 1;
  __REG32 RFF                 : 1;
  __REG32                     : 23;
} __SSP_SR_bits;

/* UART Data Register  */
typedef struct {
  __REG32 DATA                : 8;
  __REG32 FE                  : 1;
  __REG32 PE                  : 1;
  __REG32 OE                  : 1;
  __REG32 BE                  : 1;
  __REG32                     : 20;
} __UART_DATA_bits;

/* UART FIFO and Framing Control Register  */
typedef struct {
  __REG32 BRK                 : 1;
  __REG32 PEN                 : 1;
  __REG32 EPS                 : 1;
  __REG32 STP2                : 1;
  __REG32 FEN                 : 1;
  __REG32 WLEN                : 2;
  __REG32                     : 25;
} __UART_FCON_bits;

/* UART Baud Rate Control Register  */
typedef struct {
  __REG32 BAUDDIV             : 16;
  __REG32                     : 16;
} __UART_BRCON_bits;

/* UART Control Register  */
typedef struct {
  __REG32 UARTEN              : 1;
  __REG32 SIRD                : 1;
  __REG32 SIRLP               : 1;
  __REG32 RXP                 : 1;
  __REG32 TXP                 : 1;
  __REG32 MXP                 : 1;
  __REG32 LBE                 : 1;
  __REG32 SIRBD               : 1;
  __REG32                     : 24;
} __UART_CON_bits;

/* UART Status Register  */
typedef struct {
  __REG32 CTS                 : 1;
  __REG32 DSR                 : 1;
  __REG32 DCD                 : 1;
  __REG32 BUSY                : 1;
  __REG32 RXFE                : 1;
  __REG32 TXFF                : 1;
  __REG32 RXFF                : 1;
  __REG32 TXFE                : 1;
  __REG32                     : 24;
} __UART_STATUS_bits;

/* UART Raw Interrupt Register  */
typedef struct {
  __REG32 RI                  : 1;
  __REG32 TI                  : 1;
  __REG32 MI                  : 1;
  __REG32 RTI                 : 1;
  __REG32 FEI                 : 1;
  __REG32 PEI                 : 1;
  __REG32 BEI                 : 1;
  __REG32 OEI                 : 1;
  __REG32                     : 24;
} __UART_RAWISR_bits;

/* UART Interrupt Enable Register  */
typedef struct {
  __REG32 REN                 : 1;
  __REG32 TEN                 : 1;
  __REG32 MEN                 : 1;
  __REG32 RTEN                : 1;
  __REG32 FEEN                : 1;
  __REG32 PEEN                : 1;
  __REG32 BEEN                : 1;
  __REG32 OEEN                : 1;
  __REG32                     : 24;
} __UART_INTEN_bits;

/* UART Interrupt Status Register  */
typedef struct {
  __REG32 RIM                 : 1;
  __REG32 TIM                 : 1;
  __REG32 MIM                 : 1;
  __REG32 RTIM                : 1;
  __REG32 FEIM                : 1;
  __REG32 PEIM                : 1;
  __REG32 BEIM                : 1;
  __REG32 OEIM                : 1;
  __REG32                     : 24;
} __UART_ISR_bits;

/* Error Interrupt Clear Register (EIC) */
typedef struct {
  __REG32 FEIC                : 1;
  __REG32 PEIC                : 1;
  __REG32 BEIC                : 1;
  __REG32 OEIC                : 1;
  __REG32                     : 28;
} __UART_EIC_bits;

/* Read Error Status and Clear Register (RES) */
typedef struct {
  __REG32 FE                  : 1;
  __REG32 PE                  : 1;
  __REG32 OE                  : 1;
  __REG32 BE                  : 1;
  __REG32                     : 28;
} __UART_RES_bits;

/* DMA Control Register (DMACR) */
typedef struct {
  __REG32 RDE                 : 1;
  __REG32 TDE                 : 1;
  __REG32 DE                  : 1;
  __REG32                     : 29;
} __UART_DMACR_bits;


/* GPIO Data Registers  */
typedef struct {
  __REG32 Py0                 : 1;
  __REG32 Py1                 : 1;
  __REG32 Py2                 : 1;
  __REG32 Py3                 : 1;
  __REG32 Py4                 : 1;
  __REG32 Py5                 : 1;
  __REG32 Py6                 : 1;
  __REG32 Py7                 : 1;
  __REG32                     : 24;
} __GPIO_PyD_bits;

/* GPIO Pin Data Register E  */
typedef struct {
  __REG32 PE0                 : 1;
  __REG32 PE1                 : 1;
  __REG32 PE2                 : 1;
  __REG32 PE3                 : 1;
  __REG32                     : 28;
} __GPIO_PEPD_bits;

/* GPIO Data Direction Registers  */
typedef struct {
  __REG32 Py0DIR              : 1;
  __REG32 Py1DIR              : 1;
  __REG32 Py2DIR              : 1;
  __REG32 Py3DIR              : 1;
  __REG32 Py4DIR              : 1;
  __REG32 Py5DIR              : 1;
  __REG32 Py6DIR              : 1;
  __REG32 Py7DIR              : 1;
  __REG32                     : 24;
} __GPIO_PyDD_bits;

/* GPIO Data Direction Register E  */
typedef struct {
  __REG32 PE0DIR              : 1;
  __REG32 PE1DIR              : 1;
  __REG32 PE2DIR              : 1;
  __REG32 PE3DIR              : 1;
  __REG32                     : 28;
} __GPIO_PEDD_bits;

/* GPIO Keyboard Control Register  */
typedef struct {
  __REG32 CSTATE              : 4;
  __REG32                     : 28;
} __GPIO_KBDCTL_bits;

/* GPIO Pin Multiplexing Register  */
typedef struct {
  __REG32 PEOCON              : 1;
  __REG32 PDOCON              : 1;
  __REG32 CODECON             : 1;
  __REG32 UART3CON            : 1;
  __REG32 CLK1_2EN            : 1;
  __REG32 CLK0EN              : 1;
  __REG32                     : 26;
} __GPIO_PINMUX_bits;

/* GPIO Interrupt Type Register  */
typedef struct {
  __REG32 F0                  : 1;
  __REG32 F1                  : 1;
  __REG32 F2                  : 1;
  __REG32 F3                  : 1;
  __REG32 F4                  : 1;
  __REG32 F5                  : 1;
  __REG32 F6                  : 1;
  __REG32 F7                  : 1;
  __REG32                     : 24;
} __GPIO_INTTYPE_bits;


/* MMC STR_STP_CLK  */
typedef struct {
  __REG32 STOP_CLK            : 1;
  __REG32 START_CLK           : 1;
  __REG32                     : 30;
} __MMC_STR_STP_CLK_bits;

/* MMC Status  */
typedef struct {
  __REG32 TIME_OUT_READ       : 1;
  __REG32 TIME_OUT_RESPONSE   : 1;
  __REG32 CRC_WRITE_ERROR     : 1;
  __REG32 CRC_READ_ERROR      : 1;
  __REG32 SPI_READ_ERROR_TOKEN: 1;
  __REG32 RESPONSE_CRC_ERROR  : 1;
  __REG32 FIFO_EMPTY          : 1;
  __REG32 FIFO_FULL           : 1;
  __REG32 CLK_DIS             : 1;
  __REG32                     : 2;
  __REG32 DATA_TRAN_DONE      : 1;
  __REG32 PRG_DONE            : 1;
  __REG32 END_CMD_RESP        : 1;
  __REG32                     : 18;
} __MMC_STATUS_bits;

/* MMC CLK_RATE  */
typedef struct {
  __REG32 CLK_RATE            : 3;
  __REG32                     : 29;
} __MMC_CLK_RATE_bits;

/* MMC_PREDIV  */
typedef struct {
  __REG32 CLOCK_PREDIV        : 4;
  __REG32 MMC_EN              : 1;
  __REG32 APB_RD_EN           : 1;
  __REG32                     : 26;
} __MMC_CLOCK_PREDIV_bits;

/* MMC SPI_REG  */
typedef struct {
  __REG32 SPI_EN              : 1;
  __REG32 CRC_ON              : 1;
  __REG32 SPI_CS_EN           : 1;
  __REG32 SPI_CS_ADDR         : 3;
  __REG32                     : 26;
} __MMC_SPI_REG_bits;

/* MMC Command control register  */
typedef struct {
  __REG32 RESPONSE_FORMAT     : 2;
  __REG32 DATA_EN             : 1;
  __REG32 WRITE               : 1;
  __REG32 STREAM              : 1;
  __REG32 BUSY                : 1;
  __REG32 Initialize          : 1;
  __REG32                     : 1;
  __REG32 BIG_ENDIAN          : 1;
  __REG32                     : 23;
} __MMC_CMD_CONTROL_bits;

/* MMC RES_TO  */
typedef struct {
  __REG32 RES_TO              : 7;
  __REG32                     : 25;
} __MMC_RES_TO_bits;

/* MMC READ_TO  */
typedef struct {
  __REG32 READ_TO             : 16;
  __REG32                     : 16;
} __MMC_READ_TO_bits;

/* MMC BLK_LEN  */
typedef struct {
  __REG32 BLOCK_LEN           : 10;
  __REG32                     : 22;
} __MMC_BLK_LEN_bits;

/* MMC BLOCK COUNT  */
typedef struct {
  __REG32 BLOCKS              : 16;
  __REG32                     : 16;
} __MMC_NOB_bits;

/* MMC INT_STATUS  */
typedef struct {
  __REG32 DATA_TRAN_DONE      : 1;
  __REG32 PRG_DONE            : 1;
  __REG32 END_CMD             : 1;
  __REG32                     : 1;
  __REG32 CLK_DIS             : 1;
  __REG32                     : 27;
} __MMC_INT_STATUS_bits;

/* MMC INT_CLEAR  */
typedef struct {
  __REG32 DATA_TRAN_DONE      : 1;
  __REG32 PRG_DONE            : 1;
  __REG32 END_CMD             : 1;
  __REG32                     : 29;
} __MMC_INT_CLEAR_bits;

/* MMC INT_EN  */
typedef struct {
  __REG32 DATA_TRAN_DONE      : 1;
  __REG32 PRG_DONE            : 1;
  __REG32 END_CMD             : 1;
  __REG32 BUF_READY           : 1;
  __REG32 CLK_DIS             : 1;
  __REG32                     : 27;
} __MMC_INT_EN_bits;

/* MMC CMD_NUM  */
typedef struct {
  __REG32 CMD_NUM             : 6;
  __REG32                     : 25;
  __REG32                     : 1;
} __MMC_CMD_bits;

/* MMC RES_FIFO  */
typedef struct {
  __REG32 RES_FIFO            : 16;
  __REG32                     : 16;
} __MMC_RES_FIFO_bits;

/* MMC DATA_FIFO  */
typedef struct {
  __REG32 DATA_FIFO           : 16;
  __REG32                     : 16;
} __MMC_DATA_FIFO_bits;

/* MMC BUF_PART_FULL  */
typedef struct {
  __REG32 BUF_PART_FULL       : 1;
  __REG32                     : 31;
} __MMC_BUF_PART_FULL_bits;


/* USB Function Address Register  */
typedef struct {
  __REG32 FUNCTION_ADDR       : 7;
  __REG32 ADDR_UPDATE         : 1;
  __REG32                     : 24;
} __USB_FAR_bits;

/* USB Power Management Register  */
typedef struct {
  __REG32 ENABLE_SUSPEND      : 1;
  __REG32 SUSPEND_MODE        : 1;
  __REG32 UC_RESUME           : 1;
  __REG32 USB_RESET           : 1;
  __REG32 USB_ENABLE          : 1;
  __REG32                     : 1;
  __REG32                     : 26;
} __USB_PMR_bits;

/* USB IN Interrupt Register  */
typedef struct {
  __REG32 EP0                 : 1;
  __REG32 EP1IN               : 1;
  __REG32                     : 1;
  __REG32 EP3IN               : 1;
  __REG32                     : 28;
} __USB_IIR_bits;

/* USB OUT Interrupt Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 EP2OUT              : 1;
  __REG32                     : 29;
} __USB_OIR_bits;

/* USB Interrupt Register  */
typedef struct {
  __REG32 SUSINT              : 1;
  __REG32 RESINT              : 1;
  __REG32 URINT               : 1;
  __REG32                     : 29;
} __USB_UIR_bits;

/* USB IN Interrupt Enable Register  */
typedef struct {
  __REG32 EP0EN               : 1;
  __REG32 EP1INEN             : 1;
  __REG32                     : 1;
  __REG32 EP3INEN             : 1;
  __REG32                     : 28;
} __USB_IIE_bits;

/* USB OUT Interrupt Enable Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 EP2OUTEN            : 1;
  __REG32                     : 29;
} __USB_OIE_bits;

/* USB Interrupt Enable Register  */
typedef struct {
  __REG32 SUSINTEN            : 1;
  __REG32                     : 1;
  __REG32 URINTEN             : 1;
  __REG32                     : 29;
} __USB_UIE_bits;

/* USB Frame Number Register 1  */
typedef struct {
  __REG32 FRAME1              : 8;
  __REG32                     : 24;
} __USB_FRAME1_bits;

/* USB Frame Number Register 2  */
typedef struct {
  __REG32 FRAME2              : 3;
  __REG32                     : 29;
} __USB_FRAME2_bits;

/* USB Index Register  */
typedef struct {
  __REG32 INDEX               : 2;
  __REG32                     : 30;
} __USB_INDEX_bits;

/* USB Maximum Packet Size Register  */
typedef struct {
  __REG32 MAXP                : 4;
  __REG32                     : 28;
} __USB_MAXP_bits;

/* USB IN Control and Status Register,
   USB Endpoint 0 Control and Status Register */
typedef union {
  //USB_INCSR1
  struct {
    __REG32 IN_PKT_RDY_INCSR1   : 1;
    __REG32 FIFO_NE             : 1;
    __REG32                     : 1;
    __REG32 FIFO_FLUSH          : 1;
    __REG32 SEND_STALL_INCSR1   : 1;
    __REG32 SENT_STALL_INCSR1   : 1;
    __REG32 CLRTOG              : 1;
    __REG32                     : 25;
  };
  //USB_EP0CSR
  struct {
  __REG32 OUT_PKT_RDY         : 1;
  __REG32 IN_PKT_RDY_EP0CSR   : 1;
  __REG32 SENT_STALL_EP0CSR   : 1;
  __REG32 DATA_END            : 1;
  __REG32 SETUP_END           : 1;
  __REG32 SEND_STALL_EP0CSR   : 1;
  __REG32 CLR_OUT             : 1;
  __REG32 CLR_SETUP_END       : 1;
  __REG32                     : 24;
  };
} __USB_INCSR1_EP0CSR_bits;

/* USB IN Control and Status Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 USB_DMA_EN          : 1;
  __REG32                     : 2;
  __REG32 AUTO_SET            : 1;
  __REG32                     : 24;
} __USB_INCSR2_bits;

/* USB OUT Control and Status Register 1  */
typedef struct {
  __REG32 OUT_PKT_RDY         : 1;
  __REG32 FIFO_FULL           : 1;
  __REG32                     : 2;
  __REG32 FIFO_FLUSH          : 1;
  __REG32 SEND_STALL          : 1;
  __REG32 SENT_STALL          : 1;
  __REG32 CL_DATATOG          : 1;
  __REG32                     : 24;
} __USB_OUTCSR1_bits;

/* USB OUT Control and Status Register 2  */
typedef struct {
  __REG32                     : 4;
  __REG32 USB_DMA_EN          : 1;
  __REG32                     : 2;
  __REG32 AUTO_CLR            : 1;
  __REG32                     : 24;
} __USB_OUTCSR2_bits;

/* USB Out FIFO Write Count Register  */
typedef struct {
  __REG32 COUNT               : 8;
  __REG32                     : 24;
} __USB_COUNT1_bits;


/* AC97 Data Registers  */
typedef union {
  //AC97_DRx
  struct {  /* Standard mode */
    __REG32 DATA                : 20;
    __REG32                     : 12;
  };
  //AC97_DRx
  struct { /* Compact mode */
    __REG32 ODATA               : 16;
    __REG32 EDATA               : 16;
  };
} __AC97_DRx_bits;

/* AC97 Receive Control Registers  */
typedef struct {
  __REG32 REN                 : 1;
  __REG32 RX1                 : 1;
  __REG32 RX2                 : 1;
  __REG32 RX3                 : 1;
  __REG32 RX4                 : 1;
  __REG32 RX5                 : 1;
  __REG32 RX6                 : 1;
  __REG32 RX7                 : 1;
  __REG32 RX8                 : 1;
  __REG32 RX9                 : 1;
  __REG32 RX10                : 1;
  __REG32 RX11                : 1;
  __REG32 RX12                : 1;
  __REG32 RSIZE               : 2;
  __REG32 CM                  : 1;
  __REG32 FDIS                : 1;
  __REG32 TOC                 : 12;
  __REG32                     : 3;
} __AC97_RXCRx_bits;

/* AC97 Transmit Control Registers  */
typedef struct {
  __REG32 TEN                 : 1;
  __REG32 TX1                 : 1;
  __REG32 TX2                 : 1;
  __REG32 TX3                 : 1;
  __REG32 TX4                 : 1;
  __REG32 TX5                 : 1;
  __REG32 TX6                 : 1;
  __REG32 TX7                 : 1;
  __REG32 TX8                 : 1;
  __REG32 TX9                 : 1;
  __REG32 TX10                : 1;
  __REG32 TX11                : 1;
  __REG32 TX12                : 1;
  __REG32 TSIZE               : 2;
  __REG32 CM                  : 1;
  __REG32 FDIS                : 1;
  __REG32                     : 15;
} __AC97_TXCRx_bits;

/* AC97 Controller Status Registers  */
typedef struct {
  __REG32 RXFE                : 1;
  __REG32 TXFE                : 1;
  __REG32 RXFF                : 1;
  __REG32 TXFF                : 1;
  __REG32 TXBUSY              : 1;
  __REG32 RXOE                : 1;
  __REG32 TXUE                : 1;
  __REG32                     : 25;
} __AC97_SRx_bits;

/* AC97 Raw Interrupt Status Registers  */
typedef struct {
  __REG32 TCIS                : 1;
  __REG32 RTIS                : 1;
  __REG32 TIS                 : 1;
  __REG32 RIS                 : 1;
  __REG32                     : 28;
} __AC97_RISRx_bits;

/* AC97 Interrupt Status Registers  */
typedef struct {
  __REG32 TCIS                : 1;
  __REG32 RTIS                : 1;
  __REG32 TIS                 : 1;
  __REG32 RIS                 : 1;
  __REG32                     : 28;
} __AC97_ISRx_bits;

/* AC97 Interrupt Enable Registers  */
typedef struct {
  __REG32 TCIE                : 1;
  __REG32 RTIE                : 1;
  __REG32 TIE                 : 1;
  __REG32 RIE                 : 1;
  __REG32                     : 28;
} __AC97_IEx_bits;

/* AC97 Slot 1 Data Register  */
typedef struct {
  __REG32 DATA                : 7;
  __REG32                     : 25;
} __AC97_S1DATA_bits;

/* AC97 Slot 2 Data Register  */
typedef struct {
  __REG32 DATA                : 16;
  __REG32                     : 16;
} __AC97_S2DATA_bits;

/* AC97 Slot 12 Data Register  */
typedef struct {
  __REG32 DATA                : 20;
  __REG32                     : 12;
} __AC97_S12DATA_bits;

/* AC97 Raw Global Interrupt Status Register  */
typedef struct {
  __REG32 Slot1TXCMP          : 1;
  __REG32 Slot2INTRX          : 1;
  __REG32 GPIOTXCMP           : 1;
  __REG32 GPIOINTRX           : 1;
  __REG32 RWIS                : 1;
  __REG32 CODECREADY          : 1;
  __REG32                     : 26;
} __AC97_RGIS_bits;

/* AC97 Global Interrupt Status Register  */
typedef struct {
  __REG32 SLOT1TXCMP          : 1;
  __REG32 SLOT2INTRX          : 1;
  __REG32 GPIOTXCMP           : 1;
  __REG32 GPIOINTRX           : 1;
  __REG32 WIS                 : 1;
  __REG32 CODECREADY          : 1;
  __REG32 SLOT2TXCMP          : 1;
  __REG32                     : 25;
} __AC97_GIS_bits;

/* Global Interrupt Enable Register  */
typedef struct {
  __REG32 SLOT1TXCMPEN        : 1;
  __REG32 SLOT2INTRXEN        : 1;
  __REG32 GPIOTXCMPEN         : 1;
  __REG32 GPIOINTRXEN         : 1;
  __REG32 WIEN                : 1;
  __REG32 CODECREADYEN        : 1;
  __REG32                     : 26;
} __AC97_GIEN_bits;

/* AC97 Global End-of-Interrupt Register  */
typedef struct {
  __REG32 WISC                : 1;
  __REG32 CODECREADY          : 1;
  __REG32                     : 30;
} __AC97_GEOI_bits;

/* AC97 Global Control Register  */
typedef struct {
  __REG32 IFE                 : 1;
  __REG32 LOOP                : 1;
  __REG32 OCR                 : 1;
  __REG32                     : 29;
} __AC97_GCR_bits;

/* AC97 Reset Register  */
typedef struct {
  __REG32 TIMEDRESET          : 1;
  __REG32 FORCEDRESET         : 1;
  __REG32 EFORCER             : 1;
  __REG32                     : 29;
} __AC97_RESET_bits;

/* AC97 SYNC Port Register  */
typedef struct {
  __REG32 TIMEDSYNC           : 1;
  __REG32 FORCEDSYNC          : 1;
  __REG32 EFORCES             : 1;
  __REG32                     : 29;
} __AC97_SYNC_bits;

/* AC97 Global Control Interrupt Status Register  */
typedef struct {
  __REG32 ISR1                : 4;
  __REG32 ISR2                : 4;
  __REG32 ISR3                : 4;
  __REG32 ISR4                : 4;
  __REG32 GIS                 : 6;
  __REG32                     : 10;
} __AC97_GCIS_bits;


/* ACI Data Register  */
typedef struct {
  __REG32 DATA                : 8;
  __REG32                     : 24;
} __ACI_DATA_bits;

/* ACI Control Register  */
typedef struct {
  __REG32 TXEN                : 1;
  __REG32 RXEN                : 1;
  __REG32 RXIE                : 1;
  __REG32 TXIE                : 1;
  __REG32 LB                  : 1;
  __REG32 TXEPCLKEN           : 1;
  __REG32                     : 26;
} __ACI_CTL_bits;

/* ACI Status Register  */
typedef struct {
  __REG32 RXFE                : 1;
  __REG32 TXFF                : 1;
  __REG32 RXFF                : 1;
  __REG32 TXFE                : 1;
  __REG32 RXI                 : 1;
  __REG32 TXI                 : 1;
  __REG32 RXBUSY              : 1;
  __REG32 TXBUSY              : 1;
  __REG32                     : 24;
} __ACI_STATUS_bits;

/* ACI Clock Divisor Register  */
typedef struct {
  __REG32 CLKDIV              : 10;
  __REG32                     : 22;
} __ACI_CLKDIV_bits;


/* BMI Single Wire Interface Control Register  */
typedef struct {
  __REG32 SWIEN               : 1;
  __REG32 GBS                 : 1;
  __REG32 DINV                : 1;
  __REG32 WDCS                : 6;
  __REG32 RDSS                : 6;
  __REG32 T_RST               : 1;
  __REG32 SP_INVERT           : 1;
  __REG32                     : 15;
} __BMI_SWICR_bits;

/* BMI Single Wire Interface Status Register  */
typedef struct {
  __REG32 TXB                 : 1;
  __REG32 SBS                 : 1;
  __REG32 DBS                 : 1;
  __REG32 PBS                 : 1;
  __REG32 TXF                 : 1;
  __REG32 RXF                 : 1;
  __REG32 BKS                 : 1;
  __REG32 BRS                 : 1;
  __REG32 BRF                 : 1;
  __REG32 RXB                 : 1;
  __REG32 TEF                 : 1;
  __REG32 COL                 : 1;
  __REG32                     : 20;
} __BMI_SWISR_bits;

/* BMI Single Wire Interface Raw Interrupt Status and Clear Register  */
typedef struct {
  __REG32 WTI                 : 1;
  __REG32 WRI                 : 1;
  __REG32 BRI                 : 1;
  __REG32                     : 29;
} __BMI_SWIRSREOI_bits;

/* BMI Single Wire Interface Interrupt Status Register  */
typedef struct {
  __REG32 WTI                 : 1;
  __REG32 WRI                 : 1;
  __REG32 BRI                 : 1;
  __REG32                     : 29;
} __BMI_SWIISR_bits;

/* BMI Single Wire Interface Timing Register  */
typedef struct {
  __REG32 BTG                 : 16;
  __REG32                     : 16;
} __BMI_SWITR_bits;

/* BMI Single Wire Interface Break Register  */
typedef struct {
  __REG32 SWIBR               : 12;
  __REG32 SWIB                : 12;
  __REG32                     : 8;
} __BMI_SWIBR_bits;

/* BMI Smart Battery Control Register  */
typedef struct {
  __REG32 SBI_EN              : 1;
  __REG32 FFLUSH              : 1;
  __REG32 DIVFACT             : 8;
  __REG32 TX_FDIS             : 1;
  __REG32 RX_FDIS             : 1;
  __REG32 TOC                 : 12;
  __REG32 BRF                 : 1;
  __REG32 PEF                 : 1;
  __REG32                     : 6;
} __BMI_SBICR_bits;

/* BMI Smart Battery Count Register  */
typedef struct {
  __REG32 PRE                 : 5;
  __REG32 REP                 : 5;
  __REG32 READ                : 5;
  __REG32                     : 17;
} __BMI_SBICOUNT_bits;

/* BMI Smart Battery Status Register  */
typedef struct {
  __REG32 RXFE                : 1;
  __REG32 TXFE                : 1;
  __REG32 RXFF                : 1;
  __REG32 TXFF                : 1;
  __REG32 TXBUSY              : 1;
  __REG32 MASTER              : 1;
  __REG32 SLAVE               : 1;
  __REG32 RnW                 : 1;
  __REG32 ACKFAIL             : 1;
  __REG32 RXOE                : 1;
  __REG32 TXUE                : 1;
  __REG32 CLT                 : 1;
  __REG32 SBH                 : 1;
  __REG32                     : 19;
} __BMI_SBISR_bits;

/* BMI Smart Battery Raw Interrupt Status Register and End-of-Interrupt Register  */
typedef struct {
  __REG32 MTCI                : 1;
  __REG32 RTI                 : 1;
  __REG32 TXI                 : 1;
  __REG32 RXI                 : 1;
  __REG32 AFI                 : 1;
  __REG32 ALI                 : 1;
  __REG32 STCI                : 1;
  __REG32 CLTI                : 1;
  __REG32                     : 24;
} __BMI_SBIRISREOI_bits;

/* BMI Smart Battery Interrupt Status Register  */
typedef struct {
  __REG32 MTCI                : 1;
  __REG32 RTI                 : 1;
  __REG32 TXI                 : 1;
  __REG32 RXI                 : 1;
  __REG32 AFI                 : 1;
  __REG32 ALI                 : 1;
  __REG32 STCI                : 1;
  __REG32 CLTI                : 1;
  __REG32                     : 24;
} __BMI_SBIISR_bits;

/* BMI Smart Battery Interrupt Enable Register  */
typedef struct {
  __REG32 TCIE                : 1;
  __REG32 RTIE                : 1;
  __REG32 TIE                 : 1;
  __REG32 RIE                 : 1;
  __REG32 AFIE                : 1;
  __REG32 ALIE                : 1;
  __REG32 STCIE               : 1;
  __REG32 CLTIE               : 1;
  __REG32                     : 24;
} __BMI_SBIIER_bits;


/* DC-DC Duty Cycle Configuration Register  */
typedef struct {
  __REG32 PWM0DTYHIGH         : 4;
  __REG32 PWM0DTYLOW          : 4;
  __REG32 PWM1DTYHIGH         : 4;
  __REG32 PWM1DTYLOW          : 4;
  __REG32                     : 16;
} __DCDCCON_bits;

/* DC-DC Frequency Configuration Register  */
typedef struct {
  __REG32 PWM0PREHIGH         : 3;
  __REG32                     : 1;
  __REG32 PWM0PRELOW          : 3;
  __REG32                     : 1;
  __REG32 PWM1PREHIGH         : 3;
  __REG32                     : 1;
  __REG32 PWM1PRELOW          : 3;
  __REG32                     : 17;
} __DCDCFREQ_bits;


/* SCI Data Register  */
typedef struct {
  __REG32 DATA                : 8;
  __REG32 PARITY              : 1;
  __REG32                     : 23;
} __SCI_DATA_bits;

/* SCI Control 0 Register  */
typedef struct {
  __REG32 SENSE               : 1;
  __REG32 ORDER               : 1;
  __REG32 TXPARITY            : 1;
  __REG32 TXNAK               : 1;
  __REG32 RXPARITY            : 1;
  __REG32 RXNAK               : 1;
  __REG32                     : 26;
} __SCI_CR0_bits;

/* SCI Control 1 Register  */
typedef struct {
  __REG32 ATRDEN              : 1;
  __REG32 BLKEN               : 1;
  __REG32 MODE                : 1;
  __REG32 CLKZ1               : 1;
  __REG32 BGTEN               : 1;
  __REG32 EXDBNCE             : 1;
  __REG32                     : 26;
} __SCI_CR1_bits;

/* SCI Control 2 Register  */
typedef struct {
  __REG32 STARTUP             : 1;
  __REG32 FINISH              : 1;
  __REG32 WRESET              : 1;
  __REG32                     : 29;
} __SCI_CR2_bits;

/* SCI Interrupt Enable Register  */
typedef struct {
  __REG32 CARDINIE            : 1;
  __REG32 CARDOUTIE           : 1;
  __REG32 CARDUPIE            : 1;
  __REG32 CARDDNIE            : 1;
  __REG32 TXERRIE             : 1;
  __REG32 ATRSTOUTIE          : 1;
  __REG32 ATRDTOUTIE          : 1;
  __REG32 BLKTOUTIE           : 1;
  __REG32 CHTOUTIE            : 1;
  __REG32 RTOUTIE             : 1;
  __REG32 RXWMARKIE           : 1;
  __REG32 TXWMARKIE           : 1;
  __REG32                     : 20;
} __SCI_IER_bits;

/* SCI Retry Limit Register  */
typedef struct {
  __REG32 TXRETRY             : 3;
  __REG32 RXRETRY             : 3;
  __REG32                     : 26;
} __SCI_RETRY_bits;

/* SCI Watermark Register  */
typedef struct {
  __REG32 TXWMARK             : 4;
  __REG32 RXWMARK             : 4;
  __REG32                     : 24;
} __SCI_WMARK_bits;

/* SCI Transmit FIFO Count and Clear Register  */
typedef struct {
  __REG32 TXCOUNT             : 5;
  __REG32                     : 27;
} __SCI_TXCOUNT_bits;

/* SCI Receive FIFO Count and Clear Register  */
typedef struct {
  __REG32 RXCOUNT             : 5;
  __REG32                     : 27;
} __SCI_RXCOUNT_bits;

/* SCI FIFO Status Register  */
typedef struct {
  __REG32 TXFF                : 1;
  __REG32 TXFE                : 1;
  __REG32 RXFF                : 1;
  __REG32 RXFE                : 1;
  __REG32                     : 28;
} __SCI_FR_bits;

/* SCI Receive Read Time-Out Register  */
typedef struct {
  __REG32 RXTIME              : 16;
  __REG32                     : 16;
} __SCI_RXTIME_bits;

/* SCI Direct Status Register  */
typedef struct {
  __REG32 POWER               : 1;
  __REG32 CRESET              : 1;
  __REG32 CLKEN               : 1;
  __REG32 DATAEN              : 1;
  __REG32 nCLKOUTEN           : 1;
  __REG32 nCLKEN              : 1;
  __REG32 CLKOUT              : 1;
  __REG32 nDATAOUTEN          : 1;
  __REG32 nDATAEN             : 1;
  __REG32 CARDPRESENT         : 1;
  __REG32                     : 22;
} __SCI_DSTAT_bits;

/* SCI Debounce Timer Register  */
typedef struct {
  __REG32 STABLE              : 8;
  __REG32                     : 24;
} __SCI_STABLE_bits;

/* SCI Activation Time Register  */
typedef struct {
  __REG32 ATIME               : 16;
  __REG32                     : 16;
} __SCI_ATIME_bits;

/* SCI Deactivation Event Time Register  */
typedef struct {
  __REG32 DTIME               : 16;
  __REG32                     : 16;
} __SCI_DTIME_bits;

/* SCI ATR Reception Start Time Register  */
typedef struct {
  __REG32 ATRSTIME            : 16;
  __REG32                     : 16;
} __SCI_ATRSTIME_bits;

/* SCI ATR Duration Register  */
typedef struct {
  __REG32 ATRDTIME            : 16;
  __REG32                     : 16;
} __SCI_ATRDTIME_bits;

/* SCI Receive Block Time-Out Register  */
typedef struct {
  __REG32 BLKTIME             : 16;
  __REG32                     : 16;
} __SCI_BLKTIME_bits;

/* SCI Character-to-Character Time-Out Register  */
typedef struct {
  __REG32 CHTIME              : 16;
  __REG32                     : 16;
} __SCI_CHTIME_bits;

/* SCI Clock Frequency Register  */
typedef struct {
  __REG32 CLKDIV              : 8;
  __REG32                     : 24;
} __SCI_CLKDIV_bits;

/* SCI Baud Rate Register  */
typedef struct {
  __REG32 BAUD                : 16;
  __REG32                     : 16;
} __SCI_BAUD_bits;

/* SCI Baud Cycles Register  */
typedef struct {
  __REG32 VALUE               : 8;
  __REG32                     : 24;
} __SCI_CYCLES_bits;

/* SCI Character-to-Character Guard Time Register  */
typedef struct {
  __REG32 CHGUARD             : 8;
  __REG32                     : 24;
} __SCI_CHGUARD_bits;

/* SCI Block Guard Time Register  */
typedef struct {
  __REG32 BLKGUARD            : 8;
  __REG32                     : 24;
} __SCI_BLKGUARD_bits;

/* SCI Asynchronous and Synchronous Multiplexing Register  */
typedef struct {
  __REG32 SELDATA             : 1;
  __REG32 SELCLK              : 1;
  __REG32                     : 30;
} __SCI_SYNCCR_bits;

/* SCI Synchronous Data Register  */
typedef struct {
  __REG32 WDATA               : 1;
  __REG32 WCLK                : 1;
  __REG32 WDATAEN             : 1;
  __REG32 WCLKEN              : 1;
  __REG32                     : 28;
} __SCI_SYNCDATA_bits;

/* SCI Raw I/O and Clock Status Register  */
typedef struct {
  __REG32 RDATA               : 1;
  __REG32 RCLK                : 1;
  __REG32                     : 30;
} __SCI_RAWSTAT_bits;

/* SCI Interrupt Identification and Clear Register  */
typedef struct {
  __REG32 CARDININTR          : 1;
  __REG32 CARDOUTINTR         : 1;
  __REG32 CARDUPINTR          : 1;
  __REG32 CARDDNINTR          : 1;
  __REG32 TXERRINTR           : 1;
  __REG32 ATRSTOUTINTR        : 1;
  __REG32 ATRDTOUTINTR        : 1;
  __REG32 BLKTOUTINTR         : 1;
  __REG32 CHTOUTINTR          : 1;
  __REG32 RTOUTINTR           : 1;
  __REG32 RXWMARKINTR         : 1;
  __REG32 TXWMARKINTR         : 1;
  __REG32                     : 20;
} __SCI_IIR_bits;

/* SCI Control Register  */
typedef struct {
  __REG32 EN                  : 1;
  __REG32 PREDIV              : 1;
  __REG32                     : 2;
  __REG32 MUX_VCCEN           : 1;
  __REG32 MUX_Detect          : 1;
  __REG32                     : 26;
} __SCI_CONTROL_bits;



#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  SMC
 **
 ***************************************************************************/
__IO_REG32_BIT(SMC_BCR0,     0x80002000,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR1,     0x80002004,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR2,     0x80002008,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR3,     0x8000200c,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR6,     0x80002018,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR7,     0x8000201c,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_PC1ATTRIB,0x80002020,__READ_WRITE,__SMC_PCxATTRIB_bits);
__IO_REG32_BIT(SMC_PC1COM,   0x80002024,__READ_WRITE,__SMC_PCxCOM_bits);
__IO_REG32_BIT(SMC_PC1IO,    0x80002028,__READ_WRITE,__SMC_PCxIO_bits);
__IO_REG32_BIT(SMC_PC2ATTRIB,0x80002030,__READ_WRITE,__SMC_PCxATTRIB_bits);
__IO_REG32_BIT(SMC_PC2COM,   0x80002034,__READ_WRITE,__SMC_PCxCOM_bits);
__IO_REG32_BIT(SMC_PC2IO,    0x80002038,__READ_WRITE,__SMC_PCxIO_bits);
__IO_REG32_BIT(SMC_PCMCIACON,0x80002040,__READ_WRITE,__SMC_PCMCIACON_bits);


/***************************************************************************
 **
 **  SDRAM Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(SDRAMC_GBLCNFG, 0x80002404,__READ_WRITE,__SDRAMC_GBLCNFG_bits);
__IO_REG32_BIT(SDRAMC_RFSHTMR, 0x80002408,__READ_WRITE,__SDRAMC_RFSHTMR_bits);
__IO_REG32_BIT(SDRAMC_BOOTSTAT,0x8000240c,__READ_WRITE,__SDRAMC_BOOTSTAT_bits);
__IO_REG32_BIT(SDRAMC_SDCSC0,  0x80002410,__READ_WRITE,__SDRAMC_SDCSC_bits);
__IO_REG32_BIT(SDRAMC_SDCSC1,  0x80002414,__READ_WRITE,__SDRAMC_SDCSC_bits);
__IO_REG32_BIT(SDRAMC_SDCSC2,  0x80002418,__READ_WRITE,__SDRAMC_SDCSC_bits);
__IO_REG32_BIT(SDRAMC_SDCSC3,  0x8000241c,__READ_WRITE,__SDRAMC_SDCSC_bits);


/***************************************************************************
 **
 **  CSC
 **
 ***************************************************************************/
__IO_REG32_BIT(CSC_PWRSR,   0x80000400,__READ_WRITE,__CSC_PWRSR_bits);
__IO_REG32_BIT(CSC_PWRCNT,  0x80000404,__READ_WRITE,__CSC_PWRCNT_bits);
__IO_REG32(CSC_HALT,    0x80000408,__READ);
__IO_REG32(CSC_STBY,    0x8000040c,__READ);
__IO_REG32(CSC_BLEOI,   0x80000410,__WRITE);
__IO_REG32(CSC_MCEOI,   0x80000414,__WRITE);
__IO_REG32(CSC_TEOI,    0x80000418,__WRITE);
__IO_REG32(CSC_STFCLR,  0x8000041c,__WRITE);
__IO_REG32_BIT(CSC_CLKSET,  0x80000420,__READ_WRITE,__CSC_CLKSET_bits);
__IO_REG32(CSC_SCRREG0, 0x80000440,__READ_WRITE);
__IO_REG32(CSC_SCRREG1, 0x80000444,__READ_WRITE);
__IO_REG32_BIT(CSC_USBRESET,0x8000044c,__READ_WRITE,__CSC_USBRESET_bits);


/***************************************************************************
 **
 **  Interrupt controller
 **
 ***************************************************************************/
__IO_REG32_BIT(IC_INTSR, 0x80000500,__READ_WRITE,__IC_INTSR_bits);
__IO_REG32_BIT(IC_INTRSR,0x80000504,__READ_WRITE,__IC_INTSR_bits);
__IO_REG32_BIT(IC_INTENS,0x80000508,__READ_WRITE,__IC_INTSR_bits);
__IO_REG32_BIT(IC_INTENC,0x8000050c,__READ_WRITE,__IC_INTSR_bits);


/***************************************************************************
 **
 **  DMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DMA_CONTROL_USBTX,  0x80002800,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_USBTX,0x80002804,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_USBTX,   0x8000280c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_USBTX,   0x80002814,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_USBTX,  0x80002820,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_USBTX,    0x80002824,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_USBTX, 0x80002828,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_USBTX,  0x80002830,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_USBTX,    0x80002834,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_USBTX, 0x80002838,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_USBRX,  0x80002840,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_USBRX,0x80002844,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_USBRX,   0x8000284c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_USBRX,   0x80002854,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_USBRX,  0x80002860,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_USBRX,    0x80002864,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_USBRX, 0x80002868,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_USBRX,  0x80002870,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_USBRX,    0x80002874,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_USBRX, 0x80002878,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_MMCTX,  0x80002880,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_MMCTX,0x80002884,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_MMCTX,   0x8000288c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_MMCTX,   0x80002894,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_MMCTX,  0x800028a0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_MMCTX,    0x800028a4,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_MMCTX, 0x800028a8,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_MMCTX,  0x800028b0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_MMCTX,    0x800028b4,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_MMCTX, 0x800028b8,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_MMCRX,  0x800028c0,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_MMCRX,0x800028c4,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_MMCRX,   0x800028cc,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_MMCRX,   0x800028d4,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_MMCRX,  0x800028e0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_MMCRX,    0x800028e4,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_MMCRX, 0x800028e8,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_MMCRX,  0x800028f0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_MMCRX,    0x800028f4,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_MMCRX, 0x800028f8,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_AC97RX0,  0x80002a00,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_AC97RX0,0x80002a04,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_AC97RX0,   0x80002a0c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_AC97RX0,   0x80002a14,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_AC97RX0,  0x80002a20,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_AC97RX0,    0x80002a24,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_AC97RX0, 0x80002a28,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_AC97RX0,  0x80002a30,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_AC97RX0,    0x80002a34,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_AC97RX0, 0x80002a38,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_AC97TX0,  0x80002a40,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_AC97TX0,0x80002a44,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_AC97TX0,   0x80002a4c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_AC97TX0,   0x80002a54,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_AC97TX0,  0x80002a60,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_AC97TX0,    0x80002a64,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_AC97TX0, 0x80002a68,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_AC97TX0,  0x80002a70,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_AC97TX0,    0x80002a74,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_AC97TX0, 0x80002a78,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_AC97RX1,  0x80002a80,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_AC97RX1,0x80002a84,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_AC97RX1,   0x80002a8c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_AC97RX1,   0x80002a94,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_AC97RX1,  0x80002aa0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_AC97RX1,    0x80002aa4,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_AC97RX1, 0x80002aa8,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_AC97RX1,  0x80002ab0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_AC97RX1,    0x80002ab4,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_AC97RX1, 0x80002ab8,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_AC97TX1,  0x80002ac0,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_AC97TX1,0x80002ac4,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_AC97TX1,   0x80002acc,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_AC97TX1,   0x80002ad4,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_AC97TX1,  0x80002ae0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_AC97TX1,    0x80002ae4,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_AC97TX1, 0x80002ae8,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_AC97TX1,  0x80002af0,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_AC97TX1,    0x80002af4,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_AC97TX1, 0x80002af8,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_AC97RX2,  0x80002b00,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_AC97RX2,0x80002b04,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_AC97RX2,   0x80002b0c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_AC97RX2,   0x80002b14,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_AC97RX2,  0x80002b20,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_AC97RX2,    0x80002b24,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_AC97RX2, 0x80002b28,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_AC97RX2,  0x80002b30,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_AC97RX2,    0x80002b34,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_AC97RX2, 0x80002b38,__READ_WRITE);

__IO_REG32_BIT(DMA_CONTROL_AC97TX2,  0x80002b40,__READ_WRITE,__DMA_CONTROL_bits);
__IO_REG32_BIT(DMA_INTERRUPT_AC97TX2,0x80002b44,__READ_WRITE,__DMA_INTERRUPT_bits);
__IO_REG32_BIT(DMA_STATUS_AC97TX2,   0x80002b4c,__READ_WRITE,__DMA_STATUS_bits);
__IO_REG32_BIT(DMA_REMAIN_AC97TX2,   0x80002b54,__READ_WRITE,__DMA_REMAIN_bits);
__IO_REG32_BIT(DMA_MAXCNT0_AC97TX2,  0x80002b60,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE0_AC97TX2,    0x80002b64,__READ_WRITE);
__IO_REG32(DMA_CURRENT0_AC97TX2, 0x80002b68,__READ_WRITE);
__IO_REG32_BIT(DMA_MAXCNT1_AC97TX2,  0x80002b70,__READ_WRITE,__DMA_MAXCNT_bits);
__IO_REG32(DMA_BASE1_AC97TX2,    0x80002b74,__READ_WRITE);
__IO_REG32(DMA_CURRENT1_AC97TX2, 0x80002b78,__READ_WRITE);

// DMA global interrupt register
__IO_REG32_BIT(DMA_GINT, 0x80002bc0,__READ_WRITE,__DMA_GINT_bits);


/***************************************************************************
 **
 **  LCD
 **
 ***************************************************************************/
__IO_REG32_BIT(LCD_TIMING0,    0x80003000,__READ_WRITE,__LCD_TIMING0_bits);
__IO_REG32_BIT(LCD_TIMING1,    0x80003004,__READ_WRITE,__LCD_TIMING1_bits);
__IO_REG32_BIT(LCD_TIMING2,    0x80003008,__READ_WRITE,__LCD_TIMING2_bits);
__IO_REG32_BIT(LCD_TIMING3,    0x8000300c,__READ_WRITE,__LCD_TIMING3_bits);
__IO_REG32_BIT(LCD_UPBASE,     0x80003010,__READ_WRITE,__LCD_UPBASE_bits);
__IO_REG32_BIT(LCD_LPBASE,     0x80003014,__READ_WRITE,__LCD_LPBASE_bits);
__IO_REG32_BIT(LCD_INTREN,     0x80003018,__READ_WRITE,__LCD_INTREN_bits);
__IO_REG32_BIT(LCD_CONTROL,0x8000301c,__READ_WRITE,__LCD_CONTROL_bits);
__IO_REG32_BIT(LCD_STATUS, 0x80003020,__READ_WRITE,__LCD_STATUS_bits);
__IO_REG32_BIT(LCD_INTERRUPT,  0x80003024,__READ_WRITE,__LCD_INTERRUPT_bits);
__IO_REG32(LCD_UPCURR,     0x80003028,__READ_WRITE);
__IO_REG32(LCD_LPCURR,     0x8000302c,__READ_WRITE);
__IO_REG32_BIT(LCD_OVERFLOW,   0x80003030,__READ_WRITE,__LCD_OVERFLOW_bits);
__IO_REG32(PALETTE_1_0,      0x80003200,__READ_WRITE);

__IO_REG32_BIT(LCD_HRSETUP,  0x80001000,__READ_WRITE,__LCD_HRSETUP_bits);
#define ALISETUP        LCD_HRSETUP
#define ALISETUP_bit    LCD_HRSETUP_bit
__IO_REG32_BIT(LCD_HRCON,    0x80001004,__READ_WRITE,__LCD_HRCON_bits);
#define ALICONTROL      LCD_HRCON
#define ALICONTROL_bit  LCD_HRCON_bit
__IO_REG32_BIT(LCD_HRTIMING1,0x80001008,__READ_WRITE,__LCD_HRTIMING1_bits);
#define ALITIMING1      LCD_HRTIMING1
#define ALITIMING1_bit  LCD_HRTIMING1_bit
__IO_REG32_BIT(LCD_HRTIMING2,0x8000100c,__READ_WRITE,__LCD_HRTIMING2_bits);
#define ALITIMING2      LCD_HRTIMING2
#define ALITIMING2_bit  LCD_HRTIMING2_bit



/***************************************************************************
 **
 **  Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TIMER_LOAD1,   0x80000c00,__READ_WRITE,__TIMER_LOAD_bits);
__IO_REG32_BIT(TIMER_VALUE1,  0x80000c04,__READ_WRITE,__TIMER_VALUE_bits);
__IO_REG32_BIT(TIMER_CONTROL1,0x80000c08,__READ_WRITE,__TIMER_CONTROL12_bits);
__IO_REG32(TIMER_TCEOI1,  0x80000c0c,__READ_WRITE);
__IO_REG32_BIT(TIMER_LOAD2,   0x80000c20,__READ_WRITE,__TIMER_LOAD_bits);
__IO_REG32_BIT(TIMER_VALUE2,  0x80000c24,__READ_WRITE,__TIMER_VALUE_bits);
__IO_REG32_BIT(TIMER_CONTROL2,0x80000c28,__READ_WRITE,__TIMER_CONTROL12_bits);
__IO_REG32(TIMER_TCEOI2,  0x80000c2c,__READ_WRITE);
__IO_REG32_BIT(TIMER_BZCON,   0x80000c40,__READ_WRITE,__TIMER_BZCON_bits);
__IO_REG32_BIT(TIMER_LOAD3,   0x80000c80,__READ_WRITE,__TIMER_LOAD_bits);
__IO_REG32_BIT(TIMER_VALUE3,  0x80000c84,__READ_WRITE,__TIMER_VALUE_bits);
__IO_REG32_BIT(TIMER_CONTROL3,0x80000c88,__READ_WRITE,__TIMER_CONTROL3_bits);
__IO_REG32(TIMER_TCEOI3,  0x80000c8c,__READ_WRITE);


/***************************************************************************
 **
 **  Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDT_CTL,   0x80001400,__READ_WRITE,__WDT_CTL_bits);
__IO_REG32_BIT(WDT_RST,   0x80001404,__READ_WRITE,__WDT_RST_bits);
__IO_REG32_BIT(WDT_STATUS,0x80001408,__READ_WRITE,__WDT_STATUS_bits);
__IO_REG32_BIT(WDT_COUNT0,0x8000140c,__READ_WRITE,__WDT_COUNT_bits);
__IO_REG32_BIT(WDT_COUNT1,0x80001410,__READ_WRITE,__WDT_COUNT_bits);
__IO_REG32_BIT(WDT_COUNT2,0x80001414,__READ_WRITE,__WDT_COUNT_bits);
__IO_REG32_BIT(WDT_COUNT3,0x80001418,__READ_WRITE,__WDT_COUNT_bits);


/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32(RTCDR,  0x80000d00,__READ_WRITE);
__IO_REG32(RTCLR,  0x80000d04,__READ_WRITE);
__IO_REG32(RTCMR,  0x80000d08,__READ_WRITE);
__IO_REG32_BIT(RTCSTATCEOI,0x80000d10,__READ_WRITE,__RTCSTATCEOI_bits);

__IO_REG32_BIT(RTCCR,      0x80000d14,__READ_WRITE,__RTCCR_bits);


/***************************************************************************
 **
 **  SSP
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP_CR0,0x80000b00,__READ_WRITE,__SSP_CR0_bits);
__IO_REG32_BIT(SSP_CR1,0x80000b04,__READ_WRITE,__SSP_CR1_bits);
__IO_REG32_BIT(SSP_IIR,0x80000b08,__READ_WRITE,__SSP_IIR_bits);
#define SSP_ROEOI_bit __SSP_IIR_bit
#define SSP_ROEOI     __SSP_IIR
__IO_REG32_BIT(SSP_DR, 0x80000b0c,__READ_WRITE,__SSP_DR_bits);
__IO_REG32_BIT(SSP_CPR,0x80000b10,__READ_WRITE,__SSP_CPR_bits);
__IO_REG32_BIT(SSP_SR, 0x80000b14,__READ_WRITE,__SSP_SR_bits);


/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG32_BIT(UART_DATA_1,  0x80000600,__READ_WRITE,__UART_DATA_bits);
__IO_REG32_BIT(UART_FCON_1,  0x80000604,__READ_WRITE,__UART_FCON_bits);
__IO_REG32_BIT(UART_BRCON_1, 0x80000608,__READ_WRITE,__UART_BRCON_bits);
__IO_REG32_BIT(UART_CON_1,   0x8000060c,__READ_WRITE,__UART_CON_bits);
__IO_REG32_BIT(UART_STATUS_1,0x80000610,__READ_WRITE,__UART_STATUS_bits);
__IO_REG32_BIT(UART_RAWISR_1,0x80000614,__READ_WRITE,__UART_RAWISR_bits);
__IO_REG32_BIT(UART_INTEN_1, 0x80000618,__READ_WRITE,__UART_INTEN_bits);
__IO_REG32_BIT(UART_ISR_1,   0x8000061c,__READ_WRITE,__UART_ISR_bits);
__IO_REG32_BIT(UART_RES_1,   0x80000620,__READ_WRITE,__UART_RES_bits);
__IO_REG32_BIT(UART_EIC_1,   0x80000624,__WRITE     ,__UART_EIC_bits);
__IO_REG32_BIT(UART_DMACR_1, 0x80000628,__READ_WRITE,__UART_DMACR_bits);


/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG32_BIT(UART_DATA_2,  0x80000700,__READ_WRITE,__UART_DATA_bits);
__IO_REG32_BIT(UART_FCON_2,  0x80000704,__READ_WRITE,__UART_FCON_bits);
__IO_REG32_BIT(UART_BRCON_2, 0x80000708,__READ_WRITE,__UART_BRCON_bits);
__IO_REG32_BIT(UART_CON_2,   0x8000070c,__READ_WRITE,__UART_CON_bits);
__IO_REG32_BIT(UART_STATUS_2,0x80000710,__READ_WRITE,__UART_STATUS_bits);
__IO_REG32_BIT(UART_RAWISR_2,0x80000714,__READ_WRITE,__UART_RAWISR_bits);
__IO_REG32_BIT(UART_INTEN_2, 0x80000718,__READ_WRITE,__UART_INTEN_bits);
__IO_REG32_BIT(UART_ISR_2,   0x8000071c,__READ_WRITE,__UART_ISR_bits);
__IO_REG32_BIT(UART_RES_2,   0x80000720,__READ_WRITE,__UART_RES_bits);
__IO_REG32_BIT(UART_EIC_2,   0x80000724,__WRITE     ,__UART_EIC_bits);
__IO_REG32_BIT(UART_DMACR_2, 0x80000728,__READ_WRITE,__UART_DMACR_bits);


/***************************************************************************
 **
 **  UART3
 **
 ***************************************************************************/
__IO_REG32_BIT(UART_DATA_3,  0x80000800,__READ_WRITE,__UART_DATA_bits);
__IO_REG32_BIT(UART_FCON_3,  0x80000804,__READ_WRITE,__UART_FCON_bits);
__IO_REG32_BIT(UART_BRCON_3, 0x80000808,__READ_WRITE,__UART_BRCON_bits);
__IO_REG32_BIT(UART_CON_3,   0x8000080c,__READ_WRITE,__UART_CON_bits);
__IO_REG32_BIT(UART_STATUS_3,0x80000810,__READ_WRITE,__UART_STATUS_bits);
__IO_REG32_BIT(UART_RAWISR_3,0x80000814,__READ_WRITE,__UART_RAWISR_bits);
__IO_REG32_BIT(UART_INTEN_3, 0x80000818,__READ_WRITE,__UART_INTEN_bits);
__IO_REG32_BIT(UART_ISR_3,   0x8000081c,__READ_WRITE,__UART_ISR_bits);
__IO_REG32_BIT(UART_RES_3,   0x80000820,__READ_WRITE,__UART_RES_bits);
__IO_REG32_BIT(UART_EIC_3,   0x80000824,__WRITE     ,__UART_EIC_bits);
__IO_REG32_BIT(UART_DMACR_3, 0x80000828,__READ_WRITE,__UART_DMACR_bits);


/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIO_PAD,         0x80000e00,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PBD,         0x80000e04,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PCD,         0x80000e08,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PDD,         0x80000e0c,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PADD,        0x80000e10,__READ_WRITE,__GPIO_PyDD_bits);
__IO_REG32_BIT(GPIO_PBDD,        0x80000e14,__READ_WRITE,__GPIO_PyDD_bits);
__IO_REG32_BIT(GPIO_PCDD,        0x80000e18,__READ_WRITE,__GPIO_PyDD_bits);
__IO_REG32_BIT(GPIO_PDDD,        0x80000e1c,__READ_WRITE,__GPIO_PyDD_bits);
__IO_REG32_BIT(GPIO_PED,         0x80000e20,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PEDD,        0x80000e24,__READ_WRITE,__GPIO_PEDD_bits);
__IO_REG32_BIT(GPIO_KBDCTL,      0x80000e28,__READ_WRITE,__GPIO_KBDCTL_bits);
__IO_REG32_BIT(GPIO_PINMUX,      0x80000e2c,__READ_WRITE,__GPIO_PINMUX_bits);
__IO_REG32_BIT(GPIO_PFD,         0x80000e30,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PFDD,        0x80000e34,__READ_WRITE,__GPIO_PyDD_bits);
__IO_REG32_BIT(GPIO_PGD,         0x80000e38,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PGDD,        0x80000e3c,__READ_WRITE,__GPIO_PyDD_bits);
__IO_REG32_BIT(GPIO_PHD,         0x80000e40,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PHDD,        0x80000e44,__READ_WRITE,__GPIO_PyDD_bits);
__IO_REG32_BIT(GPIO_INTTYPE1,    0x80000e4c,__READ_WRITE,__GPIO_INTTYPE_bits);
__IO_REG32_BIT(GPIO_INTTYPE2,    0x80000e50,__READ_WRITE,__GPIO_INTTYPE_bits);
__IO_REG32_BIT(GPIO_GPIOFEOI,    0x80000e54,__READ_WRITE,__GPIO_INTTYPE_bits);
__IO_REG32_BIT(GPIO_GPIOINTEN,   0x80000e58,__READ_WRITE,__GPIO_INTTYPE_bits);
__IO_REG32_BIT(GPIO_INTSTATUS,   0x80000e5c,__READ_WRITE,__GPIO_INTTYPE_bits);
__IO_REG32_BIT(GPIO_RAWINTSTATUS,0x80000e60,__READ_WRITE,__GPIO_INTTYPE_bits);
__IO_REG32_BIT(GPIO_GPIODB,      0x80000e64,__READ_WRITE,__GPIO_INTTYPE_bits);
__IO_REG32_BIT(GPIO_PAPD,        0x80000e68,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PBPD,        0x80000e6c,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PCPD,        0x80000e70,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PDPD,        0x80000e74,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PEPD,        0x80000e78,__READ_WRITE,__GPIO_PEPD_bits);
__IO_REG32_BIT(GPIO_PFPD,        0x80000e7c,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PGPD,        0x80000e80,__READ_WRITE,__GPIO_PyD_bits);
__IO_REG32_BIT(GPIO_PHPD,        0x80000e84,__READ_WRITE,__GPIO_PyD_bits);


/***************************************************************************
 **
 **  MMC
 **
 ***************************************************************************/
__IO_REG32_BIT(MMC_CLOCK_CONTROL,0x80000100,__READ_WRITE,__MMC_STR_STP_CLK_bits);
__IO_REG32_BIT(MMC_STATUS,       0x80000104,__READ_WRITE,__MMC_STATUS_bits);
__IO_REG32_BIT(MMC_CLOCK_RATE,   0x80000108,__READ_WRITE,__MMC_CLK_RATE_bits);
__IO_REG32_BIT(MMC_CLOCK_PREDIV, 0x8000010c,__READ_WRITE,__MMC_CLOCK_PREDIV_bits);
__IO_REG32_BIT(MMC_SPI,          0x80000110,__READ_WRITE,__MMC_SPI_REG_bits);
__IO_REG32_BIT(MMC_CMD_CONTROL,  0x80000114,__READ_WRITE,__MMC_CMD_CONTROL_bits);
__IO_REG32_BIT(MMC_RESPONSE_TO,  0x80000118,__READ_WRITE,__MMC_RES_TO_bits);
__IO_REG32_BIT(MMC_READ_TO,      0x8000011c,__READ_WRITE,__MMC_READ_TO_bits);
__IO_REG32_BIT(MMC_BLOCK_LEN,    0x80000120,__READ_WRITE,__MMC_BLK_LEN_bits);
__IO_REG32_BIT(MMC_BLOCK_COUNT,  0x80000124,__READ_WRITE,__MMC_NOB_bits);
__IO_REG32_BIT(MMC_INT_STATUS,   0x80000128,__READ_WRITE,__MMC_INT_STATUS_bits);
__IO_REG32_BIT(MMC_INT_CLEAR,    0x8000012c,__READ_WRITE,__MMC_INT_CLEAR_bits);
__IO_REG32_BIT(MMC_INT_EN,       0x80000134,__READ_WRITE,__MMC_INT_EN_bits);
__IO_REG32_BIT(MMC_COMMAND,      0x80000138,__READ_WRITE,__MMC_CMD_bits);
__IO_REG32(MMC_ARGUMENT,         0x8000013c,__READ_WRITE);
__IO_REG32_BIT(MMC_RESPONSE_FIFO,0x80000140,__READ_WRITE,__MMC_RES_FIFO_bits);
__IO_REG32_BIT(MMC_DATA_FIFO,    0x80000148,__READ_WRITE,__MMC_DATA_FIFO_bits);
__IO_REG32_BIT(MMC_BUF_PART_FULL,0x8000014c,__READ_WRITE,__MMC_BUF_PART_FULL_bits);


/***************************************************************************
 **
 **  USB Client
 **
 ***************************************************************************/
__IO_REG32_BIT(USB_FAR,    0x80000200,__READ_WRITE,__USB_FAR_bits);
__IO_REG32_BIT(USB_PMR,    0x80000204,__READ_WRITE,__USB_PMR_bits);
__IO_REG32_BIT(USB_IIR,    0x80000208,__READ_WRITE,__USB_IIR_bits);
__IO_REG32_BIT(USB_OIR,    0x80000210,__READ_WRITE,__USB_OIR_bits);
__IO_REG32_BIT(USB_UIR,    0x80000218,__READ_WRITE,__USB_UIR_bits);
__IO_REG32_BIT(USB_IIE,    0x8000021c,__READ_WRITE,__USB_IIE_bits);
__IO_REG32_BIT(USB_OIE,    0x80000224,__READ_WRITE,__USB_OIE_bits);
__IO_REG32_BIT(USB_UIE,    0x8000022c,__READ_WRITE,__USB_UIE_bits);
__IO_REG32_BIT(USB_FRAME1, 0x80000230,__READ_WRITE,__USB_FRAME1_bits);
__IO_REG32_BIT(USB_FRAME2, 0x80000234,__READ_WRITE,__USB_FRAME2_bits);
__IO_REG32_BIT(USB_INDEX,  0x80000238,__READ_WRITE,__USB_INDEX_bits);

__IO_REG32_BIT(USB_INMAXP, 0x80000240,__READ_WRITE,__USB_MAXP_bits);
__IO_REG32_BIT(USB_INCSR1, 0x80000244,__READ_WRITE,__USB_INCSR1_EP0CSR_bits);
#define USB_EP0CSR     USB_INCSR1
#define USB_EP0CSR_bit USB_INCSR1_bit

__IO_REG32_BIT(USB_INCSR2, 0x80000248,__READ_WRITE,__USB_INCSR2_bits);
__IO_REG32_BIT(USB_OUTMAXP,0x8000024c,__READ_WRITE,__USB_MAXP_bits);
__IO_REG32_BIT(USB_OUTCSR1,0x80000250,__READ_WRITE,__USB_OUTCSR1_bits);
__IO_REG32_BIT(USB_OUTCSR2,0x80000254,__READ_WRITE,__USB_OUTCSR2_bits);
__IO_REG32_BIT(USB_COUNT1, 0x80000258,__READ_WRITE,__USB_COUNT1_bits);

__IO_REG32(USB_EP0FIFO,0x80000280,__READ_WRITE);
__IO_REG32(USB_EP1FIFO,0x80000284,__READ_WRITE);
__IO_REG32(USB_EP2FIFO,0x80000288,__READ_WRITE);
__IO_REG32(USB_EP3FIFO,0x8000028c,__READ_WRITE);


/***************************************************************************
 **
 **  AC97
 **
 ***************************************************************************/
__IO_REG32_BIT(AC97_DR1,    0x80000000,__READ_WRITE,__AC97_DRx_bits);
__IO_REG32_BIT(AC97_RXCR1,  0x80000004,__READ_WRITE,__AC97_RXCRx_bits);
__IO_REG32_BIT(AC97_TXCR1,  0x80000008,__READ_WRITE,__AC97_TXCRx_bits);
__IO_REG32_BIT(AC97_SR1,    0x8000000c,__READ_WRITE,__AC97_SRx_bits);
__IO_REG32_BIT(AC97_RISR1,  0x80000010,__READ_WRITE,__AC97_RISRx_bits);
__IO_REG32_BIT(AC97_ISR1,   0x80000014,__READ_WRITE,__AC97_ISRx_bits);
__IO_REG32_BIT(AC97_IE1,    0x80000018,__READ_WRITE,__AC97_IEx_bits);

__IO_REG32_BIT(AC97_DR2,    0x80000020,__READ_WRITE,__AC97_DRx_bits);
__IO_REG32_BIT(AC97_RXCR2,  0x80000024,__READ_WRITE,__AC97_RXCRx_bits);
__IO_REG32_BIT(AC97_TXCR2,  0x80000028,__READ_WRITE,__AC97_TXCRx_bits);
__IO_REG32_BIT(AC97_SR2,    0x8000002c,__READ_WRITE,__AC97_SRx_bits);
__IO_REG32_BIT(AC97_RISR2,  0x80000030,__READ_WRITE,__AC97_RISRx_bits);
__IO_REG32_BIT(AC97_ISR2,   0x80000034,__READ_WRITE,__AC97_ISRx_bits);
__IO_REG32_BIT(AC97_IE2,    0x80000038,__READ_WRITE,__AC97_IEx_bits);

__IO_REG32_BIT(AC97_DR3,    0x80000040,__READ_WRITE,__AC97_DRx_bits);
__IO_REG32_BIT(AC97_RXCR3,  0x80000044,__READ_WRITE,__AC97_RXCRx_bits);
__IO_REG32_BIT(AC97_TXCR3,  0x80000048,__READ_WRITE,__AC97_TXCRx_bits);
__IO_REG32_BIT(AC97_SR3,    0x8000004c,__READ_WRITE,__AC97_SRx_bits);
__IO_REG32_BIT(AC97_RISR3,  0x80000050,__READ_WRITE,__AC97_RISRx_bits);
__IO_REG32_BIT(AC97_ISR3,   0x80000054,__READ_WRITE,__AC97_ISRx_bits);
__IO_REG32_BIT(AC97_IE3,    0x80000058,__READ_WRITE,__AC97_IEx_bits);

__IO_REG32_BIT(AC97_DR4,    0x80000060,__READ_WRITE,__AC97_DRx_bits);
__IO_REG32_BIT(AC97_RXCR4,  0x80000064,__READ_WRITE,__AC97_RXCRx_bits);
__IO_REG32_BIT(AC97_TXCR4,  0x80000068,__READ_WRITE,__AC97_TXCRx_bits);
__IO_REG32_BIT(AC97_SR4,    0x8000006c,__READ_WRITE,__AC97_SRx_bits);
__IO_REG32_BIT(AC97_RISR4,  0x80000070,__READ_WRITE,__AC97_RISRx_bits);
__IO_REG32_BIT(AC97_ISR4,   0x80000074,__READ_WRITE,__AC97_ISRx_bits);
__IO_REG32_BIT(AC97_IE4,    0x80000078,__READ_WRITE,__AC97_IEx_bits);

__IO_REG32_BIT(AC97_S1DATA, 0x80000080,__READ_WRITE,__AC97_S1DATA_bits);
__IO_REG32_BIT(AC97_S2DATA, 0x80000084,__READ_WRITE,__AC97_S2DATA_bits);
__IO_REG32_BIT(AC97_S12DATA,0x80000088,__READ_WRITE,__AC97_S12DATA_bits);
__IO_REG32_BIT(AC97_RGIS,   0x8000008c,__READ_WRITE,__AC97_RGIS_bits);
__IO_REG32_BIT(AC97_GIS,    0x80000090,__READ_WRITE,__AC97_GIS_bits);
__IO_REG32_BIT(AC97_GIEN,   0x80000094,__READ_WRITE,__AC97_GIEN_bits);
__IO_REG32_BIT(AC97_GEOI,   0x80000098,__READ_WRITE,__AC97_GEOI_bits);
__IO_REG32_BIT(AC97_GCR,    0x8000009c,__READ_WRITE,__AC97_GCR_bits);
__IO_REG32_BIT(AC97_RESET,  0x800000a0,__READ_WRITE,__AC97_RESET_bits);
__IO_REG32_BIT(AC97_SYNC,   0x800000a4,__READ_WRITE,__AC97_SYNC_bits);
__IO_REG32_BIT(AC97_GCIS,   0x800000a8,__READ_WRITE,__AC97_GCIS_bits);


/***************************************************************************
 **
 **  ACI
 **
 ***************************************************************************/
__IO_REG32_BIT(ACI_DATA,  0x80000a00,__READ_WRITE,__ACI_DATA_bits);
__IO_REG32_BIT(ACI_CTL,   0x80000a04,__READ_WRITE,__ACI_CTL_bits);
__IO_REG32_BIT(ACI_STATUS,0x80000a08,__READ_WRITE,__ACI_STATUS_bits);
__IO_REG32(ACI_EOI,   0x80000a0c,__READ_WRITE);
__IO_REG32_BIT(ACI_CLKDIV,0x80000a10,__READ_WRITE,__ACI_CLKDIV_bits);


/***************************************************************************
 **
 **  BMI
 **
 ***************************************************************************/
__IO_REG32(BMI_SWIDR,   0x80000f00,__READ_WRITE);
__IO_REG32_BIT(BMI_SWICR,     0x80000f04,__READ_WRITE,__BMI_SWICR_bits);
__IO_REG32_BIT(BMI_SWISR,     0x80000f08,__READ_WRITE,__BMI_SWISR_bits);
__IO_REG32_BIT(BMI_SWIRSREOI, 0x80000f0c,__READ_WRITE,__BMI_SWIRSREOI_bits);
__IO_REG32_BIT(BMI_SWIISR,    0x80000f10,__READ_WRITE,__BMI_SWIISR_bits);
__IO_REG32_BIT(BMI_SWIIER,    0x80000f14,__READ_WRITE,__BMI_SWIISR_bits);
__IO_REG32_BIT(BMI_SWITR,     0x80000f18,__READ_WRITE,__BMI_SWITR_bits);
__IO_REG32_BIT(BMI_SWIBR,     0x80000f1c,__READ_WRITE,__BMI_SWIBR_bits);

__IO_REG32(BMI_SBIDR,     0x80000f40,__READ_WRITE);
__IO_REG32_BIT(BMI_SBICR,     0x80000f44,__READ_WRITE,__BMI_SBICR_bits);
__IO_REG32_BIT(BMI_SBICOUNT,  0x80000f48,__READ_WRITE,__BMI_SBICOUNT_bits);
__IO_REG32_BIT(BMI_SBISR,     0x80000f4c,__READ_WRITE,__BMI_SBISR_bits);
__IO_REG32_BIT(BMI_SBIRISREOI,0x80000f50,__READ_WRITE,__BMI_SBIRISREOI_bits);
__IO_REG32_BIT(BMI_SBIISR,    0x80000f54,__READ_WRITE,__BMI_SBIISR_bits);
__IO_REG32_BIT(BMI_SBIIER,    0x80000f58,__READ_WRITE,__BMI_SBIIER_bits);


/***************************************************************************
 **
 **  DC-DC converter
 **
 ***************************************************************************/
__IO_REG32_BIT(DCDCCON,  0x80000900,__READ_WRITE,__DCDCCON_bits);
__IO_REG32_BIT(DCDCFREQ, 0x80000908,__READ_WRITE,__DCDCFREQ_bits);


/***************************************************************************
 **
 **  SCI
 **
 ***************************************************************************/
__IO_REG32_BIT(SCI_DATA,       0x80000300,__READ_WRITE,__SCI_DATA_bits);
__IO_REG32_BIT(SCI_CR0,        0x80000304,__READ_WRITE,__SCI_CR0_bits);
__IO_REG32_BIT(SCI_CR1,        0x80000308,__READ_WRITE,__SCI_CR1_bits);
__IO_REG32_BIT(SCI_CR2,        0x8000030c,__READ_WRITE,__SCI_CR2_bits);
__IO_REG32_BIT(SCI_IER,        0x80000310,__READ_WRITE,__SCI_IER_bits);
__IO_REG32_BIT(SCI_RETRY,      0x80000314,__READ_WRITE,__SCI_RETRY_bits);
__IO_REG32_BIT(SCI_WMARK,      0x80000318,__READ_WRITE,__SCI_WMARK_bits);
__IO_REG32_BIT(SCI_TXCOUNT,    0x8000031c,__READ_WRITE,__SCI_TXCOUNT_bits);
__IO_REG32_BIT(SCI_RXCOUNT,    0x80000320,__READ_WRITE,__SCI_RXCOUNT_bits);
__IO_REG32_BIT(SCI_FR,         0x80000324,__READ_WRITE,__SCI_FR_bits);
__IO_REG32_BIT(SCI_RXTIME,     0x80000328,__READ_WRITE,__SCI_RXTIME_bits);
__IO_REG32_BIT(SCI_DSTAT,      0x8000032c,__READ_WRITE,__SCI_DSTAT_bits);
__IO_REG32_BIT(SCI_STABLE,     0x80000330,__READ_WRITE,__SCI_STABLE_bits);
__IO_REG32_BIT(SCI_ATIME,      0x80000334,__READ_WRITE,__SCI_ATIME_bits);
__IO_REG32_BIT(SCI_DTIME,      0x80000338,__READ_WRITE,__SCI_DTIME_bits);
__IO_REG32_BIT(SCI_ATRSTIME,   0x8000033c,__READ_WRITE,__SCI_ATRSTIME_bits);
__IO_REG32_BIT(SCI_ATRDTIME,   0x80000340,__READ_WRITE,__SCI_ATRDTIME_bits);
__IO_REG32_BIT(SCI_BLKTIME,    0x80000344,__READ_WRITE,__SCI_BLKTIME_bits);
__IO_REG32_BIT(SCI_CHTIME,     0x80000348,__READ_WRITE,__SCI_CHTIME_bits);
__IO_REG32_BIT(SCI_CLKDIV,     0x8000034c,__READ_WRITE,__SCI_CLKDIV_bits);
__IO_REG32_BIT(SCI_BAUD,       0x80000350,__READ_WRITE,__SCI_BAUD_bits);
__IO_REG32_BIT(SCI_CYCLES,     0x80000354,__READ_WRITE,__SCI_CYCLES_bits);
__IO_REG32_BIT(SCI_CHGUARD,    0x80000358,__READ_WRITE,__SCI_CHGUARD_bits);
__IO_REG32_BIT(SCI_BLKGUARD,   0x8000035c,__READ_WRITE,__SCI_BLKGUARD_bits);
__IO_REG32_BIT(SCI_SYNCCR,     0x80000360,__READ_WRITE,__SCI_SYNCCR_bits);
__IO_REG32_BIT(SCI_SYNCDATA,   0x80000364,__READ_WRITE,__SCI_SYNCDATA_bits);
__IO_REG32_BIT(SCI_RAWSTAT,    0x80000368,__READ_WRITE,__SCI_RAWSTAT_bits);
__IO_REG32_BIT(SCI_IIR,        0x8000036c,__READ_WRITE,__SCI_IIR_bits);
__IO_REG32_BIT(SCI_CONTROL,    0x80000370,__READ_WRITE,__SCI_CONTROL_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 ***************************************************************************/
/***************************************************************************
 **
 **  Interrupt vector table
 **
 ***************************************************************************/
#define RESETV        0x00  /* Reset                                       */
#define UNDEFV        0x04  /* Undefined instruction                       */
#define SWIV          0x08  /* Software interrupt                          */
#define PABORTV       0x0c  /* Prefetch abort                              */
#define DABORTV       0x10  /* Data abort                                  */
#define IRQV          0x18  /* Normal interrupt                            */
#define FIQV          0x1c  /* Fast interrupt                              */

/***************************************************************************
 **
 **   Interrupt Controller channels
 **
 ***************************************************************************/
#define IC_GPIO0FIQ       0
#define IC_BLINT          1
#define IC_WDINTR         2
#define IC_MCINT          3
#define IC_ACIINTR        4
#define IC_GPIO1INTR      5
#define IC_GPIO2INTR      6
#define IC_GPIO3INTR      7
#define IC_TC1OI          8
#define IC_TC2OI          9
#define IC_RTCINTR       10
#define IC_TINTR         11
#define IC_UART1INTR     12
#define IC_UART2INTR     13
#define IC_LCDINTR       14
#define IC_SSPINTR       15
#define IC_UART3INTR     16
#define IC_SCIINTR       17
#define IC_AC97INTR      18
#define IC_MMCINTR       19
#define IC_USBINTR       20
#define IC_DMAINTR       21
#define IC_TC3OI         22
#define IC_GPIO4INTR     23
#define IC_GPIO5INTR     24
#define IC_GPIO6INTR     25
#define IC_GPIO7INTR     26
#define IC_BMIINTR       27

#endif    /* __LH7A400_H */
