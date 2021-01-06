/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    OKI ML696201
 **
 **    Used with ARM IAR c/c++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.2 $
 **
 ***************************************************************************/

#ifndef __IOML696201_H
#define __IOML696201_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"


/***************************************************************************
 ***************************************************************************
 **
 **    ML696201 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* ID Register (IDR) */
typedef struct {
  __REG32 REVISION         : 3;
  __REG32 TYPE             :10;
  __REG32                  :19;
} __idr_bits;

/* Clock Stop Register (CLKSTP) */
typedef struct {
  __REG32 SIO              : 1;
  __REG32 TIC              : 1;
  __REG32 CPUG             : 1;
  __REG32                  : 4;
  __REG32 STOP             : 1;
  __REG32                  :24;
} __clkstp_bits;

/* Clock (CGB) Control Register 0 (CGBCNT0) */
typedef struct {
  __REG32 FCLKGEAR         : 3;
  __REG32 HCLKGEAR0        : 1;
  __REG32 CCLKGEAR         : 3;
  __REG32 HCLKGEAR1        : 1;
  __REG32                  :24;
} __cgbcnt0_bits;

/* Clock Supply Wait Time Control Register (CKWT) */
typedef struct {
  __REG32 CKWT0            : 4;
  __REG32 CKWT1            : 4;
  __REG32                  :24;
} __ckwt_bits;

/* Remap Control Register (RMPCON) */
typedef struct {
  __REG32 RMPM             : 4;
  __REG32                  :28;
} __rmpcon_bits;

/* Clock (CGB) Control Register 2 (CGBCNT2) */
typedef struct {
  __REG32 STOP             : 1;
  __REG32                  :31;
} __cgbcnt2_bits;

/* IRQ Register (IRQ) */
typedef struct {
  __REG32 IRQ              :16;
  __REG32                  :16;
} __irq_bits;

/* IRQ Software Register (IRQS) */
typedef struct {
  __REG32                  : 1;
  __REG32 IRQS             : 1;
  __REG32                  :30;
} __irqs_bits;

/* FIQ Register (FIQ) */
typedef struct {
  __REG32 FIQ              : 1;
  __REG32                  :31;
} __fiq_bits;

/* FIQRAW Register (FIQRAW) */
typedef struct {
  __REG32 FIQRAW           : 1;
  __REG32                  :31;
} __fiqraw_bits;

/* FIQ Enable Register (FIQEN) */
typedef struct {
  __REG32 FIQEN            : 1;
  __REG32                  :31;
} __fiqen_bits;

/* IRQ Number Register (IRN) */
typedef struct {
  __REG32 IRN              : 7;
  __REG32                  :25;
} __irn_bits;

/* Current IRQ Level Register (CIL) */
typedef struct {
  __REG32                  : 1;
  __REG32 CIL              : 7;
  __REG32                  :24;
} __cil_bits;

/* IRQ Level Control Register 0 (ILC0) */
typedef struct {
  __REG32 ILR0             : 3;
  __REG32                  : 1;
  __REG32 ILR1             : 3;
  __REG32                  : 9;
  __REG32 ILR4             : 3;
  __REG32                  : 5;
  __REG32 ILR6             : 3;
  __REG32                  : 5;
} __ilc0_bits;

/* IRQ Level Control Register 1 (ILC1) */
typedef struct {
  __REG32 ILR8             : 3;
  __REG32                  : 1;
  __REG32 ILR9             : 3;
  __REG32                  : 1;
  __REG32 ILR10            : 3;
  __REG32                  : 1;
  __REG32 ILR11            : 3;
  __REG32                  : 1;
  __REG32 ILR12            : 3;
  __REG32                  : 1;
  __REG32 ILR13            : 3;
  __REG32                  : 1;
  __REG32 ILR14            : 3;
  __REG32                  : 1;
  __REG32 ILR15            : 3;
  __REG32                  : 1;
} __ilc1_bits;

/* Current IRQ Level Encode Register (CILE) */
typedef struct {
  __REG32 CILE             : 3;
  __REG32                  :29;
} __cile_bits;

/* IRQ Clear Register (IRCL) */
typedef struct {
  __REG32 IRCL             : 7;
  __REG32                  :25;
} __ircl_bits;

/* IRQA Register (IRQA) */
typedef struct {
  __REG32 IRQ              :16;
  __REG32                  :16;
} __irqa_bits;

/* IRQ Detect Mode Setting Register (IDM) */
typedef struct {
  __REG32 IDM16            : 1;
  __REG32                  : 1;
  __REG32 IDM18            : 1;
  __REG32                  : 1;
  __REG32 IDM20            : 1;
  __REG32                  : 1;
  __REG32 IDM22            : 1;
  __REG32                  : 1;
  __REG32 IDM24            : 1;
  __REG32                  : 1;
  __REG32 IDM26            : 1;
  __REG32                  : 1;
  __REG32 IDM28            : 1;
  __REG32                  : 1;
  __REG32 IDM30            : 1;
  __REG32                  :17;
} __idm_bits;

/* IRQ Level Control Register (ILC) */
typedef struct {
  __REG32 ILC16            : 3;
  __REG32                  : 1;
  __REG32 ILC18            : 3;
  __REG32                  : 1;
  __REG32 ILC20            : 3;
  __REG32                  : 1;
  __REG32 ILC22            : 3;
  __REG32                  : 1;
  __REG32 ILC24            : 3;
  __REG32                  : 1;
  __REG32 ILC26            : 3;
  __REG32                  : 1;
  __REG32 ILC28            : 3;
  __REG32                  : 1;
  __REG32 ILC30            : 3;
  __REG32                  : 1;
} __ilc_bits;

/* Bus Width Control Register (BWC) */
typedef struct {
  __REG32                  : 2;
  __REG32 ROMBW            : 2;
  __REG32 RAMBW            : 2;
  __REG32 IO0BW            : 2;
  __REG32 IO1BW            : 2;
  __REG32                  :22;
} __bwc_bits;

/* External ROM Access Control Register (ROMAC) */
typedef struct {
  __REG32 ROMTYPE          : 3;
  __REG32                  : 1;
  __REG32 BRST             : 1;
  __REG32                  :27;
} __romac_bits;

/* External SRAM Access Control Register (RAMAC) */
typedef struct {
  __REG32 RAMTYPE          : 3;
  __REG32                  : 1;
  __REG32 BRST             : 1;
  __REG32                  :27;
} __ramac_bits;

/* External I/O Bank 0 Access Control Register (IO0AC) */
typedef struct {
  __REG32 IO0TYPE          : 3;
  __REG32                  :29;
} __io0ac_bits;

/* External I/O Bank 1 Access Control Register (IO1AC) */
typedef struct {
  __REG32 IO1TYPE          : 3;
  __REG32                  :29;
} __io1ac_bits;

/* DRAM Bus Width Control Register (DBWC) */
typedef struct {
  __REG32 BWDRAM           : 2;
  __REG32                  :30;
} __dbwc_bits;

/* DRAM Control Register (DRMC) */
typedef struct {
  __REG32 AMUX             : 2;
  __REG32 ARCH             : 1;
  __REG32                  : 1;
  __REG32 PRELAT           : 1;
  __REG32                  : 1;
  __REG32 PDWN             : 1;
  __REG32 RFRSH            : 1;
  __REG32                  :24;
} __drmc_bits;

/* DRAM Property Parameter Control Register (DRPC) */
typedef struct {
  __REG32 DRAMSPEC         : 4;
  __REG32                  :28;
} __drpc_bits;

/* SDRAM Mode Register (SDMD) */
typedef struct {
  __REG32 LTMODE           : 1;
  __REG32                  : 6;
  __REG32 MODEWR           : 1;
  __REG32                  :24;
} __sdmd_bits;

/* DRAM Command Register (DCMD) */
typedef struct {
  __REG32 DRCMD            : 3;
  __REG32                  :29;
} __dcmd_bits;

/* DRAM Refresh Cycle Control Register 0 (RFSH0) */
typedef struct {
  __REG32 RCCON            : 1;
  __REG32                  :31;
} __rfsh0_bits;

/* DRAM Refresh Cycle Control Register 1 (RFSH1) */
typedef struct {
  __REG32 RFSEL1           :13;
  __REG32                  :19;
} __rfsh1_bits;

/* DRAM Power Down Control Register (PDWC) */
typedef struct {
  __REG32 PDCNT            : 4;
  __REG32                  :28;
} __pdwc_bits;

/* DMA Mode Register (DMAMOD) */
typedef struct {
  __REG32 PRI              : 1;
  __REG32                  :31;
} __dmamod_bits;

/* DMA Status Register (DMASTA) */
typedef struct {
  __REG32 STA0             : 1;
  __REG32 STA1             : 1;
  __REG32 STA2             : 1;
  __REG32 STA3             : 1;
  __REG32                  :28;
} __dmasta_bits;

/* DMA Termination Status Register (DMAINT) */
typedef struct {
  __REG32 IREQ0            : 1;
  __REG32 IREQ1            : 1;
  __REG32 IREQ2            : 1;
  __REG32 IREQ3            : 1;
  __REG32                  : 4;
  __REG32 ISTA0            : 1;
  __REG32 ISTA1            : 1;
  __REG32 ISTA2            : 1;
  __REG32 ISTA3            : 1;
  __REG32                  : 4;
  __REG32 ISTP0            : 1;
  __REG32 ISTP1            : 1;
  __REG32 ISTP2            : 1;
  __REG32 ISTP3            : 1;
  __REG32                  :12;
} __dmaint_bits;

/* DMA Channel Mask Registers (DMACMSK0 to 3) */
typedef struct {
  __REG32 MSK              : 1;
  __REG32                  :31;
} __dmacmskx_bits;

/* DMA Transfer Mode Registers (DMACTMOD0 to 3) */
typedef struct {
  __REG32 ARQ              : 1;
  __REG32 TSIZ             : 2;
  __REG32 SDP              : 1;
  __REG32 DDP              : 1;
  __REG32 BRQ              : 1;
  __REG32 IMK              : 1;
  __REG32                  :25;
} __dmactmodx_bits;

/* DMA Transfer Count Register (DMACSIZ0 to 3) */
typedef struct {
  __REG32 CSIZ             :17;
  __REG32                  :15;
} __dmacsizx_bits;

/* Port Output Registers (GPPOA, GPPOB, GPPOC, GPPOD, GPPOE, GPPOF) */
typedef struct {
  __REG32 GPPOA            :16;
  __REG32                  :16;
} __gppoa_bits;

typedef struct {
  __REG32 GPPOB            :16;
  __REG32                  :16;
} __gppob_bits;

typedef struct {
  __REG32 GPPOC            :16;
  __REG32                  :16;
} __gppoc_bits;

typedef struct {
  __REG32 GPPOD            :16;
  __REG32                  :16;
} __gppod_bits;

typedef struct {
  __REG32 GPPOE            :16;
  __REG32                  :16;
} __gppoe_bits;

typedef struct {
  __REG32 GPPOF            :16;
  __REG32                  :16;
} __gppof_bits;

/* Port Input Registers (GPPIA, GPPIB, GPPIC, GPPID, GPPIE, GPPIF) */
typedef struct {
  __REG32 GPPIA            :16;
  __REG32                  :16;
} __gppia_bits;

typedef struct {
  __REG32 GPPIB            :16;
  __REG32                  :16;
} __gppib_bits;

typedef struct {
  __REG32 GPPIC            :16;
  __REG32                  :16;
} __gppic_bits;

typedef struct {
  __REG32 GPPID            :16;
  __REG32                  :16;
} __gppid_bits;

typedef struct {
  __REG32 GPPIE            :16;
  __REG32                  :16;
} __gppie_bits;

typedef struct {
  __REG32 GPPIF            :16;
  __REG32                  :16;
} __gppif_bits;

/* Port Mode Registers (GPPMA, GPPMB, GPPMC, GPPMD, GPPME, GPPMF) */
typedef struct {
  __REG32 GPPMA            :16;
  __REG32                  :16;
} __gppma_bits;

typedef struct {
  __REG32 GPPMB            :16;
  __REG32                  :16;
} __gppmb_bits;

typedef struct {
  __REG32 GPPMC            :16;
  __REG32                  :16;
} __gppmc_bits;

