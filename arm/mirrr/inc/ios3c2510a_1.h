/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C2510A
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1.2.3 $
 **
 ***************************************************************************/

#ifndef __S3C2510A_H
#define __S3C2510A_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C2510A SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* SYSTEM CONFIGURATION REGISTER (SYSCFG) */
typedef struct {
  __REG32 ARB           :2;
  __REG32               :2;
  __REG32 HCLKO_DIS     :1;
  __REG32               :3;
  __REG32 REMAP         :1;
  __REG32               :7;
  __REG32 BIG           :1;
  __REG32               :7;
  __REG32 PPLLFD        :1;
  __REG32 UPLLFD        :1;
  __REG32 SPLLFD        :1;
  __REG32 CPLLFD        :1;
  __REG32 PPLLREN       :1;
  __REG32 UPLLREN       :1;
  __REG32 SPLLREN       :1;
  __REG32 CPLLREN       :1;
} __syscfg_bits;

/* PRODUCT CODE AND REVISION NUMBER REGISTER (PDCODE) */
typedef struct {
  __REG32 MINREV        :4;
  __REG32 MAJREV        :4;
  __REG32               :8;
  __REG32 PC            :16;
} __pdcode_bits;

/* MISCELLANESOUS REGISTER (MISCREG) */
typedef struct {
  __REG32 OUT_DATA_SWAP     :1;
  __REG32 OUT_EDTD_SWAP     :1;
  __REG32 IN_DATA_SWAP      :1;
  __REG32 IN_EDTD_SWAP      :1;
  __REG32                   :11;
  __REG32 MISALIGN          :1;
  __REG32                   :16;
} __miscreg_bits;

/* PERIPHERAL CLOCK DISABLE REGISTER (PCLKDIS) */
typedef struct {
  __REG32 GDMA0         :1;
  __REG32 GDMA1         :1;
  __REG32 GDMA2         :1;
  __REG32 GDMA3         :1;
  __REG32 GDMA4         :1;
  __REG32 GDMA5         :1;
  __REG32 ETHERC0       :1;
  __REG32 ETHERC1       :1;
  __REG32 USB_DEVICE    :1;
  __REG32 CUART         :1;
  __REG32 HUART0        :1;
  __REG32 HUART1        :1;
  __REG32 TIMER0        :1;
  __REG32 TIMER1        :1;
  __REG32 TIMER2        :1;
  __REG32 TIMER3        :1;
  __REG32 TIMER4        :1;
  __REG32 TIMER5        :1;
  __REG32 WDT           :1;
  __REG32 IOPC          :1;
  __REG32 IICC          :1;
  __REG32 DES           :1;
  __REG32 MEMCON        :1;
  __REG32 SDRAMC        :1;
  __REG32 USB_HOST      :1;
  __REG32 PCI_PC_CARD   :1;
  __REG32 SAR           :1;
  __REG32               :3;
  __REG32 SRack         :1;
  __REG32 SRreq         :1;
} __pclkdis_bits;

/* CLOCK STATUS REGISTER (CLKST) */
typedef struct {
  __REG32 CPU_FREQ      :12;
  __REG32 BUS_FREQ      :12;
  __REG32               :6;
  __REG32 CLOCK_MODE    :2;
} __clkst_bits;

/* CORE PLL CONTROL REGISTER (CPLLCON) */
typedef struct {
  __REG32 M     :8;
  __REG32 P     :6;
  __REG32       :2;
  __REG32 S     :2;
  __REG32       :14;
} __cpllcon_bits;

/* Bank n Control (BnCON) Register Configuration */
typedef struct {
    __REG32 TCOH    :4;
    __REG32 TCOS    :4;
    __REG32 TACS    :4;
    __REG32 TPA     :4;
    __REG32 TACC    :5;
    __REG32         :2;
    __REG32 IS      :1;
    __REG32 BS      :4;
    __REG32 PMC     :2;
    __REG32 DW      :2;
} __bncon_bits;

/* Muxed Bus Control Register */
typedef struct {
  __REG32 TMA0   :3;
  __REG32 TMA1   :3;
  __REG32 TMA2   :3;
  __REG32 TMA3   :3;
  __REG32 TMA4   :3;
  __REG32 TMA5   :3;
  __REG32 TMA6   :3;
  __REG32 TMA7   :3;
  __REG32 MBE0   :1;
  __REG32 MBE1   :1;
  __REG32 MBE2   :1;
  __REG32 MBE3   :1;
  __REG32 MBE4   :1;
  __REG32 MBE5   :1;
  __REG32 MBE6   :1;
  __REG32 MBE7   :1;
} __muxbcon_bits;

/* WAIT Control Register */
typedef struct {
  __REG32 NREADY0   :1;
  __REG32 NREADY1   :1;
  __REG32 NREADY2   :1;
  __REG32 NREADY3   :1;
  __REG32 NREADY4   :1;
  __REG32 NREADY5   :1;
  __REG32 NREADY6   :1;
  __REG32 NREADY7   :1;
  __REG32 EWAITEN0  :1;
  __REG32 EWAITEN1  :1;
  __REG32 EWAITEN2  :1;
  __REG32 EWAITEN3  :1;
  __REG32 EWAITEN4  :1;
  __REG32 EWAITEN5  :1;
  __REG32 EWAITEN6  :1;
  __REG32 EWAITEN7  :1;
  __REG32 COHDIS0   :1;
  __REG32 COHDIS1   :1;
  __REG32 COHDIS2   :1;
  __REG32 COHDIS3   :1;
  __REG32 COHDIS4   :1;
  __REG32 COHDIS5   :1;
  __REG32 COHDIS6   :1;
  __REG32 COHDIS7   :1;
  __REG32           :8;
} __waitcon_bits;

/* WAIT data setup cycle Control Register */
typedef struct {
  __REG32 WDSC0   :4;
  __REG32 WDSC1   :4;
  __REG32 WDSC2   :4;
  __REG32 WDSC3   :4;
  __REG32 WDSC4   :4;
  __REG32 WDSC5   :4;
  __REG32 WDSC6   :4;
  __REG32 WDSC7   :4;
} __wdscon_bits;

/* SDRAM Configuration Register */
typedef struct {
  __REG32 XW    :1;
  __REG32 AP    :1;
  __REG32 CL    :2;
  __REG32 D1    :2;
  __REG32 D0    :2;
  __REG32 RP    :2;
  __REG32 RCD   :2;
  __REG32 RC    :4;
  __REG32 RAS   :4;
  __REG32       :12;
} __cfgreg_bits;

/* SDRAM Command Register */
typedef struct {
  __REG32 INIT  :2;
  __REG32 WBUF  :1;
  __REG32 BUSY  :1;
  __REG32       :28;
} __cmdreg_bits;

/* SDRAM Refresh Timer Register */
typedef struct {
  __REG32 REFCYC  :16;
  __REG32         :16;
} __refreg_bits;

/* SDRAM Write Buffer Time-out Register */
typedef struct {
  __REG32 WBTO :16;
  __REG32      :16;
} __wbtoreg_bits;

/* CONTROL STATUS REGISTER (IICCON) */
typedef struct {
  __REG32 BF    :1;
  __REG32 IEN   :1;
  __REG32 LRB   :1;
  __REG32 ACK   :1;
  __REG32 COND0 :1;
  __REG32 COND1 :1;
  __REG32 BUSY  :1;
  __REG32 RESET :1;
  __REG32       :24;
} __iiccon_bits;

/* SHIFT BUFFER REGISTER (IICBUF) */
typedef struct {
  __REG32 DATA :8;
  __REG32      :24;
} __iicbuf_bits;

/* PRESCALER REGISTER (IICPS) */
typedef struct {
  __REG32 PRESCALER_VALUE   :16;
  __REG32                   :16;
} __iicps_bits;

/* PRESCALER COUNTER REGISTER (IICCNT) */
typedef struct {
  __REG32 COUNTER_VALUE   :16;
  __REG32                 :16;
} __iiccnt_bits;

/* EINTERRUPT PENDING REGISTER (IICPND) */
typedef struct {
  __REG32 INTPEND   :1;
  __REG32           :31;
} __iicpnd_bits;

/* BDMA Transmit Control Register */
typedef struct {
  __REG32 BTXNBD    :4;
  __REG32 BTXMSL    :3;
  __REG32 BTXBSWAP  :1;
  __REG32 TEST_EN   :1;
  __REG32           :1;
  __REG32 BTXEN     :1;
  __REG32 BTXRS     :1;
  __REG32           :20;
} __bdmatxcon_bits;

/* BDMA Receive Control Register */
typedef struct {
  __REG32 BRXNBD    :4;
  __REG32 BRXWA     :2;
  __REG32           :1;
  __REG32 BRXBSWAP  :1;
  __REG32 TEST_EN   :1;
  __REG32           :1;
  __REG32 BRXEN     :1;
  __REG32 BRXRS     :1;
  __REG32           :20;
} __bdmarxcon_bits;

/* BDMA Transmit Buffer descriptor Counter */
typedef struct {
  __REG32 TXBDCNT   :12;
  __REG32           :20;
} __btxbdcnt_bits;

/* BDMA Receive Buffer descriptor Counter */
typedef struct {
  __REG32 RXBDCNT   :12;
  __REG32           :20;
} __brxbdcnt_bits;


/* BDMA/MAC Transmit Interrupt Enable Register */
typedef struct {
  __REG32 EXCOLLIE      :1;
  __REG32 UNDERFLOWIE   :1;
  __REG32 DEFERERRIE    :1;
  __REG32 NOCARRIE      :1;
  __REG32 LATECOLLIE    :1;
  __REG32 TXPARERRIE    :1;
  __REG32 TXCOMPIE      :1;
  __REG32               :9;
  __REG32 TXCFCOMPIE    :1;
  __REG32 BTXNOIE       :1;
  __REG32 BTXEMPTYIE    :1;
  __REG32               :13;
} __bmtxinten_bits;

/* BDMA/MAC Transmit Interrupt Status Register */
typedef struct {
  __REG32 EXCOLL      :1;
  __REG32 UNDERFLOW   :1;
  __REG32 DEFERERR    :1;
  __REG32 NOCARR      :1;
  __REG32 LATECOLL    :1;
  __REG32 TXPARERR    :1;
  __REG32 TXCOMP      :1;
  __REG32             :9;
  __REG32 TXCFCOMP    :1;
  __REG32 BTXNO       :1;
  __REG32 BTXEMPTY    :1;
  __REG32             :13;
} __bmtxstat_bits;

/* BDMA/MAC Receive Interrupt Enable Register */
typedef struct {
  __REG32 MISSROLLIE    :1;
  __REG32 ALIGNERRIE    :1;
  __REG32 CRCERRIE      :1;
  __REG32 OVERFLOWIE    :1;
  __REG32 LONGERRIE     :1;
  __REG32 RXPARERRIE    :1;
  __REG32               :1;
  __REG32               :9;
  __REG32 BRXDONEIE     :1;
  __REG32 BRXNOIE       :1;
  __REG32 BRXMSOIE      :1;
  __REG32 BRXFULLIE     :1;
  __REG32 BRXEARLYIE    :1;
  __REG32               :11;
} __bmrxinten_bits;

/* BDMA/MAC Receive Interrupt Status Register */
typedef struct {
  __REG32 MISSROLL    :1;
  __REG32 ALIGNERR    :1;
  __REG32 CRCERR      :1;
  __REG32 OVERFLOW    :1;
  __REG32 LONGERR     :1;
  __REG32 RXPARERR    :1;
  __REG32             :1;
  __REG32             :9;
  __REG32 BRXDONE     :1;
  __REG32 BRXNO       :1;
  __REG32 BRXMSO      :1;
  __REG32 BRXFULL     :1;
  __REG32 BRXEARLY    :1;
  __REG32 BRXFRF      :1;
  __REG32 BRXNFR      :5;
  __REG32             :5;
} __bmrxstat_bits;

/* BDMA Receive Frame Size Register */
typedef struct {
  __REG32 BRXBS     :12;
  __REG32           :4;
  __REG32 BRXMFS    :12;
  __REG32           :4;
} __bdmarxlen_bits;

/* Transmit Control Frame Register */
typedef struct {
  __REG32 MACTXSTAT :16;
  __REG32           :16;
} __cftxstat_bits;

/* MAC Control Register */
typedef struct {
  __REG32 MHALTREQ      :1;
  __REG32 MHALTIMM      :1;
  __REG32 MRESET        :1;
  __REG32 FULL_DUPLEX   :1;
  __REG32 MLOOPBACK     :1;
  __REG32               :1;
  __REG32 MII_OFF       :1;
  __REG32 MLOOP10       :1;
  __REG32               :4;
  __REG32 MDC_OFF       :1;
  __REG32               :2;
  __REG32 MLINK10       :1;
  __REG32               :16;
} __maccon_bits;

/* CAM Control Register  */
typedef struct {
  __REG32 MSTATION  :1;
  __REG32 MGROUP    :1;
  __REG32 MBROAD    :1;
  __REG32 MNEGCAM   :1;
  __REG32 MCOMPEN   :1;
  __REG32           :27;
} __camcon_bits;

/* MAC Transmit Control Register */
typedef struct {
  __REG32 MTXEN     :1;
  __REG32 MTXHALT   :1;
  __REG32 MNOPAD    :1;
  __REG32 MNOCRC    :1;
  __REG32 MFBACK    :1;
  __REG32 MNODEF    :1;
  __REG32 MSDPAUSE  :1;
  __REG32 MSQEN     :1;
  __REG32           :24;
} __mactxcon_bits;

/* MAC Transmit Status Register */
typedef struct {
  __REG32           :8;
  __REG32 MCOLLCNT  :4;
  __REG32 MTXDEFER  :1;
  __REG32 SQEERR    :1;
  __REG32 MTXHALTED :1;
  __REG32 MPAUSED   :1;
  __REG32           :16;
} __mactxstat_bits;

/* MAC Receive Control Register */
typedef struct {
  __REG32 MRXEN       :1;
  __REG32 MRXHALT     :1;
  __REG32 MLONGEN     :1;
  __REG32 MSHORTEN    :1;
  __REG32 MSTRIPCRC   :1;
  __REG32 MPASSCTL    :1;
  __REG32 MIGNORECRC  :1;
  __REG32             :25;
} __macrxcon_bits;

/* MAC Receive Status Register */
typedef struct {
  __REG32           :8;
  __REG32 MRXSHORT  :1;
  __REG32 MRX10STAT :1;
  __REG32 MRXHALTED :1;
  __REG32 MCTLRECD  :1;
  __REG32           :20;
} __macrxstat_bits;

/* Station Management Register */
typedef struct {
  __REG32 DATA  :16;
  __REG32       :16;
} __stadata_bits;

/* STACON Register */
typedef struct {
  __REG32 MPHYREGADDR  :5;
  __REG32 MPHYADDR     :5;
  __REG32 MPHYWRITE    :1;
  __REG32 MPHYBUSY     :1;
  __REG32              :1;
  __REG32 MMDCRATE     :4;
  __REG32              :15;
} __stacon_bits;

/*  */
typedef struct {
  __REG32 CAM_ENABLE :21;
  __REG32            :11;
} __camen_bits;

