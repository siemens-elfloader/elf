/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Sharp Semiconductors LH77790B
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2000
 **                                
 **    $Revision: 1.6 $
 **                                
 ***************************************************************************/

#ifndef __LH77790B_H
#define __LH77790B_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    LH77790B SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* CCR: Cache Control Register  */
typedef struct {
  __REG8 e  :1; /* Cache mode bit      */
  __REG8 s  :1; /* SRAM mode bit       */
  __REG8 f  :1; /* Flush mode bit      */
  __REG8 i  :1; /* Invalidate mode bit */
  __REG8    :4; /* Reserved */
} __ccr_bits;

/* LSRC: Local SRAM Control Register */
typedef struct {
  __REG8 e  :1; /* Local SRAM Enable Bit */
  __REG8 l  :1; /* Local SRAM Location   */
  __REG8    :6; /* Reserved */
} __lscr_bits;

/*- Memory Segment Registers -*/

/* start register */
typedef struct {
  __REG32       :10; 
  __REG32 start :22;  /* start address */
} __start_bits;

/* stop register */
typedef struct {
  __REG32       :10; 
  __REG32 stop  :22;  /* stop address  */
} __stop_bits;

/* Segment Descriptor Register */
typedef struct {
  __REG16 bsel  :8; /* bank select      */
  __REG16 hw    :1; /* half-word mode   */
  __REG16       :1; /* reserved         */
  __REG16 c     :1; /* cacheability     */
  __REG16 upr   :2; /* user privilege   */
  __REG16 spr   :2; /* system privilege */ 
  __REG16       :1; /* reserved         */
} __sdr_bits;

/*- Bank configuration registers -*/

/* Bank Control Register 0-5 */
typedef struct {
  __REG16 ece   :12; /* external chip enable           */
  __REG16 wait  :3;  /* wait cycles for external SRAM  */
  __REG16 ms    :1;  /* external SRAM bus size         */
} __bcr05_bits;

/* Bank Control Register 6a and 7a */
typedef struct {
  __REG16 ecas  :12; /* external cas controls          */
  __REG16 fcas  :3;  
  __REG16 ms    :1;  /* external DRAM bus size         */
} __bcra_bits;

/* Bank Control Register 6b and 7b */
typedef struct {
  __REG8 pm    :1;  /* DRAM page mode           */
  __REG8 bs    :3;  /* DRAM bank size           */
  __REG8 r     :1;  /* refresh archive          */
  __REG8 bcas  :2;  /* burst transfer CAS width */
  __REG8       :1;  /* reserved                 */
} __bcrb_bits;

/* DRAM Refresh Register */
typedef struct {
  __REG16 ddr  :1;  /* 16-bit refresh value */
  __REG16      :15;
} __ddr_bits;

/*- CPMU Registers   -*/

/* Peripheral Clock Select Register */
typedef struct {
  __REG16 uc0s  :1; /* UART 0 clock source */
  __REG16 uc1s  :1; /*      1              */
  __REG16 uc2s  :1; /*      2              */
  __REG16 ct0cs :1; /* Counter/timer0 clock source */
  __REG16 ct1cs :1; /*              1              */
  __REG16 ct2cs :1; /*              2              */
  __REG16 lcdce :1; /* LCD controller clock enable */
  __REG16 pwmce :1; /* PWM   clock enable          */
  __REG16 sirce :1; /* Serial infrared clock enable*/
  __REG16       :7; 
} __pcsr_bits;	

/* UART0 Clock Control Register */
typedef struct {
  __REG16 u1ccr  :9; /* UART0 clock divisor */
  __REG16        :7;
} __u0ccr_bits;

/* UART1 Clock Control Register */
typedef struct {
  __REG16 u1ccr  :9; /* UART1 clock divisor */
  __REG16        :7;
} __u1ccr_bits;

/* UART2 Clock Control Register */
typedef struct {
  __REG16 u1ccr  :9; /* UART2 clock divisor */
  __REG16        :7;
} __u2ccr_bits;

/* Counter/Timer 0 Clock Control Register */
typedef struct {
  __REG16 ct0ccr  :9; /* C/T0 clock divisor */
  __REG16         :7;
} __ct0ccr_bits;

/* Counter/Timer 1 Clock Control Register */
typedef struct {
  __REG16 ct1ccr  :9; /* C/T1 clock divisor */
  __REG16         :7;
} __ct1ccr_bits;

