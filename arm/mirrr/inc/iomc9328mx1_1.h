/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Motorola MC9328MX1 Dragonball
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2003
 **
 **    $Revision: 1.10 $
 **
 ***************************************************************************/

#ifndef __MC9328MX1_H
#define __MC9328MX1_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    MC9328MX1 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* -------------------------------------------------------------------------*/
/*      AIPI Registers                                                      */
/* -------------------------------------------------------------------------*/

typedef struct {        /* Peripheral Size Register lower (0x00200000) Reset 1 (0xFFFFF800)     2 (0xFFFFC410)*/
  __REG32               : 1;    // Bit  0       - Reserved
  __REG32 MOD_EN_L      : 15;   // Bits 1-15    - Module enable L bit
  __REG32               : 16;
} __AIPI_PSR0_bits;

typedef struct {        /* Peripheral Size Register upper (0x00200004) Reset 1 (0xFFFFFFFF)     2 (0xFFFFFBEF)*/
  __REG32               : 1;    // Bit  0       - Reserved
  __REG32 MOD_EN_U      : 15;   // Bits 1-15    - Module enable H bit
  __REG32               : 16;
} __AIPI_PSR1_bits;

typedef struct {        /* Peripheral Access Register (0x00200008) Reset 1 (0xFFFFFFFF)         2 (0xFFFFFFFF)  */
  __REG32               : 1;    // Bit  0       - Reserved
  __REG32 ACCESS        : 15;   // Bits 1-15    - Access Control
  __REG32               : 16;
} __AIPI_PAR_bits;

typedef struct {        /* Peripheral Control Register (0x0020000C) Reset 1 (0x00000000)        2 (0x00000000)  */
  __REG32                 : 1;    // Bit  0       - Reserved
  __REG32 ACCESS_MODE     : 15;   // Bits 1-15    - Module enable H bit
  __REG32                 : 16;
} __AIPI_PCR_bits;

typedef struct {        /* Time-Out Status Register (0x00200010) Reset 1 (0x00000000)   2 (0x00000000)          */
  __REG32                 : 1;    // Bit  0       - Reserved
  __REG32 MODULE_EN       : 15;   // Bits 1-15    - Module enable H bit
  __REG32 BE1             : 1;    // Bit  16      - contains the ips_byte_7_0 status prior to time-out event.
  __REG32 BE2             : 1;    // Bit  17      - contains the ips_byte_15_8 status prior to time-out event.
  __REG32 BE3             : 1;    // Bit  18      - contains the ips_byte_23_16 status prior to time-out event.
  __REG32 BE4             : 1;    // Bit  19      - contains the ips_byte_31_24 status prior to time-out event.
  __REG32 ADDR            : 10;   // Bits 20-29   - contains the ips_addr[11:2] status prior to time-out event.
  __REG32 RW              : 1;    // Bit  30      - contains the ips_rwb status prior to time-out event.
  __REG32 TO              : 1;    // Bit  19      - when set to 1 indicates a time-out event and may be cleared by the user.
} __AIPI_TSR_bits;


/* -------------------------------------------------------------------------*/
/*      Watchdog Registers                                                  */
/* -------------------------------------------------------------------------*/

typedef struct {        // Watchdog Control Register (0x00201000) Reset  (0x00000000)
  __REG32 WDE           : 1;    // Bit  0       - Watchdog Enable
  __REG32 WDEC          : 1;    // Bits 1       - Watchdog Enable Control
  __REG32 SWR           : 1;    // Bit  2       - Software Reset Enable
  __REG32 TMD           : 1;    // Bit  3       - Test Mode Enable
  __REG32 WIE           : 1;    // Bit  4       - Watchdog Interrupt Enable
  __REG32               : 3;    // Bits 5-7     - reserved
  __REG32 WT            : 7;    // Bits 8-14    - Watchdog Time-Out Field
  __REG32 WHALT         : 1;    // Bit  15      - Watchdog Halt
  __REG32               : 16;
} __WDG_WCR_bits ;

typedef struct {        // Watchdog Service Register (0x00201004) Reset (0x00000000)
  __REG32 WSR           : 16;   // Bit  0-15    - Watchdog Service Register
  __REG32               : 16;
} __WDG_WSR_bits ;

typedef struct {        // Watchdog Status Register (0x00201008) Reset (0x00000000)
  __REG32 TOUT          : 1;    // Bit  0       - Time-Out
  __REG32               : 1;    // Bits 1       - Watchdog Enable Control
  __REG32 TINT          : 1;    // Bit  2       - Time-Out Interrupt
  __REG32               : 29;
} __WDG_WSTR_bits ;


/* -------------------------------------------------------------------------*/
/*      Timer Registers                                                     */
/* -------------------------------------------------------------------------*/

/* ------------ Timer 1 Control Register        T1 (0x00202000) T2 (0x00203000) reset 0x0000 0x0000*/
typedef struct {
  __REG32 TEN           : 1;    // Bit  0      - Timer Enable1 = Timer is enabled 0 = Timer is disabled (counter reset to 0)
  __REG32 CLKSOURCE     : 3;    // Bit  1-3    - Clock Source
                                //             - 000 = Stop count (clock disabled)
                                //             - 001 = PERCLK1 to prescaler
                                //             - 010 = PERCLK1 ÷16 to prescaler
                                //             - 011 = TIN to prescaler
                                //             - 1xx = 32 kHz clock to prescaler
  __REG32 IRQEN         : 1;    // Bit  4      - Interrupt Request Enable1 = Enable the compare interrupt
  __REG32 OM            : 1;    // Bit  5      - Output Mode0 = Active-low pulse for one COUNT period 1 = Toggle output
  __REG32 CAP           : 2;    // Bit  6-7    - Capture Edge
                                //             - 00 = Disable the capture function
                                //             - 01 = Capture on the rising edge and generate an interrupt
                                //             - 10 = Capture on the falling edge and generate an interrupt
                                //             - 11 = Capture on the rising and falling edges and generate an interrupt
  __REG32 FRR           : 1;    // Bit  8      - Free-Run/Restart0 = Restart mode 1 = Free-run mode
  __REG32               : 6;    // Bits 9-14   - Reserved
  __REG32 SWR           : 1;    // Bit  15     - Software Reset0 = No software reset sent
  __REG32               : 16;
} __TCTL_bits ;

/* ------------Timer 1 Prescaler Register       T1 (0x00202004) T2 (0x00203004) reset 0x0000 0x0000*/
typedef struct {
  __REG32 PRESCALER     : 8;    // bits 0-7             - Bits 7-0
                                //                      - 0x00 = Divide by 1
                                //                      - 0x01 = Divide by 2
                                //                      - ...
                                //                      - 0xFF = Divide by 256
  __REG32               : 24;
} __TPRER_bits;

/* ------------Timer 1 Compare Register         T1 (0x00202008) T2 (0x00203008) reset 0xFFFF 0xFFFF*/
typedef struct {
  __REG32 COMPARE_VALUE      :32;    // bits 0-31            -
} __TCMP_bits;

/* ------------Timer 1 Capture Register         T1 (0x0020200C) T2 (0x0020300C) reset 0x0000 0x0000*/
typedef struct {
  __REG32 CAPTURE_VALUE      :32;    // bits 0-31            -
} __TCR_bits;

/* ------------Timer 1 Counter Register         T1 (0x00202010) T2 (0x00203010) reset 0x0000 0x0000*/
typedef struct {
  __REG32 COUNTER_VALUE      :32;    // bits 0-31            -
} __TCN_bits;

/* ------------Timer 1 Status Register  T1 (0x00202014) T2 (0x00203014) reset 0x0000 0x0000*/
typedef struct {
  __REG32 COMP  :1;     // bit  0  - Compare Event0 = No compare event occurred
  __REG32 CAPT  :1;     // bit  1  - Capture Event0 = No capture event occurred
  __REG32       :30;
} __TSTAT_bits;


/* -------------------------------------------------------------------------*/
/*      RTC Registers                                                       */
/* -------------------------------------------------------------------------*/

/* RTC Days counter register */
typedef struct {
  __REG32 DAYS              :9;
  __REG32                   :23;
} __DAYR_bits;

/* RTC hours and minutes counter register */
typedef struct {
  __REG32 MINUTES           :6;
  __REG32                   :2;
  __REG32 HOURS             :5;
  __REG32                   :19;
} __HOURMIN_bits;

/* RTC seconds counter register */
typedef struct {
  __REG32 SECONDS           :6;
  __REG32                   :26;
} __SECONDS_bits;

/* RTC Day alarm register */
typedef struct {
  __REG32 DAYSAL            :9;
  __REG32                   :23;
} __DAYALARM_bits;

/* RTC control register */
typedef struct {
  __REG32 SWR               :1;
  __REG32                   :4;
  __REG32 XTL               :2;
  __REG32 EN                :1;
  __REG32                   :24;
} __RCCTL_bits;

/* RTC interrupt status register */
typedef struct {
  __REG32 SW                :1;
  __REG32 MIN               :1;
  __REG32 ALM               :1;
  __REG32 DAY               :1;
  __REG32 _1HZ              :1;
  __REG32 HR                :1;
  __REG32                   :1;
  __REG32 _2HZ              :1;
  __REG32 SAM0              :1;
  __REG32 SAM1              :1;
  __REG32 SAM2              :1;
  __REG32 SAM3              :1;
  __REG32 SAM4              :1;
  __REG32 SAM5              :1;
  __REG32 SAM6              :1;
  __REG32 SAM7              :1;
  __REG32                   :16;
} __RTCISR_bits;

/* RTC stopwatch minutes register */
typedef struct {
  __REG32 CNT               :6;
  __REG32                   :26;
} __STPWCH_bits;


/* -------------------------------------------------------------------------*/
/*      LCD Registers                                                       */
/* -------------------------------------------------------------------------*/

typedef struct {        /* Screen Start Address Register (0x00205000) Reset (0x00000000) */
  __REG32               : 2;    // Bits 0:1     - reserved
  __REG32 SSA           : 30;   // Bits 2:31    - Screen start address ( 4Mb Storage Req'd )
} __SSA_bits ;

typedef struct {        /* Size Register (0x00205004) Reset (0x00000000) */
  __REG32 YMAX          : 9;    // Bits 0:8             - Screen height in lines
  __REG32               : 11;   // Bits 9:19    - Reserved
  __REG32 XMAX          : 6;    // Bits 20:25   - Screen width divided by 16
  __REG32               : 6;    // Bits 26:31   - Reserved
} __SIZE_REG_bits ;


typedef struct {        /* Virtual Page Width Register  (0x00205008) Reset (0x00000000) */
  __REG32 VPW           : 10;   // Bits 0:9     - Represents the number of 32-bit words required to hold the data for one virtual line.
  __REG32               : 22;   // Bits 10:31   - Reserved
} __VPW_bits ;

typedef struct {        /* Virtual Page Width Register  (0x00205008) Reset (0x00000000) */
  __REG32 PCD           : 6;    // Bits 0:5     - Pixel Clock Divider. LCDC_CLK is divided by (PCD+1) to yield the pixel clock rate. Must be set such that the LSCLK freq is 1/5 of teh HCLK freq.
  __REG32 SHARP         : 1;    // Bits 6       - Sharp Panel Enables/Disables signals for Sharp FR_TFT 320x240 panels
  __REG32 SCLK_SEL      : 1;    // Bits 7       - LSCLK Select - Enables(1)/Disables(0) LSCLK in TFT Mode when there is no data output
  __REG32 ACD           : 7;    // Bits 8:14    - Alternate Crystal Direction (Not used in TFT Mode)
  __REG32 ACD_SEL       : 1;    // Bit 15       - ACD Clock Source Select (0=Use FRM, 1=Use LP/HSYN)
  __REG32 REV_VS        : 1;    // Bit 16       - Reverse Vertical Scan (0=Normal, 1 = Reversed)
  __REG32 SWAP_SEL      : 1;    // Bit 17       - Swap Select - Controls the swap of data in little endian mode (0 = 16 bpp, 1 = 8/4/2/1 bpp )
  __REG32 END_SEL       : 1;    // Bit 18       - Endian Select for image memory (0 = Little endian, 1 = Big endian)
  __REG32 SCLK_IDLE     : 1;    // Bit 19       - Enables (1) or Disables (0) LSCLK when VSYNC is idle in TFT mode
  __REG32 OE_POL        : 1;    // Bit 20       - Output Enable Polarity (0 = Active high, 1 = Active low)
  __REG32 CLK_POL       : 1;    // Bit 21       - LCD Shift Clock Polarity - sets the polarity of the active edge of the shift clock (0 = Active high, 1 = Active low)
  __REG32 LP_POL        : 1;    // Bit 22       - Line Pulse Polarity (0 = Active high, 1 = Active low)
  __REG32 FLM_POL       : 1;    // Bit 23       - First Line Marker Polarity (0 = Active high, 1 = Active low)
  __REG32 PIX_POL       : 1;    // Bit 24       - Pixel Polarity (0=Active High, 1 = Active Low)
  __REG32 BPIX          : 3;    // Bits 25:27   - Bits Per Pixel in memory (0=1bpp, 1=2bpp, 2=4bpp, 3=8bpp, 4=12/16bpp)
  __REG32 PBSIZ         : 2;    // Bits 28:29   - Panel Bus Width (for non-TFT) (0=1-bit, 1=2-bit, 2=4-bit, 3=8-bit)
  __REG32 COLOUR        : 1;    // Bit 30       - Interfaces to Color Display (0=Monochrome, 1=colour)
  __REG32 TFT           : 1;    // Bit 31       - Interfaces to TFT Display (0=Passive, 1=Active)
} __PCR_bits ;

typedef struct {        /* Horizontal Configuration Register  (0x0020501C) Reset (0x04000000) */
  __REG32 H_WAIT_2      : 8;    // Bits 0:7     - Wait Between HSYNC and Start of Next Line. Specifies the number of pixel clk periods between the end of HSYNC and the beginning of the first data of next line. Total delay time equals (H_WAIT_2 + 3).
  __REG32 H_WAIT_1      : 8;    // Bits 8:15    - Wait Between OE and HSYNC - Specifies the number of pixel clk periods between the last LD of each line and the beginning of the HSYNC. Total delay time equals (H_WAIT_1 + 1).
  __REG32               : 10;   // Bits 16:25   - Reserved
  __REG32 H_WIDTH       : 6;    // Bits 26:31   - Specifies the number of pixel clk periods that HSYNC is activated. The active time is equal to (H_WIDTH + 1)
} __HCR_bits;

typedef struct {        /* Vertical Configuration Register  (0x00205020) Reset (0x04010000) */
  __REG32 V_WAIT_2      : 8;    // Bits 0:7     - Wait Between Frames 2. Defines the delay, in lines, between the end of the VSYNC pulse and the beginning of the OE pulse of the first line in active mode.
  __REG32 V_WAIT_1      : 8;    // Bits 8:15    - Wait Between Frames 1. Defines the delay, in lines, between the end of the OE pulse and the beginning of the VSYNC pulse for active (TFT=1) mode.
  __REG32               : 10;   // Bits 16:25   - Reserved
  __REG32 V_WIDTH       : 6;    // Bits 26:31   - Vertical Sync Pulse Width - Specifies the width, in lines, of the VSYNC pulse for active mode.
} __VCR_bits ;

typedef struct {        /* Panning Offset Register  (0x00205024) Reset (0x00000000) */
  __REG32 POS           : 5;    // Bits 0:4     - Panning Offset - Defines the number of bits that the data from memory is panned to the left before processing.
  __REG32               : 27;   // Bits 5:31    - Reserved
} __POS_bits ;

typedef struct {        /* LCD Cursor Position Register  (0x0020500C) Reset (0x00000000) */
  __REG32 CYP           : 9;    // Bits 0:8     - Cursor Y Position (From 0 to YMAX)
  __REG32               : 7;    // Bits 9:15    - Reserved
  __REG32 CXP           :10;    // Bits 16:25   - Cursor X Position (From 0 to XMAX)
  __REG32               : 2;    // Bits 26:27   - Reserved
  __REG32 OP            : 1;    // Bit 28       - Arithmetic Operation Control. Enables/Disables arithmetic operations between the background and the cursor
  __REG32               : 1;    // Bit 29       - Reserved
  __REG32 CC            : 2;    // Bits 30:31   - Cursor Control (0=Disabled, 1 = Full Cursor, 2 = Reversed Video, 11 = Full (White) cursor)
} __CPOS_bits ;

typedef struct {        /* LCD Cursor Width Height and Blink Register  (0x00205010) Reset (0x0101007F) */
  __REG32 BD            : 8;    // Bits 0:7             - Blink Divisor - Sets the cursor blink rate. A 32 Hz clock from RTC is used to clock the 8-bit up counter. When the counter reaches BS the cursor toggles.
  __REG32               : 8;    // Bits 8:15    - Reserved
  __REG32 CH            : 5;    // Bits 16:20   - Cursor Height in pixels (0-31)
  __REG32               : 3;    // Bits 21:23   - Reserved
  __REG32 CW            : 5;    // Bits 24:28   - Cursor Width in pixels (0-31)
  __REG32               : 2;    // Bits 29:30   - Reserved
  __REG32 BK_EN         : 1;    // Bit 31       - Blink Enable
} __LCWHB_bits ;

typedef struct {        /* LCD Color Cursor Mapping Register  (0x00205014) Reset (0x00000000) */
  __REG32 CUR_COL_B     : 5;    // Bits 0:4     - Cursor Blue Field
  __REG32 CUR_COL_G     : 6;    // Bits 5:10    - Cursor Green Field
  __REG32 CUR_COL_R     : 5;    // Bits 11:15   - Cursor Red Field
  __REG32               : 16;   // Bits 29:30   - Reserved
} __LCHCC_bits ;

typedef struct {        /* Sharp Configuration 1 Register  (0x00205028) Reset (0x04000373) */
  __REG32 GRAY1                 : 4;    // Bits 0:3     - Gray-Scale 1 - Represents one of the two grey-scale densities (0-16)
  __REG32 GRAY2                 : 4;    // Bits 4:7     - Gray-Scale 2 - Represents the other grey-scale density (0-16)
  __REG32 REV_TOGGLE_DELAY      : 4;    // Bits 8:11    - REV Toggle Delay relative to the last LD of the line (0=1..15=16 LSCLK periods)
  __REG32                       : 4;    // Bits 12:15   - Reserved
  __REG32 CLS_RISE_DELAY        : 8;    // Bits 16:23   - CLS Rise delay relative to the last LD of the line. (0=10, 1=2, 2=3...255=256 LSCLK periods)
  __REG32                       : 2;    // Bits 24:25   - Reserved
  __REG32 PS_RISE_DELAY         : 6;    // Bits 26:31   - PS Rise Delay in LCDC_CLK periods
} __LSCR1_bits ;

typedef struct {        /* PWM Contrast Control Register  (0x0020502C) Reset (0x00000000) */
  __REG32 PW            : 8;    // Bits 0:7     - Controls the pulse-width of the built-in pulse-width modulator, which controls the contrast of the LCD screen.
  __REG32 CC_EN         : 1;    // Bits 8       - Contrast Control Enable
  __REG32 SCR           : 2;    // Bits 9:10    - Selects the input clock source for the PWM. counter.(0=Line pulse, 1=pixel clock, 2=LCD clock )
  __REG32               : 4;    // Bits 11:14   - Reserved
  __REG32 LDMSK         : 1;    // Bit 15       - LD Mask - Enables/Disables the LD output to zero for the Sharp TFT panel power-off sequence.(0=LD[0:15] is normal, 1=LD[0:15] always equals 0)
  __REG32 CLS_HI_WIDTH  : 9;    // Bits 16:24   - CLS High Pulse Width (Actual pulse width is CLS_HI+WIDTH+1)
  __REG32               : 7;    // Bits 25:31   - Reserved
} __PWMR_bits ;

typedef struct {        /* Refresh Mode Control Register  (0x00205034) Reset (0x00000000) */
  __REG32 SELF_REF      : 1;    // Bit 0                - Enables/Disables self-refresh mode.
  __REG32 LCDC_EN       : 1;    // Bit 1                - Enables/Disables the LCDC.
  __REG32               : 30;
} __RMCR_bits;

typedef struct {        /* DMA Control Register  (0x00205030) Reset (0x80080002) */
  __REG32 TM            : 4;    // Bits 0:3     - DMA Trigger Mark
  __REG32               :12;    // Bits 4:15    - Reserved
  __REG32 HM            : 4;    // Bits 16:19   - DMA High Mark
  __REG32               :11;    // Bits 20:30   - Reserved
  __REG32 BURST         : 1;    // Bit 31               - Burst Length (0=Dynamic, 1=Fixed)
} __DMACR_bits;

typedef struct {        /* Interrupt Configuration Register  (0x00205038) Reset (0x00000000) */
  __REG32 INTCON        : 1;    // Bit  0   - Interrupt Condition (0=End of Frame, 1=Beggining of frame)
  __REG32               : 1;    // Bit  1   - Reserved
  __REG32 INTSYN        : 1;    // Bit  2   - Interrupt Source (0= loading last/first data from memory, 1=output of last/first data to LCD panel.
  __REG32               :29;    // Bits 3:31    - Reserved
} __LCDICR_bits;

typedef struct {        /* Interrupt Status Register  (0x00205040) Reset (0x00000000) */
  __REG32 BOFILE                : 1;    // Bit  0       - Beginning of Frame
  __REG32 EOFILE                : 1;    // Bit  1       - End of Frame
  __REG32 ERR_RES               : 1;    // Bit  2       - Error Response
  __REG32 UDR_ERR               : 1;    // Bit  3       - Under Run Error
  __REG32                       :28;    // Bits 4:31    - Reserved
} __LCDISR_bits;


/* -------------------------------------------------------------------------*/
/*      UART (1/2) Control & Status Registers                               */
/* -------------------------------------------------------------------------*/

/* ------------ Receiver Register 0-15  uart1 base (0x00206000) reset 0x0000*/
typedef struct {
  __REG32 RX_DATA               : 8;    // Bits 0-7             - Recieve Data
  __REG32                       : 2;    // Bits 8-9             - Reserved
  __REG32 PRERR                 : 1;    // Bit  10              - Receive Parity Error 1=error
  __REG32 BRK                   : 1;    // Bit  11              - Receive break Caracter detected 1 = detected
  __REG32 FRMERR                : 1;    // Bit  12              - Receive Framing Error 1=error
  __REG32 OVRRUN                : 1;    // Bit  13              - Receive Over run Error 1=error
  __REG32 ERR                   : 1;    // Bit  14              - Receive Error Detect (OVR,FRM,BRK,PR 0=error
  __REG32 CHARRDY               : 1;    // Bit  15              - Receive Character Ready 1=character valid
  __REG32                       : 16;   // Bits 31-16           - Reserved
} __URXD_bits ;

/* ------------ Transmitter Register 0-15       uart1 base(0x00206040) reset 0x0000*/
typedef struct {
  __REG32 TX_DATA               : 8;    // Bits 7-0             - Transmit Data
  __REG32                       : 24;   // Bits 31-16           - Reserved
} __UTXD_bits;

/* ------------ Control Register 1 uart1(0x00206080)uart2(0x00207080) reset 0x0004*/

typedef struct {
  __REG32 UARTEN                : 1;    // Bit  0       - UART Enable 1 = Enable the UART
  __REG32 DOZE                  : 1;    // Bit  1       - DOZE 1 = The UART is disabled when in DOZE state
  __REG32 UARTCLKEN             : 1;    // Bit  2       - UART Clock Enable 1 = enable
  __REG32 TDMAEN                : 1;    // Bit  3       - Transmitter Ready DMA Enable 1 = enable
  __REG32 SNDBRK                : 1;    // Bit  4       - Send BREAK 1 = send break char continuous
  __REG32 RTSDEN                : 1;    // Bit  5       - RTS Delta Interrupt Enable 1 = enable
  __REG32 TXMPTYEN              : 1;    // Bit  6       - Transmitter Empty Interrupt Enable 1 = enable
  __REG32 IREN                  : 1;    // Bit  7       - Infrared Interface Enable 1 = enable
  __REG32 RDMAEN                : 1;    // Bit  8       - Receive Ready DMA Enable 1 = enable
  __REG32 RRDYEN                : 1;    // Bit  9       - Receiver Ready Interrupt Enable 1 = Enable
  __REG32 ICD                   : 2;    // Bit  10-11   - Idle Condition Detect
                                        //              - 00 = Idle for more than 4 frames
                                        //              - 01 = Idle for more than 8 frames
                                        //              - 10 = Idle for more than 16 frames
                                        //              - 11 = Idle for more than 32 frames
  __REG32 IDEN                  : 1;    // Bit  12      - Idle Condition Detected Interrupt en 1=en
  __REG32 TRDYEN                : 1;    // Bit  13      - Transmitter Ready Interrupt Enable 1=en
  __REG32 ADBR                  : 1;    // Bit  14      - AutoBaud Rate Detection enable 1=en
  __REG32 ADEN                  : 1;    // Bit  15      - AutoBaud Rate Detection Interrupt en 1=en
  __REG32                       : 16;
} __UCR1_bits;

/* ------------ Control Register 2      uart1(0x00206084)uart2(0x00207084) reset 0x0001*/
typedef struct {
  __REG32 SRST          : 1;    // Bit  0       -Software Reset 0 = Reset the tx and rx state machines
  __REG32 RXEN          : 1;    // Bit  1       -Receiver Enable 1 = Enable
  __REG32 TXEN          : 1;    // Bit  2       -Transmitter Enable 1= enable
  __REG32               : 1;    // Bit  3       -Reserved
  __REG32 RTSEN         : 1;    // Bit  4       -Request to Send Interrupt Enable 1=enable
  __REG32 WS            : 1;    // Bit  5       -Word Size 0 = 7bit, 1= 8 bit
  __REG32 STPB          : 1;    // Bit  6       -Stop 0= 1 stop bits, 1= 2 stop bits
  __REG32 PROE          : 1;    // Bit  7       -Parity Odd/Even 1=Odd
  __REG32 PREN          : 1;    // Bit  8       -Parity Enable 1=enable parity generator
  __REG32 RTEC          : 2;    // Bits 9-10    -Request to Send Edge Control
                                //              - 00 = Trigger interrupt on a rising edge
                                //              - 01 = Trigger interrupt on a falling edge
                                //              - 1X = Trigger interrupt on any edge
  __REG32 ESCEN         : 1;    // Bit  11      -Escape Enable 1 = Enable escape sequence detection
  __REG32 CTS           : 1;    // Bit  12      -Clear to Send 1 = The UARTx_CTS pin is low (active)
  __REG32 CTSC          : 1;    // Bit  13      -UARTx_CTS Pin controlled by 1= receiver 0= CTS bit
  __REG32 IRTS          : 1;    // Bit  14      -Ignore UARTx_RTS Pin 1=ignore
  __REG32 ESCI          : 1;    // Bit  15      -Escape Sequence Interrupt En 1=enable
  __REG32               : 16;
} __UCR2_bits;

/* ------------ Control Register 3      uart1(0x00206088) reset 0x0000*/
typedef struct {
  __REG32 BPEN          : 1;    // Bit  0       -Preset Registers Enable 0 = The BRM reg not used (normal)
  __REG32 INVT          : 1;    // Bit  1       -Inverted Infrared Transmission 1= active high
  __REG32 REF30         : 1;    // Bit  2       -Reference Frequency 30 MHz 0 = 30 MHz not used
  __REG32 REF25         : 1;    // Bit  3       -Reference Frequency 25 MHz 0 = 25 MHz not used
  __REG32 AWAKEN        : 1;    // Bit  4       -Asynchronous WAKE Interrupt Enable 1= Enable
  __REG32 AIRINTEN      : 1;    // Bit  5       -Asynchronous IR WAKE Interrupt enable 1 = Enable
  __REG32 RXDSEN        : 1;    // Bit  6       -Receive Status Interrupt Enable 1 = Enable
  __REG32               : 4;    // Bits  7-10   -
  __REG32 FRAERREN      : 1;    // Bit  11      -Frame Error Interrupt Enable 1 = Enable
  __REG32 PARERREN      : 1;    // Bit  12      -Parity Error Interrupt Enable 1 = Enable
  __REG32               : 19;
} __UCR3_1_bits;

