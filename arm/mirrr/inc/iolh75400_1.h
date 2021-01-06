/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Sharp Semiconductors LH75400
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2003
 **
 **    $Revision: 1.8 $
 **
 ***************************************************************************/

#ifndef __LH75400_H
#define __LH75400_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    LH75400 SPECIAL FUNCTION REGISTERS
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


/* RCPC Control Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 PWR                 : 3;
  __REG32                     : 4;
  __REG32 LOCK                : 1;
  __REG32                     : 22;
} __RCPC_Ctrl_bits;

/* RCPC Identification Register  */
typedef struct {
  __REG32 PART_NUMBER         : 16;
  __REG32                     : 16;
} __RCPC_Identification_bits;

/* RCPC Remap control Register  */
typedef struct {
  __REG32 REMAP               : 2;
  __REG32                     : 30;
} __RCPC_Remap_bits;

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
  __REG32 EXT_CLR             : 1;
  __REG32 WDTO_CLR            : 1;
  __REG32                     : 30;
} __RCPC_ResetStatusClr_bits;

/* RCPC HCLK prescaler Register  */
typedef struct {
  __REG32 HCLK                : 4;
  __REG32                     : 28;
} __RCPC_SysClkPrescaler_bits;

/* Peripheral Clock Control Register 0  */
typedef struct {
  __REG32 U0                  : 1;
  __REG32 U1                  : 1;
  __REG32 U2                  : 1;
  __REG32                     : 6;
  __REG32 RTC                 : 1;
  __REG32                     : 22;
} __RCPC_APBPeriphClkCtrl0_bits;

/* Peripheral Clock Control Register 1  */
typedef struct {
  __REG32 LCD                 : 1;
  __REG32 SSP                 : 1;
  __REG32                     : 30;
} __RCPC_APBPeriphClkCtrl1_bits;

/* AHB Clock Control Register  */
typedef struct {
  __REG32 DMA                 : 1;
  __REG32                     : 31;
} __RCPC_AhbClkCtrl_bits;

/* RCPC LCD clock prescaler Register  */
typedef struct {
  __REG32 LCDPRESCALER        : 8;
  __REG32                     : 24;
} __RCPC_LCDPrescaler_bits;

/* RCPC SSP clock prescaler Register  */
typedef struct {
  __REG32 SSPPRESCALER        : 8;
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


/* VIC Interrupt bits  */
typedef struct {
  __REG32 WDT                  : 1;
  __REG32 Not_Used1            : 1;
  __REG32 ARM7_DBGCOMMRX       : 1;
  __REG32 ARM7_DBGCOMMTX       : 1;
  __REG32 Timer0_Combined      : 1;
  __REG32 Timer1_Combined      : 1;
  __REG32 Timer2_Combined      : 1;
  __REG32 External_Interrupt_0 : 1;
  __REG32 External_Interrupt_1 : 1;
  __REG32 External_Interrupt_2 : 1;
  __REG32 External_Interrupt_3 : 1;
  __REG32 External_Interrupt_4 : 1;
  __REG32 External_Interrupt_5 : 1;
  __REG32 External_Interrupt_6 : 1;
  __REG32 Not_Used2            : 1;
  __REG32 RTC_ALARM            : 1;
  __REG32 ADC_TSCIRQ           : 1;
  __REG32 ADC_BrownOutINTR     : 1;
  __REG32 ADC_PenIRQ           : 1;
  __REG32 LCD                  : 1;
  __REG32 SSPTXINTR            : 1;
  __REG32 SSPRXINTR            : 1;
  __REG32 SSPRORINTR           : 1;
  __REG32 SSPRXTOINTR          : 1;
  __REG32 SSPINTR              : 1;
  __REG32 UART1_UARTRXINTR     : 1;
  __REG32 UART1_UARTTXINTR     : 1;
  __REG32 UART1_UARTINTR       : 1;
  __REG32 UART0_UARTINTR       : 1;
  __REG32 UART2_Interrupt      : 1;
  __REG32 DMA                  : 1;
  __REG32 CAN                  : 1;
} __VIC_INT_bits;

/* VIC Vector Control Registers  */
typedef struct {
  __REG32 IntSource           : 5;
  __REG32 E                   : 1;
  __REG32                     : 26;
} __VIC_VectCtrl_bits;


/* IOCON EBI Interface Muxing Register  */
typedef struct {
  __REG32 A16                 : 1;
  __REG32 A17                 : 1;
  __REG32 A18                 : 1;
  __REG32 A19                 : 1;
  __REG32 A20                 : 1;
  __REG32 A21                 : 1;
  __REG32 A22                 : 1;
  __REG32 A23                 : 1;
  __REG32 nCE1                : 1;
  __REG32 nCE2                : 1;
  __REG32 nCE3                : 1;
  __REG32 nBLE0               : 1;
  __REG32 nBLE1               : 1;
  __REG32 nWAIT               : 1;
  __REG32 DATA                : 1;
  __REG32                     : 17;
} __IOCON_EBI_MUX_bits;

/* IOCON Pins PD6/INT6 to PD0/INT0 Muxing Register  */
typedef struct {
  __REG32 INT0                : 1;
  __REG32 INT1                : 1;
  __REG32 INT2                : 1;
  __REG32 INT3                : 2;
  __REG32 INT4                : 2;
  __REG32 INT5                : 2;
  __REG32 INT6                : 2;
  __REG32                     : 21;
} __IOCON_PD_MUX_bits;

/* IOCON Pins PE7/SSPRM to PD0/INT0 Muxing Register  */
typedef struct {
  __REG32 UARTRX2             : 1;
  __REG32 UARTTX2             : 1;
  __REG32 CANRX               : 2;
  __REG32 CANTX               : 2;
  __REG32 SSPTX               : 1;
  __REG32 SSPRX               : 1;
  __REG32 SSPCLK              : 1;
  __REG32 SSPFRM              : 1;
  __REG32                     : 22;
} __IOCON_PE_MUX_bits;

/* IOCON Timer Muxing Register  */
typedef struct {
  __REG32 CTCLK               : 1;
  __REG32 CTCAP0A             : 2;
  __REG32 CTCAP0B             : 2;
  __REG32 CTCAP0C             : 1;
  __REG32 CTCAP0D             : 1;
  __REG32 CTCAP0E             : 1;
  __REG32 CTCAP1A             : 2;
  __REG32 CTCAP1B             : 2;
  __REG32 CTCAP2A             : 2;
  __REG32 CTCAP2B             : 2;
  __REG32                     : 16;
} __IOCON_TIMER_MUX_bits;

/* IOCON LCD Mode Muxing Register  */
typedef struct {
  __REG32 MODE                : 3;
  __REG32                     : 29;
} __IOCON_LCD_MUX_bits;

/* IOCON Pins PA7/D15 to PA0/D8 Resistor Muxing Register  */
typedef struct {
  __REG32 PA0                 : 2;
  __REG32 PA1                 : 2;
  __REG32 PA2                 : 2;
  __REG32 PA3                 : 2;
  __REG32 PA4                 : 2;
  __REG32 PA5                 : 2;
  __REG32 PA6                 : 2;
  __REG32 PA7                 : 2;
  __REG32                     : 16;
} __IOCON_PA_RES_MUX_bits;

/* IOCON Pins PB5/nWAIT to PB0/nCS1 Resistor Muxing Register  */
typedef struct {
  __REG32 PB0                 : 2;
  __REG32 PB1                 : 2;
  __REG32 PB2                 : 2;
  __REG32 PB3                 : 2;
  __REG32 PB4                 : 2;
  __REG32 PB5                 : 2;
  __REG32                     : 20;
} __IOCON_PB_RES_MUX_bits;

/* IOCON Pins PC7/A23 to PC0/A16 Resistor Muxing Register  */
typedef struct {
  __REG32 PC0                 : 2;
  __REG32 PC1                 : 2;
  __REG32 PC2                 : 2;
  __REG32 PC3                 : 2;
  __REG32 PC4                 : 2;
  __REG32 PC5                 : 2;
  __REG32 PC6                 : 2;
  __REG32 PC7                 : 2;
  __REG32                     : 16;
} __IOCON_PC_RES_MUX_bits;

/* IOCON Pins PD6/INT6 to PD0/INT0 Resistor Muxing Register  */
typedef struct {
  __REG32 PD0                 : 2;
  __REG32 PD1                 : 2;
  __REG32 PD2                 : 2;
  __REG32 PD3                 : 2;
  __REG32 PD4                 : 2;
  __REG32 PD5                 : 2;
  __REG32 PD6                 : 2;
  __REG32                     : 18;
} __IOCON_PD_RES_MUX_bits;

/* IOCON Pins PE7/SSPRM to PE0/UARTRX2 Resistor Muxing Register  */
typedef struct {
  __REG32 PE0                 : 2;
  __REG32 PE1                 : 2;
  __REG32 PE2                 : 2;
  __REG32 PE3                 : 2;
  __REG32 PE4                 : 2;
  __REG32 PE5                 : 2;
  __REG32 PE6                 : 2;
  __REG32 PE7                 : 2;
  __REG32                     : 16;
} __IOCON_PE_RES_MUX_bits;

/* IOCON Pins AN7/PJ7 to AN0/PJ0 Register */
typedef struct {
  __REG32 PJ0                 : 1;
  __REG32 PJ1                 : 1;
  __REG32 PJ2                 : 1;
  __REG32 PJ3                 : 1;
  __REG32 PJ4                 : 1;
  __REG32 PJ5                 : 1;
  __REG32 PJ6                 : 1;
  __REG32 PJ7                 : 1;
  __REG32                     : 24;
} __IOCON_ADC_MUX_bits;


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
  __REG32 Int0                : 1;
  __REG32 Int1                : 1;
  __REG32 Int2                : 1;
  __REG32 Int3                : 1;
  __REG32 ErrorInt0           : 1;
  __REG32 ErrorInt1           : 1;
  __REG32 ErrorInt2           : 1;
  __REG32 ErrorInt3           : 1;
  __REG32 Active0             : 1;
  __REG32 Active1             : 1;
  __REG32 Active2             : 1;
  __REG32 Active3             : 1;
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
  __REG32 CSEL                : 1;
  __REG32 ACB                 : 5;
  __REG32 IVS                 : 1;
  __REG32 HIS                 : 1;
  __REG32 IPC                 : 1;
  __REG32 IOE                 : 1;
  __REG32                     : 1;
  __REG32 CPL                 : 10;
  __REG32 BCD                 : 1;
  __REG32                     : 5;
} __LCD_Timing2_bits;

