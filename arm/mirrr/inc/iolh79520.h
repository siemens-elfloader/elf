/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Sharp Semiconductors LH79520
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.5 $
 **                                
 ***************************************************************************/

#ifndef __LH79520_H
#define __LH79520_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    LH79520 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* SMC Bank Configuration Registers  */
typedef struct {
  __REG32 IDCY                : 4;
  __REG32                     : 1;
  __REG32 WST1                : 5;
  __REG32 RBLE                : 1;
  __REG32 WST2                : 5;
  __REG32                     : 8;
  __REG32 BUSERR              : 1;
  __REG32 WPERR               : 1;
  __REG32 WP                  : 1;
  __REG32 BM                  : 1;
  __REG32 MW                  : 2;
  __REG32                     : 2;
} __SMC_BCR_bits;


/* SDRC Configuration Register 0  */
typedef struct {
  __REG32                     : 1;
  __REG32 F0                  : 1;
  __REG32 T0                  : 1;
  __REG32 B0                  : 1;
  __REG32                     : 1;
  __REG32 F1                  : 1;
  __REG32 T1                  : 1;
  __REG32 B1                  : 1;
  __REG32                     : 9;
  __REG32 E                   : 1;
  __REG32 C                   : 1;
  __REG32 X                   : 1;
  __REG32 C1C0                : 2;
  __REG32 R1R0                : 2;
  __REG32 AP                  : 1;
  __REG32                     : 7;
} __SDRCConfig0_bits;

/* SDRC Configuration Register 1  */
typedef struct {
  __REG32 I                   : 1;
  __REG32 M                   : 1;
  __REG32 R                   : 1;
  __REG32 W                   : 1;
  __REG32                     : 1;
  __REG32 B                   : 1;
  __REG32                     : 26;
} __SDRCConfig1_bits;

/* SDRC Refresh timer Register */
typedef struct {
  __REG32 RTVAL               : 16;
  __REG32                     : 16;
} __SDRCRefTimer_bits;

/* SDRC Write buffer timeout Register */
typedef struct {
  __REG32 TOVAL               : 16;
  __REG32                     : 16;
} __SDRCWBTimeout_bits;


/* RCPC Control Register  */
typedef struct {
  __REG32 EP                  : 1;
  __REG32 EX                  : 1;
  __REG32 PWRDWNSEL           : 3;
  __REG32 OUTSEL              : 2;
  __REG32 CLKSEL              : 1;
  __REG32                     : 1;
  __REG32 WRTLOCK             : 1;
  __REG32                     : 22;
} __RCPC_Ctrl_bits;

/* RCPC Soft reset Register  */
typedef struct {
  __REG32 SRVAL               : 16;
  __REG32                     : 16;
} __RCPC_SoftReset_bits;

/* RCPC Reset status Register  */
typedef struct {
  __REG32 EXT                 : 1;
  __REG32 WDTO                : 1;
  __REG32                     : 30;
} __RCPC_ResetStatus_bits;

/* RCPC Reset status clear Register  */
typedef struct {
  __REG32 EXTCLR              : 1;
  __REG32 TOCLR               : 1;
  __REG32                     : 30;
} __RCPC_ResetStatusClr_bits;

/* RCPC HCLK prescaler Register  */
typedef struct {
  __REG32 HCPSVAL             : 4;
  __REG32                     : 28;
} __RCPC_HCLKPrescale_bits;

/* RCPC Cpu clock prescaler Register  */
typedef struct {
  __REG32 CCPSVAL             : 4;
  __REG32                     : 28;
} __RCPC_CpuClkPrescale_bits;

/* RCPC Peripheral Clock Control Register   */
typedef struct {
  __REG32 U0                  : 1;
  __REG32 U1                  : 1;
  __REG32 U2                  : 1;
  __REG32                     : 1;
  __REG32 T01                 : 1;
  __REG32 T23                 : 1;
  __REG32                     : 1;
  __REG32 PWM0                : 1;
  __REG32 PWM1                : 1;
  __REG32 RTC                 : 1;
  __REG32                     : 22;
} __RCPC_PeriphClkCtrl_bits;

/* RCPC Peripheral Clock Control Register 2  */
typedef struct {
  __REG32 LCDCLK              : 1;
  __REG32 SSPCLK              : 1;
  __REG32                     : 30;
} __RCPC_PeriphClkCtrl2_bits;

/* RCPC AHB Clock Control Register  */
typedef struct {
  __REG32 DMA                 : 1;
  __REG32 SDC                 : 1;
  __REG32                     : 30;
} __RCPC_AhbClkCtrl_bits;

/* RCPC Peripheral clock select Register  */
typedef struct {
  __REG32 U0                  : 1;
  __REG32 U1                  : 1;
  __REG32 U2                  : 1;
  __REG32                     : 4;
  __REG32 RTC                 : 2;
  __REG32                     : 23;
} __RCPC_PeriphClkSel_bits;

/* RCPC Peripheral clock select Register 2 */
typedef struct {
  __REG32 LCSRC               : 1;
  __REG32                     : 31;
} __RCPC_PeriphClkSel2_bits;

/* RCPC PWM prescale Register  */
typedef struct {
  __REG32 PRESCALEVAL         : 15;
  __REG32                     : 17;
} __RCPC_PWMPrescale_bits;

/* RCPC LCD clock prescaler Register  */
typedef struct {
  __REG32 LCDPSVAL            : 8;
  __REG32                     : 24;
} __RCPC_LCDPrescaler_bits;

/* RCPC SSP clock prescaler Register  */
typedef struct {
  __REG32 SSPPSVAL            : 8;
  __REG32                     : 24;
} __RCPC_SSPPrescaler_bits;

/* RCPC External Interrupt Configuration Register  */
typedef struct {
  __REG32 INT0                : 2;
  __REG32 INT1                : 2;
  __REG32 INT2                : 2;
  __REG32 INT3                : 2;
  __REG32 INT4                : 2;
  __REG32 INT5                : 2;
  __REG32 INT6                : 2;
  __REG32                     : 18;
} __RCPC_IntConfig_bits;


/* IOCON Mem Mux Register  */
typedef struct {
  __REG32 PIN112_109          : 2;
  __REG32 PIN106              : 1;
  __REG32 PIN105              : 1;
  __REG32 PIN104              : 1;
  __REG32 PIN102              : 1;
  __REG32 PIN101              : 1;
  __REG32 PIN67_50            : 1;
  __REG32 PIN44               : 1;
  __REG32 PIN43               : 1;
  __REG32 PIN42               : 1;
  __REG32 PIN41               : 1;
  __REG32 PIN35               : 1;
  __REG32 PIN34               : 1;
  __REG32                     : 18;
} __IOCON_MemMux_bits;

/* IOCON LCD Interface Muxing Register  */
typedef struct {
  __REG32 PIN142              : 2;
  __REG32 PIN141              : 1;
  __REG32 PIN140              : 1;
  __REG32 PIN139              : 2;
  __REG32 PIN137              : 2;
  __REG32 PIN135              : 2;
  __REG32 PIN134              : 1;
  __REG32 PIN133              : 1;
  __REG32 PIN132              : 1;
  __REG32 PIN131              : 2;
  __REG32 PIN130              : 1;
  __REG32 PIN129              : 2;
  __REG32 PIN124              : 1;
  __REG32 PIN123              : 1;
  __REG32 PIN122              : 1;
  __REG32 PIN121              : 1;
  __REG32 PIN119              : 2;
  __REG32 PIN118              : 1;
  __REG32 PIN117              : 1;
  __REG32 PIN116              : 1;
  __REG32 PIN115              : 1;
  __REG32 PIN114              : 1;
  __REG32                     : 3;
} __IOCON_LCDMux_bits;