/* Missed Error Count Register */
typedef struct {
  __REG32 MISSERRCNT :16;
  __REG32            :16;
} __misscnt_bits;

/* Received Pause Count Register */
typedef struct {
  __REG32  PZCNTRX  :16;
  __REG32           :16;
} __pzcnt_bits;

/* Remote Pause Count Register */
typedef struct {
  __REG32 RMPZCNT   :16;
  __REG32           :16;
} __rmpzcnt_bits;

/* SW_RESET */
typedef struct {
  __REG32  SW_RESET :1;
  __REG32           :31;
} __sw_reset_bits;

/* SAR_DB_ID */
typedef struct {
  __REG32 REVISION      :8;
  __REG32 SAR_DB_DATE   :24;
} __sar_db_id_bits;

/* GLOBAL_MODE */
typedef struct {
  __REG32                       :23;
  __REG32 RX_TIMEOUT_EN         :1;
  __REG32                       :2;
  __REG32 CAM_ENABLE            :1;
  __REG32 LOC_LOOPBACK          :1;
  __REG32 REM_LOOPBACK          :1;
  __REG32 REASS_FAST_FORWARD    :1;
  __REG32 RX_GLOBAL_ENABLE      :1;
  __REG32 TX_GLOBAL_ENABLE      :1;
} __global_mode_bits;

/* TIMEOUT_BASE */
typedef struct {
  __REG32 TIMEOUT_BASE  :15;
  __REG32               :17;
} __timeout_base_bits;

/* TX_READY1 */
typedef struct {
  __REG32 FIRST_DESC_ADDRESS :31;
  __REG32 READY_DONE_BAR     :1;
} __tx_ready1_bits;

/* TX_READY2 */
typedef struct {
  __REG32 LAST_DESC_ADDRES  :31;
  __REG32 TX_READY2         :1;
} __tx_ready2_bits;

/* TX_DONE_ADDR */
typedef struct {
  __REG32 ADDRESS   :31;
  __REG32 VALID     :1;
} __tx_done_addr_bits;

/* TX_DONE_SIZE */
typedef struct {
  __REG32 OFFSET    :16;
  __REG32           :4;
  __REG32 Q_SIZE    :4;
  __REG32           :8;
} __tx_done_size_bits;

/* RX_POOLn_ADDR (n = 0, 1, 2, 3) (0xF012_0020 + 4*2n) */
typedef struct {
  __REG32 ADDRESS   :31;
  __REG32 VALID     :1;
} __rx_pooln_addr_bits;

/* RX_POOLn_SIZE (n = 0, 1, 2, 3) (0xF012_0020 + 4*(2n+1))*/
typedef struct {
  __REG32 OFFSET    :16;
  __REG32           :4;
  __REG32 Q_SIZE    :4;
  __REG32 BUFF_SIZE :4;
  __REG32           :4;
} __rx_pooln_size_bits;

/* RX_DONEn_ADDR (n = 0, 1) (0xF012_0040 + 4*2n) */
typedef struct {
  __REG32 ADDRESS   :31;
  __REG32 VALID     :1;
} __rx_donen_addr_bits;

/* RX_DONEn_SIZE (n = 0, 1) (0xF012_0040 + 4*(2n+1)) */
typedef struct {
  __REG32 OFFSET    :16;
  __REG32           :4;
  __REG32 Q_SIZE    :4;
  __REG32           :8;
} __rx_donen_size_bits;

/* UTOPIA_CONFIG */
typedef struct {
  __REG32                       :20;
  __REG32 TX_DISCARD_TIMER_EN   :1;
  __REG32 TX_CLAV_TIMEOUT_EN    :1;
  __REG32 UTOPIA_OUT_DELAY      :2;
  __REG32                       :1;
  __REG32 UTOPIA_ADDR_LMT       :3;
  __REG32                       :2;
  __REG32 UTOPIA_MODE           :1;
  __REG32 UTOPIA_ENABLE         :1;
} __utopia_config_bits;

/* UTOPIA_TIMEOUT */
typedef struct {
  __REG32 TX_DISCARD_TIMEOUT    :16;
  __REG32 TX_CLAV_TIMEOUT       :16;
} __utopia_timeout_bits;

/* CLOCK_RATIO */
typedef struct {
  __REG32 CLOCK_RATIO :16;
  __REG32             :16;
} __clock_ratio_bits;

/* DONE_INT_MASK */
typedef struct {
  __REG32 RX_DONE1_MASK     :1;
  __REG32 RX_DONE0_MASK     :1;
  __REG32 TX_DONE_INTR_MASK :1;
  __REG32 RX_INTR1_MASK     :1;
  __REG32 RX_INTR0_MASK     :1;
  __REG32                   :27;
} __done_int_mask_bits;

/* ERR_INT_MASK */
typedef struct {
  __REG32                       :12;
  __REG32 TX_DISCARD_MASK       :1;
  __REG32 TX_CLAV_MASK          :1;
  __REG32 RX_INACT_VC_MASK      :1;
  __REG32 SEGQ_ERR_MASK         :1;
  __REG32 REASSQ_ERR_MASK       :1;
  __REG32 REASS_BUFF_ERR_MASK   :1;
  __REG32 RX_POOL3_WARN_MASK    :1;
  __REG32 RX_POOL2_WARN_MASK    :1;
  __REG32 RX_POOL1_WARN_MASK    :1;
  __REG32 RX_POOL0_WARN_MASK    :1;
  __REG32                       :10;
} __err_int_mask_bits;

/* DONE_INT_STATUS */
typedef struct {
  __REG32 RX_DONE1      :1;
  __REG32 RX_DONE0      :1;
  __REG32 TX_DONE_INTR  :1;
  __REG32 RX_ON_DONE_Q1 :1;
  __REG32 RX_ON_DONE_Q0 :1;
  __REG32               :27;
} __done_int_status_bits;

/* ERR_INT_STATUS */
typedef struct {
  __REG32 RX_CONN               :12;
  __REG32 TX_DISCARD_INTR       :1;
  __REG32 TX_CLAV_INTR          :1;
  __REG32 RX_INACT_VC           :1;
  __REG32 SEG_QUEUE_ERR         :1;
  __REG32 REASS_QUEUE_ERR       :1;
  __REG32 REASS_BUFF_ERR        :1;
  __REG32 RX_POOL3_WARN_INTR    :1;
  __REG32 RX_POOL2_WARN_INTR    :1;
  __REG32 RX_POOL1_WARN_INTR    :1;
  __REG32 RX_POOL0_WARN_INTR    :1;
  __REG32 TX_DISCARD_ADDR       :3;
  __REG32 TIMEOUT_TX_CLAV       :7;
} __err_int_status_bits;

/* 1/RATE_LOOKUP_TBL */
typedef struct {
  __REG32                       :12;
  __REG32 RATE_LOOKUP_TBL_BASE  :18;
  __REG32                       :2;
} __rate_lookup_tbl_bits;

/* VP_LOOKUP_TBL */
typedef struct {
  __REG32                    :12;
  __REG32 VP_LOOKUP_TBL_BASE :18;
  __REG32                    :2;
} __vp_lookup_tbl_bits;

/* UBR_SCH_TBL */
typedef struct {
  __REG32 UBR_SCH_TBL_SIZE :12;
  __REG32 UBR_SCH_TBL_BASE :18;
  __REG32                  :2;
} __ubr_sch_tbl_bits;

/* CBR_SCH_TBL */
typedef struct {
  __REG32 CBR_SCH_TBL_SIZE :12;
  __REG32 CBR_SCH_TBL_BASE :18;
  __REG32                  :2;
} __cbr_sch_tbl_bits;

/* CELL_BUFF */
typedef struct {
  __REG32 CELL_BUFF_SIZE :12;
  __REG32 CELL_BUFF_BASE :18;
  __REG32                :2;
} __cell_buff_bits;

/* SCH_CONN_TBL */
typedef struct {
  __REG32 SCH_CONN_TBL_SIZE :12;
  __REG32 SCH_CONN_TBL_BASE :18;
  __REG32                   :2;
} __sch_conn_tbl_bits;

/* AAL_CONN_TBL */
typedef struct {
  __REG32 AAL_SAR_CONN_TBL_SIZE :12;
  __REG32 AAL_CONN_TBL_BASE     :18;
  __REG32                       :2;
} __aal_conn_tbl_bits;

/* SAR_CONN_TBL */
typedef struct {
  __REG32                   :12;
  __REG32 SAR_CONN_TBL_BASE :18;
  __REG32                   :2;
} __sar_conn_tbl_bits;

/* CAM_VPIVCIn */
typedef struct {
  __REG32 VCI       :16;
  __REG32 VPI       :8;
  __REG32 PHY_PORT  :3;
  __REG32           :3;
  __REG32 VC_Vpbar  :1;
  __REG32 ACTIVE    :1;
} __cam_vpivcin_bits;

/* CAM_CNn */
typedef struct {
  __REG32 AAL_SAR_CON :5;
  __REG32             :7;
  __REG32 SCHED_CON   :5;
  __REG32             :15;
} __cam_cnn_bits;

/* CONFIGURATION */
typedef struct {
  __REG32 EXT_ONLY      :1;
  __REG32 BIG_ENDIAN    :1;
  __REG32 SAR_CLK_SEL   :3;
  __REG32 UTO_CLK_SEL   :3;
  __REG32               :24;
} __configuration_bits;

/* EXT_CMBASE */
typedef struct {
  __REG32 CM_BASE   :15;
  __REG32           :17;
} __ext_cmbase_bits;

/* HcRevision Register */
typedef struct {
  __REG32 REV               : 8;
  __REG32                   :24;
} __hcrevision_bits;

/* HcControl Register */
typedef struct {
  __REG32 CBSR              : 2;
  __REG32 PLE               : 1;
  __REG32 IE                : 1;
  __REG32 CLE               : 1;
  __REG32 BLE               : 1;
  __REG32 HCFS              : 2;
  __REG32 IR                : 1;
  __REG32 WC                : 1;
  __REG32 RWE               : 1;
  __REG32                   :21;
} __hccontrol_bits;

/* HcCommandStatus Register */
typedef struct {
  __REG32 HCR               : 1;
  __REG32 CLF               : 1;
  __REG32 BLF               : 1;
  __REG32 OCR               : 1;
  __REG32                   :12;
  __REG32 SOC               : 2;
  __REG32                   :14;
} __hccommandstatus_bits;

/* HcInterruptStatus Register */
typedef struct {
  __REG32 SO                : 1;
  __REG32 WDH               : 1;
  __REG32 SF                : 1;
  __REG32 RD                : 1;
  __REG32 UE                : 1;
  __REG32 FNO               : 1;
  __REG32 RHSC              : 1;
  __REG32                   :23;
  __REG32 OC                : 1;
  __REG32                   : 1;
} __hcinterruptstatus_bits;

/* HcInterruptEnable Register
   HcInterruptDisable Register */
typedef struct {
  __REG32 SO                : 1;
  __REG32 WDH               : 1;
  __REG32 SF                : 1;
  __REG32 RD                : 1;
  __REG32 UE                : 1;
  __REG32 FNO               : 1;
  __REG32 RHSC              : 1;
  __REG32                   :23;
  __REG32 OC                : 1;
  __REG32 MIE               : 1;
} __hcinterruptenable_bits;

/* HcHCCA Register */
typedef struct {
  __REG32                   : 8;
  __REG32 HCCA              :24;
} __hchcca_bits;

/* HcPeriodCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 PCED              :28;
} __hcperiodcurrented_bits;

/* HcControlHeadED Registerr */
typedef struct {
  __REG32                   : 4;
  __REG32 CHED              :28;
} __hccontrolheaded_bits;

/* HcControlCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 CCED              :28;
} __hccontrolcurrented_bits;

/* HcBulkHeadED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 BHED              :28;
} __hcbulkheaded_bits;

/* HcBulkCurrentED Register */
typedef struct {
  __REG32                   : 4;
  __REG32 BCED              :28;
} __hcbulkcurrented_bits;

/* HcDoneHead Register */
typedef struct {
  __REG32                   : 4;
  __REG32 DH                :28;
} __hcdonehead_bits;

/* HcFmInterval Register */
typedef struct {
  __REG32 FI                :14;
  __REG32                   : 2;
  __REG32 FSMPS             :15;
  __REG32 FIT               : 1;
} __hcfminterval_bits;

/* HcFmRemaining Register */
typedef struct {
  __REG32 FR                :14;
  __REG32                   :17;
  __REG32 FRT               : 1;
} __hcfmremaining_bits;

/* HcPeriodicStart Register */
typedef struct {
  __REG32 PS                :14;
  __REG32                   :18;
} __hcperiodicstart_bits;

/* HcLSThreshold Register */
typedef struct {
  __REG32 LST               :12;
  __REG32                   :20;
} __hclsthreshold_bits;

/* HcRhDescriptorA Register */
typedef struct {
  __REG32 NDP               : 8;
  __REG32 PSM               : 1;
  __REG32 NPS               : 1;
  __REG32 DT                : 1;
  __REG32 OCPM              : 1;
  __REG32 NOCP              : 1;
  __REG32                   :11;
  __REG32 POTPGT            : 8;
} __hcrhdescriptora_bits;

/* HcRhDescriptorB Register */
typedef struct {
  __REG32                   : 1;
  __REG32 DR                : 1;
  __REG32                   :15;
  __REG32 PPCM              : 1;
  __REG32                   :14;
} __hcrhdescriptorb_bits;

/* HcRhStatus Register */
typedef struct {
  __REG32 LPS               : 1;
  __REG32 OCI               : 1;
  __REG32                   :13;
  __REG32 DRWE              : 1;
  __REG32 LPSC              : 1;
  __REG32 CCIC              : 1;
  __REG32                   :13;
  __REG32 CRWE              : 1;
} __hcrhstatus_bits;

/* HcRhPortStatus Register */
typedef struct {
  __REG32 CCS               : 1;
  __REG32 PES               : 1;
  __REG32 PSS               : 1;
  __REG32 POCI              : 1;
  __REG32 PRS               : 1;
  __REG32                   : 3;
  __REG32 PPS               : 1;
  __REG32 LSDA              : 1;
  __REG32                   : 6;
  __REG32 CSC               : 1;
  __REG32 PESC              : 1;
  __REG32 PSSC              : 1;
  __REG32 OCIC              : 1;
  __REG32 PRSC              : 1;
  __REG32                   :11;
} __hcrhportstatus_bits;

/* USB FUNCTION ADDRESS REGISTER */
typedef struct {
  __REG32 USBFAF :7;
  __REG32 USBAUP :1;
  __REG32        :24;
} __usbfa_bits;

/* USB POWER MANAGEMENT REGISTER */
typedef struct {
  __REG32 SUSE          :1;
  __REG32 SUSM          :1;
  __REG32 RU            :1;
  __REG32 RST           :1;
  __REG32 TX_DATA_SWAP  :1;
  __REG32 RX_DATA_SWAP  :1;
  __REG32               :1;
  __REG32 ISOU          :1;
  __REG32               :24;
} __usbpm_bits;

