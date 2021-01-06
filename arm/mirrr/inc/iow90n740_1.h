/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Winbond W91N740
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1.2.2 $
 **
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/
#ifndef __IOW91N740_H
#define __IOW91N740_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   W91N740 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

/* Product Identifier Register (PDID) */
typedef struct{
__REG32 CHPID           :24;
__REG32 VERSION         : 6;
__REG32 PACKAGE         : 2;
} __pdid_bits;

/* Arbitration Control Register (ARBCON) */
typedef struct{
__REG32 PRTMOD          : 1;
__REG32 IPEN            : 1;
__REG32 IPACT           : 1;
__REG32                 :29;
} __arbcon_bits;

/* PLL Control Register 0-1 (PLLCON) */
typedef struct{
__REG32 INDV            : 5;
__REG32 OTDV            : 2;
__REG32 FBDV            : 9;
__REG32 PWDEN           : 1;
__REG32                 :15;
} __pllcon_bits;

/* Clock Select Register (CLKSEL) */
typedef struct{
__REG32 RESET           : 1;
__REG32 CLKS            : 3;
__REG32 ECLKS           : 1;
__REG32 UART            : 1;
__REG32 TIMER           : 1;
__REG32 USBH            : 1;
__REG32 WDT             : 1;
__REG32 WDTS            : 1;
__REG32 EMC0            : 1;
__REG32 EMC1            : 1;
__REG32 NATA            : 1;
__REG32 GDMA            : 1;
__REG32                 : 1;
__REG32 USBCKS          : 1;
__REG32                 :16;
} __clksel_bits;

/* EBI Control Register (EBICON) */
typedef struct{
__REG32 LITTLE          : 1;
__REG32 WAITVT          : 2;
__REG32 REFRAT          :13;
__REG32 CLKEN           : 1;
__REG32 REFMOD          : 1;
__REG32 REFEN           : 1;
__REG32                 :13;
} __ebicon_bits;

/* ROM/Flash Control Register (ROMCON) */
typedef struct{
__REG32 PGMODE          : 2;
__REG32 BTSIZE          : 2;
__REG32 TACC            : 4;
__REG32 TPA             : 4;
__REG32                 : 4;
__REG32 SIZE            : 3;
__REG32 BASADDR         :13;
} __romcon_bits;

/* Configuration Registers(SDCONF0/1) */
typedef struct{
__REG32 SIZE            : 3;
__REG32 COLUMN          : 2;
__REG32 DBWD            : 2;
__REG32 COMPBK          : 1;
__REG32                 : 3;
__REG32 LATENCY         : 2;
__REG32 AUTOPR          : 1;
__REG32                 : 1;
__REG32 MRSET           : 1;
__REG32                 : 3;
__REG32 BASADDR         :13;
} __sdconf_bits;

/* Timing Control Registers (SDTIME0/1) */
typedef struct{
__REG32 TRAS            : 3;
__REG32 TRP             : 3;
__REG32 TRDL            : 2;
__REG32 TRCD            : 3;
__REG32                 :21;
} __sdtime_bits;

/* External I/O Control Registers(EXT0CON – EXT3CON) */
typedef struct{
__REG32 DBWD            : 2;
__REG32 TCOS            : 3;
__REG32 TACS            : 3;
__REG32 TCOH            : 3;
__REG32 TACC            : 4;
__REG32 ADRS            : 1;
__REG32 SIZE            : 3;
__REG32 BASADDR         :13;
} __extcon_bits;

/* Clock Skew Control Register (CKSKEW) */
typedef struct{
__REG32 MCLK_O_D        : 4;
__REG32 DLH_CLK_SKEW    : 4;
__REG32 SWPON           : 1;
__REG32                 : 7;
__REG32 DLH_CLK_REF     :16;
} __ckskew_bits;

/* Configuration Register (CAHCNF) */
typedef struct{
__REG32 ICAEN           : 1;
__REG32 DCAEN           : 1;
__REG32 WRBEN           : 1;
__REG32                 :29;
} __cahcnf_bits;

/* Control Register (CAHCON) */
typedef struct{
__REG32 ICAH            : 1;
__REG32 DCAH            : 1;
__REG32 FLHA            : 1;
__REG32 FLHS            : 1;
__REG32 LDLK            : 1;
__REG32 ULKA            : 1;
__REG32 ULKS            : 1;
__REG32 DRWB            : 1;
__REG32                 :24;
} __cahcon_bits;

/* Address Register (CAHADR) */
typedef struct{
__REG32 ADD             :31;
__REG32 WAY             : 1;
} __cahadr_bits;

/* CAM Command Register (CAMCMR) */
typedef struct{
__REG32 AUP             : 1;
__REG32 AMP             : 1;
__REG32 ABP             : 1;
__REG32 CCAM            : 1;
__REG32 ECMP            : 1;
__REG32                 :27;
} __camcmr_bits;

/* CAM Enable Register (CAMEN) */
typedef struct{
__REG32 CAM0EN          : 1;
__REG32 CAM1EN          : 1;
__REG32 CAM2EN          : 1;
__REG32 CAM3EN          : 1;
__REG32 CAM4EN          : 1;
__REG32 CAM5EN          : 1;
__REG32 CAM6EN          : 1;
__REG32 CAM7EN          : 1;
__REG32 CAM8EN          : 1;
__REG32 CAM9EN          : 1;
__REG32 CAM10EN         : 1;
__REG32 CAM11EN         : 1;
__REG32 CAM12EN         : 1;
__REG32 CAM13EN         : 1;
__REG32 CAM14EN         : 1;
__REG32 CAM15EN         : 1;
__REG32                 :16;
} __camen_bits;

/* CAM Entry Registers (CAMxM) */
typedef struct{
__REG32 MAC_ADDR2       : 8;
__REG32 MAC_ADDR3       : 8;
__REG32 MAC_ADDR4       : 8;
__REG32 MAC_ADDR5       : 8;
} __camm_bits;

/* CAM Entry Registers (CAMxL) */
typedef struct{
__REG32                 :16;
__REG32 MAC_ADDR0       : 8;
__REG32 MAC_ADDR1       : 8;
} __caml_bits;

/* CAM Entry Registers (CAM15M) */
typedef struct{
__REG32 OP_CODE         :16;
__REG32 LENGTH_TYPE     :16;
} __cam15m_bits;

/* CAM Entry Registers (CAM15L) */
typedef struct{
__REG32                 :16;
__REG32 OPERAND         :16;
} __cam15l_bits;

/* MAC Command Register (MCMDR) */
typedef struct{
__REG32 RXON            : 1;
__REG32 ALP             : 1;
__REG32 ARP             : 1;
__REG32 ACP             : 1;
__REG32 AEP             : 1;
__REG32 SPCRC           : 1;
__REG32                 : 2;
__REG32 TXON            : 1;
__REG32 NDEF            : 1;
__REG32                 : 6;
__REG32 SDPZ            : 1;
__REG32                 : 1;
__REG32 FDUP            : 1;
__REG32 ENMDC           : 1;
__REG32 OPMOD           : 1;
__REG32 LBK             : 1;
__REG32 ENRMII          : 1;
__REG32 LPCS            : 1;
__REG32 LAN             : 1;
__REG32                 : 7;
} __mcmdr_bits;

/* MII Management Data Register (MIID) */
typedef struct{
__REG32 MIIDATA         :16;
__REG32                 :16;
} __miid_bits;

/* MII Management Control and Address Register (MIIDA) */
typedef struct{
__REG32 PHYRAD          : 5;
__REG32                 : 3;
__REG32 PHYAD           : 5;
__REG32                 : 3;
__REG32 WR              : 1;
__REG32 BUSY            : 1;
__REG32 PRESP           : 1;
__REG32 MDCON           : 1;
__REG32 MDCCR           : 4;
__REG32                 : 8;
} __miida_bits;

/* FIFO Threshold Control Register (FIFOTHD) */
typedef struct{
__REG32 RXTHD           : 2;
__REG32                 : 6;
__REG32 TXTHD           : 2;
__REG32                 : 6;
__REG32 SWR             : 1;
__REG32                 : 3;
__REG32 BLENGHT         : 2;
__REG32                 :10;
} __fifothd_bits;

/* Maximum Receive Frame Control Register (DMARFC) */
typedef struct{
__REG32 RXMS            :16;
__REG32                 :16;
} __dmarfc_bits;

/* MAC Interrupt Enable Register (MIEN) */
typedef struct{
__REG32 ENRXINTR        : 1;
__REG32 ENCRCE          : 1;
__REG32 ENRXOV          : 1;
__REG32 ENPTLE          : 1;
__REG32 ENRXGD          : 1;
__REG32 ENALIE          : 1;
__REG32 ENRP            : 1;
__REG32 ENMMP           : 1;
__REG32 ENDFO           : 1;
__REG32 ENDEN           : 1;
__REG32 ENRDU           : 1;
__REG32 ENRXBERR        : 1;
__REG32 ENNATOK         : 1;
__REG32 ENNATERR        : 1;
__REG32 ENCFR           : 1;
__REG32                 : 1;
__REG32 ENTXINTR        : 1;
__REG32 ENTXEMP         : 1;
__REG32 ENTXCP          : 1;
__REG32 ENEXDEF         : 1;
__REG32 ENNCS           : 1;
__REG32 ENTXABT         : 1;
__REG32 ENLC            : 1;
__REG32 ENTDU           : 1;
__REG32 ENTXBERR        : 1;
__REG32                 : 7;
} __mien_bits;

/* MAC Interrupt Status Register (MISTA) */
typedef struct{
__REG32 RXINTR          : 1;
__REG32 CRCE            : 1;
__REG32 RXOV            : 1;
__REG32 PTLE            : 1;
__REG32 RXGD            : 1;
__REG32 ALIE            : 1;
__REG32 RP              : 1;
__REG32 MMP             : 1;
__REG32 DFOI            : 1;
__REG32 DENI            : 1;
__REG32 RDU             : 1;
__REG32 RXBERR          : 1;
__REG32 NATOK           : 1;
__REG32 NATERR          : 1;
__REG32 CFR             : 1;
__REG32                 : 1;
__REG32 TXINTR          : 1;
__REG32 TXEMP           : 1;
__REG32 TXCP            : 1;
__REG32 EXDEF           : 1;
__REG32 NCS             : 1;
__REG32 TXABT           : 1;
__REG32 LC              : 1;
__REG32 TDU             : 1;
__REG32 TXBERR          : 1;
__REG32                 : 7;
} __mista_bits;

