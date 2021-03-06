/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Winbond W91N745
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1.2.3 $
 **
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/
#ifndef __IOW91N710_H
#define __IOW91N710_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   W91N710 SPECIAL FUNCTION REGISTERS
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

/* PLL Control Register 0-1 (PLLCONx) */
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
__REG32 UART0           : 1;
__REG32 TIMER           : 1;
__REG32 USBH            : 1;
__REG32 WDT             : 1;
__REG32                 : 1;
__REG32 EMC             : 1;
__REG32 LCD             : 1;
__REG32 SD              : 1;
__REG32 GDMA            : 1;
__REG32 USBD            : 1;
__REG32 USBCKS          : 1;
__REG32 AC97            : 1;
__REG32 PWM             : 1;
__REG32 RTC             : 1;
__REG32 I2C0            : 1;
__REG32 I2C1            : 1;
__REG32 UART1           : 1;
__REG32 UART2           : 1;
__REG32 UART3           : 1;
__REG32 USI             : 1;
__REG32 SCH0            : 1;
__REG32 SCH1            : 1;
__REG32 KPI             : 1;
__REG32 PS2             : 1;
__REG32                 : 3;
} __clksel_bits;

/* I2S Clock Control Register (I2SCKCON) */
typedef struct{
__REG32 PRESCALE        : 8;
__REG32 I2SPLLEN        : 1;
__REG32                 :23;
} __i2sckcon_bits;

/* IRQ Wakeup Control Register (IRQWAKECON) */
typedef struct{
__REG32 IRQWAKEUPEN0    : 1;
__REG32 IRQWAKEUPEN1    : 1;
__REG32 IRQWAKEUPEN2    : 1;
__REG32 IRQWAKEUPEN3    : 1;
__REG32 IRQWAKEUPPOL0   : 1;
__REG32 IRQWAKEUPPOL1   : 1;
__REG32 IRQWAKEUPPOL2   : 1;
__REG32 IRQWAKEUPPOL3   : 1;
__REG32                 :24;
} __irqwakecon_bits;

/* IRQ Wakeup Flag Register (IRQWAKEFLAG) */
typedef struct{
__REG32 IRQWAKEFLAG0    : 1;
__REG32 IRQWAKEFLAG1    : 1;
__REG32 IRQWAKEFLAG2    : 1;
__REG32 IRQWAKEFLAG3    : 1;
__REG32                 :28;
} __irqwakeflag_bits;

/* Power Management Control Register (PMCON) */
typedef struct{
__REG32 IDLE            : 1;
__REG32 PD              : 1;
__REG32 MIDLE           : 1;
__REG32                 :29;
} __pmcon_bits;

/* USB Transceiver Control Register (USBTXRCON) */
typedef struct{
__REG32 USBHND          : 1;
__REG32                 :31;
} __usbtxrcon_bits;

/* EBI Control Register (EBICON) */
typedef struct{
__REG32 LITTLE          : 1;
__REG32 WAITVT          : 2;
__REG32 REFRAT          :13;
__REG32 CLKEN           : 1;
__REG32 REFMOD          : 1;
__REG32 REFEN           : 1;
__REG32                 : 5;
__REG32 EXBE0           : 1;
__REG32 EXBE1           : 1;
__REG32 EXBE2           : 1;
__REG32 EXBE3           : 1;
__REG32                 : 4;
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

/* External I/O Control Registers(EXT0CON � EXT3CON) */
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

/* Cache Test Register 0 (CTEST0) */
typedef struct{
__REG32 CATEST          : 1;
__REG32                 : 7;
__REG32 BST_GP0         : 1;
__REG32 BST_GP1         : 1;
__REG32 BST_GP2         : 1;
__REG32 BST_GP3         : 1;
__REG32                 : 3;
__REG32 BISTEN          : 1;
__REG32                 :16;
} __ctest0_bits;

/* Cache Test Register 1 (CTEST1) */
typedef struct{
__REG32 BFAIL0          : 1;
__REG32 BFAIL1          : 1;
__REG32 BFAIL2          : 1;
__REG32 BFAIL3          : 1;
__REG32 BFAIL4          : 1;
__REG32 BFAIL5          : 1;
__REG32 BFAIL6          : 1;
__REG32 BFAIL7          : 1;
__REG32                 :23;
__REG32 FINISH          : 1;
} __ctest1_bits;

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
__REG32 ENSQE           : 1;
__REG32 FDUP            : 1;
__REG32 ENMDC           : 1;
__REG32 OPMOD           : 1;
__REG32 LBK             : 1;
__REG32                 : 2;
__REG32 SWR             : 1;
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
__REG32 WRITE           : 1;
__REG32 BUSY            : 1;
__REG32 PRESP           : 1;
__REG32 MDCON           : 1;
__REG32 MDCCR           : 4;
__REG32                 : 8;
} __miida_bits;

/* FIFO Threshold Control Register (FFTCR) */
typedef struct{
__REG32 RXTHD           : 2;
__REG32                 : 6;
__REG32 TXTHD           : 2;
__REG32                 :10;
__REG32 BLENGTH         : 2;
__REG32                 :10;
} __fftcr_bits;

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
__REG32                 : 2;
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
__REG32                 : 2;
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
__REG32 RFFULL          : 1;
__REG32                 : 1;
__REG32 CCNT            : 4;
__REG32 DEF             : 1;
__REG32 PAU             : 1;
__REG32 SQE             : 1;
__REG32 TXHA            : 1;
__REG32                 :20;
} __mgsta_bits;

/* Missed Packet Count Register (MPCNT) */
typedef struct{
__REG32 MPC             :16;
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
__REG32 RXFLT           :16;
__REG32                 :16;
} __dmarfs_bits;

/* Receive Finite State Machine Register (RXFSM) */
typedef struct{
__REG32 RFF_FSM         : 8;
__REG32 RXCLOSE_FSM     : 4;
__REG32 RXFETCH_FSM     : 4;
__REG32 RXBUF_FSM       : 6;
__REG32                 : 1;
__REG32 RX_FSM          : 9;
} __rxfsm_bits;

/* Transmit Finite State Machine Register (TXFSM) */
typedef struct{
__REG32 TFF_FSM         : 5;
__REG32                 : 3;
__REG32 TXCLOSE_FSM     : 4;
__REG32 TXFETCH_FSM     : 4;
__REG32 TXBUF_FSM       : 6;
__REG32                 : 2;
__REG32 TX_FSM          : 8;
} __txfsm_bits;

/* Finite State Machine Register 0 (FSM0) */
typedef struct{
__REG32 STA_FSM         : 8;
__REG32 TXDEFER_FSM     : 6;
__REG32                 : 2;
__REG32 TXMAC_FSM       :10;
__REG32                 : 6;
} __fsm0_bits;

/* Finite State Machine Register 1 (FSM1) */
typedef struct{
__REG32                 : 8;
__REG32 AHB_FSM         : 6;
__REG32                 :10;
__REG32 TXPAUSE_FSM     : 4;
__REG32 ARB_FSM         : 3;
__REG32                 : 1;
} __fsm1_bits;

/* Debug Configuration Register (DCR) */
typedef struct{
__REG32 CONFIG          : 6;
__REG32 OUT             : 2;
__REG32                 :14;
__REG32 ENABLE          : 2;
__REG32                 : 8;
} __dcr_bits;

/* Debug Mode MAC Information Register (DMMIR) */
typedef struct{
__REG32 RBC             :16;
__REG32                 :16;
} __dmmir_bits;

/* BIST Mode Register (BISTR) */
typedef struct{
__REG32 BMEN            : 1;
__REG32 FINISH          : 1;
__REG32 BISTFAIL        : 2;
__REG32                 :28;
} __bistr_bits;

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
__REG32 RW_TC           : 1;
__REG32 ACK_ATV         : 1;
__REG32 REQ_ATV         : 1;
__REG32 REQ_SEL         : 2;
__REG32 TC_WIDTH        : 3;
__REG32                 : 1;
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

/* USB Operational Mode Enable Register */
typedef struct {
__REG32 DBREG           : 1;
__REG32                 : 2;
__REG32 OVRCUR          : 1;
__REG32                 : 4;
__REG32 SIEPD           : 1;
__REG32                 :23;
} __operationalmodeenable_bits;

/* USB Control Register (USB_CTL) */
typedef struct {
__REG32 USB_EN          : 1;
__REG32 USB_RST         : 1;
__REG32 SUSP            : 1;
__REG32 RWU_EN          : 1;
__REG32 SUS_TST         : 1;
__REG32 SIE_RCV         : 1;
__REG32 VCMD            : 1;
__REG32 CCMD            : 1;
__REG32 WAKEUP          : 1;
__REG32                 :23;
} __usb_ctl_bits;

/* USB Class or Vendor command Register (USB_CVCMD) */
typedef struct {
__REG32 CVI_LG          : 5;
__REG32                 :27;
} __usb_cvcmd_bits;

/* USB Interrupt Enable Register (USB_IE) */
typedef struct {
__REG32 RSTI            : 1;
__REG32 SUSI            : 1;
__REG32 RUMI            : 1;
__REG32 ERRI            : 1;
__REG32 GDEVI           : 1;
__REG32 GCFGI           : 1;
__REG32 GSTRI           : 1;
__REG32 CLAI            : 1;
__REG32 VENI            : 1;
__REG32 CDOI            : 1;
__REG32 CDII            : 1;
__REG32 CVSI            : 1;
__REG32 USB_BTI         : 1;
__REG32 USB_CGI         : 1;
__REG32 RST_ENDI        : 1;
__REG32 RUM_CLKI        : 1;
__REG32                 :16;
} __usb_ie_bits;

/* USB Interrupt status Register (USB_IS) */
typedef struct {
__REG32 RSTS            : 1;
__REG32 SUSS            : 1;
__REG32 RUMS            : 1;
__REG32 ERRS            : 1;
__REG32 GDEVS           : 1;
__REG32 GCFGS           : 1;
__REG32 GSTRS           : 1;
__REG32 CLAS            : 1;
__REG32 VENS            : 1;
__REG32 CDOS            : 1;
__REG32 CDIS            : 1;
__REG32 CVSS            : 1;
__REG32 USB_BTS         : 1;
__REG32 USB_CGS         : 1;
__REG32 RST_ENDS        : 1;
__REG32 RUM_CLKS        : 1;
__REG32                 :16;
} __usb_is_bits;

/* USB Interrupt Status Clear (USB_IC) */
typedef struct {
__REG32 RSTC            : 1;
__REG32 SUSC            : 1;
__REG32 RUMC            : 1;
__REG32 ERRC            : 1;
__REG32 GDEVC           : 1;
__REG32 GCFGC           : 1;
__REG32 GSTRC           : 1;
__REG32 CLAC            : 1;
__REG32 VENC            : 1;
__REG32 CDOC            : 1;
__REG32 CDIC            : 1;
__REG32 CVSC            : 1;
__REG32 USB_BTC         : 1;
__REG32 USB_CGC         : 1;
__REG32 RST_ENDC        : 1;
__REG32 RUM_CLKC        : 1;
__REG32                 :16;
} __usb_ic_bits;

/* USB Interface and String Register (USB_IFSTR) */
typedef struct {
__REG32 INF1_EN         : 1;
__REG32 INF2_EN         : 1;
__REG32 INF3_EN         : 1;
__REG32 INF4_EN         : 1;
__REG32 STR1_EN         : 1;
__REG32 STR2_EN         : 1;
__REG32 STR3_EN         : 1;
__REG32 STR4_EN         : 1;
__REG32 STR5_EN         : 1;
__REG32 STR6_EN         : 1;
__REG32                 :22;
} __usb_ifstr_bits;

/* USB SIE Status Register (USB_SIE) */
typedef struct {
__REG32 USB_DMS         : 1;
__REG32 USB_DPS         : 1;
__REG32                 :30;
} __usb_sie_bits;

/* USB Engine Register (USB_ENG) */
typedef struct {
__REG32 CV_DAT          : 1;
__REG32 CV_STL          : 1;
__REG32 CV_LDA          : 1;
__REG32 SDO_RD          : 1;
__REG32                 :28;
} __usb_eng_bits;

/* USB Control Register (USB_CTLS) */
typedef struct {
__REG32 CTLRPS          : 5;
__REG32                 : 3;
__REG32 CONF            : 8;
__REG32                 :16;
} __usb_ctls_bits;

/* USB Configured Value Register (USB_CONFD) */
typedef struct {
__REG32 CONFD           : 8;
__REG32                 :24;
} __usb_confd_bits;

/* USB Endpoint A Information Register (EPA_INFO) */
typedef struct {
__REG32 EPA_NUM         : 4;
__REG32 EPA_CFG         : 4;
__REG32 EPA_INF         : 4;
__REG32 EPA_ALT         : 4;
__REG32 EPA_MPS         :10;
__REG32                 : 2;
__REG32 EPA_DIR         : 1;
__REG32 EPA_TYPE        : 2;
__REG32                 : 1;
} __epa_info_bits;

/* USB Endpoint A Control Register (EPA_CTL) */
typedef struct {
__REG32 EPA_EN          : 1;
__REG32 EPA_RST         : 1;
__REG32 EPA_RDY         : 1;
__REG32 EPA_STL         : 1;
__REG32 EPA_THRE        : 1;
__REG32 EPA_STL_CLR     : 1;
__REG32 EPA_ZERO        : 1;
__REG32                 :25;
} __epa_ctl_bits;

/* USB Endpoint A interrupt enable Register (EPA_IE) */
typedef struct {
__REG32 EPA_STL_IE      : 1;
__REG32 EPA_TK_IE       : 1;
__REG32 EPA_ALT_IE      : 1;
__REG32 EPA_DMA_IE      : 1;
__REG32 EPA_BUS_ERR_IE  : 1;
__REG32 EPA_CF_IE       : 1;
__REG32                 :26;
} __epa_ie_bits;

/* USB Endpoint A Interrupt Clear Register (EPA_IC) */
typedef struct {
__REG32 EPA_STL_IC      : 1;
__REG32 EPA_TK_IC       : 1;
__REG32 EPA_ALT_IC      : 1;
__REG32 EPA_DMA_IC      : 1;
__REG32 EPA_BUS_ERR_IC  : 1;
__REG32 EPA_CF_IC       : 1;
__REG32                 :26;
} __epa_ic_bits;

/* USB Endpoint A Interrupt Status Register (EPA_IS) */
typedef struct {
__REG32 EPA_STL_IS      : 1;
__REG32 EPA_TK_IS       : 1;
__REG32 EPA_ALT_IS      : 1;
__REG32 EPA_DMA_IS      : 1;
__REG32 EPA_BUS_ERR_IS  : 1;
__REG32 EPA_CF_IS       : 1;
__REG32                 :26;
} __epa_is_bits;

/* USB Endpoint A transfer length Register (EPA_LENTH) */
typedef struct {
__REG32 EPA_LENTH       :20;
__REG32                 :12;
} __epa_lenth_bits;

/* USB Endpoint B Information Register (EPB_INFO) */
typedef struct {
__REG32 EPB_NUM         : 4;
__REG32 EPB_CFG         : 4;
__REG32 EPB_INF         : 4;
__REG32 EPB_ALT         : 4;
__REG32 EPB_MPS         :10;
__REG32                 : 2;
__REG32 EPB_DIR         : 1;
__REG32 EPB_TYPE        : 2;
__REG32                 : 1;
} __epb_info_bits;

/* USB Endpoint B Control Register (EPB_CTL) */
typedef struct {
__REG32 EPB_EN          : 1;
__REG32 EPB_RST         : 1;
__REG32 EPB_RDY         : 1;
__REG32 EPB_STL         : 1;
__REG32 EPB_THRE        : 1;
__REG32 EPB_STL_CLR     : 1;
__REG32 EPB_ZERO        : 1;
__REG32                 :25;
} __epb_ctl_bits;

/* USB Endpoint B interrupt enable Register (EPB_IE) */
typedef struct {
__REG32 EPB_STL_IE      : 1;
__REG32 EPB_TK_IE       : 1;
__REG32 EPB_ALT_IE      : 1;
__REG32 EPB_DMA_IE      : 1;
__REG32 EPB_BUS_ERR_IE  : 1;
__REG32 EPB_CF_IE       : 1;
__REG32                 :26;
} __epb_ie_bits;

/* USB Endpoint B Interrupt Clear Register (EPB_IC) */
typedef struct {
  __REG32 EPB_STL_IC        : 1;
  __REG32 EPB_TK_IC         : 1;
  __REG32 EPB_ALT_IC        : 1;
  __REG32 EPB_DMA_IC        : 1;
  __REG32 EPB_BUS_ERR_IC    : 1;
  __REG32 EPB_CF_IC         : 1;
  __REG32                   :26;
} __epb_ic_bits;

/* USB Endpoint B Interrupt Status Register (EPB_IS) */
typedef struct {
  __REG32 EPB_STL_IS        : 1;
  __REG32 EPB_TK_IS         : 1;
  __REG32 EPB_ALT_IS        : 1;
  __REG32 EPB_DMA_IS        : 1;
  __REG32 EPB_BUS_ERR_IS    : 1;
  __REG32 EPB_CF_IS         : 1;
  __REG32                   :26;
} __epb_is_bits;

/* USB Endpoint B transfer length Register (EPB_LENTH) */
typedef struct {
  __REG32 EPB_LENTH         :20;
  __REG32                   :12;
} __epb_lenth_bits;

/* USB Endpoint C Information Register (EPC_INFO) */
typedef struct {
  __REG32 EPC_NUM           : 4;
  __REG32 EPC_CFG           : 4;
  __REG32 EPC_INF           : 4;
  __REG32 EPC_ALT           : 4;
  __REG32 EPC_MPS           :10;
  __REG32                   : 2;
  __REG32 EPC_DIR           : 1;
  __REG32 EPC_TYPE          : 2;
  __REG32                   : 1;
} __epc_info_bits;

/* USB Endpoint C Control Register (EPC_CTL) */
typedef struct {
  __REG32 EPC_EN            : 1;
  __REG32 EPC_RST           : 1;
  __REG32 EPC_RDY           : 1;
  __REG32 EPC_STL           : 1;
  __REG32 EPC_THRE          : 1;
  __REG32 EPC_STL_CLR       : 1;
  __REG32 EPC_ZERO          : 1;
  __REG32                   :25;
} __epc_ctl_bits;

