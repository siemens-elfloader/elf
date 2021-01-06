/***************************************************************************
 **
 **    This file defines the special function registers for the
 **    Texas Instrument TMS470R1A64 device.
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2004
 **
 **    $Revision: 1.2.2.1 $
 **    $Revision: 1.2.2.1 $ Corrected CAN Names
 **
 ***************************************************************************/

#ifndef __IOTMS470R1A64_H
#define __IOTMS470R1A64_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4f = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    IOTMS470R1A64 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#if __LITTLE_ENDIAN__ == 1
#error This file should only be compiled in big endian mode
#endif


/* MPU control register */
typedef struct {
  __REG32 CHAN0Special    :1;
  __REG32 CHAN0EN         :1;
  __REG32 CHAN0PRIV       :1;
  __REG32 CHAN0RONLY      :1;
  __REG32 CHAN1Special    :1;
  __REG32 CHAN1EN         :1;
  __REG32 CHAN1PRIV       :1;
  __REG32 CHAN1RONLY      :1;
  __REG32 CHAN2Special    :1;
  __REG32 CHAN2EN         :1;
  __REG32 CHAN2PRIV       :1;
  __REG32 CHAN2RONLY      :1;
  __REG32 CHAN3Special    :1;
  __REG32 CHAN3EN         :1;
  __REG32 CHAN3PRIV       :1;
  __REG32 CHAN3RONLY      :1;
  __REG32                 :16;
} __mpuctrl_bits;

/* MPUAHR MPU Address High Register */
typedef struct {
  __REG32 UPPERBOUND      :16;
  __REG32                 :16;
} __mpuahr_bits;

/* MPUALR MPU Address Low Register */
typedef struct {
  __REG32 LOWERBOUND      :16;
  __REG32 EQUAL           :3;
  __REG32                 :13;
} __mpualr_bits;

/* Static memory control register 0 */
typedef struct {
  __REG32 DW              :2;
  __REG32                 :1;
  __REG32 END             :1;
  __REG32 WS              :4;
  __REG32                 :1;
  __REG32 TWS             :3;
  __REG32 ASC             :2;
  __REG32                 :18;
} __smcr0_bits;

/* Static memory control registers 1 - 9 */
typedef struct {
  __REG32 DW              :2;
  __REG32 MLOC            :1;
  __REG32 END             :1;
  __REG32 WS              :4;
  __REG32                 :1;
  __REG32 TWS             :3;
  __REG32 ASC             :2;
  __REG32                 :18;
} __smcrx_bits;

/* Write control register */
typedef struct {
  __REG32 WBENABLE        :1;
  __REG32 WTWSOVR         :1;
  __REG32                 :30;
} __wcr_bits;

/* Peripheral clock register */
typedef struct {
  __REG32 PENABLE         :1;
  __REG32 CLKDIV          :4;
  __REG32                 :27;
} __pcr_bits;

/* Peripheral location register */
typedef struct {
  __REG32 PLOC0           :1;
  __REG32 PLOC1           :1;
  __REG32 PLOC2           :1;
  __REG32 PLOC3           :1;
  __REG32 PLOC4           :1;
  __REG32 PLOC5           :1;
  __REG32 PLOC6           :1;
  __REG32 PLOC7           :1;
  __REG32 PLOC8           :1;
  __REG32 PLOC9           :1;
  __REG32 PLOC10          :1;
  __REG32 PLOC11          :1;
  __REG32 PLOC12          :1;
  __REG32 PLOC13          :1;
  __REG32 PLOC14          :1;
  __REG32 PLOC15          :1;
  __REG32                 :16;
} __plr_bits;

/* Peripheral protection register */
typedef struct {
  __REG32 PPROT0           :1;
  __REG32 PPROT1           :1;
  __REG32 PPROT2           :1;
  __REG32 PPROT3           :1;
  __REG32 PPROT4           :1;
  __REG32 PPROT5           :1;
  __REG32 PPROT6           :1;
  __REG32 PPROT7           :1;
  __REG32 PPROT8           :1;
  __REG32 PPROT9           :1;
  __REG32 PPROT10          :1;
  __REG32 PPROT11          :1;
  __REG32 PPROT12          :1;
  __REG32 PPROT13          :1;
  __REG32 PPROT14          :1;
  __REG32 PPROT15          :1;
  __REG32                 :16;
} __pprot_bits;

/* Memory Fine Base Address High Registers */
typedef struct {
  __REG32 Address31_16    :16;
  __REG32                 :16;
} __mfbahr_bits;

/* Memory Fine Base Address Low Registers 0 */
typedef struct {
  __REG32 PRIV            :1;
  __REG32 RONLY           :1;
  __REG32                 :2;
  __REG32 BlockSize       :4;
  __REG32 MS              :1;
  __REG32                 :1;
  __REG32 Address15_10    :6;
  __REG32                 :16;
} __mfbalr0_bits;

/* Memory Fine Base Address Low Registers 1 - 9 */
typedef struct {
  __REG32 PRIV            :1;
  __REG32 RONLY           :1;
  __REG32                 :2;
  __REG32 BlockSize       :4;
  __REG32                 :1;
  __REG32 AW              :1;
  __REG32 Address15_10    :6;
  __REG32                 :16;
} __mfbalrx_bits;

/* Memory Coarse Base Address High Registers */
typedef struct {
  __REG32 Address31_16    :16;
  __REG32                 :16;
} __mcbahr_bits;

/* Memory Coarse Base Address Low Registers */
typedef struct {
  __REG32 PRIV            :1;
  __REG32 RONLY           :1;
  __REG32                 :2;
  __REG32 BlockSize       :4;
  __REG32                 :1;
  __REG32 AW              :1;
  __REG32                 :5;
  __REG32 Address15       :1;
  __REG32                 :16;
} __mcbalr_bits;

/* RTI Counter */
typedef struct {
  __REG32 MOD10_0         :11;
  __REG32 CNTR20_0        :21;
} __rticntr_bits;

/* RTI Preload Control Register */
typedef struct {
  __REG32 PRELD10_0       :11;
  __REG32 RTIM2_0         :3;
  __REG32                 :18;
} __rtipctl_bits;

/* RTI Control Register */
typedef struct {
  __REG32                 :6;
  __REG32 TAPENA          :1;
  __REG32 TAPFLAG         :1;
  __REG32                 :24;
} __rticntl_bits;

/* RTI Compare Register1 */
typedef struct {
  __REG32 COMPARE1_20_0   :21;
  __REG32                 :11;
} __rticmp1_bits;

/* RTI Compare Register2 */
typedef struct {
  __REG32 COMPARE2_20_0   :21;
  __REG32                 :11;
} __rticmp2_bits;

/* RTI Compare Interrupt Control Register */
typedef struct {
  __REG32                 :4;
  __REG32 CMP2ENA         :1;
  __REG32 CMP1ENA         :1;
  __REG32 CMP2FLAG        :1;
  __REG32 CMP1FLAG        :1;
  __REG32                 :24;
} __rticint_bits;

/* RTICNTEN RTI Count Enable Register */
typedef struct {
  __REG32 CNTEN           :2;
  __REG32                 :30;
} __rticnten_bits;

/* CLKCNTL Clock Control Register */
typedef struct {
  __REG32 LPM             :2;
  __REG32 CLK_DIN         :1;
  __REG32 CLK_DOUT        :1;
  __REG32 CLK_DIR         :1;
  __REG32 CLKSR           :2;
  __REG32 PPW_NOVR        :1;
  __REG32                 :24;
} __clkcntl_bits;

/* GCR Global Control Register (old name GLBCTRL) */
typedef struct {
  __REG32 CLK_DIV_PRE     :3;
  __REG32 MULT4           :1;
  __REG32 FLCONFIG        :1;
  __REG32                 :9;
  __REG32 RTI_CTRL        :1;
  __REG32 RST_OSC_FAIL_EN :1;
  __REG32                 :16;
} __gcr_bits;

/* SYSECR System Exception Control Register */
typedef struct {
  __REG32 ILL_OVR         :1;
  __REG32 ACC_OVR         :1;
  __REG32 PACC_OVR        :1;
  __REG32                 :11;
  __REG32 RESET           :2;
  __REG32                 :16;
} __sysecr_bits;

/* SYSESR System Reset Exception Status Register */
typedef struct {
  __REG32                 :7;
  __REG32 SW_RST          :1;
  __REG32 ILL_MAP         :1;
  __REG32 PILL_ACC        :1;
  __REG32 ILL_ACC         :1;
  __REG32 ILL_ADR         :1;
  __REG32 ILL_MODE        :1;
  __REG32 WD_RST          :1;
  __REG32 CLK_RST         :1;
  __REG32 POR_RST         :1;
  __REG32                 :16;
} __sysesr_bits;

/* ABRTESR Abort Exception Status Register */
typedef struct {
  __REG32                 :13;
  __REG32 PACC_VIO        :1;
  __REG32 MEM_ABT         :1;
  __REG32 ADR_ABT         :1;
  __REG32                 :16;
} __abrtesr_bits;

/* IRQIVEC IRQ Index Offset Vector Register */
typedef struct {
  __REG32 IRQIVEC_7_0     :8;
  __REG32                 :24;
} __irqivec_bits;

/* FIQIVEC FIQ Index Offset Vector Registers */
typedef struct {
  __REG32 FIQIVEC_7_0     :8;
  __REG32                 :24;
} __fiqivec_bits;

/* CIMIVEC CIM Index Offset Vector Register */
typedef struct {
  __REG32 CIMIVEC_7_0     :8;
  __REG32                 :24;
} __cimivec_bits;

/* PSAENABLE PSA Enable */
typedef struct {
  __REG32 PSADIS          :1;
  __REG32                 :31;
} __psaenable_bits;

/* GLBSTAT Global Status Register */
typedef struct {
  __REG32 PLL_SLIP        :1;
  __REG32 OSC_FAIL        :1;
  __REG32                 :2;
  __REG32 MPU_ACC         :1;
  __REG32 MPU_ADDR        :1;
  __REG32 SYS_ACC         :1;
  __REG32 SYS_ADDR        :1;
  __REG32                 :24;
} __glbstat_bits;