/* USB INTERRUPT REGISTER */
typedef struct {
  __REG32 EP0I  :1;
  __REG32 EP1I  :1;
  __REG32 EP2I  :1;
  __REG32 EP3I  :1;
  __REG32 EP4I  :1;
  __REG32       :3;
  __REG32 SUSI  :1;
  __REG32 RESI  :1;
  __REG32 RSTI  :1;
  __REG32 DISCI :1;
  __REG32       :20;
} __usbintr_bits;

/* USB INTERRUPT ENABLE REGISTER */
typedef struct {
  __REG32 EP0IEN  :1;
  __REG32 EP1IEN  :1;
  __REG32 EP2IEN  :1;
  __REG32 EP3IEN  :1;
  __REG32 EP4IEN  :1;
  __REG32         :3;
  __REG32 SUSIEN  :1;
  __REG32         :1;
  __REG32 RSTIEN  :1;
  __REG32 DISCIEN :1;
  __REG32         :20;
} __usbintre_bits;

/* USB FRAME NUMBER REGISTER */
typedef struct {
  __REG32 FN    :11;
  __REG32       :21;
} __usbfn_bits;

/* USB DISCONNECT TIMER REGISTER */
typedef struct {
  __REG32 CNTVLE  :23;
  __REG32         :8;
  __REG32 DISSTRT :1;
} __usbdisconn_bits;

/* USB ENDPOINT 0 COMMON STATUS REGISTER */
typedef struct {
  __REG32 MAXP      :4;
  __REG32           :3;
  __REG32 MAXPSET   :1;
  __REG32           :16;
  __REG32 ORDY      :1;
  __REG32 INRDY     :1;
  __REG32 STSTALL   :1;
  __REG32 DEND      :1;
  __REG32 SETEND    :1;
  __REG32 SDSTALL   :1;
  __REG32 SVORDY    :1;
  __REG32 SVSET     :1;
} __usbep0csr_bits;

/* USB ENDPOINT 1 COMMON STATUS REGISTER */
typedef struct {
  __REG32 MAXP      :3;
  __REG32           :4;
  __REG32 MAXPSET   :1;
  __REG32 OISO      :1;
  __REG32 OATCLR    :1;
  __REG32 MODE      :1;
  __REG32 IISO      :1;
  __REG32 IATSET    :1;
  __REG32           :2;
  __REG32 CSR2SET   :1;
  __REG32 OORDY     :1;
  __REG32 OFFULL    :1;
  __REG32 OOVER     :1;
  __REG32 ODERR     :1;
  __REG32 OFFLUSH   :1;
  __REG32 OSDSTALL  :1;
  __REG32 OSTSTALL  :1;
  __REG32 OCLTOG    :1;
  __REG32 IINRDY    :1;
  __REG32 INEMP     :1;
  __REG32 IUNDER    :1;
  __REG32 IFFLUSH   :1;
  __REG32 ISDSTALL  :1;
  __REG32 ISTSTALL  :1;
  __REG32 ICLTOG    :1;
  __REG32           :1;
} __usbep1csr_bits;

/* USB ENDPOINT 3 COMMON STATUS REGISTER */
typedef struct {
  __REG32 MAXP_SIZE :4;
  __REG32           :3;
  __REG32 MAXPSET   :1;
  __REG32 OISO      :1;
  __REG32 OATCLR    :1;
  __REG32 MODE      :1;
  __REG32 IISO      :1;
  __REG32 IATSET    :1;
  __REG32           :2;
  __REG32 CSR2SET   :1;
  __REG32 OORDY     :1;
  __REG32 OFFULL    :1;
  __REG32 OOVER     :1;
  __REG32 ODERR     :1;
  __REG32 OFFLUSH   :1;
  __REG32 OSDSTALL  :1;
  __REG32 OSTSTALL  :1;
  __REG32 OCLTOG    :1;
  __REG32 IINRDY    :1;
  __REG32 INEMP     :1;
  __REG32 IUNDER    :1;
  __REG32 IFFLUSH   :1;
  __REG32 ISDSTALL  :1;
  __REG32 ISTSTALL  :1;
  __REG32 ICLTOG    :1;
  __REG32           :1;
} __usbep3csr_bits;

/* USB WRITE COUNT FOR ENDPOINT 0 REGISTER */
typedef struct {
  __REG32 CPUWRTCNT :7;
  __REG32           :9;
  __REG32 WRTCNT    :7;
  __REG32           :9;
} __usbwcep0_bits;

/* USB WRITE COUNT FOR ENDPOINT 1 REGISTER */
typedef struct {
  __REG32 CPUWRTCNT :6;
  __REG32           :10;
  __REG32 WRTCNT    :6;
  __REG32           :10;
} __usbwcep1_bits;

/* USB WRITE COUNT FOR ENDPOINT 2 REGISTER */
typedef struct {
  __REG32 CPUWRTCNT  :6;
  __REG32            :10;
  __REG32 WRTCNT     :6;
  __REG32            :10;
} __usbwcep2_bits;

/* USB WRITE COUNT FOR ENDPOINT 3 REGISTER */
typedef struct {
  __REG32 CPUWRTCNT :7;
  __REG32           :9;
  __REG32 WRTCNT    :7;
  __REG32           :9;
} __usbwcep3_bits;

/* USB WRITE COUNT FOR ENDPOINT 4 REGISTER */
typedef struct {
  __REG32 CPUWRTCNT :7;
  __REG32  :9;
  __REG32 WRTCNT :7;
  __REG32  :9;
} __usbwcep4_bits;

/* DES/3DES CONTROL REGISTER */
typedef struct {
  __REG32 RUN_ENABLE        :1;
  __REG32 INDATA_DMA        :1;
  __REG32 OUTDATA_DMA       :1;
  __REG32 RIGHT_LEFT        :1;
  __REG32 ENC_DECR          :1;
  __REG32 DES_3DES          :1;
  __REG32 ECB_CBC           :1;
  __REG32 _2WORD_REQ        :1;
  __REG32 FIFO_TEST         :1;
  __REG32 FIFO_RESET        :1;
  __REG32 SWAPEN            :1;
  __REG32                   :21;
} __descon_bits;

/* DES/3DES STATUS REGISTER */
typedef struct {
  __REG32 IDLE                :1;
  __REG32                     :3;
  __REG32 AVAILABLE_DESINFIFO :1;
  __REG32 EMPTY_DESINFIFO     :1;
  __REG32 FULL_DESINFIFO      :1;
  __REG32                     :1;
  __REG32 VALID_DESOUTFIFO    :1;
  __REG32 EMPTY_DESOUTFIFO    :1;
  __REG32 FULL_DESOUTFIFO     :1;
  __REG32                     :21;
} __dessta_bits;

/* DES/3DES INTERRUPT ENABLE REGISTER */
typedef struct {
  __REG32 IDLE       :1;
  __REG32            :3;
  __REG32 DESINFIFO  :1;
  __REG32            :3;
  __REG32 DESOUTFIFO :1;
  __REG32            :23;
} __desint_bits;

/* DES/3DES RUN ENABLE REGISTER */
typedef struct {
  __REG32  RUN_ENABLE :1;
  __REG32             :31;
} __desrun_bits;

/* DPRIC */
typedef struct {
  __REG32 PRIOR_CONF :2;
  __REG32            :30;
} __dpric_bits;

/* DPRIF */
typedef struct {
  __REG32 DPRIF0 :4;
  __REG32 DPRIF1 :4;
  __REG32 DPRIF2 :4;
  __REG32 DPRIF3 :4;
  __REG32 DPRIF4 :4;
  __REG32 DPRIF5 :4;
  __REG32        :8;
} __dprif_bits;

/* DPRIR */
typedef struct {
  __REG32 DPRIR0 :4;
  __REG32 DPRIR1 :4;
  __REG32 DPRIR2 :4;
  __REG32 DPRIR3 :4;
  __REG32 DPRIR4 :4;
  __REG32 DPRIR5 :4;
  __REG32        :8;
} __dprir_bits;

/* DCON0/1/2/3/4/5 Registers */
typedef struct {
  __REG32 RE    :1;
  __REG32 MODE  :3;
  __REG32 SB    :1;
  __REG32 FB    :1;
  __REG32 TS    :2;
  __REG32 SD    :2;
  __REG32 DD    :2;
  __REG32 IE    :1;
  __REG32 XCNT  :4;
  __REG32       :14;
  __REG32  BS   :1;
} __dcon_bits;

/* GDMA TRANSFER COUNT REGISTERS DTCR0/1/2/3/4/5 */
typedef struct {
  __REG32  TCNT :24;
  __REG32       :8;
} __dtcr_bits;

/* GDMA RUN ENABLE REGISTERS DRER0/1/2/3/4/5 */
typedef struct {
  __REG32 RE :1;
  __REG32    :31;
} __drer_bits;

/* GDMA INTERRUPT PENDING REGISTER DIPR0/1/2/3 */
typedef struct {
  __REG32 IP :1;
  __REG32    :31;
} __dipr_bits;

/* CONSOLE UART CONTROL REGISTERS */
typedef struct {
  __REG32 TMODE     :2;
  __REG32 RMODE     :2;
  __REG32 SBR       :1;
  __REG32 SCSEL     :1;
  __REG32           :1;
  __REG32 LOOPB     :1;
  __REG32 PMD       :3;
  __REG32 STB       :1;
  __REG32 WL        :2;
  __REG32 IR        :1;
  __REG32           :14;
  __REG32 SFEN      :1;
  __REG32 ECHO      :1;
  __REG32           :1;
} __cucon_bits;

/* CONSOLE UART STATUS REGISTERS */
typedef struct {
  __REG32 RDV    :1;
  __REG32 BKD    :1;
  __REG32 FER    :1;
  __REG32 PER    :1;
  __REG32 OER    :1;
  __REG32 CCD    :1;
  __REG32        :5;
  __REG32 RXIDLE :1;
  __REG32        :5;
  __REG32 TI     :1;
  __REG32 THE    :1;
  __REG32        :13;
} __custat_bits;

/* CONSOLE UART INTERRUPT ENABLE REGISTER */
typedef struct {
  __REG32 RDVIE :1;
  __REG32 BKDIE :1;
  __REG32 FERIE :1;
  __REG32 PERIE :1;
  __REG32 OERIE :1;
  __REG32 CCDIE :1;
  __REG32       :11;
  __REG32 TIIE  :1;
  __REG32 THEIE :1;
  __REG32       :13;
} __cuint_bits;

/* UART BAUD RATE DIVISOR REGISTER */
typedef struct {
  __REG32 CNT1 :4;
  __REG32 CNT0 :12;
  __REG32      :16;
} __cubrd_bits;

/* UART CONTROL CHARACTER REGISTER 1 */
typedef struct {
  __REG32 CHAR0 :8;
  __REG32 CHAR1 :8;
  __REG32 CHAR2 :8;
  __REG32 CHAR3 :8;
} __cuchar1_bits;

/* UART CONTROL CHARACTER REGISTER 2 */
typedef struct {
  __REG32 CHAR4 :8;
  __REG32 CHAR5 :8;
  __REG32 CHAR6 :8;
  __REG32 CHAR7 :8;
} __cuchar2_bits;

/* HIGH-SPEED UART CONTROL REGISTERS */
typedef struct {
  __REG32 TMODE     :2;
  __REG32 RMODE     :2;
  __REG32 SBR       :1;
  __REG32 UCLK      :1;
  __REG32 AUBD      :1;
  __REG32 LOOPB     :1;
  __REG32 PMD       :3;
  __REG32 STB       :1;
  __REG32 WL        :2;
  __REG32 IR        :1;
  __REG32           :1;
  __REG32 TFEN      :1;
  __REG32 RFEN      :1;
  __REG32 TFRST     :1;
  __REG32 RFRST     :1;
  __REG32 TFTL      :2;
  __REG32 RFTL      :2;
  __REG32 DTR       :1;
  __REG32           :3;
  __REG32 HFEN      :1;
  __REG32 SFEN      :1;
  __REG32 ECHO      :1;
  __REG32 RTS_RTR   :1;
} __hucon_bits;

/* HIGH-SPEED  UART STATUS REGISTERS */
typedef struct {
  __REG32 RDV    :1;
  __REG32 BKD    :1;
  __REG32 FER    :1;
  __REG32 PER    :1;
  __REG32 OER    :1;
  __REG32 CCD    :1;
  __REG32 DCDL   :1;
  __REG32 RFREA  :1;
  __REG32 RFEMT  :1;
  __REG32 RFFUL  :1;
  __REG32 RFOV   :1;
  __REG32 RIDLE  :1;
  __REG32 E_RXTO :1;
  __REG32 AUBDDN :1;
  __REG32 DSR    :1;
  __REG32 CTS    :1;
  __REG32 E_CTS  :1;
  __REG32 TI     :1;
  __REG32 THE    :1;
  __REG32 TFEMT  :1;
  __REG32 TFFUL  :1;
  __REG32        :11;
} __hustat_bits;

/* HIGH-SPEED  UART INTERRUPT ENABLE REGISTER */
typedef struct {
  __REG32 RDVIE     :1;
  __REG32 BKDIE     :1;
  __REG32 FERIE     :1;
  __REG32 PERIE     :1;
  __REG32 OERIE     :1;
  __REG32 CCDIE     :1;
  __REG32 DCDLIE    :1;
  __REG32 RFREAIE   :1;
  __REG32           :2;
  __REG32 OVFFIE    :1;
  __REG32           :1;
  __REG32 E_RXTOIE  :1;
  __REG32 AUBDDNIE  :1;
  __REG32           :2;
  __REG32 E_CTSIE   :1;
  __REG32 TIIE      :1;
  __REG32 THEIE     :1;
  __REG32           :13;
} __huint_bits;

/* HIGH-SPEED UART BAUD RATE DIVISOR REGISTER */
typedef struct {
  __REG32 CNT1 :4;
  __REG32 CNT0 :12;
  __REG32      :16;
} __hubrd_bits;

/* HIGH-SPEED UART CONTROL CHARACTER REGISTER 1 */
typedef struct {
  __REG32 CHAR0 :8;
  __REG32 CHAR1 :8;
  __REG32 CHAR2 :8;
  __REG32 CHAR3 :8;
} __huchar1_bits;

/* HIGH-SPEED UART CONTROL CHARACTER REGISTER 2 */
typedef struct {
  __REG32 CHAR4 :8;
  __REG32 CHAR5 :8;
  __REG32 CHAR6 :8;
  __REG32 CHAR7 :8;
} __huchar2_bits;

/* High-Speed UART AutoBaud Boundary Registers */
typedef struct {
  __REG32 ABB0 :8;
  __REG32 ABB1 :8;
  __REG32 ABB2 :8;
  __REG32 ABB3 :8;
} __huabb_bits;

/* High-Speed UART AutoBaud Table Registers */
typedef struct {
  __REG32 ABT0 :8;
  __REG32 ABT1 :8;
  __REG32 ABT2 :8;
  __REG32 ABT3 :8;
} __huabt_bits;

