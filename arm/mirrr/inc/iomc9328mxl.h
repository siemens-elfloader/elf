/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Freescale MC9328MXL
 **
 **    Used with ARM IAR c/c++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.2 $
 **
 ***************************************************************************/

#ifndef __IOMC9328MXL_H
#define __IOMC9328MXL_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"


/***************************************************************************
 ***************************************************************************
 **
 **    MC9328MXL SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Reset Source Register */
typedef struct {
  __REG32 EXR              : 1;
  __REG32 WDR              : 1;
  __REG32                  :30;
} __rsr_bits;

/* AIPIx Peripheral Size Register 0 */
typedef struct {
  __REG32                  : 1;
  __REG32 MOD_EN_L         :15;
  __REG32                  :16;
} __aipipsr0x_bits;

/* AIPIx Peripheral Size Register 1 */
typedef struct {
  __REG32                  : 1;
  __REG32 MOD_EN_U         :15;
  __REG32                  :16;
} __aipipsr1x_bits;

/* AIPIx Peripheral Access Register */
typedef struct {
  __REG32                  : 1;
  __REG32 ACCESS           :15;
  __REG32                  :16;
} __aipiparx_bits;

/* AIPIx Peripheral Control Register */
typedef struct {
  __REG32                  : 1;
  __REG32 ACCESSMODE       :15;
  __REG32                  :16;
} __aipipcrx_bits;

/* AIPIx Time-Out Status Register */
typedef struct {
  __REG32                  : 1;
  __REG32 MODULE_EN        :15;
  __REG32 BE1              : 1;
  __REG32 BE2              : 1;
  __REG32 BE3              : 1;
  __REG32 BE4              : 1;
  __REG32 ADDR             :10;
  __REG32 RW               : 1;
  __REG32 TO               : 1;
} __aipitsrx_bits;

/* Function Multiplexing Control Register */
typedef struct {
  __REG32 SDCS0_SEL        : 1;
  __REG32 SDCS1_SEL        : 1;
  __REG32 EXT_BR_EN        : 1;
  __REG32 SSI_TXCLK_SEL    : 1;
  __REG32 SSI_TXFS_SEL     : 1;
  __REG32 SSI_RXDAT_SEL    : 1;
  __REG32 SSI_RXCLK_SEL    : 1;
  __REG32 SSI_RXFS_SEL     : 1;
  __REG32 SPI2_RXD_SEL     : 1;
  __REG32                  :23;
} __fmcr_bits;

/* Global Peripheral Control Register */
typedef struct {
  __REG32 CSI_PROT_EN      : 1;
  __REG32 MMA_PROT_EN      : 1;
  __REG32 HCLK_GATING_EN   : 1;
  __REG32 IP_CLK_GATING_EN : 1;
  __REG32 DS_DATA          : 2;
  __REG32 DS_ADDR          : 2;
  __REG32 DS_CNTL          : 2;
  __REG32 DS_SLOW          : 2;
  __REG32                  : 3;
  __REG32 MEMC_TEST_EN     : 1;
  __REG32                  :16;
} __gpcr_bits;

/* Global Clock Control Register */
typedef struct {
  __REG32 USBD_CLK_EN      : 1;
  __REG32 MMA_CLK_EN       : 1;
  __REG32 CSI_CLK_EN       : 1;
  __REG32 DMA_CLK_EN       : 1;
  __REG32 BROM_CLK_EN      : 1;
  __REG32                  :27;
} __gccr_bits;

/* Interrupt Control Register */
typedef struct {
  __REG32                  :19;
  __REG32 FIAD             : 1;
  __REG32 NIAD             : 1;
  __REG32                  :11;
} __intcntl_bits;

/* Normal Interrupt Mask Register */
typedef struct {
  __REG32 NIMASK           : 5;
  __REG32                  :27;
} __nimask_bits;

/* Interrupt Enable Number Register */
typedef struct {
  __REG32 ENNUM            : 6;
  __REG32                  :26;
} __intennum_bits;

/* Interrupt Disable Number Register */
typedef struct {
  __REG32 DISNUM           : 6;
  __REG32                  :26;
} __intdisnum_bits;

/* Normal Interrupt Priority Level Register 7 */
typedef struct {
  __REG32 NIPR56           : 4;
  __REG32 NIPR57           : 4;
  __REG32 NIPR58           : 4;
  __REG32 NIPR59           : 4;
  __REG32 NIPR60           : 4;
  __REG32 NIPR61           : 4;
  __REG32 NIPR62           : 4;
  __REG32 NIPR63           : 4;
} __nipriority7_bits;

/* Normal Interrupt Priority Level Register 6 */
typedef struct {
  __REG32 NIPR48           : 4;
  __REG32 NIPR49           : 4;
  __REG32 NIPR50           : 4;
  __REG32 NIPR51           : 4;
  __REG32 NIPR52           : 4;
  __REG32 NIPR53           : 4;
  __REG32 NIPR54           : 4;
  __REG32 NIPR55           : 4;
} __nipriority6_bits;

/* Normal Interrupt Priority Level Register 5 */
typedef struct {
  __REG32 NIPR40           : 4;
  __REG32 NIPR41           : 4;
  __REG32 NIPR42           : 4;
  __REG32 NIPR43           : 4;
  __REG32 NIPR44           : 4;
  __REG32 NIPR45           : 4;
  __REG32 NIPR46           : 4;
  __REG32 NIPR47           : 4;
} __nipriority5_bits;

/* Normal Interrupt Priority Level Register 4 */
typedef struct {
  __REG32 NIPR32           : 4;
  __REG32 NIPR33           : 4;
  __REG32 NIPR34           : 4;
  __REG32 NIPR35           : 4;
  __REG32 NIPR36           : 4;
  __REG32 NIPR37           : 4;
  __REG32 NIPR38           : 4;
  __REG32 NIPR39           : 4;
} __nipriority4_bits;

/* Normal Interrupt Priority Level Register 3 */
typedef struct {
  __REG32 NIPR24           : 4;
  __REG32 NIPR25           : 4;
  __REG32 NIPR26           : 4;
  __REG32 NIPR27           : 4;
  __REG32 NIPR28           : 4;
  __REG32 NIPR29           : 4;
  __REG32 NIPR30           : 4;
  __REG32 NIPR31           : 4;
} __nipriority3_bits;

/* Normal Interrupt Priority Level Register 2 */
typedef struct {
  __REG32 NIPR16           : 4;
  __REG32 NIPR17           : 4;
  __REG32 NIPR18           : 4;
  __REG32 NIPR19           : 4;
  __REG32 NIPR20           : 4;
  __REG32 NIPR21           : 4;
  __REG32 NIPR22           : 4;
  __REG32 NIPR23           : 4;
} __nipriority2_bits;

/* Normal Interrupt Priority Level Register 1 */
typedef struct {
  __REG32 NIPR8            : 4;
  __REG32 NIPR9            : 4;
  __REG32 NIPR10           : 4;
  __REG32 NIPR11           : 4;
  __REG32 NIPR12           : 4;
  __REG32 NIPR13           : 4;
  __REG32 NIPR14           : 4;
  __REG32 NIPR15           : 4;
} __nipriority1_bits;

/* Normal Interrupt Priority Level Register 0 */
typedef struct {
  __REG32 NIPR0            : 4;
  __REG32 NIPR1            : 4;
  __REG32 NIPR2            : 4;
  __REG32 NIPR3            : 4;
  __REG32 NIPR4            : 4;
  __REG32 NIPR5            : 4;
  __REG32 NIPR6            : 4;
  __REG32 NIPR7            : 4;
} __nipriority0_bits;	

/* Normal Interrupt Vector and Status Register */
typedef struct {
  __REG32 NIPRILVL         :16;
  __REG32 NIVECTOR         :16;
} __nivecsr_bits;

/* Chip Select 0 Upper Control Register */
typedef struct {
  __REG32 EDC              : 4;
  __REG32 WWS              : 3;
  __REG32                  : 1;
  __REG32 WSC              : 6;
  __REG32 CNC              : 2;
  __REG32 DOL              : 4;
  __REG32 SYNC             : 1;
  __REG32 PME              : 1;
  __REG32 PSZ              : 2;
  __REG32 BCS              : 4;
  __REG32 BCD              : 2;
  __REG32                  : 2;
} __cs0u_bits;

/* Chip Select 0 Lower Control Register */
typedef struct {
  __REG32 CSEN             : 1;
  __REG32                  : 3;
  __REG32 WP               : 1;
  __REG32                  : 1;
  __REG32 SP               : 1;
  __REG32                  : 1;
  __REG32 DSZ              : 3;
  __REG32 EBC              : 1;
  __REG32 CSA              : 4;
  __REG32 WEN              : 4;
  __REG32 WEA              : 4;
  __REG32 OEN              : 4;
  __REG32 OEA              : 4;
} __cs0l_bits;

/* Chip Select 1 - 5 Upper Control Register */
typedef struct {
  __REG32 EDC              : 4;
  __REG32 WWS              : 3;
  __REG32                  : 1;
  __REG32 WSC              : 6;
  __REG32 CNC              : 2;
  __REG32 DOL              : 4;
  __REG32 SYNC             : 1;
  __REG32 PME              : 1;
  __REG32 PSZ              : 2;
  __REG32 BCS              : 4;
  __REG32 BCD              : 2;
  __REG32                  : 1;
  __REG32 DTACK_SEL        : 1;
} __csxu_bits;

/* Chip Select 1 - 5 Lower Control Register */
typedef struct {
  __REG32 CSEN             : 1;
  __REG32 PA               : 1;
  __REG32                  : 2;
  __REG32 WP               : 1;
  __REG32                  : 1;
  __REG32 SP               : 1;
  __REG32                  : 1;
  __REG32 DSZ              : 3;
  __REG32 EBC              : 1;
  __REG32 CSA              : 4;
  __REG32 WEN              : 4;
  __REG32 WEA              : 4;
  __REG32 OEN              : 4;
  __REG32 OEA              : 4;
} __csxl_bits;

/* EIM Configuration Register */
typedef struct {
  __REG32                  : 2;
  __REG32 BCM              : 1;
  __REG32                  :29;
} __eim_bits;

/* Clock Source Control Register */
typedef struct {
  __REG32 MPEN             : 1;
  __REG32 SPEN             : 1;
  __REG32                  : 8;
  __REG32 BCLK_DIV         : 4;
  __REG32                  : 1;
  __REG32 PRESC            : 1;
  __REG32 System_SEL       : 1;
  __REG32 OSC_EN           : 1;
  __REG32 CLK16_SEL        : 1;
  __REG32                  : 2;
  __REG32 MPLL_RESTART     : 1;
  __REG32 SPLL_RESTART     : 1;
  __REG32                  : 1;
  __REG32 SD_CNT           : 2;
  __REG32 USB_DIV          : 3;
  __REG32 CLKO_SEL         : 3;
} __cscr_bits;

/* Peripheral Clock Divider Register */
typedef struct {
  __REG32 PCLK_DIV1        : 4;
  __REG32 PCLK_DIV2        : 4;
  __REG32                  : 8;
  __REG32 PCLK_DIV3        : 7;
  __REG32                  : 9;
} __pcdr_bits;

/* MCU PLL Control Register 0 */
/* System PLL Control Register 0 */
typedef struct {
  __REG32 MFN              :10;
  __REG32 MFI              : 4;
  __REG32                  : 2;
  __REG32 MFD              :10;
  __REG32 PD               : 4;
  __REG32                  : 2;
} __mpctl0_bits;

/* MCU PLL and System Clock Control Register 1 */
typedef struct {
  __REG32                  : 6;
  __REG32 BRMO             : 1;
  __REG32                  :25;
} __mpctl1_bits; 

/* System PLL Control Register 1 */
typedef struct {
  __REG32                  : 6;
  __REG32 BRMO             : 1;
  __REG32                  : 8;
  __REG32 LF               : 1;
  __REG32                  :16;
} __spctl1_bits; 

/* DMA Control Register */
typedef struct {
  __REG32 DEN              : 1;
  __REG32 DRST             : 1;
  __REG32                  :30;
} __dcr_bits;

/* DMA Interrupt Status Register */
/* DMA Interrupt Mask Register */
/* DMA Burst Time-Out Status Register */
/* DMA Request Time-Out Status Register */
/* DMA Transfer Error Status Register */
/* DMA Buffer Overflow Status Register */
typedef struct {
  __REG32 CH0              : 1;
  __REG32 CH1              : 1;
  __REG32 CH2              : 1;
  __REG32 CH3              : 1;
  __REG32 CH4              : 1;
  __REG32 CH5              : 1;
  __REG32 CH6              : 1;
  __REG32 CH7              : 1;
  __REG32 CH8              : 1;
  __REG32 CH9              : 1;
  __REG32 CH10             : 1;
  __REG32                  :21;
} __disr_bits;

/* DMA Burst Time-Out Control Register */
typedef struct {
  __REG32 CNT              :15;
  __REG32 EN               : 1;
  __REG32                  :16;
} __dbtocr_bits;

/* W-Size Register A / B */
typedef struct {
  __REG32 WS               :16;
  __REG32                  :16;
} __wsrx_bits;

/* X-Size Register A / B */
typedef struct {
  __REG32 XS               :16;
  __REG32                  :16;
} __xsrx_bits;

/* Y-Size Register A / B */
typedef struct {
  __REG32 YS               :16;
  __REG32                  :16;
} __ysrx_bits;

/* Channel 0 - 10 Source Address Register */
typedef struct {
  __REG32 SA_0             : 1;
  __REG32 SA_1             : 1;
  __REG32 SA               :30;
} __sarx_bits;

/* Channel 0 - 10 Destination Address Register */
typedef struct {
  __REG32 DA_0             : 1;
  __REG32 DA_1             : 1;
  __REG32 DA               :30;
} __darx_bits;

/* Channel 0 - 10 Count Register */
typedef struct {
  __REG32 CNT              :24;
  __REG32                  : 8;
} __cntrx_bits;

/* Channel 0 - 10 Control Register */
typedef struct {
  __REG32 CEN              : 1;
  __REG32 FRC              : 1;
  __REG32 RPT              : 1;
  __REG32 REN              : 1;
  __REG32 SSIZ             : 2;
  __REG32 DSIZ             : 2;
  __REG32 MSEL             : 1;
  __REG32 MDIR             : 1;
  __REG32 SMOD             : 2;
  __REG32 DMOD             : 2;
  __REG32                  :18;
} __ccrx_bits;

/* Channel 0 - 10 Request Source Select Register */
typedef struct {
  __REG32 RSS              : 5;
  __REG32                  :27;
} __rssrx_bits;

/* Channel 0 – 10 Burst Length Register */
typedef struct {
  __REG32 BL               : 6;
  __REG32                  :26;
} __blrx_bits;

/* Channel 0 - 10 Request Time-Out Register */
/* Channel 0 - 10 Bus Utilization Control Register */
typedef union {
  //RTOR0 RTOR1 RTOR2 RTOR3 RTOR4 RTOR5 RTOR6 RTOR7 RTOR8 RTOR9 RTOR10
  struct {
    __REG32 CNT            :13;
    __REG32 PSC            : 1;
    __REG32 CLK            : 1;
    __REG32 EN             : 1;
    __REG32                :16;
  };
  //BUCR0 BUCR1 BUCR2 BUCR3 BUCR4 BUCR5 BUCR6 BUCR7 BUCR8 BUCR9 BUCR10
  struct {
    __REG32 CCNT           :16;
    __REG32                :16;
  };
} __rtorx_bits;

/* Watchdog Control Register */
typedef struct {
  __REG32 WDE              : 1;
  __REG32 WDEC             : 1;
  __REG32 SWR              : 1;
  __REG32 TMD              : 1;
  __REG32 WIE              : 1;
  __REG32                  : 3;
  __REG32 WT               : 7;
  __REG32 WHALT            : 1;
  __REG32                  :16;
} __wcr_bits;