/* USB Endpoint C interrupt enable Register (EPC_IE) */
typedef struct {
  __REG32 EPC_STL_IE        : 1;
  __REG32 EPC_TK_IE         : 1;
  __REG32 EPC_ALT_IE        : 1;
  __REG32 EPC_DMA_IE        : 1;
  __REG32 EPC_BUS_ERR_IE    : 1;
  __REG32 EPC_CF_IE         : 1;
  __REG32                   :26;
} __epc_ie_bits;

/* USB Endpoint C Interrupt Clear Register (EPC_IC) */
typedef struct {
  __REG32 EPC_STL_IC        : 1;
  __REG32 EPC_TK_IC         : 1;
  __REG32 EPC_ALT_IC        : 1;
  __REG32 EPC_DMA_IC        : 1;
  __REG32 EPC_BUS_ERR_IC    : 1;
  __REG32 EPC_CF_IC         : 1;
  __REG32                   :26;
} __epc_ic_bits;

/* USB Endpoint C Interrupt Status Register (EPC_IS) */
typedef struct {
  __REG32 EPC_STL_IS        : 1;
  __REG32 EPC_TK_IS         : 1;
  __REG32 EPC_ALT_IS        : 1;
  __REG32 EPC_DMA_IS        : 1;
  __REG32 EPC_BUS_ERR_IS    : 1;
  __REG32 EPC_CF_IS         : 1;
  __REG32                   :26;
} __epc_is_bits;

/* USB Endpoint C transfer length Register (EPC_LENTH) */
typedef struct {
  __REG32 EPC_LENTH         :20;
  __REG32                   :12;
} __epc_lenth_bits;

/* USB Endpoint A Remain transfer length Register (EPA_XFER) */
typedef struct {
  __REG32 EPA_XFER          :20;
  __REG32                   :12;
} __epa_xfer_bits;

/* USB Endpoint A Remain packet length Register (EPA_PKT) */
typedef struct {
  __REG32 EPA_PKT           :10;
  __REG32                   :22;
} __epa_pkt_bits;

/* USB Endpoint B Remain transfer length Register (EPB_XFER) */
typedef struct {
  __REG32 EPB_XFER          :20;
  __REG32                   :12;
} __epb_xfer_bits;

/* USB Endpoint B Remain packet length Register (EPB_PKT) */
typedef struct {
  __REG32 EPB_PKT           :10;
  __REG32                   :22;
} __epb_pkt_bits;

/* USB Endpoint C Remain transfer length Register (EPC_XFER) */
typedef struct {
  __REG32 EPC_XFER          :20;
  __REG32                   :12;
} __epc_xfer_bits;

/* USB Endpoint C Remain packet length Register (EPC_PKT) */
typedef struct {
  __REG32 EPC_PKT           :10;
  __REG32                   :22;
} __epc_pkt_bits;

/* SD Gloal Control Register (SDGCR) */
typedef struct {
  __REG32 SDEN              : 1;
  __REG32 SWRST             : 1;
  __REG32 DMAWR             : 1;
  __REG32 DMARD             : 1;
  __REG32 WRSEL             : 3;
  __REG32                   : 1;
  __REG32 RDSEL             : 3;
  __REG32                   :21;
} __sdgcr_bits;

/* SD DMA Byte Count Register (SDBCR) */
typedef struct {
  __REG32 BCNT              :12;
  __REG32                   :20;
} __sdbcr_bits;

/* SD Global Interrupt Enable Register (SDGIER) */
typedef struct {
  __REG32 SDGIEN            : 1;
  __REG32                   : 2;
  __REG32 SDHIIEN           : 1;
  __REG32 DWRIEN            : 1;
  __REG32 DRDIEN            : 1;
  __REG32 ERRIEN            : 1;
  __REG32                   :25;
} __sdgier_bits;

/* SD global Interrupt Status Register (SDGISR) */
typedef struct {
  __REG32 SDGINT            : 1;
  __REG32                   : 2;
  __REG32 SDHIINT           : 1;
  __REG32 DWRINT            : 1;
  __REG32 DRDINT            : 1;
  __REG32 ERRINT            : 1;
  __REG32                   :25;
} __sdgisr_bits;

/* SDIO BIST Register (SDBIST) */
typedef struct {
  __REG32 BISTEN            : 1;
  __REG32 FINISH            : 1;
  __REG32 BISTFAIL          : 2;
  __REG32                   :28;
} __sdbist_bits;

/* SD Interface Control Register (SDICR) */
typedef struct {
  __REG32 CO_EN             : 1;
  __REG32 RI_EN             : 1;
  __REG32 DI_EN             : 1;
  __REG32 DO_EN             : 1;
  __REG32 R2_EN             : 1;
  __REG32 _74CLK_OE         : 1;
  __REG32 _8CLK_OE          : 1;
  __REG32 CLK_KEEP          : 1;
  __REG32 CMD_CODE          : 6;
  __REG32                   : 1;
  __REG32 SD_CS             : 1;
  __REG32                   :16;
} __sdicr_bits;

/* SD Host interface Initial Register (SDHIIR) */
typedef struct {
  __REG32 SD_CLK            : 8;
  __REG32 SPD               : 1;
  __REG32                   :23;
} __sdhiir_bits;

/* SD Interface Interrupt Enable Register (SDIIER) */
typedef struct {
  __REG32 DI_IEN            : 1;
  __REG32 DO_IEN            : 1;
  __REG32 CD_IEN            : 1;
  __REG32 DAT0_IEN          : 1;
  __REG32 SD_IEN            : 1;
  __REG32                   :27;
} __sdiier_bits;

/* SD Interface Interrupt Status Register (SDIISR) */
typedef struct {
  __REG32 DI_IS             : 1;
  __REG32 DO_IS             : 1;
  __REG32 CD_IS             : 1;
  __REG32 CRC_7             : 1;
  __REG32 CRC_16            : 1;
  __REG32 CRC               : 1;
  __REG32 R2_CRC7           : 1;
  __REG32 CD_               : 1;
  __REG32 DAT0_STS          : 1;
  __REG32 SD_DATA0          : 1;
  __REG32 DAT1_IS_          : 1;
  __REG32                   :21;
} __sdiisr_bits;

/* SD Block Length Register (SDBLEN) */
typedef struct {
  __REG32 SDBLEN            : 9;
  __REG32                   :23;
} __sdblen_bits;

/* LCD Control Register (LCDCON) */
typedef struct {
  __REG32 VDBPP             : 3;
  __REG32 VDLUTEN           : 1;
  __REG32 OSDBPP            : 3;
  __REG32 OSDLUTEN          : 1;
  __REG32 LCDBUS            : 2;
  __REG32 RGBSEQ            : 2;
  __REG32 YUVSEQ            : 2;
  __REG32                   : 2;
  __REG32 LCDTFT            : 1;
  __REG32 TFTTYPE           : 1;
  __REG32 PIXELSEQ          : 2;
  __REG32 TVEN              : 1;
  __REG32 YUV_NRGB          : 1;
  __REG32 LCDBW             : 1;
  __REG32 LCDMON8           : 1;
  __REG32 LCDCEN            : 1;
  __REG32 OSDEN             : 1;
  __REG32 LUTWREN           : 1;
  __REG32                   : 1;
  __REG32 LCDRST            : 1;
  __REG32 PPRST             : 1;
  __REG32                   : 2;
} __lcdcon_bits;

/* LCD Interrupt Enable Register (LCDINTENB) */
typedef struct {
  __REG32 VFFINEN1          : 1;
  __REG32 VLFINEN1          : 1;
  __REG32 VFFINEN2          : 1;
  __REG32 VLFINEN2          : 1;
  __REG32 VSEN              : 1;
  __REG32 HSEN              : 1;
  __REG32                   :10;
  __REG32 AHBEREN           : 1;
  __REG32 UNDREN1           : 1;
  __REG32 UNDREN2           : 1;
  __REG32                   :13;
} __lcdintenb_bits;

/* LCD Interrupt Status Register (LCDINTS) */
typedef struct {
  __REG32 VFFINIS1          : 1;
  __REG32 VLFINIS1          : 1;
  __REG32 VFFINIS2          : 1;
  __REG32 VLFINIS2          : 1;
  __REG32 VSIS              : 1;
  __REG32 HSIS              : 1;
  __REG32                   :10;
  __REG32 AHBERIS           : 1;
  __REG32 UNDRIS1           : 1;
  __REG32 UNDRIS2           : 1;
  __REG32                   :13;
} __lcdints_bits;

/* LCD Interrupt Clear Register (LCDINTC) */
typedef struct {
  __REG32 VFFINIC1          : 1;
  __REG32 VLFINIC1          : 1;
  __REG32 VFFINIC2          : 1;
  __REG32 VLFINIC2          : 1;
  __REG32 VSIC              : 1;
  __REG32 HSIC              : 1;
  __REG32                   :10;
  __REG32 AHBERIC           : 1;
  __REG32 UNDRIC1           : 1;
  __REG32 UNDRIC2           : 1;
  __REG32                   :13;
} __lcdintc_bits;

/* OSD Up-Scaling Factor Register (OSDUPSCF) */
typedef struct {
  __REG32                   : 1;
  __REG32 OSDVUP            : 2;
  __REG32 OSDHUP            : 2;
  __REG32                   :27;
} __osdupscf_bits;

/* Video Up-Scaling Factor Register (VDUPSCF) */
typedef struct {
  __REG32                   : 1;
  __REG32 VDVUP             : 2;
  __REG32 VDHUP             : 2;
  __REG32                   :27;
} __vdupscf_bits;

/* OSD Down-Scaling Factor Register (OSDDNSCF) */
typedef struct {
  __REG32 OSDHDNM           : 8;
  __REG32 OSDHDNN           : 8;
  __REG32 OSDVDNM           : 8;
  __REG32 OSDVDNN           : 8;
} __osddnscf_bits;

/* Video Down-Scaling Factor Register (VDDNSCF) */
typedef struct {
  __REG32 VDHDNM            : 8;
  __REG32 VDHDNN            : 8;
  __REG32 VDVDNM            : 8;
  __REG32 VDVDNN            : 8;
} __vddnscf_bits;

/* FIFO Control Register (FIFOCON) */
typedef struct {
  __REG32 FIFOEN            : 2;
  __REG32                   :14;
  __REG32 VDBSWP            : 1;
  __REG32 VDHSWP            : 1;
  __REG32 VDBPP18SW         : 1;
  __REG32 VDBPP24SW         : 1;
  __REG32                   : 4;
  __REG32 OSDBSWP           : 1;
  __REG32 OSDHSWP           : 1;
  __REG32 OSDBPP18SW        : 1;
  __REG32 OSDBPP24SW        : 1;
  __REG32                   : 4;
} __fifocon_bits;

/* FIFO Status Register (FIFOSTATUS) */
typedef struct {
  __REG32 MASTERID          : 2;
  __REG32                   :30;
} __fifostatus_bits;

/* FIFO1 Parameter Register (FIFOnPRM) */
typedef struct {
  __REG32 FTRANSZ           : 2;
  __REG32 FBURSTY           : 2;
  __REG32 FLOCK             : 1;
  __REG32                   :11;
  __REG32 FSTRIDE           :16;
} __fifoprm_bits;

/* FIFOx Request Count Register (FIFOxDREQCNT) */
typedef struct {
  __REG32 FIFOROWCNT       :16;
  __REG32 FIFOCOLCNT       :16;
} __fifodreqcnt_bits;

/* Dithering Pattern 1 Register (DITHP1) */
typedef struct {
  __REG32 DP1               :16;
  __REG32 DP2               :16;
} __dithp1_bits;

/* Dithering Pattern 2 Register (DITHP2) */
typedef struct {
  __REG32 DP3               :16;
  __REG32 DP4               :16;
} __dithp2_bits;

/* Dithering Pattern 3 Register (DITHP3) */
typedef struct {
  __REG32 DP5               :16;
  __REG32 DP6               :16;
} __dithp3_bits;

/* Dithering Pattern 4 Register (DITHP4) */
typedef struct {
  __REG32 DP7               :16;
  __REG32 DP8               :16;
} __dithp4_bits;

/* Dithering Pattern 5 Register (DITHP5) */
typedef struct {
  __REG32 DP9               :16;
  __REG32 DP10              :16;
} __dithp5_bits;

/* Dithering Pattern 6 Register (DITHP6) */
typedef struct {
  __REG32 DP11              :16;
  __REG32 DP12              :16;
} __dithp6_bits;

/* Dithering Pattern 7 Register (DITHP7) */
typedef struct {
  __REG32 DP13              :16;
  __REG32 DP14              :16;
} __dithp7_bits;

/* Dummy Display Color Pattern Register (DDISPCP) */
typedef struct {
  __REG32 DDISPB            : 8;
  __REG32 DDISPG            : 8;
  __REG32 DDISPR            : 8;
  __REG32 GRAY              : 7;
  __REG32                   : 1;
} __ddispcp_bits;

/* Video Windows Starting Coordinate Register (VWINS) */
typedef struct {
  __REG32 VWXS              :16;
  __REG32 VWYS              :16;
} __vwins_bits;

/* Video Windows Ending Coordinate Register (VWINE) */
typedef struct {
  __REG32 VWXE              :16;
  __REG32 VWYE              :16;
} __vwine_bits;

/* OSD Windows Starting Coordinate Register (OSDWINS) */
typedef struct {
  __REG32 OSDWXS            :16;
  __REG32 OSDWYS            :16;
} __osdwins_bits;

/* OSD Windows Ending Coordinate Register (OSDWINE) */
typedef struct {
  __REG32 OSDWXE            :16;
  __REG32 OSDWYE            :16;
} __osdwine_bits;

/* OSD Overlay Control Register (OSDOVCN) */
typedef struct {
  __REG32 OCR0              : 2;
  __REG32 OCR1              : 2;
  __REG32 VASYNW            : 3;
  __REG32                   : 1;
  __REG32 OSDCKY            : 1;
  __REG32 OSDBLI            : 1;
  __REG32                   : 6;
  __REG32 BLICNT            : 8;
  __REG32                   : 8;
} __osdovcn_bits;

/* OSD Overlay Color Key Pattern Register (OSDOVCKP) */
typedef struct {
  __REG32 OSDBKYP           : 8;
  __REG32 OSDGKYP           : 8;
  __REG32 OSDRKYP           : 8;
  __REG32                   : 8;
} __osdovckp_bits;
  
/* OSD Overlay Color Key Mask Register (OSDOVCKM) */
typedef struct {
  __REG32 OSDBKYM           : 8;
  __REG32 OSDGKYM           : 8;
  __REG32 OSDRKYM           : 8;
  __REG32                   : 8;
} __osdovckm_bits;

/* LCD Timing Control 1 Register (LCDTCON1) */
typedef struct {
  __REG32 HFPD              :10;
  __REG32 HBPD              :10;
  __REG32 HSPW              :10;
  __REG32                   : 2;
} __lcdtcon1_bits;

/* LCD Timing Control 2 Register (LCDTCON2) */
typedef struct {
  __REG32 LPP               :16;
  __REG32 PPL               :16;
} __lcdtcon2_bits;

/* LCD Timing Control 3 Register (LCDTCON3) */
typedef struct {
  __REG32 VFPD              :10;
  __REG32 VBPD              :10;
  __REG32 VSPW              :10;
  __REG32                   : 2;
} __lcdtcon3_bits;

/* LCD Timing Control 4 Register (LCDTCON4) */
typedef struct {
  __REG32 CLKSEL            : 1;
  __REG32 LCDPRESC          : 7;
  __REG32 PLLRDY            : 1;
  __REG32                   : 8;
  __REG32 PCD               :10;
  __REG32                   : 5;
} __lcdtcon4_bits;

/* LCD Timing Control 5 Register (LCDTCON5) */
typedef struct {
  __REG32 INVVDEN           : 1;
  __REG32 INVVSYN           : 1;
  __REG32 INVHSYN           : 1;
  __REG32 INVVCLK           : 1;
  __REG32 MMODE             : 1;
  __REG32                   :11;
  __REG32 ACBF              : 5;
  __REG32                   :11;
} __lcdtcon5_bits;

/* LCD Timing Control 6 Register (LCDTCON6) */
typedef struct {
  __REG32 LPPCURENT         :16;
  __REG32 PPLCURENT         :16;
} __lcdtcon6_bits;

/* Lookup Table SRAM Build In Self Test Register (BIST) */
typedef struct {
  __REG32 BISTEN            : 1;
  __REG32 FINISH            : 1;
  __REG32 FAIL              : 1;
  __REG32                   :29;
} __bist_bits;

/* Audio controller control registers (ACTL_CON) */
typedef struct {
  __REG32                   : 1;
  __REG32 BLOCK_EN0         : 1;
  __REG32 BLOCK_EN1         : 1;
  __REG32                   : 4;
  __REG32 FIFO_TH           : 1;
  __REG32 I2S_AC_PIN_SEL    : 1;
  __REG32                   : 2;
  __REG32 T_DMA_IRQ         : 1;
  __REG32 R_DMA_IRQ         : 1;
  __REG32                   :19;
} __actl_con_bits;

/* Sub-block reset control register (ACTL_RESET) */
typedef struct {
  __REG32 I2S_RESET         : 1;
  __REG32 AC_RESET          : 1;
  __REG32                   : 3;
  __REG32 I2S_PLAY          : 1;
  __REG32 I2S_RECORD        : 1;
  __REG32 AC_PLAY           : 1;
  __REG32 AC_RECORD         : 1;
  __REG32                   : 3;
  __REG32 PLAY_SINGLE       : 2;
  __REG32 RECORD_SINGLE     : 2;
  __REG32 ACTL_RESET        : 1;
  __REG32                   :15;
} __actl_reset_bits;

/* Audio controller record status register (ACTL_RSR) */
typedef struct {
  __REG32 R_DMA_MIDDLE_IRQ  : 1;
  __REG32 R_DMA_END_IRQ     : 1;
  __REG32 R_FIFO_FULL       : 1;
  __REG32                   :29;
} __actl_rsr_bits;

/* Audio controller playback status register (ACTL_PSR) */
typedef struct {
  __REG32 P_DMA_MIDDLE_IRQ  : 1;
  __REG32 P_DMA_END_IRQ     : 1;
  __REG32 P_FIFO_EMPTY      : 1;
  __REG32                   :29;
} __actl_psr_bits;

