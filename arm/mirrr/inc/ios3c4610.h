/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C4610
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2000
 **
 **    $Revision: 1.5 $
 **
 ***************************************************************************/

#ifndef __S3C4610_H
#define __S3C4610_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C4610 SPECIAL FUNCTION REGISTERS
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
  __REG32 se   :1; /* stall enable            */
  __REG32 ce   :1; /* cache enable            */
  __REG32 we   :1; /* write buffer enable     */
  __REG32      :1;
  __REG32 baddr:12; /* baseaddress setting for special registers */
  __REG32      :16;
} __syscfg_bits;

/* SM: ROM timing control register  */
typedef struct {
  __REG32 pgs0  :2; /* page burst mode selection */
  __REG32 tacp0 :2; /* page mode access cycles   */
  __REG32 tacc0 :3; /* ROM bank access cycles    */
  __REG32       :1;
  __REG32 pgs1  :2;
  __REG32 tacp1 :2;
  __REG32 tacc1 :3;
  __REG32       :1;
  __REG32 pgs2  :2;
  __REG32 tacp2 :2;
  __REG32 tacc2 :3;
  __REG32       :1;
  __REG32 pgs3  :2;
  __REG32 tacp3 :2;
  __REG32 tacc3 :3;
  __REG32       :1;
} __romtime_bits;

/* SM: SRAM timing control register  */
typedef struct {
  __REG32      :4;
  __REG32 tacc :3;  /* SRAM bank access cycles */
  __REG32      :25;
} __sramtime_bits;

/* SM: DRAM timing control register 0 */
typedef struct {
  __REG32 can0  :2;
  __REG32 edo0  :1;
  __REG32 tpgm0 :2;
  __REG32 tcp0  :1;
  __REG32 tcs0  :3;
  __REG32 trc0  :1;
  __REG32 trp0  :2;
  __REG32       :4;
  __REG32 can1  :2;
  __REG32 edo1  :1;
  __REG32 tpgm1 :2;
  __REG32 tcp1  :1;
  __REG32 tcs1  :3;
  __REG32 trc1  :1;
  __REG32 trp1  :2;
  __REG32       :4;
} __dramtime0_bits;

/* SM: DRAM timing control register 1 */
typedef struct {
  __REG32 can2  :2;
  __REG32 edo2  :1;
  __REG32 tpgm2 :2;
  __REG32 tcp2  :1;
  __REG32 tcs2  :3;
  __REG32 trc2  :1;
  __REG32 trp2  :2;
  __REG32       :4;
  __REG32 can3  :2;
  __REG32 edo3  :1;
  __REG32 tpgm3 :2;
  __REG32 tcp3  :1;
  __REG32 tcs3  :3;
  __REG32 trc3  :1;
  __REG32 trp3  :2;
  __REG32       :4;
} __dramtime1_bits;

/* SM: DRAM timing control register 0 */
typedef struct {
  __REG32 can4  :2;
  __REG32 edo4  :1;
  __REG32 tpgm4 :2;
  __REG32 tcp4  :1;
  __REG32 tcs4  :3;
  __REG32 trc4  :1;
  __REG32 trp4  :2;
  __REG32       :4;
  __REG32 can5  :2;
  __REG32 edo5  :1;
  __REG32 tpgm5 :2;
  __REG32 tcp5  :1;
  __REG32 tcs5  :3;
  __REG32 trc5  :1;
  __REG32 trp5  :2;
  __REG32       :4;
} __dramtime2_bits;

/* SM: External I/O timing control register 0 */
typedef struct {
  __REG32 tcos0 :3; /* chip selection set-up time on nOE   */
  __REG32 tacs0 :3; /* Address set-up time before nECS     */
  __REG32 tcoh0 :3; /*  OE to ECS hold time                */
  __REG32 tacc0 :3; /* Access cycles                       */
  __REG32       :4;
  __REG32 tcos1 :3;
  __REG32 tacs1 :3;
  __REG32 tcoh1 :3;
  __REG32 tacc1 :3;
  __REG32       :4;
} __exttime0_bits;

/* SM: External I/O timing control register 1 */
typedef struct {
  __REG32 tcos2 :3; /* chip selection set-up time on nOE   */
  __REG32 tacs2 :3; /* Address set-up time before nECS     */
  __REG32 tcoh2 :3; /* OE to ECS hold time                 */
  __REG32 tacc2 :3; /* Access cycles                       */
  __REG32       :4;
  __REG32 tcos3 :3;
  __REG32 tacs3 :3;
  __REG32 tcoh3 :3;
  __REG32 tacc3 :3;
  __REG32       :4;
} __exttime1_bits;

