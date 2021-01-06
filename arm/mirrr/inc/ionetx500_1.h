/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    ST NETX500
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.1.2.3 $
 **
 ***************************************************************************/

#ifndef __NETX500_H
#define __NETX500_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **   NETX500 SPECIAL FUNCTION REGISTERS
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

/* BOO_SR – Bond Out Option Status Register */
typedef struct {
  __REG32  BOND_OPTION    : 3;
  __REG32                 :29;
} __boo_sr_bits;

/* IOC_ACCESS_KEY – IO Configuration Access Key Register */
typedef struct {
  __REG32  ACCESS_KEY     :16;
  __REG32                 :16;
} __ioc_access_key_bits;

/* IOC_CR – IO Configuration Register
   IOC_MR – IO Configuration Mask Register */
typedef struct {
  __REG32  SEL_HIF          : 1;
  __REG32  SEL_LCD_BW       : 1;
  __REG32  SEL_LCD_COL      : 1;
  __REG32  SEL_MII2         : 1;
  __REG32  SEL_MII3         : 1;
  __REG32  SEL_MII23        : 1;
  __REG32  SEL_MII3PWM      : 1;
  __REG32  SEL_FO0          : 1;
  __REG32  SEL_FO1          : 1;
  __REG32  SEL_F0_PWM3      : 1;
  __REG32  SEL_F0_FAILURE3  : 1;
  __REG32  SEL_F1_PWM3      : 1;
  __REG32  SEL_F2_FAILURE3  : 1;
  __REG32  SEL_F2_RPWM3     : 1;
  __REG32  SEL_F3_PWM3      : 1;
  __REG32  SEL_E_PWM2       : 1;
  __REG32  SEL_E_FAILURE2   : 1;
  __REG32  SEL_E_RPWM2      : 1;
  __REG32  SEL_ENC0         : 1;
  __REG32  SEL_ENC1         : 1;
  __REG32  SEL_MP           : 1;
  __REG32  SEL_LED_MII2     : 1;
  __REG32  SEL_LED_MII3     : 1;
  __REG32  SEL_ETM          : 1;
  __REG32  SEL_WDG          : 1;
  __REG32  SEL_F0_PWM3_ECLK : 1;
  __REG32  SEL_F1_PWM3_ECLK : 1;
  __REG32  SEL_F3_PWM3_ECLK : 1;
  __REG32  SEL_E_PWM2_ECLK  : 1;
  __REG32                   : 2;
  __REG32  IF_SELECT_N      : 1;
} __ioc_cr_bits;

/* RES_CR – Reset Control Register */
typedef struct {
  __REG32  RSTINN           : 1;
  __REG32  WDG_RES          : 1;
  __REG32  HOST_RES         : 1;
  __REG32  FIRMW_RES        : 1;
  __REG32  XPEC0_RES        : 1;
  __REG32  XPEC1_RES        : 1;
  __REG32  XPEC2_RES        : 1;
  __REG32  XPEC3_RES        : 1;
  __REG32                   : 8;
  __REG32  DIS_XPEC0_RES    : 1;
  __REG32  DIS_XPEC1_RES    : 1;
  __REG32  DIS_XPEC2_RES    : 1;
  __REG32  DIS_XPEC3_RES    : 1;
  __REG32  FIRMW_FLG0       : 1;
  __REG32  FIRMW_FLG1       : 1;
  __REG32  FIRMW_FLG2       : 1;
  __REG32  FIRMW_FLG3       : 1;
  __REG32  _FIRMW_RES       : 1;
  __REG32  RSTOUTN          : 1;
  __REG32  EN_RSTOUTN       : 1;
  __REG32                   : 5;
} __res_cr_bits;

/* WDG_TR – Watchdog Trigger Register */
typedef struct {
  __REG32  WDG_ACCESS_CODE  :20;
  __REG32                   : 4;
  __REG32  IRQ_REQ          : 1;
  __REG32                   : 3;
  __REG32  WDG_TRIG         : 1;
  __REG32  WDG_ACT_EN       : 1;
  __REG32                   : 1;
  __REG32  WR_ENABLE        : 1;
} __wdg_tr_bits;

/* WDG_CTR – Watchdog Counter */
typedef struct {
  __REG32  WDG_COUNTER      :16;
  __REG32                   :16;
} __wdg_ctr_bits;

/* WDG_IRQ_TIMEOUT – Watchdog Interrupt Timeout */
typedef struct {
  __REG32  WDG_IRQ_TIMEOUT  :16;
  __REG32                   :16;
} __wdg_irq_timeout_bits;

/* WDG_RES_TIMEOUT – Watchdog Reset Timeout */
typedef struct {
  __REG32  WDG_RES_TIMEOUT  :16;
  __REG32                   :16;
} __wdg_res_timeout_bits;

/* SYS_STA – System Status */
typedef struct {
  __REG32  RDY              : 1;
  __REG32  RUN              : 1;
  __REG32  NETX_STATE       : 2;
  __REG32  HOST_STATE       : 4;
  __REG32  NETX_STA_CODE    : 8;
  __REG32  RDY_IN           : 1;
  __REG32  RUN_IN           : 1;
  __REG32  RDY_POL          : 1;
  __REG32  RUN_POL          : 1;
  __REG32                   : 4;
  __REG32  RDY_DRV          : 1;
  __REG32  RUN_DRV          : 1;
  __REG32                   : 6;
} __sys_sta_bits;

/* MEMSRn_CR – Memory SRAM Control Register for Chip Select Area */
typedef struct {
  __REG32  WSEXTMEM         : 6;
  __REG32                   : 2;
  __REG32  WSPREPASEEXTMEM  : 2;
  __REG32                   : 6;
  __REG32  WSPOSTPAUSEEXTMEM: 2;
  __REG32                   : 6;
  __REG32  WIDTHEXTMEM      : 2;
  __REG32                   : 6;
} __memsr_cr_bits;

/* MEMDR_CONFIG_CR – Memory SDRAM Configuration Control Register */
typedef struct {
  __REG32  BANKS            : 2;
  __REG32                   : 2;
  __REG32  ROWS             : 3;
  __REG32                   : 1;
  __REG32  COLUMNS          : 3;
  __REG32                   : 5;
  __REG32  DBUS32           : 1;
  __REG32  SDRAM_PWDN       : 1;
  __REG32  EXTCLK_EN        : 1;
  __REG32  CTRL_EN          : 1;
  __REG32                   : 4;
  __REG32  REFRESH_MODE     : 2;
  __REG32                   : 4;
  __REG32  SDRAM_READY      : 1;
  __REG32  REFRESH_ERROR    : 1;
} __memdr_config_cr_bits;

/* MEMDR_TIMING_CR – Memory SDRAM Timing Control Register */
typedef struct {
  __REG32  T_RCD            : 2;
  __REG32                   : 2;
  __REG32  T_WR             : 2;
  __REG32  T_RP             : 2;
  __REG32  T_RAS            : 3;
  __REG32                   : 1;
  __REG32  T_RFC            : 4;
  __REG32  T_REFI           : 2;
  __REG32                   : 2;
  __REG32  MEM_SDCLK_PHASE  : 3;
  __REG32  MEM_SDCLK_SSNEG  : 1;
  __REG32  DATA_SAMPLE_PHASE: 3;
  __REG32                   : 1;
  __REG32  BYPASS_NEG_DELAY : 1;
  __REG32                   : 3;
} __memdr_timing_cr_bits;

/* MEMDR_MR – Memory SDRAM Mode Register */
typedef struct {
  __REG32  MR               :14;
  __REG32                   : 2;
  __REG32  EMR              :14;
  __REG32                   : 2;
} __memdr_mr_bits;

/* MEMDR_EMR – Memory SDRAM Extended Mode Register */
typedef struct {
  __REG32  EMR2             :14;
  __REG32                   : 2;
  __REG32  EMR3             :14;
  __REG32                   : 2;
} __memdr_emr_bits;

/* MEMPRIO_TIMESLOT_CR – Memory Priority Timeslot Control Register */
typedef struct {
  __REG32  TS_LENGTH_HIF_MI : 3;
  __REG32                   : 1;
  __REG32  TS_LENGTH_XC_MI  : 3;
  __REG32                   : 1;
  __REG32  TS_LENGTH_LCD_MI : 3;
  __REG32                   : 1;
  __REG32  TS_LENGTH_ARMI_MI: 3;
  __REG32                   : 1;
  __REG32  TS_LENGTH_ARMD_MI: 3;
  __REG32                   :13;
} __memprio_timeslot_cr_bits;

/* MEMPRIO_ACCESS_CR – Memory Priority Access Control Register */
typedef struct {
  __REG32  TS_ACCESSRATE_HIF_MI : 6;
  __REG32  TS_ACCESSRATE_XC_MI  : 6;
  __REG32  TS_ACCESSRATE_LCD_MI : 6;
  __REG32  TS_ACCESSRATE_ARMI_MI: 6;
  __REG32  TS_ACCESSRATE_ARMD_MI: 6;
  __REG32                       : 2;
} __memprio_access_cr_bits;

/* MEMPRIO_ACCESS_CR – Memory Priority Access Control Register */
typedef struct {
  __REG32  CS_EN            : 1;
  __REG32  _16BIT           : 1;
  __REG32  NWR_MODE         : 1;
  __REG32  DS_MODE          : 1;
  __REG32  NRD_MODE         : 1;
  __REG32  WAIT_EN          : 1;
  __REG32  WAIT_POLARITY    : 1;
  __REG32  TRDWRCYC         : 5;
  __REG32  TRDWROFF         : 5;
  __REG32  TWRON            : 3;
  __REG32  TRDON            : 3;
  __REG32  TCSON            : 3;
  __REG32  TADRHOLD         : 3;
  __REG32  TALEWIDTH        : 3;
} __ext_config_cs_bits;

/* DPMHS_INT_EN0 – DPM Host Side Interrupt Enable 0 */
typedef struct {
  __REG32  HS_EVENT0        : 1;
  __REG32  HS_EVENT1        : 1;
  __REG32  HS_EVENT2        : 1;
  __REG32  HS_EVENT3        : 1;
  __REG32  HS_EVENT4        : 1;
  __REG32  HS_EVENT5        : 1;
  __REG32  HS_EVENT6        : 1;
  __REG32  HS_EVENT7        : 1;
  __REG32  HS_EVENT8        : 1;
  __REG32  HS_EVENT9        : 1;
  __REG32  HS_EVENT10       : 1;
  __REG32  HS_EVENT11       : 1;
  __REG32  HS_EVENT12       : 1;
  __REG32  HS_EVENT13       : 1;
  __REG32  HS_EVENT14       : 1;
  __REG32  HS_EVENT15       : 1;
  __REG32                   : 9;
  __REG32  TMR              : 1;
  __REG32  SYS_STA          : 1;
  __REG32                   : 2;
  __REG32  WDG_NETX         : 1;
  __REG32  MEM_LCK          : 1;
  __REG32  INT_EN           : 1;
} __dpmhs_int_en0_bits;

/* DPMHS_INT_STA0 – DPM Host Side Interrupt Status 0 */
typedef struct {
  __REG32  HS_EVENT0        : 1;
  __REG32  HS_EVENT1        : 1;
  __REG32  HS_EVENT2        : 1;
  __REG32  HS_EVENT3        : 1;
  __REG32  HS_EVENT4        : 1;
  __REG32  HS_EVENT5        : 1;
  __REG32  HS_EVENT6        : 1;
  __REG32  HS_EVENT7        : 1;
  __REG32  HS_EVENT8        : 1;
  __REG32  HS_EVENT9        : 1;
  __REG32  HS_EVENT10       : 1;
  __REG32  HS_EVENT11       : 1;
  __REG32  HS_EVENT12       : 1;
  __REG32  HS_EVENT13       : 1;
  __REG32  HS_EVENT14       : 1;
  __REG32  HS_EVENT15       : 1;
  __REG32  IRQ_VECTOR       : 8;
  __REG32                   : 1;
  __REG32  TMR              : 1;
  __REG32  SYS_STA          : 1;
  __REG32                   : 2;
  __REG32  WDG_NETX         : 1;
  __REG32  MEM_LCK          : 1;
  __REG32  INT_EN           : 1;
} __dpmhs_int_sta0_bits;

/* DPMHS_RES_REQ – DPM Host Side Reset Request */
typedef struct {
  __REG32  CONTROL          : 8;
  __REG32  DEL_CNT          : 9;
  __REG32                   :15;
} __dpmhs_res_req_bits;

/* DPMHS_SYS_STA – DPM Host Side System Status */
typedef struct {
  __REG32  RDY              : 1;
  __REG32  RUN              : 1;
  __REG32  NETX_STATE       : 2;
  __REG32  HOST_STATE       : 4;
  __REG32  NETX_STA_CODE    : 8;
  __REG32                   :16;
} __dpmhs_sys_sta_bits;

/* DPMHS_TMR_START_VALUE – DPM Host Side Timer Start Value */
typedef struct {
  __REG32  TMR_START        :16;
  __REG32                   :16;
} __dpmhs_tmr_start_value_bits;

/* DPMHS_TMR_CTRL – DPM Host Side Timer Control */
typedef struct {
  __REG32  CLKDIV           : 3;
  __REG32  FNCT             : 1;
  __REG32                   :11;
  __REG32  START            : 1;
  __REG32                   :16;
} __dpmhs_tmr_ctrl_bits;

/* DPMHS_WDG_ARM_TIMEOUT – DPM Host Side Watchdog ARM */
typedef struct {
  __REG32  TIMEOUT_VAL      :16;
  __REG32                   :16;
} __dpmhs_wdg_arm_timeout_bits;

/* DPMHS_WDG_HOST_TRIG – DPM Host Side Watchdog Host Trigger */
typedef struct {
  __REG32  WDG_TRIGGER_CODE : 8;
  __REG32                   :24;
} __dpmhs_wdg_host_trig_bits;

/* DPMHS_WDG_HOST_TIMEOUT – DPM Host Side Watchdog Host Timeout */
typedef struct {
  __REG32  TIMEOUT_VAL      :16;
  __REG32                   :16;
} __dpmhs_wdg_host_timeout_bits;