/* ------------ Control Register 3      uart2(0x00207088) reset 0x0000*/
typedef struct {
  __REG32 BPEN          : 1;    // Bit  0       -Preset Registers Enable 0 = The BRM reg not used (normal)
  __REG32 INVT          : 1;    // Bit  1       -Inverted Infrared Transmission 1= active high
  __REG32 REF30         : 1;    // Bit  2       -Reference Frequency 30 MHz 0 = 30 MHz not used
  __REG32 REF25         : 1;    // Bit  3       -Reference Frequency 25 MHz 0 = 25 MHz not used
  __REG32 AWAKEN        : 1;    // Bit  4       -Asynchronous WAKE Interrupt Enable 1= Enable
  __REG32 AIRINTEN      : 1;    // Bit  5       -Asynchronous IR WAKE Interrupt enable 1 = Enable
  __REG32 RXDSEN        : 1;    // Bit  6       -Receive Status Interrupt Enable 1 = Enable
  __REG32               : 1;    // Bits 7       -reserved
  __REG32 RI            : 1;    // Bit  8       -Ring Indicator 1= pin is logic 1
  __REG32 DCD           : 1;    // Bit  9       -Data Carrier Detect 1= pin is logic 1
  __REG32 DSR           : 1;    // Bit  10      -Data Set Ready 1= pin is logic 1
  __REG32 FRAERREN      : 1;    // Bit  11      -Frame Error Interrupt Enable 1 = Enable
  __REG32 PARERREN      : 1;    // Bit  12      -Parity Error Interrupt Enable 1 = Enable
  __REG32 DTREN         : 1;    // Bit  13      -Data Terminal Ready Interrupt Enable 1= enable
  __REG32 DPEC          : 2;    // Bit  14-15   -DTR Interrupt Edge Control
                                //              00 = Interrupt generated on rising edge
                                //              01 = Interrupt generated on falling edge
                                //              1X = Interrupt generated on either edge
  __REG32               : 16;
} __UCR3_23_bits;

/* ------------ Control Register 4      uart1(0x0020608C)uart2(0x0020708C) reset 0x8040*/
typedef struct {
  __REG32 DREN          : 1;    // Bit  0       -Receive Data Ready Interrupt Enable 1= enable
  __REG32 OREN          : 1;    // Bit  1       -Receiver Overrun Interrupt Enable 1= enable
  __REG32 BKEN          : 1;    // Bit  2       -BREAK Condition Detected Interrupt en 1= enable
  __REG32 TCEN          : 1;    // Bit  3       -Transmit Complete Interrupt Enable1 = Enable
  __REG32               : 1;    // Bit  4       -reserved
  __REG32 IRSC          : 1;    // Bit  5       -IR Special Case vote logic uses 1= uart ref clk
  __REG32 REF16         : 1;    // Bit  6       -Reference Frequency 16 MHz 0= 16MHz not used
  __REG32 WKEN          : 1;    // Bit  7       -WAKE Interrupt Enable 1= enable
  __REG32 ENIRI         : 1;    // Bit  8       -Serial Infrared Interrupt Enable 1= enable
  __REG32 INVR          : 1;    // Bit  9       -Inverted Infrared Reception 1= active high
  __REG32 CTSTL         : 6;    // Bits 10-15   -CTS Trigger Level
                                //              000000 = 0 characters received
                                //              000001 = 1 characters in the RxFIFO
                                //              ...
                                //              100000 = 32 characters in the RxFIFO (maximum)
                                //              All Other Settings Reserved
  __REG32               : 16;
} __UCR4_bits;

/* ------------ FIFO Control Register   uart1(0x00206090)uart2(0x00207090) reset 0x0881*/
typedef struct {
  __REG32 RXTL          : 6;    // Bits 0-5     -Receiver Trigger Level
                                //              000000 = 0 characters received
                                //              000001 = RxFIFO has 1 character
                                //              ...
                                //              011111 = RxFIFO has 31 characters
                                //              100000 = RxFIFO has 32 characters (maximum)
                                //              All Other Settings Reserved
  __REG32               : 1;    // Bit  6       -reserved
  __REG32 RFDIV         : 3;    // Bits 7-9     -Reference Frequency Divider
                                //              000 = Divide input clock by 6
                                //              001 = Divide input clock by 5
                                //              010 = Divide input clock by 4
                                //              011 = Divide input clock by 3
                                //              100 = Divide input clock by 2
                                //              101 = Divide input clock by 1
                                //              110 = Divide input clock by 7
  __REG32 TXTL          : 6;    // Bits 10-15   -Transmitter Trigger Level
                                //              000000 = Reserved
                                //              000001 = Reserved
                                //              000010 = TxFIFO has 2 or fewer characters
                                //              ...
                                //              011111 = TxFIFO has 31 or fewer characters
                                //              100000 = TxFIFO has 32 characters (maximum)
                                //              All Other Settings Reserved
  __REG32                : 16;
} __UFCR_bits;

/* ------------ Status Register 1       uart1(0x00206094)uart2(0x00207094) reset 0x2000*/
typedef struct {
  __REG32               : 4;    // Bits 0-3     -reserved
  __REG32 AWAKE         : 1;    // Bits 4       -Asynchronous WAKE Interrupt Flag1 = A falling edge was detected on the RXD pin
  __REG32 AIRINT        : 1;    // Bits 5       -Asynchronous IR WAKE Interrupt Flag1 = A pulse was detected on RXD
  __REG32 RXDS          : 1;    // Bits 6       -Receiver IDLE Interrupt Flag0 = Receive in progress
  __REG32               : 2;    // Bits 7-8     -reserved
  __REG32 RRDY          : 1;    // Bits 9       -Receiver Ready Interrupt / DMA Flag1 = Character(s) ready
  __REG32 FRAMERR       : 1;    // Bits 10      -Frame Error Interrupt Flag1 = Frame error detected
  __REG32 ESCF          : 1;    // Bits 11      -Escape Sequence Interrupt Flag1 = Escape sequence detected(write 1 to clear)
  __REG32 RTSD          : 1;    // Bits 12      -RTS Delta1 = UARTx_RTS pin changed state (write 1 to clear)
  __REG32 TRDY          : 1;    // Bits 13      -Transmitter Ready Interrupt / DMA Flag1 = The transmitter requires data (interrupt posted)
  __REG32 RTSS          : 1;    // Bits 14      -RTS Pin Status1 = The UARTx_RTS pin is low(active)
  __REG32 PARITYERR     : 1;    // Bits 15      -Parity Error Interrupt Flag1 = Parity error detected
  __REG32               : 16;
} __USR1_bits;

/* ------------ Status Register 2       uart1(0x00206098)uart2(0x00207098) reset 0x4008*/
typedef struct {
  __REG32 RDR           : 1;    // Bit  0       -Receive Data Ready1 = Receive data ready
  __REG32 ORE           : 1;    // Bit  1       -Overrun Error1 = Overrun error (write 1 to clear)
  __REG32 BRCD          : 1;    // Bit  2       -BREAK Condition Detected1 = A BREAK condition was detected (write 1 to clear)
  __REG32 TXDC          : 1;    // Bit  3       -Transmitter Complete1 = Transmit is complete
  __REG32 RTSF          : 1;    // Bit  4       -RTS Edge Triggered Interrupt Flag1 = Programmed edge detected on RTS (write 1 to clear)
  __REG32               : 2;    // Bits 5-6     -reserved
  __REG32 WAKE          : 1;    // Bit  7       -Wake1 = start bit detected (write 1 to clear)
  __REG32 IRINT         : 1;    // Bit  8       -Serial Infrared Interrupt Flag1 = valid edge detected (write 1 to clear)
  __REG32               : 3;    // Bits 9-11    -reserved
  __REG32 IDLE          : 1;    // Bit  12      -Idle Condition1 = Idle condition detected (write 1 to clear)
  __REG32 DTRF          : 1;    // Bit  13      -DTR Edge Triggered Interrupt Flag1 = Programmed edge detected(write 1 to clear)
  __REG32 TXFE          : 1;    // Bit  14      -Transmit Buffer FIFO Empty1 = The transmit buffer (TxFIFO)is empty
  __REG32 ADET          : 1;    // Bit  15      -Automatic Baud Rate Detect Complete1 = ASCII A or a was received(write 1 to clear)
  __REG32               : 16;
} __USR2_bits;

/* ------------ Escape Character Register       uart1(0x0020609C)uart2(0x0020709C) reset 0x002B*/
typedef struct {
  __REG32 ESC_CHAR      : 8;    // Bits 0-7     -UART Escape Character
  __REG32               : 24;
} __UESC_bits;

/* ------------ Escape Timer Register   uart1(0x002060A0)uart2(0x002070A0) reset 0x0000*/
typedef struct {
  __REG32 TIM           : 12;   // Bits 0-11    -UART Escape Timer
  __REG32               : 20;
} __UTIM_bits;

/* ------------ BRM Incremental Register        uart1(0x002060A4)uart2(0x002070A4) reset 0x0000*/
typedef struct {
  __REG32 INC           : 16;   // Bits 0-15    -Incremental Numerator
  __REG32               : 16;
} __UBIR_bits;

/* ------------ BRM Modulator Register  uart1(0x002060A8)uart2(0x002070A8) reset 0x0000*/
typedef struct {
  __REG32 MOD           : 16;   // Bits 0-15    -Modulator Denominator
  __REG32               : 16;
} __UBMR_bits;

/* ------------ Baud Rate Count register        uart1(0x002060AC)uart2(0x002070AC) reset 0x0008*/
typedef struct {
  __REG32 BCNT          : 16;   // Bits 0-15    -Baud Rate Count Register
  __REG32               : 16;
} __UBRC_bits;

/* ------------ BRM Incremental Preset Register 1       uart1(0x002060B0)uart2(0x002070B0) reset 0x????*/
typedef struct {
  __REG32 INCPI         : 16;   // Bits 0-15    -BRM Incremental Preset Register
  __REG32               : 16;
} __BIPR_bits;

/* ------------ BRM Modulator Preset Register 1 uart1(0x002060C0)uart2(0x002070C0) reset 0x????*/
typedef struct {
  __REG32 MODI          : 16;   // Bits 0-15    -BRM MOD Preset Registers
  __REG32               : 16;
} __BMPR_bits;

/* ------------ Test Register 1 uart1(0x002060D0)uart2(0x002070D0) reset 0x0060*/
typedef struct {
  __REG32 SOFTRST       : 1;    // Bit  0       -Software Reset1 = Generate software reset
  __REG32               : 2;    // Bits 1-2     -reserved
  __REG32 RXFULL        : 1;    // Bit  3       -RxFIFO FULL1 = The RxFIFO is full
  __REG32 TXFULL        : 1;    // Bit  4       -TxFIFO FULL1 = The TxFIFO is full
  __REG32 RXEMPTY       : 1;    // Bit  5       -RxFIFO Empty1 = The RxFIFO is empty
  __REG32 TXEMPTY       : 1;    // Bit  6       -TxFIFO Empty1 = The TxFIFO is empty
  __REG32               : 5;    // Bits 7-11    -reserved
  __REG32 LOOP          : 1;    // Bit  12      -Loop TX and RX for Test1 = Internally connect the transmitter output to the receiver input
  __REG32 FRCPERR       : 1;    // Bit  13      -Force Parity Error0 = Generate normal parity
  __REG32               : 18;
} __UTS_bits;


/* -------------------------------------------------------------------------*/
/*      PWM Registers                                                       */
/* -------------------------------------------------------------------------*/

/* PWM control register */
typedef struct {
  __REG32 CLKSEL            :2;
  __REG32 REPEAT            :2;
  __REG32 EN                :1;
  __REG32 FIFOAV            :1;
  __REG32 IRQEN             :1;
  __REG32 IRQ               :1;
  __REG32 PRESCALER         :7;
  __REG32 CLKSRC            :1;
  __REG32 SWR               :1;
  __REG32 BCTR              :1;
  __REG32 HCTR              :1;
  __REG32                   :13;
} __PWMC_bits;

/* PWM sample register */
typedef struct {
  __REG32 SAMPLE            :16;
  __REG32                   :16;
} __PWMS_bits;

/* PWM period register */
typedef struct {
  __REG32 PERIOD            :16;
  __REG32                   :16;
} __PWMP_bits;

/* PWM counter register */
typedef struct {
  __REG32 COUNT             :16;
  __REG32                   :16;
} __PWMCNT_bits;


/* -------------------------------------------------------------------------*/
/*               DMA Registers                                              */
/* -------------------------------------------------------------------------*/

typedef struct {        /* DMA Control Register (0x00209000) Reset (0x0000)                     */
  __REG32 DEN           : 1;    // Bit 0        - DMA Enable - Enables/Disables the system clock to the DMA module.
  __REG32 DRST          : 1;    // Bit 1        - DMA Reset - Writing "1" Generates a 3-cycle reset pulse that resets the entire DMA module
  __REG32               :30;    // Bits 31-2    - Reserved
} __DCR_bits ;

typedef struct {        /* DMA Register Type                                                                            */
  __REG32 CH0           : 1;    // Bit 0        - Channel 0
  __REG32 CH1           : 1;    // Bit 1        - Channel 1
  __REG32 CH2           : 1;    // Bit 2        - Channel 2
  __REG32 CH3           : 1;    // Bit 3        - Channel 3
  __REG32 CH4           : 1;    // Bit 4        - Channel 4
  __REG32 CH5           : 1;    // Bit 5        - Channel 5
  __REG32 CH6           : 1;    // Bit 6        - Channel 6
  __REG32 CH7           : 1;    // Bit 7        - Channel 7
  __REG32 CH8           : 1;    // Bit 8        - Channel 8
  __REG32 CH9           : 1;    // Bit 9        - Channel 9
  __REG32 CH10          : 1;    // Bit 10       - Channel 10
  __REG32               : 21;   // Bits 31-11   - Reserved
} __DISR_bits;

typedef struct {        /* DMA Burst Time-Out Control Register (0x0020901C) Reset (0x00000000) */
  __REG32 CNT           :15;    // Bits 14-0    - Count - Contains the time-out count down value.
  __REG32 EN            : 1;    // Bit 15       - Enable - (0 = burst time-out Disabled, 1 = burst time-out Enabled)
  __REG32               :16;    // Bits 31-16   - Reserved
} __DBTOCR_bits;

typedef struct {
  __REG32 WS            :16;    // Bits 15-0    - W-Size - Contains the number of bytes that make up the display width.
  __REG32               :16;    // Bits 31-16   - Reserved
} __WSR_bits;

/* X-Size Registers */
typedef struct {
  __REG32 XS            :16;    // Bits 15-0    - X-Size - Contains the number of bytes per row that define the X-Size of the 2D memory.
  __REG32               :16;    // Bits 31-16   - Reserved
} __XSR_bits;

/* Y-Size Registers */
typedef struct {
  __REG32 YS            :16;    // Bits 15-0    - Y-Size - Contains the number of rows that make up the 2D memory window.
  __REG32               :16;    // Bits 31-16   - Reserved
} __YSR_bits;

/* Channel Source Address Register */
typedef struct {
  __REG32 SA0           :1;
  __REG32 SA1           :1;
  __REG32 SA            :30;
} __SAR_bits;

/* Destination Address Registers */
typedef struct {
  __REG32 DA0           :1;
  __REG32 DA1           :1;
  __REG32 DA            :30;
} __DAR_bits;

typedef struct { /* DMA Channel Count Register */
  __REG32 CNT           : 24;   // Bits 23-0    - Count - Contains the number of bytes of data to be transferred during a DMA cycle.
  __REG32               : 8;    // Bits 31-24   - Reserved
} __CNTR_bits;

typedef struct {        /* DMA Channel Control Register */
  __REG32 CEN           : 1;    // Bit 0        - DMA Channel Enable (0 = Disables, 1 = Enable)
  __REG32 FRC           : 1;    // Bit 1        - Forces a DMA Cycle to occur (0=No Effect, 1=Force DMA cycle)
  __REG32 RPT           : 1;    // Bit 2        - Repeat - Enables(1)/Disables(0) the data transfer repeat function.
  __REG32 REN           : 1;    // Bit 3        - Request Enable - Enables(1)/Disables(0) the DMA request signal. When REN is set, DMA is started by DMA_REQ[x] signal. When REN is cleared, DMA transfer is initiated by CEN
  __REG32 SSIZ          : 2;    // Bits 5-4     - Source Size - Selects the source size of data transfer. (00=32 Bit port, 01=8-bit port, 10=16-bit port, 11=reserved)
  __REG32 DSIZ          : 2;    // Bits 7-6     - Destination Size - Selects the destination size of a data (00=32 Bit port, 01=8-bit port, 10=16-bit port, 11=reserved)
  __REG32 MSEL          : 1;    // Bit 8        - Memory Select - Selects the 2D memory register set when either source and/or destination is programmed to 2D memory mode. (0=2D memory register set A, 1=2D mem reg set B)
  __REG32 MDIR          : 1;    // Bit 9        - Memory Direction - Selects the memory address direction. (0 = Memory address increment, 1 = Memory address decrement)
  __REG32 SMOD          : 2;    // Bits 11-10   - Source Mode - Selects the source transfer mode (00=Linear Memory, 01=2D Memory, 10=FIFO, 11=End-of-burst enable FIFO)
  __REG32 DMOD          : 2;    // Bits 13-12   - Destination Mode - Selects the destination transfer mode. (00=Linear Memory, 01=2D Memory, 10=FIFO, 11=End-of-burst enable FIFO)
  __REG32               : 18;   // Bits 31-14   - Reserved
} __CCR_bits ;

typedef struct {        /* DMA Channel Request Source Select Register */
  __REG32 RSS           : 5;    // Bits 4-0     - Request Source Select (0=DMA_REQ[0]....31=DMA_REQ[31])
  __REG32               : 27;   // Bits 31-5    - Reserved
} __RSSR_bits ;

typedef struct {        /* DMA Channel Burst Length Register */
  __REG32 BL            : 5;    // Bits 4-0     - Burst Length - Contains the number of data bytes transferred in a DMA burst. (0=64 bytes, 1=1 byte...63 = 63 bytes)
  __REG32               : 27;   // Bits 31-5    - Reserved
} __BLR_bits;

typedef union {
  /* RTOR_CHxy DMA Channel Request Time-Out Register */
  struct{
    __REG32 CNT         : 13;   // Bits 12-0    - Request Time-Out Count - Contains the time-out count down value for the internal counter.
    __REG32 PSC         : 1;    // Bit 13       - Prescaler Count (0=/1, 1=/256)
    __REG32 CLK         : 1;    // Bit 14       - Clock Source - Selects the counter of input clock source. (0 = HCLK, 1 = 32.768 kHz)
    __REG32 EN          : 1;    // Bit 15       - Enable - Enables/Disables the DMA request time-out.
    __REG32             : 16;   // Bits 31-16   - Reserved
  };
  /* BUCR_CHxy Channel Bus Utilization Control Register */
  struct {
    __REG32 CCNT        : 16;   // Bits 15-0;   - Clock Count - Sets the number of system clocks that must occur before the memory channel releases the AHB, before the next DMA request for the channel.
    __REG32             : 16;   // Bits 31-16   - Reserved
  };
} __RTORBUCR_bits ;


/* -------------------------------------------------------------------------*/
/*               SIM Registers                                              */
/* -------------------------------------------------------------------------*/

/* SIM port control register */
typedef struct {
  __REG32 SAPD              :1;
  __REG32 SVEN              :1;
  __REG32 STEN              :1;
  __REG32 SRST              :1;
  __REG32 SCEN              :1;
  __REG32 SCSP              :1;
  __REG32 _3VOLT            :1;
  __REG32                   :25;
} __PORT_CNTL_bits;

/* SIM control register */
typedef struct {
  __REG32 IC                :1;
  __REG32 ICM               :1;
  __REG32 ANACK             :1;
  __REG32 ONACK             :1;
  __REG32 CLK_SEL           :3;
  __REG32 BAUD_SEL          :3;
  __REG32 GPCNT_CLK_SEL     :2;
  __REG32 CWTEN             :1;
  __REG32 LRCEN             :1;
  __REG32 CRCEN             :1;
  __REG32 XMT_CRC_LRC       :1;
  __REG32                   :16;
} __CNTL_bits;

/* SIM receive threshold register */
typedef struct {
  __REG32 RDT               : 5;
  __REG32                   : 27;
} __RCV_THRESHOLD_bits;

/* SIM transmit/receive enable register */
typedef struct {
  __REG32 SIM_EN              : 1;
  __REG32 RCV_EN              : 1;
  __REG32 XMT_EN              : 1;
  __REG32                     : 29;
} __ENABLE_bits;

/* SIM transmit status register */
typedef struct {
  __REG32 XTE                 : 1;
  __REG32 TFE                 : 1;
  __REG32 ETC                 : 1;
  __REG32 TC                  : 1;
  __REG32 TFO                 : 1;
  __REG32 TDTF                : 1;
  __REG32 GPCNT               : 1;
  __REG32                     : 25;
} __XMT_STATUS_bits;

/* SIM receive status register */
typedef struct {
  __REG32 OEF                 : 1;
  __REG32 RFD                 : 1;
  __REG32 RDRF                : 1;
  __REG32 LRCOK               : 1;
  __REG32 CRCOK               : 1;
  __REG32 CWT                 : 1;
  __REG32                     : 26;
} __RCV_STATUS_bits;

/* SIM interrupt mask register */
typedef struct {
  __REG32 RIM                 : 1;
  __REG32 TCIM                : 1;
  __REG32 OIM                 : 1;
  __REG32 ETCIM               : 1;
  __REG32 TFEIM               : 1;
  __REG32 XTM                 : 1;
  __REG32 TFOM                : 1;
  __REG32 TDTFM               : 1;
  __REG32 GPCNTM              : 1;
  __REG32 CWTM                : 1;
  __REG32                     : 22;
} __SIM_INT_MASK_bits;

/* SIM port transmit buffer register */
typedef struct {
  __REG32 XMT                 : 8;
  __REG32                     : 24;
} __XMT_BUF_bits;

/* SIM port receive buffer register */
typedef struct {
  __REG32 RCV                 : 8;
  __REG32 PE                  : 1;
  __REG32 FE                  : 1;
  __REG32                     : 22;
} __RCV_BUF_bits;

/* SIM port detect register */
typedef struct {
  __REG32 SDIM                : 1;
  __REG32 SDI                 : 1;
  __REG32 SPDP                : 1;
  __REG32 SPDS                : 1;
  __REG32                     : 28;
} __PORT_DETECT_bits;

/* SIM transmit threshold register */
typedef struct {
  __REG32 TDT                 : 4;
  __REG32 XTH                 : 4;
  __REG32                     : 24;
} __XMT_THRESHOLD_bits;

/* SIM transmit guard control register */
typedef struct {
  __REG32 GETU                : 8;
  __REG32 RCVR11              : 1;
  __REG32                     : 23;
} __GUARD_CNTL_bits;

/* SIM open drain configuration control register */
typedef struct {
  __REG32 OD_P                : 1;
  __REG32                     : 31;
} __OD_CONFIG_bits;

/* SIM reset control register */
typedef struct {
  __REG32 FLUSH_RCV           : 1;
  __REG32 FLUSH_XMT           : 1;
  __REG32 SOFT_RESET          : 1;
  __REG32                     : 29;
} __RESET_CNTL_bits;

/* SIM character wait time register */
typedef struct {
  __REG32 TIME                : 16;
  __REG32                     : 16;
} __CHAR_WAIT_bits;

/* SIM general purpose counter register */
typedef struct {
  __REG32 GPCNT               : 16;
  __REG32                     : 16;
} __GPCNT_bits;

/* SIM divisor register */
typedef struct {
  __REG32 DIVISOR             : 7;
  __REG32                     : 25;
} __DIVISOR_bits;


/* -------------------------------------------------------------------------*/
/*      USB Registers                                                       */
/* -------------------------------------------------------------------------*/

/* ------------  USB Frame Number and Match Register  (0x00212000) reset 0x0000 0x0000 */
typedef struct {
  __REG32 FRAME         : 11;   // Bits 0-10    - Frame Field
  __REG32               : 5;    // Bits 11-15   - reserved
  __REG32 MATCH         : 11;   // Bit  16-26   - Match Field
  __REG32               : 5;
}__USB_FRAME_bits;

/* ------------ USB Specification and Release Number Register   (0x00212004) reset 0x0000 0x0110*/
typedef struct {
  __REG32 SPEC          : 12;   // Bits 0-11    - Specification Number
  __REG32               : 20;
}__USB_SPEC_bits;

/* ------------ USB Status Register     (0x00212008) reset 0x0000 0x0000*/
typedef struct {
  __REG32 ALTSET        : 3;    // Bits 0-2     - Alternate Setting
  __REG32 INTF          : 2;    // Bits 3-4     - Interface
  __REG32 CFG           : 2;    // Bits 5-6     - Configuration
  __REG32 SUSP          : 1;    // Bits 7       - Suspend1 = USB is suspended
  __REG32 RST           : 1;    // Bits 8       - Reset Signaling0 = Normal signaling in progress on USB
  __REG32               : 23;
}__USB_STAT_bits;

/* ------------ USB Control Register    (0x0021200C) reset 0x0000 0x0010*/
typedef struct {
  __REG32 RESUME        : 1;    // Bit  0       - Resume1 = Initiate resume signaling when wake enabled
  __REG32 AFE_ENA       : 1;    // Bit  1       - Analog Front-End Enable1 = AFE enabled
  __REG32 UDC_RST       : 1;    // Bit  2       - UDC Reset1 = Hard reset of the UDC
  __REG32 USB_ENA       : 1;    // Bit  3       - USB Enable1 = USB module front-end logic is enabled
  __REG32 USB_SPD       : 1;    // Bit  4       - USB Speed0 = Low speed,1 = Full speed
  __REG32 CMD_ERROR     : 1;    // Bit  5       - Command Error1 = If the command was processed,an error occurred
  __REG32 CMD_OVER      : 1;    // Bit  6       - Command Over1 = Command in process
  __REG32               : 25;
}__USB_CTRL_bits;

/* ------------ USB Descriptor RAM Address Register     (0x00212010) reset 0x8000 0x0000*/
typedef struct {
  __REG32 DADR          : 9;    // Bits 0-8     - Desired RAM Address
  __REG32               : 21;   // Bits 9-29    - reserved
  __REG32 BSY           : 1;    // Bit  30      - Busy1 = A write is in progress
  __REG32 CFG           : 1;    // Bit  31      - Configuration1 = write toUSB_DDAT register enabled
}__USB_DADR_bits;

/* ------------ USB Descriptor RAM/Endpoint Buffer Data Register        (0x00212014) reset 0x0000 0x0000*/
typedef struct {
  __REG32 DDAT          : 8;    // Bits 0-7     - DDAT Descriptor write data
  __REG32               : 24;
}__USB_DDAT_bits;

/* ------------ USB Interrupt Status Register   (0x00212018) reset 0x0000 0x0000*/
typedef struct {
  __REG32 CFG_CHG       : 1;    // Bit  0       - Configuration Change1 = Configuration change occurred
  __REG32 FRAME_MATCH   : 1;    // Bit  1       - Frame Match1 = Match occurred
  __REG32 SUSP          : 1;    // Bit  2       - Active to Suspend1 = USB is suspended
  __REG32 RES           : 1;    // Bit  3       - Suspend to Resume1 = USB has left the suspend state
  __REG32 RESET_START   : 1;    // Bit  4       - Reset Signaling Start1 = Reset signaling in progress
  __REG32 RESET_STOP    : 1;    // Bit  5       - Reset Signaling Stop1 = Reset signaling has stopped
  __REG32 SOF           : 1;    // Bit  6       - Start-of-Frame Interrupt1 = The UDE received a sof token (the USB frame number is current)
  __REG32 MSOF          : 1;    // Bit  7       - Missed Start-of-Frame Interrupt1 = A SOF interrupt was set,
  __REG32               : 23;   // Bits 8-29    - Reserved
  __REG32 WAKEUP        : 1;    // Bit  31      - Wakeup1 = USB has changed state from suspend to resume (wakeup)
}__USB_INTR_bits;

