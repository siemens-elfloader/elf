/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Atmel Semiconductors AT91M63200
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2000
 **                                
 **    $Revision: 1.6 $
 **                                
 ***************************************************************************/

#ifndef __AT91M63200_H
#define __AT91M63200_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    AT91M63200 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* EBI chip select register  */
typedef struct {
  __REG32 dbw  :2;
  __REG32 nws  :3;
  __REG32 wse  :1;
  __REG32      :1;
  __REG32 pages:2;
  __REG32 tdf  :3;
  __REG32 bat  :1;
  __REG32 csen :1;
  __REG32      :6;
  __REG32 ba   :12;
} __ebicsr_bits;


/* EBI remap control register */
typedef struct {
  __REG32 rcb  :1;
  __REG32      :31;
} __ebircr_bits;	

/* EBI memory control register */
typedef struct {
  __REG32 ale  :3;
  __REG32      :1;
  __REG32 drp  :1;
  __REG32      :27;
} __ebimcr_bits;	


/* AIC source mode register */
typedef struct {
  __REG32 prior  :3;
  __REG32        :2;
  __REG32 srctype:2;
  __REG32        :25;
} __aicsmr_bits;	

/* AIC source vector register */
typedef struct {
  __REG32 vector :32;
} __aicsvr_bits;	

/* AIC interrupt vector register */
typedef struct {
  __REG32 irqv :32;
} __aicivr_bits;

/* AIC FIQ vector register */
typedef struct {
  __REG32 fiqv :32;
} __aicfiqvr_bits;
	
/* AIC interrupt status register */
typedef struct {
  __REG32 irqid :5;
  __REG32       :27;
} __aicisr_bits;
	
/* AIC interrupt pending/mask/enable command/disable command/clear command/set command
 register */
typedef struct {
  __REG32 fiq    :1;
  __REG32 swirq  :1;
  __REG32 us0irq :1;
  __REG32 us1irq :1;
  __REG32 us2irq :1;
  __REG32 spirq  :1;
  __REG32 tc0irq :1;
  __REG32 tc1irq :1;
  __REG32 tc2irq :1;
  __REG32 tc3irq :1;
  __REG32 tc4irq :1;
  __REG32 tc5irq :1;
  __REG32 wdirq  :1;
  __REG32 pioairq:1;
  __REG32 piobirq:1;
  __REG32        :13;
  __REG32 irq3   :1;
  __REG32 irq2   :1;
  __REG32 irq1   :1;
  __REG32 irq0   :1;
} __aicir_bits;
	
/* AIC core interrupt status register */
typedef struct {
  __REG32 nfiq :1;
  __REG32 nirq :1;
  __REG32      :30;
} __aiccisr_bits;
	
/* AIC spurious vector register */
typedef struct {
  __REG32 spuvec:32;
} __aicspvr_bits;

/* PIO registers */
typedef struct {
  __REG32 p0    :1;
  __REG32 p1    :1;
  __REG32 p2    :1;
  __REG32 p3    :1;
  __REG32 p4    :1;
  __REG32 p5    :1;
  __REG32 p6    :1;
  __REG32 p7    :1;
  __REG32 p8    :1;
  __REG32 p9    :1;
  __REG32 p10   :1;
  __REG32 p11   :1;
  __REG32 p12   :1;
  __REG32 p13   :1;
  __REG32 p14   :1;
  __REG32 p15   :1;
  __REG32 p16   :1;
  __REG32 p17   :1;
  __REG32 p18   :1;
  __REG32 p19   :1;
  __REG32 p20   :1;
  __REG32 p21   :1;
  __REG32 p22   :1;
  __REG32 p23   :1;
  __REG32 p24   :1;
  __REG32 p25   :1;
  __REG32 p26   :1;
  __REG32 p27   :1;
  __REG32 p28   :1;
  __REG32 p29   :1;
  __REG32 p30   :1;
  __REG32 p31   :1;
} __pior_bits;


/* USART: control register */
typedef struct {
  __REG32         :2;
  __REG32 rstrx   :1;
  __REG32 rsttx   :1;
  __REG32 rxen    :1;
  __REG32 rxdis   :1;
  __REG32 txen    :1;
  __REG32 txdis   :1;
  __REG32 rststa  :1;
  __REG32 sttbrk  :1;
  __REG32 stpbrk  :1;
  __REG32 sttto   :1;
  __REG32 senda   :1;
  __REG32         :19;
} __usartcr_bits;

/* USART: mode register */
typedef struct {
  __REG32         :4;
  __REG32 usclks  :2;
  __REG32 chrl    :2;
  __REG32 sync    :1;
  __REG32 par     :3;
  __REG32 nbstop  :2;
  __REG32 chmode  :2;
  __REG32         :1;
  __REG32 mode9   :1;
  __REG32 clko    :1;
  __REG32         :13;
} __usartmr_bits;