typedef struct {
  __REG32 GPPMD            :16;
  __REG32                  :16;
} __gppmd_bits;

typedef struct {
  __REG32 GPPME            :16;
  __REG32                  :16;
} __gppme_bits;

typedef struct {
  __REG32 GPPMF            :16;
  __REG32                  :16;
} __gppmf_bits;

/* Port E Interrupt Enable Register (GPIEE) */
typedef struct {
  __REG32                  :12;
  __REG32 GPIED            : 4;
  __REG32                  :16;
} __gpiee_bits;

/* Port E Interrupt Polarity Register (GPIPE) */
typedef struct {
  __REG32                  :12;
  __REG32 GPIPD            : 4;
  __REG32                  :16;
} __gpipe_bits;

/* Port E Interrupt Status Register (GPISE) */
typedef struct {
  __REG32                  :12;
  __REG32 GPISE            : 4;
  __REG32                  :16;
} __gpise_bits;

/* Port E Interrupt Mode Register (GPIME) */
typedef struct {
  __REG32                  :12;
  __REG32 GPIME            : 4;
  __REG32                  :16;
} __gpime_bits;

/* Watchdog Timer Control Register (WDTCON) */
typedef struct {
  __REG32 WDTCON           : 8;
  __REG32                  :24;
} __wdtcon_bits;

/* Time Base Counter Control Register (WDTBCON) */
typedef struct {
  __REG32 WDCLK            : 2;
  __REG32                  : 1;
  __REG32 ITM              : 1;
  __REG32 ITEN             : 1;
  __REG32                  : 1;
  __REG32 OFINTMODE        : 1;
  __REG32 WDHLT            : 1;
  __REG32                  :24;
} __wdtbcon_bits;

/* Status Register (WDSTAT) */
typedef struct {
  __REG32 RSTSTATUS        : 1;
  __REG32                  : 3;
  __REG32 WDTIST           : 1;
  __REG32 IVTIST           : 1;
  __REG32                  :26;
} __wdstat_bits;

/* System Timer Enable Register (TMEN) */
typedef struct {
  __REG32 TCEN             : 1;
  __REG32                  :31;
} __tmen_bits;

/* System Timer Reload Register (TMRLR) */
typedef struct {
  __REG32 TMRLR            :16;
  __REG32                  :16;
} __tmrlr_bits;

/* System Timer Overflow Register (TMOVFR) */
typedef struct {
  __REG32 OVF              : 1;
  __REG32                  :31;
} __tmovfr_bits;

/* Timer Control Registers (TIMECNTL0–2) */
typedef struct {
  __REG32 MODE             : 1;
  __REG32                  : 2;
  __REG32 START            : 1;
  __REG32 IE               : 1;
  __REG32 CLKSEL           : 3;
  __REG32                  :24;
} __timecntlx_bits;

/* Timer Base Registers (TIMEBASE0–2) */
typedef struct {
  __REG32 TIMEBASE         :16;
  __REG32                  :16;
} __timebasex_bits;

/* Timer Counter Registers (TIMECNT0–2) */
typedef struct {
  __REG32 TIMECNT          :16;
  __REG32                  :16;
} __timecntx_bits;

/* Timer Compare Registers (TIMECMP0–2) */
typedef struct {
  __REG32 TIMECMP          :16;
  __REG32                  :16;
} __timecmpx_bits;

/* Timer Status Registers (TIMESTAT0–2) */
typedef struct {
  __REG32 STATUS           : 1;
  __REG32                  :31;
} __timestatx_bits;

/* PWM Register (PWR) */
typedef struct {
  __REG32 PWR              :16;
  __REG32                  :16;
} __pwr_bits;

/* PWM Cycle Register (PWCY) */
typedef struct {
  __REG32 PWCY             :16;
  __REG32                  :16;
} __pwcy_bits;

/* PWM Counter (PWC) */
typedef struct {
  __REG32 PWC              :16;
  __REG32                  :16;
} __pwc_bits;

/* PWM Control Register (PWCON) */
typedef struct {
  __REG32 PWRUN            : 1;
  __REG32 PWCK             : 2;
  __REG32                  : 3;
  __REG32 INTIE            : 1;
  __REG32 PWCOV            : 1;
  __REG32                  :24;
} __pwcon_bits;

/* PWM Interrupt Status Register (PWINTSTS) */
typedef struct {
  __REG32 INTCLR           : 1;
  __REG32                  : 7;
  __REG32 INTS             : 1;
  __REG32                  :23;
} __pwintsts_bits;

/* Transmit/Receive Buffer Register (SIOBUF) */
typedef struct {
  __REG32 SIOBUF           : 8;
  __REG32                  :24;
} __siobuf_bits;

/* SIO Status Register (SIOSTA) */
typedef struct {
  __REG32 FERR             : 1;
  __REG32 OERR             : 1;
  __REG32 PERR             : 1;
  __REG32                  : 1;
  __REG32 RVIRQ            : 1;
  __REG32 TRIRQ            : 1;
  __REG32                  :26;
} __siosta_bits;

/* SIO Control Register (SIOCON) */
typedef struct {
  __REG32 LN               : 1;
  __REG32 PEN              : 1;
  __REG32 EVN              : 1;
  __REG32 TSTB             : 1;
  __REG32                  :28;
} __siocon_bits;

/* Baud Rate Control Register (SIOBCN) */
typedef struct {
  __REG32                  : 4;
  __REG32 BGRUN            : 1;
  __REG32                  :27;
} __siobcn_bits;

/* Baud Rate Timer Register (SIOBT) */
typedef struct {
  __REG32 SIOBT            : 8;
  __REG32                  :24;
} __siobt_bits;

/* SIO Test Control Register (SIOTCN) */
typedef struct {
  __REG32 MFERR            : 1;
  __REG32 WPERR            : 1;
  __REG32                  : 5;
  __REG32 LBTST            : 1;
  __REG32                  :24;
} __siotcn_bits;

/* A/D Control 1 Register (ADCON1) */
typedef struct {
  __REG32 ADSTM            : 3;
  __REG32                  : 1;
  __REG32 STS              : 1;
  __REG32                  :27;
} __adcon1_bits;

/* A/D Control 2 Register (ADCON2) */
typedef struct {
  __REG32 ACKSEL           : 2;
  __REG32                  :30;
} __adcon2_bits;

/* A/D Interrupt Control Register (ADINT) */
typedef struct {
  __REG32 INTSN            : 1;
  __REG32 INTST            : 1;
  __REG32 ADSNIE           : 1;
  __REG32 ADSTIE           : 1;
  __REG32                  :28;
} __adint_bits;

/* A/D Result (0 to 3) Registers (ADR0 to ADR3) */
typedef struct {
  __REG32 DT0              :10;
  __REG32                  :22;
} __adr0_bits;

typedef struct {
  __REG32 DT1              :10;
  __REG32                  :22;
} __adr1_bits;

typedef struct {
  __REG32 DT2              :10;
  __REG32                  :22;
} __adr2_bits;

typedef struct {
  __REG32 DT3              :10;
  __REG32                  :22;
} __adr3_bits;

/* SSIO Transmit/Receive Buffer Registers (SSIOBUF1, SSIOBUF0) */
typedef struct {
  __REG32 SIOBUF           : 8;
  __REG32                  :24;
} __ssiobufx_bits;

/* SSIO Transmit/Receive Status Registers (SSIOSTA1, SSIOSTA0) */
typedef struct {
  __REG32 BUSY0            : 1;
  __REG32                  : 4;
  __REG32 S0SFCT0          : 1;
  __REG32 S0SFTC1          : 1;
  __REG32 S0SFTC2          : 1;
  __REG32                  :24;
} __ssiosta0_bits;

typedef struct {
  __REG32 BUSY1            : 1;
  __REG32                  : 4;
  __REG32 S1SFCT0          : 1;
  __REG32 S1SFTC1          : 1;
  __REG32 S1SFTC2          : 1;
  __REG32                  :24;
} __ssiosta1_bits;

/* SSIO Transmit/Receive Control Registers (SSIOCON1, SSIOCON0) */
typedef struct {
  __REG32 S0SFTCK0         : 1;
  __REG32 S0SFTCK1         : 1;
  __REG32 S0SFTCK2         : 1;
  __REG32                  : 1;
  __REG32 SFTSLV0          : 1;
  __REG32 SLMSB0           : 1;
  __REG32 SCK0INV          : 1;
  __REG32 S0RST            : 1;
  __REG32                  :24;
} __ssiocon0_bits;

typedef struct {
  __REG32 S1SFTCK0         : 1;
  __REG32 S1SFTCK1         : 1;
  __REG32 S1SFTCK2         : 1;
  __REG32                  : 1;
  __REG32 SFTSLV1          : 1;
  __REG32 SLMSB1           : 1;
  __REG32 SCK1INV          : 1;
  __REG32 S1RST            : 1;
  __REG32                  :24;
} __ssiocon1_bits;

/* SSIO Interrupt Request Registers (SSIOINTR1, SSIOINTR0) */
typedef struct {
  __REG32 TRCEND0          : 1;
  __REG32 BUFEMP0          : 1;
  __REG32                  :30;
} __ssiointr0_bits;

typedef struct {
  __REG32 TRCEND1          : 1;
  __REG32 BUFEMP1          : 1;
  __REG32                  :30;
} __ssiointr1_bits;

/* SSIO Interrupt Enable Registers (SSIOINTEN1, SSIOINTEN0) */
typedef struct {
  __REG32 TRCENDIE0        : 1;
  __REG32 BUFEMPIE0        : 1;
  __REG32                  :30;
} __ssiointen0_bits;

typedef struct {
  __REG32 TRCENDIE1        : 1;
  __REG32 BUFEMPIE1        : 1;
  __REG32                  :30;
} __ssiointen1_bits;

/* SSIO DMA Transfer Registers (SSIODMAC1, SSIODMAC0) */
typedef struct {
  __REG32 S0DMAMOD         : 1;
  __REG32                  : 3;
  __REG32 TRC0SW           : 1;
  __REG32                  :27;
} __ssiodmac0_bits;

typedef struct {
  __REG32 S1DMAMOD         : 1;
  __REG32                  : 3;
  __REG32 TRC1SW           : 1;
  __REG32                  :27;
} __ssiodmac1_bits;

/* SSIO Test Control Registers (SSIOTSCON1, SSIOTSCON0) */
typedef struct {
  __REG32                  : 7;
  __REG32 LBTST0           : 1;
  __REG32                  :24;
} __ssiotscon0_bits;

typedef struct {
  __REG32                  : 7;
  __REG32 LBTST1           : 1;
  __REG32                  :24;
} __ssiotscon1_bits;

/* I2C Bus Control Register (I2CCON) */
typedef struct {
  __REG32 I2CEN            : 1;
  __REG32 I2COC            : 1;
  __REG32 STCM             : 1;
  __REG32 RESTR            : 1;
  __REG32 START            : 1;
  __REG32                  :27;
} __i2ccon_bits;

/* I2C Bus Slave Address Mode Setting Register (I2CSAD) */
typedef struct {
  __REG32 I2CRW            : 1;
  __REG32 SAD0             : 1;
  __REG32 SAD1             : 1;
  __REG32 SAD2             : 1;
  __REG32 SAD3             : 1;
  __REG32 SAD4             : 1;
  __REG32 SAD5             : 1;
  __REG32 SAD6             : 1;
  __REG32                  :24;
} __i2csad_bits;

/* I2C Bus Transfer Speed Setting Register (I2CCLR) */
typedef struct {
  __REG32 I2CMD            : 1;
  __REG32                  :31;
} __i2cclr_bits;

/* I2C Bus Status Register (I2CSR) */
typedef struct {
  __REG32 I2CDAK           : 1;
  __REG32 I2CAAK           : 1;
  __REG32                  :30;
} __i2csr_bits;

/* I2C Bus Interrupt Request Register (I2CIR) */
typedef struct {
  __REG32 I2CIR            : 1;
  __REG32                  :31;
} __i2cir_bits;

/* I2C Bus Interrupt Mask Register (I2CIMR) */
typedef struct {
  __REG32 I2CMF            : 1;
  __REG32                  :31;
} __i2cimr_bits;