/* ------------ USB Interrupt Mask Register     (0x00212000) reset 0x8000 0x00FF*/
typedef struct {
  __REG32 CFG_CHG       : 1;    // Bit  0       - Configuration Change1 = Interrupt disabled (masked)
  __REG32 FRAME_MATCH   : 1;    // Bit  1       - Frame Match1 = Interrupt disabled (masked)
  __REG32 SUSP          : 1;    // Bit  2       - Active to Suspend1 = Interrupt disabled (masked)
  __REG32 RES           : 1;    // Bit  3       - Suspend to Resume1 = Interrupt disabled (masked)
  __REG32 RESET_START   : 1;    // Bit  4       - Reset Signaling Start1 = Interrupt disabled (masked)
  __REG32 RESET_STOP    : 1;    // Bit  5       - Reset Signaling Stop1 = Interrupt disabled (masked)
  __REG32 SOF           : 1;    // Bit  6       - Start-of-Frame Interrupt1 = Interrupt disabled (masked)
  __REG32 MSOF          : 1;    // Bit  7       - Missed Start-of-Frame Interrupt1 = Interrupt disabled (masked)
  __REG32               : 23;   // Bits 8-29    - Reserved
  __REG32 WAKEUP        : 1;    // Bit  31      - Wakeup1 = Interrupt disabled (masked)
}__USB_MASK_bits;

/* ------------ USB Enable Register     (0x00212024) reset 0x0000 0x0000*/
typedef struct {
  __REG32 TSIZE         : 1;    // Bit  0       - USB_EPn_FDAT Register Size, USB_EPn_FDAT is 1=8 bits 0= 32 bits wide
  __REG32               : 27;   // Bits 1-27    - Reserved
  __REG32 ENDIAN_MODE   : 1;    // Bit  28      - Endian Mode Select1 = USBd Module is in Little Endian mode
  __REG32 SUSPEND       : 1;    // Bit  29      - Suspend1 = Module is in suspend state
  __REG32 ENAB          : 1;    // Bit  30      - Enable1 = Enable the USB
  __REG32 RST           : 1;    // Bit  31      - Reset1 = USB reset in progress
}__USB_ENAB_bits;

/* ------------ Endpoint Status/Control Register        reset 0x0000 0x0000*/
typedef struct {
  __REG32 FORCE_STALL   : 1;    // Bit  0       - 1 = Force a stall condition
  __REG32 FLUSH         : 1;    // Bit  1       - 1 = Initiate flush operation
  __REG32 ZLPS          : 1;    // Bit  2       - Zero Length Packet Send1 = A zero length packet to send
  __REG32 TYP           : 2;    // Bits 3-4     - Endpoint Type
                                //              - 00 = Control
                                //              - 01 = Isochronous
                                //              - 10 = Bulks
                                //              - 11 = Interrupt
  __REG32 MAX           : 2;    // Bits 5-6     - Maximum Packet Size Sets
                                //              - 00 = Packet is 8 Bytes
                                //              - 01 = Packet is 16 Bytes
                                //              - 10 = Packet is 32 Bytes
                                //              - 11 = Packet is 64 Bytes
  __REG32 DIR           : 1;    // Bit  7       - Transfer Direction 1 = IN endpoint(from device to host)
  __REG32 SIP           : 1;    // Bit  8       - Setup Packet In Progress1 = Setup data is currently being transferred from host to device
  __REG32               : 7;    // Bits 9-15    - Reserved
  __REG32 BYTE_COUNT    : 7;    // Bits 16-22   - Byte Count of FIFO
  __REG32               : 9;
}__USB_EP_STAT_bits;

/* ------------ Endpoint Interrupt Status Register      reset 0x0000 0x0080*/
typedef struct {
  __REG32 _EOF          : 1;    // Bit  0       - End-of-Frame1 = End-of-frame packet sent/received
                                //                Renamed to avoid name clash with the EOF constant in stdio.h
  __REG32 DEVREQ        : 1;    // Bit  1       - Device Request1 = Request pending
  __REG32 EOT           : 1;    // Bit  2       - End-of-TransferLast packet 0=not sent/received 1= sent/received
  __REG32 MDEVREQ       : 1;    // Bit  3       - Multiple Device Requests1 = Multiple setup packets pending
  __REG32 FIFO_LOW      : 1;    // Bit  4       - number of bytes in FIFO 0= <4xGR 1= ALRM
  __REG32 FIFO_HIGH     : 1;    // Bit  5       - number of bytes in FIFO 0= <GR 1= ALRM
  __REG32 FIFO_ERROR    : 1;    // Bit  6       - 1 = Error condition pending
  __REG32 FIFO_EMPTY    : 1;    // Bit  7       - 1 = The FIFO is empty
  __REG32 FIFO_FULL     : 1;    // Bit  8       - 1 = The FIFO is full
  __REG32               : 23;
}__USB_EP_INTR_bits;

/* ------------ Endpoint Interrupt Mask Register        reset 0x0000 0x01FF*/
typedef struct {
  __REG32 _EOF          : 1;    // Bit  0       - End-of-Frame1 = Interrupt disabled (masked)
                                //                Renamed to avoid name clash with the EOF constant in stdio.h
  __REG32 DEVREQ        : 1;    // Bit  1       - Device Request1 = Interrupt disabled (masked)
  __REG32 EOT           : 1;    // Bit  2       - End-of-Transfer1 = Interrupt disabled (masked)
  __REG32 MDEVREQ       : 1;    // Bit  3       - Multiple Device Requests1 = Interrupt disabled (masked)
  __REG32 FIFO_LOW      : 1;    // Bit  4       - 1 = Interrupt disabled (masked)
  __REG32 FIFO_HIGH     : 1;    // Bit  5       - 1 = Interrupt disabled (masked)
  __REG32 FIFO_ERROR    : 1;    // Bit  6       - 1 = Interrupt disabled (masked)
  __REG32 FIFO_EMPTY    : 1;    // Bit  7       - 1 = Interrupt disabled (masked)
  __REG32 FIFO_FULL     : 1;    // Bit  8       - 1 = Interrupt disabled (masked)
  __REG32               : 23;
}__USB_EP_MASK_bits;

/* ------------ Endpoint FIFO Status Register   reset 0x0001 0x0000*/
typedef struct {
  __REG32               : 16;   // Bits 0-15    - Reserved
  __REG32 EMPTY         : 1;    // Bit  16      - FIFO Empty1 = The FIFO is empty
  __REG32 ALARM         : 1;    // Bit  17      - FIFO Alarm1 = The alarm is set
  __REG32 FULL          : 1;    // Bit  18      - FIFO Full1 = The FIFO is full
  __REG32 FR            : 1;    // Bit  19      - Frame Ready1 = One or more complete frames exists in the FIFO
  __REG32 UF            : 1;    // Bit  20      - FIFO Overflow1 = Write pointer has passed the read pointer
  __REG32 OF            : 1;    // Bit  21      - FIFO Underflow1 = Read pointer has passed the write pointer
  __REG32 ERROR         : 1;    // Bit  22      - FIFO Error1 = Underflow, overflow, pointer out of bounds, or other error condition occurred
  __REG32               : 1;    // Bit  23      - Reserved
  __REG32 FRAME3        : 1;    // Bit  24      - Frame Status Bit 3 1 = A frame boundary has occurred on the [7:0] byte of the bus
  __REG32 FRAME2        : 1;    // Bit  25      - Frame Status Bit 2 1 = A frame boundary has occurred on the [15:8] byte of the bus
  __REG32 FRAME1        : 1;    // Bit  26      - Frame Status Bit 1 1 = A frame boundary has occurred on the [23:16] byte of the bus
  __REG32 FRAME0        : 1;    // Bit  27      - Frame Status Bit 0 A frame boundary has occurred on the [31:24] byte of the bus
  __REG32               : 4;
}__USB_EP_FSTAT_bits;

/* ------------ Endpoint FIFO Control Register  reset 0x0100 0x0000*/
typedef struct {
  __REG32               : 24;   // Bits 0-23    - Reserved
  __REG32 GR            : 3;    // Bits 24-26   - Granularity
                                //              - 000 = FIFO has 1 data byte or 1 free location
                                //              - 001 = FIFO has 2 data bytes or 2 free locations
                                //              - 010 = FIFO has 3 data bytes or 3 free locations
                                //              - 011 = FIFO has 4 data bytes or 4 free locations
                                //              - 100 = FIFO has 5 data bytes or 5 free locations
                                //              - 101 = FIFO has 6 data bytes or 6 free locations
                                //              - 110 = FIFO has 7 data bytes or 7 free locations
                                //              - 111 = FIFO has 8 data bytes or 8 free locations
  __REG32 FRAME         : 1;    // Bit  27      - Frame Mode 1 = Frame mode enabled
  __REG32               : 1;    // Bit  28      - Reserved
  __REG32 WFR           : 1;    // Bit  29      - Write Frame End 1 = Next write to FIFO data register is the end-of-frame
  __REG32               : 2;
}__USB_EP_FCTRL_bits;

/* ------------ Endpoint Last Read Frame Pointer Register       reset 0x0000 0x0000*/
typedef struct {
  __REG32 LRFP          : 6;    // Bits 0-5     - Last Read Frame Pointer
  __REG32               : 26;
}__USB_EP_LRFP_bits;

/* ------------ Endpoint Last Write Frame Pointer Register      reset 0x0000 0x0000*/
typedef struct {
  __REG32 LWFP          : 6;    // Bits 0-5     - Last Write Frame Pointer
  __REG32               : 26;
}__USB_EP_LWFP_bits;

/* ------------ Endpoint FIFO Alarm Register    reset 0x0000 0x0000*/
typedef struct {
  __REG32 ALRM          : 6;    // Bits 0-5     - Alarm Information
                                //              - 0x00 = 1 data byte left or 1 free byte available
                                //              - 0x01 = 2 data bytes left or 2 free bytes available
                                //              - ...
                                //              - 0x3F = 64 data bytes left or 64 free bytes available
  __REG32               : 26;
}__USB_EP_FALRM_bits;

/* ------------ Endpoint FIFO Read Pointer Register     reset 0x0000 0x0000*/
typedef struct {
  __REG32 RP            : 6;    // Bits 0-5     - Read Pointer
  __REG32               : 26;
}__USB_EP_FRDP_bits;

/* ------------ Endpoint FIFO Write Pointer Register    reset 0x0000 0x0000*/
typedef struct {
  __REG32 WP            : 6;    // Bits 0-5     - Write Pointer
  __REG32               : 26;
}__USB_EP_FWRP_bits;


/* -------------------------------------------------------------------------*/
/*      SPI Registers                                                       */
/* -------------------------------------------------------------------------*/

/* SPI receive/transmit data registers */
typedef struct {
  __REG32 DATA                : 16;
  __REG32                     : 16;
} __RXTXDATAREG_bits;

/* SPI control registers */
typedef struct {
  __REG32 BIT_COUNT           : 4;
  __REG32 POL                 : 1;
  __REG32 PHA                 : 1;
  __REG32 SSCTL               : 1;
  __REG32 SSPOL               : 1;
  __REG32 XCH                 : 1;
  __REG32 SPIEN               : 1;
  __REG32 MODE                : 1;
  __REG32 DRCTL               : 2;
  __REG32 DATARATE            : 3;
  __REG32                     : 16;
} __CONTROLREG_bits;

/* SPI interrupt control/status registers */
typedef struct {
  __REG32 TE                  : 1;
  __REG32 TH                  : 1;
  __REG32 TF                  : 1;
  __REG32 RR                  : 1;
  __REG32 RH                  : 1;
  __REG32 RF                  : 1;
  __REG32 RO                  : 1;
  __REG32 BO                  : 1;
  __REG32 TEEN                : 1;
  __REG32 THEN                : 1;
  __REG32 TFEN                : 1;
  __REG32 RREN                : 1;
  __REG32 RHEN                : 1;
  __REG32 RFEN                : 1;
  __REG32 ROEN                : 1;
  __REG32 BOEN                : 1;
  __REG32                     : 16;
} __INTREG_bits;

/* SPI test registers */
typedef struct {
  __REG32 TXCNT               : 4;
  __REG32 RXCNT               : 4;
  __REG32 SSTATUS             : 4;
  __REG32                     : 2;
  __REG32 LBC                 : 1;
  __REG32                     : 17;
} __TESTREG_bits;

/* SPI sample period control registers */
typedef struct {
  __REG32 WAIT                : 15;
  __REG32 CSRC                : 1;
  __REG32                     : 16;
} __PERIODREG_bits;

/* SPI DMA control registers */
typedef struct {
  __REG32                     : 4;
  __REG32 RHDMA               : 1;
  __REG32 RFDMA               : 1;
  __REG32 TEDMA               : 1;
  __REG32 THDMA               : 1;
  __REG32                     : 4;
  __REG32 RHDEN               : 1;
  __REG32 RFDEN               : 1;
  __REG32 TEDEN               : 1;
  __REG32 THDEN               : 1;
  __REG32                     : 16;
} __DMAREG_bits;

/* SPI soft reset registers */
typedef struct {
  __REG32 START               : 1;
  __REG32                     : 31;
} __RESETREG_bits;


/* -------------------------------------------------------------------------*/
/*      MMC/SDHC Registers                                                  */
/* -------------------------------------------------------------------------*/

/* MMC/SD Clock control register */
typedef struct {
  __REG32 STOP_CLK            : 1;
  __REG32 START_CLK           : 1;
  __REG32 MMCSD_ENABLE        : 1;
  __REG32 MMCSD_RESET         : 1;
  __REG32                     : 1;
  __REG32 ENDIAN              : 1;
  __REG32                     : 26;
} __STR_STP_CLK_bits;

/* MMC/SD Status register */
typedef struct {
  __REG32 TIME_OUT_READ       : 1;
  __REG32 TIME_OUT_RESP       : 1;
  __REG32 CRC_WRITE_ERR       : 1;
  __REG32 CRC_READ_ERR        : 1;
  __REG32                     : 1;
  __REG32 RESP_CRC_ERR        : 1;
  __REG32 APPL_BUFF_FE        : 1;
  __REG32 APPL_BUFF_FF        : 1;
  __REG32 CARD_BUS_CLK_RUN    : 1;
  __REG32 WR_CRC_ERROR_CODE   : 2;
  __REG32 DATA_TRANS_DONE     : 1;
  __REG32 WRITE_OP_DONE       : 1;
  __REG32 END_CMD_RESP        : 1;
  __REG32 SDIO_INT_ACTIVE     : 1;
  __REG32 CARD_PRESENCE       : 1;
  __REG32                     : 16;
} __STATUS_bits;

/* MMC/SD clock rate register */
typedef struct {
  __REG32 RATE                : 3;
  __REG32 PRESCALER           : 3;
  __REG32                     : 26;
} __CLK_RATE_bits;

/* MMC/SD command and data control register */
typedef struct {
  __REG32 FORMAT_OF_RESPONSE  : 3;
  __REG32 DATA_ENABLE         : 1;
  __REG32 WRITE_READ          : 1;
  __REG32 STREAM_BLOCK        : 1;
  __REG32 BUSY                : 1;
  __REG32 INIT                : 1;
  __REG32 BUS_WIDTH           : 2;
  __REG32 START_READWAIT      : 1;
  __REG32 STOP_READWAIT       : 1;
  __REG32 CMD_RESP_LONG_OFF   : 1;
  __REG32                     : 19;
} __CMD_DAT_CONT_bits;

/* MMC/SD response time out register */
typedef struct {
  __REG32 RESPONSE_TIME_OUT   : 8;
  __REG32                     : 24;
} __RES_TO_bits;

/* MMC/SD read time out register */
typedef struct {
  __REG32 DATA_READ_TIME_OUT  : 16;
  __REG32                     : 16;
} __READ_TO_bits;

/* MMC/SD block length register */
typedef struct {
  __REG32 BLOCK_LENGTH        : 10;
  __REG32                     : 22;
} __BLK_LEN_bits;

/* MMC/SD number of blocks register */
typedef struct {
  __REG32 NOB                 : 16;
  __REG32                     : 16;
} __NOB_bits;

/* MMC/SD revision number register */
typedef struct {
  __REG32 REVISION_NUMBER     : 16;
  __REG32                     : 16;
} __REV_NO_bits;

/* MMC/SD Interrupt mask register */
typedef struct {
  __REG32 DATA_TRAN           : 1;
  __REG32 WRITE_OP_DONE       : 1;
  __REG32 END_CMD_RES         : 1;
  __REG32 BUF_READY           : 1;
  __REG32 SDIO                : 1;
  __REG32 DAT0_EN             : 1;
  __REG32 AUTO_CARD_DETECT    : 1;
  __REG32                     : 25;
} __MMCSD_INT_MASK_bits;

/* MMC/SD command number register */
typedef struct {
  __REG32 COMMAND_NUMBER      : 6;
  __REG32                     : 26;
} __CMD_bits;

/* MMC/SD higher argument register */
typedef struct {
  __REG32 ARGUMENT_HIGH       : 16;
  __REG32                     : 16;
} __ARGH_bits;

/* MMC/SD lower argument register */
typedef struct {
  __REG32 ARGUMENT_LOW        : 16;
  __REG32                     : 16;
} __ARGL_bits;

/* MMC/SD response FIFO register */
typedef struct {
  __REG32 RESPONSE_CONTENT    : 16;
  __REG32                     : 16;
} __RES_FIFO_bits;

/* MMC/SD buffer access register */
typedef struct {
  __REG32 FIFO_CONTENT    : 16;
  __REG32                     : 16;
} __BUFFER_ACCESS_bits;


/* -------------------------------------------------------------------------*/
/*      ASP Registers                                                       */
/* -------------------------------------------------------------------------*/

/* ASP control register */
typedef struct {
  __REG32 BGE                 : 1;
  __REG32 PADE                : 1;
  __REG32                     : 2;
  __REG32 SW1                 : 1;
  __REG32 SW2                 : 1;
  __REG32 SW3                 : 1;
  __REG32 SW4                 : 1;
  __REG32 SW5                 : 1;
  __REG32 SW6                 : 1;
  __REG32 SW7                 : 1;
  __REG32 SW8                 : 1;
  __REG32 MOD                 : 2;
  __REG32 AUTO                : 1;
  __REG32 AZE                 : 1;
  __REG32                     : 4;
  __REG32 AZ_SEL              : 1;
  __REG32 U_SEL               : 1;
  __REG32                     : 1;
  __REG32 SWRST               : 1;
  __REG32                     : 1;
  __REG32 CLKEN               : 1;
  __REG32 ACAL                : 1;
  __REG32 ASWB                : 1;
  __REG32                     : 4;
} __ASP_ACNTLCR_bits;

/* ASP Pen A/D sample control  register */
typedef struct {
  __REG32 DSCNT               : 4;
  __REG32 IDLECNT             : 6;
  __REG32 BIT_SELECT          : 2;
  __REG32 DMCNT               : 3;
  __REG32                     : 17;
} __ASP_PSMPLRG_bits;

/* ASP compare control register */
typedef struct {
  __REG32 VALUE               : 16;
  __REG32 INSEL               : 2;
  __REG32 CC                  : 1;
  __REG32 INT                 : 1;
  __REG32                     : 12;
} __ASP_CMPCNTL_bits;

/* ASP interrupt control register */
typedef struct {
  __REG32 PDRE                : 1;
  __REG32 PFFE                : 1;
  __REG32                     : 2;
  __REG32 PIRQE               : 1;
  __REG32 EDGE                : 1;
  __REG32 POL                 : 1;
  __REG32                     : 3;
  __REG32 PUIE                : 1;
  __REG32                     : 21;
} __ASP_ICNTLR_bits;

/* ASP interrupt/error status register */
typedef struct {
  __REG32 PDR                 : 1;
  __REG32 PFF                 : 1;
  __REG32                     : 4;
  __REG32 PEN                 : 1;
  __REG32 POV                 : 1;
  __REG32                     : 2;
  __REG32 PUIS                : 1;
  __REG32                     : 21;
} __ASP_ISTATR_bits;

/* ASP pen sample fifo register */
typedef struct {
  __REG32 SAMPLE              : 16;
  __REG32                     : 16;
} __ASP_PADFIFO_bits;

/* ASP clock divide register */
typedef struct {
  __REG32 PADC_CLK            : 5;
  __REG32                     : 27;
} __ASP_CLKDIV_bits;

/* ASP FIFO pointer register */
typedef struct {
  __REG32 PEN_FIFO_WRITE_POINTER: 4;
  __REG32 PEN_FIFO_READ_POINTER : 4;
  __REG32                       : 24;
} __ASP_FIFO_PTR_bits;


/* -------------------------------------------------------------------------*/
/*      BTA Registers                                                       */
/* -------------------------------------------------------------------------*/

/* BTA command/status register */
typedef union {
  /* COMMAND register */
  struct {
    __REG32 CMD                 : 2;
    __REG32 CMD_MS              : 1;
    __REG32 IDP                 : 1;
    __REG32                     : 1;
    __REG32 CWS                 : 1;
    __REG32 OS                  : 1;
    __REG32                     : 5;
    __REG32 PIPE                : 1;
    __REG32 EFI                 : 1;
    __REG32 EHI                 : 1;
    __REG32 AAO                 : 1;
    __REG32                     : 16;
  };
  /* STATUS register */
  struct {
    __REG32 BUF_ADDR            : 3;
    __REG32 STATE               : 3;
    __REG32 STS_MS              : 1;
    __REG32                     : 2;
    __REG32 HEC8                : 1;
    __REG32 CRC16               : 1;
    __REG32 NREC                : 1;
    __REG32 REC2                : 1;
    __REG32 REC1                : 1;
    __REG32 MS2LSB              : 2;
    __REG32                     : 16;
  };
} __COMMANDSTATUS_bits;

/* BTA packet header register */
typedef struct {
  __REG32 AM_ADDR             : 3;
  __REG32 TYPE                : 4;
  __REG32 FLOW                : 1;
  __REG32 ARQN                : 1;
  __REG32 SEQN                : 1;
  __REG32                     : 22;
} __PACKET_HEADER_bits;

/* BTA payload header register */
typedef struct {
  __REG32 L_CH                : 2;
  __REG32 FLOW                : 1;
  __REG32 LENGTH              : 9;
  __REG32                     : 20;
} __PAYLOAD_HEADER_bits;

/* BTA native count register */
typedef struct {
  __REG32 NATIVE_COUNT        : 12;
  __REG32                     : 20;
} __NATIVE_COUNT_bits;

/* BTA estimated count register */
typedef struct {
  __REG32 ESTIMATED_COUNT     : 12;
  __REG32                     : 20;
} __ESTIMATED_COUNT_bits;

/* BTA offset count register */
typedef struct {
  __REG32 OFFSET_COUNT        : 12;
  __REG32                     : 20;
} __OFFSET_COUNT_bits;

/* BTA native clock low register */
typedef struct {
  __REG32 NATIVECLK_LOW       : 16;
  __REG32                     : 16;
} __NATIVECLK_LOW_bits;

/* BTA native clock high register */
typedef struct {
  __REG32 NATIVECLK_HIGH      : 12;
  __REG32                     : 20;
} __NATIVECLK_HIGH_bits;

/* BTA estimated clock low register */
typedef struct {
  __REG32 ESTIMATED_CLK_LOW   : 16;
  __REG32                     : 16;
} __ESTIMATED_CLK_LOW_bits;

/* BTA estimated clock high register */
typedef struct {
  __REG32 ESTIMATED_CLK_HIGH  : 12;
  __REG32                     : 20;
} __ESTIMATED_CLK_HIGH_bits;

/* BTA offset clock low register */
typedef struct {
  __REG32 OFFSET_CLK_LOW      : 16;
  __REG32                     : 16;
} __OFFSET_CLK_LOW_bits;

/* BTA offset clock high register */
typedef struct {
  __REG32 OFFSET_CLK_HIGH     : 12;
  __REG32                     : 20;
} __OFFSET_CLK_HIGH_bits;

/* BTA HECCRC control register */
typedef struct {
  __REG32 HECCRC_INIT         : 16;
  __REG32                     : 16;
} __HECCRC_CONTROL_bits;

/* BTA white control register */
typedef struct {
  __REG32 WHITE_INIT          : 6;
  __REG32                     : 26;
} __WHITE_CONTROL_bits;

/* BTA encryption control x13 register */
typedef struct {
  __REG32 ENCRYPT             : 16;
  __REG32                     : 16;
} __ENCRYPTION_CONTROL_X13_bits;

/* BTA correlation time stamp/setup register */
typedef union {
  //CORRELATION_TIME_SETUP
  struct {
    __REG32 EST_PRELOAD_TIME    : 10;
    __REG32                     : 22;
  };
  //CORRELATION_TIME_STAMP
  struct {
    __REG32 CORR_TIME           : 12;
    __REG32                     : 20;
  };
} __CORRELATION_TIME_STAMPSETUP_bits;

/* BTA RF GPO register */
typedef struct {
  __REG32 GPO_DOUT1           : 1;
  __REG32 GPO_DOUT2           : 1;
  __REG32                     : 2;
  __REG32 GPO_EN1             : 1;
  __REG32 GPO_EN2             : 1;
  __REG32                     : 26;
} __RF_GPO_bits;

/* BTA PWM received signal strength register */
typedef struct {
  __REG32 PWM_RSSI            : 6;
  __REG32                     : 26;
} __PWM_RSSI_bits;

/* BTA Time A & B register */
typedef struct {
  __REG32 TIME_A              : 8;
  __REG32 TIME_B              : 8;
  __REG32                     : 16;
} __TIME_A_B_bits;

/* BTA Time C & D register */
typedef struct {
  __REG32 TIME_C              : 5;
  __REG32                     : 3;
  __REG32 TIME_D              : 5;
  __REG32                     : 19;
} __TIME_C_D_bits;

/* BTA PWM TX register */
typedef struct {
  __REG32 PWM_TX              : 6;
  __REG32                     : 26;
} __PWM_TX_bits;

/* BTA RF control/status register */
typedef struct {
  __REG32 DELAY_HOP_STROBE    : 3;
  __REG32 BT11_AUTO_SPIKE     : 1;
  __REG32 BT1_CONT            : 1;
  __REG32 BT5_OE              : 1;
  __REG32 PWM_TX_EN           : 1;
  __REG32 RSSI_EN             : 1;
  __REG32 PEAK_HLD            : 1;
  __REG32 SEL                 : 1;
  __REG32 DIV                 : 1;
  __REG32 CLE                 : 1;
  __REG32 TX_TRI_EN           : 1;
  __REG32 XPOL                : 1;
  __REG32 BIST                : 1;
  __REG32 RSSIOR              : 1;
  __REG32                     : 16;
} __RF_CONTROLSTATUS_bits;

/* BTA RX time register */
typedef struct {
  __REG32 RX_TIME_START       : 5;
  __REG32                     : 3;
  __REG32 RX_TIME_END         : 6;
  __REG32                     : 18;
} __RX_TIME_bits;

/* BTA TX time register */
typedef struct {
  __REG32 TX_TIME_START       : 5;
  __REG32                     : 27;
} __TX_TIME_bits;

/* BTA Bluetooth application timer register */
typedef struct {
  __REG32 TIMER               : 12;
  __REG32                     : 3;
  __REG32 EN                  : 1;
  __REG32                     : 16;
} __BAT_bits;

/* BTA Threshold and correlation max register */
typedef union {
  //THRESHOLD
  struct { /* MC13180 */
    __REG32 THRESHOLD_I         : 4;
    __REG32 THRESHOLD_II        : 4;
    __REG32                     : 24;
  };
  //THRESHOLD
  struct { /* Siliconwave */
    __REG32 THRESHOLD           : 9;
    __REG32                     : 23;
  };
  // CORRELATION_MAX BTA correlation max register
  struct {
    __REG32 VALUE               : 9;
    __REG32                     : 23;
  };
} __THRESHOLD_bits;

/* BTA 16 bit word registers */
typedef struct {
  __REG32 WORD                : 16;
  __REG32                     : 16;
} __16BIT_WORD_bits;

/* BTA Wakeup 1 register */
typedef struct {
  __REG32 TIME                : 2;
  __REG32                     : 30;
} __WAKEUP_1_bits;

/* BTA Wakeup 2 register */
typedef struct {
  __REG32 TIME                : 16;
  __REG32                     : 16;
} __WAKEUP_2_bits;

/* BTA Wakeup 4 and delta 4 register */
typedef union {
  //WAKEUP_4
  struct {
    __REG32 TIME                : 16;
    __REG32                     : 16;
  };
  //WAKEUP_DELTA4
  struct {
    __REG32 DELTATIME           : 10;
    __REG32                     : 22;
  };
} __WAKEUP_4DELTA4_bits;

