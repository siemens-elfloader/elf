/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    LPC2888
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.2.2.4 $
 **
 **    Note: Only little endian addressing of registers.
 ***************************************************************************/

#ifndef __IOLPC2888_H
#define __IOLPC2888_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   LPC2888 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/


/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#if __LITTLE_ENDIAN__ == 0
#error This file should only be compiled in little endian mode
#endif

/* Boot Map register (SYS_BOOTMAP - 0x8000 5070) */
typedef struct{
__REG32 MAP   :1;
__REG32       :31;
} __sys_bootmap_bits;

/* Cache Reset Status register (CACHE_RST_STAT, 0x8010 4000) */
typedef struct{
__REG32 CACHE_STATUS :1;
__REG32              :31;
} __cache_rst_stat_bits;

/* Cache Settings register (CACHE_SETTINGS, 0x8010 4004) */
typedef struct{
__REG32 CACHE_RST          :1;
__REG32 DATA_ENABLE        :1;
__REG32 INSTRUCTION_ENABLE :1;
__REG32 PERF_ANAL_RST      :1;
__REG32 PERF_ANAL_ENA      :1;
__REG32                    :27;
} __cache_settings_bits;

/* Cache Page Enable Control register (CACHE_PAGE_CTRL,0x8010 4008) */
typedef struct{
__REG32 PAGE_0_ENA  :1;
__REG32 PAGE_1_ENA  :1;
__REG32 PAGE_2_ENA  :1;
__REG32 PAGE_3_ENA  :1;
__REG32 PAGE_4_ENA  :1;
__REG32 PAGE_5_ENA  :1;
__REG32 PAGE_6_ENA  :1;
__REG32 PAGE_7_ENA  :1;
__REG32 PAGE_8_ENA  :1;
__REG32 PAGE_9_ENA  :1;
__REG32 PAGE_10_ENA :1;
__REG32 PAGE_11_ENA :1;
__REG32 PAGE_12_ENA :1;
__REG32 PAGE_13_ENA :1;
__REG32 PAGE_14_ENA :1;
__REG32 PAGE_15_ENA :1;
__REG32             :16;
} __cache_page_ctrl_bits;

/* Address Pointer for Page(n) registers (ADDRESS_PAGE_(n),0x8010 4018) */
typedef struct{
__REG32 UPPR_ADDR :11;
__REG32           :21;
} __address_page_n_bits;

/* CPU Clock Gate control (CPU_CLK_GATE, 0x8010 4058) */
typedef struct{
__REG32 CPU_CLK_GATE :1;
__REG32              :31;
} __cpu_clk_gate_bits;

/* Flash Control register (F_CTRL-0x8010 2000) */
typedef struct{
__REG32 FC_CS       :1;
__REG32 FC_FUNC     :1;
__REG32 FC_WEN      :1;
__REG32             :2;
__REG32 FC_RD_LATCH :1;
__REG32             :1;
__REG32 FC_PROTECT  :1;
__REG32             :2;
__REG32 FC_SET_DATA :1;
__REG32 FC_RSSL     :1;
__REG32 FC_PROG_REQ :1;
__REG32             :1;
__REG32 FC_CLR_BUF  :1;
__REG32 FC_LOAD_REQ :1;
__REG32             :16;
} __f_ctrl_bits;

/* Flash Status register (F_STAT - 0x8010 2004) */
typedef struct{
__REG32 FS_DONE     :1;
__REG32 FS_PROGGNT  :1;
__REG32 FS_RDY      :1;
__REG32             :2;
__REG32 FS_ERR      :1;
__REG32             :26;
} __f_stat_bits;

/* Flash Program Time register (F_PROG_TIME - 0x8010 2008) */
typedef struct{
__REG32 FPT_TIME    :15;
__REG32 FPT_ENABLE  :1;
__REG32             :16;
} __f_prog_time_bits;

/* Flash Wait States register (F_WAIT - 0x8010 2010) */
typedef struct{
__REG32 WAIT_STATES :8;
__REG32             :24;
} __f_wait_bits;

/* Flash Clock Divider register (F_CLK_TIME - 0x8010 201C) */
typedef struct{
__REG32 CLK_DIV :12;
__REG32         :20;
} __f_clk_time_bits;

/* Flash Interrupt Status register (F_INT_STAT - 0x8010 2FE0) */
typedef struct{
__REG32 END_OF_ERASE    :1;
__REG32 END_OF_PROGRAM  :1;
__REG32                 :30;
} __f_int_stat_bits;

/* Flash Interrupt Set register (F_INT_SET - 0x8010 2FEC) */
typedef struct{
__REG32 SET_INT :2;
__REG32         :30;
} __f_int_set_bits;

/* Flash Interrupt Clear register (F_INT_CLR - 0x8010 2FE8) */
typedef struct{
__REG32 CLR_INT :2;
__REG32         :30;
} __f_int_clr_bits;

/* Flash Interrupt Enable register (F_INTEN - 0x8010 2FE4) */
typedef struct{
__REG32 EOE_ENABLE  :1;
__REG32 EOP_ENABLE  :1;
__REG32             :30;
} __f_inten_bits;


/* Flash Interrupt Enable Set register (F_INTEN_SET - 0x8010 2FDC) */
typedef struct{
__REG32 SET_ENABLE  :2;
__REG32             :30;
} __f_inten_set_bits;

/* Flash Interrupt Enable Clear register (F_INTEN_CLR - 0x8010 2FD8) */
typedef struct{
__REG32 CLR_ENABLE :2;
__REG32            :30;
} __f_inten_clr_bits;

/* Flash Power Down register (FLASH_PD - 0x8000 5030) */
typedef struct{
__REG32 FLASH_PD :1;
__REG32          :31;
} __flash_pd_bits;

/* Flash Initialization register (FLASH_INIT - 0x8000 5034) */
typedef struct{
__REG32 FLASH_INIT :1;
__REG32            :31;
} __flash_init_bits;

/* DCDC converter 1 Adjustment register (DCDCADJUST1 - address 0x8000 5004) */
typedef struct{
__REG32 DCDCADJUST1 :3;
__REG32             :29;
} __dcdcadjust1_bits;

/* DCDC converter 2 Adjustment register (DCDCADJUST2 - address 0x8000 5008) */
typedef struct{
__REG32 DCDCADJUST2 :3;
__REG32             :29;
} __dcdcadjust2_bits;

/* DCDC Clock Select register (DCDCCLKSEL - address 0x8000 500C) */
typedef struct{
__REG32 DCDCCLKSEL  :1;
__REG32             :31;
} __dcdcclksel_bits;

/* Power Mode Register (PMODE-0x8000 4C00) */
typedef struct{
__REG32 CGUMODE :2;
__REG32         :30;
} __pmode_bits;

/* WatchDog Bark Register (WDBARK - 0x8000 4C04) */
typedef struct{
__REG32 BARK :1;
__REG32      :31;
} __wdbark_bits;

/* 32 kHz Oscillator Control (OSC32EN - 0x8000 4C08) */
typedef struct{
__REG32 RUN :1;
__REG32     :31;
} __osc32en_bits;

/* Main Oscillator Control (OSCEN - 0x8000 4C10) */
typedef struct{
__REG32 RUN :1;
__REG32     :31;
} __oscen_bits;

/* Input Select Register (HPFIN - 0x8000 00AC) */
typedef struct{
__REG32 HPSELECT  :4;
__REG32           :28;
} __hpfin_bits;

/* Initial Divider Control Register (HPNDEC - 0x8000 00B4) */
typedef struct{
__REG32 NDEC :10;
__REG32      :22;
} __hpndec_bits;

/* Multiplier Control Register (HPMDEC - 0x8000 00B0) */
typedef struct{
__REG32 MDEC :17;
__REG32      :15;
} __hpmdec_bits;

/* Final Divider Control Register (HPPDEC - 0x8000 00B8) */
typedef struct{
__REG32 PDEC :7;
__REG32      :25;
} __hppdec_bits;

/* Mode Register (HPMODE - 0x8000 00BC) */
typedef struct{
__REG32 HPCLKEN :1;
__REG32         :1;
__REG32 HPPD    :1;
__REG32         :1;
__REG32 DIRECTI :1;
__REG32 FREERUN :1;
__REG32         :26;
} __hpmode_bits;

/* Status Register (HPSTAT - 0x8000 00C0) */
typedef struct{
__REG32 HPLOCK  :1;
__REG32 HPFREE  :1;
__REG32         :30;
} __hpstat_bits;

/* Rate Change Request Register (HPREQ - 0x8000 00C8) */
typedef struct{
__REG32 HPMREQ :1;
__REG32 HPNREQ :1;
__REG32 HPPREQ :1;
__REG32        :29;
} __hpreq_bits;

/* Rate Change Acknowledge Register (HPACK - 0x8000 00C4) */
typedef struct{
__REG32 HPMACK :1;
__REG32 HPNACK :1;
__REG32 HPPACK :1;
__REG32        :29;
} __hpack_bits;

/* R Bandwidth Register (HPSELR - 0x8000 00D8) */
typedef struct{
__REG32 SELR :4;
__REG32      :28;
} __hpselr_bits;

/* I Bandwidth Register (HPSELI - 0x8000 00DC) */
typedef struct{
__REG32 SELI :4;
__REG32      :28;
} __hpseli_bits;

/* P Bandwidth Register (HPSELP - 0x8000 00E0) */
typedef struct{
__REG32 SELP :5;
__REG32      :27;
} __hpselp_bits;

/* Switch Configuration Registers (SYSSCR-DAISCR; 0x8000 4000-4024) */
typedef struct{
__REG32 ENF1   :1;
__REG32 ENF2   :1;
__REG32 SCRES  :1;
__REG32 SCSTOP :1;
__REG32        :28;
} __sysscr_daiscr_bits;

/* Frequency Select 1 Registers (SYSFSR1-DAIFSR1; 0x8000 402C-4050) */
typedef struct{
__REG32 SELECT :4;
__REG32        :28;
} __sysfsr1_daifsr1_bits;

/* Switch Status Registers (SYSSSR-DAISSR; 0x8000 4084-40A8) */
typedef struct{
__REG32 ENF1    :1;
__REG32 ENF2    :1;
__REG32 SELECT  :4;
__REG32         :26;
} __sysssr_daissr_bits;

/* Base Control Registers (SYSBCR-DAIOBCR; 0x8000 43F0-43F8) */
typedef struct{
__REG32 FDRUN :1;
__REG32       :31;
} __sysbcr_daiobcr_bits;

/* Fractional divider configuration registers */
typedef struct{
__REG32 FDRUN   :1;
__REG32 FDRES   :1;
__REG32 FDSTRCH :1;
__REG32 MADD    :8;
__REG32 MSUB    :8;
__REG32         :13;
} __sysfdcr_bits;

/* Fractional divider configuration registers */
typedef struct{
__REG32 FDRUN   :1;
__REG32 FDRES   :1;
__REG32 FDSTRCH :1;
__REG32 MADD    :10;
__REG32 MSUB    :10;
__REG32         :9;
} __daiofdcr4_bits;

/* Power control register bit descriptions */
typedef struct{
__REG32 PCRUN     :1;
__REG32 PCAUTO    :1;
__REG32 WAKE_EN   :1;
__REG32 EXTEN_EN  :1;
__REG32 ENOUT_EN  :1;
__REG32           :27;
} __power_control_bits;

/* Power status register bit descriptions */
typedef struct{
__REG32 PSACTIVE :1;
__REG32 PSWAKE   :1;
__REG32          :30;
} __power_status_bits;

/* Enable select registers with 1 bit fields */
typedef struct{
__REG32 ESR_EN  :1;
__REG32 ESR_SEL :1;
__REG32         :30;
} __enable_select1_bits;

/* Enable select registers with 3 bit fields */
typedef struct{
__REG32 ESR_EN  :1;
__REG32 ESR_SEL :3;
__REG32         :28;
} __enable_select3_bits;

/* Enable select registers with none bit field */
typedef struct{
__REG32 ESR_EN :1;
__REG32        :31;
} __enable_select_none_bits;

/* EMC Control Register (EMCControl - address 0x8000 8000) */
typedef struct{
__REG32 MPMC      :1;
__REG32 AM        :1;
__REG32 LPM       :1;
__REG32           :29;
} __emccontrol_bits;

/* EMC Status Register (EMCStatus - address 0x8000 8004) */
typedef struct{
__REG32 BUSY  :1;
__REG32 WBS   :1;
__REG32 SRACK :1;
__REG32       :29;
} __emcstatus_bits;

/* EMC Configuration Register (EMCConfig - address 0x8000 8008) */
typedef struct{
__REG32 BIGENDIAN  :1;
__REG32            :7;
__REG32 CLKOUTDIV2 :1;
__REG32            :23;
} __emcconfig_bits;

/* Dynamic Control Register (EMCDynamicControl - address 0x8000 8020) */
typedef struct{
__REG32 FORCE_CKE    :1;
__REG32 FORCE_CLKOUT :1;
__REG32 SRREQ        :1;
__REG32              :2;
__REG32 MMC          :1;
__REG32              :1;
__REG32 SDRAMINI     :2;
__REG32              :4;
__REG32 DP           :1;
__REG32 RPOUT        :2;
__REG32              :16;
} __emcdynamiccontrol_bits;

/* Dynamic Memory Refresh Timer Register (EMCDynamicRefresh - 0x8000 8024) */
typedef struct{
__REG32 REFRESH :11;
__REG32         :21;
} __emcdynamicrefresh_bits;

/* Dynamic Memory Read Configuration Register (EMCDynamicReadConfig -
 * address 0x8000 8028) */
typedef struct{
__REG32 RDS :2;
__REG32     :30;
} __emcdynamicreadconfig_bits;

/* Dynamic Memory Percentage Command Period Register (EMCDynamictRP -
 * address 0x8000 8030) */
typedef struct{
__REG32 TRP :4;
__REG32     :28;
} __emcdynamicrp_bits;

/* Dynamic Memory Active to Precharge Command Period Register
(EMCDynamictRAS - address 0x8000 8034) */
typedef struct{
__REG32 TRAS :4;
__REG32      :28;
} __emcdynamicras_bits;

/* Dynamic Memory Self-refresh Exit Time Register (EMCDynamictSREX -
 * address 0x8000 8038) */
typedef struct{
__REG32 TSREX :4;
__REG32       :28;
} __emcdynamicsrex_bits;

/* Memory Last Data Out to Active Time Register (EMCDynamictAPR -
 * address 0x8000 803C) */
typedef struct{
__REG32 TAPR :4;
__REG32      :28;
} __emcdynamicapr_bits;

/* Dynamic Memory Data-in to Active Command Time Register (EMCDynamictDAL -
 * address 0x8000 8040) */
typedef struct{
__REG32 TDAL :4;
__REG32      :28;
} __emcdynamicdal_bits;

/* Dynamic Memory Write recover Time Register (EMCDynamictWR -
 * address 0x8000 8044) */
typedef struct{
__REG32 TWR :4;
__REG32     :28;
} __emcdynamicwr_bits;

/* Dynamic Memory Active to Active Command Period Register (EMCDynamictRC -
 * address 0x8000 8048) */
typedef struct{
__REG32 TRC :5;
__REG32     :27;
} __emcdynamicrc_bits;

/* Dynamic Memory Auto-refresh Period Register (EMCDynamictRFC -
 * address 0x8000 804C) */
typedef struct{
__REG32 TRFC :5;
__REG32      :27;
} __emcdynamicrfc_bits;

/* Dynamic Memory Exit Self-refresh Register (EMCDynamictXSR -
 * address 0x8000 8050) */
typedef struct{
__REG32 TXSR :5;
__REG32      :27;
} __emcdynamicxsr_bits;

/* Dynamic Memory Active Bank A to Active Bank B Time Register(EMCDynamictRRD -
 * address 0x8000 8054) */
typedef struct{
__REG32 TRRD :4;
__REG32      :28;
} __emcdynamicrrd_bits;

/* Dynamic Memory Load Mode Register to Active Command Time(EMCDynamictMRD -
 * address 0x8000 8058) */
typedef struct{
__REG32 TMRD :4;
__REG32      :28;
} __emcdynamicmrd_bits;

/* Dynamic Memory Configuration Register (EMCDynamicConfig -
 * address 0x8000 8100) */
typedef struct{
__REG32           :3;
__REG32 MD        :2;
__REG32           :2;
__REG32 ADDR_MAP1 :6;
__REG32           :1;
__REG32 ADDR_MAP2 :1;
__REG32           :4;
__REG32 BUF_EN    :1;
__REG32 WP        :1;
__REG32           :11;
} __emcdynamicconfig_bits;

/* Dynamic Memory RAS/CAS Delay Register (EMCDynamicRasCas - 0x8000 8104) */
typedef struct{
__REG32 RAS :2;
__REG32     :6;
__REG32 CAS :2;
__REG32     :22;
} __emcdynamicrascas_bits;

/* Static Memory Configuration Registers (EMCStaticConfig0-2 -
   addresses 0x8000 8200, 0x8000 8220, 0x8000 8240) */
typedef struct{
__REG32 MW   :2;
__REG32      :1;
__REG32 PM   :1;
__REG32      :2;
__REG32 CSP  :1;
__REG32 BLS  :1;
__REG32 EXTW :1;
__REG32      :10;
__REG32 WBEN :1;
__REG32 WP   :1;
__REG32      :11;
} __emcstaticconfig0_bits;

/* Static Memory Write Enable Delay registers (EMCStaticWaitWen0-2 - addresses
0x8000 8204,0x8000 8224, 0x8000 8244) */
typedef struct{
__REG32 WAITWEN :4;
__REG32         :28;
} __emcstaticwaitwen0_bits;

/* Static Memory Output Enable Delay Registers (EMCStaticWaitOen0-2 - addresses
0x8000 8208, 0x8000 8228, 0x8000 8248) */
typedef struct{
__REG32 WAITOEN :4;
__REG32         :28;
} __emcstaticwaitoen0_bits;

/* Static Memory Read Delay Registers (EMCStaticWaitRd0-2 - addresses
0x8000 820C, 0x8000 822C, 0x8000 824C) */
typedef struct{
__REG32 WAITRD :5;
__REG32        :27;
} __emcstaticwaitrd0_bits;

/* Static Memory Page Mode Read Delay Registers 0-2 (EMCStaticWaitPage0-2 -
addresses 0x8000 8210, 0x8000 8230, 0x8000 8250) */
typedef struct{
__REG32 WAITPAGE :5;
__REG32          :27;
} __emcstaticwaitpage0_bits;

/* Static Memory Write Delay Registers 0-2 (EMCStaticWaitWr0-2 - addresses
0x8000 8214, 0x8000 8234, 0x8000 8254) */
typedef struct{
__REG32 WAITWR :5;
__REG32        :27;
} __emcstaticwaitwr0_bits;

/* Static Memory Turnaound Delay Registers 0-2 (EMCStaticWaitTurn0-2 - addresses
0x8000 8218, 0x8000 8238, 0x8000 8258) */
typedef struct{
__REG32 WAITTURN :4;
__REG32          :28;
} __emcstaticwaitturn0_bits;

