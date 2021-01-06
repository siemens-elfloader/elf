/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    NXP LPC2212
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.11.2.1 $
 **                                
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/

#ifndef __IOLPC2212_H
#define __IOLPC2212_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    IOLPC210X SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Bank configuration register */
typedef struct {
  __REG32 IDCY           :4;
  __REG32                :1;
  __REG32 WST1           :5;
  __REG32 RBLE           :1;
  __REG32 WST2           :5;
  __REG32                :8;
  __REG32 BUSERR         :1;
  __REG32 WPERR          :1;
  __REG32 WP             :1;
  __REG32 BM             :1;
  __REG32 MW             :2;
  __REG32 AT             :2;
} __bcfg_bits;

/* External interrupt register */
typedef struct {
  __REG32 EINT0           :1;
  __REG32 EINT1           :1;
  __REG32 EINT2           :1;
  __REG32 EINT3           :1;
  __REG32                 :28;
} __extint_bits;

/* External interrupt wakeup register */
typedef struct {
  __REG32 EXTWAKE0        :1;
  __REG32 EXTWAKE1        :1;
  __REG32 EXTWAKE2        :1;
  __REG32 EXTWAKE3        :1;
  __REG32                 :28;
} __extwake_bits;

/* External interrupt mode register */
typedef struct {
  __REG32 EXTMODE0        :1;
  __REG32 EXTMODE1        :1;
  __REG32 EXTMODE2        :1;
  __REG32 EXTMODE3        :1;
  __REG32                 :28;
} __extmode_bits;

/* External interrupt polarity register */
typedef struct {
  __REG32 EXTPOLAR0        :1;
  __REG32 EXTPOLAR1        :1;
  __REG32 EXTPOLAR2        :1;
  __REG32 EXTPOLAR3        :1;
  __REG32                 :28;
} __extpolar_bits;

/* Memory mapping control register */
typedef struct {
  __REG32 MAP             :2;
  __REG32                 :30;
} __memmap_bits;

/* PLL control register */
typedef struct {
  __REG32 PLLE            :1;
  __REG32 PLLC            :1;
  __REG32                 :30;
} __pllcon_bits;

/* PLL config register */
typedef struct {
  __REG32 MSEL            :5;
  __REG32 PSEL            :2;
  __REG32                 :25;
} __pllcfg_bits;

/* PLL status register */
typedef struct {
  __REG32 MSEL            :5;
  __REG32 PSEL            :2;
  __REG32                 :1;
  __REG32 PLLE            :1;
  __REG32 PLLC            :1;
  __REG32 PLOCK           :1;
  __REG32                 :21;
} __pllstat_bits;

/* PLL feed register */
typedef struct {
  __REG32 FEED            :8;
  __REG32                 :24;
} __pllfeed_bits;

/* Power control register */
typedef struct {
  __REG32 IDL             :1;
  __REG32 PD              :1;
  __REG32                 :30;
} __pcon_bits;

/* Power control for peripherals register */
typedef struct {
  __REG32                 :1;
  __REG32 PCTIM0          :1;
  __REG32 PCTIM1          :1;
  __REG32 PCURT0          :1;
  __REG32 PCURT1          :1;
  __REG32 PCPWM0          :1;
  __REG32                 :1;
  __REG32 PCI2C           :1;
  __REG32 PCSPI0          :1;
  __REG32 PCRTC           :1;
  __REG32 PCSPI1          :1;
  __REG32 PCEMC           :1;
  __REG32 PCAD            :1;
  __REG32                 :19;
} __pconp_bits;

/* VPB divider register */
typedef struct {
  __REG32 VPBDIV          :2;
  __REG32                 :2;
  __REG32 XCLKDIV         :2;
  __REG32                 :26;
} __vpbdiv_bits;

/* Memory accelerator module control register */
typedef struct {
  __REG32 MODECTRL        :2;
  __REG32                 :30;
} __mamcr_bits;

/* Memory accelerator module timing register */
typedef struct {
  __REG32 CYCLES          :3;
  __REG32                 :29;
} __mamtim_bits;


/* VIC Interrupt registers */
typedef struct {
  __REG32 INT0            :1;
  __REG32 INT1            :1;
  __REG32 INT2            :1;
  __REG32 INT3            :1;
  __REG32 INT4            :1;
  __REG32 INT5            :1;
  __REG32 INT6            :1;
  __REG32 INT7            :1;
  __REG32 INT8            :1;
  __REG32 INT9            :1;
  __REG32 INT10           :1;
  __REG32 INT11           :1;
  __REG32 INT12           :1;
  __REG32 INT13           :1;
  __REG32 INT14           :1;
  __REG32 INT15           :1;
  __REG32 INT16           :1;
  __REG32 INT17           :1;
  __REG32 INT18           :1;
  __REG32 INT19           :1;
  __REG32 INT20           :1;
  __REG32 INT21           :1;
  __REG32 INT22           :1;
  __REG32 INT23           :1;
  __REG32 INT24           :1;
  __REG32 INT25           :1;
  __REG32 INT26           :1;
  __REG32 INT27           :1;
  __REG32 INT28           :1;
  __REG32 INT29           :1;
  __REG32 INT30           :1;
  __REG32 INT31           :1;
} __vicint_bits;

/* VIC Vector control registers */
typedef struct {
  __REG32 NUMBER          :5;
  __REG32 ENABLED         :1;
  __REG32                 :26;
} __vicvectcntl_bits;

/* VIC protection enable register */
typedef struct {
  __REG32 PROTECT         :1;
  __REG32                 :31;
} __vicprotection_bits;



/* Pin function select register 0 */
typedef struct {
  __REG32 P0_0            :2;
  __REG32 P0_1            :2;
  __REG32 P0_2            :2;
  __REG32 P0_3            :2;
  __REG32 P0_4            :2;
  __REG32 P0_5            :2;
  __REG32 P0_6            :2;
  __REG32 P0_7            :2;
  __REG32 P0_8            :2;
  __REG32 P0_9            :2;
  __REG32 P0_10           :2;
  __REG32 P0_11           :2;
  __REG32 P0_12           :2;
  __REG32 P0_13           :2;
  __REG32 P0_14           :2;
  __REG32 P0_15           :2;
} __pinsel0_bits;