/* DPM Host Side Handshake Register Pair (HostgnetX and netXgHost) */
typedef union {
  // DPMHS_HS_DATAx
  struct {
  __REG32  HOST_DATA16      :16;
  __REG32  NETX_DATA16      :16;
  };
  // 8 bits
  struct {
  __REG32  DATA_MEMORY      :16;
  __REG32  HOST_DATA8       : 8;
  __REG32  NETX_DATA8       : 8;
  };
} __dpmhs_hs_data_bits;

/* DPMAS_HSCRn – DPM ARM Side Handshake Control Registers */
typedef struct {
  __REG32  _16BIT           : 1;
  __REG32                   : 1;
  __REG32  DPM_BASE_ADDR    :14;
  __REG32                   :15;
  __REG32  ENABLE           : 1;
} __dpmas_hscr_bits;

/* DPMAS_DB_ENDn – DPM ARM Side Data Block n End */
typedef struct {
  __REG32                   : 8;
  __REG32  DATA_BLOCK_END   : 8;
  __REG32                   :15;
  __REG32  ENABLE           : 1;
} __dpmas_db_end_bits;

/* DPMAS_DB_MAPPINGn – DPM ARM Side Data Block n Address Mapping */
typedef struct {
  __REG32                   : 8;
  __REG32  NETX_MAP_ADDR    :24;
} __dpmas_db_mapping_bits;

/* DPMAS_IO_DATA1 – DPM ARM Side Input / Output Data 1 */
typedef struct {
  __REG32  PIO_DATA64       : 1;
  __REG32  PIO_DATA65       : 1;
  __REG32  PIO_DATA66       : 1;
  __REG32  PIO_DATA67       : 1;
  __REG32  PIO_DATA68       : 1;
  __REG32  PIO_DATA69       : 1;
  __REG32  PIO_DATA70       : 1;
  __REG32  PIO_DATA71       : 1;
  __REG32  PIO_DATA72       : 1;
  __REG32  PIO_DATA73       : 1;
  __REG32  PIO_DATA74       : 1;
  __REG32  PIO_DATA75       : 1;
  __REG32  PIO_DATA76       : 1;
  __REG32  PIO_DATA77       : 1;
  __REG32  PIO_DATA78       : 1;
  __REG32  PIO_DATA79       : 1;
  __REG32  PIO_DATA80       : 1;
  __REG32  PIO_DATA81       : 1;
  __REG32  PIO_DATA82       : 1;
  __REG32  PIO_DATA83       : 1;
  __REG32  PIO_DATA84       : 1;
  __REG32                   :11;
} __dpmas_io_data1_bits;

/* DPMAS_IO_DRV_EN1 – DPM ARM Side Input / Output Driver Enable 1 */
typedef struct {
  __REG32  PIO_DRV64        : 1;
  __REG32  PIO_DRV65        : 1;
  __REG32  PIO_DRV66        : 1;
  __REG32  PIO_DRV67        : 1;
  __REG32  PIO_DRV68        : 1;
  __REG32  PIO_DRV69        : 1;
  __REG32  PIO_DRV70        : 1;
  __REG32  PIO_DRV71        : 1;
  __REG32  PIO_DRV72        : 1;
  __REG32  PIO_DRV73        : 1;
  __REG32  PIO_DRV74        : 1;
  __REG32  PIO_DRV75        : 1;
  __REG32  PIO_DRV76        : 1;
  __REG32  PIO_DRV77        : 1;
  __REG32  PIO_DRV78        : 1;
  __REG32  PIO_DRV79        : 1;
  __REG32  PIO_DRV80        : 1;
  __REG32  PIO_DRV81        : 1;
  __REG32  PIO_DRV82        : 1;
  __REG32  PIO_DRV83        : 1;
  __REG32  PIO_DRV84        : 1;
  __REG32                   :11;
} __dpmas_io_drv_en1_bits;

/* DPMAS_IO_MODE1 – DPM ARM Side Input / Output Mode 1 */
typedef struct {
  __REG32  PIO_MODE64       : 1;
  __REG32  PIO_MODE65       : 1;
  __REG32  PIO_MODE66       : 1;
  __REG32  PIO_MODE67       : 1;
  __REG32  PIO_MODE68       : 1;
  __REG32  PIO_MODE69       : 1;
  __REG32  PIO_MODE70       : 1;
  __REG32  PIO_MODE71       : 1;
  __REG32  PIO_MODE72       : 1;
  __REG32  PIO_MODE73       : 1;
  __REG32  PIO_MODE74       : 1;
  __REG32  PIO_MODE75       : 1;
  __REG32  PIO_MODE76       : 1;
  __REG32  PIO_MODE77       : 1;
  __REG32  PIO_MODE78       : 1;
  __REG32  PIO_MODE79       : 1;
  __REG32  PIO_MODE80       : 1;
  __REG32  PIO_MODE81       : 1;
  __REG32  PIO_MODE82       : 1;
  __REG32  PIO_MODE83       : 1;
  __REG32  PIO_MODE84       : 1;
  __REG32                   :10;
  __REG32  IN_CONTROL       : 1;
} __dpmas_io_mode1_bits;

/* DPMAS_IO_DATA0 – DPM ARM Side Input / Output Data 0 */
typedef struct {
  __REG32  PIO_DATA32       : 1;
  __REG32  PIO_DATA33       : 1;
  __REG32  PIO_DATA34       : 1;
  __REG32  PIO_DATA35       : 1;
  __REG32  PIO_DATA36       : 1;
  __REG32  PIO_DATA37       : 1;
  __REG32  PIO_DATA38       : 1;
  __REG32  PIO_DATA39       : 1;
  __REG32  PIO_DATA40       : 1;
  __REG32  PIO_DATA41       : 1;
  __REG32  PIO_DATA42       : 1;
  __REG32  PIO_DATA43       : 1;
  __REG32  PIO_DATA44       : 1;
  __REG32  PIO_DATA45       : 1;
  __REG32  PIO_DATA46       : 1;
  __REG32  PIO_DATA47       : 1;
  __REG32  PIO_DATA48       : 1;
  __REG32  PIO_DATA49       : 1;
  __REG32  PIO_DATA50       : 1;
  __REG32  PIO_DATA51       : 1;
  __REG32  PIO_DATA52       : 1;
  __REG32  PIO_DATA53       : 1;
  __REG32  PIO_DATA54       : 1;
  __REG32  PIO_DATA55       : 1;
  __REG32  PIO_DATA56       : 1;
  __REG32  PIO_DATA57       : 1;
  __REG32  PIO_DATA58       : 1;
  __REG32  PIO_DATA59       : 1;
  __REG32  PIO_DATA60       : 1;
  __REG32  PIO_DATA61       : 1;
  __REG32  PIO_DATA62       : 1;
  __REG32  PIO_DATA63       : 1;
} __dpmas_io_data0_bits;

/* DPMAS_IO_DRV_EN0 – DPM ARM Side Input / Output Driver Enable 0 */
typedef struct {
  __REG32  PIO_DRV32        : 1;
  __REG32  PIO_DRV33        : 1;
  __REG32  PIO_DRV34        : 1;
  __REG32  PIO_DRV35        : 1;
  __REG32  PIO_DRV36        : 1;
  __REG32  PIO_DRV37        : 1;
  __REG32  PIO_DRV38        : 1;
  __REG32  PIO_DRV39        : 1;
  __REG32  PIO_DRV40        : 1;
  __REG32  PIO_DRV41        : 1;
  __REG32  PIO_DRV42        : 1;
  __REG32  PIO_DRV43        : 1;
  __REG32  PIO_DRV44        : 1;
  __REG32  PIO_DRV45        : 1;
  __REG32  PIO_DRV46        : 1;
  __REG32  PIO_DRV47        : 1;
  __REG32  PIO_DRV48        : 1;
  __REG32  PIO_DRV49        : 1;
  __REG32  PIO_DRV50        : 1;
  __REG32  PIO_DRV51        : 1;
  __REG32  PIO_DRV52        : 1;
  __REG32  PIO_DRV53        : 1;
  __REG32  PIO_DRV54        : 1;
  __REG32  PIO_DRV55        : 1;
  __REG32  PIO_DRV56        : 1;
  __REG32  PIO_DRV57        : 1;
  __REG32  PIO_DRV58        : 1;
  __REG32  PIO_DRV59        : 1;
  __REG32  PIO_DRV60        : 1;
  __REG32  PIO_DRV61        : 1;
  __REG32  PIO_DRV62        : 1;
  __REG32  PIO_DRV63        : 1;
} __dpmas_io_drv_en0_bits;

/* DPMAS_IO_MODE0 – DPM ARM Side Input / Output Mode 0 */
typedef struct {
  __REG32  PIO_MODE32       : 1;
  __REG32  PIO_MODE33       : 1;
  __REG32  PIO_MODE34       : 1;
  __REG32  PIO_MODE35       : 1;
  __REG32  PIO_MODE36       : 1;
  __REG32  PIO_MODE37       : 1;
  __REG32  PIO_MODE38       : 1;
  __REG32  PIO_MODE39       : 1;
  __REG32  PIO_MODE40       : 1;
  __REG32  PIO_MODE41       : 1;
  __REG32  PIO_MODE42       : 1;
  __REG32  PIO_MODE43       : 1;
  __REG32  PIO_MODE44       : 1;
  __REG32  PIO_MODE45       : 1;
  __REG32  PIO_MODE46       : 1;
  __REG32  PIO_MODE47       : 1;
  __REG32  PIO_MODE48       : 1;
  __REG32  PIO_MODE49       : 1;
  __REG32  PIO_MODE50       : 1;
  __REG32  PIO_MODE51       : 1;
  __REG32  PIO_MODE52       : 1;
  __REG32  PIO_MODE53       : 1;
  __REG32  PIO_MODE54       : 1;
  __REG32  PIO_MODE55       : 1;
  __REG32  PIO_MODE56       : 1;
  __REG32  PIO_MODE57       : 1;
  __REG32  PIO_MODE58       : 1;
  __REG32  PIO_MODE59       : 1;
  __REG32  PIO_MODE60       : 1;
  __REG32  PIO_MODE61       : 1;
  __REG32  PIO_MODE62       : 1;
  __REG32  PIO_MODE63       : 1;
} __dpmas_io_mode0_bits;

/* DPMAS_IF_CONF1 – DPM ARM Side Interface Configuration Register 1 */
typedef struct {
  __REG32  CS_COMP_VAL        : 8;
  __REG32  CS_COMP_SRC        : 8;
  __REG32  ADR_IN             : 4;
  __REG32                     : 3;
  __REG32  DIS_BUSY_TIMEOUT   : 1;
  __REG32  DATAOUT_VALID_TIME : 2;
  __REG32  IRQ_POL_PIO35      : 1;
  __REG32  IRQ_POL_PIO36      : 1;
  __REG32  IRQ_POL_PIO40      : 1;
  __REG32  IRQ_POL_PIO47      : 1;
  __REG32  IRQ_POL_PIO72      : 1;
  __REG32  WRITE_PROTECT      : 1;
} __dpmas_if_conf1_bits;

/* DPMAS_IF_CONF0 – DPM ARM Side Interface Configuration Register 0 */
typedef struct {
  __REG32  OE_MODE            : 3;
  __REG32  ADDR_MODE          : 1;
  __REG32  ALE_MODE           : 2;
  __REG32  IRQ_POLARITY       : 1;
  __REG32  IRQ_MODE           : 2;
  __REG32  CS_MODE            : 3;
  __REG32  WAIT_POLARITY      : 1;
  __REG32  WAIT_MODE          : 1;
  __REG32  WAIT_DRV           : 2;
  __REG32  CIS_MODE           : 2;
  __REG32  BE0_MODE           : 3;
  __REG32  BE1_MODE           : 3;
  __REG32  WR_CTRL            : 2;
  __REG32  RD_CTRL            : 2;
  __REG32  HIF_MODE           : 3;
  __REG32  DISABLE_WR         : 1;
} __dpmas_if_conf0_bits;

/* DPMAS_CLKOUT_CONF – DPM ARM Side Clock out configuration */
typedef struct {
  __REG32  CLK_SEL            :30;
  __REG32                     : 1;
  __REG32  CLKOUT_EN          : 1;
} __dpmas_clkout_conf_bits;

/* DPMAS_HS_DATAn – DPM ARM View Handshake Register n */
typedef union {
  // DPMAS_HS_DATAx
  struct {
  __REG32  HOST_DATA16        :16;
  __REG32  NETX_DATA16        :16;
  };
  // 8 bits
  struct {
  __REG32  DATA_MEMORY        :16;
  __REG32  HOST_DATA8         : 8;
  __REG32  NETX_DATA8         : 8;
  };
} __dpmas_hs_data_bits;

/* DPMAS_INT_EN1 – DPM ARM Side Interrupt Enable 1 */
typedef struct {
  __REG32  HANDSHAKE_EVENT    :16;
  __REG32                     : 8;
  __REG32  INT_PIO35          : 1;
  __REG32  INT_PIO36          : 1;
  __REG32  INT_PIO40          : 1;
  __REG32  INT_PIO47          : 1;
  __REG32  INT_PIO72          : 1;
  __REG32  WDG                : 1;
  __REG32  MEM_LCK            : 1;
  __REG32  GLB_EN             : 1;
} __dpmas_int_en1_bits;

/* DPMAS_INT_STA1 – DPM ARM Side Interrupt Status 1 */
typedef struct {
  __REG32  HANDSHAKE_EVENT    :16;
  __REG32  IRQ_VECTOR         : 8;
  __REG32  INT_PIO35          : 1;
  __REG32  INT_PIO36          : 1;
  __REG32  INT_PIO40          : 1;
  __REG32  INT_PIO47          : 1;
  __REG32  INT_PIO72          : 1;
  __REG32  WDG_IRQ            : 1;
  __REG32  MEM_LCK            : 1;
  __REG32  IRQ_REQ            : 1;
} __dpmas_int_sta1_bits;

/* DPMAS_WDG_ARM_TRIG – DPM ARM Side Watchdog ARM Supervision Trigger */
typedef struct {
  __REG32  WDG_ACCESS_CODE    : 8;
  __REG32                     :24;
} __dpmas_wdg_arm_trig_bits;