/* Static Memory Extended Wait Register (EMCStaticExtendedWait - address
0x8000 8080) */
typedef struct{
__REG32 EXTENDEDWAIT :10;
__REG32              :22;
} __emcstaticextendedwait_bits;

/* EMC Miscellaneous Control Register (EMCMisc - address 0x8000 505C) */
typedef struct{
__REG32 SREFREQ     :1;
__REG32             :7;
__REG32 REL1CONFIG  :1;
__REG32             :23;
} __emcmisc_bits;

/* Interrupt Request Registers (INT_REQ1:19, 0x8030 0404 - 0x8030 0474) */
typedef struct{
__REG32 PRIO      :4;
__REG32           :4;
__REG32 TARGET    :1;
__REG32           :7;
__REG32 INTEN     :1;
__REG32 ACTVLO    :1;
__REG32           :7;
__REG32 WE_ACTVLO :1;
__REG32 WE_ENABLE :1;
__REG32 WE_TARGET :1;
__REG32 WE_PRIO   :1;
__REG32 CLR_SWINT :1;
__REG32 SET_SWINT :1;
__REG32 PENDING   :1;
} __int_req_bits;

/* Interrupt Pending Register (INT_PENDING - 0x8030 0200) */
typedef struct{
__REG32         :1;
__REG32 IRQ0    :1;
__REG32 IRQ1    :1;
__REG32 IRQ2    :1;
__REG32 IRQ3    :1;
__REG32 TIMER0  :1;
__REG32 TIMER1  :1;
__REG32 RTC     :1;
__REG32 ALARM   :1;
__REG32 ADC     :1;
__REG32 MCI0    :1;
__REG32 MCI1    :1;
__REG32 UART    :1;
__REG32 I2C     :1;
__REG32         :1;
__REG32         :1;
__REG32 SAI1    :1;
__REG32         :1;
__REG32         :1;
__REG32 SAI4    :1;
__REG32 SAO1    :1;
__REG32 SAO2    :1;
__REG32         :1;
__REG32 FLASHP  :1;
__REG32 LCD     :1;
__REG32 GPDMA   :1;
__REG32 USB0    :1;
__REG32 USB1    :1;
__REG32 USB2    :1;
__REG32 USB3    :1;
__REG32         :2;
} __int_pending_bits;

/* Vector Registers (INT_VECTOR0:1, 0x8030 0100 - 0x8030 0104) */
typedef struct{
__REG32             :3;
__REG32 INDEX       :5;
__REG32             :3;
__REG32 TABLE_ADDR  :21;
} __int_vector0_bits;

/* Priority Mask Registers (INT_PRIOMASK0:1, 0x8030 0000 - 0x8030 0004) */
typedef struct{
__REG32 PL  :4;
__REG32     :28;
} __int_priomask0_bits;

/* Features Register (INT_FEATURES - 0x8030 0300) */
typedef struct{
__REG32 SOURCES :8;
__REG32 PL      :8;
__REG32 TARGETS :6;
__REG32         :10;
} __int_features_bits;

/* Control registers (T0CTRL, T1CTRL - 0x8002 0008, 0x8002 0408) */
typedef struct{
__REG32           :2;
__REG32 PRESCALE  :2;
__REG32           :2;
__REG32 TMODE     :1;
__REG32 TENAB     :1;
__REG32           :24;
} __t0ctrl_bits;

/* Watchdog Status Register (WDT_SR - 0x8000 2800) */
typedef struct{
__REG32 MR0 :1;
__REG32 MR1 :1;
__REG32     :30;
} __wdt_sr_bits;

/* Watchdog Timer Control Register (WDT_TCR - 0x8000 2804) */
typedef struct{
__REG32 CE :1;
__REG32 CR :1;
__REG32    :30;
} __wdt_tcr_bits;

/* Watchdog Match Control Register (WDT_MCR - 0x8000 2814) */
typedef struct{
__REG32 E_MR0 :1;
__REG32 R_MR0 :1;
__REG32 S_MR0 :1;
__REG32 E_MR1 :1;
__REG32 R_MR1 :1;
__REG32 S_MR1 :1;
__REG32       :26;
} __wdt_mcr_bits;

/* Watchdog External Match Register (WDT_EMR - 0x8000 283C) */
typedef struct{
__REG32 M0  :1;
__REG32     :3;
__REG32 EI  :2;
__REG32     :1;
__REG32 ER  :1;
__REG32     :24;
} __wdt_emr_bits;

/* RTC Configuration Register (RTC_CFG - 0x8000 5024) */
typedef struct{
__REG32 PWR_UP :1;
__REG32        :31;
} __rtc_cfg_bits;

/* Interrupt Location Register (ILR - address 0x8000 2000) */
typedef struct{
__REG32 RTCCIF :1;
__REG32 RTCALF :1;
__REG32        :30;
} __ilr_bits;

/* Clock Tick Counter Register (CTCR - address 0x8000 2004) */
typedef struct{
__REG32 CTC :15;
__REG32     :17;
} __ctc_bits;

/* Clock Control Register (CCR - address 0x8000 2008) */
typedef struct{
__REG32 CLKEN   :1;
__REG32 CTCRST  :1;
__REG32 CTTEST  :2;
__REG32         :28;
} __ccr_bits;

/* Counter Increment Interrupt Register (CIIR - address 0x8000 200C) */
typedef struct{
__REG32 IMSEC   :1;
__REG32 IMMIN   :1;
__REG32 IMHOUR  :1;
__REG32 IMDOM   :1;
__REG32 IMDOW   :1;
__REG32 IMDOY   :1;
__REG32 IMMON   :1;
__REG32 IMYEAR  :1;
__REG32         :24;
} __ciir_bits;

/* Alarm Mask Register (AMR - address 0x8000 2010) */
typedef struct{
__REG32 AMRSEC  :1;
__REG32 AMRMIN  :1;
__REG32 AMRHOUR :1;
__REG32 AMRDOM  :1;
__REG32 AMRDOW  :1;
__REG32 AMRDOY  :1;
__REG32 AMRMON  :1;
__REG32 AMRYEAR :1;
__REG32         :24;
} __amr_bits;

/* Consolidated Time register 0 (CTIME0 - address 0x8000 2014) */
typedef struct{
__REG32 SECONDS :6;
__REG32         :2;
__REG32 MINUTES :6;
__REG32         :2;
__REG32 HOURS   :5;
__REG32         :3;
__REG32 DOW     :3;
__REG32         :5;
} __ctime0_bits;

/* Consolidated Time register 1 (CTIME1 - address 0x8000 2018) */
typedef struct{
__REG32 DOM   :5;
__REG32       :3;
__REG32 MONTH :4;
__REG32       :4;
__REG32 YEAR  :12;
__REG32       :4;
} __ctime1_bits;

/* Consolidated Time register 2 (CTIME2 - address 0x8000 201C) */
typedef struct{
__REG32 DOY :12;
__REG32     :20;
} __ctime2_bits;

/* RTC second register */
typedef struct{
__REG32 SEC  : 6;
__REG32      :26;
} __sec_bits;

/* RTC minute register */
typedef struct{
__REG32 MIN  : 6;
__REG32      :26;
} __min_bits;

/* RTC hour register */
typedef struct{
__REG32 HOUR  : 5;
__REG32       :27;
} __hour_bits;

/* RTC day of month register */
typedef struct{
__REG32 DOM  : 5;
__REG32      :27;
} __dom_bits;

/* RTC day of week register */
typedef struct{
__REG32 DOW  : 3;
__REG32      :29;
} __dow_bits;

/* RTC day of year register */
typedef struct{
__REG32 DOY  : 9;
__REG32      :23;
} __doy_bits;

/* RTC month register */
typedef struct{
__REG32 MON  : 4;
__REG32      :28;
} __month_bits;

/* RTC year register */
typedef struct{
__REG32 YEAR  :12;
__REG32       :20;
} __year_bits;

/* Interrupt Enable Register (IER - 0x8010 1004 when DLAB=0) */

typedef union {
  // IER
  struct{
__REG32 RDAINTEN  :1;
__REG32 THREINTEN :1;
__REG32 RLSINTEN  :1;
__REG32 MSINTEN   :1;
__REG32           :3;
__REG32 CTSINTEN  :1;
__REG32 ABEOINTEN :1;
__REG32 ABTOINTEN :1;
__REG32           :22;
  };
  // DLM
  struct{
__REG32 _DLM :8;
__REG32     :24;
  };
} __ier_bits;

/* Interrupt Identification Register (IIR - 0x8010 1008, read only) */
typedef union{
  /*IIR*/
  struct{
__REG32 IS      :1;
__REG32 II      :3;
__REG32         :2;
__REG32 FE      :2;
__REG32 ABEOINT :1;
__REG32 ABTOINT :1;
__REG32         :22;
  };
/*FCR*/
  struct{
__REG32 FE2     :1;
__REG32 RXFR    :1;
__REG32 TXFR    :1;
__REG32 DMAMODE :1;
__REG32         :2;
__REG32 RXTL    :2;
__REG32         :24;
  };
} __iir_bits;

/* Line Control Register (LCR - 0x8010 100C) */
typedef struct{
__REG32 WLS   :2;
__REG32 SBS   :1;
__REG32 PE    :1;
__REG32 PS    :2;
__REG32 BC    :1;
__REG32 DLAB  :1;
__REG32       :24;
} __lcr_bits;

/* Modem Control Register (MCR - address 0x8010 1010) */
typedef struct{
__REG32         :1;
__REG32 RTS     :1;
__REG32         :2;
__REG32 LBMS    :1;
__REG32         :1;
__REG32 AUTORTS :1;
__REG32 AUTOCTS :1;
__REG32         :24;
} __mcr_bits;

/* Line Status Register (LSR - 0x8010 1014, read only) */
typedef struct{
__REG32 RDR   :1;
__REG32 OE    :1;
__REG32 PE    :1;
__REG32 FE    :1;
__REG32 BI    :1;
__REG32 THRE  :1;
__REG32 TEMP  :1;
__REG32 RXFE  :1;
__REG32       :24;
} __lsr_bits;

/* Modem Status Register (MSR - 0x8010 1018, Read Only) */
typedef struct{
__REG32 DTCS :1;
__REG32      :3;
__REG32 CTS  :1;
__REG32      :27;
} __msr_bits;

/* Scratch Pad Register (SCR - 0x8010 101C) */
typedef struct{
__REG32 PAD :8;
__REG32     :24;
} __scr_bits;

/* Auto-baud Control Register (ACR - 0x8010 1020) */
typedef struct{
__REG32 ACR_START   :1;
__REG32 ACR_MODE    :1;
__REG32 AUTORESTART :1;
__REG32             :6;
__REG32 ABEOINTCLR  :1;
__REG32 ABTOINTCLR  :1;
__REG32             :21;
} __acr_bits;

/* IrDA Control Register (ICR - 0x8010 1024) */
typedef struct{
__REG32 IRDAEN      :1;
__REG32 IRDAINV     :1;
__REG32 FIXPULSEEN  :1;
__REG32 PULSEDIV    :3;
__REG32             :26;
} __icr_bits;

/* Fractional Divider Register (FDR - 0x8010 1028) */
typedef struct{
__REG32 DIVADDVAL :4;
__REG32 MULVAL    :4;
__REG32           :24;
} __fdr_bits;

/* NHP Mode Register (MODE - 0x8010 1034) */
typedef struct{
__REG32 NHP :1;
__REG32     :31;
} __mode_bits;

/* NHP Pop Register (POP - 0x8010 1030) */
typedef struct{
__REG32 POP :1;
__REG32     :31;
} __pop_bits;

/* Interrupt Status Register (INTS - 0x8010 1FE0) */
typedef struct{
__REG32 DCTSINT   :1;
__REG32           :3;
__REG32 THREINT   :1;
__REG32 RXTOINT   :1;
__REG32 RXDAINT   :1;
__REG32 WAKEUPINT :1;
__REG32 ABEOINT   :1;
__REG32 ABTOINT   :1;
__REG32           :2;
__REG32 BREAKINT  :1;
__REG32 FEINT     :1;
__REG32 PEINT     :1;
__REG32 OEINT     :1;
__REG32           :16;
} __ints_bits;

/* Interrupt Clear Status Register (INTCS - 0x8010 1FE8) */
typedef struct{
__REG32 DCTSINTCLR   :1;
__REG32              :3;
__REG32 THREINTCLR   :1;
__REG32 RXTOINTCLR   :1;
__REG32              :1;
__REG32 WAKEUPINTCLR :1;
__REG32 ABEOINTCLR   :1;
__REG32 ABTOINTCLR   :1;
__REG32              :5;
__REG32 OEINTCLR     :1;
__REG32              :16;
} __intcs_bits;

/* Interrupt Set Status Register (INTSS - 0x8010 1FEC) */
typedef struct{
__REG32 DCTSINTSET   :1;
__REG32              :3;
__REG32 THREINTSET   :1;
__REG32 RXTOINTSET   :1;
__REG32              :1;
__REG32 WAKEUPINTSET :1;
__REG32 ABEOINTSET   :1;
__REG32 ABTOINTSET   :1;
__REG32              :5;
__REG32 OEINTSET     :1;
__REG32              :16;
} __intss_bits;

/* Transfer Length Register (DMA[0..7]Length - 0x8010 3808..38E8) */
typedef struct{
__REG32 LENGTH :12;
__REG32        :20;
} __dma0length_bits;

/* Channel Configuration Registers (DMA[0..7]Config - 0x8010 380C..38EC) */
typedef struct{
__REG32 DESTID          :5;
__REG32 SOURCEID        :5;
__REG32 SIZE            :2;
__REG32 SWAPENDIAN      :1;
__REG32 PCH             :3;
__REG32                 :1;
__REG32 PCHEN           :1;
__REG32 CIRCULARBUFFER  :1;
__REG32                 :13;
} __dma0config_bits;

/* Channel Enable Registers (DMA[0..7]Enab - 0x8010 3810..38F0) */
typedef struct{
__REG32 ENAB :1;
__REG32      :31;
} __dma0enab_bits;

/* Transfer Count Registers (DMA[0..7]Count - 0x8010 381C..38FC) */
typedef struct{
__REG32 COUNT :12;
__REG32       :20;
} __dma0count_bits;

/* Alternate Transfer Length Registers (DMA[0..7]AltLength - 0x8010 3A08..3A78) */
typedef struct{
__REG32 LENGTH :12;
__REG32        :20;
} __dma0altlength_bits;

/* Global Enable Register (DMA_Enable - 0x8010 3C00) */
typedef struct{
__REG32 EN_CH0 :1;
__REG32 EN_CH1 :1;
__REG32 EN_CH2 :1;
__REG32 EN_CH3 :1;
__REG32 EN_CH4 :1;
__REG32 EN_CH5 :1;
__REG32 EN_CH6 :1;
__REG32 EN_CH7 :1;
__REG32        :24;
} __dma_enable_bits;

/* Global Status and Clear Register (DMA_Stat - 0x8010 3C04) */
typedef struct{
__REG32 COMPLETE0 :1;
__REG32 HALF0     :1;
__REG32 COMPLETE1 :1;
__REG32 HALF1     :1;
__REG32 COMPLETE2 :1;
__REG32 HALF2     :1;
__REG32 COMPLETE3 :1;
__REG32 HALF3     :1;
__REG32 COMPLETE4 :1;
__REG32 HALF4     :1;
__REG32 COMPLETE5 :1;
__REG32 HALF5     :1;
__REG32 COMPLETE6 :1;
__REG32 HALF6     :1;
__REG32 COMPLETE7 :1;
__REG32 HALF7     :1;
__REG32           :14;
__REG32 SOFTINT   :1;
__REG32 ABORT     :1;
} __dma_stat_bits;

/* IRQ Mask Register (DMA_IRQMask - 0x8010 3C08) */
typedef struct{
__REG32 MASKCOMP0   :1;
__REG32 MASKHALF0   :1;
__REG32 MASKCOMP1   :1;
__REG32 MASKHALF1   :1;
__REG32 MASKCOMP2   :1;
__REG32 MASKHALF2   :1;
__REG32 MASKCOMP3   :1;
__REG32 MASKHALF3   :1;
__REG32 MASKCOMP4   :1;
__REG32 MASKHALF4   :1;
__REG32 MASKCOMP5   :1;
__REG32 MASKHALF5   :1;
__REG32 MASKCOMP6   :1;
__REG32 MASKHALF6   :1;
__REG32 MASKCOMP7   :1;
__REG32 MASKHALF7   :1;
__REG32             :14;
__REG32 MASKSOFTINT :1;
__REG32 MASKABORT   :1;
} __dma_irqmask_bits;

/* DMA Channel 3 External Enable Register (DMA3EXTEN - 0x8000 5048) */
typedef struct{
__REG32 EXTEN :1;
__REG32       :31;
} __dma3exten_bits;

/* I2C Receive/Transmit Register */
typedef union {
  //I2RX
  struct {
__REG32 RX  : 8;
__REG32     : 24;
  };
  //I2TX
  struct {
__REG32 TX    :8;
__REG32 START :1;
__REG32 STOP  :1;
__REG32       :22;
  };
} __i2rx_bits;

/* I2C Status Register (I2STS - 0x8002 0804) */
typedef struct{
__REG32 OCI    :1;
__REG32 AFI    :1;
__REG32 NAI    :1;
__REG32 DRMI   :1;
__REG32 DRSI   :1;
__REG32 ACTIVE :1;
__REG32 SCL    :1;
__REG32 SDA    :1;
__REG32 RFF    :1;
__REG32 RFE    :1;
__REG32 TFF    :1;
__REG32 TFE    :1;
__REG32 TFFS   :1;
__REG32 TFES   :1;
__REG32        :18;
} __i2sts_bits;

/* I2C Control Register (I2CTL - 0x8002 0808) */
typedef struct{
__REG32 OCIE      :1;
__REG32 AFIE      :1;
__REG32 NAIE      :1;
__REG32 DRMIE     :1;
__REG32 DRSIE     :1;
__REG32 RFFE      :1;
__REG32 RFNEE     :1;
__REG32 TFNFE     :1;
__REG32 I2RES     :1;
__REG32           :1;
__REG32 TFNFSE    :1;
__REG32           :21;
} __i2ctl_bits;

/* I2C Clock Divisor High Register (I2CLKHI - 0x8002 080C) */
typedef struct{
__REG32 CDH :15;
__REG32     :17;
} __i2clkhi_bits;

/* I2C Clock Divisor Low Register (I2CLKLO - 0x8002 0810) */
typedef struct{
__REG32 CDL :15;
__REG32     :17;
} __i2clklo_bits;

/* I2C Slave Address Register (I2ADR - 0x8002 0814) */
typedef struct{
__REG32 ADR  :7;
__REG32      :25;
} __i2adr_bits;

/* I2C Rx FIFO Level Register (I2RFL - 0x8002 0818) */
typedef struct{
__REG32  RLF :5;
__REG32      :27;
} __i2rfl_bits;

/* I2C Tx FIFO Level Register (I2TFL - 0x8002 081C) */
typedef struct{
__REG32  TLF :5;
__REG32      :27;
} __i2tfl_bits;

