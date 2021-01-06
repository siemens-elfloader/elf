/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    SHARP LH79525
 **
 **    Used with ARM IAR c/c++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.2 $
 **
 ***************************************************************************/

#ifndef __IOLH79525_H
#define __IOLH79525_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"


/***************************************************************************
 ***************************************************************************
 **
 **    LH79525 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* High Word Register */
typedef struct {
  __REG32 REFP            : 2;
  __REG32 INM             : 1;
  __REG32 INP             : 4;
  __REG32 SETTIME         : 9;
  __REG32                 :16;
} __adchw_bits;

/* Low Word Register */
typedef struct {
  __REG32 REFM            : 2;
  __REG32 BIASCON         :12;
  __REG32                 :18;
} __adclw_bits;

/* Results Register */
typedef struct {
  __REG32 CBTAG           : 4;
  __REG32                 : 2;
  __REG32 ADCOUT          :10;
  __REG32                 :16;
} __adcrr_bits;

/* Interrupt Mask Register */
typedef struct {
  __REG32 FOMSK           : 1;
  __REG32 FWMSK           : 1;
  __REG32 EOSMSK          : 1;
  __REG32 PMSK            : 1;
  __REG32 BOIRQ           : 1;
  __REG32                 : 1;
  __REG32 INTEN           : 1;
  __REG32                 :25;
} __adcim_bits;

/* Power Configuration Register */
typedef struct {
  __REG32 NOC             : 4;
  __REG32 BATEN           : 1;
  __REG32 REFEN           : 1;
  __REG32 PWM             : 2;
  __REG32 CLKSEL          : 3;
  __REG32 BATLOC          : 5;
  __REG32                 :16;
} __adcpc_bits;

/* General Configuration Register */
typedef struct {
  __REG32 SSM             : 2;
  __REG32 SSB             : 1;
  __REG32 FIFOWMK         : 4;
  __REG32                 :25;
} __adcgc_bits;

/* General Status Register */
typedef struct {
  __REG32 CBTAG           : 4;
  __REG32 CBSTATE         : 4;
  __REG32 PENIRQ          : 1;
  __REG32 BRONOUT         : 1;
  __REG32                 :22;
} __adcgs_bits;

/* Interrupt Status Register */
typedef struct {
  __REG32 FOVRN_UM        : 1;
  __REG32 FWATER_UM       : 1;
  __REG32 EOS_UM          : 1;
  __REG32 PENSYNC_UM      : 1;
  __REG32 BROWNOUT_UM     : 1;
  __REG32                 :27;
} __adcis_bits;

/* FIFO Status Register */
typedef struct {
  __REG32 FGTEWATERMRK    : 1;
  __REG32 FOVRNDET        : 1;
  __REG32 FEMPTY          : 1;
  __REG32 FFF             : 1;
  __REG32 RDPTR           : 4;
  __REG32 WRPTR           : 4;
  __REG32                 :20;
} __adcfs_bits;

/* High Word Control Bank Register */
typedef struct {
  __REG16 REFP            : 2;
  __REG16 INM             : 1;
  __REG16 INP             : 4;
  __REG16 SETTIME         : 9; 
} __adchwcbx_bits;

/* Low Word Control Bank Register */
typedef struct {
  __REG16 REFM            : 2;
  __REG16 BIASCON         :12;
  __REG16                 : 2;
} __adclwcbx_bits;

/* Idle High Word Register */
typedef struct {
  __REG32 REFP_ID         : 2;
  __REG32 INM_ID          : 1;
  __REG32 INP_ID          : 4;
  __REG32 SETTIME_ID      : 9;
  __REG32                 :16;
} __adcihwctrl_bits;

/* Idle Low Word Register */
typedef struct {
  __REG32 REFM_ID         : 2;
  __REG32 BIASCON_ID      :12;
  __REG32                 :18;
} __adcilwctrl_bits;

/* Masked Interrupt Status Register */
typedef struct {
  __REG32 FOVRNINTR       : 1;
  __REG32 FWATERINTR      : 1;
  __REG32 EOSINTR         : 1;
  __REG32 PENSYNC         : 1;
  __REG32 BROWNOUT        : 1;
  __REG32                 :27;
} __adcmis_bits;

/* Interrupt Clear Register */
typedef struct {
  __REG32 EOSINTC         : 1;
  __REG32 PENIC           : 1;
  __REG32 BOIC            : 1;
  __REG32                 :29;
} __adcic_bits;

/* Power_up Boot Configuration Register */
typedef struct {
  __REG32 PBC             : 4;
  __REG32                 :28;
} __bootpbc_bits;

/* nCS1 Override Register */
typedef struct {
  __REG32 CS1O            : 1;
  __REG32                 :31;
} __bootcs1ov_bits;

/* External Peripheral Mapping Register */
typedef struct {
  __REG32 CS0EP           : 1;
  __REG32 CS1EP           : 1;
  __REG32 CS2EP           : 1;
  __REG32 CS3EP           : 1;
  __REG32                 :28;
} __bootepm_bits;

/* Horizontal Timing Panel Control Register */
typedef struct {
  __REG32                 : 2;
  __REG32 PPL             : 6;
  __REG32 HSW             : 8;
  __REG32 HFP             : 8;
  __REG32 HBP             : 8;
} __clcdctiming0_bits;

/* Vertical Timing Panel Control Register */
typedef struct {
  __REG32 LPP             :10;
  __REG32 VSW             : 6;
  __REG32 VFP             : 8;
  __REG32 VBP             : 8;
} __clcdctiming1_bits;

/* Clock and Signal Polarity Control Register */
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
} __clcdctiming2_bits;

/* Upper Panel Frame Buffer Base Address Register */
typedef struct {
  __REG32                 : 2;
  __REG32 LCDUPBASE       :30;
} __clcdcupbase_bits;

/* Lower Panel Frame Buffer Base Address Register */
typedef struct {
  __REG32                 : 2;
  __REG32 LCDLPBASE       :30;
} __clcdclpbase_bits;

/* Interrupt Enable Register */
typedef struct {
  __REG32                 : 1;
  __REG32 FUIEN           : 1;
  __REG32 BUIEN           : 1;
  __REG32 VCIEN           : 1;
  __REG32 MBEIEN          : 1;
  __REG32                 :27;
} __clcdcintren_bits;

/* CLCDC Control Register */
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
} __clcdcctrl_bits;

/* Raw Interrupt Status */
typedef struct {
  __REG32                 : 1;
  __REG32 FUI             : 1;
  __REG32 BUI             : 1;
  __REG32 VCI             : 1;
  __REG32 MBEI            : 1;
  __REG32                 :27;
} __clcdcstatus_bits;

/* Masked Interrupt Status Register */
typedef struct {
  __REG32                 : 1;
  __REG32 FUIM            : 1;
  __REG32 BUIM            : 1;
  __REG32 VCIM            : 1;
  __REG32 MBEIM           : 1;
  __REG32                 :27;
} __clcdcinterrupt_bits;

/* Interrupt Clear Register */
typedef struct {
  __REG32                 : 1;
  __REG32 CFUI            : 1;
  __REG32 CBUI            : 1;
  __REG32 CVCI            : 1;
  __REG32 CMBEI           : 1;
  __REG32                 :27;
} __clcdcintclr_bits;

/* LCD Upper Panel and Lower Panel Frame Buffer Current Address Register */
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
} __clcdcpcurr_bits;

/* 256 × 16-bit Color Palette Register */
typedef struct {
  __REG32                 : 1;
  __REG32 LR              : 4;
  __REG32                 : 1;
  __REG32 LG              : 4;
  __REG32                 : 1;
  __REG32 LB              : 4;
  __REG32                 : 2;
  __REG32 MR              : 4;
  __REG32                 : 1;
  __REG32 MG              : 4;
  __REG32                 : 1;
  __REG32 MB              : 4;
  __REG32                 : 1;
} __clcdcpalette_bits;

/* Setup Register */
typedef struct {
  __REG32 CR              : 1;
  __REG32                 : 3;
  __REG32 PPL             : 9;
  __REG32 ALIEN           : 1;
  __REG32                 :18;
} __alialisetup_bits;

/* Control Register */
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
} __alialictrl_bits;

/* Timing Delay Register 1 */
typedef struct {
  __REG32 LPDEL           : 4;
  __REG32 REVDEL          : 4;
  __REG32 PSCLS           : 4;
  __REG32 MODDEL          : 2;
  __REG32                 :18;
} __alialitiming1_bits;

/* Timing Delay Register 2 */
typedef struct {
  __REG32 PS2CLS2         : 9;
  __REG32 SPLDEL          : 7;
  __REG32                 :16;
} __alialitiming2_bits;

/* Source Base Address Register Low */
typedef struct {
  __REG32 SOURCELO        :16;
  __REG32                 :16;
} __dmasourcelo_bits;

/* Source Base Address Register High */
typedef struct {
  __REG32 SOURCEHI        :16;
  __REG32                 :16;
} __dmasourcehi_bits;

/* Destination Base Address Register Low */
typedef struct {
  __REG32 DESTLO          :16;
  __REG32                 :16;
} __dmadestlo_bits;

/* Destination Base Address Register High */
typedef struct {
  __REG32 DESTHI          :16;
  __REG32                 :16;
} __dmadesthi_bits;

/* Maximum Count Register */
typedef struct {
  __REG32 MAXCOUNT        :16;
  __REG32                 :16;
} __dmamax_bits;

/* Control Register */
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
} __dmactrl_bits;

/* Current Source Address Register High */
typedef struct {
  __REG32 CURSHI          :16;
  __REG32                 :16;
} __dmacurshi_bits;

/* Current Source Address Register Low */
typedef struct {
  __REG32 CURSLO          :16;
  __REG32                 :16;
} __dmacurslo_bits;

/* Current Destinaiton Address Register High */
typedef struct {
  __REG32 CURDHI          :16;
  __REG32                 :16;
} __dmacurdhi_bits;

/* Current Destination Address Register Low */
typedef struct {
  __REG32 CURDLO          :16;
  __REG32                 :16;
} __dmacurdlo_bits;

/* Terminal Count Register */
typedef struct {
  __REG32 TERM            :16;
  __REG32                 :16;
} __dmatcnt_bits;

/* DMA Interrupt Mask Register */
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
} __dmamask_bits;

/* DMA Interrupt Clear */
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
} __dmaclr_bits;

/* DMA Status Register */
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
} __dmastatus_bits;

/* Network Control Register */
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
} __emacnetctl_bits;

/* Network Configuration Register */
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
} __emacnetconfig_bits;

/* Network Status Register */
typedef struct {
  __REG32                 : 1;
  __REG32 MDIOINSTAT      : 1;
  __REG32 PHYIDLE         : 1;
  __REG32                 :29;
} __emacnetstatus_bits;

/* Transmit Status Register */
typedef struct {
  __REG32 USEDBIT         : 1;
  __REG32 COLLISION       : 1;
  __REG32 RETRYLIMIT      : 1;
  __REG32 TXGO            : 1;
  __REG32 BUFEX           : 1;
  __REG32 TXCOMPLETE      : 1;
  __REG32 TXUNDER         : 1;
  __REG32                 :25;
} __emactxstatus_bits;

/* Receive Buffer Queue Pointer */
typedef struct {
  __REG32                 : 2;
  __REG32 RXBQP           :30;
} __emacrxbqp_bits;

/* Transmit Buffer Queue Pointer */
typedef struct {
  __REG32                 : 2;
  __REG32 TXBQP           :30;
} __emactxbqp_bits;

/* Receive Status Register */
typedef struct {
  __REG32 BUFNOTAVAIL     : 1;
  __REG32 FRMREC          : 1;
  __REG32 RXCOVERRUN      : 1;
  __REG32                 :29;
} __emacrxstatus_bits;

/* Interrupt Status Regsiter */
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
} __emacinstatus_bits;

/* Interrupt Enable Register */
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
} __emacenable_bits;

/* Interrupt Disable Register */
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
} __emacdisable_bits;

/* Interrupt Mask Register */
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
} __emacmask_bits;

/* PHY Maintenance Register */
typedef struct {
  __REG32 PHYRDWR         :16;
  __REG32                 : 2;
  __REG32 REGADDR         : 5;
  __REG32 PHYADDR         : 5;
  __REG32 OPERATION       : 2;
  __REG32 STARTFRM        : 2;
} __emacphymaint_bits;

/* Paus Time Register */
typedef struct {
  __REG32 PAUSETIME       :16;
  __REG32                 :16;
} __emacpausetime_bits;

/* Transmit Pause Quantum Register */
typedef struct {
  __REG32 TXPAUSEQUAN     :16;
  __REG32                 :16;
} __emactxpausequan_bits;

/* Paus Frames Received Register */
typedef struct {
  __REG32 PAUSEFRRXOK     :16;
  __REG32                 :16;
} __emacpausefrrx_bits;

/* Frames Transmitted OK Register */
typedef struct {
  __REG32 FRMTXOK         :24;
  __REG32                 : 8;
} __emacfrmtxok_bits;

/* Single Collisions Frame Register */
typedef struct {
  __REG32 SINGLECOL       :16;
  __REG32                 :16;
} __emacsinglecol_bits;

/* Multiply Collisions Frame Register */
typedef struct {
  __REG32 MULTFRM         :16;
  __REG32                 :16;
} __emacmultfrm_bits;

/* Frames Received OK Register */
typedef struct {
  __REG32 FRMRXOK         :24;
  __REG32                 : 8;
} __emacfrmrxok_bits;

/* Frame Check Sequence Error Register */
typedef struct {
  __REG32 FRCHK           : 8;
  __REG32                 :24;
} __emacfrchk_bits;

/* Alignment Errors Register */
typedef struct {
  __REG32 ALIGNERR        : 8;
  __REG32                 :24;
} __emacalignerr_bits;

/* Deferred Transmission Frames Register */
typedef struct {
  __REG32 DEFTXFRM        :16;
  __REG32                 :16;
} __emacdeftxfrm_bits;

/* Late Collisions Register */
typedef struct {
  __REG32 LATECOL         : 8;
  __REG32                 :24;
} __emaclatecol_bits;

/* Excessive Collisions Register */
typedef struct {
  __REG32 EXCCOL          : 8;
  __REG32                 :24;
} __emacexcol_bits;

/* Transmit Underrun Errors Register */
typedef struct {
  __REG32 TXUNDER         : 8;
  __REG32                 :24;
} __emactxunder_bits;

/* Carrier Sense Errors Register */
typedef struct {
  __REG32 SENSERR         : 8;
  __REG32                 :24;
} __emacsenserr_bits;

/* Receive Resource Errors Register */
typedef struct {
  __REG32 RXRERR          :16;
  __REG32                 :16;
} __emacrxrerr_bits;

/* Receive Overrun Errors Register */
typedef struct {
  __REG32 RXOVERR         : 8;
  __REG32                 :24;
} __emacrxoverr_bits;

/* Receive Symbol Errors Register */
typedef struct {
  __REG32 RXSYMERR        : 8;
  __REG32                 :24;
} __emacrxsymerr_bits;