/* Pin function select register 1 */
typedef struct {
  __REG32 P0_16           :2;
  __REG32 P0_17           :2;
  __REG32 P0_18           :2;
  __REG32 P0_19           :2;
  __REG32 P0_20           :2;
  __REG32 P0_21           :2;
  __REG32 P0_22           :2;
  __REG32 P0_23           :2;
  __REG32 P0_24           :2;
  __REG32 P0_25           :2;
  __REG32 P0_26           :2;
  __REG32 P0_27           :2;
  __REG32 P0_28           :2;
  __REG32 P0_29           :2;
  __REG32 P0_30           :2;
  __REG32 P0_31           :2;
} __pinsel1_bits;

/* Pin function select register 2 */
typedef struct {
  __REG32                 :2;
  __REG32 JTAG            :1;
  __REG32 ETCM            :1;
  __REG32 EXTMEM          :2;
  __REG32 AIN6            :1;
  __REG32 AIN7            :1;
  __REG32 WE              :1;
  __REG32                 :2;
  __REG32 CS1             :1;
  __REG32                 :1;
  __REG32 XCLK            :1;
  __REG32 CS2             :2;
  __REG32 CS3             :2;
  __REG32                 :2;
  __REG32 P2_28_29        :1;
  __REG32 AIN4            :1;
  __REG32 AIN5            :1;
  __REG32 A0              :1;
  __REG32 A1              :1;
  __REG32 ABUS            :3;
  __REG32                 :4;
} __pinsel2_bits;

/* GPIO register 0 */
typedef struct {
  __REG32 P0_0            :1;
  __REG32 P0_1            :1;
  __REG32 P0_2            :1;
  __REG32 P0_3            :1;
  __REG32 P0_4            :1;
  __REG32 P0_5            :1;
  __REG32 P0_6            :1;
  __REG32 P0_7            :1;
  __REG32 P0_8            :1;
  __REG32 P0_9            :1;
  __REG32 P0_10           :1;
  __REG32 P0_11           :1;
  __REG32 P0_12           :1;
  __REG32 P0_13           :1;
  __REG32 P0_14           :1;
  __REG32 P0_15           :1;
  __REG32 P0_16           :1;
  __REG32 P0_17           :1;
  __REG32 P0_18           :1;
  __REG32 P0_19           :1;
  __REG32 P0_20           :1;
  __REG32 P0_21           :1;
  __REG32 P0_22           :1;
  __REG32 P0_23           :1;
  __REG32 P0_24           :1;
  __REG32 P0_25           :1;
  __REG32 P0_26           :1;
  __REG32 P0_27           :1;
  __REG32 P0_28           :1;
  __REG32 P0_29           :1;
  __REG32 P0_30           :1;
  __REG32 P0_31           :1;
} __gpio0_bits;

/* GPIO register 1 */
typedef struct {
  __REG32 P1_0            :1;
  __REG32 P1_1            :1;
  __REG32 P1_2            :1;
  __REG32 P1_3            :1;
  __REG32 P1_4            :1;
  __REG32 P1_5            :1;
  __REG32 P1_6            :1;
  __REG32 P1_7            :1;
  __REG32 P1_8            :1;
  __REG32 P1_9            :1;
  __REG32 P1_10           :1;
  __REG32 P1_11           :1;
  __REG32 P1_12           :1;
  __REG32 P1_13           :1;
  __REG32 P1_14           :1;
  __REG32 P1_15           :1;
  __REG32 P1_16           :1;
  __REG32 P1_17           :1;
  __REG32 P1_18           :1;
  __REG32 P1_19           :1;
  __REG32 P1_20           :1;
  __REG32 P1_21           :1;
  __REG32 P1_22           :1;
  __REG32 P1_23           :1;
  __REG32 P1_24           :1;
  __REG32 P1_25           :1;
  __REG32 P1_26           :1;
  __REG32 P1_27           :1;
  __REG32 P1_28           :1;
  __REG32 P1_29           :1;
  __REG32 P1_30           :1;
  __REG32 P1_31           :1;
} __gpio1_bits;

/* GPIO register 2 */
typedef struct {
  __REG32 P2_0            :1;
  __REG32 P2_1            :1;
  __REG32 P2_2            :1;
  __REG32 P2_3            :1;
  __REG32 P2_4            :1;
  __REG32 P2_5            :1;
  __REG32 P2_6            :1;
  __REG32 P2_7            :1;
  __REG32 P2_8            :1;
  __REG32 P2_9            :1;
  __REG32 P2_10           :1;
  __REG32 P2_11           :1;
  __REG32 P2_12           :1;
  __REG32 P2_13           :1;
  __REG32 P2_14           :1;
  __REG32 P2_15           :1;
  __REG32 P2_16           :1;
  __REG32 P2_17           :1;
  __REG32 P2_18           :1;
  __REG32 P2_19           :1;
  __REG32 P2_20           :1;
  __REG32 P2_21           :1;
  __REG32 P2_22           :1;
  __REG32 P2_23           :1;
  __REG32 P2_24           :1;
  __REG32 P2_25           :1;
  __REG32 P2_26           :1;
  __REG32 P2_27           :1;
  __REG32 P2_28           :1;
  __REG32 P2_29           :1;
  __REG32 P2_30           :1;
  __REG32 P2_31           :1;
} __gpio2_bits;