/* USART0: interrupt enable/disable/mask/channel status register */
typedef struct {
  __REG32 rxrdy   :1;
  __REG32 txrdy   :1;
  __REG32 rxbrk   :1;
  __REG32 endrx   :1;
  __REG32 endtx   :1;
  __REG32 ovre    :1;
  __REG32 frame   :1;
  __REG32 pare    :1;
  __REG32 timeout :1;
  __REG32 txempty :1;
  __REG32         :20;
  __REG32 commtx  :1;
  __REG32 commrx  :1;
} __usart0ir_bits;

/* USART: interrupt enable/disable/mask/channel status register */
typedef struct {
  __REG32 rxrdy   :1;
  __REG32 txrdy   :1;
  __REG32 rxbrk   :1;
  __REG32 endrx   :1;
  __REG32 endtx   :1;
  __REG32 ovre    :1;
  __REG32 frame   :1;
  __REG32 pare    :1;
  __REG32 timeout :1;
  __REG32 txempty :1;
  __REG32         :22;
} __usartir_bits;

/* USART receiver holding register */
typedef struct {
  __REG32 rxchr   :9;
  __REG32         :23;
} __usartrhr_bits;

/* USART transmitter holding register */
typedef struct {
  __REG32 txchr   :9;
  __REG32         :23;
} __usartthr_bits;

/* USART baud rate generator register */
typedef struct {
  __REG32 cd      :16;
  __REG32         :16;
} __usartbrgr_bits;

/* USART receiver time-out register */
typedef struct {
  __REG32 to      :8;
  __REG32         :24;
} __usartrtr_bits;

/* USART transmitter time-guard register */
typedef struct {
  __REG32 tg      :8;
  __REG32         :24;
} __usartttr_bits;

/* USART receive pointer register */
typedef struct {
  __REG32 rxptr   :32;
} __usartrpr_bits;

/* USART receive counter register */
typedef struct {
  __REG32 rxctr   :16;
  __REG32         :16;
} __usartrcr_bits;


/* USART transmit pointer register */
typedef struct {
  __REG32 txptr   :32;
} __usarttpr_bits;

/* USART transmit counter register */
typedef struct {
  __REG32 txctr   :16;
  __REG32         :16;
} __usarttcr_bits;

/* SPI control register */
typedef struct {
  __REG32 spien   :1;
  __REG32 spidis  :1;
  __REG32         :5;
  __REG32 swrst   :1;
  __REG32         :24;
} __spicr_bits;

/* SPI mode register */
typedef struct {
  __REG32 mstr    :1;
  __REG32 ps      :1;
  __REG32 pcsdec  :1;
  __REG32 mck32   :1;
  __REG32         :3;
  __REG32 llb     :1;
  __REG32         :8;
  __REG32 pcs     :4;
  __REG32         :4;
  __REG32 dlybcs  :8;
} __spimr_bits;

/* SPI receive data register */
typedef struct {
  __REG32 rd      :16;
  __REG32 pcs     :4;
  __REG32         :12;
} __spirdr_bits;

/* SPI transmit data register */
typedef struct {
  __REG32 td      :16;
  __REG32 pcs     :4;
  __REG32         :12;
} __spitdr_bits;

/* SPI status register */
typedef struct {
  __REG32 rdrf    :1;
  __REG32 tdre    :1;
  __REG32 modf    :1;
  __REG32 ovres   :1;
  __REG32 spendrx :1;
  __REG32 spendtx :1;
  __REG32         :10;
  __REG32 spiens  :1;
  __REG32         :15;
} __spisr_bits;

/* SPI interrupt enable/ disable/mask/ register */
typedef struct {
  __REG32 rdrf    :1;
  __REG32 tdre    :1;
  __REG32 modf    :1;
  __REG32 ovres   :1;
  __REG32 spendrx :1;
  __REG32 spendtx :1;
  __REG32         :26;
} __spiir_bits;

/* SPI receive pointer register */
typedef struct {
  __REG32 rxptr   :32;
} __spirpr_bits;

/* SPI receive counter register */
typedef struct {
  __REG32 rxctr   :16;
  __REG32         :16;
} __spircr_bits;

/* SPI transmit pointer register */
typedef struct {
  __REG32 txptr   :32;
} __spitpr_bits;

/* SPI transmit counter register */
typedef struct {
  __REG32 txctr   :16;
  __REG32         :16;
} __spitcr_bits;


/* SPI chip select register */
typedef struct {
  __REG32 cpol    :1;
  __REG32 ncpha   :1;
  __REG32         :2;
  __REG32 bits    :4;
  __REG32 scbr    :8; 
  __REG32 dlybs   :8;
  __REG32 dlybct  :8;
} __spicsr_bits;



/* TC block control register */
typedef struct {
  __REG32 sync    :1;
  __REG32         :31;
} __tcbcr_bits;

/* TC block mode register */
typedef struct {
  __REG32 tc0xc0s :2;
  __REG32 tc1xc1s :2;
  __REG32 tc2xc2s :2;
  __REG32         :26;
} __tcbmr_bits;

/* TC channel control register */
typedef struct {
  __REG32 clken   :1;
  __REG32 clkdis  :1;
  __REG32 swtrg   :1;
  __REG32         :29;
} __tcccr_bits;