/* SM:  data bus width control register */
typedef struct {
  __REG32 pw0  :2;
  __REG32 pw1  :2;
  __REG32 pw2  :2;
  __REG32 pw3  :2;
  __REG32 pw4  :2;
  __REG32 pw5  :2;
  __REG32 pw6  :2;
  __REG32 pw7  :2;
  __REG32 pw8  :2;
  __REG32 pw9  :2;
  __REG32 pw10  :2;
  __REG32 pwx0  :2;
  __REG32 pwx1  :2;
  __REG32 pwx2  :2;
  __REG32 pwx3  :2;
  __REG32       :2;
} __dbuswth_bits;

/* SM: DRAM bank address pointer register */
typedef struct {
  __REG32 bp   :12;
  __REG32      :4;
  __REG32 np   :12;
  __REG32      :4;
} __bankptr_bits;


/* SM:  DRAM refresh and external I/O control register */
typedef struct {
  __REG32 bp     :12;
  __REG32 fv     :1;
  __REG32        :3;
  __REG32 refcnt :11;
  __REG32 en     :1;
  __REG32 tcs    :3;
  __REG32        :1;
} __refextcon_bits;

/* CACHE: non-cacheable area base pointer register */
typedef struct {
  __REG32        :9;
  __REG32 addr   :19;
  __REG32        :4;
} __cachnab_bits;

/* CACHE: non-cacheable area next pointer register */
typedef struct {
  __REG32         :9;
  __REG32 addr    :19;
  __REG32         :4;
} __cachnae_bits;

/* CDMA control register */
typedef struct {
  __REG32 re     :1;
  __REG32 bs     :1;
  __REG32 mode   :2;
  __REG32 da     :1;
  __REG32 sa     :1;
  __REG32 df     :1;
  __REG32 sf     :1;
  __REG32 si     :1;
  __REG32        :1;
  __REG32 td     :1;
  __REG32 sm     :1;
  __REG32 tw     :2;
  __REG32 cn     :1;
  __REG32 bm     :1;
  __REG32        :3;
  __REG32 cdm    :2;
  __REG32 cf     :1;
  __REG32 buf_cnt:5;
  __REG32 idle   :1;
  __REG32        :4;
} __cdmacon_bits;

/* CDMA source/dest address register */
typedef struct {
  __REG32 addr   :28;
  __REG32        :4;
} __cdmasrcdst_bits;

/* CDMA transfer count register */
typedef struct {
  __REG32 cnt    :24;
  __REG32        :8;
} __cdmacnt_bits;

/* GDMA control register */
typedef struct {
  __REG32 re    :1;
  __REG32 bs    :1;
  __REG32 mode  :2;
  __REG32 da    :1;
  __REG32 sa    :1;
  __REG32 df    :1;
  __REG32 sf    :1;
  __REG32 si    :1;
  __REG32       :1;
  __REG32 td    :1;
  __REG32 sb    :1;
  __REG32 tw    :2;
  __REG32 cn    :1;
  __REG32 dm    :1;
  __REG32       :16;
} __gdmacon_bits;

/* GDMA source /destination address register */
typedef struct {
  __REG32 addr  :28;
  __REG32       :4;
} __gdmasrcdst_bits;

/* GDMA transfer count register */
typedef struct {
  __REG32 tc    :24;
  __REG32       :8;
} __gdmacnt_bits;

/* UART/SIO: line control register */
typedef struct {
  __REG32 wl    :2;
  __REG32 stb   :1;
  __REG32 pmd   :3;
  __REG32 sc    :1;
  __REG32 ir    :1;
  __REG32       :24;
} __ulcon_bits;

/* UART/SIO: control register 0*/
typedef struct {
  __REG32 rxm   :2;
  __REG32 rs    :1;
  __REG32 txm   :2;
  __REG32 dsr   :1;
  __REG32 sb    :1;
  __REG32 lp    :1;
  __REG32       :24;
} __ucon0_bits;

/* UART/SIO: control register 1 */
typedef struct {
  __REG32 rxm   :2;
  __REG32 rs    :1;
  __REG32 txm   :2;
  __REG32       :1;
  __REG32 sb    :1;
  __REG32 lp    :1;
  __REG32       :24;
} __ucon1_bits;


/* UART/SIO: status register 0*/
typedef struct {
  __REG32 ov   :1;
  __REG32 pt   :1;
  __REG32 fr   :1;
  __REG32 bk   :1;
  __REG32 dtr  :1;
  __REG32 rd   :1;
  __REG32 th   :1;
  __REG32 te   :1;
  __REG32      :24;
} __ustat0_bits;

