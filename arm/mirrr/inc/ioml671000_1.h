/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Oki Semiconductors ML671000
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2000
 **
 **    $Revision: 1.10 $
 **
 ***************************************************************************/

#ifndef __ML671000_H
#define __ML671000_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    ML670100 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Standby Control Register */
typedef struct {
  __REG32 hlt    :1;
  __REG32 stp    :1;
  __REG32        :30;
} __sbycon_bits;


/* Clock Control Register */
typedef struct {
  __REG32 ckm    :2;
  __REG32        :30;
} __ckcon_bits;


/* Clock Supply Wait Control Register */
typedef struct {
  __REG32 ckwt   :2;
  __REG32        :30;
} __ckwtcon_bits;


/* Reset Status Register */
typedef struct {
  __REG32 wdtrst :1;
  __REG32        :31;
} __rstst_bits;


/* Interrupt Number Register */
typedef struct {
  __REG8 in      :5;
  __REG8         :3;
} __inr_bits;

/* Current Interrupt Level Register */
typedef struct {
  __REG8         :1;
  __REG8 cilr1   :1;
  __REG8 cilr2   :1;
  __REG8 cilr3   :1;
  __REG8 cilr4   :1;
  __REG8 cilr5   :1;
  __REG8 cilr6   :1;
  __REG8 cilr7   :1;
} __cilr_bits;

/* Interrupt Request Level Register */
typedef struct {
  __REG8 irl     :3;
  __REG8         :5;
} __irlr_bits;

/* External FIQ Control Register */
typedef struct {
  __REG8 efiqr   :1;
  __REG8 efiqs   :1;
  __REG8 efiqm   :1;
  __REG8         :5;
} __efiqcon_bits;

/* External IRQ Control Register */
typedef struct {
  __REG8 eir0    :1;
  __REG8 eir1    :1;
  __REG8 eir2    :1;
  __REG8 eir3    :1;
  __REG8 eir4    :1;
  __REG8 eir5    :1;
  __REG8 eir6    :1;
  __REG8 eir7    :1;
} __eircon_bits;

/* Interrupt Level Control Register 0*/
typedef struct {
  __REG16 ilr0   :3;
  __REG16        :1;
  __REG16 ilr1   :3;
  __REG16        :1;
  __REG16 ilr2   :3;
  __REG16        :1;
  __REG16 ilr3   :3;
  __REG16        :1;
} __ilcon0_bits;

/* Interrupt Level Control Register 1*/
typedef struct {
  __REG16 ilr4   :3;
  __REG16        :1;
  __REG16 ilr5   :3;
  __REG16        :1;
  __REG16 ilr6   :3;
  __REG16        :1;
  __REG16 ilr7   :3;
  __REG16        :1;
} __ilcon1_bits;

/* Interrupt Level Control Register 2*/
typedef struct {
  __REG16 ilr8   :3;
  __REG16        :1;
  __REG16 ilr9   :3;
  __REG16        :1;
  __REG16 ilr10  :3;
  __REG16        :1;
  __REG16 ilr11  :3;
  __REG16        :1;
} __ilcon2_bits;

/* Interrupt Level Control Register 3*/
typedef struct {
  __REG16 ilr12  :3;
  __REG16        :13;
} __ilcon3_bits;


/* Interrupt Level Control Register 4*/
typedef struct {
  __REG16 ilr16  :3;
  __REG16        :1;
  __REG16 ilr17  :3;
  __REG16        :1;
  __REG16 ilr18  :3;
  __REG16        :1;
  __REG16 ilr19  :3;
  __REG16        :1;
} __ilcon4_bits;

/* Interrupt Level Control Register 5*/
typedef struct {
  __REG16 ilr20  :3;
  __REG16        :1;
  __REG16 ilr21  :3;
  __REG16        :1;
  __REG16 ilr22  :3;
  __REG16        :1;
  __REG16 ilr23  :3;
  __REG16        :1;
} __ilcon5_bits;


/* Time Base Generator Control Register */
typedef struct {
  __REG8 wdcks   :2;
  __REG8         :1;
  __REG8 itm     :1;
  __REG8 iten    :1;
  __REG8         :3;
} __tbgcon_bits;


/* Flexible Timer Control Register */
typedef struct {
  __REG8 tmclk   :3;
  __REG8 mod     :2;
  __REG8         :3;
} __tmcon_bits;