/* IOCON Misc Mux Register  */
typedef struct {
  __REG32 PIN157              : 1;
  __REG32 PIN156              : 1;
  __REG32 PIN155              : 1;
  __REG32 PIN153              : 1;
  __REG32 PIN152              : 1;
  __REG32 PIN151              : 1;
  __REG32 PIN150              : 1;
  __REG32 PIN145              : 1;
  __REG32 PIN144              : 1;
  __REG32 PIN99               : 1;
  __REG32 PIN98               : 1;
  __REG32                     : 21;
} __IOCON_MiscMux_bits;

/* IOCON DMA Mux Register  */
typedef struct {
  __REG32 PIN148              : 1;
  __REG32 PIN147              : 1;
  __REG32 PIN146              : 1;
  __REG32                     : 29;
} __IOCON_DMAMux_bits;

/* IOCON UART Mux Register  */
typedef struct {
  __REG32 PIN163              : 1;
  __REG32 PIN162              : 1;
  __REG32 PIN160              : 1;
  __REG32 PIN159              : 1;
  __REG32                     : 28;
} __IOCON_UARTMux_bits;

/* IOCON SSP Mux Register  */
typedef struct {
  __REG32 PIN169              : 1;
  __REG32 PIN167              : 1;
  __REG32 PIN166              : 1;
  __REG32 PIN165              : 1;
  __REG32 PIN164              : 1;
  __REG32                     : 27;
} __IOCON_SSPMux_bits;


/* VIC Registers */
typedef struct {
  __REG32 S0                  : 1;
  __REG32 S1                  : 1;
  __REG32 S2                  : 1;
  __REG32 S3                  : 1;
  __REG32 S4                  : 1;
  __REG32 S5                  : 1;
  __REG32 S6                  : 1;
  __REG32 S7                  : 1;
  __REG32 S8                  : 1;
  __REG32 S9                  : 1;
  __REG32 S10                 : 1;
  __REG32 S11                 : 1;
  __REG32 S12                 : 1;
  __REG32 S13                 : 1;
  __REG32 S14                 : 1;
  __REG32 S15                 : 1;
  __REG32 S16                 : 1;
  __REG32 S17                 : 1;
  __REG32 S18                 : 1;
  __REG32 S19                 : 1;
  __REG32 S20                 : 1;
  __REG32 S21                 : 1;
  __REG32 S22                 : 1;
  __REG32 S23                 : 1;
  __REG32 S24                 : 1;
  __REG32 S25                 : 1;
  __REG32 S26                 : 1;
  __REG32 S27                 : 1;
  __REG32 S28                 : 1;
  __REG32 S29                 : 1;
  __REG32 S30                 : 1;
  __REG32 S31                 : 1;
} __VIC_S_bits;

/* VIC Registers */
typedef struct {
  __REG32 IE0                  : 1;
  __REG32 IE1                  : 1;
  __REG32 IE2                  : 1;
  __REG32 IE3                  : 1;
  __REG32 IE4                  : 1;
  __REG32 IE5                  : 1;
  __REG32 IE6                  : 1;
  __REG32 IE7                  : 1;
  __REG32 IE8                  : 1;
  __REG32 IE9                  : 1;
  __REG32 IE10                 : 1;
  __REG32 IE11                 : 1;
  __REG32 IE12                 : 1;
  __REG32 IE13                 : 1;
  __REG32 IE14                 : 1;
  __REG32 IE15                 : 1;
  __REG32 IE16                 : 1;
  __REG32 IE17                 : 1;
  __REG32 IE18                 : 1;
  __REG32 IE19                 : 1;
  __REG32 IE20                 : 1;
  __REG32 IE21                 : 1;
  __REG32 IE22                 : 1;
  __REG32 IE23                 : 1;
  __REG32 IE24                 : 1;
  __REG32 IE25                 : 1;
  __REG32 IE26                 : 1;
  __REG32 IE27                 : 1;
  __REG32 IE28                 : 1;
  __REG32 IE29                 : 1;
  __REG32 IE30                 : 1;
  __REG32 IE31                 : 1;
} __VIC_IE_bits;

/* VIC Registers */
typedef struct {
  __REG32 C0                  : 1;
  __REG32 C1                  : 1;
  __REG32 C2                  : 1;
  __REG32 C3                  : 1;
  __REG32 C4                  : 1;
  __REG32 C5                  : 1;
  __REG32 C6                  : 1;
  __REG32 C7                  : 1;
  __REG32 C8                  : 1;
  __REG32 C9                  : 1;
  __REG32 C10                 : 1;
  __REG32 C11                 : 1;
  __REG32 C12                 : 1;
  __REG32 C13                 : 1;
  __REG32 C14                 : 1;
  __REG32 C15                 : 1;
  __REG32 C16                 : 1;
  __REG32 C17                 : 1;
  __REG32 C18                 : 1;
  __REG32 C19                 : 1;
  __REG32 C20                 : 1;
  __REG32 C21                 : 1;
  __REG32 C22                 : 1;
  __REG32 C23                 : 1;
  __REG32 C24                 : 1;
  __REG32 C25                 : 1;
  __REG32 C26                 : 1;
  __REG32 C27                 : 1;
  __REG32 C28                 : 1;
  __REG32 C29                 : 1;
  __REG32 C30                 : 1;
  __REG32 C31                 : 1;
} __VIC_C_bits;

/* VIC Vector Control Registers  */
typedef struct {
  __REG32 IntSource           : 5;
  __REG32 E                   : 1;
  __REG32                     : 26;
} __VIC_VectCtrl_bits;

/* VIC Interrupt test output register 1  */
typedef struct {
  __REG32                     : 6;
  __REG32 VI                  : 1;
  __REG32 VF                  : 1;
  __REG32                     : 24;
} __VIC_ITOP1_bits;


/* DMA A Low Registers */
typedef struct {
  __REG32 A0                  : 1;
  __REG32 A1                  : 1;
  __REG32 A2                  : 1;
  __REG32 A3                  : 1;
  __REG32 A4                  : 1;
  __REG32 A5                  : 1;
  __REG32 A6                  : 1;
  __REG32 A7                  : 1;
  __REG32 A8                  : 1;
  __REG32 A9                  : 1;
  __REG32 A10                 : 1;
  __REG32 A11                 : 1;
  __REG32 A12                 : 1;
  __REG32 A13                 : 1;
  __REG32 A14                 : 1;
  __REG32 A15                 : 1;
  __REG32                     : 16;
} __DMA_ALow_bits;

/* DMA A High Registers */
typedef struct {
  __REG32 A16                 : 1;
  __REG32 A17                 : 1;
  __REG32 A18                 : 1;
  __REG32 A19                 : 1;
  __REG32 A20                 : 1;
  __REG32 A21                 : 1;
  __REG32 A22                 : 1;
  __REG32 A23                 : 1;
  __REG32 A24                 : 1;
  __REG32 A25                 : 1;
  __REG32 A26                 : 1;
  __REG32 A27                 : 1;
  __REG32 A28                 : 1;
  __REG32 A29                 : 1;
  __REG32 A30                 : 1;
  __REG32 A31                 : 1;
  __REG32                     : 16;
} __DMA_AHigh_bits;