/* Excessive Length Error Register */
typedef struct {
  __REG32 LENERR          : 8;
  __REG32                 :24;
} __emaclenerr_bits;

/* Receive Jabbers Register */
typedef struct {
  __REG32 RXJAB           : 8;
  __REG32                 :24;
} __emacrxjab_bits;

/* Undersize Frames Register */
typedef struct {
  __REG32 UNDERFRM        : 8;
  __REG32                 :24;
} __emacunderfrm_bits;

/* SQE Test Errors Register */
typedef struct {
  __REG32 SQERR           : 8;
  __REG32                 :24;
} __emacsqerr_bits;

/* Received Length Field Mismatch Register */
typedef struct {
  __REG32 RXLEN           : 8;
  __REG32                 :24;
} __emacrxlen_bits;

/* Transmitted Pause Frames Register */
typedef struct {
  __REG32 TXPAUSEFM       :16;
  __REG32                 :16;
} __emactxpausefm_bits;

/* Hash Register Bottom */
typedef struct {
  __REG32 HASHBOT         :32;
} __emachashbot_bits;

/* Hash Register Top */
typedef struct {
  __REG32 HASHTOP         :32;
} __emachashtop_bits;

/* Specific Address 1 Bottom Register */
typedef struct {
  __REG32 SPECAD1BOT      :32;
} __emacspecad1bot_bits;

/* Specific Address 1 Top Register */

typedef struct {
  __REG32 SPECAD1TOP      :16;
  __REG32                 :16;
} __emacspecad1top_bits;

/* Specific Address 2 Bottom Register */


typedef struct {
  __REG32 SPECAD2BOT      :32;
} __emacspecad2bot_bits;

/* Specific Address 2 Top Register */


typedef struct {
  __REG32 SPECAD2TOP      :16;
  __REG32                 :16;
} __emacspecad2top_bits;

/* Specific Address 3 Bottom Register */


typedef struct {
  __REG32 SPECAD3BOT      :32;
} __emacspecad3bot_bits;

/* Specific Address 3 Top Register */


typedef struct {
  __REG32 SPECAD3TOP      :16;
  __REG32                 :16;
} __emacspecad3top_bits;

/* Specific Address 4 Bottom Register */


typedef struct {
  __REG32 SPECAD4BOT      :32;
} __emacspecad4bot_bits;

/* Specific Address 4 Top Register */


typedef struct {
  __REG32 SPECAD4TOP      :16;
  __REG32                 :16;
} __emacspecad4top_bits;

/* Type ID Checking Register */
typedef struct {
  __REG32 IDCHK           :16;
  __REG32                 :16;
} __emacidchk_bits;

/* Control Register */
typedef struct {
  __REG32 ENABLE          : 1;
  __REG32                 : 1;
  __REG32 MODE            : 1;
  __REG32                 :29;
} __emccontrol_bits;

/* Status Register */
typedef struct {
  __REG32 BUSY            : 1;
  __REG32 WRBUF           : 1;
  __REG32 SA              : 1;
  __REG32                 :29;
} __emcstatus_bits;

/* Configuration Register */
typedef struct {
  __REG32                 : 8;
  __REG32 CLK             : 1;
  __REG32                 :23;
} __emcconfig_bits;

/* Dynamic Memory Control Register */
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
} __emcdynmctrl_bits;

/* Dynamic memory Refresh Timer */
typedef struct {
  __REG32 REFRESH         :11;
  __REG32                 :21;
} __emcdynmref_bits;

/* Dynamic memory Read Configuration Register */
typedef struct {
  __REG32 RDS             : 2;
  __REG32                 :30;
} __emc_dynmrcon_bits;

/* Dynamic Memory Precharge Command Period Register */
typedef struct {
  __REG32 tRP             : 4;
  __REG32                 :28;
} __emcprecharge_bits;

/* Dynamic Memory Active to Precharge Command Period Register */
typedef struct {
  __REG32 tRAS            : 4;
  __REG32                 :28;
} __emcdynm2pre_bits;

/* Dynamic Memory Self-Refresh Exit Time Register */
typedef struct {
  __REG32 tSREX           : 4;
  __REG32                 :28;
} __emcrefexit_bits;

/* Dynamic Memory Last Data Out To Active Time Register */
typedef struct {
  __REG32 tAPR            : 4;
  __REG32                 :28;
} __emcdoactive_bits;

/* Dynamic Memory Data In To Active Time Register */
typedef struct {
  __REG32 tDAL            : 4;
  __REG32                 :28;
} __emcdiactive_bits;

/* Dynamic Memory Write Recovery Time Register */
typedef struct {
  __REG32 tWR             : 4;
  __REG32                 :28;
} __emcdwrt_bits;

/* Dynamic Memory Active to Active Command Period Register */
typedef struct {
  __REG32 tRC             : 5;
  __REG32                 :27;
} __emcdynactcmd_bits;

/* Dynamic Memory Auto-Refresh Period, and Auto-Refresh to Active Command Period Register */
typedef struct {
  __REG32 tRFC            : 5;
  __REG32                 :27;
} __emcdynauto_bits;

/* Dynamic Memory Exit Self-Refresh to Active Command Time Register */
typedef struct {
  __REG32 tXSR            : 5;
  __REG32                 :27;
} __emcdynrefexit_bits;

/* Dynamic Memory Active Bank A to Active Bank Bits Time Register */
typedef struct {
  __REG32 tRRD            : 4;
  __REG32                 :28;
} __emcdynactiveab_bits;

/* Dynamic Memory Load Mode Register to Active Command Time Register */
typedef struct {
  __REG32 tMRD            : 4;
  __REG32                 :28;
} __emcdynamicmrd_bits;

/* Static Memory Extended Wait Register */
typedef struct {
  __REG32 WAIT            :10;
  __REG32                 :22;
} __emcwait_bits;

/* Dynamic Configuration Register for nDCS0 and nDCS1 */
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
} __emcdyncfg_bits;

/* Dynamic Memory RAS and CAS Delay Register for nDCS0 and nDCS1 */
typedef struct {
  __REG32 RAS             : 2;
  __REG32                 : 6;
  __REG32 CAS             : 2;
  __REG32                 :22;
} __emcdynrascas_bits;

/* Static Memory Configuration Register */
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
} __emcsconfig_bits;

/* Static Memory Write Enable Delay Registers */
typedef struct {
  __REG32 WAITWEN         : 4;
  __REG32                 :28;
} __emcswaitwen_bits;

/* Static Memory Output Enable Delay Registers */
typedef struct {
  __REG32 WAITOEN         : 4;
  __REG32                 :28;
} __emcswaitoen_bits;

/* Static Memory Read Delay Registers */
typedef struct {
  __REG32 WAITRD          : 5;
  __REG32                 :27;
} __emcswaitrd_bits;

/* Static Memory Page Mode Read Delay Registers */
typedef struct {
  __REG32 WAITPAGE        : 5;
  __REG32                 :27;
} __emcswaitpage_bits;

/* Static Memory Write Delay Registers */
typedef struct {
  __REG32 WAITWR          : 5;
  __REG32                 :27;
} __emcswaitwr_bits;

/* Static Memory Turn Around Delay Registers */
typedef struct {
  __REG32 BTC             : 4;
  __REG32                 :28;
} __emcsturn_bits;

/* GPIO Port Data Registers */
typedef struct {
  __REG32 PORT_DATA       : 8;
  __REG32                 :24;
} __gpiopxdr_bits;

/* GPIO Port Data Direction Registers */

typedef struct {
  __REG32 PORT_DIRECTION  : 8;
  __REG32                 :24;
} __gpiopxddr_bits;

/* I2C Configuration Register */
typedef struct {
  __REG32 MODE            : 2;
  __REG32 I2CEN           : 1;
  __REG32 SPEED           : 1;
  __REG32 START           : 1;
  __REG32 STOP            : 1;
  __REG32 RWC             : 1;
  __REG32 SABT            : 1;
  __REG32                 :24;
} __i2ciccon_bits;

/* I2C Slave Address Register */
typedef struct {
  __REG32 SLAD7           : 8;
  __REG32                 :24;
} __i2cicsar_bits;

/* I2C Upper Slave Address Register */
typedef struct {
  __REG32                 : 1;
  __REG32 SLAD89          : 2;
  __REG32 UPPERAD         : 5;
  __REG32                 :24;
} __i2cicusar_bits;

/* I2C Data Register */
typedef struct {
  __REG32 DAT             : 8;
  __REG32                 :24;
} __i2cicdata_bits;

/* I2C Clock High Time Register */
typedef struct {
  __REG32 HCNT            : 8;
  __REG32                 :24;
} __i2cichcnt_bits;

/* I2C Clock Low Time Register */
typedef struct {
  __REG32 LCNT            : 8;
  __REG32                 :24;
} __i2ciclcnt_bits;

/* I2C Status Register */
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
} __i2cicstat_bits;

/* I2S Control Register */
typedef struct {
  __REG32 I2SEL           : 1;
  __REG32 I2SEN           : 1;
  __REG32 WSINV           : 1;
  __REG32 WSDEL           : 1;
  __REG32 CLKINV          : 1;
  __REG32 LOOP            : 1;
  __REG32                 :26;
} __i2sctrl_bits;

/* I2S Status Register */
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
} __i2sstat_bits;

/* I2S Interrupt Mask Set or Clear Register */
typedef struct {
  __REG32 RORIM           : 1;
  __REG32 RTIM            : 1;
  __REG32 RXIM            : 1;
  __REG32 TXIM            : 1;
  __REG32 TXUEM           : 1;
  __REG32 ECPEM           : 1;
  __REG32 SSPPEM          : 1;
  __REG32                 :25;
} __i2simsc_bits;

/* I2S Raw Interrupt Status Register */
typedef struct {
  __REG32 RORRIS          : 1;
  __REG32 RTRIS           : 1;
  __REG32 RXRIS           : 1;
  __REG32 TXRIS           : 1;
  __REG32 TXUERIS         : 1;
  __REG32 ECPERIS         : 1;
  __REG32 SSPPERIS        : 1;
  __REG32                 :25;
} __i2sris_bits;

/* I2S Masked Interrupt Status Register */
typedef struct {
  __REG32 RORMIS          : 1;
  __REG32 RTMIS           : 1;
  __REG32 RXMIS           : 1;
  __REG32 TXMIS           : 1;
  __REG32 TXUEMIS         : 1;
  __REG32 ECPEMIS         : 1;
  __REG32 SSPPEMIS        : 1;
  __REG32                 :25;
} __i2smis_bits;

/* I2S Interrupt Clear Register */
typedef struct {
  __REG32                 : 4;
  __REG32 TXUEC           : 1;
  __REG32 ECPEC           : 1;	
  __REG32 SSPPEC          : 1;
  __REG32                 :25;
} __i2sicr_bits;

/* Multiplexing Control 1 Register */  /* Resistor Configuration Control 1 Register */
typedef struct {
  __REG32                 : 4; 
  __REG32 PI0             : 2;
  __REG32 PI1             : 2;
  __REG32 PI2             : 2;
  __REG32                 :22;
} __ioconctl1_bits;

/* Multiplexing Control 3 Register */  /* Resistor Configuration Control 3 Register */
typedef struct {
  __REG32 INT4            : 2;
  __REG32                 :30;
} __ioconctl3_bits;

/* Multiplexing Control 4 Register */  /* Resistor Configuration Control 4 Register */
typedef struct {
  __REG32 PA2             : 2;
  __REG32 PA3             : 2;
  __REG32 PA4             : 2;
  __REG32 PA5             : 2;
  __REG32 PA6             : 2;
  __REG32 PA7             : 2;
  __REG32                 :20;
} __ioconctl4_bits;

/* Multiplexing Control 5 Register */  /* Resistor Configuration Control 5 Register */
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
} __ioconctl5_bits;

/* Multiplexing Control 6 Register */  /* Resistor Configuration Control 6 Register */
typedef struct {
  __REG32 PB0             : 2;
  __REG32 PB1             : 2;
  __REG32                 :28;
} __ioconctl6_bits;

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
} __ioconctl7_bits;

/* Multiplexing Control 10 Register */  /* Resistor Configuration Control 10 Register */
typedef struct {
  __REG32                 : 2;
  __REG32 PD5             : 2;
  __REG32                 : 2;
  __REG32 PD6             : 2;
  __REG32                 : 2;
  __REG32 PD7             : 2;
  __REG32                 :20; 
} __ioconctl10_bits;

/* Multiplexing Control 11 Register */  /* Resistor Configuration Control 11 Register */
typedef struct {
  __REG32 PD1             : 2;
  __REG32                 : 4;
  __REG32 PD2             : 2;
  __REG32                 : 2;
  __REG32 PD3             : 2;
  __REG32                 : 2;
  __REG32 PD4             : 2;
  __REG32                 :16;
} __ioconctl11_bits;

/* Multiplexing Control 12 Register */  
typedef struct {
  __REG32                 :12;
  __REG32 PD0             : 2;
  __REG32                 :18;
} __ioconmuxctl12_bits;

/* Resistor Configuration Control 12 Register */
typedef struct {
  __REG32 D2              : 2;
  __REG32 D3              : 2;
  __REG32 D4              : 2;
  __REG32 D5              : 2;
  __REG32 D6              : 2;
  __REG32 D7              : 2;
  __REG32 PD0             : 2; 
  __REG32                 :18;
} __ioconresctl12_bits;

/* Resistor Configuration Control 13 Register */
typedef struct {
  __REG32 D0              : 2;
  __REG32 D1              : 2;
  __REG32                 :28;
} __ioconresctl13_bits;

/* Multiplexing Control 14 Register */
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
} __ioconmuxctl14_bits;

typedef struct {
  __REG32 nBLE0           : 2;
  __REG32                 :30;
} __ioconctl15_bits;

/* Resistor Configuration Control 17 Register */
typedef struct {
  __REG32 SDCLK           : 2;
  __REG32                 :30;
} __ioconresctl17_bits;

/* Multiplexing Control 17 Register */ /* Resistor Configuration Control 17 Register */
typedef struct {
  __REG32                 : 2;
  __REG32 PE3             : 2;
  __REG32 PE4             : 2;
  __REG32                 : 2;
  __REG32 PE5             : 2;
  __REG32                 : 2;
  __REG32 PE6             : 2;
  __REG32 PE7             : 2;
  __REG32                 :16;
} __ioconctl19_bits;

/* Multiplexing Control 20 Register */ /* Resistor Configuration Control 20 Register */
typedef struct {
  __REG32 PF6             : 2;
  __REG32 PF7             : 2;
  __REG32                 : 2;
  __REG32 PE0             : 2;
  __REG32                 : 2;
  __REG32 PE1             : 2;
  __REG32                 : 2;
  __REG32 PE2             : 2;
  __REG32                 :16;
} __ioconctl20_bits;

/* Multiplexing Control 21 Register */ /* Resistor Configuration Control 21 Register */
typedef struct {
  __REG32 PF2             : 2;
  __REG32 PF3             : 2;
  __REG32                 : 2;
  __REG32 PF4             : 2;
  __REG32                 : 2;
  __REG32 PF5             : 2;
  __REG32                 :20;
} __ioconctl21_bits;