/* UART/SIO: status register 1*/
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
} __ustat1_bits;


/* UART/SIO transmit holding register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __utxbuf_bits;

/* UART/SIO receive holding buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __urxbuf_bits;

/* UART/SIO: baud rate divisor register */
typedef struct {
  __REG32 brdiv :16;
  __REG32       :16;
} __ubrdiv_bits;

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
  __REG32 nselectin:1;
  __REG32 nstrobe  :1;
  __REG32 nautofd  :1;
  __REG32 ninitial :1;
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
  __REG32 oen      :1;
  __REG32 ab       :1;
  __REG32 dmasel   :1;
  __REG32 dmar     :1;
  __REG32 fd       :1;
  __REG32          :1;
  __REG32 zi       :1;
  __REG32 ds       :1;
  __REG32 dls      :1;
  __REG32 de       :1;
  __REG32          :16;
} __ppcon_bits;

/* PP: parallell interrupt enable/pending register */
typedef struct {
  __REG32 nselectinlh :1;
  __REG32 nselectinhl :1;
  __REG32 nstrobelh   :1;
  __REG32 nstrobehl   :1;
  __REG32 nautofdlh   :1;
  __REG32 nautofdhl   :1;
  __REG32 ninitiallh  :1;
  __REG32 ninitialhl  :1;
  __REG32 dr          :1;
  __REG32 cbr         :1;
  __REG32 inselectin  :1;
  __REG32 tde         :1;
  __REG32             :20;
} __ppi_bits;


/* PTimer: mode register 1*/
typedef struct {
  __REG32 rsoen  :1;
  __REG32        :1;
  __REG32 ien    :1;
  __REG32 cdfsel :2;
  __REG32 ten    :1;
  __REG32        :2;
  __REG32 pv     :8;
  __REG32        :16;
} __tmod1_bits;


/* PTimer: mode register 0 and 2-4 */
typedef struct {
  __REG32 ten    :1;
  __REG32 css    :1;
  __REG32 tces   :1;
  __REG32 oms    :2; /* timer 0 only*/
  __REG32 pv     :7;
  __REG32        :20;
} __tmod_bits;


/* PTimer: data register */
typedef struct {
  __REG32 data    :16;
  __REG32         :16;
} __tdata_bits;


/* PTimer: count register */
typedef struct {
  __REG32 cv     :16;
  __REG32        :16;
} __tcnt_bits;

/* PIFC: transmit buffer register */
typedef struct {
  __REG32 cm     :8;
  __REG32        :24;
} __pitxbuf_bits;

/* PIFC: receive buffer register */
typedef struct {
  __REG32 em     :8;
  __REG32        :24;
} __pirxbuf_bits;

/* PIFC: command mode register */
typedef struct {
  __REG32 tx     :1;
  __REG32 rx     :1;
  __REG32 pv     :5;
  __REG32        :25;
} __picmod_bits;

/* PIFC: PDMA and engine interface status register */
typedef struct {
  __REG32 nengpwr   :1;
  __REG32 nengready :1;
  __REG32 nengprq   :1;
  __REG32 pifcs     :2;
  __REG32 pdmaq     :1;
  __REG32           :26;
} __pistat_bits;

/* PIFC: video control register */
typedef struct {
  __REG32 ncpupwr   :1;
  __REG32 ncpuprint :1;
  __REG32 ncpupsync :1;
  __REG32 nvclk     :1;
  __REG32 sdir      :1;
  __REG32 sp        :1;
  __REG32           :26;
} __pivcon_bits;

/* PIFC: pattern control register */
typedef struct {
  __REG32 vdp       :1;
  __REG32 bdp       :1;
  __REG32 cks       :2;
  __REG32 ckd       :3;
  __REG32 srk       :3;
  __REG32 chop      :8;
  __REG32 ier       :2;
  __REG32           :12;
} __pipcon_bits;

/* PIFC: PDMA control register */
typedef struct {
  __REG32 bmq0      :1;
  __REG32 bmq1      :1;
  __REG32 q0en      :1;
  __REG32 q1en      :1;
  __REG32 qpdma     :1;
  __REG32 dpdma     :1;
  __REG32           :26;
} __pdmacon_bits;

/* PIFC: top margin register */
typedef struct {
  __REG32 cnt       :16;
  __REG32           :16;
} __pitopmg_bits;

/* PIFC: left margin register */
typedef struct {
  __REG32 cnt       :16;
  __REG32           :16;
} __pilftmg_bits;

