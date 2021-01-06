/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    NXP LPC2378
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1.2.3 $
 **
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/

#ifndef __IOLPC2378_H
#define __IOLPC2378_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    LPC2378 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/
#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#if __LITTLE_ENDIAN__ == 0
#error This file should only be compiled in little endian mode
#endif

/* Memory mapping control register */
typedef struct{
__REG32 MAP         : 2;
__REG32             :30;
} __memmap_bits;

/* Reset Source Identification Register */
typedef struct{
__REG32 POR         : 1;
__REG32 EXTR        : 1;
__REG32 WDTR        : 1;
__REG32 BODR        : 1;
__REG32             :28;
} __rsir_bits;

/* External interrupt register */
typedef struct{
__REG32 EINT0       : 1;
__REG32 EINT1       : 1;
__REG32 EINT2       : 1;
__REG32 EINT3       : 1;
__REG32             :28;
} __extint_bits;

/* External Interrupt Mode Register */
typedef struct{
__REG32 EXTMODE0    : 1;
__REG32 EXTMODE1    : 1;
__REG32 EXTMODE2    : 1;
__REG32 EXTMODE3    : 1;
__REG32             :28;
} __extmode_bits;

/* External Interrupt Polarity Register */
typedef struct{
__REG32 EXTPOLAR0   : 1;
__REG32 EXTPOLAR1   : 1;
__REG32 EXTPOLAR2   : 1;
__REG32 EXTPOLAR3   : 1;
__REG32             :28;
} __extpolar_bits;

/* System Controls and Status register */
typedef struct{
__REG32 GPIOM       : 1;
__REG32 EMCRD       : 1;
__REG32             : 1;
__REG32 MCIPWR      : 1;
__REG32 OSCRANGE    : 1;
__REG32 OSCEN       : 1;
__REG32 OSCSTAT     : 1;
__REG32             :25;
} __scs_bits;

/* AHB Arbiter Configuration Register*/
typedef struct{
__REG32 SHDL        : 1;
__REG32 BB          : 2;
__REG32 QT          : 1;
__REG32 QS          : 4;
__REG32 DM          : 4;
__REG32 EP1         : 4;
__REG32 EP2         : 4;
__REG32 EP3         : 4;
__REG32 EP4         : 4;
__REG32             : 4;
} __ahbcfg1_bits;

typedef struct{
__REG32 SHDL        : 1;
__REG32 BB          : 2;
__REG32 QT          : 1;
__REG32 QS          : 4;
__REG32 DM          : 4;
__REG32 EP1         : 4;
__REG32 EP2         : 4;
__REG32             :12;
} __ahbcfg2_bits;

/* Clock Soucre Select register */
typedef struct{
__REG32 CLKSRC      : 2;
__REG32             :30;
} __clksrcsel_bits;

/* IRC Trim Register (IRCTRIM - 0xE01FC1A4) */
typedef struct{
__REG32 IRCTRIM     : 8;
__REG32             :24;
} __irctrim_bits;

/* APB Divider Register */
typedef struct{
__REG32 APBDIV  : 2;
__REG32         :30;
} __apbdiv_bits;

/* CPU Clock Configuration register */
typedef struct{
__REG32 CCLKSEL     : 8;
__REG32             :24;
} __cclkcfg_bits;

/* USB Clock Configuration register */
typedef struct{
__REG32 USBSEL      : 4;
__REG32             :28;
} __usbclkcfg_bits;

/* Peripheral Clock Selection registers 0 */
typedef struct{
__REG32 PCLK_WDT    : 2;
__REG32 PCLK_TIMER0 : 2;
__REG32 PCLK_TIMER1 : 2;
__REG32 PCLK_UART0  : 2;
__REG32 PCLK_UART1  : 2;
__REG32 PCLK_PWM0   : 2;
__REG32 PCLK_PWM1   : 2;
__REG32 PCLK_I2C0   : 2;
__REG32 PCLK_SPI    : 2;
__REG32 PCLK_RTC    : 2;
__REG32 PCLK_SSP1   : 2;
__REG32 PCLK_DAC    : 2;
__REG32 PCLK_ADC    : 2;
__REG32 PCLK_CAN1   : 2;
__REG32 PCLK_CAN2   : 2;
__REG32 PCLK_ACF    : 2;
} __pclksel0_bits;

/* Peripheral Clock Selection registers 1 */
typedef struct{
__REG32 PCLK_BAT_RAM: 2;
__REG32 PCLK_GPIO   : 2;
__REG32 PCLK_PCB    : 2;
__REG32 PCLK_I2C1   : 2;
__REG32             : 2;
__REG32 PCLK_SSP0   : 2;
__REG32 PCLK_TIMER2 : 2;
__REG32 PCLK_TIMER3 : 2;
__REG32 PCLK_UART2  : 2;
__REG32 PCLK_UART3  : 2;
__REG32 PCLK_I2C2   : 2;
__REG32 PCLK_I2S    : 2;
__REG32 PCLK_MCI    : 2;
__REG32             : 2;
__REG32 PCLK_SYSCON : 2;
__REG32             : 2;
} __pclksel1_bits;

/* PLL control register */
typedef struct{
__REG32 PLLE        : 1;
__REG32 PLLC        : 1;
__REG32             :30;
} __pllcon_bits;

/* PLL config register */
typedef struct{
__REG32 MSEL        :15;
__REG32             : 1;
__REG32 NSEL        : 8;
__REG32             : 8;
} __pllcfg_bits;

/* PLL status register */
typedef struct{
__REG32 MSEL        :15;
__REG32             : 1;
__REG32 NSEL        : 8;
__REG32 PLLE        : 1;
__REG32 PLLC        : 1;
__REG32 PLOCK       : 1;
__REG32             : 5;
} __pllstat_bits;

/* PLL feed register */
typedef struct{
__REG32 FEED        : 8;
__REG32             :24;
} __pllfeed_bits;

/* Power control register */
typedef struct{
__REG32 IDL         : 1;
__REG32 PD          : 1;
__REG32 BODPDM      : 1;
__REG32 BOGD        : 1;
__REG32 BORD        : 1;
__REG32             : 2;
__REG32 PM2         : 1;
__REG32             :24;
}__pcon_bits;

/* Interrupt Wakeup Register */
typedef struct{
__REG32 EXTWAKE0    : 1;
__REG32 EXTWAKE1    : 1;
__REG32 EXTWAKE2    : 1;
__REG32 EXTWAKE3    : 1;
__REG32 ETHWAK      : 1;
__REG32 USBWAKE     : 1;
__REG32 CANWAKE     : 1;
__REG32 GPIOWAKE    : 1;
__REG32             : 6;
__REG32 BODWAKE     : 1;
__REG32 RTCWAKE     : 1;
__REG32             :16;
}__intwake_bits;

/* Power control for peripherals register */
typedef struct{
__REG32             : 1;
__REG32 PCTIM0      : 1;
__REG32 PCTIM1      : 1;
__REG32 PCUART0     : 1;
__REG32 PCUART1     : 1;
__REG32 PCPWM0      : 1;
__REG32 PCPWM1      : 1;
__REG32 PCI2C0      : 1;
__REG32 PCSPI       : 1;
__REG32 PCRTC       : 1;
__REG32 PCSSP1      : 1;
__REG32 PCEMC       : 1;
__REG32 PCAD        : 1;
__REG32 PCAN1       : 1;
__REG32 PCAN2       : 1;
__REG32             : 4;
__REG32 PCI2C1      : 1;
__REG32             : 1;
__REG32 PCSSP0      : 1;
__REG32 PCTIM2      : 1;
__REG32 PCTIM3      : 1;
__REG32 PCUART2     : 1;
__REG32 PCUART3     : 1;
__REG32 PCI2C2      : 1;
__REG32 PCI2S       : 1;
__REG32 PCSDC       : 1;
__REG32 PCGPDMA     : 1;
__REG32 PCENET      : 1;
__REG32 PCUSB       : 1;
} __pconp_bits;

/* Memory accelerator module control register */
typedef struct {
  __REG32 MODECTRL  : 2;
  __REG32           :30;
} __mamcr_bits;

/* Memory accelerator module timing register */
typedef struct {
  __REG32 CYCLES    : 3;
  __REG32           :29;
} __mamtim_bits;

/* EMC Control Register */
typedef struct {
  __REG32 E         : 1;
  __REG32 M         : 1;
  __REG32 L         : 1;
  __REG32           :29;
} __emc_ctrl_bits;

/* EMC Status Register */
typedef struct {
  __REG32 B         : 1;
  __REG32 S         : 1;
  __REG32 SA        : 1;
  __REG32           :29;
} __emc_st_bits;

/* EMC Configuration Register */
typedef struct {
  __REG32 ENDIAN    : 1;
  __REG32           :31;
} __emc_cfg_bits;

/* Static Memory Configuration Registers */
typedef struct {
  __REG32 MW        : 2;
  __REG32           : 1;
  __REG32 PM        : 1;
  __REG32           : 2;
  __REG32 PC        : 1;
  __REG32           : 1;
  __REG32 EW        : 1;
  __REG32           :10;
  __REG32 B         : 1;
  __REG32 P         : 1;
  __REG32           :11;
} __emc_s_config_bits;

/* Static Memory Write Enable Delay Registers */
typedef struct {
  __REG32 WAITWEN   : 4;
  __REG32           :28;
} __emc_s_wait_wen_bits;

/* Static Memory Output Enable Delay Registers */
typedef struct {
  __REG32 WAITOEN   : 4;
  __REG32           :28;
} __emc_s_wait_oen_bits;

/* Static Memory Read Delay Registers */
typedef struct {
  __REG32 WAITRD    : 5;
  __REG32           :27;
} __emc_s_wait_rd_bits;

/* Static Memory Page Mode Read Delay Registers */
typedef struct {
  __REG32 WAITPAGE  : 5;
  __REG32           :27;
} __emc_s_wait_pg_bits;

/* Static Memory Write Delay Registers */
typedef struct {
  __REG32 WAITWR    : 5;
  __REG32           :27;
} __emc_s_wait_wr_bits;

/* Static Memory Extended Wait Register */
typedef struct {
  __REG32 EXTENDEDWAIT  :10;
  __REG32               :22;
} __emc_s_ext_wait_bits;

/* Static Memory Turn Round Delay Registers */
typedef struct {
  __REG32 WAITTURN  : 4;
  __REG32           :28;
} __emc_s_wait_turn_bits;

/* VIC Interrupt registers */
typedef struct{
__REG32 WDT       : 1;
__REG32           : 1;
__REG32 ARMCORE0  : 1;
__REG32 ARMCORE1  : 1;
__REG32 TIMER0    : 1;
__REG32 TIMER1    : 1;
__REG32 UART0     : 1;
__REG32 UART1     : 1;
__REG32 PWM1      : 1;
__REG32 I2C0      : 1;
__REG32 SPI       : 1;
__REG32 SSP1      : 1;
__REG32 PLL       : 1;
__REG32 RTC       : 1;
__REG32 EINT0     : 1;
__REG32 EINT1     : 1;
__REG32 EINT2     : 1;
__REG32 EINT3     : 1;
__REG32 AD0       : 1;
__REG32 I2C1      : 1;
__REG32 BOD       : 1;
__REG32 ETHERNET  : 1;
__REG32 USB       : 1;
__REG32 CAN12     : 1;
__REG32 SDMMC     : 1;
__REG32 GPDMA     : 1;
__REG32 TIMER2    : 1;
__REG32 TIMER3    : 1;
__REG32 UART2     : 1;
__REG32 UART3     : 1;
__REG32 I2C2      : 1;
__REG32 I2S       : 1;
} __vicint_bits;

/* VIC Vector control registers */
typedef struct{
__REG32 PRIORITY : 4;
__REG32          :28;
} __vicvectpr_bits;

/* VIC Software Priority register */
typedef struct{
__REG32 SWPRIORITY:16;
__REG32           :16;
} __vicswprmask_bits;

/* VIC protection enable register */
typedef struct{
__REG32 PROTECT  : 1;
__REG32          :31;
} __vicprotection_bits;

/* Pin function select register 0 */
typedef struct{
__REG32 P0_0   : 2;
__REG32 P0_1   : 2;
__REG32 P0_2   : 2;
__REG32 P0_3   : 2;
__REG32 P0_4   : 2;
__REG32 P0_5   : 2;
__REG32 P0_6   : 2;
__REG32 P0_7   : 2;
__REG32 P0_8   : 2;
__REG32 P0_9   : 2;
__REG32 P0_10  : 2;
__REG32 P0_11  : 2;
__REG32 P0_12  : 2;
__REG32 P0_13  : 2;
__REG32 P0_14  : 2;
__REG32 P0_15  : 2;
} __pinsel0_bits;

/* Pin function select register 1 */
typedef struct{
__REG32 P0_16  : 2;
__REG32 P0_17  : 2;
__REG32 P0_18  : 2;
__REG32 P0_19  : 2;
__REG32 P0_20  : 2;
__REG32 P0_21  : 2;
__REG32 P0_22  : 2;
__REG32 P0_23  : 2;
__REG32 P0_24  : 2;
__REG32 P0_25  : 2;
__REG32 P0_26  : 2;
__REG32 P0_27  : 2;
__REG32 P0_28  : 2;
__REG32 P0_29  : 2;
__REG32 P0_30  : 2;
__REG32 P0_31  : 2;
} __pinsel1_bits;

/* Pin function select register 2 */
typedef struct{
__REG32 P1_0   : 2;
__REG32 P1_1   : 2;
__REG32 P1_2   : 2;
__REG32 P1_3   : 2;
__REG32 P1_4   : 2;
__REG32 P1_5   : 2;
__REG32 P1_6   : 2;
__REG32 P1_7   : 2;
__REG32 P1_8   : 2;
__REG32 P1_9   : 2;
__REG32 P1_10  : 2;
__REG32 P1_11  : 2;
__REG32 P1_12  : 2;
__REG32 P1_13  : 2;
__REG32 P1_14  : 2;
__REG32 P1_15  : 2;
} __pinsel2_bits;

/* Pin function select register 3 */
typedef struct{
__REG32 P1_16  : 2;
__REG32 P1_17  : 2;
__REG32 P1_18  : 2;
__REG32 P1_19  : 2;
__REG32 P1_20  : 2;
__REG32 P1_21  : 2;
__REG32 P1_22  : 2;
__REG32 P1_23  : 2;
__REG32 P1_24  : 2;
__REG32 P1_25  : 2;
__REG32 P1_26  : 2;
__REG32 P1_27  : 2;
__REG32 P1_28  : 2;
__REG32 P1_29  : 2;
__REG32 P1_30  : 2;
__REG32 P1_31  : 2;
} __pinsel3_bits;

/* Pin function select register 4 */
typedef struct{
__REG32 P2_0   : 2;
__REG32 P2_1   : 2;
__REG32 P2_2   : 2;
__REG32 P2_3   : 2;
__REG32 P2_4   : 2;
__REG32 P2_5   : 2;
__REG32 P2_6   : 2;
__REG32 P2_7   : 2;
__REG32 P2_8   : 2;
__REG32 P2_9   : 2;
__REG32 P2_10  : 2;
__REG32 P2_11  : 2;
__REG32 P2_12  : 2;
__REG32 P2_13  : 2;
__REG32 P2_14  : 2;
__REG32 P2_15  : 2;
} __pinsel4_bits;

/* Pin function select register 5 */
typedef struct{
__REG32 P2_16  : 2;
__REG32 P2_17  : 2;
__REG32 P2_18  : 2;
__REG32 P2_19  : 2;
__REG32 P2_20  : 2;
__REG32 P2_21  : 2;
__REG32 P2_22  : 2;
__REG32 P2_23  : 2;
__REG32 P2_24  : 2;
__REG32 P2_25  : 2;
__REG32 P2_26  : 2;
__REG32 P2_27  : 2;
__REG32 P2_28  : 2;
__REG32 P2_29  : 2;
__REG32 P2_30  : 2;
__REG32 P2_31  : 2;
} __pinsel5_bits;

/* Pin function select register 6 */
typedef struct{
__REG32 P3_0   : 2;
__REG32 P3_1   : 2;
__REG32 P3_2   : 2;
__REG32 P3_3   : 2;
__REG32 P3_4   : 2;
__REG32 P3_5   : 2;
__REG32 P3_6   : 2;
__REG32 P3_7   : 2;
__REG32 P3_8   : 2;
__REG32 P3_9   : 2;
__REG32 P3_10  : 2;
__REG32 P3_11  : 2;
__REG32 P3_12  : 2;
__REG32 P3_13  : 2;
__REG32 P3_14  : 2;
__REG32 P3_15  : 2;
} __pinsel6_bits;

/* Pin function select register 7 */
typedef struct{
__REG32 P3_16  : 2;
__REG32 P3_17  : 2;
__REG32 P3_18  : 2;
__REG32 P3_19  : 2;
__REG32 P3_20  : 2;
__REG32 P3_21  : 2;
__REG32 P3_22  : 2;
__REG32 P3_23  : 2;
__REG32 P3_24  : 2;
__REG32 P3_25  : 2;
__REG32 P3_26  : 2;
__REG32 P3_27  : 2;
__REG32 P3_28  : 2;
__REG32 P3_29  : 2;
__REG32 P3_30  : 2;
__REG32 P3_31  : 2;
} __pinsel7_bits;

/* Pin function select register 8 */
typedef struct{
__REG32 P4_0   : 2;
__REG32 P4_1   : 2;
__REG32 P4_2   : 2;
__REG32 P4_3   : 2;
__REG32 P4_4   : 2;
__REG32 P4_5   : 2;
__REG32 P4_6   : 2;
__REG32 P4_7   : 2;
__REG32 P4_8   : 2;
__REG32 P4_9   : 2;
__REG32 P4_10  : 2;
__REG32 P4_11  : 2;
__REG32 P4_12  : 2;
__REG32 P4_13  : 2;
__REG32 P4_14  : 2;
__REG32 P4_15  : 2;
} __pinsel8_bits;

/* Pin function select register 9 */
typedef struct{
__REG32 P4_16  : 2;
__REG32 P4_17  : 2;
__REG32 P4_18  : 2;
__REG32 P4_19  : 2;
__REG32 P4_20  : 2;
__REG32 P4_21  : 2;
__REG32 P4_22  : 2;
__REG32 P4_23  : 2;
__REG32 P4_24  : 2;
__REG32 P4_25  : 2;
__REG32 P4_26  : 2;
__REG32 P4_27  : 2;
__REG32 P4_28  : 2;
__REG32 P4_29  : 2;
__REG32 P4_30  : 2;
__REG32 P4_31  : 2;
} __pinsel9_bits;

/* Pin function select register 10 */
typedef struct{
__REG32             : 3;
__REG32 GPIO_TRACE  : 1;
__REG32             :28;
} __pinsel10_bits;

/* GPIO 0 Registers */
typedef struct {
__REG32 P0_0   : 1;
__REG32 P0_1   : 1;
__REG32 P0_2   : 1;
__REG32 P0_3   : 1;
__REG32 P0_4   : 1;
__REG32 P0_5   : 1;
__REG32 P0_6   : 1;
__REG32 P0_7   : 1;
__REG32 P0_8   : 1;
__REG32 P0_9   : 1;
__REG32 P0_10  : 1;
__REG32 P0_11  : 1;
__REG32 P0_12  : 1;
__REG32 P0_13  : 1;
__REG32 P0_14  : 1;
__REG32 P0_15  : 1;
__REG32 P0_16  : 1;
__REG32 P0_17  : 1;
__REG32 P0_18  : 1;
__REG32 P0_19  : 1;
__REG32 P0_20  : 1;
__REG32 P0_21  : 1;
__REG32 P0_22  : 1;
__REG32 P0_23  : 1;
__REG32 P0_24  : 1;
__REG32 P0_25  : 1;
__REG32 P0_26  : 1;
__REG32 P0_27  : 1;
__REG32 P0_28  : 1;
__REG32 P0_29  : 1;
__REG32 P0_30  : 1;
__REG32 P0_31  : 1;
} __gpio0_bits;

