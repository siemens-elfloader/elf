/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    OKI Semiconductors ML672300
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2000
 **                                
 **    $Revision: 1.5 $
 **                                
 ***************************************************************************/

#ifndef __ML672300_H
#define __ML672300_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    ML672300 SPECIAL FUNCTION REGISTERS
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
  __REG32 hlt  :1;
  __REG32 stp  :1;
  __REG32      :30;
} __sbycon_bits;


/* Clock Control Register */
typedef struct {
  __REG32 ckm   :4;
  __REG32 mcgen :1;
  __REG32      :27;
} __ckcon_bits;

/* Clock Warm-Up Time Control Register */
typedef struct {
  __REG32 ckwt  :2;
  __REG32      :30;
} __ckwtcon_bits;

/* Reset Status Register */
typedef struct {
  __REG32 wdtrst :1;
  __REG32        :31;
} __rstst_bits;


/* Interrupt Number Register */
typedef struct {
  __REG8 in     :5;
  __REG8        :3;
} __inr_bits;

/* Current Interrupt Level Register */
typedef struct {
  __REG8        :1;
  __REG8 cilr1  :1;
  __REG8 cilr2  :1;
  __REG8 cilr3  :1;
  __REG8 cilr4  :1;
  __REG8 cilr5  :1;
  __REG8 cilr6  :1;
  __REG8 cilr7  :1;
} __cilr_bits;

/* Interrupt Request Level Register */
typedef struct {
  __REG8 irl    :3;
  __REG8        :5;
} __irlr_bits;

/* External FIQ Control Register */
typedef struct {
  __REG8 efiqr  :1;
  __REG8        :1;
  __REG8 efiqm  :1;
  __REG8        :5;
} __efiqcon_bits;

/* External IRQ Control Register */
typedef struct {
  __REG8 eir0  :1;
  __REG8 eir1  :1;
  __REG8 eir2  :1;
  __REG8       :5;
} __eircon_bits;

/* Interrupt Level Control Register 0*/
typedef struct {
  __REG8 ilr0  :3;
  __REG8       :1;
  __REG8 ilr1  :3;
  __REG8       :1;
} __ilcon0_bits;

/* Interrupt Level Control Register 1*/
typedef struct {
  __REG8 ilr2  :3;
  __REG8       :1;
  __REG8 ilr3  :3;
  __REG8       :1;
} __ilcon1_bits;

/* Interrupt Level Control Register 2*/
typedef struct {
  __REG8 ilr4  :3;
  __REG8       :1;
  __REG8 ilr5  :3;
  __REG8       :1;
} __ilcon2_bits;

/* Interrupt Level Control Register 2*/
typedef struct {
  __REG8 ilr6  :3;
  __REG8       :1;
  __REG8 ilr7  :3;
  __REG8       :1;
} __ilcon3_bits;

/* Interrupt Level Control Register 4*/
typedef struct {
  __REG8 ilr8  :3;
  __REG8       :1;
  __REG8 ilr9  :3;
  __REG8       :1;
} __ilcon4_bits;

/* Interrupt Level Control Register 5*/
typedef struct {
  __REG8 ilr10 :3;
  __REG8       :1;
  __REG8 ilr11 :3;
  __REG8       :1;
} __ilcon5_bits;

/* Interrupt Level Control Register 6*/
typedef struct {
  __REG8 ilr12 :3;
  __REG8       :1;
  __REG8 ilr13 :3;
  __REG8       :1;
} __ilcon6_bits;

/* Interrupt Level Control Register 7*/
typedef struct {
  __REG8 ilr14 :3;
  __REG8       :1;
  __REG8 ilr15 :3;
  __REG8       :1;
} __ilcon7_bits;

/* Interrupt Level Control Register 8*/
typedef struct {
  __REG8 ilr16 :3;
  __REG8       :1;
  __REG8 ilr17 :3;
  __REG8       :1;
} __ilcon8_bits;

/* Interrupt Level Control Register 9*/
typedef struct {
  __REG8 ilr18 :3;
  __REG8       :1;
  __REG8 ilr19 :3;
  __REG8       :1;
} __ilcon9_bits;

/* Interrupt Level Control Register 10*/
typedef struct {
  __REG8 ilr20 :3;
  __REG8       :1;
  __REG8 ilr21 :3;
  __REG8       :1;
} __ilcon10_bits;

/* Interrupt Level Control Register 11*/
typedef struct {
  __REG8       :4;
  __REG8 ilr23 :3;
  __REG8       :1;
} __ilcon11_bits;

/* Interrupt Level Control Register 12*/
typedef struct {
  __REG8 ilr24 :3;
  __REG8       :1;
  __REG8 ilr25 :3;
  __REG8       :1;
} __ilcon12_bits;

/* Interrupt Level Control Register 13*/
typedef struct {
  __REG8 ilr26 :3;
  __REG8       :5;
} __ilcon13_bits;

