/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    ST STR736
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1 $
 **
 ***************************************************************************/

#ifndef __IOSTR736_H
#define __IOSTR736_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   STR736 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/


/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* RC Oscillator Control Register (CMU_RCCTL) */
typedef struct {
  __REG16  RCCTL          : 4;
  __REG16                 :12;
} __cmurcctl_bits;

/* Frequency Display Register (CMU_FDISP) */
typedef struct {
  __REG16  FD             :12;
  __REG16                 : 4;
} __cmufdisp_bits;

/* Frequency Reference High Register (CMU_FRH) */
typedef struct {
  __REG16  FH             :12;
  __REG16                 : 4;
} __cmufrh_bits;

/* Frequency Reference Low Register (CMU_FRL) */
typedef struct {
  __REG16  FL             :12;
  __REG16                 : 4;
} __cmufrl_bits;

/* Control Register (CMU_CTRL) */
typedef struct {
  __REG16  CKSEL0         : 1;
  __REG16  CKSEL1         : 1;
  __REG16  CKSEL2         : 1;
  __REG16  REN            : 1;
  __REG16  SFM            : 1;
  __REG16  RCSS           : 1;
  __REG16  RCHSE          : 1;
  __REG16  RCFS           : 1;
  __REG16  RCFR           : 1;
  __REG16  CRFR           : 1;
  __REG16  OSCS           : 1;
  __REG16                 : 5;
} __cmuctrl_bits;

/* Status Register (CMU_STAT) */
typedef struct {
  __REG16  CKON0          : 1;
  __REG16  CKON1          : 1;
  __REG16  CKON2          : 1;
  __REG16  RON            : 1;
  __REG16  CRF            : 1;
  __REG16                 :11;
} __cmustat_bits;

/* Interrupt Status Register (CMU_IS) */
typedef struct {
  __REG16  OLR            : 1;
  __REG16  EOC            : 1;
  __REG16  FLL            : 1;
  __REG16  ROI            : 1;
  __REG16                 :12;
} __cmuis_bits;

/* Interrupt Mask Register (CMU_IM) */
typedef struct {
  __REG16  OLRM           : 1;
  __REG16  EOCM           : 1;
  __REG16  FLLM           : 1;
  __REG16  ROIM           : 1;
  __REG16                 :12;
} __cmuim_bits;

/* End Of Count Value Register (CMU_EOCV) */
typedef struct {
  __REG16  EOCV           : 8;
  __REG16                 : 8;
} __cmueocv_bits;

/* Clock Control Register (PRCCU_CCR) */
typedef struct {
  __REG32  LPOWFI         :1;
  __REG32  WFI_CKSEL      :1;
  __REG32                 :1;
  __REG32  SRESEN         :1;
  __REG32                 :3;
  __REG32  EN_LOCK        :1;
  __REG32                 :1;
  __REG32  EN_CK2_16      :1;
  __REG32  EN_STOP        :1;
  __REG32  EN_HALT        :1;
  __REG32                 :20;
} __prccuccr_bits;

/* Voltage Regulator Control Register (PRCCU_VRCTR) */
typedef struct {
  __REG32                 :2;
  __REG32  VROK           :1;
  __REG32  VROFF_REG      :1;
  __REG32  VRLPW          :1;
  __REG32                 :27;
} __prccuvrctr_bits;

/* Clock Flag Register (PRCCU_CFR) */
typedef struct {
  __REG32  CSU_CKSEL      :1;
  __REG32  LOCK           :1;
  __REG32                 :1;
  __REG32  CK2_16         :1;
  __REG32                 :1;
  __REG32  SOFTRES        :1;
  __REG32  WDGRES0        :1;
  __REG32                 :1;
  __REG32  LVD_INT        :1;
  __REG32                 :2;
  __REG32  LOCK_I         :1;
  __REG32                 :1;
  __REG32  CK2_16_I       :1;
  __REG32  STOP_I         :1;
  __REG32  DIV2           :1;
  __REG32                 :16;
} __prccucfr_bits;

/* PLL Configuration Register (PRCCU_PLLCR) */
typedef struct {
  __REG32  DX0            :1;
  __REG32  DX1            :1;
  __REG32  DX2            :1;
  __REG32                 :1;
  __REG32  MX0            :1;
  __REG32  MX1            :1;
  __REG32  FREF_RANGE     :1;
  __REG32  FREEN          :1;
  __REG32                 :24;
} __prccupllcr_bits;

/* System Mode Register (PRCCU_SMR) */
typedef struct {
  __REG32  WFI            : 1;
  __REG32  HALT           : 1;
  __REG32                 :30;
} __prccusmr_bits;

/* Real Time Clock Programming Register (PRCCU_RTCPR) */
typedef struct {
  __REG32  RTCP           : 4;
  __REG32                 :28;
} __prccurtcpr_bits;

/* Configuration Register 0 (CFG_R0) */
typedef struct {
  __REG32  REMAP          : 1;
  __REG32                 : 3;
  __REG32  DMABSPI0       : 1;
  __REG32  DMABSPI1       : 1;
  __REG32                 : 1;
  __REG32  JTBT           : 1;
  __REG32  USER2          : 1;
  __REG32  USER1          : 1;
  __REG32  SYS            : 1;
  __REG32                 :21;
} __cfgr0_bits;

/* Configuration Register 1 (CFG_R1) */
typedef struct {
  __REG32  LPVRCC         : 2;
  __REG32  EIFILT         : 1;
  __REG32  WUP0S          : 1;
  __REG32  FLPOD          : 4;
  __REG32                 :24;
} __cfgr1_bits;

/* External Interrupt Trigger Event Register 0 (CFG_EITE0) */
typedef struct {
  __REG32  EITE0          :16;
  __REG32                 :16;
} __cfgeite0_bits;

/* External Interrupt Trigger Event Register 1 (CFG_EITE1) */
typedef struct {
  __REG32  EITE1          :16;
  __REG32                 :16;
} __cfgeite1_bits;

/* External Interrupt Trigger Event Register 2 (CFG_EITE2) */
typedef struct {
  __REG32  EITE2          :16;
  __REG32                 :16;
} __cfgeite2_bits;

/* Peripheral Clock Gating Register 0 (CFG_PCGR0) */
typedef struct {
  __REG32  RAM            : 1;
  __REG32  I2C0           : 1;
  __REG32  WIU            : 1;
  __REG32                 : 1;
  __REG32  UART0          : 1;
  __REG32  UART1          : 1;
  __REG32  TIM0           : 1;
  __REG32  TIM1           : 1;
  __REG32  TB0            : 1;
  __REG32                 : 3;
  __REG32  PWM0           : 1;
  __REG32  PWM1           : 1;
  __REG32  PWM2           : 1;
  __REG32  PWM3           : 1;
  __REG32  PWM4           : 1;
  __REG32  PWM5           : 1;
  __REG32  PORT0          : 1;
  __REG32  PORT1          : 1;
  __REG32  PORT2          : 1;
  __REG32  PORT3          : 1;
  __REG32  PORT4          : 1;
  __REG32  PORT5          : 1;
  __REG32  PORT6          : 1;
  __REG32  BSPI0          : 1;
  __REG32  BSPI1          : 1;
  __REG32  BSPI2          : 1;
  __REG32  ADC            : 1;
  __REG32  EIC            : 1;
  __REG32  WUT            : 1;
  __REG32                 : 1;
} __cfg_pcgr0_bits;

/* Peripheral Clock Gating Register 1 (CFG_PCGR1) */
typedef struct {
  __REG32  I2C1           : 1;
  __REG32                 : 2;
  __REG32  TIM5           : 1;    
  __REG32                 : 4;
  __REG32  UART2          : 1;
  __REG32  UART3          : 1;
  __REG32                 : 3;
  __REG32  TB1            : 1;
  __REG32  TB2            : 1;
  __REG32                 : 1;
  __REG32  TIM2           : 1;
  __REG32  TIM3           : 1;
  __REG32  TIM4           : 1;
  __REG32  RTC            : 1;
  __REG32  DMA0           : 1;
  __REG32  DMA1           : 1;
  __REG32  DMA2           : 1;
  __REG32  DMA3           : 1;
  __REG32                 : 5;
  __REG32  NBA            : 1;
  __REG32  AHBA           : 1;
  __REG32                 : 1;
} __cfg_pcgr1_bits;

/* TIM External Clock Select Register (CFG_TIMSR) */
typedef struct {
  __REG32  TIMECKS        :10;
  __REG32                 :22;
} __cfgtimsr_bits;

/* Emulation Serial Protection Register (CFG_ESPR) */
typedef struct {
  __REG32  UART0          : 1;
  __REG32  UART1          : 1;
  __REG32  UART2          : 1;
  __REG32  UART3          : 1;
  __REG32  BSPI0          : 1;
  __REG32  BSPI1          : 1;
  __REG32  BSPI2          : 1;
  __REG32                 :25;
} __cfgespr_bits;

/* Interrupt Control Register (EIC_ICR) */
typedef struct {
  __REG32  IRQ_EN         : 1;
  __REG32  FIQ_EN         : 1;
  __REG32                 :30;
} __eicicr_bits;

/* Current Interrupt Channel Register (EIC_CICR) */
typedef struct {
  __REG32  CIC            : 6;
  __REG32                 :26;
} __eiccicr_bits;

/* Current Interrupt Priority Register (EIC_CIPR) */
typedef struct {
  __REG32  CIP            : 4;
  __REG32                 :28;
} __eiccipr_bits;

/* Interrupt Vector Register (EIC_IVR) */
typedef struct {
  __REG32  JUMPOPCODE     :16;
  __REG32  JUMPADDRESS    :16;
} __eicivr_bits;

/* Fast Interrupt Enable Register (EIC_FIER) */
typedef struct {
  __REG32  FIE            : 2;
  __REG32                 :30;
} __eicfier_bits;

/* Fast Interrupt Pending Register (EIC_FIPR) */
typedef struct {
  __REG32  FIP            : 2;
  __REG32                 :30;
} __eicfipr_bits;

/* Fast Interrupt Register (EIC_FIR)*/
typedef struct {
  __REG32  FIE            : 2;
  __REG32                 : 1;
  __REG32  FIP            : 2;
  __REG32                 :27;
} __eicfir_bits;

/* Interrupt Enable Register 0 (EIC_IER0) */
typedef struct {
  __REG32 IER_0           : 1;
  __REG32 IER_1           : 1;
  __REG32 IER_2           : 1;
  __REG32 IER_3           : 1;
  __REG32 IER_4           : 1;
  __REG32 IER_5           : 1;
  __REG32 IER_6           : 1;
  __REG32 IER_7           : 1;
  __REG32 IER_8           : 1;
  __REG32 IER_9           : 1;
  __REG32 IER_10          : 1;
  __REG32 IER_11          : 1;
  __REG32 IER_12          : 1;
  __REG32 IER_13          : 1;
  __REG32 IER_14          : 1;
  __REG32 IER_15          : 1;
  __REG32 IER_16          : 1;
  __REG32 IER_17          : 1;
  __REG32 IER_18          : 1;
  __REG32 IER_19          : 1;
  __REG32 IER_20          : 1;
  __REG32 IER_21          : 1;
  __REG32 IER_22          : 1;
  __REG32 IER_23          : 1;
  __REG32 IER_24          : 1;
  __REG32 IER_25          : 1;
  __REG32 IER_26          : 1;
  __REG32 IER_27          : 1;
  __REG32 IER_28          : 1;
  __REG32 IER_29          : 1;
  __REG32 IER_30          : 1;
  __REG32 IER_31          : 1;
} __eicier0_bits;

/* Interrupt Enable Register 1 (EIC_IER1) */
typedef struct {
  __REG32 IER_32          : 1;
  __REG32 IER_33          : 1;
  __REG32 IER_34          : 1;
  __REG32 IER_35          : 1;
  __REG32 IER_36          : 1;
  __REG32 IER_37          : 1;
  __REG32 IER_38          : 1;
  __REG32 IER_39          : 1;
  __REG32 IER_40          : 1;
  __REG32 IER_41          : 1;
  __REG32 IER_42          : 1;
  __REG32 IER_43          : 1;
  __REG32 IER_44          : 1;
  __REG32 IER_45          : 1;
  __REG32 IER_46          : 1;
  __REG32 IER_47          : 1;
  __REG32 IER_48          : 1;
  __REG32 IER_49          : 1;
  __REG32 IER_50          : 1;
  __REG32 IER_51          : 1;
  __REG32 IER_52          : 1;
  __REG32 IER_53          : 1;
  __REG32 IER_54          : 1;
  __REG32 IER_55          : 1;
  __REG32 IER_56          : 1;
  __REG32 IER_57          : 1;
  __REG32 IER_58          : 1;
  __REG32 IER_59          : 1;
  __REG32 IER_60          : 1;
  __REG32 IER_61          : 1;
  __REG32 IER_62          : 1;
  __REG32 IER_63          : 1;
} __eicier1_bits;

