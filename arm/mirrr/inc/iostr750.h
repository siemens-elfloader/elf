/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    ST STR750F
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1 $
 **
 ***************************************************************************/

#ifndef __IOSTR750_H
#define __IOSTR750_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   STR750 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/


/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Global Configuration Register (CFG_GLCONF) */
typedef struct {
  __REG32  SW_BOOT        : 3;
  __REG32                 : 4;
  __REG32  FLASH_BUSY     : 1;
  __REG32  FLASH_BURST    : 1;
  __REG32  USB_FILTEN     : 1;
  __REG32                 :22;
} __cfg_clconf_bits;

/* Clock Control Register (MRCC_CLKCTL) */
typedef struct {
  __REG32  PPRESC         : 2;
  __REG32  PPRESC2        : 1;
  __REG32  HPRESC         : 2;
  __REG32  MCOP           : 1;
  __REG32  MCOS           : 2;
  __REG32                 : 8;
  __REG32  OSC4MBYP       : 1;
  __REG32  OSC4MOFF       : 1;
  __REG32  NCKDF          : 1;
  __REG32  NCKDIE         : 1;
  __REG32                 : 1;
  __REG32  CKOSCSEL       : 1;
  __REG32  CKUSBSEL       : 1;
  __REG32  CKSEL          : 1;
  __REG32  PLLEN          : 1;
  __REG32  PLL2EN         : 1;
  __REG32                 : 1;
  __REG32  MX             : 2;
  __REG32  LOCKIF         : 1;
  __REG32  LOCKIE         : 1;
  __REG32  LOCK           : 1;
} __mrcc_clkctl_bits;

/* Reset Flag and Status register (MRCC_RFSR) */
typedef struct {
  __REG32  SCOUNT         :12;
  __REG32                 : 4;
  __REG32  BCOUNTM        : 8;
  __REG32  BCOUNTF        : 1;
  __REG32  STDBF          : 1;
  __REG32  WKPF           : 1;
  __REG32  EXTRF          : 1;
  __REG32  WDGRF          : 1;
  __REG32  SWRF           : 1;
  __REG32                 : 2;
} __mrcc_rfsr_bits;

/* Power Management Control register (MRCC_PWRCTRL) */
typedef struct {
  __REG32  LP             : 1;
  __REG32  LPMC           : 2;
  __REG32  LPMC_DBG       : 1;
  __REG32  LPMC_WFI_DMA   : 1;
  __REG32                 : 2;
  __REG32  LP_DONE        : 1;
  __REG32  LP_PARAM       : 8;
  __REG32  EN33V          : 1;
  __REG32                 : 7;
  __REG32  CKRTCSEL       : 2;
  __REG32  RTCM           : 1;
  __REG32  CKRTCOK        : 1;
  __REG32  LPOSCEN        : 1;
  __REG32  OSC32KEN       : 1;
  __REG32  OSC32KBYP      : 1;
  __REG32  OSC32KRDY      : 1;
} __mrcc_pwrctrl_bits;

/* Peripheral Clock Enable register (MRCC_PCLKEN)
   Peripheral Software Reset register (MRCC_PSWRES) */
typedef struct {
  __REG32  ADC            : 1;
  __REG32  TB             : 1;
  __REG32  TIM0           : 1;
  __REG32  TIM1           : 1;
  __REG32  TIM2           : 1;
  __REG32  PWM            : 1;
  __REG32                 : 3;
  __REG32  USB            : 1;
  __REG32                 : 3;
  __REG32  SPI0           : 1;
  __REG32  SPI1           : 1;
  __REG32                 : 1;
  __REG32  CAN            : 1;
  __REG32                 : 1;
  __REG32  I2C            : 1;
  __REG32                 : 1;
  __REG32  UART0          : 1;
  __REG32  UART1          : 1;
  __REG32  UART2          : 1;
  __REG32                 : 1;
  __REG32  GPIO           : 1;
  __REG32                 : 2;
  __REG32  RTC            : 1;
  __REG32  EXTIT          : 1;
  __REG32                 : 3;
} __mrcc_pclken_bits;

/* I/O Remapping Register 0 (GPIO_REMAP0R) */
typedef struct {
  __REG32  TIM1_REMAP     : 1;
  __REG32  TIM3_REMAP     : 1;
  __REG32  SSP1_REMAP     : 1;
  __REG32  UART2_REMAP    : 1;
  __REG32  UART1_REMAP    : 1;
  __REG32  DBGOFF         : 1;
  __REG32  BODEN          : 1;
  __REG32                 :25;
} __gpio_remap0r_bits;

/* I/O Remapping Register 1 (GPIO_REMAP1R) */
typedef struct {
  __REG32  SMI_EN         : 1;
  __REG32  SMI_CS1_EN     : 1;
  __REG32  SMI_CS2_EN     : 1;
  __REG32  SMI_CS3_EN     : 1;
  __REG32                 :28;
} __gpio_remap1r_bits;

/* Interrupt Control Register (EIC_ICR) */
typedef struct {
  __REG32  IRQ_EN         : 1;
  __REG32  FIQ_EN         : 1;
  __REG32                 :30;
} __eicicr_bits;

/* Current Interrupt Channel Register (EIC_CICR) */
typedef struct {
  __REG32  CIC            : 5;
  __REG32                 :27;
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
  __REG32  FIP            : 2;
  __REG32                 :28;
} __eicfir_bits;

/* Interrupt Enable Register (EIC_IER) */
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
} __eicier_bits;


/* Interrupt Pending Register (EIC_IPR) */
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
} __eicipr_bits;

/* Source Interrupt Registers - Channel n (EIC_SIRn) */
typedef struct {
  __REG32 SIPL            : 4;
  __REG32                 :12;
  __REG32 SIV             :16;
} __eicsirn_bits;

/* Interrupt Mask Register (EXTIT_MR) */
typedef struct {
  __REG32 MR0             : 1;
  __REG32 MR1             : 1;
  __REG32 MR2             : 1;
  __REG32 MR3             : 1;
  __REG32 MR4             : 1;
  __REG32 MR5             : 1;
  __REG32 MR6             : 1;
  __REG32 MR7             : 1;
  __REG32 MR8             : 1;
  __REG32 MR9             : 1;
  __REG32 MR10            : 1;
  __REG32 MR11            : 1;
  __REG32 MR12            : 1;
  __REG32 MR13            : 1;
  __REG32 MR14            : 1;
  __REG32 MR15            : 1;
  __REG32                 :16;
} __extit_mr_bits;

/* Trigger Selection Register (EXTIT_TSR) */
typedef struct {
  __REG32 TR0             : 1;
  __REG32 TR1             : 1;
  __REG32 TR2             : 1;
  __REG32 TR3             : 1;
  __REG32 TR4             : 1;
  __REG32 TR5             : 1;
  __REG32 TR6             : 1;
  __REG32 TR7             : 1;
  __REG32 TR8             : 1;
  __REG32 TR9             : 1;
  __REG32 TR10            : 1;
  __REG32 TR11            : 1;
  __REG32 TR12            : 1;
  __REG32 TR13            : 1;
  __REG32 TR14            : 1;
  __REG32 TR15            : 1;
  __REG32                 :16;
} __extit_tsr_bits;

/* Software Interrupt Register (EXTIT_SWIR) */
typedef struct {
  __REG32 SWIR0           : 1;
  __REG32 SWIR1           : 1;
  __REG32 SWIR2           : 1;
  __REG32 SWIR3           : 1;
  __REG32 SWIR4           : 1;
  __REG32 SWIR5           : 1;
  __REG32 SWIR6           : 1;
  __REG32 SWIR7           : 1;
  __REG32 SWIR8           : 1;
  __REG32 SWIR9           : 1;
  __REG32 SWIR10          : 1;
  __REG32 SWIR11          : 1;
  __REG32 SWIR12          : 1;
  __REG32 SWIR13          : 1;
  __REG32 SWIR14          : 1;
  __REG32 SWIR15          : 1;
  __REG32                 :16;
} __extit_swir_bits;

/* Pending Register (EXTIT_PR) */
typedef struct {
  __REG32 PR0             : 1;
  __REG32 PR1             : 1;
  __REG32 PR2             : 1;
  __REG32 PR3             : 1;
  __REG32 PR4             : 1;
  __REG32 PR5             : 1;
  __REG32 PR6             : 1;
  __REG32 PR7             : 1;
  __REG32 PR8             : 1;
  __REG32 PR9             : 1;
  __REG32 PR10            : 1;
  __REG32 PR11            : 1;
  __REG32 PR12            : 1;
  __REG32 PR13            : 1;
  __REG32 PR14            : 1;
  __REG32 PR15            : 1;
  __REG32                 :16;
} __extit_pr_bits;

/* Control Register (DMA_CTRLx) */
typedef struct {
  __REG16  ENABLE         : 1;
  __REG16  SOINC          : 1;
  __REG16  DEINC          : 1;
  __REG16  SOSIZE         : 2;
  __REG16  SOBURST        : 2;
  __REG16  DESIZE         : 2;
  __REG16  CIRCULAR       : 1;
  __REG16                 : 3;
  __REG16  DIR            : 1;
  __REG16                 : 2;
} __dmanctrlx_bits;

/* Control Register 3 (DMA_CTRL3) */
typedef struct {
  __REG16  ENABLE         : 1;
  __REG16  SOINC          : 1;
  __REG16  DEINC          : 1;
  __REG16  SOSIZE         : 2;
  __REG16  SOBURST        : 2;
  __REG16  DESIZE         : 2;
  __REG16  CIRCULAR       : 1;
  __REG16                 : 1;
  __REG16  MEM2MEM        : 1;
  __REG16                 : 1;
  __REG16  DIR            : 1;
  __REG16                 : 2;
} __dmanctrl3_bits;