/* I/O PORT MODE SELECT REGISTER (IOPMODE1) */
typedef struct {
  __REG32 GPIO0 :1;
  __REG32 GPIO1 :1;
  __REG32 GPIO2 :1;
  __REG32 GPIO3 :1;
  __REG32 GPIO4 :1;
  __REG32 GPIO5 :1;
  __REG32 GPIO6 :1;
  __REG32 GPIO7 :1;
  __REG32 GPIO8 :1;
  __REG32 GPIO9 :1;
  __REG32 GPIO10 :1;
  __REG32 GPIO11 :1;
  __REG32 GPIO12 :1;
  __REG32 GPIO13 :1;
  __REG32 GPIO14 :1;
  __REG32 GPIO15 :1;
  __REG32 GPIO16 :1;
  __REG32 GPIO17 :1;
  __REG32 GPIO18 :1;
  __REG32 GPIO19 :1;
  __REG32 GPIO20 :1;
  __REG32 GPIO21 :1;
  __REG32 GPIO22 :1;
  __REG32 GPIO23 :1;
  __REG32 GPIO24 :1;
  __REG32 GPIO25 :1;
  __REG32 GPIO26 :1;
  __REG32 GPIO27 :1;
  __REG32 GPIO28 :1;
  __REG32 GPIO29 :1;
  __REG32 GPIO30 :1;
  __REG32 GPIO31 :1;
} __iopmode1_bits;

/* I/O PORT MODE SELECT REGISTER (IOPMODE2) */
typedef struct {
  __REG32 GPIO32 :1;
  __REG32 GPIO33 :1;
  __REG32 GPIO34 :1;
  __REG32 GPIO35 :1;
  __REG32 GPIO36 :1;
  __REG32 GPIO37 :1;
  __REG32 GPIO38 :1;
  __REG32 GPIO39 :1;
  __REG32 GPIO40 :1;
  __REG32 GPIO41 :1;
  __REG32 GPIO42 :1;
  __REG32 GPIO43 :1;
  __REG32 GPIO44 :1;
  __REG32 GPIO45 :1;
  __REG32 GPIO46 :1;
  __REG32 GPIO47 :1;
  __REG32 GPIO48 :1;
  __REG32 GPIO49 :1;
  __REG32 GPIO50 :1;
  __REG32 GPIO51 :1;
  __REG32 GPIO52 :1;
  __REG32 GPIO53 :1;
  __REG32 GPIO54 :1;
  __REG32 GPIO55 :1;
  __REG32 GPIO56 :1;
  __REG32 GPIO57 :1;
  __REG32 GPIO58 :1;
  __REG32 GPIO59 :1;
  __REG32 GPIO60 :1;
  __REG32 GPIO61 :1;
  __REG32 GPIO62 :1;
  __REG32 GPIO63 :1;
} __iopmode2_bits;

/* I/O PORT FUNCTION CONTROL REGISTER (IOPCON1) */
typedef struct {
  __REG32        :1;
  __REG32        :1;
  __REG32        :1;
  __REG32        :1;
  __REG32        :1;
  __REG32        :1;
  __REG32        :1;
  __REG32        :1;
  __REG32 GPIO8  :1;
  __REG32 GPIO9  :1;
  __REG32 GPIO10 :1;
  __REG32 GPIO11 :1;
  __REG32 GPIO12 :1;
  __REG32 GPIO13 :1;
  __REG32 GPIO14 :1;
  __REG32 GPIO15 :1;
  __REG32 GPIO16 :1;
  __REG32 GPIO17 :1;
  __REG32 GPIO18 :1;
  __REG32 GPIO19 :1;
  __REG32 GPIO20 :1;
  __REG32 GPIO21 :1;
  __REG32 GPIO22 :1;
  __REG32 GPIO23 :1;
  __REG32 GPIO24 :1;
  __REG32 GPIO25 :1;
  __REG32 GPIO26 :1;
  __REG32 GPIO27 :1;
  __REG32 GPIO28 :1;
  __REG32 GPIO29 :1;
  __REG32 GPIO30 :1;
  __REG32 GPIO31 :1;
} __iopcon1_bits;

/* I/O PORT FUNCTION CONTROL REGISTER (IOPCON2) */
typedef struct {
  __REG32 GPIO32 :1;
  __REG32 GPIO33 :1;
  __REG32 GPIO34 :1;
  __REG32 GPIO35 :1;
  __REG32 GPIO36 :1;
  __REG32 GPIO37 :1;
  __REG32 GPIO38 :1;
  __REG32 GPIO39 :1;
  __REG32 GPIO40 :1;
  __REG32 GPIO41 :1;
  __REG32 GPIO42 :1;
  __REG32 GPIO43 :1;
  __REG32 GPIO44 :1;
  __REG32 GPIO45 :1;
  __REG32 GPIO46 :1;
  __REG32 GPIO47 :1;
  __REG32 GPIO48 :1;
  __REG32 GPIO49 :1;
  __REG32 GPIO50 :1;
  __REG32 GPIO51 :1;
  __REG32 GPIO52 :1;
  __REG32 GPIO53 :1;
  __REG32 GPIO54 :1;
  __REG32 GPIO55 :1;
  __REG32 GPIO56 :1;
  __REG32 GPIO57 :1;
  __REG32 GPIO58 :1;
  __REG32 GPIO59 :1;
  __REG32 GPIO60 :1;
  __REG32 GPIO61 :1;
  __REG32 GPIO62 :1;
  __REG32 GPIO63 :1;
} __iopcon2_bits;

/* I/O PORT CONTROL REGISTER FOR GDMA (IOPGDMA) */
typedef struct {
  __REG32 XGDMA_REQ0 :2;
  __REG32 XGDMA_REQ1 :2;
  __REG32 XGDMA_REQ2 :2;
  __REG32 XGDMA_REQ3 :2;
  __REG32 XGDMA_ACK0 :1;
  __REG32 XGDMA_ACK1 :1;
  __REG32 XGDMA_ACK2 :1;
  __REG32 XGDMA_ACK3 :1;
  __REG32            :20;
} __iopgdma_bits;

/* I/O PORT CONTROL REGISTER FOR EXTERNAL INTERRUPT (IOPEXTINT) */
typedef struct {
  __REG32 XINT0 :4;
  __REG32 XINT1 :4;
  __REG32 XINT2 :4;
  __REG32 XINT3 :4;
  __REG32 XINT4 :4;
  __REG32 XINT5 :4;
  __REG32       :8;
} __iopextint_bits;

/* I/O PORT EXTERNAL INTERRUPT CLEAR REGISTER (IOPEXTINTPND) */
typedef struct {
  __REG32 EXTINTCLR0 :1;
  __REG32 EXTINTCLR1 :1;
  __REG32 EXTINTCLR2 :1;
  __REG32 EXTINTCLR3 :1;
  __REG32 EXTINTCLR4 :1;
  __REG32 EXTINTCLR5 :1;
  __REG32            :26;
} __iopextintpnd_bits;

/* INTMOD */
typedef struct {
  __REG32 IIC           :1;
  __REG32 HUART0_TX     :1;
  __REG32 HUART0_RX     :1;
  __REG32 HUART1_TX     :1;
  __REG32 HUART1_RX     :1;
  __REG32 CUART_TX      :1;
  __REG32 CUART_RX      :1;
  __REG32 USB_HOST      :1;
  __REG32 USB_DEVICE    :1;
  __REG32 PCI_CARDBUS   :1;
  __REG32 SAR_DONE      :1;
  __REG32 SAR_ERROR     :1;
  __REG32 ETHERNET0_TX  :1;
  __REG32 ETHERNET0_RX  :1;
  __REG32 ETHERNET1_TX  :1;
  __REG32 ETHERNET1_RX  :1;
  __REG32 DES           :1;
  __REG32 GDMA_CH_0     :1;
  __REG32 GDMA_CH_1     :1;
  __REG32 GDMA_CH_2     :1;
  __REG32 GDMA_CH_3     :1;
  __REG32 GDMA_CH_4     :1;
  __REG32 GDMA_CH_5     :1;
  __REG32 TIMER_0       :1;
  __REG32 TIMER_1       :1;
  __REG32 TIMER_2       :1;
  __REG32 TIMER_3       :1;
  __REG32 TIMER_4       :1;
  __REG32 TIMER_5       :1;
  __REG32 WDT           :1;
  __REG32               :2;
} __intmod_bits;

/* EXTMOD */
typedef struct {
  __REG32 EXT0 :1;
  __REG32 EXT1 :1;
  __REG32 EXT2 :1;
  __REG32 EXT3 :1;
  __REG32 EXT4 :1;
  __REG32 EXT5 :1;
  __REG32      :26;
} __extmod_bits;

/* INTERRUPT PRIORITY REGISTER 1 */
typedef struct {
  __REG32 PRIORITY0 :6;
  __REG32           :2;
  __REG32 PRIORITY1 :6;
  __REG32           :2;
  __REG32 PRIORITY2 :6;
  __REG32           :2;
  __REG32 PRIORITY3 :6;
  __REG32           :2;
} __intprior0_bits;

/* INTERRUPT PRIORITY REGISTER 1 */
typedef struct {
  __REG32 PRIORITY4 :6;
  __REG32           :2;
  __REG32 PRIORITY5 :6;
  __REG32           :2;
  __REG32 PRIORITY6 :6;
  __REG32           :2;
  __REG32 PRIORITY7 :6;
  __REG32           :2;
} __intprior1_bits;

/* INTERRUPT PRIORITY REGISTER 2 */
typedef struct {
  __REG32 PRIORITY8  :6;
  __REG32            :2;
  __REG32 PRIORITY9  :6;
  __REG32            :2;
  __REG32 PRIORITY10 :6;
  __REG32            :2;
  __REG32 PRIORITY11 :6;
  __REG32            :2;
} __intprior2_bits;

/* INTERRUPT PRIORITY REGISTER 3 */
typedef struct {
  __REG32 PRIORITY12  :6;
  __REG32             :2;
  __REG32 PRIORITY13  :6;
  __REG32             :2;
  __REG32 PRIORITY14  :6;
  __REG32             :2;
  __REG32 PRIORITY15  :6;
  __REG32             :2;
} __intprior3_bits;

/* INTERRUPT PRIORITY REGISTER 4 */
typedef struct {
  __REG32 PRIORITY16  :6;
  __REG32             :2;
  __REG32 PRIORITY17  :6;
  __REG32             :2;
  __REG32 PRIORITY18  :6;
  __REG32             :2;
  __REG32 PRIORITY19  :6;
  __REG32             :2;
} __intprior4_bits;

/* INTERRUPT PRIORITY REGISTER 5 */
typedef struct {
  __REG32 PRIORITY20  :6;
  __REG32             :2;
  __REG32 PRIORITY21  :6;
  __REG32             :2;
  __REG32 PRIORITY22  :6;
  __REG32             :2;
  __REG32 PRIORITY23  :6;
  __REG32             :2;
} __intprior5_bits;

/* INTERRUPT PRIORITY REGISTER 6 */
typedef struct {
  __REG32 PRIORITY24  :6;
  __REG32             :2;
  __REG32 PRIORITY25  :6;
  __REG32             :2;
  __REG32 PRIORITY26  :6;
  __REG32             :2;
  __REG32 PRIORITY27  :6;
  __REG32             :2;
} __intprior6_bits;

/* INTERRUPT PRIORITY REGISTER 7 */
typedef struct {
  __REG32 PRIORITY28  :6;
  __REG32             :2;
  __REG32 PRIORITY29  :6;
  __REG32             :2;
  __REG32 PRIORITY30  :6;
  __REG32             :2;
  __REG32 PRIORITY31  :6;
  __REG32             :2;
} __intprior7_bits;

/* INTERRUPT PRIORITY REGISTER 8 */
typedef struct {
  __REG32 PRIORITY32  :6;
  __REG32             :2;
  __REG32 PRIORITY33  :6;
  __REG32             :2;
  __REG32 PRIORITY34  :6;
  __REG32             :2;
  __REG32 PRIORITY35  :6;
  __REG32             :2;
} __intprior8_bits;


/* INTERRUPT BY PRIORITY REGISTER - IPRIORHI */
typedef struct {
  __REG32 PRIORITY32  :1;
  __REG32 PRIORITY33  :1;
  __REG32 PRIORITY34  :1;
  __REG32 PRIORITY35  :1;
  __REG32             :28;
} __ipriorhi_bits;

/* INTERRUPT BY PRIORITY REGISTER - IPRIORLO */
typedef struct {
  __REG32  PRIORITY0  :1;
  __REG32  PRIORITY1  :1;
  __REG32  PRIORITY2  :1;
  __REG32  PRIORITY3  :1;
  __REG32  PRIORITY4  :1;
  __REG32  PRIORITY5  :1;
  __REG32  PRIORITY6  :1;
  __REG32  PRIORITY7  :1;
  __REG32  PRIORITY8  :1;
  __REG32  PRIORITY9  :1;
  __REG32  PRIORITY10 :1;
  __REG32  PRIORITY11 :1;
  __REG32  PRIORITY12 :1;
  __REG32  PRIORITY13 :1;
  __REG32  PRIORITY14 :1;
  __REG32  PRIORITY15 :1;
  __REG32  PRIORITY16 :1;
  __REG32  PRIORITY17 :1;
  __REG32  PRIORITY18 :1;
  __REG32  PRIORITY19 :1;
  __REG32  PRIORITY20 :1;
  __REG32  PRIORITY21 :1;
  __REG32  PRIORITY22 :1;
  __REG32  PRIORITY23 :1;
  __REG32  PRIORITY24 :1;
  __REG32  PRIORITY25 :1;
  __REG32  PRIORITY26 :1;
  __REG32  PRIORITY27 :1;
  __REG32  PRIORITY28 :1;
  __REG32  PRIORITY29 :1;
  __REG32  PRIORITY30 :1;
  __REG32  PRIORITY31 :1;
} __ipriorlo_bits;

/* INTERRUPT TEST REGISTER - EXTTST */
typedef struct {
  __REG32 EXT0 :1;
  __REG32 EXT1 :1;
  __REG32 EXT2 :1;
  __REG32 EXT3 :1;
  __REG32 EXT4 :1;
  __REG32 EXT5 :1;
  __REG32      :26;
} __exttst_bits;

/* TIMER MODE REGISTER */
typedef struct {
  __REG32 TE0   :1;
  __REG32 TMD0  :1;
  __REG32 TCLR0 :1;
  __REG32       :1;
  __REG32 TE1   :1;
  __REG32 TMD1  :1;
  __REG32 TCLR1 :1;
  __REG32       :1;
  __REG32 TE2   :1;
  __REG32 TMD2  :1;
  __REG32 TCLR2 :1;
  __REG32       :1;
  __REG32 TE3   :1;
  __REG32 TMD3  :1;
  __REG32 TCLR3 :1;
  __REG32       :1;
  __REG32 TE4   :1;
  __REG32 TMD4  :1;
  __REG32 TCLR4 :1;
  __REG32       :1;
  __REG32 TE5   :1;
  __REG32 TMD5  :1;
  __REG32 TCLR5 :1;
  __REG32       :9;
} __tmod_bits;

/* TIMER INTERRUPT CLEAR REGISTERS */
typedef struct {
  __REG32 WDTIC :1;
  __REG32 TIC0  :1;
  __REG32 TIC1  :1;
  __REG32 TIC2  :1;
  __REG32 TIC3  :1;
  __REG32 TIC4  :1;
  __REG32 TIC5  :1;
  __REG32       :25;
} __tic_bits;

