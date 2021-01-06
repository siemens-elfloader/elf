/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung S3C44B0X
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2000
 **
 **    $Revision: 1.6 $
 **
 ***************************************************************************/

#ifndef __S3C44B0X_H
#define __S3C44B0X_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C44B0X SPECIAL FUNCTION REGISTERS (little endian)
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* system configuration register  */
typedef struct {
  __REG32 se   :1; /* enable stall option */
  __REG32 cm   :2; /* cache mode */
  __REG32 we   :1; /* buffer enable */
  __REG32 rse  :1; /* enable read stall option  */
  __REG32 da   :1; /* DATA ABORT */
  __REG32      :26;
} __syscfg_bits;

/* non-cacheable area control register  */
typedef struct {
  __REG32 sa0   :16;
  __REG32 se0   :16;
} __ncach0_bits;

typedef struct {
  __REG32 sa1   :16;
  __REG32 se1   :16;
} __ncach1_bits;



/* system bus priority controller */
typedef struct {
  __REG32 nbreq     :2;
  __REG32 bdma      :2;
  __REG32 zdma      :2;
  __REG32 lcd_dma   :2;
  __REG32 s_nbreq   :2;
  __REG32 s_bdma    :2;
  __REG32 s_zdma    :2;
  __REG32 s_lcd_dma :2;
  __REG32           :15;
  __REG32 fix       :1;
} __sbuscon_bits;

/* bus width & wait control register  */
typedef struct {
  __REG32 endian  :1;
  __REG32 dw0     :2;
  __REG32 dw1     :2;
  __REG32         :1;
  __REG32 ws1     :1;
  __REG32 st1     :1;
  __REG32 dw2     :2;
  __REG32 ws2     :1;
  __REG32 st2     :1;
  __REG32 dw3     :2;
  __REG32 ws3     :1;
  __REG32 st3     :1;
  __REG32 dw4     :2;
  __REG32 ws4     :1;
  __REG32 st4     :1;
  __REG32 dw5     :2;
  __REG32 ws5     :1;
  __REG32 st5     :1;
  __REG32 dw6     :2;
  __REG32 ws6     :1;
  __REG32 st6     :1;
  __REG32 dw7     :2;
  __REG32 ws7     :1;
  __REG32 st7     :1;
} __bwscon_bits;


/* bank control register */
typedef struct {
  __REG32 pmc  :2;
  __REG32 tpac :2;
  __REG32 tcah :2;
  __REG32 toch :2;
  __REG32 tacc :2;
  __REG32 tcos :2;
  __REG32 tacs :2;
  __REG32      :18;
} __bankcon0_bits;

typedef struct {
  __REG32 pmc  :2;
  __REG32 tpac :2;
  __REG32 tcah :2;
  __REG32 toch :2;
  __REG32 tacc :2;
  __REG32 tcos :2;
  __REG32 tacs :2;
  __REG32      :18;
} __bankcon1_bits;

typedef struct {
  __REG32 pmc  :2;
  __REG32 tpac :2;
  __REG32 tcah :2;
  __REG32 toch :2;
  __REG32 tacc :2;
  __REG32 tcos :2;
  __REG32 tacs :2;
  __REG32      :18;
} __bankcon2_bits;

typedef struct {
  __REG32 pmc  :2;
  __REG32 tpac :2;
  __REG32 tcah :2;
  __REG32 toch :2;
  __REG32 tacc :2;
  __REG32 tcos :2;
  __REG32 tacs :2;
  __REG32      :18;
} __bankcon3_bits;

typedef struct {
  __REG32 pmc  :2;
  __REG32 tpac :2;
  __REG32 tcah :2;
  __REG32 toch :2;
  __REG32 tacc :2;
  __REG32 tcos :2;
  __REG32 tacs :2;
  __REG32      :18;
} __bankcon4_bits;

typedef struct {
  __REG32 pmc  :2;
  __REG32 tpac :2;
  __REG32 tcah :2;
  __REG32 toch :2;
  __REG32 tacc :2;
  __REG32 tcos :2;
  __REG32 tacs :2;
  __REG32      :18;
} __bankcon5_bits;


typedef struct {
  __REG32 pmc   :2;
  __REG32 tacp  :2;
  __REG32 tcah  :2;
  __REG32 toch  :2;
  __REG32 tacc  :2;
  __REG32 tcos  :2;
  __REG32 tacs  :2;
  __REG32 mt    :2;
  __REG32       :16;
} __bankcon6_bits;

typedef struct {
  __REG32 pmc   :2;
  __REG32 tacp  :2;
  __REG32 tcah  :2;
  __REG32 toch  :2;
  __REG32 tacc  :2;
  __REG32 tcos  :2;
  __REG32 tacs  :2;
  __REG32 mt    :2;
  __REG32       :16;
} __bankcon7_bits;

/* refresh control register */
typedef struct {
  __REG32 counter :11;
  __REG32         :5;
  __REG32 tchr    :2;
  __REG32 trc     :2;
  __REG32 trp     :2;
  __REG32 trefmd  :1;
  __REG32 refen   :1;
  __REG32         :8;
} __refresh_bits;

/* banksize register */
typedef struct {
  __REG32 bk76map :3;
  __REG32         :1;
  __REG32 sclken  :1;
  __REG32         :27;
} __banksize_bits;

/* sdram mode register set register */
typedef struct {
  __REG32 bl     :3;
  __REG32 bt     :1;
  __REG32 cl     :3;
  __REG32 tm     :2;
  __REG32 wbl    :1;
  __REG32        :22;
} __mrsr_bits;


/* uart fifo control register */
typedef struct {
  __REG32 enable   :1;
  __REG32 rreset   :1;
  __REG32 treset   :1;
  __REG32          :1;
  __REG32 rtrigger :2;
  __REG32 ttrigger :2;
  __REG32          :24;
} __ufcon_bits;


/* uart modem control register */
typedef struct {
  __REG32 send     :1;
  __REG32          :3;
  __REG32 afc      :1;
  __REG32          :27;
} __umcon_bits;

/* uart tx/rx status register */
typedef struct {
  __REG32 rbuffer    :1;
  __REG32 tbuffer    :1;
  __REG32 tshifter   :1;
  __REG32            :29;
} __utrstat_bits;

/* uart error status register */
typedef struct {
  __REG32 overrun :1;
  __REG32 parity  :1;
  __REG32 frame   :1;
  __REG32 ubreak   :1;
  __REG32         :28;
} __uerstat_bits;


/* uart fifo status register */
typedef struct {
  __REG32 rcount  :4;
  __REG32 tcount  :4;
  __REG32 rfull   :1;
  __REG32 tfull   :1;
  __REG32         :22;
} __ufstat_bits;

/* uart modem status register */
typedef struct {
  __REG32 clear   :1;
  __REG32         :1;
  __REG32 cts     :1;
  __REG32         :29;
} __umstat_bits;

/* uart transmit holding(buffer) register & fifo register */
typedef struct {
  __REG32 txdata   :8;
  __REG32          :24;
} __utx_bits;

/* uart receive holding(buffer) register & fifo register */
typedef struct {
  __REG32 rxdata   :8;
  __REG32          :24;
} __urx_bits;



/* uart line control register */
typedef struct {
  __REG32 wlength   :2;
  __REG32 stop      :1;
  __REG32 parity    :3;
  __REG32 infra     :1;
  __REG32           :25;
} __ulcon0_bits;

/* uart line control register */
typedef struct {
  __REG32 wlength   :2;
  __REG32 stop      :1;
  __REG32 parity    :3;
  __REG32 infra     :1;
  __REG32           :25;
} __ulcon1_bits;

