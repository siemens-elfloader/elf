/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Luminary LM3S812
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1.2.4 $
 **
 ***************************************************************************/

#ifndef __IOLM3S812_H
#define __IOLM3S812_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   LM3S812 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/


/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif


/* Device Identification 0 (DID0) */
typedef struct {
  __REG32  MINOR          : 8;
  __REG32  MAJOR          : 8;
  __REG32                 :12;
  __REG32  VER            : 3;
  __REG32                 : 1;
} __did0_bits;

/* Device Identification 1 (DID1) */
typedef struct {
  __REG32  QUAL           : 2;
  __REG32  ROHS           : 1;
  __REG32  PKG            : 2;
  __REG32  TEMP           : 3;
  __REG32                 : 8;
  __REG32  PARTNO         : 8;
  __REG32  FAM            : 4;
  __REG32  VER            : 4;
} __did1_bits;

/* Device Capabilities 0 (DC0) */
typedef struct {
  __REG32  FLSHSZ         :16;
  __REG32  SRAMSZ         :16;
} __dc0_bits;

/* Device Capabilities 1 (DC1) */
typedef struct {
  __REG32  JTAG           : 1;
  __REG32  SWD            : 1;
  __REG32  SWO            : 1;
  __REG32  WDT            : 1;
  __REG32  PLL            : 1;
  __REG32                 : 2;
  __REG32  MPU            : 1;
  __REG32  MAXADCSPD      : 4;
  __REG32  MINSYSDIV      : 4;
  __REG32  ADC            : 1;
  __REG32                 : 3;
  __REG32  PWM            : 1;
  __REG32                 :11;
} __dc1_bits;

/* Device Capabilities 2 (DC2) */
typedef struct {
  __REG32  UART0          : 1; 
  __REG32  UART1          : 1;     
  __REG32                 : 2;
  __REG32  SSI            : 1;
  __REG32                 : 7;
  __REG32  I2C            : 1; 
  __REG32                 : 3;   
  __REG32  GPTM0          : 1;
  __REG32  GPTM1          : 1;
  __REG32  GPTM2          : 1; 
  __REG32                 : 5;
  __REG32  COMP0          : 1;      
  __REG32                 : 7;
} __dc2_bits;

/* Device Capabilities 3 (DC3) */
typedef struct {
  __REG32  PWM0           : 1;
  __REG32  PWM1           : 1;  
  __REG32                 : 4;
  __REG32  C0_N           : 1;
  __REG32  C0_P           : 1;
  __REG32  C0_O           : 1;
  __REG32                 : 7;        
  __REG32  ADC0           : 1;
  __REG32  ADC1           : 1;  
  __REG32                 : 6;        
  __REG32  CCP0           : 1; 
  __REG32  CCP1           : 1;  
  __REG32  CCP2           : 1;
  __REG32  CCP3           : 1;
  __REG32  CCP4           : 1;
  __REG32  CCP5           : 1;       
  __REG32                 : 2;
} __dc3_bits;

/* Device Capabilities 4 (DC4) */
typedef struct {
  __REG32  PORTA          : 1;
  __REG32  PORTB          : 1;
  __REG32  PORTC          : 1;
  __REG32  PORTD          : 1;
  __REG32  PORTE          : 1;    
  __REG32                 :27;
} __dc4_bits;

/* Power-On and Brown-Out Reset Control (PBORCTL) */
typedef struct {
  __REG32  BORWT          : 1;
  __REG32  BORIOR         : 1;
  __REG32  BORTIM         :14;
  __REG32                 :16;
} __pborctl_bits;

/* LDO Power Control (LDOPCTL) */
typedef struct {
  __REG32  VADJ           : 6;
  __REG32                 :26;
} __ldopctl_bits;

/* Software Reset Control 0 (SRCR0) */
typedef struct {
  __REG32                 : 3;
  __REG32  WDT            : 1;
  __REG32                 :12;
  __REG32  ADC            : 1;
  __REG32                 : 3;
  __REG32  PWM            : 1;        
  __REG32                 :11;
} __srcr0_bits;

/* Software Reset Control 1 (SRCR1) */
typedef struct {
  __REG32  UART0          : 1; 
  __REG32  UART1          : 1;     
  __REG32                 : 2;
  __REG32  SSI            : 1;
  __REG32                 : 7;
  __REG32  I2C            : 1; 
  __REG32                 : 3;   
  __REG32  GPTM0          : 1;
  __REG32  GPTM1          : 1;
  __REG32  GPTM2          : 1; 
  __REG32                 : 5;
  __REG32  COMP0          : 1;      
  __REG32                 : 7;
} __srcr1_bits;

/* Software Reset Control 2 (SRCR2) */
typedef struct {
  __REG32  PORTA          : 1;
  __REG32  PORTB          : 1;
  __REG32  PORTC          : 1;
  __REG32  PORTD          : 1; 
  __REG32  PORTE          : 1;   
  __REG32                 :27;
} __srcr2_bits;

/* Raw Interrupt Status (RIS) */
typedef struct {
  __REG32  PLLFRIS        : 1;
  __REG32  BORRIS         : 1;
  __REG32  LDORIS         : 1;
  __REG32  MOFRIS         : 1;
  __REG32  BOFRIS         : 1;
  __REG32  CLRIS          : 1;
  __REG32  PLLLRIS        : 1;
  __REG32                 :25;
} __ris_bits;

/* Interrupt Mask Control (IMC) */
typedef struct {
  __REG32  PLLFIM         : 1;
  __REG32  BORIM          : 1;
  __REG32  LDOIM          : 1;
  __REG32  MOFIM          : 1;
  __REG32  BOFIM          : 1;
  __REG32  CLIM           : 1;
  __REG32  PLLLIM         : 1;
  __REG32                 :25;
} __imc_bits;

/* Masked Interrupt Status and Clear (MISC) */
typedef struct {
  __REG32  PLLFMIS        : 1;
  __REG32  BORMIS         : 1;
  __REG32  LDOMIS         : 1;
  __REG32  MOFMIS         : 1;
  __REG32  BOFMIS         : 1;
  __REG32  CLMIS          : 1;
  __REG32  PLLLMIS        : 1;
  __REG32                 :25;
} __misc_bits;

/* Reset Cause (RESC) */
typedef struct {
  __REG32  EXT            : 1;
  __REG32  POR            : 1;
  __REG32  BOR            : 1;
  __REG32  WDT            : 1;
  __REG32  SW             : 1;
  __REG32  LDO            : 1;
  __REG32                 :26;
} __resc_bits;

/* Run-Mode Clock Configuration (RCC) */
typedef struct {
  __REG32                 : 2;
  __REG32  MOSCVER        : 1;
  __REG32  BOSCVER        : 1;
  __REG32  OSCSRC         : 2;
  __REG32  XTAL           : 4;
  __REG32  PLLVER         : 1;
  __REG32  BYPASS         : 1;
  __REG32  OEN            : 1;
  __REG32  PWRDN          : 1;
  __REG32                 : 8;
  __REG32  USESYS         : 1;
  __REG32  SYSDIV         : 4;
  __REG32  ACG            : 1;
  __REG32                 : 4;
} __rcc_bits;

/* XTAL to PLL Translation (PLLCFG) */
typedef struct {
  __REG32  R              : 5;
  __REG32  F              : 9;
  __REG32  OD             : 2;
  __REG32                 :16;
} __pllcfg_bits;

/* Run-Mode Clock Gating Control 0 (RCGC0)
   Sleep-Mode Clock Gating Control 0 (SCGC0)
   Deep-Sleep-Mode Clock Gating Control 0 (DCGC0) */
typedef struct {
  __REG32  JTAG           : 1;
  __REG32  SWD            : 1;
  __REG32  SWO            : 1;
  __REG32  WDT            : 1;
  __REG32                 : 4;
  __REG32  MAXADCSPD      : 4;
  __REG32                 : 4;  
  __REG32  ADC            : 1;
  __REG32                 : 3;
  __REG32  PWM            : 1;
  __REG32                 :11;
} __rcgc0_bits;

/* Run-Mode Clock Gating Control 1 (RCGC1)
   Sleep-Mode Clock Gating Control 1 (SCGC1)
   Deep-Sleep-Mode Clock Gating Control 1 (DCGC1) */
typedef struct {
  __REG32  UART0          : 1; 
  __REG32  UART1          : 1;     
  __REG32                 : 2;
  __REG32  SSI            : 1;
  __REG32                 : 7;
  __REG32  I2C            : 1; 
  __REG32                 : 3;   
  __REG32  GPTM0          : 1;
  __REG32  GPTM1          : 1;
  __REG32  GPTM2          : 1; 
  __REG32                 : 5;
  __REG32  COMP0          : 1;      
  __REG32                 : 7;
} __rcgc1_bits;

/* Run-Mode Clock Gating Control 2 (RCGC2)
   Sleep-Mode Clock Gating Control 2 (SCGC2)
   Deep-Sleep-Mode Clock Gating Control 2 (DCGC2) */
typedef struct {
  __REG32  PORTA          : 1;
  __REG32  PORTB          : 1;
  __REG32  PORTC          : 1;
  __REG32  PORTD          : 1;
  __REG32  PORTE          : 1;    
  __REG32                 :27;
} __rcgc2_bits;

/* Clock Verification Clear (CLKVCLR) */
typedef struct {
  __REG32  VERCLR         : 1;
  __REG32                 :31;
} __clkvclr_bits;

/* Allow Unregulated LDO to Reset the Part (LDOARST) */
typedef struct {
  __REG32  LDOARST        : 1;
  __REG32                 :31;
} __ldoarst_bits;

/* Flash Memory Protection Read Enable (FMPRE)
   Flash Memory Protection Program Enable (FMPPE) */
typedef struct {
  __REG32  BLOCK0         : 1;
  __REG32  BLOCK1         : 1;
  __REG32  BLOCK2         : 1;
  __REG32  BLOCK3         : 1;
  __REG32                 :28;
} __fmpre_bits;

/* Flash Memory Address (FMA) */
typedef struct {
  __REG32  OFFSET         :12;
  __REG32                 :20;
} __fma_bits;

/* Flash Memory Control (FMC) */
typedef struct {
  __REG32  WRITE          : 1;
  __REG32  ERASE          : 1;
  __REG32  MERASE         : 1;
  __REG32  COMT           : 1;
  __REG32                 :12;
  __REG32  WRKEY          :16;
} __fmc_bits;

/* Flash Controller Raw Interrupt Status (FCRIS) */
typedef struct {
  __REG32  ARIS           : 1;
  __REG32  PRIS           : 1;
  __REG32                 :30;
} __fcris_bits;

/* Flash Controller Interrupt Mask (FCIM) */
typedef struct {
  __REG32  AMASK          : 1;
  __REG32  PMASK          : 1;
  __REG32                 :30;
} __fcim_bits;

/* Flash Controller Masked Interrupt Status and Clear (FCMISC) */
typedef struct {
  __REG32  AMISC          : 1;
  __REG32  PMISC          : 1;
  __REG32                 :30;
} __fcmisc_bits;

/* GPIO registers */
typedef struct {
  __REG32  no0            : 1;
  __REG32  no1            : 1;
  __REG32  no2            : 1;
  __REG32  no3            : 1;
  __REG32  no4            : 1;
  __REG32  no5            : 1;
  __REG32  no6            : 1;
  __REG32  no7            : 1;
  __REG32                 :24;
} __gpio_bits;

/* GPTM Configuration (GPTMCFG) */
typedef struct {
  __REG32  GPTMCFG        : 3;
  __REG32                 :29;
} __gptmcfg_bits;

/* GPTM TimerA Mode (GPTMTAMR) */
typedef struct {
  __REG32  TAMR           : 2;
  __REG32  TACMR          : 1;
  __REG32  TAAMS          : 1;
  __REG32                 :28;
} __gptmtamr_bits;

/* GPTM TimerB Mode (GPTMTBMR) */
typedef struct {
  __REG32  TBMR           : 2;
  __REG32  TBCMR          : 1;
  __REG32  TBAMS          : 1;
  __REG32                 :28;
} __gptmtbmr_bits;

/* GPTM Control (GPTMCTL) */
typedef struct {
  __REG32  TAEN           : 1;
  __REG32  TASTALL        : 1;
  __REG32  TAEVENT        : 2;
  __REG32  RTCEN          : 1;
  __REG32  TAOTE          : 1;
  __REG32  TAPWML         : 1;
  __REG32                 : 1;
  __REG32  TBEN           : 1;
  __REG32  TBSTALL        : 1;
  __REG32  TBEVENT        : 2;
  __REG32                 : 1;
  __REG32  TBOTE          : 1;
  __REG32  TBPWML         : 1;
  __REG32                 :17;
} __gptmctl_bits;

/* GPTM Interrupt Mask (GPTMIMR) */
typedef struct {
  __REG32  TATOIM         : 1;
  __REG32  C1MIM          : 1;
  __REG32  C1EIM          : 1;
  __REG32  RTCIM          : 1;
  __REG32                 : 4;
  __REG32  TBTOIM         : 1;
  __REG32  C2MIM          : 1;
  __REG32  C2EIM          : 1;
  __REG32                 :21;
} __gptmimr_bits;

/* GPTM Raw Interrupt Status (GPTMRIS) */
typedef struct {
  __REG32  TATORIS        : 1;
  __REG32  C1MRIS         : 1;
  __REG32  C1ERIS         : 1;
  __REG32  RTCRIS         : 1;
  __REG32                 : 4;
  __REG32  TBTORIS        : 1;
  __REG32  C2MRIS         : 1;
  __REG32  C2ERIS         : 1;
  __REG32                 :21;
} __gptmris_bits;

/* GPTM Masked Interrupt Status (GPTMMIS) */
typedef struct {
  __REG32  TATOMIS        : 1;
  __REG32  C1MMIS         : 1;
  __REG32  C1EMIS         : 1;
  __REG32  RTCMIS         : 1;
  __REG32                 : 4;
  __REG32  TBTOMIS        : 1;
  __REG32  C2MMIS         : 1;
  __REG32  C2EMIS         : 1;
  __REG32                 :21;
} __gptmmis_bits;

/* GPTM Interrupt Clear (GPTMICR) */
typedef struct {
  __REG32  TATOCINT       : 1;
  __REG32  C1MCINT        : 1;
  __REG32  C1ECINT        : 1;
  __REG32  RTCCINT        : 1;
  __REG32                 : 4;
  __REG32  TBTOCINT       : 1;
  __REG32  C2MCINT        : 1;
  __REG32  C2ECINT        : 1;
  __REG32                 :21;
} __gptmicr_bits;

/* GPTM TimerA Interval Load (GPTMTAILR) */
typedef struct {
  __REG32  TAILRL         :16;
  __REG32  TAILRH         :16;
} __gptmtailr_bits;

/* GPTM TimerA Match (GPTMTAMATCHR) */
typedef struct {
  __REG32  TAMRL          :16;
  __REG32  TAMRH          :16;
} __gptmtamatchr_bits;

/* GPTM TimerA (GPTMTAR) */
typedef struct {
  __REG32  TARL           :16;
  __REG32  TARH           :16;
} __gptmtar_bits;

/* Watchdog Control (WDTCTL) */
typedef struct {
  __REG32  INTEN          : 1;
  __REG32  RESEN          : 1;
  __REG32                 :30;
} __wdtctl_bits;