/* MAC General Status Register (MGSTA) */
typedef struct{
__REG32 CFR             : 1;
__REG32 RXHA            : 1;
__REG32                 : 2;
__REG32 CCNT            : 4;
__REG32 DEF             : 1;
__REG32 PAU             : 1;
__REG32 SQE             : 1;
__REG32 TXHA            : 1;
__REG32                 :20;
} __mgsta_bits;

/* Missed Packet Count Register (MPCNT) */
typedef struct{
__REG32 MPCNT           :16;
__REG32                 :16;
} __mpcnt_bits;

/* MAC Receive Pause Count Register (MRPC) */
typedef struct{
__REG32 MRPC            :16;
__REG32                 :16;
} __mrpc_bits;

/* MAC Receive Pause Current Count Register (MRPCC) */
typedef struct{
__REG32 MRPCC           :16;
__REG32                 :16;
} __mrpcc_bits;

/* MAC Remote Pause Count Register (MREPC) */
typedef struct{
__REG32 MREPC           :16;
__REG32                 :16;
} __mrepc_bits;

/* DMA Receive Frame Status Register (DMARFS) */
typedef struct{
__REG32 RXFS            :16;
__REG32                 :16;
} __dmarfs_bits;

/* NAT Command Register (NATCMD) */
typedef struct{
__REG32 NATEN           : 1;
__REG32                 :31;
} __natcmd_bits;

/*NAT Counter 0 Clear Register (NATCCLR0)*/
typedef struct{
__REG32 CLRCNT0         : 1;
__REG32 CLRCNT1         : 1;
__REG32 CLRCNT2         : 1;
__REG32 CLRCNT3         : 1;
__REG32 CLRCNT4         : 1;
__REG32 CLRCNT5         : 1;
__REG32 CLRCNT6         : 1;
__REG32 CLRCNT7         : 1;
__REG32 CLRCNT8         : 1;
__REG32 CLRCNT9         : 1;
__REG32 CLRCNT10        : 1;
__REG32 CLRCNT11        : 1;
__REG32 CLRCNT12        : 1;
__REG32 CLRCNT13        : 1;
__REG32 CLRCNT14        : 1;
__REG32 CLRCNT15        : 1;
__REG32 CLREH0          : 1;
__REG32 CLREH1          : 1;
__REG32 CLREH2          : 1;
__REG32 CLREH3          : 1;
__REG32 CLREH4          : 1;
__REG32 CLREH5          : 1;
__REG32 CLREH6          : 1;
__REG32 CLREH7          : 1;
__REG32 CLREH8          : 1;
__REG32 CLREH9          : 1;
__REG32 CLREH10         : 1;
__REG32 CLREH11         : 1;
__REG32 CLREH12         : 1;
__REG32 CLREH13         : 1;
__REG32 CLREH14         : 1;
__REG32 CLREH15         : 1;
} __natcclr0_bits;

/*NAT Counter 1 Clear Register (NATCCLR1)*/
typedef struct{
__REG32 CLRCNT16        : 1;
__REG32 CLRCNT17        : 1;
__REG32 CLRCNT18        : 1;
__REG32 CLRCNT19        : 1;
__REG32 CLRCNT20        : 1;
__REG32 CLRCNT21        : 1;
__REG32 CLRCNT22        : 1;
__REG32 CLRCNT23        : 1;
__REG32 CLRCNT24        : 1;
__REG32 CLRCNT25        : 1;
__REG32 CLRCNT26        : 1;
__REG32 CLRCNT27        : 1;
__REG32 CLRCNT28        : 1;
__REG32 CLRCNT29        : 1;
__REG32 CLRCNT30        : 1;
__REG32 CLRCNT31        : 1;
__REG32 CLREH16         : 1;
__REG32 CLREH17         : 1;
__REG32 CLREH18         : 1;
__REG32 CLREH19         : 1;
__REG32 CLREH20         : 1;
__REG32 CLREH21         : 1;
__REG32 CLREH22         : 1;
__REG32 CLREH23         : 1;
__REG32 CLREH24         : 1;
__REG32 CLREH25         : 1;
__REG32 CLREH26         : 1;
__REG32 CLREH27         : 1;
__REG32 CLREH28         : 1;
__REG32 CLREH29         : 1;
__REG32 CLREH30         : 1;
__REG32 CLREH31         : 1;
} __natcclr1_bits;

/*NAT Counter 2 Clear Register (NATCCLR2)*/
typedef struct{
__REG32 CLRCNT32        : 1;
__REG32 CLRCNT33        : 1;
__REG32 CLRCNT34        : 1;
__REG32 CLRCNT35        : 1;
__REG32 CLRCNT36        : 1;
__REG32 CLRCNT37        : 1;
__REG32 CLRCNT38        : 1;
__REG32 CLRCNT39        : 1;
__REG32 CLRCNT40        : 1;
__REG32 CLRCNT41        : 1;
__REG32 CLRCNT42        : 1;
__REG32 CLRCNT43        : 1;
__REG32 CLRCNT44        : 1;
__REG32 CLRCNT45        : 1;
__REG32 CLRCNT46        : 1;
__REG32 CLRCNT47        : 1;
__REG32 CLREH32         : 1;
__REG32 CLREH33         : 1;
__REG32 CLREH34         : 1;
__REG32 CLREH35         : 1;
__REG32 CLREH36         : 1;
__REG32 CLREH37         : 1;
__REG32 CLREH38         : 1;
__REG32 CLREH39         : 1;
__REG32 CLREH40         : 1;
__REG32 CLREH41         : 1;
__REG32 CLREH42         : 1;
__REG32 CLREH43         : 1;
__REG32 CLREH44         : 1;
__REG32 CLREH45         : 1;
__REG32 CLREH46         : 1;
__REG32 CLREH47         : 1;
} __natcclr2_bits;

/*NAT Counter 3 Clear Register (NATCCLR3)*/
typedef struct{
__REG32 CLRCNT48        : 1;
__REG32 CLRCNT49        : 1;
__REG32 CLRCNT50        : 1;
__REG32 CLRCNT51        : 1;
__REG32 CLRCNT52        : 1;
__REG32 CLRCNT53        : 1;
__REG32 CLRCNT54        : 1;
__REG32 CLRCNT55        : 1;
__REG32 CLRCNT56        : 1;
__REG32 CLRCNT57        : 1;
__REG32 CLRCNT58        : 1;
__REG32 CLRCNT59        : 1;
__REG32 CLRCNT60        : 1;
__REG32 CLRCNT61        : 1;
__REG32 CLRCNT62        : 1;
__REG32 CLRCNT63        : 1;
__REG32 CLREH48         : 1;
__REG32 CLREH49         : 1;
__REG32 CLREH50         : 1;
__REG32 CLREH51         : 1;
__REG32 CLREH52         : 1;
__REG32 CLREH53         : 1;
__REG32 CLREH54         : 1;
__REG32 CLREH55         : 1;
__REG32 CLREH56         : 1;
__REG32 CLREH57         : 1;
__REG32 CLREH58         : 1;
__REG32 CLREH59         : 1;
__REG32 CLREH60         : 1;
__REG32 CLREH61         : 1;
__REG32 CLREH62         : 1;
__REG32 CLREH63         : 1;
} __natcclr3_bits;

/* NAT Entry x Configuration Registers (NATCFGx) */
typedef struct{
__REG32 EXEN            : 1;
__REG32 AXCE            : 1;
__REG32 PXCE            : 1;
__REG32 AXRE            : 1;
__REG32 PXRE            : 1;
__REG32 INVERSE         : 1;
__REG32 DISCARD         : 1;
__REG32 NOP             : 1;
__REG32 CNT             : 3;
__REG32                 : 5;
__REG32 EHCNT           :16;
} __natcfg_bits;

/* MAC Address Registers EXMACM, INMACM, LSMACxM, RSMACxM */
typedef struct{
__REG32 ADDR_BYTE3      : 8;
__REG32 ADDR_BYTE4      : 8;
__REG32 ADDR_BYTE5      : 8;
__REG32 ADDR_BYTE6      : 8;
} __exmacm_bits;

/* MAC Address Registers EXMACL, INMACL, LSMACxL, RSMACxL */
typedef struct{
__REG32                 :16;
__REG32 DST_ADDR1       : 8;
__REG32 DST_ADDR2       : 8;
} __exmacl_bits;

/* MAC Address Registers MASADx, LSADx */
typedef struct{
__REG32 IP_ADDR_BYTE1   : 8;
__REG32 IP_ADDR_BYTE2   : 8;
__REG32 IP_ADDR_BYTE3   : 8;
__REG32 IP_ADDR_BYTE4   : 8;
} __masad_bits;

/* MAC Address Registers MASPNx, LSPNx */
typedef struct{
__REG32 PORT_NUMB       :16;
__REG32                 :16;
} __maspn_bits;


/* Channel 0/1 Control Register (GDMA_CTL0, GDMA_CTL1) */
typedef struct{
__REG32 GDMAEN          : 1;
__REG32                 : 1;
__REG32 GDMAMS          : 2;
__REG32 DADIR           : 1;
__REG32 SADIR           : 1;
__REG32 DAFIX           : 1;
__REG32 SAFIX           : 1;
__REG32 SIEN            : 1;
__REG32 BME             : 1;
__REG32                 : 1;
__REG32 SBMS            : 1;
__REG32 TWS             : 2;
__REG32                 : 1;
__REG32 DM              : 1;
__REG32 SOFTREQ         : 1;
__REG32 BLOCK           : 1;
__REG32 TC              : 1;
__REG32 AUTOIEN         : 1;
__REG32 GDMAERR         : 1;
__REG32 DABNDERR        : 1;
__REG32 SABNDERR        : 1;
__REG32                 : 1;
__REG32 ACK_ATV         : 1;
__REG32 REQ_ATV         : 1;
__REG32 REQ_SEL         : 2;
__REG32                 : 4;
} __gdma_ctl_bits;

/* Channel 0/1 Transfer Count Register (GDMA_TCNT0, GDMA_TCNT1) */
typedef struct{
__REG32 TFR_CNT         :24;
__REG32                 : 8;
} __gdma_tcnt_bits;

/* HcRevision Register */
typedef struct {
__REG32 REV             : 8;
__REG32                 :24;
} __HcRevision_bits;

/* HcControl Register */
typedef struct {
__REG32 CBSR            : 2;
__REG32 PLE             : 1;
__REG32 IE              : 1;
__REG32 CLE             : 1;
__REG32 BLE             : 1;
__REG32 HCFS            : 2;
__REG32 IR              : 1;
__REG32 WC              : 1;
__REG32 RWE             : 1;
__REG32                 :21;
} __HcControl_bits;

