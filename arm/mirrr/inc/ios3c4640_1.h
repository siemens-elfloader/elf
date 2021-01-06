/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C4640
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2000
 **
 **    $Revision: 1.6 $
 **
 ***************************************************************************/

#ifndef __S3C4640_H
#define __S3C4640_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C4640 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* SM: system configuration register  */
typedef struct {
  __REG32 st   :1; /* stall enable */
  __REG32 ce   :1; /* cache enable */
  __REG32 we   :1; /* write buffer enable */
  __REG32      :1;
  __REG32 start:9; /* SFRs start address */
  __REG32      :3;
  __REG32 cs   :1; /* cache select bit */
  __REG32      :15;
} __syscfg_bits;

/* SM: ROM timing control register  */
typedef struct {
  __REG32 dw    :2;
  __REG32       :5;
  __REG32 pmc   :2;
  __REG32 tacp  :2;
  __REG32 tacc  :3;
  __REG32 bp    :9;
  __REG32 np    :9;
} __romcon_bits;



/* SM: SRAM control register  */
typedef struct {
  __REG32 dw      :2;
  __REG32 sioaddr :9;
  __REG32 tacc    :3;
  __REG32 bp      :9;
  __REG32 np      :9;
} __sramcon_bits;

/* SM: DRAM control register  */
typedef struct {
  __REG32 dw      :2;
  __REG32 can     :2;
  __REG32 edo     :1;
  __REG32 tpgm    :2;
  __REG32 tcp     :1;
  __REG32 tcs     :3;
  __REG32 trc     :1;
  __REG32 trp     :2;
  __REG32 bp      :9;
  __REG32 np      :9;
} __dramcon_bits;


/* SM: DRAM refresh control register  */
typedef struct {
  __REG32 vsf  :1;
  __REG32      :15;
  __REG32 ren  :1;
  __REG32 tcs  :3;
  __REG32 tcsr :1;
  __REG32 rcnt :11;
} __refcon_bits;

/* SM: DRAM extra bank control register */
typedef struct {
  __REG32 dw    :2;
  __REG32 tocs  :3;
  __REG32 tacs  :3;
  __REG32 tcoh  :3;
  __REG32 tacc  :3;
  __REG32 bp    :9;
  __REG32 np    :9;
} __extcon_bits;

/* CACHE: start/end address of non-cacheable area register */
typedef struct {
  __REG32       :9;
  __REG32 addr  :16;
  __REG32       :7;
} __cachna_bits;

/* SC: data transfer register */
typedef struct {
  __REG32 rd    :16;
  __REG32       :16;
} __datarvs_bits;

/* SC: control register */
typedef struct {
  __REG32 mode  :1;
  __REG32 sdir  :1;
  __REG32 stat  :1;
  __REG32 ddir  :1;
  __REG32       :28;
} __sftcon_bits;

/* SC: count register */
typedef struct {
  __REG32 cnt    :8;
  __REG32        :24;
} __sftcnt_bits;


/* Timer: control register */
typedef struct {
  __REG32 t0en    :1;
  __REG32 cdfsel0 :2;
  __REG32 t1en    :1;
  __REG32 cdfsel1 :2;
  __REG32 t2en    :1;
  __REG32 cdfsel2 :2;
  __REG32         :23;
} __tcon_bits;

/* Timer: count register */
typedef struct {
  __REG32 cv     :16;
  __REG32        :16;
} __tbcnt_bits;


/* DMA0 and DMA1 control register */
typedef struct {
  __REG32 re     :1;
  __REG32 bs     :1;
  __REG32 mode   :2;
  __REG32 dd     :1;
  __REG32 sd     :1;
  __REG32 df     :1;
  __REG32 sf     :1;
  __REG32 si     :1;
  __REG32        :1;
  __REG32 td     :1;
  __REG32 sb     :1;
  __REG32 tw     :2;
  __REG32 cn     :1;
  __REG32 dm     :1;
  __REG32        :3;
  __REG32 x2m    :1;
  __REG32 m2x    :1;
  __REG32        :11;
} __dmacon01_bits;

/* DMA source/dest address register */
typedef struct {
  __REG32 addr   :25;
  __REG32        :7;
} __dmasrcdst_bits;

/* DMA transfer count register */
typedef struct {
  __REG32 cnt    :24;
  __REG32        :8;
} __dmacnt_bits;

/* DMA2 control register */
typedef struct {
  __REG32 re     :1;
  __REG32 bs     :1;
  __REG32 mode   :2;
  __REG32 dd     :1;
  __REG32 sd     :1;
  __REG32 df     :1;
  __REG32 sf     :1;
  __REG32 si     :1;
  __REG32        :1;
  __REG32 td     :1;
  __REG32 sb     :1;
  __REG32 tw     :2;
  __REG32 cn     :1;
  __REG32        :4;
  __REG32 cdm    :2;
  __REG32        :1;
  __REG32 bufcnt :5;
  __REG32        :5;
} __dmacon2_bits;


