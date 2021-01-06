/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    st STR912
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.6.2.1 $
 **
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/
#ifndef __IOSTR912_H
#define __IOSTR912_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   STR912 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

/* Boot bank size register (FMI_BBSR) */
typedef struct{
__REG32 BBSIZE  : 4;
__REG32         :28;
} __fmi_bbsr_bits;

/* Non-boot bank size register (FMI_NBBSR) */
typedef struct{
__REG32 NBBSIZE  : 4;
__REG32          :28;
} __fmi_nbbsr_bits;

/* Boot Bank base address register (FMI_BBADR) */
typedef struct{
__REG32 BBADDR  :24;
__REG32         : 8;
} __fmi_bbadr_bits;

/* Non-boot bank base address register (FMI_NBBADR) */
typedef struct{
__REG32 NBBADDR  :24;
__REG32          : 8;
} __fmi_nbbadr_bits;

/* FMI Control register (FMI_CR) */
typedef struct {
  __REG32                 : 3;
  __REG32 B0EN            : 1;
  __REG32 B1EN            : 1;
  __REG32                 : 1;
  __REG32 BERRIE          : 1;
  __REG32 OMIE            : 1;
  __REG32 WWS             : 1;
  __REG32                 :23;
} __fmi_cr_bits;

/* FMI Status register (FMI_SR) */
typedef struct {
  __REG32 B0ERR           : 1;
  __REG32 B1ERR           : 1;
  __REG32                 : 1;
  __REG32 OM              : 1;
  __REG32 PFQBCEN         : 1;
  __REG32                 :27;
} __fmi_sr_bits;

/* BC Fifth Entry Target Address register (FMI_BCE5ADDR) */
typedef struct {
  __REG32 BCE5ADDR        :24;
  __REG32                 : 8;
} __fmi_bce5addr_bits;

/* Bank x Idle Cycle Control Register (EMI_ICRx) */
typedef struct{
__REG32 IDCY  : 4;
__REG32       :28;
} __emi_icr_bits;

/* Bank x Read Wait State Control Register (EMI_RCRx) */
typedef struct{
__REG32 WSTRD  : 5;
__REG32        :27;
} __emi_rcr_bits;

/* Bank x Write Wait State Control Register (EMI_WCRx) */
typedef struct{
__REG32 WSTWR  : 5;
__REG32        :27;
} __emi_wcr_bits;

/* Bank x Output Enable Control Register (EMI_OECRx) */
typedef struct{
__REG32 WSTOEN  : 4;
__REG32         :28;
} __emi_oecr_bits;

/* Bank x Write Enable Control Register (EMI_WECRx) */
typedef struct{
__REG32 WSTWEN  : 4;
__REG32         :28;
} __emi_wecr_bits;

/* Bank x Control Register (EMI_BCRx) */
typedef struct{
__REG32       : 3;
__REG32 WP    : 1;
__REG32 MW    : 2;
__REG32       : 2;
__REG32 PM    : 1;
__REG32       : 1;
__REG32 PLEN  : 2;
__REG32       :20;
} __emi_bcr_bits;

/* Clock control register (SCU_CLKCNTR) */
typedef struct{
__REG32 MCLKSEL   : 2;
__REG32 RCLKDIV   : 3;
__REG32 AHBDIV    : 2;
__REG32 APBDIV    : 2;
__REG32 BRSEL     : 1;
__REG32 USBSEL    : 2;
__REG32 PHYSEL    : 1;
__REG32 TIM01SEL  : 1;
__REG32 TIM23SEL  : 1;
__REG32           : 1;
__REG32 FMISEL    : 1;
__REG32 EMIRATIO  : 2;
__REG32           :13;
} __scu_clkcntr_bits;

/* PLL configuration register (SCU_PLLCONF) */
typedef struct{
__REG32 PLL_MDIV  : 8;
__REG32 PLL_NDIV  : 8;
__REG32 PLL_PDIV  : 3;
__REG32 PLL_EN    : 1;
__REG32           :12;
} __scu_pllconf_bits;

/* System status register (SCU_SYSSTATUS) */
typedef struct{
__REG32 LOCK       : 1;
__REG32 LOCK_LOST  : 1;
__REG32 WDG_RST    : 1;
__REG32 LVD_RST    : 1;
__REG32 ACK_PFQBC  : 1;
__REG32 SRAM_ERR   : 1;
__REG32            :26;
} __scu_sysstatus_bits;

/* Power management register (SCU_PWRMNG) */
typedef struct{
__REG32 PWR_MODE      : 3;
__REG32 CPU_INTR      : 1;
__REG32 FLASH_PD_DBG  : 1;
__REG32               :27;
} __scu_pwrmng_bits;

/* Interrupt mask register (SCU_ITCMSK) */
typedef struct{
__REG32 MSK_LOCK       : 1;
__REG32 MSK_LOCK_LOST  : 1;
__REG32 MSK_ACK_PFQBC  : 1;
__REG32 MSK_SRAM_ERR   : 1;
__REG32 MSK_LVD_RST    : 1;
__REG32                :27;
} __scu_itcmsk_bits;

/* Peripheral clock gating register 0 (SCU_PCGR0) */
/* Peripheral emulation clock gating register 0 (SCU_PECGR0) */
typedef struct{
__REG32 FMI           : 1;
__REG32 PQFBC         : 1;
__REG32               : 1;
__REG32 SRAM          : 1;
__REG32 SRAM_ARBITER  : 1;
__REG32 VIC           : 1;
__REG32 EMI           : 1;
__REG32 EXT_MEM_CLK   : 1;
__REG32 DMA           : 1;
__REG32 USB           : 1;
__REG32 USB48M        : 1;
__REG32 MAC           : 1;
__REG32               :20;
} __scu_pcgr0_bits;

/* Peripheral clock gating register 1 (SCU_PCGR1) */
typedef struct{
__REG32 TIM01  : 1;
__REG32 TIM23  : 1;
__REG32 MC     : 1;
__REG32 UART0  : 1;
__REG32 UART1  : 1;
__REG32 UART2  : 1;
__REG32 I2C0   : 1;
__REG32 I2C1   : 1;
__REG32 SSP0   : 1;
__REG32 SSP1   : 1;
__REG32 CAN    : 1;
__REG32 ADC    : 1;
__REG32 WDG    : 1;
__REG32 WIU    : 1;
__REG32 GPIO0  : 1;
__REG32 GPIO1  : 1;
__REG32 GPIO2  : 1;
__REG32 GPIO3  : 1;
__REG32 GPIO4  : 1;
__REG32 GPIO5  : 1;
__REG32 GPIO6  : 1;
__REG32 GPIO7  : 1;
__REG32 GPIO8  : 1;
__REG32 GPIO9  : 1;
__REG32 RTC    : 1;
__REG32        : 7;
} __scu_pcgr1_bits;

/* Peripheral emulation clock gating register 1 (SCU_PECGR1) */
typedef struct{
__REG32 TIM01  : 1;
__REG32 TIM23  : 1;
__REG32 MC     : 1;
__REG32 UART0  : 1;
__REG32 UART1  : 1;
__REG32 UART2  : 1;
__REG32 I2C0   : 1;
__REG32 I2C1   : 1;
__REG32 SSP0   : 1;
__REG32 SSP1   : 1;
__REG32 CAN    : 1;
__REG32 ADC    : 1;
__REG32 WDG    : 1;
__REG32 WIU    : 1;
__REG32 GPIO0  : 1;
__REG32 GPIO1  : 1;
__REG32 GPIO2  : 1;
__REG32 GPIO3  : 1;
__REG32 GPIO4  : 1;
__REG32 GPIO5  : 1;
__REG32 GPIO6  : 1;
__REG32 GPIO7  : 1;
__REG32 GPIO8  : 1;
__REG32 GPIO9  : 1;
__REG32        : 8;
} __scu_pecgr1_bits;

/* Peripheral reset register 0 (SCU_PRR0) */
typedef struct{
__REG32 RST_FMI           : 1;
__REG32 RST_PQFBC         : 1;
__REG32                   : 2;
__REG32 RST_SRAM_ARBITER  : 1;
__REG32 RST_VIC           : 1;
__REG32 RST_EMI           : 1;
__REG32                   : 1;
__REG32 RST_DMA           : 1;
__REG32 RST_USB           : 1;
__REG32                   : 1;
__REG32 RST_MAC           : 1;
__REG32 RST_PFQBC_AHB     : 1;
__REG32                   :19;
} __scu_prr0_bits;

/* Peripheral reset register 1 (SCU_PRR1) */
typedef struct{
__REG32 RST_TIM01  : 1;
__REG32 RST_TIM23  : 1;
__REG32 RST_MC     : 1;
__REG32 RST_UART0  : 1;
__REG32 RST_UART1  : 1;
__REG32 RST_UART2  : 1;
__REG32 RST_I2C0   : 1;
__REG32 RST_I2C1   : 1;
__REG32 RST_SSP0   : 1;
__REG32 RST_SSP1   : 1;
__REG32 RST_CAN    : 1;
__REG32 RST_ADC    : 1;
__REG32 RST_WDG    : 1;
__REG32 RST_WIU    : 1;
__REG32 RST_GPIO0  : 1;
__REG32 RST_GPIO1  : 1;
__REG32 RST_GPIO2  : 1;
__REG32 RST_GPIO3  : 1;
__REG32 RST_GPIO4  : 1;
__REG32 RST_GPIO5  : 1;
__REG32 RST_GPIO6  : 1;
__REG32 RST_GPIO7  : 1;
__REG32 RST_GPIO8  : 1;
__REG32 RST_GPIO9  : 1;
__REG32 RST_RTC    : 1;
__REG32            : 7;
} __scu_prr1_bits;

/* Idle mode gating mask register 0 (SCU_MGR0) */
typedef struct{
__REG32                   : 1;
__REG32 MSK_PQFBC         : 1;
__REG32                   : 1;
__REG32 MSK_SRAM          : 1;
__REG32 MSK_SRAM_ARBITER  : 1;
__REG32 MSK_VIC           : 1;
__REG32 MSK_EMI           : 1;
__REG32 MSK_EXT_MEM_CLK   : 1;
__REG32 MSK_DMA           : 1;
__REG32 MSK_USB           : 1;
__REG32 MSK_USB48M        : 1;
__REG32 MSK_MAC           : 1;
__REG32                   :20;
} __scu_mgr0_bits;

/* Idle mode gating mask register 1 (SCU_MGR1) */
typedef struct{
__REG32 MSK_TIM01  : 1;
__REG32 MSK_TIM23  : 1;
__REG32 MSK_MC     : 1;
__REG32 MSK_UART0  : 1;
__REG32 MSK_UART1  : 1;
__REG32 MSK_UART2  : 1;
__REG32 MSK_I2C0   : 1;
__REG32 MSK_I2C1   : 1;
__REG32 MSK_SSP0   : 1;
__REG32 MSK_SSP1   : 1;
__REG32 MSK_CAN    : 1;
__REG32 MSK_ADC    : 1;
__REG32 MSK_WDG    : 1;
__REG32 MSK_WIU    : 1;
__REG32 MSK_GPIO0  : 1;
__REG32 MSK_GPIO1  : 1;
__REG32 MSK_GPIO2  : 1;
__REG32 MSK_GPIO3  : 1;
__REG32 MSK_GPIO4  : 1;
__REG32 MSK_GPIO5  : 1;
__REG32 MSK_GPIO6  : 1;
__REG32 MSK_GPIO7  : 1;
__REG32 MSK_GPIO8  : 1;
__REG32 MSK_GPIO9  : 1;
__REG32 MSK_RTC    : 1;
__REG32            : 7;
} __scu_mgr1_bits;

/* System configuration register 0 (SCU_SCR0) */
typedef struct{
__REG32 EN_PFQBC        : 1;
__REG32 WSR_DTCM        : 1;
__REG32 WSR_AHB         : 1;
__REG32 SRAM_SIZE       : 2;
__REG32 SRAM_LK_EN      : 1;
__REG32 EMI_MUX         : 1;
__REG32 EMI_ALE_POLR    : 1;
__REG32 EMI_ALE_LNGT    : 1;
__REG32                 : 1;
__REG32 UART0_IRDA      : 1;
__REG32 UART1_IRDA      : 1;
__REG32 UART2_IRDA      : 1;
__REG32 EXT_ETMT_EDBGR  : 1;
__REG32 P30_SELEDBG     : 1;
__REG32                 :17;
} __scu_scr0_bits;

/* GPIO output register (SCU_GPIOOUT0) */
typedef struct{
__REG32 P0OUT0  : 2;
__REG32 P0OUT1  : 2;
__REG32 P0OUT2  : 2;
__REG32 P0OUT3  : 2;
__REG32 P0OUT4  : 2;
__REG32 P0OUT5  : 2;
__REG32 P0OUT6  : 2;
__REG32 P0OUT7  : 2;
__REG32         :16;
} __scu_gpioout0_bits;

/* GPIO output register (SCU_GPIOOUT1) */
typedef struct{
__REG32 P1OUT0  : 2;
__REG32 P1OUT1  : 2;
__REG32 P1OUT2  : 2;
__REG32 P1OUT3  : 2;
__REG32 P1OUT4  : 2;
__REG32 P1OUT5  : 2;
__REG32 P1OUT6  : 2;
__REG32 P1OUT7  : 2;
__REG32         :16;
} __scu_gpioout1_bits;

/* GPIO output register (SCU_GPIOOUT2) */
typedef struct{
__REG32 P2OUT0  : 2;
__REG32 P2OUT1  : 2;
__REG32 P2OUT2  : 2;
__REG32 P2OUT3  : 2;
__REG32 P2OUT4  : 2;
__REG32 P2OUT5  : 2;
__REG32 P2OUT6  : 2;
__REG32 P2OUT7  : 2;
__REG32         :16;
} __scu_gpioout2_bits;

/* GPIO output register (SCU_GPIOOUT3) */
typedef struct{
__REG32 P3OUT0  : 2;
__REG32 P3OUT1  : 2;
__REG32 P3OUT2  : 2;
__REG32 P3OUT3  : 2;
__REG32 P3OUT4  : 2;
__REG32 P3OUT5  : 2;
__REG32 P3OUT6  : 2;
__REG32 P3OUT7  : 2;
__REG32         :16;
} __scu_gpioout3_bits;

/* GPIO output register (SCU_GPIOOUT4) */
typedef struct{
__REG32 P4OUT0  : 2;
__REG32 P4OUT1  : 2;
__REG32 P4OUT2  : 2;
__REG32 P4OUT3  : 2;
__REG32 P4OUT4  : 2;
__REG32 P4OUT5  : 2;
__REG32 P4OUT6  : 2;
__REG32 P4OUT7  : 2;
__REG32         :16;
} __scu_gpioout4_bits;

/* GPIO output register (SCU_GPIOOUT5) */
typedef struct{
__REG32 P5OUT0  : 2;
__REG32 P5OUT1  : 2;
__REG32 P5OUT2  : 2;
__REG32 P5OUT3  : 2;
__REG32 P5OUT4  : 2;
__REG32 P5OUT5  : 2;
__REG32 P5OUT6  : 2;
__REG32 P5OUT7  : 2;
__REG32         :16;
} __scu_gpioout5_bits;

/* GPIO output register (SCU_GPIOOUT6) */
typedef struct{
__REG32 P6OUT0  : 2;
__REG32 P6OUT1  : 2;
__REG32 P6OUT2  : 2;
__REG32 P6OUT3  : 2;
__REG32 P6OUT4  : 2;
__REG32 P6OUT5  : 2;
__REG32 P6OUT6  : 2;
__REG32 P6OUT7  : 2;
__REG32         :16;
} __scu_gpioout6_bits;

/* GPIO output register (SCU_GPIOOUT7) */
typedef struct{
__REG32 P7OUT0  : 2;
__REG32 P7OUT1  : 2;
__REG32 P7OUT2  : 2;
__REG32 P7OUT3  : 2;
__REG32 P7OUT4  : 2;
__REG32 P7OUT5  : 2;
__REG32 P7OUT6  : 2;
__REG32 P7OUT7  : 2;
__REG32         :16;
} __scu_gpioout7_bits;

/* GPIO input register (SCU_GPIOIN0) */
typedef struct{
__REG32 P0IN0  : 1;
__REG32 P0IN1  : 1;
__REG32 P0IN2  : 1;
__REG32 P0IN3  : 1;
__REG32 P0IN4  : 1;
__REG32 P0IN5  : 1;
__REG32 P0IN6  : 1;
__REG32 P0IN7  : 1;
__REG32        :24;
} __scu_gpioin0_bits;

/* GPIO input register (SCU_GPIOIN1) */
typedef struct{
__REG32 P1IN0  : 1;
__REG32 P1IN1  : 1;
__REG32 P1IN2  : 1;
__REG32 P1IN3  : 1;
__REG32 P1IN4  : 1;
__REG32 P1IN5  : 1;
__REG32 P1IN6  : 1;
__REG32 P1IN7  : 1;
__REG32        :24;
} __scu_gpioin1_bits;

/* GPIO input register (SCU_GPIOIN2) */
typedef struct{
__REG32 P2IN0  : 1;
__REG32 P2IN1  : 1;
__REG32 P2IN2  : 1;
__REG32 P2IN3  : 1;
__REG32 P2IN4  : 1;
__REG32 P2IN5  : 1;
__REG32 P2IN6  : 1;
__REG32 P2IN7  : 1;
__REG32        :24;
} __scu_gpioin2_bits;

/* GPIO input register (SCU_GPIOIN3) */
typedef struct{
__REG32 P3IN0  : 1;
__REG32 P3IN1  : 1;
__REG32 P3IN2  : 1;
__REG32 P3IN3  : 1;
__REG32 P3IN4  : 1;
__REG32 P3IN5  : 1;
__REG32 P3IN6  : 1;
__REG32 P3IN7  : 1;
__REG32        :24;
} __scu_gpioin3_bits;

/* GPIO input register (SCU_GPIOIN4) */
typedef struct{
__REG32 P4IN0  : 1;
__REG32 P4IN1  : 1;
__REG32 P4IN2  : 1;
__REG32 P4IN3  : 1;
__REG32 P4IN4  : 1;
__REG32 P4IN5  : 1;
__REG32 P4IN6  : 1;
__REG32 P4IN7  : 1;
__REG32        :24;
} __scu_gpioin4_bits;

/* GPIO input register (SCU_GPIOIN5) */
typedef struct{
__REG32 P5IN0  : 1;
__REG32 P5IN1  : 1;
__REG32 P5IN2  : 1;
__REG32 P5IN3  : 1;
__REG32 P5IN4  : 1;
__REG32 P5IN5  : 1;
__REG32 P5IN6  : 1;
__REG32 P5IN7  : 1;
__REG32        :24;
} __scu_gpioin5_bits;

/* GPIO input register (SCU_GPIOIN6) */
typedef struct{
__REG32 P6IN0  : 1;
__REG32 P6IN1  : 1;
__REG32 P6IN2  : 1;
__REG32 P6IN3  : 1;
__REG32 P6IN4  : 1;
__REG32 P6IN5  : 1;
__REG32 P6IN6  : 1;
__REG32 P6IN7  : 1;
__REG32        :24;
} __scu_gpioin6_bits;

/* GPIO input register (SCU_GPIOIN7) */
typedef struct{
__REG32 P7IN0  : 1;
__REG32 P7IN1  : 1;
__REG32 P7IN2  : 1;
__REG32 P7IN3  : 1;
__REG32 P7IN4  : 1;
__REG32 P7IN5  : 1;
__REG32 P7IN6  : 1;
__REG32 P7IN7  : 1;
__REG32        :24;
} __scu_gpioin7_bits;