/* Interrupt Pending Register 0 (EIC_IPR0) */
typedef struct {
  __REG32 IPR_0           : 1;
  __REG32 IPR_1           : 1;
  __REG32 IPR_2           : 1;
  __REG32 IPR_3           : 1;
  __REG32 IPR_4           : 1;
  __REG32 IPR_5           : 1;
  __REG32 IPR_6           : 1;
  __REG32 IPR_7           : 1;
  __REG32 IPR_8           : 1;
  __REG32 IPR_9           : 1;
  __REG32 IPR_10          : 1;
  __REG32 IPR_11          : 1;
  __REG32 IPR_12          : 1;
  __REG32 IPR_13          : 1;
  __REG32 IPR_14          : 1;
  __REG32 IPR_15          : 1;
  __REG32 IPR_16          : 1;
  __REG32 IPR_17          : 1;
  __REG32 IPR_18          : 1;
  __REG32 IPR_19          : 1;
  __REG32 IPR_20          : 1;
  __REG32 IPR_21          : 1;
  __REG32 IPR_22          : 1;
  __REG32 IPR_23          : 1;
  __REG32 IPR_24          : 1;
  __REG32 IPR_25          : 1;
  __REG32 IPR_26          : 1;
  __REG32 IPR_27          : 1;
  __REG32 IPR_28          : 1;
  __REG32 IPR_29          : 1;
  __REG32 IPR_30          : 1;
  __REG32 IPR_31          : 1;
} __eicipr0_bits;

/* Interrupt Pending Register 1 (EIC_IPR1) */
typedef struct {
  __REG32 IPR_32          : 1;
  __REG32 IPR_33          : 1;
  __REG32 IPR_34          : 1;
  __REG32 IPR_35          : 1;
  __REG32 IPR_36          : 1;
  __REG32 IPR_37          : 1;
  __REG32 IPR_38          : 1;
  __REG32 IPR_39          : 1;
  __REG32 IPR_40          : 1;
  __REG32 IPR_41          : 1;
  __REG32 IPR_42          : 1;
  __REG32 IPR_43          : 1;
  __REG32 IPR_44          : 1;
  __REG32 IPR_45          : 1;
  __REG32 IPR_46          : 1;
  __REG32 IPR_47          : 1;
  __REG32 IPR_48          : 1;
  __REG32 IPR_49          : 1;
  __REG32 IPR_50          : 1;
  __REG32 IPR_51          : 1;
  __REG32 IPR_52          : 1;
  __REG32 IPR_53          : 1;
  __REG32 IPR_54          : 1;
  __REG32 IPR_55          : 1;
  __REG32 IPR_56          : 1;
  __REG32 IPR_57          : 1;
  __REG32 IPR_58          : 1;
  __REG32 IPR_59          : 1;
  __REG32 IPR_60          : 1;
  __REG32 IPR_61          : 1;
  __REG32 IPR_62          : 1;
  __REG32 IPR_63          : 1;
} __eicipr1_bits;

/* Source Interrupt Registers - Channel n (EIC_SIRn) */
typedef struct {
  __REG32 SIPL            : 4;
  __REG32                 :12;
  __REG32 SIV             :16;
} __eicsirn_bits;


/* Flash Control Register 0 (FLASH_CR0)*/
typedef struct
{
  __REG32                 : 1;
  __REG32  BSYA0          : 1;
  __REG32  BSYA1          : 1;
  __REG32                 : 1;
  __REG32  LOCK           : 1;
  __REG32                 :10;
  __REG32  PWD            : 1;
  __REG32                 : 4;
  __REG32  INTP           : 1;
  __REG32  INTM           : 1;
  __REG32                 : 2;
  __REG32  SPR            : 1;
  __REG32                 : 2;
  __REG32  SER            : 1;
  __REG32  DWPG           : 1;
  __REG32  WPG            : 1;
  __REG32  SUSP           : 1;
  __REG32  WMS            : 1;
} __flashctrl0_bits;

/* Flash Control Register 1 (FLASH_CR1)*/
typedef struct
{
  __REG32  B0F0           : 1;
  __REG32  B0F1           : 1;
  __REG32  B0F2           : 1;
  __REG32  B0F3           : 1;
  __REG32  B0F4           : 1;
  __REG32  B0F5           : 1;
  __REG32  B0F6           : 1;
  __REG32  B0F7           : 1;
  __REG32                 : 8;
  __REG32  B1F0           : 1;
  __REG32  B1F1           : 1;
  __REG32                 : 6;
  __REG32  B0S            : 1;
  __REG32  B1S            : 1;
  __REG32                 : 6;
} __flashctrl1_bits;

/* Flash Address Register (FLASH_AR) */
typedef struct
{
  __REG32                 : 2;
  __REG32  ADD            :19;
  __REG32                 :11;
} __flashadd_bits;

/* Flash Error Register (FLASH_ER) */
typedef struct
{
  __REG32  ERR            : 1;
  __REG32  ERER           : 1;
  __REG32  PGER           : 1;
  __REG32  _10ER          : 1;
  __REG32                 : 2;
  __REG32  SEQER          : 1;
  __REG32  RESER          : 1;
  __REG32  WPF            : 1;
  __REG32                 :23;
} __flasherr_bits;

/* Flash Non Volatile Write Protection Register (FLASH_NVWPAR) */
typedef struct
{
  __REG32  W0P            : 8;
  __REG32                 : 8;
  __REG32  W1P            : 2;
  __REG32                 :14;
} __flashwrprot_bits;

/* Flash NV Access Protection Register 0 (FLASH_NVAPR0) */
typedef struct
{
  __REG32                 : 1;
  __REG32  DBGP           : 1;
  __REG32                 :30;
} __flashaccprot0_bits;

/* Flash NV Access Protection Register 1 (FLASH_NVAPR1) */
typedef struct
{
  __REG32  PDS            :16;
  __REG32  PEN            :16;
} __flashaccprot1_bits;

/* Wake-up Control Register (WIU_CTRL) */
typedef struct {
  __REG32  WKUP_INT       : 1;
  __REG32  INT_EN         : 1;
  __REG32  STOP           : 1;
  __REG32                 :29;
} __wiuctrl_bits;

/* Wake-up Mask Register (WIU_MR) */
typedef struct {
  __REG32  WUM0           : 1;
  __REG32  WUM1           : 1;
  __REG32  WUM2           : 1;
  __REG32  WUM3           : 1;
  __REG32  WUM4           : 1;
  __REG32  WUM5           : 1;
  __REG32  WUM6           : 1;
  __REG32  WUM7           : 1;
  __REG32  WUM8           : 1;
  __REG32  WUM9           : 1;
  __REG32  WUM10          : 1;
  __REG32  WUM11          : 1;
  __REG32  WUM12          : 1;
  __REG32  WUM13          : 1;
  __REG32  WUM14          : 1;
  __REG32  WUM15          : 1;
  __REG32  WUM16          : 1;
  __REG32  WUM17          : 1;
  __REG32  WUM18          : 1;
  __REG32  WUM19          : 1;
  __REG32  WUM20          : 1;
  __REG32  WUM21          : 1;
  __REG32  WUM22          : 1;
  __REG32  WUM23          : 1;
  __REG32  WUM24          : 1;
  __REG32  WUM25          : 1;
  __REG32  WUM26          : 1;
  __REG32  WUM27          : 1;
  __REG32  WUM28          : 1;
  __REG32  WUM29          : 1;
  __REG32  WUM30          : 1;
  __REG32  WUM31          : 1;
} __wiumr_bits;

/* Wake-up Triger Register (WIU_TR) */
typedef struct {
  __REG32  WUT0           : 1;
  __REG32  WUT1           : 1;
  __REG32  WUT2           : 1;
  __REG32  WUT3           : 1;
  __REG32  WUT4           : 1;
  __REG32  WUT5           : 1;
  __REG32  WUT6           : 1;
  __REG32  WUT7           : 1;
  __REG32  WUT8           : 1;
  __REG32  WUT9           : 1;
  __REG32  WUT10          : 1;
  __REG32  WUT11          : 1;
  __REG32  WUT12          : 1;
  __REG32  WUT13          : 1;
  __REG32  WUT14          : 1;
  __REG32  WUT15          : 1;
  __REG32  WUT16          : 1;
  __REG32  WUT17          : 1;
  __REG32  WUT18          : 1;
  __REG32  WUT19          : 1;
  __REG32  WUT20          : 1;
  __REG32  WUT21          : 1;
  __REG32  WUT22          : 1;
  __REG32  WUT23          : 1;
  __REG32  WUT24          : 1;
  __REG32  WUT25          : 1;
  __REG32  WUT26          : 1;
  __REG32  WUT27          : 1;
  __REG32  WUT28          : 1;
  __REG32  WUT29          : 1;
  __REG32  WUT30          : 1;
  __REG32  WUT31          : 1;
} __wiutr_bits;

/* Wake-up Software Interrupt Register (WIU_INTR) */
typedef struct {
  __REG32  WUINT0           : 1;
  __REG32  WUINT1           : 1;
  __REG32  WUINT2           : 1;
  __REG32  WUINT3           : 1;
  __REG32  WUINT4           : 1;
  __REG32  WUINT5           : 1;
  __REG32  WUINT6           : 1;
  __REG32  WUINT7           : 1;
  __REG32  WUINT8           : 1;
  __REG32  WUINT9           : 1;
  __REG32  WUINT10          : 1;
  __REG32  WUINT11          : 1;
  __REG32  WUINT12          : 1;
  __REG32  WUINT13          : 1;
  __REG32  WUINT14          : 1;
  __REG32  WUINT15          : 1;
  __REG32  WUINT16          : 1;
  __REG32  WUINT17          : 1;
  __REG32                   :14;
} __wiuintr_bits;

/* Wake-up Pending Register (WIU_PR) */
typedef struct {
  __REG32  WUP0           : 1;
  __REG32  WUP1           : 1;
  __REG32  WUP2           : 1;
  __REG32  WUP3           : 1;
  __REG32  WUP4           : 1;
  __REG32  WUP5           : 1;
  __REG32  WUP6           : 1;
  __REG32  WUP7           : 1;
  __REG32  WUP8           : 1;
  __REG32  WUP9           : 1;
  __REG32  WUP10          : 1;
  __REG32  WUP11          : 1;
  __REG32  WUP12          : 1;
  __REG32  WUP13          : 1;
  __REG32  WUP14          : 1;
  __REG32  WUP15          : 1;
  __REG32  WUP16          : 1;
  __REG32  WUP17          : 1;
  __REG32                 :14;
} __wiupr_bits;

/* Control Register (DMAn_CTRLx) */
typedef struct {
  __REG16  Enable         : 1;
  __REG16  SoInc          : 1;
  __REG16  DeInc          : 1;
  __REG16  SoSize         : 2;
  __REG16  SoBurst        : 2;
  __REG16  DeSize         : 2;
  __REG16  Circular       : 1;
  __REG16                 : 3;
  __REG16  Dir            : 1;
  __REG16                 : 2;
} __dmanctrlx_bits;

/* Control Register 3 (DMAn_CTRL3) */
typedef struct {
  __REG16  Enable         : 1;
  __REG16  SoInc          : 1;
  __REG16  DeInc          : 1;
  __REG16  SoSize         : 2;
  __REG16  SoBurst        : 2;
  __REG16  DeSize         : 2;
  __REG16  Circular       : 1;
  __REG16                 : 1;
  __REG16  Mem2Mem        : 1;
  __REG16                 : 1;
  __REG16  Dir            : 1;
  __REG16                 : 2;
} __dmanctrl3_bits;

/* Interrupt Mask Register (DMAn_MASK) */
typedef struct {
  __REG16  SIM0           : 1;
  __REG16  SIM1           : 1;
  __REG16  SIM2           : 1;
  __REG16  SIM3           : 1;
  __REG16  SEM0           : 1;
  __REG16  SEM1           : 1;
  __REG16  SEM2           : 1;
  __REG16  SEM3           : 1;
  __REG16                 : 8;
} __dmanmask_bits;

/* Interrupt Clear Register (DMAn_CLR) */
typedef struct {
  __REG16  SIC0           : 1;
  __REG16  SIC1           : 1;
  __REG16  SIC2           : 1;
  __REG16  SIC3           : 1;
  __REG16  SEC0           : 1;
  __REG16  SEC1           : 1;
  __REG16  SEC2           : 1;
  __REG16  SEC3           : 1;
  __REG16                 : 8;
} __dmanclr_bits;

/* Interrupt Status Register (DMAn_STATUS) */
typedef struct {
  __REG16  INT0           : 1;
  __REG16  INT1           : 1;
  __REG16  INT2           : 1;
  __REG16  INT3           : 1;
  __REG16  ERR0           : 1;
  __REG16  ERR1           : 1;
  __REG16  ERR2           : 1;
  __REG16  ERR3           : 1;
  __REG16  ACT0           : 1;
  __REG16  ACT1           : 1;
  __REG16  ACT2           : 1;
  __REG16  ACT3           : 1;
  __REG16                 : 4;
} __dmanstatus_bits;

/* Last Flag Register (DMAn_LAST) */
typedef struct {
  __REG16  LAST0          : 1;
  __REG16  LAST1          : 1;
  __REG16  LAST2          : 1;
  __REG16  LAST3          : 1;
  __REG16                 :12;
} __dmanlast_bits;

/* Time-Out Register (ARB_TOR) */
typedef struct {
  __REG32  TIMEOUT        :16;
  __REG32                 :16;
} __arbtor_bits;

/* Priority Register (ARB_PRIOR) */
typedef struct {
  __REG32  PRIORITY       : 2;
  __REG32                 :30;
} __arbprior_bits;

/* Control Register (ARB_CTLR) */
typedef struct {
  __REG32                 : 1;
  __REG32  ABORT          : 1;
  __REG32                 :30;
} __arbctlr_bits;

