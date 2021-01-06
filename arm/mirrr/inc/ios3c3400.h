/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C3400
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2000
 **
 **    $Revision: 1.4 $
 **
 ***************************************************************************/

#ifndef __S3C3400_H
#define __S3C3400_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    S3C3400 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* SM: system configuration register  */
typedef struct {
  __REG32 se   :1; /* stall enable            */
  __REG32 ce   :1; /* cache enable            */
  __REG32 we   :1; /* write buffer enable     */
  __REG32      :10;
  __REG32 cm   :2; /* cache mode              */
  __REG32 am   :1; /* address MUX enable bit  */
  __REG32      :16;
} __syscfg_bits;

/* SM: Memory control register  */
typedef struct {
  __REG32 ms   :1; /* memory selection        */
  __REG32 dw   :1; /* bus width               */
  __REG32 pmc  :2; /* page mode or col address*/
  __REG32 edx16:1; /* EDO DRAM or x16SRAM     */
  __REG32 ac   :2; /* access cycle, CAS time  */
  __REG32 tcp  :1; /* CAS pre-change          */
  __REG32 tacc :3; /* access cycles of bank   */
  __REG32 trc  :1; /* RAS to CAS delay        */
  __REG32 trp  :2; /* RAS pre-change time     */
  __REG32 ba   :9; /* base address            */
  __REG32 ea   :9; /* end address             */
} __memcon_bits;

/* SM: Extra device control register  */
typedef struct {
  __REG32 dw   :2;  /* bus width    */
  __REG32 tcos :3;  /* chip selection set-up on nRD ornWBE  */
  __REG32 tacs :3;  /* address set-up before nECS           */
  __REG32 tcoh :3;  /* chip selection hold on nRD or nWBE   */
  __REG32 tacc :3;  /* access cycles */
  __REG32      :18;
} __edvcon_bits;

/* SM: DRAM refresh control register  */
typedef struct {
  __REG32 vf   :1;
  __REG32 rc   :11;
  __REG32 ren  :1;
  __REG32 tcs  :3;
  __REG32 tcsr :1;
  __REG32      :15;
} __refcon_bits;

/* DMA: control register  */
typedef struct {
  __REG32 re     :1;
  __REG32 busy   :1;
  __REG32 mode   :2;
  __REG32 dstdir :1;
  __REG32 srcdir :1;
  __REG32 dstfix :1;
  __REG32 srcfix :1;
  __REG32 stopien:1;
  __REG32 burst4 :1;
  __REG32 tdir   :1;
  __REG32 nxdreqs:1;
  __REG32 width  :2;
  __REG32 cn     :1;
  __REG32 dm     :1;
  __REG32        :16;
} __dmacon_bits;

/* DMA: source/destination address register  */
typedef struct {
  __REG32 addr   :25;
  __REG32        :7;
} __dmasrcdst_bits;

/* DMA: transfer count register  */
typedef struct {
  __REG32 count  :24;
  __REG32        :8;
} __dmacnt_bits;

/* UART: line control register */
typedef struct {
  __REG8 wl    :2;
  __REG8 stb   :1;
  __REG8 pmd   :3;
  __REG8 brs   :1;
  __REG8       :1;
} __lcon_bits;

/* UART: control register */
typedef struct {
  __REG8 rxm   :2;
  __REG8 rxsi  :1;
  __REG8 txm   :2;
  __REG8 dsr   :1;
  __REG8 sbk   :1;
  __REG8 lpb   :1;
} __ucon_bits;

/* UART: status register */
typedef struct {
  __REG8 ov   :1;
  __REG8 pe   :1;
  __REG8 fe   :1;
  __REG8 brki :1;
  __REG8      :1;
  __REG8 rdr  :1;
  __REG8 the  :1;
  __REG8 te   :1;
} __ussr_bits;

/* UART: transmit buffer register */
typedef struct {
  __REG8 data :8;
} __tbr_bits;

/* UART: receive buffer register */
typedef struct {
  __REG8 data :8;
} __rbr_bits;