/* Watchdog Raw Interrupt Status (WDTRIS) */
typedef struct {
  __REG32  WDTRIS         : 1;
  __REG32                 :31;
} __wdtris_bits;

/* Watchdog Masked Interrupt Status (WDTMIS) */
typedef struct {
  __REG32  WDTMIS         : 1;
  __REG32                 :31;
} __wdtmis_bits;

/* Analog-to-Digital Converter Active Sample Sequencer (ADCACTSS) */
typedef struct {
  __REG32  ASEN0          : 1;
  __REG32  ASEN1          : 1;
  __REG32  ASEN2          : 1;
  __REG32  ASEN3          : 1;
  __REG32                 :28;
} __adcactss_bits;

/* Analog-to-Digital Converter Raw Interrupt Status (ADCRIS) */
typedef struct {
  __REG32  INR0           : 1;
  __REG32  INR1           : 1;
  __REG32  INR2           : 1;
  __REG32  INR3           : 1;
  __REG32                 :28;
} __adcris_bits;

/* Analog-to-Digital Converter Interrupt Mask (ADCIM) */
typedef struct {
  __REG32  MASK0          : 1;
  __REG32  MASK1          : 1;
  __REG32  MASK2          : 1;
  __REG32  MASK3          : 1;
  __REG32                 :28;
} __adcim_bits;

/* Analog-to-Digital Converter Interrupt Status and Clear (ADCISC) */
typedef struct {
  __REG32  IN0            : 1;
  __REG32  IN1            : 1;
  __REG32  IN2            : 1;
  __REG32  IN3            : 1;
  __REG32                 :28;
} __adcisc_bits;

/* Analog-to-Digital Converter Overflow Status (ADCOSTAT) */
typedef struct {
  __REG32  OV0            : 1;
  __REG32  OV1            : 1;
  __REG32  OV2            : 1;
  __REG32  OV3            : 1;
  __REG32                 :28;
} __adcostat_bits;

/* Analog-to-Digital Converter Event Multiplexer Select (ADCEMUX) */
typedef struct {
  __REG32  EM0            : 4;
  __REG32  EM1            : 4;
  __REG32  EM2            : 4;
  __REG32  EM3            : 4;
  __REG32                 :16;
} __adcemux_bits;

/* Analog-to-Digital Converter Underflow Status (ADCUSTAT) */
typedef struct {
  __REG32  UV0            : 1;
  __REG32  UV1            : 1;
  __REG32  UV2            : 1;
  __REG32  UV3            : 1;
  __REG32                 :28;
} __adcustat_bits;

/* Analog-to-Digital Converter Sample Sequencer Priority (ADCSSPRI) */
typedef struct {
  __REG32  SS0            : 2;
  __REG32                 : 2;
  __REG32  SS1            : 2;
  __REG32                 : 2;
  __REG32  SS2            : 2;
  __REG32                 : 2;
  __REG32  SS3            : 2;
  __REG32                 :18;
} __adcsspri_bits;

/* Analog-to-Digital Converter Processor Sample Sequence Initiate (ADCPSSI) */
typedef struct {
  __REG32  SS0            : 1;
  __REG32  SS1            : 1;
  __REG32  SS2            : 1;
  __REG32  SS3            : 1;
  __REG32                 :28;
} __adcpssi_bits;

/* Analog-to-Digital Converter Sample Sequence Input Mux Select 0 (ADCSSMUX0) */
typedef struct {
  __REG32  MUX0           : 1;
  __REG32                 : 3;
  __REG32  MUX1           : 1;
  __REG32                 : 3;  
  __REG32  MUX2           : 1;
  __REG32                 : 3;
  __REG32  MUX3           : 1;
  __REG32                 : 3;
  __REG32  MUX4           : 1;
  __REG32                 : 3;
  __REG32  MUX5           : 1;
  __REG32                 : 3;  
  __REG32  MUX6           : 1;
  __REG32                 : 3;
  __REG32  MUX7           : 1;
  __REG32                 : 3;  
} __adcssmux0_bits;

/* Analog-to-Digital Converter Sample Sequence Control 0 (ADCSSCTL0) */
typedef struct {
  __REG32  D0             : 1;
  __REG32  END0           : 1;
  __REG32  IE0            : 1;
  __REG32  TS0            : 1;
  __REG32  D1             : 1;
  __REG32  END1           : 1;
  __REG32  IE1            : 1;
  __REG32  TS1            : 1;
  __REG32  D2             : 1;
  __REG32  END2           : 1;
  __REG32  IE2            : 1;
  __REG32  TS2            : 1;
  __REG32  D3             : 1;
  __REG32  END3           : 1;
  __REG32  IE3            : 1;
  __REG32  TS3            : 1;
  __REG32  D4             : 1;
  __REG32  END4           : 1;
  __REG32  IE4            : 1;
  __REG32  TS4            : 1;
  __REG32  D5             : 1;
  __REG32  END5           : 1;
  __REG32  IE5            : 1;
  __REG32  TS5            : 1;
  __REG32  D6             : 1;
  __REG32  END6           : 1;
  __REG32  IE6            : 1;
  __REG32  TS6            : 1;
  __REG32  D7             : 1;
  __REG32  END7           : 1;
  __REG32  IE7            : 1;
  __REG32  TS7            : 1;    
} __adcssctl0_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 0 (ADCSSFIFO0) */
typedef struct {
  __REG32  DATA           :10;
  __REG32                 :22;
} __adcssfifo0_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 0 Status (ADCSSFSTAT0) */
typedef struct {
  __REG32  TPTR           : 4;
  __REG32  HPTR           : 4;
  __REG32  EMPTY          : 1;
  __REG32                 : 3;
  __REG32  FULL           : 1;
  __REG32                 :19;
} __adcssfstat0_bits;

/* Analog-to-Digital Converter Sample Sequence Input Mux Select 1 (ADCSSMUX1) */
typedef struct {
  __REG32  MUX0           : 1;
  __REG32                 : 3;
  __REG32  MUX1           : 1;
  __REG32                 : 3;  
  __REG32  MUX2           : 1;
  __REG32                 : 3;
  __REG32  MUX3           : 1;
  __REG32                 :19;  
} __adcssmux1_bits;

/* Analog-to-Digital Converter Sample Sequence Control 1 (ADCSSCTL1) */
typedef struct {
  __REG32  D0             : 1;
  __REG32  END0           : 1;
  __REG32  IE0            : 1;
  __REG32  TS0            : 1;
  __REG32  D1             : 1;
  __REG32  END1           : 1;
  __REG32  IE1            : 1;
  __REG32  TS1            : 1;
  __REG32  D2             : 1;
  __REG32  END2           : 1;
  __REG32  IE2            : 1;
  __REG32  TS2            : 1;
  __REG32  D3             : 1;
  __REG32  END3           : 1;
  __REG32  IE3            : 1;
  __REG32  TS3            : 1;
  __REG32                 :16;   
} __adcssctl1_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 1 (ADCSSFIFO1) */
typedef struct {
  __REG32  DATA           :10;
  __REG32                 :22;
} __adcssfifo1_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 1 Status (ADCSSFSTAT1) */
typedef struct {
  __REG32  TPTR           : 4;
  __REG32  HPTR           : 4;
  __REG32  EMPTY          : 1;
  __REG32                 : 3;
  __REG32  FULL           : 1;
  __REG32                 :19;
} __adcssfstat1_bits;

/* Analog-to-Digital Converter Sample Sequence Input Mux Select 2 (ADCSSMUX2) */
typedef struct {
  __REG32  MUX0           : 1;
  __REG32                 : 3;
  __REG32  MUX1           : 1;
  __REG32                 : 3;  
  __REG32  MUX2           : 1;
  __REG32                 : 3;
  __REG32  MUX3           : 1;
  __REG32                 :19;  
} __adcssmux2_bits;

/* Analog-to-Digital Converter Sample Sequence Control 2 (ADCSSCTL2) */
typedef struct {
  __REG32  D0             : 1;
  __REG32  END0           : 1;
  __REG32  IE0            : 1;
  __REG32  TS0            : 1;
  __REG32  D1             : 1;
  __REG32  END1           : 1;
  __REG32  IE1            : 1;
  __REG32  TS1            : 1;
  __REG32  D2             : 1;
  __REG32  END2           : 1;
  __REG32  IE2            : 1;
  __REG32  TS2            : 1;
  __REG32  D3             : 1;
  __REG32  END3           : 1;
  __REG32  IE3            : 1;
  __REG32  TS3            : 1;
  __REG32                 :16;   
} __adcssctl2_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 2 (ADCSSFIFO2) */
typedef struct {
  __REG32  DATA           :10;
  __REG32                 :22;
} __adcssfifo2_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 2 Status (ADCSSFSTAT2) */
typedef struct {
  __REG32  TPTR           : 4;
  __REG32  HPTR           : 4;
  __REG32  EMPTY          : 1;
  __REG32                 : 3;
  __REG32  FULL           : 1;
  __REG32                 :19;
} __adcssfstat2_bits;

/* Analog-to-Digital Converter Sample Sequence Input Mux Select 3 (ADCSSMUX3) */
typedef struct {
  __REG32  MUX0           : 1;
  __REG32                 :31;
} __adcssmux3_bits;

/* Analog-to-Digital Converter Sample Sequence Control 3 (ADCSSCTL3) */
typedef struct {
  __REG32  D0             : 1;
  __REG32  END0           : 1;
  __REG32  IE0            : 1;
  __REG32  TS0            : 1;
  __REG32                 :28;   
} __adcssctl3_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 3 (ADCSSFIFO3) */
typedef struct {
  __REG32  DATA           :10;
  __REG32                 :22;
} __adcssfifo3_bits;

/* Analog-to-Digital Converter Sample Sequence FIFO 3 Status (ADCSSFSTAT3) */
typedef struct {
  __REG32  TPTR           : 4;
  __REG32  HPTR           : 4;
  __REG32  EMPTY          : 1;
  __REG32                 : 3;
  __REG32  FULL           : 1;
  __REG32                 :19;
} __adcssfstat3_bits;

/* Analog-to-Digital Converter Test Mode Loopback (ADCTMLB) */
typedef struct {
  __REG32  MUX            : 3;
  __REG32  TS             : 1;
  __REG32  DIFF           : 1;
  __REG32  CONT           : 1;
  __REG32  CNT            : 4;
  __REG32                 :22;
} __adctmlb_bits;

/* UART Data (UARTDR) */
typedef struct {
  __REG32  DATA           : 8;
  __REG32  FE             : 1;
  __REG32  PE             : 1;
  __REG32  BE             : 1;
  __REG32  OE             : 1;
  __REG32                 :20;
} __uartdr_bits;

/* UART Receive Status/Error Clear (UARTRSR/UARTECR) */
typedef union {
  /* UARTRSR */
  struct {
    __REG32  FE           : 1;
    __REG32  PE           : 1;
    __REG32  BE           : 1;
    __REG32  OE           : 1;
    __REG32               :28;
  };
  /* UARTECR */
  struct {
    __REG32  DATA         : 8;
    __REG32               :24;
  };
} __uartrsr_bits;

/* UART Flag (UARTFR) */
typedef struct {
  __REG32                 : 3;
  __REG32  BUSY           : 1;
  __REG32  RXFE           : 1;
  __REG32  TXFF           : 1;
  __REG32  RXFF           : 1;
  __REG32  TXFE           : 1;
  __REG32                 :24;
} __uartfr_bits;

/* UART Fractional Baud-Rate Divisor (UARTFBRD) */
typedef struct {
  __REG32  DIVFRAC        : 6;
  __REG32                 :26;
} __uartfbrd_bits;

/* UART Line Control (UARTLCRH) */
typedef struct {
  __REG32  BRK            : 1;
  __REG32  PEN            : 1;
  __REG32  EPS            : 1;
  __REG32  STP2           : 1;
  __REG32  FEN            : 1;
  __REG32  WLEN           : 2;
  __REG32  SPS            : 1;
  __REG32                 :24;
} __uartlcrh_bits;

/* UART Control (UARTCTL) */
typedef struct {
  __REG32  UARTEN         : 1;
  __REG32                 : 6;
  __REG32  LBE            : 1;
  __REG32  TXE            : 1;
  __REG32  RXE            : 1;
  __REG32                 :22;
} __uartctl_bits;

/* UART Interrupt FIFO Level Select (UARTIFLS) */
typedef struct {
  __REG32  TXIFLSEL       : 3;
  __REG32  RXIFLSEL       : 3;
  __REG32                 :26;
} __uartifls_bits;

/* UART Interrupt Mask (UARTIM) */
typedef struct {
  __REG32                 : 4;
  __REG32  RXIM           : 1;
  __REG32  TXIM           : 1;
  __REG32  RTIM           : 1;
  __REG32  FEIM           : 1;
  __REG32  PEIM           : 1;
  __REG32  BEIM           : 1;
  __REG32  OEIM           : 1;
  __REG32                 :21;
} __uartim_bits;

/* UART Raw Interrupt Status (UARTRIS) */
typedef struct {
  __REG32                 : 4;
  __REG32  RXRIS          : 1;
  __REG32  TXRIS          : 1;
  __REG32  RTRIS          : 1;
  __REG32  FERIS          : 1;
  __REG32  PERIS          : 1;
  __REG32  BERIS          : 1;
  __REG32  OERIS          : 1;
  __REG32                 :21;
} __uartris_bits;

/* UART Masked Interrupt Status (UARTMIS) */
typedef struct {
  __REG32                 : 4;
  __REG32  RXMIS          : 1;
  __REG32  TXMIS          : 1;
  __REG32  RTMIS          : 1;
  __REG32  FEMIS          : 1;
  __REG32  PEMIS          : 1;
  __REG32  BEMIS          : 1;
  __REG32  OEMIS          : 1;
  __REG32                 :21;
} __uartmis_bits;

/* UART Interrupt Clear (UARTICR) */
typedef struct {
  __REG32                 : 4;
  __REG32  RXIC           : 1;
  __REG32  TXIC           : 1;
  __REG32  RTIC           : 1;
  __REG32  FEIC           : 1;
  __REG32  PEIC           : 1;
  __REG32  BEIC           : 1;
  __REG32  OEIC           : 1;
  __REG32                 :21;
} __uarticr_bits;

/* SSI Control 0 (SSICR0) */
typedef struct {
  __REG32  DSS            : 4;
  __REG32  FRF            : 2;
  __REG32  SPO            : 1;
  __REG32  SPH            : 1;
  __REG32  SCR            : 8;
  __REG32                 :16;
} __ssicr0_bits;

/* SSI Control 1 (SSICR1) */
typedef struct {
  __REG32  LBM            : 1;
  __REG32  SSE            : 1;
  __REG32  MS             : 1;
  __REG32  SOD            : 1;
  __REG32                 :28;
} __ssicr1_bits;

/* SSI Status (SSISR) */
typedef struct {
  __REG32  TFE            : 1;
  __REG32  TNF            : 1;
  __REG32  RNE            : 1;
  __REG32  RFF            : 1;
  __REG32  BSY            : 1;
  __REG32                 :27;
} __ssisr_bits;

/* SSI Interrupt Mask (SSIIM) */
typedef struct {
  __REG32  RORIM          : 1;
  __REG32  RTIM           : 1;
  __REG32  RXIM           : 1;
  __REG32  TXIM           : 1;
  __REG32                 :28;
} __ssiim_bits;