/* PIFC: pixel count register */
typedef struct {
  __REG32 cnt       :16;
  __REG32           :16;
} __pipxlcnt_bits;

/* PIFC: PDMA queue start address register */
typedef struct {
  __REG32 addr      :28;
  __REG32           :4;
} __pdmasrc_bits;

/* PIFC: PDMA queue transfer count register */
typedef struct {
  __REG32 cnt       :24;
  __REG32           :8;
} __pdmacnt_bits;

/* GEU: pattern page width register */
typedef struct {
  __REG32 w         :21;
  __REG32           :11;
} __gpatpgwth_bits;

/* GEU: pattern start address register */
typedef struct {
  __REG32 addr      :31;
  __REG32           :1;
} __gpatsa_bits;

/* GEU: pattern width register */
typedef struct {
  __REG32 w         :21;
  __REG32           :11;
} __gpatwth_bits;

/* GEU: pattern height register */
typedef struct {
  __REG32 h         :16;
  __REG32           :16;
} __gpatht_bits;


/* GEU: immediate pattern start address register */
typedef struct {
  __REG32 addr      :31;
  __REG32           :1;
} __gpatisa_bits;

/* GEU: pattern X remainder register */
typedef struct {
  __REG32 rem       :21;
  __REG32           :11;
} __gpatxr_bits;

/* GEU: pattern Y remainder register */
typedef struct {
  __REG32 rem       :16;
  __REG32           :16;
} __gpatyr_bits;

/* GEU: source start address register */
typedef struct {
  __REG32 addr      :31;
  __REG32           :1;
} __gsrcsa_bits;

/* GEU: source page width register */
typedef struct {
  __REG32 w         :21;
  __REG32           :11;
} __gsrcpgwth_bits;

/* GEU:  destination start address register */
typedef struct {
  __REG32 addr      :31;
  __REG32           :1;
} __gdstsa_bits;

/* GEU: destination width/page width register */
typedef struct {
  __REG32 w         :21;
  __REG32           :11;
} __gdstwth_bits;

/* GEU: destination hight register */
typedef struct {
  __REG32 h         :16;
  __REG32           :16;
} __gdstht_bits;

/* GEU: control register */
typedef struct {
  __REG32 fc        :8;
  __REG32 bfien     :1;
  __REG32 dien      :1;
  __REG32 ydst      :1;
  __REG32 ysrc      :1;
  __REG32 xsrc      :1;
  __REG32 yp        :1;
  __REG32 srcf      :1;
  __REG32 fd        :1;
  __REG32 bs        :1;
  __REG32 bf        :1;
  __REG32 slts      :1;
  __REG32           :13;
} __gcon_bits;

/* GEU: band register */
typedef struct {
  __REG32 addr    :31;
  __REG32         :1;
} __gbandptr_bits;

/* GEU: scanline table start address register */
typedef struct {
  __REG32 addr      :26;
  __REG32           :6;
} __gsltsa_bits;

/* GEU: pattern companion table start address register */
typedef struct {
  __REG32 addr      :26;
  __REG32           :6;
} __gpctsa_bits;

/* IFB: expander/rotator control register */
typedef struct {
  __REG32 efsel     :1;
  __REG32 drsel     :1;
  __REG32           :30;
} __exprotcon_bits;

/* IFB: expander data register */
typedef struct {
  __REG32 data     :32;
} __expdata_bits;

/* IFB: rotator data register */
typedef struct {
  __REG32 data     :16;
  __REG32          :16;
} __rotdata_bits;

/* IFB: VIS/halftone bit packer status register */
typedef struct {
  __REG32 rr     :1;
  __REG32 wr     :1;
  __REG32 busy   :1;
  __REG32        :29;
} __vishtstat_bits;

/* IFB: VIS/halftone bit packer control register */
typedef struct {
  __REG32 hten   :1;
  __REG32 dmsel  :1;
  __REG32        :30;
} __vishtcon_bits;


/* IFB: VIS destination/source image data size register */
typedef struct {
  __REG32 ds  :16;
  __REG32     :16;
} __visdsize_bits;


/* IFB: VIS source image data register */
typedef struct {
  __REG32 sid  :8;
  __REG32      :24;
} __vissdata_bits;

/* IFB: VIS destination image data register */
typedef struct {
  __REG32 did  :16;
  __REG32      :16;
} __visddata_bits;

/* IFB: halftone bit packer reference data register */
typedef struct {
  __REG32 rdn_1 :8; /* reference data n+1 */
  __REG32 rdn   :8;
  __REG32       :16;
} __htrdata_bits;