/* Counter/Timer 2 Clock Control Register */
typedef struct {
  __REG16 ct2ccr  :9; /* C/T2 clock divisor */
  __REG16         :7;
} __ct2ccr_bits;


/* Core Clock Control Register */
typedef struct {
  __REG16 cccr    :9; /* core clock divisor */
  __REG16         :7;
} __cccr_bits;

/*- USART registers  -*/

/* RBR:receive buffer, THR:transmit holding, DLL: divisor latch, SCR:scratch pad registers */
typedef struct {
  __REG8 d0   :1; 
  __REG8 d1   :1;
  __REG8 d2   :1; 
  __REG8 d3   :1;
  __REG8 d4   :1; 
  __REG8 d5   :1;
  __REG8 d6   :1; 
  __REG8 d7   :1;
} __rtds_bits;

/* DLM divisor latch register, IER interrupt enable register */
typedef union {
  //__IERx
  struct {
    __REG8 erbfi  :1; /* enable receiver buffer interrupt */ 
    __REG8 etbei  :1; /* enable THR empty interrupt       */
    __REG8 elsi   :1; /* enable receiver status interrupt */
    __REG8 edssi  :1; /* enable modem status interrupt    */ 
    __REG8        :1; 
    __REG8        :1;
    __REG8        :1; 
    __REG8        :1;
  };
  //__DLMx
  struct {
    __REG8 d8   :1; 
    __REG8 d9   :1;
    __REG8 d10  :1; 
    __REG8 d11  :1;
    __REG8 d12  :1; 
    __REG8 d13  :1;
    __REG8 d14  :1; 
    __REG8 d15  :1;
  };
} __ier_dlm_bits;


/* IIR interrupt identification register */
typedef struct {
  __REG8 ip   :1; /* interrupt pending    */ 
  __REG8 id   :1; /* interrupt identifier */
  __REG8      :6; 
} __iir_bits;

/* LCR line control register */
typedef struct {
  __REG8 lcr  :1; /* line control     */ 
  __REG8      :1; 
  __REG8 cl   :1; /* character length */
  __REG8 stb  :1; /* stop bits        */
  __REG8 pen  :1; /* parity enable    */
  __REG8 ptyp :1; /* parity type      */
  __REG8 sb   :1; /* set break        */
  __REG8 dlab :1;    
} __lcr_bits;

/* MCR modem control register */
typedef struct {
  __REG8 dtr  :1;
  __REG8 rts  :1; 
  __REG8 out1 :1; 
  __REG8 out2 :1; 
  __REG8 loop :1; 
  __REG8      :1; 
  __REG8      :1; 
  __REG8      :1;    
} __mcr_bits;

/* LSR line status register */
typedef struct {
  __REG8 dr   :1; /* data ready      */
  __REG8 oe   :1; /* overrun error   */ 
  __REG8 pe   :1; /* parity error    */
  __REG8 fe   :1; /* frame error     */ 
  __REG8 bi   :1; /* break interrupt */
  __REG8 thre :1; /* THR empty       */
  __REG8 temt :1; /* transmit empty  */
  __REG8      :1;    
} __lsr_bits;

/* MSR modem status register */
typedef struct {
  __REG8 dcts  :1; /* delta CTS           */
  __REG8 ddsr  :1; /* delta DSR           */
  __REG8 teri  :1; /* trailing edge ring indicator */
  __REG8 ddcd  :1; /* delta DCD           */
  __REG8 cts   :1; /* clear to send       */
  __REG8 dsr   :1; /* data set ready      */
  __REG8 ri    :1; /* ring indicator      */
  __REG8 dcd   :1; /* data carrier detect */   
} __msr_bits;

/*- Serial Infrared Interface  -*/

/* SIR: control register */
typedef struct {
  __REG8 mode  :2; /* UART2 operation mode */
  __REG8 rxp   :1; /* Rx polarity */
  __REG8 txp   :1; /* Tx polarity */
  __REG8       :4; /* reserved    */
} __sirctlr_bits;	

/*- PWM: Pulse Width Modulator registers -*/

/* PWM: clock divider registers */
typedef struct {
  __REG8 dv    :6; /* divide value */ 
  __REG8       :2;
} __pwmdiv_bits;	

/* PWM: terminal count registers */
typedef struct {
  __REG8 tc    :8; /* terminal count */ 
} __pwmtc_bits;	

