/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **
 **    SHARP LH79524
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.6.2.1 $
 **
 ***************************************************************************/

#ifndef __IOLH79524_H
#define __IOLH79524_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    LH79524 PERIPHERAL MEMORY MAP
 **
 ***************************************************************************
 ***************************************************************************/

#define ADC_base        0xFFFC3000      /* ADC and Brownout Detector                          */
#define BOOT_base       0xFFFE6000      /* Boot Controller                                    */
#define CLCDC_base      0xFFFF4000      /* Color LCD Controller                               */
#define ALI_base        0xFFFE4000      /* Advanced LCD Interface                             */
#define DMA_base        0xFFFE1000      /* DMA Controller                                     */
#define EMAC_base       0xFFFC7000      /* Ethernet Medium Access Controller                  */
#define EMC_base        0xFFFF1000      /* External Memory Controller                         */
#define GPIO_base       0xFFFD9000      /* General Purpose Input/Output                       */
#define I2C_base        0xFFFC5000      /* Inter-IC bus                                       */
#define I2S_base        0xFFFC8000      /* I2S converter                                      */
#define IOCON_base      0xFFFE5000      /* I/O Configuration                                  */
#define RCPC_base       0xFFFE2000      /* Reset Clock and Power Controller                   */
#define RTC_base        0xFFFE0000      /* Real Time Clock                                    */
#define SSP_base        0xFFFC6000      /* Synchronous Serial Port                            */
#define TIMER_base      0xFFFC4000      /* Timer 0 1 2                                        */
#define UART0_base      0xFFFC0000      /* UART0                                              */
#define UART1_base      0xFFFC1000      /* UART1                                              */
#define UART2_base      0xFFFC2000      /* UART2                                              */
#define USB_base        0xFFFF5000      /* Universal Serial Bus Device                        */
#define VIC_base        0xFFFFF000      /* Vectored Interrupt Controller                      */
#define WDT_base        0xFFFE3000      /* Watchdog Timer                                     */

