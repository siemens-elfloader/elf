/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C4510B
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2000
 **
 **    $Revision: 1.4 $
 **
 ***************************************************************************/

#ifndef __S3C4510B_H
#define __S3C4510B_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C4510B SPECIAL FUNCTION REGISTERS
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
  __REG32 se   :1; /* stall enable, must be 0 */
  __REG32 ce   :1; /* cache enable            */
  __REG32 we   :1; /* write buffer enable     */
  __REG32      :1;
  __REG32 cm   :2; /* cache mode */
  __REG32 isbp :10;/* internal SRAM base pointer */
  __REG32 srbbp:10;/* special register bank base pointer */
  __REG32 pd_id:5;
  __REG32 sdm  :1;
} __syscfg_bits;

/* SM: clock control register  */
typedef struct {
  __REG32 cdv  :16; /* clock dividing value    */
  __REG32 wait :1;  /* ROM bank 5 wait enable  */
  __REG32 addre:1;  /* ROM bank 5 address/data bus Mux enable */
  __REG32 tac  :2;  /* Mux bus address cycle   */
  __REG32      :11;
  __REG32 tb   :1;  /* test bit, should be 0 */
} __clkcon_bits;

/* SM: External I/O access control register 0 */
typedef struct {
  __REG32 tcos0 :3; /* chip selection set-up time on nOE   */
  __REG32 tacs0 :3; /* Address set-up time before nECS     */
  __REG32 tcoh0 :3; /* chip selection hold time on nOE     */
  __REG32 tacc0 :3; /* Access cycles                       */
  __REG32       :4;
  __REG32 tcos1 :3;
  __REG32 tacs1 :3;
  __REG32 tcoh1 :3;
  __REG32 tacc1 :3;
  __REG32       :4;
} __extacon0_bits;

/* SM: External I/O access control register 1 */
typedef struct {
  __REG32 tcos2 :3; /* chip selection set-up time on nOE   */
  __REG32 tacs2 :3; /* Address set-up time before nECS     */
  __REG32 tcoh2 :3; /* chip selection hold time on nOE     */
  __REG32 tacc2 :3; /* Access cycles                       */
  __REG32       :4;
  __REG32 tcos3 :3;
  __REG32 tacs3 :3;
  __REG32 tcoh3 :3;
  __REG32 tacc3 :3;
  __REG32       :4;
} __extacon1_bits;

/* SM:  data bus width register */
typedef struct {
  __REG32 dsr0  :2;
  __REG32 dsr1  :2;
  __REG32 dsr2  :2;
  __REG32 dsr3  :2;
  __REG32 dsr4  :2;
  __REG32 dsr5  :2;
  __REG32 dsd0  :2;
  __REG32 dsd1  :2;
  __REG32 dsd2  :2;
  __REG32 dsd3  :2;
  __REG32 dsx0  :2;
  __REG32 dsx1  :2;
  __REG32 dsx2  :2;
  __REG32 dsx3  :2;
  __REG32       :4;
} __extdbwth_bits;

/* SM:  ROM/SRAM/Flash control register */
typedef struct {
  __REG32 pmc  :2;
  __REG32 tpa  :2;
  __REG32 tacc :3;
  __REG32      :3;
  __REG32 bp   :10;
  __REG32 np   :10;
  __REG32      :2;
} __romcon_bits;

/* SM: DRAM control register */
typedef struct {
  __REG32 edo  :1;
  __REG32 tcs  :2;
  __REG32 tcp  :1;
  __REG32      :3;
  __REG32 trc  :1;
  __REG32 trp  :2;
  __REG32 bp   :10;
  __REG32 np   :10;
  __REG32 can :2;
} __dramcon_bits;


/* SM:  DRAM refresh and external I/O control register */
typedef struct {
  __REG32 bp   :10;
  __REG32      :5;
  __REG32 vsf  :1;
  __REG32 ren  :1;
  __REG32 tchr :3;
  __REG32 tcsr :1;
  __REG32 rcv  :11;
} __refextcon_bits;

/* BC: control status register */
typedef struct {
  __REG32 bf   :1;
  __REG32 ien  :1;
  __REG32 lrb  :1;
  __REG32 ack  :1;
  __REG32 cond0:1;
  __REG32 cond1:1;
  __REG32 busy :1;
  __REG32 reset:1;
  __REG32      :24;
} __iiccon_bits;

/* BC: shift buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __iicbuf_bits;

/* BC: prescaler register */
typedef struct {
  __REG32 pv   :16;
  __REG32      :16;
} __iicps_bits;

/* BC: prescaler counter register */
typedef struct {
  __REG32 cv   :16;
  __REG32      :16;
} __iiccnt_bits;

