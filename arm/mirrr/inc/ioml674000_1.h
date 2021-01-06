/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Oki Semiconductors ML674000
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.7 $
 **                                
 ***************************************************************************/

#ifndef __ML674000_H
#define __ML674000_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4f = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    ML674000 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Remap control register */
typedef struct {
  __REG32 RMPM    :4;
  __REG32         :28;
} __rmpcon_bits;


/* Block control register */
typedef struct {
  __REG16 BCKCTL0      :1;
  __REG16 BCKCTL1      :1;
  __REG16 BCKCTL2      :1;
  __REG16 BCKCTL3      :1;
  __REG16 BCKCTL4      :1;
  __REG16 BCKCTL5      :1;
  __REG16 BCKCTL6      :1;
  __REG16 BCKCTL7      :1;
  __REG16 BCKCTL8      :1;
  __REG16 BCKCTL9      :1;
  __REG16 BCKCTL10     :1;
  __REG16              :5;
} __bckctl_bits;

/* Clock stop register */
typedef struct {
  __REG32 SIO   :1;
  __REG32 TIC   :1;
  __REG32 HALT  :1;
  __REG32       :4;
  __REG32 STBY  :1;
  __REG32       :24;
} __clkstp_bits;

/* Clock gear control register */
typedef struct {
  __REG32 HCLKSEL :3;
  __REG32         :1;
  __REG32 CCLKSEL :3;
  __REG32         :25;
} __cgbcnt0_bits;

/* Clock wait register */
typedef struct {
  __REG32 CKWT    :4;
  __REG32         :28;
} __ckwt_bits;


/* IRQ register */
typedef struct {
  __REG32 IRQ0  :1;
  __REG32 IRQ1  :1;
  __REG32 IRQ2  :1;
  __REG32 IRQ3  :1;
  __REG32 IRQ4  :1;
  __REG32 IRQ5  :1;
  __REG32 IRQ6  :1;
  __REG32 IRQ7  :1;
  __REG32 IRQ8  :1;
  __REG32 IRQ9  :1;
  __REG32 IRQ10 :1;
  __REG32 IRQ11 :1;
  __REG32 IRQ12 :1;
  __REG32 IRQ13 :1;
  __REG32 IRQ14 :1;
  __REG32 IRQ15 :1;
  __REG32       :16;
} __irq_bits;

/* Software interrupt register, IRQS */
typedef struct {
  __REG32       :1;
  __REG32 IRQS  :1;
  __REG32       :30;
} __irqs_bits;

/* FIQ register */
typedef struct {
  __REG32 FIQ   :1;
  __REG32       :31;
} __fiq_bits;

/* FIQRAW register */
typedef struct {
  __REG32 FIQRAW :1;
  __REG32        :31;
} __fiqraw_bits;

/* FIQ enable register */
typedef struct {
  __REG32 FIQEN :1;
  __REG32       :31;
} __fiqen_bits;

/* IRQ number register */
typedef struct {
  __REG32 IRN   :7;
  __REG32       :25;
} __irn_bits;

/* Current interrupt level register */
typedef struct {
  __REG32       :1;
  __REG32 CIL1  :1;
  __REG32 CIL2  :1;
  __REG32 CIL3  :1;
  __REG32 CIL4  :1;
  __REG32 CIL5  :1;
  __REG32 CIL6  :1;
  __REG32 CIL7  :1;
  __REG32       :24;
} __cil_bits;

/* Interrupt level control register 0*/
typedef struct {
  __REG32 ILR0  :3;
  __REG32       :1;
  __REG32 ILR1  :3;
  __REG32       :9;
  __REG32 ILR4  :3;
  __REG32       :5;
  __REG32 ILR6  :3;
  __REG32       :5;
} __ilc0_bits;

/* Interrupt level control register 1*/
typedef struct {
  __REG32 ILR8  :3;
  __REG32       :1;
  __REG32 ILR9  :3;
  __REG32       :1;
  __REG32 ILR10 :3;
  __REG32       :1;
  __REG32 ILR11 :3;
  __REG32       :1;
  __REG32 ILR12 :3;
  __REG32       :1;
  __REG32 ILR13 :3;
  __REG32       :1;
  __REG32 ILR14 :3;
  __REG32       :1;
  __REG32 ILR15 :3;
  __REG32       :1;
} __ilc1_bits;

/* Current interrupt level encode register */
typedef struct {
  __REG32 CILE  :3;
  __REG32       :29;
} __cile_bits;

/* IRQ clear register */
typedef struct {
  __REG32 IRCL0 :1;
  __REG32 IRCL1 :1;
  __REG32 IRCL2 :1;
  __REG32 IRCL3 :1;
  __REG32 IRCL4 :1;
  __REG32 IRCL5 :1;
  __REG32 IRCL6 :1;
  __REG32       :25;
} __ircl_bits;

/* IRQA register */
typedef struct {
  __REG32 IRQ16 :1;
  __REG32 IRQ17 :1;
  __REG32 IRQ18 :1;
  __REG32 IRQ19 :1;
  __REG32 IRQ20 :1;
  __REG32 IRQ21 :1;
  __REG32 IRQ22 :1;
  __REG32 IRQ23 :1;
  __REG32 IRQ24 :1;
  __REG32 IRQ25 :1;
  __REG32 IRQ26 :1;
  __REG32 IRQ27 :1;
  __REG32 IRQ28 :1;
  __REG32 IRQ29 :1;
  __REG32 IRQ30 :1;
  __REG32 IRQ31 :1;
  __REG32       :16;
} __irqa_bits;