/* Wake-up Timer Control Register (WUT_CR) */
typedef struct {
  __REG16                 : 1;
  __REG16  SC             : 1;
  __REG16  EE             : 1;
  __REG16                 :13;
} __wutcr_bits;

/* Wake-up Timer Prescaler Register (WUT_PR) */
typedef struct {
  __REG16  PR             : 8;
  __REG16                 : 8;
} __wutpr_bits;

/* Wake-up Timer Status Register (WUT_SR) */
typedef struct {
  __REG16  EC             : 1;
  __REG16  BSYCR          : 1;
  __REG16  BSYPR          : 1;
  __REG16  BSYVR          : 1;
  __REG16                 :12;
} __wutsr_bits;

/* Wake-up Timer Mask Register (WUT_MR) */
typedef struct {
  __REG16  ECM            : 1;
  __REG16  BSYMSK         : 1;
  __REG16                 :14;
} __wutmr_bits;

/* RTC Control Register High (RTC_CRH) */
typedef struct {
  __REG16 SEN             : 1;
  __REG16 AEN             : 1;
  __REG16 OWEN            : 1;
  __REG16 GEN             : 1;
  __REG16                 :12;
} __rtccrh_bits;

/* RTC Control Register Low (RTC_CRL) */
typedef struct {
  __REG16 SIR             : 1;
  __REG16 AIR             : 1;
  __REG16 OWIR            : 1;
  __REG16 GIR             : 1;
  __REG16 CNF             : 1;
  __REG16 RTOFF           : 1;
  __REG16                 :10;
} __rtccrl_bits;

/* RTC Prescaler Load Register High (RTC_PRLH) */
typedef struct {
  __REG16 PRSL            : 4;
  __REG16                 :12;
} __rtcprlh_bits;

/* RTC Prescaler Divider Register High (RTC_DIVH) */
typedef struct {
  __REG16 DIV             : 4;
  __REG16                 :12;
} __rtcdivh_bits;

/* WDG Control Register (WDG_CR) */
typedef struct {
  __REG16 WE              : 1;
  __REG16 SC              : 1;
  __REG16 EE              : 1;
  __REG16                 :13;
} __wdgcr_bits;

/* WDG Prescaler Register (WDG_PR) */
typedef struct {
  __REG16 PR0             : 1;
  __REG16 PR1             : 1;
  __REG16 PR2             : 1;
  __REG16 PR3             : 1;
  __REG16 PR4             : 1;
  __REG16 PR5             : 1;
  __REG16 PR6             : 1;
  __REG16 PR7             : 1;
  __REG16                 : 8;
} __wdgpr_bits;

/* WDG Status Register (WDG_SR) */
typedef struct {
  __REG16  EC             : 1;
  __REG16                 :15;
} __wdgsr_bits;

/* WDG Mask Register (WDG_MR) */
typedef struct {
  __REG16  ECM            : 1;
  __REG16                 :15;
} __wdgmr_bits;

/* TB Timer Control Register (TBn_CR) */
typedef struct {
  __REG16                 : 1;
  __REG16  SC             : 1;
  __REG16  EE             : 1;
  __REG16                 :13;
} __tbncr_bits;

/* TB Timer Prescaler Register (TBn_PR) */
typedef struct {
  __REG16  PR0            : 1;
  __REG16  PR1            : 1;
  __REG16  PR2            : 1;
  __REG16  PR3            : 1;
  __REG16  PR4            : 1;
  __REG16  PR5            : 1;
  __REG16  PR6            : 1;
  __REG16  PR7            : 1;
  __REG16                 : 8;
} __tbnpr_bits;

/* TB Timer Status Register (TBn_SR) */
typedef struct {
  __REG16   EC            : 1;
  __REG16                 :15;
} __tbnsr_bits;

/* TB Timer Mask Register (TBn_MR) */
typedef struct {
  __REG16  ECM            : 1;
  __REG16                 :15;
} __tbnmr_bits;

/* Control Register 1 (TIMn_CR1) */
typedef struct {
  __REG16 ECKEN           : 1;
  __REG16 EXEDG           : 1;
  __REG16 IEDGA           : 1;
  __REG16 IEDGB           : 1;
  __REG16 PWM             : 1;
  __REG16 OPM             : 1;
  __REG16 OCAE            : 1;
  __REG16 OCBE            : 1;
  __REG16 OLVLA           : 1;
  __REG16 OLVLB           : 1;
  __REG16 FOLVA           : 1;
  __REG16 FOLVB           : 1;
  __REG16 DMAS0           : 1;
  __REG16 DMAS1           : 1;
  __REG16 PWMI            : 1;
  __REG16 EN              : 1;
} __timcr1_bits;

/* Control Register 2 (TIMn_CR2) */
typedef struct {
  __REG16 CC0             : 1;
  __REG16 CC1             : 1;
  __REG16 CC2             : 1;
  __REG16 CC3             : 1;
  __REG16 CC4             : 1;
  __REG16 CC5             : 1;
  __REG16 CC6             : 1;
  __REG16 CC7             : 1;
  __REG16                 : 2;
  __REG16 DMAIE           : 1;
  __REG16 OCBIE           : 1;
  __REG16 ICBIE           : 1;
  __REG16 TOE             : 1;
  __REG16 OCAIE           : 1;
  __REG16 ICAIE           : 1;
} __timcr2_bits;

/* Status Register (TIMn_SR) */
typedef struct {
  __REG16                 :11;
  __REG16 OCFB            : 1;
  __REG16 ICFB            : 1;
  __REG16 TOF             : 1;
  __REG16 OCFA            : 1;
  __REG16 ICFA            : 1;
} __timsr_bits;

/* Prescaler 0 Register (PWMn_PRS0) */
typedef struct {
  __REG16  PR00           : 1;
  __REG16  PR01           : 1;
  __REG16  PR02           : 1;
  __REG16                 :13;
} __pwmnprs0_bits;

/* Prescaler 1 Register (PWMn_PRS1) */
typedef struct {
  __REG16  PR10           : 1;
  __REG16  PR11           : 1;
  __REG16  PR12           : 1;
  __REG16  PR13           : 1;
  __REG16  PR14           : 1;
  __REG16                 :11;
} __pwmnprs1_bits;

/* PWM Enable Register (PWMn_PEN) */
typedef struct {
  __REG16  PE             : 1;
  __REG16                 :15;
} __pwmnpen_bits;

/* PWM Output Polarity Level Selection (PWMn_PLS) */
typedef struct {
  __REG16  PL             : 1;
  __REG16                 :15;
} __pwmnpls_bits;

/* PWM Compare Period Interrupt (PWMn_CPI) */
typedef struct {
  __REG16  CP             : 1;
  __REG16                 :15;
} __pwmncpi_bits;

/* PWM Interrupt Mask Register (PWMn_IM) */
typedef struct {
  __REG16  IM             : 1;
  __REG16                 :15;
} __pwmnim_bits;

/* I2C Control Register (I2Cn_CR) */
typedef struct {
  __REG8  ITE             : 1;
  __REG8  STOP            : 1;
  __REG8  ACK             : 1;
  __REG8  START           : 1;
  __REG8  ENGC            : 1;
  __REG8  PE              : 1;
  __REG8                  : 2;
} __i2cncr_bits;

/* I2C Status Register 1 (I2Cn_SR1) */
typedef struct {
  __REG8  SB              : 1;
  __REG8  MSL             : 1;
  __REG8  ADSL            : 1;
  __REG8  BTF             : 1;
  __REG8  BUSY            : 1;
  __REG8  TRA             : 1;
  __REG8  ADD10           : 1;
  __REG8  EVF             : 1;
} __i2cnsr1_bits;

/* I2C Status Register 2 (I2Cn_SR2) */
typedef struct {
  __REG8  GCAL            : 1;
  __REG8  BERR            : 1;
  __REG8  ARLO            : 1;
  __REG8  STOPF           : 1;
  __REG8  AF              : 1;
  __REG8  ENDAD           : 1;
  __REG8                  : 2;
} __i2cnsr2_bits;

/* I2C Clock Control Register (I2Cn_CCR) */
typedef struct {
  __REG8  CC0             : 1;
  __REG8  CC1             : 1;
  __REG8  CC2             : 1;
  __REG8  CC3             : 1;
  __REG8  CC4             : 1;
  __REG8  CC5             : 1;
  __REG8  CC6             : 1;
  __REG8  FM_SM           : 1;
} __i2cnccr_bits;

/* I2C Extended Clock Control Register (I2Cn_ECCR) */
typedef struct {
  __REG8  CC7             : 1;
  __REG8  CC8             : 1;
  __REG8  CC9             : 1;
  __REG8  CC10            : 1;
  __REG8  CC11            : 1;
  __REG8                  : 3;
} __i2cneccr_bits;

/* I2C Own Address Register 1 (I2Cn_OAR1) */
typedef struct {
  __REG8  ADD0            : 1;
  __REG8  ADD1            : 1;
  __REG8  ADD2            : 1;
  __REG8  ADD3            : 1;
  __REG8  ADD4            : 1;
  __REG8  ADD5            : 1;
  __REG8  ADD6            : 1;
  __REG8  ADD7            : 1;
} __i2cnoar1_bits;

/* I2C Own Address Register 2 (I2Cn_OAR2) */
typedef struct {
  __REG8                  : 1;
  __REG8  ADD8            : 1;
  __REG8  ADD9            : 1;
  __REG8                  : 2;
  __REG8  FR0             : 1;
  __REG8  FR1             : 1;
  __REG8  FR2             : 1;
} __i2cnoar2_bits;

/* BSPI Control/Status Register 1 (BSPIn_CSR1) */
typedef struct {
  __REG16  BSPE           : 1;
  __REG16  MSTR           : 1;
  __REG16  RIE            : 2;
  __REG16  REIE           : 1;
  __REG16                 : 2;
  __REG16  BEIE           : 1;
  __REG16  CPOL           : 1;
  __REG16  CPHA           : 1;
  __REG16  WL             : 2;
  __REG16  RFE            : 4;
} __bspincsr1_bits;

/* BSPI Control/Status Register 2 (BSPIn_CSR2) */
typedef struct {
  __REG16  DFIFO          : 1;
  __REG16                 : 1;
  __REG16  BERR           : 1;
  __REG16  RFNE           : 1;
  __REG16  RFF            : 1;
  __REG16  ROFL           : 1;
  __REG16  TFEMPTY        : 1;
  __REG16  TUFL           : 1;
  __REG16  TFF            : 1;
  __REG16  TFNE           : 1;
  __REG16  TFENABLE       : 4;
  __REG16  TIE            : 2;
} __bspincsr2_bits;

/* BSPI Control/Status Register 2 (BSPIn_CSR3) */
typedef struct {
  __REG16  MASK_SS        : 1;
  __REG16  DMA_EN         : 1;
  __REG16  TBURST_LEN     : 2;
  __REG16  RBURST_LEN     : 2;
  __REG16  TREQ_EN        : 1;
  __REG16  RREQ_EN        : 1;
  __REG16                 : 8;
} __bspincsr3_bits;

/* BSPI Master Clock Divider Register (BSPIn_CLK) */
typedef struct {
  __REG16  DIV            : 8;
  __REG16                 : 8;
} __bspinclk_bits;

/* UART TxBuffer Register (UARTn_TxBUFR) */
typedef struct {
  __REG16  TX             : 9;
  __REG16                 : 7;
} __uartntx_bits;

/* UART RxBuffer Register (UARTn_RxBUFR) */
typedef struct {
  __REG16  RX             :10;
  __REG16                 : 6;
} __uartnrx_bits;

/* UART Control Register (UARTn_CR) */
typedef struct {
  __REG16  Mode           : 3;
  __REG16  StopBits       : 2;
  __REG16  ParityOdd      : 1;
  __REG16  LoopBack       : 1;
  __REG16  Run            : 1;
  __REG16  RxEnable       : 1;
  __REG16  SCEnable       : 1;
  __REG16  FifoEnable     : 1;
  __REG16                 : 5;
} __uartncr_bits;

/* UART IntEnable Register (UARTn_IER) */
typedef struct {
  __REG16  RxBufNotEmptyIE   : 1;
  __REG16  TxEmptyIE         : 1;
  __REG16  TxHalfEmptyIE     : 1;
  __REG16  ParityErrorIE     : 1;
  __REG16  FrameErrorIE      : 1;
  __REG16  OverrunErrorIE    : 1;
  __REG16  TimeoutNotEmptyIE : 1;
  __REG16  TimeoutIdleIE     : 1;
  __REG16  RxHalfFullIE      : 1;
  __REG16                    : 7;
} __uartnier_bits;

/* UART Status Register (UARTn_SR) */
typedef struct {
  __REG16  RxBufNotEmpty     : 1;
  __REG16  TxEmpty           : 1;
  __REG16  TxHalfEmpty       : 1;
  __REG16  ParityError       : 1;
  __REG16  FrameError        : 1;
  __REG16  OverrunError      : 1;
  __REG16  TimeoutNotEmpty   : 1;
  __REG16  TimeoutIdle       : 1;
  __REG16  RxHalfFull        : 1;
  __REG16  TxFull            : 1;
  __REG16                    : 6;
} __uartnsr_bits;

/* UART Timeout Register (UARTn_TOR) */
typedef struct {
  __REG16  Timeout        : 8;
  __REG16                 : 8;
} __uartntor_bits;