/* HcCommandStatus Register */
typedef struct {
__REG32 HCR             : 1;
__REG32 CLF             : 1;
__REG32 BLF             : 1;
__REG32 OCR             : 1;
__REG32                 :12;
__REG32 SOC             : 2;
__REG32                 :14;
} __HcCommandStatus_bits;

/* HcInterruptStatus Register */
typedef struct {
__REG32 SO              : 1;
__REG32 WDH             : 1;
__REG32 SF              : 1;
__REG32 RD              : 1;
__REG32 UE              : 1;
__REG32 FNO             : 1;
__REG32 RHSC            : 1;
__REG32                 :23;
__REG32 OC              : 1;
__REG32                 : 1;
} __HcInterruptStatus_bits;

/* HcInterruptEnable Register
   HcInterruptDisable Register */
typedef struct {
__REG32 SO              : 1;
__REG32 WDH             : 1;
__REG32 SF              : 1;
__REG32 RD              : 1;
__REG32 UE              : 1;
__REG32 FNO             : 1;
__REG32 RHSC            : 1;
__REG32                 :23;
__REG32 OC              : 1;
__REG32 MIE             : 1;
} __HcInterruptEnable_bits;

/* HcHCCA Register */
typedef struct {
__REG32                 : 8;
__REG32 HCCA            :24;
} __HcHCCA_bits;

/* HcPeriodCurrentED Register */
typedef struct {
__REG32                 : 4;
__REG32 PCED            :28;
} __HcPeriodCurrentED_bits;

/* HcControlHeadED Registerr */
typedef struct {
__REG32                 : 4;
__REG32 CHED            :28;
} __HcControlHeadED_bits;

/* HcControlCurrentED Register */
typedef struct {
__REG32                 : 4;
__REG32 CCED            :28;
} __HcControlCurrentED_bits;

/* HcBulkHeadED Register */
typedef struct {
__REG32                 : 4;
__REG32 BHED            :28;
} __HcBulkHeadED_bits;

/* HcBulkCurrentED Register */
typedef struct {
__REG32                 : 4;
__REG32 BCED            :28;
} __HcBulkCurrentED_bits;

/* HcDoneHead Register */
typedef struct {
__REG32                 : 4;
__REG32 DH              :28;
} __HcDoneHead_bits;

/* HcFmInterval Register */
typedef struct {
__REG32 FI              :14;
__REG32                 : 2;
__REG32 FSMPS           :15;
__REG32 FIT             : 1;
} __HcFmInterval_bits;

/* HcFmRemaining Register */
typedef struct {
__REG32 FR              :14;
__REG32                 :17;
__REG32 FRT             : 1;
} __HcFmRemaining_bits;

/* HcPeriodicStart Register */
typedef struct {
__REG32 PS              :14;
__REG32                 :18;
} __HcPeriodicStart_bits;

/* HcLSThreshold Register */
typedef struct {
__REG32 LST             :12;
__REG32                 :20;
} __HcLSThreshold_bits;

/* HcRhDescriptorA Register */
typedef struct {
__REG32 NDP             : 8;
__REG32 PSM             : 1;
__REG32 NPS             : 1;
__REG32 DT              : 1;
__REG32 OCPM            : 1;
__REG32 NOCP            : 1;
__REG32                 :11;
__REG32 POTPGT          : 8;
} __HcRhDescriptorA_bits;

/* HcRhDescriptorB Register */
typedef struct {
__REG32 DEVRM           :16;
__REG32 PPCM            :16;
} __HcRhDescriptorB_bits;

/* HcRhStatus Register */
typedef struct {
__REG32 LPS             : 1;
__REG32 OCI             : 1;
__REG32                 :13;
__REG32 DRWE            : 1;
__REG32 LPSC            : 1;
__REG32 CCIC            : 1;
__REG32                 :13;
__REG32 CRWE            : 1;
} __HcRhStatus_bits;

/* HcRhPortStatus Register */
typedef struct {
__REG32 CCS             : 1;
__REG32 PES             : 1;
__REG32 PSS             : 1;
__REG32 POCI            : 1;
__REG32 PRS             : 1;
__REG32                 : 3;
__REG32 PPS             : 1;
__REG32 LSDA            : 1;
__REG32                 : 6;
__REG32 CSC             : 1;
__REG32 PESC            : 1;
__REG32 PSSC            : 1;
__REG32 OCIC            : 1;
__REG32 PRSC            : 1;
__REG32                 :11;
} __HcRhPortStatus_bits;

/* UART Interrupt Enable Register (UART_IER)
   UART Divisor Latch (High Byte) Register (UART_DLM) */
typedef union {
  // UART_IER
  struct {
  __REG32 RDAIE             : 1;
  __REG32 THREIE            : 1;
  __REG32 RLSIE             : 1;
  __REG32 MSIE              : 1;
  __REG32 NDBGACK_EN        : 1;
  __REG32                   :27;
  };
  // UART_DLM
  struct {
  __REG32 BRD_HI            : 8;
  __REG32                   :24;
  };
} __uart_ier_bits;

/* UART Interrupt Identification Register (UART_IIR)
   UART FIFO Control Register (UART_FCR) */
typedef union {
  // UART_IIR
  struct {
  __REG32 NIP               : 1;
  __REG32 IID               : 3;
  __REG32 DMS               : 1;
  __REG32 RFTLS             : 2;
  __REG32 FMES              : 1;
  __REG32                   :24;
  };
// UART_FCR
  struct {
  __REG32 FME               : 1;
  __REG32 RFR               : 1;
  __REG32 TFR               : 1;
  __REG32 MS                : 1;
  __REG32                   : 2;
  __REG32 RFITL             : 2;
  __REG32                   :24;
  };
} __uart_iir_bits;

/* UART Line Control Register (UART_LCR) */
typedef struct {
  __REG32 WLS               : 2;
  __REG32 NSB               : 1;
  __REG32 PBE               : 1;
  __REG32 EPE               : 1;
  __REG32 SPE               : 1;
  __REG32 BCB               : 1;
  __REG32 DLAB              : 1;
  __REG32                   :24;
} __uart_lcr_bits;

/* UART Modem Control Register (UART_MCR) */
typedef struct {
  __REG32 DTR               : 1;
  __REG32 RTS               : 1;
  __REG32 OUT1              : 1;
  __REG32 OUT2              : 1;
  __REG32 LBME              : 1;
  __REG32                   :27;
} __uart_mcr_bits;

/* UART Line Status Control Register (UART_LSR) */
typedef struct {
  __REG32 RFDR              : 1;
  __REG32 OEI               : 1;
  __REG32 PEI               : 1;
  __REG32 FEI               : 1;
  __REG32 BII               : 1;
  __REG32 THRE              : 1;
  __REG32 TE                : 1;
  __REG32 ERR_RX            : 1;
  __REG32                   :24;
} __uart_lsr_bits;

/* UART Modem Status Register (UART_MSR) */
typedef struct {
  __REG32 DCTS              : 1;
  __REG32 DDSR              : 1;
  __REG32 TERI              : 1;
  __REG32 DDCD              : 1;
  __REG32 CTS               : 1;
  __REG32 DSR               : 1;
  __REG32 RI                : 1;
  __REG32 DCD               : 1;
  __REG32                   :24;
} __uart_msr_bits;

/* UART Time Out Register (UART_TOR) */
typedef struct {
  __REG32 TOIC              : 7;
  __REG32 TOIE              : 1;
  __REG32                   :24;
} __uart_tor_bits;

/* Timer Control Register 0/1 (TCSR 0/1) */
typedef struct {
  __REG32 PRESCALE          : 8;
  __REG32                   :19;
  __REG32 MODE              : 2;
  __REG32 IE                : 1;
  __REG32 CEN               : 1;
  __REG32 NDBGACK_EN        : 1;
} __tcsr_bits;

/* Timer Initial Count Register 0/1 (TICR0/1) */
typedef struct {
  __REG32 TIC               :24;
  __REG32                   : 8;
} __ticr_bits;

/* Timer Data Register 0/1 (TDR0/1) */
typedef struct {
  __REG32 TDR               :24;
  __REG32                   : 8;
} __tdr_bits;

/* Timer Interrupt Status Register (TISR) */
typedef struct {
  __REG32 TIF0              : 1;
  __REG32 TIF1              : 1;
  __REG32                   :30;
} __tisr_bits;

/* Watchdog Timer Control Register (WTCR) */
typedef struct {
  __REG32 WTR               : 1;
  __REG32 WTRE              : 1;
  __REG32 WTRF              : 1;
  __REG32 WTIF              : 1;
  __REG32 WTIS              : 2;
  __REG32 WTIE              : 1;
  __REG32 WTE               : 1;
  __REG32                   : 1;
  __REG32 NDBGACK_EN        : 1;
  __REG32                   :22;
} __wtcr_bits;

/* AIC Source Control Registers (AIC_SCR1 ~ AIC_SCR31) */
typedef struct {
  __REG32 PRIORITY          : 3;
  __REG32                   : 3;
  __REG32 SRCTYPE           : 2;
  __REG32                   :24;
} __aic_scr_bits;

/* AIC Interrupt Raw Status Register (AIC_IRSR) */
typedef struct {
  __REG32                   : 1;
  __REG32 IRS1              : 1;
  __REG32 IRS2              : 1;
  __REG32 IRS3              : 1;
  __REG32 IRS4              : 1;
  __REG32 IRS5              : 1;
  __REG32 IRS6              : 1;
  __REG32 IRS7              : 1;
  __REG32 IRS8              : 1;
  __REG32 IRS9              : 1;
  __REG32 IRS10             : 1;
  __REG32 IRS11             : 1;
  __REG32 IRS12             : 1;
  __REG32 IRS13             : 1;
  __REG32 IRS14             : 1;
  __REG32 IRS15             : 1;
  __REG32 IRS16             : 1;
  __REG32 IRS17             : 1;
  __REG32 IRS18             : 1;
  __REG32                   :13;
} __aic_irsr_bits;

/* AIC Interrupt Active Status Register (AIC_IASR) */
typedef struct {
  __REG32                   : 1;
  __REG32 IAS1              : 1;
  __REG32 IAS2              : 1;
  __REG32 IAS3              : 1;
  __REG32 IAS4              : 1;
  __REG32 IAS5              : 1;
  __REG32 IAS6              : 1;
  __REG32 IAS7              : 1;
  __REG32 IAS8              : 1;
  __REG32 IAS9              : 1;
  __REG32 IAS10             : 1;
  __REG32 IAS11             : 1;
  __REG32 IAS12             : 1;
  __REG32 IAS13             : 1;
  __REG32 IAS14             : 1;
  __REG32 IAS15             : 1;
  __REG32 IAS16             : 1;
  __REG32 IAS17             : 1;
  __REG32 IAS18             : 1;
  __REG32                   :13;
} __aic_iasr_bits;