/* GPIO register 3 */
typedef struct {
  __REG32 P3_0            :1;
  __REG32 P3_1            :1;
  __REG32 P3_2            :1;
  __REG32 P3_3            :1;
  __REG32 P3_4            :1;
  __REG32 P3_5            :1;
  __REG32 P3_6            :1;
  __REG32 P3_7            :1;
  __REG32 P3_8            :1;
  __REG32 P3_9            :1;
  __REG32 P3_10           :1;
  __REG32 P3_11           :1;
  __REG32 P3_12           :1;
  __REG32 P3_13           :1;
  __REG32 P3_14           :1;
  __REG32 P3_15           :1;
  __REG32 P3_16           :1;
  __REG32 P3_17           :1;
  __REG32 P3_18           :1;
  __REG32 P3_19           :1;
  __REG32 P3_20           :1;
  __REG32 P3_21           :1;
  __REG32 P3_22           :1;
  __REG32 P3_23           :1;
  __REG32 P3_24           :1;
  __REG32 P3_25           :1;
  __REG32 P3_26           :1;
  __REG32 P3_27           :1;
  __REG32 P3_28           :1;
  __REG32 P3_29           :1;
  __REG32 P3_30           :1;
  __REG32 P3_31           :1;
} __gpio3_bits;


/* UART interrupt enable register */
typedef struct {
  __REG8 RDAIE            :1;
  __REG8 THREIE           :1;
  __REG8 RXLSIE           :1;
  __REG8                  :5;
} __uartier0_bits;


/* UART interrupt enable register */
typedef struct {
  __REG8 RDAIE            :1;
  __REG8 THREIE           :1;
  __REG8 RXLSIE           :1;
  __REG8 MSIE             :1;
  __REG8                  :4;
} __uartier1_bits;

/* UART interrupt identification register and fifo control register */
typedef union {
  //UxIIR
  struct {
    __REG8 IP             :1;
    __REG8 IID            :3;
    __REG8                :2;
    __REG8 IIRFE          :2;
  };
  //UxFCR
  struct {
    __REG8 FCRFE          :1;
    __REG8 RFR            :1;
    __REG8 TFR            :1;
    __REG8                :3;
    __REG8 RTLS           :2;
  };
} __uartfcriir_bits;

/* UART line control register */
typedef struct {
  __REG8 WLS              :2;
  __REG8 SBS              :1;
  __REG8 PE               :1;
  __REG8 PS               :2;
  __REG8 BC               :1;
  __REG8 DLAB             :1;
} __uartlcr_bits;

/* UART modem control register */
typedef struct {
  __REG8 DTR              :1;
  __REG8 RTS              :1;
  __REG8                  :2;
  __REG8 LMS              :1;
  __REG8                  :3;
} __uartmcr_bits;

/* UART line status register */
typedef struct {
  __REG8 DR               :1;
  __REG8 OE               :1;
  __REG8 PE               :1;
  __REG8 FE               :1;
  __REG8 BI               :1;
  __REG8 THRE             :1;
  __REG8 TEMT             :1;
  __REG8 RXFE             :1;
} __uartlsr_bits;

/* UART modem status register */
typedef union {
  //U1MSR
  struct {
  __REG8 DCTS             :1;
  __REG8 DDSR             :1;
  __REG8 TERI             :1;
  __REG8 DDCD             :1;
  __REG8 CTS              :1;
  __REG8 DSR              :1;
  __REG8 RI               :1;
  __REG8 DCD              :1;
  };
  //U1MSR
  struct {
  __REG8 MSR0             :1;
  __REG8 MSR1             :1;
  __REG8 MSR2             :1;
  __REG8 MSR3             :1;
  __REG8 MSR4             :1;
  __REG8 MSR5             :1;
  __REG8 MSR6             :1;
  __REG8 MSR7             :1;
  };
} __uartmsr_bits;


/* I2C control set register */
typedef struct {
  __REG32                 :2;
  __REG32 AA              :1;
  __REG32 SI              :1;
  __REG32 STO             :1;
  __REG32 STA             :1;
  __REG32 I2EN            :1;
  __REG32                 :25;
} __i2conset_bits;

/* I2C control clear register */
typedef struct {
  __REG32                 :2;
  __REG32 AAC             :1;
  __REG32 SIC             :1;
  __REG32                 :1;
  __REG32 STAC            :1;
  __REG32 I2ENC           :1;
  __REG32                 :25;
} __i2conclr_bits;

/* I2C status register */
typedef struct {
  __REG32 STATUS          :8;
  __REG32                 :24;
} __i2stat_bits;

/* I2C data register */
typedef struct {
  __REG32 DATA            :8;
  __REG32                 :24;
} __i2dat_bits;

/* I2C slave address register */
typedef struct {
  __REG32 GC              :1;
  __REG32 ADDR            :7;
  __REG32                 :24;
} __i2adr_bits;

/* I2C scl duty cycle register */
typedef struct {
  __REG32 COUNT           :16;
  __REG32                 :16;
} __i2scl_bits;


/* SPI control register */
typedef struct {
  __REG32                 :3;
  __REG32 CPHA            :1;
  __REG32 CPOL            :1;
  __REG32 MSTR            :1;
  __REG32 LSBF            :1;
  __REG32 SPIE            :1;
  __REG32                 :24;
} __spcr_bits;

/* SPI status register */
typedef struct {
  __REG32                 :3;
  __REG32 ABRT            :1;
  __REG32 MODF            :1;
  __REG32 ROVR            :1;
  __REG32 WCOL            :1;
  __REG32 SPIF            :1;
  __REG32                 :24;
} __spsr_bits;

/* SPI data register */
typedef struct {
  __REG32 DATA            :8;
  __REG32                 :24;
} __spdr_bits;

/* SPI clock counter register */
typedef struct {
  __REG32 COUNTER         :8;
  __REG32                 :24;
} __spccr_bits;

/* SPI interrupt register */
typedef struct {
  __REG32 SPIINT          :1;
  __REG32                 :31;
} __spint_bits;

/* TIMER interrupt register */
typedef struct {
  __REG32 MR0INT          :1;
  __REG32 MR1INT          :1;
  __REG32 MR2INT          :1;
  __REG32 MR3INT          :1;
  __REG32 CR0INT          :1;
  __REG32 CR1INT          :1;
  __REG32 CR2INT          :1;
  __REG32 CR3INT          :1;
  __REG32                 :24;
} __ir_bits;

/* TIMER control register */
typedef struct {
  __REG32 CE              :1;
  __REG32 CR              :1;
  __REG32                 :30;
} __tcr_bits;