/* SSI Raw Interrupt Status (SSIRIS) */
typedef struct {
  __REG32  RORRIS         : 1;
  __REG32  RTRIS          : 1;
  __REG32  RXRIS          : 1;
  __REG32  TXRIS          : 1;
  __REG32                 :28;
} __ssiris_bits;

/* SSI Masked Interrupt Status (SSIMIS) */
typedef struct {
  __REG32  RORMIS         : 1;
  __REG32  RTMIS          : 1;
  __REG32  RXMIS          : 1;
  __REG32  TXMIS          : 1;
  __REG32                 :28;
} __ssimis_bits;

/* SSI Interrupt Clear (SSIICR) */
typedef struct {
  __REG32  RORIC          : 1;
  __REG32  RTIC           : 1;
  __REG32                 :30;
} __ssiicr_bits;

/* I2C Master Slave Address (I2CMSA) */
typedef struct {
  __REG32  R_S            : 1;
  __REG32  SA             : 7;
  __REG32                 :24;
} __i2cmsa_bits;

/* I2C Master Control/Status (I2CMCS) */
typedef union {
  /* I2CMS */
  struct {
    __REG32  BUSY         : 1;
    __REG32  ERROR        : 1;
    __REG32  ADRACK       : 1;
    __REG32  DATACK       : 1;
    __REG32  ARBLST       : 1;
    __REG32  IDLE         : 1;
    __REG32  BUSBSY       : 1;
    __REG32               :25;
  };
  /* I2CMC */
  struct {
    __REG32  RUN          : 1;
    __REG32  START        : 1;
    __REG32  STOP         : 1;
    __REG32  ACK          : 1;
    __REG32               :28;
  };
} __i2cmcs_bits;

/* I2C Master Interrupt Mask (I2CMIMR) */
typedef struct {
  __REG32  IM             : 1;
  __REG32                 :31;
} __i2cmimr_bits;

/* I2C Master Raw Interrupt Status (I2CMRIS) */
typedef struct {
  __REG32  RIS            : 1;
  __REG32                 :31;
} __i2cmris_bits;

/* I2C Master Masked Interrupt Status (I2CMMIS) */
typedef struct {
  __REG32  MIS            : 1;
  __REG32                 :31;
} __i2cmmis_bits;

/* I2C Master Interrupt Clear (I2CMICR) */
typedef struct {
  __REG32  IC             : 1;
  __REG32                 :31;
} __i2cmicr_bits;

/* I2C Master Configuration (I2CMCR) */
typedef struct {
  __REG32  LPBK           : 1;
  __REG32                 : 3;
  __REG32  MFE            : 1;
  __REG32  SFE            : 1;
  __REG32                 :26;
} __i2cmcr_bits;

/* I2C Slave Own Address (I2CSOAR) */
typedef struct {
  __REG32  OAR            : 7;
  __REG32                 :25;
} __i2csoar_bits;

/* I2C Slave Control/Status (I2CSCSR) */
typedef union {
  /* I2CSSR */
  struct {
    __REG32  RREQ         : 1;
    __REG32  TREQ         : 1;
    __REG32               :30;
  };
  /* I2CSCR */
  struct {
    __REG32  DA           : 1;
    __REG32               :31;
  };
} __i2cscsr_bits;

/* I2C Slave Interrupt Mask (I2CSIMR) */
typedef struct {
  __REG32  IM             : 1;
  __REG32                 :31;
} __i2csimr_bits;

/* I2C Slave Raw Interrupt Status (I2CSRIS) */
typedef struct {
  __REG32  RIS            : 1;
  __REG32                 :31;
} __i2csris_bits;

/* I2C Slave Masked Interrupt Status (I2CSMIS) */
typedef struct {
  __REG32  MIS            : 1;
  __REG32                 :31;
} __i2csmis_bits;

/* I2C Slave Interrupt Clear (I2CSICR) */
typedef struct {
  __REG32  IC             : 1;
  __REG32                 :31;
} __i2csicr_bits;

/* Analog Comparator Masked Interrupt Status (ACMIS)
   Analog Comparator Raw Interrupt Status (ACRIS)
   Analog Comparator Interrupt Enable (ACINTEN) */
typedef struct {
  __REG32  IN0            : 1;
  __REG32                 :31;
} __acmis_bits;

/* Analog Comparator Reference Voltage Control (ACREFCTL) */
typedef struct {
  __REG32  VREF           : 4;
  __REG32                 : 4;
  __REG32  RNG            : 1;
  __REG32  EN             : 1;
  __REG32                 :22;
} __acrefctl_bits;

/* Analog Comparator Status (ACSTAT) */
typedef struct {
  __REG32                 : 1;
  __REG32  OVAL           : 1;
  __REG32                 :30;
} __acstat_bits;

/* Analog Comparator Control (ACCTL) */
typedef struct {
  __REG32                 : 1;
  __REG32  CINV           : 1;
  __REG32  ISEN           : 2;
  __REG32  ISLVAL         : 1;
  __REG32                 : 4;
  __REG32  ASRCP          : 2;
  __REG32                 :21;
} __acctl_bits;

/* Pulse Width Modulator Master Control (PWMCTL) */
typedef struct {
  __REG32  GlobalSync0    : 1;
  __REG32  GlobalSync1    : 1;
  __REG32                 :30;
} __pwmctl_bits;

/* Pulse Width Modulator Time Base Sync (PWMSYNC) */
typedef struct {
  __REG32  Sync0          : 1;
  __REG32  Sync1          : 1;
  __REG32                 :30;
} __pwmsync_bits;

/* Pulse Width Modulator Output Enable (PWMENABLE) */
typedef struct {
  __REG32  PWM0En         : 1;
  __REG32  PWM1En         : 1;
  __REG32  PWM2En         : 1;
  __REG32  PWM3En         : 1;    
  __REG32                 :28;
} __pwmenable_bits;

/* Pulse Width Modulator Output Inversion (PWMINVERT) */
typedef struct {
  __REG32  PWM0Inv        : 1;
  __REG32  PWM1Inv        : 1;
  __REG32  PWM2Inv        : 1;
  __REG32  PWM3Inv        : 1;    
  __REG32                 :28;
} __pwminvert_bits;

/* Pulse Width Modulator Output Fault (PWMFAULT) */
typedef struct {
  __REG32  Fault0         : 1;
  __REG32  Fault1         : 1;
  __REG32  Fault2         : 1;
  __REG32  Fault3         : 1;    
  __REG32                 :28;
} __pwmfault_bits;

/* Pulse Width Modulator Interrupt Enable (PWMINTEN) */
typedef struct {
  __REG32  IntPWM0        : 1;
  __REG32  IntPWM1        : 1;
  __REG32                 :14;
  __REG32  IntFault       : 1;    
  __REG32                 :15;
} __pwminten_bits;

/* Pulse Width Modulator Interrupt Status (PWMRIS) */
typedef struct {
  __REG32  IntPWM0        : 1;
  __REG32  IntPWM1        : 1;
  __REG32                 :14;
  __REG32  IntFault       : 1;    
  __REG32                 :15;
} __pwmris_bits;

/* Pulse Width Modulator Interrupt Status and Clear (PWMISC) */
typedef struct {
  __REG32  IntPWM0        : 1;
  __REG32  IntPWM1        : 1;
  __REG32                 :14;
  __REG32  IntFault       : 1;    
  __REG32                 :15;
} __pwmisc_bits;

/* Pulse Width Modulator Status (PWMSTATUS) */
typedef struct {
  __REG32  Fault          : 1;   
  __REG32                 :31;
} __pwmstatus_bits;

/* Pulse Width Modulator 0 Control (PWM0CTL) */
typedef struct {
  __REG32  Enable         : 1;
  __REG32  Mode           : 1;
  __REG32  Debug          : 1;
  __REG32  LoadUpd        : 1;    
  __REG32  CmpAUpd        : 1;
  __REG32  CmpBUpd        : 1;
  __REG32                 :26;                  
} __pwm0ctl_bits;

/* Pulse Width Modulator 0 Interrupt/Trigger Enable (PWM0INTEN) */
typedef struct {
  __REG32  IntCntZero     : 1;
  __REG32  IntCntLoad     : 1;
  __REG32  IntCmpAU       : 1;
  __REG32  IntCmpAD       : 1;    
  __REG32  IntCmpBU       : 1;
  __REG32  IntCmpBD       : 1;
  __REG32                 : 2;   
  __REG32  TrCntZero      : 1;
  __REG32  TrCntLoad      : 1;
  __REG32  TrCmpAU        : 1;
  __REG32  TrCmpAD        : 1;    
  __REG32  TrCmpBU        : 1;
  __REG32  TrCmpBD        : 1;  
  __REG32                 :18;                     
} __pwm0inten_bits;

/* Pulse Width Modulator 0 Raw Interrupt Status (PWM0RIS) */
typedef struct {
  __REG32  IntCntZero     : 1;
  __REG32  IntCntLoad     : 1;
  __REG32  IntCmpAU       : 1;
  __REG32  IntCmpAD       : 1;    
  __REG32  IntCmpBU       : 1;
  __REG32  IntCmpBD       : 1;     
  __REG32                 :26;                     
} __pwm0ris_bits;

/* Pulse Width Modulator 0 Interrupt Status and Clear (PWM0ISC) */
typedef struct {
  __REG32  IntCntZero     : 1;
  __REG32  IntCntLoad     : 1;
  __REG32  IntCmpAU       : 1;
  __REG32  IntCmpAD       : 1;    
  __REG32  IntCmpBU       : 1;
  __REG32  IntCmpBD       : 1;    
  __REG32                 :26;                     
} __pwm0isc_bits;

/* Pulse Width Modulator 0 Load (PWM0LOAD) */
typedef struct {
  __REG32  Load           :16;    
  __REG32                 :16;                     
} __pwm0load_bits;

/* Pulse Width Modulator 0 Counter (PWM0COUNT) */
typedef struct {
  __REG32  Count          :16;    
  __REG32                 :16;                     
} __pwm0count_bits;

/* Pulse Width Modulator 0 Compare A (PWM0CMPA) */
typedef struct {
  __REG32  CompA          :16;    
  __REG32                 :16;                     
} __pwm0cmpa_bits;

/* Pulse Width Modulator 0 Compare B (PWM0CMPB) */
typedef struct {
  __REG32  CompB          :16;    
  __REG32                 :16;                     
} __pwm0cmpb_bits;

/* Pulse Width Modulator 0 Generator A Control (PWM0GENA) */
typedef struct {
  __REG32  ActZer0        : 2;
  __REG32  ActLoad        : 2;
  __REG32  ActCmpAU       : 2;
  __REG32  ActCmpAD       : 2;    
  __REG32  ActCmpBU       : 2;
  __REG32  ActCmpBD       : 2;    
  __REG32                 :20;                     
} __pwm0gena_bits;

/* Pulse Width Modulator 0 Generator B Control (PWM0GENB) */
typedef struct {
  __REG32  ActZer0        : 2;
  __REG32  ActLoad        : 2;
  __REG32  ActCmpAU       : 2;
  __REG32  ActCmpAD       : 2;    
  __REG32  ActCmpBU       : 2;
  __REG32  ActCmpBD       : 2;    
  __REG32                 :20;                     
} __pwm0genb_bits;

/* Pulse Width Modulator 0 Dead-Band Control (PWM0DBCTL) */
typedef struct {
  __REG32  Enable         : 1;    
  __REG32                 :31;                     
} __pwm0dbctl_bits;

/* Pulse Width Modulator 0 Dead-Band Rising-Edge Delay (PWM0DBRISE) */
typedef struct {
  __REG32  RiseDelay      :12;    
  __REG32                 :20;                     
} __pwm0dbrise_bits;

/* Pulse Width Modulator 0 Dead-Band Falling-Edge Delay (PWM0DBFALL) */
typedef struct {
  __REG32  FallDelay      :12;    
  __REG32                 :20;                     
} __pwm0dbfall_bits;

/* Interrupt Controller Type Register */
typedef struct {
  __REG32  INTLINESNUM    : 5;
  __REG32                 :27;
} __nvic_bits;

/* SysTick Control and Status Register */
typedef struct {
  __REG32  ENABLE         : 1;
  __REG32  TICKINT        : 1;
  __REG32  CLKSOURCE      : 1;
  __REG32                 :13;
  __REG32  COUNTFLAG      : 1;
  __REG32                 :15;
} __systickcsr_bits;

/* SysTick Reload Value Register */
typedef struct {
  __REG32  RELOAD         :24;
  __REG32                 : 8;
} __systickrvr_bits;

/* SysTick Current Value Register */
typedef struct {
  __REG32  CURRENT        :24;
  __REG32                 : 8;
} __systickcvr_bits;

/* SysTick Calibration Value Register */
typedef struct {
  __REG32  TENMS          :24;
  __REG32                 : 6;
  __REG32  SKEW           : 1;
  __REG32  NOREF          : 1;
} __systickcalvr_bits;

/* Interrupt Set-Enable Registers 0-31 */
typedef struct {
  __REG32  SETENA0        : 1;
  __REG32  SETENA1        : 1;
  __REG32  SETENA2        : 1;
  __REG32  SETENA3        : 1;
  __REG32  SETENA4        : 1;
  __REG32  SETENA5        : 1;
  __REG32  SETENA6        : 1;
  __REG32  SETENA7        : 1;
  __REG32  SETENA8        : 1;
  __REG32  SETENA9        : 1;
  __REG32  SETENA10       : 1;
  __REG32  SETENA11       : 1;
  __REG32  SETENA12       : 1;
  __REG32  SETENA13       : 1;
  __REG32  SETENA14       : 1;
  __REG32  SETENA15       : 1;
  __REG32  SETENA16       : 1;
  __REG32  SETENA17       : 1;
  __REG32  SETENA18       : 1;
  __REG32  SETENA19       : 1;
  __REG32  SETENA20       : 1;
  __REG32  SETENA21       : 1;
  __REG32  SETENA22       : 1;
  __REG32  SETENA23       : 1;
  __REG32  SETENA24       : 1;
  __REG32  SETENA25       : 1;
  __REG32  SETENA26       : 1;
  __REG32  SETENA27       : 1;
  __REG32  SETENA28       : 1;
  __REG32  SETENA29       : 1;
  __REG32  SETENA30       : 1;
  __REG32  SETENA31       : 1;
} __setena0_bits;

/* Interrupt Clear-Enable Registers 0-31 */
typedef struct {
  __REG32  CLRENA0        : 1;
  __REG32  CLRENA1        : 1;
  __REG32  CLRENA2        : 1;
  __REG32  CLRENA3        : 1;
  __REG32  CLRENA4        : 1;
  __REG32  CLRENA5        : 1;
  __REG32  CLRENA6        : 1;
  __REG32  CLRENA7        : 1;
  __REG32  CLRENA8        : 1;
  __REG32  CLRENA9        : 1;
  __REG32  CLRENA10       : 1;
  __REG32  CLRENA11       : 1;
  __REG32  CLRENA12       : 1;
  __REG32  CLRENA13       : 1;
  __REG32  CLRENA14       : 1;
  __REG32  CLRENA15       : 1;
  __REG32  CLRENA16       : 1;
  __REG32  CLRENA17       : 1;
  __REG32  CLRENA18       : 1;
  __REG32  CLRENA19       : 1;
  __REG32  CLRENA20       : 1;
  __REG32  CLRENA21       : 1;
  __REG32  CLRENA22       : 1;
  __REG32  CLRENA23       : 1;
  __REG32  CLRENA24       : 1;
  __REG32  CLRENA25       : 1;
  __REG32  CLRENA26       : 1;
  __REG32  CLRENA27       : 1;
  __REG32  CLRENA28       : 1;
  __REG32  CLRENA29       : 1;
  __REG32  CLRENA30       : 1;
  __REG32  CLRENA31       : 1;
} __clrena0_bits;