/* PWM2: terminal count registers */
typedef struct {
  __REG16 tc   :16; /* terminal count */ 
} __pwm2tc_bits;	

/* PWM: duty cycle registers */
typedef struct {
  __REG8 dc    :8; /* duty cycle    */ 
} __pwmdc_bits;	

/* PWM2: duty cycle registers */
typedef struct {
  __REG16 dc   :16; /* duty cycle    */ 
} __pwm2dc_bits;	

/* PWM: output invert registers */
typedef struct {
  __REG8 inv    :1; /* invert PWM output */ 
  __REG8        :7; /* reserved */ 
} __pwminv_bits;	

/* PWM: enable registers */
typedef struct {
  __REG8 enb    :1; /* enable PWM */ 
  __REG8        :7; /* reserved */ 
} __pwmenb_bits;	

/* PWM: synchronous registers */
typedef struct {
  __REG8 sync    :1; /* PWM synchronous mode */ 
  __REG8         :7; /* reserved */ 
} __pwmsync_bits;	


/* LCD: mode register */
typedef struct {
  __REG8 lcda    :1; /* controls the activation of the LCD controller   */
  __REG8 lcdc    :1; /* controls the state of the LCDCNTL output signal */
  __REG8 xsize   :1; /* 4-bit or 8bit data transfer */
  __REG8 gray    :1; /* binary/gray display mode    */
  __REG8 or_bit  :1; /* should be or, but or is an EC++ keyword */
  __REG8 scan    :1; /* single/dual scan mode       */
  __REG8 rev     :1; /* normal/reverse display mode */
  __REG8 disp    :1; 
} __lcdmode_bits;	

/* LCD: line display byte count register */
typedef struct {
  __REG8 bc    :8; 
} __lcdbc_bits;	

/* LCD: line pulse width register */
typedef struct {
  __REG8 cp1w    :8; 
} __lcdcp1w_bits;	

/* LCD: dutya cycle register */
typedef struct {
  __REG8 cp1w    :8; 
} __lcddutya_bits;	

/* LCD: dutyb cycle register */
typedef struct {
  __REG8 duty    :2;
  __REG8         :6;
} __lcddutyb_bits;	

/* LCD: screen 1 frame buffer start address register (32 bits)*/
typedef struct {
  __REG8 adr :8; 
} __lcdsadr1a_bits;	
typedef struct {
  __REG8 adr :8; 
} __lcdsadr1b_bits;	
typedef struct {
  __REG8 adr :8; 
} __lcdsadr1c_bits;	
typedef struct {
  __REG8 adr :8; 
} __lcdsadr1d_bits;	

/* LCD: screen 2 frame buffer start address register (32 bits)*/
typedef struct {
  __REG8 adr  :8; 
} __lcdsadr2a_bits;	
typedef struct {
  __REG8 adr  :8; 
} __lcdsadr2b_bits;	
typedef struct {
  __REG8 adr  :8; 
} __lcdsadr2c_bits;	
typedef struct {
  __REG8 adr  :8; 
} __lcdsadr2d_bits;	

/* LCD: Screen 1 vertical line count registers */
typedef struct {
  __REG8 vlc  :8; /* number of vertical lines */ 
} __lcdvlc1a_bits;	
typedef struct {
  __REG8 vlc  :2;
  __REG8      :6;
} __lcdvlc1b_bits;	

/* LCD: virtual display delta register */
typedef struct {
  __REG8 vdlt  :8; 
} __lcdvdlt_bits;	

/* LCD: gray1 shade register */
typedef struct {
  __REG8 gray1 :8; 
} __lcdgray1_bits;
	
/* LCD: gray2 shade register */
typedef struct {
  __REG8 gray2  :8; 
} __lcdgray2_bits;	

/* LCD: clock frequency divider */
typedef struct {
  __REG8 clkdiv :8; 
} __lcdclkdiv_bits;	

/* LCD: MCLK width */
typedef struct {
  __REG8 mclkw :8; 
} __lcdmclkwa_bits;
typedef struct {
  __REG8 mclkw :8; 
} __lcdmclkwb_bits;	

/* LCD: bit control  */
typedef struct {
  __REG8 lbc :1; /* display frame buffer using format #0/#1 */
  __REG8     :7;
} __lcdbitctl_bits;


/* CT: Count registers */
typedef struct {
  __REG8 cv    :8; 
} __ctcntr_bits;	

