/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors S3C380D and S3F380D
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2000
 **                                
 **    $Revision: 1.4 $
 **                                
 ***************************************************************************/

#ifndef __S3X380D_H
#define __S3X380D_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    S3X380D SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Timer: control register  */
typedef struct {
  __REG16 t0en   :1;
  __REG16 t0csel :2; 
  __REG16 t0ien  :1; 
  __REG16 t1en   :1;
  __REG16 t1csel :2; 
  __REG16 t1ien  :1; 
  __REG16 t2en   :1;
  __REG16 t2csel :2; 
  __REG16 t2ien  :1;  
  __REG16        :4; 
} __tmcon_bits;


/* Timer: basic timer control register  */
typedef struct {
  __REG16 wtcnt  :1;
  __REG16 btcnt  :1; 
  __REG16 cssel  :2; 
  __REG16        :4;
  __REG16 wdten  :8; 
} __btcon_bits;

/* Timer: basic timer counter register  */
typedef struct {
  __REG16 cv     :8;
  __REG16        :8; 
} __btcnt_bits;

/* Timer: data register  */
typedef struct {
  __REG16 data   :16; 
} __tdata_bits;

/* Timer: count register  */
typedef struct {
  __REG16 cnt   :16; 
} __tcnt_bits;


/* RR: remocon receive control register  */
typedef struct {
  __REG16 pc      :2;
  __REG16 mpw     :2; 
  __REG16 ccsel   :2; 
  __REG16         :2;
  __REG16 fifoes  :1;
  __REG16 fifofs  :1;
  __REG16 rii     :1;  
  __REG16 fifofsdi:1; 
  __REG16 coi     :1;
  __REG16         :3;    
} __rrcr_bits;

/* RR: fifo data register  */
typedef struct {
  __REG16 data   :8;
  __REG16        :8; 
} __fifod_bits;

/* RT: clock control register  */
typedef struct {
  __REG16 ccclr :1;
  __REG16 cen   :1; 
  __REG16 ien   :1;
  __REG16       :13;    
} __rtcon_bits;


/* PLL:  clock control register  */
typedef struct {
  __REG16 fcpu     :3;
  __REG16 om       :1;
  __REG16 fosd     :3;
  __REG16          :9;
} __pllcon_bits;

/* SYSTEM: control register  */
typedef struct {
  __REG16 cw   :1;
  __REG16 sren :1;
  __REG16 ipf  :1;
  __REG16      :13;
} __syscon_bits;


/* Interrupt pending/mode/mask register  */
typedef struct {
  __REG16 posthsynci :1;
  __REG16 prehsynci  :1;
  __REG16 osdri      :1;
  __REG16 t0i        :1;
  __REG16 t1i        :1; 
  __REG16 t2i        :1;
  __REG16 rcsii      :1;
  __REG16 fifofi     :1;
  __REG16 rcovfi     :1; 
  __REG16 vsynci     :1;
  __REG16 bti        :1;
  __REG16 ei0        :1;
  __REG16 ei1        :1;
  __REG16 ei2        :1;
  __REG16 ei3        :1;  
  __REG16 rti        :1;    
} __intr_bits;


/* Interrupt priority register 0 */
typedef struct {
  __REG16 p0   :4;
  __REG16 p1   :4;
  __REG16 p2   :4;
  __REG16 p3   :4;
} __ipr0_bits;

/* Interrupt priority register 1 */
typedef struct {
  __REG16 p4   :4;
  __REG16 p5   :4;
  __REG16 p6   :4;
  __REG16 p7   :4;
} __ipr1_bits;

/* Interrupt priority register 2 */
typedef struct {
  __REG16 p8   :4;
  __REG16 p9   :4;
  __REG16 p10  :4;
  __REG16 p11  :4;
} __ipr2_bits;

/* Interrupt priority register 3 */
typedef struct {
  __REG16 p12   :4;
  __REG16 p13   :4;
  __REG16 p14   :4;
  __REG16 p15   :4;
} __ipr3_bits;


/* ADC: A/D conversion mode register  */
typedef struct {
  __REG16 data     :4; 
  __REG16 fadcmsel :1; 
  __REG16 adcsel   :2; 
  __REG16 adcc     :1; 
  __REG16 adctsel  :2; 
  __REG16          :6;
} __adcon_bits;


/* OSD: fade control register  */
typedef struct {
  __REG16 fladdr :6;
  __REG16 fdsel  :1; 
  __REG16 ffen   :1;
  __REG16 fraddr :4; 
  __REG16        :4;  
} __fadecon_bits;