/* Interrupt Mask Register (DMA_MASK) */
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

/* Interrupt Status Register (DMA_STATUS) */
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

/* Last Flag Register (DMA_LAST) */
typedef struct {
  __REG16  LAST0          : 1;
  __REG16  LAST1          : 1;
  __REG16  LAST2          : 1;
  __REG16  LAST3          : 1;
  __REG16                 :12;
} __dmanlast_bits;

/* SMI control register 1 (SMI_CR1) */
typedef struct {
  __REG32  BE             : 4;
  __REG32  TCS            : 4;
  __REG32  PRESC          : 7;
  __REG32  FAST           : 1;
  __REG32  HOLD           : 8;
  __REG32  ADD_LENGTH     : 4;
  __REG32  SW             : 1;
  __REG32  WBM            : 1;
  __REG32                 : 2;
} __smi_cr1_bits;

/* SMI control register 2 (SMI_CR2) */
typedef struct {
  __REG32  TL             : 3;
  __REG32                 : 1;
  __REG32  RL             : 3;
  __REG32  SEND           : 1;
  __REG32  TFIE           : 1;
  __REG32  WCIE           : 1;
  __REG32  RSR            : 1;
  __REG32  WEN            : 1;
  __REG32  BS             : 2;
  __REG32                 :18;
} __smi_cr2_bits;

/* SMI status register (SMI_SR) */
typedef struct {
  __REG32  STATUS         : 8;
  __REG32  TFF            : 1;
  __REG32  WCF            : 1;
  __REG32  ERF1           : 1;
  __REG32  ERF2           : 1;
  __REG32  WM             : 4;
  __REG32                 :16;
} __smi_sr_bits;

/* SMI transmit register (SMI_TR)
   SMI receive register (SMI_RR) */
typedef struct {
  __REG32  BYTE0          : 8;
  __REG32  BYTE1          : 8;
  __REG32  BYTE2          : 8;
  __REG32  BYTE3          : 8;
} __smi_tr_bits;

/* RTC Control Register High (RTC_CRH) */
typedef struct {
  __REG16 SEN             : 1;
  __REG16 AEN             : 1;
  __REG16 OWEN            : 1;
  __REG16                 :13;
} __rtccrh_bits;

/* RTC Control Register Low (RTC_CRL) */
typedef struct {
  __REG16 SIR             : 1;
  __REG16 AIR             : 1;
  __REG16 OWIR            : 1;
  __REG16 RSF             : 1;
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
  __REG16                 :14;
} __wdgcr_bits;

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

/* Control Register (TB_CR) */
typedef struct {
  __REG16  UFS            : 1;
  __REG16  CNT_RST        : 1;
  __REG16  CNT_EN         : 1;
  __REG16                 : 1;
  __REG16  U_D            : 1;
  __REG16  CMS            : 2;
  __REG16                 : 3;
  __REG16  DBGC           : 1;
  __REG16                 : 5;
} __tb_cr_bits;

/* Input Mode Control Register (TB_IMCR) */
typedef struct {
  __REG16                 : 2;
  __REG16  IC1E           : 1;
  __REG16  IC1P           : 1;
  __REG16                 :12;
} __tb_imcr_bits;

/* Request Selection Register (TB_RSR) */
typedef struct {
  __REG16  URS            : 1;
  __REG16                 : 1;
  __REG16  IC1RS          : 1;
  __REG16                 :13;
} __tb_rsr_bits;

/* Request Enable Register (TB_RER) */
typedef struct {
  __REG16  URE            : 1;
  __REG16                 : 1;
  __REG16  IC1RE          : 1;
  __REG16                 :13;
} __tb_rer_bits;

/* Interrupt Status Register (TB_ISR) */
typedef struct {
  __REG16  UI             : 1;
  __REG16                 : 1;
  __REG16  IC1I           : 1;
  __REG16                 :13;
} __tb_isr_bits;

/* Control Register (TIM_CR) */
typedef struct {
  __REG16  UFS            : 1;
  __REG16  CNT_RST        : 1;
  __REG16  CNT_EN         : 1;
  __REG16  OPM            : 1;
  __REG16  U_D            : 1;
  __REG16  CMS            : 2;
  __REG16                 : 1;
  __REG16  MMS            : 2;
  __REG16  DBGC           : 1;
  __REG16  DBASE          : 5;
} __tim_cr_bits;

/* Synchro Control Register (TIM_SCR) */
typedef struct {
  __REG16  ENC            : 2;
  __REG16  SME            : 1;
  __REG16  SMS            : 2;
  __REG16                 : 3;
  __REG16  TS             : 2;
  __REG16                 : 2;
  __REG16  ITS            : 3;
  __REG16                 : 1;
} __tim_scr_bits;

/* Input Mode Control Register (TIM_IMCR) */
typedef struct {
  __REG16  IC1S           : 1;
  __REG16  IC2S           : 1;
  __REG16  IC1E           : 1;
  __REG16  IC1P           : 1;
  __REG16  IC2E           : 1;
  __REG16  IC2P           : 1;
  __REG16                 :10;
} __tim_imcr_bits;

/* Output Mode Register 1 (TIM_OMR1) */
typedef struct {
  __REG16  PLD1           : 1;
  __REG16  OC1C           : 3;
  __REG16  OC1E           : 1;
  __REG16  OC1P           : 1;
  __REG16                 : 2;
  __REG16  PLD2           : 1;
  __REG16  OC2C           : 3;
  __REG16  OC2E           : 1;
  __REG16  OC2P           : 1;
  __REG16                 : 2;
} __tim_omr1_bits;

/* Request Selection Register (TIM_RSR) */
typedef struct {
  __REG16  URS            : 1;
  __REG16                 : 1;
  __REG16  IC1RS          : 1;
  __REG16  IC2RS          : 1;
  __REG16                 : 3;
  __REG16  OCRM           : 1;
  __REG16  OC1RS          : 1;
  __REG16  OC2RS          : 1;
  __REG16                 : 6;
} __tim_rsr_bits;

/* Request Enable Register (TIM_RER) */
typedef struct {
  __REG16  URE            : 1;
  __REG16                 : 1;
  __REG16  IC1RE          : 1;
  __REG16  IC2RE          : 1;
  __REG16                 : 4;
  __REG16  OC1RE          : 1;
  __REG16  OC2RE          : 1;
  __REG16                 : 6;
} __tim_rer_bits;

/* Interrupt Status Register (TIM_ISR) */
typedef struct {
  __REG16  UI             : 1;
  __REG16                 : 1;
  __REG16  IC1I           : 1;
  __REG16  IC2I           : 1;
  __REG16                 : 4;
  __REG16  OC1I           : 1;
  __REG16  OC2I           : 1;
  __REG16                 : 6;
} __tim_isr_bits;

/* Control Register (PWM_CR) */
typedef struct {
  __REG16  UFS            : 1;
  __REG16  CNT_RST        : 1;
  __REG16  CNT_EN         : 1;
  __REG16  OPM            : 1;
  __REG16  U_D            : 1;
  __REG16  CMS            : 2;
  __REG16                 : 1;
  __REG16  MMS            : 2;
  __REG16  DBGC           : 1;
  __REG16  DBASE          : 5;
} __pwm_cr_bits;

/* Synchro Control Register (PWM_SCR) */
typedef struct {
  __REG16                 : 2;
  __REG16  SME            : 1;
  __REG16  SMS            : 2;
  __REG16                 : 3;
  __REG16  TS             : 2;
  __REG16                 : 2;
  __REG16  ITS            : 3;
  __REG16                 : 1;
} __pwm_scr_bits;

/* Output Mode Register 1 (PWM_OMR1) */
typedef struct {
  __REG16  PLD1           : 1;
  __REG16  OC1C           : 3;
  __REG16  OC1E           : 1;
  __REG16  OC1P           : 1;
  __REG16  OC1NE          : 1;
  __REG16  OC1NP          : 1;
  __REG16  PLD2           : 1;
  __REG16  OC2C           : 3;
  __REG16  OC2E           : 1;
  __REG16  OC2P           : 1;
  __REG16  OC2NE          : 1;
  __REG16  OC2NP          : 1;
} __pwm_omr1_bits;

/* Output Mode Register 2 (PWM_OMR2) */
typedef struct {
  __REG16  PLD3           : 1;
  __REG16  OC3C           : 3;
  __REG16  OC3E           : 1;
  __REG16  OC3P           : 1;
  __REG16  OC3NE          : 1;
  __REG16  OC3NP          : 1;
  __REG16                 : 8;
} __pwm_omr2_bits;

/* Request Selection Register (PWM_RSR) */
typedef struct {
  __REG16  URS            : 1;
  __REG16                 : 6;
  __REG16  OCRM           : 1;
  __REG16  OC1RS          : 1;
  __REG16  OC2RS          : 1;
  __REG16  OC3RS          : 1;
  __REG16                 : 4;
  __REG16  ERS            : 1;
} __pwm_rsr_bits;

/* Request Enable Register (PWM_RER) */
typedef struct {
  __REG16  URE            : 1;
  __REG16                 : 7;
  __REG16  OC1RE          : 1;
  __REG16  OC2RE          : 1;
  __REG16  OC3RE          : 1;
  __REG16                 : 4;
  __REG16  ERE            : 1;
} __pwm_rer_bits;