/* DPMAS_WDG_ARM_TIMEOUT – DPM ARM Side Watchdog ARM Timeout
   DPMAS_WDG_HOST_TIMEOUT – DPM ARM Side Watchdog Host Timeout */
typedef struct {
  __REG32  TIMEOUT_VAL        :16;
  __REG32                     :16;
} __dpmas_wdg_arm_timeout_bits;

/* DPMAS_CIS_MAPPING – DPM ARM Side CIS Mapping Address */
typedef struct {
  __REG32  CIS_ENABLE         : 1;
  __REG32  WR_ENABLE          : 1;
  __REG32                     : 6;
  __REG32  CIS_MAPPING        :24;
} __dpmas_cis_mapping_bits;

/* GPIO_CFGn – GPIO n Configuration Register */
typedef struct {
  __REG32  IOCFG              : 2;
  __REG32  INV                : 1;
  __REG32  MODE               : 2;
  __REG32  COUNT_REF          : 3;
  __REG32                     :24;
} __gpio_cfg_bits;

/* GPIO_COUNTERn_CTRL – GPIO Counter n Control */
typedef struct {
  __REG32  RUN                : 1;
  __REG32  SYM_NASYM          : 1;
  __REG32  ONCE               : 1;
  __REG32  IRQ_EN             : 1;
  __REG32  CNT_EVENT          : 1;
  __REG32  RST_EN             : 1;
  __REG32  SEL_EVENT          : 1;
  __REG32  GPIO_REF           : 4;
  __REG32                     :21;
} __gpio_counter_ctrl_bits;

/* GPIO_IRQ_MASK_SET – GPIO Interrupt Enable
   GPIO_IRQ_MASK_RST – GPIO Interrupt Disable
   GPIO_IRQ– GPIO Interrupt Register */
typedef struct {
  __REG32  GPIO               :16;
  __REG32  CNT0               : 1;
  __REG32  CNT1               : 1;
  __REG32  CNT2               : 1;
  __REG32  CNT3               : 1;
  __REG32  CNT4               : 1;
  __REG32  SYSTIME            : 1;
  __REG32                     :10;
} __gpio_irq_mask_set_bits;

/* GPIO_LINE– GPIO Line Register */
typedef struct {
  __REG32  GPIO0              : 1;
  __REG32  GPIO1              : 1;
  __REG32  GPIO2              : 1;
  __REG32  GPIO3              : 1;
  __REG32  GPIO4              : 1;
  __REG32  GPIO5              : 1;
  __REG32  GPIO6              : 1;
  __REG32  GPIO7              : 1;
  __REG32  GPIO8              : 1;
  __REG32  GPIO9              : 1;
  __REG32  GPIO10             : 1;
  __REG32  GPIO11             : 1;
  __REG32  GPIO12             : 1;
  __REG32  GPIO13             : 1;
  __REG32  GPIO14             : 1;
  __REG32  GPIO15             : 1;
  __REG32                     :16;
} __gpio_line_bits;

/* PIO_IN – PIO Input Register
   PIO_OUT – PIO Output Register
   PIO_OE – PIO Output Enable Register */
typedef struct {
  __REG32  PIO0               : 1;
  __REG32  PIO1               : 1;
  __REG32  PIO2               : 1;
  __REG32  PIO3               : 1;
  __REG32  PIO4               : 1;
  __REG32  PIO5               : 1;
  __REG32  PIO6               : 1;
  __REG32  PIO7               : 1;
  __REG32  PIO8               : 1;
  __REG32  PIO9               : 1;
  __REG32  PIO10              : 1;
  __REG32  PIO11              : 1;
  __REG32  PIO12              : 1;
  __REG32  PIO13              : 1;
  __REG32  PIO14              : 1;
  __REG32  PIO15              : 1;
  __REG32  PIO16              : 1;
  __REG32  PIO17              : 1;
  __REG32  PIO18              : 1;
  __REG32  PIO19              : 1;
  __REG32  PIO20              : 1;
  __REG32  PIO21              : 1;
  __REG32  PIO22              : 1;
  __REG32  PIO23              : 1;
  __REG32  PIO24              : 1;
  __REG32  PIO25              : 1;
  __REG32  PIO26              : 1;
  __REG32  PIO27              : 1;
  __REG32  PIO28              : 1;
  __REG32  PIO29              : 1;
  __REG32  PIO30              : 1;
  __REG32                     : 1;
} __pio_in_bits;

/* UART_DR – UART Data Register */
typedef struct {
  __REG32  DATA               : 8;
  __REG32                     :24;
} __uart_dr_bits;

/* UART_SR – UART Status Register */
typedef struct {
  __REG32  FE                 : 1;
  __REG32  PE                 : 1;
  __REG32  BE                 : 1;
  __REG32  OE                 : 1;
  __REG32                     :28;
} __uart_sr_bits;

/* UART_LINE_CR – UART Line Control Register */
typedef struct {
  __REG32  BRK                : 1;
  __REG32  PEN                : 1;
  __REG32  EPS                : 1;
  __REG32  STP2               : 1;
  __REG32  FEN                : 1;
  __REG32  WLEN               : 2;
  __REG32                     :25;
} __uart_line_cr_bits;

/* UART_BAUDDIV_MSB – UART Baud Rate Divisor MSB */
typedef struct {
  __REG32  BAUDDIVMSB         : 8;
  __REG32                     :24;
} __uart_bauddiv_msb_bits;

/* UART_BAUDDIV_LSB – UART Baud Rate Divisor LSB */
typedef struct {
  __REG32  BAUDDIVLSB         : 8;
  __REG32                     :24;
} __uart_bauddiv_lsb_bits;

/* UART_CR – UART Control Register */
typedef struct {
  __REG32  UARTEN             : 1;
  __REG32  SIREN              : 1;
  __REG32  SIRLP              : 1;
  __REG32  MSIE               : 1;
  __REG32  RIE                : 1;
  __REG32  TIE                : 1;
  __REG32  RTIE               : 1;
  __REG32  LBE                : 1;
  __REG32                     :24;
} __uart_cr_bits;

/* UART_FR – UART Flag Register */
typedef struct {
  __REG32  CTS                : 1;
  __REG32  DSR                : 1;
  __REG32  DCD                : 1;
  __REG32  BUSY               : 1;
  __REG32  RXFE               : 1;
  __REG32  TXFF               : 1;
  __REG32  RXFF               : 1;
  __REG32  TXFE               : 1;
  __REG32                     :24;
} __uart_fr_bits;

/* UART_IIR – UART Interrupt Identification Register */
typedef struct {
  __REG32  MIS                : 1;
  __REG32  RIS                : 1;
  __REG32  TIS                : 1;
  __REG32  RTIS               : 1;
  __REG32                     :28;
} __uart_iir_bits;

/* UART_ILPR – UART IrDA Low Power Counter Register */
typedef struct {
  __REG32  ILPDVSR            : 8;
  __REG32                     :24;
} __uart_ilpr_bits;

/* UART_RTS_CR – UART RTS Control Register */
typedef struct {
  __REG32  AUTO               : 1;
  __REG32  RTS                : 1;
  __REG32  COUNT              : 1;
  __REG32  MOD2               : 1;
  __REG32  RTS_POL            : 1;
  __REG32  CTS_CTR            : 1;
  __REG32  CTS_POL            : 1;
  __REG32  STICK              : 1;
  __REG32                     :24;
} __uart_rts_cr_bits;

/* UART_RTS_LEAD – UART RTS Leading Cycles */
typedef struct {
  __REG32  LEADCYC            : 8;
  __REG32                     :24;
} __uart_rts_lead_bits;

/* UART_RTS_TRAIL – UART RTS Trailing cycles */
typedef struct {
  __REG32  TRAILCYC           : 8;
  __REG32                     :24;
} __uart_rts_trail_bits;

/* UART_DRV_ENABLE – UART Driver Enable Register */
typedef struct {
  __REG32  DRVTX              : 1;
  __REG32  DRVRTS             : 1;
  __REG32                     :30;
} __uart_drv_enable_bits;

/* UART_BRM_CR – UART Baud Rate Mode Control Register */
typedef struct {
  __REG32  BAUD_RATE_MODE     : 1;
  __REG32                     :31;
} __uart_brm_cr_bits;

/* UART_RXFIFO_IRQLEVEL – UART Receive FIFO Interrupt Trigger Level */
typedef struct {
  __REG32  RFIRQLEVEL         : 5;
  __REG32                     :27;
} __uart_rxfifo_irqlevel_bits;

/* UART_TXFIFO_IRQLEVEL – UART Transmit FIFO Interrupt Trigger Level */
typedef struct {
  __REG32  TFIRQLEVEL         : 5;
  __REG32                     :27;
} __uart_txfifo_irqlevel_bits;

/* SPI_DATA_REGISTER – SPI Data Register */
typedef struct {
  __REG32  DATA_BYTE_0        : 8;
  __REG32  DATA_BYTE_1        : 8;
  __REG32  DR_VALID0          : 1;
  __REG32  DR_VALID1          : 1;
  __REG32                     :14;
} __spi_data_register_bits;

/* SPI_SR – SPI Status Register */
typedef struct {
  __REG32  SR_IN_FILL_VAL     : 9;
  __REG32  SR_OUT_FILL_VAL    : 9;
  __REG32  SR_IN_FILL_LEVEL   : 1;
  __REG32  SR_IN_RECDATA      : 1;
  __REG32  SR_IN_FULL         : 1;
  __REG32  SR_OUT_FUEL        : 1;
  __REG32  SR_OUT_FW          : 1;
  __REG32  SR_OUT_EMPTY       : 1;
  __REG32  SR_OUT_FULL        : 1;
  __REG32  SR_SELECTED        : 1;
  __REG32                     : 6;
} __spi_sr_bits;

/* SPI_CR – SPI Control Register */
typedef struct {
  __REG32  CR_SOFTRESET       : 1;
  __REG32  CR_SPEED           : 4;
  __REG32                     : 1;
  __REG32  CR_READ            : 1;
  __REG32  CR_WRITE           : 1;
  __REG32  CR_SS              : 3;
  __REG32  CS_MODE            : 1;
  __REG32                     : 8;
  __REG32  CR_CLR_INFIFO      : 1;
  __REG32  CR_CLR_OUTFIFO     : 1;
  __REG32  CR_BURSTDELAY      : 3;
  __REG32  CR_BURST           : 3;
  __REG32  CR_NCPHA           : 1;
  __REG32  CR_CPOL            : 1;
  __REG32  CR_MS              : 1;
  __REG32  CR_EN              : 1;
} __spi_cr_bits;

/* SPI_INTERRUPT_CR – SPI Interrupt Control Register */
typedef struct {
  __REG32  IR_IN_FULL_LEVEL   : 9;
  __REG32  IR_OUT_FULL_LEVEL  : 9;
  __REG32  IR_IN_FUEL_EN      : 1;
  __REG32  IR_IN_RECDATA_EN   : 1;
  __REG32  IR_IN_FULL_EN      : 1;
  __REG32  IR_OUT_FUEL_EN     : 1;
  __REG32  IR_OUT_FW_EN       : 1;
  __REG32  IR_OUT_EMPTY_EN    : 1;
  __REG32  IR_OUT_FULL_EN     : 1;
  __REG32                     : 7;
} __spi_interrupt_cr_bits;

/* I2C_CTRL – I2C Control Register */
typedef struct {
  __REG32  ENABLE             : 1;
  __REG32  SPEED              : 3;
  __REG32  ID                 : 7;
  __REG32                     :21;
} __i2c_ctrl_bits;

/* I2C_DATA – I2C Data Register */
typedef struct {
  __REG32  DATA               : 8;
  __REG32  CMD0               : 1;
  __REG32  CMD1               : 1;
  __REG32  CMD2               : 1;
  __REG32  CMD3               : 1;
  __REG32  RDF                : 1;
  __REG32  ACK                : 2;
  __REG32                     :17;
} __i2c_data_bits;

/* SYSTIME_S_COMPARE_ENABLE – System Time Second Compare Enable Register */
typedef struct {
  __REG32  ENABLE             : 1;
  __REG32                     :31;
} __systime_s_comp_ena_bits;

/* SYSTIME_S_COMPARE_IRQ – System Time Second Compare Interrupt Register */
typedef struct {
  __REG32  COMPARE_IRQ        : 1;
  __REG32                     :31;
} __systime_s_compare_irq_bits;

/* RTC_IRQ2ISOLATE_CYCLES – RTC Number of Clock_32kHz Cycles */
typedef struct {
  __REG32  IRQ2ISO            : 8;
  __REG32                     :24;
} __rtc_irq2isolate_cycles_bits;

/* RTC_IRQ_MSK – RTC Isolated Area Interrupt Mask Register */
typedef struct {
  __REG32  EN_POWER_DOWN      : 1;
  __REG32  EN_CLK32_FAULT1    : 1;
  __REG32  EN_CLK32_FAULT2    : 1;
  __REG32                     :29;
} __rtc_irq_msk_bits;

/* RTC_IRQ_STAT – RTC Isolated Area Interrupt Status Register */
typedef struct {
  __REG32  POWER_DOWN         : 1;
  __REG32  CLK32_FAULT1       : 1;
  __REG32  CLK32_FAULT2       : 1;
  __REG32                     :29;
} __rtc_irq_stat_bits;

/* RTC_ISOLATED – RTC Isolated Area Status */
typedef struct {
  __REG32  NOT_ISOLATED       : 1;
  __REG32                     :31;
} __rtc_isolated_bits;

/* LCD_TIMING0 – LCD Horizontal Axis Panel Control Register */
typedef struct {
  __REG32                     : 2;
  __REG32  PPL                : 6;
  __REG32  HSW                : 8;
  __REG32  HFP                : 8;
  __REG32  HBP                : 8;
} __lcd_timing0_bits;

/* LCD_TIMING1 – LCD Vertical Axis Panel Control Register */
typedef struct {
  __REG32  LPP                :10;
  __REG32  VSW                : 6;
  __REG32  VFP                : 8;
  __REG32  VBD                : 8;
} __lcd_timing1_bits;