/* Interrupt Set-Pending Register 0-31 */
typedef struct {
  __REG32  SETPEND0       : 1;
  __REG32  SETPEND1       : 1;
  __REG32  SETPEND2       : 1;
  __REG32  SETPEND3       : 1;
  __REG32  SETPEND4       : 1;
  __REG32  SETPEND5       : 1;
  __REG32  SETPEND6       : 1;
  __REG32  SETPEND7       : 1;
  __REG32  SETPEND8       : 1;
  __REG32  SETPEND9       : 1;
  __REG32  SETPEND10      : 1;
  __REG32  SETPEND11      : 1;
  __REG32  SETPEND12      : 1;
  __REG32  SETPEND13      : 1;
  __REG32  SETPEND14      : 1;
  __REG32  SETPEND15      : 1;
  __REG32  SETPEND16      : 1;
  __REG32  SETPEND17      : 1;
  __REG32  SETPEND18      : 1;
  __REG32  SETPEND19      : 1;
  __REG32  SETPEND20      : 1;
  __REG32  SETPEND21      : 1;
  __REG32  SETPEND22      : 1;
  __REG32  SETPEND23      : 1;
  __REG32  SETPEND24      : 1;
  __REG32  SETPEND25      : 1;
  __REG32  SETPEND26      : 1;
  __REG32  SETPEND27      : 1;
  __REG32  SETPEND28      : 1;
  __REG32  SETPEND29      : 1;
  __REG32  SETPEND30      : 1;
  __REG32  SETPEND31      : 1;
} __setpend0_bits;

/* Interrupt Clear-Pending Register 0-31 */
typedef struct {
  __REG32  CLRPEND0       : 1;
  __REG32  CLRPEND1       : 1;
  __REG32  CLRPEND2       : 1;
  __REG32  CLRPEND3       : 1;
  __REG32  CLRPEND4       : 1;
  __REG32  CLRPEND5       : 1;
  __REG32  CLRPEND6       : 1;
  __REG32  CLRPEND7       : 1;
  __REG32  CLRPEND8       : 1;
  __REG32  CLRPEND9       : 1;
  __REG32  CLRPEND10      : 1;
  __REG32  CLRPEND11      : 1;
  __REG32  CLRPEND12      : 1;
  __REG32  CLRPEND13      : 1;
  __REG32  CLRPEND14      : 1;
  __REG32  CLRPEND15      : 1;
  __REG32  CLRPEND16      : 1;
  __REG32  CLRPEND17      : 1;
  __REG32  CLRPEND18      : 1;
  __REG32  CLRPEND19      : 1;
  __REG32  CLRPEND20      : 1;
  __REG32  CLRPEND21      : 1;
  __REG32  CLRPEND22      : 1;
  __REG32  CLRPEND23      : 1;
  __REG32  CLRPEND24      : 1;
  __REG32  CLRPEND25      : 1;
  __REG32  CLRPEND26      : 1;
  __REG32  CLRPEND27      : 1;
  __REG32  CLRPEND28      : 1;
  __REG32  CLRPEND29      : 1;
  __REG32  CLRPEND30      : 1;
  __REG32  CLRPEND31      : 1;
} __clrpend0_bits;

/* Active Bit Register 0-31 */
typedef struct {
  __REG32  ACTIVE0        : 1;
  __REG32  ACTIVE1        : 1;
  __REG32  ACTIVE2        : 1;
  __REG32  ACTIVE3        : 1;
  __REG32  ACTIVE4        : 1;
  __REG32  ACTIVE5        : 1;
  __REG32  ACTIVE6        : 1;
  __REG32  ACTIVE7        : 1;
  __REG32  ACTIVE8        : 1;
  __REG32  ACTIVE9        : 1;
  __REG32  ACTIVE10       : 1;
  __REG32  ACTIVE11       : 1;
  __REG32  ACTIVE12       : 1;
  __REG32  ACTIVE13       : 1;
  __REG32  ACTIVE14       : 1;
  __REG32  ACTIVE15       : 1;
  __REG32  ACTIVE16       : 1;
  __REG32  ACTIVE17       : 1;
  __REG32  ACTIVE18       : 1;
  __REG32  ACTIVE19       : 1;
  __REG32  ACTIVE20       : 1;
  __REG32  ACTIVE21       : 1;
  __REG32  ACTIVE22       : 1;
  __REG32  ACTIVE23       : 1;
  __REG32  ACTIVE24       : 1;
  __REG32  ACTIVE25       : 1;
  __REG32  ACTIVE26       : 1;
  __REG32  ACTIVE27       : 1;
  __REG32  ACTIVE28       : 1;
  __REG32  ACTIVE29       : 1;
  __REG32  ACTIVE30       : 1;
  __REG32  ACTIVE31       : 1;
} __active0_bits;

/* Interrupt Priority Registers 0-3 */
typedef struct {
  __REG32  PRI_0          : 8;
  __REG32  PRI_1          : 8;
  __REG32  PRI_2          : 8;
  __REG32  PRI_3          : 8;
} __pri0_bits;

/* Interrupt Priority Registers 4-7 */
typedef struct {
  __REG32  PRI_4          : 8;
  __REG32  PRI_5          : 8;
  __REG32  PRI_6          : 8;
  __REG32  PRI_7          : 8;
} __pri1_bits;

/* Interrupt Priority Registers 8-11 */
typedef struct {
  __REG32  PRI_8          : 8;
  __REG32  PRI_9          : 8;
  __REG32  PRI_10         : 8;
  __REG32  PRI_11         : 8;
} __pri2_bits;

/* Interrupt Priority Registers 12-15 */
typedef struct {
  __REG32  PRI_12         : 8;
  __REG32  PRI_13         : 8;
  __REG32  PRI_14         : 8;
  __REG32  PRI_15         : 8;
} __pri3_bits;

/* Interrupt Priority Registers 16-19 */
typedef struct {
  __REG32  PRI_16         : 8;
  __REG32  PRI_17         : 8;
  __REG32  PRI_18         : 8;
  __REG32  PRI_19         : 8;
} __pri4_bits;

/* Interrupt Priority Registers 20-23 */
typedef struct {
  __REG32  PRI_20         : 8;
  __REG32  PRI_21         : 8;
  __REG32  PRI_22         : 8;
  __REG32  PRI_23         : 8;
} __pri5_bits;

/* Interrupt Priority Registers 24-27 */
typedef struct {
  __REG32  PRI_24         : 8;
  __REG32  PRI_25         : 8;
  __REG32  PRI_26         : 8;
  __REG32  PRI_27         : 8;
} __pri6_bits;

/* Interrupt Priority Registers 28-31 */
typedef struct {
  __REG32  PRI_28         : 8;
  __REG32  PRI_29         : 8;
  __REG32  PRI_30         : 8;
  __REG32  PRI_31         : 8;
} __pri7_bits;

/* CPU ID Base Register */
typedef struct {
  __REG32  REVISION       : 4;
  __REG32  PARTNO         :12;
  __REG32                 : 4;
  __REG32  VARIANT        : 4;
  __REG32  IMPLEMENTER    : 8;
} __cpuidbr_bits;

/* Interrupt Control State Register */
typedef struct {
  __REG32  VECTACTIVE     :10;
  __REG32                 : 1;
  __REG32  RETTOBASE      : 1;
  __REG32  VECTPENDING    :10;
  __REG32  ISRPENDING     : 1;
  __REG32  ISRPREEMPT     : 1;
  __REG32                 : 1;
  __REG32  PENDSTCLR      : 1;
  __REG32  PENDSTSET      : 1;
  __REG32  PENDSVCLR      : 1;
  __REG32  PENDSVSET      : 1;
  __REG32                 : 2;
  __REG32  NMIPENDSET     : 1;
} __icsr_bits;

/* Vector Table Offset Register */
typedef struct {
  __REG32                 : 7;
  __REG32  TBLOFF         :22;
  __REG32  TBLBASE        : 1;
  __REG32                 : 2;
} __vtor_bits;

/* Application Interrupt and Reset Control Register */
typedef struct {
  __REG32  VECTRESET      : 1;
  __REG32  VECTCLRACTIVE  : 1;
  __REG32  SYSRESETREQ    : 1;
  __REG32                 : 5;
  __REG32  PRIGROUP       : 3;
  __REG32                 : 4;
  __REG32  ENDIANESS      : 1;
  __REG32  VECTKEY        :16;
} __aircr_bits;

/* System Control Register */
typedef struct {
  __REG32                 : 1;
  __REG32  SLEEPONEXIT    : 1;
  __REG32  SLEEPDEEP      : 1;
  __REG32                 : 1;
  __REG32  SEVONPEND      : 1;
  __REG32                 :27;
} __scr_bits;

/* Configuration Control Register */
typedef struct {
  __REG32  NONEBASETHRDENA: 1;
  __REG32  USERSETMPEND   : 1;
  __REG32                 : 1;
  __REG32  UNALIGN_TRP    : 1;
  __REG32  DIV_0_TRP      : 1;
  __REG32                 : 3;
  __REG32  BFHFNMIGN      : 1;
  __REG32                 :23;
} __ccr_bits;

/* System Handler Control and State Register */
typedef struct {
  __REG32  MEMFAULTACT    : 1;
  __REG32  BUSFAULTACT    : 1;
  __REG32                 : 1;
  __REG32  USGFAULTACT    : 1;
  __REG32                 : 3;
  __REG32  SVCALLACT      : 1;
  __REG32  MONITORACT     : 1;
  __REG32                 : 1;
  __REG32  PENDSVACT      : 1;
  __REG32  SYSTICKACT     : 1;
  __REG32                 : 1;
  __REG32  MEMFAULTPENDED : 1;
  __REG32  BUSFAULTPENDED : 1;
  __REG32  SVCALLPENDED   : 1;
  __REG32  MEMFAULTENA    : 1;
  __REG32  BUSFAULTENA    : 1;
  __REG32  USGFAULTENA    : 1;
  __REG32                 :13;
} __shcsr_bits;

/* Configurable Fault Status Registers */
typedef struct {
  __REG32  IACCVIOL       : 1;
  __REG32  DACCVIOL       : 1;
  __REG32                 : 1;
  __REG32  MUNSTKERR      : 1;
  __REG32  MSTKERR        : 1;
  __REG32                 : 2;
  __REG32  MMARVALID      : 1;
  __REG32  IBUSERR        : 1;
  __REG32  PRECISERR      : 1;
  __REG32  IMPRECISERR    : 1;
  __REG32  UNSTKERR       : 1;
  __REG32  STKERR         : 1;
  __REG32                 : 2;
  __REG32  BFARVALID      : 1;
  __REG32  UNDEFINSTR     : 1;
  __REG32  INVSTATE       : 1;
  __REG32  INVPC          : 1;
  __REG32  NOCP           : 1;
  __REG32                 : 4;
  __REG32  UNALIGNED      : 1;
  __REG32  DIVBYZERO      : 1;
  __REG32                 : 6;
} __cfsr_bits;

/* Hard Fault Status Register */
typedef struct {
  __REG32                 : 1;
  __REG32  VECTTBL        : 1;
  __REG32                 :28;
  __REG32  FORCED         : 1;
  __REG32  DEBUGEVT       : 1;
} __hfsr_bits;

/* Debug Fault Status Register */
typedef struct {
  __REG32  HALTED         : 1;
  __REG32  BKPT           : 1;
  __REG32  DWTTRAP        : 1;
  __REG32  VCATCH         : 1;
  __REG32  EXTERNAL       : 1;
  __REG32                 :27;
} __dfsr_bits;

/* Software Trigger Interrupt Register */
typedef struct {
  __REG32  INTID          : 9;
  __REG32                 :23;
} __stir_bits;

/* Debug Halting Control and Status Register */
typedef union {
  /* DHSR */
  struct {
    __REG32  C_DEBUGEN    : 1;
    __REG32  C_HALT       : 1;
    __REG32  C_STEP       : 1;
    __REG32  C_MASKINTS   : 1;
    __REG32               : 1;
    __REG32  C_SNAPSTALL  : 1;
    __REG32               :10;
    __REG32  S_REGRDY     : 1;
    __REG32  S_HALT       : 1;
    __REG32  S_SLEEP      : 1;
    __REG32  S_LOCKUP     : 1;
    __REG32               : 4;
    __REG32  S_RETIRE_ST  : 1;
    __REG32  S_RESET_ST   : 1;
    __REG32               : 6;
  };
  /* DHCR */
  struct {
    __REG32               :16;
    __REG32  DBGKEY       :16;
  };
} __dhsr_bits;

/* Debug Core Selector Register */
typedef struct {
  __REG32  REGSEL         : 5;
  __REG32                 :11;
  __REG32  REGWnR         : 1;
  __REG32                 :15;
} __dcrsr_bits;

/* Debug Exception and Monitor Control Register */
typedef struct {
  __REG32  VC_CORERESET   : 1;
  __REG32                 : 3;
  __REG32  VC_MMERR       : 1;
  __REG32  VC_NOCPERR     : 1;
  __REG32  VC_CHKERR      : 1;
  __REG32  VC_STATERR     : 1;
  __REG32  VC_BUSERR      : 1;
  __REG32  VC_INTERR      : 1;
  __REG32  VC_HARDERR     : 1;
  __REG32                 : 5;
  __REG32  MON_EN         : 1;
  __REG32  MON_PEND       : 1;
  __REG32  MON_STEP       : 1;
  __REG32  MON_REQ        : 1;
  __REG32                 : 4;
  __REG32  TRCENA         : 1;
  __REG32                 : 7;
} __demcr_bits;

/* Flash Patch Control Register */
typedef struct {
  __REG32  ENABLE         : 1;
  __REG32  KEY            : 1;
  __REG32                 : 2;
  __REG32  NUM_CODE       : 4;
  __REG32  NUM_LIT        : 4;
  __REG32                 :20;
} __fp_ctrl_bits;

/* Flash Patch Remap Register */
typedef struct {
  __REG32                 : 5;
  __REG32  REMAP          :24;
  __REG32                 : 3;
} __fp_remap_bits;

/* Flash Patch Comparator Registers */
typedef struct {
  __REG32  ENABLE         : 1;
  __REG32                 : 1;
  __REG32  REMAP          :27;
  __REG32                 : 1;
  __REG32  REPLACE        : 2;
} __fp_comp_bits;

/* DWT Control Register */
typedef struct {
  __REG32  CYCCNTENA      : 1;
  __REG32  POSTPRESET     : 4;
  __REG32  POSTCNT        : 4;
  __REG32  CYCTAP         : 1;
  __REG32  SYNCTAP        : 2;
  __REG32  PCSAMPLEENA    : 1;
  __REG32                 : 3;
  __REG32  EXCTRCENA      : 1;
  __REG32  CPIEVTENA      : 1;
  __REG32  EXCEVTENA      : 1;
  __REG32  SLEEPEVTENA    : 1;
  __REG32  LSUEVTENA      : 1;
  __REG32  FOLDEVTENA     : 1;
  __REG32  CYCEVTEN       : 1;
  __REG32                 : 5;
  __REG32  NUMCOMP        : 4;
} __dwt_ctrl_bits;