/* PP: parallell port register */
typedef struct {
  __REG32 ppd  :8;
  __REG32 ecp  :1;
  __REG32      :23;
} __ppdata_bits;

/* PP: parallell port status register */
typedef struct {
  __REG32 nfault   :1;
  __REG32 select   :1;
  __REG32 perrror  :1;
  __REG32 busyc    :1;
  __REG32 nackc    :1;
  __REG32 busys    :1;
  __REG32 nacks    :1;
  __REG32 nslctin  :1;
  __REG32 nstrobe  :1;
  __REG32 nautofd  :1;
  __REG32 ninit    :1;
  __REG32          :21;
} __ppstat_bits;

/* PP: parallell port nack pulse width register */
typedef struct {
  __REG32 pw       :9;
  __REG32          :23;
} __ppackwth_bits;

/* PP: parallell port control register */
typedef struct {
  __REG32 sr       :1;
  __REG32 dfen     :1;
  __REG32 mode     :2;
  __REG32 ecp      :1;
  __REG32 ec       :1;
  __REG32 dboen    :1;
  __REG32 ab       :1;
  __REG32 dmasel   :1;
  __REG32 dmar     :1;
  __REG32 fr       :1;
  __REG32          :1;
  __REG32 zi       :1;
  __REG32 rle      :1;
  __REG32 dls      :1;
  __REG32 de       :1;
  __REG32          :16;
} __ppcon_bits;

/* PP: parallell interrupt enable/pending register */
typedef struct {
  __REG32 nslctinlh   :1;
  __REG32 nslctinhl   :1;
  __REG32 nstrobelh   :1;
  __REG32 nstrobehl   :1;
  __REG32 nautofdlh   :1;
  __REG32 nautofdhl   :1;
  __REG32 ninitlh     :1;
  __REG32 ninithl     :1;
  __REG32 dr          :1;
  __REG32 cr          :1;
  __REG32 it          :1;
  __REG32 tde         :1;
  __REG32             :20;
} __ppi_bits;


/* UART: line control register */
typedef struct {
  __REG32 wl    :2;
  __REG32 st    :1;
  __REG32 parity:3;
  __REG32       :1;
  __REG32 ir    :1;
  __REG32       :24;
} __ulcon_bits;

/* UART: control register */
typedef struct {
  __REG32 rxm   :2;
  __REG32 rs    :1;
  __REG32 txm   :2;
  __REG32       :1;
  __REG32 sb    :1;
  __REG32 lp    :1;
  __REG32       :24;
} __ucon_bits;


/* UART: status register */
typedef struct {
  __REG32 ov   :1;
  __REG32 pt   :1;
  __REG32 fr   :1;
  __REG32 bk   :1;
  __REG32      :1;
  __REG32 rd   :1;
  __REG32 th   :1;
  __REG32 te   :1;
  __REG32      :24;
} __ustat_bits;


/* UART transmit buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __utxbuf_bits;

/* UART receive buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __urxbuf_bits;

/* UART: baud rate divisor register */
typedef struct {
  __REG32 brdiv :16;
  __REG32       :16;
} __ubrdiv_bits;

/* TG: data register */
typedef struct {
  __REG32 tcd :8;
  __REG32 tgc :1;
  __REG32     :23;
} __tondata_bits;

/* WDT: control register */
typedef struct {
  __REG32 rm   :1;
  __REG32      :1;
  __REG32 im   :1;
  __REG32 clk  :2;
  __REG32 wden :1;
  __REG32      :26;
} __wtcon_bits;

/* WDT: count register */
typedef struct {
  __REG32 cnt :16;
  __REG32     :16;
} __wtcnt_bits;

/* I/O: port mode register */
typedef struct {
  __REG32 giop  :8;
  __REG32 gop   :14;
  __REG32       :2;
  __REG32 gip   :7;
  __REG32       :1;
} __iopmod_bits;

/* I/O: port data register */
typedef struct {
  __REG32 giop  :8;
  __REG32 gop   :14;
  __REG32       :2;
  __REG32 gip   :7;
  __REG32       :1;
}__iopdata_bits;

/* I/O: test control register */
typedef struct {
  __REG32 ctm   :1;
  __REG32       :4;
  __REG32 ckout :1;
  __REG32       :1;
  __REG32 pv    :8;
  __REG32 ov    :1;
  __REG32       :16;
}__tstcon_bits;

/* I/O: EERAM control register */
typedef struct {
  __REG32 data  :1;
  __REG32 clk   :1;
  __REG32 dir   :1;
  __REG32       :29;
}__eeramcon_bits;

/* I/O: extra-output port A register */
/* ASIC: DRV_ASIF data & data output register */
typedef union {
  //__EOPA
  struct {
    __REG32 eop   :6;
    __REG32       :26;
  };
  //__IDRVASIFR
  struct {
    __REG32 od     :16;
    __REG32 odsel  :4;
    __REG32 cs     :1;
    __REG32        :11;
  };
}__eopa_idrvasifr_bits;

