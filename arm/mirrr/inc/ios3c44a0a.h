/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C44A0A
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2000
 **
 **    $Revision: 1.3 $
 **
 ***************************************************************************/

#ifndef __S3C44A0A_H
#define __S3C44A0A_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C44A0A SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* MEMC: bus width & wait control register*/
typedef struct {
  __REG32 endian:1;
  __REG32 dw0   :2;
  __REG32       :1;
  __REG32 dw1   :2;
  __REG32 ws1   :1;
  __REG32       :1;
  __REG32 dw2   :2;
  __REG32 ws2   :1;
  __REG32       :1;
  __REG32 dw3   :2;
  __REG32 ws3   :1;
  __REG32       :1;
  __REG32 dw4   :2;
  __REG32 ws4   :1;
  __REG32       :1;
  __REG32 dw5   :2;
  __REG32 ws5   :1;
  __REG32       :1;
  __REG32 dw6   :2;
  __REG32 ws6   :1;
  __REG32       :1;
  __REG32 dw7   :2;
  __REG32 ws7   :1;
  __REG32       :1;
} __bwscon_bits;

/* MEMC: bank control register 1-5 and 6,7 (MT=00 ROM or SRAM)*/
typedef struct {
  __REG32 pmc  :2;
  __REG32 tacp :2;
  __REG32 tah  :2;
  __REG32 tcoh :3;
  __REG32 tacc :3;
  __REG32 tcos :2;
  __REG32 tacs :2;
  __REG32 mt   :2;
  __REG32      :2;
  __REG32      :12;
} __bankcon_bits;

/* MEMC: bank control register 6 and 7 (MT=10 FP DRAM or MT=01 EDO DRAM)*/
typedef struct {
  __REG32 can  :2;
  __REG32 tcp  :1;
  __REG32 tcas :2;
  __REG32 trcd :2;
  __REG32 trp  :2;
  __REG32      :7;
  __REG32 mt   :2;
  __REG32      :2;
  __REG32      :12;
} __bankcon67b_bits;

/* MEMC: bank control register 6 and 7  (MT=11 SDRAM) */
typedef struct {
  __REG32 md   :2;
  __REG32 scan :1;
  __REG32 trcd :2;
  __REG32 trp  :2;
  __REG32      :9;
  __REG32 mt   :2;
  __REG32      :2;
  __REG32      :12;
} __bankcon67c_bits;

/* MEMC: SDRAM mode register */
typedef struct {
  __REG32 bl   :3;
  __REG32 bt   :1;
  __REG32 cl   :3;
  __REG32 tm   :2;
  __REG32 wbl  :1;
  __REG32      :22;
} __mrsr_bits;

/* MEMC: DRAM/SDRAM refresh control register */
typedef struct {
  __REG32          :1;
  __REG32 tcsr     :1;
  __REG32 tchr     :2;
  __REG32 ren      :1;
  __REG32 rc       :11;
  __REG32 sdren    :1;
  __REG32          :2;
  __REG32 buslatch :2;
  __REG32          :11;
} __dramcon_bits;

/* CLKPOW: PLL configuration register */
typedef struct {
  __REG32 sdiv  :2;
  __REG32       :2;
  __REG32 pdiv  :6;
  __REG32       :2;
  __REG32 mdiv  :8;
  __REG32       :12;
} __pllcon_bits;

/* CLKPOW: clock generator control register */
typedef struct {
  __REG32 stop     :1;
  __REG32 sl_idle  :1;
  __REG32 idle     :1;
  __REG32 pwmtimer :1;
  __REG32 zdma     :1;
  __REG32 sio      :1;
  __REG32 lcdc     :1;
  __REG32 bdma     :1;
  __REG32 uart0    :1;
  __REG32 uart1    :1;
  __REG32 gpio     :1;
  __REG32 rtc      :1;
  __REG32 adc      :1;
  __REG32 iic      :1;
  __REG32          :18;
} __clkcon_bits;

/* CLKPOW: clock slow control register */
typedef struct {
  __REG32 slow_val :4;
  __REG32 slow_bit :1;
  __REG32 pll_off  :1;
  __REG32          :26;
} __clkslow_bits;

/* CPUWRAP: system configuration register */
typedef struct {
  __REG32 se    :1;
  __REG32 cm    :2;
  __REG32 we    :1;
  __REG32 rse   :1;
  __REG32 da    :1;
  __REG32 bsfrd :1;
  __REG32       :25;
} __syscfg_bits;

/* CPUWRAP: start address & end address of non-cacheable area 0 register */
typedef struct {
  __REG32 sa0   :16;
  __REG32 se0   :16;
} __ncachbe0_bits;

/* CPUWRAP: start address & end address of non-cacheable area 1 register */
typedef struct {
  __REG32 sa1   :16;
  __REG32 se1   :16;
} __ncachbe1_bits;

/* BUSPRIOR: system bus priority controller register */
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
  __REG32 isaddr:28;
  __REG32 dal   :2;
  __REG32 dst   :2;
} __zdisrc_bits;

/* DMA: ZDMA current src register */
typedef struct {
  __REG32 csaddr:28;
  __REG32 dal   :2;
  __REG32 dst   :2;
} __zdcsrc_bits;

/* DMA: ZDMA initial dst register */
typedef struct {
  __REG32 idaddr :28;
  __REG32 das    :2;
  __REG32 opt    :2;
} __zdides_bits;

/* DMA: ZDMA current dst register */
typedef struct {
  __REG32 cdaddr :28;
  __REG32 das    :2;
  __REG32 opt    :2;
} __zdcdes_bits;