/* BTA Wakeup control/status register */
typedef union {
  //WU_CONTROL
  struct { /* Wakeup control register */
    __REG32                     : 3;
    __REG32 CLR_CNT             : 1;
    __REG32 CTL_PDE             : 1;
    __REG32                     : 27;
  };
  //WU_STATUS
  struct { /* Wakeup status register */
    __REG32 STS_PDE             : 1;
    __REG32 BT1_CLK_HOLD        : 1;
    __REG32 BTWUI               : 1;
    __REG32 WAKEUP_DELTA4       : 10;
    __REG32                     : 19;
  };
} __WU_CONTROLSTATUS_bits;

/* BTA Wakeup count register */
typedef struct {
  __REG32 COUNT               : 16;
  __REG32                     : 16;
} __WU_COUNT_bits;

/* BTA Clock control register */
typedef struct {
  __REG32 BT1_CLK_IN_DIV      : 2;
  __REG32                     : 2;
  __REG32 BT1_WSLOT           : 4;
  __REG32 BT1_RSLOT           : 4;
  __REG32                     : 1;
  __REG32 RFM                 : 3;
  __REG32                     : 16;
} __CLK_CONTROL_bits;

/* BTA SPI word 0 register */
typedef union {
  //SPI_WORD0
  struct { /* MC13180 */
    __REG32 WORD0               : 16;
    __REG32                     : 16;
  };
  //SPI_WORD0
  struct { /* Siliconwave */
    __REG32 BYTE1               : 8;
    __REG32 BYTE0               : 8;
    __REG32                     : 16;
  };
} __SPI_WORD0_bits;

/* BTA SPI word 1 register */
typedef union {
  //SPI_WORD1
  struct { /* MC13180 */
    __REG32 WORD1               : 16;
    __REG32                     : 16;
  };
  //SPI_WORD1
  struct { /* Siliconwave */
    __REG32 BYTE3               : 8;
    __REG32 BYTE2               : 8;
    __REG32                     : 16;
  };
} __SPI_WORD1_bits;

/* BTA SPI word 2 register */
typedef union {
  //SPI_WORD2
  struct { /* MC13180 */
    __REG32 WORD2               : 16;
    __REG32                     : 16;
  };
  //SPI_WORD2
  struct { /* Siliconwave */
    __REG32 BYTE5               : 8;
    __REG32 BYTE4               : 8;
    __REG32                     : 16;
  };
} __SPI_WORD2_bits;

/* BTA SPI word 3 register */
typedef union {
  //SPI_WORD3
  struct { /* MC13180 */
    __REG32 WORD3               : 16;
    __REG32                     : 16;
  };
  //SPI_WORD3
  struct { /* Siliconwave */
    __REG32 BYTE7               : 8;
    __REG32 BYTE6               : 8;
    __REG32                     : 16;
  };
} __SPI_WORD3_bits;

/* BTA SPI read/write address register */
typedef union {
  //SPI_READ_ADDR SPI_WRITE_ADDR
  struct { /* MC13180 */
    __REG32 MCADDRESS           : 7;
    __REG32 MCRW                : 1;
    __REG32                     : 24;
  };
  //SPI_READ_ADDR SPI_WRITE_ADDR
  struct { /* Siliconwave */
    __REG32 SWADDRESS           : 8;
    __REG32 COMMAND             : 7;
    __REG32 SWRW                : 1;
    __REG32                     : 16;
  };
} __SPI_READWRITE_ADDR_bits;

/* BTA SPI control register */
typedef union {
  //SPI_CONTROL
  struct { /* SPI control register */
    __REG32 SPI_MODE            : 3;
    __REG32                     : 1;
    __REG32 SPI_CLKDIV1         : 4;
    __REG32 SPI_CLKDIV2         : 4;
    __REG32 SPI_CLKDIV3         : 2;
    __REG32 SPI_CLKINV          : 1;
    __REG32 BYTE_ONLY           : 1;
    __REG32                     : 16;
  };
  //SPI_STATUS
  struct { /* SPI status register */
    __REG32 DONE                : 1;
    __REG32                     : 31;
  };
} __SPI_CONTROLSTATUS_bits;

/* BTA HOP0 (frequency in) register */
typedef union {
  //HOP0
  struct {
    __REG32 CLK_LOW             : 16;
    __REG32                     : 16;
  };
  //HOP_FREQ_OUT BTA HOP frequency out register
  struct {
    __REG32 HOP_OUT             : 8;
    __REG32                     : 24;
  };
} __HOP0_bits;

/* BTA HOP1 (frequency in) register */
typedef struct {
  __REG32 CLK_HIGH            : 10;
  __REG32                     : 22;
} __HOP1_bits;

/* BTA HOP2 (frequency in) register */
typedef struct {
  __REG32 LAPUAP_LOW          : 16;
  __REG32                     : 16;
} __HOP2_bits;

/* BTA HOP3 (frequency in) register */
typedef struct {
  __REG32 LAPUAP_LOW          : 12;
  __REG32                     : 20;
} __HOP3_bits;

/* BTA HOP4 (frequency in) register */
typedef struct {
  __REG32 STATE               : 2;
  __REG32 SYS                 : 1;
  __REG32                     : 29;
} __HOP4_bits;

/* BTA interrupt vector register */
typedef struct {
  __REG32 SYSTICK             : 1;
  __REG32 EOH                 : 1;
  __REG32 _EOF                : 1; //                Renamed to avoid name clash with the EOF constant in stdio.h
  __REG32 TIMER               : 1;
  __REG32                     : 28;
} __INTERRUPT_VECTOR_bits;

/* BTA synchronization metric register */
typedef struct {
  __REG32 SYNC_METRIC         : 15;
  __REG32                     : 17;
} __SYNC_METRIC_bits;

/* BTA synchronize frequency carrier register */
typedef struct {
  __REG32 SYNC_FC             : 8;
  __REG32                     : 24;
} __SYNC_FC_bits;

/* BTA word reverse register */
typedef struct {
  __REG32 WORD_REVERSED       : 16;
  __REG32                     : 16;
} __WORD_REVERSE_bits;

/* BTA byte reverse register */
typedef struct {
  __REG32 BYTE_REVERSED       : 8;
  __REG32                     : 24;
} __BYTE_REVERSE_bits;


/* -------------------------------------------------------------------------*/
/*               I2C registers                                                  */
/* -------------------------------------------------------------------------*/

typedef struct {        /* I2C Address Register (0x00217000) Reset (0x00000000)         */
  __REG32               : 1;    // Bit 0                - reserved
  __REG32 ADR           : 1;    // Bit 1                - Slave Address - Contains the specific slave address to be used by the I2C module.
  __REG32               :30;    // Bits 31-2    - Reserved
} __IADR_bits ;

typedef struct {        /* I2C Address Register (0x00217004) Reset (0x00000000)         */
  __REG32 IC            : 5;    // Bits 0-4             - I2C Clock Rate Divider - Prescales the clock for bit-rate selection.
  __REG32               :27;    // Bits 31-5    - Reserved
} __IFDR_bits ;

typedef struct {        /* I2C Control Register (0x00217008)    Reset (0x00000000) */
  __REG32               : 2;    // Bits 0-1     - Reserved
  __REG32 RSTA          : 1;    // Bit 2        - Repeated START - Generates a repeated START condition
  __REG32 TXAK          : 1;    // Bit 3        - Transmit Acknowledge Enable (0 = Send ACK, 1 = Dont send ACK)
  __REG32 MTX           : 1;    // Bit 4        - Transmit/Receive Mode Select (0 = Rx, 1 = Tx)
  __REG32 MSTA          : 1;    // Bit 5        - Master/Slave Mode Select (0 = Slave, 1 = Master)
  __REG32 IIEN          : 1;    // Bit 6        - I2C Interrupt Enable
  __REG32 IEN           : 1;    // Bit 7        - I2C Enable
  __REG32               :24;    // Bits 8-31    - Reserved
} __I2CR_bits ;

typedef struct {        /* I2C Status Register  (0x0021700C)    Reset (0x00000081) */
  __REG32 RXAK          : 1;    // Bit 0        - Received Acknowledge (0 = ACK received, 1 = No ACK received)
  __REG32 IIF           : 1;    // Bit 1        - I2C interrupt - (0 = No Int. pending, 1 = Interrupt pending )
  __REG32 SRW           : 1;    // Bit 2        - Slave Read/Write - Indicates the value of the R/W command bit
  __REG32               : 1;    // Bit 3        - Reserved
  __REG32 IAL           : 1;    // Bit 4        - Arbitration Lost
  __REG32 IBB           : 1;    // Bit 5        - I2C Bus Busy
  __REG32 IAAS          : 1;    // Bit 6        - I2C Addressed As a Slave
  __REG32 ICF           : 1;    // Bit 7        - Data Transfer (0=In Progress, 1 = Complete)
  __REG32               :24;    // Bits 8-31    - Reserved
} __I2SR_bits ;

typedef struct {        /* I2C Data I/O Register        (0x00217010)    Reset (0x00000000) */
  __REG32 DATA          : 8;    // Bits 0-7     - I2C Data to be transmitted / last byte received
  __REG32               :24;    // Bits 8-31    - Reserved
} __I2DR_bits ;


/* -------------------------------------------------------------------------*/
/*               SSI registers                                              */
/* -------------------------------------------------------------------------*/

typedef struct {        /* SSI Transmit Data register (0x00218000) Reset (0x0000)*/
  __REG32 DATA        :16;      // Bits 15-0    - word access to tx data
  __REG32             :16;      // Bits 31-16   - unused should read 0
} __STX_bits ;

typedef struct { /* SSI Receive Data Register (0x00218004) Reset (0x0000)*/
  __REG32 DATA        :16;      // Bits 15-0    - word access to tx data
  __REG32             :16;      // Bits 31-16
} __SRX_bits ;

typedef struct { /* SSI Control/Status Register (0x00218008) Reset (0x00000041)*/
  __REG32 TFE           : 1;    // Bit 0        - Transmit FIFO Empty   (0=Data level exceeds water mark, 1=Data level below water mark )
  __REG32 RFF           : 1;    // Bit 1        - Receive FIFO Full             (0=Data level exceeds water mark, 1=Data level reaches water mark )
  __REG32 RFS           : 1;    // Bit 2        - Receive Frame Sync    (0=No Frame sync occured, 1=Frame sync occured)
  __REG32 TFS           : 1;    // Bit 3        - Transmit Frame Sync   (0=No Frame sync occured, 1=Frame sync occured)
  __REG32 TUE           : 1;    // Bit 4        - Transmitter Underrun Error (0 = TXSR is empty and no tx slot has occured or TXSR is not empty, 1=TXSR is empty and time slot has occured) Cleared by reading this register, and then writing to STX or STSR register
  __REG32 ROE           : 1;    // Bit 5        - Receive Overrun Error (0=SRX/FIFO can hold more data, 1=SRX/FIFO are is full) Cleared by reading this register, and then reading SRX register
  __REG32 TDE           : 1;    // Bit 6        - Transmit Data Register Empty (0=Data waiting to be tx, 1=no data is waiting)
  __REG32 RDR           : 1;    // Bit 7        - Receive Data Ready.   (1=SRX contains new data, 0=FIFO empty) Automatically cleared when CPU reads SRX
  __REG32 SSI_EN        : 1;    // Bit 8        - SSI Enable, must be set before setting other bits (0=Disable, 1=Enable), clears FIFO's when reset
  __REG32 TE            : 1;    // Bit 9        - Transmit Enable               (0=Disable, 1=Enable)
  __REG32 RE            : 1;    // Bit 10       - Receive Enable                (0=Disable, 1=Enable)
  __REG32 NET           : 1;    // Bit 11       - Network (TDM) Mode    (0=Normal, 1=Network)
  __REG32 SYN           : 1;    // Bit 12       - Synchronous Mode      (0=Disable, 1=Enable)
  __REG32 I2S_MODE      : 2;    // Bits 14-13   - I2S Mode Select               (00,11 = Normal mode, 01 = Master mode, 10 = Slave mode)
  __REG32 SYS_CLK_EN    : 1;    // Bit 15       - System Clock Enable   (0 = SYS_CLK is not displayed at the SSI_RXCLK pin, 1 = SYS_CLK is displayed at the SSI_RXCLK pin
  __REG32               : 16;   // Bits 31-16   - Reserved
} __SCSR_bits ;

typedef struct { /* SSI Transmit Configuration Register (0x0021800C) Reset (0x00000000)*/
  __REG32 TEFS          : 1;    // Bit 0        - Transmit Early Frame Sync (0=Frame sync is initiated with first data bit tx, 1=Frame sync is initiated one bit-clock before tx starts)
  __REG32 TFSL          : 1;    // Bit 1        - Transmit Frame Sync Length(0=1 Word long, 0=1 Bit long)
  __REG32 TFSI          : 1;    // Bit 2        - Transmit Frame Sync Invert(0=Active High, 1=Active Low)
  __REG32 TSCKP         : 1;    // Bit 3        - Transmit Clock Polarity       (0=Rising edge, 1=Falling Edge)
  __REG32 TSHFD         : 1;    // Bit 4        - Transmit Shift Direction      (0=MSB First, 1=LSB First)
  __REG32 TXDIR         : 1;    // Bit 5        - Transmit Direction            (0=External, 1=Internal ) SSI_TXCLK clock pin
  __REG32 TFDIR         : 1;    // Bit 6        - Transmit Frame Direction      (0=Generated Externally, 1=Generated Internally)
  __REG32 TFEN          : 1;    // Bit 7        - Transmit FIFO Enable          (0=Disabled, 1=Enabled)
  __REG32 TIE           : 1;    // Bit 8        - Transmit Interrupt Enable (0=Disabled, 1=Enabled)
  __REG32 TDMAE         : 1;    // Bit 9        - Transmit DMA Enable           (0=No DMA Issued, 1=DMA request issued)
  __REG32 TXBIT0        : 1;    // Bit 10       - Transmit Bit0. Data shift direction (0=MSB First(default), 1=LSB First)
  __REG32               : 21;   // Bits 31-11   - Reserved
} __STCR_bits;

/* -------------------------------------------------------------------------*/
typedef struct { /* SSI Receive Configuration Register (0x00218010) Reset (0x00000000)*/
  __REG32 REFS          : 1;    // Bit 0        - Receive Early Frame Sync  (0=Frame sync is initiated with first data bit rx, 1=Frame sync is initiated one bit-clock before rx starts)
  __REG32 RFSL          : 1;    // Bit 1        - Receive Frame Sync Length (0=1 Word long, 0=1 Bit long)
  __REG32 RFSI          : 1;    // Bit 2        - Receive Frame Sync Invert (0=Active High, 1=Active Low)
  __REG32 RSCKP         : 1;    // Bit 3        - Receive Clock Polarity        (0=Falling edge, 1=Rising Edge)
  __REG32 RSHFD         : 1;    // Bit 4        - Receive Shift Direction       (0=MSB First, 1=LSB First)
  __REG32 RXDIR         : 1;    // Bit 5        - Receive Direction             (0=External, 1=Internal ) SSI_RXCLK clock pin
  __REG32 RFDIR         : 1;    // Bit 6        - Receive Frame Direction       (0=Generated Externally, 1=Generated Internally)
  __REG32 RFEN          : 1;    // Bit 7        - Receive FIFO Enable           (0=Disabled, 1=Enabled)
  __REG32 RIE           : 1;    // Bit 8        - Receive Interrupt Enable  (0=Disabled, 1=Enabled)
  __REG32 RDMAE         : 1;    // Bit 9        - Receive DMA Enable            (0=No DMA Issued, 1=DMA request issued)
  __REG32 RXBIT0        : 1;    // Bit 10       - Receive Bit0. Data shift direction (0=MSB First(default), 1=LSB First)
  __REG32               : 21;   // Bits 31-11   - Reserved
} __SRCR_bits;

typedef struct { /* SSI Clock Control Register */
  __REG32 PM            : 8;    // Bits 7-0     - Prescale Modulus Select       (0=/1, 1=/2 ..255=1/256)
  __REG32 DC            : 5;    // Bits 12-8    - Frame Rate Divider Control(0=/1, 1=/2 ...31=1/32) In network mode, DC=0 is a speacial case
  __REG32 WL            : 2;    // Bits 14-13   - Word Length                           (00=8 Bits, 01 = 10 Bits, 10 = 12 Bits, 11 = 16 Bits )
  __REG32 PSR           : 1;    // Bit 15       - Prescaler range                       (0=Bypass /8 prescaler, 1=Use /8 prescaler) Using prescaler allows a 128kHz master clock for motorola MC1440x series codecs
  __REG32               : 16;   // Bits 31-16   - Reserved
} __SSI_CCR_bits ;

typedef struct { /* SSI Time Slot Register      (0x0021801C) Reset (0x0000)*/
  __REG32 DUMMY       :16;      // Bits 15-0            - Dummy Bits. Holds data that is not intended for transmission.
  __REG32             :16;      // Bits 31-16           - Reserved
} __STSR_bits ;

typedef struct { /* SSI FIFO Control/Status Register    (0x00218020) Reset (0x0000)*/
  __REG32 TFWM          : 4;    // Bits 3-0             - Transmit FIFO Empty Water Mark
  __REG32 RFWM          : 4;    // Bits 7-4             - Receive FIFO Full Water Mark
  __REG32 TFCNT         : 4;    // Bits 11-8            - Transmit FIFO Counter - num words in tx FIFO
  __REG32 RFCNT         : 4;    // Bits 15-12           - Receive FIFO Counter - num words in rx FIFO
  __REG32               : 16;   // Bits 31-16           - Reserved
} __SFCSR_bits ;

typedef struct { /* SSI Option Register (0x00218028) Reset (0x0000)*/
  __REG32 SYNRST        : 1;    // Bit 0      - Frame Sync Reset. Resets the accumulation of data in the SRX register and receive FIFO (RXFIFO) on frame synchronization. (0 = No effect, 1 = Reset data accumulation)
  __REG32               : 3;    // Bits 3-1   - Reserved
  __REG32 TX_CLR        : 1;    // Bit 4      - Transmitter Clear. Controls whether the transmit FIFO is flushed. (0 = No effect, 1 = Clear receive FIFO)
  __REG32 RX_CLR        : 1;    // Bit 5      - Receiver Clear. Controls whether the receive FIFO is flushed. (0 = No effect, 1 = Clear receive FIFO)
  __REG32 CLKOFF        : 1;    // Bit 6      - Clock Off. Turns off the clocks when the SSI is disabled to reduce power consumption (0=Enabled, 1=Disabled)
  __REG32               : 25;   // Bits 31-7  - Reserved
} __SOR_bits ;


/* -------------------------------------------------------------------------*/
/*               MSHC registers                                             */
/* -------------------------------------------------------------------------*/

/* MSHC Memory stick command register */
typedef struct {
  __REG16 SIZE                : 10;
  __REG16                     : 2;
  __REG16 PID                 : 4;
} __MSCMD_bits;

/* MSHC Memory stick control/status register */
typedef struct {
  __REG16 TBF                 : 1;
  __REG16 TBE                 : 1;
  __REG16 RBF                 : 1;
  __REG16 RBE                 : 1;
  __REG16                     : 2;
  __REG16 DRQ                 : 1;
  __REG16 INT                 : 1;
  __REG16 BSYCNT              : 3;
  __REG16 NOCRC               : 1;
  __REG16 DAKEN               : 1;
  __REG16 SIEN                : 1;
  __REG16 PWS                 : 1;
  __REG16 RST                 : 1;
} __MSCS_bits;

/* MSHC Memory stick interrupt control/status register */
typedef struct {
  __REG16 TOE                 : 1;
  __REG16 CRC                 : 1;
  __REG16 FAE                 : 1;
  __REG16                     : 1;
  __REG16 PIN                 : 1;
  __REG16 DRQ                 : 1;
  __REG16 SIF                 : 1;
  __REG16 RDY                 : 1;
  __REG16                     : 5;
  __REG16 PINEN               : 1;
  __REG16 DRQSL               : 1;
  __REG16 INTEN               : 1;
} __MSICS_bits;

/* Memory Stick Parallel Port Control/Data Register */
typedef struct {
  __REG16                     : 4;
  __REG16 XPIN0               : 1;
  __REG16 XPIN1               : 1;
  __REG16                     : 6;
  __REG16 PIEN0               : 1;
  __REG16 PIEN1               : 1;
  __REG16                     : 2;
} __MSPPCD_bits;

/* Memory Stick Control 2 Register */
typedef struct {
  __REG16 MSCEN               : 1;
  __REG16 LEND                : 1;
  __REG16                     : 12;
  __REG16 RED                 : 1;
  __REG16 ACD                 : 1;
} __MSC2_bits;

/* Memory Stick Auto Command Register */
typedef struct {
  __REG16 ADATASIZE           : 10;
  __REG16                     : 2;
  __REG16 APID                : 4;
} __MSACD_bits;

/* Memory Stick FIFO Access Error Control/Status Register */
typedef struct {
  __REG16 TOV                 : 1;
  __REG16 RUN                 : 1;
  __REG16                     : 6;
  __REG16 FAEEN               : 1;
  __REG16                     : 7;
} __MSFAECS_bits;

/* Memory Stick Serial Clock Divider Register */
typedef struct {
  __REG16 DIV                 : 2;
  __REG16                     : 13;
  __REG16 SRC                 : 1;
} __MSCLKD_bits;

/* Memory Stick DMA Request Control Register */
typedef struct {
  __REG16 TFE                 : 1;
  __REG16                     : 3;
  __REG16 RFF                 : 1;
  __REG16                     : 10;
  __REG16 DRQEN               : 1;
} __MSDRQC_bits;


/* -------------------------------------------------------------------------*/
/*      PLL and Clock Controller Module Registers                                                               */
/* -------------------------------------------------------------------------*/

typedef struct { /* Clock Source Control Register (0x0021B000) reset (0x0F00AC03) */
  __REG32 MPEN          : 1;    // Bit 0        - MCU PLL Enable. When software writes 0 to MPEN, the PLL shuts down immediately.
  __REG32 SPEN          : 1;    // Bit 1        - System PLL Enable. When software writes 0 to SPEN, the System PLL shuts down after SDCNT times out.
  __REG32               : 6;    // Bits 2-7     - Reserved
  __REG32               : 2;    // Bits 8-9     - Reserved
  __REG32 BCLK_DIV      : 4;    // Bits 10-13   - Contains the 4-bit integer divider values for the generation of the BCLK.
  __REG32               : 1;    // Bit 14       - Reserved
  __REG32 PRESC         : 1;    // Bit 15       - Defines the MPU PLL clock prescaler.
  __REG32 SYSTEM_SEL    : 1;    // Bit 16       - Selects the clock source of the System PLL input.
  __REG32 OSC_EN        : 1;    // Bit 17       - Enables the external 16 MHz oscillator circuit when set.
  __REG32 CLK16_SEL     : 1;    // Bit 18       - Selects the clock source of the 16 MHz clock.
  __REG32               : 2;    // Bits 19-20   - Reserved
  __REG32 MPLL_RESTART  : 1;    // Bit 21       - Restarts the MCU PLL at a new assigned frequency.
  __REG32 SPLL_RESTART  : 1;    // Bit 22       - Restarts System PLL at new assigned frequency.
  __REG32               : 1;    // Bit 23       - Reserved
  __REG32 SD_CNT        : 2;    // Bits 24-25   - Contains the value that sets the duration of System PLL clock output after 0 is written to the SPEN bit.
  __REG32 USB_DIV       : 3;    // Bits 26-28   - Contains the integer divider value used to generate the CLK48M signal for the USB modules.
  __REG32 CLK0_SEL      : 3;    // Bits 29-31   - Selects the clock signal source that is output on the CLKO pin.
} __CSCR_bits ;

typedef struct { /* Peripheral Clock Divider Register (0x0021B020) reset (0x000B00BB) */
  __REG32 PCLK_DIV1     : 4;    // Bits 0-3     - Contains the 4-bit integer divider that produces the PERCLK1 clock signal for the peripherals.
  __REG32 PCLK_DIV2     : 4;    // Bits 4-7     - Contains the 4-bit integer divider that produces the PERCLK2 clock signal for the peripherals.
  __REG32               : 8;    // Bits 8-15    - Reserved
  __REG32 PCLK_DIV3     : 7;    // Bits 16-22   - Contains the 7-bit integer divider that produces the PERCLK3 clock signal for the peripherals.
  __REG32               : 1;    // Bit 23       - Reserved
  __REG32               : 8;    // Bits 24-31   - Reserved
} __PCDR_bits ;

typedef struct { /* MCU PLL Control Register 0 (0x0021B004) reset (0x003F1437) */
  __REG32 MFN           :10;    // Bits 0-9     - Multiplication Factor (Numerator)
  __REG32 MFI           : 4;    // Bits 10-13   - Multiplication Factor (Integer)
  __REG32               : 2;    // Bits 14-15   - Reserved
  __REG32 MFD           :10;    // Bits 16-25   - Multiplication Factor (Denominator Part)
  __REG32 PD            : 4;    // Bits 26-29   - Predivider Factor applied to the PLL input frequency.(0-15)
  __REG32               : 2;    // Bits 30-31   - Reserved
} __MPCTL0_bits ;

typedef struct { /* MCU PLL and System Clock Control Register 1 (0x0021B008) reset (0x00000000) */
  __REG32               : 6;    // Bits 0-5     - Reserved
  __REG32 BRMO          : 1;    // Bit 6        - Controls the BRM order.
  __REG32               : 25;   // Bits 7-31    - Reserved
} __MPCTL1_bits ;

typedef struct { /* System PLL Control Register 0 (0x0021B00C) reset (0x043F1437) */
  __REG32 MFN           :10;    // Bits 0-9     - Multiplication Factor (Numerator)
  __REG32 MFI           : 4;    // Bits 10-13   - Multiplication Factor (Integer)
  __REG32               : 2;    // Bits 14-15   - Reserved
  __REG32 MFD           :10;    // Bits 16-25   - Multiplication Factor (Denominator Part)
  __REG32 PD            : 4;    // Bits 26-29   - Predivider Factor applied to the PLL input frequency.(0-15)
  __REG32               : 2;    // Bits 30-31   - Reserved
} __SPCTL0_bits ;

typedef struct { /* System PLL Control Register 1 (0x0021B010) reset (0x00000000) */
  __REG32               : 6;    // Bits 0-5     - Reserved
  __REG32 BRMO          : 1;    // Bit 6        - Controls the BRM order.
  __REG32               : 1;    // Bit 7        - Reserved
  __REG32               : 7;    // Bits 8-14    - Reserved
  __REG32 LF            : 1;    // Bit 15       - Lock Flag - Indicates whether the System PLL is locked.
  __REG32               : 16;   // Bits 16-31   - Reserved
} __SPCTL1_bits ;


/* -------------------------------------------------------------------------*/
/*               System control registers                                                       */
/* -------------------------------------------------------------------------*/

typedef struct { /* Function Multiplexing Control Register      (0x0021B808) Reset (0x00000003) */
  __REG32 SDCS0_SEL     :1;     // Bit 0        - SDRAM/SyncFlash Chip Select CS2/CSD0
  __REG32 SDCS1_SEL     :1;     // Bit 1        - SDRAM/SyncFlash Chip Select CS3/CS1
  __REG32 EXT_BR_EN     :1;     // Bit 2        - External Bus Request Control
  __REG32 SSI_TXCLK_SEL :1;     // Bit 3        - SSI Transmit Clock Select
  __REG32 SSI_TXFS_SEL  :1;     // Bit 4        - SSI Transmit Frame Sync Select
  __REG32 SSI_RXDAT_SEL :1;     // Bit 5        - SSI Receive Data Select
  __REG32 SSI_RXCLK_SEL :1;     // Bit 6        - SSI Receive Clock Select
  __REG32 SSI_RXFS_SEL  :1;     // Bit 7        - SSI Receive Frame Sync Input Select
  __REG32 SPI2_RXD_SEL  :1;     // Bit 8        - SPI2 Receive Data Input Select
  __REG32               :23;    // Bits 31-9    - Reserved
} __FMCR_bits ;