/* AIC Interrupt Status Register (AIC_ISR) */
typedef struct {
  __REG32                   : 1;
  __REG32 IS1               : 1;
  __REG32 IS2               : 1;
  __REG32 IS3               : 1;
  __REG32 IS4               : 1;
  __REG32 IS5               : 1;
  __REG32 IS6               : 1;
  __REG32 IS7               : 1;
  __REG32 IS8               : 1;
  __REG32 IS9               : 1;
  __REG32 IS10              : 1;
  __REG32 IS11              : 1;
  __REG32 IS12              : 1;
  __REG32 IS13              : 1;
  __REG32 IS14              : 1;
  __REG32 IS15              : 1;
  __REG32 IS16              : 1;
  __REG32 IS17              : 1;
  __REG32 IS18              : 1;
  __REG32                   :13;
} __aic_isr_bits;

/* AIC IRQ Priority Encoding Register (AIC_IPER) */
typedef struct {
  __REG32                   : 2;
  __REG32 VECTOR            : 5;
  __REG32                   :25;
} __aic_iper_bits;

/* AIC Interrupt Source Number Register (AIC_ISNR) */
typedef struct {
  __REG32 IRQID             : 5;
  __REG32                   :27;
} __aic_isnr_bits;

/* AIC Interrupt Mask Register (AIC_IMR) */
typedef struct {
  __REG32                   : 1;
  __REG32 IM1               : 1;
  __REG32 IM2               : 1;
  __REG32 IM3               : 1;
  __REG32 IM4               : 1;
  __REG32 IM5               : 1;
  __REG32 IM6               : 1;
  __REG32 IM7               : 1;
  __REG32 IM8               : 1;
  __REG32 IM9               : 1;
  __REG32 IM10              : 1;
  __REG32 IM11              : 1;
  __REG32 IM12              : 1;
  __REG32 IM13              : 1;
  __REG32 IM14              : 1;
  __REG32 IM15              : 1;
  __REG32 IM16              : 1;
  __REG32 IM17              : 1;
  __REG32 IM18              : 1;
  __REG32                   :13;
} __aic_imr_bits;

/* AIC Output Interrupt Status Register (AIC_OISR) */
typedef struct {
  __REG32 FIQ               : 1;
  __REG32 IRQ               : 1;
  __REG32                   :30;
} __aic_oisr_bits;

/* AIC Mask Enable Command Register (AIC_MECR) */
typedef struct {
  __REG32                   : 1;
  __REG32 MEC1              : 1;
  __REG32 MEC2              : 1;
  __REG32 MEC3              : 1;
  __REG32 MEC4              : 1;
  __REG32 MEC5              : 1;
  __REG32 MEC6              : 1;
  __REG32 MEC7              : 1;
  __REG32 MEC8              : 1;
  __REG32 MEC9              : 1;
  __REG32 MEC10             : 1;
  __REG32 MEC11             : 1;
  __REG32 MEC12             : 1;
  __REG32 MEC13             : 1;
  __REG32 MEC14             : 1;
  __REG32 MEC15             : 1;
  __REG32 MEC16             : 1;
  __REG32 MEC17             : 1;
  __REG32 MEC18             : 1;
  __REG32                   :13;
} __aic_mecr_bits;

/* AIC Mask Disable Command Register (AIC_MDCR) */
typedef struct {
  __REG32                   : 1;
  __REG32 MDC1              : 1;
  __REG32 MDC2              : 1;
  __REG32 MDC3              : 1;
  __REG32 MDC4              : 1;
  __REG32 MDC5              : 1;
  __REG32 MDC6              : 1;
  __REG32 MDC7              : 1;
  __REG32 MDC8              : 1;
  __REG32 MDC9              : 1;
  __REG32 MDC10             : 1;
  __REG32 MDC11             : 1;
  __REG32 MDC12             : 1;
  __REG32 MDC13             : 1;
  __REG32 MDC14             : 1;
  __REG32 MDC15             : 1;
  __REG32 MDC16             : 1;
  __REG32 MDC17             : 1;
  __REG32 MDC18             : 1;
  __REG32                   :13;
} __aic_mdcr_bits;

/* AIC Source Set Command Register (AIC_SSCR) */
typedef struct {
  __REG32                   : 1;
  __REG32 SSC1              : 1;
  __REG32 SSC2              : 1;
  __REG32 SSC3              : 1;
  __REG32 SSC4              : 1;
  __REG32 SSC5              : 1;
  __REG32 SSC6              : 1;
  __REG32 SSC7              : 1;
  __REG32 SSC8              : 1;
  __REG32 SSC9              : 1;
  __REG32 SSC10             : 1;
  __REG32 SSC11             : 1;
  __REG32 SSC12             : 1;
  __REG32 SSC13             : 1;
  __REG32 SSC14             : 1;
  __REG32 SSC15             : 1;
  __REG32 SSC16             : 1;
  __REG32 SSC17             : 1;
  __REG32 SSC18             : 1;
  __REG32                   :13;
} __aic_sscr_bits;

/* AIC Source Clear Command Register (AIC_SCCR) */
typedef struct {
  __REG32                   : 1;
  __REG32 SCC1              : 1;
  __REG32 SCC2              : 1;
  __REG32 SCC3              : 1;
  __REG32 SCC4              : 1;
  __REG32 SCC5              : 1;
  __REG32 SCC6              : 1;
  __REG32 SCC7              : 1;
  __REG32 SCC8              : 1;
  __REG32 SCC9              : 1;
  __REG32 SCC10             : 1;
  __REG32 SCC11             : 1;
  __REG32 SCC12             : 1;
  __REG32 SCC13             : 1;
  __REG32 SCC14             : 1;
  __REG32 SCC15             : 1;
  __REG32 SCC16             : 1;
  __REG32 SCC17             : 1;
  __REG32 SCC18             : 1;
  __REG32                   :13;
} __aic_sccr_bits;

/* GPIO Port Configuration Register (GPIO_CFG) */
typedef struct {
  __REG32 GPIOCFG3_0        : 2;
  __REG32 GPIOCFG9_4        : 2;
  __REG32 GPIOCFG11_10      : 2;
  __REG32 GPIOCFG12         : 2;
  __REG32 GPIOCFG13         : 2;
  __REG32 GPIOCFG14         : 2;
  __REG32 GPIOCFG16_15      : 2;
  __REG32 GPIOCFG17         : 2;
  __REG32 GPIOCFG18         : 2;
  __REG32 GPIOCFG19         : 2;
  __REG32 GPIOCFG20         : 2;
  __REG32                   :10;
} __gpio_cfg_bits;

/* GPIO Port Direction Register (GPIO_DIR) */
typedef struct {
  __REG32 GPIOD0            : 1;
  __REG32 GPIOD1            : 1;
  __REG32 GPIOD2            : 1;
  __REG32 GPIOD3            : 1;
  __REG32 GPIOD4            : 1;
  __REG32 GPIOD5            : 1;
  __REG32 GPIOD6            : 1;
  __REG32 GPIOD7            : 1;
  __REG32 GPIOD8            : 1;
  __REG32 GPIOD9            : 1;
  __REG32 GPIOD10           : 1;
  __REG32 GPIOD11           : 1;
  __REG32 GPIOD12           : 1;
  __REG32 GPIOD13           : 1;
  __REG32 GPIOD14           : 1;
  __REG32 GPIOD15           : 1;
  __REG32 GPIOD16           : 1;
  __REG32 GPIOD17           : 1;
  __REG32 GPIOD18           : 1;
  __REG32 GPIOD19           : 1;
  __REG32 GPIOD20           : 1;
  __REG32                   :11;
} __gpio_dir_bits;

/* GPIO Port Data Output Register (GPIO_DATAOUT) */
typedef struct {
  __REG32 GPIODO0           : 1;
  __REG32 GPIODO1           : 1;
  __REG32 GPIODO2           : 1;
  __REG32 GPIODO3           : 1;
  __REG32 GPIODO4           : 1;
  __REG32 GPIODO5           : 1;
  __REG32 GPIODO6           : 1;
  __REG32 GPIODO7           : 1;
  __REG32 GPIODO8           : 1;
  __REG32 GPIODO9           : 1;
  __REG32 GPIODO10          : 1;
  __REG32 GPIODO11          : 1;
  __REG32 GPIODO12          : 1;
  __REG32 GPIODO13          : 1;
  __REG32 GPIODO14          : 1;
  __REG32 GPIODO15          : 1;
  __REG32 GPIODO16          : 1;
  __REG32 GPIODO17          : 1;
  __REG32 GPIODO18          : 1;
  __REG32 GPIODO19          : 1;
  __REG32 GPIODO20          : 1;
  __REG32                   :11;
} __gpio_dataout_bits;

/* GPIO Port Data Input Register (GPIO_DATAIN) */
typedef struct {
  __REG32 GPIODI0           : 1;
  __REG32 GPIODI1           : 1;
  __REG32 GPIODI2           : 1;
  __REG32 GPIODI3           : 1;
  __REG32 GPIODI4           : 1;
  __REG32 GPIODI5           : 1;
  __REG32 GPIODI6           : 1;
  __REG32 GPIODI7           : 1;
  __REG32 GPIODI8           : 1;
  __REG32 GPIODI9           : 1;
  __REG32 GPIODI10          : 1;
  __REG32 GPIODI11          : 1;
  __REG32 GPIODI12          : 1;
  __REG32 GPIODI13          : 1;
  __REG32 GPIODI14          : 1;
  __REG32 GPIODI15          : 1;
  __REG32 GPIODI16          : 1;
  __REG32 GPIODI17          : 1;
  __REG32 GPIODI18          : 1;
  __REG32 GPIODI19          : 1;
  __REG32 GPIODI20          : 1;
  __REG32                   :11;
} __gpio_datain_bits;

/* Debounce Control Register (DEBNCE_CTRL) */
typedef struct {
  __REG32 DBE0              : 1;
  __REG32 DBE1              : 1;
  __REG32 DBE2              : 1;
  __REG32 DBE3              : 1;
  __REG32 DBCLKSEL          : 3;
  __REG32                   :25;
} __debnce_ctrl_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */
/***************************************************************************/
/* Common declarations  ****************************************************/
/***************************************************************************
 **
 ** SMC
 **
 ***************************************************************************/
__IO_REG32_BIT(PDID,                  0xFFF00000,__READ       ,__pdid_bits);
__IO_REG32_BIT(ARBCON,                0xFFF00004,__READ_WRITE ,__arbcon_bits);
__IO_REG32_BIT(PLLCON,                0xFFF00008,__READ_WRITE ,__pllcon_bits);
__IO_REG32_BIT(CLKSEL,                0xFFF0000C,__READ_WRITE ,__clksel_bits);