/* Interrupt Status Register (PWM_ISR) */
typedef struct {
  __REG16  UI             : 1;
  __REG16                 : 7;
  __REG16  OC1I           : 1;
  __REG16  OC2I           : 1;
  __REG16  OC3I           : 1;
  __REG16                 : 4;
  __REG16  EI             : 1;
} __pwm_isr_bits;

/* Dead-Time Register (PWM_DTR) */
typedef struct {
  __REG16  DTG            :10;
  __REG16  LOCK           : 2;
  __REG16  EEN            : 1;
  __REG16  OSSI           : 1;
  __REG16  OSSR           : 1;
  __REG16  MOE            : 1;
} __pwm_dtr_bits;

/* CAN Control Register (CAN_CR) */
typedef struct {
  __REG16  INIT           : 1;
  __REG16  IE             : 1;
  __REG16  SIE            : 1;
  __REG16  EIE            : 1;
  __REG16                 : 1;
  __REG16  DAR            : 1;
  __REG16  CCE            : 1;
  __REG16  TEST           : 1;
  __REG16                 : 8;
} __canncr_bits;

/* Status Register (CAN_SR) */
typedef struct {
  __REG16  LEC            : 3;
  __REG16  TXOK           : 1;
  __REG16  RXOK           : 1;
  __REG16  EPASS          : 1;
  __REG16  EWARN          : 1;
  __REG16  BOFF           : 1;
  __REG16                 : 8;
} __cannsr_bits;

/* Error Counter (CAN_ERR) */
typedef struct {
  __REG16  TEC            : 8;
  __REG16  REC            : 7;
  __REG16  RP             : 1;
} __cannerr_bits;

/* Bit Timing Register (CAN_BTR) */
typedef struct {
  __REG16  BRP            : 6;
  __REG16  SJW            : 2;
  __REG16  TSEG1          : 4;
  __REG16  TSEG2          : 3;
  __REG16                 : 1;
} __cannbtr_bits;

/* Test Register (CAN_TESTR) */
typedef struct {
  __REG16                 : 2;
  __REG16  BASIC          : 1;
  __REG16  SILENT         : 1;
  __REG16  LBACK          : 1;
  __REG16  TX             : 2;
  __REG16  RX             : 1;
  __REG16                 : 8;
} __canntestr_bits;

/* BRP Extension Register (CAN_BRPR) */
typedef struct {
  __REG16  BRPE           : 4;
  __REG16                 :12;
} __cannbrpr_bits;

/* IFn Command Request Registers (CAN_IFx_CRR) */
typedef struct {
  __REG16  MSGNO          : 6;
  __REG16                 : 9;
  __REG16  BUSY           : 1;
} __cannifxcrr_bits;

/* IFn Command Mask Registers (CAN_IFx_CMR) */
typedef struct {
  __REG16  DATAB          : 1;
  __REG16  DATAA          : 1;
  __REG16  TXRQST         : 1;
  __REG16  CLRINTPND      : 1;
  __REG16  CONTROL        : 1;
  __REG16  ARB            : 1;
  __REG16  MASK           : 1;
  __REG16  WR_RD          : 1;
  __REG16                 : 8;
} __cannifxcmr_bits;

/* IFn Mask 1 Register (CAN_IFx_M1R) */
typedef struct {
  __REG16  MSK0           : 1;
  __REG16  MSK1           : 1;
  __REG16  MSK2           : 1;
  __REG16  MSK3           : 1;
  __REG16  MSK4           : 1;
  __REG16  MSK5           : 1;
  __REG16  MSK6           : 1;
  __REG16  MSK7           : 1;
  __REG16  MSK8           : 1;
  __REG16  MSK9           : 1;
  __REG16  MSK10          : 1;
  __REG16  MSK11          : 1;
  __REG16  MSK12          : 1;
  __REG16  MSK13          : 1;
  __REG16  MSK14          : 1;
  __REG16  MSK15          : 1;
} __cannifxm1r_bits;

/* IFn Mask 2 Register (CAN_IFx_M2R) */
typedef struct {
  __REG16  MSK16          : 1;
  __REG16  MSK17          : 1;
  __REG16  MSK18          : 1;
  __REG16  MSK19          : 1;
  __REG16  MSK20          : 1;
  __REG16  MSK21          : 1;
  __REG16  MSK22          : 1;
  __REG16  MSK23          : 1;
  __REG16  MSK24          : 1;
  __REG16  MSK25          : 1;
  __REG16  MSK26          : 1;
  __REG16  MSK27          : 1;
  __REG16  MSK28          : 1;
  __REG16                 : 1;
  __REG16  MDIR           : 1;
  __REG16  MXTD           : 1;
} __cannifxm2r_bits;

/* IFn Message Arbitration 1 Register (CAN_IFx_A1R) */
typedef struct {
  __REG16  ID0            : 1;
  __REG16  ID1            : 1;
  __REG16  ID2            : 1;
  __REG16  ID3            : 1;
  __REG16  ID4            : 1;
  __REG16  ID5            : 1;
  __REG16  ID6            : 1;
  __REG16  ID7            : 1;
  __REG16  ID8            : 1;
  __REG16  ID9            : 1;
  __REG16  ID10           : 1;
  __REG16  ID11           : 1;
  __REG16  ID12           : 1;
  __REG16  ID13           : 1;
  __REG16  ID14           : 1;
  __REG16  ID15           : 1;
} __cannifxa1r_bits;

/* IFn Message Arbitration 2 Register (CAN_IFx_A2R) */
typedef struct {
  __REG16  ID16           : 1;
  __REG16  ID17           : 1;
  __REG16  ID18           : 1;
  __REG16  ID19           : 1;
  __REG16  ID20           : 1;
  __REG16  ID21           : 1;
  __REG16  ID22           : 1;
  __REG16  ID23           : 1;
  __REG16  ID24           : 1;
  __REG16  ID25           : 1;
  __REG16  ID26           : 1;
  __REG16  ID27           : 1;
  __REG16  ID28           : 1;
  __REG16  DIR            : 1;
  __REG16  XTD            : 1;
  __REG16  MSGVAL         : 1;
} __cannifxa2r_bits;

/* Message Control Registers (CAN_IFx_MCR) */
typedef struct {
  __REG16  DLC            : 4;
  __REG16                 : 3;
  __REG16  EOB            : 1;
  __REG16  TXRQST         : 1;
  __REG16  RMTEN          : 1;
  __REG16  RXIE           : 1;
  __REG16  TXIE           : 1;
  __REG16  UMASK          : 1;
  __REG16  INTPND         : 1;
  __REG16  MSGLST         : 1;
  __REG16  NEWDAT         : 1;
} __cannifxmcr_bits;

/* IFn Data A/B Registers (CAN_IFx_DAnR and CAN_IFx_DBnR) */
typedef struct {
  __REG16  DATA0          : 8;
  __REG16  DATA1          : 8;
} __cannifxda1r_bits;

typedef struct {
  __REG16  DATA2          : 8;
  __REG16  DATA3          : 8;
} __cannifxda2r_bits;

typedef struct {
  __REG16  DATA4          : 8;
  __REG16  DATA5          : 8;
} __cannifxdb1r_bits;

typedef struct {
  __REG16  DATA6          : 8;
  __REG16  DATA7          : 8;
} __cannifxdb2r_bits;

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
  __REG8  CC              : 7;
  __REG8  FM_SM           : 1;
} __i2cnccr_bits;

/* I2C Extended Clock Control Register (I2Cn_ECCR) */
typedef struct {
  __REG8  CC              : 5;
  __REG8                  : 3;
} __i2cneccr_bits;

/* I2C Own Address Register 1 (I2Cn_OAR1) */
typedef struct {
  __REG8  DIR             : 1;
  __REG8  ADD             : 7;
} __i2cnoar1_bits;

/* I2C Own Address Register 2 (I2Cn_OAR2) */
typedef struct {
  __REG8                  : 1;
  __REG8  ADD             : 2;
  __REG8                  : 2;
  __REG8  FR              : 3;
} __i2cnoar2_bits;

/* Control Register 0 (SSP_CR0) */
typedef struct {
  __REG16 DSS             : 4;
  __REG16 FRF             : 2;
  __REG16 CPOL            : 1;
  __REG16 CPHA            : 1;
  __REG16 SCR             : 8;
} __ssp_cr0_bits;

/* Control Register 1 (SSP_CR1) */
typedef struct {
  __REG16 LBM             : 1;
  __REG16 SSE             : 1;
  __REG16 MS              : 1;
  __REG16 SOD             : 1;
  __REG16 SSM             : 1;
  __REG16 SSI             : 1;
  __REG16                 :10;
} __ssp_cr1_bits;

/* Status Register (SSP_SR) */
typedef struct {
  __REG16 TFE             : 1;
  __REG16 TNF             : 1;
  __REG16 RNE             : 1;
  __REG16 RFF             : 1;
  __REG16 BSY             : 1;
  __REG16                 :11;
} __ssp_sr_bits;

/* Interrupt Mask Set and Clear Register (SSP_IMSCR) */
typedef struct {
  __REG16 RORIM           : 1;
  __REG16 RTIM            : 1;
  __REG16 RXIM            : 1;
  __REG16 TXIM            : 1;
  __REG16                 :12;
} __ssp_imscr_bits;