/* CT: Control word registers */
typedef struct {
  __REG8 bcd    :1;
  __REG8 m0     :1; /* counter mode   */
  __REG8 m1     :1;
  __REG8 m2     :1;
  __REG8 rw0    :1; /* read/write     */
  __REG8 rw1    :1;
  __REG8 sc0    :1; /* select counter */
  __REG8 sc1    :1; 
} __ctcwr_bits;	

/* WD: control register */
typedef struct {
  __REG8 en     :1;
  __REG8 rsp    :2; /* time out response selection */
  __REG8 frz    :1; /* freeze enable/disable       */
  __REG8 top    :3; /* time-out period select      */
  __REG8        :1;
} __wdctlr_bits;	

/* WD: counter register */
typedef struct {
  __REG32 cv     :32;
} __wdcntr_bits;	

/*PPI: control register */
typedef struct {
  __REG8 clio  :1;
  __REG8 bio   :1;
  __REG8 bm    :1;
  __REG8 chio  :1;
  __REG8 aio   :1;
  __REG8 aml   :1;
  __REG8 amh   :1;
  __REG8       :1;
} __ppictlr_bits;	

/*- interrupt controller registers -*/

/* interrupt configuration register 0 */
typedef struct {
  __REG16 hl_0  :1; /* active LOW/HIGH      */
  __REG16 el_0  :1; /* level/edge triggered */
  __REG16 hl_1  :1;
  __REG16 el_1  :1;
  __REG16 hl_2  :1;
  __REG16 el_2  :1;
  __REG16 hl_3  :1;
  __REG16 el_3  :1;
  __REG16 hl_4  :1;
  __REG16 el_4  :1;
  __REG16 hl_5  :1;
  __REG16 el_5  :1;
  __REG16       :4;
} __icr0_bits;
	
/* interrupt configuration register 1 */
typedef struct {
  __REG8 hl_0  :1;
  __REG8 hl_1  :1;
  __REG8 hl_2  :1;
  __REG8       :5;
} __icr1_bits;	

/* interrupt clear register */
typedef struct {
  __REG16 ch0  :1; /* clear channel i edge level interrupt */
  __REG16 ch1  :1;
  __REG16 ch2  :1;
  __REG16 ch3  :1;
  __REG16 ch4  :1;
  __REG16 ch5  :1;
  __REG16 ch6  :1;
  __REG16 ch7  :1;
  __REG16 ch8  :1;
  __REG16 ch12 :1;
  __REG16      :6;
} __iclr_bits;	

/* IRQSR/IRQER register */
typedef struct {
  __REG16 ch0  :1; 
  __REG16 ch1  :1; 
  __REG16 ch2  :1;
  __REG16 ch3  :1;
  __REG16 ch4  :1;
  __REG16 ch5  :1;
  __REG16 ch6  :1;
  __REG16 ch7  :1;
  __REG16 ch8  :1;
  __REG16 ch9  :1;
  __REG16 ch10 :1;
  __REG16 ch11 :1;
  __REG16      :4;
} __irqr_bits;	
	
/* FIQER register */
typedef struct {
  __REG16 ch0  :1; 
  __REG16 ch1  :1; 
  __REG16 ch2  :1;
  __REG16 ch3  :1;
  __REG16 ch4  :1;
  __REG16 ch5  :1;
  __REG16 ch6  :1;
  __REG16 ch7  :1;
  __REG16 ch8  :1;
  __REG16 ch9  :1;
  __REG16 ch10 :1;
  __REG16 ch11 :1;
  __REG16      :4;
} __fiqer_bits;	
	
	
/* FIQ status register*/
typedef struct {
  __REG16 ch0  :1; 
  __REG16 ch1  :1; 
  __REG16 ch2  :1;
  __REG16 ch3  :1;
  __REG16 ch4  :1;
  __REG16 ch5  :1;
  __REG16 ch6  :1;
  __REG16 ch7  :1;
  __REG16 ch8  :1;
  __REG16 ch9  :1;
  __REG16 ch10 :1;
  __REG16 ch11 :1;
  __REG16 ch12 :1;
  __REG16      :3;
} __fiqsr_bits;		

/* interrupt polling register*/
typedef struct {
  __REG16 ch0  :1; 
  __REG16 ch1  :1; 
  __REG16 ch2  :1;
  __REG16 ch3  :1;
  __REG16 ch4  :1;
  __REG16 ch5  :1;
  __REG16 ch6  :1;
  __REG16 ch7  :1;
  __REG16 ch8  :1;
  __REG16 ch9  :1;
  __REG16 ch10 :1;
  __REG16 ch11 :1;
  __REG16 ch12 :1;
  __REG16      :3;
} __ipr_bits;		