/* UART: baud rate divisor register */
typedef struct {
  __REG16 div  :16;
} __ubrdr_bits;

/* SIO: port control register */
typedef struct {
  __REG8 mode  :2;
  __REG8 he    :1;
  __REG8 start :1;
  __REG8 clkp  :1;
  __REG8 txe   :1;
  __REG8 msb   :1;
  __REG8 sclks :1;
} __siocon_bits;

/* SIO: port data register */
typedef struct {
  __REG8 data  :8;
} __siodata_bits;

/* SIO: byte interval time value register */
typedef struct {
  __REG8 data  :8;
} __sbidr_bits;

/* SIO: baud rate divisor register */
typedef struct {
  __REG8 data  :8;
} __sbrdr_bits;

/* BTWDT: basic timer control register */
typedef struct {
  __REG16 wdcclr :1;
  __REG16 btcclr :1;
  __REG16 clksrc :2;
  __REG16        :4;
  __REG16 wde    :8;
} __btcon_bits;

/* Timer16: control register */
typedef struct {
  __REG8        :2;
  __REG8 clksrc :1;
  __REG8 mode   :3;
  __REG8 cclr   :1;
  __REG8 ten    :1;
} __tcon16_bits;

/* Timer16: data register */
typedef struct {
  __REG16 data   :16;
} __tdata16_bits;

/* Timer16: count register */
typedef struct {
  __REG16 count  :16;
} __tcnt16_bits;

/* Timer16: prescaler register */
typedef struct {
  __REG8 data   :8;
} __tpre16_bits;

/* Timer8: control register */
typedef struct {
  __REG8 clksrc :3;
  __REG8 mode   :3;
  __REG8 cclr   :1;
  __REG8 ten    :1;
} __tcon8_bits;

/* Timer8: data register */
typedef struct {
  __REG8 data   :8;
} __tdata8_bits;

/* Timer8: prescaler register */
typedef struct {
  __REG8 data   :8;
} __tpre8_bits;

/* Timer8: count register */
typedef struct {
  __REG8 count  :8;
} __tcnt8_bits;

/* ADC: control register */
typedef struct {
  __REG8 adstr  :1;
  __REG8 speed  :2;
  __REG8 eoc    :1;
  __REG8 is     :3;
  __REG8        :1;
} __adcon_bits;

/* ADC: converter data register */
typedef struct {
  __REG8 data   :8;
} __addata_bits;

/* interrupt pending/mask/mode register */
typedef struct {
  __REG32 int_ext0     :1;
  __REG32 int_ext1     :1;
  __REG32 int_ur       :1;
  __REG32 int_ut       :1;
  __REG32 int_uerr     :1;
  __REG32 int_dma0     :1;
  __REG32 int_dma1     :1;
  __REG32 int_timer0o  :1;
  __REG32 int_timer0mc :1;
  __REG32 int_timer1o  :1;
  __REG32 int_timer1mc :1;
  __REG32 int_timer2o  :1;
  __REG32 int_timer2mc :1;
  __REG32 int_timer3o  :1;
  __REG32 int_timer3mc :1;
  __REG32 int_timer4o  :1;
  __REG32 int_timer4mc :1;
  __REG32 int_btimer   :1;
  __REG32 int_serio0   :1;
  __REG32 int_serio1   :1;
  __REG32 int_ext2     :1;
  __REG32 int_ext3     :1;
  __REG32 int_ext4     :1;
  __REG32 int_ext5     :1;
  __REG32 int_ext6     :1;
  __REG32 int_ext7     :1;
  __REG32 int_ext8     :1;
  __REG32 int_ext9     :1;
  __REG32 int_adc      :1;
  __REG32 int_ext10    :1;
  __REG32 int_ext11    :1;
  __REG32 int_ext12    :1;
} __int_bits;

/* System control register */
typedef struct {
  __REG8 stop   :1;
  __REG8 idle   :1;
  __REG8        :1;
  __REG8 cpuclk :3;
  __REG8 gie    :1;
  __REG8        :1;
} __syscon_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/