/* uart control register */
typedef struct {
  __REG32 receive  :2;
  __REG32 transmit :2;
  __REG32 sbreak   :1;
  __REG32 loop     :1;
  __REG32 rxerror  :1;
  __REG32 rxtime   :1;
  __REG32 rxint    :1;
  __REG32 txint    :1;
  __REG32          :22;
} __ucon0_bits;

/* uart control register */
typedef struct {
  __REG32 receive  :2;
  __REG32 transmit :2;
  __REG32 sbreak   :1;
  __REG32 loop     :1;
  __REG32 rxerror  :1;
  __REG32 rxtime   :1;
  __REG32 rxint    :1;
  __REG32 txint    :1;
  __REG32          :22;
} __ucon1_bits;

/* uart baud rate division register */
typedef struct {
  __REG32 ubrdiv      :16;
  __REG32             :16;
} __ubrdiv0_bits;

typedef struct {
  __REG32 ubrdiv      :16;
  __REG32             :16;
} __ubrdiv1_bits;

/* sio control register */
typedef struct {
  __REG32 mode   :2;
  __REG32 shift  :1;
  __REG32 start  :1;
  __REG32 cledge :1;
  __REG32 tr     :1;
  __REG32 data   :1;
  __REG32 clsrc  :1;
  __REG32        :24;
} __siocon_bits;


/* sio data register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __siodat_bits;


/* sio baud rate prescaler register */
typedef struct {
  __REG32 sbrdr :12;
  __REG32      :20;
} __sbrdr_bits;

/* sio interval count register */
typedef struct {
  __REG32 ivtcnt :8;
  __REG32       :24;
} __ivtcnt_bits;

/* sio dma count zero register */
typedef struct {
  __REG32 dcntz0  :1;
  __REG32 dcntz1  :1;
  __REG32         :30;
}__dcntz_bits;

/* iis control register */
typedef struct {
  __REG32 start     :1;
  __REG32 prescaler :1;
  __REG32 rch       :1;
  __REG32 tch       :1;
  __REG32 rdma      :1;
  __REG32 tdma      :1;
  __REG32 rfifo     :1;
  __REG32 tfifo     :1;
  __REG32 index     :1;
  __REG32           :23;
}__iiscon_bits;

/* iis mode register */
typedef struct {
  __REG32 clkserial  :2;
  __REG32 clkmaster  :1;
  __REG32 data       :1;
  __REG32 format     :1;
  __REG32 level      :1;
  __REG32 trmode     :2;
  __REG32 msmode     :1;
  __REG32            :23;
}__iismod_bits;

/* iis prescaler register */
typedef struct {
  __REG32 valueb   :3;
  __REG32 controlb :1;
  __REG32 _valueb   :3;
  __REG32 _controlb :1;
  __REG32          :24;
}__iispsr_bits;

/* iis fifo register */
typedef struct {
  __REG32 fentry  :16;
  __REG32         :16;
}__iisfif_bits;


/* watch-dog timer control register */
typedef struct {
  __REG32 reset     :1;
  __REG32           :1;
  __REG32 interrupt :1;
  __REG32 clock     :2;
  __REG32 watchdog  :1;
  __REG32           :2;
  __REG32 prescaler :8;
  __REG32           :16;
}__wtcon_bits;

/* watch-dog timer data register */
typedef struct {
  __REG32 value  :16;
  __REG32        :16;
}__wtdat_bits;

/* watch-dog timer count register */
typedef struct {
  __REG32 value :16;
  __REG32       :16;
}__wtcnt_bits;

/* a/d converter control register */
typedef struct {
  __REG32 enable   :1;
  __REG32 read     :1;
  __REG32 input    :3;
  __REG32 sleep    :1;
  __REG32 flag     :1;
  __REG32          :25;
}__adccon_bits;

/* a/d converter prescaler register */
typedef struct {
  __REG32 prescaler :8;
  __REG32           :24;
}__adcpsr_bits;

/* a/d converter data register */
typedef struct {
  __REG32 adcdat  :10;
  __REG32         :22;
}__adcdat_bits;

/* timer configuration register1 */
typedef struct {
  __REG32 pre0   :8;
  __REG32 pre1   :8;
  __REG32 pre2   :8;
  __REG32 length :8;
}__tcfg0_bits;

/* timer configuration register1 */
typedef struct {
  __REG32 mux0       :4;
  __REG32 mux1       :4;
  __REG32 mux2       :4;
  __REG32 mux3       :4;
  __REG32 mux4       :4;
  __REG32 mux5       :4;
  __REG32 mode       :4;
  __REG32            :4;
} __tcfg1_bits;

/* timer control register */
typedef struct {
  __REG32 t0_start    :1;
  __REG32 t0_update   :1;
  __REG32 t0_inverter :1;
  __REG32 t0_reload   :1;
  __REG32 dead_zone   :1;
  __REG32             :3;
  __REG32 t1_start    :1;
  __REG32 t1_update   :1;
  __REG32 t1_inverter :1;
  __REG32 t1_reload   :1;
  __REG32 t2_start    :1;
  __REG32 t2_update   :1;
  __REG32 t2_inverter :1;
  __REG32 t2_reload   :1;
  __REG32 t3_start    :1;
  __REG32 t3_update   :1;
  __REG32 t3_inverter :1;
  __REG32 t3_reload   :1;
  __REG32 t4_start    :1;
  __REG32 t4_update   :1;
  __REG32 t4_inverter :1;
  __REG32 t4_reload   :1;
  __REG32 t5_start    :1;
  __REG32 t5_update   :1;
  __REG32 t5_reload   :1;
  __REG32             :5;
} __tcon_bits;

/* multi-master-bus control register */
typedef struct {
  __REG32 clock      :4;
  __REG32 int_flag   :1;
  __REG32 int_enable :1;
  __REG32 tx_clock   :1;
  __REG32 enable     :1;
  __REG32            :24;
} __iiccon_bits;

/* multi-master-iicbus control/status register */
typedef struct {
  __REG32 last       :1;
  __REG32 zero       :1;
  __REG32 slave      :1;
  __REG32 arbitration:1;
  __REG32 out_enable :1;
  __REG32 busy       :1;
  __REG32 mode       :2;
  __REG32            :24;
} __iicstat_bits;

/* multi-master-iicbus address register */
typedef struct {
  __REG32 shift      :8;
  __REG32            :24;
} __iicadd_bits;

/* multi-master-iic-bus transmit/receive data shift register */
typedef struct {
  __REG32 shift      :8;
  __REG32            :24;
} __iicds_bits;

/* real time clock special register */
typedef struct {
  __REG32 clkrst     :1;
  __REG32 cntsel     :1;
  __REG32 clksel     :1;
  __REG32 rtcen      :1;
  __REG32            :28;
} __rtccon_bits;

/* ¨rtc alarm control register */
typedef struct {
  __REG32 secen      :1;
  __REG32 minen      :1;
  __REG32 houren     :1;
  __REG32 dayen      :1;
  __REG32 monren     :1;
  __REG32 rearen     :1;
  __REG32 almen      :1;
  __REG32            :25;
} __rtcalm_bits;

/* alarm second data register */
typedef struct {
  __REG32            :4;
  __REG32 secdata    :3;
  __REG32            :25;
} __almsec_bits;

/* multi-master-iic-bus transmit/receive data shift register */
typedef struct {
  __REG32            :4;
  __REG32 mindata    :3;
  __REG32            :25;
} __almmin_bits;

/* alarm hour data register */
typedef struct {
  __REG32            :4;
  __REG32 hourdata   :2;
  __REG32            :26;
} __almhour_bits;

/* alarm day data register */
typedef struct {
  __REG32            :4;
  __REG32 daydata    :2;
  __REG32            :26;
} __almday_bits;

/* alarm mon data register */
typedef struct {
  __REG32            :4;
  __REG32 mondata    :1;
  __REG32            :27;
} __almmon_bits;