/* WATCHDOG TIMER REGISTER (WDT) */
typedef struct {
  __REG32 WDTVAL :18;
  __REG32        :11;
  __REG32 RST    :1;
  __REG32 MODE   :1;
  __REG32 EN     :1;
} __wdt_bits;

/* PCIHID (Vendor ID & Device ID) */
typedef struct {
  __REG32 VENDOR_ID :16;
  __REG32 DEVICE_ID :16;
} __pcihid_bits;

/* PCIHSC (Device Status & Command Register) */
typedef struct {
  __REG32 IOE :1;
  __REG32 MME :1;
  __REG32 BME :1;
  __REG32 SCE :1;
  __REG32 MWI :1;
  __REG32 VGA :1;
  __REG32 PEE :1;
  __REG32 STC :1;
  __REG32 SER :1;
  __REG32 FBE :1;
  __REG32     :10;
  __REG32 CAP :1;
  __REG32 M66 :1;
  __REG32     :1;
  __REG32 FBB :1;
  __REG32 MPE :1;
  __REG32 DST :2;
  __REG32 STA :1;
  __REG32 RTA :1;
  __REG32 RMA :1;
  __REG32 SSE :1;
  __REG32 DPE :1;
} __pcihsc_bits;

/* PCIHCODE (Class Code, Revision ID) */
typedef struct {
  __REG32 REV :8;
  __REG32 PGI :8;
  __REG32 SCC :8;
  __REG32 BCC :8;
} __pcihcode_bits;

/* PCIHLINE (BIST, Header, Lat_timer, Cachelinesize) */
typedef struct {
  __REG32 CLS :8;
  __REG32 LTT :8;
  __REG32 HTP :7;
  __REG32 SMF :1;
  __REG32 CMP :4;
  __REG32     :2;
  __REG32 STB :1;
  __REG32 CAP :1;
} __pcihline_bits;

/* PCIHBAR0/1 (Memory Base Address Register 0/1) */
typedef struct {
  __REG32 IND :1;
  __REG32 TYP :2;
  __REG32 PRF :1;
  __REG32 BAR :28;
} __pcihbar0_1_bits;

/* PCIHBAR2 (I/O Base Address Register 2) */
typedef struct {
  __REG32 IND :1;
  __REG32     :1;
  __REG32 BAR :30;
} __pcihbar2_bits;

/* PCIHSSID (Subsystem ID, Subsystem Vendor ID) */
typedef struct {
  __REG32 SVD :16;
  __REG32 SID :16;
}__pcihssid_bits;

/* PCIHCISP (CIS (CardBus Information Structure) Pointer) */
typedef struct {
  __REG32 IND :3;
  __REG32 OFF :29;
} __pcihcisp_bits;

/* PCIHCAP (Capabilities List Pointer) */
typedef struct {
  __REG32 CAP :8;
  __REG32     :24;
} __pcihcap_bits;

/* PCIHLTIT (Int_Pin, Int_Line) */
typedef struct {
  __REG32 INL :8;
  __REG32 INP :8;
  __REG32     :16;
} __pcihltit_bits;

/* PCIHTIMER (Master Timer Register) */
typedef struct {
  __REG32 TRT :8;
  __REG32 RTC :8;
  __REG32     :16;
} __pcihtimer_bits;

/* PCIHPMR0 (Power Management Register 0 (PMC): 0xF01100DC) */
typedef struct {
  __REG32 CID :8;
  __REG32 NIP :8;
  __REG32 VER :3;
  __REG32 CLK :1;
  __REG32     :1;
  __REG32 DSI :1;
  __REG32 AUX :3;
  __REG32 D1S :1;
  __REG32 D2S :1;
  __REG32 PD0 :1;
  __REG32 PD1 :1;
  __REG32 PD2 :1;
  __REG32 PD3 :1;
  __REG32 PDC :1;
} __pcihpmr0_bits;

/* PCIHPMR1 (Power Management Register 1 (PMCSR): 0xF01100E0) */
typedef struct {
  __REG32 PST :2;
  __REG32     :6;
  __REG32 PME :1;
  __REG32 DSL :4;
  __REG32 DSC :2;
  __REG32 PMS :1;
  __REG32     :6;
  __REG32 B23 :1;
  __REG32 BPE :1;
  __REG32 DAT :8;
} __pcihpmr1_bits;

/* PCICON (PC Card Control and Status Register: 0xF0110100) */
typedef struct {
  __REG32 HST :1;
  __REG32 ARB :1;
  __REG32     :2;
  __REG32 ATS :1;
  __REG32 SPL :1;
  __REG32 IOP :1;
  __REG32 MMP :1;
  __REG32 CFD :1;
  __REG32 RDY :1;
  __REG32     :6;
  __REG32 WKI :1;
  __REG32 WKA :1;
  __REG32     :6;
  __REG32 CAR :1;
  __REG32     :3;
  __REG32 TBS :1;
  __REG32 MBS :1;
  __REG32 DBS :1;
  __REG32 INT :1;
} __pcicon_bits;

/* PCISET (PC Card Command Set, Read Count, DAC Register) */
typedef struct {
  __REG32 DAC :8;
  __REG32 RDC :8;
  __REG32     :1;
  __REG32 CMD :3;
  __REG32     :12;
} __pciset_bits;

/* PCIINTEN (PC Card Interrupt Enable Register) */
typedef struct {
  __REG32 PRD :1;
  __REG32 PRA :1;
  __REG32 MFE :1;
  __REG32 MPE :1;
  __REG32 TPE :1;
  __REG32 PME :1;
  __REG32 PMC :1;
  __REG32 PSC :1;
  __REG32 BPA :1;
  __REG32 SER :1;
  __REG32 INA :1;
  __REG32     :1;
  __REG32 DM0 :1;
  __REG32 DE0 :1;
  __REG32 DM1 :1;
  __REG32 DE1 :1;
  __REG32 AER :1;
  __REG32     :14;
  __REG32 BAP :1;
} __pciinten_bits;

/* PCIINTST (PC Card Interrupt Status Register) */
typedef struct {
  __REG32 PRD :1;
  __REG32 PRA :1;
  __REG32 MFE :1;
  __REG32 MPE :1;
  __REG32 TPE :1;
  __REG32 PME :1;
  __REG32 PMC :1;
  __REG32 PSC :1;
  __REG32 BPA :1;
  __REG32 SER :1;
  __REG32 INA :1;
  __REG32     :1;
  __REG32 DM0 :1;
  __REG32 DE0 :1;
  __REG32 DM1 :1;
  __REG32 DE1 :1;
  __REG32 AER :1;
  __REG32     :12;
  __REG32 DME :1;
  __REG32 RDE :1;
  __REG32 WRE :1;
} __pciintst_bits;

/* PCIBATAPM (PC Card Base Address Translation Register from AHB to
CardBus of Memory Cycle) */
typedef struct {
  __REG32     :28;
  __REG32 APM :4;
} __pcibatapm_bits;

/* PCIBATAPI (PC Card Base Address Translation Register from
AHB to CardBus of I/O Cycle) */
typedef struct {
  __REG32     :26;
  __REG32 API :6;
} __pcibatapi_bits;

/* PCIRCC (PC Card Reset & Clock Control Register) */
typedef struct {
  __REG32 RSB   :1;
  __REG32 RSL   :1;
  __REG32 MSK   :1;
  __REG32 C33M  :1;
  __REG32 SLW   :1;
  __REG32       :3;
  __REG32 KCK   :1;
  __REG32 ACC   :1;
  __REG32 CKI   :1;
  __REG32 CKR   :1;
  __REG32 CKA   :1;
  __REG32 CKD   :1;
  __REG32       :14;
  __REG32 BRS   :1;
  __REG32 LRS   :1;
  __REG32 CKS   :1;
  __REG32 CKN   :1;
} __pcircc_bits;

/* PCIDIAG0 (PC Card Diagnostic Register for Test Purpose) */
typedef struct {
  __REG32 CMR :1;
  __REG32 EXR :1;
  __REG32 EXC :1;
  __REG32 IGB :1;
  __REG32 WPR :1;
  __REG32 NPU :1;
  __REG32 FAS :1;
  __REG32 SPC :1;
  __REG32 FTR :1;
  __REG32 FTT :1;
  __REG32 FMR :1;
  __REG32 FMT :1;
  __REG32 DI4 :1;
  __REG32 DIR :1;
  __REG32 ABE :1;
  __REG32 D4W :1;
  __REG32 DC3 :1;
  __REG32 ECB :1;
  __REG32     :14;
} __pcidiag0_bits;

/* PCIDIAG1 (PC Card Diagnostic Register for Test Purpose) */
typedef struct {
  __REG32     :16;
  __REG32 BID :2;
  __REG32 REQ :1;
  __REG32 MAS :5;
  __REG32 TAR :4;
  __REG32 REV :4;
} __pcidiag1_bits;

/* PCIBELAP (PC Card Doorbell Register to CardBus bus:
User interrupt to CardBus bus) */
typedef struct {
  __REG32 UIF :31;
  __REG32 BEL :1;
} __pcibelap_bits;

/* PCIBELPA (PC Card Doorbell Register to AHB bus: User interrupt to AHB bus) */
typedef struct {
  __REG32 UIF :31;
  __REG32 BEL :1;
} __pcibelpa_bits;

/* PCIMAIL0~PCIMAIL3 (PC Card Mailbox Register 0~3: User information) */
typedef struct {
  __REG32 B0  :1;
  __REG32 B1  :1;
  __REG32 B2  :1;
  __REG32 B3  :1;
  __REG32 B4  :1;
  __REG32 B5  :1;
  __REG32 B6  :1;
  __REG32 B7  :1;
  __REG32 B8  :1;
  __REG32 B9  :1;
  __REG32 B10 :1;
  __REG32 B11 :1;
  __REG32 B12 :1;
  __REG32 B13 :1;
  __REG32 B14 :1;
  __REG32 B15 :1;
  __REG32 B16 :1;
  __REG32 B17 :1;
  __REG32 B18 :1;
  __REG32 B19 :1;
  __REG32 B20 :1;
  __REG32 B21 :1;
  __REG32 B22 :1;
  __REG32 B23 :1;
  __REG32 B24 :1;
  __REG32 B25 :1;
  __REG32 B26 :1;
  __REG32 B27 :1;
  __REG32 B28 :1;
  __REG32 B29 :1;
  __REG32 B30 :1;
  __REG32 B31 :1;
} __pcimail_bits;

/* PCIBATPA0 (PC Card Base Address Translation from
CardBus to AHB of Memory BAR 0) */
typedef struct {
  __REG32     :4;
  __REG32 PA0 :28;
} __pcibatpa0_bits;

/* PCIBAM0 (PC Card Base Address Mask Register of Memory BAR 0) */
typedef struct {
  __REG32     :4;
  __REG32 AM0 :27;
  __REG32     :1;
} __pcibam0_bits;

/* PCIBATPA1 (PC Card Base Address Translation from
CardBus to AHB of Memory BAR 1) */
typedef struct {
  __REG32     :4;
  __REG32 PA1 :28;
} __pcibatpa1_bits;

/* PCIBAM1 (PC Card Base Address Mask Register of Memory BAR 1) */
typedef struct {
  __REG32     :4;
  __REG32 AM1 :27;
  __REG32     :1;
} __pcibam1_bits;

/* PCIBAM2 (PC Card Base Address Mask Register of I/O BAR 2) */
typedef struct {
  __REG32     :8;
  __REG32 PA2 :24;
} __pcibatpa2_bits;

/* PCISWAP (PC Card Byte Swap register) */
typedef struct {
  __REG32 TRB :2;
  __REG32 TRH :2;
  __REG32 TRW :2;
  __REG32     :2;
  __REG32 TTB :2;
  __REG32 TTH :2;
  __REG32 TTW :2;
  __REG32     :2;
  __REG32 MRB :2;
  __REG32 MRH :2;
  __REG32 MRW :2;
  __REG32     :2;
  __REG32 MTB :2;
  __REG32 MTH :2;
  __REG32 MTW :2;
  __REG32     :2;
} __pciswap_bits;

/* PCCARDEVT (PC Card Socket/Function Event Register) */
typedef struct {
  __REG32 STC :1;
  __REG32 CD1 :1;
  __REG32 CD2 :1;
  __REG32 PWC :1;
  __REG32 GWA :1;
  __REG32     :10;
  __REG32 INT :1;
  __REG32 WPC :1;
  __REG32 IRC :1;
  __REG32 SPC :1;
  __REG32 WPW :1;
  __REG32 RDA :1;
  __REG32 INA :1;
  __REG32     :10;
} __pccardevt_bits;

/* PCCARDEVM (PC Card Socket/Function Event Mask Register) */
typedef struct {
  __REG32 STC :1;
  __REG32 CD1 :1;
  __REG32 CD2 :1;
  __REG32 PWC :1;
  __REG32 GWA :1;
  __REG32     :9;
  __REG32 WKU :1;
  __REG32 INT :1;
  __REG32 WPC :1;
  __REG32 IRC :1;
  __REG32 SPC :1;
  __REG32 WPW :1;
  __REG32 RDA :1;
  __REG32 INA :1;
  __REG32     :10;
} __pccardevm_bits;

/* PCCARDPRS (PC Card Socket/Function PRESENT STATE Register) */
typedef struct {
  __REG32 STC :1;
  __REG32 CD1 :1;
  __REG32 CD2 :1;
  __REG32 PWC :1;
  __REG32 C16 :1;
  __REG32 C32 :1;
  __REG32     :1;
  __REG32 CNO :1;
  __REG32 DTL :1;
  __REG32 BVR :1;
  __REG32 C5V :1;
  __REG32 C3V :1;
  __REG32 CXV :1;
  __REG32 CYV :1;
  __REG32 CVS :1;
  __REG32 INT :1;
  __REG32 WPS :1;
  __REG32 RDY :1;
  __REG32 BVD :1;
  __REG32     :2;
  __REG32 INP :1;
  __REG32     :6;
  __REG32 S5V :1;
  __REG32 S3V :1;
  __REG32 SXV :1;
  __REG32 SYV :1;
} __pccardprs_bits;

/* PCCARDFEV (PC Card Socket/Function Force Event Register) */
typedef struct {
  __REG32 STC :1;
  __REG32 CD1 :1;
  __REG32 CD2 :1;
  __REG32 PWC :1;
  __REG32 C16 :1;
  __REG32 C32 :1;
  __REG32     :1;
  __REG32 CNO :1;
  __REG32 DTL :1;
  __REG32 BVR :1;
  __REG32 C5V :1;
  __REG32 C3V :1;
  __REG32 CXV :1;
  __REG32 CYV :1;
  __REG32 CVS :1;
  __REG32 INT :1;
  __REG32 WPC :1;
  __REG32 IRC :1;
  __REG32 SPC :1;
  __REG32 WPW :1;
  __REG32 RDA :1;
  __REG32 INA :1;
  __REG32     :10;
} __pccardfev_bits;