/* OSD: background color register  */
typedef struct {
  __REG16 fb     :4;
  __REG16 afhtf  :1; 
  __REG16 irsc   :1;
  __REG16 itsht  :1; 
  __REG16        :1;
  __REG16 icsc   :3;
  __REG16 lmdpc  :5;  
} __osdbgd_bits;

/* OSD: counter register  */
typedef struct {
  __REG16 lcv    :6;
  __REG16        :2;
  __REG16 rcv    :4; 
  __REG16        :4;
} __osdcnt_bits;

/* OSD: CCD display control register  */
typedef struct {
  __REG16 ccdm     :1;
  __REG16 hcs      :2;
  __REG16 vcs      :2; 
  __REG16 rgbpol   :1;
  __REG16 htpol    :1;
  __REG16 hvsyncpol:1;
  __REG16 ic       :1;
  __REG16 vsyncien :1;
  __REG16 hsyncien :1;
  __REG16 rien     :1;
  __REG16          :1; 
  __REG16 lgen     :1;
  __REG16 gosden   :1; 
  __REG16 osdccdden:1;
} __osdcon_bits;


/* OSD: field control register  */
typedef struct {
  __REG16 efr        :4;
  __REG16 hsyncdpsel :1;
  __REG16 fd         :1; 
  __REG16            :10;
} __osdfld_bits;

/* OSD: palette color mode B register  */
typedef struct {
  __REG16 m0bl   :2;
  __REG16 m1bl   :2;
  __REG16 m2bl   :2;
  __REG16 m3bl   :2; 
  __REG16 m4bl   :2;
  __REG16 m5bl   :2;
  __REG16 m6bl   :2;
  __REG16 m7bl   :2;   
} __osdpltb_bits;

/* OSD: palette color mode G register  */
typedef struct {
  __REG16 m0gl   :2;
  __REG16 m1gl   :2;
  __REG16 m2gl   :2;
  __REG16 m3gl   :2; 
  __REG16 m4gl   :2;
  __REG16 m5gl   :2;
  __REG16 m6gl   :2;
  __REG16 m7gl   :2;   
} __osdpltg_bits;

/* OSD: palette color mode R register  */
typedef struct {
  __REG16 m0rl   :2;
  __REG16 m1rl   :2;
  __REG16 m2rl   :2;
  __REG16 m3rl   :2; 
  __REG16 m4rl   :2;
  __REG16 m5rl   :2;
  __REG16 m6rl   :2;
  __REG16 m7rl   :2;   
} __osdpltr_bits;


/* OSD:  margin control register  */
typedef struct {
  __REG16 irsc     :4;
  __REG16 tmdpc    :6;
  __REG16 vsyncbcr :5;
  __REG16          :1; 
} __osdvmgn_bits;


/* IO port:  port0 control register  */
typedef struct {
  __REG16 p00_pwm0 :2;
  __REG16 p01_pwm1 :2;
  __REG16 p02      :2;
  __REG16 p03      :2; 
  __REG16 p04      :2;
  __REG16 p05      :2;
  __REG16 p06      :2;
  __REG16 p07      :2;  
} __p0con_bits;

/* IO port:  port1 control register  */
typedef struct {
  __REG16 p10      :2;
  __REG16 p11      :2;
  __REG16 p12      :2;
  __REG16 p13      :2; 
  __REG16 p14_adc1 :2;
  __REG16 p15_adc2 :2;
  __REG16 p16_adc3 :2;
  __REG16 p17_adc4 :2;  
} __p1con_bits;


/* IO port:  port2 control register  */
typedef struct {
  __REG16 p20_int0 :2;
  __REG16 p21_int1 :2;
  __REG16 p22_int2 :2;
  __REG16 p23_int3 :2; 
  __REG16 p24      :2;
  __REG16 p25      :2;
  __REG16 p26      :2;
  __REG16 p27_osdht:2;  
} __p2con_bits;

/* IO port:  port3 control register  */
typedef struct {
  __REG16 p30      :2;
  __REG16          :14;
} __p3con_bits;


/* PWM: control register  */
typedef struct {
  __REG16 presc    :4;
  __REG16 cnten    :1;
  __REG16          :11;
} __pwmcon_bits;