/* Multiplexing Control 22 Register */ /* Resistor Configuration Control 22 Register */
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
} __ioconctl22_bits;

/* Multiplexing Control 23 Register */ /* Resistor Configuration Control 23 Register */
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
} __ioconctl23_bits;

/* Multiplexing Control 24 Register */ /* Resistor Configuration Control 24 Register */
typedef struct {
  __REG32 PI3             : 2;
  __REG32 PI4             : 2;
  __REG32 PI5             : 2;
  __REG32 PI6             : 2;
  __REG32 PI7             : 2;
  __REG32 PH0             : 2;
  __REG32 PH1             : 2;
  __REG32                 :18;
} __ioconctl24_bits;

/* Multiplexing Control 25 Register */
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
} __ioconmuxctl25_bits;

/* RTC Data Register */
typedef struct {
  __REG32 RTCDR           :32;
} __rtcdr_bits;

/* RTC Match Register */
typedef struct {
  __REG32 RTCMR           :32;
} __rtcmr_bits;

/* RTC Load Register */
typedef struct {
  __REG32 RTCLR           :32;
} __rtclr_bits;

/* RTC Control Register */

typedef struct {
  __REG32 START           : 1;
  __REG32                 :31;
} __rtccr_bits;

/* RTC Interrupt Mask Set or Clear Register */

typedef struct {
  __REG32 IMSC            : 1;
  __REG32                 :31;
} __rtcimsc_bits;

/* RTC Raw Interrupt Status Register */


typedef struct {
  __REG32 RIS             : 1;
  __REG32                 :31;
} __rtcris_bits;

/* RTC Masked Interrupt Status Register */


typedef struct {
  __REG32 MIS             : 1;
  __REG32                 :31;
} __rtcmis_bits;

/* RTC Interrupt Clear Register */

typedef struct {
  __REG32 ICR             : 1;
  __REG32                 :31;
} __rtcicr_bits;

/* RCPC Control Register */
typedef struct {
  __REG32                 : 2;
  __REG32 PWRDWNSEL       : 3;
  __REG32 OUTSEL          : 2;
  __REG32                 : 2;
  __REG32 LOCK            : 1;
  __REG32                 :22;
} __rcpcctrl_bits;

/* RCPC Identification Register */
typedef struct {
  __REG32                 : 4;
  __REG32 PARTNO          :12;
  __REG32                 :16;
} __rcpcchipid_bits;

/* RCPC Remap Control Register */
typedef struct {
  __REG32 REMAP           : 2;
  __REG32                 :30;
} __rcpcremap_bits;

/* RCPC Software Reset Register */
typedef struct {
  __REG32 SRST            :16;
  __REG32                 :16;
} __rcpcsoftreset_bits;

/* RCPC Reset Status Register */
typedef struct {
  __REG32 EXT             : 1;
  __REG32 WDTO            : 1;
  __REG32                 :30;
} __rcpcrststatus_bits;

/* RCPC Reset Status Clear Register */
typedef struct {
  __REG32 EXTCLR          : 1;
  __REG32 TOCLR           : 1;
  __REG32                 :30;
} __rcpcrststatusclr_bits;

/* RCPC System Clock Prescaler Register */
typedef struct {
  __REG32 HDIV            : 4;
  __REG32                 :28;
} __rcpcsysclkpre_bits;

/* RCPC CPU Clock Prescaler Register */
typedef struct {
  __REG32 FDIV            : 4;
  __REG32                 :28;
} __rcpccpuclkpre_bits;

/* RCPC Peripheral Clock Control Register 0 */
typedef struct {
  __REG32 U0              : 1;
  __REG32 U1              : 1;
  __REG32 U2              : 1;
  __REG32                 : 6;
  __REG32 RTC             : 1;
  __REG32                 :22;
} __rcpcpclkctrl0_bits;

/* RCPC Peripheral Clock Control Register 1 */
typedef struct {
  __REG32 LCD             : 1;
  __REG32 SSP             : 1;
  __REG32 ADC             : 1;
  __REG32 USB             : 1;
  __REG32                 :28;
} __rcpcpclkctrl1_bits;

/* RCPC AHB Clock Control Register */
typedef struct {
  __REG32 DMA             : 1;
  __REG32 SDRAM           : 1;
  __REG32 ETHERNET        : 1;
  __REG32 USB             : 1;
  __REG32 LCD             : 1;
  __REG32                 :27;
} __rcpcahbclkctrl_bits;

/* RCPC Peripheral Clock Select Register 1 */
typedef struct {
  __REG32 UART0           : 1;
  __REG32 UART1           : 1;
  __REG32 UART2           : 1;
  __REG32                 :29;
} __rcpcpclksel0_bits;

/* RCPC Peripheral Clock Select Register 1 */
typedef struct {
  __REG32                 : 1;
  __REG32 SSP             : 1;
  __REG32 ADC             : 1;
  __REG32 USB             : 1;
  __REG32                 :28;
} __rcpcpclksel1_bits;

/* RCPC Silicon Revision Register */
typedef struct {
  __REG32 REVNO           :16;
  __REG32                 :16;
} __rcpcsiliconrev_bits;

/* RCPC LCD Clock Prescaler Register */
typedef struct {
  __REG32 LCDDIV          : 8;
  __REG32                 :24;
} __rcpclcdpre_bits;

/* RCPC SSP Clock Prescaler Register */
typedef struct {
  __REG32 SSPDIV          : 8;
  __REG32                 :24;
} __rcpcssppre_bits;

/* RCPC ADC Clock Prescaler Register */
typedef struct {
  __REG32 ADCDIV          : 8;
  __REG32                 :24;
} __rcpcadcpre_bits;

/* RCPC USB Clock Prescaler Register */
typedef struct {
  __REG32 USBDIV          : 8;
  __REG32                 :24;
} __rcpcusbpre_bits;

/* RCPC External Interrupt Configuration Register */
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
} __rcpcintconfig_bits;

/* RCPC External Interrupt Clear Register */
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
} __rcpcintclr_bits;

/* RCPC Core Clock Configuration Register */
typedef struct {
  __REG32 CCLK            : 2;
  __REG32                 :30;
} __rcpccoreconfig_bits;

/* RCPC System PLL Control Register */
typedef struct {
  __REG32 SYSLOOPDIV      : 6;
  __REG32 SYSPREDIV       : 6;
  __REG32 SYSFRANGE       : 1;
  __REG32                 :19;
} __rcpcsyspllcntl_bits;

/* RCPC USB PLL Control Register */
typedef struct {
  __REG32 USBLOOPDIV      : 6;
  __REG32 USBPREDIV       : 6;
  __REG32 USBFRANGE       : 1;
  __REG32 USBPDN          : 1;
  __REG32                 :18;
} __rcpcusbpllctl_bits;

/* RCPC SSP Control Register 0 */
typedef struct {
  __REG32 DSS             : 4;
  __REG32 FRF             : 2;
  __REG32 SPO             : 1;
  __REG32 SPH             : 1;
  __REG32 CPD             : 8;
  __REG32                 :16;
} __sspctrl0_bits;

/* SSP Control Register 1 */
typedef struct {
  __REG32 LBM             : 1;
  __REG32 SSE             : 1;
  __REG32 MS              : 1;
  __REG32 SOD             : 1;
  __REG32                 :28;
} __sspctrl1_bits;

/* SSP Data Register – Receive/Transmit FIFO Register */
typedef struct {
  __REG32 DATA            :16;
  __REG32                 :16;
} __sspdr_bits;

/* SSP Status Register */
typedef struct {
  __REG32 TFE             : 1;
  __REG32 TNF             : 1;
  __REG32 RNE             : 1;
  __REG32 REFI            : 1;
  __REG32 BSY             : 1;
  __REG32                 :27;
} __sspsr_bits;

/* SSP Clock Prescale Register */
typedef struct {
  __REG32 DVSR            : 8;
  __REG32                 :24;
} __sspcpsr_bits;

/* SSP Interrupt Mask Set and Clear Register */
typedef struct {
  __REG32 RORIM           : 1;
  __REG32 RTIM            : 1;
  __REG32 RXIM            : 1;
  __REG32 TXIM            : 1;
  __REG32                 :28;
} __sspimsc_bits;

/* SSP Raw Interrupt Status Register */
typedef struct {
  __REG32 RORRIS          : 1;
  __REG32 RTRIS           : 1;
  __REG32 RXRIS           : 1;
  __REG32 TXRIS           : 1;
  __REG32                 :28;
} __sspris_bits;

/* SSP Masked Interrupt Status Register */
typedef struct {
  __REG32 RORMIS          : 1;
  __REG32 RTMIS           : 1;
  __REG32 RXMIS           : 1;
  __REG32 TXMIS           : 1;
  __REG32                 :28;
} __sspmis_bits;

/* SSP Interrupt Clear Register */
typedef struct {
  __REG32 RORIC           : 1;
  __REG32 RTIC            : 1;
  __REG32                 :30;
} __sspicr_bits;

/* SSP DMA Control Register */
typedef struct {
  __REG32 RXDMAE          : 1;
  __REG32 TXDMAE          : 1;
  __REG32                 :30;
} __sspdcr_bits;

/* Timer 0 Control Register */
typedef struct {
  __REG32 CCL             : 1;
  __REG32 CS              : 1;
  __REG32 SEL             : 3;
  __REG32                 :27;
} __timerctrl0_bits;

/* Timer 0 Compare/Capture Control Register */
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
} __timercmpcapctrl_bits;

/* Timer 0 Interrupt Control Register */
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
} __timerinten0_bits;

/* Timer 0 Status Register */
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
} __timerstatus0_bits;

/* Timer 0 Counter Register */
typedef struct {
  __REG32 TM0CNT          :16;
  __REG32                 :16;
} __timercnt0_bits;

/* Timer 0 Compare Registers */
typedef struct {
  __REG32 TM0CMP          :16;
  __REG32                 :16;
} __timert0cmp0_bits;

/* Timer 0 Capture Registers */
typedef struct {
  __REG32 CAPTURE0        :16;
  __REG32                 :16;
} __timert0cmp_bits;

/* Timer 1 Counter Register */
typedef struct {
  __REG32 TM1CNT          :16;
  __REG32                 :16;
} __timercnt1_bits;

/* Timer 1 Compare Registers */
typedef struct {
  __REG32 TM1CMP          :16;
  __REG32                 :16;
} __timert1cmp_bits;

/* Timer 1 Capture Registers */
typedef struct {
  __REG32 CAPTURE1        :16;
  __REG32                 :16;
} __timert1cap_bits;

/* Timer 1 Control Register */ /* Timer 2 Control Register */
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
} __timerctrl_bits;

/* Timer 1 Interrupt Control Register */ /* Timer 2 Interrupt Control Register */
typedef struct {
  __REG32 OVF_EN          : 1;
  __REG32 CMP0_EN         : 1;
  __REG32 CMP1_EN         : 1;
  __REG32 CAPA_EN         : 1;
  __REG32 CAPB_EN         : 1;
  __REG32                 :27;
} __timerinten_bits;

/* Timer 1 Status Register */ /* Timer 2 Status Register */
typedef struct {
  __REG32 OVF_ST          : 1;
  __REG32 CMP0_ST         : 1;
  __REG32 CMP1_ST         : 1;
  __REG32 CAPA_ST         : 1;
  __REG32 CAPB_ST         : 1;
  __REG32                 :27;
} __timerstatus_bits;

/* Timer 2 Counter Register */
typedef struct {
  __REG32 TM2CNT          :16;
  __REG32                 :16;
} __timercnt2_bits;

/* Timer 2 Compare Registers */
typedef struct {
  __REG32 TM2CMP          :16;
  __REG32                 :16;
} __timert2cmp_bits;

/* Timer 2 Capture Registers */
typedef struct {
  __REG32 CAPTURE2        :16;
  __REG32                 :16;
} __timert2cap_bits;

/* UART Interrupt Mask Set/Clear Register UART0 */
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
} __uart0uartimsc_bits;

/* UART Raw Interrupt Status Register UART0 */
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
} __uart0uartris_bits;

/* UART Masked Interrupt Status Register UART0*/
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
} __uart0uartmis_bits;

/* UART Interrupt Clear Register UART0 */
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
} __uart0uarticr_bits;

/* UART Data Register */
typedef struct {
  __REG32 DATA            : 8;
  __REG32 FE              : 1;
  __REG32 PEAR            : 1;
  __REG32 BE              : 1;
  __REG32 OE              : 1;
  __REG32                 :20;
} __uartuartdr_bits;

/* UART Receive Status/Error Clear Register */
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
} __uartuartrsrecr_bits;

/* UART Flag Register */
typedef struct {
  __REG32                 : 3;
  __REG32 BUSY            : 1;
  __REG32 RXFE            : 1;
  __REG32 TXFF            : 1;
  __REG32 RXFF            : 1;
  __REG32 TXFE            : 1;
  __REG32                 :24;
} __uartuartfr_bits;

/* UART IrDA Low-Power Counter Register */
typedef struct {
  __REG32 ILPDVSR         : 8;
  __REG32                 :24;
} __uartuartilpr_bits;

/* UART Integer Baud Rate Divisor Register */
typedef struct {
  __REG32 BAUDDIVINT      :16;
  __REG32                 :16;
} __uartuartibrd_bits;

/* UART Fractional Baud Rate Divisor Register */
typedef struct {
  __REG32 FRAC            : 6;
  __REG32                 :26;
} __uartuartfbrd_bits;

/* UART Line Control Register */
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
} __uartuartlcrh_bits;

/* UART Control Register */
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
} __uartuartcr_bits;

/* UART Interrupt FIFO Level Select Register */
typedef struct {
  __REG32 TXIFLSEL        : 3;
  __REG32 RXIFLSEL        : 3;
  __REG32                 :26;
} __uartuartifls_bits;

/* UART Interrupt Mask Set/Clear Register */
typedef struct {
  __REG32                 : 4;
  __REG32 RXIM            : 1;
  __REG32 TXIM            : 1;
  __REG32 RTIM            : 1;
  __REG32 FEIM            : 1;
  __REG32 PEARIM          : 1;
  __REG32 BEIM            : 1;
  __REG32 OEIM            : 1;
  __REG32                 :21;
} __uartuartimsc_bits;

/* UART Raw Interrupt Status Register */
typedef struct {
  __REG32                 : 4;
  __REG32 RXRIS           : 1;
  __REG32 TXRIS           : 1;
  __REG32 RTRIS           : 1;
  __REG32 FERIS           : 1;
  __REG32 PEARIS          : 1;
  __REG32 BERIS           : 1;
  __REG32 OERIS           : 1;
  __REG32                 :21;
} __uartuartris_bits;

/* UART Masked Interrupt Status Register */
typedef struct {
  __REG32                 : 4;
  __REG32 RXMIS           : 1;
  __REG32 TXMIS           : 1;
  __REG32 RTMIS           : 1;
  __REG32 FEMIS           : 1;
  __REG32 PEARMIS         : 1;
  __REG32 BEMIS           : 1;
  __REG32 OEMIS           : 1;
  __REG32                 :21;
} __uartuartmis_bits;