/* DMA Max count Register */
typedef struct {
  __REG32 MAXCOUNT              : 16;
  __REG32                     : 16;
} __DMA_Max_bits;

/* DMA control Register  */
typedef struct {
  __REG32 Enable              : 1;
  __REG32 SoInc               : 1;
  __REG32 DeInc               : 1;
  __REG32 SoSize              : 2;
  __REG32 SoBurst             : 2;
  __REG32 DeSize              : 2;
  __REG32 AddrMode            : 1;
  __REG32                     : 1;
  __REG32 Mem2Mem             : 1;
  __REG32                     : 1;
  __REG32 Dir                 : 1;
  __REG32                     : 18;
} __DMA_Ctrl_bits;

/* DMA Terminal count Register */
typedef struct {
  __REG32 TCOUNT              : 16;
  __REG32                     : 16;
} __DMA_TCnt_bits;

/* DMA Interrupt Mask Register  */
typedef struct {
  __REG32 Mask0               : 1;
  __REG32 Mask1               : 1;
  __REG32 Mask2               : 1;
  __REG32 Mask3               : 1;
  __REG32 MaskE0              : 1;
  __REG32 MaskE1              : 1;
  __REG32 MaskE2              : 1;
  __REG32 MaskE3              : 1;
  __REG32                     : 24;
} __DMA_Mask_bits;

/* DMA Interrupt Clear Register  */
typedef struct {
  __REG32 Clear0              : 1;
  __REG32 Clear1              : 1;
  __REG32 Clear2              : 1;
  __REG32 Clear3              : 1;
  __REG32 ClearE0             : 1;
  __REG32 ClearE1             : 1;
  __REG32 ClearE2             : 1;
  __REG32 ClearE3             : 1;
  __REG32                     : 24;
} __DMA_Clr_bits;

/* DMA Status Register  */
typedef struct {
  __REG32 EOT0                : 1;
  __REG32 EOT1                : 1;
  __REG32 EOT2                : 1;
  __REG32 EOT3                : 1;
  __REG32 ERROR0              : 1;
  __REG32 ERROR1              : 1;
  __REG32 ERROR2              : 1;
  __REG32 ERROR3              : 1;
  __REG32 ACTIVE0             : 1;
  __REG32 ACTIVE1             : 1;
  __REG32 ACTIVE2             : 1;
  __REG32 ACTIVE3             : 1;
  __REG32                     : 20;
} __DMA_Status_bits;


/* LCD Timing 0 Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 PPL                 : 6;
  __REG32 HSW                 : 8;
  __REG32 HFP                 : 8;
  __REG32 HBP                 : 8;
} __LCD_Timing0_bits;

/* LCD Timing 1 Register  */
typedef struct {
  __REG32 LPP                 : 10;
  __REG32 VSW                 : 6;
  __REG32 VFP                 : 8;
  __REG32 VBP                 : 8;
} __LCD_Timing1_bits;

/* LCD Timing 2 Register  */
typedef struct {
  __REG32 PCD                 : 5;
  __REG32                     : 1;
  __REG32 ACB                 : 5;
  __REG32 IVS                 : 1;
  __REG32 IHS                 : 1;
  __REG32 IPC                 : 1;
  __REG32 IOE                 : 1;
  __REG32                     : 1;
  __REG32 CPL                 : 10;
  __REG32 BCD                 : 1;
  __REG32                     : 5;
} __LCD_Timing2_bits;

/* LCD Interrupt Enable Register  */
typedef struct {
  __REG32                     : 1;
  __REG32 FUFINTRENB          : 1;
  __REG32 LNBUINTRENB         : 1;
  __REG32 VCOMPINTRENB        : 1;
  __REG32 MBERRINTRENB        : 1;
  __REG32                     : 27;
} __LCD_INTRENABLE_bits;

/* LCD Raw Interrupt Status Register  */
typedef struct {
  __REG32                     : 1;
  __REG32 FUF                 : 1;
  __REG32 LNBU                : 1;
  __REG32 VCOMP               : 1;
  __REG32 MBERROR             : 1;
  __REG32                     : 27;
} __LCD_Status_bits;

/* CLCDC Panel Parameters, LCD Panel Power, and CLCDC Control Register  */
typedef struct {
  __REG32 LcdEn               : 1;
  __REG32 LcdBpp              : 3;
  __REG32 LcdBW               : 1;
  __REG32 LcdTFT              : 1;
  __REG32 LcdMONO8            : 1;
  __REG32 LcdDual             : 1;
  __REG32 BGR                 : 1;
  __REG32 BEBO                : 1;
  __REG32 BEPO                : 1;
  __REG32 LcdPwr              : 1;
  __REG32 LcdVComp            : 2;
  __REG32                     : 2;
  __REG32 WATERMARK           : 1;
  __REG32                     : 15;
} __CLCDC_Ctrl_bits;

/* CLCDC Final Masked Interrupts Register  */
typedef struct {
  __REG32                     : 1;
  __REG32 FUFINTR             : 1;
  __REG32 LNBUINTR            : 1;
  __REG32 VCOMPINTR           : 1;
  __REG32 MBERRORINTR         : 1;
  __REG32                     : 27;
} __CLCDC_Interrupt_bits;

/* CLCDC HRTFTC Setup Register  */
typedef struct {
  __REG32 CR                  : 2;
  __REG32                     : 2;
  __REG32 PPL                 : 9;
  __REG32                     : 19;
} __HRTFTC_Setup_bits;

/* CLCDC HRTFTC Control Register  */
typedef struct {
  __REG32 SPSEN               : 1;
  __REG32 CLSEN               : 1;
  __REG32                     : 1;
  __REG32 DISP                : 1;
  __REG32                     : 28;
} __HRTFTC_CTRL_bits;

/* CLCDC HRTFTC Timing 1 Register  */
typedef struct {
  __REG32 LPDEL               : 4;
  __REG32 REVDEL              : 4;
  __REG32 PSDEL               : 4;
  __REG32                     : 20;
} __HRTFTC_Timing1_bits;

/* CLCDC HRTFTC Timing 2 Register  */
typedef struct {
  __REG32 PSDEL2              : 9;
  __REG32 SPLVALUE            : 7;
  __REG32                     : 16;
} __HRTFTC_Timing2_bits;

/* Timer Load Registers  */
typedef struct {
  __REG32 LOADVAL             : 16;
  __REG32                     : 16;
} __TIMER_LOAD_bits;

/* Timer Value Registers  */
typedef struct {
  __REG32 CURRENTCOUNT        : 16;
  __REG32                     : 16;
} __TIMER_VALUE_bits;

/* Timer Control Registers  */
typedef struct {
  __REG32                     : 2;
  __REG32 PRESCALE            : 2;
  __REG32 CASCADE             : 1;
  __REG32                     : 1;
  __REG32 MODE                : 1;
  __REG32 ENABLE              : 1;
  __REG32                     : 24;
} __TIMER_CONTROL_bits;