/* I2S control register (ACTL_I2SCON) */
typedef struct {
  __REG32                   : 3;
  __REG32 FORMAT            : 1;
  __REG32 MCLK_SEL          : 1;
  __REG32 FS_SEL            : 1;
  __REG32 BCLK_SEL          : 2;
  __REG32                   : 8;
  __REG32 PRS               : 4;
  __REG32                   :12;
} __actl_i2scon_bits;

/* AC-link Control Register (ACTL_ACCON) */
typedef struct {
  __REG32                   : 1;
  __REG32 AC_C_RES          : 1;
  __REG32 AC_W_RES          : 1;
  __REG32 AC_W_FINISH       : 1;
  __REG32 AC_R_FINISH       : 1;
  __REG32 AC_BCLK_PU_EN     : 1;
  __REG32                   :26;
} __actl_accon_bits;

/* AC-link output slot 0 (ACTL_ACOS0) */
typedef struct {
  __REG32 SLOT_VALID        : 4;
  __REG32 VALID_FRAME       : 1;
  __REG32                   :27;
} __actl_acos0_bits;

/* AC-link output slot 1 (ACTL_ACOS1) */
typedef struct {
  __REG32 R_INDEX           : 7;
  __REG32 R_WB              : 1;
  __REG32                   :24;
} __actl_acos1_bits;

/* AC-link output slot 2 (ACTL_ACOS2) */
typedef struct {
  __REG32 WD                :16;
  __REG32                   :16;
} __actl_acos2_bits;

/* AC-link input slot 0 (ACTL_ACIS0) */
typedef struct {
  __REG32 SLOT_VALID        : 4;
  __REG32 CODEC_READY       : 1;
  __REG32                   :27;
} __actl_acis0_bits;

/* AC-link input slot 1 (ACTL_ACIS1) */
typedef struct {
  __REG32 SLOT_REQ          : 2;
  __REG32 R_INDEX           : 7;
  __REG32                   :23;
} __actl_acis1_bits;

/* AC-link input slot 2 (ACTL_ACIS2) */
typedef struct {
  __REG32 RD                :16;
  __REG32                   :16;
} __actl_acis2_bits;

/* UART1 Bluetooth Control Register (UART1_UBCR) */
typedef struct {
  __REG32 UBCR              : 3;
  __REG32                   :29;
} __uart_ubcr_bits;

/* UART2 IrDA Control Register (UART2_IRCR) */
typedef struct {
  __REG32 IRDA_EN           : 1;
  __REG32 TX_SELECT         : 1;
  __REG32 LB                : 1;
  __REG32                   : 2;
  __REG32 INV_TX            : 1;
  __REG32 INV_RX            : 1;
  __REG32                   :25;
} __uart_ircr_bits;
/* UART Interrupt Enable Register (UARTx_IER)
   UART Divisor Latch (High Byte) Register (UARTx_DLM) */
typedef union {
  //UARTx_IER
  struct {
  __REG32 RDAIE             : 1;
  __REG32 THREIE            : 1;
  __REG32 RLSIE             : 1;
  __REG32 MSIE              : 1;
  __REG32 NDBGACK_EN        : 1;
  __REG32                   :27;
  };
  // UARTx_DLM
  struct {
  __REG32 BRD_HI            : 8;
  __REG32                   :24;
  };
} __uart_ier_bits;

/* UART Interrupt Identification Register (UARTx_IIR)
   UART FIFO Control Register (UARTx_FCR) */
typedef union {
  //UARTx_IIR
  struct {
  __REG32 NIP               : 1;
  __REG32 IID               : 3;
  __REG32 DMS               : 1;
  __REG32 RFTLS             : 2;
  __REG32 FMES              : 1;
  __REG32                   :24;
  };
// UARTx_FCR
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
  __REG32                   : 3;
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
  __REG32                   : 1;
  __REG32 DDSR              : 1;
  __REG32                   : 3;
  __REG32 DSR               : 1;
  __REG32                   :26;
} __uart_msr_bits;

/* UART Time Out Register (UART_TOR) */
typedef struct {
  __REG32 TOIC              : 7;
  __REG32 TOIE              : 1;
  __REG32                   :24;
} __uart_tor_bits;

/* HSUART Interrupt Identification Register (HSUARTx_IIR)
   HSUART FIFO Control Register (HSUARTx_FCR) */
typedef union {
  //UARTx_IIR
  struct {
  __REG32 NIP               : 1;
  __REG32 IID               : 3;
  __REG32 DMS               : 1;
  __REG32 RFTLS             : 2;
  __REG32 FMES              : 1;
  __REG32                   :24;
  };
  //UARTx_FCR
  struct {
  __REG32 FME               : 1;
  __REG32 RFR               : 1;
  __REG32 TFR               : 1;
  __REG32 MS                : 1;
  __REG32 RFITL             : 4;
  __REG32                   :24;
  };
} __uart1_iir_bits;

/* HSUART Modem Control Register (HSUART_MCR) */
typedef struct {
  __REG32                   : 1;
  __REG32 RTS               : 1;
  __REG32                   : 2;
  __REG32 LBME              : 1;
  __REG32                   :27;
} __uart1_mcr_bits;

/* HSUART Modem Status Register (HSUART_MSR) */
typedef struct {
  __REG32 DCTS              : 1;
  __REG32                   : 3;
  __REG32 CTS               : 1;
  __REG32                   :27;
} __uart1_msr_bits;

/* Timer Control Register 0/1 (TCSR 0/1) */
typedef struct {
  __REG32 PRESCALE          : 8;
  __REG32                   :17;
  __REG32 CACT              : 1;
  __REG32 CRST              : 1;
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
  __REG32 WTTME             : 1;
  __REG32 NDBGACK_EN        : 1;
  __REG32 WTCLK             : 1;
  __REG32                   :21;
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
  __REG32 IRS19             : 1;
  __REG32 IRS20             : 1;
  __REG32 IRS21             : 1;
  __REG32 IRS22             : 1;
  __REG32 IRS23             : 1;
  __REG32 IRS24             : 1;
  __REG32 IRS25             : 1;
  __REG32 IRS26             : 1;
  __REG32 IRS27             : 1;
  __REG32 IRS28             : 1;
  __REG32 IRS29             : 1;
  __REG32 IRS30             : 1;
  __REG32 IRS31             : 1;
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
  __REG32 IAS19             : 1;
  __REG32 IAS20             : 1;
  __REG32 IAS21             : 1;
  __REG32 IAS22             : 1;
  __REG32 IAS23             : 1;
  __REG32 IAS24             : 1;
  __REG32 IAS25             : 1;
  __REG32 IAS26             : 1;
  __REG32 IAS27             : 1;
  __REG32 IAS28             : 1;
  __REG32 IAS29             : 1;
  __REG32 IAS30             : 1;
  __REG32 IAS31             : 1;
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
  __REG32 IS19              : 1;
  __REG32 IS20              : 1;
  __REG32 IS21              : 1;
  __REG32 IS22              : 1;
  __REG32 IS23              : 1;
  __REG32 IS24              : 1;
  __REG32 IS25              : 1;
  __REG32 IS26              : 1;
  __REG32 IS27              : 1;
  __REG32 IS28              : 1;
  __REG32 IS29              : 1;
  __REG32 IS30              : 1;
  __REG32 IS31              : 1;
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
  __REG32 IM19              : 1;
  __REG32 IM20              : 1;
  __REG32 IM21              : 1;
  __REG32 IM22              : 1;
  __REG32 IM23              : 1;
  __REG32 IM24              : 1;
  __REG32 IM25              : 1;
  __REG32 IM26              : 1;
  __REG32 IM27              : 1;
  __REG32 IM28              : 1;
  __REG32 IM29              : 1;
  __REG32 IM30              : 1;
  __REG32 IM31              : 1;
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
  __REG32 MEC19             : 1;
  __REG32 MEC20             : 1;
  __REG32 MEC21             : 1;
  __REG32 MEC22             : 1;
  __REG32 MEC23             : 1;
  __REG32 MEC24             : 1;
  __REG32 MEC25             : 1;
  __REG32 MEC26             : 1;
  __REG32 MEC27             : 1;
  __REG32 MEC28             : 1;
  __REG32 MEC29             : 1;
  __REG32 MEC30             : 1;
  __REG32 MEC31             : 1;
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
  __REG32 MDC19             : 1;
  __REG32 MDC20             : 1;
  __REG32 MDC21             : 1;
  __REG32 MDC22             : 1;
  __REG32 MDC23             : 1;
  __REG32 MDC24             : 1;
  __REG32 MDC25             : 1;
  __REG32 MDC26             : 1;
  __REG32 MDC27             : 1;
  __REG32 MDC28             : 1;
  __REG32 MDC29             : 1;
  __REG32 MDC30             : 1;
  __REG32 MDC31             : 1;
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
  __REG32 SSC19             : 1;
  __REG32 SSC20             : 1;
  __REG32 SSC21             : 1;
  __REG32 SSC22             : 1;
  __REG32 SSC23             : 1;
  __REG32 SSC24             : 1;
  __REG32 SSC25             : 1;
  __REG32 SSC26             : 1;
  __REG32 SSC27             : 1;
  __REG32 SSC28             : 1;
  __REG32 SSC29             : 1;
  __REG32 SSC30             : 1;
  __REG32 SSC31             : 1;
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
  __REG32 SCC19             : 1;
  __REG32 SCC20             : 1;
  __REG32 SCC21             : 1;
  __REG32 SCC22             : 1;
  __REG32 SCC23             : 1;
  __REG32 SCC24             : 1;
  __REG32 SCC25             : 1;
  __REG32 SCC26             : 1;
  __REG32 SCC27             : 1;
  __REG32 SCC28             : 1;
  __REG32 SCC29             : 1;
  __REG32 SCC30             : 1;
  __REG32 SCC31             : 1;
} __aic_sccr_bits;

/* AIC ICE/Debug Register (AIC_TEST) */
typedef struct {
  __REG32 TEST              : 1;
  __REG32                   :31;
} __aic_test_bits;

/* GPIO Port0 Configuration Register (GPIO_CFG0) */
typedef struct {
  __REG32 PT0CFG0           : 2;
  __REG32 PT0CFG1           : 2;
  __REG32 PT0CFG2           : 2;
  __REG32 PT0CFG3           : 2;
  __REG32 PT0CFG4           : 2;
  __REG32                   :22;
} __gpio_cfg0_bits;

/* GPIO Port0 Direction Register (GPIO_DIR0) */
typedef struct {
  __REG32 OMDEN0            : 1;
  __REG32 OMDEN1            : 1;
  __REG32 OMDEN2            : 1;
  __REG32 OMDEN3            : 1;
  __REG32 OMDEN4            : 1;
  __REG32                   :11;
  __REG32 PUPEN0            : 1;
  __REG32 PUPEN1            : 1;
  __REG32 PUPEN2            : 1;
  __REG32 PUPEN3            : 1;
  __REG32                   :12;
} __gpio_dir0_bits;

/* GPIO Port0 Data Output Register (GPIO_DATAOUT0) */
typedef struct {
  __REG32 DATAOUT0          : 1;
  __REG32 DATAOUT1          : 1;
  __REG32 DATAOUT2          : 1;
  __REG32 DATAOUT3          : 1;
  __REG32 DATAOUT4          : 1;
  __REG32                   :27;
} __gpio_dataout0_bits;

/* GPIO Port0 Data Input Register (GPIO_DATAIN0) */
typedef struct {
  __REG32 DATAIN0           : 1;
  __REG32 DATAIN1           : 1;
  __REG32 DATAIN2           : 1;
  __REG32 DATAIN3           : 1;
  __REG32 DATAIN4           : 1;
  __REG32                   :27;
} __gpio_datain0_bits;

/* GPIO Port1 Configuration Register (GPIO_CFG1) */
typedef struct {
  __REG32 PT1CFG0           : 2;
  __REG32 PT1CFG1           : 2;
  __REG32 PT1CFG2           : 2;
  __REG32 PT1CFG3           : 2;
  __REG32 PT1CFG4           : 2;
  __REG32 PT1CFG5           : 2;
  __REG32 PT1CFG6           : 2;
  __REG32 PT1CFG7           : 2;
  __REG32 PT1CFG8           : 2;
  __REG32 PT1CFG9           : 2;
  __REG32                   :12;
} __gpio_cfg1_bits;

/* GPIO Port1 Direction Register (GPIO_DIR1) */
typedef struct {
  __REG32 OMDEN0            : 1;
  __REG32 OMDEN1            : 1;
  __REG32 OMDEN2            : 1;
  __REG32 OMDEN3            : 1;
  __REG32 OMDEN4            : 1;
  __REG32 OMDEN5            : 1;
  __REG32 OMDEN6            : 1;
  __REG32 OMDEN7            : 1;
  __REG32 OMDEN8            : 1;
  __REG32 OMDEN9            : 1;
  __REG32                   : 6;
  __REG32 PUPEN0            : 1;
  __REG32 PUPEN1            : 1;
  __REG32 PUPEN2            : 1;
  __REG32 PUPEN3            : 1;
  __REG32 PUPEN4            : 1;
  __REG32 PUPEN5            : 1;
  __REG32 PUPEN6            : 1;
  __REG32 PUPEN7            : 1;
  __REG32 PUPEN8            : 1;
  __REG32 PUPEN9            : 1;
  __REG32                   : 6;
} __gpio_dir1_bits;

/* GPIO Port1 Data Output Register (GPIO_DATAOUT1) */
typedef struct {
  __REG32 DATAOUT0          : 1;
  __REG32 DATAOUT1          : 1;
  __REG32 DATAOUT2          : 1;
  __REG32 DATAOUT3          : 1;
  __REG32 DATAOUT4          : 1;
  __REG32 DATAOUT5          : 1;
  __REG32 DATAOUT6          : 1;
  __REG32 DATAOUT7          : 1;
  __REG32 DATAOUT8          : 1;
  __REG32 DATAOUT9          : 1;
  __REG32                   :22;
} __gpio_dataout1_bits;

/* GPIO Port1 Data Input Register (GPIO_DATAIN1) */
typedef struct {
  __REG32 DATAIN0           : 1;
  __REG32 DATAIN1           : 1;
  __REG32 DATAIN2           : 1;
  __REG32 DATAIN3           : 1;
  __REG32 DATAIN4           : 1;
  __REG32 DATAIN5           : 1;
  __REG32 DATAIN6           : 1;
  __REG32 DATAIN7           : 1;
  __REG32 DATAIN8           : 1;
  __REG32 DATAIN9           : 1;
  __REG32                   :22;
} __gpio_datain1_bits;

/* GPIO Port2 Configuration Register (GPIO_CFG2) */
typedef struct {
  __REG32 PT2CFG0           : 2;
  __REG32 PT2CFG1           : 2;
  __REG32 PT2CFG2           : 2;
  __REG32 PT2CFG3           : 2;
  __REG32 PT2CFG4           : 2;
  __REG32 PT2CFG5           : 2;
  __REG32 PT2CFG6           : 2;
  __REG32 PT2CFG7           : 2;
  __REG32 PT2CFG8           : 2;
  __REG32 PT2CFG9           : 2;
  __REG32                   :12;
} __gpio_cfg2_bits;

/* GPIO Port2 Direction Register (GPIO_DIR2) */
typedef struct {
  __REG32 OMDEN0            : 1;
  __REG32 OMDEN1            : 1;
  __REG32 OMDEN2            : 1;
  __REG32 OMDEN3            : 1;
  __REG32 OMDEN4            : 1;
  __REG32 OMDEN5            : 1;
  __REG32 OMDEN6            : 1;
  __REG32 OMDEN7            : 1;
  __REG32 OMDEN8            : 1;
  __REG32 OMDEN9            : 1;
  __REG32                   : 6;
  __REG32 PUPEN0            : 1;
  __REG32 PUPEN1            : 1;
  __REG32 PUPEN2            : 1;
  __REG32 PUPEN3            : 1;
  __REG32 PUPEN4            : 1;
  __REG32 PUPEN5            : 1;
  __REG32 PUPEN6            : 1;
  __REG32 PUPEN7            : 1;
  __REG32 PUPEN8            : 1;
  __REG32 PUPEN9            : 1;
  __REG32                   : 6;
} __gpio_dir2_bits;

/* GPIO Port2 Data Output Register (GPIO_DATAOUT2) */
typedef struct {
  __REG32 DATAOUT0          : 1;
  __REG32 DATAOUT1          : 1;
  __REG32 DATAOUT2          : 1;
  __REG32 DATAOUT3          : 1;
  __REG32 DATAOUT4          : 1;
  __REG32 DATAOUT5          : 1;
  __REG32 DATAOUT6          : 1;
  __REG32 DATAOUT7          : 1;
  __REG32 DATAOUT8          : 1;
  __REG32 DATAOUT9          : 1;
  __REG32                   :22;
} __gpio_dataout2_bits;

/* GPIO Port2 Data Input Register (GPIO_DATAIN2) */
typedef struct {
  __REG32 DATAIN0           : 1;
  __REG32 DATAIN1           : 1;
  __REG32 DATAIN2           : 1;
  __REG32 DATAIN3           : 1;
  __REG32 DATAIN4           : 1;
  __REG32 DATAIN5           : 1;
  __REG32 DATAIN6           : 1;
  __REG32 DATAIN7           : 1;
  __REG32 DATAIN8           : 1;
  __REG32 DATAIN9           : 1;
  __REG32                   :22;
} __gpio_datain2_bits;

/* GPIO Port3 Configuration Register (GPIO_CFG3) */
typedef struct {
  __REG32 PT3CFG0           : 2;
  __REG32 PT3CFG1           : 2;
  __REG32 PT3CFG2           : 2;
  __REG32 PT3CFG3           : 2;
  __REG32 PT3CFG4           : 2;
  __REG32 PT3CFG5           : 2;
  __REG32 PT3CFG6           : 2;
  __REG32 PT3CFG7           : 2;
  __REG32                   :16;
} __gpio_cfg3_bits;

