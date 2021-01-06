/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Cirrus Logic EP73xx
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.7 $
 **                                
 ***************************************************************************/

#ifndef __IOEP73XX_H
#define __IOEP73XX_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    IOEP73XX SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* SYS System control register 1 */
typedef struct {
  __REG32 keyboard_scan   :4;
  __REG32 tc1m            :1;
  __REG32 tc1s            :1;
  __REG32 tc2m            :1;
  __REG32 tc2s            :1;
  __REG32 uart1en         :1;
  __REG32 bztog           :1;
  __REG32 bzmod           :1;
  __REG32 dbgen           :1;
  __REG32 lcden           :1;
  __REG32 cdent           :1;
  __REG32 cdenrx          :1;
  __REG32 siren           :1;
  __REG32 adcksel         :2;
  __REG32 excken          :1;
  __REG32 wakedis         :1;
  __REG32 irtxm           :1;
  __REG32                 :11;
} __syscon1_bits;

/* SYS System control register 2 */
typedef struct {
  __REG32 sersel          :1;
  __REG32 kbd6            :1;
  __REG32 sdramz          :1;
  __REG32 kbwen           :1;
  __REG32 ss2txen         :1;
  __REG32                 :2;
  __REG32 ss2rxen         :1;
  __REG32 uart2en         :1;
  __REG32 ss2maen         :1;
  __REG32                 :2;
  __REG32 ostb            :1;
  __REG32 clkensl         :1;
  __REG32 buzfreq         :1;
  __REG32                 :17;
} __syscon2_bits;

/* SYS System control register 3 */
typedef struct {
  __REG32 adccon          :1;
  __REG32 clkctl0         :1;
  __REG32 clkctl1         :1;
  __REG32 daisel          :1;
  __REG32 adccknsen       :1;
  __REG32 versn           :3;
  __REG32                 :1;
  __REG32 fs128           :1;
  __REG32 enpd67          :1;
  __REG32                 :21;
} __syscon3_bits;

/* SYS System flag register 1 */
typedef struct {
  __REG32 mcdr            :1;
  __REG32 dcdet           :1;
  __REG32 wudr            :1;
  __REG32 wuon            :1;
  __REG32 did             :4;
  __REG32 cts             :1;
  __REG32 dsr             :1;
  __REG32 dcd             :1;
  __REG32 ubusy1          :1;
  __REG32 nbflg           :1;
  __REG32 rstflg          :1;
  __REG32 pfflg           :1;
  __REG32 cldflg          :1;
  __REG32 rtcdiv          :6;
  __REG32 urxfe1          :1;
  __REG32 utxff1          :1;
  __REG32 crxfe           :1;
  __REG32 ctxff           :1;
  __REG32 ssibusy         :1;
  __REG32 bootbit0        :1;
  __REG32 bootbit1        :1;
  __REG32 id              :1;
  __REG32 verid           :2;
} __sysflg1_bits;

/* SYS System flag register 2 */
typedef struct {
  __REG32 ss2rxof         :1;
  __REG32 resval          :1;
  __REG32 resfrm          :1;
  __REG32 ss2rxfe         :1;
  __REG32 ss2txff         :1;
  __REG32 ss2txuf         :1;
  __REG32 ckmode          :1;
  __REG32                 :4;
  __REG32 ubusy2          :1;
  __REG32                 :10;
  __REG32 urxfe2          :1;
  __REG32 utxff2          :1;
  __REG32                 :8;
} __sysflg2_bits;


/* SEBC Memory configuration register 1*/
typedef struct {
  __REG32 ncs0bw          :2;
  __REG32 ncs0ws          :4;
  __REG32 ncs0sqaen       :1;
  __REG32 ncs0clkenb      :1;
  __REG32 ncs1bw          :2;
  __REG32 ncs1ws          :4;
  __REG32 ncs1sqaen       :1;
  __REG32 ncs1clkenb      :1;
  __REG32 ncs2bw          :2;
  __REG32 ncs2ws          :4;
  __REG32 ncs2sqaen       :1;
  __REG32 ncs2clkenb      :1;
  __REG32 ncs3bw          :2;
  __REG32 ncs3ws          :4;
  __REG32 ncs3sqaen       :1;
  __REG32 ncs3clkenb      :1;
} __sebcmemcfg1_bits;

/* SEBC Memory configuration register 2*/
typedef struct {
  __REG32 ncs4bw          :2;
  __REG32 ncs4ws          :4;
  __REG32 ncs4sqaen       :1;
  __REG32 ncs4clkenb      :1;
  __REG32 ncs5bw          :2;
  __REG32 ncs5ws          :4;
  __REG32 ncs5sqaen       :1;
  __REG32 ncs5clkenb      :1;
  __REG32 ncs6bw          :2;
  __REG32 ncs6ws          :4;
  __REG32 ncs6sqaen       :1;
  __REG32 ncs6clkenb      :1;
  __REG32 ncs7bw          :2;
  __REG32 ncs7ws          :4;
  __REG32 ncs7sqaen       :1;
  __REG32 ncs7clkenb      :1;
} __sebcmemcfg2_bits;