/* DMA: ZDMA initial count register */
typedef struct {
  __REG32 icnt :20;
  __REG32 en   :1;
  __REG32 ar   :1;
  __REG32 ints :2;
  __REG32 otf  :2;
  __REG32 tmd  :2;
  __REG32 qty  :2;
  __REG32 qsc  :2;
} __zdicnt_bits;

/* DMA: ZDMA current count register */
typedef struct {
  __REG32 ccnt :20;
  __REG32 en   :1;
  __REG32 ar   :1;
  __REG32 ints :2;
  __REG32 otf  :2;
  __REG32 tmd  :2;
  __REG32 qty  :2;
  __REG32 qsc  :2;
} __zdccnt_bits;

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
  __REG32 isaddr:28;
  __REG32 dal   :2;
  __REG32 dst   :2;
} __bdisrc_bits;

/* DMA: BDMA current src register */
typedef struct {
  __REG32 csaddr:28;
  __REG32 dal   :2;
  __REG32 dst   :2;
} __bdcsrc_bits;

/* DMA: BDMA initial dst register */
typedef struct {
  __REG32 idaddr :28;
  __REG32 das    :2;
  __REG32 opt    :2;
} __bdides_bits;

/* DMA: BDMA current dst register */
typedef struct {
  __REG32 cdaddr :28;
  __REG32 das    :2;
  __REG32 tdm    :2;
} __bdcdes_bits;

/* DMA: BDMA initial count register */
typedef struct {
  __REG32 icnt :20;
  __REG32 en   :1;
  __REG32 ar   :1;
  __REG32 ints :2;
  __REG32      :2;
  __REG32      :2;
  __REG32      :2;
  __REG32 qsc  :2;
} __bdicnt_bits;

/* DMA: BDMA current count register */
typedef struct {
  __REG32 ccnt :20;
  __REG32 en   :1;
  __REG32 ar   :1;
  __REG32 ints :2;
  __REG32      :2;
  __REG32      :2;
  __REG32      :2;
  __REG32 qsc  :2;
} __bdccnt_bits;

/* I/O: Port configuration register A*/
typedef struct {
  __REG32 pa0   :2;
  __REG32 pa1   :2;
  __REG32 pa2   :2;
  __REG32 pa3   :2;
  __REG32 pa4   :2;
  __REG32 pa5   :2;
  __REG32 pa6   :3;
  __REG32 pa7   :3;
  __REG32 pa8   :2;
  __REG32 pa9   :2;
  __REG32       :10;
} __pcona_bits;

/* I/O: Port data register A */
typedef struct {
  __REG32 pa    :10;
  __REG32       :22;
} __pdata_bits;

/* I/O: Port pull-up disable register A */
typedef struct {
  __REG32 en    :10;
  __REG32       :22;
} __pupa_bits;


/* I/O: Port configuration register B*/
typedef struct {
  __REG32 pb0   :1;
  __REG32 pb1   :1;
  __REG32 pb2   :1;
  __REG32 pb3   :1;
  __REG32 pb4   :1;
  __REG32 pb5   :1;
  __REG32 pb6   :1;
  __REG32 pb7   :1;
  __REG32 pb8   :1;
  __REG32       :23;
} __pconb_bits;

/* I/O: Port data register B*/
typedef struct {
  __REG32 pb    :9;
  __REG32       :23;
} __pdatb_bits;


/* I/O: Port configuration register C*/
typedef struct {
  __REG32 pc0   :2;
  __REG32 pc1   :2;
  __REG32 pc2   :2;
  __REG32 pc3   :2;
  __REG32 pc4   :2;
  __REG32 pc5   :2;
  __REG32 pc6   :2;
  __REG32 pc7   :2;
  __REG32 pc8   :2;
  __REG32 pc9   :2;
  __REG32       :12;
} __pconc_bits;

/* I/O: Port data register C*/
typedef struct {
  __REG32 pc   :10;
  __REG32      :22;
} __pdatc_bits;

/* I/O: Port pull-up disable register C*/
typedef struct {
  __REG32 en    :10;
  __REG32       :22;
} __pupc_bits;

/* I/O: Port configuration register D*/
typedef struct {
  __REG32 pd0   :2;
  __REG32 pd1   :2;
  __REG32 pd2   :2;
  __REG32 pd3   :2;
  __REG32 pd4   :2;
  __REG32 pd5   :2;
  __REG32 pd6   :2;
  __REG32 pd7   :2;
  __REG32       :16;
} __pcond_bits;

/* I/O: Port data register D*/
typedef struct {
  __REG32 pd    :8;
  __REG32       :24;
} __pdatd_bits;

/* I/O: Port pull-up disable register D*/
typedef struct {
  __REG32 en    :8;
  __REG32       :24;
} __pupd_bits;

/* I/O: Port configuration register E*/
typedef struct {
  __REG32 pe0   :1;
  __REG32 pe1   :1;
  __REG32 pe2   :1;
  __REG32 pe3   :1;
  __REG32 pe4   :1;
  __REG32 pe5   :1;
  __REG32 pe6   :1;
  __REG32 pe7   :1;
  __REG32       :24;
} __pcone_bits;

/* I/O: Port data register E*/
typedef struct {
  __REG32 pe    :8;
  __REG32       :24;
} __pdate_bits;


/* I/O: Port configuration register F*/
typedef struct {
  __REG32 pf0   :2;
  __REG32 pf1   :2;
  __REG32 pf2   :2;
  __REG32 pf3   :2;
  __REG32 pf4   :2;
  __REG32 pf5   :2;
  __REG32 pf6   :2;
  __REG32       :18;
} __pconf_bits;