/* DWT Mask Registers */
typedef struct {
  __REG32  MASK           : 4;
  __REG32                 :28;
} __dwt_mask_bits;

/* DWT Function Registers */
typedef struct {
  __REG32  FUNCTION       : 4;
  __REG32                 : 1;
  __REG32  EMITRANGE      : 1;
  __REG32                 : 1;
  __REG32  CYCMATCH       : 1;
  __REG32                 :24;
} __dwt_function_bits;

/* ITM Trace Enable Register */
typedef struct {
  __REG32  STIMULUS_MASK0 : 1;
  __REG32  STIMULUS_MASK1 : 1;
  __REG32  STIMULUS_MASK2 : 1;
  __REG32  STIMULUS_MASK3 : 1;
  __REG32  STIMULUS_MASK4 : 1;
  __REG32  STIMULUS_MASK5 : 1;
  __REG32  STIMULUS_MASK6 : 1;
  __REG32  STIMULUS_MASK7 : 1;
  __REG32  STIMULUS_MASK8 : 1;
  __REG32  STIMULUS_MASK9 : 1;
  __REG32  STIMULUS_MASK10: 1;
  __REG32  STIMULUS_MASK11: 1;
  __REG32  STIMULUS_MASK12: 1;
  __REG32  STIMULUS_MASK13: 1;
  __REG32  STIMULUS_MASK14: 1;
  __REG32  STIMULUS_MASK15: 1;
  __REG32  STIMULUS_MASK16: 1;
  __REG32  STIMULUS_MASK17: 1;
  __REG32  STIMULUS_MASK18: 1;
  __REG32  STIMULUS_MASK19: 1;
  __REG32  STIMULUS_MASK20: 1;
  __REG32  STIMULUS_MASK21: 1;
  __REG32  STIMULUS_MASK22: 1;
  __REG32  STIMULUS_MASK23: 1;
  __REG32  STIMULUS_MASK24: 1;
  __REG32  STIMULUS_MASK25: 1;
  __REG32  STIMULUS_MASK26: 1;
  __REG32  STIMULUS_MASK27: 1;
  __REG32  STIMULUS_MASK28: 1;
  __REG32  STIMULUS_MASK29: 1;
  __REG32  STIMULUS_MASK30: 1;
  __REG32  STIMULUS_MASK31: 1;
} __itm_te_bits;

/* ITM Trace Privilege Register */
typedef struct {
  __REG32  PRIVILEGE_MASK : 4;
  __REG32                 :28;
} __itm_tp_bits;

/* ITM Control Register */
typedef struct {
  __REG32  ITMEN          : 1;
  __REG32  TSENA          : 1;
  __REG32  SYNCEN         : 1;
  __REG32  DWTEN          : 1;
  __REG32                 : 4;
  __REG32  TSPRESCALE     : 2;
  __REG32                 : 6;
  __REG32  ATBID          : 7;
  __REG32                 : 9;
} __itm_cr_bits;

/* ITM Integration Write Register */
typedef struct {
  __REG32  ATVALIDM       : 1;
  __REG32                 :31;
} __itm_iw_bits;

/* ITM Integration Read Register */
typedef struct {
  __REG32  ATREADYM       : 1;
  __REG32                 :31;
} __itm_ir_bits;

/* ITM Integration Mode Control Register */
typedef struct {
  __REG32  INTEGRATION    : 1;
  __REG32                 :31;
} __itm_imc_bits;

/* ITM Lock Status Register */
typedef struct {
  __REG32  PRESENT        : 1;
  __REG32  ACCESS         : 1;
  __REG32  BYTEACC        : 1;
  __REG32                 :29;
} __itm_lsr_bits;

/* Supported Port Sizes Register / Current */
typedef struct {
  __REG32  MAXPORTSIZE1   : 1;
  __REG32  MAXPORTSIZE2   : 1;
  __REG32  MAXPORTSIZE3   : 1;
  __REG32  MAXPORTSIZE4   : 1;
  __REG32                 :28;
} __tpiu_spsr_bits;

/* Current Output Speed Divisors Register */
typedef struct {
  __REG32  PRESCALER      :13;
  __REG32                 :19;
} __tpiu_cosdr_bits;

/* Selected Pin Protocol Register */
typedef struct {
  __REG32  PROTOCOL       : 2;
  __REG32                 :30;
} __tpiu_sppr_bits;

/* Formatter and Flush Status Register */
typedef struct {
  __REG32  FL_IN_PROG     : 1;
  __REG32  FT_STOPPED     : 1;
  __REG32  TC_PRESENT     : 1;
  __REG32  FT_NON_STOP    : 1;
  __REG32                 :28;
} __tpiu_ffsr_bits;

/* Integration Test Register-ITATBCTR2 */
typedef struct {
  __REG32  ATREADY1_2     : 1;
  __REG32                 :31;
} __tpiu_itatbctr2_bits;

/* Integration Test Register-ITATBCTR0 */
typedef struct {
  __REG32  ATVALID1_2     : 1;
  __REG32                 :31;
} __tpiu_itatbctr0_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/
/***************************************************************************
 **
 ** Device Identification
 **
 ***************************************************************************/
__IO_REG32_BIT(DID0,              0x400FE000,__READ       ,__did0_bits);
__IO_REG32_BIT(DID1,              0x400FE004,__READ       ,__did1_bits);
__IO_REG32_BIT(DC0,               0x400FE008,__READ       ,__dc0_bits);
__IO_REG32_BIT(DC1,               0x400FE010,__READ       ,__dc1_bits);
__IO_REG32_BIT(DC2,               0x400FE014,__READ       ,__dc2_bits);
__IO_REG32_BIT(DC3,               0x400FE018,__READ       ,__dc3_bits);
__IO_REG32_BIT(DC4,               0x400FE01C,__READ       ,__dc4_bits);

/***************************************************************************
 **
 ** Local Control
 **
 ***************************************************************************/
__IO_REG32_BIT(PBORCTL,           0x400FE030,__READ_WRITE ,__pborctl_bits);
__IO_REG32_BIT(LDOPCTL,           0x400FE034,__READ_WRITE ,__ldopctl_bits);
__IO_REG32_BIT(SRCR0,             0x400FE040,__READ_WRITE ,__srcr0_bits);
__IO_REG32_BIT(SRCR1,             0x400FE044,__READ_WRITE ,__srcr1_bits);
__IO_REG32_BIT(SRCR2,             0x400FE048,__READ_WRITE ,__srcr2_bits);
__IO_REG32_BIT(RIS,               0x400FE050,__READ       ,__ris_bits);
__IO_REG32_BIT(IMC,               0x400FE054,__READ_WRITE ,__imc_bits);
__IO_REG32_BIT(MISC,              0x400FE058,__READ_WRITE ,__misc_bits);
__IO_REG32_BIT(RESC,              0x400FE05C,__READ_WRITE ,__resc_bits);
__IO_REG32_BIT(RCC,               0x400FE060,__READ_WRITE ,__rcc_bits);
__IO_REG32_BIT(PLLCFG,            0x400FE064,__READ       ,__pllcfg_bits);

/***************************************************************************
 **
 ** System Control
 **
 ***************************************************************************/
__IO_REG32_BIT(RCGC0,             0x400FE100,__READ_WRITE ,__rcgc0_bits);
__IO_REG32_BIT(RCGC1,             0x400FE104,__READ_WRITE ,__rcgc1_bits);
__IO_REG32_BIT(RCGC2,             0x400FE108,__READ_WRITE ,__rcgc2_bits);
__IO_REG32_BIT(SCGC0,             0x400FE110,__READ_WRITE ,__rcgc0_bits);
__IO_REG32_BIT(SCGC1,             0x400FE114,__READ_WRITE ,__rcgc1_bits);
__IO_REG32_BIT(SCGC2,             0x400FE118,__READ_WRITE ,__rcgc2_bits);
__IO_REG32_BIT(DCGC0,             0x400FE120,__READ_WRITE ,__rcgc0_bits);
__IO_REG32_BIT(DCGC1,             0x400FE124,__READ_WRITE ,__rcgc1_bits);
__IO_REG32_BIT(DCGC2,             0x400FE128,__READ_WRITE ,__rcgc2_bits);
__IO_REG32_BIT(CLKVCLR,           0x400FE150,__READ_WRITE ,__clkvclr_bits);
__IO_REG32_BIT(LDOARST,           0x400FE160,__READ_WRITE ,__ldoarst_bits);

/***************************************************************************
 **
 ** Flash
 **
 ***************************************************************************/
__IO_REG32_BIT(FMPRE,             0x400FE130,__READ_WRITE ,__fmpre_bits);
__IO_REG32_BIT(FMPPE,             0x400FE134,__READ_WRITE ,__fmpre_bits);
__IO_REG8(     USECRL,            0x400FE140,__READ_WRITE);
__IO_REG32_BIT(FMA,               0x400FD000,__READ_WRITE ,__fma_bits);
__IO_REG32(    FMD,               0x400FD004,__READ_WRITE);
__IO_REG32_BIT(FMC,               0x400FD008,__READ_WRITE ,__fmc_bits);
__IO_REG32_BIT(FCRIS,             0x400FD00C,__READ       ,__fcris_bits);
__IO_REG32_BIT(FCIM,              0x400FD010,__READ_WRITE ,__fcim_bits);
__IO_REG32_BIT(FCMISC,            0x400FD014,__READ_WRITE ,__fcmisc_bits);

/***************************************************************************
 **
 ** GPIOA
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIOADATAMASK,     0x40004000,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOADATA,         0x400043FC,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOADIR,          0x40004400,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOAIS,           0x40004404,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOAIBE,          0x40004408,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOAIEV,          0x4000440C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOAIM,           0x40004410,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOARIS,          0x40004414,__READ			  ,__gpio_bits);
__IO_REG32_BIT(GPIOAMIS,          0x40004418,__READ			  ,__gpio_bits);
__IO_REG32_BIT(GPIOAICR,          0x4000441C,__WRITE 			,__gpio_bits);
__IO_REG32_BIT(GPIOAAFSEL,        0x40004420,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOADR2R,         0x40004500,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOADR4R,         0x40004504,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOADR8R,         0x40004508,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOAODR,          0x4000450C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOAPUR,          0x40004510,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOAPDR,          0x40004514,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOASLR,          0x40004518,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOADEN,          0x4000451C,__READ_WRITE ,__gpio_bits);
__IO_REG8(     GPIOAPERIPHID4,    0x40004FD0,__READ);
__IO_REG8(     GPIOAPERIPHID5,    0x40004FD4,__READ);
__IO_REG8(     GPIOAPERIPHID6,    0x40004FD8,__READ);
__IO_REG8(     GPIOAPERIPHID7,    0x40004FDC,__READ);
__IO_REG8(     GPIOAPERIPHID0,    0x40004FE0,__READ);
__IO_REG8(     GPIOAPERIPHID1,    0x40004FE4,__READ);
__IO_REG8(     GPIOAPERIPHID2,    0x40004FE8,__READ);
__IO_REG8(     GPIOAPERIPHID3,    0x40004FEC,__READ);
__IO_REG8(     GPIOAPCELLID0,     0x40004FF0,__READ);
__IO_REG8(     GPIOAPCELLID1,     0x40004FF4,__READ);
__IO_REG8(     GPIOAPCELLID2,     0x40004FF8,__READ);
__IO_REG8(     GPIOAPCELLID3,     0x40004FFC,__READ);

/***************************************************************************
 **
 ** GPIOB
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIOBDATAMASK,     0x40005000,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBDATA,         0x400053FC,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBDIR,          0x40005400,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBIS,           0x40005404,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBIBE,          0x40005408,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBIEV,          0x4000540C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBIM,           0x40005410,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBRIS,          0x40005414,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIOBMIS,          0x40005418,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIOBICR,          0x4000541C,__WRITE 			,__gpio_bits);
__IO_REG32_BIT(GPIOBAFSEL,        0x40005420,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBDR2R,         0x40005500,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBDR4R,         0x40005504,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBDR8R,         0x40005508,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBODR,          0x4000550C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBPUR,          0x40005510,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBPDR,          0x40005514,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBSLR,          0x40005518,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOBDEN,          0x4000551C,__READ_WRITE ,__gpio_bits);
__IO_REG8(     GPIOBPERIPHID4,    0x40005FD0,__READ);
__IO_REG8(     GPIOBPERIPHID5,    0x40005FD4,__READ);
__IO_REG8(     GPIOBPERIPHID6,    0x40005FD8,__READ);
__IO_REG8(     GPIOBPERIPHID7,    0x40005FDC,__READ);
__IO_REG8(     GPIOBPERIPHID0,    0x40005FE0,__READ);
__IO_REG8(     GPIOBPERIPHID1,    0x40005FE4,__READ);
__IO_REG8(     GPIOBPERIPHID2,    0x40005FE8,__READ);
__IO_REG8(     GPIOBPERIPHID3,    0x40005FEC,__READ);
__IO_REG8(     GPIOBPCELLID0,     0x40005FF0,__READ);
__IO_REG8(     GPIOBPCELLID1,     0x40005FF4,__READ);
__IO_REG8(     GPIOBPCELLID2,     0x40005FF8,__READ);
__IO_REG8(     GPIOBPCELLID3,     0x40005FFC,__READ);

/***************************************************************************
 **
 ** GPIOC
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIOCDATAMASK,     0x40006000,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCDATA,         0x400063FC,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCDIR,          0x40006400,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCIS,           0x40006404,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCIBE,          0x40006408,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCIEV,          0x4000640C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCIM,           0x40006410,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCRIS,          0x40006414,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIOCMIS,          0x40006418,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIOCICR,          0x4000641C,__WRITE 			,__gpio_bits);
__IO_REG32_BIT(GPIOCAFSEL,        0x40006420,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCDR2R,         0x40006500,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCDR4R,         0x40006504,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCDR8R,         0x40006508,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCODR,          0x4000650C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCPUR,          0x40006510,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCPDR,          0x40006514,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCSLR,          0x40006518,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOCDEN,          0x4000651C,__READ_WRITE ,__gpio_bits);
__IO_REG8(     GPIOCPERIPHID4,    0x40006FD0,__READ);
__IO_REG8(     GPIOCPERIPHID5,    0x40006FD4,__READ);
__IO_REG8(     GPIOCPERIPHID6,    0x40006FD8,__READ);
__IO_REG8(     GPIOCPERIPHID7,    0x40006FDC,__READ);
__IO_REG8(     GPIOCPERIPHID0,    0x40006FE0,__READ);
__IO_REG8(     GPIOCPERIPHID1,    0x40006FE4,__READ);
__IO_REG8(     GPIOCPERIPHID2,    0x40006FE8,__READ);
__IO_REG8(     GPIOCPERIPHID3,    0x40006FEC,__READ);
__IO_REG8(     GPIOCPCELLID0,     0x40006FF0,__READ);
__IO_REG8(     GPIOCPCELLID1,     0x40006FF4,__READ);
__IO_REG8(     GPIOCPCELLID2,     0x40006FF8,__READ);
__IO_REG8(     GPIOCPCELLID3,     0x40006FFC,__READ);

/***************************************************************************
 **
 ** GPIOD
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIODDATAMASK,     0x40007000,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODDATA,         0x400073FC,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODDIR,          0x40007400,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODIS,           0x40007404,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODIBE,          0x40007408,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODIEV,          0x4000740C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODIM,           0x40007410,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODRIS,          0x40007414,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIODMIS,          0x40007418,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIODICR,          0x4000741C,__WRITE 			,__gpio_bits);
__IO_REG32_BIT(GPIODAFSEL,        0x40007420,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODDR2R,         0x40007500,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODDR4R,         0x40007504,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODDR8R,         0x40007508,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODODR,          0x4000750C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODPUR,          0x40007510,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODPDR,          0x40007514,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODSLR,          0x40007518,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIODDEN,          0x4000751C,__READ_WRITE ,__gpio_bits);
__IO_REG8(     GPIODPERIPHID4,    0x40007FD0,__READ);
__IO_REG8(     GPIODPERIPHID5,    0x40007FD4,__READ);
__IO_REG8(     GPIODPERIPHID6,    0x40007FD8,__READ);
__IO_REG8(     GPIODPERIPHID7,    0x40007FDC,__READ);
__IO_REG8(     GPIODPERIPHID0,    0x40007FE0,__READ);
__IO_REG8(     GPIODPERIPHID1,    0x40007FE4,__READ);
__IO_REG8(     GPIODPERIPHID2,    0x40007FE8,__READ);
__IO_REG8(     GPIODPERIPHID3,    0x40007FEC,__READ);
__IO_REG8(     GPIODPCELLID0,     0x40007FF0,__READ);
__IO_REG8(     GPIODPCELLID1,     0x40007FF4,__READ);
__IO_REG8(     GPIODPCELLID2,     0x40007FF8,__READ);
__IO_REG8(     GPIODPCELLID3,     0x40007FFC,__READ);

/***************************************************************************
 **
 ** GPIOE
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIOEDATAMASK,     0x40024000,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEDATA,         0x400243FC,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEDIR,          0x40024400,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEIS,           0x40024404,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEIBE,          0x40024408,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEIEV,          0x4002440C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEIM,           0x40024410,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOERIS,          0x40024414,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIOEMIS,          0x40024418,__READ				,__gpio_bits);
__IO_REG32_BIT(GPIOEICR,          0x4002441C,__WRITE 			,__gpio_bits);
__IO_REG32_BIT(GPIOEAFSEL,        0x40024420,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEDR2R,         0x40024500,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEDR4R,         0x40024504,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEDR8R,         0x40024508,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEODR,          0x4002450C,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEPUR,          0x40024510,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEPDR,          0x40024514,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOESLR,          0x40024518,__READ_WRITE ,__gpio_bits);
__IO_REG32_BIT(GPIOEDEN,          0x4002451C,__READ_WRITE ,__gpio_bits);
__IO_REG8(     GPIOEPERIPHID4,    0x40024FD0,__READ);
__IO_REG8(     GPIOEPERIPHID5,    0x40024FD4,__READ);
__IO_REG8(     GPIOEPERIPHID6,    0x40024FD8,__READ);
__IO_REG8(     GPIOEPERIPHID7,    0x40024FDC,__READ);
__IO_REG8(     GPIOEPERIPHID0,    0x40024FE0,__READ);
__IO_REG8(     GPIOEPERIPHID1,    0x40024FE4,__READ);
__IO_REG8(     GPIOEPERIPHID2,    0x40024FE8,__READ);
__IO_REG8(     GPIOEPERIPHID3,    0x40024FEC,__READ);
__IO_REG8(     GPIOEPCELLID0,     0x40024FF0,__READ);
__IO_REG8(     GPIOEPCELLID1,     0x40024FF4,__READ);
__IO_REG8(     GPIOEPCELLID2,     0x40024FF8,__READ);
__IO_REG8(     GPIOEPCELLID3,     0x40024FFC,__READ);

/***************************************************************************
 **
 ** TIMER0
 **
 ***************************************************************************/