/* IDM register */
typedef struct {
  __REG32        :12;
  __REG32 IDM28  :1;
  __REG32 IDMP28 :1;
  __REG32 IDM30  :1;
  __REG32 IDMP30 :1;
  __REG32        :16;
} __idm_bits;

/* Interrupt level control register, ILC */
typedef struct {
  __REG32 ILC16 :3;
  __REG32       :1;
  __REG32 ILC18 :3;
  __REG32       :1;
  __REG32 ILC20 :3;
  __REG32       :1;
  __REG32 ILC22 :3;
  __REG32       :1;
  __REG32 ILC24 :3;
  __REG32       :1;
  __REG32 ILC26 :3;
  __REG32       :1;
  __REG32 ILC28 :3;
  __REG32       :1;
  __REG32 ILC30 :3;
  __REG32       :1;
} __ilc_bits;


/* Bus width control register */
typedef struct {
  __REG32         :2;
  __REG32 ROMBW   :2;
  __REG32 RAMBW   :2;
  __REG32 IO0BW   :2;
  __REG32 IO1BW   :2;
  __REG32         :22;
} __bwc_bits;

/* External ROM access control register */
typedef struct {
  __REG32 ROMTYPE :3;
  __REG32         :29;
} __romac_bits;

/* External RAM access control register */
typedef struct {
  __REG32 RAMTYPE :3;
  __REG32         :29;
} __ramac_bits;

/* External I/O bank 0 access control register */
typedef struct {
  __REG32 IO0TYPE  :3;
  __REG32          :29;
} __io0ac_bits;

/* External I/O bank 1 access control register */
typedef struct {
  __REG32 IO1TYPE  :3;
  __REG32          :29;
} __io1ac_bits;

/* DRAM bus width control register */
typedef struct {
  __REG32 BWDRAM   :2;
  __REG32          :30;
} __dbwc_bits;

/* DRAM control register */
typedef struct {
  __REG32 AMUX     :2;
  __REG32 ARCH     :1;
  __REG32          :1;
  __REG32 PRELA    :1;
  __REG32          :1;
  __REG32 PDWN     :1;
  __REG32 RFRSH    :1;
  __REG32          :24;
} __drmc_bits;

/* DRAM characteristics control register */
typedef struct {
  __REG32 DRAMSPEC :4;
  __REG32          :28;
} __drpc_bits;

/* SDRAM mode register */
typedef struct {
  __REG32 LTMODE   :1;
  __REG32          :6;
  __REG32 MODEWR   :1;
  __REG32          :24;
} __sdmd_bits;

/* DRAM command register */
typedef struct {
  __REG32 DRCMD    :3;
  __REG32          :29;
} __dcmd_bits;

/* DRAM refresh cycle control register 0 */
typedef struct {
  __REG32 RCCON    :1;
  __REG32          :31;
} __rfsh0_bits;

/* DRAM refresh cycle control register 1 */
typedef struct {
  __REG32 RFSEL1   :11;
  __REG32          :21;
} __rfsh1_bits;

/* DRAM power down control register */
typedef struct {
  __REG32 PDCNT    :4;
  __REG32          :28;
} __rdwc_bits;


/* DMA mode register */
typedef struct {
  __REG32 PRI      :1;
  __REG32          :31;
} __dmamod_bits;

/* DMA status register */
typedef struct {
  __REG32 STA0     :1;
  __REG32 STA1     :1;
  __REG32          :30;
} __dmasta_bits;

/* DMA transfer complete status register */
typedef struct {
  __REG32 IREQ0    :1;
  __REG32 IREQ1    :1;
  __REG32          :6;
  __REG32 ISTA0    :1;
  __REG32 ISTA1    :1;
  __REG32          :6;
  __REG32 ISTP0    :1;
  __REG32 ISTP1    :1;
  __REG32          :14;
} __dmaint_bits;

/* DMA channel mask register */
typedef struct {
  __REG32 MSK      :1;
  __REG32          :31;
} __dmacmsk_bits;

/* DMA transfer mode register */
typedef struct {
  __REG32 ARQ      :1;
  __REG32 TSIZ     :2;
  __REG32 SDP      :1;
  __REG32 DDP      :1;
  __REG32 BRQ      :1;
  __REG32 IMK      :1;
  __REG32          :25;
} __dmactmod_bits;

/* DMA transfer count register */
typedef struct {
  __REG32 CSIZ     :17;
  __REG32          :15;
} __dmacsiz_bits;

/* GPIO port A output registers */
typedef struct {
  __REG16 GPPOA0     :1;
  __REG16 GPPOA1     :1;
  __REG16 GPPOA2     :1;
  __REG16 GPPOA3     :1;
  __REG16 GPPOA4     :1;
  __REG16 GPPOA5     :1;
  __REG16 GPPOA6     :1;
  __REG16 GPPOA7     :1;
  __REG16 GPPOA8     :1;
  __REG16 GPPOA9     :1;
  __REG16 GPPOA10    :1;
  __REG16 GPPOA11    :1;
  __REG16 GPPOA12    :1;
  __REG16 GPPOA13    :1;
  __REG16 GPPOA14    :1;
  __REG16 GPPOA15    :1;
} __gppoa_bits;

