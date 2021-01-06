/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    NXP LPC210x
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.4.2.1 $
 **                                
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/

#ifndef __IOLPC210X_H
#define __IOLPC210X_H


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

/* Part configuration register */
typedef struct {
  __REG32 flash           :4;
  __REG32 ram             :4;
  __REG32                 :24;
} __partcfg_bits;


/* VIC Interrupt registers */
typedef struct {
  __REG32 int0            :1;
  __REG32 int1            :1;
  __REG32 int2            :1;
  __REG32 int3            :1;
  __REG32 int4            :1;
  __REG32 int5            :1;
  __REG32 int6            :1;
  __REG32 int7            :1;
  __REG32 int8            :1;
  __REG32 int9            :1;
  __REG32 int10           :1;
  __REG32 int11           :1;
  __REG32 int12           :1;
  __REG32 int13           :1;
  __REG32 int14           :1;
  __REG32 int15           :1;
  __REG32 int16           :1;
  __REG32 int17           :1;
  __REG32 int18           :1;
  __REG32 int19           :1;
  __REG32 int20           :1;
  __REG32 int21           :1;
  __REG32 int22           :1;
  __REG32 int23           :1;
  __REG32 int24           :1;
  __REG32 int25           :1;
  __REG32 int26           :1;
  __REG32 int27           :1;
  __REG32 int28           :1;
  __REG32 int29           :1;
  __REG32 int30           :1;
  __REG32 int31           :1;
} __vicint_bits;

/* VIC Vector control registers */
typedef struct {
  __REG32 number          :5;
  __REG32 enabled         :1;
  __REG32                 :26;
} __vicvectcntl_bits;

/* VIC protection enable register */
typedef struct {
  __REG32 protected_bit   :1;
  __REG32                 :31;
} __vicprotection_bits;


/* MAM statistical status register */
typedef struct {
  __REG32 fcovf           :1;
  __REG32 bcovf           :1;
  __REG32                 :30;
} __mss_bits;

/* MAM statistical control register */
typedef struct {
  __REG32 msrst           :1;
  __REG32 control         :2;
  __REG32                 :29;
} __mscon_bits;


/* Pin function select register 0 */
typedef struct {
  __REG32 p0_0            :2;
  __REG32 p0_1            :2;
  __REG32 p0_2            :2;
  __REG32 p0_3            :2;
  __REG32 p0_4            :2;
  __REG32 p0_5            :2;
  __REG32 p0_6            :2;
  __REG32 p0_7            :2;
  __REG32 p0_8            :2;
  __REG32 p0_9            :2;
  __REG32 p0_10           :2;
  __REG32 p0_11           :2;
  __REG32 p0_12           :2;
  __REG32 p0_13           :2;
  __REG32 p0_14           :2;
  __REG32 p0_15           :2;
} __pinsel0_bits;

/* Pin function select register 1 */
typedef struct {
  __REG32 p0_16           :2;
  __REG32 p0_17           :2;
  __REG32 p0_18           :2;
  __REG32 p0_19           :2;
  __REG32 p0_20           :2;
  __REG32 p0_21           :2;
  __REG32 p0_22           :2;
  __REG32 p0_23           :2;
  __REG32 p0_24           :2;
  __REG32 p0_25           :2;
  __REG32 p0_26           :2;
  __REG32 p0_27           :2;
  __REG32 p0_28           :2;
  __REG32 p0_29           :2;
  __REG32 p0_30           :2;
  __REG32 p0_31           :2;
} __pinsel1_bits;


/* GPIO registers */
typedef struct {
  __REG32 p0_0            :1;
  __REG32 p0_1            :1;
  __REG32 p0_2            :1;
  __REG32 p0_3            :1;
  __REG32 p0_4            :1;
  __REG32 p0_5            :1;
  __REG32 p0_6            :1;
  __REG32 p0_7            :1;
  __REG32 p0_8            :1;
  __REG32 p0_9            :1;
  __REG32 p0_10           :1;
  __REG32 p0_11           :1;
  __REG32 p0_12           :1;
  __REG32 p0_13           :1;
  __REG32 p0_14           :1;
  __REG32 p0_15           :1;
  __REG32 p0_16           :1;
  __REG32 p0_17           :1;
  __REG32 p0_18           :1;
  __REG32 p0_19           :1;
  __REG32 p0_20           :1;
  __REG32 p0_21           :1;
  __REG32 p0_22           :1;
  __REG32 p0_23           :1;
  __REG32 p0_24           :1;
  __REG32 p0_25           :1;
  __REG32 p0_26           :1;
  __REG32 p0_27           :1;
  __REG32 p0_28           :1;
  __REG32 p0_29           :1;
  __REG32 p0_30           :1;
  __REG32 p0_31           :1;
} __gpio_bits;


/* UART interrupt enable register */
typedef struct {
  __REG8 rdaie            :1;
  __REG8 threie           :1;
  __REG8 rxlsie           :1;
  __REG8 msie             :1;
  __REG8                  :4;
} __uartier_bits;

/* UART interrupt identification register and fifo control register */
typedef union {
  struct {
    __REG8 ip             :1;
    __REG8 iid            :3;
    __REG8                :2;
    __REG8 iirfe          :2;
  };
  struct {
    __REG8 fcrfe          :1;
    __REG8 rfr            :1;
    __REG8 tfr            :1;
    __REG8 dms            :1;
    __REG8                :2;
    __REG8 rtls           :2;
  };
} __uartfcriir_bits;