/* TC channel mode register: capture mode */
typedef struct {
  __REG32 tcclks  :3;
  __REG32 clki    :1;
  __REG32 burst   :2;
  __REG32 ldbstop :1;
  __REG32 ldbdis  :1;
  __REG32 etrgedg :2;
  __REG32 abetrg  :1;	
  __REG32         :3;	
  __REG32 cpctrg  :1;
  __REG32 wave    :1;
  __REG32 ldra    :2;
  __REG32 ldrb    :2;
  __REG32         :12;	 
} __tccmrcm_bits;


/* TC channel mode register: waveform mode */
typedef struct {
  __REG32 tcclks  :3;
  __REG32 clki    :1;
  __REG32 burst   :2;
  __REG32 cpcstop :1;
  __REG32 cpcdis  :1;
  __REG32 eevtedg :2;
  __REG32 eevt    :2;	
  __REG32 enetrg  :1;	
  __REG32         :1;
  __REG32 cpctrg  :1;
  __REG32 wave    :1;
  __REG32 acpa    :2;
  __REG32 acpc    :2;
  __REG32 aeevt   :2;
  __REG32 aswtrg  :2;
  __REG32 bcpb    :2;
  __REG32 bcpc    :2;
  __REG32 beevt   :2;
  __REG32 bswtrg  :2;
} __tccmrwm_bits;


/* TC counter value register */
typedef struct {
  __REG32 cv      :16;
  __REG32         :16;
} __tccvr_bits;

/* TC register A */
typedef struct {
  __REG32 ra      :16;
  __REG32         :16;
} __tcra_bits;

/* TC register B */
typedef struct {
  __REG32 rb      :16;
  __REG32         :16;
} __tcrb_bits;

/* TC register C */
typedef struct {
  __REG32 rc      :16;
  __REG32         :16;
} __tcrc_bits;

/* TC status register */
typedef struct {
  __REG32 covfs   :1;
  __REG32 lovrs   :1;
  __REG32 cpas    :1;
  __REG32 cpbs    :1;
  __REG32 cpcs    :1;
  __REG32 ldras   :1;
  __REG32 ldrbs   :1;
  __REG32 etrgs   :1;
  __REG32         :8;
  __REG32 clksta  :1;	
  __REG32 mtioa   :1;
  __REG32 mtiob   :1;
  __REG32         :13;
} __tcsr_bits;

/* TC interrupt enable/disable/mask register */
typedef struct {
  __REG32 covfs   :1;
  __REG32 lovrs   :1;
  __REG32 cpas    :1;
  __REG32 cpbs    :1;
  __REG32 cpcs    :1;
  __REG32 ldras   :1;
  __REG32 ldrbs   :1;
  __REG32 etrgs   :1;
  __REG32         :24;
} __tcir_bits;


/* WD: watchdog timer overflow mode register */
typedef struct {
  __REG32 wden   :1;
  __REG32 rsten  :1;
  __REG32 irqen  :1;
  __REG32 exten  :1;
  __REG32 okey   :12;
  __REG32        :16;
} __wdomr_bits;
	
/* WD: watchdog timer clock mode register */
typedef struct {
  __REG32 wdclks :2;
  __REG32 hpcv   :4;
  __REG32        :1;
  __REG32 ckey   :9;
  __REG32        :16;
} __wdcmr_bits;
	
/* WD: watchdog timer control register */
typedef struct {
  __REG32 rstkey :16;
  __REG32        :16;
} __wdcr_bits;
	
/* WD: watchdog timer status register */
typedef struct {
  __REG32 wdovf  :1;
  __REG32        :31;
} __wdsr_bits;



/* PMC system clock enable/disable/status register */
typedef struct {
  __REG32 cpu  :1;
  __REG32      :31;
} __pmcscr_bits;	


/* PMC peripheral clock enable/disable/status register */
typedef struct {
  __REG32      :2;
  __REG32 us0  :1;
  __REG32 us1  :1;
  __REG32 us2  :1;
  __REG32 spi  :1;
  __REG32 tc0  :1;
  __REG32 tc1  :1;
  __REG32 tc2  :1;
  __REG32 tc3  :1;
  __REG32 tc4  :1;
  __REG32 tc5  :1;
  __REG32      :1;
  __REG32 pioa :1;
  __REG32 piob :1;
  __REG32      :17;
} __pmcpcr_bits;	

	
/* SF: Special function registers chip ID register */
typedef struct {
  __REG32 version :5;
  __REG32         :1;
  __REG32         :1;
  __REG32         :1;
  __REG32 nvpsiz  :4;
  __REG32 nvdsiz  :4;
  __REG32 vdsiz   :4;
  __REG32 arch    :8;
  __REG32 nvptyp  :3;
  __REG32 ext     :1;
} __sfcir_bits;


/***** chip id extension register reserved for future use */

/* SF: reset status register */
typedef struct {
  __REG32 reset   :8;
  __REG32         :24;
} __sfrsr_bits;
		
/* SF: protect mode register */
typedef struct {
  __REG32         :5;
  __REG32 aic     :1;
  __REG32         :10;
  __REG32 pmrkey  :16;
} __sfpmr_bits;


	
#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  EBI   
 **
 ***************************************************************************/