/* I/O: Port data register F*/
typedef struct {
  __REG32 pf    :7;
  __REG32       :25;
} __pdatf_bits;

/* I/O: Port pull-up disable register F*/
typedef struct {
  __REG32 en    :7;
  __REG32       :25;
} __pupf_bits;


/* I/O: Port configuration register G*/
typedef struct {
  __REG32 pg0   :2;
  __REG32 pg1   :2;
  __REG32 pg2   :2;
  __REG32 pg3   :2;
  __REG32 pg4   :2;
  __REG32 pg5   :2;
  __REG32 pg6   :2;
  __REG32 pg7   :2;
  __REG32       :16;
} __pcong_bits;

/* I/O: Port data register G*/
typedef struct {
  __REG32 pg        :8;
  __REG32 eintpend6 :1;
  __REG32 eintpend7 :1;
  __REG32           :22;
} __pdatg_bits;

/* I/O: Port pull-up disable register G*/
typedef struct {
  __REG32 en    :8;
  __REG32       :24;
} __pupg_bits;

/* I/O: external interrupt control register */
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


/* I/O: pull-up control register */
typedef struct {
  __REG32 ps0   :1;
  __REG32 ps1   :1;
  __REG32       :30;
} __pups_bits;

/* PWMTIMER: time configuration register */
typedef struct {
  __REG32 pres0 :8;
  __REG32 pres1 :8;
  __REG32 mux0  :2;
  __REG32 mux1  :2;
  __REG32 mux2  :2;
  __REG32 mux3  :2;
  __REG32 dzl   :8;
} __tcfg_bits;

/* PWMTIMER: time control register */
typedef struct {
  __REG32 t0ss  :1;
  __REG32 t0mu  :1;
  __REG32 t0oi  :1;
  __REG32 t0ar  :1;
  __REG32 dzen  :1;
  __REG32       :3;
  __REG32 t1ss  :1;
  __REG32 t1mu  :1;
  __REG32 t1oi  :1;
  __REG32 t1ar  :1;
  __REG32 t2ss  :1;
  __REG32 t2mu  :1;
  __REG32 t2oi  :1;
  __REG32 t2ar  :1;
  __REG32 t3ss  :1;
  __REG32 t3mu  :1;
  __REG32 t3ar  :1;
  __REG32       :13;
} __tcon_bits;



/* UART: line control register */
typedef struct {
  __REG32 wl    :2;
  __REG32 nsb   :1;
  __REG32 pmd   :3;
  __REG32 ir    :1;
  __REG32       :25;
} __ulcon_bits;

/* UART: control register */
typedef struct {
  __REG32 rxm   :2;
  __REG32 txm   :2;
  __REG32 sbs   :1;
  __REG32 lbm   :1;
  __REG32 rxsien:1;
  __REG32 rxtoen:1;
  __REG32       :24;
} __ucon_bits;

/* UART: status register */
typedef struct {
  __REG32 ov   :1;
  __REG32 pe   :1;
  __REG32 fe   :1;
  __REG32 bkd  :1;
  __REG32 rto  :1;
  __REG32 rdr  :1;
  __REG32 tbe  :1;
  __REG32 tse  :1;
  __REG32      :24;
} __ustat_bits;

/* UART: FIFO control register */
typedef struct {
  __REG32 fen  :1;
  __REG32 rfr  :1;
  __REG32 tfr  :1;
  __REG32      :1;
  __REG32 rftl :2;
  __REG32 tftl :2;
  __REG32      :24;
} __ufcon_bits;

/* UART: FIFO control register */
typedef struct {
  __REG32 rxfc  :4;
  __REG32 txfc  :4;
  __REG32 rxff  :1;
  __REG32 txff  :1;
  __REG32       :22;
} __ufstat_bits;

/* Timer: timer mode register */
typedef struct {
  __REG32 te0   :1;
  __REG32 tmd0  :1;
  __REG32 tclr0 :1;
  __REG32 te1   :1;
  __REG32 tmd1  :1;
  __REG32 tclr1 :1;
  __REG32       :26;
} __tmod_bits;

/* Timer: timer data register */
typedef struct {
  __REG32 tdata  :32;
} __tdata_bits;

/* Timer: timer count register */
typedef struct {
  __REG32 tc    :32;
} __tcnt_bits;


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
  __REG32 eint6_eint7:1;
  __REG32 int_wdt   :1;
  __REG32 int_timer3 :1;
  __REG32 int_timer2 :1;
  __REG32 int_timer1 :1;
  __REG32 int_timer0 :1;
  __REG32 int_uerr1 :1;
  __REG32 int_uerr0 :1;
  __REG32 int_bdma1 :1;
  __REG32 int_bdma0 :1;
  __REG32 int_zdma1 :1;
  __REG32 int_zdma0 :1;
  __REG32 eint5     :1;
  __REG32 eint4     :1;
  __REG32 eint3     :1;
  __REG32 eint2     :1;
  __REG32 eint1     :1;
  __REG32 eint0     :1;
  __REG32           :2;
  __REG32           :4;
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
  __REG32 eint6_eint7:1;
  __REG32 int_wdt    :1;
  __REG32 int_timer3 :1;
  __REG32 int_timer2 :1;
  __REG32 int_timer1 :1;
  __REG32 int_timer0 :1;
  __REG32 int_uerr1  :1;
  __REG32 int_uerr0  :1;
  __REG32 int_bdma1  :1;
  __REG32 int_bdma0  :1;
  __REG32 int_zdma1  :1;
  __REG32 int_zdma0  :1;
  __REG32 eint5      :1;
  __REG32 eint4      :1;
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
  __REG32 mgd   :2;
  __REG32 mgc   :2;
  __REG32 mgb   :2;
  __REG32 mga   :2;
  __REG32 fx_mgd:1; /* fx@mgd */
  __REG32 fx_mgc:1;
  __REG32 fx_mgb:1;
  __REG32 fx_mga:1;
  __REG32 m     :1;
  __REG32       :19;
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
  __REG32 hozval    :9;
  __REG32 lineblank :11;
  __REG32 modesel   :2;
} __lcdcon2_bits;