/* General Purpose Timer Control Register */
typedef struct {
  __REG8 tmclk   :3;
  __REG8         :5;
} __tmgcon_bits;


/* Flexible Timer Status Register */
typedef struct {
  __REG8 ovf     :1;
  __REG8 event   :1;
  __REG8         :6;
} __tmst_bits;


/* General Purpose Timer Status Register */
typedef struct {
  __REG8 ovf     :1;
  __REG8         :7;
} __tmgst_bits;


/* Flexible Timer I/O Level Registers */
typedef struct {
  __REG8 iolv    :2;
  __REG8         :6;
} __tmiolv_bits;


/* Flexible Timer Output Registers */
typedef struct {
  __REG8 tmout   :1;
  __REG8         :7;
} __tmout_bits;


/* Timer Enable Register */
typedef struct {
  __REG8 tm0en   :1;
  __REG8 tm1en   :1;
  __REG8 tm2en   :1;
  __REG8 tm3en   :1;
  __REG8         :4;
} __tmen_bits;


/* Timer Disable Register */
typedef struct {
  __REG8 tm0dis  :1;
  __REG8 tm1dis  :1;
  __REG8 tm2dis  :1;
  __REG8 tm3dis  :1;
  __REG8         :4;
} __tmdis_bits;


/* Interrupt Enable Register */
typedef struct {
  __REG8 erbfi   :1;
  __REG8 etbei   :1;
  __REG8 elsi    :1;
  __REG8 edssi   :1;
  __REG8         :4;
} __ier_bits;


/* Interrupt Identification Register */
typedef union {
  //__IIR
  struct {
    __REG8 intp    :1;
    __REG8 intid   :3;
    __REG8         :2;
    __REG8 fifoen  :2;
  };
  //__FCR
  struct {
    __REG8 fifoe   :1;
    __REG8 rfr     :1;
    __REG8 tfr     :1;
    __REG8 dms     :1;
    __REG8         :2;
    __REG8 rftl    :2;
  };
} __iirfcr_bits;


/* Line Control Register */
typedef struct {
  __REG8 wls     :2;
  __REG8 sbs     :1;
  __REG8 pe      :1;
  __REG8 eps     :1;
  __REG8 sp      :1;
  __REG8 bc      :1;
  __REG8 dlab    :1;
} __lcr_bits;


/* Modem Control Register */
typedef struct {
  __REG8 dtr     :1;
  __REG8 rts     :1;
  __REG8 out1    :1;
  __REG8 out2    :1;
  __REG8 loop    :1;
  __REG8         :3;
} __mcr_bits;


/* Line Status Register */
typedef struct {
  __REG8 dr      :1;
  __REG8 oe      :1;
  __REG8 pe      :1;
  __REG8 fe      :1;
  __REG8 bi      :1;
  __REG8 thre    :1;
  __REG8 temt    :1;
  __REG8 rfr     :1;
} __lsr_bits;


/* Modem Status Register */
typedef struct {
  __REG8 dcts    :1;
  __REG8 ddsr    :1;
  __REG8 teri    :1;
  __REG8 ddcd    :1;
  __REG8 cts     :1;
  __REG8 dsr     :1;
  __REG8 ri      :1;
  __REG8 dcd     :1;
} __msr_bits;


/* Clock Select Register */
typedef struct {
  __REG8 bgclk   :2;
  __REG8         :6;
} __csr_bits;


/* SCI  Status Register */
typedef struct {
  __REG8 ferr    :1;
  __REG8 oerr    :1;
  __REG8 perr    :1;
  __REG8 tremp   :1;
  __REG8 trend   :1;
  __REG8 rcend   :1;
  __REG8         :2;
} __scist_bits;


/* SCI Transmit Control Register */
typedef struct {
  __REG8 stmod   :1;
  __REG8 stln    :1;
  __REG8         :1;
  __REG8 ststb   :1;
  __REG8 stpen   :1;
  __REG8 stodd   :1;
  __REG8 stmie   :1;
  __REG8 stnie   :1;
} __stcon_bits;


/* SCI Receive Control Register */
typedef struct {
  __REG8 srmod   :1;
  __REG8 srln    :1;
  __REG8         :1;
  __REG8 srslv   :1;
  __REG8 srpen   :1;
  __REG8 srodd   :1;
  __REG8 srnie   :1;
  __REG8 srren   :1;
} __srcon_bits;