/* alarm year data register */
typedef struct {
  __REG32 yeardata   :8;
  __REG32            :24;
} __almyear_bits;

/* rtc round reset register */
typedef struct {
  __REG32 seccr      :3;
  __REG32 srsten     :1;
  __REG32            :28;
} __rtcrst_bits;

/* bcd second register */
typedef struct {
  __REG32            :4;
  __REG32 secdata    :3;
  __REG32            :25;
} __bcdsec_bits;

/* bcd minute register */
typedef struct {
  __REG32            :4;
  __REG32 mindata    :3;
  __REG32            :25;
} __bcdmin_bits;

/* bcd hour register */
typedef struct {
  __REG32            :4;
  __REG32 hourdata   :2;
  __REG32            :26;
} __bcdhour_bits;

/* bcd day register */
typedef struct {
  __REG32            :4;
  __REG32 daydata    :2;
  __REG32            :26;
} __bcdday_bits;

/* bcd date register */
typedef struct {
  __REG32 datedata   :3;
  __REG32            :29;
} __bcddate_bits;

/* bcd month register */
typedef struct {
  __REG32            :4;
  __REG32 mondata    :1;
  __REG32            :27;
} __bcdmon_bits;

/* bcd year register */
typedef struct {
  __REG32 yeardata   :8;
  __REG32            :24;
} __bcdyear_bits;

/* tick time count register */
typedef struct {
  __REG32 time       :7;
  __REG32 enable     :1;
  __REG32            :24;
} __ticnt_bits;

/* pll control register */
typedef struct {
  __REG32 sdiv       :2;
  __REG32            :2;
  __REG32 pdiv       :6;
  __REG32            :2;
  __REG32 mdiv       :7;
  __REG32            :13;
} __pllcon_bits;

/* clock control register */
typedef struct {
  __REG32 stop       :1;
  __REG32 sl_idle    :1;
  __REG32 idle       :1;
  __REG32 pwmtimer   :1;
  __REG32 zdma       :1;
  __REG32 sio        :1;
  __REG32 lcdc       :1;
  __REG32 bdma       :1;
  __REG32 uart0      :1;
  __REG32 uart1      :1;
  __REG32 gpio       :1;
  __REG32 rtc        :1;
  __REG32 adc        :1;
  __REG32 iic        :1;
  __REG32 iis        :1;
  __REG32            :17;
} __clkcon_bits;

/* clock slow control register */
typedef struct {
  __REG32 slow_val   :4;
  __REG32 slow_bit   :1;
  __REG32 pll_off    :1;
  __REG32            :26;
} __clkslow_bits;

/* lock time count register */
typedef struct {
  __REG32 cnt        :12;
  __REG32            :20;
} __locktime_bits;

/* IC: interrupt control register*/
typedef struct {
  __REG32 f :1;
  __REG32 i :1;
  __REG32 v :1;
  __REG32   :1;
  __REG32   :28;
} __intcon_bits;

/* IC: interrupt pending/mode/I_ISPC/F_ISPC register*/
typedef struct {
  __REG32 int_adc   :1;
  __REG32 int_rtc   :1;
  __REG32 int_utxd1 :1;
  __REG32 int_utxd0 :1;
  __REG32 int_sio   :1;
  __REG32 int_iic   :1;
  __REG32 int_urxd1 :1;
  __REG32 int_urxd0 :1;
  __REG32 int_timer5:1;
  __REG32 int_timer4:1;
  __REG32 int_timer3:1;
  __REG32 int_timer2:1;
  __REG32 int_timer1:1;
  __REG32 int_timer0:1;
  __REG32 int_uerr  :1;
  __REG32 int_wdt   :1;
  __REG32 int_bdma1 :1;
  __REG32 int_bdma0 :1;
  __REG32 int_zdma1 :1;
  __REG32 int_zdma0 :1;
  __REG32 int_tick  :1;
  __REG32 eint4567  :1;
  __REG32 eint3     :1;
  __REG32 eint2     :1;
  __REG32 eint1     :1;
  __REG32 eint0     :1;
  __REG32           :6;
} __intpndmodispc_bits;

/* IC: interrupt mask register*/
typedef struct {
  __REG32 int_adc    :1;
  __REG32 int_rtc    :1;
  __REG32 int_utxd1  :1;
  __REG32 int_utxd0  :1;
  __REG32 int_sio    :1;
  __REG32 int_iic    :1;
  __REG32 int_urxd1  :1;
  __REG32 int_urxd0  :1;
  __REG32 int_timer5 :1;
  __REG32 int_timer4 :1;
  __REG32 int_timer3 :1;
  __REG32 int_timer2 :1;
  __REG32 int_timer1 :1;
  __REG32 int_timer0 :1;
  __REG32 int_uerr   :1;
  __REG32 int_wtd    :1;
  __REG32 int_bdma1  :1;
  __REG32 int_bdma0  :1;
  __REG32 int_zdma1  :1;
  __REG32 int_zdma0  :1;
  __REG32 int_tick   :1;
  __REG32 eint4567   :1;
  __REG32 eint3      :1;
  __REG32 eint2      :1;
  __REG32 eint1      :1;
  __REG32 eint0      :1;
  __REG32 global     :1;
  __REG32            :1;
  __REG32            :4;
} __intmsk_bits;

/* IC: IRQ/FIQ priority of slave register*/
typedef struct {
  __REG32 int_sio    :2;
  __REG32 int_iic    :2;
  __REG32 int_urxd1  :2;
  __REG32 int_urxd0  :2;
  __REG32 int_timer3 :2;
  __REG32 int_timer2 :2;
  __REG32 int_timer1 :2;
  __REG32 int_timer0 :2;
  __REG32 int_bdma1  :2;
  __REG32 int_bdma0  :2;
  __REG32 int_zdma1  :2;
  __REG32 int_zdma0  :2;
  __REG32 eint3      :2;
  __REG32 eint2      :2;
  __REG32 eint1      :2;
  __REG32 eint0      :2;
} __slv_bits;

/* IC: IRQ/FIQ priority of master register */
typedef struct {
  __REG32 mgd    :2;
  __REG32 mgc    :2;
  __REG32 mgb    :2;
  __REG32 mga    :2;
  __REG32 fx_mgd :1; /* fx@mgd */
  __REG32 fx_mgc :1;
  __REG32 fx_mgb :1;
  __REG32 fx_mga :1;
  __REG32 m      :1;
  __REG32        :19;
} __pmst_bits;

/* IC: current IRQ/FIQ priority of master register */
typedef struct {
  __REG32 mgd   :2;
  __REG32 mgb   :2;
  __REG32 mgc   :2;
  __REG32 mga   :2;
  __REG32 vector:6;
  __REG32       :18;
} __cmst_bits;

/* LCD: control register 1 */
typedef struct {
  __REG32 envid   :1;
  __REG32 invvd   :1;
  __REG32 invframe:1;
  __REG32 invline :1;
  __REG32 invclk  :1;
  __REG32 dismode :2;
  __REG32 mmode   :1;
  __REG32 wdly    :2;
  __REG32 wlh     :2;
  __REG32 clkval  :10;
  __REG32 linecnt :10;
} __lcdcon1_bits;


/* LCD: control register 2 */
typedef struct {
  __REG32 lineval   :10;
  __REG32 hozval    :11;
  __REG32 lineblank :11;
} __lcdcon2_bits;

/* LCD: control register 3 */
typedef struct {
  __REG32 selfref:1;
  __REG32        :2;
  __REG32        :29;
} __lcdcon3_bits;

/* LCD: frame buffer start address register 1 */
typedef struct {
  __REG32 lcdbaseu :21;
  __REG32 lcdbank  :6;
  __REG32 modesel  :2;
  __REG32          :3;
} __lcdsaddr1_bits;

