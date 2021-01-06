/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Atmel Semiconductors 
 **    AT91RM9200
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.6 $
 **                                
 ***************************************************************************/

#ifndef __AT91RM9200_H
#define __AT91RM9200_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    AT91RM9200 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* MC Remap Control Register */
typedef struct {
  __REG32 RCB                 : 1;
  __REG32                     : 31;
} __MC_RCR_bits;

/* MC Abort Status Register */
typedef struct {
  __REG32 UNDADD              : 1;
  __REG32 MISADD              : 1;
  __REG32                     : 6;
  __REG32 ABTSZ               : 2;
  __REG32 ABTTYP              : 2;
  __REG32                     : 4;
  __REG32 MST0                : 1;
  __REG32 MST1                : 1;
  __REG32 MST2                : 1;
  __REG32 MST3                : 1;
  __REG32                     : 4;
  __REG32 SVMST0              : 1;
  __REG32 SVMST1              : 1;
  __REG32 SVMST2              : 1;
  __REG32 SVMST3              : 1;
  __REG32                     : 4;
} __MC_ASR_bits;

/* MC Master Priority Register */
typedef struct {
  __REG32 MSTP0               : 3;
  __REG32                     : 1;
  __REG32 MSTP1               : 3;
  __REG32                     : 1;
  __REG32 MSTP2               : 3;
  __REG32                     : 1;
  __REG32 MSTP3               : 3;
  __REG32                     : 17;
} __MC_MPR_bits;


/* EBI Chip Select Assignment Register */
typedef struct {
  __REG32 CS0A                : 1;
  __REG32 CS1A                : 1;
  __REG32                     : 1;
  __REG32 CS3A                : 1;
  __REG32 CS4A                : 1;
  __REG32                     : 27;
} __EBI_CSA_bits;

/* EBI Configuration Register */
typedef struct {
  __REG32 DBPUC               : 1;
  __REG32                     : 31;
} __EBI_CFGR_bits;


/* SMC Chip Select Registers */
typedef struct {
  __REG32 NWS                 : 7;
  __REG32 WSEN                : 1;
  __REG32 TDF                 : 4;
  __REG32 BAT                 : 1;
  __REG32 DBW                 : 2;
  __REG32 DRP                 : 1;
  __REG32 ACSS                : 2;
  __REG32                     : 6;
  __REG32 RWSETUP             : 3;
  __REG32                     : 1;
  __REG32 RWHOLD              : 3;
  __REG32                     : 1;
} __SMC_CSR_bits;


/* SDRAMC Mode Register */
typedef struct {
  __REG32 MODE                : 4;
  __REG32 DBW                 : 1;
  __REG32                     : 27;
} __SDRAMC_MR_bits;

/* SDRAMC Refresh Timer Register */
typedef struct {
  __REG32 COUNT               : 12;
  __REG32                     : 20;
} __SDRAMC_TR_bits;

/* SDRAMC Configuration Register */
typedef struct {
  __REG32 NC                  : 2;
  __REG32 NR                  : 2;
  __REG32 NB                  : 1;
  __REG32 CAS                 : 2;
  __REG32 TWR                 : 4;
  __REG32 TRC                 : 4;
  __REG32 TRP                 : 4;
  __REG32 TRCD                : 4;
  __REG32 TRAS                : 4;
  __REG32 TXSR                : 4;
  __REG32                     : 1;
} __SDRAMC_CR_bits;

/* SDRAMC Self-refresh Register */
typedef struct {
  __REG32 SRCB                : 1;
  __REG32                     : 31;
} __SDRAMC_SRR_bits;

/* SDRAMC Low-power Register */
typedef struct {
  __REG32 LPCB                : 1;
  __REG32                     : 31;
} __SDRAMC_LPR_bits;

/* SDRAMC Interrupt Enable Register */
typedef struct {
  __REG32 RES                 : 1;
  __REG32                     : 31;
} __SDRAMC_IER_bits;


/* Burst Flash Controller Mode Register */
typedef struct {
  __REG32 BFCOM               : 2;
  __REG32 BFCC                : 2;
  __REG32 AVL                 : 4;
  __REG32 PAGES               : 3;
  __REG32                     : 1;
  __REG32 OEL                 : 2;
  __REG32                     : 2;
  __REG32 BAAEN               : 1;
  __REG32 BFOEH               : 1;
  __REG32 MUXEN               : 1;
  __REG32 RDYEN               : 1;
  __REG32                     : 12;
} __BFC_MR_bits;


/* PDC Receive Counter Register */
typedef struct {
  __REG32 RXCTR               : 16;
  __REG32                     : 16;
} __PERIPH_RCR_bits;

/* PDC Transmit Counter Register */
typedef struct {
  __REG32 TXCTR               : 16;
  __REG32                     : 16;
} __PERIPH_TCR_bits;

/* PDC Receive Next Counter Register */
typedef struct {
  __REG32 RXNCR               : 16;
  __REG32                     : 16;
} __PERIPH_RNCR_bits;

/* PDC Transmit Next Counter Register */
typedef struct {
  __REG32 TXNCR               : 16;
  __REG32                     : 16;
} __PERIPH_TNCR_bits;

/* PDC Transfer Control Register */
typedef struct {
  __REG32 RXTEN               : 1;
  __REG32 RXTDIS              : 1;
  __REG32                     : 6;
  __REG32 TXTEN               : 1;
  __REG32 TXTDIS              : 1;
  __REG32                     : 22;
} __PERIPH_PTCR_bits;

/* PDC Transfer Status Register */
typedef struct {
  __REG32 RXTEN               : 1;
  __REG32                     : 7;
  __REG32 TXTEN               : 1;
  __REG32                     : 23;
} __PERIPH_PTSR_bits;


/* AIC source mode register */
typedef struct {
  __REG32 PRIOR  :3;
  __REG32        :2;
  __REG32 SRCTYPE:2;
  __REG32        :25;
} __aicsmr_bits;	

/* AIC source vector register */
typedef struct {
  __REG32 VECTOR :32;
} __aicsvr_bits;	

/* AIC interrupt vector register */
typedef struct {
  __REG32 IRQV :32;
} __aicivr_bits;

/* AIC FIQ vector register */
typedef struct {
  __REG32 FIQV :32;
} __aicfiqvr_bits;
	
/* AIC interrupt status register */
typedef struct {
  __REG32 IRQID :5;
  __REG32       :27;
} __aicisr_bits;
	
/* AIC Interrupt Pending Register */
typedef struct {
  __REG32 FIQ                 : 1;
  __REG32 SYS                 : 1;
  __REG32 PID2                : 1;
  __REG32 PID3                : 1;
  __REG32 PID4                : 1;
  __REG32 PID5                : 1;
  __REG32 PID6                : 1;
  __REG32 PID7                : 1;
  __REG32 PID8                : 1;
  __REG32 PID9                : 1;
  __REG32 PID10               : 1;
  __REG32 PID11               : 1;
  __REG32 PID12               : 1;
  __REG32 PID13               : 1;
  __REG32 PID14               : 1;
  __REG32 PID15               : 1;
  __REG32 PID16               : 1;
  __REG32 PID17               : 1;
  __REG32 PID18               : 1;
  __REG32 PID19               : 1;
  __REG32 PID20               : 1;
  __REG32 PID21               : 1;
  __REG32 PID22               : 1;
  __REG32 PID23               : 1;
  __REG32 PID24               : 1;
  __REG32 PID25               : 1;
  __REG32 PID26               : 1;
  __REG32 PID27               : 1;
  __REG32 PID28               : 1;
  __REG32 PID29               : 1;
  __REG32 PID30               : 1;
  __REG32 PID31               : 1;
} __aicir_bits;

/* AIC core interrupt status register */
typedef struct {
  __REG32 NFIQ :1;
  __REG32 NIRQ :1;
  __REG32      :30;
} __aiccisr_bits;
	
/* AIC Debug Control Register */
typedef struct {
  __REG32 PROT                : 1;
  __REG32 GMSK                : 1;
  __REG32                     : 30;
} __AIC_DCR_bits;

/* AIC Fast Forcing Enable Register */
typedef struct {
  __REG32                     : 1;
  __REG32 SYS                 : 1;
  __REG32 PID2                : 1;
  __REG32 PID3                : 1;
  __REG32 PID4                : 1;
  __REG32 PID5                : 1;
  __REG32 PID6                : 1;
  __REG32 PID7                : 1;
  __REG32 PID8                : 1;
  __REG32 PID9                : 1;
  __REG32 PID10               : 1;
  __REG32 PID11               : 1;
  __REG32 PID12               : 1;
  __REG32 PID13               : 1;
  __REG32 PID14               : 1;
  __REG32 PID15               : 1;
  __REG32 PID16               : 1;
  __REG32 PID17               : 1;
  __REG32 PID18               : 1;
  __REG32 PID19               : 1;
  __REG32 PID20               : 1;
  __REG32 PID21               : 1;
  __REG32 PID22               : 1;
  __REG32 PID23               : 1;
  __REG32 PID24               : 1;
  __REG32 PID25               : 1;
  __REG32 PID26               : 1;
  __REG32 PID27               : 1;
  __REG32 PID28               : 1;
  __REG32 PID29               : 1;
  __REG32 PID30               : 1;
  __REG32 PID31               : 1;
} __AIC_FFER_bits;


/* PMC System Clock Enable Register */
typedef struct {
  __REG32 PCK                 : 1;
  __REG32 UDP                 : 1;
  __REG32 MCKUDP              : 1;
  __REG32                     : 1;
  __REG32 UHP                 : 1;
  __REG32                     : 3;
  __REG32 PCK0                : 1;
  __REG32 PCK1                : 1;
  __REG32 PCK2                : 1;
  __REG32 PCK3                : 1;
  __REG32 PCK4                : 1;
  __REG32 PCK5                : 1;
  __REG32 PCK6                : 1;
  __REG32 PCK7                : 1;
  __REG32                     : 16;
} __PMC_SCER_bits;

/* PMC Peripheral Clock Enable Register */
typedef struct {
  __REG32                     : 2;
  __REG32 PID2                : 1;
  __REG32 PID3                : 1;
  __REG32 PID4                : 1;
  __REG32 PID5                : 1;
  __REG32 PID6                : 1;
  __REG32 PID7                : 1;
  __REG32 PID8                : 1;
  __REG32 PID9                : 1;
  __REG32 PID10               : 1;
  __REG32 PID11               : 1;
  __REG32 PID12               : 1;
  __REG32 PID13               : 1;
  __REG32 PID14               : 1;
  __REG32 PID15               : 1;
  __REG32 PID16               : 1;
  __REG32 PID17               : 1;
  __REG32 PID18               : 1;
  __REG32 PID19               : 1;
  __REG32 PID20               : 1;
  __REG32 PID21               : 1;
  __REG32 PID22               : 1;
  __REG32 PID23               : 1;
  __REG32 PID24               : 1;
  __REG32 PID25               : 1;
  __REG32 PID26               : 1;
  __REG32 PID27               : 1;
  __REG32 PID28               : 1;
  __REG32 PID29               : 1;
  __REG32 PID30               : 1;
  __REG32 PID31               : 1;
} __PMC_PCER_bits;

/* PMC Main Oscillator Register */
typedef struct {
  __REG32 MOSCEN              : 1;
  __REG32                     : 7;
  __REG32 OSCOUNT             : 8;
  __REG32                     : 16;
} __PMC_MOR_bits;

/* PMC Main Clock Frequency Register */
typedef struct {
  __REG32 MAINF               : 16;
  __REG32 MAINRDY             : 1;
  __REG32                     : 15;
} __PMC_MCFR_bits;

/* PMC PLL A Register */
typedef struct {
  __REG32 DIVA                : 8;
  __REG32 PLLACOUNT           : 6;
  __REG32 OUTA                : 2;
  __REG32 MULA                : 11;
  __REG32                     : 5;
} __PMC_PLLAR_bits;

/* PMC PLL B Register */
typedef struct {
  __REG32 DIVB                : 8;
  __REG32 PLLBCOUNT           : 6;
  __REG32 OUTB                : 2;
  __REG32 MULB                : 11;
  __REG32                     : 1;
  __REG32 USB_96M             : 1;
  __REG32                     : 3;
} __PMC_PLLBR_bits;

/* PMC Master Clock Register */
typedef struct {
  __REG32 CSS                 : 2;
  __REG32 PRES                : 3;
  __REG32                     : 3;
  __REG32 MDIV                : 2;
  __REG32                     : 22;
} __PMC_MCKR_bits;

/* PMC Programmable Clock Register 0 to 7 */
typedef struct {
  __REG32 CSS                 : 2;
  __REG32 PRES                : 3;
  __REG32                     : 27;
} __PMC_PCK_bits;

/* PMC Interrupt Enable Register */
typedef struct {
  __REG32 MOSCS               : 1;
  __REG32 LOCKA               : 1;
  __REG32 LOCKB               : 1;
  __REG32 MCKRDY              : 1;
  __REG32                     : 4;
  __REG32 PCK0RDY             : 1;
  __REG32 PCK1RDY             : 1;
  __REG32 PCK2RDY             : 1;
  __REG32 PCK3RDY             : 1;
  __REG32 PCK4RDY             : 1;
  __REG32 PCK5RDY             : 1;
  __REG32 PCK6RDY             : 1;
  __REG32 PCK7RDY             : 1;
  __REG32                     : 16;
} __PMC_IER_bits;


/* ST Control Register */
typedef struct {
  __REG32 WDRST               : 1;
  __REG32                     : 31;
} __ST_CR_bits;