/* SCI Timer Control Register */
typedef struct {
  __REG8 bgmod   :1;
  __REG8         :1;
  __REG8 qstm    :1;
  __REG8         :1;
  __REG8 bgrun   :1;
  __REG8 bgck    :2;
  __REG8         :1;
} __stmcon_bits;


/* DMA Channel Mode Register 0/1 */
typedef struct {
  __REG16 dme    :1;
  __REG16 sws    :1;
  __REG16 trm    :1;
  __REG16 adm    :1;
  __REG16 dacs   :1;
  __REG16 sam    :2;
  __REG16 lmp    :1;
  __REG16 dts    :1;
  __REG16 dam    :2;
  __REG16 drqd   :1;
  __REG16 dacl   :1;
  __REG16        :3;
} __dcm_bits;


/* DMA Command Register */
typedef struct {
  __REG8 dmae    :1;
  __REG8 cpm     :1;
  __REG8 fdc     :1;
  __REG8 ie0     :1;
  __REG8 ie1     :1;
  __REG8         :3;
} __dcmd_bits;


/* DMA End Status Register */
typedef struct {
  __REG8 ch0erq  :1;
  __REG8 ch1erq  :1;
  __REG8         :2;
  __REG8 ch0irq  :1;
  __REG8 ch1irq  :1;
  __REG8         :2;
} __dmaes_bits;


/* DMA Status Register */
typedef struct {
  __REG8 dst0    :2;
  __REG8 dst1    :2;
  __REG8         :4;
} __dmast_bits;


/* DMA Request Status Register */
typedef struct {
  __REG8 txrdy     :1;
  __REG8 rxrdy     :1;
  __REG8 usb_dreq0 :1;
  __REG8 usb_dreq1 :1;
  __REG8 dreq0     :1;
  __REG8 dreq1     :1;
  __REG8           :2;
} __dreqs_bits;


/* Device Status Register */
typedef struct {
  __REG8 f0      :1;
  __REG8 f1      :1;
  __REG8 f2      :1;
  __REG8 susp    :1;
  __REG8         :4;
} __dvcstat_bits;
	

/* Packet Error Register */
typedef struct {
  __REG8 bse     :1;
  __REG8 dce     :1;
  __REG8 ace     :1;
  __REG8 pide    :1;
  __REG8         :4;
} __pkterr_bits;


/* FIFO Status Register 1 */
typedef struct {
  __REG8 ep0rf   :1;
  __REG8 ep0re   :1;
  __REG8 ep1ful  :1;
  __REG8 ep1emp  :1;
  __REG8         :4;
} __fifostat1_bits;


/* FIFO Status Register 2 */
typedef struct {
  __REG8 ep0tf   :1;
  __REG8 ep0te   :1;
  __REG8 ep2ful  :1;
  __REG8 ep2emp  :1;
  __REG8 ep3ful  :1;
  __REG8 ep3emp  :1;
  __REG8         :2;
} __fifostat2_bits;


/* Endpoint Packet Ready Register */
typedef struct {
  __REG8 ep0rrdy :1;
  __REG8 ep1rrdy :1;
  __REG8 ep2rrdy :1;
  __REG8 ep3rrdy :1;
  __REG8 ep0trdy :1;
  __REG8 ep1trdy :1;
  __REG8 ep2trdy :1;
  __REG8 ep3trdy :1;
} __pktrdy_bits;


/* Transmit FIFO BufferClear Register */
typedef struct {
  __REG8         :1;
  __REG8 ep1tfc  :1;
  __REG8 ep2tfc  :1;
  __REG8 ep3tfc  :1;
  __REG8         :4;
} __clrfifo_bits;


/* Software Reset Register */
typedef struct {
  __REG8 sr      :1;
  __REG8         :7;
} __softrst_bits;


/* Interrupt Enable Register 1 */
typedef struct {
  __REG8 surie     :1;
  __REG8 ep1prie   :1;
  __REG8 ep2prie   :1;
  __REG8 ep0rprie  :1;
  __REG8 ep0tprie  :1;
  __REG8 ubrie     :1;
  __REG8 ssie      :1;
  __REG8 ep3prie   :1;
} __intenbl1_bits;