/* LCD: frame buffer start address register 2 */
typedef struct {
  __REG32 lcdbasel :21;
  __REG32 mval     :8;
  __REG32 bswp     :1;
  __REG32          :2;
} __lcdsaddr2_bits;

/* LCD: frame buffer start address register 2 */
typedef struct {
  __REG32 pagewidth :9;
  __REG32 offsize   :11;
  __REG32           :12;
} __lcdsaddr3_bits;

/* LCD: red look up  register */
typedef struct {
  __REG32 redval :32;
} __red_bits;

/* LCD: green look up register */
typedef struct {
  __REG32 greenval :32;
} __green_bits;

/* LCD: blue look up register */
typedef struct {
  __REG32 blueval :16;
  __REG32         :16;
} __blue_bits;

/* DMA: ZDMA control register */
typedef struct {
  __REG32 cmd  :2;
  __REG32 qds  :2;
  __REG32 ste  :2;
  __REG32 INT  :2;
  __REG32      :24;
} __zdcon_bits;

/* DMA: ZDMA initial src register */
typedef struct {
  __REG32 saddr:28;
  __REG32 dal   :2;
  __REG32 dst   :2;
} __zdsrc_bits;

/* DMA: ZDMA initial dst register */
typedef struct {
  __REG32 daddr :28;
  __REG32 das    :2;
  __REG32 opt    :2;
} __zddes_bits;

/* DMA: ZDMA initial count register */
typedef struct {
  __REG32 cnt  :20;
  __REG32 en   :1;
  __REG32 ar   :1;
  __REG32 ints :2;
  __REG32 otf  :2;
  __REG32 tmd  :2;
  __REG32 qty  :2;
  __REG32 qsc  :2;
} __zdcnt_bits;

/* DMA: Bridge DMA control register */
typedef struct {
  __REG32 cmd :2;
  __REG32 qds :2;
  __REG32 ste :2;
  __REG32 INT :2;
  __REG32     :24;
} __bdcon_bits;


/* DMA: BDMA initial src register */
typedef struct {
  __REG32 saddr:28;
  __REG32 dal   :2;
  __REG32 dst   :2;
} __bdsrc_bits;

/* DMA: BDMA initial dst register */
typedef struct {
  __REG32 daddr :28;
  __REG32 das    :2;
  __REG32 tdm    :2;
} __bddes_bits;

/* DMA: BDMA initial count register */
typedef struct {
  __REG32 cnt :20;
  __REG32 en   :1;
  __REG32 ar   :1;
  __REG32 ints :2;
  __REG32      :2;
  __REG32      :2;
  __REG32      :2;
  __REG32 qsc  :2;
} __bdcnt_bits;

/* I/O control register */
typedef struct {
  __REG32 pa0  :1;
  __REG32 pa1  :1;
  __REG32 pa2  :1;
  __REG32 pa3  :1;
  __REG32 pa4  :1;
  __REG32 pa5  :1;
  __REG32 pa6  :1;
  __REG32 pa7  :1;
  __REG32 pa8  :1;
  __REG32 pa9  :1;
  __REG32      :22;
  } __pcona_bits;

typedef struct {
  __REG32 pa0  :1;
  __REG32 pa1  :1;
  __REG32 pa2  :1;
  __REG32 pa3  :1;
  __REG32 pa4  :1;
  __REG32 pa5  :1;
  __REG32 pa6  :1;
  __REG32 pa7  :1;
  __REG32 pa8  :1;
  __REG32 pa9  :1;
  __REG32      :22;
  } __pdata_bits;

typedef struct {
  __REG32 pb0  :1;
  __REG32 pb1  :1;
  __REG32 pb2  :1;
  __REG32 pb3  :1;
  __REG32 pb4  :1;
  __REG32 pb5  :1;
  __REG32 pb6  :1;
  __REG32 pb7  :1;
  __REG32 pb8  :1;
  __REG32 pb9  :1;
  __REG32 pb10 :1;
  __REG32      :21;
  } __pconb_bits;

typedef struct {
  __REG32 pb0  :1;
  __REG32 pb1  :1;
  __REG32 pb2  :1;
  __REG32 pb3  :1;
  __REG32 pb4  :1;
  __REG32 pb5  :1;
  __REG32 pb6  :1;
  __REG32 pb7  :1;
  __REG32 pb8  :1;
  __REG32 pb9  :1;
  __REG32 pb10 :1;
  __REG32      :21;
  } __pdatb_bits;

typedef struct {
  __REG32 pc0  :1;
  __REG32 pc1  :1;
  __REG32 pc2  :1;
  __REG32 pc3  :1;
  __REG32 pc4  :1;
  __REG32 pc5  :1;
  __REG32 pc6  :1;
  __REG32 pc7  :1;
  __REG32 pc8  :1;
  __REG32 pc9  :1;
  __REG32 pc10 :1;
  __REG32 pc11 :1;
  __REG32 pc12 :1;
  __REG32 pc13 :1;
  __REG32 pc14 :1;
  __REG32 pc15 :1;
  __REG32      :16;
  } __pconc_bits;

typedef struct {
  __REG32 pc0  :1;
  __REG32 pc1  :1;
  __REG32 pc2  :1;
  __REG32 pc3  :1;
  __REG32 pc4  :1;
  __REG32 pc5  :1;
  __REG32 pc6  :1;
  __REG32 pc7  :1;
  __REG32 pc8  :1;
  __REG32 pc9  :1;
  __REG32 pc10 :1;
  __REG32 pc11 :1;
  __REG32 pc12 :1;
  __REG32 pc13 :1;
  __REG32 pc14 :1;
  __REG32 pc15 :1;
  __REG32      :16;
  } __pdatc_bits;

typedef struct {
  __REG32 pc0  :1;
  __REG32 pc1  :1;
  __REG32 pc2  :1;
  __REG32 pc3  :1;
  __REG32 pc4  :1;
  __REG32 pc5  :1;
  __REG32 pc6  :1;
  __REG32 pc7  :1;
  __REG32 pc8  :1;
  __REG32 pc9  :1;
  __REG32 pc10 :1;
  __REG32 pc11 :1;
  __REG32 pc12 :1;
  __REG32 pc13 :1;
  __REG32 pc14 :1;
  __REG32 pc15 :1;
  __REG32      :16;
  } __pupc_bits;

typedef struct {
  __REG32 pd0  :2;
  __REG32 pd1  :2;
  __REG32 pd2  :2;
  __REG32 pd3  :2;
  __REG32 pd4  :2;
  __REG32 pd5  :2;
  __REG32 pd6  :2;
  __REG32 pd7  :2;
  __REG32      :16;
  } __pcond_bits;

typedef struct {
  __REG32 pd0  :1;
  __REG32 pd1  :1;
  __REG32 pd2  :1;
  __REG32 pd3  :1;
  __REG32 pd4  :1;
  __REG32 pd5  :1;
  __REG32 pd6  :1;
  __REG32 pd7  :1;
  __REG32      :24;
  } __pdatd_bits;

typedef struct {
  __REG32 pd0  :1;
  __REG32 pd1  :1;
  __REG32 pd2  :1;
  __REG32 pd3  :1;
  __REG32 pd4  :1;
  __REG32 pd5  :1;
  __REG32 pd6  :1;
  __REG32 pd7  :1;
  __REG32      :24;
  } __pupd_bits;

typedef struct {
  __REG32 pe0  :2;
  __REG32 pe1  :2;
  __REG32 pe2  :2;
  __REG32 pe3  :2;
  __REG32 pe4  :2;
  __REG32 pe5  :2;
  __REG32 pe6  :2;
  __REG32 pe7  :2;
  __REG32 pe8  :2;
  __REG32      :14;
  } __pcone_bits;