/* Interrupt Level Control Register 14*/
typedef struct {
  __REG8       :4;
  __REG8 ilr29 :3;
  __REG8       :1;
} __ilcon14_bits;

/* Interrupt Level Control Register 15*/
typedef struct {
  __REG8 ilr30 :3;
  __REG8       :5;
} __ilcon15_bits;

/* Interrupt Level Control Register 15*/
typedef struct {
  __REG8 scm   :1;
  __REG8       :7;
} __cmsr_bits;

/* Time Base Generator Control Register */
typedef struct {
  __REG8 wdcks :2;
  __REG8       :1;
  __REG8 itm   :1;
  __REG8 iten  :1;
  __REG8       :3;
} __tbgcon_bits;

/* Watch Timer Control Register */
typedef struct {
  __REG8 wten  :1;
  __REG8       :7;
} __wtcon_bits;

/* Time Control Register */
typedef struct {
  __REG8 tmclk :3;
  __REG8 mod   :2;
  __REG8       :3;
} __tmcon_bits;


/* Time Status Register compare out/capture mode */
typedef struct {
  __REG8 ovf     :1;
  __REG8 cm_capev:1;
  __REG8         :6;
} __tmst_bits;


/* Time I/O Level Registers */
typedef struct {
  __REG8 iolv    :2;
  __REG8         :6;
} __tmiolv_bits;


/* Time Output Registers */
typedef struct {
  __REG8 tmout   :1;
  __REG8         :7;
} __tmout_bits;


/* Time Enable Register */
typedef struct {
  __REG8 tm0en   :1;
  __REG8 tm1en   :1;
  __REG8 tm2en   :1;
  __REG8 tm3en   :1;
  __REG8 tm4en   :1;
  __REG8 tm5en   :1;
  __REG8         :2;
  
} __tmen_bits;

/* Time Disable Register */
typedef struct {
  __REG8 tm0dis  :1;
  __REG8 tm1dis  :1;
  __REG8 tm2dis  :1;
  __REG8 tm3dis  :1;
  __REG8 tm4dis  :1;
  __REG8 tm5dis  :1;
  __REG8         :2;
  
} __tmdis_bits;


/* ASI  Control Register */
typedef struct {
  __REG8 asln    :1;
  __REG8 aspen   :1;
  __REG8 asevn   :1;
  __REG8 aststb  :1;
  __REG8         :3;
  __REG8 asrven  :1;
} __asicon_bits;

/* ASI Status Register */
typedef struct {
  __REG8 ferr    :1;
  __REG8 oerr    :1;
  __REG8 perr    :1;
  __REG8         :1;
  __REG8 arvirq  :1;
  __REG8 atrirq  :1;
  __REG8         :2;
} __asist_bits;


/* ASI Test Control Register */
typedef struct {
  __REG8 mferr   :1;
  __REG8 mperr   :1;
  __REG8         :5;
  __REG8 lbtst   :1;
} __astscon_bits;
	

/* Baud Rate Control Register */
typedef struct {
  __REG8 bgmod   :1;
  __REG8         :1;
  __REG8 qstm    :1;
  __REG8         :1;
  __REG8 bgrun   :1;
  __REG8 bgck    :2;
  __REG8         :1;
} __asbcon_bits;


/* CSI Control Register */
typedef struct {
  __REG8 cssftc  :2;
  __REG8         :1;
  __REG8 csmsv   :1;
  __REG8         :4;
} __csicon_bits;


/* CSI Status Registers */
typedef struct {
  __REG8 busy    :1;
  __REG8         :3;
  __REG8 sftct   :3;
  __REG8         :1;
} __csist_bits;


/* CSI Test Control Register */
typedef struct {
  __REG8         :7;
  __REG8 lbtst   :1;
} __cstscon_bits;		
	

/* AD Control Register */
typedef struct {
  __REG8 adstch  :4;
  __REG8 adchmod :1;
  __REG8         :1;
  __REG8 cont    :1;
  __REG8 adrun   :1;
} __adhcon_bits;


/* AD Control Register L */
typedef struct {
  __REG8 adtm    :2;
  __REG8         :6;
} __adlcon_bits;


/* AD Status Register */
typedef struct {
  __REG8 aderq   :1;
  __REG8         :7;
} __adst_bits;


/* Bus width control Register */
typedef struct {
  __REG8 bwb0   :1;
  __REG8 bwb1   :1;
  __REG8 bwb2   :1;
  __REG8        :5;
} __bwcon_bits;


/* Wait Input control Register */
typedef struct {
  __REG8 wib0   :1;
  __REG8 wib1   :1;
  __REG8 wib2   :1;
  __REG8        :5;
} __wicon_bits;		


/* Off time control Register */
typedef struct {
  __REG8 otcn0  :2;
  __REG8 otcn1  :2;
  __REG8 otcn2  :2;
  __REG8        :2;
} __otcon_bits;