/* UART line control register */
typedef struct {
  __REG8 wls              :2;
  __REG8 sbs              :1;
  __REG8 pe               :1;
  __REG8 ps               :2;
  __REG8 bc               :1;
  __REG8 dlab             :1;
} __uartlcr_bits;

/* UART modem control register */
typedef struct {
  __REG8 dtr              :1;
  __REG8 rts              :1;
  __REG8                  :2;
  __REG8 lms              :1;
  __REG8                  :3;
} __uartmcr_bits;

/* UART line status register */
typedef struct {
  __REG8 rdr              :1;
  __REG8 oe               :1;
  __REG8 pe               :1;
  __REG8 fe               :1;
  __REG8 bi               :1;
  __REG8 thre             :1;
  __REG8 temt             :1;
  __REG8 rxfe             :1;
} __uartlsr_bits;

/* UART modem status register */
typedef union {
  struct {
  __REG8 dcts             :1;
  __REG8 ddsr             :1;
  __REG8 teri             :1;
  __REG8 ddcd             :1;
  __REG8 cts              :1;
  __REG8 dsr              :1;
  __REG8 ri               :1;
  __REG8 dcd              :1;
  };
  struct {
  __REG8 msr0             :1;
  __REG8 msr1             :1;
  __REG8 msr2             :1;
  __REG8 msr3             :1;
  __REG8 msr4             :1;
  __REG8 msr5             :1;
  __REG8 msr6             :1;
  __REG8 msr7             :1;
  };
} __uartmsr_bits;


/* I2C control set register */
typedef struct {
  __REG32                 :2;
  __REG32 aa              :1;
  __REG32 si              :1;
  __REG32 sto             :1;
  __REG32 sta             :1;
  __REG32 i2en            :1;
  __REG32                 :25;
} __i2conset_bits;

/* I2C control clear register */
typedef struct {
  __REG32                 :2;
  __REG32 aac             :1;
  __REG32 sic             :1;
  __REG32                 :1;
  __REG32 stac            :1;
  __REG32 i2enc           :1;
  __REG32                 :25;
} __i2conclr_bits;

/* I2C status register */
typedef struct {
  __REG32 status          :8;
  __REG32                 :24;
} __i2stat_bits;

/* I2C data register */
typedef struct {
  __REG32 data            :8;
  __REG32                 :24;
} __i2dat_bits;

/* I2C slave address register */
typedef struct {
  __REG32 gc              :1;
  __REG32 addr            :7;
  __REG32                 :24;
} __i2adr_bits;

/* I2C scl duty cycle register */
typedef struct {
  __REG32 count           :16;
  __REG32                 :16;
} __i2scl_bits;


/* SPI control register */
typedef struct {
  __REG32                 :3;
  __REG32 cpha            :1;
  __REG32 cpol            :1;
  __REG32 mstr            :1;
  __REG32 lsbf            :1;
  __REG32 spie            :1;
  __REG32                 :24;
} __spcr_bits;

/* SPI status register */
typedef struct {
  __REG32                 :3;
  __REG32 abrt            :1;
  __REG32 modf            :1;
  __REG32 rovr            :1;
  __REG32 wcol            :1;
  __REG32 spif            :1;
  __REG32                 :24;
} __spsr_bits;

/* SPI data register */
typedef struct {
  __REG32 data            :8;
  __REG32                 :24;
} __spdr_bits;

/* SPI clock counter register */
typedef struct {
  __REG32 counter         :8;
  __REG32                 :24;
} __spccr_bits;

/* SPI interrupt register */
typedef struct {
  __REG32 spiint          :1;
  __REG32                 :31;
} __spint_bits;

/* SPI test control register */
typedef struct {
  __REG32 test            :1;
  __REG32                 :31;
} __sptcr_bits;

/* SPI test observe register */
typedef struct {
  __REG32 state           :2;
  __REG32                 :30;
} __sptor_bits;


/* TIMER interrupt register */
typedef struct {
  __REG32 mr0int          :1;
  __REG32 mr1int          :1;
  __REG32 mr2int          :1;
  __REG32 mr3int          :1;
  __REG32 cr0int          :1;
  __REG32 cr1int          :1;
  __REG32 cr2int          :1;
  __REG32 cr3int          :1;
  __REG32                 :24;
} __ir_bits;

/* TIMER control register */
typedef struct {
  __REG32 ce              :1;
  __REG32 cr              :1;
  __REG32                 :30;
} __tcr_bits;

/* TIMER match control register */
typedef struct {
  __REG32 mr0int          :1;
  __REG32 mr0res          :1;
  __REG32 mr0stop         :1;
  __REG32 mr1int          :1;
  __REG32 mr1res          :1;
  __REG32 mr1stop         :1;
  __REG32 mr2int          :1;
  __REG32 mr2res          :1;
  __REG32 mr2stop         :1;
  __REG32 mr3int          :1;
  __REG32 mr3res          :1;
  __REG32 mr3stop         :1;
  __REG32                 :20;
} __mcr_bits;