/* I2C Bus Transmit/Receive Data Setting Register (I2CDR) */
typedef struct {
  __REG32 I2CD0            : 1;
  __REG32 I2CD1            : 1;
  __REG32 I2CD2            : 1;
  __REG32 I2CD3            : 1;
  __REG32 I2CD4            : 1;
  __REG32 I2CD5            : 1;
  __REG32 I2CD6            : 1;
  __REG32 I2CD7            : 1;
  __REG32                  :24;
} __i2cdr_bits;

/* RTC Control Register (RTCCON) */
typedef struct {
  __REG32 RTCE             : 1;
  __REG32                  :31;
} __rtccon_bits;

/* RTC Status Register (RTCST) */
typedef struct {
  __REG32 INT              : 1;
  __REG32                  :31;
} __rtcst_bits;

/* Power Down Mask Register (PDMASK) */
typedef struct {
  __REG32 RTCEN            : 1;
  __REG32                  :31;
} __pdmask_bits;

/* Module Clock Stop Register (MCKST) */
typedef struct {
  __REG32 CKSTDMAC         : 1;
  __REG32 CKSTDRAM         : 1;
  __REG32 CKSTI2ST         : 1;
  __REG32 CKSTI2SR         : 1;
  __REG32 CKSTNFC          : 1;
  __REG32 CKSTNFB          : 1;
  __REG32 XSYSCLKEN        : 1;
  __REG32                  :25;
} __mckst_bits;

/* PIO Pin Switching Register (PIOCTL) */
typedef struct {
  __REG32 PIOCTL           :16;
  __REG32                  :16;
} __pioctl_bits;

/* I2S Control Register (I2SCNTL) */
typedef struct {
  __REG32 I2SSCLC          : 2;
  __REG32 I2SCKO           : 2;
  __REG32 I2SCLKSEL        : 2;
  __REG32 I2SOUT           : 1;
  __REG32 I2SPLLEN         : 1;
  __REG32 I2SOSCST         : 1;
  __REG32 I2SCNTCLR        : 1;
  __REG32                  :22;
} __i2scntl_bits;

/* OTHER Configuration Register (OCONFIG) */
typedef struct {
  __REG32 FRRST            : 1;
  __REG32                  :31;
} __oconfig_bits;

/* Test Register (TST) */
typedef struct {
  __REG32                  : 5;
  __REG32 WDTTST           : 1;
  __REG32 USBTST           : 1;
  __REG32                  :25;
} __tst_bits;

/* I2S Transceiver FIFO Register (I2SFIFOO) */
typedef struct {
  __REG32 I2SFIFOO_LOW     :16;
  __REG32 I2SFIFOO_HIGH    :16;
} __i2sfifoo_bits;


/* I2S Transceiver Control Register 0 (I2SCONO0) */
typedef struct {
  __REG32 SFSO             : 1;
  __REG32                  : 1;
  __REG32 MSBO             : 1;
  __REG32 WSLO             : 1;
  __REG32 DLYO             : 1;
  __REG32 RUNO             : 1;
  __REG32 FSO0             : 1;
  __REG32 FSO1             : 1;
  __REG32                  :24;
} __i2scono0_bits;

/* I2S Transceiver Control Register 1 (I2SCONO1) */
typedef struct {
  __REG32 CLRO             : 1;
  __REG32 CLKO             : 1;
  __REG32 MSTO             : 1;
  __REG32                  :29;
} __i2scono1_bits;

/* I2S Transceiver Almost Full Threshold Value Setting Register (I2SAFRO) */
typedef struct {
  __REG32                  : 4;
  __REG32 AFO04            : 1;
  __REG32 AFO05            : 1;
  __REG32 AFO06            : 1;
  __REG32 AFO07            : 1;
  __REG32 AFO08            : 1;
  __REG32 AFO09            : 1;
  __REG32 AFO10            : 1;
  __REG32 AFO11            : 1;
  __REG32                  :20;
} __i2safro_bits;

/* I2S Transceiver Almost Empty Threshold Value Setting Register (I2SAERO) */
typedef struct {
  __REG32                  : 4;
  __REG32 AEO04            : 1;
  __REG32 AEO05            : 1;
  __REG32 AEO06            : 1;
  __REG32 AEO07            : 1;
  __REG32 AEO08            : 1;
  __REG32 AEO09            : 1;
  __REG32 AEO10            : 1;
  __REG32 AEO11            : 1;
  __REG32                  :20;
} __i2saero_bits;

/* I2S Transceiver Interrupt Mask Register (I2SIMRO) */
typedef struct {
  __REG32 FMO              : 1;
  __REG32 AFMO             : 1;
  __REG32 EMO              : 1;
  __REG32 AEMO             : 1;
  __REG32                  :28;
} __i2simro_bits;

/* I2S Transceiver Interrupt Status Register (I2SISTO) */
typedef struct {
  __REG32 FIO              : 1;
  __REG32 AFIO             : 1;
  __REG32 EIO              : 1;
  __REG32 AEIO             : 1;
  __REG32                  :28;
} __i2sisto_bits;

/* I2S Transceiver FIFO Write Address Register (I2SWADRO) */
typedef struct {
  __REG32 WAO00            : 1;
  __REG32 WAO01            : 1;
  __REG32 WAO02            : 1;
  __REG32 WAO03            : 1;
  __REG32 WAO04            : 1;
  __REG32 WAO05            : 1;
  __REG32 WAO06            : 1;
  __REG32 WAO07            : 1;
  __REG32 WAO08            : 1;
  __REG32 WAO09            : 1;
  __REG32 WAO10            : 1;
  __REG32 WAO11            : 1;
  __REG32                  :20;
} __i2swadro_bits;

/* I2S Transceiver FIFO Read Address Register (2SRADRO) */
typedef struct {
  __REG32 RAO00            : 1;
  __REG32 RAO01            : 1;
  __REG32 RAO02            : 1;
  __REG32 RAO03            : 1;
  __REG32 RAO04            : 1;
  __REG32 RAO05            : 1;
  __REG32 RAO06            : 1;
  __REG32 RAO07            : 1;
  __REG32 RAO08            : 1;
  __REG32 RAO09            : 1;
  __REG32 RAO10            : 1;
  __REG32 RAO11            : 1;
  __REG32                  :20;
} __i2sradro_bits;

/* I2S Transceiver FIFO Occupied Data Size Register (I2SDNOO) */
typedef struct {
  __REG32 DNO00            : 1;
  __REG32 DNO01            : 1;
  __REG32 DNO02            : 1;
  __REG32 DNO03            : 1;
  __REG32 DNO04            : 1;
  __REG32 DNO05            : 1;
  __REG32 DNO06            : 1;
  __REG32 DNO07            : 1;
  __REG32 DNO08            : 1;
  __REG32 DNO09            : 1;
  __REG32 DNO10            : 1;
  __REG32 DNO11            : 1;
  __REG32                  :20;
} __i2sdnoo_bits;

/* I2S Receiver FIFO Register (I2SFIFOI) */
typedef struct {
  __REG32 I2SFIFOI_LOW     :16;
  __REG32 I2SFIFOI_HIGH    :16;
} __i2sfifoi_bits;


/* I2S Receiver Control Register 0 (I2SCONI0) */
typedef struct {
  __REG32 SFSI             : 1;
  __REG32                  : 1;
  __REG32 MSBI             : 1;
  __REG32 WSLI             : 1;
  __REG32 DLYI             : 1;
  __REG32 RUNI             : 1;
  __REG32 FSI0             : 1;
  __REG32 FSI1             : 1;
  __REG32                  :24;
} __i2sconi0_bits;

/* I2S Receiver Control Register 1 (I2SCONI1) */
typedef struct {
  __REG32 CLRI             : 1;
  __REG32 CLKI             : 1;
  __REG32 MSTI             : 1;
  __REG32                  :29;
} __i2sconi1_bits;

/* I2S Receiver Almost Full Threshold Value Setting Register (I2SAFRI) */
typedef struct {
  __REG32                  : 4;
  __REG32 AFI04            : 1;
  __REG32 AFI05            : 1;
  __REG32 AFI06            : 1;
  __REG32 AFI07            : 1;
  __REG32 AFI08            : 1;
  __REG32 AFI09            : 1;
  __REG32 AFI10            : 1;
  __REG32 AFI11            : 1;
  __REG32                  :20;
} __i2safri_bits;

/* I2S Receiver Almost Empty Threshold Value Setting Register (I2SAERI) */
typedef struct {
  __REG32                  : 4;
  __REG32 AEI04            : 1;
  __REG32 AEI05            : 1;
  __REG32 AEI06            : 1;
  __REG32 AEI07            : 1;
  __REG32 AEI08            : 1;
  __REG32 AEI09            : 1;
  __REG32 AEI10            : 1;
  __REG32 AEI11            : 1;
  __REG32                  :20;
} __i2saeri_bits;

/* I2S Receiver Interrupt Mask Register (I2SIMRI) */
typedef struct {
  __REG32 FMI              : 1;
  __REG32 AFMI             : 1;
  __REG32 EMI              : 1;
  __REG32 AEMI             : 1;
  __REG32                  :28;
} __i2simri_bits;

/* I2S Receiver Interrupt Status Register (I2SISTI) */
typedef struct {
  __REG32 FII              : 1;
  __REG32 AFII             : 1;
  __REG32 EII              : 1;
  __REG32 AEII             : 1;
  __REG32                  :28;
} __i2sisti_bits;

/* I2S Receiver FIFO Write Address Register (I2SWADRI) */
typedef struct {
  __REG32 WAI00            : 1;
  __REG32 WAI01            : 1;
  __REG32 WAI02            : 1;
  __REG32 WAI03            : 1;
  __REG32 WAI04            : 1;
  __REG32 WAI05            : 1;
  __REG32 WAI06            : 1;
  __REG32 WAI07            : 1;
  __REG32 WAI08            : 1;
  __REG32 WAI09            : 1;
  __REG32 WAI10            : 1;
  __REG32 WAI11            : 1;
  __REG32                  :20;
} __i2swadri_bits;

/* I2S Receiver FIFO Read Address Register (2SRADRI) */
typedef struct {
  __REG32 RAI00            : 1;
  __REG32 RAI01            : 1;
  __REG32 RAI02            : 1;
  __REG32 RAI03            : 1;
  __REG32 RAI04            : 1;
  __REG32 RAI05            : 1;
  __REG32 RAI06            : 1;
  __REG32 RAI07            : 1;
  __REG32 RAI08            : 1;
  __REG32 RAI09            : 1;
  __REG32 RAI10            : 1;
  __REG32 RAI11            : 1;
  __REG32                  :20;
} __i2sradri_bits;

/* I2S Receiver FIFO Occupied Data Size Register (I2SDNOI) */
typedef struct {
  __REG32 DNI00            : 1;
  __REG32 DNI01            : 1;
  __REG32 DNI02            : 1;
  __REG32 DNI03            : 1;
  __REG32 DNI04            : 1;
  __REG32 DNI05            : 1;
  __REG32 DNI06            : 1;
  __REG32 DNI07            : 1;
  __REG32 DNI08            : 1;
  __REG32 DNI09            : 1;
  __REG32 DNI10            : 1;
  __REG32 DNI11            : 1;
  __REG32                  :20;
} __i2sdnoi_bits;
	
/* Media Bank Register (MBANK) */
typedef struct {
  __REG32 MBANK            : 3;
  __REG32                  :29;
} __mbank_bits;

/* Media Sequencer Control Register (MSCTRL) */
typedef struct {
  __REG32 START            : 1;
  __REG32 DIR              : 1;
  __REG32 DLEN             : 2;
  __REG32 HEAD             : 2;
  __REG32 ECC              : 1;
  __REG32 PARITY           : 1;
  __REG32                  :24;
} __msctrl_bits;

/* Media Sequencer Wait Register (MSWAIT) */
typedef struct {
  __REG32 WAITR            : 2;
  __REG32 WAITW            : 2;
  __REG32 DISFWT           : 1;
  __REG32                  :27;
} __mswait_bits;