/* Timer Clear Register  */
typedef struct {
  __REG32 CLR                 : 16;
  __REG32                     : 16;
} __TIMER_CLEAR_bits;


/* WDT Control Register  */
typedef struct {
  __REG32 EN                  : 1;
  __REG32 RSP                 : 1;
  __REG32                     : 1;
  __REG32 FRZ                 : 1;
  __REG32 TOP                 : 4;
  __REG32                     : 24;
} __WDT_CTL_bits;

/* WDT Counter Reset Register  */
typedef struct {
  __REG32 RST                 : 16;
  __REG32                     : 16;
} __WDT_RST_bits;

/* WDT Status Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 RSP                 : 2;
  __REG32 nWDRES              : 1;
  __REG32 nWDINT              : 1;
  __REG32                     : 24;
} __WDT_STATUS_bits;

/* WDT Current Watchdog Count Registers  */
typedef struct {
  __REG32 COUNT               : 8;
  __REG32                     : 24;
} __WDT_COUNT_bits;


/* RTC Interrupt Status and Interrupt clear Register  */
typedef struct {
  __REG32 RTCINTR             : 1;
  __REG32                     : 31;
} __RTCSTATCEOI_bits;

/* RTC Control Register  */
typedef struct {
  __REG32 MIE                 : 1;
  __REG32                     : 31;
} __RTCCR_bits;


/* PWM Terminal Count Registers  */
typedef struct {
  __REG32 TERMINALCOUNT       : 16;
  __REG32                     : 16;
} __PWM_TCx_bits;

/* PWM Duty Cycle Register  */
typedef struct {
  __REG32 DCCOUNT             : 16;
  __REG32                     : 16;
} __PWM_DCx_bits;

/* PWM Enable Register  */
typedef struct {
  __REG32 EN                  : 1;
  __REG32                     : 31;
} __PWM_ENx_bits;

/* PWM Output Invert Registers  */
typedef struct {
  __REG32 INV                 : 1;
  __REG32                     : 31;
} __PWM_INVx_bits;

/* PWM Synchronous Mode Registers  */
typedef struct {
  __REG32 MODE                : 1;
  __REG32                     : 31;
} __PWM_SYNCx_bits;


/* SSP Control 0 Register  */
typedef struct {
  __REG32 DSS                 : 4;
  __REG32 FRF                 : 2;
  __REG32 SPO                 : 1;
  __REG32 SPH                 : 1;
  __REG32 SCR                 : 8;
  __REG32                     : 16;
} __SSP_CR0_bits;

/* SSP Control 1 Register  */
typedef struct {
  __REG32 RIE                 : 1;
  __REG32 TIE                 : 1;
  __REG32 RORIE               : 1;
  __REG32 LBM                 : 1;
  __REG32 SSE                 : 1;
  __REG32                     : 27;
} __SSP_CR1_bits;

/* SSP Data Register  */
typedef struct {
  __REG32 DATA                : 16;
  __REG32                     : 16;
} __SSP_DR_bits;

/* SSP Status Register  */
typedef struct {
  __REG32 TFE                 : 1;
  __REG32 TNF                 : 1;
  __REG32 RNE                 : 1;
  __REG32 BSY                 : 1;
  __REG32                     : 28;
} __SSP_SR_bits;

/* SSP Clock Prescale Register  */
typedef struct {
  __REG32 CPSDVSR             : 8;
  __REG32                     : 24;
} __SSP_CPSR_bits;

/* SSP Interrupt Identification Register  */
typedef union {
  //SSP_IIR
  struct {
    __REG32 RIS                 : 1;
    __REG32 TIS                 : 1;
    __REG32 RORIS               : 1;
    __REG32                     : 29;
  };
  //SSP_ICR
  struct {
    __REG32 CLEAR               : 16;
    __REG32                     : 16;
  };
} __SSP_IIR_bits;

/* SSP DMA Receive Timeout Register  */
typedef struct {
  __REG32 TOCOUNT             : 16;
  __REG32                     : 16;
} __SSP_RXTO_bits;


/* UART Data Register  */
typedef struct {
  __REG32 DATA                : 8;
  __REG32 FRAMING_ERROR       : 1;
  __REG32 PARITY_ERROR        : 1;
  __REG32 BREAK_ERROR         : 1;
  __REG32 OVERRUN_ERROR       : 1;
  __REG32                     : 20;
} __UART_DR_bits;

/* UART Receive status/clear Register  */
typedef struct {
  __REG32 FRAMING_ERROR       : 1;
  __REG32 PARITY_ERROR        : 1;
  __REG32 BREAK_ERROR         : 1;
  __REG32 OVERRUN_ERROR       : 1;
  __REG32                     : 28;
} __UART_RSRECR_bits;

/* UART Flag Register  */
typedef struct {
  __REG32                     : 3;
  __REG32 UART_BUSY           : 1;
  __REG32 RECEIVE_FIFO_EMPTY  : 1;
  __REG32 TRANSMIT_FIFO_FULL  : 1;
  __REG32 RECEIVE_FIFO_FULL   : 1;
  __REG32 TRANSMIT_FIFO_EMPTY : 1;
  __REG32                     : 24;
} __UART_FR_bits;

/* UART Integer baud rate divisor register  */
typedef struct {
  __REG32 BAUD_RATE_INTEGER   : 16;
  __REG32                     : 16;
} __UART_IBRD_bits;

/* UART Fractional baud rate divisor register  */
typedef struct {
  __REG32 BAUD_RATE_FRACTION  : 5;
  __REG32                     : 27;
} __UART_FBRD_bits;

/* UART Line Control Register  */
typedef struct {
  __REG32 SEND_BREAK          : 1;
  __REG32 PARITY_ENABLE       : 1;
  __REG32 EVEN_PARITY_SELECT  : 1;
  __REG32 TWO_STOP_BITS_SELECT: 1;
  __REG32 ENABLE_FIFOS        : 1;
  __REG32 WORD_LENGTH         : 2;
  __REG32 STICK_PARITY_SELECT : 1;
  __REG32                     : 24;
} __UART_LCTRL_H_bits;

/* UART 0 Control Register  */
typedef struct {
  __REG32 UARTEN              : 1;
  __REG32 SIREN               : 1;
  __REG32 SIRLP               : 1;
  __REG32                     : 4;
  __REG32 LBE                 : 1;
  __REG32 TXE                 : 1;
  __REG32 RXE                 : 1;
  __REG32                     : 22;
} __UART0_CTRL_bits;

/* UART 1 and 2 Control Register  */
typedef struct {
  __REG32 UARTEN              : 1;
  __REG32                     : 1;
  __REG32 SIRLP               : 1;
  __REG32                     : 4;
  __REG32 LBE                 : 1;
  __REG32 TXE                 : 1;
  __REG32 RXE                 : 1;
  __REG32                     : 22;
} __UART_CTRL_bits;

/* UART Interrupt FIFO level select Register  */
typedef struct {
  __REG32 TIFLS               : 3;
  __REG32 RIFLS               : 3;
  __REG32                     : 26;
} __UART_IFLS_bits;