/* Interrupt Enable Register 2 */
typedef struct {
  __REG8 sofie   :1;
  __REG8         :7;
} __intenbl2_bits;


/* Interrupt Status Register 1 */
typedef struct {
  __REG8 suris     :1;
  __REG8 ep1pris   :1;
  __REG8 ep2pris   :1;
  __REG8 ep0rpris  :1;
  __REG8 ep0tpris  :1;
  __REG8 ubrsis    :1;
  __REG8 ssis      :1;
  __REG8 ep3pris   :1;
} __intstat1_bits;


/* Interrupt Status Register 2 */
typedef struct {
  __REG8 sofis   :1;
  __REG8 ubreis  :1;
  __REG8         :6;
} __intstat2_bits;


/* Endpoint 2/3 DMA Control Register */
typedef struct {
  __REG8 dmaen   :1;
  __REG8         :1;
  __REG8 bci     :1;
  __REG8 tdw     :1;
  __REG8 trm     :1;
  __REG8         :3;
} __dmacon_bits;


/* Endpoint 0 Receive/Transmit Control Register */
typedef struct {
  __REG8 conf    :1;
  __REG8         :1;
  __REG8 trtype  :2;
  __REG8 epa     :3;
  __REG8         :1;
} __ep0rtxcon_bits;


/* Endpoint 0/2/3 Data Toggle Register */
typedef struct {
  __REG8 dtsb    :1;
  __REG8         :7;
} __eptgl_bits;


/* Endpoint 1/2/3 Control Register */
typedef struct {
  __REG8 conf    :1;
  __REG8 stall   :1;
  __REG8 trtype  :2;
  __REG8 epa     :3;
  __REG8 trdir   :1;
} __epcon_bits;


/* Endpoint 1 Data Toggle Register */
typedef struct {
  __REG8 dtsb    :1;
  __REG8 tr      :1;
  __REG8         :6;
} __ep1tgl_bits;


/* Endpoint 0 Status Register */
typedef struct {
  __REG8 srdy    :1;
  __REG8         :1;
  __REG8 stall   :1;
  __REG8 ep0st   :2;
  __REG8         :3;
} __ep0stat_bits;


/* Wake-up Control Register */
typedef struct {
  __REG8 rwup    :1;
  __REG8 oscen   :1;
  __REG8         :2;
  __REG8 sintis  :1;
  __REG8         :3;
} __awkcon_bits;


/* Bus width control Register */
typedef struct {
  __REG8 bwb0    :1;
  __REG8 bwb1    :1;
  __REG8 bwb2    :1;
  __REG8 bwb3    :1;
  __REG8         :4;
} __bwcon_bits;


/* Wait Input control Register */
typedef struct {
  __REG8 wib0    :1;
  __REG8 wib1    :1;
  __REG8 wib2    :1;
  __REG8 wib3    :1;
  __REG8         :4;
} __wicon_bits;		


/* Off time control Register */
typedef struct {
  __REG8 otcn0   :2;
  __REG8 otcn1   :2;
  __REG8 otcn2   :2;
  __REG8 otcn3   :2;
} __otcon_bits;


/* Programmable Wait control Register */
typedef struct {
  __REG8 pwn0    :3;
  __REG8         :1;
  __REG8 pwn1    :3;
  __REG8         :1;
} __pwcon_bits;	


/* Bus access control Register */
typedef struct {
  __REG8 bas0    :1;
  __REG8         :3;
  __REG8 bas1    :1;
  __REG8         :3;
} __bacon_bits;


/* DRAM Bank 2 and 3 Control Register */
typedef struct {
  __REG8 be      :1;
  __REG8 dbas    :1;
  __REG8 amux    :2;
  __REG8         :4;
} __drcon_bits;

/* DRAM Bank 2 and 3 Access Timing Control Registers */
typedef struct {
  __REG8 rcd     :1;
  __REG8         :1;
  __REG8 rp      :1;
  __REG8         :5;
} __atcon_bits;


/* DRAM Bank 2 and 3 Programmable Wait Control Registers */
typedef struct {
  __REG8 cawa    :2;
  __REG8         :6;
} __dwcon_bits;


/* Refresh Timing Control Registers */
typedef struct {
  __REG8 crp     :3;
  __REG8         :1;
  __REG8 chs     :2;
  __REG8         :2;
} __rtcon_bits;