/* UART Interrupt Clear Register */
typedef struct {
  __REG32                 : 4;
  __REG32 RXIC            : 1;
  __REG32 TXIC            : 1;
  __REG32 RTIC            : 1;
  __REG32 FEIC            : 1;
  __REG32 PEARIC          : 1;
  __REG32 BEIC            : 1;
  __REG32 OEIC            : 1;
  __REG32                 :21;
} __uartuarticr_bits;

/* UART DMA Control Register */
typedef struct {
  __REG32 RXDMAEN         : 1;
  __REG32 TXDMAEN         : 1;
  __REG32 DMAOE           : 1;
  __REG32                 :29;
} __uartdmactrl_bits;

/* Function Address Register */
typedef struct {
  __REG32 FUNCTION_ADDR   : 7;
  __REG32 ADDR_UPDATE     : 1;
  __REG32                 :24;
} __usbfar_bits;

/* Power Management Register */
typedef struct {
  __REG32 ENABLE_SUSPEND  : 1;
  __REG32 SUSPEND_MODE    : 1;
  __REG32 UC_RESUME       : 1;
  __REG32 USB_RESET       : 1;
  __REG32                 : 3;
  __REG32 SOF_UPDATE      : 1;
  __REG32                 :24;
} __usbpmr_bits;

/* Interrupt Register for Endpoint 0, 1, 2, and 3 */
typedef struct {
  __REG32 EP0IN           : 1;
  __REG32 EP1IN           : 1;
  __REG32 EP2IN           : 1;
  __REG32 EP3IN           : 1;
  __REG32                 :28;
} __usbiir_bits;

/*  Interrupt Register for OUT Endpoint 1 and 2 */
typedef struct {
  __REG32                 : 1;
  __REG32 EP1OUT          : 1;
  __REG32 EP2OUT          : 1;
  __REG32                 :29;
} __usboir_bits;

/* Interrupt Register for common USB interrupts */
typedef struct {
  __REG32 SUSINT          : 1;
  __REG32 RESINT          : 1;
  __REG32 URINT           : 1;
  __REG32 SOF             : 1;
  __REG32                 :28;
} __usbuir_bits;

/* IN Interrupt Enable Register */
typedef struct {
  __REG32 EP0INEN         : 1;
  __REG32 EP1INEN         : 1;
  __REG32 EP2INEN         : 1;
  __REG32 EP3INEN         : 1;
  __REG32                 :28;
} __usbiie_bits;

/* OUT Interrupt Enable Register */
typedef struct {
  __REG32                 : 1;
  __REG32 EP1OUTEN        : 1;
  __REG32 EP2OUTEN        : 1;
  __REG32                 :29;
} __usboie_bits;

/* Interrupt Enable Register */
typedef struct {
  __REG32 SUSINTEN        : 1;
  __REG32 RESINTEN        : 1;
  __REG32 URINTEN         : 1;
  __REG32 SOFINTEN        : 1;
  __REG32                 :28;
} __usbuie_bits;

/* Frame Number Registers */
typedef struct {
  __REG32 FRAME1          : 8;
  __REG32                 :24;
} __usbframe1_bits;

typedef struct {
  __REG32 FRAME2          : 3;
  __REG32                 :29;
} __usbframe2_bits;

/* Index Register */
typedef struct {
  __REG32 INDEX           : 4;
  __REG32                 :28;
} __usbindex_bits;

/* IN Maximum Packet Size Register */
typedef struct {
  __REG32 INMAXP          : 8;
  __REG32                 :24;
} __usbinmaxp_bits;

/* Control Status Register 1 for IN EP 1, 2, and 3 */ /* Control Status Register for EP 0 */
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
} __usbcsr0incsr1_bits;

/* Control Status Register 2 for IN EP 1, 2, and 3 */
typedef struct {
  __REG32                 : 3;
  __REG32 FRC_DATA_TOG    : 1;
  __REG32 USB_DMA_EN      : 1;
  __REG32 MODE            : 1;
  __REG32 ISO             : 1;
  __REG32 AUTO_SET        : 1;
  __REG32                 :24;
} __usbincsr2_bits;

/* OUT Maximum Packet Size Register EP 1 and 2 */
typedef struct {
  __REG32 OUTMAXP         : 8;
  __REG32                 :24;
} __usboutmaxp_bits;

/* Control Status Register 1 for OUT EP1 and EP2 */
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
} __usboutcsr1_bits;

/* Control Status Register 2 for OUT EP1 and EP 2 */
typedef struct {
  __REG32                 : 4;
  __REG32 DMA_MODE        : 1;
  __REG32 USB_DMA_EN      : 1;
  __REG32 ISO             : 1;
  __REG32 AUTO_CLR        : 1;
  __REG32                 :24;
} __usboutcsr2_bits;

/* Count 0 Register */ /* Count 1 Register */
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
} __usboutcount_bits;

/* Count 1 Register */ 
typedef struct {
  __REG32 OUTCOUNT2       : 3;
  __REG32                 :29;
} __usboutcount2_bits;

/* FIFOs for Endpoints 0-3 */
typedef struct {
  __REG32 FIFO            : 8;
  __REG32                 :24;
} __usbepfifo_bits;

/* Pending DMA Interrupts Register */
typedef struct {
  __REG32 INTR1           : 1;
  __REG32 INTR2           : 1;
  __REG32 INTR3           : 1;
  __REG32 INTR4           : 1;
  __REG32 INTR5           : 1;
  __REG32 INTR6           : 1;
  __REG32                 :26;
} __usbintr_bits;

/* DMA Channel x Control Register */
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
} __usbcntl_bits;

/* DMA Channel 1 AHB Memory Address Register */
typedef struct {
  __REG32 ADDR1           :32;
} __usbaddr1_bits;

/* DMA Channel 2 AHB Memory Address Register */
typedef struct {
  __REG32 ADDR2           :32;
} __usbaddr2_bits;

/* DMA Channel 3 AHB Memory Address Register */
typedef struct {
  __REG32 ADDR3           :32;
} __usbaddr3_bits;

/* DMA Channel 4 AHB Memory Address Register */
typedef struct {
  __REG32 ADDR4           :32;
} __usbaddr4_bits;

/* DMA Channel 5 AHB Memory Address Register */
typedef struct {
  __REG32 ADDR5           :32;
} __usbaddr5_bits;

/* DMA Channel 6 AHB Memory Address Register */
typedef struct {
  __REG32 ADDR6           :32;
} __usbaddr6_bits;

/* DMA Channel 1 Byte Count Register */
typedef struct {
  __REG32 COUNT1          :32;
} __usbcount1_bits;

/* DMA Channel 2 Byte Count Register */
typedef struct {
  __REG32 COUNT2          :32;
} __usbcount2_bits;

/* DMA Channel 3 Byte Count Register */
typedef struct {
  __REG32 COUNT3          :32;
} __usbcount3_bits;

/* DMA Channel 4 Byte Count Register */
typedef struct {
  __REG32 COUNT4          :32;
} __usbcount4_bits;

/* DMA Channel 5 Byte Count Register */
typedef struct {
  __REG32 COUNT5          :32;
} __usbcount5_bits;

/* DMA Channel 6 Byte Count Register */
typedef struct {
  __REG32 COUNT6          :32;
} __usbcount6_bits;

/* IRQ Status Register */
typedef struct {
  __REG32 IRQStatus       :32;
} __vicirqstatus_bits;

/* FIQ Status Register */
typedef struct {
  __REG32 FIQStatus       :32;
} __vicfiqstatus_bits;

/* Raw Interrupt Status Register */
typedef struct {
  __REG32 RawInterrupt    :32;
} __vicrawintr_bits;

/* Interrupt Select Register */
typedef struct {
  __REG32 IntSelect       :32;
} __vicintselect_bits;

/* Interrupt Enable Register */
typedef struct {
  __REG32 IntEnable       :32;
} __vicintenable_bits;

/* Interrupt Enable Clear Register */
typedef struct {
  __REG32 IntEnableClear  :32;
} __vicintenclear_bits;

/* Software Interrupt Register */
typedef struct {
  __REG32 SoftInt         :32;
} __vicsoftint_bits;

/* Software Interrupt Clear Register */
typedef struct {
  __REG32 SoftIntClear    :32;
} __vicsoftintclear_bits;

/* Vector Address Register */
typedef struct {
  __REG32 VectorAddr      :32;
} __vicvectaddr_bits;

/* Default Vector Address Register */
typedef struct {
  __REG32 DefaultVectorAddr :32;
} __vicdefvectaddr_bits;

/* Vector Control Registers */
typedef struct {
  __REG32 IntSource       : 5;
  __REG32 E               : 1;
  __REG32                 :26;
} __vicvectctrl_bits;

/* Interrupt Test Output Register */
typedef struct {
  __REG32                 : 6;
  __REG32 VF              : 1;
  __REG32 VI              : 1;
  __REG32                 :24;
} __vicitop_bits;

/* WDT Control Register */
typedef struct {
  __REG32 EN              : 1;
  __REG32 IF              : 1;
  __REG32                 : 1;
  __REG32 FRZ             : 1;
  __REG32 TOP             : 4;
  __REG32                 :24;
} __wdtctl_bits;

/* WDT Counter Reset Register */
typedef struct {
  __REG32 RST             :16;
  __REG32                 :16;
} __wdtrst_bits;

/* WDT Status Register */
typedef struct {
  __REG32                 : 4;
  __REG32 IF              : 1;
  __REG32                 : 2;
  __REG32 INT             : 1;
  __REG32                 :24;
} __wdtstatus_bits;

/* Current Watchdog Count Registers */
typedef struct {
  __REG32 COUNT           : 8;
  __REG32                 :24;
} __wdtcount_bits;

#endif	/* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/