/* DEV Device Identification Register */
typedef struct {
  __REG32 DEV_15_0        :16;
  __REG32                 :16;
} __dev_bits;

/* SSIF System Software Interrupt Flag Register */
typedef struct {
  __REG32 SSIF            :1;
  __REG32                 :31;
} __ssif_bits;

/* SSIR System Software Interrupt Request Register */
typedef struct {
  __REG32 SSDATA_7_0      :8;
  __REG32 SSKEY_7_0       :8;
  __REG32                 :16;
} __ssir_bits;


/* HETGCR Global Configuration Register */
typedef struct {
  __REG32 ON              :1;
  __REG32 IGNORE_SUSPEND  :1;
  __REG32 DEBUG_STATUS    :1;
  __REG32                 :5;
  __REG32 ACCESS64        :1;
  __REG32                 :7;
  __REG32 CLK_MASTER      :1;
  __REG32                 :7;
  __REG32 POWER_DOWN      :1;
  __REG32                 :7;
} __hetgcr_bits;

/* HETPFR Prescale Factor Register */
typedef struct {
  __REG32 HRPRES_FACTOR   :6;
  __REG32                 :2;
  __REG32 LRPRES_FACTOR   :3;
  __REG32                 :21;
} __hetpfr_bits;

/* HETADDR HET Current Address Register */
typedef struct {
  __REG32 HETADDR         :8;
  __REG32                 :24;
} __hetaddr_bits;

/* HETOFF Offset Level Register */
typedef struct {
  __REG32 OFFSET          :8;
  __REG32                 :24;
} __hetoff_bits;

/* HETEXC1 Exception Control Register 1 */
typedef struct {
  __REG32 PRGM_OVRFL_PRY  :1;
  __REG32 APCNT_UNDRFL_PRY:1;
  __REG32 APCNT_OVRFL_PRY :1;
  __REG32                 :5;
  __REG32 PRGM_OVRFL_ENA  :1;
  __REG32                 :7;
  __REG32 APCNT_UNDRFL_ENA:1;
  __REG32                 :7;
  __REG32 APCNT_OVRFL_ENA :1;
  __REG32                 :7;
} __hetexc1_bits;

/* HETEXC2 Exception Control Register 2 */
typedef struct {
  __REG32 PRGM_OVRFL_FLG  :1;
  __REG32 APCNT_UNDRFL_FLG:1;
  __REG32 APCNT_OVRFL_FLG :1;
  __REG32                 :29;
} __hetexc2_bits;

/* HETHRSH HR Share Control Register */
typedef struct {
  __REG32 HR_SHARE_0_1    :1;
  __REG32 HR_SHARE_2_3    :1;
  __REG32 HR_SHARE_4_5    :1;
  __REG32 HR_SHARE_6_7    :1;
  __REG32 HR_SHARE_8_9    :1;
  __REG32 HR_SHARE_10_11  :1;
  __REG32 HR_SHARE_12_13  :1;
  __REG32 HR_SHARE_14_15  :1;
  __REG32 HR_SHARE_16_17  :1;
  __REG32 HR_SHARE_18_19  :1;
  __REG32 HR_SHARE_20_21  :1;
  __REG32 HR_SHARE_22_23  :1;
  __REG32                 :20;
} __hethrsh_bits;

/* HETXOR HR XOR Control Register */
typedef struct {
  __REG32 HR_XOR_SHARE_0_1  :1;
  __REG32 HR_XOR_SHARE_2_3  :1;
  __REG32 HR_XOR_SHARE_4_5  :1;
  __REG32 HR_XOR_SHARE_6_7  :1;
  __REG32 HR_XOR_SHARE_8_9  :1;
  __REG32 HR_XOR_SHARE_10_11:1;
  __REG32 HR_XOR_SHARE_12_13:1;
  __REG32 HR_XOR_SHARE_14_15:1;
  __REG32 HR_XOR_SHARE_16_17:1;
  __REG32 HR_XOR_SHARE_18_19:1;
  __REG32 HR_XOR_SHARE_20_21:1;
  __REG32 HR_XOR_SHARE_22_23:1;
  __REG32                   :20;
} __hetxor_bits;

/* SPICTRL1 SPI Control Register 1 */
typedef struct {
  __REG32 CHARLEN         :5;
  __REG32 PRESCALE        :8;
  __REG32                 :19;
} __spictrl1_bits;

/* SPICTRL2 SPI Control Register 2 */
typedef struct {
  __REG32 PHASE           :1;
  __REG32 POLARITY        :1;
  __REG32 PWRDN           :1;
  __REG32 MASTER          :1;
  __REG32 SPIEN           :1;
  __REG32 CLKMOD          :1;
  __REG32                 :26;
} __spictrl2_bits;

/* SPICTRL3 SPI Control Register 3 */
typedef struct {
  __REG32 RXINTFLAG       :1;
  __REG32 RXINTEN         :1;
  __REG32 RCVR_OVRN       :1;
  __REG32 OVRNINTEN       :1;
  __REG32                 :1;
  __REG32 ENABLE_HIGH_Z   :1;
  __REG32                 :26;
} __spictrl3_bits;

/* SPIDAT1 SPI Shift Register 0 */
typedef struct {
  __REG32 SPIDAT0         :16;
  __REG32                 :16;
} __spidat0_bits;

/* SPIDAT1 SPI Shift Register 1 */
typedef struct {
  __REG32 SPIDAT1         :16;
  __REG32                 :16;
} __spidat1_bits;

/* SPIBUF SPI Buffer Register */
typedef struct {
  __REG32 SPIBUF          :16;
  __REG32 RXINTFLAG_IMG   :1;
  __REG32 RCVR_OVRN_IMG   :1;
  __REG32                 :14;
} __spibuf_bits;

/* SPIEMU SPI Emulation Register */
typedef struct {
  __REG32 SPIEMU          :16;
  __REG32                 :16;
} __spiemu_bits;

/* SPIPC1 SPI Pin Control Register 1 */
typedef struct {
  __REG32 ENA_DIR         :1;
  __REG32 CLK_DIR         :1;
  __REG32 SIMO_DIR        :1;
  __REG32 SOMI_DIR        :1;
  __REG32 SCS_DIR         :1;
  __REG32                 :27;
} __spipc1_bits;

/* SPIPC2 SPI Pin Control Register 2 */
typedef struct {
  __REG32 ENA_DIN         :1;
  __REG32 CLK_DIN         :1;
  __REG32 SIMO_DIN        :1;
  __REG32 SOMI_DIN        :1;
  __REG32 SCS_DIN         :1;
  __REG32                 :27;
} __spipc2_bits;

/* SPIPC3 SPI Pin Control Register 3 */
typedef struct {
  __REG32 ENA_DOUT        :1;
  __REG32 CLK_DOUT        :1;
  __REG32 SIMO_DOUT       :1;
  __REG32 SOMI_DOUT       :1;
  __REG32 SCS_DOUT        :1;
  __REG32                 :27;
} __spipc3_bits;

/* SPIPC4 SPI Pin Control Register 4 */
typedef struct {
  __REG32 ENA_DSET        :1;
  __REG32 CLK_DSET        :1;
  __REG32 SIMO_DSET       :1;
  __REG32 SOMI_DSET       :1;
  __REG32 SCS_DSET        :1;
  __REG32                 :27;
} __spipc4_bits;

/* SPIPC5 SPI Pin Control Register 5 */
typedef struct {
  __REG32 ENA_DCLR        :1;
  __REG32 CLK_DCLR        :1;
  __REG32 SIMO_DCLR       :1;
  __REG32 SOMI_DCLR       :1;
  __REG32 SCS_DCLR        :1;
  __REG32                 :27;
} __spipc5_bits;

/* SPIPC6 SPI Pin Control Register 6 */
typedef struct {
  __REG32 ENA_FUN         :1;
  __REG32 CLK_FUN         :1;
  __REG32 SIMO_FUN        :1;
  __REG32 SOMI_FUN        :1;
  __REG32 SCS_FUN         :1;
  __REG32                 :27;
} __spipc6_bits;

/* SCICCR Communication Control Register */
typedef struct {
  __REG8 CHAR0           :1;
  __REG8 CHAR1           :1;
  __REG8 CHAR2           :1;
  __REG8 COMM_MODE       :1;
  __REG8 TIMING_MODE     :1;
  __REG8 PARITY_ENA      :1;
  __REG8 PARITY          :1;
  __REG8 STOP            :1;
} __sciccr_bits;

/* SCICTL1 SCI Control Register 1 */
typedef struct {
  __REG8 RXENA           :1;
  __REG8 RXWAKE          :1;
  __REG8 RXRDY           :1;
  __REG8 SLEEP           :1;
  __REG8 IDLE            :1;
  __REG8                 :3;
} __scictl1_bits;

/* SCICTL2 SCI Control Register 2 */
typedef struct {
  __REG8 TXENA           :1;
  __REG8 TXWAKE          :1;
  __REG8 TXRDY           :1;
  __REG8 TX_EMPTY        :1;
  __REG8                 :2;
  __REG8 LOOP_BACK       :1;
  __REG8 CONT            :1;
} __scictl2_bits;

/* SCICTL3 SCI Control Register 3 */
typedef struct {
  __REG8 RXERR_INT_ENA   :1;
  __REG8 BRKDT_INT_ENA   :1;
  __REG8 WAKEUP_INT_ENA  :1;
  __REG8 TX_ACTION_ENA   :1;
  __REG8 RX_ACTION_ENA   :1;
  __REG8 CLOCK           :1;
  __REG8 POWER_DOWN      :1;
  __REG8 SW_RESET        :1;
} __scictl3_bits;

/* SCIRXST Receiver Status Register */
typedef struct {
  __REG8 RXERR           :1;
  __REG8 BRKDT           :1;
  __REG8 WAKEUP          :1;
  __REG8 PE              :1;
  __REG8 OE              :1;
  __REG8 FE              :1;
  __REG8                 :1;
  __REG8 BUS_BUSY        :1;
} __scirxst_bits;

/* SCIPC1 Pin Control Register 1 */
typedef struct {
  __REG8 CLK_DATA_DIR    :1;
  __REG8 CLK_FUNC        :1;
  __REG8 CLK_DATA_OUT    :1;
  __REG8 CLK_DATA_IN     :1;
  __REG8                 :4;
} __scipc1_bits;