/* Watchdog Service Register */
typedef struct {
  __REG32 WSR              :16;
  __REG32                  :16;
} __wsr_bits;

/* Watchdog Status Register */
typedef struct {
  __REG32 TOUT             : 1;
  __REG32                  : 7;
  __REG32 TINT             : 1;
  __REG32                  :23;
} __wstr_bits;

/* MMA MAC Module Register */
typedef struct {
  __REG32 MODENAB          : 1;
  __REG32                  :30;
  __REG32 RST              : 1; 
} __mmamacmod_bits;

/* MMA MAC Control Register */
typedef struct {
  __REG32 OPEN             : 1;
  __REG32 CACHEEN          : 1;
  __REG32 CACHECLR         : 1;
  __REG32                  :13;
  __REG32 YSIGNED          : 1;
  __REG32 YSIGNINI         : 1;
  __REG32 YSIGNALT         : 1;
  __REG32 Y_DATA_SEL       : 1;
  __REG32 YINDEXLOAD       : 1;
  __REG32 YINDEXINCR       : 1;
  __REG32 YINDEXCLR        : 1;
  __REG32 YMODIFYPRESET    : 1;
  __REG32 XSIGNED          : 1;
  __REG32 XSIGNINI         : 1;
  __REG32 XSIGNALT         : 1;
  __REG32 X_DATA_SEL       : 1;
  __REG32 XINDEXLOAD       : 1;
  __REG32 XINDEXINCR       : 1;
  __REG32 XINDEXCLR        : 1;
  __REG32 XMODIFYPRESET    : 1; 
} __mmamacctrl_bits;

/* MMA MAC Multiply Counter Register */
typedef struct {
  __REG32 MULTCOUNTER      :16;
  __REG32                  :16; 
} __mmamacmult_bits;


/* MMA MAC Accumulate Counter Register */
typedef struct {
  __REG32 ACCUCOUNTER      :16;
  __REG32                  :16; 
} __mmamacaccu_bits;

/* MMA MAC Interrupt Register */
/* MMA MAC Interrupt Mask Register */
typedef struct {
  __REG32 FIFOFULL         : 1;
  __REG32 FIFOHALF         : 1;
  __REG32 FIFOEMPT         : 1;
  __REG32 OPEND            : 1;
  __REG32 OPERROR          : 1; 
  __REG32                  :27; 
} __mmamacintr_bits;

/* MMA MAC FIFO Status Register */
typedef struct {
  __REG32 FIFOFULL         : 1;
  __REG32 FIFOHALF         : 1;
  __REG32 FIFOEMPT         : 1;
  __REG32                  :13;
  __REG32 FIFOCOUNT        : 5; 
  __REG32                  :11; 
} __mmamacfifostat_bits;

/* MMA MAC Burst Count Register */
typedef struct {
  __REG32 BURSTCOUNT       : 8;
  __REG32                  :24; 
} __mmamacburst_bits;

/* MMA MAC Bit Select Register */
typedef struct {
  __REG32 BITSEL           : 3;
  __REG32                  :29; 
} __mmamacbitsel_bits;

/* MMA MAC X Index Register */
typedef struct {
  __REG32 XINDEX           :16;
  __REG32                  :16; 
} __mmamacxindex_bits;

/* MMA MAC X Length Register */
typedef struct {
  __REG32 LENGTH           :16;
  __REG32 COLUMN           :16; 
} __mmamacxlength_bits;

/* MMA MAC X Modify Register */
typedef struct {
  __REG32 XMODIFY          :16;
  __REG32                  :16; 
} __mmamacxmodify_bits;

/* MMA MAC X Increment Register */
typedef struct {
  __REG32 XINCR            :16;
  __REG32                  :16; 
} __mmamacxincr_bits;

/* MMA MAC X Count Register */
typedef struct {
  __REG32 XCOUNT           :16;
  __REG32                  :16; 
} __mmamacxcount_bits;

/* MMA MAC Y Index Register */
typedef struct {
  __REG32 XINDEX           :16;
  __REG32                  :16; 
} __mmamacyindex_bits;

/* MMA MAC Y Length Register */
typedef struct {
  __REG32 LENGTH           :16;
  __REG32 COLUMN           :16; 
} __mmamacylength_bits;

/* MMA MAC Y Modify Register */
typedef struct {
  __REG32 YMODIFY          :16;
  __REG32                  :16; 
} __mmamacymodify_bits;

/* MMA MAC Y Increment Register */
typedef struct {
  __REG32 YINCR            :16;
  __REG32                  :16; 
} __mmamacyincr_bits;

/* MMA MAC Y Count Register */
typedef struct {
  __REG32 YCOUNT           :16;
  __REG32                  :16; 
} __mmamacycount_bits;

/* DCT/iDCT Control Register */
typedef struct {
  __REG32 DCTENA           : 1;
  __REG32 DCTIDCT          : 1;
  __REG32 ARMMCMSEL        : 2;
  __REG32 DCTBYPASS        : 1;
  __REG32 SWRST            : 1;
  __REG32 DCTCLKEN         : 1;
  __REG32 DCTXPOSE         : 1;
  __REG32 SEMAEN           : 1;
  __REG32 DATAINSHIFT      : 4;
  __REG32 DCT_HWORD_SWAP   : 1; 
  __REG32                  :18;
} __mmadctctrl_bits;

/* DCT/iDCT IRQ Enable Register */
typedef struct {
  __REG32 DCTCOMP          : 1;
  __REG32 DIIEN            : 1;
  __REG32 DOIEN            : 1;
  __REG32 DIDEN            : 1;
  __REG32 DODEN            : 1;
  __REG32 ERRINTREN        : 1; 
  __REG32                  :26;
} __mmadctirqena_bits;

/* DCT/iDCT IRQ Status Register */
typedef struct {
  __REG32 DCTCOMP          : 1;
  __REG32 DININTR          : 1;
  __REG32 DOUTINTR         : 1;
  __REG32 ERRINTR          : 1;
  __REG32 FIFOEMP          : 1;
  __REG32 FIFOFULL         : 1; 
  __REG32                  :26;
} __mmadctirqstat_bits;

/* DCT/iDCT X-Offset Address */
typedef struct {
  __REG32 X_OFFSET         :16;
  __REG32                  :16; 
} __mmadctxoff_bits;

/* DCT/iDCT Y-Offset Address */
typedef struct {
  __REG32 Y_OFFSET         :16;
  __REG32                  :16; 
} __mmadctyoff_bits;

/* DCT/iDCT XY Count */
typedef struct {
  __REG32 X_COUNT          : 7;
  __REG32                  : 1;
  __REG32 Y_COUNT          : 7;
  __REG32                  :17; 
} __mmadctxycnt_bits;

/* DCT/iDCT Skip Address */
typedef struct {
  __REG32 SKIP_ADDR        :16;
  __REG32                  :16; 
} __mmadctskip_bits;

/* SPI 1 - 2 Rx Data Register */
typedef struct {
  __REG32 DATA             :16;
  __REG32                  :16; 
} __rxdataregx_bits;

/* SPI 1 - 2 Tx Data Register */
typedef struct {
  __REG32 DATA             :16;
  __REG32                  :16; 
} __txdataregx_bits;


/* SPI 1 - 2 Control Register */
typedef struct {
  __REG32 BIT_COUNT        : 4;
  __REG32 POL              : 1;
  __REG32 PHA              : 1;
  __REG32 SSCTL            : 1;
  __REG32 SSPOL            : 1;
  __REG32 XCH              : 1;
  __REG32 SPIEN            : 1;
  __REG32 MODE             : 1;
  __REG32 DRCTL            : 2;
  __REG32 DATARATE         : 3; 
  __REG32                  :16; 
} __controlregx_bits;

/* SPI 1 - 2 Interrupt Control/Status Register */
typedef struct {
  __REG32 TE               : 1;
  __REG32 TH               : 1;
  __REG32 TF               : 1;
  __REG32 RR               : 1;
  __REG32 RH               : 1;
  __REG32 RF               : 1;
  __REG32 RO               : 1;
  __REG32 BO               : 1;
  __REG32 TEEN             : 1;
  __REG32 THEN             : 1; 
  __REG32 TFEN             : 1;
  __REG32 RREN             : 1;
  __REG32 RHEN             : 1;
  __REG32 RFEN             : 1;
  __REG32 ROEN             : 1;
  __REG32 BOEN             : 1; 
  __REG32                  :16; 
} __intregx_bits;

/* SPI 1 - 2 Test Register */
typedef struct {
  __REG32 TXCNT            : 4;
  __REG32 RXCNT            : 4;
  __REG32 SSTATUS          : 4;
  __REG32                  : 2;
  __REG32 LBC              : 1; 
  __REG32                  :17; 
} __testregx_bits;

/* SPI 1 - 2 Sample Period Control Register */
typedef struct {
  __REG32 WAIT             :15;
  __REG32 CSRC             : 1; 
  __REG32                  :16; 
} __periodregx_bits;

/* SPI 1 - 2 DMA Control Register */
typedef struct {
  __REG32                  : 4;
  __REG32 RHDMA            : 1;
  __REG32 RFDMA            : 1;
  __REG32 TEDMA            : 1;
  __REG32 THDMA            : 1;
  __REG32                  : 4;
  __REG32 RHDEN            : 1;
  __REG32 RFDEN            : 1;
  __REG32 TEDEN            : 1;
  __REG32 THDEN            : 1; 
  __REG32                  :16; 
} __dmaregx_bits;

/* SPI 1 – 2 Soft Reset Register */
typedef struct {
  __REG32 START            : 1; 
  __REG32                  :31; 
} __resetregx_bits;

/* Screen Start Address Register */
typedef struct {
  __REG32                  : 2; 
  __REG32 SSA              :30; 
} __ssa_bits;

/* Size Register */
typedef struct {
  __REG32 YMAX             : 9;
  __REG32                  :11;
  __REG32 XMAX             : 6;
  __REG32                  : 6; 
} __size_bits;

/* Virtual Page Width Register */
typedef struct {
  __REG32 VPW              :10;
  __REG32                  :22; 
} __vpw_bits;

/* Panel Configuration Register */
typedef struct {
  __REG32 PCD              : 6;
  __REG32 SHARP            : 1;
  __REG32 SCLKSEL          : 1;
  __REG32 ACD              : 7;
  __REG32 ACDSEL           : 1;
  __REG32 REV_VS           : 1;
  __REG32 SWAP_SEL         : 1;
  __REG32 END_SEL          : 1;
  __REG32 SCLKIDLE         : 1;
  __REG32 OEPOL            : 1;
  __REG32 CLKPOL           : 1;
  __REG32 LPPOL            : 1;
  __REG32 FLMPOL           : 1;
  __REG32 PIXPOL           : 1;
  __REG32 BPIX             : 3;
  __REG32 PBSIZ            : 2;
  __REG32 COLOR            : 1;
  __REG32 TFT              : 1; 
} __pcr_bits;

/* Horizontal Configuration Register */
typedef struct {
  __REG32 H_WAIT_2         : 8;
  __REG32 H_WAIT_1         : 8;
  __REG32                  :10;
  __REG32 H_WIDTH          : 6; 
} __hcr_bits;

/* Vertical Configuration Register */
typedef struct {
  __REG32 V_WAIT_2         : 8;
  __REG32 V_WAIT_1         : 8;
  __REG32                  :10;
  __REG32 V_WIDTH          : 6; 
} __vcr_bits;

/* Panning Offset Register */
typedef struct {
  __REG32 POS              : 5;
  __REG32                  :27; 
} __pos_bits;

/* LCD Cursor Position Register */
typedef struct {
  __REG32 CYP              : 9;
  __REG32                  : 7;
  __REG32 CXP              :10;
  __REG32                  : 2;
  __REG32 OP               : 1;
  __REG32                  : 1;
  __REG32 CC               : 2; 
} __cpos_bits;

/* LCD Cursor Width Height and Blink Register */
typedef struct {
  __REG32 BD               : 8;
  __REG32                  : 8;
  __REG32 CH               : 5;
  __REG32                  : 3;
  __REG32 CW               : 5;
  __REG32                  : 2;
  __REG32 BK_EN            : 1; 
} __lcwhb_bits;

/* LCD Color Cursor Mapping Register */
typedef struct {
  __REG32 CUR_COL_B        : 5;
  __REG32 CUR_COL_G        : 6;
  __REG32 CUR_COL_R        : 5;
  __REG32                  :16; 
} __lchcc_bits;

/* Sharp Configuration 1 Register */
typedef struct {
  __REG32 GRAY1            : 4;
  __REG32 GRAY2            : 4;
  __REG32 REV_TOGGLE_DELAY : 4;
  __REG32                  : 4;
  __REG32 CLR_RISE_DELAY   : 8;
  __REG32                  : 2;
  __REG32 PS_RISE_DELAY    : 6; 
} __lscr1_bits;

/* PWM Contrast Control Register */
typedef struct {
  __REG32 PW               : 8;
  __REG32 CC_EN            : 1;
  __REG32 SCR              : 2;
  __REG32                  : 4;
  __REG32 LDMSK            : 1;
  __REG32 CLS_HI_WIDTH     : 9;
  __REG32                  : 7; 
} __pwmr_bits;

/* Refresh Mode Control Register */
typedef struct {
  __REG32 SELF_REF         : 1;
  __REG32 LCDC_EN          : 1;
  __REG32                  :30; 
} __rmcr_bits;

/* DMA Control Register */
typedef struct {
  __REG32 TM               : 4;
  __REG32                  :12;
  __REG32 HM               : 4;
  __REG32                  :11;
  __REG32 BURST            : 1; 
} __dmacr_bits;

/* Interrupt Configuration Register */
typedef struct {
  __REG32 INTCON           : 1;
  __REG32                  : 1;
  __REG32 INTSYN           : 1;
  __REG32                  :29; 
} __lcdicr_bits;

/* Interrupt Status Register */
typedef struct {
  __REG32 BOF              : 1;
  __REG32 _EOF             : 1;
  __REG32 ERR_RES          : 1;
  __REG32 UDR_ERR          : 1;
  __REG32                  :28; 
} __lcdisr_bits;

/* LCD Mapping RAM Registers */
typedef union {
  //RGBx
  struct {
    __REG16 R                : 4; 
    __REG16 G                : 4; 
    __REG16 B                : 4; 
    __REG16                  : 4; 
  };
  //GPMx
  struct {
    __REG16 GPM              : 4;
    __REG16                  :12; 
  };
} __lcdram_bits;


/* MMC/SD Clock Control Register */
typedef struct {
  __REG32 STOP_CLK         : 1;
  __REG32 START_CLK        : 1;
  __REG32 MMCSD_ENABLE     : 1;
  __REG32 MMCSD_RESET      : 1;
  __REG32                  : 1;
  __REG32 ENDIAN           : 1;
  __REG32                  :26; 
} __strstpclk_bits;

/* MMC/SD Status Register */
typedef struct {
  __REG32 TIME_OUT_READ    : 1;
  __REG32 TIME_OUT_RESP    : 1;
  __REG32 CRC_WRITE_ERR    : 1;
  __REG32 CRC_READ_ERR     : 1;
  __REG32                  : 1;
  __REG32 RESP_CRC_ERR     : 1;
  __REG32 APPL_BUFF_FE     : 1;
  __REG32 APPL_BUFF_FF     : 1;
  __REG32 CARD_BUS_CLK_RUN : 1;
  __REG32 WR_CRC_ERROR_CODE: 2;
  __REG32 DATA_TRANS_DONE  : 1;
  __REG32 WRITE_OP_DONE    : 1;
  __REG32 END_CMD_RESP     : 1;
  __REG32 SDIO_INT_ACTIVE  : 1;
  __REG32 CARD_PRESENCE    : 1; 
  __REG32                  :16; 
} __status_bits;