/* LCD: control register 3 */
typedef struct {
  __REG32 selfref:1;
  __REG32        :1;
  __REG32 tm     :1;
  __REG32        :29;
} __lcdcon3_bits;

/* LCD: frame buffer start address register 1 */
typedef struct {
  __REG32 lcdbaseu :16;
  __REG32 lcdbank  :8;
  __REG32          :8;
} __lcdsaddr1_bits;

/* LCD: frame buffer start address register 2 */
typedef struct {
  __REG32 lcdbasel :16;
  __REG32 mval     :8;
  __REG32 bswp     :1;
  __REG32          :7;
} __lcdsaddr2_bits;

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
  __REG32 blueval :32;
} __blue_bits;

/* ADC: control register  */
typedef struct {
  __REG8 aden     :1;
  __REG8 asel     :2;
  __REG8 cksel    :2;
  __REG8 stby     :1;
  __REG8 mode     :1;
  __REG8 flag     :1;
} __adccon_bits;

/* RTC: control register  */
typedef struct {
  __REG8 rtcen     :1;
  __REG8 clksel    :1;
  __REG8 cntsel    :1;
  __REG8 clkrst    :1;
  __REG8           :4;
} __rtccon_bits;

/* RTC: alarm control register  */
typedef struct {
  __REG8 secen     :1;
  __REG8 minen     :1;
  __REG8 houren    :1;
  __REG8 dayen     :1;
  __REG8 monren    :1;
  __REG8 yearen    :1;
  __REG8 almen     :1;
  __REG8           :1;
} __rtcalm_bits;


/* RTC: alarm second data/BCD second register  */
typedef struct {
  __REG8         :4;
  __REG8 secdata :3;
  __REG8         :1;
} __sec_bits;

/* RTC: alarm minute data/BCD minute register  */
typedef struct {
  __REG8         :4;
  __REG8 mindata :3;
  __REG8         :1;
} __min_bits;

/* RTC: alarm hour data/BCD hour register  */
typedef struct {
  __REG8          :4;
  __REG8 hourdata :2;
  __REG8          :2;
} __hour_bits;

/* RTC: alarm day data/BCD day register  */
typedef struct {
  __REG8          :4;
  __REG8 daydata  :2;
  __REG8          :2;
} __day_bits;

/* RTC: alarm month data/BCD month register  */
typedef struct {
  __REG8          :4;
  __REG8 mondata  :1;
  __REG8          :3;
} __mon_bits;


/* RTC: alarm year data/BCD year register  */
typedef struct {
  __REG8 yeardata :8;
} __year_bits;

/* RTC: round reset register  */
typedef struct {
  __REG8 seccr    :3;
  __REG8 srsten   :1;
  __REG8          :4;
} __rtcrst_bits;

/* RTC: BCD date register  */
typedef struct {
  __REG8 datedata  :3;
  __REG8          :5;
} __bcddate_bits;

/* WD: Watch dog timer control register  */
typedef struct {
  __REG32 rsten  :1;
  __REG32        :1;
  __REG32 ien    :1;
  __REG32 clksel :2;
  __REG32 wdten  :1;
  __REG32        :2;
  __REG32 presval:8;
  __REG32        :16;
} __wtcon_bits;

/* WD: Watch dog timer data register  */
typedef struct {
  __REG32 cntrval  :16;
  __REG32          :16;
} __wtdat_bits;

/* WD: Watch dog timer count register  */
typedef struct {
  __REG32 cntval  :16;
  __REG32         :16;
} __wtcnt_bits;


/* IIC: IIC-bus control register  */
typedef struct {
  __REG32 tclkval  :4;
  __REG32 ipndflag :1;
  __REG32 ien      :1;
  __REG32 txcss    :1;
  __REG32 acken    :2;
  __REG32          :23;
} __iiccon_bits;

/* IIC: IIC-bus control/status register  */
typedef struct {
  __REG32 lrsflag  :1;
  __REG32 azsflag  :1;
  __REG32 aassflag :1;
  __REG32 asf      :1;
  __REG32 soen     :1;
  __REG32 busyss   :1;
  __REG32 mode     :2;
  __REG32          :24;
} __iicstat_bits;


/* IIC: IIC-bus address register  */
typedef struct {
  __REG32 addr  :8;
  __REG32       :24;
} __iicadd_bits;

/* IIC: IIC-bus data shift register  */
typedef struct {
  __REG32 shift  :8;
  __REG32        :24;
} __iicds_bits;

/* SIO:  control register  */
typedef struct {
  __REG32 mode      :2;
  __REG32 shiftop   :1;
  __REG32 start     :1;
  __REG32 clkesel   :1;
  __REG32 txrxsel   :1;
  __REG32 ddir      :1;
  __REG32 clksrcsel :1;
  __REG32          :24;
} __siocon_bits;