/* UART Interrupt Mask Set/Clear Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 RXIM                : 1;
  __REG32 TXIM                : 1;
  __REG32 RTIM                : 1;
  __REG32 FEIM                : 1;
  __REG32 PEIM                : 1;
  __REG32 BEIM                : 1;
  __REG32 OEIM                : 1;
  __REG32                     : 21;
} __UART_IMSC_bits;

/* UART Raw interrupt status Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 RXIS                : 1;
  __REG32 TXIS                : 1;
  __REG32 RTIS                : 1;
  __REG32 FEIS                : 1;
  __REG32 PEIS                : 1;
  __REG32 BEIS                : 1;
  __REG32 OEIS                : 1;
  __REG32                     : 21;
} __UART_RIS_bits;

/* UART Masked interrupt status Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 RXMIS               : 1;
  __REG32 TXMIS               : 1;
  __REG32 RTMIS               : 1;
  __REG32 FEMIS               : 1;
  __REG32 PEMIS               : 1;
  __REG32 BEMIS               : 1;
  __REG32 OEMIS               : 1;
  __REG32                     : 21;
} __UART_MIS_bits;

/* UART interrupt clear Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 RXIC                : 1;
  __REG32 TXIC                : 1;
  __REG32 RTIC                : 1;
  __REG32 FEIC                : 1;
  __REG32 PEIC                : 1;
  __REG32 BEIC                : 1;
  __REG32 OEIC                : 1;
  __REG32                     : 21;
} __UART_ICR_bits;

/* UART0 IrDA Low power Counter register  */
typedef struct {
  __REG32 ILPDVSR             : 8;
  __REG32                     : 24;
} __UART0_ILPR_bits;

/* UART0 test control register  */
typedef struct {
  __REG32                     : 2;
  __REG32 SIRFDME             : 1;
  __REG32                     : 29;
} __UART0_TCR_bits;


/* GPIO port data register */
typedef struct {
  __REG32 DATA0               : 1;
  __REG32 DATA1               : 1;
  __REG32 DATA2               : 1;
  __REG32 DATA3               : 1;
  __REG32 DATA4               : 1;
  __REG32 DATA5               : 1;
  __REG32 DATA6               : 1;
  __REG32 DATA7               : 1;
  __REG32                     : 24;
} __GPIO_DATA_bits;

/* GPIO port data direction register */
typedef struct {
  __REG32 DDR0               : 1;
  __REG32 DDR1               : 1;
  __REG32 DDR2               : 1;
  __REG32 DDR3               : 1;
  __REG32 DDR4               : 1;
  __REG32 DDR5               : 1;
  __REG32 DDR6               : 1;
  __REG32 DDR7               : 1;
  __REG32                    : 24;
} __GPIO_DDR_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  SMC   
 **
 ***************************************************************************/
__IO_REG32_BIT(SMCBCR0,     0xffff1000,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMCBCR1,     0xffff1004,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMCBCR2,     0xffff1008,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMCBCR3,     0xffff100c,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMCBCR4,     0xffff1010,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMCBCR5,     0xffff1014,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMCBCR6,     0xffff1018,__READ_WRITE,__SMC_BCR_bits);


/***************************************************************************
 **
 **  SDRAM Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(SDRCConfig0,  0xffff2000,__READ_WRITE,__SDRCConfig0_bits);
__IO_REG32_BIT(SDRCConfig1,  0xffff2004,__READ_WRITE,__SDRCConfig1_bits);
__IO_REG32_BIT(SDRCRefTimer, 0xffff2008,__READ_WRITE,__SDRCRefTimer_bits);
__IO_REG32_BIT(SDRCWBTimeout,0xffff200c,__READ_WRITE,__SDRCWBTimeout_bits);


/***************************************************************************
 **
 **  RCPC
 **
 ***************************************************************************/
__IO_REG32_BIT(RCPC_Ctrl,       0xfffe2000,__READ_WRITE,__RCPC_Ctrl_bits);
__IO_REG32(RCPCRemapCtrl,       0xfffe2008,__READ_WRITE);
__IO_REG32_BIT(SoftReset,       0xfffe200c,__READ_WRITE,__RCPC_SoftReset_bits);
__IO_REG32_BIT(ResetStatus,     0xfffe2010,__READ_WRITE,__RCPC_ResetStatus_bits);
__IO_REG32_BIT(ResetStatusClr,  0xfffe2014,__READ_WRITE,__RCPC_ResetStatusClr_bits);
__IO_REG32_BIT(HCLKPrescale,    0xfffe2018,__READ_WRITE,__RCPC_HCLKPrescale_bits);
__IO_REG32_BIT(CpuClkPrescale,  0xfffe201c,__READ_WRITE,__RCPC_CpuClkPrescale_bits);
__IO_REG32_BIT(PeriphClkCtrl,   0xfffe2024,__READ_WRITE,__RCPC_PeriphClkCtrl_bits);
__IO_REG32_BIT(PeriphClkCtrl2,  0xfffe2028,__READ_WRITE,__RCPC_PeriphClkCtrl2_bits);
__IO_REG32_BIT(AHBClkCtrl,      0xfffe202c,__READ_WRITE,__RCPC_AhbClkCtrl_bits);
__IO_REG32_BIT(PeriphClkSel,    0xfffe2030,__READ_WRITE,__RCPC_PeriphClkSel_bits);
__IO_REG32_BIT(PeriphClkSel2,   0xfffe2034,__READ_WRITE,__RCPC_PeriphClkSel2_bits);
__IO_REG32_BIT(PWM0Prescale,    0xfffe2038,__READ_WRITE,__RCPC_PWMPrescale_bits);
__IO_REG32_BIT(PWM1Prescale,    0xfffe203c,__READ_WRITE,__RCPC_PWMPrescale_bits);
__IO_REG32_BIT(LCDClkPrescaler, 0xfffe2040,__READ_WRITE,__RCPC_LCDPrescaler_bits);
__IO_REG32_BIT(SSPClkPrescaler, 0xfffe2044,__READ_WRITE,__RCPC_SSPPrescaler_bits);
__IO_REG32_BIT(IntConfig,       0xfffe2080,__READ_WRITE,__RCPC_IntConfig_bits);
__IO_REG32_BIT(IntClear,        0xfffe2084,__READ_WRITE,__RCPC_IntConfig_bits);
__IO_REG32(CoreClkConfig,       0xfffe2088,__READ_WRITE);


/***************************************************************************
 **
 **  IOCON
 **
 ***************************************************************************/
__IO_REG32_BIT(MemMux,   0xfffe5000,__READ_WRITE,__IOCON_MemMux_bits);
__IO_REG32_BIT(LCDMux,   0xfffe5004,__READ_WRITE,__IOCON_LCDMux_bits);
__IO_REG32_BIT(MiscMux,  0xfffe5008,__READ_WRITE,__IOCON_MiscMux_bits);
__IO_REG32_BIT(DMAMux,   0xfffe500C,__READ_WRITE,__IOCON_DMAMux_bits);
__IO_REG32_BIT(UARTMux,  0xfffe5010,__READ_WRITE,__IOCON_UARTMux_bits);
__IO_REG32_BIT(SSPMux,   0xfffe5014,__READ_WRITE,__IOCON_SSPMux_bits);