/***************************************************************************
 **
 ** EBI
 **
 ***************************************************************************/
__IO_REG32_BIT(EBICON,                0xFFF01000,__READ_WRITE ,__ebicon_bits);
__IO_REG32_BIT(ROMCON,                0xFFF01004,__READ_WRITE ,__romcon_bits);
__IO_REG32_BIT(SDCONF0,               0xFFF01008,__READ_WRITE ,__sdconf_bits);
__IO_REG32_BIT(SDCONF1,               0xFFF0100C,__READ_WRITE ,__sdconf_bits);
__IO_REG32_BIT(SDTIME0,               0xFFF01010,__READ_WRITE ,__sdtime_bits);
__IO_REG32_BIT(SDTIME1,               0xFFF01014,__READ_WRITE ,__sdtime_bits);
__IO_REG32_BIT(EXT0CON,               0xFFF01018,__READ_WRITE ,__extcon_bits);
__IO_REG32_BIT(EXT1CON,               0xFFF0101C,__READ_WRITE ,__extcon_bits);
__IO_REG32_BIT(EXT2CON,               0xFFF01020,__READ_WRITE ,__extcon_bits);
__IO_REG32_BIT(EXT3CON,               0xFFF01024,__READ_WRITE ,__extcon_bits);
__IO_REG32_BIT(CKSKEW,                0xFFF01F00,__READ_WRITE ,__ckskew_bits);

/***************************************************************************
 **
 ** Cache
 **
 ***************************************************************************/
__IO_REG32_BIT(CAHCNF,                0xFFF02000,__READ_WRITE ,__cahcnf_bits);
__IO_REG32_BIT(CAHCON,                0xFFF02004,__READ_WRITE ,__cahcon_bits);
__IO_REG32_BIT(CAHADR,                0xFFF02008,__READ_WRITE ,__cahadr_bits);
__IO_REG32(    CTEST0,                0xFFF60000,__READ_WRITE );
__IO_REG32(    CTEST1,                0xFFF60004,__READ       );

/***************************************************************************
 **
 ** EMC0
 **
 ***************************************************************************/
__IO_REG32_BIT(CAMCMR_0,              0xFFF03000,__READ_WRITE ,__camcmr_bits);
__IO_REG32_BIT(CAMEN_0,               0xFFF03004,__READ_WRITE ,__camen_bits);
__IO_REG32_BIT(CAM0M_0,               0xFFF03008,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM0L_0,               0xFFF0300C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM1M_0,               0xFFF03010,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM1L_0,               0xFFF03014,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM2M_0,               0xFFF03018,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM2L_0,               0xFFF0301C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM3M_0,               0xFFF03020,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM3L_0,               0xFFF03024,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM4M_0,               0xFFF03028,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM4L_0,               0xFFF0302C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM5M_0,               0xFFF03030,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM5L_0,               0xFFF03034,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM6M_0,               0xFFF03038,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM6L_0,               0xFFF0303C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM7M_0,               0xFFF03040,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM7L_0,               0xFFF03044,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM8M_0,               0xFFF03048,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM8L_0,               0xFFF0304C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM9M_0,               0xFFF03050,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM9L_0,               0xFFF03054,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM10M_0,              0xFFF03058,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM10L_0,              0xFFF0305C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM11M_0,              0xFFF03060,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM11L_0,              0xFFF03064,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM12M_0,              0xFFF03068,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM12L_0,              0xFFF0306C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM13M_0,              0xFFF03070,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM13L_0,              0xFFF03074,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM14M_0,              0xFFF03078,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM14L_0,              0xFFF0307C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM15M_0,              0xFFF03080,__READ_WRITE ,__cam15m_bits);
__IO_REG32_BIT(CAM15L_0,              0xFFF03084,__READ_WRITE ,__cam15l_bits);
__IO_REG32_BIT(MIEN_0,                0xFFF03088,__READ_WRITE ,__mien_bits);
__IO_REG32_BIT(MCMDR_0,               0xFFF0308C,__READ_WRITE ,__mcmdr_bits);
__IO_REG32_BIT(MIID_0,                0xFFF03090,__READ_WRITE ,__miid_bits);
__IO_REG32_BIT(MIIDA_0,               0xFFF03094,__READ_WRITE ,__miida_bits);
__IO_REG32_BIT(MPCNT_0,               0xFFF03098,__READ_WRITE ,__mpcnt_bits);
__IO_REG32(    TXDLSA_0,              0xFFF0309C,__READ_WRITE );
__IO_REG32(    RXDLSA_0,              0xFFF030A0,__READ_WRITE );
__IO_REG32_BIT(DMARFC_0,              0xFFF030A4,__READ_WRITE ,__dmarfc_bits);
__IO_REG32(    TSDR_0,                0xFFF030A8,__WRITE      );
__IO_REG32(    RSDR_0,                0xFFF030AC,__WRITE      );
__IO_REG32_BIT(FIFOTHD_0,             0xFFF030B0,__READ_WRITE ,__fifothd_bits);
__IO_REG32_BIT(MISTA_0,               0xFFF030B4,__READ_WRITE ,__mista_bits);
__IO_REG32_BIT(MGSTA_0,               0xFFF030B8,__READ_WRITE ,__mgsta_bits);
__IO_REG32_BIT(MRPC_0,                0xFFF030BC,__READ       ,__mrpc_bits);
__IO_REG32_BIT(MRPCC_0,               0xFFF030C0,__READ       ,__mrpcc_bits);
__IO_REG32_BIT(MREPC_0,               0xFFF030C4,__READ       ,__mrepc_bits);
__IO_REG32_BIT(DMARFS_0,              0xFFF030C8,__READ_WRITE ,__dmarfs_bits);
__IO_REG32(    CTXDSA_0,              0xFFF030CC,__READ       );
__IO_REG32(    CTXBSA_0,              0xFFF030D0,__READ       );
__IO_REG32(    CRXDSA_0,              0xFFF030D4,__READ       );
__IO_REG32(    CRXBSA_0,              0xFFF030D8,__READ       );

/***************************************************************************
 **
 ** EMC1
 **
 ***************************************************************************/