/* MMC/SD Clock Rate Register */
typedef struct {
  __REG32 CLKRATE          : 3;
  __REG32 PRESCALER        : 3; 
  __REG32                  :26; 
} __clkrate_bits;

/* MMC/SD Command and Data Control Register */
typedef struct {
  __REG32 FORMAT_OF_RESPONSE: 3;
  __REG32 DATA_ENABLE      : 1;
  __REG32 WRITE_READ       : 1;
  __REG32 STREAM_BLOCK     : 1;
  __REG32 BUSY             : 1;
  __REG32 INIT             : 1;
  __REG32 BUS_WIDTH        : 2;
  __REG32 START_READWAIT   : 1;
  __REG32 STOP_READWAIT    : 1;
  __REG32 CMD_RESP_LONG_OFF: 1;
  __REG32                  :19; 
} __cmddatcont_bits;

/* MMC/SD Response Time-Out Register */
typedef struct {
  __REG32 RESPONSETIMEOUT  : 8; 
  __REG32                  :24; 
} __resto_bits;

/* MMC/SD Read Time-Out Register */
typedef struct {
  __REG32 DATAREADTIMEOUT  :16; 
  __REG32                  :16; 
} __readto_bits;

/* MMC/SD Block Length Register */
typedef struct {
  __REG32 BLOCKLENGTH      :10; 
  __REG32                  :22; 
} __blklen_bits;

/* MMC/SD Number of Blocks Register */
typedef struct {
  __REG32 NOB              :16; 
  __REG32                  :16; 
} __nob_bits;

/* MMC/SD Revision Number Register */
typedef struct {
  __REG32 REVISIONNUMBER   :16; 
  __REG32                  :16; 
} __revno_bits;

/* MMC/SD Interrupt Mask Register */
typedef struct {
  __REG32 DATA_TRAN        : 1;
  __REG32 WRITE_OP_DONE    : 1;
  __REG32 END_CMD_RES      : 1;
  __REG32 BUF_READY        : 1;
  __REG32 SDIO             : 1;
  __REG32 DAT0_EN          : 1;
  __REG32 AUTO_CARD_DETECT : 1;
  __REG32                  :25; 
} __intmask_bits;

/* MMC/SD Command Number Register */
typedef struct {
  __REG32 COMMANDNUMBER    : 6; 
  __REG32                  :26; 
} __cmd_bits;

/* MMC/SD Higher Argument Register */
typedef struct {
  __REG32 ARGUMENTHIGH     :16; 
  __REG32                  :16; 
} __argh_bits;

/* MMC/SD Lower Argument Register */
typedef struct {
  __REG32 ARGUMENTLOW      :16; 
  __REG32                  :16; 
} __argl_bits;

/* MMC/SD Response FIFO Register */
typedef struct {
  __REG32 RESPONSECONTENT  :16; 
  __REG32                  :16; 
} __resfifo_bits;

/* MMC/SD Buffer Access Register */
typedef struct {
  __REG32 FIFOCONTENT      :16; 
  __REG32                  :16; 
} __bufferaccess_bits;

/* Memory Stick Command Register */
typedef struct {
  __REG16 DATASIZE         :10; 
  __REG16                  : 2; 
  __REG16 PID              : 4; 
} __mscmd_bits;

/* Memory Stick Control/Status Register */
typedef struct {
  __REG16 TBF              : 1; 
  __REG16 TBE              : 1; 
  __REG16 RBF              : 1; 
  __REG16 RBE              : 1; 
  __REG16                  : 2; 
  __REG16 DRQ              : 1; 
  __REG16 INT              : 1; 
  __REG16 BSYCNT           : 3; 
  __REG16 NOCRC            : 1; 
  __REG16 DAKEN            : 1; 
  __REG16 SIEN             : 1; 
  __REG16 PWS              : 1; 
  __REG16 RST              : 1; 
} __mscs_bits;

/* Memory Stick Transmit FIFO Data Register */
/* Memory Stick Receive FIFO Data Register */
typedef union {
  //MSTDATA
  struct {
    __REG16 TXDATABUFFER     :16; 
  };
  //MSRDATA
  struct {
    __REG16 RXDATABUFFER     :16; 
  };
} __msxdata_bits;

/* Memory Stick Interrupt Control/Status Register */
typedef struct {
  __REG16 TOE              : 1; 
  __REG16 CRC              : 1; 
  __REG16 FAE              : 1; 
  __REG16                  : 1; 
  __REG16 PIN              : 1; 
  __REG16 DRQ              : 1; 
  __REG16 SIF              : 1; 
  __REG16 RDY              : 1; 
  __REG16                  : 5; 
  __REG16 PINEN            : 1; 
  __REG16 DRQSL            : 1; 
  __REG16 INTEN            : 1; 
} __msics_bits;

/* Memory Stick Parallel Port Control/Data Register */
typedef struct {
  __REG16                  : 4; 
  __REG16 XPIN0            : 1; 
  __REG16 XPIN1            : 1; 
  __REG16                  : 6; 
  __REG16 PIEN0            : 1; 
  __REG16 PIEN1            : 1; 
  __REG16                  : 2; 
} __msppcd_bits;

/* Memory Stick Control 2 Register */
typedef struct {
  __REG16 MSCEN            : 1; 
  __REG16 LEND             : 1; 
  __REG16                  :12; 
  __REG16 RED              : 1; 
  __REG16 ACD              : 1; 
} __msc2_bits;

/* Memory Stick Auto Command Register */
typedef struct {
  __REG16 ADATASIZE        :10; 
  __REG16                  : 2; 
  __REG16 APID             : 4; 
} __msacd_bits;

/* Memory Stick FIFO Access Error Control/Status Register */
typedef struct {
  __REG16 TOV              : 1; 
  __REG16 RUN              : 1; 
  __REG16                  : 6; 
  __REG16 FAEEN            : 1; 
  __REG16                  : 7; 
} __msfaecs_bits;

/* Memory Stick Serial Clock Divider Register */
typedef struct {
  __REG16 DIV              : 2; 
  __REG16                  :13; 
  __REG16 SRC              : 1; 
} __msclkd_bits;

/* Memory Stick DMA Request Control Register */
typedef struct {
  __REG16 TFE              : 1; 
  __REG16                  : 3; 
  __REG16 RFF              : 1; 
  __REG16                  :10; 
  __REG16 DRQEN            : 1; 
} __msdrqc_bits;

/* PWM Control Register */
typedef struct {
  __REG32 CLKSEL           : 2;
  __REG32 REPEAT           : 2;
  __REG32 EN               : 1;
  __REG32 FIFOAV           : 1;
  __REG32 IRQEN            : 1;
  __REG32 IRQ              : 1;
  __REG32 PRESCALER        : 7;
  __REG32 CLKSRC           : 1;
  __REG32 SWR              : 1;
  __REG32 BCTR             : 1;
  __REG32 HCTR             : 1;
  __REG32                  :13; 
} __pwmc_bits;

/* PWM Sample Register */
typedef struct {
  __REG32 SAMPLE           :16;
  __REG32                  :16; 
} __pwms_bits;

/* PWM Period Register */
typedef struct {
  __REG32 PERIOD           :16;
  __REG32                  :16; 
} __pwmp_bits;

/* PWM Counter Register */
typedef struct {
  __REG32 COUNT            :16;
  __REG32                  :16; 
} __pwmcnt_bits;

/* RTC Days Counter Register */
typedef struct {
  __REG32 DAYS             : 9;
  __REG32                  :23; 
} __dayr_bits;

/* RTC Hours and Minutes Counter Register */
typedef struct {
  __REG32 MINUTES          : 6;
  __REG32                  : 2; 
  __REG32 HOURS            : 5;
  __REG32                  :19; 
} __hourmin_bits;

/* RTC Seconds Counter Register */
typedef struct {
  __REG32 SECONDS          : 6;
  __REG32                  :26; 
} __seconds_bits;

/* RTC Day Alarm Register */
typedef struct {
  __REG32 DAYSAL           : 9;
  __REG32                  :23; 
} __dayalarm_bits;

/* RTC Control Register */
typedef struct {
  __REG32 SWR              : 1;
  __REG32                  : 4; 
  __REG32 XTL              : 2;
  __REG32 EN               : 1;
  __REG32                  :24; 
} __rcctl_bits;

/* RTC Interrupt Status Register */ /* RTC Interrupt Enable Register */
typedef struct {
  __REG32 SW               : 1;
  __REG32 MIN              : 1;
  __REG32 ALM              : 1;
  __REG32 DAY              : 1;
  __REG32 _1HZ             : 1;
  __REG32 HR               : 1;
  __REG32                  : 1; 
  __REG32 _2HZ             : 1;
  __REG32 SAM0             : 1;
  __REG32 SAM1             : 1;
  __REG32 SAM2             : 1;
  __REG32 SAM3             : 1;
  __REG32 SAM4             : 1;
  __REG32 SAM5             : 1;
  __REG32 SAM6             : 1;
  __REG32 SAM7             : 1;
  __REG32                  :16; 
} __rtcisr_bits;

/* Stopwatch Minutes Register */
typedef struct {
  __REG32 CNT              : 6;
  __REG32                  :26; 
} __stpwch_bits;

/* SDRAM 0 - 1 Control Register */
typedef struct {
  __REG32 SRC              : 3;
  __REG32                  : 1;
  __REG32 SRCD             : 2;
  __REG32 SRP              : 1;
  __REG32                  : 1;
  __REG32 SCL              : 2;
  __REG32                  : 2;
  __REG32 CLKST            : 2;
  __REG32 SREFR            : 2;
  __REG32 DSIZ             : 2;
  __REG32                  : 1;
  __REG32 IAM              : 1;
  __REG32 COL              : 2;
  __REG32                  : 2;
  __REG32 ROW              : 2;
  __REG32                  : 1;
  __REG32 SP               : 1;
  __REG32 SMODE            : 3;
  __REG32 SDE              : 1; 
} __sdctlx_bits;

/* SDRAM Reset Register */
typedef struct {
  __REG32                  :30;
  __REG32 RST              : 2; 
} __sdrst_bits;

/* Miscellaneous Register */
typedef struct {
  __REG32 RMA0             : 1; 
  __REG32                  :30;
  __REG32 OMA              : 1; 
} __miscellaneous_bits;
	
/* Timer Control Register 1 - 2 */
typedef struct {
  __REG32 TEN              : 1;
  __REG32 CLKSOURCE        : 3;
  __REG32 IRQEN            : 1;
  __REG32 OM               : 1;
  __REG32 CAP              : 2; 
  __REG32 FRR              : 1;
  __REG32                  : 6; 
  __REG32 SWR              : 1;
  __REG32                  :16; 
} __tctlx_bits;

/* Timer Prescaler Register 1 - 2 */
typedef struct {
  __REG32 PRESCALER        : 8;
  __REG32                  :24;
} __tprerx_bits;

/* Timer Status Register 1 - 2 */
typedef struct {
  __REG32 COMP             : 1;
  __REG32 CAPT             : 1;
  __REG32                  :30;
} __tstatx_bits;

/* USB Frame */
typedef struct {
  __REG32 FRAME            :11;
  __REG32                  : 5;
  __REG32 MATCH            :11;
  __REG32                  : 5; 
} __usbframe_bits;

/* USB Specification */
typedef struct {
  __REG32 SPEC             :12;
  __REG32                  :20; 
} __usbspec_bits;

/* USB Status */
typedef struct {
  __REG32 ALTSET           : 3;
  __REG32 INTF             : 2;
  __REG32 CFG              : 2;
  __REG32 SUSP             : 1;
  __REG32 RST              : 1;
  __REG32                  :23; 
} __usbstat_bits;

/* USB Control */
typedef struct {
  __REG32 RESUME           : 1;
  __REG32 AFE_ENA          : 1;
  __REG32 UDC_RST          : 1;
  __REG32 USB_ENA          : 1;
  __REG32 USB_SPD          : 1;
  __REG32 CMD_ERROR        : 1;
  __REG32 CMD_OVER         : 1; 
  __REG32                  :25; 
} __usbctrl_bits;

/* USB Descriptor RAM Address */
typedef struct {
  __REG32 DADR             : 9;
  __REG32                  :21;
  __REG32 BSY              : 1;
  __REG32 CFG              : 1; 
} __usbdadr_bits;

/* USB Descriptor RAM/Endpoint Buffer Data */
typedef struct {
  __REG32 DDAT             : 8;
  __REG32                  :24; 
} __usbddat_bits;

/* USB Interrupt */
/* USB Interrupt Mask */
typedef struct {
  __REG32 CFG_CHG          : 1;
  __REG32 FRAME_MATCH      : 1;
  __REG32 SUSP             : 1;
  __REG32 RES              : 1;
  __REG32 RESET_START      : 1;
  __REG32 RESET_STOP       : 1;
  __REG32 SOF              : 1;
  __REG32 MSOF             : 1; 
  __REG32                  :23;
  __REG32 WAKEUP           : 1; 
} __usbintr_bits;

/* USB Enable */
typedef struct {
  __REG32 PWRMD            : 1;
  __REG32                  :27;
  __REG32 ENDIAN_MODE      : 1;
  __REG32 SUSPEND          : 1;
  __REG32 ENAB             : 1;
  __REG32 RST              : 1; 
} __usbenab_bits;

/* Endpoint 0-5 Status/Control Register */
typedef struct {
  __REG32 FORCE_STALL      : 1;
  __REG32 FLUSH            : 1;
  __REG32 ZLPS             : 1;
  __REG32 TYP              : 2;
  __REG32 MAX              : 2;
  __REG32 DIR              : 1;
  __REG32 SIP              : 1;
  __REG32                  : 7; 
  __REG32 BYTE_COUNT       : 7;
  __REG32                  : 9; 
} __usbepxstat_bits;


/* Endpoint 0-5 Interrupt Status Register */
/* Endpoint 0-5 Interrupt Mask Register */
typedef struct {
  __REG32 _EOF             : 1;
  __REG32 DEVREQ           : 1;
  __REG32 EOT              : 1;
  __REG32 MDEVREQ          : 1;
  __REG32 FIFO_LOW         : 1;
  __REG32 FIFO_HIGH        : 1;
  __REG32 FIFO_ERROR       : 1;
  __REG32 FIFO_EMPTY       : 1; 
  __REG32 FIFO_FULL        : 1;
  __REG32                  :23; 
} __usbepxintr_bits;

/* Endpoint 0-5 Status Register */ 
typedef struct {
  __REG32                  :16;
  __REG32 EMPTY            : 1;
  __REG32 ALARM            : 1;
  __REG32 FULL             : 1;
  __REG32 FR               : 1;
  __REG32 UF               : 1;
  __REG32 OF               : 1;
  __REG32 ERROR            : 1; 
  __REG32                  : 1;
  __REG32 FRAME3           : 1;
  __REG32 FRAME2           : 1;
  __REG32 FRAME1           : 1; 
  __REG32 FRAME0           : 1;
  __REG32                  : 4; 
} __usbepxfstat_bits;

/* Endpoint 0-5 Control Register */ 
typedef struct {
  __REG32                  :24;
  __REG32 GR               : 3;
  __REG32 FRAME            : 1;
  __REG32                  : 1;
  __REG32 WFR              : 1;
  __REG32                  : 2; 
} __usbepxfctrl_bits;

/* Endpoint 0-5 Last Read Frame Pointer Register */ 
typedef struct {
  __REG32 LRFP             : 6;
  __REG32                  :26; 
} __usbepxlrfp_bits;