typedef struct {
  __REG32 pe0  :1;
  __REG32 pe1  :1;
  __REG32 pe2  :1;
  __REG32 pe3  :1;
  __REG32 pe4  :1;
  __REG32 pe5  :1;
  __REG32 pe6  :1;
  __REG32 pe7  :1;
  __REG32 pe8  :1;
  __REG32      :23;
  } __pdate_bits;

typedef struct {
  __REG32 pe0  :1;
  __REG32 pe1  :1;
  __REG32 pe2  :1;
  __REG32 pe3  :1;
  __REG32 pe4  :1;
  __REG32 pe5  :1;
  __REG32 pe6  :1;
  __REG32 pe7  :1;
  __REG32      :24;
  } __pupe_bits;

typedef struct {
  __REG32 pf0  :2;
  __REG32 pf1  :2;
  __REG32 pf2  :2;
  __REG32 pf3  :2;
  __REG32 pf4  :2;
  __REG32 pf5  :3;
  __REG32 pf6  :3;
  __REG32 pf7  :3;
  __REG32 pf8  :3;
  __REG32      :10;
  } __pconf_bits;

typedef struct {
  __REG32 pf0  :1;
  __REG32 pf1  :1;
  __REG32 pf2  :1;
  __REG32 pf3  :1;
  __REG32 pf4  :1;
  __REG32 pf5  :1;
  __REG32 pf6  :1;
  __REG32 pf7  :1;
  __REG32 pf8  :1;
  __REG32      :23;
  } __pdatf_bits;

typedef struct {
  __REG32 pf0  :1;
  __REG32 pf1  :1;
  __REG32 pf2  :1;
  __REG32 pf3  :1;
  __REG32 pf4  :1;
  __REG32 pf5  :1;
  __REG32 pf6  :1;
  __REG32 pf7  :1;
  __REG32 pf8  :1;
  __REG32      :23;
  } __pupf_bits;

typedef struct {
  __REG32 pg0  :2;
  __REG32 pg1  :2;
  __REG32 pg2  :2;
  __REG32 pg3  :2;
  __REG32 pg4  :2;
  __REG32 pg5  :2;
  __REG32 pg6  :2;
  __REG32 pg7  :2;
  __REG32      :16;
  } __pcong_bits;

typedef struct {
  __REG32 pg0  :1;
  __REG32 pg1  :1;
  __REG32 pg2  :1;
  __REG32 pg3  :1;
  __REG32 pg4  :1;
  __REG32 pg5  :1;
  __REG32 pg6  :1;
  __REG32 pg7  :1;
  __REG32      :24;
  } __pdatg_bits;

typedef struct {
  __REG32 pg0  :1;
  __REG32 pg1  :1;
  __REG32 pg2  :1;
  __REG32 pg3  :1;
  __REG32 pg4  :1;
  __REG32 pg5  :1;
  __REG32 pg6  :1;
  __REG32 pg7  :1;
  __REG32      :24;
  } __pupg_bits;

typedef struct {
  __REG32 spucr0 :1;
  __REG32 spucr1 :1;
  __REG32 hzstop :1;
  __REG32        :29;
  } __spucr_bits;

typedef struct {
  __REG32 eint0 :3;
  __REG32       :1;
  __REG32 eint1 :3;
  __REG32       :1;
  __REG32 eint2 :3;
  __REG32       :1;
  __REG32 eint3 :3;
  __REG32       :1;
  __REG32 eint4 :3;
  __REG32       :1;
  __REG32 eint5 :3;
  __REG32       :1;
  __REG32 eint6 :3;
  __REG32       :1;
  __REG32 eint7 :3;
  __REG32       :1;
  } __extint_bits;

typedef struct {
  __REG32 extintpnd0 :1;
  __REG32 extintpnd1 :1;
  __REG32 extintpnd2 :1;
  __REG32 extintpnd3 :1;
  __REG32            :28;
  } __extintpnd_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcmpb0_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcntb0_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcnto0_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcmpb1_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcntb1_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcnto1_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcmpb2_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcntb2_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcnto2_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcmpb3_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcntb3_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcnto3_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcmpb4_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcntb4_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcnto4_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcntb5_bits;

typedef struct {
  __REG32 b0  : 1;
  __REG32 b1  : 1;
  __REG32 b2  : 1;
  __REG32 b3  : 1;
  __REG32 b4  : 1;
  __REG32 b5  : 1;
  __REG32 b6  : 1;
  __REG32 b7  : 1;
  __REG32 b8  : 1;
  __REG32 b9  : 1;
  __REG32 b10 : 1;
  __REG32 b11 : 1;
  __REG32 b12 : 1;
  __REG32 b13 : 1;
  __REG32 b14 : 1;
  __REG32 b15 : 1;
  __REG32     :16;
  } __tcnto5_bits;

typedef struct {
  __REG32 int_adc     :1;
  __REG32 int_rtc     :1;
  __REG32 int_utxd1   :1;
  __REG32 int_utxd2   :1;
  __REG32 int_sio     :1;
  __REG32 int_iic     :1;
  __REG32 int_urxd1   :1;
  __REG32 int_urxd0   :1;
  __REG32 int_timer5  :1;
  __REG32 int_timer4  :1;
  __REG32 int_timer3  :1;
  __REG32 int_timer2  :1;
  __REG32 int_timer1  :1;
  __REG32 int_timer0  :1;
  __REG32 int_uerr0   :1;
  __REG32 int_wdt     :1;
  __REG32 int_bdma1   :1;
  __REG32 int_bdma0   :1;
  __REG32 int_zdma1   :1;
  __REG32 int_zdma0   :1;
  __REG32 int_tick    :1;
  __REG32 eint4567    :1;
  __REG32 eint3       :1;
  __REG32 eint2       :1;
  __REG32 eint1       :1;
  __REG32 eint0       :1;
  __REG32             :6;
  } __i_ispr_bits;

typedef struct {
  __REG32 int_adc     :1;
  __REG32 int_rtc     :1;
  __REG32 int_utxd1   :1;
  __REG32 int_utxd2   :1;
  __REG32 int_sio     :1;
  __REG32 int_iic     :1;
  __REG32 int_urxd1   :1;
  __REG32 int_urxd0   :1;
  __REG32 int_timer5  :1;
  __REG32 int_timer4  :1;
  __REG32 int_timer3  :1;
  __REG32 int_timer2  :1;
  __REG32 int_timer1  :1;
  __REG32 int_timer0  :1;
  __REG32 int_uerr0   :1;
  __REG32 int_wdt     :1;
  __REG32 int_bdma1   :1;
  __REG32 int_bdma0   :1;
  __REG32 int_zdma1   :1;
  __REG32 int_zdma0   :1;
  __REG32 int_tick    :1;
  __REG32 eint4567    :1;
  __REG32 eint3       :1;
  __REG32 eint2       :1;
  __REG32 eint1       :1;
  __REG32 eint0       :1;
  __REG32             :6;
  } __i_ispc_bits;

typedef struct {
  __REG32 int_adc     :1;
  __REG32 int_rtc     :1;
  __REG32 int_utxd1   :1;
  __REG32 int_utxd2   :1;
  __REG32 int_sio     :1;
  __REG32 int_iic     :1;
  __REG32 int_urxd1   :1;
  __REG32 int_urxd0   :1;
  __REG32 int_timer5  :1;
  __REG32 int_timer4  :1;
  __REG32 int_timer3  :1;
  __REG32 int_timer2  :1;
  __REG32 int_timer1  :1;
  __REG32 int_timer0  :1;
  __REG32 int_uerr0   :1;
  __REG32 int_wdt     :1;
  __REG32 int_bdma1   :1;
  __REG32 int_bdma0   :1;
  __REG32 int_zdma1   :1;
  __REG32 int_zdma0   :1;
  __REG32 int_tick    :1;
  __REG32 eint4567    :1;
  __REG32 eint3       :1;
  __REG32 eint2       :1;
  __REG32 eint1       :1;
  __REG32 eint0       :1;
  __REG32             :6;
  } __f_ispc_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  CPU WRAPPER Special Register
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG,0x01c00000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__NCACHBE0,0x01c00004,__READ_WRITE,__ncach0_bits);
__IO_REG32_BIT(__NCACHBE1,0x01c00008,__READ_WRITE,__ncach1_bits);
__IO_REG32_BIT(__SBUSCON,0x01c40000,__READ_WRITE,__sbuscon_bits);