__IO_REG32_BIT(__EBI_CSR0,0xffe00000,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_CSR1,0xffe00004,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_CSR2,0xffe00008,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_CSR3,0xffe0000c,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_CSR4,0xffe00010,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_CSR5,0xffe00014,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_CSR6,0xffe00018,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_CSR7,0xffe0001c,__READ_WRITE,__ebicsr_bits);
__IO_REG32_BIT(__EBI_RCR,0xffe00020,__WRITE,__ebircr_bits);
__IO_REG32_BIT(__EBI_MCR,0xffe00024,__READ_WRITE,__ebimcr_bits);


/***************************************************************************
 **
 **  Advanced interrupt controller  
 **
 ***************************************************************************/

/*  Source mode register */
__IO_REG32_BIT(__AIC_SMR0,0xfffff000,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR1,0xfffff004,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR2,0xfffff008,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR3,0xfffff00c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR4,0xfffff010,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR5,0xfffff014,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR6,0xfffff018,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR7,0xfffff01c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR8,0xfffff020,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR9,0xfffff024,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR10,0xfffff028,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR11,0xfffff02c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR12,0xfffff030,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR13,0xfffff034,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR14,0xfffff038,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR15,0xfffff03c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR16,0xfffff040,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR17,0xfffff044,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR18,0xfffff048,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR19,0xfffff04c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR20,0xfffff050,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR21,0xfffff054,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR22,0xfffff058,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR23,0xfffff05c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR24,0xfffff060,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR25,0xfffff064,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR26,0xfffff068,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR27,0xfffff06c,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR28,0xfffff070,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR29,0xfffff074,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR30,0xfffff078,__READ_WRITE,__aicsmr_bits);
__IO_REG32_BIT(__AIC_SMR31,0xfffff07c,__READ_WRITE,__aicsmr_bits);

/* Source vector register  */
__IO_REG32_BIT(__AIC_SVR0,0xfffff080,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR1,0xfffff084,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR2,0xfffff088,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR3,0xfffff08c,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR4,0xfffff090,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR5,0xfffff094,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR6,0xfffff098,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR7,0xfffff09c,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR8,0xfffff0a0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR9,0xfffff0a4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR10,0xfffff0a8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR11,0xfffff0ac,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR12,0xfffff0b0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR13,0xfffff0b4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR14,0xfffff0b8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR15,0xfffff0bc,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR16,0xfffff0c0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR17,0xfffff0c4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR18,0xfffff0c8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR19,0xfffff0cc,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR20,0xfffff0d0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR21,0xfffff0d4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR22,0xfffff0d8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR23,0xfffff0dc,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR24,0xfffff0e0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR25,0xfffff0e4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR26,0xfffff0e8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR27,0xfffff0ec,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR28,0xfffff0f0,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR29,0xfffff0f4,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR30,0xfffff0f8,__READ_WRITE,__aicsvr_bits);
__IO_REG32_BIT(__AIC_SVR31,0xfffff0fc,__READ_WRITE,__aicsvr_bits);


__IO_REG32_BIT(__AIC_IVR,0xfffff100,__READ_WRITE,__aicivr_bits);
__IO_REG32_BIT(__AIC_FVR,0xfffff104,__READ,__aicfiqvr_bits);
__IO_REG32_BIT(__AIC_ISR,0xfffff108,__READ,__aicisr_bits);
__IO_REG32_BIT(__AIC_IPR,0xfffff10c,__READ,__aicir_bits);

__IO_REG32_BIT(__AIC_IMR,0xfffff110,__READ,__aicir_bits);
__IO_REG32_BIT(__AIC_CISR,0xfffff114,__READ,__aiccisr_bits);
/*****RESERVED: 0xfffff118,0xfffff11c */

__IO_REG32_BIT(__AIC_IECR,0xfffff120,__WRITE,__aicir_bits);
__IO_REG32_BIT(__AIC_IDCR,0xfffff124,__WRITE,__aicir_bits);
__IO_REG32_BIT(__AIC_ICCR,0xfffff128,__WRITE,__aicir_bits);
__IO_REG32_BIT(__AIC_ISCR,0xfffff12c,__WRITE,__aicir_bits);

__IO_REG32(__AIC_EOICR,0xfffff130,__WRITE);
__IO_REG32_BIT(__AIC_SPU,0xfffff134,__READ_WRITE,__aicspvr_bits);


/***************************************************************************
 **
 **  Parallell I/O controller A  
 **
 ***************************************************************************/

__IO_REG32_BIT(__PIO_PER,0xfffec000,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_PDR,0xfffec004,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_PSR,0xfffec008,__READ,__pior_bits);
//RESERVED: 0xfffec00c 

__IO_REG32_BIT(__PIO_OER,0xfffec010,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_ODR,0xfffec014,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_OSR,0xfffec018,__READ,__pior_bits);
//RESERVED: 0xfffec01c 

__IO_REG32_BIT(__PIO_IFER,0xfffec020,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IFDR,0xfffec024,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IFSR,0xfffec028,__READ,__pior_bits);
//RESERVED: 0xfffec02c