/* SIO:  data register  */
typedef struct {
  __REG32 data      :8;
  __REG32           :24;
} __siodat_bits;

/* SIO:  baud rate prescaler register  */
typedef struct {
  __REG32 sbrdr    :12;
  __REG32          :20;
} __sbrdr_bits;

/* SIO:  interval counter register  */
typedef struct {
  __REG32 ivcnt    :8;
  __REG32          :24;
} __ivtcnt_bits;

/* SIO: dma count zero register  */
typedef struct {
  __REG32 dcntz0    :1;
  __REG32 dcntz1    :1;
  __REG32           :30;
} __dcntz_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  Memory controller registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__BWSCON,0x01c80000,__READ_WRITE,__bwscon_bits);
__IO_REG32_BIT(__BANKCON0,0x01c80004,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__BANKCON1,0x01c80008,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__BANKCON2,0x01c8000c,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__BANKCON3,0x01c80010,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__BANKCON4,0x01c80014,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__BANKCON5,0x01c80018,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__BANKCON6,0x01c8001c,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__BANKCON7,0x01c80020,__READ_WRITE,__bankcon_bits);
__IO_REG32_BIT(__MRSR,0x01c80024,__READ_WRITE,__mrsr_bits);
__IO_REG32_BIT(__DRAMCON,0x01c80028,__READ_WRITE,__dramcon_bits);

/***************************************************************************
 **
 **  Clock & power management registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PLLCON,0x01d80000,__READ_WRITE,__pllcon_bits);
__IO_REG32_BIT(__CLKCON,0x01d80004,__READ_WRITE,__clkcon_bits);
__IO_REG32_BIT(__CLKSLOW,0x01d80008,__READ_WRITE,__clkslow_bits);

/***************************************************************************
 **
 **  CPUWRAPER registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG,0x01c00000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__NCACHBE0,0x01c00004,__READ_WRITE,__ncachbe0_bits);
__IO_REG32_BIT(__NCACHBE1,0x01c00008,__READ_WRITE,__ncachbe1_bits);

/***************************************************************************
 **
 **  Bus priority register
 **
 ***************************************************************************/
__IO_REG32_BIT(__SBUSCON,0x01c40000,__READ_WRITE,__sbuscon_bits);