/***************************************************************************
 **
 **  System manager registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG, 0x01ff1000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__MEMCON0,0x01ff2000,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(__MEMCON1,0x01ff2004,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(__MEMCON2,0x01ff2008,__READ_WRITE,__memcon_bits);
__IO_REG32_BIT(__MEMCON3,0x01ff200c,__READ_WRITE,__memcon_bits);

__IO_REG32_BIT(__EDVCON,0x01ff2014,__READ_WRITE,__edvcon_bits);
__IO_REG16(__EXTPORT,0x01ff201a,__READ_WRITE);
__IO_REG16(__ECSDATA0,0x01ff201c,__READ_WRITE);
__IO_REG16(__ECSDATA1,0x01ff201e,__READ_WRITE);
__IO_REG32_BIT(__REFCON,0x01ff2010,__READ_WRITE, __refcon_bits);

/***************************************************************************
 **
 **  DMA controller registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__DMA0CON,0x01ff3000,__READ_WRITE,__dmacon_bits);
__IO_REG32_BIT(__DMA1CON,0x01ff4000,__READ_WRITE,__dmacon_bits);
__IO_REG32_BIT(__DMA0SRC,0x01ff3004,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMA0DST,0x01ff3008,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMA1SRC,0x01ff4004,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMA1DST,0x01ff4008,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMA0CNT,0x01ff300c,__READ_WRITE,__dmacnt_bits);
__IO_REG32_BIT(__DMA1CNT,0x01ff400c,__READ_WRITE,__dmacnt_bits);


/***************************************************************************
 **
 **  UART Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__LCON,0x01ff5003,__READ_WRITE,__lcon_bits);
__IO_REG8_BIT(__UCON,0x01ff5007,__READ_WRITE,__ucon_bits);
__IO_REG8_BIT(__USSR,0x01ff500b,__READ,__ussr_bits);
__IO_REG8_BIT(__TBR,0x01ff500f,__WRITE,__tbr_bits);
__IO_REG8_BIT(__RBR,0x01ff5013,__READ,__rbr_bits);
__IO_REG16_BIT(__UBRDR,0x01ff5016,__READ_WRITE,__ubrdr_bits);
__IO_REG16(__BRDCNT,0x01ff501a,__WRITE);
__IO_REG8(__BRCKCON,0x01ff501f,__WRITE);


/***************************************************************************
 **
 **  SIO Registers
 **
 ***************************************************************************/

__IO_REG8_BIT(__SIO0CON,0x01ff6003,__READ_WRITE,__siocon_bits);
__IO_REG8_BIT(__SIO1CON,0x01ff7003,__READ_WRITE,__siocon_bits);
__IO_REG8_BIT(__SIO0DATA,0x01ff6002,__READ_WRITE,__siodata_bits);
__IO_REG8_BIT(__SIO1DATA,0x01ff7002,__READ_WRITE,__siodata_bits);
__IO_REG8_BIT(__SBIDR0,0x01ff6000,__READ_WRITE,__sbidr_bits);
__IO_REG8_BIT(__SBRDR0,0x01ff6001,__READ_WRITE,__sbrdr_bits);
__IO_REG8_BIT(__SBIDR1,0x01ff7000,__READ_WRITE,__sbidr_bits);
__IO_REG8_BIT(__SBRDR1,0x01ff7001,__READ_WRITE,__sbrdr_bits);

/***************************************************************************
 **
 **  Basic Timer and Watch Dog Registers
 **
 ***************************************************************************/
__IO_REG16_BIT(__BTCON,0x01ffa002,__READ_WRITE,__btcon_bits);
__IO_REG8(__BTCNT,0x01ffa007,__READ);