/* Refresh Control Registers */
typedef struct {
  __REG8 cbrr    :2;
  __REG8 rsr     :1;
  __REG8 srsm    :1;
  __REG8 clks    :3;
  __REG8         :1;
} __rfcon_bits;

	
#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/
/***************************************************************************
 **
 **  CPU Control Unit Control Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SBYCON,0x04000000,__WRITE,__sbycon_bits);
__IO_REG32_BIT(__CKCON,0x04000004,__READ_WRITE,__ckcon_bits);
__IO_REG32_BIT(__CKWTCON,0x04000008,__READ_WRITE,__ckwtcon_bits);
__IO_REG32_BIT(__RSTST,0x0400000c,__READ,__rstst_bits);

/***************************************************************************
 **
 **  Interrupt Controller (INT) Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__INR,0x0600000,__READ,__inr_bits);
__IO_REG8_BIT(__CILR,0x0600004,__READ_WRITE, __cilr_bits);
__IO_REG8_BIT(__IRLR,0x0600008,__READ,__irlr_bits);
__IO_REG8_BIT(__EFIQCON,0x060000C,__READ_WRITE,__efiqcon_bits);
__IO_REG8_BIT(__EIRCON,0x0600010,__READ_WRITE,__eircon_bits);
__IO_REG16(__IRR0,0x0600014,__READ_WRITE);
__IO_REG8(__IRR1,0x0600018,__READ_WRITE);
__IO_REG16_BIT(__ILCON0,0x0600020,__READ_WRITE,__ilcon0_bits);
__IO_REG16_BIT(__ILCON1,0x0600024,__READ_WRITE,__ilcon1_bits);
__IO_REG16_BIT(__ILCON2,0x0600028,__READ_WRITE,__ilcon2_bits);
__IO_REG16_BIT(__ILCON3,0x060002C,__READ_WRITE,__ilcon3_bits);
__IO_REG16_BIT(__ILCON4,0x0600030,__READ_WRITE,__ilcon4_bits);
__IO_REG16_BIT(__ILCON5,0x0600034,__READ_WRITE,__ilcon5_bits);


/***************************************************************************
 **
 **  I/O Port Control Registers
 **
 ***************************************************************************/

__IO_REG16(__PO0,0x0600600,__READ_WRITE);
__IO_REG16(__PO1,0x0600604,__READ_WRITE);
__IO_REG16(__PO2,0x0600608,__READ_WRITE);
__IO_REG16(__PO3,0x060060C,__READ_WRITE);

__IO_REG16(__PI0,0x0600610,__READ);
__IO_REG16(__PI1,0x0600614,__READ);
__IO_REG16(__PI2,0x0600618,__READ);
__IO_REG16(__PI3,0x060061C,__READ);


__IO_REG16(__PM0,0x0600620,__READ_WRITE);
__IO_REG16(__PM1,0x0600624,__READ_WRITE);
__IO_REG16(__PM2,0x0600628,__READ_WRITE);
__IO_REG16(__PM3,0x060062C,__READ_WRITE);


__IO_REG16(__PFS0,0x0600630,__READ_WRITE);
__IO_REG16(__PFS1,0x0600634,__READ_WRITE);
__IO_REG16(__PFS2,0x0600638,__READ_WRITE);
__IO_REG8(__PFS3,0x060063C,__READ_WRITE);


/***************************************************************************
 **
 ** Time Base Generator (TBG) Control Registers
 **
 ***************************************************************************/
__IO_REG8(__WDTCON,0x0600200,__WRITE);
__IO_REG8_BIT(__TBGCON,0x0600204,__READ_WRITE,__tbgcon_bits);