typedef struct { /* Global Peripheral Control Register (0x0021B80C) Reset (0x00000000) */
  __REG32 CSI_PROT_EN   : 1;    // Bit 0        - CMOS Sensor Interface Privileged Mode
  __REG32 MMA_PROT_EN   : 1;    // Bit 1        - MMA Privileged Mode Access
  __REG32               : 1;    // Bit 2        - reserved should read 0
  __REG32               : 1;    // Bit 3        - reserved MUST BE SET TO 1 AT ALL TIMES
  __REG32 DS_DATA       : 2;    // Bits 5-4     - Driving Strength Data Bus
  __REG32 DS_ADDR       : 2;    // Bits 7-6     - Driving Strength Address Bus
  __REG32 DS_CNTL       : 2;    // Bits 9-8     - Driving Strength Bus Control Signal
  __REG32 DS_SLOW       : 2;    // Bits 11-10   - Driving Strength Slow I/O
  __REG32 BTAEN         : 1;    // Bit 12       - BTA Clock Input Control
  __REG32               :19;    // Bits 31-13   - Reserved
} __GPCR_bits ;

typedef struct {        /* Global Clock Control Register (0x0021B810) Reset (0x0000000F) */
  __REG32 USBD_CLK_EN   : 1;    // Bit 0        - USBD Clock Enable
  __REG32 MMA_CLK_EN    : 1;    // Bit 1        - Multimedia Accelerator Clock Enable
  __REG32 CSI_CLK_EN    : 1;    // Bit 2        - CMOS Sensor Inteface Clock Enable
  __REG32 DMA_CLK_EN    : 1;    // Bit 3        - DMA Clock Enable
  __REG32 BROM_CLK_EN   : 1;    // Bit 4        - BROM Clock Enable
  __REG32               :27;    // Bits 13-5    - Reserved
} __GCCR_bits ;

/* Reset Source Register */
typedef struct {
  __REG32 EXR                 : 1;
  __REG32 WDR                 : 1;
  __REG32                     : 30;
} __RSR_bits;


/* -------------------------------------------------------------------------*/
/*      GPIO Registers                                                          */
/* -------------------------------------------------------------------------*/

typedef struct { /* Structure for GPIO Register Type 1.                                         */
  __REG32 PIN0          : 2;    // Bits 1-0
  __REG32 PIN1          : 2;    // Bits 3-2
  __REG32 PIN2          : 2;    // Bits 5-4
  __REG32 PIN3          : 2;    // Bits 7-6
  __REG32 PIN4          : 2;    // Bits 9-8
  __REG32 PIN5          : 2;    // Bits 11-10
  __REG32 PIN6          : 2;    // Bits 13-12
  __REG32 PIN7          : 2;    // Bits 15-14
  __REG32 PIN8          : 2;    // Bits 17-16
  __REG32 PIN9          : 2;    // Bits 19-18
  __REG32 PIN10         : 2;    // Bits 21-20
  __REG32 PIN11         : 2;    // Bits 23-22
  __REG32 PIN12         : 2;    // Bits 25-24
  __REG32 PIN13         : 2;    // Bits 27-26
  __REG32 PIN14         : 2;    // Bits 29-28
  __REG32 PIN15         : 2;    // Bits 31-30
} __PORT_REG_15_0_bits ;

typedef struct { /* Structure for GPIO Register Type 2.                                         */
  __REG32 PIN16         : 2;    // Bits 1-0
  __REG32 PIN17         : 2;    // Bits 3-2
  __REG32 PIN18         : 2;    // Bits 5-4
  __REG32 PIN19         : 2;    // Bits 7-6
  __REG32 PIN20         : 2;    // Bits 9-8
  __REG32 PIN21         : 2;    // Bits 11-10
  __REG32 PIN22         : 2;    // Bits 13-12
  __REG32 PIN23         : 2;    // Bits 15-14
  __REG32 PIN24         : 2;    // Bits 17-16
  __REG32 PIN25         : 2;    // Bits 19-18
  __REG32 PIN26         : 2;    // Bits 21-20
  __REG32 PIN27         : 2;    // Bits 23-22
  __REG32 PIN28         : 2;    // Bits 25-24
  __REG32 PIN29         : 2;    // Bits 27-26
  __REG32 PIN30         : 2;    // Bits 29-28
  __REG32 PIN31         : 2;    // Bits 31-30           - See table below
} __PORT_REG_31_16_bits ;

typedef struct { /* Structure for GPIO Register Type 3.                                         */
  __REG32 PIN0          : 1;    // Bit 0
  __REG32 PIN1          : 1;    // Bit 1
  __REG32 PIN2          : 1;    // Bit 2
  __REG32 PIN3          : 1;    // Bit 3
  __REG32 PIN4          : 1;    // Bit 4
  __REG32 PIN5          : 1;    // Bit 5
  __REG32 PIN6          : 1;    // Bit 6
  __REG32 PIN7          : 1;    // Bit 7
  __REG32 PIN8          : 1;    // Bit 8
  __REG32 PIN9          : 1;    // Bit 9
  __REG32 PIN10         : 1;    // Bit 10
  __REG32 PIN11         : 1;    // Bit 11
  __REG32 PIN12         : 1;    // Bit 12
  __REG32 PIN13         : 1;    // Bit 13
  __REG32 PIN14         : 1;    // Bit 14
  __REG32 PIN15         : 1;    // Bit 15
  __REG32 PIN16         : 1;    // Bit 16
  __REG32 PIN17         : 1;    // Bit 17
  __REG32 PIN18         : 1;    // Bit 18
  __REG32 PIN19         : 1;    // Bit 19
  __REG32 PIN20         : 1;    // Bit 20
  __REG32 PIN21         : 1;    // Bit 21
  __REG32 PIN22         : 1;    // Bit 22
  __REG32 PIN23         : 1;    // Bit 23
  __REG32 PIN24         : 1;    // Bit 24
  __REG32 PIN25         : 1;    // Bit 25
  __REG32 PIN26         : 1;    // Bit 26
  __REG32 PIN27         : 1;    // Bit 27
  __REG32 PIN28         : 1;    // Bit 28
  __REG32 PIN29         : 1;    // Bit 29
  __REG32 PIN30         : 1;    // Bit 30
  __REG32 PIN31         : 1;    // Bit 31
} __PORT_REG_31_0_bits ;

typedef struct {
  __REG32 SWR           : 1;    // Bit 0        -   Software Reset (0 = No effect, 1 = GPIO circuitry for Port X Reset)
  __REG32               :31;    // Bits 31-1    -   Reserved, should read 0
} __SWR_bits ;


/* -------------------------------------------------------------------------*/
/*               EIM registers                                              */
/* -------------------------------------------------------------------------*/

typedef struct {        /* Chip Select 0-5 Upper Control Register (0x00220000) Reset CS0(0x00003E00) CS2-5(0x00000000)*/
  __REG32 EDC           : 4;    // Bit  0-3     - Extra Dead Cycles
  __REG32 WWS           : 3;    // Bits 1-15    - Write Wait State
  __REG32               : 1;    // Bits 1-15    - Reserved
  __REG32 WSC           : 6;    // Bits 1-15    - Wait State Control
  __REG32 CNC           : 2;    // Bits 1-15    - Chip Select Negation Clock Cycles
  __REG32 DOL           : 4;    // Bits 1-15    - Data Output Length
  __REG32 SYNC          : 1;    // Bits 1-15    - Synchronous Burst Mode Enable
  __REG32 PME           : 1;    // Bits 1-15    - Page Mode Emulation
  __REG32 PSZ           : 2;    // Bits 1-15    - Page Size
  __REG32 BCS           : 4;    // Bits 1-15    - Burst Clock Start
  __REG32 BCD           : 2;    // Bits 1-15    - Burst Clock Divisor
  __REG32               : 1;    // Bits 1-15    - Reserved
  __REG32 DTACK_SEL     : 1;    // Bits 1-15    - DTACK Select   NOT CS0
} __CSU_bits ;

typedef struct {        /* Chip Select 0-5 Lower Control Register (0x00220004) Reset CS0 (0x00000801) CS2-5(0x00000802)*/
  __REG32 CSEN          : 1;    // Bit  0       - Chip Select Enable
  __REG32 PA            : 1;    // Bits 1       - Pin Assert  NOT CS0
  __REG32               : 2;    // Bits 1-15    - Reserved
  __REG32 WP            : 1;    // Bits 1-15    - Write Protect
  __REG32               : 1;    // Bits 1-15    - Reserved
  __REG32 SP            : 1;    // Bits 1-15    - Supervisor Protect
  __REG32               : 1;    // Bits 1-15    - Reserved
  __REG32 DSZ           : 3;    // Bits 1-15    - Data Port Size
  __REG32 EBC           : 1;    // Bits 1-15    - Enable Byte Control
  __REG32 CSA           : 4;    // Bits 1-15    - Chip Select Assert
  __REG32 WEN           : 4;    // Bits 1-15    - EB [3:0] Negate During Write
  __REG32 WEA           : 4;    // Bits 1-15    - EB [3:0] Assert
  __REG32 OEN           : 4;    // Bits 1-15    - OE Negate
  __REG32 OEA           : 4;    // Bits 1-15    - OE Assert
} __CSL_bits ;

typedef struct {        /* EIM Configuration Register (0x00220030) Reset (0x00000000)*/
  __REG32               : 2;    // Bits 0-1     - Reserved
  __REG32 BCM           : 1;    // Bit  2       - Burst Clock Mode
  __REG32               : 29;
} __EIM_bits ;


/* -------------------------------------------------------------------------*/
/*               SDRAMC registers                                           */
/* -------------------------------------------------------------------------*/

typedef struct {        // SDRAM 0 Control Register (0x00201000) Reset  (0x01000300)
                        // SDRAM 1 Control Register (0x00221004) Reset  (0x01000300)
  __REG32 SRC           : 3;    // Bit  0-2     - SDRAM Row Cycle Delay
  __REG32               : 1;    // Bits 3       - reserved
  __REG32 SRCD          : 2;    // Bit  4-5     - SDRAM Row-to-Column Delay
  __REG32 SRP           : 1;    // Bit  6       - SDRAM Row Precharge Delay
  __REG32               : 1;    // Bit  7       - reserved
  __REG32 SCL           : 2;    // Bits 8-9     - SDRAM CAS Latency
  __REG32 CI            : 2;    // Bits 10-11   - Cache Inhibit
  __REG32 CLKST         : 2;    // Bit  12-13   - Clock Suspend Time-out
  __REG32 SREFR         : 2;    // Bit  14-15   - SDRAM Refresh Rate
  __REG32 DSIZ          : 2;    // Bits 16-17   - SDRAM Memory Data Width
  __REG32               : 1;    // Bit  18      - reserved
  __REG32 IAM           : 1;    // Bit  19      - (Bank 1 ) Interleaved Address Mode
  __REG32 COL           : 2;    // Bit  20-21   - Column Address Width
  __REG32               : 2;    // Bits 22-23   - reserved
  __REG32 ROW           : 2;    // Bits 24-25   - Row Address Width
  __REG32               : 1;    // Bit  26      - reserved
  __REG32 SP            : 1;    // Bits 27      - Supervisor Protect
  __REG32 SMODE         : 3;    // Bits 28-30   - SDRAM Controller Operating Mode
  __REG32 SDE           : 1;    // Bit  31      - SDRAM Controller Enable
} __SDCTL_bits ;

typedef struct {        // SDRAM Reset register (0x00221018) Reset (0x00000000)
  __REG32               : 30;   // Bits 0-29    - reserved
  __REG32 RST           : 2;    // Bit  30-31   - Software Initiated Local Module Reset Bits
} __SDRST_bits ;

typedef struct {        // SDRAM Reset register (0x00221014) Reset (0x00000000)
  __REG32 RMA0          : 1;    // Bit  0       - MA0 Replacement
  __REG32               : 30;   // Bits 1-30    - reserved
  __REG32 OMA           : 1;    // Bit  31      - Multiplexed Address Override
} __MISC_bits ;


/* -------------------------------------------------------------------------*/
/*               MMA registers                                              */
/* -------------------------------------------------------------------------*/

/* MMA MAC Module Register */
typedef struct {
  __REG32 ENAB                : 1;
  __REG32                     : 30;
  __REG32 RST                 : 1;
} __MMA_MAC_MOD_bits;

/* MMA MAC Control Register */
typedef struct {
  __REG32 OP_EN               : 1;
  __REG32 CACHE_EN            : 1;
  __REG32 CACHE_CLR           : 1;
  __REG32                     : 13;
  __REG32 Y_SIGNED            : 1;
  __REG32 Y_SIGN_INI          : 1;
  __REG32 Y_SIGN_ALT          : 1;
  __REG32 Y_DATA_SEL          : 1;
  __REG32 Y_INDEX_LOAD        : 1;
  __REG32 Y_INDEX_INCR        : 1;
  __REG32 Y_INDEX_CLR         : 1;
  __REG32 Y_MODIFYPRESET      : 1;
  __REG32 X_SIGNED            : 1;
  __REG32 X_SIGN_INI          : 1;
  __REG32 X_SIGN_ALT          : 1;
  __REG32 X_DATA_SEL          : 1;
  __REG32 X_INDEX_LOAD        : 1;
  __REG32 X_INDEX_INCR        : 1;
  __REG32 X_INDEX_CLR         : 1;
  __REG32 X_MODIFYPRESET      : 1;
} __MMA_MAC_CTRL_bits;

/* MMA MAC Multiply Counter Register */
typedef struct {
  __REG32 MULT_COUNTER        : 16;
  __REG32                     : 16;
} __MMA_MAC_MULT_bits;

/* MMA MAC Accumulate Counter Register */
typedef struct {
  __REG32 ACCU_COUNTER        : 16;
  __REG32                     : 16;
} __MMA_MAC_ACCU_bits;

/* MMA MAC Interrupt & interrupt mask Register */
typedef struct {
  __REG32 FIFO_FULL           : 1;
  __REG32 FIFO_HALF           : 1;
  __REG32 FIFO_EMPT           : 1;
  __REG32 OP_END              : 1;
  __REG32 OP_ERROR            : 1;
  __REG32                     : 27;
} __MMA_MAC_INTR_bits;

/* MMA MAC FIFO Status Register */
typedef struct {
  __REG32 FIFO_FULL           : 1;
  __REG32 FIFO_HALF           : 1;
  __REG32 FIFO_EMPT           : 1;
  __REG32                     : 13;
  __REG32 FIFO_COUNT          : 5;
  __REG32                     : 11;
} __MMA_MAC_FIFO_STAT_bits;

/* MMA MAC Burst Count Register */
typedef struct {
  __REG32 BURST_COUNT         : 8;
  __REG32                     : 24;
} __MMA_MAC_BURST_bits;

/* MMA MAC Bit Select Register */
typedef struct {
  __REG32 BITSEL              : 3;
  __REG32                     : 29;
} __MMA_MAC_BITSEL_bits;

/* MMA MAC X Index Register */
typedef struct {
  __REG32 XINDEX              : 16;
  __REG32                     : 16;
} __MMA_MAC_XINDEX_bits;

/* MMA MAC X length Register */
typedef struct {
  __REG32 LENGTH              : 16;
  __REG32 COLUMN              : 16;
} __MMA_MAC_XLENGTH_bits;

/* MMA MAC X modify Register */
typedef struct {
  __REG32 XMODIFY             : 16;
  __REG32                     : 16;
} __MMA_MAC_XMODIFY_bits;

/* MMA MAC X increment Register */
typedef struct {
  __REG32 XINCR               : 16;
  __REG32                     : 16;
} __MMA_MAC_XINCR_bits;

/* MMA MAC X count Register */
typedef struct {
  __REG32 XCOUNT              : 16;
  __REG32                     : 16;
} __MMA_MAC_XCOUNT_bits;

/* MMA MAC Y Index Register */
typedef struct {
  __REG32 YINDEX              : 16;
  __REG32                     : 16;
} __MMA_MAC_YINDEX_bits;

/* MMA MAC Y length Register */
typedef struct {
  __REG32 LENGTH              : 16;
  __REG32 COLUMN              : 16;
} __MMA_MAC_YLENGTH_bits;

/* MMA MAC Y modify Register */
typedef struct {
  __REG32 YMODIFY             : 16;
  __REG32                     : 16;
} __MMA_MAC_YMODIFY_bits;

/* MMA MAC Y increment Register */
typedef struct {
  __REG32 YINCR               : 16;
  __REG32                     : 16;
} __MMA_MAC_YINCR_bits;

/* MMA MAC Y count Register */
typedef struct {
  __REG32 YCOUNT              : 16;
  __REG32                     : 16;
} __MMA_MAC_YCOUNT_bits;

/* MMA DCT/iDCT Control Register */
typedef struct {
  __REG32 DCT_ENA             : 1;
  __REG32 DCT_IDCT            : 1;
  __REG32 ARMMCMSEL           : 2;
  __REG32 DCTBYPASS           : 1;
  __REG32 SWRST               : 1;
  __REG32 DCTCLKEN            : 1;
  __REG32 DCTXPOSE            : 1;
  __REG32 SEMAEN              : 1;
  __REG32 DATAINSHIFT         : 4;
  __REG32 DCT_HWORD_SWAP      : 1;
  __REG32                     : 18;
} __MMA_DCTCTRL_bits;

/* MMA DCT/iDCT IRQ Enable Register */
typedef struct {
  __REG32 DCTCOMP             : 1;
  __REG32 DIIEN               : 1;
  __REG32 DOIEN               : 1;
  __REG32 DIDEN               : 1;
  __REG32 DODEN               : 1;
  __REG32 ERRINTREN           : 1;
  __REG32                     : 26;
} __MMA_DCTIRQENA_bits;

/* MMA DCT/iDCT IRQ Status Register */
typedef struct {
  __REG32 DCTCOMP             : 1;
  __REG32 DININTR             : 1;
  __REG32 DOUTINTR            : 1;
  __REG32 ERR_INTR            : 1;
  __REG32 FIFO_EMP            : 1;
  __REG32 FIFO_FULL           : 1;
  __REG32                     : 26;
} __MMA_DCTIRQSTAT_bits;

/* MMA DCT/iDCT X-Offset Address */
typedef struct {
  __REG32 XOFFSET             : 16;
  __REG32                     : 16;
} __MMA_DCTXOFF_bits;

/* MMA DCT/iDCT Y-Offset Address */
typedef struct {
  __REG32 YOFFSET             : 16;
  __REG32                     : 16;
} __MMA_DCTYOFF_bits;

/* MMA DCT/iDCT XY Count */
typedef struct {
  __REG32 XCOUNT              : 7;
  __REG32                     : 1;
  __REG32 YCOUNT              : 7;
  __REG32                     : 17;
} __MMA_DCTXYCNT_bits;

/* MMA DCT/iDCT Skip Address */
typedef struct {
  __REG32 SKIP_ADDR           : 16;
  __REG32                     : 16;
} __MMA_DCTSKIP_bits;


/* -------------------------------------------------------------------------*/
/*               AITC registers                                             */
/* -------------------------------------------------------------------------*/

typedef struct {        /* Interrupt Control Register (0x00223000) Reset (0x00000000)                   */
  __REG32                 : 19;   // Bits 0-18    - Reserved
  __REG32 FIAD            : 1;    // Bit 19       - Fast Interrupt Arbiter Disable
  __REG32 NIAD            : 1;    // Bit 20       - Normal Interrupt Arbiter Disable
  __REG32                 :11;    // Bits 21-31   - Reserved
} __INTCNTL_bits;

typedef struct {        /* Normal Interrupt Mask Register (0x00223004) Reset (0x0000001F)                       */
  __REG32 NIMASK  : 5;    // Bits 0-4     - Normal Interrupt Mask (0 = Disable priority level 0 ints, 1 = disable priority 1 and lower... 16+ = disable all interrupts)
  __REG32         :27;    // Bits 5-31    - Reserved
} __NIMASK_bits;

typedef struct {        /* Interrupt Enable Number Register (0x00223008) Reset (0x00000000)                     */
  __REG32 ENNUM           : 6;    // Bits 0-5     - Interrupt Enable Number - Enables/Disables the interrupt source associated with this value.
  __REG32                 :26;    // Bits 6-31    - Reserved
} __INTENNUM_bits;

typedef struct {        /* Interrupt Disable Number Register (0x0022300C) Reset (0x00000000)                    */
  __REG32 DISNUM          : 6;    // Bits 0-5     - Interrupt Disable Number - Enables/Disables the interrupt source associated with this value.
  __REG32                 :26;    // Bits 6-31    - Reserved
} __INTDISNUM_bits;

typedef struct {        /* Interrupt Enable Register High (0x00223010) Reset (0x00000000)                       */
  __REG32 INTENABLE32 :1; // Bit  0               - Interrupt Enable
  __REG32 INTENABLE33 :1; // Bit  1               - Interrupt Enable
  __REG32 INTENABLE34 :1; // Bit  2               - Interrupt Enable
  __REG32 INTENABLE35 :1; // Bit  3               - Interrupt Enable
  __REG32 INTENABLE36 :1; // Bit  4               - Interrupt Enable
  __REG32 INTENABLE37 :1; // Bit  5               - Interrupt Enable
  __REG32 INTENABLE38 :1; // Bit  6               - Interrupt Enable
  __REG32 INTENABLE39 :1; // Bit  7               - Interrupt Enable
  __REG32 INTENABLE40 :1; // Bit  8               - Interrupt Enable
  __REG32 INTENABLE41 :1; // Bit  9               - Interrupt Enable
  __REG32 INTENABLE42 :1; // Bit  10              - Interrupt Enable
  __REG32 INTENABLE43 :1; // Bit  11              - Interrupt Enable
  __REG32 INTENABLE44 :1; // Bit  12              - Interrupt Enable
  __REG32 INTENABLE45 :1; // Bit  13              - Interrupt Enable
  __REG32 INTENABLE46 :1; // Bit  14              - Interrupt Enable
  __REG32 INTENABLE47 :1; // Bit  15              - Interrupt Enable
  __REG32 INTENABLE48 :1; // Bit  16              - Interrupt Enable
  __REG32 INTENABLE49 :1; // Bit  17              - Interrupt Enable
  __REG32 INTENABLE50 :1; // Bit  18              - Interrupt Enable
  __REG32 INTENABLE51 :1; // Bit  19              - Interrupt Enable
  __REG32 INTENABLE52 :1; // Bit  20              - Interrupt Enable
  __REG32 INTENABLE53 :1; // Bit  21              - Interrupt Enable
  __REG32 INTENABLE54 :1; // Bit  22              - Interrupt Enable
  __REG32 INTENABLE55 :1; // Bit  23              - Interrupt Enable
  __REG32 INTENABLE56 :1; // Bit  24              - Interrupt Enable
  __REG32 INTENABLE57 :1; // Bit  25              - Interrupt Enable
  __REG32 INTENABLE58 :1; // Bit  26              - Interrupt Enable
  __REG32 INTENABLE59 :1; // Bit  27              - Interrupt Enable
  __REG32 INTENABLE60 :1; // Bit  28              - Interrupt Enable
  __REG32 INTENABLE61 :1; // Bit  29              - Interrupt Enable
  __REG32 INTENABLE62 :1; // Bit  30              - Interrupt Enable
  __REG32 INTENABLE63 :1; // Bit  31              - Interrupt Enable
} __INTENABLEH_bits;

typedef struct {        /* Interrupt Enable Register Low (0x00223014) Reset (0x00000000)                        */
  __REG32 INTENABLE0  :1; // Bit  0               - Interrupt Enable
  __REG32 INTENABLE1  :1; // Bit  1               - Interrupt Enable
  __REG32 INTENABLE2  :1; // Bit  2               - Interrupt Enable
  __REG32 INTENABLE3  :1; // Bit  3               - Interrupt Enable
  __REG32 INTENABLE4  :1; // Bit  4               - Interrupt Enable
  __REG32 INTENABLE5  :1; // Bit  5               - Interrupt Enable
  __REG32 INTENABLE6  :1; // Bit  6               - Interrupt Enable
  __REG32 INTENABLE7  :1; // Bit  7               - Interrupt Enable
  __REG32 INTENABLE8  :1; // Bit  8               - Interrupt Enable
  __REG32 INTENABLE9  :1; // Bit  9               - Interrupt Enable
  __REG32 INTENABLE10 :1; // Bit  10              - Interrupt Enable
  __REG32 INTENABLE11 :1; // Bit  11              - Interrupt Enable
  __REG32 INTENABLE12 :1; // Bit  12              - Interrupt Enable
  __REG32 INTENABLE13 :1; // Bit  13              - Interrupt Enable
  __REG32 INTENABLE14 :1; // Bit  14              - Interrupt Enable
  __REG32 INTENABLE15 :1; // Bit  15              - Interrupt Enable
  __REG32 INTENABLE16 :1; // Bit  16              - Interrupt Enable
  __REG32 INTENABLE17 :1; // Bit  17              - Interrupt Enable
  __REG32 INTENABLE18 :1; // Bit  18              - Interrupt Enable
  __REG32 INTENABLE19 :1; // Bit  19              - Interrupt Enable
  __REG32 INTENABLE20 :1; // Bit  20              - Interrupt Enable
  __REG32 INTENABLE21 :1; // Bit  21              - Interrupt Enable
  __REG32 INTENABLE22 :1; // Bit  22              - Interrupt Enable
  __REG32 INTENABLE23 :1; // Bit  23              - Interrupt Enable
  __REG32 INTENABLE24 :1; // Bit  24              - Interrupt Enable
  __REG32 INTENABLE25 :1; // Bit  25              - Interrupt Enable
  __REG32 INTENABLE26 :1; // Bit  26              - Interrupt Enable
  __REG32 INTENABLE27 :1; // Bit  27              - Interrupt Enable
  __REG32 INTENABLE28 :1; // Bit  28              - Interrupt Enable
  __REG32 INTENABLE29 :1; // Bit  29              - Interrupt Enable
  __REG32 INTENABLE30 :1; // Bit  30              - Interrupt Enable
  __REG32 INTENABLE31 :1; // Bit  31              - Interrupt Enable
} __INTENABLEL_bits;

typedef struct {        /* Interrupt Type Register High (0x00223018) Reset (0x00000000)                 */
  __REG32 INTTYPE32 :1;   // Bit  0               - Interrupt Enable
  __REG32 INTTYPE33 :1;   // Bit  1               - Interrupt Enable
  __REG32 INTTYPE34 :1;   // Bit  2               - Interrupt Enable
  __REG32 INTTYPE35 :1;   // Bit  3               - Interrupt Enable
  __REG32 INTTYPE36 :1;   // Bit  4               - Interrupt Enable
  __REG32 INTTYPE37 :1;   // Bit  5               - Interrupt Enable
  __REG32 INTTYPE38 :1;   // Bit  6               - Interrupt Enable
  __REG32 INTTYPE39 :1;   // Bit  7               - Interrupt Enable
  __REG32 INTTYPE40 :1;   // Bit  8               - Interrupt Enable
  __REG32 INTTYPE41 :1;   // Bit  9               - Interrupt Enable
  __REG32 INTTYPE42 :1;   // Bit  10              - Interrupt Enable
  __REG32 INTTYPE43 :1;   // Bit  11              - Interrupt Enable
  __REG32 INTTYPE44 :1;   // Bit  12              - Interrupt Enable
  __REG32 INTTYPE45 :1;   // Bit  13              - Interrupt Enable
  __REG32 INTTYPE46 :1;   // Bit  14              - Interrupt Enable
  __REG32 INTTYPE47 :1;   // Bit  15              - Interrupt Enable
  __REG32 INTTYPE48 :1;   // Bit  16              - Interrupt Enable
  __REG32 INTTYPE49 :1;   // Bit  17              - Interrupt Enable
  __REG32 INTTYPE50 :1;   // Bit  18              - Interrupt Enable
  __REG32 INTTYPE51 :1;   // Bit  19              - Interrupt Enable
  __REG32 INTTYPE52 :1;   // Bit  20              - Interrupt Enable
  __REG32 INTTYPE53 :1;   // Bit  21              - Interrupt Enable
  __REG32 INTTYPE54 :1;   // Bit  22              - Interrupt Enable
  __REG32 INTTYPE55 :1;   // Bit  23              - Interrupt Enable
  __REG32 INTTYPE56 :1;   // Bit  24              - Interrupt Enable
  __REG32 INTTYPE57 :1;   // Bit  25              - Interrupt Enable
  __REG32 INTTYPE58 :1;   // Bit  26              - Interrupt Enable
  __REG32 INTTYPE59 :1;   // Bit  27              - Interrupt Enable
  __REG32 INTTYPE60 :1;   // Bit  28              - Interrupt Enable
  __REG32 INTTYPE61 :1;   // Bit  29              - Interrupt Enable
  __REG32 INTTYPE62 :1;   // Bit  30              - Interrupt Enable
  __REG32 INTTYPE63 :1;   // Bit  31              - Interrupt Enable
} __INTTYPEH_bits;