/* IC: interrupt mode/pending register*/
typedef struct {
  __REG32 int_print    :1;
  __REG32 int_wdtimer  :1;
  __REG32 int_ext2     :1;
  __REG32 int_ext1     :1;
  __REG32 int_usr1     :1;
  __REG32 int_usr0     :1;
  __REG32 int_txc1     :1;
  __REG32 int_txc0     :1;
  __REG32 int_rxc1     :1;
  __REG32 int_rxc0     :1;
  __REG32 int_timer2   :1;
  __REG32 int_timer1   :1;
  __REG32 int_timer0   :1;
  __REG32 int_hi       :1;
  __REG32 int_cdma1    :1;
  __REG32 int_ext0     :1;
  __REG32 int_xdma1_tc_color :1;
  __REG32 int_xdma0_tc :1;
  __REG32 int_lfs      :1;
  __REG32 int_crp      :1;
  __REG32 int_crms     :1;
  __REG32 int_hdma_tc  :1;
  __REG32              :10;
}__intmodpnd_bits;

/* IC: interrupt mode/pending register*/
typedef struct {
  __REG32 int_print    :1;
  __REG32 int_wdtimer  :1;
  __REG32 int_ext2     :1;
  __REG32 int_ext1     :1;
  __REG32 int_usr1     :1;
  __REG32 int_usr0     :1;
  __REG32 int_txc1     :1;
  __REG32 int_txc0     :1;
  __REG32 int_rxc1     :1;
  __REG32 int_rxc0     :1;
  __REG32 int_timer2   :1;
  __REG32 int_timer1   :1;
  __REG32 int_timer0   :1;
  __REG32 int_hi       :1;
  __REG32 int_cdma1    :1;
  __REG32 int_ext0     :1;
  __REG32 int_xdma1_tc_color :1;
  __REG32 int_xdma0_tc :1;
  __REG32 int_lfs      :1;
  __REG32 int_crp      :1;
  __REG32 int_crms     :1;
  __REG32 int_hdma_tc  :1;
  __REG32 gmask        :1;
  __REG32              :9;
}__intmsk_bits;

/* IC: FIQ interrupt priority & jump address register*/
typedef struct {
  __REG32 ja    :8;
  __REG32 pv    :3;
  __REG32       :21;
}__fiqpri_bits;

/* IC: FIQ/IRQ interrupt priority & jump address register*/
typedef struct {
  __REG32 ja    :8;
  __REG32 pv    :5;
  __REG32       :19;
}__fipri_bits;

/* IC: IRQ FIQ base address register*/
typedef struct {
  __REG32 ba    :24;
  __REG32       :8;
}__fiqirqbase_bits;

/* LF: motor control register */
typedef struct {
  __REG32 ts     :1;
  __REG32 clk    :2;
  __REG32 ir     :1;
  __REG32 ws     :1;
  __REG32 stepwen:1;
  __REG32 st     :1;
  __REG32 dir    :1;
  __REG32 cen    :1;
  __REG32 amen   :1;
  __REG32 msel   :1;
  __REG32 ids    :1;
  __REG32 sls    :1;
  __REG32 ilen   :1;
  __REG32 phase  :2;
  __REG32        :16;
}__lfcr_bits;

/* LF: motor phase control register */
typedef struct {
  __REG32 phase     :4;
  __REG32 mc1       :1;
  __REG32 mc2       :1;
  __REG32           :2;
  __REG32 phaz_ia1  :1;
  __REG32 pha_ia0   :1;
  __REG32 lfphaseb  :1;
  __REG32 lfcon_pha :1;
  __REG32           :20;
}__lfpcr_bits;


/* LF: timer register */
typedef struct {
  __REG32 tv     :14;
  __REG32        :18;
}__lftr_bits;

/* LFCON each control register */
typedef struct {
  __REG32 val    :16;
  __REG32        :16;
}__lfcon_bits;

/* CRC:  carrier motor control register */
typedef struct {
  __REG32 bten   :1;
  __REG32 pten   :1;
  __REG32 csien  :1;
  __REG32        :1;
  __REG32 dcmoen :1;
  __REG32 dcmosel:1;
  __REG32 pwmtr  :1;
  __REG32 pwmmsel:1;
  __REG32 peisel :1;
  __REG32 mtsel  :1;
  __REG32 htsel  :1;
  __REG32 ovfien :1;
  __REG32        :20;
}__cmcr_bits;

/* CRC:  basic timer base register */
typedef struct {
  __REG32 cv     :16;
  __REG32        :16;
}__btbr_bits;

/* CRC:  prestep timer base register */
typedef struct {
  __REG32 cv     :10;
  __REG32        :22;
}__pstbr_bits;

/* CRC:  state control register */
typedef struct {
  __REG32 phasestat :6;
  __REG32 ws        :1;
  __REG32 wen       :1;
  __REG32 ib        :2;
  __REG32 ia        :2;
  __REG32 dir       :1;
  __REG32 step      :1;
  __REG32 pcen      :1;
  __REG32 idsc      :1;
  __REG32           :16;
}__crscr_bits;