/* Programmable Wait control Register */
typedef struct {
  __REG8 pwn0   :3;
  __REG8        :1;
  __REG8 pwn1   :3;
  __REG8        :1;
} __pwcon0_bits;	

typedef struct {
  __REG8 pwn2   :3;
  __REG8        :5;
} __pwcon1_bits;	

typedef struct {
  __REG8 pwnc   :4;
  __REG8        :4;
} __pwcon2_bits;	

/* CAN Control Register */
typedef struct {
  __REG8 init   :1;
  __REG8 tirs   :1;
  __REG8        :1;
  __REG8 sync   :1;
  __REG8 cana   :1;
  __REG8 txf    :1;
  __REG8 rxf    :1;
  __REG8        :1;
} __canc_bits;	

/* CAN Interrupt Control Register */
typedef struct {
  __REG8 eintt   :1;
  __REG8 eintr   :1;
  __REG8 einte   :1;
  __REG8         :1;
  __REG8 itf     :1;
  __REG8 irf     :1;
  __REG8 ief     :1;
  __REG8 meint   :1;
} __cani_bits;	

/* Message Box Count Setting Register */
typedef struct {
  __REG8 nmes0   :1;
  __REG8 nmes1   :1;
  __REG8 nmes2   :1;
  __REG8 nmes3   :1;
  __REG8         :4;
} __nmes_bits;	

/* CAN Bus Timing Registers */
typedef struct {
  __REG8 brp0   :1;
  __REG8 brp1   :1;
  __REG8 brp2   :1;
  __REG8 brp3   :1;
  __REG8 brp4   :1;
  __REG8 brp5   :1;
  __REG8 sjwa   :1;
  __REG8 sjwb   :1;
} __btr0_bits;	

typedef struct {
  __REG8 tseg10   :1;
  __REG8 tseg11   :1;
  __REG8 tseg12   :1;
  __REG8 tseg13   :1;
  __REG8 tseg20   :1;
  __REG8 tseg21   :1;
  __REG8 tseg22   :1;
  __REG8          :1;
} __btr1_bits;	

/* Communication Input/Output Control Register */
typedef struct {
  __REG8 ocmd0   :1;
  __REG8 ocmd1   :1;
  __REG8 ocpol   :1;
  __REG8 octn    :1;
  __REG8 octp    :1;
  __REG8         :3;
} __tioc_bits;	

/* Group Message Registers 0 and 1 */
typedef struct {
  __REG8 gmr00   :1;
  __REG8 gmr01   :1;
  __REG8 gmr02   :1;
  __REG8 gmr03   :1;
  __REG8         :3;
  __REG8 egm0    :1;
} __gmr0_bits;	

typedef struct {
  __REG8 gmr10   :1;
  __REG8 gmr11   :1;
  __REG8 gmr12   :1;
  __REG8 gmr13   :1;
  __REG8         :3;
  __REG8 egm1    :1;
} __gmr1_bits;	

/* Group Message Mask Registers */
typedef struct {
  __REG8 m0id21  :1;
  __REG8 m0id22  :1;
  __REG8 m0id23  :1;
  __REG8 m0id24  :1;
  __REG8 m0id25  :1;
  __REG8 m0id26  :1;
  __REG8 m0id27  :1;
  __REG8 m0id28  :1;
} __gmsk00_bits;	

typedef struct {
  __REG8 m0id13  :1;
  __REG8 m0id14  :1;
  __REG8 m0id15  :1;
  __REG8 m0id16  :1;
  __REG8 m0id17  :1;
  __REG8 m0id18  :1;
  __REG8 m0id19  :1;
  __REG8 m0id20  :1;
} __gmsk01_bits;	

typedef struct {
  __REG8 m0id5   :1;
  __REG8 m0id6   :1;
  __REG8 m0id7   :1;
  __REG8 m0id8   :1;
  __REG8 m0id9   :1;
  __REG8 m0id10  :1;
  __REG8 m0id11  :1;
  __REG8 m0id12  :1;
} __gmsk02_bits;	

typedef struct {
  __REG8         :3;
  __REG8 m0id0   :1;
  __REG8 m0id1   :1;
  __REG8 m0id2   :1;
  __REG8 m0id3   :1;
  __REG8 m0id4   :1;
} __gmsk03_bits;	


typedef struct {
  __REG8 m1id21  :1;
  __REG8 m1id22  :1;
  __REG8 m1id23  :1;
  __REG8 m1id24  :1;
  __REG8 m1id25  :1;
  __REG8 m1id26  :1;
  __REG8 m1id27  :1;
  __REG8 m1id28  :1;
} __gmsk10_bits;	

typedef struct {
  __REG8 m1id13  :1;
  __REG8 m1id14  :1;
  __REG8 m1id15  :1;
  __REG8 m1id16  :1;
  __REG8 m1id17  :1;
  __REG8 m1id18  :1;
  __REG8 m1id19  :1;
  __REG8 m1id20  :1;
} __gmsk11_bits;	