/* ADC Data Register (ADC_Dx) */
typedef struct {
  __REG16  CDATA          :10;
  __REG16                 : 6;
} __adcdx_bits;

/* Control Logic Register 0 (ADC_CLR0) */
typedef struct {
  __REG16  START          : 1;
  __REG16  CAL            : 1;
  __REG16                 :14;
} __adcclr0_bits;

/* Control Logic Register 1 (ADC_CLR1) */
typedef struct {
  __REG16  SMPP           : 3;
  __REG16                 : 2;
  __REG16  CNVP           : 3;
  __REG16                 : 7;
  __REG16  SPEN           : 1;
} __adcclr1_bits;

/* Control Logic Register 2 (ADC_CLR2) */
typedef struct {
  __REG16  FCH            : 4;
  __REG16                 : 2;
  __REG16  NCH            : 4;
  __REG16                 : 5;
  __REG16  MODE           : 1;
} __adcclr2_bits;

/* Control Logic Register 3 (ADC_CLR3) */
typedef struct {
  __REG16  JFCH           : 4;
  __REG16                 : 2;
  __REG16  JNCH           : 4;
  __REG16                 : 5;
  __REG16  JSTART         : 1;
} __adcclr3_bits;

/* Control Logic Register 4 (ADC_CLR4) */
typedef struct {
  __REG16                 : 5;
  __REG16  NOAVRG         : 1;
  __REG16                 : 8;
  __REG16  ACKO           : 1;
  __REG16  PWDN           : 1;
} __adcclr4_bits;

/* Threshold Registers A (ADC_TRA0 ..3) */
typedef struct {
  __REG16  THRH           :10;
  __REG16  THRCH          : 4;
  __REG16                 : 2;
} __adctrax_bits;

/* Threshold Registers B (ADC_TRB0 ..3) */
typedef struct {
  __REG16  THRL           :10;
  __REG16                 : 5;
  __REG16  THREN          : 1;
} __adctrbx_bits;

/* DMA Channel Enable Register (ADC_DMAR) */
typedef struct {
  __REG16  DMA0           : 1;
  __REG16  DMA1           : 1;
  __REG16  DMA2           : 1;
  __REG16  DMA3           : 1;
  __REG16  DMA4           : 1;
  __REG16  DMA5           : 1;
  __REG16  DMA6           : 1;
  __REG16  DMA7           : 1;
  __REG16  DMA8           : 1;
  __REG16  DMA9           : 1;
  __REG16  DMA10          : 1;
  __REG16  DMA11          : 1;
  __REG16                 : 4;
} __adcdmar_bits;

/* DMA Global Enable Register (ADC_DMAE) */
typedef struct {
  __REG16  DENCH          : 4;
  __REG16                 :11;
  __REG16  DMAEN          : 1;
} __adcdmae_bits;

/* Pending Bit Register (ADC_PBR) */
typedef struct {
  __REG16  ECH            : 1;
  __REG16  EOC            : 1;
  __REG16  JECH           : 1;
  __REG16  JEOC           : 1;
  __REG16  THR0           : 2;
  __REG16  THR1           : 2;
  __REG16  THR2           : 2;
  __REG16  THR3           : 2;
  __REG16                 : 4;
} __adcpbr_bits;

/* Interrupt Mask Register (ADC_IMR) */
typedef struct {
  __REG16  MSKECH         : 1;
  __REG16  MSKEOC         : 1;
  __REG16  MSKJECH        : 1;
  __REG16  MSKJEOC        : 1;
  __REG16  MSK0L          : 1;
  __REG16  MSK0H          : 1;
  __REG16  MSK1L          : 1;
  __REG16  MSK1H          : 1;
  __REG16  MSK2L          : 1;
  __REG16  MSK2H          : 1;
  __REG16  MSK3L          : 1;
  __REG16  MSK3H          : 1;
  __REG16                 : 4;
} __adcimr_bits;

/* Bridge Status Register (APBn_BSR) */
typedef struct {
  __REG32  ABORT          : 1;
  __REG32                 : 3;
  __REG32  OUTM           : 1;
  __REG32  APBT           : 1;
  __REG32                 :26;
} __apbnbsr_bits;

/* Time-out Register (APBn_TOR) */
typedef struct {
  __REG32  TOUT_CNT       : 5;
  __REG32                 : 3;
  __REG32  ABTEN          : 1;
  __REG32                 :23;
} __apbntor_bits;

/* Out of Memory Register (APBn_OMR) */
/* Time-out Error Register (APBn_TOER) */
typedef struct {
  __REG32                 : 7;
  __REG32  nRW            : 1;
  __REG32  PRPHADDR       :16;
  __REG32                 : 8;
} __apbnomr_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/
/***************************************************************************
 **
 ** Clock Monitor Unit CMU
 **
 ***************************************************************************/
__IO_REG16_BIT(CMU_RCCTL,   0xFFFFF600,__READ_WRITE,__cmurcctl_bits);
__IO_REG16_BIT(CMU_FDISP,   0xFFFFF604,__READ_WRITE,__cmufdisp_bits);
__IO_REG16_BIT(CMU_FRH,     0xFFFFF608,__READ_WRITE,__cmufrh_bits);
__IO_REG16_BIT(CMU_FRL,     0xFFFFF60C,__READ_WRITE,__cmufrl_bits);
__IO_REG16_BIT(CMU_CTRL,    0xFFFFF610,__READ_WRITE,__cmuctrl_bits);
__IO_REG16_BIT(CMU_STAT,    0xFFFFF614,__READ      ,__cmustat_bits);
__IO_REG16_BIT(CMU_IS,      0xFFFFF618,__READ_WRITE,__cmuis_bits);
__IO_REG16_BIT(CMU_IM,      0xFFFFF61C,__READ_WRITE,__cmuim_bits);
__IO_REG16_BIT(CMU_EOCV,    0xFFFFF620,__READ_WRITE,__cmueocv_bits);
__IO_REG16(    CMU_WE,      0xFFFFF624,__WRITE);

/***************************************************************************
 **
 **  PRCCU
 **
 ***************************************************************************/
__IO_REG32_BIT(PRCCU_CCR,    0x60000000,__READ_WRITE,__prccuccr_bits);
__IO_REG32_BIT(PRCCU_VRCTR,  0x60000004,__READ_WRITE,__prccuvrctr_bits);
__IO_REG32_BIT(PRCCU_CFR,    0x60000008,__READ_WRITE,__prccucfr_bits);
__IO_REG32_BIT(PRCCU_PLLCR,  0x60000018,__READ_WRITE,__prccupllcr_bits);
__IO_REG32_BIT(PRCCU_SMR,    0x60000020,__READ_WRITE,__prccusmr_bits);
__IO_REG32_BIT(PRCCU_RTCPR,  0X60000028,__READ_WRITE,__prccurtcpr_bits);

/***************************************************************************
 **
 **  CFG
 **
 ***************************************************************************/
__IO_REG32_BIT(CFG_R0,       0x40000000,__READ_WRITE,__cfgr0_bits);
__IO_REG32_BIT(CFG_EITE0,    0x40000004,__READ_WRITE,__cfgeite0_bits);
__IO_REG32_BIT(CFG_PCGR0,    0x40000008,__READ_WRITE,__cfg_pcgr0_bits);
__IO_REG32_BIT(CFG_PCGR1,    0x4000000C,__READ_WRITE,__cfg_pcgr1_bits);
__IO_REG32_BIT(CFG_PECGR0,   0x40000010,__READ_WRITE,__cfg_pcgr0_bits);
__IO_REG32_BIT(CFG_PECGR1,   0x40000014,__READ_WRITE,__cfg_pcgr1_bits);
__IO_REG32_BIT(CFG_PCGRB0,   0x40000018,__READ_WRITE,__cfg_pcgr0_bits);
__IO_REG32_BIT(CFG_PCGRB1,   0x4000001C,__READ_WRITE,__cfg_pcgr1_bits);
__IO_REG32_BIT(CFG_TIMSR,    0x40000020,__READ_WRITE,__cfgtimsr_bits);
__IO_REG32_BIT(CFG_EITE1,    0x40000024,__READ_WRITE,__cfgeite1_bits);
__IO_REG32_BIT(CFG_EITE2,    0x40000028,__READ_WRITE,__cfgeite2_bits);
__IO_REG32_BIT(CFG_ESPR,     0x4000002C,__READ_WRITE,__cfgespr_bits);
__IO_REG32_BIT(CFG_R1,       0x40000030,__READ_WRITE,__cfgr1_bits);
__IO_REG32(    CFG_DIDR,     0x40000034,__READ);

/***************************************************************************
 **
 ** GPIO PORT 0
 **
 ***************************************************************************/
__IO_REG16_BIT(GPIOPORT0_PC0, 0xFFFFD400,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT0_PC1, 0xFFFFD404,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT0_PC2, 0xFFFFD408,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT0_PD,  0xFFFFD40C,__READ_WRITE,__BITS16);

/***************************************************************************
 **
 ** GPIO PORT 1
 **
 ***************************************************************************/
__IO_REG16_BIT(GPIOPORT1_PC0, 0xFFFFD410,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT1_PC1, 0xFFFFD414,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT1_PC2, 0xFFFFD418,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT1_PD,  0xFFFFD41C,__READ_WRITE,__BITS16);

/***************************************************************************
 **
 ** GPIO PORT 2
 **
 ***************************************************************************/
__IO_REG16_BIT(GPIOPORT2_PC0, 0xFFFFD420,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT2_PC1, 0xFFFFD424,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT2_PC2, 0xFFFFD428,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT2_PD,  0xFFFFD42C,__READ_WRITE,__BITS16);

/***************************************************************************
 **
 ** GPIO PORT 3
 **
 ***************************************************************************/
__IO_REG16_BIT(GPIOPORT3_PC0, 0xFFFFD430,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT3_PC1, 0xFFFFD434,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT3_PC2, 0xFFFFD438,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT3_PD,  0xFFFFD43C,__READ_WRITE,__BITS16);

/***************************************************************************
 **
 ** GPIO PORT 4
 **
 ***************************************************************************/
__IO_REG16_BIT(GPIOPORT4_PC0, 0xFFFFD440,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT4_PC1, 0xFFFFD444,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT4_PC2, 0xFFFFD448,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT4_PD,  0xFFFFD44C,__READ_WRITE,__BITS16);

/***************************************************************************
 **
 ** GPIO PORT 5
 **
 ***************************************************************************/
__IO_REG16_BIT(GPIOPORT5_PC0, 0xFFFFD450,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT5_PC1, 0xFFFFD454,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT5_PC2, 0xFFFFD458,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT5_PD,  0xFFFFD45C,__READ_WRITE,__BITS16);

/***************************************************************************
 **
 ** GPIO PORT 6
 **
 ***************************************************************************/
__IO_REG16_BIT(GPIOPORT6_PC0, 0xFFFFD460,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT6_PC1, 0xFFFFD464,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT6_PC2, 0xFFFFD468,__READ_WRITE,__BITS16);
__IO_REG16_BIT(GPIOPORT6_PD,  0xFFFFD46C,__READ_WRITE,__BITS16);

/***************************************************************************
 **
 ** Enhanced Interrupt Controller EIC
 **
 ***************************************************************************/
__IO_REG32_BIT(EIC_ICR,     0xFFFFFC00,__READ_WRITE,__eicicr_bits);
__IO_REG32_BIT(EIC_CICR,    0xFFFFFC04,__READ,      __eiccicr_bits);
__IO_REG32_BIT(EIC_CIPR,    0xFFFFFC08,__READ_WRITE,__eiccipr_bits);
__IO_REG32_BIT(EIC_IVR,     0xFFFFFC18,__READ_WRITE,__eicivr_bits);
__IO_REG32_BIT(EIC_FIER,    0xFFFFFC10,__READ_WRITE,__eicfier_bits);
__IO_REG32_BIT(EIC_FIPR,    0xFFFFFC14,__READ_WRITE,__eicfipr_bits);
__IO_REG32_BIT(EIC_FIR,     0xFFFFFC1C,__READ_WRITE,__eicfir_bits);
__IO_REG32_BIT(EIC_IER0,    0xFFFFFC20,__READ_WRITE,__eicier0_bits);
__IO_REG32_BIT(EIC_IER1,    0xFFFFFC24,__READ_WRITE,__eicier1_bits);
__IO_REG32_BIT(EIC_IPR0,    0xFFFFFC40,__READ_WRITE,__eicipr0_bits);
__IO_REG32_BIT(EIC_IPR1,    0xFFFFFC44,__READ_WRITE,__eicipr1_bits);
__IO_REG32_BIT(EIC_SIR0,    0xFFFFFC60,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR1,    0xFFFFFC64,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR2,    0xFFFFFC68,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR3,    0xFFFFFC6C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR4,    0xFFFFFC70,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR5,    0xFFFFFC74,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR6,    0xFFFFFC78,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR7,    0xFFFFFC7C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR8,    0xFFFFFC80,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR9,    0xFFFFFC84,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR10,   0xFFFFFC88,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR11,   0xFFFFFC8C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR12,   0xFFFFFC90,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR13,   0xFFFFFC94,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR14,   0xFFFFFC98,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR15,   0xFFFFFC9C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR16,   0xFFFFFCA0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR17,   0xFFFFFCA4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR18,   0xFFFFFCA8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR19,   0xFFFFFCAC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR20,   0xFFFFFCB0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR21,   0xFFFFFCB4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR22,   0xFFFFFCB8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR23,   0xFFFFFCBC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR24,   0xFFFFFCC0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR25,   0xFFFFFCC4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR26,   0xFFFFFCC8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR27,   0xFFFFFCCC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR28,   0xFFFFFCD0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR29,   0xFFFFFCD4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR30,   0xFFFFFCD8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR31,   0xFFFFFCDC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR32,   0xFFFFFCE0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR33,   0xFFFFFCE4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR34,   0xFFFFFCE8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR35,   0xFFFFFCEC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR36,   0xFFFFFCF0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR37,   0xFFFFFCF4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR38,   0xFFFFFCF8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR39,   0xFFFFFCFC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR40,   0xFFFFFD00,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR41,   0xFFFFFD04,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR42,   0xFFFFFD08,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR43,   0xFFFFFD0C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR44,   0xFFFFFD10,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR45,   0xFFFFFD14,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR46,   0xFFFFFD18,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR47,   0xFFFFFD1C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR48,   0xFFFFFD20,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR49,   0xFFFFFD24,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR50,   0xFFFFFD28,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR51,   0xFFFFFD2C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR52,   0xFFFFFD30,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR53,   0xFFFFFD34,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR54,   0xFFFFFD38,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR55,   0xFFFFFD3C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR56,   0xFFFFFD40,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR57,   0xFFFFFD44,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR58,   0xFFFFFD48,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR59,   0xFFFFFD4C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR60,   0xFFFFFD50,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR61,   0xFFFFFD54,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR62,   0xFFFFFD58,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR63,   0xFFFFFD5C,__READ_WRITE,__eicsirn_bits);