/* SCIPC2 Pin Control Register 2 */
typedef struct {
  __REG8 RX_DATA_DIR     :1;
  __REG8 RX_FUNC         :1;
  __REG8 RX_DATA_OUT     :1;
  __REG8 RX_DATA_IN      :1;
  __REG8                 :4;
} __scipc2_bits;

/* SCIPC3 Pin Control Register 2 */
typedef struct {
  __REG8 TX_DATA_DIR     :1;
  __REG8 TX_FUNC         :1;
  __REG8 TX_DATA_OUT     :1;
  __REG8 TX_DATA_IN      :1;
  __REG8                 :4;
} __scipc3_bits;

/* ADCR1 AD Control Register 1 */
typedef struct {
  __REG16 PS              :3;
  __REG16 ACQ             :2;
  __REG16 ADC_EN          :1;
  __REG16                 :2;
  __REG16 PWR_DN          :1;
  __REG16 SELF_TST        :1;
  __REG16 HILO            :1;
  __REG16 BRIDGE_EN       :1;
  __REG16 CAL_ST          :1;
  __REG16 CAL_EN          :1;
  __REG16                 :1;
  __REG16 COS             :1;
} __adccr1_bits;

/* ADCR2 AD Control Register 2 */
typedef struct {
  __REG16 ENA_G2_INT      :1;
  __REG16 FRZ_G2          :1;
  __REG16 G2_MODE         :1;
  __REG16 ENA_G1_INT      :1;
  __REG16 FRZ_G1          :1;
  __REG16 G1_MODE         :1;
  __REG16                 :2;
  __REG16 EV_EDG_SEL      :1;
  __REG16 ENA_EV_INT      :1;
  __REG16 FRZ_EV          :1;
  __REG16 EV_MODE         :1;
  __REG16                 :4;
} __adccr2_bits;

/* ADSR AD Status Register */
typedef struct {
  __REG16 EV_END          :1;
  __REG16 G2_END          :1;
  __REG16 G1_END          :1;
  __REG16                 :5;
  __REG16 EV_STOP         :1;
  __REG16 G2_STOP         :1;
  __REG16 G1_STOP         :1;
  __REG16 EV_BUSY         :1;
  __REG16 G2_BUSY         :1;
  __REG16 G1_BUSY         :1;
  __REG16                 :2;
} __adsr_bits;

/* ADCALR Calibration and Offset Error Correction Register */
typedef struct {
  __REG16 CALR            :10;
  __REG16                 :6;
} __adcalr_bits;

/* ADDR0 Digital Result Registers */
typedef struct {
  __REG16 DT              :10;
  __REG16                 :5;
  __REG16 DT_ST           :1;
} __addr_bits;

/* ADEMDR0 Emulation Digital Result Registers */
typedef struct {
  __REG16 EDT_9_0         :10;
  __REG16                 :5;
  __REG16 EDT_ST          :1;
} __ademdr_bits;

typedef union {
  /* ADEMDR0 Emulation Digital Result Registers */
  struct {
    __REG16 EDT_9_0         :10;
    __REG16                 :5;
    __REG16 EDT_ST          :1;
  };
  /* ADBUFE AD Event FIFO Buffer */
  struct {
    __REG16 EVDR            :10;
    __REG16 EVCHID          :4;
    __REG16                 :1;
    __REG16 EV_EMPTY        :1;
  };
} __ademdr014adbufe_bits;

typedef union{
  /* Buffered mode */
  /* ADEMDR4 Emulation Digital Result Registers */
  struct {
    __REG16 EDT_9_0         :10;
    __REG16                 :5;
    __REG16 EDT_ST          :1;
  };
  /* Compatibility mode */
  /* ADBUF1 AD Group 1 FIFO Buffer */
  struct {
    __REG16 G1DR            :10;
    __REG16 G1CHID          :4;
    __REG16                 :1;
    __REG16 G1_EMPTY        :1;
  };
} __ademdr4adbuf1_bits;

typedef union{
  /* Buffered mode */
  /* ADEMDR8 ADMDR15 Emulation Digital Result Registers */
  struct {
    __REG16 EDT_9_0         :10;
    __REG16                 :5;
    __REG16 EDT_ST          :1;
  };
  /* Compatibility mode */
  /* ADBUF2 AD Group 2 FIFO Buffer */
  struct {
    __REG16 G2DR            :10;
    __REG16 G2CHID          :4;
    __REG16                 :1;
    __REG16 G2_EMPTY        :1;
  };
} __ademdr815adbuf2_bits;

typedef union{
  /* Buffered mode */
  /* ADDR15 Digital Result Registers */
  struct {
    __REG16 DT              :10;
    __REG16                 :5;
    __REG16 DT_ST           :1;
  };
  /* Compatibility mode */
  /* ADBUF1 AD Group 1 FIFO Buffer */
  struct {
    __REG16 G1DR            :10;
    __REG16 G1CHID          :4;
    __REG16                 :1;
    __REG16 G1_EMPTY        :1;
  };
} __addr15ademubuf1_bits;

/* ADCPCR Pin Control Register */
typedef struct {
  __REG16 EVT_DIR         :1;
  __REG16                 :1;
  __REG16 EVT_OUT         :1;
  __REG16 EVT_IN          :1;
  __REG16                 :12;
} __adcpcr_bits;

/* ADBCR1 AD Buffer Control Register 1 */
typedef struct {
  __REG16 BNDB            :8;
  __REG16 BNDA            :7;
  __REG16 BUFEN           :1;
} __adbcr1_bits;

/* ADBCR2 AD Buffer Control Register 2 */
typedef struct {
  __REG16 BINDEND         :3;
  __REG16                 :13;
} __adbcr2_bits;

/* ADBCR3 AD Buffer Control Register 3 */
typedef struct {
  __REG16 CHID            :1;
  __REG16 G2_8_BIT        :1;
  __REG16 G1_8_BIT        :1;
  __REG16 EV_8_BIT        :1;
  __REG16                 :3;
  __REG16 G2_BUF_INTEN    :1;
  __REG16 G1_BUF_INTEN    :1;
  __REG16 EV_BUF_INTEN    :1;
  __REG16 G2_OVR_INTEN    :1;
  __REG16 G1_OVR_INTEN    :1;
  __REG16 EV_OVR_INTEN    :1;
  __REG16                 :3;
} __adbcr3_bits;

/* ADBUFST AD Buffer Status Register */
typedef struct {
  __REG16 G2_EMPTY        :1;
  __REG16 G1_EMPTY        :1;
  __REG16 EV_EMPTY        :1;
  __REG16                 :1;
  __REG16 G2_OVR_FLAG     :1;
  __REG16 G1_OVR_FLAG     :1;
  __REG16 EV_OVR_FLAG     :1;
  __REG16                 :1;
  __REG16 G2_INT_FLAG     :1;
  __REG16 G1_INT_FLAG     :1;
  __REG16 EV_INT_FLAG     :1;
  __REG16                 :5;
} __adbufst_bits;

/* ADTHREV AD Event Group Threshold Counter */
typedef struct {
  __REG16 EVTHR           :10;
  __REG16 SIGN_EX         :6;
} __adthrev_bits;

/* ADTHRG1 AD Group 1 Threshold Counter */
typedef struct {
  __REG16 G1THR           :10;
  __REG16 SIGN_EX         :6;
} __adthrg1_bits;

/* ADTHRG2 AD Group 2 Threshold Counter */
typedef struct {
  __REG16 G2THR           :10;
  __REG16 SIGN_EX         :6;
} __adthrg2_bits;

/* ADSAMPEV AD Sample Time Event Register */
typedef struct {
  __REG16 EVACQ           :8;
  __REG16                 :7;
  __REG16 SEN             :1;
} __adsampev_bits;

/* ADSAMP1 AD Sample Time Group 1 Register */
typedef struct {
  __REG16 G1ACQ           :8;
  __REG16                 :8;
} __adsamp1_bits;

/* ADSAMP2 AD Sample Time Group 2 Register */
typedef struct {
  __REG16 G2ACQ           :8;
  __REG16                 :8;
} __adsamp2_bits;

/* ADEVTSRC AD Event Source Register */
typedef struct {
  __REG16 EVSRC           :2;
  __REG16                 :2;
  __REG16 G1SRC           :2;
  __REG16                 :1;
  __REG16 G1_EDG_SEL      :1;
  __REG16 G1_ENA          :1;
  __REG16                 :7;
} __adevtsrc_bits;

/* ECPCTRL ECP Control Register */
typedef struct {
  __REG16 ECPDIV          :8;
  __REG16 ECPCOS          :1;
  __REG16                 :6;
  __REG16 ECPEN           :1;
} __ecpctrl_bits;

/* GIOPWDN GIO Power Down */
typedef struct {
  __REG32 GIOPWDN         :1;
  __REG32                 :31;
} __giopwdn_bits;

/* GIOENA1 GIO Interrupt Enable */
typedef struct {
  __REG32 ENA_A           :8;
  __REG32 ENA_B           :8;
  __REG32                 :16;
} __gioena1_bits;

/* GIOPOL1 GIO Interrupt Polarity */
typedef struct {
  __REG32 POL_A           :8;
  __REG32 POL_B           :8;
  __REG32                 :16;
} __giopol1_bits;

/* GIOFLG1 GIO Interrupt Flag */
typedef struct {
  __REG32 FLG_A           :8;
  __REG32 FLG_B           :8;
  __REG32                 :16;
} __gioflg1_bits;

/* GIOPRY1 GIO Interrupt Priority */
typedef struct {
  __REG32 PRY_A           :8;
  __REG32 PRY_B           :8;
  __REG32                 :16;
} __giopry1_bits;

/* GIOOFFA GIO Offset A */
typedef struct {
  __REG32 GIOOFFA         :7;
  __REG32                 :25;
} __giooffa_bits;

/* GIOEMUA GIO Emulation A */
typedef struct {
  __REG32 GIOEMUA         :7;
  __REG32                 :25;
} __gioemua_bits;