/* IFB: halftone bit packer source image pixel data register */
typedef struct {
  __REG32 spd_1 :8; /* source pixel data n+1 */
  __REG32 spdn  :8;
  __REG32       :16;
} __htsdata_bits;

/* IFB: halftone image pixel data register */
typedef struct {
  __REG32 htid :16;
  __REG32      :16;
} __htdata_bits;



/* I/O: port mode register */
typedef struct {
  __REG32 p0    :2;
  __REG32 p1    :2;
  __REG32 p2    :2;
  __REG32 p3    :2;
  __REG32 p4    :2;
  __REG32 p5    :2;
  __REG32 p6    :2;
  __REG32 p7    :2;
  __REG32 p8    :2;
  __REG32 p9    :2;
  __REG32 p10   :2;
  __REG32 p11   :2;
  __REG32 p12   :2;
  __REG32 p13   :2;
  __REG32 p14   :2;
  __REG32 p15   :2;
} __iopmod_bits;


/* I/O: external interrupt mode register */
typedef struct {
  __REG32 im0      :2;
  __REG32 exti0al  :1;
  __REG32 exti0en  :1;
  __REG32 im1      :2;
  __REG32 exti1al  :1;
  __REG32 exti1en  :1;
  __REG32          :24;
} __extintmod_bits;

/* I/O: port data register */
typedef struct {
  __REG32 iorw  :16;
  __REG32       :16;
} __iopdata_bits;

/*IC: interrupt mask/pending/mode register */
typedef struct {
  __REG32 int_ext0   :1;
  __REG32 int_ext1   :1;
  __REG32 int_timer0 :1;
  __REG32 int_timer1 :1;
  __REG32 int_timer2 :1;
  __REG32 int_timer3 :1;
  __REG32 int_timer4 :1;
  __REG32 int_txd0   :1;
  __REG32 int_rxd0   :1;
  __REG32 int_usr0   :1;
  __REG32 int_txd1   :1;
  __REG32 int_rxd1   :1;
  __REG32 int_usr1   :1;
  __REG32 int_ppic   :1;
  __REG32 int_dma0   :1;
  __REG32 int_dma1   :1;
  __REG32 int_dma2   :1;
  __REG32 int_bbf    :1;
  __REG32 int_bdn    :1;
  __REG32 int_sdn    :1;
  __REG32 int_busy   :1;
  __REG32 int_event  :1;
  __REG32 int_eop    :1;
  __REG32 int_sod    :1;
  __REG32 int_pur    :1;
  __REG32 int_sync1  :1;
  __REG32 int_sync2  :1;
  __REG32            :5;
} __int_bits;



#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  System manager registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG,0x01000000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__ROMTIME,0x01001000,__READ_WRITE,__romtime_bits);
__IO_REG32_BIT(__SRAMTIME,0x01001004,__READ_WRITE,__sramtime_bits);
__IO_REG32_BIT(__DRAMTIME0,0x01001008,__READ_WRITE,__dramtime0_bits);
__IO_REG32_BIT(__DRAMTIME1,0x0100100c,__READ_WRITE,__dramtime1_bits);
__IO_REG32_BIT(__DRAMTIME2,0x01001010,__READ_WRITE,__dramtime2_bits);
__IO_REG32_BIT(__EXTTIME0,0x01001014,__READ_WRITE,__exttime0_bits);
__IO_REG32_BIT(__EXTTIME1,0x01001018,__READ_WRITE,__exttime1_bits);
__IO_REG32_BIT(__DBUSWTH,0x0100101c,__READ_WRITE,__dbuswth_bits);
__IO_REG32_BIT(__BANKPTR0,0x01001020,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR1,0x01001024,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR2,0x01001028,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR3,0x0100102c,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR4,0x01001030,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR5,0x01001034,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR6,0x01001038,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR7,0x0100103c,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR8,0x01001040,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR9,0x01001044,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__BANKPTR10,0x01001048,__READ_WRITE,__bankptr_bits);
__IO_REG32_BIT(__REFEXTCON,0x0100104c,__READ_WRITE,__refextcon_bits);

