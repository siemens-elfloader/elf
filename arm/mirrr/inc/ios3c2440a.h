/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C2440A
 **
 **     Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **   (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.5 $
 **
 ***************************************************************************/

#ifndef __S3C2440A_H
#define __S3C2440A_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C2440A SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Memory Controller - Bus Width & Wait Control Register */
typedef struct {
 __REG32      : 1;
 __REG32 DW0  : 2;
 __REG32      : 1;
 __REG32 DW1  : 2;
 __REG32 WS1  : 1;
 __REG32 ST1  : 1;
 __REG32 DW2  : 2;
 __REG32 WS2  : 1;
 __REG32 ST2  : 1;
 __REG32 DW3  : 2;
 __REG32 WS3  : 1;
 __REG32 ST3  : 1;
 __REG32 DW4  : 2;
 __REG32 WS4  : 1;
 __REG32 ST4  : 1;
 __REG32 DW5  : 2;
 __REG32 WS5  : 1;
 __REG32 ST5  : 1;
 __REG32 DW6  : 2;
 __REG32 WS6  : 1;
 __REG32 ST6  : 1;
 __REG32 DW7  : 2;
 __REG32 WS7  : 1;
 __REG32 ST7  : 1;
} __bwscon_bits;

/* Memory Controller - Bank Control Register nGCS0-5 */
typedef struct {
  __REG32 PMC   : 2;
  __REG32 Tacp  : 2;
  __REG32 Tcah  : 2;
  __REG32 Tcoh  : 2;
  __REG32 Tacc  : 3;
  __REG32 Tcos  : 2;
  __REG32 Tacs  : 2;
  __REG32       :17;
} __bankconn_bits;

/* Memory Controller - Bank Control Register nGCS6-7 */
typedef union {
  //BANKCONx
  struct {
  __REG32 PMC   : 2;
  __REG32 Tacp  : 2;
  __REG32 Tcah  : 2;
  __REG32 Tcoh  : 2;
  __REG32 Tacc  : 3;
  __REG32 Tcos  : 2;
  __REG32 Tacs  : 2;
  __REG32 MT    : 2;
  __REG32       :15;
  };
  //BANKCONx
  struct {
    __REG32 SCAN  : 2;
    __REG32 Trcd  : 2;
    __REG32       :28;
  };
} __bankconn2_bits;

/* Memory Controller - Refresh Control Register */
typedef struct {
  __REG32 RefreshCounter  :11;
  __REG32                 : 5;
  __REG32                 : 2;
  __REG32 Tsrc            : 2;
  __REG32 Trp             : 2;
  __REG32 TREFMD          : 1;
  __REG32 REFEN           : 1;
  __REG32                 : 8;
} __refresh_bits;

/* Memory Controller - Banksize Register */
typedef struct {
  __REG32 BK76MAP   : 3;
  __REG32           : 1;
  __REG32 SCLK_EN   : 1;
  __REG32 SCKE_EN   : 1;
  __REG32           : 1;
  __REG32 BURST_EN  : 1;
  __REG32           : 24;
} __banksize_bits;

/* Memory Controller - SDRAM Mode Register Set Register (MRSR) */
typedef struct {
  __REG32 BL  : 3;
  __REG32 BT  : 1;
  __REG32 CL  : 3;
  __REG32 TM  : 2;
  __REG32 WBL : 1;
  __REG32     : 2;
  __REG32     :20;
} __mrsrbx_bits;


/* USB Host - hc revision register */
typedef struct{
__REG32 REV  : 8;
__REG32      :24;
} __hcrevision_bits;

/* USB Host - control register */
typedef struct{
__REG32 CBSR  : 2;
__REG32 PLE   : 1;
__REG32 IE    : 1;
__REG32 CLE   : 1;
__REG32 BLE   : 1;
__REG32 HCFS  : 2;
__REG32 IR    : 1;
__REG32 RWC   : 1;
__REG32 RWE   : 1;
__REG32       :21;
} __hccontrol_bits;

/* USB Host - command status register */
typedef struct{
__REG32 HCR  : 1;
__REG32 CLF  : 1;
__REG32 BLF  : 1;
__REG32 OCR  : 1;
__REG32      :12;
__REG32 SOC  : 1;
__REG32      :15;
} __hccommandstatus_bits;

/* USB Host - interrupt status register */
typedef struct{
__REG32 SO    : 1;
__REG32 WDH   : 1;
__REG32 SF    : 1;
__REG32 RD    : 1;
__REG32 UE    : 1;
__REG32 FNO   : 1;
__REG32 RHSC  : 1;
__REG32       :23;
__REG32 OC    : 1;
__REG32       : 1;
} __hcinterruptstatus_bits;

/* USB Host - interrupt enable register */
typedef struct{
__REG32 SO    : 1;
__REG32 WDH   : 1;
__REG32 SF    : 1;
__REG32 RD    : 1;
__REG32 UE    : 1;
__REG32 FNO   : 1;
__REG32 RHSC  : 1;
__REG32       :23;
__REG32 OC    : 1;
__REG32 MIE   : 1;
} __hcinterruptenable_bits;

/* USB Host -  HcHCCA register */
typedef struct{
__REG32     : 8;
__REG32 AD  :24;
} __hchcca_bits;

/* USB Host - register */
typedef struct{
__REG32     : 4;
__REG32 AD  :28;
} __currented_bits;

/* USB Host - HcFmInterval register */
typedef struct{
__REG32 FI     :14;
__REG32        : 2;
__REG32 FSMPS  :15;
__REG32 FIT    : 1;
} __hcfminterval_bits;

/* USB Host - HcFmRemaining register */
typedef struct{
__REG32 FR   :14;
__REG32      :17;
__REG32 FRT  : 1;
} __hcfmremaining_bits;

/* USB Host - HcFmNumber register */
typedef struct{
__REG32 FN  :16;
__REG32     :16;
} __hcfmnumber_bits;

/* USB Host - HcPeriodicStart register */
typedef struct{
__REG32 PS  :14;
__REG32     :18;
} __hcperiodicstart_bits;

/* USB Host - HcLsThreshold register */
typedef struct{
__REG32 LST  :12;
__REG32      :20;
} __hclsthreshold_bits;

/* USB Host - HcRhDescriptorA register */
typedef struct{
__REG32 NDP   : 8;
__REG32 PSM   : 1;
__REG32 NPS   : 1;
__REG32 DT    : 1;
__REG32 OCPM  : 1;
__REG32 NOCP  : 1;
__REG32       :11;
__REG32 P     : 8;
} __hcrhdescriptora_bits;

/* USB Host - HcRhDescriptorB register */
typedef struct{
__REG32 DR    : 4;
__REG32       :12;
__REG32 PPCM  : 4;
__REG32       :12;
} __hcrhdescriptorb_bits;

/* USB Host - HcRhStatus register */
typedef struct{
__REG32 LPS   : 1;
__REG32 OCI   : 1;
__REG32       :13;
__REG32 DRWE  : 1;
__REG32 LPSC  : 1;
__REG32 CCIC  : 1;
__REG32       :13;
__REG32 CRWE  : 1;
} __hcrhstatus_bits;

/* USB Host - HcRhPortStatus register */
typedef struct{
__REG32 CCS   : 1;
__REG32 PES   : 1;
__REG32 PSS   : 1;
__REG32 POCI  : 1;
__REG32 PRS   : 1;
__REG32       : 3;
__REG32 PPS   : 1;
__REG32 LSDA  : 1;
__REG32       : 6;
__REG32 CSC   : 1;
__REG32 PESC  : 1;
__REG32 PSSC  : 1;
__REG32 OCIC  : 1;
__REG32 PRSC  : 1;
__REG32       :11;
} __hcrhportstatus_bits;

/* Interrupt Controller - Source Pending Register     */
/*                      - Interrupt Mode Register     */
/*                      - Interrupt Mask Register     */
/*                      - Interrupt Pending Register  */
typedef struct {
  __REG32 EINT0         : 1;
  __REG32 EINT1         : 1;
  __REG32 EINT2         : 1;
  __REG32 EINT3         : 1;
  __REG32 EINT4_7       : 1;
  __REG32 EINT8_23      : 1;
  __REG32 INT_CAM       : 1;
  __REG32 nBATT_FLT     : 1;
  __REG32 INT_TICK      : 1;
  __REG32 INT_WDT_AC97  : 1;
  __REG32 INT_TIMER0    : 1;
  __REG32 INT_TIMER1    : 1;
  __REG32 INT_TIMER2    : 1;
  __REG32 INT_TIMER3    : 1;
  __REG32 INT_TIMER4    : 1;
  __REG32 INT_UART2     : 1;
  __REG32 INT_LCD       : 1;
  __REG32 INT_DMA0      : 1;
  __REG32 INT_DMA1      : 1;
  __REG32 INT_DMA2      : 1;
  __REG32 INT_DMA3      : 1;
  __REG32 INT_SDI       : 1;
  __REG32 INT_SPIO      : 1;
  __REG32 INT_UART1     : 1;
  __REG32 INT_NFCON     : 1;
  __REG32 INT_USBD      : 1;
  __REG32 INT_USBH      : 1;
  __REG32 INT_IIC       : 1;
  __REG32 INT_UART0     : 1;
  __REG32 INT_SPI1      : 1;
  __REG32 INT_RTC       : 1;
  __REG32 INT_ADC       : 1;
} __srcpnd_bits;

/* Interrupt Controller - Priority Register */
typedef struct {
  __REG32 ARB_MODE0 : 1;
  __REG32 ARB_MODE1 : 1;
  __REG32 ARB_MODE2 : 1;
  __REG32 ARB_MODE3 : 1;
  __REG32 ARB_MODE4 : 1;
  __REG32 ARB_MODE5 : 1;
  __REG32 ARB_MODE6 : 1;
  __REG32 ARB_SEL0  : 2;
  __REG32 ARB_SEL1  : 2;
  __REG32 ARB_SEL2  : 2;
  __REG32 ARB_SEL3  : 2;
  __REG32 ARB_SEL4  : 2;
  __REG32 ARB_SEL5  : 2;
  __REG32 ARB_SEL6  : 2;
  __REG32           :11;
} __priority_bits;

/* Interrupt Controller - Sub Source pending register */
/*                      - Sub Mask Register           */
typedef struct {
  __REG32 INT_RXD0  : 1;
  __REG32 INT_TXD0  : 1;
  __REG32 INT_ERR0  : 1;
  __REG32 INT_RXD1  : 1;
  __REG32 INT_TXD1  : 1;
  __REG32 INT_ERR1  : 1;
  __REG32 INT_RXD2  : 1;
  __REG32 INT_TXD2  : 1;
  __REG32 INT_ERR2  : 1;
  __REG32 INT_TC    : 1;
  __REG32 INT_ADC_S : 1;
  __REG32 INT_CAM_C : 1;
  __REG32 INT_CAM_P : 1;
  __REG32 INT_WDT   : 1;
  __REG32 INT_AC97  : 1;
  __REG32           :17;
} __subsrcpnd_bits;

/* DMA - Initial Source Register */
typedef struct {
  __REG32 S_ADDR  :31;
  __REG32         : 1;
} __disrcn_bits;

/* DMA - Initial Source Control Register */
typedef struct {
  __REG32 INC : 1;
  __REG32 LOC : 1;
  __REG32     :30;
} __disrccn_bits;

/* DMA - Initial Destination Register */
typedef struct {
  __REG32 D_ADDR  : 31;
  __REG32         : 1;
} __didstn_bits;

/* DMA - Initial Destination Control Register */
typedef struct {
  __REG32 INC     : 1;
  __REG32 LOC     : 1;
  __REG32 CHK_INT : 1;
  __REG32         :29;
} __didstcn_bits;

/* DMA Control Register */
typedef struct {
  __REG32 TC        :20;
  __REG32 DSZ       : 2;
  __REG32 RELOAD    : 1;
  __REG32 SWHW_SEL  : 1;
  __REG32 HWSRCSEL  : 3;
  __REG32 SERVMODE  : 1;
  __REG32 TSZ       : 1;
  __REG32 INT       : 1;
  __REG32 SYNC      : 1;
  __REG32 DMD_HS    : 1;
} __dconn_bits;

/* DMA - Status Register */
typedef struct {
  __REG32 CURR_TC :20;
  __REG32 STAT    : 2;
  __REG32         :10;
} __dstatn_bits;

/* DMA - Current Source Register */
typedef struct {
  __REG32 CURR_SRC  :31;
  __REG32           : 1;
} __dcsrcn_bits;

/* DMA - Current Destination Register */
typedef struct {
  __REG32 CURR_DST  :31;
  __REG32           : 1;
} __dcdstn_bits;

/* DMA - Mask Trigger Register */
typedef struct {
  __REG32 SW_TRIG : 1;
  __REG32 ON_OFF  : 1;
  __REG32 STOP    : 1;
  __REG32         : 29;
} __dmasktrign_bits;

/* Clock Generator & Power Management - Lock Time Count Register */
typedef struct {
  __REG32 M_LTIME :16;
  __REG32 U_LTIME :16;
} __locktime_bits;

/* Clock Generator & Power Management - PLL Control Register */
typedef struct {
  __REG32 SDIV  : 2;
  __REG32       : 2;
  __REG32 PDIV  : 6;
  __REG32       : 2;
  __REG32 MDIV  : 8;
  __REG32       :12;
} __pllcon_bits;

/* Clock Generator & Power Management - Clock Control Register */
typedef struct {
  __REG32             : 1;
  __REG32             : 1;
  __REG32 IDLE        : 1;
  __REG32 SLEEP       : 1;
  __REG32 NAND        : 1;
  __REG32 LCDC        : 1;
  __REG32 USB_host    : 1;
  __REG32 USB_device  : 1;
  __REG32 PWMTIMER    : 1;
  __REG32 SDI         : 1;
  __REG32 UART0       : 1;
  __REG32 UART1       : 1;
  __REG32 UART2       : 1;
  __REG32 GPIO        : 1;
  __REG32 RTC         : 1;
  __REG32 ADC         : 1;
  __REG32 IIC         : 1;
  __REG32 IIS         : 1;
  __REG32 SPI         : 1;
  __REG32 CAMERA      : 1;
  __REG32 AC97        : 1;
  __REG32             :11;
} __clkcon_bits;

/* Clock Generator & Power Management - Clock Slow Control Register */
typedef struct {
  __REG32 SLOW_VAL  : 3;
  __REG32           : 1;
  __REG32 SLOW_BIT  : 1;
  __REG32 MPLL_OFF  : 1;
  __REG32           : 1;
  __REG32 UCLK_ON   : 1;
  __REG32           :24;
} __clkslow_bits;

/* Clock Generator & Power Management - Clock Divider Control Register */
typedef struct {
  __REG32 PDIVN     : 1;
  __REG32 HDIVN     : 1;
  __REG32 DIVN_UPLL : 1;
  __REG32           :29;
} __clkdivn_bits;

/* Clock Generator & Power Management - Camera Clock Divider Register */
typedef struct {
  __REG32 CAMCLK_DIV  : 4;
  __REG32 CAMCLK_SEL  : 1;
  __REG32             : 3;
  __REG32 HCLK3_HALF  : 1;
  __REG32 HCLK4_HALF  : 1;
  __REG32             : 1;
  __REG32             : 1;
  __REG32 DVS_EN      : 1;
  __REG32             :19;
} __camdivn_bits;

/* LCD Controller - Control 1 Register */
typedef struct {
  __REG32 ENDIV   : 1;
  __REG32 BPPMODE : 4;
  __REG32 PNRMODE : 2;
  __REG32 MMODE   : 1;
  __REG32 CLKVAL  :10;
  __REG32 LINECNT :10; /* Read only */
  __REG32         : 4;
} __lcdcon1_bits;

/* LCD Controller - Control 2 Register */
typedef struct {
  __REG32 VSPW    : 6;
  __REG32 VFPD    : 8;
  __REG32 LINEVAL :10;
  __REG32 VBPD    : 8;
} __lcdcon2_bits;

/* LCD Controller - Control 3 Register */
typedef union {
  //LCDCON3
  struct {                  /* STN */
    __REG32 LINEBLANK : 8;
    __REG32 HOZVAL    :11;
    __REG32 WDLY      : 7;
    __REG32           : 6;
  };
  //LCDCON3
  struct {                  /* TFT */
    __REG32 HFPD  : 8;
    __REG32       :11;
    __REG32 HBPD  : 7;
    __REG32       : 6;
  };
} __lcdcon3_bits;

/* LCD Controller - Control 4 Register */
typedef union {
  //LCDCON4
  struct {                  /* STN */
  __REG32 WLH   : 8;
  __REG32 MVAL  : 8;
  __REG32       :16;
  };
  //LCDCON4
  struct {                  /* TFT */
    __REG32 HSPW  : 8;
    __REG32       : 8;
    __REG32       :16;
  };
} __lcdcon4_bits;

/* LCD Controller - Control 5 Register */
typedef struct {
  __REG32 HWSWP     : 1;
  __REG32 BSWP      : 1;
  __REG32 ENLEND    : 1;
  __REG32 PWREN     : 1;
  __REG32 INVLEND   : 1;
  __REG32 INVPWREN  : 1;
  __REG32 INVVDEN   : 1;
  __REG32 INVVD     : 1;
  __REG32 INVVFRAME : 1;
  __REG32 INVVLINE  : 1;
  __REG32 INVVCLK   : 1;
  __REG32 FRM565    : 1;
  __REG32 BPP24BL   : 1;
  __REG32 HSTATUS   : 2;
  __REG32 VSTATUS   : 2;
  __REG32           :15;
} __lcdcon5_bits;

/* LCD Controller - FRAME Buffer Start Address 1 Register */
typedef struct {
  __REG32 LCDBASEU  :21;
  __REG32 LCDBANK   : 9;
  __REG32           : 2;
} __lcdsaddr1_bits;

/* LCD Controller - FRAME Buffer Start Address 2 Register */
typedef struct {
  __REG32 LCDBASEL  :21;
  __REG32           :11;
} __lcdsaddr2_bits;

/* LCD Controller - FRAME Buffer Start Address 3 Register */
typedef struct {
  __REG32 PAGEWIDTH :11;
  __REG32 OFFSIZE   :11;
  __REG32           :10;
} __lcdsaddr3_bits;

/* LCD Controller - RED Lookup Table Register */
typedef struct {
  __REG32 REDVAL_0  : 4;
  __REG32 REDVAL_1  : 4;
  __REG32 REDVAL_2  : 4;
  __REG32 REDVAL_3  : 4;
  __REG32 REDVAL_4  : 4;
  __REG32 REDVAL_5  : 4;
  __REG32 REDVAL_6  : 4;
  __REG32 REDVAL_7  : 4;
} __redlut_bits;

/* LCD Controller - GREEN Lookup Table Register */
typedef struct {
  __REG32 GREENVAL_0  : 4;
  __REG32 GREENVAL_1  : 4;
  __REG32 GREENVAL_2  : 4;
  __REG32 GREENVAL_3  : 4;
  __REG32 GREENVAL_4  : 4;
  __REG32 GREENVAL_5  : 4;
  __REG32 GREENVAL_6  : 4;
  __REG32 GREENVAL_7  : 4;
} __greenlut_bits;

/* LCD Controller - BLUE Lookup Table Register */
typedef struct {
  __REG32 BLUEVAL_0 : 4;
  __REG32 BLUEVAL_1 : 4;
  __REG32 BLUEVAL_2 : 4;
  __REG32 BLUEVAL_3 : 4;
  __REG32           :16;
} __bluelut_bits;

/* LCD Controller - Dithering Mode Register */
typedef struct {
  __REG32 DITHMODE  :19; /* 0x00000 or 0x12210 */
  __REG32           :13;
} __dithmode_bits;

/* LCD Controller - Temp Palette Register */
typedef struct {
  __REG32 TPALVAL_BLUE  : 8;
  __REG32 TPALVAL_GREEN : 8;
  __REG32 TPALVAL_RED   : 8;
  __REG32 TPALEN        : 1;
  __REG32               : 7;
} __tpal_bits;

/* LCD Controller - Interrupt Pending Register */
/*                - Source Pending Register */
typedef struct {
  __REG32 INT_FiCnt : 1;
  __REG32 INT_FrSyn : 1;
  __REG32           :30;
} __lcdintpnd_bits;

/* LCD Controller - Interrupt Mask Register */
typedef struct {
  __REG32 INT_FiCnt : 1;
  __REG32 INT_FrSyn : 1;
  __REG32 FIWSEL    : 1;
  __REG32           :29;
} __lcdintmsk_bits;

/* LCD Controller - TCON Control Register */
typedef struct {
  __REG32 LPC_EN  : 1;
  __REG32 RES_SEL : 1;
  __REG32 MODE_SEL  : 1;
  __REG32 CPV_SEL   : 1;
  __REG32 LCC_EN    : 1;
  __REG32 LCC_SEL1  : 1;
  __REG32 LCC_SEL2  : 1;
  __REG32 LCC_SEL3  : 1;
  __REG32 LCC_SEL4  : 1;
  __REG32 LCC_SEL5  : 1;
  __REG32 LCC_TEST1 : 1;
  __REG32 LCC_TEST2 : 1;
  __REG32           :20;
} __tconsel_bits;

/* NAND FLASH CONTROLLER - Nand Flash Configuration Register  */
typedef struct {
  __REG32 BusWidth  : 1;
  __REG32 AddrCycle : 1; /*Read only*/
  __REG32 PageSize  : 1; /*Read only*/
  __REG32 AdvFlash  : 1; /*Read only*/
  __REG32 TWRPH1    : 3;
  __REG32           : 1;
  __REG32 TWRPH0    : 3;
  __REG32           : 1;
  __REG32 TACLS     : 2;
  __REG32           : 2;
  __REG32           :16;
} __nfconf_bits;

/* NAND FLASH CONTROLLER - Nand Flash Control Register  */
typedef struct {
  __REG32 MODE              : 1;
  __REG32 Reg_nCE           : 1;
  __REG32                   : 2;
  __REG32 InitECC           : 1;
  __REG32 MainECCLock       : 1;
  __REG32 SpareECCLock      : 1;
  __REG32                   : 1;
  __REG32 RnB_TransMode     : 1;
  __REG32 EnbRnBINT         : 1;
  __REG32 EnbIllegalAccINT  : 1;
  __REG32                   : 1;
  __REG32 SoftLock          : 1;
  __REG32 Lock_tight        : 1;
  __REG32                   : 2;
  __REG32                   :16;
} __nfcont_bits;

/* NAND Flash Controller -  Command Register */
typedef struct {
  __REG32 NFCMMD  : 8;
  __REG32         : 8; /*Reserved */
  __REG32         :16;
} __nfcmd_bits;

/* NAND Flash Controller - Address Set Register */
typedef struct {
  __REG32 NFADDR  : 8;
  __REG32         : 8; /* Reserved */
  __REG32         :16;
} __nfaddr_bits;

/* NAND Flash Controller - Main Data Area Register (NFMECCD0) */
/*                       - Spare Area ECC Register */
typedef struct {
  __REG32 ECC_DATA0_0 : 8;
  __REG32 ECC_DATA0_1 : 8;
  __REG32 ECC_DATA1_0 : 8;
  __REG32 ECC_DATA1_1 : 8;
} __nfmeccd0_bits;

/* NAND Flash Controller - Main Data Area Register (NFMECCD1) */
typedef struct {
  __REG32 ECC_DATA2_0 : 8;
  __REG32 ECC_DATA2_1 : 8;
  __REG32 ECC_DATA3_0 : 8;
  __REG32 ECC_DATA3_1 : 8;
} __nfmeccd1_bits;

/* NAND Flash Controller - NFCON Status Register */
typedef struct {
  __REG32 RnB             : 1; /* Read only */
  __REG32 nCE             : 1; /* Read only */
  __REG32 RnB_TransDetect : 1;
  __REG32 IllegalAccess   : 1;
  __REG32                 : 3;
  __REG32                 : 1;
  __REG32                 :24;
} __nfstat_bits;

/* NAND Flash Controller - ECC0/1 Status Register */
typedef struct {
  __REG32 MainError     : 2;
  __REG32 SpareError    : 2;
  __REG32 MErrorBitNo   : 3;
  __REG32 MErrorDataNo  :11;
  __REG32 SErrorBitNo   : 3;
  __REG32 SErrorDataNo  : 4;
  __REG32               : 7;
} __nfestatn_bits;

/* NAND Flash Controller - Main Data Area ECC0 Status Register */
typedef struct {
  __REG32 MECC0_0 : 8;
  __REG32 MECC0_1 : 8;
  __REG32 MECC0_2 : 8;
  __REG32 MECC0_3 : 8;
} __nfmecc0_bits;

/* NAND Flash Controller - Main Data Area ECC1 Status Register */
typedef struct {
  __REG32 MECC1_0 : 8;
  __REG32 MECC1_1 : 8;
  __REG32 MECC1_2 : 8;
  __REG32 MECC1_3 : 8;
} __nfmecc1_bits;

/* NAND Flash Controller - Spare Area ECC Status Register */
typedef struct {
  __REG32 SECC0_0 : 8;
  __REG32 SECC0_1 : 8;
  __REG32 SECC1_0 : 8;
  __REG32 SECC1_1 : 8;
} __nfsecc_bits;

/* NAND Flash Controller - Block Address Register (NFSBLK) */
typedef struct {
  __REG32 SBLK_ADDR0 : 8;
  __REG32 SBLK_ADDR1 : 8;
  __REG32 SBLK_ADDR2 : 8;
  __REG32            : 8;
} __nfsblk_bits;

/* NAND Flash Controller - Block Address Register (NFEBLK)*/
typedef struct {
  __REG32 EBLK_ADDR0 : 8;
  __REG32 EBLK_ADDR1 : 8;
  __REG32 EBLK_ADDR2 : 8;
  __REG32            : 8;
} __nfeblk_bits;

/* Camera Interface - Source Format Register */
typedef struct {
  __REG32 SourceVsize :13;
  __REG32             : 1;
  __REG32 Ordef422    : 2;
  __REG32 SourceHsize :13;
  __REG32             : 1;
  __REG32 UVOffset    : 1;
  __REG32 ITU601_656n : 1;
} __cisrcfmt_bits;

/* Camera Interface - Window Option Register */
typedef struct {
  __REG32 WinVerOfst  :11;
  __REG32             : 1;
  __REG32 ClrOvPrFiCr : 1;
  __REG32 ClrOvPrFiCb : 1;
  __REG32 ClrOvCoFiCr : 1;
  __REG32 ClrOvCoFiCb : 1;
  __REG32 WinHorOfst  :11;
  __REG32             : 3;
  __REG32 ClrOvCoFiY  : 1;
  __REG32 WinOfsEn    : 1;
} __ciwdofst_bits;

/* Camera Interface - Global Control Register */
typedef struct {
  __REG32                 :24;
  __REG32 InvPolCAMHREF   : 1;
  __REG32 InvPolCAMVSYNC  : 1;
  __REG32 InvPolCAMPCLK   : 1;
  __REG32 TestPattern     : 2;
  __REG32                 : 1;
  __REG32 CamRst          : 1;
  __REG32 SwRst           : 1;
} __cigctrl_bits;

/* Camera Interface - Codec Target Format Register */
typedef struct {
  __REG32 TargetVsize_Co  :13;
  __REG32                 : 1;
  __REG32 FlipMd_Co       : 2;
  __REG32 TargetHsize_Co  :13;
  __REG32                 : 1;
  __REG32 Out422_Co       : 1;
  __REG32 In422_Co        : 1;
} __cicotrgfmt_bits;

/* Camera Interface - Codec DMA Control Register */
typedef struct {
  __REG32               : 2;
  __REG32 LastIRQEn_Co  : 1;
  __REG32               : 1;
  __REG32 Cburst2_Co    : 5;
  __REG32 Cburst1_Co    : 5;
  __REG32 Yburst2_Co    : 5;
  __REG32 Yburst1_Co    : 5;
  __REG32               : 8;
} __cicoctrl_bits;

/* Camera Interface - Codec Pre-scaler Control Register 1 */
typedef struct {
  __REG32 PreVerRatio_Co  : 7;
  __REG32                 : 9;
  __REG32 PreHorRatio_Co  : 7;
  __REG32                 : 5;
  __REG32 SHfactor_Co     : 4;
} __cicoscpreratio_bits;

/* Camera Interface - Codec Pre-scaler Control Register 2 */
typedef struct {
  __REG32 PreDstHeight_Co :12;
  __REG32                 : 4;
  __REG32 PreDstWidth_Co  :12;
  __REG32                 : 4;
} __cicoscpredst_bits;

/* Camera Interface - Codec Main-Scaler Control Register */
typedef struct {
  __REG32 MainVerRatio_Co : 9;
  __REG32                 : 6;
  __REG32 CoScalerStart   : 1;
  __REG32 MainHorRatio_Co : 9;
  __REG32                 : 4;
  __REG32 ScaleUpDown_Co  : 2;
  __REG32 ScalerBypass_Co : 1;
} __cicoscctrl_bits;

/* Camera Interface - Codec DMA Target Area Register */
typedef struct {
  __REG32 CICOTAREA :26;
  __REG32           : 6;
} __cicotarea_bits;

/* Camera Interface - Codec Status Register */
typedef struct {
  __REG32                 :21;
  __REG32 ImgCptEn_CoSC   : 1;
  __REG32 ImgCptEn_CamIf  : 1;
  __REG32 FlipMd_Co       : 2;
  __REG32 WinOfstEn_Co    : 1;
  __REG32 FrameCnt_Co     : 2;
  __REG32 VSYNC           : 1;
  __REG32 OvFiCr_Co       : 1;
  __REG32 OcFiCb_Co       : 1;
  __REG32 OvFiY_Co        : 1;
} __cicostatus_bits;

/* Camera Interface - Preview Target Format Register */
typedef struct {
  __REG32 TargetVsize_Pr  :13;
  __REG32                 : 1;
  __REG32 FlipMd_Pr       : 2;
  __REG32 TargetHsize_Pr  :13;
  __REG32                 : 3;
} __ciprtrgfmt_bits;

/* Camera Interface - Preview DMA Control Register */
typedef struct {
  __REG32               : 2;
  __REG32 LastIRQEn_Pr  : 1;
  __REG32               :11;
  __REG32 RGBburst2_Pr  : 5;
  __REG32 RGBburst1_Pr  : 5;
  __REG32               : 8;
} __ciprctrl_bits;

/* Camera Interface - Preview Pre-scaler Control Register 1 */
typedef struct {
  __REG32 PreVerRatio_Pr  : 7;
  __REG32                 : 9;
  __REG32 PreHorRatio_Pr  : 7;
  __REG32                 : 5;
  __REG32 SHfactor_Pr     : 4;
} __ciprscpreratio_bits;

/* Camera Interface - Preview Pre-scaler Control Register 2 */
typedef struct {
  __REG32 PreDstHeight_Pr :12;
  __REG32                 : 4;
  __REG32 PreDstWidth_Pr  :12;
  __REG32                 : 4;
} __ciprscpredst_bits;

/* Camera Interface - Preview Main-scaler Control Register */
typedef struct {
  __REG32 MainVerRatio_Pr : 9;
  __REG32                 : 6;
  __REG32 PrScalerStart   : 1;
  __REG32 MainHorRatil_Pr : 9;
  __REG32                 : 3;
  __REG32 ScaleUpDown_Pr  : 2;
  __REG32 RGBformat_Pr    : 1;
  __REG32 Sample_Pr       : 1;
} __ciprscctrl_bits;

/* Camera Interface - Preview DMA Target Area Register */
typedef struct {
  __REG32 CIPRTAREA :26;
  __REG32           : 6;
} __ciprtarea_bits;

/* Camera Interface - Preview Status Register */
typedef struct {
  __REG32               :21;
  __REG32 ImgCptEn_PrSC : 1;
  __REG32               : 1;
  __REG32 FlipMd_Pr     : 2;
  __REG32               : 1;
  __REG32 FrameCnt_Pr   : 2;
  __REG32               : 2;
  __REG32 OvFiCr_Pr     : 1;
  __REG32 OvFiCb_Pr     : 1;
} __ciprstatus_bits;

/* Camera Interface - Image Capture Enable Register */
typedef struct {
  __REG32               :29;
  __REG32 ImgCptEn_PrSc : 1;
  __REG32 ImgCptEn_CoSc : 1;
  __REG32 ImgCptEn      : 1;
} __ciimgcpt_bits;

/* UART - Line Control Register */
typedef struct {
  __REG32 wlenght   : 2;
  __REG32 stop      : 1;
  __REG32 parity    : 3;
  __REG32 infra     : 1;
  __REG32           : 1;
  __REG32           :24;
} __ulconn_bits;

/* UART - Control Register */
typedef struct {
  __REG32 receive   : 2;
  __REG32 transmit  : 2;
  __REG32 breaksig  : 1;
  __REG32 loop      : 1;
  __REG32 rxerror   : 1;
  __REG32 rxtime    : 1;
  __REG32 rxint     : 1;
  __REG32 txint     : 1;
  __REG32 clock     : 2;
  __REG32 FCLK      : 4;
  __REG32           :16;
} __uconn_bits;

/* UART - FIFO Control Register */
typedef struct {
  __REG32 enable    : 1;
  __REG32 rreset    : 1;
  __REG32 treset    : 1;
  __REG32           : 1;
  __REG32 rtrigger  : 2;
  __REG32 ttrigger  : 2;
  __REG32           :24;
} __ufconn_bits;

/* UART - Modem Control Register */
typedef struct {
  __REG32 send  : 1;
  __REG32       : 3; /* Must be 0 */
  __REG32 afc   : 1;
  __REG32       : 3; /* Must be 0 */
  __REG32       :24;
} __umconn_bits;

/* UART - TX/RX Status Register */
typedef struct {
  __REG32 rbuffer : 1;
  __REG32 tbuffer : 1;
  __REG32 shifter : 1;
  __REG32         :29;
} __utrstatn_bits;

/* UART - Error Status Register */
typedef struct {
  __REG32 overrun       : 1;
  __REG32 parity        : 1;
  __REG32 frame         : 1;
  __REG32 break_detect  : 1;
  __REG32               :28;
} __uerstatn_bits;

/* UART - FIFO Status Register */
typedef struct {
  __REG32 rcount  : 6;
  __REG32 rfull   : 1;
  __REG32         : 1;
  __REG32 tcount  : 6;
  __REG32 tfull   : 1;
  __REG32         : 1;
  __REG32         :16;
} __ufstatn_bits;

/* UART - Modem Status Register */
typedef struct {
  __REG32 clear : 1;
  __REG32       : 3;
  __REG32 cts   : 1;
  __REG32       :27;
} __umstatn_bits;

/* UART - Baud Rate Divisor Register */
typedef struct {
  __REG32 UBRDIV  : 16;
  __REG32         : 16;
} __ubrdivn_bits;

/* PWM Timer - Configuration Register 0 */
typedef struct {
  __REG32 pre0    : 8;
  __REG32 pre1    : 8;
  __REG32 length  : 8;
  __REG32         : 8;
} __tcfg0_bits;

/* PWM Timer - Configuration Register 1 */
typedef struct {
  __REG32 mux0  : 4;
  __REG32 mux1  : 4;
  __REG32 mux2  : 4;
  __REG32 mux3  : 4;
  __REG32 mux4  : 4;
  __REG32 dma   : 4;
  __REG32       : 8;
} __tcfg1_bits;

/* PWM Timer - Control Register */
typedef struct {
  __REG32 t0_start    : 1;
  __REG32 t0_update   : 1;
  __REG32 t0_inverter : 1;
  __REG32 t0_reload   : 1;
  __REG32 dead_zone   : 1;
  __REG32             : 3;
  __REG32 t1_start    : 1;
  __REG32 t1_update   : 1;
  __REG32 t1_inverter : 1;
  __REG32 t1_reload   : 1;
  __REG32 t2_start    : 1;
  __REG32 t2_update   : 1;
  __REG32 t2_inverter : 1;
  __REG32 t2_reload   : 1;
  __REG32 t3_start    : 1;
  __REG32 t3_update   : 1;
  __REG32 t3_inverter : 1;
  __REG32 t3_reload   : 1;
  __REG32 t4_start    : 1;
  __REG32 t4_update   : 1;
  __REG32 t4_reload   : 1;
  __REG32             : 9;
} __tcon_bits;

/* PWM Timer - Timer x Count Buffer Register */
typedef struct {
  __REG32 count :16;
  __REG32       :16;
} __tcntbx_bits;

/* PWM Timer - Timer x Compare Buffer Register */
typedef struct {
  __REG32 compare  :16;
  __REG32          :16;
} __tcmpbx_bits;

/* PWM Timer - Timer x Count Observation Register */
typedef struct {
  __REG32 observ    :16;
  __REG32           :16;
} __tcntox_bits;

/* USB Device Controller - Function Address Register */
typedef struct {
  __REG8 FUNCTION_ADDR : 7;
  __REG8 ADDR_UPDATE   : 1;
} __funcaddrreg_bits;

/* USB Device Controller - Power Management Register */
typedef struct {
  __REG8 SUSPEND_EN    : 1;
  __REG8 SUSPEND_MODE  : 1;
  __REG8 MCU_RESUME    : 1;
  __REG8 USB_RESET     : 1;
  __REG8               : 4;
} __pwraddr_bits;

/* USB Device Controller - EP Interrupt Register */
typedef struct {
  __REG8 EP0_Interrupt : 1;
  __REG8 EP1_Interrupt : 1;
  __REG8 EP2_Interrupt : 1;
  __REG8 EP3_Interrupt : 1;
  __REG8 EP4_Interrupt : 1;
  __REG8               : 3;
} __epintreg_bits;

/* USB Device Controller - USB Interrupt register */
typedef struct {
  __REG8 SUSPEND : 1;
  __REG8 RESUME  : 1;
  __REG8 RESET   : 1;
  __REG8         : 5;
} __usbintreg_bits;

/* USB Device Controller - EP Interrupt Enable Register */
typedef struct {
  __REG8 EP0_INT_EN  : 1;
  __REG8 EP1_INT_EN  : 1;
  __REG8 EP2_INT_EN  : 1;
  __REG8 EP3_INT_EN  : 1;
  __REG8 EP4_INT_EN  : 1;
  __REG8             : 3;
} __epintenreg_bits;

/* USB Device Controller - USB Interrupt Enable Register */
typedef struct {
  __REG8  SUSPEND_INT_EN  : 1;
  __REG8                  : 1;
  __REG8  RESET_INT_EN    : 1;
  __REG8                  : 5;
} __usbintenreg_bits;

/* USB Device Controller - Frame Number1 Register */
typedef struct {
  __REG8 FRAME_NUM1  : 8;
} __framenum1reg_bits;

/* USB Device Controller - Frame Number2 Register */
typedef struct {
  __REG8 FRAME_NUM2  : 8;
} __framenum2reg_bits;

/* USB Device Controller - Index Register */
typedef struct {
  __REG8 INDEX : 8;
} __indexreg_bits;

/* USB Device Controller - Max Packet Register */
typedef struct {
  __REG8 MAXP  : 4;
  __REG8       : 4;
} __maxpreg_bits;

/* USB Device Controller - End Point IN Control Status Register 1*/
/*                       - End Point0 Control Status Register (EP0_CSR) */
typedef union {
  //IN_CSR1_REG
  struct {
  __REG8 IN_PKT_RDY_IN_CSR1 : 1;
  __REG8                    : 2;
  __REG8 FIFO_FLUSH         : 1;
  __REG8 SEND_STALL_IN_CSR1 : 1;
  __REG8 SENT_STALL_IN_CSR1 : 1;
  __REG8 CLR_DATA_TOGGLE    : 1;
  __REG8                    : 1;
  };
  //EP0_CSR
  struct {
    __REG8 OUT_PKT_RDY           : 1;
    __REG8 IN_PKT_RDY_EP0_CSR    : 1;
    __REG8 SENT_STALL_EP0_CSR    : 1;
    __REG8 DATA_END              : 1;
    __REG8 SETUP_END             : 1;
    __REG8 SEND_STALL_EP0_CSR    : 1;
    __REG8 SERVICED_OUT_PKT_RDY  : 1;
    __REG8 SERVICED_SETUP_END    : 1;
  };
} __incsr1reg_bits;

/* USB Device Controller - End Point IN Control Status Register 2 */
typedef struct {
  __REG8                 : 4;
  __REG8 IN_DMA_INT_EN   : 1;
  __REG8 MODE_IN         : 1;
  __REG8 ISO             : 1;
  __REG8 AUTO_SET        : 1;
} __incsr2reg_bits;

/* USB Device Controller - End Point Out Control Status Register 1 */
typedef struct {
  __REG8 OUT_PKT_RDY     : 1;
  __REG8                 : 3;
  __REG8 FIFO_FLUSH      : 1;
  __REG8 SEND_STALL      : 1;
  __REG8 SENT_STALL      : 1;
  __REG8 CLR_DATA_TOGGLE : 1;
} __outcsr1reg_bits;

/* USB Device Controller - End Point Out Control Status Register 2 */
typedef struct {
  __REG8                    : 5;
  __REG8 OUT_DMA_INT_MASK   : 1;
  __REG8 ISO                : 1;
  __REG8 AUTO_CLR           : 1;
} __outcsr2reg_bits;

/* USB Device Controller - End Point Out Write Count Register 1 */
typedef struct {
  __REG8 OUT_CNT_LOW : 8;
} __outfifocnt1reg_bits;

/* USB Device Controller - End Point Out Write Count Register 2 */
typedef struct {
  __REG8 OUT_CNT_HIGH  : 8;
} __outfifocnt2reg_bits;

/* USB Device Controller - End Point FIFO Register */
typedef struct {
  __REG8 FIFO_DATA : 8;
} __epnfifo_bits;

/* USB Device Controller - DMA Interface Control Register */
typedef union {
  //EPx_DMA_CON
  struct {
    __REG8 DMA_MODE_EN : 1;
    __REG8 IN_DMA_RUN  : 1;
    __REG8 OUT_RUN_OB  : 1;
    __REG8 DEMAND_MODE : 1;
    __REG8 STATE       : 3;
    __REG8 IN_RUN_OB   : 1;
  };
  //EPx_DMA_CON
  struct {
    __REG8              : 2;
    __REG8 OUT_DMA_RUN  : 1;
    __REG8              : 5;
  };
} __epndmacon_bits;

/* USB Device Controller - DMA Unit Counter Register */
typedef struct {
  __REG8 EPn_UNIT_CNT  : 8;
} __epndmaunit_bits;

/* USB Device Controller - DMA FIFO Counter Register */
typedef struct {
  __REG8 EPn_FIFO_CNT  : 8;
} __epndmafifo_bits;

/* USB Device Controller - DMA total transfer counter register high) */
typedef struct {
  __REG8 EPn_TTC_H : 8;
} __epndmatxh_bits;

/* USB Device Controller - DMA total transfer counter register middle) */
typedef struct {
  __REG8 EPn_TTC_M : 8;
} __epndmatxm_bits;

/* USB Device Controller - DMA total transfer counter register low) */
typedef struct {
  __REG8 EPn_TTC_L : 8;
} __epndmatxl_bits;

/* Watchdog Timer - Control Register */
typedef struct {
  __REG32 reset     : 1;
  __REG32           : 1;  /* Must be 0 */
  __REG32 interrupt : 1;
  __REG32 clock     : 2;
  __REG32 watchdog  : 1;
  __REG32           : 2;  /* Must be 00 */
  __REG32 prescaler : 8;
  __REG32           :16;
} __wtcon_bits;

/* Watchdog Timer - Data Register */
/*                - Count Register */
typedef struct {
  __REG32 value :16;
  __REG32       :16;
} __wtdat_bits;

/* IIC - Multimaster Bus Control Register */
typedef struct {
  __REG32 clock     : 4;
  __REG32 flag      : 1;
  __REG32 interrupt : 1;
  __REG32 tx_clock  : 1;
  __REG32 ack_gen   : 1;
  __REG32           :24;
} __iiccon_bits;

/* IIC - Control/Status Register */
typedef struct {
  __REG32 last        : 1;
  __REG32 zero        : 1;
  __REG32 slave       : 1;
  __REG32 arbitration : 1;
  __REG32 out_enable  : 1;
  __REG32 busy        : 1;
  __REG32 mode        : 2;
  __REG32             :24;
} __iicstat_bits;

/* IIC Bus Address Register */
typedef struct {
  __REG32 slave : 8;
  __REG32       :24;
} __iicadd_bits;

/* IIC Bus Transmit/Receive Data Shift Register */
typedef struct {
  __REG32 shift : 8;
  __REG32       :24;
} __iicds_bits;

/* IIC Bus - Multi-Mastaer IIC Bus Line Control Register */
typedef struct {
  __REG32 SDA_delay : 2;
  __REG32 filter    : 1;
  __REG32           : 5;
  __REG32           :24;
} __iiclc_bits;

/* IIS Bus - Control Register */
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

/* IIS Bus - Mode Register */
typedef struct {
  __REG32 clkserial  : 2;
  __REG32 clkmaster  : 1;
  __REG32 data       : 1;
  __REG32 format     : 1;
  __REG32 level      : 1;
  __REG32 trmode     : 2;
  __REG32 msmode     : 1;
  __REG32 mclkselect : 1;
  __REG32            :22;
}__iismod_bits;

/* IIS Bus - Prescaler Register */
typedef struct {
  __REG32 controlb  : 5;
  __REG32 controla  : 5;
  __REG32           :22;
} __iispsr_bits;

/* IIS Bus - FIFO Control Register */
typedef struct {
  __REG32 rdatacnt  : 6;
  __REG32 tdatacnt  : 6;
  __REG32 recieve   : 1;
  __REG32 transmit  : 1;
  __REG32 raccess   : 1;
  __REG32 taccess   : 1;
  __REG32           :16;
} __iisfcon_bits;

/* IIS Bus FIFO Register */
typedef struct {
  __REG16 FENTRY  :16;
}__iisfifo_bits;

/* I/O Port A Control Registers (GPACON & GPADAT) */
typedef struct {
  __REG32 GPA0  : 1;
  __REG32 GPA1  : 1;
  __REG32 GPA2  : 1;
  __REG32 GPA3  : 1;
  __REG32 GPA4  : 1;
  __REG32 GPA5  : 1;
  __REG32 GPA6  : 1;
  __REG32 GPA7  : 1;
  __REG32 GPA8  : 1;
  __REG32 GPA9  : 1;
  __REG32 GPA10 : 1;
  __REG32 GPA11 : 1;
  __REG32 GPA12 : 1;
  __REG32 GPA13 : 1;
  __REG32 GPA14 : 1;
  __REG32 GPA15 : 1;
  __REG32 GPA16 : 1;
  __REG32 GPA17 : 1;
  __REG32 GPA18 : 1;
  __REG32 GPA19 : 1;
  __REG32 GPA20 : 1;
  __REG32 GPA21 : 1;
  __REG32 GPA22 : 1;
  __REG32 GPA23 : 1;
  __REG32 GPA24 : 1;
  __REG32       : 7;
} __gpacon_bits;

/* I/O Port B Control Register (GPBCON) */
typedef struct {
  __REG32 GPB0  : 2;
  __REG32 GPB1  : 2;
  __REG32 GPB2  : 2;
  __REG32 GPB3  : 2;
  __REG32 GPB4  : 2;
  __REG32 GPB5  : 2;
  __REG32 GPB6  : 2;
  __REG32 GPB7  : 2;
  __REG32 GPB8  : 2;
  __REG32 GPB9  : 2;
  __REG32 GPB10 : 2;
  __REG32       :10;
} __gpbcon_bits;

/* I/O Port B Control Register (GPBDAT & GPBUP) */
typedef struct {
  __REG32 GPB0  : 1;
  __REG32 GPB1  : 1;
  __REG32 GPB2  : 1;
  __REG32 GPB3  : 1;
  __REG32 GPB4  : 1;
  __REG32 GPB5  : 1;
  __REG32 GPB6  : 1;
  __REG32 GPB7  : 1;
  __REG32 GPB8  : 1;
  __REG32 GPB9  : 1;
  __REG32 GPB10 : 1;
  __REG32       :21;
} __gpbdat_bits;

/* I/O Port C Control Register (GPCCON) */
typedef struct {
  __REG32 GPC0  : 2;
  __REG32 GPC1  : 2;
  __REG32 GPC2  : 2;
  __REG32 GPC3  : 2;
  __REG32 GPC4  : 2;
  __REG32 GPC5  : 2;
  __REG32 GPC6  : 2;
  __REG32 GPC7  : 2;
  __REG32 GPC8  : 2;
  __REG32 GPC9  : 2;
  __REG32 GPC10 : 2;
  __REG32 GPC11 : 2;
  __REG32 GPC12 : 2;
  __REG32 GPC13 : 2;
  __REG32 GPC14 : 2;
  __REG32 GPC15 : 2;
} __gpccon_bits;

/* I/O Port C Control Register (GPCDAT & GPCUP) */
typedef struct {
  __REG32 GPC0  : 1;
  __REG32 GPC1  : 1;
  __REG32 GPC2  : 1;
  __REG32 GPC3  : 1;
  __REG32 GPC4  : 1;
  __REG32 GPC5  : 1;
  __REG32 GPC6  : 1;
  __REG32 GPC7  : 1;
  __REG32 GPC8  : 1;
  __REG32 GPC9  : 1;
  __REG32 GPC10 : 1;
  __REG32 GPC11 : 1;
  __REG32 GPC12 : 1;
  __REG32 GPC13 : 1;
  __REG32 GPC14 : 1;
  __REG32 GPC15 : 1;
  __REG32       :16;
} __gpcdat_bits;

/* I/O Port D Control Register (GPDCON) */
typedef struct {
  __REG32 GPD0  : 2;
  __REG32 GPD1  : 2;
  __REG32 GPD2  : 2;
  __REG32 GPD3  : 2;
  __REG32 GPD4  : 2;
  __REG32 GPD5  : 2;
  __REG32 GPD6  : 2;
  __REG32 GPD7  : 2;
  __REG32 GPD8  : 2;
  __REG32 GPD9  : 2;
  __REG32 GPD10 : 2;
  __REG32 GPD11 : 2;
  __REG32 GPD12 : 2;
  __REG32 GPD13 : 2;
  __REG32 GPD14 : 2;
  __REG32 GPD15 : 2;
} __gpdcon_bits;

/* I/O Port D Control Register (GPDDAT & GPDUP) */
typedef struct {
  __REG32 GPD0  : 1;
  __REG32 GPD1  : 1;
  __REG32 GPD2  : 1;
  __REG32 GPD3  : 1;
  __REG32 GPD4  : 1;
  __REG32 GPD5  : 1;
  __REG32 GPD6  : 1;
  __REG32 GPD7  : 1;
  __REG32 GPD8  : 1;
  __REG32 GPD9  : 1;
  __REG32 GPD10 : 1;
  __REG32 GPD11 : 1;
  __REG32 GPD12 : 1;
  __REG32 GPD13 : 1;
  __REG32 GPD14 : 1;
  __REG32 GPD15 : 1;
  __REG32       :16;
} __gpddat_bits;

/* I/O Port E Control Register (GPECON) */
typedef struct {
  __REG32 GPE0  : 2;
  __REG32 GPE1  : 2;
  __REG32 GPE2  : 2;
  __REG32 GPE3  : 2;
  __REG32 GPE4  : 2;
  __REG32 GPE5  : 2;
  __REG32 GPE6  : 2;
  __REG32 GPE7  : 2;
  __REG32 GPE8  : 2;
  __REG32 GPE9  : 2;
  __REG32 GPE10 : 2;
  __REG32 GPE11 : 2;
  __REG32 GPE12 : 2;
  __REG32 GPE13 : 2;
  __REG32 GPE14 : 2;
  __REG32 GPE15 : 2;
} __gpecon_bits;

/* I/O Port E Control Register (GPEDAT) */
typedef struct {
  __REG32 GPE0  : 1;
  __REG32 GPE1  : 1;
  __REG32 GPE2  : 1;
  __REG32 GPE3  : 1;
  __REG32 GPE4  : 1;
  __REG32 GPE5  : 1;
  __REG32 GPE6  : 1;
  __REG32 GPE7  : 1;
  __REG32 GPE8  : 1;
  __REG32 GPE9  : 1;
  __REG32 GPE10 : 1;
  __REG32 GPE11 : 1;
  __REG32 GPE12 : 1;
  __REG32 GPE13 : 1;
  __REG32 GPE14 : 1;
  __REG32 GPE15 : 1;
  __REG32       :16;
} __gpedat_bits;

/* I/O Port E Control Register (GPEDAT) */
typedef struct {
  __REG32 GPE0  : 1;
  __REG32 GPE1  : 1;
  __REG32 GPE2  : 1;
  __REG32 GPE3  : 1;
  __REG32 GPE4  : 1;
  __REG32 GPE5  : 1;
  __REG32 GPE6  : 1;
  __REG32 GPE7  : 1;
  __REG32 GPE8  : 1;
  __REG32 GPE9  : 1;
  __REG32 GPE10 : 1;
  __REG32 GPE11 : 1;
  __REG32 GPE12 : 1;
  __REG32 GPE13 : 1;
  __REG32       :18;
} __gpeup_bits;

/* I/O Port F Control Register (GPFCON) */
typedef struct {
  __REG32 GPF0  : 2;
  __REG32 GPF1  : 2;
  __REG32 GPF2  : 2;
  __REG32 GPF3  : 2;
  __REG32 GPF4  : 2;
  __REG32 GPF5  : 2;
  __REG32 GPF6  : 2;
  __REG32 GPF7  : 2;
  __REG32       :16;
} __gpfcon_bits;

/* I/O Port Control Register (GPFDAT & GPFUP) */
typedef struct {
  __REG32 GPF0  : 1;
  __REG32 GPF1  : 1;
  __REG32 GPF2  : 1;
  __REG32 GPF3  : 1;
  __REG32 GPF4  : 1;
  __REG32 GPF5  : 1;
  __REG32 GPF6  : 1;
  __REG32 GPF7  : 1;
  __REG32       :24;
} __gpfdat_bits;

/* I/O Port G Control Register (GPGCON) */
typedef struct {
  __REG32 GPG0  : 2;
  __REG32 GPG1  : 2;
  __REG32 GPG2  : 2;
  __REG32 GPG3  : 2;
  __REG32 GPG4  : 2;
  __REG32 GPG5  : 2;
  __REG32 GPG6  : 2;
  __REG32 GPG7  : 2;
  __REG32 GPG8  : 2;
  __REG32 GPG9  : 2;
  __REG32 GPG10 : 2;
  __REG32 GPG11 : 2;
  __REG32 GPG12 : 2;
  __REG32 GPG13 : 2;
  __REG32 GPG14 : 2;
  __REG32 GPG15 : 2;
} __gpgcon_bits;

/* I/O Port G Control Register (GPGDAT & GPGUP) */
typedef struct {
  __REG32 GPG0  : 1;
  __REG32 GPG1  : 1;
  __REG32 GPG2  : 1;
  __REG32 GPG3  : 1;
  __REG32 GPG4  : 1;
  __REG32 GPG5  : 1;
  __REG32 GPG6  : 1;
  __REG32 GPG7  : 1;
  __REG32 GPG8  : 1;
  __REG32 GPG9  : 1;
  __REG32 GPG10 : 1;
  __REG32 GPG11 : 1;
  __REG32 GPG12 : 1;
  __REG32 GPG13 : 1;
  __REG32 GPG14 : 1;
  __REG32 GPG15 : 1;
  __REG32       :16;
} __gpgdat_bits;

/* I/O Port H Control Register (GPHCON) */
typedef struct {
  __REG32 GPH0  : 2;
  __REG32 GPH1  : 2;
  __REG32 GPH2  : 2;
  __REG32 GPH3  : 2;
  __REG32 GPH4  : 2;
  __REG32 GPH5  : 2;
  __REG32 GPH6  : 2;
  __REG32 GPH7  : 2;
  __REG32 GPH8  : 2;
  __REG32 GPH9  : 2;
  __REG32 GPH10 : 2;
  __REG32       :10;
} __gphcon_bits;

/* I/O Port H Control Register (GPHDAT & GPHUP) */
typedef struct {
  __REG32 GPH0  : 1;
  __REG32 GPH1  : 1;
  __REG32 GPH2  : 1;
  __REG32 GPH3  : 1;
  __REG32 GPH4  : 1;
  __REG32 GPH5  : 1;
  __REG32 GPH6  : 1;
  __REG32 GPH7  : 1;
  __REG32 GPH8  : 1;
  __REG32 GPH9  : 1;
  __REG32 GPH10 : 1;
  __REG32       :21;
} __gphdat_bits;

/* I/O Port J Control Register (GPJCON) */
typedef struct {
  __REG32 GPJ0  : 2;
  __REG32 GPJ1  : 2;
  __REG32 GPJ2  : 2;
  __REG32 GPJ3  : 2;
  __REG32 GPJ4  : 2;
  __REG32 GPJ5  : 2;
  __REG32 GPJ6  : 2;
  __REG32 GPJ7  : 2;
  __REG32 GPJ8  : 2;
  __REG32 GPJ9  : 2;
  __REG32 GPJ10 : 2;
  __REG32 GPJ11 : 2;
  __REG32 GPJ12 : 2;
  __REG32       : 6;
} __gpjcon_bits;

/* I/O Port J Control Register (GPJDAT & GPJUP) */
typedef struct {
  __REG32 GPJ0  : 1;
  __REG32 GPJ1  : 1;
  __REG32 GPJ2  : 1;
  __REG32 GPJ3  : 1;
  __REG32 GPJ4  : 1;
  __REG32 GPJ5  : 1;
  __REG32 GPJ6  : 1;
  __REG32 GPJ7  : 1;
  __REG32 GPJ8  : 1;
  __REG32 GPJ9  : 1;
  __REG32 GPJ10 : 1;
  __REG32 GPJ11 : 1;
  __REG32 GPJ12 : 1;
  __REG32       :19;
} __gpjdat_bits;

/* I/O Port - Miscellaneous Control Register */
typedef struct {
  __REG32 SPUCR0        : 1;
  __REG32 SPUCR1        : 1;
  __REG32               : 1;
  __REG32 SEL_USBPAD    : 1;
  __REG32 CLKSEL0       : 3;
  __REG32               : 1;
  __REG32 CLKSEL1       : 3;
  __REG32               : 1;
  __REG32 SEL_SUSPND0   : 1;
  __REG32 SEL_SUSPND1   : 1;
  __REG32               : 2;
  __REG32 nRSTCON       : 1;
  __REG32 nEN_SCLK0     : 1;
  __REG32 nEN_SCLK1     : 1;
  __REG32 OFFREFRESH    : 1;
  __REG32 BATT_FUNC     : 3;
  __REG32               : 1;
  __REG32               : 1;
  __REG32               : 7;
} __misccr_bits;

/* I/O Ports - DCLK Control Register */
typedef struct {
  __REG32 DCLK0EN     : 1;
  __REG32 DCLK0SelCK  : 1;
  __REG32             : 2;
  __REG32 DCLK0DIV    : 4;
  __REG32 DCLK0CMP    : 4;
  __REG32             : 4;
  __REG32 DCLK1EN     : 1;
  __REG32 DCLK1SeCK   : 1;
  __REG32             : 2;
  __REG32 DCLK1DIV    : 4;
  __REG32 DCLK1CMP    : 4;
  __REG32             : 4;
} __dclkcon_bits;

/* I/O Ports - External Interrupt Control Register 0 */
typedef struct {
  __REG32 EINT0 : 3;
  __REG32       : 1;
  __REG32 EINT1 : 3;
  __REG32       : 1;
  __REG32 EINT2 : 3;
  __REG32       : 1;
  __REG32 EINT3 : 3;
  __REG32       : 1;
  __REG32 EINT4 : 3;
  __REG32       : 1;
  __REG32 EINT5 : 3;
  __REG32       : 1;
  __REG32 EINT6 : 3;
  __REG32       : 1;
  __REG32 EINT7 : 3;
  __REG32       : 1;
} __extint0_bits;

/* I/O Ports - External Interrupt Control Register 1 */
typedef struct {
  __REG32 EINT8   : 3;
  __REG32 FLTEN8  : 1;
  __REG32 EINT9   : 3;
  __REG32 FLTEN9  : 1;
  __REG32 EINT10  : 3;
  __REG32 FLTEN10 : 1;
  __REG32 EINT11  : 3;
  __REG32 FLTEN11 : 1;
  __REG32 EINT12  : 3;
  __REG32 FLTEN12 : 1;
  __REG32 EINT13  : 3;
  __REG32 FLTEN13 : 1;
  __REG32 EINT14  : 3;
  __REG32 FLTEN14 : 1;
  __REG32 EINT15  : 3;
  __REG32 FLTEN15 : 1;
} __extint1_bits;

/* I/O Ports - External Interrupt Control Register 2 */
typedef struct {
  __REG32 EINT16  : 3;
  __REG32 FLTEN16 : 1;
  __REG32 EINT17  : 3;
  __REG32 FLTEN17 : 1;
  __REG32 EINT18  : 3;
  __REG32 FLTEN18 : 1;
  __REG32 EINT19  : 3;
  __REG32 FLTEN19 : 1;
  __REG32 EINT20  : 3;
  __REG32 FLTEN20 : 1;
  __REG32 EINT21  : 3;
  __REG32 FLTEN21 : 1;
  __REG32 EINT22  : 3;
  __REG32 FLTEN22 : 1;
  __REG32 EINT23  : 3;
  __REG32 FLTEN23 : 1;
} __extint2_bits;

/* I/O Ports - External Interrupt Filter Register 2 */
typedef struct {
  __REG32 EINTFLT16 : 7;
  __REG32 FLTCLK16  : 1;
  __REG32 EINTFLT17 : 7;
  __REG32 FLTCLK17  : 1;
  __REG32 EINTFLT18 : 7;
  __REG32 FLTCLK18  : 1;
  __REG32 EINTFLT19 : 7;
  __REG32 FLTCLK19  : 1;
} __eintflt2_bits;

/* I/O Ports - External Interrupt Filter Register 3 */
typedef struct {
  __REG32 EINTFLT20 : 7;
  __REG32 FLTCLK20  : 1;
  __REG32 EINTFLT21 : 7;
  __REG32 FLTCLK21  : 1;
  __REG32 EINTFLT22 : 7;
  __REG32 FLTCLK22  : 1;
  __REG32 EINTFLT23 : 7;
  __REG32 FLTCLK23  : 1;
} __eintflt3_bits;

/* I/O Ports - External Interrupt Mask Register */
/*           - External Interrupt Pending Register*/
typedef struct {
  __REG32         : 4;
  __REG32 EINT4   : 1;
  __REG32 EINT5   : 1;
  __REG32 EINT6   : 1;
  __REG32 EINT7   : 1;
  __REG32 EINT8   : 1;
  __REG32 EINT9   : 1;
  __REG32 EINT10  : 1;
  __REG32 EINT11  : 1;
  __REG32 EINT12  : 1;
  __REG32 EINT13  : 1;
  __REG32 EINT14  : 1;
  __REG32 EINT15  : 1;
  __REG32 EINT16  : 1;
  __REG32 EINT17  : 1;
  __REG32 EINT18  : 1;
  __REG32 EINT19  : 1;
  __REG32 EINT20  : 1;
  __REG32 EINT21  : 1;
  __REG32 EINT22  : 1;
  __REG32 EINT23  : 1;
  __REG32         : 8;
} __eintmask_bits;

/* I/O Ports - General Status Register 0 */
typedef struct {
  __REG32 BATT_FLT  : 1;
  __REG32 RnB       : 1;
  __REG32 NCON      : 1;
  __REG32 nWAIT     : 1;
  __REG32           :28;
} __gstatus0_bits;

/* I/O Ports - General Status Register 1 */
typedef struct {
  __REG32 CHIP_ID : 1;
  __REG32         :31;
} __gstatus1_bits;

/* I/O Ports - General Status Register 2 */
typedef struct {
  __REG32 PWRST     : 1;
  __REG32 SLEEPRST  : 1;
  __REG32 WDTRST    : 1;
  __REG32           : 1;
  __REG32           :28;
} __gstatus2_bits;

/* I/O Ports - General Status Register 3 & 4 */
typedef struct {
  __REG32 inform :32;
} __gstatus34_bits;

/* I/O Ports - DSCn (Drive Strength Control) Register 0 */
typedef struct {
  __REG32 DSC_DATA0 : 2;
  __REG32 DSC_DATA1 : 2;
  __REG32 DSC_DATA2 : 2;
  __REG32 DSC_DATA3 : 2;
  __REG32 DSC_ADR   : 2;
  __REG32           :21;
  __REG32 nEN_DSC   : 1;
} __dsc0_bits;

/* I/O Ports - DSCn (Drive Strength Control) Register 1 */
typedef struct {
  __REG32 DSC_CS0   : 2;
  __REG32 DSC_CS1   : 2;
  __REG32 DSC_CS2   : 2;
  __REG32 DSC_CS3   : 2;
  __REG32 DSC_CS4   : 2;
  __REG32 DSC_CS5   : 2;
  __REG32 DSC_CS6   : 2;
  __REG32 DSC_CS7   : 2;
  __REG32 DSC_WOE   : 2;
  __REG32 DSC_BE    : 2;
  __REG32 DSC_NFC   : 2;
  __REG32 DSC_SDR   : 2;
  __REG32 DSC_SCKE  : 2;
  __REG32 DSC_SCK0  : 2;
  __REG32 DSC_SCK1  : 2;
  __REG32           : 2;
} __dsc1_bits;

/* I/O Ports - MSLCON (Memory Sleep Control Register) */
typedef struct {
  __REG32 PSC_GCS7  : 1;
  __REG32 PSC_GCS6  : 1;
  __REG32 PSC_GCS51 : 1;
  __REG32 PSC_GCS0  : 1;
  __REG32 PSC_WE    : 1;
  __REG32 PSC_OE    : 1;
  __REG32 PSC_DQM   : 1;
  __REG32 PSC_SDR   : 1;
  __REG32 PSC_NF    : 1;
  __REG32 PSC_RnB   : 1;
  __REG32 PSC_WAIT  : 1;
  __REG32 PSC_DATA  : 1;
  __REG32           :20;
} __mslcon_bits;

/* RTC - Control Register */
typedef struct {
  __REG8 RTCEN  : 1;
  __REG8 CLKSEL : 1;
  __REG8 CNTSEL : 1;
  __REG8 CLKRST : 1;
  __REG8        : 4;
} __rtccon_bits;

/* RTC - Tick Time Count Register */
typedef struct {
  __REG8  TICK_TIME_COUNT : 7;
  __REG8  TICK_INT_ENABLE : 1;
} __ticnt_bits;

/* RTC - Alarm Control Register */
typedef struct {
  __REG8 SECEN  : 1;
  __REG8 MINEN  : 1;
  __REG8 HOUREN : 1;
  __REG8 DATEEN : 1;
  __REG8 MONEN  : 1;
  __REG8 YEAREN : 1;
  __REG8 ALMEN  : 1;
  __REG8        : 1;
} __rtcalm_bits;

/* RTC - Alarm Second Data Register */
typedef struct {
  __REG8 SECDATA  : 7;
  __REG8          : 1;
} __almsec_bits;

/* RTC - Alarm Min Data */
typedef struct {
  __REG8 MINDATA  : 7;
  __REG8          : 1;
} __almmin_bits;

/* RTC - Alarm Hour Data */
typedef struct {
  __REG8 HOURDATA : 6;
  __REG8          : 2;
} __almhour_bits;

/* RTC - Alarm Date Data */
typedef struct {
  __REG8 DATEDATA : 6;
  __REG8          : 2;
} __almdate_bits;

/* RTC - Alarm Mon Data */
typedef struct {
  __REG8 MONDATA  : 5;
  __REG8          : 3;
} __almmon_bits;

/* RTC - Alarm Year Data */
typedef struct {
  __REG8 YEARDATA  : 8;
} __almyear_bits;

/* RTC - BCD Second Register */
typedef struct {
  __REG8 SECDATA  : 7;
  __REG8          : 1;
} __bcdsec_bits;

/* RTC - BCD Minute Register */
typedef struct {
  __REG8 MINDATA  : 7;
  __REG8          : 1;
} __bcdmin_bits;

/* RTC - BCD Hour Register */
typedef struct {
  __REG8 HOURDATA : 6;
  __REG8          : 2;
} __bcdhour_bits;

/* RTC - BCD Date Register */
typedef struct {
  __REG8 DATEDATA : 6;
  __REG8          : 2;
} __bcddate_bits;

/* RTC - BCD Day Register */
typedef struct {
  __REG8 DAYDATA  : 3;
  __REG8          : 5;
} __bcdday_bits;

/* RTC - BCD Month Register */
typedef struct {
  __REG8 MONDATA  : 5;
  __REG8          : 3;
} __bcdmon_bits;

/* RTC - BCD Year Register */
typedef struct {
  __REG8 YEARDATA  : 8;
} __bcdyear_bits;

/* ADC - Control Register */
typedef struct {
  __REG32 ENABLE_START  : 1;
  __REG32 READ_START    : 1;
  __REG32 STDBM         : 1;
  __REG32 SEL_MUX       : 3;
  __REG32 PRSCVL        : 8;
  __REG32 PRSCEN        : 1;
  __REG32 ECFLG         : 1;
  __REG32               :16;
} __adccon_bits;

/* ADC - Touch Screen Control Register */
typedef struct {
  __REG32 XY_PST    : 2;
  __REG32 AUTO_PST  : 1;
  __REG32 PULL_UP   : 1;
  __REG32 XP_SEN    : 1;
  __REG32 XM_SEN    : 1;
  __REG32 YP_SEN    : 1;
  __REG32 YM_SEN    : 1;
  __REG32 UD_SEN    : 1;
  __REG32           :23;
} __adctsc_bits;

/* ADC - Start Delay Register */
typedef struct {
  __REG32 DELAY :16;
  __REG32       :16;
} __adcdly_bits;

/* ADC - Conversion Data Register 0 */
typedef struct {
  __REG32 XPDATA    :10;
  __REG32           : 2;
  __REG32 XY_PST    : 2;
  __REG32 AUTO_PST  : 1;
  __REG32 UPDOWN    : 1;
  __REG32           :16;
} __adcdat0_bits;

/* ADC - Conversion Data Register 1 */
typedef struct {
  __REG32 YPDATA    :10;
  __REG32           : 2;
  __REG32 XY_PST    : 2;
  __REG32 AUTO_PST  : 1;
  __REG32 UPDOWN    : 1;
  __REG32           :16;
} __adcdat1_bits;

/* ADC - Touch Screen Up-Down Register */
typedef struct {
  __REG32 TSC_DN  : 1;
  __REG32 TSC_UP  : 1;
  __REG32         :30;
} __adcupdn_bits;

/* SPI - Control Register */
typedef struct {
  __REG32 TAGD  : 1;
  __REG32 CPHA  : 1;
  __REG32 CPOL  : 1;
  __REG32 MSTR  : 1;
  __REG32 ENSCK : 1;
  __REG32 SMOD  : 2;
  __REG32       :25;
} __spconn_bits;

/* SPI - Status Register */
typedef struct {
  __REG32 REDY  : 1;
  __REG32 MULF  : 1;
  __REG32 DCOL  : 1;
  __REG32       : 5;
  __REG32       :24;
} __spstan_bits;

/* SPI - Pin Control Register */
typedef struct {
  __REG32 KEEP  : 1;
  __REG32       : 1;
  __REG32 ENMUL : 1;
  __REG32       : 5;
  __REG32       :24;
} __sppinn_bits;

/* SPI - Baud Rate Prescaler Register */
typedef struct {
  __REG32 VALUE : 8;
  __REG32       :24;
} __sppren_bits;

/* SPI - Tx Data Register */
typedef struct {
  __REG32 TXDATA  : 8;
  __REG32         : 24;
} __sptdatn_bits;

/* SPI - Rx Data Register */
typedef struct {
  __REG32 RXDATA  : 8;
  __REG32         : 24;
} __sprdatn_bits;

/* SDI - Control Register */
typedef struct {
  __REG32 ENCLK     : 1;
  __REG32           : 1;
  __REG32 RWaitEn   : 1;
  __REG32 RcvIOInt  : 1;
  __REG32 ByteOrder : 1;
  __REG32 CTYP      : 1;
  __REG32           : 2;
  __REG32 SDreset   : 1;
  __REG32           :23;
} __sdicon_bits;

/* SDI - Baud Rate Prescaler Register */
typedef struct {
  __REG32 VALUE : 8;
  __REG32       : 24;
} __sdipre_bits;

/* SDI - Command Control Register */
typedef struct {
  __REG32 CmdIndex  : 8;
  __REG32 CMST      : 1;
  __REG32 WaitRsp   : 1;
  __REG32 LongRsp   : 1;
  __REG32 WithData  : 1;
  __REG32 AbortCmd  : 1;
  __REG32           :19;
} __sdiccon_bits;

/* SDI - Command Status Register */
typedef struct {
  __REG32 RspIndex  : 8;
  __REG32 CmdOn     : 1;
  __REG32 RspFin    : 1;
  __REG32 CmdTout   : 1;
  __REG32 CmdSent   : 1;
  __REG32 RspCrc    : 1;
  __REG32           :19;
} __sdicsta_bits;

/* SDI Response Register 1 */
typedef struct {
  __REG32 Response1 :24;
  __REG32 RCRC7     : 8;
} __sdirsp1_bits;

/* SDI Data / Busy Timer Register */
typedef struct {
  __REG32 DataTimer :23;
  __REG32           : 9;
} __sdidtimer_bits;

/* SDI - Block Size Register */
typedef struct {
  __REG32 BlkSize :12;
  __REG32         :20;
} __sdibsize_bits;

/* SDI - Data Control Register */
typedef struct {
  __REG32 BlkNum    :12;
  __REG32 DatMode   : 2;
  __REG32 DTST      : 1;
  __REG32 EnDMA     : 1;
  __REG32 WideBus   : 1;
  __REG32 BlkMode   : 1;
  __REG32 BACMD     : 1;
  __REG32 RACMD     : 1;
  __REG32 TARSP     : 1;
  __REG32 PrdType   : 1;
  __REG32 DataSize  : 2;
  __REG32 Burst4    : 1;
  __REG32           : 7;
} __sdidcon_bits;

/* SDI - Data Remain Counter Register */
typedef struct {
  __REG32 BlkCnt    :12;
  __REG32 BlkNumCnt :12;
  __REG32           : 8;
} __sdidcnt_bits;

/* SDI - Data Status Register */
typedef struct {
  __REG32 RxDatOn   : 1;
  __REG32 TxDatOn   : 1;
  __REG32           : 1;
  __REG32 BusyFin   : 1;
  __REG32 DatFin    : 1;
  __REG32 DatOut    : 1;
  __REG32 DatCrc    : 1;
  __REG32 CrcSta    : 1;
  __REG32           : 1;
  __REG32 IOIntDet  : 1;
  __REG32 RWaitReq  : 1;
  __REG32 NoBusy    : 1;
  __REG32           :20;
} __sdidsta_bits;

/* SDI - FIFO Status Register */
typedef struct {
  __REG32 FFCNT   : 7;
  __REG32 RFHalf  : 1;
  __REG32 RFFull  : 1;
  __REG32 RFLast  : 1;
  __REG32 TFEmpty : 1;
  __REG32 TFHalf  : 1;
  __REG32 RFDET   : 1;
  __REG32 TFDET   : 1;
  __REG32 FFfail  : 2;
  __REG32 FRST    : 1;
  __REG32         :15;
} __sdifsta_bits;

/* SDI - Interrupt Mask Register */
typedef struct {
  __REG32 RFHalfInt    : 1;
  __REG32 RFFullInt    : 1;
  __REG32 RFLastInt    : 1;
  __REG32 TFEmptyInt   : 1;
  __REG32 TFHalfInt    : 1;
  __REG32              : 1;
  __REG32 BusyFinInt   : 1;
  __REG32 DatFinInt    : 1;
  __REG32 DatToutInt   : 1;
  __REG32 DatCrcInt    : 1;
  __REG32 CrcStaInt    : 1;
  __REG32 FFfailInt    : 1;
  __REG32 IntDetInt    : 1;
  __REG32 RWReqInt     : 1;
  __REG32 RspEndInt    : 1;
  __REG32 CmdToutInt   : 1;
  __REG32 CmdSentInt   : 1;
  __REG32 RspCrcInt    : 1;
  __REG32 NoBusyInt    : 1;
  __REG32              :13;
} __sdiimsk_bits;

/* AC97 Controller - Global Control Register */
typedef struct {
  __REG32 ColdReset   : 1;
  __REG32 WarmReset   : 1;
  __REG32 AC_link     : 1;
  __REG32 Transfer    : 1;
  __REG32             : 4;
  __REG32 MIC_in      : 2;
  __REG32 PCM_in      : 2;
  __REG32 PCM_out     : 2;
  __REG32             : 2;
  __REG32 MIC_inTIr   : 1;
  __REG32 PCM_inTIr   : 1;
  __REG32 PCM_outTIr  : 1;
  __REG32 MIC_inOIr   : 1;
  __REG32 PCM_inOIr   : 1;
  __REG32 PCM_outUIr  : 1;
  __REG32 Codec       : 1;
  __REG32             : 9;
} __acglbctrl_bits;

/* AC97 Controller - Global Status Register */
typedef struct {
  __REG32 Controller  : 3;
  __REG32             :13;
  __REG32 MIC_inTIr   : 1;
  __REG32 PCM_inRIr   : 1;
  __REG32 PCM_outTIr  : 1;
  __REG32 MIC_inOIr   : 1;
  __REG32 PCM_inOIr   : 1;
  __REG32 PCM_outUIr  : 1;
  __REG32 Codec       : 1;
  __REG32             : 9;
} __acglbstat_bits;

/* AC97 Controller - Codec Command Register */
/*                 - Codec Status Register */
typedef struct {
  __REG32 Data    : 16;
  __REG32 Adress  : 7;
  __REG32 Read    : 1;
  __REG32         : 8;
} __accodeccmd_bits;

/* AC97 Controller - PCM Out/In Channel FIFO Address Register */
typedef struct {
  __REG32 InWrite   : 4;
  __REG32           : 4;
  __REG32 OutWrite  : 4;
  __REG32           : 4;
  __REG32 InRead    : 4;
  __REG32           : 4;
  __REG32 OutRead   : 4;
  __REG32           : 4;
} __acpcmaddr_bits;

/* AC97 Controller - MIC In Channel FIFO Address Register */
typedef struct {
  __REG32 Write : 4;
  __REG32       :12;
  __REG32 Read  : 4;
  __REG32       :12;
} __acmicaddr_bits;

/* AC97 Controller - PCM Out/In Channel FIFO Data Register */
typedef struct {
  __REG32 Right :16;
  __REG32 Left  :16;
} __acpcmdata_bits;

/* AC97 Controller - MIC In Channel FIFO Data Register */
typedef struct {
  __REG32 Mono  :16;
  __REG32       :16;
} __acmicdata_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/

/***************************************************************************
 **
 **  Memory Control Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(BWSCON,    0x48000000, __READ_WRITE, __bwscon_bits);
__IO_REG32_BIT(BANKCON0,  0x48000004, __READ_WRITE, __bankconn_bits);
__IO_REG32_BIT(BANKCON1,  0x48000008, __READ_WRITE, __bankconn_bits);
__IO_REG32_BIT(BANKCON2,  0x4800000c, __READ_WRITE, __bankconn_bits);
__IO_REG32_BIT(BANKCON3,  0x48000010, __READ_WRITE, __bankconn_bits);
__IO_REG32_BIT(BANKCON4,  0x48000014, __READ_WRITE, __bankconn_bits);
__IO_REG32_BIT(BANKCON5,  0x48000018, __READ_WRITE, __bankconn_bits);
__IO_REG32_BIT(BANKCON6,  0x4800001c, __READ_WRITE, __bankconn2_bits);
__IO_REG32_BIT(BANKCON7,  0x48000020, __READ_WRITE, __bankconn2_bits);
__IO_REG32_BIT(REFRESH,   0x48000024, __READ_WRITE, __refresh_bits);
__IO_REG32_BIT(BANKSIZE,  0x48000028, __READ_WRITE, __banksize_bits);
__IO_REG32_BIT(MRSRB6,    0x4800002c, __READ_WRITE, __mrsrbx_bits);
__IO_REG32_BIT(MRSRB7,    0x48000030, __READ_WRITE, __mrsrbx_bits);


/***************************************************************************
 **
 **  USB Host Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(HcRevision,          0x49000000,__READ_WRITE,__hcrevision_bits);
__IO_REG32_BIT(HcControl,           0x49000004,__READ_WRITE,__hccontrol_bits);
__IO_REG32_BIT(HcCommandStatus,     0x49000008,__READ_WRITE,__hccommandstatus_bits);
__IO_REG32_BIT(HcInterruptStatus,   0x4900000c,__READ_WRITE,__hcinterruptstatus_bits);
__IO_REG32_BIT(HcInterruptEnable,   0x49000010,__READ_WRITE,__hcinterruptenable_bits);
__IO_REG32_BIT(HcInterruptDis,      0x49000014,__READ_WRITE,__hcinterruptenable_bits);
__IO_REG32_BIT(HcHCCA,              0x49000018,__READ_WRITE,__hchcca_bits);
__IO_REG32_BIT(HcPeriodCurrentED,   0x4900001c,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcControlHeadED,     0x49000020,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcControlCurrentED,  0x49000024,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcBulkHeadED,        0x49000028,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcBulkCurrentED,     0x4900002c,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcDoneHead,          0x49000030,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcFmInterval,        0x49000034,__READ_WRITE,__hcfminterval_bits);
__IO_REG32_BIT(HcFmRemaining,       0x49000038,__READ_WRITE,__hcfmremaining_bits);
__IO_REG32_BIT(HcFmNumber,          0x4900003c,__READ_WRITE,__hcfmnumber_bits);
__IO_REG32_BIT(HcPeriodicStart,     0x49000040,__READ_WRITE,__hcperiodicstart_bits);
__IO_REG32_BIT(HcLSThreshold,       0x49000044,__READ_WRITE,__hclsthreshold_bits);
__IO_REG32_BIT(HcRhDescriptorA,     0x49000048,__READ_WRITE,__hcrhdescriptora_bits);
__IO_REG32_BIT(HcRhDescriptorB,     0x4900004c,__READ_WRITE,__hcrhdescriptorb_bits);
__IO_REG32_BIT(HcRhStatus,          0x49000050,__READ_WRITE,__hcrhstatus_bits);
__IO_REG32_BIT(HcRhPortStatus1,     0x49000054,__READ_WRITE,__hcrhportstatus_bits);
__IO_REG32_BIT(HcRhPortStatus2,     0x49000058,__READ_WRITE,__hcrhportstatus_bits);

/***************************************************************************
 **
 **  Interrupt Controller Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(SRCPND,    0x4a000000, __READ_WRITE, __srcpnd_bits);
__IO_REG32_BIT(INTMOD,    0x4a000004, __READ_WRITE, __srcpnd_bits);
__IO_REG32_BIT(INTMSK,    0x4a000008, __READ_WRITE, __srcpnd_bits);
__IO_REG32_BIT(PRIORITY,  0x4a00000c, __READ_WRITE, __priority_bits);
__IO_REG32_BIT(INTPND,    0x4a000010, __READ_WRITE, __srcpnd_bits);
__IO_REG32(    INTOFFSET, 0x4a000014, __READ      );
__IO_REG32_BIT(SUBSRCPND, 0x4a000018, __READ_WRITE, __subsrcpnd_bits);
__IO_REG32_BIT(INTSUBMSK, 0x4a00001c, __READ_WRITE, __subsrcpnd_bits);

/***************************************************************************
 **
 **  DMA Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(DISRC0,    0x4b000000, __READ_WRITE, __disrcn_bits);
__IO_REG32_BIT(DISRCC0,   0x4b000004, __READ_WRITE, __disrccn_bits);
__IO_REG32_BIT(DIDST0,    0x4b000008, __READ_WRITE, __didstn_bits);
__IO_REG32_BIT(DIDSTC0,   0x4b00000c, __READ_WRITE, __didstcn_bits);
__IO_REG32_BIT(DCON0,     0x4b000010, __READ_WRITE, __dconn_bits);
__IO_REG32_BIT(DSTAT0,    0x4b000014, __READ,       __dstatn_bits);
__IO_REG32_BIT(DCSRC0,    0x4b000018, __READ,       __dcsrcn_bits);
__IO_REG32_BIT(DCDST0,    0x4b00001c, __READ,       __dcdstn_bits);
__IO_REG32_BIT(DMASKTRIG0,0x4b000020, __READ_WRITE, __dmasktrign_bits);

__IO_REG32_BIT(DISRC1,    0x4b000040, __READ_WRITE, __disrcn_bits);
__IO_REG32_BIT(DISRCC1,   0x4b000044, __READ_WRITE, __disrccn_bits);
__IO_REG32_BIT(DIDST1,    0x4b000048, __READ_WRITE, __didstn_bits);
__IO_REG32_BIT(DIDSTC1,   0x4b00004c, __READ_WRITE, __didstcn_bits);
__IO_REG32_BIT(DCON1,     0x4b000050, __READ_WRITE, __dconn_bits);
__IO_REG32_BIT(DSTAT1,    0x4b000054, __READ,       __dstatn_bits);
__IO_REG32_BIT(DCSRC1,    0x4b000058, __READ,       __dcsrcn_bits);
__IO_REG32_BIT(DCDST1,    0x4b00005c, __READ,       __dcdstn_bits);
__IO_REG32_BIT(DMASKTRIG1,0x4b000060, __READ_WRITE, __dmasktrign_bits);

__IO_REG32_BIT(DISRC2,    0x4b000080, __READ_WRITE, __disrcn_bits);
__IO_REG32_BIT(DISRCC2,   0x4b000084, __READ_WRITE, __disrccn_bits);
__IO_REG32_BIT(DIDST2,    0x4b000088, __READ_WRITE, __didstn_bits);
__IO_REG32_BIT(DIDSTC2,   0x4b00008c, __READ_WRITE, __didstcn_bits);
__IO_REG32_BIT(DCON2,     0x4b000090, __READ_WRITE, __dconn_bits);
__IO_REG32_BIT(DSTAT2,    0x4b000094, __READ,       __dstatn_bits);
__IO_REG32_BIT(DCSRC2,    0x4b000098, __READ,       __dcsrcn_bits);
__IO_REG32_BIT(DCDST2,    0x4b00009c, __READ,       __dcdstn_bits);
__IO_REG32_BIT(DMASKTRIG2,0x4b0000a0, __READ_WRITE, __dmasktrign_bits);

__IO_REG32_BIT(DISRC3,    0x4b0000c0, __READ_WRITE, __disrcn_bits);
__IO_REG32_BIT(DISRCC3,   0x4b0000c4, __READ_WRITE, __disrccn_bits);
__IO_REG32_BIT(DIDST3,    0x4b0000c8, __READ_WRITE, __didstn_bits);
__IO_REG32_BIT(DIDSTC3,   0x4b0000cc, __READ_WRITE, __didstcn_bits);
__IO_REG32_BIT(DCON3,     0x4b0000d0, __READ_WRITE, __dconn_bits);
__IO_REG32_BIT(DSTAT3,    0x4b0000d4, __READ,       __dstatn_bits);
__IO_REG32_BIT(DCSRC3,    0x4b0000d8, __READ,       __dcsrcn_bits);
__IO_REG32_BIT(DCDST3,    0x4b0000dc, __READ,       __dcdstn_bits);
__IO_REG32_BIT(DMASKTRIG3,0x4b0000e0, __READ_WRITE, __dmasktrign_bits);

/***************************************************************************
 **
 **  Clock Generator & Power Management Register
 **
 ***************************************************************************/
__IO_REG32_BIT(LOCKTIME,  0x4c000000, __READ_WRITE, __locktime_bits);
__IO_REG32_BIT(MPLLCON,   0x4c000004, __READ_WRITE, __pllcon_bits);
__IO_REG32_BIT(UPLLCON,   0x4c000008, __READ_WRITE, __pllcon_bits);
__IO_REG32_BIT(CLKCON,    0x4c00000c, __READ_WRITE, __clkcon_bits);
__IO_REG32_BIT(CLKSLOW,   0x4c000010, __READ_WRITE, __clkslow_bits);
__IO_REG32_BIT(CLKDIVN,   0x4c000014, __READ_WRITE, __clkdivn_bits);
__IO_REG32_BIT(CAMDIVN,   0x4c000018, __READ_WRITE, __camdivn_bits);

/***************************************************************************
 **
 **  LCD Control Register
 **
 ***************************************************************************/
__IO_REG32_BIT(LCDCON1,   0x4d000000, __READ_WRITE, __lcdcon1_bits);
__IO_REG32_BIT(LCDCON2,   0x4d000004, __READ_WRITE, __lcdcon2_bits);
__IO_REG32_BIT(LCDCON3,   0x4d000008, __READ_WRITE, __lcdcon3_bits);
__IO_REG32_BIT(LCDCON4,   0x4d00000c, __READ_WRITE, __lcdcon4_bits);
__IO_REG32_BIT(LCDCON5,   0x4d000010, __READ_WRITE, __lcdcon5_bits);
__IO_REG32_BIT(LCDSADDR1, 0x4d000014, __READ_WRITE, __lcdsaddr1_bits);
__IO_REG32_BIT(LCDSADDR2, 0x4d000018, __READ_WRITE, __lcdsaddr2_bits);
__IO_REG32_BIT(LCDSADDR3, 0x4d00001c, __READ_WRITE, __lcdsaddr3_bits);
__IO_REG32_BIT(REDLUT,    0x4d000020, __READ_WRITE, __redlut_bits);
__IO_REG32_BIT(GREENLUT,  0x4d000024, __READ_WRITE, __greenlut_bits);
__IO_REG32_BIT(BLUELUT,   0x4d000028, __READ_WRITE, __bluelut_bits);
__IO_REG32_BIT(DITHMODE,  0x4d00004c, __READ_WRITE, __dithmode_bits);
__IO_REG32_BIT(TPAL,      0x4d000050, __READ_WRITE, __tpal_bits);
__IO_REG32_BIT(LCDINTPND, 0x4d000054, __READ_WRITE, __lcdintpnd_bits);
__IO_REG32_BIT(LCDSRCPND, 0x4d000058, __READ_WRITE, __lcdintpnd_bits);
__IO_REG32_BIT(LCDINTMSK, 0x4d00005c, __READ_WRITE, __lcdintmsk_bits);
__IO_REG32_BIT(TCONSEL,   0x4d000060, __READ_WRITE, __tconsel_bits);

/***************************************************************************
 **
 **  NAND Flash Control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(NFCONF,  0x4e000000, __READ_WRITE, __nfconf_bits);
__IO_REG32_BIT(NFCONT,  0x4e000004, __READ_WRITE, __nfcont_bits);
__IO_REG32_BIT(NFCMD,   0x4e000008, __READ_WRITE, __nfcmd_bits);
__IO_REG32_BIT(NFADDR,  0x4e00000c, __READ_WRITE, __nfaddr_bits);
__IO_REG32(   NFDATA,  0x4e000010, __READ_WRITE);
__IO_REG32_BIT(NFMECCD0,0x4e000014, __READ_WRITE, __nfmeccd0_bits);
__IO_REG32_BIT(NFMECCD1,0x4e000018, __READ_WRITE, __nfmeccd1_bits);
__IO_REG32_BIT(NFSECCD, 0x4e00001c, __READ_WRITE, __nfmeccd0_bits);
__IO_REG32_BIT(NFSTAT,  0x4e000020, __READ_WRITE, __nfstat_bits);
__IO_REG32_BIT(NFESTAT0,0x4e000024, __READ_WRITE, __nfestatn_bits);
__IO_REG32_BIT(NFESTAT1,0x4e000028, __READ_WRITE, __nfestatn_bits);
__IO_REG32_BIT(NFMECC0, 0x4e00002c, __READ      , __nfmecc0_bits);
__IO_REG32_BIT(NFMECC1, 0x4e000030, __READ      , __nfmecc1_bits);
__IO_REG32_BIT(NFSECC,  0x4e000034, __READ      , __nfsecc_bits);
__IO_REG32_BIT(NFSBLK,  0x4e000038, __READ_WRITE, __nfsblk_bits);
__IO_REG32_BIT(NFEBLK,  0x4e00003c, __READ_WRITE, __nfeblk_bits);

/***************************************************************************
 **
 **  Camera Interface Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(CISRCFMT,        0x4f000000, __READ_WRITE, __cisrcfmt_bits);
__IO_REG32_BIT(CIWDOFST,        0x4f000004, __READ_WRITE, __ciwdofst_bits);
__IO_REG32_BIT(CIGCTRL,         0x4f000008, __READ_WRITE, __cigctrl_bits);
__IO_REG32(   CICOYSA1,        0x4f000018, __READ_WRITE);
__IO_REG32(   CICOYSA2,        0x4f00001c, __READ_WRITE);
__IO_REG32(   CICOYSA3,        0x4f000020, __READ_WRITE);
__IO_REG32(   CICOYSA4,        0x4f000024, __READ_WRITE);
__IO_REG32(   CICOCBSA1,       0x4f000028, __READ_WRITE);
__IO_REG32(   CICOCBSA2,       0x4f00002c, __READ_WRITE);
__IO_REG32(   CICOCBSA3,       0x4f000030, __READ_WRITE);
__IO_REG32(   CICOCBSA4,       0x4f000034, __READ_WRITE);
__IO_REG32(   CICOCRSA1,       0x4f000038, __READ_WRITE);
__IO_REG32(   CICOCRSA2,       0x4f00003c, __READ_WRITE);
__IO_REG32(   CICOCRSA3,       0x4f000040, __READ_WRITE);
__IO_REG32(   CICOCRSA4,       0x4f000044, __READ_WRITE);
__IO_REG32_BIT(CICOTRGFMT,      0x4f000048, __READ_WRITE, __cicotrgfmt_bits);
__IO_REG32_BIT(CICOCTRL,        0x4f00004c, __READ_WRITE, __cicoctrl_bits);
__IO_REG32_BIT(CICOSCPRERATIO,  0x4f000050, __READ_WRITE, __cicoscpreratio_bits);
__IO_REG32_BIT(CICOSCPREDST,    0x4f000054, __READ_WRITE, __cicoscpredst_bits);
__IO_REG32_BIT(CICOSCCTRL,      0x4f000058, __READ_WRITE, __cicoscctrl_bits);
__IO_REG32_BIT(CICOTAREA,       0x4f00005c, __READ_WRITE, __cicotarea_bits);
__IO_REG32_BIT(CICOSTATUS,      0x4f000064, __READ      , __cicostatus_bits);
__IO_REG32(   CIPRCLRSA1,      0x4f00006c, __READ_WRITE);
__IO_REG32(   CIPRCLRSA2,      0x4f000070, __READ_WRITE);
__IO_REG32(   CIPRCLRSA3,      0x4f000074, __READ_WRITE);
__IO_REG32(   CIPRCLRSA4,      0x4f000078, __READ_WRITE);
__IO_REG32_BIT(CIPRTRGFMT,      0x4f00007c, __READ_WRITE, __ciprtrgfmt_bits);
__IO_REG32_BIT(CIPRCTRL,        0x4f000080, __READ_WRITE, __ciprctrl_bits);
__IO_REG32_BIT(CIPRSCPRERATIO,  0x4f000084, __READ_WRITE, __ciprscpreratio_bits);
__IO_REG32_BIT(CIPRSCPREDST,    0x4f000088, __READ_WRITE, __ciprscpredst_bits);
__IO_REG32_BIT(CIPRSCCTRL,      0x4f00008c, __READ_WRITE, __ciprscctrl_bits);
__IO_REG32_BIT(CIPRTAREA,       0x4f000090, __READ_WRITE, __ciprtarea_bits);
__IO_REG32_BIT(CIPRSTATUS,      0x4f000098, __READ_WRITE, __ciprstatus_bits);
__IO_REG32_BIT(CIIMGCPT,        0x4f0000a0, __READ_WRITE, __ciimgcpt_bits);



/***************************************************************************
 **
 **  UART
 **
 ***************************************************************************/
__IO_REG32_BIT(ULCON0,  0x50000000, __READ_WRITE, __ulconn_bits);
__IO_REG32_BIT(UCON0,   0x50000004, __READ_WRITE, __uconn_bits);
__IO_REG32_BIT(UFCON0,  0x50000008, __READ_WRITE, __ufconn_bits);
__IO_REG32_BIT(UMCON0,  0x5000000c, __READ_WRITE, __umconn_bits);
__IO_REG32_BIT(UTRSTAT0,0x50000010, __READ      , __utrstatn_bits);
__IO_REG32_BIT(UERSTAT0,0x50000014, __READ      , __uerstatn_bits);
__IO_REG32_BIT(UFSTAT0, 0x50000018, __READ      , __ufstatn_bits);
__IO_REG32_BIT(UMSTAT0, 0x5000001c, __READ      , __umstatn_bits);
__IO_REG32_BIT(UBRDIV0, 0x50000028, __READ_WRITE, __ubrdivn_bits);

__IO_REG32_BIT(ULCON1,  0x50004000, __READ_WRITE, __ulconn_bits);
__IO_REG32_BIT(UCON1,   0x50004004, __READ_WRITE, __uconn_bits);
__IO_REG32_BIT(UFCON1,  0x50004008, __READ_WRITE, __ufconn_bits);
__IO_REG32_BIT(UMCON1,  0x5000400c, __READ_WRITE, __umconn_bits);
__IO_REG32_BIT(UTRSTAT1,0x50004010, __READ      , __utrstatn_bits);
__IO_REG32_BIT(UERSTAT1,0x50004014, __READ      , __uerstatn_bits);
__IO_REG32_BIT(UFSTAT1, 0x50004018, __READ      , __ufstatn_bits);
__IO_REG32_BIT(UMSTAT1, 0x5000401c, __READ      , __umstatn_bits);
__IO_REG32_BIT(UBRDIV1, 0x50004028, __READ_WRITE, __ubrdivn_bits);

__IO_REG32_BIT(ULCON2,  0x50008000, __READ_WRITE, __ulconn_bits);
__IO_REG32_BIT(UCON2,   0x50008004, __READ_WRITE, __uconn_bits);
__IO_REG32_BIT(UFCON2,  0x50008008, __READ_WRITE, __ufconn_bits);
__IO_REG32_BIT(UTRSTAT2,0x50008010, __READ      , __utrstatn_bits);
__IO_REG32_BIT(UERSTAT2,0x50008014, __READ      , __uerstatn_bits);
__IO_REG32_BIT(UFSTAT2, 0x50008018, __READ      , __ufstatn_bits);
__IO_REG32_BIT(UBRDIV2, 0x50008028, __READ_WRITE, __ubrdivn_bits);

#if __LITTLE_ENDIAN__

__IO_REG8(    UTXH0,    0x50000020, __WRITE);
__IO_REG8(    URXH0,    0x50000024, __READ);
__IO_REG8(    UTXH1,    0x50004020, __WRITE);
__IO_REG8(    URXH1,    0x50004024, __READ);
__IO_REG8(    UTXH2,    0x50008020, __WRITE);
__IO_REG8(    URXH2,    0x50008024, __READ);

#else  /* __LITTLE_ENDIAN */

__IO_REG8(    UTXH0,    0x50000023, __WRITE);
__IO_REG8(    URXH0,    0x50000027, __READ);
__IO_REG8(    UTXH1,    0x50004023, __WRITE);
__IO_REG8(    URXH1,    0x50004027, __READ);
__IO_REG8(    UTXH2,    0x50008023, __WRITE);
__IO_REG8(    URXH2,    0x50008027, __READ);

#endif /* __LITTLE_ENDIAN__ */

/***************************************************************************
 **
 ** PWM Timer Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(TCFG0, 0x51000000, __READ_WRITE, __tcfg0_bits);
__IO_REG32_BIT(TCFG1, 0x51000004, __READ_WRITE, __tcfg1_bits);
__IO_REG32_BIT(TCON,  0x51000008, __READ_WRITE, __tcon_bits);
__IO_REG32_BIT(TCNTB0,0x5100000c, __READ_WRITE, __tcntbx_bits);
__IO_REG32_BIT(TCMPB0,0x51000010, __READ_WRITE, __tcmpbx_bits);
__IO_REG32_BIT(TCNTO0,0x51000014, __READ      , __tcntox_bits);
__IO_REG32_BIT(TCNTB1,0x51000018, __READ_WRITE, __tcntbx_bits);
__IO_REG32_BIT(TCMPB1,0x5100001c, __READ_WRITE, __tcmpbx_bits);
__IO_REG32_BIT(TCNTO1,0x51000020, __READ      , __tcntox_bits);
__IO_REG32_BIT(TCNTB2,0x51000024, __READ_WRITE, __tcntbx_bits);
__IO_REG32_BIT(TCMPB2,0x51000028, __READ_WRITE, __tcmpbx_bits);
__IO_REG32_BIT(TCNTO2,0x5100002c, __READ      , __tcntox_bits);
__IO_REG32_BIT(TCNTB3,0x51000030, __READ_WRITE, __tcntbx_bits);
__IO_REG32_BIT(TCMPB3,0x51000034, __READ_WRITE, __tcmpbx_bits);
__IO_REG32_BIT(TCNTO3,0x51000038, __READ      , __tcntox_bits);
__IO_REG32_BIT(TCNTB4,0x5100003c, __READ_WRITE, __tcntbx_bits);
__IO_REG32_BIT(TCNTO4,0x51000040, __READ      , __tcntox_bits);

/***************************************************************************
 **
 **  USB Device Controller Registers
 **
 ***************************************************************************/
#if __LITTLE_ENDIAN__

__IO_REG8_BIT(FUNC_ADDR_REG,     0x52000140, __READ_WRITE, __funcaddrreg_bits);
__IO_REG8_BIT(PWR_REG,           0x52000144, __READ_WRITE, __pwraddr_bits);
__IO_REG8_BIT(EP_INT_REG,        0x52000148, __READ_WRITE, __epintreg_bits);
__IO_REG8_BIT(USB_INT_REG,       0x52000158, __READ_WRITE, __usbintreg_bits);
__IO_REG8_BIT(EP_INT_EN_REG,     0x5200015c, __READ_WRITE, __epintenreg_bits);
__IO_REG8_BIT(USB_INT_EN_REG,    0x5200016c, __READ_WRITE, __usbintenreg_bits);
__IO_REG8_BIT(FRAME_NUM1_REG,    0x52000170, __READ,       __framenum1reg_bits);
__IO_REG8_BIT(FRAME_NUM2_REG,    0x52000174, __READ,       __framenum2reg_bits);
__IO_REG8_BIT(INDEX_REG,         0x52000178, __READ_WRITE, __indexreg_bits);
__IO_REG8_BIT(MAXP_REG,          0x52000180, __READ_WRITE, __maxpreg_bits);
__IO_REG8_BIT(IN_CSR1_REG,       0x52000184, __READ_WRITE, __incsr1reg_bits);
#define EP0_CSR     IN_CSR1_REG
#define EP0_CSR_bit IN_CSR1_REG_bit

__IO_REG8_BIT(IN_CSR2_REG,       0x52000188, __READ_WRITE, __incsr2reg_bits);
__IO_REG8_BIT(OUT_CSR1_REG,      0x52000190, __READ_WRITE, __outcsr1reg_bits);
__IO_REG8_BIT(OUT_CSR2_REG,      0x52000194, __READ_WRITE, __outcsr2reg_bits);
__IO_REG8_BIT(OUT_FIFO_CNT1_REG, 0x52000198, __READ      , __outfifocnt1reg_bits);
__IO_REG8_BIT(OUT_FIFO_CNT2_REG, 0x5200019c, __READ      , __outfifocnt2reg_bits);
__IO_REG8_BIT(EP0_FIFO,          0x520001c0, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP1_FIFO,          0x520001c4, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP2_FIFO,          0x520001c8, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP3_FIFO,          0x520001cc, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP4_FIFO,          0x520001d0, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP1_DMA_CON,       0x52000200, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP1_DMA_UNIT,      0x52000204, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP1_DMA_FIFO,      0x52000208, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP1_DMA_TTC_L,     0x5200020c, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP1_DMA_TTC_M,     0x52000210, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP1_DMA_TTC_H,     0x52000214, __READ_WRITE, __epndmatxh_bits);

__IO_REG8_BIT(EP2_DMA_CON,       0x52000218, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP2_DMA_UNIT,      0x5200021c, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP2_DMA_FIFO,      0x52000220, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP2_DMA_TTC_L,     0x52000224, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP2_DMA_TTC_M,     0x52000228, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP2_DMA_TTC_H,     0x5200022c, __READ_WRITE, __epndmatxh_bits);

__IO_REG8_BIT(EP3_DMA_CON,       0x52000240, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP3_DMA_UNIT,      0x52000244, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP3_DMA_FIFO,      0x52000248, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP3_DMA_TTC_L,     0x5200024c, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP3_DMA_TTC_M,     0x52000250, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP3_DMA_TTC_H,     0x52000254, __READ_WRITE, __epndmatxh_bits);

__IO_REG8_BIT(EP4_DMA_CON,       0x52000258, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP4_DMA_UNIT,      0x5200025c, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP4_DMA_FIFO,      0x52000260, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP4_DMA_TTC_L,     0x52000264, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP4_DMA_TTC_M,     0x52000268, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP4_DMA_TTC_H,     0x5200026c, __READ_WRITE, __epndmatxh_bits);

#else /* __LITTLE_ENDIAN__ */
__IO_REG8_BIT(FUNC_ADDR_REG,     0x52000143, __READ_WRITE, __funcaddrreg_bits);
__IO_REG8_BIT(PWR_REG,           0x52000147, __READ_WRITE, __pwraddr_bits);
__IO_REG8_BIT(EP_INT_REG,        0x5200014b, __READ_WRITE, __epintreg_bits);
__IO_REG8_BIT(USB_INT_REG,       0x5200015b, __READ_WRITE, __usbintreg_bits);
__IO_REG8_BIT(EP_INT_EN_REG,     0x5200015f, __READ_WRITE, __epintenreg_bits);
__IO_REG8_BIT(USB_INT_EN_REG,    0x5200016f, __READ_WRITE, __usbintenreg_bits);
__IO_REG8_BIT(FRAME_NUM1_REG,    0x52000173, __READ,       __framenum1reg_bits);
__IO_REG8_BIT(FRAME_NUM2_REG,    0x52000177, __READ,       __framenum2reg_bits);
__IO_REG8_BIT(INDEX_REG,         0x5200017b, __READ_WRITE, __indexreg_bits);
__IO_REG8_BIT(MAXP_REG,          0x52000183, __READ_WRITE, __maxpreg_bits);
__IO_REG8_BIT(IN_CSR1_REG,       0x52000187, __READ_WRITE, __incsr1reg_bits);
#define EP0_CSR     IN_CSR1_REG
#define EP0_CSR_bit IN_CSR1_REG_bit

__IO_REG8_BIT(IN_CSR2_REG,       0x5200018b, __READ_WRITE, __incsr2reg_bits);
__IO_REG8_BIT(OUT_CSR1_REG,      0x52000193, __READ_WRITE, __outcsr1reg_bits);
__IO_REG8_BIT(OUT_CSR2_REG,      0x52000197, __READ_WRITE, __outcsr2reg_bits);
__IO_REG8_BIT(OUT_FIFO_CNT1_REG, 0x5200019b, __READ      , __outfifocnt1reg_bits);
__IO_REG8_BIT(OUT_FIFO_CNT2_REG, 0x5200019f, __READ      , __outfifocnt2reg_bits);
__IO_REG8_BIT(EP0_FIFO,          0x520001c3, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP1_FIFO,          0x520001c7, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP2_FIFO,          0x520001cb, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP3_FIFO,          0x520001cf, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP4_FIFO,          0x520001d3, __READ_WRITE, __epnfifo_bits);
__IO_REG8_BIT(EP1_DMA_CON,       0x52000203, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP1_DMA_UNIT,      0x52000207, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP1_DMA_FIFO,      0x5200020b, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP1_DMA_TTC_L,     0x5200020f, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP1_DMA_TTC_M,     0x52000213, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP1_DMA_TTC_H,     0x52000217, __READ_WRITE, __epndmatxh_bits);

__IO_REG8_BIT(EP2_DMA_CON,       0x5200021b, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP2_DMA_UNIT,      0x5200021f, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP2_DMA_FIFO,      0x52000223, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP2_DMA_TTC_L,     0x52000227, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP2_DMA_TTC_M,     0x5200022b, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP2_DMA_TTC_H,     0x5200022f, __READ_WRITE, __epndmatxh_bits);

__IO_REG8_BIT(EP3_DMA_CON,       0x52000243, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP3_DMA_UNIT,      0x52000247, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP3_DMA_FIFO,      0x5200024b, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP3_DMA_TTC_L,     0x5200024f, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP3_DMA_TTC_M,     0x52000253, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP3_DMA_TTC_H,     0x52000257, __READ_WRITE, __epndmatxh_bits);

__IO_REG8_BIT(EP4_DMA_CON,       0x5200025b, __READ_WRITE, __epndmacon_bits);
__IO_REG8_BIT(EP4_DMA_UNIT,      0x5200025f, __READ_WRITE, __epndmaunit_bits);
__IO_REG8_BIT(EP4_DMA_FIFO,      0x52000263, __READ_WRITE, __epndmafifo_bits);
__IO_REG8_BIT(EP4_DMA_TTC_L,     0x52000267, __READ_WRITE, __epndmatxl_bits);
__IO_REG8_BIT(EP4_DMA_TTC_M,     0x5200026b, __READ_WRITE, __epndmatxm_bits);
__IO_REG8_BIT(EP4_DMA_TTC_H,     0x5200026f, __READ_WRITE, __epndmatxh_bits);

#endif /* __LITTLE_ENDIAN__ */

/***************************************************************************
 **
 **  Watchdog Timer Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(WTCON, 0x53000000, __READ_WRITE, __wtcon_bits);
__IO_REG32_BIT(WTDAT, 0x53000004, __READ_WRITE, __wtdat_bits);
__IO_REG32_BIT(WTCNT, 0x53000008, __READ_WRITE, __wtdat_bits);

/***************************************************************************
 **
 ** IIC Bus Interface Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(IICCON,  0x54000000, __READ_WRITE, __iiccon_bits);
__IO_REG32_BIT(IICSTAT, 0x54000004, __READ_WRITE, __iicstat_bits);
__IO_REG32_BIT(IICADD,  0x54000008, __READ_WRITE, __iicadd_bits);
__IO_REG32_BIT(IICDS,   0x5400000c, __READ_WRITE, __iicds_bits);
__IO_REG32_BIT(IICLC,   0x54000010, __READ_WRITE, __iiclc_bits);

/***************************************************************************
 **
 ** IIS Bus Interface Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(IISCON,  0x55000000, __READ_WRITE, __iiscon_bits);
__IO_REG32_BIT(IISMOD,  0x55000004, __READ_WRITE, __iismod_bits);
__IO_REG32_BIT(IISPSR,  0x55000008, __READ_WRITE, __iispsr_bits);
__IO_REG32_BIT(IISFCON, 0x5500000c, __READ_WRITE, __iisfcon_bits);

#if __LITTLE_ENDIAN__
__IO_REG16_BIT(IISFIFO, 0x55000010, __READ_WRITE, __iisfifo_bits);
#else /*__LITTLE_ENDIAN__ */
__IO_REG16_BIT(IISFIFO, 0x55000012, __READ_WRITE, __iisfifo_bits);
#endif /*__LITTLE_ENDIAN__ */

/***************************************************************************
 **
 ** I/O Port Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(GPACON,  0x56000000, __READ_WRITE, __gpacon_bits);
__IO_REG32_BIT(GPADAT,  0x56000004, __READ_WRITE, __gpacon_bits);

__IO_REG32_BIT(GPBCON,  0x56000010, __READ_WRITE, __gpbcon_bits);
__IO_REG32_BIT(GPBDAT,  0x56000014, __READ_WRITE, __gpbdat_bits);
__IO_REG32_BIT(GPBUP,   0x56000018, __READ_WRITE, __gpbdat_bits);

__IO_REG32_BIT(GPCCON,  0x56000020, __READ_WRITE, __gpccon_bits);
__IO_REG32_BIT(GPCDAT,  0x56000024, __READ_WRITE, __gpcdat_bits);
__IO_REG32_BIT(GPCUP,   0x56000028, __READ_WRITE, __gpcdat_bits);

__IO_REG32_BIT(GPDCON,  0x56000030, __READ_WRITE, __gpdcon_bits);
__IO_REG32_BIT(GPDDAT,  0x56000034, __READ_WRITE, __gpddat_bits);
__IO_REG32_BIT(GPDUP,   0x56000038, __READ_WRITE, __gpddat_bits);

__IO_REG32_BIT(GPECON,  0x56000040, __READ_WRITE, __gpecon_bits);
__IO_REG32_BIT(GPEDAT,  0x56000044, __READ_WRITE, __gpedat_bits);
__IO_REG32_BIT(GPEUP,   0x56000048, __READ_WRITE, __gpeup_bits);

__IO_REG32_BIT(GPFCON,  0x56000050, __READ_WRITE, __gpfcon_bits);
__IO_REG32_BIT(GPFDAT,  0x56000054, __READ_WRITE, __gpfdat_bits);
__IO_REG32_BIT(GPFUP,   0x56000058, __READ_WRITE, __gpfdat_bits);

__IO_REG32_BIT(GPGCON,  0x56000060, __READ_WRITE, __gpgcon_bits);
__IO_REG32_BIT(GPGDAT,  0x56000064, __READ_WRITE, __gpgdat_bits);
__IO_REG32_BIT(GPGUP,   0x56000068, __READ_WRITE, __gpgdat_bits);

__IO_REG32_BIT(GPHCON,  0x56000070, __READ_WRITE, __gphcon_bits);
__IO_REG32_BIT(GPHDAT,  0x56000074, __READ_WRITE, __gphdat_bits);
__IO_REG32_BIT(GPHUP,   0x56000078, __READ_WRITE, __gphdat_bits);

__IO_REG32_BIT(GPJCON,  0x560000d0, __READ_WRITE, __gpjcon_bits);
__IO_REG32_BIT(GPJDAT,  0x560000d4, __READ_WRITE, __gpjdat_bits);
__IO_REG32_BIT(GPJUP,   0x560000d8, __READ_WRITE, __gpjdat_bits);

__IO_REG32_BIT(MISCCR,  0x56000080, __READ_WRITE, __misccr_bits);
__IO_REG32_BIT(DCLKCON, 0x56000084, __READ_WRITE, __dclkcon_bits);
__IO_REG32_BIT(EXTINT0, 0x56000088, __READ_WRITE, __extint0_bits);
__IO_REG32_BIT(EXTINT1, 0x5600008c, __READ_WRITE, __extint1_bits);
__IO_REG32_BIT(EXTINT2, 0x56000090, __READ_WRITE, __extint2_bits);
__IO_REG32(   EINTFLT0,0x56000094, __READ_WRITE);
__IO_REG32(   EINTFLT1,0x56000098, __READ_WRITE);
__IO_REG32_BIT(EINTFLT2,0x5600009c, __READ_WRITE, __eintflt2_bits);
__IO_REG32_BIT(EINTFLT3,0x560000a0, __READ_WRITE, __eintflt3_bits);
__IO_REG32_BIT(EINTMASK,0x560000a4, __READ_WRITE, __eintmask_bits);
__IO_REG32_BIT(EINTPEND,0x560000a8, __READ_WRITE, __eintmask_bits);
__IO_REG32_BIT(GSTATUS0,0x560000ac, __READ,       __gstatus0_bits);
__IO_REG32_BIT(GSTATUS1,0x560000b0, __READ_WRITE, __gstatus1_bits);
__IO_REG32_BIT(GSTATUS2,0x560000b4, __READ_WRITE, __gstatus2_bits);
__IO_REG32_BIT(GSTATUS3,0x560000b8, __READ_WRITE, __gstatus34_bits);
__IO_REG32_BIT(GSTATUS4,0x560000bc, __READ_WRITE, __gstatus34_bits);
__IO_REG32_BIT(DSC0,    0x560000c4, __READ_WRITE, __dsc0_bits);
__IO_REG32_BIT(DSC1,    0x560000c8, __READ_WRITE, __dsc1_bits);
__IO_REG32_BIT(MSLCON,  0x560000cc, __READ_WRITE, __mslcon_bits);

/***************************************************************************
 **
 ** Real Time Clock (RTC) Registers
 **
 ***************************************************************************/
#if __LITTLE_ENDIAN__
__IO_REG8_BIT(RTCCON, 0x57000040, __READ_WRITE, __rtccon_bits);
__IO_REG8_BIT(TICNT,  0x57000044, __READ_WRITE, __ticnt_bits);
__IO_REG8_BIT(RTCALM, 0x57000050, __READ_WRITE, __rtcalm_bits);
__IO_REG8_BIT(ALMSEC, 0x57000054, __READ_WRITE, __almsec_bits);
__IO_REG8_BIT(ALMMIN, 0x57000058, __READ_WRITE, __almmin_bits);
__IO_REG8_BIT(ALMHOUR,0x5700005c, __READ_WRITE, __almhour_bits);
__IO_REG8_BIT(ALMDATE,0x57000060, __READ_WRITE, __almdate_bits);
__IO_REG8_BIT(ALMMON, 0x57000064, __READ_WRITE, __almmon_bits);
__IO_REG8_BIT(ALMYEAR,0x57000068, __READ_WRITE, __almyear_bits);
__IO_REG8_BIT(BCDSEC, 0x57000070, __READ_WRITE, __bcdsec_bits);
__IO_REG8_BIT(BCDMIN, 0x57000074, __READ_WRITE, __bcdmin_bits);
__IO_REG8_BIT(BCDHOUR,0x57000078, __READ_WRITE, __bcdhour_bits);
__IO_REG8_BIT(BCDDATE,0x5700007c, __READ_WRITE, __bcddate_bits);
__IO_REG8_BIT(BCDDAY, 0x57000080, __READ_WRITE, __bcdday_bits);
__IO_REG8_BIT(BCDMON, 0x57000084, __READ_WRITE, __bcdmon_bits);
__IO_REG8_BIT(BCDYEAR,0x57000088, __READ_WRITE, __bcdyear_bits);

#else  /* __LITTLE_ENDIAN__ */
__IO_REG8_BIT(RTCCON, 0x57000043, __READ_WRITE, __rtccon_bits);
__IO_REG8_BIT(TICNT,  0x57000047, __READ_WRITE, __ticnt_bits);
__IO_REG8_BIT(RTCALM, 0x57000053, __READ_WRITE, __rtcalm_bits);
__IO_REG8_BIT(ALMSEC, 0x57000057, __READ_WRITE, __almsec_bits);
__IO_REG8_BIT(ALMMIN, 0x5700005b, __READ_WRITE, __almmin_bits);
__IO_REG8_BIT(ALMHOUR,0x5700005f, __READ_WRITE, __almhour_bits);
__IO_REG8_BIT(ALMDATE,0x57000063, __READ_WRITE, __almdate_bits);
__IO_REG8_BIT(ALMMON, 0x57000067, __READ_WRITE, __almmon_bits);
__IO_REG8_BIT(ALMYEAR,0x5700006b, __READ_WRITE, __almyear_bits);
__IO_REG8_BIT(BCDSEC, 0x57000073, __READ_WRITE, __bcdsec_bits);
__IO_REG8_BIT(BCDMIN, 0x57000077, __READ_WRITE, __bcdmin_bits);
__IO_REG8_BIT(BCDHOUR,0x5700007b, __READ_WRITE, __bcdhour_bits);
__IO_REG8_BIT(BCDDATE,0x5700007f, __READ_WRITE, __bcddate_bits);
__IO_REG8_BIT(BCDDAY, 0x57000083, __READ_WRITE, __bcdday_bits);
__IO_REG8_BIT(BCDMON, 0x57000087, __READ_WRITE, __bcdmon_bits);
__IO_REG8_BIT(BCDYEAR,0x5700008b, __READ_WRITE, __bcdyear_bits);

#endif  /* __LITTLE_ENDIAN__ */

/***************************************************************************
 **
 ** A/D Converter and Touch Screen Interface Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(ADCCON,  0x58000000, __READ_WRITE, __adccon_bits);
__IO_REG32_BIT(ADCTSC,  0x58000004, __READ_WRITE, __adctsc_bits);
__IO_REG32_BIT(ADCDLY,  0x58000008, __READ_WRITE, __adcdly_bits);
__IO_REG32_BIT(ADCDAT0, 0x5800000c, __READ      , __adcdat0_bits);
__IO_REG32_BIT(ADCDAT1, 0x58000010, __READ      , __adcdat1_bits);
__IO_REG32_BIT(ADCUPDN, 0x58000014, __READ_WRITE, __adcupdn_bits);

/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(SPCON0,  0x59000000, __READ_WRITE, __spconn_bits);
__IO_REG32_BIT(SPSTA0,  0x59000004, __READ      , __spstan_bits);
__IO_REG32_BIT(SPPIN0,  0x59000008, __READ_WRITE, __sppinn_bits);
__IO_REG32_BIT(SPPRE0,  0x5900000c, __READ_WRITE, __sppren_bits);
__IO_REG32_BIT(SPTDAT0, 0x59000010, __READ_WRITE, __sptdatn_bits);
__IO_REG32_BIT(SPRDAT0, 0x59000014, __READ      , __sprdatn_bits);

__IO_REG32_BIT(SPCON1,  0x59000020, __READ_WRITE, __spconn_bits);
__IO_REG32_BIT(SPSTA1,  0x59000024, __READ      , __spstan_bits);
__IO_REG32_BIT(SPPIN1,  0x59000028, __READ_WRITE, __sppinn_bits);
__IO_REG32_BIT(SPPRE1,  0x5900002c, __READ_WRITE, __sppren_bits);
__IO_REG32_BIT(SPTDAT1, 0x59000030, __READ_WRITE, __sptdatn_bits);
__IO_REG32_BIT(SPRDAT1, 0x59000034, __READ      , __sprdatn_bits);

/***************************************************************************
 **
 ** SDI
 **
 ***************************************************************************/
__IO_REG32_BIT(SDICON,    0x5a000000, __READ_WRITE, __sdicon_bits);
__IO_REG32_BIT(SDIPRE,    0x5a000004, __READ_WRITE, __sdipre_bits);
__IO_REG32(   SDICARG,   0x5a000008, __READ_WRITE);
__IO_REG32_BIT(SDICCON,   0x5a00000c, __READ_WRITE, __sdiccon_bits);
__IO_REG32_BIT(SDICSTA,   0x5a000010, __READ_WRITE, __sdicsta_bits);
__IO_REG32(   SDIRSP0,   0x5a000014, __READ);
__IO_REG32_BIT(SDIRSP1,   0x5a000018, __READ      , __sdirsp1_bits);
__IO_REG32(   SDIRSP2,   0x5a00001c, __READ);
__IO_REG32(   SDIRSP3,   0x5a000020, __READ);
__IO_REG32_BIT(SDIDTIMER, 0x5a000024, __READ_WRITE, __sdidtimer_bits);
__IO_REG32_BIT(SDIBSIZE,  0x5a000028, __READ_WRITE, __sdibsize_bits);
__IO_REG32_BIT(SDIDCON,   0x5a00002c, __READ_WRITE, __sdidcon_bits);
__IO_REG32_BIT(SDIDCNT,   0x5a000030, __READ      , __sdidcnt_bits);
__IO_REG32_BIT(SDIDSTA,   0x5a000034, __READ_WRITE, __sdidsta_bits);
__IO_REG32_BIT(SDIFSTA,   0x5a000038, __READ      , __sdifsta_bits);
__IO_REG32_BIT(SDIIMSK,   0x5a00003c, __READ_WRITE, __sdiimsk_bits);
__IO_REG32(   SDIDAT,    0x5a000040, __READ_WRITE);

/***************************************************************************
 **
 ** AC97 Controller Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(AC_GLBCTRL,    0x5b000000, __READ_WRITE, __acglbctrl_bits);
__IO_REG32_BIT(AC_GLBSTAT,    0x5b000004, __READ      , __acglbstat_bits);
__IO_REG32_BIT(AC_CODEC_CMD,  0x5b000008, __READ_WRITE, __accodeccmd_bits);
__IO_REG32_BIT(AC_CODEC_STAT, 0x5b00000c, __READ      , __accodeccmd_bits);
__IO_REG32_BIT(AC_PCMADDR,    0x5b000010, __READ      , __acpcmaddr_bits);
__IO_REG32_BIT(AC_MICADDR,    0x5b000014, __READ      , __acmicaddr_bits);
__IO_REG32_BIT(AC_PCMDATA,    0x5b000018, __READ_WRITE, __acpcmdata_bits);
__IO_REG32_BIT(AC_MICDATA,    0x5b00001c, __READ_WRITE, __acmicdata_bits);


/* Assembler-specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3C2440A interrupt source values
 **
 ***************************************************************************/
#define INO_EINT0         0
#define INO_EINT1         1
#define INO_EINT2         2
#define INO_EINT3         3
#define INO_EINT4_7       4
#define INO_EINT8_23      5
#define INO_INT_CAM       6
#define INO_nBATT_FLT     7
#define INO_INT_TICK      8
#define INO_INT_WDT_AC97  9
#define INO_INT_TIMER0    10
#define INO_INT_TIMER1    11
#define INO_INT_TIMER2    12
#define INO_INT_TIMER3    13
#define INO_INT_TIMER4    14
#define INO_INT_UART2     15
#define INO_INT_LDC       16
#define INO_INT_DMA0      17
#define INO_INT_DMA1      18
#define INO_INT_DMA2      19
#define INO_INT_DMA3      20
#define INO_INT_SDI       21
#define INO_INT_SPI0      22
#define INO_INT_UART1     23
#define INO_INT_NFCON     24
#define INO_INT_USBD      25
#define INO_INT_USBH      26
#define INO_INT_IIC       27
#define INO_INT_UART0     28
#define INO_INT_SPI1      29
#define INO_INT_RTC       30
#define INO_INT_ADC       31


#endif    /* __S3C2440A_H */