/* Endpoint 0-5 Last Write Frame Pointer Register */ 
typedef struct {
  __REG32 LWFP             : 6;
  __REG32                  :26; 
} __usbepxlwfp_bits;

/* Endpoint 0-5 FIFO Alarm Register */ 
typedef struct {
  __REG32 ALRM             : 6;
  __REG32                  :26; 
} __usbepxfalrm_bits;

/* Endpoint 0-5 FIFO Read Pointer Register */ 
typedef struct {
  __REG32 RP               : 6;
  __REG32                  :26; 
} __usbepxfrdp_bits;

/* Endpoint 0-5 FIFO Write Pointer Register */ 
typedef struct {
  __REG32 WP               : 6;
  __REG32                  :26; 
} __usbepxfwrp_bits;

/* UART1-2 Receiver Register n */
typedef struct {
  __REG32 RX_DATA          : 8;
  __REG32                  : 2;
  __REG32 PRERR            : 1;
  __REG32 BRK              : 1;
  __REG32 FRMERR           : 1;
  __REG32 OVRRUN           : 1;
  __REG32 ERR              : 1;
  __REG32 CHARRDY          : 1; 
  __REG32                  :16; 
} __urxndx_bits;

/* UART1-2 Transmitter Register n */
typedef struct {
  __REG32 TX_DATA          : 8; 
  __REG32                  :24; 
} __utxndx_bits;


/* UART1-2 Control Register 1 */
typedef struct {
  __REG32 UARTEN           : 1; 
  __REG32 DOZE             : 1; 
  __REG32 UARTCLKEN        : 1; 
  __REG32 TDMAEN           : 1; 
  __REG32 SNDBRK           : 1; 
  __REG32 RTSDEN           : 1; 
  __REG32 TXMPTYEN         : 1; 
  __REG32 IREN             : 1; 
  __REG32 RDMAEN           : 1; 
  __REG32 RRDYEN           : 1; 
  __REG32 ICD              : 2; 
  __REG32 IDEN             : 1; 
  __REG32 TRDYEN           : 1; 
  __REG32 ADBR             : 1; 
  __REG32 ADEN             : 1; 
  __REG32                  :16; 
} __ucr1x_bits;

/* UART1-2 Control Register 2 */
typedef struct {
  __REG32 SRST             : 1; 
  __REG32 RXEN             : 1; 
  __REG32 TXEN             : 1; 
  __REG32                  : 1; 
  __REG32 RTSEN            : 1; 
  __REG32 WS               : 1; 
  __REG32 STPB             : 1; 
  __REG32 PROE             : 1; 
  __REG32 PREN             : 1; 
  __REG32 RTEC             : 2; 
  __REG32 ESCEN            : 1; 
  __REG32 CTS              : 1; 
  __REG32 CTSC             : 1; 
  __REG32 IRTS             : 1; 
  __REG32 ESCI             : 1; 
  __REG32                  :16; 
} __ucr2x_bits;

/* UART1 Control Register 3 */
typedef struct {
  __REG32 BPEN             : 1; 
  __REG32 INVT             : 1; 
  __REG32 REF30            : 1; 
  __REG32 REF25            : 1; 
  __REG32 AWAKEN           : 1; 
  __REG32 AIRINTEN         : 1; 
  __REG32 RXDSEN           : 1; 
  __REG32                  : 4; 
  __REG32 FRAERREN         : 1; 
  __REG32 PARERREN         : 1; 
  __REG32                  :19; 
} __ucr31_bits;

/* UART2 Control Register 3 */
typedef struct {
  __REG32 BPEN             : 1; 
  __REG32 INVT             : 1; 
  __REG32 REF30            : 1; 
  __REG32 REF25            : 1; 
  __REG32 AWAKEN           : 1; 
  __REG32 AIRINTEN         : 1; 
  __REG32 RXDSEN           : 1; 
  __REG32                  : 1; 
  __REG32 RI               : 1; 
  __REG32 DCD              : 1; 
  __REG32 DSR              : 1; 
  __REG32 FRAERREN         : 1; 
  __REG32 PARERREN         : 1; 
  __REG32 DTREN            : 1; 
  __REG32 DPEC             : 2; 
  __REG32                  :16; 
} __ucr32_bits;

/* UART1-2 Control Register 4 */
typedef struct {
  __REG32 DREN             : 1; 
  __REG32 OREN             : 1; 
  __REG32 BKEN             : 1; 
  __REG32 TCEN             : 1; 
  __REG32                  : 1; 
  __REG32 IRSC             : 1; 
  __REG32 REF16            : 1; 
  __REG32 WKEN             : 1; 
  __REG32 ENIRI            : 1; 
  __REG32 INVR             : 1; 
  __REG32 CTSTL            : 6; 
  __REG32                  :16; 
} __ucr4x_bits;

/* UART1-2 FIFO Control Register */
typedef struct {
  __REG32 RXTL             : 6; 
  __REG32                  : 1; 
  __REG32 RFDIV            : 3; 
  __REG32 TXTL             : 6; 
  __REG32                  :16; 
} __ufcrx_bits;

/* UART1-2 Status Register 1 */
typedef struct {
  __REG32                  : 4; 
  __REG32 AWAKE            : 1; 
  __REG32 AIRINT           : 1; 
  __REG32 RXDS             : 1; 
  __REG32                  : 2; 
  __REG32 RRDY             : 1; 
  __REG32 FRAMERR          : 1; 
  __REG32 ESCF             : 1; 
  __REG32 RTSD             : 1; 
  __REG32 TRDY             : 1; 
  __REG32 RTSS             : 1; 
  __REG32 PARITYERR        : 1; 
  __REG32                  :16; 
} __usr1x_bits;

/* UART1-2 Status Register 2 */
typedef struct {
  __REG32 RDR              : 1; 
  __REG32 ORE              : 1; 
  __REG32 BRCD             : 1; 
  __REG32 TXDC             : 1; 
  __REG32 RTSF             : 1; 
  __REG32                  : 2; 
  __REG32 WAKE             : 1; 
  __REG32 IRINT            : 1; 
  __REG32                  : 3; 
  __REG32 IDLE             : 1; 
  __REG32 DTRF             : 1; 
  __REG32 TXFE             : 1; 
  __REG32 ADET             : 1; 
  __REG32                  :16; 
} __usr2x_bits;

/* UART1-2 Escape Charachter Register */
typedef struct {
  __REG32 ESC_CHAR         : 8; 
  __REG32                  :24; 
} __uescx_bits;

/* UART1-2 Escape Timer Register */
typedef struct {
  __REG32 TIM              :12; 
  __REG32                  :20; 
} __utimx_bits;

/* UART1-2 BRM Incremental Register */
typedef struct {
  __REG32 INC              :16; 
  __REG32                  :16; 
} __ubirx_bits;

/* UART1-2 BRM Modulator Register */
typedef struct {
  __REG32 MOD              :16; 
  __REG32                  :16; 
} __ubmrx_bits;

/* UART1-2 Baud Rate Count Register */
typedef struct {
  __REG32 BCNT             :16; 
  __REG32                  :16; 
} __ubrcx_bits;

/* UART1-2 BRM Incremental Preset Register n */
typedef struct {
  __REG32 INCPI            :16; 
  __REG32                  :16; 
} __biprnx_bits;

/* UART1-2 BRM Modulator Preset Register n */
typedef struct {
  __REG32 MODI             :16; 
  __REG32                  :16; 
} __bmprnx_bits;

/* UART1-2 Test Register 1 */
typedef struct {
  __REG32 SOFTRST          : 1; 
  __REG32                  : 2;
  __REG32 RXFULL           : 1;
  __REG32 TXFULL           : 1;
  __REG32 RXEMPTY          : 1;
  __REG32 TXEMPTY          : 1;
  __REG32                  : 5;
  __REG32 LOOP             : 1;
  __REG32 FRCPERR          : 1;
  __REG32                  :18; 
} __utsx_bits;

/* I2C Address Register */
typedef struct {
  __REG32                  : 1; 
  __REG32 ADR              : 7;
  __REG32                  :24; 
} __iadr_bits;

/* I2C Frequency Divider Register */
typedef struct { 
  __REG32 IC               : 6;
  __REG32                  :26; 
} __ifdr_bits;

/* I2C Control Register */
typedef struct {
  __REG32                  : 2; 
  __REG32 RSTA             : 1;
  __REG32 TXAK             : 1;
  __REG32 MTX              : 1;
  __REG32 MSTA             : 1;
  __REG32 IIEN             : 1;
  __REG32 IEN              : 1;
  __REG32                  :24; 
} __i2cr_bits;

/* I2C Status Register */
typedef struct {
  __REG32 RXAK             : 1; 
  __REG32 IIF              : 1;
  __REG32 SRW              : 1;
  __REG32                  : 1;
  __REG32 IAL              : 1;
  __REG32 IBB              : 1;
  __REG32 IAAS             : 1;
  __REG32 ICF              : 1;
  __REG32                  :24; 
} __i2sr_bits;

/* I2C Data I/O Register */
typedef struct { 
  __REG32 D                : 8;
  __REG32                  :24; 
} __i2dr_bits;

/* SSI Transmit Data Register */
/* SSI Receive Data Register */
typedef struct { 
  __REG32 LOWBYTE          : 8;
  __REG32 HIGHBYTE         : 8;
  __REG32                  :16; 
} __stx_bits;

/* SSI Control/Status Register */
typedef struct { 
  __REG32 TFE              : 1;
  __REG32 RFF              : 1;
  __REG32 RFS              : 1;
  __REG32 TFS              : 1;
  __REG32 TUE              : 1;
  __REG32 ROE              : 1;
  __REG32 TDE              : 1;
  __REG32 RDR              : 1;
  __REG32 SSI_EN           : 1;
  __REG32 TE               : 1;
  __REG32 RE               : 1;
  __REG32 NET              : 1;
  __REG32 SYN              : 1;
  __REG32 I2S_MODE         : 2;
  __REG32 SYS_CLK_EN       : 1; 
  __REG32                  :16; 
} __scsr_bits;

/* SSI Transmit Configuration Register */
typedef struct { 
  __REG32 TEFS             : 1;
  __REG32 TFSL             : 1;
  __REG32 TFSI             : 1;
  __REG32 TSCKP            : 1;
  __REG32 TSHFD            : 1;
  __REG32 TXDIR            : 1;
  __REG32 TFDIR            : 1;
  __REG32 TFEN             : 1;
  __REG32 TIE              : 1;
  __REG32 TDMAE            : 1;
  __REG32 TXBIT0           : 1; 
  __REG32                  :21; 
} __stcr_bits;

/* SSI Receive Configuration Register */
typedef struct { 
  __REG32 REFS             : 1;
  __REG32 RFSL             : 1;
  __REG32 RFSI             : 1;
  __REG32 RSCKP            : 1;
  __REG32 RSHFD            : 1;
  __REG32 RXDIR            : 1;
  __REG32 RFDIR            : 1;
  __REG32 RFEN             : 1;
  __REG32 RIE              : 1;
  __REG32 RDMAE            : 1;
  __REG32 RXBIT0           : 1; 
  __REG32                  :21; 
} __srcr_bits;

/* SSI Transmit Clock Control Register */
/* SSI Receive Clock Control Register */
typedef struct { 
  __REG32 PM               : 8;
  __REG32 DC               : 5;
  __REG32 WL               : 2;
  __REG32 PSR              : 1; 
  __REG32                  :16; 
} __sxccr_bits;

/* SSI Time Slot Register */
typedef struct { 
  __REG32 DUMMY            :16; 
  __REG32                  :16; 
} __stsr_bits;

/* SSI FIFO Control/Status Register */
typedef struct { 
  __REG32 TFWM             : 4;
  __REG32 RFWM             : 4;
  __REG32 TFCNT            : 4;
  __REG32 RFCNT            : 4; 
  __REG32                  :16; 
} __sfcsr_bits;

/* SSI Option Register */
typedef struct { 
  __REG32 SYNRST           : 1;
  __REG32                  : 3;
  __REG32 TX_CLR           : 1;
  __REG32 RX_CLR           : 1;
  __REG32 CLKOFF           : 1;
  __REG32                  :25;
} __sor_bits;

/* CSI Control Register 1 */
typedef struct { 
  __REG32 EN               : 1;
  __REG32 REGDE            : 1;
  __REG32 INV_PCLK         : 1;
  __REG32 INV_DATA         : 1;
  __REG32 GCLK_MODE        : 1;
  __REG32 CLR_RxFIFO       : 1;
  __REG32 CLR_STATFIFO     : 1;
  __REG32 BIG_ENDIAN       : 1;
  __REG32 FCC              : 1;
  __REG32 MCLKEN           : 1;
  __REG32                  : 2;
  __REG32 MCLKDIV          : 4;
  __REG32 SOF_INTEN        : 1;
  __REG32 SOF_POL          : 1;
  __REG32 RXFF_INTEN       : 1;
  __REG32 RXFF_LEVEL       : 2;
  __REG32 STATFF_INTEN     : 1;
  __REG32 STATFF_LEVEL     : 2;
  __REG32 RF_OR_INTEN      : 1;
  __REG32 SF_OR_INTEN      : 1; 
  __REG32                  : 6;
} __csicr1_bits;

/* CSI Control Register 2 */
typedef struct { 
  __REG32 HSC              : 8;
  __REG32 VSC              : 8;
  __REG32 LVRM             : 3;
  __REG32 BTS              : 2;
  __REG32                  : 2;
  __REG32 SCE              : 1;
  __REG32 AFS              : 2;
  __REG32 DRM              : 1; 
  __REG32                  : 5;
} __csicr2_bits;

/* CSI Status Register 1 */
typedef struct { 
  __REG32 DRDY             : 1;
  __REG32                  :15;
  __REG32 SOF_INT          : 1;
  __REG32                  : 1;
  __REG32 RXFF_INT         : 1;
  __REG32                  : 2;
  __REG32 STATFF_INT       : 1;
  __REG32                  : 2; 
  __REG32 RFF_OR_INT       : 1;
  __REG32 SFF_OR_INT       : 1;
  __REG32                  : 6;
} __csisr_bits;

/* Port x Output Configuration Register 1 */
/* Port x Input Configuration Register A1 */
/* Port x Input Configuration Register B1 */
/* Port x Interrupt Configuration Register 1 */
typedef struct { 
  __REG32 pin0             : 2;
  __REG32 pin1             : 2;
  __REG32 pin2             : 2;
  __REG32 pin3             : 2;
  __REG32 pin4             : 2;
  __REG32 pin5             : 2;
  __REG32 pin6             : 2;
  __REG32 pin7             : 2;
  __REG32 pin8             : 2;
  __REG32 pin9             : 2;
  __REG32 pin10            : 2;
  __REG32 pin11            : 2;
  __REG32 pin12            : 2;
  __REG32 pin13            : 2;
  __REG32 pin14            : 2;
  __REG32 pin15            : 2;
} __ocr1x_bits;

/* Port x Output Configuration Register 2 */
/* Port x Input Configuration Register A2 */
/* Port x Input Configuration Register B2 */
/* Port x Interrupt Configuration Register 2 */
typedef struct { 
  __REG32 pin16            : 2;
  __REG32 pin17            : 2;
  __REG32 pin18            : 2;
  __REG32 pin19            : 2;
  __REG32 pin20            : 2;
  __REG32 pin21            : 2;
  __REG32 pin22            : 2;
  __REG32 pin23            : 2;
  __REG32 pin24            : 2;
  __REG32 pin25            : 2;
  __REG32 pin26            : 2;
  __REG32 pin27            : 2;
  __REG32 pin28            : 2;
  __REG32 pin29            : 2;
  __REG32 pin30            : 2;
  __REG32 pin31            : 2;
} __ocr2x_bits;

/* Port x Software Reset Register */
typedef struct { 
  __REG32 SWR              : 1;
  __REG32                  :31;
} __swrx_bits;