/* CRSREG each control register */
typedef struct {
  __REG32 val    :16;
  __REG32        :16;
}__crsreg_bits;

/* CRC: PWM counter base and observation register */
typedef struct {
  __REG32 cv     :16;
  __REG32        :16;
}__pwm_bits;

/* CRC: countering result and observation register */
typedef struct {
  __REG32 cr     :20;
  __REG32        :12;
}__ecd_bits;

/* CRC: interrupt interval countering result and observation register */
typedef struct {
  __REG32 cv     :16;
  __REG32        :16;
}__int_bits;

/* CRF: position & fire control register */
typedef struct {
  __REG32 ppen      :1;
  __REG32 mode      :3;
  __REG32 pcr       :1;
  __REG32 wtbsel    :1;
  __REG32           :1;
  __REG32 prescaler1:8;
  __REG32 prescaler2:6;
  __REG32           :11;
}__pfcr_bits;


/* CRF: carrier position counter register */
typedef struct {
  __REG32 cv      :16;
  __REG32         :16;
}__cpcr_bits;
/* CRF: print start position register */
typedef struct {
  __REG32 cv      :16;
  __REG32         :16;
}__pspr_bits;
/* CRF: print slice counter register */
typedef struct {
  __REG32 cv      :16;
  __REG32         :16;
}__pscr_bits;
/* CRF: position interrupt register */
typedef struct {
  __REG32 cv      :16;
  __REG32         :16;
}__pir_bits;

/* PH: print head control register */
typedef struct {
  __REG32 dither  :4;
  __REG32 dteng   :1;
  __REG32 bdcsel  :1;
  __REG32 cdcsel  :1;
  __REG32 chsel   :1;
  __REG32 htsel   :1;
  __REG32 cde     :1;
  __REG32 tngsel  :1;
  __REG32 v300m   :1;
  __REG32 h300m   :1;
  __REG32 dm      :1;
  __REG32 dsel    :1;
  __REG32 stc     :1;
  __REG32 pfc     :1;
  __REG32 pdc     :1;
  __REG32 cs      :2;
  __REG32 address :4;
  __REG32 als     :1;
  __REG32 cm      :1;
  __REG32         :6;
}__phcr_bits;

/* PH: fire enable timer register */
typedef struct {
  __REG32 cv      :8;
  __REG32         :24;
}__fetr_bits;

/* PH: fire window timer/timer observation register */
typedef struct {
  __REG32 cv      :10;
  __REG32         :22;
}__fwtr_bits;

/* PH: fire strobe delay timer register */
typedef struct {
  __REG32 cv      :12;
  __REG32         :20;
}__fsdtr_bits;

/* PH: pre-heat pulse timer/timer observation register */
typedef struct {
  __REG32 cv      :6;
  __REG32         :26;
}__phptr_bits;

/* PH: pre-heat delay timer/timer observation register */
typedef struct {
  __REG32 cv      :6;
  __REG32         :26;
}__phdtr_bits;

/* PH: print head observation register */
typedef struct {
  __REG32 data    :4;
  __REG32 fire    :3;
  __REG32 hdma    :4;
  __REG32 dither  :4;
  __REG32 number  :4;
  __REG32 delay   :4;
  __REG32 sum     :5;
  __REG32         :4;
}__phor_bits;

/* PH: Td delay counter register */
typedef struct {
  __REG32 back    :4;
  __REG32 front   :4;
  __REG32         :24;
}__tdcr_bits;

/* PH: Td delay counter register */
typedef struct {
  __REG32 phdw    :16;
  __REG32         :16;
}__phdwr_bits;

/* PH: dot counter register */
typedef struct {
  __REG32 dcv     :32;
}__dcr_bits;

/* PH: dot counter control observation register */
typedef struct {
  __REG32 yellow  :3;
  __REG32 cyan    :3;
  __REG32 magnenta:3;
  __REG32         :23;
}__dccor_bits;

/* HDMA: control register */
typedef struct {
  __REG32 re     :1;
  __REG32 busy   :1;
  __REG32 sad    :1;
  __REG32 saf    :1;
  __REG32 reset  :1;
  __REG32        :1;
  __REG32 mps    :1;
  __REG32 mipen  :1;
  __REG32 ien    :1;
  __REG32 al     :1;
  __REG32 aen    :1;
  __REG32 cqbsel :1;
  __REG32        :5;
  __REG32 q0en   :1;
  __REG32        :7;
  __REG32 q1en   :1;
  __REG32        :6;
}__hdcon_bits;

/* HDMA: source/match address register */
typedef struct {
  __REG32 addr   :28;
  __REG32        :4;
}__hdsmar_bits;

/* HDMA: transfer count register */
typedef struct {
  __REG32 tc     :24;
  __REG32        :8;
}__hdtcr_bits;


/* RTC: control register */
typedef struct {
  __REG32 rtce   :1;
  __REG32 rclk   :1;
  __REG32 cntsel :1;
  __REG32 cntrst :1;
  __REG32        :28;
}__rtccon_bits;

