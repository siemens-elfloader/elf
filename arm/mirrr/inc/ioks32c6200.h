/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Samsung Semiconductors KS32C6200
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2000
 **                                
 **    $Revision: 1.5 $
 **                                
 ***************************************************************************/

#ifndef __KS32C6200_H
#define __KS32C6200_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    KS32C6200 SPECIAL FUNCTION REGISTERS
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
  __REG32 se   :1; /* stall enable */ 
  __REG32 ce   :1; /* cache enable */
  __REG32 we   :1; /* write buffer enable */
  __REG32 nu   :1; /* not used bit  */
  __REG32 start:9; /* SFRs start address */
  __REG32      :19; 
} __syscfg_bits;

/* SM: ROM timing control register  */
typedef struct {
  __REG32 dw    :2; 
  __REG32       :5; 
  __REG32 pmc   :2; 
  __REG32 tacp  :2; 
  __REG32 tacc  :3; 
  __REG32 bp    :9;
  __REG32 np    :9; 
} __romcon_bits;



/* SM: SRAM control register  */
typedef struct {
  __REG32 dw      :2; 
  __REG32 sioaddr :9; 
  __REG32 tacc    :3; 
  __REG32 bp      :9; 
  __REG32 np      :9; 
} __sramcon_bits;

/* SM: DRAM control register  */
typedef struct {
  __REG32 dw      :2; 
  __REG32 can     :2; 
  __REG32 edo     :1; 
  __REG32 tpgm    :2;
  __REG32 tcp     :1; 
  __REG32 tcs     :3;
  __REG32 trc     :1;
  __REG32 trp     :2;
  __REG32 bp      :9;
  __REG32 np      :9; 
} __dramcon_bits;


/* SM: DRAM refresh control register  */
typedef struct {
  __REG32 vsf  :1; 
  __REG32      :15;  
  __REG32 ren  :1;
  __REG32 tcs  :3; 
  __REG32 tcsr :1;
  __REG32 rcnt :11;
} __refcon_bits;

/* SM: DRAM extra bank control register */
typedef struct {
  __REG32 dw    :2; 
  __REG32 tocs  :3;  
  __REG32 tacs  :3;
  __REG32 tcoh  :3; 
  __REG32 tacc  :3;  
  __REG32 bp    :9;
  __REG32 np    :9;
} __extcon_bits;

/* CACHE: start/end address of non-cacheable area register */
typedef struct {
  __REG32       :9; 
  __REG32 addr  :19; 
  __REG32       :4; 
} __cachna_bits;	
	
/* SC: data transfer register */
typedef struct {
  __REG32 rd    :16; 
  __REG32       :16;  
} __datarvs_bits;	
	
/* SC: control register */
typedef struct {
  __REG32 mode  :1;
  __REG32 sdir   :1; 
  __REG32 stat  :1; 
  __REG32 ddir   :1;
  __REG32        :28; 
} __sftcon_bits;	

/* SC: count register */
typedef struct {
  __REG32 cnt    :8;
  __REG32        :24; 
} __sftcnt_bits;		
	
	
/* Timer: control register */
typedef struct {
  __REG32 t0en    :1;
  __REG32 cdfsel0 :2;
  __REG32 t1en    :1;
  __REG32 cdfsel1 :2;
  __REG32 t2en    :1;
  __REG32 cdfsel2 :2;
  __REG32         :23;
} __tcon_bits;

/* Timer: count register */
typedef struct {
  __REG32 cv     :16;
  __REG32        :16;
} __tbcnt_bits;	

	
/* DMA0 control register */
typedef struct {
  __REG32 re     :1; 
  __REG32 bs     :1; 
  __REG32 mode   :2;
  __REG32 dd     :1;
  __REG32 sd     :1; 
  __REG32 df     :1;
  __REG32 sf     :1; 
  __REG32 si     :1; 
  __REG32 rs     :1;
  __REG32 td     :1;  
  __REG32 sb     :1;
  __REG32 tw     :2;
  __REG32 cn     :1;
  __REG32 dm     :1;
  __REG32        :16; 
} __dmacon0_bits;	

/* DMA source/dest address register */
typedef struct {
  __REG32 addr   :25; 
  __REG32        :7; 
} __dmasrcdst_bits;	
	
