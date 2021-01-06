/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Intel XScale PXA250
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.7 $
 **                                
 ***************************************************************************/

#ifndef __IOPXA250_H
#define __IOPXA250_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    IOPXA250 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* DMA interrupt register */
typedef struct {
  __REG32 chlintr0  :1;
  __REG32 chlintr1  :1;
  __REG32 chlintr2  :1;
  __REG32 chlintr3  :1;
  __REG32 chlintr4  :1;
  __REG32 chlintr5  :1;
  __REG32 chlintr6  :1;
  __REG32 chlintr7  :1;
  __REG32 chlintr8  :1;
  __REG32 chlintr9  :1;
  __REG32 chlintr10 :1;
  __REG32 chlintr11 :1;
  __REG32 chlintr12 :1;
  __REG32 chlintr13 :1;
  __REG32 chlintr14 :1;
  __REG32 chlintr15 :1;
  __REG32           :16;
} __dmadint_bits;

/* DMA channel control status registers */
typedef struct {
  __REG32 buserrintr  :1;
  __REG32 startintr   :1;
  __REG32 endintr     :1;
  __REG32 stopstate   :1;
  __REG32             :4;
  __REG32 reqpend     :1;
  __REG32             :20;
  __REG32 stopirqen   :1;
  __REG32 nodescfetch :1;
  __REG32 run         :1;
} __dmadcsr_bits;

/* DMA request to channel map registers */
typedef struct {
  __REG32 chlnum      :4;
  __REG32             :3;
  __REG32 mapvld      :1;
  __REG32             :24;
} __dmadrcmr_bits;

/* DMA descriptor address registers */
typedef struct {
  __REG32 stop                :1;
  __REG32                     :3;
  __REG32 descriptoraddress   :28;
} __dmaddadr_bits;

/* DMA source address registers */
typedef struct {
  __REG32             :2;
  __REG32 srcaddr     :30;
} __dmadsadr_bits;

/* DMA target address registers */
typedef struct {
  __REG32             :2;
  __REG32 trgaddr     :30;
} __dmadtadr_bits;

/* DMA command registers */
typedef struct {
  __REG32 length      :13;
  __REG32             :1;
  __REG32 width       :2;
  __REG32 size        :2;
  __REG32 endian      :1;
  __REG32             :2;
  __REG32 endirqen    :1;
  __REG32 startirqen  :1;
  __REG32             :5;
  __REG32 flowtrg     :1;
  __REG32 flowsrc     :1;
  __REG32 inctrgaddr  :1;
  __REG32 incsrcaddr  :1;
} __dmadcmd_bits;

/* UART receive buffer register, transmit holding register and divisor
   latch low register. (These share the same address) */
typedef union {
  //__UART_FFRBR __UART_BTRBR __UART_STRBR __UART_FFRBTHDL __UART_STRBTHDL __UART_BTRBTHDL
  struct {
    __REG32 rbr         :8;
    __REG32             :24;
  };
  //__UART_FFTHR __UART_BTTHR __UART_STTHR
  struct {
    __REG32 thr         :8;
    __REG32             :24;
  };
  //__UART_FFDLL __UART_BTDLL __UART_STDLL
  struct {
    __REG32 dll         :8;
    __REG32             :24;
  };
} __uartrbrthrdll_bits;

/* UART divisor latch high register and interrupt enable register.
   (These share the same address) */
typedef union {
  //__UART_FFIER __UART_BTIER __UART_STIER
  struct {
    __REG32 ravie       :1;
    __REG32 tie         :1;
    __REG32 rlse        :1;
    __REG32 mie         :1;
    __REG32 rtoie       :1;
    __REG32 nrze        :1;
    __REG32 uue         :1;
    __REG32 dmae        :1;
    __REG32             :24;
  };
  //__UART_FFDLH __UART_BTDLH __UART_STDLH
  struct {
    __REG32 dlh         :8;
    __REG32             :24;
  };
}__uartierdlh_bits;

/* UART interrupt identification register and FIFO control register. */
typedef union {
  //__UART_FFIIR __UART_BTIIR __UART_STIIR 
  struct {
    __REG32 ip          :1;
    __REG32 iid         :2;
    __REG32 tod         :1;
    __REG32             :2;
    __REG32 fifoes      :2;
    __REG32             :24;
  };
  //__UART_FFFCR __UART_BTFCR __UART_STFCR
  struct {
    __REG32 trfifoe     :1;
    __REG32 resetrf     :1;
    __REG32 resettf     :1;
    __REG32             :3;
    __REG32 itl         :2;
    __REG32             :24;
  };
} __uartiirfcr_bits;

/* UART line control register */
typedef struct {
  __REG32 wls         :2;
  __REG32 stb         :1;
  __REG32 pen         :1;
  __REG32 eps         :1;
  __REG32 stkyp       :1;
  __REG32 sb          :1;
  __REG32 dlab        :1;
  __REG32             :24;
} __uartlcr_bits;

/* UART line status register */
typedef struct {
  __REG32 dr          :1;
  __REG32 oe          :1;
  __REG32 pe          :1;
  __REG32 fe          :1;
  __REG32 bi          :1;
  __REG32 tdrq        :1;
  __REG32 temt        :1;
  __REG32 fifoe       :1;
  __REG32             :24;
} __uartlsr_bits;

/* UART modem control register */
typedef struct {
  __REG32 dtr         :1;
  __REG32 rts         :1;
  __REG32 out1        :1;
  __REG32 out2        :1;
  __REG32 loop        :1;
  __REG32             :27;
} __uartmcr_bits;

/* UART modem status register */
typedef struct {
  __REG32 dcts        :1;
  __REG32 ddsr        :1;
  __REG32 teri        :1;
  __REG32 ddcd        :1;
  __REG32 cts         :1;
  __REG32 dsr         :1;
  __REG32 ri          :1;
  __REG32 dcd         :1;
  __REG32             :24;
} __uartmsr_bits;

/* UART scratchpad register */
typedef struct {
  __REG32 sp          :8;
  __REG32             :24;
} __uartspr_bits;

/* UART infrared selection register */
typedef struct {
  __REG32 xmitir      :1;
  __REG32 rcveir      :1;
  __REG32 xmode       :1;
  __REG32 txpl        :1;
  __REG32 rxpl        :1;
  __REG32             :27;
} __uartisr_bits;


/* I2C control register */
typedef struct {
  __REG32 start   :1;
  __REG32 stop    :1;
  __REG32 acknack :1;
  __REG32 tb      :1;
  __REG32 ma      :1;
  __REG32 scle    :1;
  __REG32 iue     :1;
  __REG32 gcd     :1;
  __REG32 iteie   :1;
  __REG32 irfie   :1;
  __REG32 beie    :1;
  __REG32 ssdie   :1;
  __REG32 aldie   :1;
  __REG32 sadie   :1;
  __REG32 ur      :1;
  __REG32 fm      :1;
  __REG32         :16;
} __i2cicr_bits;

/* I2C status register */
typedef struct {
  __REG32 rwm     :1;
  __REG32 acknack :1;
  __REG32 ub      :1;
  __REG32 ibb     :1;
  __REG32 ssd     :1;
  __REG32 ald     :1;
  __REG32 ite     :1;
  __REG32 irf     :1;
  __REG32 gcad    :1;
  __REG32 sad     :1;
  __REG32 bed     :1;
  __REG32         :21;
} __i2cisr_bits;

/* I2C slave address register */
typedef struct {
  __REG32 isa     :7;
  __REG32         :25;
} __i2csar_bits;

/* I2C data buffer register */
typedef struct {
  __REG32 idb     :8;
  __REG32         :24;
} __i2cidbr_bits;

/* I2C bus monitor register */
typedef struct {
  __REG32 sdas    :1;
  __REG32 scls    :1;
  __REG32         :30;
} __i2cibmr_bits;


/* I2S serial audio controller global control register */
typedef struct {
  __REG32 enb     :1;
  __REG32         :1;
  __REG32 bckd    :1;
  __REG32 rst     :1;
  __REG32 efwr    :1;
  __REG32 strf    :1;
  __REG32         :2;
  __REG32 tfth    :4;
  __REG32 rfth    :4;
  __REG32         :16;
} __i2ssacr0_bits;


/* I2S serial audio controller global I2S/MSB justified control register */
typedef struct {
  __REG32 amsl    :1;
  __REG32         :2;
  __REG32 drec    :1;
  __REG32 drpl    :1;
  __REG32 enlbf   :1;
  __REG32         :26;
} __i2ssacr1_bits;

/* I2S serial audio controller global I2S/MSB justified status register */
typedef struct {
  __REG32 tnf     :1;
  __REG32 rne     :1;
  __REG32 bsy     :1;
  __REG32 tfs     :1;
  __REG32 rfs     :1;
  __REG32 tur     :1;
  __REG32 ror     :1;
  __REG32         :1;
  __REG32 tfl     :4;
  __REG32 rfl     :4;
  __REG32         :16;
} __i2ssasr0_bits;

/* I2S serial audio clock divider register */
typedef struct {
  __REG32 sadiv   :7;
  __REG32         :25;
} __i2ssadiv_bits;

/* I2S serial audio interrupt clear register */
typedef struct {
  __REG32         :5;
  __REG32 tur     :1;
  __REG32 ror     :1;
  __REG32         :25;
} __i2ssaicr_bits;

/* I2S serial audio interrupt mask register */
typedef struct {
  __REG32         :3;
  __REG32 tfs     :1;
  __REG32 rfs     :1;
  __REG32 tur     :1;
  __REG32 ror     :1;
  __REG32         :25;
} __i2ssaimr_bits;

/* I2S serial audio data register */
typedef struct {
  __REG32 dtl     :16;
  __REG32 dth     :16;
} __i2ssadr_bits;


/* AC97 global control register */
typedef struct {
  __REG32 gie        :1;
  __REG32 cold_rst   :1;
  __REG32 warm_rst   :1;
  __REG32 aclink_off :1;
  __REG32 prires_ien :1;
  __REG32 secres_ien :1;
  __REG32            :2;
  __REG32 prirdy_ien :1;
  __REG32 secrdy_ien :1;
  __REG32            :8;
  __REG32 sdone_ie   :1;
  __REG32 cdone_ie   :1;
  __REG32            :12;
} __ac97gcr_bits;

/* AC97 global status register */
typedef struct {
  __REG32 gsci       :1;
  __REG32 miint      :1;
  __REG32 moint      :1;
  __REG32            :2;
  __REG32 piint      :1;
  __REG32 point      :1;
  __REG32 mint       :1;
  __REG32 pcr        :1;
  __REG32 scr        :1;
  __REG32 prires     :1;
  __REG32 secres     :1;
  __REG32 bit1slt12  :1;
  __REG32 bit2slt12  :1;
  __REG32 bit3slt12  :1;
  __REG32 rdcs       :1;
  __REG32            :2;
  __REG32 sdone      :1;
  __REG32 cdone      :1;
  __REG32            :12;
} __ac97gsr_bits;

/* AC97 PCM-in/out,mic,modem control registers */
typedef struct {
  __REG32            :3;
  __REG32 feie       :1;
  __REG32            :28;
} __ac97piocr_bits;

/* AC97 PCM-in/out,mic,modem status registers */
typedef struct {
  __REG32            :4;
  __REG32 fifoe      :1;
  __REG32            :27;
} __ac97piosr_bits;

/* AC97 codec access register */
typedef struct {
  __REG32 caip       :1;
  __REG32            :31;
} __ac97car_bits;

/* AC97 PCM data register */
typedef struct {
  __REG32 pcm_ldata  :16;
  __REG32 pcm_rdata  :16;
} __ac97pcdr_bits;

/* AC97 Mic-in data register */
typedef struct {
  __REG32 mic_in_dat :16;
  __REG32            :16;
} __ac97mcdr_bits;

/* AC97 Modem data register */
typedef struct {
  __REG32 modem_dat  :16;
  __REG32            :16;
} __ac97modr_bits;


/* UDC control register */
typedef struct {
  __REG32 ude        :1;
  __REG32 uda        :1;
  __REG32 rsm        :1;
  __REG32 resir      :1;
  __REG32 susir      :1;
  __REG32 srm        :1;
  __REG32 rstir      :1;
  __REG32 rem        :1;
  __REG32            :24;
} __udccr_bits;

/* UDC endpoint control/status register 0 */
typedef struct {
  __REG32 opr        :1;
  __REG32 ipr        :1;
  __REG32 ftf        :1;
  __REG32 drwf       :1;
  __REG32 sst        :1;
  __REG32 fst        :1;
  __REG32 rne        :1;
  __REG32 sa         :1;
  __REG32            :24;
} __udccs0_bits;

/* UDC endpoint control/status register 1,6 or 11 */
typedef struct {
  __REG32 tfs        :1;
  __REG32 tpc        :1;
  __REG32 ftf        :1;
  __REG32 tur        :1;
  __REG32 sst        :1;
  __REG32 fst        :1;
  __REG32            :1;
  __REG32 tsp        :1;
  __REG32            :24;
} __udccs1611_bits;

/* UDC endpoint control/status register 2,7 or 12 */
typedef struct {
  __REG32 rfs        :1;
  __REG32 rpc        :1;
  __REG32            :1;
  __REG32 dme        :1;
  __REG32 sst        :1;
  __REG32 fst        :1;
  __REG32 rne        :1;
  __REG32 rsp        :1;
  __REG32            :24;
} __udccs2712_bits;