/* GIOOFFB GIO Offset B */
typedef struct {
  __REG32 GIOOFFB         :7;
  __REG32                 :25;
} __giooffb_bits;

/* GIOEMUB GIO Emulation B */
typedef struct {
  __REG32 GIOEMUB         :7;
  __REG32                 :25;
} __gioemub_bits;

/* GIODIRx GIO Data Direction */
typedef struct {
  __REG32 GIODIR0         :1;
  __REG32 GIODIR1         :1;
  __REG32 GIODIR2         :1;
  __REG32 GIODIR3         :1;
  __REG32 GIODIR4         :1;
  __REG32 GIODIR5         :1;
  __REG32 GIODIR6         :1;
  __REG32 GIODIR7         :1;
  __REG32                 :24;
} __giodir_bits;

/* GIODINx GIO Data Input */
typedef struct {
  __REG32 GIODIN0         :1;
  __REG32 GIODIN1         :1;
  __REG32 GIODIN2         :1;
  __REG32 GIODIN3         :1;
  __REG32 GIODIN4         :1;
  __REG32 GIODIN5         :1;
  __REG32 GIODIN6         :1;
  __REG32 GIODIN7         :1;
  __REG32                 :24;
} __giodin_bits;

/* GIODOUTx GIO Data Output */
typedef struct {
  __REG32 GIODOUT0        :1;
  __REG32 GIODOUT1        :1;
  __REG32 GIODOUT2        :1;
  __REG32 GIODOUT3        :1;
  __REG32 GIODOUT4        :1;
  __REG32 GIODOUT5        :1;
  __REG32 GIODOUT6        :1;
  __REG32 GIODOUT7        :1;
  __REG32                 :24;
} __giodout_bits;

/* GIODSETx GIO Data Set */
typedef struct {
  __REG32 GIODSET0        :1;
  __REG32 GIODSET1        :1;
  __REG32 GIODSET2        :1;
  __REG32 GIODSET3        :1;
  __REG32 GIODSET4        :1;
  __REG32 GIODSET5        :1;
  __REG32 GIODSET6        :1;
  __REG32 GIODSET7        :1;
  __REG32                 :24;
} __giodset_bits;

/* GIODCLRx GIO Data Clear */
typedef struct {
  __REG32 GIODCLR0        :1;
  __REG32 GIODCLR1        :1;
  __REG32 GIODCLR2        :1;
  __REG32 GIODCLR3        :1;
  __REG32 GIODCLR4        :1;
  __REG32 GIODCLR5        :1;
  __REG32 GIODCLR6        :1;
  __REG32 GIODCLR7        :1;
  __REG32                 :24;
} __giodclr_bits;

/* CANGAM Global acceptance mask */
typedef struct {
  __REG32 GAM             :29;
  __REG32                 :2;
  __REG32 AMI             :1;
} __cangam_bits;

/* CANMC Master control */
typedef struct {
  __REG32 MBNR            :5;
  __REG32 SRES            :1;
  __REG32 STM             :1;
  __REG32 ABO             :1;
  __REG32 CDR             :1;
  __REG32 WUBA            :1;
  __REG32 DBO             :1;
  __REG32 PDR             :1;
  __REG32 CCR             :1;
  __REG32 SCM             :1;
  __REG32 LNTM            :1;
  __REG32 LNTC            :1;
  __REG32                 :16;
} __canmc_bits;

/* CANBTC Bit-timing configuration */
typedef struct {
  __REG32 TSEG2           :3;
  __REG32 TSEG1           :4;
  __REG32 SAM             :1;
  __REG32 SJW             :2;
  __REG32 ERM             :1;
  __REG32                 :5;
  __REG32 BRP             :8;
  __REG32                 :8;
} __canbtc_bits;

/* CANES Error and status */
typedef struct {
  __REG32 TM              :1;
  __REG32 RM              :1;
  __REG32                 :1;
  __REG32 PDA             :1;
  __REG32 CCE             :1;
  __REG32 SMA             :1;
  __REG32                 :10;
  __REG32 EW              :1;
  __REG32 EP              :1;
  __REG32 BO              :1;
  __REG32 ACKE            :1;
  __REG32 SE              :1;
  __REG32 CRCE            :1;
  __REG32 SA1             :1;
  __REG32 BE              :1;
  __REG32 FE              :1;
  __REG32                 :7;
} __canes_bits;

/* CANTEC Transmit error counter */
typedef struct {
  __REG32 TEC             :8;
  __REG32                 :24;
} __cantec_bits;

/* CANREC Receive error counter */
typedef struct {
  __REG32 REC             :8;
  __REG32                 :24;
} __canrec_bits;

/* CANGIFx Global interrupt flag */
typedef struct {
  __REG32 MIV_3_0         :4;
  __REG32 MIV_4           :1;
  __REG32                 :3;
  __REG32 WLIF            :1;
  __REG32 EPIF            :1;
  __REG32 BOIF            :1;
  __REG32 RMLIF           :1;
  __REG32 WUIF            :1;
  __REG32 WDIF            :1;
  __REG32 AAIF            :1;
  __REG32 GMIF            :1;
  __REG32 TCOIF           :1;
  __REG32 MAIF            :1;
  __REG32                 :14;
} __cangif_bits;

/* CANGIM Global interrupt mask */
typedef struct {
  __REG32 I0EN            :1;
  __REG32 I1EN            :1;
  __REG32 SIL             :1;
  __REG32                 :5;
  __REG32 WLIM            :1;
  __REG32 EPIM            :1;
  __REG32 BOIM            :1;
  __REG32 RMLIM           :1;
  __REG32 WUIM            :1;
  __REG32 WDIM            :1;
  __REG32 AAIM            :1;
  __REG32                 :1;
  __REG32 TCOIM           :1;
  __REG32 MAIM            :1;
  __REG32                 :14;
} __cangim_bits;

/* CANTIOC TX I/O control */
typedef struct {
  __REG32 TXIN            :1;
  __REG32 TXOUT           :1;
  __REG32 TXDIR           :1;
  __REG32 TXFUNC          :1;
  __REG32                 :28;
} __cantioc_bits;

/* CANRIOC RX I/O control */
typedef struct {
  __REG32 RXIN            :1;
  __REG32 RXOUT           :1;
  __REG32 RXDIR           :1;
  __REG32 RXFUNC          :1;
  __REG32                 :28;
} __canrioc_bits;

/* C2SIAISR C2SIa Interrupt Status Register */
typedef struct {
  __REG8 RBFIF           :1;
  __REG8 BRKIF           :1;
  __REG8 RCCIF           :1;
  __REG8 RXOIF           :1;
  __REG8 TXUOIF          :1;
  __REG8 TBEIF           :1;
  __REG8 TIDLIF          :1;
  __REG8 ARBIF           :1;
} __c2siaisr_bits;

/* C2SIAICR C2SIa Interrupt Control Register */
typedef struct {
  __REG8 RBFIE           :1;
  __REG8 BRKIE           :1;
  __REG8 RCCIE           :1;
  __REG8 RXOIE           :1;
  __REG8 TXUOIE          :1;
  __REG8 TBEIE           :1;
  __REG8 TIDLIE          :1;
  __REG8 ARBIE           :1;
} __c2siaicr_bits;

/* C2SIAGSR C2SIa Global Status Register */
typedef struct {
  __REG8 WAKE            :1;
  __REG8 NOISE           :1;
  __REG8 SHORTGND        :1;
  __REG8 IDLE            :1;
  __REG8 RIFR            :1;
  __REG8 TXERROR         :1;
  __REG8 RXACTIVE        :1;
  __REG8 TXACTIVE        :1;
} __c2siagsr_bits;

/* C2SIAGCR C2SIa Global Control Register */
typedef struct {
  __REG8 ENWAKE          :1;
  __REG8 TIFR            :1;
  __REG8 TBRK            :1;
  __REG8 TXRESET         :1;
  __REG8 NBPOL           :1;
  __REG8 T2IFR           :1;
  __REG8 X4MODE          :1;
  __REG8 CRCDIS          :1;
} __c2siagcr_bits;

/* C2SIACCSR C2SIa Completion Code Status Register */
typedef struct {
  __REG8 IFRCRC          :1;
  __REG8 IFR             :1;
  __REG8 BREAK           :1;
  __REG8 XMITOK          :1;
  __REG8 CRCERR          :1;
  __REG8 BYTERR          :1;
  __REG8 BITERR          :1;
  __REG8 ROVR            :1;
} __c2siaccsr_bits;

/* C2SIACTR C2SIa Control Register */
typedef struct {
  __REG8 LPM             :1;
  __REG8 ESPEN           :1;
  __REG8 RXDMAEN         :1;
  __REG8 TXDMAEN         :1;
  __REG8 IGNORERX        :1;
  __REG8 LPEN            :1;
  __REG8 CALEN           :1;
  __REG8 LONGBRK         :1;
} __c2siactr_bits;

/* C2SIACLK C2SIa Interface Clock Register */
typedef struct {
  __REG8 ICLKFR          :6;
  __REG8                 :2;
} __c2siaclk_bits;

/* C2SIAPC1 C2SIa Pin Control Register 1 */
typedef struct {
  __REG8 LPDIR           :1;
  __REG8 RXDIR           :1;
  __REG8 TXDIR           :1;
  __REG8 LPFUN           :1;
  __REG8 RXFUN           :1;
  __REG8 TXFUN           :1;
  __REG8 RXPOL           :1;
  __REG8 TXPOL           :1;
} __c2siapc1_bits;

/* C2SIAPC2 C2SIa Pin Control Register 2 */
typedef struct {
  __REG8 LPDOUT          :1;
  __REG8 RXDOUT          :1;
  __REG8 TXDOUT          :1;
  __REG8                 :5;
} __c2siapc2_bits;

/* C2SIAPC3 C2SIa Pin Control Register 3 */
typedef struct {
  __REG8 LPDIN           :1;
  __REG8 RXDIN           :1;
  __REG8 TXDIN           :1;
  __REG8                 :5;
} __c2siapc3_bits;

/* C2SIACAL C2SIa Calibration Register */
typedef struct {
  __REG8 CAL             :6;
  __REG8 SOFX            :1;
  __REG8 ARBTYPE         :1;
} __c2siacal_bits;