/* DMA transfer count register */
typedef struct {
  __REG32 cnt    :24; 
  __REG32        :8; 
} __dmacnt_bits;		

/* DMA1 control register */
typedef struct {
  __REG32 re     :1; 
  __REG32 bs     :1; 
  __REG32 mode   :2;
  __REG32 dd     :1;
  __REG32 sd     :1; 
  __REG32 df     :1;
  __REG32 sf     :1; 
  __REG32 si     :1; 
  __REG32 rs     :1;
  __REG32 td     :1;  
  __REG32 sb     :1;
  __REG32 tw     :2;
  __REG32 cn     :1;
  __REG32        :17;
} __dmacon1_bits;	


/* PP: parallell port register */
typedef struct {
  __REG32 ppd  :8;
  __REG32 ecp  :1;
  __REG32      :23;
} __ppdata_bits;

/* PP: parallell port status register */
typedef struct {
  __REG32 nfault   :1;
  __REG32 select   :1;
  __REG32 perrror  :1;
  __REG32 busyc    :1;
  __REG32 nackc    :1;
  __REG32 busys    :1;
  __REG32 nacks    :1;
  __REG32 nslctin  :1;
  __REG32 nstrobe  :1;
  __REG32 nautofd  :1;
  __REG32 ninit    :1;
  __REG32          :21;
} __ppstat_bits;

/* PP: parallell port nack pulse width register */
typedef struct {
  __REG32 pw       :9;
  __REG32          :23;
} __ppackwth_bits;

/* PP: parallell port control register */
typedef struct {
  __REG32 sr       :1;
  __REG32 dfen     :1;
  __REG32 mode     :2;
  __REG32 ecp      :1;
  __REG32 ec       :1;
  __REG32 oen      :1;
  __REG32 ab       :1;
  __REG32 dmasel   :1;
  __REG32 dmar     :1;
  __REG32 fd       :1;
  __REG32          :1;
  __REG32 zi       :1;
  __REG32 ds       :1;
  __REG32 dls      :1;
  __REG32 de       :1;
  __REG32          :16;
} __ppcon_bits;

/* PP: parallell interrupt enable/pending register */
typedef struct {
  __REG32 nslctinlh   :1;
  __REG32 nslctinhl   :1;
  __REG32 nstrobelh   :1;
  __REG32 nstrobehl   :1;
  __REG32 nautofdlh   :1;
  __REG32 nautofdhl   :1;
  __REG32 ninitiallh  :1;
  __REG32 ninitialhl  :1;
  __REG32 dr          :1;
  __REG32 cbr         :1;
  __REG32 iselt       :1;
  __REG32 tde         :1;
  __REG32             :20;
} __ppi_bits;

		
/* UART: line control register */
typedef struct {
  __REG32 wl    :2;
  __REG32 stb   :1;
  __REG32 pmd   :3;
  __REG32 sc    :1;
  __REG32 ir    :1;
  __REG32       :24;
} __ulcon_bits;

/* UART: control register */
typedef struct {
  __REG32 rxm   :2;
  __REG32 rs    :1;
  __REG32 txm   :2;
  __REG32       :1;
  __REG32 sb    :1;
  __REG32 lp    :1;
  __REG32       :24;
} __ucon_bits;


/* UART: status register */
typedef struct {
  __REG32 ov   :1;
  __REG32 pt   :1;
  __REG32 fr   :1;
  __REG32 bk   :1;
  __REG32      :1;
  __REG32 rd   :1;
  __REG32 th   :1;
  __REG32 te   :1;
  __REG32      :24;
} __ustat_bits;


/* UART transmit buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __utxbuf_bits;

/* UART receive buffer register */
typedef struct {
  __REG32 data :8;
  __REG32      :24;
} __urxbuf_bits;

/* UART: baud rate divisor register */
typedef struct {
  __REG32 brdiv :16;
  __REG32       :16;
} __ubrdiv_bits;

/* TG: data register */
typedef struct {
  __REG32 tcd :8;
  __REG32 tgc :1;
  __REG32     :23;
} __tondata_bits;


/* WDT: count register */
typedef struct {
  __REG32 cnt :16;
  __REG32     :16;
} __wtcnt_bits;