/* TIMER0 capture control register */
typedef struct {
  __REG32 cap0re          :1;
  __REG32 cap0fe          :1;
  __REG32 cap0int         :1;
  __REG32 cap1re          :1;
  __REG32 cap1fe          :1;
  __REG32 cap1int         :1;
  __REG32 cap2re          :1;
  __REG32 cap2fe          :1;
  __REG32 cap2int         :1;
  __REG32                 :23;
} __ccr0_bits;

/* TIMER1 capture control register */
typedef struct {
  __REG32 cap0re          :1;
  __REG32 cap0fe          :1;
  __REG32 cap0int         :1;
  __REG32 cap1re          :1;
  __REG32 cap1fe          :1;
  __REG32 cap1int         :1;
  __REG32 cap2re          :1;
  __REG32 cap2fe          :1;
  __REG32 cap2int         :1;
  __REG32 cap3re          :1;
  __REG32 cap3fe          :1;
  __REG32 cap3int         :1;
  __REG32                 :20;
} __ccr1_bits;

/* TIMER external match register */
typedef struct {
  __REG32 em0             :1;
  __REG32 em1             :1;
  __REG32 em2             :1;
  __REG32 em3             :1;
  __REG32 emc0            :2;
  __REG32 emc1            :2;
  __REG32 emc2            :2;
  __REG32 emc3            :2;
  __REG32                 :20;
} __emr_bits;


/* PWM interrupt register */
typedef struct {
  __REG32 mr0int          :1;
  __REG32 mr1int          :1;
  __REG32 mr2int          :1;
  __REG32 mr3int          :1;
  __REG32 cr0int          :1;
  __REG32 cr1int          :1;
  __REG32 cr2int          :1;
  __REG32 cr3int          :1;
  __REG32 mr4int          :1;
  __REG32 mr5int          :1;
  __REG32 mr6int          :1;
  __REG32                 :21;
} __pwmir_bits;

/* PWM timer control register */
typedef struct {
  __REG32 ce              :1;
  __REG32 cr              :1;
  __REG32                 :1;
  __REG32 pwmen           :1;
  __REG32                 :28;
} __pwmtcr_bits;

/* PWM match control register */
typedef struct {
  __REG32 mr0int          :1;
  __REG32 mr0res          :1;
  __REG32 mr0stop         :1;
  __REG32 mr1int          :1;
  __REG32 mr1res          :1;
  __REG32 mr1stop         :1;
  __REG32 mr2int          :1;
  __REG32 mr2res          :1;
  __REG32 mr2stop         :1;
  __REG32 mr3int          :1;
  __REG32 mr3res          :1;
  __REG32 mr3stop         :1;
  __REG32 mr4int          :1;
  __REG32 mr4res          :1;
  __REG32 mr4stop         :1;
  __REG32 mr5int          :1;
  __REG32 mr5res          :1;
  __REG32 mr5stop         :1;
  __REG32 mr6int          :1;
  __REG32 mr6res          :1;
  __REG32 mr6stop         :1;
  __REG32                 :11;
} __pwmmcr_bits;

/* PWM external match register */
typedef struct {
  __REG32 em0             :1;
  __REG32 em1             :1;
  __REG32 em2             :1;
  __REG32 em3             :1;
  __REG32 emc0            :2;
  __REG32 emc1            :2;
  __REG32 emc2            :2;
  __REG32 emc3            :2;
  __REG32                 :4;
  __REG32 em4             :1;
  __REG32 em5             :1;
  __REG32 em6             :1;
  __REG32                 :1;
  __REG32 emc4            :2;
  __REG32 emc5            :2;
  __REG32 emc6            :2;
  __REG32                 :6;
} __pwmemr_bits;

/* PWM  control register */
typedef struct {
  __REG32                 :2;
  __REG32 pwmsel2         :1;
  __REG32 pwmsel3         :1;
  __REG32 pwmsel4         :1;
  __REG32 pwmsel5         :1;
  __REG32 pwmsel6         :1;
  __REG32                 :2;
  __REG32 pwmena1         :1;
  __REG32 pwmena2         :1;
  __REG32 pwmena3         :1;
  __REG32 pwmena4         :1;
  __REG32 pwmena5         :1;
  __REG32 pwmena6         :1;
  __REG32                 :17;
} __pwmpcr_bits;

/* PWM latch enable register */
typedef struct {
  __REG32 em0l            :1;
  __REG32 em1l            :1;
  __REG32 em2l            :1;
  __REG32 em3l            :1;
  __REG32 em4l            :1;
  __REG32 em5l            :1;
  __REG32 em6l            :1;
  __REG32                 :25;
} __pwmler_bits;


/* RTC interrupt location register */
typedef struct {
  __REG32 rtccif          :1;
  __REG32 rtcalf          :1;
  __REG32                 :30;
} __ilr_bits;

/* RTC clock tick counter register */
typedef struct {
  __REG32                 :1;
  __REG32 ctc             :15;
  __REG32                 :16;
} __ctc_bits;

/* RTC clock control register */
typedef struct {
  __REG32 clken           :1;
  __REG32 ctcrst          :1;
  __REG32 cttest          :2;
  __REG32                 :28;
} __rtcccr_bits;

/* RTC counter increment interrupt register */
typedef struct {
  __REG32 imsec           :1;
  __REG32 immin           :1;
  __REG32 imhour          :1;
  __REG32 imdom           :1;
  __REG32 imdow           :1;
  __REG32 imdoy           :1;
  __REG32 immon           :1;
  __REG32 imyear          :1;
  __REG32                 :24;
} __ciir_bits;