/* GPIO Port3 Direction Register (GPIO_DIR3) */
typedef struct {
  __REG32 OMDEN0            : 1;
  __REG32 OMDEN1            : 1;
  __REG32 OMDEN2            : 1;
  __REG32 OMDEN3            : 1;
  __REG32 OMDEN4            : 1;
  __REG32 OMDEN5            : 1;
  __REG32 OMDEN6            : 1;
  __REG32 OMDEN7            : 1;
  __REG32                   : 8;
  __REG32 PUPEN0            : 1;
  __REG32 PUPEN1            : 1;
  __REG32 PUPEN2            : 1;
  __REG32 PUPEN3            : 1;
  __REG32 PUPEN4            : 1;
  __REG32 PUPEN5            : 1;
  __REG32 PUPEN6            : 1;
  __REG32 PUPEN7            : 1;
  __REG32                   : 8;
} __gpio_dir3_bits;

/* GPIO Port3 Data Output Register (GPIO_DATAOUT3) */
typedef struct {
  __REG32 DATAOUT0          : 1;
  __REG32 DATAOUT1          : 1;
  __REG32 DATAOUT2          : 1;
  __REG32 DATAOUT3          : 1;
  __REG32 DATAOUT4          : 1;
  __REG32 DATAOUT5          : 1;
  __REG32 DATAOUT6          : 1;
  __REG32 DATAOUT7          : 1;
  __REG32                   :24;
} __gpio_dataout3_bits;

/* GPIO Port3 Data Input Register (GPIO_DATAIN3) */
typedef struct {
  __REG32 DATAIN0           : 1;
  __REG32 DATAIN1           : 1;
  __REG32 DATAIN2           : 1;
  __REG32 DATAIN3           : 1;
  __REG32 DATAIN4           : 1;
  __REG32 DATAIN5           : 1;
  __REG32 DATAIN6           : 1;
  __REG32 DATAIN7           : 1;
  __REG32                   :24;
} __gpio_datain3_bits;

/* GPIO Port4 Configuration Register (GPIO_CFG4) */
typedef struct {
  __REG32 PT4CFG0           : 2;
  __REG32 PT4CFG1           : 2;
  __REG32 PT4CFG2           : 2;
  __REG32 PT4CFG3           : 2;
  __REG32 PT4CFG4           : 2;
  __REG32 PT4CFG5           : 2;
  __REG32 PT4CFG6           : 2;
  __REG32 PT4CFG7           : 2;
  __REG32 PT4CFG8           : 2;
  __REG32 PT4CFG9           : 2;
  __REG32 PT4CFG10          : 2;
  __REG32                   :10;
} __gpio_cfg4_bits;

/* GPIO Port4 Direction Register (GPIO_DIR4) */
typedef struct {
  __REG32 OMDEN0            : 1;
  __REG32 OMDEN1            : 1;
  __REG32 OMDEN2            : 1;
  __REG32 OMDEN3            : 1;
  __REG32 OMDEN4            : 1;
  __REG32 OMDEN5            : 1;
  __REG32 OMDEN6            : 1;
  __REG32 OMDEN7            : 1;
  __REG32 OMDEN8            : 1;
  __REG32 OMDEN9            : 1;
  __REG32 OMDEN10           : 1;
  __REG32                   : 5;
  __REG32 PUPEN0            : 1;
  __REG32 PUPEN1            : 1;
  __REG32 PUPEN2            : 1;
  __REG32 PUPEN3            : 1;
  __REG32 PUPEN4            : 1;
  __REG32 PUPEN5            : 1;
  __REG32 PUPEN6            : 1;
  __REG32 PUPEN7            : 1;
  __REG32 PUPEN8            : 1;
  __REG32 PUPEN9            : 1;
  __REG32 PUPEN10           : 1;
  __REG32                   : 5;
} __gpio_dir4_bits;

/* GPIO Port4 Data Output Register (GPIO_DATAOUT4) */
typedef struct {
  __REG32 DATAOUT0          : 1;
  __REG32 DATAOUT1          : 1;
  __REG32 DATAOUT2          : 1;
  __REG32 DATAOUT3          : 1;
  __REG32 DATAOUT4          : 1;
  __REG32 DATAOUT5          : 1;
  __REG32 DATAOUT6          : 1;
  __REG32 DATAOUT7          : 1;
  __REG32 DATAOUT8          : 1;
  __REG32 DATAOUT9          : 1;
  __REG32 DATAOUT10         : 1;
  __REG32                   :21;
} __gpio_dataout4_bits;

/* GPIO Port4 Data Input Register (GPIO_DATAIN4) */
typedef struct {
  __REG32 DATAIN0           : 1;
  __REG32 DATAIN1           : 1;
  __REG32 DATAIN2           : 1;
  __REG32 DATAIN3           : 1;
  __REG32 DATAIN4           : 1;
  __REG32 DATAIN5           : 1;
  __REG32 DATAIN6           : 1;
  __REG32 DATAIN7           : 1;
  __REG32 DATAIN8           : 1;
  __REG32 DATAIN9           : 1;
  __REG32 DATAIN10          : 1;
  __REG32                   :21;
} __gpio_datain4_bits;

/* GPIO Port5 Configuration Register (GPIO_CFG5) */
typedef struct {
  __REG32 PT5CFG0           : 2;
  __REG32 PT5CFG1           : 2;
  __REG32 PT5CFG2           : 2;
  __REG32 PT5CFG3           : 2;
  __REG32 PT5CFG4           : 2;
  __REG32 PT5CFG5           : 2;
  __REG32 PT5CFG6           : 2;
  __REG32 PT5CFG7           : 2;
  __REG32 PT5CFG8           : 2;
  __REG32 PT5CFG9           : 2;
  __REG32 PT5CFG10          : 2;
  __REG32 PT5CFG11          : 2;
  __REG32 PT5CFG12          : 2;
  __REG32 PT5CFG13          : 2;
  __REG32 PT5CFG14          : 2;
  __REG32                   : 2;
} __gpio_cfg5_bits;

/* GPIO Port5 Direction Register (GPIO_DIR5) */
typedef struct {
  __REG32 OMDEN0            : 1;
  __REG32 OMDEN1            : 1;
  __REG32 OMDEN2            : 1;
  __REG32 OMDEN3            : 1;
  __REG32 OMDEN4            : 1;
  __REG32 OMDEN5            : 1;
  __REG32 OMDEN6            : 1;
  __REG32 OMDEN7            : 1;
  __REG32 OMDEN8            : 1;
  __REG32 OMDEN9            : 1;
  __REG32 OMDEN10           : 1;
  __REG32 OMDEN11           : 1;
  __REG32 OMDEN12           : 1;
  __REG32 OMDEN13           : 1;
  __REG32 OMDEN14           : 1;
  __REG32                   : 1;
  __REG32 PUPEN0            : 1;
  __REG32 PUPEN1            : 1;
  __REG32 PUPEN2            : 1;
  __REG32 PUPEN3            : 1;
  __REG32 PUPEN4            : 1;
  __REG32 PUPEN5            : 1;
  __REG32 PUPEN6            : 1;
  __REG32 PUPEN7            : 1;
  __REG32 PUPEN8            : 1;
  __REG32 PUPEN9            : 1;
  __REG32 PUPEN10           : 1;
  __REG32 PUPEN11           : 1;
  __REG32 PUPEN12           : 1;
  __REG32 PUPEN13           : 1;
  __REG32 PUPEN14           : 1;
  __REG32                   : 1;
} __gpio_dir5_bits;

/* GPIO Port5 Data Output Register (GPIO_DATAOUT5) */
typedef struct {
  __REG32 DATAOUT0          : 1;
  __REG32 DATAOUT1          : 1;
  __REG32 DATAOUT2          : 1;
  __REG32 DATAOUT3          : 1;
  __REG32 DATAOUT4          : 1;
  __REG32 DATAOUT5          : 1;
  __REG32 DATAOUT6          : 1;
  __REG32 DATAOUT7          : 1;
  __REG32 DATAOUT8          : 1;
  __REG32 DATAOUT9          : 1;
  __REG32 DATAOUT10         : 1;
  __REG32 DATAOUT11         : 1;
  __REG32 DATAOUT12         : 1;
  __REG32 DATAOUT13         : 1;
  __REG32 DATAOUT14         : 1;
  __REG32                   :17;
} __gpio_dataout5_bits;

/* GPIO Port5 Data Input Register (GPIO_DATAIN5) */
typedef struct {
  __REG32 DATAIN0           : 1;
  __REG32 DATAIN1           : 1;
  __REG32 DATAIN2           : 1;
  __REG32 DATAIN3           : 1;
  __REG32 DATAIN4           : 1;
  __REG32 DATAIN5           : 1;
  __REG32 DATAIN6           : 1;
  __REG32 DATAIN7           : 1;
  __REG32 DATAIN8           : 1;
  __REG32 DATAIN9           : 1;
  __REG32 DATAIN10          : 1;
  __REG32 DATAIN11          : 1;
  __REG32 DATAIN12          : 1;
  __REG32 DATAIN13          : 1;
  __REG32 DATAIN14          : 1;
  __REG32                   :17;
} __gpio_datain5_bits;

/* GPIO Port6 Configuration Register (GPIO_CFG6) */
typedef struct {
  __REG32 PT6CFG0           : 2;
  __REG32 PT6CFG1           : 2;
  __REG32 PT6CFG2           : 2;
  __REG32 PT6CFG3           : 2;
  __REG32 PT6CFG4           : 2;
  __REG32 PT6CFG5           : 2;
  __REG32 PT6CFG6           : 2;
  __REG32 PT6CFG7           : 2;
  __REG32 PT6CFG8           : 2;
  __REG32 PT6CFG9           : 2;
  __REG32 PT6CFG10          : 2;
  __REG32 PT6CFG11          : 2;
  __REG32                   : 8;
} __gpio_cfg6_bits;

/* GPIO Port6 Direction Register (GPIO_DIR6) */
typedef struct {
  __REG32 OMDEN0            : 1;
  __REG32 OMDEN1            : 1;
  __REG32 OMDEN2            : 1;
  __REG32 OMDEN3            : 1;
  __REG32 OMDEN4            : 1;
  __REG32 OMDEN5            : 1;
  __REG32 OMDEN6            : 1;
  __REG32 OMDEN7            : 1;
  __REG32 OMDEN8            : 1;
  __REG32 OMDEN9            : 1;
  __REG32 OMDEN10           : 1;
  __REG32 OMDEN11           : 1;
  __REG32                   : 4;
  __REG32 PUPEN0            : 1;
  __REG32 PUPEN1            : 1;
  __REG32 PUPEN2            : 1;
  __REG32 PUPEN3            : 1;
  __REG32 PUPEN4            : 1;
  __REG32 PUPEN5            : 1;
  __REG32 PUPEN6            : 1;
  __REG32 PUPEN7            : 1;
  __REG32 PUPEN8            : 1;
  __REG32 PUPEN9            : 1;
  __REG32 PUPEN10           : 1;
  __REG32 PUPEN11           : 1;
  __REG32                   : 4;
} __gpio_dir6_bits;

/* GPIO Port6 Data Output Register (GPIO_DATAOUT6) */
typedef struct {
  __REG32 DATAOUT0          : 1;
  __REG32 DATAOUT1          : 1;
  __REG32 DATAOUT2          : 1;
  __REG32 DATAOUT3          : 1;
  __REG32 DATAOUT4          : 1;
  __REG32 DATAOUT5          : 1;
  __REG32 DATAOUT6          : 1;
  __REG32 DATAOUT7          : 1;
  __REG32 DATAOUT8          : 1;
  __REG32 DATAOUT9          : 1;
  __REG32 DATAOUT10         : 1;
  __REG32 DATAOUT11         : 1;
  __REG32                   :20;
} __gpio_dataout6_bits;

/* GPIO Port6 Data Input Register (GPIO_DATAIN6) */
typedef struct {
  __REG32 DATAIN0           : 1;
  __REG32 DATAIN1           : 1;
  __REG32 DATAIN2           : 1;
  __REG32 DATAIN3           : 1;
  __REG32 DATAIN4           : 1;
  __REG32 DATAIN5           : 1;
  __REG32 DATAIN6           : 1;
  __REG32 DATAIN7           : 1;
  __REG32 DATAIN8           : 1;
  __REG32 DATAIN9           : 1;
  __REG32 DATAIN10          : 1;
  __REG32 DATAIN11          : 1;
  __REG32                   :20;
} __gpio_datain6_bits;

/* GPIO Debounce Control Register (GPIO_DBNCECON) */
typedef struct {
  __REG32 DBEN0             : 1;
  __REG32 DBEN1             : 1;
  __REG32 DBEN2             : 1;
  __REG32 DBEN3             : 1;
  __REG32 DBCLKSEL          : 3;
  __REG32                   :25;
} __gpio_dbncecon_bits;

/* GPIO Interrupt Configuration Register (GPIO_XICFG) */
typedef struct {
  __REG32 ISTYPE4           : 2;
  __REG32 DBE4              : 1;
  __REG32 ENIRQ4            : 1;
  __REG32 ISTYPE5           : 2;
  __REG32 DBE5              : 1;
  __REG32 ENIRQ5            : 1;
  __REG32                   :24;
} __gpio_xicfg_bits;

/* GPIO Interrupt Status Register (GPIO_XISTATUS) */
typedef struct {
  __REG32 NIRQ4             : 1;
  __REG32 NIRQ5             : 1;
  __REG32                   :30;
} __gpio_xistatus_bits;

/* RTC Access Enable Register (RTC_AER) */
typedef struct {
  __REG32 AER               :17;
  __REG32                   :15;
} __rtc_aer_bits;

/* RTC Frequency Compensation Register (RTC_FCR) */
typedef struct {
  __REG32 FCR_FRA           : 6;
  __REG32                   : 2;
  __REG32 FCR_INT           : 4;
  __REG32                   :20;
} __rtc_fcr_bits;

/* RTC Time Loading Register (RTC_TLR) */
typedef struct {
  __REG32 LO_SEC            : 4;
  __REG32 HI_SEC            : 3;
  __REG32                   : 1;
  __REG32 LO_MIN            : 4;
  __REG32 HI_MIN            : 3;
  __REG32                   : 1;
  __REG32 LO_HR             : 4;
  __REG32 HI_HR             : 2;
  __REG32                   :10;
} __rtc_tlr_bits;

/* RTC Calendar Loading Register (RTC_CLR) */
typedef struct {
  __REG32 LO_DAY            : 4;
  __REG32 HI_DAY            : 2;
  __REG32                   : 2;
  __REG32 LO_MON            : 4;
  __REG32 HI_MON            : 1;
  __REG32                   : 3;
  __REG32 LO_YEAR           : 4;
  __REG32 HI_YEAR           : 4;
  __REG32                   : 8;
} __rtc_clr_bits;

/* RTC Time Scale Selection Register (RTC_TSSR) */
typedef struct {
  __REG32 _24HR             : 1;
  __REG32                   :31;
} __rtc_tssr_bits;

/* RTC Day of the Week Register (RTC_DWR) */
typedef struct {
  __REG32 DWR               : 3;
  __REG32                   :29;
} __rtc_dwr_bits;

/* RTC Time Alarm Register (RTC_TAR) */
typedef struct {
  __REG32 LO_SEC_ALARM      : 4;
  __REG32 HI_SEC_ALARM      : 3;
  __REG32                   : 1;
  __REG32 LO_MIN_ALARM      : 4;
  __REG32 HI_MIN_ALARM      : 3;
  __REG32                   : 1;
  __REG32 LO_HR_ALARM       : 4;
  __REG32 HI_HR_ALARM       : 2;
  __REG32                   :10;
} __rtc_tar_bits;

/* RTC Calendar Alarm Register (RTC_CAR) */
typedef struct {
  __REG32 LO_DAY_ALARM      : 4;
  __REG32 HI_DAY_ALARM      : 2;
  __REG32                   : 2;
  __REG32 LO_MON_ALARM      : 4;
  __REG32 HI_MON_ALARM      : 1;
  __REG32                   : 3;
  __REG32 LO_YEAR_ALARM     : 4;
  __REG32 HI_YEAR_ALARM     : 4;
  __REG32                   : 8;
} __rtc_car_bits;

/* RTC Leap year Indication Register (RTC_LIR) */
typedef struct {
  __REG32 LIR               : 1;
  __REG32                   :31;
} __rtc_lir_bits;

/* RTC Interrupt Enable Register (RTC_RIER) */
typedef struct {
  __REG32 ALARM_INT_EN      : 1;
  __REG32 TICK_INT_EN       : 1;
  __REG32                   :30;
} __rtc_rier_bits;

/* RTC Interrupt Indication Register (RTC_RIIR) */
typedef struct {
  __REG32 ALARM_INT_ST      : 1;
  __REG32 TICK_INT_ST       : 1;
  __REG32                   :30;
} __rtc_riir_bits;

/* RTC Tick Time Register (RTC_TTR) */
typedef struct {
  __REG32 TTI               : 3;
  __REG32                   :29;
} __rtc_ttr_bits;

/* Interrupt Enable register (SCHI_IER) */
typedef union {
	//SCHIx_IER
	struct {
  __REG32 ERDRI             : 1;
  __REG32 ETBREI            : 1;
  __REG32 ESCSRI            : 1;
  __REG32 ESCPTI            : 1;
  __REG32                   : 2;
  __REG32 INTERFACE         : 1;
  __REG32 PWRDN             : 1;
  __REG32 ETOR0             : 1;
  __REG32 ETOR1             : 1;
  __REG32 ETOR2             : 1;
  __REG32                   :21;
  };
  //SCHIx_BLH
  struct {
  __REG32 BLH	              : 8;
  __REG32                   :24;
  };
} __schi_ier_bits;

/* Interrupt Status Register (SCHI_ISR) 
   Smart Card FIFO control Register (SCHI_SCFR) */
typedef union {
	//SCHIx_ISR
	struct {
  __REG32 PI           			: 1;
  __REG32 INTS0             : 1;
  __REG32 INTS1             : 1;
  __REG32 INTS2             : 1;
  __REG32 SCPTI             : 1;
  __REG32 SCPSNT	          : 1;
  __REG32                   :26;
  };
	//SCHIx_SCFR
	struct {
  __REG32            				: 1;
  __REG32 RXFRST            : 1;
  __REG32 TXFRST            : 1;
  __REG32 PEC0              : 1;
  __REG32 PEC1              : 1;
  __REG32 PEC2  	          : 1;
  __REG32 RXTL0  	          : 1;
  __REG32 RXTL1  	          : 1;
  __REG32                   :24;
  };
	//SCHIx_ID
	struct {
  __REG32 ID	              : 8;
  __REG32                   :24;
  };
} __schi_isr_bits;