/* LCD_TIMING2 – LCD Clock and Signal Polarity Control Register */
typedef struct {
  __REG32  PCD_LO             : 5;
  __REG32  CLKSEL             : 1;
  __REG32  ACB                : 5;
  __REG32  IVS                : 1;
  __REG32  HIS                : 1;
  __REG32  IPC                : 1;
  __REG32  IEO                : 1;
  __REG32                     : 1;
  __REG32  CPL                :10;
  __REG32  BCD                : 1;
  __REG32  PVD_HI             : 5;
} __lcd_timing2_bits;

/* LCD_TIMING3 – LCD Line End Control Register */
typedef struct {
  __REG32  LED                : 7;
  __REG32                     : 9;
  __REG32  LEE                : 1;
  __REG32                     :15;
} __lcd_timing3_bits;

/* LCD_IMSC – LCD Interrupt Mask Set/Clear Register */
typedef struct {
  __REG32                     : 1;
  __REG32  FUFIRQREN          : 1;
  __REG32  LNBUIRQEN          : 1;
  __REG32  VCOMPIRQEN         : 1;
  __REG32  MBEIRQEN           : 1;
  __REG32                     :27;
} __lcd_imsc_bits;

/* LCD_CONTROL – LCD Control Register */
typedef struct {
  __REG32  LCDEN              : 1;
  __REG32  LCDBPP             : 3;
  __REG32  LCDBW              : 1;
  __REG32  LCDTFT             : 1;
  __REG32  LCDMONO8           : 1;
  __REG32  LCDDUAL            : 1;
  __REG32  BGR                : 1;
  __REG32  BEBO               : 1;
  __REG32  BEPO               : 1;
  __REG32  LCDPWR             : 1;
  __REG32  LCDVCOMP           : 2;
  __REG32                     : 2;
  __REG32  WATERMARK          : 1;
  __REG32                     :15;
} __lcd_control_bits;

/* LCD_RIS – LCD Raw Interrupt Status Register */
typedef struct {
  __REG32                     : 1;
  __REG32  FUFSTAT            : 1;
  __REG32  LNBUSTAT           : 1;
  __REG32  VCOMPSTAT          : 1;
  __REG32  MBESTAT            : 1;
  __REG32                     :27;
} __lcd_ris_bits;

/* LCD_MIS – LCD Masked Interrupt Status Register */
typedef struct {
  __REG32                     : 1;
  __REG32  FUFIRQ             : 1;
  __REG32  LNBUIRQ            : 1;
  __REG32  VCOMPIRQ           : 1;
  __REG32  MBEIRQ             : 1;
  __REG32                     :27;
} __lcd_mis_bits;

/* LCD_ICR – LCD Interrupt Clear Register */
typedef struct {
  __REG32                     : 1;
  __REG32  FUFCLR             : 1;
  __REG32  LNBUCLR            : 1;
  __REG32  VCOMPCLR           : 1;
  __REG32  MBECLR             : 1;
  __REG32                     :27;
} __lcd_icr_bits;

/* USB_ID – USB ID Register */
typedef struct {
  __REG32  REV_ID             : 8;
  __REG32  CORE_ID            : 5;
  __REG32                     :19;
} __usb_id_bits;

/* USB_CTRL – USB Control Register */
typedef struct {
  __REG32  CSUSP              : 1;
  __REG32  XSUSP              : 1;
  __REG32  HRS                : 1;
  __REG32  ASE                : 1;
  __REG32  PSE                : 1;
  __REG32                     :27;
} __usb_ctrl_bits;

/* USB_FRM_TIMER – USB Frame Timer Register */
typedef struct {
  __REG32  FRAME_NR           :11;
  __REG32  FTLOCK             : 1;
  __REG32  AGSOF              : 1;
  __REG32                     :19;
} __usb_frm_timer_bits;

/* USB_MAIN_EV – USB Main Event Register */
typedef struct {
  __REG32  FRM_EV             : 1;
  __REG32  FRM32_EV           : 1;
  __REG32  GPORT_EV           : 1;
  __REG32  GPIPE_EV           : 1;
  __REG32  HCHA_EV            : 1;
  __REG32  BWERR_EV           : 1;
  __REG32                     :26;
} __usb_main_ev_bits;

/* USB_MAIN_EM – USB Main Event Mask Register */
typedef struct {
  __REG32  FRM_EM             : 1;
  __REG32  FRM32_EM           : 1;
  __REG32  GPORT_EM           : 1;
  __REG32  GPIPE_EM           : 1;
  __REG32  HCHA_EM            : 1;
  __REG32  BWERR_EM           : 1;
  __REG32                     :26;
} __usb_main_em_bits;

/* USB_PIPE_EV – USB Pipe Event Register */
typedef struct {
  __REG32  PI_EV0             : 1;
  __REG32  PI_EV1             : 1;
  __REG32  PI_EV2             : 1;
  __REG32  PI_EV3             : 1;
  __REG32  PI_EV4             : 1;
  __REG32  PI_EV5             : 1;
  __REG32  PI_EV6             : 1;
  __REG32  PI_EV7             : 1;
  __REG32                     :24;
} __usb_pipe_ev_bits;

/* USB_PIPE_EM – USB Pipe Event Mask Register */
typedef struct {
  __REG32  PI_EM0             : 1;
  __REG32  PI_EM1             : 1;
  __REG32  PI_EM2             : 1;
  __REG32  PI_EM3             : 1;
  __REG32  PI_EM4             : 1;
  __REG32  PI_EM5             : 1;
  __REG32  PI_EM6             : 1;
  __REG32  PI_EM7             : 1;
  __REG32                     :24;
} __usb_pipe_em_bits;

/* USB_PIPE_SEL – USB Pipe Select Register */
typedef struct {
  __REG32  PI_SEL             : 3;
  __REG32                     :29;
} __usb_pipe_sel_bits;

/* USB_PORT_STAT – USB Port Status Register */
typedef struct {
  __REG32  VBUS_VLD           : 1;
  __REG32  VA_SESS_VLD        : 1;
  __REG32  VB_SESS_VLD        : 1;
  __REG32  VB_SESS_END        : 1;
  __REG32  CONN_ID            : 1;
  __REG32  PCS                : 1;
  __REG32  DLS                : 1;
  __REG32  OCURC              : 1;
  __REG32  LINESTATE          : 2;
  __REG32                     :22;
} __usb_port_stat_bits;

/* USB_PORT_CTRL – USB Port Control Register */
typedef struct {
  __REG32  PTESTC             : 2;
  __REG32  URESET             : 1;
  __REG32  FPRESU             : 1;
  __REG32  PENA               : 1;
  __REG32  PSUSP              : 1;
  __REG32  VB_ON              : 1;
  __REG32  TERM_SEL           : 1;
  __REG32  TERM_ENA           : 1;
  __REG32  DCHRG              : 1;
  __REG32  VBS_ON             : 1;
  __REG32                     : 1;
  __REG32  ID_PU              : 1;
  __REG32                     : 3;
  __REG32  P_LEN              : 8;
  __REG32                     : 8;
} __usb_port_ctrl_bits;

/* USB_PSC_EV – USB Port Status Change Event Register */
typedef struct {
  __REG32  OCU_EV             : 1;
  __REG32  BERR_EV            : 1;
  __REG32  RSU_EV             : 1;
  __REG32  RSUC_EV            : 1;
  __REG32  SUSP_EV            : 1;
  __REG32  URES_EV            : 1;
  __REG32  CDC_EV             : 1;
  __REG32  PWRSC_EV           : 1;
  __REG32  P_END_EV           : 1;
  __REG32                     :23;
} __usb_psc_ev_bits;

/* USB_PSC_EM – USB Port Status Change Event Mask Register */
typedef struct {
  __REG32  OCU_EM             : 1;
  __REG32  BERR_EM            : 1;
  __REG32  RSU_EM             : 1;
  __REG32  RSUC_EM            : 1;
  __REG32  SUSP_EM            : 1;
  __REG32  URES_EM            : 1;
  __REG32  CDC_EM             : 1;
  __REG32  PWRSC_EM           : 1;
  __REG32  P_END_EM           : 1;
  __REG32                     :23;
} __usb_psc_em_bits;

/* USB_PIPE_CTRL – USB Pipe Control Register */
typedef struct {
  __REG32  TPID               : 2;
  __REG32  ACT                : 1;
  __REG32                     :29;
} __usb_pipe_ctrl_bits;

/* USB_PIPE_CFG – USB Pipe Configuration Register */
typedef struct {
  __REG32  MPS                :10;
  __REG32  ET                 : 2;
  __REG32  STRM               : 1;
  __REG32  EPS                : 1;
  __REG32  ACID               : 1;
  __REG32  STALL              : 1;
  __REG32  POFF               : 8;
  __REG32  PI                 : 4;
  __REG32  SKIPISO            : 1;
  __REG32  HIDBE              : 1;
  __REG32  IOT                : 1;
  __REG32                     : 1;
} __usb_pipe_cfg_bits;

/* USB_PIPE_ADDR – USB Pipe Address Register */
typedef struct {
  __REG32  ERNR               : 4;
  __REG32  EPADDR             : 7;
  __REG32                     :21;
} __usb_pipe_addr_bits;

/* USB_PIPE_STAT – USB Pipe Status Register */
typedef struct {
  __REG32  DBOFF              : 2;
  __REG32  DT                 : 1;
  __REG32  DBSEL              : 1;
  __REG32  BBL                : 1;
  __REG32  HALT               : 1;
  __REG32  ACTS               : 1;
  __REG32  DBERR              : 1;
  __REG32  CERR               : 2;
  __REG32                     :22;
} __usb_pipe_stat_bits;

/* USB_PIPE_DATA_PTR – USB Pipe Data Pointer Register */
typedef struct {
  __REG32  DPTR               :10;
  __REG32                     :22;
} __usb_pipe_data_ptr_bits;

/* USB_PIPE_DATA_TBYTES – USB Pipe Total Bytes Register */
typedef struct {
  __REG32  TBYTES             :13;
  __REG32                     :18;
  __REG32  DBV                : 1;
} __usb_pipe_data_tbytes_bits;

/* USB_PIPE_ADATA_PTR – USB Pipe Alternative Data Pointer Register */
typedef struct {
  __REG32  ADPTR              :10;
  __REG32                     :22;
} __usb_pipe_adata_ptr_bits;

/* USB_PIPE_ADATA_TBYTES – USB Pipe Alternative Data Total Bytes Register */
typedef struct {
  __REG32  TBYTES             :11;
  __REG32                     :20;
  __REG32  ADBV               : 1;
} __usb_pipe_adata_tbytes_bits;

/* USB_DEBUG_CTRL – USB Debug Control Register */
typedef struct {
  __REG32  DBSERRDET          : 1;
  __REG32  DBSTX              : 1;
  __REG32  FTXCRC5E           : 1;
  __REG32  FTXCRC16E          : 1;
  __REG32  FRXCRCE            : 1;
  __REG32  FRXCRC5G           : 1;
  __REG32  FRXCRC16G          : 1;
  __REG32  UDDPID             : 1;
  __REG32  UDHSPID            : 1;
  __REG32  UDTPID             : 1;
  __REG32                     :22;
} __usb_debug_ctrl_bits;

/* USB_DEBUG_PID – USB Debug PID Register */
typedef struct {
  __REG32  DDPID              : 8;
  __REG32  DTPID              : 8;
  __REG32  DHSPID             : 8;
  __REG32                     : 8;
} __usb_debug_pid_bits;

/* USB_DEBUG_STAT – USB Debug Status Register */
typedef struct {
  __REG32  DRXPIP             : 8;
  __REG32                     :24;
} __usb_debug_stat_bits;

/* USB_MAIN_CFG – USB Main Configuration Register */
typedef struct {
  __REG32  NOP_CFG            : 6;
  __REG32  DW_CFG             : 6;
  __REG32                     :12;
  __REG32  RAW_CFG            : 6;
  __REG32                     : 2;
} __usb_main_cfg_bits;

/* USB_MODE_CFG – USB Mode Configuration Register */
typedef struct {
  __REG32  ABUFF_CFG          : 8;
  __REG32                     : 8;
  __REG32  DBG_CFG            : 1;
  __REG32  XDBG_CFG           : 1;
  __REG32                     :14;
} __usb_mode_cfg_bits;

/* USB_CORE_CTRL – USB Core Control and Status Register */
typedef struct {
  __REG32  RESET              : 1;
  __REG32  DBG_SUPPORT        : 1;
  __REG32  XTD_DBG_SUPPORT    : 1;
  __REG32  SOFT_ID_DIG        : 1;
  __REG32  ALT_BUFF_SUPPORT   : 8;
  __REG32  CORE_SUSPEND_N     : 1;
  __REG32  XCVR_SUSPEND_N     : 1;
  __REG32  OVER_CURRENT       : 1;
  __REG32  VA_SESS_VLD        : 1;
  __REG32  VB_SESS_END        : 1;
  __REG32  VB_SESS_VLD        : 1;
  __REG32  VBUS_VLD           : 1;
  __REG32  CHRG_VBUS          : 1;
  __REG32  DLP_ACTIVE         : 1;
  __REG32  VB_ON              : 1;
  __REG32  DISCHRG_VBUS       : 1;
  __REG32  UCIF_RDY           : 1;
  __REG32  USB_IRQ            : 1;
  __REG32                     : 7;
} __usb_core_ctrl_bits;

/* VIC_IRQ_STATUS – VIC IRQ Status Register
   VIC_FIQ_STATUS – VIC FIQ Status Register
   VIC_RAW_INTR – VIC Raw Interrupt Status Register
   VIC_INT_SELECT – VIC Interrupt Select Register
   VIC_INT_ENABLE – VIC Interrupt Enable Register
   VIC_INT_ENCLEAR – VIC Interrupt Enable Clear Register
   VIC_SOFTINT – VIC Software Interrupt Register
   VIC_SOFTINT_CLEAR – VIC Software Interrupt Clear Register */