__IO_REG32_BIT(GPTM0CFG,          0x40030000,__READ_WRITE ,__gptmcfg_bits);
__IO_REG32_BIT(GPTM0TAMR,         0x40030004,__READ_WRITE ,__gptmtamr_bits);
__IO_REG32_BIT(GPTM0TBMR,         0x40030008,__READ_WRITE ,__gptmtbmr_bits);
__IO_REG32_BIT(GPTM0CTL,          0x4003000C,__READ_WRITE ,__gptmctl_bits);
__IO_REG32_BIT(GPTM0IMR,          0x40030018,__READ_WRITE ,__gptmimr_bits);
__IO_REG32_BIT(GPTM0RIS,          0x4003001C,__READ       ,__gptmris_bits);
__IO_REG32_BIT(GPTM0MIS,          0x40030020,__READ       ,__gptmmis_bits);
__IO_REG32_BIT(GPTM0ICR,          0x40030024,__WRITE 			,__gptmicr_bits);
__IO_REG32_BIT(GPTM0TAILR,        0x40030028,__READ_WRITE ,__gptmtailr_bits);
__IO_REG16(    GPTM0TBILR,        0x4003002C,__READ_WRITE);
__IO_REG32_BIT(GPTM0TAMATCHR,     0x40030030,__READ_WRITE ,__gptmtamatchr_bits);
__IO_REG16(    GPTM0TBMATCHR,     0x40030034,__READ_WRITE);
__IO_REG8(     GPTM0TAPR,         0x40030038,__READ_WRITE);
__IO_REG8(     GPTM0TBPR,         0x4003003C,__READ_WRITE);
__IO_REG8(     GPTM0TAPMR,        0x40030040,__READ_WRITE);
__IO_REG8(     GPTM0TBPMR,        0x40030044,__READ_WRITE);
__IO_REG32_BIT(GPTM0TAR,          0x40030048,__READ       ,__gptmtar_bits);
__IO_REG16(    GPTM0TBR,          0x4003004C,__READ);

/***************************************************************************
 **
 ** TIMER1
 **
 ***************************************************************************/
__IO_REG32_BIT(GPTM1CFG,          0x40031000,__READ_WRITE ,__gptmcfg_bits);
__IO_REG32_BIT(GPTM1TAMR,         0x40031004,__READ_WRITE ,__gptmtamr_bits);
__IO_REG32_BIT(GPTM1TBMR,         0x40031008,__READ_WRITE ,__gptmtbmr_bits);
__IO_REG32_BIT(GPTM1CTL,          0x4003100C,__READ_WRITE ,__gptmctl_bits);
__IO_REG32_BIT(GPTM1IMR,          0x40031018,__READ_WRITE ,__gptmimr_bits);
__IO_REG32_BIT(GPTM1RIS,          0x4003101C,__READ       ,__gptmris_bits);
__IO_REG32_BIT(GPTM1MIS,          0x40031020,__READ       ,__gptmmis_bits);
__IO_REG32_BIT(GPTM1ICR,          0x40031024,__WRITE 			,__gptmicr_bits);
__IO_REG32_BIT(GPTM1TAILR,        0x40031028,__READ_WRITE ,__gptmtailr_bits);
__IO_REG16(    GPTM1TBILR,        0x4003102C,__READ_WRITE);
__IO_REG32_BIT(GPTM1TAMATCHR,     0x40031030,__READ_WRITE ,__gptmtamatchr_bits);
__IO_REG16(    GPTM1TBMATCHR,     0x40031034,__READ_WRITE);
__IO_REG8(     GPTM1TAPR,         0x40031038,__READ_WRITE);
__IO_REG8(     GPTM1TBPR,         0x4003103C,__READ_WRITE);
__IO_REG8(     GPTM1TAPMR,        0x40031040,__READ_WRITE);
__IO_REG8(     GPTM1TBPMR,        0x40031044,__READ_WRITE);
__IO_REG32_BIT(GPTM1TAR,          0x40031048,__READ       ,__gptmtar_bits);
__IO_REG16(    GPTM1TBR,          0x4003104C,__READ);

/***************************************************************************
 **
 ** TIMER2
 **
 ***************************************************************************/
__IO_REG32_BIT(GPTM2CFG,          0x40032000,__READ_WRITE ,__gptmcfg_bits);
__IO_REG32_BIT(GPTM2TAMR,         0x40032004,__READ_WRITE ,__gptmtamr_bits);
__IO_REG32_BIT(GPTM2TBMR,         0x40032008,__READ_WRITE ,__gptmtbmr_bits);
__IO_REG32_BIT(GPTM2CTL,          0x4003200C,__READ_WRITE ,__gptmctl_bits);
__IO_REG32_BIT(GPTM2IMR,          0x40032018,__READ_WRITE ,__gptmimr_bits);
__IO_REG32_BIT(GPTM2RIS,          0x4003201C,__READ       ,__gptmris_bits);
__IO_REG32_BIT(GPTM2MIS,          0x40032020,__READ       ,__gptmmis_bits);
__IO_REG32_BIT(GPTM2ICR,          0x40032024,__WRITE 			,__gptmicr_bits);
__IO_REG32_BIT(GPTM2TAILR,        0x40032028,__READ_WRITE ,__gptmtailr_bits);
__IO_REG16(    GPTM2TBILR,        0x4003202C,__READ_WRITE);
__IO_REG32_BIT(GPTM2TAMATCHR,     0x40032030,__READ_WRITE ,__gptmtamatchr_bits);
__IO_REG16(    GPTM2TBMATCHR,     0x40032034,__READ_WRITE);
__IO_REG8(     GPTM2TAPR,         0x40032038,__READ_WRITE);
__IO_REG8(     GPTM2TBPR,         0x4003203C,__READ_WRITE);
__IO_REG8(     GPTM2TAPMR,        0x40032040,__READ_WRITE);
__IO_REG8(     GPTM2TBPMR,        0x40032044,__READ_WRITE);
__IO_REG32_BIT(GPTM2TAR,          0x40032048,__READ       ,__gptmtar_bits);
__IO_REG16(    GPTM2TBR,          0x4003204C,__READ);

/***************************************************************************
 **
 ** ADC
 **
 ***************************************************************************/
__IO_REG32_BIT(ADCACTSS,          0x40038000,__READ_WRITE ,__adcactss_bits);
__IO_REG32_BIT(ADCRIS,            0x40038004,__READ       ,__adcris_bits);
__IO_REG32_BIT(ADCIM,             0x40038008,__READ_WRITE ,__adcim_bits);
__IO_REG32_BIT(ADCISC,            0x4003800C,__READ_WRITE ,__adcisc_bits);
__IO_REG32_BIT(ADCOSTAT,          0x40038010,__READ_WRITE ,__adcostat_bits);
__IO_REG32_BIT(ADCEMUX,           0x40038014,__READ_WRITE ,__adcemux_bits);
__IO_REG32_BIT(ADCUSTAT,          0x40038018,__READ_WRITE ,__adcustat_bits);
__IO_REG32_BIT(ADCSSPRI,          0x40038020,__READ_WRITE ,__adcsspri_bits);
__IO_REG32_BIT(ADCPSSI,           0x40038028,__WRITE      ,__adcpssi_bits);
__IO_REG32_BIT(ADCSSMUX0,         0x40038040,__READ_WRITE ,__adcssmux0_bits);
__IO_REG32_BIT(ADCSSCTL0,         0x40038044,__READ_WRITE ,__adcssctl0_bits);
__IO_REG32_BIT(ADCSSFIFO0,        0x40038048,__READ       ,__adcssfifo0_bits);
__IO_REG32_BIT(ADCSSFSTAT0,       0x4003804C,__READ       ,__adcssfstat0_bits);
__IO_REG32_BIT(ADCSSMUX1,         0x40038060,__READ_WRITE ,__adcssmux1_bits);
__IO_REG32_BIT(ADCSSCTL1,         0x40038064,__READ_WRITE ,__adcssctl1_bits);
__IO_REG32_BIT(ADCSSFIFO1,        0x40038068,__READ       ,__adcssfifo1_bits);
__IO_REG32_BIT(ADCSSFSTAT1,       0x4003806C,__READ       ,__adcssfstat1_bits);
__IO_REG32_BIT(ADCSSMUX2,         0x40038080,__READ_WRITE ,__adcssmux2_bits);
__IO_REG32_BIT(ADCSSCTL2,         0x40038084,__READ_WRITE ,__adcssctl2_bits);
__IO_REG32_BIT(ADCSSFIFO2,        0x40038088,__READ       ,__adcssfifo2_bits);
__IO_REG32_BIT(ADCSSFSTAT2,       0x4003808C,__READ       ,__adcssfstat2_bits);
__IO_REG32_BIT(ADCSSMUX3,         0x400380A0,__READ_WRITE ,__adcssmux3_bits);
__IO_REG32_BIT(ADCSSCTL3,         0x400380A4,__READ_WRITE ,__adcssctl3_bits);
__IO_REG32_BIT(ADCSSFIFO3,        0x400380A8,__READ       ,__adcssfifo3_bits);
__IO_REG32_BIT(ADCSSFSTAT3,       0x400380AC,__READ       ,__adcssfstat3_bits);

/***************************************************************************
 **
 ** WDT
 **
 ***************************************************************************/
__IO_REG32(    WDTLOAD,           0x40000000,__READ_WRITE);
__IO_REG32(    WDTVALUE,          0x40000004,__READ);
__IO_REG32_BIT(WDTCTL,            0x40000008,__READ_WRITE ,__wdtctl_bits);
__IO_REG32(    WDTICR,            0x4000000C,__WRITE);
__IO_REG32_BIT(WDTRIS,            0x40000010,__READ       ,__wdtris_bits);
__IO_REG32_BIT(WDTMIS,            0x40000014,__READ       ,__wdtmis_bits);
__IO_REG32(    WDTLOCK,           0x40000C00,__READ_WRITE);
__IO_REG8(     WDTPERIPHID4,      0x40000FD0,__READ);
__IO_REG8(     WDTPERIPHID5,      0x40000FD4,__READ);
__IO_REG8(     WDTPERIPHID6,      0x40000FD8,__READ);
__IO_REG8(     WDTPERIPHID7,      0x40000FDC,__READ);
__IO_REG8(     WDTPERIPHID0,      0x40000FE0,__READ);
__IO_REG8(     WDTPERIPHID1,      0x40000FE4,__READ);
__IO_REG8(     WDTPERIPHID2,      0x40000FE8,__READ);
__IO_REG8(     WDTPERIPHID3,      0x40000FEC,__READ);
__IO_REG8(     WDTPCELLID0,       0x40000FF0,__READ);
__IO_REG8(     WDTPCELLID1,       0x40000FF4,__READ);
__IO_REG8(     WDTPCELLID2,       0x40000FF8,__READ);
__IO_REG8(     WDTPCELLID3,       0x40000FFC,__READ);

/***************************************************************************
 **
 ** UART 0
 **
 ***************************************************************************/