/***************************************************************************
 ***************************************************************************
 **
 **    LH79524 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif


typedef struct {
  __REG32 REFP            : 2;
  __REG32 INM             : 1;
  __REG32 INP             : 4;
  __REG32 SETTIME         : 9;
  __REG32                 :16;
} __adc_hw_bits;

typedef struct {
  __REG32 REFM            : 2;
  __REG32 BIASCON         :12;
  __REG32                 :18;
} __adc_lw_bits;

typedef struct {
  __REG32 CBTAG           : 4;
  __REG32                 : 2;
  __REG32 ADCOUT          :10;
  __REG32                 :16;
} __adc_rr_bits;

typedef struct {
  __REG32 FOMSK           : 1;
  __REG32 FWMSK           : 1;
  __REG32 EOSMSK          : 1;
  __REG32 PMSK            : 1;
  __REG32 BOIRQ           : 1;
  __REG32                 : 1;
  __REG32 INTEN           : 1;
  __REG32                 :25;
} __adc_im_bits;

typedef struct {
  __REG32 NOC             : 4;
  __REG32 BAT_EN          : 1;
  __REG32 REFEN           : 1;
  __REG32 PWM             : 2;
  __REG32 CLKSEL          : 3;
  __REG32                 :21;
} __adc_pc_bits;

typedef struct {
  __REG32 SSM             : 2;
  __REG32 SSB             : 1;
  __REG32 FIFOWMK         : 4;
  __REG32                 :25;
} __adc_gc_bits;

typedef struct {
  __REG32 CBTAG           : 4;
  __REG32 CBSTATE         : 4;
  __REG32 PENIRQ          : 1;
  __REG32 BRONOUT         : 1;
  __REG32                 :22;
} __adc_gs_bits;

typedef struct {
  __REG32 FOVRN_UM        : 1;
  __REG32 FWATER_UM       : 1;
  __REG32 EOS_UM          : 1;
  __REG32 PENSYNC_UM      : 1;
  __REG32 BROWNOUT_UM     : 1;
  __REG32                 :27;
} __adc_is_bits;

typedef struct {
  __REG32 FGTEWATERMRK    : 1;
  __REG32 FOVRNDET        : 1;
  __REG32 FEMPTY          : 1;
  __REG32 FFF             : 1;
  __REG32 RDPTR           : 4;
  __REG32 WRPTR           : 4;
  __REG32                 :20;
} __adc_fs_bits;

typedef struct {
  __REG16 REFP            : 2;
  __REG16 INM             : 1;
  __REG16 INP             : 4;
  __REG16 SETTIME         : 9;
} __adc_hwcb_bits;

typedef struct {
  __REG16 REFM            : 2;
  __REG16 BIASCON         :12;
  __REG16                 : 2;
} __adc_lwcb_bits;

typedef struct {
  __REG32 REFP_ID         : 2;
  __REG32 INM_ID          : 1;
  __REG32 INP_ID          : 4;
  __REG32 SETTIME_ID      : 9;
  __REG32                 :16;
} __adc_ihwctrl_bits;

typedef struct {
  __REG32 REFM_ID         : 2;
  __REG32 BIASCON_ID      :12;
  __REG32                 :18;
} __adc_ilwctrl_bits;

typedef struct {
  __REG32 FOVRNINTR       : 1;
  __REG32 FWATERINTR      : 1;
  __REG32 EOSINTR         : 1;
  __REG32 PENSYNC         : 1;
  __REG32 BROWNOUT        : 1;
  __REG32                 :27;
} __adc_mis_bits;

typedef struct {
  __REG32 EOSINTC         : 1;
  __REG32 PENIC           : 1;
  __REG32 BOIC            : 1;
  __REG32                 :29;
} __adc_ic_bits;

typedef struct {
  __REG32 PBC             : 4;
  __REG32                 :28;
} __boot_pbc_bits;

typedef struct {
  __REG32 CS1O            : 1;
  __REG32                 :31;
} __boot_cs1ov_bits;

typedef struct {
  __REG32 CS0EP           : 1;
  __REG32 CS1EP           : 1;
  __REG32 CS2EP           : 1;
  __REG32 CS3EP           : 1;
  __REG32                 :28;
} __boot_epm_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 PPL             : 6;
  __REG32 HSW             : 8;
  __REG32 HFP             : 8;
  __REG32 HBP             : 8;
} __clcdc_timing0_bits;

typedef struct {
  __REG32 LPP             :10;
  __REG32 VSW             : 6;
  __REG32 VFP             : 8;
  __REG32 VBP             : 8;
} __clcdc_timing1_bits;

typedef struct {
  __REG32 PCD_LO          : 5;
  __REG32                 : 1;
  __REG32 ACB             : 5;
  __REG32 IVS             : 1;
  __REG32 IHS             : 1;
  __REG32 IPC             : 1;
  __REG32 IOE             : 1;
  __REG32                 : 1;
  __REG32 CPL             :10;
  __REG32 BCD             : 1;
  __REG32 PCD_HI          : 5;
} __clcdc_timing2_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 LCDUPBASE       :30;
} __clcdc_upbase_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 LCDLPBASE       :30;
} __clcdc_lpbase_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 FUIEN           : 1;
  __REG32 BUIEN           : 1;
  __REG32 VCIEN           : 1;
  __REG32 MBEIEN          : 1;
  __REG32                 :27;
} __clcdc_intren_bits;

typedef struct {
  __REG32 LCDEN           : 1;
  __REG32 BPP             : 3;
  __REG32 BW              : 1;
  __REG32 TFT             : 1;
  __REG32 MONO8L          : 1;
  __REG32 DUAL            : 1;
  __REG32 BGR             : 1;
  __REG32 BEBO            : 1;
  __REG32 BEPO            : 1;
  __REG32 PWR             : 1;
  __REG32 VCI             : 2;
  __REG32                 : 2;
  __REG32 WATERMARK       : 1;
  __REG32                 :15;
} __clcdc_ctrl_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 FUI             : 1;
  __REG32 BUI             : 1;
  __REG32 VCI             : 1;
  __REG32 MBEI            : 1;
  __REG32                 :27;
} __clcdc_status_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 FUIM            : 1;
  __REG32 BUIM            : 1;
  __REG32 VCIM            : 1;
  __REG32 MBEIM           : 1;
  __REG32                 :27;
} __clcdc_interrupt_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CFUI            : 1;
  __REG32 CBUI            : 1;
  __REG32 CVCI            : 1;
  __REG32 CMBEI           : 1;
  __REG32                 :27;
} __clcdcintclr_bits;

typedef struct {
  __REG32 A0              : 1;
  __REG32 A1              : 1;
  __REG32 A2              : 1;
  __REG32 A3              : 1;
  __REG32 A4              : 1;
  __REG32 A5              : 1;
  __REG32 A6              : 1;
  __REG32 A7              : 1;
  __REG32 A8              : 1;
  __REG32 A9              : 1;
  __REG32 A10             : 1;
  __REG32 A11             : 1;
  __REG32 A12             : 1;
  __REG32 A13             : 1;
  __REG32 A14             : 1;
  __REG32 A15             : 1;
  __REG32 A16             : 1;
  __REG32 A17             : 1;
  __REG32 A18             : 1;
  __REG32 A19             : 1;
  __REG32 A20             : 1;
  __REG32 A21             : 1;
  __REG32 A22             : 1;
  __REG32 A23             : 1;
  __REG32 A24             : 1;
  __REG32 A25             : 1;
  __REG32 A26             : 1;
  __REG32 A27             : 1;
  __REG32 A28             : 1;
  __REG32 A29             : 1;
  __REG32 A30             : 1;
  __REG32 A31             : 1;
} __clcdc_pcurr_bits;

typedef struct {
  __REG32 LR              : 5;
  __REG32 LG              : 5;
  __REG32 LB              : 5;
  __REG32 LI              : 1;
  __REG32 MR              : 5;
  __REG32 MG              : 5;
  __REG32 MB              : 5;
  __REG32 MI              : 1;
} __clcdc_palette_bits;

typedef struct {
  __REG32 CR              : 1;
  __REG32                 : 3;
  __REG32 PPL             : 9;
  __REG32                 :19;
} __ali_alisetup_bits;

typedef struct {
  __REG32 SPSEN           : 1;
  __REG32 CLSEN           : 1;
  __REG32                 : 1;
  __REG32 DISP            : 1;
  __REG32 EN0             : 1;
  __REG32                 : 3;
  __REG32 MODVAL          : 1;
  __REG32 MODOVRD         : 1;
  __REG32                 :22;
} __ali_alictrl_bits;

typedef struct {
  __REG32 LPDEL           : 4;
  __REG32 REVDEL          : 4;
  __REG32 PSCLS           : 4;
  __REG32 MODDEL          : 2;
  __REG32                 :18;
} __ali_alitiming1_bits;

typedef struct {
  __REG32 PS2CLS2         : 9;
  __REG32 SPLDEL          : 7;
  __REG32                 :16;
} __ali_alitiming2_bits;

typedef struct {
  __REG32 SOURCELO        :16;
  __REG32                 :16;
} __dma_sourcelo_bits;

typedef struct {
  __REG32 SOURCEHI        :16;
  __REG32                 :16;
} __dma_sourcehi_bits;

typedef struct {
  __REG32 DESTLO          :16;
  __REG32                 :16;
} __dma_destlo_bits;

typedef struct {
  __REG32 DESTHI          :16;
  __REG32                 :16;
} __dma_desthi_bits;

typedef struct {
  __REG32 MAXCOUNT        :16;
  __REG32                 :16;
} __dma_max_bits;

typedef struct {
  __REG32 ENABLE          : 1;
  __REG32 SOINC           : 1;
  __REG32 DEINC           : 1;
  __REG32 SOSIZE          : 2;
  __REG32 SOBURST         : 2;
  __REG32 DESIZE          : 2;
  __REG32 ADMODE          : 1;
  __REG32                 : 1;
  __REG32 M2M             : 1;
  __REG32                 : 1;
  __REG32 DIR             : 1;
  __REG32                 :18;
} __dma_ctrl_bits;

typedef struct {
  __REG32 CURSHI          :16;
  __REG32                 :16;
} __dma_curshi_bits;

typedef struct {
  __REG32 CURSLO          :16;
  __REG32                 :16;
} __dma_curslo_bits;

typedef struct {
  __REG32 CURDHI          :16;
  __REG32                 :16;
} __dma_curdhi_bits;

typedef struct {
  __REG32 CURDLO          :16;
  __REG32                 :16;
} __dma_curdlo_bits;

typedef struct {
  __REG32 TERM            :16;
  __REG32                 :16;
} __dma_tcnt_bits;

typedef struct {
  __REG32 MASK0           : 1;
  __REG32 MASK1           : 1;
  __REG32 MASK2           : 1;
  __REG32 MASK3           : 1;
  __REG32 MASKE0          : 1;
  __REG32 MASKE1          : 1;
  __REG32 MASKE2          : 1;
  __REG32 MASKE3          : 1;
  __REG32                 :24;
} __dma_mask_bits;

typedef struct {
  __REG32 CLEAR0          : 1;
  __REG32 CLEAR1          : 1;
  __REG32 CLEAR2          : 1;
  __REG32 CLEAR3          : 1;
  __REG32 CLEARE0         : 1;
  __REG32 CLEARE1         : 1;
  __REG32 CLEARE2         : 1;
  __REG32 CLEARE3         : 1;
  __REG32                 :24;
} __dma_clr_bits;

typedef struct {
  __REG32 INT0            : 1;
  __REG32 INT1            : 1;
  __REG32 INT2            : 1;
  __REG32 INT3            : 1;
  __REG32 ERRORINT0       : 1;
  __REG32 ERRORINT1       : 1;
  __REG32 ERRORINT2       : 1;
  __REG32 ERRORINT3       : 1;
  __REG32 ACTIVE0         : 1;
  __REG32 ACTIVE1         : 1;
  __REG32 ACTIVE2         : 1;
  __REG32 ACTIVE3         : 1;
  __REG32                 :20;
} __dma_status_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 LOOPLOCAL       : 1;
  __REG32 RXEN            : 1;
  __REG32 TXEN            : 1;
  __REG32 MANGEEN         : 1;
  __REG32 CLRSTAT         : 1;
  __REG32 INCRSTAT        : 1;
  __REG32 WRENSTAT        : 1;
  __REG32 BACKPRESS       : 1;
  __REG32 STARTTX         : 1;
  __REG32 TXHALT          : 1;
  __REG32 TXPFRAME        : 1;
  __REG32 TXZEROQ         : 1;
  __REG32                 :19;
} __emac_netctl_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 FULLDUPLEX      : 1;
  __REG32 BITRATE         : 1;
  __REG32 JUMBOFRM        : 1;
  __REG32 CPYFRM          : 1;
  __REG32 NOBCAST         : 1;
  __REG32 MULTIHASHEN     : 1;
  __REG32 UNIHASHEN       : 1;
  __REG32 RECBYTE         : 1;
  __REG32                 : 1;
  __REG32 DIV             : 2;
  __REG32 RETRY           : 1;
  __REG32 PAUSEEN         : 1;
  __REG32 RXBUFOS         : 2;
  __REG32 LENGTHCHK       : 1;
  __REG32 DISCARDFCS      : 1;
  __REG32 ENFRM           : 1;
  __REG32 IGNORE          : 1;
  __REG32                 :12;
} __emac_netconfig_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 MDIOINSTAT      : 1;
  __REG32 PHYIDLE         : 1;
  __REG32                 :29;
} __emac_netstatus_bits;

typedef struct {
  __REG32 USEDBIT         : 1;
  __REG32 COLLISION       : 1;
  __REG32 RETRYLIMIT      : 1;
  __REG32 TXGO            : 1;
  __REG32 BUFEX           : 1;
  __REG32 TXCOMPLETE      : 1;
  __REG32 TXUNDER         : 1;
  __REG32                 :25;
} __emac_txstatus_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 RXBQP           :30;
} __emac_rxbqp_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 TXBQP           :30;
} __emac_txbqp_bits;

typedef struct {
  __REG32 BUFNOTAVAIL     : 1;
  __REG32 FRMREC          : 1;
  __REG32 RXCOVERRUN      : 1;
  __REG32                 :29;
} __emac_rxstatus_bits;

typedef struct {
  __REG32 MNGFRMSENT      : 1;
  __REG32 RXCOMP          : 1;
  __REG32 RXUSDBITRD      : 1;
  __REG32 TXUSDBITRD      : 1;
  __REG32 ETHTXBUFUR      : 1;
  __REG32 RETRYLIM        : 1;
  __REG32 TXBUFEXH        : 1;
  __REG32 TXCOMPLETE      : 1;
  __REG32                 : 2;
  __REG32 RECOVERRUN      : 1;
  __REG32 NOTOK           : 1;
  __REG32 PAUSEFRRX       : 1;
  __REG32 PAUSEZERO       : 1;
  __REG32                 :18;
} __emac_instatus_bits;

typedef struct {
  __REG32 MNGDONEIEN      : 1;
  __REG32 RXCOMPIEN       : 1;
  __REG32 RXUSEDBITIEN    : 1;
  __REG32 TXUSEDBITIEN    : 1;
  __REG32 TXBUFUNDERIEN   : 1;
  __REG32 RETRYLMTEXIEN   : 1;
  __REG32 TXBUFEXHIEN     : 1;
  __REG32 TXCOMPIEN       : 1;
  __REG32                 : 2;
  __REG32 RECOVERRUNIEN   : 1;
  __REG32 NOTOKIEN        : 1;
  __REG32 PAUSEFRRXIEN    : 1;
  __REG32 PAUSETMZEROIEN  : 1;
  __REG32                 :18;
} __emac_enable_bits;

typedef struct {
  __REG32 MNGDONEIDIS     : 1;
  __REG32 RXCOMPIDIS      : 1;
  __REG32 RXUSEDBITIDIS   : 1;
  __REG32 TXUSEDBITIDIS   : 1;
  __REG32 TXBUFUNDERIDIS  : 1;
  __REG32 RETRYLMTEXIDIS  : 1;
  __REG32 TXBUFEXHIDIS    : 1;
  __REG32 TXCOMPIDIS      : 1;
  __REG32                 : 2;
  __REG32 RECOVERRUNIDIS  : 1;
  __REG32 NOTOKIDIS       : 1;
  __REG32 PAUSEFRRXIDIS   : 1;
  __REG32 PAUSETMZEROIDIS : 1;
  __REG32                 :18;
} __emac_disable_bits;

typedef struct {
  __REG32 MNGDONEMSK      : 1;
  __REG32 RXCOMPMSK       : 1;
  __REG32 RXUSEDBITMSK    : 1;
  __REG32 TXUSEDBITMSK    : 1;
  __REG32 TXBUFUNDERMSK   : 1;
  __REG32 RETRYLMTEXMSK   : 1;
  __REG32 TXBUFEXHMSK     : 1;
  __REG32 TXCOMPMSK       : 1;
  __REG32                 : 2;
  __REG32 RECOVERRUNMSK   : 1;
  __REG32 NOTOKMSK        : 1;
  __REG32 PAUSEFRRXMSK    : 1;
  __REG32 PAUSETMZEROMSK  : 1;
  __REG32                 :18;
} __emac_mask_bits;

typedef struct {
  __REG32 PHYRDWR         :16;
  __REG32                 : 2;
  __REG32 REGADDR         : 5;
  __REG32 PHYADDR         : 5;
  __REG32 OPERATION       : 2;
  __REG32 STARTFRM        : 2;
} __emac_phymaint_bits;

typedef struct {
  __REG32 PAUSETIME       :16;
  __REG32                 :16;
} __emac_pausetime_bits;

typedef struct {
  __REG32 TXPAUSEQUAN     :16;
  __REG32                 :16;
} __emac_txpausequan_bits;

typedef struct {
  __REG32 PAUSEFRRXOK     :16;
  __REG32                 :16;
} __emac_pausefrrx_bits;

typedef struct {
  __REG32 FRMTXOK         :24;
  __REG32                 : 8;
} __emac_frmtxok_bits;

typedef struct {
  __REG32 SINGLECOL       :16;
  __REG32                 :16;
} __emac_singlecol_bits;

typedef struct {
  __REG32 MULTFRM         :16;
  __REG32                 :16;
} __emac_multfrm_bits;

typedef struct {
  __REG32 FRMRXOK         :24;
  __REG32                 : 8;
} __emac_frmrxok_bits;

typedef struct {
  __REG32 FRCHK           : 8;
  __REG32                 :24;
} __emac_frchk_bits;

typedef struct {
  __REG32 ALIGNERR        : 8;
  __REG32                 :24;
} __emac_alignerr_bits;

typedef struct {
  __REG32 DEFTXFRM        :16;
  __REG32                 :16;
} __emac_deftxfrm_bits;

typedef struct {
  __REG32 LATECOL         : 8;
  __REG32                 :24;
} __emac_latecol_bits;

typedef struct {
  __REG32 EXCCOL          : 8;
  __REG32                 :24;
} __emac_excol_bits;

typedef struct {
  __REG32 TXUNDER         : 8;
  __REG32                 :24;
} __emac_txunder_bits;

typedef struct {
  __REG32 SENSERR         : 8;
  __REG32                 :24;
} __emac_senserr_bits;

typedef struct {
  __REG32 RXRERR          :16;
  __REG32                 :16;
} __emac_rxrerr_bits;

typedef struct {
  __REG32 RXOVERR         : 8;
  __REG32                 :24;
} __emac_rxoverr_bits;

typedef struct {
  __REG32 RXSYMERR        : 8;
  __REG32                 :24;
} __emac_rxsymerr_bits;

typedef struct {
  __REG32 LENERR          : 8;
  __REG32                 :24;
} __emac_lenerr_bits;

typedef struct {
  __REG32 RXJAB           : 8;
  __REG32                 :24;
} __emac_rxjab_bits;

typedef struct {
  __REG32 UNDERFRM        : 8;
  __REG32                 :24;
} __emac_underfrm_bits;

typedef struct {
  __REG32 SQERR           : 8;
  __REG32                 :24;
} __emac_sqerr_bits;

typedef struct {
  __REG32 RXLEN           : 8;
  __REG32                 :24;
} __emac_rxlen_bits;

typedef struct {
  __REG32 TXPAUSEFM       :16;
  __REG32                 :16;
} __emac_txpausefm_bits;

typedef struct {
  __REG32 HASHBOT         :32;
} __emac_hashbot_bits;

typedef struct {
  __REG32 HASHTOP         :32;
} __emac_hashtop_bits;

typedef struct {
  __REG32 SPECAD1BOT      :32;
} __emac_specad1bot_bits;

typedef struct {
  __REG32 SPECAD1TOP      :16;
  __REG32                 :16;
} __emac_specad1top_bits;

typedef struct {
  __REG32 SPECAD2BOT      :32;
} __emac_specad2bot_bits;

typedef struct {
  __REG32 SPECAD2TOP      :16;
  __REG32                 :16;
} __emac_specad2top_bits;

typedef struct {
  __REG32 SPECAD3BOT      :32;
} __emac_specad3bot_bits;

typedef struct {
  __REG32 SPECAD3TOP      :16;
  __REG32                 :16;
} __emac_specad3top_bits;

typedef struct {
  __REG32 SPECAD4BOT      :32;
} __emac_specad4bot_bits;

typedef struct {
  __REG32 SPECAD4TOP      :16;
  __REG32                 :16;
} __emac_specad4top_bits;

typedef struct {
  __REG32 IDCHK           :16;
  __REG32                 :16;
} __emac_idchk_bits;

typedef struct {
  __REG32 ENABLE          : 1;
  __REG32                 : 1;
  __REG32 MODE            : 1;
  __REG32                 :29;
} __emc_control_bits;

typedef struct {
  __REG32 BUSY            : 1;
  __REG32 WRBUF           : 1;
  __REG32 SA              : 1;
  __REG32                 :29;
} __emc_status_bits;

typedef struct {
  __REG32                 : 8;
  __REG32 CLK             : 1;
  __REG32                 :23;
} __emc_config_bits;

typedef struct {
  __REG32 CE              : 1;
  __REG32 CS              : 1;
  __REG32 SR              : 1;
  __REG32                 : 2;
  __REG32 MEMCC           : 1;
  __REG32                 : 1;
  __REG32 INIT            : 2;
  __REG32                 : 4;
  __REG32 DP              : 1;
  __REG32                 :18;
} __emc_dynmctrl_bits;

typedef struct {
  __REG32 REFRESH         :11;
  __REG32                 :21;
} __emc_dynmref_bits;

typedef struct {
  __REG32 RDS             : 2;
  __REG32                 :30;
} __emc_dynmrcon_bits;

typedef struct {
  __REG32 tRP             : 4;
  __REG32                 :28;
} __emc_precharge_bits;

typedef struct {
  __REG32 tRAS            : 4;
  __REG32                 :28;
} __emc_dynm2pre_bits;

typedef struct {
  __REG32 tSREX           : 4;
  __REG32                 :28;
} __emc_refexit_bits;

typedef struct {
  __REG32 tAPR            : 4;
  __REG32                 :28;
} __emc_doactive_bits;

typedef struct {
  __REG32 tDAL            : 4;
  __REG32                 :28;
} __emc_diactive_bits;

typedef struct {
  __REG32 tWR             : 4;
  __REG32                 :28;
} __emc_dwrt_bits;

typedef struct {
  __REG32 tRC             : 5;
  __REG32                 :27;
} __emc_dynactcmd_bits;

typedef struct {
  __REG32 tRFC            : 5;
  __REG32                 :27;
} __emc_dynauto_bits;

typedef struct {
  __REG32 tXSR            : 5;
  __REG32                 :27;
} __emc_dynrefexit_bits;

typedef struct {
  __REG32 tRRD            : 4;
  __REG32                 :28;
} __emc_dynactiveab_bits;

typedef struct {
  __REG32 tMRD            : 4;
  __REG32                 :28;
} __emc_dynamicmrd_bits;

typedef struct {
  __REG32 WAIT            :10;
  __REG32                 :22;
} __emc_wait_bits;

typedef struct {
  __REG32                 : 3;
  __REG32 MD              : 2;
  __REG32                 : 2;
  __REG32 AM              : 6;
  __REG32                 : 1;
  __REG32 _AM             : 1;
  __REG32                 : 4;
  __REG32 B               : 1;
  __REG32 P               : 1;
  __REG32                 :11;
} __emc_dyncfg_bits;

typedef struct {
  __REG32 RAS             : 2;
  __REG32                 : 6;
  __REG32 CAS             : 2;
  __REG32                 :22;
} __emc_dynrascas_bits;

typedef struct {
  __REG32 MW              : 2;
  __REG32                 : 1;
  __REG32 PM              : 1;
  __REG32                 : 2;
  __REG32 PC              : 1;
  __REG32 BLS             : 1;
  __REG32 EW              : 1;
  __REG32                 :10;
  __REG32 B               : 1;
  __REG32 P               : 1;
  __REG32                 :11;
} __emc_sconfig_bits;

typedef struct {
  __REG32 WAITWEN         : 4;
  __REG32                 :28;
} __emc_swaitwen_bits;

typedef struct {
  __REG32 WAITOEN         : 4;
  __REG32                 :28;
} __emc_swaitoen_bits;

typedef struct {
  __REG32 WAITRD          : 5;
  __REG32                 :27;
} __emc_swaitrd_bits;

typedef struct {
  __REG32 WAITPAGE        : 5;
  __REG32                 :27;
} __emc_swaitpage_bits;

typedef struct {
  __REG32 WAITWR          : 5;
  __REG32                 :27;
} __emc_swaitwr_bits;

typedef struct {
  __REG32 BTC             : 4;
  __REG32                 :28;
} __emc_sturn_bits;

typedef struct {
  __REG32 PORT_DATA       : 8;
  __REG32                 :24;
} __gpio_pxdr_bits;

typedef struct {
  __REG32 PORT_DIRECTION  : 8;
  __REG32                 :24;
} __gpio_pxddr_bits;

typedef struct {
  __REG32 MODE            : 2;
  __REG32 I2CEN           : 1;
  __REG32 SPEED           : 1;
  __REG32 START           : 1;
  __REG32 STOP            : 1;
  __REG32 RWC             : 1;
  __REG32 SABT            : 1;
  __REG32                 :24;
} __i2c_iccon_bits;

typedef struct {
  __REG32 SLAD7           : 8;
  __REG32                 :24;
} __i2c_icsar_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 SLAD89          : 2;
  __REG32 UPPERAD         : 5;
  __REG32                 :24;
} __i2c_icusar_bits;

typedef struct {
  __REG32 DAT             : 8;
  __REG32                 :24;
} __i2c_icdata_bits;

typedef struct {
  __REG32 HCNT            : 8;
  __REG32                 :24;
} __i2c_ichcnt_bits;

typedef struct {
  __REG32 LCNT            : 8;
  __REG32                 :24;
} __i2c_iclcnt_bits;

typedef struct {
  __REG32 INTR            : 1;
  __REG32 FULL            : 1;
  __REG32                 : 1;
  __REG32 _10BITADDR      : 1;
  __REG32 IDLE            : 1;
  __REG32 TXABORT         : 1;
  __REG32 RXABORT         : 1;
  __REG32 SLAVEAD         : 1;
  __REG32                 :24;
} __i2c_icstat_bits;

typedef struct {
  __REG32 I2SEL           : 1;
  __REG32 I2SEN           : 1;
  __REG32 WSINV           : 1;
  __REG32 WSDEL           : 1;
  __REG32 CLKINV          : 1;
  __REG32 LOOP            : 1;
  __REG32                 :26;
} __i2s_ctrl_bits;

typedef struct {
  __REG32 LBM             : 1;
  __REG32 WS              : 1;
  __REG32 RXWS            : 1;
  __REG32 TXWS            : 1;
  __REG32 TFE             : 1;
  __REG32 TFF             : 1;
  __REG32 RFE             : 1;
  __REG32 RFF             : 1;
  __REG32 MS              : 1;
  __REG32                 :23;
} __i2s_stat_bits;

typedef struct {
  __REG32 RORIM           : 1;
  __REG32 RTIM            : 1;
  __REG32 RXIM            : 1;
  __REG32 TXIM            : 1;
  __REG32 TXUEM           : 1;
  __REG32 ECPEM           : 1;
  __REG32 SSPPEM          : 1;
  __REG32                 :25;
} __i2s_imsc_bits;

typedef struct {
  __REG32 RORRIS          : 1;
  __REG32 RTRIS           : 1;
  __REG32 RXRIS           : 1;
  __REG32 TXRIS           : 1;
  __REG32 TXUERIS         : 1;
  __REG32 ECPERIS         : 1;
  __REG32 SSPPERIS        : 1;
  __REG32                 :25;
} __i2s_ris_bits;

typedef struct {
  __REG32 RORMIS          : 1;
  __REG32 RTMIS           : 1;
  __REG32 RXMIS           : 1;
  __REG32 TXMIS           : 1;
  __REG32 TXUEMIS         : 1;
  __REG32 ECPEMIS         : 1;
  __REG32 SSPPEMIS        : 1;
  __REG32                 :25;
} __i2s_mis_bits;

typedef struct {
  __REG32                 : 4;
  __REG32 TXUEC           : 1;
  __REG32 ECPEC           : 1;
  __REG32 SSPPEC          : 1;
  __REG32                 :25;
} __i2s_icr_bits;

typedef struct {
  __REG32 PL0             : 2;
  __REG32 PL1             : 2;
  __REG32 PI0             : 2;
  __REG32 PI1             : 2;
  __REG32 PI2             : 2;
  __REG32                 :22;
} __iocon_ctl1_bits;

typedef struct {
  __REG32 INT4            : 2;
  __REG32                 :30;
} __iocon_ctl3_bits;

typedef struct {
  __REG32 PA2             : 2;
  __REG32 PA3             : 2;
  __REG32 PA4             : 2;
  __REG32 PA5             : 2;
  __REG32 PA6             : 2;
  __REG32 PA7             : 2;
  __REG32                 :20;
} __iocon_ctl4_bits;

typedef struct {
  __REG32 PB2             : 2;
  __REG32 PB3             : 2;
  __REG32 PB4             : 2;
  __REG32 PB5             : 2;
  __REG32 PB6             : 2;
  __REG32 PB7             : 2;
  __REG32 PA0             : 2;
  __REG32 PA1             : 2;
  __REG32                 :16;
} __iocon_ctl5_bits;

typedef struct {
  __REG32 PB0             : 2;
  __REG32 PB1             : 2;
  __REG32                 :28;
} __iocon_ctl6_bits;

typedef struct {
  __REG32 PC0             : 2;
  __REG32 PC1             : 2;
  __REG32 PC2             : 2;
  __REG32 PC3             : 2;
  __REG32 PC4             : 2;
  __REG32 PC5             : 2;
  __REG32 PC6             : 2;
  __REG32 PC7             : 2;
  __REG32                 :16;
} __iocon_ctl7_bits;

typedef struct {
  __REG32 PK5             : 2;
  __REG32 PD5             : 2;
  __REG32 PK6             : 2;
  __REG32 PD6             : 2;
  __REG32 PK7             : 2;
  __REG32 PD7             : 2;
  __REG32 PN2             : 2;
  __REG32 PN3             : 2;
  __REG32                 :16;
} __iocon_ctl10_bits;

typedef struct {
  __REG32 PD1             : 2;
  __REG32 PK1             : 2;
  __REG32 PK2             : 2;
  __REG32 PD2             : 2;
  __REG32 PK3             : 2;
  __REG32 PD3             : 2;
  __REG32 PK4             : 2;
  __REG32 PD4             : 2;
  __REG32                 :16;
} __iocon_ctl11_bits;

typedef struct {
  __REG32                 :12;
  __REG32 PD0             : 2;
  __REG32 PK0             : 2;
  __REG32                 :16;
} __iocon_ctl12_bits;

typedef struct {
  __REG32 D2              : 2;
  __REG32 D3              : 2;
  __REG32 D4              : 2;
  __REG32 D5              : 2;
  __REG32 D6              : 2;
  __REG32 D7              : 2;
  __REG32 PD0             : 2;
  __REG32 PK0             : 2;
  __REG32                 :16;
} __ioconresctl12_bits;

typedef struct {
  __REG32 D0              : 2;
  __REG32 D1              : 2;
  __REG32                 :28;
} __iocon_resctl13_bits;

typedef struct {
  __REG32 nBLE1           : 2;
  __REG32 nBLE2           : 2;
  __REG32 nBLE3           : 2;
  __REG32                 : 2;
  __REG32 nCS0            : 2;
  __REG32 nCS1            : 2;
  __REG32 nCS2            : 2;
  __REG32 nCS3            : 2;
  __REG32                 :16;
} __iocon_muxctl14_bits;

typedef struct {
  __REG32 nBLE0           : 2;
  __REG32                 :30;
} __iocon_ctl15_bits;

typedef struct {
  __REG32 SDCLK           : 2;
  __REG32                 :30;
} __iocon_resctl17_bits;

typedef struct {
  __REG32 PL5             : 2;
  __REG32 PE3             : 2;
  __REG32 PE4             : 2;
  __REG32 PL6             : 2;
  __REG32 PE5             : 2;
  __REG32 PL7             : 2;
  __REG32 PE6             : 2;
  __REG32 PE7             : 2;
  __REG32                 :16;
} __iocon_ctl19_bits;

typedef struct {
  __REG32 PF6             : 2;
  __REG32 PF7             : 2;
  __REG32 PN0             : 2;
  __REG32 PE0             : 2;
  __REG32 PN1             : 2;
  __REG32 PE1             : 2;
  __REG32 PL4             : 2;
  __REG32 PE2             : 2;
  __REG32                 :16;
} __iocon_ctl20_bits;

typedef struct {
  __REG32 PF2             : 2;
  __REG32 PF3             : 2;
  __REG32 PL2             : 2;
  __REG32 PF4             : 2;
  __REG32 PL3             : 2;
  __REG32 PF5             : 2;
  __REG32                 :20;
} __iocon_ctl21_bits;

typedef struct {
  __REG32 PG2             : 2;
  __REG32 PG3             : 2;
  __REG32 PG4             : 2;
  __REG32 PG5             : 2;
  __REG32 PG6             : 2;
  __REG32 PG7             : 2;
  __REG32 PF0             : 2;
  __REG32 PF1             : 2;
  __REG32                 :16;
} __iocon_ctl22_bits;

typedef struct {
  __REG32 PH2             : 2;
  __REG32 PH3             : 2;
  __REG32 PH4             : 2;
  __REG32 PH5             : 2;
  __REG32 PH6             : 2;
  __REG32 PH7             : 2;
  __REG32 PG0             : 2;
  __REG32 PG1             : 2;
  __REG32                 :16;
} __iocon_ctl23_bits;

typedef struct {
  __REG32 PI3             : 2;
  __REG32 PI4             : 2;
  __REG32 PI5             : 2;
  __REG32 PI6             : 2;
  __REG32 PI7             : 2;
  __REG32 PH0             : 2;
  __REG32 PH1             : 2;
  __REG32                 :18;
} __iocon_ctl24_bits;

typedef struct {
  __REG32 AN3             : 2;
  __REG32 AN4             : 2;
  __REG32 AN9             : 2;
  __REG32 AN2             : 2;
  __REG32 AN8             : 2;
  __REG32 AN5             : 2;
  __REG32 AN7             : 2;
  __REG32 AN6             : 2;
  __REG32                 :16;
} __iocon_muxctl25_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 PWRDWNSEL       : 3;
  __REG32 OUTSEL          : 2;
  __REG32                 : 2;
  __REG32 LOCK            : 1;
  __REG32                 :22;
} __rcpc_ctrl_bits;

typedef struct {
  __REG32                 : 4;
  __REG32 PARTNO          :12;
  __REG32                 :16;
} __rcpc_chipid_bits;

typedef struct {
  __REG32 REMAP           : 2;
  __REG32                 :30;
} __rcpc_remap_bits;

typedef struct {
  __REG32 SRST            :16;
  __REG32                 :16;
} __rcpc_softreset_bits;

typedef struct {
  __REG32 EXT             : 1;
  __REG32 WDTO            : 1;
  __REG32                 :30;
} __rcpc_rststatus_bits;

typedef struct {
  __REG32 EXTCLR          : 1;
  __REG32 TOCLR           : 1;
  __REG32                 :30;
} __rcpc_rststatusclr_bits;

typedef struct {
  __REG32 HDIV            : 4;
  __REG32                 :28;
} __rcpc_sysclkpre_bits;

typedef struct {
  __REG32 FDIV            : 4;
  __REG32                 :28;
} __rcpc_cpuclkpre_bits;

typedef struct {
  __REG32 U0              : 1;
  __REG32 U1              : 1;
  __REG32 U2              : 1;
  __REG32                 : 6;
  __REG32 RTC             : 1;
  __REG32                 :22;
} __rcpc_pclkctrl0_bits;

typedef struct {
  __REG32 LCD             : 1;
  __REG32 SSP             : 1;
  __REG32 ADC             : 1;
  __REG32 USB             : 1;
  __REG32                 :28;
} __rcpc_pclkctrl1_bits;

typedef struct {
  __REG32 DMA             : 1;
  __REG32 SDRAM           : 1;
  __REG32 ETHERNET        : 1;
  __REG32 USB             : 1;
  __REG32 LCD             : 1;
  __REG32                 :27;
} __rcpc_ahbclkctrl_bits;

typedef struct {
  __REG32 UART0           : 1;
  __REG32 UART1           : 1;
  __REG32 UART2           : 1;
  __REG32                 :29;
} __rcpc_pclksel0_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 SSP             : 1;
  __REG32 ADC             : 1;
  __REG32 USB             : 1;
  __REG32                 :28;
} __rcpc_pclksel1_bits;

typedef struct {
  __REG32 REVNO           :16;
  __REG32                 :16;
} __rcpc_siliconrev_bits;

typedef struct {
  __REG32 LCDDIV          : 8;
  __REG32                 :24;
} __rcpc_lcdpre_bits;

typedef struct {
  __REG32 SSPDIV          : 8;
  __REG32                 :24;
} __rcpc_ssppre_bits;

typedef struct {
  __REG32 ADCDIV          : 8;
  __REG32                 :24;
} __rcpc_adcpre_bits;

typedef struct {
  __REG32 USBDIV          : 8;
  __REG32                 :24;
} __rcpc_usbpre_bits;

typedef struct {
  __REG32 INT0            : 2;
  __REG32 INT1            : 2;
  __REG32 INT2            : 2;
  __REG32 INT3            : 2;
  __REG32 INT4            : 2;
  __REG32 INT5            : 2;
  __REG32 INT6            : 2;
  __REG32 INT7            : 2;
  __REG32                 :16;
} __rcpc_intconfig_bits;

typedef struct {
  __REG32 INT0            : 1;
  __REG32 INT1            : 1;
  __REG32 INT2            : 1;
  __REG32 INT3            : 1;
  __REG32 INT4            : 1;
  __REG32 INT5            : 1;
  __REG32 INT6            : 1;
  __REG32 INT7            : 1;
  __REG32                 :24;
} __rcpc_intclr_bits;

typedef struct {
  __REG32 CCLK            : 2;
  __REG32                 :30;
} __rcpc_coreconfig_bits;

typedef struct {
  __REG32 SYSLOOPDIV      : 6;
  __REG32 SYSPREDIV       : 6;
  __REG32 SYSFRANGE       : 1;
  __REG32                 :19;
} __rcpc_syspllcntl_bits;

typedef struct {
  __REG32 USBLOOPDIV      : 6;
  __REG32 USBPREDIV       : 6;
  __REG32 USBFRANGE       : 1;
  __REG32 USBPDN          : 1;
  __REG32                 :18;
} __rcpc_usbpllctl_bits;

typedef struct {
  __REG32 RTCDR           :32;
} __rtc_dr_bits;

typedef struct {
  __REG32 RTCMR           :32;
} __rtc_mr_bits;

typedef struct {
  __REG32 RTCLR           :32;
} __rtc_lr_bits;

typedef struct {
  __REG32 START           : 1;
  __REG32                 :31;
} __rtc_cr_bits;

typedef struct {
  __REG32 IMSC            : 1;
  __REG32                 :31;
} __rtc_imsc_bits;

typedef struct {
  __REG32 RIS             : 1;
  __REG32                 :31;
} __rtc_ris_bits;

typedef struct {
  __REG32 MIS             : 1;
  __REG32                 :31;
} __rtc_mis_bits;

typedef struct {
  __REG32 ICR             : 1;
  __REG32                 :31;
} __rtc_icr_bits;

typedef struct {
  __REG32 DSS             : 4;
  __REG32 FRF             : 2;
  __REG32 SPO             : 1;
  __REG32 SPH             : 1;
  __REG32 CPD             : 8;
  __REG32                 :16;
} __ssp_ctrl0_bits;

typedef struct {
  __REG32 LBM             : 1;
  __REG32 SSE             : 1;
  __REG32 MS              : 1;
  __REG32 SOD             : 1;
  __REG32                 :28;
} __ssp_ctrl1_bits;

typedef struct {
  __REG32 DATA            :16;
  __REG32                 :16;
} __ssp_dr_bits;

typedef struct {
  __REG32 TFE             : 1;
  __REG32 TNF             : 1;
  __REG32 RNE             : 1;
  __REG32 REFI            : 1;
  __REG32 BSY             : 1;
  __REG32                 :27;
} __ssp_sr_bits;

typedef struct {
  __REG32 DVSR            : 8;
  __REG32                 :24;
} __ssp_cpsr_bits;

typedef struct {
  __REG32 RORIM           : 1;
  __REG32 RTIM            : 1;
  __REG32 RXIM            : 1;
  __REG32 TXIM            : 1;
  __REG32                 :28;
} __ssp_imsc_bits;

typedef struct {
  __REG32 RORRIS          : 1;
  __REG32 RTRIS           : 1;
  __REG32 RXRIS           : 1;
  __REG32 TXRIS           : 1;
  __REG32                 :28;
} __ssp_ris_bits;

typedef struct {
  __REG32 RORMIS          : 1;
  __REG32 RTMIS           : 1;
  __REG32 RXMIS           : 1;
  __REG32 TXMIS           : 1;
  __REG32                 :28;
} __ssp_mis_bits;

typedef struct {
  __REG32 RORIC           : 1;
  __REG32 RTIC            : 1;
  __REG32                 :30;
} __ssp_icr_bits;

typedef struct {
  __REG32 RXDMAE          : 1;
  __REG32 TXDMAE          : 1;
  __REG32                 :30;
} __ssp_dcr_bits;

typedef struct {
  __REG32 CCL             : 1;
  __REG32 CS              : 1;
  __REG32 SEL             : 3;
  __REG32                 :27;
} __timer_ctrl0_bits;

typedef struct {
  __REG32 CAPA            : 2;
  __REG32 CAPB            : 2;
  __REG32 CAPC            : 2;
  __REG32 CAPD            : 2;
  __REG32 CAPE            : 2;
  __REG32 CMP0            : 2;
  __REG32 CMP1            : 2;
  __REG32 TC              : 1;
  __REG32 PWM             : 1;
  __REG32                 :16;
} __timer_cmp_cap_ctrl_bits;

typedef struct {
  __REG32 OVF_EN          : 1;
  __REG32 CMP0_EN         : 1;
  __REG32 CMP1_EN         : 1;
  __REG32 CAPA_EN         : 1;
  __REG32 CAPB_EN         : 1;
  __REG32 CAPC_EN         : 1;
  __REG32 CAPD_EN         : 1;
  __REG32 CAPE_EN         : 1;
  __REG32                 :24;
} __timer_inten0_bits;

typedef struct {
  __REG32 OVF_ST          : 1;
  __REG32 CMP0_ST         : 1;
  __REG32 CMP1_ST         : 1;
  __REG32 CAPA_ST         : 1;
  __REG32 CAPB_ST         : 1;
  __REG32 CAPC_ST         : 1;
  __REG32 CAPD_ST         : 1;
  __REG32 CAPE_ST         : 1;
  __REG32                 :24;
} __timer_status0_bits;

typedef struct {
  __REG32 TM0CNT          :16;
  __REG32                 :16;
} __timer_cnt0_bits;

typedef struct {
  __REG32 TM0CMP          :16;
  __REG32                 :16;
} __timer_t0cmp0_bits;

typedef struct {
  __REG32 CAPTURE0        :16;
  __REG32                 :16;
} __timer_t0cmp_bits;

typedef struct {
  __REG32 TM1CNT          :16;
  __REG32                 :16;
} __timer_cnt1_bits;

typedef struct {
  __REG32 TM1CMP          :16;
  __REG32                 :16;
} __timer_t1cmp_bits;

typedef struct {
  __REG32 CAPTURE1        :16;
  __REG32                 :16;
} __timer_t1cap_bits;

typedef struct {
  __REG32 CCL             : 1;
  __REG32 CS              : 1;
  __REG32 SEL             : 3;
  __REG32 CAPA            : 2;
  __REG32 CAPB            : 2;
  __REG32 CMP0            : 2;
  __REG32 CMP1            : 2;
  __REG32 TC              : 1;
  __REG32 PWM             : 1;
  __REG32                 :17;
} __timer_ctrl_bits;

typedef struct {
  __REG32 OVF_EN          : 1;
  __REG32 CMP0_EN         : 1;
  __REG32 CMP1_EN         : 1;
  __REG32 CAPA_EN         : 1;
  __REG32 CAPB_EN         : 1;
  __REG32                 :27;
} __timer_inten_bits;

typedef struct {
  __REG32 OVF_ST          : 1;
  __REG32 CMP0_ST         : 1;
  __REG32 CMP1_ST         : 1;
  __REG32 CAPA_ST         : 1;
  __REG32 CAPB_ST         : 1;
  __REG32                 :27;
} __timer_status_bits;

typedef struct {
  __REG32 TM2CNT          :16;
  __REG32                 :16;
} __timer_cnt2_bits;

typedef struct {
  __REG32 TM2CMP          :16;
  __REG32                 :16;
} __timer_t2cmp_bits;

typedef struct {
  __REG32 CAPTURE2        :16;
  __REG32                 :16;
} __timer_t2cap_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0IM          : 1;
  __REG32                 : 2;
  __REG32 RXIM            : 1;
  __REG32 TXIM            : 1;
  __REG32 RTIM            : 1;
  __REG32 FEIM            : 1;
  __REG32 PEARIM          : 1;
  __REG32 BEIM            : 1;
  __REG32 OEIM            : 1;
  __REG32                 :21;
} __uart0_uartimsc_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0IS          : 1;
  __REG32                 : 2;
  __REG32 RXRIS           : 1;
  __REG32 TXRIS           : 1;
  __REG32 RTRIS           : 1;
  __REG32 FERIS           : 1;
  __REG32 PEARIS          : 1;
  __REG32 BERIS           : 1;
  __REG32 OERIS           : 1;
  __REG32                 :21;
} __uart0_uartris_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0MIS         : 1;
  __REG32                 : 2;
  __REG32 RXMIS           : 1;
  __REG32 TXMIS           : 1;
  __REG32 RTMIS           : 1;
  __REG32 FEMIS           : 1;
  __REG32 PEARMIS         : 1;
  __REG32 BEMIS           : 1;
  __REG32 OEMIS           : 1;
  __REG32                 :21;
} __uart0_uartmis_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0IC          : 1;
  __REG32                 : 2;
  __REG32 RXIC            : 1;
  __REG32 TXIC            : 1;
  __REG32 RTIC            : 1;
  __REG32 FEIC            : 1;
  __REG32 PEARIC          : 1;
  __REG32 BEIC            : 1;
  __REG32 OEIC            : 1;
  __REG32                 :21;
} __uart0_uarticr_bits;

typedef struct {
  __REG32 DATA            : 8;
  __REG32 FE              : 1;
  __REG32 PEAR            : 1;
  __REG32 BE              : 1;
  __REG32 OE              : 1;
  __REG32                 :20;
} __uart_uartdr_bits;

typedef union {
  //UARTRSR
  struct{
    __REG32 FE              : 1;
    __REG32 PEAR            : 1;
    __REG32 BE              : 1;
    __REG32 OE              : 1;
    __REG32                 :28;
  };
  // UARTECR
  struct{
    __REG32 EC              : 8;
    __REG32                 :24;
  };
} __uart_uartrsr_ecr_bits;

typedef struct {
  __REG32                 : 3;
  __REG32 BUSY            : 1;
  __REG32 RXFE            : 1;
  __REG32 TXFF            : 1;
  __REG32 RXFF            : 1;
  __REG32 TXFE            : 1;
  __REG32                 :24;
} __uart_uartfr_bits;

typedef struct {
  __REG32 ILPDVSR         : 8;
  __REG32                 :24;
} __uart_uartilpr_bits;

typedef struct {
  __REG32 BAUDDIVINT      :16;
  __REG32                 :16;
} __uart_uartibrd_bits;

typedef struct {
  __REG32 FRAC            : 6;
  __REG32                 :26;
} __uart_uartfbrd_bits;

typedef struct {
  __REG32 BRK             : 1;
  __REG32 PEN             : 1;
  __REG32 EPS             : 1;
  __REG32 STP2            : 1;
  __REG32 FEN             : 1;
  __REG32 WLEN            : 2;
  __REG32 SPS             : 1;
  __REG32 ADDTX           : 1;
  __REG32 _9BIT           : 1;
  __REG32                 :22;
} __uart_uartlcr_h_bits;

typedef struct {
  __REG32 UARTEN          : 1;
  __REG32 SIREN           : 1;
  __REG32 SIRLP           : 1;
  __REG32                 : 4;
  __REG32 LBE             : 1;
  __REG32 TXE             : 1;
  __REG32 RXE             : 1;
  __REG32                 : 1;
  __REG32 RTS             : 1;
  __REG32                 : 2;
  __REG32 RTSEN           : 1;
  __REG32 CTSEN           : 1;
  __REG32                 :16;
} __uart_uartcr_bits;

typedef struct {
  __REG32 TXIFLSEL        : 3;
  __REG32 RXIFLSEL        : 3;
  __REG32                 :26;
} __uart_uartifls_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0IM          : 1;
  __REG32                 : 2;
  __REG32 RXIM            : 1;
  __REG32 TXIM            : 1;
  __REG32 RTIM            : 1;
  __REG32 FEIM            : 1;
  __REG32 PEARIM          : 1;
  __REG32 BEIM            : 1;
  __REG32 OEIM            : 1;
  __REG32                 :21;
} __uart_uartimsc_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0IS          : 1;
  __REG32                 : 2;
  __REG32 RXRIS           : 1;
  __REG32 TXRIS           : 1;
  __REG32 RTRIS           : 1;
  __REG32 FERIS           : 1;
  __REG32 PEARIS          : 1;
  __REG32 BERIS           : 1;
  __REG32 OERIS           : 1;
  __REG32                 :21;
} __uart_uartris_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0MIS         : 1;
  __REG32                 : 2;
  __REG32 RXMIS           : 1;
  __REG32 TXMIS           : 1;
  __REG32 RTMIS           : 1;
  __REG32 FEMIS           : 1;
  __REG32 PEARMIS         : 1;
  __REG32 BEMIS           : 1;
  __REG32 OEMIS           : 1;
  __REG32                 :21;
} __uart_uartmis_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 CTS0IC         : 1;
  __REG32                 : 2;
  __REG32 RXIC            : 1;
  __REG32 TXIC            : 1;
  __REG32 RTIC            : 1;
  __REG32 FEIC            : 1;
  __REG32 PEARIC          : 1;
  __REG32 BEIC            : 1;
  __REG32 OEIC            : 1;
  __REG32                 :21;
} __uart_uarticr_bits;

typedef struct {
  __REG32 RXDMAEN         : 1;
  __REG32 TXDMAEN         : 1;
  __REG32 DMAOE           : 1;
  __REG32                 :29;
} __uart_dmactrl_bits;

typedef struct {
  __REG32 FUNCTION_ADDR   : 7;
  __REG32 ADDR_UPDATE     : 1;
  __REG32                 :24;
} __usb_far_bits;

typedef struct {
  __REG32 ENABLE_SUSPEND  : 1;
  __REG32 SUSPEND_MODE    : 1;
  __REG32 UC_RESUME       : 1;
  __REG32 USB_RESET       : 1;
  __REG32                 : 3;
  __REG32 SOF_UPDATE      : 1;
  __REG32                 :24;
} __usb_pmr_bits;

typedef struct {
  __REG32 EP0IN           : 1;
  __REG32 EP1IN           : 1;
  __REG32 EP2IN           : 1;
  __REG32 EP3IN           : 1;
  __REG32                 :28;
} __usb_iir_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 EP1OUT          : 1;
  __REG32 EP2OUT          : 1;
  __REG32                 :29;
} __usb_oir_bits;

typedef struct {
  __REG32 SUSINT          : 1;
  __REG32 RESINT          : 1;
  __REG32 URINT           : 1;
  __REG32 SOF             : 1;
  __REG32                 :28;
} __usb_uir_bits;

typedef struct {
  __REG32 EP0EN           : 1;
  __REG32 EP1INEN         : 1;
  __REG32 EP2INEN         : 1;
  __REG32 EP3INEN         : 1;
  __REG32                 :28;
} __usb_iie_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 EP1OUTEN        : 1;
  __REG32 EP2OUTEN        : 1;
  __REG32                 :29;
} __usb_oie_bits;

typedef struct {
  __REG32 SUSINTEN        : 1;
  __REG32 RESINTEN        : 1;
  __REG32 URINTEN         : 1;
  __REG32 SOFINTEN        : 1;
  __REG32                 :28;
} __usb_uie_bits;

typedef struct {
  __REG32 FRAME1          : 8;
  __REG32                 :24;
} __usb_frame1_bits;

typedef struct {
  __REG32 FRAME2          : 3;
  __REG32                 :29;
} __usb_frame2_bits;

typedef struct {
  __REG32 INDEX           : 4;
  __REG32                 :28;
} __usb_index_bits;

typedef struct {
  __REG32 INMAXP          : 8;
  __REG32                 :24;
} __usb_inmaxp_bits;

typedef union {
  //INCSR1
  struct{
    __REG32 IN_PKT_RDY      : 1;
    __REG32 FIFO_NE         : 1;
    __REG32 UNDERRUN        : 1;
    __REG32 FIFO_FLUSH      : 1;
    __REG32 SEND_STALL      : 1;
    __REG32 SENT_STALL      : 1;
    __REG32 CLRTOG          : 1;
    __REG32                 :25;
  };
  //CSR0
  struct{
    __REG32 OUT_PKT_RDY     : 1;
    __REG32 IN_PKT_RDY_CSR0 : 1;
    __REG32 SENT_STALL_CSR0 : 1;
    __REG32 DATA_END        : 1;
    __REG32 SETUP_END       : 1;
    __REG32 SEND_STALL_CSR0 : 1;
    __REG32 CLR_OUT         : 1;
    __REG32 CLR_SETUP_END   : 1;
    __REG32                 :24;
  };
} __usb_csr0_incsr1_bits;

typedef struct {
  __REG32                 : 3;
  __REG32 FRC_DATA_TOG    : 1;
  __REG32 USB_DMA_EN      : 1;
  __REG32 MODE            : 1;
  __REG32 ISO             : 1;
  __REG32 AUTO_SET        : 1;
  __REG32                 :24;
} __usb_incsr2_bits;

typedef struct {
  __REG32 OUTMAXP         : 8;
  __REG32                 :24;
} __usb_outmaxp_bits;

typedef struct {
  __REG32 OUT_PKT_RDY     : 1;
  __REG32 FIFO_FULL       : 1;
  __REG32 OVERRUN         : 1;
  __REG32 DATAERROR       : 1;
  __REG32 FIFO_FLUSH      : 1;
  __REG32 SEND_STALL      : 1;
  __REG32 SENT_STALL      : 1;
  __REG32 CL_DATATOG      : 1;
  __REG32                 :24;
} __usb_outcsr1_bits;

typedef struct {
  __REG32                 : 4;
  __REG32 DMA_MODE        : 1;
  __REG32 USB_DMA_EN      : 1;
  __REG32 ISO             : 1;
  __REG32 AUTO_CLR        : 1;
  __REG32                 :24;
} __usb_outcsr2_bits;

typedef union {
  //OUTCOUNT1
  struct{
    __REG32 OUTCOUNT1       : 8;
    __REG32                 :24;
  };
  //OUTCOUNT0
  struct{
    __REG32 OUTCOUNT0       : 7;
    __REG32                 :25;
  };
} __usb_outcount_bits;

typedef struct {
  __REG32 OUTCOUNT2       : 3;
  __REG32                 :29;
} __usb_outcount2_bits;

typedef struct {
  __REG32 FIFO            : 8;
  __REG32                 :24;
} __usb_epfifo_bits;

typedef struct {
  __REG32 INTR1           : 1;
  __REG32 INTR2           : 1;
  __REG32 INTR3           : 1;
  __REG32 INTR4           : 1;
  __REG32 INTR5           : 1;
  __REG32 INTR6           : 1;
  __REG32                 :26;
} __usb_intr_bits;

typedef struct {
  __REG32 DMAEN           : 1;
  __REG32 DIRECTION       : 1;
  __REG32 DMA_MODE        : 1;
  __REG32 INTEN           : 1;
  __REG32 ENDPOINT        : 2;
  __REG32                 : 2;
  __REG32 MAX             : 7;
  __REG32 BUS_ERR         : 1;
  __REG32                 :16;
} __usb_cntl_bits;

typedef struct {
  __REG32 ADDR1           :32;
} __usb_addr1_bits;

typedef struct {
  __REG32 ADDR2           :32;
} __usb_addr2_bits;

typedef struct {
  __REG32 ADDR3           :32;
} __usb_addr3_bits;

typedef struct {
  __REG32 ADDR4           :32;
} __usb_addr4_bits;

typedef struct {
  __REG32 ADDR5           :32;
} __usb_addr5_bits;

typedef struct {
  __REG32 ADDR6           :32;
} __usb_addr6_bits;

typedef struct {
  __REG32 COUNT1          :32;
} __usb_count1_bits;

typedef struct {
  __REG32 COUNT2          :32;
} __usb_count2_bits;

typedef struct {
  __REG32 COUNT3          :32;
} __usb_count3_bits;

typedef struct {
  __REG32 COUNT4          :32;
} __usb_count4_bits;

typedef struct {
  __REG32 COUNT5          :32;
} __usb_count5_bits;

typedef struct {
  __REG32 COUNT6          :32;
} __usb_count6_bits;

typedef struct {
  __REG32 VectorAddr      :32;
} __vic_vectaddr_bits;

typedef struct {
  __REG32 DefaultVectorAddr :32;
} __vic_defvectaddr_bits;

typedef struct {
  __REG32 IntSource       : 5;
  __REG32 E               : 1;
  __REG32                 :26;
} __vic_vectctrl_bits;

typedef struct {
  __REG32                 : 6;
  __REG32 VF              : 1;
  __REG32 VI              : 1;
  __REG32                 :24;
} __vic_itop_bits;

/* VIC Interrupt bits  */
typedef struct {
  __REG32 WDTINTR              : 1;
  __REG32 SWINTR               : 1;
  __REG32 DBGCOMMRXINTR        : 1;
  __REG32 DBGCOMMTXINTR        : 1;
  __REG32 TIMER0INTR           : 1;
  __REG32 TIMER1INTR           : 1;
  __REG32 TIMER2INTR           : 1;
  __REG32 EXT0INTR             : 1;
  __REG32 EXT1INTR             : 1;
  __REG32 EXT2INTR             : 1;
  __REG32 EXT3INTR             : 1;
  __REG32 EXT4INTR             : 1;
  __REG32 EXT5INTR             : 1;
  __REG32 EXT6INTR             : 1;
  __REG32 EXT7INTR             : 1;
  __REG32 ALARMINTR            : 1;
  __REG32 ADCTSCINTR           : 1;
  __REG32 ADCBOINTR            : 1;
  __REG32 ADCPENINTR           : 1;
  __REG32 CLCDINTR             : 1;
  __REG32 DMA0INTR             : 1;
  __REG32 DMA1INTR             : 1;
  __REG32 DMA2INTR             : 1;
  __REG32 DMA3INTR             : 1;
  __REG32 SSPI2SINTR           : 1;
  __REG32 ETHERNETINTR         : 1;
  __REG32 USBINTR              : 1;
  __REG32 UART0INTR            : 1;
  __REG32 UART1INTR            : 1;
  __REG32 UART2INTR            : 1;
  __REG32 USBDMAINTR           : 1;
  __REG32 I2CINTR              : 1;
} __vic_int_bits;