/* RTC alarm mask register */
typedef struct {
  __REG32 amrsec          :1;
  __REG32 amrmin          :1;
  __REG32 amrhour         :1;
  __REG32 amrdom          :1;
  __REG32 amrdow          :1;
  __REG32 amrdoy          :1;
  __REG32 amrmon          :1;
  __REG32 amryear         :1;
  __REG32                 :24;
} __amr_bits;

/* RTC consolidated time register 0 */
typedef struct {
  __REG32                 :5;
  __REG32 dow             :3;
  __REG32                 :3;
  __REG32 hour            :5;
  __REG32                 :2;
  __REG32 min             :6;
  __REG32                 :2;
  __REG32 sec             :6;
} __ctime0_bits;

/* RTC consolidated time register 1 */
typedef struct {
  __REG32                 :4;
  __REG32 year            :12;
  __REG32                 :4;
  __REG32 mon             :4;
  __REG32                 :3;
  __REG32 dom             :5;
} __ctime1_bits;

/* RTC consolidated time register 2 */
typedef struct {
  __REG32                 :20;
  __REG32 doy             :12;
} __ctime2_bits;

/* RTC second register */
typedef struct {
  __REG32 sec             :6;
  __REG32                 :26;
} __sec_bits;

/* RTC minute register */
typedef struct {
  __REG32 min             :6;
  __REG32                 :26;
} __min_bits;

/* RTC hour register */
typedef struct {
  __REG32 hour            :5;
  __REG32                 :27;
} __hour_bits;

/* RTC day of month register */
typedef struct {
  __REG32 dom             :5;
  __REG32                 :27;
} __dom_bits;

/* RTC day of week register */
typedef struct {
  __REG32 dow             :3;
  __REG32                 :29;
} __dow_bits;

/* RTC day of year register */
typedef struct {
  __REG32 doy             :9;
  __REG32                 :23;
} __doy_bits;

/* RTC month register */
typedef struct {
  __REG32 mon             :4;
  __REG32                 :28;
} __month_bits;

/* RTC year register */
typedef struct {
  __REG32 year            :12;
  __REG32                 :20;
} __year_bits;

/* RTC prescaler value, integer portion register */
typedef struct {
  __REG32 preint          :13;
  __REG32                 :19;
} __preint_bits;

/* RTC prescaler value, fractional portion register */
typedef struct {
  __REG32 preint          :15;
  __REG32                 :17;
} __prefrac_bits;


/* Watchdog mode register */
typedef struct {
  __REG32 wden            :1;
  __REG32 wdreset         :1;
  __REG32 wdtof           :1;
  __REG32 wdint           :1;
  __REG32                 :28;
} __wdmod_bits;

/* Watchdog feed register */
typedef struct {
  __REG32 feed            :8;
  __REG32                 :24;
} __wdfeed_bits;


/* Flash programming start address register */
typedef struct {
  __REG32                 :8;
  __REG32 rowaddr         :24;
} __fpsa_bits;

/* Flash programming data steering register */
typedef struct {
  __REG32                 :4;
  __REG32 lineaddr        :4;
  __REG32                 :24;
} __fpds_bits;

/* Flash programming control register */
typedef struct {
  __REG32 program         :1;
  __REG32 erase           :1;
  __REG32 unprotect       :1;
  __REG32 protect         :1;
  __REG32 transfer        :1;
  __REG32                 :27;
} __fpcon_bits;

/* Flash programming sector select register */
typedef struct {
  __REG32 low64kselect    :8;
  __REG32                 :16;
  __REG32 high64kselect   :8;
} __fpss_bits;

/* Flash programming status register */
typedef struct {
  __REG32 low64kstatus    :8;
  __REG32                 :16;
  __REG32 high64kstatus   :8;
} __fsps_bits;

/* Flash programming clock divisor register */
typedef struct {
  __REG32 divisor         :12;
  __REG32                 :20;
} __cradiv_bits;

/* Flash programming timer register */
typedef struct {
  __REG32 count           :16;
  __REG32                 :16;
} __fptr_bits;


/* External interrupt register */
typedef struct {
  __REG32 eint0           :1;
  __REG32 eint1           :1;
  __REG32 eint2           :1;
  __REG32                 :29;
} __extint_bits;

/* External interrupt wakeup register */
typedef struct {
  __REG32 extwake0        :1;
  __REG32 extwake1        :1;
  __REG32 extwake2        :1;
  __REG32                 :29;
} __extwake_bits;

/* Memory accelerator module control register */
typedef struct {
  __REG32 modectrl        :2;
  __REG32                 :30;
} __mamcr_bits;

/* Memory accelerator module timing register */
typedef struct {
  __REG32 fetchcycles     :3;
  __REG32                 :29;
} __mamtim_bits;

/* Memory mapping control register */
typedef struct {
  __REG32 map             :2;
  __REG32                 :30;
} __memmap_bits;

/* PLL control register */
typedef struct {
  __REG32 plle            :1;
  __REG32 pllc            :1;
  __REG32                 :30;
} __pllcon_bits;

/* PLL config register */
typedef struct {
  __REG32 msel            :5;
  __REG32 psel            :2;
  __REG32                 :25;
} __pllcfg_bits;