/***************************************************************************
 **
 **  Cache special registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__CACHNAE0,0x01000004,__READ_WRITE,__cachnae_bits);
__IO_REG32_BIT(__CACHNAB0,0x01000008,__READ_WRITE,__cachnab_bits);
__IO_REG32_BIT(__CACHNAE1,0x0100000c,__READ_WRITE,__cachnae_bits);
__IO_REG32_BIT(__CACHNAB1,0x01000010,__READ_WRITE,__cachnab_bits);

/***************************************************************************
 **
 **  CDMA control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__CDMACON,0x01003000,__READ_WRITE,__cdmacon_bits);
__IO_REG32_BIT(__CDMASRC,0x01003004,__READ_WRITE,__cdmasrcdst_bits);
__IO_REG32_BIT(__CDMADST,0x01003008,__READ_WRITE,__cdmasrcdst_bits);
__IO_REG32_BIT(__CDMACNT,0x0100300c,__READ_WRITE,__cdmacnt_bits);
__IO_REG32(__CDMARUN,0x01003010,__WRITE);
__IO_REG32(__CDMABUF,0x01003020,__READ);


/***************************************************************************
 **
 **  GDMA control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__GDMACON0,0x01004000,__READ_WRITE,__gdmacon_bits);
__IO_REG32_BIT(__GDMACON1,0x01005000,__READ_WRITE,__gdmacon_bits);
__IO_REG32_BIT(__GDMASRC0,0x01004004,__READ_WRITE,__gdmasrcdst_bits);
__IO_REG32_BIT(__GDMADST0,0x01004008,__READ_WRITE,__gdmasrcdst_bits);
__IO_REG32_BIT(__GDMASRC1,0x01005004,__READ_WRITE,__gdmasrcdst_bits);
__IO_REG32_BIT(__GDMADST1,0x01005008,__READ_WRITE,__gdmasrcdst_bits);
__IO_REG32_BIT(__GDMACNT0,0x0100400c,__READ_WRITE,__gdmacnt_bits);
__IO_REG32_BIT(__GDMACNT1,0x0100500c,__READ_WRITE,__gdmacnt_bits);
__IO_REG32(__GDMARUN0,0x01004020,__WRITE);
__IO_REG32(__GDMARUN1,0x01005020,__WRITE);



/***************************************************************************
 **
 **  UART registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__ULCON0,0x01007000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__UCON0,0x01007004,__READ_WRITE,__ucon0_bits);
__IO_REG32_BIT(__USTAT0,0x01007008,__READ,__ustat0_bits);
__IO_REG32_BIT(__UTXBUF0,0x0100700c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__URXBUF0,0x01007010,__READ,__urxbuf_bits);
__IO_REG32_BIT(__UBRDIV0,0x01007014,__READ_WRITE,__ubrdiv_bits);

/***************************************************************************
 **
 **  SIO registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__ULCON1,0x01009000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__UCON1,0x01009004,__READ_WRITE,__ucon1_bits);
__IO_REG32_BIT(__USTAT1,0x01009008,__READ,__ustat1_bits);
__IO_REG32_BIT(__UTXBUF1,0x0100900c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__URXBUF1,0x01009010,__READ,__urxbuf_bits);
__IO_REG32_BIT(__UBRDIV1,0x01009014,__READ_WRITE,__ubrdiv_bits);

/***************************************************************************
 **
 **  Parallell port registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PPDATA,0x01006000,__READ_WRITE,__ppdata_bits);
__IO_REG32_BIT(__PPSTAT,0x01006004,__READ_WRITE,__ppstat_bits);
__IO_REG32_BIT(__PPACKWTH,0x01006008,__READ_WRITE,__ppackwth_bits);
__IO_REG32_BIT(__PPCON,0x0100600c,__READ_WRITE,__ppcon_bits);
__IO_REG32_BIT(__PPINTEN,0x01006010,__READ_WRITE,__ppi_bits);
__IO_REG32_BIT(__PPINTPND,0x01006014,__READ_WRITE,__ppi_bits);

/***************************************************************************
 **
 **  Programmable Timers registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__TMOD0,0x0100c000,__READ_WRITE,__tmod_bits);
__IO_REG32_BIT(__TMOD1,0x0100c004,__READ_WRITE,__tmod1_bits);
__IO_REG32_BIT(__TMOD2,0x0100c008,__READ_WRITE,__tmod_bits);
__IO_REG32_BIT(__TMOD3,0x0100c00c,__READ_WRITE,__tmod_bits);
__IO_REG32_BIT(__TMOD4,0x0100c010,__READ_WRITE,__tmod_bits);
__IO_REG32_BIT(__TDATA0,0x0100c014,__READ_WRITE,__tdata_bits);
__IO_REG32_BIT(__TDATA1,0x0100c018,__READ_WRITE,__tdata_bits);
__IO_REG32_BIT(__TDATA2,0x0100c01c,__READ_WRITE,__tdata_bits);
__IO_REG32_BIT(__TDATA3,0x0100c020,__READ_WRITE,__tdata_bits);
__IO_REG32_BIT(__TDATA4,0x0100c024,__READ_WRITE,__tdata_bits);
__IO_REG32_BIT(__TCNT0,0x0100c028,__READ,__tcnt_bits);
__IO_REG32_BIT(__TCNT1,0x0100c02c,__READ_WRITE,__tcnt_bits);
__IO_REG32_BIT(__TCNT2,0x0100c030,__READ,__tcnt_bits);
__IO_REG32_BIT(__TCNT3,0x0100c034,__READ,__tcnt_bits);
__IO_REG32_BIT(__TCNT4,0x0100c038,__READ,__tcnt_bits);


/***************************************************************************
 **
 **  Printer interface controller registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__PITXBUF,0x01008000,__WRITE,__pitxbuf_bits);
__IO_REG32_BIT(__PIRXBUF,0x01008004,__READ,__pirxbuf_bits);
__IO_REG32_BIT(__PICMOD,0x01008008,__READ_WRITE,__picmod_bits);
__IO_REG32_BIT(__PISTAT,0x0100800c,__READ,__pistat_bits);
__IO_REG32_BIT(__PIVCON,0x01008010,__READ_WRITE,__pivcon_bits);
__IO_REG32_BIT(__PIPCON,0x01008014,__READ_WRITE,__pipcon_bits);
__IO_REG32_BIT(__PDMACON,0x01008018,__READ_WRITE,__pdmacon_bits);
__IO_REG32_BIT(__PITOPMG,0x0100801c,__READ_WRITE,__pitopmg_bits);
__IO_REG32_BIT(__PILFTMG,0x01008020,__READ_WRITE,__pilftmg_bits);
__IO_REG32_BIT(__PIPXLCNT,0x01008024,__READ_WRITE,__pipxlcnt_bits);
__IO_REG32_BIT(__PDMASRC0,0x01008028,__READ_WRITE,__pdmasrc_bits);
__IO_REG32_BIT(__PDMASRC1,0x01008030,__READ_WRITE,__pdmasrc_bits);
__IO_REG32_BIT(__PDMACNT0,0x0100802c,__READ_WRITE,__pdmacnt_bits);
__IO_REG32_BIT(__PDMACNT1,0x01008034,__READ_WRITE,__pdmacnt_bits);


/***************************************************************************
 **
 **  Graphic engine unit registers
 **
 ***************************************************************************/