/***************************************************************************
 **
 **  Timer 0 (16 bit timer) Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__T0CON,0x01ff9003,__READ_WRITE,__tcon16_bits);
__IO_REG16_BIT(__T0DATA,0x01ff9000,__READ_WRITE,__tdata16_bits);
__IO_REG16_BIT(__T0CNT,0x01ff9006,__READ,__tcnt16_bits);
__IO_REG8_BIT(__T0PRE,0x01ff9002,__READ_WRITE,__tpre16_bits);


/***************************************************************************
 **
 **  Timer 1 (16 bit timer) Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__T1CON,0x01ff9013,__READ_WRITE,__tcon16_bits);
__IO_REG16_BIT(__T1DATA,0x01ff9010,__READ_WRITE,__tdata16_bits);
__IO_REG16_BIT(__T1CNT,0x01ff9016,__READ,__tcnt16_bits);
__IO_REG8_BIT(__T1PRE,0x01ff9012,__READ_WRITE,__tpre16_bits);

/***************************************************************************
 **
 **  Timer 2 (16 bit timer) Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__T2CON,0x01ff9023,__READ_WRITE,__tcon16_bits);
__IO_REG16_BIT(__T2DATA,0x01ff9020,__READ_WRITE,__tdata16_bits);
__IO_REG16_BIT(__T2CNT,0x01ff9026,__READ,__tcnt16_bits);
__IO_REG8_BIT(__T2PRE,0x01ff9022,__READ_WRITE,__tpre16_bits);


/***************************************************************************
 **
 **  Timer 3 (8 bit timer) Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__T3CON,0x01ff9033,__READ_WRITE,__tcon8_bits);
__IO_REG8_BIT(__T3DATA,0x01ff9031,__READ_WRITE,__tdata8_bits);
__IO_REG8_BIT(__T3CNT,0x01ff9037,__READ,__tcnt8_bits);
__IO_REG8_BIT(__T3PRE,0x01ff9032,__READ_WRITE,__tpre8_bits);

/***************************************************************************
 **
 **  Timer 4 (8 bit timer) Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__T4CON,0x01ff9043,__READ_WRITE,__tcon8_bits);
__IO_REG8_BIT(__T4DATA,0x01ff9041,__READ_WRITE,__tdata8_bits);
__IO_REG8_BIT(__T4CNT,0x01ff9047,__READ,__tcnt8_bits);
__IO_REG8_BIT(__T4PRE,0x01ff9042,__READ_WRITE,__tpre8_bits);


/***************************************************************************
 **
 **  ADC Analog to Digital Converter Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__ADCON,0x01ff8003,__READ_WRITE,__adcon_bits);
__IO_REG8_BIT(__ADDATA,0x01ff8007,__READ,__addata_bits);


/***************************************************************************
 **
 **  IO port registers
 **
 ***************************************************************************/
__IO_REG8(__P0,0x01ffb000,__READ_WRITE);
__IO_REG8(__P1,0x01ffb001,__READ_WRITE);
__IO_REG8(__P2,0x01ffb002,__READ_WRITE);
__IO_REG8(__P3,0x01ffb003,__READ_WRITE);
__IO_REG8(__P4,0x01ffb004,__READ_WRITE);
__IO_REG8(__P5,0x01ffb005,__READ_WRITE);
__IO_REG8(__P6,0x01ffb006,__READ_WRITE);
__IO_REG8(__P7,0x01ffb007,__READ);
__IO_REG8(__P0BR,0x01ffb008,__READ_WRITE);
__IO_REG16(__EINTCON,0x01ffb00a,__READ_WRITE);
__IO_REG32(__EINTMOD,0x01ffb00c,__READ_WRITE);

/***************************************************************************
 **
 **  IO port control registers
 **
 ***************************************************************************/

__IO_REG16(__P0CON,0x01ffb010,__READ_WRITE);
__IO_REG16(__P1CON,0x01ffb012,__READ_WRITE);
__IO_REG16(__P2CON,0x01ffb014,__READ_WRITE);
__IO_REG16(__P3CON,0x01ffb018,__READ_WRITE);
__IO_REG16(__P4CON,0x01ffb01a,__READ_WRITE);
__IO_REG32(__P5CON,0x01ffb01c,__READ_WRITE);
__IO_REG16(__P6CON,0x01ffb020,__READ_WRITE);
__IO_REG8(__P7CON,0x01ffb022,__READ_WRITE);