/* PLL status register */
typedef struct {
  __REG32 msel            :5;
  __REG32 psel            :2;
  __REG32                 :1;
  __REG32 plle            :1;
  __REG32 pllc            :1;
  __REG32 plock           :1;
  __REG32                 :21;
} __pllstat_bits;

/* PLL feed register */
typedef struct {
  __REG32 feed            :8;
  __REG32                 :24;
} __pllfeed_bits;

/* Power control register */
typedef struct {
  __REG32 idl             :1;
  __REG32 pd              :1;
  __REG32                 :30;
} __pcon_bits;

/* Power control for peripherals register */
typedef struct {
  __REG32                 :1;
  __REG32 pctim0          :1;
  __REG32 pctim1          :1;
  __REG32 pcurt0          :1;
  __REG32 pcurt1          :1;
  __REG32 pcpwm0          :1;
  __REG32                 :1;
  __REG32 pci2c           :1;
  __REG32 pcspi           :1;
  __REG32 pcrtc           :1;
  __REG32                 :22;
} __pconp_bits;

/* VPB divider register */
typedef struct {
  __REG32 vpbdiv          :2;
  __REG32                 :30;
} __vpbdiv_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Common declarations  ****************************************************/


/***************************************************************************
 **
 ** Memory Config
 **
 ***************************************************************************/
__IO_REG32_BIT(__PARTCFG, 0x3fff8000,__READ_WRITE,__partcfg_bits);


/***************************************************************************
 **
 ** VIC
 **
 ***************************************************************************/