/***************************************************************************
 **
 **  Memory Controller special registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__BWSCON,0x01c80000,__READ_WRITE,__bwscon_bits);
__IO_REG32_BIT(__BANKCON0,0x01c80004,__READ_WRITE,__bankcon0_bits);
__IO_REG32_BIT(__BANKCON1,0x01c80008,__READ_WRITE,__bankcon1_bits);
__IO_REG32_BIT(__BANKCON2,0x01c8000c,__READ_WRITE,__bankcon2_bits);
__IO_REG32_BIT(__BANKCON3,0x01c80010,__READ_WRITE,__bankcon3_bits);
__IO_REG32_BIT(__BANKCON4,0x01c80014,__READ_WRITE,__bankcon4_bits);
__IO_REG32_BIT(__BANKCON5,0x01c80018,__READ_WRITE,__bankcon5_bits);
__IO_REG32_BIT(__BANKCON6,0x01c8001c,__READ_WRITE,__bankcon6_bits);
__IO_REG32_BIT(__BANKCON7,0x01c80020,__READ_WRITE,__bankcon7_bits);
__IO_REG32_BIT(__REFRESH,0x01c80024,__READ_WRITE,__refresh_bits);
__IO_REG32_BIT(__BANKSIZE,0x01c80028,__READ_WRITE,__banksize_bits);
__IO_REG32_BIT(__MRSRB6,0x01c8002c,__READ_WRITE,__mrsr_bits);
__IO_REG32_BIT(__MRSRB7,0x01c80030,__READ_WRITE,__mrsr_bits);


/***************************************************************************
 **
 **  UART
 **
 ***************************************************************************/
__IO_REG32_BIT(__ULCON0,0x01d00000,__READ_WRITE,__ulcon0_bits);
__IO_REG32_BIT(__ULCON1,0x01d04000,__READ_WRITE,__ulcon1_bits);
__IO_REG32_BIT(__UCON0,0x01d00004,__READ_WRITE,__ucon0_bits);
__IO_REG32_BIT(__UCON1,0x01d04004,__READ_WRITE,__ucon1_bits);
__IO_REG32_BIT(__UFCON0,0x01d00008,__READ_WRITE,__ufcon_bits);
__IO_REG32_BIT(__UFCON1,0x01d04008,__READ_WRITE,__ufcon_bits);
__IO_REG32_BIT(__UMCON0,0x01d0000c,__READ_WRITE,__umcon_bits);
__IO_REG32_BIT(__UMCON1,0x01d0400c,__READ_WRITE,__umcon_bits);
__IO_REG32_BIT(__UTRSTAT0,0x01d00010,__READ,__utrstat_bits);
__IO_REG32_BIT(__UTRSTAT1,0x01d04010,__READ,__utrstat_bits);
__IO_REG32_BIT(__UERSTAT0,0x01d00014,__READ,__uerstat_bits);
__IO_REG32_BIT(__UERSTAT1,0x01d04014,__READ,__uerstat_bits);
__IO_REG32_BIT(__UFSTAT0,0x01d00018,__READ,__ufstat_bits);
__IO_REG32_BIT(__UFSTAT1,0x01d04018,__READ,__ufstat_bits);
__IO_REG32_BIT(__UMSTAT0,0x01d0001c,__READ,__umstat_bits);
__IO_REG32_BIT(__UMSTAT1,0x01d0401c,__READ,__umstat_bits);
__IO_REG32_BIT(__UTXH0,0x01d00020,__WRITE,__utx_bits);
__IO_REG32_BIT(__UTXH1,0x01d04020,__WRITE,__utx_bits);
__IO_REG32_BIT(__URXH0,0x01d00024,__READ,__urx_bits);
__IO_REG32_BIT(__URXH1,0x01d04024,__READ,__urx_bits);
__IO_REG32_BIT(__UBRDIV0,0x01d00028,__READ_WRITE,__ubrdiv0_bits);
__IO_REG32_BIT(__UBRDIV1,0x01d04028,__READ_WRITE,__ubrdiv1_bits);


/***************************************************************************
 **
 **  SIO
 **
 ***************************************************************************/
__IO_REG32_BIT(__SIOCON,0x01d14000,__READ_WRITE,__siocon_bits);
__IO_REG32_BIT(__SIODAT,0x01d14004,__READ_WRITE,__siodat_bits);
__IO_REG32_BIT(__SBRDR,0x01d14008,__READ_WRITE,__sbrdr_bits);
__IO_REG32_BIT(__IVTCNT,0x01d1400c,__READ_WRITE,__ivtcnt_bits);
__IO_REG32_BIT(__DCNTZ,0x01d14010,__READ_WRITE,__dcntz_bits);

/***************************************************************************
 **
 **  IIS
 **
 ***************************************************************************/
__IO_REG32_BIT(__IISCON,0x01d18000,__READ_WRITE, __iiscon_bits);
__IO_REG32_BIT(__IISMOD,0x01d18004,__READ_WRITE, __iismod_bits);
__IO_REG32_BIT(__IISPSR,0x01d18008,__READ_WRITE, __iispsr_bits);
__IO_REG32(__IISFIFCON,0x01d1800c,__READ_WRITE);
__IO_REG32_BIT(__IISFIF,0x01d18010,__READ_WRITE,__iisfif_bits);

/***************************************************************************
 **
 **  I/O PORT
 **
 ***************************************************************************/
__IO_REG32_BIT(__PCONA,0x01d20000,__READ_WRITE, __pcona_bits);
__IO_REG32_BIT(__PDATA,0x01d20004,__READ_WRITE, __pdata_bits);
__IO_REG32_BIT(__PCONB,0x01d20008,__READ_WRITE, __pconb_bits);
__IO_REG32_BIT(__PDATB,0x01d2000c,__READ_WRITE, __pdatb_bits);
__IO_REG32_BIT(__PCONC,0x01d20010,__READ_WRITE, __pconc_bits);
__IO_REG32_BIT(__PDATC,0x01d20014,__READ_WRITE, __pdatc_bits);
__IO_REG32_BIT(__PUPC,0x01d20018,__READ_WRITE, __pupc_bits);
__IO_REG32_BIT(__PCOND,0x01d2001c,__READ_WRITE, __pcond_bits);
__IO_REG32_BIT(__PDATD,0x01d20020,__READ_WRITE, __pdatd_bits);
__IO_REG32_BIT(__PUPD,0x01d20024,__READ_WRITE, __pupd_bits);
__IO_REG32_BIT(__PCONE,0x01d20028,__READ_WRITE, __pcone_bits);
__IO_REG32_BIT(__PDATE,0x01d2002c,__READ_WRITE, __pdate_bits);
__IO_REG32_BIT(__PUPE,0x01d20030,__READ_WRITE, __pupe_bits);
__IO_REG32_BIT(__PCONF,0x01d20034,__READ_WRITE, __pconf_bits);
__IO_REG32_BIT(__PDATF,0x01d20038,__READ_WRITE, __pdatf_bits);
__IO_REG32_BIT(__PUPF,0x01d2003c,__READ_WRITE, __pupf_bits);
__IO_REG32_BIT(__PCONG,0x01d20040,__READ_WRITE, __pcong_bits);
__IO_REG32_BIT(__PDATG,0x01d20044,__READ_WRITE, __pdatg_bits);
__IO_REG32_BIT(__PUPG,0x01d20048,__READ_WRITE, __pupg_bits);
__IO_REG32_BIT(__SPUCR,0x01d2004c,__READ_WRITE, __spucr_bits);
__IO_REG32_BIT(__EXTINT,0x01d20050,__READ_WRITE, __extint_bits);
__IO_REG32_BIT(__EXTINPND,0x01d20054,__READ_WRITE, __extintpnd_bits);