/* WDT: control register */
typedef struct {
  __REG32 rm   :1;
  __REG32      :1;
  __REG32 im   :1;
  __REG32 clk  :2;
  __REG32 wden :1;
  __REG32      :26;
} __wtcon_bits;

/* I/O: port mode register */
typedef struct {
  __REG32 giop  :5; 
  __REG32 gop   :11;
  __REG32 gip   :6;
  __REG32       :10;
} __iopmod_bits;

/* I/O: port data register */
typedef struct {
  __REG32 giop  :5; 
  __REG32 gop   :13;
  __REG32 gip   :6;
  __REG32       :8;
}__iopdata_bits;

/* I/O: test control register */
typedef struct {
  __REG32       :5; 
  __REG32 clkout:1;
  __REG32       :1;
  __REG32 pv    :8;
  __REG32 ov    :1;
  __REG32       :16;
}__tstcon_bits;

/* I/O: EERAM control register */
typedef struct {
  __REG32 data  :1; 
  __REG32 clk   :1;
  __REG32 dir   :1;
  __REG32       :29;
}__eeramcon_bits;

/* I/O: extra-output port A register */
typedef struct {
  __REG32 eop   :6; 
  __REG32       :26;
}__eopa_bits;

/* I/O: extra-output port B register */
typedef struct {
  __REG32       :8; 
  __REG32 eopb  :4;
  __REG32       :20; 
}__eopb_bits;

/*IC: interrupt mode register */
typedef struct {
  __REG32 int_ext0   :1; 
  __REG32 int_ext1   :1;
  __REG32 int_wdtimer:1;
  __REG32 int_txc1   :1;
  __REG32 int_txc0   :1;
  __REG32 int_rxc1   :1;
  __REG32 int_rxc0   :1;
  __REG32 int_usr0   :1; 
  __REG32 int_usr1   :1;
  __REG32 int_dma1   :1;
  __REG32 int_dma0   :1;
  __REG32 int_timer0 :1;
  __REG32 int_timer1 :1;
  __REG32 int_timer2 :1;
  __REG32 int_pp     :1;
  __REG32            :17;
} __intmod_bits;

/*IC: interrupt mask/pending register */
typedef struct {
  __REG32 int_ext0   :1; 
  __REG32 int_ext1   :1;
  __REG32 int_wdtimer:1;
  __REG32 int_txc1   :1;
  __REG32 int_txc0   :1;
  __REG32 int_rxc1   :1;
  __REG32 int_rxc0   :1;
  __REG32 int_usr0   :1; 
  __REG32 int_usr1   :1;
  __REG32 int_dma1   :1;
  __REG32 int_dma0   :1;
  __REG32 int_timer0 :1;
  __REG32 int_timer1 :1;
  __REG32 int_timer2 :1;
  __REG32 int_pp     :1;
  __REG32            :5;
  __REG32 gmask      :1;
  __REG32            :11;
} __intpndmsk_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  System manager registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__SYSCFG,0x01000000,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(__ROMCON,0x01003000,__READ_WRITE,__romcon_bits);
__IO_REG32_BIT(__SRAMCON0,0x01003004,__READ_WRITE,__sramcon_bits);
__IO_REG32_BIT(__SRAMCON1,0x01003008,__READ_WRITE,__sramcon_bits);
__IO_REG32_BIT(__DRAMCON0,0x0100301c,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__DRAMCON1,0x01003020,__READ_WRITE,__dramcon_bits);
__IO_REG32_BIT(__REFCON,0x01003024,__READ_WRITE,__refcon_bits);
__IO_REG32_BIT(__EXTCON0,0x0100300c,__READ_WRITE,__extcon_bits);
__IO_REG32_BIT(__EXTCON1,0x01003010,__READ_WRITE,__extcon_bits);
__IO_REG32_BIT(__EXTCON2,0x01003014,__READ_WRITE,__extcon_bits);
__IO_REG32_BIT(__EXTCON3,0x01003018,__READ_WRITE,__extcon_bits);