/* Media Sequencer Status Register (MSSTS) */
typedef struct {
  __REG32 MSCMP            : 1;
  __REG32 MSRDY            : 1;
  __REG32 ECCOK            : 1;
  __REG32 PRTYOK           : 1;
  __REG32 MRDY             : 1;
  __REG32                  :27;
} __mssts_bits;

/* Media Sequencer Interrupt Enable Register (MINTENBL) */
typedef struct {
  __REG32 INTENBL          : 1;
  __REG32                  :31;
} __mintenbl_bits;

/* Media Sequencer Error Status Register (MSERR) */
typedef struct {
  __REG32 ECC1UNC          : 1;
  __REG32 ECC1COR          : 1;
  __REG32 ECC2UNC          : 1;
  __REG32 ECC2COR          : 1;
  __REG32 PAR1ERR          : 1;
  __REG32 PAR2ERR          : 1;
  __REG32                  : 2;
  __REG32 ECC3UNC          : 1;
  __REG32 ECC3COR          : 1;
  __REG32 ECC4UNC          : 1;
  __REG32 ECC4COR          : 1;
  __REG32 PAR3ERR          : 1;
  __REG32 PAR4ERR          : 1;
  __REG32                  : 2;
  __REG32 ECC5UNC          : 1;
  __REG32 ECC5COR          : 1;
  __REG32 ECC6UNC          : 1;
  __REG32 ECC6COR          : 1;
  __REG32 PAR5ERR          : 1;
  __REG32 PAR6ERR          : 1;
  __REG32                  : 2;
  __REG32 ECC7UNC          : 1;
  __REG32 ECC7COR          : 1;
  __REG32 ECC8UNC          : 1;
  __REG32 ECC8COR          : 1;
  __REG32 PAR7ERR          : 1;
  __REG32 PAR8ERR          : 1;
  __REG32                  : 2;
} __mserr_bits;

/* Media Command Register (MMCMD) */
typedef struct {
  __REG32 MMCMD            : 8;
  __REG32                  :24;
} __mmcmd_bits;

/* Media Address Register (MMADR) */
typedef struct {
  __REG32 MMADR            : 8;
  __REG32                  :24;
} __mmadr_bits;

/* Media Select Register (MMSEL) */
typedef struct {
  __REG32 CLE              : 1;
  __REG32 ALE              : 1;
  __REG32                  :30;
} __mmsel_bits;

/* Media Data Read Control Register (MMRDCTL) */
typedef struct {
  __REG32 MDWAIT           : 2;
  __REG32                  : 2;
  __REG32 MDRDIS           : 1;
  __REG32                  :27;
} __mmrdctl_bits;

/* Media Section Option Register (MOPTION) */
typedef struct {
  __REG32 MDSTART          : 1;
  __REG32 PRTYMD           : 1;
  __REG32                  :30;
} __moption_bits;

/* Media Section Read Data Storage Register (MMRDDATA) */
typedef struct {
  __REG32 MMRDDATA         : 8;
  __REG32                  :24;
} __mmrddata_bits;

/* ECC Line Parity Register x (ECCLPx) (x = 1, 3, 5, 7) */
typedef struct {
  __REG32 LP1              :16;
  __REG32 LP2              :16;
} __ecclp1_bits;

typedef struct {
  __REG32 LP3              :16;
  __REG32 LP4              :16;
} __ecclp3_bits;

typedef struct {
  __REG32 LP5              :16;
  __REG32 LP6              :16;
} __ecclp5_bits;

typedef struct {
  __REG32 LP7              :16;
  __REG32 LP8              :16;
} __ecclp7_bits;

/* ECC Column Parity Register x (ECCCPx) (x = 1, 3, 5, 7) */
typedef struct {
  __REG32 CP1              :16;
  __REG32 CP2              :16;
} __ecccp1_bits;

typedef struct {
  __REG32 CP3              :16;
  __REG32 CP4              :16;
} __ecccp3_bits;

typedef struct {
  __REG32 CP5              :16;
  __REG32 CP6              :16;
} __ecccp5_bits;

typedef struct {
  __REG32 CP7              :16;
  __REG32 CP8              :16;
} __ecccp7_bits;

/* ECC Error Pointer Register x (ECCERRx) (x = 1, 3, 5, 7) */
typedef struct {
  __REG32 BYTEP1           : 8;
  __REG32 BITP1            : 3;
  __REG32                  : 5;
  __REG32 BYTEP2           : 8;
  __REG32 BITP2            : 3;
  __REG32                  : 5;
} __eccerr1_bits;

typedef struct {
  __REG32 BYTEP3           : 8;
  __REG32 BITP3            : 3;
  __REG32                  : 5;
  __REG32 BYTEP4           : 8;
  __REG32 BITP4            : 3;
  __REG32                  : 5;
} __eccerr3_bits;

typedef struct {
  __REG32 BYTEP5           : 8;
  __REG32 BITP5            : 3;
  __REG32                  : 5;
  __REG32 BYTEP6           : 8;
  __REG32 BITP6            : 3;
  __REG32                  : 5;
} __eccerr5_bits;

typedef struct {
  __REG32 BYTEP7           : 8;
  __REG32 BITP7            : 3;
  __REG32                  : 5;
  __REG32 BYTEP8           : 8;
  __REG32 BITP8            : 3;
  __REG32                  : 5;
} __eccerr7_bits;

/* Redundancy Part Reserve Data Register x (HREVx) (x = 1, 3, 5, 7) */
typedef struct {
  __REG32 REV1D1           : 8;
  __REG32 REV1D2           : 8;
  __REG32 REV2D3           : 8;
  __REG32 REV2D4           : 8;
} __hrev1_bits;

typedef struct {
  __REG32 REV3D1           : 8;
  __REG32 REV3D2           : 8;
  __REG32 REV4D3           : 8;
  __REG32 REV4D4           : 8;
} __hrev3_bits;

typedef struct {
  __REG32 REV5D1           : 8;
  __REG32 REV5D2           : 8;
  __REG32 REV6D3           : 8;
  __REG32 REV6D4           : 8;
} __hrev5_bits;

typedef struct {
  __REG32 REV7D1           : 8;
  __REG32 REV7D2           : 8;
  __REG32 REV8D3           : 8;
  __REG32 REV8D4           : 8;
} __hrev7_bits;

/* Redundancy Part Data/Block Status & Block Address Register x (HSTADx) (x = 1, 3, 5, 7) */
typedef struct {
  __REG32 DSTS1            : 8;
  __REG32 BSTS1            : 8;
  __REG32 BA1ADH           : 3;
  __REG32 BA1FX            : 5;
  __REG32 BA1P             : 1;
  __REG32 BA1ADL           : 7;
} __hstad1_bits;

typedef struct {
  __REG32 DSTS3            : 8;
  __REG32 BSTS3            : 8;
  __REG32 BA3ADH           : 3;
  __REG32 BA3FX            : 5;
  __REG32 BA3P             : 1;
  __REG32 BA3ADL           : 7;
} __hstad3_bits;

typedef struct {
  __REG32 DSTS5            : 8;
  __REG32 BSTS5            : 8;
  __REG32 BA5ADH           : 3;
  __REG32 BA5FX            : 5;
  __REG32 BA5P             : 1;
  __REG32 BA5ADL           : 7;
} __hstad5_bits;

typedef struct {
  __REG32 DSTS7            : 8;
  __REG32 BSTS7            : 8;
  __REG32 BA7ADH           : 3;
  __REG32 BA7FX            : 5;
  __REG32 BA7P             : 1;
  __REG32 BA7ADL           : 7;
} __hstad7_bits;

/* Redundancy Part ECCx+1-High Register & Redundancy Part ECCx+1-Low/Block Address x+1 Register (HECCx+1) (x = 1, 3, 5, 7) */
typedef struct {
  __REG32 ECC2H            : 8;
  __REG32 ECC2M            : 8;
  __REG32 ECC2L            : 8;
  __REG32 BA2ADH           : 3;
  __REG32 BA2FX            : 5;
} __hecc2_bits;

typedef struct {
  __REG32 ECC4H            : 8;
  __REG32 ECC4M            : 8;
  __REG32 ECC4L            : 8;
  __REG32 BA4ADH           : 3;
  __REG32 BA4FX            : 5;
} __hecc4_bits;

typedef struct {
  __REG32 ECC6H            : 8;
  __REG32 ECC6M            : 8;
  __REG32 ECC6L            : 8;
  __REG32 BA6ADH           : 3;
  __REG32 BA6FX            : 5;
} __hecc6_bits;

typedef struct {
  __REG32 ECC8H            : 8;
  __REG32 ECC8M            : 8;
  __REG32 ECC8L            : 8;
  __REG32 BA8ADH           : 3;
  __REG32 BA8FX            : 5;
} __hecc8_bits;

/* Redundancy Part ECCx-High/Block Address x+1 Register & Redundancy Part ECCx-Low Register (HECCx) */
typedef struct {
  __REG32 BA2P             : 1;
  __REG32 BA2ADL           : 7;
  __REG32 ECC1H            : 8;
  __REG32 ECC1M            : 8;
  __REG32 ECC1L            : 8;
} __hecc1_bits;

typedef struct {
  __REG32 BA4P             : 1;
  __REG32 BA4ADL           : 7;
  __REG32 ECC3H            : 8;
  __REG32 ECC3M            : 8;
  __REG32 ECC3L            : 8;
} __hecc3_bits;

typedef struct {
  __REG32 BA6P             : 1;
  __REG32 BA6ADL           : 7;
  __REG32 ECC5H            : 8;
  __REG32 ECC5M            : 8;
  __REG32 ECC5L            : 8;
} __hecc5_bits;

typedef struct {
  __REG32 BA8P             : 1;
  __REG32 BA8ADL           : 7;
  __REG32 ECC7H            : 8;
  __REG32 ECC7M            : 8;
  __REG32 ECC7L            : 8;
} __hecc7_bits;

/* Media Data Register (MMDATA) */
typedef struct {
  __REG32 MMDATA           : 8;
  __REG32                  :24;
} __mmdata_bits;

/* Primary/Secondary IDE channel DMA Control (BMICP/BMICS*1) */
typedef struct {
  __REG16 DMASTART         : 1;
  __REG16                  : 2;
  __REG16 DMADIR           : 1;
  __REG16                  :12;
} __bmicp_bits;

/* Primary/Secondary IDE Channel DMA Status (BMISP/BMISS*1) */
typedef struct {
  __REG16 IDEACT           : 1;
  __REG16 DMAERROR         : 1;
  __REG16 INTRSTAT         : 1;
  __REG16 IORDYINT         : 1;
  __REG16 EOTINT           : 1;
  __REG16 DMAEN0           : 1;
  __REG16 DMAEN1           : 1;
  __REG16 SIMPLEX          : 1;
  __REG16 HERRINT          : 1;
  __REG16                  : 7;
} __bmisp_bits;

/* Primary/Secondary IDE Channel DMA Descriptor Pointer (BMIDTPP/BMIDTPS*1) */
typedef struct {
  __REG32                  : 2;
  __REG32 BMIDTP           :30;
} __bmidtpp_bits;

/* DMA Controller Feature Configuration Register (DMAFEAT) */
typedef struct {
  __REG32 MULTPRDT         : 1;
  __REG32 EOTINTEN         : 1;
  __REG32                  :30;
} __dmafeat_bits;

/* IDE Clock Control Register (CLKCTL) */
typedef struct {
  __REG32 ICLKDIS          : 1;
  __REG32                  :31;
} __clkctl_bits;

/* Primary/Secondary Channel IDE Timing Control (IDETIMP/IDETIMS*1) */
typedef struct {
  __REG16 PIOFTIM0         : 1;
  __REG16 RDYSEN0          : 1;
  __REG16 PREPOST0         : 1;
  __REG16 DMAFTIM0         : 1;
  __REG16 PIOFTIM1         : 1;
  __REG16 RDYSEN1          : 1;
  __REG16 PREPOST1         : 1;
  __REG16 DMAFTIM1         : 1;
  __REG16 RDYRCVRY         : 2;
  __REG16                  : 2;
  __REG16 RDYSMPL          : 2;
  __REG16 SLVTIMEN         : 1;
  __REG16 IDEEN            : 1;
} __idetimp_bits;