/* IC interrupt status register 1 */
typedef struct {
  __REG32 extfiq          :1;
  __REG32 blint           :1;
  __REG32 weint           :1;
  __REG32 mcint           :1;
  __REG32 csint           :1;
  __REG32 eint1           :1;
  __REG32 eint2           :1;
  __REG32 eint3           :1;
  __REG32 tc1oi           :1;
  __REG32 tc2oi           :1;
  __REG32 rtcmi           :1;
  __REG32 tint            :1;
  __REG32 utxint1         :1;
  __REG32 urxint1         :1;
  __REG32 umsint          :1;
  __REG32 sseoti          :1;
  __REG32                 :16;
} __icintsr1_bits;

/* IC interrupt status register 2 */
typedef struct {
  __REG32 kbdint          :1;
  __REG32 ss2rx           :1;
  __REG32 ss2tx           :1;
  __REG32                 :9;
  __REG32 utxint2         :1;
  __REG32 urxint2         :1;
  __REG32                 :18;
} __icintsr2_bits;

/* IC interrupt status register 3 */
typedef struct {
  __REG32 daiint          :1;
  __REG32                 :31;
} __icintsr3_bits;


/* LCD control register */
typedef struct {
  __REG32 video_buffer_size :13;
  __REG32 length            :3;
  __REG32 line              :3;
  __REG32 pixel_prescale    :6;
  __REG32 ac_prescale       :5;
  __REG32 gsen              :1;
  __REG32 gsmd              :1;
} __lcdcon_bits;

/* LCD palette register, least significant word */
typedef struct {
  __REG32 gsvp0             :4;
  __REG32 gsvp1             :4;
  __REG32 gsvp2             :4;
  __REG32 gsvp3             :4;
  __REG32 gsvp4             :4;
  __REG32 gsvp5             :4;
  __REG32 gsvp6             :4;
  __REG32 gsvp7             :4;
} __lcdpallsw_bits;

/* LCD palette register, most significant word */
typedef struct {
  __REG32 gsvp8             :4;
  __REG32 gsvp9             :4;
  __REG32 gsvp10            :4;
  __REG32 gsvp11            :4;
  __REG32 gsvp12            :4;
  __REG32 gsvp13            :4;
  __REG32 gsvp14            :4;
  __REG32 gsvp15            :4;
} __lcdpalmsw_bits;


/* PWM pump control register */
typedef struct {
  __REG32 d0br              :4;
  __REG32 d0acsr            :4;
  __REG32 d1pr              :4;
  __REG32                   :20;
} __pwmpmpcon_bits;


/* SSI2 DAI mode control register */
typedef struct {
  __REG32 i2sf64            :1;
  __REG32 audioclken        :1;
  __REG32 audclksrc         :1;
  __REG32 mlcken            :1;
  __REG32                   :1;
  __REG32 loopback          :1;
  __REG32                   :2;
  __REG32 audiv             :7;
  __REG32                   :17;
} __ssi2dai64fs_bits;

/* SSI2 DAI control register */
typedef struct {
  __REG32                   :16;
  __REG32 daien             :1;
  __REG32 ecs               :1;
  __REG32                   :1;
  __REG32 lctm              :1;
  __REG32 lcrm              :1;
  __REG32 rctm              :1;
  __REG32 rcrm              :1;
  __REG32                   :9;
} __ssi2dair_bits;

/* SSI2 DAI data register 2 */
typedef struct {
  __REG32                   :15;
  __REG32 fifoen            :1;
  __REG32 fifocs            :5;
  __REG32                   :11;
} __ssi2daidr2_bits;

/* SSI2 DAI status register  */
typedef struct {
  __REG32 rcts              :1;
  __REG32 rcrs              :1;
  __REG32 lcts              :1;
  __REG32 lcrs              :1;
  __REG32 rctu              :1;
  __REG32 rcro              :1;
  __REG32 lctu              :1;
  __REG32 lcro              :1;
  __REG32 rcnf              :1;
  __REG32 rcne              :1;
  __REG32 lcnf              :1;
  __REG32 lcne              :1;
  __REG32 fifo              :1;
  __REG32                   :19;
} __ssi2daisr_bits;

/* UART data register */
typedef struct {
  __REG32 rxdata            :8;
  __REG32 frmerr            :1;
  __REG32 parerr            :1;
  __REG32 overr             :1;
  __REG32                   :21;
} __uartdr_bits;