/* GPIO port A input registers */
typedef struct {
  __REG16 GPPIA0     :1;
  __REG16 GPPIA1     :1;
  __REG16 GPPIA2     :1;
  __REG16 GPPIA3     :1;
  __REG16 GPPIA4     :1;
  __REG16 GPPIA5     :1;
  __REG16 GPPIA6     :1;
  __REG16 GPPIA7     :1;
  __REG16 GPPIA8     :1;
  __REG16 GPPIA9     :1;
  __REG16 GPPIA10    :1;
  __REG16 GPPIA11    :1;
  __REG16 GPPIA12    :1;
  __REG16 GPPIA13    :1;
  __REG16 GPPIA14    :1;
  __REG16 GPPIA15    :1;
} __gppia_bits;

/* GPIO port A mode registers */
typedef struct {
  __REG16 GPPMA0     :1;
  __REG16 GPPMA1     :1;
  __REG16 GPPMA2     :1;
  __REG16 GPPMA3     :1;
  __REG16 GPPMA4     :1;
  __REG16 GPPMA5     :1;
  __REG16 GPPMA6     :1;
  __REG16 GPPMA7     :1;
  __REG16 GPPMA8     :1;
  __REG16 GPPMA9     :1;
  __REG16 GPPMA10    :1;
  __REG16 GPPMA11    :1;
  __REG16 GPPMA12    :1;
  __REG16 GPPMA13    :1;
  __REG16 GPPMA14    :1;
  __REG16 GPPMA15    :1;
} __gppma_bits;

/* GPIO port A interrupt enable registers */
typedef struct {
  __REG16 GPIEA0     :1;
  __REG16 GPIEA1     :1;
  __REG16 GPIEA2     :1;
  __REG16 GPIEA3     :1;
  __REG16 GPIEA4     :1;
  __REG16 GPIEA5     :1;
  __REG16 GPIEA6     :1;
  __REG16 GPIEA7     :1;
  __REG16 GPIEA8     :1;
  __REG16 GPIEA9     :1;
  __REG16 GPIEA10    :1;
  __REG16 GPIEA11    :1;
  __REG16 GPIEA12    :1;
  __REG16 GPIEA13    :1;
  __REG16 GPIEA14    :1;
  __REG16 GPIEA15    :1;
} __gpiea_bits;

/* GPIO port A interrupt polarity registers */
typedef struct {
  __REG16 GPIPA0     :1;
  __REG16 GPIPA1     :1;
  __REG16 GPIPA2     :1;
  __REG16 GPIPA3     :1;
  __REG16 GPIPA4     :1;
  __REG16 GPIPA5     :1;
  __REG16 GPIPA6     :1;
  __REG16 GPIPA7     :1;
  __REG16 GPIPA8     :1;
  __REG16 GPIPA9     :1;
  __REG16 GPIPA10    :1;
  __REG16 GPIPA11    :1;
  __REG16 GPIPA12    :1;
  __REG16 GPIPA13    :1;
  __REG16 GPIPA14    :1;
  __REG16 GPIPA15    :1;
} __gpipa_bits;

/* GPIO port A interrupt status registers */
typedef struct {
  __REG16 GPISA0     :1;
  __REG16 GPISA1     :1;
  __REG16 GPISA2     :1;
  __REG16 GPISA3     :1;
  __REG16 GPISA4     :1;
  __REG16 GPISA5     :1;
  __REG16 GPISA6     :1;
  __REG16 GPISA7     :1;
  __REG16 GPISA8     :1;
  __REG16 GPISA9     :1;
  __REG16 GPISA10    :1;
  __REG16 GPISA11    :1;
  __REG16 GPISA12    :1;
  __REG16 GPISA13    :1;
  __REG16 GPISA14    :1;
  __REG16 GPISA15    :1;
} __gpisa_bits;

/* GPIO port B output registers */
typedef struct {
  __REG16 GPPOB0     :1;
  __REG16 GPPOB1     :1;
  __REG16 GPPOB2     :1;
  __REG16 GPPOB3     :1;
  __REG16 GPPOB4     :1;
  __REG16 GPPOB5     :1;
  __REG16 GPPOB6     :1;
  __REG16 GPPOB7     :1;
  __REG16 GPPOB8     :1;
  __REG16 GPPOB9     :1;
  __REG16 GPPOB10    :1;
  __REG16 GPPOB11    :1;
  __REG16 GPPOB12    :1;
  __REG16 GPPOB13    :1;
  __REG16 GPPOB14    :1;
  __REG16 GPPOB15    :1;
} __gppob_bits;

/* GPIO port B input registers */
typedef struct {
  __REG16 GPPIB0     :1;
  __REG16 GPPIB1     :1;
  __REG16 GPPIB2     :1;
  __REG16 GPPIB3     :1;
  __REG16 GPPIB4     :1;
  __REG16 GPPIB5     :1;
  __REG16 GPPIB6     :1;
  __REG16 GPPIB7     :1;
  __REG16 GPPIB8     :1;
  __REG16 GPPIB9     :1;
  __REG16 GPPIB10    :1;
  __REG16 GPPIB11    :1;
  __REG16 GPPIB12    :1;
  __REG16 GPPIB13    :1;
  __REG16 GPPIB14    :1;
  __REG16 GPPIB15    :1;
} __gppib_bits;