typedef struct {
  __REG8 m1id5   :1;
  __REG8 m1id6   :1;
  __REG8 m1id7   :1;
  __REG8 m1id8   :1;
  __REG8 m1id9   :1;
  __REG8 m1id10  :1;
  __REG8 m1id11  :1;
  __REG8 m1id12  :1;
} __gmsk12_bits;	

typedef struct {
  __REG8         :3;
  __REG8 m1id0   :1;
  __REG8 m1id1   :1;
  __REG8 m1id2   :1;
  __REG8 m1id3   :1;
  __REG8 m1id4   :1;
} __gmsk13_bits;	

/* Stancby Control Register */
typedef struct {
  __REG8 stop    :1;
  __REG8 sleep   :1;
  __REG8         :6;
} __stdby_bits;	

/* CAN Control Register 2 */
typedef struct {
  __REG8 compat  :1;
  __REG8         :3;
  __REG8 rstec   :1;
  __REG8         :3;
} __canc2_bits;	


/* Communication Message Box Number Register */
typedef struct {
  __REG8 trsn0  :1;
  __REG8 trsn1  :1;
  __REG8 trsn2  :1;
  __REG8 trsn3  :1;
  __REG8        :4;
} __tmn_bits;	

/* CAN Status Register */

typedef struct {
  __REG8 rew     :1;
  __REG8 rep     :1;
  __REG8         :2;
  __REG8 tew     :1;
  __REG8 tep     :1;
  __REG8 boff    :1;
  __REG8         :1;
} __cans_bits;	

/* Transmit Error Counter */
typedef struct {
  __REG8 tec0    :1;
  __REG8 tec1    :1;
  __REG8 tec2    :1;
  __REG8 tec3    :1;
  __REG8 tec4    :1;
  __REG8 tec5    :1;
  __REG8 tec6    :1;
  __REG8 tec7    :1;
} __tec_bits;	

/* Receive Error Counter */
typedef struct {
  __REG8 rec0    :1;
  __REG8 rec1    :1;
  __REG8 rec2    :1;
  __REG8 rec3    :1;
  __REG8 rec4    :1;
  __REG8 rec5    :1;
  __REG8 rec6    :1;
  __REG8 rec7    :1;
} __rec_bits;	

/* CAN Status Register 2 */
typedef struct {
  __REG8 bite    :1;
  __REG8 stuf    :1;
  __REG8 ack     :1;
  __REG8 crc     :1;
  __REG8 frm     :1;
  __REG8         :2;
  __REG8 bof     :1;
} __cans2_bits;	

/* Bus Off Release */
typedef struct {
  __REG8 boc0    :1;
  __REG8 boc1    :1;
  __REG8 boc2    :1;
  __REG8 boc3    :1;
  __REG8 boc4    :1;
  __REG8 boc5    :1;
  __REG8 boc6    :1;
  __REG8 boc7    :1;
} __boco_bits;	



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
__IO_REG8_BIT(__CILR,0x0600002,__READ_WRITE, __cilr_bits);
__IO_REG8_BIT(__IRLR,0x0600003,__READ,__irlr_bits);
__IO_REG8_BIT(__EFIQCON,0x0600004,__READ_WRITE,__efiqcon_bits);
__IO_REG8_BIT(__EIRCON,0x0600005,__READ_WRITE,__eircon_bits);
__IO_REG8(__IRR0,0x0600008,__READ_WRITE);
__IO_REG8(__IRR1,0x0600009,__READ_WRITE);
__IO_REG8(__IRR2,0x060000a,__READ_WRITE);
__IO_REG8(__IRR3,0x060000b,__READ_WRITE);
__IO_REG8_BIT(__ILCON0,0x0600010,__READ_WRITE,__ilcon0_bits);
__IO_REG8_BIT(__ILCON1,0x0600011,__READ_WRITE,__ilcon1_bits);
__IO_REG8_BIT(__ILCON2,0x0600012,__READ_WRITE,__ilcon2_bits);
__IO_REG8_BIT(__ILCON3,0x0600013,__READ_WRITE,__ilcon3_bits);
__IO_REG8_BIT(__ILCON4,0x0600014,__READ_WRITE,__ilcon4_bits);
__IO_REG8_BIT(__ILCON5,0x0600015,__READ_WRITE,__ilcon5_bits);
__IO_REG8_BIT(__ILCON6,0x0600016,__READ_WRITE,__ilcon6_bits);
__IO_REG8_BIT(__ILCON7,0x0600017,__READ_WRITE,__ilcon7_bits);
__IO_REG8_BIT(__ILCON8,0x0600018,__READ_WRITE,__ilcon8_bits);
__IO_REG8_BIT(__ILCON9,0x0600019,__READ_WRITE,__ilcon9_bits);
__IO_REG8_BIT(__ILCON10,0x060001a,__READ_WRITE,__ilcon10_bits);
__IO_REG8_BIT(__ILCON11,0x060001b,__READ_WRITE,__ilcon11_bits);
__IO_REG8_BIT(__ILCON12,0x060001c,__READ_WRITE,__ilcon12_bits);
__IO_REG8_BIT(__ILCON13,0x060001d,__READ_WRITE,__ilcon13_bits);
__IO_REG8_BIT(__ILCON14,0x060001e,__READ_WRITE,__ilcon14_bits);
__IO_REG8_BIT(__ILCON15,0x060001f,__READ_WRITE,__ilcon15_bits);