__IO_REG32_BIT(__GPATPGWTH,0x0100a000,__WRITE,__gpatpgwth_bits);
__IO_REG32_BIT(__GPATSA,0x0100a004,__WRITE,__gpatsa_bits);
__IO_REG32_BIT(__GPATWTH,0x0100a008,__WRITE,__gpatwth_bits);
__IO_REG32_BIT(__GPATHT,0x0100a00c,__WRITE,__gpatht_bits);
__IO_REG32_BIT(__GPATISA,0x0100a010,__WRITE,__gpatisa_bits);
__IO_REG32_BIT(__GPATXR,0x0100a014,__WRITE,__gpatxr_bits);
__IO_REG32_BIT(__GPATYR,0x0100a018,__WRITE,__gpatyr_bits);
__IO_REG32_BIT(__GSRCSA,0x0100a01c,__WRITE,__gsrcsa_bits);
__IO_REG32_BIT(__GSRCPGWTH,0x0100a020,__WRITE,__gsrcpgwth_bits);
__IO_REG32_BIT(__GDSTSA,0x0100a024,__WRITE,__gdstsa_bits);
__IO_REG32_BIT(__GDSTPGWTH,0x0100a028,__WRITE,__gdstwth_bits);
__IO_REG32_BIT(__GDSTWTH,0x0100a02c,__WRITE,__gdstwth_bits);
__IO_REG32_BIT(__GDSTHT,0x0100a030,__READ_WRITE,__gdstht_bits);
__IO_REG32_BIT(__GCON,0x0100a034,__READ_WRITE,__gcon_bits);
__IO_REG32_BIT(__GBANDPTR,0x0100a038,__WRITE,__gbandptr_bits);
__IO_REG32_BIT(__GSLTSA,0x0100a03c,__READ_WRITE,__gsltsa_bits);
__IO_REG32_BIT(__GPCTSA,0x0100a040,__READ_WRITE,__gpctsa_bits);