/* GPIO port B mode registers */
typedef struct {
  __REG16 GPPMB0     :1;
  __REG16 GPPMB1     :1;
  __REG16 GPPMB2     :1;
  __REG16 GPPMB3     :1;
  __REG16 GPPMB4     :1;
  __REG16 GPPMB5     :1;
  __REG16 GPPMB6     :1;
  __REG16 GPPMB7     :1;
  __REG16 GPPMB8     :1;
  __REG16 GPPMB9     :1;
  __REG16 GPPMB10    :1;
  __REG16 GPPMB11    :1;
  __REG16 GPPMB12    :1;
  __REG16 GPPMB13    :1;
  __REG16 GPPMB14    :1;
  __REG16 GPPMB15    :1;
} __gppmb_bits;

/* GPIO port B interrupt enable registers */
typedef struct {
  __REG16 GPIEB0     :1;
  __REG16 GPIEB1     :1;
  __REG16 GPIEB2     :1;
  __REG16 GPIEB3     :1;
  __REG16 GPIEB4     :1;
  __REG16 GPIEB5     :1;
  __REG16 GPIEB6     :1;
  __REG16 GPIEB7     :1;
  __REG16 GPIEB8     :1;
  __REG16 GPIEB9     :1;
  __REG16 GPIEB10    :1;
  __REG16 GPIEB11    :1;
  __REG16 GPIEB12    :1;
  __REG16 GPIEB13    :1;
  __REG16 GPIEB14    :1;
  __REG16 GPIEB15    :1;
} __gpieb_bits;

/* GPIO port B interrupt polarity registers */
typedef struct {
  __REG16 GPIPB0     :1;
  __REG16 GPIPB1     :1;
  __REG16 GPIPB2     :1;
  __REG16 GPIPB3     :1;
  __REG16 GPIPB4     :1;
  __REG16 GPIPB5     :1;
  __REG16 GPIPB6     :1;
  __REG16 GPIPB7     :1;
  __REG16 GPIPB8     :1;
  __REG16 GPIPB9     :1;
  __REG16 GPIPB10    :1;
  __REG16 GPIPB11    :1;
  __REG16 GPIPB12    :1;
  __REG16 GPIPB13    :1;
  __REG16 GPIPB14    :1;
  __REG16 GPIPB15    :1;
} __gpipb_bits;

/* GPIO port B interrupt status registers */
typedef struct {
  __REG16 GPISB0     :1;
  __REG16 GPISB1     :1;
  __REG16 GPISB2     :1;
  __REG16 GPISB3     :1;
  __REG16 GPISB4     :1;
  __REG16 GPISB5     :1;
  __REG16 GPISB6     :1;
  __REG16 GPISB7     :1;
  __REG16 GPISB8     :1;
  __REG16 GPISB9     :1;
  __REG16 GPISB10    :1;
  __REG16 GPISB11    :1;
  __REG16 GPISB12    :1;
  __REG16 GPISB13    :1;
  __REG16 GPISB14    :1;
  __REG16 GPISB15    :1;
} __gpisb_bits;

/* GPIO port function select register */
typedef struct {
  __REG16 GPCTL0      :1;
  __REG16 GPCTL1      :1;
  __REG16 GPCTL2      :1;
  __REG16 GPCTL3      :1;
  __REG16 GPCTL4      :1;
  __REG16 GPCTL5      :1;
  __REG16 GPCTL6      :1;
  __REG16 GPCTL7      :1;
  __REG16             :8;
} __gpctl_bits;


/* WDT time base counter control register */
typedef struct {
  __REG8 WDCLK     :2;
  __REG8           :1;
  __REG8 ITM       :1;
  __REG8 ITEN      :1;
  __REG8           :1;
  __REG8 OFINTM    :1;
  __REG8 WDHLT     :1;
} __wdtbcon_bits;

/* WDT status register */
typedef struct {
  __REG8 RSTSTATUS :1;
  __REG8           :3;
  __REG8 WDTIST    :1;
  __REG8 IVTIST    :1;
  __REG8           :2;
} __wdstat_bits;


/* System timer enable register */
typedef struct {
  __REG32 TCEN     :1;
  __REG32          :31;
} __tmen_bits;

/* System timer reload register */
typedef struct {
  __REG32 TMRLR    :16;
  __REG32          :16;
} __tmrlr_bits;

/* System timer overflow register */
typedef struct {
  __REG32 OVF      :1;
  __REG32          :31;
} __tmovfr_bits;

/* Timer control register */
typedef struct {
  __REG16 MODE     :1;
  __REG16          :2;
  __REG16 START    :1;
  __REG16 IE       :1;
  __REG16 CLKSEL   :3;
  __REG16          :8;
} __timecntl_bits;

/* Timer status register */
typedef struct {
  __REG16 STATUS   :1;
  __REG16          :15;
} __timestat_bits;


/* PWM0 control register */
typedef struct {
  __REG16 PW0R     :1;
  __REG16 PWCK0    :2;
  __REG16          :3;
  __REG16 INTIE0   :1;
  __REG16 PWC0OV   :1;
  __REG16          :8;
} __pwcon0_bits;

/* PWM1 control register */
typedef struct {
  __REG16 PW1R     :1;
  __REG16 PWCK1    :2;
  __REG16          :3;
  __REG16 INTIE1   :1;
  __REG16 PWC1OV   :1;
  __REG16          :8;
} __pwcon1_bits;

/* PWM interrupt status register */
typedef struct {
  __REG16 INT0CLR  :1;
  __REG16 INT1CLR  :1;
  __REG16          :6;
  __REG16 INT0S    :1;
  __REG16 INT1S    :1;
  __REG16          :6;
} __pwintsts_bits;