/* ST Period Interval Mode Register */
typedef struct {
  __REG32 PIV                 : 16;
  __REG32                     : 16;
} __ST_PIMR_bits;

/* ST Watchdog Mode Register */
typedef struct {
  __REG32 WDV                 : 16;
  __REG32 RSTEN               : 1;
  __REG32 EXTEN               : 1;
  __REG32                     : 14;
} __ST_WDMR_bits;

/* ST Real-Time Mode Register */
typedef struct {
  __REG32 RTPRES              : 16;
  __REG32                     : 16;
} __ST_RTMR_bits;

/* ST Status Register */
typedef struct {
  __REG32 PITS                : 1;
  __REG32 WDOVF               : 1;
  __REG32 RTTINC              : 1;
  __REG32 ALMS                : 1;
  __REG32                     : 28;
} __ST_SR_bits;

/* ST Real-time Alarm Register */
typedef struct {
  __REG32 ALMV                : 20;
  __REG32                     : 12;
} __ST_RTAR_bits;

/* ST Current Real-Time Register */
typedef struct {
  __REG32 CRTV                : 20;
  __REG32                     : 12;
} __ST_CRTR_bits;


/* RTC Control Register */
typedef struct {
  __REG32 UPDTIM              : 1;
  __REG32 UPDCAL              : 1;
  __REG32                     : 6;
  __REG32 TIMEVSEL            : 2;
  __REG32                     : 6;
  __REG32 CALEVSEL            : 2;
  __REG32                     : 14;
} __RTC_CR_bits;

/* RTC Mode Register */
typedef struct {
  __REG32 HRMOD               : 1;
  __REG32                     : 31;
} __RTC_MR_bits;

/* RTC Time Register */
typedef struct {
  __REG32 SEC                 : 7;
  __REG32                     : 1;
  __REG32 MIN                 : 7;
  __REG32                     : 1;
  __REG32 HOUR                : 6;
  __REG32 AMPM                : 1;
  __REG32                     : 9;
} __RTC_TIMR_bits;

/* RTC Calendar Register */
typedef struct {
  __REG32 CENT                : 7;
  __REG32                     : 1;
  __REG32 YEAR                : 8;
  __REG32 MONTH               : 5;
  __REG32 DAY                 : 3;
  __REG32 DATE                : 6;
  __REG32                     : 2;
} __RTC_CALR_bits;

/* RTC Time Alarm Register */
typedef struct {
  __REG32 SEC                 : 7;
  __REG32 SECEN               : 1;
  __REG32 MIN                 : 7;
  __REG32 MINEN               : 1;
  __REG32 HOUR                : 6;
  __REG32 AMPM                : 1;
  __REG32 HOUREN              : 1;
  __REG32                     : 8;
} __RTC_TIMALR_bits;

/* RTC Calendar Alarm Register */
typedef struct {
  __REG32                     : 16;
  __REG32 MONTH               : 5;
  __REG32                     : 2;
  __REG32 MTHEN               : 1;
  __REG32 DATE                : 6;
  __REG32                     : 1;
  __REG32 DATEEN              : 1;
} __RTC_CALALR_bits;

/* RTC Status Register */
typedef struct {
  __REG32 ACKUPD              : 1;
  __REG32 ALARM               : 1;
  __REG32 SEC                 : 1;
  __REG32 TIMEV               : 1;
  __REG32 CALEV               : 1;
  __REG32                     : 27;
} __RTC_SR_bits;

/* RTC Status Clear Command Register */
typedef struct {
  __REG32 ACKCLR              : 1;
  __REG32 ALRCLR              : 1;
  __REG32 SECCLR              : 1;
  __REG32 TIMCLR              : 1;
  __REG32 CALCLR              : 1;
  __REG32                     : 27;
} __RTC_SCCR_bits;

/* RTC Interrupt Enable Register */
typedef struct {
  __REG32 ACKEN               : 1;
  __REG32 ALREN               : 1;
  __REG32 SECEN               : 1;
  __REG32 TIMEN               : 1;
  __REG32 CALEN               : 1;
  __REG32                     : 27;
} __RTC_IER_bits;

/* RTC Interrupt Disable Register */
typedef struct {
  __REG32 ACKDIS              : 1;
  __REG32 ALRDIS              : 1;
  __REG32 SECDIS              : 1;
  __REG32 TIMDIS              : 1;
  __REG32 CALDIS              : 1;
  __REG32                     : 27;
} __RTC_IDR_bits;

/* RTC Interrupt Mask Register */
typedef struct {
  __REG32 ACK                 : 1;
  __REG32 ALR                 : 1;
  __REG32 SEC                 : 1;
  __REG32 TIM                 : 1;
  __REG32 CAL                 : 1;
  __REG32                     : 27;
} __RTC_IMR_bits;

/* RTC Valid Entry Register */
typedef struct {
  __REG32 NVTIM               : 1;
  __REG32 NVCAL               : 1;
  __REG32 NVTIMALR            : 1;
  __REG32 NVCALAR             : 1;
  __REG32                     : 28;
} __RTC_VER_bits;


/* Debug Unit Control Register */
typedef struct {
  __REG32                     : 2;
  __REG32 RSTRX               : 1;
  __REG32 RSTTX               : 1;
  __REG32 RXEN                : 1;
  __REG32 RXDIS               : 1;
  __REG32 TXEN                : 1;
  __REG32 TXDIS               : 1;
  __REG32 RSTSTA              : 1;
  __REG32                     : 23;
} __DBGU_CR_bits;

/* Debug Unit Mode Register */
typedef struct {
  __REG32                     : 9;
  __REG32 PAR                 : 3;
  __REG32                     : 2;
  __REG32 CHMODE              : 2;
  __REG32                     : 16;
} __DBGU_MR_bits;

/* Debug Unit Interrupt Enable Register */
typedef struct {
  __REG32 RXRDY               : 1;
  __REG32 TXRDY               : 1;
  __REG32                     : 1;
  __REG32 ENDRX               : 1;
  __REG32 ENDTX               : 1;
  __REG32 OVRE                : 1;
  __REG32 FRAME               : 1;
  __REG32 PARE                : 1;
  __REG32                     : 1;
  __REG32 TXEMPTY             : 1;
  __REG32                     : 1;
  __REG32 TXBUFE              : 1;
  __REG32 RXBUFF              : 1;
  __REG32                     : 17;
  __REG32 COMMTX              : 1;
  __REG32 COMMRX              : 1;
} __DBGU_IER_bits;

/* Debug Unit Receiver Holding Register */
typedef struct {
  __REG32 RXCHR               : 8;
  __REG32                     : 24;
} __DBGU_RHR_bits;

/* Debug Unit Transmit Holding Register */
typedef struct {
  __REG32 TXCHR               : 8;
  __REG32                     : 24;
} __DBGU_THR_bits;

/* Debug Unit Baud Rate Generator Register */
typedef struct {
  __REG32 CD                  : 16;
  __REG32                     : 16;
} __DBGU_BRGR_bits;

/* Debug Unit Chip ID Register */
typedef struct {
  __REG32 VERSION             : 5;
  __REG32 EPROC               : 3;
  __REG32 NVPSIZ              : 4;
  __REG32                     : 4;
  __REG32 SRAMSIZ             : 4;
  __REG32 ARCH                : 8;
  __REG32 NVPTYP              : 3;
  __REG32 EXT                 : 1;
} __DBGU_CIDR_bits;

/* Debug Unit Force NTRST Register */
typedef struct {
  __REG32 FNTRST              : 1;
  __REG32                     : 31;
} __DBGU_FNR_bits;


/* PIO Registers */
typedef struct {
  __REG32 P0                  : 1;
  __REG32 P1                  : 1;
  __REG32 P2                  : 1;
  __REG32 P3                  : 1;
  __REG32 P4                  : 1;
  __REG32 P5                  : 1;
  __REG32 P6                  : 1;
  __REG32 P7                  : 1;
  __REG32 P8                  : 1;
  __REG32 P9                  : 1;
  __REG32 P10                 : 1;
  __REG32 P11                 : 1;
  __REG32 P12                 : 1;
  __REG32 P13                 : 1;
  __REG32 P14                 : 1;
  __REG32 P15                 : 1;
  __REG32 P16                 : 1;
  __REG32 P17                 : 1;
  __REG32 P18                 : 1;
  __REG32 P19                 : 1;
  __REG32 P20                 : 1;
  __REG32 P21                 : 1;
  __REG32 P22                 : 1;
  __REG32 P23                 : 1;
  __REG32 P24                 : 1;
  __REG32 P25                 : 1;
  __REG32 P26                 : 1;
  __REG32 P27                 : 1;
  __REG32 P28                 : 1;
  __REG32 P29                 : 1;
  __REG32 P30                 : 1;
  __REG32 P31                 : 1;
} __PIO_REG_bits;


/* SPI Control Register */
typedef struct {
  __REG32 SPIEN               : 1;
  __REG32 SPIDIS              : 1;
  __REG32                     : 5;
  __REG32 SWRST               : 1;
  __REG32                     : 24;
} __SPI_CR_bits;

/* SPI Mode Register */
typedef struct {
  __REG32 MSTR                : 1;
  __REG32 PS                  : 1;
  __REG32 PCSDEC              : 1;
  __REG32 DIV32               : 1;
  __REG32 MODFDIS             : 1;
  __REG32                     : 2;
  __REG32 LLB                 : 1;
  __REG32                     : 8;
  __REG32 PCS                 : 4;
  __REG32                     : 4;
  __REG32 DLYBCS              : 8;
} __SPI_MR_bits;

/* SPI Receive Data Register */
typedef struct {
  __REG32 RD                  : 16;
  __REG32 PCS                 : 4;
  __REG32                     : 12;
} __SPI_RDR_bits;

/* SPI Transmit Data Register */
typedef struct {
  __REG32 TD                  : 16;
  __REG32 PCS                 : 4;
  __REG32                     : 12;
} __SPI_TDR_bits;

/* SPI Status Register */
typedef struct {
  __REG32 RDRF                : 1;
  __REG32 TDRE                : 1;
  __REG32 MODF                : 1;
  __REG32 OVRES               : 1;
  __REG32 ENDRX               : 1;
  __REG32 ENDTX               : 1;
  __REG32 RXBUFF              : 1;
  __REG32 TXBUFE              : 1;
  __REG32                     : 8;
  __REG32 SPIENS              : 1;
  __REG32                     : 15;
} __SPI_SR_bits;

/* SPI Interrupt Enable Register */
typedef struct {
  __REG32 RDRF                : 1;
  __REG32 TDRE                : 1;
  __REG32 MODF                : 1;
  __REG32 OVRES               : 1;
  __REG32 ENDRX               : 1;
  __REG32 ENDTX               : 1;
  __REG32 RXBUFF              : 1;
  __REG32 TXBUFE              : 1;
  __REG32                     : 24;
} __SPI_IER_bits;

/* SPI Chip Select Register */
typedef struct {
  __REG32 CPOL                : 1;
  __REG32 NCPHA               : 1;
  __REG32                     : 2;
  __REG32 BITS                : 4;
  __REG32 SCBR                : 8;
  __REG32 DLYBS               : 8;
  __REG32 DLYBCT              : 8;
} __SPI_CSR_bits;


/* TWI Control Register */
typedef struct {
  __REG32 START               : 1;
  __REG32 STOP                : 1;
  __REG32 MSEN                : 1;
  __REG32 MSDIS               : 1;
  __REG32                     : 3;
  __REG32 SWRST               : 1;
  __REG32                     : 24;
} __TWI_CR_bits;

/* TWI Master Mode Register */
typedef struct {
  __REG32                     : 8;
  __REG32 IADRSZ              : 2;
  __REG32                     : 2;
  __REG32 MREAD               : 1;
  __REG32                     : 3;
  __REG32 DADR                : 7;
  __REG32                     : 9;
} __TWI_MMR_bits;

/* TWI Internal Address Register */
typedef struct {
  __REG32 IADR                : 24;
  __REG32                     : 8;
} __TWI_IADR_bits;

/* TWI Clock Waveform Generator Register */
typedef struct {
  __REG32 CLDIV               : 8;
  __REG32 CHDIV               : 8;
  __REG32 CKDIV               : 3;
  __REG32                     : 13;
} __TWI_CWGR_bits;

/* TWI Status Register */
typedef struct {
  __REG32 TXCOMP              : 1;
  __REG32 RXRDY               : 1;
  __REG32 TXRDY               : 1;
  __REG32                     : 3;
  __REG32 OVRE                : 1;
  __REG32 UNRE                : 1;
  __REG32 NACK                : 1;
  __REG32                     : 23;
} __TWI_SR_bits;

/* TWI Receive Holding Register */
typedef struct {
  __REG32 RXDATA              : 8;
  __REG32                     : 24;
} __TWI_RHR_bits;

/* TWI Transmit Holding Register */
typedef struct {
  __REG32 TXDATA              : 8;
  __REG32                     : 24;
} __TWI_THR_bits;


/* USART Control Register */
typedef struct {
  __REG32                     : 2;
  __REG32 RSTRX               : 1;
  __REG32 RSTTX               : 1;
  __REG32 RXEN                : 1;
  __REG32 RXDIS               : 1;
  __REG32 TXEN                : 1;
  __REG32 TXDIS               : 1;
  __REG32 RSTSTA              : 1;
  __REG32 STTBRK              : 1;
  __REG32 STPBRK              : 1;
  __REG32 STTTO               : 1;
  __REG32 SENDA               : 1;
  __REG32 RSTIT               : 1;
  __REG32 RSTNACK             : 1;
  __REG32 RETTO               : 1;
  __REG32 DTREN               : 1;
  __REG32 DTRDIS              : 1;
  __REG32 RTSEN               : 1;
  __REG32 RTSDIS              : 1;
  __REG32                     : 12;
} __US_CR_bits;