/* FGPIO 0 Registers*/
typedef union{
  struct {
    __REG32 P0_0   : 1;
    __REG32 P0_1   : 1;
    __REG32 P0_2   : 1;
    __REG32 P0_3   : 1;
    __REG32 P0_4   : 1;
    __REG32 P0_5   : 1;
    __REG32 P0_6   : 1;
    __REG32 P0_7   : 1;
    __REG32 P0_8   : 1;
    __REG32 P0_9   : 1;
    __REG32 P0_10  : 1;
    __REG32 P0_11  : 1;
    __REG32 P0_12  : 1;
    __REG32 P0_13  : 1;
    __REG32 P0_14  : 1;
    __REG32 P0_15  : 1;
    __REG32 P0_16  : 1;
    __REG32 P0_17  : 1;
    __REG32 P0_18  : 1;
    __REG32 P0_19  : 1;
    __REG32 P0_20  : 1;
    __REG32 P0_21  : 1;
    __REG32 P0_22  : 1;
    __REG32 P0_23  : 1;
    __REG32 P0_24  : 1;
    __REG32 P0_25  : 1;
    __REG32 P0_26  : 1;
    __REG32 P0_27  : 1;
    __REG32 P0_28  : 1;
    __REG32 P0_29  : 1;
    __REG32 P0_30  : 1;
    __REG32 P0_31  : 1;
  };

  struct
  {
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      struct{
        __REG8  P0_0   : 1;
        __REG8  P0_1   : 1;
        __REG8  P0_2   : 1;
        __REG8  P0_3   : 1;
        __REG8  P0_4   : 1;
        __REG8  P0_5   : 1;
        __REG8  P0_6   : 1;
        __REG8  P0_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      struct{
        __REG16 P0_0   : 1;
        __REG16 P0_1   : 1;
        __REG16 P0_2   : 1;
        __REG16 P0_3   : 1;
        __REG16 P0_4   : 1;
        __REG16 P0_5   : 1;
        __REG16 P0_6   : 1;
        __REG16 P0_7   : 1;
        __REG16 P0_8   : 1;
        __REG16 P0_9   : 1;
        __REG16 P0_10  : 1;
        __REG16 P0_11  : 1;
        __REG16 P0_12  : 1;
        __REG16 P0_13  : 1;
        __REG16 P0_14  : 1;
        __REG16 P0_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      struct{
        __REG16 P0_0   : 1;
        __REG16 P0_1   : 1;
        __REG16 P0_2   : 1;
        __REG16 P0_3   : 1;
        __REG16 P0_4   : 1;
        __REG16 P0_5   : 1;
        __REG16 P0_6   : 1;
        __REG16 P0_7   : 1;
        __REG16 P0_8   : 1;
        __REG16 P0_9   : 1;
        __REG16 P0_10  : 1;
        __REG16 P0_11  : 1;
        __REG16 P0_12  : 1;
        __REG16 P0_13  : 1;
        __REG16 P0_14  : 1;
        __REG16 P0_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio0_bits;

/* GPIO 1 Registers */
typedef struct {
__REG32 P1_0   : 1;
__REG32 P1_1   : 1;
__REG32 P1_2   : 1;
__REG32 P1_3   : 1;
__REG32 P1_4   : 1;
__REG32 P1_5   : 1;
__REG32 P1_6   : 1;
__REG32 P1_7   : 1;
__REG32 P1_8   : 1;
__REG32 P1_9   : 1;
__REG32 P1_10  : 1;
__REG32 P1_11  : 1;
__REG32 P1_12  : 1;
__REG32 P1_13  : 1;
__REG32 P1_14  : 1;
__REG32 P1_15  : 1;
__REG32 P1_16  : 1;
__REG32 P1_17  : 1;
__REG32 P1_18  : 1;
__REG32 P1_19  : 1;
__REG32 P1_20  : 1;
__REG32 P1_21  : 1;
__REG32 P1_22  : 1;
__REG32 P1_23  : 1;
__REG32 P1_24  : 1;
__REG32 P1_25  : 1;
__REG32 P1_26  : 1;
__REG32 P1_27  : 1;
__REG32 P1_28  : 1;
__REG32 P1_29  : 1;
__REG32 P1_30  : 1;
__REG32 P1_31  : 1;
} __gpio1_bits;

/* FGPIO 1 Registers*/
typedef union{
  struct {
    __REG32 P1_0   : 1;
    __REG32 P1_1   : 1;
    __REG32 P1_2   : 1;
    __REG32 P1_3   : 1;
    __REG32 P1_4   : 1;
    __REG32 P1_5   : 1;
    __REG32 P1_6   : 1;
    __REG32 P1_7   : 1;
    __REG32 P1_8   : 1;
    __REG32 P1_9   : 1;
    __REG32 P1_10  : 1;
    __REG32 P1_11  : 1;
    __REG32 P1_12  : 1;
    __REG32 P1_13  : 1;
    __REG32 P1_14  : 1;
    __REG32 P1_15  : 1;
    __REG32 P1_16  : 1;
    __REG32 P1_17  : 1;
    __REG32 P1_18  : 1;
    __REG32 P1_19  : 1;
    __REG32 P1_20  : 1;
    __REG32 P1_21  : 1;
    __REG32 P1_22  : 1;
    __REG32 P1_23  : 1;
    __REG32 P1_24  : 1;
    __REG32 P1_25  : 1;
    __REG32 P1_26  : 1;
    __REG32 P1_27  : 1;
    __REG32 P1_28  : 1;
    __REG32 P1_29  : 1;
    __REG32 P1_30  : 1;
    __REG32 P1_31  : 1;
  };

  struct
  {
    union
    {
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      struct{
        __REG8  P1_0   : 1;
        __REG8  P1_1   : 1;
        __REG8  P1_2   : 1;
        __REG8  P1_3   : 1;
        __REG8  P1_4   : 1;
        __REG8  P1_5   : 1;
        __REG8  P1_6   : 1;
        __REG8  P1_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      struct{
        __REG16 P1_0   : 1;
        __REG16 P1_1   : 1;
        __REG16 P1_2   : 1;
        __REG16 P1_3   : 1;
        __REG16 P1_4   : 1;
        __REG16 P1_5   : 1;
        __REG16 P1_6   : 1;
        __REG16 P1_7   : 1;
        __REG16 P1_8   : 1;
        __REG16 P1_9   : 1;
        __REG16 P1_10  : 1;
        __REG16 P1_11  : 1;
        __REG16 P1_12  : 1;
        __REG16 P1_13  : 1;
        __REG16 P1_14  : 1;
        __REG16 P1_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      struct{
        __REG16 P1_0   : 1;
        __REG16 P1_1   : 1;
        __REG16 P1_2   : 1;
        __REG16 P1_3   : 1;
        __REG16 P1_4   : 1;
        __REG16 P1_5   : 1;
        __REG16 P1_6   : 1;
        __REG16 P1_7   : 1;
        __REG16 P1_8   : 1;
        __REG16 P1_9   : 1;
        __REG16 P1_10  : 1;
        __REG16 P1_11  : 1;
        __REG16 P1_12  : 1;
        __REG16 P1_13  : 1;
        __REG16 P1_14  : 1;
        __REG16 P1_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio1_bits;

/* FGPIO 2 Registers*/
typedef union{
  struct {
    __REG32 P2_0   : 1;
    __REG32 P2_1   : 1;
    __REG32 P2_2   : 1;
    __REG32 P2_3   : 1;
    __REG32 P2_4   : 1;
    __REG32 P2_5   : 1;
    __REG32 P2_6   : 1;
    __REG32 P2_7   : 1;
    __REG32 P2_8   : 1;
    __REG32 P2_9   : 1;
    __REG32 P2_10  : 1;
    __REG32 P2_11  : 1;
    __REG32 P2_12  : 1;
    __REG32 P2_13  : 1;
    __REG32 P2_14  : 1;
    __REG32 P2_15  : 1;
    __REG32 P2_16  : 1;
    __REG32 P2_17  : 1;
    __REG32 P2_18  : 1;
    __REG32 P2_19  : 1;
    __REG32 P2_20  : 1;
    __REG32 P2_21  : 1;
    __REG32 P2_22  : 1;
    __REG32 P2_23  : 1;
    __REG32 P2_24  : 1;
    __REG32 P2_25  : 1;
    __REG32 P2_26  : 1;
    __REG32 P2_27  : 1;
    __REG32 P2_28  : 1;
    __REG32 P2_29  : 1;
    __REG32 P2_30  : 1;
    __REG32 P2_31  : 1;
  };

  struct
  {
    union
    {
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      struct{
        __REG8  P2_0   : 1;
        __REG8  P2_1   : 1;
        __REG8  P2_2   : 1;
        __REG8  P2_3   : 1;
        __REG8  P2_4   : 1;
        __REG8  P2_5   : 1;
        __REG8  P2_6   : 1;
        __REG8  P2_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      struct{
        __REG16 P2_0   : 1;
        __REG16 P2_1   : 1;
        __REG16 P2_2   : 1;
        __REG16 P2_3   : 1;
        __REG16 P2_4   : 1;
        __REG16 P2_5   : 1;
        __REG16 P2_6   : 1;
        __REG16 P2_7   : 1;
        __REG16 P2_8   : 1;
        __REG16 P2_9   : 1;
        __REG16 P2_10  : 1;
        __REG16 P2_11  : 1;
        __REG16 P2_12  : 1;
        __REG16 P2_13  : 1;
        __REG16 P2_14  : 1;
        __REG16 P2_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      struct{
        __REG16 P2_0   : 1;
        __REG16 P2_1   : 1;
        __REG16 P2_2   : 1;
        __REG16 P2_3   : 1;
        __REG16 P2_4   : 1;
        __REG16 P2_5   : 1;
        __REG16 P2_6   : 1;
        __REG16 P2_7   : 1;
        __REG16 P2_8   : 1;
        __REG16 P2_9   : 1;
        __REG16 P2_10  : 1;
        __REG16 P2_11  : 1;
        __REG16 P2_12  : 1;
        __REG16 P2_13  : 1;
        __REG16 P2_14  : 1;
        __REG16 P2_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio2_bits;

/* FGPIO 3 Registers*/
typedef union{
  struct {
    __REG32 P3_0   : 1;
    __REG32 P3_1   : 1;
    __REG32 P3_2   : 1;
    __REG32 P3_3   : 1;
    __REG32 P3_4   : 1;
    __REG32 P3_5   : 1;
    __REG32 P3_6   : 1;
    __REG32 P3_7   : 1;
    __REG32 P3_8   : 1;
    __REG32 P3_9   : 1;
    __REG32 P3_10  : 1;
    __REG32 P3_11  : 1;
    __REG32 P3_12  : 1;
    __REG32 P3_13  : 1;
    __REG32 P3_14  : 1;
    __REG32 P3_15  : 1;
    __REG32 P3_16  : 1;
    __REG32 P3_17  : 1;
    __REG32 P3_18  : 1;
    __REG32 P3_19  : 1;
    __REG32 P3_20  : 1;
    __REG32 P3_21  : 1;
    __REG32 P3_22  : 1;
    __REG32 P3_23  : 1;
    __REG32 P3_24  : 1;
    __REG32 P3_25  : 1;
    __REG32 P3_26  : 1;
    __REG32 P3_27  : 1;
    __REG32 P3_28  : 1;
    __REG32 P3_29  : 1;
    __REG32 P3_30  : 1;
    __REG32 P3_31  : 1;
  };

  struct
  {
    union
    {
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      struct{
        __REG8  P3_0   : 1;
        __REG8  P3_1   : 1;
        __REG8  P3_2   : 1;
        __REG8  P3_3   : 1;
        __REG8  P3_4   : 1;
        __REG8  P3_5   : 1;
        __REG8  P3_6   : 1;
        __REG8  P3_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      struct{
        __REG16 P3_0   : 1;
        __REG16 P3_1   : 1;
        __REG16 P3_2   : 1;
        __REG16 P3_3   : 1;
        __REG16 P3_4   : 1;
        __REG16 P3_5   : 1;
        __REG16 P3_6   : 1;
        __REG16 P3_7   : 1;
        __REG16 P3_8   : 1;
        __REG16 P3_9   : 1;
        __REG16 P3_10  : 1;
        __REG16 P3_11  : 1;
        __REG16 P3_12  : 1;
        __REG16 P3_13  : 1;
        __REG16 P3_14  : 1;
        __REG16 P3_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      struct{
        __REG16 P3_0   : 1;
        __REG16 P3_1   : 1;
        __REG16 P3_2   : 1;
        __REG16 P3_3   : 1;
        __REG16 P3_4   : 1;
        __REG16 P3_5   : 1;
        __REG16 P3_6   : 1;
        __REG16 P3_7   : 1;
        __REG16 P3_8   : 1;
        __REG16 P3_9   : 1;
        __REG16 P3_10  : 1;
        __REG16 P3_11  : 1;
        __REG16 P3_12  : 1;
        __REG16 P3_13  : 1;
        __REG16 P3_14  : 1;
        __REG16 P3_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio3_bits;

/* FGPIO 4 Registers*/
typedef union{
  struct {
    __REG32 P4_0   : 1;
    __REG32 P4_1   : 1;
    __REG32 P4_2   : 1;
    __REG32 P4_3   : 1;
    __REG32 P4_4   : 1;
    __REG32 P4_5   : 1;
    __REG32 P4_6   : 1;
    __REG32 P4_7   : 1;
    __REG32 P4_8   : 1;
    __REG32 P4_9   : 1;
    __REG32 P4_10  : 1;
    __REG32 P4_11  : 1;
    __REG32 P4_12  : 1;
    __REG32 P4_13  : 1;
    __REG32 P4_14  : 1;
    __REG32 P4_15  : 1;
    __REG32 P4_16  : 1;
    __REG32 P4_17  : 1;
    __REG32 P4_18  : 1;
    __REG32 P4_19  : 1;
    __REG32 P4_20  : 1;
    __REG32 P4_21  : 1;
    __REG32 P4_22  : 1;
    __REG32 P4_23  : 1;
    __REG32 P4_24  : 1;
    __REG32 P4_25  : 1;
    __REG32 P4_26  : 1;
    __REG32 P4_27  : 1;
    __REG32 P4_28  : 1;
    __REG32 P4_29  : 1;
    __REG32 P4_30  : 1;
    __REG32 P4_31  : 1;
  };

  struct
  {
    union
    {
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte0_bit;
      __REG8 __byte0;
    };
    union
    {
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte1_bit;
      __REG8 __byte1;
    };
    union
    {
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte2_bit;
      __REG8 __byte2;
    };
    union
    {
      struct{
        __REG8  P4_0   : 1;
        __REG8  P4_1   : 1;
        __REG8  P4_2   : 1;
        __REG8  P4_3   : 1;
        __REG8  P4_4   : 1;
        __REG8  P4_5   : 1;
        __REG8  P4_6   : 1;
        __REG8  P4_7   : 1;
      } __byte3_bit;
      __REG8 __byte3;
    };
  };

  struct
  {
    union
    {
      struct{
        __REG16 P4_0   : 1;
        __REG16 P4_1   : 1;
        __REG16 P4_2   : 1;
        __REG16 P4_3   : 1;
        __REG16 P4_4   : 1;
        __REG16 P4_5   : 1;
        __REG16 P4_6   : 1;
        __REG16 P4_7   : 1;
        __REG16 P4_8   : 1;
        __REG16 P4_9   : 1;
        __REG16 P4_10  : 1;
        __REG16 P4_11  : 1;
        __REG16 P4_12  : 1;
        __REG16 P4_13  : 1;
        __REG16 P4_14  : 1;
        __REG16 P4_15  : 1;
      } __shortl_bit;
      __REG16 __shortl;
    };
    union
    {
      struct{
        __REG16 P4_0   : 1;
        __REG16 P4_1   : 1;
        __REG16 P4_2   : 1;
        __REG16 P4_3   : 1;
        __REG16 P4_4   : 1;
        __REG16 P4_5   : 1;
        __REG16 P4_6   : 1;
        __REG16 P4_7   : 1;
        __REG16 P4_8   : 1;
        __REG16 P4_9   : 1;
        __REG16 P4_10  : 1;
        __REG16 P4_11  : 1;
        __REG16 P4_12  : 1;
        __REG16 P4_13  : 1;
        __REG16 P4_14  : 1;
        __REG16 P4_15  : 1;
      } __shortu_bit;
      __REG16 __shortu;
    };
  };
} __fgpio4_bits;

/* GPIO overall Interrupt Status register */
typedef struct{
__REG32 P0INT  : 1;
__REG32        : 1;
__REG32 P1INT  : 1;
__REG32        :29;
}__iointst_bits;

/* MAC Configuration Register 1 */
typedef struct{
__REG32 RE        : 1;
__REG32 PARF      : 1;
__REG32 RXFC      : 1;
__REG32 TXFC      : 1;
__REG32 LB        : 1;
__REG32           : 3;
__REG32 RSTTX     : 1;
__REG32 RSTMCSTX  : 1;
__REG32 RSTRX     : 1;
__REG32 RSTMCSRX  : 1;
__REG32           : 2;
__REG32 SRST      : 1;
__REG32 SOFTRST   : 1;
__REG32           :16;
}__mac1_bits;

/* MAC Configuration Register 2 */
typedef struct{
__REG32 FD        : 1;
__REG32 FLC       : 1;
__REG32 HFE       : 1;
__REG32 DLYCRC    : 1;
__REG32 CRCEN     : 1;
__REG32 PADCRCEN  : 1;
__REG32 VLANCRCEN : 1;
__REG32 ADPE      : 1;
__REG32 PPE       : 1;
__REG32 LPE       : 1;
__REG32           : 2;
__REG32 NOBACKOFF : 1;
__REG32 BP        : 1;
__REG32 ED        : 1;
__REG32           :17;
}__mac2_bits;

/* Back-to-Back Inter-Packet-Gap Register */
typedef struct{
__REG32 IPG       : 7;
__REG32           :25;
}__ipgt_bits;

/* Non Back-to-Back Inter-Packet-Gap Register */
typedef struct{
__REG32 IPGR2     : 7;
__REG32           : 1;
__REG32 IPGR1     : 7;
__REG32           :17;
}__ipgr_bits;

/*Collision Window / Retry Register */
typedef struct{
__REG32 RM        : 4;
__REG32           : 4;
__REG32 CW        : 6;
__REG32           :18;
}__clrt_bits;

/* Maximum Frame Register */
typedef struct{
__REG32 MAXF      :16;
__REG32           :16;
}__maxf_bits;

/* PHY Support Register */
typedef struct{
__REG32             : 8;
__REG32 SPEED       : 1;
__REG32             :23;
}__supp_bits;

/* Test Register */
typedef struct{
__REG32 SPQ         : 1;
__REG32 TP          : 1;
__REG32 TB          : 1;
__REG32             :29;
}__test_bits;

/* MII Mgmt Configuration Register */
typedef struct{
__REG32 SI          : 1;
__REG32 SP          : 1;
__REG32 CS          : 3;
__REG32             :10;
__REG32 RSTMIIMGMT  : 1;
__REG32             :16;
}__mcfg_bits;

/* MII Mgmt Command Register */
typedef struct{
__REG32 READ        : 1;
__REG32 SCAN        : 1;
__REG32             :30;
}__mcmd_bits;

/* MII Mgmt Address Register */
typedef struct{
__REG32 REGADDR     : 5;
__REG32             : 3;
__REG32 PHY_ADDR    : 5;
__REG32             :19;
}__madr_bits;

/* MII Mgmt Write Data Register */
typedef struct{
__REG32 WRITEDATA   :16;
__REG32             :16;
}__mwtd_bits;

/* MII Mgmt Read Data Register */
typedef struct{
__REG32 READDATA    :16;
__REG32             :16;
}__mrdd_bits;

/* MII Mgmt Indicators Register */
typedef struct{
__REG32 BUSY          : 1;
__REG32 SCANNING      : 1;
__REG32 NOT_VALID     : 1;
__REG32 MII_LINC_FAIL : 1;
__REG32               :28;
}__mind_bits;

/* Station Address 0 Register */
typedef struct{
__REG32 STATION_ADDR_2  : 8;
__REG32 STATION_ADDR_1  : 8;
__REG32                 :16;
}__sa0_bits;

/* Station Address 1 Register */
typedef struct{
__REG32 STATION_ADDR_4  : 8;
__REG32 STATION_ADDR_3  : 8;
__REG32                 :16;
}__sa1_bits;

/* Station Address 2 Register */
typedef struct{
__REG32 STATION_ADDR_6  : 8;
__REG32 STATION_ADDR_5  : 8;
__REG32                 :16;
}__sa2_bits;

/* Command Register */
typedef struct{
__REG32 RXENABLE        : 1;
__REG32 TXENABLE        : 1;
__REG32                 : 1;
__REG32 REGRESET        : 1;
__REG32 TXRESET         : 1;
__REG32 RXRESET         : 1;
__REG32 PASSRUNTFRAME   : 1;
__REG32 PASSRXFILTER    : 1;
__REG32 TXFLOWCONTROL   : 1;
__REG32 RMII            : 1;
__REG32 FULLDUPLEX      : 1;
__REG32                 :21;
}__command_bits;

/* Status Register */
typedef struct{
__REG32 RXSTATUS        : 1;
__REG32 TXSTATUS        : 1;
__REG32                 :30;
}__status_bits;

/* Receive Number of Descriptors Register */
typedef struct{
__REG32 RXDESCRIPTORNUMBER  :16;
__REG32                     :16;
}__rxdescrn_bits;

/* Receive Produce Index Register */
typedef struct{
__REG32 RXPRODUCDINDEX  :16;
__REG32                 :16;
}__rxprodind_bits;

/* Receive Consume Index Register */
typedef struct{
__REG32 RXCONSUMEINDEX  :16;
__REG32                 :16;
}__rxcomind_bits;

/* Transmit Number of Descriptors Register */
typedef struct{
__REG32 TXDESCRIPTORNUMBER  :16;
__REG32                     :16;
}__txdescrn_bits;

/* Transmit Produce Index Register */
typedef struct{
__REG32 TXPRODUCDINDEX  :16;
__REG32                 :16;
}__txprodind_bits;

/* Transmit Consume Index Register */
typedef struct{
__REG32 TXCONSUMEINDEX  :16;
__REG32                 :16;
}__txcomind_bits;

/* Transmit Status Vector 0 Register */
typedef struct{
__REG32 CCR_ERR         : 1;
__REG32 LCERR           : 1;
__REG32 LOOR            : 1;
__REG32 DONE            : 1;
__REG32 MULTICAST       : 1;
__REG32 BROADCAST       : 1;
__REG32 PD              : 1;
__REG32 ED              : 1;
__REG32 EC              : 1;
__REG32 LC              : 1;
__REG32 GIANT           : 1;
__REG32 UNDERRUN        : 1;
__REG32 TB              :16;
__REG32 CF              : 1;
__REG32 PAUSE           : 1;
__REG32 BACKPRESSURE    : 1;
__REG32 VLAN            : 1;
}__tsv0_bits;

/* Transmit Status Vector 1 Register */
typedef struct{
__REG32 TBC             :16;
__REG32 TCC             : 4;
__REG32                 :12;
}__tsv1_bits;

/* Receive Status Vector Register */
typedef struct{
__REG32 RBC             :16;
__REG32 PPI             : 1;
__REG32 RXDVEPS         : 1;
__REG32 CEPS            : 1;
__REG32 RCV             : 1;
__REG32 CRC_ERR         : 1;
__REG32 LCE             : 1;
__REG32 LOOR            : 1;
__REG32 R_OK            : 1;
__REG32 MULTICAST       : 1;
__REG32 BROADCAST       : 1;
__REG32 DN              : 1;
__REG32 CF              : 1;
__REG32 PAUSE           : 1;
__REG32 UO              : 1;
__REG32 VLAN            : 1;
__REG32                 : 1;
}__rsv_bits;

/* Flow Control Counter Register */
typedef struct{
__REG32 MC              :16;
__REG32 PT              :16;
}__fwctrlcnt_bits;

/* Flow Control Status Register */
typedef struct{
__REG32 MCC             :16;
__REG32                 :16;
}__fwctrlstat_bits;

/* Receive Filter Control Register */
typedef struct{
__REG32 AUE             : 1;
__REG32 ABE             : 1;
__REG32 AME             : 1;
__REG32 AUHE            : 1;
__REG32 AMHE            : 1;
__REG32 APE             : 1;
__REG32                 : 6;
__REG32 MPEWOL          : 1;
__REG32 RXFEWOL         : 1;
__REG32                 :18;
}__rxflctrl_bits;

/* Receive Filter WoL Status Register */
typedef struct{
__REG32 AUWOL           : 1;
__REG32 ABWOL           : 1;
__REG32 AMWOL           : 1;
__REG32 AUHWOL          : 1;
__REG32 AMHWOL          : 1;
__REG32 APWOL           : 1;
__REG32                 : 1;
__REG32 RXFWOL          : 1;
__REG32 MPWOL           : 1;
__REG32                 :23;
}__rxflwolstat_bits;

/* Receive Filter WoL Clear Register */
typedef struct{
__REG32 AUWOLC          : 1;
__REG32 ABWOLC          : 1;
__REG32 AMWOLC          : 1;
__REG32 AUHWOLC         : 1;
__REG32 AMHWOLC         : 1;
__REG32 APWOLC          : 1;
__REG32                 : 1;
__REG32 RXFWOLC         : 1;
__REG32 MPWOLC          : 1;
__REG32                 :23;
}__rxflwolclr_bits;

/* Interrupt Status Register */
typedef struct{
__REG32 RXOVERRUNINT    : 1;
__REG32 RXERRORINT      : 1;
__REG32 RXFINISHEDINT   : 1;
__REG32 RXDONEINT       : 1;
__REG32 TXUNDERRUNINT   : 1;
__REG32 TXERRORINT      : 1;
__REG32 TXFINISHEDINT   : 1;
__REG32 TXDONEINT       : 1;
__REG32                 : 4;
__REG32 SOFTINT         : 1;
__REG32 WAKEUPINT       : 1;
__REG32                 :18;
}__intstat_bits;

/* Interrupt Enable Register */
typedef struct{
__REG32 RXOVERRUNINTEN  : 1;
__REG32 RXERRORINTEN    : 1;
__REG32 RXFINISHEDINTEN : 1;
__REG32 RXDONEINTEN     : 1;
__REG32 TXUNDERRUNINTEN : 1;
__REG32 TXERRORINTEN    : 1;
__REG32 TXFINISHEDINTEN : 1;
__REG32 TXDONEINTEN     : 1;
__REG32                 : 4;
__REG32 SOFTINTEN       : 1;
__REG32 WAKEUPINTEN     : 1;
__REG32                 :18;
}__intena_bits;

/* Interrupt Clear Register */
typedef struct{
__REG32 RXOVERRUNINTCLR : 1;
__REG32 RXERRORINTCLR   : 1;
__REG32 RXFINISHEDINTCLR: 1;
__REG32 RXDONEINTCLR    : 1;
__REG32 TXUNDERRUNINTCLR: 1;
__REG32 TXERRORINTCLR   : 1;
__REG32 TXFINISHEDINTCLR: 1;
__REG32 TXDONEINTCLR    : 1;
__REG32                 : 4;
__REG32 SOFTINTCLR      : 1;
__REG32 WAKEUPINTCLR    : 1;
__REG32                 :18;
}__intclr_bits;

/* Interrupt Set Register */
typedef struct{
__REG32 RXOVERRUNINTSET : 1;
__REG32 RXERRORINTSET   : 1;
__REG32 RXFINISHEDINTSET: 1;
__REG32 RXDONEINTSET    : 1;
__REG32 TXUNDERRUNINTSET: 1;
__REG32 TXERRORINTSET   : 1;
__REG32 TXFINISHEDINTSET: 1;
__REG32 TXDONEINTSET    : 1;
__REG32                 : 4;
__REG32 SOFTINTSET      : 1;
__REG32 WAKEUPINTSET    : 1;
__REG32                 :18;
}__intset_bits;

/* Power Down Register */
typedef struct{
__REG32                 :31;
__REG32 POWERDOWN       : 1;
}__pwrdn_bits;


/* USB - Device Interrupt Status Register */
typedef struct {
  __REG32 PORTSEL           : 2;
  __REG32                   :30;
} __usbportsel_bits;

/* USB Clock Control register (USBClkCtrl - 0xFFE0 CFF4) 
   USB Clock Status register (USBClkSt - 0xFFE0 CFF8) */
typedef struct{
__REG32                 : 1;
__REG32 DEV_CLK_EN      : 1;
__REG32                 : 1;
__REG32 PORTSEL_CLK_EN  : 1;
__REG32 AHB_CLK_EN      : 1;
__REG32                 :27;
} __usbclkctrl_bits;

/* USB - Device Interrupt Status Register */
typedef struct {
  __REG32 USB_INT_REQ_LP    : 1;
  __REG32 USB_INT_REQ_HP    : 1;
  __REG32 USB_INT_REQ_DMA   : 1;
  __REG32                   : 5;
  __REG32 USB_NEED_CLOCK    : 1;
  __REG32                   :22;
  __REG32 EN_USB_INTS       : 1;
} __usbints_bits;

/* USB - Device Interrupt Status Register */
/* USB - Device Interrupt Enable Register */
/* USB - Device Interrupt Clear Register */
/* USB - Device Interrupt Set Register */
typedef struct {
  __REG32 FRAME             : 1;
  __REG32 EP_FAST           : 1;
  __REG32 EP_SLOW           : 1;
  __REG32 DEV_STAT          : 1;
  __REG32 CCEMTY            : 1;
  __REG32 CDFULL            : 1;
  __REG32 RXENDPKT          : 1;
  __REG32 TXENDPKT          : 1;
  __REG32 EP_RLZED          : 1;
  __REG32 ERR_INT           : 1;
  __REG32                   :22;
} __usbdevintst_bits;

/* USB - Device Interrupt Priority Register */
typedef struct {
  __REG8  FRAME             : 1;
  __REG8  EP_FAST           : 1;
  __REG8                    : 6;
} __usbdevintpri_bits;

/* USB - Endpoint Interrupt Status Register */
/* USB - Endpoint Interrupt Enable Register */
/* USB - Endpoint Interrupt Clear Register */
/* USB - Endpoint Interrupt Set Register */
/* USB - Endpoint Interrupt Priority Register */
typedef struct {
  __REG32 EP_0RX            : 1;
  __REG32 EP_0TX            : 1;
  __REG32 EP_1RX            : 1;
  __REG32 EP_1TX            : 1;
  __REG32 EP_2RX            : 1;
  __REG32 EP_2TX            : 1;
  __REG32 EP_3RX            : 1;
  __REG32 EP_3TX            : 1;
  __REG32 EP_4RX            : 1;
  __REG32 EP_4TX            : 1;
  __REG32 EP_5RX            : 1;
  __REG32 EP_5TX            : 1;
  __REG32 EP_6RX            : 1;
  __REG32 EP_6TX            : 1;
  __REG32 EP_7RX            : 1;
  __REG32 EP_7TX            : 1;
  __REG32 EP_8RX            : 1;
  __REG32 EP_8TX            : 1;
  __REG32 EP_9RX            : 1;
  __REG32 EP_9TX            : 1;
  __REG32 EP_10RX           : 1;
  __REG32 EP_10TX           : 1;
  __REG32 EP_11RX           : 1;
  __REG32 EP_11TX           : 1;
  __REG32 EP_12RX           : 1;
  __REG32 EP_12TX           : 1;
  __REG32 EP_13RX           : 1;
  __REG32 EP_13TX           : 1;
  __REG32 EP_14RX           : 1;
  __REG32 EP_14TX           : 1;
  __REG32 EP_15RX           : 1;
  __REG32 EP_15TX           : 1;
} __usbepintst_bits;

/* USB - Realize Enpoint Register */
/* USB - DMA Request Status Register */
/* USB - DMA Request Clear Register */
/* USB - DMA Request Set Regiser */
/* USB - EP DMA Status Register */
/* USB - EP DMA Enable Register */
/* USB - EP DMA Disable Register */
/* USB - New DD Request Interrupt Status Register */
/* USB - New DD Request Interrupt Clear Register */
/* USB - New DD Request Interrupt Set Register */
/* USB - End Of Transfer Interrupt Status Register */
/* USB - End Of Transfer Interrupt Clear Register */
/* USB - End Of Transfer Interrupt Set Register */
/* USB - System Error Interrupt Status Register */
/* USB - System Error Interrupt Clear Register */
/* USB - System Error Interrupt Set Register */
typedef struct {
  __REG32 EP0               : 1;
  __REG32 EP1               : 1;
  __REG32 EP2               : 1;
  __REG32 EP3               : 1;
  __REG32 EP4               : 1;
  __REG32 EP5               : 1;
  __REG32 EP6               : 1;
  __REG32 EP7               : 1;
  __REG32 EP8               : 1;
  __REG32 EP9               : 1;
  __REG32 EP10              : 1;
  __REG32 EP11              : 1;
  __REG32 EP12              : 1;
  __REG32 EP13              : 1;
  __REG32 EP14              : 1;
  __REG32 EP15              : 1;
  __REG32 EP16              : 1;
  __REG32 EP17              : 1;
  __REG32 EP18              : 1;
  __REG32 EP19              : 1;
  __REG32 EP20              : 1;
  __REG32 EP21              : 1;
  __REG32 EP22              : 1;
  __REG32 EP23              : 1;
  __REG32 EP24              : 1;
  __REG32 EP25              : 1;
  __REG32 EP26              : 1;
  __REG32 EP27              : 1;
  __REG32 EP28              : 1;
  __REG32 EP29              : 1;
  __REG32 EP30              : 1;
  __REG32 EP31              : 1;
} __usbreep_bits;

/* USB - Endpoint Index Register */
typedef struct {
  __REG32 PHY_ENDP          : 5;
  __REG32                   :27;
} __usbepin_bits;

/* USB - MaxPacketSize Register */
typedef struct {
  __REG32 MPS               :10;
  __REG32                   :22;
} __usbmaxpsize_bits;

/* USB - Receive Packet Length Register */
typedef struct {
  __REG32 PKT_LNGTH         :10;
  __REG32 DV                : 1;
  __REG32 PKT_RDY           : 1;
  __REG32                   :20;
} __usbrxplen_bits;

/* USB - Transmit Packet Length Register */
typedef struct {
  __REG32 PKT_LNGHT         :10;
  __REG32                   :22;
} __usbtxplen_bits;

/* USB - Control Register */
typedef struct {
  __REG32 RD_EN             : 1;
  __REG32 WR_EN             : 1;
  __REG32 LOG_ENDPOINT      : 4;
  __REG32                   :26;
} __usbctrl_bits;

/* USB - Command Code Register */
typedef struct {
  __REG32                   : 8;
  __REG32 CMD_PHASE         : 8;
  __REG32 CMD_CODE          : 8;
  __REG32                   : 8;
} __usbcmdcode_bits;

/* USB - Command Data Register */
typedef struct {
  __REG32 CMD_DATA          : 8;
  __REG32                   :24;
} __usbcmddata_bits;

/* USB - DMA Interrupt Status Register */
/* USB - DMA Interrupt Enable Register */
typedef struct {
  __REG32 EOT       : 1;
  __REG32 NDDR      : 1;
  __REG32 ERR       : 1;
  __REG32           :29;
} __usbdmaintst_bits;

/* CAN acceptance filter mode register */
typedef struct {
  __REG32 ACCOFF          :1;
  __REG32 ACCBP           :1;
  __REG32 EFCAN           :1;
  __REG32                 :29;
} __afmr_bits;

/* Global FullCANInterrupt Enable register */
typedef struct {
  __REG32 FCANIE          :1;
  __REG32                 :31;
} __fcanie_bits;

/* FullCAN Interrupt and Capture registers 0 */
typedef struct {
  __REG32 INTPND0         :1;
  __REG32 INTPND1         :1;
  __REG32 INTPND2         :1;
  __REG32 INTPND3         :1;
  __REG32 INTPND4         :1;
  __REG32 INTPND5         :1;
  __REG32 INTPND6         :1;
  __REG32 INTPND7         :1;
  __REG32 INTPND8         :1;
  __REG32 INTPND9         :1;
  __REG32 INTPND10        :1;
  __REG32 INTPND11        :1;
  __REG32 INTPND12        :1;
  __REG32 INTPND13        :1;
  __REG32 INTPND14        :1;
  __REG32 INTPND15        :1;
  __REG32 INTPND16        :1;
  __REG32 INTPND17        :1;
  __REG32 INTPND18        :1;
  __REG32 INTPND19        :1;
  __REG32 INTPND20        :1;
  __REG32 INTPND21        :1;
  __REG32 INTPND22        :1;
  __REG32 INTPND23        :1;
  __REG32 INTPND24        :1;
  __REG32 INTPND25        :1;
  __REG32 INTPND26        :1;
  __REG32 INTPND27        :1;
  __REG32 INTPND28        :1;
  __REG32 INTPND29        :1;
  __REG32 INTPND30        :1;
  __REG32 INTPND31        :1;
} __fcanic0_bits;

/* FullCAN Interrupt and Capture registers 1 */
typedef struct {
  __REG32 INTPND32        :1;
  __REG32 INTPND33        :1;
  __REG32 INTPND34        :1;
  __REG32 INTPND35        :1;
  __REG32 INTPND36        :1;
  __REG32 INTPND37        :1;
  __REG32 INTPND38        :1;
  __REG32 INTPND39        :1;
  __REG32 INTPND40        :1;
  __REG32 INTPND41        :1;
  __REG32 INTPND42        :1;
  __REG32 INTPND43        :1;
  __REG32 INTPND44        :1;
  __REG32 INTPND45        :1;
  __REG32 INTPND46        :1;
  __REG32 INTPND47        :1;
  __REG32 INTPND48        :1;
  __REG32 INTPND49        :1;
  __REG32 INTPND50        :1;
  __REG32 INTPND51        :1;
  __REG32 INTPND52        :1;
  __REG32 INTPND53        :1;
  __REG32 INTPND54        :1;
  __REG32 INTPND55        :1;
  __REG32 INTPND56        :1;
  __REG32 INTPND57        :1;
  __REG32 INTPND58        :1;
  __REG32 INTPND59        :1;
  __REG32 INTPND60        :1;
  __REG32 INTPND61        :1;
  __REG32 INTPND62        :1;
  __REG32 INTPND63        :1;
} __fcanic1_bits;

/* CAN central transmit status register */
typedef struct {
  __REG32 TS1             : 1;
  __REG32 TS2             : 1;
  __REG32                 : 6;
  __REG32 TBS1            : 1;
  __REG32 TBS2            : 1;
  __REG32                 : 6;
  __REG32 TCS1            : 1;
  __REG32 TCS2            : 1;
  __REG32                 :14;
} __cantxsr_bits;

/* CAN central receive status register */
typedef struct {
  __REG32 RS1             : 1;
  __REG32 RS2             : 1;
  __REG32                 : 6;
  __REG32 RBS1            : 1;
  __REG32 RBS2            : 1;
  __REG32                 : 6;
  __REG32 DOS1            : 1;
  __REG32 DOS2            : 1;
  __REG32                 :14;
} __canrxsr_bits;

/* CAN miscellaneous status register */
typedef struct {
  __REG32 ES1             : 1;
  __REG32 ES2             : 1;
  __REG32                 : 6;
  __REG32 BS1             : 1;
  __REG32 BS2             : 1;
  __REG32                 :22;
} __canmsr_bits;

/* CAN mode register */
typedef struct {
  __REG32 RM              :1;
  __REG32 LOM             :1;
  __REG32 STM             :1;
  __REG32 TPM             :1;
  __REG32 SM              :1;
  __REG32 RPM             :1;
  __REG32                 :1;
  __REG32 TM              :1;
  __REG32                 :24;
} __canmod_bits;

/* CAN command register */
typedef struct {
  __REG32 TR              :1;
  __REG32 AT              :1;
  __REG32 RRB             :1;
  __REG32 CDO             :1;
  __REG32 SRR             :1;
  __REG32 STB1            :1;
  __REG32 STB2            :1;
  __REG32 STB3            :1;
  __REG32                 :24;
} __cancmr_bits;

/* CAN global status register */
typedef struct {
  __REG32 RBS              :1;
  __REG32 DOS              :1;
  __REG32 TBS              :1;
  __REG32 TCS              :1;
  __REG32 RS               :1;
  __REG32 TS               :1;
  __REG32 ES               :1;
  __REG32 BS               :1;
  __REG32                  :8;
  __REG32 RXERR            :8;
  __REG32 TXERR            :8;
} __cangsr_bits;

/* CAN interrupt capture register */
typedef struct {
  __REG32 RI               :1;
  __REG32 TI1              :1;
  __REG32 EI               :1;
  __REG32 DOI              :1;
  __REG32 WUI              :1;
  __REG32 EPI              :1;
  __REG32 ALI              :1;
  __REG32 BEI              :1;
  __REG32 IDI              :1;
  __REG32 TI2              :1;
  __REG32 TI3              :1;
  __REG32                  :5;
  __REG32 ERRBIT           :5;
  __REG32 ERRDIR           :1;
  __REG32 ERRC             :2;
  __REG32 ALCBIT           :8;
} __canicr_bits;

/* CAN interrupt enable register */
typedef struct {
  __REG32 RIE               :1;
  __REG32 TIE1              :1;
  __REG32 EIE               :1;
  __REG32 DOIE              :1;
  __REG32 WUIE              :1;
  __REG32 EPIE              :1;
  __REG32 ALIE              :1;
  __REG32 BEIE              :1;
  __REG32 IDIE              :1;
  __REG32 TIE2              :1;
  __REG32 TIE3              :1;
  __REG32                   :21;
} __canier_bits;

/* CAN bus timing register */
typedef struct {
  __REG32 BRP                :10;
  __REG32                    :4;
  __REG32 SJW                :2;
  __REG32 TSEG1              :4;
  __REG32 TSEG2              :3;
  __REG32 SAM                :1;
  __REG32                    :8;
} __canbtr_bits;

/* CAN error warning limit register */
typedef struct {
  __REG32 EWL                :8;
  __REG32                    :24;
} __canewl_bits;

/* CAN status register */
typedef struct {
  __REG32 RBS                :1;
  __REG32 DOS                :1;
  __REG32 TBS1               :1;
  __REG32 TCS1               :1;
  __REG32 RS                 :1;
  __REG32 TS1                :1;
  __REG32 ES                 :1;
  __REG32 BS                 :1;
  __REG32 /*RBS*/            :1;
  __REG32 /*DOS*/            :1;
  __REG32 TBS2               :1;
  __REG32 TCS2               :1;
  __REG32 /*RS*/             :1;
  __REG32 TS2                :1;
  __REG32 /*ES*/             :1;
  __REG32 /*BS*/             :1;
  __REG32 /*RBS*/            :1;
  __REG32 /*DOS*/            :1;
  __REG32 TBS3               :1;
  __REG32 TCS3               :1;
  __REG32 /*RS*/             :1;
  __REG32 TS3                :1;
  __REG32 /*ES*/             :1;
  __REG32 /*BS*/             :1;
  __REG32                    :8;
} __cansr_bits;

/* CAN rx frame status register */
typedef struct {
  __REG32 IDINDEX            :10;
  __REG32 BP                 :1;
  __REG32                    :5;
  __REG32 DLC                :4;
  __REG32                    :10;
  __REG32 RTR                :1;
  __REG32 FF                 :1;
} __canrfs_bits;

/* CAN rx identifier register */
typedef union {
  //CANxRID
  struct {
   __REG32 ID10_0             :11;
   __REG32                    :21;
  };
  //CANxRID
  struct {
   __REG32 ID29_18            :11;
   __REG32                    :21;
  };
  //CANxRID
  struct {
   __REG32 ID29_0             :29;
   __REG32                    :3;
  };
} __canrid_bits;

/* CAN rx data register A */
typedef struct {
  __REG32 DATA1               :8;
  __REG32 DATA2               :8;
  __REG32 DATA3               :8;
  __REG32 DATA4               :8;
} __canrda_bits;

/* CAN rx data register B */
typedef struct {
  __REG32 DATA5               :8;
  __REG32 DATA6               :8;
  __REG32 DATA7               :8;
  __REG32 DATA8               :8;
} __canrdb_bits;

/* CAN tx frame information register */
typedef struct {
  __REG32 PRIO              :8;
  __REG32                   :8;
  __REG32 DLC               :4;
  __REG32                   :10;
  __REG32 RTR               :1;
  __REG32 FF                :1;
} __cantfi_bits;

/* CAN tx identifier register */
typedef union {
  //CANxTIDy
  struct {
   __REG32 ID10_0             :11;
   __REG32                    :21;
  };
  //CANxTIDy
  struct {
   __REG32 ID29_18            :11;
   __REG32                    :21;
  };
  //CANxTIDy
  struct {
   __REG32 ID29_0             :29;
   __REG32                    :3;
  };
} __cantid_bits;

/* CAN tx data register A */
typedef struct {
  __REG32 DATA1               :8;
  __REG32 DATA2               :8;
  __REG32 DATA3               :8;
  __REG32 DATA4               :8;
} __cantda_bits;

/* CAN tx data register B */
typedef struct {
  __REG32 DATA5               :8;
  __REG32 DATA6               :8;
  __REG32 DATA7               :8;
  __REG32 DATA8               :8;
} __cantdb_bits;

/* UART interrupt enable register */
typedef struct{
__REG32 RDAIE     : 1;
__REG32 THREIE    : 1;
__REG32 RXLSIE    : 1;
__REG32           : 5;
__REG32 ABTOINTEN : 1;
__REG32 ABEOINTEN : 1;
__REG32           :22;
} __uartier0_bits;

/* UART1 interrupt enable register */
typedef struct{
__REG32 RDAIE     : 1;
__REG32 THREIE    : 1;
__REG32 RXLSIE    : 1;
__REG32 RXMSIE    : 1;
__REG32           : 3;
__REG32 CTSIE     : 1;
__REG32 ABTOINTEN : 1;
__REG32 ABEOINTEN : 1;
__REG32           :22;
} __uartier1_bits;

/* UART Transmit Enable Register */
typedef struct{
__REG8        : 7;
__REG8  TXEN  : 1;
} __uartter_bits;

/* UART line status register */
typedef struct{
__REG8  DR    : 1;
__REG8  OE    : 1;
__REG8  PE    : 1;
__REG8  FE    : 1;
__REG8  BI    : 1;
__REG8  THRE  : 1;
__REG8  TEMT  : 1;
__REG8  RXFE  : 1;
} __uartlsr_bits;

/* UART line control register */
typedef struct{
__REG8  WLS   : 2;
__REG8  SBS   : 1;
__REG8  PE    : 1;
__REG8  PS    : 2;
__REG8  BC    : 1;
__REG8  DLAB  : 1;
} __uartlcr_bits;

/* UART interrupt identification register and fifo control register */
typedef union {
  //UxIIR
  struct {
__REG32 IP     : 1;
__REG32 IID    : 3;
__REG32        : 2;
__REG32 IIRFE  : 2;
__REG32 ABEOINT: 1;
__REG32 ABTOINT: 1;
__REG32        :22;
  };
  //UxFCR
  struct {
__REG32 FCRFE  : 1;
__REG32 RFR    : 1;
__REG32 TFR    : 1;
__REG32        : 3;
__REG32 RTLS   : 2;
__REG32        :24;
  };
} __uartfcriir_bits;

/* UART modem control register */
typedef struct{
__REG8  DTR   : 1;
__REG8  RTS   : 1;
__REG8        : 2;
__REG8  LMS   : 1;
__REG8        : 1;
__REG8  RTSEN : 1;
__REG8  CTSEN : 1;
} __uartmcr_bits;

/* UART modem status register */
typedef union{
  //UxMSR
  struct {
__REG8  DCTS  : 1;
__REG8  DDSR  : 1;
__REG8  TERI  : 1;
__REG8  DDCD  : 1;
__REG8  CTS   : 1;
__REG8  DSR   : 1;
__REG8  RI    : 1;
__REG8  DCD   : 1;
  };
  //UxMSR
  struct {
__REG8  MSR0  : 1;
__REG8  MSR1  : 1;
__REG8  MSR2  : 1;
__REG8  MSR3  : 1;
__REG8  MSR4  : 1;
__REG8  MSR5  : 1;
__REG8  MSR6  : 1;
__REG8  MSR7  : 1;
  };
} __uartmsr_bits;

/* UART Auto-baud Control Register */
typedef struct{
__REG32 START        : 1;
__REG32 MODE         : 1;
__REG32 AUTORESTART  : 1;
__REG32              : 5;
__REG32 ABEOINTCLR   : 1;
__REG32 ABTOINTCLR   : 1;
__REG32              :22;
} __uartacr_bits;

/* IrDA Control Register for UART3 Only */
typedef struct{
__REG32 IRDAEN       : 1;
__REG32 IRDAINV      : 1;
__REG32 FIXPULSEEN   : 1;
__REG32 PULSEDIV     : 3;
__REG32              :26;
} __uarticr_bits;

/* UART Fractional Divider Register */
typedef struct{
__REG32 DIVADDVAL  : 4;
__REG32 MULVAL     : 4;
__REG32            :24;
} __uartfdr_bits;

/* SPI control register */
typedef struct{
__REG32           : 2;
__REG32 BITENABLE : 1;
__REG32 CPHA      : 1;
__REG32 CPOL      : 1;
__REG32 MSTR      : 1;
__REG32 LSBF      : 1;
__REG32 SPIE      : 1;
__REG32 BITS      : 4;
__REG32           :20;
} __spcr_bits;

/* SPI status register */
typedef struct{
__REG32         : 3;
__REG32 ABRT    : 1;
__REG32 MODF    : 1;
__REG32 ROVR    : 1;
__REG32 WCOL    : 1;
__REG32 SPIF    : 1;
__REG32         :24;
} __spsr_bits;

/* SPI clock counter register */
typedef struct{
__REG32 COUNTER  : 8;
__REG32          :24;
} __spccr_bits;

/* SPI interrupt register */
typedef struct{
__REG32 SPIINT  : 1;
__REG32         :31;
} __spint_bits;

/* SPI Test control register */
typedef struct{
__REG8          : 1;
__REG8  TEST    : 7;
} __sptcr_bits;

/* SPI Test Status Register */
typedef struct{
__REG8          : 3;
__REG8  ABRT    : 1;
__REG8  MODF    : 1;
__REG8  ROVR    : 1;
__REG8  WCOL    : 1;
__REG8  SPIF    : 1;
} __sptsr_bits;

/* SSP Control Register 0 */
typedef struct{
__REG32 DSS  : 4;
__REG32 FRF  : 2;
__REG32 SPO  : 1;
__REG32 SPH  : 1;
__REG32 SCR  : 8;
__REG32      :16;
} __sspcr0_bits;

/* SSP Control Register 1 */
typedef struct{
__REG32 LBM  : 1;
__REG32 SSE  : 1;
__REG32 MS   : 1;
__REG32 SOD  : 1;
__REG32      :28;
} __sspcr1_bits;

/* SSP Data Register */
typedef struct{
__REG32 DATA :16;
__REG32      :16;
} __sspdr_bits;

/* SSP Status Register */
typedef struct{
__REG32 TFE  : 1;
__REG32 TNF  : 1;
__REG32 RNE  : 1;
__REG32 RFF  : 1;
__REG32 BSY  : 1;
__REG32      :27;
} __sspsr_bits;

/* SSP Clock Prescale Register */
typedef struct{
__REG32 CPSDVSR : 8;
__REG32         :24;
} __sspcpsr_bits;

/* SSP Interrupt Mask Set/Clear Register */
typedef struct{
__REG32 RORIM  : 1;
__REG32 RTIM   : 1;
__REG32 RXIM   : 1;
__REG32 TXIM   : 1;
__REG32        :28;
} __sspimsc_bits;

/* SSP Raw Interrupt Status Register */
typedef struct{
__REG32 RORRIS  : 1;
__REG32 RTRIS   : 1;
__REG32 RXRIS   : 1;
__REG32 TXRIS   : 1;
__REG32         :28;
} __sspris_bits;

/* SSP Masked Interrupt Status Register */
typedef struct{
__REG32 RORMIS  : 1;
__REG32 RTMIS   : 1;
__REG32 RXMIS   : 1;
__REG32 TXMIS   : 1;
__REG32         :28;
} __sspmis_bits;

/* SSP Interrupt Clear Register */
typedef struct{
__REG32 RORIC  : 1;
__REG32 RTIC   : 1;
__REG32        :30;
} __sspicr_bits;

/* SSP DMA Control Register */
typedef struct{
__REG32 RXDMAE : 1;
__REG32 TXDMAE : 1;
__REG32        :30;
} __sspdmacr_bits;

/* SD/MMC Power control register */
typedef struct{
__REG32 CTRL       : 2;
__REG32            : 4;
__REG32 OPENDRAIN  : 1;
__REG32 ROD        : 1;
__REG32            :24;
} __mcipower_bits;

/* SD/MMC Clock control register */
typedef struct{
__REG32 CLKDIV   : 8;
__REG32 ENABLE   : 1;
__REG32 PWRSAVE  : 1;
__REG32 BYPASS   : 1;
__REG32 WIDEBUS  : 1;
__REG32          :20;
} __mciclock_bits;

/* SD/MMC Command register */
typedef struct{
__REG32 CMDINDEX   : 6;
__REG32 RESPONSE   : 1;
__REG32 LONGRSP    : 1;
__REG32 INTERRUPT  : 1;
__REG32 PENDING    : 1;
__REG32 ENABLE     : 1;
__REG32            :21;
} __mcicommand_bits;

/* SD/MMC Command response register */
typedef struct{
__REG32 RESPCMD  : 6;
__REG32          :26;
} __mcirespcmd_bits;

/* SD/MMC Data control register */
typedef struct{
__REG32 ENABLE     : 1;
__REG32 DIRECTION  : 1;
__REG32 MODE       : 1;
__REG32 DMAENABLE  : 1;
__REG32 BLOCKSIZE  : 4;
__REG32            :24;
} __mcidatactrl_bits;

/* SD/MMC Status register */
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
__REG32 RXFIFOEMPTY      : 1;
__REG32 TXDATAAVLBL      : 1;
__REG32 RXDATAAVLBL      : 1;
__REG32                  :10;
} __mcistatus_bits;

/* SD/MMC Clear register */
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

/* SD/MMC FIFO counter register */
typedef struct{
__REG32 DATACOUNT  :15;
__REG32            :17;
} __mcififocnt_bits;

/* I2C control set register */
typedef struct{
__REG32       : 2;
__REG32 AA    : 1;
__REG32 SI    : 1;
__REG32 STO   : 1;
__REG32 STA   : 1;
__REG32 I2EN  : 1;
__REG32       :25;
} __i2conset_bits;

/* I2C control clear register */
typedef struct{
__REG32        : 2;
__REG32 AAC    : 1;
__REG32 SIC    : 1;
__REG32        : 1;
__REG32 STAC   : 1;
__REG32 I2ENC  : 1;
__REG32        :25;
} __i2conclr_bits;

/* I2C status register */
typedef struct{
__REG32 STATUS  : 8;
__REG32         :24;
} __i2stat_bits;

/* I2C data register */
typedef struct{
__REG32 DATA  : 8;
__REG32       :24;
} __i2dat_bits;

/* I2C slave address register */
typedef struct{
__REG32 GC    : 1;
__REG32 ADDR  : 7;
__REG32       :24;
} __i2adr_bits;

/* I2C SCL High Duty Cycle register */
typedef struct{
__REG32 SCLH   :16;
__REG32        :16;
} __i2sch_bits;

/* I2C scl duty cycle register */
typedef struct{
__REG32 SCLL   :16;
__REG32        :16;
} __i2scl_bits;

/* I2S Digital Audio Output Registes */
typedef struct{
__REG32 WORS_WIDTH    : 2;
__REG32 MONO          : 1;
__REG32 STOP          : 1;
__REG32 RESET         : 1;
__REG32 WS_SEL        : 1;
__REG32 WS_HALFPERIOD : 9;
__REG32 MUTE          : 1;
__REG32               :16;
} __i2sdao_bits;

/* I2S Digital Audio Input Register */
typedef struct{
__REG32 WORS_WIDTH    : 2;
__REG32 MONO          : 1;
__REG32 STOP          : 1;
__REG32 RESET         : 1;
__REG32 WS_SEL        : 1;
__REG32 WS_HALFPERIOD : 9;
__REG32               :17;
} __i2sdai_bits;

/* I2S Status Feedback Register */
typedef struct{
__REG32 IRQ           : 1;
__REG32 DMAREQ1       : 1;
__REG32 DMAREQ2       : 1;
__REG32               : 5;
__REG32 RX_LEVEL      : 8;
__REG32 TX_LEVEL      : 8;
__REG32               : 8;
} __i2sstate_bits;

/* I2S DMA Configuration Register */
typedef struct{
__REG32 RX_DMA_EN     : 1;
__REG32 TX_DMA_EN     : 1;
__REG32               : 6;
__REG32 RX_DEPTH_DMA  : 8;
__REG32 TX_DEPTH_DMA  : 8;
__REG32               : 8;
} __i2sdma_bits;

/* I2S Interrupt Request Control register */
typedef struct{
__REG32 RX_IRQ_EN     : 1;
__REG32 TX_IRQ_EN     : 1;
__REG32               : 6;
__REG32 RX_DEPTH_IRQ  : 8;
__REG32 TX_DEPTH_IRQ  : 8;
__REG32               : 8;
} __i2sirq_bits;

/* I2S Transmit Clock Rate Register */
typedef struct{
__REG32 TX_RATE       :10;
__REG32               :22;
} __i2stxrate_bits;

/* I2S Receive Clock Rate Register */
typedef struct{
__REG32 RX_RATE       :10;
__REG32               :22;
} __i2srxrate_bits;

/* TIMER interrupt register */
typedef struct{
__REG32 MR0INT  : 1;
__REG32 MR1INT  : 1;
__REG32 MR2INT  : 1;
__REG32 MR3INT  : 1;
__REG32 CR0INT  : 1;
__REG32 CR1INT  : 1;
__REG32 CR2INT  : 1;
__REG32 CR3INT  : 1;
__REG32         :24;
} __ir_bits;

/* TIMER control register */
typedef struct{
__REG32 CE  : 1;
__REG32 CR  : 1;
__REG32     :30;
} __tcr_bits;

/* TIMER count control register */
typedef struct{
__REG32 CTM : 2;     //Counter/Timer Mode
__REG32 CIS : 2;     //Count Input Select
__REG32     :28;
} __ctcr_bits;

/* TIMER match control register */
typedef struct{
__REG32 MR0I     : 1;
__REG32 MR0R     : 1;
__REG32 MR0S     : 1;
__REG32 MR1I     : 1;
__REG32 MR1R     : 1;
__REG32 MR1S     : 1;
__REG32 MR2I     : 1;
__REG32 MR2R     : 1;
__REG32 MR2S     : 1;
__REG32 MR3I     : 1;
__REG32 MR3R     : 1;
__REG32 MR3S     : 1;
__REG32          :20;
} __mcr_bits;

/* TIMER capture control register */
typedef struct{
__REG32 CAP0RE   : 1;
__REG32 CAP0FE   : 1;
__REG32 CAP0I    : 1;
__REG32 CAP1RE   : 1;
__REG32 CAP1FE   : 1;
__REG32 CAP1I    : 1;
__REG32 CAP2RE   : 1;
__REG32 CAP2FE   : 1;
__REG32 CAP2I    : 1;
__REG32 CAP3RE   : 1;
__REG32 CAP3FE   : 1;
__REG32 CAP3I    : 1;
__REG32          :20;
} __ccr_bits;

/* TIMER external match register */
typedef struct{
__REG32 EM0   : 1;
__REG32 EM1   : 1;
__REG32 EM2   : 1;
__REG32 EM3   : 1;
__REG32 EMC0  : 2;
__REG32 EMC1  : 2;
__REG32 EMC2  : 2;
__REG32 EMC3  : 2;
__REG32       :20;
} __emr_bits;

/* Watchdog mode register */
typedef struct{
__REG32 WDEN     : 1;
__REG32 WDRESET  : 1;
__REG32 WDTOF    : 1;
__REG32 WDINT    : 1;
__REG32          :28;
} __wdmod_bits;

/* Watchdog feed register */
typedef struct{
__REG32 FEED  : 8;
__REG32       :24;
} __wdfeed_bits;

/* Watchdog feed register */
typedef struct{
__REG32 WDSEL : 2;
__REG32       :30;
} __wdclksel_bits;

/* A/D Control Register */
typedef struct{
__REG32 SEL     : 8;
__REG32 CLKDIV  : 8;
__REG32 BURST   : 1;
__REG32 CLKS    : 3;
__REG32         : 1;
__REG32 PDN     : 1;
__REG32         : 2;
__REG32 START   : 3;
__REG32 EDGE    : 1;
__REG32         : 4;
} __adcr_bits;

/* A/D Global Data Register */
typedef struct{
__REG32         : 6;
__REG32 RESULT  :10;
__REG32         : 8;
__REG32 CHN     : 3;
__REG32         : 3;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __adgdr_bits;

/* A/D Status Register */
typedef struct{
__REG32 DONE0     : 1;
__REG32 DONE1     : 1;
__REG32 DONE2     : 1;
__REG32 DONE3     : 1;
__REG32 DONE4     : 1;
__REG32 DONE5     : 1;
__REG32 DONE6     : 1;
__REG32 DONE7     : 1;
__REG32 OVERRUN0  : 1;
__REG32 OVERRUN1  : 1;
__REG32 OVERRUN2  : 1;
__REG32 OVERRUN3  : 1;
__REG32 OVERRUN4  : 1;
__REG32 OVERRUN5  : 1;
__REG32 OVERRUN6  : 1;
__REG32 OVERRUN7  : 1;
__REG32 ADINT     : 1;
__REG32           :15;
} __adstat_bits;

/* A/D Intrrupt Enable Register */
typedef struct{
__REG32 ADINTEN0  : 1;
__REG32 ADINTEN1  : 1;
__REG32 ADINTEN2  : 1;
__REG32 ADINTEN3  : 1;
__REG32 ADINTEN4  : 1;
__REG32 ADINTEN5  : 1;
__REG32 ADINTEN6  : 1;
__REG32 ADINTEN7  : 1;
__REG32 ADGINTEN  : 1;
__REG32           :23;
} __adinten_bits;

/* A/D Data Register */
typedef struct{
__REG32         : 6;
__REG32 RESULT  :10;
__REG32         :14;
__REG32 OVERUN  : 1;
__REG32 DONE    : 1;
} __addr_bits;

/* D/A Converter Register */
typedef struct{
__REG32        : 6;
__REG32 VALUE  :10;
__REG32 BIAS   : 1;
__REG32        :15;
} __dacr_bits;

/* PWM interrupt register */
typedef struct{
__REG32 PWMMR0I : 1;
__REG32 PWMMR1I : 1;
__REG32 PWMMR2I : 1;
__REG32 PWMMR3I : 1;
__REG32         : 4;
__REG32 PWMMR4I : 1;
__REG32 PWMMR5I : 1;
__REG32 PWMMR6I : 1;
__REG32         :21;
} __pwmir_bits;

/* PWM1 timer control register */
typedef struct{
__REG32 CE     : 1;
__REG32 CR     : 1;
__REG32        : 1;
__REG32 PWMEN  : 1;
__REG32        :28;
} __pwmtcr1_bits;

/* PWM Count Control Register */
typedef struct{
__REG32 CM     : 2;
__REG32 CIS    : 2;
__REG32        :28;
} __pwmctcr_bits;

/* PWM match control register */
typedef struct{
__REG32 PWMMR0I  : 1;
__REG32 PWMMR0R  : 1;
__REG32 PWMMR0S  : 1;
__REG32 PWMMR1I  : 1;
__REG32 PWMMR1R  : 1;
__REG32 PWMMR1S  : 1;
__REG32 PWMMR2I  : 1;
__REG32 PWMMR2R  : 1;
__REG32 PWMMR2S  : 1;
__REG32 PWMMR3I  : 1;
__REG32 PWMMR3R  : 1;
__REG32 PWMMR3S  : 1;
__REG32 PWMMR4I  : 1;
__REG32 PWMMR4R  : 1;
__REG32 PWMMR4S  : 1;
__REG32 PWMMR5I  : 1;
__REG32 PWMMR5R  : 1;
__REG32 PWMMR5S  : 1;
__REG32 PWMMR6I  : 1;
__REG32 PWMMR6R  : 1;
__REG32 PWMMR6S  : 1;
__REG32          :11;
} __pwmmcr_bits;

/* PWM Capture Control Register */
typedef struct{
__REG32 CAP0RE   : 1;
__REG32 CAP0FE   : 1;
__REG32 CAP0INT  : 1;
__REG32 CAP1RE   : 1;
__REG32 CAP1FE   : 1;
__REG32 CAP1INT  : 1;
__REG32 CAP2RE   : 1;
__REG32 CAP2FE   : 1;
__REG32 CAP2INT  : 1;
__REG32 CAP3RE   : 1;
__REG32 CAP3FE   : 1;
__REG32 CAP3INT  : 1;
__REG32          :20;
} __pwmccr_bits;

/* PWM  control register */
typedef struct{
__REG32         : 2;
__REG32 PWMSEL2 : 1;
__REG32 PWMSEL3 : 1;
__REG32 PWMSEL4 : 1;
__REG32 PWMSEL5 : 1;
__REG32 PWMSEL6 : 1;
__REG32         : 2;
__REG32 PWMENA1 : 1;
__REG32 PWMENA2 : 1;
__REG32 PWMENA3 : 1;
__REG32 PWMENA4 : 1;
__REG32 PWMENA5 : 1;
__REG32 PWMENA6 : 1;
__REG32         :17;
} __pwmpcr_bits;

/* PWM latch enable register */
typedef struct{
__REG32 EM0L  : 1;
__REG32 EM1L  : 1;
__REG32 EM2L  : 1;
__REG32 EM3L  : 1;
__REG32 EM4L  : 1;
__REG32 EM5L  : 1;
__REG32 EM6L  : 1;
__REG32       :25;
} __pwmler_bits;

/* RTC interrupt location register */
typedef struct{
__REG32 RTCCIF  : 1;
__REG32 RTCALF  : 1;
__REG32 RTSSF   : 1;
__REG32         :29;
} __ilr_bits;

/* RTC clock tick counter register */
typedef struct{
__REG32 COUNTER  :15;
__REG32          :17;
} __ctc_bits;

/* RTC clock control register */
typedef struct{
__REG32 CLKEN   : 1;
__REG32 CTCRST  : 1;
__REG32 CTTEST  : 2;
__REG32 CLKSRC  : 1;
__REG32         :27;
} __rtcccr_bits;

/* RTC counter increment interrupt register */
typedef struct{
__REG32 IMSEC   : 1;
__REG32 IMMIN   : 1;
__REG32 IMHOUR  : 1;
__REG32 IMDOM   : 1;
__REG32 IMDOW   : 1;
__REG32 IMDOY   : 1;
__REG32 IMMON   : 1;
__REG32 IMYEAR  : 1;
__REG32         :24;
} __ciir_bits;

/* RTC Counter Increment Select Mask Register */
typedef struct{
__REG32 SUBSECSEL : 3;
__REG32           : 4;
__REG32 SUBSECENA : 1;
__REG32           :24;
} __ciss_bits;

/* RTC alarm mask register */
typedef struct{
__REG32 AMRSEC   : 1;
__REG32 AMRMIN   : 1;
__REG32 AMRHOUR  : 1;
__REG32 AMRDOM   : 1;
__REG32 AMRDOW   : 1;
__REG32 AMRDOY   : 1;
__REG32 AMRMON   : 1;
__REG32 AMRYEAR  : 1;
__REG32          :24;
} __amr_bits;

/* RTC consolidated time register 0 */
typedef struct{
__REG32 SEC   : 6;
__REG32       : 2;
__REG32 MIN   : 6;
__REG32       : 2;
__REG32 HOUR  : 5;
__REG32       : 3;
__REG32 DOW   : 3;
__REG32       : 5;
} __ctime0_bits;

/* RTC consolidated time register 1 */
typedef struct{
__REG32 DOM   : 5;
__REG32       : 3;
__REG32 MON   : 4;
__REG32       : 4;
__REG32 YEAR  :12;
__REG32       : 4;
} __ctime1_bits;

/* RTC consolidated time register 2 */
typedef struct{
__REG32 DOY  :12;
__REG32      :20;
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

/* RTC prescaler value, integer portion register */
typedef struct{
__REG32 VALUE  :13;
__REG32        :19;
} __preint_bits;

/* RTC prescaler value, fractional portion register */
typedef struct{
__REG32 VALUE  :15;
__REG32        :17;
} __prefrac_bits;

/* DMA Interrupt Status Register */
typedef struct{
__REG32 INTSTATUS0  : 1;
__REG32 INTSTATUS1  : 1;
__REG32             :30;
} __dmacintstatus_bits;

/* DMA Interrupt Terminal Count Request Status Register */
typedef struct{
__REG32 INTTCSTATUS0  : 1;
__REG32 INTTCSTATUS1  : 1;
__REG32               :30;
} __dmacinttcstatus_bits;

/* DMA Interrupt Terminal Count Request Clear Register */
typedef struct{
__REG32 INTTCCLEAR0   : 1;
__REG32 INTTCCLEAR1   : 1;
__REG32               :30;
} __dmacinttcclear_bits;

/* DMA Interrupt Error Status Register */
typedef struct{
__REG32 INTERRORSTATUS0 : 1;
__REG32 INTERRORSTATUS1 : 1;
__REG32                 :30;
} __dmacinterrstat_bits;

/* DMA Interrupt Error Clear Register */
typedef struct{
__REG32 INTERRCLR0      : 1;
__REG32 INTERRCLR1      : 1;
__REG32                 :30;
} __dmacinterrclr_bits;

/* DMA Raw Interrupt Terminal Count Status Register */
typedef struct{
__REG32 RAWINTTCSTATUS0 : 1;
__REG32 RAWINTTCSTATUS1 : 1;
__REG32                 :30;
} __dmacrawinttcstatus_bits;

/* DMA Raw Error Interrupt Status Register */
typedef struct{
__REG32 RAWINTERRORSTATUS0  : 1;
__REG32 RAWINTERRORSTATUS1  : 1;
__REG32                     :30;
} __dmacrawinterrorstatus_bits;

/* DMA Enabled Channel Register */
typedef struct{
__REG32 ENABLEDCHANNELS0  : 1;
__REG32 ENABLEDCHANNELS1  : 1;
__REG32                   :30;
} __dmacenbldchns_bits;

/* DMA Software Burst Request Register */
typedef struct{
__REG32 SOFTBREQSSP0TX    : 1;
__REG32 SOFTBREQSSP0RX    : 1;
__REG32 SOFTBREQSSP1TX    : 1;
__REG32 SOFTBREQSSP1RX    : 1;
__REG32 SOFTBREQSDMMC     : 1;
__REG32                   :27;
} __dmacsoftbreq_bits;

/* DMA Software Single Request Register */
typedef struct{
__REG32 SOFTREQSSP0TX     : 1;
__REG32 SOFTREQSSP0RX     : 1;
__REG32 SOFTREQSSP1TX     : 1;
__REG32 SOFTREQSSP1RX     : 1;
__REG32 SOFTREQSDMMC      : 1;
__REG32 SOFTSREQI2S0      : 1;
__REG32 SOFTSREQI2S1      : 1;
__REG32                   :25;
} __dmacsoftsreq_bits;

/* DMA Software Last Burst Request Register */
typedef struct{
__REG32                   : 4;
__REG32 SOFTLBREQSDMMC    : 1;
__REG32                   :27;
} __dmacsoftlbreq_bits;

/* DMA Software Last Single Request Register */
typedef struct{
__REG32                   : 4;
__REG32 SOFTLSREQSDMMC    : 1;
__REG32                   :27;
} __dmacsoftlsreq_bits;

/* DMA Synchronization Register */
typedef struct{
__REG32 DMACSYNC    :16;
__REG32             :16;
} __dmacsync_bits;

/* DMA Configuration Register */
typedef struct{
__REG32 E   : 1;
__REG32 M   : 1;
__REG32     :30;
} __dmacconfig_bits;

/* DMA Software Burst Request Register */
typedef struct{
__REG32      : 2;
__REG32 LLI  :30;
} __dma_lli_bits;

/* DMA Channel Control Registers */
typedef struct{
__REG32 TRANSFERSIZE  :12;
__REG32 SBSIZE        : 3;
__REG32 DBSIZE        : 3;
__REG32 SWIDTH        : 3;
__REG32 DWIDTH        : 3;
__REG32               : 2;
__REG32 SI            : 1;
__REG32 DI            : 1;
__REG32 PROT1         : 1;
__REG32 PROT2         : 1;
__REG32 PROT3         : 1;
__REG32 I             : 1;
} __dma_ctrl_bits;

/* DMA Channel Configuration Registers */
typedef struct{
__REG32 E               : 1;
__REG32 SRCPERIPHERAL   : 4;
__REG32                 : 1;
__REG32 DESTPERIPHERAL  : 4;
__REG32                 : 1;
__REG32 FLOWCNTRL       : 3;
__REG32 IE              : 1;
__REG32 ITC             : 1;
__REG32 L               : 1;
__REG32 A               : 1;
__REG32 H               : 1;
__REG32                 :13;
} __dma_cfg_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler **************************/

/***************************************************************************
 **
 ** System control block
 **
 ***************************************************************************/
__IO_REG32_BIT(MEMMAP,                0xE01FC040,__READ_WRITE ,__memmap_bits);
__IO_REG32_BIT(RSIR,                  0xE01FC180,__READ_WRITE ,__rsir_bits);
__IO_REG32_BIT(EXTINT,                0xE01FC140,__READ_WRITE ,__extint_bits);
__IO_REG32_BIT(EXTMODE,               0xE01FC148,__READ_WRITE ,__extmode_bits);
__IO_REG32_BIT(EXTPOLAR,              0xE01FC14C,__READ_WRITE ,__extpolar_bits);
__IO_REG32_BIT(SCS,                   0xE01FC1A0,__READ_WRITE ,__scs_bits);
__IO_REG32(    CSPR,                  0xE01FC184,__WRITE);
__IO_REG32_BIT(PLLCON,                0xE01FC080,__READ_WRITE ,__pllcon_bits);
__IO_REG32_BIT(PLLCFG,                0xE01FC084,__READ_WRITE ,__pllcfg_bits);
__IO_REG32_BIT(PLLSTAT,               0xE01FC088,__READ       ,__pllstat_bits);
__IO_REG32_BIT(PLLFEED,               0xE01FC08C,__WRITE      ,__pllfeed_bits);
__IO_REG32_BIT(APBDIV,                0xE01FC100,__READ_WRITE ,__apbdiv_bits);
__IO_REG32_BIT(CCLKCFG,               0xE01FC104,__READ_WRITE ,__cclkcfg_bits);
__IO_REG32_BIT(USBCLKCFG,             0xE01FC108,__READ_WRITE ,__usbclkcfg_bits);
__IO_REG32_BIT(CLKSRCSEL,             0xE01FC10C,__READ_WRITE ,__clksrcsel_bits);
__IO_REG32_BIT(IRCTRIM,               0xE01FC1A4,__READ_WRITE ,__irctrim_bits);
__IO_REG32_BIT(PCLKSEL0,              0xE01FC1A8,__READ_WRITE ,__pclksel0_bits);
__IO_REG32_BIT(PCLKSEL1,              0xE01FC1AC,__READ_WRITE ,__pclksel1_bits);
__IO_REG32_BIT(PCON,                  0xE01FC0C0,__READ_WRITE ,__pcon_bits);
__IO_REG32_BIT(PCONP,                 0xE01FC0C4,__READ_WRITE ,__pconp_bits);
__IO_REG32_BIT(INTWAKE,               0xE01FC144,__READ_WRITE ,__intwake_bits);

/***************************************************************************
 **
 ** AHB
 **
 ***************************************************************************/
__IO_REG32_BIT(AHBCFG1,               0xE01FC188,__READ_WRITE ,__ahbcfg1_bits);
__IO_REG32_BIT(AHBCFG2,               0xE01FC18C,__READ_WRITE ,__ahbcfg2_bits);

/***************************************************************************
 **
 ** MAM
 **
 ***************************************************************************/
__IO_REG32_BIT(MAMCR,                 0xE01FC000,__READ_WRITE ,__mamcr_bits);
__IO_REG32_BIT(MAMTIM,                0xE01FC004,__READ_WRITE ,__mamtim_bits);

/***************************************************************************
 **
 ** EMC
 **
 ***************************************************************************/
__IO_REG32_BIT(EMCCONTROL,            0xFFE08000,__READ_WRITE ,__emc_ctrl_bits);
__IO_REG32_BIT(EMCSTATUS,             0xFFE08004,__READ       ,__emc_st_bits);
__IO_REG32_BIT(EMCCONFIG,             0xFFE08008,__READ_WRITE ,__emc_cfg_bits);
__IO_REG32_BIT(EMCSTATICCNFG0,        0xFFE08200,__READ_WRITE ,__emc_s_config_bits);
__IO_REG32_BIT(EMCSTATICWAITWEN0,     0xFFE08204,__READ_WRITE ,__emc_s_wait_wen_bits);
__IO_REG32_BIT(EMCSTATICWAITOEN0,     0xFFE08208,__READ_WRITE ,__emc_s_wait_oen_bits);
__IO_REG32_BIT(EMCSTATICWAITRD0,      0xFFE0820C,__READ_WRITE ,__emc_s_wait_rd_bits);
__IO_REG32_BIT(EMCSTATICWAITPG0,      0xFFE08210,__READ_WRITE ,__emc_s_wait_pg_bits);
__IO_REG32_BIT(EMCSTATICWAITWR0,      0xFFE08214,__READ_WRITE ,__emc_s_wait_wr_bits);
__IO_REG32_BIT(EMCSTATICWAITTURN0,    0xFFE08218,__READ_WRITE ,__emc_s_wait_turn_bits);
__IO_REG32_BIT(EMCSTATICCNFG1,        0xFFE08220,__READ_WRITE ,__emc_s_config_bits);
__IO_REG32_BIT(EMCSTATICWAITWEN1,     0xFFE08224,__READ_WRITE ,__emc_s_wait_wen_bits);
__IO_REG32_BIT(EMCSTATICWAITOEN1,     0xFFE08228,__READ_WRITE ,__emc_s_wait_oen_bits);
__IO_REG32_BIT(EMCSTATICWAITRD1,      0xFFE0822C,__READ_WRITE ,__emc_s_wait_rd_bits);
__IO_REG32_BIT(EMCSTATICWAITPG1,      0xFFE08230,__READ_WRITE ,__emc_s_wait_pg_bits);
__IO_REG32_BIT(EMCSTATICWAITWR1,      0xFFE08234,__READ_WRITE ,__emc_s_wait_wr_bits);
__IO_REG32_BIT(EMCSTATICWAITTURN1,    0xFFE08238,__READ_WRITE ,__emc_s_wait_turn_bits);
__IO_REG32_BIT(EMCSTATICEXTENDEDWAIT, 0xFFE08880,__READ_WRITE ,__emc_s_ext_wait_bits);


/***************************************************************************
 **
 ** VIC
 **
 ***************************************************************************/
__IO_REG32_BIT(VICIRQStatus,          0xFFFFF000,__READ       ,__vicint_bits);
__IO_REG32_BIT(VICFIQStatus,          0xFFFFF004,__READ       ,__vicint_bits);
__IO_REG32_BIT(VICRawIntr,            0xFFFFF008,__READ       ,__vicint_bits);
__IO_REG32_BIT(VICIntSelect,          0xFFFFF00C,__READ_WRITE ,__vicint_bits);
__IO_REG32_BIT(VICIntEnable,          0xFFFFF010,__READ_WRITE ,__vicint_bits);
__IO_REG32_BIT(VICIntEnClear,         0xFFFFF014,__WRITE      ,__vicint_bits);
__IO_REG32_BIT(VICSoftInt,            0xFFFFF018,__READ_WRITE ,__vicint_bits);
__IO_REG32_BIT(VICSoftIntClear,       0xFFFFF01C,__WRITE      ,__vicint_bits);
__IO_REG32_BIT(VICProtection,         0xFFFFF020,__READ_WRITE ,__vicprotection_bits);
__IO_REG32_BIT(VICSWPriorityMask,     0xFFFFF024,__READ_WRITE ,__vicswprmask_bits);
__IO_REG32(    VICVectAddr0,          0xFFFFF100,__READ_WRITE);
__IO_REG32(    VICVectAddr1,          0xFFFFF104,__READ_WRITE);
__IO_REG32(    VICVectAddr2,          0xFFFFF108,__READ_WRITE);
__IO_REG32(    VICVectAddr3,          0xFFFFF10C,__READ_WRITE);
__IO_REG32(    VICVectAddr4,          0xFFFFF110,__READ_WRITE);
__IO_REG32(    VICVectAddr5,          0xFFFFF114,__READ_WRITE);
__IO_REG32(    VICVectAddr6,          0xFFFFF118,__READ_WRITE);
__IO_REG32(    VICVectAddr7,          0xFFFFF11C,__READ_WRITE);
__IO_REG32(    VICVectAddr8,          0xFFFFF120,__READ_WRITE);
__IO_REG32(    VICVectAddr9,          0xFFFFF124,__READ_WRITE);
__IO_REG32(    VICVectAddr10,         0xFFFFF128,__READ_WRITE);
__IO_REG32(    VICVectAddr11,         0xFFFFF12C,__READ_WRITE);
__IO_REG32(    VICVectAddr12,         0xFFFFF130,__READ_WRITE);
__IO_REG32(    VICVectAddr13,         0xFFFFF134,__READ_WRITE);
__IO_REG32(    VICVectAddr14,         0xFFFFF138,__READ_WRITE);
__IO_REG32(    VICVectAddr15,         0xFFFFF13C,__READ_WRITE);
__IO_REG32(    VICVectAddr16,         0xFFFFF140,__READ_WRITE);
__IO_REG32(    VICVectAddr17,         0xFFFFF144,__READ_WRITE);
__IO_REG32(    VICVectAddr18,         0xFFFFF148,__READ_WRITE);
__IO_REG32(    VICVectAddr19,         0xFFFFF14C,__READ_WRITE);
__IO_REG32(    VICVectAddr20,         0xFFFFF150,__READ_WRITE);
__IO_REG32(    VICVectAddr21,         0xFFFFF154,__READ_WRITE);
__IO_REG32(    VICVectAddr22,         0xFFFFF158,__READ_WRITE);
__IO_REG32(    VICVectAddr23,         0xFFFFF15C,__READ_WRITE);
__IO_REG32(    VICVectAddr24,         0xFFFFF160,__READ_WRITE);
__IO_REG32(    VICVectAddr25,         0xFFFFF164,__READ_WRITE);
__IO_REG32(    VICVectAddr26,         0xFFFFF168,__READ_WRITE);
__IO_REG32(    VICVectAddr27,         0xFFFFF16C,__READ_WRITE);
__IO_REG32(    VICVectAddr28,         0xFFFFF170,__READ_WRITE);
__IO_REG32(    VICVectAddr29,         0xFFFFF174,__READ_WRITE);
__IO_REG32(    VICVectAddr30,         0xFFFFF178,__READ_WRITE);
__IO_REG32(    VICVectAddr31,         0xFFFFF17C,__READ_WRITE);
__IO_REG32_BIT(VICVectPriority0,      0xFFFFF200,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority1,      0xFFFFF204,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority2,      0xFFFFF208,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority3,      0xFFFFF20C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority4,      0xFFFFF210,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority5,      0xFFFFF214,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority6,      0xFFFFF218,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority7,      0xFFFFF21C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority8,      0xFFFFF220,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority9,      0xFFFFF224,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority10,     0xFFFFF228,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority11,     0xFFFFF22C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority12,     0xFFFFF230,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority13,     0xFFFFF234,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority14,     0xFFFFF238,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority15,     0xFFFFF23C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority16,     0xFFFFF240,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority17,     0xFFFFF244,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority18,     0xFFFFF248,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority19,     0xFFFFF24C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority20,     0xFFFFF250,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority21,     0xFFFFF254,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority22,     0xFFFFF258,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority23,     0xFFFFF25C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority24,     0xFFFFF260,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority25,     0xFFFFF264,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority26,     0xFFFFF268,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority27,     0xFFFFF26C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority28,     0xFFFFF270,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority29,     0xFFFFF274,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority30,     0xFFFFF278,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32_BIT(VICVectPriority31,     0xFFFFF27C,__READ_WRITE ,__vicvectpr_bits);
__IO_REG32(    VICAddress,            0xFFFFFF00,__READ_WRITE);

/***************************************************************************
 **
 ** Pin connect block
 **
 ***************************************************************************/
__IO_REG32_BIT(PINSEL0,               0xE002C000,__READ_WRITE ,__pinsel0_bits);
__IO_REG32_BIT(PINSEL1,               0xE002C004,__READ_WRITE ,__pinsel1_bits);
__IO_REG32_BIT(PINSEL2,               0xE002C008,__READ_WRITE ,__pinsel2_bits);
__IO_REG32_BIT(PINSEL3,               0xE002C00C,__READ_WRITE ,__pinsel3_bits);
__IO_REG32_BIT(PINSEL4,               0xE002C010,__READ_WRITE ,__pinsel4_bits);
__IO_REG32_BIT(PINSEL5,               0xE002C014,__READ_WRITE ,__pinsel5_bits);
__IO_REG32_BIT(PINSEL6,               0xE002C018,__READ_WRITE ,__pinsel6_bits);
__IO_REG32_BIT(PINSEL7,               0xE002C01C,__READ_WRITE ,__pinsel7_bits);
__IO_REG32_BIT(PINSEL8,               0xE002C020,__READ_WRITE ,__pinsel8_bits);
__IO_REG32_BIT(PINSEL9,               0xE002C024,__READ_WRITE ,__pinsel9_bits);
__IO_REG32_BIT(PINSEL10,              0xE002C028,__READ_WRITE ,__pinsel10_bits);
__IO_REG32_BIT(PINMODE0,              0xE002C040,__READ_WRITE ,__pinsel0_bits);
__IO_REG32_BIT(PINMODE1,              0xE002C044,__READ_WRITE ,__pinsel1_bits);
__IO_REG32_BIT(PINMODE2,              0xE002C048,__READ_WRITE ,__pinsel2_bits);
__IO_REG32_BIT(PINMODE3,              0xE002C04C,__READ_WRITE ,__pinsel3_bits);
__IO_REG32_BIT(PINMODE4,              0xE002C050,__READ_WRITE ,__pinsel4_bits);
__IO_REG32_BIT(PINMODE5,              0xE002C054,__READ_WRITE ,__pinsel5_bits);
__IO_REG32_BIT(PINMODE6,              0xE002C058,__READ_WRITE ,__pinsel6_bits);
__IO_REG32_BIT(PINMODE7,              0xE002C05C,__READ_WRITE ,__pinsel7_bits);
__IO_REG32_BIT(PINMODE8,              0xE002C060,__READ_WRITE ,__pinsel8_bits);
__IO_REG32_BIT(PINMODE9,              0xE002C064,__READ_WRITE ,__pinsel9_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(IO0PIN,          0xE0028000,__READ      ,__gpio0_bits);
__IO_REG32_BIT(IO0SET,          0xE0028004,__READ_WRITE,__gpio0_bits);
__IO_REG32_BIT(IO0DIR,          0xE0028008,__READ_WRITE,__gpio0_bits);
__IO_REG32_BIT(IO0CLR,          0xE002800C,__WRITE     ,__gpio0_bits);
__IO_REG32_BIT(FIO0DIR,         0x3FFFC000,__READ_WRITE,__fgpio0_bits);
#define FIO0DIR0          FIO0DIR_bit.__byte0
#define FIO0DIR0_bit      FIO0DIR_bit.__byte0_bit
#define FIO0DIR1          FIO0DIR_bit.__byte1
#define FIO0DIR1_bit      FIO0DIR_bit.__byte1_bit
#define FIO0DIR2          FIO0DIR_bit.__byte2
#define FIO0DIR2_bit      FIO0DIR_bit.__byte2_bit
#define FIO0DIR3          FIO0DIR_bit.__byte3
#define FIO0DIR3_bit      FIO0DIR_bit.__byte3_bit
#define FIO0DIRL          FIO0DIR_bit.__shortl
#define FIO0DIRL_bit      FIO0DIR_bit.__shortl_bit
#define FIO0DIRU          FIO0DIR_bit.__shortu
#define FIO0DIRU_bit      FIO0DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO0MASK,        0x3FFFC010,__READ_WRITE,__fgpio0_bits);
#define FIO0MASK0         FIO0MASK_bit.__byte0
#define FIO0MASK0_bit     FIO0MASK_bit.__byte0_bit
#define FIO0MASK1         FIO0MASK_bit.__byte1
#define FIO0MASK1_bit     FIO0MASK_bit.__byte1_bit
#define FIO0MASK2         FIO0MASK_bit.__byte2
#define FIO0MASK2_bit     FIO0MASK_bit.__byte2_bit
#define FIO0MASK3         FIO0MASK_bit.__byte3
#define FIO0MASK3_bit     FIO0MASK_bit.__byte3_bit
#define FIO0MASKL         FIO0MASK_bit.__shortl
#define FIO0MASKL_bit     FIO0MASK_bit.__shortl_bit
#define FIO0MASKU         FIO0MASK_bit.__shortu
#define FIO0MASKU_bit     FIO0MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO0PIN,         0x3FFFC014,__READ_WRITE,__fgpio0_bits);
#define FIO0PIN0          FIO0PIN_bit.__byte0
#define FIO0PIN0_bit      FIO0PIN_bit.__byte0_bit
#define FIO0PIN1          FIO0PIN_bit.__byte1
#define FIO0PIN1_bit      FIO0PIN_bit.__byte1_bit
#define FIO0PIN2          FIO0PIN_bit.__byte2
#define FIO0PIN2_bit      FIO0PIN_bit.__byte2_bit
#define FIO0PIN3          FIO0PIN_bit.__byte3
#define FIO0PIN3_bit      FIO0PIN_bit.__byte3_bit
#define FIO0PINL          FIO0PIN_bit.__shortl
#define FIO0PINL_bit      FIO0PIN_bit.__shortl_bit
#define FIO0PINU          FIO0PIN_bit.__shortu
#define FIO0PINU_bit      FIO0PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO0SET,         0x3FFFC018,__READ_WRITE,__fgpio0_bits);
#define FIO0SET0          FIO0SET_bit.__byte0
#define FIO0SET0_bit      FIO0SET_bit.__byte0_bit
#define FIO0SET1          FIO0SET_bit.__byte1
#define FIO0SET1_bit      FIO0SET_bit.__byte1_bit
#define FIO0SET2          FIO0SET_bit.__byte2
#define FIO0SET2_bit      FIO0SET_bit.__byte2_bit
#define FIO0SET3          FIO0SET_bit.__byte3
#define FIO0SET3_bit      FIO0SET_bit.__byte3_bit
#define FIO0SETL          FIO0SET_bit.__shortl
#define FIO0SETL_bit      FIO0SET_bit.__shortl_bit
#define FIO0SETU          FIO0SET_bit.__shortu
#define FIO0SETU_bit      FIO0SET_bit.__shortu_bit
__IO_REG32_BIT(FIO0CLR,         0x3FFFC01C,__WRITE     ,__fgpio0_bits);
#define FIO0CLR0          FIO0CLR_bit.__byte0
#define FIO0CLR0_bit      FIO0CLR_bit.__byte0_bit
#define FIO0CLR1          FIO0CLR_bit.__byte1
#define FIO0CLR1_bit      FIO0CLR_bit.__byte1_bit
#define FIO0CLR2          FIO0CLR_bit.__byte2
#define FIO0CLR2_bit      FIO0CLR_bit.__byte2_bit
#define FIO0CLR3          FIO0CLR_bit.__byte3
#define FIO0CLR3_bit      FIO0CLR_bit.__byte3_bit
#define FIO0CLRL          FIO0CLR_bit.__shortl
#define FIO0CLRL_bit      FIO0CLR_bit.__shortl_bit
#define FIO0CLRU          FIO0CLR_bit.__shortu
#define FIO0CLRU_bit      FIO0CLR_bit.__shortu_bit
__IO_REG32_BIT(IO1PIN,          0xE0028010,__READ      ,__gpio1_bits);
__IO_REG32_BIT(IO1SET,          0xE0028014,__READ_WRITE,__gpio1_bits);
__IO_REG32_BIT(IO1DIR,          0xE0028018,__READ_WRITE,__gpio1_bits);
__IO_REG32_BIT(IO1CLR,          0xE002801C,__WRITE     ,__gpio1_bits);
__IO_REG32_BIT(FIO1DIR,         0x3FFFC020,__READ_WRITE,__fgpio1_bits);
#define FIO1DIR0          FIO1DIR_bit.__byte0
#define FIO1DIR0_bit      FIO1DIR_bit.__byte0_bit
#define FIO1DIR1          FIO1DIR_bit.__byte1
#define FIO1DIR1_bit      FIO1DIR_bit.__byte1_bit
#define FIO1DIR2          FIO1DIR_bit.__byte2
#define FIO1DIR2_bit      FIO1DIR_bit.__byte2_bit
#define FIO1DIR3          FIO1DIR_bit.__byte3
#define FIO1DIR3_bit      FIO1DIR_bit.__byte3_bit
#define FIO1DIRL          FIO1DIR_bit.__shortl
#define FIO1DIRL_bit      FIO1DIR_bit.__shortl_bit
#define FIO1DIRU          FIO1DIR_bit.__shortu
#define FIO1DIRU_bit      FIO1DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO1MASK,        0x3FFFC030,__READ_WRITE,__fgpio1_bits);
#define FIO1MASK0         FIO1MASK_bit.__byte0
#define FIO1MASK0_bit     FIO1MASK_bit.__byte0_bit
#define FIO1MASK1         FIO1MASK_bit.__byte1
#define FIO1MASK1_bit     FIO1MASK_bit.__byte1_bit
#define FIO1MASK2         FIO1MASK_bit.__byte2
#define FIO1MASK2_bit     FIO1MASK_bit.__byte2_bit
#define FIO1MASK3         FIO1MASK_bit.__byte3
#define FIO1MASK3_bit     FIO1MASK_bit.__byte3_bit
#define FIO1MASKL         FIO1MASK_bit.__shortl
#define FIO1MASKL_bit     FIO1MASK_bit.__shortl_bit
#define FIO1MASKU         FIO1MASK_bit.__shortu
#define FIO1MASKU_bit     FIO1MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO1PIN,         0x3FFFC034,__READ_WRITE,__fgpio1_bits);
#define FIO1PIN0          FIO1PIN_bit.__byte0
#define FIO1PIN0_bit      FIO1PIN_bit.__byte0_bit
#define FIO1PIN1          FIO1PIN_bit.__byte1
#define FIO1PIN1_bit      FIO1PIN_bit.__byte1_bit
#define FIO1PIN2          FIO1PIN_bit.__byte2
#define FIO1PIN2_bit      FIO1PIN_bit.__byte2_bit
#define FIO1PIN3          FIO1PIN_bit.__byte3
#define FIO1PIN3_bit      FIO1PIN_bit.__byte3_bit
#define FIO1PINL          FIO1PIN_bit.__shortl
#define FIO1PINL_bit      FIO1PIN_bit.__shortl_bit
#define FIO1PINU          FIO1PIN_bit.__shortu
#define FIO1PINU_bit      FIO1PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO1SET,         0x3FFFC038,__READ_WRITE,__fgpio1_bits);
#define FIO1SET0          FIO1SET_bit.__byte0
#define FIO1SET0_bit      FIO1SET_bit.__byte0_bit
#define FIO1SET1          FIO1SET_bit.__byte1
#define FIO1SET1_bit      FIO1SET_bit.__byte1_bit
#define FIO1SET2          FIO1SET_bit.__byte2
#define FIO1SET2_bit      FIO1SET_bit.__byte2_bit
#define FIO1SET3          FIO1SET_bit.__byte3
#define FIO1SET3_bit      FIO1SET_bit.__byte3_bit
#define FIO1SETL          FIO1SET_bit.__shortl
#define FIO1SETL_bit      FIO1SET_bit.__shortl_bit
#define FIO1SETU          FIO1SET_bit.__shortu
#define FIO1SETU_bit      FIO1SET_bit.__shortu_bit
__IO_REG32_BIT(FIO1CLR,         0x3FFFC03C,__WRITE     ,__fgpio1_bits);
#define FIO1CLR0          FIO1CLR_bit.__byte0
#define FIO1CLR0_bit      FIO1CLR_bit.__byte0_bit
#define FIO1CLR1          FIO1CLR_bit.__byte1
#define FIO1CLR1_bit      FIO1CLR_bit.__byte1_bit
#define FIO1CLR2          FIO1CLR_bit.__byte2
#define FIO1CLR2_bit      FIO1CLR_bit.__byte2_bit
#define FIO1CLR3          FIO1CLR_bit.__byte3
#define FIO1CLR3_bit      FIO1CLR_bit.__byte3_bit
#define FIO1CLRL          FIO1CLR_bit.__shortl
#define FIO1CLRL_bit      FIO1CLR_bit.__shortl_bit
#define FIO1CLRU          FIO1CLR_bit.__shortu
#define FIO1CLRU_bit      FIO1CLR_bit.__shortu_bit
__IO_REG32_BIT(FIO2DIR,         0x3FFFC040,__READ_WRITE,__fgpio2_bits);
#define FIO2DIR0          FIO2DIR_bit.__byte0
#define FIO2DIR0_bit      FIO2DIR_bit.__byte0_bit
#define FIO2DIR1          FIO2DIR_bit.__byte1
#define FIO2DIR1_bit      FIO2DIR_bit.__byte1_bit
#define FIO2DIR2          FIO2DIR_bit.__byte2
#define FIO2DIR2_bit      FIO2DIR_bit.__byte2_bit
#define FIO2DIR3          FIO2DIR_bit.__byte3
#define FIO2DIR3_bit      FIO2DIR_bit.__byte3_bit
#define FIO2DIRL          FIO2DIR_bit.__shortl
#define FIO2DIRL_bit      FIO2DIR_bit.__shortl_bit
#define FIO2DIRU          FIO2DIR_bit.__shortu
#define FIO2DIRU_bit      FIO2DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO2MASK,        0x3FFFC050,__READ_WRITE,__fgpio2_bits);
#define FIO2MASK0         FIO2MASK_bit.__byte0
#define FIO2MASK0_bit     FIO2MASK_bit.__byte0_bit
#define FIO2MASK1         FIO2MASK_bit.__byte1
#define FIO2MASK1_bit     FIO2MASK_bit.__byte1_bit
#define FIO2MASK2         FIO2MASK_bit.__byte2
#define FIO2MASK2_bit     FIO2MASK_bit.__byte2_bit
#define FIO2MASK3         FIO2MASK_bit.__byte3
#define FIO2MASK3_bit     FIO2MASK_bit.__byte3_bit
#define FIO2MASKL         FIO2MASK_bit.__shortl
#define FIO2MASKL_bit     FIO2MASK_bit.__shortl_bit
#define FIO2MASKU         FIO2MASK_bit.__shortu
#define FIO2MASKU_bit     FIO2MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO2PIN,         0x3FFFC054,__READ_WRITE,__fgpio2_bits);
#define FIO2PIN0          FIO2PIN_bit.__byte0
#define FIO2PIN0_bit      FIO2PIN_bit.__byte0_bit
#define FIO2PIN1          FIO2PIN_bit.__byte1
#define FIO2PIN1_bit      FIO2PIN_bit.__byte1_bit
#define FIO2PIN2          FIO2PIN_bit.__byte2
#define FIO2PIN2_bit      FIO2PIN_bit.__byte2_bit
#define FIO2PIN3          FIO2PIN_bit.__byte3
#define FIO2PIN3_bit      FIO2PIN_bit.__byte3_bit
#define FIO2PINL          FIO2PIN_bit.__shortl
#define FIO2PINL_bit      FIO2PIN_bit.__shortl_bit
#define FIO2PINU          FIO2PIN_bit.__shortu
#define FIO2PINU_bit      FIO2PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO2SET,         0x3FFFC058,__READ_WRITE,__fgpio2_bits);
#define FIO2SET0          FIO2SET_bit.__byte0
#define FIO2SET0_bit      FIO2SET_bit.__byte0_bit
#define FIO2SET1          FIO2SET_bit.__byte1
#define FIO2SET1_bit      FIO2SET_bit.__byte1_bit
#define FIO2SET2          FIO2SET_bit.__byte2
#define FIO2SET2_bit      FIO2SET_bit.__byte2_bit
#define FIO2SET3          FIO2SET_bit.__byte3
#define FIO2SET3_bit      FIO2SET_bit.__byte3_bit
#define FIO2SETL          FIO2SET_bit.__shortl
#define FIO2SETL_bit      FIO2SET_bit.__shortl_bit
#define FIO2SETU          FIO2SET_bit.__shortu
#define FIO2SETU_bit      FIO2SET_bit.__shortu_bit
__IO_REG32_BIT(FIO2CLR,         0x3FFFC05C,__WRITE     ,__fgpio2_bits);
#define FIO2CLR0          FIO2CLR_bit.__byte0
#define FIO2CLR0_bit      FIO2CLR_bit.__byte0_bit
#define FIO2CLR1          FIO2CLR_bit.__byte1
#define FIO2CLR1_bit      FIO2CLR_bit.__byte1_bit
#define FIO2CLR2          FIO2CLR_bit.__byte2
#define FIO2CLR2_bit      FIO2CLR_bit.__byte2_bit
#define FIO2CLR3          FIO2CLR_bit.__byte3
#define FIO2CLR3_bit      FIO2CLR_bit.__byte3_bit
#define FIO2CLRL          FIO2CLR_bit.__shortl
#define FIO2CLRL_bit      FIO2CLR_bit.__shortl_bit
#define FIO2CLRU          FIO2CLR_bit.__shortu
#define FIO2CLRU_bit      FIO2CLR_bit.__shortu_bit
__IO_REG32_BIT(FIO3DIR,         0x3FFFC060,__READ_WRITE,__fgpio3_bits);
#define FIO3DIR0          FIO3DIR_bit.__byte0
#define FIO3DIR0_bit      FIO3DIR_bit.__byte0_bit
#define FIO3DIR1          FIO3DIR_bit.__byte1
#define FIO3DIR1_bit      FIO3DIR_bit.__byte1_bit
#define FIO3DIR2          FIO3DIR_bit.__byte2
#define FIO3DIR2_bit      FIO3DIR_bit.__byte2_bit
#define FIO3DIR3          FIO3DIR_bit.__byte3
#define FIO3DIR3_bit      FIO3DIR_bit.__byte3_bit
#define FIO3DIRL          FIO3DIR_bit.__shortl
#define FIO3DIRL_bit      FIO3DIR_bit.__shortl_bit
#define FIO3DIRU          FIO3DIR_bit.__shortu
#define FIO3DIRU_bit      FIO3DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO3MASK,        0x3FFFC070,__READ_WRITE,__fgpio3_bits);
#define FIO3MASK0         FIO3MASK_bit.__byte0
#define FIO3MASK0_bit     FIO3MASK_bit.__byte0_bit
#define FIO3MASK1         FIO3MASK_bit.__byte1
#define FIO3MASK1_bit     FIO3MASK_bit.__byte1_bit
#define FIO3MASK2         FIO3MASK_bit.__byte2
#define FIO3MASK2_bit     FIO3MASK_bit.__byte2_bit
#define FIO3MASK3         FIO3MASK_bit.__byte3
#define FIO3MASK3_bit     FIO3MASK_bit.__byte3_bit
#define FIO3MASKL         FIO3MASK_bit.__shortl
#define FIO3MASKL_bit     FIO3MASK_bit.__shortl_bit
#define FIO3MASKU         FIO3MASK_bit.__shortu
#define FIO3MASKU_bit     FIO3MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO3PIN,         0x3FFFC074,__READ_WRITE,__fgpio3_bits);
#define FIO3PIN0          FIO3PIN_bit.__byte0
#define FIO3PIN0_bit      FIO3PIN_bit.__byte0_bit
#define FIO3PIN1          FIO3PIN_bit.__byte1
#define FIO3PIN1_bit      FIO3PIN_bit.__byte1_bit
#define FIO3PIN2          FIO3PIN_bit.__byte2
#define FIO3PIN2_bit      FIO3PIN_bit.__byte2_bit
#define FIO3PIN3          FIO3PIN_bit.__byte3
#define FIO3PIN3_bit      FIO3PIN_bit.__byte3_bit
#define FIO3PINL          FIO3PIN_bit.__shortl
#define FIO3PINL_bit      FIO3PIN_bit.__shortl_bit
#define FIO3PINU          FIO3PIN_bit.__shortu
#define FIO3PINU_bit      FIO3PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO3SET,         0x3FFFC078,__READ_WRITE,__fgpio3_bits);
#define FIO3SET0          FIO3SET_bit.__byte0
#define FIO3SET0_bit      FIO3SET_bit.__byte0_bit
#define FIO3SET1          FIO3SET_bit.__byte1
#define FIO3SET1_bit      FIO3SET_bit.__byte1_bit
#define FIO3SET2          FIO3SET_bit.__byte2
#define FIO3SET2_bit      FIO3SET_bit.__byte2_bit
#define FIO3SET3          FIO3SET_bit.__byte3
#define FIO3SET3_bit      FIO3SET_bit.__byte3_bit
#define FIO3SETL          FIO3SET_bit.__shortl
#define FIO3SETL_bit      FIO3SET_bit.__shortl_bit
#define FIO3SETU          FIO3SET_bit.__shortu
#define FIO3SETU_bit      FIO3SET_bit.__shortu_bit
__IO_REG32_BIT(FIO3CLR,         0x3FFFC07C,__WRITE     ,__fgpio3_bits);
#define FIO3CLR0          FIO3CLR_bit.__byte0
#define FIO3CLR0_bit      FIO3CLR_bit.__byte0_bit
#define FIO3CLR1          FIO3CLR_bit.__byte1
#define FIO3CLR1_bit      FIO3CLR_bit.__byte1_bit
#define FIO3CLR2          FIO3CLR_bit.__byte2
#define FIO3CLR2_bit      FIO3CLR_bit.__byte2_bit
#define FIO3CLR3          FIO3CLR_bit.__byte3
#define FIO3CLR3_bit      FIO3CLR_bit.__byte3_bit
#define FIO3CLRL          FIO3CLR_bit.__shortl
#define FIO3CLRL_bit      FIO3CLR_bit.__shortl_bit
#define FIO3CLRU          FIO3CLR_bit.__shortu
#define FIO3CLRU_bit      FIO3CLR_bit.__shortu_bit
__IO_REG32_BIT(FIO4DIR,         0x3FFFC080,__READ_WRITE,__fgpio4_bits);
#define FIO4DIR0          FIO4DIR_bit.__byte0
#define FIO4DIR0_bit      FIO4DIR_bit.__byte0_bit
#define FIO4DIR1          FIO4DIR_bit.__byte1
#define FIO4DIR1_bit      FIO4DIR_bit.__byte1_bit
#define FIO4DIR2          FIO4DIR_bit.__byte2
#define FIO4DIR2_bit      FIO4DIR_bit.__byte2_bit
#define FIO4DIR3          FIO4DIR_bit.__byte3
#define FIO4DIR3_bit      FIO4DIR_bit.__byte3_bit
#define FIO4DIRL          FIO4DIR_bit.__shortl
#define FIO4DIRL_bit      FIO4DIR_bit.__shortl_bit
#define FIO4DIRU          FIO4DIR_bit.__shortu
#define FIO4DIRU_bit      FIO4DIR_bit.__shortu_bit
__IO_REG32_BIT(FIO4MASK,        0x3FFFC090,__READ_WRITE,__fgpio4_bits);
#define FIO4MASK0         FIO4MASK_bit.__byte0
#define FIO4MASK0_bit     FIO4MASK_bit.__byte0_bit
#define FIO4MASK1         FIO4MASK_bit.__byte1
#define FIO4MASK1_bit     FIO4MASK_bit.__byte1_bit
#define FIO4MASK2         FIO4MASK_bit.__byte2
#define FIO4MASK2_bit     FIO4MASK_bit.__byte2_bit
#define FIO4MASK3         FIO4MASK_bit.__byte3
#define FIO4MASK3_bit     FIO4MASK_bit.__byte3_bit
#define FIO4MASKL         FIO4MASK_bit.__shortl
#define FIO4MASKL_bit     FIO4MASK_bit.__shortl_bit
#define FIO4MASKU         FIO4MASK_bit.__shortu
#define FIO4MASKU_bit     FIO4MASK_bit.__shortu_bit
__IO_REG32_BIT(FIO4PIN,         0x3FFFC094,__READ_WRITE,__fgpio4_bits);
#define FIO4PIN0          FIO4PIN_bit.__byte0
#define FIO4PIN0_bit      FIO4PIN_bit.__byte0_bit
#define FIO4PIN1          FIO4PIN_bit.__byte1
#define FIO4PIN1_bit      FIO4PIN_bit.__byte1_bit
#define FIO4PIN2          FIO4PIN_bit.__byte2
#define FIO4PIN2_bit      FIO4PIN_bit.__byte2_bit
#define FIO4PIN3          FIO4PIN_bit.__byte3
#define FIO4PIN3_bit      FIO4PIN_bit.__byte3_bit
#define FIO4PINL          FIO4PIN_bit.__shortl
#define FIO4PINL_bit      FIO4PIN_bit.__shortl_bit
#define FIO4PINU          FIO4PIN_bit.__shortu
#define FIO4PINU_bit      FIO4PIN_bit.__shortu_bit
__IO_REG32_BIT(FIO4SET,         0x3FFFC098,__READ_WRITE,__fgpio4_bits);
#define FIO4SET0          FIO4SET_bit.__byte0
#define FIO4SET0_bit      FIO4SET_bit.__byte0_bit
#define FIO4SET1          FIO4SET_bit.__byte1
#define FIO4SET1_bit      FIO4SET_bit.__byte1_bit
#define FIO4SET2          FIO4SET_bit.__byte2
#define FIO4SET2_bit      FIO4SET_bit.__byte2_bit
#define FIO4SET3          FIO4SET_bit.__byte3
#define FIO4SET3_bit      FIO4SET_bit.__byte3_bit
#define FIO4SETL          FIO4SET_bit.__shortl
#define FIO4SETL_bit      FIO4SET_bit.__shortl_bit
#define FIO4SETU          FIO4SET_bit.__shortu
#define FIO4SETU_bit      FIO4SET_bit.__shortu_bit
__IO_REG32_BIT(FIO4CLR,         0x3FFFC09C,__WRITE     ,__fgpio4_bits);
#define FIO4CLR0          FIO4CLR_bit.__byte0
#define FIO4CLR0_bit      FIO4CLR_bit.__byte0_bit
#define FIO4CLR1          FIO4CLR_bit.__byte1
#define FIO4CLR1_bit      FIO4CLR_bit.__byte1_bit
#define FIO4CLR2          FIO4CLR_bit.__byte2
#define FIO4CLR2_bit      FIO4CLR_bit.__byte2_bit
#define FIO4CLR3          FIO4CLR_bit.__byte3
#define FIO4CLR3_bit      FIO4CLR_bit.__byte3_bit
#define FIO4CLRL          FIO4CLR_bit.__shortl
#define FIO4CLRL_bit      FIO4CLR_bit.__shortl_bit
#define FIO4CLRU          FIO4CLR_bit.__shortu
#define FIO4CLRU_bit      FIO4CLR_bit.__shortu_bit
__IO_REG32_BIT(IO0INTENR,             0xE0028090,__READ_WRITE ,__gpio0_bits);
__IO_REG32_BIT(IO0INTENF,             0xE0028094,__READ_WRITE ,__gpio0_bits);
__IO_REG32_BIT(IO0INTSTATR,           0xE0028084,__READ       ,__gpio0_bits);
__IO_REG32_BIT(IO0INTSTATF,           0xE0028088,__READ       ,__gpio0_bits);
__IO_REG32_BIT(IO0INTCLR,             0xE002808C,__WRITE      ,__gpio0_bits);
__IO_REG32_BIT(IO1INTENR,             0xE00280B0,__READ_WRITE ,__gpio1_bits);
__IO_REG32_BIT(IO1INTENF,             0xE00280B4,__READ_WRITE ,__gpio1_bits);
__IO_REG32_BIT(IO1INTSTATR,           0xE00280A4,__READ       ,__gpio1_bits);
__IO_REG32_BIT(IO1INTSTATF,           0xE00280A8,__READ       ,__gpio1_bits);
__IO_REG32_BIT(IO1INTCLR,             0xE00280AC,__WRITE      ,__gpio1_bits);
__IO_REG32_BIT(IOINTSTATUS,           0xE0028080,__READ       ,__iointst_bits);

/***************************************************************************
 **
 **  ETHERNET
 **
 ***************************************************************************/
__IO_REG32_BIT(MAC1,                  0xFFE00000,__READ_WRITE ,__mac1_bits);
__IO_REG32_BIT(MAC2,                  0xFFE00004,__READ_WRITE ,__mac2_bits);
__IO_REG32_BIT(IPGT,                  0xFFE00008,__READ_WRITE ,__ipgt_bits);
__IO_REG32_BIT(IPGR,                  0xFFE0000C,__READ_WRITE ,__ipgr_bits);
__IO_REG32_BIT(CLRT,                  0xFFE00010,__READ_WRITE ,__clrt_bits);
__IO_REG32_BIT(MAXF,                  0xFFE00014,__READ_WRITE ,__maxf_bits);
__IO_REG32_BIT(SUPP,                  0xFFE00018,__READ_WRITE ,__supp_bits);
__IO_REG32_BIT(TEST,                  0xFFE0001C,__READ_WRITE ,__test_bits);
__IO_REG32_BIT(MCFG,                  0xFFE00020,__READ_WRITE ,__mcfg_bits);
__IO_REG32_BIT(MCMD,                  0xFFE00024,__READ_WRITE ,__mcmd_bits);
__IO_REG32_BIT(MADR,                  0xFFE00028,__READ_WRITE ,__madr_bits);
__IO_REG32_BIT(MWTD,                  0xFFE0002C,__WRITE      ,__mwtd_bits);
__IO_REG32_BIT(MRDD,                  0xFFE00030,__READ       ,__mrdd_bits);
__IO_REG32_BIT(MIND,                  0xFFE00034,__READ       ,__mind_bits);
__IO_REG32_BIT(SA0,                   0xFFE00040,__READ_WRITE ,__sa0_bits);
__IO_REG32_BIT(SA1,                   0xFFE00044,__READ_WRITE ,__sa1_bits);
__IO_REG32_BIT(SA2,                   0xFFE00048,__READ_WRITE ,__sa2_bits);
__IO_REG32_BIT(COMMAND,               0xFFE00100,__READ_WRITE ,__command_bits);
__IO_REG32_BIT(STATUS,                0xFFE00104,__READ       ,__status_bits);
__IO_REG32(    RXDESCRIPTOR,          0xFFE00108,__READ_WRITE );
__IO_REG32(    RXSTATUS,              0xFFE0010C,__READ_WRITE );
__IO_REG32_BIT(RXDESCRIPTORNUMBER,    0xFFE00110,__READ_WRITE ,__rxdescrn_bits);
__IO_REG32_BIT(RXPRODUCEINDEX,        0xFFE00114,__READ       ,__rxprodind_bits);
__IO_REG32_BIT(RXCONSUMEINDEX,        0xFFE00118,__READ_WRITE ,__rxcomind_bits);
__IO_REG32(    TXDESCRIPTOR,          0xFFE0011C,__READ_WRITE );
__IO_REG32(    TXSTATUS,              0xFFE00120,__READ_WRITE );
__IO_REG32_BIT(TXDESCRIPTORNUMBER,    0xFFE00124,__READ_WRITE ,__txdescrn_bits);
__IO_REG32_BIT(TXPRODUCEINDEX,        0xFFE00128,__READ_WRITE ,__txprodind_bits);
__IO_REG32_BIT(TXCONSUMEINDEX,        0xFFE0012C,__READ       ,__txcomind_bits);
__IO_REG32_BIT(TSV0,                  0xFFE00158,__READ       ,__tsv0_bits);
__IO_REG32_BIT(TSV1,                  0xFFE0015C,__READ       ,__tsv1_bits);
__IO_REG32_BIT(RSV,                   0xFFE00160,__READ       ,__rsv_bits);
__IO_REG32_BIT(FLOWCONTROLCOUNTER,    0xFFE00170,__READ_WRITE ,__fwctrlcnt_bits);
__IO_REG32_BIT(FLOWCONTROLSTATUS,     0xFFE00174,__READ       ,__fwctrlstat_bits);
__IO_REG32_BIT(RXFILTERCTRL,          0xFFE00200,__READ_WRITE ,__rxflctrl_bits);
__IO_REG32_BIT(RXFILTERWOLSTATUS,     0xFFE00204,__READ_WRITE ,__rxflwolstat_bits);
__IO_REG32_BIT(RXFILTERWOLCLEAR,      0xFFE00208,__READ_WRITE ,__rxflwolclr_bits);
__IO_REG32(    HASHFILTERL,           0xFFE00210,__READ_WRITE );
__IO_REG32(    HASHFILTERH,           0xFFE00214,__READ_WRITE );
__IO_REG32_BIT(INTSTATUS,             0xFFE00FE0,__READ       ,__intstat_bits);
__IO_REG32_BIT(INTENABLE,             0xFFE00FE4,__READ_WRITE ,__intena_bits);
__IO_REG32_BIT(INTCLEAR,              0xFFE00FE8,__WRITE      ,__intclr_bits);
__IO_REG32_BIT(INTSET,                0xFFE00FEC,__WRITE      ,__intset_bits);
__IO_REG32_BIT(POWERDOWN,             0xFFE00FF4,__READ_WRITE ,__pwrdn_bits);

/***************************************************************************
 **
 ** USB
 **
 ***************************************************************************/
__IO_REG32_BIT(USBPORTSEL,            0xFFE0C110,__READ_WRITE ,__usbportsel_bits);
__IO_REG32_BIT(USBCLKCTRL,            0xFFE0CFF4,__READ_WRITE ,__usbclkctrl_bits);
__IO_REG32_BIT(USBCLKST,              0xFFE0CFF8,__READ       ,__usbclkctrl_bits);
__IO_REG32_BIT(USBINTS,               0xE01FC1C0,__READ_WRITE ,__usbints_bits);
__IO_REG32_BIT(USBDEVINTST,           0xFFE0C200,__READ       ,__usbdevintst_bits);
__IO_REG32_BIT(USBDEVINTEN,           0xFFE0C204,__READ_WRITE ,__usbdevintst_bits);
__IO_REG32_BIT(USBDEVINTCLR,          0xFFE0C208,__WRITE      ,__usbdevintst_bits);
__IO_REG32_BIT(USBDEVINTSET,          0xFFE0C20C,__WRITE      ,__usbdevintst_bits);
__IO_REG8_BIT( USBDEVINTPRI,          0xFFE0C22C,__WRITE      ,__usbdevintpri_bits);
__IO_REG32_BIT(USBEPINTST,            0xFFE0C230,__READ       ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTEN,            0xFFE0C234,__READ_WRITE ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTCLR,           0xFFE0C238,__WRITE      ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTSET,           0xFFE0C23C,__WRITE      ,__usbepintst_bits);
__IO_REG32_BIT(USBEPINTPRI,           0xFFE0C240,__WRITE      ,__usbepintst_bits);
__IO_REG32_BIT(USBREEP,               0xFFE0C244,__READ_WRITE ,__usbreep_bits);
__IO_REG32_BIT(USBEPIN,               0xFFE0C248,__WRITE      ,__usbepin_bits);
__IO_REG32_BIT(USBMAXPSIZE,           0xFFE0C24C,__READ_WRITE ,__usbmaxpsize_bits);
__IO_REG32(    USBRXDATA,             0xFFE0C218,__READ);
__IO_REG32_BIT(USBRXPLEN,             0xFFE0C220,__READ       ,__usbrxplen_bits);
__IO_REG32(    TDATA,                 0xFFE0C21C,__WRITE);
__IO_REG32_BIT(USBTXPLEN,             0xFFE0C224,__WRITE      ,__usbtxplen_bits);
__IO_REG32_BIT(USBCTRL,               0xFFE0C228,__READ_WRITE ,__usbctrl_bits);
__IO_REG32_BIT(USBCMDCODE,            0xFFE0C210,__WRITE      ,__usbcmdcode_bits);
__IO_REG32_BIT(USBCMDDATA,            0xFFE0C214,__READ       ,__usbcmddata_bits);
__IO_REG32_BIT(USBDMARST,             0xFFE0C250,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBDMARCLR,            0xFFE0C254,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBDMARSET,            0xFFE0C258,__WRITE      ,__usbreep_bits);
__IO_REG32(    USBUDCAH,              0xFFE0C280,__READ_WRITE );
__IO_REG32_BIT(USBEPDMAST,            0xFFE0C284,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBEPDMAEN,            0xFFE0C288,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBEPDMADIS,           0xFFE0C28C,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBDMAINTST,           0xFFE0C290,__READ       ,__usbdmaintst_bits);
__IO_REG32_BIT(USBDMAINTEN,           0xFFE0C294,__READ_WRITE ,__usbdmaintst_bits);
__IO_REG32_BIT(USBNDDRINTST,          0xFFE0C2AC,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBNDDRINTCLR,         0xFFE0C2B0,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBNDDRINTSET,         0xFFE0C2B4,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBEOTINTST,           0xFFE0C2A0,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBEOTINTCLR,          0xFFE0C2A4,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBEOTINTSET,          0xFFE0C2A8,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBSYSERRINTST,        0xFFE0C2B8,__READ       ,__usbreep_bits);
__IO_REG32_BIT(USBSYSERRINTCLR,       0xFFE0C2BC,__WRITE      ,__usbreep_bits);
__IO_REG32_BIT(USBSYSERRINTSET,       0xFFE0C2C0,__WRITE      ,__usbreep_bits);

/***************************************************************************
 **
 ** CAN
 **
 ***************************************************************************/
__IO_REG32_BIT(AFMR,                  0xE003C000,__READ_WRITE ,__afmr_bits);
__IO_REG32(    SFF_SA,                0xE003C004,__READ_WRITE);
__IO_REG32(    SFF_GRP_SA,            0xE003C008,__READ_WRITE);
__IO_REG32(    EFF_SA,                0xE003C00C,__READ_WRITE);
__IO_REG32(    EFF_GRP_SA,            0xE003C010,__READ_WRITE);
__IO_REG32(    ENDOFTABLE,            0xE003C014,__READ_WRITE);
__IO_REG32(    LUTERRAD,              0xE003C018,__READ);
__IO_REG32(    LUTERR,                0xE003C01C,__READ);
__IO_REG32_BIT(FCANIE,                0xE003C020,__READ_WRITE ,__fcanie_bits);
__IO_REG32_BIT(FCANIC0,               0xE003C024,__READ_WRITE ,__fcanic0_bits);
__IO_REG32_BIT(FCANIC1,               0xE003C028,__READ_WRITE ,__fcanic1_bits);
__IO_REG32_BIT(CANTXSR,               0xE0040000,__READ       ,__cantxsr_bits);
__IO_REG32_BIT(CANRXSR,               0xE0040004,__READ       ,__canrxsr_bits);
__IO_REG32_BIT(CANMSR,                0xE0040008,__READ       ,__canmsr_bits);
__IO_REG32_BIT(CAN1MOD,               0xE0044000,__READ_WRITE ,__canmod_bits);
__IO_REG32_BIT(CAN1CMR,               0xE0044004,__WRITE      ,__cancmr_bits);
__IO_REG32_BIT(CAN1GSR,               0xE0044008,__READ_WRITE ,__cangsr_bits);
__IO_REG32_BIT(CAN1ICR,               0xE004400C,__READ       ,__canicr_bits);
__IO_REG32_BIT(CAN1IER,               0xE0044010,__READ_WRITE ,__canier_bits);
__IO_REG32_BIT(CAN1BTR,               0xE0044014,__READ_WRITE ,__canbtr_bits);
__IO_REG32_BIT(CAN1EWL,               0xE0044018,__READ_WRITE ,__canewl_bits);
__IO_REG32_BIT(CAN1SR,                0xE004401C,__READ       ,__cansr_bits);
__IO_REG32_BIT(CAN1RFS,               0xE0044020,__READ_WRITE ,__canrfs_bits);
__IO_REG32_BIT(CAN1RID,               0xE0044024,__READ_WRITE ,__canrid_bits);
__IO_REG32_BIT(CAN1RDA,               0xE0044028,__READ_WRITE ,__canrda_bits);
__IO_REG32_BIT(CAN1RDB,               0xE004402C,__READ_WRITE ,__canrdb_bits);
__IO_REG32_BIT(CAN1TFI1,              0xE0044030,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN1TID1,              0xE0044034,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN1TDA1,              0xE0044038,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN1TDB1,              0xE004403C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN1TFI2,              0xE0044040,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN1TID2,              0xE0044044,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN1TDA2,              0xE0044048,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN1TDB2,              0xE004404C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN1TFI3,              0xE0044050,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN1TID3,              0xE0044054,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN1TDA3,              0xE0044058,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN1TDB3,              0xE004405C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN2MOD,               0xE0048000,__READ_WRITE ,__canmod_bits);
__IO_REG32_BIT(CAN2CMR,               0xE0048004,__WRITE      ,__cancmr_bits);
__IO_REG32_BIT(CAN2GSR,               0xE0048008,__READ_WRITE ,__cangsr_bits);
__IO_REG32_BIT(CAN2ICR,               0xE004800C,__READ       ,__canicr_bits);
__IO_REG32_BIT(CAN2IER,               0xE0048010,__READ_WRITE ,__canier_bits);
__IO_REG32_BIT(CAN2BTR,               0xE0048014,__READ_WRITE ,__canbtr_bits);
__IO_REG32_BIT(CAN2EWL,               0xE0048018,__READ_WRITE ,__canewl_bits);
__IO_REG32_BIT(CAN2SR,                0xE004801C,__READ       ,__cansr_bits);
__IO_REG32_BIT(CAN2RFS,               0xE0048020,__READ_WRITE ,__canrfs_bits);
__IO_REG32_BIT(CAN2RID,               0xE0048024,__READ_WRITE ,__canrid_bits);
__IO_REG32_BIT(CAN2RDA,               0xE0048028,__READ_WRITE ,__canrda_bits);
__IO_REG32_BIT(CAN2RDB,               0xE004802C,__READ_WRITE ,__canrdb_bits);
__IO_REG32_BIT(CAN2TFI1,              0xE0048030,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN2TID1,              0xE0048034,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN2TDA1,              0xE0048038,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN2TDB1,              0xE004803C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN2TFI2,              0xE0048040,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN2TID2,              0xE0048044,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN2TDA2,              0xE0048048,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN2TDB2,              0xE004804C,__READ_WRITE ,__cantdb_bits);
__IO_REG32_BIT(CAN2TFI3,              0xE0048050,__READ_WRITE ,__cantfi_bits);
__IO_REG32_BIT(CAN2TID3,              0xE0048054,__READ_WRITE ,__cantid_bits);
__IO_REG32_BIT(CAN2TDA3,              0xE0048058,__READ_WRITE ,__cantda_bits);
__IO_REG32_BIT(CAN2TDB3,              0xE004805C,__READ_WRITE ,__cantdb_bits);

/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/
/* U0DLL, U0RBR and U0THR share the same address */
__IO_REG8(     U0RBRTHR,              0xE000C000,__READ_WRITE);
#define U0DLL U0RBRTHR
#define U0RBR U0RBRTHR
#define U0THR U0RBRTHR

/* U0DLM and U0IER share the same address */
__IO_REG32_BIT(U0IER,                 0xE000C004,__READ_WRITE ,__uartier0_bits);
#define U0DLM      U0IER

/* U0FCR and U0IIR share the same address */
__IO_REG32_BIT(U0FCR,                 0xE000C008,__READ_WRITE ,__uartfcriir_bits);
#define U0IIR      U0FCR
#define U0IIR_bit  U0FCR_bit

__IO_REG8_BIT( U0LCR,                 0xE000C00C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U0LSR,                 0xE000C014,__READ       ,__uartlsr_bits);
__IO_REG8(     U0SCR,                 0xE000C01C,__READ_WRITE);
__IO_REG32_BIT(U0ACR,                 0xE000C020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U0FDR,                 0xE000C028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U0TER,                 0xE000C030,__READ_WRITE ,__uartter_bits);

/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
/* U1DLL, U1RBR and U1THR share the same address */
__IO_REG8(     U1RBRTHR,              0xE0010000,__READ_WRITE);
#define U1DLL U1RBRTHR
#define U1RBR U1RBRTHR
#define U1THR U1RBRTHR

/* U1DLM and U1IER share the same address */
__IO_REG32_BIT(U1IER,                 0xE0010004,__READ_WRITE ,__uartier1_bits);
#define U1DLM      U1IER

/* U1FCR and U1IIR share the same address */
__IO_REG32_BIT(U1FCR,                 0xE0010008,__READ_WRITE ,__uartfcriir_bits);
#define U1IIR      U1FCR
#define U1IIR_bit  U1FCR_bit

__IO_REG8_BIT( U1LCR,                 0xE001000C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U1MCR,                 0xE0010010,__READ_WRITE ,__uartmcr_bits);
__IO_REG8_BIT( U1LSR,                 0xE0010014,__READ       ,__uartlsr_bits);
__IO_REG8_BIT( U1MSR,                 0xE0010018,__READ       ,__uartmsr_bits);
__IO_REG8(     U1SCR,                 0xE001001C,__READ_WRITE);
__IO_REG32_BIT(U1ACR,                 0xE0010020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U1FDR,                 0xE0010028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U1TER,                 0xE0010030,__READ_WRITE ,__uartter_bits);

/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
/* U2DLL, U2RBR and U2THR share the same address */
__IO_REG8(     U2RBRTHR,              0xE0078000,__READ_WRITE);
#define U2DLL U2RBRTHR
#define U2RBR U2RBRTHR
#define U2THR U2RBRTHR

/* U2DLM and U2IER share the same address */
__IO_REG32_BIT(U2IER,                 0xE0078004,__READ_WRITE ,__uartier0_bits);
#define U2DLM      U2IER

/* U2FCR and U2IIR share the same address */
__IO_REG32_BIT(U2FCR,                 0xE0078008,__READ_WRITE ,__uartfcriir_bits);
#define U2IIR      U2FCR
#define U2IIR_bit  U2FCR_bit

__IO_REG8_BIT( U2LCR,                 0xE007800C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U2LSR,                 0xE0078014,__READ       ,__uartlsr_bits);
__IO_REG8(     U2SCR,                 0xE007801C,__READ_WRITE);
__IO_REG32_BIT(U2ACR,                 0xE0078020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U2FDR,                 0xE0078028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U2TER,                 0xE0078030,__READ_WRITE ,__uartter_bits);

/***************************************************************************
 **
 **  UART3
 **
 ***************************************************************************/
/* U3DLL, U3RBR and U3THR share the same address */
__IO_REG8(     U3RBRTHR,              0xE007C000,__READ_WRITE);
#define U3DLL U3RBRTHR
#define U3RBR U3RBRTHR
#define U3THR U3RBRTHR

/* U3DLM and U3IER share the same address */
__IO_REG32_BIT(U3IER,                 0xE007C004,__READ_WRITE ,__uartier0_bits);
#define U3DLM      U3IER

/* U3FCR and U3IIR share the same address */
__IO_REG32_BIT(U3FCR,                 0xE007C008,__READ_WRITE ,__uartfcriir_bits);
#define U3IIR      U3FCR
#define U3IIR_bit  U3FCR_bit

__IO_REG8_BIT( U3LCR,                 0xE007C00C,__READ_WRITE ,__uartlcr_bits);
__IO_REG8_BIT( U3LSR,                 0xE007C014,__READ       ,__uartlsr_bits);
__IO_REG8(     U3SCR,                 0xE007C01C,__READ_WRITE);
__IO_REG32_BIT(U3ACR,                 0xE007C020,__READ_WRITE ,__uartacr_bits);
__IO_REG32_BIT(U3ICR,                 0xE007C024,__READ_WRITE ,__uarticr_bits);
__IO_REG32_BIT(U3FDR,                 0xE007C028,__READ_WRITE ,__uartfdr_bits);
__IO_REG8_BIT( U3TER,                 0xE007C030,__READ_WRITE ,__uartter_bits);

/***************************************************************************
 **
 ** SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(S0SPCR,                0xE0020000,__READ_WRITE ,__spcr_bits);
__IO_REG32_BIT(S0SPSR,                0xE0020004,__READ       ,__spsr_bits);
__IO_REG16(    S0SPDR,                0xE0020008,__READ_WRITE);
__IO_REG32_BIT(S0SPCCR,               0xE002000C,__READ_WRITE ,__spccr_bits);
__IO_REG8_BIT( SPTCR,                 0xE0020010,__READ_WRITE ,__sptcr_bits);
__IO_REG8_BIT( SPTSR,                 0xE0020014,__READ_WRITE ,__sptsr_bits);
__IO_REG32_BIT(S0SPINT,               0xE002001C,__READ_WRITE ,__spint_bits);

/***************************************************************************
 **
 ** SSP0
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP0CR0,               0xE0068000,__READ_WRITE ,__sspcr0_bits);
__IO_REG32_BIT(SSP0CR1,               0xE0068004,__READ_WRITE ,__sspcr1_bits);
__IO_REG32_BIT(SSP0DR,                0xE0068008,__READ_WRITE ,__sspdr_bits);
__IO_REG32_BIT(SSP0SR,                0xE006800C,__READ       ,__sspsr_bits);
__IO_REG32_BIT(SSP0CPSR,              0xE0068010,__READ_WRITE ,__sspcpsr_bits);
__IO_REG32_BIT(SSP0IMSC,              0xE0068014,__READ_WRITE ,__sspimsc_bits);
__IO_REG32_BIT(SSP0RIS,               0xE0068018,__READ_WRITE ,__sspris_bits);
__IO_REG32_BIT(SSP0MIS,               0xE006801C,__READ_WRITE ,__sspmis_bits);
__IO_REG32_BIT(SSP0ICR,               0xE0068020,__READ_WRITE ,__sspicr_bits);
__IO_REG32_BIT(SSP0DMACR,             0xE0068024,__READ_WRITE ,__sspdmacr_bits);

/***************************************************************************
 **
 ** SSP1
 **
 ***************************************************************************/
__IO_REG32_BIT(SSP1CR0,               0xE0030000,__READ_WRITE ,__sspcr0_bits);
__IO_REG32_BIT(SSP1CR1,               0xE0030004,__READ_WRITE ,__sspcr1_bits);
__IO_REG32_BIT(SSP1DR,                0xE0030008,__READ_WRITE ,__sspdr_bits);
__IO_REG32_BIT(SSP1SR,                0xE003000C,__READ       ,__sspsr_bits);
__IO_REG32_BIT(SSP1CPSR,              0xE0030010,__READ_WRITE ,__sspcpsr_bits);
__IO_REG32_BIT(SSP1IMSC,              0xE0030014,__READ_WRITE ,__sspimsc_bits);
__IO_REG32_BIT(SSP1RIS,               0xE0030018,__READ_WRITE ,__sspris_bits);
__IO_REG32_BIT(SSP1MIS,               0xE003001C,__READ_WRITE ,__sspmis_bits);
__IO_REG32_BIT(SSP1ICR,               0xE0030020,__READ_WRITE ,__sspicr_bits);
__IO_REG32_BIT(SSP1DMACR,             0xE0030024,__READ_WRITE ,__sspdmacr_bits);

/***************************************************************************
 **
 ** SD/MMC
 **
 ***************************************************************************/
__IO_REG32_BIT(MCIPOWER,              0xE008C000,__READ_WRITE ,__mcipower_bits);
__IO_REG32_BIT(MCICLOCK,              0xE008C004,__READ_WRITE ,__mciclock_bits);
__IO_REG32(    MCIARGUMENT,           0xE008C008,__READ_WRITE);
__IO_REG32_BIT(MCICOMMAND,            0xE008C00C,__READ_WRITE ,__mcicommand_bits);
__IO_REG32_BIT(MCIRESPCMD,            0xE008C010,__READ       ,__mcirespcmd_bits);
__IO_REG32(    MCIRESPONSE0,          0xE008C014,__READ);
__IO_REG32(    MCIRESPONSE1,          0xE008C018,__READ);
__IO_REG32(    MCIRESPONSE2,          0xE008C01C,__READ);
__IO_REG32(    MCIRESPONSE3,          0xE008C020,__READ);
__IO_REG32(    MCIDATATIMER,          0xE008C024,__READ_WRITE);
__IO_REG16(    MCIDATALENGTH,         0xE008C028,__READ_WRITE);
__IO_REG32_BIT(MCIDATACTRL,           0xE008C02C,__READ_WRITE ,__mcidatactrl_bits);
__IO_REG16(    MCIDATACNT,            0xE008C030,__READ);
__IO_REG32_BIT(MCISTATUS,             0xE008C034,__READ       ,__mcistatus_bits);
__IO_REG32_BIT(MCICLEAR,              0xE008C038,__WRITE      ,__mciclear_bits);
__IO_REG32_BIT(MCIMASK0,              0xE008C03C,__READ_WRITE ,__mcistatus_bits);
__IO_REG32_BIT(MCIMASK1,              0xE008C040,__READ_WRITE ,__mcistatus_bits);
__IO_REG32_BIT(MCIFIFOCNT,            0xE008C048,__READ       ,__mcififocnt_bits);
__IO_REG32(    MCIFIFO0,              0xE008C080,__READ_WRITE);
__IO_REG32(    MCIFIFO1,              0xE008C084,__READ_WRITE);
__IO_REG32(    MCIFIFO2,              0xE008C088,__READ_WRITE);
__IO_REG32(    MCIFIFO3,              0xE008C08C,__READ_WRITE);
__IO_REG32(    MCIFIFO4,              0xE008C090,__READ_WRITE);
__IO_REG32(    MCIFIFO5,              0xE008C094,__READ_WRITE);
__IO_REG32(    MCIFIFO6,              0xE008C098,__READ_WRITE);
__IO_REG32(    MCIFIFO7,              0xE008C09C,__READ_WRITE);
__IO_REG32(    MCIFIFO8,              0xE008C0A0,__READ_WRITE);
__IO_REG32(    MCIFIFO9,              0xE008C0A4,__READ_WRITE);
__IO_REG32(    MCIFIFO10,             0xE008C0A8,__READ_WRITE);
__IO_REG32(    MCIFIFO11,             0xE008C0AC,__READ_WRITE);
__IO_REG32(    MCIFIFO12,             0xE008C0B0,__READ_WRITE);
__IO_REG32(    MCIFIFO13,             0xE008C0B4,__READ_WRITE);
__IO_REG32(    MCIFIFO14,             0xE008C0B8,__READ_WRITE);
__IO_REG32(    MCIFIFO15,             0xE008C0BC,__READ_WRITE);

/***************************************************************************
 **
 ** I2C0
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C0CONSET,            0xE001C000,__READ_WRITE ,__i2conset_bits);
__IO_REG32_BIT(I2C0STAT,              0xE001C004,__READ       ,__i2stat_bits);
__IO_REG32_BIT(I2C0DAT,               0xE001C008,__READ_WRITE ,__i2dat_bits);
__IO_REG32_BIT(I2C0ADR,               0xE001C00C,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C0SCLH,              0xE001C010,__READ_WRITE ,__i2sch_bits);
__IO_REG32_BIT(I2C0SCLL,              0xE001C014,__READ_WRITE ,__i2scl_bits);
__IO_REG32_BIT(I2C0CONCLR,            0xE001C018,__WRITE      ,__i2conclr_bits);

//The names of the registers above have been corrected according to the chip
//documentation. The defines below are aliases with the old names for backwards
//compatibility.
#define I20CONSET I2C0CONSET
#define I20STAT   I2C0STAT
#define I20DAT    I2C0DAT
#define I20ADR    I2C0ADR
#define I20SCLH   I2C0SCLH
#define I20SCLL   I2C0SCLL
#define I20CONCLR I2C0CONCLR

/***************************************************************************
 **
 ** I2C1
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C1CONSET,            0xE005C000,__READ_WRITE ,__i2conset_bits);
__IO_REG32_BIT(I2C1STAT,              0xE005C004,__READ       ,__i2stat_bits);
__IO_REG32_BIT(I2C1DAT,               0xE005C008,__READ_WRITE ,__i2dat_bits);
__IO_REG32_BIT(I2C1ADR,               0xE005C00C,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C1SCLH,              0xE005C010,__READ_WRITE ,__i2sch_bits);
__IO_REG32_BIT(I2C1SCLL,              0xE005C014,__READ_WRITE ,__i2scl_bits);
__IO_REG32_BIT(I2C1CONCLR,            0xE005C018,__WRITE      ,__i2conclr_bits);

//The names of the registers above have been corrected according to the chip
//documentation. The defines below are aliases with the old names for backwards
//compatibility.
#define I21CONSET I2C1CONSET
#define I21STAT   I2C1STAT
#define I21DAT    I2C1DAT
#define I21ADR    I2C1ADR
#define I21SCLH   I2C1SCLH
#define I21SCLL   I2C1SCLL
#define I21CONCLR I2C1CONCLR

/***************************************************************************
 **
 ** I2C2
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C2CONSET,            0xE0080000,__READ_WRITE ,__i2conset_bits);
__IO_REG32_BIT(I2C2STAT,              0xE0080004,__READ       ,__i2stat_bits);
__IO_REG32_BIT(I2C2DAT,               0xE0080008,__READ_WRITE ,__i2dat_bits);
__IO_REG32_BIT(I2C2ADR,               0xE008000C,__READ_WRITE ,__i2adr_bits);
__IO_REG32_BIT(I2C2SCLH,              0xE0080010,__READ_WRITE ,__i2sch_bits);
__IO_REG32_BIT(I2C2SCLL,              0xE0080014,__READ_WRITE ,__i2scl_bits);
__IO_REG32_BIT(I2C2CONCLR,            0xE0080018,__WRITE      ,__i2conclr_bits);

/***************************************************************************
 **
 ** I2S
 **
 ***************************************************************************/
__IO_REG32_BIT(I2SDAO,                0xE0088000,__READ_WRITE ,__i2sdao_bits);
__IO_REG32_BIT(I2SDAI,                0xE0088004,__READ_WRITE ,__i2sdai_bits);
__IO_REG32(    I2STXFIFO,             0xE0088008,__WRITE);
__IO_REG32(    I2SRXFIFO,             0xE008800C,__READ);
__IO_REG32_BIT(I2SSTATE,              0xE0088010,__READ       ,__i2sstate_bits);
__IO_REG32_BIT(I2SDMA1,               0xE0088014,__READ_WRITE ,__i2sdma_bits);
__IO_REG32_BIT(I2SDMA2,               0xE0088018,__READ_WRITE ,__i2sdma_bits);
__IO_REG32_BIT(I2SIRQ,                0xE008801C,__READ_WRITE ,__i2sirq_bits);
__IO_REG32_BIT(I2STXRATE,             0xE0088020,__READ_WRITE ,__i2stxrate_bits);
__IO_REG32_BIT(I2SRXRATE,             0xE0088024,__READ_WRITE ,__i2srxrate_bits);

/***************************************************************************
 **
 ** TIMER0
 **
 ***************************************************************************/
__IO_REG32_BIT(T0IR,                  0xE0004000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T0TCR,                 0xE0004004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T0TC,                  0xE0004008,__READ_WRITE);
__IO_REG32(    T0PR,                  0xE000400C,__READ_WRITE);
__IO_REG32(    T0PC,                  0xE0004010,__READ_WRITE);
__IO_REG32_BIT(T0MCR,                 0xE0004014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T0MR0,                 0xE0004018,__READ_WRITE);
__IO_REG32(    T0MR1,                 0xE000401C,__READ_WRITE);
__IO_REG32(    T0MR2,                 0xE0004020,__READ_WRITE);
__IO_REG32(    T0MR3,                 0xE0004024,__READ_WRITE);
__IO_REG32_BIT(T0CCR,                 0xE0004028,__READ_WRITE ,__ccr_bits);
__IO_REG32(    T0CR0,                 0xE000402C,__READ);
__IO_REG32(    T0CR1,                 0xE0004030,__READ);
__IO_REG32(    T0CR2,                 0xE0004034,__READ);
__IO_REG32(    T0CR3,                 0xE0004038,__READ);
__IO_REG32_BIT(T0EMR,                 0xE000403C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T0CTCR,                0xE0004070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** TIMER1
 **
 ***************************************************************************/
__IO_REG32_BIT(T1IR,                  0xE0008000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T1TCR,                 0xE0008004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T1TC,                  0xE0008008,__READ_WRITE);
__IO_REG32(    T1PR,                  0xE000800C,__READ_WRITE);
__IO_REG32(    T1PC,                  0xE0008010,__READ_WRITE);
__IO_REG32_BIT(T1MCR,                 0xE0008014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T1MR0,                 0xE0008018,__READ_WRITE);
__IO_REG32(    T1MR1,                 0xE000801C,__READ_WRITE);
__IO_REG32(    T1MR2,                 0xE0008020,__READ_WRITE);
__IO_REG32(    T1MR3,                 0xE0008024,__READ_WRITE);
__IO_REG32_BIT(T1CCR,                 0xE0008028,__READ_WRITE ,__ccr_bits);
__IO_REG32(    T1CR0,                 0xE000802C,__READ);
__IO_REG32(    T1CR1,                 0xE0008030,__READ);
__IO_REG32(    T1CR2,                 0xE0008034,__READ);
__IO_REG32(    T1CR3,                 0xE0008038,__READ);
__IO_REG32_BIT(T1EMR,                 0xE000803C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T1CTCR,                0xE0008070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** TIMER2
 **
 ***************************************************************************/
__IO_REG32_BIT(T2IR,                  0xE0070000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T2TCR,                 0xE0070004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T2TC,                  0xE0070008,__READ_WRITE);
__IO_REG32(    T2PR,                  0xE007000C,__READ_WRITE);
__IO_REG32(    T2PC,                  0xE0070010,__READ_WRITE);
__IO_REG32_BIT(T2MCR,                 0xE0070014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T2MR0,                 0xE0070018,__READ_WRITE);
__IO_REG32(    T2MR1,                 0xE007001C,__READ_WRITE);
__IO_REG32(    T2MR2,                 0xE0070020,__READ_WRITE);
__IO_REG32(    T2MR3,                 0xE0070024,__READ_WRITE);
__IO_REG32_BIT(T2CCR,                 0xE0070028,__READ_WRITE ,__ccr_bits);
__IO_REG32(    T2CR0,                 0xE007002C,__READ);
__IO_REG32(    T2CR1,                 0xE0070030,__READ);
__IO_REG32(    T2CR2,                 0xE0070034,__READ);
__IO_REG32(    T2CR3,                 0xE0070038,__READ);
__IO_REG32_BIT(T2EMR,                 0xE007003C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T2CTCR,                0xE0070070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** TIMER3
 **
 ***************************************************************************/
__IO_REG32_BIT(T3IR,                  0xE0074000,__READ_WRITE ,__ir_bits);
__IO_REG32_BIT(T3TCR,                 0xE0074004,__READ_WRITE ,__tcr_bits);
__IO_REG32(    T3TC,                  0xE0074008,__READ_WRITE);
__IO_REG32(    T3PR,                  0xE007400C,__READ_WRITE);
__IO_REG32(    T3PC,                  0xE0074010,__READ_WRITE);
__IO_REG32_BIT(T3MCR,                 0xE0074014,__READ_WRITE ,__mcr_bits);
__IO_REG32(    T3MR0,                 0xE0074018,__READ_WRITE);
__IO_REG32(    T3MR1,                 0xE007401C,__READ_WRITE);
__IO_REG32(    T3MR2,                 0xE0074020,__READ_WRITE);
__IO_REG32(    T3MR3,                 0xE0074024,__READ_WRITE);
__IO_REG32_BIT(T3CCR,                 0xE0074028,__READ_WRITE ,__ccr_bits);
__IO_REG32(    T3CR0,                 0xE007402C,__READ);
__IO_REG32(    T3CR1,                 0xE0074030,__READ);
__IO_REG32(    T3CR2,                 0xE0074034,__READ);
__IO_REG32(    T3CR3,                 0xE0074038,__READ);
__IO_REG32_BIT(T3EMR,                 0xE007403C,__READ_WRITE ,__emr_bits);
__IO_REG32_BIT(T3CTCR,                0xE0074070,__READ_WRITE ,__ctcr_bits);

/***************************************************************************
 **
 ** Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDMOD,                 0xE0000000,__READ_WRITE ,__wdmod_bits);
__IO_REG32(    WDTC,                  0xE0000004,__READ_WRITE);
__IO_REG32_BIT(WDFEED,                0xE0000008,__WRITE      ,__wdfeed_bits);
__IO_REG32(    WDTV,                  0xE000000C,__READ);
__IO_REG32_BIT(WDCLKSEL,              0xE0000010,__READ_WRITE ,__wdclksel_bits);

/***************************************************************************
 **
 ** A/D Converters
 **
 ***************************************************************************/
__IO_REG32_BIT(AD0CR,                 0xE0034000,__READ_WRITE ,__adcr_bits);
__IO_REG32_BIT(AD0GDR,                0xE0034004,__READ_WRITE ,__adgdr_bits);
__IO_REG32_BIT(ADINTEN,               0xE003400C,__READ_WRITE ,__adinten_bits);
__IO_REG32_BIT(ADDR0,                 0xE0034010,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR1,                 0xE0034014,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR2,                 0xE0034018,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR3,                 0xE003401C,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR4,                 0xE0034020,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR5,                 0xE0034024,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR6,                 0xE0034028,__READ       ,__addr_bits);
__IO_REG32_BIT(ADDR7,                 0xE003402C,__READ       ,__addr_bits);
__IO_REG32_BIT(ADSTAT,                0xE0034030,__READ       ,__adstat_bits);

/***************************************************************************
 **
 ** D/A Converter
 **
 ***************************************************************************/
__IO_REG32_BIT(DACR,                  0xE006C000,__READ_WRITE ,__dacr_bits);

/***************************************************************************
 **
 ** PWM1
 **
 ***************************************************************************/
__IO_REG32_BIT(PWM1IR,                0xE0018000,__READ_WRITE ,__pwmir_bits);
__IO_REG32_BIT(PWM1TCR,               0xE0018004,__READ_WRITE ,__pwmtcr1_bits);
__IO_REG32(    PWM1TC,                0xE0018008,__READ_WRITE);
__IO_REG32(    PWM1PR,                0xE001800C,__READ_WRITE);
__IO_REG32(    PWM1PC,                0xE0018010,__READ_WRITE);
__IO_REG32_BIT(PWM1MCR,               0xE0018014,__READ_WRITE ,__pwmmcr_bits);
__IO_REG32(    PWM1MR0,               0xE0018018,__READ_WRITE);
__IO_REG32(    PWM1MR1,               0xE001801C,__READ_WRITE);
__IO_REG32(    PWM1MR2,               0xE0018020,__READ_WRITE);
__IO_REG32(    PWM1MR3,               0xE0018024,__READ_WRITE);
__IO_REG32_BIT(PWM1CCR,               0xE0018028,__READ_WRITE ,__pwmccr_bits);
__IO_REG32(    PWM1CR0,               0xE001802C,__READ_WRITE);
__IO_REG32(    PWM1CR1,               0xE0018030,__READ_WRITE);
__IO_REG32(    PWM1CR2,               0xE0018034,__READ_WRITE);
__IO_REG32(    PWM1CR3,               0xE0018038,__READ_WRITE);
__IO_REG32(    PWM1EMR,               0xE001803C,__READ_WRITE);
__IO_REG32(    PWM1MR4,               0xE0018040,__READ_WRITE);
__IO_REG32(    PWM1MR5,               0xE0018044,__READ_WRITE);
__IO_REG32(    PWM1MR6,               0xE0018048,__READ_WRITE);
__IO_REG32_BIT(PWM1PCR,               0xE001804C,__READ_WRITE ,__pwmpcr_bits);
__IO_REG32_BIT(PWM1LER,               0xE0018050,__READ_WRITE ,__pwmler_bits);
__IO_REG32_BIT(PWM1CTCR,              0xE0018070,__READ_WRITE ,__pwmctcr_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(ILR,                   0xE0024000,__READ_WRITE ,__ilr_bits);
__IO_REG32_BIT(CTC,                   0xE0024004,__READ       ,__ctc_bits);
__IO_REG32_BIT(CCR,                   0xE0024008,__READ_WRITE ,__rtcccr_bits);
__IO_REG32_BIT(CIIR,                  0xE002400C,__READ_WRITE ,__ciir_bits);
__IO_REG32_BIT(AMR,                   0xE0024010,__READ_WRITE ,__amr_bits);
__IO_REG32_BIT(CTIME0,                0xE0024014,__READ       ,__ctime0_bits);
__IO_REG32_BIT(CTIME1,                0xE0024018,__READ       ,__ctime1_bits);
__IO_REG32_BIT(CTIME2,                0xE002401C,__READ       ,__ctime2_bits);
__IO_REG32_BIT(SEC,                   0xE0024020,__READ_WRITE ,__sec_bits);
__IO_REG32_BIT(MIN,                   0xE0024024,__READ_WRITE ,__min_bits);
__IO_REG32_BIT(HOUR,                  0xE0024028,__READ_WRITE ,__hour_bits);
__IO_REG32_BIT(DOM,                   0xE002402C,__READ_WRITE ,__dom_bits);
__IO_REG32_BIT(DOW,                   0xE0024030,__READ_WRITE ,__dow_bits);
__IO_REG32_BIT(DOY,                   0xE0024034,__READ_WRITE ,__doy_bits);
__IO_REG32_BIT(MONTH,                 0xE0024038,__READ_WRITE ,__month_bits);
__IO_REG32_BIT(YEAR,                  0xE002403C,__READ_WRITE ,__year_bits);
__IO_REG32_BIT(CISS,                  0xE0024040,__READ_WRITE ,__ciss_bits);
__IO_REG32_BIT(ALSEC,                 0xE0024060,__READ_WRITE ,__sec_bits);
__IO_REG32_BIT(ALMIN,                 0xE0024064,__READ_WRITE ,__min_bits);
__IO_REG32_BIT(ALHOUR,                0xE0024068,__READ_WRITE ,__hour_bits);
__IO_REG32_BIT(ALDOM,                 0xE002406C,__READ_WRITE ,__dom_bits);
__IO_REG32_BIT(ALDOW,                 0xE0024070,__READ_WRITE ,__dow_bits);
__IO_REG32_BIT(ALDOY,                 0xE0024074,__READ_WRITE ,__doy_bits);
__IO_REG32_BIT(ALMON,                 0xE0024078,__READ_WRITE ,__month_bits);
__IO_REG32_BIT(ALYEAR,                0xE002407C,__READ_WRITE ,__year_bits);
__IO_REG32_BIT(PREINT,                0xE0024080,__READ_WRITE ,__preint_bits);
__IO_REG32_BIT(PREFRAC,               0xE0024084,__READ_WRITE ,__prefrac_bits);

/***************************************************************************
 **
 ** DMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DMACINTSTATUS,         0xFFE04000,__READ      ,__dmacintstatus_bits);
__IO_REG32_BIT(DMACINTTCSTATUS,       0xFFE04004,__READ      ,__dmacinttcstatus_bits);
__IO_REG32_BIT(DMACINTTCCLEAR,        0xFFE04008,__WRITE     ,__dmacinttcclear_bits);
__IO_REG32_BIT(DMACINTERRSTAT,        0xFFE0400C,__READ      ,__dmacinterrstat_bits);
__IO_REG32_BIT(DMACINTERRCLR,         0xFFE04010,__WRITE     ,__dmacinterrclr_bits);
__IO_REG32_BIT(DMACRAWINTTCSTATUS,    0xFFE04014,__READ      ,__dmacrawinttcstatus_bits);
__IO_REG32_BIT(DMACRAWINTERRORSTATUS, 0xFFE04018,__READ      ,__dmacrawinterrorstatus_bits);
__IO_REG32_BIT(DMACENBLDCHNS,         0xFFE0401C,__READ      ,__dmacenbldchns_bits);
__IO_REG32_BIT(DMACSOFTBREQ,          0xFFE04020,__READ_WRITE,__dmacsoftbreq_bits);
__IO_REG32_BIT(DMACSOFTSREQ,          0xFFE04024,__READ_WRITE,__dmacsoftsreq_bits);
__IO_REG32_BIT(DMACSOFTLBREQ,         0xFFE04028,__READ_WRITE,__dmacsoftlbreq_bits);
__IO_REG32_BIT(DMACSOFTLSREQ,         0xFFE0402C,__READ_WRITE,__dmacsoftlsreq_bits);
__IO_REG32_BIT(DMACCONFIGURATION,     0xFFE04030,__READ_WRITE,__dmacconfig_bits);
__IO_REG32_BIT(DMACSYNC,              0xFFE04034,__READ_WRITE,__dmacsync_bits);
__IO_REG32(    DMACC0SRCADDR,         0xFFE04100,__READ_WRITE);
__IO_REG32(    DMACC0DESTADDR,        0xFFE04104,__READ_WRITE);
__IO_REG32_BIT(DMACC0LLI,             0xFFE04108,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMACC0CONTROL,         0xFFE0410C,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC0CONFIGURATION,   0xFFE04110,__READ_WRITE,__dma_cfg_bits);
__IO_REG32(    DMACC1SRCADDR,         0xFFE04120,__READ_WRITE);
__IO_REG32(    DMACC1DESTADDR,        0xFFE04124,__READ_WRITE);
__IO_REG32_BIT(DMACC1LLI,             0xFFE04128,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMACC1CONTROL,         0xFFE0412C,__READ_WRITE,__dma_ctrl_bits);
__IO_REG32_BIT(DMACC1CONFIGURATION,   0x31000130,__READ_WRITE,__dma_cfg_bits);

/***************************************************************************
 **  Assembler-specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__
#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  Interrupt vector table
 **
 ***************************************************************************/
#define RESETV        0x00  /* Reset                              */
#define UNDEFV        0x04  /* Undefined instruction              */
#define SWIV          0x08  /* Software interrupt                 */
#define PABORTV       0x0C  /* Prefetch abort                     */
#define DABORTV       0x10  /* Data abort                         */
#define IRQV          0x18  /* Normal interrupt                   */
#define FIQV          0x1C  /* Fast interrupt                     */

/***************************************************************************
 **
 **  DMA Controller peripheral devices lines
 **
 ***************************************************************************/
#define DMA_SSP0TX       0  /* SPI0 Tx                            */
#define DMA_SSP0RX       1  /* SPI0 Rx                            */
#define DMA_SSP1TX       2  /* SPI1 Tx                            */
#define DMA_SSP1RX       3  /* SPI1 Rx                            */
#define DMA_MMCSD        4  /* MMC/SD                             */
#define DMA_I2S0         5  /* I2S Channel 0                      */
#define DMA_I2S1         6  /* I2S Channel 1                      */

/***************************************************************************
 **
 **  VIC Interrupt channels
 **
 ***************************************************************************/
#define VIC_WDT          0  /* Watchdog                           */
#define VIC_SW           1  /* Software interrupts                */
#define VIC_DEBUGRX      2  /* Embedded ICE, DbgCommRx            */
#define VIC_DEBUGTX      3  /* Embedded ICE, DbgCommTx            */
#define VIC_TIMER0       4  /* Timer 0 (Match 0-3 Capture 0-3)    */
#define VIC_TIMER1       5  /* Timer 1 (Match 0-3 Capture 0-3)    */
#define VIC_UART0        6  /* UART 0  (RLS, THRE, RDA, CTI)      */
#define VIC_UART1        7  /* UART 1  (RLS, THRE, RDA, CTI, MSI) */
#define VIC_PWM01        8  /* PWM 01  (Match 0-6 Capture 0-3)    */
#define VIC_I2C0         9  /* I2C 0   (SI)                       */
#define VIC_SPI         10  /* SPI 0, SSP 0                       */
#define VIC_SSP1         11 /* SSP 1                              */
#define VIC_PLL         12  /* PLL lock (PLOCK)                   */
#define VIC_RTC         13  /* RTC      (RTCCIF, RTCALF)          */
#define VIC_EINT0       14  /* External interrupt 0 (EINT0)       */
#define VIC_EINT1       15  /* External interrupt 1 (EINT1)       */
#define VIC_EINT2       16  /* External interrupt 2 (EINT2)       */
#define VIC_EINT3       17  /* External interrupt 3 (EINT3)       */
#define VIC_AD0         18  /* A/D converter 0                    */
#define VIC_I2C1        19  /* I2C 1                              */
#define VIC_BOD         20  /* Brown out detect                   */
#define VIC_ETHERNET    21  /* Ethernet                           */
#define VIC_USB         22  /* USB Low and High priority          */
#define VIC_CAN12       23  /* CAN1,2 Tx, Rx                      */
#define VIC_MMC         24  /* SD/MMC                             */
#define VIC_GP_DMA      25  /* DMA channel 0, DMA channel 1       */
#define VIC_TIMER2      26  /* Timer 2 (Match 0-3 Capture 0-3)    */
#define VIC_TIMER3      27  /* Timer 3 (Match 0-3 Capture 0-3)    */
#define VIC_UART2       28  /* UART 2  (RLS, THRE, RDA, CTI)      */
#define VIC_UART3       29  /* UART 3  (RLS, THRE, RDA, CTI, MSI) */
#define VIC_I2C2        30  /* I2C 0   (SI)                       */
#define VIC_I2S         31  /* I2S Rx, Tx                         */

#endif    /* __IOLPC2378_H */