/***************************************************************************
 **
 **  VIC
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQStatus,   0xfffff000,__READ_WRITE,__VIC_S_bits);
__IO_REG32_BIT(FIQStatus,   0xfffff004,__READ_WRITE,__VIC_S_bits);
__IO_REG32_BIT(RawInterrupt,0xfffff008,__READ_WRITE,__VIC_S_bits);
__IO_REG32_BIT(IntSelect,   0xfffff00c,__READ_WRITE,__VIC_S_bits);
__IO_REG32_BIT(IntEnable,   0xfffff010,__READ_WRITE,__VIC_IE_bits);
__IO_REG32_BIT(IntEnClear,  0xfffff014,__READ_WRITE,__VIC_C_bits);
__IO_REG32_BIT(SoftInt,     0xfffff018,__READ_WRITE,__VIC_S_bits);
__IO_REG32_BIT(SoftIntClear,0xfffff01c,__READ_WRITE,__VIC_C_bits);
__IO_REG32(VectAddr,    0xfffff030,__READ_WRITE);
__IO_REG32(DefVectAddr, 0xfffff034,__READ_WRITE);
__IO_REG32(VectAddr0,   0xfffff100,__READ_WRITE);
__IO_REG32(VectAddr1,   0xfffff104,__READ_WRITE);
__IO_REG32(VectAddr2,   0xfffff108,__READ_WRITE);
__IO_REG32(VectAddr3,   0xfffff10c,__READ_WRITE);
__IO_REG32(VectAddr4,   0xfffff110,__READ_WRITE);
__IO_REG32(VectAddr5,   0xfffff114,__READ_WRITE);
__IO_REG32(VectAdd6,    0xfffff118,__READ_WRITE);
__IO_REG32(VectAddr7,   0xfffff11c,__READ_WRITE);
__IO_REG32(VectAddr8,   0xfffff120,__READ_WRITE);
__IO_REG32(VectAddr9,   0xfffff124,__READ_WRITE);
__IO_REG32(VectAddr10,  0xfffff128,__READ_WRITE);
__IO_REG32(VectAddr11,  0xfffff12c,__READ_WRITE);
__IO_REG32(VectAddr12,  0xfffff130,__READ_WRITE);
__IO_REG32(VectAddr13,  0xfffff134,__READ_WRITE);
__IO_REG32(VectAddr14,  0xfffff138,__READ_WRITE);
__IO_REG32(VectAddr15,  0xfffff13c,__READ_WRITE);
__IO_REG32_BIT(VectCntl0,   0xfffff200,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl1,   0xfffff204,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl2,   0xfffff208,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl3,   0xfffff20c,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl4,   0xfffff210,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl5,   0xfffff214,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl6,   0xfffff218,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl7,   0xfffff21c,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl8,   0xfffff220,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl9,   0xfffff224,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl10,  0xfffff228,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl11,  0xfffff22c,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl12,  0xfffff230,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl13,  0xfffff234,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl14,  0xfffff238,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VectCntl15,  0xfffff23c,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(ITOP1,       0xfffff30c,__READ_WRITE,__VIC_ITOP1_bits);


/***************************************************************************
 **
 **  DMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DMASourceLo_0,0xfffe1000,__READ_WRITE,__DMA_ALow_bits);
__IO_REG32_BIT(DMASourceHi_0,0xfffe1004,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADestLo_0,  0xfffe1008,__READ_WRITE,__DMA_ALow_bits);
__IO_REG32_BIT(DMADestHi_0,  0xfffe100c,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMAMax_0,     0xfffe1010,__READ_WRITE,__DMA_Max_bits);
__IO_REG32_BIT(DMACtrl_0,    0xfffe1014,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG32_BIT(DMASoCurrHi_0,0xfffe1018,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMASoCurrLo_0,0xfffe101c,__READ,__DMA_ALow_bits);
__IO_REG32_BIT(DMADeCurrHi_0,0xfffe1020,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADeCurrLo_0,0xfffe1024,__READ,__DMA_ALow_bits); 
__IO_REG32_BIT(DMATCnt_0,    0xfffe1028,__READ,__DMA_TCnt_bits);

__IO_REG32_BIT(DMASourceLo_1,0xfffe1040,__READ_WRITE,__DMA_ALow_bits); 
__IO_REG32_BIT(DMASourceHi_1,0xfffe1044,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADestLo_1,  0xfffe1048,__READ_WRITE,__DMA_ALow_bits); 
__IO_REG32_BIT(DMADestHi_1,  0xfffe104c,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMAMax_1,     0xfffe1050,__READ_WRITE,__DMA_Max_bits);
__IO_REG32_BIT(DMACtrl_1,    0xfffe1054,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG32_BIT(DMASoCurrHi_1,0xfffe1058,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMASoCurrLo_1,0xfffe105c,__READ,__DMA_ALow_bits); 
__IO_REG32_BIT(DMADeCurrHi_1,0xfffe1060,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADeCurrLo_1,0xfffe1064,__READ,__DMA_ALow_bits); 
__IO_REG32_BIT(DMATCnt_1,    0xfffe1068,__READ,__DMA_TCnt_bits);

__IO_REG32_BIT(DMASourceLo_2,0xfffe1080,__READ_WRITE,__DMA_ALow_bits); 
__IO_REG32_BIT(DMASourceHi_2,0xfffe1084,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADestLo_2,  0xfffe1088,__READ_WRITE,__DMA_ALow_bits); 
__IO_REG32_BIT(DMADestHi_2,  0xfffe108c,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMAMax_2,     0xfffe1090,__READ_WRITE,__DMA_Max_bits);
__IO_REG32_BIT(DMACtrl_2,    0xfffe1094,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG32_BIT(DMASoCurrHi_2,0xfffe1098,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMASoCurrLo_2,0xfffe109c,__READ,__DMA_ALow_bits); 
__IO_REG32_BIT(DMADeCurrHi_2,0xfffe10a0,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADeCurrLo_2,0xfffe10a4,__READ,__DMA_ALow_bits); 
__IO_REG32_BIT(DMATCnt_2,    0xfffe10a8,__READ,__DMA_TCnt_bits);

__IO_REG32_BIT(DMASourceLo_3,0xfffe10c0,__READ_WRITE,__DMA_ALow_bits); 
__IO_REG32_BIT(DMASourceHi_3,0xfffe10c4,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADestLo_3,  0xfffe10c8,__READ_WRITE,__DMA_ALow_bits); 
__IO_REG32_BIT(DMADestHi_3,  0xfffe10cc,__READ_WRITE,__DMA_AHigh_bits);
__IO_REG32_BIT(DMAMax_3,     0xfffe10d0,__READ_WRITE,__DMA_Max_bits);
__IO_REG32_BIT(DMACtrl_3,    0xfffe10d4,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG32_BIT(DMASoCurrHi_3,0xfffe10d8,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMASoCurrLo_3,0xfffe10dc,__READ,__DMA_ALow_bits); 
__IO_REG32_BIT(DMADeCurrHi_3,0xfffe10e0,__READ,__DMA_AHigh_bits);
__IO_REG32_BIT(DMADeCurrLo_3,0xfffe10e4,__READ,__DMA_ALow_bits); 
__IO_REG32_BIT(DMATCnt_3,    0xfffe10e8,__READ,__DMA_TCnt_bits);

__IO_REG32_BIT(DMAMask,      0xfffe10f0,__READ_WRITE,__DMA_Mask_bits);
__IO_REG32_BIT(DMAClr,       0xfffe10f4,__READ_WRITE,__DMA_Clr_bits);
__IO_REG32_BIT(DMAStatus,    0xfffe10f8,__READ_WRITE,__DMA_Status_bits);


/***************************************************************************
 **
 **  CLCDC
 **
 ***************************************************************************/