/* USART Mode Register */
typedef struct {
  __REG32 USART_MODE          : 4;
  __REG32 USCLKS              : 2;
  __REG32 CHRL                : 2;
  __REG32 SYNC                : 1;
  __REG32 PAR                 : 3;
  __REG32 NBSTOP              : 2;
  __REG32 CHMODE              : 2;
  __REG32 MSBF                : 1;
  __REG32 MODE9               : 1;
  __REG32 CLKO                : 1;
  __REG32 OVER                : 1;
  __REG32 INACK               : 1;
  __REG32 DSNACK              : 1;
  __REG32                     : 2;
  __REG32 MAX_ITERATION       : 3;
  __REG32                     : 1;
  __REG32 FILTER              : 1;
  __REG32                     : 3;
} __US_MR_bits;

/* USART Interrupt Enable Register */
typedef struct {
  __REG32 RXRDY               : 1;
  __REG32 TXRDY               : 1;
  __REG32 RXBRK               : 1;
  __REG32 ENDRX               : 1;
  __REG32 ENDTX               : 1;
  __REG32 OVRE                : 1;
  __REG32 FRAME               : 1;
  __REG32 PARE                : 1;
  __REG32 TIMEOUT             : 1;
  __REG32 TXEMPTY             : 1;
  __REG32 ITERATION           : 1;
  __REG32 TXBUFE              : 1;
  __REG32 RXBUFF              : 1;
  __REG32 NACK                : 1;
  __REG32                     : 2;
  __REG32 RIIC                : 1;
  __REG32 DSRIC               : 1;
  __REG32 DCDIC               : 1;
  __REG32 CTSIC               : 1;
  __REG32                     : 12;
} __US_IER_bits;

/* USART Channel Status Register */
typedef struct {
  __REG32 RXRDY               : 1;
  __REG32 TXRDY               : 1;
  __REG32 RXBRK               : 1;
  __REG32 ENDRX               : 1;
  __REG32 ENDTX               : 1;
  __REG32 OVRE                : 1;
  __REG32 FRAME               : 1;
  __REG32 PARE                : 1;
  __REG32 TIMEOUT             : 1;
  __REG32 TXEMPTY             : 1;
  __REG32 ITERATION           : 1;
  __REG32 TXBUFE              : 1;
  __REG32 RXBUFF              : 1;
  __REG32 NACK                : 1;
  __REG32                     : 2;
  __REG32 RIIC                : 1;
  __REG32 DSRIC               : 1;
  __REG32 DCDIC               : 1;
  __REG32 CTSIC               : 1;
  __REG32 RI                  : 1;
  __REG32 DSR                 : 1;
  __REG32 DCD                 : 1;
  __REG32 CTS                 : 1;
  __REG32                     : 8;
} __US_CSR_bits;

/* USART Receive Holding Register */
typedef struct {
  __REG32 RXCHR               : 9;
  __REG32                     : 23;
} __US_RHR_bits;

/* USART Transmit Holding Register */
typedef struct {
  __REG32 TXCHR               : 9;
  __REG32                     : 23;
} __US_THR_bits;

/* USART Baud Rate Generator Register */
typedef struct {
  __REG32 CD                  : 16;
  __REG32                     : 16;
} __US_BRGR_bits;

/* USART Receiver Time-out Register */
typedef struct {
  __REG32 TO                  : 16;
  __REG32                     : 16;
} __US_RTOR_bits;

/* USART Transmitter Timeguard Register */
typedef struct {
  __REG32 TG                  : 8;
  __REG32                     : 24;
} __US_TTGR_bits;

/* USART FI DI RATIO Register */
typedef struct {
  __REG32 FI_DI_RATIO         : 11;
  __REG32                     : 21;
} __US_FIDI_bits;

/* USART Number of Errors Register */
typedef struct {
  __REG32 NB_ERRORS           : 8;
  __REG32                     : 24;
} __US_NER_bits;

/* USART IrDA FILTER Register */
typedef struct {
  __REG32 IRDA_FILTER         : 8;
  __REG32                     : 24;
} __US_IF_bits;


/* SSC Control Register */
typedef struct {
  __REG32 RXEN                : 1;
  __REG32 RXDIS               : 1;
  __REG32                     : 6;
  __REG32 TXEN                : 1;
  __REG32 TXDIS               : 1;
  __REG32                     : 5;
  __REG32 SWRST               : 1;
  __REG32                     : 16;
} __SSC_CR_bits;

/* SSC Clock Mode Register */
typedef struct {
  __REG32 DIV                 : 12;
  __REG32                     : 20;
} __SSC_CMR_bits;

/* SSC Receive Clock Mode Register */
typedef struct {
  __REG32 CKS                 : 2;
  __REG32 CKO                 : 3;
  __REG32 CKI                 : 1;
  __REG32                     : 2;
  __REG32 START               : 4;
  __REG32                     : 4;
  __REG32 STTDLY              : 8;
  __REG32 PERIOD              : 8;
} __SSC_RCMR_bits;

/* SSC Receive Frame Mode Register */
typedef struct {
  __REG32 DATLEN              : 5;
  __REG32 LOOP                : 1;
  __REG32                     : 1;
  __REG32 MSBF                : 1;
  __REG32 DATNB               : 4;
  __REG32                     : 4;
  __REG32 FSLEN               : 4;
  __REG32 FSOS                : 3;
  __REG32                     : 1;
  __REG32 FSEDGE              : 1;
  __REG32                     : 7;
} __SSC_RFMR_bits;

/* SSC Transmit Clock Mode Register */
typedef struct {
  __REG32 CKS                 : 2;
  __REG32 CKO                 : 3;
  __REG32 CKI                 : 1;
  __REG32                     : 2;
  __REG32 START               : 4;
  __REG32                     : 4;
  __REG32 STTDLY              : 8;
  __REG32 PERIOD              : 8;
} __SSC_TCMR_bits;

/* SSC Transmit Frame Mode Register */
typedef struct {
  __REG32 DATLEN              : 5;
  __REG32 DATDEF              : 1;
  __REG32                     : 1;
  __REG32 MSBF                : 1;
  __REG32 DATNB               : 4;
  __REG32                     : 4;
  __REG32 FSLEN               : 4;
  __REG32 FSOS                : 3;
  __REG32 FSDEN               : 1;
  __REG32 FSEDGE              : 1;
  __REG32                     : 7;
} __SSC_TFMR_bits;

/* SSC Receive Synchronization Holding Register */
typedef struct {
  __REG32 RSDAT               : 16;
  __REG32                     : 16;
} __SSC_RSHR_bits;

/* SSC Transmit Synchronization Holding Register */
typedef struct {
  __REG32 TSDAT               : 16;
  __REG32                     : 16;
} __SSC_TSHR_bits;

/* SSC Status Register */
typedef struct {
  __REG32 TXRDY               : 1;
  __REG32 TXEMPTY             : 1;
  __REG32 ENDTX               : 1;
  __REG32 TXBUFE              : 1;
  __REG32 RXRDY               : 1;
  __REG32 OVRUN               : 1;
  __REG32 ENDRX               : 1;
  __REG32 RXBUFF              : 1;
  __REG32                     : 2;
  __REG32 TXSYN               : 1;
  __REG32 RXSYN               : 1;
  __REG32                     : 4;
  __REG32 TXEN                : 1;
  __REG32 RXEN                : 1;
  __REG32                     : 14;
} __SSC_SR_bits;

/* SSC Interrupt Enable Register */
typedef struct {
  __REG32 TXRDY               : 1;
  __REG32 TXEMPTY             : 1;
  __REG32 ENDTX               : 1;
  __REG32 TXBUFE              : 1;
  __REG32 RXRDY               : 1;
  __REG32 OVRUN               : 1;
  __REG32 ENDRX               : 1;
  __REG32 RXBUFF              : 1;
  __REG32                     : 2;
  __REG32 TXSYN               : 1;
  __REG32 RXSYN               : 1;
  __REG32                     : 20;
} __SSC_IER_bits;


/* TC block control register */
typedef struct {
  __REG32 SYNC    :1;
  __REG32         :31;
} __tcbcr_bits;

/* TC block mode register */
typedef struct {
  __REG32 TC0XC0S :2;
  __REG32 TC1XC1S :2;
  __REG32 TC2XC2S :2;
  __REG32         :26;
} __tcbmr_bits;

/* TC channel control register */
typedef struct {
  __REG32 CLKEN   :1;
  __REG32 CLKDIS  :1;
  __REG32 SWTRG   :1;
  __REG32         :29;
} __tcccr_bits;

/* TC channel mode register: capture mode */
typedef struct {
  __REG32 TCCLKS  :3;
  __REG32 CLKI    :1;
  __REG32 BURST   :2;
  __REG32 LDBSTOP :1;
  __REG32 LDBDIS  :1;
  __REG32 ETRGEDG :2;
  __REG32 ABETRG  :1;	
  __REG32         :3;	
  __REG32 CPCTRG  :1;
  __REG32 WAVE    :1;
  __REG32 LDRA    :2;
  __REG32 LDRB    :2;
  __REG32         :12;	 
} __tccmrcm_bits;

/* TC channel mode register: waveform mode */
typedef struct {
  __REG32 TCCLKS  :3;
  __REG32 CLKI    :1;
  __REG32 BURST   :2;
  __REG32 CPCSTOP :1;
  __REG32 CPCDIS  :1;
  __REG32 EEVTEDG :2;
  __REG32 EEVT    :2;	
  __REG32 ENETRG  :1;	
  __REG32         :1;
  __REG32 CPCTRG  :1;
  __REG32 WAVE    :1;
  __REG32 ACPA    :2;
  __REG32 ACPC    :2;
  __REG32 AEEVT   :2;
  __REG32 ASWTRG  :2;
  __REG32 BCPB    :2;
  __REG32 BCPC    :2;
  __REG32 BEEVT   :2;
  __REG32 BSWTRG  :2;
} __tccmrwm_bits;


/* TC counter value register */
typedef struct {
  __REG32 CV      :16;
  __REG32         :16;
} __tccvr_bits;

/* TC register A */
typedef struct {
  __REG32 RA      :16;
  __REG32         :16;
} __tcra_bits;

/* TC register B */
typedef struct {
  __REG32 RB      :16;
  __REG32         :16;
} __tcrb_bits;

/* TC register C */
typedef struct {
  __REG32 RC      :16;
  __REG32         :16;
} __tcrc_bits;

/* TC status register */
typedef struct {
  __REG32 COVFS   :1;
  __REG32 LOVRS   :1;
  __REG32 CPAS    :1;
  __REG32 CPBS    :1;
  __REG32 CPCS    :1;
  __REG32 LDRAS   :1;
  __REG32 LDRBS   :1;
  __REG32 ETRGS   :1;
  __REG32         :8;
  __REG32 CLKSTA  :1;	
  __REG32 MTIOA   :1;
  __REG32 MTIOB   :1;
  __REG32         :13;
} __tcsr_bits;

/* TC interrupt enable/disable/mask register */
typedef struct {
  __REG32 COVFS   :1;
  __REG32 LOVRS   :1;
  __REG32 CPAS    :1;
  __REG32 CPBS    :1;
  __REG32 CPCS    :1;
  __REG32 LDRAS   :1;
  __REG32 LDRBS   :1;
  __REG32 ETRGS   :1;
  __REG32         :24;
} __tcir_bits;


/* MCI Control Register */
typedef struct {
  __REG32 MCIEN               : 1;
  __REG32 MCIDIS              : 1;
  __REG32 PWSEN               : 1;
  __REG32 PWSDIS              : 1;
  __REG32                     : 28;
} __MCI_CR_bits;

/* MCI Mode Register */
typedef struct {
  __REG32 CLKDIV              : 8;
  __REG32 PWSDIV              : 3;
  __REG32                     : 3;
  __REG32 PDCPADV             : 1;
  __REG32 PDCMODE             : 1;
  __REG32                     : 2;
  __REG32 BLKLEN              : 12;
  __REG32                     : 2;
} __MCI_MR_bits;

/* MCI Data Timeout Register */
typedef struct {
  __REG32 DTOCYC              : 4;
  __REG32 DTOMUL              : 3;
  __REG32                     : 25;
} __MCI_DTOR_bits;

/* MCI SD Card Register */
typedef struct {
  __REG32 SDCSEL              : 4;
  __REG32                     : 3;
  __REG32 SDCBUS              : 1;
  __REG32                     : 24;
} __MCI_SDCR_bits;

/* MCI Command Register */
typedef struct {
  __REG32 CMDNB               : 6;
  __REG32 RSPTYP              : 2;
  __REG32 SPCMD               : 3;
  __REG32 OPDCMD              : 1;
  __REG32 MAXLAT              : 1;
  __REG32                     : 3;
  __REG32 TRCMD               : 2;
  __REG32 TRDIR               : 1;
  __REG32 TRTYPE              : 1;
  __REG32                     : 12;
} __MCI_CMDR_bits;