__IO_REG32_BIT(UART0DR,            0x4000C000,__READ_WRITE ,__uartdr_bits);
__IO_REG32_BIT(UART0RSR,           0x4000C004,__READ_WRITE ,__uartrsr_bits);
#define UART0ECR         UART0RSR
#define UART0ECR_bit     UART0RSR_bit
__IO_REG32_BIT(UART0FR,            0x4000C018,__READ       ,__uartfr_bits);
__IO_REG16(    UART0IBRD,          0x4000C024,__READ_WRITE);
__IO_REG32_BIT(UART0FBRD,          0x4000C028,__READ_WRITE ,__uartfbrd_bits);
__IO_REG32_BIT(UART0LCRH,          0x4000C02C,__READ_WRITE ,__uartlcrh_bits);
__IO_REG32_BIT(UART0CTL,           0x4000C030,__READ_WRITE ,__uartctl_bits);
__IO_REG32_BIT(UART0IFLS,          0x4000C034,__READ_WRITE ,__uartifls_bits);
__IO_REG32_BIT(UART0IM,            0x4000C038,__READ_WRITE ,__uartim_bits);
__IO_REG32_BIT(UART0RIS,           0x4000C03C,__READ       ,__uartris_bits);
__IO_REG32_BIT(UART0MIS,           0x4000C040,__READ       ,__uartmis_bits);
__IO_REG32_BIT(UART0ICR,           0x4000C044,__WRITE 			,__uarticr_bits);
__IO_REG8(     UART0PERIPHID4,     0x4000CFD0,__READ);
__IO_REG8(     UART0PERIPHID5,     0x4000CFD4,__READ);
__IO_REG8(     UART0PERIPHID6,     0x4000CFD8,__READ);
__IO_REG8(     UART0PERIPHID7,     0x4000CFDC,__READ);
__IO_REG8(     UART0PERIPHID0,     0x4000CFE0,__READ);
__IO_REG8(     UART0PERIPHID1,     0x4000CFE4,__READ);
__IO_REG8(     UART0PERIPHID2,     0x4000CFE8,__READ);
__IO_REG8(     UART0PERIPHID3,     0x4000CFEC,__READ);
__IO_REG8(     UART0PCELLID0,      0x4000CFF0,__READ);
__IO_REG8(     UART0PCELLID1,      0x4000CFF4,__READ);
__IO_REG8(     UART0PCELLID2,      0x4000CFF8,__READ);
__IO_REG8(     UART0PCELLID3,      0x4000CFFC,__READ);

/***************************************************************************
 **
 ** UART 1
 **
 ***************************************************************************/
__IO_REG32_BIT(UART1DR,            0x4000D000,__READ_WRITE ,__uartdr_bits);
__IO_REG32_BIT(UART1RSR,           0x4000D004,__READ_WRITE ,__uartrsr_bits);
#define UART1ECR         UART1RSR
#define UART1ECR_bit     UART1RSR_bit
__IO_REG32_BIT(UART1FR,            0x4000D018,__READ       ,__uartfr_bits);
__IO_REG16(    UART1IBRD,          0x4000D024,__READ_WRITE);
__IO_REG32_BIT(UART1FBRD,          0x4000D028,__READ_WRITE ,__uartfbrd_bits);
__IO_REG32_BIT(UART1LCRH,          0x4000D02C,__READ_WRITE ,__uartlcrh_bits);
__IO_REG32_BIT(UART1CTL,           0x4000D030,__READ_WRITE ,__uartctl_bits);
__IO_REG32_BIT(UART1IFLS,          0x4000D034,__READ_WRITE ,__uartifls_bits);
__IO_REG32_BIT(UART1IM,            0x4000D038,__READ_WRITE ,__uartim_bits);
__IO_REG32_BIT(UART1RIS,           0x4000D03C,__READ       ,__uartris_bits);
__IO_REG32_BIT(UART1MIS,           0x4000D040,__READ       ,__uartmis_bits);
__IO_REG32_BIT(UART1ICR,           0x4000D044,__WRITE 			,__uarticr_bits);
__IO_REG8(     UART1PERIPHID4,     0x4000DFD0,__READ);
__IO_REG8(     UART1PERIPHID5,     0x4000DFD4,__READ);
__IO_REG8(     UART1PERIPHID6,     0x4000DFD8,__READ);
__IO_REG8(     UART1PERIPHID7,     0x4000DFDC,__READ);
__IO_REG8(     UART1PERIPHID0,     0x4000DFE0,__READ);
__IO_REG8(     UART1PERIPHID1,     0x4000DFE4,__READ);
__IO_REG8(     UART1PERIPHID2,     0x4000DFE8,__READ);
__IO_REG8(     UART1PERIPHID3,     0x4000DFEC,__READ);
__IO_REG8(     UART1PCELLID0,      0x4000DFF0,__READ);
__IO_REG8(     UART1PCELLID1,      0x4000DFF4,__READ);
__IO_REG8(     UART1PCELLID2,      0x4000DFF8,__READ);
__IO_REG8(     UART1PCELLID3,      0x4000DFFC,__READ);

/***************************************************************************
 **
 ** SSI
 **
 ***************************************************************************/
__IO_REG32_BIT(SSICR0,            0x40008000,__READ_WRITE ,__ssicr0_bits);
__IO_REG32_BIT(SSICR1,            0x40008004,__READ_WRITE ,__ssicr1_bits);
__IO_REG16(    SSIDR,             0x40008008,__READ_WRITE);
__IO_REG32_BIT(SSISR,             0x4000800C,__READ       ,__ssisr_bits);
__IO_REG8(     SSICPSR,           0x40008010,__READ_WRITE);
__IO_REG32_BIT(SSIIM,             0x40008014,__READ_WRITE ,__ssiim_bits);
__IO_REG32_BIT(SSIRIS,            0x40008018,__READ       ,__ssiris_bits);
__IO_REG32_BIT(SSIMIS,            0x4000801C,__READ       ,__ssimis_bits);
__IO_REG32_BIT(SSIICR,            0x40008020,__WRITE 			,__ssiicr_bits);
__IO_REG8(     SSIPERIPHID4,      0x40008FD0,__READ);
__IO_REG8(     SSIPERIPHID5,      0x40008FD4,__READ);
__IO_REG8(     SSIPERIPHID6,      0x40008FD8,__READ);
__IO_REG8(     SSIPERIPHID7,      0x40008FDC,__READ);
__IO_REG8(     SSIPERIPHID0,      0x40008FE0,__READ);
__IO_REG8(     SSIPERIPHID1,      0x40008FE4,__READ);
__IO_REG8(     SSIPERIPHID2,      0x40008FE8,__READ);
__IO_REG8(     SSIPERIPHID3,      0x40008FEC,__READ);
__IO_REG8(     SSIPCELLID0,       0x40008FF0,__READ);
__IO_REG8(     SSIPCELLID1,       0x40008FF4,__READ);
__IO_REG8(     SSIPCELLID2,       0x40008FF8,__READ);
__IO_REG8(     SSIPCELLID3,       0x40008FFC,__READ);

/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(I2CMSA,            0x40020000,__READ_WRITE ,__i2cmsa_bits);
__IO_REG32_BIT(I2CMS,             0x40020004,__READ_WRITE ,__i2cmcs_bits);
#define I2CMC           I2CMS
#define I2CMC_bit       I2CMS_bit
__IO_REG8(     I2CMDR,            0x40020008,__READ_WRITE);
__IO_REG8(     I2CMTPR,           0x4002000C,__READ_WRITE);
__IO_REG32_BIT(I2CMIMR,           0x40020010,__READ_WRITE ,__i2cmimr_bits);
__IO_REG32_BIT(I2CMRIS,           0x40020014,__READ       ,__i2cmris_bits);
__IO_REG32_BIT(I2CMMIS,           0x40020018,__READ       ,__i2cmmis_bits);
__IO_REG32_BIT(I2CMICR,           0x4002001C,__WRITE      ,__i2cmicr_bits);
__IO_REG32_BIT(I2CMCR,            0x40020020,__READ_WRITE ,__i2cmcr_bits);
__IO_REG32_BIT(I2CSOAR,           0x40020800,__READ_WRITE ,__i2csoar_bits);
__IO_REG32_BIT(I2CSSR,            0x40020804,__READ_WRITE ,__i2cscsr_bits);
#define I2CSCR          I2CSSR
#define I2CSCR_bit      I2CSSR_bit
__IO_REG8(     I2CSDR,            0x40020808,__READ_WRITE);
__IO_REG32_BIT(I2CSIMR,           0x4002080C,__READ_WRITE ,__i2csimr_bits);
__IO_REG32_BIT(I2CSRIS,           0x40020810,__READ       ,__i2csris_bits);
__IO_REG32_BIT(I2CSMIS,           0x40020814,__READ       ,__i2csmis_bits);
__IO_REG32_BIT(I2CSICR,           0x40020818,__WRITE      ,__i2csicr_bits);

/***************************************************************************
 **
 ** Analog Comparators
 **
 ***************************************************************************/
__IO_REG32_BIT(ACMIS,             0x4003C000,__READ       ,__acmis_bits);
__IO_REG32_BIT(ACRIS,             0x4003C004,__READ       ,__acmis_bits);
__IO_REG32_BIT(ACINTEN,           0x4003C008,__READ_WRITE ,__acmis_bits);
__IO_REG32_BIT(ACREFCTL,          0x4003C010,__READ_WRITE ,__acrefctl_bits);
__IO_REG32_BIT(ACSTAT0,           0x4003C020,__READ       ,__acstat_bits);
__IO_REG32_BIT(ACCTL0,            0x4003C024,__READ_WRITE ,__acctl_bits);

/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(PWMCTL,            0x40028000,__READ_WRITE  ,__pwmctl_bits);
__IO_REG32_BIT(PWMSYNC,            0x40028004,__READ_WRITE  ,__pwmsync_bits);
__IO_REG32_BIT(PWMENABLE,         0x40028008,__READ_WRITE  ,__pwmenable_bits);
__IO_REG32_BIT(PWMINVERT,         0x4002800C,__READ_WRITE  ,__pwminvert_bits);
__IO_REG32_BIT(PWMFAULT,          0x40028010,__READ_WRITE  ,__pwmfault_bits);
__IO_REG32_BIT(PWMINTEN,          0x40028014,__READ_WRITE  ,__pwminten_bits);
__IO_REG32_BIT(PWMRIS,            0x40028018,__READ        ,__pwmris_bits);
__IO_REG32_BIT(PWMISC,            0x4002801C,__READ_WRITE  ,__pwmisc_bits);
__IO_REG32_BIT(PWMSTATUS,         0x40028020,__READ        ,__pwmstatus_bits);
__IO_REG32_BIT(PWM0CTL,           0x40028040,__READ_WRITE  ,__pwm0ctl_bits);
__IO_REG32_BIT(PWM0INTEN,         0x40028044,__READ_WRITE  ,__pwm0inten_bits);
__IO_REG32_BIT(PWM0RIS,           0x40028048,__READ        ,__pwm0ris_bits);
__IO_REG32_BIT(PWM0ISC,           0x4002804C,__READ_WRITE  ,__pwm0isc_bits);
__IO_REG32_BIT(PWM0LOAD,          0x40028050,__READ_WRITE  ,__pwm0load_bits);
__IO_REG32_BIT(PWM0COUNT,         0x40028054,__READ        ,__pwm0count_bits);
__IO_REG32_BIT(PWM0CMPA,          0x40028058,__READ_WRITE  ,__pwm0cmpa_bits);
__IO_REG32_BIT(PWM0CMPB,          0x4002805C,__READ_WRITE  ,__pwm0cmpb_bits);
__IO_REG32_BIT(PWM0GENA,          0x40028060,__READ_WRITE  ,__pwm0gena_bits);
__IO_REG32_BIT(PWM0GENB,          0x40028064,__READ_WRITE  ,__pwm0genb_bits);
__IO_REG32_BIT(PWM0DBCTL,         0x40028068,__READ_WRITE  ,__pwm0dbctl_bits);
__IO_REG32_BIT(PWM0DBRISE,        0x4002806C,__READ_WRITE  ,__pwm0dbrise_bits);
__IO_REG32_BIT(PWM0DBFALL,        0x40028070,__READ_WRITE  ,__pwm0dbfall_bits);

/***************************************************************************
 **
 ** NVIC
 **
 ***************************************************************************/
__IO_REG32_BIT(NVIC,              0xE000E004,__READ       ,__nvic_bits);
__IO_REG32_BIT(SYSTICKCSR,        0xE000E010,__READ_WRITE ,__systickcsr_bits);
__IO_REG32_BIT(SYSTICKRVR,        0xE000E014,__READ_WRITE ,__systickrvr_bits);
__IO_REG32_BIT(SYSTICKCVR,        0xE000E018,__READ_WRITE ,__systickcvr_bits);
__IO_REG32_BIT(SYSTICKCALVR,      0xE000E01C,__READ       ,__systickcalvr_bits);
__IO_REG32_BIT(SETENA0,           0xE000E100,__READ_WRITE ,__setena0_bits);
__IO_REG32_BIT(CLRENA0,           0xE000E180,__READ_WRITE ,__clrena0_bits);
__IO_REG32_BIT(SETPEND0,          0xE000E200,__READ_WRITE ,__setpend0_bits);
__IO_REG32_BIT(CLRPEND0,          0xE000E280,__READ_WRITE ,__clrpend0_bits);
__IO_REG32_BIT(ACTIVE0,           0xE000E300,__READ       ,__active0_bits);
__IO_REG32_BIT(IP0,               0xE000E400,__READ_WRITE ,__pri0_bits);
__IO_REG32_BIT(IP1,               0xE000E404,__READ_WRITE ,__pri1_bits);
__IO_REG32_BIT(IP2,               0xE000E408,__READ_WRITE ,__pri2_bits);
__IO_REG32_BIT(IP3,               0xE000E40C,__READ_WRITE ,__pri3_bits);
__IO_REG32_BIT(IP4,               0xE000E410,__READ_WRITE ,__pri4_bits);
__IO_REG32_BIT(IP5,               0xE000E414,__READ_WRITE ,__pri5_bits);
__IO_REG32_BIT(IP6,               0xE000E418,__READ_WRITE ,__pri6_bits);
__IO_REG32_BIT(IP7,               0xE000E41C,__READ_WRITE ,__pri7_bits);
__IO_REG32_BIT(CPUIDBR,           0xE000ED00,__READ       ,__cpuidbr_bits);
__IO_REG32_BIT(ICSR,              0xE000ED04,__READ_WRITE ,__icsr_bits);
__IO_REG32_BIT(VTOR,              0xE000ED08,__READ_WRITE ,__vtor_bits);
__IO_REG32_BIT(AITCR,             0xE000ED0C,__READ_WRITE ,__aircr_bits);
__IO_REG32_BIT(SCR,               0xE000ED10,__READ_WRITE ,__scr_bits);
__IO_REG32_BIT(CCR,               0xE000ED14,__READ_WRITE ,__ccr_bits);
__IO_REG32_BIT(SHPR0,             0xE000ED18,__READ_WRITE ,__pri1_bits);
__IO_REG32_BIT(SHPR1,             0xE000ED1C,__READ_WRITE ,__pri2_bits);
__IO_REG32_BIT(SHPR2,             0xE000ED20,__READ_WRITE ,__pri3_bits);
__IO_REG32_BIT(SHCSR,             0xE000ED24,__READ_WRITE ,__shcsr_bits);
__IO_REG32_BIT(CFSR,              0xE000ED28,__READ_WRITE ,__cfsr_bits);
__IO_REG32_BIT(HFSR,              0xE000ED2C,__READ_WRITE ,__hfsr_bits);
__IO_REG32_BIT(DFSR,              0xE000ED30,__READ_WRITE ,__dfsr_bits);
__IO_REG32(    MMFAR,             0xE000ED34,__READ_WRITE);
__IO_REG32(    BFAR,              0xE000ED38,__READ_WRITE);
__IO_REG32_BIT(STIR,              0xE000EF00,__WRITE      ,__stir_bits);