/* UDC endpoint control/status register 3,8 or 13 */
typedef struct {
  __REG32 tfs        :1;
  __REG32 tpc        :1;
  __REG32 ftf        :1;
  __REG32 tur        :1;
  __REG32            :1;
  __REG32            :1;
  __REG32            :1;
  __REG32 tsp        :1;
  __REG32            :24;
} __udccs3813_bits;

/* UDC endpoint control/status register 4,9 or 14 */
typedef struct {
  __REG32 rfs        :1;
  __REG32 rpc        :1;
  __REG32 rof        :1;
  __REG32 dme        :1;
  __REG32            :1;
  __REG32            :1;
  __REG32 rne        :1;
  __REG32 rsp        :1;
  __REG32            :24;
} __udccs4914_bits;

/* UDC endpoint control/status register 5,10 or 15 */
typedef struct {
  __REG32 tfs        :1;
  __REG32 tpc        :1;
  __REG32 ftf        :1;
  __REG32 tur        :1;
  __REG32 sst        :1;
  __REG32 fst        :1;
  __REG32            :1;
  __REG32 tsp        :1;
  __REG32            :24;
} __udccs51015_bits;

/* UDC interrupt control register 0 */
typedef struct {
  __REG32 im0        :1;
  __REG32 im1        :1;
  __REG32 im2        :1;
  __REG32 im3        :1;
  __REG32 im4        :1;
  __REG32 im5        :1;
  __REG32 im6        :1;
  __REG32 im7        :1;
  __REG32            :24;
} __udcuicr0_bits;

/* UDC interrupt control register 1 */
typedef struct {
  __REG32 im8        :1;
  __REG32 im9        :1;
  __REG32 im10       :1;
  __REG32 im11       :1;
  __REG32 im12       :1;
  __REG32 im13       :1;
  __REG32 im14       :1;
  __REG32 im15       :1;
  __REG32            :24;
} __udcuicr1_bits;

/* UDC status/interrupt register 0 */
typedef struct {
  __REG32 ir0        :1;
  __REG32 ir1        :1;
  __REG32 ir2        :1;
  __REG32 ir3        :1;
  __REG32 ir4        :1;
  __REG32 ir5        :1;
  __REG32 ir6        :1;
  __REG32 ir7        :1;
  __REG32            :24;
} __udcusir0_bits;

/* UDC status/interrupt register 1 */
typedef struct {
  __REG32 ir8        :1;
  __REG32 ir9        :1;
  __REG32 ir10       :1;
  __REG32 ir11       :1;
  __REG32 ir12       :1;
  __REG32 ir13       :1;
  __REG32 ir14       :1;
  __REG32 ir15       :1;
  __REG32            :24;
} __udcusir1_bits;

/* UDC frame number high register */
typedef struct {
  __REG32 fnmsb      :3;
  __REG32 ipe4       :1;
  __REG32 ipe9       :1;
  __REG32 ipe14      :1;
  __REG32 sim        :1;
  __REG32 sir        :1;
  __REG32            :24;
} __udcufnhr_bits;

/* UDC frame number low register */
typedef struct {
  __REG32 fnlsb      :8;
  __REG32            :24;
} __udcufnlr_bits;

/* UDC byte count register */
typedef struct {
  __REG32 bc         :8;
  __REG32            :24;
} __udcubcr_bits;

/* UDC data register */
typedef struct {
  __REG32 data       :8;
  __REG32            :24;
} __udcdata_bits;


/* ICP control register 0 */
typedef struct {
  __REG32 itr        :1;
  __REG32 lbm        :1;
  __REG32 tus        :1;
  __REG32 txe        :1;
  __REG32 rxe        :1;
  __REG32 rie        :1;
  __REG32 tie        :1;
  __REG32 ame        :1;
  __REG32            :24;
} __icpiccr0_bits;

/* ICP control register 1 */
typedef struct {
  __REG32 amw        :8;
  __REG32            :24;
} __icpiccr1_bits;

/* ICP control register 2 */
typedef struct {
  __REG32 trig       :2;
  __REG32 txp        :1;
  __REG32 rxp        :1;
  __REG32            :28;
} __icpiccr2_bits;

/* ICP data register */
typedef struct {
  __REG32 data       :8;
  __REG32            :24;
} __icpdata_bits;

/* ICP status register 0 */
typedef struct {
  __REG32 eif        :1;
  __REG32 tur        :1;
  __REG32 rab        :1;
  __REG32 tfs        :1;
  __REG32 rfs        :1;
  __REG32 fre        :1;
  __REG32            :26;
} __icpicsr0_bits;

/* ICP status register 1 */
typedef struct {
  __REG32 rsy        :1;
  __REG32 tby        :1;
  __REG32 rne        :1;
  __REG32 tnf        :1;
  __REG32 eof        :1;
  __REG32 cre        :1;
  __REG32 ror        :1;
  __REG32            :25;
} __icpicsr1_bits;


/* RTC trim register */
typedef struct {
  __REG32 ck_div     :16;
  __REG32 del        :10;
  __REG32            :5;
  __REG32 lck        :1;
} __rtcrttr_bits;

/* RTC status register */
typedef struct {
  __REG32 al         :1;
  __REG32 hz         :1;
  __REG32 ale        :1;
  __REG32 hze        :1;
  __REG32            :28;
} __rtcrtsr_bits;


/* OST interrupt enable register */
typedef struct {
  __REG32 e0         :1;
  __REG32 e1         :1;
  __REG32 e2         :1;
  __REG32 e3         :1;
  __REG32            :28;
} __ostoier_bits;

/* OST watchdog match enable register */
typedef struct {
  __REG32 wme        :1;
  __REG32            :31;
} __ostower_bits;

/* OST timer status register */
typedef struct {
  __REG32 m0         :1;
  __REG32 m1         :1;
  __REG32 m2         :1;
  __REG32 m3         :1;
  __REG32            :28;
} __ostossr_bits;


/* PWM control register */
typedef struct {
  __REG32 prescale   :6;
  __REG32 pwm_sd     :1;
  __REG32            :25;
} __pwmctrl_bits;

/* PWM duty cycle register */
typedef struct {
  __REG32 dcycle     :10;
  __REG32 fdcycle    :1;
  __REG32            :21;
} __pwmduty_bits;

/* PWM period control register */
typedef struct {
  __REG32 pv         :10;
  __REG32            :22;
} __pwmperval_bits;


/* Interrupt controller mask register */
typedef struct {
  __REG32            :8;
  __REG32 im8        :1;
  __REG32 im9        :1;
  __REG32 im10       :1;
  __REG32 im11       :1;
  __REG32 im12       :1;
  __REG32 im13       :1;
  __REG32 im14       :1;
  __REG32            :2;
  __REG32 im17       :1;
  __REG32 im18       :1;
  __REG32 im19       :1;
  __REG32 im20       :1;
  __REG32 im21       :1;
  __REG32 im22       :1;
  __REG32 im23       :1;
  __REG32 im24       :1;
  __REG32 im25       :1;
  __REG32 im26       :1;
  __REG32 im27       :1;
  __REG32 im28       :1;
  __REG32 im29       :1;
  __REG32 im30       :1;
  __REG32 im31       :1;
} __icicmr_bits;

/* Interrupt controller level register */
typedef struct {
  __REG32            :8;
  __REG32 il8        :1;
  __REG32 il9        :1;
  __REG32 il10       :1;
  __REG32 il11       :1;
  __REG32 il12       :1;
  __REG32 il13       :1;
  __REG32 il14       :1;
  __REG32            :2;
  __REG32 il17       :1;
  __REG32 il18       :1;
  __REG32 il19       :1;
  __REG32 il20       :1;
  __REG32 il21       :1;
  __REG32 il22       :1;
  __REG32 il23       :1;
  __REG32 il24       :1;
  __REG32 il25       :1;
  __REG32 il26       :1;
  __REG32 il27       :1;
  __REG32 il28       :1;
  __REG32 il29       :1;
  __REG32 il30       :1;
  __REG32 il31       :1;
} __iciclr_bits;

/* Interrupt controller control register */
typedef struct {
  __REG32 dim        :1;
  __REG32            :31;
} __iciccr_bits;

/* Interrupt controller IRQ pending register */
typedef struct {
  __REG32            :8;
  __REG32 ip8        :1;
  __REG32 ip9        :1;
  __REG32 ip10       :1;
  __REG32 ip11       :1;
  __REG32 ip12       :1;
  __REG32 ip13       :1;
  __REG32 ip14       :1;
  __REG32            :2;
  __REG32 ip17       :1;
  __REG32 ip18       :1;
  __REG32 ip19       :1;
  __REG32 ip20       :1;
  __REG32 ip21       :1;
  __REG32 ip22       :1;
  __REG32 ip23       :1;
  __REG32 ip24       :1;
  __REG32 ip25       :1;
  __REG32 ip26       :1;
  __REG32 ip27       :1;
  __REG32 ip28       :1;
  __REG32 ip29       :1;
  __REG32 ip30       :1;
  __REG32 ip31       :1;
} __icicip_bits;

/* Interrupt controller FIQ pending register */
typedef struct {
  __REG32            :8;
  __REG32 fp8        :1;
  __REG32 fp9        :1;
  __REG32 fp10       :1;
  __REG32 fp11       :1;
  __REG32 fp12       :1;
  __REG32 fp13       :1;
  __REG32 fp14       :1;
  __REG32            :2;
  __REG32 fp17       :1;
  __REG32 fp18       :1;
  __REG32 fp19       :1;
  __REG32 fp20       :1;
  __REG32 fp21       :1;
  __REG32 fp22       :1;
  __REG32 fp23       :1;
  __REG32 fp24       :1;
  __REG32 fp25       :1;
  __REG32 fp26       :1;
  __REG32 fp27       :1;
  __REG32 fp28       :1;
  __REG32 fp29       :1;
  __REG32 fp30       :1;
  __REG32 fp31       :1;
} __icicfp_bits;

/* Interrupt controller pending register */
typedef struct {
  __REG32            :8;
  __REG32 is8        :1;
  __REG32 is9        :1;
  __REG32 is10       :1;
  __REG32 is11       :1;
  __REG32 is12       :1;
  __REG32 is13       :1;
  __REG32 is14       :1;
  __REG32            :2;
  __REG32 is17       :1;
  __REG32 is18       :1;
  __REG32 is19       :1;
  __REG32 is20       :1;
  __REG32 is21       :1;
  __REG32 is22       :1;
  __REG32 is23       :1;
  __REG32 is24       :1;
  __REG32 is25       :1;
  __REG32 is26       :1;
  __REG32 is27       :1;
  __REG32 is28       :1;
  __REG32 is29       :1;
  __REG32 is30       :1;
  __REG32 is31       :1;
} __icicpr_bits;


/* GPIO pin level register 0 */
typedef struct {
  __REG32 pl0        :1;
  __REG32 pl1        :1;
  __REG32 pl2        :1;
  __REG32 pl3        :1;
  __REG32 pl4        :1;
  __REG32 pl5        :1;
  __REG32 pl6        :1;
  __REG32 pl7        :1;
  __REG32 pl8        :1;
  __REG32 pl9        :1;
  __REG32 pl10       :1;
  __REG32 pl11       :1;
  __REG32 pl12       :1;
  __REG32 pl13       :1;
  __REG32 pl14       :1;
  __REG32 pl15       :1;
  __REG32 pl16       :1;
  __REG32 pl17       :1;
  __REG32 pl18       :1;
  __REG32 pl19       :1;
  __REG32 pl20       :1;
  __REG32 pl21       :1;
  __REG32 pl22       :1;
  __REG32 pl23       :1;
  __REG32 pl24       :1;
  __REG32 pl25       :1;
  __REG32 pl26       :1;
  __REG32 pl27       :1;
  __REG32 pl28       :1;
  __REG32 pl29       :1;
  __REG32 pl30       :1;
  __REG32 pl31       :1;
} __gpiogplr0_bits;

/* GPIO pin level register 1 */
typedef struct {
  __REG32 pl32       :1;
  __REG32 pl33       :1;
  __REG32 pl34       :1;
  __REG32 pl35       :1;
  __REG32 pl36       :1;
  __REG32 pl37       :1;
  __REG32 pl38       :1;
  __REG32 pl39       :1;
  __REG32 pl40       :1;
  __REG32 pl41       :1;
  __REG32 pl42       :1;
  __REG32 pl43       :1;
  __REG32 pl44       :1;
  __REG32 pl45       :1;
  __REG32 pl46       :1;
  __REG32 pl47       :1;
  __REG32 pl48       :1;
  __REG32 pl49       :1;
  __REG32 pl50       :1;
  __REG32 pl51       :1;
  __REG32 pl52       :1;
  __REG32 pl53       :1;
  __REG32 pl54       :1;
  __REG32 pl55       :1;
  __REG32 pl56       :1;
  __REG32 pl57       :1;
  __REG32 pl58       :1;
  __REG32 pl59       :1;
  __REG32 pl60       :1;
  __REG32 pl61       :1;
  __REG32 pl62       :1;
  __REG32 pl63       :1;
} __gpiogplr1_bits;