/* in/output configuration register */	
typedef struct {
  __REG16 pu0  :1; 
  __REG16 pu1  :1; 
  __REG16 pu2  :1;
  __REG16 pu3  :1;
  __REG16 pu4  :1;
  __REG16 pu5  :1;
  __REG16 pu6  :1;
  __REG16 pu7  :1;
  __REG16 pu8  :1;
  __REG16 ct0g :2;
  __REG16 ct1g :2;
  __REG16 ct2g :2;
  __REG16      :1;
} __iocr_bits;
	

/* identification register */	
typedef struct {
  __REG16 prod :6; 
  __REG16 mem  :6; 
  __REG16 t    :1;
  __REG16 fam  :3;
} __idr_bits;		


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  Cache register(s)  
 **
 ***************************************************************************/

__IO_REG8_BIT(__CCR,0x0ffffa400,__READ_WRITE,__ccr_bits);

/***************************************************************************
 **
 **  Local SRAM register(s)  
 **
 ***************************************************************************/

__IO_REG8_BIT(__LSCR,0xffffa404,__READ_WRITE,__lscr_bits);

/***************************************************************************
 **
 **  Memory Segment registers  
 **
 ***************************************************************************/

__IO_REG32_BIT(__START0,0xffffa000,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__START1,0xffffa004,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__START2,0xffffa008,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__START3,0xffffa00c,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__START4,0xffffa010,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__START5,0xffffa014,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__START6,0xffffa018,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__START7,0xffffa01c,__READ_WRITE,__start_bits);
__IO_REG32_BIT(__STOP0,0xffffa020,__READ_WRITE,__stop_bits);
__IO_REG32_BIT(__STOP1,0xffffa024,__READ_WRITE,__stop_bits);
__IO_REG32_BIT(__STOP2,0xffffa028,__READ_WRITE,__stop_bits);
__IO_REG32_BIT(__STOP3,0xffffa02c,__READ_WRITE,__stop_bits);
__IO_REG32_BIT(__STOP4,0xffffa030,__READ_WRITE,__stop_bits);
__IO_REG32_BIT(__STOP5,0xffffa034,__READ_WRITE,__stop_bits);
__IO_REG32_BIT(__STOP6,0xffffa038,__READ_WRITE,__stop_bits);
__IO_REG32_BIT(__STOP7,0xffffa03c,__READ_WRITE,__stop_bits);
__IO_REG16_BIT(__SDR0,0xffffa040,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR1,0xffffa044,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR2,0xffffa048,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR3,0xffffa04c,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR4,0xffffa050,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR5,0xffffa054,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR6,0xffffa058,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR7,0xffffa05c,__READ_WRITE,__sdr_bits);
__IO_REG16_BIT(__SDR8,0xffffa060,__READ_WRITE,__sdr_bits);


/***************************************************************************
 **
 **  Bank Configuration Register 
 **
 ***************************************************************************/
__IO_REG16_BIT(__BCR0,0xffffa100,__READ_WRITE,__bcr05_bits);
__IO_REG16_BIT(__BCR1,0xffffa104,__READ_WRITE,__bcr05_bits);
__IO_REG16_BIT(__BCR2,0xffffa108,__READ_WRITE,__bcr05_bits);
__IO_REG16_BIT(__BCR3,0xffffa10c,__READ_WRITE,__bcr05_bits);
__IO_REG16_BIT(__BCR4,0xffffa110,__READ_WRITE,__bcr05_bits);
__IO_REG16_BIT(__BCR5,0xffffa114,__READ_WRITE,__bcr05_bits);
__IO_REG16_BIT(__BCR6a,0xffffa118,__READ_WRITE,__bcra_bits);
__IO_REG16_BIT(__BCR7a,0xffffa11c,__READ_WRITE,__bcra_bits);
__IO_REG8_BIT(__BCR6b,0xffffa120,__READ_WRITE,__bcrb_bits);
__IO_REG8_BIT(__BCR7b,0xffffa124,__READ_WRITE,__bcrb_bits);
__IO_REG16_BIT(__DDR,0xffffa128,__READ_WRITE,__ddr_bits);

/***************************************************************************
 **
 **   CPMU Registers
 **
 ***************************************************************************/