typedef struct {        /* Interrupt Enable Register Low (0x0022301C) Reset (0x00000000)                        */
  __REG32 INTTYPE0  :1;   // Bit  0               - Interrupt Enable
  __REG32 INTTYPE1  :1;   // Bit  1               - Interrupt Enable
  __REG32 INTTYPE2  :1;   // Bit  2               - Interrupt Enable
  __REG32 INTTYPE3  :1;   // Bit  3               - Interrupt Enable
  __REG32 INTTYPE4  :1;   // Bit  4               - Interrupt Enable
  __REG32 INTTYPE5  :1;   // Bit  5               - Interrupt Enable
  __REG32 INTTYPE6  :1;   // Bit  6               - Interrupt Enable
  __REG32 INTTYPE7  :1;   // Bit  7               - Interrupt Enable
  __REG32 INTTYPE8  :1;   // Bit  8               - Interrupt Enable
  __REG32 INTTYPE9  :1;   // Bit  9               - Interrupt Enable
  __REG32 INTTYPE10 :1;   // Bit  10              - Interrupt Enable
  __REG32 INTTYPE11 :1;   // Bit  11              - Interrupt Enable
  __REG32 INTTYPE12 :1;   // Bit  12              - Interrupt Enable
  __REG32 INTTYPE13 :1;   // Bit  13              - Interrupt Enable
  __REG32 INTTYPE14 :1;   // Bit  14              - Interrupt Enable
  __REG32 INTTYPE15 :1;   // Bit  15              - Interrupt Enable
  __REG32 INTTYPE16 :1;   // Bit  16              - Interrupt Enable
  __REG32 INTTYPE17 :1;   // Bit  17              - Interrupt Enable
  __REG32 INTTYPE18 :1;   // Bit  18              - Interrupt Enable
  __REG32 INTTYPE19 :1;   // Bit  19              - Interrupt Enable
  __REG32 INTTYPE20 :1;   // Bit  20              - Interrupt Enable
  __REG32 INTTYPE21 :1;   // Bit  21              - Interrupt Enable
  __REG32 INTTYPE22 :1;   // Bit  22              - Interrupt Enable
  __REG32 INTTYPE23 :1;   // Bit  23              - Interrupt Enable
  __REG32 INTTYPE24 :1;   // Bit  24              - Interrupt Enable
  __REG32 INTTYPE25 :1;   // Bit  25              - Interrupt Enable
  __REG32 INTTYPE26 :1;   // Bit  26              - Interrupt Enable
  __REG32 INTTYPE27 :1;   // Bit  27              - Interrupt Enable
  __REG32 INTTYPE28 :1;   // Bit  28              - Interrupt Enable
  __REG32 INTTYPE29 :1;   // Bit  29              - Interrupt Enable
  __REG32 INTTYPE30 :1;   // Bit  30              - Interrupt Enable
  __REG32 INTTYPE31 :1;   // Bit  31              - Interrupt Enable
} __INTTYPEL_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 7 (0x00223020) Reset (0x00000000)                   */
  __REG32 NIPR56          : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR57          : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR58          : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR59          : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR60          : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR61          : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR62          : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR63          : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY7_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 6 (0x00223024) Reset (0x00000000)                   */
  __REG32 NIPR48          : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR49          : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR50          : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR51          : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR52          : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR53          : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR54          : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR55          : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY6_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 5 (0x00223028) Reset (0x00000000)                   */
  __REG32 NIPR40          : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR41          : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR42          : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR43          : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR44          : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR45          : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR46          : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR47          : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY5_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 4 (0x0022302C) Reset (0x00000000)                   */
  __REG32 NIPR32          : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR33          : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR34          : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR35          : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR36          : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR37          : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR38          : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR39          : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY4_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 3 (0x00223030) Reset (0x00000000)                   */
  __REG32 NIPR24          : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR25          : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR26          : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR27          : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR28          : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR29          : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR30          : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR31          : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY3_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 2 (0x00223034) Reset (0x00000000)                   */
  __REG32 NIPR16          : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR17          : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR18          : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR19          : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR20          : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR21          : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR22          : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR23          : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY2_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 1 (0x00223038) Reset (0x00000000)                   */
  __REG32 NIPR8           : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR9           : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR10          : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR11          : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR12          : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR13          : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR14          : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR15          : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY1_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 0 (0x0022303C) Reset (0x00000000)                   */
  __REG32 NIPR0           : 4;    // Bits 0-3     - Normal Interrupt Priority Level
  __REG32 NIPR1           : 4;    // Bits 4-7     - Normal Interrupt Priority Level
  __REG32 NIPR2           : 4;    // Bits 8-11    - Normal Interrupt Priority Level
  __REG32 NIPR3           : 4;    // Bits 12-15   - Normal Interrupt Priority Level
  __REG32 NIPR4           : 4;    // Bits 16-19   - Normal Interrupt Priority Level
  __REG32 NIPR5           : 4;    // Bits 20-23   - Normal Interrupt Priority Level
  __REG32 NIPR6           : 4;    // Bits 24-27   - Normal Interrupt Priority Level
  __REG32 NIPR7           : 4;    // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY0_bits;

typedef struct {        /* Normal Interrupt Vector and Status Register (0x00223040) Reset (0xFFFFFFFF)  */
  __REG32 NIPRILVL   : 16;   // Bits 0-15    - Normal Interrupt Priority Level - Indicates the priority level of the highest priority normal interrupt.
  __REG32 NIVECTOR   : 16;   // Bits 16-31   - Normal Interrupt Vector - Indicates vector index for the highest pending normal interrupt.
} __NIVECSR_bits;

typedef struct {        /* Normal Interrupt Vector and Status Register (0x00223040) Reset (0xFFFFFFFF)  */
  __REG32 NIVECTOR        : 32;   // Bits 0-31    - Fast Interrupt Vector - Indicates vector index for the highest pending fast interrupt.
} __FIVECSR_bits;

typedef struct {        /* Interrupt Source Register High (0x00223048) Reset (0x00000000)       */
  __REG32 INTIN32 : 1;    // Bit  0       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN33 : 1;    // Bit  1       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN34 : 1;    // Bit  2       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN35 : 1;    // Bit  3       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN36 : 1;    // Bit  4       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN37 : 1;    // Bit  5       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN38 : 1;    // Bit  6       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN39 : 1;    // Bit  7       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN40 : 1;    // Bit  8       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN41 : 1;    // Bit  9       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN42 : 1;    // Bit  10      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN43 : 1;    // Bit  11      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN44 : 1;    // Bit  12      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN45 : 1;    // Bit  13      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN46 : 1;    // Bit  14      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN47 : 1;    // Bit  15      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN48 : 1;    // Bit  16      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN49 : 1;    // Bit  17      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN50 : 1;    // Bit  18      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN51 : 1;    // Bit  19      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN52 : 1;    // Bit  20      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN53 : 1;    // Bit  21      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN54 : 1;    // Bit  22      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN55 : 1;    // Bit  23      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN56 : 1;    // Bit  24      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN57 : 1;    // Bit  25      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN58 : 1;    // Bit  26      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN59 : 1;    // Bit  27      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN60 : 1;    // Bit  28      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN61 : 1;    // Bit  29      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN62 : 1;    // Bit  30      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN63 : 1;    // Bit  31      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
} __INTSRCH_bits;

typedef struct {        /* Interrupt Source Register Low (0x0022304C) Reset (0x00000000)        */
  __REG32 INTIN0  : 1;    // Bit  0       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN1  : 1;    // Bit  1       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN2  : 1;    // Bit  2       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN3  : 1;    // Bit  3       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN4  : 1;    // Bit  4       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN5  : 1;    // Bit  5       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN6  : 1;    // Bit  6       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN7  : 1;    // Bit  7       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN8  : 1;    // Bit  8       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN9  : 1;    // Bit  9       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN10: 1;     // Bit  10      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN11: 1;     // Bit  11      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN12: 1;     // Bit  12      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN13: 1;     // Bit  13      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN14: 1;     // Bit  14      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN15: 1;     // Bit  15      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN16: 1;     // Bit  16      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN17: 1;     // Bit  17      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN18: 1;     // Bit  18      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN19: 1;     // Bit  19      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN20: 1;     // Bit  20      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN21: 1;     // Bit  21      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN22: 1;     // Bit  22      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN23: 1;     // Bit  23      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN24: 1;     // Bit  24      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN25: 1;     // Bit  25      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN26: 1;     // Bit  26      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN27: 1;     // Bit  27      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN28: 1;     // Bit  28      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN29: 1;     // Bit  29      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN30: 1;     // Bit  30      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
  __REG32 INTIN31: 1;     // Bit  31      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
} __INTSRCL_bits;

typedef struct {        /* Interrupt Force Register High (0x00223050) Reset (0x00000000)        */
  __REG32 FORCE32 : 1;    // Bit  0       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE33 : 1;    // Bit  1       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE34 : 1;    // Bit  2       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE35 : 1;    // Bit  3       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE36 : 1;    // Bit  4       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE37 : 1;    // Bit  5       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE38 : 1;    // Bit  6       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE39 : 1;    // Bit  7       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE40 : 1;    // Bit  8       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE41 : 1;    // Bit  9       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE42 : 1;    // Bit  10      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE43 : 1;    // Bit  11      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE44 : 1;    // Bit  12      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE45 : 1;    // Bit  13      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE46 : 1;    // Bit  14      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE47 : 1;    // Bit  15      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE48 : 1;    // Bit  16      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE49 : 1;    // Bit  17      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE50 : 1;    // Bit  18      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE51 : 1;    // Bit  19      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE52 : 1;    // Bit  20      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE53 : 1;    // Bit  21      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE54 : 1;    // Bit  22      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE55 : 1;    // Bit  23      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE56 : 1;    // Bit  24      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE57 : 1;    // Bit  25      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE58 : 1;    // Bit  26      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE59 : 1;    // Bit  27      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE60 : 1;    // Bit  28      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE61 : 1;    // Bit  29      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE62 : 1;    // Bit  30      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE63 : 1;    // Bit  31      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
} __INTFRCH_bits;

typedef struct {        /* Interrupt Force Register Low (0x00223054) Reset (0x00000000) */
  __REG32 FORCE0  : 1;    // Bit  0       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE1  : 1;    // Bit  1       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE2  : 1;    // Bit  2       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE3  : 1;    // Bit  3       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE4  : 1;    // Bit  4       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE5  : 1;    // Bit  5       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE6  : 1;    // Bit  6       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE7  : 1;    // Bit  7       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE8  : 1;    // Bit  8       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE9  : 1;    // Bit  9       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE10: 1;     // Bit  10      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE11: 1;     // Bit  11      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE12: 1;     // Bit  12      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE13: 1;     // Bit  13      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE14: 1;     // Bit  14      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE15: 1;     // Bit  15      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE16: 1;     // Bit  16      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE17: 1;     // Bit  17      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE18: 1;     // Bit  18      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE19: 1;     // Bit  19      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE20: 1;     // Bit  20      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE21: 1;     // Bit  21      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE22: 1;     // Bit  22      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE23: 1;     // Bit  23      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE24: 1;     // Bit  24      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE25: 1;     // Bit  25      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE26: 1;     // Bit  26      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE27: 1;     // Bit  27      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE28: 1;     // Bit  28      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE29: 1;     // Bit  29      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE30: 1;     // Bit  30      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
  __REG32 FORCE31: 1;     // Bit  31      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
} __INTFRCL_bits;

typedef struct {        /* Normal Interrupt Pending Register High (0x00223058) Reset (0x00000000)       */
  __REG32 NIPEND32        : 1;    // Bit  0       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND33        : 1;    // Bit  1       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND34        : 1;    // Bit  2       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND35        : 1;    // Bit  3       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND36        : 1;    // Bit  4       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND37        : 1;    // Bit  5       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND38        : 1;    // Bit  6       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND39        : 1;    // Bit  7       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND40        : 1;    // Bit  8       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND41        : 1;    // Bit  9       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND42        : 1;    // Bit  10      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND43        : 1;    // Bit  11      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND44        : 1;    // Bit  12      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND45        : 1;    // Bit  13      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND46        : 1;    // Bit  14      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND47        : 1;    // Bit  15      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND48        : 1;    // Bit  16      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND49        : 1;    // Bit  17      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND50        : 1;    // Bit  18      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND51        : 1;    // Bit  19      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND52        : 1;    // Bit  20      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND53        : 1;    // Bit  21      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND54        : 1;    // Bit  22      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND55        : 1;    // Bit  23      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND56        : 1;    // Bit  24      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND57        : 1;    // Bit  25      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND58        : 1;    // Bit  26      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND59        : 1;    // Bit  27      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND60        : 1;    // Bit  28      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND61        : 1;    // Bit  29      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND62        : 1;    // Bit  30      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND63        : 1;    // Bit  31      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
} __NIPNDH_bits;

typedef struct {        /* Normal Interrupt Pending Register Low (0x0022305C) Reset (0x00000000)        */
  __REG32 NIPEND0         : 1;    // Bit  0       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND1         : 1;    // Bit  1       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND2         : 1;    // Bit  2       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND3         : 1;    // Bit  3       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND4         : 1;    // Bit  4       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND5         : 1;    // Bit  5       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND6         : 1;    // Bit  6       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND7         : 1;    // Bit  7       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND8         : 1;    // Bit  8       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND9         : 1;    // Bit  9       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND10        : 1;    // Bit  10      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND11        : 1;    // Bit  11      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND12        : 1;    // Bit  12      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND13        : 1;    // Bit  13      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND14        : 1;    // Bit  14      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND15        : 1;    // Bit  15      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND16        : 1;    // Bit  16      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND17        : 1;    // Bit  17      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND18        : 1;    // Bit  18      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND19        : 1;    // Bit  19      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND20        : 1;    // Bit  20      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND21        : 1;    // Bit  21      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND22        : 1;    // Bit  22      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND23        : 1;    // Bit  23      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND24        : 1;    // Bit  24      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND25        : 1;    // Bit  25      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND26        : 1;    // Bit  26      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND27        : 1;    // Bit  27      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND28        : 1;    // Bit  28      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND29        : 1;    // Bit  29      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND30        : 1;    // Bit  30      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
  __REG32 NIPEND31        : 1;    // Bit  31      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
} __NIPNDL_bits;

typedef struct {        /* Fast Interrupt Pending Register High (0x00223060) Reset (0x00000000) */
  __REG32 FIPEND32        : 1;    // Bit  0       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND33        : 1;    // Bit  1       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND34        : 1;    // Bit  2       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND35        : 1;    // Bit  3       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND36        : 1;    // Bit  4       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND37        : 1;    // Bit  5       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND38        : 1;    // Bit  6       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND39        : 1;    // Bit  7       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND40        : 1;    // Bit  8       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND41        : 1;    // Bit  9       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND42        : 1;    // Bit  10      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND43        : 1;    // Bit  11      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND44        : 1;    // Bit  12      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND45        : 1;    // Bit  13      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND46        : 1;    // Bit  14      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND47        : 1;    // Bit  15      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND48        : 1;    // Bit  16      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND49        : 1;    // Bit  17      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND50        : 1;    // Bit  18      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND51        : 1;    // Bit  19      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND52        : 1;    // Bit  20      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND53        : 1;    // Bit  21      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND54        : 1;    // Bit  22      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND55        : 1;    // Bit  23      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND56        : 1;    // Bit  24      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND57        : 1;    // Bit  25      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND58        : 1;    // Bit  26      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND59        : 1;    // Bit  27      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND60        : 1;    // Bit  28      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND61        : 1;    // Bit  29      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND62        : 1;    // Bit  30      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND63        : 1;    // Bit  31      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
} __FIPNDH_bits;

typedef struct {        /* Fast Interrupt Pending Register Low (0x00223064) Reset (0x00000000)  */
  __REG32 FIPEND0         : 1;    // Bit  0       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND1         : 1;    // Bit  1       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND2         : 1;    // Bit  2       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND3         : 1;    // Bit  3       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND4         : 1;    // Bit  4       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND5         : 1;    // Bit  5       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND6         : 1;    // Bit  6       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND7         : 1;    // Bit  7       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND8         : 1;    // Bit  8       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND9         : 1;    // Bit  9       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND10        : 1;    // Bit  10      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND11        : 1;    // Bit  11      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND12        : 1;    // Bit  12      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND13        : 1;    // Bit  13      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND14        : 1;    // Bit  14      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND15        : 1;    // Bit  15      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND16        : 1;    // Bit  16      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND17        : 1;    // Bit  17      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND18        : 1;    // Bit  18      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND19        : 1;    // Bit  19      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND20        : 1;    // Bit  20      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND21        : 1;    // Bit  21      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND22        : 1;    // Bit  22      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND23        : 1;    // Bit  23      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND24        : 1;    // Bit  24      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND25        : 1;    // Bit  25      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND26        : 1;    // Bit  26      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND27        : 1;    // Bit  27      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND28        : 1;    // Bit  28      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND29        : 1;    // Bit  29      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND30        : 1;    // Bit  30      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
  __REG32 FIPEND31        : 1;    // Bit  31      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
} __FIPNDL_bits;


/* -------------------------------------------------------------------------*/
/*               CSI  registers                                             */
/* -------------------------------------------------------------------------*/

/* CSI Control Register 1 */
typedef struct {
  __REG32 EN                  : 1;
  __REG32 REDGE               : 1;
  __REG32 INV_PCLK            : 1;
  __REG32 INV_DATA            : 1;
  __REG32 GCLK_MODE           : 1;
  __REG32 CLR_RXFIFO          : 1;
  __REG32 CLR_STATFIFO        : 1;
  __REG32 BIG_ENDIAN          : 1;
  __REG32 FCC                 : 1;
  __REG32 MCLKEN              : 1;
  __REG32                     : 2;
  __REG32 MCLKDIV             : 4;
  __REG32 SOF_INTEN           : 1;
  __REG32 SOF_POL             : 1;
  __REG32 RXFF_INTEN          : 1;
  __REG32 RXFF_LEVEL          : 2;
  __REG32 STATFF_INTEN        : 1;
  __REG32 STATFF_LEVEL        : 2;
  __REG32 RF_OR_INTEN         : 1;
  __REG32 SF_OR_INTEN         : 1;
  __REG32                     : 6;
} __CSICR1_bits;

/* CSI Control Register 2 */
typedef struct {
  __REG32 HSC                 : 8;
  __REG32 VSC                 : 8;
  __REG32 LVRM                : 3;
  __REG32 BTS                 : 2;
  __REG32                     : 2;
  __REG32 SCE                 : 1;
  __REG32 AFS                 : 2;
  __REG32 DRM                 : 1;
  __REG32                     : 5;
} __CSICR2_bits;

/* CSI Status Register 1 */
typedef struct {
  __REG32 DRDY                : 1;
  __REG32                     : 15;
  __REG32 SOF_INT             : 1;
  __REG32                     : 1;
  __REG32 RXFF_INT            : 1;
  __REG32                     : 2;
  __REG32 STATFF_INT          : 1;
  __REG32                     : 2;
  __REG32 RFF_OR_INT          : 1;
  __REG32 SFF_OR_INT          : 1;
  __REG32                     : 6;
} __CSISR_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  AIPI1
 **
 ***************************************************************************/
__IO_REG32_BIT(AIPI1_PSR0,0x00200000,__READ_WRITE,__AIPI_PSR0_bits);
__IO_REG32_BIT(AIPI1_PSR1,0x00200004,__READ_WRITE,__AIPI_PSR1_bits);
__IO_REG32_BIT(AIPI1_PAR, 0x00200008,__READ_WRITE,__AIPI_PAR_bits);
__IO_REG32_BIT(AIPI1_PCR, 0x0020000c,__READ_WRITE,__AIPI_PCR_bits);
__IO_REG32_BIT(AIPI1_TSR, 0x00200010,__READ_WRITE,__AIPI_TSR_bits);


/***************************************************************************
 **
 **  AIPI2
 **
 ***************************************************************************/
__IO_REG32_BIT(AIPI2_PSR0,0x00210000,__READ_WRITE,__AIPI_PSR0_bits);
__IO_REG32_BIT(AIPI2_PSR1,0x00210004,__READ_WRITE,__AIPI_PSR1_bits);
__IO_REG32_BIT(AIPI2_PAR, 0x00210008,__READ_WRITE,__AIPI_PAR_bits);
__IO_REG32_BIT(AIPI2_PCR, 0x0021000c,__READ_WRITE,__AIPI_PCR_bits);
__IO_REG32_BIT(AIPI2_TSR, 0x00210010,__READ_WRITE,__AIPI_TSR_bits);


/***************************************************************************
 **
 **  Watchdog
 **
 ***************************************************************************/
__IO_REG32_BIT(WDG_WCR, 0x00201000,__READ_WRITE,__WDG_WCR_bits);
__IO_REG32_BIT(WDG_WSR, 0x00201004,__READ_WRITE,__WDG_WSR_bits);
__IO_REG32_BIT(WDG_WSTR,0x00201008,__READ_WRITE,__WDG_WSTR_bits);


/***************************************************************************
 **
 **  Timer1
 **
 ***************************************************************************/
__IO_REG32_BIT(TCTL1, 0x00202000,__READ_WRITE,__TCTL_bits);
__IO_REG32_BIT(TPRER1,0x00202004,__READ_WRITE,__TPRER_bits);
__IO_REG32_BIT(TCMP1, 0x00202008,__READ_WRITE,__TCMP_bits);
__IO_REG32_BIT(TCR1,  0x0020200C,__READ_WRITE,__TCR_bits);
__IO_REG32_BIT(TCN1,  0x00202010,__READ_WRITE,__TCN_bits);
__IO_REG32_BIT(TSTAT1,0x00202014,__READ_WRITE,__TSTAT_bits);


/***************************************************************************
 **
 **  Timer2
 **
 ***************************************************************************/
__IO_REG32_BIT(TCTL2, 0x00203000,__READ_WRITE,__TCTL_bits);
__IO_REG32_BIT(TPRER2,0x00203004,__READ_WRITE,__TPRER_bits);
__IO_REG32_BIT(TCMP2, 0x00203008,__READ_WRITE,__TCMP_bits);
__IO_REG32_BIT(TCR2,  0x0020300C,__READ_WRITE,__TCR_bits);
__IO_REG32_BIT(TCN2,  0x00203010,__READ_WRITE,__TCN_bits);
__IO_REG32_BIT(TSTAT2,0x00203014,__READ_WRITE,__TSTAT_bits);


/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(HOURMIN, 0x00204000,__READ_WRITE,__HOURMIN_bits);
__IO_REG32_BIT(SECONDS, 0x00204004,__READ_WRITE,__SECONDS_bits);
__IO_REG32_BIT(ALRM_HM, 0x00204008,__READ_WRITE,__HOURMIN_bits);
__IO_REG32_BIT(ALRM_SEC,0x0020400C,__READ_WRITE,__SECONDS_bits);
__IO_REG32_BIT(RCCTL,   0x00204010,__READ_WRITE,__RCCTL_bits);
__IO_REG32_BIT(RTCISR,  0x00204014,__READ_WRITE,__RTCISR_bits);
__IO_REG32_BIT(RTCIENR, 0x00204018,__READ_WRITE,__RTCISR_bits);
__IO_REG32_BIT(STPWCH,  0x0020401C,__READ_WRITE,__STPWCH_bits);
__IO_REG32_BIT(DAYR,    0x00204020,__READ_WRITE,__DAYR_bits);
__IO_REG32_BIT(DAYALARM,0x00204024,__READ_WRITE,__DAYALARM_bits);


/***************************************************************************
 **
 **  LCD
 **
 ***************************************************************************/
__IO_REG32_BIT(SSA,0x00205000,__READ_WRITE,__SSA_bits);
__IO_REG32_BIT(SIZE_REG,0x00205004,__READ_WRITE,__SIZE_REG_bits);
__IO_REG32_BIT(VPW,0x00205008,__READ_WRITE,__VPW_bits);
__IO_REG32_BIT(CPOS,0x0020500C,__READ_WRITE,__CPOS_bits);
__IO_REG32_BIT(LCWHB,0x00205010,__READ_WRITE,__LCWHB_bits);
__IO_REG32_BIT(LCHCC,0x00205014,__READ_WRITE,__LCHCC_bits);
__IO_REG32_BIT(PCR,0x00205018,__READ_WRITE,__PCR_bits);
__IO_REG32_BIT(HCR,0x0020501C,__READ_WRITE,__HCR_bits);
__IO_REG32_BIT(VCR,0x00205020,__READ_WRITE,__VCR_bits);
__IO_REG32_BIT(POS,0x00205024,__READ_WRITE,__POS_bits);
__IO_REG32_BIT(LSCR1,0x00205028,__READ_WRITE,__LSCR1_bits);
__IO_REG32_BIT(PWMR,0x0020502C,__READ_WRITE,__PWMR_bits);
__IO_REG32_BIT(DMACR,0x00205030,__READ_WRITE,__DMACR_bits);
__IO_REG32_BIT(RMCR,0x00205034,__READ_WRITE,__RMCR_bits);
__IO_REG32_BIT(LCDICR,0x00205038,__READ_WRITE,__LCDICR_bits);
__IO_REG32_BIT(LCDISR,0x00205040,__READ_WRITE,__LCDISR_bits);