__IO_REG32_BIT(__VICIRQStatus, 0xFFFFF000,__READ,__vicint_bits);
__IO_REG32_BIT(__VICFIQStatus, 0xFFFFF004,__READ,__vicint_bits);
__IO_REG32_BIT(__VICRawIntr, 0xFFFFF008,__READ,__vicint_bits);
__IO_REG32_BIT(__VICIntSelect, 0xFFFFF00C,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(__VICIntEnable, 0xFFFFF010,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(__VICIntEnClr, 0xFFFFF014,__WRITE,__vicint_bits);
__IO_REG32_BIT(__VICSoftInt, 0xFFFFF018,__READ_WRITE,__vicint_bits);
__IO_REG32_BIT(__VICSoftIntClear, 0xFFFFF01C,__WRITE,__vicint_bits);
__IO_REG32_BIT(__VICProtection, 0xFFFFF020,__READ_WRITE,__vicprotection_bits);
__IO_REG32(__VICVectAddr, 0xFFFFF030,__READ_WRITE);
__IO_REG32(__VICDefVectAddr, 0xFFFFF034,__READ_WRITE);
__IO_REG32(__VICVectAddr0, 0xFFFFF100,__READ_WRITE);
__IO_REG32(__VICVectAddr1, 0xFFFFF104,__READ_WRITE);
__IO_REG32(__VICVectAddr2, 0xFFFFF108,__READ_WRITE);
__IO_REG32(__VICVectAddr3, 0xFFFFF10C,__READ_WRITE);
__IO_REG32(__VICVectAddr4, 0xFFFFF110,__READ_WRITE);
__IO_REG32(__VICVectAddr5, 0xFFFFF114,__READ_WRITE);
__IO_REG32(__VICVectAddr6, 0xFFFFF118,__READ_WRITE);
__IO_REG32(__VICVectAddr7, 0xFFFFF11C,__READ_WRITE);
__IO_REG32(__VICVectAddr8, 0xFFFFF120,__READ_WRITE);
__IO_REG32(__VICVectAddr9, 0xFFFFF124,__READ_WRITE);
__IO_REG32(__VICVectAddr10, 0xFFFFF128,__READ_WRITE);
__IO_REG32(__VICVectAddr11, 0xFFFFF12C,__READ_WRITE);
__IO_REG32(__VICVectAddr12, 0xFFFFF130,__READ_WRITE);
__IO_REG32(__VICVectAddr13, 0xFFFFF134,__READ_WRITE);
__IO_REG32(__VICVectAddr14, 0xFFFFF138,__READ_WRITE);
__IO_REG32(__VICVectAddr15, 0xFFFFF13C,__READ_WRITE);
__IO_REG32_BIT(__VICVectCntl0, 0xFFFFF200,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl1, 0xFFFFF204,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl2, 0xFFFFF208,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl3, 0xFFFFF20C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl4, 0xFFFFF210,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl5, 0xFFFFF214,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl6, 0xFFFFF218,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl7, 0xFFFFF21C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl8, 0xFFFFF220,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl9, 0xFFFFF224,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl10, 0xFFFFF228,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl11, 0xFFFFF22C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl12, 0xFFFFF230,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl13, 0xFFFFF234,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl14, 0xFFFFF238,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(__VICVectCntl15, 0xFFFFF23C,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32(__VICITCR, 0xFFFFF300,__READ_WRITE);
__IO_REG32(__VICITIP1, 0xFFFFF304,__READ);
__IO_REG32(__VICITIP2, 0xFFFFF308,__READ);
__IO_REG32(__VICITOP1, 0xFFFFF30C,__READ);
__IO_REG32(__VICITOP2, 0xFFFFF310,__READ);
__IO_REG32(__VICPeriphID0, 0xFFFFFFE0,__READ);
__IO_REG32(__VICPeriphID1, 0xFFFFFFE4,__READ);
__IO_REG32(__VICPeriphID2, 0xFFFFFFE8,__READ);
__IO_REG32(__VICPeriphID3, 0xFFFFFFEC,__READ);
__IO_REG32(__VICPCellID0, 0xFFFFFFF0,__READ);
__IO_REG32(__VICPCellID1, 0xFFFFFFF4,__READ);
__IO_REG32(__VICPCellID2, 0xFFFFFFF8,__READ);
__IO_REG32(__VICPCellID3, 0xFFFFFFFC,__READ);


/***************************************************************************
 **
 ** MAM
 **
 ***************************************************************************/
__IO_REG32(__MFAC, 0x3FFFC000,__READ);
__IO_REG32(__MBAC, 0x3FFFC004,__READ);
__IO_REG32_BIT(__MSS, 0x3FFFC008,__READ_WRITE,__mss_bits);
__IO_REG32_BIT(__MSCON, 0x3FFFC00C,__READ_WRITE,__mscon_bits);


/***************************************************************************
 **
 ** Pin connect block
 **
 ***************************************************************************/
__IO_REG32_BIT(__PINSEL0, 0xE002C000,__READ_WRITE,__pinsel0_bits);
__IO_REG32_BIT(__PINSEL1, 0xE002C004,__READ_WRITE,__pinsel1_bits);


/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(__IOPIN, 0xE0028000,__READ,__gpio_bits);
__IO_REG32_BIT(__IOSET, 0xE0028004,__READ_WRITE,__gpio_bits);
__IO_REG32_BIT(__IODIR, 0xE0028008,__READ_WRITE,__gpio_bits);
__IO_REG32_BIT(__IOCLR, 0xE002800C,__WRITE,__gpio_bits);


/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/

/* UARTDLL, UARTRBR and UARTTHR share the same address */
__IO_REG8(__UART0RBRTHR, 0xE000C000,__READ_WRITE);
#define __UART0DLL __UART0RBRTHR
#define __UART0RBR __UART0RBRTHR
#define __UART0THR __UART0RBRTHR

/* UARTDLM and UARTIER share the same address */
__IO_REG8_BIT(__UART0IER, 0xE000C004,__READ_WRITE,__uartier_bits);
#define __UART0DLM __UART0IER

/* UARTFCR and UARTIIR share the same address */
__IO_REG8_BIT(__UART0FCRIIR, 0xE000C008,__READ_WRITE,__uartfcriir_bits);

__IO_REG8_BIT(__UART0LCR, 0xE000C00C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(__UART0LSR, 0xE000C014,__READ_WRITE,__uartlsr_bits);
__IO_REG8(__UART0SCR, 0xE000C01C,__READ_WRITE);


/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/

/* UARTDLL, UARTRBR and UARTTHR share the same address */
__IO_REG8(__UART1RBRTHR, 0xE0010000,__READ_WRITE);
#define __UART1DLL __UART1RBRTHR
#define __UART1RBR __UART1RBRTHR
#define __UART1THR __UART1RBRTHR

/* UARTDLM and UARTIER share the same address */
__IO_REG8_BIT(__UART1IER, 0xE0010004,__READ_WRITE,__uartier_bits);
#define __UART1DLM __UART1IER

/* UARTFCR and UARTIIR share the same address */
__IO_REG8_BIT(__UART1FCRIIR, 0xE0010008,__READ_WRITE,__uartfcriir_bits);

__IO_REG8_BIT(__UART1MCR, 0xE0010010,__READ_WRITE,__uartmcr_bits);
__IO_REG8_BIT(__UART1LCR, 0xE001000C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(__UART1LSR, 0xE0010014,__READ_WRITE,__uartlsr_bits);
__IO_REG8_BIT(__UART1MSR, 0xE0010018,__READ_WRITE,__uartmsr_bits);
__IO_REG8(__UART1SCR, 0xE001001C,__READ_WRITE);


/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(__I2CONSET, 0xE001C000,__READ_WRITE,__i2conset_bits);
__IO_REG32_BIT(__I2STAT, 0xE001C004,__READ,__i2stat_bits);
__IO_REG32_BIT(__I2DAT, 0xE001C008,__READ_WRITE,__i2dat_bits);
__IO_REG32_BIT(__I2ADR, 0xE001C00C,__READ_WRITE,__i2adr_bits);
__IO_REG32_BIT(__I2SCLH, 0xE001C010,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(__I2SCLL, 0xE001C014,__READ_WRITE,__i2scl_bits);
__IO_REG32_BIT(__I2CONCLR, 0xE001C018,__WRITE,__i2conclr_bits);


/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(__SPCR, 0xE0020000,__READ_WRITE,__spcr_bits);
__IO_REG32_BIT(__SPSR, 0xE0020004,__READ,__spsr_bits);
__IO_REG32_BIT(__SPDR, 0xE0020008,__READ_WRITE,__spdr_bits);
__IO_REG32_BIT(__SPCCR, 0xE002000C,__READ_WRITE,__spccr_bits);
__IO_REG32_BIT(__SPTCR, 0xE0020010,__READ_WRITE,__sptcr_bits);
__IO_REG32_BIT(__SPTSR, 0xE0020014,__READ_WRITE,__spsr_bits);
__IO_REG32_BIT(__SPTOR, 0xE0020018,__READ,__sptor_bits);
__IO_REG32_BIT(__SPINT, 0xE002001C,__READ_WRITE,__spint_bits);


/***************************************************************************
 **
 ** TIMER0
 **
 ***************************************************************************/
__IO_REG32_BIT(__IR0, 0xE0004000,__READ_WRITE,__ir_bits);
__IO_REG32_BIT(__TCR0, 0xE0004004,__READ_WRITE,__tcr_bits);
__IO_REG32(__TC0, 0xE0004008,__READ_WRITE);
__IO_REG32(__PR0, 0xE000400c,__READ_WRITE);
__IO_REG32(__PC0, 0xE0004010,__READ_WRITE);
__IO_REG32_BIT(__MCR0, 0xE0004014,__READ_WRITE,__mcr_bits);
__IO_REG32(__MR0_0, 0xE0004018,__READ_WRITE);
__IO_REG32(__MR1_0, 0xE000401C,__READ_WRITE);
__IO_REG32(__MR2_0, 0xE0004020,__READ_WRITE);
__IO_REG32(__MR3_0, 0xE0004024,__READ_WRITE);
__IO_REG32_BIT(__CCR0, 0xE0004028,__READ_WRITE,__ccr0_bits);
__IO_REG32(__CR0_0, 0xE000402C,__READ);
__IO_REG32(__CR1_0, 0xE0004030,__READ);
__IO_REG32(__CR2_0, 0xE0004034,__READ);
__IO_REG32(__CR3_0, 0xE0004038,__READ);
__IO_REG32_BIT(__EMR0, 0xE000403c,__READ_WRITE,__emr_bits);


/***************************************************************************
 **
 ** TIMER1
 **
 ***************************************************************************/
__IO_REG32_BIT(__IR1, 0xE0008000,__READ_WRITE,__ir_bits);
__IO_REG32_BIT(__TCR1, 0xE0008004,__READ_WRITE,__tcr_bits);
__IO_REG32(__TC1, 0xE0008008,__READ_WRITE);
__IO_REG32(__PR1, 0xE000800c,__READ_WRITE);
__IO_REG32(__PC1, 0xE0008010,__READ_WRITE);
__IO_REG32_BIT(__MCR1, 0xE0008014,__READ_WRITE,__mcr_bits);
__IO_REG32(__MR0_1, 0xE0008018,__READ_WRITE);
__IO_REG32(__MR1_1, 0xE000801C,__READ_WRITE);
__IO_REG32(__MR2_1, 0xE0008020,__READ_WRITE);
__IO_REG32(__MR3_1, 0xE0008024,__READ_WRITE);
__IO_REG32_BIT(__CCR1, 0xE0008028,__READ_WRITE,__ccr1_bits);
__IO_REG32(__CR0_1, 0xE000802C,__READ);
__IO_REG32(__CR1_1, 0xE0008030,__READ);
__IO_REG32(__CR2_1, 0xE0008034,__READ);
__IO_REG32(__CR3_1, 0xE0008038,__READ);
__IO_REG32_BIT(__EMR1, 0xE000803c,__READ_WRITE,__emr_bits);


/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(__PWMIR, 0xE0014000,__READ_WRITE,__pwmir_bits);
__IO_REG32_BIT(__PWMTCR, 0xE0014004,__READ_WRITE,__pwmtcr_bits);
__IO_REG32(__PWMTC, 0xE0014008,__READ_WRITE);
__IO_REG32(__PWMPR, 0xE001400C,__READ_WRITE);
__IO_REG32(__PWMPC, 0xE0014010,__READ_WRITE);
__IO_REG32_BIT(__PWMMCR, 0xE0014014,__READ_WRITE,__pwmmcr_bits);
__IO_REG32(__PWMMR0, 0xE0014018,__READ_WRITE);
__IO_REG32(__PWMMR1, 0xE001401C,__READ_WRITE);
__IO_REG32(__PWMMR2, 0xE0014020,__READ_WRITE);
__IO_REG32(__PWMMR3, 0xE0014024,__READ_WRITE);
__IO_REG32(__PWMMR4, 0xE0014040,__READ_WRITE);
__IO_REG32(__PWMMR5, 0xE0014044,__READ_WRITE);
__IO_REG32(__PWMMR6, 0xE0014048,__READ_WRITE);
__IO_REG32_BIT(__PWMEMR, 0xE001403C,__READ_WRITE,__pwmemr_bits);
__IO_REG32_BIT(__PWMPCR, 0xE001404C,__READ_WRITE,__pwmpcr_bits);
__IO_REG32_BIT(__PWMLER, 0xE0014050,__READ_WRITE,__pwmler_bits);
__IO_REG32_BIT(__PWMCCR, 0xE0014028,__READ_WRITE,__ccr1_bits);
__IO_REG32(__PWMCR0, 0xE001402C,__READ);
__IO_REG32(__PWMCR1, 0xE0014030,__READ);
__IO_REG32(__PWMCR2, 0xE0014034,__READ);
__IO_REG32(__PWMCR3, 0xE0014038,__READ);


/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(__ILR, 0xE0024000,__READ_WRITE,__ilr_bits);
__IO_REG32_BIT(__CTC, 0xE0024004,__READ,__ctc_bits);
__IO_REG32_BIT(__CCR, 0xE0024008,__READ_WRITE,__rtcccr_bits);
__IO_REG32_BIT(__CIIR, 0xE002400C,__READ_WRITE,__ciir_bits);
__IO_REG32_BIT(__AMR, 0xE0024010,__READ_WRITE,__amr_bits);
__IO_REG32_BIT(__CTIME0, 0xE0024014,__READ,__ctime0_bits);
__IO_REG32_BIT(__CTIME1, 0xE0024018,__READ,__ctime1_bits);
__IO_REG32_BIT(__CTIME2, 0xE002401C,__READ,__ctime2_bits);
__IO_REG32_BIT(__SEC, 0xE0024020,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(__MIN, 0xE0024024,__READ_WRITE,__min_bits);
__IO_REG32_BIT(__HOUR, 0xE0024028,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(__DOM, 0xE002402C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(__DOW, 0xE0024030,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(__DOY, 0xE0024034,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(__MONTH, 0xE0024038,__READ_WRITE,__month_bits);
__IO_REG32_BIT(__YEAR, 0xE002403C,__READ_WRITE,__year_bits);
__IO_REG32_BIT(__ALSEC, 0xE0024060,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(__ALMIN, 0xE0024064,__READ_WRITE,__min_bits);
__IO_REG32_BIT(__ALHOUR, 0xE0024068,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(__ALDOM, 0xE002406C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(__ALDOW, 0xE0024070,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(__ALDOY, 0xE0024074,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(__ALMON, 0xE0024078,__READ_WRITE,__month_bits);
__IO_REG32_BIT(__ALYEAR, 0xE002407C,__READ_WRITE,__year_bits);
__IO_REG32_BIT(__PREINT, 0xE0024080,__READ_WRITE,__preint_bits);
__IO_REG32_BIT(__PREFRAC, 0xE0024084,__READ_WRITE,__prefrac_bits);


/***************************************************************************
 **
 ** Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(__WDMOD, 0xE0000000,__READ_WRITE,__wdmod_bits);
__IO_REG32(__WDTC, 0xE0000004,__READ_WRITE);
__IO_REG32_BIT(__WDFEED, 0xE0000008,__WRITE,__wdfeed_bits);
__IO_REG32(__WDTV, 0xE000000C,__READ);


/***************************************************************************
 **
 ** Flash programming interface
 **
 ***************************************************************************/
__IO_REG32_BIT(__FPSA, 0x3FFF8004,__READ_WRITE,__fpsa_bits);
__IO_REG32(__FPD0, 0x3FFF8008,__READ_WRITE);
__IO_REG32(__FPD1, 0x3FFF800C,__READ_WRITE);
__IO_REG32(__FPD2, 0x3FFF8010,__READ_WRITE);
__IO_REG32(__FPD3, 0x3FFF8014,__READ_WRITE);
__IO_REG32_BIT(__FPCON, 0x3FFF8018,__READ_WRITE,__fpcon_bits);
__IO_REG32_BIT(__FPSS, 0x3FFF801C,__READ_WRITE,__fpss_bits);
__IO_REG32_BIT(__FPDS, 0x3FFF8020,__READ_WRITE,__fpds_bits);
__IO_REG32_BIT(__FSPS, 0x3FFF8024,__READ_WRITE,__fsps_bits);
__IO_REG32_BIT(__CRADIV, 0x3FFF8028,__READ_WRITE,__cradiv_bits);
__IO_REG32_BIT(__FPTR, 0x3FFF802C,__READ_WRITE,__fptr_bits);


/***************************************************************************
 **
 ** System control block
 **
 ***************************************************************************/
__IO_REG32_BIT(__MAMCR, 0xE01FC000,__READ_WRITE,__mamcr_bits);
__IO_REG32_BIT(__MAMTIM, 0xE01FC004,__READ_WRITE,__mamtim_bits);
__IO_REG32_BIT(__EXTINT, 0xE01FC140,__READ_WRITE,__extint_bits);
__IO_REG32_BIT(__EXTWAKE, 0xE01FC144,__READ_WRITE,__extwake_bits);
__IO_REG32_BIT(__MEMMAP, 0xE01FC040,__READ_WRITE,__memmap_bits);
__IO_REG32_BIT(__PLLCON, 0xE01FC080,__READ_WRITE,__pllcon_bits);
__IO_REG32_BIT(__PLLCFG, 0xE01FC084,__READ_WRITE,__pllcfg_bits);
__IO_REG32_BIT(__PLLSTAT, 0xE01FC088,__READ,__pllstat_bits);
__IO_REG32_BIT(__PLLFEED, 0xE01FC08C,__READ_WRITE,__pllfeed_bits);
__IO_REG32_BIT(__PCON, 0xE01FC0C0,__READ_WRITE,__pcon_bits);
__IO_REG32_BIT(__PCONP, 0xE01FC0C4,__READ_WRITE,__pconp_bits);
__IO_REG32_BIT(__VPBDIV, 0xE01FC100,__READ_WRITE,__vpbdiv_bits);



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
#define VIC_SPI         10  /* SPI     (SPIF, MODF)               */
//#define VIC_RES       11  /* Reserved                           */
#define VIC_PLL         12  /* PLL lock (PLOCK)                   */
#define VIC_RTC         13  /* RTC     (RTCCIF, RTCALF)           */
#define VIC_EINT0       14  /* External interrupt 0 (EINT0)       */
#define VIC_EINT1       15  /* External interrupt 1 (EINT1)       */
#define VIC_EINT2       16  /* External interrupt 2 (EINT2)       */


#endif    /* __IOLPC210X_H */