/* TIMER match control register */
typedef struct {
  __REG32 MR0INT          :1;
  __REG32 MR0RES          :1;
  __REG32 MR0STOP         :1;
  __REG32 MR1INT          :1;
  __REG32 MR1RES          :1;
  __REG32 MR1STOP         :1;
  __REG32 MR2INT          :1;
  __REG32 MR2RES          :1;
  __REG32 MR2STOP         :1;
  __REG32 MR3INT          :1;
  __REG32 MR3RES          :1;
  __REG32 MR3STOP         :1;
  __REG32                 :20;
} __mcr_bits;

/* TIMER0 capture control register */
typedef struct {
  __REG32 CAP0RE          :1;
  __REG32 CAP0FE          :1;
  __REG32 CAP0INT         :1;
  __REG32 CAP1RE          :1;
  __REG32 CAP1FE          :1;
  __REG32 CAP1INT         :1;
  __REG32 CAP2RE          :1;
  __REG32 CAP2FE          :1;
  __REG32 CAP2INT         :1;
  __REG32                 :23;
} __ccr0_bits;

/* TIMER1 capture control register */
typedef struct {
  __REG32 CAP0RE          :1;
  __REG32 CAP0FE          :1;
  __REG32 CAP0INT         :1;
  __REG32 CAP1RE          :1;
  __REG32 CAP1FE          :1;
  __REG32 CAP1INT         :1;
  __REG32 CAP2RE          :1;
  __REG32 CAP2FE          :1;
  __REG32 CAP2INT         :1;
  __REG32 CAP3RE          :1;
  __REG32 CAP3FE          :1;
  __REG32 CAP3INT         :1;
  __REG32                 :20;
} __ccr1_bits;

/* TIMER external match register */
typedef struct {
  __REG32 EM0             :1;
  __REG32 EM1             :1;
  __REG32 EM2             :1;
  __REG32 EM3             :1;
  __REG32 EMC0            :2;
  __REG32 EMC1            :2;
  __REG32 EMC2            :2;
  __REG32 EMC3            :2;
  __REG32                 :20;
} __emr_bits;


/* PWM interrupt register */
typedef struct {
  __REG32 MR0INT          :1;
  __REG32 MR1INT          :1;
  __REG32 MR2INT          :1;
  __REG32 MR3INT          :1;
  __REG32                 :4;  
  __REG32 MR4INT          :1;
  __REG32 MR5INT          :1;
  __REG32 MR6INT          :1;
  __REG32                 :21;
} __pwmir_bits;

/* PWM timer control register */
typedef struct {
  __REG32 CE              :1;
  __REG32 CR              :1;
  __REG32                 :1;
  __REG32 PWMEN           :1;
  __REG32                 :28;
} __pwmtcr_bits;

/* PWM match control register */
typedef struct {
  __REG32 MR0INT          :1;
  __REG32 MR0RES          :1;
  __REG32 MR0STOP         :1;
  __REG32 MR1INT          :1;
  __REG32 MR1RES          :1;
  __REG32 MR1STOP         :1;
  __REG32 MR2INT          :1;
  __REG32 MR2RES          :1;
  __REG32 MR2STOP         :1;
  __REG32 MR3INT          :1;
  __REG32 MR3RES          :1;
  __REG32 MR3STOP         :1;
  __REG32 MR4INT          :1;
  __REG32 MR4RES          :1;
  __REG32 MR4STOP         :1;
  __REG32 MR5INT          :1;
  __REG32 MR5RES          :1;
  __REG32 MR5STOP         :1;
  __REG32 MR6INT          :1;
  __REG32 MR6RES          :1;
  __REG32 MR6STOP         :1;
  __REG32                 :11;
} __pwmmcr_bits;


/* PWM  control register */
typedef struct {
  __REG32                 :1;
  __REG32 SEL1            :1;
  __REG32 SEL2            :1;
  __REG32 SEL3            :1;
  __REG32 SEL4            :1;
  __REG32 SEL5            :1;
  __REG32 SEL6            :1;
  __REG32                 :2;
  __REG32 ENA1            :1;
  __REG32 ENA2            :1;
  __REG32 ENA3            :1;
  __REG32 ENA4            :1;
  __REG32 ENA5            :1;
  __REG32 ENA6            :1;
  __REG32                 :17;
} __pwmpcr_bits;

/* PWM latch enable register */
typedef struct {
  __REG32 EM0L            :1;
  __REG32 EM1L            :1;
  __REG32 EM2L            :1;
  __REG32 EM3L            :1;
  __REG32 EM4L            :1;
  __REG32 EM5L            :1;
  __REG32 EM6L            :1;
  __REG32                 :25;
} __pwmler_bits;



/* A/D control register */
typedef struct {
  __REG32 SEL             :8;
  __REG32 CLKDIV          :8;
  __REG32 BURST           :1;
  __REG32 CLKS            :3;
  __REG32                 :1;
  __REG32 PDN             :1;
  __REG32 TEST            :2;
  __REG32 START           :3;
  __REG32 EDGE            :1;
  __REG32                 :4;
} __adcr_bits;

/* A/D data register */
typedef struct {
  __REG32                 :6;
  __REG32 VVDDA           :10;
  __REG32                 :8;
  __REG32 CHN             :3;
  __REG32                 :3;
  __REG32 OVERUN          :1;
  __REG32 DONE            :1;
} __addr_bits;


/* RTC interrupt location register */
typedef struct {
  __REG32 RTCCIF          :1;
  __REG32 RTCALF          :1;
  __REG32                 :30;
} __ilr_bits;

/* RTC clock tick counter register */
typedef struct {
  __REG32                 :1;
  __REG32 COUNTER         :15;
  __REG32                 :16;
} __ctc_bits;

/* RTC clock control register */
typedef struct {
  __REG32 CLKEN           :1;
  __REG32 CTCRST          :1;
  __REG32 CTTEST          :2;
  __REG32                 :28;
} __rtcccr_bits;