typedef struct {
  __REG32  SW                 : 1;
  __REG32  TIMER0             : 1;
  __REG32  TIMER1             : 1;
  __REG32  TIMER2             : 1;
  __REG32  SYSTIME_NS         : 1;
  __REG32  SYSTIME_S          : 1;
  __REG32  GPIO15             : 1;
  __REG32  WATCHDOG           : 1;
  __REG32  UART0              : 1;
  __REG32  UART1              : 1;
  __REG32  UART2              : 1;
  __REG32  USB                : 1;
  __REG32  SPI                : 1;
  __REG32  I2C                : 1;
  __REG32  LCD                : 1;
  __REG32  HIF                : 1;
  __REG32  GPIO               : 1;
  __REG32  COM0               : 1;
  __REG32  COM1               : 1;
  __REG32  COM2               : 1;
  __REG32  COM3               : 1;
  __REG32  MSYNC0             : 1;
  __REG32  MSYNC1             : 1;
  __REG32  MSYNC2             : 1;
  __REG32  MSYNC3             : 1;
  __REG32  INT_PHY            : 1;
  __REG32  ISO_AREA           : 1;
  __REG32                     : 2;
  __REG32  TIMER3             : 1;
  __REG32  TIMER4             : 1;
  __REG32                     : 1;
} __vic_channels_bits;

/* VIC_PROTECTION – VIC Protection Enable Register */
typedef struct {
  __REG32  PROTECTION         : 1;
  __REG32                     :31;
} __vic_protection_bits;

/* VIC_VECT_CNTLn – VIC Vector Control Registers n */
typedef struct {
  __REG32  INT_SOURCE         : 5;
  __REG32  ENABLE             : 1;
  __REG32                     :26;
} __vic_vect_cntl_bits;

/* PWMn_CONFIG – PWM n Configuration Register */
typedef struct {
  __REG32  VAL_U              : 1;
  __REG32  VAL_UN             : 1;
  __REG32  VAL_V              : 1;
  __REG32  VAL_VN             : 1;
  __REG32  VAL_W              : 1;
  __REG32  VAL_WN             : 1;
  __REG32  FO_MODE            : 1;
  __REG32  PWM_MODE           : 1;
  __REG32  AUTO_U             : 1;
  __REG32  AUTO_V             : 1;
  __REG32  AUTO_W             : 1;
  __REG32                     : 3;
  __REG32  RUN_MP             : 1;
  __REG32  RUN_RP             : 1;
  __REG32                     :16;
} __pwm_config_bits;

/* PWMn_STATUS – PWM n Status Register */
typedef struct {
  __REG32  SYSTC              : 1;
  __REG32                     : 5;
  __REG32  PWMERR             : 1;
  __REG32  PWMERR_REG         : 1;
  __REG32  SYSTIME_REG        : 1;
  __REG32                     :23;
} __pwm_status_bits;

/* PWMn_TP - PWM n Period */
typedef struct {
  __REG32  TP                 :16;
  __REG32                     :16;
} __pwm_tp_bits;

/* PWMn_TU – PWM n Channel U Low Phase Width */
typedef struct {
  __REG32  LEVEL_U            :16;
  __REG32                     :16;
} __pwm_tu_bits;

/* PWMn_TV – PWM n Channel V Low Phase Width */
typedef struct {
  __REG32  LEVEL_V            :16;
  __REG32                     :16;
} __pwm_tv_bits;

/* PWM_TW – PWM n Channel W Low Phase Width */
typedef struct {
  __REG32  LEVEL_W            :16;
  __REG32                     :16;
} __pwm_tw_bits;

/* PWMn_TD – PWM n Dead Time Counter Preload */
typedef struct {
  __REG32  PRELOAD_D          :16;
  __REG32                     :16;
} __pwm_td_bits;

/* PWMn_CNT – Actual Counter Motor PWM n Period */
typedef struct {
  __REG32  PWM_CNT            :16;
  __REG32                     :16;
} __pwm_cnt_bits;

/* PWMn_STRTIME – Captured System Time at Start Point of Motor PWM n Period */
typedef struct {
  __REG32  PWM_STRTIME        :16;
  __REG32                     :16;
} __pwm_strtime_bits;

/* RPWMn_TP – Resolver PWM n Period */
typedef struct {
  __REG32  RES_TP             :16;
  __REG32                     :16;
} __rpwm_tp_bits;

/* RPWMn_TR – Resolver PWM n Pulse */
typedef struct {
  __REG32  RES_TR             :16;
  __REG32                     :16;
} __rpwm_tr_bits;

/* RPWMn_CNT – Actual Counter Resolver PWM n Period */
typedef struct {
  __REG32  RPWM_CNT           :16;
  __REG32                     :16;
} __rpwm_cnt_bits;

/* RPWMn_STRTIME – Captured System time at Start Point of Resolver PWM n Period */
typedef struct {
  __REG32  RPWM_STRTIME       :16;
  __REG32                     :16;
} __rpwm_strtime_bits;

/* ENC_STATUS – Encoder Position and Capture Status */
typedef struct {
  __REG32  ENC0_OVFL_POS      : 1;
  __REG32  ENC0_OVFL_NEG      : 1;
  __REG32  ENC0_CAP_ZPOS      : 1;
  __REG32  ENC0_CAP_ETIME     : 1;
  __REG32  ENC1_OVFL_POS      : 1;
  __REG32  ENC1_OVFL_NEG      : 1;
  __REG32  ENC1_CAP_ZPOS      : 1;
  __REG32  ENC1_CAP_ETIME     : 1;
  __REG32  CAP0               : 1;
  __REG32  CAP1               : 1;
  __REG32  CAP2               : 1;
  __REG32  CAP3               : 1;
  __REG32  ENC0_SIGN          : 1;
  __REG32  ENC1_SIGN          : 1;
  __REG32  MP0                : 1;
  __REG32  MP1                : 1;
  __REG32                     :16;
} __enc_status_bits;

/* ENC_CONFIG_ENCODER – Encoder Configuration Register */
typedef struct {
  __REG32  ENC0_FILTER_SR     : 3;
  __REG32  ENC0_COUNT_DIR     : 1;
  __REG32  ENC0_N_QUALIFIER   : 2;
  __REG32                     : 2;
  __REG32  ENC1_FILTER_SR     : 3;
  __REG32  ENC1_COUNT_DIR     : 1;
  __REG32  ENC1_N_QUALIFIER   : 2;
  __REG32                     :18;
} __enc_config_encoder_bits;

/* ENC_COMMAND – Encoder Command Register */
typedef struct {
  __REG32  ENC0_EN            : 1;
  __REG32  ENC0_RES_POS       : 1;
  __REG32  ENC0_RES_ZPOS      : 1;
  __REG32                     : 5;
  __REG32  ENC1_EN            : 1;
  __REG32  ENC1_RES_POS       : 1;
  __REG32  ENC1_RES_ZPOS      : 1;
  __REG32                     :21;
} __enc_command_bits;

/* ENCn_POSITION - Actual Position Encoder n */
typedef struct {
  __REG32  POSITION           :16;
  __REG32                     :16;
} __enc_position_bits;

/* ENCn_NULLPOSITION - Sampled Null Position Encoder n */
typedef struct {
  __REG32  NULLPOSITION       :16;
  __REG32                     :16;
} __enc_nullposition_bits;

/* ENCn_EDGETIME - System Time at Last Edge of Encoder n */
typedef struct {
  __REG32  EDGETIME           :16;
  __REG32                     :16;
} __enc_edgetime_bits;

/* ENC_CONFIG_CAPTURE – Encoder Capture Configuration Register */
typedef struct {
  __REG32  CREG0_CW           : 2;
  __REG32  CREG0_SRC          : 2;
  __REG32  CREG1_CW           : 2;
  __REG32  CREG1_SRC          : 2;
  __REG32  CREG2_CW           : 2;
  __REG32  CREG2_SRC          : 2;
  __REG32  CREG3_CW           : 2;
  __REG32  CREG3_SRC          : 2;
  __REG32                     :16;
} __enc_config_capture_bits;

/* ENC_CAPTUREn – Encoder Capture Register n */
typedef struct {
  __REG32  ENC_CAPTURE        :16;
  __REG32                     :16;
} __enc_capture_bits;

/* ADC – Analogue Digital Converter */
typedef union {
  // ADCx
  struct {
  __REG32  ADC0_D             :10;
  __REG32  ADC0_BUSY          : 1;
  __REG32                     : 5;
  __REG32  ADC1_D             :10;
  __REG32  ADC1_BUSY          : 1;
  __REG32                     : 5;
  };  
  // Write access
  struct {
  __REG32  ADC0_PDB           : 1;
  __REG32  ADC0_START         : 1;
  __REG32  ADC0_SEL           : 3;
  __REG32                     :10;
  __REG32  DONT_WRITE_ADC0    : 1;
  __REG32  ADC1_PDB           : 1;
  __REG32  ADC1_START         : 1;
  __REG32  ADC1_SEL           : 3;
  __REG32                     :10;
  __REG32  DONT_WRITE_ADC1    : 1;
  };
} __adc_bits;

/* PHY_CR - PHY Control Register */
typedef struct {
  __REG32  PHY_ADDRESS        : 4;
  __REG32  PHY0_MODE          : 3;
  __REG32  PHY0_FIXMODE       : 1;
  __REG32  PHY0_AUTOMIX       : 1;
  __REG32  PHY0_NP_MSG_CODE   : 3;
  __REG32  PHY0_ENABLE        : 1;
  __REG32  PHY1_MODE          : 3;
  __REG32  PHY1_FIXMODE       : 1;
  __REG32  PHY1_AUTOMDIX      : 1;
  __REG32  PHY1_NP_MSG_CODE   : 3;
  __REG32  PHY1_ENABLE        : 1;
  __REG32                     : 7;
  __REG32  PHY_CLK_XLATIN     : 1;
  __REG32  PHY_SIM_BYP        : 1;
  __REG32  PHY_RESET          : 1;
} __phy_cr_bits;

/* PFIFO_FILL_LEVEL_BASE0-31 – Pointer FIFO Fill Level 0-31 */
typedef struct {
  __REG32  FILL_LEVEL         :11;
  __REG32                     :21;
} __pfifo_fill_level_base_bits;

/* CRC_DATA – CRC Input Data register */
typedef struct {
  __REG32  CRC_INPUT          : 8;
  __REG32                     :24;
} __crc_data_bits;

/* CRC_CONFIG – CRC Configuration Register */
typedef struct {
  __REG32 CRC_LEN             : 6;
  __REG32 CRC_SHIFT_DIV       : 1;
  __REG32 CRC_DIRECT_DIV      : 1;
  __REG32 CRC_NOF_BITS        : 2;
  __REG32 CRC_IN_MSB_LOW      : 1;
  __REG32                     :21;
} __crc_config_bits;

/* IRQ_XPECn – IRQs between XPEC0 and ARM Registers */
typedef struct {
  __REG32 XPEC_IRQ            :16;
  __REG32 ARM_IRQ             :16;
} __irq_xpec_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/
/***************************************************************************
 **
 **  System Functions
 **
 ***************************************************************************/
__IO_REG32_BIT(BOO_SR,                0x00100000,__READ       ,__boo_sr_bits);
__IO_REG32_BIT(IOC_CR,                0x00100004,__READ_WRITE ,__ioc_cr_bits);
__IO_REG32_BIT(IOC_MR,                0x00100008,__READ_WRITE ,__ioc_cr_bits);
__IO_REG32_BIT(RES_CR,                0x0010000C,__READ_WRITE ,__res_cr_bits);
__IO_REG32(    _REV,                   0x00100034,__READ       );
__IO_REG32_BIT(IOC_ACCESS_KEY,        0x00100070,__READ_WRITE ,__ioc_access_key_bits);
__IO_REG32_BIT(WDG_TR,                0x00100200,__READ_WRITE ,__wdg_tr_bits);
__IO_REG32_BIT(WDG_CTR,               0x00100204,__READ       ,__wdg_ctr_bits);
__IO_REG32_BIT(WDG_IRQ_TIMEOUT,       0x00100208,__READ_WRITE ,__wdg_irq_timeout_bits);
__IO_REG32_BIT(WDG_RES_TIMEOUT,       0x0010020C,__READ_WRITE ,__wdg_res_timeout_bits);
__IO_REG32_BIT(SYS_STA,               0x001034D8,__READ_WRITE ,__sys_sta_bits);

/***************************************************************************
 **
 **  MEM
 **
 ***************************************************************************/
__IO_REG32_BIT(MEMSR0_CR,             0x00100100,__READ_WRITE ,__memsr_cr_bits);
__IO_REG32_BIT(MEMSR1_CR,             0x00100104,__READ_WRITE ,__memsr_cr_bits);
__IO_REG32_BIT(MEMSR2_CR,             0x00100108,__READ_WRITE ,__memsr_cr_bits);
__IO_REG32_BIT(MEMDR_CONFIG_CR,       0x00100140,__READ_WRITE ,__memdr_config_cr_bits);
__IO_REG32_BIT(MEMDR_TIMING_CR,       0x00100144,__READ_WRITE ,__memdr_timing_cr_bits);
__IO_REG32_BIT(MEMDR_MR,              0x00100148,__READ_WRITE ,__memdr_mr_bits);
__IO_REG32_BIT(MEMDR_EMR,             0x0010014C,__READ       ,__memdr_emr_bits);
__IO_REG32_BIT(MEMPRIO_TIMESLOT_CR,   0x00100180,__READ       ,__memprio_timeslot_cr_bits);
__IO_REG32_BIT(MEMPRIO_ACCESS_CR,     0x00100184,__READ_WRITE ,__memprio_access_cr_bits);

/***************************************************************************
 **
 **  EXT
 **
 ***************************************************************************/
__IO_REG32_BIT(EXT_CONFIG_CS0,        0x00103610,__READ_WRITE ,__ext_config_cs_bits);
__IO_REG32_BIT(EXT_CONFIG_CS1,        0x00103614,__READ_WRITE ,__ext_config_cs_bits);
__IO_REG32_BIT(EXT_CONFIG_CS2,        0x00103618,__READ_WRITE ,__ext_config_cs_bits);
__IO_REG32_BIT(EXT_CONFIG_CS3,        0x0010361C,__READ_WRITE ,__ext_config_cs_bits);

/***************************************************************************
 **
 **  DPMAS
 **
 ***************************************************************************/