/***************************************************************************
 **
 ** Core debug
 **
 ***************************************************************************/
__IO_REG32_BIT(DHSR,              0xE000EDF0,__READ_WRITE ,__dhsr_bits);
#define DHCR        DHSR
#define DHCR_bit    DHSR_bit
__IO_REG32_BIT(DCRSR,             0xE000EDF4,__WRITE      ,__dcrsr_bits);
__IO_REG32(    DCRDR,             0xE000EDF8,__READ_WRITE);
__IO_REG32_BIT(DEMCR,             0xE000EDFC,__READ_WRITE ,__demcr_bits);

/***************************************************************************
 **
 ** FPB
 **
 ***************************************************************************/
__IO_REG32_BIT(FP_CTRL,           0xE0002000,__READ_WRITE ,__fp_ctrl_bits);
__IO_REG32_BIT(FP_REMAP,          0xE0002004,__READ_WRITE ,__fp_remap_bits);
__IO_REG32_BIT(FP_COMP0,          0xE0002008,__READ_WRITE ,__fp_comp_bits);
__IO_REG32_BIT(FP_COMP1,          0xE000200C,__READ_WRITE ,__fp_comp_bits);
__IO_REG32_BIT(FP_COMP2,          0xE0002010,__READ_WRITE ,__fp_comp_bits);
__IO_REG32_BIT(FP_COMP3,          0xE0002014,__READ_WRITE ,__fp_comp_bits);
__IO_REG32_BIT(FP_COMP4,          0xE0002018,__READ_WRITE ,__fp_comp_bits);
__IO_REG32_BIT(FP_COMP5,          0xE000201C,__READ_WRITE ,__fp_comp_bits);
__IO_REG32_BIT(FP_COMP6,          0xE0002020,__READ_WRITE ,__fp_comp_bits);
__IO_REG32_BIT(FP_COMP7,          0xE0002024,__READ_WRITE ,__fp_comp_bits);
__IO_REG8(     FP_PERIPID4,       0xE0002FD0,__READ);
__IO_REG8(     FP_PERIPID5,       0xE0002FD4,__READ);
__IO_REG8(     FP_PERIPID6,       0xE0002FD8,__READ);
__IO_REG8(     FP_PERIPID7,       0xE0002FDC,__READ);
__IO_REG8(     FP_PERIPID0,       0xE0002FE0,__READ);
__IO_REG8(     FP_PERIPID1,       0xE0002FE4,__READ);
__IO_REG8(     FP_PERIPID2,       0xE0002FE8,__READ);
__IO_REG8(     FP_PERIPID3,       0xE0002FEC,__READ);
__IO_REG8(     FP_PCELLID0,       0xE0002FF0,__READ);
__IO_REG8(     FP_PCELLID1,       0xE0002FF4,__READ);
__IO_REG8(     FP_PCELLID2,       0xE0002FF8,__READ);
__IO_REG8(     FP_PCELLID3,       0xE0002FFC,__READ);

/***************************************************************************
 **
 ** DWT
 **
 ***************************************************************************/
__IO_REG32_BIT(DWT_CTRL,          0xE0001000,__READ_WRITE ,__dwt_ctrl_bits);
__IO_REG32(    DWT_CYCCNT,        0xE0001004,__READ);
__IO_REG8(     DWT_CPICNT,        0xE0001008,__READ_WRITE);
__IO_REG8(     DWT_EXCCNT,        0xE000100C,__READ_WRITE);
__IO_REG8(     DWT_SLEEPCNT,      0xE0001010,__READ_WRITE);
__IO_REG8(     DWT_LSUCNT,        0xE0001014,__READ_WRITE);
__IO_REG8(     DWT_FOLDCNT,       0xE0001018,__READ_WRITE);
__IO_REG32(    DWT_COMP0,         0xE0001020,__READ_WRITE);
__IO_REG32_BIT(DWT_MASK0,         0xE0001024,__READ_WRITE ,__dwt_mask_bits);
__IO_REG32_BIT(DWT_FUNCTION0,     0xE0001028,__READ_WRITE ,__dwt_function_bits);
__IO_REG32(    DWT_COMP1,         0xE0001030,__READ_WRITE);
__IO_REG32_BIT(DWT_MASK1,         0xE0001034,__READ_WRITE ,__dwt_mask_bits);
__IO_REG32_BIT(DWT_FUNCTION1,     0xE0001038,__READ_WRITE ,__dwt_function_bits);
__IO_REG32(    DWT_COMP2,         0xE0001040,__READ_WRITE);
__IO_REG32_BIT(DWT_MASK2,         0xE0001044,__READ_WRITE ,__dwt_mask_bits);
__IO_REG32_BIT(DWT_FUNCTION2,     0xE0001048,__READ_WRITE ,__dwt_function_bits);
__IO_REG32(    DWT_COMP3,         0xE0001050,__READ_WRITE);
__IO_REG32_BIT(DWT_MASK3,         0xE0001054,__READ_WRITE ,__dwt_mask_bits);
__IO_REG32_BIT(DWT_FUNCTION3,     0xE0001058,__READ_WRITE ,__dwt_function_bits);
__IO_REG8(     DWT_PERIPID4,      0xE0001FD0,__READ);
__IO_REG8(     DWT_PERIPID5,      0xE0001FD4,__READ);
__IO_REG8(     DWT_PERIPID6,      0xE0001FD8,__READ);
__IO_REG8(     DWT_PERIPID7,      0xE0001FDC,__READ);
__IO_REG8(     DWT_PERIPID0,      0xE0001FE0,__READ);
__IO_REG8(     DWT_PERIPID1,      0xE0001FE4,__READ);
__IO_REG8(     DWT_PERIPID2,      0xE0001FE8,__READ);
__IO_REG8(     DWT_PERIPID3,      0xE0001FEC,__READ);
__IO_REG8(     DWT_PCELLID0,      0xE0001FF0,__READ);
__IO_REG8(     DWT_PCELLID1,      0xE0001FF4,__READ);
__IO_REG8(     DWT_PCELLID2,      0xE0001FF8,__READ);
__IO_REG8(     DWT_PCELLID3,      0xE0001FFC,__READ);

/***************************************************************************
 **
 ** ITM
 **
 ***************************************************************************/
__IO_REG32(    ITM_SP0,           0xE0000000,__READ_WRITE);
__IO_REG32(    ITM_SP1,           0xE0000004,__READ_WRITE);
__IO_REG32(    ITM_SP2,           0xE0000008,__READ_WRITE);
__IO_REG32(    ITM_SP3,           0xE000000C,__READ_WRITE);
__IO_REG32(    ITM_SP4,           0xE0000010,__READ_WRITE);
__IO_REG32(    ITM_SP5,           0xE0000014,__READ_WRITE);
__IO_REG32(    ITM_SP6,           0xE0000018,__READ_WRITE);
__IO_REG32(    ITM_SP7,           0xE000001C,__READ_WRITE);
__IO_REG32(    ITM_SP8,           0xE0000020,__READ_WRITE);
__IO_REG32(    ITM_SP9,           0xE0000024,__READ_WRITE);
__IO_REG32(    ITM_SP10,          0xE0000028,__READ_WRITE);
__IO_REG32(    ITM_SP11,          0xE000002C,__READ_WRITE);
__IO_REG32(    ITM_SP12,          0xE0000030,__READ_WRITE);
__IO_REG32(    ITM_SP13,          0xE0000034,__READ_WRITE);
__IO_REG32(    ITM_SP14,          0xE0000038,__READ_WRITE);
__IO_REG32(    ITM_SP15,          0xE000003C,__READ_WRITE);
__IO_REG32(    ITM_SP16,          0xE0000040,__READ_WRITE);
__IO_REG32(    ITM_SP17,          0xE0000044,__READ_WRITE);
__IO_REG32(    ITM_SP18,          0xE0000048,__READ_WRITE);
__IO_REG32(    ITM_SP19,          0xE000004C,__READ_WRITE);
__IO_REG32(    ITM_SP20,          0xE0000050,__READ_WRITE);
__IO_REG32(    ITM_SP21,          0xE0000054,__READ_WRITE);
__IO_REG32(    ITM_SP22,          0xE0000058,__READ_WRITE);
__IO_REG32(    ITM_SP23,          0xE000005C,__READ_WRITE);
__IO_REG32(    ITM_SP24,          0xE0000060,__READ_WRITE);
__IO_REG32(    ITM_SP25,          0xE0000064,__READ_WRITE);
__IO_REG32(    ITM_SP26,          0xE0000068,__READ_WRITE);
__IO_REG32(    ITM_SP27,          0xE000006C,__READ_WRITE);
__IO_REG32(    ITM_SP28,          0xE0000070,__READ_WRITE);
__IO_REG32(    ITM_SP29,          0xE0000074,__READ_WRITE);
__IO_REG32(    ITM_SP30,          0xE0000078,__READ_WRITE);
__IO_REG32(    ITM_SP31,          0xE000007C,__READ_WRITE);
__IO_REG32_BIT(ITM_TE,            0xE0000E00,__READ_WRITE ,__itm_te_bits);
__IO_REG32_BIT(ITM_TP,            0xE0000E40,__READ_WRITE ,__itm_tp_bits);
__IO_REG32_BIT(ITM_CR,            0xE0000E80,__READ_WRITE ,__itm_cr_bits);
__IO_REG32_BIT(ITM_IW,            0xE0000EF8,__WRITE      ,__itm_iw_bits);
__IO_REG32_BIT(ITM_IR,            0xE0000EFC,__READ       ,__itm_ir_bits);
__IO_REG32_BIT(ITM_IMC,           0xE0000F00,__READ_WRITE ,__itm_imc_bits);
__IO_REG32(    ITM_LAR,           0xE0000FB0,__WRITE);
__IO_REG32_BIT(ITM_LSR,           0xE0000FB4,__READ       ,__itm_lsr_bits);
__IO_REG8(     ITM_PERIPID4,      0xE0000FD0,__READ);
__IO_REG8(     ITM_PERIPID5,      0xE0000FD4,__READ);
__IO_REG8(     ITM_PERIPID6,      0xE0000FD8,__READ);
__IO_REG8(     ITM_PERIPID7,      0xE0000FDC,__READ);
__IO_REG8(     ITM_PERIPID0,      0xE0000FE0,__READ);
__IO_REG8(     ITM_PERIPID1,      0xE0000FE4,__READ);
__IO_REG8(     ITM_PERIPID2,      0xE0000FE8,__READ);
__IO_REG8(     ITM_PERIPID3,      0xE0000FEC,__READ);
__IO_REG8(     ITM_PCELLID0,      0xE0000FF0,__READ);
__IO_REG8(     ITM_PCELLID1,      0xE0000FF4,__READ);
__IO_REG8(     ITM_PCELLID2,      0xE0000FF8,__READ);
__IO_REG8(     ITM_PCELLID3,      0xE0000FFC,__READ);

/***************************************************************************
 **
 ** TPIU

 **
 ***************************************************************************/
__IO_REG32_BIT(TPIU_SPSR,         0xE0040000,__READ       ,__tpiu_spsr_bits);
__IO_REG32_BIT(TPIU_CPSR,         0xE0040004,__READ_WRITE ,__tpiu_spsr_bits);
__IO_REG32_BIT(TPIU_COSDR,        0xE0040010,__READ_WRITE ,__tpiu_cosdr_bits);
__IO_REG32_BIT(TPIU_SPPR,         0xE00400F0,__READ_WRITE ,__tpiu_sppr_bits);
__IO_REG32_BIT(TPIU_FFSR,         0xE0040300,__READ       ,__tpiu_ffsr_bits);
__IO_REG32_BIT(TPIU_FFCR,         0xE0040304,__READ       ,__tpiu_ffsr_bits);
__IO_REG32(    TPIU_FSCR,         0xE0040308,__READ);
__IO_REG32_BIT(TPIU_ITATBCTR2,    0xE0040EF0,__READ       ,__tpiu_itatbctr2_bits);
__IO_REG32_BIT(TPIU_ITATBCTR0,    0xE0040EF8,__READ       ,__tpiu_itatbctr0_bits);

/* Assembler-specific declarations  ****************************************/
#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  LM3S812 Interrupt Lines
 **
 ***************************************************************************/
#define MAIN_STACK             0          /* Main Stack                   */
#define RESETI                 1          /* Reset                        */
#define NMII                   2          /* Non-maskable Interrupt       */
#define HFI                    3          /* Hard Fault                   */
#define MMI                    4          /* Memory Management            */
#define BFI                    5          /* Bus Fault                    */
#define UFI                    6          /* Usage Fault                  */
#define SVCI                  11          /* SVCall                       */
#define DMI                   12          /* Debug Monitor                */
#define PSI                   14          /* PendSV                       */
#define STI                   15          /* SysTick                      */
#define EII                   16          /* External Interrupt           */
#define NVIC_GPIOA           ( 0 + EII)   /* PORTA                        */
#define NVIC_GPIOB           ( 1 + EII)   /* PORTB                        */
#define NVIC_GPIOC           ( 2 + EII)   /* PORTC                        */
#define NVIC_GPIOD           ( 3 + EII)   /* PORTD                        */
#define NVIC_GPIOE           ( 4 + EII)   /* PORTE                        */
#define NVIC_UART0           ( 5 + EII)   /* UART 0                       */
#define NVIC_UART1           ( 6 + EII)   /* UART 1                       */
#define NVIC_SSI             ( 7 + EII)   /* SSI                          */
#define NVIC_I2C             ( 8 + EII)   /* I2C                          */
#define NVIC_PWM_FAULT       ( 9 + EII)   /* PWM Fault                    */
#define NVIC_PWM_GEN0        (10 + EII)   /* PWM Generator 0              */
#define NVIC_ADC_SS0         (14 + EII)   /* ADC Sample Sequencer 0       */
#define NVIC_ADC_SS1         (15 + EII)   /* ADC Sample Sequencer 1       */
#define NVIC_ADC_SS2         (16 + EII)   /* ADC Sample Sequencer 2       */
#define NVIC_ADC_SS3         (17 + EII)   /* ADC Sample Sequencer 3       */
#define NVIC_WDT             (18 + EII)   /* WDT                          */
#define NVIC_TIMER0A         (19 + EII)   /* Timer 0 Channel A            */
#define NVIC_TIMER0B         (20 + EII)   /* Timer 0 Channel B            */
#define NVIC_TIMER1A         (21 + EII)   /* Timer 1 Channel A            */
#define NVIC_TIMER1B         (22 + EII)   /* Timer 1 Channel B            */
#define NVIC_TIMER2A         (23 + EII)   /* Timer 2 Channel A            */
#define NVIC_TIMER2B         (24 + EII)   /* Timer 2 Channel B            */
#define NVIC_ANAL_COMP0      (25 + EII)   /* Analog comparator 0          */
#define NVIC_SYS_CTRL        (28 + EII)   /* System control               */
#define NVIC_FLASH_CTRL      (29 + EII)   /* Flash controller             */

#endif    /* __IOLM3S812_H */