/***************************************************************************
 **
 **  I/O Port Control Registers
 **
 ***************************************************************************/

__IO_REG8(__PO0,0x0600600,__READ_WRITE);
__IO_REG8(__PO1,0x0600601,__READ_WRITE);
__IO_REG8(__PO2,0x0600602,__READ_WRITE);
__IO_REG8(__PO3,0x0600603,__READ_WRITE);
__IO_REG8(__PO4,0x0600604,__READ_WRITE);
__IO_REG8(__PO5,0x0600605,__READ_WRITE);
__IO_REG8(__PO6,0x0600606,__READ_WRITE);
__IO_REG8(__PO7,0x0600607,__READ_WRITE);
__IO_REG8(__PO8,0x0600608,__READ_WRITE);
__IO_REG8(__PO9,0x0600609,__READ_WRITE);
__IO_REG8(__PO10,0x060060a,__READ_WRITE);
__IO_REG8(__PO11,0x060060b,__READ_WRITE);
__IO_REG8(__PO12,0x060060c,__READ_WRITE);
__IO_REG8(__PO13,0x060060d,__READ_WRITE);
__IO_REG8(__PO14,0x060060e,__READ_WRITE);

__IO_REG8(__PI0,0x0600610,__READ);
__IO_REG8(__PI1,0x0600611,__READ);
__IO_REG8(__PI2,0x0600612,__READ);
__IO_REG8(__PI3,0x0600613,__READ);
__IO_REG8(__PI4,0x0600614,__READ);
__IO_REG8(__PI5,0x0600615,__READ);
__IO_REG8(__PI6,0x0600616,__READ);
__IO_REG8(__PI7,0x0600617,__READ);
__IO_REG8(__PI8,0x0600618,__READ);
__IO_REG8(__PI9,0x0600619,__READ);
__IO_REG8(__PI10,0x060061a,__READ);
__IO_REG8(__PI11,0x060061b,__READ);
__IO_REG8(__PI12,0x060061c,__READ);
__IO_REG8(__PI13,0x060061d,__READ);
__IO_REG8(__PI14,0x060061e,__READ);


__IO_REG8(__PM0,0x0600620,__READ_WRITE);
__IO_REG8(__PM1,0x0600621,__READ_WRITE);
__IO_REG8(__PM2,0x0600622,__READ_WRITE);
__IO_REG8(__PM3,0x0600623,__READ_WRITE);
__IO_REG8(__PM4,0x0600624,__READ_WRITE);
__IO_REG8(__PM5,0x0600625,__READ_WRITE);
__IO_REG8(__PM6,0x0600626,__READ_WRITE);
__IO_REG8(__PM7,0x0600627,__READ_WRITE);
__IO_REG8(__PM8,0x0600628,__READ_WRITE);
__IO_REG8(__PM9,0x0600629,__READ_WRITE);
__IO_REG8(__PM10,0x060062a,__READ_WRITE);
__IO_REG8(__PM11,0x060062b,__READ_WRITE);
__IO_REG8(__PM12,0x060062c,__READ_WRITE);
__IO_REG8(__PM13,0x060062d,__READ_WRITE);
__IO_REG8(__PM14,0x060062e,__READ_WRITE);


__IO_REG8(__PFS0,0x0600630,__READ_WRITE);
__IO_REG8(__PFS1,0x0600631,__READ_WRITE);
__IO_REG8(__PFS2,0x0600632,__READ_WRITE);
__IO_REG8(__PFS3,0x0600633,__READ_WRITE);
__IO_REG8(__PFS4,0x0600634,__READ_WRITE);
__IO_REG8(__PFS5,0x0600635,__READ_WRITE);
__IO_REG8(__PFS6,0x0600636,__READ_WRITE);
__IO_REG8(__PFS7,0x0600637,__READ_WRITE);
__IO_REG8(__PFS8,0x0600638,__READ_WRITE);
__IO_REG8(__PFS9,0x0600639,__READ_WRITE);
__IO_REG8(__PFS10,0x060063a,__READ_WRITE);
__IO_REG8(__PFS11,0x060063b,__READ_WRITE);
__IO_REG8(__PFS12,0x060063c,__READ_WRITE);
__IO_REG8(__PFS13,0x060063d,__READ_WRITE);
__IO_REG8(__PFS14,0x060063e,__READ_WRITE);

__IO_REG8_BIT(__CMSR,0x060063f,__READ_WRITE,__cmsr_bits);



/***************************************************************************
 **
 ** Time Base Generator (TBG) Control Registers
 **
 ***************************************************************************/