/* SIO transfer buffer register */
typedef struct {
  __REG32 SIOBUF   :8;
  __REG32          :24;
} __siobuf_bits;

/* SIO status register */
typedef struct {
  __REG32 FERR     :1;
  __REG32 OERR     :1;
  __REG32 PERR     :1;
  __REG32          :1;
  __REG32 RVIRQ    :1;
  __REG32 TRIRQ    :1;
  __REG32          :26;
} __siosta_bits;

/* SIO control register */
typedef struct {
  __REG32 LN       :1;
  __REG32 PEN      :1;
  __REG32 EVN      :1;
  __REG32 TSTB     :1;
  __REG32          :28;
} __siocon_bits;

/* SIO baud rate control register */
typedef struct {
  __REG32          :4;
  __REG32 BGRUN    :1;
  __REG32          :27;
} __siobcn_bits;

/* SIO baud rate timer register */
typedef struct {
  __REG32 SIOBT    :8;
  __REG32          :24;
} __siobt_bits;

/* SIO baud rate timer register */
typedef struct {
  __REG32 MFERR    :1;
  __REG32 WPERR    :1;
  __REG32          :5;
  __REG32 LBTST    :1;
  __REG32          :24;
} __siotcn_bits;


/* UART interrupt enable register */
typedef struct {
  __REG8 IER0      :1;
  __REG8 IER1      :1;
  __REG8 IER2      :1;
  __REG8 IER3      :1;
  __REG8           :4;
} __uartier_bits;

/* UART interrupt identification register and fifo control register */
typedef union {
  //UARTIIR
  struct {
    __REG8 IIR0      :1;
    __REG8 IIR31     :3;
    __REG8           :2;
    __REG8 IIR76     :2;
  };
  //UARTFCR
  struct {
    __REG8 FCR0      :1;
    __REG8 FCR1      :1;
    __REG8 FCR2      :1;
    __REG8 FCR3      :1;
    __REG8           :2;
    __REG8 FCR76     :2;
  };
} __uartfcriir_bits;

/* UART line control register */
typedef struct {
  __REG8 LCR10     :2;
  __REG8 LCR2      :1;
  __REG8 LCR3      :1;
  __REG8 LCR4      :1;
  __REG8 LCR5      :1;
  __REG8 LCR6      :1;
  __REG8 LCR7      :1;
} __uartlcr_bits;

/* UART modem control register */
typedef struct {
  __REG8 MCR0      :1;
  __REG8 MCR1      :1;
  __REG8           :2;
  __REG8 MCR4      :1;
  __REG8           :3;
} __uartmcr_bits;

/* UART line status register */
typedef struct {
  __REG8 LSR0      :1;
  __REG8 LSR1      :1;
  __REG8 LSR2      :1;
  __REG8 LSR3      :1;
  __REG8 LSR4      :1;
  __REG8 LSR5      :1;
  __REG8 LSR6      :1;
  __REG8 LSR7      :1;
} __uartlsr_bits;

/* UART modem status register */
typedef union {
  //UARTMSR
  struct {
  __REG8 DCTS      :1;
  __REG8 DDSR      :1;
  __REG8 TERI      :1;
  __REG8 DDCD      :1;
  __REG8 CTS       :1;
  __REG8 DSR       :1;
  __REG8 RI        :1;
  __REG8 DCD       :1;
  };
  //UARTMSR
  struct {
  __REG8 MSR0      :1;
  __REG8 MSR1      :1;
  __REG8 MSR2      :1;
  __REG8 MSR3      :1;
  __REG8 MSR4      :1;
  __REG8 MSR5      :1;
  __REG8 MSR6      :1;
  __REG8 MSR7      :1;
  };
} __uartmsr_bits;


/* ADC control register 0 */
typedef struct {
  __REG16 ADSNM    :3;
  __REG16          :1;
  __REG16 ADRUN    :1;
  __REG16          :1;
  __REG16 SCNC     :1;
  __REG16          :9;
} __adcon0_bits;

/* ADC control register 1 */
typedef struct {
  __REG16 ADSTM    :3;
  __REG16          :1;
  __REG16 STS      :1;
  __REG16          :11;
} __adcon1_bits;

/* ADC control register 2 */
typedef struct {
  __REG16 ACKSEL   :2;
  __REG16          :14;
} __adcon2_bits;

/* ADC interrupt control register */
typedef struct {
  __REG16 INTSN    :1;
  __REG16 INTST    :1;
  __REG16 ADSNIE   :1;
  __REG16 ADSTIE   :1;
  __REG16          :12;
} __adint_bits;

/* ADC forced interrupt register */
typedef struct {
  __REG16 ADFAS    :1;
  __REG16          :15;
} __adfint_bits;

/* ADC result register 0 */
typedef struct {
  __REG16 DT0      :10;
  __REG16          :6;
} __adr0_bits;

/* ADC result register 1 */
typedef struct {
  __REG16 DT1      :10;
  __REG16          :6;
} __adr1_bits;

/* ADC result register 2 */
typedef struct {
  __REG16 DT2      :10;
  __REG16          :6;
} __adr2_bits;

/* ADC result register 3 */
typedef struct {
  __REG16 DT3      :10;
  __REG16          :6;
} __adr3_bits;

/* ADC result register 4 */
typedef struct {
  __REG16 DT4      :10;
  __REG16          :6;
} __adr4_bits;