/* Raw Interrupt Status Register (SSP_RISR) */
typedef struct {
  __REG16 RORRIS          : 1;
  __REG16 RTRIS           : 1;
  __REG16 RXRIS           : 1;
  __REG16 TXRIS           : 1;
  __REG16                 :12;
} __ssp_risr_bits;

/* Masked Interrupt Status Register (SSP_MISR) */
typedef struct {
  __REG16 RORMIS          : 1;
  __REG16 RTMIS           : 1;
  __REG16 RXMIS           : 1;
  __REG16 TXMIS           : 1;
  __REG16                 :12;
} __ssp_misr_bits;

/* Interrupt Clear Register (SSP_ICR) */
typedef struct {
  __REG16 RORIC           : 1;
  __REG16 RTIC            : 1;
  __REG16                 :14;
} __ssp_icr_bits;

/* DMA Control Register (SSP_DMACR) */
typedef struct {
  __REG16 RXDMAE          : 1;
  __REG16 TXDMAE          : 1;
  __REG16 RXDMASD         : 1;
  __REG16 TXDMASD         : 1;
  __REG16                 :12;
} __ssp_dmacr_bits;

/* Data Register (UART_DR) */
typedef struct {
  __REG16 DATA            : 8;
  __REG16 FE              : 1;
  __REG16 PE              : 1;
  __REG16 BE              : 1;
  __REG16 OE              : 1;
  __REG16                 : 4;
} __uart_dr_bits;

/* Receive Status Register (UART_RSR) */
typedef struct {
  __REG16 FE              : 1;
  __REG16 PE              : 1;
  __REG16 BE              : 1;
  __REG16 OE              : 1;
  __REG16                 :12;
} __uart_rsr_bits;

/* Flag Register (UART_FR) */
typedef struct {
  __REG16 CTS             : 1;
  __REG16                 : 2;
  __REG16 BUSY            : 1;
  __REG16 RXFE            : 1;
  __REG16 TXFF            : 1;
  __REG16 RXFF            : 1;
  __REG16 TXFE            : 1;
  __REG16                 : 8;
} __uart_fr_bits;

/* Break Register (UART_BKR) */
typedef struct {
  __REG16 BRK             : 1;
  __REG16                 :15;
} __uart_bkr_bits;

/* Fractional Baud Rate Register (UART_FBRD) */
typedef struct {
  __REG16 DIVFRAC         : 6;
  __REG16                 :10;
} __uart_fbrd_bits;

/* Line Control Register (UART_LCR) */
typedef struct {
  __REG16                 : 1;
  __REG16 PEN             : 1;
  __REG16 EPS             : 1;
  __REG16 STP2            : 1;
  __REG16 FEN             : 1;
  __REG16 WLEN            : 2;
  __REG16 SPS             : 1;
  __REG16 LINEN           : 1;
  __REG16 LBKLEN          : 4;
  __REG16                 : 3;
} __uart_lcr_bits;

/* Control Register (UART_CR) */
typedef struct {
  __REG16 UARTEN          : 1;
  __REG16                 : 6;
  __REG16 LBE             : 1;
  __REG16 TXE             : 1;
  __REG16 RXE             : 1;
  __REG16                 : 1;
  __REG16 RTS             : 1;
  __REG16                 : 2;
  __REG16 RTSEN           : 1;
  __REG16 CTSEN           : 1;
} __uart_cr_bits;

/* Interrupt FIFO Level Select Register (UART_IFLS) */
typedef struct {
  __REG16 TXIFLSEL        : 3;
  __REG16 RXIFLSEL        : 3;
  __REG16                 :10;
} __uart_ifls_bits;

/* Interrupt Mask Set/Clear Register (UART_IMSC) */
typedef struct {
  __REG16                 : 1;
  __REG16 CTSIM           : 1;
  __REG16                 : 2;
  __REG16 RXIM            : 1;
  __REG16 TXIM            : 1;
  __REG16 RTIM            : 1;
  __REG16 FEIM            : 1;
  __REG16 PEIM            : 1;
  __REG16 BEIM            : 1;
  __REG16 OEIM            : 1;
  __REG16                 : 5;
} __uart_imsc_bits;

/* Raw Interrupt Status Register (UART_RIS) */
typedef struct {
  __REG16                 : 1;
  __REG16 CTSRIS          : 1;
  __REG16                 : 2;
  __REG16 RXRIS           : 1;
  __REG16 TXRIS           : 1;
  __REG16 RTRIS           : 1;
  __REG16 FERIS           : 1;
  __REG16 PERIS           : 1;
  __REG16 BERIS           : 1;
  __REG16 OERIS           : 1;
  __REG16                 : 5;
} __uart_ris_bits;

/* Masked Interrupt Status Register (UART_MIS) */
typedef struct {
  __REG16                 : 1;
  __REG16 CTSMIS          : 1;
  __REG16                 : 2;
  __REG16 RXMIS           : 1;
  __REG16 TXMIS           : 1;
  __REG16 RTMIS           : 1;
  __REG16 FEMIS           : 1;
  __REG16 PEMIS           : 1;
  __REG16 BEMIS           : 1;
  __REG16 OEMIS           : 1;
  __REG16                 : 5;
} __uart_mis_bits;

/* Interrupt Clear Register (UART_ICR) */
typedef struct {
  __REG16                 : 1;
  __REG16 CTSIC           : 1;
  __REG16                 : 2;
  __REG16 RXIC            : 1;
  __REG16 TXIC            : 1;
  __REG16 RTIC            : 1;
  __REG16 FEIC            : 1;
  __REG16 PEIC            : 1;
  __REG16 BEIC            : 1;
  __REG16 OEIC            : 1;
  __REG16                 : 5;
} __uart_icr_bits;

/* DMA Control Register (UART_DMACR) */
typedef struct {
  __REG16 RXDMAE          : 1;
  __REG16 TXDMAE          : 1;
  __REG16 DMAONERR        : 1;
  __REG16 DMASD           : 1;
  __REG16                 :12;
} __uart_dmacr_bits;

/* USB Control Register (USB_CNTR) */
typedef struct {
  __REG16  FRES           : 1;
  __REG16  PDWN           : 1;
  __REG16  LPMODE         : 1;
  __REG16  FSUSP          : 1;
  __REG16  RESUME         : 1;
  __REG16                 : 3;
  __REG16  ESOFM          : 1;
  __REG16  SOFM           : 1;
  __REG16  RESETM         : 1;
  __REG16  SUSPM          : 1;
  __REG16  WKUPM          : 1;
  __REG16  ERRM           : 1;
  __REG16  DOVRM          : 1;
  __REG16  CTRM           : 1;
} __usb_cntr_bits;

/* USB Interrupt Status Register (USB_ISTR) */
typedef struct {
  __REG16  EP_ID          : 4;
  __REG16  DIR            : 1;
  __REG16                 : 3;
  __REG16  ESOF           : 1;
  __REG16  SOF            : 1;
  __REG16  RESET          : 1;
  __REG16  SUSP           : 1;
  __REG16  WKUP           : 1;
  __REG16  ERR            : 1;
  __REG16  DOVR           : 1;
  __REG16  CTR            : 1;
} __usb_st_bits;

/* USB Frame Number Register (USB_FNR) */
typedef struct {
  __REG16  FN             :11;
  __REG16  LSOF           : 2;
  __REG16  LCK            : 1;
  __REG16  RXDM           : 1;
  __REG16  RXDP           : 1;
} __usb_fnr_bits;

/* USB Device Address (USB_DADDR) */
typedef struct {
  __REG16  ADD            : 7;
  __REG16  EF             : 1;
  __REG16                 : 8;
} __usb_daddr_bits;

/* USB Endpoint n Register (USB_EPnR) */
typedef struct {
  __REG16  EA             : 4;
  __REG16  STATTX         : 2;
  __REG16  DTOGTX         : 1;
  __REG16  CTRTX          : 1;
  __REG16  EPKIND         : 1;
  __REG16  EPTYPE         : 2;
  __REG16  SETUP          : 1;
  __REG16  STATRX         : 2;
  __REG16  DTOGRX         : 1;
  __REG16  CTRRX          : 1;
} __usb_epr_bits;

/* ADC Data Register (ADC_Dx) */
typedef struct {
  __REG16  CDATA          :10;
  __REG16                 : 6;
} __adcdx_bits;

/* Control Logic Register 0 (ADC_CLR0) */
typedef struct {
  __REG16  START          : 1;
  __REG16  CAL            : 1;
  __REG16                 :10;
  __REG16  EDGE           : 1;
  __REG16  EDGLEV         : 1;
  __REG16  TRGEN          : 1;
  __REG16                 : 1;
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
  __REG16                 : 3;
  __REG16  JEDGE          : 1;
  __REG16  JTRGEN         : 1;
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
  __REG16  DMA12          : 1;
  __REG16  DMA13          : 1;
  __REG16  DMA14          : 1;
  __REG16  DMA15          : 1;
} __adcdmar_bits;

