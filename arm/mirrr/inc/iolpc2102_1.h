/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    NXP LPC2102
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2003
 **
 **    $Revision: 1.2.2.1 $
 **
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/

#ifndef __IOLPC2102_H
#define __IOLPC2102_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    IOLPC2102 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#if __LITTLE_ENDIAN__ == 0
#error This file should only be compiled in little endian mode
#endif

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* External Interrupt Register */
typedef struct{
__REG32 EINT0  : 1;
__REG32 EINT1  : 1;
__REG32 EINT2  : 1;
__REG32        :29;
} __extint_bits;

/* External Interrupt Wakeup Register */
typedef struct{
__REG32 EXTWAKE0  : 1;
__REG32 EXTWAKE1  : 1;
__REG32 EXTWAKE2  : 1;
__REG32           :12;
__REG32 RTCWAKE   : 1;
__REG32           :16;
} __extwake_bits;

/* External Interrupt Mode Register */
typedef struct{
__REG32 EXTMODE0  : 1;
__REG32 EXTMODE1  : 1;
__REG32 EXTMODE2  : 1;
__REG32           :29;
} __extmode_bits;

/* External Interrupt Polarity Register */
typedef struct{
__REG32 EXTPOLAR0  : 1;
__REG32 EXTPOLAR1  : 1;
__REG32 EXTPOLAR2  : 1;
__REG32            :29;
} __extpol_bits;

/* System Control/Status Flags Register */
typedef struct{
__REG32 GPIO0M  : 1;
__REG32         :31;
} __scs_bits;

/* Memory Mapping Control Register */
typedef struct{
__REG32 MAP  : 2;
__REG32      :30;
} __memmap_bits;

/* PLL Control Register */
typedef struct{
__REG32 PLLE  : 1;
__REG32 PLLC  : 1;
__REG32       :30;
} __pllcon_bits;

/* PLL Config Register */
typedef struct{
__REG32 MSEL  : 5;
__REG32 PSEL  : 2;
__REG32       :25;
} __pllcfg_bits;

/* PLL Status Register */
typedef struct{
__REG32 MSEL   : 5;
__REG32 PSEL   : 2;
__REG32        : 1;
__REG32 PLLE   : 1;
__REG32 PLLC   : 1;
__REG32 PLOCK  : 1;
__REG32        :21;
} __pllstat_bits;

/* PLL Feed Register */
typedef struct{
__REG32 FEED  : 8;
__REG32       :24;
} __pllfeed_bits;

/* Power Control Register */
typedef struct{
__REG32 IDL  : 1;
__REG32 PD   : 1;
__REG32      :30;
} __pcon_bits;

/* Power Control For Peripherals Register */
typedef struct{
__REG32          : 1;
__REG32 PCTIM0   : 1;
__REG32 PCTIM1   : 1;
__REG32 PCUART0  : 1;
__REG32 PCUART1  : 1;
__REG32          : 2;
__REG32 PCI2C0   : 1;
__REG32 PCSPI    : 1;
__REG32 PCRTC    : 1;
__REG32 PCSSP    : 1;
__REG32          : 1;
__REG32 PCAD     : 1;
__REG32          : 6;
__REG32 PCI2C1   : 1;
__REG32          : 8;
__REG32 PCTIM2   : 1;
__REG32 PCTIM3   : 1;
__REG32          : 2;
} __pconp_bits;

/* Reset Source Identification Register */
typedef struct{
__REG32 POR   : 1;
__REG32 EXTR  : 1;
__REG32 WDTR  : 1;
__REG32       :29;
} __rsir_bits;

/* APB Divider Register */
typedef struct{
__REG32 APBDIV  : 2;
__REG32         :30;
} __apbdiv_bits;

/* Memory Accelerator Module Control Register */
typedef struct{
__REG32 MODECTRL  : 2;
__REG32           :30;
} __mamcr_bits;

/* Memory Accelerator Module Timing Register */
typedef struct{
__REG32 CYCLES  : 3;
__REG32         :29;
} __mamtim_bits;

/* VIC Interrupt Registers */
typedef struct{
__REG32 WDT      : 1;
__REG32          : 1;
__REG32 DEBUGRX  : 1;
__REG32 DEBUGTX  : 1;
__REG32 TIMER0   : 1;
__REG32 TIMER1   : 1;
__REG32 UART0    : 1;
__REG32 UART1    : 1;
__REG32          : 1;
__REG32 I2C0     : 1;
__REG32 SPI0     : 1;
__REG32 SSP      : 1;
__REG32 PLL      : 1;
__REG32 RTC      : 1;
__REG32 EINT0    : 1;
__REG32 EINT1    : 1;
__REG32 EINT2    : 1;
__REG32          : 1;
__REG32 AD0      : 1;
__REG32 I2C1     : 1;
__REG32          : 6;
__REG32 TIMER2   : 1;
__REG32 TIMER3   : 1;
__REG32          : 4;
} __vicint_bits;

/* VIC Vector Control Registers */
typedef struct{
__REG32 NUMBER   : 5;
__REG32 ENABLED  : 1;
__REG32          :26;
} __vicvectcntl_bits;

/* VIC Protection Enable Register */
typedef struct{
__REG32 PROTECT  : 1;
__REG32          :31;
} __vicprotection_bits;

/* Pin Function Select Register 0 */
typedef struct{
__REG32 P0_0   : 2;
__REG32 P0_1   : 2;
__REG32 P0_2   : 2;
__REG32 P0_3   : 2;
__REG32 P0_4   : 2;
__REG32 P0_5   : 2;
__REG32 P0_6   : 2;
__REG32 P0_7   : 2;
__REG32 P0_8   : 2;
__REG32 P0_9   : 2;
__REG32 P0_10  : 2;
__REG32 P0_11  : 2;
__REG32 P0_12  : 2;
__REG32 P0_13  : 2;
__REG32 P0_14  : 2;
__REG32 P0_15  : 2;
} __pinsel0_bits;

/* Pin Function Select Register 1 */
typedef struct{
__REG32 P0_16  : 2;
__REG32 P0_17  : 2;
__REG32 P0_18  : 2;
__REG32 P0_19  : 2;
__REG32 P0_20  : 2;
__REG32 P0_21  : 2;
__REG32 P0_22  : 2;
__REG32 P0_23  : 2;
__REG32 P0_24  : 2;
__REG32 P0_25  : 2;
__REG32 P0_26  : 2;
__REG32 P0_27  : 2;
__REG32 P0_28  : 2;
__REG32 P0_29  : 2;
__REG32 P0_30  : 2;
__REG32 P0_31  : 2;
} __pinsel1_bits;