/* Slave IDE Timing Enable (SIDETIM) */
typedef struct {
  __REG8  RDYRCYP1         : 2;
  __REG8  RDYSMPP1         : 2;
  __REG8  RDYRCYS1         : 2;
  __REG8  RDYSMPS1         : 2;
} __sidetim_bits;

/* IDE Cable ID Status (IDESTAT) */
typedef struct {
  __REG8  CABLEIDS         : 1;
  __REG8  CABLEIDP         : 1;
  __REG8                   : 6;
} __idestat_bits;

/* UltraDMA Control (UDMACTL) */
typedef struct {
  __REG16 UDMAP0           : 1;
  __REG16 UDMAP1           : 1;
  __REG16 UDMAS0           : 1;
  __REG16 UDMAS1           : 1;
  __REG16                  :12;
} __udmactl_bits;

/* UltraDMA Timing Control (UDMATIM) */
typedef struct {
  __REG16 TCYCP0           : 3;
  __REG16                  : 1;
  __REG16 TCYCP1           : 3;
  __REG16                  : 1;
  __REG16 TCYCS0           : 3;
  __REG16                  : 1;
  __REG16 TCYCS1           : 3;
  __REG16                  : 1;
} __udmatim_bits;

/* IDE Timing Override Control (TIMORIDE) */
typedef struct {
  __REG32 TIMORIDE         : 1;
  __REG32                  :31;
} __timoride_bits;

/* 8-Bit Register Access Strobe Width (REGSTB) */
typedef struct {
  __REG32 REGSTB0          : 7;
  __REG32                  : 1;
  __REG32 REGSTB1          : 7;
  __REG32                  : 1;
  __REG32 REGSTB           : 7;
  __REG32                  : 9;
} __regstb_bits;

/* 8-Bit Register Access Recovery Time (REGRCVR) */
typedef struct {
  __REG32 REGRCVR0         : 7;
  __REG32                  : 1;
  __REG32 REGRCVR1         : 7;
  __REG32                  : 1;
  __REG32 REGRCVR          : 7;
  __REG32                  : 9;
} __regrcvr_bits;

/* Data Register Access Strobe Width (DATSTB) */
typedef struct {
  __REG32 DATSTB0          : 7;
  __REG32                  : 1;
  __REG32 DATSTB1          : 7;
  __REG32                  :17;
} __datstb_bits;

/* Data Register Access Recovery Time (DATRCVR) */
typedef struct {
  __REG32 DATRCVR0         : 7;
  __REG32                  : 1;
  __REG32 DATRCVR1         : 7;
  __REG32                  :17;
} __datrcvr_bits;

/* DMA Access Strove Width (DMASTB) */
typedef struct {
  __REG32 DMASTB0          : 7;
  __REG32                  : 1;
  __REG32 DMASTB1          : 7;
  __REG32                  :17;
} __dmastb_bits;

/* DMA Access Recovery Time (DMARCVR) */
typedef struct {
  __REG32 DMARCVR0         : 7;
  __REG32                  : 1;
  __REG32 DMARCVR1         : 7;
  __REG32                  :17;
} __dmarcvr_bits;

/* UltraDMA Access Strobe Width (UDMASTB) */
typedef struct {
  __REG32 UDMASTB0         : 4;
  __REG32                  : 4;
  __REG32 UDMASTB1         : 4;
  __REG32                  :20;
} __udmastb_bits;

/* UltraDMA ready-to-pause Time (UDMATRP) */
typedef struct {
  __REG32 UDMATRP0         : 5;
  __REG32                  : 3;
  __REG32 UDMATRP1         : 5;
  __REG32                  :19;
} __udmatrp_bits;

/* UltraDMA tENV Timing Parameter (UDMATENV) */
typedef struct {
  __REG32 UDMTENV0         : 4;
  __REG32 UDMTENV1         : 4;
  __REG32                  :24;
} __udmatenv_bits;

/* Reset Pin Control (PINCTL) */
typedef struct {
  __REG32 RESET            : 1;
  __REG32 RSTMODE          : 1;
  __REG32                  :30;
} __pinctl_bits;

/* IORDY Timer(IORDYTMR) */
typedef struct {
  __REG32 IORDYTMR         :18;
  __REG32                  :14;
} __iordytmr_bits;

/* Revision Register (Rev) */
typedef struct {
  __REG16 Revision         : 8;
  __REG16 RevInv           : 8;
} __rev_bits;

/* System Control Register (SysCtl) */
typedef struct {
  __REG16 SR               : 1;
  __REG16 PD               : 1;
  __REG16                  : 2;
  __REG16 RWA              : 1;
  __REG16 PDCtl            : 1;
  __REG16 PUCtl            : 1;
  __REG16 SelfPwr          : 1;
  __REG16                  : 8;
} __sysctl_bits;

/* DMA Configuration Register(DMACfg) */
typedef struct {
  __REG16                  : 3;
  __REG16 DMA_EP           : 3;
  __REG16                  : 1;
  __REG16 DMAEnb           : 1;
  __REG16 DREQItvl         : 4;
  __REG16                  : 4;
} __dmacfg_bits;

/* DMA Control Register (DMACtl) */
typedef struct {
  __REG16                  : 4;
  __REG16 DMAStrt          : 1;
  __REG16                  :11;
} __dmactl_bits;

/* Interrupt Status Register (IntStt) */
typedef struct {
  __REG16 SOFStt           : 1;
  __REG16 USBRstAstStt     : 1;
  __REG16 USBRstDastStt    : 1;
  __REG16 SpendStt         : 1;
  __REG16 AwkStt           : 1;
  __REG16                  : 3;
  __REG16 EP0EvtStt        : 1;
  __REG16 EPaEvtStt        : 1;
  __REG16 EPbEvtStt        : 1;
  __REG16 EPcEvtStt        : 1;
  __REG16 EPdEvtStt        : 1;
  __REG16 EPeEvtStt        : 1;
  __REG16 EPfEvtStt        : 1;
  __REG16                  : 1;
} __intstt_bits;

/* Interrupt Enable Register (IntEnb) */
typedef struct {
  __REG16 SOFEnb           : 1;
  __REG16 USBRstAstEnb     : 1;
  __REG16 USBRstDastEnb    : 1;
  __REG16 SpendEnb         : 1;
  __REG16 AwkEnb           : 1;
  __REG16                  : 3;
  __REG16 EP0EvtEnb        : 1;
  __REG16 EPaEvtEnb        : 1;
  __REG16 EPbEvtEnb        : 1;
  __REG16 EPcEvtEnb        : 1;
  __REG16 EPdEvtEnb        : 1;
  __REG16 EPeEvtEnb        : 1;
  __REG16 EPfEvtEnb        : 1;
  __REG16                  : 1;
} __intenb_bits;

/* Setup Data 1 Register (SetUpData1) */
typedef struct {
  __REG16 bmRequestType    : 8;
  __REG16 bRequest         : 8;
} __setupdata1_bits;

/* Setup Data 2 Register (SetUpData2) */
typedef struct {
  __REG16 wValueLSB        : 8;
  __REG16 wValueMSB        : 8;
} __setupdata2_bits;

/* Setup Data 3 Register (SetUpData3) */
typedef struct {
  __REG16 wIndexLSB        : 8;
  __REG16 wIndexMSB        : 8;
} __setupdata3_bits;

/* Setup Data 4 Register (SetUpData4) */
typedef struct {
  __REG16 wLengthLSB       : 8;
  __REG16 wLengthMSB       : 8;
} __setupdata4_bits;

/* Frame Number Register (FrameNum) */
typedef struct {
  __REG16 FrmNum           :11;
  __REG16                  : 5;
} __framenum_bits;

/* Standard Device Request Information Register (SrdDevReqInfo) */
typedef struct {
  __REG16 Cfg              : 4;
  __REG16 If               : 4;
  __REG16 Alt              : 4;
  __REG16                  : 3;
  __REG16 H_FSpd           : 1;
} __srddevreqinfo_bits;

/* EP0 Configuration 1 Register (EP0Cfg1) */
typedef struct {
  __REG16                  : 3;
  __REG16 MaxPktSize       : 7;
  __REG16                  : 6;
} __ep0cfg1_bits;

/* EP0 Control Register (EP0Ctl) */
typedef struct {
  __REG16 StUpRdyEnb       : 1;
  __REG16 RxPktRdyEnb      : 1;
  __REG16 TxPktRdyEnb      : 1;
  __REG16                  : 1;
  __REG16 ShrtPktRxEnb     : 1;
  __REG16                  : 3;
  __REG16 SetCfgEnb        : 1;
  __REG16 SetItfEnb        : 1;
  __REG16 SttStgChgEnbEnb  : 1;
  __REG16 Stl              : 1;
  __REG16                  : 4;
} __ep0ctl_bits;

/* EP0 Status Register (EP0Stt) */
typedef struct {
  __REG16 StUpRdyStt       : 1;
  __REG16 RxPktRdyStt      : 1;
  __REG16 TxPktRdyStt      : 1;
  __REG16                  : 1;
  __REG16 ShrtPktRxStt     : 1;
  __REG16                  : 3;
  __REG16 SetCfgStt        : 1;
  __REG16 SetItfStt        : 1;
  __REG16 SttStgChgStt     : 1;
  __REG16                  : 5;
} __ep0stt_bits;


/* EP0 Transmit Byte Count Register (EP0TxCnt) */
typedef struct {
  __REG16 TxByteCunt       : 7;
  __REG16                  : 9;
} __ep0txcnt_bits;


/* EPa - EPf Configuration 1 Register (EPa - EPfCfg1) */
typedef struct {
  __REG16 EPNum            : 4;
  __REG16 EPDir            : 1;
  __REG16 EPType           : 2;
  __REG16 CfgNum           : 4;
  __REG16 ItfNum           : 4;
  __REG16 AltStLSB         : 1;
} __epxcfg1_bits;

/* EPa - EPf Configuration 2 Register (EPa – EPfCfg2) */
typedef struct {
  __REG16 AltStMSB         : 3;
  __REG16 MaxPktSize       :11;
  __REG16 TPuF             : 2;
} __epxcfg2_bits;

/* EPa - EPfFIFO Assignment Register (EPa - EPfFIFOAsin) */
typedef struct {
  __REG16 BufMod           : 1;
  __REG16                  :15;
} __epxfifoasin_bits;

/* EPa - EPf Control Register (EPa - EPfCtl) */
typedef struct {
  __REG16                  : 1;
  __REG16 RxPktRdyEnb      : 1;
  __REG16 TxPktRdyEnb      : 1;
  __REG16                  : 1;
  __REG16 ShrtPktRxEnb     : 1;
  __REG16 NAKResEnb        : 1;
  __REG16 OvrEnb           : 1;
  __REG16                  : 4;
  __REG16 Stl              : 1;
  __REG16 FIFOClr          : 1;
  __REG16 PreFrmInTk       : 1;
  __REG16 ISOModSel        : 1;
  __REG16 Busy             : 1;
} __epxctl_bits;

/* EPa - EPf Status Register (EPa - EPfStt) */
typedef struct {
  __REG32                  : 1;
  __REG32 RxPktRdyStt      : 1;
  __REG32 TxPktRdyStt      : 1;
  __REG32                  : 1;
  __REG32 ShrtPktRxStt     : 1;
  __REG32 NAKResStt        : 1;
  __REG32 OvrStt           : 1;
  __REG32                  :25;
} __epxstt_bits;

/* EPa - EPf Transmit Byte Count 1 Register (EPa - EPfTxCnt1) */
typedef struct {
  __REG16 TxByteCnt1       :11;
  __REG16                  : 5;
} __epxtxcnt1_bits;

/* EPa - EPf Transmit Byte Count 2 Register (EPa – EPfTxCnt2) */
typedef struct {
  __REG16 TxByteCnt2       :11;
  __REG16                  : 5;
} __epxtxcnt2_bits;


#endif	/* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/
	
/***************************************************************************
 **
 ** Power Consumption Control and System Control
 **
 ***************************************************************************/