/***************************************************************************
 **
 ** Flexible Timer Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__TM0CON,0x0600100,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM0ST,0x0600104,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM0C,0x0600108,__READ_WRITE);
__IO_REG16(__TM0R,0x060010C,__READ_WRITE);
__IO_REG16(__TM0GR,0x0600110,__READ_WRITE);
__IO_REG8_BIT(__TM0IOLV,0x0600114,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM0OUT,0x0600118,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TM1CON,0x0600120,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM1ST,0x0600124,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM1C,0x0600128,__READ_WRITE);
__IO_REG16(__TM1R,0x060012C,__READ_WRITE);
__IO_REG16(__TM1GR,0x0600130,__READ_WRITE);
__IO_REG8_BIT(__TM1IOLV,0x0600134,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM1OUT,0x0600138,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TM2CON,0x0600140,__READ_WRITE,__tmgcon_bits);
__IO_REG8_BIT(__TM2ST,0x0600144,__READ_WRITE,__tmgst_bits);
__IO_REG16(__TM2C,0x0600148,__READ_WRITE);
__IO_REG16(__TM2R,0x060014C,__READ_WRITE);
__IO_REG8_BIT(__TM3CON,0x0600150,__READ_WRITE,__tmgcon_bits);
__IO_REG8_BIT(__TM3ST,0x0600154,__READ_WRITE,__tmgst_bits);
__IO_REG16(__TM3C,0x0600158,__READ_WRITE);
__IO_REG16(__TM3R,0x060015C,__READ_WRITE);
__IO_REG8_BIT(__TMEN,0x0600160,__READ_WRITE,__tmen_bits);
__IO_REG8_BIT(__TMDIS,0x0600164,__WRITE,__tmdis_bits);


/***************************************************************************
 **
 ** Universal Asynchronous Receiver/Transmitter (UART) Registers
 **
 ***************************************************************************/
//RBR and THR share the same address
__IO_REG8(__RBR,0x0600300,__READ);
#define __THR __RBR

//IIR and FCR share the same address
__IO_REG8_BIT(__IER,0x0600304,__READ_WRITE,__ier_bits);
__IO_REG8_BIT(__IIR,0x0600308,__READ,__iirfcr_bits);
#define __FCR_bit __IIR_bit
#define __FCR     __IIR

__IO_REG8_BIT(__LCR,0x060030C,__READ_WRITE,__lcr_bits);
__IO_REG8_BIT(__MCR0,0x0600310,__READ_WRITE,__mcr_bits);
__IO_REG8_BIT(__LSR,0x0600314,__READ_WRITE,__lsr_bits);
__IO_REG8_BIT(__MSR,0x0600318,__READ_WRITE,__msr_bits);
__IO_REG8(__SCR,0x060031C,__READ_WRITE);
__IO_REG8(__DLL,0x0600320,__READ_WRITE);
__IO_REG8(__DLM,0x0600324,__READ_WRITE);
__IO_REG8_BIT(__CSR,0x0600328,__READ_WRITE,__csr_bits);


/***************************************************************************
 **
 ** Serial Communications Interface (SCI) Control Registers
 **
 ***************************************************************************/
__IO_REG8(__SBUF,0x0600400,__READ_WRITE);
__IO_REG8_BIT(__SCIST,0x0600404,__READ_WRITE,__scist_bits);
__IO_REG8_BIT(__STCON,0x0600408,__READ_WRITE,__stcon_bits);
__IO_REG8_BIT(__SRCON,0x060040C,__READ_WRITE,__srcon_bits);
__IO_REG16(__STMC,0x0600410,__READ_WRITE);
__IO_REG16(__STMR,0x0600414,__READ_WRITE);
__IO_REG8_BIT(__STMCON,0x0600418,__READ_WRITE,__stmcon_bits);


/***************************************************************************
 **
 ** Direct Memory Access Controller (DMAC) Control Registers
 **
 ***************************************************************************/
__IO_REG16(__DSAL0,0x0600800,__READ_WRITE);
__IO_REG16(__DSAH0,0x0600804,__READ_WRITE);
__IO_REG16(__DDAL0,0x0600808,__READ_WRITE);
__IO_REG16(__DDAH0,0x060080C,__READ_WRITE);
__IO_REG16(__DTC0,0x0600810,__READ_WRITE);
__IO_REG16(__DTRS0,0x0600814,__READ_WRITE);
__IO_REG16_BIT(__DCM0,0x0600818,__READ_WRITE,__dcm_bits);
__IO_REG16(__DSAL1,0x0600820,__READ_WRITE);
__IO_REG16(__DSAH1,0x0600824,__READ_WRITE);
__IO_REG16(__DDAL1,0x0600828,__READ_WRITE);
__IO_REG16(__DDAH1,0x060082C,__READ_WRITE);
__IO_REG16(__DTC1,0x0600830,__READ_WRITE);
__IO_REG16(__DTRS1,0x0600834,__READ_WRITE);
__IO_REG16_BIT(__DCM1,0x0600838,__READ_WRITE,__dcm_bits);
__IO_REG8_BIT(__DCMD,0x0600840,__READ_WRITE,__dcmd_bits);
__IO_REG8_BIT(__DMAES,0x0600844,__READ_WRITE,__dmaes_bits);
__IO_REG8_BIT(__DMAST,0x0600848,__READ,__dmast_bits);
__IO_REG8_BIT(__DREQS,0x060084C,__READ,__dreqs_bits);