__IO_REG32_BIT(DPMAS_HSCR0,           0x00103680,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR1,           0x00103684,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR2,           0x00103688,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR3,           0x0010368C,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR4,           0x00103690,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR5,           0x00103694,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR6,           0x00103698,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR7,           0x0010369C,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR8,           0x001036A0,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR9,           0x001036A4,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR10,          0x001036A8,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR11,          0x001036AC,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR12,          0x001036B0,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR13,          0x001036B4,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR14,          0x001036B8,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_HSCR15,          0x001036BC,__READ_WRITE ,__dpmas_hscr_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING7,     0x0010367C,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END7,         0x00103678,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING6,     0x00103674,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END6,         0x00103670,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING5,     0x0010366C,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END5,         0x00103668,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING4,     0x00103664,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END4,         0x00103660,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING3,     0x0010365C,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END3,         0x00103658,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING2,     0x00103654,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END2,         0x00103650,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING1,     0x0010364C,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END1,         0x00103648,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_DB_MAPPING0,     0x00103644,__READ_WRITE ,__dpmas_db_mapping_bits);
__IO_REG32_BIT(DPMAS_DB_END0,         0x00103640,__READ_WRITE ,__dpmas_db_end_bits);
__IO_REG32_BIT(DPMAS_IO_DATA1,        0x00103638,__READ_WRITE ,__dpmas_io_data1_bits);
__IO_REG32_BIT(DPMAS_IO_DRV_EN1,      0x00103634,__READ_WRITE ,__dpmas_io_drv_en1_bits);
__IO_REG32_BIT(DPMAS_IO_MODE1,        0x00103630,__READ_WRITE ,__dpmas_io_mode1_bits);
__IO_REG32_BIT(DPMAS_IO_DATA0,        0x00103628,__READ_WRITE ,__dpmas_io_data0_bits);
__IO_REG32_BIT(DPMAS_IO_DRV_EN0,      0x00103624,__READ_WRITE ,__dpmas_io_drv_en0_bits);
__IO_REG32_BIT(DPMAS_IO_MODE0,        0x00103620,__READ_WRITE ,__dpmas_io_mode0_bits);
#define DPMAS_EXT_CONFIG0     EXT_CONFIG_CS0
#define DPMAS_EXT_CONFIG0_bit EXT_CONFIG_CS0_bit
#define DPMAS_EXT_CONFIG1     EXT_CONFIG_CS1
#define DPMAS_EXT_CONFIG1_bit EXT_CONFIG_CS1_bit
#define DPMAS_EXT_CONFIG2     EXT_CONFIG_CS2
#define DPMAS_EXT_CONFIG2_bit EXT_CONFIG_CS2_bit
#define DPMAS_EXT_CONFIG3     EXT_CONFIG_CS3
#define DPMAS_EXT_CONFIG3_bit EXT_CONFIG_CS3_bit
__IO_REG32_BIT(DPMAS_IF_CONF1,        0x0010360C,__READ_WRITE ,__dpmas_if_conf1_bits);
__IO_REG32_BIT(DPMAS_IF_CONF0,        0x00103608,__READ_WRITE ,__dpmas_if_conf0_bits);
__IO_REG32_BIT(DPMAS_CLKOUT_CONF,     0x00103604,__READ_WRITE ,__dpmas_clkout_conf_bits);
__IO_REG32_BIT(DPMAS_HS_DATA0,        0x00103500,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA1,        0x00103504,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA2,        0x00103508,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA3,        0x0010350C,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA4,        0x00103510,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA5,        0x00103514,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA6,        0x00103518,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA7,        0x0010351C,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA8,        0x00103520,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA9,        0x00103524,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA10,       0x00103528,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA11,       0x0010352C,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA12,       0x00103530,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA13,       0x00103534,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA14,       0x00103538,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_HS_DATA15,       0x0010353C,__READ_WRITE ,__dpmas_hs_data_bits);
__IO_REG32_BIT(DPMAS_INT_EN1,         0x001034F0,__READ_WRITE ,__dpmas_int_en1_bits);
__IO_REG32_BIT(DPMAS_INT_STA1,        0x001034E0,__READ_WRITE ,__dpmas_int_sta1_bits);
#define DPMAS_SYS_STA       SYS_STA
#define DPMAS_SYS_STA_bit   SYS_STA_bit
__IO_REG32_BIT(DPMAS_WDG_ARM_TRIG,    0x001034CC,__READ_WRITE ,__dpmas_wdg_arm_trig_bits);
__IO_REG32_BIT(DPMAS_WDG_ARM_TIMEOUT, 0x001034C8,__READ       ,__dpmas_wdg_arm_timeout_bits);
__IO_REG32_BIT(DPMAS_WDG_HOST_TIMEOUT,0x001034C0,__READ_WRITE ,__dpmas_wdg_arm_timeout_bits);
__IO_REG32_BIT(DPMAS_CIS_MAPPING,     0x001034BC,__READ_WRITE ,__dpmas_cis_mapping_bits);
__IO_REG32_BIT(DPMHS_HS_DATA0,        0x00103200,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA1,        0x00103204,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA2,        0x00103208,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA3,        0x0010320C,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA4,        0x00103210,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA5,        0x00103214,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA6,        0x00103218,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA7,        0x0010321C,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA8,        0x00103220,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA9,        0x00103224,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA10,       0x00103228,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA11,       0x0010322C,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA12,       0x00103230,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA13,       0x00103234,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA14,       0x00103238,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_HS_DATA15,       0x0010323C,__READ_WRITE ,__dpmhs_hs_data_bits);
__IO_REG32_BIT(DPMHS_INT_EN0,         0x001031F0,__READ_WRITE ,__dpmhs_int_en0_bits);
__IO_REG32_BIT(DPMHS_INT_STA0,        0x001031e0,__READ_WRITE ,__dpmhs_int_sta0_bits);
__IO_REG32_BIT(DPMHS_RES_REQ,         0x001031DC,__READ_WRITE ,__dpmhs_res_req_bits);
__IO_REG32_BIT(DPMHS_SYS_STA,         0x001031D8,__READ_WRITE ,__dpmhs_sys_sta_bits);
__IO_REG32_BIT(DPMHS_TMR_START_VALUE, 0x001031D4,__READ_WRITE ,__dpmhs_tmr_start_value_bits);
__IO_REG32_BIT(DPMHS_TMR_CTRL,        0x001031D0,__READ_WRITE ,__dpmhs_tmr_ctrl_bits);
__IO_REG32_BIT(DPMHS_WDG_ARM_TIMEOUT, 0x001031C8,__READ_WRITE ,__dpmhs_wdg_arm_timeout_bits);
__IO_REG32_BIT(DPMHS_WDG_HOST_TRIG,   0x001031C4,__READ_WRITE ,__dpmhs_wdg_host_trig_bits);
__IO_REG32_BIT(DPMHS_WDG_HOST_TIMEOUT,0x001031C0,__READ       ,__dpmhs_wdg_host_timeout_bits);