__IO_REG32_BIT(IDR,                0xB8000000, __READ      , __idr_bits);
__IO_REG32_BIT(CLKSTP,             0xB8000004, __READ_WRITE, __clkstp_bits);
__IO_REG32_BIT(CGBCNT0,            0xB8000008, __READ_WRITE, __cgbcnt0_bits);
__IO_REG32_BIT(CKWT,               0xB800000C, __READ_WRITE, __ckwt_bits);
__IO_REG32_BIT(RMPCON,             0xB8000010, __READ_WRITE, __rmpcon_bits);
__IO_REG32_BIT(CGBCNT2,            0xB800001C, __READ_WRITE, __cgbcnt2_bits);

/***************************************************************************
 **
 ** Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQ,                0x78000000, __READ      , __irq_bits   );
__IO_REG32_BIT(IRQS,               0x78000004, __READ_WRITE, __irqs_bits  );
__IO_REG32_BIT(FIQ,                0x78000008, __READ      , __fiq_bits   );
__IO_REG32_BIT(FIQRAW,             0x7800000C, __READ      , __fiqraw_bits);
__IO_REG32_BIT(FIQEN,              0x78000010, __READ_WRITE, __fiqen_bits );
__IO_REG32_BIT(IRN,                0x78000014, __READ      , __irn_bits   );
__IO_REG32_BIT(CIL,                0x78000018, __READ_WRITE, __cil_bits   );
__IO_REG32_BIT(ILC0,               0x78000020, __READ_WRITE, __ilc0_bits  );
__IO_REG32_BIT(ILC1,               0x78000024, __READ_WRITE, __ilc1_bits  );
__IO_REG32(    CILCL,              0x78000028, __WRITE                    );
__IO_REG32_BIT(CILE,               0x7800002C, __READ      , __cile_bits  );
__IO_REG32_BIT(IRCL,               0x78F00004, __WRITE     , __ircl_bits  );
__IO_REG32_BIT(IRQA,               0x78F00010, __READ_WRITE, __irqa_bits  );
__IO_REG32_BIT(IDM,                0x78F00014, __READ_WRITE, __idm_bits   );
__IO_REG32_BIT(ILC,                0x78F00018, __READ_WRITE, __ilc_bits   );

/***************************************************************************
 **
 ** External Memory Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(BWC,                0x78100000, __READ_WRITE, __bwc_bits  );
__IO_REG32_BIT(ROMAC,              0x78100004, __READ_WRITE, __romac_bits);
__IO_REG32_BIT(RAMAC,              0x78100008, __READ_WRITE, __ramac_bits);
__IO_REG32_BIT(IO0AC,              0x7810000C, __READ_WRITE, __io0ac_bits);
__IO_REG32_BIT(IO1AC,              0x78100010, __READ_WRITE, __io1ac_bits);
__IO_REG32_BIT(DBWC,               0x78180000, __READ_WRITE, __dbwc_bits );
__IO_REG32_BIT(DRMC,               0x78180004, __READ_WRITE, __drmc_bits );
__IO_REG32_BIT(DRPC,               0x78180008, __READ_WRITE, __drpc_bits );
__IO_REG32_BIT(SDMD,               0x7818000C, __READ_WRITE, __sdmd_bits );
__IO_REG32_BIT(DCMD,               0x78180010, __READ_WRITE, __dcmd_bits );
__IO_REG32_BIT(RFSH0,              0x78180014, __READ_WRITE, __rfsh0_bits);
__IO_REG32_BIT(RFSH1,              0x7818001C, __READ_WRITE, __rfsh1_bits);
__IO_REG32_BIT(PDWC,               0x78180018, __WRITE     , __pdwc_bits );

/***************************************************************************
 **
 ** Direct Memory Access Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(DMAMOD,             0x7BE00000, __READ_WRITE, __dmamod_bits   );
__IO_REG32_BIT(DMASTA,             0x7BE00004, __READ      , __dmasta_bits   );
__IO_REG32_BIT(DMAINT,             0x7BE00008, __READ      , __dmaint_bits   );
__IO_REG32_BIT(DMACMSK0,           0x7BE00100, __READ_WRITE, __dmacmskx_bits );
__IO_REG32_BIT(DMACTMOD0,          0x7BE00104, __READ_WRITE, __dmactmodx_bits);
__IO_REG32(    DMACSAD0,           0x7BE00108, __READ_WRITE                  );
__IO_REG32(    DMACDAD0,           0x7BE0010C, __READ_WRITE                  );
__IO_REG32_BIT(DMACSIZ0,           0x7BE00110, __READ_WRITE, __dmacsizx_bits );
__IO_REG32(    DMACCINT0,          0x7BE00114, __READ_WRITE                  );
__IO_REG32_BIT(DMACMSK1,           0x7BE00200, __READ_WRITE, __dmacmskx_bits );
__IO_REG32_BIT(DMACTMOD1,          0x7BE00204, __READ_WRITE, __dmactmodx_bits);
__IO_REG32(    DMACSAD1,           0x7BE00208, __READ_WRITE                  );
__IO_REG32(    DMACDAD1,           0x7BE0020C, __READ_WRITE                  );
__IO_REG32_BIT(DMACSIZ1,           0x7BE00210, __READ_WRITE, __dmacsizx_bits );
__IO_REG32(    DMACCINT1,          0x7BE00214, __READ_WRITE                  );
__IO_REG32_BIT(DMACMSK2,           0x7BE00300, __READ_WRITE, __dmacmskx_bits );
__IO_REG32_BIT(DMACTMOD2,          0x7BE00304, __READ_WRITE, __dmactmodx_bits);
__IO_REG32(    DMACSAD2,           0x7BE00308, __READ_WRITE                  );
__IO_REG32(    DMACDAD2,           0x7BE0030C, __READ_WRITE                  );
__IO_REG32_BIT(DMACSIZ2,           0x7BE00310, __READ_WRITE, __dmacsizx_bits );
__IO_REG32(    DMACCINT2,          0x7BE00314, __READ_WRITE                  );
__IO_REG32_BIT(DMACMSK3,           0x7BE00400, __READ_WRITE, __dmacmskx_bits );
__IO_REG32_BIT(DMACTMOD3,          0x7BE00404, __READ_WRITE, __dmactmodx_bits);
__IO_REG32(    DMACSAD3,           0x7BE00408, __READ_WRITE                  );
__IO_REG32(    DMACDAD3,           0x7BE0040C, __READ_WRITE                  );
__IO_REG32_BIT(DMACSIZ3,           0x7BE00410, __READ_WRITE, __dmacsizx_bits );
__IO_REG32(    DMACCINT3,          0x7BE00414, __READ_WRITE                  );

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPPOA,              0xB7A00000, __READ_WRITE, __gppoa_bits );
__IO_REG32_BIT(GPPIA,              0xB7A00004, __READ      , __gppia_bits );
__IO_REG32_BIT(GPPMA,              0xB7A00008, __READ_WRITE, __gppma_bits );
__IO_REG32_BIT(GPPOB,              0xB7A00020, __READ_WRITE, __gppob_bits );
__IO_REG32_BIT(GPPIB,              0xB7A00024, __READ      , __gppib_bits );
__IO_REG32_BIT(GPPMB,              0xB7A00028, __READ_WRITE, __gppmb_bits );
__IO_REG32_BIT(GPPOC,              0xB7A00040, __READ_WRITE, __gppoc_bits );
__IO_REG32_BIT(GPPIC,              0xB7A00044, __READ      , __gppic_bits );
__IO_REG32_BIT(GPPMC,              0xB7A00048, __READ_WRITE, __gppmc_bits );
__IO_REG32_BIT(GPPOD,              0xB7A00060, __READ_WRITE, __gppod_bits );
__IO_REG32_BIT(GPPID,              0xB7A00064, __READ      , __gppid_bits );
__IO_REG32_BIT(GPPMD,              0xB7A00068, __READ_WRITE, __gppmd_bits );
__IO_REG32_BIT(GPPOE,              0xB7A00080, __READ_WRITE, __gppoe_bits );
__IO_REG32_BIT(GPPIE,              0xB7A00084, __READ      , __gppie_bits );
__IO_REG32_BIT(GPPME,              0xB7A00088, __READ_WRITE, __gppme_bits );
__IO_REG32_BIT(GPIEE,              0xB7A0008C, __READ_WRITE, __gpiee_bits );
__IO_REG32_BIT(GPIPE,              0xB7A00090, __READ_WRITE, __gpipe_bits );
__IO_REG32_BIT(GPISE,              0xB7A00094, __READ_WRITE, __gpise_bits );
__IO_REG32_BIT(GPIME,              0xB7A00098, __READ_WRITE, __gpime_bits );
__IO_REG32_BIT(GPPOF,              0xB7A000A0, __READ_WRITE, __gppof_bits );
__IO_REG32_BIT(GPPIF,              0xB7A000A4, __READ      , __gppif_bits );
__IO_REG32_BIT(GPPMF,              0xB7A000A8, __READ_WRITE, __gppmf_bits );

/***************************************************************************
 **
 ** Watchdog Timer
 **
 ***************************************************************************/
__IO_REG32_BIT(WDTCON,             0xB7E00000, __WRITE     , __wdtcon_bits );
__IO_REG32_BIT(WDTBCON,            0xB7E00004, __READ_WRITE, __wdtbcon_bits);
__IO_REG32_BIT(WDSTAT,             0xB7E00014, __READ_WRITE, __wdstat_bits );

/***************************************************************************
 **
 ** Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TIMECNTL0,          0xB7F00000, __READ_WRITE, __timecntlx_bits);
__IO_REG32_BIT(TIMEBASE0,          0xB7F00004, __READ_WRITE, __timebasex_bits);
__IO_REG32_BIT(TIMECNT0,           0xB7F00008, __READ      , __timecntx_bits );
__IO_REG32_BIT(TIMECMP0,           0xB7F0000C, __READ_WRITE, __timecmpx_bits );
__IO_REG32_BIT(TIMESTAT0,          0xB7F00010, __READ_WRITE, __timestatx_bits);
__IO_REG32_BIT(TIMECNTL1,          0xB7F00020, __READ_WRITE, __timecntlx_bits);
__IO_REG32_BIT(TIMEBASE1,          0xB7F00024, __READ_WRITE, __timebasex_bits);
__IO_REG32_BIT(TIMECNT1,           0xB7F00028, __READ      , __timecntx_bits );
__IO_REG32_BIT(TIMECMP1,           0xB7F0002C, __READ_WRITE, __timecmpx_bits );
__IO_REG32_BIT(TIMESTAT1,          0xB7F00030, __READ_WRITE, __timestatx_bits);
__IO_REG32_BIT(TIMECNTL2,          0xB7F00040, __READ_WRITE, __timecntlx_bits);
__IO_REG32_BIT(TIMEBASE2,          0xB7F00044, __READ_WRITE, __timebasex_bits);
__IO_REG32_BIT(TIMECNT2,           0xB7F00048, __READ      , __timecntx_bits );
__IO_REG32_BIT(TIMECMP2,           0xB7F0004C, __READ_WRITE, __timecmpx_bits );
__IO_REG32_BIT(TIMESTAT2,          0xB7F00050, __READ_WRITE, __timestatx_bits);
__IO_REG32_BIT(TMEN,               0xB8001004, __READ_WRITE, __tmen_bits     );
__IO_REG32_BIT(TMRLR,              0xB8001008, __READ_WRITE, __tmrlr_bits    );
__IO_REG32_BIT(TMOVFR,             0xB8001010, __READ_WRITE, __tmovfr_bits   );

/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(PWR,                0xB7D00000, __READ_WRITE, __pwr_bits     );
__IO_REG32_BIT(PWCY,               0xB7D00004, __READ_WRITE, __pwcy_bits    );
__IO_REG32_BIT(PWC,                0xB7D00008, __READ_WRITE, __pwc_bits     );
__IO_REG32_BIT(PWCON,              0xB7D0000C, __READ_WRITE, __pwcon_bits   );
__IO_REG32_BIT(PWINTSTS,           0xB7D0003C, __READ_WRITE, __pwintsts_bits);

/***************************************************************************
 **
 ** uPLAT-SIO (UART)
 **
 ***************************************************************************/