/* RTC counter increment interrupt register */
typedef struct {
  __REG32 IMSEC           :1;
  __REG32 IMMIN           :1;
  __REG32 IMHOUR          :1;
  __REG32 IMDOM           :1;
  __REG32 IMDOW           :1;
  __REG32 IMDOY           :1;
  __REG32 IMMON           :1;
  __REG32 IMYEAR          :1;
  __REG32                 :24;
} __ciir_bits;

/* RTC alarm mask register */
typedef struct {
  __REG32 AMRSEC          :1;
  __REG32 AMRMIN          :1;
  __REG32 AMRHOUR         :1;
  __REG32 AMRDOM          :1;
  __REG32 AMRDOW          :1;
  __REG32 AMRDOY          :1;
  __REG32 AMRMON          :1;
  __REG32 AMRYEAR         :1;
  __REG32                 :24;
} __amr_bits;

/* RTC consolidated time register 0 */
typedef struct {
  __REG32 SEC             :6;
  __REG32                 :2;
  __REG32 MIN             :6;
  __REG32                 :2;
  __REG32 HOUR            :5;
  __REG32                 :3;
  __REG32 DOW             :3;
  __REG32                 :5;
} __ctime0_bits;

/* RTC consolidated time register 1 */
typedef struct {
  __REG32 DOM             :5;
  __REG32                 :3;
  __REG32 MON             :4;
  __REG32                 :4;
  __REG32 YEAR            :12;
  __REG32                 :4;
} __ctime1_bits;

/* RTC consolidated time register 2 */
typedef struct {
  __REG32 DOY             :12;
  __REG32                 :20;
} __ctime2_bits;

/* RTC second register */
typedef struct {
  __REG32 SEC             :6;
  __REG32                 :26;
} __sec_bits;

/* RTC minute register */
typedef struct {
  __REG32 MIN             :6;
  __REG32                 :26;
} __min_bits;

/* RTC hour register */
typedef struct {
  __REG32 HOUR            :5;
  __REG32                 :27;
} __hour_bits;

/* RTC day of month register */
typedef struct {
  __REG32 DOM             :5;
  __REG32                 :27;
} __dom_bits;

/* RTC day of week register */
typedef struct {
  __REG32 DOW             :3;
  __REG32                 :29;
} __dow_bits;

/* RTC day of year register */
typedef struct {
  __REG32 DOY             :9;
  __REG32                 :23;
} __doy_bits;

/* RTC month register */
typedef struct {
  __REG32 MON             :4;
  __REG32                 :28;
} __month_bits;

/* RTC year register */
typedef struct {
  __REG32 YEAR            :12;
  __REG32                 :20;
} __year_bits;

/* RTC prescaler value, integer portion register */
typedef struct {
  __REG32 VALUE           :13;
  __REG32                 :19;
} __preint_bits;

/* RTC prescaler value, fractional portion register */
typedef struct {
  __REG32 VALUE           :15;
  __REG32                 :17;
} __prefrac_bits;


/* Watchdog mode register */
typedef struct {
  __REG32 WDEN            :1;
  __REG32 WDRESET         :1;
  __REG32 WDTOF           :1;
  __REG32 WDINT           :1;
  __REG32                 :28;
} __wdmod_bits;

/* Watchdog feed register */
typedef struct {
  __REG32 FEED            :8;
  __REG32                 :24;
} __wdfeed_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Common declarations  ****************************************************/

/***************************************************************************
 **
 ** EMC
 **
 ***************************************************************************/

__IO_REG32_BIT(BCFG0, 0xFFE00000,__READ_WRITE,__bcfg_bits);
__IO_REG32_BIT(BCFG1, 0xFFE00004,__READ_WRITE,__bcfg_bits);
__IO_REG32_BIT(BCFG2, 0xFFE00008,__READ_WRITE,__bcfg_bits);
__IO_REG32_BIT(BCFG3, 0xFFE0000C,__READ_WRITE,__bcfg_bits);

/***************************************************************************
 **
 ** System control block
 **
 ***************************************************************************/
__IO_REG32_BIT(EXTINT, 0xE01FC140,__READ_WRITE,__extint_bits);
__IO_REG32_BIT(EXTWAKE, 0xE01FC144,__READ_WRITE,__extwake_bits);
__IO_REG32_BIT(EXTMODE, 0xE01FC148,__READ_WRITE,__extmode_bits);
__IO_REG32_BIT(EXTPOLAR, 0xE01FC14C,__READ_WRITE,__extpolar_bits);
__IO_REG32_BIT(MEMMAP, 0xE01FC040,__READ_WRITE,__memmap_bits);
__IO_REG32_BIT(PLLCON, 0xE01FC080,__READ_WRITE,__pllcon_bits);
__IO_REG32_BIT(PLLCFG, 0xE01FC084,__READ_WRITE,__pllcfg_bits);
__IO_REG32_BIT(PLLSTAT, 0xE01FC088,__READ,__pllstat_bits);
__IO_REG32_BIT(PLLFEED, 0xE01FC08C,__READ_WRITE,__pllfeed_bits);
__IO_REG32_BIT(PCON, 0xE01FC0C0,__READ_WRITE,__pcon_bits);
__IO_REG32_BIT(PCONP, 0xE01FC0C4,__READ_WRITE,__pconp_bits);
__IO_REG32_BIT(VPBDIV, 0xE01FC100,__READ_WRITE,__vpbdiv_bits);

/***************************************************************************
 **
 ** MAM
 **
 ***************************************************************************/
__IO_REG32_BIT(MAMCR, 0xE01FC000,__READ_WRITE,__mamcr_bits);
__IO_REG32_BIT(MAMTIM, 0xE01FC004,__READ_WRITE,__mamtim_bits);

/***************************************************************************
 **
 ** VIC
 **
 ***************************************************************************/