/* GPIO pin level register 2 */
typedef struct {
  __REG32 pl64       :1;
  __REG32 pl65       :1;
  __REG32 pl66       :1;
  __REG32 pl67       :1;
  __REG32 pl68       :1;
  __REG32 pl69       :1;
  __REG32 pl70       :1;
  __REG32 pl71       :1;
  __REG32 pl72       :1;
  __REG32 pl73       :1;
  __REG32 pl74       :1;
  __REG32 pl75       :1;
  __REG32 pl76       :1;
  __REG32 pl77       :1;
  __REG32 pl78       :1;
  __REG32 pl79       :1;
  __REG32 pl80       :1;
  __REG32            :15;
} __gpiogplr2_bits;

/* GPIO pin direction register 0 */
typedef struct {
  __REG32 pd0        :1;
  __REG32 pd1        :1;
  __REG32 pd2        :1;
  __REG32 pd3        :1;
  __REG32 pd4        :1;
  __REG32 pd5        :1;
  __REG32 pd6        :1;
  __REG32 pd7        :1;
  __REG32 pd8        :1;
  __REG32 pd9        :1;
  __REG32 pd10       :1;
  __REG32 pd11       :1;
  __REG32 pd12       :1;
  __REG32 pd13       :1;
  __REG32 pd14       :1;
  __REG32 pd15       :1;
  __REG32 pd16       :1;
  __REG32 pd17       :1;
  __REG32 pd18       :1;
  __REG32 pd19       :1;
  __REG32 pd20       :1;
  __REG32 pd21       :1;
  __REG32 pd22       :1;
  __REG32 pd23       :1;
  __REG32 pd24       :1;
  __REG32 pd25       :1;
  __REG32 pd26       :1;
  __REG32 pd27       :1;
  __REG32 pd28       :1;
  __REG32 pd29       :1;
  __REG32 pd30       :1;
  __REG32 pd31       :1;
} __gpiogpdr0_bits;

/* GPIO pin direction register 1 */
typedef struct {
  __REG32 pd32       :1;
  __REG32 pd33       :1;
  __REG32 pd34       :1;
  __REG32 pd35       :1;
  __REG32 pd36       :1;
  __REG32 pd37       :1;
  __REG32 pd38       :1;
  __REG32 pd39       :1;
  __REG32 pd40       :1;
  __REG32 pd41       :1;
  __REG32 pd42       :1;
  __REG32 pd43       :1;
  __REG32 pd44       :1;
  __REG32 pd45       :1;
  __REG32 pd46       :1;
  __REG32 pd47       :1;
  __REG32 pd48       :1;
  __REG32 pd49       :1;
  __REG32 pd50       :1;
  __REG32 pd51       :1;
  __REG32 pd52       :1;
  __REG32 pd53       :1;
  __REG32 pd54       :1;
  __REG32 pd55       :1;
  __REG32 pd56       :1;
  __REG32 pd57       :1;
  __REG32 pd58       :1;
  __REG32 pd59       :1;
  __REG32 pd60       :1;
  __REG32 pd61       :1;
  __REG32 pd62       :1;
  __REG32 pd63       :1;
} __gpiogpdr1_bits;

/* GPIO pin direction register 2 */
typedef struct {
  __REG32 pd64       :1;
  __REG32 pd65       :1;
  __REG32 pd66       :1;
  __REG32 pd67       :1;
  __REG32 pd68       :1;
  __REG32 pd69       :1;
  __REG32 pd70       :1;
  __REG32 pd71       :1;
  __REG32 pd72       :1;
  __REG32 pd73       :1;
  __REG32 pd74       :1;
  __REG32 pd75       :1;
  __REG32 pd76       :1;
  __REG32 pd77       :1;
  __REG32 pd78       :1;
  __REG32 pd79       :1;
  __REG32 pd80       :1;
  __REG32            :15;
} __gpiogpdr2_bits;

/* GPIO pin output set register 0 */
typedef struct {
  __REG32 ps0        :1;
  __REG32 ps1        :1;
  __REG32 ps2        :1;
  __REG32 ps3        :1;
  __REG32 ps4        :1;
  __REG32 ps5        :1;
  __REG32 ps6        :1;
  __REG32 ps7        :1;
  __REG32 ps8        :1;
  __REG32 ps9        :1;
  __REG32 ps10       :1;
  __REG32 ps11       :1;
  __REG32 ps12       :1;
  __REG32 ps13       :1;
  __REG32 ps14       :1;
  __REG32 ps15       :1;
  __REG32 ps16       :1;
  __REG32 ps17       :1;
  __REG32 ps18       :1;
  __REG32 ps19       :1;
  __REG32 ps20       :1;
  __REG32 ps21       :1;
  __REG32 ps22       :1;
  __REG32 ps23       :1;
  __REG32 ps24       :1;
  __REG32 ps25       :1;
  __REG32 ps26       :1;
  __REG32 ps27       :1;
  __REG32 ps28       :1;
  __REG32 ps29       :1;
  __REG32 ps30       :1;
  __REG32 ps31       :1;
} __gpiogpsr0_bits;

/* GPIO pin output set register 1 */
typedef struct {
  __REG32 ps32       :1;
  __REG32 ps33       :1;
  __REG32 ps34       :1;
  __REG32 ps35       :1;
  __REG32 ps36       :1;
  __REG32 ps37       :1;
  __REG32 ps38       :1;
  __REG32 ps39       :1;
  __REG32 ps40       :1;
  __REG32 ps41       :1;
  __REG32 ps42       :1;
  __REG32 ps43       :1;
  __REG32 ps44       :1;
  __REG32 ps45       :1;
  __REG32 ps46       :1;
  __REG32 ps47       :1;
  __REG32 ps48       :1;
  __REG32 ps49       :1;
  __REG32 ps50       :1;
  __REG32 ps51       :1;
  __REG32 ps52       :1;
  __REG32 ps53       :1;
  __REG32 ps54       :1;
  __REG32 ps55       :1;
  __REG32 ps56       :1;
  __REG32 ps57       :1;
  __REG32 ps58       :1;
  __REG32 ps59       :1;
  __REG32 ps60       :1;
  __REG32 ps61       :1;
  __REG32 ps62       :1;
  __REG32 ps63       :1;
} __gpiogpsr1_bits;

/* GPIO pin output set register 2 */
typedef struct {
  __REG32 ps64       :1;
  __REG32 ps65       :1;
  __REG32 ps66       :1;
  __REG32 ps67       :1;
  __REG32 ps68       :1;
  __REG32 ps69       :1;
  __REG32 ps70       :1;
  __REG32 ps71       :1;
  __REG32 ps72       :1;
  __REG32 ps73       :1;
  __REG32 ps74       :1;
  __REG32 ps75       :1;
  __REG32 ps76       :1;
  __REG32 ps77       :1;
  __REG32 ps78       :1;
  __REG32 ps79       :1;
  __REG32 ps80       :1;
  __REG32            :15;
} __gpiogpsr2_bits;

/* GPIO pin output clear register 0 */
typedef struct {
  __REG32 pc0        :1;
  __REG32 pc1        :1;
  __REG32 pc2        :1;
  __REG32 pc3        :1;
  __REG32 pc4        :1;
  __REG32 pc5        :1;
  __REG32 pc6        :1;
  __REG32 pc7        :1;
  __REG32 pc8        :1;
  __REG32 pc9        :1;
  __REG32 pc10       :1;
  __REG32 pc11       :1;
  __REG32 pc12       :1;
  __REG32 pc13       :1;
  __REG32 pc14       :1;
  __REG32 pc15       :1;
  __REG32 pc16       :1;
  __REG32 pc17       :1;
  __REG32 pc18       :1;
  __REG32 pc19       :1;
  __REG32 pc20       :1;
  __REG32 pc21       :1;
  __REG32 pc22       :1;
  __REG32 pc23       :1;
  __REG32 pc24       :1;
  __REG32 pc25       :1;
  __REG32 pc26       :1;
  __REG32 pc27       :1;
  __REG32 pc28       :1;
  __REG32 pc29       :1;
  __REG32 pc30       :1;
  __REG32 pc31       :1;
} __gpiogpcr0_bits;

/* GPIO pin output clear register 1 */
typedef struct {
  __REG32 pc32       :1;
  __REG32 pc33       :1;
  __REG32 pc34       :1;
  __REG32 pc35       :1;
  __REG32 pc36       :1;
  __REG32 pc37       :1;
  __REG32 pc38       :1;
  __REG32 pc39       :1;
  __REG32 pc40       :1;
  __REG32 pc41       :1;
  __REG32 pc42       :1;
  __REG32 pc43       :1;
  __REG32 pc44       :1;
  __REG32 pc45       :1;
  __REG32 pc46       :1;
  __REG32 pc47       :1;
  __REG32 pc48       :1;
  __REG32 pc49       :1;
  __REG32 pc50       :1;
  __REG32 pc51       :1;
  __REG32 pc52       :1;
  __REG32 pc53       :1;
  __REG32 pc54       :1;
  __REG32 pc55       :1;
  __REG32 pc56       :1;
  __REG32 pc57       :1;
  __REG32 pc58       :1;
  __REG32 pc59       :1;
  __REG32 pc60       :1;
  __REG32 pc61       :1;
  __REG32 pc62       :1;
  __REG32 pc63       :1;
} __gpiogpcr1_bits;

/* GPIO pin output clear register 2 */
typedef struct {
  __REG32 pc64       :1;
  __REG32 pc65       :1;
  __REG32 pc66       :1;
  __REG32 pc67       :1;
  __REG32 pc68       :1;
  __REG32 pc69       :1;
  __REG32 pc70       :1;
  __REG32 pc71       :1;
  __REG32 pc72       :1;
  __REG32 pc73       :1;
  __REG32 pc74       :1;
  __REG32 pc75       :1;
  __REG32 pc76       :1;
  __REG32 pc77       :1;
  __REG32 pc78       :1;
  __REG32 pc79       :1;
  __REG32 pc80       :1;
  __REG32            :15;
} __gpiogpcr2_bits;

/* GPIO rising edge detect enable register 0 */
typedef struct {
  __REG32 re0        :1;
  __REG32 re1        :1;
  __REG32 re2        :1;
  __REG32 re3        :1;
  __REG32 re4        :1;
  __REG32 re5        :1;
  __REG32 re6        :1;
  __REG32 re7        :1;
  __REG32 re8        :1;
  __REG32 re9        :1;
  __REG32 re10       :1;
  __REG32 re11       :1;
  __REG32 re12       :1;
  __REG32 re13       :1;
  __REG32 re14       :1;
  __REG32 re15       :1;
  __REG32 re16       :1;
  __REG32 re17       :1;
  __REG32 re18       :1;
  __REG32 re19       :1;
  __REG32 re20       :1;
  __REG32 re21       :1;
  __REG32 re22       :1;
  __REG32 re23       :1;
  __REG32 re24       :1;
  __REG32 re25       :1;
  __REG32 re26       :1;
  __REG32 re27       :1;
  __REG32 re28       :1;
  __REG32 re29       :1;
  __REG32 re30       :1;
  __REG32 re31       :1;
} __gpiogrer0_bits;

/* GPIO pin rising edge detect enable register 1 */
typedef struct {
  __REG32 re32       :1;
  __REG32 re33       :1;
  __REG32 re34       :1;
  __REG32 re35       :1;
  __REG32 re36       :1;
  __REG32 re37       :1;
  __REG32 re38       :1;
  __REG32 re39       :1;
  __REG32 re40       :1;
  __REG32 re41       :1;
  __REG32 re42       :1;
  __REG32 re43       :1;
  __REG32 re44       :1;
  __REG32 re45       :1;
  __REG32 re46       :1;
  __REG32 re47       :1;
  __REG32 re48       :1;
  __REG32 re49       :1;
  __REG32 re50       :1;
  __REG32 re51       :1;
  __REG32 re52       :1;
  __REG32 re53       :1;
  __REG32 re54       :1;
  __REG32 re55       :1;
  __REG32 re56       :1;
  __REG32 re57       :1;
  __REG32 re58       :1;
  __REG32 re59       :1;
  __REG32 re60       :1;
  __REG32 re61       :1;
  __REG32 re62       :1;
  __REG32 re63       :1;
} __gpiogrer1_bits;

/* GPIO rising edge detect enable register 2 */
typedef struct {
  __REG32 re64       :1;
  __REG32 re65       :1;
  __REG32 re66       :1;
  __REG32 re67       :1;
  __REG32 re68       :1;
  __REG32 re69       :1;
  __REG32 re70       :1;
  __REG32 re71       :1;
  __REG32 re72       :1;
  __REG32 re73       :1;
  __REG32 re74       :1;
  __REG32 re75       :1;
  __REG32 re76       :1;
  __REG32 re77       :1;
  __REG32 re78       :1;
  __REG32 re79       :1;
  __REG32 re80       :1;
  __REG32            :15;
} __gpiogrer2_bits;