/***************************************************************************
 **
 ** NATIVE BUS ARBITER (ARB)
 **
 ***************************************************************************/
__IO_REG32_BIT(ARB_TOR,     0x20000000,__READ_WRITE,__arbtor_bits);
__IO_REG32_BIT(ARB_PRIOR,   0x20000004,__READ_WRITE,__arbprior_bits);
__IO_REG32_BIT(ARB_CTRL,    0x2000000C,__READ_WRITE,__arbctlr_bits);

/***************************************************************************
 **
 **  FLASH
 **
 ***************************************************************************/
__IO_REG32_BIT(FLASH_CR0,   0x80000000,__READ_WRITE,__flashctrl0_bits);
__IO_REG32_BIT(FLASH_CR1,   0x80000004,__READ_WRITE,__flashctrl1_bits);
__IO_REG32(    FLASH_DR0,   0x80000008,__READ_WRITE);
__IO_REG32(    FLASH_DR1,   0x8000000C,__READ_WRITE);
__IO_REG32_BIT(FLASH_AR,    0x80000010,__READ_WRITE,__flashadd_bits);
__IO_REG32_BIT(FLASH_ER,    0x80000014,__READ_WRITE,__flasherr_bits);
__IO_REG32_BIT(FLASH_NVWPAR,0x8000DFB0,__READ_WRITE,__flashwrprot_bits);
__IO_REG32_BIT(FLASH_NVAPR0,0x8000DFB8,__READ_WRITE,__flashaccprot0_bits);
__IO_REG32_BIT(FLASH_NVAPR1,0x8000DFBC,__READ_WRITE,__flashaccprot1_bits);

/***************************************************************************
 **
 ** APB0 Bridge Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(APB0_BSR,    0xFFFF8000,__READ_WRITE,__apbnbsr_bits);
__IO_REG32_BIT(APB0_TOR,    0xFFFF8004,__READ_WRITE,__apbntor_bits);
__IO_REG32_BIT(APB0_OMR,    0xFFFF8008,__READ,      __apbnomr_bits);
__IO_REG32_BIT(APB0_TOER,   0xFFFF800C,__READ,      __apbnomr_bits);

/***************************************************************************
 **
 ** I2C0
 **
 ***************************************************************************/
__IO_REG8_BIT(I2C0_CR,      0xFFFF8400,__READ_WRITE,__i2cncr_bits);
__IO_REG8_BIT(I2C0_SR1,     0xFFFF8404,__READ      ,__i2cnsr1_bits);
__IO_REG8_BIT(I2C0_SR2,     0xFFFF8408,__READ      ,__i2cnsr2_bits);
__IO_REG8_BIT(I2C0_CCR,     0xFFFF840C,__READ_WRITE,__i2cnccr_bits);
__IO_REG8_BIT(I2C0_OAR1,    0xFFFF8410,__READ_WRITE,__i2cnoar1_bits);
__IO_REG8_BIT(I2C0_OAR2,    0xFFFF8414,__READ_WRITE,__i2cnoar2_bits);
__IO_REG8(    I2C0_DR,      0xFFFF8418,__READ_WRITE);
__IO_REG8_BIT(I2C0_ECCR,    0xFFFF841C,__READ_WRITE,__i2cneccr_bits);

/***************************************************************************
 **
 ** I2C1
 **
 ***************************************************************************/
__IO_REG8_BIT(I2C1_CR,      0xFFFF8800,__READ_WRITE,__i2cncr_bits);
__IO_REG8_BIT(I2C1_SR1,     0xFFFF8804,__READ      ,__i2cnsr1_bits);
__IO_REG8_BIT(I2C1_SR2,     0xFFFF8808,__READ      ,__i2cnsr2_bits);
__IO_REG8_BIT(I2C1_CCR,     0xFFFF880C,__READ_WRITE,__i2cnccr_bits);
__IO_REG8_BIT(I2C1_OAR1,    0xFFFF8810,__READ_WRITE,__i2cnoar1_bits);
__IO_REG8_BIT(I2C1_OAR2,    0xFFFF8814,__READ_WRITE,__i2cnoar2_bits);
__IO_REG8(    I2C1_DR,      0xFFFF8818,__READ_WRITE);
__IO_REG8_BIT(I2C1_ECCR,    0xFFFF881C,__READ_WRITE,__i2cneccr_bits);

/***************************************************************************
 **
 ** Timebase (TB)
 **
 ***************************************************************************/
__IO_REG16_BIT(TB0_CR,      0xFFFF9800,__READ_WRITE,__tbncr_bits);
__IO_REG16_BIT(TB0_PR,      0xFFFF9804,__READ_WRITE,__tbnpr_bits);
__IO_REG16(    TB0_VR,      0xFFFF9808,__READ_WRITE);
__IO_REG16(    TB0_CNT,     0xFFFF980C,__READ);
__IO_REG16_BIT(TB0_SR,      0xFFFF9810,__READ_WRITE,__tbnsr_bits);
__IO_REG16_BIT(TB0_MR,      0xFFFF9814,__READ_WRITE,__tbnmr_bits);
__IO_REG16_BIT(TB1_CR,      0xFFFF9900,__READ_WRITE,__tbncr_bits);
__IO_REG16_BIT(TB1_PR,      0xFFFF9904,__READ_WRITE,__tbnpr_bits);
__IO_REG16(    TB1_VR,      0xFFFF9908,__READ_WRITE);
__IO_REG16(    TB1_CNT,     0xFFFF990C,__READ);
__IO_REG16_BIT(TB1_SR,      0xFFFF9910,__READ_WRITE,__tbnsr_bits);
__IO_REG16_BIT(TB1_MR,      0xFFFF9914,__READ_WRITE,__tbnmr_bits);
__IO_REG16_BIT(TB2_CR,      0xFFFF9A00,__READ_WRITE,__tbncr_bits);
__IO_REG16_BIT(TB2_PR,      0xFFFF9A04,__READ_WRITE,__tbnpr_bits);
__IO_REG16(    TB2_VR,      0xFFFF9A08,__READ_WRITE);
__IO_REG16(    TB2_CNT,     0xFFFF9A0C,__READ);
__IO_REG16_BIT(TB2_SR,      0xFFFF9A10,__READ_WRITE,__tbnsr_bits);
__IO_REG16_BIT(TB2_MR,      0xFFFF9A14,__READ_WRITE,__tbnmr_bits);

/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/
__IO_REG16(    UART0_BR,    0xFFFF9C00,__READ_WRITE);
__IO_REG16_BIT(UART0_TXBUFR,0xFFFF9C04,__WRITE     ,__uartntx_bits);
__IO_REG16_BIT(UART0_RXBUFR,0xFFFF9C08,__READ      ,__uartnrx_bits);
__IO_REG16_BIT(UART0_CR,    0xFFFF9C0C,__READ_WRITE,__uartncr_bits);
__IO_REG16_BIT(UART0_IER,   0xFFFF9C10,__READ_WRITE,__uartnier_bits);
__IO_REG16_BIT(UART0_SR,    0xFFFF9C14,__READ      ,__uartnsr_bits);
__IO_REG16_BIT(UART0_TOR,   0xFFFF9C1C,__READ_WRITE,__uartntor_bits);
__IO_REG16(    UART0_TXRSTR,0xFFFF9C20,__WRITE);
__IO_REG16(    UART0_RXRSTR,0xFFFF9C24,__WRITE);

/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG16(    UART2_BR,    0xFFFF9E00,__READ_WRITE);
__IO_REG16_BIT(UART2_TXBUFR,0xFFFF9E04,__WRITE     ,__uartntx_bits);
__IO_REG16_BIT(UART2_RXBUFR,0xFFFF9E08,__READ      ,__uartnrx_bits);
__IO_REG16_BIT(UART2_CR,    0xFFFF9E0C,__READ_WRITE,__uartncr_bits);
__IO_REG16_BIT(UART2_IER,   0xFFFF9E10,__READ_WRITE,__uartnier_bits);
__IO_REG16_BIT(UART2_SR,    0xFFFF9E14,__READ      ,__uartnsr_bits);
__IO_REG16_BIT(UART2_TOR,   0xFFFF9E1C,__READ_WRITE,__uartntor_bits);
__IO_REG16(    UART2_TXRSTR,0xFFFF9E20,__WRITE);
__IO_REG16(    UART2_RXRSTR,0xFFFF9E24,__WRITE);

/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG16(    UART1_BR,    0xFFFFA000,__READ_WRITE);
__IO_REG16_BIT(UART1_TXBUFR,0xFFFFA004,__WRITE     ,__uartntx_bits);
__IO_REG16_BIT(UART1_RXBUFR,0xFFFFA008,__READ      ,__uartnrx_bits);
__IO_REG16_BIT(UART1_CR,    0xFFFFA00C,__READ_WRITE,__uartncr_bits);
__IO_REG16_BIT(UART1_IER,   0xFFFFA010,__READ_WRITE,__uartnier_bits);
__IO_REG16_BIT(UART1_SR,    0xFFFFA014,__READ      ,__uartnsr_bits);
__IO_REG16_BIT(UART1_TOR,   0xFFFFA01C,__READ_WRITE,__uartntor_bits);
__IO_REG16(    UART1_TXRSTR,0xFFFFA020,__WRITE);
__IO_REG16(    UART1_RXRSTR,0xFFFFA024,__WRITE);

/***************************************************************************
 **
 **  UART3
 **
 ***************************************************************************/
__IO_REG16(    UART3_BR,    0xFFFFA200,__READ_WRITE);
__IO_REG16_BIT(UART3_TXBUFR,0xFFFFA204,__WRITE     ,__uartntx_bits);
__IO_REG16_BIT(UART3_RXBUFR,0xFFFFA208,__READ      ,__uartnrx_bits);
__IO_REG16_BIT(UART3_CR,    0xFFFFA20C,__READ_WRITE,__uartncr_bits);
__IO_REG16_BIT(UART3_IER,   0xFFFFA210,__READ_WRITE,__uartnier_bits);
__IO_REG16_BIT(UART3_SR,    0xFFFFA214,__READ      ,__uartnsr_bits);
__IO_REG16_BIT(UART3_TOR,   0xFFFFA21C,__READ_WRITE,__uartntor_bits);
__IO_REG16(    UART3_TXRSTR,0xFFFFA220,__WRITE);
__IO_REG16(    UART3_RXRSTR,0xFFFFA224,__WRITE);

/***************************************************************************
 **
 ** WDG
 **
 ***************************************************************************/
__IO_REG16_BIT(WDG_CR,      0xFFFFA400,__READ_WRITE,__wdgcr_bits);
__IO_REG16_BIT(WDG_PR,      0xFFFFA404,__READ_WRITE,__wdgpr_bits);
__IO_REG16(    WDG_VR,      0xFFFFA408,__READ_WRITE);
__IO_REG16(    WDG_CNT,     0xFFFFA40C,__READ);
__IO_REG16_BIT(WDG_SR,      0xFFFFA410,__READ_WRITE,__wdgsr_bits);
__IO_REG16_BIT(WDG_MR,      0xFFFFA414,__READ_WRITE,__wdgmr_bits);
__IO_REG16(    WDG_KR,      0xFFFFA418,__READ_WRITE);

/***************************************************************************
 **
 ** Wake-Up Timer (WUT)
 **
 ***************************************************************************/
__IO_REG16_BIT(WUT_CR,      0xFFFFA600,__READ_WRITE,__wutcr_bits);
__IO_REG16_BIT(WUT_PR,      0xFFFFA604,__READ_WRITE,__wutpr_bits);
__IO_REG16(    WUT_VR,      0xFFFFA608,__READ_WRITE);
__IO_REG16(    WUT_CNT,     0xFFFFA60C,__READ);
__IO_REG16_BIT(WUT_SR,      0xFFFFA610,__READ_WRITE,__wutsr_bits);
__IO_REG16_BIT(WUT_MR,      0xFFFFA614,__READ_WRITE,__wutmr_bits);