__IO_REG8(__WDTCON,0x0600200,__WRITE);
__IO_REG8_BIT(__TBGCON,0x0600201,__READ_WRITE,__tbgcon_bits);

/***************************************************************************
 **
 **  Watch Timer Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__WTCON,0x0600800,__READ_WRITE,__wtcon_bits);
__IO_REG16(__WTC,0x0600802,__READ_WRITE);
__IO_REG16(__WTR,0x0600804,__READ_WRITE);


/***************************************************************************
 **
 ** Flexible Timer (FTM) Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__TM0CON,0x0600100,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM0ST,0x0600101,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM0C,0x0600102,__READ_WRITE);
__IO_REG16(__TM0R,0x0600104,__READ_WRITE);
__IO_REG16(__TM0GR,0x0600106,__READ_WRITE);
__IO_REG8_BIT(__TM0IOLV,0x0600108,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM0OUT,0x0600109,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TM1CON,0x0600110,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM1ST,0x0600111,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM1C,0x0600112,__READ_WRITE);
__IO_REG16(__TM1R,0x0600114,__READ_WRITE);
__IO_REG16(__TM1GR,0x0600116,__READ_WRITE);
__IO_REG8_BIT(__TM1IOLV,0x0600118,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM1OUT,0x0600119,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TM2CON,0x0600120,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM2ST,0x0600121,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM2C,0x0600122,__READ_WRITE);
__IO_REG16(__TM2R,0x0600124,__READ_WRITE);
__IO_REG16(__TM2GR,0x0600126,__READ_WRITE);
__IO_REG8_BIT(__TM2IOLV,0x0600128,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM2OUT,0x0600129,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TM3CON,0x0600130,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM3ST,0x0600131,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM3C,0x0600132,__READ_WRITE);
__IO_REG16(__TM3R,0x0600134,__READ_WRITE);
__IO_REG16(__TM3GR,0x0600136,__READ_WRITE);
__IO_REG8_BIT(__TM3IOLV,0x0600138,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM3OUT,0x0600139,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TM4CON,0x0600140,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM4ST,0x0600141,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM4C,0x0600142,__READ_WRITE);
__IO_REG16(__TM4R,0x0600144,__READ_WRITE);
__IO_REG16(__TM4GR,0x0600146,__READ_WRITE);
__IO_REG8_BIT(__TM4IOLV,0x0600148,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM4OUT,0x0600149,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TM5CON,0x0600150,__READ_WRITE,__tmcon_bits);
__IO_REG8_BIT(__TM5ST,0x0600151,__READ_WRITE,__tmst_bits);
__IO_REG16(__TM5C,0x0600152,__READ_WRITE);
__IO_REG16(__TM5R,0x0600154,__READ_WRITE);
__IO_REG16(__TM5GR,0x0600156,__READ_WRITE);
__IO_REG8_BIT(__TM5IOLV,0x0600158,__READ_WRITE,__tmiolv_bits);
__IO_REG8_BIT(__TM5OUT,0x0600159,__READ_WRITE,__tmout_bits);
__IO_REG8_BIT(__TMEN,0x0600160,__READ_WRITE,__tmen_bits);
__IO_REG8_BIT(__TMDIS,0x0600161,__WRITE,__tmdis_bits);


/***************************************************************************
 **
 ** Asynchonous Serial Interface (ASI) Control Registers
 **
 ***************************************************************************/
__IO_REG8(__AS0BUF,0x0600300,__READ_WRITE);
__IO_REG8_BIT(__ASI0ST,0x0600301,__READ_WRITE,__asist_bits);
__IO_REG8_BIT(__ASI0CON,0x0600302,__READ_WRITE,__asicon_bits);
__IO_REG8_BIT(__AS0BCON,0x0600303,__READ_WRITE,__asbcon_bits);
__IO_REG8(__AS0BTMC,0x0600304,__READ_WRITE);
__IO_REG8(__AS0BTMR,0x0600305,__READ_WRITE);
__IO_REG8_BIT(__AS0TSCON,0x0600306,__READ_WRITE,__astscon_bits);
__IO_REG8(__AS1BUF,0x0600310,__READ_WRITE);
__IO_REG8_BIT(__ASI1ST,0x0600311,__READ_WRITE,__asist_bits);
__IO_REG8_BIT(__ASI1CON,0x0600312,__READ_WRITE,__asicon_bits);
__IO_REG8_BIT(__AS1BCON,0x0600313,__READ_WRITE,__asbcon_bits);
__IO_REG8(__AS1BTMC,0x0600314,__READ_WRITE);
__IO_REG8(__AS1BTMR,0x0600315,__READ_WRITE);
__IO_REG8_BIT(__AS1TSCON,0x0600316,__READ_WRITE,__astscon_bits);

/***************************************************************************
 **
 ** Clock SynchronousSerial Interface (CSIn) Control Registers
 **
 ***************************************************************************/
 