/***************************************************************************
 **
 **  DMA registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__ZDCON0,0x01e80000,__READ_WRITE,__zdcon_bits);
__IO_REG32_BIT(__ZDCON1,0x01e80020,__READ_WRITE,__zdcon_bits);
__IO_REG32_BIT(__ZDISRC0,0x01e80004,__READ_WRITE,__zdisrc_bits);
__IO_REG32_BIT(__ZDIDES0,0x01e80008,__READ_WRITE,__zdides_bits);
__IO_REG32_BIT(__ZDICNT0,0x01e8000c,__READ_WRITE,__zdicnt_bits);
__IO_REG32_BIT(__ZDCSRC0,0x01e80010,__READ,__zdcsrc_bits);
__IO_REG32_BIT(__ZDCDES0,0x01e80014,__READ,__zdcdes_bits);
__IO_REG32_BIT(__ZDCCNT0,0x01e80018,__READ,__zdccnt_bits);
__IO_REG32_BIT(__ZDISRC1,0x01e80024,__READ_WRITE,__zdisrc_bits);
__IO_REG32_BIT(__ZDIDES1,0x01e80028,__READ_WRITE,__zdides_bits);
__IO_REG32_BIT(__ZDICNT1,0x01e8002c,__READ_WRITE,__zdicnt_bits);
__IO_REG32_BIT(__ZDCSRC1,0x01e80030,__READ,__zdcsrc_bits);
__IO_REG32_BIT(__ZDCDES1,0x01e80034,__READ,__zdcdes_bits);
__IO_REG32_BIT(__ZDCCNT1,0x01e80038,__READ,__zdccnt_bits);
__IO_REG32_BIT(__BDCON0,0x01f80000,__READ_WRITE,__bdcon_bits);
__IO_REG32_BIT(__BDCON1,0x01f80020,__READ_WRITE,__bdcon_bits);
__IO_REG32_BIT(__BDISRC0,0x01f80004,__READ_WRITE,__bdisrc_bits);
__IO_REG32_BIT(__BDIDES0,0x01f80008,__READ_WRITE,__bdides_bits);
__IO_REG32_BIT(__BDICNT0,0x01f8000c,__READ_WRITE,__bdicnt_bits);
__IO_REG32_BIT(__BDCSRC0,0x01f80010,__READ,__bdcsrc_bits);
__IO_REG32_BIT(__BDCDES0,0x01f80014,__READ,__bdcdes_bits);
__IO_REG32_BIT(__BDCCNT0,0x01f80018,__READ,__bdccnt_bits);

__IO_REG32_BIT(__BDISRC1,0x01f80024,__READ_WRITE,__bdisrc_bits);
__IO_REG32_BIT(__BDIDES1,0x01f80028,__READ_WRITE,__bdides_bits);
__IO_REG32_BIT(__BDICNT1,0x01f8002c,__READ_WRITE,__bdicnt_bits);
__IO_REG32_BIT(__BDCSRC1,0x01f80030,__READ,__bdcsrc_bits);
__IO_REG32_BIT(__BDCDES1,0x01f80034,__READ,__bdcdes_bits);
__IO_REG32_BIT(__BDCCNT1,0x01f80038,__READ,__bdccnt_bits);


/***************************************************************************
 **
 **  I/O ports registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PCONA,0x01d20000,__READ_WRITE,__pcona_bits);
__IO_REG32_BIT(__PDATA,0x01d20004,__READ_WRITE,__pdata_bits);
__IO_REG32_BIT(__PUPA,0x01d2003c,__READ_WRITE,__pupa_bits);
__IO_REG32_BIT(__PCONB,0x01d20008,__READ_WRITE,__pconb_bits);
__IO_REG32_BIT(__PDATB,0x01d2000c,__READ_WRITE,__pdatb_bits);
__IO_REG32_BIT(__PCONC,0x01d20010,__READ_WRITE,__pconc_bits);
__IO_REG32_BIT(__PDATC,0x01d20014,__READ_WRITE,__pdatc_bits);
__IO_REG32_BIT(__PUPC,0x01d20040,__READ_WRITE,__pupc_bits);
__IO_REG32_BIT(__PCOND,0x01d20018,__READ_WRITE,__pcond_bits);
__IO_REG32_BIT(__PDATD,0x01d2001c,__READ_WRITE,__pdatd_bits);
__IO_REG32_BIT(__PUPD,0x01d20044,__READ_WRITE,__pupd_bits);
__IO_REG32_BIT(__PCONE,0x01d20020,__READ_WRITE,__pcone_bits);
__IO_REG32_BIT(__PDATE,0x01d20024,__READ_WRITE,__pdate_bits);
__IO_REG32_BIT(__PCONF,0x01d20028,__READ_WRITE,__pconf_bits);
__IO_REG32_BIT(__PDATF,0x01d2002c,__READ_WRITE,__pdatf_bits);
__IO_REG32_BIT(__PUPF,0x01d20048,__READ_WRITE,__pupf_bits);
__IO_REG32_BIT(__PCONG,0x01d20030,__READ_WRITE,__pcong_bits);
__IO_REG32_BIT(__PDATG,0x01d20034,__READ_WRITE,__pdatg_bits);
__IO_REG32_BIT(__PUPG,0x01d2004c,__READ_WRITE,__pupg_bits);
__IO_REG32_BIT(__EXTINT,0x01d20038,__READ_WRITE,__extint_bits);
__IO_REG32_BIT(__PUPS,0x01d20050,__READ_WRITE,__pups_bits);


/***************************************************************************
 **
 **  PWM timer registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__TCFG,0x01d50000,__READ_WRITE,__tcfg_bits);
__IO_REG32_BIT(__TCON,0x01d50004,__READ_WRITE,__tcon_bits);
__IO_REG32(__TCNTB0,0x01d50008,__READ_WRITE);
__IO_REG32(__TCMPB0,0x01d5000c,__READ_WRITE);
__IO_REG32(__TCNTO0,0x01d50010,__READ);
__IO_REG32(__TCNTB1,0x01d50014,__READ_WRITE);
__IO_REG32(__TCMPB1,0x01d50018,__READ_WRITE);
__IO_REG32(__TCNTO1,0x01d5001c,__READ);
__IO_REG32(__TCNTB2,0x01d50020,__READ_WRITE);
__IO_REG32(__TCMPB2,0x01d50024,__READ_WRITE);
__IO_REG32(__TCNTO2,0x01d50028,__READ_WRITE);
__IO_REG32(__TCNTB3,0x01d5002c,__READ_WRITE);
__IO_REG32(__TCNTO3,0x01d50030,__READ_WRITE);

/***************************************************************************
 **
 **  UART registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__ULCON0,0x01d00000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__ULCON1,0x01d04000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__UCON0,0x01d00004,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__UCON1,0x01d04004,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__USTAT0,0x01d00008,__READ,__ustat_bits);
__IO_REG32_BIT(__USTAT1,0x01d04008,__READ,__ustat_bits);
__IO_REG32_BIT(__UFCON0,0x01d0000c,__READ_WRITE,__ufcon_bits);
__IO_REG32_BIT(__UFSTAT0,0x01d00010,__READ,__ufstat_bits);

__IO_REG32(__UTXH0,0x01d00014,__READ_WRITE);
/*__IO_REG8(__UTXH0,0x01d00014,__READ_WRITE) byte access, little endian*/
/*__IO_REG8(__UTXH0,0x01d00017,__READ_WRITE); big endian*/
__IO_REG32(__UTXH1,0x01d04014,__READ_WRITE);
/*__IO_REG8(__UTXH1,0x01d04017,__READ_WRITE); big endian*/
__IO_REG32(__URXH0,0x01d00018,__READ_WRITE);
/*__IO_REG8(__URXH0,0x01d00018,__READ_WRITE); byte acces, little endian*/
/*__IO_REG8(__URXH0,0x01d0001b,__READ_WRITE); big endian */
__IO_REG32(__URXH1,0x01d04018,__READ_WRITE);
/*__IO_REG8(__URXH1,0x01d0401b,__READ_WRITE); big endian*/

__IO_REG32(__UBRDIV0,0x01d0001c,__READ_WRITE);
__IO_REG32(__UBRDIV1,0x01d0401c,__READ_WRITE);