__IO_REG32_BIT(__PIO_SODR,0xfffec030,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_CODR,0xfffec034,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_ODSR,0xfffec038,__READ,__pior_bits);
__IO_REG32_BIT(__PIO_PDSR,0xfffec03c,__READ,__pior_bits);

__IO_REG32_BIT(__PIO_IER,0xfffec040,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IDR,0xfffec044,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IMR,0xfffec048,__READ,__pior_bits);
__IO_REG32_BIT(__PIO_ISR,0xfffec04c,__READ,__pior_bits);

__IO_REG32_BIT(__PIO_MDER,0xfffec050,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_MDDR,0xfffec054,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_MDSR,0xfffec058,__READ,__pior_bits);
//RESERVED:0xfffec05c

/***************************************************************************
 **
 **  Parallell I/O controller B  
 **
 ***************************************************************************/

__IO_REG32_BIT(__PIO_PERB,0xffff0000,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_PDRB,0xffff0004,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_PSRB,0xffff0008,__READ,__pior_bits);
//RESERVED: 0xffff000c 

__IO_REG32_BIT(__PIO_OERB,0xffff0010,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_ODRB,0xffff0014,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_OSRB,0xffff0018,__READ,__pior_bits);
//RESERVED: 0xffff001c 

__IO_REG32_BIT(__PIO_IFERB,0xffff0020,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IFDRB,0xffff0024,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IFSRB,0xffff0028,__READ,__pior_bits);
//RESERVED: 0xffff002c

__IO_REG32_BIT(__PIO_SODRB,0xffff0030,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_CODRB,0xffff0034,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_ODSRB,0xffff0038,__READ,__pior_bits);
__IO_REG32_BIT(__PIO_PDSRB,0xffff003c,__READ,__pior_bits);

__IO_REG32_BIT(__PIO_IERB,0xffff0040,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IDRB,0xffff0044,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_IMRB,0xffff0048,__READ,__pior_bits);
__IO_REG32_BIT(__PIO_ISRB,0xffff004c,__READ,__pior_bits);

__IO_REG32_BIT(__PIO_MDERB,0xffff0050,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_MDDRB,0xffff0054,__WRITE,__pior_bits);
__IO_REG32_BIT(__PIO_MDSRB,0xffff0058,__READ,__pior_bits);
//RESERVED:0xffff005c


/***************************************************************************
 **
 **  USART0 
 **
 ***************************************************************************/

__IO_REG32_BIT(__US_CR,0xfffc0000,__WRITE,__usartcr_bits);
__IO_REG32_BIT(__US_MR,0xfffc0004,__READ_WRITE,__usartmr_bits);
__IO_REG32_BIT(__US_IER,0xfffc0008,__WRITE,__usart0ir_bits);
__IO_REG32_BIT(__US_IDR,0xfffc000c,__WRITE,__usart0ir_bits);

__IO_REG32_BIT(__US_IMR,0xfffc0010,__READ,__usart0ir_bits);
__IO_REG32_BIT(__US_CSR,0xfffc0014,__READ,__usart0ir_bits);
__IO_REG32_BIT(__US_RHR,0xfffc0018,__READ,__usartrhr_bits);
__IO_REG32_BIT(__US_THR,0xfffc001c,__WRITE,__usartthr_bits);

__IO_REG32_BIT(__US_BRGR,0xfffc0020,__READ_WRITE,__usartbrgr_bits);
__IO_REG32_BIT(__US_RTOR,0xfffc0024,__READ_WRITE,__usartrtr_bits);
__IO_REG32_BIT(__US_TTGR,0xfffc0028,__READ_WRITE,__usartttr_bits);
//RESERVED: 0xfffc002c 

__IO_REG32_BIT(__US_RPR,0xfffc0030,__READ_WRITE,__usartrpr_bits);
__IO_REG32_BIT(__US_RCR,0xfffc0034,__READ_WRITE,__usartrcr_bits);
__IO_REG32_BIT(__US_TPR,0xfffc0038,__READ_WRITE,__usarttpr_bits);
__IO_REG32_BIT(__US_TCR,0xfffc003c,__READ_WRITE,__usarttcr_bits);

/***************************************************************************
 **
 **  USART1  
 **
 ***************************************************************************/

__IO_REG32_BIT(__US_CR1,0xfffc4000,__WRITE,__usartcr_bits);
__IO_REG32_BIT(__US_MR1,0xfffc4004,__READ_WRITE,__usartmr_bits);
__IO_REG32_BIT(__US_IER1,0xfffc4008,__WRITE,__usartir_bits);
__IO_REG32_BIT(__US_IDR1,0xfffc400c,__WRITE,__usartir_bits);

__IO_REG32_BIT(__US_IMR1,0xfffc4010,__READ,__usartir_bits);
__IO_REG32_BIT(__US_CSR1,0xfffc4014,__READ,__usartir_bits);
__IO_REG32_BIT(__US_RHR1,0xfffc4018,__READ,__usartrhr_bits);
__IO_REG32_BIT(__US_THR1,0xfffc401c,__WRITE,__usartthr_bits);

