/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Oki Semiconductors ML670100
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2000
 **                                
 **    $Revision: 1.7 $
 **                                
 ***************************************************************************/

#ifndef __ML670100_H
#define __ML670100_H


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
  __REG32 hlt  :1;
  __REG32      :31;
} __sbycon_bits;


/* Clock Control Register */
typedef struct {
  __REG32 ckm  :2;
  __REG32      :30;
} __ckcon_bits;

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
  __REG8 efiqs  :1;
  __REG8 efiqm  :1;
  __REG8        :5;
} __efiqcon_bits;

/* External IRQ Control Register */
typedef struct {
  __REG8 eir0  :1;
  __REG8 eir1  :1;
  __REG8 eir2  :1;
  __REG8 eir3  :1;
  __REG8 eir4  :1;
  __REG8 eir5  :1;
  __REG8 eir6  :1;
  __REG8 eir7  :1;
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

/* Interrupt Level Control Register 4*/
typedef struct {
  __REG8       :4;
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
  __REG8       :1;
  __REG8 ilr27 :3;
  __REG8       :1;
} __ilcon13_bits;

/* Interrupt Level Control Register 14*/
typedef struct {
  __REG8 ilr28 :3;
  __REG8       :1;
  __REG8 ilr29 :3;
  __REG8       :1;
} __ilcon14_bits;

/* Interrupt Level Control Register 15*/
typedef struct {
  __REG8 ilr30 :3;
  __REG8       :1;
  __REG8 ilr31 :3;
  __REG8       :1;
} __ilcon15_bits;

/* Time Base Generator Control Register */
typedef struct {
  __REG8 wdcks :2;
  __REG8       :1;
  __REG8 itm   :1;
  __REG8 iten  :1;
  __REG8       :3;
} __tbgcon_bits;

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
  __REG8 adstch  :3;
  __REG8         :1;
  __REG8 adchmod :2;
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
  __REG8 bwb3   :1;
  __REG8        :4;
} __bwcon_bits;


/* Wait Input control Register */
typedef struct {
  __REG8 wib0   :1;
  __REG8 wib1   :1;
  __REG8 wib2   :1;
  __REG8 wib3   :1;
  __REG8        :4;
} __wicon_bits;		


/* Off time control Register */
typedef struct {
  __REG8 otcn0  :2;
  __REG8 otcn1  :2;
  __REG8 otcn2  :2;
  __REG8 otcn3  :2;
} __otcon_bits;


/* Programmable Wait control Register */
typedef struct {
  __REG8 pwn0   :3;
  __REG8        :1;
  __REG8 pwn1   :3;
  __REG8        :1;
} __pwcon_bits;	


/* Bus access control Register */
typedef struct {
  __REG8 bas0   :1;
  __REG8        :3;
  __REG8 bas1   :1;
  __REG8        :3;
} __bacon_bits;


/* DRAM Bank 2 and 3 Control Register */
typedef struct {
  __REG8 be     :1;
  __REG8 dbas   :1;
  __REG8 amux   :2;
  __REG8        :4;
} __drcon_bits;

/* DRAM Bank 2 and 3 Access Timing Control Registers */
typedef struct {
  __REG8 rcd    :1;
  __REG8        :1;
  __REG8 rp     :1;
  __REG8        :5;
} __atcon_bits;


/* DRAM Bank 2 and 3 Programmable Wait Control Registers */
typedef struct {
  __REG8 cawa   :2;
  __REG8        :6;
} __dwcon_bits;


/* Refresh Timing Control Registers */
typedef struct {
  __REG8 rps    :3;
  __REG8        :1;
  __REG8 chs    :2;
  __REG8        :2;
} __rtcon_bits;


/* Refresh Control Registers */
typedef struct {
  __REG8 cbrr   :2;
  __REG8 rsr    :1;
  __REG8        :1;
  __REG8 clks   :3;
  __REG8        :1;
} __rfcon_bits;


/* Cycle Trace Control Registers */
typedef struct {
  __REG8 ct     :1;
  __REG8        :7;
} __ctcon_bits;		
	
#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/
/***************************************************************************
 **
 **  CPU Control Unit Control Registers
 **
 ***************************************************************************/
__IO_REG32_BIT(__SBYCON,0x04000000,__WRITE,__sbycon_bits);
__IO_REG32_BIT(__CKCON,0x04000004,__READ_WRITE,__ckcon_bits);
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
__IO_REG8(__ILCON3,0x0600013,__READ_WRITE);
__IO_REG8_BIT(__ILCON4,0x0600014,__READ_WRITE,__ilcon4_bits);
__IO_REG8_BIT(__ILCON5,0x0600015,__READ_WRITE,__ilcon5_bits);
__IO_REG8_BIT(__ILCON6,0x0600016,__READ_WRITE,__ilcon6_bits);
__IO_REG8_BIT(__ILCON7,0x0600017,__READ_WRITE,__ilcon7_bits);
__IO_REG8_BIT(__ILCON8,0x0600018,__READ_WRITE,__ilcon8_bits);
__IO_REG8_BIT(__ILCON9,0x0600019,__READ_WRITE,__ilcon9_bits);
__IO_REG8_BIT(__ILCON10,0x060001a,__READ_WRITE,__ilcon10_bits);
__IO_REG8(__ILCON11,0x060001b,__READ_WRITE);
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

__IO_REG8(__PI0,0x0600610,__READ);
__IO_REG8(__PI1,0x0600611,__READ);
__IO_REG8(__PI2,0x0600612,__READ);
__IO_REG8(__PI3,0x0600613,__READ);
__IO_REG8(__PI4,0x0600614,__READ);
__IO_REG8(__PI5,0x0600615,__READ);
__IO_REG8(__PI6,0x0600616,__READ);
__IO_REG8(__PI7,0x0600617,__READ);
__IO_REG8(__PI8,0x0600618,__READ);