/* EC: buffered DMA receive control register */
typedef struct {
  __REG32 brxbrst  :5;
  __REG32 brxstsko :1;
  __REG32 brxmainc :1;
  __REG32 brxdie   :1;
  __REG32 brxnlie  :1;
  __REG32 brxnoie  :1;
  __REG32 brxmsoie :1;
  __REG32 brxlittle:1;
  __REG32 brxwa    :2;
  __REG32 brxen    :1;
  __REG32 brxrs    :1;
  __REG32 brxempty :1;
  __REG32 brxearly :1;
  __REG32          :14;
} __bdmarxcon_bits;

/* EC: buffered DMA transmit control register */
typedef struct {
  __REG32 btxbrst  :5;
  __REG32 btxstsko :1;
  __REG32          :1;
  __REG32 btxccpie :1;
  __REG32 btxnlie  :1;
  __REG32 btxnoie  :1;
  __REG32 btxempty :1;
  __REG32 btxmsl   :3;
  __REG32 btxen    :1;
  __REG32 btxrs    :1;
  __REG32          :16;
} __bdmatxcon_bits;

/* EC: buffered DMA transmit frame descriptor start address register */
typedef struct {
  __REG32 addr :26;
  __REG32      :6;
} __bdmatxptr_bits;

/* EC: buffered DMA receive frame descriptor start address register */
typedef struct {
  __REG32 addr :26;
  __REG32      :6;
} __bdmarxptr_bits;

/* EC: buffered DMA receive frame maximum size register */
typedef struct {
  __REG32 brxlsz  :16;
  __REG32 brxfsz  :16;
} __bdmarxlsz_bits;

/* EC: buffered DMA status register */
typedef struct {
  __REG32 brxrdf   :1;
  __REG32 brxnl    :1;
  __REG32 brxno    :1;
  __REG32 brxmso   :1;
  __REG32 brxempty :1;
  __REG32 brxsearly:1;
  __REG32          :1;
  __REG32 brxfrf   :1;
  __REG32 brxnfr   :8;
  __REG32 btxccp   :1;
  __REG32 btxnl    :1;
  __REG32 btxno    :1;
  __REG32          :1;
  __REG32 btxempty :1;
  __REG32          :11;
} __bdmastat_bits;


/* EC: media access control register */
typedef struct {
  __REG32 haltreq   :1;
  __REG32 haltimm   :1;
  __REG32 reset     :1;
  __REG32 fulldup   :1;
  __REG32 macloop   :1;
  __REG32           :1;
  __REG32 mii_off   :1;
  __REG32 loop_10   :1;
  __REG32           :2;
  __REG32 missroll  :1;
  __REG32           :1;
  __REG32 mdc_off   :1;
  __REG32 enmissroll:1;
  __REG32           :1;
  __REG32 link_10   :1;
  __REG32           :16;
} __macon_bits;

/* EC: CAM control register */
typedef struct {
  __REG32 stationacc:1;
  __REG32 groupacc  :1;
  __REG32 broadacc  :1;
  __REG32 negcam    :1;
  __REG32 compen    :1;
  __REG32           :27;
} __camcon_bits;

/* EC: MAC transmit control register */
typedef struct {
  __REG32 txen      :1;
  __REG32 txhalt    :1;
  __REG32 nopad     :1;
  __REG32 nocrc     :1;
  __REG32 fback     :1;
  __REG32 nodef     :1;
  __REG32 sdpause   :1;
  __REG32 sqen      :1;
  __REG32 enunder   :1;
  __REG32 endefer   :1;
  __REG32 enncarr   :1;
  __REG32 enexcoll  :1;
  __REG32 enlatecoll:1;
  __REG32 entxpar   :1;
  __REG32 encomp    :1;
  __REG32           :17;
} __mactxcon_bits;

/* EC: MAC transmit status register */
typedef struct {
  __REG32 txcoll    :4;
  __REG32 excoll    :1;
  __REG32 txdeferred:1;
  __REG32 paused    :1;
  __REG32 inttx     :1;
  __REG32 under     :1;
  __REG32 defer     :1;
  __REG32 ncarr     :1;
  __REG32 sqe       :1;
  __REG32 latecoll  :1;
  __REG32 txpar     :1;
  __REG32 comp      :1;
  __REG32 txhalted  :1;
  __REG32           :16;
} __mactxstat_bits;

/* EC: MAC receive control register */
typedef struct {
  __REG32 rxen      :1;
  __REG32 rxhalt    :1;
  __REG32 longen    :1;
  __REG32 shorten   :1;
  __REG32 stripcrc  :1;
  __REG32 passctl   :1;
  __REG32 ignorecrc :1;
  __REG32           :1;
  __REG32 enalign   :1;
  __REG32 encrcerr  :1;
  __REG32 enover    :1;
  __REG32 enlongerr :1;
  __REG32           :1;
  __REG32 enrxpar   :1;
  __REG32 engood    :1;
  __REG32           :17;
} __macrxcon_bits;