__IO_REG16_BIT(__PCSR,0xffffac04,__READ_WRITE,__pcsr_bits);
__IO_REG16_BIT(__U0CCR,0xffffac08,__READ_WRITE,__u0ccr_bits);
__IO_REG16_BIT(__U1CCR,0xffffac0c,__READ_WRITE,__u1ccr_bits);
__IO_REG16_BIT(__U2CCR,0xffffac10,__READ_WRITE,__u2ccr_bits);
__IO_REG16_BIT(__CT0CCR,0xffffac18,__READ_WRITE,__ct0ccr_bits);
__IO_REG16_BIT(__CT1CCR,0xffffac1c,__READ_WRITE,__ct1ccr_bits);
__IO_REG16_BIT(__CT2CCR,0xffffac20,__READ_WRITE,__ct2ccr_bits);
__IO_REG16_BIT(__CCCR,0xffffac28,__READ_WRITE,__cccr_bits);


/***************************************************************************
 **
 **   UART0 Registers
 **
 ***************************************************************************/

__IO_REG8_BIT(__RBR0,0xffff0000,__READ_WRITE,__rtds_bits);
#define __THR0      __RBR0
#define __THR0_bit  __RBR0_bit
#define __DLL0      __RBR0
#define __DLL0_bit  __RBR0_bit

__IO_REG8_BIT(__IER0,0xffff0004,__READ_WRITE,__ier_dlm_bits);
#define __DLM0     __IER0
#define __DLM0_bit __IER0_bit

__IO_REG8_BIT(__IIR0,0xffff0008,__READ,__iir_bits);
__IO_REG8_BIT(__LCR0,0xffff000c,__READ_WRITE,__lcr_bits);
__IO_REG8_BIT(__MCR0,0xffff0010,__READ_WRITE,__mcr_bits);
__IO_REG8_BIT(__LSR0,0xffff0014,__READ,__lsr_bits);
__IO_REG8_BIT(__MSR0,0xffff0018,__READ_WRITE,__msr_bits);
__IO_REG8_BIT(__SCR0,0xffff001c,__READ_WRITE,__rtds_bits);


/***************************************************************************
 **
 **   UART1 Registers
 **
 ***************************************************************************/

__IO_REG8_BIT(__RBR1,0xffff0400,__READ_WRITE,__rtds_bits);
#define __THR1      __RBR1
#define __THR1_bit  __RBR1_bit
#define __DLL1      __RBR1
#define __DLL1_bit  __RBR1_bit

__IO_REG8_BIT(__IER1,0xffff0404,__READ_WRITE,__ier_dlm_bits);
#define __DLM1     __IER1
#define __DLM1_bit __IER1_bit

__IO_REG8_BIT(__IIR1,0xffff0408,__READ,__iir_bits);
__IO_REG8_BIT(__LCR1,0xffff040c,__READ_WRITE,__lcr_bits);
__IO_REG8_BIT(__MCR1,0xffff0410,__READ_WRITE,__mcr_bits);
__IO_REG8_BIT(__LSR1,0xffff0414,__READ,__lsr_bits);
__IO_REG8_BIT(__MSR1,0xffff0418,__READ_WRITE,__msr_bits);
__IO_REG8_BIT(__SCR1,0xffff041c,__READ_WRITE,__rtds_bits);


/***************************************************************************
 **
 **   UART2 Registers
 **
 ***************************************************************************/

__IO_REG8_BIT(__RBR2,0xffff0800,__READ_WRITE,__rtds_bits);
#define __THR2      __RBR2
#define __THR2_bit  __RBR2_bit
#define __DLL2      __RBR2
#define __DLL2_bit  __RBR2_bit

__IO_REG8_BIT(__IER2,0xffff0804,__READ_WRITE,__ier_dlm_bits);
#define __DLM2     __IER2
#define __DLM2_bit __IER2_bit

__IO_REG8_BIT(__IIR2,0xffff0808,__READ,__iir_bits);
__IO_REG8_BIT(__LCR2,0xffff080c,__READ_WRITE,__lcr_bits);
__IO_REG8_BIT(__MCR2,0xffff0810,__READ_WRITE,__mcr_bits);
__IO_REG8_BIT(__LSR2,0xffff0814,__READ,__lsr_bits);
__IO_REG8_BIT(__MSR2,0xffff0818,__READ_WRITE,__msr_bits);
__IO_REG8_BIT(__SCR2,0xffff081c,__READ_WRITE,__rtds_bits);