/* MCI Status Register */
typedef struct {
  __REG32 CMDRDY              : 1;
  __REG32 RXRDY               : 1;
  __REG32 TXRDY               : 1;
  __REG32 BLKE                : 1;
  __REG32 DTIP                : 1;
  __REG32 NOTBUSY             : 1;
  __REG32 ENDRX               : 1;
  __REG32 ENDTX               : 1;
  __REG32                     : 6;
  __REG32 RXBUFF              : 1;
  __REG32 TXBUFE              : 1;
  __REG32 RINDE               : 1;
  __REG32 RDIRE               : 1;
  __REG32 RCRCE               : 1;
  __REG32 RENDE               : 1;
  __REG32 RTOE                : 1;
  __REG32 TCRCE               : 1;
  __REG32 DTOE                : 1;
  __REG32                     : 7;
  __REG32 OVRE                : 1;
  __REG32 UNRE                : 1;
} __MCI_SR_bits;


/* USB Frame Number Register */
typedef struct {
  __REG32 FRM_NUM             : 11;
  __REG32                     : 5;
  __REG32 FRM_ERR             : 1;
  __REG32 FRM_OK              : 1;
  __REG32                     : 14;
} __USB_FRM_NUM_bits;

/* USB Global State Register */
typedef struct {
  __REG32 FADDEN              : 1;
  __REG32 CONFG               : 1;
  __REG32 ESR                 : 1;
  __REG32 RSMINPR             : 1;
  __REG32 RMWUPE              : 1;
  __REG32                     : 27;
} __USB_GLB_STAT_bits;

/* USB Function Address Register */
typedef struct {
  __REG32 FADD                : 7;
  __REG32                     : 1;
  __REG32 FEN                 : 1;
  __REG32                     : 23;
} __USB_FADDR_bits;

/* USB Interrupt Enable Register */
typedef struct {
  __REG32 EP0INT              : 1;
  __REG32 EP1INT              : 1;
  __REG32 EP2INT              : 1;
  __REG32 EP3INT              : 1;
  __REG32 EP4INT              : 1;
  __REG32 EP5INT              : 1;
  __REG32 EP6INT              : 1;
  __REG32 EP7INT              : 1;
  __REG32 RXSUSP              : 1;
  __REG32 RXRSM               : 1;
  __REG32 EXTRSM              : 1;
  __REG32 SOFINT              : 1;
  __REG32                     : 1;
  __REG32 WAKEUP              : 1;
  __REG32                     : 18;
} __USB_IER_bits;

/* USB Interrupt Status Register */
typedef struct {
  __REG32 EP0INT              : 1;
  __REG32 EP1INT              : 1;
  __REG32 EP2INT              : 1;
  __REG32 EP3INT              : 1;
  __REG32 EP4INT              : 1;
  __REG32 EP5INT              : 1;
  __REG32 EP6INT              : 1;
  __REG32 EP7INT              : 1;
  __REG32 RXSUSP              : 1;
  __REG32 RXRSM               : 1;
  __REG32 EXTRSM              : 1;
  __REG32 SOFINT              : 1;
  __REG32 ENDBUSRES           : 1;
  __REG32 WAKEUP              : 1;
  __REG32                     : 18;
} __USB_ISR_bits;

/* USB Interrupt Clear Register */
typedef struct {
  __REG32                     : 8;
  __REG32 RXSUSP              : 1;
  __REG32 RXRSM               : 1;
  __REG32 EXTRSM              : 1;
  __REG32 SOFINT              : 1;
  __REG32 ENDBURST            : 1;
  __REG32 WAKEUP              : 1;
  __REG32                     : 18;
} __USB_ICR_bits;

/* USB Reset Endpoint Register */
typedef struct {
  __REG32 EP0                 : 1;
  __REG32 EP1                 : 1;
  __REG32 EP2                 : 1;
  __REG32 EP3                 : 1;
  __REG32 EP4                 : 1;
  __REG32 EP5                 : 1;
  __REG32 EP6                 : 1;
  __REG32 EP7                 : 1;
  __REG32                     : 24;
} __USB_RST_EP_bits;

/* USB Endpoint Control and Status Register */
typedef struct {
  __REG32 TXCOMP              : 1;
  __REG32 RX_DATA_BK0         : 1;
  __REG32 RXSETUP             : 1;
  __REG32 STALLSENT_ISOERROR  : 1;
  __REG32 TXPKTRDY            : 1;
  __REG32 FORCE_STALL         : 1;
  __REG32 RX_DATA_BK1         : 1;
  __REG32 DIR                 : 1;
  __REG32 EPTYPE              : 3;
  __REG32 DTGLE               : 1;
  __REG32                     : 3;
  __REG32 EPEDS               : 1;
  __REG32 RXBYTECNT           : 11;
  __REG32                     : 5;
} __USB_CSR_bits;

/* USB FIFO Data Register */
typedef struct {
  __REG32 FIFO_DATA           : 8;
  __REG32                     : 24;
} __USB_FDR_bits;


/* EMAC Control Register */
typedef struct {
  __REG32 LB                  : 1;
  __REG32 LBL                 : 1;
  __REG32 RE                  : 1;
  __REG32 TE                  : 1;
  __REG32 MPE                 : 1;
  __REG32 CSR                 : 1;
  __REG32 ISR                 : 1;
  __REG32 WES                 : 1;
  __REG32 BP                  : 1;
  __REG32                     : 23;
} __ETH_CTL_bits;

/* EMAC Configuration Register */
typedef struct {
  __REG32 SPD                 : 1;
  __REG32 FD                  : 1;
  __REG32 BR                  : 1;
  __REG32                     : 1;
  __REG32 CAF                 : 1;
  __REG32 NBC                 : 1;
  __REG32 MTI                 : 1;
  __REG32 UNI                 : 1;
  __REG32 BIG                 : 1;
  __REG32 EAE                 : 1;
  __REG32 CLK                 : 2;
  __REG32 RTY                 : 1;
  __REG32 RMII                : 1;
  __REG32                     : 18;
} __ETH_CFG_bits;

/* EMAC Status Register */
typedef struct {
  __REG32 LINK                : 1;
  __REG32 MDIO                : 1;
  __REG32 IDLE                : 1;
  __REG32                     : 29;
} __ETH_SR_bits;

/* EMAC Transmit Control Register */
typedef struct {
  __REG32 LEN                 : 11;
  __REG32                     : 4;
  __REG32 NCRC                : 1;
  __REG32                     : 16;
} __ETH_TCR_bits;

/* EMAC Transmit Status Register */
typedef struct {
  __REG32 OVR                 : 1;
  __REG32 COL                 : 1;
  __REG32 RLE                 : 1;
  __REG32 IDLE                : 1;
  __REG32 BNQ                 : 1;
  __REG32 COMP                : 1;
  __REG32 UND                 : 1;
  __REG32                     : 25;
} __ETH_TSR_bits;

/* EMAC Receive Status Register */
typedef struct {
  __REG32 BNA                 : 1;
  __REG32 REC                 : 1;
  __REG32 OVR                 : 1;
  __REG32                     : 29;
} __ETH_RSR_bits;

/* EMAC Interrupt Status Register */
typedef struct {
  __REG32 DONE                : 1;
  __REG32 RCOM                : 1;
  __REG32 RBNA                : 1;
  __REG32 TOVR                : 1;
  __REG32 TUND                : 1;
  __REG32 RTRY                : 1;
  __REG32 TBRE                : 1;
  __REG32 TCOM                : 1;
  __REG32 TIDLE               : 1;
  __REG32 LINK                : 1;
  __REG32 ROVR                : 1;
  __REG32 ABT                 : 1;
  __REG32                     : 20;
} __ETH_ISR_bits;

/* EMAC PHY Maintenance Register */
typedef struct {
  __REG32 DATA                : 16;
  __REG32 CODE                : 2;
  __REG32 REGA                : 5;
  __REG32 PHYA                : 5;
  __REG32 RW                  : 2;
  __REG32 HIGH                : 1;
  __REG32 LOW                 : 1;
} __ETH_MAN_bits;

/* EMAC Specific Address (1, 2, 3 and 4) High Register */
typedef struct {
  __REG32 ADDR                : 16;
  __REG32                     : 16;
} __ETH_SAH_bits;

/* EMAC Specific Address (1, 2, 3 and 4) Low Register */
typedef struct {
  __REG32 ADDR                : 32;
} __ETH_SAL_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  MC
 **
 ***************************************************************************/
__IO_REG32_BIT(MC_RCR, 0xffffff00,__WRITE,__MC_RCR_bits);
__IO_REG32_BIT(MC_ASR, 0xffffff04,__READ,__MC_ASR_bits);
__IO_REG32(MC_AASR,0xffffff08,__READ);
__IO_REG32_BIT(MC_MPR, 0xffffff0c,__READ_WRITE,__MC_MPR_bits);


/***************************************************************************
 **
 **  EBI   
 **
 ***************************************************************************/
__IO_REG32_BIT(EBI_CSA, 0xffffff60,__READ_WRITE,__EBI_CSA_bits);
__IO_REG32_BIT(EBI_CFGR,0xffffff64,__READ_WRITE,__EBI_CFGR_bits);


/***************************************************************************
 **
 **  SMC   
 **
 ***************************************************************************/
__IO_REG32_BIT(SMC_CSR0,0xffffff70,__READ_WRITE,__SMC_CSR_bits);
__IO_REG32_BIT(SMC_CSR1,0xffffff74,__READ_WRITE,__SMC_CSR_bits);
__IO_REG32_BIT(SMC_CSR2,0xffffff78,__READ_WRITE,__SMC_CSR_bits);
__IO_REG32_BIT(SMC_CSR3,0xffffff7c,__READ_WRITE,__SMC_CSR_bits);
__IO_REG32_BIT(SMC_CSR4,0xffffff80,__READ_WRITE,__SMC_CSR_bits);
__IO_REG32_BIT(SMC_CSR5,0xffffff84,__READ_WRITE,__SMC_CSR_bits);
__IO_REG32_BIT(SMC_CSR6,0xffffff88,__READ_WRITE,__SMC_CSR_bits);
__IO_REG32_BIT(SMC_CSR7,0xffffff8c,__READ_WRITE,__SMC_CSR_bits);


/***************************************************************************
 **
 **  SDRAMC   
 **
 ***************************************************************************/
__IO_REG32_BIT(SDRAMC_MR, 0xffffff90,__READ_WRITE,__SDRAMC_MR_bits);
__IO_REG32_BIT(SDRAMC_TR, 0xffffff94,__READ_WRITE,__SDRAMC_TR_bits);
__IO_REG32_BIT(SDRAMC_CR, 0xffffff98,__READ_WRITE,__SDRAMC_CR_bits);
__IO_REG32_BIT(SDRAMC_SRR,0xffffff9c,__READ_WRITE,__SDRAMC_SRR_bits);
__IO_REG32_BIT(SDRAMC_LPR,0xffffffa0,__READ_WRITE,__SDRAMC_LPR_bits);
__IO_REG32_BIT(SDRAMC_IER,0xffffffa4,__READ_WRITE,__SDRAMC_IER_bits);
__IO_REG32_BIT(SDRAMC_IDR,0xffffffa8,__READ_WRITE,__SDRAMC_IER_bits);
__IO_REG32_BIT(SDRAMC_IMR,0xffffffac,__READ_WRITE,__SDRAMC_IER_bits);
__IO_REG32_BIT(SDRAMC_ISR,0xffffffb0,__READ_WRITE,__SDRAMC_IER_bits);


/***************************************************************************
 **
 **  BFC
 **
 ***************************************************************************/
__IO_REG32_BIT(BFC_MR,    0xffffffc0,__READ_WRITE,__BFC_MR_bits);


/***************************************************************************
 **
 **  AIC
 **
 ***************************************************************************/