/***************************************************************************
 **
 ** Universal Serial Bus Device Controller (USBC) Control Registers
 **
 ***************************************************************************/
__IO_REG8(__DVCADR,0x0600A00,__READ_WRITE);
__IO_REG8_BIT(__DVCSTAT,0x0600A04,__READ_WRITE,__dvcstat_bits);
__IO_REG8_BIT(__PKTERR,0x0600A08,__READ,__pkterr_bits);
__IO_REG8_BIT(__FIFOSTAT1,0x0600A0C,__READ,__fifostat1_bits);
__IO_REG8_BIT(__FIFOSTAT2,0x0600A10,__READ,__fifostat2_bits);
__IO_REG8(__FRAMELSB,0x0600A14,__READ);
__IO_REG8(__FRAMEMSB,0x0600A18,__READ);
__IO_REG8_BIT(__PKTRDY,0x0600A20,__READ_WRITE,__pktrdy_bits);
__IO_REG8(__EP0RXCNT,0x0600A24,__READ);
__IO_REG8(__EP1RXCNT,0x0600A28,__READ);
__IO_REG8(__EP2RXCNT,0x0600A2C,__READ);
__IO_REG8(__EP3RXCNTLSB,0x0600A30,__READ);
__IO_REG8(__EP3RXCNTMSB,0x0600A34,__READ);
__IO_REG8_BIT(__CLRFIFO,0x0600A38,__WRITE,__clrfifo_bits);
__IO_REG8_BIT(__SOFTRST,0x0600A3C,__WRITE,__softrst_bits);
__IO_REG8(__bmRequestType,0x0600A40,__READ);
__IO_REG8(__bRequest,0x0600A44,__READ);
__IO_REG8(__wValueLSB,0x0600A48,__READ);
__IO_REG8(__wValueMSB,0x0600A4C,__READ);
__IO_REG8(__wIndexLSB,0x0600A50,__READ);
__IO_REG8(__wIndexMSB,0x0600A54,__READ);
__IO_REG8(__wLengthLSB,0x0600A58,__READ);
__IO_REG8(__wLengthMSB,0x0600A5C,__READ);
__IO_REG8_BIT(__INTENBL1,0x0600A60,__READ_WRITE,__intenbl1_bits);
__IO_REG8_BIT(__INTENBL2,0x0600A64,__READ_WRITE,__intenbl2_bits);
__IO_REG8_BIT(__INTSTAT1,0x0600A68,__READ_WRITE,__intstat1_bits);
__IO_REG8_BIT(__INTSTAT2,0x0600A6C,__READ_WRITE,__intstat2_bits);
__IO_REG8_BIT(__DMACON2,0x0600A70,__READ_WRITE,__dmacon_bits);
__IO_REG8(__DMAINTVL2,0x0600A74,__READ_WRITE);
__IO_REG8_BIT(__DMACON3,0x0600A78,__READ_WRITE,__dmacon_bits);
__IO_REG8(__DMAINTVL3,0x0600A7C,__READ_WRITE);
__IO_REG8_BIT(__EP0RXCON,0x0600A80,__READ,__ep0rtxcon_bits);
__IO_REG8_BIT(__EP0RXTGL,0x0600A84,__READ,__eptgl_bits);
__IO_REG8(__EP0RXPLD,0x0600A88,__READ_WRITE);
__IO_REG8_BIT(__EP1CON,0x0600A90,__READ_WRITE,__epcon_bits);
__IO_REG8_BIT(__EP1TGL,0x0600A94,__READ_WRITE,__ep1tgl_bits);
__IO_REG8(__EP1PLD,0x0600A98,__READ_WRITE);
__IO_REG8_BIT(__EP0TXCON,0x0600AC0,__READ,__ep0rtxcon_bits);
__IO_REG8_BIT(__EP0TXTGL,0x0600AC4,__READ,__eptgl_bits);
__IO_REG8(__EP0TXPLD,0x0600AC8,__READ_WRITE);
__IO_REG8_BIT(__EP0STAT,0x0600ACC,__READ_WRITE,__ep0stat_bits);
__IO_REG8_BIT(__EP2CON,0x0600AD0,__READ_WRITE,__epcon_bits);
__IO_REG8_BIT(__EP2TGL,0x0600AD4,__READ_WRITE,__eptgl_bits);
__IO_REG8(__EP2PLD,0x0600AD8,__READ_WRITE);
__IO_REG8_BIT(__EP3CON,0x0600AE0,__READ_WRITE,__epcon_bits);
__IO_REG8_BIT(__EP3TGL,0x0600AE4,__READ_WRITE,__eptgl_bits);
__IO_REG8(__EP3PLDLSB,0x0600AE8,__READ_WRITE);
__IO_REG8(__EP3PLDMSB,0x0600AEC,__READ_WRITE);