/***************************************************************************
 **
 **  Imaging function block Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__EXPROTCON,0x0100d000,__READ_WRITE,__exprotcon_bits);
__IO_REG32_BIT(__EXPDATA0,0x0100d004,__READ_WRITE,__expdata_bits);
__IO_REG32_BIT(__EXPDATA1,0x0100d008,__READ,__expdata_bits);
__IO_REG32_BIT(__EXPDATA2,0x0100d00c,__READ,__expdata_bits);
__IO_REG32_BIT(__ROTDATA0,0x0100d010,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA1,0x0100d014,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA2,0x0100d018,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA3,0x0100d01c,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA4,0x0100d020,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA5,0x0100d024,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA6,0x0100d028,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA7,0x0100d02c,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA8,0x0100d030,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA9,0x0100d034,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA10,0x0100d038,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA11,0x0100d03c,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA12,0x0100d040,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA13,0x0100d044,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA14,0x0100d048,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__ROTDATA15,0x0100d04c,__READ_WRITE,__rotdata_bits);
__IO_REG32_BIT(__VISHTSTAT,0x0100e000,__READ,__vishtstat_bits);
__IO_REG32_BIT(__VISHTCON,0x0100e004,__READ_WRITE,__vishtcon_bits);
__IO_REG32_BIT(__VISDDSIZE,0x0100e008,__READ_WRITE,__visdsize_bits);
__IO_REG32_BIT(__VISSDSIZE,0x0100e00c,__READ_WRITE,__visdsize_bits);
__IO_REG32_BIT(__VISSDATA,0x0100e010,__READ_WRITE,__vissdata_bits);
__IO_REG32_BIT(__VISDDATA,0x0100e014,__READ,__visddata_bits);
__IO_REG32_BIT(__HTRDATA,0x0100e018,__READ_WRITE,__htrdata_bits);
__IO_REG32_BIT(__HTSDATA,0x0100e01c,__READ_WRITE,__htsdata_bits);
__IO_REG32_BIT(__HTDATA,0x0100e020,__READ,__htdata_bits);


/***************************************************************************
 **
 ** IO Ports registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__IOPMOD,0x0100b000,__READ_WRITE,__iopmod_bits);
__IO_REG32_BIT(__EXTINTMOD,0x0100b004,__READ_WRITE,__extintmod_bits);
__IO_REG32_BIT(__IOPDATA,0x0100b008,__READ_WRITE,__iopdata_bits);

/***************************************************************************
 **
 **  Interrupt controller Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTMOD,0x01002000,__READ_WRITE,__int_bits);
__IO_REG32_BIT(__INTPND,0x01002004,__READ_WRITE,__int_bits);
__IO_REG32_BIT(__INTMSK,0x01002008,__READ_WRITE,__int_bits);



/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3C4610 interrupt sources
 **
 ***************************************************************************/
#define INT_EXT0    0  /* external interrupt 0  (at I/O port 6) */
#define INT_EXT1    1  /* external interrupt 1 (at I/O port 7)  */
#define INT_TIMER0  2  /* timer 0 interrupt                     */
#define INT_TIMER1  3  /* timer 1 interrupt                     */
#define INT_TIMER2  4  /* timer 2 interrupt                     */
#define INT_TIMER3  5  /* timer 3 interrupt                     */
#define INT_TIMER4  6  /* timer 4 interrupt                     */
#define INT_TXD0    7  /* UART serial data transmit interrupt   */
#define INT_RXD0    8  /* UART serial data receive interrupt    */
#define INT_USR0    9  /* UART error interrupt                  */
#define INT_TXD1   10  /* SIO serial data transmit interrupt    */
#define INT_RXD1   11  /* SIO serial datareceive interrupt      */
#define INT_USR1   12  /* SIO error interrupt                   */
#define INT_PPIC   13  /* parallell port interface controller interrupt  */
#define INT_DMA0   14  /* DMA channel 0 interrupt               */
#define INT_DMA1   15  /* DMA channel 1 interrupt               */
#define INT_DMA2   16  /* DMA channel 2 interrupt               */
#define INT_BBF    17  /* band fault interrupt                  */
#define INT_BDN    18  /* bitblt done interrupt                 */
#define INT_SDN    19  /* scanline transfer done interrupt      */
#define INT_BUSY   20  /* printer engine busy interrupt         */
#define INT_EVENT  21  /* printer interface event interrupt     */
#define INT_EOP    22  /* PIFC end-of-page interrupt            */
#define INT_SOD    23  /* PIFC start-of-DMA interrupt           */
#define INT_PUR    24  /* PIFC page underrun interrupt          */
#define INT_SYNC1  25  /* printer interface event interrupt     */
#define INT_SYNC2  26  /* printer interface event interrupt     */


#endif    /* __S3C4610_H */