/* UART control register */
typedef struct {
  __REG32 bitrate_divisor   :12;
  __REG32 brk                :1;
  __REG32 prten             :1;
  __REG32 evenprt           :1;
  __REG32 xstop             :1;
  __REG32 fifoen            :1;
  __REG32 wrdlen            :2;
  __REG32                   :13;
} __uartubrlcr_bits;


/* SSI ADC interface data register */
typedef union {
  union {
    struct {
      __REG32 adc_configuration_byte   :8;
      __REG32 frame_length_default     :5;
    };
    struct {
      __REG32 adc_configuration_length :7;
      __REG32 frame_length_extmode     :6;
    };
  };
  struct {
    __REG32 smcken            :1;
    __REG32 txfrmen           :1;
    __REG32                   :17;
  };
} __ssisyncio_bits;


/* LED flash register */
typedef struct {
  __REG32 flash_rate        :2;
  __REG32 duty_ratio        :4;
  __REG32 enable            :1;
  __REG32                   :25;
} __ledflsh_bits;


/* SDRAM control register */
typedef struct {
  __REG32 caslat            :2;
  __REG32                   :3;
  __REG32 sdsize            :2;
  __REG32 sdwidth           :2;
  __REG32 clkctl            :1;
  __REG32 sdactive          :1;
  __REG32                   :21;
} __sdramsdconf_bits;


/* CORE PLL multiplier register */
typedef struct {
  __REG32                   :24;
  __REG32 pllmultiplier     :8;
} __corepll_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/


/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
#if __LITTLE_ENDIAN__

__IO_REG8_BIT(__GPIO_PADR,  0x80000000,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PBDR,  0x80000001,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PDDR,  0x80000003,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PADDR, 0x80000040,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PBDDR, 0x80000041,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PDDDR, 0x80000043,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PEDR,  0x80000080,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PEDDR, 0x800000c0,__READ_WRITE,__BITS8);

#else  /* __LITTLE_ENDIAN__ */

__IO_REG8_BIT(__GPIO_PADR,  0x80000003,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PBDR,  0x80000002,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PDDR,  0x80000000,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PADDR, 0x80000043,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PBDDR, 0x80000042,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PDDDR, 0x80000040,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PEDR,  0x80000083,__READ_WRITE,__BITS8);
__IO_REG8_BIT(__GPIO_PEDDR, 0x800000c3,__READ_WRITE,__BITS8);

#endif /* __LITTLE_ENDIAN__ */


/***************************************************************************
 **
 ** SYS - system registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYS_SYSCON1, 0x80000100,__READ_WRITE,__syscon1_bits);
__IO_REG32_BIT(__SYS_SYSFLG1, 0x80000140,__READ,__sysflg1_bits);

__IO_REG32(__SYS_STFCLR, 0x800005c0,__WRITE);

__IO_REG32_BIT(__SYS_SYSCON2, 0x80001100,__READ_WRITE,__syscon2_bits);
__IO_REG32_BIT(__SYS_SYSFLG2, 0x80001140,__READ,__sysflg2_bits);

__IO_REG32_BIT(__SYS_SYSCON3, 0x80002200,__READ_WRITE,__syscon3_bits);

__IO_REG32(__SYS_UNIQID, 0x80002440,__READ);
__IO_REG32(__SYS_RANDID0, 0x80002700,__READ);
__IO_REG32(__SYS_RANDID1, 0x80002704,__READ);
__IO_REG32(__SYS_RANDID2, 0x80002708,__READ);
__IO_REG32(__SYS_RANDID3, 0x8000270c,__READ);


/***************************************************************************
 **
 ** SEBC - SRAM/expansion bus controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__SEBC_MEMCFG1, 0x80000180,__READ_WRITE,__sebcmemcfg1_bits);
__IO_REG32_BIT(__SEBC_MEMCFG2, 0x800001c0,__READ_WRITE,__sebcmemcfg2_bits);


/***************************************************************************
 **
 ** IC - interrupt controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__IC_INTSR1, 0x80000240,__READ,__icintsr1_bits);
__IO_REG32_BIT(__IC_INTMR1, 0x80000280,__READ_WRITE,__icintsr1_bits);

__IO_REG32(__IC_BLEOI, 0x80000600,__WRITE);
__IO_REG32(__IC_MCEOI, 0x80000640,__WRITE);
__IO_REG32(__IC_TEOI, 0x80000680,__WRITE);
__IO_REG32(__IC_TC1EOI, 0x800006c0,__WRITE);
__IO_REG32(__IC_TC2EOI, 0x80000700,__WRITE);
__IO_REG32(__IC_RTCEOI, 0x80000740,__WRITE);
__IO_REG32(__IC_UMSEOI, 0x80000780,__WRITE);
__IO_REG32(__IC_COEOI, 0x800007C0,__WRITE);

__IO_REG32_BIT(__IC_INTSR2, 0x80001240,__READ_WRITE,__icintsr2_bits);
__IO_REG32_BIT(__IC_INTMR2, 0x80001280,__READ_WRITE,__icintsr2_bits);

__IO_REG32(__IC_KBDEOI, 0x80001700,__WRITE);
__IO_REG32(__IC_SRXEOF, 0x80001600,__WRITE);

__IO_REG32_BIT(__IC_INTSR3, 0x80002240,__READ_WRITE,__icintsr3_bits);
__IO_REG32_BIT(__IC_INTMR3, 0x80002280,__READ_WRITE,__icintsr3_bits);


/***************************************************************************
 **
 ** LCD interface
 **
 ***************************************************************************/