#endif	/* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/

/***************************************************************************
 **
 ** AHB to IP Bus Interface 1 (AIPI1)
 **
 ***************************************************************************/
__IO_REG32_BIT(PSR0_1,        0x00200000, __READ_WRITE, __aipipsr0x_bits);
__IO_REG32_BIT(PSR1_1,        0x00200004, __READ_WRITE, __aipipsr1x_bits);
__IO_REG32_BIT(PAR_1,         0x00200008, __READ_WRITE, __aipiparx_bits );
__IO_REG32_BIT(PCR_1,         0x0020000C, __READ_WRITE, __aipipcrx_bits);
__IO_REG32_BIT(TSR_1,         0x00200010, __READ_WRITE, __aipitsrx_bits);

/***************************************************************************
 **
 ** Watchdog Timer Module
 **
 ***************************************************************************/
__IO_REG32_BIT(WCR,           0x00201000, __READ_WRITE, __wcr_bits );
__IO_REG32_BIT(WSR,           0x00201004, __READ_WRITE, __wsr_bits );
__IO_REG32_BIT(WSTR,          0x00201008, __READ_WRITE, __wstr_bits);

/***************************************************************************
 **
 ** General Purpose Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TCTL1,         0x00202000, __READ_WRITE, __tctlx_bits ); 
__IO_REG32_BIT(TPRER1,        0x00202004, __READ_WRITE, __tprerx_bits); 
__IO_REG32(    TCMP1,         0x00202008, __READ_WRITE               ); 
__IO_REG32(    TCR1,          0x0020200C, __READ                     ); 
__IO_REG32(    TCN1,          0x00202010, __READ                     ); 
__IO_REG32_BIT(TSTAT1,        0x00202014, __READ_WRITE, __tstatx_bits); 
__IO_REG32_BIT(TCTL2,         0x00203000, __READ_WRITE, __tctlx_bits ); 
__IO_REG32_BIT(TPRER2,        0x00203004, __READ_WRITE, __tprerx_bits); 
__IO_REG32(    TCMP2,         0x00203008, __READ_WRITE               ); 
__IO_REG32(    TCR2,          0x0020300C, __READ                     ); 
__IO_REG32(    TCN2,          0x00203010, __READ                     ); 
__IO_REG32_BIT(TSTAT2,        0x00203014, __READ_WRITE, __tstatx_bits); 


/***************************************************************************
 **
 ** Real-Time Clock (RTC)
 **
 ***************************************************************************/
__IO_REG32_BIT(HOURMIN,       0x00204000, __READ_WRITE, __hourmin_bits ); 
__IO_REG32_BIT(SECONDS,       0x00204004, __READ_WRITE, __seconds_bits ); 
__IO_REG32_BIT(ALRM_HM,       0x00204008, __READ_WRITE, __hourmin_bits ); 
__IO_REG32_BIT(ALRM_SEC,      0x0020400C, __READ_WRITE, __seconds_bits ); 
__IO_REG32_BIT(RCCTL,         0x00204010, __READ_WRITE, __rcctl_bits   ); 
__IO_REG32_BIT(RTCISR,        0x00204014, __READ_WRITE, __rtcisr_bits  ); 
__IO_REG32_BIT(RTCIENR,       0x00204018, __READ_WRITE, __rtcisr_bits ); 
__IO_REG32_BIT(STPWCH,        0x0020401C, __READ_WRITE, __stpwch_bits  ); 
__IO_REG32_BIT(DAYR,          0x00204020, __READ_WRITE, __dayr_bits    ); 
__IO_REG32_BIT(DAYALARM,      0x00204024, __READ_WRITE, __dayalarm_bits); 

/***************************************************************************
 **
 ** LCD Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(SSA,           0x00205000, __READ_WRITE, __ssa_bits   );
__IO_REG32_BIT(SIZE,          0x00205004, __READ_WRITE, __size_bits  );
__IO_REG32_BIT(VPW,           0x00205008, __READ_WRITE, __vpw_bits   );
__IO_REG32_BIT(CPOS,          0x0020500C, __READ_WRITE, __cpos_bits  );
__IO_REG32_BIT(LCWHB,         0x00205010, __READ_WRITE, __lcwhb_bits );
__IO_REG32_BIT(LCHCC,         0x00205014, __READ_WRITE, __lchcc_bits );
__IO_REG32_BIT(PCR,           0x00205018, __READ_WRITE, __pcr_bits   );
__IO_REG32_BIT(HCR,           0x0020501C, __READ_WRITE, __hcr_bits   );
__IO_REG32_BIT(VCR,           0x00205020, __READ_WRITE, __vcr_bits   );
__IO_REG32_BIT(POS,           0x00205024, __READ_WRITE, __pos_bits   );
__IO_REG32_BIT(LSCR1,         0x00205028, __READ_WRITE, __lscr1_bits );
__IO_REG32_BIT(PWMR,          0x0020502C, __READ_WRITE, __pwmr_bits  );
__IO_REG32_BIT(DMACR,         0x00205030, __READ_WRITE, __dmacr_bits );
__IO_REG32_BIT(RMCR,          0x00205034, __READ_WRITE, __rmcr_bits  );
__IO_REG32_BIT(LCDICR,        0x00205038, __READ_WRITE, __lcdicr_bits);
__IO_REG32_BIT(LCDISR,        0x00205040, __READ_WRITE, __lcdisr_bits); 
__IO_REG16_BIT(RGB0,          0x00205800, __READ_WRITE, __lcdram_bits);
#define        GPM0           RGB0
#define        GPM0_bit       RGB0_bit
__IO_REG16_BIT(RGB1,          0x00205804, __READ_WRITE, __lcdram_bits);
#define        GPM1           RGB1
#define        GPM1_bit       RGB1_bit
__IO_REG16_BIT(RGB2,          0x00205808, __READ_WRITE, __lcdram_bits);
#define        GPM2           RGB2
#define        GPM2_bit       RGB2_bit
__IO_REG16_BIT(RGB3,          0x0020580C, __READ_WRITE, __lcdram_bits);
#define        GPM3           RGB3
#define        GPM3_bit       RGB3_bit
__IO_REG16_BIT(RGB4,          0x00205810, __READ_WRITE, __lcdram_bits);
#define        GPM4           RGB4
#define        GPM4_bit       RGB4_bit
__IO_REG16_BIT(RGB5,          0x00205814, __READ_WRITE, __lcdram_bits);
#define        GPM5           RGB5
#define        GPM5_bit       RGB5_bit
__IO_REG16_BIT(RGB6,          0x00205818, __READ_WRITE, __lcdram_bits);
#define        GPM6           RGB6
#define        GPM6_bit       RGB6_bit
__IO_REG16_BIT(RGB7,          0x0020581C, __READ_WRITE, __lcdram_bits);
#define        GPM7           RGB7
#define        GPM7_bit       RGB7_bit
__IO_REG16_BIT(RGB8,          0x00205820, __READ_WRITE, __lcdram_bits);
#define        GPM8           RGB8
#define        GPM8_bit       RGB8_bit
__IO_REG16_BIT(RGB9,          0x00205824, __READ_WRITE, __lcdram_bits);
#define        GPM9           RGB9
#define        GPM9_bit       RGB9_bit
__IO_REG16_BIT(RGB10,         0x00205828, __READ_WRITE, __lcdram_bits);
#define        GPM10          RGB10
#define        GPM10_bit      RGB10_bit
__IO_REG16_BIT(RGB11,         0x0020582C, __READ_WRITE, __lcdram_bits);
#define        GPM11          RGB11
#define        GPM11_bit      RGB11_bit
__IO_REG16_BIT(RGB12,         0x00205830, __READ_WRITE, __lcdram_bits);
#define        GPM12          RGB12
#define        GPM12_bit      RGB12_bit
__IO_REG16_BIT(RGB13,         0x00205834, __READ_WRITE, __lcdram_bits);
#define        GPM13          RGB13
#define        GPM13_bit      RGB13_bit
__IO_REG16_BIT(RGB14,         0x00205838, __READ_WRITE, __lcdram_bits);
#define        GPM14          RGB14
#define        GPM14_bit      RGB14_bit
__IO_REG16_BIT(RGB15,         0x0020583C, __READ_WRITE, __lcdram_bits);
#define        GPM15          RGB15
#define        GPM15_bit      RGB15_bit
__IO_REG16_BIT(RGB16,         0x00205840, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB17,         0x00205844, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB18,         0x00205848, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB19,         0x0020584C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB20,         0x00205850, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB21,         0x00205854, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB22,         0x00205858, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB23,         0x0020585C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB24,         0x00205860, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB25,         0x00205864, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB26,         0x00205868, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB27,         0x0020586C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB28,         0x00205870, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB29,         0x00205874, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB30,         0x00205878, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB31,         0x0020587C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB32,         0x00205880, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB33,         0x00205884, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB34,         0x00205888, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB35,         0x0020588C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB36,         0x00205890, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB37,         0x00205894, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB38,         0x00205898, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB39,         0x0020589C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB40,         0x002058A0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB41,         0x002058A4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB42,         0x002058A8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB43,         0x002058AC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB44,         0x002058B0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB45,         0x002058B4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB46,         0x002058B8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB47,         0x002058BC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB48,         0x002058C0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB49,         0x002058C4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB50,         0x002058C8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB51,         0x002058CC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB52,         0x002058D0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB53,         0x002058D4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB54,         0x002058D8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB55,         0x002058DC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB56,         0x002058E0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB57,         0x002058E4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB58,         0x002058E8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB59,         0x002058EC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB60,         0x002058F0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB61,         0x002058F4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB62,         0x002058F8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB63,         0x002058FC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB64,         0x00205900, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB65,         0x00205904, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB66,         0x00205908, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB67,         0x0020590C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB68,         0x00205910, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB69,         0x00205914, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB70,         0x00205918, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB71,         0x0020591C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB72,         0x00205920, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB73,         0x00205924, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB74,         0x00205928, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB75,         0x0020592C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB76,         0x00205930, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB77,         0x00205934, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB78,         0x00205938, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB79,         0x0020593C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB80,         0x00205940, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB81,         0x00205944, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB82,         0x00205948, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB83,         0x0020594C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB84,         0x00205950, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB85,         0x00205954, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB86,         0x00205958, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB87,         0x0020595C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB88,         0x00205960, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB89,         0x00205964, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB90,         0x00205968, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB91,         0x0020596C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB92,         0x00205970, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB93,         0x00205974, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB94,         0x00205978, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB95,         0x0020597C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB96,         0x00205980, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB97,         0x00205984, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB98,         0x00205988, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB99,         0x0020598C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB100,        0x00205990, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB101,        0x00205994, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB102,        0x00205998, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB103,        0x0020599C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB104,        0x002059A0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB105,        0x002059A4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB106,        0x002059A8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB107,        0x002059AC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB108,        0x002059B0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB109,        0x002059B4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB110,        0x002059B8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB111,        0x002059BC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB112,        0x002059C0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB113,        0x002059C4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB114,        0x002059C8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB115,        0x002059CC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB116,        0x002059D0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB117,        0x002059D4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB118,        0x002059D8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB119,        0x002059DC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB120,        0x002059E0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB121,        0x002059E4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB122,        0x002059E8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB123,        0x002059EC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB124,        0x002059F0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB125,        0x002059F4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB126,        0x002059F8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB127,        0x002059FC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB128,        0x00205A00, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB129,        0x00205A04, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB130,        0x00205A08, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB131,        0x00205A0C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB132,        0x00205A10, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB133,        0x00205A14, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB134,        0x00205A18, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB135,        0x00205A1C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB136,        0x00205A20, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB137,        0x00205A24, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB138,        0x00205A28, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB139,        0x00205A2C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB140,        0x00205A30, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB141,        0x00205A34, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB142,        0x00205A38, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB143,        0x00205A3C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB144,        0x00205A40, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB145,        0x00205A44, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB146,        0x00205A48, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB147,        0x00205A4C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB148,        0x00205A50, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB149,        0x00205A54, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB150,        0x00205A58, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB151,        0x00205A5C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB152,        0x00205A60, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB153,        0x00205A64, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB154,        0x00205A68, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB155,        0x00205A6C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB156,        0x00205A70, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB157,        0x00205A74, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB158,        0x00205A78, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB159,        0x00205A7C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB160,        0x00205A80, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB161,        0x00205A84, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB162,        0x00205A88, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB163,        0x00205A8C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB164,        0x00205A90, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB165,        0x00205A94, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB166,        0x00205A98, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB167,        0x00205A9C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB168,        0x00205AA0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB169,        0x00205AA4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB170,        0x00205AA8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB171,        0x00205AAC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB172,        0x00205AB0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB173,        0x00205AB4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB174,        0x00205AB8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB175,        0x00205ABC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB176,        0x00205AC0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB177,        0x00205AC4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB178,        0x00205AC8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB179,        0x00205ACC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB180,        0x00205AD0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB181,        0x00205AD4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB182,        0x00205AD8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB183,        0x00205ADC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB184,        0x00205AE0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB185,        0x00205AE4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB186,        0x00205AE8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB187,        0x00205AEC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB188,        0x00205AF0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB189,        0x00205AF4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB190,        0x00205AF8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB191,        0x00205AFC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB192,        0x00205B00, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB193,        0x00205B04, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB194,        0x00205B08, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB195,        0x00205B0C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB196,        0x00205B10, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB197,        0x00205B14, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB198,        0x00205B18, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB199,        0x00205B1C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB200,        0x00205B20, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB201,        0x00205B24, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB202,        0x00205B28, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB203,        0x00205B2C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB204,        0x00205B30, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB205,        0x00205B34, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB206,        0x00205B38, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB207,        0x00205B3C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB208,        0x00205B40, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB209,        0x00205B44, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB210,        0x00205B48, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB211,        0x00205B4C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB212,        0x00205B50, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB213,        0x00205B54, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB214,        0x00205B58, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB215,        0x00205B5C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB216,        0x00205B60, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB217,        0x00205B64, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB218,        0x00205B68, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB219,        0x00205B6C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB220,        0x00205B70, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB221,        0x00205B74, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB222,        0x00205B78, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB223,        0x00205B7C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB224,        0x00205B80, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB225,        0x00205B84, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB226,        0x00205B88, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB227,        0x00205B8C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB228,        0x00205B90, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB229,        0x00205B94, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB230,        0x00205B98, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB231,        0x00205B9C, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB232,        0x00205BA0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB233,        0x00205BA4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB234,        0x00205BA8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB235,        0x00205BAC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB236,        0x00205BB0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB237,        0x00205BB4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB238,        0x00205BB8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB239,        0x00205BBC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB240,        0x00205BC0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB241,        0x00205BC4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB242,        0x00205BC8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB243,        0x00205BCC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB244,        0x00205BD0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB245,        0x00205BD4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB246,        0x00205BD8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB247,        0x00205BDC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB248,        0x00205BE0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB249,        0x00205BE4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB250,        0x00205BE8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB251,        0x00205BEC, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB252,        0x00205BF0, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB253,        0x00205BF4, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB254,        0x00205BF8, __READ_WRITE, __lcdram_bits);
__IO_REG16_BIT(RGB255,        0x00205BFC, __READ_WRITE, __lcdram_bits);


/***************************************************************************
 **
 ** Universal Asynchronous Receiver/Transmitters (UART) Modules
 **
 ***************************************************************************/