/***************************************************************************
 **
 **  Cache special registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__CACHNAB0,0x01001000,__READ_WRITE,__cachna_bits);
__IO_REG32_BIT(__CACHNAE0,0x01001800,__READ_WRITE,__cachna_bits);
__IO_REG32_BIT(__CACHNAB1,0x01002000,__READ_WRITE,__cachna_bits);
__IO_REG32_BIT(__CACHNAE1,0x01002800,__READ_WRITE,__cachna_bits);

/***************************************************************************
 **
 **  Derasterizer registers  
 **
 ***************************************************************************/
__IO_REG32(__DRAST0,0x01006000,__READ_WRITE);
__IO_REG32(__DRAST1,0x01006004,__READ_WRITE);
__IO_REG32(__DRAST2,0x01006008,__READ_WRITE);
__IO_REG32(__DRAST3,0x0100600c,__READ_WRITE);
__IO_REG32(__DRAST4,0x01006010,__READ_WRITE);
__IO_REG32(__DRAST5,0x01006014,__READ_WRITE);
__IO_REG32(__DRAST6,0x01006018,__READ_WRITE);
__IO_REG32(__DRAST7,0x0100601c,__READ_WRITE);
__IO_REG32(__DRAST8,0x01006020,__READ_WRITE);
__IO_REG32(__DRAST9,0x01006024,__READ_WRITE);
__IO_REG32(__DRAST10,0x01006028,__READ_WRITE);
__IO_REG32(__DRAST11,0x0100602c,__READ_WRITE);
__IO_REG32(__DRAST12,0x01006030,__READ_WRITE);
__IO_REG32(__DRAST13,0x01006034,__READ_WRITE);
__IO_REG32(__DRAST14,0x01006038,__READ_WRITE);
__IO_REG32(__DRAST15,0x0100603c,__READ_WRITE);

/***************************************************************************
 **
 **  Shift control registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__DATARVS,0x01007000,__READ_WRITE, __datarvs_bits);
__IO_REG32_BIT(__SFTCON,0x01007004,__READ_WRITE, __sftcon_bits);
__IO_REG32_BIT(__SFTCNT,0x01007008,__READ_WRITE, __sftcnt_bits);
__IO_REG32(__SFTDATA0,0x0100700c,__READ_WRITE);
__IO_REG32(__SFTDATA1,0x01007010,__READ_WRITE);
__IO_REG32(__SFTDATA2,0x01007014,__READ_WRITE);
__IO_REG32(__SFTDATA3,0x01007018,__READ_WRITE);
__IO_REG32(__SFTDATA4,0x0100701c,__READ_WRITE);
__IO_REG32(__SFTDATA5,0x01007020,__READ_WRITE);
__IO_REG32(__SFTDATA6,0x01007024,__READ_WRITE);


/***************************************************************************
 **
 **  Timer registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__TCON,0x01005800,__READ_WRITE, __tcon_bits);
__IO_REG32_BIT(__TBCNT0,0x01005804,__READ_WRITE, __tbcnt_bits);
__IO_REG32_BIT(__TBCNT1,0x01005808,__READ_WRITE, __tbcnt_bits);
__IO_REG32_BIT(__TBCNT2,0x0100580c,__READ_WRITE, __tbcnt_bits);

/***************************************************************************
 **
 **  DMA control registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__DMACON0,0x0100c000,__READ_WRITE,__dmacon0_bits);
__IO_REG32_BIT(__DMASRC0,0x0100c004,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMADST0,0x0100c008,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMACNT0,0x0100c00c,__READ_WRITE,__dmacnt_bits);
__IO_REG32_BIT(__DMACON1,0x0100c800,__READ_WRITE,__dmacon1_bits);
__IO_REG32_BIT(__DMASRC1,0x0100c804,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMADST1,0x0100c808,__READ_WRITE,__dmasrcdst_bits);
__IO_REG32_BIT(__DMACNT1,0x0100c80c,__READ_WRITE,__dmacnt_bits);

/***************************************************************************
 **
 **  Parallell port registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__PPDATA,0x0100b000,__READ_WRITE,__ppdata_bits);
__IO_REG32_BIT(__PPSTAT,0x0100b004,__READ_WRITE,__ppstat_bits);
__IO_REG32_BIT(__PPACKWTH,0x0100b008,__READ_WRITE,__ppackwth_bits);
__IO_REG32_BIT(__PPCON,0x0100b00c,__READ_WRITE,__ppcon_bits);
__IO_REG32_BIT(__PPINTEN,0x0100b010,__READ_WRITE,__ppi_bits);
__IO_REG32_BIT(__PPINTPND,0x0100b014,__READ_WRITE,__ppi_bits);


/***************************************************************************
 **
 **  UART registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__ULCON0,0x0100e000,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__ULCON1,0x0100e800,__READ_WRITE,__ulcon_bits);
__IO_REG32_BIT(__UCON0,0x0100e004,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__UCON1,0x0100e804,__READ_WRITE,__ucon_bits);
__IO_REG32_BIT(__USTAT0,0x0100e008,__READ,__ustat_bits);
__IO_REG32_BIT(__USTAT1,0x0100e808,__READ,__ustat_bits);
__IO_REG32_BIT(__UTXBUF0,0x0100e00c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__UTXBUF1,0x0100e80c,__WRITE,__utxbuf_bits);
__IO_REG32_BIT(__URXBUF0,0x0100e010,__READ,__urxbuf_bits);
__IO_REG32_BIT(__URXBUF1,0x0100e810,__READ,__urxbuf_bits);
__IO_REG32_BIT(__UBRDIV0,0x0100e014,__READ_WRITE,__ubrdiv_bits);
__IO_REG32_BIT(__UBRDIV1,0x0100e814,__READ_WRITE,__ubrdiv_bits);



/***************************************************************************
 **
 **  Tone generator registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__TONDATA,0x0100f004,__READ_WRITE,__tondata_bits);

/***************************************************************************
 **
 **  Watchdog timer registers  
 **
 ***************************************************************************/