/* EC: MAC receive status register */
typedef struct {
  __REG32           :5;
  __REG32 ctlrecd   :1;
  __REG32 intrx     :1;
  __REG32 rx10stat  :1;
  __REG32 alignerr  :1;
  __REG32 crcerr    :1;
  __REG32 overflow  :1;
  __REG32 longerr   :1;
  __REG32           :1;
  __REG32 rxpar     :1;
  __REG32 good      :1;
  __REG32 rxhalted  :1;
  __REG32           :16;
} __macrxstat_bits;

/* EC: MAC station management data register */
typedef struct {
  __REG16 data      :16;
} __stadata_bits;

/* EC: MAC station management data control and address register */
typedef struct {
  __REG32 addr      :5;
  __REG32 phy       :5;
  __REG32 wr        :1;
  __REG32 busy      :1;
  __REG32 presup    :1;
  __REG32 mdc_cr    :3;
  __REG32           :16;
} __stacon_bits;

/* EC: CAM enable register */
typedef struct {
  __REG32 camen :21;
  __REG32       :11;
} __camen_bits;


/* EC: MAC missed error count register */
typedef struct {
  __REG32 alignerrcnt :16;
  __REG32             :16;
} __emisscnt_bits;


/* EC: MAC received pause count register */
typedef struct {
  __REG16 epzcnt    :16;
} __epzcnt_bits;

/* EC: MAC remote pause count register */
typedef struct {
  __REG16 epmpzcnt  :16;
} __ermpzcnt_bits;

/* EC: MAC transmit control frame status register */
typedef struct {
  __REG16 tx_stat   :16;
} __etxstat_bits;

/* HDLC: control mode register*/
typedef struct {
  __REG32 mff      :1;
  __REG32          :3;
  __REG32 rxlittle :1;
  __REG32 txlittle :1;
  __REG32          :2;
  __REG32 txpl     :3;
  __REG32          :1;
  __REG32 df       :3;
  __REG32          :1;
  __REG32 dpllclk  :3;
  __REG32 brgclk   :1;
  __REG32 txclk    :3;
  __REG32          :1;
  __REG32 rxclk    :3;
  __REG32          :1;
  __REG32 txcops   :3;
  __REG32          :1;
} __hmode_bits;

/* HDLC: control register */
typedef struct {
  __REG32 txrs     :1;
  __REG32 rxrs     :1;
  __REG32 dtxrs    :1;
  __REG32 drxrs    :1;
  __REG32 txen     :1;
  __REG32 rxen     :1;
  __REG32 dtxen    :1;
  __REG32 drxen    :1;
  __REG32 dpllen   :1;
  __REG32 brgen    :1;
  __REG32 tx4wd    :1;
  __REG32 rx4wd    :1;
  __REG32 rxwa     :2;
  __REG32 dtxstsk  :1;
  __REG32 drxstsk  :1;
  __REG32 drxmadec :1;
  __REG32 txflag   :1;
  __REG32 txsflag  :1;
  __REG32 txloop   :1;
  __REG32 rxecho   :1;
  __REG32 txabtext :1;
  __REG32 txabt    :1;
  __REG32 txprmb   :1;
  __REG32 txdtr    :1;
  __REG32 rxdiscon :1;
  __REG32 txnocrc  :1;
  __REG32 rxnocrc  :1;
  __REG32 autoen   :1;
  __REG32          :3;
} __hcon_bits;


/* HDLC: status register */
typedef struct {
  __REG32 rxrb     :4;
  __REG32 txfc     :1;
  __REG32 txfa     :1;
  __REG32 txcts    :1;
  __REG32 txscts   :1;
  __REG32 txu      :1;
  __REG32 rxfa     :1;
  __REG32          :1;
  __REG32 rxfd     :1;
  __REG32 rxdcd    :1;
  __REG32 rxsdcd   :1;
  __REG32 rxfv     :1;
  __REG32 rxidle   :1;
  __REG32 rxabt    :1;
  __REG32 rxcrce   :1;
  __REG32 rxno     :1;
  __REG32 rxov     :1;
  __REG32 rxmov    :1;
  __REG32          :1;
  __REG32 dtxabt   :1;
  __REG32 rxierr   :1;
  __REG32 drxfd    :1;
  __REG32 drxnl    :1;
  __REG32 drxno    :1;
  __REG32 dtxfd    :1;
  __REG32 dtxnl    :1;
  __REG32 dtxno    :1;
  __REG32 dpllom   :1;
  __REG32 dplltm   :1;
} __hstat_bits;