/* LCD Upper Panel Frame Buffer Base Address Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 LCDUPBASE           : 30;
} __LCD_UPBASE_bits;

/* LCD Lower Panel Frame Buffer Base Address Register  */
typedef struct {
  __REG32                     : 2;
  __REG32 LCDLPBASE           : 30;
} __LCD_LPBASE_bits;

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

/* LCDC Panel Parameters, LCD Panel Power, and LCDC Control Register  */
typedef struct {
  __REG32 LcdEn               : 1;
  __REG32 LcdBpp              : 3;
  __REG32                     : 2;
  __REG32 LcdMono8            : 1;
  __REG32 LcdDual             : 1;
  __REG32                     : 3;
  __REG32 LcdPwr              : 1;
  __REG32 LcdVComp            : 2;
  __REG32                     : 1;
  __REG32 LDmaFIFOTME         : 1;
  __REG32 WATERMARK           : 1;
  __REG32                     : 15;
} __LCDC_Ctrl_bits;


/* Timer 0 Control Register  */
typedef struct {
  __REG32 CCL                 : 1;
  __REG32 CS                  : 1;
  __REG32 SEL                 : 3;
  __REG32                     : 27;
} __TIMER0_CTRL_bits;

/* Timer 0 Compare/Capture Control Register  */
typedef struct {
  __REG32 CAP0                : 2;
  __REG32 CAP1                : 2;
  __REG32 CAP2                : 2;
  __REG32 CAP3                : 2;
  __REG32 CAP4                : 2;
  __REG32 CMP0                : 2;
  __REG32 CMP1                : 2;
  __REG32 TC                  : 1;
  __REG32 PWM                 : 1;
  __REG32                     : 16;
} __TIMER0_CMP_CAP_CTRL_bits;

/* Timer 0 Interrupt Control Register  */
typedef struct {
  __REG32 OVF_EN              : 1;
  __REG32 CMP0_EN             : 1;
  __REG32 CMP1_EN             : 1;
  __REG32 CAP0_EN             : 1;
  __REG32 CAP1_EN             : 1;
  __REG32 CAP2_EN             : 1;
  __REG32 CAP3_EN             : 1;
  __REG32 CAP4_EN             : 1;
  __REG32                     : 24;
} __TIMER0_INT_CTRL_bits;

/* Timer 0 Status Register  */
typedef struct {
  __REG32 OVF_ST              : 1;
  __REG32 CMP0_ST             : 1;
  __REG32 CMP1_ST             : 1;
  __REG32 CAP0_ST             : 1;
  __REG32 CAP1_ST             : 1;
  __REG32 CAP2_ST             : 1;
  __REG32 CAP3_ST             : 1;
  __REG32 CAP4_ST             : 1;
  __REG32                     : 24;
} __TIMER0_STATUS_bits;

/* Timer Counter Register  */
typedef struct {
  __REG32 TMCNT               : 16;
  __REG32                     : 16;
} __TIMER_CNT_bits;

/* Timer Compare Registers  */
typedef struct {
  __REG32 TMCMP               : 16;
  __REG32                     : 16;
} __TIMER_CMP_bits;

/* Timer Capture Registers  */
typedef struct {
  __REG32 TMCAP               : 16;
  __REG32                     : 16;
} __TIMER_CAP_bits;

/* Timer 1 and 2 Control Registers  */
typedef struct {
  __REG32 CCL                 : 1;
  __REG32 CS                  : 1;
  __REG32 SEL                 : 3;
  __REG32 CAP0                : 2;
  __REG32 CAP1                : 2;
  __REG32 CMP0                : 2;
  __REG32 CMP1                : 2;
  __REG32 TC                  : 1;
  __REG32 PWM                 : 1;
  __REG32                     : 17;
} __TIMER12_CTRL_bits;

/* Timer 1 and 2 Interrupt Control Registers  */
typedef struct {
  __REG32 OVF_EN              : 1;
  __REG32 CMP0_EN             : 1;
  __REG32 CMP1_EN             : 1;
  __REG32 CAP0_EN             : 1;
  __REG32 CAP1_EN             : 1;
  __REG32                     : 27;
} __TIMER12_INT_CTRL_bits;

/* Timer 1and 2 Status Register  */
typedef struct {
  __REG32 OVF_ST              : 1;
  __REG32 CMP0_ST             : 1;
  __REG32 CMP1_ST             : 1;
  __REG32 CAP0_ST             : 1;
  __REG32 CAP1_ST             : 1;
  __REG32                     : 27;
} __TIMER12_STATUS_bits;


/* WDT Control Register  */
typedef struct {
  __REG32 EN                  : 1;
  __REG32 RSP                 : 1;
  __REG32                     : 1;
  __REG32 FRZ                 : 1;
  __REG32 TOP                 : 4;
  __REG32                     : 24;
} __WDT_CTRL_bits;

/* WDT Counter Reset Register  */
typedef struct {
  __REG32 WDCNTR              : 16;
  __REG32                     : 16;
} __WDT_CNTR_bits;

/* WDT Status Register  */
typedef struct {
  __REG32                     : 4;
  __REG32 RSP                 : 2;
  __REG32                     : 1;
  __REG32 nWDINTR             : 1;
  __REG32                     : 24;
} __WDT_STR_bits;

/* WDT Watchdog Count Registers  */
typedef struct {
  __REG32 COUNT               : 8;
  __REG32                     : 24;
} __WDT_CNT_bits;


/* RTC Data registers  */
typedef struct {
  __REG32 RTCDR               : 16;
  __REG32                     : 16;
} __RTC_DR_bits;

/* RTC Match registers  */
typedef struct {
  __REG32 RTCMR               : 16;
  __REG32                     : 16;
} __RTC_MR_bits;

/* RTC Interrupt Status and Interrupt clear Register  */
typedef union {
  //RTC_STAT
  struct {
    __REG32 RTCINTR             : 1;
    __REG32                     : 31;
  };
  //RTC_EOI
  struct {
    __REG32 RTCEOI              : 32;
  };
} __RTC_STATEOI_bits;

/* RTC Load registers  */
typedef struct {
  __REG32 RTCLR               : 16;
  __REG32                     : 16;
} __RTC_LR_bits;

/* RTC Control Register  */
typedef struct {
  __REG32 MIE                 : 1;
  __REG32                     : 31;
} __RTC_CTRL_bits;


/* SSP Control 0 Register  */
typedef struct {
  __REG32 DSS                 : 4;
  __REG32 FRF                 : 2;
  __REG32 SPO                 : 1;
  __REG32 SPH                 : 1;
  __REG32 SCR                 : 8;
  __REG32                     : 16;
} __SSP_CTRL0_bits;

/* SSP Control 1 Register  */
typedef struct {
  __REG32 RIE                 : 1;
  __REG32 TIE                 : 1;
  __REG32 RORIE               : 1;
  __REG32 LBM                 : 1;
  __REG32 SSE                 : 1;
  __REG32                     : 27;
} __SSP_CTRL1_bits;

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
  __REG32 RFF                 : 1;
  __REG32 BSY                 : 1;
  __REG32                     : 27;
} __SSP_SR_bits;

/* SSP Clock Prescale Register  */
typedef struct {
  __REG32                     : 1;
  __REG32 CPSDVSR             : 7;
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
    __REG32 ICR                 : 32;
  };
} __SSP_IIRICR_bits;