/***************************************************************************
 **
 ** TIMER0 (TIM0)
 **
 ***************************************************************************/
__IO_REG16(    TIM0_ICAR,   0xFFFFA800,__READ);
__IO_REG16(    TIM0_ICBR,   0xFFFFA804,__READ);
__IO_REG16(    TIM0_OCAR,   0xFFFFA808,__READ_WRITE);
__IO_REG16(    TIM0_OCBR,   0xFFFFA80C,__READ_WRITE);
__IO_REG16(    TIM0_CNTR,   0xFFFFA810,__READ);
__IO_REG16_BIT(TIM0_CR1,    0xFFFFA814,__READ_WRITE,__timcr1_bits);
__IO_REG16_BIT(TIM0_CR2,    0xFFFFA818,__READ_WRITE,__timcr2_bits);
__IO_REG16_BIT(TIM0_SR,     0xFFFFA81C,__READ_WRITE,__timsr_bits);

/***************************************************************************
 **
 ** TIMER1 (TIM1)
 **
 ***************************************************************************/
__IO_REG16(    TIM1_ICAR,   0xFFFFAC00,__READ);
__IO_REG16(    TIM1_ICBR,   0xFFFFAC04,__READ);
__IO_REG16(    TIM1_OCAR,   0xFFFFAC08,__READ_WRITE);
__IO_REG16(    TIM1_OCBR,   0xFFFFAC0C,__READ_WRITE);
__IO_REG16(    TIM1_CNTR,   0xFFFFAC10,__READ);
__IO_REG16_BIT(TIM1_CR1,    0xFFFFAC14,__READ_WRITE,__timcr1_bits);
__IO_REG16_BIT(TIM1_CR2,    0xFFFFAC18,__READ_WRITE,__timcr2_bits);
__IO_REG16_BIT(TIM1_SR,     0xFFFFAC1C,__READ_WRITE,__timsr_bits);

/***************************************************************************
 **
 ** TIMER5 (TIM5)
 **
 ***************************************************************************/
__IO_REG16(    TIM5_ICAR,   0xFFFFB000,__READ);
__IO_REG16(    TIM5_ICBR,   0xFFFFB004,__READ);
__IO_REG16(    TIM5_OCAR,   0xFFFFB008,__READ_WRITE);
__IO_REG16(    TIM5_OCBR,   0xFFFFB00C,__READ_WRITE);
__IO_REG16(    TIM5_CNTR,   0xFFFFB010,__READ);
__IO_REG16_BIT(TIM5_CR1,    0xFFFFB014,__READ_WRITE,__timcr1_bits);
__IO_REG16_BIT(TIM5_CR2,    0xFFFFB018,__READ_WRITE,__timcr2_bits);
__IO_REG16_BIT(TIM5_SR,     0xFFFFB01C,__READ_WRITE,__timsr_bits);

/***************************************************************************
 **
 ** Wake-up Interrupt Unit (WIU)
 **
 ***************************************************************************/
__IO_REG32_BIT(WIU_CTRL,    0xFFFFB800,__READ_WRITE,__wiuctrl_bits);
__IO_REG32_BIT(WIU_MR,      0xFFFFB804,__READ_WRITE,__wiumr_bits);
__IO_REG32_BIT(WIU_TR,      0xFFFFB808,__READ_WRITE,__wiutr_bits);
__IO_REG32_BIT(WIU_PR,      0xFFFFB80C,__READ_WRITE,__wiupr_bits);
__IO_REG32_BIT(WIU_INTR,    0xFFFFB810,__READ_WRITE,__wiuintr_bits);

/***************************************************************************
 **
 ** APB1 Bridge Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(APB1_BSR,    0xFFFFC000,__READ_WRITE,__apbnbsr_bits);
__IO_REG32_BIT(APB1_TOR,    0xFFFFC004,__READ_WRITE,__apbntor_bits);
__IO_REG32_BIT(APB1_OMR,    0xFFFFC008,__READ,      __apbnomr_bits);
__IO_REG32_BIT(APB1_TOER,   0xFFFFC00C,__READ,      __apbnomr_bits);

/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/
__IO_REG16_BIT(PWM0_PRS0,    0xFFFFD000,__READ_WRITE,__pwmnprs0_bits);
__IO_REG16_BIT(PWM0_PRS1,    0xFFFFD004,__READ_WRITE,__pwmnprs1_bits);
__IO_REG16_BIT(PWM0_PEN,     0xFFFFD008,__READ_WRITE,__pwmnpen_bits);
__IO_REG16_BIT(PWM0_PLS,     0xFFFFD00C,__READ_WRITE,__pwmnpls_bits);
__IO_REG16_BIT(PWM0_CPI,     0xFFFFD010,__READ_WRITE,__pwmncpi_bits);
__IO_REG16_BIT(PWM0_IM,      0xFFFFD014,__READ_WRITE,__pwmnim_bits);
__IO_REG16(    PWM0_DUT,     0xFFFFD01C,__READ_WRITE);
__IO_REG16(    PWM0_PER,     0xFFFFD020,__READ_WRITE);
__IO_REG16_BIT(PWM1_PRS0,    0xFFFFD040,__READ_WRITE,__pwmnprs0_bits);
__IO_REG16_BIT(PWM1_PRS1,    0xFFFFD044,__READ_WRITE,__pwmnprs1_bits);
__IO_REG16_BIT(PWM1_PEN,     0xFFFFD048,__READ_WRITE,__pwmnpen_bits);
__IO_REG16_BIT(PWM1_PLS,     0xFFFFD04C,__READ_WRITE,__pwmnpls_bits);
__IO_REG16_BIT(PWM1_CPI,     0xFFFFD050,__READ_WRITE,__pwmncpi_bits);
__IO_REG16_BIT(PWM1_IM,      0xFFFFD054,__READ_WRITE,__pwmnim_bits);
__IO_REG16(    PWM1_DUT,     0xFFFFD05C,__READ_WRITE);
__IO_REG16(    PWM1_PER,     0xFFFFD060,__READ_WRITE);
__IO_REG16_BIT(PWM2_PRS0,    0xFFFFD080,__READ_WRITE,__pwmnprs0_bits);
__IO_REG16_BIT(PWM2_PRS1,    0xFFFFD084,__READ_WRITE,__pwmnprs1_bits);
__IO_REG16_BIT(PWM2_PEN,     0xFFFFD088,__READ_WRITE,__pwmnpen_bits);
__IO_REG16_BIT(PWM2_PLS,     0xFFFFD08C,__READ_WRITE,__pwmnpls_bits);
__IO_REG16_BIT(PWM2_CPI,     0xFFFFD090,__READ_WRITE,__pwmncpi_bits);
__IO_REG16_BIT(PWM2_IM,      0xFFFFD094,__READ_WRITE,__pwmnim_bits);
__IO_REG16(    PWM2_DUT,     0xFFFFD09C,__READ_WRITE);
__IO_REG16(    PWM2_PER,     0xFFFFD0A0,__READ_WRITE);
__IO_REG16_BIT(PWM3_PRS0,    0xFFFFD0C0,__READ_WRITE,__pwmnprs0_bits);
__IO_REG16_BIT(PWM3_PRS1,    0xFFFFD0C4,__READ_WRITE,__pwmnprs1_bits);
__IO_REG16_BIT(PWM3_PEN,     0xFFFFD0C8,__READ_WRITE,__pwmnpen_bits);
__IO_REG16_BIT(PWM3_PLS,     0xFFFFD0CC,__READ_WRITE,__pwmnpls_bits);
__IO_REG16_BIT(PWM3_CPI,     0xFFFFD0D0,__READ_WRITE,__pwmncpi_bits);
__IO_REG16_BIT(PWM3_IM,      0xFFFFD0D4,__READ_WRITE,__pwmnim_bits);
__IO_REG16(    PWM3_DUT,     0xFFFFD0DC,__READ_WRITE);
__IO_REG16(    PWM3_PER,     0xFFFFD0E0,__READ_WRITE);
__IO_REG16_BIT(PWM4_PRS0,    0xFFFFD100,__READ_WRITE,__pwmnprs0_bits);
__IO_REG16_BIT(PWM4_PRS1,    0xFFFFD104,__READ_WRITE,__pwmnprs1_bits);
__IO_REG16_BIT(PWM4_PEN,     0xFFFFD108,__READ_WRITE,__pwmnpen_bits);
__IO_REG16_BIT(PWM4_PLS,     0xFFFFD10C,__READ_WRITE,__pwmnpls_bits);
__IO_REG16_BIT(PWM4_CPI,     0xFFFFD110,__READ_WRITE,__pwmncpi_bits);
__IO_REG16_BIT(PWM4_IM,      0xFFFFD114,__READ_WRITE,__pwmnim_bits);
__IO_REG16(    PWM4_DUT,     0xFFFFD11C,__READ_WRITE);
__IO_REG16(    PWM4_PER,     0xFFFFD120,__READ_WRITE);
__IO_REG16_BIT(PWM5_PRS0,    0xFFFFD140,__READ_WRITE,__pwmnprs0_bits);
__IO_REG16_BIT(PWM5_PRS1,    0xFFFFD144,__READ_WRITE,__pwmnprs1_bits);
__IO_REG16_BIT(PWM5_PEN,     0xFFFFD148,__READ_WRITE,__pwmnpen_bits);
__IO_REG16_BIT(PWM5_PLS,     0xFFFFD14C,__READ_WRITE,__pwmnpls_bits);
__IO_REG16_BIT(PWM5_CPI,     0xFFFFD150,__READ_WRITE,__pwmncpi_bits);
__IO_REG16_BIT(PWM5_IM,      0xFFFFD154,__READ_WRITE,__pwmnim_bits);
__IO_REG16(    PWM5_DUT,     0xFFFFD15C,__READ_WRITE);
__IO_REG16(    PWM5_PER,     0xFFFFD160,__READ_WRITE);

/***************************************************************************
 **
 **  BSPI0
 **
 ***************************************************************************/
__IO_REG16(     BSPI0_RXR,    0xFFFFD800,__READ);
__IO_REG16(     BSPI0_TXR,    0xFFFFD804,__WRITE);
__IO_REG16_BIT(BSPI0_CSR1,    0xFFFFD808,__READ_WRITE,__bspincsr1_bits);
__IO_REG16_BIT(BSPI0_CSR2,    0xFFFFD80C,__READ_WRITE,__bspincsr2_bits);
__IO_REG16_BIT(BSPI0_CLK,     0xFFFFD810,__READ_WRITE,__bspinclk_bits);
__IO_REG16_BIT(BSPI0_CSR3,    0xFFFFD814,__READ_WRITE,__bspincsr3_bits);

/***************************************************************************
 **
 **  BSPI1
 **
 ***************************************************************************/
__IO_REG16(     BSPI1_RXR,    0xFFFFDC00,__READ);
__IO_REG16(     BSPI1_TXR,    0xFFFFDC04,__WRITE);
__IO_REG16_BIT(BSPI1_CSR1,    0xFFFFDC08,__READ_WRITE,__bspincsr1_bits);
__IO_REG16_BIT(BSPI1_CSR2,    0xFFFFDC0C,__READ_WRITE,__bspincsr2_bits);
__IO_REG16_BIT(BSPI1_CLK,     0xFFFFDC10,__READ_WRITE,__bspinclk_bits);
__IO_REG16_BIT(BSPI1_CSR3,    0xFFFFDC14,__READ_WRITE,__bspincsr3_bits);

/***************************************************************************
 **
 **  BSPI2
 **
 ***************************************************************************/
__IO_REG16(     BSPI2_RXR,    0xFFFFE000,__READ);
__IO_REG16(     BSPI2_TXR,    0xFFFFE004,__WRITE);
__IO_REG16_BIT(BSPI2_CSR1,    0xFFFFE008,__READ_WRITE,__bspincsr1_bits);
__IO_REG16_BIT(BSPI2_CSR2,    0xFFFFE00C,__READ_WRITE,__bspincsr2_bits);
__IO_REG16_BIT(BSPI2_CLK,     0xFFFFE010,__READ_WRITE,__bspinclk_bits);
__IO_REG16_BIT(BSPI2_CSR3,    0xFFFFE014,__READ_WRITE,__bspincsr3_bits);

/***************************************************************************
 **
 ** TIMER2 (TIM2)
 **
 ***************************************************************************/
__IO_REG16(    TIM2_ICAR,   0xFFFFE400,__READ);
__IO_REG16(    TIM2_ICBR,   0xFFFFE404,__READ);
__IO_REG16(    TIM2_OCAR,   0xFFFFE408,__READ_WRITE);
__IO_REG16(    TIM2_OCBR,   0xFFFFE40C,__READ_WRITE);
__IO_REG16(    TIM2_CNTR,   0xFFFFE410,__READ);
__IO_REG16_BIT(TIM2_CR1,    0xFFFFE414,__READ_WRITE,__timcr1_bits);
__IO_REG16_BIT(TIM2_CR2,    0xFFFFE418,__READ_WRITE,__timcr2_bits);
__IO_REG16_BIT(TIM2_SR,     0xFFFFE41C,__READ_WRITE,__timsr_bits);

/***************************************************************************
 **
 ** TIMER3 (TIM3)
 **
 ***************************************************************************/