/***************************************************************************
 **
 **  watch-dog timer
 **
 ***************************************************************************/
__IO_REG32_BIT(__WTCON,0x01d30000,__READ_WRITE,__wtcon_bits);
__IO_REG32_BIT(__WTDAT,0x01d30004,__READ_WRITE,__wtdat_bits);
__IO_REG32_BIT(__WTCNT,0x01d30008,__READ_WRITE,__wtcnt_bits);

/***************************************************************************
 **
 **  A/D converter
 **
 ***************************************************************************/
__IO_REG32_BIT(__ADCCON,0x01d40000,__READ_WRITE,__adccon_bits);
__IO_REG32_BIT(__ADCPSR,0x01d40004,__READ_WRITE,__adcpsr_bits);
__IO_REG32_BIT(__ADCDAT,0x01d40008,__READ,__adcdat_bits);

/***************************************************************************
 **
 **  PWM TIMER
 **
 ***************************************************************************/
__IO_REG32_BIT(__TCFG0,0x01d50000,__READ_WRITE,__tcfg0_bits);
__IO_REG32_BIT(__TCFG1,0x01d50004,__READ_WRITE,__tcfg1_bits);
__IO_REG32_BIT(__TCON,0x01d50008,__READ_WRITE,__tcon_bits);
__IO_REG32_BIT(__TCNTB0,0x01d5000c,__READ_WRITE,__tcntb0_bits);
__IO_REG32_BIT(__TCMPB0,0x01d50010,__READ_WRITE,__tcmpb0_bits);
__IO_REG32_BIT(__TCNTO0,0x01d50014,__READ,__tcnto0_bits);
__IO_REG32_BIT(__TCNTB1,0x01d50018,__READ_WRITE,__tcntb1_bits);
__IO_REG32_BIT(__TCMPB1,0x01d5001c,__READ_WRITE,__tcmpb1_bits);
__IO_REG32_BIT(__TCNTO1,0x01d50020,__READ,__tcnto1_bits);
__IO_REG32_BIT(__TCNTB2,0x01d50024,__READ_WRITE,__tcntb2_bits);
__IO_REG32_BIT(__TCMPB2,0x01d50028,__READ_WRITE,__tcmpb2_bits);
__IO_REG32_BIT(__TCNTO2,0x01d5002c,__READ,__tcnto2_bits);
__IO_REG32_BIT(__TCNTB3,0x01d50030,__READ_WRITE,__tcntb3_bits);
__IO_REG32_BIT(__TCMPB3,0x01d50034,__READ_WRITE,__tcmpb3_bits);
__IO_REG32_BIT(__TCNTO3,0x01d50038,__READ,__tcnto3_bits);
__IO_REG32_BIT(__TCNTB4,0x01d5003c,__READ_WRITE,__tcntb4_bits);
__IO_REG32_BIT(__TCMPB4,0x01d50040,__READ_WRITE,__tcmpb4_bits);
__IO_REG32_BIT(__TCNTO4,0x01d50044,__READ,__tcnto4_bits);
__IO_REG32_BIT(__TCNTB5,0x01d50048,__READ_WRITE,__tcntb5_bits);
__IO_REG32_BIT(__TCNTO5,0x01d5004c,__READ,__tcnto5_bits);

/***************************************************************************
 **
 **  IIC
 **
 ***************************************************************************/

__IO_REG32_BIT(__IICCON,0x01d60000,__READ_WRITE,__iiccon_bits);
__IO_REG32_BIT(__IICSTAT,0x01d60004,__READ_WRITE,__iicstat_bits);
__IO_REG32_BIT(__IICADD,0x01d60008,__READ_WRITE,__iicadd_bits);
__IO_REG32_BIT(__IICDS,0x01d6000c,__READ_WRITE,__iicds_bits);


/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(__RTCCON,0x01d70040,__READ_WRITE,__rtccon_bits);
__IO_REG32_BIT(__RTCALM,0x01d70050,__READ_WRITE,__rtcalm_bits);
__IO_REG32_BIT(__ALMSEC,0x01d70054,__READ_WRITE,__almsec_bits);
__IO_REG32_BIT(__ALMMIN,0x01d70058,__READ_WRITE,__almmin_bits);
__IO_REG32_BIT(__ALMHOUR,0x01d7005c,__READ_WRITE,__almhour_bits);
__IO_REG32_BIT(__ALMDAY,0x01d70060,__READ_WRITE,__almday_bits);
__IO_REG32_BIT(__ALMMON,0x01d70064,__READ_WRITE,__almmon_bits);
__IO_REG32_BIT(__ALMYEAR,0x01d70068,__READ_WRITE,__almyear_bits);
__IO_REG32_BIT(__RTCRST,0x01d7006c,__READ_WRITE,__rtcrst_bits);
__IO_REG32_BIT(__BCDSEC,0x01d70070,__READ_WRITE,__bcdsec_bits);
__IO_REG32_BIT(__BCDMIN,0x01d70074,__READ_WRITE,__bcdmin_bits);
__IO_REG32_BIT(__BCDHOUR,0x01d70078,__READ_WRITE,__bcdhour_bits);
__IO_REG32_BIT(__BCDDAY,0x01d7007c,__READ_WRITE,__bcdday_bits);
__IO_REG32_BIT(__BCDDATE,0x01d70080,__READ_WRITE,__bcddate_bits);
__IO_REG32_BIT(__BCDMON,0x01d70084,__READ_WRITE,__bcdmon_bits);
__IO_REG32_BIT(__BCDYEAR,0x01d70088,__READ_WRITE,__bcdyear_bits);
__IO_REG32_BIT(__TICNT,0x01d7008c,__READ_WRITE,__ticnt_bits);


/***************************************************************************
 **
 **  CLOCK & POWER MANAGEMENT
 **
 ***************************************************************************/
__IO_REG32_BIT(__PLLCON,0x01d80000,__READ_WRITE,__pllcon_bits);
__IO_REG32_BIT(__CLKCON,0x01d80004,__READ_WRITE,__clkcon_bits);
__IO_REG32_BIT(__CLKSLOW,0x01d80008,__READ_WRITE,__clkslow_bits);
__IO_REG32_BIT(__LOCKTIME,0x01d8000c,__READ_WRITE,__locktime_bits);


/***************************************************************************
 **
 **   INTERRUPT CONTROLLER
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTCON,0x01e00000,__READ_WRITE,__intcon_bits);
__IO_REG32_BIT(__INTPND,0x01e00004,__READ,__intpndmodispc_bits);
__IO_REG32_BIT(__INTMOD,0x01e00008,__READ_WRITE,__intpndmodispc_bits);
__IO_REG32_BIT(__INTMSK,0x01e0000c,__READ_WRITE,__intmsk_bits);
__IO_REG32_BIT(__I_PSLV,0x01e00010,__READ_WRITE,__slv_bits);
__IO_REG32_BIT(__I_PMST,0x01e00014,__READ_WRITE,__pmst_bits);
__IO_REG32_BIT(__I_CSLV,0x01e00018,__READ,__slv_bits);
__IO_REG32_BIT(__I_CMST,0x01e0001c,__READ,__cmst_bits);
__IO_REG32_BIT(__I_ISPR,0x01e00020,__READ,__i_ispr_bits);
__IO_REG32_BIT(__I_ISPC,0x01e00024,__WRITE,__i_ispc_bits);
__IO_REG32_BIT(__F_ISPR,0x01e00038,__READ,__intpndmodispc_bits);
__IO_REG32_BIT(__F_ISPC,0x01e0003c,__WRITE,__f_ispc_bits);

/***************************************************************************
 **
 **   LCD CONTROLLER
 **
 ***************************************************************************/