__IO_REG32_BIT(__LCD_LCDON, 0x800002c0,__READ_WRITE,__lcdcon_bits);
__IO_REG32_BIT(__LCD_PALLSW, 0x80000580,__READ_WRITE,__lcdpallsw_bits);
__IO_REG32_BIT(__LCD_PALMSW, 0x80000540,__READ_WRITE,__lcdpalmsw_bits);
__IO_REG32(__LCD_FBADDR, 0x80001000,__READ_WRITE);


/***************************************************************************
 **
 ** TIM - Timers
 **
 ***************************************************************************/
__IO_REG32(__TIM_TC1D, 0x80000300,__READ_WRITE);
__IO_REG32(__TIM_TC2D, 0x80000340,__READ_WRITE);
__IO_REG32(__TIM_RTCDR, 0x80000380,__READ_WRITE);
__IO_REG32(__TIM_RTCMR, 0x800003c0,__READ_WRITE);


/***************************************************************************
 **
 ** PWM interface
 **
 ***************************************************************************/
__IO_REG32_BIT(__PWM_PMPCON, 0x80000400,__READ_WRITE,__pwmpmpcon_bits);


/***************************************************************************
 **
 ** SSI2 - DAI/CODEC/SSI2
 **
 ***************************************************************************/
__IO_REG32_BIT(__SSI2_DAI64FS, 0x80002600,__READ_WRITE,__ssi2dai64fs_bits);
__IO_REG32_BIT(__SSI2_DAIR, 0x80002000,__READ_WRITE,__ssi2dair_bits);
__IO_REG32(__SSI2_DAIDR0, 0x80002040,__READ_WRITE);
__IO_REG32(__SSI2_DAIDR1, 0x80002080,__READ_WRITE);
__IO_REG32_BIT(__SSI2_DAIDR2, 0x800020c0,__READ_WRITE,__ssi2daidr2_bits);
__IO_REG32_BIT(__SSI2_DAISR, 0x80002100,__READ_WRITE,__ssi2daisr_bits);

__IO_REG32(__SSI2_SS2DR, 0x80001500,__READ_WRITE);
__IO_REG32(__SSI2_SS2POP, 0x800016c0,__WRITE);

__IO_REG32(__SSI2_CODR, 0x80000440,__READ_WRITE);


/***************************************************************************
 **
 ** UART
 **
 ***************************************************************************/
__IO_REG32_BIT(__UART_UARTDR1, 0x80000480,__READ_WRITE,__uartdr_bits);
__IO_REG32_BIT(__UART_UBRLCR1, 0x800004c0,__READ_WRITE,__uartubrlcr_bits);

__IO_REG32_BIT(__UART_UARTDR2, 0x80001480,__READ_WRITE,__uartdr_bits);
__IO_REG32_BIT(__UART_UBRLCR2, 0x800014c0,__READ_WRITE,__uartubrlcr_bits);


/***************************************************************************
 **
 ** SSI
 **
 ***************************************************************************/
__IO_REG32_BIT(__SSI_SYNCIO, 0x80000500,__READ_WRITE,__ssisyncio_bits);


/***************************************************************************
 **
 ** CPU CORE
 **
 ***************************************************************************/
__IO_REG32(__CORE_HALT, 0x80000800,__WRITE);
__IO_REG32(__CORE_STDBY, 0x80000840,__WRITE);
__IO_REG32_BIT(__CORE_PLLW, 0x80002610,__WRITE,__corepll_bits);
__IO_REG32_BIT(__CORE_PLLR, 0x8000a5a8,__READ,__corepll_bits);


/***************************************************************************
 **
 ** LED flasher
 **
 ***************************************************************************/
__IO_REG32_BIT(__LED_LEDFLSH, 0x800022c0,__READ_WRITE,__ledflsh_bits);


/***************************************************************************
 **
 ** SDRAM controller
 **
 ***************************************************************************/

__IO_REG32_BIT(__SDCONF, 0x80002300,__READ_WRITE,__sdramsdconf_bits);
__IO_REG32(__SDRFPR, 0x80002340,__READ_WRITE);

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

#endif    /* __IOEP73XX_H */