/* ADC result register 5 */
typedef struct {
  __REG16 DT5      :10;
  __REG16          :6;
} __adr5_bits;

/* ADC result register 6 */
typedef struct {
  __REG16 DT6      :10;
  __REG16          :6;
} __adr6_bits;

/* ADC result register 7 */
typedef struct {
  __REG16 DT7      :10;
  __REG16          :6;
} __adr7_bits;



#endif    /* __IAR_SYSTEMS_ICC__ */



/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  Address mapping
 **
 ***************************************************************************/
__IO_REG32_BIT(RMPCON, 0xB8000010,__READ_WRITE,__rmpcon_bits);


/***************************************************************************
 **
 **  Power management
 **
 ***************************************************************************/
__IO_REG16_BIT(BCKCTL,  0xB7000004,__READ_WRITE,__bckctl_bits);
__IO_REG32_BIT(CLKSTP,  0xB8000004,__READ_WRITE,__clkstp_bits);
__IO_REG32_BIT(CGBCNT0, 0xB8000008,__READ_WRITE,__cgbcnt0_bits);
__IO_REG32_BIT(CKWT,    0xB800000C,__READ_WRITE,__ckwt_bits);


/***************************************************************************
 **
 **  Interrupt controller
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQ,    0x78000000,__READ,__irq_bits);
__IO_REG32_BIT(IRQS,   0x78000004,__READ_WRITE,__irqs_bits);
__IO_REG32_BIT(FIQ,    0x78000008,__READ,__fiq_bits);
__IO_REG32_BIT(FIQRAW, 0x7800000C,__READ,__fiqraw_bits);
__IO_REG32_BIT(FIQEN,  0x78000010,__READ_WRITE,__fiqen_bits);
__IO_REG32_BIT(IRN,    0x78000014,__READ,__irn_bits);
__IO_REG32_BIT(CIL,    0x78000018,__READ_WRITE,__cil_bits);
__IO_REG32_BIT(ILC0,   0x78000020,__READ_WRITE,__ilc0_bits);
__IO_REG32_BIT(ILC1,   0x78000024,__READ_WRITE,__ilc1_bits);
__IO_REG32(CILCL, 0x78000028,__WRITE);
__IO_REG32_BIT(CILE,   0x7800002C,__READ,__cile_bits);
__IO_REG32_BIT(IRCL,   0x7BF00004,__WRITE,__ircl_bits);
__IO_REG32_BIT(IRQA,   0x7BF00010,__READ_WRITE,__irqa_bits);
__IO_REG32_BIT(IDM,    0x7BF00014,__READ_WRITE,__idm_bits);
__IO_REG32_BIT(ILC,    0x7BF00018,__READ_WRITE,__ilc_bits);


/***************************************************************************
 **
 **  External memory controller
 **
 ***************************************************************************/
__IO_REG32_BIT(BWC,    0x78100000,__READ_WRITE,__bwc_bits);
__IO_REG32_BIT(ROMAC,  0x78100004,__READ_WRITE,__romac_bits);
__IO_REG32_BIT(RAMAC,  0x78100008,__READ_WRITE,__ramac_bits);
__IO_REG32_BIT(IO0AC,  0x7810000C,__READ_WRITE,__io0ac_bits);
__IO_REG32_BIT(IO1AC,  0x78100010,__READ_WRITE,__io1ac_bits);
__IO_REG32_BIT(DBWC,   0x78180000,__READ_WRITE,__dbwc_bits);
__IO_REG32_BIT(DRMC,   0x78180004,__READ_WRITE,__drmc_bits);
__IO_REG32_BIT(DRPC,   0x78180008,__READ_WRITE,__drpc_bits);
__IO_REG32_BIT(SDMD,   0x7818000C,__READ_WRITE,__sdmd_bits);
__IO_REG32_BIT(DCMD,   0x78180010,__READ_WRITE,__dcmd_bits);
__IO_REG32_BIT(RFSH0,  0x78180014,__READ_WRITE,__rfsh0_bits);
__IO_REG32_BIT(RDWC,   0x78180018,__WRITE,__rdwc_bits);
__IO_REG32_BIT(RFSH1,  0x7818001C,__READ_WRITE,__rfsh1_bits);


/***************************************************************************
 **
 **  Direct memory access controller (DMAC)
 **
 ***************************************************************************/
__IO_REG32_BIT(DMAMOD, 0x7BE00000,__READ_WRITE,__dmamod_bits);
__IO_REG32_BIT(DMASTA, 0x7BE00004,__READ,__dmasta_bits);
__IO_REG32_BIT(DMAINT, 0x7BE00008,__READ,__dmaint_bits);
__IO_REG32_BIT(DMACMSK0, 0x7BE00100,__READ_WRITE,__dmacmsk_bits);
__IO_REG32_BIT(DMACTMOD0, 0x7BE00104,__READ_WRITE,__dmactmod_bits);
__IO_REG32(DMACSAD0, 0x7BE00108,__READ_WRITE);
__IO_REG32(DMACDAD0, 0x7BE0010C,__READ_WRITE);
__IO_REG32_BIT(DMACSIZ0, 0x7BE00110,__READ_WRITE,__dmacsiz_bits);
__IO_REG32(DMACCINT0, 0x7BE00114,__WRITE);
__IO_REG32_BIT(DMACMSK1, 0x7BE00200,__READ_WRITE,__dmacmsk_bits);
__IO_REG32_BIT(DMACTMOD1, 0x7BE00204,__READ_WRITE,__dmactmod_bits);
__IO_REG32(DMACSAD1, 0x7BE00208,__READ_WRITE);
__IO_REG32(DMACDAD1, 0x7BE0020C,__READ_WRITE);
__IO_REG32_BIT(DMACSIZ1, 0x7BE00210,__READ_WRITE,__dmacsiz_bits);
__IO_REG32(DMACCINT1, 0x7BE00214,__WRITE);