/* DMA Global Enable Register (ADC_DMAE) */
typedef struct {
  __REG16  DENCH          : 4;
  __REG16                 : 9;
  __REG16  DLEV           : 1;
  __REG16  DXEN           : 1;
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

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/
/***************************************************************************
 **
 **  CFG
 **
 ***************************************************************************/
__IO_REG32_BIT(CFG_GLCONF,            0x60000010,__READ_WRITE ,__cfg_clconf_bits);

/***************************************************************************
 **
 **  MRCC
 **
 ***************************************************************************/
__IO_REG32_BIT(MRCC_CLKCTL,           0x60000020,__READ_WRITE ,__mrcc_clkctl_bits);
__IO_REG32_BIT(MRCC_RFSR,             0x60000024,__READ_WRITE ,__mrcc_rfsr_bits);
__IO_REG32_BIT(MRCC_PWRCTRL,          0x60000028,__READ_WRITE ,__mrcc_pwrctrl_bits);
__IO_REG32_BIT(MRCC_PCLKEN,           0x60000030,__READ_WRITE ,__mrcc_pclken_bits);
__IO_REG32_BIT(MRCC_PSWRES,           0x60000034,__READ_WRITE ,__mrcc_pclken_bits);
__IO_REG32(    MRCC_BKP0,             0x60000040,__READ_WRITE);
__IO_REG32(    MRCC_BKP1,             0x60000044,__READ_WRITE);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIO_P0C0,             0xFFFFE400,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P0C1,             0xFFFFE404,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P0C2,             0xFFFFE408,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P0D,              0xFFFFE40C,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P0M,              0xFFFFE410,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P1C0,             0xFFFFE440,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P1C1,             0xFFFFE444,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P1C2,             0xFFFFE448,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P1D,              0xFFFFE44C,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P1M,              0xFFFFE450,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P2C0,             0xFFFFE480,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P2C1,             0xFFFFE484,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P2C2,             0xFFFFE488,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P2D,              0xFFFFE48C,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_P2M,              0xFFFFE490,__READ_WRITE,__BITS32);
__IO_REG32_BIT(GPIO_REMAP0R,          0xFFFFE420,__READ_WRITE,__gpio_remap0r_bits);
__IO_REG32_BIT(GPIO_REMAP1R,          0xFFFFE424,__READ_WRITE,__gpio_remap1r_bits);

/***************************************************************************
 **
 ** EIC
 **
 ***************************************************************************/
__IO_REG32_BIT(EIC_ICR,               0xFFFFF800,__READ_WRITE,__eicicr_bits);
__IO_REG32_BIT(EIC_CICR,              0xFFFFF804,__READ,      __eiccicr_bits);
__IO_REG32_BIT(EIC_CIPR,              0xFFFFF808,__READ_WRITE,__eiccipr_bits);
__IO_REG32_BIT(EIC_FIER,              0xFFFFF810,__READ_WRITE,__eicfier_bits);
__IO_REG32_BIT(EIC_FIPR,              0xFFFFF814,__READ_WRITE,__eicfipr_bits);
__IO_REG32_BIT(EIC_IVR,               0xFFFFF818,__READ_WRITE,__eicivr_bits);
__IO_REG32_BIT(EIC_FIR,               0xFFFFF81C,__READ_WRITE,__eicfir_bits);
__IO_REG32_BIT(EIC_IER,               0xFFFFF820,__READ_WRITE,__eicier_bits);
__IO_REG32_BIT(EIC_IPR,               0xFFFFF840,__READ_WRITE,__eicipr_bits);
__IO_REG32_BIT(EIC_SIR0,              0xFFFFF860,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR1,              0xFFFFF864,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR2,              0xFFFFF868,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR3,              0xFFFFF86C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR4,              0xFFFFF870,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR5,              0xFFFFF874,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR6,              0xFFFFF878,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR7,              0xFFFFF87C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR8,              0xFFFFF880,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR9,              0xFFFFF884,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR10,             0xFFFFF888,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR11,             0xFFFFF88C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR12,             0xFFFFF890,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR13,             0xFFFFF894,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR14,             0xFFFFF898,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR15,             0xFFFFF89C,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR16,             0xFFFFF8A0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR17,             0xFFFFF8A4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR18,             0xFFFFF8A8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR19,             0xFFFFF8AC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR20,             0xFFFFF8B0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR21,             0xFFFFF8B4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR22,             0xFFFFF8B8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR23,             0xFFFFF8BC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR24,             0xFFFFF8C0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR25,             0xFFFFF8C4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR26,             0xFFFFF8C8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR27,             0xFFFFF8CC,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR28,             0xFFFFF8D0,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR29,             0xFFFFF8D4,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR30,             0xFFFFF8D8,__READ_WRITE,__eicsirn_bits);
__IO_REG32_BIT(EIC_SIR31,             0xFFFFF8DC,__READ_WRITE,__eicsirn_bits);

/***************************************************************************
 **
 ** EXTIT
 **
 ***************************************************************************/
__IO_REG32_BIT(EXTIT_MR,              0xFFFFF400,__READ_WRITE,__extit_mr_bits);
__IO_REG32_BIT(EXTIT_TSR,             0xFFFFF404,__READ_WRITE,__extit_tsr_bits);
__IO_REG32_BIT(EXTIT_SWIR,            0xFFFFF408,__READ_WRITE,__extit_swir_bits);
__IO_REG32_BIT(EXTIT_PR,              0xFFFFF40C,__READ_WRITE,__extit_pr_bits);

/***************************************************************************
 **
 ** DMA
 **
 ***************************************************************************/