__IO_REG8(__EP0RXFIFO,0x0600B00,__READ);
#define __EP0TXFIFO __EP0RXFIFO

__IO_REG8(__EP1RXFIFO,0x0600B04,__READ);
#define __EP1TXFIFO __EP1RXFIFO

__IO_REG8(__EP2RXFIFO,0x0600B08,__READ);
#define __EP2TXFIFO __EP2RXFIFO

__IO_REG8(__EP3RXFIFO,0x0600B0C,__READ);
#define __EP3TXFIFO __EP3RXFIFO

__IO_REG8_BIT(__AWKCON,0x0600B10,__READ_WRITE,__awkcon_bits);


/***************************************************************************
 **
 ** External Memory Controller (XMC) Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__BWCON,0x0600700,__READ_WRITE,__bwcon_bits);
__IO_REG8_BIT(__WICON,0x0600704,__READ_WRITE,__wicon_bits);
__IO_REG8_BIT(__OTCON,0x0600708,__READ_WRITE,__otcon_bits);
__IO_REG8_BIT(__PWCON,0x060070C,__READ_WRITE,__pwcon_bits);
__IO_REG8_BIT(__BACON,0x0600710,__READ_WRITE,__bacon_bits);
__IO_REG8_BIT(__DR2CON,0x0600714,__READ_WRITE,__drcon_bits);
__IO_REG8_BIT(__AT2CON,0x0600718,__READ_WRITE,__atcon_bits);
__IO_REG8_BIT(__DW2CON,0x060071C,__READ_WRITE,__dwcon_bits);
__IO_REG8_BIT(__DR3CON,0x0600720,__READ_WRITE,__drcon_bits);
__IO_REG8_BIT(__AT3CON,0x0600724,__READ_WRITE,__atcon_bits);
__IO_REG8_BIT(__DW3CON,0x0600728,__READ_WRITE,__dwcon_bits);
__IO_REG8(__RFTCN,0x060072C,__READ_WRITE);
__IO_REG8(__RCCON,0x0600730,__READ_WRITE);
__IO_REG8_BIT(__RTCON,0x0600734,__READ_WRITE,__rtcon_bits);
__IO_REG8_BIT(__RFCON,0x0600738,__READ_WRITE,__rfcon_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **   ML671000 interrupt sources
 **
 ***************************************************************************/

#define USBSINT    0    /* A/D conversion complete interrupt          */
#define UARTEVENT  1    /* Transfer complete interrupt req from CSI   */
#define BGINT      2    /* Baud rate interrupt request from ASI       */
#define SCIEVENT   3
#define DMAEVENT   4    /* Transmit ready interrupt from ASI          */
#define WDINT      5    /* Watchdog timer interrupt req from TBG      */
#define TMOV2      6
#define TMOV3      7
#define TMOV0      8
#define TMEVENT0   9
#define TMOV1     10    /* Capture event or compare match interrupt request from FTM */
#define TMEVENT1  11
#define USBEVENT  12
/* Reserved: 13-15 */
#define EIR_0     16    /* Interrupt request from EIR_n     pin*/
#define EIR_1     17
#define EIR_2     18
#define EIR_3     19
#define EIR_4     20
#define EIR_5     21
#define EIR_6     22
#define EIR_7     23

#endif    /* __ML671000_H */