__IO_REG32_BIT(VICIRQStatus, 0xFFFFF000,__READ,__vicint_bits);
__IO_REG32_BIT(VICFIQStatus, 0xFFFFF004,__READ,__vicint_bits);
__IO_REG32_BIT(VICRawIntr, 0xFFFFF008,__READ,__vicint_bits);
__IO_REG32_BIT(VICIntSelect, 0xFFFFF00C,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(VICIntEnable, 0xFFFFF010,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(VICIntEnClear, 0xFFFFF014,__WRITE,__vicint_bits);
__IO_REG32_BIT(VICSoftInt, 0xFFFFF018,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(VICSoftIntClear, 0xFFFFF01C,__WRITE,__vicint_bits);
__IO_REG32_BIT(VICProtection, 0xFFFFF020,__READ_WRITE,__vicprotection_bits);
__IO_REG32(VICVectAddr, 0xFFFFF030,__READ_WRITE);
__IO_REG32(VICDefVectAddr, 0xFFFFF034,__READ_WRITE);
__IO_REG32(VICVectAddr0, 0xFFFFF100,__READ_WRITE);
__IO_REG32(VICVectAddr1, 0xFFFFF104,__READ_WRITE);
__IO_REG32(VICVectAddr2, 0xFFFFF108,__READ_WRITE);
__IO_REG32(VICVectAddr3, 0xFFFFF10C,__READ_WRITE);
__IO_REG32(VICVectAddr4, 0xFFFFF110,__READ_WRITE);
__IO_REG32(VICVectAddr5, 0xFFFFF114,__READ_WRITE);
__IO_REG32(VICVectAddr6, 0xFFFFF118,__READ_WRITE);
__IO_REG32(VICVectAddr7, 0xFFFFF11C,__READ_WRITE);
__IO_REG32(VICVectAddr8, 0xFFFFF120,__READ_WRITE);
__IO_REG32(VICVectAddr9, 0xFFFFF124,__READ_WRITE);
__IO_REG32(VICVectAddr10, 0xFFFFF128,__READ_WRITE);
__IO_REG32(VICVectAddr11, 0xFFFFF12C,__READ_WRITE);
__IO_REG32(VICVectAddr12, 0xFFFFF130,__READ_WRITE);
__IO_REG32(VICVectAddr13, 0xFFFFF134,__READ_WRITE);
__IO_REG32(VICVectAddr14, 0xFFFFF138,__READ_WRITE);
__IO_REG32(VICVectAddr15, 0xFFFFF13C,__READ_WRITE);
__IO_REG32_BIT(VICVectCntl0, 0xFFFFF200,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl1, 0xFFFFF204,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl2, 0xFFFFF208,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl3, 0xFFFFF20C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl4, 0xFFFFF210,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl5, 0xFFFFF214,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl6, 0xFFFFF218,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl7, 0xFFFFF21C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl8, 0xFFFFF220,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl9, 0xFFFFF224,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl10, 0xFFFFF228,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl11, 0xFFFFF22C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl12, 0xFFFFF230,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl13, 0xFFFFF234,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl14, 0xFFFFF238,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VICVectCntl15, 0xFFFFF23C,__READ_WRITE,__vicvectcntl_bits);

/***************************************************************************
 **
 ** Pin connect block
 **
 ***************************************************************************/
__IO_REG32_BIT(PINSEL0, 0xE002C000,__READ_WRITE,__pinsel0_bits);
__IO_REG32_BIT(PINSEL1, 0xE002C004,__READ_WRITE,__pinsel1_bits);
__IO_REG32_BIT(PINSEL2, 0xE002C014,__READ_WRITE,__pinsel2_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(IO0PIN, 0xE0028000,__READ_WRITE,__gpio0_bits);
__IO_REG32_BIT(IO0SET, 0xE0028004,__READ_WRITE,__gpio0_bits);
__IO_REG32_BIT(IO0DIR, 0xE0028008,__READ_WRITE,__gpio0_bits);
__IO_REG32_BIT(IO0CLR, 0xE002800C,__WRITE,__gpio0_bits);

__IO_REG32_BIT(IO1PIN, 0xE0028010,__READ_WRITE,__gpio1_bits);
__IO_REG32_BIT(IO1SET, 0xE0028014,__READ_WRITE,__gpio1_bits);
__IO_REG32_BIT(IO1DIR, 0xE0028018,__READ_WRITE,__gpio1_bits);
__IO_REG32_BIT(IO1CLR, 0xE002801C,__WRITE,__gpio1_bits);

__IO_REG32_BIT(IO2PIN, 0xE0028020,__READ_WRITE,__gpio2_bits);
__IO_REG32_BIT(IO2SET, 0xE0028024,__READ_WRITE,__gpio2_bits);
__IO_REG32_BIT(IO2DIR, 0xE0028028,__READ_WRITE,__gpio2_bits);
__IO_REG32_BIT(IO2CLR, 0xE002802C,__WRITE,__gpio2_bits);

__IO_REG32_BIT(IO3PIN, 0xE0028030,__READ_WRITE,__gpio3_bits);
__IO_REG32_BIT(IO3SET, 0xE0028034,__READ_WRITE,__gpio3_bits);
__IO_REG32_BIT(IO3DIR, 0xE0028038,__READ_WRITE,__gpio3_bits);
__IO_REG32_BIT(IO3CLR, 0xE002803C,__WRITE,__gpio3_bits);


/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/

/* U0DLL, U0RBR and U0THR share the same address */
__IO_REG8(U0RBRTHR, 0xE000C000,__READ_WRITE);
#define U0DLL U0RBRTHR
#define U0RBR U0RBRTHR
#define U0THR U0RBRTHR

/* U0DLM and U0IER share the same address */
__IO_REG8_BIT(U0IER, 0xE000C004,__READ_WRITE,__uartier0_bits);
#define U0DLM     U0IER

/* U0FCR and U0IIR share the same address */
__IO_REG8_BIT(U0FCR, 0xE000C008,__READ_WRITE,__uartfcriir_bits);
#define U0IIR_bit  U0FCR_bit
#define U0IIR       U0FCR

__IO_REG8_BIT(U0LCR, 0xE000C00C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(U0LSR, 0xE000C014,__READ_WRITE,__uartlsr_bits);
__IO_REG8(U0SCR, 0xE000C01C,__READ_WRITE);


/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/

/* U1DLL, U1RBR and U1THR share the same address */
__IO_REG8(U1RBRTHR, 0xE0010000,__READ_WRITE);
#define U1DLL U1RBRTHR
#define U1RBR U1RBRTHR
#define U1THR U1RBRTHR

/* U1DLM and U1IER share the same address */
__IO_REG8_BIT(U1IER, 0xE0010004,__READ_WRITE,__uartier1_bits);
#define U1DLM      U1IER

/* U1FCR and U1IIR share the same address */
__IO_REG8_BIT(U1FCR, 0xE0010008,__READ_WRITE,__uartfcriir_bits);
#define U1IIR_bit  U1FCR_bit
#define U1IIR      U1FCR

__IO_REG8_BIT(U1MCR, 0xE0010010,__READ_WRITE,__uartmcr_bits);
__IO_REG8_BIT(U1LCR, 0xE001000C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(U1LSR, 0xE0010014,__READ_WRITE,__uartlsr_bits);
__IO_REG8_BIT(U1MSR, 0xE0010018,__READ_WRITE,__uartmsr_bits);
__IO_REG8(U1SCR, 0xE001001C,__READ_WRITE);


/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(I2CONSET, 0xE001C000,__READ_WRITE,__i2conset_bits);
__IO_REG32_BIT(I2STAT, 0xE001C004,__READ,__i2stat_bits);
__IO_REG32_BIT(I2DAT, 0xE001C008,__READ_WRITE,__i2dat_bits);
__IO_REG32_BIT(I2ADR, 0xE001C00C,__READ_WRITE,__i2adr_bits);
__IO_REG32_BIT(I2SCLH, 0xE001C010,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(I2SCLL, 0xE001C014,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(I2CONCLR, 0xE001C018,__WRITE,__i2conclr_bits);


/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(S0SPCR, 0xE0020000,__READ_WRITE,__spcr_bits);
__IO_REG32_BIT(S0SPSR, 0xE0020004,__READ,__spsr_bits);
__IO_REG32_BIT(S0SPDR, 0xE0020008,__READ_WRITE,__spdr_bits);
__IO_REG32_BIT(S0SPCCR, 0xE002000C,__READ_WRITE,__spccr_bits);
__IO_REG32_BIT(S0SPINT, 0xE002001C,__READ_WRITE,__spint_bits);
__IO_REG32_BIT(S1SPCR, 0xE0030000,__READ_WRITE,__spcr_bits);
__IO_REG32_BIT(S1SPSR, 0xE0030004,__READ,__spsr_bits);
__IO_REG32_BIT(S1SPDR, 0xE0030008,__READ_WRITE,__spdr_bits);
__IO_REG32_BIT(S1SPCCR, 0xE003000C,__READ_WRITE,__spccr_bits);
__IO_REG32_BIT(S1SPINT, 0xE003001C,__READ_WRITE,__spint_bits);


/***************************************************************************
 **
 ** TIMER0
 **
 ***************************************************************************/
__IO_REG32_BIT(T0IR, 0xE0004000,__READ_WRITE,__ir_bits);
__IO_REG32_BIT(T0TCR, 0xE0004004,__READ_WRITE,__tcr_bits);
__IO_REG32(T0TC, 0xE0004008,__READ_WRITE);
__IO_REG32(T0PR, 0xE000400c,__READ_WRITE);
__IO_REG32(T0PC, 0xE0004010,__READ_WRITE);
__IO_REG32_BIT(T0MCR, 0xE0004014,__READ_WRITE,__mcr_bits);
__IO_REG32(T0MR0, 0xE0004018,__READ_WRITE);
__IO_REG32(T0MR1, 0xE000401C,__READ_WRITE);
__IO_REG32(T0MR2, 0xE0004020,__READ_WRITE);
__IO_REG32(T0MR3, 0xE0004024,__READ_WRITE);
__IO_REG32_BIT(T0CCR, 0xE0004028,__READ_WRITE,__ccr0_bits);
__IO_REG32(T0CR0, 0xE000402C,__READ);
__IO_REG32(T0CR1, 0xE0004030,__READ);
__IO_REG32(T0CR2, 0xE0004034,__READ);
__IO_REG32(T0CR3, 0xE0004038,__READ);
__IO_REG32_BIT(T0EMR, 0xE000403c,__READ_WRITE,__emr_bits);


/***************************************************************************
 **
 ** TIMER1
 **
 ***************************************************************************/
__IO_REG32_BIT(T1IR, 0xE0008000,__READ_WRITE,__ir_bits);
__IO_REG32_BIT(T1TCR, 0xE0008004,__READ_WRITE,__tcr_bits);
__IO_REG32(T1TC, 0xE0008008,__READ_WRITE);
__IO_REG32(T1PR, 0xE000800c,__READ_WRITE);
__IO_REG32(T1PC, 0xE0008010,__READ_WRITE);
__IO_REG32_BIT(T1MCR, 0xE0008014,__READ_WRITE,__mcr_bits);
__IO_REG32(T1MR0, 0xE0008018,__READ_WRITE);
__IO_REG32(T1MR1, 0xE000801C,__READ_WRITE);
__IO_REG32(T1MR2, 0xE0008020,__READ_WRITE);
__IO_REG32(T1MR3, 0xE0008024,__READ_WRITE);
__IO_REG32_BIT(T1CCR, 0xE0008028,__READ_WRITE,__ccr1_bits);
__IO_REG32(T1CR0, 0xE000802C,__READ);
__IO_REG32(T1CR1, 0xE0008030,__READ);
__IO_REG32(T1CR2, 0xE0008034,__READ);
__IO_REG32(T1CR3, 0xE0008038,__READ);
__IO_REG32_BIT(T1EMR, 0xE000803c,__READ_WRITE,__emr_bits);


/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(PWMIR, 0xE0014000,__READ_WRITE,__pwmir_bits);
__IO_REG32_BIT(PWMTCR, 0xE0014004,__READ_WRITE,__pwmtcr_bits);
__IO_REG32(PWMTC, 0xE0014008,__READ_WRITE);
__IO_REG32(PWMPR, 0xE001400C,__READ_WRITE);
__IO_REG32(PWMPC, 0xE0014010,__READ_WRITE);
__IO_REG32_BIT(PWMMCR, 0xE0014014,__READ_WRITE,__pwmmcr_bits);
__IO_REG32(PWMMR0, 0xE0014018,__READ_WRITE);
__IO_REG32(PWMMR1, 0xE001401C,__READ_WRITE);
__IO_REG32(PWMMR2, 0xE0014020,__READ_WRITE);
__IO_REG32(PWMMR3, 0xE0014024,__READ_WRITE);
__IO_REG32(PWMMR4, 0xE0014040,__READ_WRITE);
__IO_REG32(PWMMR5, 0xE0014044,__READ_WRITE);
__IO_REG32(PWMMR6, 0xE0014048,__READ_WRITE);
__IO_REG32_BIT(PWMPCR, 0xE001404C,__READ_WRITE,__pwmpcr_bits);
__IO_REG32_BIT(PWMLER, 0xE0014050,__READ_WRITE,__pwmler_bits);


/***************************************************************************
 **
 ** A/D Converter
 **
 ***************************************************************************/
__IO_REG32_BIT(ADCR, 0xE0034000,__READ_WRITE,__adcr_bits);
__IO_REG32_BIT(ADDR, 0xE0034004,__READ_WRITE,__addr_bits);


/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(ILR, 0xE0024000,__READ_WRITE,__ilr_bits);
__IO_REG32_BIT(CTC, 0xE0024004,__READ,__ctc_bits);
__IO_REG32_BIT(CCR, 0xE0024008,__READ_WRITE,__rtcccr_bits);
__IO_REG32_BIT(CIIR, 0xE002400C,__READ_WRITE,__ciir_bits);
__IO_REG32_BIT(AMR, 0xE0024010,__READ_WRITE,__amr_bits);
__IO_REG32_BIT(CTIME0, 0xE0024014,__READ,__ctime0_bits);
__IO_REG32_BIT(CTIME1, 0xE0024018,__READ,__ctime1_bits);
__IO_REG32_BIT(CTIME2, 0xE002401C,__READ,__ctime2_bits);
__IO_REG32_BIT(SEC, 0xE0024020,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(MIN, 0xE0024024,__READ_WRITE,__min_bits);
__IO_REG32_BIT(HOUR, 0xE0024028,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(DOM, 0xE002402C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(DOW, 0xE0024030,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(DOY, 0xE0024034,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(MONTH, 0xE0024038,__READ_WRITE,__month_bits);
__IO_REG32_BIT(YEAR, 0xE002403C,__READ_WRITE,__year_bits);
__IO_REG32_BIT(ALSEC, 0xE0024060,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(ALMIN, 0xE0024064,__READ_WRITE,__min_bits);
__IO_REG32_BIT(ALHOUR, 0xE0024068,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(ALDOM, 0xE002406C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(ALDOW, 0xE0024070,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(ALDOY, 0xE0024074,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(ALMON, 0xE0024078,__READ_WRITE,__month_bits);
__IO_REG32_BIT(ALYEAR, 0xE002407C,__READ_WRITE,__year_bits);
__IO_REG32_BIT(PREINT, 0xE0024080,__READ_WRITE,__preint_bits);
__IO_REG32_BIT(PREFRAC, 0xE0024084,__READ_WRITE,__prefrac_bits);


/***************************************************************************
 **
 ** Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDMOD, 0xE0000000,__READ_WRITE,__wdmod_bits);
__IO_REG32(WDTC, 0xE0000004,__READ_WRITE);
__IO_REG32_BIT(WDFEED, 0xE0000008,__WRITE,__wdfeed_bits);
__IO_REG32(WDTV, 0xE000000C,__READ);



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
#define RESETV  0x00  /* Reset                           */
#define UNDEFV  0x04  /* Undefined instruction           */
#define SWIV    0x08  /* Software interrupt              */
#define PABORTV 0x0c  /* Prefetch abort                  */
#define DABORTV 0x10  /* Data abort                      */
#define IRQV    0x18  /* Normal interrupt                */
#define FIQV    0x1c  /* Fast interrupt                  */

/***************************************************************************
 **
 **  VIC Interrupt channels
 **
 ***************************************************************************/
#define VIC_WDT          0  /* Watchdog                           */
#define VIC_SW           1  /* Software interrupts                */
#define VIC_DEBUGRX      2  /* Embedded ICE, DbgCommRx            */
#define VIC_DEBUGTX      3  /* Embedded ICE, DbgCommTx            */
#define VIC_TIMER0       4  /* Timer 0 (Match 0-3 Capture 0-3)    */
#define VIC_TIMER1       5  /* Timer 1 (Match 0-3 Capture 0-3)    */
#define VIC_UART0        6  /* UART 0  (RLS, THRE, RDA, CTI)      */
#define VIC_UART1        7  /* UART 1  (RLS, THRE, RDA, CTI, MSI) */
#define VIC_PWM0         8  /* PWM 0   (Match 0-6 Capture 0-3)    */
#define VIC_I2C          9  /* I2C     (SI)                       */
#define VIC_SPI0        10  /* SPI     (SPIF, MODF)               */
#define VIC_SPI1        11  /* SPI     (SPIF, MODF)               */
#define VIC_PLL         12  /* PLL lock (PLOCK)                   */
#define VIC_RTC         13  /* RTC     (RTCCIF, RTCALF)           */
#define VIC_EINT0       14  /* External interrupt 0 (EINT0)       */
#define VIC_EINT1       15  /* External interrupt 1 (EINT1)       */
#define VIC_EINT2       16  /* External interrupt 2 (EINT2)       */
#define VIC_EINT3       17  /* External interrupt 3 (EINT3)       */
#define VIC_AD          18  /* A/D converter                      */


#endif    /* __IOLPC210X_H */