/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(GPIO_CFG0,             0x00100800,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG1,             0x00100804,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG2,             0x00100808,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG3,             0x0010080C,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG4,             0x00100810,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG5,             0x00100814,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG6,             0x00100818,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG7,             0x0010081C,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG8,             0x00100820,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG9,             0x00100824,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG10,            0x00100828,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG11,            0x0010082C,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG12,            0x00100830,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG13,            0x00100834,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG14,            0x00100838,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32_BIT(GPIO_CFG15,            0x0010083C,__READ_WRITE ,__gpio_cfg_bits);
__IO_REG32(    GPIO_TC0,              0x00100840,__READ_WRITE );
__IO_REG32(    GPIO_TC1,              0x00100844,__READ_WRITE );
__IO_REG32(    GPIO_TC2,              0x00100848,__READ_WRITE );
__IO_REG32(    GPIO_TC3,              0x0010084C,__READ_WRITE );
__IO_REG32(    GPIO_TC4,              0x00100850,__READ_WRITE );
__IO_REG32(    GPIO_TC5,              0x00100854,__READ_WRITE );
__IO_REG32(    GPIO_TC6,              0x00100858,__READ_WRITE );
__IO_REG32(    GPIO_TC7,              0x0010085C,__READ_WRITE );
__IO_REG32(    GPIO_TC8,              0x00100860,__READ_WRITE );
__IO_REG32(    GPIO_TC9,              0x00100864,__READ_WRITE );
__IO_REG32(    GPIO_TC10,             0x00100868,__READ_WRITE );
__IO_REG32(    GPIO_TC11,             0x0010086C,__READ_WRITE );
__IO_REG32(    GPIO_TC12,             0x00100870,__READ_WRITE );
__IO_REG32(    GPIO_TC13,             0x00100874,__READ_WRITE );
__IO_REG32(    GPIO_TC14,             0x00100878,__READ_WRITE );
__IO_REG32(    GPIO_TC15,             0x0010087C,__READ_WRITE );
__IO_REG32_BIT(GPIO_COUNTER0_CTRL,    0x00100880,__READ_WRITE ,__gpio_counter_ctrl_bits);
__IO_REG32_BIT(GPIO_COUNTER1_CTRL,    0x00100884,__READ_WRITE ,__gpio_counter_ctrl_bits);
__IO_REG32_BIT(GPIO_COUNTER2_CTRL,    0x00100888,__READ_WRITE ,__gpio_counter_ctrl_bits);
__IO_REG32_BIT(GPIO_COUNTER3_CTRL,    0x0010088C,__READ_WRITE ,__gpio_counter_ctrl_bits);
__IO_REG32_BIT(GPIO_COUNTER4_CTRL,    0x00100890,__READ_WRITE ,__gpio_counter_ctrl_bits);
__IO_REG32(    GPIO_COUNTER0_MAX,     0x00100894,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER1_MAX,     0x00100898,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER2_MAX,     0x0010089C,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER3_MAX,     0x001008A0,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER4_MAX,     0x001008A4,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER0_CNT,     0x001008A8,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER1_CNT,     0x001008AC,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER2_CNT,     0x001008B0,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER3_CNT,     0x001008B4,__READ_WRITE );
__IO_REG32(    GPIO_COUNTER4_CNT,     0x001008B8,__READ_WRITE );
__IO_REG32_BIT(GPIO_IRQ_MASK_SET,     0x001008BC,__READ_WRITE ,__gpio_irq_mask_set_bits);
__IO_REG32_BIT(GPIO_IRQ_MASK_RST,     0x001008C0,__READ_WRITE ,__gpio_irq_mask_set_bits);
__IO_REG32(    GPIO_SYSTIME_NS_CMP,   0x001008C4,__READ_WRITE );
__IO_REG32_BIT(GPIO_LINE,             0x001008C8,__READ_WRITE ,__gpio_line_bits);
__IO_REG32_BIT(GPIO_IRQ,              0x001008D0,__READ_WRITE ,__gpio_irq_mask_set_bits);

/***************************************************************************
 **
 **  PIO
 **
 ***************************************************************************/
__IO_REG32_BIT(PIO_IN,                0x00100900,__READ       ,__pio_in_bits);
__IO_REG32_BIT(PIO_OUT,               0x00100904,__READ_WRITE ,__pio_in_bits);
__IO_REG32_BIT(PIO_OE,                0x00100908,__READ_WRITE ,__pio_in_bits);

/***************************************************************************
 **
 **  UART0
 **
 ***************************************************************************/
__IO_REG32_BIT(UART0_DR,              0x00100A00,__READ_WRITE ,__uart_dr_bits);
__IO_REG32_BIT(UART0_SR,              0x00100A04,__READ_WRITE ,__uart_sr_bits);
__IO_REG32_BIT(UART0_LINE_CR,         0x00100A08,__READ_WRITE ,__uart_line_cr_bits);
__IO_REG32_BIT(UART0_BAUDDIV_MSB,     0x00100A0C,__READ_WRITE ,__uart_bauddiv_msb_bits);
__IO_REG32_BIT(UART0_BAUDDIV_LSB,     0x00100A10,__READ_WRITE ,__uart_bauddiv_lsb_bits);
__IO_REG32_BIT(UART0_CR,              0x00100A14,__READ_WRITE ,__uart_cr_bits);
__IO_REG32_BIT(UART0_FR,              0x00100A18,__READ       ,__uart_fr_bits);
__IO_REG32_BIT(UART0_IIR,             0x00100A1C,__READ_WRITE ,__uart_iir_bits);
__IO_REG32_BIT(UART0_ILPR,            0x00100A20,__READ_WRITE ,__uart_ilpr_bits);
__IO_REG32_BIT(UART0_RTS_CR,          0x00100A24,__READ_WRITE ,__uart_rts_cr_bits);
__IO_REG32_BIT(UART0_RTS_LEAD,        0x00100A28,__READ_WRITE ,__uart_rts_lead_bits);
__IO_REG32_BIT(UART0_RTS_TRAIL,       0x00100A2C,__READ_WRITE ,__uart_rts_trail_bits);
__IO_REG32_BIT(UART0_DRV_ENABLE,      0x00100A30,__READ_WRITE ,__uart_drv_enable_bits);
__IO_REG32_BIT(UART0_BRM_CR,          0x00100A34,__READ_WRITE ,__uart_brm_cr_bits);
__IO_REG32_BIT(UART0_RXFIFO_IRQLEVEL, 0x00100A38,__READ_WRITE ,__uart_rxfifo_irqlevel_bits);
__IO_REG32_BIT(UART0_TXFIFO_IRQLEVEL, 0x00100A3C,__READ_WRITE ,__uart_txfifo_irqlevel_bits);

/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG32_BIT(UART1_DR,              0x00100A40,__READ_WRITE ,__uart_dr_bits);
__IO_REG32_BIT(UART1_SR,              0x00100A44,__READ_WRITE ,__uart_sr_bits);
__IO_REG32_BIT(UART1_LINE_CR,         0x00100A48,__READ_WRITE ,__uart_line_cr_bits);
__IO_REG32_BIT(UART1_BAUDDIV_MSB,     0x00100A4C,__READ_WRITE ,__uart_bauddiv_msb_bits);
__IO_REG32_BIT(UART1_BAUDDIV_LSB,     0x00100A50,__READ_WRITE ,__uart_bauddiv_lsb_bits);
__IO_REG32_BIT(UART1_CR,              0x00100A54,__READ_WRITE ,__uart_cr_bits);
__IO_REG32_BIT(UART1_FR,              0x00100A58,__READ       ,__uart_fr_bits);
__IO_REG32_BIT(UART1_IIR,             0x00100A5C,__READ_WRITE ,__uart_iir_bits);
__IO_REG32_BIT(UART1_ILPR,            0x00100A60,__READ_WRITE ,__uart_ilpr_bits);
__IO_REG32_BIT(UART1_RTS_CR,          0x00100A64,__READ_WRITE ,__uart_rts_cr_bits);
__IO_REG32_BIT(UART1_RTS_LEAD,        0x00100A68,__READ_WRITE ,__uart_rts_lead_bits);
__IO_REG32_BIT(UART1_RTS_TRAIL,       0x00100A6C,__READ_WRITE ,__uart_rts_trail_bits);
__IO_REG32_BIT(UART1_DRV_ENABLE,      0x00100A70,__READ_WRITE ,__uart_drv_enable_bits);
__IO_REG32_BIT(UART1_BRM_CR,          0x00100A74,__READ_WRITE ,__uart_brm_cr_bits);
__IO_REG32_BIT(UART1_RXFIFO_IRQLEVEL, 0x00100A78,__READ_WRITE ,__uart_rxfifo_irqlevel_bits);
__IO_REG32_BIT(UART1_TXFIFO_IRQLEVEL, 0x00100A7C,__READ_WRITE ,__uart_txfifo_irqlevel_bits);

/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG32_BIT(UART2_DR,              0x00100A80,__READ_WRITE ,__uart_dr_bits);
__IO_REG32_BIT(UART2_SR,              0x00100A84,__READ_WRITE ,__uart_sr_bits);
__IO_REG32_BIT(UART2_LINE_CR,         0x00100A88,__READ_WRITE ,__uart_line_cr_bits);
__IO_REG32_BIT(UART2_BAUDDIV_MSB,     0x00100A8C,__READ_WRITE ,__uart_bauddiv_msb_bits);
__IO_REG32_BIT(UART2_BAUDDIV_LSB,     0x00100A90,__READ_WRITE ,__uart_bauddiv_lsb_bits);
__IO_REG32_BIT(UART2_CR,              0x00100A94,__READ_WRITE ,__uart_cr_bits);
__IO_REG32_BIT(UART2_FR,              0x00100A98,__READ       ,__uart_fr_bits);
__IO_REG32_BIT(UART2_IIR,             0x00100A9C,__READ_WRITE ,__uart_iir_bits);
__IO_REG32_BIT(UART2_ILPR,            0x00100AA0,__READ_WRITE ,__uart_ilpr_bits);
__IO_REG32_BIT(UART2_RTS_CR,          0x00100AA4,__READ_WRITE ,__uart_rts_cr_bits);
__IO_REG32_BIT(UART2_RTS_LEAD,        0x00100AA8,__READ_WRITE ,__uart_rts_lead_bits);
__IO_REG32_BIT(UART2_RTS_TRAIL,       0x00100AAC,__READ_WRITE ,__uart_rts_trail_bits);
__IO_REG32_BIT(UART2_DRV_ENABLE,      0x00100AB0,__READ_WRITE ,__uart_drv_enable_bits);
__IO_REG32_BIT(UART2_BRM_CR,          0x00100AB4,__READ_WRITE ,__uart_brm_cr_bits);
__IO_REG32_BIT(UART2_RXFIFO_IRQLEVEL, 0x00100AB8,__READ_WRITE ,__uart_rxfifo_irqlevel_bits);
__IO_REG32_BIT(UART2_TXFIFO_IRQLEVEL, 0x00100ABC,__READ_WRITE ,__uart_txfifo_irqlevel_bits);

/***************************************************************************
 **
 **  SPI
 **
 ***************************************************************************/
__IO_REG32_BIT(SPI_DATA_REGISTER,     0x00100C00,__READ_WRITE ,__spi_data_register_bits);
__IO_REG32_BIT(SPI_SR,                0x00100C04,__READ_WRITE ,__spi_sr_bits);
__IO_REG32_BIT(SPI_CR,                0x00100C08,__READ_WRITE ,__spi_cr_bits);
__IO_REG32_BIT(SPI_INTERRUPT_CR,      0x00100C0C,__READ_WRITE ,__spi_interrupt_cr_bits);

/***************************************************************************
 **
 **  I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(I2C_CTRL,              0x00100D00,__READ_WRITE ,__i2c_ctrl_bits);
__IO_REG32_BIT(I2C_DATA,              0x00100D04,__READ_WRITE ,__i2c_data_bits);

/***************************************************************************
 **
 **  SYSTIME
 **
 ***************************************************************************/
__IO_REG32(    SYSTIME_NS,            0x00101100,__READ_WRITE );
__IO_REG32(    SYSTIME_S,             0x00101104,__READ_WRITE );
__IO_REG32(    SYSTIME_NS_BORDER,     0x00101108,__READ_WRITE );
__IO_REG32(    SYSTIME_NS_ADDUP,      0x0010110C,__READ_WRITE );
__IO_REG32(    SYSTIME_S_COMPARE,     0x00101110,__READ_WRITE );
__IO_REG32_BIT(SYSTIME_S_COMP_ENA,    0x00101114,__READ_WRITE ,__systime_s_comp_ena_bits);
__IO_REG32_BIT(SYSTIME_S_COMPARE_IRQ, 0x00101118,__READ_WRITE ,__systime_s_compare_irq_bits);

/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32(    RTC_1HZ_COUNTER,       0x00101200,__READ_WRITE );
__IO_REG32(    RTC_32KHZ_CUR_VAL,     0x00101204,__READ       );
__IO_REG32(    RTC_32KHZ_LAT_VAL,     0x00101208,__READ       );
__IO_REG32_BIT(RTC_IRQ2ISOLATE_CYCLES,0x0010120C,__WRITE      ,__rtc_irq2isolate_cycles_bits);
__IO_REG32_BIT(RTC_IRQ_MSK,           0x00101210,__READ_WRITE ,__rtc_irq_msk_bits);
__IO_REG32_BIT(RTC_IRQ_STAT,          0x00101214,__READ_WRITE ,__rtc_irq_stat_bits);
__IO_REG32_BIT(RTC_ISOLATED,          0x00101218,__READ       ,__rtc_isolated_bits);

/***************************************************************************
 **
 **  LCD
 **
 ***************************************************************************/
__IO_REG32_BIT(LCD_TIMING0,           0x00104000,__READ_WRITE ,__lcd_timing0_bits);
__IO_REG32_BIT(LCD_TIMING1,           0x00104004,__READ_WRITE ,__lcd_timing1_bits);
__IO_REG32_BIT(LCD_TIMING2,           0x00104008,__READ_WRITE ,__lcd_timing2_bits);
__IO_REG32_BIT(LCD_TIMING3,           0x0010400C,__READ_WRITE ,__lcd_timing3_bits);
__IO_REG32(   LCD_UPBASE,             0x00104010,__READ_WRITE );
__IO_REG32(   LCD_LPBASE,             0x00104014,__READ_WRITE );
__IO_REG32_BIT(LCD_IMSC,              0x00104018,__READ_WRITE ,__lcd_imsc_bits);
__IO_REG32_BIT(LCD_CONTROL,           0x0010401C,__READ_WRITE ,__lcd_control_bits);
__IO_REG32_BIT(LCD_RIS,               0x00104020,__READ       ,__lcd_ris_bits);
__IO_REG32_BIT(LCD_MIS,               0x00104024,__READ       ,__lcd_mis_bits);
__IO_REG32_BIT(LCD_ICR,               0x00104028,__WRITE      ,__lcd_icr_bits);
__IO_REG32(   LCD_UPCURR,             0x0010402C,__READ       );
__IO_REG32(   LCD_LPCURR,             0x00104030,__READ       );
__IO_REG32(   LCD_PALETTE_BASE_ADDR,  0x00104200,__READ       );
__IO_REG32(   CLCD_PERIPH_ID0,        0x00104FE0,__READ       );
__IO_REG32(   CLCD_PERIPH_ID1,        0x00104FE4,__READ       );
__IO_REG32(   CLCD_PERIPH_ID2,        0x00104FE8,__READ       );
__IO_REG32(   CLCD_PERIPH_ID3,        0x00104FEC,__READ       );
__IO_REG32(   CLCD_PCELL_ID0,         0x00104FF0,__READ       );
__IO_REG32(   CLCD_PCELL_ID1,         0x00104FF4,__READ       );
__IO_REG32(   CLCD_PCELL_ID2,         0x00104FF8,__READ       );
__IO_REG32(   CLCD_PCELL_ID3,         0x00104FFC,__READ       );

/***************************************************************************
 **
 **  USB
 **
 ***************************************************************************/
__IO_REG32_BIT(USB_ID,                0x00120000,__READ       ,__usb_id_bits);
__IO_REG32_BIT(USB_CTRL,              0x00120004,__READ_WRITE ,__usb_ctrl_bits);
__IO_REG32_BIT(USB_FRM_TIMER,         0x00120008,__READ_WRITE ,__usb_frm_timer_bits);
__IO_REG32_BIT(USB_MAIN_EV,           0x0012000C,__READ_WRITE ,__usb_main_ev_bits);
__IO_REG32_BIT(USB_MAIN_EM,           0x00120010,__READ_WRITE ,__usb_main_em_bits);
__IO_REG32_BIT(USB_PIPE_EV,           0x00120014,__READ_WRITE ,__usb_pipe_ev_bits);
__IO_REG32_BIT(USB_PIPE_EM,           0x00120018,__READ_WRITE ,__usb_pipe_em_bits);
__IO_REG32_BIT(USB_PIPE_SEL,          0x00120024,__READ_WRITE ,__usb_pipe_sel_bits);
__IO_REG32_BIT(USB_PORT_STAT,         0x0012002C,__READ       ,__usb_port_stat_bits);
__IO_REG32_BIT(USB_PORT_CTRL,         0x00120030,__READ_WRITE ,__usb_port_ctrl_bits);
__IO_REG32_BIT(USB_PSC_EV,            0x00120034,__READ_WRITE ,__usb_psc_ev_bits);
__IO_REG32_BIT(USB_PSC_EM,            0x00120038,__READ_WRITE ,__usb_psc_em_bits);
__IO_REG32_BIT(USB_PIPE_CTRL,         0x00120040,__READ_WRITE ,__usb_pipe_ctrl_bits);
__IO_REG32_BIT(USB_PIPE_CFG,          0x00120044,__READ_WRITE ,__usb_pipe_cfg_bits);
__IO_REG32_BIT(USB_PIPE_ADDR,         0x00120048,__READ_WRITE ,__usb_pipe_addr_bits);
__IO_REG32_BIT(USB_PIPE_STAT,         0x0012004C,__READ_WRITE ,__usb_pipe_stat_bits);
__IO_REG32_BIT(USB_PIPE_DATA_PTR,     0x00120050,__READ_WRITE ,__usb_pipe_data_ptr_bits);
__IO_REG32_BIT(USB_PIPE_DATA_TBYTES,  0x00120054,__READ_WRITE ,__usb_pipe_data_tbytes_bits);
__IO_REG32_BIT(USB_PIPE_ADATA_PTR,    0x00120058,__READ_WRITE ,__usb_pipe_adata_ptr_bits);
__IO_REG32_BIT(USB_PIPE_ADATA_TBYTES, 0x0012005C,__READ_WRITE ,__usb_pipe_adata_tbytes_bits);
__IO_REG32_BIT(USB_DEBUG_CTRL,        0x00120060,__READ_WRITE ,__usb_debug_ctrl_bits);
__IO_REG32_BIT(USB_DEBUG_PID,         0x00120064,__READ_WRITE ,__usb_debug_pid_bits);
__IO_REG32_BIT(USB_DEBUG_STAT,        0x00120068,__READ       ,__usb_debug_stat_bits);
__IO_REG32(    USB_TEST,              0x0012006C,__READ_WRITE );
__IO_REG32_BIT(USB_MAIN_CFG,          0x00120080,__READ       ,__usb_main_cfg_bits);
__IO_REG32_BIT(USB_MODE_CFG,          0x00120084,__READ       ,__usb_mode_cfg_bits);
__IO_REG32_BIT(USB_CORE_CTRL,         0x00120088,__READ_WRITE ,__usb_core_ctrl_bits);

/***************************************************************************
 **
 **  VIC
 **
 ***************************************************************************/
__IO_REG32_BIT(VIC_IRQ_STATUS,        0x001ff000,__READ       ,__vic_channels_bits);
__IO_REG32_BIT(VIC_FIQ_STATUS,        0x001ff004,__READ       ,__vic_channels_bits);
__IO_REG32_BIT(VIC_RAW_INTR,          0x001ff008,__READ       ,__vic_channels_bits);
__IO_REG32_BIT(VIC_INT_SELECT,        0x001ff00C,__READ_WRITE ,__vic_channels_bits);
__IO_REG32_BIT(VIC_INT_ENABLE,        0x001ff010,__READ_WRITE ,__vic_channels_bits);
__IO_REG32_BIT(VIC_INT_ENCLEAR,       0x001ff014,__WRITE      ,__vic_channels_bits);
__IO_REG32_BIT(VIC_SOFTINT,           0x001ff018,__READ_WRITE ,__vic_channels_bits);
__IO_REG32_BIT(VIC_SOFTINT_CLEAR,     0x001ff01C,__WRITE      ,__vic_channels_bits);
__IO_REG32_BIT(VIC_PROTECTION,        0x001ff020,__READ_WRITE ,__vic_protection_bits);
__IO_REG32(    VIC_VECT_ADDR,         0x001ff030,__READ_WRITE );
__IO_REG32(    VIC_DEF_VECT_ADDR,     0x001ff034,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR0,        0x001ff100,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR1,        0x001ff104,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR2,        0x001ff108,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR3,        0x001ff10C,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR4,        0x001ff110,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR5,        0x001ff114,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR6,        0x001ff118,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR7,        0x001ff11C,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR8,        0x001ff120,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR9,        0x001ff124,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR10,       0x001ff128,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR11,       0x001ff12C,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR12,       0x001ff130,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR13,       0x001ff134,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR14,       0x001ff138,__READ_WRITE );
__IO_REG32(    VIC_VECT_ADDR15,       0x001ff13C,__READ_WRITE );
__IO_REG32_BIT(VIC_VECT_CNTL0,        0x001ff200,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL1,        0x001ff204,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL2,        0x001ff208,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL3,        0x001ff20C,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL4,        0x001ff210,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL5,        0x001ff214,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL6,        0x001ff218,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL7,        0x001ff21C,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL8,        0x001ff220,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL9,        0x001ff224,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL10,       0x001ff228,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL11,       0x001ff22C,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL12,       0x001ff230,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL13,       0x001ff234,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL14,       0x001ff238,__READ_WRITE ,__vic_vect_cntl_bits);
__IO_REG32_BIT(VIC_VECT_CNTL15,       0x001ff23C,__READ_WRITE ,__vic_vect_cntl_bits);

/***************************************************************************
 **
 **  Motior Control
 **
 ***************************************************************************/
__IO_REG32_BIT(PWM0_CONFIG,           0x0016295C,__READ_WRITE ,__pwm_config_bits);
__IO_REG32_BIT(PWM0_STATUS,           0x00162960,__READ_WRITE ,__pwm_status_bits);
__IO_REG32_BIT(PWM0_TP,               0x00162964,__READ_WRITE ,__pwm_tp_bits);
__IO_REG32_BIT(PWM0_TU,               0x00162968,__READ_WRITE ,__pwm_tu_bits);
__IO_REG32_BIT(PWM0_TV,               0x0016296C,__READ_WRITE ,__pwm_tv_bits);
__IO_REG32_BIT(PWM0_TW,               0x00162970,__READ_WRITE ,__pwm_tw_bits);
__IO_REG32_BIT(PWM0_TD,               0x00162974,__READ_WRITE ,__pwm_td_bits);
__IO_REG32_BIT(RPWM0_TP,              0x00162978,__READ_WRITE ,__rpwm_tp_bits);
__IO_REG32_BIT(RPWM0_TR,              0x0016297C,__READ_WRITE ,__rpwm_tr_bits);
__IO_REG32_BIT(PWM0_CNT,              0x00162980,__READ_WRITE ,__pwm_cnt_bits);
__IO_REG32_BIT(RPWM0_CNT,             0x00162984,__READ_WRITE ,__rpwm_cnt_bits);
__IO_REG32_BIT(PWM0_STRTIME,          0x00162988,__READ_WRITE ,__pwm_strtime_bits);
__IO_REG32_BIT(RPWM0_STRTIME,         0x0016298C,__READ_WRITE ,__rpwm_strtime_bits);
__IO_REG32_BIT(PWM1_CONFIG,           0x00162A5C,__READ_WRITE ,__pwm_config_bits);
__IO_REG32_BIT(PWM1_STATUS,           0x00162A60,__READ_WRITE ,__pwm_status_bits);
__IO_REG32_BIT(PWM1_TP,               0x00162A64,__READ_WRITE ,__pwm_tp_bits);
__IO_REG32_BIT(PWM1_TU,               0x00162A68,__READ_WRITE ,__pwm_tu_bits);
__IO_REG32_BIT(PWM1_TV,               0x00162A6C,__READ_WRITE ,__pwm_tv_bits);
__IO_REG32_BIT(PWM1_TW,               0x00162A70,__READ_WRITE ,__pwm_tw_bits);
__IO_REG32_BIT(PWM1_TD,               0x00162A74,__READ_WRITE ,__pwm_td_bits);
__IO_REG32_BIT(RPWM1_TP,              0x00162A78,__READ_WRITE ,__rpwm_tp_bits);
__IO_REG32_BIT(RPWM1_TR,              0x00162A7C,__READ_WRITE ,__rpwm_tr_bits);
__IO_REG32_BIT(PWM1_CNT,              0x00162A80,__READ_WRITE ,__pwm_cnt_bits);
__IO_REG32_BIT(RPWM1_CNT,             0x00162A84,__READ_WRITE ,__rpwm_cnt_bits);
__IO_REG32_BIT(PWM1_STRTIME,          0x00162A88,__READ_WRITE ,__pwm_strtime_bits);
__IO_REG32_BIT(RPWM1_STRTIME,         0x00162A8C,__READ_WRITE ,__rpwm_strtime_bits);
__IO_REG32_BIT(ENC_CONFIG_ENCODER,    0x00163990,__READ_WRITE ,__enc_config_encoder_bits);
__IO_REG32_BIT(ENC_CONFIG_CAPTURE,    0x00163994,__READ_WRITE ,__enc_config_capture_bits);
__IO_REG32_BIT(ENC_COMMAND,           0x00163998,__READ_WRITE ,__enc_command_bits);
__IO_REG32_BIT(ENC_STATUS,            0x0016399C,__READ_WRITE ,__enc_status_bits);
__IO_REG32_BIT(ENC0_POSITION,         0x001639A0,__READ_WRITE ,__enc_position_bits);
__IO_REG32_BIT(ENC0_NULLPOSITION,     0x001639A4,__READ       ,__enc_nullposition_bits);
__IO_REG32_BIT(ENC1_POSITION,         0x001639A8,__READ_WRITE ,__enc_position_bits);
__IO_REG32_BIT(ENC1_NULLPOSITION,     0x001639AC,__READ       ,__enc_nullposition_bits);
__IO_REG32_BIT(ENC0_EDGETIME,         0x001639B0,__READ       ,__enc_edgetime_bits);
__IO_REG32_BIT(ENC1_EDGETIME,         0x001639B4,__READ       ,__enc_edgetime_bits);
__IO_REG32_BIT(ENC_CAPTURE0,          0x001639B8,__READ       ,__enc_capture_bits);
__IO_REG32_BIT(ENC_CAPTURE1,          0x001639BC,__READ       ,__enc_capture_bits);
__IO_REG32_BIT(ENC_CAPTURE2,          0x001639C0,__READ       ,__enc_capture_bits);
__IO_REG32_BIT(ENC_CAPTURE3,          0x001639C4,__READ       ,__enc_capture_bits);

/***************************************************************************
 **
 **  ADC
 **
 ***************************************************************************/
__IO_REG32_BIT(ADC0,                  0x0017009C,__READ_WRITE ,__adc_bits);
__IO_REG32_BIT(ADC1,                  0x0017409C,__READ_WRITE ,__adc_bits);
__IO_REG32_BIT(ADC2,                  0x0017809C,__READ_WRITE ,__adc_bits);
__IO_REG32_BIT(ADC3,                  0x0017C09C,__READ_WRITE ,__adc_bits);

/***************************************************************************
 **
 **  PHY
 **
 ***************************************************************************/
__IO_REG32_BIT(PHY_CR,                0x00100010,__READ_WRITE ,__phy_cr_bits);

/***************************************************************************
 **
 **  PFIFO
 **
 ***************************************************************************/
__IO_REG32(    PFIFO_BASE0,           0x00164000,__READ_WRITE );
__IO_REG32(    PFIFO_BASE1,           0x00164004,__READ_WRITE );
__IO_REG32(    PFIFO_BASE2,           0x00164008,__READ_WRITE );
__IO_REG32(    PFIFO_BASE3,           0x0016400C,__READ_WRITE );
__IO_REG32(    PFIFO_BASE4,           0x00164010,__READ_WRITE );
__IO_REG32(    PFIFO_BASE5,           0x00164014,__READ_WRITE );
__IO_REG32(    PFIFO_BASE6,           0x00164018,__READ_WRITE );
__IO_REG32(    PFIFO_BASE7,           0x0016401C,__READ_WRITE );
__IO_REG32(    PFIFO_BASE8,           0x00164020,__READ_WRITE );
__IO_REG32(    PFIFO_BASE9,           0x00164024,__READ_WRITE );
__IO_REG32(    PFIFO_BASE10,          0x00164028,__READ_WRITE );
__IO_REG32(    PFIFO_BASE11,          0x0016402C,__READ_WRITE );
__IO_REG32(    PFIFO_BASE12,          0x00164030,__READ_WRITE );
__IO_REG32(    PFIFO_BASE13,          0x00164034,__READ_WRITE );
__IO_REG32(    PFIFO_BASE14,          0x00164038,__READ_WRITE );
__IO_REG32(    PFIFO_BASE15,          0x0016403C,__READ_WRITE );
__IO_REG32(    PFIFO_BASE16,          0x00164040,__READ_WRITE );
__IO_REG32(    PFIFO_BASE17,          0x00164044,__READ_WRITE );
__IO_REG32(    PFIFO_BASE18,          0x00164048,__READ_WRITE );
__IO_REG32(    PFIFO_BASE19,          0x0016404C,__READ_WRITE );
__IO_REG32(    PFIFO_BASE20,          0x00164050,__READ_WRITE );
__IO_REG32(    PFIFO_BASE21,          0x00164054,__READ_WRITE );
__IO_REG32(    PFIFO_BASE22,          0x00164058,__READ_WRITE );
__IO_REG32(    PFIFO_BASE23,          0x0016405C,__READ_WRITE );
__IO_REG32(    PFIFO_BASE24,          0x00164060,__READ_WRITE );
__IO_REG32(    PFIFO_BASE25,          0x00164064,__READ_WRITE );
__IO_REG32(    PFIFO_BASE26,          0x00164068,__READ_WRITE );
__IO_REG32(    PFIFO_BASE27,          0x0016406C,__READ_WRITE );
__IO_REG32(    PFIFO_BASE28,          0x00164070,__READ_WRITE );
__IO_REG32(    PFIFO_BASE29,          0x00164074,__READ_WRITE );
__IO_REG32(    PFIFO_BASE30,          0x00164078,__READ_WRITE );
__IO_REG32(    PFIFO_BASE31,          0x0016407C,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE0,    0x00164080,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE1,    0x00164084,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE2,    0x00164088,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE3,    0x0016408C,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE4,    0x00164090,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE5,    0x00164094,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE6,    0x00164098,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE7,    0x0016409C,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE8,    0x001640A0,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE9,    0x001640A4,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE10,   0x001640A8,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE11,   0x001640AC,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE12,   0x001640B0,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE13,   0x001640B4,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE14,   0x001640B8,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE15,   0x001640BC,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE16,   0x001640C0,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE17,   0x001640C4,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE18,   0x001640C8,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE19,   0x001640CC,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE20,   0x001640D0,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE21,   0x001640D4,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE22,   0x001640D8,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE23,   0x001640DC,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE24,   0x001640E0,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE25,   0x001640E4,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE26,   0x001640E8,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE27,   0x001640EC,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE28,   0x001640F0,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE29,   0x001640F4,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE30,   0x001640F8,__READ_WRITE );
__IO_REG32(    PFIFO_BORDER_BASE31,   0x001640FC,__READ_WRITE );
__IO_REG32_BIT(PFIFO_RESET,           0x00164100,__READ_WRITE ,__BITS32);
__IO_REG32_BIT(PFIFO_FULL,            0x00164104,__READ       ,__BITS32);
__IO_REG32_BIT(PFIFO_EMPTY,           0x00164108,__READ       ,__BITS32);
__IO_REG32_BIT(PFIFO_OVERFLOW,        0x0016410C,__READ       ,__BITS32);
__IO_REG32_BIT(PFIFO_UNDERRUN,        0x00164110,__READ       ,__BITS32);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE0,0x00164180,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE1,0x00164184,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE2,0x00164188,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE3,0x0016418C,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE4,0x00164190,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE5,0x00164194,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE6,0x00164198,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE7,0x0016419C,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE8,0x001641A0,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE9,0x001641A4,__READ       ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE10,0x001641A8,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE11,0x001641AC,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE12,0x001641B0,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE13,0x001641B4,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE14,0x001641B8,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE15,0x001641BC,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE16,0x001641C0,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE17,0x001641C4,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE18,0x001641C8,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE19,0x001641CC,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE20,0x001641D0,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE21,0x001641D4,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE22,0x001641D8,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE23,0x001641DC,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE24,0x001641E0,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE25,0x001641E4,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE26,0x001641E8,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE27,0x001641EC,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE28,0x001641F0,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE29,0x001641F4,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE30,0x001641F8,__READ      ,__pfifo_fill_level_base_bits);
__IO_REG32_BIT(PFIFO_FILL_LEVEL_BASE31,0x001641FC,__READ      ,__pfifo_fill_level_base_bits);