/***************************************************************************
 **
 **  IO port resistor control registers
 **
 ***************************************************************************/

__IO_REG8(__P0PUR,0x01ffb028,__READ_WRITE);
__IO_REG8(__P1PDR,0x01ffb029,__READ_WRITE);
__IO_REG8(__P2PDR,0x01ffb02a,__READ_WRITE);
__IO_REG8(__P3PUR,0x01ffb02b,__READ_WRITE);
__IO_REG8(__P4PUR,0x01ffb02c,__READ_WRITE);
__IO_REG8(__P5PUR,0x01ffb02d,__READ_WRITE);
__IO_REG8(__P6PUR,0x01ffb02e,__READ_WRITE);
__IO_REG8(__P7PUR,0x01ffb02f,__READ_WRITE);

/***************************************************************************
 **
 **  Interrupt controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTMODE,0x01ffc000,__READ_WRITE,__int_bits);
__IO_REG32_BIT(__INTPEND,0x01ffc004,__READ_WRITE,__int_bits);
__IO_REG32_BIT(__INTMASK,0x01ffc008,__READ_WRITE,__int_bits);

/***************************************************************************
 **
 **  System control register
 **
 ***************************************************************************/
__IO_REG8_BIT(__SYSCON,0x01ffd003,__READ_WRITE,__syscon_bits);


/***************************************************************************
 **
 **  SRAM register
 **
 ***************************************************************************/
__IO_REG8(__SRAM,0x01ff0000,__READ_WRITE);



/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  ks32c4000a interrupt sources
 **
 ***************************************************************************/
#define INT_EXT0      0  /* external interrupt 0             */
#define INT_EXT1      1  /* external interrupt 1             */
#define INT_UR        2  /* uart receive                     */
#define INT_UT        3  /* uart transmit                    */
#define INT_UERR      4  /* uart error                       */
#define INT_DMA0      5  /* DMA  0 interrupt                 */
#define INT_DMA1      6  /* DMA  1 interrupt                 */
#define INT_TIMER0O   7  /* timer 0 overflow interrupt       */
#define INT_TIMER0MC  8  /* timer 0 match/capture interrupt  */
#define INT_TIMER1O   9  /* timer 1 overflow interrupt       */
#define INT_TIMER1MC 10  /* timer 1 match/capture interrupt  */
#define INT_TIMER2O  11  /* timer 2 overflow interrupt       */
#define INT_TIMER2MC 12  /* timer 2 match/capture interrupt  */
#define INT_TIMER3O  13  /* timer 3 overflow interrupt       */
#define INT_TIMER3MC 14  /* timer 3 match/capture interrupt  */
#define INT_TIMER4O  15  /* timer 4 overflow interrupt       */
#define INT_TIMER4MC 16  /* timer 4 match/capture interrupt  */
#define INT_BTIMER   17  /* basic timer interrupt             */
#define INT_SERIO0   18  /* serial I/O 0 interrupt           */
#define INT_SERIO1   19  /* serial I/O 1 interrupt           */
#define INT_EXT2     20  /* external interrupt 2             */
#define INT_EXT3     21  /* external interrupt 3             */
#define INT_EXT4     22  /* external interrupt 4             */
#define INT_EXT5     23  /* external interrupt 5             */
#define INT_EXT6     24  /* external interrupt 6             */
#define INT_EXT7     25  /* external interrupt 7             */
#define INT_EXT8     26  /* external interrupt 8             */
#define INT_EXT9     27  /* external interrupt 9             */
#define INT_ADC      28  /* A/D conversion interrupt         */
#define INT_EXT10    29  /* external interrupt 10            */
#define INT_EXT11    30  /* external interrupt 11            */
#define INT_EXT12    31  /* external interrupt 12            */

#endif    /* __S3C3400_H */