/* GPIO falling edge detect enable register 0 */
typedef struct {
  __REG32 fe0        :1;
  __REG32 fe1        :1;
  __REG32 fe2        :1;
  __REG32 fe3        :1;
  __REG32 fe4        :1;
  __REG32 fe5        :1;
  __REG32 fe6        :1;
  __REG32 fe7        :1;
  __REG32 fe8        :1;
  __REG32 fe9        :1;
  __REG32 fe10       :1;
  __REG32 fe11       :1;
  __REG32 fe12       :1;
  __REG32 fe13       :1;
  __REG32 fe14       :1;
  __REG32 fe15       :1;
  __REG32 fe16       :1;
  __REG32 fe17       :1;
  __REG32 fe18       :1;
  __REG32 fe19       :1;
  __REG32 fe20       :1;
  __REG32 fe21       :1;
  __REG32 fe22       :1;
  __REG32 fe23       :1;
  __REG32 fe24       :1;
  __REG32 fe25       :1;
  __REG32 fe26       :1;
  __REG32 fe27       :1;
  __REG32 fe28       :1;
  __REG32 fe29       :1;
  __REG32 fe30       :1;
  __REG32 fe31       :1;
} __gpiogfer0_bits;

/* GPIO pin falling edge detect enable register 1 */
typedef struct {
  __REG32 fe32       :1;
  __REG32 fe33       :1;
  __REG32 fe34       :1;
  __REG32 fe35       :1;
  __REG32 fe36       :1;
  __REG32 fe37       :1;
  __REG32 fe38       :1;
  __REG32 fe39       :1;
  __REG32 fe40       :1;
  __REG32 fe41       :1;
  __REG32 fe42       :1;
  __REG32 fe43       :1;
  __REG32 fe44       :1;
  __REG32 fe45       :1;
  __REG32 fe46       :1;
  __REG32 fe47       :1;
  __REG32 fe48       :1;
  __REG32 fe49       :1;
  __REG32 fe50       :1;
  __REG32 fe51       :1;
  __REG32 fe52       :1;
  __REG32 fe53       :1;
  __REG32 fe54       :1;
  __REG32 fe55       :1;
  __REG32 fe56       :1;
  __REG32 fe57       :1;
  __REG32 fe58       :1;
  __REG32 fe59       :1;
  __REG32 fe60       :1;
  __REG32 fe61       :1;
  __REG32 fe62       :1;
  __REG32 fe63       :1;
} __gpiogfer1_bits;

/* GPIO falling edge detect enable register 2 */
typedef struct {
  __REG32 fe64       :1;
  __REG32 fe65       :1;
  __REG32 fe66       :1;
  __REG32 fe67       :1;
  __REG32 fe68       :1;
  __REG32 fe69       :1;
  __REG32 fe70       :1;
  __REG32 fe71       :1;
  __REG32 fe72       :1;
  __REG32 fe73       :1;
  __REG32 fe74       :1;
  __REG32 fe75       :1;
  __REG32 fe76       :1;
  __REG32 fe77       :1;
  __REG32 fe78       :1;
  __REG32 fe79       :1;
  __REG32 fe80       :1;
  __REG32            :15;
} __gpiogfer2_bits;

/* GPIO edge detect status register 0 */
typedef struct {
  __REG32 ed0        :1;
  __REG32 ed1        :1;
  __REG32 ed2        :1;
  __REG32 ed3        :1;
  __REG32 ed4        :1;
  __REG32 ed5        :1;
  __REG32 ed6        :1;
  __REG32 ed7        :1;
  __REG32 ed8        :1;
  __REG32 ed9        :1;
  __REG32 ed10       :1;
  __REG32 ed11       :1;
  __REG32 ed12       :1;
  __REG32 ed13       :1;
  __REG32 ed14       :1;
  __REG32 ed15       :1;
  __REG32 ed16       :1;
  __REG32 ed17       :1;
  __REG32 ed18       :1;
  __REG32 ed19       :1;
  __REG32 ed20       :1;
  __REG32 ed21       :1;
  __REG32 ed22       :1;
  __REG32 ed23       :1;
  __REG32 ed24       :1;
  __REG32 ed25       :1;
  __REG32 ed26       :1;
  __REG32 ed27       :1;
  __REG32 ed28       :1;
  __REG32 ed29       :1;
  __REG32 ed30       :1;
  __REG32 ed31       :1;
} __gpiogedr0_bits;

/* GPIO edge detect status register 1 */
typedef struct {
  __REG32 ed32       :1;
  __REG32 ed33       :1;
  __REG32 ed34       :1;
  __REG32 ed35       :1;
  __REG32 ed36       :1;
  __REG32 ed37       :1;
  __REG32 ed38       :1;
  __REG32 ed39       :1;
  __REG32 ed40       :1;
  __REG32 ed41       :1;
  __REG32 ed42       :1;
  __REG32 ed43       :1;
  __REG32 ed44       :1;
  __REG32 ed45       :1;
  __REG32 ed46       :1;
  __REG32 ed47       :1;
  __REG32 ed48       :1;
  __REG32 ed49       :1;
  __REG32 ed50       :1;
  __REG32 ed51       :1;
  __REG32 ed52       :1;
  __REG32 ed53       :1;
  __REG32 ed54       :1;
  __REG32 ed55       :1;
  __REG32 ed56       :1;
  __REG32 ed57       :1;
  __REG32 ed58       :1;
  __REG32 ed59       :1;
  __REG32 ed60       :1;
  __REG32 ed61       :1;
  __REG32 ed62       :1;
  __REG32 ed63       :1;
} __gpiogedr1_bits;

/* GPIO edge detect status register 2 */
typedef struct {
  __REG32 ed64       :1;
  __REG32 ed65       :1;
  __REG32 ed66       :1;
  __REG32 ed67       :1;
  __REG32 ed68       :1;
  __REG32 ed69       :1;
  __REG32 ed70       :1;
  __REG32 ed71       :1;
  __REG32 ed72       :1;
  __REG32 ed73       :1;
  __REG32 ed74       :1;
  __REG32 ed75       :1;
  __REG32 ed76       :1;
  __REG32 ed77       :1;
  __REG32 ed78       :1;
  __REG32 ed79       :1;
  __REG32 ed80       :1;
  __REG32            :15;
} __gpiogedr2_bits;

/* GPIO alternate function register 0 lower*/
typedef struct {
  __REG32 af0        :2;
  __REG32 af1        :2;
  __REG32 af2        :2;
  __REG32 af3        :2;
  __REG32 af4        :2;
  __REG32 af5        :2;
  __REG32 af6        :2;
  __REG32 af7        :2;
  __REG32 af8        :2;
  __REG32 af9        :2;
  __REG32 af10       :2;
  __REG32 af11       :2;
  __REG32 af12       :2;
  __REG32 af13       :2;
  __REG32 af14       :2;
  __REG32 af15       :2;
} __gpiogafr0l_bits;

/* GPIO alternate function register 0 upper*/
typedef struct {
  __REG32 af16       :2;
  __REG32 af17       :2;
  __REG32 af18       :2;
  __REG32 af19       :2;
  __REG32 af20       :2;
  __REG32 af21       :2;
  __REG32 af22       :2;
  __REG32 af23       :2;
  __REG32 af24       :2;
  __REG32 af25       :2;
  __REG32 af26       :2;
  __REG32 af27       :2;
  __REG32 af28       :2;
  __REG32 af29       :2;
  __REG32 af30       :2;
  __REG32 af31       :2;
} __gpiogafr0u_bits;

/* GPIO alternate function register 1 lower */
typedef struct {
  __REG32 af32       :2;
  __REG32 af33       :2;
  __REG32 af34       :2;
  __REG32 af35       :2;
  __REG32 af36       :2;
  __REG32 af37       :2;
  __REG32 af38       :2;
  __REG32 af39       :2;
  __REG32 af40       :2;
  __REG32 af41       :2;
  __REG32 af42       :2;
  __REG32 af43       :2;
  __REG32 af44       :2;
  __REG32 af45       :2;
  __REG32 af46       :2;
  __REG32 af47       :2;
} __gpiogafr1l_bits;

/* GPIO alternate function register 1 upper */
typedef struct {
  __REG32 af48       :2;
  __REG32 af49       :2;
  __REG32 af50       :2;
  __REG32 af51       :2;
  __REG32 af52       :2;
  __REG32 af53       :2;
  __REG32 af54       :2;
  __REG32 af55       :2;
  __REG32 af56       :2;
  __REG32 af57       :2;
  __REG32 af58       :2;
  __REG32 af59       :2;
  __REG32 af60       :2;
  __REG32 af61       :2;
  __REG32 af62       :2;
  __REG32 af63       :2;
} __gpiogafr1u_bits;

/* GPIO alternate function register 2 lower */
typedef struct {
  __REG32 af64       :2;
  __REG32 af65       :2;
  __REG32 af66       :2;
  __REG32 af67       :2;
  __REG32 af68       :2;
  __REG32 af69       :2;
  __REG32 af70       :2;
  __REG32 af71       :2;
  __REG32 af72       :2;
  __REG32 af73       :2;
  __REG32 af74       :2;
  __REG32 af75       :2;
  __REG32 af76       :2;
  __REG32 af77       :2;
  __REG32 af78       :2;
  __REG32 af79       :2;
} __gpiogafr2l_bits;

/* GPIO alternate function register 2 upper */
typedef struct {
  __REG32 af80       :2;
  __REG32            :30;
} __gpiogafr2u_bits;


/* PM control register */
typedef struct {
  __REG32 idae       :1;
  __REG32            :31;
} __pmpmcr_bits;

/* PM general configuration register */
typedef struct {
  __REG32 opde       :1;
  __REG32 fp         :1;
  __REG32 fs         :1;
  __REG32            :29;
} __pmpcfr_bits;

/* PM wake up enable register */
typedef struct {
  __REG32 we0        :1;
  __REG32 we1        :1;
  __REG32 we2        :1;
  __REG32 we3        :1;
  __REG32 we4        :1;
  __REG32 we5        :1;
  __REG32 we6        :1;
  __REG32 we7        :1;
  __REG32 we8        :1;
  __REG32 we9        :1;
  __REG32 we10       :1;
  __REG32 we11       :1;
  __REG32 we12       :1;
  __REG32 we13       :1;
  __REG32 we14       :1;
  __REG32 we15       :1;
  __REG32            :15;
  __REG32 wertc      :1;
} __pmpwer_bits;

/* PM rising edge detect enable register */
typedef struct {
  __REG32 re0        :1;
  __REG32 re1        :1;
  __REG32 re2        :1;
  __REG32 re3        :1;
  __REG32 re4        :1;
  __REG32 re5        :1;
  __REG32 re6        :1;
  __REG32 re7        :1;
  __REG32 re8        :1;
  __REG32 re9        :1;
  __REG32 re10       :1;
  __REG32 re11       :1;
  __REG32 re12       :1;
  __REG32 re13       :1;
  __REG32 re14       :1;
  __REG32 re15       :1;
  __REG32            :16;
} __pmprer_bits;

/* PM falling edge detect enable register */
typedef struct {
  __REG32 fe0        :1;
  __REG32 fe1        :1;
  __REG32 fe2        :1;
  __REG32 fe3        :1;
  __REG32 fe4        :1;
  __REG32 fe5        :1;
  __REG32 fe6        :1;
  __REG32 fe7        :1;
  __REG32 fe8        :1;
  __REG32 fe9        :1;
  __REG32 fe10       :1;
  __REG32 fe11       :1;
  __REG32 fe12       :1;
  __REG32 fe13       :1;
  __REG32 fe14       :1;
  __REG32 fe15       :1;
  __REG32            :16;
} __pmpfer_bits;

/* PM GPIO edge detect status register */
typedef struct {
  __REG32 ed0        :1;
  __REG32 ed1        :1;
  __REG32 ed2        :1;
  __REG32 ed3        :1;
  __REG32 ed4        :1;
  __REG32 ed5        :1;
  __REG32 ed6        :1;
  __REG32 ed7        :1;
  __REG32 ed8        :1;
  __REG32 ed9        :1;
  __REG32 ed10       :1;
  __REG32 ed11       :1;
  __REG32 ed12       :1;
  __REG32 ed13       :1;
  __REG32 ed14       :1;
  __REG32 ed15       :1;
  __REG32            :16;
} __pmpedr_bits;

/* PM sleep status register */
typedef struct {
  __REG32 sss        :1;
  __REG32 bfs        :1;
  __REG32 vfs        :1;
  __REG32            :1;
  __REG32 ph         :1;
  __REG32 rdh        :1;
  __REG32            :26;
} __pmpssr_bits;

/* PM GPIO sleep state register 0 */
typedef struct {
  __REG32 ss0        :1;
  __REG32 ss1        :1;
  __REG32 ss2        :1;
  __REG32 ss3        :1;
  __REG32 ss4        :1;
  __REG32 ss5        :1;
  __REG32 ss6        :1;
  __REG32 ss7        :1;
  __REG32 ss8        :1;
  __REG32 ss9        :1;
  __REG32 ss10       :1;
  __REG32 ss11       :1;
  __REG32 ss12       :1;
  __REG32 ss13       :1;
  __REG32 ss14       :1;
  __REG32 ss15       :1;
  __REG32 ss16       :1;
  __REG32 ss17       :1;
  __REG32 ss18       :1;
  __REG32 ss19       :1;
  __REG32 ss20       :1;
  __REG32 ss21       :1;
  __REG32 ss22       :1;
  __REG32 ss23       :1;
  __REG32 ss24       :1;
  __REG32 ss25       :1;
  __REG32 ss26       :1;
  __REG32 ss27       :1;
  __REG32 ss28       :1;
  __REG32 ss29       :1;
  __REG32 ss30       :1;
  __REG32 ss31       :1;
} __pmpgsr0_bits;