/* C2SIABRK C2SIa Break status Register */
typedef struct {
  __REG8 INBREAK         :1;
  __REG8 BREAKEND        :1;
  __REG8                 :6;
} __c2siabrk_bits;

/* FMREGOPT Option Control Register */
typedef struct {
  __REG32 ENPIPE         :1;
  __REG32 READOTP        :1;
  __REG32 RDMRGN0        :1;
  __REG32 RDMRGN1        :1;
  __REG32                :28;
} __fmregopt_bits;

/* FMBBUSY Bank Busy Register */
typedef struct {
  __REG32 BUSY           :8;
  __REG32                :7;
  __REG32 PROTL2DIS      :1;
  __REG32                :16;
} __fmbbusy_bits;

/* FMBAC1 Bank Access Control Register 1 */
typedef struct {
  __REG16 BNKPWR         :2;
  __REG16 BSTDBY         :6;
  __REG16 BAGP           :8;
} __fmbac1_bits;

/* FMBAC2 Bank Access Control Register 2 */
typedef struct {
  __REG16 WAIT_3_0       :4;
  __REG16 WAIT_7_4       :4;
  __REG16 BSLEEP         :7;
  __REG16 OTPPROTDIS     :1;
} __fmbac2_bits;

/* FMBRDY Bank Ready Register */
typedef struct {
  __REG16                :5;
  __REG16 BANKRDY        :1;
  __REG16                :10;
} __fmbrdy_bits;

/* FMPRDY Pump Ready Register */
typedef struct {
  __REG16                :9;
  __REG16 PUMPRDY        :1;
  __REG16                :6;
} __fmprdy_bits;

/* FMMAC1 Module Access Control Register 1 */
typedef struct {
  __REG16 PSLEEP         :15;
  __REG16 PROTL1DIS      :1;
} __fmmac1_bits;

/* FMMAC2 Module Access Control Register 2 */
typedef struct {
  __REG16 BANK           :3;
  __REG16 PMPPWR         :2;
  __REG16 PSTDBY         :11;
} __fmmac2_bits;

/* FMMSTAT Module Status Register */
typedef struct {
  __REG16 SLOCK          :1;
  __REG16 PSUSP          :1;
  __REG16 ESUSP          :1;
  __REG16 VSTAT          :1;  /* 3VSTAT (symbols cannot start with a digit) */
  __REG16 CSTAT          :1;
  __REG16 INVDAT         :1;
  __REG16 PGM            :1;
  __REG16 ERS            :1;
  __REG16 BUSY           :1;
  __REG16                :7;
} __fmmstat_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Common declarations  ****************************************************/

/***************************************************************************
 **
 ** System module
 **
 ***************************************************************************/