/* Smart Card Control Register (SCHI_SCCR) */
typedef struct {
  __REG32 		              : 2;
  __REG32 CDP		            : 1;
  __REG32 PROT              : 1;
  __REG32 EPE		            : 1;
  __REG32 NSBE              : 1;
  __REG32 DIR			          : 1;
  __REG32 BDLAB             : 1;
  __REG32                   :24;
} __schi_sccr_bits;

/* Smart Card Host Status Register (SCHI_SCSR) */
typedef struct {
  __REG32 RDR               : 1;
  __REG32 OER		            : 1;
  __REG32 PBER              : 1;
  __REG32 NSER	            : 1;
  __REG32 SBD               : 1;
  __REG32 TBRE		          : 1;
  __REG32 TSRE              : 1;
  __REG32 SC_RESET          : 1;
  __REG32 TOF0              : 1;
  __REG32 TOF1              : 1;
  __REG32 TOF2              : 1;
  __REG32                   :21;
} __schi_scsr_bits;

/* Smart Card Host Extended Control Register (SCHI_ECR) */
typedef struct {
  __REG32 		              : 2;
  __REG32 CLKSTPL           : 1;
  __REG32 CLKSTP            : 1;
  __REG32 SCKFS0            : 1;
  __REG32 SCKFS1            : 1;
  __REG32 SCKFS2	          : 1;
  __REG32 	                : 1;
  __REG32 PSCKFS0           : 1;
  __REG32 PSCKFS1           : 1;
  __REG32 PSCKFS2           : 1;
  __REG32                   :21;
} __schi_ecr_bits;

/* Smart Card Host Test Mode Register (SCHI_TMR) */
typedef struct {
  __REG32 POWER_SEQ_SKIP		: 1;
  __REG32 SCRST_L           : 1;
  __REG32                   :30;
} __schi_tmr_bits;

/* Smart Card Host Time-out configuration Register (SCHI_TOC) */
typedef struct {
  __REG32 TOC0              : 1;
  __REG32 TOC1	            : 1;
  __REG32 TOC2              : 1;
  __REG32 NDBGACK_EN0       : 1;
  __REG32 TOC3              : 1;
  __REG32 TOC4		          : 1;
  __REG32 TOC5              : 1;
  __REG32 NDBGACK_EN1       : 1;
  __REG32 TOC6	            : 1;
  __REG32 TOC7	            : 1;
  __REG32 TOC8	            : 1;
  __REG32 NDBGACK_EN2       : 1;
  __REG32                   :20;
} __schi_toc_bits;

/* Smart Card Host Time-out Initial Register 2 (SCHI_TOIR 2) */
typedef struct {
  __REG32 TOIR2             :24;
  __REG32                   : 8;
} __schi_toir2_bits;

/* Smart Card Host Time-Out Data Register 2 (SCHI_TODR2) */
typedef struct {
  __REG32 TDO2              :24;
  __REG32                   : 8;
} __schi_tod2_bits;

/* Smart Card Host Buffer Time-Out Data Register (SCHI_BTOR) */
typedef struct {
  __REG32 BTOIC_0           : 1;
  __REG32 BTOIC_1           : 1;
  __REG32 BTOIC_2           : 1;
  __REG32 BTOIC_3           : 1;
  __REG32 BTOIC_4           : 1;
  __REG32 BTOIC_5           : 1;
  __REG32 BTOIC_6           : 1;
  __REG32 BTOIE             : 1;
  __REG32                   :24;
} __schi_btor_bits;

/* I2C Control and Status Register 0/1 (I2C_CSR0/1) */
typedef struct {
  __REG32 I2C_EN            : 1;
  __REG32 IE                : 1;
  __REG32 IF                : 1;
  __REG32                   : 1;
  __REG32 TX_NUM            : 2;
  __REG32                   : 2;
  __REG32 I2C_TIP           : 1;
  __REG32 I2C_AL            : 1;
  __REG32 I2C_BUSY          : 1;
  __REG32 I2C_RXACK         : 1;
  __REG32                   :20;
} __i2c_csr_bits;

/* I2C Prescale Register 0/1 (I2C_DIVIDER 0 /1) */
typedef struct {
  __REG32 DIVIDER           :16;
  __REG32                   :16;
} __i2c_divider_bits;

/* I2C Command Register 0/1 (I2C_CMDR 0/1) */
typedef struct {
  __REG32 ACK               : 1;
  __REG32 WRITE             : 1;
  __REG32 READ              : 1;
  __REG32 STOP              : 1;
  __REG32 START             : 1;
  __REG32                   :27;
} __i2c_cmdr_bits;

/* I2C Software Mode Register 0/1(I2C_SWR 0/1) */
typedef struct {
  __REG32 SCW               : 1;
  __REG32 SDW               : 1;
  __REG32                   : 1;
  __REG32 SCR               : 1;
  __REG32 SDR               : 1;
  __REG32                   :27;
} __i2c_swr_bits;

/* USI_Control and Status Register (USI_CNTRL) */
typedef struct {
  __REG32 GO_BUSY           : 1;
  __REG32 RX_NEG            : 1;
  __REG32 TX_NEG            : 1;
  __REG32 TX_BIT_LEN        : 5;
  __REG32 TX_NUM            : 2;
  __REG32 LSB               : 1;
  __REG32                   : 1;
  __REG32 SLEEP             : 4;
  __REG32 IF                : 1;
  __REG32 IE                : 1;
  __REG32                   :14;
} __usi_cntrl_bits;

/* USI Divider Register (USI_DIVIDER) */
typedef struct {
  __REG32 DIVIDER           :16;
  __REG32                   :16;
} __usi_divider_bits;

/* USI Slave Select Register (USI_SSR) */
typedef struct {
  __REG32 SSR               : 2;
  __REG32 SS_LVL            : 1;
  __REG32 ASS               : 1;
  __REG32                   :28;
} __usi_ssr_bits;

/* PWM Prescaler Register (PWM_PPR) */
typedef struct {
  __REG32 CP0               : 8;
  __REG32 CP1               : 8;
  __REG32 DZI0              : 8;
  __REG32 DZI1              : 8;
} __pwm_ppr_bits;

/* PWM Clock Select Register (PWM_CSR) */
typedef struct {
  __REG32 CSR0              : 3;
  __REG32                   : 1;
  __REG32 CSR1              : 3;
  __REG32                   : 1;
  __REG32 CSR2              : 3;
  __REG32                   : 1;
  __REG32 CSR3              : 3;
  __REG32                   :17;
} __pwm_csr_bits;

/* PWM Control Register (PWM_PCR) */
typedef struct {
  __REG32 PCR00             : 1;
  __REG32 PCR01             : 1;
  __REG32 PCR02             : 1;
  __REG32 PCR03             : 1;
  __REG32 PCR04             : 1;
  __REG32 PCR05             : 1;
  __REG32 PCR06             : 1;
  __REG32 PCR07             : 1;
  __REG32 PCR08             : 1;
  __REG32 PCR09             : 1;
  __REG32 PCR10             : 1;
  __REG32 PCR11             : 1;
  __REG32 PCR12             : 1;
  __REG32 PCR13             : 1;
  __REG32 PCR14             : 1;
  __REG32 PCR15             : 1;
  __REG32 PCR16             : 1;
  __REG32 PCR17             : 1;
  __REG32 PCR18             : 1;
  __REG32 PCR19             : 1;
  __REG32                   :12;
} __pwm_pcr_bits;

/* PWM Counter Register 0/1/2/3 (PWM_CNR0/1/2/3) */
typedef struct {
  __REG32 CNR               :16;
  __REG32                   :16;
} __pwm_cnr_bits;

/* PWM Comparator Register 0/1/2/3 (PWM_CMR0/1/2/3) */
typedef struct {
  __REG32 CMR               :16;
  __REG32                   :16;
} __pwm_cmr_bits;

/* PWM Data Register 0/1/2/3 (PWM_PDR 0/1/2/3) */
typedef struct {
  __REG32 PDR               :16;
  __REG32                   :16;
} __pwm_pdr_bits;

/* PWM Interrupt Enable Register (PWM_PIER) */
typedef struct {
  __REG32 PIER0             : 1;
  __REG32 PIER1             : 1;
  __REG32 PIER2             : 1;
  __REG32 PIER3             : 1;
  __REG32                   :28;
} __pwm_pier_bits;

/* PWM Interrupt Indication Register (PWM_PIIR) */
typedef struct {
  __REG32 PIIR0             : 1;
  __REG32 PIIR1             : 1;
  __REG32 PIIR2             : 1;
  __REG32 PIIR3             : 1;
  __REG32                   :28;
} __pwm_piir_bits;

/* Keypad Controller Configuration Register (KPI_CONF) */
typedef struct {
  __REG32 PRESCALE          : 8;
  __REG32 DBTC              : 8;
  __REG32 KSIZE             : 2;
  __REG32 ENKP              : 1;
  __REG32 KPSEL             : 1;
  __REG32 ODEN              : 1;
  __REG32 ENCODE            : 1;
  __REG32                   :10;
} __kpiconf_bits;

/* Keypad Controller 3-keys Configuration Register (KPI3KCONF) */
typedef struct {
  __REG32 K30C              : 3;
  __REG32 K30R              : 4;
  __REG32                   : 1;
  __REG32 K31C              : 3;
  __REG32 K31R              : 4;
  __REG32                   : 1;
  __REG32 K32C              : 3;
  __REG32 K32R              : 4;
  __REG32                   : 1;
  __REG32 ENRST             : 1;
  __REG32 EN3KY             : 1;
  __REG32                   : 6;
} __kpi3kconf_bits;

/* KeyPad Interface Low Power Mode Configuration Register (KPILPCONF) */
typedef struct {
  __REG32 LPWR              : 4;
  __REG32                   : 4;
  __REG32 LPWCEN            : 8;
  __REG32 WAKE              : 1;
  __REG32                   :15;
} __kpilpconf_bits;

/* Key Pad Interface Status Register (KPISTATUS) */
typedef struct {
  __REG32 KEY0C             : 3;
  __REG32 KEY0R             : 4;
  __REG32                   : 1;
  __REG32 KEY1C             : 3;
  __REG32 KEY1R             : 4;
  __REG32                   : 1;
  __REG32 _1KEY             : 1;
  __REG32 _2KEY             : 1;
  __REG32 _3KEY             : 1;
  __REG32 PDWAKE            : 1;
  __REG32 _3KRST            : 1;
  __REG32 INT               : 1;
  __REG32                   :10;
} __kpistatus_bits;

/* PS2 Host Controller Command Register (PS2_CMD) */
typedef struct {
  __REG32 PS2CMD            : 8;
  __REG32 ENCMD             : 1;
  __REG32 TRAP_SHIFT        : 1;
  __REG32                   :22;
} __ps2cmd_bits;

/* PS2 Host Controller Status Register (PS2_STS) */
typedef struct {
  __REG32 RX_IRQ            : 1;
  __REG32                   : 3;
  __REG32 TX_IRQ            : 1;
  __REG32 TX_ERR            : 1;
  __REG32                   :26;
} __ps2sts_bits;

/* PS2 Host Controller RX Scan Code Register (PS2_SCANCODE) */
typedef struct {
  __REG32 RX_SCAN_CODE      : 8;
  __REG32 RX_EXTEND         : 1;
  __REG32 RX_RELEASE        : 1;
  __REG32 RX_SHIFT_KEY      : 1;
  __REG32                   :21;
} __ps2scancode_bits;

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
__IO_REG32_BIT(PLLCON0,               0xFFF00008,__READ_WRITE ,__pllcon_bits);
__IO_REG32_BIT(CLKSEL,                0xFFF0000C,__READ_WRITE ,__clksel_bits);
__IO_REG32_BIT(PLLCON1,               0xFFF00010,__READ_WRITE ,__pllcon_bits);
__IO_REG32_BIT(I2SCKCON,              0xFFF00014,__READ_WRITE ,__i2sckcon_bits);
__IO_REG32_BIT(IRQWAKECON,            0xFFF00020,__READ_WRITE ,__irqwakecon_bits);
__IO_REG32_BIT(IRQWAKEFLAG,           0xFFF00024,__READ_WRITE ,__irqwakeflag_bits);
__IO_REG32_BIT(PMCON,                 0xFFF00028,__READ_WRITE ,__pmcon_bits);
__IO_REG32_BIT(USBTXRCON,             0xFFF00030,__READ_WRITE ,__usbtxrcon_bits);

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
__IO_REG32_BIT(CTEST0,                0xFFF60000,__READ_WRITE ,__ctest0_bits);
__IO_REG32_BIT(CTEST1,                0xFFF60004,__READ       ,__ctest1_bits);

/***************************************************************************
 **
 ** EMC
 **
 ***************************************************************************/
__IO_REG32_BIT(CAMCMR,                0xFFF03000,__READ_WRITE ,__camcmr_bits);
__IO_REG32_BIT(CAMEN,                 0xFFF03004,__READ_WRITE ,__camen_bits);
__IO_REG32_BIT(CAM0M,                 0xFFF03008,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM0L,                 0xFFF0300C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM1M,                 0xFFF03010,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM1L,                 0xFFF03014,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM2M,                 0xFFF03018,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM2L,                 0xFFF0301C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM3M,                 0xFFF03020,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM3L,                 0xFFF03024,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM4M,                 0xFFF03028,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM4L,                 0xFFF0302C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM5M,                 0xFFF03030,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM5L,                 0xFFF03034,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM6M,                 0xFFF03038,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM6L,                 0xFFF0303C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM7M,                 0xFFF03040,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM7L,                 0xFFF03044,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM8M,                 0xFFF03048,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM8L,                 0xFFF0304C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM9M,                 0xFFF03050,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM9L,                 0xFFF03054,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM10M,                0xFFF03058,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM10L,                0xFFF0305C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM11M,                0xFFF03060,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM11L,                0xFFF03064,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM12M,                0xFFF03068,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM12L,                0xFFF0306C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM13M,                0xFFF03070,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM13L,                0xFFF03074,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM14M,                0xFFF03078,__READ_WRITE ,__camm_bits);
__IO_REG32_BIT(CAM14L,                0xFFF0307C,__READ_WRITE ,__caml_bits);
__IO_REG32_BIT(CAM15M,                0xFFF03080,__READ_WRITE ,__cam15m_bits);
__IO_REG32_BIT(CAM15L,                0xFFF03084,__READ_WRITE ,__cam15l_bits);
__IO_REG32(    TXDLSA,                0xFFF03088,__READ_WRITE );
__IO_REG32(    RXDLSA,                0xFFF0308C,__READ_WRITE );
__IO_REG32_BIT(MCMDR,                 0xFFF03090,__READ_WRITE ,__mcmdr_bits);
__IO_REG32_BIT(MIID,                  0xFFF03094,__READ_WRITE ,__miid_bits);
__IO_REG32_BIT(MIIDA,                 0xFFF03098,__READ_WRITE ,__miida_bits);
__IO_REG32_BIT(FFTCR,                 0xFFF0309C,__READ_WRITE ,__fftcr_bits);
__IO_REG32(    TSDR,                  0xFFF030A0,__WRITE      );
__IO_REG32(    RSDR,                  0xFFF030A4,__WRITE      );
__IO_REG32_BIT(DMARFC,                0xFFF030A8,__READ_WRITE ,__dmarfc_bits);
__IO_REG32_BIT(MIEN,                  0xFFF030AC,__READ_WRITE ,__mien_bits);
__IO_REG32_BIT(MISTA,                 0xFFF030B0,__READ_WRITE ,__mista_bits);
__IO_REG32_BIT(MGSTA,                 0xFFF030B4,__READ_WRITE ,__mgsta_bits);
__IO_REG32_BIT(MPCNT,                 0xFFF030B8,__READ_WRITE ,__mpcnt_bits);
__IO_REG32_BIT(MRPC,                  0xFFF030BC,__READ       ,__mrpc_bits);
__IO_REG32_BIT(MRPCC,                 0xFFF030C0,__READ       ,__mrpcc_bits);
__IO_REG32_BIT(MREPC,                 0xFFF030C4,__READ       ,__mrepc_bits);
__IO_REG32_BIT(DMARFS,                0xFFF030C8,__READ_WRITE ,__dmarfs_bits);
__IO_REG32(    CTXDSA,                0xFFF030CC,__READ       );
__IO_REG32(    CTXBSA,                0xFFF030D0,__READ       );
__IO_REG32(    CRXDSA,                0xFFF030D4,__READ       );
__IO_REG32(    CRXBSA,                0xFFF030D8,__READ       );
__IO_REG32_BIT(RXFSM,                 0xFFF03200,__READ       ,__rxfsm_bits);
__IO_REG32_BIT(TXFSM,                 0xFFF03204,__READ       ,__txfsm_bits);
__IO_REG32_BIT(FSM0,                  0xFFF03208,__READ       ,__fsm0_bits);
__IO_REG32_BIT(FSM1,                  0xFFF0320C,__READ       ,__fsm1_bits);
__IO_REG32_BIT(DCR,                   0xFFF03210,__READ_WRITE ,__dcr_bits);
__IO_REG32_BIT(DMMIR,                 0xFFF03214,__READ       ,__dmmir_bits);
__IO_REG32_BIT(BISTR,                 0xFFF03300,__READ_WRITE ,__bistr_bits);

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
__IO_REG32(    TESTMODEENABLE,        0xFFF05200,__READ_WRITE );
__IO_REG32_BIT(OPERATIONALMODEENABLE, 0xFFF05204,__READ_WRITE ,__operationalmodeenable_bits);

/***************************************************************************
 **
 ** USB Device
 **
 ***************************************************************************/