/* HDLC: interrupt enable register */
typedef struct {
  __REG32          :4;
  __REG32 txfcie   :1;
  __REG32 txfaie   :1;
  __REG32          :1;
  __REG32 txsctsie :1;
  __REG32 txuie    :1;
  __REG32 rxfaie   :1;
  __REG32          :1;
  __REG32 rxfdie   :1;
  __REG32          :1;
  __REG32 rxsdcdie :1;
  __REG32 rxfvie   :1;
  __REG32 rxidleie :1;
  __REG32 rxabtie  :1;
  __REG32 rxcrceie :1;
  __REG32 rxnoie   :1;
  __REG32 rxovie   :1;
  __REG32 rxmovie  :1;
  __REG32          :1;
  __REG32 dtxabtie :1;
  __REG32 rxierrie :1;
  __REG32 drxfdie  :1;
  __REG32 drxnlie  :1;
  __REG32 drxnoie  :1;
  __REG32 dtxfdie  :1;
  __REG32 dtxnlie  :1;
  __REG32 dtxnoie  :1;
  __REG32 dpllomie :1;
  __REG32 dplltmie :1;
} __hinten_bits;

/* HDLC: BRG time constant register */
typedef struct {
  __REG32 cnt2     :2;
  __REG32 cnt1     :2;
  __REG32 cnt0     :12;
  __REG32          :16;
} __hbrgtc_bits;


/* HDLC: preamble constant register */
typedef struct {
  __REG32 pp      :8;
  __REG32         :24;
} __hprmb_bits;


/* HDLC: station address and HMASK register */
typedef struct {
  __REG32 byte4 :8;
  __REG32 byte3 :8;
  __REG32 byte2 :8;
  __REG32 byte1 :8;
} __hsarmask_bits;

/* HDLC: DMA TX buffer descriptor pointer register*/
typedef struct {
  __REG32 ptr     :26;
  __REG32         :6;
} __hdmatxptr_bits;

/* HDLC: DMA RX buffer descriptor pointer register*/
typedef struct {
  __REG32 ptr     :26;
  __REG32         :6;
} __hdmarxptr_bits;

/* HDLC: Maximum frame length register */
typedef struct {
  __REG32 mfl     :16;
  __REG32         :16;
} __hmflr_bits;

/* HDLC: DMA RX buffer size register */
typedef struct {
  __REG32 rbs     :16;
  __REG32         :16;
} __hrbsr_bits;

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
  __REG32 fb    :1;
  __REG32 td    :1;
  __REG32 sb    :1;
  __REG32 tw    :2;
  __REG32 cn    :1;
  __REG32 dm    :1;
  __REG32       :16;
} __gdmacon_bits;

/* GDMA source /destination address register */
typedef struct {
  __REG32 addr  :26;
  __REG32       :6;
} __gdmasrcdest_bits;

/* GDMA transfer count register */
typedef struct {
  __REG32 tc    :24;
  __REG32       :8;
} __gdmacnt_bits;

/* UART: line control register */
typedef struct {
  __REG32 wl    :2;
  __REG32 stb   :1;
  __REG32 pmd   :3;
  __REG32 sc    :1;
  __REG32 ir    :1;
  __REG32       :24;
} __ulcon_bits;

/* UART: control register */
typedef struct {
  __REG32 rxm   :2;
  __REG32 rxsi  :1;
  __REG32 txm   :2;
  __REG32 dsr   :1;
  __REG32 sbk   :1;
  __REG32 lpb   :1;
  __REG32       :24;
} __ucon_bits;

/* UART: status register */
typedef struct {
  __REG32 ov   :1;
  __REG32 pe   :1;
  __REG32 fe   :1;
  __REG32 bkd  :1;
  __REG32 dtr  :1;
  __REG32 rdr  :1;
  __REG32 tbe  :1;
  __REG32 tc   :1;
  __REG32      :24;
} __ustat_bits;

/* UART: transmit buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __utxbuf_bits;

/* UART: receive buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __urxbuf_bits;

/* UART: baud rate divisor register */
typedef struct {
  __REG32 cnt1 :4;
  __REG32 cnt0 :12;
  __REG32      :16;
} __ubrdiv_bits;

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

/* I/O: port mode register */
typedef struct {
  __REG32 m0    :1; /* I/O mode bit for port 0 */
  __REG32 m1    :1;
  __REG32 m2    :1;
  __REG32 m3    :1;
  __REG32 m4    :1;
  __REG32 m5    :1;
  __REG32 m6    :1;
  __REG32 m7    :1;
  __REG32 m8    :1;
  __REG32 m9    :1;
  __REG32 m10   :1;
  __REG32 m11   :1;
  __REG32 m12   :1;
  __REG32 m13   :1;
  __REG32 m14   :1;
  __REG32 m15   :1;
  __REG32 m16   :1;
  __REG32 m17   :1;
  __REG32       :14;
} __iopmod_bits;