/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG16_BIT(GPCTL, 0xB7000000,__READ_WRITE,__gpctl_bits);

__IO_REG16_BIT(GPPOA, 0xB7A00000,__READ_WRITE,__gppoa_bits);
__IO_REG16_BIT(GPPIA, 0xB7A00004,__READ,      __gppia_bits);
__IO_REG16_BIT(GPPMA, 0xB7A00008,__READ_WRITE,__gppma_bits);
__IO_REG16_BIT(GPIEA, 0xB7A0000C,__READ_WRITE,__gpiea_bits);
__IO_REG16_BIT(GPIPA, 0xB7A00010,__READ_WRITE,__gpipa_bits);
__IO_REG16_BIT(GPISA, 0xB7A00014,__READ_WRITE,__gpisa_bits);

__IO_REG16_BIT(GPPOB, 0xB7A00020,__READ_WRITE,__gppob_bits);
__IO_REG16_BIT(GPPIB, 0xB7A00024,__READ,      __gppib_bits);
__IO_REG16_BIT(GPPMB, 0xB7A00028,__READ_WRITE,__gppmb_bits);
__IO_REG16_BIT(GPIEB, 0xB7A0002C,__READ_WRITE,__gpieb_bits);
__IO_REG16_BIT(GPIPB, 0xB7A00030,__READ_WRITE,__gpipb_bits);
__IO_REG16_BIT(GPISB, 0xB7A00034,__READ_WRITE,__gpisb_bits);


/***************************************************************************
 **
 **  Watchdog timer
 **
 ***************************************************************************/
__IO_REG8(WDTCON, 0xB7E00000,__WRITE);
__IO_REG8_BIT(WDTBCON, 0xB7E00004,__READ_WRITE,__wdtbcon_bits);
__IO_REG8_BIT(WDSTAT, 0xB7E00014,__READ_WRITE,__wdstat_bits);


/***************************************************************************
 **
 **  Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TMEN,      0xB8001004,__READ_WRITE,__tmen_bits);
__IO_REG32_BIT(TMRLR,     0xB8001008,__READ_WRITE,__tmrlr_bits);
__IO_REG32_BIT(TMOVFR,    0xB8001010,__READ_WRITE,__tmovfr_bits);

__IO_REG16_BIT(TIMECNTL0, 0xB7F00000,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE0,     0xB7F00004,__READ_WRITE);
__IO_REG16(TIMECNT0,      0xB7F00008,__READ);
__IO_REG16(TIMECMP0,      0xB7F0000C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT0, 0xB7F00010,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL1, 0xB7F00020,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE1,     0xB7F00024,__READ_WRITE);
__IO_REG16(TIMECNT1,      0xB7F00028,__READ);
__IO_REG16(TIMECMP1,      0xB7F0002C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT1, 0xB7F00030,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL2, 0xB7F00040,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE2,     0xB7F00044,__READ_WRITE);
__IO_REG16(TIMECNT2,      0xB7F00048,__READ);
__IO_REG16(TIMECMP2,      0xB7F0004C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT2, 0xB7F00050,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL3, 0xB7F00060,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE3,     0xB7F00064,__READ_WRITE);
__IO_REG16(TIMECNT3,      0xB7F00068,__READ);
__IO_REG16(TIMECMP3,      0xB7F0006C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT3, 0xB7F00070,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL4, 0xB7F00080,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE4,     0xB7F00084,__READ_WRITE);
__IO_REG16(TIMECNT4,      0xB7F00088,__READ);
__IO_REG16(TIMECMP4,      0xB7F0008C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT4, 0xB7F00090,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL5, 0xB7F000A0,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE5,     0xB7F000A4,__READ_WRITE);
__IO_REG16(TIMECNT5,      0xB7F000A8,__READ);
__IO_REG16(TIMECMP5,      0xB7F000AC,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT5, 0xB7F000B0,__READ_WRITE,__timestat_bits);


/***************************************************************************
 **
 **  PWM generator
 **
 ***************************************************************************/
__IO_REG16(PWR0,         0xB7D00000,__READ_WRITE);
__IO_REG16(PWCY0,        0xB7D00004,__READ_WRITE);
__IO_REG16(PWC0,         0xB7D00008,__READ_WRITE);
__IO_REG16_BIT(PWCON0,   0xB7D0000C,__READ_WRITE,__pwcon0_bits);

__IO_REG16(PWR1,         0xB7D00020,__READ_WRITE);
__IO_REG16(PWCY1,        0xB7D00024,__READ_WRITE);
__IO_REG16(PWC1,         0xB7D00028,__READ_WRITE);
__IO_REG16_BIT(PWCON1,   0xB7D0002C,__READ_WRITE,__pwcon1_bits);

__IO_REG16_BIT(PWINTSTS, 0xB7D0003C,__READ_WRITE,__pwintsts_bits);


/***************************************************************************
 **
 **  SIO
 **
 ***************************************************************************/