__IO_REG8(__CSI0SFT,0x0600400,__READ_WRITE);
__IO_REG8_BIT(__CSI0ST,0x0600401,__READ_WRITE,__csist_bits);
__IO_REG8_BIT(__CSI0CON,0x0600402,__READ_WRITE,__csicon_bits);
__IO_REG8(__CSI1SFT,0x0600404,__READ_WRITE);
__IO_REG8_BIT(__CSI1ST,0x0600405,__READ_WRITE,__csist_bits);
__IO_REG8_BIT(__CSI1CON,0x0600406,__READ_WRITE,__csicon_bits);
__IO_REG8_BIT(__CSTSCON,0x0600407,__READ_WRITE,__cstscon_bits);

/***************************************************************************
 **
 ** Analog-to-Digital Coverter (ADC) Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__ADHCON,0x0600500,__READ_WRITE,__adhcon_bits);
__IO_REG8_BIT(__ADST,0x0600501,__READ_WRITE,__adst_bits);
__IO_REG8_BIT(__ADLCON,0x0600502,__READ_WRITE,__adlcon_bits);
__IO_REG16(__ADCR0,0x0600510,__READ);
__IO_REG16(__ADCR1,0x0600512,__READ);
__IO_REG16(__ADCR2,0x0600514,__READ);
__IO_REG16(__ADCR3,0x0600516,__READ);
__IO_REG16(__ADCR4,0x0600518,__READ);
__IO_REG16(__ADCR5,0x060051a,__READ);
__IO_REG16(__ADCR6,0x060051c,__READ);
__IO_REG16(__ADCR7,0x060051e,__READ);
__IO_REG16(__ADCR8,0x0600520,__READ);
__IO_REG16(__ADCR9,0x0600522,__READ);
__IO_REG16(__ADCR10,0x0600524,__READ);
__IO_REG16(__ADCR11,0x0600526,__READ);


/***************************************************************************
 **
 ** External Memory Controller (XMC) Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__BWCON,0x0600700,__READ_WRITE,__bwcon_bits);
__IO_REG8_BIT(__WICON,0x0600701,__READ_WRITE,__wicon_bits);
__IO_REG8_BIT(__OTCON,0x0600702,__READ_WRITE,__otcon_bits); 
__IO_REG8_BIT(__PWCON0,0x0600703,__READ_WRITE,__pwcon0_bits);
__IO_REG8_BIT(__PWCON1,0x0600704,__READ_WRITE,__pwcon1_bits);
__IO_REG8_BIT(__PWCON2,0x0600705,__READ_WRITE,__pwcon2_bits);

/***************************************************************************
 **
 ** CAN Controller Control Register Configuration (channel 0)
 **
 ***************************************************************************/
__IO_REG8_BIT(__CANC_0,0x0600a0e,__READ_WRITE,__canc_bits);
__IO_REG8_BIT(__CANI_0,0x0600a0f,__READ_WRITE,__cani_bits);
__IO_REG8_BIT(__NMES_0,0x0600a1e,__READ_WRITE,__nmes_bits);
__IO_REG8_BIT(__BTR0_0,0x0600a1f,__READ_WRITE,__btr0_bits);
__IO_REG8_BIT(__BTR1_0,0x0600a2e,__READ_WRITE,__btr1_bits);
__IO_REG8_BIT(__TIOC_0,0x0600a2f,__READ_WRITE,__tioc_bits);
__IO_REG8_BIT(__GMR0_0,0x0600a3e,__READ_WRITE,__gmr0_bits);
__IO_REG8_BIT(__GMR1_0,0x0600a3f,__READ_WRITE,__gmr1_bits);
__IO_REG8_BIT(__GMSK00_0,0x0600a4e,__READ_WRITE,__gmsk00_bits);
__IO_REG8_BIT(__GMSK01_0,0x0600a4f,__READ_WRITE,__gmsk01_bits);
__IO_REG8_BIT(__GMSK02_0,0x0600a5e,__READ_WRITE,__gmsk02_bits);
__IO_REG8_BIT(__GMSK03_0,0x0600a5f,__READ_WRITE,__gmsk03_bits);
__IO_REG8_BIT(__GMSK10_0,0x0600a6e,__READ_WRITE,__gmsk10_bits);
__IO_REG8_BIT(__GMSK11_0,0x0600a6f,__READ_WRITE,__gmsk11_bits);
__IO_REG8_BIT(__GMSK12_0,0x0600a7e,__READ_WRITE,__gmsk12_bits);
__IO_REG8_BIT(__GMSK13_0,0x0600a7f,__READ_WRITE,__gmsk13_bits);
__IO_REG8_BIT(__STBY_0,0x0600a8e,__READ_WRITE,__stdby_bits);
__IO_REG8_BIT(__CANC2_0,0x0600a8f,__READ_WRITE,__canc2_bits);
__IO_REG8_BIT(__TMN_0,0x0600a9e,__READ_WRITE,__tmn_bits);
__IO_REG8_BIT(__CANS_0,0x0600a9f,__READ_WRITE,__cans_bits);
__IO_REG8_BIT(__TEC_0,0x0600aae,__READ_WRITE,__tec_bits);
__IO_REG8_BIT(__REC_0,0x0600aaf,__READ_WRITE,__rec_bits);
__IO_REG8_BIT(__CANS2_0,0x0600abe,__READ_WRITE,__cans2_bits);
__IO_REG8_BIT(__BOCO_0,0x0600abf,__READ_WRITE,__boco_bits);
/***************************************************************************
 **
 ** CAN Controller Control Register Configuration (channel 1)
 **
 ***************************************************************************/