/* PCCARDCON (PC Card Socket Control Register) */
typedef struct {
  __REG32 VPP :3;
  __REG32     :1;
  __REG32 VCC :3;
  __REG32     :16;
  __REG32 ACT :1;
  __REG32 CST :8;
} __pccardcon_bits;

/* PCCARD16C (16-bit PC Card Host Control Register) */
typedef struct {
  __REG32 CDT :1;
  __REG32     :3;
  __REG32 MMS :1;
  __REG32 IOS :1;
  __REG32 IOE :1;
  __REG32     :19;
  __REG32 WPS :1;
  __REG32 INS :1;
  __REG32 RDY :1;
  __REG32 BVD :2;
  __REG32 C16 :1;
} __pccard16c_bits;

/* PCCARD16M (16-bit PC Card Host Memory Timing Register) */
typedef struct {
  __REG32 AST :4;
  __REG32     :4;
  __REG32 SST :4;
  __REG32     :4;
  __REG32 SL  :6;
  __REG32     :2;
  __REG32 SHT :4;
  __REG32     :4;
} __pccard16m_bits;

/* PDMACON0/1 (PDMA Channel0 Control & Status Register) */
typedef struct {
  __REG32 RE    :1;
  __REG32 IRP   :1;
  __REG32 BSE   :1;
  __REG32       :1;
  __REG32 S     :1;
  __REG32 D     :1;
  __REG32 SAF   :1;
  __REG32 DAF   :1;
  __REG32 SCM   :4;
  __REG32 DCM   :4;
  __REG32       :13;
  __REG32 ERR   :1;
  __REG32 PRG   :1;
  __REG32 BS    :1;
} __pdmacon0_1_bits;

/* PDMACNT0/1 (PDMA Channel0/1 Transfer Byte Count Register) */
typedef struct {
  __REG32 CNT :24;
  __REG32     :8;
} __pdmacnt0_1_bits;

/* PDMARUN0/1 (PDMA Channel0/1 Run Enable Register) */
typedef struct {
  __REG32 RE  :1;
  __REG32     :31;
} __pdmarun0_1_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  System manager registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG, 0xf0000000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__PDCODE, 0xf0000004,__READ,__pdcode_bits);
__IO_REG32_BIT(__MISCREG,0xf0000008,__READ_WRITE,__miscreg_bits);
__IO_REG32_BIT(__PCLKDIS,0xf000000C,__READ_WRITE,__pclkdis_bits);
__IO_REG32_BIT(__CLKST,  0xf0000010,__READ,__clkst_bits);
__IO_REG32(    __HPRIF,  0xf0000014,__READ_WRITE);
__IO_REG32(    __HPRIR,  0xf0000018,__READ_WRITE);
__IO_REG32_BIT(__CPLLCON,0xf000001C,__READ_WRITE,__cpllcon_bits);
__IO_REG32_BIT(__SPLLCON,0xf0000020,__READ_WRITE,__cpllcon_bits);
__IO_REG32_BIT(__UPLLCON,0xf0000024,__READ_WRITE,__cpllcon_bits);
__IO_REG32_BIT(__PPLLCON,0xf0000028,__READ_WRITE,__cpllcon_bits);

/***************************************************************************
 **
 **  Ext. I/O
 **
 ***************************************************************************/
__IO_REG32_BIT(__B0CON,  0xf0010000,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__B1CON,  0xf0010004,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__B2CON,  0xf0010008,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__B3CON,  0xf001000c,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__B4CON,  0xf0010010,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__B5CON,  0xf0010014,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__B6CON,  0xf0010018,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__B7CON,  0xf001001c,__READ_WRITE,__bncon_bits);
__IO_REG32_BIT(__MUXBCON,0xf0010020,__READ_WRITE,__muxbcon_bits);
__IO_REG32_BIT(__WAITCON,0xf0010024,__READ_WRITE,__waitcon_bits);
__IO_REG32_BIT(__WDSCON, 0xf0010028,__READ_WRITE,__wdscon_bits);

/***************************************************************************
 **
 **  SDRAM
 **
 ***************************************************************************/
__IO_REG32_BIT(__CFGREG, 0xf0020000,__READ_WRITE,__cfgreg_bits);
__IO_REG32_BIT(__CMDREG, 0xf0020004,__READ_WRITE,__cmdreg_bits);
__IO_REG32_BIT(__REFREG, 0xf0020008,__READ_WRITE,__refreg_bits);
__IO_REG32_BIT(__WBTOREG,0xf002000c,__READ_WRITE,__wbtoreg_bits);

/***************************************************************************
 **
 **  i2c
 **
 ***************************************************************************/
__IO_REG32_BIT(__IICCON,0xF00F0000,__READ_WRITE,__iiccon_bits);
__IO_REG32_BIT(__IICBUF,0xF00F0004,__READ_WRITE,__iicbuf_bits);
__IO_REG32_BIT(__IICPS, 0xF00F0008,__READ_WRITE,__iicps_bits);
__IO_REG32_BIT(__IICCNT,0xF00F000C,__READ_WRITE,__iiccnt_bits);
__IO_REG32_BIT(__IICPND,0xF00F0010,__READ_WRITE,__iicpnd_bits);

/***************************************************************************
 **
 **  Ethernet
 **
 ***************************************************************************/
__IO_REG32_BIT(__BDMATXCONA, 0xf00a0000,__READ_WRITE,__bdmatxcon_bits);
__IO_REG32_BIT(__BDMARXCONA, 0xf00a0004,__READ_WRITE,__bdmarxcon_bits);
__IO_REG32(    __BDMATXDPTRA,0xf00a0008,__READ_WRITE);
__IO_REG32(    __BDMARXDPTRA,0xf00a000c,__READ_WRITE);
__IO_REG32_BIT(__BTXBDCNTA,  0xf00a0010,__READ_WRITE,__btxbdcnt_bits);
__IO_REG32_BIT(__BRXBDCNTA,  0xf00a0014,__READ_WRITE,__brxbdcnt_bits);
__IO_REG32_BIT(__BMTXINTENA, 0xf00a0018,__READ_WRITE,__bmtxinten_bits);
__IO_REG32_BIT(__BMRXINTENA, 0xf00a001c,__READ_WRITE,__bmrxinten_bits);
__IO_REG32_BIT(__BMTXSTATA,  0xf00a0020,__READ_WRITE,__bmtxstat_bits);
__IO_REG32_BIT(__BMRXSTATA,  0xf00a0024,__READ_WRITE,__bmrxstat_bits);
__IO_REG32_BIT(__BDMARXLENA, 0xf00a0028,__READ_WRITE,__bdmarxlen_bits);
__IO_REG32_BIT(__CFTXSTATA,  0xf00a0030,__READ,      __cftxstat_bits);
__IO_REG32_BIT(__MACCONA,    0xf00b0000,__READ_WRITE,__maccon_bits);
__IO_REG32_BIT(__CAMCONA,    0xf00b0004,__READ_WRITE,__camcon_bits);
__IO_REG32_BIT(__MACTXCONA,  0xf00b0008,__READ_WRITE,__mactxcon_bits);
__IO_REG32_BIT(__MACTXSTATA, 0xf00b000c,__READ,      __mactxstat_bits);
__IO_REG32_BIT(__MACRXCONA,  0xf00b0010,__READ_WRITE,__macrxcon_bits);
__IO_REG32_BIT(__MACRXSTATA, 0xf00b0014,__READ,      __macrxstat_bits);
__IO_REG32_BIT(__STADATAA,   0xf00b0018,__READ_WRITE,__stadata_bits);
__IO_REG32_BIT(__STACONA,    0xf00b001c,__READ_WRITE,__stacon_bits);
__IO_REG32_BIT(__CAMENA,     0xf00b0028,__READ_WRITE,__camen_bits);
__IO_REG32_BIT(__MISSCNTA,   0xf00b003c,__READ_WRITE,__misscnt_bits);
__IO_REG32_BIT(__PZCNTA,     0xf00b0040,__READ,      __pzcnt_bits);
__IO_REG32_BIT(__RMPZCNTA,   0xf00b0044,__READ,      __rmpzcnt_bits);
__IO_REG32(    __CAMA,       0xf00b0080,__WRITE);

__IO_REG32_BIT(__BDMATXCONB, 0xf00c0000,__READ_WRITE,__bdmatxcon_bits);
__IO_REG32_BIT(__BDMARXCONB, 0xf00c0004,__READ_WRITE,__bdmarxcon_bits);
__IO_REG32(    __BDMATXDPTRB,0xf00c0008,__READ_WRITE);
__IO_REG32(    __BDMARXDPTRB,0xf00c000c,__READ_WRITE);
__IO_REG32_BIT(__BTXBDCNTB,  0xf00c0010,__READ_WRITE,__btxbdcnt_bits);
__IO_REG32_BIT(__BRXBDCNTB,  0xf00c0014,__READ_WRITE,__brxbdcnt_bits);
__IO_REG32_BIT(__BMTXINTENB, 0xf00c0018,__READ_WRITE,__bmtxinten_bits);
__IO_REG32_BIT(__BMRXINTENB, 0xf00c001c,__READ_WRITE,__bmrxinten_bits);
__IO_REG32_BIT(__BMTXSTATB,  0xf00c0020,__READ_WRITE,__bmtxstat_bits);
__IO_REG32_BIT(__BMRXSTATB,  0xf00c0024,__READ_WRITE,__bmrxstat_bits);
__IO_REG32_BIT(__BDMARXLENB, 0xf00c0028,__READ_WRITE,__bdmarxlen_bits);
__IO_REG32_BIT(__CFTXSTATB,  0xf00c0030,__READ,      __cftxstat_bits);
__IO_REG32_BIT(__MACCONB,    0xf00d0000,__READ_WRITE,__maccon_bits);
__IO_REG32_BIT(__CAMCONB,    0xf00d0004,__READ_WRITE,__camcon_bits);
__IO_REG32_BIT(__MACTXCONB,  0xf00d0008,__READ_WRITE,__mactxcon_bits);
__IO_REG32_BIT(__MACTXSTATB, 0xf00d000c,__READ,      __mactxstat_bits);
__IO_REG32_BIT(__MACRXCONB,  0xf00d0010,__READ_WRITE,__macrxcon_bits);
__IO_REG32_BIT(__MACRXSTATB, 0xf00d0014,__READ,      __macrxstat_bits);
__IO_REG32_BIT(__CAMENB,     0xf00d0028,__READ_WRITE,__camen_bits);
__IO_REG32_BIT(__MISSCNTB,   0xf00d003c,__READ_WRITE,__misscnt_bits);
__IO_REG32_BIT(__PZCNTB,     0xf00d0040,__READ,      __pzcnt_bits);
__IO_REG32_BIT(__RMPZCNTB,   0xf00d0044,__READ,      __rmpzcnt_bits);
__IO_REG32(    __CAMB,       0xf00d0080,__WRITE);

/***************************************************************************
 **
 **  SAR
 **
 ***************************************************************************/
__IO_REG32_BIT(__SW_RESET,       0xf0120000,__READ_WRITE,__sw_reset_bits);
__IO_REG32_BIT(__SAR_DB_ID,      0xf0120004,__READ,      __sar_db_id_bits);
__IO_REG32_BIT(__GLOBAL_MODE,    0xf0120008,__READ_WRITE,__global_mode_bits);
__IO_REG32_BIT(__TIMEOUT_BASE,   0xf012000c,__READ_WRITE,__timeout_base_bits);
__IO_REG32_BIT(__TX_READY1,      0xf0120010,__READ_WRITE,__tx_ready1_bits);
__IO_REG32_BIT(__TX_READY2,      0xf0120014,__READ_WRITE,__tx_ready2_bits);
__IO_REG32_BIT(__TX_DONE_ADDR,   0xf0120018,__READ_WRITE,__tx_done_addr_bits);
__IO_REG32_BIT(__TX_DONE_SIZE,   0xf012001c,__READ_WRITE,__tx_done_size_bits);
__IO_REG32_BIT(__RX_POOL0_ADDR,  0xf0120020,__READ_WRITE,__rx_pooln_addr_bits);
__IO_REG32_BIT(__RX_POOL0_SIZE,  0xf0120024,__READ_WRITE,__rx_pooln_size_bits);
__IO_REG32_BIT(__RX_POOL1_ADDR,  0xf0120028,__READ_WRITE,__rx_pooln_addr_bits);
__IO_REG32_BIT(__RX_POOL1_SIZE,  0xf012002c,__READ_WRITE,__rx_pooln_size_bits);
__IO_REG32_BIT(__RX_POOL2_ADDR,  0xf0120030,__READ_WRITE,__rx_pooln_addr_bits);
__IO_REG32_BIT(__RX_POOL2_SIZE,  0xf0120034,__READ_WRITE,__rx_pooln_size_bits);
__IO_REG32_BIT(__RX_POOL3_ADDR,  0xf0120038,__READ_WRITE,__rx_pooln_addr_bits);
__IO_REG32_BIT(__RX_POOL3_SIZE,  0xf012003c,__READ_WRITE,__rx_pooln_size_bits);
__IO_REG32_BIT(__RX_DONE0_ADDR,  0xf0120040,__READ_WRITE,__rx_donen_addr_bits);
__IO_REG32_BIT(__RX_DONE0_SIZE,  0xf0120044,__READ_WRITE,__rx_donen_size_bits);
__IO_REG32_BIT(__RX_DONE1_ADDR,  0xf0120048,__READ_WRITE,__rx_donen_addr_bits);
__IO_REG32_BIT(__RX_DONE1_SIZE,  0xf012004c,__READ_WRITE,__rx_donen_size_bits);
__IO_REG32_BIT(__UTOPIA_CONFIG,  0xf0120050,__READ_WRITE,__utopia_config_bits);
__IO_REG32_BIT(__UTOPIA_TIMEOUT, 0xf0120054,__READ_WRITE,__utopia_timeout_bits);
__IO_REG32_BIT(__CLOCK_RATIO,    0xf0120064,__READ_WRITE,__clock_ratio_bits);
__IO_REG32_BIT(__DONE_INT_MASK,  0xf0120070,__READ_WRITE,__done_int_mask_bits);
__IO_REG32_BIT(__ERR_INT_MASK,   0xf0120074,__READ_WRITE,__err_int_mask_bits);
__IO_REG32_BIT(__DONE_INT_STATUS,0xf0120078,__READ_WRITE,__done_int_status_bits);
__IO_REG32_BIT(__ERR_INT_STATUS, 0xf012007c,__READ_WRITE,__err_int_status_bits);
__IO_REG32_BIT(__RATE_LOOKUP_TBL,0xf0120080,__READ_WRITE,__rate_lookup_tbl_bits);
__IO_REG32_BIT(__VP_LOOKUP_TBL,  0xf0120084,__READ_WRITE,__vp_lookup_tbl_bits);
__IO_REG32_BIT(__UBR_SCH_TBL,    0xf0120088,__READ_WRITE,__ubr_sch_tbl_bits);
__IO_REG32_BIT(__CBR_SCH_TBL,    0xf012008c,__READ_WRITE,__cbr_sch_tbl_bits);
__IO_REG32_BIT(__CELL_BUFF,      0xf0120090,__READ_WRITE,__cell_buff_bits);
__IO_REG32_BIT(__SCH_CONN_TBL,   0xf0120094,__READ_WRITE,__sch_conn_tbl_bits);
__IO_REG32_BIT(__AAL_CONN_TBL,   0xf0120098,__READ_WRITE,__aal_conn_tbl_bits);
__IO_REG32_BIT(__SAR_CONN_TBL,   0xf012009c,__READ_WRITE,__sar_conn_tbl_bits);
__IO_REG32_BIT(__CAM_VPIVCI0,    0xf0120100,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN0,        0xf0120104,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI1,    0xf0120108,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN1,        0xf012010c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI2,    0xf0120110,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN2,        0xf0120114,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI3,    0xf0120118,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN3,        0xf012011c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI4,    0xf0120120,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN4,        0xf0120124,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI5,    0xf0120128,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN5,        0xf012012c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI6,    0xf0120130,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN6,        0xf0120134,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI7,    0xf0120138,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN7,        0xf012013c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI8,    0xf0120140,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN8,        0xf0120144,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI9,    0xf0120148,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN9,        0xf012014c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI10,   0xf0120150,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN10,       0xf0120154,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI11,   0xf0120158,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN11,       0xf012015c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI12,   0xf0120160,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN12,       0xf0120164,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI13,   0xf0120168,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN13,       0xf012016c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI14,   0xf0120170,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN14,       0xf0120174,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI15,   0xf0120178,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN15,       0xf012017c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI16,   0xf0120180,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN16,       0xf0120184,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI17,   0xf0120188,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN17,       0xf012018c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI18,   0xf0120190,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN18,       0xf0120194,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI19,   0xf0120198,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN19,       0xf012019c,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI20,   0xf01201a0,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN20,       0xf01201a4,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI21,   0xf01201a8,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN21,       0xf01201ac,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI22,   0xf01201b0,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN22,       0xf01201b4,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI23,   0xf01201b8,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN23,       0xf01201bc,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI24,   0xf01201c0,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN24,       0xf01201c4,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI25,   0xf01201c8,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN25,       0xf01201cc,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI26,   0xf01201d0,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN26,       0xf01201d4,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI27,   0xf01201d8,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN27,       0xf01201dc,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI28,   0xf01201e0,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN28,       0xf01201e4,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI29,   0xf01201e8,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN29,       0xf01201ec,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI30,   0xf01201f0,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN30,       0xf01201f4,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CAM_VPIVCI31,   0xf01201f8,__READ_WRITE,__cam_vpivcin_bits);
__IO_REG32_BIT(__CAM_CN31,       0xf01201fc,__READ_WRITE,__cam_cnn_bits);
__IO_REG32_BIT(__CONFIGURATION,  0xf0120200,__READ_WRITE,__configuration_bits);
__IO_REG32_BIT(__EXT_CMBASE,     0xf0120204,__READ_WRITE,__ext_cmbase_bits);