/* I2C Rx Byte Count Register (I2RXB - 0x8002 0820) */
typedef struct{
__REG32 RXB :7;
__REG32     :25;
} __i2rxb_bits;

/* I2C Tx Byte Count Register (I2TXB - 0x8002 0824) */
typedef struct{
__REG32 TXB :7;
__REG32     :25;
} __i2txb_bits;

/* I2C Slave Transmit Register (I2TXS - 0x8002 0828) */
typedef struct{
__REG32 TXS :8;
__REG32     :24;
} __i2txs_bits;

/* I2C Slave Tx FIFO Level Register (I2STFL - 0x8002 082C) */
typedef struct{
__REG32  STFL :5;
__REG32       :27;
} __i2stfl_bits;

/* A/D Control Register (ADCCON - 0x8000 2420) */
typedef struct{
__REG32 SELVREF :1;
__REG32 ADCENAB :1;
__REG32 CSCAN   :1;
__REG32 ADCSTRT :1;
__REG32 ADCBUSY :1;
__REG32         :27;
} __adccon_bits;

/* A/D Select Register (ADCSEL-0x8000 2424) */
typedef struct{
__REG32 SEL0 :4;
__REG32 SEL1 :4;
__REG32 SEL2 :4;
__REG32 SEL3 :4;
__REG32 SEL4 :4;
__REG32 SEL5 :4;
__REG32      :8;
} __adcsel_bits;

/* A/D Result Registers (ADCR5:0 - 0x8000 2400:2414) */
typedef struct{
__REG32 ADCR :10;
__REG32      :22;
} __adcr0_bits;

/* A/D Interrupt Enable Register (ADCINTE - 0x8000 2428) */
typedef struct{
__REG32 INTENAB :1;
__REG32         :31;
} __adcinte_bits;

/* A/D Interrupt Status Register (ADCINTS - 0x8000 242C) */
typedef struct{
__REG32 INTSTAT :1;
__REG32         :31;
} __adcints_bits;

/* A/D Interrupt Status Register (ADCINTC - 0x8000 2430) */
typedef struct{
__REG32 INTCLR :1;
__REG32        :31;
} __adcintc_bits;

/* A/D Power Down Register (ADCPD - 0x8000 5028) */
typedef struct{
__REG32 ADCPD :1;
__REG32       :31;
} __adcpd_bits;

/* USB Device Address Register (USBDevAdr - 0x8004 1000) */
typedef struct{
__REG32 DEVADDR :7;
__REG32 DEVEN   :1;
__REG32         :24;
} __usbdevadr_bits;

/* USB Mode Register (USBMode - 0x8004 100C) */
typedef struct{
__REG32 SOFTCT    :1;
__REG32 PWROFF    :1;
__REG32 WKUP      :1;
__REG32 GIE       :1;
__REG32 USBRESET  :1;
__REG32 GOSUSP    :1;
__REG32 SNDRSU    :1;
__REG32 CLKAON    :1;
__REG32           :24;
} __usbmode_bits;

/* USB Interrupt Enable Register (USBIntE - 0x8004 108C) */
typedef struct{
__REG32 BRESET  :1;
__REG32 SOF     :1;
__REG32 PSOF      :1;
__REG32 SUSP      :1;
__REG32 RESUME    :1;
__REG32 HS_STAT   :1;
__REG32 DMA       :1;
__REG32 EP0SETUP  :1;
__REG32           :24;
} __usbinte_bits;

/* USB Interrupt Status Register (USBIntStat - 0x8004 1094) */
typedef struct{
__REG32 BRESET    :1;
__REG32 SOF       :1;
__REG32 PSOF      :1;
__REG32 SUSP      :1;
__REG32 RESUME    :1;
__REG32 HS_STAT   :1;
__REG32 DMA       :1;
__REG32 EP0SETUP  :1;
__REG32           :24;
} __usbintstat_bits;

/* USB Interrupt Clear Register (USBIntClr - 0x8004 10AC) */
typedef struct{
__REG32 CLRBRESET   :1;
__REG32 CLRSOF      :1;
__REG32 CLRPSOF     :1;
__REG32 CLRSUSP     :1;
__REG32 CLRRESUME   :1;
__REG32 CLRHS_STAT  :1;
__REG32 CLRDMA      :1;
__REG32 CLREP0SETUP :1;
__REG32             :24;
} __usbintclr_bits;

/* USB Interrupt Set Register (USBIntSet - 0x8004 10B0) */
typedef struct{
__REG32 SETBRESET   :1;
__REG32 SETSOF      :1;
__REG32 SETPSOF     :1;
__REG32 SETSUSP     :1;
__REG32 SETRESUME   :1;
__REG32 SETHS_STAT  :1;
__REG32 SETDMA      :1;
__REG32 SETEP0SETUP :1;
__REG32             :24;
} __usbintset_bits;

/* USB Interrupt Priority Register (USBIntP - 0x8004 10B4) */
typedef struct{
__REG32 BRESET1   :1;
__REG32 SOF1      :1;
__REG32 PSOF1     :1;
__REG32 SUSP1     :1;
__REG32 RESUME1   :1;
__REG32 HS_STAT1  :1;
__REG32 UDMA1     :1;
__REG32 EP0SETUP1 :1;
__REG32           :24;
} __usbintp_bits;

/* USB Interrupt Configuration Register (USBIntCfg - 0x8004 1010) */
typedef struct{
__REG32 INTPOL      :1;
__REG32 INTEDGE     :1;
__REG32 DDBG_M_OUT  :2;
__REG32 DDBG_M_IN   :2;
__REG32 CDGB_M      :2;
__REG32             :24;
} __usbintcfg_bits;

/* USB Frame Number Register (USBFN - 0x8004 1074) */
typedef struct{
__REG32 SOF   :11;
__REG32 MSOF  :3;
__REG32       :18;
} __usbfn_bits;

/* USB Scratch Register (USBScratch - 0x8004 1078) */
typedef struct{
__REG32  SCRATCH :16;
__REG32          :16;
} __usbscratch_bits;

/* USB lock Register (USBlock - 0x8004 107C) */
typedef struct{
__REG32 UNLOCKCODE :16;
__REG32            :16;
} __usblock_bits;

/* USB Endpoint Index Register (USBEIX - 0x8004 102C) */
typedef struct{
__REG32 DIR        :1;
__REG32 ENDPIDX    :4;
__REG32 SEL_EP0SET :1;
__REG32            :26;
} __usbeix_bits;

/* USB Endpoint Type Register (USBEType - 0x8004 1008) */
typedef struct{
__REG32 TYPE    :2;
__REG32 DBLBUF  :1;
__REG32 EP_ENAB :1;
__REG32 DIS_EOT :1;
__REG32         :27;
} __usbetype_bits;

/* USB Endpoint Control Register (USBECtrl - 0x8004 1028) */
typedef struct{
__REG32 STALL     :1;
__REG32 TO_STATUS :1;
__REG32 DATA      :1;
__REG32           :1;
__REG32 CLRBUF    :1;
__REG32 BUFFULL   :1;
__REG32           :26;
} __usbectrl_bits;

/* USB Endpoint Max Packet Size Register (USBMaxSize - 0x8004 1004) */
typedef struct{
__REG32 FIFOSIZE :11;
__REG32 NTRANS   :2;
__REG32          :19;
} __usbmaxsize_bits;

/* USB Data Count Register (USBDCnt - 0x8004 101C) */
typedef struct{
__REG32 DATACOUNT :11;
__REG32           :21;
} __usbdcnt_bits;

/* USB Short Packet Register (USBShort - 0x8004 1024) */
typedef struct{
__REG32 OUTSH :8;
__REG32       :24;
} __usbshort_bits;

/* USB Endpoint Interrupt Enable Register (USBEIntE - 0x8004 1090) */
typedef struct{
__REG32 EP0RXIE :1;
__REG32 EP0TXIE :1;
__REG32 EP1RXIE :1;
__REG32 EP1TXIE :1;
__REG32 EP2RXIE :1;
__REG32 EP2TXIE :1;
__REG32 EP3RXIE :1;
__REG32 EP3TXIE :1;
__REG32 EP4RXIE :1;
__REG32 EP4TXIE :1;
__REG32 EP5RXIE :1;
__REG32 EP5TXIE :1;
__REG32 EP6RXIE :1;
__REG32 EP6TXIE :1;
__REG32 EP7RXIE :1;
__REG32 EP7TXIE :1;
__REG32         :16;
} __usbeinte_bits;

/* USB Endpoint Interrupt Status Register (USBEIntStat - 0x8004 1098) */
typedef struct{
__REG32 EP0RX :1;
__REG32 EP0TX :1;
__REG32 EP1RX :1;
__REG32 EP1TX :1;
__REG32 EP2RX :1;
__REG32 EP2TX :1;
__REG32 EP3RX :1;
__REG32 EP3TX :1;
__REG32 EP4RX :1;
__REG32 EP4TX :1;
__REG32 EP5RX :1;
__REG32 EP5TX :1;
__REG32 EP6RX :1;
__REG32 EP6TX :1;
__REG32 EP7RX :1;
__REG32 EP7TX :1;
__REG32       :16;
} __usbeintstat_bits;

/* USB Endpoint Interrupt Clear Register (USBEIntClr - 0x8004 10A0) */
typedef struct{
__REG32 CLR0RX :1;
__REG32 CLR0TX :1;
__REG32 CLR1RX :1;
__REG32 CLR1TX :1;
__REG32 CLR2RX :1;
__REG32 CLR2TX :1;
__REG32 CLR3RX :1;
__REG32 CLR3TX :1;
__REG32 CLR4RX :1;
__REG32 CLR4TX :1;
__REG32 CLR5RX :1;
__REG32 CLR5TX :1;
__REG32 CLR6RX :1;
__REG32 CLR6TX :1;
__REG32 CLR7RX :1;
__REG32 CLR7TX :1;
__REG32        :16;
} __usbeintclr_bits;

/* USB Endpoint Interrupt Set Register (USBEIntSet - 0x8004 10A4) */
typedef struct{
__REG32 SET0RX :1;
__REG32 SET0TX :1;
__REG32 SET1RX :1;
__REG32 SET1TX :1;
__REG32 SET2RX :1;
__REG32 SET2TX :1;
__REG32 SET3RX :1;
__REG32 SET3TX :1;
__REG32 SET4RX :1;
__REG32 SET4TX :1;
__REG32 SET5RX :1;
__REG32 SET5TX :1;
__REG32 SET6RX :1;
__REG32 SET6TX :1;
__REG32 SET7RX :1;
__REG32 SET7TX :1;
__REG32        :16;
} __usbeintset_bits;

/* USB Endpoint Interrupt Priority Register (USBEIntP - 0x8004 10A8) */
typedef struct{
__REG32 P0RX :1;
__REG32 P0TX :1;
__REG32 P1RX :1;
__REG32 P1TX :1;
__REG32 P2RX :1;
__REG32 P2TX :1;
__REG32 P3RX :1;
__REG32 P3TX :1;
__REG32 P4RX :1;
__REG32 P4TX :1;
__REG32 P5RX :1;
__REG32 P5TX :1;
__REG32 P6RX :1;
__REG32 P6TX :1;
__REG32 P7RX :1;
__REG32 P7TX :1;
__REG32      :16;
} __usbeintp_bits;

/* USB Test Mode Register (USBTMode - 0x8004 1084) */
typedef struct{
__REG32 SE0NAK  :1;
__REG32 JSTATE  :1;
__REG32 KSTATE  :1;
__REG32 PRBS    :1;
__REG32 FORCEFS :1;
__REG32         :2;
__REG32 FORCEHS :1;
__REG32         :24;
} __usbtest_bits;

/* USB Clock Enable Register (USBClkEn - 0x8000 5050) */
typedef struct{
__REG32 CLKEN :1;
__REG32       :31;
} __usbclken_bits;

/* USB DMA Control Register (UDMACtrl - 0x8004 0400) */
typedef struct{
__REG32 UDMA_EN :1;
__REG32         :31;
} __udmactrl_bits;

/* USB DMA Software Reset Register (UDMASoftRes - 0x8004 0404) */
typedef struct{
__REG32 RSTCH0 :1;
__REG32 RSTCH1 :1;
__REG32        :30;
} __udmasoftres_bits;

/* USB DMA Status Register (UDMAStat - 0x8004 0408) */
typedef struct{
__REG32 CH0STAT :3;
__REG32         :1;
__REG32 CH1STAT :3;
__REG32         :25;
} __udmastat_bits;

/* USB DMA Channel Status Registers (UDMA0Stat - 0x8004 0000,
UDMA1Stat - 0x8004 0040) */
typedef struct{
__REG32 STATE :2;
__REG32       :14;
__REG32 WE    :1;
__REG32 DFCE  :1;
__REG32       :2;
__REG32 RE    :1;
__REG32 SFCE  :1;
__REG32 UE    :1;
__REG32 CE    :1;
__REG32       :8;
} __udma0stat_bits;

/* USB DMA Interrupt Status Register (UDMAIntStat - 0x8004 0410) */
typedef struct{
__REG32           :1;
__REG32 CH0IEOT   :1;
__REG32 CH0IERROR :1;
__REG32           :2;
__REG32 CH1IEOT   :1;
__REG32 CH1IERROR :1;
__REG32           :25;
} __udmaintstat_bits;

/* USB DMA Interrupt Enable Register (UDMAIntEn - 0x8004 0418) */
typedef struct{
__REG32             :1;
__REG32 CH0IEOTEN   :1;
__REG32 CH0IERROREN :1;
__REG32             :2;
__REG32 CH1IEOTEN   :1;
__REG32 CH1IERROREN :1;
__REG32             :25;
} __udmainten_bits;

/* USB DMA Interrupt Disable Register (UDMAIntDis - 0x8004 0420) */
typedef struct{
__REG32               :1;
__REG32 CH0IEOTDIS    :1;
__REG32 CH0IERRORDIS  :1;
__REG32               :2;
__REG32 CH1IEOTDIS    :1;
__REG32 CH1IERRORDIS  :1;
__REG32               :25;
} __udmaintdis_bits;

/* USB DMA Interrupt Clear Register (UDMAIntClr - 0x8004 0430) */
typedef struct{
__REG32               :1;
__REG32 CH0IEOTCLR    :1;
__REG32 CH0IERRORCLR  :1;
__REG32               :2;
__REG32 CH1IEOTCLR    :1;
__REG32 CH1IERRORCLR  :1;
__REG32               :25;
} __udmaintclr_bits;

/* USB DMA Interrupt Set Register (UDMAIntSet - 0x8004 0428) */
typedef struct{
__REG32               :1;
__REG32 CH0IEOTSET    :1;
__REG32 CH0IERRORSET  :1;
__REG32               :2;
__REG32 CH1IEOTSET    :1;
__REG32 CH1IERRORSET  :1;
__REG32               :25;
} __udmaintset_bits;

/* USB DMA Channel Control Registers (UDMA0Ctrl - 0x8004 0004 and
UDMA1Ctrl - 0x8004 0044) */
typedef struct{
__REG32 CHEN      :2;
__REG32           :1;
__REG32 SOURCE    :2;
__REG32 STYPE     :2;
__REG32 SA_ADJ    :2;
__REG32 SFC_MODE  :2;
__REG32 SFC_PORT  :4;
__REG32 DEST      :2;
__REG32 DTYPE     :2;
__REG32 DA_ADJ    :2;
__REG32 DFC_MODE  :2;
__REG32 DFC_PORT  :4;
__REG32           :3;
__REG32 IEOT_EN   :1;
__REG32 IERROR_EN :1;
} __udma0ctrl_bits;

/* USB DMA Channel Count Registers (UDMA0Throtl - 0x8004 0010 and
UDMA1Throtl - 0x8004 0050 */
typedef struct{
__REG32 STHROTTLE :16;
__REG32 DTHROTTLE :16;
} __udma0throtl_bits;

/* Stream I/O Configuration Register (SIOCR - 0x8020 0384) */
typedef struct{
__REG32        :7;
__REG32 DAI_OE :1;
__REG32        :24;
} __siocr_bits;

/* I2S Format Register (I2S_FMT - 0x8020 0380) */
typedef struct{
__REG32 DAI_FMT :3;
__REG32         :3;
__REG32 DAO_FMT :3;
__REG32         :23;
} __i2s_fmt_bits;

/* SAI1 Status Register (SAISTAT1 - 0x8020 0010) */
typedef struct{
__REG32 RUNDER  :1;
__REG32 LUNDER  :1;
__REG32 ROVER   :1;
__REG32 LOVER   :1;
__REG32 LFULL   :1;
__REG32 LHALF   :1;
__REG32 LNOTMT  :1;
__REG32 RFULL   :1;
__REG32 RHALF   :1;
__REG32 RNOTMT  :1;
__REG32         :22;
} __saistat1_bits;

/* SAI1 Mask Register (SAIMASK1 - 0x8020 0014) */
typedef struct{
__REG32 RUNMK   :1;
__REG32 LUNMK   :1;
__REG32 ROVMK   :1;
__REG32 LOVMK   :1;
__REG32 LFULMK  :1;
__REG32 LHALFMK :1;
__REG32 LNMTMK  :1;
__REG32 RFULMK  :1;
__REG32 RHALFMK :1;
__REG32 RNMTMK  :1;
__REG32         :22;
} __saimask1_bits;

/* SAO1 Status Register (SAOSTAT1 - 0x8020 0210) */
typedef struct{
__REG32 RUNDER :1;
__REG32 LUNDER :1;
__REG32 ROVER  :1;
__REG32 LOVER  :1;
__REG32 LFULL  :1;
__REG32 LHALF  :1;
__REG32 LMT    :1;
__REG32 RFULL  :1;
__REG32 RHALF  :1;
__REG32 RMT    :1;
__REG32        :22;
} __saostat1_bits;

/* SAO1 Mask Register (SAOMASK1 - 0x8020 0214) */
typedef struct{
__REG32 RUNMK   :1;
__REG32 LUNMK   :1;
__REG32 ROVMK   :1;
__REG32 LOVMK   :1;
__REG32 LFULLMK :1;
__REG32 LHALFMK :1;
__REG32 LMTMK   :1;
__REG32 RFULLMK :1;
__REG32 RHALFMK :1;
__REG32 RMTMK   :1;
__REG32         :22;
} __saomask1_bits;

/* Dual Analog In Control Register (DAINCTRL - 0x8020 03A4) */
typedef struct{
__REG32 RSD_PD    :1;
__REG32 LSD_PD    :1;
__REG32           :1;
__REG32 RPGA_GAIN :4;
__REG32 RPGA_PD   :1;
__REG32 LPGA_GAIN :4;
__REG32 LPGA_PD   :1;
__REG32           :19;
} __dainctrl_bits;

/* Dual ADC Control Register (DADCCTRL - 0x8020 03A8) */
typedef struct{
__REG32         :1;
__REG32 RDITHER :1;
__REG32         :1;
__REG32 RPD     :1;
__REG32         :1;
__REG32 LDITHER :1;
__REG32         :1;
__REG32 LPD     :1;
__REG32         :24;
} __dadcctrl_bits;