/* PM GPIO sleep state register 1 */
typedef struct {
  __REG32 ss32       :1;
  __REG32 ss33       :1;
  __REG32 ss34       :1;
  __REG32 ss35       :1;
  __REG32 ss36       :1;
  __REG32 ss37       :1;
  __REG32 ss38       :1;
  __REG32 ss39       :1;
  __REG32 ss40       :1;
  __REG32 ss41       :1;
  __REG32 ss42       :1;
  __REG32 ss43       :1;
  __REG32 ss44       :1;
  __REG32 ss45       :1;
  __REG32 ss46       :1;
  __REG32 ss47       :1;
  __REG32 ss48       :1;
  __REG32 ss49       :1;
  __REG32 ss50       :1;
  __REG32 ss51       :1;
  __REG32 ss52       :1;
  __REG32 ss53       :1;
  __REG32 ss54       :1;
  __REG32 ss55       :1;
  __REG32 ss56       :1;
  __REG32 ss57       :1;
  __REG32 ss58       :1;
  __REG32 ss59       :1;
  __REG32 ss60       :1;
  __REG32 ss61       :1;
  __REG32 ss62       :1;
  __REG32 ss63       :1;
} __pmpgsr1_bits;

/* PM GPIO sleep state register 2 */
typedef struct {
  __REG32 ss64       :1;
  __REG32 ss65       :1;
  __REG32 ss66       :1;
  __REG32 ss67       :1;
  __REG32 ss68       :1;
  __REG32 ss69       :1;
  __REG32 ss70       :1;
  __REG32 ss71       :1;
  __REG32 ss72       :1;
  __REG32 ss73       :1;
  __REG32 ss74       :1;
  __REG32 ss75       :1;
  __REG32 ss76       :1;
  __REG32 ss77       :1;
  __REG32 ss78       :1;
  __REG32 ss79       :1;
  __REG32 ss80       :1;
  __REG32            :15;
} __pmpgsr2_bits;

/* PM reset controller status register */
typedef struct {
  __REG32 hwr        :1;
  __REG32 wdr        :1;
  __REG32 smr        :1;
  __REG32 gpr        :1;
  __REG32            :28;
} __pmrcsr_bits;


/* SSP SSC control register 0 */
typedef struct {
  __REG32 dss     :4;
  __REG32 frf     :2;
  __REG32 ecs     :1;
  __REG32 sse     :1;
  __REG32 scr     :8;
  __REG32         :16;
} __sspsscr0_bits;

/* SSP SSC control register 1 */
typedef struct {
  __REG32 rie     :1;
  __REG32 tie     :1;
  __REG32 lbm     :1;
  __REG32 spo     :1;
  __REG32 sph     :1;
  __REG32 mwds    :1;
  __REG32 tft     :4;
  __REG32 rft     :4;
  __REG32         :18;
} __sspsscr1_bits;

/* SSP status register */
typedef struct {
  __REG32         :2;
  __REG32 tnf     :1;
  __REG32 rne     :1;
  __REG32 bsy     :1;
  __REG32 tfs     :1;
  __REG32 rfs     :1;
  __REG32 ror     :1;
  __REG32 tfl     :4;
  __REG32 rfl     :4;
  __REG32         :16;
} __sspsssr_bits;

/* SSP data register */
typedef struct {
  __REG32 data    :16;
  __REG32         :16;
} __sspssdr_bits;


/* MMC STRPCL register */
typedef struct {
  __REG32 strpcl  :2;
  __REG32         :30;
} __mmcstrpcl_bits;

/* MMC status register */
typedef struct {
  __REG32 read_time_out         :1;
  __REG32 time_out_response     :1;
  __REG32 crc_write_error       :1;
  __REG32 crc_read_error        :1;
  __REG32 crc_read_error_token  :1;
  __REG32 res_crc_err           :1;
  __REG32 xmit_fifo_empty       :1;
  __REG32 recv_fifo_full        :1;
  __REG32 clk_en                :1;
  __REG32                       :2;
  __REG32 data_tran_online      :1;
  __REG32 prg_done              :1;
  __REG32 end_cmd_res           :1;
  __REG32                       :18;
} __mmcstat_bits;

/* MMC clock rate register */
typedef struct {
  __REG32 clk_rate              :3;
  __REG32                       :29;
} __mmcclkrt_bits;

/* MMC SPI register */
typedef struct {
  __REG32 spi_en                :1;
  __REG32 crc_on                :1;
  __REG32 spi_cs_en             :1;
  __REG32 spi_cs_address        :1;
  __REG32                       :28;
} __mmcspi_bits;

/* MMC CMDAT register */
typedef struct {
  __REG32 response_format       :2;
  __REG32 data_en               :1;
  __REG32 write_read            :1;
  __REG32 stream_block          :1;
  __REG32 busy                  :1;
  __REG32 init                  :1;
  __REG32 mmc_dma_en            :1;
  __REG32                       :24;
} __mmccmdat_bits;

/* MMC RESTO register */
typedef struct {
  __REG32 res_to                :7;
  __REG32                       :25;
} __mmcresto_bits;

/* MMC RDTO register */
typedef struct {
  __REG32 read_to               :16;
  __REG32                       :16;
} __mmcrdto_bits;

/* MMC BLKLEN register */
typedef struct {
  __REG32 blk_len               :10;
  __REG32                       :22;
} __mmcblklen_bits;

/* MMC NOB register */
typedef struct {
  __REG32 mmc_nob               :16;
  __REG32                       :16;
} __mmcnob_bits;

/* MMC PRTBUF register */
typedef struct {
  __REG32 buf_part_full         :1;
  __REG32                       :31;
} __mmcprtbuf_bits;

/* MMC I_MAS, IREG register */
typedef struct {
  __REG32 data_tran_done        :1;
  __REG32 prg_done              :1;
  __REG32 end_cmd_res           :1;
  __REG32 stop_cmd              :1;
  __REG32 clk_is_off            :1;
  __REG32 rxfifo_rd_req         :1;
  __REG32 txfifo_wr_req         :1;
  __REG32                       :25;
} __mmcimr_bits;

/* MMC CMD register */
typedef struct {
  __REG32 cmd_index             :6;
  __REG32                       :26;
} __mmccmd_bits;

/* MMC ARGH register */
typedef struct {
  __REG32 arg_h                 :16;
  __REG32                       :16;
} __mmcargh_bits;

/* MMC ARGL register */
typedef struct {
  __REG32 arg_l                 :16;
  __REG32                       :16;
} __mmcargl_bits;

/* MMC RES FIFO register */
typedef struct {
  __REG32 response_data         :16;
  __REG32                       :16;
} __mmcres_bits;

/* MMC RXFIFO register */
typedef struct {
  __REG32 read_data             :8;
  __REG32                       :24;
} __mmcrxfifo_bits;

/* MMC TXFIFO register */
typedef struct {
  __REG32 write_data            :8;
  __REG32                       :24;
} __mmctxfifo_bits;


/* CL core clock configuration register */
typedef struct {
  __REG32 l                     :5;
  __REG32 m                     :2;
  __REG32 n                     :3;
  __REG32                       :22;
} __clcccr_bits;

/* CL clock enable register */
typedef struct {
  __REG32 cken0                 :1;
  __REG32 cken1                 :1;
  __REG32 cken2                 :1;
  __REG32 cken3                 :1;
  __REG32                       :1;
  __REG32 cken5                 :1;
  __REG32 cken6                 :1;
  __REG32 cken7                 :1;
  __REG32 cken8                 :1;
  __REG32                       :2;
  __REG32 cken11                :1;
  __REG32 cken12                :1;
  __REG32 cken13                :1;
  __REG32 cken14                :1;
  __REG32                       :1;
  __REG32 cken16                :1;
  __REG32                       :15;
} __clcken_bits;

/* CL oscillator configuration register */
typedef struct {
  __REG32 ook                   :1;
  __REG32 oon                   :1;
  __REG32                       :30;
} __closcc_bits;



/* LCD controller control register 0 */
typedef struct {
  __REG32 enb                   :1;
  __REG32 cms                   :1;
  __REG32 sds                   :1;
  __REG32 ldm                   :1;
  __REG32 sfm                   :1;
  __REG32 ium                   :1;
  __REG32 efm                   :1;
  __REG32 pas                   :1;
  __REG32                       :1;
  __REG32 dpd                   :1;
  __REG32 dis                   :1;
  __REG32 qdm                   :1;
  __REG32 pdd                   :8;
  __REG32 bm                    :1;
  __REG32 oum                   :1;
  __REG32                       :10;
} __lcdlccr0_bits;

/* LCD controller control register 1 */
typedef struct {
  __REG32 ppl                   :10;
  __REG32 hsw                   :6;
  __REG32 elw                   :8;
  __REG32 blw                   :8;
} __lcdlccr1_bits;

/* LCD controller control register 2 */
typedef struct {
  __REG32 lpp                   :10;
  __REG32 vsw                   :6;
  __REG32 efw                   :8;
  __REG32 bfw                   :8;
} __lcdlccr2_bits;

/* LCD controller control register 3 */
typedef struct {
  __REG32 pcd                   :8;
  __REG32 acb                   :8;
  __REG32 api                   :4;
  __REG32 vsp                   :1;
  __REG32 hsp                   :1;
  __REG32 pcp                   :1;
  __REG32 oep                   :1;
  __REG32 bpp                   :3;
  __REG32 dpc                   :1;
  __REG32                       :4;
} __lcdlccr3_bits;

/* LCD frame id register */
typedef struct {
  __REG32                       :3;
  __REG32 frameid               :29;
} __lcdfidr_bits;

/* LCD DMA command register */
typedef struct {
  __REG32 len                   :21;
  __REG32 eofint                :1;
  __REG32 sofint                :1;
  __REG32                       :3;
  __REG32 pal                   :1;
  __REG32                       :5;
} __lcdldcmd_bits;

/* LCD DMA frame branch register */
typedef struct {
  __REG32 bra                   :1;
  __REG32 bint                  :1;
  __REG32                       :2;
  __REG32 frame_branch_address  :28;
} __lcdfbr_bits;

/* LCD controller status register */
typedef struct {
  __REG32 ldd                   :1;
  __REG32 sof                   :1;
  __REG32 ber                   :1;
  __REG32 abc                   :1;
  __REG32 iul                   :1;
  __REG32 iuu                   :1;
  __REG32 ou                    :1;
  __REG32 qd                    :1;
  __REG32 eof                   :1;
  __REG32 bs                    :1;
  __REG32 sint                  :1;
  __REG32                       :21;
} __lcdlcsr_bits;

/* LCD controller interrupt id register */
typedef struct {
  __REG32                       :3;
  __REG32 iframeid              :29;
} __lcdliidr_bits;

/* LCD TMED RGB seed register */
typedef struct {
  __REG32 trs                   :8;
  __REG32 tgs                   :8;
  __REG32 tbs                   :8;
  __REG32                       :8;
} __lcdtrgbr_bits;

/* LCD TMED control register */
typedef struct {
  __REG32 coam                  :1;
  __REG32 fnam                  :1;
  __REG32 coae                  :1;
  __REG32 fname                 :1;
  __REG32 tvbs                  :4;
  __REG32 thbs                  :4;
  __REG32                       :2;
  __REG32 ted                   :1;
  __REG32                       :17;
} __lcdtcr_bits;


/* MC MDCNFG register */
typedef struct {
  __REG32 de0                   :1;
  __REG32 de1                   :1;
  __REG32 dwid0                 :1;
  __REG32 dcac0                 :2;
  __REG32 drac0                 :2;
  __REG32 dnb0                  :1;
  __REG32 dtc0                  :2;
  __REG32 daddr0                :1;
  __REG32 dlatch0               :1;
  __REG32 dsa1111_0             :1;
  __REG32                       :3;
  __REG32 de2                   :1;
  __REG32 de3                   :1;
  __REG32 dwid2                 :1;
  __REG32 dcac2                 :2;
  __REG32 drac2                 :2;
  __REG32 dnb2                  :1;
  __REG32 dtc2                  :2;
  __REG32 daddr2                :1;
  __REG32 dlatch2               :1;
  __REG32 dsa1111_2             :1;
  __REG32                       :3;
} __mcmdcnfg_bits;

/* MC mode register set configuration register */
typedef struct {
  __REG32 mdbl0                 :3;
  __REG32 mdadd0                :1;
  __REG32 mdcl0                 :3;
  __REG32 mdmrs0                :8;
  __REG32                       :1;
  __REG32 mdbl2                 :3;
  __REG32 mdadd2                :1;
  __REG32 mdcl2                 :3;
  __REG32 mdmrs2                :8;
  __REG32                       :1;
} __mcmdmrs_bits;

/* MC MDREFR register */
typedef struct {
  __REG32 dri                   :12;
  __REG32 e0pin                 :1;
  __REG32 k0run                 :1;
  __REG32 k0db2                 :1;
  __REG32 e1pin                 :1;
  __REG32 k1run                 :1;
  __REG32 k1db2                 :1;
  __REG32 k2run                 :1;
  __REG32 k2db2                 :1;
  __REG32 apd                   :1;
  __REG32                       :1;
  __REG32 slfrsh                :1;
  __REG32 k0free                :1;
  __REG32 k1free                :1;
  __REG32 k2free                :1;
  __REG32                       :6;
} __mcmdrefr_bits;