/* RTC: BCD  second register */
typedef struct {
  __REG32 cv   :7;
  __REG32      :25;
}__bcdsec_bits;

/* RTC: BCD minute register */
typedef struct {
  __REG32 cv   :7;
  __REG32      :25;
}__bcdmin_bits;

/* RTC: BCD hour register */
typedef struct {
  __REG32 cv   :6;
  __REG32      :26;
}__bcdhour_bits;

/* RTC: BCD day register */
typedef struct {
  __REG32 cv   :6;
  __REG32      :26;
}__bcdday_bits;

/* RTC: BCD date register */
typedef struct {
  __REG32 val  :3;
  __REG32      :29;
}__bcddate_bits;

/* RTC: BCD month register */
typedef struct {
  __REG32 val  :5;
  __REG32      :27;
}__bcdmon_bits;

/* RTC: BCD year register */
typedef struct {
  __REG32 cv   :8;
  __REG32      :24;
}__bcdyear_bits;

/* PSC: clock save control register */
typedef struct {
  __REG32 enpsave :1;
  __REG32         :31;
}__pwrsavcon_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  System manager registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG,0x01000000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__ROMCON,0x01003000,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__SRAMCON0,0x01003004,__READ_WRITE,__sramcon_bits);
__IO_REG32_BIT(__SRAMCON1,0x01003008,__READ_WRITE,__sramcon_bits);
__IO_REG32_BIT(__DRAMCON0,0x0100301c,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__DRAMCON1,0x01003020,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__REFCON,0x01003024,__READ_WRITE,__refcon_bits);
__IO_REG32_BIT(__EXTCON0,0x0100300c,__READ_WRITE,__extcon_bits);
__IO_REG32_BIT(__EXTCON1,0x01003010,__READ_WRITE,__extcon_bits);
__IO_REG32_BIT(__EXTCON2,0x01003014,__READ_WRITE,__extcon_bits);
__IO_REG32_BIT(__EXTCON3,0x01003018,__READ_WRITE,__extcon_bits);

/***************************************************************************
 **
 **  Cache special registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__CACHNAB0,0x01001000,__READ_WRITE,__cachna_bits);
__IO_REG32_BIT(__CACHNAE0,0x01001400,__READ_WRITE,__cachna_bits);
__IO_REG32_BIT(__CACHNAB1,0x01001800,__READ_WRITE,__cachna_bits);
__IO_REG32_BIT(__CACHNAE1,0x01001c00,__READ_WRITE,__cachna_bits);

/***************************************************************************
 **
 **  Derasterizer registers
 **
 ***************************************************************************/
__IO_REG32(__DRAST0,0x01006000,__READ_WRITE);
__IO_REG32(__DRAST1,0x01006004,__READ_WRITE);
__IO_REG32(__DRAST2,0x01006008,__READ_WRITE);
__IO_REG32(__DRAST3,0x0100600c,__READ_WRITE);
__IO_REG32(__DRAST4,0x01006010,__READ_WRITE);
__IO_REG32(__DRAST5,0x01006014,__READ_WRITE);
__IO_REG32(__DRAST6,0x01006018,__READ_WRITE);
__IO_REG32(__DRAST7,0x0100601c,__READ_WRITE);
__IO_REG32(__DRAST8,0x01006020,__READ_WRITE);
__IO_REG32(__DRAST9,0x01006024,__READ_WRITE);
__IO_REG32(__DRAST10,0x01006028,__READ_WRITE);
__IO_REG32(__DRAST11,0x0100602c,__READ_WRITE);
__IO_REG32(__DRAST12,0x01006030,__READ_WRITE);
__IO_REG32(__DRAST13,0x01006034,__READ_WRITE);
__IO_REG32(__DRAST14,0x01006038,__READ_WRITE);
__IO_REG32(__DRAST15,0x0100603c,__READ_WRITE);