typedef struct {
  __REG32 EN              : 1;
  __REG32 IF              : 1;
  __REG32                 : 1;
  __REG32 FRZ             : 1;
  __REG32 TOP             : 4;
  __REG32                 :24;
} __wdt_ctl_bits;

typedef struct {
  __REG32 RST             :16;
  __REG32                 :16;
} __wdt_rst_bits;

typedef struct {
  __REG32                 : 4;
  __REG32 IF              : 1;
  __REG32                 : 2;
  __REG32 INT             : 1;
  __REG32                 :24;
} __wdt_status_bits;

typedef struct {
  __REG32 COUNT           : 8;
  __REG32                 :24;
} __wdt_count_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler *********************************/



/***************************************************************************
 **
 **  ADC : ADC and Brownout Detector
 **
 ***************************************************************************/

__IO_REG32_BIT(HW,                   0xFFFC3000, __READ,       __adc_hw_bits             );    /* ADC High Word Register, init value = 0x00000000 */
__IO_REG32_BIT(LW,                   0xFFFC3004, __READ,       __adc_lw_bits             );    /* ADC Low Word Register, init value = 0x00000000 */
__IO_REG32_BIT(RR,                   0xFFFC3008, __READ,       __adc_rr_bits             );    /* ADC Results Register, init value = 0x00000000 */
__IO_REG32_BIT(IM,                   0xFFFC300C, __READ_WRITE, __adc_im_bits             );    /* ADC Interrupt Masking Register, init value = 0x00000000 */
__IO_REG32_BIT(_PC,                  0xFFFC3010, __READ_WRITE, __adc_pc_bits             );    /* ADC Power Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(GC,                   0xFFFC3014, __READ_WRITE, __adc_gc_bits             );    /* ADC General Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(GS,                   0xFFFC3018, __READ_WRITE, __adc_gs_bits             );    /* ADC General Status Register, init value = 0x00000210 */
__IO_REG32_BIT(IS,                   0xFFFC301C, __READ,       __adc_is_bits             );    /* ADC Interrupt Status Register, init value = 0x00000010 */
__IO_REG32_BIT(FS,                   0xFFFC3020, __READ,       __adc_fs_bits             );    /* ADC FIFO Status Register, init value = 0x00000004 */
__IO_REG16_BIT(HWCB0,                0xFFFC3024, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 0, init value = 0x00000000 */
__IO_REG16_BIT(HWCB1,                0xFFFC3028, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 1, init value = 0x00000000 */
__IO_REG16_BIT(HWCB2,                0xFFFC302C, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 2, init value = 0x00000000 */
__IO_REG16_BIT(HWCB3,                0xFFFC3030, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 3, init value = 0x00000000 */
__IO_REG16_BIT(HWCB4,                0xFFFC3034, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 4, init value = 0x00000000 */
__IO_REG16_BIT(HWCB5,                0xFFFC3038, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 5, init value = 0x00000000 */
__IO_REG16_BIT(HWCB6,                0xFFFC303C, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 6, init value = 0x00000000 */
__IO_REG16_BIT(HWCB7,                0xFFFC3040, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 7, init value = 0x00000000 */
__IO_REG16_BIT(HWCB8,                0xFFFC3044, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 8, init value = 0x00000000 */
__IO_REG16_BIT(HWCB9,                0xFFFC3048, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 9, init value = 0x00000000 */
__IO_REG16_BIT(HWCB10,               0xFFFC304C, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 10, init value = 0x00000000 */
__IO_REG16_BIT(HWCB11,               0xFFFC3050, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 11, init value = 0x00000000 */
__IO_REG16_BIT(HWCB12,               0xFFFC3054, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 12, init value = 0x00000000 */
__IO_REG16_BIT(HWCB13,               0xFFFC3058, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 13, init value = 0x00000000 */
__IO_REG16_BIT(HWCB14,               0xFFFC305C, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 14, init value = 0x00000000 */
__IO_REG16_BIT(HWCB15,               0xFFFC3060, __READ_WRITE, __adc_hwcb_bits           );    /* ADC High Word Control Bank Register 15, init value = 0x00000000 */
__IO_REG16_BIT(LWCB0,                0xFFFC3064, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 0, init value = 0x00000000 */
__IO_REG16_BIT(LWCB1,                0xFFFC3068, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 1, init value = 0x00000000 */
__IO_REG16_BIT(LWCB2,                0xFFFC306C, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 2, init value = 0x00000000 */
__IO_REG16_BIT(LWCB3,                0xFFFC3070, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 3, init value = 0x00000000 */
__IO_REG16_BIT(LWCB4,                0xFFFC3074, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 4, init value = 0x00000000 */
__IO_REG16_BIT(LWCB5,                0xFFFC3078, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 5, init value = 0x00000000 */
__IO_REG16_BIT(LWCB6,                0xFFFC307C, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 6, init value = 0x00000000 */
__IO_REG16_BIT(LWCB7,                0xFFFC3080, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 7, init value = 0x00000000 */
__IO_REG16_BIT(LWCB8,                0xFFFC3084, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 8, init value = 0x00000000 */
__IO_REG16_BIT(LWCB9,                0xFFFC3088, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 9, init value = 0x00000000 */
__IO_REG16_BIT(LWCB10,               0xFFFC308C, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 10, init value = 0x00000000 */
__IO_REG16_BIT(LWCB11,               0xFFFC3090, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 11, init value = 0x00000000 */
__IO_REG16_BIT(LWCB12,               0xFFFC3094, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 12, init value = 0x00000000 */
__IO_REG16_BIT(LWCB13,               0xFFFC3098, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 13, init value = 0x00000000 */
__IO_REG16_BIT(LWCB14,               0xFFFC309C, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 14, init value = 0x00000000 */
__IO_REG16_BIT(LWCB15,               0xFFFC30A0, __READ_WRITE, __adc_lwcb_bits           );    /* ADC Low Word Control Bank Register 15, init value = 0x00000000 */
__IO_REG32_BIT(IHWCTRL,              0xFFFC30A4, __READ_WRITE, __adc_ihwctrl_bits        );    /* ADC Idle High Word Register, init value = 0x00000000 */
__IO_REG32_BIT(ILWCTRL,              0xFFFC30A8, __READ_WRITE, __adc_ilwctrl_bits        );    /* ADC Idle Low Word Register, init value = 0x00000000 */
__IO_REG32_BIT(MIS,                  0xFFFC30AC, __READ,       __adc_mis_bits            );    /* ADC Masked Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(IC,                   0xFFFC30B0, __WRITE,      __adc_ic_bits             );    /* ADC Interrupt Clear Register, init value = 0x00000000 */


#define ADC_HW          HW
#define ADC_LW          LW
#define ADC_RR          RR
#define ADC_IM          IM
#define ADC_PC          _PC
#define ADC_GC          GC
#define ADC_GS          GS
#define ADC_IS          IS
#define ADC_FS          FS
#define ADC_HWCB0       HWCB0
#define ADC_HWCB1       HWCB1
#define ADC_HWCB2       HWCB2
#define ADC_HWCB3       HWCB3
#define ADC_HWCB4       HWCB4
#define ADC_HWCB5       HWCB5
#define ADC_HWCB6       HWCB6
#define ADC_HWCB7       HWCB7
#define ADC_HWCB8       HWCB8
#define ADC_HWCB9       HWCB9
#define ADC_HWCB10      HWCB10
#define ADC_HWCB11      HWCB11
#define ADC_HWCB12      HWCB12
#define ADC_HWCB13      HWCB13
#define ADC_HWCB14      HWCB14
#define ADC_HWCB15      HWCB15
#define ADC_LWCB0       LWCB0
#define ADC_LWCB1       LWCB1
#define ADC_LWCB2       LWCB2
#define ADC_LWCB3       LWCB3
#define ADC_LWCB4       LWCB4
#define ADC_LWCB5       LWCB5
#define ADC_LWCB6       LWCB6
#define ADC_LWCB7       LWCB7
#define ADC_LWCB8       LWCB8
#define ADC_LWCB9       LWCB9
#define ADC_LWCB10      LWCB10
#define ADC_LWCB11      LWCB11
#define ADC_LWCB12      LWCB12
#define ADC_LWCB13      LWCB13
#define ADC_LWCB14      LWCB14
#define ADC_LWCB15      LWCB15
#define ADC_IHWCTRL     IHWCTRL
#define ADC_ILWCTRL     ILWCTRL
#define ADC_MIS         MIS
#define ADC_IC          IC

#define ADC_HW_bit      HW_bit
#define ADC_LW_bit      LW_bit
#define ADC_RR_bit      RR_bit
#define ADC_IM_bit      IM_bit
#define ADC_PC_bit      _PC_bit
#define ADC_GC_bit      GC_bit
#define ADC_GS_bit      GS_bit
#define ADC_IS_bit      IS_bit
#define ADC_FS_bit      FS_bit
#define ADC_HWCB0_bit   HWCB0_bit
#define ADC_HWCB1_bit   HWCB1_bit
#define ADC_HWCB2_bit   HWCB2_bit
#define ADC_HWCB3_bit   HWCB3_bit
#define ADC_HWCB4_bit   HWCB4_bit
#define ADC_HWCB5_bit   HWCB5_bit
#define ADC_HWCB6_bit   HWCB6_bit
#define ADC_HWCB7_bit   HWCB7_bit
#define ADC_HWCB8_bit   HWCB8_bit
#define ADC_HWCB9_bit   HWCB9_bit
#define ADC_HWCB10_bit  HWCB10_bit
#define ADC_HWCB11_bit  HWCB11_bit
#define ADC_HWCB12_bit  HWCB12_bit
#define ADC_HWCB13_bit  HWCB13_bit
#define ADC_HWCB14_bit  HWCB14_bit
#define ADC_HWCB15_bit  HWCB15_bit
#define ADC_LWCB0_bit   LWCB0_bit
#define ADC_LWCB1_bit   LWCB1_bit
#define ADC_LWCB2_bit   LWCB2_bit
#define ADC_LWCB3_bit   LWCB3_bit
#define ADC_LWCB4_bit   LWCB4_bit
#define ADC_LWCB5_bit   LWCB5_bit
#define ADC_LWCB6_bit   LWCB6_bit
#define ADC_LWCB7_bit   LWCB7_bit
#define ADC_LWCB8_bit   LWCB8_bit
#define ADC_LWCB9_bit   LWCB9_bit
#define ADC_LWCB10_bit  LWCB10_bit
#define ADC_LWCB11_bit  LWCB11_bit
#define ADC_LWCB12_bit  LWCB12_bit
#define ADC_LWCB13_bit  LWCB13_bit
#define ADC_LWCB14_bit  LWCB14_bit
#define ADC_LWCB15_bit  LWCB15_bit
#define ADC_IHWCTRL_bit IHWCTRL_bit
#define ADC_ILWCTRL_bit ILWCTRL_bit
#define ADC_MIS_bit     MIS_bit
#define ADC_IC_bit      IC_bit


/***************************************************************************
 **
 **  BOOT : Boot Controller
 **
 ***************************************************************************/

__IO_REG32_BIT(PBC,                 0xFFFE6000, __READ,       __boot_pbc_bits           );    /* BOOT Power-up Boot Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(CS1OV,               0xFFFE6004, __READ_WRITE, __boot_cs1ov_bits         );    /* BOOT nCS1 Override Register, init value = 0x00000000 */
__IO_REG32_BIT(EPM,                 0xFFFE6008, __READ_WRITE, __boot_epm_bits           );    /* BOOT External Peripheral Mapping Register, init value = 0x0000000F */


/***************************************************************************
 **
 **  CLCDC : Color LCD Controller
 **
 ***************************************************************************/

__IO_REG32_BIT(TIMING0,            0xFFFF4000, __READ_WRITE, __clcdc_timing0_bits      );    /* CLCDC Horizontal Axis Timing Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMING1,            0xFFFF4004, __READ_WRITE, __clcdc_timing1_bits      );    /* CLCDC Vertical Axis Timing Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMING2,            0xFFFF4008, __READ_WRITE, __clcdc_timing2_bits      );    /* CLCDC Clock and Signal Polarity Control Register, init value = 0x00000000 */
__IO_REG32_BIT(UPBASE,             0xFFFF4010, __READ_WRITE, __clcdc_upbase_bits       );    /* CLCDC Upper Panel Frame Buffer Base Address Register, init value = 0x00000000 */
__IO_REG32_BIT(LPBASE,             0xFFFF4014, __READ_WRITE, __clcdc_lpbase_bits       );    /* CLCDC Lower Panel Frame Buffer Base Address Register, init value = 0x00000000 */
__IO_REG32_BIT(INTREN,             0xFFFF4018, __READ_WRITE, __clcdc_intren_bits       );    /* CLCDC Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(CLCDC_CTRL,         0xFFFF401C, __READ_WRITE, __clcdc_ctrl_bits         );    /* CLCDC Panel Parameters Panel Power and Control Register, init value = 0x00000000 */
__IO_REG32_BIT(CLCDC_STATUS,       0xFFFF4020, __READ,       __clcdc_status_bits       );    /* CLCDC Raw Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(INTERRUPT,          0xFFFF4024, __READ,       __clcdc_interrupt_bits    );    /* CLCDC Final Masked Interrupts Register, init value = 0x00000000 */
__IO_REG32_BIT(CLCDC_INTCLR,       0xFFFF4028, __WRITE,      __clcdcintclr_bits        );    /* CLCDC Interrupt Clear Register */
__IO_REG32_BIT(UPCURR,             0xFFFF402C, __READ,       __clcdc_pcurr_bits        );    /* CLCDC Upper Panel Frame Buffer Current Address Register, init value = 0x00000000 */
__IO_REG32_BIT(LPCURR,             0xFFFF4030, __READ,       __clcdc_pcurr_bits        );    /* CLCDC Lower Panel Frame Buffer Current Address Register, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_1_0,        0xFFFF4200, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 1 and 0, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_3_2,        0xFFFF4204, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 3 and 2, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_5_4,        0xFFFF4208, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 5 and 4, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_7_6,        0xFFFF420C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 7 and 6, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_9_8,        0xFFFF4210, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 9 and 8, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_11_10,      0xFFFF4214, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 11 and 10, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_13_12,      0xFFFF4218, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 13 and 12, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_15_14,      0xFFFF421C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 15 and 14, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_17_16,      0xFFFF4220, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 17 and 16, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_19_18,      0xFFFF4224, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 19 and 18, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_21_20,      0xFFFF4228, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 21 and 20, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_23_22,      0xFFFF422C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 23 and 22, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_25_24,      0xFFFF4230, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 25 and 24, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_27_26,      0xFFFF4234, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 27 and 26, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_29_28,      0xFFFF4238, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 29 and 28, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_31_30,      0xFFFF423C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 31 and 30, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_33_32,      0xFFFF4240, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 33 and 32, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_35_34,      0xFFFF4244, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 35 and 34, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_37_36,      0xFFFF4248, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 37 and 36, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_39_38,      0xFFFF424C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 39 and 38, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_41_40,      0xFFFF4250, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 41 and 40, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_43_42,      0xFFFF4254, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 43 and 42, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_45_44,      0xFFFF4258, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 45 and 44, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_47_46,      0xFFFF425C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 47 and 46, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_49_48,      0xFFFF4260, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 49 and 48, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_51_50,      0xFFFF4264, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 51 and 50, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_53_52,      0xFFFF4268, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 53 and 52, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_55_54,      0xFFFF426C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 55 and 54, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_57_56,      0xFFFF4270, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 57 and 56, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_59_58,      0xFFFF4274, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 59 and 58, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_61_60,      0xFFFF4278, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 61 and 60, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_63_62,      0xFFFF427C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 63 and 62, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_65_64,      0xFFFF4280, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 65 and 64, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_67_66,      0xFFFF4284, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 67 and 66, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_69_68,      0xFFFF4288, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 69 and 68, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_71_70,      0xFFFF428C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 71 and 70, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_73_72,      0xFFFF4290, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 73 and 72, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_75_74,      0xFFFF4294, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 75 and 74, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_77_76,      0xFFFF4298, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 77 and 76, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_79_78,      0xFFFF429C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 79 and 78, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_81_80,      0xFFFF42A0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 81 and 80, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_83_82,      0xFFFF42A4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 83 and 82, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_85_84,      0xFFFF42A8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 85 and 84, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_87_86,      0xFFFF42AC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 87 and 86, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_89_88,      0xFFFF42B0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 89 and 88, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_91_90,      0xFFFF42B4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 91 and 90, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_93_92,      0xFFFF42B8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 93 and 92, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_95_94,      0xFFFF42BC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 95 and 94, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_97_96,      0xFFFF42C0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 97 and 96, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_99_98,      0xFFFF42C4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 99 and 98, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_101_100,    0xFFFF42C8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 101 and 100, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_103_102,    0xFFFF42CC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 103 and 102, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_105_104,    0xFFFF42D0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 105 and 104, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_107_106,    0xFFFF42D4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 107 and 106, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_109_108,    0xFFFF42D8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 109 and 108, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_111_110,    0xFFFF42DC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 111 and 110, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_113_112,    0xFFFF42E0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 113 and 112, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_115_114,    0xFFFF42E4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 115 and 114, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_117_116,    0xFFFF42E8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 117 and 116, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_119_118,    0xFFFF42EC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 119 and 118, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_121_120,    0xFFFF42F0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 121 and 120, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_123_122,    0xFFFF42F4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 123 and 122, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_125_124,    0xFFFF42F8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 125 and 124, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_127_126,    0xFFFF42FC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 127 and 126, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_129_128,    0xFFFF4300, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 129 and 128, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_131_130,    0xFFFF4304, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 131 and 130, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_133_132,    0xFFFF4308, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 133 and 132, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_135_134,    0xFFFF430C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 135 and 134, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_137_136,    0xFFFF4310, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 137 and 136, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_139_138,    0xFFFF4314, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 139 and 138, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_141_140,    0xFFFF4318, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 141 and 140, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_143_142,    0xFFFF431C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 143 and 142, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_145_144,    0xFFFF4320, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 145 and 144, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_147_146,    0xFFFF4324, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 147 and 146, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_149_148,    0xFFFF4328, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 149 and 148, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_151_150,    0xFFFF432C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 151 and 150, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_153_152,    0xFFFF4330, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 153 and 152, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_155_154,    0xFFFF4334, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 155 and 154, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_157_156,    0xFFFF4338, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 157 and 156, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_159_158,    0xFFFF433C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 159 and 158, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_161_160,    0xFFFF4340, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 161 and 160, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_163_162,    0xFFFF4344, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 163 and 162, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_165_164,    0xFFFF4348, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 165 and 164, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_167_166,    0xFFFF434C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 167 and 166, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_169_168,    0xFFFF4350, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 169 and 168, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_171_170,    0xFFFF4354, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 171 and 170, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_173_172,    0xFFFF4358, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 173 and 172, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_175_174,    0xFFFF435C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 175 and 174, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_177_176,    0xFFFF4360, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 177 and 176, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_179_178,    0xFFFF4364, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 179 and 178, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_181_180,    0xFFFF4368, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 181 and 180, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_183_182,    0xFFFF436C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 183 and 182, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_185_184,    0xFFFF4370, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 185 and 184, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_187_186,    0xFFFF4374, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 187 and 186, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_189_188,    0xFFFF4378, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 189 and 188, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_191_190,    0xFFFF437C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 191 and 190, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_193_192,    0xFFFF4380, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 193 and 192, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_195_194,    0xFFFF4384, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 195 and 194, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_197_196,    0xFFFF4388, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 197 and 196, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_199_198,    0xFFFF438C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 199 and 198, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_201_200,    0xFFFF4390, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 201 and 200, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_203_202,    0xFFFF4394, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 203 and 202, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_205_204,    0xFFFF4398, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 205 and 204, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_207_206,    0xFFFF439C, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 207 and 206, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_209_208,    0xFFFF43A0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 209 and 208, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_211_210,    0xFFFF43A4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 211 and 210, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_213_212,    0xFFFF43A8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 213 and 212, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_215_214,    0xFFFF43AC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 215 and 214, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_217_216,    0xFFFF43B0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 217 and 216, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_219_218,    0xFFFF43B4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 219 and 218, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_221_220,    0xFFFF43B8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 221 and 220, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_223_222,    0xFFFF43BC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 223 and 222, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_225_224,    0xFFFF43C0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 225 and 224, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_227_226,    0xFFFF43C4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 227 and 226, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_229_228,    0xFFFF43C8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 229 and 228, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_231_230,    0xFFFF43CC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 231 and 230, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_233_232,    0xFFFF43D0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 233 and 232, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_235_234,    0xFFFF43D4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 235 and 234, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_237_236,    0xFFFF43D8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 237 and 236, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_239_238,    0xFFFF43DC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 239 and 238, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_241_240,    0xFFFF43E0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 241 and 240, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_243_242,    0xFFFF43E4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 243 and 242, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_245_244,    0xFFFF43E8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 245 and 244, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_247_246,    0xFFFF43EC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 247 and 246, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_249_248,    0xFFFF43F0, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 249 and 248, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_251_250,    0xFFFF43F4, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 251 and 250, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_253_252,    0xFFFF43F8, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 253 and 252, init value = 0x00000000 */
__IO_REG32_BIT(PALETTE_255_254,    0xFFFF43FC, __READ_WRITE, __clcdc_palette_bits      );    /* CLCDC PALETTE 256 × 16-bit Color Palette Register 255 and 254, init value = 0x00000000 */


/***************************************************************************
 **
 **  ALI : Advanced LCD Interface
 **
 ***************************************************************************/

__IO_REG32_BIT(ALISETUP,             0xFFFE4000, __READ_WRITE, __ali_alisetup_bits       );    /* ALI Setup Register, init value = 0x00000000 */
__IO_REG32_BIT(ALICTRL,              0xFFFE4004, __READ_WRITE, __ali_alictrl_bits        );    /* ALI Control Register, init value = 0x00000000 */
__IO_REG32_BIT(ALITIMING1,           0xFFFE4008, __READ_WRITE, __ali_alitiming1_bits     );    /* ALI Timing Register 1, init value = 0x00000000 */
__IO_REG32_BIT(ALITIMING2,           0xFFFE400C, __READ_WRITE, __ali_alitiming2_bits     );    /* ALI Timing Register 2, init value = 0x00000000 */


/***************************************************************************
 **
 **  DMA : DMA Controller
 **
 ***************************************************************************/

__IO_REG32_BIT(STREAM0_SOURCELO,     0xFFFE1000, __READ_WRITE, __dma_sourcelo_bits       );    /* DMA Data Stream 0 Source Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_SOURCEHI,     0xFFFE1004, __READ_WRITE, __dma_sourcehi_bits       );    /* DMA Data Stream 0 Source Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_DESTLO,       0xFFFE1008, __READ_WRITE, __dma_destlo_bits         );    /* DMA Data Stream 0 Destination Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_DESTHI,       0xFFFE100C, __READ_WRITE, __dma_desthi_bits         );    /* DMA Data Stream 0 Destination Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_MAX,          0xFFFE1010, __READ_WRITE, __dma_max_bits            );    /* DMA Data Stream 0 Maximum Count Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_CTRL,         0xFFFE1014, __READ_WRITE, __dma_ctrl_bits           );    /* DMA Data Stream 0 Control Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_CURSHI,       0xFFFE1018, __READ_WRITE, __dma_curshi_bits         );    /* DMA Data Stream 0 Current Source Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_CURSLO,       0xFFFE101C, __READ_WRITE, __dma_curslo_bits         );    /* DMA Data Stream 0 Current Source Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_CURDHI,       0xFFFE1020, __READ_WRITE, __dma_curdhi_bits         );    /* DMA Data Stream 0 Current Destination Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_CURDLO,       0xFFFE1024, __READ_WRITE, __dma_curdlo_bits         );    /* DMA Data Stream 0 Current Destination Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM0_TCNT,         0xFFFE1028, __READ_WRITE, __dma_tcnt_bits           );    /* DMA Data Stream 0 Terminal Count, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_SOURCELO,     0xFFFE1040, __READ_WRITE, __dma_sourcelo_bits       );    /* DMA Data Stream 1 Source Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_SOURCEHI,     0xFFFE1044, __READ_WRITE, __dma_sourcehi_bits       );    /* DMA Data Stream 1 Source Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_DESTLO,       0xFFFE1048, __READ_WRITE, __dma_destlo_bits         );    /* DMA Data Stream 1 Destination Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_DESTHI,       0xFFFE104C, __READ_WRITE, __dma_desthi_bits         );    /* DMA Data Stream 1 Destination Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_MAX,          0xFFFE1050, __READ_WRITE, __dma_max_bits            );    /* DMA Data Stream 1 Maximum Count Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_CTRL,         0xFFFE1054, __READ_WRITE, __dma_ctrl_bits           );    /* DMA Data Stream 1 Control Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_CURSHI,       0xFFFE1058, __READ_WRITE, __dma_curshi_bits         );    /* DMA Data Stream 1 Current Source Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_CURSLO,       0xFFFE105C, __READ_WRITE, __dma_curslo_bits         );    /* DMA Data Stream 1 Current Source Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_CURDHI,       0xFFFE1060, __READ_WRITE, __dma_curdhi_bits         );    /* DMA Data Stream 1 Current Destination Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_CURDLO,       0xFFFE1064, __READ_WRITE, __dma_curdlo_bits         );    /* DMA Data Stream 1 Current Destination Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM1_TCNT,         0xFFFE1068, __READ_WRITE, __dma_tcnt_bits           );    /* DMA Data Stream 1 Terminal Count, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_SOURCELO,     0xFFFE1080, __READ_WRITE, __dma_sourcelo_bits       );    /* DMA Data Stream 2 Source Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_SOURCEHI,     0xFFFE1084, __READ_WRITE, __dma_sourcehi_bits       );    /* DMA Data Stream 2 Source Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_DESTLO,       0xFFFE1088, __READ_WRITE, __dma_destlo_bits         );    /* DMA Data Stream 2 Destination Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_DESTHI,       0xFFFE108C, __READ_WRITE, __dma_desthi_bits         );    /* DMA Data Stream 2 Destination Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_MAX,          0xFFFE1090, __READ_WRITE, __dma_max_bits            );    /* DMA Data Stream 2 Maximum Count Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_CTRL,         0xFFFE1094, __READ_WRITE, __dma_ctrl_bits           );    /* DMA Data Stream 2 Control Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_CURSHI,       0xFFFE1098, __READ_WRITE, __dma_curshi_bits         );    /* DMA Data Stream 2 Current Source Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_CURSLO,       0xFFFE109C, __READ_WRITE, __dma_curslo_bits         );    /* DMA Data Stream 2 Current Source Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_CURDHI,       0xFFFE10A0, __READ_WRITE, __dma_curdhi_bits         );    /* DMA Data Stream 2 Current Destination Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_CURDLO,       0xFFFE10A4, __READ_WRITE, __dma_curdlo_bits         );    /* DMA Data Stream 2 Current Destination Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM2_TCNT,         0xFFFE10A8, __READ_WRITE, __dma_tcnt_bits           );    /* DMA Data Stream 2 Terminal Count, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_SOURCELO,     0xFFFE10C0, __READ_WRITE, __dma_sourcelo_bits       );    /* DMA Data Stream 3 Source Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_SOURCEHI,     0xFFFE10C4, __READ_WRITE, __dma_sourcehi_bits       );    /* DMA Data Stream 3 Source Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_DESTLO,       0xFFFE10C8, __READ_WRITE, __dma_destlo_bits         );    /* DMA Data Stream 3 Destination Base Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_DESTHI,       0xFFFE10CC, __READ_WRITE, __dma_desthi_bits         );    /* DMA Data Stream 3 Destination Base Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_MAX,          0xFFFE10D0, __READ_WRITE, __dma_max_bits            );    /* DMA Data Stream 3 Maximum Count Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_CTRL,         0xFFFE10D4, __READ_WRITE, __dma_ctrl_bits           );    /* DMA Data Stream 3 Control Register, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_CURSHI,       0xFFFE10D8, __READ_WRITE, __dma_curshi_bits         );    /* DMA Data Stream 3 Current Source Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_CURSLO,       0xFFFE10DC, __READ_WRITE, __dma_curslo_bits         );    /* DMA Data Stream 3 Current Source Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_CURDHI,       0xFFFE10E0, __READ_WRITE, __dma_curdhi_bits         );    /* DMA Data Stream 3 Current Destination Address Register higher 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_CURDLO,       0xFFFE10E4, __READ_WRITE, __dma_curdlo_bits         );    /* DMA Data Stream 3 Current Destination Address Register lower 16 bits, init value = 0x00000000 */
__IO_REG32_BIT(STREAM3_TCNT,         0xFFFE10E8, __READ_WRITE, __dma_tcnt_bits           );    /* DMA Data Stream 3 Terminal Count, init value = 0x00000000 */
__IO_REG32_BIT(DMA_MASK,             0xFFFE10F0, __READ_WRITE, __dma_mask_bits           );    /* DMA Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(CLR,                  0xFFFE10F4, __WRITE,      __dma_clr_bits            );    /* DMA Interrupt Clear, init value = 0x00000000 */
__IO_REG32_BIT(STATUS,               0xFFFE10F8, __READ,       __dma_status_bits         );    /* DMA Status Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  EMAC : Ethernet Medium Access Controller
 **
 ***************************************************************************/

__IO_REG32_BIT(NETCTL,              0xFFFC7000, __READ_WRITE, __emac_netctl_bits        );    /* EMAC Network Control Register, init value = 0x00000000 */
__IO_REG32_BIT(NETCONFIG,           0xFFFC7004, __READ_WRITE, __emac_netconfig_bits     );    /* EMAC Network Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(NETSTATUS,           0xFFFC7008, __READ,       __emac_netstatus_bits     );    /* EMAC Network Status Register, init value = 0x00000004 */
__IO_REG32_BIT(TXSTATUS,            0xFFFC7014, __READ_WRITE, __emac_txstatus_bits      );    /* EMAC Transmit Status Register, init value = 0x00000000 */
__IO_REG32_BIT(RXBQP,               0xFFFC7018, __READ_WRITE, __emac_rxbqp_bits         );    /* EMAC Receive Buffer Queue Pointer, init value = 0x00000000 */
__IO_REG32_BIT(TXBQP,               0xFFFC701C, __READ_WRITE, __emac_txbqp_bits         );    /* EMAC Transmit Buffer Queue Pointer, init value = 0x00000000 */
__IO_REG32_BIT(RXSTATUS,            0xFFFC7020, __READ_WRITE, __emac_rxstatus_bits      );    /* EMAC Receive Status Register, init value = 0x00000000 */
__IO_REG32_BIT(INSTATUS,            0xFFFC7024, __READ_WRITE, __emac_instatus_bits      );    /* EMAC Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(ENABLE,              0xFFFC7028, __WRITE,      __emac_enable_bits        );    /* EMAC Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(DISABLE,             0xFFFC702C, __WRITE,      __emac_disable_bits       );    /* EMAC Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(EMAC_MASK,           0xFFFC7030, __READ,       __emac_mask_bits          );    /* EMAC Interrupt Mask Register, init value = 0x00003FFF */
__IO_REG32_BIT(PHYMAINT,            0xFFFC7034, __READ_WRITE, __emac_phymaint_bits      );    /* EMAC PHY Maintenance Register, init value = 0x00000000 */
__IO_REG32_BIT(PAUSETIME,           0xFFFC7038, __READ,       __emac_pausetime_bits     );    /* EMAC Pause Time Register, init value = 0x00000000 */
__IO_REG32_BIT(TXPAUSEQUAN,         0xFFFC70BC, __READ_WRITE, __emac_txpausequan_bits   );    /* EMAC Transmit pause quantum, init value = 0x0000FFFF */
__IO_REG32_BIT(PAUSEFRRX,           0xFFFC703C, __READ_WRITE, __emac_pausefrrx_bits     );    /* EMAC Pause Frames Received, init value = 0x00000000 */
__IO_REG32_BIT(FRMTXOK,             0xFFFC7040, __READ_WRITE, __emac_frmtxok_bits       );    /* EMAC Frames Transmitted OK, init value = 0x00000000 */
__IO_REG32_BIT(SINGLECOL,           0xFFFC7044, __READ_WRITE, __emac_singlecol_bits     );    /* EMAC Single Collision Frames, init value = 0x00000000 */
__IO_REG32_BIT(MULTFRM,             0xFFFC7048, __READ_WRITE, __emac_multfrm_bits       );    /* EMAC Multiple Collision Frames, init value = 0x00000000 */
__IO_REG32_BIT(FRMRXOK,             0xFFFC704C, __READ_WRITE, __emac_frmrxok_bits       );    /* EMAC Frames Received OK, init value = 0x00000000 */
__IO_REG32_BIT(FRCHK,               0xFFFC7050, __READ_WRITE, __emac_frchk_bits         );    /* EMAC Frame Check Sequence Errors, init value = 0x00000000 */
__IO_REG32_BIT(ALIGNERR,            0xFFFC7054, __READ_WRITE, __emac_alignerr_bits      );    /* EMAC Alignment Errors, init value = 0x00000000 */
__IO_REG32_BIT(DEFTXFRM,            0xFFFC7058, __READ_WRITE, __emac_deftxfrm_bits      );    /* EMAC Deferred Transmission Frames, init value = 0x00000000 */
__IO_REG32_BIT(LATECOL,             0xFFFC705C, __READ_WRITE, __emac_latecol_bits       );    /* EMAC Late collisions, init value = 0x00000000 */
__IO_REG32_BIT(EXCOL,               0xFFFC7060, __READ_WRITE, __emac_excol_bits         );    /* EMAC Excessive collisions, init value = 0x00000000 */
__IO_REG32_BIT(TXUNDER,             0xFFFC7064, __READ_WRITE, __emac_txunder_bits       );    /* EMAC Transmit underrun errors, init value = 0x00000000 */
__IO_REG32_BIT(SENSERR,             0xFFFC7068, __READ_WRITE, __emac_senserr_bits       );    /* EMAC Carrier sense errors, init value = 0x00000000 */
__IO_REG32_BIT(RXRERR,              0xFFFC706C, __READ_WRITE, __emac_rxrerr_bits        );    /* EMAC Receive resource errors, init value = 0x00000000 */
__IO_REG32_BIT(RXOVERR,             0xFFFC7070, __READ_WRITE, __emac_rxoverr_bits       );    /* EMAC Receive overrun errors, init value = 0x00000000 */
__IO_REG32_BIT(RXSYMERR,            0xFFFC7074, __READ_WRITE, __emac_rxsymerr_bits      );    /* EMAC Receive symbol errors, init value = 0x00000000 */
__IO_REG32_BIT(LENERR,              0xFFFC7078, __READ_WRITE, __emac_lenerr_bits        );    /* EMAC Excessive length errors, init value = 0x00000000 */
__IO_REG32_BIT(RXJAB,               0xFFFC707C, __READ_WRITE, __emac_rxjab_bits         );    /* EMAC Receive jabbers, init value = 0x00000000 */
__IO_REG32_BIT(UNDERFRM,            0xFFFC7080, __READ_WRITE, __emac_underfrm_bits      );    /* EMAC Undersize frames, init value = 0x00000000 */
__IO_REG32_BIT(SQERR,               0xFFFC7084, __READ_WRITE, __emac_sqerr_bits         );    /* EMAC SQE test errors, init value = 0x00000000 */
__IO_REG32_BIT(RXLEN,               0xFFFC7088, __READ_WRITE, __emac_rxlen_bits         );    /* EMAC Received length field mismatch, init value = 0x00000000 */
__IO_REG32_BIT(TXPAUSEFM,           0xFFFC708C, __READ_WRITE, __emac_txpausefm_bits     );    /* EMAC Transmitted pause frames, init value = 0x00000000 */
__IO_REG32_BIT(HASHBOT,             0xFFFC7090, __READ_WRITE, __emac_hashbot_bits       );    /* EMAC Hash register bottom [31:0], init value = 0x00000000 */
__IO_REG32_BIT(HASHTOP,             0xFFFC7094, __READ_WRITE, __emac_hashtop_bits       );    /* EMAC Hash register top [63:32], init value = 0x00000000 */
__IO_REG32_BIT(SPECAD1BOT,          0xFFFC7098, __READ_WRITE, __emac_specad1bot_bits    );    /* EMAC Specific address 1 bottom, init value = 0x00000000 */
__IO_REG32_BIT(SPECAD1TOP,          0xFFFC709C, __READ_WRITE, __emac_specad1top_bits    );    /* EMAC Specific address 1 top, init value = 0x00000000 */
__IO_REG32_BIT(SPECAD2BOT,          0xFFFC70A0, __READ_WRITE, __emac_specad2bot_bits    );    /* EMAC Specific address 2 bottom, init value = 0x00000000 */
__IO_REG32_BIT(SPECAD2TOP,          0xFFFC70A4, __READ_WRITE, __emac_specad2top_bits    );    /* EMAC Specific address 2 top, init value = 0x00000000 */
__IO_REG32_BIT(SPECAD3BOT,          0xFFFC70A8, __READ_WRITE, __emac_specad3bot_bits    );    /* EMAC Specific address 3 bottom, init value = 0x00000000 */
__IO_REG32_BIT(SPECAD3TOP,          0xFFFC70AC, __READ_WRITE, __emac_specad3top_bits    );    /* EMAC Specific address 3 top, init value = 0x00000000 */
__IO_REG32_BIT(SPECAD4BOT,          0xFFFC70B0, __READ_WRITE, __emac_specad4bot_bits    );    /* EMAC Specific address 4 bottom, init value = 0x00000000 */
__IO_REG32_BIT(SPECAD4TOP,          0xFFFC70B4, __READ_WRITE, __emac_specad4top_bits    );    /* EMAC Specific address 4 top, init value = 0x00000000 */
__IO_REG32_BIT(IDCHK,               0xFFFC70B8, __READ_WRITE, __emac_idchk_bits         );    /* EMAC Type ID checking, init value = 0x00000000 */


/***************************************************************************
 **
 **  EMC : External Memory Controller
 **
 ***************************************************************************/

__IO_REG32_BIT(EMC_CONTROL,          0xFFFF1000, __READ_WRITE, __emc_control_bits        );    /* EMC Control Register, init value = 0x00000001 */
__IO_REG32_BIT(EMC_STATUS,           0xFFFF1004, __READ,       __emc_status_bits         );    /* EMC Status Register, init value = 0x00000005 */
__IO_REG32_BIT(EMC_CONFIG,           0xFFFF1008, __READ_WRITE, __emc_config_bits         );    /* EMC Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(DYNMCTRL,             0xFFFF1020, __READ_WRITE, __emc_dynmctrl_bits       );    /* EMC Dynamic Memory Control Register, init value = 0x00000006 */
__IO_REG32_BIT(DYNMREF,              0xFFFF1024, __READ_WRITE, __emc_dynmref_bits        );    /* EMC Dynamic Memory Refresh Timer, init value = 0x00000000 */
__IO_REG32_BIT(DYNMRCON,             0xFFFF1028, __READ_WRITE, __emc_dynmrcon_bits       );    /* EMC Dynamic Memory Read Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(PRECHARGE,            0xFFFF1030, __READ_WRITE, __emc_precharge_bits      );    /* EMC Dynamic Memory Precharge Command Period, init value = 0x0000000F */
__IO_REG32_BIT(DYNM2PRE,             0xFFFF1034, __READ_WRITE, __emc_dynm2pre_bits       );    /* EMC Dynamic Memory Active to Precharge Command Period, init value = 0x0000000F */
__IO_REG32_BIT(REFEXIT,              0xFFFF1038, __READ_WRITE, __emc_refexit_bits        );    /* EMC Dynamic Memory Self-Refresh Exit Time, init value = 0x0000000F */
__IO_REG32_BIT(DOACTIVE,             0xFFFF103C, __READ_WRITE, __emc_doactive_bits       );    /* EMC Dynamic Memory Last Data Out to Active Time, init value = 0x0000000F */
__IO_REG32_BIT(DIACTIVE,             0xFFFF1040, __READ_WRITE, __emc_diactive_bits       );    /* EMC Dynamic Memory Data-In to Active Command Time, init value = 0x0000000F */
__IO_REG32_BIT(DWRT,                 0xFFFF1044, __READ_WRITE, __emc_dwrt_bits           );    /* EMC Dynamic Memory Write Recovery Time, init value = 0x0000000F */
__IO_REG32_BIT(DYNACTCMD,            0xFFFF1048, __READ_WRITE, __emc_dynactcmd_bits      );    /* EMC Dynamic Memory Active to Active Command Period, init value = 0x0000001F */
__IO_REG32_BIT(DYNAUTO,              0xFFFF104C, __READ_WRITE, __emc_dynauto_bits        );    /* EMC Dynamic Memory Auto-Refresh Period and Auto-Refresh to Active Command Period, init value = 0x0000001F */
__IO_REG32_BIT(DYNREFEXIT,           0xFFFF1050, __READ_WRITE, __emc_dynrefexit_bits     );    /* EMC Dynamic Memory Exit Self-Refresh to Active Command Time, init value = 0x0000001F */
__IO_REG32_BIT(DYNACTIVEAB,          0xFFFF1054, __READ_WRITE, __emc_dynactiveab_bits    );    /* EMC Dynamic Memory Active Bank A to Active Bank B Time, init value = 0x0000000F */
__IO_REG32_BIT(DYNAMICMRD,           0xFFFF1058, __READ_WRITE, __emc_dynamicmrd_bits     );    /* EMC Dynamic Memory Load Mode Register to Active Command Time, init value = 0x0000000F */
__IO_REG32_BIT(WAIT,                 0xFFFF1080, __READ_WRITE, __emc_wait_bits           );    /* EMC Static Memory Extended Wait, init value = 0x00000000 */
__IO_REG32_BIT(DYNCFG0,              0xFFFF1100, __READ_WRITE, __emc_dyncfg_bits         );    /* EMC Dynamic Configuration Register for nDCS0, init value = 0x00000000 */
__IO_REG32_BIT(DYNRASCAS0,           0xFFFF1104, __READ_WRITE, __emc_dynrascas_bits      );    /* EMC Dynamic Memory RAS and CAS Delay for nDCS0, init value = 0x00000303 */
__IO_REG32_BIT(DYNCFG1,              0xFFFF1120, __READ_WRITE, __emc_dyncfg_bits         );    /* EMC Dynamic Configuration Register for nDCS1, init value = 0x00000000 */
__IO_REG32_BIT(DYNRASCAS1,           0xFFFF1124, __READ_WRITE, __emc_dynrascas_bits      );    /* EMC Dynamic Memory RAS and CAS Delay for nDCS1, init value = 0x00000303 */
__IO_REG32_BIT(SCONFIG0,             0xFFFF1200, __READ_WRITE, __emc_sconfig_bits        );    /* EMC Static Memory Configuration for nCS0, init value = 0x00000000 */
__IO_REG32_BIT(SWAITWEN0,            0xFFFF1204, __READ_WRITE, __emc_swaitwen_bits       );    /* EMC Static Memory Write Enable Delay for nCS0, init value = 0x00000000 */
__IO_REG32_BIT(SWAITOEN0,            0xFFFF1208, __READ_WRITE, __emc_swaitoen_bits       );    /* EMC Static Memory Output Enable Delay for nCS0, init value = 0x00000000 */
__IO_REG32_BIT(SWAITRD0,             0xFFFF120C, __READ_WRITE, __emc_swaitrd_bits        );    /* EMC Static Memory Read Delay for nCS0, init value = 0x0000001F */
__IO_REG32_BIT(SWAITPAGE0,           0xFFFF1210, __READ_WRITE, __emc_swaitpage_bits      );    /* EMC Static Memory Page Mode Read Delay for nCS0, init value = 0x0000001F */
__IO_REG32_BIT(SWAITWR0,             0xFFFF1214, __READ_WRITE, __emc_swaitwr_bits        );    /* EMC Static Memory Write Delay for nCS0, init value = 0x0000001F */
__IO_REG32_BIT(STURN0,               0xFFFF1218, __READ_WRITE, __emc_sturn_bits          );    /* EMC Static Memory Turn Around Delay for nCS0, init value = 0x0000000F */
__IO_REG32_BIT(SCONFIG1,             0xFFFF1220, __READ_WRITE, __emc_sconfig_bits        );    /* EMC Static Memory Configuration for nCS1, init value = 0x00000000 */
__IO_REG32_BIT(SWAITWEN1,            0xFFFF1224, __READ_WRITE, __emc_swaitwen_bits       );    /* EMC Static Memory Write Enable Delay for nCS1, init value = 0x00000000 */
__IO_REG32_BIT(SWAITOEN1,            0xFFFF1228, __READ_WRITE, __emc_swaitoen_bits       );    /* EMC Static Memory Output Enable Delay for nCS1, init value = 0x00000000 */
__IO_REG32_BIT(SWAITRD1,             0xFFFF122C, __READ_WRITE, __emc_swaitrd_bits        );    /* EMC Static Memory Read Delay for nCS1, init value = 0x0000001F */
__IO_REG32_BIT(SWAITPAGE1,           0xFFFF1230, __READ_WRITE, __emc_swaitpage_bits      );    /* EMC Static Memory Page Mode Read Delay for nCS1, init value = 0x0000001F */
__IO_REG32_BIT(SWAITWR1,             0xFFFF1234, __READ_WRITE, __emc_swaitwr_bits        );    /* EMC Static Memory Write Delay for nCS1, init value = 0x0000001F */
__IO_REG32_BIT(STURN1,               0xFFFF1238, __READ_WRITE, __emc_sturn_bits          );    /* EMC Static Memory Turn Around Delay for nCS1, init value = 0x0000000F */
__IO_REG32_BIT(SCONFIG2,             0xFFFF1240, __READ_WRITE, __emc_sconfig_bits        );    /* EMC Static Memory Configuration for nCS2, init value = 0x00000000 */
__IO_REG32_BIT(SWAITWEN2,            0xFFFF1244, __READ_WRITE, __emc_swaitwen_bits       );    /* EMC Static Memory Write Enable Delay for nCS2, init value = 0x00000000 */
__IO_REG32_BIT(SWAITOEN2,            0xFFFF1248, __READ_WRITE, __emc_swaitoen_bits       );    /* EMC Static Memory Output Enable Delay for nCS2, init value = 0x00000000 */
__IO_REG32_BIT(SWAITRD2,             0xFFFF124C, __READ_WRITE, __emc_swaitrd_bits        );    /* EMC Static Memory Read Delay for nCS2, init value = 0x0000001F */
__IO_REG32_BIT(SWAITPAGE2,           0xFFFF1250, __READ_WRITE, __emc_swaitpage_bits      );    /* EMC Static Memory Page Mode Read Delay for nCS2, init value = 0x0000001F */
__IO_REG32_BIT(SWAITWR2,             0xFFFF1254, __READ_WRITE, __emc_swaitwr_bits        );    /* EMC Static Memory Write Delay for nCS2, init value = 0x0000001F */
__IO_REG32_BIT(STURN2,               0xFFFF1258, __READ_WRITE, __emc_sturn_bits          );    /* EMC Static Memory Turn Around Delay for nCS2, init value = 0x0000000F */
__IO_REG32_BIT(SCONFIG3,             0xFFFF1260, __READ_WRITE, __emc_sconfig_bits        );    /* EMC Static Memory Configuration for nCS3, init value = 0x00000000 */
__IO_REG32_BIT(SWAITWEN3,            0xFFFF1264, __READ_WRITE, __emc_swaitwen_bits       );    /* EMC Static Memory Write Enable Delay for nCS3, init value = 0x00000000 */
__IO_REG32_BIT(SWAITOEN3,            0xFFFF1268, __READ_WRITE, __emc_swaitoen_bits       );    /* EMC Static Memory Output Enable Delay for nCS3, init value = 0x00000000 */
__IO_REG32_BIT(SWAITRD3,             0xFFFF126C, __READ_WRITE, __emc_swaitrd_bits        );    /* EMC Static Memory Read Delay for nCS3, init value = 0x0000001F */
__IO_REG32_BIT(SWAITPAGE3,           0xFFFF1270, __READ_WRITE, __emc_swaitpage_bits      );    /* EMC Static Memory Page Mode Read Delay for nCS3, init value = 0x0000001F */
__IO_REG32_BIT(SWAITWR3,             0xFFFF1274, __READ_WRITE, __emc_swaitwr_bits        );    /* EMC Static Memory Write Delay for nCS3, init value = 0x0000001F */
__IO_REG32_BIT(STURN3,               0xFFFF1278, __READ_WRITE, __emc_sturn_bits          );    /* EMC Static Memory Turn Around Delay for nCS3, init value = 0x0000000F */


/***************************************************************************
 **
 **  GPIO : General Purpose Input/Output
 **
 ***************************************************************************/

__IO_REG32_BIT(P1DRA,               0xFFFDF000, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port A Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DRC,               0xFFFDE000, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port C Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DRE,               0xFFFDD000, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port E Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DRG,               0xFFFDC000, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port G Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DRI,               0xFFFDB000, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port I Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DRK,               0xFFFDA000, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port K Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DRM,               0xFFFD9000, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port M Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DRB,               0xFFFDF004, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port B Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DRD,               0xFFFDE004, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port D Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DRF,               0xFFFDD004, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port F Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DRH,               0xFFFDC004, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port H Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DRJ,               0xFFFDB004, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port J Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DRL,               0xFFFDA004, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port L Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DRN,               0xFFFD9004, __READ_WRITE, __gpio_pxdr_bits          );    /* GPIO Port N Data Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DDRA,              0xFFFDF008, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port A Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DDRC,              0xFFFDE008, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port C Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DDRE,              0xFFFDD008, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port E Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DDRG,              0xFFFDC008, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port G Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DDRI,              0xFFFDB008, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port I Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DDRK,              0xFFFDA008, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port K Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P1DDRM,              0xFFFD9008, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port M Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DDRB,              0xFFFDF00C, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port B Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DDRD,              0xFFFDE00C, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port D Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DDRF,              0xFFFDD00C, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port F Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DDRH,              0xFFFDC00C, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port H Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DDRJ,              0xFFFDB00C, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port J Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DDRL,              0xFFFDA00C, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port L Data Direction Register, init value = 0x00000000 */
__IO_REG32_BIT(P2DDRN,              0xFFFD900C, __READ_WRITE, __gpio_pxddr_bits         );    /* GPIO Port N Data Direction Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  I2C : Inter-IC bus
 **
 ***************************************************************************/

__IO_REG32_BIT(ICCON,                0xFFFC5000, __READ_WRITE, __i2c_iccon_bits          );    /* I2C Configuration Register, init value = 0x00000008 */
__IO_REG32_BIT(ICSAR,                0xFFFC5004, __READ_WRITE, __i2c_icsar_bits          );    /* I2C Slave Address Register, init value = 0x00000000 */
__IO_REG32_BIT(ICUSAR,               0xFFFC5008, __READ_WRITE, __i2c_icusar_bits         );    /* I2C Upper Slave Address Register, init value = 0x00000000 */
__IO_REG32_BIT(ICDATA,               0xFFFC500C, __READ_WRITE, __i2c_icdata_bits         );    /* I2C Data Register, init value = 0x00000000 */
__IO_REG32_BIT(ICHCNT,               0xFFFC5010, __READ_WRITE, __i2c_ichcnt_bits         );    /* I2C Clock High Period Count Register, init value = 0x00000000 */
__IO_REG32_BIT(ICLCNT,               0xFFFC5014, __READ_WRITE, __i2c_iclcnt_bits         );    /* I2C Clock Low Period Count Register, init value = 0x00000000 */
__IO_REG32_BIT(ICSTAT,               0xFFFC501C, __READ,       __i2c_icstat_bits         );    /* I2C Status Register, init value = 0x00000010 */


/***************************************************************************
 **
 **  I2S : I2S converter
 **
 ***************************************************************************/

__IO_REG32_BIT(I2S_CTRL,                 0xFFFC8000, __READ_WRITE, __i2s_ctrl_bits           );    /* I2S Control Register, init value = 0x00000000 */
__IO_REG32_BIT(I2S_STAT,                 0xFFFC8004, __READ,       __i2s_stat_bits           );    /* I2S Status Register, init value = 0x00000052 */
__IO_REG32_BIT(I2S_IMSC,                 0xFFFC8008, __READ_WRITE, __i2s_imsc_bits           );    /* I2S Interrupt Mask Set and Clear Register., init value = 0x00000000 */
__IO_REG32_BIT(I2S_RIS,                  0xFFFC800C, __READ,       __i2s_ris_bits            );    /* I2S Raw Interrupt Status register, init value = 0x00000008 */
__IO_REG32_BIT(I2S_MIS,                  0xFFFC8010, __READ,       __i2s_mis_bits            );    /* I2S Masked Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(I2S_ICR,                  0xFFFC8014, __WRITE,      __i2s_icr_bits            );    /* I2S Interrupt Clear Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  IOCON : I/O Configuration
 **
 ***************************************************************************/

__IO_REG32_BIT(MUXCTL1,            0xFFFE5000, __READ_WRITE, __iocon_ctl1_bits         );    /* IOCON Muxing Control 1 For pins from PI2/ETHERCOL to PL0/LCDVD14, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL1,            0xFFFE5004, __READ_WRITE, __iocon_ctl1_bits         );    /* IOCON Resistor Control 1 Assignment for pins From PI2/ETHERCOL to PL0/LCDVD14, init value = 0x00000195 */
__IO_REG32_BIT(MUXCTL3,            0xFFFE5010, __READ_WRITE, __iocon_ctl3_bits         );    /* IOCON Muxing Control 3 For pin INT4/CTCLK/BATCNTL, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL3,            0xFFFE5014, __READ_WRITE, __iocon_ctl3_bits         );    /* IOCON Resistor Control 3 Assignment for pin INT4/CTCLK/BATCNTL, init value = 0x00000002 */
__IO_REG32_BIT(MUXCTL4,            0xFFFE5018, __READ_WRITE, __iocon_ctl4_bits         );    /* IOCON Muxing Control 4 For PA7/CTCAP2B/CTCMP2B/SCL to PA2/CTCAP0A/CTCMP0A, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL4,            0xFFFE501C, __READ_WRITE, __iocon_ctl4_bits         );    /* IOCON Resistor Control 4 Assignment for pins from PA7/CTCAP2B/CTCMP2B/SCL to PA2/CTCAP0A/CTCMP0A, init value = 0x00000A55 */
__IO_REG32_BIT(MUXCTL5,            0xFFFE5020, __READ_WRITE, __iocon_ctl5_bits         );    /* IOCON Muxing Control 5 For pins from PA1/INT3/UARTTX2/UARTIRTX2 to PB2/SSPFRM, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL5,            0xFFFE5024, __READ_WRITE, __iocon_ctl5_bits         );    /* IOCON Resistor Control 5 Assignment for pins from PA1/INT3/UARTTX2/UARTIRTX2 to PB2/SSPFRM, init value = 0x00005556 */
__IO_REG32_BIT(MUXCTL6,            0xFFFE5028, __READ_WRITE, __iocon_ctl6_bits         );    /* IOCON Muxing Control 6 For pins from PB1/DREQ/nUARTRTS0 to PB0/nDACK/nUARTCTS0, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL6,            0xFFFE502C, __READ_WRITE, __iocon_ctl6_bits         );    /* IOCON Resistor Control 6 Assignment for pins from PB1/DREQ/nUARTRTS0 to PB0/nDACK/nUARTCTS0, init value = 0x0000000A */
__IO_REG32_BIT(MUXCTL7,            0xFFFE5030, __READ_WRITE, __iocon_ctl7_bits         );    /* IOCON Muxing Control 7 For pins from PC7/A23 to PC0/A16, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL7,            0xFFFE5034, __READ_WRITE, __iocon_ctl7_bits         );    /* IOCON Resistor Control 7 Assignment for pins from PC7/A23 to PC0/A16, init value = 0x00005555 */
__IO_REG32_BIT(MUXCTL10,           0xFFFE5048, __READ_WRITE, __iocon_ctl10_bits        );    /* IOCON Muxing Control 10 For pins from PN3/D25 to PK5/D21, init value = 0x00005555 */
__IO_REG32_BIT(RESCTL10,           0xFFFE504C, __READ_WRITE, __iocon_ctl10_bits        );    /* IOCON Resistor Control 10 Assignment for pins from PN3/D25 to PK5/D21, init value = 0x00005555 */
__IO_REG32_BIT(MUXCTL11,           0xFFFE5050, __READ_WRITE, __iocon_ctl11_bits        );    /* IOCON Muxing Control 11 For pins from PD4/D12 to PD1/D9, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL11,           0xFFFE5054, __READ_WRITE, __iocon_ctl11_bits        );    /* IOCON Resistor Control 11 Assignment for pins from PD4/D12 to PD1/D9, init value = 0x00005555 */
__IO_REG32_BIT(MUXCTL12,           0xFFFE5058, __READ_WRITE, __iocon_ctl12_bits        );    /* IOCON Muxing Control 12 For pins from PK0/D16 to PD0/D8, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL12,           0xFFFE505C, __READ_WRITE, __ioconresctl12_bits      );    /* IOCON Resistor Control 12 Assignment for pins from PK0/D16 to D2, init value = 0x00005555 */
__IO_REG32_BIT(RESCTL13,           0xFFFE5064, __READ_WRITE, __iocon_resctl13_bits     );    /* IOCON Resistor Control 13 Assignment for pins from D1 to D0, init value = 0x00000005 */
__IO_REG32_BIT(MUXCTL14,           0xFFFE5068, __READ_WRITE, __iocon_muxctl14_bits     );    /* IOCON Muxing Control 14 For Pins Ranging From nCS3/PM3 to nBLE3/PM5, init value = 0x00000000 */
__IO_REG32_BIT(MUXCTL15,           0xFFFE5070, __READ_WRITE, __iocon_ctl15_bits        );    /* IOCON Muxing Control 15 For Pin nBLE0/PM4, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL15,           0xFFFE5074, __READ_WRITE, __iocon_ctl15_bits        );    /* IOCON Resistor Control 15 Assignment for pin nBLE0/PM4, init value = 0x00000002 */
__IO_REG32_BIT(RESCTL17,           0xFFFE5084, __READ_WRITE, __iocon_resctl17_bits     );    /* IOCON Resistor Control 17 Assignment for pin SDCLK, init value = 0x00000001 */
__IO_REG32_BIT(MUXCTL19,           0xFFFE5090, __READ_WRITE, __iocon_ctl19_bits        );    /* IOCON Muxing Control 19 For pins From PE7/nWAIT/nDEOT to PL5/D29, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL19,           0xFFFE5094, __READ_WRITE, __iocon_ctl19_bits        );    /* IOCON Resistor Control 19 Assignment for pins from PE7/nWAIT/nDEOT to PL5/D29, init value = 0x00009555 */
__IO_REG32_BIT(MUXCTL20,           0xFFFE5098, __READ_WRITE, __iocon_ctl20_bits        );    /* IOCON Muxing Control 20 For pins from PE2/LCDPS to PF6/LCDEN/LCDSPL, init value = 0x00001110 */
__IO_REG32_BIT(RESCTL20,           0xFFFE509C, __READ_WRITE, __iocon_ctl20_bits        );    /* IOCON Resistor Control 20 Assignment for pins from PE2/LCDPS to PF6/LCDEN/LCDSPL, init value = 0x00005555 */
__IO_REG32_BIT(MUXCTL21,           0xFFFE50A0, __READ_WRITE, __iocon_ctl21_bits        );    /* IOCON Muxing Control 21 For pins from PF5/LCDVD11 to PF2/LCDVD8, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL21,           0xFFFE50A4, __READ_WRITE, __iocon_ctl21_bits        );    /* IOCON Resistor Control 21 Assignment for pins from PF5/LCDVD11 to PF2/LCDVD8, init value = 0x00000555 */
__IO_REG32_BIT(MUXCTL22,           0xFFFE50A8, __READ_WRITE, __iocon_ctl22_bits        );    /* IOCON Muxing Control 22 For pins from PF1/LCDVD7 to PG2/LCDVD0, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL22,           0xFFFE50AC, __READ_WRITE, __iocon_ctl22_bits        );    /* IOCON Resistor Control 22 Assignment for pins from PF1/LCDVD7 to PG2/LCDVD0, init value = 0x00005555 */
__IO_REG32_BIT(MUXCTL23,           0xFFFE50B0, __READ_WRITE, __iocon_ctl23_bits        );    /* IOCON Muxing Control 23 For pins from PG1/ETHERTXCLK to PH2/ETHERRXCLK, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL23,           0xFFFE50B4, __READ_WRITE, __iocon_ctl23_bits        );    /* IOCON Resistor Control 23 Assignment for pins from PG1/ETHERTXCLK to PH2/ETHERRXCLK, init value = 0x00005555 */
__IO_REG32_BIT(MUXCTL24,           0xFFFE50B8, __READ_WRITE, __iocon_ctl24_bits        );    /* IOCON Muxing Control 24 For pins from PH1/ETHERRXDV to PI3/ETHERCRS, init value = 0x00000000 */
__IO_REG32_BIT(RESCTL24,           0xFFFE50BC, __READ_WRITE, __iocon_ctl24_bits        );    /* IOCON Resistor Control 24 Assignment for pins from PH1/ETHERRXDV to PI3/ETHERCRS, init value = 0x00001555 */
__IO_REG32_BIT(MUXCTL25,           0xFFFE50C0, __READ_WRITE, __iocon_muxctl25_bits     );    /* IOCON Muxing Control 25 For pins from AN6/PJ7/INT7 to AN3/LR/Y-/PJ0, init value = 0x00000000 */


/***************************************************************************
 **
 **  RCPC : Reset Clock and Power Controller
 **
 ***************************************************************************/

__IO_REG32_BIT(RCPC_CTRL,           0xFFFE2000, __READ_WRITE, __rcpc_ctrl_bits          );    /* RCPC RCPC Control Register, init value = 0x00000263 */
__IO_REG32_BIT(CHIPID,              0xFFFE2004, __READ,       __rcpc_chipid_bits        );    /* RCPC Chip Identification Register, init value = 0x00005240 */
__IO_REG32_BIT(REMAP,               0xFFFE2008, __READ_WRITE, __rcpc_remap_bits         );    /* RCPC Remap Control Register, init value = 0x00000000 */
__IO_REG32_BIT(SOFTRESET,           0xFFFE200C, __READ_WRITE, __rcpc_softreset_bits     );    /* RCPC Soft Reset Register, init value = 0x00000000 */
__IO_REG32_BIT(RSTSTATUS,           0xFFFE2010, __READ,       __rcpc_rststatus_bits     );    /* RCPC Reset Status Register, init value = 0x00000001 */
__IO_REG32_BIT(RSTSTATUSCLR,        0xFFFE2014, __WRITE,      __rcpc_rststatusclr_bits  );    /* RCPC Reset Status Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(SYSCLKPRE,           0xFFFE2018, __READ_WRITE, __rcpc_sysclkpre_bits     );    /* RCPC System Clock Prescaler Register, init value = 0x0000000F */
__IO_REG32_BIT(CPUCLKPRE,           0xFFFE201C, __READ_WRITE, __rcpc_cpuclkpre_bits     );    /* RCPC CPU Clock Prescaler Register, init value = 0x0000000F */
__IO_REG32_BIT(PCLKCTRL0,           0xFFFE2024, __READ_WRITE, __rcpc_pclkctrl0_bits     );    /* RCPC Peripheral Clock Control 0 Register, init value = 0x00000207 */
__IO_REG32_BIT(PCLKCTRL1,           0xFFFE2028, __READ_WRITE, __rcpc_pclkctrl1_bits     );    /* RCPC Peripheral Clock Control 1 Register, init value = 0x0000000F */
__IO_REG32_BIT(AHBCLKCTRL,          0xFFFE202C, __READ_WRITE, __rcpc_ahbclkctrl_bits    );    /* RCPC AHB Clock Control, init value = 0x00000000 */
__IO_REG32_BIT(PCLKSEL0,            0xFFFE2030, __READ_WRITE, __rcpc_pclksel0_bits      );    /* RCPC Peripheral Clock Select Register 0, init value = 0x00000000 */
__IO_REG32_BIT(PCLKSEL1,            0xFFFE2034, __READ_WRITE, __rcpc_pclksel1_bits      );    /* RCPC Peripheral Clock Select Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SILICONREV,          0xFFFE203C, __READ,       __rcpc_siliconrev_bits    );    /* RCPC Silicon Revision Register, init value = 0x00000002 */
__IO_REG32_BIT(LCDPRE,              0xFFFE2040, __READ_WRITE, __rcpc_lcdpre_bits        );    /* RCPC LCD Prescaler Register, init value = 0x00000000 */
__IO_REG32_BIT(SSPPRE,              0xFFFE2044, __READ_WRITE, __rcpc_ssppre_bits        );    /* RCPC SSP Prescaler Register, init value = 0x00000000 */
__IO_REG32_BIT(ADCPRE,              0xFFFE2048, __READ_WRITE, __rcpc_adcpre_bits        );    /* RCPC ADC Prescaler Register, init value = 0x00000000 */
__IO_REG32_BIT(USBPRE,              0xFFFE204C, __READ_WRITE, __rcpc_usbpre_bits        );    /* RCPC USB Prescaler Register, init value = 0x00000000 */
__IO_REG32_BIT(INTCONFIG,           0xFFFE2080, __READ_WRITE, __rcpc_intconfig_bits     );    /* RCPC External Interrupt Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(INTCLR,              0xFFFE2084, __WRITE,      __rcpc_intclr_bits        );    /* RCPC External Interrupt Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(CORECONFIG,          0xFFFE2088, __WRITE,      __rcpc_coreconfig_bits    );    /* RCPC Core Clock Configuration Register, init value = 0x00000000 */
__IO_REG32_BIT(SYSPLLCNTL,          0xFFFE20C0, __READ_WRITE, __rcpc_syspllcntl_bits    );    /* RCPC System PLL Control Register, init value = 0x00000045 */
__IO_REG32_BIT(USBPLLCTL,           0xFFFE20C4, __READ_WRITE, __rcpc_usbpllctl_bits     );    /* RCPC USB PLL Control Register, init value = 0x00002045 */


/***************************************************************************
 **
 **  RTC : Real Time Clock
 **
 ***************************************************************************/

__IO_REG32_BIT(RTC_DR,                   0xFFFE0000, __READ,       __rtc_dr_bits             );    /* RTC Data Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_MR,                   0xFFFE0004, __READ_WRITE, __rtc_mr_bits             );    /* RTC Match Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_LR,                   0xFFFE0008, __READ_WRITE, __rtc_lr_bits             );    /* RTC Load Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_CR,                   0xFFFE000C, __READ_WRITE, __rtc_cr_bits             );    /* RTC Control Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_IMSC,                 0xFFFE0010, __READ_WRITE, __rtc_imsc_bits           );    /* RTC Interrupt Mask Set and Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_RIS,                  0xFFFE0014, __READ,       __rtc_ris_bits            );    /* RTC Raw Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_MIS,                  0xFFFE0018, __READ,       __rtc_mis_bits            );    /* RTC Masked Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_ICR,                  0xFFFE001C, __WRITE,      __rtc_icr_bits            );    /* RTC Interrupt Clear Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  SSP : Synchronous Serial Port
 **
 ***************************************************************************/

__IO_REG32_BIT(SSP_CTRL0,                0xFFFC6000, __READ_WRITE, __ssp_ctrl0_bits          );    /* SSP Control Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSP_CTRL1,                0xFFFC6004, __READ_WRITE, __ssp_ctrl1_bits          );    /* SSP Control Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSP_DR,                   0xFFFC6008, __READ_WRITE, __ssp_dr_bits             );    /* SSP Data Register, init value = 0x00000000 */
__IO_REG32_BIT(SSP_SR,                   0xFFFC600C, __READ,       __ssp_sr_bits             );    /* SSP Status Register, init value = 0x00000003 */
__IO_REG32_BIT(SSP_CPSR,                 0xFFFC6010, __READ_WRITE, __ssp_cpsr_bits           );    /* SSP Clock Prescale Register, init value = 0x00000000 */
__IO_REG32_BIT(SSP_IMSC,                 0xFFFC6014, __READ_WRITE, __ssp_imsc_bits           );    /* SSP Interrupt Mask Set and Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(SSP_RIS,                  0xFFFC6018, __READ,       __ssp_ris_bits            );    /* SSP Raw Interrupt Status Register, init value = 0x00000008 */
__IO_REG32_BIT(SSP_MIS,                  0xFFFC601C, __READ,       __ssp_mis_bits            );    /* SSP Masked Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(SSP_ICR,                  0xFFFC6020, __WRITE,      __ssp_icr_bits            );    /* SSP Interrupt Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(SSP_DCR,                  0xFFFC6024, __READ_WRITE, __ssp_dcr_bits            );    /* SSP DMA Control Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  TIMER : Timer 0 1 2
 **
 ***************************************************************************/

__IO_REG32_BIT(TIMER_CTRL0,              0xFFFC4000, __READ_WRITE, __timer_ctrl0_bits        );    /* TIMER Timer 0 Control Register, init value = 0x00000000 */
__IO_REG32_BIT(CMP_CAP_CTRL,       0xFFFC4004, __READ_WRITE, __timer_cmp_cap_ctrl_bits );    /* TIMER Timer 0 Compare/Capture Control Register, init value = 0x00000000 */
__IO_REG32_BIT(INTEN0,             0xFFFC4008, __READ_WRITE, __timer_inten0_bits       );    /* TIMER Timer 0 Interrupt Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_STATUS0,            0xFFFC400C, __READ_WRITE, __timer_status0_bits      );    /* TIMER Timer 0 Status Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_CNT0,               0xFFFC4010, __READ_WRITE, __timer_cnt0_bits         );    /* TIMER Timer 0 Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(T0CMP0,             0xFFFC4014, __READ_WRITE, __timer_t0cmp0_bits       );    /* TIMER Timer 0 Compare Register 0, init value = 0x0000FFFF */
__IO_REG32_BIT(T0CMP1,             0xFFFC4018, __READ_WRITE, __timer_t0cmp_bits        );    /* TIMER Timer 0 Compare Register 1, init value = 0x00000000 */
__IO_REG32_BIT(T0CAPA,             0xFFFC401C, __READ_WRITE, __timer_t0cmp_bits        );    /* TIMER Timer 0 Capture Register A, init value = 0x00000000 */
__IO_REG32_BIT(T0CAPB,             0xFFFC4020, __READ,       __timer_t0cmp_bits        );    /* TIMER Timer 0 Capture Register B, init value = 0x00000000 */
__IO_REG32_BIT(T0CAPC,             0xFFFC4024, __READ,       __timer_t0cmp_bits        );    /* TIMER Timer 0 Capture Register C, init value = 0x00000000 */
__IO_REG32_BIT(T0CAPD,             0xFFFC4028, __READ,       __timer_t0cmp_bits        );    /* TIMER Timer 0 Capture Register D, init value = 0x00000000 */
__IO_REG32_BIT(T0CAPE,             0xFFFC402C, __READ,       __timer_t0cmp_bits        );    /* TIMER Timer 0 Capture Register E, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_CTRL1,              0xFFFC4030, __READ_WRITE, __timer_ctrl_bits         );    /* TIMER Timer 1 Control Register, init value = 0x00000000 */
__IO_REG32_BIT(INTEN1,             0xFFFC4034, __READ_WRITE, __timer_inten_bits        );    /* TIMER Timer 1 Interrupt Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_STATUS1,            0xFFFC4038, __READ_WRITE, __timer_status_bits       );    /* TIMER Timer 1 Status Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_CNT1,               0xFFFC403C, __READ_WRITE, __timer_cnt1_bits         );    /* TIMER Timer 1 Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(T1CMP0,             0xFFFC4040, __READ_WRITE, __timer_t1cmp_bits        );    /* TIMER Timer 1 Compare Register 0, init value = 0x0000FFFF */
__IO_REG32_BIT(T1CMP1,             0xFFFC4044, __READ_WRITE, __timer_t1cmp_bits        );    /* TIMER Timer 1 Compare Register 1, init value = 0x0000FFFF */
__IO_REG32_BIT(T1CAPA,             0xFFFC4048, __READ,       __timer_t1cap_bits        );    /* TIMER Timer 1 Capture Register A, init value = 0x00000000 */
__IO_REG32_BIT(T1CAPB,             0xFFFC404C, __READ,       __timer_t1cap_bits        );    /* TIMER Timer 1 Capture Register B, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_CTRL2,              0xFFFC4050, __READ_WRITE, __timer_ctrl_bits         );    /* TIMER Timer 2 Control Register, init value = 0x00000000 */
__IO_REG32_BIT(INTEN2,             0xFFFC4054, __READ_WRITE, __timer_inten_bits        );    /* TIMER Timer 2 Interrupt Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_STATUS2,            0xFFFC4058, __READ_WRITE, __timer_status_bits       );    /* TIMER Timer 2 Status Register, init value = 0x00000000 */
__IO_REG32_BIT(TIMER_CNT2,               0xFFFC405C, __READ_WRITE, __timer_cnt2_bits         );    /* TIMER Timer 2 Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(T2CMP0,             0xFFFC4060, __READ_WRITE, __timer_t2cmp_bits        );    /* TIMER Timer 2 Compare Register 0, init value = 0x0000FFFF */
__IO_REG32_BIT(T2CMP1,             0xFFFC4064, __READ_WRITE, __timer_t2cmp_bits        );    /* TIMER Timer 2 Compare Register 1, init value = 0x0000FFFF */
__IO_REG32_BIT(T2CAPA,             0xFFFC4068, __READ,       __timer_t2cap_bits        );    /* TIMER Timer 2 Capture Register A, init value = 0x00000000 */
__IO_REG32_BIT(T2CAPB,             0xFFFC406C, __READ,       __timer_t2cap_bits        );    /* TIMER Timer 2 Capture Register B, init value = 0x00000000 */


/***************************************************************************
 **
 **  UART0 : UART0
 **
 ***************************************************************************/

__IO_REG32_BIT(UART0_UARTDR,             0xFFFC0000, __READ_WRITE, __uart_uartdr_bits        );    /* UART0 Data Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTRSR_UARTECR,    0xFFFC0004, __READ_WRITE, __uart_uartrsr_ecr_bits   );    /* UART0 Read - Receive Status Register  Write - Error Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTFR,             0xFFFC0018, __READ,       __uart_uartfr_bits        );    /* UART0 Flag Register, init value = 0x00000090 */
__IO_REG32_BIT(UART0_UARTILPR,           0xFFFC0020, __READ_WRITE, __uart_uartilpr_bits      );    /* UART0 IrDA Low Power Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTIBRD,           0xFFFC0024, __READ_WRITE, __uart_uartibrd_bits      );    /* UART0 Integer Baud Rate Divisor Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTFBRD,           0xFFFC0028, __READ_WRITE, __uart_uartfbrd_bits      );    /* UART0 Fractional Baud Rate Divisor Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTLCR_H,          0xFFFC002C, __READ_WRITE, __uart_uartlcr_h_bits     );    /* UART0 Line Control Register HIGH byte, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTCR,             0xFFFC0030, __READ_WRITE, __uart_uartcr_bits        );    /* UART0 Control Register, init value = 0x00000300 */
__IO_REG32_BIT(UART0_UARTIFLS,           0xFFFC0034, __READ_WRITE, __uart_uartifls_bits      );    /* UART0 Interrupt FIFO Level Select Register, init value = 0x00000012 */
__IO_REG32_BIT(UART0_UARTIMSC,           0xFFFC0038, __READ_WRITE, __uart0_uartimsc_bits      );    /* UART0 Interrupt Mask Set/Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTRIS,            0xFFFC003C, __READ,       __uart0_uartris_bits       );    /* UART0 Raw Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTMIS,            0xFFFC0040, __READ,       __uart0_uartmis_bits       );    /* UART0 Masked Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_UARTICR,            0xFFFC0044, __READ_WRITE, __uart0_uarticr_bits       );    /* UART0 Interrupt Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(UART0_DMACTRL,            0xFFFC0048, __READ_WRITE, __uart_dmactrl_bits       );    /* UART0 DMA Control Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  UART1 : UART1
 **
 ***************************************************************************/

__IO_REG32_BIT(UART1_UARTDR,             0xFFFC1000, __READ_WRITE, __uart_uartdr_bits        );    /* UART1 Data Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTRSR_UARTECR,    0xFFFC1004, __READ_WRITE, __uart_uartrsr_ecr_bits   );    /* UART1 Read - Receive Status Register  Write - Error Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTFR,             0xFFFC1018, __READ,       __uart_uartfr_bits        );    /* UART1 Flag Register, init value = 0x00000090 */
__IO_REG32_BIT(UART1_UARTILPR,           0xFFFC1020, __READ_WRITE, __uart_uartilpr_bits      );    /* UART1 IrDA Low Power Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTIBRD,           0xFFFC1024, __READ_WRITE, __uart_uartibrd_bits      );    /* UART1 Integer Baud Rate Divisor Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTFBRD,           0xFFFC1028, __READ_WRITE, __uart_uartfbrd_bits      );    /* UART1 Fractional Baud Rate Divisor Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTLCR_H,          0xFFFC102C, __READ_WRITE, __uart_uartlcr_h_bits     );    /* UART1 Line Control Register HIGH byte, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTCR,             0xFFFC1030, __READ_WRITE, __uart_uartcr_bits        );    /* UART1 Control Register, init value = 0x00000300 */
__IO_REG32_BIT(UART1_UARTIFLS,           0xFFFC1034, __READ_WRITE, __uart_uartifls_bits      );    /* UART1 Interrupt FIFO Level Select Register, init value = 0x00000012 */
__IO_REG32_BIT(UART1_UARTIMSC,           0xFFFC1038, __READ_WRITE, __uart_uartimsc_bits      );    /* UART1 Interrupt Mask Set/Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTRIS,            0xFFFC103C, __READ,       __uart_uartris_bits       );    /* UART1 Raw Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTMIS,            0xFFFC1040, __READ,       __uart_uartmis_bits       );    /* UART1 Masked Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(UART1_UARTICR,            0xFFFC1044, __READ_WRITE, __uart_uarticr_bits       );    /* UART1 Interrupt Clear Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  UART2 : UART2
 **
 ***************************************************************************/

__IO_REG32_BIT(UART2_UARTDR,             0xFFFC2000, __READ_WRITE, __uart_uartdr_bits        );    /* UART2 Data Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTRSR_UARTECR,    0xFFFC2004, __READ_WRITE, __uart_uartrsr_ecr_bits   );    /* UART2 Read - Receive Status Register  Write - Error Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTFR,             0xFFFC2018, __READ,       __uart_uartfr_bits        );    /* UART2 Flag Register, init value = 0x00000090 */
__IO_REG32_BIT(UART2_UARTILPR,           0xFFFC2020, __READ_WRITE, __uart_uartilpr_bits      );    /* UART2 IrDA Low Power Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTIBRD,           0xFFFC2024, __READ_WRITE, __uart_uartibrd_bits      );    /* UART2 Integer Baud Rate Divisor Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTFBRD,           0xFFFC2028, __READ_WRITE, __uart_uartfbrd_bits      );    /* UART2 Fractional Baud Rate Divisor Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTLCR_H,          0xFFFC202C, __READ_WRITE, __uart_uartlcr_h_bits     );    /* UART2 Line Control Register HIGH byte, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTCR,             0xFFFC2030, __READ_WRITE, __uart_uartcr_bits        );    /* UART2 Control Register, init value = 0x00000300 */
__IO_REG32_BIT(UART2_UARTIFLS,           0xFFFC2034, __READ_WRITE, __uart_uartifls_bits      );    /* UART2 Interrupt FIFO Level Select Register, init value = 0x00000012 */
__IO_REG32_BIT(UART2_UARTIMSC,           0xFFFC2038, __READ_WRITE, __uart_uartimsc_bits      );    /* UART2 Interrupt Mask Set/Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTRIS,            0xFFFC203C, __READ,       __uart_uartris_bits       );    /* UART2 Raw Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTMIS,            0xFFFC2040, __READ,       __uart_uartmis_bits       );    /* UART2 Masked Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(UART2_UARTICR,            0xFFFC2044, __READ_WRITE, __uart_uarticr_bits       );    /* UART2 Interrupt Clear Register, init value = 0x00000000 */


/***************************************************************************
 **
 **  USB : Universal Serial Bus Device
 **
 ***************************************************************************/

__IO_REG32_BIT(_FAR,                 0xFFFF5000, __READ_WRITE, __usb_far_bits            );    /* USB Function Address Register, init value = 0x00000000 */
__IO_REG32_BIT(PMR,                  0xFFFF5004, __READ_WRITE, __usb_pmr_bits            );    /* USB Power Management Register, init value = 0x00000008 */
__IO_REG32_BIT(IIR,                  0xFFFF5008, __READ,       __usb_iir_bits            );    /* USB Interrupt Register for Endpoint 0 1 2 and 3, init value = 0x00000000 */
__IO_REG32_BIT(OIR,                  0xFFFF5010, __READ,       __usb_oir_bits            );    /* USB Interrupt register for OUT Endpoint 1 and 2, init value = 0x00000000 */
__IO_REG32_BIT(UIR,                  0xFFFF5018, __READ,       __usb_uir_bits            );    /* USB Interrupt register for common USB interrupts, init value = 0x00000000 */
__IO_REG32_BIT(IIE,                  0xFFFF501C, __READ_WRITE, __usb_iie_bits            );    /* USB Interrupt enable register for IIR, init value = 0x0000000F */
__IO_REG32_BIT(OIE,                  0xFFFF5024, __READ_WRITE, __usb_oie_bits            );    /* USB Interrupt enable register for OIR, init value = 0x00000006 */
__IO_REG32_BIT(UIE,                  0xFFFF502C, __READ_WRITE, __usb_uie_bits            );    /* USB Interrupt enable register for UIR, init value = 0x00000006 */
__IO_REG32_BIT(FRAME1,               0xFFFF5030, __READ,       __usb_frame1_bits         );    /* USB Frame number bits 0 to 7, init value = 0x00000000 */
__IO_REG32_BIT(FRAME2,               0xFFFF5034, __READ,       __usb_frame2_bits         );    /* USB Frame number bits 8 to 10, init value = 0x00000000 */
__IO_REG32_BIT(INDEX,                0xFFFF5038, __READ_WRITE, __usb_index_bits          );    /* USB Index register for selecting the endpoint when accessing the status and control registers, init value = 0x00000000 */
__IO_REG32_BIT(INMAXP,               0xFFFF5040, __READ_WRITE, __usb_inmaxp_bits         );    /* USB Maximum packet size for IN endpoint (INDEX register set to select Endpoints 1 2 or 3 only), init value = 0x00000000 */
__IO_REG32_BIT(CSR0_INCSR1,          0xFFFF5044, __READ_WRITE, __usb_csr0_incsr1_bits    );    /* USB Control Status register for Endpoint 0 (INDEX register set to select Endpoint 0)  Control Status register 1 for IN endpoint (INDEX register set to select Endpoints 1 2 and 3), init value = 0x00000000 */
__IO_REG32_BIT(INCSR2,               0xFFFF5048, __READ_WRITE, __usb_incsr2_bits         );    /* USB Control Status register 2 for IN endpoint (INDEX register set to select Endpoints 1 2 and 3 only), init value = 0x00000000 */
__IO_REG32_BIT(OUTMAXP,              0xFFFF504C, __READ_WRITE, __usb_outmaxp_bits        );    /* USB Maximum packet size for OUT endpoint (INDEX register set to select Endpoints 1 and 2 only), init value = 0x00000000 */
__IO_REG32_BIT(OUTCSR1,              0xFFFF5050, __READ_WRITE, __usb_outcsr1_bits        );    /* USB Control Status register 1 for OUT endpoint (INDEX register set to select Endpoints 1 and 2 only), init value = 0x00000000 */
__IO_REG32_BIT(OUTCSR2,              0xFFFF5054, __READ_WRITE, __usb_outcsr2_bits        );    /* USB Control Status register 2 for OUT endpoint (INDEX register set to select Endpoints 1 and 2 only), init value = 0x00000000 */
__IO_REG32_BIT(OUTCOUNT,             0xFFFF5058, __READ,       __usb_outcount_bits       );    /* USB Number of received bytes in Endpoint 0 FIFO (INDEX register set to select Endpoint 0)  Number of bytes in OUT endpoint FIFO (lower byte) (INDEX register set to select Endpoints 1 – 3), init value = 0x00000000 */
__IO_REG32_BIT(OUTCOUNT2,            0xFFFF505C, __READ,       __usb_outcount2_bits      );    /* USB Number of bytes in OUT endpoint FIFO (upper byte) (INDEX register set to select Endpoints 1 – 3 only), init value = 0x00000000 */
__IO_REG32_BIT(EP0FIFO,              0xFFFF5080, __READ_WRITE, __usb_epfifo_bits         );    /* USB FIFO for Endpoint 0, init value = 0x00000000 */
__IO_REG32_BIT(EP1FIFO,              0xFFFF5084, __READ_WRITE, __usb_epfifo_bits         );    /* USB FIFO for Endpoint 1, init value = 0x00000000 */
__IO_REG32_BIT(EP2FIFO,              0xFFFF5088, __READ_WRITE, __usb_epfifo_bits         );    /* USB FIFO for Endpoint 2, init value = 0x00000000 */
__IO_REG32_BIT(EP3FIFO,              0xFFFF508C, __READ_WRITE, __usb_epfifo_bits         );    /* USB FIFO for Endpoint 3, init value = 0x00000000 */
__IO_REG32_BIT(INTR,                 0xFFFF5200, __READ,       __usb_intr_bits           );    /* USB Indicates pending DMA interrupts, init value = 0x00000000 */
__IO_REG32_BIT(USB_CNTL1,                0xFFFF5204, __READ_WRITE, __usb_cntl_bits           );    /* USB DMA Channel 1 Control, init value = 0x00000000 */
__IO_REG32_BIT(USB_ADDR1,                0xFFFF5208, __READ_WRITE, __usb_addr1_bits          );    /* USB DMA Channel 1 AHB Memory Address (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_COUNT1,               0xFFFF520C, __READ_WRITE, __usb_count1_bits         );    /* USB DMA Channel 1 Byte Count (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_CNTL2,                0xFFFF5214, __READ_WRITE, __usb_cntl_bits           );    /* USB DMA Channel 2 Control, init value = 0x00000000 */
__IO_REG32_BIT(USB_ADDR2,                0xFFFF5218, __READ_WRITE, __usb_addr2_bits          );    /* USB DMA Channel 2 AHB Memory Address (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_COUNT2,               0xFFFF521C, __READ_WRITE, __usb_count2_bits         );    /* USB DMA Channel 2 Byte Count (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_CNTL3,                0xFFFF5224, __READ_WRITE, __usb_cntl_bits           );    /* USB DMA Channel 3 Control, init value = 0x00000000 */
__IO_REG32_BIT(USB_ADDR3,                0xFFFF5228, __READ_WRITE, __usb_addr3_bits          );    /* USB DMA Channel 3 AHB Memory Address (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_COUNT3,               0xFFFF522C, __READ_WRITE, __usb_count3_bits         );    /* USB DMA Channel 3 Byte Count (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_CNTL4,                0xFFFF5234, __READ_WRITE, __usb_cntl_bits           );    /* USB DMA Channel 4 Control, init value = 0x00000000 */
__IO_REG32_BIT(USB_ADDR4,                0xFFFF5238, __READ_WRITE, __usb_addr4_bits          );    /* USB DMA Channel 4 AHB Memory Address (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_COUNT4,               0xFFFF523C, __READ_WRITE, __usb_count4_bits         );    /* USB DMA Channel 4 Byte Count (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_CNTL5,                0xFFFF5244, __READ_WRITE, __usb_cntl_bits           );    /* USB DMA Channel 5 Control, init value = 0x00000000 */
__IO_REG32_BIT(USB_ADDR5,                0xFFFF5248, __READ_WRITE, __usb_addr5_bits          );    /* USB DMA Channel 5 AHB Memory Address (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_COUNT5,               0xFFFF524C, __READ_WRITE, __usb_count5_bits         );    /* USB DMA Channel 5 Byte Count (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_CNTL6,                0xFFFF5254, __READ_WRITE, __usb_cntl_bits           );    /* USB DMA Channel 6 Control, init value = 0x00000000 */
__IO_REG32_BIT(USB_ADDR6,                0xFFFF5258, __READ_WRITE, __usb_addr6_bits          );    /* USB DMA Channel 6 AHB Memory Address (32 bits), init value = 0x00000000 */
__IO_REG32_BIT(USB_COUNT6,               0xFFFF525C, __READ_WRITE, __usb_count6_bits         );    /* USB DMA Channel 6 Byte Count (32 bits), init value = 0x00000000 */



/***************************************************************************
 **
 **  VIC
 **
 ***************************************************************************/

/***************************************************************************
 **
 **  VIC : Vectored Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(VIC_IRQStatus,        0xfffff000, __READ      , __vic_int_bits);
__IO_REG32_BIT(VIC_FIQStatus,        0xfffff004, __READ      , __vic_int_bits);
__IO_REG32_BIT(VIC_RawIntr,          0xfffff008, __READ      , __vic_int_bits);
__IO_REG32_BIT(VIC_IntSelect,        0xfffff00c, __READ_WRITE, __vic_int_bits);
__IO_REG32_BIT(VIC_IntEnable,        0xfffff010, __READ_WRITE, __vic_int_bits);
__IO_REG32_BIT(VIC_IntEnClear,       0xfffff014, __WRITE     , __vic_int_bits);
__IO_REG32_BIT(VIC_SoftInt,          0xfffff018, __READ_WRITE, __vic_int_bits);
__IO_REG32_BIT(VIC_SoftIntClear,     0xfffff01c, __WRITE      , __vic_int_bits);
__IO_REG32_BIT(VECTADDR,             0xFFFFF030, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address Register, init value = 0x00000000 */
__IO_REG32_BIT(DEFVECTADDR,          0xFFFFF034, __READ_WRITE, __vic_defvectaddr_bits    );    /* VIC Default Vector Address Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR0,            0xFFFFF100, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 0 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR1,            0xFFFFF104, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 1 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR2,            0xFFFFF108, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 2 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR3,            0xFFFFF10C, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 3 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR4,            0xFFFFF110, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 4 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR5,            0xFFFFF114, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 5 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR6,            0xFFFFF118, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 6 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR7,            0xFFFFF11C, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 7 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR8,            0xFFFFF120, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 8 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR9,            0xFFFFF124, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 9 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR10,           0xFFFFF128, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 10 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR11,           0xFFFFF12C, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 11 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR12,           0xFFFFF130, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 12 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR13,           0xFFFFF134, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 13 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR14,           0xFFFFF138, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 14 Register, init value = 0x00000000 */
__IO_REG32_BIT(VECTADDR15,           0xFFFFF13C, __READ_WRITE, __vic_vectaddr_bits       );    /* VIC Vector Address 15 Register, init value = 0x00000000 */
__IO_REG32_BIT(VIC_VectCtrl0,        0xfffff200, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl1,        0xfffff204, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl2,        0xfffff208, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl3,        0xfffff20c, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl4,        0xfffff210, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl5,        0xfffff214, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl6,        0xfffff218, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl7,        0xfffff21c, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl8,        0xfffff220, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl9,        0xfffff224, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl10,       0xfffff228, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl11,       0xfffff22c, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl12,       0xfffff230, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl13,       0xfffff234, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl14,       0xfffff238, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_VectCtrl15,       0xfffff23c, __READ_WRITE, __vic_vectctrl_bits);
__IO_REG32_BIT(VIC_ITOP,             0xFFFFF30C, __READ      , __vic_itop_bits);

#define IRQSTATUS           VIC_IRQStatus
#define FIQSTATUS           VIC_FIQStatus
#define RAWINTR             VIC_RawIntr
#define INTSELECT           VIC_IntSelect
#define INTENABLE           VIC_IntEnable
#define INTENCLEAR          VIC_IntEnClear
#define SOFTINT             VIC_SoftInt
#define SOFTINT_CLEAR       VIC_SoftIntClear
#define VIC_VectAddr        VECTADDR
#define VIC_DefVectAddr     DEFVECTADDR
#define VIC_VectAddr0       VECTADDR0
#define VIC_VectAddr1       VECTADDR1
#define VIC_VectAddr2       VECTADDR2
#define VIC_VectAddr3       VECTADDR3
#define VIC_VectAddr4       VECTADDR4
#define VIC_VectAddr5       VECTADDR5
#define VIC_VectAddr6       VECTADDR6
#define VIC_VectAddr7       VECTADDR7
#define VIC_VectAddr8       VECTADDR8
#define VIC_VectAddr9       VECTADDR9
#define VIC_VectAddr10      VECTADDR10
#define VIC_VectAddr11      VECTADDR11
#define VIC_VectAddr12      VECTADDR12
#define VIC_VectAddr13      VECTADDR13
#define VIC_VectAddr14      VECTADDR14
#define VIC_VectAddr15      VECTADDR15
#define VECTCTRL0           VIC_VectCtrl0
#define VECTCTRL0_bit       VIC_VectCtrl0_bit
#define VECTCTRL1           VIC_VectCtrl1
#define VECTCTRL1_bit       VIC_VectCtrl1_bit
#define VECTCTRL2           VIC_VectCtrl2
#define VECTCTRL2_bit       VIC_VectCtrl2_bit
#define VECTCTRL3           VIC_VectCtrl3
#define VECTCTRL3_bit       VIC_VectCtrl3_bit
#define VECTCTRL4           VIC_VectCtrl4
#define VECTCTRL4_bit       VIC_VectCtrl4_bit
#define VECTCTRL5           VIC_VectCtrl5
#define VECTCTRL5_bit       VIC_VectCtrl5_bit
#define VECTCTRL6           VIC_VectCtrl6
#define VECTCTRL6_bit       VIC_VectCtrl6_bit
#define VECTCTRL7           VIC_VectCtrl7
#define VECTCTRL7_bit       VIC_VectCtrl7_bit
#define VECTCTRL8           VIC_VectCtrl8
#define VECTCTRL8_bit       VIC_VectCtrl8_bit
#define VECTCTRL9           VIC_VectCtrl9
#define VECTCTRL9_bit       VIC_VectCtrl9_bit
#define VECTCTRL10          VIC_VectCtrl10
#define VECTCTRL10_bit      VIC_VectCtrl10_bit
#define VECTCTRL11          VIC_VectCtrl11
#define VECTCTRL11_bit      VIC_VectCtrl11_bit
#define VECTCTRL12          VIC_VectCtrl12
#define VECTCTRL12_bit      VIC_VectCtrl12_bit
#define VECTCTRL13          VIC_VectCtrl13
#define VECTCTRL13_bit      VIC_VectCtrl13_bit
#define VECTCTRL14          VIC_VectCtrl14
#define VECTCTRL14_bit      VIC_VectCtrl14_bit
#define VECTCTRL15          VIC_VectCtrl15
#define VECTCTRL15_bit      VIC_VectCtrl15_bit
#define ITOP                VIC_ITOP
#define ITOP_bit            VIC_ITOP_bit

/***************************************************************************
 **
 **  WDT : Watchdog Timer
 **
 ***************************************************************************/

__IO_REG32_BIT(WDT_CTL,                  0xFFFE3000, __READ_WRITE, __wdt_ctl_bits            );    /* WDT Watchdog Control Register, init value = 0x00000000 */
__IO_REG32_BIT(WDT_RST,                  0xFFFE3004, __WRITE,      __wdt_rst_bits            );    /* WDT Watchdog Counter Reset, init value = 0x00000000 */
__IO_REG32_BIT(WDT_STATUS,               0xFFFE3008, __READ,       __wdt_status_bits         );    /* WDT Watchdog Status Register, init value = 0x00000000 */
__IO_REG32_BIT(WDT_COUNT0,               0xFFFE300C, __READ,       __wdt_count_bits          );    /* WDT Current Count bits [7:0], init value = 0x00000001 */
__IO_REG32_BIT(WDT_COUNT1,               0xFFFE3010, __READ,       __wdt_count_bits          );    /* WDT Current Count bits [15:8], init value = 0x00000001 */
__IO_REG32_BIT(WDT_COUNT2,               0xFFFE3014, __READ,       __wdt_count_bits          );    /* WDT Current Count bits [23:16], init value = 0x00000001 */
__IO_REG32_BIT(WDT_COUNT3,               0xFFFE3018, __READ,       __wdt_count_bits          );    /* WDT Current Count bits [31:24], init value = 0x00000001 */

/* Assembler-specific declarations  ****************************************/
#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  Interrupt vector table
 **
 ***************************************************************************/
#define RESETV        0x00  /* Reset                                       */
#define UNDEFV        0x04  /* Undefined instruction                       */
#define SWIV          0x08  /* Software interrupt                          */
#define PABORTV       0x0c  /* Prefetch abort                              */
#define DABORTV       0x10  /* Data abort                                  */
#define IRQV          0x18  /* Normal interrupt                            */
#define FIQV          0x1c  /* Fast interrupt                              */

/***************************************************************************
 **
 **  Interrupt sources
 **
 ***************************************************************************/

#define WDT_IRQ              0
#define COMMRX_IRQ           2
#define COMMTX_IRQ           3
#define Timer0_IRQ           4
#define Timer1_IRQ           5
#define Timer2_IRQ           6
#define External0_IRQ        7
#define External1_IRQ        8
#define External2_IRQ        9
#define External3_IRQ        10
#define External4_IRQ        11
#define External5_IRQ        12
#define External6_IRQ        13
#define External7_IRQ        14
#define RTC_IRQ              15
#define TSCIRQ_IRQ           16
#define BROWNOUTINTR_IRQ     17
#define PENIRQ_IRQ           18
#define CLCD_IRQ             19
#define DMA0_IRQ             20
#define DMA1_IRQ             21
#define DMA2_IRQ             22
#define DMA3_IRQ             23
#define SSPI2SINTR_IRQ       24
#define EMAC_IRQ             25
#define USB_IRQ              26
#define UART0_IRQ            27
#define UART1_IRQ            28
#define UART2_IRQ            29
#define USB_DMA_IRQ          30
#define I2C_IRQ              31

#endif    /* __IOLH79524_H */