/* MC synchronous static memory configuration register */
typedef struct {
  __REG32 sxen0                 :2;
  __REG32 sxcl0                 :3;
  __REG32 sxrl0                 :3;
  __REG32 sxra0                 :2;
  __REG32 sxca0                 :2;
  __REG32 sxtp0                 :2;
  __REG32 sxlatch0              :1;
  __REG32                       :1;
  __REG32 sxen2                 :2;
  __REG32 sxcl2                 :3;
  __REG32 sxrl2                 :3;
  __REG32 sxra2                 :2;
  __REG32 sxca2                 :2;
  __REG32 sxtp2                 :2;
  __REG32 sxlatch2              :1;
  __REG32                       :1;
} __mcsxcnfg_bits;

/* MC synchronous static memory mode register set configuration register */
typedef struct {
  __REG32 sxmrs0                :15;
  __REG32                       :1;
  __REG32 sxmrs2                :15;
  __REG32                       :1;
} __mcsxmrs_bits;

/* MC asynchronous static memory control register 0*/
typedef struct {
  __REG32 rt0                   :3;
  __REG32 rbw0                  :1;
  __REG32 rdf0                  :4;
  __REG32 rdn0                  :4;
  __REG32 rrr0                  :3;
  __REG32 rbuff0                :1;
  __REG32 rt1                   :3;
  __REG32 rbw1                  :1;
  __REG32 rdf1                  :4;
  __REG32 rdn1                  :4;
  __REG32 rrr1                  :3;
  __REG32 rbuff1                :1;
} __mcmsc0_bits;

/* MC asynchronous static memory control register 1*/
typedef struct {
  __REG32 rt2                   :3;
  __REG32 rbw2                  :1;
  __REG32 rdf2                  :4;
  __REG32 rdn2                  :4;
  __REG32 rrr2                  :3;
  __REG32 rbuff2                :1;
  __REG32 rt3                   :3;
  __REG32 rbw3                  :1;
  __REG32 rdf3                  :4;
  __REG32 rdn3                  :4;
  __REG32 rrr3                  :3;
  __REG32 rbuff3                :1;
} __mcmsc1_bits;

/* MC asynchronous static memory control register 2*/
typedef struct {
  __REG32 rt4                   :3;
  __REG32 rbw4                  :1;
  __REG32 rdf4                  :4;
  __REG32 rdn4                  :4;
  __REG32 rrr4                  :3;
  __REG32 rbuff4                :1;
  __REG32 rt5                   :3;
  __REG32 rbw5                  :1;
  __REG32 rdf5                  :4;
  __REG32 rdn5                  :4;
  __REG32 rrr5                  :3;
  __REG32 rbuff5                :1;
} __mcmsc2_bits;

/* MC expansion memory timing configuration register */
typedef struct {
  __REG32 mcmem_set             :7;
  __REG32 mcmem_asst            :5;
  __REG32                       :2;
  __REG32 mcmem_hold            :6;
  __REG32                       :12;
} __mcmcmem_bits;

/* MC MCATT register */
typedef struct {
  __REG32 mcatt_set             :7;
  __REG32 mcatt_asst            :5;
  __REG32                       :2;
  __REG32 mcmatt_hold           :6;
  __REG32                       :12;
} __mcmcatt_bits;

/* MC MCIO register */
typedef struct {
  __REG32 mcio_set              :7;
  __REG32 mcio_asst             :5;
  __REG32                       :2;
  __REG32 mcio_hold             :6;
  __REG32                       :12;
} __mcmcio_bits;

/* MC MECR register */
typedef struct {
  __REG32 nos                   :1;
  __REG32 cit                   :1;
  __REG32                       :30;
} __mcmecr_bits;

/* MC BOOT_DEF register */
typedef struct {
  __REG32 boot_sel              :3;
  __REG32 pkg_type              :1;
  __REG32                       :28;
} __mcbootdef_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/


/***************************************************************************
 **
 ** DMA controller register group 1
 **
 ***************************************************************************/
__IO_REG32_BIT(__DMA_DCSR0, 0x40000000,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR1, 0x40000004,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR2, 0x40000008,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR3, 0x4000000c,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR4, 0x40000010,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR5, 0x40000014,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR6, 0x40000018,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR7, 0x4000001c,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR8, 0x40000020,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR9, 0x40000024,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR10, 0x40000028,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR11, 0x4000002c,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR12, 0x40000030,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR13, 0x40000034,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR14, 0x40000038,__READ_WRITE,__dmadcsr_bits);
__IO_REG32_BIT(__DMA_DCSR15, 0x4000003c,__READ_WRITE,__dmadcsr_bits);

__IO_REG32_BIT(__DMA_DINT, 0x400000f0,__READ,__dmadint_bits);

__IO_REG32_BIT(__DMA_DRCMR0, 0x40000100,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR1, 0x40000104,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR2, 0x40000108,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR3, 0x4000010c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR4, 0x40000110,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR5, 0x40000114,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR6, 0x40000118,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR7, 0x4000011c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR8, 0x40000120,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR9, 0x40000124,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR10, 0x40000128,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR11, 0x4000012c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR12, 0x40000130,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR13, 0x40000134,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR14, 0x40000138,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR15, 0x4000013c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR16, 0x40000140,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR17, 0x40000144,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR18, 0x40000148,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR19, 0x4000014c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR20, 0x40000150,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR21, 0x40000154,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR22, 0x40000158,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR23, 0x4000015c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR24, 0x40000160,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR25, 0x40000164,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR26, 0x40000168,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR27, 0x4000016c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR28, 0x40000170,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR29, 0x40000174,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR30, 0x40000178,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR31, 0x4000017c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR32, 0x40000180,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR33, 0x40000184,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR34, 0x40000188,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR35, 0x4000018c,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR36, 0x40000190,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR37, 0x40000194,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR38, 0x40000198,__READ_WRITE,__dmadrcmr_bits);
__IO_REG32_BIT(__DMA_DRCMR39, 0x4000019c,__READ_WRITE,__dmadrcmr_bits);

/***************************************************************************
 **
 ** DMA controller register group 2
 **
 ***************************************************************************/
__IO_REG32_BIT(__DMA_DDADR0, 0x40000200,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR0, 0x40000204,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR0, 0x40000208,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD0, 0x4000020c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR1, 0x40000210,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR1, 0x40000214,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR1, 0x40000218,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD1, 0x4000021c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR2, 0x40000220,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR2, 0x40000224,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR2, 0x40000228,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD2, 0x4000022c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR3, 0x40000230,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR3, 0x40000234,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR3, 0x40000238,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD3, 0x4000023c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR4, 0x40000240,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR4, 0x40000244,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR4, 0x40000248,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD4, 0x4000024c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR5, 0x40000250,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR5, 0x40000254,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR5, 0x40000258,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD5, 0x4000025c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR6, 0x40000260,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR6, 0x40000264,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR6, 0x40000268,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD6, 0x4000026c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR7, 0x40000270,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR7, 0x40000274,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR7, 0x40000278,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD7, 0x4000027c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR8, 0x40000280,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR8, 0x40000284,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR8, 0x40000288,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD8, 0x4000028c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR9, 0x40000290,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR9, 0x40000294,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR9, 0x40000298,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD9, 0x4000029c,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR10, 0x400002a0,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR10, 0x400002a4,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR10, 0x400002a8,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD10, 0x400002ac,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR11, 0x400002b0,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR11, 0x400002b4,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR11, 0x400002b8,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD11, 0x400002bc,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR12, 0x400002c0,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR12, 0x400002c4,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR12, 0x400002c8,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD12, 0x400002cc,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR13, 0x400002d0,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR13, 0x400002d4,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR13, 0x400002d8,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD13, 0x400002dc,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR14, 0x400002e0,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR14, 0x400002e4,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR14, 0x400002e8,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD14, 0x400002ec,__READ_WRITE,__dmadcmd_bits);

__IO_REG32_BIT(__DMA_DDADR15, 0x400002f0,__READ_WRITE,__dmaddadr_bits);
__IO_REG32_BIT(__DMA_DSADR15, 0x400002f4,__READ_WRITE,__dmadsadr_bits);
__IO_REG32_BIT(__DMA_DTADR15, 0x400002f8,__READ_WRITE,__dmadtadr_bits);
__IO_REG32_BIT(__DMA_DCMD15, 0x400002fc,__READ_WRITE,__dmadcmd_bits);


/***************************************************************************
 **
 **  FFUART
 **
 ***************************************************************************/
/* FFRBR, FFTHR and FFDLL share the same address. */
__IO_REG32_BIT(__UART_FFRBTHDL, 0x40100000, __READ_WRITE,__uartrbrthrdll_bits);
#define __UART_FFRBR_bit __UART_FFRBTHDL_bit
#define __UART_FFRBR     __UART_FFRBTHDL
#define __UART_FFTHR_bit __UART_FFRBTHDL_bit
#define __UART_FFTHR     __UART_FFRBTHDL
#define __UART_FFDLL_bit __UART_FFRBTHDL_bit
#define __UART_FFDLL     __UART_FFRBTHDL

/* FFIER, FFDLH share the same address. */
__IO_REG32_BIT(__UART_FFIER_DLH, 0x40100004, __READ_WRITE,__uartierdlh_bits);
#define __UART_FFIER_bit __UART_FFIER_DLH_bit
#define __UART_FFIER     __UART_FFIER_DLH
#define __UART_FFDLH     __UART_FFIER_DLH

/* FFIIR, FFFCR share the same address. */
__IO_REG32_BIT(__UART_FFIIR_FCR, 0x40100008, __READ_WRITE,__uartiirfcr_bits);
#define __UART_FFIIR_bit __UART_FFIIR_FCR_bit
#define __UART_FFIIR     __UART_FFIIR_FCR
#define __UART_FFFCR_bit __UART_FFIIR_FCR_bit
#define __UART_FFFCR     __UART_FFIIR_FCR

__IO_REG32_BIT(__UART_FFLCR, 0x4010000c,__READ_WRITE,__uartlcr_bits);
__IO_REG32_BIT(__UART_FFMCR, 0x40100010,__READ_WRITE,__uartmcr_bits);
__IO_REG32_BIT(__UART_FFLSR, 0x40100014,__READ,__uartlsr_bits);
__IO_REG32_BIT(__UART_FFMSR, 0x40100018,__READ,__uartmsr_bits);
__IO_REG32_BIT(__UART_FFSPR, 0x4010001c,__READ,__uartspr_bits);
__IO_REG32_BIT(__UART_FFISR, 0x40100020,__READ_WRITE,__uartisr_bits);


/***************************************************************************
 **
 **  BTUART
 **
 ***************************************************************************/
/* BTRBR, BTTHR and BTDLL share the same address. */
__IO_REG32_BIT(__UART_BTRBTHDL, 0x40200000, __READ_WRITE,__uartrbrthrdll_bits);
#define __UART_BTRBR_bit __UART_BTRBTHDL_bit
#define __UART_BTRBR     __UART_BTRBTHDL
#define __UART_BTTHR_bit __UART_BTRBTHDL_bit
#define __UART_BTTHR     __UART_BTRBTHDL
#define __UART_BTDLL_bit __UART_BTRBTHDL_bit
#define __UART_BTDLL     __UART_BTRBTHDL

/* BTIER, BTDLH share the same address. */
__IO_REG32_BIT(__UART_BTIER_DLH, 0x40200004, __READ_WRITE,__uartierdlh_bits);
#define __UART_BTIER_bit __UART_BTIER_DLH_bit
#define __UART_BTIER     __UART_BTIER_DLH
#define __UART_BTDLH     __UART_BTIER_DLH

/* BTIIR, BTFCR share the same address. */
__IO_REG32_BIT(__UART_BTIIR_FCR, 0x40200008, __READ_WRITE,__uartiirfcr_bits);
#define __UART_BTIIR_bit __UART_BTIIR_FCR_bit
#define __UART_BTIIR     __UART_BTIIR_FCR
#define __UART_BTFCR_bit __UART_BTIIR_FCR_bit
#define __UART_BTFCR     __UART_BTIIR_FCR

__IO_REG32_BIT(__UART_BTLCR, 0x4020000c,__READ_WRITE,__uartlcr_bits);
__IO_REG32_BIT(__UART_BTMCR, 0x40200010,__READ_WRITE,__uartmcr_bits);
__IO_REG32_BIT(__UART_BTLSR, 0x40200014,__READ,__uartlsr_bits);
__IO_REG32_BIT(__UART_BTMSR, 0x40200018,__READ,__uartmsr_bits);
__IO_REG32_BIT(__UART_BTSPR, 0x4020001c,__READ_WRITE,__uartspr_bits);
__IO_REG32_BIT(__UART_BTISR, 0x40200020,__READ_WRITE,__uartisr_bits);


/***************************************************************************
 **
 **  STUART
 **
 ***************************************************************************/
/* STRBR, STTHR and STDLL share the same address. */
__IO_REG32_BIT(__UART_STRBTHDL, 0x40700000, __READ_WRITE,__uartrbrthrdll_bits);
#define __UART_STRBR_bit __UART_STRBTHDL_bit
#define __UART_STRBR     __UART_STRBTHDL
#define __UART_STTHR_bit __UART_STRBTHDL_bit
#define __UART_STTHR     __UART_STRBTHDL
#define __UART_STDLL_bit __UART_STRBTHDL_bit
#define __UART_STDLL     __UART_STRBTHDL