__IO_REG32_BIT(CAMCMR_1,              0xFFF03800,__READ_WRITE ,__camcmr_bits);
__IO_REG32_BIT(CAMEN_1,               0xFFF03804,__READ_WRITE ,__camen_bits);
__IO_REG32_BIT(CAM0M_1,               0xFFF03808,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM0L_1,               0xFFF0380C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM1M_1,               0xFFF03810,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM1L_1,               0xFFF03814,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM2M_1,               0xFFF03818,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM2L_1,               0xFFF0381C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM3M_1,               0xFFF03820,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM3L_1,               0xFFF03824,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM4M_1,               0xFFF03828,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM4L_1,               0xFFF0382C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM5M_1,               0xFFF03830,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM5L_1,               0xFFF03834,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM6M_1,               0xFFF03838,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM6L_1,               0xFFF0383C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM7M_1,               0xFFF03840,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM7L_1,               0xFFF03844,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM8M_1,               0xFFF03848,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM8L_1,               0xFFF0384C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM9M_1,               0xFFF03850,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM9L_1,               0xFFF03854,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM10M_1,              0xFFF03858,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM10L_1,              0xFFF0385C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM11M_1,              0xFFF03860,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM11L_1,              0xFFF03864,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM12M_1,              0xFFF03868,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM12L_1,              0xFFF0386C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM13M_1,              0xFFF03870,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM13L_1,              0xFFF03874,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM14M_1,              0xFFF03878,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM14L_1,              0xFFF0387C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM15M_1,              0xFFF03880,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM15L_1,              0xFFF03884,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(MIEN_1,                0xFFF03888,__READ_WRITE ,__mien_bits);
__IO_REG32_BIT(MCMDR_1,               0xFFF0388C,__READ_WRITE ,__mcmdr_bits);
__IO_REG32_BIT(MIID_1,                0xFFF03890,__READ_WRITE ,__miid_bits);
__IO_REG32_BIT(MIIDA_1,               0xFFF03894,__READ_WRITE ,__miida_bits);
__IO_REG32_BIT(MPCNT_1,               0xFFF03898,__READ_WRITE ,__mpcnt_bits);
__IO_REG32(    TXDLSA_1,              0xFFF0389C,__READ_WRITE );
__IO_REG32(    RXDLSA_1,              0xFFF038A0,__READ_WRITE );
__IO_REG32_BIT(DMARFC_1,              0xFFF038A4,__READ_WRITE ,__dmarfc_bits);
__IO_REG32(    TSDR_1,                0xFFF038A8,__WRITE      );
__IO_REG32(    RSDR_1,                0xFFF038AC,__WRITE      );
__IO_REG32_BIT(FIFOTHD_1,             0xFFF038B0,__READ_WRITE ,__fifothd_bits);
__IO_REG32_BIT(MISTA_1,               0xFFF038B4,__READ_WRITE ,__mista_bits);
__IO_REG32_BIT(MGSTA_1,               0xFFF038B8,__READ_WRITE ,__mgsta_bits);
__IO_REG32_BIT(MRPC_1,                0xFFF038BC,__READ       ,__mrpc_bits);
__IO_REG32_BIT(MRPCC_1,               0xFFF038C0,__READ       ,__mrpcc_bits);
__IO_REG32_BIT(MREPC_1,               0xFFF038C4,__READ       ,__mrepc_bits);
__IO_REG32_BIT(DMARFS_1,              0xFFF038C8,__READ_WRITE ,__dmarfs_bits);
__IO_REG32(    CTXDSA_1,              0xFFF038CC,__READ       );
__IO_REG32(    CTXBSA_1,              0xFFF038D0,__READ       );
__IO_REG32(    CRXDSA_1,              0xFFF038D4,__READ       );
__IO_REG32(    CRXBSA_1,              0xFFF038D8,__READ       );

/***************************************************************************
 **
 ** NATA
 **
 ***************************************************************************/
__IO_REG32_BIT(NATCMD,                0xFFF06000,__READ_WRITE ,__natcmd_bits);
__IO_REG32_BIT(NATCCLR0,              0xFFF06010,__WRITE      ,__natcclr0_bits);
__IO_REG32_BIT(NATCCLR1,              0xFFF06014,__WRITE      ,__natcclr1_bits);
__IO_REG32_BIT(NATCCLR2,              0xFFF06018,__WRITE      ,__natcclr2_bits);
__IO_REG32_BIT(NATCCLR3,              0xFFF0601C,__WRITE      ,__natcclr3_bits);
__IO_REG32_BIT(NATCFG0,               0xFFF06100,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG1,               0xFFF06104,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG2,               0xFFF06108,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG3,               0xFFF0610C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG4,               0xFFF06110,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG5,               0xFFF06114,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG6,               0xFFF06118,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG7,               0xFFF0611C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG8,               0xFFF06120,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG9,               0xFFF06124,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG10,              0xFFF06128,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG11,              0xFFF0612C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG12,              0xFFF06130,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG13,              0xFFF06134,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG14,              0xFFF06138,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG15,              0xFFF0613C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG16,              0xFFF06140,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG17,              0xFFF06144,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG18,              0xFFF06148,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG19,              0xFFF0614C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG20,              0xFFF06150,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG21,              0xFFF06154,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG22,              0xFFF06158,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG23,              0xFFF0615C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG24,              0xFFF06160,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG25,              0xFFF06164,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG26,              0xFFF06168,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG27,              0xFFF0616C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG28,              0xFFF06170,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG29,              0xFFF06174,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG30,              0xFFF06178,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG31,              0xFFF0617C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG32,              0xFFF06180,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG33,              0xFFF06184,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG34,              0xFFF06188,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG35,              0xFFF0618C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG36,              0xFFF06190,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG37,              0xFFF06194,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG38,              0xFFF06198,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG39,              0xFFF0619C,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG40,              0xFFF061A0,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG41,              0xFFF061A4,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG42,              0xFFF061A8,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG43,              0xFFF061AC,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG44,              0xFFF061B0,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG45,              0xFFF061B4,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG46,              0xFFF061B8,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG47,              0xFFF061BC,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG48,              0xFFF061C0,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG49,              0xFFF061C4,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG50,              0xFFF061C8,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG51,              0xFFF061CC,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG52,              0xFFF061D0,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG53,              0xFFF061D4,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG54,              0xFFF061D8,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG55,              0xFFF061DC,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG56,              0xFFF061E0,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG57,              0xFFF061E4,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG58,              0xFFF061E8,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG59,              0xFFF061EC,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG60,              0xFFF061F0,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG61,              0xFFF061F4,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG62,              0xFFF061F8,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(NATCFG63,              0xFFF061FC,__READ_WRITE ,__natcfg_bits);
__IO_REG32_BIT(EXMACM,                0xFFF06200,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(EXMACL,                0xFFF06204,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(INMACM,                0xFFF06208,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(INMACL,                0xFFF0620C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD0,                0xFFF06800,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN0,                0xFFF06804,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD0,                 0xFFF06808,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN0,                 0xFFF0680C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC0M,               0xFFF06810,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC0L,               0xFFF06814,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC0M,               0xFFF06818,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC0L,               0xFFF0681C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD1,                0xFFF06820,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN1,                0xFFF06824,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD1,                 0xFFF06828,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN1,                 0xFFF0682C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC1M,               0xFFF06830,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC1L,               0xFFF06834,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC1M,               0xFFF06838,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC1L,               0xFFF0683C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD2,                0xFFF06840,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN2,                0xFFF06844,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD2,                 0xFFF06848,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN2,                 0xFFF0684C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC2M,               0xFFF06850,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC2L,               0xFFF06854,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC2M,               0xFFF06858,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC2L,               0xFFF0685C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD3,                0xFFF06860,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN3,                0xFFF06864,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD3,                 0xFFF06868,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN3,                 0xFFF0686C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC3M,               0xFFF06870,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC3L,               0xFFF06874,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC3M,               0xFFF06878,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC3L,               0xFFF0687C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD4,                0xFFF06880,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN4,                0xFFF06884,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD4,                 0xFFF06888,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN4,                 0xFFF0688C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC4M,               0xFFF06890,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC4L,               0xFFF06894,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC4M,               0xFFF06898,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC4L,               0xFFF0689C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD5,                0xFFF068A0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN5,                0xFFF068A4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD5,                 0xFFF068A8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN5,                 0xFFF068AC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC5M,               0xFFF068B0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC5L,               0xFFF068B4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC5M,               0xFFF068B8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC5L,               0xFFF068BC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD6,                0xFFF068C0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN6,                0xFFF068C4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD6,                 0xFFF068C8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN6,                 0xFFF068CC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC6M,               0xFFF068D0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC6L,               0xFFF068D4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC6M,               0xFFF068D8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC6L,               0xFFF068DC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD7,                0xFFF068E0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN7,                0xFFF068E4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD7,                 0xFFF068E8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN7,                 0xFFF068EC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC7M,               0xFFF068F0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC7L,               0xFFF068F4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC7M,               0xFFF068F8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC7L,               0xFFF068FC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD8,                0xFFF06900,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN8,                0xFFF06904,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD8,                 0xFFF06908,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN8,                 0xFFF0690C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC8M,               0xFFF06910,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC8L,               0xFFF06914,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC8M,               0xFFF06918,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC8L,               0xFFF0691C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD9,                0xFFF06920,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN9,                0xFFF06924,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD9,                 0xFFF06928,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN9,                 0xFFF0692C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC9M,               0xFFF06930,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC9L,               0xFFF06934,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC9M,               0xFFF06938,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC9L,               0xFFF0693C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD10,               0xFFF06940,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN10,               0xFFF06944,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD10,                0xFFF06948,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN10,                0xFFF0694C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC10M,              0xFFF06950,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC10L,              0xFFF06954,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC10M,              0xFFF06958,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC10L,              0xFFF0695C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD11,               0xFFF06960,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN11,               0xFFF06964,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD11,                0xFFF06968,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN11,                0xFFF0696C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC11M,              0xFFF06970,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC11L,              0xFFF06974,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC11M,              0xFFF06978,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC11L,              0xFFF0697C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD12,               0xFFF06980,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN12,               0xFFF06984,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD12,                0xFFF06988,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN12,                0xFFF0698C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC12M,              0xFFF06990,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC12L,              0xFFF06994,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC12M,              0xFFF06998,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC12L,              0xFFF0699C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD13,               0xFFF069A0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN13,               0xFFF069A4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD13,                0xFFF069A8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN13,                0xFFF069AC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC13M,              0xFFF069B0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC13L,              0xFFF069B4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC13M,              0xFFF069B8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC13L,              0xFFF069BC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD14,               0xFFF069C0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN14,               0xFFF069C4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD14,                0xFFF069C8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN14,                0xFFF069CC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC14M,              0xFFF069D0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC14L,              0xFFF069D4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC14M,              0xFFF069D8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC14L,              0xFFF069DC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD15,               0xFFF069E0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN15,               0xFFF069E4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD15,                0xFFF069E8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN15,                0xFFF069EC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC15M,              0xFFF069F0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC15L,              0xFFF069F4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC15M,              0xFFF069F8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC15L,              0xFFF069FC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD16,               0xFFF06A00,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN16,               0xFFF06A04,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD16,                0xFFF06A08,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN16,                0xFFF06A0C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC16M,              0xFFF06A10,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC16L,              0xFFF06A14,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC16M,              0xFFF06A18,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC16L,              0xFFF06A1C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD17,               0xFFF06A20,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN17,               0xFFF06A24,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD17,                0xFFF06A28,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN17,                0xFFF06A2C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC17M,              0xFFF06A30,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC17L,              0xFFF06A34,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC17M,              0xFFF06A38,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC17L,              0xFFF06A3C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD18,               0xFFF06A40,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN18,               0xFFF06A44,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD18,                0xFFF06A48,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN18,                0xFFF06A4C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC18M,              0xFFF06A50,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC18L,              0xFFF06A54,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC18M,              0xFFF06A58,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC18L,              0xFFF06A5C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD19,               0xFFF06A60,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN19,               0xFFF06A64,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD19,                0xFFF06A68,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN19,                0xFFF06A6C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC19M,              0xFFF06A70,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC19L,              0xFFF06A74,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC19M,              0xFFF06A78,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC19L,              0xFFF06A7C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD20,               0xFFF06A80,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN20,               0xFFF06A84,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD20,                0xFFF06A88,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN20,                0xFFF06A8C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC20M,              0xFFF06A90,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC20L,              0xFFF06A94,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC20M,              0xFFF06A98,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC20L,              0xFFF06A9C,__READ_WRITE ,__exmacl_bits);

__IO_REG32_BIT(MASAD21,               0xFFF06AA0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN21,               0xFFF06AA4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD21,                0xFFF06AA8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN21,                0xFFF06AAC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC21M,              0xFFF06AB0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC21L,              0xFFF06AB4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC21M,              0xFFF06AB8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC21L,              0xFFF06ABC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD22,               0xFFF06AC0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN22,               0xFFF06AC4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD22,                0xFFF06AC8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN22,                0xFFF06ACC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC22M,              0xFFF06AD0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC22L,              0xFFF06AD4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC22M,              0xFFF06AD8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC22L,              0xFFF06ADC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD23,               0xFFF06AE0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN23,               0xFFF06AE4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD23,                0xFFF06AE8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN23,                0xFFF06AEC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC23M,              0xFFF06AF0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC23L,              0xFFF06AF4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC23M,              0xFFF06AF8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC23L,              0xFFF06AFC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD24,               0xFFF06B00,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN24,               0xFFF06B04,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD24,                0xFFF06B08,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN24,                0xFFF06B0C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC24M,              0xFFF06B10,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC24L,              0xFFF06B14,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC24M,              0xFFF06B18,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC24L,              0xFFF06B1C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD25,               0xFFF06B20,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN25,               0xFFF06B24,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD25,                0xFFF06B28,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN25,                0xFFF06B2C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC25M,              0xFFF06B30,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC25L,              0xFFF06B34,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC25M,              0xFFF06B38,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC25L,              0xFFF06B3C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD26,               0xFFF06B40,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN26,               0xFFF06B44,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD26,                0xFFF06B48,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN26,                0xFFF06B4C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC26M,              0xFFF06B50,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC26L,              0xFFF06B54,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC26M,              0xFFF06B58,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC26L,              0xFFF06B5C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD27,               0xFFF06B60,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN27,               0xFFF06B64,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD27,                0xFFF06B68,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN27,                0xFFF06B6C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC27M,              0xFFF06B70,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC27L,              0xFFF06B74,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC27M,              0xFFF06B78,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC27L,              0xFFF06B7C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD28,               0xFFF06B80,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN28,               0xFFF06B84,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD28,                0xFFF06B88,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN28,                0xFFF06B8C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC28M,              0xFFF06B90,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC28L,              0xFFF06B94,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC28M,              0xFFF06B98,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC28L,              0xFFF06B9C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD29,               0xFFF06BA0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN29,               0xFFF06BA4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD29,                0xFFF06BA8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN29,                0xFFF06BAC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC29M,              0xFFF06BB0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC29L,              0xFFF06BB4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC29M,              0xFFF06BB8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC29L,              0xFFF06BBC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD30,               0xFFF06BC0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN30,               0xFFF06BC4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD30,                0xFFF06BC8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN30,                0xFFF06BCC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC30M,              0xFFF06BD0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC30L,              0xFFF06BD4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC30M,              0xFFF06BD8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC30L,              0xFFF06BDC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD31,               0xFFF06BE0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN31,               0xFFF06BE4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD31,                0xFFF06BE8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN31,                0xFFF06BEC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC31M,              0xFFF06BF0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC31L,              0xFFF06BF4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC31M,              0xFFF06BF8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC31L,              0xFFF06BFC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD32,               0xFFF06C00,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN32,               0xFFF06C04,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD32,                0xFFF06C08,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN32,                0xFFF06C0C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC32M,              0xFFF06C10,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC32L,              0xFFF06C14,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC32M,              0xFFF06C18,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC32L,              0xFFF06C1C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD33,               0xFFF06C20,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN33,               0xFFF06C24,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD33,                0xFFF06C28,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN33,                0xFFF06C2C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC33M,              0xFFF06C30,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC33L,              0xFFF06C34,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC33M,              0xFFF06C38,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC33L,              0xFFF06C3C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD34,               0xFFF06C40,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN34,               0xFFF06C44,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD34,                0xFFF06C48,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN34,                0xFFF06C4C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC34M,              0xFFF06C50,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC34L,              0xFFF06C54,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC34M,              0xFFF06C58,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC34L,              0xFFF06C5C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD35,               0xFFF06C60,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN35,               0xFFF06C64,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD35,                0xFFF06C68,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN35,                0xFFF06C6C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC35M,              0xFFF06C70,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC35L,              0xFFF06C74,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC35M,              0xFFF06C78,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC35L,              0xFFF06C7C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD36,               0xFFF06C80,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN36,               0xFFF06C84,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD36,                0xFFF06C88,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN36,                0xFFF06C8C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC36M,              0xFFF06C90,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC36L,              0xFFF06C94,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC36M,              0xFFF06C98,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC36L,              0xFFF06C9C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD37,               0xFFF06CA0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN37,               0xFFF06CA4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD37,                0xFFF06CA8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN37,                0xFFF06CAC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC37M,              0xFFF06CB0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC37L,              0xFFF06CB4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC37M,              0xFFF06CB8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC37L,              0xFFF06CBC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD38,               0xFFF06CC0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN38,               0xFFF06CC4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD38,                0xFFF06CC8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN38,                0xFFF06CCC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC38M,              0xFFF06CD0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC38L,              0xFFF06CD4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC38M,              0xFFF06CD8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC38L,              0xFFF06CDC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD39,               0xFFF06CE0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN39,               0xFFF06CE4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD39,                0xFFF06CE8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN39,                0xFFF06CEC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC39M,              0xFFF06CF0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC39L,              0xFFF06CF4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC39M,              0xFFF06CF8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC39L,              0xFFF06CFC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD40,               0xFFF06D00,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN40,               0xFFF06D04,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD40,                0xFFF06D08,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN40,                0xFFF06D0C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC40M,              0xFFF06D10,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC40L,              0xFFF06D14,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC40M,              0xFFF06D18,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC40L,              0xFFF06D1C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD41,               0xFFF06D20,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN41,               0xFFF06D24,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD41,                0xFFF06D28,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN41,                0xFFF06D2C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC41M,              0xFFF06D30,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC41L,              0xFFF06D34,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC41M,              0xFFF06D38,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC41L,              0xFFF06D3C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD42,               0xFFF06D40,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN42,               0xFFF06D44,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD42,                0xFFF06D48,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN42,                0xFFF06D4C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC42M,              0xFFF06D50,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC42L,              0xFFF06D54,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC42M,              0xFFF06D58,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC42L,              0xFFF06D5C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD43,               0xFFF06D60,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN43,               0xFFF06D64,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD43,                0xFFF06D68,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN43,                0xFFF06D6C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC43M,              0xFFF06D70,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC43L,              0xFFF06D74,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC43M,              0xFFF06D78,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC43L,              0xFFF06D7C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD44,               0xFFF06D80,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN44,               0xFFF06D84,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD44,                0xFFF06D88,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN44,                0xFFF06D8C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC44M,              0xFFF06D90,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC44L,              0xFFF06D94,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC44M,              0xFFF06D98,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC44L,              0xFFF06D9C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD45,               0xFFF06DA0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN45,               0xFFF06DA4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD45,                0xFFF06DA8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN45,                0xFFF06DAC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC45M,              0xFFF06DB0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC45L,              0xFFF06DB4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC45M,              0xFFF06DB8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC45L,              0xFFF06DBC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD46,               0xFFF06DC0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN46,               0xFFF06DC4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD46,                0xFFF06DC8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN46,                0xFFF06DCC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC46M,              0xFFF06DD0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC46L,              0xFFF06DD4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC46M,              0xFFF06DD8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC46L,              0xFFF06DDC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD47,               0xFFF06DE0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN47,               0xFFF06DE4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD47,                0xFFF06DE8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN47,                0xFFF06DEC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC47M,              0xFFF06DF0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC47L,              0xFFF06DF4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC47M,              0xFFF06DF8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC47L,              0xFFF06DFC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD48,               0xFFF06E00,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN48,               0xFFF06E04,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD48,                0xFFF06E08,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN48,                0xFFF06E0C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC48M,              0xFFF06E10,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC48L,              0xFFF06E14,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC48M,              0xFFF06E18,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC48L,              0xFFF06E1C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD49,               0xFFF06E20,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN49,               0xFFF06E24,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD49,                0xFFF06E28,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN49,                0xFFF06E2C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC49M,              0xFFF06E30,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC49L,              0xFFF06E34,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC49M,              0xFFF06E38,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC49L,              0xFFF06E3C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD50,               0xFFF06E40,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN50,               0xFFF06E44,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD50,                0xFFF06E48,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN50,                0xFFF06E4C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC50M,              0xFFF06E50,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC50L,              0xFFF06E54,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC50M,              0xFFF06E58,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC50L,              0xFFF06E5C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD51,               0xFFF06E60,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN51,               0xFFF06E64,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD51,                0xFFF06E68,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN51,                0xFFF06E6C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC51M,              0xFFF06E70,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC51L,              0xFFF06E74,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC51M,              0xFFF06E78,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC51L,              0xFFF06E7C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD52,               0xFFF06E80,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN52,               0xFFF06E84,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD52,                0xFFF06E88,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN52,                0xFFF06E8C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC52M,              0xFFF06E90,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC52L,              0xFFF06E94,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC52M,              0xFFF06E98,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC52L,              0xFFF06E9C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD53,               0xFFF06EA0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN53,               0xFFF06EA4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD53,                0xFFF06EA8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN53,                0xFFF06EAC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC53M,              0xFFF06EB0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC53L,              0xFFF06EB4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC53M,              0xFFF06EB8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC53L,              0xFFF06EBC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD54,               0xFFF06EC0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN54,               0xFFF06EC4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD54,                0xFFF06EC8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN54,                0xFFF06ECC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC54M,              0xFFF06ED0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC54L,              0xFFF06ED4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC54M,              0xFFF06ED8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC54L,              0xFFF06EDC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD55,               0xFFF06EE0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN55,               0xFFF06EE4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD55,                0xFFF06EE8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN55,                0xFFF06EEC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC55M,              0xFFF06EF0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC55L,              0xFFF06EF4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC55M,              0xFFF06EF8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC55L,              0xFFF06EFC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD56,               0xFFF06F00,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN56,               0xFFF06F04,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD56,                0xFFF06F08,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN56,                0xFFF06F0C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC56M,              0xFFF06F10,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC56L,              0xFFF06F14,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC56M,              0xFFF06F18,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC56L,              0xFFF06F1C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD57,               0xFFF06F20,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN57,               0xFFF06F24,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD57,                0xFFF06F28,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN57,                0xFFF06F2C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC57M,              0xFFF06F30,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC57L,              0xFFF06F34,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC57M,              0xFFF06F38,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC57L,              0xFFF06F3C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD58,               0xFFF06F40,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN58,               0xFFF06F44,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD58,                0xFFF06F48,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN58,                0xFFF06F4C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC58M,              0xFFF06F50,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC58L,              0xFFF06F54,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC58M,              0xFFF06F58,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC58L,              0xFFF06F5C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD59,               0xFFF06F60,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN59,               0xFFF06F64,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD59,                0xFFF06F68,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN59,                0xFFF06F6C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC59M,              0xFFF06F70,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC59L,              0xFFF06F74,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC59M,              0xFFF06F78,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC59L,              0xFFF06F7C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD60,               0xFFF06F80,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN60,               0xFFF06F84,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD60,                0xFFF06F88,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN60,                0xFFF06F8C,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC60M,              0xFFF06F90,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC60L,              0xFFF06F94,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC60M,              0xFFF06F98,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC60L,              0xFFF06F9C,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD61,               0xFFF06FA0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN61,               0xFFF06FA4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD61,                0xFFF06FA8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN61,                0xFFF06FAC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC61M,              0xFFF06FB0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC61L,              0xFFF06FB4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC61M,              0xFFF06FB8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC61L,              0xFFF06FBC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD62,               0xFFF06FC0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN62,               0xFFF06FC4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD62,                0xFFF06FC8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN62,                0xFFF06FCC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC62M,              0xFFF06FD0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC62L,              0xFFF06FD4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC62M,              0xFFF06FD8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC62L,              0xFFF06FDC,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(MASAD63,               0xFFF06FE0,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(MASPN63,               0xFFF06FE4,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSAD63,                0xFFF06FE8,__READ_WRITE ,__masad_bits);
__IO_REG32_BIT(LSPN63,                0xFFF06FEC,__READ_WRITE ,__maspn_bits);
__IO_REG32_BIT(LSMAC63M,              0xFFF06FF0,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(LSMAC63L,              0xFFF06FF4,__READ_WRITE ,__exmacl_bits);
__IO_REG32_BIT(RSMAC63M,              0xFFF06FF8,__READ_WRITE ,__exmacm_bits);
__IO_REG32_BIT(RSMAC63L,              0xFFF06FFC,__READ_WRITE ,__exmacl_bits);

/***************************************************************************
 **
 ** GDMA0
 **
 ***************************************************************************/
__IO_REG32_BIT(GDMA_CTL0,             0xFFF04000,__READ_WRITE ,__gdma_ctl_bits);
__IO_REG32(    GDMA_SRCB0,            0xFFF04004,__READ_WRITE );
__IO_REG32(    GDMA_DSTB0,            0xFFF04008,__READ_WRITE );
__IO_REG32_BIT(GDMA_TCNT0,            0xFFF0400C,__READ_WRITE ,__gdma_tcnt_bits);
__IO_REG32(    GDMA_CSRC0,            0xFFF04010,__READ       );
__IO_REG32(    GDMA_CDST0,            0xFFF04014,__READ       );
__IO_REG32_BIT(GDMA_CTCNT0,           0xFFF04018,__READ       ,__gdma_tcnt_bits);

/***************************************************************************
 **
 ** GDMA1
 **
 ***************************************************************************/
__IO_REG32_BIT(GDMA_CTL1,             0xFFF04020,__READ_WRITE ,__gdma_ctl_bits);
__IO_REG32(    GDMA_SRCB1,            0xFFF04024,__READ_WRITE );
__IO_REG32(    GDMA_DSTB1,            0xFFF04028,__READ_WRITE );
__IO_REG32_BIT(GDMA_TCNT1,            0xFFF0402C,__READ_WRITE ,__gdma_tcnt_bits);
__IO_REG32(    GDMA_CSRC1,            0xFFF04030,__READ       );
__IO_REG32(    GDMA_CDST1,            0xFFF04034,__READ       );
__IO_REG32_BIT(GDMA_CTCNT1,           0xFFF04038,__READ       ,__gdma_tcnt_bits);

/***************************************************************************
 **
 ** USB Host
 **
 ***************************************************************************/
__IO_REG32_BIT(HcRevision,            0xFFF05000,__READ       ,__HcRevision_bits);
__IO_REG32_BIT(HcControl,             0xFFF05004,__READ_WRITE ,__HcControl_bits);
__IO_REG32_BIT(HcCommandStatus,       0xFFF05008,__READ_WRITE ,__HcCommandStatus_bits);
__IO_REG32_BIT(HcInterruptStatus,     0xFFF0500C,__READ_WRITE ,__HcInterruptStatus_bits);
__IO_REG32_BIT(HcInterruptEnable,     0xFFF05010,__READ_WRITE ,__HcInterruptEnable_bits);
__IO_REG32_BIT(HcInterruptDisable,    0xFFF05014,__READ_WRITE ,__HcInterruptEnable_bits);
__IO_REG32_BIT(HcHCCA,                0xFFF05018,__READ_WRITE ,__HcHCCA_bits);
__IO_REG32_BIT(HcPeriodCurrentED,     0xFFF0501C,__READ_WRITE ,__HcPeriodCurrentED_bits);
__IO_REG32_BIT(HcControlHeadED,       0xFFF05020,__READ_WRITE ,__HcControlHeadED_bits);
__IO_REG32_BIT(HcControlCurrentED,    0xFFF05024,__READ_WRITE ,__HcControlCurrentED_bits);
__IO_REG32_BIT(HcBulkHeadED,          0xFFF05028,__READ_WRITE ,__HcBulkHeadED_bits);
__IO_REG32_BIT(HcBulkCurrentED,       0xFFF0502C,__READ_WRITE ,__HcBulkCurrentED_bits);
__IO_REG32_BIT(HcDoneHead,            0xFFF05030,__READ_WRITE ,__HcDoneHead_bits);
__IO_REG32_BIT(HcFmInterval,          0xFFF05034,__READ_WRITE ,__HcFmInterval_bits);
__IO_REG32_BIT(HcFmRemaining,         0xFFF05038,__READ       ,__HcFmRemaining_bits);
__IO_REG16(    HcFmNumber,            0xFFF0503C,__READ       );
__IO_REG32_BIT(HcPeriodicStart,       0xFFF05040,__READ_WRITE ,__HcPeriodicStart_bits);
__IO_REG32_BIT(HcLSThreshold,         0xFFF05044,__READ_WRITE ,__HcLSThreshold_bits);
__IO_REG32_BIT(HcRhDescriptorA,       0xFFF05048,__READ_WRITE ,__HcRhDescriptorA_bits);
__IO_REG32_BIT(HcRhDescriptorB,       0xFFF0504C,__READ_WRITE ,__HcRhDescriptorB_bits);
__IO_REG32_BIT(HcRhStatus,            0xFFF05050,__READ_WRITE ,__HcRhStatus_bits);
__IO_REG32_BIT(HcRhPortStatus1,       0xFFF05054,__READ_WRITE ,__HcRhPortStatus_bits);
__IO_REG32_BIT(HcRhPortStatus2,       0xFFF05058,__READ_WRITE ,__HcRhPortStatus_bits);

/***************************************************************************
 **
 ** UART
 **
 ***************************************************************************/
__IO_REG8(     UART_RBR,              0xFFF80000,__READ_WRITE );
#define UART_THR      UART_RBR
#define UART_DLL      UART_RBR
__IO_REG32_BIT(UART_IER,              0xFFF80004,__READ_WRITE ,__uart_ier_bits);
#define UART_DLM      UART_IER
#define UART_DLM_bit  UART_IER_bit
__IO_REG32_BIT(UART_IIR,              0xFFF80008,__READ_WRITE ,__uart_iir_bits);
#define UART_FCR      UART_IIR
#define UART_FCR_bit  UART_IIR_bit
__IO_REG32_BIT(UART_LCR,              0xFFF8000C,__READ_WRITE ,__uart_lcr_bits);
__IO_REG32_BIT(UART_MCR,              0xFFF80010,__READ_WRITE ,__uart_mcr_bits);
__IO_REG32_BIT(UART_LSR,              0xFFF80014,__READ       ,__uart_lsr_bits);
__IO_REG32_BIT(UART_MSR,              0xFFF80018,__READ       ,__uart_msr_bits);
__IO_REG32_BIT(UART_TOR,              0xFFF8001C,__READ_WRITE ,__uart_tor_bits);

/***************************************************************************
 **
 ** Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TCSR0,                 0xFFF81000,__READ_WRITE ,__tcsr_bits);
__IO_REG32_BIT(TCSR1,                 0xFFF81004,__READ_WRITE ,__tcsr_bits);
__IO_REG32_BIT(TICR0,                 0xFFF81008,__READ_WRITE ,__ticr_bits);
__IO_REG32_BIT(TICR1,                 0xFFF8100C,__READ_WRITE ,__ticr_bits);
__IO_REG32_BIT(TDR0,                  0xFFF81010,__READ       ,__tdr_bits);
__IO_REG32_BIT(TDR1,                  0xFFF81014,__READ       ,__tdr_bits);
__IO_REG32_BIT(TISR,                  0xFFF81018,__READ_WRITE ,__tisr_bits);

/***************************************************************************
 **
 ** WDT
 **
 ***************************************************************************/
__IO_REG32_BIT(WTCR,                  0xFFF8101C,__READ_WRITE ,__wtcr_bits);

/***************************************************************************
 **
 ** AIC
 **
 ***************************************************************************/
__IO_REG32_BIT(AIC_SCR1,              0xFFF82004,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR2,              0xFFF82008,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR3,              0xFFF8200C,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR4,              0xFFF82010,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR5,              0xFFF82014,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR6,              0xFFF82018,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR7,              0xFFF8201C,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR8,              0xFFF82020,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR9,              0xFFF82024,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR10,             0xFFF82028,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR11,             0xFFF8202C,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR12,             0xFFF82030,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR13,             0xFFF82034,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR14,             0xFFF82038,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR15,             0xFFF8203C,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR16,             0xFFF82040,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR17,             0xFFF82044,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR18,             0xFFF82048,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_IRSR,              0xFFF82100,__READ       ,__aic_irsr_bits);
__IO_REG32_BIT(AIC_IASR,              0xFFF82104,__READ       ,__aic_iasr_bits);
__IO_REG32_BIT(AIC_ISR,               0xFFF82108,__READ       ,__aic_isr_bits);
__IO_REG32_BIT(AIC_IPER,              0xFFF8210C,__READ       ,__aic_iper_bits);
__IO_REG32_BIT(AIC_ISNR,              0xFFF82110,__READ       ,__aic_isnr_bits);
__IO_REG32_BIT(AIC_IMR,               0xFFF82114,__READ       ,__aic_imr_bits);
__IO_REG32_BIT(AIC_OISR,              0xFFF82118,__READ       ,__aic_oisr_bits);
__IO_REG32_BIT(AIC_MECR,              0xFFF82120,__WRITE      ,__aic_mecr_bits);
__IO_REG32_BIT(AIC_MDCR,              0xFFF82124,__WRITE      ,__aic_mdcr_bits);
__IO_REG32_BIT(AIC_SSCR,              0xFFF82128,__WRITE      ,__aic_sscr_bits);
__IO_REG32_BIT(AIC_SCCR,              0xFFF8212C,__WRITE      ,__aic_sccr_bits);
__IO_REG32(    AIC_EOSCR,             0xFFF82130,__WRITE      );

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIO_CFG,              0xFFF83000,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_DIR,              0xFFF83004,__READ_WRITE ,__gpio_dir_bits);
__IO_REG32_BIT(GPIO_DATAOUT,          0xFFF83008,__READ_WRITE ,__gpio_dataout_bits);
__IO_REG32_BIT(GPIO_DATAIN,           0xFFF8300C,__READ       ,__gpio_datain_bits);
__IO_REG32_BIT(DEBNCE_CTRL,           0xFFF83010,__READ_WRITE ,__debnce_ctrl_bits);

/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/
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
 **  VIC Interrupt channels
 **
 ***************************************************************************/
#define AIC_WDT          1  /* Watchdog                                    */
#define AIC_NIRQ0        2  /* External Interrupt 0                        */
#define AIC_NIRQ1        3  /* External Interrupt 1                        */
#define AIC_NIRQ3        4  /* External Interrupt 2                        */
#define AIC_NIRQ4        5  /* External Interrupt 3                        */
#define AIC_UART         6  /* UART Interrupt                              */
#define AIC_TIMER0       7  /* Timer Interrupt 0                           */
#define AIC_TIMER1       8  /* Timer Interrupt 1                           */
#define AIC_USBH0        9  /* USB Host Interrupt 0                        */
#define AIC_USBH1       10  /* USB Host Interrupt 1                        */
#define AIC_EMCTXINT0   13  /* EMC TX Interrupt 0                          */
#define AIC_EMCTXINT1   14  /* EMC TX Interrupt 1                          */
#define AIC_EMCRXINT0   15  /* EMC RX Interrupt 0                          */
#define AIC_EMCRXINT1   16  /* EMC RX Interrupt 1                          */
#define AIC_GDMA0       17  /* GDMA Channel Interrupt 0                    */
#define AIC_GDMA1       18  /* GDMA Channel Interrupt 1                    */

#endif    /* __W91N740_H */