/***************************************************************************
 **
 **  CRC
 **
 ***************************************************************************/
__IO_REG32(    CRC_CRC,               0x00101000,__READ_WRITE );
__IO_REG32_BIT(CRC_DATA,              0x00101004,__READ_WRITE ,__crc_data_bits);
__IO_REG32(    CRC_POLYNOMIAL,        0x00101008,__READ_WRITE );
__IO_REG32_BIT(CRC_CONFIG,            0x0010100C,__READ_WRITE ,__crc_config_bits);

/***************************************************************************
 **
 **  COM
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQ_XPEC0,             0x00164400,__READ_WRITE ,__irq_xpec_bits);
__IO_REG32_BIT(IRQ_XPEC1,             0x00164404,__READ_WRITE ,__irq_xpec_bits);
__IO_REG32_BIT(IRQ_XPEC2,             0x00164408,__READ_WRITE ,__irq_xpec_bits);
__IO_REG32_BIT(IRQ_XPEC3,             0x0016440C,__READ_WRITE ,__irq_xpec_bits);

/* Assembler-specific declarations  ****************************************/
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
 **  NETX500 IRQ Interrupt Vector Table
 **
 ***************************************************************************/
#define SW_INT            0
#define TIMER0_INT        1
#define TIMER1_INT        2
#define TIMER2_INT        3
#define SYSTIME_NS_INT    4
#define SYSTIME_S_INT     5
#define GPIO15_INT        6
#define WATCHDOG_INT      7
#define UART0_INT         8
#define UART1_INT         9
#define UART2_INT        10
#define USB_INT          11
#define SPI_INT          12
#define I2C_INT          13
#define LCD_INT          14
#define HIF_INT          15
#define GPIO_INT         16
#define COM0_INT         17
#define COM1_INT         18
#define COM2_INT         19
#define COM3_INT         20
#define MSYNC0_INT       21
#define MSYNC1_INT       22
#define MSYNC2_INT       23
#define MSYNC3_INT       24
#define INT_PHY_INT      25
#define ISO_AREA_INT     26
#define TIMER3_INT       29
#define TIMER4_INT       30

#endif    /* __NETX500_H */