/* STIER, STDLH share the same address. */
__IO_REG32_BIT(__UART_STIER_DLH, 0x40700004, __READ_WRITE,__uartierdlh_bits);
#define __UART_STIER_bit __UART_STIER_DLH_bit
#define __UART_STIER     __UART_STIER_DLH
#define __UART_STDLH_bit __UART_STIER_DLH_bit
#define __UART_STDLH     __UART_STIER_DLH

/* STIIR, STFCR share the same address. */
__IO_REG32_BIT(__UART_STIIR_FCR, 0x40700008, __READ_WRITE,__uartiirfcr_bits);
#define __UART_STIIR_bit __UART_STIIR_FCR_bit
#define __UART_STIIR     __UART_STIIR_FCR
#define __UART_STFCR_bit __UART_STIIR_FCR_bit
#define __UART_STFCR     __UART_STIIR_FCR

__IO_REG32_BIT(__UART_STLCR, 0x4070000c,__READ_WRITE,__uartlcr_bits);
__IO_REG32_BIT(__UART_STMCR, 0x40700010,__READ_WRITE,__uartmcr_bits);
__IO_REG32_BIT(__UART_STLSR, 0x40700014,__READ,__uartlsr_bits);
__IO_REG32_BIT(__UART_STMSR, 0x40700018,__READ,__uartmsr_bits);
__IO_REG32_BIT(__UART_STSPR, 0x4070001c,__READ_WRITE,__uartspr_bits);
__IO_REG32_BIT(__UART_STISR, 0x40700020,__READ_WRITE,__uartisr_bits);


/***************************************************************************
 **
 **  I2C - I2C bus interface unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__I2C_IBMR, 0x40301680,__READ,__i2cibmr_bits);
__IO_REG32_BIT(__I2C_IDBR, 0x40301688,__READ_WRITE,__i2cidbr_bits);
__IO_REG32_BIT(__I2C_ICR, 0x40301690,__READ_WRITE,__i2cicr_bits);
__IO_REG32_BIT(__I2C_ISR, 0x40301698,__READ_WRITE,__i2cisr_bits);
__IO_REG32_BIT(__I2C_ISAR, 0x403016a0,__READ_WRITE,__i2csar_bits);


/***************************************************************************
 **
 **  I2S
 **
 ***************************************************************************/
__IO_REG32_BIT(__I2S_SACR0, 0x40400000,__READ_WRITE,__i2ssacr0_bits);
__IO_REG32_BIT(__I2S_SACR1, 0x40400004,__READ_WRITE,__i2ssacr1_bits);
/*****RESERVED: 0x40400008 */
__IO_REG32_BIT(__I2S_SASR0, 0x4040000c,__READ,__i2ssasr0_bits);
__IO_REG32_BIT(__I2S_SAIMR, 0x40400014,__READ_WRITE,__i2ssaimr_bits);
__IO_REG32_BIT(__I2S_SAICR, 0x40400018,__WRITE,__i2ssaicr_bits);
/*****RESERVED: 0x4040001c - 0x4040005c */
__IO_REG32_BIT(__I2S_SADIV, 0x40400060,__READ_WRITE,__i2ssadiv_bits);
/*****RESERVED: 0x40400064 - 0x4040007c */
__IO_REG32_BIT(__I2S_SADR, 0x40400080,__READ_WRITE,__i2ssadr_bits);


/***************************************************************************
 **
 **  AC97
 **
 ***************************************************************************/
__IO_REG32_BIT(__AC97_POCR, 0x40500000,__READ_WRITE,__ac97piocr_bits);
__IO_REG32_BIT(__AC97_PICR, 0x40500004,__READ_WRITE,__ac97piocr_bits);
__IO_REG32_BIT(__AC97_MCCR, 0x40500008,__READ_WRITE,__ac97piocr_bits);
__IO_REG32_BIT(__AC97_GCR, 0x4050000c,__READ_WRITE,__ac97gcr_bits);
__IO_REG32_BIT(__AC97_POSR, 0x40500010,__READ_WRITE,__ac97piosr_bits);
__IO_REG32_BIT(__AC97_PISR, 0x40500014,__READ_WRITE,__ac97piosr_bits);
__IO_REG32_BIT(__AC97_MCSR, 0x40500018,__READ_WRITE,__ac97piosr_bits);
__IO_REG32_BIT(__AC97_GSR, 0x4050001c,__READ_WRITE,__ac97gsr_bits);
__IO_REG32_BIT(__AC97_CAR, 0x40500020,__READ_WRITE,__ac97car_bits);
/*****RESERVED: 0x40500024 - 0x4050003c */
__IO_REG32_BIT(__AC97_PCDR, 0x40500040,__READ_WRITE,__ac97pcdr_bits);
/*****RESERVED: 0x40500044 - 0x4050005c */
__IO_REG32_BIT(__AC97_MCDR, 0x40500060,__READ,__ac97mcdr_bits);
/*****RESERVED: 0x40500064 - 0x405000fc */
__IO_REG32_BIT(__AC97_MOCR, 0x40500100,__READ_WRITE,__ac97piocr_bits);
/*****RESERVED: 0x40500104 */
__IO_REG32_BIT(__AC97_MICR, 0x40500108,__READ_WRITE,__ac97piocr_bits);
__IO_REG32_BIT(__AC97_MOSR, 0x40500110,__READ_WRITE,__ac97piosr_bits);
/*****RESERVED: 0x40500114 */
__IO_REG32_BIT(__AC97_MISR, 0x40500118,__READ_WRITE,__ac97piosr_bits);
/*****RESERVED: 0x4050011c - 0x4050013c */
__IO_REG32_BIT(__AC97_MODR, 0x40500140,__READ_WRITE,__ac97modr_bits);
/*****RESERVED: 0x40500144 - 0x405001fc */


/***************************************************************************
 **
 **  UDC - USB device controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__UDC_UDCCR, 0x40600000,__READ_WRITE,__udccr_bits);
/*****RESERVED: 0x40600004 - 0x4050000f */

__IO_REG32_BIT(__UDC_UDCCS0, 0x40600010,__READ_WRITE,__udccs0_bits);
__IO_REG32_BIT(__UDC_UDCCS1, 0x40600014,__READ_WRITE,__udccs1611_bits);
__IO_REG32_BIT(__UDC_UDCCS2, 0x40600018,__READ_WRITE,__udccs2712_bits);
__IO_REG32_BIT(__UDC_UDCCS3, 0x4060001c,__READ_WRITE,__udccs3813_bits);
__IO_REG32_BIT(__UDC_UDCCS4, 0x40600020,__READ_WRITE,__udccs4914_bits);
__IO_REG32_BIT(__UDC_UDCCS5, 0x40600024,__READ_WRITE,__udccs51015_bits);
__IO_REG32_BIT(__UDC_UDCCS6, 0x40600028,__READ_WRITE,__udccs1611_bits);
__IO_REG32_BIT(__UDC_UDCCS7, 0x4060002c,__READ_WRITE,__udccs2712_bits);
__IO_REG32_BIT(__UDC_UDCCS8, 0x40600030,__READ_WRITE,__udccs3813_bits);
__IO_REG32_BIT(__UDC_UDCCS9, 0x40600034,__READ_WRITE,__udccs4914_bits);
__IO_REG32_BIT(__UDC_UDCCS10, 0x40600038,__READ_WRITE,__udccs51015_bits);
__IO_REG32_BIT(__UDC_UDCCS11, 0x4060003c,__READ_WRITE,__udccs1611_bits);
__IO_REG32_BIT(__UDC_UDCCS12, 0x40600040,__READ_WRITE,__udccs2712_bits);
__IO_REG32_BIT(__UDC_UDCCS13, 0x40600044,__READ_WRITE,__udccs3813_bits);
__IO_REG32_BIT(__UDC_UDCCS14, 0x40600048,__READ_WRITE,__udccs4914_bits);
__IO_REG32_BIT(__UDC_UDCCS15, 0x4060004c,__READ_WRITE,__udccs51015_bits);

__IO_REG32_BIT(__UDC_UICR0, 0x40600050,__READ_WRITE,__udcuicr0_bits);
__IO_REG32_BIT(__UDC_UICR1, 0x40600054,__READ_WRITE,__udcuicr1_bits);
__IO_REG32_BIT(__UDC_USIR0, 0x40600058,__READ_WRITE,__udcusir0_bits);
__IO_REG32_BIT(__UDC_USIR1, 0x4060005c,__READ_WRITE,__udcusir1_bits);
__IO_REG32_BIT(__UDC_UFNHR, 0x40600060,__READ_WRITE,__udcufnhr_bits);
__IO_REG32_BIT(__UDC_UFNLR, 0x40600064,__READ_WRITE,__udcufnlr_bits);

__IO_REG32_BIT(__UDC_UBCR2, 0x40600068,__READ,__udcubcr_bits);
__IO_REG32_BIT(__UDC_UBCR4, 0x4060006c,__READ,__udcubcr_bits);
__IO_REG32_BIT(__UDC_UBCR7, 0x40600070,__READ,__udcubcr_bits);
__IO_REG32_BIT(__UDC_UBCR9, 0x40600074,__READ,__udcubcr_bits);
__IO_REG32_BIT(__UDC_UBCR12, 0x40600078,__READ,__udcubcr_bits);
__IO_REG32_BIT(__UDC_UBCR14, 0x4060007c,__READ,__udcubcr_bits);

__IO_REG32_BIT(__UDC_UDDR0, 0x40600080,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR1, 0x40600100,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR2, 0x40600180,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR3, 0x40600200,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR4, 0x40600400,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR5, 0x406000A0,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR6, 0x40600600,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR7, 0x40600680,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR8, 0x40600700,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR9, 0x40600900,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR10, 0x406000c0,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR11, 0x40600b00,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR12, 0x40600b80,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR13, 0x40600c00,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR14, 0x40600e00,__READ_WRITE,__udcdata_bits);
__IO_REG32_BIT(__UDC_UDDR15, 0x406000e0,__READ_WRITE,__udcdata_bits);


/***************************************************************************
 **
 **  ICP - fast infrared communication port
 **
 ***************************************************************************/
__IO_REG32_BIT(__ICP_ICCR0, 0x40800000,__READ_WRITE,__icpiccr0_bits);
__IO_REG32_BIT(__ICP_ICCR1, 0x40800004,__READ_WRITE,__icpiccr1_bits);
__IO_REG32_BIT(__ICP_ICCR2, 0x40800008,__READ_WRITE,__icpiccr2_bits);
/*****RESERVED: 0x40800010 */
__IO_REG32_BIT(__ICP_ICDR, 0x4080000c,__READ_WRITE,__icpdata_bits);
__IO_REG32_BIT(__ICP_ICSR0, 0x40800014,__READ_WRITE,__icpicsr0_bits);
__IO_REG32_BIT(__ICP_ICSR1, 0x40800018,__READ_WRITE,__icpicsr1_bits);


/***************************************************************************
 **
 **  RTC - real time clock
 **
 ***************************************************************************/
__IO_REG32(__RTC_RCNR, 0x40900000,__READ_WRITE);
__IO_REG32(__RTC_RTAR, 0x40900004,__READ_WRITE);
__IO_REG32_BIT(__RTC_RTSR, 0x40900008,__READ_WRITE,__rtcrtsr_bits);
__IO_REG32_BIT(__RTC_RTTR, 0x4090000c,__READ_WRITE,__rtcrttr_bits);


/***************************************************************************
 **
 **  OST - operating system timer
 **
 ***************************************************************************/
__IO_REG32(__OST_OSMR0, 0x40a00000,__READ_WRITE);
__IO_REG32(__OST_OSMR1, 0x40a00004,__READ_WRITE);
__IO_REG32(__OST_OSMR2, 0x40a00008,__READ_WRITE);
__IO_REG32(__OST_OSMR3, 0x40a0000c,__READ_WRITE);
__IO_REG32(__OST_OSCR, 0x40a00010,__READ_WRITE);
__IO_REG32_BIT(__OST_OSSR, 0x40a00014,__READ_WRITE,__ostossr_bits);
__IO_REG32_BIT(__OST_OWER, 0x40a00018,__READ_WRITE,__ostower_bits);
__IO_REG32_BIT(__OST_OIER, 0x40a0001c,__READ_WRITE,__ostoier_bits);


/***************************************************************************
 **
 **  PWM - pulse width modulator
 **
 ***************************************************************************/
__IO_REG32_BIT(__PWM_CTRL0, 0x40b00000,__READ_WRITE,__pwmctrl_bits);
__IO_REG32_BIT(__PWM_PWDUTY0, 0x40b00004,__READ_WRITE,__pwmduty_bits);
__IO_REG32_BIT(__PWM_PERVAL0, 0x40b00008,__READ_WRITE,__pwmperval_bits);

__IO_REG32_BIT(__PWM_CTRL1, 0x40c00000,__READ_WRITE,__pwmctrl_bits);
__IO_REG32_BIT(__PWM_PWDUTY1, 0x40c00004,__READ_WRITE,__pwmduty_bits);
__IO_REG32_BIT(__PWM_PERVAL1, 0x40c00008,__READ_WRITE,__pwmperval_bits);