/***************************************************************************
 **
 **  Shift control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__DATARVS,0x01007000,__READ_WRITE, __datarvs_bits);
__IO_REG32_BIT(__SFTCON,0x01007004,__READ_WRITE, __sftcon_bits);
__IO_REG32_BIT(__SFTCNT,0x01007008,__READ_WRITE, __sftcnt_bits);
__IO_REG32(__SFTDATA0,0x0100700c,__READ_WRITE);
__IO_REG32(__SFTDATA1,0x01007010,__READ_WRITE);
__IO_REG32(__SFTDATA2,0x01007014,__READ_WRITE);
__IO_REG32(__SFTDATA3,0x01007018,__READ_WRITE);
__IO_REG32(__SFTDATA4,0x0100701c,__READ_WRITE);
__IO_REG32(__SFTDATA5,0x01007020,__READ_WRITE);
__IO_REG32(__SFTDATA6,0x01007024,__READ_WRITE);


/***************************************************************************
 **
 **  Timer registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__TCON,0x01005800,__READ_WRITE, __tcon_bits);
__IO_REG32_BIT(__TBCNT0,0x01005804,__READ_WRITE, __tbcnt_bits);
__IO_REG32_BIT(__TBCNT1,0x01005808,__READ_WRITE, __tbcnt_bits);
__IO_REG32_BIT(__TBCNT2,0x0100580c,__READ_WRITE, __tbcnt_bits);

/***************************************************************************
 **
 **  DMA control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__DMACON0,0x0100c000,__READ_WRITE,__dmacon01_bits);
__IO_REG32_BIT(__DMACON1,0x0100d800,__READ_WRITE,__dmacon01_bits);

__IO_REG32_BIT(__DMASRC0,0x0100c004,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMADST0,0x0100c008,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMASRC1,0x0100d804,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMADST1,0x0100d808,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMACNT0,0x0100c00c,__READ_WRITE,__dmacnt_bits);
__IO_REG32_BIT(__DMACNT1,0x0100d80c,__READ_WRITE,__dmacnt_bits);
__IO_REG32_BIT(__DMACON2,0x0100c800,__READ_WRITE,__dmacon2_bits);
__IO_REG32_BIT(__DMASRC2,0x0100c804,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMADST2,0x0100c808,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMACNT2,0x0100c80c,__READ_WRITE,__dmacnt_bits);


/***************************************************************************
 **
 **  Parallell port registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PPDATA,0x0100b000,__READ_WRITE,__ppdata_bits);
__IO_REG32_BIT(__PPSTAT,0x0100b004,__READ_WRITE,__ppstat_bits);
__IO_REG32_BIT(__PPACKWTH,0x0100b008,__READ_WRITE,__ppackwth_bits);
__IO_REG32_BIT(__PPCON,0x0100b00c,__READ_WRITE,__ppcon_bits);
__IO_REG32_BIT(__PPINTEN,0x0100b010,__READ_WRITE,__ppi_bits);
__IO_REG32_BIT(__PPINTPND,0x0100b014,__READ_WRITE,__ppi_bits);

/***************************************************************************
 **
 **  UART registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__ULCON0,0x0100e000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__ULCON1,0x0100e800,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__UCON0,0x0100e004,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__UCON1,0x0100e804,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__USTAT0,0x0100e008,__READ,__ustat_bits);
__IO_REG32_BIT(__USTAT1,0x0100e808,__READ,__ustat_bits);
__IO_REG32_BIT(__UTXBUF0,0x0100e00c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__UTXBUF1,0x0100e80c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__URXBUF0,0x0100e010,__READ,__urxbuf_bits);
__IO_REG32_BIT(__URXBUF1,0x0100e810,__READ,__urxbuf_bits);
__IO_REG32_BIT(__UBRDIV0,0x0100e014,__READ_WRITE,__ubrdiv_bits);
__IO_REG32_BIT(__UBRDIV1,0x0100e814,__READ_WRITE,__ubrdiv_bits);



/***************************************************************************
 **
 **  Tone generator registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__TONDATA,0x0100f004,__READ_WRITE,__tondata_bits);

/***************************************************************************
 **
 **  Watchdog timer registers
 **
 ***************************************************************************/

__IO_REG32_BIT(__WTCNT,0x0100f804,__READ_WRITE,__wtcnt_bits);
__IO_REG32_BIT(__WTCON,0x0100f800,__READ_WRITE,__wtcon_bits);