__IO_REG16(    TIM3_ICAR,   0xFFFFE800,__READ);
__IO_REG16(    TIM3_ICBR,   0xFFFFE804,__READ);
__IO_REG16(    TIM3_OCAR,   0xFFFFE808,__READ_WRITE);
__IO_REG16(    TIM3_OCBR,   0xFFFFE80C,__READ_WRITE);
__IO_REG16(    TIM3_CNTR,   0xFFFFE810,__READ);
__IO_REG16_BIT(TIM3_CR1,    0xFFFFE814,__READ_WRITE,__timcr1_bits);
__IO_REG16_BIT(TIM3_CR2,    0xFFFFE818,__READ_WRITE,__timcr2_bits);
__IO_REG16_BIT(TIM3_SR,     0xFFFFE81C,__READ_WRITE,__timsr_bits);

/***************************************************************************
 **
 ** TIMER4 (TIM4)
 **
 ***************************************************************************/
__IO_REG16(    TIM4_ICAR,   0xFFFFEC00,__READ);
__IO_REG16(    TIM4_ICBR,   0xFFFFEC04,__READ);
__IO_REG16(    TIM4_OCAR,   0xFFFFEC08,__READ_WRITE);
__IO_REG16(    TIM4_OCBR,   0xFFFFEC0C,__READ_WRITE);
__IO_REG16(    TIM4_CNTR,   0xFFFFEC10,__READ);
__IO_REG16_BIT(TIM4_CR1,    0xFFFFEC14,__READ_WRITE,__timcr1_bits);
__IO_REG16_BIT(TIM4_CR2,    0xFFFFEC18,__READ_WRITE,__timcr2_bits);
__IO_REG16_BIT(TIM4_SR,     0xFFFFEC1C,__READ_WRITE,__timsr_bits);

/***************************************************************************
 **
 ** DMA 0
 **
 ***************************************************************************/
__IO_REG16(DMA0_SOURCEL0,   0xFFFFF000,__READ_WRITE);
__IO_REG16(DMA0_SOURCEH0,   0xFFFFF004,__READ_WRITE);
__IO_REG16(DMA0_DESTL0,     0xFFFFF008,__READ_WRITE);
__IO_REG16(DMA0_DESTH0,     0xFFFFF00C,__READ_WRITE);
__IO_REG16(DMA0_MAX0,       0xFFFFF010,__READ_WRITE);
__IO_REG16_BIT(DMA0_CTRL0,  0xFFFFF014,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA0_SOCURRH0,   0xFFFFF018,__READ);
__IO_REG16(DMA0_SOCURRL0,   0xFFFFF01C,__READ);
__IO_REG16(DMA0_DECURRH0,   0xFFFFF020,__READ);
__IO_REG16(DMA0_DECURRL0,   0xFFFFF024,__READ);
__IO_REG16(DMA0_TCNT0,      0xFFFFF028,__READ);
__IO_REG16(DMA0_LUBuff0,    0xFFFFF02C,__READ);
__IO_REG16(DMA0_SOURCEL1,   0xFFFFF040,__READ_WRITE);
__IO_REG16(DMA0_SOURCEH1,   0xFFFFF044,__READ_WRITE);
__IO_REG16(DMA0_DESTL1,     0xFFFFF048,__READ_WRITE);
__IO_REG16(DMA0_DESTH1,     0xFFFFF04C,__READ_WRITE);
__IO_REG16(DMA0_MAX1,       0xFFFFF050,__READ_WRITE);
__IO_REG16_BIT(DMA0_CTRL1,  0xFFFFF054,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA0_SOCURRH1,   0xFFFFF058,__READ);
__IO_REG16(DMA0_SOCURRL1,   0xFFFFF05C,__READ);
__IO_REG16(DMA0_DECURRH1,   0xFFFFF060,__READ);
__IO_REG16(DMA0_DECURRL1,   0xFFFFF064,__READ);
__IO_REG16(DMA0_TCNT1,      0xFFFFF068,__READ);
__IO_REG16(DMA0_LUBuff1,    0xFFFFF06C,__READ);
__IO_REG16(DMA0_SOURCEL2,   0xFFFFF080,__READ_WRITE);
__IO_REG16(DMA0_SOURCEH2,   0xFFFFF084,__READ_WRITE);
__IO_REG16(DMA0_DESTL2,     0xFFFFF088,__READ_WRITE);
__IO_REG16(DMA0_DESTH2,     0xFFFFF08C,__READ_WRITE);
__IO_REG16(DMA0_MAX2,       0xFFFFF090,__READ_WRITE);
__IO_REG16_BIT(DMA0_CTRL2,  0xFFFFF094,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA0_SOCURRH2,   0xFFFFF098,__READ);
__IO_REG16(DMA0_SOCURRL2,   0xFFFFF09C,__READ);
__IO_REG16(DMA0_DECURRH2,   0xFFFFF0A0,__READ);
__IO_REG16(DMA0_DECURRL2,   0xFFFFF0A4,__READ);
__IO_REG16(DMA0_TCNT2,      0xFFFFF0A8,__READ);
__IO_REG16(DMA0_LUBuff2,    0xFFFFF0AC,__READ);
__IO_REG16(DMA0_SOURCEL3,   0xFFFFF0C0,__READ_WRITE);
__IO_REG16(DMA0_SOURCEH3,   0xFFFFF0C4,__READ_WRITE);
__IO_REG16(DMA0_DESTL3,     0xFFFFF0C8,__READ_WRITE);
__IO_REG16(DMA0_DESTH3,     0xFFFFF0CC,__READ_WRITE);
__IO_REG16(DMA0_MAX3,       0xFFFFF0D0,__READ_WRITE);
__IO_REG16_BIT(DMA0_CTRL3,  0xFFFFF0D4,__READ_WRITE,__dmanctrl3_bits);
__IO_REG16(DMA0_SOCURRH3,   0xFFFFF0D8,__READ);
__IO_REG16(DMA0_SOCURRL3,   0xFFFFF0DC,__READ);
__IO_REG16(DMA0_DECURRH3,   0xFFFFF0E0,__READ);
__IO_REG16(DMA0_DECURRL3,   0xFFFFF0E4,__READ);
__IO_REG16(DMA0_TCNT3,      0xFFFFF0E8,__READ);
__IO_REG16(DMA0_LUBuff3,    0xFFFFF0EC,__READ);
__IO_REG16_BIT(DMA0_MASK,   0xFFFFF0F0,__READ_WRITE,__dmanmask_bits);
__IO_REG16_BIT(DMA0_CLR,    0xFFFFF0F4,__WRITE,__dmanclr_bits);
__IO_REG16_BIT(DMA0_STATUS, 0xFFFFF0F8,__READ,__dmanstatus_bits);
__IO_REG16_BIT(DMA0_LAST,   0xFFFFF0FC,__READ_WRITE,__dmanlast_bits);

/***************************************************************************
 **
 ** DMA 1
 **
 ***************************************************************************/
__IO_REG16(DMA1_SOURCEL0,   0xFFFFF100,__READ_WRITE);
__IO_REG16(DMA1_SOURCEH0,   0xFFFFF104,__READ_WRITE);
__IO_REG16(DMA1_DESTL0,     0xFFFFF108,__READ_WRITE);
__IO_REG16(DMA1_DESTH0,     0xFFFFF10C,__READ_WRITE);
__IO_REG16(DMA1_MAX0,       0xFFFFF110,__READ_WRITE);
__IO_REG16_BIT(DMA1_CTRL0,  0xFFFFF114,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA1_SOCURRH0,   0xFFFFF118,__READ);
__IO_REG16(DMA1_SOCURRL0,   0xFFFFF11C,__READ);
__IO_REG16(DMA1_DECURRH0,   0xFFFFF120,__READ);
__IO_REG16(DMA1_DECURRL0,   0xFFFFF124,__READ);
__IO_REG16(DMA1_TCNT0,      0xFFFFF128,__READ);
__IO_REG16(DMA1_LUBuff0,    0xFFFFF12C,__READ);
__IO_REG16(DMA1_SOURCEL1,   0xFFFFF140,__READ_WRITE);
__IO_REG16(DMA1_SOURCEH1,   0xFFFFF144,__READ_WRITE);
__IO_REG16(DMA1_DESTL1,     0xFFFFF148,__READ_WRITE);
__IO_REG16(DMA1_DESTH1,     0xFFFFF14C,__READ_WRITE);
__IO_REG16(DMA1_MAX1,       0xFFFFF150,__READ_WRITE);
__IO_REG16_BIT(DMA1_CTRL1,  0xFFFFF154,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA1_SOCURRH1,   0xFFFFF158,__READ);
__IO_REG16(DMA1_SOCURRL1,   0xFFFFF15C,__READ);
__IO_REG16(DMA1_DECURRH1,   0xFFFFF160,__READ);
__IO_REG16(DMA1_DECURRL1,   0xFFFFF164,__READ);
__IO_REG16(DMA1_TCNT1,      0xFFFFF168,__READ);
__IO_REG16(DMA1_LUBuff1,    0xFFFFF16C,__READ);
__IO_REG16(DMA1_SOURCEL2,   0xFFFFF180,__READ_WRITE);
__IO_REG16(DMA1_SOURCEH2,   0xFFFFF184,__READ_WRITE);
__IO_REG16(DMA1_DESTL2,     0xFFFFF188,__READ_WRITE);
__IO_REG16(DMA1_DESTH2,     0xFFFFF18C,__READ_WRITE);
__IO_REG16(DMA1_MAX2,       0xFFFFF190,__READ_WRITE);
__IO_REG16_BIT(DMA1_CTRL2,  0xFFFFF194,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA1_SOCURRH2,   0xFFFFF198,__READ);
__IO_REG16(DMA1_SOCURRL2,   0xFFFFF19C,__READ);
__IO_REG16(DMA1_DECURRH2,   0xFFFFF1A0,__READ);
__IO_REG16(DMA1_DECURRL2,   0xFFFFF1A4,__READ);
__IO_REG16(DMA1_TCNT2,      0xFFFFF1A8,__READ);
__IO_REG16(DMA1_LUBuff2,    0xFFFFF1AC,__READ);
__IO_REG16(DMA1_SOURCEL3,   0xFFFFF1C0,__READ_WRITE);
__IO_REG16(DMA1_SOURCEH3,   0xFFFFF1C4,__READ_WRITE);
__IO_REG16(DMA1_DESTL3,     0xFFFFF1C8,__READ_WRITE);
__IO_REG16(DMA1_DESTH3,     0xFFFFF1CC,__READ_WRITE);
__IO_REG16(DMA1_MAX3,       0xFFFFF1D0,__READ_WRITE);
__IO_REG16_BIT(DMA1_CTRL3,  0xFFFFF1D4,__READ_WRITE,__dmanctrl3_bits);
__IO_REG16(DMA1_SOCURRH3,   0xFFFFF1D8,__READ);
__IO_REG16(DMA1_SOCURRL3,   0xFFFFF1DC,__READ);
__IO_REG16(DMA1_DECURRH3,   0xFFFFF1E0,__READ);
__IO_REG16(DMA1_DECURRL3,   0xFFFFF1E4,__READ);
__IO_REG16(DMA1_TCNT3,      0xFFFFF1E8,__READ);
__IO_REG16(DMA1_LUBuff3,    0xFFFFF1EC,__READ);
__IO_REG16_BIT(DMA1_MASK,   0xFFFFF1F0,__READ_WRITE,__dmanmask_bits);
__IO_REG16_BIT(DMA1_CLR,    0xFFFFF1F4,__WRITE,__dmanclr_bits);
__IO_REG16_BIT(DMA1_STATUS, 0xFFFFF1F8,__READ,__dmanstatus_bits);
__IO_REG16_BIT(DMA1_LAST,   0xFFFFF1FC,__READ_WRITE,__dmanlast_bits);

/***************************************************************************
 **
 ** DMA 2
 **
 ***************************************************************************/