/* GPIO Registers */
typedef struct {
__REG32 P0_0   : 1;
__REG32 P0_1   : 1;
__REG32 P0_2   : 1;
__REG32 P0_3   : 1;
__REG32 P0_4   : 1;
__REG32 P0_5   : 1;
__REG32 P0_6   : 1;
__REG32 P0_7   : 1;
__REG32 P0_8   : 1;
__REG32 P0_9   : 1;
__REG32 P0_10  : 1;
__REG32 P0_11  : 1;
__REG32 P0_12  : 1;
__REG32 P0_13  : 1;
__REG32 P0_14  : 1;
__REG32 P0_15  : 1;
__REG32 P0_16  : 1;
__REG32 P0_17  : 1;
__REG32 P0_18  : 1;
__REG32 P0_19  : 1;
__REG32 P0_20  : 1;
__REG32 P0_21  : 1;
__REG32 P0_22  : 1;
__REG32 P0_23  : 1;
__REG32 P0_24  : 1;
__REG32 P0_25  : 1;
__REG32 P0_26  : 1;
__REG32 P0_27  : 1;
__REG32 P0_28  : 1;
__REG32 P0_29  : 1;
__REG32 P0_30  : 1;
__REG32 P0_31  : 1;
} __gpio_bits;

/* FGPIO Registers */
typedef union{
  struct {
    __REG32 P0_0   : 1;
    __REG32 P0_1   : 1;
    __REG32 P0_2   : 1;
    __REG32 P0_3   : 1;
    __REG32 P0_4   : 1;
    __REG32 P0_5   : 1;
    __REG32 P0_6   : 1;
    __REG32 P0_7   : 1;
    __REG32 P0_8   : 1;
    __REG32 P0_9   : 1;
    __REG32 P0_10  : 1;
    __REG32 P0_11  : 1;
    __REG32 P0_12  : 1;
    __REG32 P0_13  : 1;
    __REG32 P0_14  : 1;
    __REG32 P0_15  : 1;
    __REG32 P0_16  : 1;
    __REG32 P0_17  : 1;
    __REG32 P0_18  : 1;
    __REG32 P0_19  : 1;
    __REG32 P0_20  : 1;
    __REG32 P0_21  : 1;
    __REG32 P0_22  : 1;
    __REG32 P0_23  : 1;
    __REG32 P0_24  : 1;
    __REG32 P0_25  : 1;
    __REG32 P0_26  : 1;
    __REG32 P0_27  : 1;
    __REG32 P0_28  : 1;
    __REG32 P0_29  : 1;
    __REG32 P0_30  : 1;
    __REG32 P0_31  : 1;
  };
  struct
  {
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      struct{
        __REG16 P0_0   : 1;
        __REG16 P0_1   : 1;
        __REG16 P0_2   : 1;
        __REG16 P0_3   : 1;
        __REG16 P0_4   : 1;
        __REG16 P0_5   : 1;
        __REG16 P0_6   : 1;
        __REG16 P0_7   : 1;
        __REG16 P0_8   : 1;
        __REG16 P0_9   : 1;
        __REG16 P0_10  : 1;
        __REG16 P0_11  : 1;
        __REG16 P0_12  : 1;
        __REG16 P0_13  : 1;
        __REG16 P0_14  : 1;
        __REG16 P0_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      struct{
        __REG16 P0_0   : 1;
        __REG16 P0_1   : 1;
        __REG16 P0_2   : 1;
        __REG16 P0_3   : 1;
        __REG16 P0_4   : 1;
        __REG16 P0_5   : 1;
        __REG16 P0_6   : 1;
        __REG16 P0_7   : 1;
        __REG16 P0_8   : 1;
        __REG16 P0_9   : 1;
        __REG16 P0_10  : 1;
        __REG16 P0_11  : 1;
        __REG16 P0_12  : 1;
        __REG16 P0_13  : 1;
        __REG16 P0_14  : 1;
        __REG16 P0_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio_bits;

/* UART Fractional Divider Register */
typedef struct{
__REG32 DIVADDVAL  : 4;
__REG32 MULVAL     : 4;
__REG32            :24;
} __uartfdr_bits;

/* UART Interrupt Enable Register */
typedef struct{
__REG32 RDAIE      : 1;
__REG32 THREIE     : 1;
__REG32 RXLSIE     : 1;
__REG32            : 5;
__REG32 ABTOIntEn  : 1;
__REG32 ABEOIntEn  : 1;
__REG32            :22;
} __uartier0_bits;

/* UART Interrupt Enable Register */
typedef struct{
__REG32 RDAIE      : 1;
__REG32 THREIE     : 1;
__REG32 RXLSIE     : 1;
__REG32 MSIE       : 1;
__REG32            : 3;
__REG32 CTSIE      : 1;
__REG32 ABTOIntEn  : 1;
__REG32 ABEOIntEn  : 1;
__REG32            :22;
} __uartier1_bits;

/* UART Interrupt Identification Register and Fifo Control Register */
typedef union{
  /* UxIIR */
  struct {
__REG32 IP       : 1;
__REG32 IID      : 3;
__REG32          : 2;
__REG32 IIRFE    : 2;
__REG32 ABEOInt  : 1;
__REG32 ABTOInt  : 1;
__REG32          :22;
  };
  /* UxFCR */
  struct {
__REG32 FCRFE    : 1;
__REG32 RFR      : 1;
__REG32 TFR      : 1;
__REG32          : 3;
__REG32 RTLS     : 2;
__REG32          :24;
  };
} __uartfcriir_bits;

/* UART Line Control Register */
typedef struct{
__REG8  WLS   : 2;
__REG8  SBS   : 1;
__REG8  PE    : 1;
__REG8  PS    : 2;
__REG8  BC    : 1;
__REG8  DLAB  : 1;
} __uartlcr_bits;

/* UART Line Status Register */
typedef struct{
__REG8  DR    : 1;
__REG8  OE    : 1;
__REG8  PE    : 1;
__REG8  FE    : 1;
__REG8  BI    : 1;
__REG8  THRE  : 1;
__REG8  TEMT  : 1;
__REG8  RXFE  : 1;
} __uartlsr_bits;

/* UART Auto-baud Control Register */
typedef struct{
__REG32 Start        : 1;
__REG32 Mode         : 1;
__REG32 AutoRestart  : 1;
__REG32              : 5;
__REG32 ABEOIntClr   : 1;
__REG32 ABTOIntClr   : 1;
__REG32              :22;
} __uartacr_bits;

/* UART Transmit Enable Register */
typedef struct{
__REG8        : 7;
__REG8  TXEN  : 1;
} __uartter_bits;

/* UART Modem Control Register */
typedef struct{
__REG8  DTR    : 1;
__REG8  RTS    : 1;
__REG8         : 2;
__REG8  LMS    : 1;
__REG8         : 1;
__REG8  RTSen  : 1;
__REG8  CTSen  : 1;
} __uartmcr_bits;

/* UART Modem Status Register */
typedef union{
  //U1MSR
  struct {
__REG8  DCTS  : 1;
__REG8  DDSR  : 1;
__REG8  TERI  : 1;
__REG8  DDCD  : 1;
__REG8  CTS   : 1;
__REG8  DSR   : 1;
__REG8  RI    : 1;
__REG8  DCD   : 1;
  };
  //U1MSR
  struct {
__REG8  MSR0  : 1;
__REG8  MSR1  : 1;
__REG8  MSR2  : 1;
__REG8  MSR3  : 1;
__REG8  MSR4  : 1;
__REG8  MSR5  : 1;
__REG8  MSR6  : 1;
__REG8  MSR7  : 1;
  };
} __uartmsr_bits;

/* I2C Control Set Register */
typedef struct{
__REG32       : 2;
__REG32 AA    : 1;
__REG32 SI    : 1;
__REG32 STO   : 1;
__REG32 STA   : 1;
__REG32 I2EN  : 1;
__REG32       :25;
} __i2conset_bits;

/* I2C Control Clear Register */
typedef struct{
__REG32        : 2;
__REG32 AAC    : 1;
__REG32 SIC    : 1;
__REG32        : 1;
__REG32 STAC   : 1;
__REG32 I2ENC  : 1;
__REG32        :25;
} __i2conclr_bits;

/* I2C Status Register */
typedef struct{
__REG32 STATUS  : 8;
__REG32         :24;
} __i2stat_bits;

/* I2C Data Register */
typedef struct{
__REG32 DATA  : 8;
__REG32       :24;
} __i2dat_bits;

/* I2C Slave Address Register */
typedef struct{
__REG32 GC    : 1;
__REG32 ADDR  : 7;
__REG32       :24;
} __i2adr_bits;

/* I2C SCL Duty Cycle Register */
typedef struct{
__REG32 COUNT  :16;
__REG32        :16;
} __i2scl_bits;

/* SPI Control Register */
typedef struct{
__REG32         : 2;
__REG32 BitEna  : 1;
__REG32 CPHA    : 1;
__REG32 CPOL    : 1;
__REG32 MSTR    : 1;
__REG32 LSBF    : 1;
__REG32 SPIE    : 1;
__REG32 BITS    : 4;
__REG32         :20;
} __spcr_bits;

/* SPI Status Register */
typedef struct{
__REG32       : 3;
__REG32 ABRT  : 1;
__REG32 MODF  : 1;
__REG32 ROVR  : 1;
__REG32 WCOL  : 1;
__REG32 SPIF  : 1;
__REG32       :24;
} __spsr_bits;

/* SPI Data Register */
typedef struct{
__REG32 DATA  :16;
__REG32       :16;
} __spdr_bits;

/* SPI Clock Counter Register */
typedef struct{
__REG32 COUNTER  : 8;
__REG32          :24;
} __spccr_bits;

/* SPI Interrupt Register */
typedef struct{
__REG32 SPIINT  : 1;
__REG32         :31;
} __spint_bits;

/* SSP Control Register 0 */
typedef struct{
__REG32 DSS   : 4;
__REG32 FRF   : 2;
__REG32 CPOL  : 1;
__REG32 CPHA  : 1;
__REG32 SCR   : 8;
__REG32       :16;
} __sspcr0_bits;

/* SSP Control Register 1 */
typedef struct{
__REG32 LBM  : 1;
__REG32 SSE  : 1;
__REG32 MS   : 1;
__REG32 SOD  : 1;
__REG32      :28;
} __sspcr1_bits;

/* SSP Data Register */
typedef struct{
__REG32 DATA  :16;
__REG32       :16;
} __sspdr_bits;

/* SSP Status Register */
typedef struct{
__REG32 TFE  : 1;
__REG32 TNF  : 1;
__REG32 RNE  : 1;
__REG32 RNF  : 1;
__REG32 BSY  : 1;
__REG32      :27;
} __sspsr_bits;

/* SSP Clock Prescale Register */
typedef struct{
__REG32 CPSDVSR  : 8;
__REG32          :24;
} __sspcpsr_bits;

/* SSP Interrupt Mask Set/Clear Register */
typedef struct{
__REG32 RORIM  : 1;
__REG32 RTIM   : 1;
__REG32 RXIM   : 1;
__REG32 TXIM   : 1;
__REG32        :28;
} __sspimsc_bits;

/* SSP Raw Interrupt Status Register */
typedef struct{
__REG32 RORRIS  : 1;
__REG32 RTRIS   : 1;
__REG32 RXRIS   : 1;
__REG32 TXRIS   : 1;
__REG32         :28;
} __sspris_bits;

/* SSP Masked Interrupt Register */
typedef struct{
__REG32 RORMIS  : 1;
__REG32 RTMIS   : 1;
__REG32 RXMIS   : 1;
__REG32 TXMIS   : 1;
__REG32         :28;
} __sspmis_bits;

/* SSP Interrupt Clear Registerr */
typedef struct{
__REG32 RORIC  : 1;
__REG32 RTIC   : 1;
__REG32        :30;
} __sspicr_bits;

/* A/D Control Register */
typedef struct{
__REG32 SEL     : 8;
__REG32 CLKDIV  : 8;
__REG32 BURST   : 1;
__REG32 CLKS    : 3;
__REG32         : 1;
__REG32 PDN     : 1;
__REG32         : 2;
__REG32 START   : 3;
__REG32 EDGE    : 1;
__REG32         : 4;
} __adcr_bits;

/* A/D Global Data Register */
typedef struct{
__REG32         : 6;
__REG32 RESULT  :10;
__REG32         : 8;
__REG32 CHN     : 3;
__REG32         : 3;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __adgdr_bits;

/* A/D Status Register */
typedef struct{
__REG32 DONE0     : 1;
__REG32 DONE1     : 1;
__REG32 DONE2     : 1;
__REG32 DONE3     : 1;
__REG32 DONE4     : 1;
__REG32 DONE5     : 1;
__REG32 DONE6     : 1;
__REG32 DONE7     : 1;
__REG32 OVERRUN0  : 1;
__REG32 OVERRUN1  : 1;
__REG32 OVERRUN2  : 1;
__REG32 OVERRUN3  : 1;
__REG32 OVERRUN4  : 1;
__REG32 OVERRUN5  : 1;
__REG32 OVERRUN6  : 1;
__REG32 OVERRUN7  : 1;
__REG32 ADINT     : 1;
__REG32           :15;
} __adstat_bits;

/* A/D Intrrupt Enable Register */
typedef struct{
__REG32 ADINTEN0  : 1;
__REG32 ADINTEN1  : 1;
__REG32 ADINTEN2  : 1;
__REG32 ADINTEN3  : 1;
__REG32 ADINTEN4  : 1;
__REG32 ADINTEN5  : 1;
__REG32 ADINTEN6  : 1;
__REG32 ADINTEN7  : 1;
__REG32 ADGINTEN  : 1;
__REG32           :23;
} __adinten_bits;

/* A/D Data Register */
typedef struct{
__REG32         : 6;
__REG32 RESULT  :10;
__REG32         :14;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __addr_bits;

/* TIMER0 Interrupt Register */
typedef struct{
__REG32 MR0INT  : 1;
__REG32 MR1INT  : 1;
__REG32 MR2INT  : 1;
__REG32 MR3INT  : 1;
__REG32 CR0INT  : 1;
__REG32 CR1INT  : 1;
__REG32 CR2INT  : 1;
__REG32         :25;
} __ir0_bits;

/* TIMER1 Interrupt Register */
typedef struct{
__REG32 MR0INT  : 1;
__REG32 MR1INT  : 1;
__REG32 MR2INT  : 1;
__REG32 MR3INT  : 1;
__REG32 CR0INT  : 1;
__REG32 CR1INT  : 1;
__REG32 CR2INT  : 1;
__REG32 CR3INT  : 1;
__REG32         :24;
} __ir1_bits;

/* TIMER3 Interrupt Register */
typedef struct{
__REG32 MR0INT  : 1;
__REG32 MR1INT  : 1;
__REG32 MR2INT  : 1;
__REG32 MR3INT  : 1;
__REG32         :28;
} __ir3_bits;

/* TIMER Control Register */
typedef struct{
__REG32 CE  : 1;
__REG32 CR  : 1;
__REG32     :30;
} __tcr_bits;

/* TIMER Count Control Register */
typedef struct{
__REG32 TM   : 2;
__REG32 CIS  : 2;
__REG32      :28;
} __tctcr_bits;

/* TIMER Match Control Register */
typedef struct{
__REG32 MR0INT   : 1;
__REG32 MR0RES   : 1;
__REG32 MR0STOP  : 1;
__REG32 MR1INT   : 1;
__REG32 MR1RES   : 1;
__REG32 MR1STOP  : 1;
__REG32 MR2INT   : 1;
__REG32 MR2RES   : 1;
__REG32 MR2STOP  : 1;
__REG32 MR3INT   : 1;
__REG32 MR3RES   : 1;
__REG32 MR3STOP  : 1;
__REG32          :20;
} __mcr_bits;

/* TIMER0 Capture Control Register */
typedef struct{
__REG32 CAP0RE   : 1;
__REG32 CAP0FE   : 1;
__REG32 CAP0INT  : 1;
__REG32 CAP1RE   : 1;
__REG32 CAP1FE   : 1;
__REG32 CAP1INT  : 1;
__REG32 CAP2RE   : 1;
__REG32 CAP2FE   : 1;
__REG32 CAP2INT  : 1;
__REG32          :23;
} __ccr0_bits;

/* TIMER1 Capture Control Register */
typedef struct{
__REG32 CAP0RE   : 1;
__REG32 CAP0FE   : 1;
__REG32 CAP0INT  : 1;
__REG32 CAP1RE   : 1;
__REG32 CAP1FE   : 1;
__REG32 CAP1INT  : 1;
__REG32 CAP2RE   : 1;
__REG32 CAP2FE   : 1;
__REG32 CAP2INT  : 1;
__REG32 CAP3RE   : 1;
__REG32 CAP3FE   : 1;
__REG32 CAP3INT  : 1;
__REG32          :20;
} __ccr1_bits;

/* TIMER External Match Register */
typedef struct{
__REG32 EM0   : 1;
__REG32 EM1   : 1;
__REG32 EM2   : 1;
__REG32 EM3   : 1;
__REG32 EMC0  : 2;
__REG32 EMC1  : 2;
__REG32 EMC2  : 2;
__REG32 EMC3  : 2;
__REG32       :20;
} __emr_bits;

/* TIMER PWM Control Register */
typedef struct{
__REG32 PWM0ENA  : 1;
__REG32 PWM1ENA  : 1;
__REG32 PWM2ENA  : 1;
__REG32 PWM3ENA  : 1;
__REG32          :28;
} __tpwrcon_bits;

/* RTC Interrupt Location Register */
typedef struct{
__REG32 RTCCIF  : 1;
__REG32 RTCALF  : 1;
__REG32         :30;
} __ilr_bits;

/* RTC Clock Tick Counter Register */
typedef struct{
__REG32 COUNTER  :16;
__REG32          :16;
} __ctc_bits;

/* RTC Clock Control Register */
typedef struct{
__REG32 CLKEN   : 1;
__REG32 CTCRST  : 1;
__REG32 CTTEST  : 2;
__REG32 CLKSRC  : 1;
__REG32         :27;
} __rtcccr_bits;

/* RTC Counter Increment Interrupt Register */
typedef struct{
__REG32 IMSEC   : 1;
__REG32 IMMIN   : 1;
__REG32 IMHOUR  : 1;
__REG32 IMDOM   : 1;
__REG32 IMDOW   : 1;
__REG32 IMDOY   : 1;
__REG32 IMMON   : 1;
__REG32 IMYEAR  : 1;
__REG32         :24;
} __ciir_bits;

/* RTC Alarm Mask Register */
typedef struct{
__REG32 AMRSEC   : 1;
__REG32 AMRMIN   : 1;
__REG32 AMRHOUR  : 1;
__REG32 AMRDOM   : 1;
__REG32 AMRDOW   : 1;
__REG32 AMRDOY   : 1;
__REG32 AMRMON   : 1;
__REG32 AMRYEAR  : 1;
__REG32          :24;
} __amr_bits;

/* RTC Consolidated Time Register 0 */
typedef struct{
__REG32 SEC   : 6;
__REG32       : 2;
__REG32 MIN   : 6;
__REG32       : 2;
__REG32 HOUR  : 5;
__REG32       : 3;
__REG32 DOW   : 3;
__REG32       : 5;
} __ctime0_bits;

/* RTC Consolidated Time Register 1 */
typedef struct{
__REG32 DOM   : 5;
__REG32       : 3;
__REG32 MON   : 4;
__REG32       : 4;
__REG32 YEAR  :12;
__REG32       : 4;
} __ctime1_bits;

/* RTC Consolidated Time Register 2 */
typedef struct{
__REG32 DOY  :12;
__REG32      :20;
} __ctime2_bits;

/* RTC Second Register */
typedef struct{
__REG32 SEC  : 6;
__REG32      :26;
} __sec_bits;

/* RTC Minute Register */
typedef struct{
__REG32 MIN  : 6;
__REG32      :26;
} __min_bits;

/* RTC Hour Register */
typedef struct{
__REG32 HOUR  : 5;
__REG32       :27;
} __hour_bits;

/* RTC Day Of Month Register */
typedef struct{
__REG32 DOM  : 5;
__REG32      :27;
} __dom_bits;

/* RTC Day Of Week Register */
typedef struct{
__REG32 DOW  : 3;
__REG32      :29;
} __dow_bits;

/* RTC Day Of Year Register */
typedef struct{
__REG32 DOY  : 9;
__REG32      :23;
} __doy_bits;

/* RTC Month Register */
typedef struct{
__REG32 MON  : 4;
__REG32      :28;
} __month_bits;

/* RTC Year Register */
typedef struct{
__REG32 YEAR  :12;
__REG32       :20;
} __year_bits;

/* RTC Prescaler Value, Integer Portion Register */
typedef struct{
__REG32 VALUE  :13;
__REG32        :19;
} __preint_bits;

/* RTC Prescaler Value, Fractional Portion Register */
typedef struct{
__REG32 VALUE  :15;
__REG32        :17;
} __prefrac_bits;

/* Watchdog Mode Register */
typedef struct{
__REG32 WDEN     : 1;
__REG32 WDRESET  : 1;
__REG32 WDTOF    : 1;
__REG32 WDINT    : 1;
__REG32          :28;
} __wdmod_bits;

/* Watchdog Feed Register */
typedef struct{
__REG32 FEED  : 8;
__REG32       :24;
} __wdfeed_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Common declarations  ****************************************************/

/***************************************************************************
 **
 ** System control block
 **
 ***************************************************************************/
__IO_REG32_BIT(EXTINT,          0xE01FC140,__READ_WRITE,__extint_bits);
__IO_REG32_BIT(EXTWAKE,         0xE01FC144,__READ_WRITE,__extwake_bits);
__IO_REG32_BIT(EXTMODE,         0xE01FC148,__READ_WRITE,__extmode_bits);
__IO_REG32_BIT(EXTPOLAR,        0xE01FC14C,__READ_WRITE,__extpol_bits);
__IO_REG32_BIT(SCS,             0xE01FC1A0,__READ_WRITE,__scs_bits);
__IO_REG32_BIT(MEMMAP,          0xE01FC040,__READ_WRITE,__memmap_bits);
__IO_REG32_BIT(PLLCON,          0xE01FC080,__READ_WRITE,__pllcon_bits);
__IO_REG32_BIT(PLLCFG,          0xE01FC084,__READ_WRITE,__pllcfg_bits);
__IO_REG32_BIT(PLLSTAT,         0xE01FC088,__READ      ,__pllstat_bits);
__IO_REG32_BIT(PLLFEED,         0xE01FC08C,__WRITE     ,__pllfeed_bits);
__IO_REG32_BIT(PCON,            0xE01FC0C0,__READ_WRITE,__pcon_bits);
__IO_REG32_BIT(PCONP,           0xE01FC0C4,__READ_WRITE,__pconp_bits);
__IO_REG32_BIT(RSIR,            0xE01FC180,__READ_WRITE,__rsir_bits);
__IO_REG32(    CSPR,            0xE01FC184,__READ);
__IO_REG32_BIT(APBDIV,          0xE01FC100,__READ_WRITE,__apbdiv_bits);
__IO_REG32_BIT(MAMCR,           0xE01FC000,__READ_WRITE,__mamcr_bits);
__IO_REG32_BIT(MAMTIM,          0xE01FC004,__READ_WRITE,__mamtim_bits);

/***************************************************************************
 **
 ** VIC
 **
 ***************************************************************************/
__IO_REG32_BIT(VICIRQStatus,    0xFFFFF000,__READ      ,__vicint_bits);
__IO_REG32_BIT(VICFIQStatus,    0xFFFFF004,__READ      ,__vicint_bits);
__IO_REG32_BIT(VICRawIntr,      0xFFFFF008,__READ      ,__vicint_bits);
__IO_REG32_BIT(VICIntSelect,    0xFFFFF00C,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(VICIntEnable,    0xFFFFF010,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(VICIntEnClear,   0xFFFFF014,__WRITE     ,__vicint_bits);
__IO_REG32_BIT(VICSoftInt,      0xFFFFF018,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(VICSoftIntClear, 0xFFFFF01C,__WRITE     ,__vicint_bits);
__IO_REG32_BIT(VICProtection,   0xFFFFF020,__READ_WRITE,__vicprotection_bits);
__IO_REG32(    VICVectAddr,     0xFFFFF030,__READ_WRITE);
__IO_REG32(    VICDefVectAddr,  0xFFFFF034,__READ_WRITE);
__IO_REG32(    VICVectAddr0,    0xFFFFF100,__READ_WRITE);
__IO_REG32(    VICVectAddr1,    0xFFFFF104,__READ_WRITE);
__IO_REG32(    VICVectAddr2,    0xFFFFF108,__READ_WRITE);
__IO_REG32(    VICVectAddr3,    0xFFFFF10C,__READ_WRITE);
__IO_REG32(    VICVectAddr4,    0xFFFFF110,__READ_WRITE);
__IO_REG32(    VICVectAddr5,    0xFFFFF114,__READ_WRITE);
__IO_REG32(    VICVectAddr6,    0xFFFFF118,__READ_WRITE);
__IO_REG32(    VICVectAddr7,    0xFFFFF11C,__READ_WRITE);
__IO_REG32(    VICVectAddr8,    0xFFFFF120,__READ_WRITE);
__IO_REG32(    VICVectAddr9,    0xFFFFF124,__READ_WRITE);
__IO_REG32(    VICVectAddr10,   0xFFFFF128,__READ_WRITE);
__IO_REG32(    VICVectAddr11,   0xFFFFF12C,__READ_WRITE);
__IO_REG32(    VICVectAddr12,   0xFFFFF130,__READ_WRITE);
__IO_REG32(    VICVectAddr13,   0xFFFFF134,__READ_WRITE);
__IO_REG32(    VICVectAddr14,   0xFFFFF138,__READ_WRITE);
__IO_REG32(    VICVectAddr15,   0xFFFFF13C,__READ_WRITE);
__IO_REG32_BIT(VICVectCntl0,    0xFFFFF200,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl1,    0xFFFFF204,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl2,    0xFFFFF208,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl3,    0xFFFFF20C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl4,    0xFFFFF210,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl5,    0xFFFFF214,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl6,    0xFFFFF218,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl7,    0xFFFFF21C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl8,    0xFFFFF220,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl9,    0xFFFFF224,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl10,   0xFFFFF228,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl11,   0xFFFFF22C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl12,   0xFFFFF230,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl13,   0xFFFFF234,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl14,   0xFFFFF238,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl15,   0xFFFFF23C,__READ_WRITE,__vicvectcntl_bits);

/***************************************************************************
 **
 ** Pin connect block
 **
 ***************************************************************************/
__IO_REG32_BIT(PINSEL0,         0xE002C000,__READ_WRITE,__pinsel0_bits);
__IO_REG32_BIT(PINSEL1,         0xE002C004,__READ_WRITE,__pinsel1_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(IOPIN,           0xE0028000,__READ      ,__gpio_bits);
__IO_REG32_BIT(IOSET,           0xE0028004,__READ_WRITE,__gpio_bits);
__IO_REG32_BIT(IODIR,           0xE0028008,__READ_WRITE,__gpio_bits);
__IO_REG32_BIT(IOCLR,           0xE002800C,__WRITE     ,__gpio_bits);
__IO_REG32_BIT(FIODIR,          0x3FFFC000,__READ_WRITE,__fgpio_bits);
#define FIODIR0           FIODIR_bit.__byte0
#define FIODIR0_bit       FIODIR_bit.__byte0_bit
#define FIODIR1           FIODIR_bit.__byte1
#define FIODIR1_bit       FIODIR_bit.__byte1_bit
#define FIODIR2           FIODIR_bit.__byte2
#define FIODIR2_bit       FIODIR_bit.__byte2_bit
#define FIODIR3           FIODIR_bit.__byte3
#define FIODIR3_bit       FIODIR_bit.__byte3_bit
#define FIODIRL           FIODIR_bit.__shortl
#define FIODIRL_bit       FIODIR_bit.__shortl_bit
#define FIODIRU           FIODIR_bit.__shortu
#define FIODIRU_bit       FIODIR_bit.__shortu_bit
__IO_REG32_BIT(FIOMASK,         0x3FFFC010,__READ_WRITE,__fgpio_bits);
#define FIOMASK0          FIOMASK_bit.__byte0
#define FIOMASK0_bit      FIOMASK_bit.__byte0_bit
#define FIOMASK1          FIOMASK_bit.__byte1
#define FIOMASK1_bit      FIOMASK_bit.__byte1_bit
#define FIOMASK2          FIOMASK_bit.__byte2
#define FIOMASK2_bit      FIOMASK_bit.__byte2_bit
#define FIOMASK3          FIOMASK_bit.__byte3
#define FIOMASK3_bit      FIOMASK_bit.__byte3_bit
#define FIOMASKL          FIOMASK_bit.__shortl
#define FIOMASKL_bit      FIOMASK_bit.__shortl_bit
#define FIOMASKU          FIOMASK_bit.__shortu
#define FIOMASKU_bit      FIOMASK_bit.__shortu_bit
__IO_REG32_BIT(FIOPIN,          0x3FFFC014,__READ_WRITE,__fgpio_bits);
#define FIOPIN0           FIOPIN_bit.__byte0
#define FIOPIN0_bit       FIOPIN_bit.__byte0_bit
#define FIOPIN1           FIOPIN_bit.__byte1
#define FIOPIN1_bit       FIOPIN_bit.__byte1_bit
#define FIOPIN2           FIOPIN_bit.__byte2
#define FIOPIN2_bit       FIOPIN_bit.__byte2_bit
#define FIOPIN3           FIOPIN_bit.__byte3
#define FIOPIN3_bit       FIOPIN_bit.__byte3_bit
#define FIOPINL           FIOPIN_bit.__shortl
#define FIOPINL_bit       FIOPIN_bit.__shortl_bit
#define FIOPINU           FIOPIN_bit.__shortu
#define FIOPINU_bit       FIOPIN_bit.__shortu_bit
__IO_REG32_BIT(FIOSET,          0x3FFFC018,__READ_WRITE,__fgpio_bits);
#define FIOSET0           FIOSET_bit.__byte0
#define FIOSET0_bit       FIOSET_bit.__byte0_bit
#define FIOSET1           FIOSET_bit.__byte1
#define FIOSET1_bit       FIOSET_bit.__byte1_bit
#define FIOSET2           FIOSET_bit.__byte2
#define FIOSET2_bit       FIOSET_bit.__byte2_bit
#define FIOSET3           FIOSET_bit.__byte3
#define FIOSET3_bit       FIOSET_bit.__byte3_bit
#define FIOSETL           FIOSET_bit.__shortl
#define FIOSETL_bit       FIOSET_bit.__shortl_bit
#define FIOSETU           FIOSET_bit.__shortu
#define FIOSETU_bit       FIOSET_bit.__shortu_bit
__IO_REG32_BIT(FIOCLR,          0x3FFFC01C,__WRITE     ,__fgpio_bits);
#define FIOCLR0           FIOCLR_bit.__byte0
#define FIOCLR0_bit       FIOCLR_bit.__byte0_bit
#define FIOCLR1           FIOCLR_bit.__byte1
#define FIOCLR1_bit       FIOCLR_bit.__byte1_bit
#define FIOCLR2           FIOCLR_bit.__byte2
#define FIOCLR2_bit       FIOCLR_bit.__byte2_bit
#define FIOCLR3           FIOCLR_bit.__byte3
#define FIOCLR3_bit       FIOCLR_bit.__byte3_bit
#define FIOCLRL           FIOCLR_bit.__shortl
#define FIOCLRL_bit       FIOCLR_bit.__shortl_bit
#define FIOCLRU           FIOCLR_bit.__shortu
#define FIOCLRU_bit       FIOCLR_bit.__shortu_bit

/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/
/* U0DLL, U0RBR and U0THR share the same address */
__IO_REG8(     U0RBRTHR,        0xE000C000,__READ_WRITE);
#define U0DLL  U0RBRTHR
#define U0RBR  U0RBRTHR
#define U0THR  U0RBRTHR

/* U0DLM and U0IER share the same address */
__IO_REG32_BIT(U0IER,           0xE000C004,__READ_WRITE,__uartier0_bits);
#define U0DLM  U0IER

/* U0FCR and U0IIR share the same address */
__IO_REG32_BIT(U0FCR,           0xE000C008,__READ_WRITE,__uartfcriir_bits);
#define U0IIR_bit  U0FCR_bit
#define U0IIR      U0FCR

__IO_REG8_BIT( U0LCR,           0xE000C00C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT( U0LSR,           0xE000C014,__READ      ,__uartlsr_bits);
__IO_REG8(     U0SCR,           0xE000C01C,__READ_WRITE);
__IO_REG32_BIT(U0ACR,           0xE000C020,__READ_WRITE,__uartacr_bits);
__IO_REG32_BIT(U0FDR,           0xE000C028,__READ_WRITE,__uartfdr_bits);
__IO_REG8_BIT( U0TER,           0xE000C030,__READ_WRITE,__uartter_bits);

/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
/* U1DLL, U1RBR and U1THR share the same address */
__IO_REG8(     U1RBRTHR,        0xE0010000,__READ_WRITE);
#define U1DLL  U1RBRTHR
#define U1RBR  U1RBRTHR
#define U1THR  U1RBRTHR

/* U1DLM and U1IER share the same address */
__IO_REG32_BIT(U1IER,           0xE0010004,__READ_WRITE,__uartier1_bits);
#define U1DLM  U1IER

/* U1FCR and U1IIR share the same address */
__IO_REG32_BIT(U1FCR,           0xE0010008,__READ_WRITE,__uartfcriir_bits);
#define U1IIR_bit  U1FCR_bit
#define U1IIR      U1FCR

__IO_REG8_BIT( U1LCR,           0xE001000C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT( U1MCR,           0xE0010010,__READ_WRITE,__uartmcr_bits);
__IO_REG8_BIT( U1LSR,           0xE0010014,__READ      ,__uartlsr_bits);
__IO_REG8_BIT( U1MSR,           0xE0010018,__READ      ,__uartmsr_bits);
__IO_REG8(     U1SCR,           0xE001001C,__READ_WRITE);
__IO_REG32_BIT(U1ACR,           0xE001C020,__READ_WRITE,__uartacr_bits);
__IO_REG32_BIT(U1FDR,           0xE001C028,__READ_WRITE,__uartfdr_bits);
__IO_REG8_BIT( U1TER,           0xE001C030,__READ_WRITE,__uartter_bits);

/***************************************************************************
 **
 ** I2C0
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C0ONSET,       0xE001C000,__READ_WRITE,__i2conset_bits);
__IO_REG32_BIT(I2C0STAT,        0xE001C004,__READ      ,__i2stat_bits);
__IO_REG32_BIT(I2C0DAT,         0xE001C008,__READ_WRITE,__i2dat_bits);
__IO_REG32_BIT(I2C0ADR,         0xE001C00C,__READ_WRITE,__i2adr_bits);
__IO_REG32_BIT(I2C0SCLH,        0xE001C010,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(I2C0SCLL,        0xE001C014,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(I2C0CONCLR,      0xE001C018,__WRITE     ,__i2conclr_bits);

/***************************************************************************
 **
 ** I2C1
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C1ONSET,       0xE005C000,__READ_WRITE,__i2conset_bits);
__IO_REG32_BIT(I2C1STAT,        0xE005C004,__READ      ,__i2stat_bits);
__IO_REG32_BIT(I2C1DAT,         0xE005C008,__READ_WRITE,__i2dat_bits);
__IO_REG32_BIT(I2C1ADR,         0xE005C00C,__READ_WRITE,__i2adr_bits);
__IO_REG32_BIT(I2C1SCLH,        0xE005C010,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(I2C1SCLL,        0xE005C014,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(I2C1CONCLR,      0xE005C018,__WRITE     ,__i2conclr_bits);

/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(S0SPCR,          0xE0020000,__READ_WRITE,__spcr_bits);
__IO_REG32_BIT(S0SPSR,          0xE0020004,__READ      ,__spsr_bits);
__IO_REG32_BIT(S0SPDR,          0xE0020008,__READ_WRITE,__spdr_bits);
__IO_REG32_BIT(S0SPCCR,         0xE002000C,__READ_WRITE,__spccr_bits);
__IO_REG32_BIT(S0SPINT,         0xE002001C,__READ_WRITE,__spint_bits);

/***************************************************************************
 **
 ** SSP
 **
 ***************************************************************************/
__IO_REG32_BIT(SSPCR0,          0xE0068000,__READ_WRITE,__sspcr0_bits);
__IO_REG32_BIT(SSPCR1,          0xE0068004,__READ_WRITE,__sspcr1_bits);
__IO_REG32_BIT(SSPDR,           0xE0068008,__READ_WRITE,__sspdr_bits);
__IO_REG32_BIT(SSPSR,           0xE006800C,__READ      ,__sspsr_bits);
__IO_REG32_BIT(SSPCPSR,         0xE0068010,__READ_WRITE,__sspcpsr_bits);
__IO_REG32_BIT(SSPIMSC,         0xE0068014,__READ_WRITE,__sspimsc_bits);
__IO_REG32_BIT(SSPRIS,          0xE0068018,__READ_WRITE,__sspris_bits);
__IO_REG32_BIT(SSPMIS,          0xE006801C,__READ      ,__sspmis_bits);
__IO_REG32_BIT(SSPICR,          0xE0068020,__WRITE     ,__sspicr_bits);

/***************************************************************************
 **
 ** A/D Converters
 **
 ***************************************************************************/
__IO_REG32_BIT(AD0CR,           0xE0034000,__READ_WRITE,__adcr_bits);
__IO_REG32_BIT(AD0GDR,          0xE0034004,__READ_WRITE,__adgdr_bits);
__IO_REG32_BIT(ADINTEN,         0xE003400C,__READ_WRITE,__adinten_bits);
__IO_REG32_BIT(ADDR0,           0xE0034010,__READ      ,__addr_bits);
__IO_REG32_BIT(ADDR1,           0xE0034014,__READ      ,__addr_bits);
__IO_REG32_BIT(ADDR2,           0xE0034018,__READ      ,__addr_bits);
__IO_REG32_BIT(ADDR3,           0xE003401C,__READ      ,__addr_bits);
__IO_REG32_BIT(ADDR4,           0xE0034020,__READ      ,__addr_bits);
__IO_REG32_BIT(ADDR5,           0xE0034024,__READ      ,__addr_bits);
__IO_REG32_BIT(ADDR6,           0xE0034028,__READ      ,__addr_bits);
__IO_REG32_BIT(ADDR7,           0xE003402C,__READ      ,__addr_bits);
__IO_REG32_BIT(ADSTAT,          0xE0034030,__READ      ,__adstat_bits);

/***************************************************************************
 **
 ** TIMER0
 **
 ***************************************************************************/
__IO_REG32_BIT(T0IR,            0xE0004000,__READ_WRITE,__ir0_bits);
__IO_REG32_BIT(T0TCR,           0xE0004004,__READ_WRITE,__tcr_bits);
__IO_REG32(    T0TC,            0xE0004008,__READ_WRITE);
__IO_REG32(    T0PR,            0xE000400c,__READ_WRITE);
__IO_REG32(    T0PC,            0xE0004010,__READ_WRITE);
__IO_REG32_BIT(T0MCR,           0xE0004014,__READ_WRITE,__mcr_bits);
__IO_REG32(    T0MR0,           0xE0004018,__READ_WRITE);
__IO_REG32(    T0MR1,           0xE000401C,__READ_WRITE);
__IO_REG32(    T0MR2,           0xE0004020,__READ_WRITE);
__IO_REG32(    T0MR3,           0xE0004024,__READ_WRITE);
__IO_REG32_BIT(T0CCR,           0xE0004028,__READ_WRITE,__ccr0_bits);
__IO_REG32(    T0CR0,           0xE000402C,__READ      );
__IO_REG32(    T0CR1,           0xE0004030,__READ      );
__IO_REG32(    T0CR2,           0xE0004034,__READ      );
__IO_REG32_BIT(T0EMR,           0xE000403c,__READ_WRITE,__emr_bits);
__IO_REG32_BIT(T0CTCR,          0xE0004070,__READ_WRITE,__tctcr_bits);
__IO_REG32_BIT(T0PWMCON,        0xE0004074,__READ_WRITE,__tpwrcon_bits);

/***************************************************************************
 **
 ** TIMER1
 **
 ***************************************************************************/
__IO_REG32_BIT(T1IR,            0xE0008000,__READ_WRITE,__ir1_bits);
__IO_REG32_BIT(T1TCR,           0xE0008004,__READ_WRITE,__tcr_bits);
__IO_REG32(    T1TC,            0xE0008008,__READ_WRITE);
__IO_REG32(    T1PR,            0xE000800c,__READ_WRITE);
__IO_REG32(    T1PC,            0xE0008010,__READ_WRITE);
__IO_REG32_BIT(T1MCR,           0xE0008014,__READ_WRITE,__mcr_bits);
__IO_REG32(    T1MR0,           0xE0008018,__READ_WRITE);
__IO_REG32(    T1MR1,           0xE000801C,__READ_WRITE);
__IO_REG32(    T1MR2,           0xE0008020,__READ_WRITE);
__IO_REG32(    T1MR3,           0xE0008024,__READ_WRITE);
__IO_REG32_BIT(T1CCR,           0xE0008028,__READ_WRITE,__ccr1_bits);
__IO_REG32(    T1CR0,           0xE000802C,__READ      );
__IO_REG32(    T1CR1,           0xE0008030,__READ      );
__IO_REG32(    T1CR2,           0xE0008034,__READ      );
__IO_REG32(    T1CR3,           0xE0008038,__READ      );
__IO_REG32_BIT(T1EMR,           0xE000803c,__READ_WRITE,__emr_bits);
__IO_REG32_BIT(T1CTCR,          0xE0008070,__READ_WRITE,__tctcr_bits);
__IO_REG32_BIT(T1PWMCON,        0xE0008074,__READ_WRITE,__tpwrcon_bits);

/***************************************************************************
 **
 ** TIMER2
 **
 ***************************************************************************/
__IO_REG32_BIT(T2IR,            0xE0070000,__READ_WRITE,__ir0_bits);
__IO_REG32_BIT(T2TCR,           0xE0070004,__READ_WRITE,__tcr_bits);
__IO_REG32(    T2TC,            0xE0070008,__READ_WRITE);
__IO_REG32(    T2PR,            0xE007000c,__READ_WRITE);
__IO_REG32(    T2PC,            0xE0070010,__READ_WRITE);
__IO_REG32_BIT(T2MCR,           0xE0070014,__READ_WRITE,__mcr_bits);
__IO_REG32(    T2MR0,           0xE0070018,__READ_WRITE);
__IO_REG32(    T2MR1,           0xE007001C,__READ_WRITE);
__IO_REG32(    T2MR2,           0xE0070020,__READ_WRITE);
__IO_REG32(    T2MR3,           0xE0070024,__READ_WRITE);
__IO_REG32_BIT(T2CCR,           0xE0070028,__READ_WRITE,__ccr0_bits);
__IO_REG32(    T2CR0,           0xE007002C,__READ      );
__IO_REG32(    T2CR1,           0xE0070030,__READ      );
__IO_REG32(    T2CR2,           0xE0070034,__READ      );
__IO_REG32_BIT(T2EMR,           0xE007003c,__READ_WRITE,__emr_bits);
__IO_REG32_BIT(T2CTCR,          0xE0070070,__READ_WRITE,__tctcr_bits);
__IO_REG32_BIT(T2PWMCON,        0xE0070074,__READ_WRITE,__tpwrcon_bits);

/***************************************************************************
 **
 ** TIMER3
 **
 ***************************************************************************/
__IO_REG32_BIT(T3IR,            0xE0074000,__READ_WRITE,__ir3_bits);
__IO_REG32_BIT(T3TCR,           0xE0074004,__READ_WRITE,__tcr_bits);
__IO_REG32(    T3TC,            0xE0074008,__READ_WRITE);
__IO_REG32(    T3PR,            0xE007400c,__READ_WRITE);
__IO_REG32(    T3PC,            0xE0074010,__READ_WRITE);
__IO_REG32_BIT(T3MCR,           0xE0074014,__READ_WRITE,__mcr_bits);
__IO_REG32(    T3MR0,           0xE0074018,__READ_WRITE);
__IO_REG32(    T3MR1,           0xE007401C,__READ_WRITE);
__IO_REG32(    T3MR2,           0xE0074020,__READ_WRITE);
__IO_REG32(    T3MR3,           0xE0074024,__READ_WRITE);
__IO_REG32_BIT(T3EMR,           0xE007403c,__READ_WRITE,__emr_bits);
__IO_REG32_BIT(T3CTCR,          0xE0074070,__READ_WRITE,__tctcr_bits);
__IO_REG32_BIT(T3PWMCON,        0xE0074074,__READ_WRITE,__tpwrcon_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(ILR,             0xE0024000,__READ_WRITE,__ilr_bits);
__IO_REG32_BIT(CTC,             0xE0024004,__READ      ,__ctc_bits);
__IO_REG32_BIT(CCR,             0xE0024008,__READ_WRITE,__rtcccr_bits);
__IO_REG32_BIT(CIIR,            0xE002400C,__READ_WRITE,__ciir_bits);
__IO_REG32_BIT(AMR,             0xE0024010,__READ_WRITE,__amr_bits);
__IO_REG32_BIT(CTIME0,          0xE0024014,__READ      ,__ctime0_bits);
__IO_REG32_BIT(CTIME1,          0xE0024018,__READ      ,__ctime1_bits);
__IO_REG32_BIT(CTIME2,          0xE002401C,__READ      ,__ctime2_bits);
__IO_REG32_BIT(SEC,             0xE0024020,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(MIN,             0xE0024024,__READ_WRITE,__min_bits);
__IO_REG32_BIT(HOUR,            0xE0024028,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(DOM,             0xE002402C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(DOW,             0xE0024030,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(DOY,             0xE0024034,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(MONTH,           0xE0024038,__READ_WRITE,__month_bits);
__IO_REG32_BIT(YEAR,            0xE002403C,__READ_WRITE,__year_bits);
__IO_REG32_BIT(ALSEC,           0xE0024060,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(ALMIN,           0xE0024064,__READ_WRITE,__min_bits);
__IO_REG32_BIT(ALHOUR,          0xE0024068,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(ALDOM,           0xE002406C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(ALDOW,           0xE0024070,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(ALDOY,           0xE0024074,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(ALMON,           0xE0024078,__READ_WRITE,__month_bits);
__IO_REG32_BIT(ALYEAR,          0xE002407C,__READ_WRITE,__year_bits);
__IO_REG32_BIT(PREINT,          0xE0024080,__READ_WRITE,__preint_bits);
__IO_REG32_BIT(PREFRAC,         0xE0024084,__READ_WRITE,__prefrac_bits);

/***************************************************************************
 **
 ** Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDMOD,           0xE0000000,__READ_WRITE,__wdmod_bits);
__IO_REG32(    WDTC,            0xE0000004,__READ_WRITE);
__IO_REG32_BIT(WDFEED,          0xE0000008,__WRITE     ,__wdfeed_bits);
__IO_REG32(    WDTV,            0xE000000C,__READ      );

/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/
#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  Interrupt vector table
 **
 ***************************************************************************/
#define RESETV          0x00  /* Reset                              */
#define UNDEFV          0x04  /* Undefined instruction              */
#define SWIV            0x08  /* Software interrupt                 */
#define PABORTV         0x0c  /* Prefetch abort                     */
#define DABORTV         0x10  /* Data abort                         */
#define IRQV            0x18  /* Normal interrupt                   */
#define FIQV            0x1c  /* Fast interrupt                     */

/***************************************************************************
 **
 **  VIC Interrupt channels
 **
 ***************************************************************************/
#define VIC_WDT          0    /* Watchdog                           */
#define VIC_DEBUGRX      2    /* Embedded ICE, DbgCommRx            */
#define VIC_DEBUGTX      3    /* Embedded ICE, DbgCommTx            */
#define VIC_TIMER0       4    /* Timer 0 (Match 0-2 Capture 0-2)    */
#define VIC_TIMER1       5    /* Timer 1 (Match 0-3 Capture 0-3)    */
#define VIC_UART0        6    /* UART 0  (RLS, THRE, RDA, CTI)      */
#define VIC_UART1        7    /* UART 1  (RLS, THRE, RDA, CTI, MSI) */
#define VIC_I2C0         9    /* I2C     (SI)                       */
#define VIC_SPI         10    /* SPI     (SPIF, MODF)               */
#define VIC_SSP         11    /* SPI1 (SSP)                         */
#define VIC_PLL         12    /* PLL lock (PLOCK)                   */
#define VIC_RTC         13    /* RTC     (RTCCIF, RTCALF)           */
#define VIC_EINT0       14    /* External interrupt 0 (EINT0)       */
#define VIC_EINT1       15    /* External interrupt 1 (EINT1)       */
#define VIC_EINT2       16    /* External interrupt 2 (EINT2)       */
#define VIC_ADC         18    /* A/D Converter 0 end of conversion  */
#define VIC_I2C1        19    /* I2C     (SI)                       */
#define VIC_TIMER2      26    /* Timer 2 (Match 0-2 Capture 0-2)    */
#define VIC_TIMER3      27    /* Timer 3 (Match 0-3)                */

#endif    /* __IOLPC2102_H */