/* I/O: port control register */
typedef struct {
  __REG32 xirq0 :5;
  __REG32 xirq1 :5;
  __REG32 xirq2 :5;
  __REG32 xirq3 :5;
  __REG32 drq0  :3;
  __REG32 drq1  :3;
  __REG32 dak0  :2;
  __REG32 dak1  :2;
  __REG32 toen0 :1;
  __REG32 toen1 :1;
} __iopcon_bits;


/* I/O: port data register */
typedef struct {
  __REG32 p0  :1;
  __REG32 p1  :1;
  __REG32 p2  :1;
  __REG32 p3  :1;
  __REG32 p4  :1;
  __REG32 p5  :1;
  __REG32 p6  :1;
  __REG32 p7  :1;
  __REG32 p8  :1;
  __REG32 p9  :1;
  __REG32 p10 :1;
  __REG32 p11 :1;
  __REG32 p12 :1;
  __REG32 p13 :1;
  __REG32 p14 :1;
  __REG32 p15 :1;
  __REG32 p16 :1;
  __REG32 p17 :1;
  __REG32     :14;
} __iopdata_bits;

/* IC: interrupt mode/pending register*/
typedef struct {
  __REG32 m0  :1;
  __REG32 m1  :1;
  __REG32 m2  :1;
  __REG32 m3  :1;
  __REG32 m4  :1;
  __REG32 m5  :1;
  __REG32 m6  :1;
  __REG32 m7  :1;
  __REG32 m8  :1;
  __REG32 m9  :1;
  __REG32 m10 :1;
  __REG32 m11 :1;
  __REG32 m12 :1;
  __REG32 m13 :1;
  __REG32 m14 :1;
  __REG32 m15 :1;
  __REG32 m16 :1;
  __REG32 m17 :1;
  __REG32 m18 :1;
  __REG32 m19 :1;
  __REG32 m20 :1;
  __REG32     :11;
} __intmodpnd_bits;

/* IC: interrupt mask register*/
typedef struct {
  __REG32 m0  :1;
  __REG32 m1  :1;
  __REG32 m2  :1;
  __REG32 m3  :1;
  __REG32 m4  :1;
  __REG32 m5  :1;
  __REG32 m6  :1;
  __REG32 m7  :1;
  __REG32 m8  :1;
  __REG32 m9  :1;
  __REG32 m10 :1;
  __REG32 m11 :1;
  __REG32 m12 :1;
  __REG32 m13 :1;
  __REG32 m14 :1;
  __REG32 m15 :1;
  __REG32 m16 :1;
  __REG32 m17 :1;
  __REG32 m18 :1;
  __REG32 m19 :1;
  __REG32 m20 :1;
  __REG32 g   :1;
  __REG32     :10;
} __intmsk_bits;

/* IC: interrupt priority register 0 */
typedef struct {
  __REG32 priority0 :5;
  __REG32           :3;
  __REG32 priority1 :5;
  __REG32           :3;
  __REG32 priority2 :5;
  __REG32           :3;
  __REG32 priority3 :5;
  __REG32           :3;
} __intpri0_bits;

/* IC: interrupt priority register 1 */
typedef struct {
  __REG32 priority4 :5;
  __REG32           :3;
  __REG32 priority5 :5;
  __REG32           :3;
  __REG32 priority6 :5;
  __REG32           :3;
  __REG32 priority7 :5;
  __REG32           :3;
} __intpri1_bits;


/* IC: interrupt priority register 2*/
typedef struct {
  __REG32 priority8 :5;
  __REG32           :3;
  __REG32 priority9 :5;
  __REG32           :3;
  __REG32 priority10:5;
  __REG32           :3;
  __REG32 priority11:5;
  __REG32           :3;
} __intpri2_bits;

/* IC: interrupt priority register 3 */
typedef struct {
  __REG32 priority12:5;
  __REG32           :3;
  __REG32 priority13:5;
  __REG32           :3;
  __REG32 priority14:5;
  __REG32           :3;
  __REG32 priority15:5;
  __REG32           :3;
} __intpri3_bits;

/* IC: interrupt priority register 4*/
typedef struct {
  __REG32 priority16:5;
  __REG32           :3;
  __REG32 priority17:5;
  __REG32           :3;
  __REG32 priority18:5;
  __REG32           :3;
  __REG32 priority19:5;
  __REG32           :3;
} __intpri4_bits;