__IO_REG32_BIT(SIOBUF,             0xB8002000, __READ_WRITE, __siobuf_bits);
__IO_REG32_BIT(SIOSTA,             0xB8002004, __READ_WRITE, __siosta_bits);
__IO_REG32_BIT(SIOCON,             0xB8002008, __READ_WRITE, __siocon_bits);
__IO_REG32_BIT(SIOBCN,             0xB800200C, __READ_WRITE, __siobcn_bits);
__IO_REG32_BIT(SIOBT,              0xB8002014, __READ_WRITE, __siobt_bits );
__IO_REG32_BIT(SIOTCN,             0xB8002018, __READ_WRITE, __siotcn_bits);

/***************************************************************************
 **
 ** A/D Converter
 **
 ***************************************************************************/
__IO_REG32_BIT(ADCON1,             0xB6000004, __READ_WRITE, __adcon1_bits);
__IO_REG32_BIT(ADCON2,             0xB6000008, __READ_WRITE, __adcon2_bits);
__IO_REG32_BIT(ADINT,              0xB600000C, __READ_WRITE, __adint_bits );
__IO_REG32_BIT(ADR0,               0xB6000014, __READ_WRITE, __adr0_bits  );
__IO_REG32_BIT(ADR1,               0xB6000018, __READ_WRITE, __adr1_bits  );
__IO_REG32_BIT(ADR2,               0xB600001C, __READ_WRITE, __adr2_bits  );
__IO_REG32_BIT(ADR3,               0xB6000020, __READ_WRITE, __adr3_bits  );

/***************************************************************************
 **
 ** Synchronous SIO
 **
 ***************************************************************************/
__IO_REG32_BIT(SSIOBUF0,           0xB7B10000, __READ_WRITE, __ssiobufx_bits  );
__IO_REG32_BIT(SSIOSTA0,           0xB7B10004, __READ_WRITE, __ssiosta0_bits  );
__IO_REG32_BIT(SSIOCON0,           0xB7B10008, __READ_WRITE, __ssiocon0_bits  );
__IO_REG32_BIT(SSIOINTR0,          0xB7B1000C, __READ_WRITE, __ssiointr0_bits );
__IO_REG32_BIT(SSIOINTEN0,         0xB7B10010, __READ_WRITE, __ssiointen0_bits);
__IO_REG32_BIT(SSIODMAC0,          0xB7B10014, __READ_WRITE, __ssiodmac0_bits );
__IO_REG32_BIT(SSIOTSCON0,         0xB7B10018, __READ_WRITE, __ssiotscon0_bits);
__IO_REG32_BIT(SSIOBUF1,           0xB7B10020, __READ_WRITE, __ssiobufx_bits  );
__IO_REG32_BIT(SSIOSTA1,           0xB7B10024, __READ_WRITE, __ssiosta1_bits  );
__IO_REG32_BIT(SSIOCON1,           0xB7B10028, __READ_WRITE, __ssiocon1_bits  );
__IO_REG32_BIT(SSIOINTR1,          0xB7B1002C, __READ_WRITE, __ssiointr1_bits );
__IO_REG32_BIT(SSIOINTEN1,         0xB7B10030, __READ_WRITE, __ssiointen1_bits);
__IO_REG32_BIT(SSIODMAC1,          0xB7B10034, __READ_WRITE, __ssiodmac1_bits );
__IO_REG32_BIT(SSIOTSCON1,         0xB7B10038, __READ_WRITE, __ssiotscon1_bits);

/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(I2CCON,             0xB7B00000, __READ_WRITE, __i2ccon_bits);
__IO_REG32_BIT(I2CSAD,             0xB7B00004, __READ_WRITE, __i2csad_bits);
__IO_REG32_BIT(I2CCLR,             0xB7B00008, __READ_WRITE, __i2cclr_bits);
__IO_REG32_BIT(I2CSR,              0xB7B0000C, __READ      , __i2csr_bits );
__IO_REG32_BIT(I2CIR,              0xB7B00010, __READ_WRITE, __i2cir_bits );
__IO_REG32_BIT(I2CIMR,             0xB7B00014, __READ_WRITE, __i2cimr_bits);
__IO_REG32_BIT(I2CDR,              0xB7B00018, __READ_WRITE, __i2cdr_bits );

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32(    RTCREG,             0xB7C00000, __READ_WRITE               );
__IO_REG32_BIT(RTCCON,             0xB7C00004, __READ_WRITE, __rtccon_bits);
__IO_REG32(    RTCCMP,             0xB7C00008, __READ_WRITE               );
__IO_REG32(    RTCSCRP,            0xB7C0000C, __READ_WRITE               );
__IO_REG32_BIT(RTCST,              0xB7C00010, __READ_WRITE, __rtcst_bits );

/***************************************************************************
 **
 ** Cofigurations Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(PDMASK,             0x80000000, __READ_WRITE, __pdmask_bits );
__IO_REG32_BIT(MCKST,              0x80000004, __READ_WRITE, __mckst_bits  );
__IO_REG32_BIT(PIOCTL,             0x80000008, __READ_WRITE, __pioctl_bits );
__IO_REG32_BIT(I2SCNTL,            0x8000000C, __READ_WRITE, __i2scntl_bits);
__IO_REG32_BIT(OCONFIG,            0x80000010, __READ_WRITE, __oconfig_bits);
__IO_REG32_BIT(_TST,                0x80000014, __READ_WRITE, __tst_bits    );

/***************************************************************************
 **
 ** I2S Transmission
 **
 ***************************************************************************/
__IO_REG32_BIT(I2SFIFOO,           0x82000000, __READ_WRITE, __i2sfifoo_bits);
__IO_REG32_BIT(I2SCONO0,           0x82000004, __READ_WRITE, __i2scono0_bits);
__IO_REG32_BIT(I2SCONO1,           0x82000008, __READ_WRITE, __i2scono1_bits);
__IO_REG32_BIT(I2SAFRO,            0x8200000C, __READ_WRITE, __i2safro_bits );
__IO_REG32_BIT(I2SAERO,            0x82000010, __READ_WRITE, __i2saero_bits );
__IO_REG32_BIT(I2SIMRO,            0x82000014, __READ_WRITE, __i2simro_bits );
__IO_REG32_BIT(I2SISTO,            0x82000018, __READ_WRITE, __i2sisto_bits );
__IO_REG32_BIT(I2SWADRO,           0x8200001C, __READ_WRITE, __i2swadro_bits);
__IO_REG32_BIT(I2SRADRO,           0x82000020, __READ_WRITE, __i2sradro_bits);
__IO_REG32_BIT(I2SDNOO,            0x82000024, __READ      , __i2sdnoo_bits );

/***************************************************************************
 **
 ** I2S Reception
 **
 ***************************************************************************/
__IO_REG32_BIT(I2SFIFOI,           0x84000000, __READ      , __i2sfifoi_bits);
__IO_REG32_BIT(I2SCONI0,           0x84000004, __READ_WRITE, __i2sconi0_bits);
__IO_REG32_BIT(I2SCONI1,           0x84000008, __READ_WRITE, __i2sconi1_bits);
__IO_REG32_BIT(I2SAFRI,            0x8400000C, __READ_WRITE, __i2safri_bits );
__IO_REG32_BIT(I2SAERI,            0x84000010, __READ_WRITE, __i2saeri_bits );
__IO_REG32_BIT(I2SIMRI,            0x84000014, __READ_WRITE, __i2simri_bits );
__IO_REG32_BIT(I2SISTI,            0x84000018, __READ_WRITE, __i2sisti_bits );
__IO_REG32_BIT(I2SWADRI,           0x8400001C, __READ_WRITE, __i2swadri_bits);
__IO_REG32_BIT(I2SRADRI,           0x84000020, __READ_WRITE, __i2sradri_bits);
__IO_REG32_BIT(I2SDNOI,            0x84000024, __READ      , __i2sdnoi_bits );

/***************************************************************************
 **
 ** NAND Flash Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(MBANK,              0x86000000, __READ_WRITE, __mbank_bits   );
__IO_REG32_BIT(MSCTRL,             0x86000004, __READ_WRITE, __msctrl_bits  );
__IO_REG32_BIT(MSWAIT,             0x86000008, __READ_WRITE, __mswait_bits  );
__IO_REG32_BIT(MSSTS,              0x8600000C, __READ      , __mssts_bits   );
__IO_REG32_BIT(MINTENBL,           0x86000010, __READ_WRITE, __mintenbl_bits);
__IO_REG32_BIT(MSERR,              0x86000014, __READ      , __mserr_bits   );
__IO_REG32_BIT(MMCMD,              0x86000018, __WRITE     , __mmcmd_bits   );
__IO_REG32_BIT(MMADR,              0x8600001C, __WRITE     , __mmadr_bits   );
__IO_REG32_BIT(MMSEL,              0x86000020, __READ_WRITE, __mmsel_bits   );
__IO_REG32_BIT(MMRDCTL,            0x86000024, __READ_WRITE, __mmrdctl_bits );
__IO_REG32_BIT(MOPTION,            0x86000028, __READ_WRITE, __moption_bits );
__IO_REG32_BIT(MMRDDATA,           0x8600002C, __READ      , __mmrddata_bits);
__IO_REG32_BIT(ECCLP1,             0x86000030, __READ      , __ecclp1_bits  );
__IO_REG32_BIT(ECCCP1,             0x86000034, __READ      , __ecccp1_bits  );
__IO_REG32_BIT(ECCERR1,            0x86000038, __READ      , __eccerr1_bits );
__IO_REG32_BIT(HREV1,              0x86000040, __READ_WRITE, __hrev1_bits   );
__IO_REG32_BIT(HSTAD1,             0x86000044, __READ_WRITE, __hstad1_bits  );
__IO_REG32_BIT(HECC2,              0x86000048, __READ_WRITE, __hecc2_bits   );
__IO_REG32_BIT(HECC1,              0x8600004C, __READ_WRITE, __hecc1_bits   );
__IO_REG32_BIT(ECCLP3,             0x86000050, __READ      , __ecclp3_bits  );
__IO_REG32_BIT(ECCCP3,             0x86000054, __READ      , __ecccp3_bits  );
__IO_REG32_BIT(ECCERR3,            0x86000058, __READ      , __eccerr3_bits );
__IO_REG32_BIT(HREV3,              0x86000060, __READ_WRITE, __hrev3_bits   );
__IO_REG32_BIT(HSTAD3,             0x86000064, __READ_WRITE, __hstad3_bits  );
__IO_REG32_BIT(HECC4,              0x86000068, __READ_WRITE, __hecc4_bits   );
__IO_REG32_BIT(HECC3,              0x8600006C, __READ_WRITE, __hecc3_bits   );
__IO_REG32_BIT(ECCLP5,             0x86000070, __READ      , __ecclp5_bits  );
__IO_REG32_BIT(ECCCP5,             0x86000074, __READ      , __ecccp5_bits  );
__IO_REG32_BIT(ECCERR5,            0x86000078, __READ      , __eccerr5_bits );
__IO_REG32_BIT(HREV5,              0x86000080, __READ_WRITE, __hrev5_bits   );
__IO_REG32_BIT(HSTAD5,             0x86000084, __READ_WRITE, __hstad5_bits  );
__IO_REG32_BIT(HECC6,              0x86000088, __READ_WRITE, __hecc6_bits   );
__IO_REG32_BIT(HECC5,              0x8600008C, __READ_WRITE, __hecc5_bits   );
__IO_REG32_BIT(ECCLP7,             0x86000090, __READ      , __ecclp7_bits  );
__IO_REG32_BIT(ECCCP7,             0x86000094, __READ      , __ecccp7_bits  );
__IO_REG32_BIT(ECCERR7,            0x86000098, __READ      , __eccerr7_bits );
__IO_REG32_BIT(HREV7,              0x860000A0, __READ_WRITE, __hrev7_bits   );
__IO_REG32_BIT(HSTAD7,             0x860000A4, __READ_WRITE, __hstad7_bits  );
__IO_REG32_BIT(HECC8,              0x860000A8, __READ_WRITE, __hecc8_bits   );
__IO_REG32_BIT(HECC7,              0x860000AC, __READ_WRITE, __hecc7_bits   );
__IO_REG32_BIT(MMDATA,             0x86000100, __READ_WRITE, __mmdata_bits  );

/***************************************************************************
 **
 ** ATA IP (IDE Host Controller)
 **
 ***************************************************************************/