/* Decimator Control Register (DECCTRL - 0x8020 03AC) */
typedef struct{
__REG32 RGAIN     :8;
__REG32 LGAIN     :8;
__REG32           :1;
__REG32 DADC_INV  :1;
__REG32 DADC_MUTE :1;
__REG32 ENODCBF   :1;
__REG32 ENIDCBF   :1;
__REG32           :1;
__REG32 ENTIMER   :1;
__REG32           :9;
} __decctrl_bits;

/* Decimator status register (DECSTAT - 0x8020 03B0) Read Only */
typedef struct{
__REG32 MUTED  :1;
__REG32 OVFLO  :1;
__REG32        :30;
} __decstat_bits;

/* Dual DAC Control Register (DDACCTRL - 0x8020 0398) */
typedef struct{
__REG32 RGAIN     :8;
__REG32 LGAIN     :8;
__REG32 DEEMPH    :3;
__REG32 SMUTE     :1;
__REG32 MODE2FS   :2;
__REG32 ROLLOFF   :2;
__REG32 PSLOW     :1;
__REG32 DDAC_PD   :1;
__REG32 DDAC_INV  :1;
__REG32 SILDET_T  :2;
__REG32 ENSILDET  :1;
__REG32           :2;
} __ddacctrl_bits;

/* Dual DAC status register (DDACSTAT - 0x8020 039C) Read Only */
typedef struct{
__REG32 MUTED   :1;
__REG32 PDOWN   :1;
__REG32 RSILENT :1;
__REG32 LSILENT :1;
__REG32         :28;
} __ddacstat_bits;

/* Dual DAC Settings Register (DDACSET - 0x8020 03A0) */
typedef struct{
__REG32         :8;
__REG32 RDYNPON :1;
__REG32 LDYNPON :1;
__REG32 LBI_DWA :1;
__REG32 RBI_DWA :1;
__REG32         :20;
} __ddacset_bits;

/* Power Control register (MCIPower - address 0x8010 0000) */
typedef struct{
__REG32 CTRL      :2;
__REG32           :4;
__REG32 OPENDRAIN :1;
__REG32           :25;
} __mcipower_bits;

/* Clock Control register (MCIClock - address 0x8010 0004) */
typedef struct{
__REG32 CLKDIV   : 8;
__REG32 CLKENAB  : 1;
__REG32 PWRSAVE  : 1;
__REG32 BYPASS   : 1;
__REG32 WIDEBUS  : 1;
__REG32          :20;
} __mciclock_bits;

/* Command register (MCICommand - address 0x8010 000C) */
typedef struct{
__REG32 CMDINDEX   : 6;
__REG32 RESPONSE   : 1;
__REG32 LONGRSP    : 1;
__REG32 INTERRUPT  : 1;
__REG32 W8PEND     : 1;
__REG32 CPSM_EN    : 1;
__REG32            :21;
} __mcicommand_bits;

/* Command Response register (MCIRespCommand - address 0x8010 0010) */
typedef struct{
__REG32 RESPCMD  : 6;
__REG32          :26;
} __mcirespcmd_bits;

/* Data Control register (MCIDataCtrl - address 0x8010 002C) */
typedef struct{
__REG32 XFERENAB   : 1;
__REG32 DIRECTION  : 1;
__REG32 STREAMMODE : 1;
__REG32 DMAENABLE  : 1;
__REG32 BLOCKSIZE  : 4;
__REG32            :24;
} __mcidatactrl_bits;

/* Status register (MCIStatus - address 0x8010 0034) */
typedef struct{
__REG32 CMDCRCFAIL       : 1;
__REG32 DATACRCFAIL      : 1;
__REG32 CMDTIMEOUT       : 1;
__REG32 DATATIMEOUT      : 1;
__REG32 TXUNDERRUN       : 1;
__REG32 RXOVERRUN        : 1;
__REG32 CMDRESPEND       : 1;
__REG32 CMDSENT          : 1;
__REG32 DATAEND          : 1;
__REG32 STARTBITERR      : 1;
__REG32 DATABLOCKEND     : 1;
__REG32 CMDACTIVE        : 1;
__REG32 TXACTIVE         : 1;
__REG32 RXACTIVE         : 1;
__REG32 TXFIFOHALFEMPTY  : 1;
__REG32 RXFIFOHALFFULL   : 1;
__REG32 TXFIFOFULL       : 1;
__REG32 RXFIFOFULL       : 1;
__REG32 TXFIFOEMPTY      : 1;
__REG32 RXDATAAVLBL      : 1;
__REG32 TXDATAAVLBL      : 1;
__REG32 RXFIFOEMPTY      : 1;
__REG32                  :10;
} __mcistatus_bits;

/* Clear register (MCIClear - 0x8010 0038) */
typedef struct{
__REG32 CMDCRCFAILCLR    : 1;
__REG32 DATACRCFAILCLR   : 1;
__REG32 CMDTIMEOUTCLR    : 1;
__REG32 DATATIMEOUTCLR   : 1;
__REG32 TXUNDERRUNCLR    : 1;
__REG32 RXOVERRUNCLR     : 1;
__REG32 CMDRESPENDCLR    : 1;
__REG32 CMDSENTCLR       : 1;
__REG32 DATAENDCLR       : 1;
__REG32 STARTBITERRCLR   : 1;
__REG32 DATABLOCKENDCLR  : 1;
__REG32                  :21;
} __mciclear_bits;

/* Interrupt Mask registers (MCIMask0-1 - addresses 0x8010 003C, 0x8010 0040) */
typedef struct{
__REG32 Mask0  :1;
__REG32 Mask1  :1;
__REG32 Mask2  :1;
__REG32 Mask3  :1;
__REG32 Mask4  :1;
__REG32 Mask5  :1;
__REG32 Mask6  :1;
__REG32 Mask7  :1;
__REG32 Mask8  :1;
__REG32 Mask9  :1;
__REG32 Mask10 :1;
__REG32 Mask11 :1;
__REG32 Mask12 :1;
__REG32 Mask13 :1;
__REG32 Mask14 :1;
__REG32 Mask15 :1;
__REG32 Mask16 :1;
__REG32 Mask17 :1;
__REG32 Mask18 :1;
__REG32 Mask19 :1;
__REG32 Mask20 :1;
__REG32 Mask21 :1;
__REG32        :10;
} __mcimask0_bits;

/* FIFO Counter register (MCIFifoCnt - address 0x8010 0048) */
typedef struct{
__REG32 DATACOUNT  :15;
__REG32            :17;
} __mcififocnt_bits;

/* MCI Clock Enable register (MCICLKEN - 0x8000 502C) */
typedef struct{
__REG32 MCICLKEN :1;
__REG32          :31;
} __mciclken_bits;

/* LCD Control Register (LCDCTRL - 0x8010 3004) */
typedef struct{
__REG32         :1;
__REG32 LCDPS   :1;
__REG32 LCDMI   :1;
__REG32 LCDW84  :1;
__REG32 SCLKSEL :2;
__REG32 SSAMPL  :2;
__REG32 LCDCBSY :1;
__REG32 CBSENSE :1;
__REG32 LCDBSYN :3;
__REG32 LRSSEL  :1;
__REG32 CSPOLAR :1;
__REG32 ERPOLAR :1;
__REG32 MSFIRST :1;
__REG32         :15;
} __lcdctrl_bits;

/* LCD Status Register (LCDSTAT - 0x8010 3000) Read Only */
typedef struct{
__REG32 LCDFIFOMT :1;
__REG32 LCDFIFOH  :1;
__REG32 LCDOVER   :1;
__REG32 LCDREAD   :1;
__REG32 LCDBUSY   :1;
__REG32 FIFOLEV   :5;
__REG32           :22;
} __lcdstat_bits;

/* LCD Raw Interrupt Status Register (LCDISTAT - 0x8010 0008) Read Only */
typedef struct{
__REG32 LCDFIFOMT :1;
__REG32 LCDFIFOH  :1;
__REG32           :1;
__REG32 LCDREAD   :1;
__REG32           :28;
} __lcdistat_bits;

/* LCD Interrupt Mask Register (LCDIMASK - 0x8010 3010) */
typedef struct{
__REG32 LCDFIFOMT :1;
__REG32 LCDFIFOH  :1;
__REG32 LCDOVER   :1;
__REG32 LCDREAD   :1;
__REG32           :28;
} __lcdimask_bits;

/* LCD Read Command Register (LCDREAD - 0x8010 3014) Write Only */
typedef struct{
__REG32 LCDDATA :1;
__REG32         :31;
} __lcdread_bits;

/* LCD Instruction Byte Register (LCDIBYTE - 0x8010 3020) */
typedef struct{
__REG32 IBYTE :8;
__REG32       :24;
} __lcdibyte_bits;

/* LCD Data Byte Register (LCDDBYTE - 0x8010 3030) */
typedef struct{
__REG32 DBYTE :8;
__REG32       :24;
} __lcddbyte_bits;

/* LCD Data Word Register (LCDDWORD - 0x8010 3080) Write Only */
typedef struct{
__REG32  DWORD :8;
__REG32        :24;
} __lcddword_bits;

/* Bit/Signal correspondence in Port 0 (EMC) registers */
typedef struct{
  __REG32 P0_0   :1;
  __REG32 P0_1   :1;
  __REG32 P0_2   :1;
  __REG32 P0_3   :1;
  __REG32 P0_4   :1;
  __REG32 P0_5   :1;
  __REG32 P0_6   :1;
  __REG32 P0_7   :1;
  __REG32 P0_8   :1;
  __REG32 P0_9   :1;
  __REG32 P0_10  :1;
  __REG32 P0_11  :1;
  __REG32 P0_12  :1;
  __REG32 P0_13  :1;
  __REG32 P0_14  :1;
  __REG32 P0_15  :1;
  __REG32 P0_16  :1;
  __REG32 P0_17  :1;
  __REG32 P0_18  :1;
  __REG32 P0_19  :1;
  __REG32 P0_20  :1;
  __REG32 P0_21  :1;
  __REG32 P0_22  :1;
  __REG32 P0_23  :1;
  __REG32 P0_24  :1;
  __REG32 P0_25  :1;
  __REG32 P0_26  :1;
  __REG32 P0_27  :1;
  __REG32 P0_28  :1;
  __REG32 P0_29  :1;
  __REG32 P0_30  :1;
  __REG32 P0_31  :1;
} __port0_bits;

/* Bit/Signal correspondence in input group 1 (EMC) registers */
typedef struct{
    __REG32 A16   :1;
    __REG32 A17   :1;
    __REG32 A18   :1;
    __REG32 A19   :1;
    __REG32 A20   :1;
    __REG32 STCS0 :1;
    __REG32 STCS1 :1;
    __REG32 STCS2 :1;
    __REG32 DYCS  :1;
    __REG32 CKE   :1;
    __REG32 DQM0  :1;
    __REG32 DQM1  :1;
    __REG32 BLS0  :1;
    __REG32 BLS1  :1;
    __REG32 MCLKO :1;
    __REG32 WE    :1;
    __REG32 CAS   :1;
    __REG32 RAS   :1;
    __REG32 OE    :1;
    __REG32 PRO   :1;
    __REG32       :12;
} __port1_bits;

/* Bit/Signal correspondence in Port 2 (GPIO) registers */
typedef struct {
    __REG32 P2_0 :1;
    __REG32 P2_1 :1;
    __REG32 P2_2 :1;
    __REG32 P2_3 :1;
    __REG32      :28;
} __port2_bits;

/* Bit/Signal correspondence in Port 3 (DAI/DAO) registers */
typedef struct{
__REG32 P3_0 :1;
__REG32 P3_1 :1;
__REG32 P3_2 :1;
__REG32 P3_3 :1;
__REG32      :1;
__REG32 P3_5 :1;
__REG32 P3_6 :1;
__REG32      :25;
} __port3_bits;

/* Bit/Signal correspondence in Port 4 (LCD) registers */
typedef struct{
__REG32 P4_0  :1;
__REG32 P4_1  :1;
__REG32 P4_2  :1;
__REG32 P4_3  :1;
__REG32 P4_4  :1;
__REG32 P4_5  :1;
__REG32 P4_6  :1;
__REG32 P4_7  :1;
__REG32 P4_8  :1;
__REG32 P4_9  :1;
__REG32 P4_10 :1;
__REG32 P4_11 :1;
__REG32       :20;
} __port4_bits;

/* Bit/Signal correspondence in Port 5 (MCI/SD) registers */
typedef struct{
__REG32 P5_0 :1;
__REG32 P5_1 :1;
__REG32 P5_2 :1;
__REG32 P5_3 :1;
__REG32 P5_4 :1;
__REG32 P5_5 :1;
__REG32      :26;
} __port5_bits;

/* Bit/Signal correspondence in Port 6 (UART) registers */
typedef struct{
__REG32 P6_0 :1;
__REG32 P6_1 :1;
__REG32 P6_2 :1;
__REG32 P6_3 :1;
__REG32      :28;
} __port6_bits;

/* Port 7 (USB) Registers */
typedef struct{
__REG32 P7_0 :1;
__REG32      :31;
} __port7_bits;

/* Bit/Signal correspondence in input group 0 registers */
typedef struct{
__REG32 START  :1;
__REG32 ATARDY :1;
__REG32 P0_0   :1;
__REG32 P0_1   :1;
__REG32 P0_2   :1;
__REG32 P0_3   :1;
__REG32 P0_4   :1;
__REG32 P0_5   :1;
__REG32 P0_6   :1;
__REG32 P0_7   :1;
__REG32 P0_8   :1;
__REG32 P0_9   :1;
__REG32 P0_10  :1;
__REG32 P0_11  :1;
__REG32 P0_12  :1;
__REG32 P0_13  :1;
__REG32 P0_14  :1;
__REG32 P0_15  :1;
__REG32 P0_16  :1;
__REG32 P0_17  :1;
__REG32 P0_18  :1;
__REG32 P0_19  :1;
__REG32 P0_20  :1;
__REG32 P0_21  :1;
__REG32 P0_22  :1;
__REG32 P0_23  :1;
__REG32 P0_24  :1;
__REG32 P0_25  :1;
__REG32 P0_26  :1;
__REG32 P0_27  :1;
__REG32 P0_28  :1;
__REG32 P0_29  :1;
} __igroup0_bits;

/* Bit/Signal correspondence in input group 1 registers */
typedef struct{
__REG32 P0_30 :1;
__REG32 P0_31 :1;
__REG32 P1_0  :1;
__REG32 P1_1  :1;
__REG32 P1_2  :1;
__REG32 P1_3  :1;
__REG32 P1_4  :1;
__REG32 P1_5  :1;
__REG32 P1_6  :1;
__REG32 P1_7  :1;
__REG32 P1_8  :1;
__REG32 P1_9  :1;
__REG32 P1_10 :1;
__REG32 P1_11 :1;
__REG32 P1_12 :1;
__REG32 P1_13 :1;
__REG32 P1_14 :1;
__REG32 P1_15 :1;
__REG32 P1_16 :1;
__REG32 P1_17 :1;
__REG32 P1_18 :1;
__REG32 P1_19 :1;
__REG32 P3_0  :1;
__REG32 P3_1  :1;
__REG32 P3_2  :1;
__REG32 WSO   :1;
__REG32 P3_5  :1;
__REG32 P3_6  :1;
__REG32 P4_0  :1;
__REG32 P4_1  :1;
__REG32 P4_2  :1;
__REG32 P4_3  :1;
} __igroup1_bits;

/* Bit/Signal correspondence in input group 2 registers */
typedef struct{
__REG32 P4_4      :1;
__REG32 P4_5      :1;
__REG32 P4_6      :1;
__REG32 P4_7      :1;
__REG32 P4_8      :1;
__REG32 P4_9      :1;
__REG32 P4_10     :1;
__REG32 P4_11     :1;
__REG32 P3_3      :1;
__REG32 P5_0      :1;
__REG32 P5_1      :1;
__REG32 P5_2      :1;
__REG32 P5_3      :1;
__REG32 P5_4      :1;
__REG32 P5_5      :1;
__REG32 P6_0      :1;
__REG32 P6_1      :1;
__REG32 P6_2      :1;
__REG32 P6_3      :1;
__REG32 CACHEFIQ  :1;
__REG32 CACHEIRQ  :1;
__REG32 T0CT1     :1;
__REG32 T1CT1     :1;
__REG32 RTCINT    :1;
__REG32 ADCINT    :1;
__REG32 P5_5_1    :1;
__REG32 P5_4_1    :1;
__REG32 P5_3_1    :1;
__REG32 P5_2_1    :1;
__REG32 WDOG      :1;
__REG32 P6_0_1    :1;
__REG32 SCL       :1;
} __igroup2_bits;

/* Bit/Signal correspondence in input group 3 registers */
typedef struct{
__REG32             :2;
__REG32 P2_0        :1;
__REG32 P2_1        :1;
__REG32 P2_2        :1;
__REG32 P2_3        :1;
__REG32 USBGOSUSP   :1;
__REG32 USBWKUPPCS  :1;
__REG32 USBPWROFF   :1;
__REG32 P7_0        :1;
__REG32 USBBUSRES   :1;
__REG32             :21;
} __igroup3_bits;

/* Event Router Output Register (EVOUT - 0x8000 0D40) */
typedef struct{
__REG32 INT0   :1;
__REG32 INT1   :1;
__REG32 INT2   :1;
__REG32 INT3   :1;
__REG32 WAKEUP :1;
__REG32        :27;
} __evout_bits;

/* Features Register (EVFEATURES - 0x8000 0E00) */
typedef struct{
__REG32 N :8;
__REG32   :8;
__REG32 M :6;
__REG32   :10;
} __evfeatures_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Common declarations  ****************************************************/
/***************************************************************************
 **
 ** System control
 **
 ***************************************************************************/
__IO_REG32_BIT(SYS_BOOTMAP,     0x80005070,__READ_WRITE,__sys_bootmap_bits);
__IO_REG32(    SYS_BOOTADDR,    0x80005074,__READ_WRITE);
__IO_REG32(    SYS_PARTID,      0x8000507C,__READ      );

/***************************************************************************
 **
 ** Cache and memory mapping
 **
 ***************************************************************************/