__IO_REG32_BIT(__LCDCON1,0x01f00000,__READ_WRITE,__lcdcon1_bits);
__IO_REG32_BIT(__LCDCON2,0x01f00004,__READ_WRITE,__lcdcon2_bits);
__IO_REG32_BIT(__LCDCON3,0x01f00040,__READ_WRITE,__lcdcon3_bits);
__IO_REG32_BIT(__LCDSADDR1,0x01f00008,__READ_WRITE,__lcdsaddr1_bits);
__IO_REG32_BIT(__LCDSADDR2,0x01f0000c,__READ_WRITE,__lcdsaddr2_bits);
__IO_REG32_BIT(__LCDSADDR3,0x01f00010,__READ_WRITE,__lcdsaddr3_bits);
__IO_REG32_BIT(__REDLUT,0x01f00014,__READ_WRITE,__red_bits);
__IO_REG32_BIT(__GREENLUT,0x01f00018,__READ_WRITE,__green_bits);
__IO_REG32_BIT(__BLUELUT,0x01f0001c,__READ_WRITE,__blue_bits);
__IO_REG32(__DP1_2,0x01f00020,__READ_WRITE);
__IO_REG32(__DP4_7,0x01f00024,__READ_WRITE);
__IO_REG32(__DP3_5,0x01f00028,__READ_WRITE);
__IO_REG32(__DP2_3,0x01f0002c,__READ_WRITE);
__IO_REG32(__DP5_7,0x01f00030,__READ_WRITE);
__IO_REG32(__DP3_4,0x01f00034,__READ_WRITE);
__IO_REG32(__DP4_5,0x01f00038,__READ_WRITE);
__IO_REG32(__DP6_7,0x01f0003c,__READ_WRITE);
__IO_REG32(__DITHMODE,0x01f00044,__READ_WRITE);


/***************************************************************************
 **
 **   DMA
 **
 ***************************************************************************/
__IO_REG32_BIT(__ZDCON0,0x01e80000,__READ_WRITE,__zdcon_bits);
__IO_REG32_BIT(__ZDISRC0,0x01e80004,__READ_WRITE,__zdsrc_bits);
__IO_REG32_BIT(__ZDIDES0,0x01e80008,__READ_WRITE,__zddes_bits);
__IO_REG32_BIT(__ZDICNT0,0x01e8000c,__READ_WRITE,__zdcnt_bits);
__IO_REG32_BIT(__ZDCSRC0,0x01e80010,__READ,__zdsrc_bits);
__IO_REG32_BIT(__ZDCDES0,0x01e80014,__READ,__zddes_bits);
__IO_REG32_BIT(__ZDCCNT0,0x01e80018,__READ,__zdcnt_bits);
__IO_REG32_BIT(__ZDCON1,0x01e80020,__READ,__zdcon_bits);
__IO_REG32_BIT(__ZDISRC1,0x01e80024,__READ_WRITE,__zdsrc_bits);
__IO_REG32_BIT(__ZDIDES1,0x01e80028,__READ_WRITE,__zddes_bits);
__IO_REG32_BIT(__ZDICNT1,0x01e8002c,__READ_WRITE,__zdcnt_bits);
__IO_REG32_BIT(__ZDCSRC1,0x01e80030,__READ_WRITE,__zdsrc_bits);
__IO_REG32_BIT(__ZDCDES1,0x01e80034,__READ,__zddes_bits);
__IO_REG32_BIT(__ZDCCNT1,0x01e80038,__READ,__zdcnt_bits);
__IO_REG32_BIT(__BDCON0,0x01f80000,__READ,__bdcon_bits);
__IO_REG32_BIT(__BDISRC0,0x01f80004,__READ,__bdsrc_bits);
__IO_REG32_BIT(__BDIDES0,0x01f80008,__READ_WRITE,__bddes_bits);
__IO_REG32_BIT(__BDICNT0,0x01f8000c,__READ_WRITE,__bdcnt_bits);
__IO_REG32_BIT(__BDCSRC0,0x01f80010,__READ_WRITE,__bdsrc_bits);
__IO_REG32_BIT(__BDCDES0,0x01f80014,__READ_WRITE,__bddes_bits);
__IO_REG32_BIT(__BDCCNT0,0x01f80018,__READ,__bdcnt_bits);
__IO_REG32_BIT(__BDCON1,0x01f80020,__READ,__bdcon_bits);
__IO_REG32_BIT(__BDISRC1,0x01f80024,__READ,__bdsrc_bits);
__IO_REG32_BIT(__BDIDES1,0x01f80028,__READ,__bddes_bits);
__IO_REG32_BIT(__BDICNT1,0x01f8002c,__READ_WRITE,__bdcnt_bits);
__IO_REG32_BIT(__BDCSRC1,0x01f80030,__READ_WRITE,__bdsrc_bits);
__IO_REG32_BIT(__BDCDES1,0x01f80034,__READ_WRITE,__bddes_bits);
__IO_REG32_BIT(__BDCCNT1,0x01f80038,__READ_WRITE,__bdcnt_bits);






/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3C44B0X interrupt sources
 **
 ***************************************************************************/
#define EINT0       0x00000020 /* External interrupt 0                  */
#define EINT1       0x00000024 /* External interrupt 1                  */
#define EINT2       0x00000028 /* External interrupt 2                  */
#define EINT3       0x0000002c /* External interrupt 3                  */
#define EINT4567    0x00000030 /* External interrupt 4/5/6/7            */
#define TICK        0x00000034 /* RTC Time tick interrupt               */
#define INT_ZDMA0   0x00000040 /* General DMA0 interrupt                */
#define INT_ZDMA1   0x00000044 /* General DMA1 interrupt                */
#define INT_BDMA0   0x00000048 /* Bridge DMA0 interrupt                 */
#define INT_BDMA1   0x0000004c /* Bridge DMA1 interrupt                 */
#define INT_WDT     0x00000050 /* Watch-Dog interrupt                   */
#define INT_UERR01  0x00000054 /* UART0/1 error interrupt               */
#define INT_TIMER0  0x00000060 /* Timer0 interrupt                      */
#define INT_TIMER1  0x00000064 /* Timer1 interrupt                      */
#define INT_TIMER2  0x00000068 /* Timer2 interrupt                      */
#define INT_TIMER3  0x0000006c /* Timer3 interrupt                      */
#define INT_TIMER4  0x00000070 /* Timer4 interrupt                      */
#define INT_TIMER5  0x00000074 /* Timer5 interrupt                      */
#define INT_USR1    0x00000080 /* UART0 receive interrupt               */
#define INT_RXC0    0x00000084 /* UART1 receive interrupt               */
#define INT_RXC1    0x00000088 /* IIC interrupt                         */
#define INT_TXC0    0x0000008c /* SIO interrupt                         */
#define INT_TXC1    0x00000090 /* UART0 transmit interrupt              */
#define INT_UTXD1   0x00000094 /* UART1 transmit interrupt              */
#define INT_RTC     0x000000a0 /* RTC alarm interrupt                   */
#define INT_ADC     0x000000c0 /* ADC EOC interrupt                     */


#endif    /* __S3C44B0X_H */