/***************************************************************************
 **
 **  Interrupt controller Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTCON,0x01e00000,__READ_WRITE,__intcon_bits);
__IO_REG32_BIT(__INTPND,0x01e00004,__READ_WRITE,__intpndmodispc_bits);
__IO_REG32_BIT(__INTMOD,0x01e00008,__READ_WRITE,__intpndmodispc_bits);
__IO_REG32_BIT(__INTMSK,0x01e0000c,__READ_WRITE,__intmsk_bits);

__IO_REG32_BIT(__I_PSLV,0x01e00010,__READ_WRITE,__slv_bits);
__IO_REG32_BIT(__I_PMST,0x01e00014,__READ_WRITE,__pmst_bits);
__IO_REG32_BIT(__I_CSLV,0x01e00018,__READ,__slv_bits);
__IO_REG32_BIT(__I_CMST,0x01e0001c,__READ,__cmst_bits);
__IO_REG32_BIT(__I_ISPR,0x01e00020,__READ,__intpndmodispc_bits);
__IO_REG32_BIT(__I_ISPC,0x01e00024,__WRITE,__intpndmodispc_bits);
__IO_REG32_BIT(__F_PSLV,0x01e00028,__READ_WRITE,__slv_bits);
__IO_REG32_BIT(__F_PMST,0x01e0002c,__READ_WRITE,__pmst_bits);
__IO_REG32_BIT(__F_CSLV,0x01e00030,__READ,__slv_bits);
__IO_REG32_BIT(__F_CMST,0x01e00034,__READ,__cmst_bits);
__IO_REG32_BIT(__F_ISPR,0x01e00038,__READ,__intpndmodispc_bits);
__IO_REG32_BIT(__F_ISPC,0x01e0003c,__WRITE,__intpndmodispc_bits);


/***************************************************************************
 **
 **  LCD controller Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__LCDCON1,0x01f00000,__READ_WRITE,__lcdcon1_bits);
__IO_REG32_BIT(__LCDCON2,0x01f00004,__READ_WRITE,__lcdcon2_bits);
__IO_REG32_BIT(__LCDCON3,0x01f00048,__READ_WRITE,__lcdcon3_bits);
__IO_REG32_BIT(__LCDSADDR1,0x01f00008,__READ_WRITE,__lcdsaddr1_bits);
__IO_REG32_BIT(__LCDSADDR2,0x01f0000c,__READ_WRITE,__lcdsaddr2_bits);
__IO_REG32_BIT(__REDLUT,0x01f00010,__READ_WRITE,__red_bits);
__IO_REG32_BIT(__GREENLUT,0x01f00014,__READ_WRITE,__green_bits);
__IO_REG32_BIT(__BLUELUT,0x01f00018,__READ_WRITE,__blue_bits);
__IO_REG32(__DP1_2,0x01f0001c,__READ_WRITE);
__IO_REG32(__DP4_7H,0x01f00020,__READ_WRITE);
__IO_REG32(__DP4_7L,0x01f00024,__READ_WRITE);
__IO_REG32(__DP3_5,0x01f00028,__READ_WRITE);
__IO_REG32(__DP2_3,0x01f0002c,__READ_WRITE);
__IO_REG32(__DP3_4,0x01f00030,__READ_WRITE);
__IO_REG32(__DP5_7H,0x01f00034,__READ_WRITE);
__IO_REG32(__DP5_7L,0x01f00038,__READ_WRITE);
__IO_REG32(__DP4_5,0x01f0003c,__READ_WRITE);
__IO_REG32(__DP6_7H,0x01f00040,__READ_WRITE);
__IO_REG32(__DP6_7L,0x01f00044,__READ_WRITE);
__IO_REG32(__DITHMODE,0x01f0004c,__READ_WRITE);


/***************************************************************************
 **
 **  A/D converter Registers
 ** (default little endian)
 ***************************************************************************/
__IO_REG8_BIT(__ADCCON,0x01d40000,__READ_WRITE,__adccon_bits);
/*__IO_REG8_BIT(__ADCCON,0x01d40003,__READ_WRITE,__adccon_bits); big endian*/
__IO_REG16(__ADCDAT,0x01d40004,__READ);
/*__IO_REG16(__ADCDAT,0x01d40006,__READ); big endian */


/***************************************************************************
 **
 **  RTC Registers
 ** (default little endian)
 ***************************************************************************/