/* GPIO type register (SCU_GPIOTYPE0) */
typedef struct{
__REG32 P0TYPE0  : 1;
__REG32 P0TYPE1  : 1;
__REG32 P0TYPE2  : 1;
__REG32 P0OUT03  : 1;
__REG32 P0OUT04  : 1;
__REG32 P0TYPE5  : 1;
__REG32 P0TYPE6  : 1;
__REG32 P0TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype0_bits;

/* GPIO type register (SCU_GPIOTYPE1) */
typedef struct{
__REG32 P1TYPE0  : 1;
__REG32 P1TYPE1  : 1;
__REG32 P1TYPE2  : 1;
__REG32 P1TYPE3  : 1;
__REG32 P1TYPE4  : 1;
__REG32 P1TYPE5  : 1;
__REG32 P1TYPE6  : 1;
__REG32 P1TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype1_bits;

/* GPIO type register (SCU_GPIOTYPE2) */
typedef struct{
__REG32 P2TYPE0  : 1;
__REG32 P2TYPE1  : 1;
__REG32 P2TYPE2  : 1;
__REG32 P2TYPE3  : 1;
__REG32 P2TYPE4  : 1;
__REG32 P2TYPE5  : 1;
__REG32 P2TYPE6  : 1;
__REG32 P2TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype2_bits;

/* GPIO type register (SCU_GPIOTYPE3) */
typedef struct{
__REG32 P3TYPE0  : 1;
__REG32 P3TYPE1  : 1;
__REG32 P3TYPE2  : 1;
__REG32 P3TYPE3  : 1;
__REG32 P3TYPE4  : 1;
__REG32 P3TYPE5  : 1;
__REG32 P3TYPE6  : 1;
__REG32 P3TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype3_bits;

/* GPIO type register (SCU_GPIOTYPE4) */
typedef struct{
__REG32 P4TYPE0  : 1;
__REG32 P4TYPE1  : 1;
__REG32 P4TYPE2  : 1;
__REG32 P4TYPE3  : 1;
__REG32 P4TYPE4  : 1;
__REG32 P4TYPE5  : 1;
__REG32 P4TYPE6  : 1;
__REG32 P4TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype4_bits;

/* GPIO type register (SCU_GPIOTYPE5) */
typedef struct{
__REG32 P5TYPE0  : 1;
__REG32 P5TYPE1  : 1;
__REG32 P5TYPE2  : 1;
__REG32 P5TYPE3  : 1;
__REG32 P5TYPE4  : 1;
__REG32 P5TYPE5  : 1;
__REG32 P5TYPE6  : 1;
__REG32 P5TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype5_bits;

/* GPIO type register (SCU_GPIOTYPE6) */
typedef struct{
__REG32 P6TYPE0  : 1;
__REG32 P6TYPE1  : 1;
__REG32 P6TYPE2  : 1;
__REG32 P6TYPE3  : 1;
__REG32 P6TYPE4  : 1;
__REG32 P6TYPE5  : 1;
__REG32 P6TYPE6  : 1;
__REG32 P6TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype6_bits;

/* GPIO type register (SCU_GPIOTYPE7) */
typedef struct{
__REG32 P7TYPE0  : 1;
__REG32 P7TYPE1  : 1;
__REG32 P7TYPE2  : 1;
__REG32 P7TYPE3  : 1;
__REG32 P7TYPE4  : 1;
__REG32 P7TYPE5  : 1;
__REG32 P7TYPE6  : 1;
__REG32 P7TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype7_bits;

/* GPIO type register (SCU_GPIOTYPE8) */
typedef struct{
__REG32 P8TYPE0  : 1;
__REG32 P8TYPE1  : 1;
__REG32 P8TYPE2  : 1;
__REG32 P8TYPE3  : 1;
__REG32 P8TYPE4  : 1;
__REG32 P8TYPE5  : 1;
__REG32 P8TYPE6  : 1;
__REG32 P8TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype8_bits;

/* GPIO type register (SCU_GPIOTYPE9) */
typedef struct{
__REG32 P9TYPE0  : 1;
__REG32 P9TYPE1  : 1;
__REG32 P9TYPE2  : 1;
__REG32 P9TYPE3  : 1;
__REG32 P9TYPE4  : 1;
__REG32 P9TYPE5  : 1;
__REG32 P9TYPE6  : 1;
__REG32 P9TYPE7  : 1;
__REG32          :24;
} __scu_gpiotype9_bits;

/* GPIO external memory interface register (SCU_EMI)) */
typedef struct{
__REG32 GPIOEMI  : 1;
__REG32          :31;
} __scu_emi_bits;

/* Wakeup selection register (SCU_WKUPSEL) */
typedef struct{
__REG32 WKUP_SEL3  : 3;
__REG32 WKUP_SEL5  : 3;
__REG32 WKUP_SEL6  : 3;
__REG32 WKUP_SEL7  : 3;
__REG32            :20;
} __scu_wkupsel_bits;

/* GPIO analog mode register (SCU_GPIOANA) */
typedef struct{
__REG32 P40A  : 1;
__REG32 P41A  : 1;
__REG32 P42A  : 1;
__REG32 P43A  : 1;
__REG32 P44A  : 1;
__REG32 P45A  : 1;
__REG32 P46A  : 1;
__REG32 P47A  : 1;
__REG32       :24;
} __scu_gpioana_bits;

/* VIC0 Register */
typedef struct{
__REG32 WDT     : 1;
__REG32 SWI     : 1;
__REG32 DBG_RX  : 1;
__REG32 DBG_TX  : 1;
__REG32 TIM0    : 1;
__REG32 TIM1    : 1;
__REG32 TIM2    : 1;
__REG32 TIM3    : 1;
__REG32 USB_HI  : 1;
__REG32 USB_LO  : 1;
__REG32 SCU     : 1;
__REG32 MAC     : 1;
__REG32 DMA     : 1;
__REG32 CAN     : 1;
__REG32 IMC     : 1;
__REG32 ADC     : 1;
__REG32         :16;
} __vic0_bits;

/* VIC1 Register */
typedef struct{
__REG32 UART0   : 1;
__REG32 UART1   : 1;
__REG32 UART2   : 1;
__REG32 I2C0    : 1;
__REG32 I2C1    : 1;
__REG32 SSP0    : 1;
__REG32 SSP1    : 1;
__REG32 SCU     : 1;
__REG32 RTC     : 1;
__REG32 WIU     : 1;
__REG32 WIU0    : 1;
__REG32 WIU1    : 1;
__REG32 WIU2    : 1;
__REG32 WIU3    : 1;
__REG32 USB     : 1;
__REG32 PFQ_BC  : 1;
__REG32         :16;
} __vic1_bits;

/* Protection Enable Register (VICx_Protection) */
typedef struct{
__REG32 PROT  : 1;
__REG32       :31;
} __vic_protection_bits;

/* Vector Control x Registers (VICx_VectCntlx) */
typedef struct{
__REG32 VectCntl  : 5;
__REG32 E         : 1;
__REG32           :26;
} __vic_vectcntl_bits;

/* WIU Control Register (WIU_CTRL) */
typedef struct{
__REG32 WKUP_INT  : 1;
__REG32 INT_EN    : 1;
__REG32           :30;
} __wiu_ctrl_bits;

/* WIU Mask Register (WIU_MR) */
typedef struct{
__REG32        : 2;
__REG32 WUM2   : 1;
__REG32 WUM3   : 1;
__REG32 WUM4   : 1;
__REG32 WUM5   : 1;
__REG32 WUM6   : 1;
__REG32 WUM7   : 1;
__REG32 WUM8   : 1;
__REG32 WUM9   : 1;
__REG32 WUM10  : 1;
__REG32 WUM11  : 1;
__REG32 WUM12  : 1;
__REG32 WUM13  : 1;
__REG32 WUM14  : 1;
__REG32 WUM15  : 1;
__REG32 WUM16  : 1;
__REG32 WUM17  : 1;
__REG32 WUM18  : 1;
__REG32 WUM19  : 1;
__REG32 WUM20  : 1;
__REG32 WUM21  : 1;
__REG32 WUM22  : 1;
__REG32 WUM23  : 1;
__REG32 WUM24  : 1;
__REG32 WUM25  : 1;
__REG32 WUM26  : 1;
__REG32 WUM27  : 1;
__REG32 WUM28  : 1;
__REG32 WUM29  : 1;
__REG32 WUM30  : 1;
__REG32 WUM31  : 1;
} __wiu_msk_bits;

/*   WIU Trigger Register (WIU_TR) */
typedef struct{
__REG32        : 2;
__REG32 WUT2   : 1;
__REG32 WUT3   : 1;
__REG32 WUT4   : 1;
__REG32 WUT5   : 1;
__REG32 WUT6   : 1;
__REG32 WUT7   : 1;
__REG32 WUT8   : 1;
__REG32 WUT9   : 1;
__REG32 WUT10  : 1;
__REG32 WUT11  : 1;
__REG32 WUT12  : 1;
__REG32 WUT13  : 1;
__REG32 WUT14  : 1;
__REG32 WUT15  : 1;
__REG32 WUT16  : 1;
__REG32 WUT17  : 1;
__REG32 WUT18  : 1;
__REG32 WUT19  : 1;
__REG32 WUT20  : 1;
__REG32 WUT21  : 1;
__REG32 WUT22  : 1;
__REG32 WUT23  : 1;
__REG32 WUT24  : 1;
__REG32 WUT25  : 1;
__REG32 WUT26  : 1;
__REG32 WUT27  : 1;
__REG32 WUT28  : 1;
__REG32 WUT29  : 1;
__REG32 WUT30  : 1;
__REG32 WUT31  : 1;
} __wiu_tr_bits;

/* WIU Software Interrupt Register (WIU_INTR) */
typedef struct{
__REG32          : 2;
__REG32 WINTR2   : 1;
__REG32 WINTR3   : 1;
__REG32 WINTR4   : 1;
__REG32 WINTR5   : 1;
__REG32 WINTR6   : 1;
__REG32 WINTR7   : 1;
__REG32 WINTR8   : 1;
__REG32 WINTR9   : 1;
__REG32 WINTR10  : 1;
__REG32 WINTR11  : 1;
__REG32 WINTR12  : 1;
__REG32 WINTR13  : 1;
__REG32 WINTR14  : 1;
__REG32 WINTR15  : 1;
__REG32 WINTR16  : 1;
__REG32 WINTR17  : 1;
__REG32 WINTR18  : 1;
__REG32 WINTR19  : 1;
__REG32 WINTR20  : 1;
__REG32 WINTR21  : 1;
__REG32 WINTR22  : 1;
__REG32 WINTR23  : 1;
__REG32 WINTR24  : 1;
__REG32 WINTR25  : 1;
__REG32 WINTR26  : 1;
__REG32 WINTR27  : 1;
__REG32 WINTR28  : 1;
__REG32 WINTR29  : 1;
__REG32 WINTR30  : 1;
__REG32 WINTR31  : 1;
} __wiu_intr_bits;

/* WIU Pending Register (WIU_PR)  */
typedef struct{
__REG32        : 2;
__REG32 WUP2   : 1;
__REG32 WUP3   : 1;
__REG32 WUP4   : 1;
__REG32 WUP5   : 1;
__REG32 WUP6   : 1;
__REG32 WUP7   : 1;
__REG32 WUP8   : 1;
__REG32 WUP9   : 1;
__REG32 WUP10  : 1;
__REG32 WUP11  : 1;
__REG32 WUP12  : 1;
__REG32 WUP13  : 1;
__REG32 WUP14  : 1;
__REG32 WUP15  : 1;
__REG32 WUP16  : 1;
__REG32 WUP17  : 1;
__REG32 WUP18  : 1;
__REG32 WUP19  : 1;
__REG32 WUP20  : 1;
__REG32 WUP21  : 1;
__REG32 WUP22  : 1;
__REG32 WUP23  : 1;
__REG32 WUP24  : 1;
__REG32 WUP25  : 1;
__REG32 WUP26  : 1;
__REG32 WUP27  : 1;
__REG32 WUP28  : 1;
__REG32 WUP29  : 1;
__REG32 WUP30  : 1;
__REG32 WUP31  : 1;
} __wiu_pr_bits;


/* RTC time register (RTC_TR) */
typedef struct{
__REG32 SU   : 4;
__REG32 ST   : 3;
__REG32      : 1;
__REG32 MIU  : 4;
__REG32 MIT  : 3;
__REG32      : 1;
__REG32 HU   : 4;
__REG32 HT   : 2;
__REG32      : 2;
__REG32 DU   : 4;
__REG32 DT   : 2;
__REG32      : 2;
} __rtc_tr_bits;

/* RTC date register (RTC_DTR) */
typedef struct{
__REG32 WDU  : 4;
__REG32      : 4;
__REG32 MU   : 4;
__REG32 MT   : 1;
__REG32      : 3;
__REG32 YU   : 4;
__REG32 YT   : 4;
__REG32 CU   : 4;
__REG32 CT   : 4;
} __rtc_dtr_bits;

/* RTC alarm time register (RTC_ATR) */
typedef struct{
__REG32 ASU   : 4;
__REG32 AST   : 3;
__REG32       : 1;
__REG32 AMIU  : 4;
__REG32 AMIT  : 3;
__REG32       : 1;
__REG32 AHU   : 4;
__REG32 AHT   : 2;
__REG32       : 2;
__REG32 ADU   : 4;
__REG32 ADT   : 2;
__REG32       : 2;
} __rtc_atr_bits;

/* RTC control register (RTC_CR) */
typedef struct{
__REG32 TE     : 1;
__REG32        : 1;
__REG32 TIS    : 1;
__REG32        : 1;
__REG32 TM     : 1;
__REG32        : 1;
__REG32 C      : 1;
__REG32 W      : 1;
__REG32        : 8;
__REG32 PISEL  : 4;
__REG32 AE     : 1;
__REG32 PIE    : 1;
__REG32 TIE    : 1;
__REG32 AIE    : 1;
__REG32        : 8;
} __rtc_cr_bits;

/* RTC Status Register (RTC_SR) */
typedef struct{
__REG32       :28;
__REG32 TSF   : 1;
__REG32       : 1;
__REG32 AF    : 1;
__REG32 PISF  : 1;
} __rtc_sr_bits;

/* RTC Millisecond Register (RTC_MILR) */
typedef struct{
__REG32 MSU  : 4;
__REG32 MST  : 4;
__REG32 MSH  : 4;
__REG32      :20;
} __rtc_milr_bits;

/* WDG control register (WDG_CR) */
typedef struct{
__REG16 WE  : 1;
__REG16 SC  : 1;
__REG16 EE  : 1;
__REG16     :13;
} __wdt_cr_bits;

/* WDG status register (WDG_SR) */
typedef struct{
__REG16 EC  : 1;
__REG16     :15;
} __wdt_sr_bits;

/* WDG mask register (WDG_MR) */
typedef struct{
__REG16 ECM  : 1;
__REG16      :15;
} __wdt_mr_bits;

/* Control Register 1 (TIM_CR1) */
typedef struct{
__REG16 ECKEN  : 1;
__REG16 EXEDG  : 1;
__REG16 IEDG1  : 1;
__REG16 IEDG2  : 1;
__REG16 PWM    : 1;
__REG16 OPM    : 1;
__REG16 OC1E   : 1;
__REG16 OC2E   : 1;
__REG16 OLVL1  : 1;
__REG16 OLVL2  : 1;
__REG16 FOLV1  : 1;
__REG16 FOLV2  : 1;
__REG16 DMAS   : 2;
__REG16 PWMI   : 1;
__REG16 EN     : 1;
} __tim_cr1_bits;

/* Control Register 1 (TIM2_CR1/TIM3_CR1) */
typedef struct{
__REG16 ECKEN  : 1;
__REG16 EXEDG  : 1;
__REG16 IEDG1  : 1;
__REG16 IEDG2  : 1;
__REG16 PWM    : 1;
__REG16 OPM    : 1;
__REG16 OC1E   : 1;
__REG16 OC2E   : 1;
__REG16 OLVL1  : 1;
__REG16 OLVL2  : 1;
__REG16 FOLV1  : 1;
__REG16 FOLV2  : 1;
__REG16        : 2;
__REG16 PWMI   : 1;
__REG16 EN     : 1;
} __tim2_cr1_bits;

/* Control Register 2 (TIM_CR2) */
typedef struct{
__REG16 CC     : 8;
__REG16        : 2;
__REG16 DMAE   : 1;
__REG16 OC2IE  : 1;
__REG16 IC2IE  : 1;
__REG16 TOIE   : 1;
__REG16 OC1IE  : 1;
__REG16 IC1IE  : 1;
} __tim_cr2_bits;

/* Control Register 2 (TIM2_CR2/TIM3_CR2) */
typedef struct{
__REG16 CC     : 8;
__REG16        : 3;
__REG16 OC2IE  : 1;
__REG16 IC2IE  : 1;
__REG16 TOIE   : 1;
__REG16 OC1IE  : 1;
__REG16 IC1IE  : 1;
} __tim2_cr2_bits;

/* Status Register (TIM_SR) */
typedef struct{
__REG16       :11;
__REG16 OCF2  : 1;
__REG16 ICF2  : 1;
__REG16 TOF   : 1;
__REG16 OCF1  : 1;
__REG16 ICF1  : 1;
} __tim_sr_bits;

/* DMA Status/Control Register (ENET_SCR) */
typedef struct{
__REG32 SRESET             : 1;
__REG32 LOOPB              : 1;
__REG32                    : 2;
__REG32 RX_MAX_BURST_SIZE  : 2;
__REG32 TX_MAX_BURST_SIZE  : 2;
__REG32 REVISION           : 8;
__REG32 RX_CHAN_STATUS     : 2;
__REG32 RX_IO_DATA_WIDTH   : 2;
__REG32 RX_FIFO_SIZE       : 4;
__REG32 TX_CHAN_STATUS     : 2;
__REG32 TX_IO_DATA_WIDTH   : 2;
__REG32 TX_FIFO_SIZE       : 4;
} __enet_scr_bits;

/* DMA Interrupt Enable Register (ENET_IER) */
typedef struct{
__REG32 RX_EMPTY_EN      : 1;
__REG32 RX_FULL_EN       : 1;
__REG32 RX_ENTRY_EN      : 1;
__REG32 RX_TO_EN         : 1;
__REG32                  : 1;
__REG32 PACKET_LOST_EN   : 1;
__REG32 RX_NEXT_EN       : 1;
__REG32 RX_DONE_EN       : 1;
__REG32                  : 1;
__REG32 RX_MERR_INT_EN   : 1;
__REG32                  : 5;
__REG32 RX_CURR_DONE_EN  : 1;
__REG32 TX_EMPTY_EN      : 1;
__REG32 TX_FULL_EN       : 1;
__REG32 TX_ENTRY_EN      : 1;
__REG32 TX_TO_EN         : 1;
__REG32                  : 2;
__REG32 TX_NEXT_EN       : 1;
__REG32 TX_DONE_EN       : 1;
__REG32                  : 1;
__REG32 TX_MERR_INT_EN   : 1;
__REG32                  : 2;
__REG32 MAC_8023_INT_EN  : 1;
__REG32                  : 2;
__REG32 TX_CURR_DONE_EN  : 1;
} __enet_ier_bits;

/* DMA Interrupt Status Register (ENET_ISR) */
typedef struct{
__REG32 RX_EMPTY      : 1;
__REG32 RX_FULL       : 1;
__REG32 RX_ENTRY      : 1;
__REG32 RX_TO         : 1;
__REG32               : 1;
__REG32 PACKET_LOST   : 1;
__REG32 RX_NEXT       : 1;
__REG32 RX_DONE       : 1;
__REG32               : 1;
__REG32 RX_MERR_INT   : 1;
__REG32               : 5;
__REG32 RX_CURR_DONE  : 1;
__REG32 TX_EMPTY      : 1;
__REG32 TX_FULL       : 1;
__REG32 TX_ENTRY      : 1;
__REG32 TX_TO         : 1;
__REG32               : 2;
__REG32 TX_NEXT       : 1;
__REG32 TX_DONE       : 1;
__REG32               : 1;
__REG32 TX_MERR_INT   : 1;
__REG32               : 2;
__REG32 MAC_8023_INT  : 1;
__REG32               : 2;
__REG32 TX_CURR_DONE  : 1;
} __enet_isr_bits;

/* Clock Configuration Register (ENET_CCR) */
typedef struct{
__REG32          : 2;
__REG32 SEL_CLK  : 2;
__REG32          :28;
} __enet_ccr_bits;

/* RX Start Register (ENET_RXSTR) */
typedef struct{
__REG32 DMA_EN       : 1;
__REG32              : 1;
__REG32 START_FETCH  : 1;
__REG32              : 2;
__REG32 FILTER_FAIL  : 1;
__REG32 RUNT_FRAME   : 1;
__REG32 COLL_SEEN    : 1;
__REG32 DFETCH_DLY   :16;
__REG32              : 8;
} __enet_rxstr_bits;

/* RX Control Register (ENET_RXCR) */
typedef struct{
__REG32 DMA_XFERCOUNT  :12;
__REG32 CONT_EN        : 1;
__REG32                : 1;
__REG32 NXT_EN         : 1;
__REG32 DLY_EN         : 1;
__REG32                : 1;
__REG32 ENTRY_TRIG     : 5;
__REG32 ADDR_WRAP      :10;
} __enet_rxcr_bits;

/* RX Start Address Register (ENET_RXSAR) */
typedef struct{
__REG32 WRAP_EN   : 1;
__REG32 FIX_ADDR  : 1;
__REG32 RXADDR    :30;
} __enet_rxsar_bits;

/* RX Next Descriptor Address Register (ENET_RXNDAR) */
typedef struct{
__REG32 NPOL_EN   : 1;
__REG32           : 1;
__REG32 DESCADDR  :30;
} __enet_rxndar_bits;

/* RX Current Transfer Count Register (ENET_RXCTCR) */
typedef struct{
__REG32 CXFER  :12;
__REG32        :20;
} __enet_rxctcr_bits;

/* RX Time-Out Register (ENET_RXTOR) */
typedef struct{
__REG32 RXTO   :16;
__REG32        :16;
} __enet_rxtor_bits;


/* RX Status Register (ENET_RXSR) */
typedef struct{
__REG32 EMPTY        : 1;
__REG32 FULL         : 1;
__REG32 ENTRY_T      : 1;
__REG32 DELAY_T      : 1;
__REG32              : 4;
__REG32 IO_POINTER   : 5;
__REG32              : 3;
__REG32 DMA_POINTER  : 5;
__REG32              : 3;
__REG32 ENTRIES      : 6;
__REG32              : 2;
} __enet_rxsr_bits;

/* TX Start Register (ENET_TXSTR) */
typedef struct{
__REG32 DMA_EN       : 1;
__REG32              : 1;
__REG32 START_FETCH  : 1;
__REG32              : 2;
__REG32 UNDER_RUN    : 1;
__REG32              : 2;
__REG32 DFETCH_DLY   :16;
__REG32              : 8;
} __enet_txstr_bits;

/* TX Control Register (ENET_TXCR) */
typedef struct{
__REG32 DMA_XFERCOUNT  :12;
__REG32 CONT_EN        : 1;
__REG32                : 1;
__REG32 NXT_EN         : 1;
__REG32 DLY_EN         : 1;
__REG32                : 1;
__REG32 ENTRY_TRIG     : 5;
__REG32 ADDR_WRAP      :10;
} __enet_txcr_bits;

/* TX Start Address Register (ENET_TXSAR) */
typedef struct{
__REG32 WRAP_EN   : 1;
__REG32 FIX_ADDR  : 1;
__REG32 TXADDR    :30;
} __enet_txsar_bits;

/* TX Next Descriptor Address Register (ENET_TXNDAR) */
typedef struct{
__REG32 NPOL_EN   : 1;
__REG32           : 1;
__REG32 DESCADDR  :30;
} __enet_txndar_bits;

/* TX Current Transfer Count Register (ENET_TXCTCR) */
typedef struct{
__REG32 CXFER  :12;
__REG32        :20;
} __enet_txctcr_bits;

/* TX Time-Out Register (ENET_TXTOR) */
typedef struct{
__REG32 TXTO   :16;
__REG32        :16;
} __enet_txtor_bits;

/* TX Status Register (ENET_TXSR) */
typedef struct{
__REG32 EMPTY        : 1;
__REG32 FULL         : 1;
__REG32 ENTRY_T      : 1;
__REG32 DELAY_T      : 1;
__REG32              : 4;
__REG32 IO_POINTER   : 5;
__REG32              : 3;
__REG32 DMA_POINTER  : 5;
__REG32              : 3;
__REG32 ENTRIES      : 6;
__REG32              : 2;
} __enet_txsr_bits;

/* MAC Control Register (ENET_MCR) */
typedef struct{
__REG32 RCFA  : 1;
__REG32       : 1;
__REG32 RE    : 1;
__REG32 TE    : 1;
__REG32 RVBE  : 1;
__REG32 DCE   : 1;
__REG32 BL    : 2;
__REG32 APR   : 1;
__REG32 RVFF  : 1;
__REG32 DPR   : 1;
__REG32 DBF   : 1;
__REG32 ELC   : 1;
__REG32       : 2;
__REG32 VFM   : 1;
__REG32 PWF   : 1;
__REG32 AFM   : 3;
__REG32 FDM   : 1;
__REG32 LM    : 2;
__REG32 DRO   : 1;
__REG32 PS    : 2;
__REG32       : 4;
__REG32 EN    : 1;
__REG32 RA    : 1;
} __enet_mcr_bits;

/* MII Address Register (ENET_MIIA) */
typedef struct{
__REG32 BUSY   : 1;
__REG32 WR     : 1;
__REG32 PR     : 1;
__REG32        : 3;
__REG32 RADDR  : 5;
__REG32 PADDR  : 5;
__REG32        :16;
} __enet_miia_bits;

/* MII Data Register (ENET_MIID) */
typedef struct{
__REG32 RDATA  :16;
__REG32        :16;
} __enet_miid_bits;

/* MII Control Frame Register (ENET_MCF) */
typedef struct{
__REG32 FCB    : 1;
__REG32 FCE    : 1;
__REG32 PCF    : 1;
__REG32        :13;
__REG32 PTIME  :16;
} __enet_mcf_bits;

/* VLAN1 Register (ENET_VL1) */
typedef struct{
__REG32 VLTAG1  :16;
__REG32 VLID1   :12;
__REG32         : 4;
} __enet_vl1_bits;

/* VLAN2 Register (ENET_VL2) */
typedef struct{
__REG32 VLTAG2  :16;
__REG32 VLID2   :12;
__REG32         : 4;
} __enet_vl2_bits;

/* MAC Transmission Status Register (ENET_MTS) */
typedef struct{
__REG32 FA   : 1;
__REG32      : 1;
__REG32 NC   : 1;
__REG32 LOC  : 1;
__REG32 ED   : 1;
__REG32 LC   : 1;
__REG32 EC   : 1;
__REG32 UR   : 1;
__REG32 DEF  : 1;
__REG32 LCO  : 1;
__REG32 CC   : 4;
__REG32      : 4;
__REG32 BC   :13;
__REG32 PR   : 1;
} __enet_mts_bits;

/* MAC Reception Status Register (ENET_MRS) */
typedef struct{
__REG32 FL   :11;
__REG32      : 2;
__REG32 FCI  : 1;
__REG32 WT   : 1;
__REG32 RF   : 1;
__REG32 OL   : 1;
__REG32 LC   : 1;
__REG32 FT   : 1;
__REG32 ME   : 1;
__REG32 EB   : 1;
__REG32 CE   : 1;
__REG32 VL1  : 1;
__REG32 VL2  : 1;
__REG32 LE   : 1;
__REG32 CF   : 1;
__REG32 UCF  : 1;
__REG32 MCF  : 1;
__REG32 BF   : 1;
__REG32 FF   : 1;
__REG32 PF   : 1;
__REG32 FA   : 1;
} __enet_mrs_bits;

/* Interrupt Status Register (DMA_ISR) */
typedef struct{
__REG32 IS0  : 1;
__REG32 IS1  : 1;
__REG32 IS2  : 1;
__REG32 IS3  : 1;
__REG32 IS4  : 1;
__REG32 IS5  : 1;
__REG32 IS6  : 1;
__REG32 IS7  : 1;
__REG32      :24;
} __dma_isr_bits;

/* Terminal Count Interrupt Status Register (DMA_TCISR) */
typedef struct{
__REG32 TCS0  : 1;
__REG32 TCS1  : 1;
__REG32 TCS2  : 1;
__REG32 TCS3  : 1;
__REG32 TCS4  : 1;
__REG32 TCS5  : 1;
__REG32 TCS6  : 1;
__REG32 TCS7  : 1;
__REG32       :24;
} __dma_tcisr_bits;

/* Terminal Count Interrupt Clear Register (DMA_TCICR) */
typedef struct{
__REG32 TCC0  : 1;
__REG32 TCC1  : 1;
__REG32 TCC2  : 1;
__REG32 TCC3  : 1;
__REG32 TCC4  : 1;
__REG32 TCC5  : 1;
__REG32 TCC6  : 1;
__REG32 TCC7  : 1;
__REG32       :24;
} __dma_tcicr_bits;

/* Error Interrupt Status Register (DMA_EISR) */
typedef struct{
__REG32 ES0  : 1;
__REG32 ES1  : 1;
__REG32 ES2  : 1;
__REG32 ES3  : 1;
__REG32 ES4  : 1;
__REG32 ES5  : 1;
__REG32 ES6  : 1;
__REG32 ES7  : 1;
__REG32      :24;
} __dma_eisr_bits;

/* Error Interrupt Clear Register (DMA_EICR) */
typedef struct{
__REG32 EC0  : 1;
__REG32 EC1  : 1;
__REG32 EC2  : 1;
__REG32 EC3  : 1;
__REG32 EC4  : 1;
__REG32 EC5  : 1;
__REG32 EC6  : 1;
__REG32 EC7  : 1;
__REG32      :24;
} __dma_eicr_bits;

/* Terminal Count Raw Interrupt Status Register (DMA_TCRISR) */
typedef struct{
__REG32 TCRS0  : 1;
__REG32 TCRS1  : 1;
__REG32 TCRS2  : 1;
__REG32 TCRS3  : 1;
__REG32 TCRS4  : 1;
__REG32 TCRS5  : 1;
__REG32 TCRS6  : 1;
__REG32 TCRS7  : 1;
__REG32        :24;
} __dma_tcrisr_bits;

/* Error Raw Interrupt Status Register (DMA_ERISR) */
typedef struct{
__REG32 ERS0  : 1;
__REG32 ERS1  : 1;
__REG32 ERS2  : 1;
__REG32 ERS3  : 1;
__REG32 ERS4  : 1;
__REG32 ERS5  : 1;
__REG32 ERS6  : 1;
__REG32 ERS7  : 1;
__REG32       :24;
} __dma_erisr_bits;

/* Enabled Channel Status Register (DMA_ENCSR) */
typedef struct{
__REG32 ENCS0  : 1;
__REG32 ENCS1  : 1;
__REG32 ENCS2  : 1;
__REG32 ENCS3  : 1;
__REG32 ENCS4  : 1;
__REG32 ENCS5  : 1;
__REG32 ENCS6  : 1;
__REG32 ENCS7  : 1;
__REG32        :24;
} __dma_encsr_bits;

/* Software Burst Request Register (DMA_SBRR) */
typedef struct{
__REG32 SBR0   : 1;
__REG32 SBR1   : 1;
__REG32 SBR2   : 1;
__REG32 SBR3   : 1;
__REG32 SBR4   : 1;
__REG32 SBR5   : 1;
__REG32 SBR6   : 1;
__REG32 SBR7   : 1;
__REG32 SBR8   : 1;
__REG32 SBR9   : 1;
__REG32 SBR10  : 1;
__REG32 SBR11  : 1;
__REG32 SBR12  : 1;
__REG32 SBR13  : 1;
__REG32 SBR14  : 1;
__REG32 SBR15  : 1;
__REG32        :16;
} __dma_sbrr_bits;

/* Software Single Request Register (DMA_SSRR) */
typedef struct{
__REG32 SSR0   : 1;
__REG32 SSR1   : 1;
__REG32 SSR2   : 1;
__REG32 SSR3   : 1;
__REG32 SSR4   : 1;
__REG32 SSR5   : 1;
__REG32 SSR6   : 1;
__REG32 SSR7   : 1;
__REG32 SSR8   : 1;
__REG32 SSR9   : 1;
__REG32 SSR10  : 1;
__REG32 SSR11  : 1;
__REG32 SSR12  : 1;
__REG32 SSR13  : 1;
__REG32 SSR14  : 1;
__REG32 SSR15  : 1;
__REG32        :16;
} __dma_ssrr_bits;

/* Software Last Burst Request Register (DMA_SLBR) */
typedef struct{
__REG32 SLB0   : 1;
__REG32 SLB1   : 1;
__REG32 SLB2   : 1;
__REG32 SLB3   : 1;
__REG32 SLB4   : 1;
__REG32 SLB5   : 1;
__REG32 SLB6   : 1;
__REG32 SLB7   : 1;
__REG32 SLB8   : 1;
__REG32 SLB9   : 1;
__REG32 SLB10  : 1;
__REG32 SLB11  : 1;
__REG32 SLB12  : 1;
__REG32 SLB13  : 1;
__REG32 SLB14  : 1;
__REG32 SLB15  : 1;
__REG32        :16;
} __dma_slbr_bits;

/* Software Last Single Request Register (DMA_SLSR) */
typedef struct{
__REG32 SLS0   : 1;
__REG32 SLS1   : 1;
__REG32 SLS2   : 1;
__REG32 SLS3   : 1;
__REG32 SLS4   : 1;
__REG32 SLS5   : 1;
__REG32 SLS6   : 1;
__REG32 SLS7   : 1;
__REG32 SLS8   : 1;
__REG32 SLS9   : 1;
__REG32 SLS10  : 1;
__REG32 SLS11  : 1;
__REG32 SLS12  : 1;
__REG32 SLS13  : 1;
__REG32 SLS14  : 1;
__REG32 SLS15  : 1;
__REG32        :16;
} __dma_slsr_bits;

/* Configuration Register (DMA_CNFR) */
typedef struct{
__REG32 EN  : 1;
__REG32     :31;
} __dma_cnfr_bits;

/* Synchronization Register (DMA_SYNC) */
typedef struct{
__REG32 SYNC0   : 1;
__REG32 SYNC1   : 1;
__REG32 SYNC2   : 1;
__REG32 SYNC3   : 1;
__REG32 SYNC4   : 1;
__REG32 SYNC5   : 1;
__REG32 SYNC6   : 1;
__REG32 SYNC7   : 1;
__REG32 SYNC8   : 1;
__REG32 SYNC9   : 1;
__REG32 SYNC10  : 1;
__REG32 SYNC11  : 1;
__REG32 SYNC12  : 1;
__REG32 SYNC13  : 1;
__REG32 SYNC14  : 1;
__REG32 SYNC15  : 1;
__REG32         :16;
} __dma_sync_bits;

/* Channel Linked List Item Register x (DMA_LLIx) */
typedef struct{
__REG32      : 2;
__REG32 LLI  :30;
} __dma_lli_bits;

/* Channel Control Register x (DMA_CCx) */
typedef struct{
__REG32 TRANSFERSIZE  :12;
__REG32 SBSIZE        : 3;
__REG32 DBSIZE        : 3;
__REG32 SWIDTH        : 3;
__REG32 DWIDTH        : 3;
__REG32               : 2;
__REG32 SI            : 1;
__REG32 DI            : 1;
__REG32 PROT0         : 1;
__REG32 PROT1         : 1;
__REG32 PROT2         : 1;
__REG32 TCIE          : 1;
} __dma_cc_bits;

/* Channel Configuration Register x (DMA_CCNFx) */
typedef struct{
__REG32 E               : 1;
__REG32 SrcPeripheral   : 4;
__REG32                 : 1;
__REG32 DestPeripheral  : 4;
__REG32                 : 1;
__REG32 FlowCntrl       : 3;
__REG32 IE              : 1;
__REG32 ITC             : 1;
__REG32 L               : 1;
__REG32 A               : 1;
__REG32 H               : 1;
__REG32                 :13;
} __dma_ccnf_bits;

/* Control Register 0 (SSP_CR0) */
typedef struct{
__REG16 DSS   : 4;
__REG16 FRF   : 2;
__REG16 CPOL  : 1;
__REG16 CPHA  : 1;
__REG16 SCR   : 8;
} __ssp_cr0_bits;

/* Control Register 1 (SSP_CR1) */
typedef struct{
__REG16 LBM  : 1;
__REG16 SSE  : 1;
__REG16 MS   : 1;
__REG16 SOD  : 1;
__REG16      :12;
} __ssp_cr1_bits;

/* Status Register (SSP_SR) */
typedef struct{
__REG16 TFE  : 1;
__REG16 TNF  : 1;
__REG16 RNE  : 1;
__REG16 RFF  : 1;
__REG16 BSY  : 1;
__REG16      :11;
} __ssp_sr_bits;

/* Interrupt Mask Set and Clear Register (SSP_IMSCR) */
typedef struct{
__REG16 RORIM  : 1;
__REG16 RTIM   : 1;
__REG16 RXIM   : 1;
__REG16 TXIM   : 1;
__REG16        :12;
} __ssp_imscr_bits;

/* Raw Interrupt Status Register (SSP_RISR) */
typedef struct{
__REG16 RORRIS  : 1;
__REG16 RTRIS   : 1;
__REG16 RXRIS   : 1;
__REG16 TXRIS   : 1;
__REG16         :12;
} __ssp_risr_bits;

/* Masked Interrupt Status Register (SSP_MISR) */
typedef struct{
__REG16 RORMIS  : 1;
__REG16 RTMIS   : 1;
__REG16 RXMIS   : 1;
__REG16 TXMIS   : 1;
__REG16         :12;
} __ssp_misr_bits;

/* Interrupt Clear Register (SSP_ICR) */
typedef struct{
__REG16 RORIC  : 1;
__REG16 RTIC   : 1;
__REG16        :14;
} __ssp_icr_bits;

/* DMA Control Register (SSP_DMACR) */
typedef struct{
__REG16 RXDMAE  : 1;
__REG16 TXDMAE  : 1;
__REG16         :14;
} __ssp_dmacr_bits;

/* Data Register (UART_DR) */
typedef struct{
__REG16 DATA  : 8;
__REG16 FE    : 1;
__REG16 PE    : 1;
__REG16 BE    : 1;
__REG16 OE    : 1;
__REG16       : 4;
} __uart_dr_bits;

/* Receive Status Register (UART_RSR) */
typedef struct{
__REG16 FE  : 1;
__REG16 PE  : 1;
__REG16 BF  : 1;
__REG16 OE  : 1;
__REG16     :12;
} __uart_rsr_bits;

/* Flag Register (UART_FR) */
typedef struct{
__REG16 CTS   : 1;
__REG16 DSR   : 1;
__REG16 DCD   : 1;
__REG16 BUSY  : 1;
__REG16 RXFE  : 1;
__REG16 TXFF  : 1;
__REG16 RXFF  : 1;
__REG16 TXFE  : 1;
__REG16 RI    : 1;
__REG16       : 7;
} __uart_fr_bits;

/* Fractional Baud Rate Register (UART_FBRD) */
typedef struct{
__REG16 BAUD_DIVFRAC  : 6;
__REG16               :10;
} __uart_fbrd_bits;

/* Line Control Register (UART_LCR) */
typedef struct{
__REG16 BRK   : 1;
__REG16 PEN   : 1;
__REG16 EPS   : 1;
__REG16 STP2  : 1;
__REG16 FEN   : 1;
__REG16 WLEN  : 2;
__REG16 SPS   : 1;
__REG16       : 8;
} __uart_lcr_bits;

/* Control Register (UART_CR) */
typedef struct{
__REG16 UARTEN  : 1;
__REG16 SIREN   : 1;
__REG16 SIRLP   : 1;
__REG16         : 4;
__REG16 LBE     : 1;
__REG16 TXE     : 1;
__REG16 RXE     : 1;
__REG16 DTR     : 1;
__REG16 RTS     : 1;
__REG16         : 2;
__REG16 RTSEN   : 1;
__REG16 CTSEN   : 1;
} __uart_cr_bits;

/* Interrupt FIFO Level Select Register (UART_IFLS) */
typedef struct{
__REG16 TXIFLSEL  : 3;
__REG16 RXIFLSEL  : 3;
__REG16           :10;
} __uart_ifls_bits;

/* Interrupt Mask Set/Clear Register (UART_IMSC) */
typedef struct{
__REG16 RIIM   : 1;
__REG16 CTSIM  : 1;
__REG16 DCDIM  : 1;
__REG16 DSRIM  : 1;
__REG16 RXIM   : 1;
__REG16 TXIM   : 1;
__REG16 RTIM   : 1;
__REG16 FEIM   : 1;
__REG16 PEIM   : 1;
__REG16 BEIM   : 1;
__REG16 OEIM   : 1;
__REG16        : 5;
} __uart_imsc_bits;

/* Raw Interrupt Status Register (UART_RIS) */
typedef struct{
__REG16 RIRIS   : 1;
__REG16 CTSRIS  : 1;
__REG16 DCDRIS  : 1;
__REG16 DSRRIS  : 1;
__REG16 RXRIS   : 1;
__REG16 TXRIS   : 1;
__REG16 RTRIS   : 1;
__REG16 FERIS   : 1;
__REG16 PERIS   : 1;
__REG16 BERIS   : 1;
__REG16 OERIS   : 1;
__REG16         : 5;
} __uart_ris_bits;

/* Masked Interrupt Status Register (UART_MIS) */
typedef struct{
__REG16 RIMIS   : 1;
__REG16 CTSMIS  : 1;
__REG16 DCDMIS  : 1;
__REG16 DSRMIS  : 1;
__REG16 RXMIS   : 1;
__REG16 TXMIS   : 1;
__REG16 RTMIS   : 1;
__REG16 FEMIS   : 1;
__REG16 PEMIS   : 1;
__REG16 BEMIS   : 1;
__REG16 OEMIS   : 1;
__REG16         : 5;
} __uart_mis_bits;

/* Interrupt Clear Register (UART_ICR) */
typedef struct{
__REG16 RIIC   : 1;
__REG16 CTSIC  : 1;
__REG16 DCDIC  : 1;
__REG16 DSRIC  : 1;
__REG16 RXIC   : 1;
__REG16 TXIC   : 1;
__REG16 RTIC   : 1;
__REG16 FEIC   : 1;
__REG16 PEIC   : 1;
__REG16 BEIC   : 1;
__REG16 OEIC   : 1;
__REG16        : 5;
} __uart_icr_bits;

/* DMA Control Register (UART_DMACR) */
typedef struct{
__REG16 RXDMAE    : 1;
__REG16 TXDMAE    : 1;
__REG16 DMAONERR  : 1;
__REG16           :13;
} __uart_dmacr_bits;

/* I2C Control Register (I2Cn_CR) */
typedef struct{
__REG8  ITE    : 1;
__REG8  STOP   : 1;
__REG8  ACK    : 1;
__REG8  START  : 1;
__REG8  ENGC   : 1;
__REG8  PE     : 1;
__REG8         : 2;
} __i2c_cr_bits;

/* I2C Status Register 1 (I2Cn_SR1) */
typedef struct{
__REG8  SB     : 1;
__REG8  M_SL   : 1;
__REG8  ADSL   : 1;
__REG8  BTF    : 1;
__REG8  BUSY   : 1;
__REG8  TRA    : 1;
__REG8  ADD10  : 1;
__REG8  EVF    : 1;
} __i2c_sr1_bits;

/* I2C Status Register 2 (I2Cn_SR2) */
typedef struct{
__REG8  GCAL   : 1;
__REG8  BERR   : 1;
__REG8  ARLO   : 1;
__REG8  STOPF  : 1;
__REG8  AF     : 1;
__REG8  ENDAD  : 1;
__REG8         : 2;
} __i2c_sr2_bits;

/* I2C Clock Control Register (I2Cn_CCR) */
typedef struct{
__REG8  CC     : 7;
__REG8  FM_SM  : 1;
} __i2c_ccr_bits;

/* I2C Extended Clock Control Register (I2Cn_ECCR) */
typedef struct{
__REG8  CC  : 5;
__REG8      : 3;
} __i2c_eccr_bits;

/* I2C Own Address Register 2 (I2Cn_OAR2) */
typedef struct{
__REG8       : 1;
__REG8  ADD  : 2;
__REG8       : 2;
__REG8  FR   : 3;
} __i2c_oar2_bits;

/* Interrupt pending register (MC_IPR) */
typedef struct{
__REG16 CMPW  : 1;
__REG16 CMPV  : 1;
__REG16 CMPU  : 1;
__REG16 ZPC   : 1;
__REG16 ADT   : 1;
__REG16 OTC   : 1;
__REG16 CPT   : 1;
__REG16 CM0   : 1;
__REG16 EST   : 1;
__REG16       : 7;
} __mc_ipr_bits;

/* Tacho prescaler register (MC_TPRS) */
typedef struct{
__REG16 TPRS  :12;
__REG16       : 4;
} __mc_tprs_bits;

/* Compare phase W preload register (MC_CMPW) */
typedef struct{
__REG16 CMPW  :11;
__REG16       : 5;
} __mc_cmpw_bits;

/* Compare phase V preload register (MC_CMPV) */
typedef struct{
__REG16 CMPV  :11;
__REG16       : 5;
} __mc_cmpv_bits;

/* Compare phase U preload register (MC_CMPU) */
typedef struct{
__REG16 CMPU  :11;
__REG16       : 5;
} __mc_cmpu_bits;

/* Compare 0 preload register (MC_CMP0) */
typedef struct{
__REG16 CMP0  :10;
__REG16       : 6;
} __mc_cmp0_bits;

/* Peripheral control register 0 (MC_PCR0) */
typedef struct{
__REG16 ODCS  : 1;
__REG16 UDCS  : 1;
__REG16 CMS   : 1;
__REG16 CPC   : 1;
__REG16 CTC   : 1;
__REG16 PCE   : 1;
__REG16 TCE   : 1;
__REG16 DTE   : 1;
__REG16       : 8;
} __mc_pcr0_bits;

/* Peripheral control register 1 (MC_PCR1) */
typedef struct{
__REG16 TIN    : 2;
__REG16 TCB    : 1;
__REG16 STC    : 1;
__REG16 TES    : 1;
__REG16 CCPT   : 1;
__REG16 DISEST : 1;
__REG16        : 9;
} __mc_pcr1_bits;

/* Peripheral control register 2 (MC_PCR2) */
typedef struct{
__REG16 DTS   : 1;
__REG16 SDT   : 1;
__REG16 C0SE  : 1;
__REG16 CUSE  : 1;
__REG16 CVSE  : 1;
__REG16 CWSE  : 1;
__REG16 RSE   : 1;
__REG16 GPIE  : 1;
__REG16       : 8;
} __mc_pcr2_bits;

/* Polarity selection register (MC_PSR) */
typedef struct{
__REG16 PWL   : 1;
__REG16 PWH   : 1;
__REG16 PVL   : 1;
__REG16 PVH   : 1;
__REG16 PUL   : 1;
__REG16 PUH   : 1;
__REG16 UDIS  : 1;
__REG16       : 9;
} __mc_psr_bits;

/* Output peripheral register (MC_OPR) */
typedef struct{
__REG16 WL   : 1;
__REG16 WH   : 1;
__REG16 VL   : 1;
__REG16 VH   : 1;
__REG16 UL   : 1;
__REG16 UH   : 1;
__REG16 ODS  : 1;
__REG16      : 9;
} __mc_opr_bits;

/* Interrupt mask register (MC_IMR) */
typedef struct{
__REG16 CMPWE  : 1;
__REG16 CMPVE  : 1;
__REG16 CMPUE  : 1;
__REG16 ZPCE   : 1;
__REG16 ADTE   : 1;
__REG16 OTCE   : 1;
__REG16 CPTE   : 1;
__REG16 CM0E   : 1;
__REG16        : 8;
} __mc_imr_bits;

/* Dead time generator register (MC_DTG) */
typedef struct{
__REG16 DTG  : 6;
__REG16      :10;
} __mc_dtg_bits;

/* CAN control register (CAN_CR) */
typedef struct{
__REG16 INIT  : 1;
__REG16 IE    : 1;
__REG16 SIE   : 1;
__REG16 EIE   : 1;
__REG16       : 1;
__REG16 DAR   : 1;
__REG16 CCE   : 1;
__REG16 TEST  : 1;
__REG16       : 8;
} __can_cr_bits;

/* Status register (CAN_SR) */
typedef struct{
__REG16 LEC    : 3;
__REG16 TXOK   : 1;
__REG16 RXOK   : 1;
__REG16 EPASS  : 1;
__REG16 EWARN  : 1;
__REG16 BOFF   : 1;
__REG16        : 8;
} __can_sr_bits;

/* Error counter (CAN_ERR) */
typedef struct{
__REG16 TEC  : 8;
__REG16 REC  : 7;
__REG16 RP   : 1;
} __can_err_bits;

/* Bit timing register (CAN_BTR) */
typedef struct{
__REG16 BRP    : 6;
__REG16 SJW    : 2;
__REG16 TSEG1  : 4;
__REG16 TSEG2  : 3;
__REG16        : 1;
} __can_btr_bits;

/* Test register (CAN_TESTR) */
typedef struct{
__REG16         : 2;
__REG16 BASIC   : 1;
__REG16 SILENT  : 1;
__REG16 LBACK   : 1;
__REG16 TX      : 2;
__REG16 RX      : 1;
__REG16         : 8;
} __can_testr_bits;

/* BRP extension register (CAN_BRPR) */
typedef struct{
__REG16 BRPE  : 4;
__REG16       :12;
} __can_brpr_bits;

/* IFn command request registers (CAN_IFn_CRR) */
typedef struct{
__REG16 MN    : 6;
__REG16       : 9;
__REG16 BUSY  : 1;
} __can_if_crr_bits;

/* IFn command mask registers (CAN_IFn_CMR) */
typedef struct{
__REG16 DATAB      : 1;
__REG16 DATAA      : 1;
__REG16 TXRQST     : 1;
__REG16 CLRINTPND  : 1;
__REG16 CONTROL    : 1;
__REG16 ARB        : 1;
__REG16 MASK       : 1;
__REG16 RW         : 1;
__REG16            : 8;
} __can_if_cmr_bits;

/* IFn mask 2 register (CAN_IFn_M2R) */
typedef struct{
__REG16 MSK   :13;
__REG16       : 1;
__REG16 MDIR  : 1;
__REG16 MXTD  : 1;
} __can_if_m2r_bits;

/* IFn message arbitration 2 register (CAN_IFn_A2R) */
typedef struct{
__REG16 ID      :13;
__REG16 DIR     : 1;
__REG16 XTD     : 1;
__REG16 MSGVAL  : 1;
} __can_if_a2r_bits;

/* IFn message control registers (CAN_IFn_MCR) */
typedef struct{
__REG16 DLC     : 4;
__REG16         : 3;
__REG16 EOB     : 1;
__REG16 TXRQST  : 1;
__REG16 RMTEN   : 1;
__REG16 RXIE    : 1;
__REG16 TXIE    : 1;
__REG16 UMASK   : 1;
__REG16 INTPND  : 1;
__REG16 MSGLST  : 1;
__REG16 NEWDAT  : 1;
} __can_if_mcr_bits;

/* IFn data A registers (CAN_IF_DA1R) */
typedef struct{
__REG16 DATA0  : 8;
__REG16 DATA1  : 8;
} __can_if_da1r_bits;

/* IFn data A registers (CAN_IF_DA2R) */
typedef struct{
__REG16 DATA2  : 8;
__REG16 DATA3  : 8;
} __can_if_da2r_bits;

/* IFn data B registers (CAN_IF_DB1R) */
typedef struct{
__REG16 DATA4  : 8;
__REG16 DATA5  : 8;
} __can_if_db1r_bits;

/* IFn data B registers (CAN_IF_DB2R) */
typedef struct{
__REG16 DATA6  : 8;
__REG16 DATA7  : 8;
} __can_if_db2r_bits;

/* USB control register (USB_CNTR) */
typedef struct{
__REG16 FRES     : 1;
__REG16 PDWN     : 1;
__REG16 LP_MODE  : 1;
__REG16 FSUSP    : 1;
__REG16 RESUME   : 1;
__REG16          : 2;
__REG16 SZDPRM   : 1;
__REG16 ESOFM    : 1;
__REG16 SOFM     : 1;
__REG16 RESETM   : 1;
__REG16 SUSPM    : 1;
__REG16 WKUPM    : 1;
__REG16 ERRM     : 1;
__REG16 DOVRM    : 1;
__REG16 CTRM     : 1;
} __usb_cntr_bits;

/* USB Interrupt Status Register (USB_ISTR) */
typedef struct{
__REG16 EP_ID  : 4;
__REG16 DIR    : 1;
__REG16        : 2;
__REG16 SZDPR  : 1;
__REG16 ESOF   : 1;
__REG16 SOF    : 1;
__REG16 RESET  : 1;
__REG16 SUSP   : 1;
__REG16 WKUP   : 1;
__REG16 ERR    : 1;
__REG16 DOVR   : 1;
__REG16 CTR    : 1;
} __usb_st_bits;

/* USB Frame Number Register (USB_FNR) */
typedef struct{
__REG16 FN    :11;
__REG16 LSOF  : 2;
__REG16 LCK   : 1;
__REG16 RXDM  : 1;
__REG16 RXDP  : 1;
} __usb_fnr_bits;

/* USB device address (USB_DADDR) */
typedef struct{
__REG16 ADD  : 7;
__REG16 EF   : 1;
__REG16      : 8;
} __usb_daddr_bits;

/* Buffer table address (USB_BTABLE) */
typedef struct{
__REG16         : 3;
__REG16 BTABLE  :13;
} __usb_btable_bits;

/* USB Endpoint n Register (USB_EPnR) */
typedef struct{
__REG16 EA       : 4;
__REG16 STAT_TX  : 2;
__REG16 DTOG_TX  : 1;
__REG16 CTR_TX   : 1;
__REG16 EP_KIND  : 1;
__REG16 EP_TYPE  : 2;
__REG16 SETUP    : 1;
__REG16 STAT_RX  : 2;
__REG16 DTOG_RX  : 1;
__REG16 CTR_RX   : 1;
} __usb_epr_bits;

/* DMA control register 1 (USB_DMACR1) */
typedef struct{
__REG16 DMA_UNLK_RK_EN  :10;
__REG16                 : 6;
} __usb_dmacr1_bits;

/* DMA control register 2 (USB_DMACR2) */
typedef struct{
__REG16 UNLNK_TX_EP_ID1  : 4;
__REG16 UNLNK_TX_EP_ID2  : 4;
__REG16 UNLNK_TX_EP_ID3  : 4;
__REG16 DMA_UNLK_TX_EN   : 2;
__REG16                  : 2;
} __usb_dmacr2_bits;

/* DMA control register 3 (USB_DMACR3) */
typedef struct{
__REG16 LK_TX_EN      : 1;
__REG16 LK_TX_EP_ID   : 4;
__REG16 DMA_LK_TX_EN  : 1;
__REG16 SLE           : 1;
__REG16               : 1;
__REG16 LK_RX_EN      : 1;
__REG16 LK_RX_EP_ID   : 4;
__REG16 DMA_LK_RX_EN  : 1;
__REG16 SR_TX         : 1;
__REG16 SR_RX         : 1;
} __usb_dmacr3_bits;

/* DMA burst size register (USB_DMABSIZE) */
typedef struct{
__REG16 SBSIZE           : 3;
__REG16                  : 1;
__REG16 DBSIZE           : 3;
__REG16                  : 1;
__REG16 LLI_RX_NPACKETS  : 8;
} __usb_dmabsize_bits;

/* DMA LLI register (USB_DMALLI) */
typedef struct{
__REG16 LLI_TX_LNG  : 8;
__REG16 LLI_RX_LNG  : 8;
} __usb_dmalli_bits;

/* ADC Control Register (ADC_CR) */
typedef struct{
__REG16 STR   : 1;
__REG16 POR   : 1;
__REG16       : 1;
__REG16 STB   : 1;
__REG16 CONT  : 1;
__REG16 SCE   : 1;
__REG16 SC    : 3;
__REG16 AWDI  : 1;
__REG16 ECVI  : 1;
__REG16       : 3;
__REG16 AWD   : 1;
__REG16 ECV   : 1;
} __adc_cr_bits;

/* Channel Configuration Register (ADC_CCR) */
typedef struct{
__REG16 CC0  : 2;
__REG16 CC1  : 2;
__REG16 CC2  : 2;
__REG16 CC3  : 2;
__REG16 CC4  : 2;
__REG16 CC5  : 2;
__REG16 CC6  : 2;
__REG16 CC7  : 2;
} __adc_ccr_bits;

/* Low Threshold Register (ADC_LTR) */
typedef struct{
__REG16 LT  :10;
__REG16     : 6;
} __adc_ltr_bits;

/* High Threshold Register (ADC_HTR) */
typedef struct{
__REG16 HT  :10;
__REG16     : 6;
} __adc_htr_bits;

/* Compare Result Register (ADC_CRR) */
typedef struct{
__REG16 CR0  : 1;
__REG16 CR1  : 1;
__REG16 CR2  : 1;
__REG16 CR3  : 1;
__REG16 CR4  : 1;
__REG16 CR5  : 1;
__REG16 CR6  : 1;
__REG16 CR7  : 1;
__REG16      : 8;
} __adc_crr_bits;

/* ADC Data Register (ADC_DRx) */
typedef struct{
__REG16 CDATA  :10;
__REG16        : 5;
__REG16 OV     : 1;
} __adc_dr_bits;

/* Bridge Status Register (APB_BSR) */
typedef struct{
__REG32 ERROR  : 1;
__REG32        : 3;
__REG32 OUTM   : 1;
__REG32 APBT   : 1;
__REG32        :26;
} __apb_bsr_bits;

/* Bridge Configuration Register (APB_BCR) */
typedef struct{
__REG32 TOUT_CNT   : 5;
__REG32            : 3;
__REG32 ERREN      : 1;
__REG32            : 7;
__REG32 SPLIT_CNT  : 5;
__REG32            : 3;
__REG32 SPLITEN    : 1;
__REG32            : 7;
} __apb_bcr_bits;

/* Peripheral Address Register (APB_PAER) */
typedef struct{
__REG32 PERIPHERAL_ADDRESS  :24;
__REG32 RW                  : 1;
__REG32                     : 7;
} __apb_paer_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */
/***************************************************************************/
/* Common declarations  ****************************************************/
/***************************************************************************
 **
 ** FMI
 **
 ***************************************************************************/
__IO_REG32_BIT(FMI_BBSR,            0x54000000,__READ_WRITE ,__fmi_bbsr_bits);
__IO_REG32_BIT(FMI_NBBSR,           0x54000004,__READ_WRITE ,__fmi_nbbsr_bits);
__IO_REG32_BIT(FMI_BBADR,           0x5400000C,__READ_WRITE ,__fmi_bbadr_bits);
__IO_REG32_BIT(FMI_NBBADR,          0x54000010,__READ_WRITE ,__fmi_nbbadr_bits);
__IO_REG32_BIT(FMI_CR,              0x54000018,__READ_WRITE ,__fmi_cr_bits);
__IO_REG32_BIT(FMI_SR,              0x5400001C,__READ_WRITE ,__fmi_sr_bits);
__IO_REG32_BIT(FMI_BCE5ADDR,        0x54000020,__READ_WRITE ,__fmi_bce5addr_bits);

/***************************************************************************
 **
 ** FMI Buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(FMI_BBSR_BUF,        0x44000000,__READ_WRITE ,__fmi_bbsr_bits);
__IO_REG32_BIT(FMI_NBBSR_BUF,       0x44000004,__READ_WRITE ,__fmi_nbbsr_bits);
__IO_REG32_BIT(FMI_BBADR_BUF,       0x4400000C,__READ_WRITE ,__fmi_bbadr_bits);
__IO_REG32_BIT(FMI_NBBADR_BUF,      0x44000010,__READ_WRITE ,__fmi_nbbadr_bits);
__IO_REG32_BIT(FMI_CR_BUF,          0x44000018,__READ_WRITE ,__fmi_cr_bits);
__IO_REG32_BIT(FMI_SR_BUF,          0x4400001C,__READ_WRITE ,__fmi_sr_bits);
__IO_REG32_BIT(FMI_BCE5ADDR_BUF,    0x44000020,__READ_WRITE ,__fmi_bce5addr_bits);

/***************************************************************************
 **
 ** EMI
 **
 ***************************************************************************/
__IO_REG32_BIT(EMI_ICR1,            0x74000000,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR1,            0x74000004,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR1,            0x74000008,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR1,           0x7400000C,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR1,           0x74000010,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR1,            0x74000014,__READ_WRITE,__emi_bcr_bits);
__IO_REG32_BIT(EMI_ICR2,            0x74000020,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR2,            0x74000024,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR2,            0x74000028,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR2,           0x7400002C,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR2,           0x74000030,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR2,            0x74000034,__READ_WRITE,__emi_bcr_bits);
__IO_REG32_BIT(EMI_ICR3,            0x74000040,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR3,            0x74000044,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR3,            0x74000048,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR3,           0x7400004C,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR3,           0x74000050,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR3,            0x74000054,__READ_WRITE,__emi_bcr_bits);
__IO_REG32_BIT(EMI_ICR0,            0x740000E0,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR0,            0x740000E4,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR0,            0x740000E8,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR0,           0x740000EC,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR0,           0x740000F0,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR0,            0x740000F4,__READ_WRITE,__emi_bcr_bits);

/***************************************************************************
 **
 ** EMI Buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(EMI_ICR1_BUF,        0x64000000,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR1_BUF,        0x64000004,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR1_BUF,        0x64000008,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR1_BUF,       0x6400000C,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR1_BUF,       0x64000010,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR1_BUF,        0x64000014,__READ_WRITE,__emi_bcr_bits);
__IO_REG32_BIT(EMI_ICR2_BUF,        0x64000020,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR2_BUF,        0x64000024,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR2_BUF,        0x64000028,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR2_BUF,       0x6400002C,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR2_BUF,       0x64000030,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR2_BUF,        0x64000034,__READ_WRITE,__emi_bcr_bits);
__IO_REG32_BIT(EMI_ICR3_BUF,        0x64000040,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR3_BUF,        0x64000044,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR3_BUF,        0x64000048,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR3_BUF,       0x6400004C,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR3_BUF,       0x64000050,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR3_BUF,        0x64000054,__READ_WRITE,__emi_bcr_bits);
__IO_REG32_BIT(EMI_ICR0_BUF,        0x640000E0,__READ_WRITE,__emi_icr_bits);
__IO_REG32_BIT(EMI_RCR0_BUF,        0x640000E4,__READ_WRITE,__emi_rcr_bits);
__IO_REG32_BIT(EMI_WCR0_BUF,        0x640000E8,__READ_WRITE,__emi_wcr_bits);
__IO_REG32_BIT(EMI_OECR0_BUF,       0x640000EC,__READ_WRITE,__emi_oecr_bits);
__IO_REG32_BIT(EMI_WECR0_BUF,       0x640000F0,__READ_WRITE,__emi_wecr_bits);
__IO_REG32_BIT(EMI_BCR0_BUF,        0x640000F4,__READ_WRITE,__emi_bcr_bits);

/***************************************************************************
 **
 ** SCU
 **
 ***************************************************************************/
__IO_REG32_BIT(SCU_CLKCNTR,         0x5C002000,__READ_WRITE,__scu_clkcntr_bits);
__IO_REG32_BIT(SCU_PLLCONF,         0x5C002004,__READ_WRITE,__scu_pllconf_bits);
__IO_REG32_BIT(SCU_SYSSTATUS,       0x5C002008,__READ_WRITE,__scu_sysstatus_bits);
__IO_REG32_BIT(SCU_PWRMNG,          0x5C00200C,__READ_WRITE,__scu_pwrmng_bits);
__IO_REG32_BIT(SCU_ITCMSK,          0x5C002010,__READ_WRITE,__scu_itcmsk_bits);
__IO_REG32_BIT(SCU_PCGR0,           0x5C002014,__READ_WRITE,__scu_pcgr0_bits);
__IO_REG32_BIT(SCU_PCGR1,           0x5C002018,__READ_WRITE,__scu_pcgr1_bits);
__IO_REG32_BIT(SCU_PRR0,            0x5C00201C,__READ_WRITE,__scu_prr0_bits);
__IO_REG32_BIT(SCU_PRR1,            0x5C002020,__READ_WRITE,__scu_prr1_bits);
__IO_REG32_BIT(SCU_MGR0,            0x5C002024,__READ_WRITE,__scu_mgr0_bits);
__IO_REG32_BIT(SCU_MGR1,            0x5C002028,__READ_WRITE,__scu_mgr1_bits);
__IO_REG32_BIT(SCU_PECGR0,          0x5C00202C,__READ_WRITE,__scu_pcgr0_bits);
__IO_REG32_BIT(SCU_PECGR1,          0x5C002030,__READ_WRITE,__scu_pecgr1_bits);
__IO_REG32_BIT(SCU_SCR0,            0x5C002034,__READ_WRITE,__scu_scr0_bits);
__IO_REG16(    SCU_SCR1,            0x5C002038,__READ_WRITE);
__IO_REG16(    SCU_SCR2,            0x5C00203C,__READ_WRITE);
__IO_REG32_BIT(SCU_GPIOOUT0,        0x5C002044,__READ_WRITE,__scu_gpioout0_bits);
__IO_REG32_BIT(SCU_GPIOOUT1,        0x5C002048,__READ_WRITE,__scu_gpioout1_bits);
__IO_REG32_BIT(SCU_GPIOOUT2,        0x5C00204C,__READ_WRITE,__scu_gpioout2_bits);
__IO_REG32_BIT(SCU_GPIOOUT3,        0x5C002050,__READ_WRITE,__scu_gpioout3_bits);
__IO_REG32_BIT(SCU_GPIOOUT4,        0x5C002054,__READ_WRITE,__scu_gpioout4_bits);
__IO_REG32_BIT(SCU_GPIOOUT5,        0x5C002058,__READ_WRITE,__scu_gpioout5_bits);
__IO_REG32_BIT(SCU_GPIOOUT6,        0x5C00205C,__READ_WRITE,__scu_gpioout6_bits);
__IO_REG32_BIT(SCU_GPIOOUT7,        0x5C002060,__READ_WRITE,__scu_gpioout7_bits);
__IO_REG32_BIT(SCU_GPIOIN0,         0x5C002064,__READ_WRITE,__scu_gpioin0_bits);
__IO_REG32_BIT(SCU_GPIOIN1,         0x5C002068,__READ_WRITE,__scu_gpioin1_bits);
__IO_REG32_BIT(SCU_GPIOIN2,         0x5C00206C,__READ_WRITE,__scu_gpioin2_bits);
__IO_REG32_BIT(SCU_GPIOIN3,         0x5C002070,__READ_WRITE,__scu_gpioin3_bits);
__IO_REG32_BIT(SCU_GPIOIN4,         0x5C002074,__READ_WRITE,__scu_gpioin4_bits);
__IO_REG32_BIT(SCU_GPIOIN5,         0x5C002078,__READ_WRITE,__scu_gpioin5_bits);
__IO_REG32_BIT(SCU_GPIOIN6,         0x5C00207C,__READ_WRITE,__scu_gpioin6_bits);
__IO_REG32_BIT(SCU_GPIOIN7,         0x5C002080,__READ_WRITE,__scu_gpioin7_bits);
__IO_REG32_BIT(SCU_GPIOTYPE0,       0x5C002084,__READ_WRITE,__scu_gpiotype0_bits);
__IO_REG32_BIT(SCU_GPIOTYPE1,       0x5C002088,__READ_WRITE,__scu_gpiotype1_bits);
__IO_REG32_BIT(SCU_GPIOTYPE2,       0x5C00208C,__READ_WRITE,__scu_gpiotype2_bits);
__IO_REG32_BIT(SCU_GPIOTYPE3,       0x5C002090,__READ_WRITE,__scu_gpiotype3_bits);
__IO_REG32_BIT(SCU_GPIOTYPE4,       0x5C002094,__READ_WRITE,__scu_gpiotype4_bits);
__IO_REG32_BIT(SCU_GPIOTYPE5,       0x5C002098,__READ_WRITE,__scu_gpiotype5_bits);
__IO_REG32_BIT(SCU_GPIOTYPE6,       0x5C00209C,__READ_WRITE,__scu_gpiotype6_bits);
__IO_REG32_BIT(SCU_GPIOTYPE7,       0x5C0020A0,__READ_WRITE,__scu_gpiotype7_bits);
__IO_REG32_BIT(SCU_GPIOTYPE8,       0x5C0020A4,__READ_WRITE,__scu_gpiotype8_bits);
__IO_REG32_BIT(SCU_GPIOTYPE9,       0x5C0020A8,__READ_WRITE,__scu_gpiotype9_bits);
__IO_REG32_BIT(SCU_EMI,             0x5C0020AC,__READ_WRITE,__scu_emi_bits);
__IO_REG32_BIT(SCU_WKUPSEL,         0x5C0020B0,__READ_WRITE,__scu_wkupsel_bits);
__IO_REG32_BIT(SCU_GPIOANA,         0x5C0020BC,__READ_WRITE,__scu_gpioana_bits);

/***************************************************************************
 **
 ** SCU Buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(SCU_CLKCNTR_BUF,     0x4C002000,__READ_WRITE,__scu_clkcntr_bits);
__IO_REG32_BIT(SCU_PLLCONF_BUF,     0x4C002004,__READ_WRITE,__scu_pllconf_bits);
__IO_REG32_BIT(SCU_SYSSTATUS_BUF,   0x4C002008,__READ_WRITE,__scu_sysstatus_bits);
__IO_REG32_BIT(SCU_PWRMNG_BUF,      0x4C00200C,__READ_WRITE,__scu_pwrmng_bits);
__IO_REG32_BIT(SCU_ITCMSK_BUF,      0x4C002010,__READ_WRITE,__scu_itcmsk_bits);
__IO_REG32_BIT(SCU_PCGR0_BUF,       0x4C002014,__READ_WRITE,__scu_pcgr0_bits);
__IO_REG32_BIT(SCU_PCGR1_BUF,       0x4C002018,__READ_WRITE,__scu_pcgr1_bits);
__IO_REG32_BIT(SCU_PRR0_BUF,        0x4C00201C,__READ_WRITE,__scu_prr0_bits);
__IO_REG32_BIT(SCU_PRR1_BUF,        0x4C002020,__READ_WRITE,__scu_prr1_bits);
__IO_REG32_BIT(SCU_MGR0_BUF,        0x4C002024,__READ_WRITE,__scu_mgr0_bits);
__IO_REG32_BIT(SCU_MGR1_BUF,        0x4C002028,__READ_WRITE,__scu_mgr1_bits);
__IO_REG32_BIT(SCU_PECGR0_BUF,      0x4C00202C,__READ_WRITE,__scu_pcgr0_bits);
__IO_REG32_BIT(SCU_PECGR1_BUF,      0x4C002030,__READ_WRITE,__scu_pecgr1_bits);
__IO_REG32_BIT(SCU_SCR0_BUF,        0x4C002034,__READ_WRITE,__scu_scr0_bits);
__IO_REG16(    SCU_SCR1_BUF,        0x4C002038,__READ_WRITE);
__IO_REG16(    SCU_SCR2_BUF,        0x4C00203C,__READ_WRITE);
__IO_REG32_BIT(SCU_GPIOOUT0_BUF,    0x4C002044,__READ_WRITE,__scu_gpioout0_bits);
__IO_REG32_BIT(SCU_GPIOOUT1_BUF,    0x4C002048,__READ_WRITE,__scu_gpioout1_bits);
__IO_REG32_BIT(SCU_GPIOOUT2_BUF,    0x4C00204C,__READ_WRITE,__scu_gpioout2_bits);
__IO_REG32_BIT(SCU_GPIOOUT3_BUF,    0x4C002050,__READ_WRITE,__scu_gpioout3_bits);
__IO_REG32_BIT(SCU_GPIOOUT4_BUF,    0x4C002054,__READ_WRITE,__scu_gpioout4_bits);
__IO_REG32_BIT(SCU_GPIOOUT5_BUF,    0x4C002058,__READ_WRITE,__scu_gpioout5_bits);
__IO_REG32_BIT(SCU_GPIOOUT6_BUF,    0x4C00205C,__READ_WRITE,__scu_gpioout6_bits);
__IO_REG32_BIT(SCU_GPIOOUT7_BUF,    0x4C002060,__READ_WRITE,__scu_gpioout7_bits);
__IO_REG32_BIT(SCU_GPIOIN0_BUF,     0x4C002064,__READ_WRITE,__scu_gpioin0_bits);
__IO_REG32_BIT(SCU_GPIOIN1_BUF,     0x4C002068,__READ_WRITE,__scu_gpioin1_bits);
__IO_REG32_BIT(SCU_GPIOIN2_BUF,     0x4C00206C,__READ_WRITE,__scu_gpioin2_bits);
__IO_REG32_BIT(SCU_GPIOIN3_BUF,     0x4C002070,__READ_WRITE,__scu_gpioin3_bits);
__IO_REG32_BIT(SCU_GPIOIN4_BUF,     0x4C002074,__READ_WRITE,__scu_gpioin4_bits);
__IO_REG32_BIT(SCU_GPIOIN5_BUF,     0x4C002078,__READ_WRITE,__scu_gpioin5_bits);
__IO_REG32_BIT(SCU_GPIOIN6_BUF,     0x4C00207C,__READ_WRITE,__scu_gpioin6_bits);
__IO_REG32_BIT(SCU_GPIOIN7_BUF,     0x4C002080,__READ_WRITE,__scu_gpioin7_bits);
__IO_REG32_BIT(SCU_GPIOTYPE0_BUF,   0x4C002084,__READ_WRITE,__scu_gpiotype0_bits);
__IO_REG32_BIT(SCU_GPIOTYPE1_BUF,   0x4C002088,__READ_WRITE,__scu_gpiotype1_bits);
__IO_REG32_BIT(SCU_GPIOTYPE2_BUF,   0x4C00208C,__READ_WRITE,__scu_gpiotype2_bits);
__IO_REG32_BIT(SCU_GPIOTYPE3_BUF,   0x4C002090,__READ_WRITE,__scu_gpiotype3_bits);
__IO_REG32_BIT(SCU_GPIOTYPE4_BUF,   0x4C002094,__READ_WRITE,__scu_gpiotype4_bits);
__IO_REG32_BIT(SCU_GPIOTYPE5_BUF,   0x4C002098,__READ_WRITE,__scu_gpiotype5_bits);
__IO_REG32_BIT(SCU_GPIOTYPE6_BUF,   0x4C00209C,__READ_WRITE,__scu_gpiotype6_bits);
__IO_REG32_BIT(SCU_GPIOTYPE7_BUF,   0x4C0020A0,__READ_WRITE,__scu_gpiotype7_bits);
__IO_REG32_BIT(SCU_GPIOTYPE8_BUF,   0x4C0020A4,__READ_WRITE,__scu_gpiotype8_bits);
__IO_REG32_BIT(SCU_GPIOTYPE9_BUF,   0x4C0020A8,__READ_WRITE,__scu_gpiotype9_bits);
__IO_REG32_BIT(SCU_EMI_BUF,         0x4C0020AC,__READ_WRITE,__scu_emi_bits);
__IO_REG32_BIT(SCU_WKUPSEL_BUF,     0x4C0020B0,__READ_WRITE,__scu_wkupsel_bits);
__IO_REG32_BIT(SCU_GPIOANA_BUF,     0x4C0020BC,__READ_WRITE,__scu_gpioana_bits);

/***************************************************************************
 **
 ** GPIO
 **
 ***************************************************************************/
__IO_REG8_BIT( GPIO0_DATA,          0x580063FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO0_DIR,           0x58006400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO0_SEL,           0x58006420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO1_DATA,          0x580073FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO1_DIR,           0x58007400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO1_SEL,           0x58007420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO2_DATA,          0x580083FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO2_DIR,           0x58008400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO2_SEL,           0x58008420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO3_DATA,          0x580093FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO3_DIR,           0x58009400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO3_SEL,           0x58009420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO4_DATA,          0x5800A3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO4_DIR,           0x5800A400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO4_SEL,           0x5800A420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO5_DATA,          0x5800B3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO5_DIR,           0x5800B400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO5_SEL,           0x5800B420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO6_DATA,          0x5800C3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO6_DIR,           0x5800C400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO6_SEL,           0x5800C420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO7_DATA,          0x5800D3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO7_DIR,           0x5800D400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO7_SEL,           0x5800D420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO8_DATA,          0x5800E3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO8_DIR,           0x5800E400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO8_SEL,           0x5800E420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO9_DATA,          0x5800F3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO9_DIR,           0x5800F400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO9_SEL,           0x5800F420,__READ_WRITE,__BITS8);

/***************************************************************************
 **
 ** GPIO buffered
 **
 ***************************************************************************/
__IO_REG8_BIT( GPIO0_DATA_BUF,      0x480063FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO0_DIR_BUF,       0x48006400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO0_SEL_BUF,       0x48006420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO1_DATA_BUF,      0x480073FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO1_DIR_BUF,       0x48007400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO1_SEL_BUF,       0x48007420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO2_DATA_BUF,      0x480083FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO2_DIR_BUF,       0x48008400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO2_SEL_BUF,       0x48008420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO3_DATA_BUF,      0x480093FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO3_DIR_BUF,       0x48009400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO3_SEL_BUF,       0x48009420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO4_DATA_BUF,      0x4800A3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO4_DIR_BUF,       0x4800A400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO4_SEL_BUF,       0x4800A420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO5_DATA_BUF,      0x4800B3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO5_DIR_BUF,       0x4800B400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO5_SEL_BUF,       0x4800B420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO6_DATA_BUF,      0x4800C3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO6_DIR_BUF,       0x4800C400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO6_SEL_BUF,       0x4800C420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO7_DATA_BUF,      0x4800D3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO7_DIR_BUF,       0x4800D400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO7_SEL_BUF,       0x4800D420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO8_DATA_BUF,      0x4800E3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO8_DIR_BUF,       0x4800E400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO8_SEL_BUF,       0x4800E420,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO9_DATA_BUF,      0x4800F3FC,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO9_DIR_BUF,       0x4800F400,__READ_WRITE,__BITS8);
__IO_REG8_BIT( GPIO9_SEL_BUF,       0x4800F420,__READ_WRITE,__BITS8);

/***************************************************************************
 **
 ** VIC0
 **
 ***************************************************************************/
__IO_REG32_BIT(VIC0_IRQStatus,      0xFFFFF000,__READ      ,__vic0_bits);
__IO_REG32_BIT(VIC0_FIQStatus,      0xFFFFF004,__READ      ,__vic0_bits);
__IO_REG32_BIT(VIC0_RawIntr,        0xFFFFF008,__READ      ,__vic0_bits);
__IO_REG32_BIT(VIC0_IntSelect,      0xFFFFF00C,__READ_WRITE,__vic0_bits);
__IO_REG32_BIT(VIC0_IntEnable,      0xFFFFF010,__READ_WRITE,__vic0_bits);
__IO_REG32_BIT(VIC0_IntEnClear,     0xFFFFF014,__WRITE     ,__vic0_bits);
__IO_REG32_BIT(VIC0_SoftInt,        0xFFFFF018,__READ_WRITE,__vic0_bits);
__IO_REG32_BIT(VIC0_SoftIntClear,   0xFFFFF01C,__WRITE     ,__vic0_bits);
__IO_REG32_BIT(VIC0_Protection,     0xFFFFF020,__READ_WRITE,__vic_protection_bits);
__IO_REG32(    VIC0_CurrVectAddr,   0xFFFFF030,__READ_WRITE);
__IO_REG32(    VIC0_DefVectAddr,    0xFFFFF034,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr0,      0xFFFFF100,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr1,      0xFFFFF104,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr2,      0xFFFFF108,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr3,      0xFFFFF10C,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr4,      0xFFFFF110,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr5,      0xFFFFF114,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr6,      0xFFFFF118,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr7,      0xFFFFF11C,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr8,      0xFFFFF120,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr9,      0xFFFFF124,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr10,     0xFFFFF128,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr11,     0xFFFFF12C,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr12,     0xFFFFF130,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr13,     0xFFFFF134,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr14,     0xFFFFF138,__READ_WRITE);
__IO_REG32(    VIC0_VectAddr15,     0xFFFFF13C,__READ_WRITE);
__IO_REG32_BIT(VIC0_VectCntl0,      0xFFFFF200,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl1,      0xFFFFF204,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl2,      0xFFFFF208,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl3,      0xFFFFF20C,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl4,      0xFFFFF210,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl5,      0xFFFFF214,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl6,      0xFFFFF218,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl7,      0xFFFFF21C,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl8,      0xFFFFF220,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl9,      0xFFFFF224,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl10,     0xFFFFF228,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl11,     0xFFFFF22C,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl12,     0xFFFFF230,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl13,     0xFFFFF234,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl14,     0xFFFFF238,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC0_VectCntl15,     0xFFFFF23C,__READ_WRITE,__vic_vectcntl_bits);

/***************************************************************************
 **
 ** VIC1
 **
 ***************************************************************************/
__IO_REG32_BIT(VIC1_IRQStatus,      0xFC000000,__READ      ,__vic1_bits);
__IO_REG32_BIT(VIC1_FIQStatus,      0xFC000004,__READ      ,__vic1_bits);
__IO_REG32_BIT(VIC1_RawIntr,        0xFC000008,__READ      ,__vic1_bits);
__IO_REG32_BIT(VIC1_IntSelect,      0xFC00000C,__READ_WRITE,__vic1_bits);
__IO_REG32_BIT(VIC1_IntEnable,      0xFC000010,__READ_WRITE,__vic1_bits);
__IO_REG32_BIT(VIC1_IntEnClear,     0xFC000014,__WRITE     ,__vic1_bits);
__IO_REG32_BIT(VIC1_SoftInt,        0xFC000018,__READ_WRITE,__vic1_bits);
__IO_REG32_BIT(VIC1_SoftIntClear,   0xFC00001C,__WRITE     ,__vic1_bits);
__IO_REG32_BIT(VIC1_Protection,     0xFC000020,__READ_WRITE,__vic_protection_bits);
__IO_REG32(    VIC1_CurrVectAddr,   0xFC000030,__READ_WRITE);
__IO_REG32(    VIC1_DefVectAddr,    0xFC000034,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr0,      0xFC000100,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr1,      0xFC000104,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr2,      0xFC000108,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr3,      0xFC00010C,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr4,      0xFC000110,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr5,      0xFC000114,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr6,      0xFC000118,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr7,      0xFC00011C,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr8,      0xFC000120,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr9,      0xFC000124,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr10,     0xFC000128,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr11,     0xFC00012C,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr12,     0xFC000130,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr13,     0xFC000134,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr14,     0xFC000138,__READ_WRITE);
__IO_REG32(    VIC1_VectAddr15,     0xFC00013C,__READ_WRITE);
__IO_REG32_BIT(VIC1_VectCntl0,      0xFC000200,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl1,      0xFC000204,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl2,      0xFC000208,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl3,      0xFC00020C,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl4,      0xFC000210,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl5,      0xFC000214,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl6,      0xFC000218,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl7,      0xFC00021C,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl8,      0xFC000220,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl9,      0xFC000224,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl10,     0xFC000228,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl11,     0xFC00022C,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl12,     0xFC000230,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl13,     0xFC000234,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl14,     0xFC000238,__READ_WRITE,__vic_vectcntl_bits);
__IO_REG32_BIT(VIC1_VectCntl15,     0xFC00023C,__READ_WRITE,__vic_vectcntl_bits);

/***************************************************************************
 **
 ** WIU
 **
 ***************************************************************************/
__IO_REG32_BIT(WIU_CTRL,            0x58001000,__READ_WRITE,__wiu_ctrl_bits);
__IO_REG32_BIT(WIU_MR,              0x58001004,__READ_WRITE,__wiu_msk_bits);
__IO_REG32_BIT(WIU_TR,              0x58001008,__READ_WRITE,__wiu_tr_bits);
__IO_REG32_BIT(WIU_PR,              0x5800100C,__READ_WRITE,__wiu_pr_bits);
__IO_REG32_BIT(WIU_INTR,            0x58001010,__READ_WRITE,__wiu_intr_bits);

/***************************************************************************
 **
 ** WIU buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(WIU_CTRL_BUF,        0x48001000,__READ_WRITE,__wiu_ctrl_bits);
__IO_REG32_BIT(WIU_MR_BUF,          0x48001004,__READ_WRITE,__wiu_msk_bits);
__IO_REG32_BIT(WIU_TR_BUF,          0x48001008,__READ_WRITE,__wiu_tr_bits);
__IO_REG32_BIT(WIU_PR_BUF,          0x4800100C,__READ_WRITE,__wiu_pr_bits);
__IO_REG32_BIT(WIU_INTR_BUF,        0x48001010,__READ_WRITE,__wiu_intr_bits);

/***************************************************************************
 **
 ** RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(RTC_TR,              0x5C001000,__READ_WRITE,__rtc_tr_bits);
__IO_REG32_BIT(RTC_DTR,             0x5C001004,__READ_WRITE,__rtc_dtr_bits);
__IO_REG32_BIT(RTC_ATR,             0x5C001008,__READ_WRITE,__rtc_atr_bits);
__IO_REG32_BIT(RTC_CR,              0x5C00100C,__READ_WRITE,__rtc_cr_bits);
__IO_REG32_BIT(RTC_SR,              0x5C001010,__READ      ,__rtc_sr_bits);
__IO_REG32_BIT(RTC_MILR,            0x5C001014,__READ_WRITE,__rtc_milr_bits);

/***************************************************************************
 **
 ** RTC buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(RTC_TR_BUF,          0x4C001000,__READ_WRITE,__rtc_tr_bits);
__IO_REG32_BIT(RTC_DTR_BUF,         0x4C001004,__READ_WRITE,__rtc_dtr_bits);
__IO_REG32_BIT(RTC_ATR_BUF,         0x4C001008,__READ_WRITE,__rtc_atr_bits);
__IO_REG32_BIT(RTC_CR_BUF,          0x4C00100C,__READ_WRITE,__rtc_cr_bits);
__IO_REG32_BIT(RTC_SR_BUF,          0x4C001010,__READ      ,__rtc_sr_bits);
__IO_REG32_BIT(RTC_MILR_BUF,        0x4C001014,__READ_WRITE,__rtc_milr_bits);

/***************************************************************************
 **
 ** WDT
 **
 ***************************************************************************/
__IO_REG16_BIT(WDG_CR,              0x5C00B000,__READ_WRITE,__wdt_cr_bits);
__IO_REG8(     WDG_PR,              0x5C00B004,__READ_WRITE);
__IO_REG16(    WDG_VR,              0x5C00B008,__READ_WRITE);
__IO_REG16(    WDG_CNT,             0x5C00B00C,__READ      );
__IO_REG16_BIT(WDG_SR,              0x5C00B010,__READ_WRITE,__wdt_sr_bits);
__IO_REG16_BIT(WDG_MR,              0x5C00B014,__READ_WRITE,__wdt_mr_bits);
__IO_REG16(    WDG_KR,              0x5C00B018,__READ_WRITE);

/***************************************************************************
 **
 ** WDT buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(WDG_CR_BUF,          0x4C00B000,__READ_WRITE,__wdt_cr_bits);
__IO_REG8(     WDG_PR_BUF,          0x4C00B004,__READ_WRITE);
__IO_REG16(    WDG_VR_BUF,          0x4C00B008,__READ_WRITE);
__IO_REG16(    WDG_CNT_BUF,         0x4C00B00C,__READ      );
__IO_REG16_BIT(WDG_SR_BUF,          0x4C00B010,__READ_WRITE,__wdt_sr_bits);
__IO_REG16_BIT(WDG_MR_BUF,          0x4C00B014,__READ_WRITE,__wdt_mr_bits);
__IO_REG16(    WDG_KR_BUF,          0x4C00B018,__READ_WRITE);

/***************************************************************************
 **
 ** TIM0
 **
 ***************************************************************************/
__IO_REG16(    TIM0_IC1R,           0x58002000,__READ      );
__IO_REG16(    TIM0_IC2R,           0x58002004,__READ      );
__IO_REG16(    TIM0_OC1R,           0x58002008,__READ_WRITE);
__IO_REG16(    TIM0_OC2R,           0x5800200C,__READ_WRITE);
__IO_REG16(    TIM0_CNTR,           0x58002010,__READ      );
__IO_REG16_BIT(TIM0_CR1,            0x58002014,__READ_WRITE,__tim_cr1_bits);
__IO_REG16_BIT(TIM0_CR2,            0x58002018,__READ_WRITE,__tim_cr2_bits);
__IO_REG16_BIT(TIM0_SR,             0x5800201C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** TIM0 Buffered
 **
 ***************************************************************************/
__IO_REG16(    TIM0_ICR1_BUF,       0x48002000,__READ      );
__IO_REG16(    TIM0_ICR2_BUF,       0x48002004,__READ      );
__IO_REG16(    TIM0_OCR1_BUF,       0x48002008,__READ_WRITE);
__IO_REG16(    TIM0_OCR2_BUF,       0x4800200C,__READ_WRITE);
__IO_REG16(    TIM0_CNTR_BUF,       0x48002010,__READ      );
__IO_REG16_BIT(TIM0_CR1_BUF,        0x48002014,__READ_WRITE,__tim_cr1_bits);
__IO_REG16_BIT(TIM0_CR2_BUF,        0x48002018,__READ_WRITE,__tim_cr2_bits);
__IO_REG16_BIT(TIM0_SR_BUF,         0x4800201C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** TIM1
 **
 ***************************************************************************/
__IO_REG16(    TIM1_ICR1,           0x58003000,__READ      );
__IO_REG16(    TIM1_ICR2,           0x58003004,__READ      );
__IO_REG16(    TIM1_OCR1,           0x58003008,__READ_WRITE);
__IO_REG16(    TIM1_OCR2,           0x5800300C,__READ_WRITE);
__IO_REG16(    TIM1_CNTR,           0x58003010,__READ      );
__IO_REG16_BIT(TIM1_CR1,            0x58003014,__READ_WRITE,__tim_cr1_bits);
__IO_REG16_BIT(TIM1_CR2,            0x58003018,__READ_WRITE,__tim_cr2_bits);
__IO_REG16_BIT(TIM1_SR,             0x5800301C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** TIM1 Buffered
 **
 ***************************************************************************/
__IO_REG16(    TIM1_ICR1_BUF,       0x48003000,__READ      );
__IO_REG16(    TIM1_ICR2_BUF,       0x48003004,__READ      );
__IO_REG16(    TIM1_OCR1_BUF,       0x48003008,__READ_WRITE);
__IO_REG16(    TIM1_OCR2_BUF,       0x4800300C,__READ_WRITE);
__IO_REG16(    TIM1_CNTR_BUF,       0x48003010,__READ      );
__IO_REG16_BIT(TIM1_CR1_BUF,        0x48003014,__READ_WRITE,__tim_cr1_bits);
__IO_REG16_BIT(TIM1_CR2_BUF,        0x48003018,__READ_WRITE,__tim_cr2_bits);
__IO_REG16_BIT(TIM1_SR_BUF,         0x4800301C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** TIM2
 **
 ***************************************************************************/
__IO_REG16(    TIM2_ICR1,           0x58004000,__READ      );
__IO_REG16(    TIM2_ICR2,           0x58004004,__READ      );
__IO_REG16(    TIM2_OCR1,           0x58004008,__READ_WRITE);
__IO_REG16(    TIM2_OCR2,           0x5800400C,__READ_WRITE);
__IO_REG16(    TIM2_CNTR,           0x58004010,__READ      );
__IO_REG16_BIT(TIM2_CR1,            0x58004014,__READ_WRITE,__tim2_cr1_bits);
__IO_REG16_BIT(TIM2_CR2,            0x58004018,__READ_WRITE,__tim2_cr2_bits);
__IO_REG16_BIT(TIM2_SR,             0x5800401C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** TIM2 Buffered
 **
 ***************************************************************************/
__IO_REG16(    TIM2_ICR1_BUF,       0x48004000,__READ      );
__IO_REG16(    TIM2_ICR2_BUF,       0x48004004,__READ      );
__IO_REG16(    TIM2_OCR1_BUF,       0x48004008,__READ_WRITE);
__IO_REG16(    TIM2_OCR2_BUF,       0x4800400C,__READ_WRITE);
__IO_REG16(    TIM2_CNTR_BUF,       0x48004010,__READ      );
__IO_REG16_BIT(TIM2_CR1_BUF,        0x48004014,__READ_WRITE,__tim2_cr1_bits);
__IO_REG16_BIT(TIM2_CR2_BUF,        0x48004018,__READ_WRITE,__tim2_cr2_bits);
__IO_REG16_BIT(TIM2_SR_BUF,         0x4800401C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** TIM3
 **
 ***************************************************************************/
__IO_REG16(    TIM3_ICR1,           0x58005000,__READ      );
__IO_REG16(    TIM3_ICR2,           0x58005004,__READ      );
__IO_REG16(    TIM3_OCR1,           0x58005008,__READ_WRITE);
__IO_REG16(    TIM3_OCR2,           0x5800500C,__READ_WRITE);
__IO_REG16(    TIM3_CNTR,           0x58005010,__READ      );
__IO_REG16_BIT(TIM3_CR1,            0x58005014,__READ_WRITE,__tim2_cr1_bits);
__IO_REG16_BIT(TIM3_CR2,            0x58005018,__READ_WRITE,__tim2_cr2_bits);
__IO_REG16_BIT(TIM3_SR,             0x5800501C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** TIM3 Buffered
 **
 ***************************************************************************/
__IO_REG16(    TIM3_ICR1_BUF,       0x48005000,__READ      );
__IO_REG16(    TIM3_ICR2_BUF,       0x48005004,__READ      );
__IO_REG16(    TIM3_OCR1_BUF,       0x48005008,__READ_WRITE);
__IO_REG16(    TIM3_OCR2_BUF,       0x4800500C,__READ_WRITE);
__IO_REG16(    TIM3_CNTR_BUF,       0x48005010,__READ      );
__IO_REG16_BIT(TIM3_CR1_BUF,        0x48005014,__READ_WRITE,__tim2_cr1_bits);
__IO_REG16_BIT(TIM3_CR2_BUF,        0x48005018,__READ_WRITE,__tim2_cr2_bits);
__IO_REG16_BIT(TIM3_SR_BUF,         0x4800501C,__READ_WRITE,__tim_sr_bits);

/***************************************************************************
 **
 ** ENET
 **
 ***************************************************************************/
__IO_REG32_BIT(ENET_SCR,            0x7C000000,__READ_WRITE,__enet_scr_bits);
__IO_REG32_BIT(ENET_IER,            0x7C000004,__READ_WRITE,__enet_ier_bits);
__IO_REG32_BIT(ENET_ISR,            0x7C000008,__READ_WRITE,__enet_isr_bits);
__IO_REG32_BIT(ENET_CCR,            0x7C00000C,__READ_WRITE,__enet_ccr_bits);
__IO_REG32_BIT(ENET_RXSTR,          0x7C000010,__READ_WRITE,__enet_rxstr_bits);
__IO_REG32_BIT(ENET_RXCR,           0x7C000014,__READ_WRITE,__enet_rxcr_bits);
__IO_REG32_BIT(ENET_RXSAR,          0x7C000018,__READ_WRITE,__enet_rxsar_bits);
__IO_REG32_BIT(ENET_RXNDAR,         0x7C00001C,__READ_WRITE,__enet_rxndar_bits);
__IO_REG32(    ENET_RXCAR,          0x7C000020,__READ      );
__IO_REG32_BIT(ENET_RXCTCR,         0x7C000024,__READ      ,__enet_rxctcr_bits);
__IO_REG32_BIT(ENET_RXTOR,          0x7C000028,__READ      ,__enet_rxtor_bits);
__IO_REG32_BIT(ENET_RXSR,           0x7C00002C,__READ      ,__enet_rxsr_bits);
__IO_REG32_BIT(ENET_TXSTR,          0x7C000030,__READ_WRITE,__enet_txstr_bits);
__IO_REG32_BIT(ENET_TXCR,           0x7C000034,__READ_WRITE,__enet_txcr_bits);
__IO_REG32_BIT(ENET_TXSAR,          0x7C000038,__READ_WRITE,__enet_txsar_bits);
__IO_REG32_BIT(ENET_TXNDAR,         0x7C00003C,__READ_WRITE,__enet_txndar_bits);
__IO_REG32(    ENET_TXCAR,          0x7C000040,__READ      );
__IO_REG32_BIT(ENET_TXCTCR,         0x7C000044,__READ      ,__enet_txctcr_bits);
__IO_REG32_BIT(ENET_TXTOR,          0x7C000048,__READ      ,__enet_txtor_bits);
__IO_REG32_BIT(ENET_TXSR,           0x7C00004C,__READ      ,__enet_txsr_bits);
__IO_REG32_BIT(ENET_MCR,            0x7C000400,__READ_WRITE,__enet_mcr_bits);
__IO_REG32(    ENET_MAH,            0x7C000404,__READ_WRITE);
__IO_REG32(    ENET_MAL,            0x7C000408,__READ_WRITE);
__IO_REG32(    ENET_MCHA,           0x7C00040C,__READ_WRITE);
__IO_REG32(    ENET_MCLA,           0x7C000410,__READ_WRITE);
__IO_REG32_BIT(ENET_MIIA,           0x7C000414,__READ_WRITE,__enet_miia_bits);
__IO_REG32_BIT(ENET_MIID,           0x7C000418,__READ_WRITE,__enet_miid_bits);
__IO_REG32_BIT(ENET_MCF,            0x7C00041C,__READ_WRITE,__enet_mcf_bits);
__IO_REG32_BIT(ENET_VL1,            0x7C000420,__READ_WRITE,__enet_vl1_bits);
__IO_REG32_BIT(ENET_VL2,            0x7C000424,__READ_WRITE,__enet_vl2_bits);
__IO_REG32_BIT(ENET_MTS,            0x7C000428,__READ      ,__enet_mts_bits);
__IO_REG32_BIT(ENET_MRS,            0x7C00042C,__READ      ,__enet_mrs_bits);
__IO_REG32(    ENET_RX_FIFO_0,      0x7C000100,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_1,      0x7C000104,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_2,      0x7C000108,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_3,      0x7C00010C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_4,      0x7C000110,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_5,      0x7C000114,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_6,      0x7C000118,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_7,      0x7C00011C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_8,      0x7C000120,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_9,      0x7C000124,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_10,     0x7C000128,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_11,     0x7C00012C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_12,     0x7C000130,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_13,     0x7C000134,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_14,     0x7C000138,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_15,     0x7C00013C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_16,     0x7C000140,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_17,     0x7C000144,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_18,     0x7C000148,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_19,     0x7C00014C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_20,     0x7C000150,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_21,     0x7C000154,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_22,     0x7C000158,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_23,     0x7C00015C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_24,     0x7C000160,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_25,     0x7C000164,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_26,     0x7C000168,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_27,     0x7C00016C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_28,     0x7C000170,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_29,     0x7C000174,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_30,     0x7C000178,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_31,     0x7C00017C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_0,      0x7C000200,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_1,      0x7C000204,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_2,      0x7C000208,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_3,      0x7C00020C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_4,      0x7C000210,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_5,      0x7C000214,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_6,      0x7C000218,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_7,      0x7C00021C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_8,      0x7C000220,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_9,      0x7C000224,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_10,     0x7C000228,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_11,     0x7C00022C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_12,     0x7C000230,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_13,     0x7C000234,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_14,     0x7C000238,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_15,     0x7C00023C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_16,     0x7C000240,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_17,     0x7C000244,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_18,     0x7C000248,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_19,     0x7C00024C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_20,     0x7C000250,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_21,     0x7C000254,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_22,     0x7C000258,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_23,     0x7C00025C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_24,     0x7C000260,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_25,     0x7C000264,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_26,     0x7C000268,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_27,     0x7C00026C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_28,     0x7C000270,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_29,     0x7C000274,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_30,     0x7C000278,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_31,     0x7C00027C,__READ_WRITE);

/***************************************************************************
 **
 ** ENET Buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(ENET_SCR_BUF,        0x6C000000,__READ_WRITE,__enet_scr_bits);
__IO_REG32_BIT(ENET_IER_BUF,        0x6C000004,__READ_WRITE,__enet_ier_bits);
__IO_REG32_BIT(ENET_ISR_BUF,        0x6C000008,__READ_WRITE,__enet_isr_bits);
__IO_REG32_BIT(ENET_CCR_BUF,        0x6C00000C,__READ_WRITE,__enet_ccr_bits);
__IO_REG32_BIT(ENET_RXSTR_BUF,      0x6C000010,__READ_WRITE,__enet_rxstr_bits);
__IO_REG32_BIT(ENET_RXCR_BUF,       0x6C000014,__READ_WRITE,__enet_rxcr_bits);
__IO_REG32_BIT(ENET_RXSAR_BUF,      0x6C000018,__READ_WRITE,__enet_rxsar_bits);
__IO_REG32_BIT(ENET_RXNDAR_BUF,     0x6C00001C,__READ_WRITE,__enet_rxndar_bits);
__IO_REG32(    ENET_RXCAR_BUF,      0x6C000020,__READ      );
__IO_REG32_BIT(ENET_RXCTCR_BUF,     0x6C000024,__READ      ,__enet_rxctcr_bits);
__IO_REG32_BIT(ENET_RXTOR_BUF,      0x6C000028,__READ      ,__enet_rxtor_bits);
__IO_REG32_BIT(ENET_RXSR_BUF,       0x6C00002C,__READ      ,__enet_rxsr_bits);
__IO_REG32_BIT(ENET_TXSTR_BUF,      0x6C000030,__READ_WRITE,__enet_txstr_bits);
__IO_REG32_BIT(ENET_TXCR_BUF,       0x6C000034,__READ_WRITE,__enet_txcr_bits);
__IO_REG32_BIT(ENET_TXSAR_BUF,      0x6C000038,__READ_WRITE,__enet_txsar_bits);
__IO_REG32_BIT(ENET_TXNDAR_BUF,     0x6C00003C,__READ_WRITE,__enet_txndar_bits);
__IO_REG32(    ENET_TXCAR_BUF,      0x6C000040,__READ      );
__IO_REG32_BIT(ENET_TXCTCR_BUF,     0x6C000044,__READ      ,__enet_txctcr_bits);
__IO_REG32_BIT(ENET_TXTOR_BUF,      0x6C000048,__READ      ,__enet_txtor_bits);
__IO_REG32_BIT(ENET_TXSR_BUF,       0x6C00004C,__READ      ,__enet_txsr_bits);
__IO_REG32_BIT(ENET_MCR_BUF,        0x6C000400,__READ_WRITE,__enet_mcr_bits);
__IO_REG32(    ENET_MAH_BUF,        0x6C000404,__READ_WRITE);
__IO_REG32(    ENET_MAL_BUF,        0x6C000408,__READ_WRITE);
__IO_REG32(    ENET_MCHA_BUF,       0x6C00040C,__READ_WRITE);
__IO_REG32(    ENET_MCLA_BUF,       0x6C000410,__READ_WRITE);
__IO_REG32_BIT(ENET_MIIA_BUF,       0x6C000414,__READ_WRITE,__enet_miia_bits);
__IO_REG32_BIT(ENET_MIID_BUF,       0x6C000418,__READ_WRITE,__enet_miid_bits);
__IO_REG32_BIT(ENET_MCF_BUF,        0x6C00041C,__READ_WRITE,__enet_mcf_bits);
__IO_REG32_BIT(ENET_VL1_BUF,        0x6C000420,__READ_WRITE,__enet_vl1_bits);
__IO_REG32_BIT(ENET_VL2_BUF,        0x6C000424,__READ_WRITE,__enet_vl2_bits);
__IO_REG32_BIT(ENET_MTS_BUF,        0x6C000428,__READ      ,__enet_mts_bits);
__IO_REG32_BIT(ENET_MRS_BUF,        0x6C00042C,__READ      ,__enet_mrs_bits);
__IO_REG32(    ENET_RX_FIFO_0_BUF,  0x6C000100,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_1_BUF,  0x6C000104,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_2_BUF,  0x6C000108,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_3_BUF,  0x6C00010C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_4_BUF,  0x6C000110,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_5_BUF,  0x6C000114,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_6_BUF,  0x6C000118,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_7_BUF,  0x6C00011C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_8_BUF,  0x6C000120,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_9_BUF,  0x6C000124,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_10_BUF, 0x6C000128,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_11_BUF, 0x6C00012C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_12_BUF, 0x6C000130,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_13_BUF, 0x6C000134,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_14_BUF, 0x6C000138,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_15_BUF, 0x6C00013C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_16_BUF, 0x6C000140,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_17_BUF, 0x6C000144,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_18_BUF, 0x6C000148,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_19_BUF, 0x6C00014C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_20_BUF, 0x6C000150,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_21_BUF, 0x6C000154,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_22_BUF, 0x6C000158,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_23_BUF, 0x6C00015C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_24_BUF, 0x6C000160,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_25_BUF, 0x6C000164,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_26_BUF, 0x6C000168,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_27_BUF, 0x6C00016C,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_28_BUF, 0x6C000170,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_29_BUF, 0x6C000174,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_30_BUF, 0x6C000178,__READ_WRITE);
__IO_REG32(    ENET_RX_FIFO_31_BUF, 0x6C00017C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_0_BUF,  0x6C000200,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_1_BUF,  0x6C000204,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_2_BUF,  0x6C000208,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_3_BUF,  0x6C00020C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_4_BUF,  0x6C000210,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_5_BUF,  0x6C000214,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_6_BUF,  0x6C000218,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_7_BUF,  0x6C00021C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_8_BUF,  0x6C000220,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_9_BUF,  0x6C000224,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_10_BUF, 0x6C000228,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_11_BUF, 0x6C00022C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_12_BUF, 0x6C000230,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_13_BUF, 0x6C000234,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_14_BUF, 0x6C000238,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_15_BUF, 0x6C00023C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_16_BUF, 0x6C000240,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_17_BUF, 0x6C000244,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_18_BUF, 0x6C000248,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_19_BUF, 0x6C00024C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_20_BUF, 0x6C000250,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_21_BUF, 0x6C000254,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_22_BUF, 0x6C000258,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_23_BUF, 0x6C00025C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_24_BUF, 0x6C000260,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_25_BUF, 0x6C000264,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_26_BUF, 0x6C000268,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_27_BUF, 0x6C00026C,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_28_BUF, 0x6C000270,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_29_BUF, 0x6C000274,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_30_BUF, 0x6C000278,__READ_WRITE);
__IO_REG32(    ENET_TX_FIFO_31_BUF, 0x6C00027C,__READ_WRITE);

/***************************************************************************
 **
 ** DMAC
 **
 ***************************************************************************/
__IO_REG32_BIT(DMA_ISR,             0x78000000,__READ      ,__dma_isr_bits);
__IO_REG32_BIT(DMA_TCISR,           0x78000004,__READ      ,__dma_tcisr_bits);
__IO_REG32_BIT(DMA_TCICR,           0x78000008,__WRITE     ,__dma_tcicr_bits);
__IO_REG32_BIT(DMA_EISR,            0x7800000C,__READ      ,__dma_eisr_bits);
__IO_REG32_BIT(DMA_EICR,            0x78000010,__WRITE     ,__dma_eicr_bits);
__IO_REG32_BIT(DMA_TCRISR,          0x78000014,__READ      ,__dma_tcrisr_bits);
__IO_REG32_BIT(DMA_ERISR,           0x78000018,__READ      ,__dma_erisr_bits);
__IO_REG32_BIT(DMA_ENCSR,           0x7800001C,__READ      ,__dma_encsr_bits);
__IO_REG32_BIT(DMA_SBRR,            0x78000020,__READ_WRITE,__dma_sbrr_bits);
__IO_REG32_BIT(DMA_SSRR,            0x78000024,__READ_WRITE,__dma_ssrr_bits);
__IO_REG32_BIT(DMA_SLBR,            0x78000028,__READ_WRITE,__dma_slbr_bits);
__IO_REG32_BIT(DMA_SLSR,            0x7800002C,__READ_WRITE,__dma_slsr_bits);
__IO_REG32_BIT(DMA_CNFR,            0x78000030,__READ_WRITE,__dma_cnfr_bits);
__IO_REG32_BIT(DMA_SYNC,            0x78000034,__READ_WRITE,__dma_sync_bits);
__IO_REG32(    DMA_SRC0,            0x78000100,__READ_WRITE);
__IO_REG32(    DMA_DEST0,           0x78000104,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI0,            0x78000108,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC0,             0x7800010C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF0,           0x78000110,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC1,            0x78000120,__READ_WRITE);
__IO_REG32(    DMA_DEST1,           0x78000124,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI1,            0x78000128,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC1,             0x7800012C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF1,           0x78000130,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC2,            0x78000140,__READ_WRITE);
__IO_REG32(    DMA_DEST2,           0x78000144,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI2,            0x78000148,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC2,             0x7800014C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF2,           0x78000150,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC3,            0x78000160,__READ_WRITE);
__IO_REG32(    DMA_DEST3,           0x78000164,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI3,            0x78000168,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC3,             0x7800016C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF3,           0x78000170,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC4,            0x78000180,__READ_WRITE);
__IO_REG32(    DMA_DEST4,           0x78000184,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI4,            0x78000188,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC4,             0x7800018C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF4,           0x78000190,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC5,            0x780001A0,__READ_WRITE);
__IO_REG32(    DMA_DEST5,           0x780001A4,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI5,            0x780001A8,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC5,             0x780001AC,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF5,           0x780001B0,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC6,            0x780001C0,__READ_WRITE);
__IO_REG32(    DMA_DEST6,           0x780001C4,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI6,            0x780001C8,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC6,             0x780001CC,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF6,           0x780001D0,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC7,            0x780001E0,__READ_WRITE);
__IO_REG32(    DMA_DEST7,           0x780001E4,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI7,            0x780001E8,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC7,             0x780001EC,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF7,           0x780001F0,__READ_WRITE,__dma_ccnf_bits);

/***************************************************************************
 **
 ** DMAC Buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(DMA_ISR_BUF,         0x68000000,__READ      ,__dma_isr_bits);
__IO_REG32_BIT(DMA_TCISR_BUF,       0x68000004,__READ      ,__dma_tcisr_bits);
__IO_REG32_BIT(DMA_TCICR_BUF,       0x68000008,__WRITE     ,__dma_tcicr_bits);
__IO_REG32_BIT(DMA_EISR_BUF,        0x6800000C,__READ      ,__dma_eisr_bits);
__IO_REG32_BIT(DMA_EICR_BUF,        0x68000010,__WRITE     ,__dma_eicr_bits);
__IO_REG32_BIT(DMA_TCRISR_BUF,      0x68000014,__READ      ,__dma_tcrisr_bits);
__IO_REG32_BIT(DMA_ERISR_BUF,       0x68000018,__READ      ,__dma_erisr_bits);
__IO_REG32_BIT(DMA_ENCSR_BUF,       0x6800001C,__READ      ,__dma_encsr_bits);
__IO_REG32_BIT(DMA_SBRR_BUF,        0x68000020,__READ_WRITE,__dma_sbrr_bits);
__IO_REG32_BIT(DMA_SSRR_BUF,        0x68000024,__READ_WRITE,__dma_ssrr_bits);
__IO_REG32_BIT(DMA_SLBR_BUF,        0x68000028,__READ_WRITE,__dma_slbr_bits);
__IO_REG32_BIT(DMA_SLSR_BUF,        0x6800002C,__READ_WRITE,__dma_slsr_bits);
__IO_REG32_BIT(DMA_CNFR_BUF,        0x68000030,__READ_WRITE,__dma_cnfr_bits);
__IO_REG32_BIT(DMA_SYNC_BUF,        0x68000034,__READ_WRITE,__dma_sync_bits);
__IO_REG32(    DMA_SRC0_BUF,        0x68000100,__READ_WRITE);
__IO_REG32(    DMA_DEST0_BUF,       0x68000104,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI0_BUF,        0x68000108,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC0_BUF,         0x6800010C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF0_BUF,       0x68000110,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC1_BUF,        0x68000120,__READ_WRITE);
__IO_REG32(    DMA_DEST1_BUF,       0x68000124,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI1_BUF,        0x68000128,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC1_BUF,         0x6800012C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF1_BUF,       0x68000130,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC2_BUF,        0x68000140,__READ_WRITE);
__IO_REG32(    DMA_DEST2_BUF,       0x68000144,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI2_BUF,        0x68000148,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC2_BUF,         0x6800014C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF2_BUF,       0x68000150,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC3_BUF,        0x68000160,__READ_WRITE);
__IO_REG32(    DMA_DEST3_BUF,       0x68000164,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI3_BUF,        0x68000168,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC3_BUF,         0x6800016C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF3_BUF,       0x68000170,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC4_BUF,        0x68000180,__READ_WRITE);
__IO_REG32(    DMA_DEST4_BUF,       0x68000184,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI4_BUF,        0x68000188,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC4_BUF,         0x6800018C,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF4_BUF,       0x68000190,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC5_BUF,        0x680001A0,__READ_WRITE);
__IO_REG32(    DMA_DEST5_BUF,       0x680001A4,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI5_BUF,        0x680001A8,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC5_BUF,         0x680001AC,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF5_BUF,       0x680001B0,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC6_BUF,        0x680001C0,__READ_WRITE);
__IO_REG32(    DMA_DEST6_BUF,       0x680001C4,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI6_BUF,        0x680001C8,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC6_BUF,         0x680001CC,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF6_BUF,       0x680001D0,__READ_WRITE,__dma_ccnf_bits);
__IO_REG32(    DMA_SRC7_BUF,        0x680001E0,__READ_WRITE);
__IO_REG32(    DMA_DEST7_BUF,       0x680001E4,__READ_WRITE);
__IO_REG32_BIT(DMA_LLI7_BUF,        0x680001E8,__READ_WRITE,__dma_lli_bits);
__IO_REG32_BIT(DMA_CC7_BUF,         0x680001EC,__READ_WRITE,__dma_cc_bits);
__IO_REG32_BIT(DMA_CCNF7_BUF,       0x680001F0,__READ_WRITE,__dma_ccnf_bits);

/***************************************************************************
 **
 ** SSP0
 **
 ***************************************************************************/
__IO_REG16_BIT(SSP0_CR0,            0x5C007000,__READ_WRITE,__ssp_cr0_bits);
__IO_REG16_BIT(SSP0_CR1,            0x5C007004,__READ_WRITE,__ssp_cr1_bits);
__IO_REG16(    SSP0_DR,             0x5C007008,__READ_WRITE);
__IO_REG16_BIT(SSP0_SR,             0x5C00700C,__READ      ,__ssp_sr_bits);
__IO_REG8(     SSP0_PR,             0x5C007010,__READ_WRITE);
__IO_REG16_BIT(SSP0_IMSCR,          0x5C007014,__READ_WRITE,__ssp_imscr_bits);
__IO_REG16_BIT(SSP0_RISR,           0x5C007018,__READ      ,__ssp_risr_bits);
__IO_REG16_BIT(SSP0_MISR,           0x5C00701C,__READ      ,__ssp_misr_bits);
__IO_REG16_BIT(SSP0_ICR,            0x5C007020,__WRITE     ,__ssp_icr_bits);
__IO_REG16_BIT(SSP0_DMACR,          0x5C007024,__READ_WRITE,__ssp_dmacr_bits);

/***************************************************************************
 **
 ** SSP0 Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(SSP0_CR0_BUF,        0x4C007000,__READ_WRITE,__ssp_cr0_bits);
__IO_REG16_BIT(SSP0_CR1_BUF,        0x4C007004,__READ_WRITE,__ssp_cr1_bits);
__IO_REG16(    SSP0_DR_BUF,         0x4C007008,__READ_WRITE);
__IO_REG16_BIT(SSP0_SR_BUF,         0x4C00700C,__READ      ,__ssp_sr_bits);
__IO_REG8(     SSP0_PR_BUF,         0x4C007010,__READ_WRITE);
__IO_REG16_BIT(SSP0_IMSCR_BUF,      0x4C007014,__READ_WRITE,__ssp_imscr_bits);
__IO_REG16_BIT(SSP0_RISR_BUF,       0x4C007018,__READ      ,__ssp_risr_bits);
__IO_REG16_BIT(SSP0_MISR_BUF,       0x4C00701C,__READ      ,__ssp_misr_bits);
__IO_REG16_BIT(SSP0_ICR_BUF,        0x4C007020,__WRITE     ,__ssp_icr_bits);
__IO_REG16_BIT(SSP0_DMACR_BUF,      0x4C007024,__READ_WRITE,__ssp_dmacr_bits);

/***************************************************************************
 **
 ** SSP1
 **
 ***************************************************************************/
__IO_REG16_BIT(SSP1_CR0,            0x5C008000,__READ_WRITE,__ssp_cr0_bits);
__IO_REG16_BIT(SSP1_CR1,            0x5C008004,__READ_WRITE,__ssp_cr1_bits);
__IO_REG16(    SSP1_DR,             0x5C008008,__READ_WRITE);
__IO_REG16_BIT(SSP1_SR,             0x5C00800C,__READ      ,__ssp_sr_bits);
__IO_REG8(     SSP1_PR,             0x5C008010,__READ_WRITE);
__IO_REG16_BIT(SSP1_IMSCR,          0x5C008014,__READ_WRITE,__ssp_imscr_bits);
__IO_REG16_BIT(SSP1_RISR,           0x5C008018,__READ      ,__ssp_risr_bits);
__IO_REG16_BIT(SSP1_MISR,           0x5C00801C,__READ      ,__ssp_misr_bits);
__IO_REG16_BIT(SSP1_ICR,            0x5C008020,__WRITE     ,__ssp_icr_bits);
__IO_REG16_BIT(SSP1_DMACR,          0x5C008024,__READ_WRITE,__ssp_dmacr_bits);

/***************************************************************************
 **
 ** SSP1 Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(SSP1_CR0_BUF,        0x4C008000,__READ_WRITE,__ssp_cr0_bits);
__IO_REG16_BIT(SSP1_CR1_BUF,        0x4C008004,__READ_WRITE,__ssp_cr1_bits);
__IO_REG16(    SSP1_DR_BUF,         0x4C008008,__READ_WRITE);
__IO_REG16_BIT(SSP1_SR_BUF,         0x4C00800C,__READ      ,__ssp_sr_bits);
__IO_REG8(     SSP1_PR_BUF,         0x4C008010,__READ_WRITE);
__IO_REG16_BIT(SSP1_IMSCR_BUF,      0x4C008014,__READ_WRITE,__ssp_imscr_bits);
__IO_REG16_BIT(SSP1_RISR_BUF,       0x4C008018,__READ      ,__ssp_risr_bits);
__IO_REG16_BIT(SSP1_MISR_BUF,       0x4C00801C,__READ      ,__ssp_misr_bits);
__IO_REG16_BIT(SSP1_ICR_BUF,        0x4C008020,__WRITE     ,__ssp_icr_bits);
__IO_REG16_BIT(SSP1_DMACR_BUF,      0x4C008024,__READ_WRITE,__ssp_dmacr_bits);

/***************************************************************************
 **
 ** UART0
 **
 ***************************************************************************/
__IO_REG16_BIT(UART0_DR,            0x5C004000,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART0_RSR,           0x5C004004,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART0_FR,            0x5C004018,__READ      ,__uart_fr_bits);
__IO_REG8(     UART0_ILPR,          0x5C004020,__READ_WRITE);
__IO_REG16(    UART0_IBRD,          0x5C004024,__READ_WRITE);
__IO_REG16_BIT(UART0_FBRD,          0x5C004028,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART0_LCR,           0x5C00402C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART0_CR,            0x5C004030,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART0_IFLS,          0x5C004034,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART0_IMSC,          0x5C004038,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART0_RIS,           0x5C00403C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART0_MIS,           0x5C004040,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART0_ICR,           0x5C004044,__WRITE     ,__uart_icr_bits);
__IO_REG16_BIT(UART0_DMACR,         0x5C004048,__READ_WRITE,__uart_dmacr_bits);

/***************************************************************************
 **
 ** UART0 Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(UART0_DR_BUF,        0x4C004000,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART0_RSR_BUF,       0x4C004004,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART0_FR_BUF,        0x4C004018,__READ      ,__uart_fr_bits);
__IO_REG8(     UART0_ILPR_BUF,      0x4C004020,__READ_WRITE);
__IO_REG16(    UART0_IBRD_BUF,      0x4C004024,__READ_WRITE);
__IO_REG16_BIT(UART0_FBRD_BUF,      0x4C004028,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART0_LCR_BUF,       0x4C00402C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART0_CR_BUF,        0x4C004030,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART0_IFLS_BUF,      0x4C004034,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART0_IMSC_BUF,      0x4C004038,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART0_RIS_BUF,       0x4C00403C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART0_MIS_BUF,       0x4C004040,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART0_ICR_BUF,       0x4C004044,__WRITE     ,__uart_icr_bits);
__IO_REG16_BIT(UART0_DMACR_BUF,     0x4C004048,__READ_WRITE,__uart_dmacr_bits);

/***************************************************************************
 **
 ** UART1
 **
 ***************************************************************************/
__IO_REG16_BIT(UART1_DR,            0x5C005000,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART1_RSR,           0x5C005004,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART1_FR,            0x5C005018,__READ      ,__uart_fr_bits);
__IO_REG8(     UART1_ILPR,          0x5C005020,__READ_WRITE);
__IO_REG16(    UART1_IBRD,          0x5C005024,__READ_WRITE);
__IO_REG16_BIT(UART1_FBRD,          0x5C005028,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART1_LCR,           0x5C00502C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART1_CR,            0x5C005030,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART1_IFLS,          0x5C005034,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART1_IMSC,          0x5C005038,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART1_RIS,           0x5C00503C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART1_MIS,           0x5C005040,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART1_ICR,           0x5C005044,__WRITE     ,__uart_icr_bits);
__IO_REG16_BIT(UART1_DMACR,         0x5C005048,__READ_WRITE,__uart_dmacr_bits);

/***************************************************************************
 **
 ** UART1 Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(UART1_DR_BUF,        0x4C005000,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART1_RSR_BUF,       0x4C005004,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART1_FR_BUF,        0x4C005018,__READ      ,__uart_fr_bits);
__IO_REG8(     UART1_ILPR_BUF,      0x4C005020,__READ_WRITE);
__IO_REG16(    UART1_IBRD_BUF,      0x4C005024,__READ_WRITE);
__IO_REG16_BIT(UART1_FBRD_BUF,      0x4C005028,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART1_LCR_BUF,       0x4C00502C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART1_CR_BUF,        0x4C005030,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART1_IFLS_BUF,      0x4C005034,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART1_IMSC_BUF,      0x4C005038,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART1_RIS_BUF,       0x4C00503C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART1_MIS_BUF,       0x4C005040,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART1_ICR_BUF,       0x4C005044,__WRITE     ,__uart_icr_bits);
__IO_REG16_BIT(UART1_DMACR_BUF,     0x4C005048,__READ_WRITE,__uart_dmacr_bits);

/***************************************************************************
 **
 ** UART2
 **
 ***************************************************************************/
__IO_REG16_BIT(UART2_DR,            0x5C006000,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART2_RSR,           0x5C006004,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART2_FR,            0x5C006018,__READ      ,__uart_fr_bits);
__IO_REG8(     UART2_ILPR,          0x5C006020,__READ_WRITE);
__IO_REG16(    UART2_IBRD,          0x5C006024,__READ_WRITE);
__IO_REG16_BIT(UART2_FBRD,          0x5C006028,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART2_LCR,           0x5C00602C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART2_CR,            0x5C006030,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART2_IFLS,          0x5C006034,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART2_IMSC,          0x5C006038,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART2_RIS,           0x5C00603C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART2_MIS,           0x5C006040,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART2_ICR,           0x5C006044,__WRITE     ,__uart_icr_bits);

/***************************************************************************
 **
 ** UART2 Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(UART2_DR_BUF,        0x4C006000,__READ_WRITE,__uart_dr_bits);
__IO_REG16_BIT(UART2_RSR_BUF,       0x4C006004,__READ_WRITE,__uart_rsr_bits);
__IO_REG16_BIT(UART2_FR_BUF,        0x4C006018,__READ      ,__uart_fr_bits);
__IO_REG8(     UART2_ILPR_BUF,      0x4C006020,__READ_WRITE);
__IO_REG16(    UART2_IBRD_BUF,      0x4C006024,__READ_WRITE);
__IO_REG16_BIT(UART2_FBRD_BUF,      0x4C006028,__READ_WRITE,__uart_fbrd_bits);
__IO_REG16_BIT(UART2_LCR_BUF,       0x4C00602C,__READ_WRITE,__uart_lcr_bits);
__IO_REG16_BIT(UART2_CR_BUF,        0x4C006030,__READ_WRITE,__uart_cr_bits);
__IO_REG16_BIT(UART2_IFLS_BUF,      0x4C006034,__READ_WRITE,__uart_ifls_bits);
__IO_REG16_BIT(UART2_IMSC_BUF,      0x4C006038,__READ_WRITE,__uart_imsc_bits);
__IO_REG16_BIT(UART2_RIS_BUF,       0x4C00603C,__READ      ,__uart_ris_bits);
__IO_REG16_BIT(UART2_MIS_BUF,       0x4C006040,__READ      ,__uart_mis_bits);
__IO_REG16_BIT(UART2_ICR_BUF,       0x4C006044,__WRITE     ,__uart_icr_bits);

/***************************************************************************
 **
 ** I2C0
 **
 ***************************************************************************/
__IO_REG8_BIT( I2C0_CR,             0x5C00C000,__READ_WRITE,__i2c_cr_bits);
__IO_REG8_BIT( I2C0_SR1,            0x5C00C004,__READ      ,__i2c_sr1_bits);
__IO_REG8_BIT( I2C0_SR2,            0x5C00C008,__READ      ,__i2c_sr2_bits);
__IO_REG8_BIT( I2C0_CCR,            0x5C00C00C,__READ_WRITE,__i2c_ccr_bits);
__IO_REG8(     I2C0_OAR1,           0x5C00C010,__READ_WRITE);
__IO_REG8_BIT( I2C0_OAR2,           0x5C00C014,__READ_WRITE,__i2c_oar2_bits);
__IO_REG8(     I2C0_DR,             0x5C00C018,__READ_WRITE);
__IO_REG8_BIT( I2C0_ECCR,           0x5C00C01C,__READ_WRITE,__i2c_eccr_bits);

/***************************************************************************
 **
 ** I2C0 Buffered
 **
 ***************************************************************************/
__IO_REG8_BIT( I2C0_CR_BUF,         0x4C00C000,__READ_WRITE,__i2c_cr_bits);
__IO_REG8_BIT( I2C0_SR1_BUF,        0x4C00C004,__READ      ,__i2c_sr1_bits);
__IO_REG8_BIT( I2C0_SR2_BUF,        0x4C00C008,__READ      ,__i2c_sr2_bits);
__IO_REG8_BIT( I2C0_CCR_BUF,        0x4C00C00C,__READ_WRITE,__i2c_ccr_bits);
__IO_REG8(     I2C0_OAR1_BUF,       0x4C00C010,__READ_WRITE);
__IO_REG8_BIT( I2C0_OAR2_BUF,       0x4C00C014,__READ_WRITE,__i2c_oar2_bits);
__IO_REG8(     I2C0_DR_BUF,         0x4C00C018,__READ_WRITE);
__IO_REG8_BIT( I2C0_ECCR_BUF,       0x4C00C01C,__READ_WRITE,__i2c_eccr_bits);

/***************************************************************************
 **
 ** I2C1
 **
 ***************************************************************************/
__IO_REG8_BIT( I2C1_CR,             0x5C00D000,__READ_WRITE,__i2c_cr_bits);
__IO_REG8_BIT( I2C1_SR1,            0x5C00D004,__READ      ,__i2c_sr1_bits);
__IO_REG8_BIT( I2C1_SR2,            0x5C00D008,__READ      ,__i2c_sr2_bits);
__IO_REG8_BIT( I2C1_CCR,            0x5C00D00C,__READ_WRITE,__i2c_ccr_bits);
__IO_REG8(     I2C1_OAR1,           0x5C00D010,__READ_WRITE);
__IO_REG8_BIT( I2C1_OAR2,           0x5C00D014,__READ_WRITE,__i2c_oar2_bits);
__IO_REG8(     I2C1_DR,             0x5C00D018,__READ_WRITE);
__IO_REG8_BIT( I2C1_ECCR,           0x5C00D01C,__READ_WRITE,__i2c_eccr_bits);

/***************************************************************************
 **
 ** I2C1 Buffered
 **
 ***************************************************************************/
__IO_REG8_BIT( I2C1_CR_BUF,         0x4C00D000,__READ_WRITE,__i2c_cr_bits);
__IO_REG8_BIT( I2C1_SR1_BUF,        0x4C00D004,__READ      ,__i2c_sr1_bits);
__IO_REG8_BIT( I2C1_SR2_BUF,        0x4C00D008,__READ      ,__i2c_sr2_bits);
__IO_REG8_BIT( I2C1_CCR_BUF,        0x4C00D00C,__READ_WRITE,__i2c_ccr_bits);
__IO_REG8(     I2C1_OAR1_BUF,       0x4C00D010,__READ_WRITE);
__IO_REG8_BIT( I2C1_OAR2_BUF,       0x4C00D014,__READ_WRITE,__i2c_oar2_bits);
__IO_REG8(     I2C1_DR_BUF,         0x4C00D018,__READ_WRITE);
__IO_REG8_BIT( I2C1_ECCR_BUF,       0x4C00D01C,__READ_WRITE,__i2c_eccr_bits);

/***************************************************************************
 **
 ** IMC
 **
 ***************************************************************************/
__IO_REG16(    MC_TCPT,             0x5C003000,__READ      );
__IO_REG8(     MC_TCMP,             0x5C003004,__READ_WRITE);
__IO_REG16_BIT(MC_IPR,              0x5C003008,__READ_WRITE,__mc_ipr_bits);
__IO_REG16_BIT(MC_TPRS,             0x5C00300C,__READ_WRITE,__mc_tprs_bits);
__IO_REG8(     MC_CPRS,             0x5C003010,__READ_WRITE);
__IO_REG8(     MC_REP,              0x5C003014,__READ_WRITE);
__IO_REG16_BIT(MC_CMPW,             0x5C003018,__READ_WRITE,__mc_cmpw_bits);
__IO_REG16_BIT(MC_CMPV,             0x5C00301C,__READ_WRITE,__mc_cmpv_bits);
__IO_REG16_BIT(MC_CMPU,             0x5C003020,__READ_WRITE,__mc_cmpu_bits);
__IO_REG16_BIT(MC_CMP0,             0x5C003024,__READ_WRITE,__mc_cmp0_bits);
__IO_REG16_BIT(MC_PCR0,             0x5C003028,__READ_WRITE,__mc_pcr0_bits);
__IO_REG16_BIT(MC_PCR1,             0x5C00302C,__READ_WRITE,__mc_pcr1_bits);
__IO_REG16_BIT(MC_PCR2,             0x5C003030,__READ_WRITE,__mc_pcr2_bits);
__IO_REG16_BIT(MC_PSR,              0x5C003034,__READ_WRITE,__mc_psr_bits);
__IO_REG16_BIT(MC_OPR,              0x5C003038,__READ_WRITE,__mc_opr_bits);
__IO_REG16_BIT(MC_IMR,              0x5C00303C,__READ_WRITE,__mc_imr_bits);
__IO_REG16_BIT(MC_DTG,              0x5C003040,__READ_WRITE,__mc_dtg_bits);
__IO_REG16(    MC_ESC,              0x5C003044,__READ_WRITE);

/***************************************************************************
 **
 ** IMC Buffered
 **
 ***************************************************************************/
__IO_REG16(    MC_TCPT_BUF,         0x4C003000,__READ      );
__IO_REG8(     MC_TCMP_BUF,         0x4C003004,__READ_WRITE);
__IO_REG16_BIT(MC_IPR_BUF,          0x4C003008,__READ_WRITE,__mc_ipr_bits);
__IO_REG16_BIT(MC_TPRS_BUF,         0x4C00300C,__READ_WRITE,__mc_tprs_bits);
__IO_REG8(     MC_CPRS_BUF,         0x4C003010,__READ_WRITE);
__IO_REG8(     MC_REP_BUF,          0x4C003014,__READ_WRITE);
__IO_REG16_BIT(MC_CMPW_BUF,         0x4C003018,__READ_WRITE,__mc_cmpw_bits);
__IO_REG16_BIT(MC_CMPV_BUF,         0x4C00301C,__READ_WRITE,__mc_cmpv_bits);
__IO_REG16_BIT(MC_CMPU_BUF,         0x4C003020,__READ_WRITE,__mc_cmpu_bits);
__IO_REG16_BIT(MC_CMP0_BUF,         0x4C003024,__READ_WRITE,__mc_cmp0_bits);
__IO_REG16_BIT(MC_PCR0_BUF,         0x4C003028,__READ_WRITE,__mc_pcr0_bits);
__IO_REG16_BIT(MC_PCR1_BUF,         0x4C00302C,__READ_WRITE,__mc_pcr1_bits);
__IO_REG16_BIT(MC_PCR2_BUF,         0x4C003030,__READ_WRITE,__mc_pcr2_bits);
__IO_REG16_BIT(MC_PSR_BUF,          0x4C003034,__READ_WRITE,__mc_psr_bits);
__IO_REG16_BIT(MC_OPR_BUF,          0x4C003038,__READ_WRITE,__mc_opr_bits);
__IO_REG16_BIT(MC_IMR_BUF,          0x4C00303C,__READ_WRITE,__mc_imr_bits);
__IO_REG16_BIT(MC_DTG_BUF,          0x4C003040,__READ_WRITE,__mc_dtg_bits);
__IO_REG16(    MC_ESC_BUF,          0x4C003044,__READ_WRITE);

/***************************************************************************
 **
 ** CAN
 **
 ***************************************************************************/
__IO_REG16_BIT(CAN_CR,              0x5C009000,__READ_WRITE,__can_cr_bits);
__IO_REG16_BIT(CAN_SR,              0x5C009004,__READ_WRITE,__can_sr_bits);
__IO_REG16_BIT(CAN_ERR,             0x5C009008,__READ      ,__can_err_bits);
__IO_REG16_BIT(CAN_BTR,             0x5C00900C,__READ_WRITE,__can_btr_bits);
__IO_REG16(    CAN_IDR,             0x5C009010,__READ      );
__IO_REG16_BIT(CAN_TESTR,           0x5C009014,__READ_WRITE,__can_testr_bits);
__IO_REG16_BIT(CAN_BRPR,            0x5C009018,__READ_WRITE,__can_brpr_bits);
__IO_REG16_BIT(CAN_IF1_CRR,         0x5C009020,__READ_WRITE,__can_if_crr_bits);
__IO_REG16_BIT(CAN_IF1_CMR,         0x5C009024,__READ_WRITE,__can_if_cmr_bits);
__IO_REG16(    CAN_IF1_M1R,         0x5C009028,__READ_WRITE);
__IO_REG16_BIT(CAN_IF1_M2R,         0x5C00902C,__READ_WRITE,__can_if_m2r_bits);
__IO_REG16(    CAN_IF1_A1R,         0x5C009030,__READ_WRITE);
__IO_REG16_BIT(CAN_IF1_A2R,         0x5C009034,__READ_WRITE,__can_if_a2r_bits);
__IO_REG16_BIT(CAN_IF1_MCR,         0x5C009038,__READ_WRITE,__can_if_mcr_bits);
__IO_REG16_BIT(CAN_IF1_DA1R,        0x5C00903C,__READ_WRITE,__can_if_da1r_bits);
__IO_REG16_BIT(CAN_IF1_DA2R,        0x5C009040,__READ_WRITE,__can_if_da2r_bits);
__IO_REG16_BIT(CAN_IF1_DB1R,        0x5C009044,__READ_WRITE,__can_if_db1r_bits);
__IO_REG16_BIT(CAN_IF1_DB2R,        0x5C009048,__READ_WRITE,__can_if_db2r_bits);
__IO_REG16_BIT(CAN_IF2_CRR,         0x5C009080,__READ_WRITE,__can_if_crr_bits);
__IO_REG16_BIT(CAN_IF2_CMR,         0x5C009084,__READ_WRITE,__can_if_cmr_bits);
__IO_REG16(    CAN_IF2_M1R,         0x5C009088,__READ_WRITE);
__IO_REG16_BIT(CAN_IF2_M2R,         0x5C00908C,__READ_WRITE,__can_if_m2r_bits);
__IO_REG16(    CAN_IF2_A1R,         0x5C009090,__READ_WRITE);
__IO_REG16_BIT(CAN_IF2_A2R,         0x5C009094,__READ_WRITE,__can_if_a2r_bits);
__IO_REG16_BIT(CAN_IF2_MCR,         0x5C009098,__READ_WRITE,__can_if_mcr_bits);
__IO_REG16_BIT(CAN_IF2_DA1R,        0x5C00909C,__READ_WRITE,__can_if_da1r_bits);
__IO_REG16_BIT(CAN_IF2_DA2R,        0x5C0090A0,__READ_WRITE,__can_if_da2r_bits);
__IO_REG16_BIT(CAN_IF2_DB1R,        0x5C0090A4,__READ_WRITE,__can_if_db1r_bits);
__IO_REG16_BIT(CAN_IF2_DB2R,        0x5C0090A8,__READ_WRITE,__can_if_db2r_bits);
__IO_REG32(    CAN_TxR1R,           0x5C009100,__READ      );
__IO_REG32(    CAN_TxR2R,           0x5C009104,__READ      );
__IO_REG32(    CAN_ND1R,            0x5C009120,__READ      );
__IO_REG32(    CAN_ND2R,            0x5C009124,__READ      );
__IO_REG32(    CAN_IP1R,            0x5C009140,__READ      );
__IO_REG32(    CAN_IP2R,            0x5C009144,__READ      );
__IO_REG32(    CAN_MV1R,            0x5C009160,__READ      );
__IO_REG32(    CAN_MV2R,            0x5C009164,__READ      );

/***************************************************************************
 **
 ** CAN Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(CAN_CR_BUF,          0x4C009000,__READ_WRITE,__can_cr_bits);
__IO_REG16_BIT(CAN_SR_BUF,          0x4C009004,__READ_WRITE,__can_sr_bits);
__IO_REG16_BIT(CAN_ERR_BUF,         0x4C009008,__READ      ,__can_err_bits);
__IO_REG16_BIT(CAN_BTR_BUF,         0x4C00900C,__READ_WRITE,__can_btr_bits);
__IO_REG16(    CAN_IDR_BUF,         0x4C009010,__READ      );
__IO_REG16_BIT(CAN_TESTR_BUF,       0x4C009014,__READ_WRITE,__can_testr_bits);
__IO_REG16_BIT(CAN_BRPR_BUF,        0x4C009018,__READ_WRITE,__can_brpr_bits);
__IO_REG16_BIT(CAN_IF1_CRR_BUF,     0x4C009020,__READ_WRITE,__can_if_crr_bits);
__IO_REG16_BIT(CAN_IF1_CMR_BUF,     0x4C009024,__READ_WRITE,__can_if_cmr_bits);
__IO_REG16(    CAN_IF1_M1R_BUF,     0x4C009028,__READ_WRITE);
__IO_REG16_BIT(CAN_IF1_M2R_BUF,     0x4C00902C,__READ_WRITE,__can_if_m2r_bits);
__IO_REG16(    CAN_IF1_A1R_BUF,     0x4C009030,__READ_WRITE);
__IO_REG16_BIT(CAN_IF1_A2R_BUF,     0x4C009034,__READ_WRITE,__can_if_a2r_bits);
__IO_REG16_BIT(CAN_IF1_MCR_BUF,     0x4C009038,__READ_WRITE,__can_if_mcr_bits);
__IO_REG16_BIT(CAN_IF1_DA1R_BUF,    0x4C00903C,__READ_WRITE,__can_if_da1r_bits);
__IO_REG16_BIT(CAN_IF1_DA2R_BUF,    0x4C009040,__READ_WRITE,__can_if_da2r_bits);
__IO_REG16_BIT(CAN_IF1_DB1R_BUF,    0x4C009044,__READ_WRITE,__can_if_db1r_bits);
__IO_REG16_BIT(CAN_IF1_DB2R_BUF,    0x4C009048,__READ_WRITE,__can_if_db2r_bits);
__IO_REG16_BIT(CAN_IF2_CRR_BUF,     0x4C009080,__READ_WRITE,__can_if_crr_bits);
__IO_REG16_BIT(CAN_IF2_CMR_BUF,     0x4C009084,__READ_WRITE,__can_if_cmr_bits);
__IO_REG16(    CAN_IF2_M1R_BUF,     0x4C009088,__READ_WRITE);
__IO_REG16_BIT(CAN_IF2_M2R_BUF,     0x4C00908C,__READ_WRITE,__can_if_m2r_bits);
__IO_REG16(    CAN_IF2_A1R_BUF,     0x4C009090,__READ_WRITE);
__IO_REG16_BIT(CAN_IF2_A2R_BUF,     0x4C009094,__READ_WRITE,__can_if_a2r_bits);
__IO_REG16_BIT(CAN_IF2_MCR_BUF,     0x4C009098,__READ_WRITE,__can_if_mcr_bits);
__IO_REG16_BIT(CAN_IF2_DA1R_BUF,    0x4C00909C,__READ_WRITE,__can_if_da1r_bits);
__IO_REG16_BIT(CAN_IF2_DA2R_BUF,    0x4C0090A0,__READ_WRITE,__can_if_da2r_bits);
__IO_REG16_BIT(CAN_IF2_DB1R_BUF,    0x4C0090A4,__READ_WRITE,__can_if_db1r_bits);
__IO_REG16_BIT(CAN_IF2_DB2R_BUF,    0x4C0090A8,__READ_WRITE,__can_if_db2r_bits);
__IO_REG32(    CAN_TxR1R_BUF,       0x4C009100,__READ      );
__IO_REG32(    CAN_TxR2R_BUF,       0x4C009104,__READ      );
__IO_REG32(    CAN_ND1R_BUF,        0x4C009120,__READ      );
__IO_REG32(    CAN_ND2R_BUF,        0x4C009124,__READ      );
__IO_REG32(    CAN_IP1R_BUF,        0x4C009140,__READ      );
__IO_REG32(    CAN_IP2R_BUF,        0x4C009144,__READ      );
__IO_REG32(    CAN_MV1R_BUF,        0x4C009160,__READ      );
__IO_REG32(    CAN_MV2R_BUF,        0x4C009164,__READ      );

/***************************************************************************
 **
 **  USB
 **
 ***************************************************************************/
__IO_REG16_BIT(USB_EP0R,            0x70000800,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP1R,            0x70000804,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP2R,            0x70000808,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP3R,            0x7000080C,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP4R,            0x70000810,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP5R,            0x70000814,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP6R,            0x70000818,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP7R,            0x7000081C,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP8R,            0x70000820,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP9R,            0x70000824,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_CNTR,            0x70000840,__READ_WRITE,__usb_cntr_bits);
__IO_REG16_BIT(USB_ISTR,            0x70000844,__READ_WRITE,__usb_st_bits);
__IO_REG16_BIT(USB_FNR,             0x70000848,__READ      ,__usb_fnr_bits);
__IO_REG16_BIT(USB_DADDR,           0x7000084C,__READ_WRITE,__usb_daddr_bits);
__IO_REG16_BIT(USB_BTABLE,          0x70000850,__READ_WRITE,__usb_btable_bits);
__IO_REG16_BIT(USB_DMACR1,          0x70000854,__READ_WRITE,__usb_dmacr1_bits);
__IO_REG16_BIT(USB_DMACR2,          0x70000858,__READ_WRITE,__usb_dmacr2_bits);
__IO_REG16_BIT(USB_DMACR3,          0x7000085C,__READ_WRITE,__usb_dmacr3_bits);
__IO_REG16_BIT(USB_DMABSIZE,        0x70000860,__READ_WRITE,__usb_dmabsize_bits);
__IO_REG16_BIT(USB_DMALLI,          0x70000864,__READ_WRITE,__usb_dmalli_bits);

/***************************************************************************
 **
 **  USB Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(USB_EP0R_BUF,        0x60000800,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP1R_BUF,        0x60000804,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP2R_BUF,        0x60000808,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP3R_BUF,        0x6000080C,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP4R_BUF,        0x60000810,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP5R_BUF,        0x60000814,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP6R_BUF,        0x60000818,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP7R_BUF,        0x6000081C,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP8R_BUF,        0x60000820,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_EP9R_BUF,        0x60000824,__READ_WRITE,__usb_epr_bits);
__IO_REG16_BIT(USB_CNTR_BUF,        0x60000840,__READ_WRITE,__usb_cntr_bits);
__IO_REG16_BIT(USB_ISTR_BUF,        0x60000844,__READ_WRITE,__usb_st_bits);
__IO_REG16_BIT(USB_FNR_BUF,         0x60000848,__READ      ,__usb_fnr_bits);
__IO_REG16_BIT(USB_DADDR_BUF,       0x6000084C,__READ_WRITE,__usb_daddr_bits);
__IO_REG16_BIT(USB_BTABLE_BUF,      0x60000850,__READ_WRITE,__usb_btable_bits);
__IO_REG16_BIT(USB_DMACR1_BUF,      0x60000854,__READ_WRITE,__usb_dmacr1_bits);
__IO_REG16_BIT(USB_DMACR2_BUF,      0x60000858,__READ_WRITE,__usb_dmacr2_bits);
__IO_REG16_BIT(USB_DMACR3_BUF,      0x6000085C,__READ_WRITE,__usb_dmacr3_bits);
__IO_REG16_BIT(USB_DMABSIZE_BUF,    0x60000860,__READ_WRITE,__usb_dmabsize_bits);
__IO_REG16_BIT(USB_DMALLI_BUF,      0x60000864,__READ_WRITE,__usb_dmalli_bits);

/***************************************************************************
 **
 **  ADC
 **
 ***************************************************************************/
__IO_REG16_BIT(ADC_CR,              0x5C00A000,__READ_WRITE,__adc_cr_bits);
__IO_REG16_BIT(ADC_CCR,             0x5C00A004,__READ_WRITE,__adc_ccr_bits);
__IO_REG16_BIT(ADC_LTR,             0x5C00A008,__READ_WRITE,__adc_ltr_bits);
__IO_REG16_BIT(ADC_HTR,             0x5C00A00C,__READ_WRITE,__adc_htr_bits);
__IO_REG16_BIT(ADC_CRR,             0x5C00A010,__READ_WRITE,__adc_crr_bits);
__IO_REG16_BIT(ADC_DR0,             0x5C00A014,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR1,             0x5C00A018,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR2,             0x5C00A01C,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR3,             0x5C00A020,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR4,             0x5C00A024,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR5,             0x5C00A028,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR6,             0x5C00A02C,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR7,             0x5C00A030,__READ      ,__adc_dr_bits);
__IO_REG8(     ADC_PRS,             0x5C00A034,__READ_WRITE);

/***************************************************************************
 **
 **  ADC Buffered
 **
 ***************************************************************************/
__IO_REG16_BIT(ADC_CR_BUF,          0x4C00A000,__READ_WRITE,__adc_cr_bits);
__IO_REG16_BIT(ADC_CCR_BUF,         0x4C00A004,__READ_WRITE,__adc_ccr_bits);
__IO_REG16_BIT(ADC_LTR_BUF,         0x4C00A008,__READ_WRITE,__adc_ltr_bits);
__IO_REG16_BIT(ADC_HTR_BUF,         0x4C00A00C,__READ_WRITE,__adc_htr_bits);
__IO_REG16_BIT(ADC_CRR_BUF,         0x4C00A010,__READ_WRITE,__adc_crr_bits);
__IO_REG16_BIT(ADC_DR0_BUF,         0x4C00A014,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR1_BUF,         0x4C00A018,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR2_BUF,         0x4C00A01C,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR3_BUF,         0x4C00A020,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR4_BUF,         0x4C00A024,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR5_BUF,         0x4C00A028,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR6_BUF,         0x4C00A02C,__READ      ,__adc_dr_bits);
__IO_REG16_BIT(ADC_DR7_BUF,         0x4C00A030,__READ      ,__adc_dr_bits);
__IO_REG8(     ADC_PRS_BUF,         0x4C00A034,__READ_WRITE);

/***************************************************************************
 **
 **  APB
 **
 ***************************************************************************/
__IO_REG32_BIT(APB_BSR,             0x58000000,__READ_WRITE,__apb_bsr_bits);
__IO_REG32_BIT(APB_BCR,             0x58000004,__READ_WRITE,__apb_bcr_bits);
__IO_REG32_BIT(APB_PAER,            0x58000008,__READ      ,__apb_paer_bits);

/***************************************************************************
 **
 **  APB Buffered
 **
 ***************************************************************************/
__IO_REG32_BIT(APB_BSR_BUF,         0x48000000,__READ_WRITE,__apb_bsr_bits);
__IO_REG32_BIT(APB_BCR_BUF,         0x48000004,__READ_WRITE,__apb_bcr_bits);
__IO_REG32_BIT(APB_PAER_BUF,        0x48000008,__READ      ,__apb_paer_bits);

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
#define VIC0_WDT         0  /* Watchdog                                    */
#define VIC0_SW          1  /* Software interrupts                         */
#define VIC0_DEBUGRX     2  /* Embedded ICE, DbgCommRx                     */
#define VIC0_DEBUGTX     3  /* Embedded ICE, DbgCommTx                     */
#define VIC0_TIMER0      4  /* Timer 0                                     */
#define VIC0_TIMER1      5  /* Timer 1                                     */
#define VIC0_TIMER2      6  /* Timer 2                                     */
#define VIC0_TIMER3      7  /* Timer 3                                     */
#define VIC0_USB_H       8  /* Logic OR of high priority USB interrupts    */
#define VIC0_USB_L       9  /* Logic OR of low priority USB interrupts     */
#define VIC1_USB_WU     10  /* USB Bus Resume Wake-up                      */
#define VIC0_EMAC       11  /* Ethernet MAC interrupts                     */
#define VIC0_DMA        12  /* DMA                                         */
#define VIC0_CAN        13  /* CAN interface interrupt                     */
#define VIC0_IMC        14  /* Induction Motor Control Unit interrupts     */
#define VIC0_ADC        15  /* A/D conversion or analog watchdog interrupt */
#define VIC1_UART0       0  /* UART channel 0                              */
#define VIC1_UART1       1  /* UART channel 1                              */
#define VIC1_UART2       2  /* UART channel 2                              */
#define VIC1_I2C0        3  /* I2C channel 0                               */
#define VIC1_I2C1        4  /* I2C channel 1                               */
#define VIC1_SSP0        5  /* SSP channel 0                               */
#define VIC1_SSP1        6  /* SSP channel 1                               */
#define VIC1_SCU         7  /* LVD early warning interrupt (Brownout)      */
#define VIC1_RTC         8  /* Alarm, Tamper, or Periodic Timer interrupts */
#define VIC1_WIU         9  /* WIU All                                     */
#define VIC1_WIU0       10  /* WIU Group 0                                 */
#define VIC1_WIU1       11  /* WIU Group 1                                 */
#define VIC1_WIU2       12  /* WIU Group 2                                 */
#define VIC1_WIU3       13  /* WIU Group 3                                 */
#define VIC0_SCU        14  /* System Control Unit(SCU)except Early warning*/
#define VIC1_PFQ_BC     15  /* Prefetch Queue and Branch Cache             */

/***************************************************************************
 **
 **  DMA Controller peripheral devices lines
 **
 ***************************************************************************/
#define DMA_USB_TX       0  /* USB TX                                      */
#define DMA_USB_RX       1  /* USB RX                                      */
#define DMA_TIM0         2  /* TIM 0                                       */
#define DMA_TIM1         3  /* TIM 1                                       */
#define DMA_UART0_TX     4  /* UART0 TX                                    */
#define DMA_UART0_RX     5  /* UART0 RX                                    */
#define DMA_UART1_TX     6  /* UART1 TX                                    */
#define DMA_UART1_RX     7  /* UART1 RX                                    */
#define DMA_EXT_REQ1     8  /* External request 1 Shared with GPIO         */
#define DMA_EXT_REQ2     9  /* External request 1 Shared with GPIO         */
#define DMA_I2C0        10  /* I2C 0                                       */
#define DMA_I2C1        11  /* I2C 1                                       */
#define DMA_SSP0_TX     12  /* SSP0 TX                                     */
#define DMA_SSP0_RX     13  /* SSP0 RX                                     */
#define DMA_SSP1_TX     14  /* SSP1 TX                                     */
#define DMA_SSP1_RX     15  /* SSP1 RX                                     */

#endif    /* __IOSTR912_H */