/***************************************************************************
 **
 **  EMC : External Memory Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(EMC_CONTROL,              0xFFFF1000, __READ_WRITE, __emccontrol_bits        ); 
__IO_REG32_BIT(EMC_STATUS,               0xFFFF1004, __READ,       __emcstatus_bits         ); 
__IO_REG32_BIT(EMC_CONFIG,               0xFFFF1008, __READ_WRITE, __emcconfig_bits         ); 
__IO_REG32_BIT(DYNMCTRL,                 0xFFFF1020, __READ_WRITE, __emcdynmctrl_bits       );
__IO_REG32_BIT(DYNMREF,                  0xFFFF1024, __READ_WRITE, __emcdynmref_bits        ); 
__IO_REG32_BIT(DYNMRCON,                 0xFFFF1028, __READ_WRITE, __emc_dynmrcon_bits      );
__IO_REG32_BIT(PRECHARGE,                0xFFFF1030, __READ_WRITE, __emcprecharge_bits      ); 
__IO_REG32_BIT(DYNM2PRE,                 0xFFFF1034, __READ_WRITE, __emcdynm2pre_bits       ); 
__IO_REG32_BIT(REFEXIT,                  0xFFFF1038, __READ_WRITE, __emcrefexit_bits        ); 
__IO_REG32_BIT(DOACTIVE,                 0xFFFF103C, __READ_WRITE, __emcdoactive_bits       ); 
__IO_REG32_BIT(DIACTIVE,                 0xFFFF1040, __READ_WRITE, __emcdiactive_bits       ); 
__IO_REG32_BIT(DWRT,                     0xFFFF1044, __READ_WRITE, __emcdwrt_bits           ); 
__IO_REG32_BIT(DYNACTCMD,                0xFFFF1048, __READ_WRITE, __emcdynactcmd_bits      ); 
__IO_REG32_BIT(DYNAUTO,                  0xFFFF104C, __READ_WRITE, __emcdynauto_bits        ); 
__IO_REG32_BIT(DYNREFEXIT,               0xFFFF1050, __READ_WRITE, __emcdynrefexit_bits     ); 
__IO_REG32_BIT(DYNACTIVEAB,              0xFFFF1054, __READ_WRITE, __emcdynactiveab_bits    ); 
__IO_REG32_BIT(DYNAMICMRD,               0xFFFF1058, __READ_WRITE, __emcdynamicmrd_bits     ); 
__IO_REG32_BIT(WAIT,                     0xFFFF1080, __READ_WRITE, __emcwait_bits           ); 
__IO_REG32_BIT(DYNCFG0,                  0xFFFF1100, __READ_WRITE, __emcdyncfg_bits         ); 
__IO_REG32_BIT(DYNRASCAS0,               0xFFFF1104, __READ_WRITE, __emcdynrascas_bits      ); 
__IO_REG32_BIT(DYNCFG1,                  0xFFFF1120, __READ_WRITE, __emcdyncfg_bits         ); 
__IO_REG32_BIT(DYNRASCAS1,               0xFFFF1124, __READ_WRITE, __emcdynrascas_bits      ); 
__IO_REG32_BIT(SCONFIG0,                 0xFFFF1200, __READ_WRITE, __emcsconfig_bits        ); 
__IO_REG32_BIT(SWAITWEN0,                0xFFFF1204, __READ_WRITE, __emcswaitwen_bits       ); 
__IO_REG32_BIT(SWAITOEN0,                0xFFFF1208, __READ_WRITE, __emcswaitoen_bits       ); 
__IO_REG32_BIT(SWAITRD0,                 0xFFFF120C, __READ_WRITE, __emcswaitrd_bits        ); 
__IO_REG32_BIT(SWAITPAGE0,               0xFFFF1210, __READ_WRITE, __emcswaitpage_bits      ); 
__IO_REG32_BIT(SWAITWR0,                 0xFFFF1214, __READ_WRITE, __emcswaitwr_bits        ); 
__IO_REG32_BIT(STURN0,                   0xFFFF1218, __READ_WRITE, __emcsturn_bits          ); 
__IO_REG32_BIT(SCONFIG1,                 0xFFFF1220, __READ_WRITE, __emcsconfig_bits        );
__IO_REG32_BIT(SWAITWEN1,                0xFFFF1224, __READ_WRITE, __emcswaitwen_bits       ); 
__IO_REG32_BIT(SWAITOEN1,                0xFFFF1228, __READ_WRITE, __emcswaitoen_bits       ); 
__IO_REG32_BIT(SWAITRD1,                 0xFFFF122C, __READ_WRITE, __emcswaitrd_bits        ); 
__IO_REG32_BIT(SWAITPAGE1,               0xFFFF1230, __READ_WRITE, __emcswaitpage_bits      ); 
__IO_REG32_BIT(SWAITWR1,                 0xFFFF1234, __READ_WRITE, __emcswaitwr_bits        ); 
__IO_REG32_BIT(STURN1,                   0xFFFF1238, __READ_WRITE, __emcsturn_bits          ); 
__IO_REG32_BIT(SCONFIG2,                 0xFFFF1240, __READ_WRITE, __emcsconfig_bits        ); 
__IO_REG32_BIT(SWAITWEN2,                0xFFFF1244, __READ_WRITE, __emcswaitwen_bits       ); 
__IO_REG32_BIT(SWAITOEN2,                0xFFFF1248, __READ_WRITE, __emcswaitoen_bits       ); 
__IO_REG32_BIT(SWAITRD2,                 0xFFFF124C, __READ_WRITE, __emcswaitrd_bits        ); 
__IO_REG32_BIT(SWAITPAGE2,               0xFFFF1250, __READ_WRITE, __emcswaitpage_bits      ); 
__IO_REG32_BIT(SWAITWR2,                 0xFFFF1254, __READ_WRITE, __emcswaitwr_bits        ); 
__IO_REG32_BIT(STURN2,                   0xFFFF1258, __READ_WRITE, __emcsturn_bits          ); 
__IO_REG32_BIT(SCONFIG3,                 0xFFFF1260, __READ_WRITE, __emcsconfig_bits        );
__IO_REG32_BIT(SWAITWEN3,                0xFFFF1264, __READ_WRITE, __emcswaitwen_bits       ); 
__IO_REG32_BIT(SWAITOEN3,                0xFFFF1268, __READ_WRITE, __emcswaitoen_bits       ); 
__IO_REG32_BIT(SWAITRD3,                 0xFFFF126C, __READ_WRITE, __emcswaitrd_bits        ); 
__IO_REG32_BIT(SWAITPAGE3,               0xFFFF1270, __READ_WRITE, __emcswaitpage_bits      ); 
__IO_REG32_BIT(SWAITWR3,                 0xFFFF1274, __READ_WRITE, __emcswaitwr_bits        ); 
__IO_REG32_BIT(STURN3,                   0xFFFF1278, __READ_WRITE, __emcsturn_bits          ); 

/***************************************************************************
 **
 **  CLCDC : Color LCD Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(TIMING0,                  0xFFFF4000, __READ_WRITE, __clcdctiming0_bits      ); 
__IO_REG32_BIT(TIMING1,                  0xFFFF4004, __READ_WRITE, __clcdctiming1_bits      ); 
__IO_REG32_BIT(TIMING2,                  0xFFFF4008, __READ_WRITE, __clcdctiming2_bits      ); 
__IO_REG32_BIT(UPBASE,                   0xFFFF4010, __READ_WRITE, __clcdcupbase_bits       ); 
__IO_REG32_BIT(LPBASE,                   0xFFFF4014, __READ_WRITE, __clcdclpbase_bits       ); 
__IO_REG32_BIT(INTREN,                   0xFFFF4018, __READ,       __clcdcintren_bits       ); 
__IO_REG32_BIT(CLCDC_CTRL,               0xFFFF401C, __READ_WRITE, __clcdcctrl_bits         ); 
__IO_REG32_BIT(CLCDC_STATUS,             0xFFFF4020, __READ,       __clcdcstatus_bits       ); 
__IO_REG32_BIT(INTERRUPT,                0xFFFF4024, __READ,       __clcdcinterrupt_bits    ); 
__IO_REG32_BIT(CLCDC_INTCLR,             0xFFFF4028, __WRITE,      __clcdcintclr_bits       ); 
__IO_REG32_BIT(UPCURR,                   0xFFFF402C, __READ,       __clcdcpcurr_bits        );  
__IO_REG32_BIT(LPCURR,                   0xFFFF4030, __READ,       __clcdcpcurr_bits        ); 
__IO_REG32_BIT(PALETTE_1_0,              0xFFFF4200, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_3_2,              0xFFFF4204, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_5_4,              0xFFFF4208, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_7_6,              0xFFFF420C, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_9_8,              0xFFFF4210, __READ_WRITE, __clcdcpalette_bits      );  
__IO_REG32_BIT(PALETTE_11_10,            0xFFFF4214, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_13_12,            0xFFFF4218, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_15_14,            0xFFFF421C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_17_16,            0xFFFF4220, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_19_18,            0xFFFF4224, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_21_20,            0xFFFF4228, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_23_22,            0xFFFF422C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_25_24,            0xFFFF4230, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_27_26,            0xFFFF4234, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_29_28,            0xFFFF4238, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_31_30,            0xFFFF423C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_33_32,            0xFFFF4240, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_35_34,            0xFFFF4244, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_37_36,            0xFFFF4248, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_39_38,            0xFFFF424C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_41_40,            0xFFFF4250, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_43_42,            0xFFFF4254, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_45_44,            0xFFFF4258, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_47_46,            0xFFFF425C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_49_48,            0xFFFF4260, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_51_50,            0xFFFF4264, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_53_52,            0xFFFF4268, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_55_54,            0xFFFF426C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_57_56,            0xFFFF4270, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_59_58,            0xFFFF4274, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_61_60,            0xFFFF4278, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_63_62,            0xFFFF427C, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_65_64,            0xFFFF4280, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_67_66,            0xFFFF4284, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_69_68,            0xFFFF4288, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_71_70,            0xFFFF428C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_73_72,            0xFFFF4290, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_75_74,            0xFFFF4294, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_77_76,            0xFFFF4298, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_79_78,            0xFFFF429C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_81_80,            0xFFFF42A0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_83_82,            0xFFFF42A4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_85_84,            0xFFFF42A8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_87_86,            0xFFFF42AC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_89_88,            0xFFFF42B0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_91_90,            0xFFFF42B4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_93_92,            0xFFFF42B8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_95_94,            0xFFFF42BC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_97_96,            0xFFFF42C0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_99_98,            0xFFFF42C4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_101_100,          0xFFFF42C8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_103_102,          0xFFFF42CC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_105_104,          0xFFFF42D0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_107_106,          0xFFFF42D4, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_109_108,          0xFFFF42D8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_111_110,          0xFFFF42DC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_113_112,          0xFFFF42E0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_115_114,          0xFFFF42E4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_117_116,          0xFFFF42E8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_119_118,          0xFFFF42EC, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_121_120,          0xFFFF42F0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_123_122,          0xFFFF42F4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_125_124,          0xFFFF42F8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_127_126,          0xFFFF42FC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_129_128,          0xFFFF4300, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_131_130,          0xFFFF4304, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_133_132,          0xFFFF4308, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_135_134,          0xFFFF430C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_137_136,          0xFFFF4310, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_139_138,          0xFFFF4314, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_141_140,          0xFFFF4318, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_143_142,          0xFFFF431C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_145_144,          0xFFFF4320, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_147_146,          0xFFFF4324, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_149_148,          0xFFFF4328, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_151_150,          0xFFFF432C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_153_152,          0xFFFF4330, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_155_154,          0xFFFF4334, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_157_156,          0xFFFF4338, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_159_158,          0xFFFF433C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_161_160,          0xFFFF4340, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_163_162,          0xFFFF4344, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_165_164,          0xFFFF4348, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_167_166,          0xFFFF434C, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_169_168,          0xFFFF4350, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_171_170,          0xFFFF4354, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_173_172,          0xFFFF4358, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_175_174,          0xFFFF435C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_177_176,          0xFFFF4360, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_179_178,          0xFFFF4364, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_181_180,          0xFFFF4368, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_183_182,          0xFFFF436C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_185_184,          0xFFFF4370, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_187_186,          0xFFFF4374, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_189_188,          0xFFFF4378, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_191_190,          0xFFFF437C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_193_192,          0xFFFF4380, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_195_194,          0xFFFF4384, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_197_196,          0xFFFF4388, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_199_198,          0xFFFF438C, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_201_200,          0xFFFF4390, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_203_202,          0xFFFF4394, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_205_204,          0xFFFF4398, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_207_206,          0xFFFF439C, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_209_208,          0xFFFF43A0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_211_210,          0xFFFF43A4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_213_212,          0xFFFF43A8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_215_214,          0xFFFF43AC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_217_216,          0xFFFF43B0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_219_218,          0xFFFF43B4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_221_220,          0xFFFF43B8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_223_222,          0xFFFF43BC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_225_224,          0xFFFF43C0, __READ_WRITE, __clcdcpalette_bits      );
__IO_REG32_BIT(PALETTE_227_226,          0xFFFF43C4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_229_228,          0xFFFF43C8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_231_230,          0xFFFF43CC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_233_232,          0xFFFF43D0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_235_234,          0xFFFF43D4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_237_236,          0xFFFF43D8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_239_238,          0xFFFF43DC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_241_240,          0xFFFF43E0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_243_242,          0xFFFF43E4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_245_244,          0xFFFF43E8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_247_246,          0xFFFF43EC, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_249_248,          0xFFFF43F0, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_251_250,          0xFFFF43F4, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_253_252,          0xFFFF43F8, __READ_WRITE, __clcdcpalette_bits      ); 
__IO_REG32_BIT(PALETTE_255_254,          0xFFFF43FC, __READ_WRITE, __clcdcpalette_bits      ); 

/***************************************************************************
 **
 **  USB : Universal Serial Bus Device
 **
 ***************************************************************************/
__IO_REG32_BIT(_FAR,                     0xFFFF5000, __READ_WRITE, __usbfar_bits            ); 
__IO_REG32_BIT(PMR,                      0xFFFF5004, __READ_WRITE, __usbpmr_bits            ); 
__IO_REG32_BIT(IIR,                      0xFFFF5008, __READ,       __usbiir_bits            ); 
__IO_REG32_BIT(OIR,                      0xFFFF5010, __READ,       __usboir_bits            ); 
__IO_REG32_BIT(UIR,                      0xFFFF5018, __READ,       __usbuir_bits            ); 
__IO_REG32_BIT(IIE,                      0xFFFF501C, __READ_WRITE, __usbiie_bits            ); 
__IO_REG32_BIT(OIE,                      0xFFFF5024, __READ_WRITE, __usboie_bits            ); 
__IO_REG32_BIT(UIE,                      0xFFFF502C, __READ_WRITE, __usbuie_bits            ); 
__IO_REG32_BIT(FRAME1,                   0xFFFF5030, __READ,       __usbframe1_bits         ); 
__IO_REG32_BIT(FRAME2,                   0xFFFF5034, __READ,       __usbframe2_bits         ); 
__IO_REG32_BIT(INDEX,                    0xFFFF5038, __READ_WRITE, __usbindex_bits          ); 
__IO_REG32_BIT(INMAXP,                   0xFFFF5040, __READ_WRITE, __usbinmaxp_bits         ); 
__IO_REG32_BIT(CSR0_INCSR1,              0xFFFF5044, __READ_WRITE, __usbcsr0incsr1_bits     ); 
__IO_REG32_BIT(INCSR2,                   0xFFFF5048, __READ_WRITE, __usbincsr2_bits         ); 
__IO_REG32_BIT(OUTMAXP,                  0xFFFF504C, __READ_WRITE, __usboutmaxp_bits        ); 
__IO_REG32_BIT(OUTCSR1,                  0xFFFF5050, __READ_WRITE, __usboutcsr1_bits        ); 
__IO_REG32_BIT(OUTCSR2,                  0xFFFF5054, __READ_WRITE, __usboutcsr2_bits        ); 
__IO_REG32_BIT(OUTCOUNT,                 0xFFFF5058, __READ,       __usboutcount_bits       ); 
__IO_REG32_BIT(OUTCOUNT2,                0xFFFF505C, __READ,       __usboutcount2_bits      ); 
__IO_REG32_BIT(EP0FIFO,                  0xFFFF5080, __READ_WRITE, __usbepfifo_bits         ); 
__IO_REG32_BIT(EP1FIFO,                  0xFFFF5084, __READ_WRITE, __usbepfifo_bits         ); 
__IO_REG32_BIT(EP2FIFO,                  0xFFFF5088, __READ_WRITE, __usbepfifo_bits         );
__IO_REG32_BIT(EP3FIFO,                  0xFFFF508C, __READ_WRITE, __usbepfifo_bits         ); 
__IO_REG32_BIT(INTR,                     0xFFFF5200, __READ,       __usbintr_bits           );
__IO_REG32_BIT(USB_CNTL1,                0xFFFF5204, __READ_WRITE, __usbcntl_bits           ); 
__IO_REG32_BIT(USB_ADDR1,                0xFFFF5208, __READ_WRITE, __usbaddr1_bits          ); 
__IO_REG32_BIT(USB_COUNT1,               0xFFFF520C, __READ_WRITE, __usbcount1_bits         ); 
__IO_REG32_BIT(USB_CNTL2,                0xFFFF5214, __READ_WRITE, __usbcntl_bits           ); 
__IO_REG32_BIT(USB_ADDR2,                0xFFFF5218, __READ_WRITE, __usbaddr2_bits          ); 
__IO_REG32_BIT(USB_COUNT2,               0xFFFF521C, __READ_WRITE, __usbcount2_bits         ); 
__IO_REG32_BIT(USB_CNTL3,                0xFFFF5224, __READ_WRITE, __usbcntl_bits           ); 
__IO_REG32_BIT(USB_ADDR3,                0xFFFF5228, __READ_WRITE, __usbaddr3_bits          ); 
__IO_REG32_BIT(USB_COUNT3,               0xFFFF522C, __READ_WRITE, __usbcount3_bits         ); 
__IO_REG32_BIT(USB_CNTL4,                0xFFFF5234, __READ_WRITE, __usbcntl_bits           ); 
__IO_REG32_BIT(USB_ADDR4,                0xFFFF5238, __READ_WRITE, __usbaddr4_bits          ); 
__IO_REG32_BIT(USB_COUNT4,               0xFFFF523C, __READ_WRITE, __usbcount4_bits         ); 
__IO_REG32_BIT(USB_CNTL5,                0xFFFF5244, __READ_WRITE, __usbcntl_bits           ); 
__IO_REG32_BIT(USB_ADDR5,                0xFFFF5248, __READ_WRITE, __usbaddr5_bits          ); 
__IO_REG32_BIT(USB_COUNT5,               0xFFFF524C, __READ_WRITE, __usbcount5_bits         ); 
__IO_REG32_BIT(USB_CNTL6,                0xFFFF5254, __READ_WRITE, __usbcntl_bits           ); 
__IO_REG32_BIT(USB_ADDR6,                0xFFFF5258, __READ_WRITE, __usbaddr6_bits          ); 
__IO_REG32_BIT(USB_COUNT6,               0xFFFF525C, __READ_WRITE, __usbcount6_bits         ); 