__IO_REG32_BIT(LCDTiming0,   0xffff4000,__READ_WRITE,__LCD_Timing0_bits);
__IO_REG32_BIT(LCDTiming1,   0xffff4004,__READ_WRITE,__LCD_Timing1_bits);
__IO_REG32_BIT(LCDTiming2,   0xffff4008,__READ_WRITE,__LCD_Timing2_bits);
__IO_REG32(LCDUPBASE,    0xffff4010,__READ_WRITE);
__IO_REG32(LCDLPBASE,    0xffff4014,__READ_WRITE);
__IO_REG32_BIT(LCDINTRENABLE,0xffff4018,__READ_WRITE,__LCD_INTRENABLE_bits);
__IO_REG32_BIT(LCDCtrl,      0xffff401c,__READ_WRITE,__CLCDC_Ctrl_bits);
__IO_REG32_BIT(LCDStatus,    0xffff4020,__READ_WRITE,__LCD_Status_bits);
__IO_REG32_BIT(LCDInterrupt, 0xffff4024,__READ_WRITE,__CLCDC_Interrupt_bits);
__IO_REG32(LCDUPCURR,    0xffff4028,__READ_WRITE);
__IO_REG32(LCDLPCURR,    0xffff402c,__READ_WRITE);

__IO_REG32_BIT(HRTFTCSetup,  0xfffe4000,__READ_WRITE,__HRTFTC_Setup_bits);
__IO_REG32_BIT(HRTFTCControl,0xfffe4004,__READ_WRITE,__HRTFTC_CTRL_bits);
__IO_REG32_BIT(HRTFTCTiming1,0xfffe4008,__READ_WRITE,__HRTFTC_Timing1_bits);
__IO_REG32_BIT(HRTFTCTiming2,0xfffe400c,__READ_WRITE,__HRTFTC_Timing2_bits);