/***************************************************************************
 **
 **  SIR: Serial Infrared Interface  
 **
 ***************************************************************************/
__IO_REG8_BIT(__SIR_CTLR,0xffff0c00,__READ_WRITE,__sirctlr_bits);

/***************************************************************************
 **
 **  PWM: Power Wave Mode register 
 **
 ***************************************************************************/

__IO_REG8_BIT(__PWM0_TC,0xffff1000,__WRITE,__pwmtc_bits);
__IO_REG8_BIT(__PWM0_DC,0xffff1004,__WRITE,__pwmdc_bits);
__IO_REG8_BIT(__PWM0_ENB,0xffff1008,__WRITE,__pwmenb_bits);
__IO_REG8_BIT(__PWM0_DIV,0xffff100c,__WRITE,__pwmdiv_bits);
__IO_REG8_BIT(__PWM0_SYNC,0xffff1010,__WRITE,__pwmsync_bits);
__IO_REG8_BIT(__PWM0_INV,0xffff1014,__WRITE,__pwminv_bits);

__IO_REG8_BIT(__PWM1_TC,0xffff1020,__WRITE,__pwmtc_bits);
__IO_REG8_BIT(__PWM1_DC,0xffff1024,__WRITE,__pwmdc_bits);
__IO_REG8_BIT(__PWM1_ENB,0xffff1028,__WRITE,__pwmenb_bits);
__IO_REG8_BIT(__PWM1_DIV,0xffff102c,__WRITE,__pwmdiv_bits);
__IO_REG8_BIT(__PWM1_SYNC,0xffff1030,__WRITE,__pwmsync_bits);
__IO_REG8_BIT(__PWM1_INV,0xffff1034,__WRITE,__pwminv_bits);

__IO_REG16_BIT(__PWM2_TC,0xffff1040,__WRITE,__pwm2tc_bits);
__IO_REG16_BIT(__PWM2_DC,0xffff1044,__WRITE,__pwm2dc_bits);
__IO_REG8_BIT(__PWM2_ENB,0xffff1048,__WRITE,__pwmenb_bits);
__IO_REG8_BIT(__PWM2_DIV,0xffff104c,__WRITE,__pwmdiv_bits);
__IO_REG8_BIT(__PWM2_SYNC,0xffff1050,__WRITE,__pwmsync_bits);
__IO_REG8_BIT(__PWM2_INV,0xffff1054,__WRITE,__pwminv_bits);

__IO_REG16_BIT(__PWMA_TC,0xffff1060,__WRITE,__pwm2tc_bits);
__IO_REG16_BIT(__PWMA_DC,0xffff1064,__WRITE,__pwm2dc_bits);
__IO_REG8_BIT(__PWMA_ENB,0xffff1068,__WRITE,__pwmenb_bits);
__IO_REG8_BIT(__PWMA_DIV,0xffff106c,__WRITE,__pwmdiv_bits);
__IO_REG8_BIT(__PWMA_SYNC,0xffff1070,__WRITE,__pwmsync_bits);
__IO_REG8_BIT(__PWMA_INV,0xffff1074,__WRITE,__pwminv_bits);


/***************************************************************************
 **
 **  LCD registers  
 **
 ***************************************************************************/