/***************************************************************************
 **
 **  USB Host
 **
 ***************************************************************************/
__IO_REG32_BIT(__HCREVISION,        0xf0100000,__READ       ,__hcrevision_bits);
__IO_REG32_BIT(__HCCONTROL,         0xf0100004,__READ_WRITE ,__hccontrol_bits);
__IO_REG32_BIT(__HCCOMMANDSTATUS,   0xf0100008,__READ_WRITE ,__hccommandstatus_bits);
__IO_REG32_BIT(__HCINTERRUPTSTATUS, 0xf010000C,__READ_WRITE ,__hcinterruptstatus_bits);
__IO_REG32_BIT(__HCINTERRUPTENABLE, 0xf0100010,__READ_WRITE ,__hcinterruptenable_bits);
__IO_REG32_BIT(__HCINTERRUPTDISABLE,0xf0100014,__READ_WRITE ,__hcinterruptenable_bits);
__IO_REG32_BIT(__HCHCCA,            0xf0100018,__READ_WRITE ,__hchcca_bits);
__IO_REG32_BIT(__HCPERIODCURRENTED, 0xf010001C,__READ_WRITE ,__hcperiodcurrented_bits);
__IO_REG32_BIT(__HCCONTROLHEADED,   0xf0100020,__READ_WRITE ,__hccontrolheaded_bits);
__IO_REG32_BIT(__HCCONTROLCURRENTED,0xf0100024,__READ_WRITE ,__hccontrolcurrented_bits);
__IO_REG32_BIT(__HCBULKHEADED,      0xf0100028,__READ_WRITE ,__hcbulkheaded_bits);
__IO_REG32_BIT(__HCBULKCURRENTED,   0xf010002C,__READ_WRITE ,__hcbulkcurrented_bits);
__IO_REG32_BIT(__HCDONEHEAD,        0xf0100030,__READ_WRITE ,__hcdonehead_bits);
__IO_REG32_BIT(__HCFMINTERVAL,      0xf0100034,__READ_WRITE ,__hcfminterval_bits);
__IO_REG32_BIT(__HCFMREMAINING,     0xf0100038,__READ_WRITE ,__hcfmremaining_bits);
__IO_REG16(    __HCFMNUMBER,        0xf010003C,__READ_WRITE);
__IO_REG32_BIT(__HCPERIODICSTART,   0xf0100040,__READ_WRITE ,__hcperiodicstart_bits);
__IO_REG32_BIT(__HCLSTHRESHOLD,     0xf0100044,__READ_WRITE ,__hclsthreshold_bits);
__IO_REG32_BIT(__HCRHDESCRIPTORA,   0xf0100048,__READ_WRITE ,__hcrhdescriptora_bits);
__IO_REG32_BIT(__HCRHDESCRIPTORB,   0xf010004C,__READ_WRITE ,__hcrhdescriptorb_bits);
__IO_REG32_BIT(__HCRHSTATUS,        0xf0100050,__READ_WRITE ,__hcrhstatus_bits);
__IO_REG32_BIT(__HCRHPORTSTATUS1,   0xf0100054,__READ_WRITE ,__hcrhportstatus_bits);
__IO_REG32_BIT(__HCRHPORTSTATUS2,   0xf0100058,__READ_WRITE ,__hcrhportstatus_bits);

/***************************************************************************
 **
 **  USB Special REG
 **
 ***************************************************************************/
__IO_REG32_BIT(__USBFA,     0xf00e0000,__READ_WRITE,__usbfa_bits);
__IO_REG32_BIT(__USBPM,     0xf00e0004,__READ_WRITE,__usbpm_bits);
__IO_REG32_BIT(__USBINTR,   0xf00e0008,__READ_WRITE,__usbintr_bits);
__IO_REG32_BIT(__USBINTRE,  0xf00e000c,__READ_WRITE,__usbintre_bits);
__IO_REG32_BIT(__USBFN,     0xf00e0010,__READ      ,__usbfn_bits);
__IO_REG32_BIT(__USBDISCONN,0xf00e0014,__READ_WRITE,__usbdisconn_bits);
__IO_REG32_BIT(__USBEP0CSR, 0xf00e0018,__READ_WRITE,__usbep0csr_bits);
__IO_REG32_BIT(__USBEP1CSR, 0xf00e001c,__READ_WRITE,__usbep1csr_bits);
__IO_REG32_BIT(__USBEP2CSR, 0xf00e0020,__READ_WRITE,__usbep1csr_bits);
__IO_REG32_BIT(__USBEP3CSR, 0xf00e0024,__READ_WRITE,__usbep3csr_bits);
__IO_REG32_BIT(__USBEP4CSR, 0xf00e0028,__READ_WRITE,__usbep3csr_bits);
__IO_REG32_BIT(__USBWCEP0,  0xf00e0030,__READ_WRITE,__usbwcep0_bits);
__IO_REG32_BIT(__USBWCEP1,  0xf00e0034,__READ_WRITE,__usbwcep1_bits);
__IO_REG32_BIT(__USBWCEP2,  0xf00e0038,__READ_WRITE,__usbwcep2_bits);
__IO_REG32_BIT(__USBWCEP3,  0xf00e003c,__READ_WRITE,__usbwcep3_bits);
__IO_REG32_BIT(__USBWCEP4,  0xf00e0040,__READ_WRITE,__usbwcep4_bits);
__IO_REG32(    __USBEP0,    0xf00e0080,__READ_WRITE);
__IO_REG32(    __USBEP1,    0xf00e0084,__READ_WRITE);
__IO_REG32(    __USBEP2,    0xf00e0088,__READ_WRITE);
__IO_REG32(    __USBEP3,    0xf00e008c,__READ_WRITE);
__IO_REG32(    __USBEP4,    0xf00e0090,__READ_WRITE);

/***************************************************************************
 **
 **  DES/3DES
 **
 ***************************************************************************/
__IO_REG32_BIT(__DESCON,    0xf0090000,__READ_WRITE,__descon_bits);
__IO_REG32_BIT(__DESSTA,    0xf0090004,__READ,      __dessta_bits);
__IO_REG32_BIT(__DESINT,    0xf0090008,__READ_WRITE,__desint_bits);
__IO_REG32_BIT(__DESRUN,    0xf009000c,__WRITE,     __desrun_bits);
__IO_REG32(    __DESKEY1L,  0xf0090010,__READ_WRITE);
__IO_REG32(    __DESKEY1R,  0xf0090014,__READ_WRITE);
__IO_REG32(    __DESKEY2L,  0xf0090018,__READ_WRITE);
__IO_REG32(    __DESKEY2R,  0xf009001c,__READ_WRITE);
__IO_REG32(    __DESKEY3L,  0xf0090020,__READ_WRITE);
__IO_REG32(    __DESKEY3R,  0xf0090024,__READ_WRITE);
__IO_REG32(    __DESIVL,    0xf0090028,__READ_WRITE);
__IO_REG32(    __DESIVR,    0xf009002c,__READ_WRITE);
__IO_REG32(    __DESINFIFO, 0xf0090030,__WRITE);
__IO_REG32(    __DESOUTFIFO,0xf0090034,__READ);

/***************************************************************************
 **
 **  GDMA
 **
 ***************************************************************************/
__IO_REG32_BIT(__DPRIC,0xf0051000,__READ_WRITE,__dpric_bits);
__IO_REG32_BIT(__DPRIF,0xf0052000,__READ_WRITE,__dprif_bits);
__IO_REG32_BIT(__DPRIR,0xf0053000,__READ_WRITE,__dprir_bits);
__IO_REG32_BIT(__DCON0,0xf0050000,__READ_WRITE,__dcon_bits);
__IO_REG32(    __DSAR0,0xf0050004,__READ_WRITE);
__IO_REG32(    __DDAR0,0xf0050008,__READ_WRITE);
__IO_REG32_BIT(__DTCR0,0xf005000c,__READ_WRITE,__dtcr_bits);
__IO_REG32_BIT(__DRER0,0xf0050010,__WRITE,     __drer_bits);
__IO_REG32_BIT(__DIPR0,0xf0050014,__READ_WRITE,__dipr_bits);

__IO_REG32_BIT(__DCON1,0xf0050020,__READ_WRITE,__dcon_bits);
__IO_REG32(    __DSAR1,0xf0050024,__READ_WRITE);
__IO_REG32(    __DDAR1,0xf0050028,__READ_WRITE);
__IO_REG32_BIT(__DTCR1,0xf005002c,__READ_WRITE,__dtcr_bits);
__IO_REG32_BIT(__DRER1,0xf0050030,__WRITE,     __drer_bits);
__IO_REG32_BIT(__DIPR1,0xf0050034,__READ_WRITE,__dipr_bits);

__IO_REG32_BIT(__DCON2,0xf0050040,__READ_WRITE,__dcon_bits);
__IO_REG32(    __DSAR2,0xf0050044,__READ_WRITE);
__IO_REG32(    __DDAR2,0xf0050048,__READ_WRITE);
__IO_REG32_BIT(__DTCR2,0xf005004c,__READ_WRITE,__dtcr_bits);
__IO_REG32_BIT(__DRER2,0xf0050050,__WRITE,     __drer_bits);
__IO_REG32_BIT(__DIPR2,0xf0050054,__READ_WRITE,__dipr_bits);

__IO_REG32_BIT(__DCON3,0xf0050060,__READ_WRITE,__dcon_bits);
__IO_REG32(    __DSAR3,0xf0050064,__READ_WRITE);
__IO_REG32(    __DDAR3,0xf0050068,__READ_WRITE);
__IO_REG32_BIT(__DTCR3,0xf005006c,__READ_WRITE,__dtcr_bits);
__IO_REG32_BIT(__DRER3,0xf0050070,__WRITE,     __drer_bits);
__IO_REG32_BIT(__DIPR3,0xf0050074,__READ_WRITE,__dipr_bits);

__IO_REG32_BIT(__DCON4,0xf0050080,__READ_WRITE,__dcon_bits);
__IO_REG32(    __DSAR4,0xf0050084,__READ_WRITE);
__IO_REG32(    __DDAR4,0xf0050088,__READ_WRITE);
__IO_REG32_BIT(__DTCR4,0xf005008c,__READ_WRITE,__dtcr_bits);
__IO_REG32_BIT(__DRER4,0xf0050090,__WRITE,     __drer_bits);
__IO_REG32_BIT(__DIPR4,0xf0050094,__READ_WRITE,__dipr_bits);

__IO_REG32_BIT(__DCON5,0xf00500a0,__READ_WRITE,__dcon_bits);
__IO_REG32(    __DSAR5,0xf00500a4,__READ_WRITE);
__IO_REG32(    __DDAR5,0xf00500a8,__READ_WRITE);
__IO_REG32_BIT(__DTCR5,0xf00500ac,__READ_WRITE,__dtcr_bits);
__IO_REG32_BIT(__DRER5,0xf00500b0,__WRITE,     __drer_bits);
__IO_REG32_BIT(__DIPR5,0xf00500b4,__READ_WRITE,__dipr_bits);

/***************************************************************************
 **
 **  SIO/(CONSOLE UART)
 **
 ***************************************************************************/
__IO_REG32_BIT(__CUCON,  0xf0060000,__READ_WRITE,__cucon_bits);
__IO_REG32_BIT(__CUSTAT, 0xf0060004,__READ_WRITE,__custat_bits);
__IO_REG32_BIT(__CUINT,  0xf0060008,__READ_WRITE,__cuint_bits);
__IO_REG8(     __CUTXBUF,0xf006000c,__WRITE);
__IO_REG8(     __CURXBUF,0xf0060010,__READ);
__IO_REG32_BIT(__CUBRD,  0xf0060014,__READ_WRITE,__cubrd_bits);
__IO_REG32_BIT(__CUCHAR1,0xf0060018,__READ_WRITE,__cuchar1_bits);
__IO_REG32_BIT(__CUCHAR2,0xf006001c,__READ_WRITE,__cuchar2_bits);

/***************************************************************************
 **
 **  SIO/(HS UART)
 **
 ***************************************************************************/