__IO_REG32_BIT(__US_BRGR1,0xfffc4020,__READ_WRITE,__usartbrgr_bits);
__IO_REG32_BIT(__US_RTOR1,0xfffc4024,__READ_WRITE,__usartrtr_bits);
__IO_REG32_BIT(__US_TTGR1,0xfffc4028,__READ_WRITE,__usartttr_bits);
//RESERVED: 0xfffc402c

__IO_REG32_BIT(__US_RPR1,0xfffc4030,__READ_WRITE,__usartrpr_bits);
__IO_REG32_BIT(__US_RCR1,0xfffc4034,__READ_WRITE,__usartrcr_bits);
__IO_REG32_BIT(__US_TPR1,0xfffc4038,__READ_WRITE,__usarttpr_bits);
__IO_REG32_BIT(__US_TCR1,0xfffc403c,__READ_WRITE,__usarttcr_bits);



/***************************************************************************
 **
 **  USART2  
 **
 ***************************************************************************/

__IO_REG32_BIT(__US_CR2,0xfffc8000,__WRITE,__usartcr_bits);
__IO_REG32_BIT(__US_MR2,0xfffc8004,__READ_WRITE,__usartmr_bits);
__IO_REG32_BIT(__US_IER2,0xfffc8008,__WRITE,__usartir_bits);
__IO_REG32_BIT(__US_IDR2,0xfffc800c,__WRITE,__usartir_bits);

__IO_REG32_BIT(__US_IMR2,0xfffc8010,__READ,__usartir_bits);
__IO_REG32_BIT(__US_CSR2,0xfffc8014,__READ,__usartir_bits);
__IO_REG32_BIT(__US_RHR2,0xfffc8018,__READ,__usartrhr_bits);
__IO_REG32_BIT(__US_THR2,0xfffc801c,__WRITE,__usartthr_bits);

__IO_REG32_BIT(__US_BRGR2,0xfffc8020,__READ_WRITE,__usartbrgr_bits);
__IO_REG32_BIT(__US_RTOR2,0xfffc8024,__READ_WRITE,__usartrtr_bits);
__IO_REG32_BIT(__US_TTGR2,0xfffc8028,__READ_WRITE,__usartttr_bits);
//RESERVED: 0xfffc802c

__IO_REG32_BIT(__US_RPR2,0xfffc8030,__READ_WRITE,__usartrpr_bits);
__IO_REG32_BIT(__US_RCR2,0xfffc8034,__READ_WRITE,__usartrcr_bits);
__IO_REG32_BIT(__US_TPR2,0xfffc8038,__READ_WRITE,__usarttpr_bits);
__IO_REG32_BIT(__US_TCR2,0xfffc803c,__READ_WRITE,__usarttcr_bits);



/***************************************************************************
 **
 **  Serial Peripherial Interface  
 **  
 ***************************************************************************/

__IO_REG32_BIT(__SP_CR,0xfffbc000,__WRITE,__spicr_bits);
__IO_REG32_BIT(__SP_MR,0xfffbc004,__READ_WRITE,__spimr_bits);
__IO_REG32_BIT(__SP_RDR,0xfffbc008,__READ,__spirdr_bits);
__IO_REG32_BIT(__SP_TDR,0xfffbc00c,__WRITE,__spitdr_bits);
__IO_REG32_BIT(__SP_SR,0xfffbc010,__READ,__spisr_bits);
__IO_REG32_BIT(__SP_IER,0xfffbc014,__WRITE,__spiir_bits);
__IO_REG32_BIT(__SP_IDR,0xfffbc018,__WRITE,__spiir_bits);
__IO_REG32_BIT(__SP_IMR,0xfffbc01c,__READ,__spiir_bits);
__IO_REG32_BIT(__SP_RPR,0xfffbc020,__READ_WRITE,__spirpr_bits);
__IO_REG32_BIT(__SP_RCR,0xfffbc024,__READ_WRITE,__spircr_bits);
__IO_REG32_BIT(__SP_TPR,0xfffbc028,__READ_WRITE,__spitpr_bits);
__IO_REG32_BIT(__SP_TCR,0xfffbc02c,__READ_WRITE,__spitcr_bits);
__IO_REG32_BIT(__SP_CSR0,0xfffbc030,__READ_WRITE,__spicsr_bits);
__IO_REG32_BIT(__SP_CSR1,0xfffbc034,__READ_WRITE,__spicsr_bits);
__IO_REG32_BIT(__SP_CSR2,0xfffbc038,__READ_WRITE,__spicsr_bits);
__IO_REG32_BIT(__SP_CSR3,0xfffbc03c,__READ_WRITE,__spicsr_bits);


/***************************************************************************
 **
 **  TC Block 0  
 **  (default: capturemode)
 ***************************************************************************/

/* TC channel 0 */