__IO_REG8_BIT(__CANC_1,0x0600b0e,__READ_WRITE,__canc_bits);
__IO_REG8_BIT(__CANI_1,0x0600b0f,__READ_WRITE,__cani_bits);
__IO_REG8_BIT(__NMES_1,0x0600b1e,__READ_WRITE,__nmes_bits);
__IO_REG8_BIT(__BTR0_1,0x0600b1f,__READ_WRITE,__btr0_bits);
__IO_REG8_BIT(__BTR1_1,0x0600b2e,__READ_WRITE,__btr1_bits);
__IO_REG8_BIT(__TIOC_1,0x0600b2f,__READ_WRITE,__tioc_bits);
__IO_REG8_BIT(__GMR0_1,0x0600b3e,__READ_WRITE,__gmr0_bits);
__IO_REG8_BIT(__GMR1_1,0x0600b3f,__READ_WRITE,__gmr1_bits);
__IO_REG8_BIT(__GMSK00_1,0x0600b4e,__READ_WRITE,__gmsk00_bits);
__IO_REG8_BIT(__GMSK01_1,0x0600b4f,__READ_WRITE,__gmsk01_bits);
__IO_REG8_BIT(__GMSK02_1,0x0600b5e,__READ_WRITE,__gmsk02_bits);
__IO_REG8_BIT(__GMSK03_1,0x0600b5f,__READ_WRITE,__gmsk03_bits);
__IO_REG8_BIT(__GMSK10_1,0x0600b6e,__READ_WRITE,__gmsk10_bits);
__IO_REG8_BIT(__GMSK11_1,0x0600b6f,__READ_WRITE,__gmsk11_bits);
__IO_REG8_BIT(__GMSK12_1,0x0600b7e,__READ_WRITE,__gmsk12_bits);
__IO_REG8_BIT(__GMSK13_1,0x0600b7f,__READ_WRITE,__gmsk13_bits);
__IO_REG8_BIT(__STBY_1,0x0600b8e,__READ_WRITE,__stdby_bits);
__IO_REG8_BIT(__CANC2_1,0x0600b8f,__READ_WRITE,__canc2_bits);
__IO_REG8_BIT(__TMN_1,0x0600b9e,__READ_WRITE,__tmn_bits);
__IO_REG8_BIT(__CANS_1,0x0600b9f,__READ_WRITE,__cans_bits);
__IO_REG8_BIT(__TEC_1,0x0600bae,__READ_WRITE,__tec_bits);
__IO_REG8_BIT(__REC_1,0x0600baf,__READ_WRITE,__rec_bits);
__IO_REG8_BIT(__CANS2_1,0x0600bbe,__READ_WRITE,__cans2_bits);
__IO_REG8_BIT(__BOCO_1,0x0600bbf,__READ_WRITE,__boco_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **   ML672300 interrupt sources
 **  
 ***************************************************************************/

#define ADINT    0    /* A/D conversion complete interrupt          */
#define CSINT0   1    /* Transfer complete interrupt req from CSI   */
#define CSINT1   2            
#define BGINT0   3    /* Baud rate interrupt request from ASI       */
#define TRINT0   4    /* Transmit ready interrupt from ASI          */
#define RVINT0   5    /* Receive ready interrupt  from ASI          */
#define BGINT1   6    /* Baud rate interrupt request from ASI       */
#define TRINT1   7    /* Transmit ready interrupt from ASI          */
#define RVINT1   8    /* Receive ready interrupt  from ASI          */
#define WDINT    9    /* Watchdog timer interrupt req from TBG      */
#define TMOV0   10    /* Timer overflow interrupt req from FTM      */
#define EVENT0  11    /* Capture event or compare match interrupt request from FTM */
#define TMOV1   12  
#define EVENT1  13 
#define TMOV2   14 
#define EVENT2  15 
#define TMOV3   16 
#define EVENT3  17 
#define TMOV4   18 
#define EVENT4  19 
#define TMOV5   20 
#define EVENT5  21 
/* Reserved: 22 */
#define WTINT   23
#define nEIR_0  24    /* Interrupt request from nEIR_n     pin*/
#define nEIR_1  25 
#define nEIR_2  26 
/* Reserved: 27-28 */
#define CANINT0 29 
#define CANINT1 30 

#endif    /* __ML672300_H */