__IO_REG16(    DMA_SOURCEL0,          0xFFFFEC00,__READ_WRITE);
__IO_REG16(    DMA_SOURCEH0,          0xFFFFEC04,__READ_WRITE);
__IO_REG16(    DMA_DESTL0,            0xFFFFEC08,__READ_WRITE);
__IO_REG16(    DMA_DESTH0,            0xFFFFEC0C,__READ_WRITE);
__IO_REG16(    DMA_MAX0,              0xFFFFEC10,__READ_WRITE);
__IO_REG16_BIT(DMA_CTRL0,             0xFFFFEC14,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(    DMA_SOCURRH0,          0xFFFFEC18,__READ);
__IO_REG16(    DMA_SOCURRL0,          0xFFFFEC1C,__READ);
__IO_REG16(    DMA_DECURRH0,          0xFFFFEC20,__READ);
__IO_REG16(    DMA_DECURRL0,          0xFFFFEC24,__READ);
__IO_REG16(    DMA_TCNT0,             0xFFFFEC28,__READ);
__IO_REG16(    DMA_LUBUFF0,           0xFFFFEC2C,__READ_WRITE);
__IO_REG16(    DMA_SOURCEL1,          0xFFFFEC40,__READ_WRITE);
__IO_REG16(    DMA_SOURCEH1,          0xFFFFEC44,__READ_WRITE);
__IO_REG16(    DMA_DESTL1,            0xFFFFEC48,__READ_WRITE);
__IO_REG16(    DMA_DESTH1,            0xFFFFEC4C,__READ_WRITE);
__IO_REG16(    DMA_MAX1,              0xFFFFEC50,__READ_WRITE);
__IO_REG16_BIT(DMA_CTRL1,             0xFFFFEC54,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(    DMA_SOCURRH1,          0xFFFFEC58,__READ);
__IO_REG16(    DMA_SOCURRL1,          0xFFFFEC5C,__READ);
__IO_REG16(    DMA_DECURRH1,          0xFFFFEC60,__READ);
__IO_REG16(    DMA_DECURRL1,          0xFFFFEC64,__READ);
__IO_REG16(    DMA_TCNT1,             0xFFFFEC68,__READ);
__IO_REG16(    DMA_LUBUFF1,           0xFFFFEC6C,__READ);
__IO_REG16(    DMA_SOURCEL2,          0xFFFFEC80,__READ_WRITE);
__IO_REG16(    DMA_SOURCEH2,          0xFFFFEC84,__READ_WRITE);
__IO_REG16(    DMA_DESTL2,            0xFFFFEC88,__READ_WRITE);
__IO_REG16(    DMA_DESTH2,            0xFFFFEC8C,__READ_WRITE);
__IO_REG16(    DMA_MAX2,              0xFFFFEC90,__READ_WRITE);
__IO_REG16_BIT(DMA_CTRL2,             0xFFFFEC94,__READ_WRITE,__dmanctrlx_bits);
__IO_REG16(    DMA_SOCURRH2,          0xFFFFEC98,__READ);
__IO_REG16(    DMA_SOCURRL2,          0xFFFFEC9C,__READ);
__IO_REG16(    DMA_DECURRH2,          0xFFFFECA0,__READ);
__IO_REG16(    DMA_DECURRL2,          0xFFFFECA4,__READ);
__IO_REG16(    DMA_TCNT2,             0xFFFFECA8,__READ);
__IO_REG16(    DMA_LUBUFF2,           0xFFFFECAC,__READ_WRITE);
__IO_REG16(    DMA_SOURCEL3,          0xFFFFECC0,__READ_WRITE);
__IO_REG16(    DMA_SOURCEH3,          0xFFFFECC4,__READ_WRITE);
__IO_REG16(    DMA_DESTL3,            0xFFFFECC8,__READ_WRITE);
__IO_REG16(    DMA_DESTH3,            0xFFFFECCC,__READ_WRITE);
__IO_REG16(    DMA_MAX3,              0xFFFFECD0,__READ_WRITE);
__IO_REG16_BIT(DMA_CTRL3,             0xFFFFECD4,__READ_WRITE,__dmanctrl3_bits);
__IO_REG16(    DMA_SOCURRH3,          0xFFFFECD8,__READ);
__IO_REG16(    DMA_SOCURRL3,          0xFFFFECDC,__READ);
__IO_REG16(    DMA_DECURRH3,          0xFFFFECE0,__READ);
__IO_REG16(    DMA_DECURRL3,          0xFFFFECE4,__READ);
__IO_REG16(    DMA_TCNT3,             0xFFFFECE8,__READ);
__IO_REG16(    DMA_LUBUFF3,           0xFFFFECEC,__READ_WRITE);
__IO_REG16_BIT(DMA_MASK,              0xFFFFECF0,__READ_WRITE,__dmanmask_bits);
__IO_REG16_BIT(DMA_CLR,               0xFFFFECF4,__WRITE     ,__dmanclr_bits);
__IO_REG16_BIT(DMA_STATUS,            0xFFFFECF8,__READ      ,__dmanstatus_bits);
__IO_REG16_BIT(DMA_LAST,              0xFFFFECFC,__READ_WRITE,__dmanlast_bits);

/***************************************************************************
 **
 ** SMI
 **
 ***************************************************************************/
__IO_REG32_BIT(SMI_CR1,               0x90000000,__READ_WRITE,__smi_cr1_bits);
__IO_REG32_BIT(SMI_CR2,               0x90000004,__READ_WRITE,__smi_cr2_bits);
__IO_REG32_BIT(SMI_SR,                0x90000008,__READ_WRITE,__smi_sr_bits);
__IO_REG32_BIT(SMI_TR,                0x9000000C,__READ_WRITE,__smi_tr_bits);
__IO_REG32_BIT(SMI_RR,                0x90000010,__READ      ,__smi_tr_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG16_BIT(RTC_CRH,               0xFFFFF000,__READ_WRITE,__rtccrh_bits);
__IO_REG16_BIT(RTC_CRL,               0xFFFFF004,__READ_WRITE,__rtccrl_bits);
__IO_REG16_BIT(RTC_PRLH,              0xFFFFF008,__WRITE     ,__rtcprlh_bits);
__IO_REG16(    RTC_PRLL,              0xFFFFF00C,__WRITE);
__IO_REG16_BIT(RTC_DIVH,              0xFFFFF010,__READ      ,__rtcdivh_bits);
__IO_REG16(    RTC_DIVL,              0xFFFFF014,__READ);
__IO_REG16(    RTC_CNTH,              0xFFFFF018,__READ_WRITE);
__IO_REG16(    RTC_CNTL,              0xFFFFF01C,__READ_WRITE);
__IO_REG16(    RTC_ALRH,              0xFFFFF020,__WRITE);
__IO_REG16(    RTC_ALRL,              0xFFFFF024,__WRITE);

/***************************************************************************
 **
 ** WDG
 **
 ***************************************************************************/
__IO_REG16_BIT(WDG_CR,                0xFFFFB000,__READ_WRITE,__wdgcr_bits);
__IO_REG8(     WDG_PR,                0xFFFFB004,__READ_WRITE);
__IO_REG16(    WDG_VR,                0xFFFFB008,__READ_WRITE);
__IO_REG16(    WDG_CNT,               0xFFFFB00C,__READ);
__IO_REG16_BIT(WDG_SR,                0xFFFFB010,__READ_WRITE,__wdgsr_bits);
__IO_REG16_BIT(WDG_MR,                0xFFFFB014,__READ_WRITE,__wdgmr_bits);
__IO_REG16(    WDG_KR,                0xFFFFB018,__READ_WRITE);

/***************************************************************************
 **
 ** TB
 **
 ***************************************************************************/
__IO_REG16_BIT(TB_CR,                 0xFFFF8800,__READ_WRITE,__tb_cr_bits);
__IO_REG16_BIT(TB_IMCR,               0xFFFF8808,__READ_WRITE,__tb_imcr_bits);
__IO_REG16_BIT(TB_RSR,                0xFFFF8818,__READ_WRITE,__tb_rsr_bits);
__IO_REG16_BIT(TB_RER,                0xFFFF881C,__READ_WRITE,__tb_rer_bits);
__IO_REG16_BIT(TB_ISR,                0xFFFF8820,__READ_WRITE,__tb_isr_bits);
__IO_REG16(    TB_CNT,                0xFFFF8824,__READ_WRITE);
__IO_REG16(    TB_PSC,                0xFFFF8828,__READ_WRITE);
__IO_REG16(    TB_ARR,                0xFFFF8830,__READ_WRITE);
__IO_REG16(    TB_ICR1,               0xFFFF884C,__READ);

/***************************************************************************
 **
 ** TIM0
 **
 ***************************************************************************/
__IO_REG16_BIT(TIM0_CR,               0xFFFF8C00,__READ_WRITE,__tim_cr_bits);
__IO_REG16_BIT(TIM0_SCR,              0xFFFF8C04,__READ_WRITE,__tim_scr_bits);
__IO_REG16_BIT(TIM0_IMCR,             0xFFFF8C08,__READ_WRITE,__tim_imcr_bits);
__IO_REG16_BIT(TIM0_OMR1,             0xFFFF8C0C,__READ_WRITE,__tim_omr1_bits);
__IO_REG16_BIT(TIM0_RSR,              0xFFFF8C18,__READ_WRITE,__tim_rsr_bits);
__IO_REG16_BIT(TIM0_RER,              0xFFFF8C1C,__READ_WRITE,__tim_rer_bits);
__IO_REG16_BIT(TIM0_ISR,              0xFFFF8C20,__READ_WRITE,__tim_isr_bits);
__IO_REG16(    TIM0_CNT,              0xFFFF8C24,__READ_WRITE);
__IO_REG16(    TIM0_PSC,              0xFFFF8C28,__READ_WRITE);
__IO_REG16(    TIM0_ARR,              0xFFFF8C30,__READ_WRITE);
__IO_REG16(    TIM0_OCR1,             0xFFFF8C34,__READ_WRITE);
__IO_REG16(    TIM0_OCR2,             0xFFFF8C38,__READ_WRITE);
__IO_REG16(    TIM0_ICR1,             0xFFFF8C4C,__READ);
__IO_REG16(    TIM0_ICR2,             0xFFFF8C50,__READ);
__IO_REG16(    TIM0_DMAB,             0xFFFF8C60,__READ_WRITE);

/***************************************************************************
 **
 ** TIM1
 **
 ***************************************************************************/
__IO_REG16_BIT(TIM1_CR,               0xFFFF9000,__READ_WRITE,__tim_cr_bits);
__IO_REG16_BIT(TIM1_SCR,              0xFFFF9004,__READ_WRITE,__tim_scr_bits);
__IO_REG16_BIT(TIM1_IMCR,             0xFFFF9008,__READ_WRITE,__tim_imcr_bits);
__IO_REG16_BIT(TIM1_OMR1,             0xFFFF900C,__READ_WRITE,__tim_omr1_bits);
__IO_REG16_BIT(TIM1_RSR,              0xFFFF9018,__READ_WRITE,__tim_rsr_bits);
__IO_REG16_BIT(TIM1_RER,              0xFFFF901C,__READ_WRITE,__tim_rer_bits);
__IO_REG16_BIT(TIM1_ISR,              0xFFFF9020,__READ_WRITE,__tim_isr_bits);
__IO_REG16(    TIM1_CNT,              0xFFFF9024,__READ_WRITE);
__IO_REG16(    TIM1_PSC,              0xFFFF9028,__READ_WRITE);
__IO_REG16(    TIM1_ARR,              0xFFFF9030,__READ_WRITE);
__IO_REG16(    TIM1_OCR1,             0xFFFF9034,__READ_WRITE);
__IO_REG16(    TIM1_OCR2,             0xFFFF9038,__READ_WRITE);
__IO_REG16(    TIM1_ICR1,             0xFFFF904C,__READ);
__IO_REG16(    TIM1_ICR2,             0xFFFF9050,__READ);
__IO_REG16(    TIM1_DMAB,             0xFFFF9060,__READ_WRITE);

/***************************************************************************
 **
 ** TIM2
 **
 ***************************************************************************/
__IO_REG16_BIT(TIM2_CR,               0xFFFF9400,__READ_WRITE,__tim_cr_bits);
__IO_REG16_BIT(TIM2_SCR,              0xFFFF9404,__READ_WRITE,__tim_scr_bits);
__IO_REG16_BIT(TIM2_IMCR,             0xFFFF9408,__READ_WRITE,__tim_imcr_bits);
__IO_REG16_BIT(TIM2_OMR1,             0xFFFF940C,__READ_WRITE,__tim_omr1_bits);
__IO_REG16_BIT(TIM2_RSR,              0xFFFF9418,__READ_WRITE,__tim_rsr_bits);
__IO_REG16_BIT(TIM2_RER,              0xFFFF941C,__READ_WRITE,__tim_rer_bits);
__IO_REG16_BIT(TIM2_ISR,              0xFFFF9420,__READ_WRITE,__tim_isr_bits);
__IO_REG16(    TIM2_CNT,              0xFFFF9424,__READ_WRITE);
__IO_REG16(    TIM2_PSC,              0xFFFF9428,__READ_WRITE);
__IO_REG16(    TIM2_ARR,              0xFFFF9430,__READ_WRITE);
__IO_REG16(    TIM2_OCR1,             0xFFFF9434,__READ_WRITE);
__IO_REG16(    TIM2_OCR2,             0xFFFF9438,__READ_WRITE);
__IO_REG16(    TIM2_ICR1,             0xFFFF944C,__READ);
__IO_REG16(    TIM2_ICR2,             0xFFFF9450,__READ);
__IO_REG16(    TIM2_DMAB,             0xFFFF9460,__READ_WRITE);

/***************************************************************************
 **
 ** PWM
 **
 ***************************************************************************/
__IO_REG16_BIT(PWM_CR,                0xFFFF9800,__READ_WRITE,__pwm_cr_bits);
__IO_REG16_BIT(PWM_SCR,               0xFFFF9804,__READ_WRITE,__pwm_scr_bits);
__IO_REG16_BIT(PWM_OMR1,              0xFFFF980C,__READ_WRITE,__pwm_omr1_bits);
__IO_REG16_BIT(PWM_OMR2,              0xFFFF9810,__READ_WRITE,__pwm_omr2_bits);
__IO_REG16_BIT(PWM_RSR,               0xFFFF9818,__READ_WRITE,__pwm_rsr_bits);
__IO_REG16_BIT(PWM_RER,               0xFFFF981C,__READ_WRITE,__pwm_rer_bits);
__IO_REG16_BIT(PWM_ISR,               0xFFFF9820,__READ_WRITE,__pwm_isr_bits);
__IO_REG16(    PWM_CNT,               0xFFFF9824,__READ_WRITE);
__IO_REG16(    PWM_PSC,               0xFFFF9828,__READ_WRITE);
__IO_REG8(     PWM_RCR,               0xFFFF982C,__READ_WRITE);
__IO_REG16(    PWM_ARR,               0xFFFF9830,__READ_WRITE);
__IO_REG16(    PWM_OCR1,              0xFFFF9834,__READ_WRITE);
__IO_REG16(    PWM_OCR2,              0xFFFF9838,__READ_WRITE);
__IO_REG16(    PWM_OCR3,              0xFFFF983C,__READ_WRITE);
__IO_REG16_BIT(PWM_DTR,               0xFFFF985C,__READ_WRITE,__pwm_dtr_bits);
__IO_REG16(    PWM_DMAB,              0xFFFF9860,__READ_WRITE);

/***************************************************************************
 **
 **  CAN
 **
 ***************************************************************************/
__IO_REG16_BIT(CAN_CR,                0xFFFFC400,__READ_WRITE,__canncr_bits);
__IO_REG16_BIT(CAN_SR,                0xFFFFC404,__READ_WRITE,__cannsr_bits);
__IO_REG16_BIT(CAN_ERR,               0xFFFFC408,__READ      ,__cannerr_bits);
__IO_REG16_BIT(CAN_BTR,               0xFFFFC40C,__READ_WRITE,__cannbtr_bits);
__IO_REG16(    CAN_IDR,               0xFFFFC410,__READ);
__IO_REG16_BIT(CAN_TESTR,             0xFFFFC414,__READ_WRITE,__canntestr_bits);
__IO_REG16_BIT(CAN_BRPR,              0xFFFFC418,__READ_WRITE,__cannbrpr_bits);
__IO_REG16_BIT(CAN_IF1_CRR,           0xFFFFC420,__READ_WRITE,__cannifxcrr_bits);
__IO_REG16_BIT(CAN_IF1_CMR,           0xFFFFC424,__READ_WRITE,__cannifxcmr_bits);
__IO_REG16_BIT(CAN_IF1_M1R,           0xFFFFC428,__READ_WRITE,__cannifxm1r_bits);
__IO_REG16_BIT(CAN_IF1_M2R,           0xFFFFC42C,__READ_WRITE,__cannifxm2r_bits);
__IO_REG16_BIT(CAN_IF1_A1R,           0xFFFFC430,__READ_WRITE,__cannifxa1r_bits);
__IO_REG16_BIT(CAN_IF1_A2R,           0xFFFFC434,__READ_WRITE,__cannifxa2r_bits);
__IO_REG16_BIT(CAN_IF1_MCR,           0xFFFFC438,__READ_WRITE,__cannifxmcr_bits);
__IO_REG16_BIT(CAN_IF1_DA1R,          0xFFFFC43C,__READ_WRITE,__cannifxda1r_bits);
__IO_REG16_BIT(CAN_IF1_DA2R,          0xFFFFC440,__READ_WRITE,__cannifxda2r_bits);
__IO_REG16_BIT(CAN_IF1_DB1R,          0xFFFFC444,__READ_WRITE,__cannifxdb1r_bits);
__IO_REG16_BIT(CAN_IF1_DB2R,          0xFFFFC448,__READ_WRITE,__cannifxdb2r_bits);
__IO_REG16_BIT(CAN_IF2_CRR,           0xFFFFC480,__READ_WRITE,__cannifxcrr_bits);
__IO_REG16_BIT(CAN_IF2_CMR,           0xFFFFC484,__READ_WRITE,__cannifxcmr_bits);
__IO_REG16_BIT(CAN_IF2_M1R,           0xFFFFC488,__READ_WRITE,__cannifxm1r_bits);
__IO_REG16_BIT(CAN_IF2_M2R,           0xFFFFC48C,__READ_WRITE,__cannifxm2r_bits);
__IO_REG16_BIT(CAN_IF2_A1R,           0xFFFFC490,__READ_WRITE,__cannifxa1r_bits);
__IO_REG16_BIT(CAN_IF2_A2R,           0xFFFFC494,__READ_WRITE,__cannifxa2r_bits);
__IO_REG16_BIT(CAN_IF2_MCR,           0xFFFFC498,__READ_WRITE,__cannifxmcr_bits);
__IO_REG16_BIT(CAN_IF2_DA1R,          0xFFFFC49c,__READ_WRITE,__cannifxda1r_bits);
__IO_REG16_BIT(CAN_IF2_DA2R,          0xFFFFC4A0,__READ_WRITE,__cannifxda2r_bits);
__IO_REG16_BIT(CAN_IF2_DB1R,          0xFFFFC4A4,__READ_WRITE,__cannifxdb1r_bits);
__IO_REG16_BIT(CAN_IF2_DB2R,          0xFFFFC4A8,__READ_WRITE,__cannifxdb2r_bits);
__IO_REG32(    CAN_TXR1R,             0xFFFFC500,__READ);
__IO_REG32(    CAN_TXR2R,             0xFFFFC504,__READ);
__IO_REG32(    CAN_ND1R,              0xFFFFC520,__READ);
__IO_REG32(    CAN_ND2R,              0xFFFFC524,__READ);
__IO_REG32(    CAN_IP1R,              0xFFFFC540,__READ);
__IO_REG32(    CAN_IP2R,              0xFFFFC544,__READ);
__IO_REG32(    CAN_MV1R,              0xFFFFC560,__READ);
__IO_REG32(    CAN_MV2R,              0xFFFFC564,__READ);

/***************************************************************************
 **
 ** I2C0
 **
 ***************************************************************************/
__IO_REG8_BIT( I2C0_CR,               0xFFFFCC00,__READ_WRITE,__i2cncr_bits);
__IO_REG8_BIT( I2C0_SR1,              0xFFFFCC04,__READ      ,__i2cnsr1_bits);
__IO_REG8_BIT( I2C0_SR2,              0xFFFFCC08,__READ      ,__i2cnsr2_bits);
__IO_REG8_BIT( I2C0_CCR,              0xFFFFCC0C,__READ_WRITE,__i2cnccr_bits);
__IO_REG8_BIT( I2C0_OAR1,             0xFFFFCC10,__READ_WRITE,__i2cnoar1_bits);
__IO_REG8_BIT( I2C0_OAR2,             0xFFFFCC14,__READ_WRITE,__i2cnoar2_bits);
__IO_REG8(     I2C0_DR,               0xFFFFCC18,__READ_WRITE);
__IO_REG8_BIT( I2C0_ECCR,             0xFFFFCC1C,__READ_WRITE,__i2cneccr_bits);

/***************************************************************************
 **
 **  SPI0
 **
 ***************************************************************************/
__IO_REG16_BIT(SSP0_CR0,              0xFFFFB800,__READ_WRITE,__ssp_cr0_bits);
__IO_REG16_BIT(SSP0_CR1,              0xFFFFB804,__READ_WRITE,__ssp_cr1_bits);
__IO_REG16(    SSP0_DR,               0xFFFFB808,__READ_WRITE);
__IO_REG16_BIT(SSP0_SR,               0xFFFFB80C,__READ      ,__ssp_sr_bits);
__IO_REG8(     SSP0_PR,               0xFFFFB810,__READ_WRITE);
__IO_REG16_BIT(SSP0_IMSCR,            0xFFFFB814,__READ_WRITE,__ssp_imscr_bits);
__IO_REG16_BIT(SSP0_RISR,             0xFFFFB818,__READ      ,__ssp_risr_bits);
__IO_REG16_BIT(SSP0_MISR,             0xFFFFB81C,__READ      ,__ssp_misr_bits);
__IO_REG16_BIT(SSP0_ICR,              0xFFFFB820,__WRITE     ,__ssp_icr_bits);
__IO_REG16_BIT(SSP0_DMACR,            0xFFFFB824,__READ_WRITE,__ssp_dmacr_bits);

/***************************************************************************
 **
 **  SPI1
 **
 ***************************************************************************/
__IO_REG16_BIT(SSP1_CR0,              0xFFFFBC00,__READ_WRITE,__ssp_cr0_bits);
__IO_REG16_BIT(SSP1_CR1,              0xFFFFBC04,__READ_WRITE,__ssp_cr1_bits);
__IO_REG16(    SSP1_DR,               0xFFFFBC08,__READ_WRITE);
__IO_REG16_BIT(SSP1_SR,               0xFFFFBC0C,__READ      ,__ssp_sr_bits);
__IO_REG8(     SSP1_PR,               0xFFFFBC10,__READ_WRITE);
__IO_REG16_BIT(SSP1_IMSCR,            0xFFFFBC14,__READ_WRITE,__ssp_imscr_bits);
__IO_REG16_BIT(SSP1_RISR,             0xFFFFBC18,__READ      ,__ssp_risr_bits);
__IO_REG16_BIT(SSP1_MISR,             0xFFFFBC1C,__READ      ,__ssp_misr_bits);
__IO_REG16_BIT(SSP1_ICR,              0xFFFFBC20,__WRITE     ,__ssp_icr_bits);
__IO_REG16_BIT(SSP1_DMACR,            0xFFFFBC24,__READ_WRITE,__ssp_dmacr_bits);

/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/
__IO_REG16_BIT(UART0_DR,              0xFFFFD400,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART0_RSR,             0xFFFFD404,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART0_FR,              0xFFFFD418,__READ      ,__uart_fr_bits);
__IO_REG16_BIT(UART0_BKR,             0xFFFFD41C,__READ_WRITE,__uart_bkr_bits);
__IO_REG16(    UART0_IBRD,            0xFFFFD424,__READ_WRITE);
__IO_REG16_BIT(UART0_FBRD,            0xFFFFD428,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART0_LCR,             0xFFFFD42C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART0_CR,              0xFFFFD430,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART0_IFLS,            0xFFFFD434,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART0_IMSC,            0xFFFFD438,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART0_RIS,             0xFFFFD43C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART0_MIS,             0xFFFFD440,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART0_ICR,             0xFFFFD444,__WRITE     ,__uart_icr_bits);
__IO_REG16_BIT(UART0_DMACR,           0xFFFFD448,__READ_WRITE,__uart_dmacr_bits);

/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG16_BIT(UART1_DR,              0xFFFFD800,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART1_RSR,             0xFFFFD804,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART1_FR,              0xFFFFD818,__READ      ,__uart_fr_bits);
__IO_REG16_BIT(UART1_BKR,             0xFFFFD81C,__READ_WRITE,__uart_bkr_bits);
__IO_REG16(    UART1_IBRD,            0xFFFFD824,__READ_WRITE);
__IO_REG16_BIT(UART1_FBRD,            0xFFFFD828,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART1_LCR,             0xFFFFD82C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART1_CR,              0xFFFFD830,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART1_IFLS,            0xFFFFD834,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART1_IMSC,            0xFFFFD838,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART1_RIS,             0xFFFFD83C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART1_MIS,             0xFFFFD840,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART1_ICR,             0xFFFFD844,__WRITE     ,__uart_icr_bits);
__IO_REG16_BIT(UART1_DMACR,           0xFFFFD848,__READ_WRITE,__uart_dmacr_bits);

/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG16_BIT(UART2_DR,              0xFFFFDC00,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART2_RSR,             0xFFFFDC04,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART2_FR,              0xFFFFDC18,__READ      ,__uart_fr_bits);
__IO_REG16_BIT(UART2_BKR,             0xFFFFDC1C,__READ_WRITE,__uart_bkr_bits);
__IO_REG16(    UART2_IBRD,            0xFFFFDC24,__READ_WRITE);
__IO_REG16_BIT(UART2_FBRD,            0xFFFFDC28,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART2_LCR,             0xFFFFDC2C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART2_CR,              0xFFFFDC30,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART2_IFLS,            0xFFFFDC34,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART2_IMSC,            0xFFFFDC38,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART2_RIS,             0xFFFFDC3C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART2_MIS,             0xFFFFDC40,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART2_ICR,             0xFFFFDC44,__WRITE     ,__uart_icr_bits);
__IO_REG16_BIT(UART2_DMACR,           0xFFFFDC48,__READ_WRITE,__uart_dmacr_bits);

/***************************************************************************
 **
 **  USB
 **
 ***************************************************************************/
__IO_REG16_BIT(USB_EP0R,              0xFFFFA800,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP1R,              0xFFFFA804,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP2R,              0xFFFFA808,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP3R,              0xFFFFA80C,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP4R,              0xFFFFA810,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP5R,              0xFFFFA814,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP6R,              0xFFFFA818,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP7R,              0xFFFFA81C,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_CNTR,              0xFFFFA840,__READ_WRITE,__usb_cntr_bits);
__IO_REG16_BIT(USB_ISTR,              0xFFFFA844,__READ_WRITE,__usb_st_bits);
__IO_REG16_BIT(USB_FNR,               0xFFFFA848,__READ      ,__usb_fnr_bits);
__IO_REG16_BIT(USB_DADDR,             0xFFFFA84C,__READ_WRITE,__usb_daddr_bits);
__IO_REG16(    USB_BTABLE,            0xFFFFA850,__READ_WRITE);

/***************************************************************************
 **
 ** Analog/Digital Converter ADC
 **
 ***************************************************************************/
__IO_REG16_BIT(ADC_CLR0,              0xFFFF8400,__READ_WRITE,__adcclr0_bits);
__IO_REG16_BIT(ADC_CLR1,              0xFFFF8404,__READ_WRITE,__adcclr1_bits);
__IO_REG16_BIT(ADC_CLR2,              0xFFFF8408,__READ_WRITE,__adcclr2_bits);
__IO_REG16_BIT(ADC_CLR3,              0xFFFF840C,__READ_WRITE,__adcclr3_bits);
__IO_REG16_BIT(ADC_CLR4,              0xFFFF8410,__READ_WRITE,__adcclr4_bits);
__IO_REG16_BIT(ADC_TRA0,              0xFFFF8414,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRA1,              0xFFFF8418,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRA2,              0xFFFF841C,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRA3,              0xFFFF8420,__READ_WRITE,__adctrax_bits);
__IO_REG16_BIT(ADC_TRB0,              0xFFFF8424,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_TRB1,              0xFFFF8428,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_TRB2,              0xFFFF842C,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_TRB3,              0xFFFF8430,__READ_WRITE,__adctrbx_bits);
__IO_REG16_BIT(ADC_DMAR,              0xFFFF8434,__READ_WRITE,__adcdmar_bits);
__IO_REG16_BIT(ADC_DMAE,              0xFFFF8444,__READ_WRITE,__adcdmae_bits);
__IO_REG16_BIT(ADC_PBR,               0xFFFF8448,__READ_WRITE,__adcpbr_bits);
__IO_REG16_BIT(ADC_IMR,               0xFFFF844C,__READ_WRITE,__adcimr_bits);
__IO_REG16_BIT(ADC_D0,                0xFFFF8450,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D1,                0xFFFF8454,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D2,                0xFFFF8458,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D3,                0xFFFF845C,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D4,                0xFFFF8460,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D5,                0xFFFF8464,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D6,                0xFFFF8468,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D7,                0xFFFF846C,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D8,                0xFFFF8470,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D9,                0xFFFF8474,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D10,               0xFFFF8478,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D11,               0xFFFF847C,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D12,               0xFFFF8480,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D13,               0xFFFF8484,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D14,               0xFFFF8488,__READ,      __adcdx_bits);
__IO_REG16_BIT(ADC_D15,               0xFFFF848C,__READ,      __adcdx_bits);

/***************************************************************************
 **
 **  FLASH
 **
 ***************************************************************************/
__IO_REG32_BIT(FLASH_CR0,             0x20100000,__READ_WRITE,__flashctrl0_bits);
__IO_REG32_BIT(FLASH_CR1,             0x20100004,__READ_WRITE,__flashctrl1_bits);
__IO_REG32(    FLASH_DR0,             0x20100008,__READ_WRITE);
__IO_REG32(    FLASH_DR1,             0x2010000C,__READ_WRITE);
__IO_REG32_BIT(FLASH_AR,              0x20100010,__READ_WRITE,__flashadd_bits);
__IO_REG32_BIT(FLASH_ER,              0x20100014,__READ_WRITE,__flasherr_bits);
__IO_REG32_BIT(FLASH_NVWPAR,          0x2010DFB0,__READ_WRITE,__flashwrprot_bits);
__IO_REG32_BIT(FLASH_NVAPR0,          0x2010DFB8,__READ_WRITE,__flashaccprot0_bits);
__IO_REG32_BIT(FLASH_NVAPR1,          0x2010DFBC,__READ_WRITE,__flashaccprot1_bits);


/* Assembler-specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  STR750 IRQ Interrupt Vector Table
 **
 ***************************************************************************/
#define WAKEUP_INT       0
#define SPT3_OC2_INT     1
#define SPT3_OC1_INT     2
#define SPT3_IC12_INT    3
#define SPT3_UPDATE_INT  4
#define SPT2_OC2_INT     5
#define SPT2_OC1_INT     6
#define SPT2_IC12_INT    7
#define SPT2_UPDATE_INT  8
#define SPT1_OC2_INT     9
#define SPT1_OC1_INT    10
#define SPT1_IC12_INT   11
#define SPT1_UPDATE_INT 12
#define SPT4_OC123_INT  13
#define SPT4_EMG_INT    14
#define SPT4_UPDATE_INT 15
#define I2C_INT         16
#define SPI1_INT        17
#define SPI0_INT        18
#define UART2_INT       19
#define UART1_INT       20
#define UART0_INT       21
#define CAN_INT         22
#define USB_LP_INT      23
#define USB_HP_INT      24
#define ADC_INT         25
#define DMA_INT         26
#define EXTIT_INT       27
#define MRCC_INT        28
#define FLASH_INT       29
#define RTC_INT         30
#define SPT0_INT        31

/***************************************************************************
 **
 **  STR750 FIQ Interrupt Vector Table
 **
 ***************************************************************************/
#define INT0_INT         0
#define WDG_INT          1

#endif    /* __IOSTR750_H */