/***************************************************************************
 **
 **  Interrupt controller Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTMOD,0x01004000,__READ_WRITE,__intmodpnd_bits);
__IO_REG32_BIT(__INTPND,0x01004004,__READ_WRITE,__intmodpnd_bits);
__IO_REG32_BIT(__INTMSK,0x01004008,__READ_WRITE,__intmsk_bits);
__IO_REG32_BIT(__FIQPRI0,0x0100400c,__READ_WRITE,__fiqpri_bits);
__IO_REG32_BIT(__FIQPRI1,0x01004010,__READ_WRITE,__fiqpri_bits);
__IO_REG32_BIT(__FIQPRI2,0x01004014,__READ_WRITE,__fiqpri_bits);

__IO_REG32_BIT(__FIPRI0,0x01004018,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__FIPRI1,0x0100401c,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__FIPRI2,0x01004020,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__FIPRI3,0x01004024,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__FIPRI4,0x01004028,__READ_WRITE,__fipri_bits);

__IO_REG32_BIT(__IRQPRI0,0x0100402c,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI1,0x01004030,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI2,0x01004034,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI3,0x01004038,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI4,0x0100403c,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI5,0x01004040,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI6,0x01004044,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI7,0x01004048,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI8,0x0100404c,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI9,0x01004050,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI10,0x01004054,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI11,0x01004058,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI12,0x0100405c,__READ_WRITE,__fipri_bits);
__IO_REG32_BIT(__IRQPRI13,0x01004060,__READ_WRITE,__fipri_bits);

__IO_REG32_BIT(__IRQBASE,0x01004064,__READ_WRITE,__fiqirqbase_bits);
__IO_REG32_BIT(__FIQBASE,0x01004068,__READ_WRITE,__fiqirqbase_bits);

__IO_REG32(__INTTEST,0x0100406c,__WRITE);
__IO_REG32(__IRQJPADDR,0x01004070,__READ);
__IO_REG32(__FIQJPADDR,0x01004074,__READ);


/***************************************************************************
 **
 **  LF motor Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__LFCR,0x01008000,__READ_WRITE,__lfcr_bits);
__IO_REG32_BIT(__LFPCR,0x01008004,__READ_WRITE,__lfpcr_bits);
__IO_REG32_BIT(__LFTBR,0x01008008,__READ_WRITE,__lftr_bits);
__IO_REG32_BIT(__LFTOR,0x0100800c,__READ,__lftr_bits);
__IO_REG32_BIT(__LFTCBR,0x01008010,__READ_WRITE,__lftr_bits);
__IO_REG32_BIT(__LFTCOR,0x01008014,__READ,__lftr_bits);
__IO_REG32_BIT(__LFCON,0x01008018,__READ_WRITE,__lfcon_bits);


/***************************************************************************
 **
 **  IO port registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__IOPMOD,0x01004808,__READ_WRITE,__iopmod_bits);
__IO_REG32_BIT(__IOPDATA,0x01004804,__READ_WRITE,__iopdata_bits);
__IO_REG32_BIT(__TSTCON,0x01004800,__READ_WRITE,__tstcon_bits);
__IO_REG32_BIT(__EERAMCON,0x01005000,__READ_WRITE,__eeramcon_bits);
__IO_REG32_BIT(__EOPA,0x01005004,__READ_WRITE,__eopa_idrvasifr_bits);
//EOPL and LFCR has the same address
#define __EOPL __LFCR


/***************************************************************************
 **
 **  CR Control Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__CMCR,0x01009000,__READ_WRITE,__cmcr_bits);
__IO_REG32_BIT(__BTB1R,0x01009004,__READ_WRITE,__btbr_bits);
__IO_REG32_BIT(__BTB2R,0x01009008,__READ_WRITE,__btbr_bits);
__IO_REG32_BIT(__PSTBR,0x0100900c,__READ_WRITE,__pstbr_bits);
__IO_REG32_BIT(__CRSCR,0x01009010,__READ_WRITE,__crscr_bits);
__IO_REG32_BIT(__CRSREG,0x01009030,__READ_WRITE,__crsreg_bits);

__IO_REG32_BIT(__PWMOBS,0x01009014,__READ,__pwm_bits);
__IO_REG32_BIT(__PWMCYL,0x01009018,__READ_WRITE,__pwm_bits);
__IO_REG32_BIT(__PWMONT,0x0100901c,__READ_WRITE,__pwm_bits);
__IO_REG32_BIT(__ECDTIM,0x01009020,__READ,__ecd_bits);
__IO_REG32_BIT(__ECDVAL,0x01009024,__READ,__ecd_bits);
__IO_REG32_BIT(__INTTIM,0x01009028,__READ,__int_bits);
__IO_REG32_BIT(__INTVAL,0x0100902c,__READ,__int_bits);

/***************************************************************************
 **
 **  CR Fire Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PFCR,0x01009820,__READ_WRITE,__pfcr_bits);
__IO_REG32_BIT(__CPCR,0x01009824,__READ_WRITE,__cpcr_bits);
__IO_REG32_BIT(__PSPR,0x01009828,__READ_WRITE,__pspr_bits);
__IO_REG32_BIT(__PSCR,0x0100982c,__READ_WRITE,__pscr_bits);
__IO_REG32_BIT(__PIR,0x01009830,__READ_WRITE,__pir_bits);

/***************************************************************************
 **
 **  Print head Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PHCR,0x0100a000,__READ_WRITE,__phcr_bits);
__IO_REG32_BIT(__FETR,0x0100a004,__READ_WRITE,__fetr_bits);
__IO_REG32_BIT(__FETOR,0x0100a008,__READ,__fetr_bits);
__IO_REG32_BIT(__FWTR,0x0100a00c,__READ_WRITE,__fwtr_bits);
__IO_REG32_BIT(__FWTOR,0x0100a010,__READ,__fwtr_bits);

__IO_REG32_BIT(__FSDTR,0x0100a014,__READ_WRITE,__fsdtr_bits);
__IO_REG32_BIT(__FSDT0OR,0x0100a018,__READ,__fsdtr_bits);
__IO_REG32_BIT(__FSDT1OR,0x0100a01c,__READ,__fsdtr_bits);
__IO_REG32_BIT(__FSDT2OR,0x0100a020,__READ,__fsdtr_bits);
__IO_REG32_BIT(__FSDT3OR,0x0100a024,__READ,__fsdtr_bits);

__IO_REG32_BIT(__PHPTR,0x0100a028,__READ_WRITE,__phptr_bits);
__IO_REG32_BIT(__PHPTOR,0x0100a02c,__READ,__phptr_bits);
__IO_REG32_BIT(__PHDTR,0x0100a030,__READ_WRITE,__phdtr_bits);
__IO_REG32_BIT(__PHDTOR,0x0100a034,__READ,__phdtr_bits);

__IO_REG32_BIT(__PHOR,0x0100a038,__READ,__phor_bits);
__IO_REG32_BIT(__TDCR,0x0100a03c,__READ_WRITE,__tdcr_bits);

__IO_REG32_BIT(__PHDW0R,0x0100a040,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW1R,0x0100a044,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW2R,0x0100a048,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW3R,0x0100a04c,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW4R,0x0100a050,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW5R,0x0100a054,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW6R,0x0100a058,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW7R,0x0100a05c,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW8R,0x0100a060,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW9R,0x0100a064,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW10R,0x0100a068,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW11R,0x0100a06c,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__PHDW12R,0x0100a070,__READ_WRITE,__phdwr_bits);
__IO_REG32_BIT(__DCBR,0x0100a074,__READ_WRITE,__dcr_bits);
__IO_REG32_BIT(__DCYR,0x0100a078,__READ_WRITE,__dcr_bits);
__IO_REG32_BIT(__DCCR,0x0100a07c,__READ_WRITE,__dcr_bits);
__IO_REG32_BIT(__DCMR,0x0100a080,__READ_WRITE,__dcr_bits);
__IO_REG32_BIT(__DCCOR,0x0100a084,__READ_WRITE,__dccor_bits);


/***************************************************************************
 **
 **  HDMA Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__HDCON,0x0100d000,__READ_WRITE,__hdcon_bits);
__IO_REG32_BIT(__HDSAR,0x0100d004,__READ_WRITE,__hdsmar_bits);
__IO_REG32_BIT(__HDTCR,0x0100d00c,__READ_WRITE,__hdtcr_bits);

__IO_REG32_BIT(__HDSAR0,0x0100d014,__READ_WRITE,__hdsmar_bits);
__IO_REG32_BIT(__HDMAR0,0x0100d018,__READ_WRITE,__hdsmar_bits);
__IO_REG32_BIT(__HDSAR1,0x0100d01c,__READ_WRITE,__hdsmar_bits);
__IO_REG32_BIT(__HDMAR1,0x0100d020,__READ_WRITE,__hdsmar_bits);

/***************************************************************************
 **
 **   ASIC Registers
 **
 ***************************************************************************/