/* PWM: data register  */
typedef struct {
  __REG16 evs      :6;
  __REG16 bcfvs    :8;
  __REG16          :2;
} __pwm_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  Basic and 16-bit timers registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__BTCON,0x30000,__READ_WRITE,__btcon_bits);
__IO_REG16_BIT(__BTCNT,0x30002,__READ,__btcnt_bits);
__IO_REG16_BIT(__T0DATA,0x30004,__READ_WRITE,__tdata_bits);
__IO_REG16_BIT(__T1DATA,0x30006,__READ_WRITE,__tdata_bits);
__IO_REG16_BIT(__T2DATA,0x30008,__READ_WRITE,__tdata_bits);
__IO_REG16_BIT(__TMCON,0x3000a,__READ_WRITE,__tmcon_bits);
__IO_REG16_BIT(__T0CNT,0x3000c,__READ,__tcnt_bits);
__IO_REG16_BIT(__T1CNT,0x3000e,__READ,__tcnt_bits);
__IO_REG16_BIT(__T2CNT,0x30010,__READ,__tcnt_bits);



/***************************************************************************
 **
 **  PWM registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__PWMCON,0x30012,__READ_WRITE,__pwmcon_bits);
__IO_REG16_BIT(__PWM0,0x30014,__READ_WRITE,__pwm_bits);
__IO_REG16_BIT(__PWM1,0x30016,__READ_WRITE,__pwm_bits);

/***************************************************************************
 **
 **  Remocon receive registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__RRCR,0x30018,__READ_WRITE,__rrcr_bits);
__IO_REG16_BIT(__FIFOD,0x3001a,__READ,__fifod_bits);

/***************************************************************************
 **
 **  Real time registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__RTCON,0x3001c,__READ_WRITE,__rtcon_bits);

/***************************************************************************
 **
 **  PLL registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__PLLCON,0x3001e,__READ_WRITE,__pllcon_bits);

/***************************************************************************
 **
 **  System registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__SYSCON,0x30020,__READ_WRITE,__syscon_bits);

/***************************************************************************
 **
 **  Interrupt registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__INTPR,0x30022,__READ_WRITE,__intr_bits);
__IO_REG16_BIT(__INTMD,0x30024,__READ_WRITE,__intr_bits);
__IO_REG16_BIT(__INTMK,0x30026,__READ_WRITE,__intr_bits);
__IO_REG16_BIT(__IPR0,0x30028,__READ_WRITE,__ipr0_bits);
__IO_REG16_BIT(__IPR1,0x3002a,__READ_WRITE,__ipr1_bits);
__IO_REG16_BIT(__IPR2,0x3002c,__READ_WRITE,__ipr2_bits);
__IO_REG16_BIT(__IPR3,0x3002e,__READ_WRITE,__ipr3_bits);

__IO_REG16(__IRQ0,0x30060,__READ_WRITE);
__IO_REG16(__IRQ1,0x30062,__READ_WRITE);
__IO_REG16(__IRQ2,0x30064,__READ_WRITE);
__IO_REG16(__IRQ3,0x30066,__READ_WRITE);
__IO_REG16(__IRQ4,0x30068,__READ_WRITE);
__IO_REG16(__IRQ5,0x3006a,__READ_WRITE);
__IO_REG16(__IRQ6,0x3006c,__READ_WRITE);
__IO_REG16(__IRQ7,0x3006e,__READ_WRITE);
__IO_REG16(__IRQ8,0x30070,__READ_WRITE);
__IO_REG16(__IRQ9,0x30072,__READ_WRITE);
__IO_REG16(__IRQ10,0x30074,__READ_WRITE);
__IO_REG16(__IRQ11,0x30076,__READ_WRITE);
__IO_REG16(__IRQ12,0x30078,__READ_WRITE);
__IO_REG16(__IRQ13,0x3007a,__READ_WRITE);
__IO_REG16(__IRQ14,0x3007c,__READ_WRITE);
__IO_REG16(__IRQ15,0x3007e,__READ_WRITE);

__IO_REG16(__FIQV0,0x30080,__READ_WRITE);
__IO_REG16(__FIQV1,0x30082,__READ_WRITE);
__IO_REG16(__FIQV2,0x30084,__READ_WRITE);
__IO_REG16(__FIQV3,0x30086,__READ_WRITE);
__IO_REG16(__FIQV4,0x30088,__READ_WRITE);
__IO_REG16(__FIQV5,0x3008a,__READ_WRITE);
__IO_REG16(__FIQV6,0x3008c,__READ_WRITE);
__IO_REG16(__FIQV7,0x3008e,__READ_WRITE);
__IO_REG16(__FIQV8,0x30090,__READ_WRITE);
__IO_REG16(__FIQV9,0x30092,__READ_WRITE);
__IO_REG16(__FIQV10,0x30094,__READ_WRITE);
__IO_REG16(__FIQV11,0x30096,__READ_WRITE);
__IO_REG16(__FIQV12,0x30098,__READ_WRITE);
__IO_REG16(__FIQV13,0x3009a,__READ_WRITE);
__IO_REG16(__FIQV14,0x3009c,__READ_WRITE);
__IO_REG16(__FIQV15,0x3009e,__READ_WRITE);

__IO_REG16(__IRQSR,0x300a8,__READ);
__IO_REG16(__FIQSR,0x300ac,__READ);



/***************************************************************************
 **
 **  I/O ports registers  
 **
 ***************************************************************************/