__IO_REG16(DMA2_SOURCEL0,   0xFFFFF200,__READ_WRITE);
__IO_REG16(DMA2_SOURCEH0,   0xFFFFF204,__READ_WRITE);
__IO_REG16(DMA2_DESTL0,     0xFFFFF208,__READ_WRITE);
__IO_REG16(DMA2_DESTH0,     0xFFFFF20C,__READ_WRITE);
__IO_REG16(DMA2_MAX0,       0xFFFFF210,__READ_WRITE);
__IO_REG16_BIT(DMA2_CTRL0,  0xFFFFF214,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA2_SOCURRH0,   0xFFFFF218,__READ);
__IO_REG16(DMA2_SOCURRL0,   0xFFFFF21C,__READ);
__IO_REG16(DMA2_DECURRH0,   0xFFFFF220,__READ);
__IO_REG16(DMA2_DECURRL0,   0xFFFFF224,__READ);
__IO_REG16(DMA2_TCNT0,      0xFFFFF228,__READ);
__IO_REG16(DMA2_LUBuff0,    0xFFFFF22C,__READ);
__IO_REG16(DMA2_SOURCEL1,   0xFFFFF240,__READ_WRITE);
__IO_REG16(DMA2_SOURCEH1,   0xFFFFF244,__READ_WRITE);
__IO_REG16(DMA2_DESTL1,     0xFFFFF248,__READ_WRITE);
__IO_REG16(DMA2_DESTH1,     0xFFFFF24C,__READ_WRITE);
__IO_REG16(DMA2_MAX1,       0xFFFFF250,__READ_WRITE);
__IO_REG16_BIT(DMA2_CTRL1,  0xFFFFF254,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA2_SOCURRH1,   0xFFFFF258,__READ);
__IO_REG16(DMA2_SOCURRL1,   0xFFFFF25C,__READ);
__IO_REG16(DMA2_DECURRH1,   0xFFFFF260,__READ);
__IO_REG16(DMA2_DECURRL1,   0xFFFFF264,__READ);
__IO_REG16(DMA2_TCNT1,      0xFFFFF268,__READ);
__IO_REG16(DMA2_LUBuff1,    0xFFFFF26C,__READ);
__IO_REG16(DMA2_SOURCEL2,   0xFFFFF280,__READ_WRITE);
__IO_REG16(DMA2_SOURCEH2,   0xFFFFF284,__READ_WRITE);
__IO_REG16(DMA2_DESTL2,     0xFFFFF288,__READ_WRITE);
__IO_REG16(DMA2_DESTH2,     0xFFFFF28C,__READ_WRITE);
__IO_REG16(DMA2_MAX2,       0xFFFFF290,__READ_WRITE);
__IO_REG16_BIT(DMA2_CTRL2,  0xFFFFF294,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA2_SOCURRH2,   0xFFFFF298,__READ);
__IO_REG16(DMA2_SOCURRL2,   0xFFFFF29C,__READ);
__IO_REG16(DMA2_DECURRH2,   0xFFFFF2A0,__READ);
__IO_REG16(DMA2_DECURRL2,   0xFFFFF2A4,__READ);
__IO_REG16(DMA2_TCNT2,      0xFFFFF2A8,__READ);
__IO_REG16(DMA2_LUBuff2,    0xFFFFF2AC,__READ);
__IO_REG16(DMA2_SOURCEL3,   0xFFFFF2C0,__READ_WRITE);
__IO_REG16(DMA2_SOURCEH3,   0xFFFFF2C4,__READ_WRITE);
__IO_REG16(DMA2_DESTL3,     0xFFFFF2C8,__READ_WRITE);
__IO_REG16(DMA2_DESTH3,     0xFFFFF2CC,__READ_WRITE);
__IO_REG16(DMA2_MAX3,       0xFFFFF2D0,__READ_WRITE);
__IO_REG16_BIT(DMA2_CTRL3,  0xFFFFF2D4,__READ_WRITE,__dmanctrl3_bits);
__IO_REG16(DMA2_SOCURRH3,   0xFFFFF2D8,__READ);
__IO_REG16(DMA2_SOCURRL3,   0xFFFFF2DC,__READ);
__IO_REG16(DMA2_DECURRH3,   0xFFFFF2E0,__READ);
__IO_REG16(DMA2_DECURRL3,   0xFFFFF2E4,__READ);
__IO_REG16(DMA2_TCNT3,      0xFFFFF2E8,__READ);
__IO_REG16(DMA2_LUBuff3,    0xFFFFF2EC,__READ);
__IO_REG16_BIT(DMA2_MASK,   0xFFFFF2F0,__READ_WRITE,__dmanmask_bits);
__IO_REG16_BIT(DMA2_CLR,    0xFFFFF2F4,__WRITE,__dmanclr_bits);
__IO_REG16_BIT(DMA2_STATUS, 0xFFFFF2F8,__READ,__dmanstatus_bits);
__IO_REG16_BIT(DMA2_LAST,   0xFFFFF2FC,__READ_WRITE,__dmanlast_bits);

/***************************************************************************
 **
 ** DMA 3
 **
 ***************************************************************************/
__IO_REG16(DMA3_SOURCEL0,   0xFFFFF300,__READ_WRITE);
__IO_REG16(DMA3_SOURCEH0,   0xFFFFF304,__READ_WRITE);
__IO_REG16(DMA3_DESTL0,     0xFFFFF308,__READ_WRITE);
__IO_REG16(DMA3_DESTH0,     0xFFFFF30C,__READ_WRITE);
__IO_REG16(DMA3_MAX0,       0xFFFFF310,__READ_WRITE);
__IO_REG16_BIT(DMA3_CTRL0,  0xFFFFF314,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA3_SOCURRH0,   0xFFFFF318,__READ);
__IO_REG16(DMA3_SOCURRL0,   0xFFFFF31C,__READ);
__IO_REG16(DMA3_DECURRH0,   0xFFFFF320,__READ);
__IO_REG16(DMA3_DECURRL0,   0xFFFFF324,__READ);
__IO_REG16(DMA3_TCNT0,      0xFFFFF328,__READ);
__IO_REG16(DMA3_LUBuff0,    0xFFFFF32C,__READ);
__IO_REG16(DMA3_SOURCEL1,   0xFFFFF340,__READ_WRITE);
__IO_REG16(DMA3_SOURCEH1,   0xFFFFF344,__READ_WRITE);
__IO_REG16(DMA3_DESTL1,     0xFFFFF348,__READ_WRITE);
__IO_REG16(DMA3_DESTH1,     0xFFFFF34C,__READ_WRITE);
__IO_REG16(DMA3_MAX1,       0xFFFFF350,__READ_WRITE);
__IO_REG16_BIT(DMA3_CTRL1,  0xFFFFF354,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA3_SOCURRH1,   0xFFFFF358,__READ);
__IO_REG16(DMA3_SOCURRL1,   0xFFFFF35C,__READ);
__IO_REG16(DMA3_DECURRH1,   0xFFFFF360,__READ);
__IO_REG16(DMA3_DECURRL1,   0xFFFFF364,__READ);
__IO_REG16(DMA3_TCNT1,      0xFFFFF368,__READ);
__IO_REG16(DMA3_LUBuff1,    0xFFFFF36C,__READ);
__IO_REG16(DMA3_SOURCEL2,   0xFFFFF380,__READ_WRITE);
__IO_REG16(DMA3_SOURCEH2,   0xFFFFF384,__READ_WRITE);
__IO_REG16(DMA3_DESTL2,     0xFFFFF388,__READ_WRITE);
__IO_REG16(DMA3_DESTH2,     0xFFFFF38C,__READ_WRITE);
__IO_REG16(DMA3_MAX2,       0xFFFFF390,__READ_WRITE);
__IO_REG16_BIT(DMA3_CTRL2,  0xFFFFF394,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(DMA3_SOCURRH2,   0xFFFFF398,__READ);
__IO_REG16(DMA3_SOCURRL2,   0xFFFFF39C,__READ);
__IO_REG16(DMA3_DECURRH2,   0xFFFFF3A0,__READ);
__IO_REG16(DMA3_DECURRL2,   0xFFFFF3A4,__READ);
__IO_REG16(DMA3_TCNT2,      0xFFFFF3A8,__READ);
__IO_REG16(DMA3_LUBuff2,    0xFFFFF3AC,__READ);
__IO_REG16(DMA3_SOURCEL3,   0xFFFFF3C0,__READ_WRITE);
__IO_REG16(DMA3_SOURCEH3,   0xFFFFF3C4,__READ_WRITE);
__IO_REG16(DMA3_DESTL3,     0xFFFFF3C8,__READ_WRITE);
__IO_REG16(DMA3_DESTH3,     0xFFFFF3CC,__READ_WRITE);
__IO_REG16(DMA3_MAX3,       0xFFFFF3D0,__READ_WRITE);
__IO_REG16_BIT(DMA3_CTRL3,  0xFFFFF3D4,__READ_WRITE,__dmanctrl3_bits);
__IO_REG16(DMA3_SOCURRH3,   0xFFFFF3D8,__READ);
__IO_REG16(DMA3_SOCURRL3,   0xFFFFF3DC,__READ);
__IO_REG16(DMA3_DECURRH3,   0xFFFFF3E0,__READ);
__IO_REG16(DMA3_DECURRL3,   0xFFFFF3E4,__READ);
__IO_REG16(DMA3_TCNT3,      0xFFFFF3E8,__READ);
__IO_REG16(DMA3_LUBuff3,    0xFFFFF3EC,__READ);
__IO_REG16_BIT(DMA3_MASK,   0xFFFFF3F0,__READ_WRITE,__dmanmask_bits);
__IO_REG16_BIT(DMA3_CLR,    0xFFFFF3F4,__WRITE,__dmanclr_bits);
__IO_REG16_BIT(DMA3_STATUS, 0xFFFFF3F8,__READ,__dmanstatus_bits);
__IO_REG16_BIT(DMA3_LAST,   0xFFFFF3FC,__READ_WRITE,__dmanlast_bits);

/***************************************************************************
 **
 ** Realtime Clock RTC
 **
 ***************************************************************************/
__IO_REG16_BIT(RTC_CRH,     0xFFFFF400,__READ_WRITE,__rtccrh_bits);
__IO_REG16_BIT(RTC_CRL,     0xFFFFF404,__READ_WRITE,__rtccrl_bits);
__IO_REG16_BIT(RTC_PRLH,    0xFFFFF408,__WRITE     ,__rtcprlh_bits);
__IO_REG16(    RTC_PRLL,    0xFFFFF40C,__WRITE);
__IO_REG16_BIT(RTC_DIVH,    0xFFFFF410,__READ      ,__rtcdivh_bits);
__IO_REG16(    RTC_DIVL,    0xFFFFF414,__READ);
__IO_REG16(    RTC_CNTH,    0xFFFFF418,__READ_WRITE);
__IO_REG16(    RTC_CNTL,    0xFFFFF41C,__READ_WRITE);
__IO_REG16(    RTC_ALRH,    0xFFFFF420,__WRITE);
__IO_REG16(    RTC_ALRL,    0xFFFFF424,__WRITE);

/***************************************************************************
 **
 ** Analog/Digital Converter ADC
 **
 ***************************************************************************/

__IO_REG16_BIT(ADC_CLR0,    0xFFFFF800,__READ_WRITE,__adcclr0_bits);
__IO_REG16_BIT(ADC_CLR1,    0xFFFFF804,__READ_WRITE,__adcclr1_bits);
__IO_REG16_BIT(ADC_CLR2,    0xFFFFF808,__READ_WRITE,__adcclr2_bits);
__IO_REG16_BIT(ADC_CLR3,    0xFFFFF80C,__READ_WRITE,__adcclr3_bits);
__IO_REG16_BIT(ADC_CLR4,    0xFFFFF810,__READ_WRITE,__adcclr4_bits);
__IO_REG16_BIT(ADC_TRA0,    0xFFFFF814,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRA1,    0xFFFFF818,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRA2,    0xFFFFF81C,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRA3,    0xFFFFF820,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRB0,    0xFFFFF824,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_TRB1,    0xFFFFF828,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_TRB2,    0xFFFFF82C,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_TRB3,    0xFFFFF830,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_DMAR,    0xFFFFF834,__READ_WRITE,__adcdmar_bits);
__IO_REG16_BIT(ADC_DMAE,    0xFFFFF844,__READ_WRITE,__adcdmae_bits);
__IO_REG16_BIT(ADC_PBR,     0xFFFFF848,__READ_WRITE,__adcpbr_bits);
__IO_REG16_BIT(ADC_IMR,     0xFFFFF84C,__READ_WRITE,__adcimr_bits);
__IO_REG16_BIT(ADC_D0,      0xFFFFF850,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D1,      0xFFFFF854,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D2,      0xFFFFF858,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D3,      0xFFFFF85C,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D4,      0xFFFFF860,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D5,      0xFFFFF864,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D6,      0xFFFFF868,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D7,      0xFFFFF86C,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D8,      0xFFFFF870,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D9,      0xFFFFF874,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D10,     0xFFFFF878,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D11,     0xFFFFF87C,__READ,      __adcdx_bits);

/* Assembler-specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  STR736 IRQ Interrupt Vector Table
 **
 ***************************************************************************/
#define CMU_PRCCU_INT    0
#define INT1_INT         1
#define INT2_INT         2
#define INT3_INT         3
#define INT4_INT         4
#define INT5_INT         5
#define INT6_INT         6
#define INT7_INT         7
#define INT8_INT         8
#define INT9_INT         9
#define INT10_INT       10
#define INT11_INT       11
#define INT12_INT       12
#define INT13_INT       13
#define INT14_INT       14
#define INT15_INT       15
#define DMA_INT         16
#define TIM1_INT        17
#define TIM2_INT        18
#define TIM3_INT        19
#define TIM4_INT        20
#define TBU0_INT        21
#define TBU1_INT        22
#define TBU2_INT        23
#define TIM5_INT        24
#define UART2_INT       31
#define UART3_INT       32
#define FLASH_INT       33
#define PWM0_INT        34
#define PWM1_INT        35
#define PWM2_INT        36
#define PWM3_INT        37
#define PWM4_INT        38
#define PWM5_INT        39
#define WIU_INT         40
#define WDG_WUT_INT     41
#define BSPI0_INT       42
#define BSPI1_INT       43
#define BSPI2_INT       44
#define UART0_INT       45
#define UART1_INT       46
#define I2C0_ITERR_INT  47
#define I2C1_ITERR_INT  48
#define I2C0_ITDDC_INT  51
#define I2C1_ITDDC_INT  52
#define DMA0_INT        58
#define DMA1_INT        59
#define DMA2_INT        60
#define DMA3_INT        61
#define ADC_INT         62
#define RTC_INT         63

/***************************************************************************
 **
 **  STR736 FIQ Interrupt Vector Table
 **
 ***************************************************************************/
#define INT0_INT         0
#define TIM0_INT         1

#endif    /* __IOSTR736_H */