__IO_REG32_BIT(__TC_CCRC0,0xfffd0000,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(__TC_CMRC0,0xfffd0004,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(__TC_CMRC0,0xfffd0004,__READ_WRITE,__tccmrwm_bits); 
 
//RESERVED: 0xfffd0008, 0xfffd000c 
__IO_REG32_BIT(__TC_CVC0,0xfffd0010,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(__TC_RAC0,0xfffd0014,__READ,__tcra_bits);
__IO_REG32_BIT(__TC_RBC0,0xfffd0018,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(__TC_RAC0,0xfffd0014,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(__TC_RBC0,0xfffd0018,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(__TC_RCC0,0xfffd001c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(__TC_SRC0,0xfffd0020,__READ,__tcsr_bits);
__IO_REG32_BIT(__TC_IERC0,0xfffd0024,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IDRC0,0xfffd0028,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IMRC0,0xfffd002c,__READ,__tcir_bits);


/******* TC channel 1 *******/

__IO_REG32_BIT(__TC_CCRC1,0xfffd0040,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(__TC_CMRC1,0xfffd0044,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(__TC_CMRC1,0xfffd0044,__READ_WRITE,__tccmrwm_bits); 

//RESERVED: 0xfffd0048, 0xfffd004c 

__IO_REG32_BIT(__TC_CVC1,0xfffd0050,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(__TC_RAC1,0xfffd0054,__READ,__tcra_bits);
__IO_REG32_BIT(__TC_RBC1,0xfffd0058,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(__TC_RAC1,0xfffd0054,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(__TC_RBC1,0xfffd0058,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(__TC_RCC1,0xfffd005c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(__TC_SRC1,0xfffd0060,__READ,__tcsr_bits);
__IO_REG32_BIT(__TC_IERC1,0xfffd0064,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IDRC1,0xfffd0068,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IMRC1,0xfffd006c,__READ,__tcir_bits);

/******* TC channel 2 *******/

__IO_REG32_BIT(__TC_CCRC2,0xfffd0080,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(__TC_CMRC2,0xfffd0084,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(__TC_CMRC2,0xfffd0084,__READ_WRITE,__tccmrwm_bits); 

//RESERVED: 0xfffd0088, 0xfffd008c
__IO_REG32_BIT(__TC_CVC2,0xfffd0090,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(__TC_RAC2,0xfffd0094,__READ,__tcra_bits);
__IO_REG32_BIT(__TC_RBC2,0xfffd0098,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(__TC_RAC2,0xfffd0094,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(__TC_RBC2,0xfffd0098,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(__TC_RCC2,0xfffd009c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(__TC_SRC2,0xfffd00a0,__READ,__tcsr_bits);
__IO_REG32_BIT(__TC_IERC2,0xfffd00a4,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IDRC2,0xfffd00a8,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IMRC2,0xfffd00ac,__READ,__tcir_bits);


__IO_REG32_BIT(__TC_BCR,0xfffd00c0,__WRITE,__tcbcr_bits);
__IO_REG32_BIT(__TC_BMR,0xfffd00c4,__READ_WRITE,__tcbmr_bits);


/***************************************************************************
 **
 **  TC Block 1 
 **  (default: capturemode)
 ***************************************************************************/

/* TC channel 0 */

__IO_REG32_BIT(__TC_CCR1C0,0xfffd4000,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(__TC_CMR1C0,0xfffd4004,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(__TC_CMR1C0,0xfffd4004,__READ_WRITE,__tccmrwm_bits); 
 
//RESERVED: 0xfffd4008, 0xfffd400c 
__IO_REG32_BIT(__TC_CV1C0,0xfffd4010,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(__TC_RA1C0,0xfffd4014,__READ,__tcra_bits);
__IO_REG32_BIT(__TC_RB1C0,0xfffd4018,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(__TC_RA1C0,0xfffd4014,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(__TC_RB1C0,0xfffd4018,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(__TC_RC1C0,0xfffd401c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(__TC_SR1C0,0xfffd4020,__READ,__tcsr_bits);
__IO_REG32_BIT(__TC_IER1C0,0xfffd4024,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IDR1C0,0xfffd4028,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IMR1C0,0xfffd402c,__READ,__tcir_bits);


/******* TC channel 1 *******/

__IO_REG32_BIT(__TC_CCR1C1,0xfffd4040,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(__TC_CMR1C1,0xfffd4044,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(__TC_CMR1C1,0xfffd4044,__READ_WRITE,__tccmrwm_bits); 

//RESERVED: 0xfffd4048, 0xfffd404c 

__IO_REG32_BIT(__TC_CV1C1,0xfffd4050,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(__TC_RA1C1,0xfffd4054,__READ,__tcra_bits);
__IO_REG32_BIT(__TC_RB1C1,0xfffd4058,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(__TC_RA1C1,0xfffd4054,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(__TC_RB1C1,0xfffd4058,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(__TC_RC1C1,0xfffd405c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(__TC_SR1C1,0xfffd4060,__READ,__tcsr_bits);
__IO_REG32_BIT(__TC_IER1C1,0xfffd4064,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IDR1C1,0xfffd4068,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IMR1C1,0xfffd406c,__READ,__tcir_bits);

/******* TC channel 2 *******/

__IO_REG32_BIT(__TC_CCR1C2,0xfffd4080,__WRITE,__tcccr_bits);

// capturemode 
__IO_REG32_BIT(__TC_CMR1C2,0xfffd4084,__READ_WRITE,__tccmrcm_bits);
// wavemode
//__IO_REG32_BIT(__TC_CMR1C2,0xfffd4084,__READ_WRITE,__tccmrwm_bits); 

//RESERVED: 0xfffd4088, 0xfffd408c
__IO_REG32_BIT(__TC_CV1C2,0xfffd4090,__READ_WRITE,__tccvr_bits);

//capturemode
__IO_REG32_BIT(__TC_RA1C2,0xfffd4094,__READ,__tcra_bits);
__IO_REG32_BIT(__TC_RB1C2,0xfffd4098,__READ,__tcrb_bits); 
// wave mode 
//__IO_REG32_BIT(__TC_RA1C2,0xfffd4094,__READ_WRITE,__tcra_bits);
//__IO_REG32_BIT(__TC_RB1C2,0xfffd4098,__READ_WRITE,__tcrb_bits); 

__IO_REG32_BIT(__TC_RC1C2,0xfffd409c,__READ_WRITE,__tcrc_bits);
__IO_REG32_BIT(__TC_SR1C2,0xfffd40a0,__READ,__tcsr_bits);
__IO_REG32_BIT(__TC_IER1C2,0xfffd40a4,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IDR1C2,0xfffd40a8,__WRITE,__tcir_bits);
__IO_REG32_BIT(__TC_IMR1C2,0xfffd40ac,__READ,__tcir_bits);


__IO_REG32_BIT(__TC_BCR1,0xfffd40c0,__WRITE,__tcbcr_bits);
__IO_REG32_BIT(__TC_BMR1,0xfffd40c4,__READ_WRITE,__tcbmr_bits);

/***************************************************************************
 **
 **  Watchdog timer 
 **
 ***************************************************************************/

__IO_REG32_BIT(__WD_OMR,0xffff8000,__READ_WRITE,__wdomr_bits);
__IO_REG32_BIT(__WD_CMR,0xffff8004,__READ_WRITE,__wdcmr_bits);
__IO_REG32_BIT(__WD_CR,0xffff8008,__WRITE,__wdcr_bits);
__IO_REG32_BIT(__WD_SR,0xffff800c,__READ,__wdsr_bits);


/***************************************************************************
 **
 **  Power management controller   
 **
 ***************************************************************************/

__IO_REG32_BIT(__PMC_SCER,0xffff4000,__WRITE,__pmcscr_bits);
__IO_REG32_BIT(__PMC_SCDR,0xffff4004,__WRITE,__pmcscr_bits);
__IO_REG32_BIT(__PMC_SCSR,0xffff4008,__READ,__pmcscr_bits);
/*RESERVED: 0xffff400c */
__IO_REG32_BIT(__PMC_PCER,0xffff4010,__WRITE,__pmcpcr_bits);
__IO_REG32_BIT(__PMC_PCDR,0xffff4014,__WRITE,__pmcpcr_bits);
__IO_REG32_BIT(__PMC_PCSR,0xffff4018,__READ,__pmcpcr_bits);


/***************************************************************************
 **
 **  Special function registers 
 **
 ***************************************************************************/
__IO_REG32_BIT(__SF_CIDR,0xfff00000,__READ,__sfcir_bits);
__IO_REG32(__SF_EXID,0xfff00004,__READ); /* reserved for future use */
__IO_REG32_BIT(__SF_RSR,0xfff00008,__READ,__sfrsr_bits);
/*RESERVED: 0xfff0000c,0xfff00010,0xfff00014 */
__IO_REG32_BIT(__SF_PMR,0xfff00018,__READ_WRITE,__sfpmr_bits);


/* Assembler specific declarations  ****************************************/
#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */


/***************************************************************************
 **
 **  AIC interrupt sources 
 **
 ***************************************************************************/
#define FIQ      0   /* Fast interrupt                        */
#define SWIRQ    1   /* Soft interrupt (generated by the AIC) */
#define US0IRQ   2   /* USART channel 0 interrupt             */
#define US1IRQ   3   /* USART channel 1 interrupt             */
#define US2IRQ   4   /* USART channel 2 interrupt             */
#define SPIRQ    5   /* SPI interrupt                         */
#define TC0IRQ   6   /* Timer channel 0 interrupt             */ 
#define TC1IRQ   7   /* Timer channel 1 interrupt             */
#define TC2IRQ   8   /* Timer channel 2 interrupt             */ 
#define TC3IRQ   9   /* Timer channel 3 interrupt             */ 
#define TC4IRQ  10   /* Timer channel 4 interrupt             */
#define TC5IRQ  11   /* Timer channel 5 interrupt             */ 
#define WDIRQ   12   /* Watchdog interrupt                    */
#define PIOAIRQ 13   /* Parallell I/O controller A interrupt  */
#define PIOBIRQ 14   /* Parallell I/O controller B interrupt  */
/* Reserved 15-27*/
#define IRQ3    28   /* External interrupt 3                  */
#define IRQ2    29   /* External interrupt 2                  */
#define IRQ1    30   /* External interrupt 1                  */
#define IRQ0    31   /* External interrupt 0                  */

#endif    /* __AT91M63200_H */