//  Source mode register 
__IO_REG32_BIT(AIC_SMR0,0xfffff000,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR1,0xfffff004,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR2,0xfffff008,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR3,0xfffff00c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR4,0xfffff010,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR5,0xfffff014,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR6,0xfffff018,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR7,0xfffff01c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR8,0xfffff020,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR9,0xfffff024,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR10,0xfffff028,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR11,0xfffff02c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR12,0xfffff030,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR13,0xfffff034,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR14,0xfffff038,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR15,0xfffff03c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR16,0xfffff040,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR17,0xfffff044,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR18,0xfffff048,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR19,0xfffff04c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR20,0xfffff050,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR21,0xfffff054,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR22,0xfffff058,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR23,0xfffff05c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR24,0xfffff060,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR25,0xfffff064,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR26,0xfffff068,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR27,0xfffff06c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR28,0xfffff070,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR29,0xfffff074,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR30,0xfffff078,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(AIC_SMR31,0xfffff07c,__READ_WRITE,__aicsmr_bits);

// Source vector register
__IO_REG32_BIT(AIC_SVR0,0xfffff080,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR1,0xfffff084,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR2,0xfffff088,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR3,0xfffff08c,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR4,0xfffff090,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR5,0xfffff094,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR6,0xfffff098,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR7,0xfffff09c,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR8,0xfffff0a0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR9,0xfffff0a4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR10,0xfffff0a8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR11,0xfffff0ac,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR12,0xfffff0b0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR13,0xfffff0b4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR14,0xfffff0b8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR15,0xfffff0bc,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR16,0xfffff0c0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR17,0xfffff0c4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR18,0xfffff0c8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR19,0xfffff0cc,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR20,0xfffff0d0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR21,0xfffff0d4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR22,0xfffff0d8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR23,0xfffff0dc,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR24,0xfffff0e0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR25,0xfffff0e4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR26,0xfffff0e8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR27,0xfffff0ec,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR28,0xfffff0f0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR29,0xfffff0f4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR30,0xfffff0f8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(AIC_SVR31,0xfffff0fc,__READ_WRITE,__aicsvr_bits);

__IO_REG32_BIT(AIC_IVR,0xfffff100,__READ_WRITE,__aicivr_bits); 
__IO_REG32_BIT(AIC_FVR,0xfffff104,__READ,__aicfiqvr_bits);
__IO_REG32_BIT(AIC_ISR,0xfffff108,__READ,__aicisr_bits);
__IO_REG32_BIT(AIC_IPR,0xfffff10c,__READ,__aicir_bits);

__IO_REG32_BIT(AIC_IMR,0xfffff110,__READ,__aicir_bits);
__IO_REG32_BIT(AIC_CISR,0xfffff114,__READ,__aiccisr_bits);

__IO_REG32_BIT(AIC_IECR,0xfffff120,__WRITE,__aicir_bits);
__IO_REG32_BIT(AIC_IDCR,0xfffff124,__WRITE,__aicir_bits);
__IO_REG32_BIT(AIC_ICCR,0xfffff128,__WRITE,__aicir_bits);
__IO_REG32_BIT(AIC_ISCR,0xfffff12c,__WRITE,__aicir_bits);

__IO_REG32(AIC_EOICR,0xfffff130,__WRITE);
__IO_REG32(AIC_SPU,  0xfffff134,__READ_WRITE);

__IO_REG32_BIT(AIC_DCR, 0xfffff138,__READ_WRITE,__AIC_DCR_bits);
__IO_REG32_BIT(AIC_FFER,0xfffff140,__WRITE,__AIC_FFER_bits);
__IO_REG32_BIT(AIC_FFDR,0xfffff144,__WRITE,__AIC_FFER_bits);
__IO_REG32_BIT(AIC_FFSR,0xfffff148,__READ,__AIC_FFER_bits);


/***************************************************************************
 **
 **  PMC   
 **
 ***************************************************************************/
__IO_REG32_BIT(PMC_SCER, 0xfffffc00,__READ_WRITE,__PMC_SCER_bits);
__IO_REG32_BIT(PMC_SCDR, 0xfffffc04,__READ_WRITE,__PMC_SCER_bits);
__IO_REG32_BIT(PMC_SCSR, 0xfffffc08,__READ_WRITE,__PMC_SCER_bits);
__IO_REG32_BIT(PMC_PCER, 0xfffffc10,__READ_WRITE,__PMC_PCER_bits);
__IO_REG32_BIT(PMC_PCDR, 0xfffffc14,__READ_WRITE,__PMC_PCER_bits);
__IO_REG32_BIT(PMC_PCSR, 0xfffffc18,__READ_WRITE,__PMC_PCER_bits);
__IO_REG32_BIT(PMC_MOR,  0xfffffc20,__READ_WRITE,__PMC_MOR_bits);
__IO_REG32_BIT(PMC_MCFR, 0xfffffc24,__READ_WRITE,__PMC_MCFR_bits);
__IO_REG32_BIT(PMC_PLLAR,0xfffffc28,__READ_WRITE,__PMC_PLLAR_bits);
__IO_REG32_BIT(PMC_PLLBR,0xfffffc2c,__READ_WRITE,__PMC_PLLBR_bits);
__IO_REG32_BIT(PMC_MCKR, 0xfffffc30,__READ_WRITE,__PMC_MCKR_bits);
__IO_REG32_BIT(PMC_PCK0, 0xfffffc40,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_PCK1, 0xfffffc44,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_PCK2, 0xfffffc48,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_PCK3, 0xfffffc4c,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_PCK4, 0xfffffc50,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_PCK5, 0xfffffc54,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_PCK6, 0xfffffc58,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_PCK7, 0xfffffc5c,__READ_WRITE,__PMC_PCK_bits);
__IO_REG32_BIT(PMC_IER,  0xfffffc60,__READ_WRITE,__PMC_IER_bits);
__IO_REG32_BIT(PMC_IDR,  0xfffffc64,__READ_WRITE,__PMC_IER_bits);
__IO_REG32_BIT(PMC_SR,   0xfffffc68,__READ_WRITE,__PMC_IER_bits);
__IO_REG32_BIT(PMC_IMR,  0xfffffc6c,__READ_WRITE,__PMC_IER_bits);


/***************************************************************************
 **
 **  ST
 **
 ***************************************************************************/
__IO_REG32_BIT(ST_CR,  0xfffffd00,__READ_WRITE,__ST_CR_bits);
__IO_REG32_BIT(ST_PIMR,0xfffffd04,__READ_WRITE,__ST_PIMR_bits);
__IO_REG32_BIT(ST_WDMR,0xfffffd08,__READ_WRITE,__ST_WDMR_bits);
__IO_REG32_BIT(ST_RTMR,0xfffffd0c,__READ_WRITE,__ST_RTMR_bits);
__IO_REG32_BIT(ST_SR,  0xfffffd10,__READ_WRITE,__ST_SR_bits);
__IO_REG32_BIT(ST_IER, 0xfffffd14,__READ_WRITE,__ST_SR_bits);
__IO_REG32_BIT(ST_IDR, 0xfffffd18,__READ_WRITE,__ST_SR_bits);
__IO_REG32_BIT(ST_IMR, 0xfffffd1c,__READ_WRITE,__ST_SR_bits);
__IO_REG32_BIT(ST_RTAR,0xfffffd20,__READ_WRITE,__ST_RTAR_bits);
__IO_REG32_BIT(ST_CRTR,0xfffffd24,__READ_WRITE,__ST_CRTR_bits);


/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(RTC_CR,    0xfffffe00,__READ_WRITE,__RTC_CR_bits);
__IO_REG32_BIT(RTC_MR,    0xfffffe04,__READ_WRITE,__RTC_MR_bits);
__IO_REG32_BIT(RTC_TIMR,  0xfffffe08,__READ_WRITE,__RTC_TIMR_bits);
__IO_REG32_BIT(RTC_CALR,  0xfffffe0c,__READ_WRITE,__RTC_CALR_bits);
__IO_REG32_BIT(RTC_TIMALR,0xfffffe10,__READ_WRITE,__RTC_TIMALR_bits);
__IO_REG32_BIT(RTC_CALALR,0xfffffe14,__READ_WRITE,__RTC_CALALR_bits);
__IO_REG32_BIT(RTC_SR,    0xfffffe18,__READ_WRITE,__RTC_SR_bits);
__IO_REG32_BIT(RTC_SCCR,  0xfffffe1c,__READ_WRITE,__RTC_SCCR_bits);
__IO_REG32_BIT(RTC_IER,   0xfffffe20,__READ_WRITE,__RTC_IER_bits);
__IO_REG32_BIT(RTC_IDR,   0xfffffe24,__READ_WRITE,__RTC_IDR_bits);
__IO_REG32_BIT(RTC_IMR,   0xfffffe28,__READ_WRITE,__RTC_IMR_bits);
__IO_REG32_BIT(RTC_VER,   0xfffffe2c,__READ_WRITE,__RTC_VER_bits);


/***************************************************************************
 **
 **  DBGU
 **
 ***************************************************************************/
__IO_REG32_BIT(DBGU_CR,  0xfffff200,__READ_WRITE,__DBGU_CR_bits);
__IO_REG32_BIT(DBGU_MR,  0xfffff204,__READ_WRITE,__DBGU_MR_bits);
__IO_REG32_BIT(DBGU_IER, 0xfffff208,__READ_WRITE,__DBGU_IER_bits);
__IO_REG32_BIT(DBGU_IDR, 0xfffff20c,__READ_WRITE,__DBGU_IER_bits);
__IO_REG32_BIT(DBGU_IMR, 0xfffff210,__READ_WRITE,__DBGU_IER_bits);
__IO_REG32_BIT(DBGU_SR,  0xfffff214,__READ_WRITE,__DBGU_IER_bits);
__IO_REG32_BIT(DBGU_RHR, 0xfffff218,__READ_WRITE,__DBGU_RHR_bits);
__IO_REG32_BIT(DBGU_THR, 0xfffff21c,__READ_WRITE,__DBGU_THR_bits);
__IO_REG32_BIT(DBGU_BRGR,0xfffff220,__READ_WRITE,__DBGU_BRGR_bits);
__IO_REG32_BIT(DBGU_CIDR,0xfffff240,__READ_WRITE,__DBGU_CIDR_bits);
__IO_REG32(DBGU_EXID,0xfffff244,__READ_WRITE);
__IO_REG32_BIT(DBGU_FNR, 0xfffff248,__READ_WRITE,__DBGU_FNR_bits);

__IO_REG32(DBGU_RPR, 0xfffff300,__READ_WRITE);
__IO_REG32_BIT(DBGU_RCR, 0xfffff304,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(DBGU_TPR, 0xfffff308,__READ_WRITE);
__IO_REG32_BIT(DBGU_TCR, 0xfffff30c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(DBGU_RNPR,0xfffff310,__READ_WRITE);
__IO_REG32_BIT(DBGU_RNCR,0xfffff314,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(DBGU_TNPR,0xfffff318,__READ_WRITE);
__IO_REG32_BIT(DBGU_TNCR,0xfffff31c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(DBGU_PTCR,0xfffff320,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(DBGU_PTSR,0xfffff324,__READ_WRITE,__PERIPH_PTSR_bits);


/**************************************************************************
 **
 **  PIO A
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOA_PER, 0xfffff400,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_PDR, 0xfffff404,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_PSR, 0xfffff408,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_OER, 0xfffff410,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_ODR, 0xfffff414,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_OSR, 0xfffff418,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_IFER,0xfffff420,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_IFDR,0xfffff424,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_IFSR,0xfffff428,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_SODR,0xfffff430,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_CODR,0xfffff434,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_ODSR,0xfffff438,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_PDSR,0xfffff43c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_IER, 0xfffff440,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_IDR, 0xfffff444,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_IMR, 0xfffff448,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_ISR, 0xfffff44c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_MDER,0xfffff450,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_MDDR,0xfffff454,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_MDSR,0xfffff458,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_PUDR,0xfffff460,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_PUER,0xfffff464,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_PUSR,0xfffff468,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_ASR, 0xfffff470,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_BSR, 0xfffff474,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_ABSR,0xfffff478,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOA_OWER,0xfffff4a0,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_OWDR,0xfffff4a4,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOA_OWSR,0xfffff4a8,__READ,      __PIO_REG_bits);

__IO_REG32(PIOA_RPR, 0xfffff500,__READ_WRITE);
__IO_REG32_BIT(PIOA_RCR, 0xfffff504,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(PIOA_TPR, 0xfffff508,__READ_WRITE);
__IO_REG32_BIT(PIOA_TCR, 0xfffff50c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(PIOA_RNPR,0xfffff510,__READ_WRITE);
__IO_REG32_BIT(PIOA_RNCR,0xfffff514,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(PIOA_TNPR,0xfffff518,__READ_WRITE);
__IO_REG32_BIT(PIOA_TNCR,0xfffff51c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(PIOA_PTCR,0xfffff520,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(PIOA_PTSR,0xfffff524,__READ_WRITE,__PERIPH_PTSR_bits);


/**************************************************************************
 **
 **  PIO B
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOB_PER, 0xfffff600,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_PDR, 0xfffff604,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_PSR, 0xfffff608,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_OER, 0xfffff610,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_ODR, 0xfffff614,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_OSR, 0xfffff618,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_IFER,0xfffff620,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_IFDR,0xfffff624,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_IFSR,0xfffff628,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_SODR,0xfffff630,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_CODR,0xfffff634,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_ODSR,0xfffff638,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_PDSR,0xfffff63c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_IER, 0xfffff640,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_IDR, 0xfffff644,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_IMR, 0xfffff648,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_ISR, 0xfffff64c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_MDER,0xfffff650,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_MDDR,0xfffff654,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_MDSR,0xfffff658,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_PUDR,0xfffff660,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_PUER,0xfffff664,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_PUSR,0xfffff668,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_ASR, 0xfffff670,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_BSR, 0xfffff674,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_ABSR,0xfffff678,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOB_OWER,0xfffff6a0,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_OWDR,0xfffff6a4,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOB_OWSR,0xfffff6a8,__READ,      __PIO_REG_bits);

__IO_REG32(PIOB_RPR, 0xfffff700,__READ_WRITE);
__IO_REG32_BIT(PIOB_RCR, 0xfffff704,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(PIOB_TPR, 0xfffff708,__READ_WRITE);
__IO_REG32_BIT(PIOB_TCR, 0xfffff70c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(PIOB_RNPR,0xfffff710,__READ_WRITE);
__IO_REG32_BIT(PIOB_RNCR,0xfffff714,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(PIOB_TNPR,0xfffff718,__READ_WRITE);
__IO_REG32_BIT(PIOB_TNCR,0xfffff71c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(PIOB_PTCR,0xfffff720,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(PIOB_PTSR,0xfffff724,__READ_WRITE,__PERIPH_PTSR_bits);



/**************************************************************************
 **
 **  PIO C
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOC_PER, 0xfffff800,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_PDR, 0xfffff804,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_PSR, 0xfffff808,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_OER, 0xfffff810,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_ODR, 0xfffff814,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_OSR, 0xfffff818,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_IFER,0xfffff820,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_IFDR,0xfffff824,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_IFSR,0xfffff828,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_SODR,0xfffff830,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_CODR,0xfffff834,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_ODSR,0xfffff838,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_PDSR,0xfffff83c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_IER, 0xfffff840,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_IDR, 0xfffff844,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_IMR, 0xfffff848,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_ISR, 0xfffff84c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_MDER,0xfffff850,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_MDDR,0xfffff854,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_MDSR,0xfffff858,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_PUDR,0xfffff860,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_PUER,0xfffff864,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_PUSR,0xfffff868,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_ASR, 0xfffff870,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_BSR, 0xfffff874,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_ABSR,0xfffff878,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOC_OWER,0xfffff8a0,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_OWDR,0xfffff8a4,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOC_OWSR,0xfffff8a8,__READ,      __PIO_REG_bits);

__IO_REG32(PIOC_RPR, 0xfffff900,__READ_WRITE);
__IO_REG32_BIT(PIOC_RCR, 0xfffff904,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(PIOC_TPR, 0xfffff908,__READ_WRITE);
__IO_REG32_BIT(PIOC_TCR, 0xfffff90c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(PIOC_RNPR,0xfffff910,__READ_WRITE);
__IO_REG32_BIT(PIOC_RNCR,0xfffff914,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(PIOC_TNPR,0xfffff918,__READ_WRITE);
__IO_REG32_BIT(PIOC_TNCR,0xfffff91c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(PIOC_PTCR,0xfffff920,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(PIOC_PTSR,0xfffff924,__READ_WRITE,__PERIPH_PTSR_bits);


/**************************************************************************
 **
 **  PIO D
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOD_PER, 0xfffffa00,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_PDR, 0xfffffa04,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_PSR, 0xfffffa08,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_OER, 0xfffffa10,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_ODR, 0xfffffa14,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_OSR, 0xfffffa18,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_IFER,0xfffffa20,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_IFDR,0xfffffa24,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_IFSR,0xfffffa28,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_SODR,0xfffffa30,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_CODR,0xfffffa34,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_ODSR,0xfffffa38,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_PDSR,0xfffffa3c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_IER, 0xfffffa40,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_IDR, 0xfffffa44,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_IMR, 0xfffffa48,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_ISR, 0xfffffa4c,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_MDER,0xfffffa50,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_MDDR,0xfffffa54,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_MDSR,0xfffffa58,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_PUDR,0xfffffa60,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_PUER,0xfffffa64,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_PUSR,0xfffffa68,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_ASR, 0xfffffa70,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_BSR, 0xfffffa74,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_ABSR,0xfffffa78,__READ,      __PIO_REG_bits);
__IO_REG32_BIT(PIOD_OWER,0xfffffaa0,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_OWDR,0xfffffaa4,__WRITE,     __PIO_REG_bits);
__IO_REG32_BIT(PIOD_OWSR,0xfffffaa8,__READ,      __PIO_REG_bits);

__IO_REG32(PIOD_RPR, 0xfffffb00,__READ_WRITE);
__IO_REG32_BIT(PIOD_RCR, 0xfffffb04,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(PIOD_TPR, 0xfffffb08,__READ_WRITE);
__IO_REG32_BIT(PIOD_TCR, 0xfffffb0c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(PIOD_RNPR,0xfffffb10,__READ_WRITE);
__IO_REG32_BIT(PIOD_RNCR,0xfffffb14,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(PIOD_TNPR,0xfffffb18,__READ_WRITE);
__IO_REG32_BIT(PIOD_TNCR,0xfffffb1c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(PIOD_PTCR,0xfffffb20,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(PIOD_PTSR,0xfffffb24,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  SPI   
 **
 ***************************************************************************/
__IO_REG32_BIT(SPI_CR,  0xfffe0000,__READ_WRITE,__SPI_CR_bits);
__IO_REG32_BIT(SPI_MR,  0xfffe0004,__READ_WRITE,__SPI_MR_bits);
__IO_REG32_BIT(SPI_RDR, 0xfffe0008,__READ_WRITE,__SPI_RDR_bits);
__IO_REG32_BIT(SPI_TDR, 0xfffe000c,__READ_WRITE,__SPI_TDR_bits);
__IO_REG32_BIT(SPI_SR,  0xfffe0010,__READ_WRITE,__SPI_SR_bits);
__IO_REG32_BIT(SPI_IER, 0xfffe0014,__READ_WRITE,__SPI_IER_bits);
__IO_REG32_BIT(SPI_IDR, 0xfffe0018,__READ_WRITE,__SPI_IER_bits);
__IO_REG32_BIT(SPI_IMR, 0xfffe001c,__READ_WRITE,__SPI_IER_bits);
__IO_REG32_BIT(SPI_CSR0,0xfffe0030,__READ_WRITE,__SPI_CSR_bits);
__IO_REG32_BIT(SPI_CSR1,0xfffe0034,__READ_WRITE,__SPI_CSR_bits);
__IO_REG32_BIT(SPI_CSR2,0xfffe0038,__READ_WRITE,__SPI_CSR_bits);
__IO_REG32_BIT(SPI_CSR3,0xfffe003c,__READ_WRITE,__SPI_CSR_bits);

__IO_REG32(SPI_RPR, 0xfffe0100,__READ_WRITE);
__IO_REG32_BIT(SPI_RCR, 0xfffe0104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(SPI_TPR, 0xfffe0108,__READ_WRITE);
__IO_REG32_BIT(SPI_TCR, 0xfffe010c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(SPI_RNPR,0xfffe0110,__READ_WRITE);
__IO_REG32_BIT(SPI_RNCR,0xfffe0114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(SPI_TNPR,0xfffe0118,__READ_WRITE);
__IO_REG32_BIT(SPI_TNCR,0xfffe011c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(SPI_PTCR,0xfffe0120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(SPI_PTSR,0xfffe0124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  TWI   
 **
 ***************************************************************************/
__IO_REG32_BIT(TWI_CR,  0xfffb8000,__READ_WRITE,__TWI_CR_bits);
__IO_REG32_BIT(TWI_MMR, 0xfffb8004,__READ_WRITE,__TWI_MMR_bits);
__IO_REG32_BIT(TWI_IADR,0xfffb800c,__READ_WRITE,__TWI_IADR_bits);
__IO_REG32_BIT(TWI_CWGR,0xfffb8010,__READ_WRITE,__TWI_CWGR_bits);
__IO_REG32_BIT(TWI_SR,  0xfffb8020,__READ_WRITE,__TWI_SR_bits);
__IO_REG32_BIT(TWI_IER, 0xfffb8024,__READ_WRITE,__TWI_SR_bits);
__IO_REG32_BIT(TWI_IDR, 0xfffb8028,__READ_WRITE,__TWI_SR_bits);
__IO_REG32_BIT(TWI_IMR, 0xfffb802c,__READ_WRITE,__TWI_SR_bits);
__IO_REG32_BIT(TWI_RHR, 0xfffb8030,__READ_WRITE,__TWI_RHR_bits);
__IO_REG32_BIT(TWI_THR, 0xfffb8034,__READ_WRITE,__TWI_THR_bits);

__IO_REG32(TWI_RPR, 0xfffb8100,__READ_WRITE);
__IO_REG32_BIT(TWI_RCR, 0xfffb8104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(TWI_TPR, 0xfffb8108,__READ_WRITE);
__IO_REG32_BIT(TWI_TCR, 0xfffb810c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(TWI_RNPR,0xfffb8110,__READ_WRITE);
__IO_REG32_BIT(TWI_RNCR,0xfffb8114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(TWI_TNPR,0xfffb8118,__READ_WRITE);
__IO_REG32_BIT(TWI_TNCR,0xfffb811c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(TWI_PTCR,0xfffb8120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(TWI_PTSR,0xfffb8124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  USART0
 **
 ***************************************************************************/
__IO_REG32_BIT(USART0_CR,  0xfffc0000,__READ_WRITE,__US_CR_bits);
__IO_REG32_BIT(USART0_MR,  0xfffc0004,__READ_WRITE,__US_MR_bits);
__IO_REG32_BIT(USART0_IER, 0xfffc0008,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART0_IDR, 0xfffc000c,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART0_IMR, 0xfffc0010,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART0_CSR, 0xfffc0014,__READ_WRITE,__US_CSR_bits);
__IO_REG32_BIT(USART0_RHR, 0xfffc0018,__READ_WRITE,__US_RHR_bits);
__IO_REG32_BIT(USART0_THR, 0xfffc001c,__READ_WRITE,__US_THR_bits);
__IO_REG32_BIT(USART0_BRGR,0xfffc0020,__READ_WRITE,__US_BRGR_bits);
__IO_REG32_BIT(USART0_RTOR,0xfffc0024,__READ_WRITE,__US_RTOR_bits);
__IO_REG32_BIT(USART0_TTGR,0xfffc0028,__READ_WRITE,__US_TTGR_bits);
__IO_REG32_BIT(USART0_FIDI,0xfffc0040,__READ_WRITE,__US_FIDI_bits);
__IO_REG32_BIT(USART0_NER, 0xfffc0044,__READ_WRITE,__US_NER_bits);
__IO_REG32_BIT(USART0_IF,  0xfffc004c,__READ_WRITE,__US_IF_bits);

__IO_REG32(USART0_RPR, 0xfffc0100,__READ_WRITE);
__IO_REG32_BIT(USART0_RCR, 0xfffc0104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(USART0_TPR, 0xfffc0108,__READ_WRITE);
__IO_REG32_BIT(USART0_TCR, 0xfffc010c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(USART0_RNPR,0xfffc0110,__READ_WRITE);
__IO_REG32_BIT(USART0_RNCR,0xfffc0114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(USART0_TNPR,0xfffc0118,__READ_WRITE);
__IO_REG32_BIT(USART0_TNCR,0xfffc011c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(USART0_PTCR,0xfffc0120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(USART0_PTSR,0xfffc0124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  USART1
 **
 ***************************************************************************/
__IO_REG32_BIT(USART1_CR,  0xfffc4000,__READ_WRITE,__US_CR_bits);
__IO_REG32_BIT(USART1_MR,  0xfffc4004,__READ_WRITE,__US_MR_bits);
__IO_REG32_BIT(USART1_IER, 0xfffc4008,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART1_IDR, 0xfffc400c,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART1_IMR, 0xfffc4010,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART1_CSR, 0xfffc4014,__READ_WRITE,__US_CSR_bits);
__IO_REG32_BIT(USART1_RHR, 0xfffc4018,__READ_WRITE,__US_RHR_bits);
__IO_REG32_BIT(USART1_THR, 0xfffc401c,__READ_WRITE,__US_THR_bits);
__IO_REG32_BIT(USART1_BRGR,0xfffc4020,__READ_WRITE,__US_BRGR_bits);
__IO_REG32_BIT(USART1_RTOR,0xfffc4024,__READ_WRITE,__US_RTOR_bits);
__IO_REG32_BIT(USART1_TTGR,0xfffc4028,__READ_WRITE,__US_TTGR_bits);
__IO_REG32_BIT(USART1_FIDI,0xfffc4040,__READ_WRITE,__US_FIDI_bits);
__IO_REG32_BIT(USART1_NER, 0xfffc4044,__READ_WRITE,__US_NER_bits);
__IO_REG32_BIT(USART1_IF,  0xfffc404c,__READ_WRITE,__US_IF_bits);

__IO_REG32(USART1_RPR, 0xfffc4100,__READ_WRITE);
__IO_REG32_BIT(USART1_RCR, 0xfffc4104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(USART1_TPR, 0xfffc4108,__READ_WRITE);
__IO_REG32_BIT(USART1_TCR, 0xfffc410c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(USART1_RNPR,0xfffc4110,__READ_WRITE);
__IO_REG32_BIT(USART1_RNCR,0xfffc4114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(USART1_TNPR,0xfffc4118,__READ_WRITE);
__IO_REG32_BIT(USART1_TNCR,0xfffc411c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(USART1_PTCR,0xfffc4120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(USART1_PTSR,0xfffc4124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  USART2
 **
 ***************************************************************************/
__IO_REG32_BIT(USART2_CR,  0xfffc8000,__READ_WRITE,__US_CR_bits);
__IO_REG32_BIT(USART2_MR,  0xfffc8004,__READ_WRITE,__US_MR_bits);
__IO_REG32_BIT(USART2_IER, 0xfffc8008,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART2_IDR, 0xfffc800c,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART2_IMR, 0xfffc8010,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART2_CSR, 0xfffc8014,__READ_WRITE,__US_CSR_bits);
__IO_REG32_BIT(USART2_RHR, 0xfffc8018,__READ_WRITE,__US_RHR_bits);
__IO_REG32_BIT(USART2_THR, 0xfffc801c,__READ_WRITE,__US_THR_bits);
__IO_REG32_BIT(USART2_BRGR,0xfffc8020,__READ_WRITE,__US_BRGR_bits);
__IO_REG32_BIT(USART2_RTOR,0xfffc8024,__READ_WRITE,__US_RTOR_bits);
__IO_REG32_BIT(USART2_TTGR,0xfffc8028,__READ_WRITE,__US_TTGR_bits);
__IO_REG32_BIT(USART2_FIDI,0xfffc8040,__READ_WRITE,__US_FIDI_bits);
__IO_REG32_BIT(USART2_NER, 0xfffc8044,__READ_WRITE,__US_NER_bits);
__IO_REG32_BIT(USART2_IF,  0xfffc804c,__READ_WRITE,__US_IF_bits);

__IO_REG32(USART2_RPR, 0xfffc8100,__READ_WRITE);
__IO_REG32_BIT(USART2_RCR, 0xfffc8104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(USART2_TPR, 0xfffc8108,__READ_WRITE);
__IO_REG32_BIT(USART2_TCR, 0xfffc810c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(USART2_RNPR,0xfffc8110,__READ_WRITE);
__IO_REG32_BIT(USART2_RNCR,0xfffc8114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(USART2_TNPR,0xfffc8118,__READ_WRITE);
__IO_REG32_BIT(USART2_TNCR,0xfffc811c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(USART2_PTCR,0xfffc8120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(USART2_PTSR,0xfffc8124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  USART3
 **
 ***************************************************************************/
__IO_REG32_BIT(USART3_CR,  0xfffcc000,__READ_WRITE,__US_CR_bits);
__IO_REG32_BIT(USART3_MR,  0xfffcc004,__READ_WRITE,__US_MR_bits);
__IO_REG32_BIT(USART3_IER, 0xfffcc008,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART3_IDR, 0xfffcc00c,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART3_IMR, 0xfffcc010,__READ_WRITE,__US_IER_bits);
__IO_REG32_BIT(USART3_CSR, 0xfffcc014,__READ_WRITE,__US_CSR_bits);
__IO_REG32_BIT(USART3_RHR, 0xfffcc018,__READ_WRITE,__US_RHR_bits);
__IO_REG32_BIT(USART3_THR, 0xfffcc01c,__READ_WRITE,__US_THR_bits);
__IO_REG32_BIT(USART3_BRGR,0xfffcc020,__READ_WRITE,__US_BRGR_bits);
__IO_REG32_BIT(USART3_RTOR,0xfffcc024,__READ_WRITE,__US_RTOR_bits);
__IO_REG32_BIT(USART3_TTGR,0xfffcc028,__READ_WRITE,__US_TTGR_bits);
__IO_REG32_BIT(USART3_FIDI,0xfffcc040,__READ_WRITE,__US_FIDI_bits);
__IO_REG32_BIT(USART3_NER, 0xfffcc044,__READ_WRITE,__US_NER_bits);
__IO_REG32_BIT(USART3_IF,  0xfffcc04c,__READ_WRITE,__US_IF_bits);

__IO_REG32(USART3_RPR, 0xfffcc100,__READ_WRITE);
__IO_REG32_BIT(USART3_RCR, 0xfffcc104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(USART3_TPR, 0xfffcc108,__READ_WRITE);
__IO_REG32_BIT(USART3_TCR, 0xfffcc10c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(USART3_RNPR,0xfffcc110,__READ_WRITE);
__IO_REG32_BIT(USART3_RNCR,0xfffcc114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(USART3_TNPR,0xfffcc118,__READ_WRITE);
__IO_REG32_BIT(USART3_TNCR,0xfffcc11c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(USART3_PTCR,0xfffcc120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(USART3_PTSR,0xfffcc124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  SSC0   
 **
 ***************************************************************************/
__IO_REG32_BIT(SSC0_CR,  0xfffd0000,__WRITE     ,__SSC_CR_bits);
__IO_REG32_BIT(SSC0_CMR, 0xfffd0004,__READ_WRITE,__SSC_CMR_bits);
__IO_REG32_BIT(SSC0_RCMR,0xfffd0010,__READ_WRITE,__SSC_RCMR_bits);
__IO_REG32_BIT(SSC0_RFMR,0xfffd0014,__READ_WRITE,__SSC_RFMR_bits);
__IO_REG32_BIT(SSC0_TCMR,0xfffd0018,__READ_WRITE,__SSC_TCMR_bits);
__IO_REG32_BIT(SSC0_TFMR,0xfffd001c,__READ_WRITE,__SSC_TFMR_bits);
__IO_REG32(SSC0_RHR, 0xfffd0020,__READ_WRITE);
__IO_REG32(SSC0_THR, 0xfffd0024,__READ_WRITE);
__IO_REG32_BIT(SSC0_RSHR,0xfffd0030,__READ_WRITE,__SSC_RSHR_bits);
__IO_REG32_BIT(SSC0_TSHR,0xfffd0034,__READ_WRITE,__SSC_TSHR_bits);
__IO_REG32_BIT(SSC0_SR,  0xfffd0040,__READ_WRITE,__SSC_SR_bits);
__IO_REG32_BIT(SSC0_IER, 0xfffd0044,__READ_WRITE,__SSC_IER_bits);
__IO_REG32_BIT(SSC0_IDR, 0xfffd0048,__READ_WRITE,__SSC_IER_bits);
__IO_REG32_BIT(SSC0_IMR, 0xfffd004c,__READ_WRITE,__SSC_IER_bits);

__IO_REG32(SSC0_RPR, 0xfffd0100,__READ_WRITE);
__IO_REG32_BIT(SSC0_RCR, 0xfffd0104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(SSC0_TPR, 0xfffd0108,__READ_WRITE);
__IO_REG32_BIT(SSC0_TCR, 0xfffd010c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(SSC0_RNPR,0xfffd0110,__READ_WRITE);
__IO_REG32_BIT(SSC0_RNCR,0xfffd0114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(SSC0_TNPR,0xfffd0118,__READ_WRITE);
__IO_REG32_BIT(SSC0_TNCR,0xfffd011c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(SSC0_PTCR,0xfffd0120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(SSC0_PTSR,0xfffd0124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  SSC1
 **
 ***************************************************************************/
__IO_REG32_BIT(SSC1_CR,  0xfffd4000,__WRITE     ,__SSC_CR_bits);
__IO_REG32_BIT(SSC1_CMR, 0xfffd4004,__READ_WRITE,__SSC_CMR_bits);
__IO_REG32_BIT(SSC1_RCMR,0xfffd4010,__READ_WRITE,__SSC_RCMR_bits);
__IO_REG32_BIT(SSC1_RFMR,0xfffd4014,__READ_WRITE,__SSC_RFMR_bits);
__IO_REG32_BIT(SSC1_TCMR,0xfffd4018,__READ_WRITE,__SSC_TCMR_bits);
__IO_REG32_BIT(SSC1_TFMR,0xfffd401c,__READ_WRITE,__SSC_TFMR_bits);
__IO_REG32(SSC1_RHR, 0xfffd4020,__READ_WRITE);
__IO_REG32(SSC1_THR, 0xfffd4024,__READ_WRITE);
__IO_REG32_BIT(SSC1_RSHR,0xfffd4030,__READ_WRITE,__SSC_RSHR_bits);
__IO_REG32_BIT(SSC1_TSHR,0xfffd4034,__READ_WRITE,__SSC_TSHR_bits);
__IO_REG32_BIT(SSC1_SR,  0xfffd4040,__READ_WRITE,__SSC_SR_bits);
__IO_REG32_BIT(SSC1_IER, 0xfffd4044,__READ_WRITE,__SSC_IER_bits);
__IO_REG32_BIT(SSC1_IDR, 0xfffd4048,__READ_WRITE,__SSC_IER_bits);
__IO_REG32_BIT(SSC1_IMR, 0xfffd404c,__READ_WRITE,__SSC_IER_bits);

__IO_REG32(SSC1_RPR, 0xfffd4100,__READ_WRITE);
__IO_REG32_BIT(SSC1_RCR, 0xfffd4104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(SSC1_TPR, 0xfffd4108,__READ_WRITE);
__IO_REG32_BIT(SSC1_TCR, 0xfffd410c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(SSC1_RNPR,0xfffd4110,__READ_WRITE);
__IO_REG32_BIT(SSC1_RNCR,0xfffd4114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(SSC1_TNPR,0xfffd4118,__READ_WRITE);
__IO_REG32_BIT(SSC1_TNCR,0xfffd411c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(SSC1_PTCR,0xfffd4120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(SSC1_PTSR,0xfffd4124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  SSC2   
 **
 ***************************************************************************/
__IO_REG32_BIT(SSC2_CR,  0xfffd8000,__WRITE     ,__SSC_CR_bits);
__IO_REG32_BIT(SSC2_CMR, 0xfffd8004,__READ_WRITE,__SSC_CMR_bits);
__IO_REG32_BIT(SSC2_RCMR,0xfffd8010,__READ_WRITE,__SSC_RCMR_bits);
__IO_REG32_BIT(SSC2_RFMR,0xfffd8014,__READ_WRITE,__SSC_RFMR_bits);
__IO_REG32_BIT(SSC2_TCMR,0xfffd8018,__READ_WRITE,__SSC_TCMR_bits);
__IO_REG32_BIT(SSC2_TFMR,0xfffd801c,__READ_WRITE,__SSC_TFMR_bits);
__IO_REG32(SSC2_RHR, 0xfffd8020,__READ_WRITE);
__IO_REG32(SSC2_THR, 0xfffd8024,__READ_WRITE);
__IO_REG32_BIT(SSC2_RSHR,0xfffd8030,__READ_WRITE,__SSC_RSHR_bits);
__IO_REG32_BIT(SSC2_TSHR,0xfffd8034,__READ_WRITE,__SSC_TSHR_bits);
__IO_REG32_BIT(SSC2_SR,  0xfffd8040,__READ_WRITE,__SSC_SR_bits);
__IO_REG32_BIT(SSC2_IER, 0xfffd8044,__READ_WRITE,__SSC_IER_bits);
__IO_REG32_BIT(SSC2_IDR, 0xfffd8048,__READ_WRITE,__SSC_IER_bits);
__IO_REG32_BIT(SSC2_IMR, 0xfffd804c,__READ_WRITE,__SSC_IER_bits);

__IO_REG32(SSC2_RPR, 0xfffd8100,__READ_WRITE);
__IO_REG32_BIT(SSC2_RCR, 0xfffd8104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(SSC2_TPR, 0xfffd8108,__READ_WRITE);
__IO_REG32_BIT(SSC2_TCR, 0xfffd810c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(SSC2_RNPR,0xfffd8110,__READ_WRITE);
__IO_REG32_BIT(SSC2_RNCR,0xfffd8114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(SSC2_TNPR,0xfffd8118,__READ_WRITE);
__IO_REG32_BIT(SSC2_TNCR,0xfffd811c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(SSC2_PTCR,0xfffd8120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(SSC2_PTSR,0xfffd8124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  TC 0,1,2
 **
 ***************************************************************************/

/* (default: capturemode) */

//// TC channel 0
__IO_REG32_BIT(TC012_CCR,0xfffa0000,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(TC012_CMR,0xfffa0004,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(TC012_CMR,0xfffa0004,__READ_WRITE,__tccmrwm_bits); 
 
__IO_REG32_BIT(TC012_CV,0xfffa0010,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(TC012_RA,0xfffa0014,__READ,__tcra_bits);
__IO_REG32_BIT(TC012_RB,0xfffa0018,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(TC012_RA,0xfffa0014,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(TC012_RB,0xfffa0018,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(TC012_RC,0xfffa001c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(TC012_SR,0xfffa0020,__READ,__tcsr_bits);
__IO_REG32_BIT(TC012_IER,0xfffa0024,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC012_IDR,0xfffa0028,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC012_IMR,0xfffa002c,__READ,__tcir_bits);

//// TC channel 1

__IO_REG32_BIT(TC012_CCR1,0xfffa0040,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(TC012_CMR1,0xfffa0044,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(TC012_CMR1,0xfffa0044,__READ_WRITE,__tccmrwm_bits); 

//RESERVED: 0xfffa0048, 0xfffa004c 

__IO_REG32_BIT(TC012_CV1,0xfffa0050,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(TC012_RA1,0xfffa0054,__READ,__tcra_bits);
__IO_REG32_BIT(TC012_RB1,0xfffa0058,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(TC012_RA1,0xfffa0054,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(TC012_RB1,0xfffa0058,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(TC012_RC1,0xfffa005c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(TC012_SR1,0xfffa0060,__READ,__tcsr_bits);
__IO_REG32_BIT(TC012_IER1,0xfffa0064,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC012_IDR1,0xfffa0068,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC012_IMR1,0xfffa006c,__READ,__tcir_bits);

//// TC channel 2

__IO_REG32_BIT(TC012_CCR2,0xfffa0080,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(TC012_CMR2,0xfffa0084,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(TC012_CMR2,0xfffa0084,__READ_WRITE,__tccmrwm_bits); 

__IO_REG32_BIT(TC012_CV2,0xfffa0090,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(TC012_RA2,0xfffa0094,__READ,__tcra_bits);
__IO_REG32_BIT(TC012_RB2,0xfffa0098,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(TC012_RA2,0xfffa0094,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(TC012_RB2,0xfffa0098,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(TC012_RC2,0xfffa009c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(TC012_SR2,0xfffa00a0,__READ,__tcsr_bits);
__IO_REG32_BIT(TC012_IER2,0xfffa00a4,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC012_IDR2,0xfffa00a8,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC012_IMR2,0xfffa00ac,__READ,__tcir_bits);

__IO_REG32_BIT(TC012_BCR,0xfffa00c0,__WRITE,__tcbcr_bits);
__IO_REG32_BIT(TC012_BMR,0xfffa00c4,__READ_WRITE,__tcbmr_bits);


/***************************************************************************
 **
 **  TC 3,4,5
 **
 ***************************************************************************/

/* (default: capturemode) */

//// TC channel 3
__IO_REG32_BIT(TC345_CCR,0xfffa4000,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(TC345_CMR,0xfffa4004,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(TC345_CMR,0xfffa4004,__READ_WRITE,__tccmrwm_bits); 
 
__IO_REG32_BIT(TC345_CV,0xfffa4010,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(TC345_RA,0xfffa4014,__READ,__tcra_bits);
__IO_REG32_BIT(TC345_RB,0xfffa4018,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(TC345_RA,0xfffa4014,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(TC345_RB,0xfffa4018,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(TC345_RC,0xfffa401c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(TC345_SR,0xfffa4020,__READ,__tcsr_bits);
__IO_REG32_BIT(TC345_IER,0xfffa4024,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC345_IDR,0xfffa4028,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC345_IMR,0xfffa402c,__READ,__tcir_bits);

//// TC channel 4

__IO_REG32_BIT(TC345_CCR1,0xfffa4040,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(TC345_CMR1,0xfffa4044,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(TC345_CMR1,0xfffa4044,__READ_WRITE,__tccmrwm_bits); 

__IO_REG32_BIT(TC345_CV1,0xfffa4050,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(TC345_RA1,0xfffa4054,__READ,__tcra_bits);
__IO_REG32_BIT(TC345_RB1,0xfffa4058,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(TC345_RA1,0xfffa4054,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(TC345_RB1,0xfffa4058,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(TC345_RC1,0xfffa405c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(TC345_SR1,0xfffa4060,__READ,__tcsr_bits);
__IO_REG32_BIT(TC345_IER1,0xfffa4064,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC345_IDR1,0xfffa4068,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC345_IMR1,0xfffa406c,__READ,__tcir_bits);

//// TC channel 5

__IO_REG32_BIT(TC345_CCR2,0xfffa4080,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(TC345_CMR2,0xfffa4084,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(TC345_CMR2,0xfffa4084,__READ_WRITE,__tccmrwm_bits); 

__IO_REG32_BIT(TC345_CV2,0xfffa4090,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(TC345_RA2,0xfffa4094,__READ,__tcra_bits);
__IO_REG32_BIT(TC345_RB2,0xfffa4098,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(TC345_RA2,0xfffa4094,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(TC345_RB2,0xfffa4098,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(TC345_RC2,0xfffa409c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(TC345_SR2,0xfffa40a0,__READ,__tcsr_bits);
__IO_REG32_BIT(TC345_IER2,0xfffa40a4,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC345_IDR2,0xfffa40a8,__WRITE,__tcir_bits);
__IO_REG32_BIT(TC345_IMR2,0xfffa40ac,__READ,__tcir_bits);

__IO_REG32_BIT(TC345_BCR,0xfffa40c0,__WRITE,__tcbcr_bits);
__IO_REG32_BIT(TC345_BMR,0xfffa40c4,__READ_WRITE,__tcbmr_bits);


/***************************************************************************
 **
 **  MCI   
 **
 ***************************************************************************/
__IO_REG32_BIT(MCI_CR,  0xfffb4000,__READ_WRITE,__MCI_CR_bits);
__IO_REG32_BIT(MCI_MR,  0xfffb4004,__READ_WRITE,__MCI_MR_bits);
__IO_REG32_BIT(MCI_DTOR,0xfffb4008,__READ_WRITE,__MCI_DTOR_bits);
__IO_REG32_BIT(MCI_SDCR,0xfffb400c,__READ_WRITE,__MCI_SDCR_bits);
__IO_REG32(MCI_ARGR,0xfffb4010,__READ_WRITE);
__IO_REG32_BIT(MCI_CMDR,0xfffb4014,__READ_WRITE,__MCI_CMDR_bits);
__IO_REG32(MCI_RSPR,0xfffb4020,__READ_WRITE);
__IO_REG32(MCI_RDR, 0xfffb4030,__READ_WRITE);
__IO_REG32(MCI_TDR, 0xfffb4034,__READ_WRITE);
__IO_REG32_BIT(MCI_SR,  0xfffb4040,__READ_WRITE,__MCI_SR_bits);
__IO_REG32_BIT(MCI_IER, 0xfffb4044,__READ_WRITE,__MCI_SR_bits);
__IO_REG32_BIT(MCI_IDR, 0xfffb4048,__READ_WRITE,__MCI_SR_bits);
__IO_REG32_BIT(MCI_IMR, 0xfffb404c,__READ_WRITE,__MCI_SR_bits);

__IO_REG32(MCI_RPR, 0xfffb4100,__READ_WRITE);
__IO_REG32_BIT(MCI_RCR, 0xfffb4104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(MCI_TPR, 0xfffb4108,__READ_WRITE);
__IO_REG32_BIT(MCI_TCR, 0xfffb410c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(MCI_RNPR,0xfffb4110,__READ_WRITE);
__IO_REG32_BIT(MCI_RNCR,0xfffb4114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(MCI_TNPR,0xfffb4118,__READ_WRITE);
__IO_REG32_BIT(MCI_TNCR,0xfffb411c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(MCI_PTCR,0xfffb4120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(MCI_PTSR,0xfffb4124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  USB   
 **
 ***************************************************************************/
__IO_REG32_BIT(USB_FRM_NUM, 0xfffb0000,__READ_WRITE,__USB_FRM_NUM_bits);
__IO_REG32_BIT(USB_GLB_STAT,0xfffb0004,__READ_WRITE,__USB_GLB_STAT_bits);
__IO_REG32_BIT(USB_FADDR,   0xfffb0008,__READ_WRITE,__USB_FADDR_bits);
__IO_REG32_BIT(USB_IER,     0xfffb0010,__READ_WRITE,__USB_IER_bits);
__IO_REG32_BIT(USB_IDR,     0xfffb0014,__READ_WRITE,__USB_IER_bits);
__IO_REG32_BIT(USB_IMR,     0xfffb0018,__READ_WRITE,__USB_IER_bits);
__IO_REG32_BIT(USB_ISR,     0xfffb001c,__READ_WRITE,__USB_ISR_bits);
__IO_REG32_BIT(USB_ICR,     0xfffb0020,__READ_WRITE,__USB_ICR_bits);
__IO_REG32_BIT(USB_RST_EP,  0xfffb0028,__READ_WRITE,__USB_RST_EP_bits);
__IO_REG32_BIT(USB_CSR0,    0xfffb0030,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_CSR1,    0xfffb0034,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_CSR2,    0xfffb0038,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_CSR3,    0xfffb003c,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_CSR4,    0xfffb0040,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_CSR5,    0xfffb0044,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_CSR6,    0xfffb0048,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_CSR7,    0xfffb004c,__READ_WRITE,__USB_CSR_bits);
__IO_REG32_BIT(USB_FDR0,    0xfffb0050,__READ_WRITE,__USB_FDR_bits);
__IO_REG32_BIT(USB_FDR1,    0xfffb0054,__READ_WRITE,__USB_FDR_bits);
__IO_REG32_BIT(USB_FDR2,    0xfffb0058,__READ_WRITE,__USB_FDR_bits);
__IO_REG32_BIT(USB_FDR3,    0xfffb005c,__READ_WRITE,__USB_FDR_bits);
__IO_REG32_BIT(USB_FDR4,    0xfffb0060,__READ_WRITE,__USB_FDR_bits);
__IO_REG32_BIT(USB_FDR5,    0xfffb0064,__READ_WRITE,__USB_FDR_bits);
__IO_REG32_BIT(USB_FDR6,    0xfffb0068,__READ_WRITE,__USB_FDR_bits);
__IO_REG32_BIT(USB_FDR7,    0xfffb006c,__READ_WRITE,__USB_FDR_bits);

__IO_REG32(USB_RPR, 0xfffb0100,__READ_WRITE);
__IO_REG32_BIT(USB_RCR, 0xfffb0104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(USB_TPR, 0xfffb0108,__READ_WRITE);
__IO_REG32_BIT(USB_TCR, 0xfffb010c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(USB_RNPR,0xfffb0110,__READ_WRITE);
__IO_REG32_BIT(USB_RNCR,0xfffb0114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(USB_TNPR,0xfffb0118,__READ_WRITE);
__IO_REG32_BIT(USB_TNCR,0xfffb011c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(USB_PTCR,0xfffb0120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(USB_PTSR,0xfffb0124,__READ_WRITE,__PERIPH_PTSR_bits);


/***************************************************************************
 **
 **  EMAC 
 **
 ***************************************************************************/
__IO_REG32_BIT(ETH_CTL, 0xfffbc000,__READ_WRITE,__ETH_CTL_bits);
__IO_REG32_BIT(ETH_CFG, 0xfffbc004,__READ_WRITE,__ETH_CFG_bits);
__IO_REG32_BIT(ETH_SR,  0xfffbc008,__READ_WRITE,__ETH_SR_bits);
__IO_REG32(ETH_TAR, 0xfffbc00c,__READ_WRITE);
__IO_REG32_BIT(ETH_TCR, 0xfffbc010,__READ_WRITE,__ETH_TCR_bits);
__IO_REG32_BIT(ETH_TSR, 0xfffbc014,__READ_WRITE,__ETH_TSR_bits);
__IO_REG32(ETH_RBQP,0xfffbc018,__READ_WRITE);
__IO_REG32_BIT(ETH_RSR, 0xfffbc020,__READ_WRITE,__ETH_RSR_bits);
__IO_REG32_BIT(ETH_ISR, 0xfffbc024,__READ_WRITE,__ETH_ISR_bits);
__IO_REG32_BIT(ETH_IER, 0xfffbc028,__READ_WRITE,__ETH_ISR_bits);
__IO_REG32_BIT(ETH_IDR, 0xfffbc02c,__READ_WRITE,__ETH_ISR_bits);
__IO_REG32_BIT(ETH_IMR, 0xfffbc030,__READ_WRITE,__ETH_ISR_bits);
__IO_REG32_BIT(ETH_MAN, 0xfffbc034,__READ_WRITE,__ETH_MAN_bits);
__IO_REG32(ETH_FRA, 0xfffbc040,__READ_WRITE);
__IO_REG32(ETH_SCOL,0xfffbc044,__READ_WRITE);
__IO_REG32(ETH_MCOL,0xfffbc048,__READ_WRITE);
__IO_REG32(ETH_OK,  0xfffbc04c,__READ_WRITE);
__IO_REG32(ETH_SEQE,0xfffbc050,__READ_WRITE);
__IO_REG32(ETH_ALE, 0xfffbc054,__READ_WRITE);
__IO_REG32(ETH_DTE, 0xfffbc058,__READ_WRITE);
__IO_REG32(ETH_LCOL,0xfffbc05c,__READ_WRITE);
__IO_REG32(ETH_ECOL,0xfffbc060,__READ_WRITE);
__IO_REG32(ETH_CSE, 0xfffbc064,__READ_WRITE);
__IO_REG32(ETH_TUE, 0xfffbc068,__READ_WRITE);
__IO_REG32(ETH_CDE, 0xfffbc06c,__READ_WRITE);
__IO_REG32(ETH_ELR, 0xfffbc070,__READ_WRITE);
__IO_REG32(ETH_RJB, 0xfffbc074,__READ_WRITE);
__IO_REG32(ETH_USF, 0xfffbc078,__READ_WRITE);
__IO_REG32(ETH_SQEE,0xfffbc07c,__READ_WRITE);
__IO_REG32(ETH_DRFC,0xfffbc080,__READ_WRITE);
__IO_REG32(ETH_HSH, 0xfffbc090,__READ_WRITE);
__IO_REG32(ETH_HSL, 0xfffbc094,__READ_WRITE);
__IO_REG32_BIT(ETH_SA1L,0xfffbc098,__READ_WRITE,__ETH_SAL_bits);
__IO_REG32_BIT(ETH_SA1H,0xfffbc09c,__READ_WRITE,__ETH_SAH_bits);
__IO_REG32_BIT(ETH_SA2L,0xfffbc0a0,__READ_WRITE,__ETH_SAL_bits);
__IO_REG32_BIT(ETH_SA2H,0xfffbc0a4,__READ_WRITE,__ETH_SAH_bits);
__IO_REG32_BIT(ETH_SA3L,0xfffbc0a8,__READ_WRITE,__ETH_SAL_bits);
__IO_REG32_BIT(ETH_SA3H,0xfffbc0ac,__READ_WRITE,__ETH_SAH_bits);
__IO_REG32_BIT(ETH_SA4L,0xfffbc0b0,__READ_WRITE,__ETH_SAL_bits);
__IO_REG32_BIT(ETH_SA4H,0xfffbc0b4,__READ_WRITE,__ETH_SAH_bits);

__IO_REG32(ETH_RPR, 0xfffbc100,__READ_WRITE);
__IO_REG32_BIT(ETH_RCR, 0xfffbc104,__READ_WRITE,__PERIPH_RCR_bits);
__IO_REG32(ETH_TPR, 0xfffbc108,__READ_WRITE);
__IO_REG32_BIT(ETH_PDCTCR, 0xfffbc10c,__READ_WRITE,__PERIPH_TCR_bits);
__IO_REG32(ETH_RNPR,0xfffbc110,__READ_WRITE);
__IO_REG32_BIT(ETH_RNCR,0xfffbc114,__READ_WRITE,__PERIPH_RNCR_bits);
__IO_REG32(ETH_TNPR,0xfffbc118,__READ_WRITE);
__IO_REG32_BIT(ETH_TNCR,0xfffbc11c,__READ_WRITE,__PERIPH_TNCR_bits);
__IO_REG32_BIT(ETH_PTCR,0xfffbc120,__READ_WRITE,__PERIPH_PTCR_bits);
__IO_REG32_BIT(ETH_PTSR,0xfffbc124,__READ_WRITE,__PERIPH_PTSR_bits);


/* Assembler specific declarations  ****************************************/


/***************************************************************************
 ** 
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

#endif    /* __AT91RM9200_H */