/* SSP Receive timeout Register  */
typedef struct {
  __REG32 RXTO                : 16;
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
typedef union {
  //UARTx_ECR
  struct {
    __REG32 ERROR_CLEAR         : 8;
    __REG32                     : 24;
  };
  //UARTx_RSR
  struct {
    __REG32 FRAMING_ERROR       : 1;
    __REG32 PARITY_ERROR        : 1;
    __REG32 BREAK_ERROR         : 1;
    __REG32 OVERRUN_ERROR       : 1;
    __REG32                     : 28;
  };
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
  __REG32 BAUD_RATE_FUNCTION  : 5;
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

/* UART Control Register  */
typedef struct {
  __REG32 UART_ENABLE         : 1;
  __REG32                     : 6;
  __REG32 LC                  : 1;
  __REG32 TRANSMIT_ENABLE     : 1;
  __REG32 RECEIVE_ENABLE      : 1;
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

/* UART DMA control Register  */
typedef struct {
  __REG32 RXDMAEN             : 1;
  __REG32 TXDMAEN             : 1;
  __REG32 DMAONERROR          : 1;
  __REG32                     : 29;
} __UART_DMACTRL_bits;


/* UART2 Registers at offset 0 */
typedef union {
  //UART2_TXD UART2_RXD
  struct { /* Transmit/receive buffered data */
    __REG32 DATA                : 8;
    __REG32                     : 24;
  };
  //UART2_BAL
  struct { /* BAL Register  */
    __REG32 BAL                 : 8;
    __REG32                     : 24;
  };
  //UART2_CLCF
  struct { /* UART2 Clocks configure Register  */
  __REG32                     : 4;
  __REG32 RXCS                : 1;
  __REG32                     : 1;
  __REG32 TXCS                : 1;
  __REG32                     : 25;
  };
} __UART2_OFFSET00_bits;

/* UART2 Registers at offset 4 */
typedef union {
  //UART2_BAH
  struct { /* UART2 BAH Register  (Register bank 0) */
    __REG32 BAH                 : 8;
    __REG32                     : 24;
  };
  //UART2_GER
  struct { /* UART2 GER Register  (Register bank 0) */
    __REG32 RFIE                : 1;
    __REG32 TFIE                : 1;
    __REG32 RxIE                : 1;
    __REG32                     : 1;
    __REG32 TxIE                : 1;
    __REG32 TIE                 : 1;
    __REG32                     : 26;
  };
  //UART2_TXF
  struct {  /* UART2 Transmit character flag Register (Register bank 1) */
    __REG32                     : 5;
    __REG32 D8                  : 1;
    __REG32 SP                  : 1;
    __REG32 uLAN                : 1;
    __REG32                     : 24;
  };
  //UART2_RXF
  struct { /* UART2 Receive character flags Register (Register bank 1) */
    __REG32 RND                 : 1;
    __REG32 RFE                 : 1;
    __REG32 BKF                 : 1;
    __REG32 ACR                 : 1;
    __REG32 RPE                 : 1;
    __REG32 RXN                 : 1;
    __REG32 ROK                 : 1;
    __REG32                     : 25;
  };
  //UART2_FMD
  struct { /* UART2 FIFO mode Register  (Register bank 2) */
    __REG32 TFT                 : 2;
    __REG32                     : 2;
    __REG32 RFT                 : 2;
    __REG32                     : 26;
  };
  //UART2_BACF
  struct { /* BRGA Configuration Register  (Register bank 3) */
    __REG32                     : 2;
    __REG32 BAM                 : 1;
    __REG32                     : 29;
  };
  //UART2_BBH
  struct { /* BBH (Register bank 3) */
    __REG32 DATA                : 8;
    __REG32                     : 24;
  };
} __UART2_OFFSET04_bits;

/* UART2 General Interrupt/Bank Register  */
typedef struct {
  __REG32                     : 1;
  __REG32 BI                  : 3;
  __REG32                     : 1;
  __REG32 BANK                : 2;
  __REG32                     : 25;
} __UART2_GIR_bits;

/* UART2 Registers at offset 0c */
typedef union {
  //UART2_LCR
  struct { /* UART2 Line Control Register  (Register bank 0) */
    __REG32 CL                  : 2;
    __REG32 SBL0                : 1;
    __REG32 PM                  : 3;
    __REG32 SBK                 : 1;
    __REG32 DLAB                : 1;
    __REG32                     : 24;
  };
  //UART2_TMCTRL
  struct { /* UART2 Timer control Register  (Register bank 1) */
    __REG32 STA                 : 1;
    __REG32 STB                 : 1;
    __REG32                     : 2;
    __REG32 TGA                 : 1;
    __REG32 TGB                 : 1;
    __REG32                     : 26;
  };
  //UART2_TMST
  struct { /* UART2 Timer status Register (Register bank 1) */
    __REG32 TAEx                : 1;
    __REG32 TBEx                : 1;
    __REG32                     : 2;
    __REG32 GAS                 : 1;
    __REG32 GBS                 : 1;
    __REG32                     : 26;
  };
  //UART2_TMD
  struct { /* UART2 Transmit machine mode Register  (Register bank 2) */
    __REG32 SBL                 : 2;
    __REG32 SPF                 : 1;
    __REG32                     : 2;
    __REG32 NBCL                : 1;
    __REG32 CED                 : 1;
    __REG32 EED                 : 1;
    __REG32                     : 24;
  };
  //UART2_BBCF
  struct { /* BRGB Configuration Register (Register bank 3) */
    __REG32                     : 2;
    __REG32 BBM                 : 1;
    __REG32                     : 2;
    __REG32 BBCS                : 2;
    __REG32                     : 25;
  };

} __UART2_OFFSET0c_bits;

/* UART2 Registers at offset 10 */
typedef union {
  // UART2_MCTRL
  struct { /* UART2 Loopback control Register (Register bank 0) */
    __REG32                     : 4;
    __REG32 LC                  : 1;
    __REG32                     : 27;
  };
  // UART2_FLR
  struct { /* UART2 FIFO level Register (Register bank 1) */
    __REG32 TFL                 : 3;
    __REG32                     : 1;
    __REG32 RFL                 : 3;
    __REG32                     : 25;
  };
  // UART2_IMD
  struct { /* UART2 Internal mode Register (Register bank 2) */
    __REG32 LEM                 : 1;
    __REG32 uLM                 : 1;
    __REG32 RFD                 : 1;
    __REG32                     : 29;
  };
} __UART2_OFFSET10_bits;

/* UART2 Registers at offset 14 */
typedef union {
  //UART2_LSR
  struct { /* UART2 Line Status Register (Register bank 0) */
    __REG32 RFIRLSR             : 1;
    __REG32 OELSR               : 1;
    __REG32 PELSR               : 1;
    __REG32 FELSR               : 1;
    __REG32 BkDLSR              : 1;
    __REG32 TFST                : 1;
    __REG32 TxST                : 1;
    __REG32                     : 25;
  };
  //UART2_RCM
  struct { /* UART2 Receive command Register (Register bank 1) */
    __REG32                     : 2;
    __REG32 ORF                 : 1;
    __REG32 LFR                 : 1;
    __REG32 FRF                 : 1;
    __REG32 FRM                 : 1;
    __REG32 RXDI                : 1;
    __REG32 RXE                 : 1;
    __REG32                     : 24;
  };
  //UART2_RST
  struct { /* UART2 Receive Machine Status Register (Register bank 1) */
    __REG32 RIFRRST             : 1;
    __REG32 OERST               : 1;
    __REG32 PERST               : 1;
    __REG32 FERST               : 1;
    __REG32 BKDRST              : 1;
    __REG32 BKT                 : 1;
    __REG32 PCRF                : 1;
    __REG32 CRF                 : 1;
    __REG32                     : 24;
  };
  //UART2_ACTRL1
  struct { /* UART2 ACTRL1 (Register bank 3) */
    __REG32 DATA                : 8;
    __REG32                     : 24;
  };
} __UART2_OFFSET14_bits;

/* UART2 Registers at offset 18 */
typedef union {
  //UART2_TCM
  struct { /* UART2 Transmit Command Register (Register bank 1) */
    __REG32 TxDI                : 1;
    __REG32 TxEN                : 1;
    __REG32 FTF                 : 1;
    __REG32 FTM                 : 1;
    __REG32                     : 28;
  };
  //UART2_RIE
  struct { /* UART2 Receive interrupt enable Register (Register bank 2) */
    __REG32                     : 1;
    __REG32 OEE                 : 1;
    __REG32 PEE                 : 1;
    __REG32 FEE                 : 1;
    __REG32 BKDE                : 1;
    __REG32 BKTE                : 1;
    __REG32 PCRE                : 1;
    __REG32 CRE                 : 1;
    __REG32                     : 24;
  };
  //UART2_TMIE
  struct { /* UART2 Timer Interrupt Enable Register  */
    __REG32 TAIE                : 1;
    __REG32 TBIE                : 1;
    __REG32                     : 30;
  };
} __UART2_OFFSET18_bits;

/* UART2 Registers at offset 1c */
typedef union {
  //UART2_ACTRL0
  struct { /* UART2 ACTRL0 (Register bank 0) */
    __REG32 DATA                : 8;
    __REG32                     : 24;
  };
  //UART2_ICM
  struct { /* UART2 Internal Command Register  (Register bank 1) */
    __REG32                     : 2;
    __REG32 STC                 : 1;
    __REG32 INTA                : 1;
    __REG32                     : 28;
  };
  //UART2_GSR
  struct { /* UART2 General status Register (Register bank 1)  */
    __REG32 RFIR                : 1;
    __REG32 TFIR                : 1;
    __REG32 RXIR                : 1;
    __REG32                     : 1;
    __REG32 TXIR                : 1;
    __REG32 TIR                 : 1;
    __REG32                     : 26;
  };
  //UART2_RMD
  struct { /* UART2 Receive machine mode Register (Register bank 2) */
    __REG32                     : 3;
    __REG32 SSM                 : 1;
    __REG32 SWM                 : 1;
    __REG32 DPD                 : 1;
    __REG32 uCM                 : 2;
    __REG32                     : 24;
  };
} __UART2_OFFSET1c_bits;


/* GPIO Data Registers  */
typedef struct {
  __REG32 D0                  : 1;
  __REG32 D1                  : 1;
  __REG32 D2                  : 1;
  __REG32 D3                  : 1;
  __REG32 D4                  : 1;
  __REG32 D5                  : 1;
  __REG32 D6                  : 1;
  __REG32 D7                  : 1;
  __REG32                     : 24;
} __GPIO_8BITDATA_bits;

/* GPIO Data Registers  */
typedef struct {
  __REG32 D0                  : 1;
  __REG32 D1                  : 1;
  __REG32 D2                  : 1;
  __REG32 D3                  : 1;
  __REG32 D4                  : 1;
  __REG32 D5                  : 1;
  __REG32 D6                  : 1;
  __REG32                     : 25;
} __GPIO_7BITDATA_bits;

/* GPIO Data Registers  */
typedef struct {
  __REG32 D0                  : 1;
  __REG32 D1                  : 1;
  __REG32 D2                  : 1;
  __REG32 D3                  : 1;
  __REG32 D4                  : 1;
  __REG32 D5                  : 1;
  __REG32                     : 26;
} __GPIO_6BITDATA_bits;

/* GPIO Data Direction Registers  */
typedef struct {
  __REG32 DDIR0               : 1;
  __REG32 DDIR1               : 1;
  __REG32 DDIR2               : 1;
  __REG32 DDIR3               : 1;
  __REG32 DDIR4               : 1;
  __REG32 DDIR5               : 1;
  __REG32 DDIR6               : 1;
  __REG32 DDIR7               : 1;
  __REG32                     : 24;
} __GPIO_8BITDDIR_bits;

/* GPIO Data Direction Registers  */
typedef struct {
  __REG32 DDIR0               : 1;
  __REG32 DDIR1               : 1;
  __REG32 DDIR2               : 1;
  __REG32 DDIR3               : 1;
  __REG32 DDIR4               : 1;
  __REG32 DDIR5               : 1;
  __REG32 DDIR6               : 1;
  __REG32                     : 25;
} __GPIO_7BITDDIR_bits;

/* GPIO Data Direction Registers  */
typedef struct {
  __REG32 DDIR0               : 1;
  __REG32 DDIR1               : 1;
  __REG32 DDIR2               : 1;
  __REG32 DDIR3               : 1;
  __REG32 DDIR4               : 1;
  __REG32 DDIR5               : 1;
  __REG32                     : 26;
} __GPIO_6BITDDIR_bits;


/* CAN Mode Register  */
typedef struct {
  __REG32 RM                  : 1;
  __REG32 LOM                 : 1;
  __REG32 STM                 : 1;
  __REG32 AFM                 : 1;
  __REG32                     : 1;
  __REG32                     : 27;
} __CAN_MOD_bits;

/* CAN Command Register  */
typedef struct {
  __REG32 TR                  : 1;
  __REG32 AT                  : 1;
  __REG32 RRB                 : 1;
  __REG32 CDO                 : 1;
  __REG32 SRR                 : 1;
  __REG32                     : 27;
} __CAN_CMR_bits;

/* CAN Status Register  */
typedef struct {
  __REG32 RBS                 : 1;
  __REG32 DOS                 : 1;
  __REG32 TBS                 : 1;
  __REG32 TCS                 : 1;
  __REG32 RS                  : 1;
  __REG32 TS                  : 1;
  __REG32 ES                  : 1;
  __REG32 BS                  : 1;
  __REG32                     : 24;
} __CAN_SR_bits;

/* CAN Interrupt Register  */
typedef struct {
  __REG32 RI                  : 1;
  __REG32 TI                  : 1;
  __REG32 EI                  : 1;
  __REG32 DOI                 : 1;
  __REG32 WUI                 : 1;
  __REG32 EPI                 : 1;
  __REG32 ALI                 : 1;
  __REG32 BEI                 : 1;
  __REG32                     : 24;
} __CAN_IR_bits;

/* CAN Interrupt Enable Register  */
typedef struct {
  __REG32 RIE                 : 1;
  __REG32 TIE                 : 1;
  __REG32 EIE                 : 1;
  __REG32 DOIE                : 1;
  __REG32                     : 1;
  __REG32 EPIE                : 1;
  __REG32 ALIE                : 1;
  __REG32 BEIE                : 1;
  __REG32                     : 24;
} __CAN_IER_bits;

/* CAN Bus Timing Register 0  */
typedef struct {
  __REG32 BRP                 : 6;
  __REG32 SJW                 : 2;
  __REG32                     : 24;
} __CAN_BTR0_bits;

/* CAN Bus Timing Register 1  */
typedef struct {
  __REG32 TSEG1               : 4;
  __REG32 TSEG2               : 3;
  __REG32 SAM                 : 1;
  __REG32                     : 24;
} __CAN_BTR1_bits;

/* CAN Arbitration Lost Capture Register  */
typedef struct {
  __REG32 Arbitration_Loss    : 5;
  __REG32                     : 27;
} __CAN_ALC_bits;

/* CAN Error Code Capture Register  */
typedef struct {
  __REG32 Segment_Code        : 5;
  __REG32 Direction           : 1;
  __REG32 Error_Code          : 2;
  __REG32                     : 24;
} __CAN_ECC_bits;

/* CAN Error Warning Limit Register  */
typedef struct {
  __REG32 EWL                 : 8;
  __REG32                     : 24;
} __CAN_EWLR_bits;

/* CAN Receive Error Counter Register  */
typedef struct {
  __REG32 RXERR               : 8;
  __REG32                     : 24;
} __CAN_RXERR_bits;

/* CAN Receive Message Counter Register  */
typedef struct {
  __REG32 RMC                 : 5;
  __REG32                     : 27;
} __CAN_RMC_bits;

/* CAN Receive Buffer Start Address Register  */
typedef struct {
  __REG32 RBSA                : 6;
  __REG32                     : 26;
} __CAN_RBSA_bits;


/* ADC High Word Register  */
typedef struct {
  __REG32 RefP                : 2;
  __REG32 INM                 : 1;
  __REG32 INP                 : 4;
  __REG32 SETTIME             : 9;
  __REG32                     : 16;
} __ADC_HW_bits;

/* ADC Control Bank Low Word Register  */
typedef struct {
  __REG32 RefM                : 2;
  __REG32 BIASCON             : 12;
  __REG32                     : 18;
} __ADC_LW_bits;

/* ADC Results Register  */
typedef struct {
  __REG32 CBTAG               : 4;
  __REG32                     : 2;
  __REG32 BITRES              : 10;
  __REG32                     : 16;
} __ADC_RR_bits;

/* ADC Interrupt Masking/Enabling Register  */
typedef struct {
  __REG32 FOMSK               : 1;
  __REG32 FWMSK               : 1;
  __REG32 EOSMSK              : 1;
  __REG32 PMSK                : 1;
  __REG32 BOMSK               : 1;
  __REG32                     : 1;
  __REG32 INTEN               : 1;
  __REG32                     : 25;
} __ADC_IM_bits;

/* ADC Power Configuration Register  */
typedef struct {
  __REG32 NOC                 : 4;
  __REG32                     : 1;
  __REG32 REFEN               : 1;
  __REG32 PWM                 : 2;
  __REG32 CLKSEL              : 3;
  __REG32                     : 21;
} __ADC_PC_bits;

/* ADC General Configuration Register  */
typedef struct {
  __REG32 SSM                 : 2;
  __REG32 SSB                 : 1;
  __REG32 FIFOWMK             : 4;
  __REG32                     : 25;
} __ADC_GC_bits;

/* ADC General Status Register  */
typedef struct {
  __REG32 CBTAG               : 4;
  __REG32 CBSTATE             : 4;
  __REG32 PENIRQ              : 1;
  __REG32 BROWNOUT            : 1;
  __REG32                     : 22;
} __ADC_GS_bits;

/* ADC Interrupt Status Register  */
typedef struct {
  __REG32 FOVRNINTR_UM        : 1;
  __REG32 FWATERINTR_UM       : 1;
  __REG32 EOSINTR_UM          : 1;
  __REG32 PENSYNC_UM          : 1;
  __REG32 BROWNOUTINTR_UM     : 1;
  __REG32                     : 27;
} __ADC_IS_bits;

/* ADC FIFO Status Register  */
typedef struct {
  __REG32 FGTEWATERMRK        : 1;
  __REG32 FOVRNDET            : 1;
  __REG32 FEMPTY              : 1;
  __REG32 FFF                 : 1;
  __REG32 RSPTR               : 4;
  __REG32 WRPTR               : 4;
  __REG32                     : 20;
} __ADC_FS_bits;

/* ADC Idle High Word Register  */
typedef struct {
  __REG32 REFP_ID             : 2;
  __REG32 INM_ID              : 1;
  __REG32 INP_ID              : 4;
  __REG32 SETTIME_ID          : 9;
  __REG32                     : 16;
} __ADC_IHWCTRL_bits;

/* ADC Idle Low Word Register  */
typedef struct {
  __REG32 REFM_ID             : 2;
  __REG32 BIASCON_ID          : 12;
  __REG32                     : 18;
} __ADC_ILWCTRL_bits;

/* ADC Masked Interrupt Status Register  */
typedef struct {
  __REG32 FOVRNINTR           : 1;
  __REG32 FWATERINTR          : 1;
  __REG32 EOSINTR             : 1;
  __REG32 PENSYNC             : 1;
  __REG32 BROWNOUT            : 1;
  __REG32                     : 27;
} __ADC_MIS_bits;

/* ADC Interrupt Clear Register  */
typedef struct {
  __REG32 EOSINTC             : 1;
  __REG32 PENIC               : 1;
  __REG32 BOIC                : 1;
  __REG32                     : 29;
} __ADC_IC_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  SMC
 **
 ***************************************************************************/
__IO_REG32_BIT(SMC_BCR0,     0xffff1000,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR1,     0xffff1004,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR2,     0xffff1008,__READ_WRITE,__SMC_BCR_bits);
__IO_REG32_BIT(SMC_BCR3,     0xffff100c,__READ_WRITE,__SMC_BCR_bits);


/***************************************************************************
 **
 **  RCPC
 **
 ***************************************************************************/
__IO_REG32_BIT(RCPC_Ctrl,             0xfffe2000,__READ_WRITE,__RCPC_Ctrl_bits);
__IO_REG32_BIT(RCPC_Identification,   0xfffe2004,__READ_WRITE,__RCPC_Identification_bits);
__IO_REG32_BIT(RCPC_Remap,            0xfffe2008,__READ_WRITE,__RCPC_Remap_bits);
__IO_REG32_BIT(RCPC_SoftReset,        0xfffe200c,__READ_WRITE,__RCPC_SoftReset_bits);
__IO_REG32_BIT(RCPC_ResetStatus,      0xfffe2010,__READ_WRITE,__RCPC_ResetStatus_bits);
__IO_REG32_BIT(RCPC_ResetStatusClr,   0xfffe2014,__READ_WRITE,__RCPC_ResetStatusClr_bits);
__IO_REG32_BIT(RCPC_SysClkPrescaler,  0xfffe2018,__READ_WRITE,__RCPC_SysClkPrescaler_bits);
__IO_REG32_BIT(RCPC_APBPeriphClkCtrl0,0xfffe2024,__READ_WRITE,__RCPC_APBPeriphClkCtrl0_bits);
__IO_REG32_BIT(RCPC_APBPeriphClkCtrl1,0xfffe2028,__READ_WRITE,__RCPC_APBPeriphClkCtrl1_bits);
__IO_REG32_BIT(RCPC_AhbClkCtrl,       0xfffe202c,__READ_WRITE,__RCPC_AhbClkCtrl_bits);
__IO_REG32_BIT(RCPC_LCDPrescaler,     0xfffe2040,__READ_WRITE,__RCPC_LCDPrescaler_bits);
__IO_REG32_BIT(RCPC_SSPPrescaler,     0xfffe2044,__READ_WRITE,__RCPC_SSPPrescaler_bits);
__IO_REG32_BIT(RCPC_IntConfig,        0xfffe2080,__READ_WRITE,__RCPC_IntConfig_bits);
__IO_REG32_BIT(RCPC_IntClear,         0xfffe2084,__READ_WRITE,__RCPC_IntConfig_bits);


/***************************************************************************
 **
 **  VIC
 **
 ***************************************************************************/
__IO_REG32_BIT(VIC_IRQStatus,   0xfffff000,__READ_WRITE,__VIC_INT_bits);
__IO_REG32_BIT(VIC_FIQStatus,   0xfffff004,__READ_WRITE,__VIC_INT_bits);
__IO_REG32_BIT(VIC_RawIntr,     0xfffff008,__READ_WRITE,__VIC_INT_bits);
__IO_REG32_BIT(VIC_IntSelect,   0xfffff00c,__READ_WRITE,__VIC_INT_bits);
__IO_REG32_BIT(VIC_IntEnable,   0xfffff010,__READ_WRITE,__VIC_INT_bits);
__IO_REG32_BIT(VIC_IntEnClear,  0xfffff014,__READ_WRITE,__VIC_INT_bits);
__IO_REG32_BIT(VIC_SoftInt,     0xfffff018,__READ_WRITE,__VIC_INT_bits);
__IO_REG32_BIT(VIC_SoftIntClear,0xfffff01c,__READ_WRITE,__VIC_INT_bits);
__IO_REG32(VIC_VectAddr,    0xfffff030,__READ_WRITE);
__IO_REG32(VIC_DefVectAddr, 0xfffff034,__READ_WRITE);
__IO_REG32(VIC_VectAddr0,   0xfffff100,__READ_WRITE);
__IO_REG32(VIC_VectAddr1,   0xfffff104,__READ_WRITE);
__IO_REG32(VIC_VectAddr2,   0xfffff108,__READ_WRITE);
__IO_REG32(VIC_VectAddr3,   0xfffff10c,__READ_WRITE);
__IO_REG32(VIC_VectAddr4,   0xfffff110,__READ_WRITE);
__IO_REG32(VIC_VectAddr5,   0xfffff114,__READ_WRITE);
__IO_REG32(VIC_VectAdd6,    0xfffff118,__READ_WRITE);
__IO_REG32(VIC_VectAddr7,   0xfffff11c,__READ_WRITE);
__IO_REG32(VIC_VectAddr8,   0xfffff120,__READ_WRITE);
__IO_REG32(VIC_VectAddr9,   0xfffff124,__READ_WRITE);
__IO_REG32(VIC_VectAddr10,  0xfffff128,__READ_WRITE);
__IO_REG32(VIC_VectAddr11,  0xfffff12c,__READ_WRITE);
__IO_REG32(VIC_VectAddr12,  0xfffff130,__READ_WRITE);
__IO_REG32(VIC_VectAddr13,  0xfffff134,__READ_WRITE);
__IO_REG32(VIC_VectAddr14,  0xfffff138,__READ_WRITE);
__IO_REG32(VIC_VectAddr15,  0xfffff13c,__READ_WRITE);
__IO_REG32_BIT(VIC_VectCtrl0,   0xfffff200,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl1,   0xfffff204,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl2,   0xfffff208,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl3,   0xfffff20c,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl4,   0xfffff210,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl5,   0xfffff214,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl6,   0xfffff218,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl7,   0xfffff21c,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl8,   0xfffff220,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl9,   0xfffff224,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl10,  0xfffff228,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl11,  0xfffff22c,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl12,  0xfffff230,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl13,  0xfffff234,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl14,  0xfffff238,__READ_WRITE,__VIC_VectCtrl_bits);
__IO_REG32_BIT(VIC_VectCtrl15,  0xfffff23c,__READ_WRITE,__VIC_VectCtrl_bits);


/***************************************************************************
 **
 **  IOCON
 **
 ***************************************************************************/
__IO_REG32_BIT(IOCON_EBI_MUX,   0xfffe5000,__READ_WRITE,__IOCON_EBI_MUX_bits);
__IO_REG32_BIT(IOCON_PD_MUX,    0xfffe5004,__READ_WRITE,__IOCON_PD_MUX_bits);
__IO_REG32_BIT(IOCON_PE_MUX,    0xfffe5008,__READ_WRITE,__IOCON_PE_MUX_bits);
__IO_REG32_BIT(IOCON_TIMER_MUX, 0xfffe500c,__READ_WRITE,__IOCON_TIMER_MUX_bits);
__IO_REG32_BIT(IOCON_LCD_MUX,   0xfffe5010,__READ_WRITE,__IOCON_LCD_MUX_bits);
__IO_REG32_BIT(IOCON_PA_RES_MUX,0xfffe5014,__READ_WRITE,__IOCON_PA_RES_MUX_bits);
__IO_REG32_BIT(IOCON_PB_RES_MUX,0xfffe5018,__READ_WRITE,__IOCON_PB_RES_MUX_bits);
__IO_REG32_BIT(IOCON_PC_RES_MUX,0xfffe501c,__READ_WRITE,__IOCON_PC_RES_MUX_bits);
__IO_REG32_BIT(IOCON_PD_RES_MUX,0xfffe5020,__READ_WRITE,__IOCON_PD_RES_MUX_bits);
__IO_REG32_BIT(IOCON_PE_RES_MUX,0xfffe5024,__READ_WRITE,__IOCON_PE_RES_MUX_bits);
__IO_REG32_BIT(IOCON_ADC_MUX,   0xfffe5028,__READ_WRITE,__IOCON_ADC_MUX_bits);


/***************************************************************************
 **
 **  DMA
 **
 ***************************************************************************/
__IO_REG16(DMA_SourceLo_0,0xfffe1000,__READ_WRITE);
__IO_REG16(DMA_SourceHi_0,0xfffe1004,__READ_WRITE);
__IO_REG16(DMA_DestLo_0,  0xfffe1008,__READ_WRITE);
__IO_REG16(DMA_DestHi_0,  0xfffe100c,__READ_WRITE);
__IO_REG32(DMA_Max_0,     0xfffe1010,__READ_WRITE);
__IO_REG32_BIT(DMA_Ctrl_0,    0xfffe1014,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG16(DMA_SoCurrHi_0,0xfffe1018,__READ);
__IO_REG16(DMA_SoCurrLo_0,0xfffe101c,__READ);
__IO_REG16(DMA_DeCurrHi_0,0xfffe1020,__READ);
__IO_REG16(DMA_DeCurrLo_0,0xfffe1024,__READ);
__IO_REG16(DMA_TCnt_0,    0xfffe1028,__READ);

__IO_REG16(DMA_SourceLo_1,0xfffe1040,__READ_WRITE);
__IO_REG16(DMA_SourceHi_1,0xfffe1044,__READ_WRITE);
__IO_REG16(DMA_DestLo_1,  0xfffe1048,__READ_WRITE);
__IO_REG16(DMA_DestHi_1,  0xfffe104c,__READ_WRITE);
__IO_REG32(DMA_Max_1,     0xfffe1050,__READ_WRITE);
__IO_REG32_BIT(DMA_Ctrl_1,    0xfffe1054,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG16(DMA_SoCurrHi_1,0xfffe1058,__READ);
__IO_REG16(DMA_SoCurrLo_1,0xfffe105c,__READ);
__IO_REG16(DMA_DeCurrHi_1,0xfffe1060,__READ);
__IO_REG16(DMA_DeCurrLo_1,0xfffe1064,__READ);
__IO_REG16(DMA_TCnt_1,    0xfffe1068,__READ);

__IO_REG16(DMA_SourceLo_2,0xfffe1080,__READ_WRITE);
__IO_REG16(DMA_SourceHi_2,0xfffe1084,__READ_WRITE);
__IO_REG16(DMA_DestLo_2,  0xfffe1088,__READ_WRITE);
__IO_REG16(DMA_DestHi_2,  0xfffe108c,__READ_WRITE);
__IO_REG32(DMA_Max_2,     0xfffe1090,__READ_WRITE);
__IO_REG32_BIT(DMA_Ctrl_2,    0xfffe1094,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG16(DMA_SoCurrHi_2,0xfffe1098,__READ);
__IO_REG16(DMA_SoCurrLo_2,0xfffe109c,__READ);
__IO_REG16(DMA_DeCurrHi_2,0xfffe10a0,__READ);
__IO_REG16(DMA_DeCurrLo_2,0xfffe10a4,__READ);
__IO_REG16(DMA_TCnt_2,    0xfffe10a8,__READ);

__IO_REG16(DMA_SourceLo_3,0xfffe10c0,__READ_WRITE);
__IO_REG16(DMA_SourceHi_3,0xfffe10c4,__READ_WRITE);
__IO_REG16(DMA_DestLo_3,  0xfffe10c8,__READ_WRITE);
__IO_REG16(DMA_DestHi_3,  0xfffe10cc,__READ_WRITE);
__IO_REG32(DMA_Max_3,     0xfffe10d0,__READ_WRITE);
__IO_REG32_BIT(DMA_Ctrl_3,    0xfffe10d4,__READ_WRITE,__DMA_Ctrl_bits);
__IO_REG16(DMA_SoCurrHi_3,0xfffe10d8,__READ);
__IO_REG16(DMA_SoCurrLo_3,0xfffe10dc,__READ);
__IO_REG16(DMA_DeCurrHi_3,0xfffe10e0,__READ);
__IO_REG16(DMA_DeCurrLo_3,0xfffe10e4,__READ);
__IO_REG16(DMA_TCnt_3,    0xfffe10e8,__READ);

__IO_REG32_BIT(DMA_Mask,      0xfffe10f0,__READ_WRITE,__DMA_Mask_bits);
__IO_REG32_BIT(DMA_Clr,       0xfffe10f4,__READ_WRITE,__DMA_Clr_bits);
__IO_REG32_BIT(DMA_Status,    0xfffe10f8,__READ_WRITE,__DMA_Status_bits);


/***************************************************************************
 **
 **  LCDC
 **
 ***************************************************************************/
__IO_REG32_BIT(LCDC_Timing0,   0xffff4000,__READ_WRITE,__LCD_Timing0_bits);
__IO_REG32_BIT(LCDC_Timing1,   0xffff4004,__READ_WRITE,__LCD_Timing1_bits);
__IO_REG32_BIT(LCDC_Timing2,   0xffff4008,__READ_WRITE,__LCD_Timing2_bits);
__IO_REG32_BIT(LCDC_UPBASE,    0xffff4010,__READ_WRITE,__LCD_UPBASE_bits);
__IO_REG32_BIT(LCDC_LPBASE,    0xffff4014,__READ_WRITE,__LCD_LPBASE_bits);
__IO_REG32_BIT(LCDC_INTRENABLE,0xffff4018,__READ_WRITE,__LCD_INTRENABLE_bits);
__IO_REG32_BIT(LCDC_Ctrl,      0xffff401c,__READ_WRITE,__LCDC_Ctrl_bits);
__IO_REG32_BIT(LCDC_Status,    0xffff4020,__READ_WRITE,__LCD_Status_bits);
__IO_REG32_BIT(LCDC_Interrupt, 0xffff4024,__READ_WRITE,__LCD_INTRENABLE_bits);
__IO_REG32(LCDC_UPCURR,    0xffff4028,__READ_WRITE);
__IO_REG32(LCDC_LPCURR,    0xffff402c,__READ_WRITE);


/***************************************************************************
 **
 **  Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TIMER0_CTRL,        0xfffc4000,__READ_WRITE,__TIMER0_CTRL_bits);
__IO_REG32_BIT(TIMER0_CMP_CAP_CTRL,0xfffc4004,__READ_WRITE,__TIMER0_CMP_CAP_CTRL_bits);
__IO_REG32_BIT(TIMER0_INT_CTRL,    0xfffc4008,__READ_WRITE,__TIMER0_INT_CTRL_bits);
__IO_REG32_BIT(TIMER0_STATUS,      0xfffc400c,__READ_WRITE,__TIMER0_STATUS_bits);
__IO_REG32_BIT(TIMER0_CNT,         0xfffc4010,__READ_WRITE,__TIMER_CNT_bits);
__IO_REG32_BIT(TIMER0_CMP0,        0xfffc4014,__READ_WRITE,__TIMER_CMP_bits);
__IO_REG32_BIT(TIMER0_CMP1,        0xfffc4018,__READ_WRITE,__TIMER_CMP_bits);
__IO_REG32_BIT(TIMER0_CAP0,        0xfffc401c,__READ_WRITE,__TIMER_CAP_bits);
__IO_REG32_BIT(TIMER0_CAP1,        0xfffc4020,__READ_WRITE,__TIMER_CAP_bits);
__IO_REG32_BIT(TIMER0_CAP2,        0xfffc4024,__READ_WRITE,__TIMER_CAP_bits);
__IO_REG32_BIT(TIMER0_CAP3,        0xfffc4028,__READ_WRITE,__TIMER_CAP_bits);
__IO_REG32_BIT(TIMER0_CAP4,        0xfffc402c,__READ_WRITE,__TIMER_CAP_bits);

__IO_REG32_BIT(TIMER1_CTRL,    0xfffc4030,__READ_WRITE,__TIMER12_CTRL_bits);
__IO_REG32_BIT(TIMER1_INT_CTRL,0xfffc4034,__READ_WRITE,__TIMER12_INT_CTRL_bits);
__IO_REG32_BIT(TIMER1_STATUS,  0xfffc4038,__READ_WRITE,__TIMER12_STATUS_bits);
__IO_REG32_BIT(TIMER1_CNT,     0xfffc403c,__READ_WRITE,__TIMER_CNT_bits);
__IO_REG32_BIT(TIMER1_CMP0,    0xfffc4040,__READ_WRITE,__TIMER_CMP_bits);
__IO_REG32_BIT(TIMER1_CMP1,    0xfffc4044,__READ_WRITE,__TIMER_CMP_bits);
__IO_REG32_BIT(TIMER1_CAP0,    0xfffc4048,__READ_WRITE,__TIMER_CAP_bits);
__IO_REG32_BIT(TIMER1_CAP1,    0xfffc404c,__READ_WRITE,__TIMER_CAP_bits);

__IO_REG32_BIT(TIMER2_CTRL,    0xfffc4050,__READ_WRITE,__TIMER12_CTRL_bits);
__IO_REG32_BIT(TIMER2_INT_CTRL,0xfffc4054,__READ_WRITE,__TIMER12_INT_CTRL_bits);
__IO_REG32_BIT(TIMER2_STATUS,  0xfffc4058,__READ_WRITE,__TIMER12_STATUS_bits);
__IO_REG32_BIT(TIMER2_CNT,     0xfffc405c,__READ_WRITE,__TIMER_CNT_bits);
__IO_REG32_BIT(TIMER2_CMP0,    0xfffc4060,__READ_WRITE,__TIMER_CMP_bits);
__IO_REG32_BIT(TIMER2_CMP1,    0xfffc4064,__READ_WRITE,__TIMER_CMP_bits);
__IO_REG32_BIT(TIMER2_CAP0,    0xfffc4068,__READ_WRITE,__TIMER_CAP_bits);
__IO_REG32_BIT(TIMER2_CAP1,    0xfffc406c,__READ_WRITE,__TIMER_CAP_bits);


/***************************************************************************
 **
 **  Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDT_CTRL,0xfffe3000,__READ_WRITE,__WDT_CTRL_bits);
__IO_REG32_BIT(WDT_CNTR,0xfffe3004,__READ_WRITE,__WDT_CNTR_bits);
__IO_REG32_BIT(WDT_TSTR,0xfffe3008,__READ_WRITE,__WDT_STR_bits);
__IO_REG32_BIT(WDT_CNT0,0xfffe300c,__READ_WRITE,__WDT_CNT_bits);
__IO_REG32_BIT(WDT_CNT1,0xfffe3010,__READ_WRITE,__WDT_CNT_bits);
__IO_REG32_BIT(WDT_CNT2,0xfffe3014,__READ_WRITE,__WDT_CNT_bits);
__IO_REG32_BIT(WDT_CNT3,0xfffe3018,__READ_WRITE,__WDT_CNT_bits);


/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(RTC_DR0,    0xfffe0000,__READ_WRITE,__RTC_DR_bits);
__IO_REG32_BIT(RTC_DR1,    0xfffe0004,__READ_WRITE,__RTC_DR_bits);
__IO_REG32_BIT(RTC_MR0,    0xfffe0008,__READ_WRITE,__RTC_MR_bits);
__IO_REG32_BIT(RTC_MR1,    0xfffe000c,__READ_WRITE,__RTC_MR_bits);
__IO_REG32_BIT(RTC_STATEOI,0xfffe0010,__READ_WRITE,__RTC_STATEOI_bits);
#define RTC_STAT_bit RTC_STATEOI_bit
#define RTC_STAT     RTC_STATEOI
#define RTC_EOI_bit  RTC_STATEOI_bit
#define RTC_EOI      RTC_STATEOI

__IO_REG32_BIT(RTC_LR0,    0xfffe0014,__READ_WRITE,__RTC_LR_bits);
__IO_REG32_BIT(RTC_LR1,    0xfffe0018,__READ_WRITE,__RTC_LR_bits);
__IO_REG32_BIT(RTC_CTRL,   0xfffe001c,__READ_WRITE,__RTC_CTRL_bits);


/***************************************************************************
 **
 **  SSP
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP_CTRL0, 0xfffc6000,__READ_WRITE,__SSP_CTRL0_bits);
__IO_REG32_BIT(SSP_CTRL1, 0xfffc6004,__READ_WRITE,__SSP_CTRL1_bits);
__IO_REG32_BIT(SSP_DR,    0xfffc6008,__READ_WRITE,__SSP_DR_bits);
__IO_REG32_BIT(SSP_SR,    0xfffc600c,__READ_WRITE,__SSP_SR_bits);
__IO_REG32_BIT(SSP_CPSR,  0xfffc6010,__READ_WRITE,__SSP_CPSR_bits);
__IO_REG32_BIT(SSP_IIRICR,0xfffc6014,__READ_WRITE,__SSP_IIRICR_bits);
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
#define UART0_RSR_bit UART0_RSRECR_bit
#define UART0_RSR     UART0_RSRECR
#define UART0_ECR_bit UART0_RSRECR_bit
#define UART0_ECR     UART0_RSRECR

__IO_REG32_BIT(UART0_FR,     0xfffc0018,__READ_WRITE,__UART_FR_bits);
__IO_REG32_BIT(UART0_IBRD,   0xfffc0024,__READ_WRITE,__UART_IBRD_bits);
__IO_REG32_BIT(UART0_FBRD,   0xfffc0028,__READ_WRITE,__UART_FBRD_bits);
__IO_REG32_BIT(UART0_LCTRL_H,0xfffc002c,__READ_WRITE,__UART_LCTRL_H_bits);
__IO_REG32_BIT(UART0_CTRL,   0xfffc0030,__READ_WRITE,__UART_CTRL_bits);
__IO_REG32_BIT(UART0_IFLS,   0xfffc0034,__READ_WRITE,__UART_IFLS_bits);
__IO_REG32_BIT(UART0_IMSC,   0xfffc0038,__READ_WRITE,__UART_IMSC_bits);
__IO_REG32_BIT(UART0_RIS,    0xfffc003c,__READ_WRITE,__UART_RIS_bits);
__IO_REG32_BIT(UART0_MIS,    0xfffc0040,__READ_WRITE,__UART_MIS_bits);
__IO_REG32_BIT(UART0_ICR,    0xfffc0044,__READ_WRITE,__UART_ICR_bits);
__IO_REG32_BIT(UART0_DMACTRL,0xfffc0048,__READ_WRITE,__UART_DMACTRL_bits);


/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG32_BIT(UART1_DR,     0xfffc1000,__READ_WRITE,__UART_DR_bits);
__IO_REG32_BIT(UART1_RSRECR, 0xfffc1004,__READ_WRITE,__UART_RSRECR_bits);
#define UART1_RSR_bit UART1_RSRECR_bit
#define UART1_RSR     UART1_RSRECR
#define UART1_ECR_bit UART1_RSRECR_bit
#define UART1_ECR     UART1_RSRECR

__IO_REG32_BIT(UART1_FR,     0xfffc1018,__READ_WRITE,__UART_FR_bits);
__IO_REG32_BIT(UART1_IBRD,   0xfffc1024,__READ_WRITE,__UART_IBRD_bits);
__IO_REG32_BIT(UART1_FBRD,   0xfffc1028,__READ_WRITE,__UART_FBRD_bits);
__IO_REG32_BIT(UART1_LCTRL_H,0xfffc102c,__READ_WRITE,__UART_LCTRL_H_bits);
__IO_REG32_BIT(UART1_CTRL,   0xfffc1030,__READ_WRITE,__UART_CTRL_bits);
__IO_REG32_BIT(UART1_IFLS,   0xfffc1034,__READ_WRITE,__UART_IFLS_bits);
__IO_REG32_BIT(UART1_IMSC,   0xfffc1038,__READ_WRITE,__UART_IMSC_bits);
__IO_REG32_BIT(UART1_RIS,    0xfffc103c,__READ_WRITE,__UART_RIS_bits);
__IO_REG32_BIT(UART1_MIS,    0xfffc1040,__READ_WRITE,__UART_MIS_bits);
__IO_REG32_BIT(UART1_ICR,    0xfffc1044,__READ_WRITE,__UART_ICR_bits);
__IO_REG32_BIT(UART1_DMACTRL,0xfffc1048,__READ_WRITE,__UART_DMACTRL_bits);


/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG32_BIT(UART2_GIR,      0xfffc2008,__READ_WRITE,__UART2_GIR_bits);

// Register bank 0
__IO_REG32_BIT(UART2_TXDRXDBAL,0xfffc2000,__READ_WRITE,__UART2_OFFSET00_bits);
#define UART2_TXD_bit  UART2_TXDRXDBAL_bit
#define UART2_TXD      UART2_TXDRXDBAL
#define UART2_RXD_bit  UART2_TXDRXDBAL_bit
#define UART2_RXD      UART2_TXDRXDBAL
#define UART2_BAL_bit  UART2_TXDRXDBAL_bit
#define UART2_BAL      UART2_TXDRXDBAL

__IO_REG32_BIT(UART2_BAHGER,   0xfffc2004,__READ_WRITE,__UART2_OFFSET04_bits);
#define UART2_BAH_bit  UART2_BAHGER_bit
#define UART2_BAH      UART2_BAHGER
#define UART2_GER_bit  UART2_BAHGER_bit
#define UART2_GER      UART2_BAHGER

__IO_REG32_BIT(UART2_LCR,      0xfffc200c,__READ_WRITE,__UART2_OFFSET0c_bits);
__IO_REG32_BIT(UART2_MCTRL,    0xfffc2010,__READ_WRITE,__UART2_OFFSET10_bits);
__IO_REG32_BIT(UART2_LSR,      0xfffc2014,__READ_WRITE,__UART2_OFFSET14_bits);
__IO_REG32_BIT(UART2_ACTRL0,   0xfffc201c,__READ_WRITE,__UART2_OFFSET1c_bits);

//Register bank 1
//#define UART2_TXD_bit  UART2_TXDRXDBAL_bit
//#define UART2_TXD      UART2_TXDRXDBAL
//#define UART2_RXD_bit  UART2_TXDRXDBAL_bit
//#define UART2_RXD      UART2_TXDRXDBAL
#define UART2_TXF_bit    UART2_BAHGER_bit
#define UART2_TXF        UART2_BAHGER
#define UART2_RXF_bit    UART2_BAHGER_bit
#define UART2_RXF        UART2_BAHGER
#define UART2_TMCTRL_bit UART2_LCR_bit
#define UART2_TMCTRL     UART2_LCR
#define UART2_TMST_bit   UART2_LCR_bit
#define UART2_TMST       UART2_LCR
#define UART2_FLR_bit    UART2_MCTRL_bit
#define UART2_FLR        UART2_MCTRL
#define UART2_RCM_bit    UART2_LSR_bit
#define UART2_RCM        UART2_LSR
#define UART2_RST_bit    UART2_LSR_bit
#define UART2_RST        UART2_LSR
__IO_REG32_BIT(UART2_TCM,     0xfffc2018,__READ_WRITE,__UART2_OFFSET18_bits);
#define UART2_ICM_bit    UART2_ACTRL0_bit
#define UART2_ICM        UART2_ACTRL0
#define UART2_GSR_bit    UART2_ACTRL0_bit
#define UART2_GSR        UART2_ACTRL0

//Register bank 2
#define UART2_FMD_bit    UART2_BAHGER_bit
#define UART2_FMD        UART2_BAHGER
#define UART2_TMD        UART2_LCR
#define UART2_TMD_bit    UART2_LCR_bit
#define UART2_IMD_bit    UART2_MCTRL_bit
#define UART2_IMD        UART2_MCTRL
#define UART2_ACTRL1_bit UART2_LSR_bit
#define UART2_ACTRL1     UART2_LSR
#define UART2_RIE_bit    UART2_TCM_bit
#define UART2_RIE        UART2_TCM
#define UART2_RMD_bit    UART2_ACTRL0_bit
#define UART2_RMD        UART2_ACTRL0

//Register bank 3
#define UART2_CLCF_bit UART2_TXDRXDBAL_bit
#define UART2_CLCF     UART2_TXDRXDBAL
#define UART2_BBL      UART2_TXDRXDBAL
#define UART2_BACF_bit UART2_BAHGER_bit
#define UART2_BACF     UART2_BAHGER
#define UART2_BBH_bit  UART2_BAHGER_bit
#define UART2_BBH      UART2_BAHGER
#define UART2_BBCF_bit UART2_LCR_bit
#define UART2_BBCF     UART2_LCR
#define UART2_TMIE_bit UART2_TCM_bit
#define UART2_TMIE     UART2_TCM


/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIO_PIDR, 0xfffdb000,__READ_WRITE,__GPIO_8BITDATA_bits);
__IO_REG32_BIT(GPIO_PJDR, 0xfffdb004,__READ_WRITE,__GPIO_8BITDATA_bits);
__IO_REG32_BIT(GPIO_PIDDR,0xfffdb008,__READ_WRITE,__GPIO_8BITDDIR_bits);

__IO_REG32_BIT(GPIO_PGDR, 0xfffdc000,__READ_WRITE,__GPIO_8BITDATA_bits);
__IO_REG32_BIT(GPIO_PHDR, 0xfffdc004,__READ_WRITE,__GPIO_8BITDATA_bits);
__IO_REG32_BIT(GPIO_PGDDR,0xfffdc008,__READ_WRITE,__GPIO_8BITDDIR_bits);
__IO_REG32_BIT(GPIO_PHDDR,0xfffdc00c,__READ_WRITE,__GPIO_8BITDDIR_bits);

__IO_REG32_BIT(GPIO_PEDR, 0xfffdd000,__READ_WRITE,__GPIO_8BITDATA_bits);
__IO_REG32_BIT(GPIO_PFDR, 0xfffdd004,__READ_WRITE,__GPIO_7BITDATA_bits);
__IO_REG32_BIT(GPIO_PEDDR,0xfffdd008,__READ_WRITE,__GPIO_8BITDDIR_bits);
__IO_REG32_BIT(GPIO_PFDDR,0xfffdd00c,__READ_WRITE,__GPIO_7BITDDIR_bits);

__IO_REG32_BIT(GPIO_PCDR, 0xfffde000,__READ_WRITE,__GPIO_8BITDATA_bits);
__IO_REG32_BIT(GPIO_PDDR, 0xfffde004,__READ_WRITE,__GPIO_7BITDATA_bits);
__IO_REG32_BIT(GPIO_PCDDR,0xfffde008,__READ_WRITE,__GPIO_8BITDDIR_bits);
__IO_REG32_BIT(GPIO_PDDDR,0xfffde00c,__READ_WRITE,__GPIO_7BITDDIR_bits);

__IO_REG32_BIT(GPIO_PADR, 0xfffdf000,__READ_WRITE,__GPIO_8BITDATA_bits);
__IO_REG32_BIT(GPIO_PBDR, 0xfffdf004,__READ_WRITE,__GPIO_6BITDATA_bits);
__IO_REG32_BIT(GPIO_PADDR,0xfffdf008,__READ_WRITE,__GPIO_8BITDDIR_bits);
__IO_REG32_BIT(GPIO_PBDDR,0xfffdf00c,__READ_WRITE,__GPIO_6BITDDIR_bits);


/***************************************************************************
 **
 **  CAN
 **
 ***************************************************************************/
__IO_REG32_BIT(CAN_MOD,  0xfffc5000,__READ_WRITE,__CAN_MOD_bits);
__IO_REG32_BIT(CAN_CMR,  0xfffc5004,__READ_WRITE,__CAN_CMR_bits);
__IO_REG32_BIT(CAN_SR,   0xfffc5008,__READ_WRITE,__CAN_SR_bits);
__IO_REG32_BIT(CAN_IR,   0xfffc500c,__READ_WRITE,__CAN_IR_bits);
__IO_REG32_BIT(CAN_IER,  0xfffc5010,__READ_WRITE,__CAN_IER_bits);
__IO_REG32_BIT(CAN_BTR0, 0xfffc5018,__READ_WRITE,__CAN_BTR0_bits);
__IO_REG32_BIT(CAN_BTR1, 0xfffc501c,__READ_WRITE,__CAN_BTR1_bits);
__IO_REG32_BIT(CAN_ALC,  0xfffc502c,__READ_WRITE,__CAN_ALC_bits);
__IO_REG32_BIT(CAN_ECC,  0xfffc5030,__READ_WRITE,__CAN_ECC_bits);
__IO_REG32_BIT(CAN_EWLR, 0xfffc5034,__READ_WRITE,__CAN_EWLR_bits);
__IO_REG32_BIT(CAN_RXERR,0xfffc5038,__READ_WRITE,__CAN_RXERR_bits);
__IO_REG32(CAN_TXERR,0xfffc503c,__READ_WRITE);
__IO_REG8(CAN_ACR0, 0xfffc5040,__READ_WRITE);
__IO_REG8(CAN_ACR1, 0xfffc5044,__READ_WRITE);
__IO_REG8(CAN_ACR2, 0xfffc5048,__READ_WRITE);
__IO_REG8(CAN_ACR3, 0xfffc504c,__READ_WRITE);
__IO_REG8(CAN_AMR0, 0xfffc5050,__READ_WRITE);
__IO_REG8(CAN_AMR1, 0xfffc5054,__READ_WRITE);
__IO_REG8(CAN_AMR2, 0xfffc5058,__READ_WRITE);
__IO_REG8(CAN_AMR3, 0xfffc505c,__READ_WRITE);
__IO_REG32_BIT(CAN_RMC,  0xfffc5074,__READ_WRITE,__CAN_RMC_bits);
__IO_REG32_BIT(CAN_RBSA, 0xfffc5078,__READ_WRITE,__CAN_RBSA_bits);


/***************************************************************************
 **
 **  ADC
 **
 ***************************************************************************/
__IO_REG32_BIT(ADC_HW,     0xfffc3000,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_LW,     0xfffc3004,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_RR,     0xfffc3008,__READ_WRITE,__ADC_RR_bits);
__IO_REG32_BIT(ADC_IM,     0xfffc300c,__READ_WRITE,__ADC_IM_bits);
__IO_REG32_BIT(ADC_PC,     0xfffc3010,__READ_WRITE,__ADC_PC_bits);
__IO_REG32_BIT(ADC_GC,     0xfffc3014,__READ_WRITE,__ADC_GC_bits);
__IO_REG32_BIT(ADC_GS,     0xfffc3018,__READ_WRITE,__ADC_GS_bits);
__IO_REG32_BIT(ADC_IS,     0xfffc301c,__READ_WRITE,__ADC_IS_bits);
__IO_REG32_BIT(ADC_FS,     0xfffc3020,__READ_WRITE,__ADC_FS_bits);

__IO_REG32_BIT(ADC_HWCB0,  0xfffc3024,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB1,  0xfffc3028,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB2,  0xfffc302c,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB3,  0xfffc3030,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB4,  0xfffc3034,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB5,  0xfffc3038,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB6,  0xfffc303c,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB7,  0xfffc3040,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB8,  0xfffc3044,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB9,  0xfffc3048,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB10, 0xfffc304c,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB11, 0xfffc3050,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB12, 0xfffc3054,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB13, 0xfffc3058,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB14, 0xfffc305c,__READ_WRITE,__ADC_HW_bits);
__IO_REG32_BIT(ADC_HWCB15, 0xfffc3060,__READ_WRITE,__ADC_HW_bits);

__IO_REG32_BIT(ADC_LWCB0,  0xfffc3064,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB1,  0xfffc3068,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB2,  0xfffc306c,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB3,  0xfffc3070,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB4,  0xfffc3074,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB5,  0xfffc3078,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB6,  0xfffc307c,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB7,  0xfffc3080,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB8,  0xfffc3084,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB9,  0xfffc3088,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB10, 0xfffc308c,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB11, 0xfffc3090,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB12, 0xfffc3094,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB13, 0xfffc3098,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB14, 0xfffc309c,__READ_WRITE,__ADC_LW_bits);
__IO_REG32_BIT(ADC_LWCB15, 0xfffc30a0,__READ_WRITE,__ADC_LW_bits);

__IO_REG32_BIT(ADC_IHWCTRL,0xfffc30a4,__READ_WRITE,__ADC_IHWCTRL_bits);
__IO_REG32_BIT(ADC_ILWCTRL,0xfffc30a8,__READ_WRITE,__ADC_ILWCTRL_bits);
__IO_REG32_BIT(ADC_MIS,    0xfffc30ac,__READ_WRITE,__ADC_MIS_bits);
__IO_REG32_BIT(ADC_IC,     0xfffc30b0,__READ_WRITE,__ADC_IC_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 ***************************************************************************/

#endif    /* __LH75400_H */