/***************************************************************************
 **
 **  IC - interrupt controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__IC_ICIP, 0x40d00000,__READ_WRITE,__icicip_bits);
__IO_REG32_BIT(__IC_ICMR, 0x40d00004,__READ_WRITE,__icicmr_bits);
__IO_REG32_BIT(__IC_ICLR, 0x40d00008,__READ_WRITE,__iciclr_bits);
__IO_REG32_BIT(__IC_ICFP, 0x40d0000c,__READ_WRITE,__icicfp_bits);
__IO_REG32_BIT(__IC_ICPR, 0x40d00010,__READ_WRITE,__icicpr_bits);
__IO_REG32_BIT(__IC_ICCR, 0x40d00014,__READ_WRITE,__iciccr_bits);


/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(__GPIO_GPLR0, 0x40e00000,__READ,__gpiogplr0_bits);
__IO_REG32_BIT(__GPIO_GPLR1, 0x40e00004,__READ,__gpiogplr1_bits);
__IO_REG32_BIT(__GPIO_GPLR2, 0x40e00008,__READ,__gpiogplr2_bits);

__IO_REG32_BIT(__GPIO_GPDR0, 0x40e0000c,__READ_WRITE,__gpiogpdr0_bits);
__IO_REG32_BIT(__GPIO_GPDR1, 0x40e00010,__READ_WRITE,__gpiogpdr1_bits);
__IO_REG32_BIT(__GPIO_GPDR2, 0x40e00014,__READ_WRITE,__gpiogpdr2_bits);

__IO_REG32_BIT(__GPIO_GPSR0, 0x40e00018,__READ_WRITE,__gpiogpsr0_bits);
__IO_REG32_BIT(__GPIO_GPSR1, 0x40e0001c,__READ_WRITE,__gpiogpsr1_bits);
__IO_REG32_BIT(__GPIO_GPSR2, 0x40e00020,__READ_WRITE,__gpiogpsr2_bits);

__IO_REG32_BIT(__GPIO_GPCR0, 0x40e00024,__READ_WRITE,__gpiogpcr0_bits);
__IO_REG32_BIT(__GPIO_GPCR1, 0x40e00028,__READ_WRITE,__gpiogpcr1_bits);
__IO_REG32_BIT(__GPIO_GPCR2, 0x40e0002c,__READ_WRITE,__gpiogpcr2_bits);

__IO_REG32_BIT(__GPIO_GPRER0, 0x40e00030,__READ_WRITE,__gpiogrer0_bits);
__IO_REG32_BIT(__GPIO_GPRER1, 0x40e00034,__READ_WRITE,__gpiogrer1_bits);
__IO_REG32_BIT(__GPIO_GPRER2, 0x40e00038,__READ_WRITE,__gpiogrer2_bits);

__IO_REG32_BIT(__GPIO_GPFER0, 0x40e0003c,__READ_WRITE,__gpiogfer0_bits);
__IO_REG32_BIT(__GPIO_GPFER1, 0x40e00040,__READ_WRITE,__gpiogfer1_bits);
__IO_REG32_BIT(__GPIO_GPFER2, 0x40e00044,__READ_WRITE,__gpiogfer2_bits);

__IO_REG32_BIT(__GPIO_GEDR0, 0x40e00048,__READ_WRITE,__gpiogedr0_bits);
__IO_REG32_BIT(__GPIO_GEDR1, 0x40e0004c,__READ_WRITE,__gpiogedr1_bits);
__IO_REG32_BIT(__GPIO_GEDR2, 0x40e00050,__READ_WRITE,__gpiogedr2_bits);

__IO_REG32_BIT(__GPIO_GAFR0_L, 0x40e00054,__READ_WRITE,__gpiogafr0l_bits);
__IO_REG32_BIT(__GPIO_GAFR0_U, 0x40e00058,__READ_WRITE,__gpiogafr0u_bits);
__IO_REG32_BIT(__GPIO_GAFR1_L, 0x40e0005c,__READ_WRITE,__gpiogafr1l_bits);
__IO_REG32_BIT(__GPIO_GAFR1_U, 0x40e00060,__READ_WRITE,__gpiogafr1u_bits);
__IO_REG32_BIT(__GPIO_GAFR2_L, 0x40e00064,__READ_WRITE,__gpiogafr2l_bits);
__IO_REG32_BIT(__GPIO_GAFR2_U, 0x40e00068,__READ_WRITE,__gpiogafr2u_bits);


/***************************************************************************
 **
 **  PM - power manager
 **
 ***************************************************************************/
__IO_REG32_BIT(__PM_PMCR, 0x40f00000,__READ_WRITE,__pmpmcr_bits);
__IO_REG32_BIT(__PM_PSSR, 0x40f00004,__READ_WRITE,__pmpssr_bits);
__IO_REG32(__PM_PSPR, 0x40f00008,__READ_WRITE);
__IO_REG32_BIT(__PM_PWER, 0x40f0000c,__READ_WRITE,__pmpwer_bits);
__IO_REG32_BIT(__PM_PRER, 0x40f00010,__READ_WRITE,__pmprer_bits);
__IO_REG32_BIT(__PM_PFER, 0x40f00014,__READ_WRITE,__pmpfer_bits);
__IO_REG32_BIT(__PM_PEDR, 0x40f00018,__READ_WRITE,__pmpedr_bits);
__IO_REG32_BIT(__PM_PCFR, 0x40f0001c,__READ_WRITE,__pmpcfr_bits);
__IO_REG32_BIT(__PM_PGSR0, 0x40f00020,__READ_WRITE,__pmpgsr0_bits);
__IO_REG32_BIT(__PM_PGSR1, 0x40f00024,__READ_WRITE,__pmpgsr1_bits);
__IO_REG32_BIT(__PM_PGSR2, 0x40f00028,__READ_WRITE,__pmpgsr2_bits);

__IO_REG32_BIT(__PM_RCSR, 0x40f00030,__READ_WRITE,__pmrcsr_bits);


/***************************************************************************
 **
 **  SSP - serial port unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__SSP_SSCR0, 0x41000000,__READ_WRITE,__sspsscr0_bits);
__IO_REG32_BIT(__SSP_SSCR1, 0x41000004,__READ_WRITE,__sspsscr1_bits);
__IO_REG32_BIT(__SSP_SSSR, 0x41000008,__READ_WRITE,__sspsssr_bits);
__IO_REG32_BIT(__SSP_SSDR, 0x41000010,__READ_WRITE,__sspssdr_bits);


/***************************************************************************
 **
 **  MMC - multimedia card controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__MMC_STRPCL, 0x41100000,__READ_WRITE,__mmcstrpcl_bits);
__IO_REG32_BIT(__MMC_STAT, 0x41100004,__READ,__mmcstat_bits);
__IO_REG32_BIT(__MMC_CLKRT, 0x41100008,__READ_WRITE,__mmcclkrt_bits);
__IO_REG32_BIT(__MMC_SPI, 0x4110000c,__READ_WRITE,__mmcspi_bits);
__IO_REG32_BIT(__MMC_CMDAT, 0x41100010,__READ_WRITE,__mmccmdat_bits);
__IO_REG32_BIT(__MMC_RESTO, 0x41100014,__READ_WRITE,__mmcresto_bits);
__IO_REG32_BIT(__MMC_RDTO, 0x41100018,__READ_WRITE,__mmcrdto_bits);
__IO_REG32_BIT(__MMC_BLKLEN, 0x4110001c,__READ_WRITE,__mmcblklen_bits);
__IO_REG32_BIT(__MMC_NOB, 0x41100020,__READ_WRITE,__mmcnob_bits);
__IO_REG32_BIT(__MMC_PRTBUF, 0x41100024,__READ_WRITE,__mmcprtbuf_bits);
__IO_REG32_BIT(__MMC_I_MASK, 0x41100028,__READ_WRITE,__mmcimr_bits);
__IO_REG32_BIT(__MMC_I_REG, 0x4110002c,__READ,__mmcimr_bits);
__IO_REG32_BIT(__MMC_CMD, 0x41100030,__READ_WRITE,__mmccmd_bits);
__IO_REG32_BIT(__MMC_ARGH, 0x41100034,__READ_WRITE,__mmcargh_bits);
__IO_REG32_BIT(__MMC_ARGL, 0x41100038,__READ_WRITE,__mmcargl_bits);
__IO_REG32_BIT(__MMC_RES, 0x4110003c,__READ,__mmcres_bits);
__IO_REG32_BIT(__MMC_RXFIFO, 0x41100040,__READ,__mmcrxfifo_bits);
__IO_REG32_BIT(__MMC_TXFIFO, 0x41100044,__READ,__mmctxfifo_bits);


/***************************************************************************
 **
 **  CL - clock manager
 **
 ***************************************************************************/
__IO_REG32_BIT(__CL_CCCR, 0x41300000,__READ_WRITE,__clcccr_bits);
__IO_REG32_BIT(__CL_CKEN, 0x41300004,__READ_WRITE,__clcken_bits);
__IO_REG32_BIT(__CL_OSCC, 0x41300008,__READ_WRITE,__closcc_bits);


/***************************************************************************
 **
 **  LCD - LCD controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__LCD_LCCR0, 0x44000000,__READ_WRITE,__lcdlccr0_bits);
__IO_REG32_BIT(__LCD_LCCR1, 0x44000004,__READ_WRITE,__lcdlccr1_bits);
__IO_REG32_BIT(__LCD_LCCR2, 0x44000008,__READ_WRITE,__lcdlccr2_bits);
__IO_REG32_BIT(__LCD_LCCR3, 0x4400000c,__READ_WRITE,__lcdlccr3_bits);

__IO_REG32_BIT(__LCD_FBR0, 0x44000020,__READ_WRITE,__lcdfbr_bits);
__IO_REG32_BIT(__LCD_FBR1, 0x44000024,__READ_WRITE,__lcdfbr_bits);

__IO_REG32_BIT(__LCD_LCSR, 0x44000038,__READ_WRITE,__lcdlcsr_bits);
__IO_REG32_BIT(__LCD_LIIDR, 0x4400003c,__READ_WRITE,__lcdliidr_bits);
__IO_REG32_BIT(__LCD_TRGBR, 0x44000040,__READ_WRITE,__lcdtrgbr_bits);
__IO_REG32_BIT(__LCD_TCR, 0x44000044,__READ_WRITE,__lcdtcr_bits);

__IO_REG32(__LCD_FDADR0, 0x44000200,__READ_WRITE);
__IO_REG32(__LCD_FSADR0, 0x44000204,__READ_WRITE);
__IO_REG32_BIT(__LCD_FIDR0, 0x44000208,__READ_WRITE,__lcdfidr_bits);
__IO_REG32_BIT(__LCD_LDCMD0, 0x4400020c,__READ_WRITE,__lcdldcmd_bits);

__IO_REG32(__LCD_FDADR1, 0x44000210,__READ_WRITE);
__IO_REG32(__LCD_FSADR1, 0x44000214,__READ_WRITE);
__IO_REG32_BIT(__LCD_FIDR1, 0x44000218,__READ_WRITE,__lcdfidr_bits);
__IO_REG32_BIT(__LCD_LDCMD1, 0x4400021c,__READ_WRITE,__lcdldcmd_bits);


/***************************************************************************
 **
 **  MC - memory controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__MC_MDCNFG, 0x48000000,__READ_WRITE,__mcmdcnfg_bits);
__IO_REG32_BIT(__MC_MDREFR, 0x48000004,__READ_WRITE,__mcmdrefr_bits);
__IO_REG32_BIT(__MC_MSC0, 0x48000008,__READ_WRITE,__mcmsc0_bits);
__IO_REG32_BIT(__MC_MSC1, 0x4800000c,__READ_WRITE,__mcmsc1_bits);
__IO_REG32_BIT(__MC_MSC2, 0x48000010,__READ_WRITE,__mcmsc2_bits);
__IO_REG32_BIT(__MC_MECR, 0x48000014,__READ_WRITE,__mcmecr_bits);
__IO_REG32_BIT(__MC_SXCNFG, 0x4800001c,__READ_WRITE,__mcsxcnfg_bits);
__IO_REG32_BIT(__MC_SXMRS, 0x48000024,__READ_WRITE,__mcsxmrs_bits);
__IO_REG32_BIT(__MC_MCMEM0, 0x48000028,__READ_WRITE,__mcmcmem_bits);
__IO_REG32_BIT(__MC_MCMEM1, 0x4800002c,__READ_WRITE,__mcmcmem_bits);
__IO_REG32_BIT(__MC_MCATT0, 0x48000030,__READ_WRITE,__mcmcatt_bits);
__IO_REG32_BIT(__MC_MCATT1, 0x48000034,__READ_WRITE,__mcmcatt_bits);
__IO_REG32_BIT(__MC_MCIO0, 0x48000038,__READ_WRITE,__mcmcio_bits);
__IO_REG32_BIT(__MC_MCIO1, 0x4800003c,__READ_WRITE,__mcmcio_bits);
__IO_REG32_BIT(__MC_MDMRS, 0x48000040,__READ_WRITE,__mcmdmrs_bits);
__IO_REG32_BIT(__MC_BOOT_DEF, 0x48000044,__READ,__mcbootdef_bits);


/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

#endif    /* __IOPXA250_H */