/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG32_BIT(URX0D_1 ,0x00206000,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX1D_1 ,0x00206004,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX2D_1 ,0x00206008,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX3D_1 ,0x0020600c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX4D_1 ,0x00206010,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX5D_1 ,0x00206014,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX6D_1 ,0x00206018,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX7D_1 ,0x0020601c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX8D_1 ,0x00206020,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX9D_1 ,0x00206024,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX10D_1,0x00206028,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX11D_1,0x0020602c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX12D_1,0x00206030,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX13D_1,0x00206034,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX14D_1,0x00206038,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX15D_1,0x0020603c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(UTX0D_1 ,0x00206040,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX1D_1 ,0x00206044,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX2D_1 ,0x00206048,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX3D_1 ,0x0020604c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX4D_1 ,0x00206050,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX5D_1 ,0x00206054,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX6D_1 ,0x00206058,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX7D_1 ,0x0020605c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX8D_1 ,0x00206060,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX9D_1 ,0x00206064,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX10D_1,0x00206068,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX11D_1,0x0020606c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX12D_1,0x00206070,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX13D_1,0x00206074,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX14D_1,0x00206078,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX15D_1,0x0020607c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UCR1_1  ,0x00206080,__READ_WRITE,__UCR1_bits);
__IO_REG32_BIT(UCR2_1  ,0x00206084,__READ_WRITE,__UCR2_bits);
__IO_REG32_BIT(UCR3_1  ,0x00206088,__READ_WRITE,__UCR3_1_bits);
__IO_REG32_BIT(UCR4_1  ,0x0020608c,__READ_WRITE,__UCR4_bits);
__IO_REG32_BIT(UFCR_1  ,0x00206090,__READ_WRITE,__UFCR_bits);
__IO_REG32_BIT(USR1_1  ,0x00206094,__READ_WRITE,__USR1_bits);
__IO_REG32_BIT(USR2_1  ,0x00206098,__READ_WRITE,__USR2_bits);
__IO_REG32_BIT(UESC_1  ,0x0020609c,__READ_WRITE,__UESC_bits);
__IO_REG32_BIT(UTIM_1  ,0x002060a0,__READ_WRITE,__UTIM_bits);
__IO_REG32_BIT(UBIR_1  ,0x002060a4,__READ_WRITE,__UBIR_bits);
__IO_REG32_BIT(UBMR_1  ,0x002060a8,__READ_WRITE,__UBMR_bits);
__IO_REG32_BIT(UBRC_1  ,0x002060ac,__READ_WRITE,__UBRC_bits);
__IO_REG32_BIT(BIPR1_1 ,0x002060b0,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BIPR2_1 ,0x002060b4,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BIPR3_1 ,0x002060b8,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BIPR4_1 ,0x002060bc,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BMPR1_1 ,0x002060c0,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(BMPR2_1 ,0x002060c4,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(BMPR3_1 ,0x002060c8,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(BMPR4_1 ,0x002060cc,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(UTS_1   ,0x002060d0,__READ_WRITE,__UTS_bits);


/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG32_BIT(URX0D_2 ,0x00207000,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX1D_2 ,0x00207004,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX2D_2 ,0x00207008,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX3D_2 ,0x0020700c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX4D_2 ,0x00207010,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX5D_2 ,0x00207014,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX6D_2 ,0x00207018,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX7D_2 ,0x0020701c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX8D_2 ,0x00207020,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX9D_2 ,0x00207024,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX10D_2,0x00207028,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX11D_2,0x0020702c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX12D_2,0x00207030,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX13D_2,0x00207034,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX14D_2,0x00207038,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(URX15D_2,0x0020703c,__READ_WRITE,__URXD_bits);
__IO_REG32_BIT(UTX0D_2 ,0x00207040,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX1D_2 ,0x00207044,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX2D_2 ,0x00207048,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX3D_2 ,0x0020704c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX4D_2 ,0x00207050,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX5D_2 ,0x00207054,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX6D_2 ,0x00207058,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX7D_2 ,0x0020705c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX8D_2 ,0x00207060,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX9D_2 ,0x00207064,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX10D_2,0x00207068,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX11D_2,0x0020706c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX12D_2,0x00207070,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX13D_2,0x00207074,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX14D_2,0x00207078,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UTX15D_2,0x0020707c,__READ_WRITE,__UTXD_bits);
__IO_REG32_BIT(UCR1_2  ,0x00207080,__READ_WRITE,__UCR1_bits);
__IO_REG32_BIT(UCR2_2  ,0x00207084,__READ_WRITE,__UCR2_bits);
__IO_REG32_BIT(UCR3_2  ,0x00207088,__READ_WRITE,__UCR3_23_bits);
__IO_REG32_BIT(UCR4_2  ,0x0020708c,__READ_WRITE,__UCR4_bits);
__IO_REG32_BIT(UFCR_2  ,0x00207090,__READ_WRITE,__UFCR_bits);
__IO_REG32_BIT(USR1_2  ,0x00207094,__READ_WRITE,__USR1_bits);
__IO_REG32_BIT(USR2_2  ,0x00207098,__READ_WRITE,__USR2_bits);
__IO_REG32_BIT(UESC_2  ,0x0020709c,__READ_WRITE,__UESC_bits);
__IO_REG32_BIT(UTIM_2  ,0x002070a0,__READ_WRITE,__UTIM_bits);
__IO_REG32_BIT(UBIR_2  ,0x002070a4,__READ_WRITE,__UBIR_bits);
__IO_REG32_BIT(UBMR_2  ,0x002070a8,__READ_WRITE,__UBMR_bits);
__IO_REG32_BIT(UBRC_2  ,0x002070ac,__READ_WRITE,__UBRC_bits);
__IO_REG32_BIT(BIPR1_2 ,0x002070b0,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BIPR2_2 ,0x002070b4,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BIPR3_2 ,0x002070b8,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BIPR4_2 ,0x002070bc,__READ_WRITE,__BIPR_bits);
__IO_REG32_BIT(BMPR1_2 ,0x002070c0,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(BMPR2_2 ,0x002070c4,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(BMPR3_2 ,0x002070c8,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(BMPR4_2 ,0x002070cc,__READ_WRITE,__BMPR_bits);
__IO_REG32_BIT(UTS_2   ,0x002070d0,__READ_WRITE,__UTS_bits);

/***************************************************************************
 **
 **  PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(PWMC,  0x00208000,__READ_WRITE,__PWMC_bits);
__IO_REG32_BIT(PWMS,  0x00208004,__READ_WRITE,__PWMS_bits);
__IO_REG32_BIT(PWMP,  0x00208008,__READ_WRITE,__PWMP_bits);
__IO_REG32_BIT(PWMCNT,0x0020800C,__READ_WRITE,__PWMCNT_bits);

/***************************************************************************
 **
 **  DMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DCR,0x00209000,__READ_WRITE,__DCR_bits);
__IO_REG32_BIT(DISR,0x00209004,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DIMR,0x00209008,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DBTOSR,0x0020900C,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DRTOSR,0x00209010,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DSESR,0x00209014,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DBOSR,0x00209018,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DBTOCR,0x0020901C,__READ_WRITE,__DBTOCR_bits);
__IO_REG32_BIT(WSRA,0x00209040,__READ_WRITE,__WSR_bits);
__IO_REG32_BIT(XSRA,0x00209044,__READ_WRITE,__XSR_bits);
__IO_REG32_BIT(YSRA,0x00209048,__READ_WRITE,__YSR_bits);
__IO_REG32_BIT(WSRB,0x0020904C,__READ_WRITE,__WSR_bits);
__IO_REG32_BIT(XSRB,0x00209050,__READ_WRITE,__XSR_bits);
__IO_REG32_BIT(YSRB,0x00209054,__READ_WRITE,__YSR_bits);

__IO_REG32(SAR_CH0,0x00209080,__READ_WRITE);
__IO_REG32(DAR_CH0,0x00209084,__READ_WRITE);
__IO_REG32_BIT(CNTR_CH0,0x00209088,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH0,0x0020908c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH0,0x00209090,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH0,0x00209094,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH0,0x00209098,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH0_bit RTORBUCR_CH0_bit
#define RTOR_CH0     RTORBUCR_CH0
#define BUCR_CH0_bit RTORBUCR_CH0_bit
#define BUCR_CH0     RTORBUCR_CH0

__IO_REG32_BIT(SAR_CH1,0x002090c0,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH1,0x002090c4,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH1,0x002090c8,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH1,0x002090cc,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH1,0x002090d0,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH1,0x002090d4,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH1,0x002090d8,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH1_bit RTORBUCR_CH1_bit
#define RTOR_CH1     RTORBUCR_CH1
#define BUCR_CH1_bit RTORBUCR_CH1_bit
#define BUCR_CH1     RTORBUCR_CH1

__IO_REG32_BIT(SAR_CH2,0x00209100,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH2,0x00209104,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH2,0x00209108,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH2,0x0020910c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH2,0x00209110,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH2,0x00209114,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH2,0x00209118,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH2_bit RTORBUCR_CH2_bit
#define RTOR_CH2     RTORBUCR_CH2
#define BUCR_CH2_bit RTORBUCR_CH2_bit
#define BUCR_CH2     RTORBUCR_CH2

__IO_REG32_BIT(SAR_CH3,0x00209140,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH3,0x00209144,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH3,0x00209148,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH3,0x0020914c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH3,0x00209150,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH3,0x00209154,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH3,0x00209158,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH3_bit RTORBUCR_CH3_bit
#define RTOR_CH3     RTORBUCR_CH3
#define BUCR_CH3_bit RTORBUCR_CH3_bit
#define BUCR_CH3     RTORBUCR_CH3

__IO_REG32_BIT(SAR_CH4,0x00209180,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH4,0x00209184,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH4,0x00209188,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH4,0x0020918c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH4,0x00209190,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH4,0x00209194,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH4,0x00209198,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH4_bit RTORBUCR_CH4_bit
#define RTOR_CH4     RTORBUCR_CH4
#define BUCR_CH4_bit RTORBUCR_CH4_bit
#define BUCR_CH4     RTORBUCR_CH4

__IO_REG32_BIT(SAR_CH5,0x002091c0,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH5,0x002091c4,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH5,0x002091c8,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH5,0x002091cc,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH5,0x002091d0,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH5,0x002091d4,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH5,0x002091d8,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH5_bit RTORBUCR_CH5_bit
#define RTOR_CH5     RTORBUCR_CH5
#define BUCR_CH5_bit RTORBUCR_CH5_bit
#define BUCR_CH5     RTORBUCR_CH5

__IO_REG32_BIT(SAR_CH6,0x00209200,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH6,0x00209204,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH6,0x00209208,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH6,0x0020920c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH6,0x00209210,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH6,0x00209214,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH6,0x00209218,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH6_bit RTORBUCR_CH6_bit
#define RTOR_CH6     RTORBUCR_CH6
#define BUCR_CH6_bit RTORBUCR_CH6_bit
#define BUCR_CH6     RTORBUCR_CH6

__IO_REG32_BIT(SAR_CH7,0x00209240,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH7,0x00209244,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH7,0x00209248,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH7,0x0020924c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH7,0x00209250,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH7,0x00209254,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH7,0x00209258,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH7_bit RTORBUCR_CH7_bit
#define RTOR_CH7     RTORBUCR_CH7
#define BUCR_CH7_bit RTORBUCR_CH7_bit
#define BUCR_CH7     RTORBUCR_CH7

__IO_REG32_BIT(SAR_CH8,0x00209280,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH8,0x00209284,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH8,0x00209288,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH8,0x0020928c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH8,0x00209290,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH8,0x00209294,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH8,0x00209298,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH8_bit RTORBUCR_CH8_bit
#define RTOR_CH8     RTORBUCR_CH8
#define BUCR_CH8_bit RTORBUCR_CH8_bit
#define BUCR_CH8     RTORBUCR_CH8

__IO_REG32_BIT(SAR_CH9,0x002092c0,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH9,0x002092c4,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH9,0x002092c8,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH9,0x002092cc,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH9,0x002092d0,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH9,0x002092d4,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH9,0x002092d8,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH9_bit RTORBUCR_CH9_bit
#define RTOR_CH9     RTORBUCR_CH9
#define BUCR_CH9_bit RTORBUCR_CH9_bit
#define BUCR_CH9     RTORBUCR_CH9

__IO_REG32_BIT(SAR_CH10,0x00209300,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR_CH10,0x00209304,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR_CH10,0x00209308,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR_CH10,0x0020930c,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR_CH10,0x00209310,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR_CH10,0x00209314,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTORBUCR_CH10,0x00209318,__READ_WRITE,__RTORBUCR_bits);
#define RTOR_CH10_bit RTORBUCR_CH10_bit
#define RTOR_CH10     RTORBUCR_CH10
#define BUCR_CH10_bit RTORBUCR_CH10_bit
#define BUCR_CH10     RTORBUCR_CH10


/***************************************************************************
 **
 **  SIM
 **
 ***************************************************************************/
__IO_REG32_BIT(PORT_CNTL,    0x00211000,__READ_WRITE,__PORT_CNTL_bits);
__IO_REG32_BIT(CNTL,         0x00211004,__READ_WRITE,__CNTL_bits);
__IO_REG32_BIT(RCV_THRESHOLD,0x00211008,__READ_WRITE,__RCV_THRESHOLD_bits);
__IO_REG32_BIT(ENABLE,       0x0021100C,__READ_WRITE,__ENABLE_bits);
__IO_REG32_BIT(XMT_STATUS,   0x00211010,__READ_WRITE,__XMT_STATUS_bits);
__IO_REG32_BIT(RCV_STATUS,   0x00211014,__READ_WRITE,__RCV_STATUS_bits);
__IO_REG32_BIT(SIM_INT_MASK, 0x00211018,__READ_WRITE,__SIM_INT_MASK_bits);
__IO_REG32_BIT(XMT_BUF,      0x0021101C,__READ_WRITE,__XMT_BUF_bits);
__IO_REG32_BIT(RCV_BUF,      0x00211020,__READ_WRITE,__RCV_BUF_bits);
__IO_REG32_BIT(PORT_DETECT,  0x00211024,__READ_WRITE,__PORT_DETECT_bits);
__IO_REG32_BIT(XMT_THRESHOLD,0x00211028,__READ_WRITE,__XMT_THRESHOLD_bits);
__IO_REG32_BIT(GUARD_CNTL,   0x0021102C,__READ_WRITE,__GUARD_CNTL_bits);
__IO_REG32_BIT(OD_CONFIG,    0x00211030,__READ_WRITE,__OD_CONFIG_bits);
__IO_REG32_BIT(RESET_CNTL,   0x00211034,__READ_WRITE,__RESET_CNTL_bits);
__IO_REG32_BIT(CHAR_WAIT,    0x00211038,__READ_WRITE,__CHAR_WAIT_bits);
__IO_REG32_BIT(GPCNT,        0x0021103C,__READ_WRITE,__GPCNT_bits);
__IO_REG32_BIT(DIVISOR,      0x00211040,__READ_WRITE,__DIVISOR_bits);


/***************************************************************************
 **
 **  USB
 **
 ***************************************************************************/
__IO_REG32_BIT(USB_FRAME,    0x00212000,__READ_WRITE,__USB_FRAME_bits);
__IO_REG32_BIT(USB_SPEC,     0x00212004,__READ_WRITE,__USB_SPEC_bits);
__IO_REG32_BIT(USB_STAT,     0x00212008,__READ_WRITE,__USB_STAT_bits);
__IO_REG32_BIT(USB_CTRL,     0x0021200C,__READ_WRITE,__USB_CTRL_bits);
__IO_REG32_BIT(USB_DADR,     0x00212010,__READ_WRITE,__USB_DADR_bits);
__IO_REG32_BIT(USB_DDAT,     0x00212014,__READ_WRITE,__USB_DDAT_bits);
__IO_REG32_BIT(USB_INTR,     0x00212018,__READ_WRITE,__USB_INTR_bits);
__IO_REG32_BIT(USB_MASK,     0x0021201C,__READ_WRITE,__USB_MASK_bits);
__IO_REG32_BIT(USB_ENAB,     0x00212024,__READ_WRITE,__USB_ENAB_bits);

__IO_REG32_BIT(USB_EP0_STAT, 0x00212030,__READ_WRITE,__USB_EP_STAT_bits);
__IO_REG32_BIT(USB_EP0_INTR, 0x00212034,__READ_WRITE,__USB_EP_INTR_bits);
__IO_REG32_BIT(USB_EP0_MASK, 0x00212038,__READ_WRITE,__USB_EP_MASK_bits);
__IO_REG32(USB_EP0_FDAT, 0x0021203C,__READ_WRITE);
__IO_REG32_BIT(USB_EP0_FSTAT,0x00212040,__READ_WRITE,__USB_EP_FSTAT_bits);
__IO_REG32_BIT(USB_EP0_FCTRL,0x00212044,__READ_WRITE,__USB_EP_FCTRL_bits);
__IO_REG32_BIT(USB_EP0_LRFP, 0x00212048,__READ_WRITE,__USB_EP_LRFP_bits);
__IO_REG32_BIT(USB_EP0_LWFP, 0x0021204C,__READ_WRITE,__USB_EP_LWFP_bits);
__IO_REG32_BIT(USB_EP0_FALRM,0x00212050,__READ_WRITE,__USB_EP_FALRM_bits);
__IO_REG32_BIT(USB_EP0_FRDP, 0x00212054,__READ_WRITE,__USB_EP_FRDP_bits);
__IO_REG32_BIT(USB_EP0_FWRP, 0x00212058,__READ_WRITE,__USB_EP_FWRP_bits);

__IO_REG32_BIT(USB_EP1_STAT, 0x00212060,__READ_WRITE,__USB_EP_STAT_bits);
__IO_REG32_BIT(USB_EP1_INTR, 0x00212064,__READ_WRITE,__USB_EP_INTR_bits);
__IO_REG32_BIT(USB_EP1_MASK, 0x00212068,__READ_WRITE,__USB_EP_MASK_bits);
__IO_REG32(USB_EP1_FDAT, 0x0021206C,__READ_WRITE);
__IO_REG32_BIT(USB_EP1_FSTAT,0x00212070,__READ_WRITE,__USB_EP_FSTAT_bits);
__IO_REG32_BIT(USB_EP1_FCTRL,0x00212074,__READ_WRITE,__USB_EP_FCTRL_bits);
__IO_REG32_BIT(USB_EP1_LRFP, 0x00212078,__READ_WRITE,__USB_EP_LRFP_bits);
__IO_REG32_BIT(USB_EP1_LWFP, 0x0021207C,__READ_WRITE,__USB_EP_LWFP_bits);
__IO_REG32_BIT(USB_EP1_FALRM,0x00212080,__READ_WRITE,__USB_EP_FALRM_bits);
__IO_REG32_BIT(USB_EP1_FRDP, 0x00212084,__READ_WRITE,__USB_EP_FRDP_bits);
__IO_REG32_BIT(USB_EP1_FWRP, 0x00212088,__READ_WRITE,__USB_EP_FWRP_bits);

__IO_REG32_BIT(USB_EP2_STAT, 0x00212090,__READ_WRITE,__USB_EP_STAT_bits);
__IO_REG32_BIT(USB_EP2_INTR, 0x00212094,__READ_WRITE,__USB_EP_INTR_bits);
__IO_REG32_BIT(USB_EP2_MASK, 0x00212098,__READ_WRITE,__USB_EP_MASK_bits);
__IO_REG32(USB_EP2_FDAT, 0x0021209C,__READ_WRITE);
__IO_REG32_BIT(USB_EP2_FSTAT,0x002120A0,__READ_WRITE,__USB_EP_FSTAT_bits);
__IO_REG32_BIT(USB_EP2_FCTRL,0x002120A4,__READ_WRITE,__USB_EP_FCTRL_bits);
__IO_REG32_BIT(USB_EP2_LRFP, 0x002120A8,__READ_WRITE,__USB_EP_LRFP_bits);
__IO_REG32_BIT(USB_EP2_LWFP, 0x002120AC,__READ_WRITE,__USB_EP_LWFP_bits);
__IO_REG32_BIT(USB_EP2_FALRM,0x002120B0,__READ_WRITE,__USB_EP_FALRM_bits);
__IO_REG32_BIT(USB_EP2_FRDP, 0x002120B4,__READ_WRITE,__USB_EP_FRDP_bits);
__IO_REG32_BIT(USB_EP2_FWRP, 0x002120B8,__READ_WRITE,__USB_EP_FWRP_bits);

__IO_REG32_BIT(USB_EP3_STAT, 0x002120C0,__READ_WRITE,__USB_EP_STAT_bits);
__IO_REG32_BIT(USB_EP3_INTR, 0x002120C4,__READ_WRITE,__USB_EP_INTR_bits);
__IO_REG32_BIT(USB_EP3_MASK, 0x002120C8,__READ_WRITE,__USB_EP_MASK_bits);
__IO_REG32(USB_EP3_FDAT, 0x002120CC,__READ_WRITE);
__IO_REG32_BIT(USB_EP3_FSTAT,0x002120D0,__READ_WRITE,__USB_EP_FSTAT_bits);
__IO_REG32_BIT(USB_EP3_FCTRL,0x002120D4,__READ_WRITE,__USB_EP_FCTRL_bits);
__IO_REG32_BIT(USB_EP3_LRFP, 0x002120D8,__READ_WRITE,__USB_EP_LRFP_bits);
__IO_REG32_BIT(USB_EP3_LWFP, 0x002120DC,__READ_WRITE,__USB_EP_LWFP_bits);
__IO_REG32_BIT(USB_EP3_FALRM,0x002120E0,__READ_WRITE,__USB_EP_FALRM_bits);
__IO_REG32_BIT(USB_EP3_FRDP, 0x002120E4,__READ_WRITE,__USB_EP_FRDP_bits);
__IO_REG32_BIT(USB_EP3_FWRP, 0x002120E8,__READ_WRITE,__USB_EP_FWRP_bits);

__IO_REG32_BIT(USB_EP4_STAT, 0x002120F0,__READ_WRITE,__USB_EP_STAT_bits);
__IO_REG32_BIT(USB_EP4_INTR, 0x002120F4,__READ_WRITE,__USB_EP_INTR_bits);
__IO_REG32_BIT(USB_EP4_MASK, 0x002120F8,__READ_WRITE,__USB_EP_MASK_bits);
__IO_REG32(USB_EP4_FDAT, 0x002120FC,__READ_WRITE);
__IO_REG32_BIT(USB_EP4_FSTAT,0x00212100,__READ_WRITE,__USB_EP_FSTAT_bits);
__IO_REG32_BIT(USB_EP4_FCTRL,0x00212104,__READ_WRITE,__USB_EP_FCTRL_bits);
__IO_REG32_BIT(USB_EP4_LRFP, 0x00212108,__READ_WRITE,__USB_EP_LRFP_bits);
__IO_REG32_BIT(USB_EP4_LWFP, 0x0021210C,__READ_WRITE,__USB_EP_LWFP_bits);
__IO_REG32_BIT(USB_EP4_FALRM,0x00212110,__READ_WRITE,__USB_EP_FALRM_bits);
__IO_REG32_BIT(USB_EP4_FRDP, 0x00212114,__READ_WRITE,__USB_EP_FRDP_bits);
__IO_REG32_BIT(USB_EP4_FWRP, 0x00212118,__READ_WRITE,__USB_EP_FWRP_bits);

__IO_REG32_BIT(USB_EP5_STAT, 0x00212120,__READ_WRITE,__USB_EP_STAT_bits);
__IO_REG32_BIT(USB_EP5_INTR, 0x00212124,__READ_WRITE,__USB_EP_INTR_bits);
__IO_REG32_BIT(USB_EP5_MASK, 0x00212128,__READ_WRITE,__USB_EP_MASK_bits);
__IO_REG32(USB_EP5_FDAT, 0x0021212C,__READ_WRITE);
__IO_REG32_BIT(USB_EP5_FSTAT,0x00212130,__READ_WRITE,__USB_EP_FSTAT_bits);
__IO_REG32_BIT(USB_EP5_FCTRL,0x00212134,__READ_WRITE,__USB_EP_FCTRL_bits);
__IO_REG32_BIT(USB_EP5_LRFP, 0x00212138,__READ_WRITE,__USB_EP_LRFP_bits);
__IO_REG32_BIT(USB_EP5_LWFP, 0x0021213C,__READ_WRITE,__USB_EP_LWFP_bits);
__IO_REG32_BIT(USB_EP5_FALRM,0x00212140,__READ_WRITE,__USB_EP_FALRM_bits);
__IO_REG32_BIT(USB_EP5_FRDP, 0x00212144,__READ_WRITE,__USB_EP_FRDP_bits);
__IO_REG32_BIT(USB_EP5_FWRP, 0x00212148,__READ_WRITE,__USB_EP_FWRP_bits);


/***************************************************************************
 **
 **  SPI1
 **
 ***************************************************************************/
__IO_REG32_BIT(RXDATAREG1, 0x00213000,__READ_WRITE,__RXTXDATAREG_bits);
__IO_REG32_BIT(TXDATAREG1, 0x00213004,__READ_WRITE,__RXTXDATAREG_bits);
__IO_REG32_BIT(CONTROLREG1,0x00213008,__READ_WRITE,__CONTROLREG_bits);
__IO_REG32_BIT(INTREG1,    0x0021300C,__READ_WRITE,__INTREG_bits);
__IO_REG32_BIT(TESTREG1,   0x00213010,__READ_WRITE,__TESTREG_bits);
__IO_REG32_BIT(PERIODREG1, 0x00213014,__READ_WRITE,__PERIODREG_bits);
__IO_REG32_BIT(DMAREG1,    0x00213018,__READ_WRITE,__DMAREG_bits);
__IO_REG32_BIT(RESETREG1,  0x0021301C,__READ_WRITE,__RESETREG_bits);


/***************************************************************************
 **
 **  SPI2
 **
 ***************************************************************************/
__IO_REG32_BIT(RXDATAREG2, 0x00219000,__READ_WRITE,__RXTXDATAREG_bits);
__IO_REG32_BIT(TXDATAREG2, 0x00219004,__READ_WRITE,__RXTXDATAREG_bits);
__IO_REG32_BIT(CONTROLREG2,0x00219008,__READ_WRITE,__CONTROLREG_bits);
__IO_REG32_BIT(INTREG2,    0x0021900C,__READ_WRITE,__INTREG_bits);
__IO_REG32_BIT(TESTREG2,   0x00219010,__READ_WRITE,__TESTREG_bits);
__IO_REG32_BIT(PERIODREG2, 0x00219014,__READ_WRITE,__PERIODREG_bits);
__IO_REG32_BIT(DMAREG2,    0x00219018,__READ_WRITE,__DMAREG_bits);
__IO_REG32_BIT(RESETREG2,  0x0021901C,__READ_WRITE,__RESETREG_bits);


/***************************************************************************
 **
 **  MMC/SDHC
 **
 ***************************************************************************/
__IO_REG32_BIT(STR_STP_CLK,   0x00214000,__READ_WRITE,__STR_STP_CLK_bits);
__IO_REG32_BIT(STATUS,        0x00214004,__READ_WRITE,__STATUS_bits);
__IO_REG32_BIT(CLK_RATE,      0x00214008,__READ_WRITE,__CLK_RATE_bits);
__IO_REG32_BIT(CMD_DAT_CONT,  0x0021400C,__READ_WRITE,__CMD_DAT_CONT_bits);
__IO_REG32_BIT(RES_TO,        0x00214010,__READ_WRITE,__RES_TO_bits);
__IO_REG32_BIT(READ_TO,       0x00214014,__READ_WRITE,__READ_TO_bits);
__IO_REG32_BIT(BLK_LEN,       0x00214018,__READ_WRITE,__BLK_LEN_bits);
__IO_REG32_BIT(NOB,           0x0021401C,__READ_WRITE,__NOB_bits);
__IO_REG32_BIT(REV_NO,        0x00214020,__READ_WRITE,__REV_NO_bits);
__IO_REG32_BIT(MMCSD_INT_MASK,0x00214024,__READ_WRITE,__MMCSD_INT_MASK_bits);
__IO_REG32_BIT(CMD,           0x00214028,__READ_WRITE,__CMD_bits);
__IO_REG32_BIT(ARGH,          0x0021402C,__READ_WRITE,__ARGH_bits);
__IO_REG32_BIT(ARGL,          0x00214030,__READ_WRITE,__ARGL_bits);
__IO_REG32_BIT(RES_FIFO,      0x00214034,__READ_WRITE,__RES_FIFO_bits);
__IO_REG32_BIT(BUFFER_ACCESS, 0x00214038,__READ_WRITE,__BUFFER_ACCESS_bits);


/***************************************************************************
 **
 **  ASP
 **
 ***************************************************************************/
__IO_REG32_BIT(ASP_PADFIFO, 0x00215000,__READ_WRITE,__ASP_PADFIFO_bits);
__IO_REG32(ASP_VADFIFO, 0x00215004,__READ_WRITE);
__IO_REG32(ASP_VDAFIFO, 0x00215008,__READ_WRITE);
__IO_REG32(ASP_VADCOEF, 0x0021500C,__READ_WRITE);
__IO_REG32_BIT(ASP_ACNTLCR, 0x00215010,__READ_WRITE,__ASP_ACNTLCR_bits);
__IO_REG32_BIT(ASP_PSMPLRG, 0x00215014,__READ_WRITE,__ASP_PSMPLRG_bits);
__IO_REG32_BIT(ASP_ICNTLR,  0x00215018,__READ_WRITE,__ASP_ICNTLR_bits);
__IO_REG32_BIT(ASP_ISTATR,  0x0021501C,__READ_WRITE,__ASP_ISTATR_bits);
__IO_REG32(ASP_VADGAIN, 0x00215020,__READ_WRITE);
__IO_REG32(ASP_VDAGAIN, 0x00215024,__READ_WRITE);
__IO_REG32(ASP_VDACOEF, 0x00215028,__READ_WRITE);
__IO_REG32_BIT(ASP_CLKDIV,  0x0021502C,__READ_WRITE,__ASP_CLKDIV_bits);
__IO_REG32_BIT(ASP_CMPCNTL, 0x00215030,__READ_WRITE,__ASP_CMPCNTL_bits);
__IO_REG32_BIT(ASP_FIFO_PTR,0x00215034,__READ_WRITE,__ASP_FIFO_PTR_bits);


/***************************************************************************
 **
 **  BTA
 **
 ***************************************************************************/
__IO_REG32_BIT(COMMANDSTATUS,         0x00216000,__READ_WRITE,__COMMANDSTATUS_bits);
//Not possible to use the names COMMAND and STATUS, since these are used as
//bitnames in other regs. Redefining them will cause problems.
#define BTA_COMMAND_bit COMMANDSTATUS_bit
#define BTA_COMMAND     COMMANDSTATUS
#define BTA_STATUS_bit  COMMANDSTATUS_bit
#define BTA_STATUS      COMMANDSTATUS

__IO_REG32_BIT(PACKET_HEADER,         0x00216004,__READ_WRITE,__PACKET_HEADER_bits);
__IO_REG32_BIT(PAYLOAD_HEADER,        0x00216008,__READ_WRITE,__PAYLOAD_HEADER_bits);
__IO_REG32_BIT(NATIVE_COUNT,          0x0021600C,__READ_WRITE,__NATIVE_COUNT_bits);
__IO_REG32_BIT(ESTIMATED_COUNT,       0x00216010,__READ_WRITE,__ESTIMATED_COUNT_bits);
__IO_REG32_BIT(OFFSET_COUNT,          0x00216014,__READ_WRITE,__OFFSET_COUNT_bits);
__IO_REG32_BIT(NATIVECLK_LOW,         0x00216018,__READ_WRITE,__NATIVECLK_LOW_bits);
__IO_REG32_BIT(NATIVECLK_HIGH,        0x0021601C,__READ_WRITE,__NATIVECLK_HIGH_bits);
__IO_REG32_BIT(ESTIMATED_CLK_LOW,     0x00216020,__READ_WRITE,__ESTIMATED_CLK_LOW_bits);
__IO_REG32_BIT(ESTIMATED_CLK_HIGH,    0x00216024,__READ_WRITE,__ESTIMATED_CLK_HIGH_bits);
__IO_REG32_BIT(OFFSET_CLK_LOW,        0x00216028,__READ_WRITE,__OFFSET_CLK_LOW_bits);
__IO_REG32_BIT(OFFSET_CLK_HIGH,       0x0021602C,__READ_WRITE,__OFFSET_CLK_HIGH_bits);
__IO_REG32_BIT(HECCRC_CONTROL,        0x00216030,__READ_WRITE,__HECCRC_CONTROL_bits);
__IO_REG32_BIT(WHITE_CONTROL,         0x00216034,__READ_WRITE,__WHITE_CONTROL_bits);
__IO_REG32_BIT(ENCRYPTION_CONTROL_X13,0x00216038,__READ_WRITE,__ENCRYPTION_CONTROL_X13_bits);
__IO_REG32_BIT(CORRELATION_TIME_STAMPSETUP,0x00216040,__READ_WRITE,__CORRELATION_TIME_STAMPSETUP_bits);
#define CORRELATION_TIME_SETUP_bit  CORRELATION_TIME_STAMPSETUP_bit
#define CORRELATION_TIME_SETUP      CORRELATION_TIME_STAMPSETUP
#define CORRELATION_TIME_STAMP_bit  CORRELATION_TIME_STAMPSETUP_bit
#define CORRELATION_TIME_STAMP      CORRELATION_TIME_STAMPSETUP

__IO_REG32_BIT(RF_GPO,                0x00216048,__READ_WRITE,__RF_GPO_bits);
__IO_REG32_BIT(PWM_RSSI,              0x0021604C,__READ_WRITE,__PWM_RSSI_bits);
__IO_REG32_BIT(TIME_A_B,              0x00216050,__READ_WRITE,__TIME_A_B_bits);
__IO_REG32_BIT(TIME_C_D,              0x00216054,__READ_WRITE,__TIME_C_D_bits);
__IO_REG32_BIT(PWM_TX,                0x00216058,__READ_WRITE,__PWM_TX_bits);
__IO_REG32_BIT(RF_CONTROLSTATUS,      0x0021605C,__READ_WRITE,__RF_CONTROLSTATUS_bits);
__IO_REG32_BIT(RX_TIME,               0x00216060,__READ_WRITE,__RX_TIME_bits);
__IO_REG32_BIT(TX_TIME,               0x00216064,__READ_WRITE,__TX_TIME_bits);
__IO_REG32_BIT(BAT,                   0x00216068,__READ_WRITE,__BAT_bits);
__IO_REG32_BIT(THRESHOLD,             0x0021606C,__READ_WRITE,__THRESHOLD_bits);
#define CORRELATION_MAX_bit THRESHOLD_bit
#define CORRELATION_MAX     THRESHOLD

__IO_REG32_BIT(SYNCH_WORD_0,          0x00216070,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(SYNCH_WORD_1,          0x00216074,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(SYNCH_WORD_2,          0x00216078,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(SYNCH_WORD_3,          0x0021607C,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_0,            0x00216080,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_1,            0x00216084,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_2,            0x00216088,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_3,            0x0021608C,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_4,            0x00216090,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_5,            0x00216094,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_6,            0x00216098,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_7,            0x0021609C,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_8,            0x002160A0,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_9,            0x002160A4,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_10,           0x002160A8,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_11,           0x002160AC,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_12,           0x002160B0,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_13,           0x002160B4,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_14,           0x002160B8,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_15,           0x002160BC,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_16,           0x002160C0,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_17,           0x002160C4,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_18,           0x002160C8,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_19,           0x002160CC,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_20,           0x002160D0,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_21,           0x002160D4,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_22,           0x002160D8,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_23,           0x002160DC,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_24,           0x002160E0,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_25,           0x002160E4,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_26,           0x002160E8,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_27,           0x002160EC,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_28,           0x002160F0,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_29,           0x002160F4,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_30,           0x002160F8,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(BUF_WORD_31,           0x002160FC,__READ_WRITE,__16BIT_WORD_bits);
__IO_REG32_BIT(WAKEUP_1,              0x00216100,__READ_WRITE,__WAKEUP_1_bits);
__IO_REG32_BIT(WAKEUP_2,              0x00216104,__READ_WRITE,__WAKEUP_2_bits);
__IO_REG32_BIT(WAKEUP_4DELTA4,        0x0021610C,__READ_WRITE,__WAKEUP_4DELTA4_bits);
#define WAKEUP_4_bit      WAKEUP_4DELTA4_bit
#define WAKEUP_4          WAKEUP_4DELTA4

__IO_REG32_BIT(WU_CONTROLSTATUS,      0x00216110,__READ_WRITE,__WU_CONTROLSTATUS_bits);
#define WU_CONTROL_bit WU_CONTROLSTATUS_bit
#define WU_CONTROL     WU_CONTROLSTATUS
#define WU_STATUS_bit  WU_CONTROLSTATUS_bit
#define WU_STATUS      WU_CONTROLSTATUS

__IO_REG32_BIT(WU_COUNT,              0x00216114,__READ_WRITE,__WU_COUNT_bits);
__IO_REG32_BIT(CLK_CONTROL,           0x00216118,__READ_WRITE,__CLK_CONTROL_bits);
__IO_REG32_BIT(SPI_WORD0,             0x00216120,__READ_WRITE,__SPI_WORD0_bits);
__IO_REG32_BIT(SPI_WORD1,             0x00216124,__READ_WRITE,__SPI_WORD1_bits);
__IO_REG32_BIT(SPI_WORD2,             0x00216128,__READ_WRITE,__SPI_WORD2_bits);
__IO_REG32_BIT(SPI_WORD3,             0x0021612C,__READ_WRITE,__SPI_WORD3_bits);
__IO_REG32_BIT(SPI_WRITE_ADDR,        0x00216130,__READ_WRITE,__SPI_READWRITE_ADDR_bits);
__IO_REG32_BIT(SPI_READ_ADDR,         0x00216134,__READ_WRITE,__SPI_READWRITE_ADDR_bits);
__IO_REG32_BIT(SPI_CONTROLSTATUS,     0x00216138,__READ_WRITE,__SPI_CONTROLSTATUS_bits);
#define SPI_CONTROL_bit SPI_CONTROLSTATUS_bit
#define SPI_CONTROL     SPI_CONTROLSTATUS
#define SPI_STATUS_bit  SPI_CONTROLSTATUS_bit
#define SPI_STATUS      SPI_CONTROLSTATUS

__IO_REG32_BIT(HOP0,                  0x00216140,__READ_WRITE,__HOP0_bits);
#define HOP_FREQ_OUT_bit HOP0_bit
#define HOP_FREQ_OUT     HOP0

__IO_REG32_BIT(HOP1,                  0x00216144,__READ_WRITE,__HOP1_bits);
__IO_REG32_BIT(HOP2,                  0x00216148,__READ_WRITE,__HOP2_bits);
__IO_REG32_BIT(HOP3,                  0x0021614C,__READ_WRITE,__HOP3_bits);
__IO_REG32_BIT(HOP4,                  0x00216150,__READ_WRITE,__HOP4_bits);
__IO_REG32_BIT(INTERRUPT_VECTOR,      0x00216160,__READ_WRITE,__INTERRUPT_VECTOR_bits);
__IO_REG32_BIT(SYNC_METRIC,           0x00216170,__READ_WRITE,__SYNC_METRIC_bits);
__IO_REG32_BIT(SYNC_FC,               0x00216174,__READ_WRITE,__SYNC_FC_bits);
__IO_REG32_BIT(WORD_REVERSE,          0x00216178,__READ_WRITE,__WORD_REVERSE_bits);
__IO_REG32_BIT(BYTE_REVERSE,          0x0021617C,__READ_WRITE,__BYTE_REVERSE_bits);


/***************************************************************************
 **
 **  I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(IADR,0x00217000,__READ_WRITE,__IADR_bits);
__IO_REG32_BIT(IFDR,0x00217004,__READ_WRITE,__IFDR_bits);
__IO_REG32_BIT(I2CR,0x00217008,__READ_WRITE,__I2CR_bits);
__IO_REG32_BIT(I2SR,0x0021700C,__READ_WRITE,__I2SR_bits);
__IO_REG32_BIT(I2DR,0x00217010,__READ_WRITE,__I2DR_bits);


/***************************************************************************
 **
 **  SSI
 **
 ***************************************************************************/
__IO_REG32_BIT(STX,    0x00218000,__READ_WRITE,__STX_bits);
__IO_REG32_BIT(SRX,    0x00218004,__READ_WRITE,__SRX_bits);
__IO_REG32_BIT(SCSR,   0x00218008,__READ_WRITE,__SCSR_bits);
__IO_REG32_BIT(STCR,   0x0021800C,__READ_WRITE,__STCR_bits);
__IO_REG32_BIT(SRCR,   0x00218010,__READ_WRITE,__SRCR_bits);
__IO_REG32_BIT(STCCR,  0x00218014,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(SRCCR,  0x00218018,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(STSR,   0x0021801C,__READ_WRITE,__STSR_bits);
__IO_REG32_BIT(SFCSR,  0x00218020,__READ_WRITE,__SFCSR_bits);
__IO_REG32_BIT(SOR,    0x00218028,__READ_WRITE,__SOR_bits);

__IO_REG32_BIT(STX_2,  0x0021D000,__READ_WRITE,__STX_bits);
__IO_REG32_BIT(SRX_2,  0x0021D004,__READ_WRITE,__SRX_bits);
__IO_REG32_BIT(SCSR_2, 0x0021D008,__READ_WRITE,__SCSR_bits);
__IO_REG32_BIT(STCR_2, 0x0021D00C,__READ_WRITE,__STCR_bits);
__IO_REG32_BIT(SRCR_2, 0x0021D010,__READ_WRITE,__SRCR_bits);
__IO_REG32_BIT(STCCR_2,0x0021D014,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(SRCCR_2,0x0021D018,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(STSR_2, 0x0021D01C,__READ_WRITE,__STSR_bits);
__IO_REG32_BIT(SFCSR_2,0x0021D020,__READ_WRITE,__SFCSR_bits);
__IO_REG32_BIT(SOR_2,  0x0021D028,__READ_WRITE,__SOR_bits);


/***************************************************************************
 **
 **  MSHC
 **
 ***************************************************************************/
__IO_REG16_BIT(MSCMD,  0x0021A000,__READ_WRITE,__MSCMD_bits);
__IO_REG16_BIT(MSCS,   0x0021A002,__READ_WRITE,__MSCS_bits);
__IO_REG16(MSTMSRDATA,0x0021A004,__READ_WRITE);
__IO_REG16_BIT(MSICS,  0x0021A006,__READ_WRITE,__MSICS_bits);
__IO_REG16_BIT(MSPPCD, 0x0021A008,__READ_WRITE,__MSPPCD_bits);
__IO_REG16_BIT(MSC2,   0x0021A00A,__READ_WRITE,__MSC2_bits);
__IO_REG16_BIT(MSACD,  0x0021A00C,__READ_WRITE,__MSACD_bits);
__IO_REG16_BIT(MSFAECS,0x0021A00E,__READ_WRITE,__MSFAECS_bits);
__IO_REG16_BIT(MSCLKD, 0x0021A010,__READ_WRITE,__MSCLKD_bits);
__IO_REG16_BIT(MSDRQC, 0x0021A012,__READ_WRITE,__MSDRQC_bits);


/***************************************************************************
 **
 **  PLL
 **
 ***************************************************************************/
__IO_REG32_BIT(CSCR,  0x0021B000,__READ_WRITE,__CSCR_bits);
__IO_REG32_BIT(MPCTL0,0x0021B004,__READ_WRITE,__MPCTL0_bits);
__IO_REG32_BIT(MPCTL1,0x0021B008,__READ_WRITE,__MPCTL1_bits);
__IO_REG32_BIT(SPCTL0,0x0021B00C,__READ_WRITE,__SPCTL0_bits);
__IO_REG32_BIT(SPCTL1,0x0021B010,__READ_WRITE,__SPCTL1_bits);
__IO_REG32_BIT(PCDR,  0x0021B020,__READ_WRITE,__PCDR_bits);


/***************************************************************************
 **
 **  SYS CTRL
 **
 ***************************************************************************/
__IO_REG32_BIT(RSR, 0x0021B800,__READ_WRITE,__RSR_bits);
__IO_REG32(SIDR,0x0021B804,__READ_WRITE);
__IO_REG32_BIT(FMCR,0x0021B808,__READ_WRITE,__FMCR_bits);
__IO_REG32_BIT(GPCR,0x0021B80C,__READ_WRITE,__GPCR_bits);
__IO_REG32_BIT(GCCR,0x0021B810,__READ_WRITE,__GCCR_bits);


/***************************************************************************
 **
 **  GPIO PORTA
 **
 ***************************************************************************/
__IO_REG32_BIT(DDIR_A,   0x0021C000,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(OCR1_A,   0x0021C004,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(OCR2_A,   0x0021C008,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFA1_A,0x0021C00c,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFA2_A,0x0021C010,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFB1_A,0x0021C014,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFB2_A,0x0021C018,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(DR_A,     0x0021C01c,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GIUS_A,   0x0021C020,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SSR_A,    0x0021C024,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ICR1_A,   0x0021C028,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICR2_A,   0x0021C02c,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(IMR_A,    0x0021C030,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ISR_A,    0x0021C034,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GPR_A,    0x0021C038,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SWR_A,    0x0021C03c,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PUEN_A,   0x0021C040,__READ_WRITE,__PORT_REG_31_0_bits);

/***************************************************************************
 **
 **  GPIO PORTB
 **
 ***************************************************************************/
__IO_REG32_BIT(DDIR_B,   0x0021C100,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(OCR1_B,   0x0021C104,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(OCR2_B,   0x0021C108,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFA1_B,0x0021C10c,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFA2_B,0x0021C110,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFB1_B,0x0021C114,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFB2_B,0x0021C118,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(DR_B,     0x0021C11c,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GIUS_B,   0x0021C120,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SSR_B,    0x0021C124,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ICR1_B,   0x0021C128,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICR2_B,   0x0021C12c,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(IMR_B,    0x0021C130,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ISR_B,    0x0021C134,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GPR_B,    0x0021C138,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SWR_B,    0x0021C13c,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PUEN_B,   0x0021C140,__READ_WRITE,__PORT_REG_31_0_bits);


/***************************************************************************
 **
 **  GPIO PORTC
 **
 ***************************************************************************/
__IO_REG32_BIT(DDIR_C,   0x0021C200,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(OCR1_C,   0x0021C204,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(OCR2_C,   0x0021C208,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFA1_C,0x0021C20c,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFA2_C,0x0021C210,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFB1_C,0x0021C214,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFB2_C,0x0021C218,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(DR_C,     0x0021C21c,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GIUS_C,   0x0021C220,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SSR_C,    0x0021C224,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ICR1_C,   0x0021C228,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICR2_C,   0x0021C22c,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(IMR_C,    0x0021C230,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ISR_C,    0x0021C234,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GPR_C,    0x0021C238,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SWR_C,    0x0021C23c,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PUEN_C,   0x0021C240,__READ_WRITE,__PORT_REG_31_0_bits);


/***************************************************************************
 **
 **  GPIO PORTD
 **
 ***************************************************************************/
__IO_REG32_BIT(DDIR_D,   0x0021C300,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(OCR1_D,   0x0021C304,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(OCR2_D,   0x0021C308,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFA1_D,0x0021C30c,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFA2_D,0x0021C310,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(ICONFB1_D,0x0021C314,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICONFB2_D,0x0021C318,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(DR_D,     0x0021C31c,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GIUS_D,   0x0021C320,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SSR_D,    0x0021C324,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ICR1_D,   0x0021C328,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(ICR2_D,   0x0021C32c,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(IMR_D,    0x0021C330,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(ISR_D,    0x0021C334,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(GPR_D,    0x0021C338,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(SWR_D,    0x0021C33c,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PUEN_D,   0x0021C340,__READ_WRITE,__PORT_REG_31_0_bits);


/***************************************************************************
 **
 **  EIM
 **
 ***************************************************************************/
__IO_REG32_BIT(CS0U,0x00220000,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS0L,0x00220004,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS1U,0x00220008,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS1L,0x0022000C,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS2U,0x00220010,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS2L,0x00220014,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS3U,0x00220018,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS3L,0x0022001C,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS4U,0x00220020,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS4L,0x00220024,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS5U,0x00220028,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS5L,0x0022002C,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(EIM, 0x00220030,__READ_WRITE,__EIM_bits);


/***************************************************************************
 **
 **  SDRAMC
 **
 ***************************************************************************/
__IO_REG32_BIT(SDCTL0,       0x00221000,__READ_WRITE,__SDCTL_bits);
__IO_REG32_BIT(SDCTL1,       0x00221004,__READ_WRITE,__SDCTL_bits);
__IO_REG32_BIT(MISCELLANEOUS,0x00221014,__READ_WRITE,__MISC_bits);
__IO_REG32_BIT(SDRST,        0x00221018,__READ_WRITE,__SDRST_bits);


/***************************************************************************
 **
 **  MMA
 **
 ***************************************************************************/
__IO_REG32_BIT(MMA_MAC_MOD,      0x00222000,__READ_WRITE,__MMA_MAC_MOD_bits);
__IO_REG32_BIT(MMA_MAC_CTRL,     0x00222004,__READ_WRITE,__MMA_MAC_CTRL_bits);
__IO_REG32_BIT(MMA_MAC_MULT,     0x00222008,__READ_WRITE,__MMA_MAC_MULT_bits);
__IO_REG32_BIT(MMA_MAC_ACCU,     0x0022200C,__READ_WRITE,__MMA_MAC_ACCU_bits);
__IO_REG32_BIT(MMA_MAC_INTR,     0x00222010,__READ_WRITE,__MMA_MAC_INTR_bits);
__IO_REG32_BIT(MMA_MAC_INTR_MASK,0x00222014,__READ_WRITE,__MMA_MAC_INTR_bits);
__IO_REG32(MMA_MAC_FIFO,     0x00222018,__READ_WRITE);
__IO_REG32_BIT(MMA_MAC_FIFO_STAT,0x0022201C,__READ_WRITE,__MMA_MAC_FIFO_STAT_bits);
__IO_REG32_BIT(MMA_MAC_BURST,    0x00222020,__READ_WRITE,__MMA_MAC_BURST_bits);
__IO_REG32_BIT(MMA_MAC_BITSEL,   0x00222024,__READ_WRITE,__MMA_MAC_BITSEL_bits);
__IO_REG32(MMA_MAC_XYACCU,   0x00222040,__READ_WRITE);
__IO_REG32(MMA_MAC_XBASE,    0x00222200,__READ_WRITE);
__IO_REG32_BIT(MMA_MAC_XINDEX,   0x00222204,__READ_WRITE,__MMA_MAC_XINDEX_bits);
__IO_REG32_BIT(MMA_MAC_XLENGTH,  0x00222208,__READ_WRITE,__MMA_MAC_XLENGTH_bits);
__IO_REG32_BIT(MMA_MAC_XMODIFY,  0x0022220C,__READ_WRITE,__MMA_MAC_XMODIFY_bits);
__IO_REG32_BIT(MMA_MAC_XINCR,    0x00222210,__READ_WRITE,__MMA_MAC_XINCR_bits);
__IO_REG32_BIT(MMA_MAC_XCOUNT,   0x00222214,__READ_WRITE,__MMA_MAC_XCOUNT_bits);
__IO_REG32(MMA_MAC_YBASE,    0x00222300,__READ_WRITE);
__IO_REG32_BIT(MMA_MAC_YINDEX,   0x00222304,__READ_WRITE,__MMA_MAC_YINDEX_bits);
__IO_REG32_BIT(MMA_MAC_YLENGTH,  0x00222308,__READ_WRITE,__MMA_MAC_YLENGTH_bits);
__IO_REG32_BIT(MMA_MAC_YMODIFY,  0x0022230C,__READ_WRITE,__MMA_MAC_YMODIFY_bits);
__IO_REG32_BIT(MMA_MAC_YINCR,    0x00222310,__READ_WRITE,__MMA_MAC_YINCR_bits);
__IO_REG32_BIT(MMA_MAC_YCOUNT,   0x00222314,__READ_WRITE,__MMA_MAC_YCOUNT_bits);
__IO_REG32_BIT(MMA_DCTCTRL,      0x00222400,__READ_WRITE,__MMA_DCTCTRL_bits);
__IO_REG32(MMA_DCTVERSION,   0x00222404,__READ_WRITE);
__IO_REG32_BIT(MMA_DCTIRQENA,    0x00222408,__READ_WRITE,__MMA_DCTIRQENA_bits);
__IO_REG32_BIT(MMA_DCTIRQSTAT,   0x0022240C,__READ_WRITE,__MMA_DCTIRQSTAT_bits);
__IO_REG32(DSA_DCTSRCDATA,   0x00222410,__READ_WRITE);
__IO_REG32(MMA_DCTDESDATA,   0x00222414,__READ_WRITE);
__IO_REG32_BIT(MMA_DCTXOFF,      0x00222418,__READ_WRITE,__MMA_DCTXOFF_bits);
__IO_REG32_BIT(MMA_DCTYOFF,      0x0022241C,__READ_WRITE,__MMA_DCTYOFF_bits);
__IO_REG32_BIT(MMA_DCTXYCNT,     0x00222420,__READ_WRITE,__MMA_DCTXYCNT_bits);
__IO_REG32_BIT(MMA_DCTSKIP,      0x00222424,__READ_WRITE,__MMA_DCTSKIP_bits);
__IO_REG32(MMA_DCTFIFO,      0x00222500,__READ_WRITE);


/***************************************************************************
 **
 **  Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(INTCNTL,0x00223000,__READ_WRITE,__INTCNTL_bits);
__IO_REG32_BIT(NIMASK,0x00223004,__READ_WRITE,__NIMASK_bits);
__IO_REG32_BIT(INTENNUM,0x00223008,__READ_WRITE,__INTENNUM_bits);
__IO_REG32_BIT(INTDISNUM,0x0022300C,__READ_WRITE,__INTDISNUM_bits);
__IO_REG32_BIT(INTENABLEH,0x00223010,__READ_WRITE,__INTENABLEH_bits);
__IO_REG32_BIT(INTENABLEL,0x00223014,__READ_WRITE,__INTENABLEL_bits);
__IO_REG32_BIT(INTTYPEH,0x00223018,__READ_WRITE,__INTTYPEH_bits);
__IO_REG32_BIT(INTTYPEL,0x0022301C,__READ_WRITE,__INTTYPEL_bits);
__IO_REG32_BIT(NIPRIORITY7,0x00223020,__READ_WRITE,__NIPRIORITY7_bits);
__IO_REG32_BIT(NIPRIORITY6,0x00223024,__READ_WRITE,__NIPRIORITY6_bits);
__IO_REG32_BIT(NIPRIORITY5,0x00223028,__READ_WRITE,__NIPRIORITY5_bits);
__IO_REG32_BIT(NIPRIORITY4,0x0022302C,__READ_WRITE,__NIPRIORITY4_bits);
__IO_REG32_BIT(NIPRIORITY3,0x00223030,__READ_WRITE,__NIPRIORITY3_bits);
__IO_REG32_BIT(NIPRIORITY2,0x00223034,__READ_WRITE,__NIPRIORITY2_bits);
__IO_REG32_BIT(NIPRIORITY1,0x00223038,__READ_WRITE,__NIPRIORITY1_bits);
__IO_REG32_BIT(NIPRIORITY0,0x0022303C,__READ_WRITE,__NIPRIORITY0_bits);
__IO_REG32_BIT(NIVECSR,0x00223040,__READ_WRITE,__NIVECSR_bits);
__IO_REG32_BIT(FIVECSR,0x00223044,__READ_WRITE,__FIVECSR_bits);
__IO_REG32_BIT(INTSRCH,0x00223048,__READ_WRITE,__INTSRCH_bits);
__IO_REG32_BIT(INTSRCL,0x0022304C,__READ_WRITE,__INTSRCL_bits);
__IO_REG32_BIT(INTFRCH,0x00223050,__READ_WRITE,__INTFRCH_bits);
__IO_REG32_BIT(INTFRCL,0x00223054,__READ_WRITE,__INTFRCL_bits);
__IO_REG32_BIT(NIPNDH,0x00223058,__READ_WRITE,__NIPNDH_bits);
__IO_REG32_BIT(NIPNDL,0x0022305C,__READ_WRITE,__NIPNDL_bits);
__IO_REG32_BIT(FIPNDH,0x00223060,__READ_WRITE,__FIPNDH_bits);
__IO_REG32_BIT(FIPNDL,0x00223064,__READ_WRITE,__FIPNDL_bits);


/***************************************************************************
 **
 **  CSI
 **
 ***************************************************************************/
__IO_REG32_BIT(CSICR1,  0x00224000,__READ_WRITE,__CSICR1_bits);
__IO_REG32_BIT(CSICR2,  0x00224004,__READ_WRITE,__CSICR2_bits);
__IO_REG32_BIT(CSISR,   0x00224008,__READ_WRITE,__CSISR_bits);
__IO_REG32(CSISTATR,0x0022400C,__READ_WRITE);
__IO_REG32(CSIRXR,  0x00224010,__READ_WRITE);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **   MC9328MX1 interrupt sources
 **
 ***************************************************************************/

#define UART3_MINT_PFERR       0
#define UART3_MINT_RTS         1
#define UART3_MINT_DTR         2
#define UART3_MINT_UARTC       3
#define UART3_MINT_TX          4
#define PEN_UP_INT             5
#define CSI_INT                6
#define MMA_MAC_INT            7
#define MMA_INT                8
#define COMP_INT               9
#define MSIRQ                  10
#define GPIO_INT_PORTA         11
#define GPIO_INT_PORTB         12
#define GPIO_INT_PORTC         13
#define LCDC_INT               14
#define SIM_IRQ                15
#define SIM_DATA               16
#define RTC_INT                17
#define RTC_SAM_INT            18
#define UART2_MINT_PFERR       19
#define UART2_MINT_RTS         20
#define UART2_MINT_DTR         21
#define UART2_MINT_UARTC       22
#define UART2_MINT_TX          23
#define UART2_MINT_RX          24
#define UART1_MINT_PFERR       25
#define UART1_MINT_RTS         26
#define UART1_MINT_DTR         27
#define UART1_MINT_UARTC       28
#define UART1_MINT_TX          29
#define UART1_MINT_RX          30
//#define Unused               31
//#define Unused               32
#define PEN_DATA_INT           33
#define PWM_INT                34
#define MMC_IRQ                35
#define SSI2_TX_INT            36
#define SSI2_RX_INT            37
#define SSI2_RX_TX_ERR_INT     38
#define I2C_INT                39
#define SPI2_INT               40
#define SPI1_INT               41
#define SSI_TX_INT             42
#define SSI_TX_ERR_INT         43
#define SSI_RX_INT             44
#define SSI_RX_ERR_INT         45
#define TOUCH_INT              46
#define USBD_INT0              47
#define USBD_INT1              48
#define USBD_INT2              49
#define USBD_INT3              50
#define USBD_INT4              51
#define USBD_INT5              52
#define USBD_INT6              53
#define UART3_MINT_RX          54
#define BTSYS                  55
#define BTTIM                  56
#define BTWU                   57
#define TIMER2_INT             58
#define TIMER1_INT             59
#define DMA_ERR                60
#define DMA_INT                61
#define GPIO_INT_PORTD         62
#define WDT_INT                63

#endif    /* __MC9328MX1_H */