__IO_REG32_BIT(URX0D_1,       0x00206000, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX1D_1,       0x00206004, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX2D_1,       0x00206008, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX3D_1,       0x0020600C, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX4D_1,       0x00206010, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX5D_1,       0x00206014, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX6D_1,       0x00206018, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX7D_1,       0x0020601C, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX8D_1,       0x00206020, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX9D_1,       0x00206024, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX10D_1,      0x00206028, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX11D_1,      0x0020602C, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX12D_1,      0x00206030, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX13D_1,      0x00206034, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX14D_1,      0x00206038, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX15D_1,      0x0020603C, __READ      , __urxndx_bits);
__IO_REG32_BIT(UTX0D_1,       0x00206040, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX1D_1,       0x00206044, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX2D_1,       0x00206048, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX3D_1,       0x0020604C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX4D_1,       0x00206050, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX5D_1,       0x00206054, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX6D_1,       0x00206058, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX7D_1,       0x0020605C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX8D_1,       0x00206060, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX9D_1,       0x00206064, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX10D_1,      0x00206068, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX11D_1,      0x0020606C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX12D_1,      0x00206070, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX13D_1,      0x00206074, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX14D_1,      0x00206078, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX15D_1,      0x0020607C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UCR1_1,        0x00206080, __READ_WRITE, __ucr1x_bits );
__IO_REG32_BIT(UCR2_1,        0x00206084, __READ_WRITE, __ucr2x_bits );
__IO_REG32_BIT(UCR3_1,        0x00206088, __READ_WRITE, __ucr31_bits );
__IO_REG32_BIT(UCR4_1,        0x0020608C, __READ_WRITE, __ucr4x_bits );
__IO_REG32_BIT(UFCR_1,        0x00206090, __READ_WRITE, __ufcrx_bits );
__IO_REG32_BIT(USR1_1,        0x00206094, __READ      , __usr1x_bits );
__IO_REG32_BIT(USR2_1,        0x00206098, __READ      , __usr2x_bits );
__IO_REG32_BIT(UESC_1,        0x0020609C, __READ_WRITE, __uescx_bits );
__IO_REG32_BIT(UTIM_1,        0x002060A0, __READ_WRITE, __utimx_bits );
__IO_REG32_BIT(UBIR_1,        0x002060A4, __READ_WRITE, __ubirx_bits );
__IO_REG32_BIT(UBMR_1,        0x002060A8, __READ_WRITE, __ubmrx_bits );
__IO_REG32_BIT(UBRC_1,        0x002060AC, __READ      , __ubrcx_bits );
__IO_REG32_BIT(BIPR1_1,       0x002060B0, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BIPR2_1,       0x002060B4, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BIPR3_1,       0x002060B8, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BIPR4_1,       0x002060BC, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BMPR1_1,       0x002060C0, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(BMPR2_1,       0x002060C4, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(BMPR3_1,       0x002060C8, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(BMPR4_1,       0x002060CC, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(UTS_1,         0x002060D0, __READ_WRITE, __utsx_bits  );
__IO_REG32_BIT(URX0D_2,       0x00207000, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX1D_2,       0x00207004, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX2D_2,       0x00207008, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX3D_2,       0x0020700C, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX4D_2,       0x00207010, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX5D_2,       0x00207014, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX6D_2,       0x00207018, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX7D_2,       0x0020701C, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX8D_2,       0x00207020, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX9D_2,       0x00207024, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX10D_2,      0x00207028, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX11D_2,      0x0020702C, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX12D_2,      0x00207030, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX13D_2,      0x00207034, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX14D_2,      0x00207038, __READ      , __urxndx_bits);
__IO_REG32_BIT(URX15D_2,      0x0020703C, __READ      , __urxndx_bits);
__IO_REG32_BIT(UTX0D_2,       0x00207040, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX1D_2,       0x00207044, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX2D_2,       0x00207048, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX3D_2,       0x0020704C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX4D_2,       0x00207050, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX5D_2,       0x00207054, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX6D_2,       0x00207058, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX7D_2,       0x0020705C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX8D_2,       0x00207060, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX9D_2,       0x00207064, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX10D_2,      0x00207068, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX11D_2,      0x0020706C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX12D_2,      0x00207070, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX13D_2,      0x00207074, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX14D_2,      0x00207078, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UTX15D_2,      0x0020707C, __WRITE     , __utxndx_bits);
__IO_REG32_BIT(UCR1_2,        0x00207080, __READ_WRITE, __ucr1x_bits );
__IO_REG32_BIT(UCR2_2,        0x00207084, __READ_WRITE, __ucr2x_bits );
__IO_REG32_BIT(UCR3_2,        0x00207088, __READ_WRITE, __ucr32_bits );
__IO_REG32_BIT(UCR4_2,        0x0020708C, __READ_WRITE, __ucr4x_bits );
__IO_REG32_BIT(UFCR_2,        0x00207090, __READ_WRITE, __ufcrx_bits );
__IO_REG32_BIT(USR1_2,        0x00207094, __READ      , __usr1x_bits );
__IO_REG32_BIT(USR2_2,        0x00207098, __READ      , __usr2x_bits );
__IO_REG32_BIT(UESC_2,        0x0020709C, __READ_WRITE, __uescx_bits );
__IO_REG32_BIT(UTIM_2,        0x002070A0, __READ_WRITE, __utimx_bits );
__IO_REG32_BIT(UBIR_2,        0x002070A4, __READ_WRITE, __ubirx_bits );
__IO_REG32_BIT(UBMR_2,        0x002070A8, __READ_WRITE, __ubmrx_bits );
__IO_REG32_BIT(UBRC_2,        0x002070AC, __READ      , __ubrcx_bits );
__IO_REG32_BIT(BIPR1_2,       0x002070B0, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BIPR2_2,       0x002070B4, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BIPR3_2,       0x002070B8, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BIPR4_2,       0x002070BC, __READ_WRITE, __biprnx_bits);
__IO_REG32_BIT(BMPR1_2,       0x002070C0, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(BMPR2_2,       0x002070C4, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(BMPR3_2,       0x002070C8, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(BMPR4_2,       0x002070CC, __READ_WRITE, __bmprnx_bits);
__IO_REG32_BIT(UTS_2,         0x002070D0, __READ_WRITE, __utsx_bits  );

/***************************************************************************
 **
 ** Pulse-Width Modulator (PWM) 
 **
 ***************************************************************************/
__IO_REG32_BIT(PWMC,          0x00208000, __READ_WRITE, __pwmc_bits  ); 
__IO_REG32_BIT(PWMS,          0x00208004, __READ_WRITE, __pwms_bits  ); 
__IO_REG32_BIT(PWMP,          0x00208008, __READ_WRITE, __pwmp_bits  ); 
__IO_REG32_BIT(PWMCNT,        0x0020800C, __READ      , __pwmcnt_bits); 

/***************************************************************************
 **
 ** DMA Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(DCR,           0x00209000, __READ_WRITE, __dcr_bits   );
__IO_REG32_BIT(DISR,          0x00209004, __READ_WRITE, __disr_bits  );
__IO_REG32_BIT(DIMR,          0x00209008, __READ_WRITE, __disr_bits  );
__IO_REG32_BIT(DBTOSR,        0x0020900C, __READ_WRITE, __disr_bits  );
__IO_REG32_BIT(DRTOSR,        0x00209010, __READ_WRITE, __disr_bits  );
__IO_REG32_BIT(DSESR,         0x00209014, __READ_WRITE, __disr_bits  );
__IO_REG32_BIT(DBOSR,         0x00209018, __READ_WRITE, __disr_bits  );
__IO_REG32_BIT(DBTOCR,        0x0020901C, __READ_WRITE, __dbtocr_bits);
__IO_REG32_BIT(WSRA,          0x00209040, __READ_WRITE, __wsrx_bits  );
__IO_REG32_BIT(XSRA,          0x00209044, __READ_WRITE, __xsrx_bits  );
__IO_REG32_BIT(YSRA,          0x00209048, __READ_WRITE, __ysrx_bits  );
__IO_REG32_BIT(WSRB,          0x0020904C, __READ_WRITE, __wsrx_bits  );
__IO_REG32_BIT(XSRB,          0x00209050, __READ_WRITE, __xsrx_bits  );
__IO_REG32_BIT(YSRB,          0x00209054, __READ_WRITE, __ysrx_bits  );
__IO_REG32_BIT(SAR0,          0x00209080, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR0,          0x00209084, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR0,         0x00209088, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR0,          0x0020908C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR0,         0x00209090, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR0,          0x00209094, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR0,         0x00209098, __READ_WRITE, __rtorx_bits );
#define        BUCR0          RTOR0
#define        BUCR0_bit      RTOR0_bit
__IO_REG32_BIT(SAR1,          0x002090C0, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR1,          0x002090C4, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR1,         0x002090C8, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR1,          0x002090CC, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR1,         0x002090D0, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR1,          0x002090D4, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR1,         0x002090D8, __READ_WRITE, __rtorx_bits );
#define        BUCR1          RTOR1
#define        BUCR1_bit      RTOR1_bit
__IO_REG32_BIT(SAR2,          0x00209100, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR2,          0x00209104, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR2,         0x00209108, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR2,          0x0020910C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR2,         0x00209110, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR2,          0x00209114, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR2,         0x00209118, __READ_WRITE, __rtorx_bits );
#define        BUCR2          RTOR2
#define        BUCR2_bit      RTOR2_bit
__IO_REG32_BIT(SAR3,          0x00209140, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR3,          0x00209144, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR3,         0x00209148, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR3,          0x0020914C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR3,         0x00209150, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR3,          0x00209154, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR3,         0x00209158, __READ_WRITE, __rtorx_bits );
#define        BUCR3          RTOR3
#define        BUCR3_bit      RTOR3_bit
__IO_REG32_BIT(SAR4,          0x00209180, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR4,          0x00209184, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR4,         0x00209188, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR4,          0x0020918C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR4,         0x00209190, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR4,          0x00209194, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR4,         0x00209198, __READ_WRITE, __rtorx_bits );
#define        BUCR4          RTOR4
#define        BUCR4_bit      RTOR4_bit
__IO_REG32_BIT(SAR5,          0x002091C0, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR5,          0x002091C4, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR5,         0x002091C8, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR5,          0x002091CC, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR5,         0x002091D0, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR5,          0x002091D4, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR5,         0x002091D8, __READ_WRITE, __rtorx_bits );
#define        BUCR5          RTOR5
#define        BUCR5_bit      RTOR5_bit
__IO_REG32_BIT(SAR6,          0x00209200, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR6,          0x00209204, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR6,         0x00209208, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR6,          0x0020920C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR6,         0x00209210, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR6,          0x00209214, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR6,         0x00209218, __READ_WRITE, __rtorx_bits );
#define        BUCR6          RTOR6
#define        BUCR6_bit      RTOR6_bit
__IO_REG32_BIT(SAR7,          0x00209240, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR7,          0x00209244, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR7,         0x00209248, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR7,          0x0020924C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR7,         0x00209250, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR7,          0x00209254, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR7,         0x00209258, __READ_WRITE, __rtorx_bits );
#define        BUCR7          RTOR7
#define        BUCR7_bit      RTOR7_bit
__IO_REG32_BIT(SAR8,          0x00209280, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR8,          0x00209284, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR8,         0x00209288, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR8,          0x0020928C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR8,         0x00209290, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR8,          0x00209294, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR8,         0x00209298, __READ_WRITE, __rtorx_bits );
#define        BUCR8          RTOR8
#define        BUCR8_bit      RTOR8_bit
__IO_REG32_BIT(SAR9,          0x002092C0, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR9,          0x002092C4, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR9,         0x002092C8, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR9,          0x002092CC, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR9,         0x002092D0, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR9,          0x002092D4, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR9,         0x002092D8, __READ_WRITE, __rtorx_bits );
#define        BUCR9          RTOR9
#define        BUCR9_bit      RTOR9_bit
__IO_REG32_BIT(SAR10,         0x00209300, __READ_WRITE, __sarx_bits  );
__IO_REG32_BIT(DAR10,         0x00209304, __READ_WRITE, __darx_bits  );
__IO_REG32_BIT(CNTR10,        0x00209308, __READ_WRITE, __cntrx_bits );
__IO_REG32_BIT(CCR10,         0x0020930C, __READ_WRITE, __ccrx_bits  );
__IO_REG32_BIT(RSSR10,        0x00209310, __READ_WRITE, __rssrx_bits );
__IO_REG32_BIT(BLR10,         0x00209314, __READ_WRITE, __blrx_bits  );
__IO_REG32_BIT(RTOR10,        0x00209318, __READ_WRITE, __rtorx_bits );
#define        BUCR10         RTOR10
#define        BUCR10_bit     RTOR10_bit

/***************************************************************************
 **
 ** AHB to IP Bus Interface 2 (AIPI2)
 **
 ***************************************************************************/
__IO_REG32_BIT(PSR0_2,        0x00210000, __READ_WRITE, __aipipsr0x_bits);
__IO_REG32_BIT(PSR1_2,        0x00210004, __READ_WRITE, __aipipsr1x_bits);
__IO_REG32_BIT(PAR_2,         0x00210008, __READ_WRITE, __aipiparx_bits );
__IO_REG32_BIT(PCR_2,         0x0021000C, __READ_WRITE, __aipipcrx_bits );
__IO_REG32_BIT(TSR_2,         0x00210010, __READ_WRITE, __aipitsrx_bits );

/***************************************************************************
 **
 ** USB Device Port
 **
 ***************************************************************************/
__IO_REG32_BIT(USB_FRAME,     0x00212000, __READ_WRITE, __usbframe_bits   ); 
__IO_REG32_BIT(USB_SPEC,      0x00212004, __READ      , __usbspec_bits    ); 
__IO_REG32_BIT(USB_STAT,      0x00212008, __READ      , __usbstat_bits    ); 
__IO_REG32_BIT(USB_CTRL,      0x0021200C, __READ_WRITE, __usbctrl_bits    ); 
__IO_REG32_BIT(USB_DADR,      0x00212010, __READ_WRITE, __usbdadr_bits    ); 
__IO_REG32_BIT(USB_DDAT,      0x00212014, __READ_WRITE, __usbddat_bits    ); 
__IO_REG32_BIT(USB_INTR,      0x00212018, __READ_WRITE, __usbintr_bits    ); 
__IO_REG32_BIT(USB_MASK,      0x0021201C, __READ_WRITE, __usbintr_bits    ); 
__IO_REG32_BIT(USB_ENAB,      0x00212024, __READ_WRITE, __usbenab_bits    ); 
__IO_REG32_BIT(USB_EP0_STAT,  0x00212030, __READ_WRITE, __usbepxstat_bits ); 
__IO_REG32_BIT(USB_EP0_INTR,  0x00212034, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32_BIT(USB_EP0_MASK,  0x00212038, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32(    USB_EP0_FDAT,  0x0021203C, __READ_WRITE                    ); 
__IO_REG32_BIT(USB_EP0_FSTAT, 0x00212040, __READ_WRITE, __usbepxfstat_bits); 
__IO_REG32_BIT(USB_EP0_FCTRL, 0x00212044, __READ_WRITE, __usbepxfctrl_bits); 
__IO_REG32_BIT(USB_EP0_LRFP,  0x00212048, __READ_WRITE, __usbepxlrfp_bits ); 
__IO_REG32_BIT(USB_EP0_LWFP,  0x0021204C, __READ_WRITE, __usbepxlwfp_bits ); 
__IO_REG32_BIT(USB_EP0_FALRM, 0x00212050, __READ_WRITE, __usbepxfalrm_bits); 
__IO_REG32_BIT(USB_EP0_FRDP,  0x00212054, __READ_WRITE, __usbepxfrdp_bits ); 
__IO_REG32_BIT(USB_EP0_FWRP,  0x00212058, __READ_WRITE, __usbepxfwrp_bits ); 
__IO_REG32_BIT(USB_EP1_STAT,  0x00212060, __READ_WRITE, __usbepxstat_bits ); 
__IO_REG32_BIT(USB_EP1_INTR,  0x00212064, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32_BIT(USB_EP1_MASK,  0x00212068, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32(    USB_EP1_FDAT,  0x0021206C, __READ_WRITE                    ); 
__IO_REG32_BIT(USB_EP1_FSTAT, 0x00212070, __READ_WRITE, __usbepxfstat_bits); 
__IO_REG32_BIT(USB_EP1_FCTRL, 0x00212074, __READ_WRITE, __usbepxfctrl_bits); 
__IO_REG32_BIT(USB_EP1_LRFP,  0x00212078, __READ_WRITE, __usbepxlrfp_bits ); 
__IO_REG32_BIT(USB_EP1_LWFP,  0x0021207C, __READ_WRITE, __usbepxlwfp_bits ); 
__IO_REG32_BIT(USB_EP1_FALRM, 0x00212080, __READ_WRITE, __usbepxfalrm_bits); 
__IO_REG32_BIT(USB_EP1_FRDP,  0x00212084, __READ_WRITE, __usbepxfrdp_bits ); 
__IO_REG32_BIT(USB_EP1_FWRP,  0x00212088, __READ_WRITE, __usbepxfwrp_bits ); 
__IO_REG32_BIT(USB_EP2_STAT,  0x00212090, __READ_WRITE, __usbepxstat_bits ); 
__IO_REG32_BIT(USB_EP2_INTR,  0x00212094, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32_BIT(USB_EP2_MASK,  0x00212098, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32(    USB_EP2_FDAT,  0x0021209C, __READ_WRITE                    ); 
__IO_REG32_BIT(USB_EP2_FSTAT, 0x002120A0, __READ_WRITE, __usbepxfstat_bits); 
__IO_REG32_BIT(USB_EP2_FCTRL, 0x002120A4, __READ_WRITE, __usbepxfctrl_bits); 
__IO_REG32_BIT(USB_EP2_LRFP,  0x002120A8, __READ_WRITE, __usbepxlrfp_bits ); 
__IO_REG32_BIT(USB_EP2_LWFP,  0x002120AC, __READ_WRITE, __usbepxlwfp_bits ); 
__IO_REG32_BIT(USB_EP2_FALRM, 0x002120B0, __READ_WRITE, __usbepxfalrm_bits); 
__IO_REG32_BIT(USB_EP2_FRDP,  0x002120B4, __READ_WRITE, __usbepxfrdp_bits ); 
__IO_REG32_BIT(USB_EP2_FWRP,  0x002120B8, __READ_WRITE, __usbepxfwrp_bits ); 
__IO_REG32_BIT(USB_EP3_STAT,  0x002120C0, __READ_WRITE, __usbepxstat_bits ); 
__IO_REG32_BIT(USB_EP3_INTR,  0x002120C4, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32_BIT(USB_EP3_MASK,  0x002120C8, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32(    USB_EP3_FDAT,  0x002120CC, __READ_WRITE                    ); 
__IO_REG32_BIT(USB_EP3_FSTAT, 0x002120D0, __READ_WRITE, __usbepxfstat_bits); 
__IO_REG32_BIT(USB_EP3_FCTRL, 0x002120D4, __READ_WRITE, __usbepxfctrl_bits); 
__IO_REG32_BIT(USB_EP3_LRFP,  0x002120D8, __READ_WRITE, __usbepxlrfp_bits ); 
__IO_REG32_BIT(USB_EP3_LWFP,  0x002120DC, __READ_WRITE, __usbepxlwfp_bits ); 
__IO_REG32_BIT(USB_EP3_FALRM, 0x002120E0, __READ_WRITE, __usbepxfalrm_bits); 
__IO_REG32_BIT(USB_EP3_FRDP,  0x002120E4, __READ_WRITE, __usbepxfrdp_bits ); 
__IO_REG32_BIT(USB_EP3_FWRP,  0x002120E8, __READ_WRITE, __usbepxfwrp_bits ); 
__IO_REG32_BIT(USB_EP4_STAT,  0x002120F0, __READ_WRITE, __usbepxstat_bits ); 
__IO_REG32_BIT(USB_EP4_INTR,  0x002120F4, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32_BIT(USB_EP4_MASK,  0x002120F8, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32(    USB_EP4_FDAT,  0x002120FC, __READ_WRITE                    ); 
__IO_REG32_BIT(USB_EP4_FSTAT, 0x00212100, __READ_WRITE, __usbepxfstat_bits); 
__IO_REG32_BIT(USB_EP4_FCTRL, 0x00212104, __READ_WRITE, __usbepxfctrl_bits); 
__IO_REG32_BIT(USB_EP4_LRFP,  0x00212108, __READ_WRITE, __usbepxlrfp_bits ); 
__IO_REG32_BIT(USB_EP4_LWFP,  0x0021210C, __READ_WRITE, __usbepxlwfp_bits ); 
__IO_REG32_BIT(USB_EP4_FALRM, 0x00212110, __READ_WRITE, __usbepxfalrm_bits); 
__IO_REG32_BIT(USB_EP4_FRDP,  0x00212114, __READ_WRITE, __usbepxfrdp_bits ); 
__IO_REG32_BIT(USB_EP4_FWRP,  0x00212118, __READ_WRITE, __usbepxfwrp_bits ); 
__IO_REG32_BIT(USB_EP5_STAT,  0x00212120, __READ_WRITE, __usbepxstat_bits ); 
__IO_REG32_BIT(USB_EP5_INTR,  0x00212124, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32_BIT(USB_EP5_MASK,  0x00212128, __READ_WRITE, __usbepxintr_bits ); 
__IO_REG32(    USB_EP5_FDAT,  0x0021212C, __READ_WRITE                    ); 
__IO_REG32_BIT(USB_EP5_FSTAT, 0x00212130, __READ_WRITE, __usbepxfstat_bits); 
__IO_REG32_BIT(USB_EP5_FCTRL, 0x00212134, __READ_WRITE, __usbepxfctrl_bits); 
__IO_REG32_BIT(USB_EP5_LRFP,  0x00212138, __READ_WRITE, __usbepxlrfp_bits ); 
__IO_REG32_BIT(USB_EP5_LWFP,  0x0021213C, __READ_WRITE, __usbepxlwfp_bits ); 
__IO_REG32_BIT(USB_EP5_FALRM, 0x00212140, __READ_WRITE, __usbepxfalrm_bits); 
__IO_REG32_BIT(USB_EP5_FRDP,  0x00212144, __READ_WRITE, __usbepxfrdp_bits ); 
__IO_REG32_BIT(USB_EP5_FWRP,  0x00212148, __READ_WRITE, __usbepxfwrp_bits ); 

/***************************************************************************
 **
 ** SPI Module (SPI1)
 **
 ***************************************************************************/
__IO_REG32_BIT(RXDATAREG1,    0x00213000, __READ      , __rxdataregx_bits );
__IO_REG32_BIT(TXDATAREG1,    0x00213004, __WRITE     , __txdataregx_bits );
__IO_REG32_BIT(CONTROLREG1,   0x00213008, __READ_WRITE, __controlregx_bits);
__IO_REG32_BIT(INTREG1,       0x0021300C, __READ_WRITE, __intregx_bits    );
__IO_REG32_BIT(TESTREG1,      0x00213010, __READ_WRITE, __testregx_bits   );
__IO_REG32_BIT(PERIODREG1,    0x00213014, __READ_WRITE, __periodregx_bits );
__IO_REG32_BIT(DMAREG1,       0x00213018, __READ_WRITE, __dmaregx_bits    );
__IO_REG32_BIT(RESETREG1,     0x0021301C, __READ_WRITE, __resetregx_bits  );

/***************************************************************************
 **
 ** Multimedia Card/Secure Digital Host Controller Module
 **
 ***************************************************************************/
__IO_REG32_BIT(STR_STP_CLK,   0x00214000, __READ_WRITE, __strstpclk_bits   ); 
__IO_REG32_BIT(STATUS,        0x00214004, __READ      , __status_bits      ); 
__IO_REG32_BIT(CLK_RATE,      0x00214008, __READ_WRITE, __clkrate_bits     ); 
__IO_REG32_BIT(CMD_DAT_CONT,  0x0021400C, __READ_WRITE, __cmddatcont_bits  ); 
__IO_REG32_BIT(RES_TO,        0x00214010, __READ_WRITE, __resto_bits       ); 
__IO_REG32_BIT(READ_TO,       0x00214014, __READ_WRITE, __readto_bits      ); 
__IO_REG32_BIT(BLK_LEN,       0x00214018, __READ_WRITE, __blklen_bits      ); 
__IO_REG32_BIT(NOB,           0x0021401C, __READ_WRITE, __nob_bits         ); 
__IO_REG32_BIT(REV_NO,        0x00214020, __READ      , __revno_bits       ); 
__IO_REG32_BIT(INT_MASK,      0x00214024, __READ_WRITE, __intmask_bits     ); 
__IO_REG32_BIT(CMD,           0x00214028, __READ_WRITE, __cmd_bits         ); 
__IO_REG32_BIT(ARGH,          0x0021402C, __READ_WRITE, __argh_bits        ); 
__IO_REG32_BIT(ARGL,          0x00214030, __READ_WRITE, __argl_bits        ); 
__IO_REG32_BIT(RES_FIFO,      0x00214034, __READ      , __resfifo_bits     ); 
__IO_REG32_BIT(BUFFER_ACCESS, 0x00214038, __READ_WRITE, __bufferaccess_bits); 

/***************************************************************************
 **
 ** I2C Module
 **
 ***************************************************************************/
__IO_REG32_BIT(IADR,          0x00217000, __READ_WRITE, __iadr_bits  );
__IO_REG32_BIT(IFDR,          0x00217004, __READ_WRITE, __ifdr_bits  );
__IO_REG32_BIT(I2CR,          0x00217008, __READ_WRITE, __i2cr_bits  );
__IO_REG32_BIT(I2SR,          0x0021700C, __READ_WRITE, __i2sr_bits  );
__IO_REG32_BIT(I2DR,          0x00217010, __READ_WRITE, __i2dr_bits  );

/***************************************************************************
 **
 ** Synchronous Serial Interface (SSI) 
 **
 ***************************************************************************/
__IO_REG32_BIT(STX,           0x00218000, __READ_WRITE, __stx_bits  );
__IO_REG32_BIT(SRX,           0x00218004, __READ      , __stx_bits  );
__IO_REG32_BIT(SCSR,          0x00218008, __READ_WRITE, __scsr_bits );
__IO_REG32_BIT(STCR,          0x0021800C, __READ_WRITE, __stcr_bits );
__IO_REG32_BIT(SRCR,          0x00218010, __READ_WRITE, __srcr_bits );
__IO_REG32_BIT(STCCR,         0x00218014, __READ_WRITE, __sxccr_bits);
__IO_REG32_BIT(SRCCR,         0x00218018, __READ_WRITE, __sxccr_bits);
__IO_REG32_BIT(STSR,          0x0021801C, __WRITE     , __stsr_bits );
__IO_REG32_BIT(SFCSR,         0x00218020, __READ_WRITE, __sfcsr_bits);
__IO_REG32_BIT(SOR,           0x00218024, __READ_WRITE, __sor_bits  );

/***************************************************************************
 **
 ** SPI Module (SPI2)
 **
 ***************************************************************************/
__IO_REG32_BIT(RXDATAREG2,    0x00219000, __READ      , __rxdataregx_bits );
__IO_REG32_BIT(TXDATAREG2,    0x00219004, __WRITE     , __txdataregx_bits );
__IO_REG32_BIT(CONTROLREG2,   0x00219008, __READ_WRITE, __controlregx_bits);
__IO_REG32_BIT(INTREG2,       0x0021900C, __READ_WRITE, __intregx_bits    );
__IO_REG32_BIT(TESTREG2,      0x00219010, __READ_WRITE, __testregx_bits   );
__IO_REG32_BIT(PERIODREG2,    0x00219014, __READ_WRITE, __periodregx_bits );
__IO_REG32_BIT(DMAREG2,       0x00219018, __READ_WRITE, __dmaregx_bits    );
__IO_REG32_BIT(RESETREG2,     0x0021901C, __READ_WRITE, __resetregx_bits  );

/***************************************************************************
 **
 ** Memory Stick Host Controller Module
 **
 ***************************************************************************/
__IO_REG16_BIT(MSCMD,         0x0021A000, __READ_WRITE, __mscmd_bits  ); 
__IO_REG16_BIT(MSCS,          0x0021A002, __READ_WRITE, __mscs_bits   ); 
__IO_REG16_BIT(MSTDATA,       0x0021A004, __READ_WRITE, __msxdata_bits);
#define        MSRDATA        MSTDATA
#define        MSRDATA_bit    MSTDATA_bit 
__IO_REG16_BIT(MSICS,         0x0021A006, __READ_WRITE, __msics_bits  ); 
__IO_REG16_BIT(MSPPCD,        0x0021A008, __READ_WRITE, __msppcd_bits ); 
__IO_REG16_BIT(MSC2,          0x0021A00A, __READ_WRITE, __msc2_bits   ); 
__IO_REG16_BIT(MSACD,         0x0021A00C, __READ_WRITE, __msacd_bits  ); 
__IO_REG16_BIT(MSFAECS,       0x0021A00E, __READ_WRITE, __msfaecs_bits); 
__IO_REG16_BIT(MSCLKD,        0x0021A010, __READ_WRITE, __msclkd_bits ); 
__IO_REG16_BIT(MSDRQC,        0x0021A012, __READ_WRITE, __msdrqc_bits ); 

/***************************************************************************
 **
 ** Phase-Locked Loop and Clock Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(CSCR,          0x0021B000, __READ_WRITE, __cscr_bits  );
__IO_REG32_BIT(MPCTL0,        0x0021B004, __READ_WRITE, __mpctl0_bits);
__IO_REG32_BIT(MPCTL1,        0x0021B008, __READ_WRITE, __mpctl1_bits);
__IO_REG32_BIT(SPCTL0,        0x0021B00C, __READ_WRITE, __mpctl0_bits);
__IO_REG32_BIT(SPCTL1,        0x0021B010, __READ_WRITE, __spctl1_bits);
__IO_REG32_BIT(PCDR,          0x0021B020, __READ_WRITE, __pcdr_bits  );

/***************************************************************************
 **
 ** Reset Module
 **
 ***************************************************************************/
__IO_REG32_BIT(RSR,           0x0021B800, __READ      , __rsr_bits);


/***************************************************************************
 **
 ** System Control
 **
 ***************************************************************************/
__IO_REG32(    SIDR,          0x0021B804, __READ                   );
__IO_REG32_BIT(FMCR,          0x0021B808, __READ_WRITE, __fmcr_bits);
__IO_REG32_BIT(GPCR,          0x0021B80C, __READ_WRITE, __gpcr_bits);
__IO_REG32_BIT(GCCR,          0x0021B810, __READ_WRITE, __gccr_bits);

/***************************************************************************
 **
 ** GPIOA 
 **
 ***************************************************************************/
__IO_REG32(    DDIR_A,        0x0021C000, __READ_WRITE              );
__IO_REG32_BIT(OCR1_A,        0x0021C004, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(OCR2_A,        0x0021C008, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFA1_A,     0x0021C00C, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFA2_A,     0x0021C010, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFB1_A,     0x0021C014, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFB2_A,     0x0021C018, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    DR_A,          0x0021C01C, __READ_WRITE              );
__IO_REG32(    GIUS_A,        0x0021C020, __READ_WRITE              );
__IO_REG32(    SSR_A,         0x0021C024, __READ                    );
__IO_REG32_BIT(ICR1_A,        0x0021C028, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICR2_A,        0x0021C02C, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    IMR_A,         0x0021C030, __READ_WRITE              );
__IO_REG32(    ISR_A,         0x0021C034, __READ_WRITE              );
__IO_REG32(    GPR_A,         0x0021C038, __READ_WRITE              );
__IO_REG32_BIT(SWR_A,         0x0021C03C, __READ_WRITE, __swrx_bits );
__IO_REG32(    PUEN_A,        0x0021C040, __READ_WRITE              );

/***************************************************************************
 **
 ** GPIOB 
 **
 ***************************************************************************/
__IO_REG32(    DDIR_B,        0x0021C100, __READ_WRITE              );
__IO_REG32_BIT(OCR1_B,        0x0021C104, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(OCR2_B,        0x0021C108, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFA1_B,     0x0021C10C, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFA2_B,     0x0021C110, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFB1_B,     0x0021C114, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFB2_B,     0x0021C118, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    DR_B,          0x0021C11C, __READ_WRITE              );
__IO_REG32(    GIUS_B,        0x0021C120, __READ_WRITE              );
__IO_REG32(    SSR_B,         0x0021C124, __READ                    );
__IO_REG32_BIT(ICR1_B,        0x0021C128, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICR2_B,        0x0021C12C, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    IMR_B,         0x0021C130, __READ_WRITE              );
__IO_REG32(    ISR_B,         0x0021C134, __READ_WRITE              );
__IO_REG32(    GPR_B,         0x0021C138, __READ_WRITE              );
__IO_REG32_BIT(SWR_B,         0x0021C13C, __READ_WRITE, __swrx_bits );
__IO_REG32(    PUEN_B,        0x0021C140, __READ_WRITE              );

/***************************************************************************
 **
 ** GPIOC 
 **
 ***************************************************************************/
__IO_REG32(    DDIR_C,        0x0021C200, __READ_WRITE              );
__IO_REG32_BIT(OCR1_C,        0x0021C204, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(OCR2_C,        0x0021C208, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFA1_C,     0x0021C20C, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFA2_C,     0x0021C210, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFB1_C,     0x0021C214, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFB2_C,     0x0021C218, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    DR_C,          0x0021C21C, __READ_WRITE              );
__IO_REG32(    GIUS_C,        0x0021C220, __READ_WRITE              );
__IO_REG32(    SSR_C,         0x0021C224, __READ                    );
__IO_REG32_BIT(ICR1_C,        0x0021C228, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICR2_C,        0x0021C22C, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    IMR_C,         0x0021C230, __READ_WRITE              );
__IO_REG32(    ISR_C,         0x0021C234, __READ_WRITE              );
__IO_REG32(    GPR_C,         0x0021C238, __READ_WRITE              );
__IO_REG32_BIT(SWR_C,         0x0021C23C, __READ_WRITE, __swrx_bits );
__IO_REG32(    PUEN_C,        0x0021C240, __READ_WRITE              );

/***************************************************************************
 **
 ** GPIOD 
 **
 ***************************************************************************/
__IO_REG32(    DDIR_D,        0x0021C300, __READ_WRITE              );
__IO_REG32_BIT(OCR1_D,        0x0021C304, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(OCR2_D,        0x0021C308, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFA1_D,     0x0021C30C, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFA2_D,     0x0021C310, __READ_WRITE, __ocr2x_bits);
__IO_REG32_BIT(ICONFB1_D,     0x0021C314, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICONFB2_D,     0x0021C318, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    DR_D,          0x0021C31C, __READ_WRITE              );
__IO_REG32(    GIUS_D,        0x0021C320, __READ_WRITE              );
__IO_REG32(    SSR_D,         0x0021C324, __READ                    );
__IO_REG32_BIT(ICR1_D,        0x0021C328, __READ_WRITE, __ocr1x_bits);
__IO_REG32_BIT(ICR2_D,        0x0021C32C, __READ_WRITE, __ocr2x_bits);
__IO_REG32(    IMR_D,         0x0021C330, __READ_WRITE              );
__IO_REG32(    ISR_D,         0x0021C334, __READ_WRITE              );
__IO_REG32(    GPR_D,         0x0021C338, __READ_WRITE              );
__IO_REG32_BIT(SWR_D,         0x0021C33C, __READ_WRITE, __swrx_bits );
__IO_REG32(    PUEN_D,        0x0021C340, __READ_WRITE              );

/***************************************************************************
 **
 ** External Interface Module (EIM)
 **
 ***************************************************************************/
__IO_REG32_BIT(CS0U,          0x00220000, __READ_WRITE, __cs0u_bits);
__IO_REG32_BIT(CS0L,          0x00220004, __READ_WRITE, __cs0l_bits);
__IO_REG32_BIT(CS1U,          0x00220008, __READ_WRITE, __csxu_bits);
__IO_REG32_BIT(CS1L,          0x0022000C, __READ_WRITE, __csxl_bits);
__IO_REG32_BIT(CS2U,          0x00220010, __READ_WRITE, __csxu_bits);
__IO_REG32_BIT(CS2L,          0x00220014, __READ_WRITE, __csxl_bits);
__IO_REG32_BIT(CS3U,          0x00220018, __READ_WRITE, __csxu_bits);
__IO_REG32_BIT(CS3L,          0x0022001C, __READ_WRITE, __csxl_bits);
__IO_REG32_BIT(CS4U,          0x00220020, __READ_WRITE, __csxu_bits);
__IO_REG32_BIT(CS4L,          0x00220024, __READ_WRITE, __csxl_bits);
__IO_REG32_BIT(CS5U,          0x00220028, __READ_WRITE, __csxu_bits);
__IO_REG32_BIT(CS5L,          0x0022002C, __READ_WRITE, __csxl_bits);
__IO_REG32_BIT(EIM,           0x00220030, __READ_WRITE, __eim_bits );

/***************************************************************************
 **
 ** SDRAM Memory Controller 
 **
 ***************************************************************************/
__IO_REG32_BIT(SDCTL0,        0x00221000, __READ_WRITE, __sdctlx_bits       ); 
__IO_REG32_BIT(SDCTL1,        0x00221004, __READ_WRITE, __sdctlx_bits       ); 
__IO_REG32_BIT(MISCELLANEOUS, 0x00221008, __READ_WRITE, __miscellaneous_bits); 
__IO_REG32_BIT(SDRST,         0x0022100C, __WRITE     , __sdrst_bits        ); 

/***************************************************************************
 **
 ** Multimedia Accelerator (MMA)
 **
 ***************************************************************************/
__IO_REG32_BIT(MMA_MAC_MOD,         0x00222000, __READ_WRITE, __mmamacmod_bits     );
__IO_REG32_BIT(MMA_MAC_CTRL,        0x00222004, __READ_WRITE, __mmamacctrl_bits    );
__IO_REG32_BIT(MMA_MAC_MULT,        0x00222008, __READ_WRITE, __mmamacmult_bits    );
__IO_REG32_BIT(MMA_MAC_ACCU,        0x0022200C, __READ_WRITE, __mmamacaccu_bits    );
__IO_REG32_BIT(MMA_MAC_INTR,        0x00222010, __READ_WRITE, __mmamacintr_bits    );
__IO_REG32_BIT(MMA_MAC_INTR_MASK,   0x00222014, __READ_WRITE, __mmamacintr_bits    );
__IO_REG32(    MMA_MAC_FIFO,        0x00222018, __READ                             );
__IO_REG32_BIT(MMA_MAC_FIFO_STAT,   0x0022201C, __READ      , __mmamacfifostat_bits);
__IO_REG32_BIT(MMA_MAC_BURST,       0x00222020, __READ_WRITE, __mmamacburst_bits   );
__IO_REG32_BIT(MMA_MAC_BITSEL,      0x00222024, __READ_WRITE, __mmamacbitsel_bits  );
__IO_REG32(    MMA_MAC_XYACCU,      0x00222040, __WRITE                            );
__IO_REG32(    MMA_MAC_XBASE,       0x00222200, __READ_WRITE                       );
__IO_REG32_BIT(MMA_MAC_XINDEX,      0x00222204, __READ_WRITE, __mmamacxindex_bits  );
__IO_REG32_BIT(MMA_MAC_XLENGTH,     0x00222208, __READ_WRITE, __mmamacxlength_bits );
__IO_REG32_BIT(MMA_MAC_XMODIFY,     0x0022220C, __READ_WRITE, __mmamacxmodify_bits );
__IO_REG32_BIT(MMA_MAC_XINCR,       0x00222210, __READ_WRITE, __mmamacxincr_bits   );
__IO_REG32_BIT(MMA_MAC_XCOUNT,      0x00222214, __READ_WRITE, __mmamacxcount_bits  ); 
__IO_REG32(    MMA_MAC_YBASE,       0x00222300, __READ_WRITE                       );
__IO_REG32_BIT(MMA_MAC_YINDEX,      0x00222304, __READ_WRITE, __mmamacyindex_bits  );
__IO_REG32_BIT(MMA_MAC_YLENGTH,     0x00222308, __READ_WRITE, __mmamacylength_bits );
__IO_REG32_BIT(MMA_MAC_YMODIFY,     0x0022230C, __READ_WRITE, __mmamacymodify_bits );
__IO_REG32_BIT(MMA_MAC_YINCR,       0x00222310, __READ_WRITE, __mmamacyincr_bits   );
__IO_REG32_BIT(MMA_MAC_YCOUNT,      0x00222314, __READ_WRITE, __mmamacycount_bits  ); 
__IO_REG32_BIT(MMA_DCTCTRL,         0x00222400, __READ_WRITE, __mmadctctrl_bits    ); 
__IO_REG32(    MMA_DCTVERSION,      0x00222404, __READ                             );
__IO_REG32_BIT(MMA_DCTIRQENA,       0x00222408, __READ_WRITE, __mmadctirqena_bits  );
__IO_REG32_BIT(MMA_DCTIRQSTAT,      0x0022240C, __READ_WRITE, __mmadctirqstat_bits );
__IO_REG32(    MMA_DCTSRCDATA,      0x00222410, __READ_WRITE                       );
__IO_REG32(    MMA_DCTDESDATA,      0x00222414, __READ_WRITE                       );
__IO_REG32_BIT(MMA_DCTXOFF,         0x00222418, __READ_WRITE, __mmadctxoff_bits    );
__IO_REG32_BIT(MMA_DCTYOFF,         0x0022241C, __READ_WRITE, __mmadctyoff_bits    );
__IO_REG32_BIT(MMA_DCTXYCNT,        0x00222420, __READ_WRITE, __mmadctxycnt_bits   );
__IO_REG32_BIT(MMA_DCTSKIP,         0x00222424, __READ_WRITE, __mmadctskip_bits    );
__IO_REG32(    MMA_DCTFIFO,         0x00222500, __READ_WRITE                       );

/***************************************************************************
 **
 ** Interrupt Control (AITC)
 **
 ***************************************************************************/
__IO_REG32_BIT(INTCNTL,       0x00223000, __READ_WRITE, __intcntl_bits    );
__IO_REG32_BIT(NIMASK,        0x00223004, __READ_WRITE, __nimask_bits     );
__IO_REG32_BIT(INTENNUM,      0x00223008, __READ_WRITE, __intennum_bits   );
__IO_REG32_BIT(INTDISNUM,     0x0022300C, __READ_WRITE, __intdisnum_bits  );
__IO_REG32(    INTENABLEH,    0x00223010, __READ_WRITE                    );
__IO_REG32(    INTENABLEL,    0x00223014, __READ_WRITE                    );
__IO_REG32(    INTTYPEH,      0x00223018, __READ_WRITE                    );
__IO_REG32(    INTTYPEL,      0x0022301C, __READ_WRITE                    );
__IO_REG32_BIT(NIPRIORITY7,   0x00223020, __READ_WRITE, __nipriority7_bits);
__IO_REG32_BIT(NIPRIORITY6,   0x00223024, __READ_WRITE, __nipriority6_bits);
__IO_REG32_BIT(NIPRIORITY5,   0x00223028, __READ_WRITE, __nipriority5_bits);
__IO_REG32_BIT(NIPRIORITY4,   0x0022302C, __READ_WRITE, __nipriority4_bits);
__IO_REG32_BIT(NIPRIORITY3,   0x00223030, __READ_WRITE, __nipriority3_bits);
__IO_REG32_BIT(NIPRIORITY2,   0x00223034, __READ_WRITE, __nipriority2_bits);
__IO_REG32_BIT(NIPRIORITY1,   0x00223038, __READ_WRITE, __nipriority1_bits);
__IO_REG32_BIT(NIPRIORITY0,   0x0022303C, __READ_WRITE, __nipriority0_bits);
__IO_REG32_BIT(NIVECSR,       0x00223040, __READ      , __nivecsr_bits    );
__IO_REG32(    FIVECSR,       0x00223044, __READ                          );
__IO_REG32(    INTSRCH,       0x00223048, __READ                          );
__IO_REG32(    INTSRCL,       0x0022304C, __READ                          );
__IO_REG32(    INTFRCH,       0x00223050, __READ_WRITE                    );
__IO_REG32(    INTFRCL,       0x00223054, __READ_WRITE                    );
__IO_REG32(    NIPNDH,        0x00223058, __READ                          );
__IO_REG32(    NIPNDL,        0x0022305C, __READ                          );
__IO_REG32(    FIPNDH,        0x00223060, __READ                          );
__IO_REG32(    FIPNDL,        0x00223064, __READ                          );

/***************************************************************************
 **
 ** CMOS Sensor Interface Module
 **
 ***************************************************************************/
__IO_REG32_BIT(CSICR1,        0x00224000, __READ_WRITE, __csicr1_bits);
__IO_REG32_BIT(CSICR2,        0x00224004, __READ_WRITE, __csicr2_bits);
__IO_REG32_BIT(CSISR,         0x00224008, __READ_WRITE, __csisr_bits );
__IO_REG32(    CSISTATR,      0x0022400C, __READ                     );
__IO_REG32(    CSIRXR,        0x00224010, __READ                     );

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 ** MC9328MXL Interrupt Codes
 **
 ***************************************************************************/
#define INO_CSI_INT                6
#define INO_MMA_MAC_INT            7
#define INO_MMA_INT                8
#define INO_MSIRQ                 10
#define INO_GPIO_INT_PORTA        11
#define INO_GPIO_INT_PORTB        12
#define INO_GPIO_INT_PORTC        13
#define INO_LCDC_INT              14
#define INO_RTC_INT               17
#define INO_RTC_SAM_INT           18
#define INO_UART2_MINT_PFERR      19
#define INO_UART2_MINT_RTS        20
#define INO_UART2_MINT_DTR        21
#define INO_UART2_MINT_UARTC      22
#define INO_UART2_MINT_TX         23
#define INO_UART2_MINT_RX         24
#define INO_UART1_MINT_PFERR      25
#define INO_UART1_MINT_RTS        26
#define INO_UART1_MINT_DTR        27
#define INO_UART1_MINT_UARTC      28
#define INO_UART1_MINT_TX         29
#define INO_UART1_MINT_RX         30
#define INO_PWM_INT               34
#define INO_MMC_IRQ               35
#define INO_I2C_INT               39
#define INO_SPI2_INT              40
#define INO_SPI1_INT              41
#define INO_SSI_TX_INT            42
#define INO_SSI_TX_ERR_INT        43
#define INO_SSI_RX_INT            44
#define INO_SSI_RX_ERR_INT        45
#define INO_USBD_INT0             47
#define INO_USBD_INT1             48
#define INO_USBD_INT2             49
#define INO_USBD_INT3             50
#define INO_USBD_INT4             51
#define INO_USBD_INT5             52
#define INO_USBD_INT6             53
#define INO_TIMER2_INT            58
#define INO_TIMER1_INT            59
#define INO_DMA_ERR               60
#define INO_DMA_INT               61
#define INO_GPIO_INT_PORTD        62
#define INO_WDT_INT               63

#endif	/* __IOMC9328MXL_H */