__IO_REG32_BIT(USB_CTL,               0xFFF06000,__READ_WRITE ,__usb_ctl_bits);
__IO_REG32_BIT(USB_CVCMD,             0xFFF06004,__READ_WRITE ,__usb_cvcmd_bits);
__IO_REG32_BIT(USB_IE,                0xFFF06008,__READ_WRITE ,__usb_ie_bits);
__IO_REG32_BIT(USB_IS,                0xFFF0600C,__READ       ,__usb_is_bits);
__IO_REG32_BIT(USB_IC,                0xFFF06010,__READ_WRITE ,__usb_ic_bits);
__IO_REG32_BIT(USB_IFSTR,             0xFFF06014,__READ_WRITE ,__usb_ifstr_bits);
__IO_REG32(    USB_ODATA0,            0xFFF06018,__READ       );
__IO_REG32(    USB_ODATA1,            0xFFF0601C,__READ       );
__IO_REG32(    USB_ODATA2,            0xFFF06020,__READ       );
__IO_REG32(    USB_ODATA3,            0xFFF06024,__READ       );
__IO_REG32(    USB_IDATA0,            0xFFF06028,__READ_WRITE );
__IO_REG32(    USB_IDATA1,            0xFFF0602C,__READ_WRITE );
__IO_REG32(    USB_IDATA2,            0xFFF06030,__READ_WRITE );
__IO_REG32(    USB_IDATA3,            0xFFF06034,__READ_WRITE );
__IO_REG32_BIT(USB_SIE,               0xFFF06038,__READ       ,__usb_sie_bits);
__IO_REG32_BIT(USB_ENG,               0xFFF0603C,__READ_WRITE ,__usb_eng_bits);
__IO_REG32_BIT(USB_CTLS,              0xFFF06040,__READ       ,__usb_ctls_bits);
__IO_REG32_BIT(USB_CONFD,             0xFFF06044,__READ_WRITE ,__usb_confd_bits);
__IO_REG32_BIT(EPA_INFO,              0xFFF06048,__READ_WRITE ,__epa_info_bits);
__IO_REG32_BIT(EPA_CTL,               0xFFF0604C,__READ_WRITE ,__epa_ctl_bits);
__IO_REG32_BIT(EPA_IE,                0xFFF06050,__READ_WRITE ,__epa_ie_bits);
__IO_REG32_BIT(EPA_IC,                0xFFF06054,__WRITE      ,__epa_ic_bits);
__IO_REG32_BIT(EPA_IS,                0xFFF06058,__READ       ,__epa_is_bits);
__IO_REG32(    EPA_ADDR,              0xFFF0605C,__READ_WRITE );
__IO_REG32_BIT(EPA_LENTH,             0xFFF06060,__READ_WRITE ,__epa_lenth_bits);
__IO_REG32_BIT(EPB_INFO,              0xFFF06064,__READ_WRITE ,__epb_info_bits);
__IO_REG32_BIT(EPB_CTL,               0xFFF06068,__READ_WRITE ,__epb_ctl_bits);
__IO_REG32_BIT(EPB_IE,                0xFFF0606C,__READ_WRITE ,__epb_ie_bits);
__IO_REG32_BIT(EPB_IC,                0xFFF06070,__WRITE      ,__epb_ic_bits);
__IO_REG32_BIT(EPB_IS,                0xFFF06074,__READ       ,__epb_is_bits);
__IO_REG32(    EPB_ADDR,              0xFFF06078,__READ_WRITE );
__IO_REG32_BIT(EPB_LENTH,             0xFFF0607C,__READ_WRITE ,__epb_lenth_bits);
__IO_REG32_BIT(EPC_INFO,              0xFFF06080,__READ_WRITE ,__epc_info_bits);
__IO_REG32_BIT(EPC_CTL,               0xFFF06084,__READ_WRITE ,__epc_ctl_bits);
__IO_REG32_BIT(EPC_IE,                0xFFF06088,__READ_WRITE ,__epc_ie_bits);
__IO_REG32_BIT(EPC_IC,                0xFFF0608C,__WRITE      ,__epc_ic_bits);
__IO_REG32_BIT(EPC_IS,                0xFFF06090,__READ       ,__epc_is_bits);
__IO_REG32(    EPC_ADDR,              0xFFF06094,__READ_WRITE );
__IO_REG32_BIT(EPC_LENTH,             0xFFF06098,__READ_WRITE ,__epc_lenth_bits);
__IO_REG32_BIT(EPA_XFER,              0xFFF0609C,__READ_WRITE ,__epa_xfer_bits);
__IO_REG32_BIT(EPA_PKT,               0xFFF060A0,__READ_WRITE ,__epa_pkt_bits);
__IO_REG32_BIT(EPB_XFER,              0xFFF060A4,__READ_WRITE ,__epb_xfer_bits);
__IO_REG32_BIT(EPB_PKT,               0xFFF060A8,__READ_WRITE ,__epb_pkt_bits);
__IO_REG32_BIT(EPC_XFER,              0xFFF060AC,__READ_WRITE ,__epc_xfer_bits);
__IO_REG32_BIT(EPC_PKT,               0xFFF060B0,__READ_WRITE ,__epc_pkt_bits);

/***************************************************************************
 **
 ** SD
 **
 ***************************************************************************/
__IO_REG32_BIT(SDGCR,                 0xFFF07000,__READ_WRITE ,__sdgcr_bits);
__IO_REG32(    SDDSA,                 0xFFF07004,__READ_WRITE );
__IO_REG32_BIT(SDBCR,                 0xFFF07008,__READ_WRITE ,__sdbcr_bits);
__IO_REG32_BIT(SDGIER,                0xFFF0700C,__READ_WRITE ,__sdgier_bits);
__IO_REG32_BIT(SDGISR,                0xFFF07010,__READ_WRITE ,__sdgisr_bits);
__IO_REG32_BIT(SDBIST,                0xFFF07014,__READ_WRITE ,__sdbist_bits);
__IO_REG32_BIT(SDICR,                 0xFFF07300,__READ_WRITE ,__sdicr_bits);
__IO_REG32_BIT(SDHIIR,                0xFFF07304,__READ_WRITE ,__sdhiir_bits);
__IO_REG32_BIT(SDIIER,                0xFFF07308,__READ_WRITE ,__sdiier_bits);
__IO_REG32_BIT(SDIISR,                0xFFF0730C,__READ_WRITE ,__sdiisr_bits);
__IO_REG32(    SDAUG,                 0xFFF07310,__READ_WRITE );
__IO_REG32(    SDRSP0,                0xFFF07314,__READ       );
__IO_REG8(     SDRSP1,                0xFFF07318,__READ       );
__IO_REG32_BIT(SDBLEN,                0xFFF0731C,__READ_WRITE ,__sdblen_bits);
__IO_REG32(    SDIO_FB0_0,            0xFFF07400,__READ_WRITE );
__IO_REG32(    SDIO_FB0_1,            0xFFF07404,__READ_WRITE );
__IO_REG32(    SDIO_FB0_2,            0xFFF07408,__READ_WRITE );
__IO_REG32(    SDIO_FB0_3,            0xFFF0740C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_4,            0xFFF07410,__READ_WRITE );
__IO_REG32(    SDIO_FB0_5,            0xFFF07414,__READ_WRITE );
__IO_REG32(    SDIO_FB0_6,            0xFFF07418,__READ_WRITE );
__IO_REG32(    SDIO_FB0_7,            0xFFF0741C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_8,            0xFFF07420,__READ_WRITE );
__IO_REG32(    SDIO_FB0_9,            0xFFF07424,__READ_WRITE );
__IO_REG32(    SDIO_FB0_10,           0xFFF07428,__READ_WRITE );
__IO_REG32(    SDIO_FB0_11,           0xFFF0742C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_12,           0xFFF07430,__READ_WRITE );
__IO_REG32(    SDIO_FB0_13,           0xFFF07434,__READ_WRITE );
__IO_REG32(    SDIO_FB0_14,           0xFFF07438,__READ_WRITE );
__IO_REG32(    SDIO_FB0_15,           0xFFF0743C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_16,           0xFFF07440,__READ_WRITE );
__IO_REG32(    SDIO_FB0_17,           0xFFF07444,__READ_WRITE );
__IO_REG32(    SDIO_FB0_18,           0xFFF07448,__READ_WRITE );
__IO_REG32(    SDIO_FB0_19,           0xFFF0744C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_20,           0xFFF07450,__READ_WRITE );
__IO_REG32(    SDIO_FB0_21,           0xFFF07454,__READ_WRITE );
__IO_REG32(    SDIO_FB0_22,           0xFFF07458,__READ_WRITE );
__IO_REG32(    SDIO_FB0_23,           0xFFF0745C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_24,           0xFFF07460,__READ_WRITE );
__IO_REG32(    SDIO_FB0_25,           0xFFF07464,__READ_WRITE );
__IO_REG32(    SDIO_FB0_26,           0xFFF07468,__READ_WRITE );
__IO_REG32(    SDIO_FB0_27,           0xFFF0746C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_28,           0xFFF07470,__READ_WRITE );
__IO_REG32(    SDIO_FB0_29,           0xFFF07474,__READ_WRITE );
__IO_REG32(    SDIO_FB0_30,           0xFFF07478,__READ_WRITE );
__IO_REG32(    SDIO_FB0_31,           0xFFF0747C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_32,           0xFFF07480,__READ_WRITE );
__IO_REG32(    SDIO_FB0_33,           0xFFF07484,__READ_WRITE );
__IO_REG32(    SDIO_FB0_34,           0xFFF07488,__READ_WRITE );
__IO_REG32(    SDIO_FB0_35,           0xFFF0748C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_36,           0xFFF07490,__READ_WRITE );
__IO_REG32(    SDIO_FB0_37,           0xFFF07494,__READ_WRITE );
__IO_REG32(    SDIO_FB0_38,           0xFFF07498,__READ_WRITE );
__IO_REG32(    SDIO_FB0_39,           0xFFF0749C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_40,           0xFFF074A0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_41,           0xFFF074A4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_42,           0xFFF074A8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_43,           0xFFF074AC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_44,           0xFFF074B0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_45,           0xFFF074B4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_46,           0xFFF074B8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_47,           0xFFF074BC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_48,           0xFFF074C0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_49,           0xFFF074C4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_50,           0xFFF074C8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_51,           0xFFF074CC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_52,           0xFFF074D0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_53,           0xFFF074D4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_54,           0xFFF074D8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_55,           0xFFF074DC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_56,           0xFFF074E0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_57,           0xFFF074E4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_58,           0xFFF074E8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_59,           0xFFF074EC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_60,           0xFFF074F0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_61,           0xFFF074F4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_62,           0xFFF074F8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_63,           0xFFF074FC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_64,           0xFFF07500,__READ_WRITE );
__IO_REG32(    SDIO_FB0_65,           0xFFF07504,__READ_WRITE );
__IO_REG32(    SDIO_FB0_66,           0xFFF07508,__READ_WRITE );
__IO_REG32(    SDIO_FB0_67,           0xFFF0750C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_68,           0xFFF07510,__READ_WRITE );
__IO_REG32(    SDIO_FB0_69,           0xFFF07514,__READ_WRITE );
__IO_REG32(    SDIO_FB0_70,           0xFFF07518,__READ_WRITE );
__IO_REG32(    SDIO_FB0_71,           0xFFF0751C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_72,           0xFFF07520,__READ_WRITE );
__IO_REG32(    SDIO_FB0_73,           0xFFF07524,__READ_WRITE );
__IO_REG32(    SDIO_FB0_74,           0xFFF07528,__READ_WRITE );
__IO_REG32(    SDIO_FB0_75,           0xFFF0752C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_76,           0xFFF07530,__READ_WRITE );
__IO_REG32(    SDIO_FB0_77,           0xFFF07534,__READ_WRITE );
__IO_REG32(    SDIO_FB0_78,           0xFFF07538,__READ_WRITE );
__IO_REG32(    SDIO_FB0_79,           0xFFF0753C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_80,           0xFFF07540,__READ_WRITE );
__IO_REG32(    SDIO_FB0_81,           0xFFF07544,__READ_WRITE );
__IO_REG32(    SDIO_FB0_82,           0xFFF07548,__READ_WRITE );
__IO_REG32(    SDIO_FB0_83,           0xFFF0754C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_84,           0xFFF07550,__READ_WRITE );
__IO_REG32(    SDIO_FB0_85,           0xFFF07554,__READ_WRITE );
__IO_REG32(    SDIO_FB0_86,           0xFFF07558,__READ_WRITE );
__IO_REG32(    SDIO_FB0_87,           0xFFF0755C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_88,           0xFFF07560,__READ_WRITE );
__IO_REG32(    SDIO_FB0_89,           0xFFF07564,__READ_WRITE );
__IO_REG32(    SDIO_FB0_90,           0xFFF07568,__READ_WRITE );
__IO_REG32(    SDIO_FB0_91,           0xFFF0756C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_92,           0xFFF07570,__READ_WRITE );
__IO_REG32(    SDIO_FB0_93,           0xFFF07574,__READ_WRITE );
__IO_REG32(    SDIO_FB0_94,           0xFFF07578,__READ_WRITE );
__IO_REG32(    SDIO_FB0_95,           0xFFF0757C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_96,           0xFFF07580,__READ_WRITE );
__IO_REG32(    SDIO_FB0_97,           0xFFF07584,__READ_WRITE );
__IO_REG32(    SDIO_FB0_98,           0xFFF07588,__READ_WRITE );
__IO_REG32(    SDIO_FB0_99,           0xFFF0758C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_100,          0xFFF07590,__READ_WRITE );
__IO_REG32(    SDIO_FB0_101,          0xFFF07594,__READ_WRITE );
__IO_REG32(    SDIO_FB0_102,          0xFFF07598,__READ_WRITE );
__IO_REG32(    SDIO_FB0_103,          0xFFF0759C,__READ_WRITE );
__IO_REG32(    SDIO_FB0_104,          0xFFF075A0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_105,          0xFFF075A4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_106,          0xFFF075A8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_107,          0xFFF075AC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_108,          0xFFF075B0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_109,          0xFFF075B4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_110,          0xFFF075B8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_111,          0xFFF075BC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_112,          0xFFF075C0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_113,          0xFFF075C4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_114,          0xFFF075C8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_115,          0xFFF075CC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_116,          0xFFF075D0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_117,          0xFFF075D4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_118,          0xFFF075D8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_119,          0xFFF075DC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_120,          0xFFF075E0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_121,          0xFFF075E4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_122,          0xFFF075E8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_123,          0xFFF075EC,__READ_WRITE );
__IO_REG32(    SDIO_FB0_124,          0xFFF075F0,__READ_WRITE );
__IO_REG32(    SDIO_FB0_125,          0xFFF075F4,__READ_WRITE );
__IO_REG32(    SDIO_FB0_126,          0xFFF075F8,__READ_WRITE );
__IO_REG32(    SDIO_FB0_127,          0xFFF075FC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_0,            0xFFF07800,__READ_WRITE );
__IO_REG32(    SDIO_FB1_1,            0xFFF07804,__READ_WRITE );
__IO_REG32(    SDIO_FB1_2,            0xFFF07808,__READ_WRITE );
__IO_REG32(    SDIO_FB1_3,            0xFFF0780C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_4,            0xFFF07810,__READ_WRITE );
__IO_REG32(    SDIO_FB1_5,            0xFFF07814,__READ_WRITE );
__IO_REG32(    SDIO_FB1_6,            0xFFF07818,__READ_WRITE );
__IO_REG32(    SDIO_FB1_7,            0xFFF0781C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_8,            0xFFF07820,__READ_WRITE );
__IO_REG32(    SDIO_FB1_9,            0xFFF07824,__READ_WRITE );
__IO_REG32(    SDIO_FB1_10,           0xFFF07828,__READ_WRITE );
__IO_REG32(    SDIO_FB1_11,           0xFFF0782C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_12,           0xFFF07830,__READ_WRITE );
__IO_REG32(    SDIO_FB1_13,           0xFFF07834,__READ_WRITE );
__IO_REG32(    SDIO_FB1_14,           0xFFF07838,__READ_WRITE );
__IO_REG32(    SDIO_FB1_15,           0xFFF0783C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_16,           0xFFF07840,__READ_WRITE );
__IO_REG32(    SDIO_FB1_17,           0xFFF07844,__READ_WRITE );
__IO_REG32(    SDIO_FB1_18,           0xFFF07848,__READ_WRITE );
__IO_REG32(    SDIO_FB1_19,           0xFFF0784C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_20,           0xFFF07850,__READ_WRITE );
__IO_REG32(    SDIO_FB1_21,           0xFFF07854,__READ_WRITE );
__IO_REG32(    SDIO_FB1_22,           0xFFF07858,__READ_WRITE );
__IO_REG32(    SDIO_FB1_23,           0xFFF0785C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_24,           0xFFF07860,__READ_WRITE );
__IO_REG32(    SDIO_FB1_25,           0xFFF07864,__READ_WRITE );
__IO_REG32(    SDIO_FB1_26,           0xFFF07868,__READ_WRITE );
__IO_REG32(    SDIO_FB1_27,           0xFFF0786C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_28,           0xFFF07870,__READ_WRITE );
__IO_REG32(    SDIO_FB1_29,           0xFFF07874,__READ_WRITE );
__IO_REG32(    SDIO_FB1_30,           0xFFF07878,__READ_WRITE );
__IO_REG32(    SDIO_FB1_31,           0xFFF0787C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_32,           0xFFF07880,__READ_WRITE );
__IO_REG32(    SDIO_FB1_33,           0xFFF07884,__READ_WRITE );
__IO_REG32(    SDIO_FB1_34,           0xFFF07888,__READ_WRITE );
__IO_REG32(    SDIO_FB1_35,           0xFFF0788C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_36,           0xFFF07890,__READ_WRITE );
__IO_REG32(    SDIO_FB1_37,           0xFFF07894,__READ_WRITE );
__IO_REG32(    SDIO_FB1_38,           0xFFF07898,__READ_WRITE );
__IO_REG32(    SDIO_FB1_39,           0xFFF0789C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_40,           0xFFF078A0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_41,           0xFFF078A4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_42,           0xFFF078A8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_43,           0xFFF078AC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_44,           0xFFF078B0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_45,           0xFFF078B4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_46,           0xFFF078B8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_47,           0xFFF078BC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_48,           0xFFF078C0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_49,           0xFFF078C4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_50,           0xFFF078C8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_51,           0xFFF078CC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_52,           0xFFF078D0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_53,           0xFFF078D4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_54,           0xFFF078D8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_55,           0xFFF078DC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_56,           0xFFF078E0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_57,           0xFFF078E4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_58,           0xFFF078E8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_59,           0xFFF078EC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_60,           0xFFF078F0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_61,           0xFFF078F4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_62,           0xFFF078F8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_63,           0xFFF078FC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_64,           0xFFF07900,__READ_WRITE );
__IO_REG32(    SDIO_FB1_65,           0xFFF07904,__READ_WRITE );
__IO_REG32(    SDIO_FB1_66,           0xFFF07908,__READ_WRITE );
__IO_REG32(    SDIO_FB1_67,           0xFFF0790C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_68,           0xFFF07910,__READ_WRITE );
__IO_REG32(    SDIO_FB1_69,           0xFFF07914,__READ_WRITE );
__IO_REG32(    SDIO_FB1_70,           0xFFF07918,__READ_WRITE );
__IO_REG32(    SDIO_FB1_71,           0xFFF0791C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_72,           0xFFF07920,__READ_WRITE );
__IO_REG32(    SDIO_FB1_73,           0xFFF07924,__READ_WRITE );
__IO_REG32(    SDIO_FB1_74,           0xFFF07928,__READ_WRITE );
__IO_REG32(    SDIO_FB1_75,           0xFFF0792C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_76,           0xFFF07930,__READ_WRITE );
__IO_REG32(    SDIO_FB1_77,           0xFFF07934,__READ_WRITE );
__IO_REG32(    SDIO_FB1_78,           0xFFF07938,__READ_WRITE );
__IO_REG32(    SDIO_FB1_79,           0xFFF0793C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_80,           0xFFF07940,__READ_WRITE );
__IO_REG32(    SDIO_FB1_81,           0xFFF07944,__READ_WRITE );
__IO_REG32(    SDIO_FB1_82,           0xFFF07948,__READ_WRITE );
__IO_REG32(    SDIO_FB1_83,           0xFFF0794C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_84,           0xFFF07950,__READ_WRITE );
__IO_REG32(    SDIO_FB1_85,           0xFFF07954,__READ_WRITE );
__IO_REG32(    SDIO_FB1_86,           0xFFF07958,__READ_WRITE );
__IO_REG32(    SDIO_FB1_87,           0xFFF0795C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_88,           0xFFF07960,__READ_WRITE );
__IO_REG32(    SDIO_FB1_89,           0xFFF07964,__READ_WRITE );
__IO_REG32(    SDIO_FB1_90,           0xFFF07968,__READ_WRITE );
__IO_REG32(    SDIO_FB1_91,           0xFFF0796C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_92,           0xFFF07970,__READ_WRITE );
__IO_REG32(    SDIO_FB1_93,           0xFFF07974,__READ_WRITE );
__IO_REG32(    SDIO_FB1_94,           0xFFF07978,__READ_WRITE );
__IO_REG32(    SDIO_FB1_95,           0xFFF0797C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_96,           0xFFF07980,__READ_WRITE );
__IO_REG32(    SDIO_FB1_97,           0xFFF07984,__READ_WRITE );
__IO_REG32(    SDIO_FB1_98,           0xFFF07988,__READ_WRITE );
__IO_REG32(    SDIO_FB1_99,           0xFFF0798C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_100,          0xFFF07990,__READ_WRITE );
__IO_REG32(    SDIO_FB1_101,          0xFFF07994,__READ_WRITE );
__IO_REG32(    SDIO_FB1_102,          0xFFF07998,__READ_WRITE );
__IO_REG32(    SDIO_FB1_103,          0xFFF0799C,__READ_WRITE );
__IO_REG32(    SDIO_FB1_104,          0xFFF079A0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_105,          0xFFF079A4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_106,          0xFFF079A8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_107,          0xFFF079AC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_108,          0xFFF079B0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_109,          0xFFF079B4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_110,          0xFFF079B8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_111,          0xFFF079BC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_112,          0xFFF079C0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_113,          0xFFF079C4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_114,          0xFFF079C8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_115,          0xFFF079CC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_116,          0xFFF079D0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_117,          0xFFF079D4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_118,          0xFFF079D8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_119,          0xFFF079DC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_120,          0xFFF079E0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_121,          0xFFF079E4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_122,          0xFFF079E8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_123,          0xFFF079EC,__READ_WRITE );
__IO_REG32(    SDIO_FB1_124,          0xFFF079F0,__READ_WRITE );
__IO_REG32(    SDIO_FB1_125,          0xFFF079F4,__READ_WRITE );
__IO_REG32(    SDIO_FB1_126,          0xFFF079F8,__READ_WRITE );
__IO_REG32(    SDIO_FB1_127,          0xFFF079FC,__READ_WRITE );