__IO_REG32_BIT(__WTCNT,0x0100f804,__READ_WRITE,__wtcnt_bits);
__IO_REG32_BIT(__WTCON,0x0100f800,__READ_WRITE,__wtcon_bits);


/***************************************************************************
 **
 **  IO port registers  
 **
 ***************************************************************************/
__IO_REG32_BIT(__IOPMOD,0x01004808,__READ_WRITE,__iopmod_bits);
__IO_REG32_BIT(__IOPDATA,0x01004804,__READ_WRITE,__iopdata_bits);
__IO_REG32_BIT(__TSTCON,0x01004800,__READ_WRITE,__tstcon_bits);
__IO_REG32_BIT(__EERAMCON,0x01005000,__READ_WRITE,__eeramcon_bits);
__IO_REG32_BIT(__EOPA,0x01008004,__READ_WRITE,__eopa_bits);
__IO_REG32(__EOPL,0x01008000,__READ_WRITE);
__IO_REG32_BIT(__EOPB,0x01009010,__READ_WRITE,__eopb_bits);


/***************************************************************************
 **
 **  Interrupt controller Registers 
 **
 ***************************************************************************/
__IO_REG32_BIT(__INTMOD,0x01004000,__READ_WRITE,__intmod_bits);
__IO_REG32_BIT(__INTPND,0x01004004,__READ_WRITE,__intpndmsk_bits);
__IO_REG32_BIT(__INTMSK,0x01004008,__READ_WRITE,__intpndmsk_bits);

/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  KS32C6200 interrupt sources 
 **
 ***************************************************************************/
#define INT_EXT0    0  /* external interrupt 0                  */
#define INT_EXT1    1  /* external interrupt 1                  */
#define INT_WDTIMER 2  /* watchdog timer interrupt              */
#define INT_TXC1    3  /* UART channel 1 transmit interrupt     */
#define INT_TXC0    4  /* UART channel 0 transmit interrupt     */
#define INT_RXC1    5  /* UART channel 1 receive interrupt      */
#define INT_RXC0    6  /* UART channel 0 receive interrupt      */
#define INT_USR1    7  /* UART channel 1 error interrupt        */
#define INT_USR0    8  /* UART channel 0 error interrupt        */
#define INT_DMA1    9  /* DMA 1 interrupt                       */
#define INT_DMA0   10  /* DMA 0 interrupt                       */
#define INT_TIMER0 11  /* timer 0 interrupt                     */
#define INT_TIMER1 12  /* timer 1 interrupt                     */
#define INT_TIMER2 13  /* timer 2 interrupt                     */
#define INT_PP     14  /* parallell port interrupt              */

#endif    /* __KS32C6200_H */