__IO_REG8_BIT(__RTCCON,0x01d70040,__READ_WRITE,__rtccon_bits);
/*__IO_REG8_BIT(__RTCCON,0x01d70043,__READ_WRITE,__rtccon_bits); big endian*/
__IO_REG8_BIT(__RTCALM,0x01d70050,__READ_WRITE,__rtcalm_bits);
/*__IO_REG8_BIT(__RTCALM,0x01d70053,__READ_WRITE,__rtcalm_bits); big endian*/
__IO_REG8_BIT(__ALMSEC,0x01d70054,__READ_WRITE,__sec_bits);
/*__IO_REG8_BIT(__ALMSEC,0x01d70057,__READ_WRITE,__sec_bits); big endian*/
__IO_REG8_BIT(__ALMMIN,0x01d70058,__READ_WRITE,__min_bits);
/*__IO_REG8_BIT(__ALMMIN,0x01d7005b,__READ_WRITE,__min_bits); big endian*/
__IO_REG8_BIT(__ALMHOUR,0x01d7005c,__READ_WRITE,__hour_bits);
/*__IO_REG8_BIT(__ALMHOUR,0x01d7005f,__READ_WRITE,__hour_bits); big endian*/
__IO_REG8_BIT(__ALMDAY,0x01d70060,__READ_WRITE,__day_bits);
/*__IO_REG8_BIT(__ALMDAY,0x01d70063,__READ_WRITE,__day_bits); big endian*/
__IO_REG8_BIT(__ALMMON,0x01d70064,__READ_WRITE,__mon_bits);
/*__IO_REG8_BIT(__ALMMON,0x01d70067,__READ_WRITE,__mon_bits); big endian*/
__IO_REG8_BIT(__ALMYEAR,0x01d70068,__READ_WRITE,__year_bits);
/*__IO_REG8_BIT(__ALMYEAR,0x01d7006b,__READ_WRITE,__year_bits); big endian*/
__IO_REG8_BIT(__RTCRST,0x01d7006c,__READ_WRITE,__rtcrst_bits);
/*__IO_REG8_BIT(__RTCRST,0x01d7006f,__READ_WRITE,__rtcrst_bits); big endian*/
__IO_REG8_BIT(__BCDSEC,0x01d70070,__READ_WRITE,__sec_bits);
/*__IO_REG8_BIT(__BCDSEC,0x01d70073,__READ_WRITE,__sec_bits); big endian*/
__IO_REG8_BIT(__BCDMIN,0x01d70074,__READ_WRITE,__min_bits);
/*__IO_REG8_BIT(__BCDMIN,0x01d70077,__READ_WRITE,__min_bits); big endian*/
__IO_REG8_BIT(__BCDHOUR,0x01d70078,__READ_WRITE,__hour_bits);
/*__IO_REG8_BIT(__BCDHOUR,0x01d7007b,__READ_WRITE,__hour_bits); big endian*/
__IO_REG8_BIT(__BCDDAY,0x01d7007c,__READ_WRITE,__day_bits);
/*__IO_REG8_BIT(__BCDDAY,0x01d7007f,__READ_WRITE,__day_bits); big endian*/
__IO_REG8_BIT(__BCDDATE,0x01d70080,__READ_WRITE,__bcddate_bits);
/*__IO_REG8_BIT(__BCDDATE,0x01d70083,__READ_WRITE,__bcddate_bits); big endian*/
__IO_REG8_BIT(__BCDMON,0x01d70084,__READ_WRITE,__mon_bits);
/*__IO_REG8_BIT(__BCDMON,0x01d70087,__READ_WRITE,__mon_bits);  big endian*/
__IO_REG8_BIT(__BCDYEAR,0x01d70088,__READ_WRITE,__year_bits);
/*__IO_REG8_BIT(__BCDYEAR,0x01d7008b,__READ_WRITE,__year_bits); big endian*/

/***************************************************************************
 **
 **  Watch dog Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__WTCON,0x01d30000,__READ_WRITE,__wtcon_bits);
__IO_REG32_BIT(__WTDAT,0x01d30004,__READ_WRITE,__wtdat_bits);
__IO_REG32_BIT(__WTCNT,0x01d30008,__READ_WRITE,__wtcnt_bits);


/***************************************************************************
 **
 **  IIC bus Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__IICCON,0x01d60000,__READ_WRITE,__iiccon_bits);
__IO_REG32_BIT(__IICSTAT,0x01d60004,__READ_WRITE,__iicstat_bits);
__IO_REG32_BIT(__IICADD,0x01d60008,__READ_WRITE,__iicadd_bits);
__IO_REG32_BIT(__IICDS,0x01d6000c,__READ_WRITE,__iicds_bits);

/***************************************************************************
 **
 **  SIO Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SIOCON,0x01d08000,__READ_WRITE,__siocon_bits);
__IO_REG32_BIT(__SIODAT,0x01d08004,__READ_WRITE,__siodat_bits);
__IO_REG32_BIT(__SBRDR,0x01d08008,__READ_WRITE,__sbrdr_bits);
__IO_REG32_BIT(__IVTCNT,0x01d0800c,__READ_WRITE,__ivtcnt_bits);
__IO_REG32_BIT(__DCNTZ,0x01d08010,__READ_WRITE,__dcntz_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3C44A0A interrupt sources
 **
 ***************************************************************************/
#define EINT0        0x00000020  /* external interrupt 0             */
#define EINT1        0x00000024  /* external interrupt 1             */
#define EINT2        0x00000028  /* external interrupt 2             */
#define EINT3        0x0000002c  /* external interrupt 3             */
#define EINT4        0x00000030  /* external interrupt 4             */
#define EINT5        0x00000034  /* external interrupt 5             */
#define INT_ZDMA0    0x00000040  /* general DMA0 interrupt           */
#define INT_ZDMA1    0x00000044  /* general DMA1 interrupt           */
#define INT_BDMA0    0x00000048  /* uart0 bridge interrupt           */
#define INT_BDMA1    0x0000004c  /* uart1 bridge interrupt           */
#define INT_UERR0    0x00000050  /* uart0 error interrupt            */
#define INT_UERR1    0x00000054  /* uart1 error interrupt            */
#define INT_TIMER0   0x00000060  /* timer0 interrupt         */
#define INT_TIMER1   0x00000064  /* timer1 interrupt         */
#define INT_TIMER2   0x00000068  /* timer2 interrupt         */
#define INT_TIMER3   0x0000006c  /* timer3 interrupt         */
#define INT_WDT      0x00000070  /* watchdog timer interrupt */
#define EINT6_EINT7  0x00000074  /* external interrupt 6/7   */
#define INT_URXD0    0x00000080  /* uart0 receive interrupt  */
#define INT_URXD1    0x00000084  /* uart1 receive interrupt  */
#define INT_IIC      0x00000088  /* IIC interrupt            */
#define INT_SI0      0x0000008c  /* SIO interrupt            */
#define INT_UTXD0    0x00000090  /* uart0 transmit interrupt */
#define INT_UTXD1    0x00000094  /* uart1 transmit interrupt */
#define INT_RTC      0x000000a0  /* RTC interrupt            */
#define INT_ADC      0x000000c0  /* ADC EOC interrupt        */

#endif    /* __S3C44A0A_H */