__IO_REG8(__P0,0x30030,__READ_WRITE);
__IO_REG8(__P1,0x30031,__READ_WRITE);
__IO_REG8(__P2,0x30032,__READ_WRITE);
__IO_REG8(__P3,0x30033,__READ_WRITE);

__IO_REG16_BIT(__P0CON,0x30034,__READ_WRITE,__p0con_bits);
__IO_REG16_BIT(__P1CON,0x30036,__READ_WRITE,__p1con_bits);
__IO_REG16_BIT(__P2CON,0x30038,__READ_WRITE,__p2con_bits);
__IO_REG16_BIT(__P3CON,0x3003a,__READ_WRITE,__p3con_bits);

/***************************************************************************
 **
 **  ADC registers  
 **
 ***************************************************************************/
__IO_REG16_BIT(__ADCON,0x3003c,__READ_WRITE,__adcon_bits);


/***************************************************************************
 **
 **  On screen display registers  
 **
 ***************************************************************************/
__IO_REG16(__OSGM3,0x30040,__READ_WRITE);
__IO_REG16(__OSGM2,0x30042,__READ_WRITE);
__IO_REG16(__OSGM1,0x30044,__READ_WRITE);
__IO_REG16(__OSGDATA,0x30046,__READ_WRITE);
__IO_REG16_BIT(__OSDPLTR,0x30048,__READ_WRITE,__osdpltr_bits);
__IO_REG16_BIT(__OSDPLTG,0x3004a,__READ_WRITE,__osdpltg_bits);
__IO_REG16_BIT(__OSDPLTB,0x3004c,__READ_WRITE,__osdpltb_bits);
__IO_REG16_BIT(__OSDFLD,0x3004e,__READ_WRITE,__osdfld_bits);
__IO_REG16_BIT(__OSDCON,0x30050,__READ_WRITE,__osdcon_bits);
__IO_REG16_BIT(__FADECON,0x30052,__READ_WRITE,__fadecon_bits);
__IO_REG16_BIT(__OSDBGD,0x30054,__READ_WRITE,__osdbgd_bits);
__IO_REG16_BIT(__OSDVMGN,0x30056,__READ_WRITE,__osdvmgn_bits);
__IO_REG16_BIT(__OSDCNT,0x30058,__READ_WRITE,__osdcnt_bits);







/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  S3X380D interrupt sources 
 **
 ***************************************************************************/
#define INT_POSTHSYNC   0  /* Post-H-sync interrupt (2st edge H-sync)*/
#define INT_PREHSYNC    1  /* Pre-H-sync interrupt (1st edge H-sync) */
#define INT_OSDR        2  /* OSD row interrupt                      */
#define INT_TIMER0      3  /* timer 0 interrupt                      */
#define INT_TIMER1      4  /* timer 1 interrupt                      */
#define INT_TIMER2      5  /* timer 2 interrupt                      */
#define INT_RCSI        6  /* Remote control signal input interrupt  */
#define INT_FIFOF       7  /* FIFO full interrupt               */
#define INT_RCOVF       8  /* Remocon counter overflow interrupt*/
#define INT_VSYNC       9  /* V-sync interrupt                  */
#define INT_BTIMER     10  /* Basic timer interrupt             */
#define INT_EXT0       11  /* External interrupt 0              */
#define INT_EXT1       12  /* External interrupt 1              */
#define INT_EXT2       13  /* External interrupt 2              */
#define INT_EXT3       14  /* External interrupt 3              */
#define INT_RT         15  /* Real timer interrupt              */
 


#endif    /* __S3X380D_H */