#define __IDRVASIFR_bit __EOPA_bit
#define __IDRVASIFR     __EOPA

/***************************************************************************
 **
 **   RTC Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__RTCCON,0x0100f840,__READ_WRITE,__rtccon_bits);
__IO_REG32_BIT(__BCDSEC,0x0100f870,__READ_WRITE,__bcdsec_bits);
__IO_REG32_BIT(__BCDMIN,0x0100f874,__READ_WRITE,__bcdmin_bits);
__IO_REG32_BIT(__BCDHOUR,0x0100f878,__READ_WRITE,__bcdhour_bits);
__IO_REG32_BIT(__BCDDAY,0x0100f87c,__READ_WRITE,__bcdday_bits);
__IO_REG32_BIT(__BCDDATE,0x0100f880,__READ_WRITE,__bcddate_bits);
__IO_REG32_BIT(__BCDMON,0x0100f884,__READ_WRITE,__bcdmon_bits);
__IO_REG32_BIT(__BCDYEAR,0x0100f888,__READ_WRITE,__bcdyear_bits);

/***************************************************************************
 **
 **   Power Save Control Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PWRSAVCON,0x01005820,__READ_WRITE,__pwrsavcon_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3C4640 interrupt sources
 **
 ***************************************************************************/
#define INT_PRINT   0  /* print interrupt                       */
#define INT_WDTIMER 1  /* watchdog timer interrupt              */
#define INT_EXT2    2  /* external interrupt 2                  */
#define INT_EXT1    3  /* external interrupt 1                  */
#define INT_USR1    4  /* UART channel 1 error interrupt        */
#define INT_USR0    5  /* UART channel 0 error interrupt        */
#define INT_TXC1    6  /* UART channel 1 transmit interrupt     */
#define INT_TXC0    7  /* UART channel 0 transmit interrupt     */
#define INT_RXC1    8  /* UART channel 1 receive interrupt      */
#define INT_RXC0    9  /* UART channel 0 receive interrupt      */
#define INT_TIMER2 10  /* timer 2 interrupt                     */
#define INT_TIMER1 11  /* timer 1 interrupt                     */
#define INT_TIMER0 12  /* timer 0 interrupt                     */
#define INT_HI     13  /* host interface interrupt              */
#define INT_CDMA1  14  /* codec DMA 1 interrupt                 */
#define INT_EXT0   15  /* external interrupt 0                  */
#define INT_XDMA1_TC_COLOR 16  /* XDMA1_TC_color chip interrupt */
#define INT_XDMA0_TC       17  /* XDMA0_TC interrupt            */
#define INT_LFS            18  /* LF step interrupt             */
#define INT_CRP            19  /* CR position interrupt         */
#define INT_CRMS           20  /* CR motor_step/encoder interrupt*/
#define INT_HDMA_TC        21  /* HEAD DMA_TC interrupt         */

#endif    /* __S3C4640_H */