/***************************************************************************
 **
 **  Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TIMER0_LOAD,   0xfffc4000,__READ_WRITE,__TIMER_LOAD_bits);
__IO_REG32_BIT(TIMER0_VALUE,  0xfffc4004,__READ_WRITE,__TIMER_VALUE_bits);
__IO_REG32_BIT(TIMER0_CONTROL,0xfffc4008,__READ_WRITE,__TIMER_CONTROL_bits);
__IO_REG32_BIT(TIMER0_CLEAR,  0xfffc400c,__READ_WRITE,__TIMER_CLEAR_bits);

__IO_REG32_BIT(TIMER1_LOAD,   0xfffc4020,__READ_WRITE,__TIMER_LOAD_bits);
__IO_REG32_BIT(TIMER1_VALUE,  0xfffc4024,__READ_WRITE,__TIMER_VALUE_bits);
__IO_REG32_BIT(TIMER1_CONTROL,0xfffc4028,__READ_WRITE,__TIMER_CONTROL_bits);
__IO_REG32_BIT(TIMER1_CLEAR,  0xfffc402c,__READ_WRITE,__TIMER_CLEAR_bits);

__IO_REG32_BIT(TIMER2_LOAD,   0xfffc5000,__READ_WRITE,__TIMER_LOAD_bits);
__IO_REG32_BIT(TIMER2_VALUE,  0xfffc5004,__READ_WRITE,__TIMER_VALUE_bits);
__IO_REG32_BIT(TIMER2_CONTROL,0xfffc5008,__READ_WRITE,__TIMER_CONTROL_bits);
__IO_REG32_BIT(TIMER2_CLEAR,  0xfffc500c,__READ_WRITE,__TIMER_CLEAR_bits);

__IO_REG32_BIT(TIMER3_LOAD,   0xfffc5020,__READ_WRITE,__TIMER_LOAD_bits);
__IO_REG32_BIT(TIMER3_VALUE,  0xfffc5024,__READ_WRITE,__TIMER_VALUE_bits);
__IO_REG32_BIT(TIMER3_CONTROL,0xfffc5028,__READ_WRITE,__TIMER_CONTROL_bits);
__IO_REG32_BIT(TIMER3_CLEAR,  0xfffc502c,__READ_WRITE,__TIMER_CLEAR_bits);


/***************************************************************************
 **
 **  Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDCTLR,   0xfffe3000,__READ_WRITE,__WDT_CTL_bits);
__IO_REG32_BIT(WDCNTR,   0xfffe3004,__READ_WRITE,__WDT_RST_bits);
__IO_REG32_BIT(WDTSTR,   0xfffe3008,__READ_WRITE,__WDT_STATUS_bits);
__IO_REG32_BIT(WDCNT0,   0xfffe300c,__READ_WRITE,__WDT_COUNT_bits);
__IO_REG32_BIT(WDCNT1,   0xfffe3010,__READ_WRITE,__WDT_COUNT_bits);
__IO_REG32_BIT(WDCNT2,   0xfffe3014,__READ_WRITE,__WDT_COUNT_bits);
__IO_REG32_BIT(WDCNT3,   0xfffe3018,__READ_WRITE,__WDT_COUNT_bits);


/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32(RTCDR,  0xfffe0000,__READ_WRITE);
__IO_REG32(RTCMR,  0xfffe0004,__READ_WRITE);
__IO_REG32_BIT(RTCSTATCEOI,0xfffe0008,__READ_WRITE,__RTCSTATCEOI_bits);
#define RTCSTAT_bit RTCSTATCEOI_bit
#define RTCSTAT     RTCSTATCEOI
#define RTCEOI_bit  RTCSTATCEOI_bit
#define RTCEOI      RTCSTATCEOI
__IO_REG32(RTCLR,  0xfffe000c,__READ_WRITE);
__IO_REG32_BIT(RTCCR,      0xfffe0010,__READ_WRITE,__RTCCR_bits);


/***************************************************************************
 **
 **  PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(PWM0_TC,  0xfffc3000,__READ_WRITE,__PWM_TCx_bits);
__IO_REG32_BIT(PWM0_DC,  0xfffc3004,__READ_WRITE,__PWM_DCx_bits);
__IO_REG32_BIT(PWM0_EN,  0xfffc3008,__READ_WRITE,__PWM_ENx_bits);
__IO_REG32_BIT(PWM0_INV, 0xfffc300c,__READ_WRITE,__PWM_INVx_bits);
__IO_REG32_BIT(PWM0_SYNC,0xfffc3010,__READ_WRITE,__PWM_SYNCx_bits);
__IO_REG32_BIT(PWM1_TC,  0xfffc3020,__READ_WRITE,__PWM_TCx_bits);
__IO_REG32_BIT(PWM1_DC,  0xfffc3024,__READ_WRITE,__PWM_DCx_bits);
__IO_REG32_BIT(PWM1_EN,  0xfffc3028,__READ_WRITE,__PWM_ENx_bits);
__IO_REG32_BIT(PWM1_INV, 0xfffc302c,__READ_WRITE,__PWM_INVx_bits);


/***************************************************************************
 **
 **  SSP
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP_CR0,   0xfffc6000,__READ_WRITE,__SSP_CR0_bits);
__IO_REG32_BIT(SSP_CR1,   0xfffc6004,__READ_WRITE,__SSP_CR1_bits);
__IO_REG32_BIT(SSP_DR,    0xfffc6008,__READ_WRITE,__SSP_DR_bits);
__IO_REG32_BIT(SSP_SR,    0xfffc600c,__READ_WRITE,__SSP_SR_bits);
__IO_REG32_BIT(SSP_CPSR,  0xfffc6010,__READ_WRITE,__SSP_CPSR_bits);
__IO_REG32_BIT(SSP_IIRICR,0xfffc6014,__READ_WRITE,__SSP_IIR_bits);
#define SSP_IIR_bit SSP_IIRICR_bit
#define SSP_IIR     SSP_IIRICR
#define SSP_ICR_bit SSP_IIRICR_bit
#define SSP_ICR     SSP_IIRICR

__IO_REG32_BIT(SSP_RXTO,  0xfffc6018,__READ_WRITE,__SSP_RXTO_bits);


/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/
__IO_REG32_BIT(UART0_DR,     0xfffc0000,__READ_WRITE,__UART_DR_bits);
__IO_REG32_BIT(UART0_RSRECR, 0xfffc0004,__READ_WRITE,__UART_RSRECR_bits);
__IO_REG32_BIT(UART0_FR,     0xfffc0018,__READ_WRITE,__UART_FR_bits);
__IO_REG32_BIT(UART0_ILPR,   0xfffc0020,__READ_WRITE,__UART0_ILPR_bits);
__IO_REG32_BIT(UART0_IBRD,   0xfffc0024,__READ_WRITE,__UART_IBRD_bits);
__IO_REG32_BIT(UART0_FBRD,   0xfffc0028,__READ_WRITE,__UART_FBRD_bits);
__IO_REG32_BIT(UART0_LCR_H,  0xfffc002c,__READ_WRITE,__UART_LCTRL_H_bits);
__IO_REG32_BIT(UART0_CR,     0xfffc0030,__READ_WRITE,__UART0_CTRL_bits);
__IO_REG32_BIT(UART0_IFLS,   0xfffc0034,__READ_WRITE,__UART_IFLS_bits);
__IO_REG32_BIT(UART0_IMSC,   0xfffc0038,__READ_WRITE,__UART_IMSC_bits);
__IO_REG32_BIT(UART0_RIS,    0xfffc003c,__READ_WRITE,__UART_RIS_bits);
__IO_REG32_BIT(UART0_MIS,    0xfffc0040,__READ_WRITE,__UART_MIS_bits);
__IO_REG32_BIT(UART0_ICR,    0xfffc0044,__READ_WRITE,__UART_ICR_bits);
__IO_REG32_BIT(UART0_TCR,    0xfffc0080,__READ_WRITE,__UART0_TCR_bits);



/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG32_BIT(UART1_DR,     0xfffc1000,__READ_WRITE,__UART_DR_bits);
__IO_REG32_BIT(UART1_RSRECR, 0xfffc1004,__READ_WRITE,__UART_RSRECR_bits);
__IO_REG32_BIT(UART1_FR,     0xfffc1018,__READ_WRITE,__UART_FR_bits);
__IO_REG32_BIT(UART1_IBRD,   0xfffc1024,__READ_WRITE,__UART_IBRD_bits);
__IO_REG32_BIT(UART1_FBRD,   0xfffc1028,__READ_WRITE,__UART_FBRD_bits);
__IO_REG32_BIT(UART1_LCR_H,  0xfffc102c,__READ_WRITE,__UART_LCTRL_H_bits);
__IO_REG32_BIT(UART1_CR,     0xfffc1030,__READ_WRITE,__UART_CTRL_bits);
__IO_REG32_BIT(UART1_IFLS,   0xfffc1034,__READ_WRITE,__UART_IFLS_bits);
__IO_REG32_BIT(UART1_IMSC,   0xfffc1038,__READ_WRITE,__UART_IMSC_bits);
__IO_REG32_BIT(UART1_RIS,    0xfffc103c,__READ_WRITE,__UART_RIS_bits);
__IO_REG32_BIT(UART1_MIS,    0xfffc1040,__READ_WRITE,__UART_MIS_bits);
__IO_REG32_BIT(UART1_ICR,    0xfffc1044,__READ_WRITE,__UART_ICR_bits);


/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG32_BIT(UART2_DR,     0xfffc2000,__READ_WRITE,__UART_DR_bits);
__IO_REG32_BIT(UART2_RSRECR, 0xfffc2004,__READ_WRITE,__UART_RSRECR_bits);
__IO_REG32_BIT(UART2_FR,     0xfffc2018,__READ_WRITE,__UART_FR_bits);
__IO_REG32_BIT(UART2_IBRD,   0xfffc2024,__READ_WRITE,__UART_IBRD_bits);
__IO_REG32_BIT(UART2_FBRD,   0xfffc2028,__READ_WRITE,__UART_FBRD_bits);
__IO_REG32_BIT(UART2_LCR_H,  0xfffc202c,__READ_WRITE,__UART_LCTRL_H_bits);
__IO_REG32_BIT(UART2_CR,     0xfffc2030,__READ_WRITE,__UART_CTRL_bits);
__IO_REG32_BIT(UART2_IFLS,   0xfffc2034,__READ_WRITE,__UART_IFLS_bits);
__IO_REG32_BIT(UART2_IMSC,   0xfffc2038,__READ_WRITE,__UART_IMSC_bits);
__IO_REG32_BIT(UART2_RIS,    0xfffc203c,__READ_WRITE,__UART_RIS_bits);
__IO_REG32_BIT(UART2_MIS,    0xfffc2040,__READ_WRITE,__UART_MIS_bits);
__IO_REG32_BIT(UART2_ICR,    0xfffc2044,__READ_WRITE,__UART_ICR_bits);


/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIOPADR,    0xfffdf000,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPBDR,    0xfffdf004,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPADDR,   0xfffdf008,__READ_WRITE,__GPIO_DDR_bits);
__IO_REG32_BIT(GPIOPBDDR,   0xfffdf00C,__READ_WRITE,__GPIO_DDR_bits);

__IO_REG32_BIT(GPIOPCDR,    0xfffde000,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPDDR,    0xfffde004,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPCDDR,   0xfffde008,__READ_WRITE,__GPIO_DDR_bits);
__IO_REG32_BIT(GPIOPDDDR,   0xfffde00C,__READ_WRITE,__GPIO_DDR_bits);

__IO_REG32_BIT(GPIOPEDR,    0xfffdd000,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPFDR,    0xfffdd004,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPEDDR,   0xfffdd008,__READ_WRITE,__GPIO_DDR_bits);
__IO_REG32_BIT(GPIOPFDDR,   0xfffdd00C,__READ_WRITE,__GPIO_DDR_bits);

__IO_REG32_BIT(GPIOPGDR,    0xfffdc000,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPHDR,    0xfffdc004,__READ_WRITE,__GPIO_DATA_bits);
__IO_REG32_BIT(GPIOPGDDR,   0xfffdc008,__READ_WRITE,__GPIO_DDR_bits);
__IO_REG32_BIT(GPIOPHDDR,   0xfffdc00C,__READ_WRITE,__GPIO_DDR_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 ***************************************************************************/

#endif    /* __LH79520_H */