__IO_REG16_BIT(BMICP,              0x7B900000, __READ_WRITE, __bmicp_bits   );
__IO_REG16_BIT(BMISP,              0x7B900002, __READ_WRITE, __bmisp_bits   );
__IO_REG32_BIT(BMIDTPP,            0x7B900004, __READ_WRITE, __bmidtpp_bits );
__IO_REG16_BIT(BMICS,              0x7B900008, __READ_WRITE, __bmicp_bits   );
__IO_REG16_BIT(BMISS,              0x7B90000A, __READ_WRITE, __bmisp_bits   );
__IO_REG32_BIT(BMIDTPS,            0x7B90000C, __READ_WRITE, __bmidtpp_bits );
__IO_REG32_BIT(DMAFEAT,            0x7B900018, __READ_WRITE, __dmafeat_bits );
__IO_REG32_BIT(CLKCTL,             0x7B90001C, __READ_WRITE, __clkctl_bits  );
__IO_REG16_BIT(IDETIMP,            0x7B900040, __READ_WRITE, __idetimp_bits );
__IO_REG16_BIT(IDETIMS,            0x7B900042, __READ_WRITE, __idetimp_bits );
__IO_REG8_BIT( SIDETIM,            0x7B900044, __READ_WRITE, __sidetim_bits );
__IO_REG8_BIT( IDESTAT,            0x7B900047, __READ      , __idestat_bits );
__IO_REG16_BIT(UDMACTL,            0x7B900048, __READ_WRITE, __udmactl_bits );
__IO_REG16_BIT(UDMATIM,            0x7B90004A, __READ_WRITE, __udmatim_bits );
__IO_REG32_BIT(TIMORIDE,           0x7B900050, __READ_WRITE, __timoride_bits);
__IO_REG32_BIT(REGSTB,             0x7B900054, __READ_WRITE, __regstb_bits  );
__IO_REG32_BIT(REGRCVR,            0x7B900058, __READ_WRITE, __regrcvr_bits );
__IO_REG32_BIT(DATSTB,             0x7B90005C, __READ_WRITE, __datstb_bits  );
__IO_REG32_BIT(DATRCVR,            0x7B900060, __READ_WRITE, __datrcvr_bits );
__IO_REG32_BIT(DMASTB,             0x7B900064, __READ_WRITE, __dmastb_bits  );
__IO_REG32_BIT(DMARCVR,            0x7B900068, __READ_WRITE, __dmarcvr_bits );
__IO_REG32_BIT(UDMASTB,            0x7B90006C, __READ_WRITE, __udmastb_bits );
__IO_REG32_BIT(UDMATRP,            0x7B900070, __READ_WRITE, __udmatrp_bits );
__IO_REG32_BIT(UDMATENV,           0x7B900074, __READ_WRITE, __udmatenv_bits);
__IO_REG32_BIT(PINCTL,             0x7B900084, __READ_WRITE, __pinctl_bits  );
__IO_REG32_BIT(IORDYTMR,           0x7B900088, __READ_WRITE, __iordytmr_bits);

/***************************************************************************
 **
 ** HS USB
 **
 ***************************************************************************/
__IO_REG16_BIT(_Rev,                0x7BB00000, __READ      , __rev_bits         );
__IO_REG16_BIT(SysCtl,             0x7BB00004, __READ_WRITE, __sysctl_bits       );
__IO_REG16_BIT(DMACfg,             0x7BB00008, __READ_WRITE, __dmacfg_bits       );
__IO_REG16_BIT(DMACtl,             0x7BB0000A, __READ_WRITE, __dmactl_bits       );
__IO_REG16_BIT(IntStt,             0x7BB0000C, __READ_WRITE, __intstt_bits       );
__IO_REG16_BIT(IntEnb,             0x7BB00010, __READ_WRITE, __intenb_bits       );
__IO_REG16_BIT(SetUpData1,         0x7BB00020, __READ      , __setupdata1_bits   );
__IO_REG16_BIT(SetUpData2,         0x7BB00022, __READ      , __setupdata2_bits   );
__IO_REG16_BIT(SetUpData3,         0x7BB00024, __READ      , __setupdata3_bits   );
__IO_REG16_BIT(SetUpData4,         0x7BB00026, __READ      , __setupdata4_bits   );
__IO_REG16_BIT(FrameNum,           0x7BB00028, __READ      , __framenum_bits     );
__IO_REG16_BIT(SrdDevReqInfo,      0x7BB0002C, __READ      , __srddevreqinfo_bits);
__IO_REG16_BIT(EP0Cfg1,            0x7BB00030, __READ_WRITE, __ep0cfg1_bits      );
__IO_REG16_BIT(EP0Ctl,             0x7BB00034, __READ_WRITE, __ep0ctl_bits       );
__IO_REG16_BIT(EP0Stt,             0x7BB00036, __READ_WRITE, __ep0stt_bits       );
__IO_REG16(    EP0RxCnt,           0x7BB00038, __READ                            );
__IO_REG16_BIT(EP0TxCnt,           0x7BB0003C, __READ_WRITE, __ep0txcnt_bits     );
__IO_REG16_BIT(EPaCfg1,            0x7BB00040, __READ_WRITE, __epxcfg1_bits      );
__IO_REG16_BIT(EPaCfg2,            0x7BB00042, __READ_WRITE, __epxcfg2_bits      );
__IO_REG16_BIT(EPaFIFOAsin,        0x7BB00044, __READ_WRITE, __epxfifoasin_bits  );
__IO_REG16_BIT(EPaCtl,             0x7BB00048, __READ_WRITE, __epxctl_bits       );
__IO_REG32_BIT(EPaStt,             0x7BB0004C, __READ_WRITE, __epxstt_bits       );
__IO_REG16(    EPaRxCnt1,          0x7BB00050, __READ                            );
__IO_REG16(    EPaRxCnt2,          0x7BB00052, __READ                            );
__IO_REG16_BIT(EPaTxCnt1,          0x7BB00054, __READ_WRITE, __epxtxcnt1_bits    );
__IO_REG16_BIT(EPaTxCnt2,          0x7BB00056, __READ_WRITE, __epxtxcnt2_bits    );
__IO_REG16_BIT(EPbCfg1,            0x7BB00060, __READ_WRITE, __epxcfg1_bits      );
__IO_REG16_BIT(EPbCfg2,            0x7BB00062, __READ_WRITE, __epxcfg2_bits      );
__IO_REG16_BIT(EPbFIFOAsin,        0x7BB00064, __READ_WRITE, __epxfifoasin_bits  );
__IO_REG16_BIT(EPbCtl,             0x7BB00068, __READ_WRITE, __epxctl_bits       );
__IO_REG32_BIT(EPbStt,             0x7BB0006C, __READ_WRITE, __epxstt_bits       );
__IO_REG16(    EPbRxCnt1,          0x7BB00070, __READ                            );
__IO_REG16(    EPbRxCnt2,          0x7BB00072, __READ                            );
__IO_REG16_BIT(EPbTxCnt1,          0x7BB00074, __READ_WRITE, __epxtxcnt1_bits    );
__IO_REG16_BIT(EPbTxCnt2,          0x7BB00076, __READ_WRITE, __epxtxcnt2_bits    );
__IO_REG16_BIT(EPcCfg1,            0x7BB00080, __READ_WRITE, __epxcfg1_bits      );
__IO_REG16_BIT(EPcCfg2,            0x7BB00082, __READ_WRITE, __epxcfg2_bits      );
__IO_REG16_BIT(EPcFIFOAsin,        0x7BB00084, __READ_WRITE, __epxfifoasin_bits  );
__IO_REG16_BIT(EPcCtl,             0x7BB00088, __READ_WRITE, __epxctl_bits       );
__IO_REG32_BIT(EPcStt,             0x7BB0008C, __READ_WRITE, __epxstt_bits       );
__IO_REG16(    EPcRxCnt1,          0x7BB00090, __READ                            );
__IO_REG16_BIT(EPcTxCnt1,          0x7BB00094, __READ_WRITE, __epxtxcnt1_bits    );
__IO_REG16_BIT(EPdCfg1,            0x7BB000A0, __READ_WRITE, __epxcfg1_bits      );
__IO_REG16_BIT(EPdCfg2,            0x7BB000A2, __READ_WRITE, __epxcfg2_bits      );
__IO_REG16_BIT(EPdFIFOAsin,        0x7BB000A4, __READ_WRITE, __epxfifoasin_bits  );
__IO_REG16_BIT(EPdCtl,             0x7BB000A8, __READ_WRITE, __epxctl_bits       );
__IO_REG32_BIT(EPdStt,             0x7BB000AC, __READ_WRITE, __epxstt_bits       );
__IO_REG16(    EPdRxCnt1,          0x7BB000B0, __READ                            );
__IO_REG16_BIT(EPdTxCnt1,          0x7BB000B4, __READ_WRITE, __epxtxcnt1_bits    );
__IO_REG16_BIT(EPeCfg1,            0x7BB000C0, __READ_WRITE, __epxcfg1_bits      );
__IO_REG16_BIT(EPeCfg2,            0x7BB000C2, __READ_WRITE, __epxcfg2_bits      );
__IO_REG16_BIT(EPeFIFOAsin,        0x7BB000C4, __READ_WRITE, __epxfifoasin_bits  );
__IO_REG16_BIT(EPeCtl,             0x7BB000C8, __READ_WRITE, __epxctl_bits       );
__IO_REG32_BIT(EPeStt,             0x7BB000CC, __READ_WRITE, __epxstt_bits       );
__IO_REG16(    EPeRxCnt1,          0x7BB000D0, __READ                            );
__IO_REG16_BIT(EPeTxCnt1,          0x7BB000D4, __READ_WRITE, __epxtxcnt1_bits    );
__IO_REG16_BIT(EPfCfg1,            0x7BB000E0, __READ_WRITE, __epxcfg1_bits      );
__IO_REG16_BIT(EPfCfg2,            0x7BB000E2, __READ_WRITE, __epxcfg2_bits      );
__IO_REG16_BIT(EPfFIFOAsin,        0x7BB000E4, __READ_WRITE, __epxfifoasin_bits  );
__IO_REG16_BIT(EPfCtl,             0x7BB000E8, __READ_WRITE, __epxctl_bits       );
__IO_REG32_BIT(EPfStt,             0x7BB000EC, __READ_WRITE, __epxstt_bits       );
__IO_REG16(    EPfRxCnt1,          0x7BB000F0, __READ                            );
__IO_REG16_BIT(EPfTxCnt1,          0x7BB000F4, __READ_WRITE, __epxtxcnt1_bits    );
__IO_REG32(    EP0TxFIFO,          0x7BB00100, __WRITE                           );
__IO_REG32(    EP0RxFIFO,          0x7BB00104, __READ                            );
__IO_REG32(    EPaFIFO,            0x7BB01000, __READ_WRITE                      );
__IO_REG32(    EPbFIFO,            0x7BB01400, __READ_WRITE                      );
__IO_REG32(    EPcFIFO,            0x7BB01800, __READ_WRITE                      );
__IO_REG32(    EPdFIFO,            0x7BB01C00, __READ_WRITE                      );
__IO_REG32(    EPeFIFO,            0x7BB02000, __READ_WRITE                      );
__IO_REG32(    EPfFIFO,            0x7BB02400, __READ_WRITE                      );

/* Assembler-specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 ** ML696201 Interrupt Codes
 **
 ***************************************************************************/
#define INO_uPLAT         0
#define INO_SSIO0         1
#define INO_SSIO1         2
#define INO_SSIO2         3
#define INO_WDT           4
#define INO_RTC           5
#define INO_PIOE12        6
#define INO_IRQS          8
#define INO_PWM           9
#define INO_UART         10
#define INO_I2C          11
#define INO_ADC          12
#define INO_NANDFLASH    13
#define INO_IDE          14
#define INO_TIMER0       16
#define INO_TIMER1       17
#define INO_TIMER2       18
#define INO_I2STX        20
#define INO_I2SRX        21
#define INO_DMAC0        22
#define INO_DMAC1        23
#define INO_DMAC2        24
#define INO_DMAC3        25
#define INO_PIOE15       26
#define INO_USB          27
#define INO_PIOE14       29
#define INO_PIOE13       31


#endif	/* __IOML696201_H */