/***************************************************************************
 **
 **  VIC : Vectored Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQSTATUS,                0xFFFFF000, __READ,       __vicirqstatus_bits      ); 
__IO_REG32_BIT(FIQSTATUS,                0xFFFFF004, __READ,       __vicfiqstatus_bits      ); 
__IO_REG32_BIT(RAWINTR,                  0xFFFFF008, __READ,       __vicrawintr_bits        ); 
__IO_REG32_BIT(INTSELECT,                0xFFFFF00C, __READ_WRITE, __vicintselect_bits      );
__IO_REG32_BIT(INTENABLE,                0xFFFFF010, __READ_WRITE, __vicintenable_bits      ); 
__IO_REG32_BIT(INTENCLEAR,               0xFFFFF014, __WRITE,      __vicintenclear_bits     ); 
__IO_REG32_BIT(SOFTINT,                  0xFFFFF018, __READ_WRITE, __vicsoftint_bits        ); 
__IO_REG32_BIT(SOFTINT_CLEAR,            0xFFFFF01C, __WRITE,      __vicsoftintclear_bits   );
__IO_REG32_BIT(VECTADDR,                 0xFFFFF030, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(DEFVECTADDR,              0xFFFFF034, __READ_WRITE, __vicdefvectaddr_bits    ); 
__IO_REG32_BIT(VECTADDR0,                0xFFFFF100, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR1,                0xFFFFF104, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR2,                0xFFFFF108, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR3,                0xFFFFF10C, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR4,                0xFFFFF110, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR5,                0xFFFFF114, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR6,                0xFFFFF118, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR7,                0xFFFFF11C, __READ_WRITE, __vicvectaddr_bits       );
__IO_REG32_BIT(VECTADDR8,                0xFFFFF120, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR9,                0xFFFFF124, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR10,               0xFFFFF128, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR11,               0xFFFFF12C, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR12,               0xFFFFF130, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR13,               0xFFFFF134, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR14,               0xFFFFF138, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTADDR15,               0xFFFFF13C, __READ_WRITE, __vicvectaddr_bits       ); 
__IO_REG32_BIT(VECTCTRL0,                0xFFFFF200, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL1,                0xFFFFF204, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL2,                0xFFFFF208, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL3,                0xFFFFF20C, __READ_WRITE, __vicvectctrl_bits       );
__IO_REG32_BIT(VECTCTRL4,                0xFFFFF210, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL5,                0xFFFFF214, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL6,                0xFFFFF218, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL7,                0xFFFFF21C, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL8,                0xFFFFF220, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL9,                0xFFFFF224, __READ_WRITE, __vicvectctrl_bits       );
__IO_REG32_BIT(VECTCTRL10,               0xFFFFF228, __READ_WRITE, __vicvectctrl_bits       );
__IO_REG32_BIT(VECTCTRL11,               0xFFFFF22C, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL12,               0xFFFFF230, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL13,               0xFFFFF234, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL14,               0xFFFFF238, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(VECTCTRL15,               0xFFFFF23C, __READ_WRITE, __vicvectctrl_bits       ); 
__IO_REG32_BIT(ITOP,                     0xFFFFF30C, __READ      , __vicitop_bits           ); 

/***************************************************************************
 **
 **  UART : UART0
 **
 ***************************************************************************/
__IO_REG32_BIT(UART0_UARTDR,             0xFFFC0000, __READ_WRITE, __uartuartdr_bits        ); 
__IO_REG32_BIT(UART0_UARTRSR_UARTECR,    0xFFFC0004, __READ_WRITE, __uartuartrsrecr_bits    ); 
__IO_REG32_BIT(UART0_UARTFR,             0xFFFC0018, __READ,       __uartuartfr_bits        ); 
__IO_REG32_BIT(UART0_UARTILPR,           0xFFFC0020, __READ_WRITE, __uartuartilpr_bits      ); 
__IO_REG32_BIT(UART0_UARTIBRD,           0xFFFC0024, __READ_WRITE, __uartuartibrd_bits      ); 
__IO_REG32_BIT(UART0_UARTFBRD,           0xFFFC0028, __READ_WRITE, __uartuartfbrd_bits      ); 
__IO_REG32_BIT(UART0_UARTLCR_H,          0xFFFC002C, __READ_WRITE, __uartuartlcrh_bits      ); 
__IO_REG32_BIT(UART0_UARTCR,             0xFFFC0030, __READ_WRITE, __uartuartcr_bits        ); 
__IO_REG32_BIT(UART0_UARTIFLS,           0xFFFC0034, __READ_WRITE, __uartuartifls_bits      ); 
__IO_REG32_BIT(UART0_UARTIMSC,           0xFFFC0038, __READ_WRITE, __uart0uartimsc_bits     ); 
__IO_REG32_BIT(UART0_UARTRIS,            0xFFFC003C, __READ,       __uart0uartris_bits      ); 
__IO_REG32_BIT(UART0_UARTMIS,            0xFFFC0040, __READ,       __uart0uartmis_bits      );
__IO_REG32_BIT(UART0_UARTICR,            0xFFFC0044, __READ_WRITE, __uart0uarticr_bits      ); 
__IO_REG32_BIT(UART0_DMACTRL,            0xFFFC0048, __READ_WRITE, __uartdmactrl_bits       ); 

/***************************************************************************
 **
 **  UART : UART1
 **
 ***************************************************************************/
__IO_REG32_BIT(UART1_UARTDR,             0xFFFC1000, __READ_WRITE, __uartuartdr_bits        ); 
__IO_REG32_BIT(UART1_UARTRSR_UARTECR,    0xFFFC1004, __READ_WRITE, __uartuartrsrecr_bits    ); 
__IO_REG32_BIT(UART1_UARTFR,             0xFFFC1018, __READ,       __uartuartfr_bits        ); 
__IO_REG32_BIT(UART1_UARTILPR,           0xFFFC1020, __READ_WRITE, __uartuartilpr_bits      ); 
__IO_REG32_BIT(UART1_UARTIBRD,           0xFFFC1024, __READ_WRITE, __uartuartibrd_bits      ); 
__IO_REG32_BIT(UART1_UARTFBRD,           0xFFFC1028, __READ_WRITE, __uartuartfbrd_bits      ); 
__IO_REG32_BIT(UART1_UARTLCR_H,          0xFFFC102C, __READ_WRITE, __uartuartlcrh_bits      ); 
__IO_REG32_BIT(UART1_UARTCR,             0xFFFC1030, __READ_WRITE, __uartuartcr_bits        ); 
__IO_REG32_BIT(UART1_UARTIFLS,           0xFFFC1034, __READ_WRITE, __uartuartifls_bits      ); 
__IO_REG32_BIT(UART1_UARTIMSC,           0xFFFC1038, __READ_WRITE, __uartuartimsc_bits      ); 
__IO_REG32_BIT(UART1_UARTRIS,            0xFFFC103C, __READ,       __uartuartris_bits       ); 
__IO_REG32_BIT(UART1_UARTMIS,            0xFFFC1040, __READ,       __uartuartmis_bits       ); 
__IO_REG32_BIT(UART1_UARTICR,            0xFFFC1044, __READ_WRITE, __uartuarticr_bits       ); 

/***************************************************************************
 **
 **  UART : UART2
 **
 ***************************************************************************/
__IO_REG32_BIT(UART2_UARTDR,             0xFFFC2000, __READ_WRITE, __uartuartdr_bits        ); 
__IO_REG32_BIT(UART2_UARTRSR_UARTECR,    0xFFFC2004, __READ_WRITE, __uartuartrsrecr_bits    ); 
__IO_REG32_BIT(UART2_UARTFR,             0xFFFC2018, __READ,       __uartuartfr_bits        ); 
__IO_REG32_BIT(UART2_UARTILPR,           0xFFFC2020, __READ_WRITE, __uartuartilpr_bits      ); 
__IO_REG32_BIT(UART2_UARTIBRD,           0xFFFC2024, __READ_WRITE, __uartuartibrd_bits      ); 
__IO_REG32_BIT(UART2_UARTFBRD,           0xFFFC2028, __READ_WRITE, __uartuartfbrd_bits      ); 
__IO_REG32_BIT(UART2_UARTLCR_H,          0xFFFC202C, __READ_WRITE, __uartuartlcrh_bits      ); 
__IO_REG32_BIT(UART2_UARTCR,             0xFFFC2030, __READ_WRITE, __uartuartcr_bits        ); 
__IO_REG32_BIT(UART2_UARTIFLS,           0xFFFC2034, __READ_WRITE, __uartuartifls_bits      ); 
__IO_REG32_BIT(UART2_UARTIMSC,           0xFFFC2038, __READ_WRITE, __uartuartimsc_bits      ); 
__IO_REG32_BIT(UART2_UARTRIS,            0xFFFC203C, __READ,       __uartuartris_bits       ); 
__IO_REG32_BIT(UART2_UARTMIS,            0xFFFC2040, __READ,       __uartuartmis_bits       ); 
__IO_REG32_BIT(UART2_UARTICR,            0xFFFC2044, __READ_WRITE, __uartuarticr_bits       ); 

/***************************************************************************
 **
 ** ADC : ADC and Brownout Detector 
 **
 ***************************************************************************/