__IO_REG8_BIT(__LCD_MODE,0xffff1400,__WRITE,__lcdmode_bits);
__IO_REG8_BIT(__LCD_BC,0xffff1404,__WRITE,__lcdbc_bits);
__IO_REG8_BIT(__LCD_CP1W,0xffff1408,__WRITE,__lcdcp1w_bits);
__IO_REG8_BIT(__LCD_DUTYA,0xffff140c,__WRITE,__lcddutya_bits);
__IO_REG8_BIT(__LCD_DUTYB,0xffff1410,__WRITE,__lcddutyb_bits);
__IO_REG8_BIT(__LCD_SADR1A,0xffff1414,__WRITE,__lcdsadr1a_bits);
__IO_REG8_BIT(__LCD_SADR1B,0xffff1418,__WRITE,__lcdsadr1b_bits);
__IO_REG8_BIT(__LCD_SADR1C,0xffff141c,__WRITE,__lcdsadr1c_bits);
__IO_REG8_BIT(__LCD_SADR1D,0xffff1420,__WRITE,__lcdsadr1d_bits);
__IO_REG8_BIT(__LCD_SADR2A,0xffff1424,__WRITE,__lcdsadr2a_bits);
__IO_REG8_BIT(__LCD_SADR2B,0xffff1428,__WRITE,__lcdsadr2b_bits);
__IO_REG8_BIT(__LCD_SADR2C,0xffff142c,__WRITE,__lcdsadr2c_bits);
__IO_REG8_BIT(__LCD_SADR2D,0xffff1430,__WRITE,__lcdsadr2d_bits);
__IO_REG8_BIT(__LCD_VLC1A,0xffff1434,__WRITE,__lcdvlc1a_bits);
__IO_REG8_BIT(__LCD_VLC1B,0xffff1438,__WRITE,__lcdvlc1b_bits);
__IO_REG8_BIT(__LCD_VDLT,0xffff143c,__WRITE,__lcdvdlt_bits);
__IO_REG8_BIT(__LCD_GRAY1,0xffff1440,__WRITE,__lcdgray1_bits);
__IO_REG8_BIT(__LCD_GRAY2,0xffff1444,__WRITE,__lcdgray2_bits);
__IO_REG8_BIT(__LCD_CLKDIV,0xffff1448,__WRITE,__lcdclkdiv_bits);
__IO_REG8_BIT(__LCD_MCLKWA,0xffff144c,__WRITE,__lcdmclkwa_bits);
__IO_REG8_BIT(__LCD_MCLKWB,0xffff1450,__WRITE,__lcdmclkwb_bits);

__IO_REG8_BIT(__LCD_BITCTL,0xffffa414,__READ_WRITE,__lcdbitctl_bits);


/***************************************************************************
 **
 **  CT: Counters/Timers registers   
 **
 ***************************************************************************/
__IO_REG8_BIT(__CT_CNTR0,0xffff1800,__READ_WRITE,__ctcntr_bits);
__IO_REG8_BIT(__CT_CNTR1,0xffff1804,__READ_WRITE,__ctcntr_bits);
__IO_REG8_BIT(__CT_CNTR2,0xffff1808,__READ_WRITE,__ctcntr_bits);
__IO_REG8_BIT(__CT_CWR,0xffff180c,__WRITE,__ctcwr_bits);



/***************************************************************************
 **
 **  WD: Watchdog register   
 **
 ***************************************************************************/
__IO_REG8_BIT(__WDCTLR,0xffffac30,__READ_WRITE,__wdctlr_bits);
__IO_REG32_BIT(__WDCNTR,0xffffac34,__WRITE,__wdcntr_bits);


/***************************************************************************
 **
 **   PPI: Program Peripheral interface register   
 **
 ***************************************************************************/
__IO_REG8(__PPI_PA,0xffff1c00,__READ_WRITE);
__IO_REG8(__PPI_PB,0xffff1c04,__READ_WRITE);
__IO_REG8(__PPI_PC,0xffff1c08,__READ_WRITE);
__IO_REG8_BIT(__PPI_CTLR,0xffff1c0c,__WRITE,__ppictlr_bits);

/***************************************************************************
 **
 **  Interrupt control registers   
 **
 ***************************************************************************/
__IO_REG16_BIT(__ICR0,0xffffa800,__READ_WRITE,__icr0_bits);
__IO_REG8_BIT(__ICR1,0xffffa804,__READ_WRITE,__icr1_bits);
__IO_REG16_BIT(__ICLR,0xffffa808,__WRITE,__iclr_bits);
__IO_REG16_BIT(__IRQER,0xffffa80c,__READ_WRITE,__irqr_bits);
__IO_REG16_BIT(__FIQER,0xffffa810,__READ_WRITE,__fiqer_bits);
__IO_REG16_BIT(__IRQSR,0xffffa814,__READ,__irqr_bits);
__IO_REG16_BIT(__FIQSR,0xffffa818,__READ,__fiqsr_bits);
__IO_REG16_BIT(__IPR,0xffffa81c,__READ,__ipr_bits);


/***************************************************************************
 **
 **  I/O configuration register   
 **
 ***************************************************************************/
__IO_REG16_BIT(__IOCR,0xffffa410,__READ_WRITE,__iocr_bits);

/***************************************************************************
 **
 **  Identification register   
 **
 ***************************************************************************/
__IO_REG16_BIT(__IDR,0xffffa40c,__READ,__idr_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */




#endif    /* __LH77790B_H */