/***************************************************************************
 **
 ** LCD
 **
 ***************************************************************************/
__IO_REG32_BIT(LCDCON,                0xFFF08000,__READ_WRITE ,__lcdcon_bits);
__IO_REG32_BIT(LCDINTENB,             0xFFF08004,__READ_WRITE ,__lcdintenb_bits);
__IO_REG32_BIT(LCDINTS,               0xFFF08008,__READ       ,__lcdints_bits);
__IO_REG32_BIT(LCDINTC,               0xFFF0800C,__WRITE      ,__lcdintc_bits);
__IO_REG32_BIT(OSDUPSCF,              0xFFF08010,__READ_WRITE ,__osdupscf_bits);
__IO_REG32_BIT(VDUPSCF,               0xFFF08014,__READ_WRITE ,__vdupscf_bits);
__IO_REG32_BIT(OSDDNSCF,              0xFFF08018,__READ_WRITE ,__osddnscf_bits);
__IO_REG32_BIT(VDDNSCF,               0xFFF0801C,__READ_WRITE ,__vddnscf_bits);
__IO_REG32_BIT(FIFOCON,               0xFFF08020,__READ_WRITE ,__fifocon_bits);
__IO_REG32_BIT(FIFOSTATUS,            0xFFF08024,__READ       ,__fifostatus_bits);
__IO_REG32_BIT(FIFO1PRM,              0xFFF08028,__READ_WRITE ,__fifoprm_bits);
__IO_REG32_BIT(FIFO2PRM,              0xFFF0802C,__READ_WRITE ,__fifoprm_bits);
__IO_REG32(    FIFO1SADDR,            0xFFF08030,__READ_WRITE );
__IO_REG32(    FIFO2SADDR,            0xFFF08034,__READ_WRITE );
__IO_REG32_BIT(FIFO1DREQCNT,          0xFFF08038,__READ_WRITE ,__fifodreqcnt_bits);
__IO_REG32_BIT(FIFO2DREQCNT,          0xFFF0803C,__READ_WRITE ,__fifodreqcnt_bits);
__IO_REG32(    FIFO1CURADR,           0xFFF08040,__READ       );
__IO_REG32(    FIFO2CURADR,           0xFFF08044,__READ       );
__IO_REG16(    FIFO1RELACOLCNT,       0xFFF08048,__READ_WRITE );
__IO_REG16(    FIFO2RELACOLCNT,       0xFFF0804C,__READ_WRITE );

__IO_REG32(    VDLUTENTRY1,           0xFFF08050,__READ_WRITE );
__IO_REG32(    VDLUTENTRY2,           0xFFF08054,__READ_WRITE );
__IO_REG32(    VDLUTENTRY3,           0xFFF08058,__READ_WRITE );
__IO_REG32(    VDLUTENTRY4,           0xFFF0805C,__READ_WRITE );
__IO_REG32(    OSDLUTENTRY1,          0xFFF08060,__READ_WRITE );
__IO_REG32(    OSDLUTENTRY2,          0xFFF08064,__READ_WRITE );
__IO_REG32(    OSDLUTENTRY3,          0xFFF08068,__READ_WRITE );
__IO_REG32(    OSDLUTENTRY4,          0xFFF0806C,__READ_WRITE );
__IO_REG32_BIT(DITHP1,                0xFFF08070,__READ_WRITE ,__dithp1_bits);
__IO_REG32_BIT(DITHP2,                0xFFF08074,__READ_WRITE ,__dithp2_bits);
__IO_REG32_BIT(DITHP3,                0xFFF08078,__READ_WRITE ,__dithp3_bits);
__IO_REG32_BIT(DITHP4,                0xFFF0807C,__READ_WRITE ,__dithp4_bits);
__IO_REG32_BIT(DITHP5,                0xFFF08080,__READ_WRITE ,__dithp5_bits);
__IO_REG32_BIT(DITHP6,                0xFFF08084,__READ_WRITE ,__dithp6_bits);
__IO_REG32_BIT(DITHP7,                0xFFF08088,__READ_WRITE ,__dithp7_bits);
__IO_REG32_BIT(DDISPCP,               0xFFF08090,__READ_WRITE ,__ddispcp_bits);
__IO_REG32_BIT(VWINS,                 0xFFF08094,__READ_WRITE ,__vwins_bits);
__IO_REG32_BIT(VWINE,                 0xFFF08098,__READ_WRITE ,__vwine_bits);
__IO_REG32_BIT(OSDWINS,               0xFFF0809C,__READ_WRITE ,__osdwins_bits);
__IO_REG32_BIT(OSDWINE,               0xFFF080A0,__READ_WRITE ,__osdwine_bits);
__IO_REG32_BIT(OSDOVCN,               0xFFF080A4,__READ_WRITE ,__osdovcn_bits);
__IO_REG32_BIT(OSDOVCKP,              0xFFF080A8,__READ_WRITE ,__osdovckp_bits);
__IO_REG32_BIT(OSDOVCKM,              0xFFF080AC,__READ_WRITE ,__osdovckm_bits);
__IO_REG32_BIT(LCDTCON1,              0xFFF080B0,__READ_WRITE ,__lcdtcon1_bits);
__IO_REG32_BIT(LCDTCON2,              0xFFF080B4,__READ_WRITE ,__lcdtcon2_bits);
__IO_REG32_BIT(LCDTCON3,              0xFFF080B8,__READ_WRITE ,__lcdtcon3_bits);
__IO_REG32_BIT(LCDTCON4,              0xFFF080BC,__READ_WRITE ,__lcdtcon4_bits);
__IO_REG32_BIT(LCDTCON5,              0xFFF080C0,__READ_WRITE ,__lcdtcon5_bits);
__IO_REG32_BIT(LCDTCON6,              0xFFF080C4,__READ       ,__lcdtcon6_bits);
__IO_REG32_BIT(BIST,                  0xFFF080D0,__READ_WRITE ,__bist_bits);
__IO_REG32(    LCD_LTB_BASE,          0xFFF08100,__READ_WRITE );

/***************************************************************************
 **
 ** Audio Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(ACTL_CON,              0xFFF09000,__READ_WRITE ,__actl_con_bits);
__IO_REG32_BIT(ACTL_RESET,            0xFFF09004,__READ_WRITE ,__actl_reset_bits);
__IO_REG32(    ACTL_RDSTB,            0xFFF09008,__READ_WRITE );
__IO_REG32(    ACTL_RDST_LENGTH,      0xFFF0900C,__READ_WRITE );
__IO_REG32(    ACTL_RDSTC,            0xFFF09010,__READ       );
__IO_REG32_BIT(ACTL_RSR,              0xFFF09014,__READ_WRITE ,__actl_rsr_bits);
__IO_REG32(    ACTL_PDSTB,            0xFFF09018,__READ_WRITE );
__IO_REG32(    ACTL_PDST_LENGTH,      0xFFF0901C,__READ_WRITE );
__IO_REG32(    ACTL_PDSTC,            0xFFF09020,__READ       );
__IO_REG32_BIT(ACTL_PSR,              0xFFF09024,__READ_WRITE ,__actl_psr_bits);
__IO_REG32_BIT(ACTL_I2SCON,           0xFFF09028,__READ_WRITE ,__actl_i2scon_bits);
__IO_REG32_BIT(ACTL_ACCON,            0xFFF0902C,__READ_WRITE ,__actl_accon_bits);
__IO_REG32_BIT(ACTL_ACOS0,            0xFFF09030,__READ_WRITE ,__actl_acos0_bits);
__IO_REG32_BIT(ACTL_ACOS1,            0xFFF09034,__READ_WRITE ,__actl_acos1_bits);
__IO_REG32_BIT(ACTL_ACOS2,            0xFFF09038,__READ_WRITE ,__actl_acos2_bits);
__IO_REG32_BIT(ACTL_ACIS0,            0xFFF0903C,__READ       ,__actl_acis0_bits);
__IO_REG32_BIT(ACTL_ACIS1,            0xFFF09040,__READ       ,__actl_acis1_bits);
__IO_REG32_BIT(ACTL_ACIS2,            0xFFF09044,__READ       ,__actl_acis2_bits);

/***************************************************************************
 **
 ** UART0
 **
 ***************************************************************************/
__IO_REG8(     UART0_RBR,             0xFFF80000,__READ_WRITE );
#define UART0_THR     UART0_RBR
#define UART0_DLL     UART0_RBR
__IO_REG32_BIT(UART0_IER,             0xFFF80004,__READ_WRITE ,__uart_ier_bits);
#define UART0_DLM     UART0_IER
#define UART0_DLM_bit UART0_IER_bit
__IO_REG32_BIT(UART0_IIR,             0xFFF80008,__READ_WRITE ,__uart_iir_bits);
#define UART0_FCR     UART0_IIR
#define UART0_FCR_bit UART0_IIR_bit
__IO_REG32_BIT(UART0_LCR,             0xFFF8000C,__READ_WRITE ,__uart_lcr_bits);
__IO_REG32_BIT(UART0_LSR,             0xFFF80014,__READ       ,__uart_lsr_bits);
__IO_REG32_BIT(UART0_TOR,             0xFFF8001C,__READ_WRITE ,__uart_tor_bits);

/***************************************************************************
 **
 ** UART1
 **
 ***************************************************************************/
__IO_REG8(     UART1_RBR,             0xFFF80100,__READ_WRITE );
#define UART1_THR     UART1_RBR
#define UART1_DLL     UART1_RBR
__IO_REG32_BIT(UART1_IER,             0xFFF80104,__READ_WRITE ,__uart_ier_bits);
#define UART1_DLM     UART1_IER
#define UART1_DLM_bit UART1_IER_bit
__IO_REG32_BIT(UART1_IIR,             0xFFF80108,__READ_WRITE ,__uart1_iir_bits);
#define UART1_FCR     UART1_IIR
#define UART1_FCR_bit UART1_IIR_bit
__IO_REG32_BIT(UART1_LCR,             0xFFF8010C,__READ_WRITE ,__uart_lcr_bits);
__IO_REG32_BIT(UART1_MCR,             0xFFF80110,__READ_WRITE ,__uart1_mcr_bits);
__IO_REG32_BIT(UART1_LSR,             0xFFF80114,__READ       ,__uart_lsr_bits);
__IO_REG32_BIT(UART1_MSR,             0xFFF80118,__READ       ,__uart1_msr_bits);
__IO_REG32_BIT(UART1_TOR,             0xFFF8011C,__READ_WRITE ,__uart_tor_bits);
__IO_REG32_BIT(UART1_UBCR,            0xFFF80120,__READ_WRITE ,__uart_ubcr_bits);

/***************************************************************************
 **
 ** UART2
 **
 ***************************************************************************/
__IO_REG8(     UART2_RBR,             0xFFF80200,__READ_WRITE );
#define UART2_THR     UART2_RBR
#define UART2_DLL     UART2_RBR
__IO_REG32_BIT(UART2_IER,             0xFFF80204,__READ_WRITE ,__uart_ier_bits);
#define UART2_DLM     UART2_IER
#define UART2_DLM_bit UART2_IER_bit
__IO_REG32_BIT(UART2_IIR,             0xFFF80208,__READ_WRITE ,__uart_iir_bits);
#define UART0_FCR     UART0_IIR
#define UART0_FCR_bit UART0_IIR_bit
__IO_REG32_BIT(UART2_LCR,             0xFFF8020C,__READ_WRITE ,__uart_lcr_bits);
__IO_REG32_BIT(UART2_LSR,             0xFFF80214,__READ       ,__uart_lsr_bits);
__IO_REG32_BIT(UART2_TOR,             0xFFF8021C,__READ_WRITE ,__uart_tor_bits);
__IO_REG32_BIT(UART2_IRCR,            0xFFF80220,__READ_WRITE ,__uart_ircr_bits);

/***************************************************************************
 **
 ** UART3
 **
 ***************************************************************************/