/* IC: interrupt priority register 5*/
typedef struct {
  __REG32 priority20:5;
  __REG32           :27;
} __intpri5_bits;



#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  System manager registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG,0x03ff0000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__CLKCON,0x03ff3000,__READ_WRITE,__clkcon_bits);
__IO_REG32_BIT(__EXTACON0,0x03ff3008,__READ_WRITE,__extacon0_bits);
__IO_REG32_BIT(__EXTACON1,0x03ff300c,__READ_WRITE,__extacon1_bits);
__IO_REG32_BIT(__EXTDBWTH,0x03ff3010,__READ_WRITE,__extdbwth_bits);
__IO_REG32_BIT(__ROMCON0,0x03ff3014,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__ROMCON1,0x03ff3018,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__ROMCON2,0x03ff301c,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__ROMCON3,0x03ff3020,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__ROMCON4,0x03ff3024,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__ROMCON5,0x03ff3028,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__DRAMCON0,0x03ff302c,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__DRAMCON1,0x03ff3030,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__DRAMCON2,0x03ff3034,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__DRAMCON3,0x03ff3038,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__REFEXTCON,0x03ff303c,__READ_WRITE,__refextcon_bits);

/***************************************************************************
 **
 **  i2c bus special registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__IICCON,0x03fff000,__READ_WRITE,__iiccon_bits);
__IO_REG32_BIT(__IICBUF,0x03fff004,__READ_WRITE,__iicbuf_bits);
__IO_REG32_BIT(__IICPS,0x03fff008,__READ_WRITE,__iicps_bits);
__IO_REG32_BIT(__IICCNT,0x03fff00c,__READ_WRITE,__iiccnt_bits);

/***************************************************************************
 **
 **  Ethernet Controller BDMA registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__BDMATXCON,0x03ff9000,__READ_WRITE,__bdmatxcon_bits);
__IO_REG32_BIT(__BDMARXCON,0x03ff9004,__READ_WRITE,__bdmarxcon_bits);
__IO_REG32_BIT(__BDMATXPTR,0x03ff9008,__READ_WRITE,__bdmatxptr_bits);
__IO_REG32_BIT(__BDMARXPTR,0x03ff900c,__READ_WRITE,__bdmarxptr_bits);
__IO_REG32_BIT(__BDMARXLSZ,0x03ff9010,__READ_WRITE,__bdmarxlsz_bits);
__IO_REG32_BIT(__BDMASTAT,0x03ff9014,__READ_WRITE,__bdmastat_bits);

__IO_REG32(__CAM,0x03ff9100,__WRITE);
__IO_REG32(__BDMATXBUF,0x03ff9200,__READ_WRITE);
__IO_REG32(__BDMARXBUF,0x03ff9900,__READ_WRITE);



/***************************************************************************
 **
 **  Ethernet Controller MAC registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__MACON,0x03ffA000,__READ_WRITE,__macon_bits);
__IO_REG32_BIT(__CAMCON,0x03ffA004,__READ_WRITE,__camcon_bits);
__IO_REG32_BIT(__MACTXCON,0x03ffA008,__READ_WRITE,__mactxcon_bits);
__IO_REG32_BIT(__MACTXSTAT,0x03ffA00c,__READ_WRITE,__mactxstat_bits);
__IO_REG32_BIT(__MACRXCON,0x03ffA010,__READ_WRITE,__macrxcon_bits);
__IO_REG32_BIT(__MACRXSTAT,0x03ffA014,__READ_WRITE,__macrxstat_bits);
__IO_REG16_BIT(__STADATA,0x03ffA018,__READ_WRITE,__stadata_bits);
__IO_REG32_BIT(__STACON,0x03ffA01c,__READ_WRITE,__stacon_bits);
__IO_REG32_BIT(__CAMEN,0x03ffA028,__READ_WRITE,__camen_bits);
__IO_REG32_BIT(__EMISSCNT,0x03ffA03c,__READ_WRITE,__emisscnt_bits);
__IO_REG16_BIT(__EPZCNT,0x03ffA040,__READ,__epzcnt_bits);
__IO_REG16_BIT(__ERMPZCNT,0x03ffA044,__READ,__ermpzcnt_bits);
__IO_REG16_BIT(__ETXSTAT,0x03ff9040,__READ,__etxstat_bits);

/***************************************************************************
 **
 **  HDLC channel A registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__HMODEA,0x03ff7000,__READ_WRITE,__hmode_bits);
__IO_REG32_BIT(__HCONA,0x03ff7004,__READ_WRITE,__hcon_bits);
__IO_REG32_BIT(__HSTATA,0x03ff7008,__READ_WRITE,__hstat_bits);
__IO_REG32_BIT(__HINTENA,0x03ff700c,__READ_WRITE,__hinten_bits);
__IO_REG32(__HTXFIFOCA,0x03ff7010,__WRITE);
__IO_REG32(__HTXFIFOTA,0x03ff7014,__WRITE);
__IO_REG32(__HRXFIFOA,0x03ff7018,__READ);
__IO_REG32_BIT(__HBRGTCA,0x03ff701c,__READ_WRITE,__hbrgtc_bits);
__IO_REG32_BIT(__HPRMBA,0x03ff7020,__READ_WRITE,__hprmb_bits);
__IO_REG32_BIT(__HSAR0A,0x03ff7024,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HSARA1,0x03ff7028,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HSAR2A,0x03ff702c,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HSAR3A,0x03ff7030,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HMASKA,0x03ff7034,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HDMATXPTRA,0x03ff7038,__READ_WRITE,__hdmatxptr_bits);
__IO_REG32_BIT(__HDMARXPTRA,0x03ff703c,__READ_WRITE,__hdmarxptr_bits);
__IO_REG32_BIT(__HMFLRA,0x03ff7040,__READ_WRITE,__hmflr_bits);
__IO_REG32_BIT(__HRBSRA,0x03ff7044,__READ_WRITE,__hrbsr_bits);


/***************************************************************************
 **
 **  HDLC channel B registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__HMODEB,0x03ff8000,__READ_WRITE,__hmode_bits);
__IO_REG32_BIT(__HCONB,0x03ff8004,__READ_WRITE,__hcon_bits);
__IO_REG32_BIT(__HSTATB,0x03ff8008,__READ_WRITE,__hstat_bits);
__IO_REG32_BIT(__HINTENB,0x03ff800c,__READ_WRITE,__hinten_bits);
__IO_REG32(__HTXFIFOCB,0x03ff8010,__WRITE);
__IO_REG32(__HTXFIFOTB,0x03ff8014,__WRITE);
__IO_REG32(__HRXFIFOB,0x03ff8018,__READ);
__IO_REG32_BIT(__HBRGTCB,0x03ff801c,__READ_WRITE,__hbrgtc_bits);
__IO_REG32_BIT(__HPRMBB,0x03ff8020,__READ_WRITE,__hprmb_bits);
__IO_REG32_BIT(__HSAR0B,0x03ff8024,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HSAR1B,0x03ff8028,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HSAR2B,0x03ff802c,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HSAR3B,0x03ff8030,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HMASKB,0x03ff8034,__READ_WRITE,__hsarmask_bits);
__IO_REG32_BIT(__HDMATXPTRB,0x03ff8038,__READ_WRITE,__hdmatxptr_bits);
__IO_REG32_BIT(__HDMARXPTRB,0x03ff803c,__READ_WRITE,__hdmarxptr_bits);
__IO_REG32_BIT(__HMFLRB,0x03ff8040,__READ_WRITE,__hmflr_bits);
__IO_REG32_BIT(__HRBSRB,0x03ff8044,__READ_WRITE,__hrbsr_bits);


/***************************************************************************
 **
 **  GDMA Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__GDMACON0,0x03ffb000,__READ_WRITE,__gdmacon_bits);
__IO_REG32_BIT(__GDMACON1,0x03ffc000,__READ_WRITE,__gdmacon_bits);
__IO_REG32_BIT(__GDMASRC0,0x03ffb004,__READ_WRITE,__gdmasrcdest_bits);
__IO_REG32_BIT(__GDMADST0,0x03ffb008,__READ_WRITE,__gdmasrcdest_bits);
__IO_REG32_BIT(__GDMASRC1,0x03ffc004,__READ_WRITE,__gdmasrcdest_bits);
__IO_REG32_BIT(__GDMADST1,0x03ffc008,__READ_WRITE,__gdmasrcdest_bits);
__IO_REG32_BIT(__GDMACNT0,0x03ffb00c,__READ_WRITE,__gdmacnt_bits);
__IO_REG32_BIT(__GDMACNT1,0x03ffc00c,__READ_WRITE,__gdmacnt_bits);

/***************************************************************************
 **
 **  UART Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__ULCON0,0x03ffd000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__ULCON1,0x03ffe000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__UCON0,0x03ffd004,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__UCON1,0x03ffe004,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__USTAT0,0x03ffd008,__READ,__ustat_bits);
__IO_REG32_BIT(__USTAT1,0x03ffe008,__READ,__ustat_bits);
__IO_REG32_BIT(__UTXBUF0,0x03ffd00c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__UTXBUF1,0x03ffe00c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__URXBUF0,0x03ffd010,__READ,__urxbuf_bits);
__IO_REG32_BIT(__URXBUF1,0x03ffe010,__READ,__urxbuf_bits);
__IO_REG32_BIT(__UBRDIV0,0x03ffd014,__READ_WRITE,__ubrdiv_bits);
__IO_REG32_BIT(__UBRDIV1,0x03ffe014,__READ_WRITE,__ubrdiv_bits);
__IO_REG32(__BRDCNT0,0x03ffd018,__WRITE);
__IO_REG32(__BRDCNT1,0x03ffe018,__WRITE);
__IO_REG32(__BRDCLK0,0x03ffd01c,__WRITE);
__IO_REG32(__BRDCLK1,0x03ffe01c,__WRITE);


/***************************************************************************
 **
 **  Timer Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__TMOD,0x03ff6000,__READ_WRITE,__tmod_bits);
__IO_REG32_BIT(__TDATA0,0x03ff6004,__READ_WRITE,__tdata_bits);
__IO_REG32_BIT(__TDATA1,0x03ff6008,__READ_WRITE,__tdata_bits);
__IO_REG32_BIT(__TCNT0,0x03ff600c,__READ_WRITE,__tcnt_bits);
__IO_REG32_BIT(__TCNT1,0x03ff6010,__READ_WRITE,__tcnt_bits);

/***************************************************************************
 **
 **  I/O Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__IOPMOD,0x03ff5000,__READ_WRITE,__iopmod_bits);
__IO_REG32_BIT(__IOPCON,0x03ff5004,__READ_WRITE,__iopcon_bits);
__IO_REG32_BIT(__IOPDATA,0x03ff5008,__READ_WRITE,__iopdata_bits);

/***************************************************************************
 **
 **  Interrupt controller Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTMOD,0x03ff4000,__READ_WRITE,__intmodpnd_bits);
__IO_REG32_BIT(__INTPND,0x03ff4004,__READ_WRITE,__intmodpnd_bits);
__IO_REG32_BIT(__INTMSK,0x03ff4008,__READ_WRITE,__intmsk_bits);
__IO_REG32_BIT(__INTPRI0,0x03ff400c,__READ_WRITE,__intpri0_bits);
__IO_REG32_BIT(__INTPRI1,0x03ff4010,__READ_WRITE,__intpri1_bits);
__IO_REG32_BIT(__INTPRI2,0x03ff4014,__READ_WRITE,__intpri2_bits);
__IO_REG32_BIT(__INTPRI3,0x03ff4018,__READ_WRITE,__intpri3_bits);
__IO_REG32_BIT(__INTPRI4,0x03ff401c,__READ_WRITE,__intpri4_bits);
__IO_REG32_BIT(__INTPRI5,0x03ff4020,__READ_WRITE,__intpri5_bits);
__IO_REG32(__INTOFFSET,0x03ff4024,__READ);
__IO_REG32(__INTOSET_FIQ,0x03ff4030,__READ);
__IO_REG32(__INTOSET_IRQ,0x03ff4034,__READ);
__IO_REG32(__INTPNDPRI,0x03ff4028,__READ);
__IO_REG32(__INTPNDTST,0x03ff402c,__WRITE);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3C4510B interrupt sources
 **
 ***************************************************************************/