__IO_REG32_BIT(CACHE_RST_STAT ,0x80104000,__READ      ,__cache_rst_stat_bits);
__IO_REG32_BIT(CACHE_SETTINGS ,0x80104004,__READ_WRITE,__cache_settings_bits);
__IO_REG32_BIT(CACHE_PAGE_CTRL,0x80104008,__READ_WRITE,__cache_page_ctrl_bits);
__IO_REG32(    C_RD_MISSES    ,0x8010400C,__READ      );
__IO_REG32(    C_FLUSHES      ,0x80104010,__READ      );
__IO_REG32(    C_WR_MISSES    ,0x80104014,__READ      );
__IO_REG32_BIT(ADDRESS_PAGE_0 ,0x80104018,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_1 ,0x8010401C,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_2 ,0x80104020,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_3 ,0x80104024,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_4 ,0x80104028,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_5 ,0x8010402C,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_6 ,0x80104030,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_7 ,0x80104034,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_8 ,0x80104038,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_9 ,0x8010403C,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_10,0x80104040,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_11,0x80104044,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_12,0x80104048,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_13,0x8010404C,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_14,0x80104050,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(ADDRESS_PAGE_15,0x80104054,__READ_WRITE,__address_page_n_bits);
__IO_REG32_BIT(CPU_CLK_GATE   ,0x80104058,__READ_WRITE,__cpu_clk_gate_bits);

/***************************************************************************
 **
 ** Flash memory controller
 **
 ***************************************************************************/
__IO_REG32_BIT(F_CTRL,     0x80102000,__READ_WRITE,__f_ctrl_bits);
__IO_REG32_BIT(F_STAT,     0x80102004,__READ      ,__f_stat_bits);
__IO_REG32_BIT(F_PROG_TIME,0x80102008,__READ_WRITE,__f_prog_time_bits);
__IO_REG32_BIT(F_WAIT,     0x80102010,__READ_WRITE,__f_wait_bits);
__IO_REG32_BIT(F_CLK_TIME, 0x8010201C,__READ_WRITE,__f_clk_time_bits);
__IO_REG32_BIT(F_INTEN_CLR,0x80102FD8,__WRITE     ,__f_inten_clr_bits);
__IO_REG32_BIT(F_INTEN_SET,0x80102FDC,__WRITE     ,__f_inten_set_bits);
__IO_REG32_BIT(F_INT_STAT, 0x80102FE0,__READ      ,__f_int_stat_bits);
__IO_REG32_BIT(F_INTEN,    0x80102FE4,__READ      ,__f_inten_bits);
__IO_REG32_BIT(F_INT_CLR,  0x80102FE8,__WRITE     ,__f_int_clr_bits);
__IO_REG32_BIT(F_INT_SET,  0x80102FEC,__WRITE     ,__f_int_set_bits);
__IO_REG32_BIT(FLASH_PD,   0x80005030,__READ_WRITE,__flash_pd_bits);
__IO_REG32_BIT(FLASH_INIT, 0x80005034,__READ_WRITE,__flash_init_bits);

/***************************************************************************
 **
 ** DC-DC
 **
 ***************************************************************************/
__IO_REG32_BIT(DCDCADJUST1,0x80005004,__READ_WRITE,__dcdcadjust1_bits);
__IO_REG32_BIT(DCDCADJUST2,0x80005008,__READ_WRITE,__dcdcadjust2_bits);
__IO_REG32_BIT(DCDCCLKSEL, 0x8000500C,__READ_WRITE,__dcdcclksel_bits);

/***************************************************************************
 **
 ** Clock generation unit
 **
 ***************************************************************************/
__IO_REG32_BIT(PMODE,  0x80004C00,__READ_WRITE,__pmode_bits);
__IO_REG32_BIT(WDBARK, 0x80004C04,__READ      ,__wdbark_bits);
__IO_REG32_BIT(OSC32EN,0x80004C08,__READ_WRITE,__osc32en_bits);
__IO_REG32_BIT(OSCEN,  0x80004C10,__READ_WRITE,__oscen_bits);

/***************************************************************************
 **
 ** Main PLL
 **
 ***************************************************************************/
__IO_REG32(LPFIN,   0x80004CE4,__READ_WRITE);
__IO_REG32(LPPDN,   0x80004CE8,__READ_WRITE);
__IO_REG32(LPMBYP,  0x80004CEC,__READ_WRITE);
__IO_REG32(LPLOCK,  0x80004CF0,__READ      );
__IO_REG32(LPDBYP,  0x80004CF4,__READ_WRITE);
__IO_REG32(LPMSEL,  0x80004CF8,__READ_WRITE);
__IO_REG32(LPPSEL,  0x80004CFC,__READ_WRITE);

/***************************************************************************
 **
 ** High speed PLL
 **
 ***************************************************************************/
__IO_REG32_BIT(HPFIN, 0x80004CAC,__READ_WRITE,__hpfin_bits);
__IO_REG32_BIT(HPNDEC,0x80004CB4,__READ_WRITE,__hpndec_bits);
__IO_REG32_BIT(HPMDEC,0x80004CB0,__READ_WRITE,__hpmdec_bits);
__IO_REG32_BIT(HPPDEC,0x80004CB8,__READ_WRITE,__hppdec_bits);
__IO_REG32_BIT(HPMODE,0x80004CBC,__READ_WRITE,__hpmode_bits);
__IO_REG32_BIT(HPSTAT,0x80004CC0,__READ      ,__hpstat_bits);
__IO_REG32_BIT(HPREQ, 0x80004CC8,__READ_WRITE,__hpreq_bits);
__IO_REG32_BIT(HPACK, 0x80004CC4,__READ      ,__hpack_bits);
__IO_REG32_BIT(HPSELR,0x80004CD8,__READ_WRITE,__hpselr_bits);
__IO_REG32_BIT(HPSELI,0x80004CDC,__READ_WRITE,__hpseli_bits);
__IO_REG32_BIT(HPSELP,0x80004CE0,__READ_WRITE,__hpselp_bits);

/***************************************************************************
 **
 ** Selection stage
 **
 ***************************************************************************/
__IO_REG32_BIT(SYSSCR,  0x80004000,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(APB0SCR, 0x80004004,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(APB1SCR, 0x80004008,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(APB3SCR, 0x8000400C,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(DCDCSCR, 0x80004010,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(RTCSCR,  0x80004014,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(MCISCR,  0x80004018,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(UARTSCR, 0x8000401C,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(DAIOSCR, 0x80004020,__READ_WRITE,__sysscr_daiscr_bits);
__IO_REG32_BIT(DAISCR,  0x80004024,__READ_WRITE,__sysscr_daiscr_bits);

__IO_REG32_BIT(SYSFSR1, 0x8000402C,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(APB0FSR1,0x80004030,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(APB1FSR1,0x80004034,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(APB3FSR1,0x80004038,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(DCDCFSR1,0x8000403C,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(RTCFSR1, 0x80004040,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(MCIFSR1, 0x80004044,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(UARTFSR1,0x80004048,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(DAIOFSR1,0x8000404C,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(DAISFSR1,0x80004050,__READ_WRITE,__sysfsr1_daifsr1_bits);

__IO_REG32_BIT(SYSFSR2, 0x80004058,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(APB0FSR2,0x8000405C,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(APB1FSR2,0x80004060,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(APB3FSR2,0x80004064,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(DCDCFSR2,0x80004068,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(RTCFSR2, 0x8000406C,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(MCIFSR2, 0x80004070,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(UARTFSR2,0x80004074,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(DAIOFSR2,0x80004078,__READ_WRITE,__sysfsr1_daifsr1_bits);
__IO_REG32_BIT(DAISFSR2,0x8000407C,__READ_WRITE,__sysfsr1_daifsr1_bits);

__IO_REG32_BIT(SYSSSR,  0x80004084,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(APB0SSR, 0x80004088,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(APB1SSR, 0x8000408C,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(APB3SSR, 0x80004090,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(DCDCSSR, 0x80004094,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(RTCSSR,  0x80004098,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(MCISSR,  0x8000409C,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(UARTSSR, 0x800040A0,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(DAIOSSR, 0x800040A4,__READ,__sysssr_daissr_bits);
__IO_REG32_BIT(DAISSR,  0x800040A8,__READ,__sysssr_daissr_bits);

__IO_REG32_BIT(SYSBCR,  0x800043F0,__READ_WRITE,__sysbcr_daiobcr_bits);
__IO_REG32_BIT(APB0BCR, 0x800043F4,__READ_WRITE,__sysbcr_daiobcr_bits);
__IO_REG32_BIT(DAIOBCR, 0x800043F8,__READ_WRITE,__sysbcr_daiobcr_bits);

/***************************************************************************
 **
 ** Fractional divider
 **
 ***************************************************************************/
__IO_REG32_BIT(SYSFDCR0, 0x800043FC,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(SYSFDCR1, 0x80004400,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(SYSFDCR2, 0x80004404,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(SYSFDCR3, 0x80004408,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(SYSFDCR4, 0x8000440C,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(SYSFDCR5, 0x80004410,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(APB0FDCR0,0x80004414,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(APB0FDCR1,0x80004418,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(APB1FDCR, 0x8000441C,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(APB3FDCR, 0x80004420,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(UARTFDCR, 0x80004424,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(DAIOFDCR0,0x80004428,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(DAIOFDCR1,0x8000442C,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(DAIOFDCR2,0x80004430,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(DAIOFDCR3,0x80004434,__READ_WRITE,__sysfdcr_bits);
__IO_REG32_BIT(DAIOFDCR4,0x80004438,__READ_WRITE,__daiofdcr4_bits);
__IO_REG32_BIT(DAIOFDCR5,0x8000443C,__READ_WRITE,__sysfdcr_bits);

/***************************************************************************
 **
 ** Power control
 **
 ***************************************************************************/
__IO_REG32_BIT(APB0PCR0,0x800040B0,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(APB3PCR0,0x800040BC,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(MCIPCR0 ,0x800040C8,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(FLSHPCR1,0x800040E0,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(LCDPCR1 ,0x800040EC,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(USBPCR0 ,0x800040F8,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(CPUPCR2 ,0x80004104,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(EMCPCR0 ,0x80004110,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(APB0PCR1,0x8000411C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(ADCPCR0 ,0x80004128,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(IOCPCR  ,0x80004134,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(APB1PCR1,0x80004140,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(I2CPCR  ,0x8000414C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAIPCR0 ,0x80004158,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DSSPCR1 ,0x80004164,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(SAO2PCR ,0x8000417C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(EDGEPCR ,0x80004188,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(RTCPCR  ,0x80004194,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DDACPCR1,0x800041A0,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DADCPCR2,0x800041AC,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAOPCR1 ,0x800041B8,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAIPCR3 ,0x800041C4,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(APB1PCR0,0x800040B4,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(MMIOPCR0,0x800040C0,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(MCIPCR1 ,0x800040CC,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(FLSHPCR2,0x800040E4,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DMAPCR0 ,0x800040F0,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(CPUPCR0 ,0x800040FC,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(RAMPCR  ,0x80004108,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(EMCPCR1 ,0x80004114,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(EVRTPCR ,0x80004120,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(ADCPCR1 ,0x8000412C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(CGUPCR  ,0x80004138,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(T0PCR   ,0x80004144,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(APB3PCR1,0x80004150,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(SAI1PCR ,0x80004168,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(SAI4PCR ,0x80004174,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DADCPCR0,0x8000418C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(MCIPCR2 ,0x80004198,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DDACPCR2,0x800041A4,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAIPCR1 ,0x800041B0,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAOPCR2 ,0x800041BC,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(APB2PCR ,0x800040B8,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(AHB0PCR ,0x800040C4,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(UARTPCR0,0x800040D0,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(FLSHPCR0,0x800040DC,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(LCDPCR0 ,0x800040E8,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DMAPCR1 ,0x800040F4,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(CPUPCR1 ,0x80004100,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(ROMPCR  ,0x8000410C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(MMIOPCR1,0x80004118,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(RTCPCR0 ,0x80004124,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(WDTPCR  ,0x80004130,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(SYSCPCR ,0x8000413C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(T1PCR   ,0x80004148,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(SCONPCR ,0x80004154,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAOPCR0 ,0x80004160,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(SAO1PCR ,0x80004178,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DDACPCR0,0x80004184,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DCDCPCR ,0x80004190,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(UARTPCR1,0x8000419C,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DADCPCR1,0x800041A8,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAIPCR2 ,0x800041B4,__READ_WRITE,__power_control_bits);
__IO_REG32_BIT(DAOPCR3 ,0x800041C0,__READ_WRITE,__power_control_bits);

/***************************************************************************
 **
 ** Power status
 **
 ***************************************************************************/
__IO_REG32_BIT(APB0PSR0,0x800041CC,__READ,__power_status_bits);
__IO_REG32_BIT(APB1PSR0,0x800041D0,__READ,__power_status_bits);
__IO_REG32_BIT(APB2PSR ,0x800041D4,__READ,__power_status_bits);
__IO_REG32_BIT(APB3PSR0,0x800041D8,__READ,__power_status_bits);
__IO_REG32_BIT(MMIOPSR0,0x800041DC,__READ,__power_status_bits);
__IO_REG32_BIT(AHB0PSR ,0x800041E0,__READ,__power_status_bits);
__IO_REG32_BIT(MCIPSR0 ,0x800041E4,__READ,__power_status_bits);
__IO_REG32_BIT(MCIPSR1 ,0x800041E8,__READ,__power_status_bits);
__IO_REG32_BIT(UARTPSR0,0x800041EC,__READ,__power_status_bits);
__IO_REG32_BIT(FLSHPSR0,0x800041F8,__READ,__power_status_bits);
__IO_REG32_BIT(FLSHPSR1,0x800041FC,__READ,__power_status_bits);
__IO_REG32_BIT(FLSHPSR2,0x80004200,__READ,__power_status_bits);
__IO_REG32_BIT(LCDPSR0 ,0x80004204,__READ,__power_status_bits);
__IO_REG32_BIT(LCDPSR1 ,0x80004208,__READ,__power_status_bits);
__IO_REG32_BIT(DMAPSR0 ,0x8000420C,__READ,__power_status_bits);
__IO_REG32_BIT(DMAPSR1 ,0x80004210,__READ,__power_status_bits);
__IO_REG32_BIT(USBPSR0 ,0x80004214,__READ,__power_status_bits);
__IO_REG32_BIT(CPUPSR0 ,0x80004218,__READ,__power_status_bits);
__IO_REG32_BIT(CPUPSR1 ,0x8000421C,__READ,__power_status_bits);
__IO_REG32_BIT(CPUPSR2 ,0x80004220,__READ,__power_status_bits);
__IO_REG32_BIT(RAMPSR  ,0x80004224,__READ,__power_status_bits);
__IO_REG32_BIT(ROMPSR  ,0x80004228,__READ,__power_status_bits);
__IO_REG32_BIT(EMCPSR0 ,0x8000422C,__READ,__power_status_bits);
__IO_REG32_BIT(EMCPSR1 ,0x80004230,__READ,__power_status_bits);
__IO_REG32_BIT(MMIOPSR1,0x80004234,__READ,__power_status_bits);
__IO_REG32_BIT(APB0PSR1,0x80004238,__READ,__power_status_bits);
__IO_REG32_BIT(EVRTPSR ,0x8000423C,__READ,__power_status_bits);
__IO_REG32_BIT(RTCPSR0 ,0x80004240,__READ,__power_status_bits);
__IO_REG32_BIT(ADCPSR0 ,0x80004244,__READ,__power_status_bits);
__IO_REG32_BIT(ADCPSR1 ,0x80004248,__READ,__power_status_bits);
__IO_REG32_BIT(WDTPSR  ,0x8000424C,__READ,__power_status_bits);
__IO_REG32_BIT(IOCPSR  ,0x80004250,__READ,__power_status_bits);
__IO_REG32_BIT(CGUPSR  ,0x80004254,__READ,__power_status_bits);
__IO_REG32_BIT(SYSCPSR ,0x80004258,__READ,__power_status_bits);
__IO_REG32_BIT(APB1PSR1,0x8000425C,__READ,__power_status_bits);
__IO_REG32_BIT(T0PSR   ,0x80004260,__READ,__power_status_bits);
__IO_REG32_BIT(T1PSR   ,0x80004264,__READ,__power_status_bits);
__IO_REG32_BIT(I2CPSR  ,0x80004268,__READ,__power_status_bits);
__IO_REG32_BIT(APB3PSR1,0x8000426C,__READ,__power_status_bits);
__IO_REG32_BIT(SCONPSR ,0x80004270,__READ,__power_status_bits);
__IO_REG32_BIT(DAIPSR0 ,0x80004274,__READ,__power_status_bits);
__IO_REG32_BIT(DAOPSR0 ,0x8000427C,__READ,__power_status_bits);
__IO_REG32_BIT(DSSPSR1 ,0x80004280,__READ,__power_status_bits);
__IO_REG32_BIT(SAI1PSR ,0x80004284,__READ,__power_status_bits);
__IO_REG32_BIT(SAI4PSR ,0x80004290,__READ,__power_status_bits);
__IO_REG32_BIT(SAO1PSR ,0x80004294,__READ,__power_status_bits);
__IO_REG32_BIT(SAO2PSR ,0x80004298,__READ,__power_status_bits);
__IO_REG32_BIT(DDACPSR0,0x800042A0,__READ,__power_status_bits);
__IO_REG32_BIT(EDGEPSR ,0x800042A4,__READ,__power_status_bits);
__IO_REG32_BIT(DADCPSR0,0x800042A8,__READ,__power_status_bits);
__IO_REG32_BIT(DCDCPSR ,0x800042AC,__READ,__power_status_bits);
__IO_REG32_BIT(RTCPSR1 ,0x800042B0,__READ,__power_status_bits);
__IO_REG32_BIT(MCIPSR2 ,0x800042B4,__READ,__power_status_bits);
__IO_REG32_BIT(UARTPSR1,0x800042B8,__READ,__power_status_bits);
__IO_REG32_BIT(DDACPSR1,0x800042BC,__READ,__power_status_bits);
__IO_REG32_BIT(DDACPSR2,0x800042C0,__READ,__power_status_bits);
__IO_REG32_BIT(DADCPSR1,0x800042C4,__READ,__power_status_bits);
__IO_REG32_BIT(DADCPSR2,0x800042C8,__READ,__power_status_bits);
__IO_REG32_BIT(DAIPSR1 ,0x800042CC,__READ,__power_status_bits);
__IO_REG32_BIT(DAIPSR2 ,0x800042D0,__READ,__power_status_bits);
__IO_REG32_BIT(DAOPSR1 ,0x800042D4,__READ,__power_status_bits);
__IO_REG32_BIT(DAOPSR2 ,0x800042D8,__READ,__power_status_bits);
__IO_REG32_BIT(DAOPSR3 ,0x800042DC,__READ,__power_status_bits);
__IO_REG32_BIT(DAIPSR3 ,0x800042E0,__READ,__power_status_bits);

/***************************************************************************
 **
 ** Enable select
 **
 ***************************************************************************/
__IO_REG32_BIT(APB0ESR0,0x800042E8,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(APB1ESR0,0x800042EC,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(APB2ESR ,0x800042F0,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(APB3ESR0,0x800042F4,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(MMIOESR0,0x800042F8,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(AHB0ESR ,0x800042FC,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(MCIESR0 ,0x80004300,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(MCIESR1 ,0x80004304,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(UARTESR0,0x80004308,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(FLSHESR0,0x80004314,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(FLSHESR1,0x80004318,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(FLSHESR2,0x8000431C,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(LCDESR0 ,0x80004320,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(LCDESR1 ,0x80004324,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DMAESR0 ,0x80004328,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DMAESR1 ,0x8000432C,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(USBESR0 ,0x80004330,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(CPUESR0 ,0x80004334,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(CPUESR1 ,0x80004338,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(CPUESR2 ,0x8000433C,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(RAMESR  ,0x80004340,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(ROMESR  ,0x80004344,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(EMCESR0 ,0x80004348,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(EMCESR1 ,0x8000434C,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(MMIOESR1,0x80004350,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(APB0ESR1,0x80004354,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(EVRTESR ,0x80004358,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(RTCESR0 ,0x8000435C,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(ADCESR0 ,0x80004360,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(ADCESR1 ,0x80004364,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(WDTESR  ,0x80004368,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(IOCESR  ,0x8000436C,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(CGUESR  ,0x80004370,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(SYSCESR ,0x80004374,__READ_WRITE,__enable_select1_bits);
__IO_REG32_BIT(APB1ESR1,0x80004378,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(T0ESR   ,0x8000437C,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(T1ESR   ,0x80004380,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(I2CESR  ,0x80004384,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(APB3ESR1,0x80004388,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(SCONESR ,0x8000438C,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(DAIESR0 ,0x80004390,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(DAOESR0 ,0x80004398,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(DSSESR1 ,0x8000439C,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(SAI1ESR ,0x800043A0,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(SAI4ESR ,0x800043AC,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(SAO1ESR ,0x800043B0,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(SAO2ESR ,0x800043B4,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(DDACESR0,0x800043BC,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(EDGEESR ,0x800043C0,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(DADCESR0,0x800043C4,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(UARTESR1,0x800043C8,__READ_WRITE,__enable_select_none_bits);
__IO_REG32_BIT(DDACESR1,0x800043CC,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DDACESR2,0x800043D0,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DADCESR1,0x800043D4,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DADCESR2,0x800043D8,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DAIESR1 ,0x800043DC,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DAIESR2 ,0x800043E0,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DAOESR1 ,0x800043E4,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DAOESR2 ,0x800043E8,__READ_WRITE,__enable_select3_bits);
__IO_REG32_BIT(DAOESR3 ,0x800043EC,__READ_WRITE,__enable_select3_bits);

/***************************************************************************
 **
 ** Software reset
 **
 ***************************************************************************/
__IO_REG32(APB0RES ,0x80004C18,__READ_WRITE);
__IO_REG32(APB0RES2,0x80004C1C,__READ_WRITE);
__IO_REG32(APB1RES ,0x80004C20,__READ_WRITE);
__IO_REG32(APB1RES2,0x80004C24,__READ_WRITE);
__IO_REG32(APB2RES ,0x80004C28,__READ_WRITE);
__IO_REG32(APB3RES ,0x80004C2C,__READ_WRITE);
__IO_REG32(APB3RES2,0x80004C30,__READ_WRITE);
__IO_REG32(MMIORES ,0x80004C34,__READ_WRITE);
__IO_REG32(AHB0RES ,0x80004C38,__READ_WRITE);
__IO_REG32(T0RES   ,0x80004C3C,__READ_WRITE);
__IO_REG32(T1RES   ,0x80004C40,__READ_WRITE);
__IO_REG32(MCIRES  ,0x80004C44,__READ_WRITE);
__IO_REG32(MCIRES2 ,0x80004C48,__READ_WRITE);
__IO_REG32(UARTRES ,0x80004C4C,__READ_WRITE);
__IO_REG32(I2CRES  ,0x80004C50,__READ_WRITE);
__IO_REG32(SCONRES ,0x80004C58,__READ_WRITE);
__IO_REG32(DAIRES  ,0x80004C60,__READ_WRITE);
__IO_REG32(DAORES  ,0x80004C68,__READ_WRITE);
__IO_REG32(DADCRES ,0x80004C6C,__READ_WRITE);
__IO_REG32(EDGERES ,0x80004C70,__READ_WRITE);
__IO_REG32(DDACRES ,0x80004C74,__READ_WRITE);
__IO_REG32(SAI1RES ,0x80004C78,__READ_WRITE);
__IO_REG32(SAI4RES ,0x80004C84,__READ_WRITE);
__IO_REG32(SAO1RES ,0x80004C88,__READ_WRITE);
__IO_REG32(SAO2RES ,0x80004C8C,__READ_WRITE);
__IO_REG32(FLSHRES ,0x80004C94,__READ_WRITE);
__IO_REG32(LCDRES  ,0x80004C98,__READ_WRITE);
__IO_REG32(DMARES  ,0x80004C9C,__READ_WRITE);
__IO_REG32(USBRES  ,0x80004CA0,__READ_WRITE);
__IO_REG32(EMCRES  ,0x80004CA4,__READ_WRITE);
__IO_REG32(MMIORES2,0x80004CA8,__READ_WRITE);

/***************************************************************************
 **
 ** Ext. memory controller
 **
 ***************************************************************************/
__IO_REG32_BIT(EMCCONTROL           ,0x80008000,__READ_WRITE,__emccontrol_bits);
__IO_REG32_BIT(EMCSTATUS            ,0x80008004,__READ      ,__emcstatus_bits);
__IO_REG32_BIT(EMCCONFIG            ,0x80008008,__READ_WRITE,__emcconfig_bits);
__IO_REG32_BIT(EMCDYNAMICCONTROL    ,0x80008020,__READ_WRITE,__emcdynamiccontrol_bits);
__IO_REG32_BIT(EMCDYNAMICREFRESH    ,0x80008024,__READ_WRITE,__emcdynamicrefresh_bits);
__IO_REG32_BIT(EMCDYNAMICREADCONFIG ,0x80008028,__READ_WRITE,__emcdynamicreadconfig_bits);
__IO_REG32_BIT(EMCDYNAMICRP         ,0x80008030,__READ_WRITE,__emcdynamicrp_bits);
__IO_REG32_BIT(EMCDYNAMICRAS        ,0x80008034,__READ_WRITE,__emcdynamicras_bits);
__IO_REG32_BIT(EMCDYNAMICSREX       ,0x80008038,__READ_WRITE,__emcdynamicsrex_bits);
__IO_REG32_BIT(EMCDYNAMICAPR        ,0x8000803C,__READ_WRITE,__emcdynamicapr_bits);
__IO_REG32_BIT(EMCDYNAMICDAL        ,0x80008040,__READ_WRITE,__emcdynamicdal_bits);
__IO_REG32_BIT(EMCDYNAMICWR         ,0x80008044,__READ_WRITE,__emcdynamicwr_bits);
__IO_REG32_BIT(EMCDYNAMICRC         ,0x80008048,__READ_WRITE,__emcdynamicrc_bits);
__IO_REG32_BIT(EMCDYNAMICRFC        ,0x8000804C,__READ_WRITE,__emcdynamicrfc_bits);
__IO_REG32_BIT(EMCDYNAMICXSR        ,0x80008050,__READ_WRITE,__emcdynamicxsr_bits);
__IO_REG32_BIT(EMCDYNAMICRRD        ,0x80008054,__READ_WRITE,__emcdynamicrrd_bits);
__IO_REG32_BIT(EMCDYNAMICMRD        ,0x80008058,__READ_WRITE,__emcdynamicmrd_bits);
__IO_REG32_BIT(EMCSTATICEXTENDEDWAIT,0x80008080,__READ_WRITE,__emcstaticextendedwait_bits);
__IO_REG32_BIT(EMCDYNAMICCONFIG     ,0x80008100,__READ_WRITE,__emcdynamicconfig_bits);
__IO_REG32_BIT(EMCDYNAMICRASCAS     ,0x80008104,__READ_WRITE,__emcdynamicrascas_bits);
__IO_REG32_BIT(EMCSTATICCONFIG0     ,0x80008200,__READ_WRITE,__emcstaticconfig0_bits);
__IO_REG32_BIT(EMCSTATICWAITWEN0    ,0x80008204,__READ_WRITE,__emcstaticwaitwen0_bits);
__IO_REG32_BIT(EMCSTATICWAITOEN0    ,0x80008208,__READ_WRITE,__emcstaticwaitoen0_bits);
__IO_REG32_BIT(EMCSTATICWAITRD0     ,0x8000820C,__READ_WRITE,__emcstaticwaitrd0_bits);
__IO_REG32_BIT(EMCSTATICWAITPAGE0   ,0x80008210,__READ_WRITE,__emcstaticwaitpage0_bits);
__IO_REG32_BIT(EMCSTATICWAITWR0     ,0x80008214,__READ_WRITE,__emcstaticwaitwr0_bits);
__IO_REG32_BIT(EMCSTATICWAITTURN0   ,0x80008218,__READ_WRITE,__emcstaticwaitturn0_bits);
__IO_REG32_BIT(EMCSTATICCONFIG1     ,0x80008220,__READ_WRITE,__emcstaticconfig0_bits);
__IO_REG32_BIT(EMCSTATICWAITWEN1    ,0x80008224,__READ_WRITE,__emcstaticwaitwen0_bits);
__IO_REG32_BIT(EMCSTATICWAITOEN1    ,0x80008228,__READ_WRITE,__emcstaticwaitoen0_bits);
__IO_REG32_BIT(EMCSTATICWAITRD1     ,0x8000822C,__READ_WRITE,__emcstaticwaitrd0_bits);
__IO_REG32_BIT(EMCSTATICWAITPAGE1   ,0x80008230,__READ_WRITE,__emcstaticwaitpage0_bits);
__IO_REG32_BIT(EMCSTATICWAITWR1     ,0x80008234,__READ_WRITE,__emcstaticwaitwr0_bits);
__IO_REG32_BIT(EMCSTATICWAITTURN1   ,0x80008238,__READ_WRITE,__emcstaticwaitturn0_bits);
__IO_REG32_BIT(EMCSTATICCONFIG2     ,0x80008240,__READ_WRITE,__emcstaticconfig0_bits);
__IO_REG32_BIT(EMCSTATICWAITWEN2    ,0x80008244,__READ_WRITE,__emcstaticwaitwen0_bits);
__IO_REG32_BIT(EMCSTATICWAITOEN2    ,0x80008248,__READ_WRITE,__emcstaticwaitoen0_bits);
__IO_REG32_BIT(EMCSTATICWAITRD2     ,0x8000824C,__READ_WRITE,__emcstaticwaitrd0_bits);
__IO_REG32_BIT(EMCSTATICWAITPAGE2   ,0x80008250,__READ_WRITE,__emcstaticwaitpage0_bits);
__IO_REG32_BIT(EMCSTATICWAITWR2     ,0x80008254,__READ_WRITE,__emcstaticwaitwr0_bits);
__IO_REG32_BIT(EMCSTATICWAITTURN2   ,0x80008258,__READ_WRITE,__emcstaticwaitturn0_bits);
__IO_REG32_BIT(EMCMISC              ,0x8000505C,__READ_WRITE,__emcmisc_bits);

/***************************************************************************
 **
 ** Interrupts
 **
 ***************************************************************************/
__IO_REG32_BIT(INT_PRIOMASK0,0x80300000,__READ_WRITE,__int_priomask0_bits);
__IO_REG32_BIT(INT_PRIOMASK1,0x80300004,__READ_WRITE,__int_priomask0_bits);
__IO_REG32_BIT(INT_VECTOR0  ,0x80300100,__READ_WRITE,__int_vector0_bits);
__IO_REG32_BIT(INT_VECTOR1  ,0x80300104,__READ_WRITE,__int_vector0_bits);
__IO_REG32_BIT(INT_PENDING  ,0x80300200,__READ,      __int_pending_bits);
__IO_REG32_BIT(INT_FEATURES ,0x80300300,__READ,      __int_features_bits);
__IO_REG32_BIT(INT_REQ1 ,0x80300404,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ2 ,0x80300408,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ3 ,0x8030040C,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ4 ,0x80300410,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ5 ,0x80300414,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ6 ,0x80300418,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ7 ,0x8030041C,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ8 ,0x80300420,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ9 ,0x80300424,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ10,0x80300428,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ11,0x8030042C,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ12,0x80300430,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ13,0x80300434,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ14,0x80300438,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ15,0x8030043C,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ16,0x80300440,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ17,0x80300444,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ18,0x80300448,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ19,0x8030044C,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ20,0x80300450,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ21,0x80300454,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ22,0x80300458,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ23,0x8030045C,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ24,0x80300460,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ25,0x80300464,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ26,0x80300468,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ27,0x8030046C,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ28,0x80300470,__READ_WRITE,__int_req_bits);
__IO_REG32_BIT(INT_REQ29,0x80300474,__READ_WRITE,__int_req_bits);

/***************************************************************************
 **
 ** Event router
 **
 ***************************************************************************/
__IO_REG32_BIT(EVAPR0 ,0x80000CC0,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVAPR1 ,0x80000CC4,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVAPR2 ,0x80000CC8,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVAPR3 ,0x80000CCC,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVATR0 ,0x80000CE0,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVATR1 ,0x80000CE4,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVATR2 ,0x80000CE8,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVATR3 ,0x80000CEC,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVECLR0,0x80000C20,__WRITE,     __igroup0_bits);
__IO_REG32_BIT(EVECLR1,0x80000C24,__WRITE,     __igroup1_bits);
__IO_REG32_BIT(EVECLR2,0x80000C28,__WRITE,     __igroup2_bits);
__IO_REG32_BIT(EVECLR3,0x80000C2C,__WRITE,     __igroup3_bits);
__IO_REG32_BIT(EVESET0,0x80000C40,__WRITE,     __igroup0_bits);
__IO_REG32_BIT(EVESET1,0x80000C44,__WRITE,     __igroup1_bits);
__IO_REG32_BIT(EVESET2,0x80000C48,__WRITE,     __igroup2_bits);
__IO_REG32_BIT(EVESET3,0x80000C4C,__WRITE,     __igroup3_bits);
__IO_REG32_BIT(EVRSR0 ,0x80000D20,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVRSR1 ,0x80000D24,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVRSR2 ,0x80000D28,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVRSR3 ,0x80000D2C,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVMASK0,0x80000C60,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVMASK1,0x80000C64,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVMASK2,0x80000C68,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVMASK3,0x80000C6C,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVMCLR0,0x80000C80,__WRITE,     __igroup0_bits);
__IO_REG32_BIT(EVMCLR1,0x80000C84,__WRITE,     __igroup1_bits);
__IO_REG32_BIT(EVMCLR2,0x80000C88,__WRITE,     __igroup2_bits);
__IO_REG32_BIT(EVMCLR3,0x80000C8C,__WRITE,     __igroup3_bits);
__IO_REG32_BIT(EVMSET0,0x80000CA0,__WRITE,     __igroup0_bits);
__IO_REG32_BIT(EVMSET1,0x80000CA4,__WRITE,     __igroup1_bits);
__IO_REG32_BIT(EVMSET2,0x80000CA8,__WRITE,     __igroup2_bits);
__IO_REG32_BIT(EVMSET3,0x80000CAC,__WRITE,     __igroup3_bits);
__IO_REG32_BIT(EVPEND0,0x80000C00,__READ,      __igroup0_bits);
__IO_REG32_BIT(EVPEND1,0x80000C04,__READ,      __igroup1_bits);
__IO_REG32_BIT(EVPEND2,0x80000C08,__READ,      __igroup2_bits);
__IO_REG32_BIT(EVPEND3,0x80000C0C,__READ,      __igroup3_bits);

__IO_REG32_BIT(EVIOMK0_0,0x80001400,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMK0_1,0x80001404,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMK0_2,0x80001408,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMK0_3,0x8000140C,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMK1_0,0x80001420,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMK1_1,0x80001424,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMK1_2,0x80001428,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMK1_3,0x8000142C,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMK2_0,0x80001440,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMK2_1,0x80001444,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMK2_2,0x80001448,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMK2_3,0x8000144C,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMK3_0,0x80001460,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMK3_1,0x80001464,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMK3_2,0x80001468,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMK3_3,0x8000146C,__READ_WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMK4_0,0x80001480,__READ_WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMK4_1,0x80001484,__READ_WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMK4_2,0x80001488,__READ_WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMK4_3,0x8000148C,__READ_WRITE,__igroup3_bits);

__IO_REG32_BIT(EVIOMC0_0,0x80001800,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMC0_1,0x80001804,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMC0_2,0x80001808,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMC0_3,0x8000180C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMC1_0,0x80001820,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMC1_1,0x80001824,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMC1_2,0x80001828,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMC1_3,0x8000182C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMC2_0,0x80001840,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMC2_1,0x80001844,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMC2_2,0x80001848,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMC2_3,0x8000184C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMC3_0,0x80001860,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMC3_1,0x80001864,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMC3_2,0x80001868,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMC3_3,0x8000186C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMC4_0,0x80001880,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMC4_1,0x80001884,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMC4_2,0x80001888,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMC4_3,0x8000188C,__WRITE,__igroup3_bits);

__IO_REG32_BIT(EVIOMS0_0,0x80001C00,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMS0_1,0x80001C04,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMS0_2,0x80001C08,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMS0_3,0x80001C0C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMS1_0,0x80001C20,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMS1_1,0x80001C24,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMS1_2,0x80001C28,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMS1_3,0x80001C2C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMS2_0,0x80001C40,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMS2_1,0x80001C44,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMS2_2,0x80001C48,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMS2_3,0x80001C4C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMS3_0,0x80001C60,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMS3_1,0x80001C64,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMS3_2,0x80001C68,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMS3_3,0x80001C6C,__WRITE,__igroup3_bits);
__IO_REG32_BIT(EVIOMS4_0,0x80001C80,__WRITE,__igroup0_bits);
__IO_REG32_BIT(EVIOMS4_1,0x80001C84,__WRITE,__igroup1_bits);
__IO_REG32_BIT(EVIOMS4_2,0x80001C88,__WRITE,__igroup2_bits);
__IO_REG32_BIT(EVIOMS4_3,0x80001C8C,__WRITE,__igroup3_bits);

__IO_REG32_BIT(EVIOP0_0 ,0x80001000,__READ,__igroup0_bits);
__IO_REG32_BIT(EVIOP0_1 ,0x80001004,__READ,__igroup1_bits);
__IO_REG32_BIT(EVIOP0_2 ,0x80001008,__READ,__igroup2_bits);
__IO_REG32_BIT(EVIOP0_3 ,0x8000100C,__READ,__igroup3_bits);
__IO_REG32_BIT(EVIOP1_0 ,0x80001020,__READ,__igroup0_bits);
__IO_REG32_BIT(EVIOP1_1 ,0x80001024,__READ,__igroup1_bits);
__IO_REG32_BIT(EVIOP1_2 ,0x80001028,__READ,__igroup2_bits);
__IO_REG32_BIT(EVIOP1_3 ,0x8000102C,__READ,__igroup3_bits);
__IO_REG32_BIT(EVIOP2_0 ,0x80001040,__READ,__igroup0_bits);
__IO_REG32_BIT(EVIOP2_1 ,0x80001044,__READ,__igroup1_bits);
__IO_REG32_BIT(EVIOP2_2 ,0x80001048,__READ,__igroup2_bits);
__IO_REG32_BIT(EVIOP2_3 ,0x8000104C,__READ,__igroup3_bits);
__IO_REG32_BIT(EVIOP3_0 ,0x80001060,__READ,__igroup0_bits);
__IO_REG32_BIT(EVIOP3_1 ,0x80001064,__READ,__igroup1_bits);
__IO_REG32_BIT(EVIOP3_2 ,0x80001068,__READ,__igroup2_bits);
__IO_REG32_BIT(EVIOP3_3 ,0x8000106C,__READ,__igroup3_bits);
__IO_REG32_BIT(EVIOP4_0 ,0x80001080,__READ,__igroup0_bits);
__IO_REG32_BIT(EVIOP4_1 ,0x80001084,__READ,__igroup1_bits);
__IO_REG32_BIT(EVIOP4_2 ,0x80001088,__READ,__igroup2_bits);
__IO_REG32_BIT(EVIOP4_3 ,0x8000108C,__READ,__igroup3_bits);

__IO_REG32_BIT(EVOUT     ,0x80000D40,__READ,__evout_bits);
__IO_REG32_BIT(EVFEATURES,0x80000E00,__READ,__evfeatures_bits);
/***************************************************************************
 **
 ** Timers
 **
 ***************************************************************************/
__IO_REG32(T0LOAD    ,0x80020000,__READ_WRITE);
__IO_REG32(T1LOAD    ,0x80020400,__READ_WRITE);
__IO_REG32(T0VALUE   ,0x80020004,__READ);
__IO_REG32(T1VALUE   ,0x80020404,__READ);
__IO_REG32_BIT(T0CTRL,0x80020008,__READ_WRITE,__t0ctrl_bits);
__IO_REG32_BIT(T1CTRL,0x80020408,__READ_WRITE,__t0ctrl_bits);
__IO_REG32(T0CLR     ,0x8002000C,__WRITE);
__IO_REG32(T1CLR     ,0x8002040C,__WRITE);

/***************************************************************************
 **
 ** WDT
 **
 ***************************************************************************/
__IO_REG32_BIT(WDT_SR ,0x80002800,__READ_WRITE,__wdt_sr_bits);
__IO_REG32_BIT(WDT_TCR,0x80002804,__READ_WRITE,__wdt_tcr_bits);
__IO_REG32(    WDT_TC ,0x80002808,__READ_WRITE);
__IO_REG32(    WDT_PR ,0x8000280C,__READ_WRITE);
__IO_REG32_BIT(WDT_MCR,0x80002814,__READ_WRITE,__wdt_mcr_bits);
__IO_REG32(    WDT_MR0,0x80002818,__READ_WRITE);
__IO_REG32(    WDT_MR1,0x8000281C,__READ_WRITE);
__IO_REG32_BIT(WDT_EMR,0x8000283C,__READ_WRITE,__wdt_emr_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(RTC_CFG,0x80005024,__READ_WRITE,__rtc_cfg_bits);
__IO_REG32_BIT(ILR    ,0x80002000,__READ_WRITE,__ilr_bits);
__IO_REG32_BIT(CTC    ,0x80002004,__READ,      __ctc_bits);
__IO_REG32_BIT(CCR    ,0x80002008,__READ_WRITE,__ccr_bits);
__IO_REG32_BIT(CIIR   ,0x8000200C,__READ_WRITE,__ciir_bits);
__IO_REG32_BIT(AMR    ,0x80002010,__READ_WRITE,__amr_bits);
__IO_REG32_BIT(CTIME0 ,0x80002014,__READ      ,__ctime0_bits);
__IO_REG32_BIT(CTIME1 ,0x80002018,__READ      ,__ctime1_bits);
__IO_REG32_BIT(CTIME2 ,0x8000201C,__READ      ,__ctime2_bits);
__IO_REG32_BIT(SEC    ,0x80002020,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(MIN    ,0x80002024,__READ_WRITE,__min_bits);
__IO_REG32_BIT(HOUR   ,0x80002028,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(DOM    ,0x8000202C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(DOW    ,0x80002030,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(DOY    ,0x80002034,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(MONTH  ,0x80002038,__READ_WRITE,__month_bits);
__IO_REG32_BIT(YEAR   ,0x8000203C,__READ_WRITE,__year_bits);
__IO_REG32_BIT(ALSEC  ,0x80002060,__READ_WRITE,__sec_bits);
__IO_REG32_BIT(ALMIN  ,0x80002064,__READ_WRITE,__min_bits);
__IO_REG32_BIT(ALHOUR ,0x80002068,__READ_WRITE,__hour_bits);
__IO_REG32_BIT(ALDOM  ,0x8000206C,__READ_WRITE,__dom_bits);
__IO_REG32_BIT(ALDOW  ,0x80002070,__READ_WRITE,__dow_bits);
__IO_REG32_BIT(ALDOY  ,0x80002074,__READ_WRITE,__doy_bits);
__IO_REG32_BIT(ALMON  ,0x80002078,__READ_WRITE,__month_bits);
__IO_REG32_BIT(ALYEAR ,0x8000207C,__READ_WRITE,__year_bits);

/***************************************************************************
 **
 ** UART AND IrDA
 **
 ***************************************************************************/
__IO_REG8(    RBR   ,0x80101000,__READ_WRITE);
#define THR RBR
#define DLL RBR
__IO_REG32_BIT(IER  ,0x80101004,__READ_WRITE,__ier_bits);
#define DLM      IER
#define DLM_bit  IER_bit

__IO_REG32_BIT(IIR  ,0x80101008,__READ_WRITE,__iir_bits);
#define FCR IIR
__IO_REG32_BIT(LCR  ,0x8010100C,__READ_WRITE,__lcr_bits);
__IO_REG32_BIT(_MCR  ,0x80101010,__READ_WRITE,__mcr_bits);
__IO_REG32_BIT(_LSR  ,0x80101014,__READ      ,__lsr_bits);
__IO_REG32_BIT(_MSR  ,0x80101018,__READ      ,__msr_bits);
__IO_REG32_BIT(SCR  ,0x8010101C,__READ_WRITE,__scr_bits);
__IO_REG32_BIT(ACR  ,0x80101020,__READ_WRITE,__acr_bits);
__IO_REG32_BIT(ICR  ,0x80101024,__READ_WRITE,__icr_bits);
__IO_REG32_BIT(FDR  ,0x80101028,__READ_WRITE,__fdr_bits);
__IO_REG32_BIT(_POP  ,0x80101030,__WRITE     ,__pop_bits);
__IO_REG32_BIT(MODE ,0x80101034,__READ_WRITE,__mode_bits);
__IO_REG32(    CFG  ,0x80101FD4,__READ);
__IO_REG32_BIT(INTCE,0x80101FD8,__WRITE     ,__ints_bits);
__IO_REG32_BIT(INTSE,0x80101FDC,__WRITE     ,__ints_bits);
__IO_REG32_BIT(INTS ,0x80101FE0,__READ      ,__ints_bits);
__IO_REG32_BIT(INTE ,0x80101FE4,__READ      ,__ints_bits);
__IO_REG32_BIT(INTCS,0x80101FE8,__WRITE     ,__intcs_bits);
__IO_REG32_BIT(INTSS,0x80101FEC,__WRITE     ,__intss_bits);

/***************************************************************************
 **
 ** GPDMA
 **
 ***************************************************************************/
__IO_REG32(    DMA0SOURCE,0x80103800,__READ_WRITE);
__IO_REG32(    DMA0DEST  ,0x80103804,__READ_WRITE);
__IO_REG32_BIT(DMA0LENGTH,0x80103808,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA0CONFIG,0x8010380C,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA0ENAB  ,0x80103810,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA0COUNT ,0x8010381C,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA1SOURCE,0x80103820,__READ_WRITE);
__IO_REG32(    DMA1DEST  ,0x80103824,__READ_WRITE);
__IO_REG32_BIT(DMA1LENGTH,0x80103828,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA1CONFIG,0x8010382C,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA1ENAB  ,0x80103830,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA1COUNT ,0x8010383C,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA2SOURCE,0x80103840,__READ_WRITE);
__IO_REG32(    DMA2DEST  ,0x80103844,__READ_WRITE);
__IO_REG32_BIT(DMA2LENGTH,0x80103848,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA2CONFIG,0x8010384C,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA2ENAB  ,0x80103850,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA2COUNT ,0x8010385C,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA3SOURCE,0x80103860,__READ_WRITE);
__IO_REG32(    DMA3DEST  ,0x80103864,__READ_WRITE);
__IO_REG32_BIT(DMA3LENGTH,0x80103868,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA3CONFIG,0x8010386C,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA3ENAB  ,0x80103870,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA3COUNT ,0x8010387C,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA4SOURCE,0x80103880,__READ_WRITE);
__IO_REG32(    DMA4DEST  ,0x80103884,__READ_WRITE);
__IO_REG32_BIT(DMA4LENGTH,0x80103888,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA4CONFIG,0x8010388C,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA4ENAB  ,0x80103890,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA4COUNT ,0x8010389C,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA5SOURCE,0x801038A0,__READ_WRITE);
__IO_REG32(    DMA5DEST  ,0x801038A4,__READ_WRITE);
__IO_REG32_BIT(DMA5LENGTH,0x801038A8,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA5CONFIG,0x801038AC,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA5ENAB  ,0x801038B0,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA5COUNT ,0x801038BC,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA6SOURCE,0x801038C0,__READ_WRITE);
__IO_REG32(    DMA6DEST  ,0x801038C4,__READ_WRITE);
__IO_REG32_BIT(DMA6LENGTH,0x801038C8,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA6CONFIG,0x801038CC,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA6ENAB  ,0x801038D0,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA6COUNT ,0x801038DC,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA7SOURCE,0x801038E0,__READ_WRITE);
__IO_REG32(    DMA7DEST  ,0x801038E4,__READ_WRITE);
__IO_REG32_BIT(DMA7LENGTH,0x801038E8,__READ_WRITE,__dma0length_bits);
__IO_REG32_BIT(DMA7CONFIG,0x801038EC,__READ_WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA7ENAB  ,0x801038F0,__READ_WRITE,__dma0enab_bits);
__IO_REG32_BIT(DMA7COUNT ,0x801038FC,__READ_WRITE,__dma0count_bits);
__IO_REG32(    DMA0ALTSOURCE,0x80103A00,__WRITE);
__IO_REG32(    DMA0ALTDEST  ,0x80103A04,__WRITE);
__IO_REG32_BIT(DMA0ALTLENGTH,0x80103A08,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA0ALTCONFIG,0x80103A0C,__WRITE,__dma0config_bits);
__IO_REG32(    DMA1ALTSOURCE,0x80103A10,__WRITE);
__IO_REG32(    DMA1ALTDEST  ,0x80103A14,__WRITE);
__IO_REG32_BIT(DMA1ALTLENGTH,0x80103A18,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA1ALTCONFIG,0x80103A1C,__WRITE,__dma0config_bits);
__IO_REG32(    DMA2ALTSOURCE,0x80103A20,__WRITE);
__IO_REG32(    DMA2ALTDEST  ,0x80103A24,__WRITE);
__IO_REG32_BIT(DMA2ALTLENGTH,0x80103A28,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA2ALTCONFIG,0x80103A2C,__WRITE,__dma0config_bits);
__IO_REG32(    DMA3ALTSOURCE,0x80103A30,__WRITE);
__IO_REG32(    DMA3ALTDEST  ,0x80103A34,__WRITE);
__IO_REG32_BIT(DMA3ALTLENGTH,0x80103A38,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA3ALTCONFIG,0x80103A3C,__WRITE,__dma0config_bits);
__IO_REG32(    DMA4ALTSOURCE,0x80103A40,__WRITE);
__IO_REG32(    DMA4ALTDEST  ,0x80103A44,__WRITE);
__IO_REG32_BIT(DMA4ALTLENGTH,0x80103A48,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA4ALTCONFIG,0x80103A4C,__WRITE,__dma0config_bits);
__IO_REG32(    DMA5ALTSOURCE,0x80103A50,__WRITE);
__IO_REG32(    DMA5ALTDEST  ,0x80103A54,__WRITE);
__IO_REG32_BIT(DMA5ALTLENGTH,0x80103A58,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA5ALTCONFIG,0x80103A5C,__WRITE,__dma0config_bits);
__IO_REG32(    DMA6ALTSOURCE,0x80103A60,__WRITE);
__IO_REG32(    DMA6ALTDEST  ,0x80103A64,__WRITE);
__IO_REG32_BIT(DMA6ALTLENGTH,0x80103A68,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA6ALTCONFIG,0x80103A6C,__WRITE,__dma0config_bits);
__IO_REG32(    DMA7ALTSOURCE,0x80103A70,__WRITE);
__IO_REG32(    DMA7A1LTDEST ,0x80103A74,__WRITE);
__IO_REG32_BIT(DMA7ALTLENGTH,0x80103A78,__WRITE,__dma0altlength_bits);
__IO_REG32_BIT(DMA7ALTCONFIG,0x80103A7C,__WRITE,__dma0config_bits);
__IO_REG32_BIT(DMA_ENABLE   ,0x80103C00,__READ_WRITE,__dma_enable_bits);
__IO_REG32_BIT(DMA_STAT     ,0x80103C04,__READ_WRITE,__dma_stat_bits);
__IO_REG32_BIT(DMA_IRQMASK  ,0x80103C08,__READ_WRITE,__dma_irqmask_bits);
__IO_REG32(    DMA_SOFTINT  ,0x80103C10,__WRITE);
__IO_REG32_BIT(DMA3EXTEN    ,0x80005048,__READ_WRITE,__dma3exten_bits);
__IO_REG32_BIT(DMA5EXTEN    ,0x8000504C,__READ_WRITE,__dma3exten_bits);

/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(I2RX   ,0x80020800,__READ_WRITE,__i2rx_bits);
#define I2TX I2RX
#define I2TX_bit I2RX_bit
__IO_REG32_BIT(I2STS  ,0x80020804,__READ      ,__i2sts_bits);
__IO_REG32_BIT(I2CTL  ,0x80020808,__READ_WRITE,__i2ctl_bits);
__IO_REG32_BIT(I2CLKHI,0x8002080C,__READ_WRITE,__i2clkhi_bits);
__IO_REG32_BIT(I2CLKLO,0x80020810,__READ_WRITE,__i2clklo_bits);
__IO_REG32_BIT(I2ADR  ,0x80020814,__READ_WRITE,__i2adr_bits);
__IO_REG32_BIT(I2RFL  ,0x80020818,__READ      ,__i2rfl_bits);
__IO_REG32_BIT(I2TFL  ,0x8002081C,__READ      ,__i2tfl_bits);
__IO_REG32_BIT(I2RXB  ,0x80020820,__READ      ,__i2rxb_bits);
__IO_REG32_BIT(I2TXB  ,0x80020824,__READ      ,__i2txb_bits);
__IO_REG32_BIT(I2TXS  ,0x80020828,__WRITE     ,__i2txs_bits);
__IO_REG32_BIT(I2STFL ,0x8002082C,__READ      ,__i2stfl_bits);

/***************************************************************************
 **
 ** A/D
 **
 ***************************************************************************/
__IO_REG32_BIT(ADCR0  ,0x80002400,__READ      ,__adcr0_bits);
__IO_REG32_BIT(ADCR1  ,0x80002404,__READ      ,__adcr0_bits);
__IO_REG32_BIT(ADCR2  ,0x80002408,__READ      ,__adcr0_bits);
__IO_REG32_BIT(ADCR3  ,0x8000240C,__READ      ,__adcr0_bits);
__IO_REG32_BIT(ADCR4  ,0x80002410,__READ      ,__adcr0_bits);
__IO_REG32_BIT(ADCR5  ,0x80002414,__READ      ,__adcr0_bits);
__IO_REG32_BIT(ADCCON ,0x80002420,__READ_WRITE,__adccon_bits);
__IO_REG32_BIT(ADCSEL ,0x80002424,__READ_WRITE,__adcsel_bits);
__IO_REG32_BIT(ADCINTE,0x80002428,__READ_WRITE,__adcinte_bits);
__IO_REG32_BIT(ADCINTS,0x8000242C,__READ      ,__adcints_bits);
__IO_REG32_BIT(ADCINTC,0x80002430,__WRITE     ,__adcintc_bits);
__IO_REG32_BIT(ADCPD  ,0x80005028,__READ_WRITE,__adcpd_bits);

/***************************************************************************
 **
 ** USB
 **
 ***************************************************************************/
__IO_REG32_BIT(USBDEVADR  ,0x80041000,__READ_WRITE,__usbdevadr_bits);
__IO_REG32_BIT(USBMAXSIZE, 0x80041004,__READ_WRITE,__usbmaxsize_bits);
__IO_REG32_BIT(USBETYPE   ,0x80041008,__READ_WRITE,__usbetype_bits);
__IO_REG32_BIT(USBMODE    ,0x8004100C,__READ_WRITE,__usbmode_bits);
__IO_REG32_BIT(USBINTCFG  ,0x80041010,__READ_WRITE,__usbintcfg_bits);
__IO_REG32_BIT(USBDCNT    ,0x8004101C,__READ_WRITE,__usbdcnt_bits);
__IO_REG32(    USBDATA    ,0x80041020,__READ_WRITE);
__IO_REG32_BIT(USBSHORT   ,0x80041024,__READ_WRITE,__usbshort_bits);
__IO_REG32_BIT(USBECTRL   ,0x80041028,__READ_WRITE,__usbectrl_bits);
__IO_REG32_BIT(USBEIX     ,0x8004102C,__READ_WRITE,__usbeix_bits);
__IO_REG32_BIT(USBFN      ,0x80041074,__READ_WRITE,__usbfn_bits);
__IO_REG32_BIT(USBSCRATCH ,0x80041078,__READ_WRITE,__usbscratch_bits);
__IO_REG32_BIT(USBLOCK    ,0x8004107C,__READ_WRITE,__usblock_bits);
__IO_REG32_BIT(USBTEST    ,0x80041084,__READ_WRITE,__usbtest_bits);
__IO_REG32_BIT(USBINTE    ,0x8004108C,__READ_WRITE,__usbinte_bits);
__IO_REG32_BIT(USBEINTE   ,0x80041090,__READ_WRITE,__usbeinte_bits);
__IO_REG32_BIT(USBINTSTAT ,0x80041094,__READ_WRITE,__usbintstat_bits);
__IO_REG32_BIT(USBEINTSTAT,0x80041098,__READ_WRITE,__usbeintstat_bits);
__IO_REG32_BIT(USBEINTCLR ,0x800410A0,__READ_WRITE,__usbeintclr_bits);
__IO_REG32_BIT(USBEINTSET ,0x800410A4,__READ_WRITE,__usbeintset_bits);
__IO_REG32_BIT(USBEINTP   ,0x800410A8,__READ_WRITE,__usbeintp_bits);
__IO_REG32_BIT(USBINTCLR  ,0x800410AC,__READ_WRITE,__usbintclr_bits);
__IO_REG32_BIT(USBINTSET  ,0x800410B0,__READ_WRITE,__usbintset_bits);
__IO_REG32_BIT(USBINTP    ,0x800410B4,__READ_WRITE,__usbintp_bits);
__IO_REG32_BIT(USBCLKEN   ,0x80005050,__READ_WRITE,__usbclken_bits);
/* DMA Engine Register */
__IO_REG32_BIT(UDMA0STAT  ,0x80040000,__READ_WRITE,__udma0stat_bits);
__IO_REG32_BIT(UDMA0CTRL  ,0x80040004,__READ_WRITE,__udma0ctrl_bits);
__IO_REG32(    UDMA0SRC   ,0x80040008,__READ_WRITE);
__IO_REG32(    UDMA0DEST  ,0x8004000C,__READ_WRITE);
__IO_REG32_BIT(UDMA0THROTL,0x80040010,__READ_WRITE,__udma0throtl_bits);
__IO_REG32(    UDMA0CNT   ,0x80040014,__READ_WRITE);
__IO_REG32_BIT(UDMA1STAT  ,0x80040040,__READ_WRITE,__udma0stat_bits);
__IO_REG32_BIT(UDMA1CTRL  ,0x80040044,__READ_WRITE,__udma0ctrl_bits);
__IO_REG32(    UDMA1SRC   ,0x80040048,__READ_WRITE);
__IO_REG32(    UDMA1DEST  ,0x8004004C,__READ_WRITE);
__IO_REG32_BIT(UDMA1THROTL,0x80040050,__READ_WRITE,__udma0throtl_bits);
__IO_REG32(    UDMA1CNT   ,0x80040054,__READ_WRITE);
__IO_REG32_BIT(UDMACTRL   ,0x80040400,__READ_WRITE,__udmactrl_bits);
__IO_REG32_BIT(UDMASOFTRES,0x80040404,__READ_WRITE,__udmasoftres_bits);
__IO_REG32_BIT(UDMASTAT   ,0x80040408,__READ_WRITE,__udmastat_bits);
__IO_REG32_BIT(UDMAINTSTAT,0x80040410,__READ_WRITE,__udmaintstat_bits);
__IO_REG32_BIT(UDMAINTEN  ,0x80040418,__READ_WRITE,__udmainten_bits);
__IO_REG32_BIT(UDMAINTDIS ,0x80040420,__READ_WRITE,__udmaintdis_bits);
__IO_REG32_BIT(UDMAINTSET ,0x80040428,__READ_WRITE,__udmaintset_bits);
__IO_REG32_BIT(UDMAINTCLR ,0x80040430,__READ_WRITE,__udmaintclr_bits);
__IO_REG32(    UDMAFCP0   ,0x80040500,__READ_WRITE);
__IO_REG32(    UDMAFCP1   ,0x80040504,__READ_WRITE);
__IO_REG32(    UDMAFCP2   ,0x80040508,__READ_WRITE);
__IO_REG32(    UDMAFCP3   ,0x8004050C,__READ_WRITE);

/***************************************************************************
 **
 ** I2S (DAI)
 **
 ***************************************************************************/
__IO_REG32_BIT(SIOCR   ,0x80200384,__READ_WRITE,__siocr_bits);
__IO_REG32_BIT(I2S_FMT ,0x80200380,__READ_WRITE,__i2s_fmt_bits);
__IO_REG32(    L16IN1  ,0x80200000,__READ);
__IO_REG32(    R16IN1  ,0x80200004,__READ);
__IO_REG32(    L24IN1  ,0x80200008,__READ);
__IO_REG32(    R24IN1  ,0x8020000C,__READ);
__IO_REG32_BIT(SAISTAT1,0x80200010,__READ_WRITE,__saistat1_bits);
__IO_REG32_BIT(SAIMASK1,0x80200014,__READ_WRITE,__saimask1_bits);
__IO_REG32(    L32IN1  ,0x80200020,__READ);
__IO_REG32(    R32IN1  ,0x80200040,__READ);
__IO_REG32(    LR32IN1 ,0x80200060,__READ);

/***************************************************************************
 **
 ** I2S (DAO)
 **
 ***************************************************************************/
__IO_REG32(    L16OUT1 ,0x80200200,__WRITE);
__IO_REG32(    R16OUT1 ,0x80200204,__WRITE);
__IO_REG32(    L24OUT1 ,0x80200208,__WRITE);
__IO_REG32(    R24OUT1 ,0x8020020C,__READ);
__IO_REG32_BIT(SAOSTAT1,0x80200210,__READ_WRITE,__saostat1_bits);
__IO_REG32_BIT(SAOMASK1,0x80200214,__READ_WRITE,__saomask1_bits);
__IO_REG32(    L32OUT1 ,0x80200220,__WRITE);
__IO_REG32(    R32OUT1 ,0x80200240,__WRITE);
__IO_REG32(    LR32OUT1,0x80200260,__WRITE);

/***************************************************************************
 **
 ** ADC
 **
 ***************************************************************************/
__IO_REG32_BIT(DAINCTRL,0x802003A4,__READ_WRITE,__dainctrl_bits);
__IO_REG32_BIT(DADCCTRL,0x802003A8,__READ_WRITE,__dadcctrl_bits);
__IO_REG32_BIT(DECCTRL ,0x802003AC,__READ_WRITE,__decctrl_bits);
__IO_REG32_BIT(DECSTAT ,0x802003B0,__READ      ,__decstat_bits);

/***************************************************************************
 **
 ** SAI4
 **
 ***************************************************************************/
__IO_REG32(    L16IN4  ,0x80200180,__READ);
__IO_REG32(    R16IN4  ,0x80200184,__READ);
__IO_REG32(    L24IN4  ,0x80200188,__READ);
__IO_REG32(    R24IN4  ,0x8020018C,__READ);
__IO_REG32_BIT(SAISTAT4,0x80200190,__READ_WRITE,__saistat1_bits);
__IO_REG32_BIT(SAIMASK4,0x80200194,__READ_WRITE,__saimask1_bits);
__IO_REG32(    L32IN4  ,0x802001A0,__READ);
__IO_REG32(    R32IN4  ,0x802001C0,__READ);
__IO_REG32(    LR32IN4 ,0x802001E0,__READ);

/***************************************************************************
 **
 ** DAC
 **
 ***************************************************************************/
__IO_REG32_BIT(DDACCTRL,0x80200398,__READ_WRITE,__ddacctrl_bits);
__IO_REG32_BIT(DDACSTAT,0x8020039C,__READ      ,__ddacstat_bits);
__IO_REG32_BIT(DDACSET ,0x802003A0,__READ_WRITE,__ddacset_bits);

/* SAO2 */
__IO_REG32(    L16OUT2 ,0x80200280,__WRITE);
__IO_REG32(    R16OUT2 ,0x80200284,__WRITE);
__IO_REG32(    L24OUT2 ,0x80200288,__WRITE);
__IO_REG32(    R24OUT2 ,0x8020028C,__WRITE);
__IO_REG32_BIT(SAOSTAT2,0x80200290,__READ_WRITE,__saostat1_bits);
__IO_REG32_BIT(SAOMASK2,0x80200294,__READ_WRITE,__saomask1_bits);
__IO_REG32(    L32OUT2 ,0x802002A0,__WRITE);
__IO_REG32(    R32OUT2 ,0x802002C0,__WRITE);
__IO_REG32(    LR32OUT2,0x802002E0,__WRITE);

/***************************************************************************
 **
 ** SD/MCI
 **
 ***************************************************************************/
__IO_REG32_BIT(MCIPOWER,     0x80100000,__READ_WRITE ,__mcipower_bits);
__IO_REG32_BIT(MCICLOCK,     0x80100004,__READ_WRITE ,__mciclock_bits);
__IO_REG32(    MCIARGUMENT,  0x80100008,__READ_WRITE);
__IO_REG32_BIT(MCICOMMAND,   0x8010000C,__READ_WRITE ,__mcicommand_bits);
__IO_REG32_BIT(MCIRESPCMD,   0x80100010,__READ       ,__mcirespcmd_bits);
__IO_REG32(    MCIRESPONSE0, 0x80100014,__READ);
__IO_REG32(    MCIRESPONSE1, 0x80100018,__READ);
__IO_REG32(    MCIRESPONSE2, 0x8010001C,__READ);
__IO_REG32(    MCIRESPONSE3, 0x80100020,__READ);
__IO_REG32(    MCIDATATIMER, 0x80100024,__READ_WRITE);
__IO_REG16(    MCIDATALENGTH,0x80100028,__READ_WRITE);
__IO_REG32_BIT(MCIDATACTRL,  0x8010002C,__READ_WRITE ,__mcidatactrl_bits);
__IO_REG16(    MCIDATACNT,   0x80100030,__READ);
__IO_REG32_BIT(MCISTATUS,    0x80100034,__READ       ,__mcistatus_bits);
__IO_REG32_BIT(MCICLEAR,     0x80100038,__WRITE      ,__mciclear_bits);
__IO_REG32_BIT(MCIMASK0,     0x8010003C,__READ_WRITE ,__mcimask0_bits);
__IO_REG32_BIT(MCIMASK1,     0x80100040,__READ_WRITE ,__mcimask0_bits);
__IO_REG32_BIT(MCIFIFOCNT,   0x80100048,__READ       ,__mcififocnt_bits);
__IO_REG32(    MCIFIFO0,     0x80100080,__READ_WRITE);
__IO_REG32(    MCIFIFO1,     0x80100084,__READ_WRITE);
__IO_REG32(    MCIFIFO2,     0x80100088,__READ_WRITE);
__IO_REG32(    MCIFIFO3,     0x8010008C,__READ_WRITE);
__IO_REG32(    MCIFIFO4,     0x80100090,__READ_WRITE);
__IO_REG32(    MCIFIFO5,     0x80100094,__READ_WRITE);
__IO_REG32(    MCIFIFO6,     0x80100098,__READ_WRITE);
__IO_REG32(    MCIFIFO7,     0x8010009C,__READ_WRITE);
__IO_REG32(    MCIFIFO8,     0x801000A0,__READ_WRITE);
__IO_REG32(    MCIFIFO9,     0x801000A4,__READ_WRITE);
__IO_REG32(    MCIFIFO10,    0x801000A8,__READ_WRITE);
__IO_REG32(    MCIFIFO11,    0x801000AC,__READ_WRITE);
__IO_REG32(    MCIFIFO12,    0x801000B0,__READ_WRITE);
__IO_REG32(    MCIFIFO13,    0x801000B4,__READ_WRITE);
__IO_REG32(    MCIFIFO14,    0x801000B8,__READ_WRITE);
__IO_REG32(    MCIFIFO15,    0x801000BC,__READ_WRITE);
__IO_REG32_BIT(MCICLKEN,     0x8000502C,__READ_WRITE,__mciclken_bits);

/***************************************************************************
 **
 ** LCD
 **
 ***************************************************************************/
__IO_REG32_BIT(LCDSTAT ,0x80103000,__READ      ,__lcdstat_bits);
__IO_REG32_BIT(LCDCTRL ,0x80103004,__READ_WRITE,__lcdctrl_bits);
__IO_REG32_BIT(LCDISTAT,0x80103008,__READ      ,__lcdistat_bits);
__IO_REG32_BIT(LCDICLR ,0x8010300C,__WRITE     ,__lcdimask_bits);
__IO_REG32_BIT(LCDIMASK,0x80103010,__READ_WRITE,__lcdimask_bits);
__IO_REG32_BIT(LCDREAD ,0x80103014,__WRITE     ,__lcdread_bits);
__IO_REG32_BIT(LCDIBYTE,0x80103020,__READ_WRITE,__lcdibyte_bits);
__IO_REG32_BIT(LCDDBYTE,0x80103030,__READ_WRITE,__lcddbyte_bits);
__IO_REG32(    LCDIWORD,0x80103040,__WRITE);
__IO_REG32_BIT(LCDDWORD,0x80103080,__WRITE     ,__lcddword_bits);

/***************************************************************************
 **
 ** I/O
 **
 ***************************************************************************/
__IO_REG32_BIT(MODE1_0 ,0x80003020,__READ_WRITE,__port0_bits);
__IO_REG32_BIT(MODE1_1 ,0x80003060,__READ_WRITE,__port1_bits);
__IO_REG32_BIT(MODE1_2 ,0x800030A0,__READ_WRITE,__port2_bits);
__IO_REG32_BIT(MODE1_3 ,0x800030E0,__READ_WRITE,__port3_bits);
__IO_REG32_BIT(MODE1_4 ,0x80003120,__READ_WRITE,__port4_bits);
__IO_REG32_BIT(MODE1_5 ,0x80003160,__READ_WRITE,__port5_bits);
__IO_REG32_BIT(MODE1_6 ,0x800031A0,__READ_WRITE,__port6_bits);
__IO_REG32_BIT(MODE1_7 ,0x800031E0,__READ_WRITE,__port7_bits);
__IO_REG32_BIT(MODE0_0 ,0x80003010,__READ_WRITE,__port0_bits);
__IO_REG32_BIT(MODE0_1 ,0x80003050,__READ_WRITE,__port1_bits);
__IO_REG32_BIT(MODE0_2 ,0x80003090,__READ_WRITE,__port2_bits);
__IO_REG32_BIT(MODE0_3 ,0x800030D0,__READ_WRITE,__port3_bits);
__IO_REG32_BIT(MODE0_4 ,0x80003110,__READ_WRITE,__port4_bits);
__IO_REG32_BIT(MODE0_5 ,0x80003150,__READ_WRITE,__port5_bits);
__IO_REG32_BIT(MODE0_6 ,0x80003190,__READ_WRITE,__port6_bits);
__IO_REG32_BIT(MODE0_7 ,0x800031D0,__READ_WRITE,__port7_bits);
__IO_REG32_BIT(MODE1S_0,0x80003024,__READ_WRITE,__port0_bits);
__IO_REG32_BIT(MODE1S_1,0x80003064,__READ_WRITE,__port1_bits);
__IO_REG32_BIT(MODE1S_2,0x800030A4,__READ_WRITE,__port2_bits);
__IO_REG32_BIT(MODE1S_3,0x800030E4,__READ_WRITE,__port3_bits);
__IO_REG32_BIT(MODE1S_4,0x80003124,__READ_WRITE,__port4_bits);
__IO_REG32_BIT(MODE1S_5,0x80003164,__READ_WRITE,__port5_bits);
__IO_REG32_BIT(MODE1S_6,0x800031A4,__READ_WRITE,__port6_bits);
__IO_REG32_BIT(MODE1S_7,0x800031E4,__READ_WRITE,__port7_bits);
__IO_REG32_BIT(MODE0S_0,0x80003014,__READ_WRITE,__port0_bits);
__IO_REG32_BIT(MODE0S_1,0x80003054,__READ_WRITE,__port1_bits);
__IO_REG32_BIT(MODE0S_2,0x80003094,__READ_WRITE,__port2_bits);
__IO_REG32_BIT(MODE0S_3,0x800030D4,__READ_WRITE,__port3_bits);
__IO_REG32_BIT(MODE0S_4,0x80003114,__READ_WRITE,__port4_bits);
__IO_REG32_BIT(MODE0S_5,0x80003154,__READ_WRITE,__port5_bits);
__IO_REG32_BIT(MODE0S_6,0x80003194,__READ_WRITE,__port6_bits);
__IO_REG32_BIT(MODE0S_7,0x800031D4,__READ_WRITE,__port7_bits);
__IO_REG32_BIT(MODE1C_0,0x80003028,__READ_WRITE,__port0_bits);
__IO_REG32_BIT(MODE1C_1,0x80003068,__READ_WRITE,__port1_bits);
__IO_REG32_BIT(MODE1C_2,0x800030A8,__READ_WRITE,__port2_bits);
__IO_REG32_BIT(MODE1C_3,0x800030E8,__READ_WRITE,__port3_bits);
__IO_REG32_BIT(MODE1C_4,0x80003128,__READ_WRITE,__port4_bits);
__IO_REG32_BIT(MODE1C_5,0x80003168,__READ_WRITE,__port5_bits);
__IO_REG32_BIT(MODE1C_6,0x800031A8,__READ_WRITE,__port6_bits);
__IO_REG32_BIT(MODE1C_7,0x800031E8,__READ_WRITE,__port7_bits);
__IO_REG32_BIT(MODE0C_0,0x80003018,__READ_WRITE,__port0_bits);
__IO_REG32_BIT(MODE0C_1,0x80003058,__READ_WRITE,__port1_bits);
__IO_REG32_BIT(MODE0C_2,0x80003098,__READ_WRITE,__port2_bits);
__IO_REG32_BIT(MODE0C_3,0x800030D8,__READ_WRITE,__port3_bits);
__IO_REG32_BIT(MODE0C_4,0x80003118,__READ_WRITE,__port4_bits);
__IO_REG32_BIT(MODE0C_5,0x80003158,__READ_WRITE,__port5_bits);
__IO_REG32_BIT(MODE0C_6,0x80003198,__READ_WRITE,__port6_bits);
__IO_REG32_BIT(MODE0C_7,0x800031D8,__READ_WRITE,__port7_bits);
__IO_REG32_BIT(PINS_0  ,0x80003000,__READ      ,__port0_bits);
__IO_REG32_BIT(PINS_1  ,0x80003040,__READ      ,__port1_bits);
__IO_REG32_BIT(PINS_2  ,0x80003080,__READ      ,__port2_bits);
__IO_REG32_BIT(PINS_3  ,0x800030C0,__READ      ,__port3_bits);
__IO_REG32_BIT(PINS_4  ,0x80003100,__READ      ,__port4_bits);
__IO_REG32_BIT(PINS_5  ,0x80003140,__READ      ,__port5_bits);
__IO_REG32_BIT(PINS_6  ,0x80003180,__READ      ,__port6_bits);
__IO_REG32_BIT(PINS_7  ,0x800031C0,__READ      ,__port7_bits);

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
#define RESETV  0x00  /* Reset                           */
#define UNDEFV  0x04  /* Undefined instruction           */
#define SWIV    0x08  /* Software interrupt              */
#define PABORTV 0x0c  /* Prefetch abort                  */
#define DABORTV 0x10  /* Data abort                      */
#define IRQV    0x18  /* Normal interrupt                */
#define FIQV    0x1c  /* Fast interrupt                  */

/***************************************************************************
 **
 **  VIC Interrupt channels
 **
 ***************************************************************************/
#define VIC_IRQ0        1       /* Event Router IRQ0 */
#define VIC_IRQ1        2       /* Event Router IRQ1 */
#define VIC_IRQ2        3       /* Event Router IRQ2 */
#define VIC_IRQ3        4       /* Event Router IRQ3 */
#define VIC_TIMER0      5
#define VIC_TIMER1      6
#define VIC_RTC         7       /* Counter Increment */
#define VIC_ALARM       8       /* Alarm */
#define VIC_ADC         9
#define VIC_MCI1        10
#define VIC_MCI2        11
#define VIC_UART        12      /* Receiver Error Flag; Receive Data Available */
                                /* Timeout; Transmit Holding Empty */
#define VIC_I2C         13      /* Transmit Done; Transmit Arbitration Failure */
                                /* Transmit No Ack; Master Transmit Data Request*/
                                /* Receive FIFO Full; Receive FIFO Empty */
                                /* Transmit FIFO Full; Transmit FIFO Empty */
#define VIC_SAI1        16
#define VIC_SAI4        19
#define VIC_SAO1        20
#define VIC_SAO2        21
#define VIC_FLASH       23      /* Programming or Erasure Complete */
#define VIC_LCD         24      /* LCD FIFO Empty, LCD FIFO Half Empty */
                                /* LCD FIFO Overrun, LCD Read Valid */
#define VIC_GPDMA       25
#define VIC_USB1        26
#define VIC_USB2        27
#define VIC_USB3        28
#define VIC_USB4        29

#endif    /* __IOLPC2888_H */