__IO_REG8(     UART3_RBR,             0xFFF80300,__READ_WRITE );
#define UART3_THR     UART3_RBR
#define UART3_DLL     UART3_RBR
__IO_REG32_BIT(UART3_IER,             0xFFF80304,__READ_WRITE ,__uart_ier_bits);
#define UART3_DLM     UART3_IER
#define UART3_DLM_bit UART3_IER_bit
__IO_REG32_BIT(UART3_IIR,             0xFFF80308,__READ_WRITE ,__uart_iir_bits);
#define UART3_FCR     UART3_IIR
#define UART3_FCR_bit UART3_IIR_bit
__IO_REG32_BIT(UART3_LCR,             0xFFF8030C,__READ_WRITE ,__uart_lcr_bits);
__IO_REG32_BIT(UART3_MCR,             0xFFF80310,__READ_WRITE ,__uart_mcr_bits);
__IO_REG32_BIT(UART3_LSR,             0xFFF80314,__READ       ,__uart_lsr_bits);
__IO_REG32_BIT(UART3_MSR,             0xFFF80318,__READ       ,__uart_msr_bits);
__IO_REG32_BIT(UART3_TOR,             0xFFF8031C,__READ_WRITE ,__uart_tor_bits);

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
__IO_REG32_BIT(AIC_SCR19,             0xFFF8204C,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR20,             0xFFF82050,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR21,             0xFFF82054,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR22,             0xFFF82058,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR23,             0xFFF8205C,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR24,             0xFFF82060,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR25,             0xFFF82064,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR26,             0xFFF82068,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR27,             0xFFF8206C,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR28,             0xFFF82070,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR29,             0xFFF82074,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR30,             0xFFF82078,__READ_WRITE ,__aic_scr_bits);
__IO_REG32_BIT(AIC_SCR31,             0xFFF8207C,__READ_WRITE ,__aic_scr_bits);
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
__IO_REG32_BIT(AIC_TEST,              0xFFF82200,__WRITE      ,__aic_test_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIO_CFG0,             0xFFF83000,__READ_WRITE ,__gpio_cfg0_bits);
__IO_REG32_BIT(GPIO_DIR0,             0xFFF83004,__READ_WRITE ,__gpio_dir0_bits);
__IO_REG32_BIT(GPIO_DATAOUT0,         0xFFF83008,__READ_WRITE ,__gpio_dataout0_bits);
__IO_REG32_BIT(GPIO_DATAIN0,          0xFFF8300C,__READ       ,__gpio_datain0_bits);
__IO_REG32_BIT(GPIO_CFG1,             0xFFF83010,__READ_WRITE ,__gpio_cfg1_bits);
__IO_REG32_BIT(GPIO_DIR1,             0xFFF83014,__READ_WRITE ,__gpio_dir1_bits);
__IO_REG32_BIT(GPIO_DATAOUT1,         0xFFF83018,__READ_WRITE ,__gpio_dataout1_bits);
__IO_REG32_BIT(GPIO_DATAIN1,          0xFFF8301C,__READ       ,__gpio_datain1_bits);
__IO_REG32_BIT(GPIO_CFG2,             0xFFF83020,__READ_WRITE ,__gpio_cfg2_bits);
__IO_REG32_BIT(GPIO_DIR2,             0xFFF83024,__READ_WRITE ,__gpio_dir2_bits);
__IO_REG32_BIT(GPIO_DATAOUT2,         0xFFF83028,__READ_WRITE ,__gpio_dataout2_bits);
__IO_REG32_BIT(GPIO_DATAIN2,          0xFFF8302C,__READ       ,__gpio_datain2_bits);
__IO_REG32_BIT(GPIO_CFG3,             0xFFF83030,__READ_WRITE ,__gpio_cfg3_bits);
__IO_REG32_BIT(GPIO_DIR3,             0xFFF83034,__READ_WRITE ,__gpio_dir3_bits);
__IO_REG32_BIT(GPIO_DATAOUT3,         0xFFF83038,__READ_WRITE ,__gpio_dataout3_bits);
__IO_REG32_BIT(GPIO_DATAIN3,          0xFFF8303C,__READ       ,__gpio_datain3_bits);
__IO_REG32_BIT(GPIO_CFG4,             0xFFF83040,__READ_WRITE ,__gpio_cfg4_bits);
__IO_REG32_BIT(GPIO_DIR4,             0xFFF83044,__READ_WRITE ,__gpio_dir4_bits);
__IO_REG32_BIT(GPIO_DATAOUT4,         0xFFF83048,__READ_WRITE ,__gpio_dataout4_bits);
__IO_REG32_BIT(GPIO_DATAIN4,          0xFFF8304C,__READ       ,__gpio_datain4_bits);
__IO_REG32_BIT(GPIO_CFG5,             0xFFF83050,__READ_WRITE ,__gpio_cfg5_bits);
__IO_REG32_BIT(GPIO_DIR5,             0xFFF83054,__READ_WRITE ,__gpio_dir5_bits);
__IO_REG32_BIT(GPIO_DATAOUT5,         0xFFF83058,__READ_WRITE ,__gpio_dataout5_bits);
__IO_REG32_BIT(GPIO_DATAIN5,          0xFFF8305C,__READ       ,__gpio_datain5_bits);
__IO_REG32_BIT(GPIO_CFG6,             0xFFF83060,__READ_WRITE ,__gpio_cfg6_bits);
__IO_REG32_BIT(GPIO_DIR6,             0xFFF83064,__READ_WRITE ,__gpio_dir6_bits);
__IO_REG32_BIT(GPIO_DATAOUT6,         0xFFF83068,__READ_WRITE ,__gpio_dataout6_bits);
__IO_REG32_BIT(GPIO_DATAIN6,          0xFFF8306C,__READ       ,__gpio_datain6_bits);
__IO_REG32_BIT(GPIO_DBNCECON,         0xFFF83070,__READ_WRITE ,__gpio_dbncecon_bits);
__IO_REG32_BIT(GPIO_XICFG,            0xFFF83074,__READ_WRITE ,__gpio_xicfg_bits);
__IO_REG32_BIT(GPIO_XISTATUS,         0xFFF83078,__READ_WRITE ,__gpio_xistatus_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32(    RTC_INIR,              0xFFF84000,__READ_WRITE );
__IO_REG32_BIT(RTC_AER,               0xFFF84004,__READ_WRITE ,__rtc_aer_bits);
__IO_REG32_BIT(RTC_FCR,               0xFFF84008,__READ_WRITE ,__rtc_fcr_bits);
__IO_REG32_BIT(RTC_TLR,               0xFFF8400C,__READ_WRITE ,__rtc_tlr_bits);
__IO_REG32_BIT(RTC_CLR,               0xFFF84010,__READ_WRITE ,__rtc_clr_bits);
__IO_REG32_BIT(RTC_TSSR,              0xFFF84014,__READ_WRITE ,__rtc_tssr_bits);
__IO_REG32_BIT(RTC_DWR,               0xFFF84018,__READ_WRITE ,__rtc_dwr_bits);
__IO_REG32_BIT(RTC_TAR,               0xFFF8401C,__READ_WRITE ,__rtc_tar_bits);
__IO_REG32_BIT(RTC_CAR,               0xFFF84020,__READ_WRITE ,__rtc_car_bits);
__IO_REG32_BIT(RTC_LIR,               0xFFF84024,__READ       ,__rtc_lir_bits);
__IO_REG32_BIT(RTC_RIER,              0xFFF84028,__READ_WRITE ,__rtc_rier_bits);
__IO_REG32_BIT(RTC_RIIR,              0xFFF8402C,__READ_WRITE ,__rtc_riir_bits);
__IO_REG32_BIT(RTC_TTR,               0xFFF84030,__READ_WRITE ,__rtc_ttr_bits);

/***************************************************************************
 **
 ** SCHI0
 **
 ***************************************************************************/
__IO_REG8(		 SCHI0_RBR,             0xFFF85000,__READ_WRITE );
#define SCHI0_TBR 			SCHI0_RBR
#define SCHI0_BLL 			SCHI0_RBR
__IO_REG32_BIT(SCHI0_IER,             0xFFF85004,__READ_WRITE ,__schi_ier_bits);
#define SCHI0_BLH 			SCHI0_IER
#define SCHI0_BLH_bit 	SCHI0_IER_bit
__IO_REG32_BIT(SCHI0_ISR,             0xFFF85008,__READ_WRITE ,__schi_isr_bits);
#define SCHI0_SCFR 			SCHI0_ISR
#define SCHI0_SCFR_bit	SCHI0_ISR_bit
#define SCHI0_ID				SCHI0_ISR
#define SCHI0_ID_bit		SCHI0_ISR_bit
__IO_REG32_BIT(SCHI0_SCCR,            0xFFF8500C,__READ_WRITE ,__schi_sccr_bits);
__IO_REG8(     SCHI0_CBR,            	0xFFF85010,__READ_WRITE );
__IO_REG32_BIT(SCHI0_SCSR,            0xFFF85014,__READ				,__schi_scsr_bits);
__IO_REG8(		 SCHI0_GTR,            	0xFFF85018,__READ_WRITE );
__IO_REG32_BIT(SCHI0_ECR,            	0xFFF8501C,__READ_WRITE ,__schi_ecr_bits);
__IO_REG32_BIT(SCHI0_TMR,            	0xFFF85020,__READ_WRITE ,__schi_tmr_bits);
__IO_REG32_BIT(SCHI0_TOC,            	0xFFF85028,__READ_WRITE ,__schi_toc_bits);
__IO_REG8(		 SCHI0_TOIR,            0xFFF8502C,__READ_WRITE );
__IO_REG16(		 SCHI0_TOIR1,           0xFFF85030,__READ_WRITE );
__IO_REG32_BIT(SCHI0_TOIR2,           0xFFF85034,__READ_WRITE ,__schi_toir2_bits);
__IO_REG8(		 SCHI0_TOD0,          	0xFFF85038,__READ				);
__IO_REG16(		 SCHI0_TOD1,          	0xFFF8503C,__READ				);
__IO_REG32_BIT(SCHI0_TOD2,          	0xFFF85040,__READ				,__schi_tod2_bits);
__IO_REG32_BIT(SCHI0_BTOR,          	0xFFF85044,__READ_WRITE ,__schi_btor_bits);

/***************************************************************************
 **
 ** SCHI1
 **
 ***************************************************************************/
__IO_REG8(		 SCHI1_RBR,             0xFFF85800,__READ_WRITE );
#define SCHI1_TBR 			SCHI_RBR
#define SCHI1_BLL 			SCHI_RBR
__IO_REG32_BIT(SCHI1_IER,             0xFFF85804,__READ_WRITE ,__schi_ier_bits);
#define SCHI1_BLH 			SCHI1_IER
#define SCHI1_BLH_bit		SCHI1_IER_bit
__IO_REG32_BIT(SCHI1_ISR,             0xFFF85808,__READ_WRITE ,__schi_isr_bits);
#define SCHI1_SCFR 			SCHI_ISR
#define SCHI1_SCFR_bit	SCHI_ISR_bit
#define SCHI1_ID				SCHI_ISR
#define SCHI1_ID_bit		SCHI_ISR_bit
__IO_REG32_BIT(SCHI1_SCCR,            0xFFF8580C,__READ_WRITE ,__schi_sccr_bits);
__IO_REG8(     SCHI1_CBR,            	0xFFF85810,__READ_WRITE );
__IO_REG32_BIT(SCHI1_SCSR,            0xFFF85814,__READ				,__schi_scsr_bits);
__IO_REG8(		 SCHI1_GTR,            	0xFFF85818,__READ_WRITE );
__IO_REG32_BIT(SCHI1_ECR,            	0xFFF8581C,__READ_WRITE ,__schi_ecr_bits);
__IO_REG32_BIT(SCHI1_TMR,            	0xFFF85820,__READ_WRITE ,__schi_tmr_bits);
__IO_REG32_BIT(SCHI1_TOC,            	0xFFF85828,__READ_WRITE ,__schi_toc_bits);
__IO_REG8(		 SCHI1_TOIR0,           0xFFF8582C,__READ_WRITE );
__IO_REG16(		 SCHI1_TOIR1,           0xFFF85830,__READ_WRITE );
__IO_REG32_BIT(SCHI1_TOIR2,           0xFFF85834,__READ_WRITE ,__schi_toir2_bits);
__IO_REG8(		 SCHI1_TOD0,          	0xFFF85838,__READ				);
__IO_REG16(		 SCHI1_TOD1,          	0xFFF8583C,__READ				);
__IO_REG32_BIT(SCHI1_TOD2,          	0xFFF85840,__READ				,__schi_tod2_bits);
__IO_REG32_BIT(SCHI1_BTOR,          	0xFFF85844,__READ_WRITE ,__schi_btor_bits);

/***************************************************************************
 **
 ** I2C0
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C_CSR0,              0xFFF86000,__READ_WRITE ,__i2c_csr_bits);
__IO_REG32_BIT(I2C_DIVIDER0,          0xFFF86004,__READ_WRITE ,__i2c_divider_bits);
__IO_REG32_BIT(I2C_CMDR0,             0xFFF86008,__READ_WRITE ,__i2c_cmdr_bits);
__IO_REG32_BIT(I2C_SWR0,              0xFFF8600C,__READ_WRITE ,__i2c_swr_bits);
__IO_REG8(     I2C_RXR0,              0xFFF86010,__READ       );
__IO_REG32(    I2C_TXR0,              0xFFF86014,__READ_WRITE );

/***************************************************************************
 **
 ** I2C1
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C_CSR1,              0xFFF86100,__READ_WRITE ,__i2c_csr_bits);
__IO_REG32_BIT(I2C_DIVIDER1,          0xFFF86104,__READ_WRITE ,__i2c_divider_bits);
__IO_REG32_BIT(I2C_CMDR1,             0xFFF86108,__READ_WRITE ,__i2c_cmdr_bits);
__IO_REG32_BIT(I2C_SWR1,              0xFFF8610C,__READ_WRITE ,__i2c_swr_bits);
__IO_REG8(     I2C_RXR1,              0xFFF86110,__READ       );
__IO_REG32(    I2C_TXR1,              0xFFF86114,__READ_WRITE );

/***************************************************************************
 **
 ** USI
 **
 ***************************************************************************/
__IO_REG32_BIT(USI_CNTRL,             0xFFF86200,__READ_WRITE ,__usi_cntrl_bits);
__IO_REG32_BIT(USI_DIVIDER,           0xFFF86204,__READ_WRITE ,__usi_divider_bits);
__IO_REG32_BIT(USI_SSR,               0xFFF86208,__READ_WRITE ,__usi_ssr_bits);
__IO_REG32(    USI_RX0,               0xFFF86210,__READ_WRITE );
__IO_REG32(    USI_RX1,               0xFFF86214,__READ_WRITE );
__IO_REG32(    USI_RX2,               0xFFF86218,__READ_WRITE );
__IO_REG32(    USI_RX3,               0xFFF8621C,__READ_WRITE );

#define USI_TX0 USI_RX0
#define USI_TX1 USI_RX1
#define USI_TX2 USI_RX2
#define USI_TX3 USI_RX3

/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(PWM_PPR,               0xFFF87000,__READ_WRITE ,__pwm_ppr_bits);
__IO_REG32_BIT(PWM_CSR,               0xFFF87004,__READ_WRITE ,__pwm_csr_bits);
__IO_REG32_BIT(PWM_PCR,               0xFFF87008,__READ_WRITE ,__pwm_pcr_bits);
__IO_REG32_BIT(PWM_CNR0,              0xFFF8700C,__READ_WRITE ,__pwm_cnr_bits);
__IO_REG32_BIT(PWM_CMR0,              0xFFF87010,__READ_WRITE ,__pwm_cmr_bits);
__IO_REG32_BIT(PWM_PDR0,              0xFFF87014,__READ       ,__pwm_pdr_bits);
__IO_REG32_BIT(PWM_CNR1,              0xFFF87018,__READ_WRITE ,__pwm_cnr_bits);
__IO_REG32_BIT(PWM_CMR1,              0xFFF8701C,__READ_WRITE ,__pwm_cmr_bits);
__IO_REG32_BIT(PWM_PDR1,              0xFFF87020,__READ       ,__pwm_pdr_bits);
__IO_REG32_BIT(PWM_CNR2,              0xFFF87024,__READ_WRITE ,__pwm_cnr_bits);
__IO_REG32_BIT(PWM_CMR2,              0xFFF87028,__READ_WRITE ,__pwm_cmr_bits);
__IO_REG32_BIT(PWM_PDR2,              0xFFF8702C,__READ       ,__pwm_pdr_bits);
__IO_REG32_BIT(PWM_CNR3,              0xFFF87030,__READ_WRITE ,__pwm_cnr_bits);
__IO_REG32_BIT(PWM_CMR3,              0xFFF87034,__READ_WRITE ,__pwm_cmr_bits);
__IO_REG32_BIT(PWM_PDR3,              0xFFF87038,__READ       ,__pwm_pdr_bits);
__IO_REG32_BIT(PWM_PIER,              0xFFF8703C,__READ_WRITE ,__pwm_pier_bits);
__IO_REG32_BIT(PWM_PIIR,              0xFFF87040,__READ_WRITE ,__pwm_piir_bits);

/***************************************************************************
 **
 ** KPI
 **
 ***************************************************************************/
__IO_REG32_BIT(KPICONF,               0xFFF88000,__READ_WRITE ,__kpiconf_bits);
__IO_REG32_BIT(KPI3KCONF,             0xFFF88004,__READ_WRITE ,__kpi3kconf_bits);
__IO_REG32_BIT(KPILPCONF,             0xFFF88008,__READ_WRITE ,__kpilpconf_bits);
__IO_REG32_BIT(KPISTATUS,             0xFFF8800C,__READ       ,__kpistatus_bits);

/***************************************************************************
 **
 ** PS2
 **
 ***************************************************************************/
__IO_REG32_BIT(PS2CMD,                0xFFF89000,__READ_WRITE ,__ps2cmd_bits);
__IO_REG32_BIT(PS2STS,                0xFFF89004,__READ_WRITE ,__ps2sts_bits);
__IO_REG32_BIT(PS2SCANCODE,           0xFFF89008,__READ       ,__ps2scancode_bits);
__IO_REG8(     PS2ASCII,              0xFFF8900C,__READ       );

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
#define AIC_NIRQ2        4  /* External Interrupt 2                        */
#define AIC_NIRQ3        5  /* External Interrupt 3                        */
#define AIC_AC97         6  /* AC97 Interrupt                              */
#define AIC_LCD          7  /* LCD Interrupt                               */
#define AIC_RTC          8  /* RTC Interrupt                               */
#define AIC_UART0        9  /* UART Interrupt0                             */
#define AIC_UART1       10  /* UART Interrupt1                             */
#define AIC_UART2       11  /* UART Interrupt2                             */
#define AIC_UART3       12  /* UART Interrupt3                             */
#define AIC_TIMER0      13  /* Timer Interrupt 0                           */
#define AIC_TIMER1      14  /* Timer Interrupt 1                           */
#define AIC_USBH0       15  /* USB Host Interrupt 0                        */
#define AIC_USBH1       16  /* USB Host Interrupt 1                        */
#define AIC_EMCTX       17  /* EMC TX Interrupt                            */
#define AIC_EMCRX       18  /* EMC RX Interrupt                            */
#define AIC_GDMA0       19  /* GDMA Channel Interrupt 0                    */
#define AIC_GDMA1       20  /* GDMA Channel Interrupt 1                    */
#define AIC_SDIO        21  /* SDIO Interrupt                              */
#define AIC_USBD        22  /* USB Device Interrupt                        */
#define AIC_SC0         23  /* Smart Card Interrupt 0                      */
#define AIC_SC1         24  /* Smart Card Interrupt 1                      */
#define AIC_I2C0        25  /* I2C Interrupt 0                             */
#define AIC_I2C1        26  /* I2C Interrupt 1                             */
#define AIC_USI         27  /* USI Interrupt                               */
#define AIC_PWM         28  /* PWM Timer interrupt                         */
#define AIC_KPI         29  /* Keypad Interrupt                            */
#define AIC_PS2         30  /* PS2 Interrupt                               */
#define AIC_NIRQ4_5     31  /* GPIO0 & GPIO70 Interrupt                    */

#endif    /* __W91N710_H */