#define EXT0      0  /* external interrupt 0             */
#define EXT1      1  /* external interrupt 1             */
#define EXT2      2  /* external interrupt 2             */
#define EXT3      3  /* external interrupt 3             */
#define U0TINT    4  /* uart0 transmit interrupt         */
#define U0RERR    5  /* uart0 receive & error interrupt  */
#define U1T       6  /* uart1 transmit interrupt         */
#define U1RERR    7  /* uart1 receive & error interrupt  */
#define GDMA0     8  /* GDMA channel 0 interrupt         */
#define GDMA1     9  /* GDMA channel 1 interrupt         */
#define TIMER0   10  /* timer 0 interrupt                */
#define TIMER1   11  /* timer 1 interrupt                */
#define HDLCTXA  12  /* HDLC channel A TX interrupt      */
#define HDLCRXA  13  /* HDLC channel A Rx interrupt      */
#define HDLCTXB  14  /* HDLC channel B TX interrupt      */
#define HDLCRXB  15  /* HDLC channel B Rx interrupt      */
#define ECBDMATx 16  /* Eternet controller BDMA Tx intrrupt*/
#define ECBDMARx 17  /* Eternet controller BDMA Rx intrrupt*/
#define ECMACTx  18  /* Eternet controller BDMA Tx intrrupt*/
#define ECMACRx  19  /* Eternet controller BDMA Rx intrrupt*/
#define i2cbus   20  /* i2 C-bus interrupt                 */



#endif    /* __S3C4510B_H */