__IO_REG32_BIT(SIOBUF, 0xB8002000,__READ_WRITE,__siobuf_bits);
__IO_REG32_BIT(SIOSTA, 0xB8002004,__READ_WRITE,__siosta_bits);
__IO_REG32_BIT(SIOCON, 0xB8002008,__READ_WRITE,__siocon_bits);
__IO_REG32_BIT(SIOBCN, 0xB800200C,__READ_WRITE,__siobcn_bits);
__IO_REG32_BIT(SIOBT,  0xB8002014,__READ_WRITE,__siobt_bits);
__IO_REG32_BIT(SIOTCN, 0xB8002018,__READ_WRITE,__siotcn_bits);


/***************************************************************************
 **
 **  UART
 **
 ***************************************************************************/

/* UARTDLL, UARTRBR and UARTTHR share the same address */
__IO_REG8(UARTRBRTHR, 0xB7B00000,__READ_WRITE);
#define UARTDLL UARTRBRTHR
#define UARTRBR UARTRBRTHR
#define UARTTHR UARTRBRTHR

/* UARTDLM and UARTIER share the same address */
__IO_REG8_BIT(UARTIER, 0xB7B00004,__READ_WRITE,__uartier_bits);
#define UARTDLM     UARTIER

/* UARTFCR and UARTIIR share the same address */
__IO_REG8_BIT(UARTFCRIIR, 0xB7B00008,__READ_WRITE,__uartfcriir_bits);
#define UARTFCR     UARTFCRIIR
#define UARTFCR_bit UARTFCRIIR_bit
#define UARTIIR     UARTFCRIIR
#define UARTIIR_bit UARTFCRIIR_bit

__IO_REG8_BIT(UARTLCR, 0xB7B0000C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(UARTMCR, 0xB7B00010,__READ_WRITE,__uartmcr_bits);
__IO_REG8_BIT(UARTLSR, 0xB7B00014,__READ_WRITE,__uartlsr_bits);
__IO_REG8_BIT(UARTMSR, 0xB7B00018,__READ_WRITE,__uartmsr_bits);
__IO_REG8(UARTSCR, 0xB7B0001C,__READ_WRITE);


/***************************************************************************
 **
 **  A/D converter
 **
 ***************************************************************************/
__IO_REG16_BIT(ADCON0, 0xB6000000,__READ_WRITE,__adcon0_bits);
__IO_REG16_BIT(ADCON1, 0xB6000004,__READ_WRITE,__adcon1_bits);
__IO_REG16_BIT(ADCON2, 0xB6000008,__READ_WRITE,__adcon2_bits);
__IO_REG16_BIT(ADINT,  0xB600000C,__READ_WRITE,__adint_bits);
__IO_REG16_BIT(ADFINT, 0xB6000010,__READ_WRITE,__adfint_bits);
__IO_REG16_BIT(ADR0,   0xB6000014,__READ_WRITE,__adr0_bits);
__IO_REG16_BIT(ADR1,   0xB6000018,__READ_WRITE,__adr1_bits);
__IO_REG16_BIT(ADR2,   0xB600001C,__READ_WRITE,__adr2_bits);
__IO_REG16_BIT(ADR3,   0xB6000020,__READ_WRITE,__adr3_bits);
__IO_REG16_BIT(ADR4,   0xB6000024,__READ_WRITE,__adr4_bits);
__IO_REG16_BIT(ADR5,   0xB6000028,__READ_WRITE,__adr5_bits);
__IO_REG16_BIT(ADR6,   0xB600002c,__READ_WRITE,__adr6_bits);
__IO_REG16_BIT(ADR7,   0xB6000030,__READ_WRITE,__adr7_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */




/***************************************************************************
 **
 **   ML674000 interrupt sources
 **  
 ***************************************************************************/
#define SYSTIMINT      0     /*    System timer                            */
#define WDTIMINT       1     /*    Watchdog timer                          */
#define WDITIMINT      2     /*    Watchdog timer interval timer operation */
//                     3     /*    (unused)                                */
#define GPIOAINT       4     /*    GPIOA                                   */
#define GPIOBINT       5     /*    GPIOB                                   */
//                     6     /*    (unused)                                */
//                     7     /*    (unused)                                */
#define SWIREQINT      8     /*    Software interrupt requests             */
#define UARTINT        9     /*    UART                                    */
#define SIOINT        10     /*    SIO                                     */
#define ADCINT        11     /*    AD                                      */
#define PWM0INT       12     /*    PWM output 0                            */
#define PWM1INT       13     /*    PWM output 1                            */
//                    14     /*    (unused)                                */
//                    15     /*    (unused)                                */
#define TIMER0INT     16     /*    Timer 0                                 */
#define TIMER1INT     17     /*    Timer 1                                 */
#define TIMER2INT     18     /*    Timer 2                                 */
#define TIMER3INT     19     /*    Timer 3                                 */
#define TIMER4INT     20     /*    Timer 4                                 */
#define TIMER5INT     21     /*    Timer 5                                 */
//                    22     /*    (unused)                                */
//                    23     /*    (unused)                                */
#define DMA0INT       24     /*    DMA channel 0                           */
#define DMA1INT       25     /*    DMA channel 1                           */
//                    26     /*    (unused)                                */
//                    27     /*    (unused)                                */
#define EXT0INT       28     /*    External interrupt 0                    */
#define EXT1INT       29     /*    External interrupt 1                    */
#define EXT2INT       30     /*    External interrupt 2                    */
#define EXT3INT       31     /*    External interrupt 3                    */

#endif    /* __ML674000_H */