__IO_REG32_BIT(SMCR0,    0xfffffd00,__READ_WRITE,__smcr0_bits);
__IO_REG32_BIT(SMCR1,    0xfffffd04,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR2,    0xfffffd08,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR3,    0xfffffd0c,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR4,    0xfffffd10,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR5,    0xfffffd14,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR6,    0xfffffd18,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR7,    0xfffffd1c,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR8,    0xfffffd20,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(SMCR9,    0xfffffd24,__READ_WRITE,__smcrx_bits);
__IO_REG32_BIT(WCR0,     0xfffffd2c,__READ_WRITE,__wcr_bits);

__IO_REG32_BIT(PLR,      0xfffffd34,__READ_WRITE,__plr_bits);
__IO_REG32_BIT(PPROT,    0xfffffd38,__READ_WRITE,__pprot_bits);

__IO_REG32_BIT(MFBAHR0,  0xfffffe00,__READ_WRITE,__mfbahr_bits);
__IO_REG32_BIT(MFBALR0,  0xfffffe04,__READ_WRITE,__mfbalr0_bits);
__IO_REG32_BIT(MFBAHR1,  0xfffffe08,__READ_WRITE,__mfbahr_bits);
__IO_REG32_BIT(MFBALR1,  0xfffffe0c,__READ_WRITE,__mfbalrx_bits);
__IO_REG32_BIT(MFBAHR2,  0xfffffe10,__READ_WRITE,__mfbahr_bits);
__IO_REG32_BIT(MFBALR2,  0xfffffe14,__READ_WRITE,__mfbalrx_bits);
__IO_REG32_BIT(MFBAHR3,  0xfffffe18,__READ_WRITE,__mfbahr_bits);
__IO_REG32_BIT(MFBALR3,  0xfffffe1c,__READ_WRITE,__mfbalrx_bits);
__IO_REG32_BIT(MFBAHR4,  0xfffffe20,__READ_WRITE,__mfbahr_bits);
__IO_REG32_BIT(MFBALR4,  0xfffffe24,__READ_WRITE,__mfbalrx_bits);
__IO_REG32_BIT(MFBAHR5,  0xfffffe28,__READ_WRITE,__mfbahr_bits);
__IO_REG32_BIT(MFBALR5,  0xfffffe2c,__READ_WRITE,__mfbalrx_bits);
__IO_REG32_BIT(MCBAHR0,  0xfffffe30,__READ_WRITE,__mcbahr_bits);
__IO_REG32_BIT(MCBALR0,  0xfffffe34,__READ_WRITE,__mcbalr_bits);
__IO_REG32_BIT(MCBAHR1,  0xfffffe38,__READ_WRITE,__mcbahr_bits);
__IO_REG32_BIT(MCBALR1,  0xfffffe3c,__READ_WRITE,__mcbalr_bits);
__IO_REG32_BIT(MCBAHR2,  0xfffffe40,__READ_WRITE,__mcbahr_bits);
__IO_REG32_BIT(MCBALR2,  0xfffffe44,__READ_WRITE,__mcbalr_bits);
__IO_REG32_BIT(MCBAHR3,  0xfffffe48,__READ_WRITE,__mcbahr_bits);
__IO_REG32_BIT(MCBALR3,  0xfffffe4c,__READ_WRITE,__mcbalr_bits);
__IO_REG32_BIT(MCBAHR4,  0xfffffe50,__READ_WRITE,__mcbahr_bits);
__IO_REG32_BIT(MCBALR4,  0xfffffe54,__READ_WRITE,__mcbalr_bits);
__IO_REG32_BIT(MCBAHR5,  0xfffffe58,__READ_WRITE,__mcbahr_bits);
__IO_REG32_BIT(MCBALR5,  0xfffffe5c,__READ_WRITE,__mcbalr_bits);

__IO_REG32_BIT(RTICNTR,  0xffffff00,__READ_WRITE,__rticntr_bits);
__IO_REG32_BIT(RTIPCTL,  0xffffff04,__READ_WRITE,__rtipctl_bits);
__IO_REG32_BIT(RTICNTL,  0xffffff08,__READ_WRITE,__rticntl_bits);
__IO_REG32(    WKEY,     0xffffff0c,__READ_WRITE);
__IO_REG32_BIT(RTICMP1,  0xffffff10,__READ_WRITE,__rticmp1_bits);
__IO_REG32_BIT(RTICMP2,  0xffffff14,__READ_WRITE,__rticmp2_bits);
__IO_REG32_BIT(RTICINT,  0xffffff18,__READ_WRITE,__rticint_bits);
__IO_REG32_BIT(RTICNTEN, 0xffffff1c,__READ_WRITE,__rticnten_bits);

__IO_REG32_BIT(IRQIVEC,  0xffffff20,__READ_WRITE,__irqivec_bits);
__IO_REG32_BIT(FIQIVEC,  0xffffff24,__READ_WRITE,__fiqivec_bits);
__IO_REG32_BIT(CIMIVEC,  0xffffff28,__READ_WRITE,__cimivec_bits);
__IO_REG32(    FIRQPR,   0xffffff2c,__READ_WRITE);
__IO_REG32(    INTREQ,   0xffffff30,__READ_WRITE);
__IO_REG32(    REQMASK,  0xffffff34,__READ_WRITE);
__IO_REG32_BIT(SSIF,     0xfffffff8,__READ_WRITE,__ssif_bits);
__IO_REG32_BIT(SSIR,     0xfffffffc,__READ_WRITE,__ssir_bits);

__IO_REG32(    CPUPSA,   0xffffff40,__READ_WRITE);
__IO_REG32_BIT(PSAENABLE,0xffffff50,__READ_WRITE,__psaenable_bits);

__IO_REG32_BIT(PCR,      0xfffffd30,__READ_WRITE,__pcr_bits);
__IO_REG32_BIT(CLKCNTL,  0xffffffd0,__READ_WRITE,__clkcntl_bits);
__IO_REG32_BIT(GCR,      0xffffffdc,__READ_WRITE,__gcr_bits);

__IO_REG32_BIT(SYSECR,   0xffffffe0,__READ_WRITE,__sysecr_bits);
__IO_REG32_BIT(SYSESR,   0xffffffe4,__READ_WRITE,__sysesr_bits);
__IO_REG32_BIT(ABRTESR,  0xffffffe8,__READ_WRITE,__abrtesr_bits);
__IO_REG32_BIT(GLBSTAT,  0xffffffec,__READ_WRITE,__glbstat_bits);

__IO_REG32_BIT(DEV,      0xfffffff0,__READ_WRITE,__dev_bits);

/***************************************************************************
 **
 ** MPU
 **
 ***************************************************************************/

__IO_REG32_BIT(MPUAHR0,  0xffe84000,__READ_WRITE,__mpuahr_bits);
__IO_REG32_BIT(MPUALR0,  0xffe84004,__READ_WRITE,__mpualr_bits);
__IO_REG32_BIT(MPUAHR1,  0xffe84008,__READ_WRITE,__mpuahr_bits);
__IO_REG32_BIT(MPUALR1,  0xffe8400c,__READ_WRITE,__mpualr_bits);
__IO_REG32_BIT(MPUAHR2,  0xffe84010,__READ_WRITE,__mpuahr_bits);
__IO_REG32_BIT(MPUALR2,  0xffe84014,__READ_WRITE,__mpualr_bits);
__IO_REG32_BIT(MPUAHR3,  0xffe84018,__READ_WRITE,__mpuahr_bits);
__IO_REG32_BIT(MPUALR3,  0xffe8401c,__READ_WRITE,__mpualr_bits);
__IO_REG32_BIT(MPUCTRL,  0xffe84020,__READ_WRITE,__mpuctrl_bits);

/***************************************************************************
 **
 ** HET
 **
 ***************************************************************************/

__IO_REG32_BIT(HETGCR,   0xfff7fc00,__READ_WRITE,__hetgcr_bits);
__IO_REG32_BIT(HETPFR,   0xfff7fc04,__READ_WRITE,__hetpfr_bits);
__IO_REG32_BIT(HETADDR,  0xfff7fc08,__READ_WRITE,__hetaddr_bits);
__IO_REG32_BIT(HETOFF1,  0xfff7fc0c,__READ_WRITE,__hetoff_bits);
__IO_REG32_BIT(HETOFF2,  0xfff7fc10,__READ_WRITE,__hetoff_bits);
__IO_REG32_BIT(HETEXC1,  0xfff7fc14,__READ_WRITE,__hetexc1_bits);
__IO_REG32_BIT(HETEXC2,  0xfff7fc18,__READ_WRITE,__hetexc2_bits);
__IO_REG32(    HETPRY,   0xfff7fc1c,__READ_WRITE);
__IO_REG32(    HETFLG,   0xfff7fc20,__READ_WRITE);
__IO_REG32_BIT(HETHRSH,  0xfff7fc2c,__READ_WRITE,__hethrsh_bits);
__IO_REG32_BIT(HETXOR,   0xfff7fc30,__READ_WRITE,__hetxor_bits);
__IO_REG32(    HETDIR,   0xfff7fc34,__READ_WRITE);
__IO_REG32(    HETDIN,   0xfff7fc38,__READ_WRITE);
__IO_REG32(    HETDOUT,  0xfff7fc3c,__READ_WRITE);
__IO_REG32(    HETDSET,  0xfff7fc40,__READ_WRITE);
__IO_REG32(    HETDCLR,  0xfff7fc44,__READ_WRITE);

/***************************************************************************
 **
 ** SPI1
 **
 ***************************************************************************/

__IO_REG32_BIT(SPI1CTRL1,0xfff7f800,__READ_WRITE,__spictrl1_bits);
__IO_REG32_BIT(SPI1CTRL2,0xfff7f804,__READ_WRITE,__spictrl2_bits);
__IO_REG32_BIT(SPI1CTRL3,0xfff7f808,__READ_WRITE,__spictrl3_bits);
__IO_REG32_BIT(SPI1DAT0, 0xfff7f80C,__READ_WRITE,__spidat0_bits);
__IO_REG32_BIT(SPI1DAT1, 0xfff7f810,__READ_WRITE,__spidat1_bits);
__IO_REG32_BIT(SPI1BUF,  0xfff7f814,__READ_WRITE,__spibuf_bits);
__IO_REG32_BIT(SPI1EMU,  0xfff7f818,__READ_WRITE,__spiemu_bits);
__IO_REG32_BIT(SPI1PC1,  0xfff7f81c,__READ_WRITE,__spipc1_bits);
__IO_REG32_BIT(SPI1PC2,  0xfff7f820,__READ_WRITE,__spipc2_bits);
__IO_REG32_BIT(SPI1PC3,  0xfff7f824,__READ_WRITE,__spipc3_bits);
__IO_REG32_BIT(SPI1PC4,  0xfff7f828,__READ_WRITE,__spipc4_bits);
__IO_REG32_BIT(SPI1PC5,  0xfff7f82c,__READ_WRITE,__spipc5_bits);
__IO_REG32_BIT(SPI1PC6,  0xfff7f830,__READ_WRITE,__spipc6_bits);

/***************************************************************************
 **
 ** SPI2
 **
 ***************************************************************************/

__IO_REG32_BIT(SPI2CTRL1,0xfff7d400,__READ_WRITE,__spictrl1_bits);
__IO_REG32_BIT(SPI2CTRL2,0xfff7d404,__READ_WRITE,__spictrl2_bits);
__IO_REG32_BIT(SPI2CTRL3,0xfff7d408,__READ_WRITE,__spictrl3_bits);
__IO_REG32_BIT(SPI2DAT0, 0xfff7d40c,__READ_WRITE,__spidat0_bits);
__IO_REG32_BIT(SPI2DAT1, 0xfff7d410,__READ_WRITE,__spidat1_bits);
__IO_REG32_BIT(SPI2BUF,  0xfff7d414,__READ_WRITE,__spibuf_bits);
__IO_REG32_BIT(SPI2EMU,  0xfff7d418,__READ_WRITE,__spiemu_bits);
__IO_REG32_BIT(SPI2PC1,  0xfff7d41c,__READ_WRITE,__spipc1_bits);
__IO_REG32_BIT(SPI2PC2,  0xfff7d420,__READ_WRITE,__spipc2_bits);
__IO_REG32_BIT(SPI2PC3,  0xfff7d424,__READ_WRITE,__spipc3_bits);
__IO_REG32_BIT(SPI2PC4,  0xfff7d428,__READ_WRITE,__spipc4_bits);
__IO_REG32_BIT(SPI2PC5,  0xfff7d42c,__READ_WRITE,__spipc5_bits);
__IO_REG32_BIT(SPI2PC6,  0xfff7d430,__READ_WRITE,__spipc6_bits);

/***************************************************************************
 **
 ** SCI1
 **
 ***************************************************************************/

__IO_REG8_BIT(SCI1CCR,   0xfff7f403,__READ_WRITE,__sciccr_bits);
__IO_REG8_BIT(SCI1CTL1,  0xfff7f407,__READ_WRITE,__scictl1_bits);
__IO_REG8_BIT(SCI1CTL2,  0xfff7f40b,__READ_WRITE,__scictl2_bits);
__IO_REG8_BIT(SCI1CTL3,  0xfff7f40f,__READ_WRITE,__scictl3_bits);
__IO_REG8_BIT(SCI1RXST,  0xfff7f413,__READ_WRITE,__scirxst_bits);
__IO_REG8(    SCI1HBAUD, 0xfff7f417,__READ_WRITE);
__IO_REG8(    SCI1MBAUD, 0xfff7f41b,__READ_WRITE);
__IO_REG8(    SCI1LBAUD, 0xfff7f41f,__READ_WRITE);
__IO_REG8(    SCI1RXEMU, 0xfff7f423,__READ_WRITE);
__IO_REG8(    SCI1RXBUF, 0xfff7f427,__READ_WRITE);
__IO_REG8(    SCI1TXBUF, 0xfff7f42b,__READ_WRITE);
__IO_REG8_BIT(SCI1PC1,   0xfff7f42f,__READ_WRITE,__scipc1_bits);
__IO_REG8_BIT(SCI1PC2,   0xfff7f433,__READ_WRITE,__scipc2_bits);
__IO_REG8_BIT(SCI1PC3,   0xfff7f437,__READ_WRITE,__scipc3_bits);

/***************************************************************************
 **
 ** SCI2
 **
 ***************************************************************************/

__IO_REG8_BIT(SCI2CCR,   0xfff7f503,__READ_WRITE,__sciccr_bits);
__IO_REG8_BIT(SCI2CTL1,  0xfff7f507,__READ_WRITE,__scictl1_bits);
__IO_REG8_BIT(SCI2CTL2,  0xfff7f50b,__READ_WRITE,__scictl2_bits);
__IO_REG8_BIT(SCI2CTL3,  0xfff7f50f,__READ_WRITE,__scictl3_bits);
__IO_REG8_BIT(SCI2RXST,  0xfff7f513,__READ_WRITE,__scirxst_bits);
__IO_REG8(    SCI2HBAUD, 0xfff7f517,__READ_WRITE);
__IO_REG8(    SCI2MBAUD, 0xfff7f51b,__READ_WRITE);
__IO_REG8(    SCI2LBAUD, 0xfff7f51f,__READ_WRITE);
__IO_REG8(    SCI2RXEMU, 0xfff7f523,__READ_WRITE);
__IO_REG8(    SCI2RXBUF, 0xfff7f527,__READ_WRITE);
__IO_REG8(    SCI2TXBUF, 0xfff7f52b,__READ_WRITE);
__IO_REG8_BIT(SCI2PC1,   0xfff7f52f,__READ_WRITE,__scipc1_bits);
__IO_REG8_BIT(SCI2PC2,   0xfff7f533,__READ_WRITE,__scipc2_bits);
__IO_REG8_BIT(SCI2PC3,   0xfff7f537,__READ_WRITE,__scipc3_bits);

/***************************************************************************
 **
 ** MibADC
 **
 ***************************************************************************/

__IO_REG16_BIT(ADCR1,    0xfff7f002,__READ_WRITE,__adccr1_bits);
__IO_REG16_BIT(ADCR2,    0xfff7f006,__READ_WRITE,__adccr2_bits);
__IO_REG16_BIT(ADSR,     0xfff7f00a,__READ_WRITE,__adsr_bits);
__IO_REG16(    ADEISR,   0xfff7f00e,__READ_WRITE);
__IO_REG16(    ADISR1,   0xfff7f012,__READ_WRITE);
__IO_REG16(    ADISR2,   0xfff7f016,__READ_WRITE);
__IO_REG16_BIT(ADCALR,   0xfff7f01a,__READ_WRITE,__adcalr_bits);
__IO_REG16_BIT(ADDR0,    0xfff7f01e,__READ_WRITE,__addr_bits);

__IO_REG16_BIT(ADEMDR0,  0xfff7f022,__READ_WRITE,__ademdr014adbufe_bits);
__IO_REG16_BIT(ADDR1,    0xfff7f026,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR1,  0xfff7f02a,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR2,    0xfff7f02e,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR2,  0xfff7f032,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR3,    0xfff7f036,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR3,  0xfff7f03a,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR4,    0xfff7f03e,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR4,  0xfff7f042,__READ_WRITE,__ademdr4adbuf1_bits);
__IO_REG16_BIT(ADDR5,    0xfff7f046,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR5,  0xfff7f04a,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR6,    0xfff7f04e,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR6,  0xfff7f052,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR7,    0xfff7f056,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR7,  0xfff7f05a,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR8,    0xfff7f05e,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR8,  0xfff7f062,__READ_WRITE,__ademdr815adbuf2_bits);
__IO_REG16_BIT(ADDR9,    0xfff7f066,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR9,  0xfff7f06a,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR10,   0xfff7f06e,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR10, 0xfff7f072,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR11,   0xfff7f076,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR11, 0xfff7f07a,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR12,   0xfff7f07e,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR12, 0xfff7f082,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR13,   0xfff7f086,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR13, 0xfff7f08a,__READ_WRITE,__ademdr_bits);
__IO_REG16_BIT(ADDR14,   0xfff7f08e,__READ_WRITE,__addr_bits);
__IO_REG16_BIT(ADEMDR14, 0xfff7f092,__READ_WRITE,__ademdr014adbufe_bits);
__IO_REG16_BIT(ADDR15,   0xfff7f096,__READ_WRITE,__addr15ademubuf1_bits);
__IO_REG16_BIT(ADEMDR15, 0xfff7f09a,__READ_WRITE,__ademdr815adbuf2_bits);

/*
 * These registers are used in buffered mode only. They have the same
 * addresses as some of the registers in compatibility mode.
 */
#define ADBUFE    ADEMDR0
#define ADBUF1    ADEMDR4
#define ADBUF2    ADEMDR8
#define ADEMUBUFE ADEMDR14
#define ADEMUBUF1 ADDR15
#define ADEMUBUF2 ADEMDR15

__IO_REG16(    ADINR,    0xfff7f09e,__READ_WRITE);
__IO_REG16_BIT(ADCPCR,   0xfff7f0a2,__READ_WRITE,__adcpcr_bits);

__IO_REG16_BIT(ADSAMPEV, 0xfff7f0b2,__READ_WRITE,__adsampev_bits);
__IO_REG16_BIT(ADSAMP1,  0xfff7f0b6,__READ_WRITE,__adsamp1_bits);
__IO_REG16_BIT(ADSAMP2,  0xfff7f0ba,__READ_WRITE,__adsamp2_bits);
__IO_REG16_BIT(ADBCR1,   0xfff7f0be,__READ_WRITE,__adbcr1_bits);
__IO_REG16_BIT(ADBCR2,   0xfff7f0c2,__READ_WRITE,__adbcr2_bits);
__IO_REG16_BIT(ADBCR3,   0xfff7f0c6,__READ_WRITE,__adbcr3_bits);
__IO_REG16_BIT(ADBUFST,  0xfff7f0ca,__READ_WRITE,__adbufst_bits);
__IO_REG16_BIT(ADTHREV,  0xfff7f0ce,__READ_WRITE,__adthrev_bits);
__IO_REG16_BIT(ADTHRG1,  0xfff7f0d2,__READ_WRITE,__adthrg1_bits);
__IO_REG16_BIT(ADTHRG2,  0xfff7f0d6,__READ_WRITE,__adthrg2_bits);
__IO_REG16_BIT(ADEVTSRC, 0xfff7f0da,__READ_WRITE,__adevtsrc_bits);

/***************************************************************************
 **
 ** ECP
 **
 ***************************************************************************/

__IO_REG16_BIT(ECPCTRL,  0xfff7ef02,__READ_WRITE,__ecpctrl_bits);

/***************************************************************************
 **
 ** GIO
 **
 ***************************************************************************/

__IO_REG32_BIT(GIOPWDN,  0xfff7ec00,__READ_WRITE,__giopwdn_bits);
__IO_REG32_BIT(GIOENA1,  0xfff7ec04,__READ_WRITE,__gioena1_bits);
__IO_REG32_BIT(GIOPOL1,  0xfff7ec08,__READ_WRITE,__giopol1_bits);
__IO_REG32_BIT(GIOFLG1,  0xfff7ec0c,__READ_WRITE,__gioflg1_bits);
__IO_REG32_BIT(GIOPRY1,  0xfff7ec10,__READ_WRITE,__giopry1_bits);
__IO_REG32_BIT(GIOOFFA,  0xfff7ec14,__READ_WRITE,__giooffa_bits);
__IO_REG32_BIT(GIOEMUA,  0xfff7ec18,__READ_WRITE,__gioemua_bits);
__IO_REG32_BIT(GIOOFFB,  0xfff7ec1c,__READ_WRITE,__giooffb_bits);
__IO_REG32_BIT(GIOEMUB,  0xfff7ec20,__READ_WRITE,__gioemub_bits);
__IO_REG32_BIT(GIODIRA,  0xfff7ec24,__READ_WRITE,__giodir_bits);
__IO_REG32_BIT(GIODINA,  0xfff7ec28,__READ_WRITE,__giodin_bits);
__IO_REG32_BIT(GIODOUTA, 0xfff7ec2c,__READ_WRITE,__giodout_bits);
__IO_REG32_BIT(GIODSETA, 0xfff7ec30,__READ_WRITE,__giodset_bits);
__IO_REG32_BIT(GIODCLRA, 0xfff7ec34,__READ_WRITE,__giodclr_bits);
__IO_REG32_BIT(GIODIRB,  0xfff7ec38,__READ_WRITE,__giodir_bits);
__IO_REG32_BIT(GIODINB,  0xfff7ec3c,__READ_WRITE,__giodin_bits);
__IO_REG32_BIT(GIODOUTB, 0xfff7ec40,__READ_WRITE,__giodout_bits);
__IO_REG32_BIT(GIODSETB, 0xfff7ec44,__READ_WRITE,__giodset_bits);
__IO_REG32_BIT(GIODCLRB, 0xfff7ec48,__READ_WRITE,__giodclr_bits);

/***************************************************************************
 **
 ** SCC1
 **
 ***************************************************************************/

__IO_REG32(    SCC1CANME,   0xfff7e000,__READ_WRITE);
__IO_REG32(    SCC1CANMD,   0xfff7e004,__READ_WRITE);
__IO_REG32(    SCC1CANTRS,  0xfff7e008,__READ_WRITE);
__IO_REG32(    SCC1CANTRR,  0xfff7e00c,__READ_WRITE);
__IO_REG32(    SCC1CANTA,   0xfff7e010,__READ_WRITE);
__IO_REG32(    SCC1CANAA,   0xfff7e014,__READ_WRITE);
__IO_REG32(    SCC1CANRMP,  0xfff7e018,__READ_WRITE);
__IO_REG32(    SCC1CANRML,  0xfff7e01c,__READ_WRITE);
__IO_REG32(    SCC1CANRFP,  0xfff7e020,__READ_WRITE);
__IO_REG32_BIT(SCC1CANGAM,  0xfff7e024,__READ_WRITE,__cangam_bits);
__IO_REG32_BIT(SCC1CANMC,   0xfff7e028,__READ_WRITE,__canmc_bits);
__IO_REG32_BIT(SCC1CANBTC,  0xfff7e02c,__READ_WRITE,__canbtc_bits);
__IO_REG32_BIT(SCC1CANES,   0xfff7e030,__READ_WRITE,__canes_bits);
__IO_REG32_BIT(SCC1CANTEC,  0xfff7e034,__READ_WRITE,__cantec_bits);
__IO_REG32_BIT(SCC1CANREC,  0xfff7e038,__READ_WRITE,__canrec_bits);
__IO_REG32_BIT(SCC1CANGIF0, 0xfff7e03c,__READ_WRITE,__cangif_bits);
__IO_REG32_BIT(SCC1CANGIM,  0xfff7e040,__READ_WRITE,__cangim_bits);
__IO_REG32_BIT(SCC1CANGIF1, 0xfff7e044,__READ_WRITE,__cangif_bits);
__IO_REG32(    SCC1CANMIM,  0xfff7e048,__READ_WRITE);
__IO_REG32(    SCC1CANMIL,  0xfff7e04c,__READ_WRITE);
__IO_REG32(    SCC1CANOPC,  0xfff7e050,__READ_WRITE);
__IO_REG32_BIT(SCC1CANTIOC, 0xfff7e054,__READ_WRITE,__cantioc_bits);
__IO_REG32_BIT(SCC1CANRIOC, 0xfff7e058,__READ_WRITE,__canrioc_bits);
__IO_REG32(    SCC1CANLAM0 ,  0xfff7e080,__READ_WRITE);  /* Local acceptance mask */
__IO_REG32(    SCC1CANLAM3 ,  0xfff7e08c,__READ_WRITE);
__IO_REG32(    SCC1CANMID0 ,  0xfff7dc00,__READ_WRITE);  /* Message identifier */
__IO_REG32(    SCC1CANMID1 ,  0xfff7dc10,__READ_WRITE);
__IO_REG32(    SCC1CANMID2 ,  0xfff7dc20,__READ_WRITE);
__IO_REG32(    SCC1CANMID3 ,  0xfff7dc30,__READ_WRITE);
__IO_REG32(    SCC1CANMID4 ,  0xfff7dc40,__READ_WRITE);
__IO_REG32(    SCC1CANMID5 ,  0xfff7dc50,__READ_WRITE);
__IO_REG32(    SCC1CANMID6 ,  0xfff7dc60,__READ_WRITE);
__IO_REG32(    SCC1CANMID7 ,  0xfff7dc70,__READ_WRITE);
__IO_REG32(    SCC1CANMID8 ,  0xfff7dc80,__READ_WRITE);
__IO_REG32(    SCC1CANMID9 ,  0xfff7dc90,__READ_WRITE);
__IO_REG32(    SCC1CANMID10,  0xfff7dca0,__READ_WRITE);
__IO_REG32(    SCC1CANMID11,  0xfff7dcb0,__READ_WRITE);
__IO_REG32(    SCC1CANMID12,  0xfff7dcc0,__READ_WRITE);
__IO_REG32(    SCC1CANMID13,  0xfff7dcd0,__READ_WRITE);
__IO_REG32(    SCC1CANMID14,  0xfff7dce0,__READ_WRITE);
__IO_REG32(    SCC1CANMID15,  0xfff7dcf0,__READ_WRITE);
__IO_REG32(    SCC1CANMCF0 ,  0xfff7dc04,__READ_WRITE);  /* Message control field */
__IO_REG32(    SCC1CANMCF1 ,  0xfff7dc14,__READ_WRITE);
__IO_REG32(    SCC1CANMCF2 ,  0xfff7dc24,__READ_WRITE);
__IO_REG32(    SCC1CANMCF3 ,  0xfff7dc34,__READ_WRITE);
__IO_REG32(    SCC1CANMCF4 ,  0xfff7dc44,__READ_WRITE);
__IO_REG32(    SCC1CANMCF5 ,  0xfff7dc54,__READ_WRITE);
__IO_REG32(    SCC1CANMCF6 ,  0xfff7dc64,__READ_WRITE);
__IO_REG32(    SCC1CANMCF7 ,  0xfff7dc74,__READ_WRITE);
__IO_REG32(    SCC1CANMCF8 ,  0xfff7dc84,__READ_WRITE);
__IO_REG32(    SCC1CANMCF9 ,  0xfff7dc94,__READ_WRITE);
__IO_REG32(    SCC1CANMCF10,  0xfff7dca4,__READ_WRITE);
__IO_REG32(    SCC1CANMCF11,  0xfff7dcb4,__READ_WRITE);
__IO_REG32(    SCC1CANMCF12,  0xfff7dcc4,__READ_WRITE);
__IO_REG32(    SCC1CANMCF13,  0xfff7dcd4,__READ_WRITE);
__IO_REG32(    SCC1CANMCF14,  0xfff7dce4,__READ_WRITE);
__IO_REG32(    SCC1CANMCF15,  0xfff7dcf4,__READ_WRITE);
__IO_REG32(    SCC1CANMDL0 ,  0xfff7dc08,__READ_WRITE);  /* Message data low word */
__IO_REG32(    SCC1CANMDL1 ,  0xfff7dc18,__READ_WRITE);
__IO_REG32(    SCC1CANMDL2 ,  0xfff7dc28,__READ_WRITE);
__IO_REG32(    SCC1CANMDL3 ,  0xfff7dc38,__READ_WRITE);
__IO_REG32(    SCC1CANMDL4 ,  0xfff7dc48,__READ_WRITE);
__IO_REG32(    SCC1CANMDL5 ,  0xfff7dc58,__READ_WRITE);
__IO_REG32(    SCC1CANMDL6 ,  0xfff7dc68,__READ_WRITE);
__IO_REG32(    SCC1CANMDL7 ,  0xfff7dc78,__READ_WRITE);
__IO_REG32(    SCC1CANMDL8 ,  0xfff7dc88,__READ_WRITE);
__IO_REG32(    SCC1CANMDL9 ,  0xfff7dc98,__READ_WRITE);
__IO_REG32(    SCC1CANMDL10,  0xfff7dca8,__READ_WRITE);
__IO_REG32(    SCC1CANMDL11,  0xfff7dcb8,__READ_WRITE);
__IO_REG32(    SCC1CANMDL12,  0xfff7dcc8,__READ_WRITE);
__IO_REG32(    SCC1CANMDL13,  0xfff7dcd8,__READ_WRITE);
__IO_REG32(    SCC1CANMDL14,  0xfff7dce8,__READ_WRITE);
__IO_REG32(    SCC1CANMDL15,  0xfff7dcf8,__READ_WRITE);
__IO_REG32(    SCC1CANMDH0 ,  0xfff7dc0c,__READ_WRITE);  /* Message data high word */
__IO_REG32(    SCC1CANMDH1 ,  0xfff7dc1c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH2 ,  0xfff7dc2c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH3 ,  0xfff7dc3c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH4 ,  0xfff7dc4c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH5 ,  0xfff7dc5c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH6 ,  0xfff7dc6c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH7 ,  0xfff7dc7c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH8 ,  0xfff7dc8c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH9 ,  0xfff7dc9c,__READ_WRITE);
__IO_REG32(    SCC1CANMDH10,  0xfff7dcac,__READ_WRITE);
__IO_REG32(    SCC1CANMDH11,  0xfff7dcbc,__READ_WRITE);
__IO_REG32(    SCC1CANMDH12,  0xfff7dccc,__READ_WRITE);
__IO_REG32(    SCC1CANMDH13,  0xfff7dcdc,__READ_WRITE);
__IO_REG32(    SCC1CANMDH14,  0xfff7dcec,__READ_WRITE);
__IO_REG32(    SCC1CANMDH15,  0xfff7dcfc,__READ_WRITE);

#define SCC1_RAM_OFFSET 0xFFF7DC00

/***************************************************************************
 **
 ** CS2Ia
 **
 ***************************************************************************/

__IO_REG8_BIT(C2SIAISR,   0xfff7c803,__READ_WRITE,__c2siaisr_bits);
__IO_REG8_BIT(C2SIAICR,   0xfff7c807,__READ_WRITE,__c2siaicr_bits);
__IO_REG8_BIT(C2SIAGSR,   0xfff7c80b,__READ_WRITE,__c2siagsr_bits);
__IO_REG8_BIT(C2SIAGCR,   0xfff7c80f,__READ_WRITE,__c2siagcr_bits);
__IO_REG8(    C2SIATDB,   0xfff7c813,__READ_WRITE);
__IO_REG8_BIT(C2SIACCSR,  0xfff7c817,__READ_WRITE,__c2siaccsr_bits);
__IO_REG8_BIT(C2SIACTR,   0xfff7c81b,__READ_WRITE,__c2siactr_bits);
__IO_REG8_BIT(C2SIACLK,   0xfff7c81f,__READ_WRITE,__c2siaclk_bits);
__IO_REG8(    C2SIATBC,   0xfff7c823,__READ_WRITE);
__IO_REG8_BIT(C2SIAPC1,   0xfff7c827,__READ_WRITE,__c2siapc1_bits);
__IO_REG8_BIT(C2SIAPC2,   0xfff7c82b,__READ_WRITE,__c2siapc2_bits);
__IO_REG8_BIT(C2SIAPC3,   0xfff7c82f,__READ_WRITE,__c2siapc3_bits);
__IO_REG8(    C2SIAEMU,   0xfff7c833,__READ_WRITE);
__IO_REG8(    C2SIARDB,   0xfff7c837,__READ_WRITE);
__IO_REG8_BIT(C2SIACAL,   0xfff7c83b,__READ_WRITE,__c2siacal_bits);
__IO_REG8_BIT(C2SIABRK,   0xfff7c83f,__READ_WRITE,__c2siabrk_bits);

/***************************************************************************
 **
 ** Flash Module
 **
 ***************************************************************************/

__IO_REG16_BIT(FMBAC1,    0xffe88002,__READ_WRITE,__fmbac1_bits);
__IO_REG16_BIT(FMBAC2,    0xffe88006,__READ_WRITE,__fmbac2_bits);
__IO_REG16(    FMBSEA,    0xffe8800a,__READ_WRITE);
__IO_REG16(    FMBSEB,    0xffe8800e,__READ_WRITE);
__IO_REG16_BIT(FMBRDY,    0xffe88012,__READ_WRITE,__fmbrdy_bits);

__IO_REG32_BIT(FMREGOPT,  0xffe89c00,__READ_WRITE,__fmregopt_bits);
__IO_REG32_BIT(FMBBUSY,   0xffe89c08,__READ_WRITE,__fmbbusy_bits);
__IO_REG32(    FMPKEY,    0xffe89c0c,__READ_WRITE);

__IO_REG16_BIT(FMPRDY,    0xffe8a816,__READ_WRITE,__fmprdy_bits);

__IO_REG16_BIT(FMMAC1,    0xffe8bc02,__READ_WRITE,__fmmac1_bits);
__IO_REG16_BIT(FMMAC2,    0xffe8bc06,__READ_WRITE,__fmmac2_bits);
__IO_REG16(    FMPAGP,    0xffe8bc0a,__READ_WRITE);
__IO_REG16_BIT(FMMSTAT,   0xffe8bc0e,__READ_WRITE,__fmmstat_bits);

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
 **  CIM interrupt channels
 **
 ***************************************************************************/
#define CIM_SPI1         0  /* SPI1 end-transfer/overrun          */
#define CIM_COMP2        1  /* COMP2 interrupt                    */
#define CIM_COMP1        2  /* COMP1 interrupt                    */
#define CIM_TAP          3  /* TAP interrupt                      */
#define CIM_SPI2         4  /* SPI2 end-transfer/overrun          */
#define CIM_GIOA         5  /* GIO interrupt A                    */
//#define CIM_RES        6  /* --- Reserved ---                   */
#define CIM_HET1         7  /* HET interrupt 1                    */
//#define CIM_RES        8  /* --- Reserved ---                   */
#define CIM_SCIRXERR     9  /* SCI1 or SCI2 error interrupt       */
#define CIM_SCI1RX      10  /* SCI1 receive interrupt             */
#define CIM_C2SIB       11  /* C2SIb interrupt                    */
//#define CIM_RES       12  /* --- Reserved ---                   */
//#define CIM_RES       13  /* --- Reserved ---                   */
#define CIM_SCCA        14  /* SCC interrupt A                    */
//#define CIM_RES       15  /* --- Reserved ---                   */
#define CIM_MIBADCEE    16  /* MibADC end event conversion        */
#define CIM_SCI2RX      17  /* SCI2 receive interrupt             */
//#define CIM_RES       18  /* --- Reserved ---                   */
//#define CIM_RES       19  /* --- Reserved ---                   */
#define CIM_SCI1TX      20  /* SCI1 transmit interrupt            */
#define CIM_SSI         21  /* SW interrupt (SSI)                 */
//#define CIM_RES       22  /* --- Reserved ---                   */
#define CIM_HET2        23  /* HET interrupt 2                    */
//#define CIM_RES       24  /* --- Reserved ---                   */
#define CIM_SCCB        25  /* SCC interrupt B                    */
#define CIM_SCI2TX      26  /* SCI2 transmit interrupt            */
#define CIM_MIBADCE1    27  /* MibADC end Group 1 conversion      */
//#define CIM_RES       28  /* --- Reserved ---                   */
#define CIM_GIOB        29  /* GIO interrupt B                    */
#define CIM_MIBADCE2    30  /* MibADC end Group 2 conversion      */
//#define CIM_RES       31  /* --- Reserved ---                   */


#endif    /* __IOTMS470R1A64_H */