__IO_REG32_BIT(HW,                       0xFFFC3000, __READ,       __adchw_bits             ); 
__IO_REG32_BIT(LW,                       0xFFFC3004, __READ,       __adclw_bits             ); 
__IO_REG32_BIT(RR,                       0xFFFC3008, __READ,       __adcrr_bits             ); 
__IO_REG32_BIT(IM,                       0xFFFC300C, __READ_WRITE, __adcim_bits             ); 
__IO_REG32_BIT(_PC,                      0xFFFC3010, __READ_WRITE, __adcpc_bits             ); 
__IO_REG32_BIT(GC,                       0xFFFC3014, __READ_WRITE, __adcgc_bits             ); 
__IO_REG32_BIT(GS,                       0xFFFC3018, __READ_WRITE, __adcgs_bits             ); 
__IO_REG32_BIT(IS,                       0xFFFC301C, __READ,       __adcis_bits             ); 
__IO_REG32_BIT(FS,                       0xFFFC3020, __READ,       __adcfs_bits             ); 
__IO_REG16_BIT(HWCB0,                    0xFFFC3024, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB1,                    0xFFFC3028, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB2,                    0xFFFC302C, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB3,                    0xFFFC3030, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB4,                    0xFFFC3034, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB5,                    0xFFFC3038, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB6,                    0xFFFC303C, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB7,                    0xFFFC3040, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB8,                    0xFFFC3044, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB9,                    0xFFFC3048, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB10,                   0xFFFC304C, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB11,                   0xFFFC3050, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB12,                   0xFFFC3054, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB13,                   0xFFFC3058, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB14,                   0xFFFC305C, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(HWCB15,                   0xFFFC3060, __READ_WRITE, __adchwcbx_bits          ); 
__IO_REG16_BIT(LWCB0,                    0xFFFC3064, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB1,                    0xFFFC3068, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB2,                    0xFFFC306C, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB3,                    0xFFFC3070, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB4,                    0xFFFC3074, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB5,                    0xFFFC3078, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB6,                    0xFFFC307C, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB7,                    0xFFFC3080, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB8,                    0xFFFC3084, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB9,                    0xFFFC3088, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB10,                   0xFFFC308C, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB11,                   0xFFFC3090, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB12,                   0xFFFC3094, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB13,                   0xFFFC3098, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB14,                   0xFFFC309C, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG16_BIT(LWCB15,                   0xFFFC30A0, __READ_WRITE, __adclwcbx_bits          ); 
__IO_REG32_BIT(IHWCTRL,                  0xFFFC30A4, __READ_WRITE, __adcihwctrl_bits        ); 
__IO_REG32_BIT(ILWCTRL,                  0xFFFC30A8, __READ_WRITE, __adcilwctrl_bits        ); 
__IO_REG32_BIT(MIS,                      0xFFFC30AC, __READ,       __adcmis_bits            ); 
__IO_REG32_BIT(IC,                       0xFFFC30B0, __WRITE,      __adcic_bits             ); 

/***************************************************************************
 **
 **  TIMER : Timer 0 1 2
 **
 ***************************************************************************/
__IO_REG32_BIT(TIMER_CTRL0,              0xFFFC4000, __READ_WRITE, __timerctrl0_bits        ); 
__IO_REG32_BIT(CMP_CAP_CTRL,             0xFFFC4004, __READ_WRITE, __timercmpcapctrl_bits ); 
__IO_REG32_BIT(INTEN0,                   0xFFFC4008, __READ_WRITE, __timerinten0_bits       ); 
__IO_REG32_BIT(TIMER_STATUS0,            0xFFFC400C, __READ_WRITE, __timerstatus0_bits      ); 
__IO_REG32_BIT(TIMER_CNT0,               0xFFFC4010, __READ_WRITE, __timercnt0_bits         ); 
__IO_REG32_BIT(T0CMP0,                   0xFFFC4014, __READ_WRITE, __timert0cmp0_bits       );
__IO_REG32_BIT(T0CMP1,                   0xFFFC4018, __READ,       __timert0cmp_bits        ); 
__IO_REG32_BIT(T0CAPA,                   0xFFFC401C, __READ,       __timert0cmp_bits        ); 
__IO_REG32_BIT(T0CAPB,                   0xFFFC4020, __READ,       __timert0cmp_bits        ); 
__IO_REG32_BIT(T0CAPC,                   0xFFFC4024, __READ,       __timert0cmp_bits        ); 
__IO_REG32_BIT(T0CAPD,                   0xFFFC4028, __READ,       __timert0cmp_bits        ); 
__IO_REG32_BIT(T0CAPE,                   0xFFFC402C, __READ,       __timert0cmp_bits        ); 
__IO_REG32_BIT(TIMER_CTRL1,              0xFFFC4030, __READ_WRITE, __timerctrl_bits         ); 
__IO_REG32_BIT(INTEN1,                   0xFFFC4034, __READ_WRITE, __timerinten_bits        ); 
__IO_REG32_BIT(TIMER_STATUS1,            0xFFFC4038, __READ_WRITE, __timerstatus_bits       ); 
__IO_REG32_BIT(TIMER_CNT1,               0xFFFC403C, __READ_WRITE, __timercnt1_bits         );
__IO_REG32_BIT(T1CMP0,                   0xFFFC4040, __READ_WRITE, __timert1cmp_bits        ); 
__IO_REG32_BIT(T1CMP1,                   0xFFFC4044, __READ_WRITE, __timert1cmp_bits        ); 
__IO_REG32_BIT(T1CAPA,                   0xFFFC4048, __READ,       __timert1cap_bits        ); 
__IO_REG32_BIT(T1CAPB,                   0xFFFC404C, __READ,       __timert1cap_bits        ); 
__IO_REG32_BIT(TIMER_CTRL2,              0xFFFC4050, __READ_WRITE, __timerctrl_bits         ); 
__IO_REG32_BIT(INTEN2,                   0xFFFC4054, __READ_WRITE, __timerinten_bits        ); 
__IO_REG32_BIT(TIMER_STATUS2,            0xFFFC4058, __READ_WRITE, __timerstatus_bits       ); 
__IO_REG32_BIT(TIMER_CNT2,               0xFFFC405C, __READ_WRITE, __timercnt2_bits         ); 
__IO_REG32_BIT(T2CMP0,                   0xFFFC4060, __READ_WRITE, __timert2cmp_bits        ); 
__IO_REG32_BIT(T2CMP1,                   0xFFFC4064, __READ_WRITE, __timert2cmp_bits        ); 
__IO_REG32_BIT(T2CAPA,                   0xFFFC4068, __READ,       __timert2cap_bits        ); 
__IO_REG32_BIT(T2CAPB,                   0xFFFC406C, __READ,       __timert2cap_bits        ); 

/***************************************************************************
 **
 **  I2C : Inter-IC bus
 **
 ***************************************************************************/
__IO_REG32_BIT(ICCON,                    0xFFFC5000, __READ_WRITE, __i2ciccon_bits          ); 
__IO_REG32_BIT(ICSAR,                    0xFFFC5004, __READ_WRITE, __i2cicsar_bits          ); 
__IO_REG32_BIT(ICUSAR,                   0xFFFC5008, __READ_WRITE, __i2cicusar_bits         ); 
__IO_REG32_BIT(ICDATA,                   0xFFFC500C, __READ_WRITE, __i2cicdata_bits         );
__IO_REG32_BIT(ICHCNT,                   0xFFFC5010, __READ_WRITE, __i2cichcnt_bits         ); 
__IO_REG32_BIT(ICLCNT,                   0xFFFC5014, __READ_WRITE, __i2ciclcnt_bits         ); 
__IO_REG32_BIT(ICSTAT,                   0xFFFC501C, __READ,       __i2cicstat_bits         ); 

/***************************************************************************
 **
 **  SSP : Synchronous Serial Port
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP_CTRL0,                0xFFFC6000, __READ_WRITE, __sspctrl0_bits); 
__IO_REG32_BIT(SSP_CTRL1,                0xFFFC6004, __READ_WRITE, __sspctrl1_bits); 
__IO_REG32_BIT(SSP_DR,                   0xFFFC6008, __READ_WRITE, __sspdr_bits   ); 
__IO_REG32_BIT(SSP_SR,                   0xFFFC600C, __READ,       __sspsr_bits   );
__IO_REG32_BIT(SSP_CPSR,                 0xFFFC6010, __READ_WRITE, __sspcpsr_bits ); 
__IO_REG32_BIT(SSP_IMSC,                 0xFFFC6014, __READ_WRITE, __sspimsc_bits ); 
__IO_REG32_BIT(SSP_RIS,                  0xFFFC6018, __READ,       __sspris_bits  ); 
__IO_REG32_BIT(SSP_MIS,                  0xFFFC601C, __READ,       __sspmis_bits  ); 
__IO_REG32_BIT(SSP_ICR,                  0xFFFC6020, __WRITE,      __sspicr_bits  ); 
__IO_REG32_BIT(SSP_DCR,                  0xFFFC6024, __READ_WRITE, __sspdcr_bits  ); 

/***************************************************************************
 **
 **  EMAC : Ethernet Medium Access Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(NETCTL,                   0xFFFC7000, __READ_WRITE, __emacnetctl_bits        ); 
__IO_REG32_BIT(NETCONFIG,                0xFFFC7004, __READ_WRITE, __emacnetconfig_bits     ); 
__IO_REG32_BIT(NETSTATUS,                0xFFFC7008, __READ,       __emacnetstatus_bits     ); 
__IO_REG32_BIT(TXSTATUS,                 0xFFFC7014, __READ_WRITE, __emactxstatus_bits      ); 
__IO_REG32_BIT(RXBQP,                    0xFFFC7018, __READ_WRITE, __emacrxbqp_bits         ); 
__IO_REG32_BIT(TXBQP,                    0xFFFC701C, __READ_WRITE, __emactxbqp_bits         ); 
__IO_REG32_BIT(RXSTATUS,                 0xFFFC7020, __READ_WRITE, __emacrxstatus_bits      );
__IO_REG32_BIT(INSTATUS,                 0xFFFC7024, __READ_WRITE, __emacinstatus_bits      ); 
__IO_REG32_BIT(ENABLE,                   0xFFFC7028, __WRITE,      __emacenable_bits        ); 
__IO_REG32_BIT(DISABLE,                  0xFFFC702C, __WRITE,      __emacdisable_bits       ); 
__IO_REG32_BIT(EMAC_MASK,                0xFFFC7030, __READ,       __emacmask_bits          ); 
__IO_REG32_BIT(PHYMAINT,                 0xFFFC7034, __READ_WRITE, __emacphymaint_bits      ); 
__IO_REG32_BIT(PAUSETIME,                0xFFFC7038, __READ,       __emacpausetime_bits     ); 
__IO_REG32_BIT(PAUSEFRRX,                0xFFFC703C, __READ_WRITE, __emacpausefrrx_bits     ); 
__IO_REG32_BIT(FRMTXOK,                  0xFFFC7040, __READ_WRITE, __emacfrmtxok_bits       ); 
__IO_REG32_BIT(SINGLECOL,                0xFFFC7044, __READ_WRITE, __emacsinglecol_bits     ); 
__IO_REG32_BIT(MULTFRM,                  0xFFFC7048, __READ_WRITE, __emacmultfrm_bits       );
__IO_REG32_BIT(FRMRXOK,                  0xFFFC704C, __READ_WRITE, __emacfrmrxok_bits       ); 
__IO_REG32_BIT(FRCHK,                    0xFFFC7050, __READ_WRITE, __emacfrchk_bits         ); 
__IO_REG32_BIT(ALIGNERR,                 0xFFFC7054, __READ_WRITE, __emacalignerr_bits      ); 
__IO_REG32_BIT(DEFTXFRM,                 0xFFFC7058, __READ_WRITE, __emacdeftxfrm_bits      ); 
__IO_REG32_BIT(LATECOL,                  0xFFFC705C, __READ_WRITE, __emaclatecol_bits       ); 
__IO_REG32_BIT(EXCOL,                    0xFFFC7060, __READ_WRITE, __emacexcol_bits         ); 
__IO_REG32_BIT(TXUNDER,                  0xFFFC7064, __READ_WRITE, __emactxunder_bits       ); 
__IO_REG32_BIT(SENSERR,                  0xFFFC7068, __READ_WRITE, __emacsenserr_bits       ); 
__IO_REG32_BIT(RXRERR,                   0xFFFC706C, __READ_WRITE, __emacrxrerr_bits        ); 
__IO_REG32_BIT(RXOVERR,                  0xFFFC7070, __READ_WRITE, __emacrxoverr_bits       ); 
__IO_REG32_BIT(RXSYMERR,                 0xFFFC7074, __READ_WRITE, __emacrxsymerr_bits      ); 
__IO_REG32_BIT(LENERR,                   0xFFFC7078, __READ_WRITE, __emaclenerr_bits        ); 
__IO_REG32_BIT(RXJAB,                    0xFFFC707C, __READ_WRITE, __emacrxjab_bits         ); 
__IO_REG32_BIT(UNDERFRM,                 0xFFFC7080, __READ_WRITE, __emacunderfrm_bits      ); 
__IO_REG32_BIT(SQERR,                    0xFFFC7084, __READ_WRITE, __emacsqerr_bits         ); 
__IO_REG32_BIT(RXLEN,                    0xFFFC7088, __READ_WRITE, __emacrxlen_bits         ); 
__IO_REG32_BIT(TXPAUSEFM,                0xFFFC708C, __READ_WRITE, __emactxpausefm_bits     ); 
__IO_REG32_BIT(HASHBOT,                  0xFFFC7090, __READ_WRITE, __emachashbot_bits       ); 
__IO_REG32_BIT(HASHTOP,                  0xFFFC7094, __READ_WRITE, __emachashtop_bits       ); 
__IO_REG32_BIT(SPECAD1BOT,               0xFFFC7098, __READ_WRITE, __emacspecad1bot_bits    ); 
__IO_REG32_BIT(SPECAD1TOP,               0xFFFC709C, __READ_WRITE, __emacspecad1top_bits    ); 
__IO_REG32_BIT(SPECAD2BOT,               0xFFFC70A0, __READ_WRITE, __emacspecad2bot_bits    ); 
__IO_REG32_BIT(SPECAD2TOP,               0xFFFC70A4, __READ_WRITE, __emacspecad2top_bits    ); 
__IO_REG32_BIT(SPECAD3BOT,               0xFFFC70A8, __READ_WRITE, __emacspecad3bot_bits    );
__IO_REG32_BIT(SPECAD3TOP,               0xFFFC70AC, __READ_WRITE, __emacspecad3top_bits    ); 
__IO_REG32_BIT(SPECAD4BOT,               0xFFFC70B0, __READ_WRITE, __emacspecad4bot_bits    ); 
__IO_REG32_BIT(SPECAD4TOP,               0xFFFC70B4, __READ_WRITE, __emacspecad4top_bits    ); 
__IO_REG32_BIT(IDCHK,                    0xFFFC70B8, __READ_WRITE, __emacidchk_bits         ); 
__IO_REG32_BIT(TXPAUSEQUAN,              0xFFFC70BC, __READ_WRITE, __emactxpausequan_bits   ); 

/***************************************************************************
 **
 **  I2S Module 
 **
 ***************************************************************************/
__IO_REG32_BIT(I2S_CTRL,                 0xFFFC8000, __READ_WRITE, __i2sctrl_bits );
__IO_REG32_BIT(I2S_STAT,                 0xFFFC8004, __READ      , __i2sstat_bits );
__IO_REG32_BIT(I2S_IMSC,                 0xFFFC8008, __READ_WRITE, __i2simsc_bits); 
__IO_REG32_BIT(I2S_RIS,                  0xFFFC800C, __READ,       __i2sris_bits  ); 
__IO_REG32_BIT(I2S_MIS,                  0xFFFC8010, __READ,       __i2smis_bits  ); 
__IO_REG32_BIT(I2S_ICR,                  0xFFFC8014, __WRITE,      __i2sicr_bits  );    

/***************************************************************************
 **
 **  GPIO : General Purpose Input/Output
 **
 ***************************************************************************/
__IO_REG32_BIT(P1DRM,                    0xFFFD9000, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P2DRN,                    0xFFFD9004, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P1DDRM,                   0xFFFD9008, __READ_WRITE, __gpiopxddr_bits         );
__IO_REG32_BIT(P2DDRN,                   0xFFFD900C, __READ_WRITE, __gpiopxddr_bits         );
__IO_REG32_BIT(P1DRI,                    0xFFFDB000, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P2DRJ,                    0xFFFDB004, __READ_WRITE, __gpiopxdr_bits          ); 
__IO_REG32_BIT(P1DDRI,                   0xFFFDB008, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P2DDRJ,                   0xFFFDB00C, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P1DRG,                    0xFFFDC000, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P2DRH,                    0xFFFDC004, __READ_WRITE, __gpiopxdr_bits          ); 
__IO_REG32_BIT(P1DDRG,                   0xFFFDC008, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P2DDRH,                   0xFFFDC00C, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P1DRE,                    0xFFFDD000, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P2DRF,                    0xFFFDD004, __READ_WRITE, __gpiopxdr_bits          ); 
__IO_REG32_BIT(P1DDRE,                   0xFFFDD008, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P2DDRF,                   0xFFFDD00C, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P1DRC,                    0xFFFDE000, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P2DRD,                    0xFFFDE004, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P1DDRC,                   0xFFFDE008, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P2DDRD,                   0xFFFDE00C, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P1DRA,                    0xFFFDF000, __READ_WRITE, __gpiopxdr_bits          ); 
__IO_REG32_BIT(P2DRB,                    0xFFFDF004, __READ_WRITE, __gpiopxdr_bits          );
__IO_REG32_BIT(P1DDRA,                   0xFFFDF008, __READ_WRITE, __gpiopxddr_bits         ); 
__IO_REG32_BIT(P2DDRB,                   0xFFFDF00C, __READ_WRITE, __gpiopxddr_bits         ); 

/***************************************************************************
 **
 **  RTC : Real Time Clock
 **
 ***************************************************************************/
__IO_REG32_BIT(RTC_DR,                   0xFFFE0000, __READ,       __rtcdr_bits  );
__IO_REG32_BIT(RTC_MR,                   0xFFFE0004, __READ_WRITE, __rtcmr_bits  ); 
__IO_REG32_BIT(RTC_LR,                   0xFFFE0008, __READ_WRITE, __rtclr_bits  ); 
__IO_REG32_BIT(RTC_CR,                   0xFFFE000C, __READ_WRITE, __rtccr_bits  );
__IO_REG32_BIT(RTC_IMSC,                 0xFFFE0010, __READ_WRITE, __rtcimsc_bits); 
__IO_REG32_BIT(RTC_RIS,                  0xFFFE0014, __READ,       __rtcris_bits ); 
__IO_REG32_BIT(RTC_MIS,                  0xFFFE0018, __READ,       __rtcmis_bits ); 
__IO_REG32_BIT(RTC_ICR,                  0xFFFE001C, __WRITE,      __rtcicr_bits ); 

/***************************************************************************
 **
 **  DMA : DMA Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(STREAM0_SOURCELO,         0xFFFE1000, __READ_WRITE, __dmasourcelo_bits       ); 
__IO_REG32_BIT(STREAM0_SOURCEHI,         0xFFFE1004, __READ_WRITE, __dmasourcehi_bits       ); 
__IO_REG32_BIT(STREAM0_DESTLO,           0xFFFE1008, __READ_WRITE, __dmadestlo_bits         ); 
__IO_REG32_BIT(STREAM0_DESTHI,           0xFFFE100C, __READ_WRITE, __dmadesthi_bits         ); 
__IO_REG32_BIT(STREAM0_MAX,              0xFFFE1010, __READ_WRITE, __dmamax_bits            ); 
__IO_REG32_BIT(STREAM0_CTRL,             0xFFFE1014, __READ_WRITE, __dmactrl_bits           ); 
__IO_REG32_BIT(STREAM0_CURSHI,           0xFFFE1018, __READ_WRITE, __dmacurshi_bits         ); 
__IO_REG32_BIT(STREAM0_CURSLO,           0xFFFE101C, __READ_WRITE, __dmacurslo_bits         ); 
__IO_REG32_BIT(STREAM0_CURDHI,           0xFFFE1020, __READ_WRITE, __dmacurdhi_bits         ); 
__IO_REG32_BIT(STREAM0_CURDLO,           0xFFFE1024, __READ_WRITE, __dmacurdlo_bits         ); 
__IO_REG32_BIT(STREAM0_TCNT,             0xFFFE1028, __READ_WRITE, __dmatcnt_bits           );
__IO_REG32_BIT(STREAM1_SOURCELO,         0xFFFE1040, __READ_WRITE, __dmasourcelo_bits       ); 
__IO_REG32_BIT(STREAM1_SOURCEHI,         0xFFFE1044, __READ_WRITE, __dmasourcehi_bits       ); 
__IO_REG32_BIT(STREAM1_DESTLO,           0xFFFE1048, __READ_WRITE, __dmadestlo_bits         ); 
__IO_REG32_BIT(STREAM1_DESTHI,           0xFFFE104C, __READ_WRITE, __dmadesthi_bits         ); 
__IO_REG32_BIT(STREAM1_MAX,              0xFFFE1050, __READ_WRITE, __dmamax_bits            ); 
__IO_REG32_BIT(STREAM1_CTRL,             0xFFFE1054, __READ_WRITE, __dmactrl_bits           ); 
__IO_REG32_BIT(STREAM1_CURSHI,           0xFFFE1058, __READ_WRITE, __dmacurshi_bits         ); 
__IO_REG32_BIT(STREAM1_CURSLO,           0xFFFE105C, __READ_WRITE, __dmacurslo_bits         ); 
__IO_REG32_BIT(STREAM1_CURDHI,           0xFFFE1060, __READ_WRITE, __dmacurdhi_bits         ); 
__IO_REG32_BIT(STREAM1_CURDLO,           0xFFFE1064, __READ_WRITE, __dmacurdlo_bits         ); 
__IO_REG32_BIT(STREAM1_TCNT,             0xFFFE1068, __READ_WRITE, __dmatcnt_bits           ); 
__IO_REG32_BIT(STREAM2_SOURCELO,         0xFFFE1080, __READ_WRITE, __dmasourcelo_bits       ); 
__IO_REG32_BIT(STREAM2_SOURCEHI,         0xFFFE1084, __READ_WRITE, __dmasourcehi_bits       ); 
__IO_REG32_BIT(STREAM2_DESTLO,           0xFFFE1088, __READ_WRITE, __dmadestlo_bits         ); 
__IO_REG32_BIT(STREAM2_DESTHI,           0xFFFE108C, __READ_WRITE, __dmadesthi_bits         ); 
__IO_REG32_BIT(STREAM2_MAX,              0xFFFE1090, __READ_WRITE, __dmamax_bits            ); 
__IO_REG32_BIT(STREAM2_CTRL,             0xFFFE1094, __READ_WRITE, __dmactrl_bits           );
__IO_REG32_BIT(STREAM2_CURSHI,           0xFFFE1098, __READ_WRITE, __dmacurshi_bits         );
__IO_REG32_BIT(STREAM2_CURSLO,           0xFFFE109C, __READ_WRITE, __dmacurslo_bits         ); 
__IO_REG32_BIT(STREAM2_CURDHI,           0xFFFE10A0, __READ_WRITE, __dmacurdhi_bits         ); 
__IO_REG32_BIT(STREAM2_CURDLO,           0xFFFE10A4, __READ_WRITE, __dmacurdlo_bits         ); 
__IO_REG32_BIT(STREAM2_TCNT,             0xFFFE10A8, __READ_WRITE, __dmatcnt_bits           ); 
__IO_REG32_BIT(STREAM3_SOURCELO,         0xFFFE10C0, __READ_WRITE, __dmasourcelo_bits       ); 
__IO_REG32_BIT(STREAM3_SOURCEHI,         0xFFFE10C4, __READ_WRITE, __dmasourcehi_bits       ); 
__IO_REG32_BIT(STREAM3_DESTLO,           0xFFFE10C8, __READ_WRITE, __dmadestlo_bits         ); 
__IO_REG32_BIT(STREAM3_DESTHI,           0xFFFE10CC, __READ_WRITE, __dmadesthi_bits         ); 
__IO_REG32_BIT(STREAM3_MAX,              0xFFFE10D0, __READ_WRITE, __dmamax_bits            ); 
__IO_REG32_BIT(STREAM3_CTRL,             0xFFFE10D4, __READ_WRITE, __dmactrl_bits           ); 
__IO_REG32_BIT(STREAM3_CURSHI,           0xFFFE10D8, __READ_WRITE, __dmacurshi_bits         ); 
__IO_REG32_BIT(STREAM3_CURSLO,           0xFFFE10DC, __READ_WRITE, __dmacurslo_bits         ); 
__IO_REG32_BIT(STREAM3_CURDHI,           0xFFFE10E0, __READ_WRITE, __dmacurdhi_bits         ); 
__IO_REG32_BIT(STREAM3_CURDLO,           0xFFFE10E4, __READ_WRITE, __dmacurdlo_bits         ); 
__IO_REG32_BIT(STREAM3_TCNT,             0xFFFE10E8, __READ_WRITE, __dmatcnt_bits           ); 
__IO_REG32_BIT(DMA_MASK,                 0xFFFE10F0, __READ_WRITE, __dmamask_bits           ); 
__IO_REG32_BIT(CLR,                      0xFFFE10F4, __WRITE,      __dmaclr_bits            ); 
__IO_REG32_BIT(STATUS,                   0xFFFE10F8, __READ,       __dmastatus_bits         ); 

/***************************************************************************
 **
 **  RCPC : Reset Clock and Power Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(RCPC_CTRL,                0xFFFE2000, __READ_WRITE, __rcpcctrl_bits          ); 
__IO_REG32_BIT(CHIPID,                   0xFFFE2004, __READ,       __rcpcchipid_bits        ); 
__IO_REG32_BIT(REMAP,                    0xFFFE2008, __READ_WRITE, __rcpcremap_bits         ); 
__IO_REG32_BIT(SOFTRESET,                0xFFFE200C, __READ_WRITE, __rcpcsoftreset_bits     ); 
__IO_REG32_BIT(RSTSTATUS,                0xFFFE2010, __READ,       __rcpcrststatus_bits     ); 
__IO_REG32_BIT(RSTSTATUSCLR,             0xFFFE2014, __WRITE,      __rcpcrststatusclr_bits  ); 
__IO_REG32_BIT(SYSCLKPRE,                0xFFFE2018, __READ_WRITE, __rcpcsysclkpre_bits     ); 
__IO_REG32_BIT(CPUCLKPRE,                0xFFFE201C, __READ_WRITE, __rcpccpuclkpre_bits     ); 
__IO_REG32_BIT(PCLKCTRL0,                0xFFFE2024, __READ_WRITE, __rcpcpclkctrl0_bits     ); 
__IO_REG32_BIT(PCLKCTRL1,                0xFFFE2028, __READ_WRITE, __rcpcpclkctrl1_bits     ); 
__IO_REG32_BIT(AHBCLKCTRL,               0xFFFE202C, __READ_WRITE, __rcpcahbclkctrl_bits    ); 
__IO_REG32_BIT(PCLKSEL0,                 0xFFFE2030, __READ_WRITE, __rcpcpclksel0_bits      ); 
__IO_REG32_BIT(PCLKSEL1,                 0xFFFE2034, __READ_WRITE, __rcpcpclksel1_bits      ); 
__IO_REG32_BIT(SILICONREV,               0xFFFE203C, __READ,       __rcpcsiliconrev_bits    ); 
__IO_REG32_BIT(LCDPRE,                   0xFFFE2040, __READ_WRITE, __rcpclcdpre_bits        ); 
__IO_REG32_BIT(SSPPRE,                   0xFFFE2044, __READ_WRITE, __rcpcssppre_bits        ); 
__IO_REG32_BIT(ADCPRE,                   0xFFFE2048, __READ_WRITE, __rcpcadcpre_bits        ); 
__IO_REG32_BIT(USBPRE,                   0xFFFE204C, __READ_WRITE, __rcpcusbpre_bits        ); 
__IO_REG32_BIT(INTCONFIG,                0xFFFE2080, __READ_WRITE, __rcpcintconfig_bits     ); 
__IO_REG32_BIT(RCPC_INTCLR,              0xFFFE2084, __WRITE,      __rcpcintclr_bits        ); 
__IO_REG32_BIT(CORECONFIG,               0xFFFE2088, __WRITE,      __rcpccoreconfig_bits    ); 
__IO_REG32_BIT(SYSPLLCNTL,               0xFFFE20C0, __READ_WRITE, __rcpcsyspllcntl_bits    ); 
__IO_REG32_BIT(USBPLLCTL,                0xFFFE20C4, __READ_WRITE, __rcpcusbpllctl_bits     ); 

/***************************************************************************
 **
 **  WDT : Watchdog Timer
 **
 ***************************************************************************/
__IO_REG32_BIT(WDT_CTL,                  0xFFFE3000, __READ_WRITE, __wdtctl_bits            ); 
__IO_REG32_BIT(WDT_RST,                  0xFFFE3004, __WRITE,      __wdtrst_bits            ); 
__IO_REG32_BIT(WDT_STATUS,               0xFFFE3008, __READ,       __wdtstatus_bits         ); 
__IO_REG32_BIT(WDT_COUNT0,               0xFFFE300C, __READ,       __wdtcount_bits          ); 
__IO_REG32_BIT(WDT_COUNT1,               0xFFFE3010, __READ,       __wdtcount_bits          ); 
__IO_REG32_BIT(WDT_COUNT2,               0xFFFE3014, __READ,       __wdtcount_bits          ); 
__IO_REG32_BIT(WDT_COUNT3,               0xFFFE3018, __READ,       __wdtcount_bits          ); 

/***************************************************************************
 **
 **  ALI : Advanced LCD Interface
 **
 ***************************************************************************/
__IO_REG32_BIT(ALISETUP,                 0xFFFE4000, __READ_WRITE, __alialisetup_bits       ); 
__IO_REG32_BIT(ALICTRL,                  0xFFFE4004, __READ_WRITE, __alialictrl_bits        ); 
__IO_REG32_BIT(ALITIMING1,               0xFFFE4008, __READ_WRITE, __alialitiming1_bits     ); 
__IO_REG32_BIT(ALITIMING2,               0xFFFE400C, __READ_WRITE, __alialitiming2_bits     ); 

/***************************************************************************
 **
 **  I/O Configuration 
 **
 ***************************************************************************/
__IO_REG32_BIT(MUXCTL1,                  0xFFFE5000, __READ_WRITE, __ioconctl1_bits     ); 
__IO_REG32_BIT(RESCTL1,                  0xFFFE5004, __READ_WRITE, __ioconctl1_bits     ); 
__IO_REG32_BIT(MUXCTL3,                  0xFFFE5010, __READ_WRITE, __ioconctl3_bits     ); 
__IO_REG32_BIT(RESCTL3,                  0xFFFE5014, __READ_WRITE, __ioconctl3_bits     ); 
__IO_REG32_BIT(MUXCTL4,                  0xFFFE5018, __READ_WRITE, __ioconctl4_bits     ); 
__IO_REG32_BIT(RESCTL4,                  0xFFFE501C, __READ_WRITE, __ioconctl4_bits     ); 
__IO_REG32_BIT(MUXCTL5,                  0xFFFE5020, __READ_WRITE, __ioconctl5_bits     ); 
__IO_REG32_BIT(RESCTL5,                  0xFFFE5024, __READ_WRITE, __ioconctl5_bits     ); 
__IO_REG32_BIT(MUXCTL6,                  0xFFFE5028, __READ_WRITE, __ioconctl6_bits     );
__IO_REG32_BIT(RESCTL6,                  0xFFFE502C, __READ_WRITE, __ioconctl6_bits     ); 
__IO_REG32_BIT(MUXCTL7,                  0xFFFE5030, __READ_WRITE, __ioconctl7_bits     ); 
__IO_REG32_BIT(RESCTL7,                  0xFFFE5034, __READ_WRITE, __ioconctl7_bits     ); 
__IO_REG32_BIT(MUXCTL10,                 0xFFFE5048, __READ_WRITE, __ioconctl10_bits    ); 
__IO_REG32_BIT(RESCTL10,                 0xFFFE504C, __READ_WRITE, __ioconctl10_bits    ); 
__IO_REG32_BIT(MUXCTL11,                 0xFFFE5050, __READ_WRITE, __ioconctl11_bits    ); 
__IO_REG32_BIT(RESCTL11,                 0xFFFE5054, __READ_WRITE, __ioconctl11_bits    ); 
__IO_REG32_BIT(MUXCTL12,                 0xFFFE5058, __READ_WRITE, __ioconmuxctl12_bits ); 
__IO_REG32_BIT(RESCTL12,                 0xFFFE505C, __READ_WRITE, __ioconresctl12_bits ); 
__IO_REG32_BIT(RESCTL13,                 0xFFFE5064, __READ_WRITE, __ioconresctl13_bits ); 
__IO_REG32_BIT(MUXCTL14,                 0xFFFE5068, __READ_WRITE, __ioconmuxctl14_bits );
__IO_REG32_BIT(MUXCTL15,                 0xFFFE5070, __READ_WRITE, __ioconctl15_bits    );    
__IO_REG32_BIT(RESCTL15,                 0xFFFE5074, __READ_WRITE, __ioconctl15_bits    );
__IO_REG32_BIT(RESCTL17,                 0xFFFE5084, __READ_WRITE, __ioconresctl17_bits );
__IO_REG32_BIT(MUXCTL19,                 0xFFFE5090, __READ_WRITE, __ioconctl19_bits    );    
__IO_REG32_BIT(RESCTL19,                 0xFFFE5094, __READ_WRITE, __ioconctl19_bits    );    
__IO_REG32_BIT(MUXCTL20,                 0xFFFE5098, __READ_WRITE, __ioconctl20_bits    ); 
__IO_REG32_BIT(RESCTL20,                 0xFFFE509C, __READ_WRITE, __ioconctl20_bits    );
__IO_REG32_BIT(MUXCTL21,                 0xFFFE50A0, __READ_WRITE, __ioconctl21_bits    ); 
__IO_REG32_BIT(RESCTL21,                 0xFFFE50A4, __READ_WRITE, __ioconctl21_bits    );    
__IO_REG32_BIT(MUXCTL22,                 0xFFFE50A8, __READ_WRITE, __ioconctl22_bits    ); 
__IO_REG32_BIT(RESCTL22,                 0xFFFE50AC, __READ_WRITE, __ioconctl22_bits    );    
__IO_REG32_BIT(MUXCTL23,                 0xFFFE50B0, __READ_WRITE, __ioconctl23_bits   ); 
__IO_REG32_BIT(RESCTL23,                 0xFFFE50B4, __READ_WRITE, __ioconctl23_bits   ); 
__IO_REG32_BIT(MUXCTL24,                 0xFFFE50B8, __READ_WRITE, __ioconctl24_bits   ); 
__IO_REG32_BIT(RESCTL24,                 0xFFFE50BC, __READ_WRITE, __ioconctl24_bits   ); 
__IO_REG32_BIT(MUXCTL25,                 0xFFFE50C0, __READ_WRITE, __ioconmuxctl25_bits);    

/***************************************************************************
 **
 **  BOOT : Boot Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(PBC,                      0xFFFE6000, __READ,       __bootpbc_bits           ); 
__IO_REG32_BIT(CS1OV,                    0xFFFE6004, __READ_WRITE, __bootcs1ov_bits         ); 
__IO_REG32_BIT(EPM,                      0xFFFE6008, __READ_WRITE, __bootepm_bits           ); 

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 ** LH79525 Interrupt sources 
 **
 ***************************************************************************/
#define        INO_WDT                   0
#define        INO_COMMRX                2
#define        INO_COMMTX                3
#define        INO_Timer0                4
#define        INO_Timer1                5
#define        INO_Timer2                6
#define        INO_External0             7
#define        INO_External1             8
#define        INO_External2             9
#define        INO_External3             10
#define        INO_External4             11
#define        INO_External5             12
#define        INO_External6             13
#define        INO_External7             14
#define        INO_RTC                   15
#define        INO_TSCIRQ                16
#define        INO_BROWNOUTINTR          17
#define        INO_PENIRQ                18
#define        INO_CLCD                  19
#define        INO_DMA0                  20
#define        INO_DMA1                  21
#define        INO_DMA2                  22
#define        INO_DMA3                  23
#define        INO_SSPI2SINTR            24
#define        INO_EMAC                  25
#define        INO_USB                   26
#define        INO_UART0                 27
#define        INO_UART1                 28
#define        INO_UART2                 29
#define        INO_USB_DMA               30
#define        INO_I2C                   31

#endif	/* __IOLH79525_H */