__IO_REG32_BIT(__HUCON0,  0xf0070000,__READ_WRITE,__hucon_bits);
__IO_REG32_BIT(__HUSTAT0, 0xf0070004,__READ_WRITE,__hustat_bits);
__IO_REG32_BIT(__HUINT0,  0xf0070008,__READ_WRITE,__huint_bits);
__IO_REG8(     __HUTXBUF0,0xf007000c,__WRITE);
__IO_REG8(     __HURXBUF0,0xf0070010,__READ);
__IO_REG32_BIT(__HUBRD0,  0xf0070014,__READ_WRITE,__hubrd_bits);
__IO_REG32_BIT(__HUCHAR01,0xf0070018,__READ_WRITE,__huchar1_bits);
__IO_REG32_BIT(__HUCHAR02,0xf007001c,__READ_WRITE,__huchar2_bits);
__IO_REG32_BIT(__HUABB0,  0xf0070020,__READ_WRITE,__huabb_bits);
__IO_REG32_BIT(__HUABT0,  0xf0070024,__READ_WRITE,__huabt_bits);

__IO_REG32_BIT(__HUCON1,  0xf0080000,__READ_WRITE,__hucon_bits);
__IO_REG32_BIT(__HUSTAT1, 0xf0080004,__READ_WRITE,__hustat_bits);
__IO_REG32_BIT(__HUINT1,  0xf0080008,__READ_WRITE,__huint_bits);
__IO_REG8(     __HUTXBUF1,0xf008000c,__WRITE);
__IO_REG8(     __HURXBUF1,0xf0080010,__READ);
__IO_REG32_BIT(__HUBRD1,  0xf0080014,__READ_WRITE,__hubrd_bits);
__IO_REG32_BIT(__HUCHAR11,0xf0080018,__READ_WRITE,__huchar1_bits);
__IO_REG32_BIT(__HUCHAR12,0xf008001c,__READ_WRITE,__huchar2_bits);
__IO_REG32_BIT(__HUABB1,  0xf0080020,__READ_WRITE,__huabb_bits);
__IO_REG32_BIT(__HUABT1,  0xf0080024,__READ_WRITE,__huabt_bits);

/***************************************************************************
 **
 **  I/O
 **
 ***************************************************************************/
__IO_REG32_BIT(__IOPMODE1,    0xf0030000,__READ_WRITE,__iopmode1_bits);
__IO_REG32_BIT(__IOPMODE2,    0xf0030004,__READ_WRITE,__iopmode2_bits);
__IO_REG32_BIT(__IOPCON1,     0xf0030008,__READ_WRITE,__iopcon1_bits);
__IO_REG32_BIT(__IOPCON2,     0xf003000c,__READ_WRITE,__iopcon2_bits);
__IO_REG32_BIT(__IOPGDMA,     0xf0030010,__READ_WRITE,__iopgdma_bits);
__IO_REG32_BIT(__IOPEXTINT,   0xf0030014,__READ_WRITE,__iopextint_bits);
__IO_REG32_BIT(__IOPEXTINTPND,0xf0030018,__READ_WRITE,__iopextintpnd_bits);
__IO_REG32_BIT(__IOPDATA1,    0xf003001c,__READ_WRITE,__iopmode1_bits);
__IO_REG32_BIT(__IOPDATA2,    0xf0030020,__READ_WRITE,__iopmode2_bits);
__IO_REG32_BIT(__IOPDRV1,     0xf0030024,__READ_WRITE,__iopmode1_bits);
__IO_REG32_BIT(__IOPDRV2,     0xf0030028,__READ_WRITE,__iopmode2_bits);

/***************************************************************************
 **
 **  ICR
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTMOD,       0xf0140000,__READ_WRITE,__intmod_bits);
__IO_REG32_BIT(__EXTMOD,       0xf0140004,__READ_WRITE,__extmod_bits);
__IO_REG32_BIT(__INTMASK,      0xf0140008,__READ_WRITE,__intmod_bits);
__IO_REG32_BIT(__EXTMASK,      0xf014000c,__READ_WRITE,__extmod_bits);
__IO_REG32_BIT(__INTPRIOR0,    0xf0140020,__READ_WRITE,__intprior0_bits);
__IO_REG32_BIT(__INTPRIOR1,    0xf0140024,__READ_WRITE,__intprior1_bits);
__IO_REG32_BIT(__INTPRIOR2,    0xf0140028,__READ_WRITE,__intprior2_bits);
__IO_REG32_BIT(__INTPRIOR3,    0xf014002c,__READ_WRITE,__intprior3_bits);
__IO_REG32_BIT(__INTPRIOR4,    0xf0140030,__READ_WRITE,__intprior4_bits);
__IO_REG32_BIT(__INTPRIOR5,    0xf0140034,__READ_WRITE,__intprior5_bits);
__IO_REG32_BIT(__INTPRIOR6,    0xf0140038,__READ_WRITE,__intprior6_bits);
__IO_REG32_BIT(__INTPRIOR7,    0xf014003c,__READ_WRITE,__intprior7_bits);
__IO_REG32_BIT(__INTPRIOR8,    0xf0140040,__READ_WRITE,__intprior8_bits);
__IO_REG32(    __INTOFFSET_FIQ,0xf0140018,__READ);
__IO_REG32(    __INTOFFSET_IRQ,0xf014001c,__READ);
__IO_REG32_BIT(__IPRIORHI,     0xf0140010,__READ,      __ipriorhi_bits);
__IO_REG32_BIT(__IPRIORLO,     0xf0140014,__READ,      __ipriorlo_bits);
__IO_REG32_BIT(__INTTST,       0xf0140048,__READ_WRITE,__intmod_bits);
__IO_REG32_BIT(__EXTTST,       0xf014004c,__READ_WRITE,__exttst_bits);

/***************************************************************************
 **
 **  TIMERS
 **
 ***************************************************************************/
__IO_REG32_BIT(__TMOD,  0xf0040000,__READ_WRITE,__tmod_bits);
__IO_REG32(    __TDATA0,0xf0040010,__READ_WRITE);
__IO_REG32(    __TDATA1,0xf0040018,__READ_WRITE);
__IO_REG32(    __TDATA2,0xf0040020,__READ_WRITE);
__IO_REG32(    __TDATA3,0xf0040028,__READ_WRITE);
__IO_REG32(    __TDATA4,0xf0040030,__READ_WRITE);
__IO_REG32(    __TDATA5,0xf0040038,__READ_WRITE);
__IO_REG32(    __TCNT0, 0xf0040014,__READ_WRITE);
__IO_REG32(    __TCNT1, 0xf004001c,__READ_WRITE);
__IO_REG32(    __TCNT2, 0xf0040024,__READ_WRITE);
__IO_REG32(    __TCNT3, 0xf004002c,__READ_WRITE);
__IO_REG32(    __TCNT4, 0xf0040034,__READ_WRITE);
__IO_REG32(    __TCNT5, 0xf004003c,__READ_WRITE);
__IO_REG32_BIT(__TIC,   0xf0040004,__READ_WRITE,__tic_bits);
__IO_REG32_BIT(__WDT,   0xf0040008,__READ_WRITE,__wdt_bits);

/***************************************************************************
 **
 **  MINI-PCI
 **
 ***************************************************************************/
__IO_REG32_BIT(__PCIHID   ,0xf0110000,__READ_WRITE,__pcihid_bits);
__IO_REG32_BIT(__PCIHSC   ,0xf0110004,__READ_WRITE,__pcihsc_bits);
__IO_REG32_BIT(__PCIHCODE ,0xf0110008,__READ_WRITE,__pcihcode_bits);
__IO_REG32_BIT(__PCIHLINE ,0xf011000c,__READ_WRITE,__pcihline_bits);
__IO_REG32_BIT(__PCIHBAR0 ,0xf0110010,__READ_WRITE,__pcihbar0_1_bits);
__IO_REG32_BIT(__PCIHBAR1 ,0xf0110014,__READ_WRITE,__pcihbar0_1_bits);
__IO_REG32_BIT(__PCIHBAR2 ,0xf0110018,__READ_WRITE,__pcihbar2_bits);
__IO_REG32_BIT(__PCIHCISP  ,0xf0110028,__READ_WRITE,__pcihcisp_bits);
__IO_REG32_BIT(__PCIHSSID ,0xf011002c,__READ_WRITE,__pcihssid_bits);
__IO_REG32_BIT(__PCIHCAP  ,0xf0110034,__READ_WRITE,__pcihcap_bits);
__IO_REG32_BIT(__PCIHLTIT ,0xf011003c,__READ_WRITE,__pcihltit_bits);
__IO_REG32_BIT(__PCIHTIMER,0xf0110040,__READ_WRITE,__pcihtimer_bits);
__IO_REG32_BIT(__PCIHPMR0 ,0xf01100dc,__READ_WRITE,__pcihpmr0_bits);
__IO_REG32_BIT(__PCIHPMR1 ,0xf01100e0,__READ_WRITE,__pcihpmr1_bits);
__IO_REG32_BIT(__PCICON   ,0xf0110100,__READ_WRITE,__pcicon_bits);
__IO_REG32_BIT(__PCISET   ,0xf0110104,__READ_WRITE,__pciset_bits);
__IO_REG32_BIT(__PCIINTEN ,0xf0110108,__READ_WRITE,__pciinten_bits);
__IO_REG32_BIT(__PCIINTST ,0xf011010c,__READ_WRITE,__pciintst_bits);
__IO_REG32(    __PCIINTAD ,0xf0110110,__READ_WRITE);
__IO_REG32_BIT(__PCIBATAPM,0xf0110114,__READ_WRITE,__pcibatapm_bits);
__IO_REG32_BIT(__PCIBATAPI,0xf0110118,__READ_WRITE,__pcibatapi_bits);
__IO_REG32_BIT(__PCIRCC   ,0xf011011c,__READ_WRITE,__pcircc_bits);
__IO_REG32_BIT(__PCIDIAG0 ,0xf0110120,__READ_WRITE,__pcidiag0_bits);
__IO_REG32_BIT(__PCIDIAG1 ,0xf0110124,__READ_WRITE,__pcidiag1_bits);
__IO_REG32_BIT(__PCIBELAP ,0xf0110128,__READ_WRITE,__pcibelap_bits);
__IO_REG32_BIT(__PCIBELPA ,0xf011012c,__READ_WRITE,__pcibelpa_bits);
__IO_REG32_BIT(__PCIMAIL0 ,0xf0110130,__READ_WRITE,__pcimail_bits);
__IO_REG32_BIT(__PCIMAIL1 ,0xf0110134,__READ_WRITE,__pcimail_bits);
__IO_REG32_BIT(__PCIMAIL2 ,0xf0110138,__READ_WRITE,__pcimail_bits);
__IO_REG32_BIT(__PCIMAIL3 ,0xf011013c,__READ_WRITE,__pcimail_bits);
__IO_REG32_BIT(__PCIBATPA0,0xf0110140,__READ_WRITE,__pcibatpa0_bits);
__IO_REG32_BIT(__PCIBAM0  ,0xf0110144,__READ_WRITE,__pcibam0_bits);
__IO_REG32_BIT(__PCIBATPA1,0xf0110148,__READ_WRITE,__pcibatpa1_bits);
__IO_REG32_BIT(__PCIBAM1  ,0xf011014c,__READ_WRITE,__pcibam1_bits);
__IO_REG32_BIT(__PCIBATPA2,0xf0110150,__READ_WRITE,__pcibatpa2_bits);
__IO_REG32(    __PCIBAM2  ,0xf0110154,__READ);
__IO_REG32_BIT(__PCISWAP  ,0xf0110158,__READ_WRITE,__pciswap_bits);
__IO_REG32_BIT(__PCCARDEVT,0xf0110160,__READ_WRITE,__pccardevt_bits);
__IO_REG32_BIT(__PCCARDEVM,0xf0110164,__READ_WRITE,__pccardevm_bits);
__IO_REG32_BIT(__PCCARDPRS,0xf0110168,__READ      ,__pccardprs_bits);
__IO_REG32_BIT(__PCCARDFEV,0xf011016c,__WRITE     ,__pccardfev_bits);
__IO_REG32_BIT(__PCCARDCON,0xf0110170,__READ_WRITE,__pccardcon_bits);
__IO_REG32_BIT(__PCCARD16C,0xf0110174,__READ_WRITE,__pccard16c_bits);
__IO_REG32_BIT(__PCCARD16M,0xf0110178,__READ_WRITE,__pccard16m_bits);
__IO_REG32_BIT(__PCCARD16I,0xf011017c,__READ_WRITE,__pccard16m_bits);
__IO_REG32_BIT(__PDMACON0 ,0xf0110180,__READ_WRITE,__pdmacon0_1_bits);
__IO_REG32(    __PDMASRC0 ,0xf0110184,__READ_WRITE);
__IO_REG32(    __PDMADST0 ,0xf0110188,__READ_WRITE);
__IO_REG32_BIT(__PDMACNT0 ,0xf011018c,__READ_WRITE,__pdmacnt0_1_bits);
__IO_REG32_BIT(__PDMARUN0 ,0xf0110190,__READ_WRITE,__pdmarun0_1_bits);
__IO_REG32_BIT(__PDMACON1 ,0xf01101a0,__READ_WRITE,__pdmacon0_1_bits);
__IO_REG32(    __PDMASRC1 ,0xf01101a4,__READ_WRITE);
__IO_REG32(    __PDMADST1 ,0xf01101a8,__READ_WRITE);
__IO_REG32_BIT(__PDMACNT1 ,0xf01101ac,__READ_WRITE,__pdmacnt0_1_bits);
__IO_REG32_BIT(__PDMARUN1 ,0xf01101b0,__READ_WRITE,__pdmarun0_1_bits);


/* Assembler specific declarations  ****************************************/
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
 **  S3C2510A interrupt sources
 **
 ***************************************************************************/
#define INT_EXT0      0  /* external interrupt 0             */
#define INT_EXT1      1  /* external interrupt 1             */
#define INT_EXT2      2  /* external interrupt 2             */
#define INT_EXT3      3  /* external interrupt 3             */
#define INT_U0TINT    4  /* uart0 transmit interrupt         */
#define INT_U0RERR    5  /* uart0 receive & error interrupt  */
#define INT_U1T       6  /* uart1 transmit interrupt         */
#define INT_U1RERR    7  /* uart1 receive & error interrupt  */
#define INT_GDMA0     8  /* GDMA channel 0 interrupt         */
#define INT_GDMA1     9  /* GDMA channel 1 interrupt         */
#define INT_TIMER0   10  /* timer 0 interrupt                */
#define INT_TIMER1   11  /* timer 1 interrupt                */
#define INT_HDLCTXA  12  /* HDLC channel A TX interrupt      */
#define INT_HDLCRXA  13  /* HDLC channel A Rx interrupt      */
#define INT_HDLCTXB  14  /* HDLC channel B TX interrupt      */
#define INT_HDLCRXB  15  /* HDLC channel B Rx interrupt      */
#define INT_ECBDMATx 16  /* Eternet controller BDMA Tx intrrupt*/
#define INT_ECBDMARx 17  /* Eternet controller BDMA Rx intrrupt*/
#define INT_ECMACTx  18  /* Eternet controller MAC  Tx intrrupt*/
#define INT_ECMACRx  19  /* Eternet controller MAC  Rx intrrupt*/
#define INT_i2cbus   20  /* i2 C-bus interrupt                 */



#endif    /* __S3C2510A_H */