__IO_REG8(__PM0,0x0600620,__READ_WRITE);
__IO_REG8(__PM1,0x0600621,__READ_WRITE);
__IO_REG8(__PM2,0x0600622,__READ_WRITE);
__IO_REG8(__PM3,0x0600623,__READ_WRITE);
__IO_REG8(__PM4,0x0600624,__READ_WRITE);
__IO_REG8(__PM5,0x0600625,__READ_WRITE);
__IO_REG8(__PM6,0x0600626,__READ_WRITE);
__IO_REG8(__PM7,0x0600627,__READ_WRITE);
__IO_REG8(__PM8,0x0600628,__READ_WRITE);


__IO_REG8(__PFS0,0x0600630,__READ_WRITE);
__IO_REG8(__PFS1,0x0600631,__READ_WRITE);
__IO_REG8(__PFS2,0x0600632,__READ_WRITE);
__IO_REG8(__PFS3,0x0600633,__READ_WRITE);
__IO_REG8(__PFS4,0x0600634,__READ_WRITE);
__IO_REG8(__PFS5,0x0600635,__READ_WRITE);
__IO_REG8(__PFS6,0x0600636,__READ_WRITE);
__IO_REG8(__PFS7,0x0600637,__READ_WRITE);


/***************************************************************************
 **
 ** Time Base Generator (TBG) Control Registers
 **
 ***************************************************************************/
__IO_REG8(__WDTCON,0x0600200,__WRITE);
__IO_REG8_BIT(__TBGCON,0x0600201,__READ_WRITE,__tbgcon_bits);

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
__IO_REG8(__ASBUF,0x0600300,__READ_WRITE);
__IO_REG8_BIT(__ASIST,0x0600301,__READ_WRITE,__asist_bits);
__IO_REG8_BIT(__ASICON,0x0600302,__READ_WRITE,__asicon_bits);
__IO_REG8_BIT(__ASBCON,0x0600303,__READ_WRITE,__asbcon_bits);
__IO_REG8(__ASBTMC,0x0600304,__READ_WRITE);
__IO_REG8(__ASBTMR,0x0600305,__READ_WRITE);
__IO_REG8_BIT(__ASTSCON,0x0600306,__READ_WRITE,__astscon_bits);

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
__IO_REG8(__ADCR0,0x0600504,__READ);
__IO_REG8(__ADCR1,0x0600505,__READ);
__IO_REG8(__ADCR2,0x0600506,__READ);
__IO_REG8(__ADCR3,0x0600507,__READ);


/***************************************************************************
 **
 ** External Memory Controller (XMC) Control Registers
 **
 ***************************************************************************/
__IO_REG8_BIT(__BWCON,0x0600700,__READ_WRITE,__bwcon_bits);
__IO_REG8_BIT(__WICON,0x0600701,__READ_WRITE,__wicon_bits);
__IO_REG8_BIT(__OTCON,0x0600702,__READ_WRITE,__otcon_bits); 
__IO_REG8_BIT(__PWCON,0x0600703,__READ_WRITE,__pwcon_bits);
__IO_REG8_BIT(__BACON,0x0600704,__READ_WRITE,__bacon_bits);
__IO_REG8_BIT(__DR2CON,0x0600705,__READ_WRITE,__drcon_bits);
__IO_REG8_BIT(__AT2CON,0x0600706,__READ_WRITE,__atcon_bits); 
__IO_REG8_BIT(__DW2CON,0x0600707,__READ_WRITE,__dwcon_bits); 
__IO_REG8_BIT(__DR3CON,0x0600708,__READ_WRITE,__drcon_bits); 
__IO_REG8_BIT(__AT3CON,0x0600709,__READ_WRITE,__atcon_bits);
__IO_REG8_BIT(__DW3CON,0x060070a,__READ_WRITE,__dwcon_bits); 
__IO_REG8(__RFTCN,0x060070b,__READ_WRITE);   
__IO_REG8(__RCCON,0x060070c,__READ_WRITE); 
__IO_REG8_BIT(__RTCON,0x060070d,__READ_WRITE,__rtcon_bits); 
__IO_REG8_BIT(__RFCON,0x060070e,__READ_WRITE,__rfcon_bits); 
__IO_REG8_BIT(__CTCON,0x060070f,__READ_WRITE,__ctcon_bits); 


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **   ML670100 interrupt sources
 **  
 ***************************************************************************/

#define ADINT    0    /* A/D conversion complete interrupt          */
#define CSINT0   1    /* Transfer complete interrupt req from CSI   */
#define CSINT1   2            
#define BGINT    3    /* Baud rate interrupt request from ASI       */
#define TRINT    4    /* Transmit ready interrupt from ASI          */
#define RVINT    5    /* Receive ready interrupt  from ASI          */
/* Reserved: 6-8 */
#define WDINT    9    /* Watchdog timer interrupt req from TBG      */
#define FTMOV0  10    /* Timer overflow interrupt req from FTM      */
#define EVENT0  11    /* Capture event or compare match interrupt request from FTM */
#define FTMOV1  12  
#define EVENT1  13 
#define FTMOV2  14 
#define EVENT2  15 
#define FTMOV3  16 
#define EVENT3  17 
#define FTMOV4  18 
#define EVENT4  19 
#define FTMOV5  20 
#define EVENT5  21 
/* Reserved: 22-23 */
#define nEIR_0  24    /* Interrupt request from nEIR_n     pin*/
#define nEIR_1  25 
#define nEIR_2  26 
#define nEIR_3  27 
#define nEIR_4  28 
#define nEIR_5  29 
#define nEIR_6  30 
#define nEIR_7  31 

#endif    /* __ML670100_H */
