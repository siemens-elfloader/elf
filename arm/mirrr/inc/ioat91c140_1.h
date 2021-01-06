/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Atmel Semiconductors AT91C140
 **
 **    Used with ARM IAR c/c++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.1 $
 **
 ***************************************************************************/

#ifndef __IOAT91C140_H
#define __IOAT91C140_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"


/***************************************************************************
 ***************************************************************************
 **
 **    AT91C140 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* System Mode Register  */
typedef struct {
  __REG32 RM               : 1;
  __REG32                  : 5;
  __REG32 LP               : 1;
  __REG32 SA               : 1;
  __REG32 LPCS             : 2;
  __REG32                  :22;
} __sysmd_bits;

/* System Clock Status Register */
typedef struct {
  __REG32 ACLKST           : 1;
  __REG32                  :31; 
} __sysclkf_bits;


/* SDRAMC Mode Register */
typedef struct {
  __REG32                  : 6;
  __REG32 MODE             : 3;
  __REG32                  :23;
} __sdramcmr_bits;

/* SDRAMC Refresh Timer Register */
typedef struct {
  __REG32 COUNT            :12;
  __REG32                  :20;
} __sdramctr_bits;

/* SDRAMC Configuration Register */
typedef struct {
  __REG32 NC               : 2;
  __REG32 NR               : 2;
  __REG32 NB               : 1;
  __REG32                  : 2;
  __REG32 TWR              : 4;
  __REG32 TRC              : 4;
  __REG32 TRP              : 4;
  __REG32 TRCD             : 4;
  __REG32 TRAS             : 4;
  __REG32                  : 5;
} __sdramccr_bits;

/* SDRAMC Address Register  */
typedef struct {
  __REG32 SDCS_ADDR        : 8;
  __REG32                  :24;
} __sdramcaddr_bits;

/* SMC Chip Select Register */
typedef struct {
  __REG32 DBW              : 2;
  __REG32 NWS              : 3;
  __REG32 WSE              : 1;
  __REG32 MWS              : 1;
  __REG32 PAGES            : 2;
  __REG32 TDF              : 3;
  __REG32 BAT              : 1;
  __REG32 CSEN             : 1;
  __REG32                  : 6;
  __REG32 BA               :12;
} __smccsrx_bits;

/* SMC Memory Control Register */
typedef struct {
  __REG32                  : 4;
  __REG32 DRP              : 1;
  __REG32                  :27;
} __smcmcr_bits;

/* EMAC Control Register  */
typedef struct {
  __REG32 LB               : 1;
  __REG32 LBL              : 1;
  __REG32 RE               : 1;
  __REG32 TE               : 1;
  __REG32 MPE              : 1;
  __REG32 CSR              : 1;
  __REG32 ISR              : 1;
  __REG32 WES              : 1;
  __REG32 BP               : 1;
  __REG32                  :23;
} __ethctl_bits;

/* EMAC Mode Register */
typedef struct {
  __REG32 SPD              : 1;
  __REG32 FD               : 1;
  __REG32 BR               : 1;
  __REG32                  : 1;
  __REG32 CAF              : 1;
  __REG32 NBC              : 1;
  __REG32 MTI              : 1;
  __REG32 UNI              : 1;
  __REG32 BIG              : 1;
  __REG32 EAE              : 1;
  __REG32 CLK              : 2;
  __REG32 RTY              : 1;
  __REG32                  :19;
} __ethcfg_bits;

/* EMAC Status Register */
typedef struct {
  __REG32 LINK             : 1;
  __REG32 MDIO             : 1;
  __REG32 IDLE             : 1;
  __REG32                  :29;
} __ethsr_bits;

/* EMAC Transmit Control Register */
typedef struct {
  __REG32 LEN              :11;
  __REG32                  : 4;
  __REG32 NCRC             : 1;
  __REG32                  :16;
} __ethtcr_bits;

/* EMAC Transmit Status Register */
typedef struct {
  __REG32 OVR              : 1;
  __REG32 COL              : 1;
  __REG32 RLE              : 1;
  __REG32 IDLE             : 1;
  __REG32 BNQ              : 1;
  __REG32 COMP             : 1;
  __REG32 UND              : 1;
  __REG32                  :25;
} __ethtsr_bits;

/* EMAC Receive Status Register */
typedef struct {
  __REG32 BNA              : 1;
  __REG32 REC              : 1;
  __REG32 OVR              : 1;
  __REG32                  :29;
} __ethrsr_bits;

/* EMAC Interrupt Status Register */
/* EMAC Interrupt Enable Register */
/* EMAC Interrupt Disable Register */
/* EMAC Interrupt Mask Register */
typedef struct {
  __REG32 DONE             : 1;
  __REG32 RCOM             : 1;
  __REG32 RBNA             : 1;
  __REG32 TOVR             : 1;
  __REG32 TUND             : 1;
  __REG32 RTRY             : 1;
  __REG32 TBRE             : 1;
  __REG32 TCOM             : 1;
  __REG32 TIDLE            : 1;
  __REG32 LINK             : 1;
  __REG32 ROVR             : 1;
  __REG32 ABT              : 1;
  __REG32                  :20;
} __ethisr_bits;

/* EMAC PHY Maintenance Register  */
typedef struct {
  __REG32 DATA             :16;
  __REG32 CODE             : 2;
  __REG32 REGA             : 5;
  __REG32 PHYA             : 5;
  __REG32 RW               : 2;
  __REG32 HIGH             : 1;
  __REG32 LOW              : 1;
} __ethman_bits;

/* EMAC Specific Address (1, 2, 3 and 4) High Register */
typedef struct {
  __REG32 ADDR             :16;
  __REG32                  :16;
} __ethsaxh_bits;

/* EMAC Specific Address (1, 2, 3 and 4) Low Register */
typedef struct {
  __REG32 ADDR             :32; 
} __ethsaxl_bits;

/* AIC Source Mode Register  */
typedef struct {
  __REG32 PRIOR            : 3;
  __REG32                  : 2;
  __REG32 SRCTYPE          : 2;
  __REG32                  :25;
} __aicsmrx_bits;

/* AIC Interrupt Status Register */
typedef struct {
  __REG32 IRQID            : 5;
  __REG32                  :27;
} __aicisr_bits;

/* AIC Interrupt Pending Register */
/* AIC Interrupt Mask Register */
/* AIC Interrupt Enable Command Register */
/* AIC Interrupt Disable Command Register */
/* AIC Interrupt Clear Command Register */
/* AIC Interrupt Set Command Register */
typedef struct {
  __REG32 FIQ              : 1;
  __REG32                  : 1;
  __REG32 SWI              : 1;
  __REG32 UARTA            : 1;
  __REG32 TC0              : 1;
  __REG32 TC1              : 1;
  __REG32 TC2              : 1;
  __REG32 PIOA             : 1;
  __REG32 MACA             : 1;
  __REG32 SPI              : 1;
  __REG32 IRQ0             : 1;
  __REG32 IRQ1             : 1;
  __REG32                  : 1;
  __REG32 MACB             : 1;
  __REG32 UARTB            : 1;
  __REG32 PIOB             : 1;
  __REG32                  :16;
} __aicipr_bits;

/* AIC Core Interrupt Status Register */
typedef struct {
  __REG32 nFIQ             : 1;
  __REG32 NIRQ             : 1;
  __REG32                  :30;
} __aiccisr_bits;

/* PIO Enable Register */
/* PIO Disable Register */
/* PIO Status Register */
/* PIO Output Enable Register */
/* PIO Output Disable Register */
/* PIO Output Status Register */
/* PIO Set Output Data Register */
/* PIO Clear Output Data Register */
/* PIO Output Data Status Register */
/* PIO Pin Data Status Register */
/* PIO Interrupt Enable Register */
/* PIO Interrupt Disable Register */
/* PIO Interrupt Mask Register */
/* PIO Interrupt Status Register */
typedef struct {
  __REG32 P0               : 1;
  __REG32 P1               : 1;
  __REG32 P2               : 1;
  __REG32 P3               : 1;
  __REG32 P4               : 1;
  __REG32 P5               : 1;
  __REG32 P6               : 1;
  __REG32 P7               : 1;
  __REG32 P8               : 1;
  __REG32 P9               : 1;
  __REG32 P10              : 1;
  __REG32 P11              : 1;
  __REG32 P12              : 1;
  __REG32 P13              : 1;
  __REG32 P14              : 1;
  __REG32 P15              : 1;
  __REG32 P16              : 1;
  __REG32 P17              : 1;
  __REG32 P18              : 1;
  __REG32 P19              : 1;
  __REG32 P20              : 1;
  __REG32 P21              : 1;
  __REG32 P22              : 1;
  __REG32 P23              : 1;
  __REG32 P24              : 1;
  __REG32 P25              : 1;
  __REG32 P26              : 1;
  __REG32 P27              : 1;
  __REG32 P28              : 1;
  __REG32 P29              : 1;
  __REG32 P30              : 1;
  __REG32 P31              : 1;
} __pioper_bits;

/* UART Control Register */
typedef struct {
  __REG32                  : 2;
  __REG32 RSTRX            : 1;
  __REG32 RSTTX            : 1;
  __REG32 RXEN             : 1;
  __REG32 RXDIS            : 1;
  __REG32 TXEN             : 1;
  __REG32 TXDIS            : 1;
  __REG32 RSTSTA           : 1;
  __REG32                  :23;
} __uscr_bits;

/* UART Mode Register */
typedef struct {
  __REG32                  : 4;
  __REG32 USCLKS           : 2;
  __REG32 CHRL             : 2;
  __REG32                  : 1;
  __REG32 PAR              : 3;
  __REG32 NBSTOP           : 2;
  __REG32 CHMODE           : 2;
  __REG32                  :16;
} __usmr_bits;

/* UART Interrupt Enable Register */
/* UART Interrupt Disable Register */
/* UART Channel Status Register */
typedef struct {
  __REG32 RXRDY            : 1;
  __REG32 TXRDY            : 1;
  __REG32                  : 1;
  __REG32 ENDRX            : 1;
  __REG32 ENDTX            : 1;
  __REG32 OVRE             : 1;
  __REG32 FRAME            : 1;
  __REG32 PARE             : 1;
  __REG32                  : 1;
  __REG32 TXEMPTY          : 1;
  __REG32 DMSI             : 1;
  __REG32                  :21;
} __usier_bits;

/* UART Interrupt Mask Register */
typedef struct {
  __REG32 RXRDY            : 1;
  __REG32                  : 1;
  __REG32 RXBRK            : 1;
  __REG32 ENDRX            : 1;
  __REG32 ENDTX            : 1;
  __REG32 OVRE             : 1;
  __REG32 FRAME            : 1;
  __REG32 PARE             : 1;
  __REG32                  : 1;
  __REG32 TXEMPTY          : 1;
  __REG32 DMSI             : 1;
  __REG32                  :21;
} __usimr_bits;

/* UART Receiver Holding Register */
typedef struct {
  __REG32 RXCHR            : 8;
  __REG32                  :24;
} __usrhr_bits;

/* UART Transmitter Holding Register */
typedef struct {
  __REG32 TXCHR            : 8;
  __REG32                  :24;
} __usthr_bits;

/* UART Baud Rate Generator Register */
typedef struct {
  __REG32 CD               :16;
  __REG32                  :16;
} __usbrgr_bits;

/* UART Receive Counter Register */
typedef struct {
  __REG32 RXCTR            :16;
  __REG32                  :16;
} __usrcr_bits;

/* UART Transmit Counter Register */
typedef struct {
  __REG32 TXCTR            :16;
  __REG32                  :16;
} __ustcr_bits;

/* Modem Control Register */
typedef struct {
  __REG32 DTR              : 1;
  __REG32 RTS              : 1;
  __REG32                  :30;
} __usmc_bits;

/* Modem Status Register */
typedef struct {
  __REG32 DCTS             : 1;
  __REG32 DDSR             : 1;
  __REG32 TERI             : 1;
  __REG32 DDCD             : 1;
  __REG32 CTS              : 1;
  __REG32 DSR              : 1;
  __REG32 RI               : 1;
  __REG32 DCD              : 1;
  __REG32                  :24;
} __usms_bits;

/* TC Block Control Register */
typedef struct {
  __REG32 SYNC             : 1;
  __REG32                  :31;
} __tcbcr_bits;

/* TC Block Mode Register */
typedef struct {
  __REG32 TC0XC0S          : 2;
  __REG32 TC1XC1S          : 2;
  __REG32 TC2XC2S          : 2;
  __REG32                  :26;
} __tcbmr_bits;

/* TC Channel Control Register */
typedef struct {
  __REG32 CLKEN            : 1;
  __REG32 CLKDIS           : 1;
  __REG32 SWTRG            : 1;
  __REG32                  :29;
} __tcccr_bits;

/* TC Channel Mode Register: Capture Mode */
/* TC Channel Mode Register: Waveform Mode */
typedef union {
  //TC_CMR_0 TC_CMR_1 TC_CMR_2
  struct {
    __REG32 TCCLKS           : 3;
    __REG32 CLKI             : 1;
    __REG32 BURST            : 2;
    __REG32 LDBSTOP          : 1;
    __REG32 LDBDIS           : 1;
    __REG32 ETRGEDG          : 2;
    __REG32 ABETRG           : 1;
    __REG32                  : 3;
    __REG32 CPCTRG           : 1;
    __REG32 WAVE             : 1;
    __REG32 LDRA             : 2;
    __REG32 LDRB             : 2;
    __REG32                  :12;
  };
  //TC_CMR_0 TC_CMR_1 TC_CMR_2
  struct {
    __REG32                  : 3;
    __REG32                  : 1;
    __REG32                  : 2;
    __REG32 CPCSTOP          : 1;
    __REG32 CPCDIS           : 1;
    __REG32 EEVTEDG          : 2;
    __REG32 EEVT             : 2;
    __REG32 ENETRG           : 1;
    __REG32                  : 1;
    __REG32                  : 1;
    __REG32                  : 1;
    __REG32 ACPA             : 2;
    __REG32 ACPC             : 2;
    __REG32 AEEVT            : 2;
    __REG32 ASWTRG           : 2;
    __REG32 BCPB             : 2;
    __REG32 BCPC             : 2;
    __REG32 BEEVT            : 2;
    __REG32 BSWTRG           : 2;
  };
} __tccmr_bits;

/* TC Counter Value Register */
typedef struct {
  __REG32 CV               :16;
  __REG32                  :16;
} __tccvr_bits;

/* TC Register A */
typedef struct {
  __REG32 RA               :16;
  __REG32                  :16;
} __tcra_bits;

/* TC Register B */
typedef struct {
  __REG32 RB               :16;
  __REG32                  :16;
} __tcrb_bits;

/* TC Register C */
typedef struct {
  __REG32 RC               :16;
  __REG32                  :16;
} __tcrc_bits;

/* TC Status Register */
typedef struct {
  __REG32 COVFS            : 1;
  __REG32 LOVRS            : 1;
  __REG32 CPAS             : 1;
  __REG32 CPBS             : 1;
  __REG32 CPCS             : 1;
  __REG32 LDRAS            : 1;
  __REG32 LDRBS            : 1;
  __REG32 ETRGS            : 1;
  __REG32                  : 8;
  __REG32 CLKSTA           : 1;
  __REG32 MTIOA            : 1;
  __REG32 MTIOB            : 1;
  __REG32                  :13;
} __tcsr_bits;

/* TC Interrupt Enable Register */
/* TC Interrupt Disable Register */
/* TC Interrupt Mask Register */
typedef struct {
  __REG32 COVFS            : 1;
  __REG32 LOVRS            : 1;
  __REG32 CPAS             : 1;
  __REG32 CPBS             : 1;
  __REG32 CPCS             : 1;
  __REG32 LDRAS            : 1;
  __REG32 LDRBS            : 1;
  __REG32 ETRGS            : 1;
  __REG32                  : 24;
} __tcier_bits;

/* SPI Control Register */
typedef struct {
  __REG32 SPIEN            : 1;
  __REG32 SPIDIS           : 1;
  __REG32                  : 5;
  __REG32 SWRST            : 1;
  __REG32                  :24;
} __spicr_bits;

/* SPI Mode Register */
typedef struct {
  __REG32 MSTR             : 1;
  __REG32 PS               : 1;
  __REG32 PCSDEC           : 1;
  __REG32 DIV32            : 1;
  __REG32 MODFDIS          : 1;
  __REG32                  : 2;
  __REG32 LLB              : 1;
  __REG32                  : 8;
  __REG32 PCS              : 4;
  __REG32                  : 4;
  __REG32 DLYBCS           : 8;
} __spimr_bits;

/* SPI Receive Data Register */
typedef struct {
  __REG32 RD               :16;
  __REG32 PCS              : 4;
  __REG32                  :12;
} __spirdr_bits;

/* SPI Transmit Data Register */
typedef struct {
  __REG32 TD               :16;
  __REG32 PCS              : 4;
  __REG32                  :12;
} __spitdr_bits;

/* SPI Status Register */
typedef struct {
  __REG32 RDRF             : 1;
  __REG32 TDRE             : 1;
  __REG32 MODF             : 1;
  __REG32 OVRES            : 1;
  __REG32 ENDRX            : 1;
  __REG32 ENDTX            : 1;
  __REG32                  :10;
  __REG32 SPIENS           : 1;
  __REG32                  :15;
} __spisr_bits;

/* SPI Interrupt Enable Register */
/* SPI Interrupt Disable Register */
/* SPI Interrupt Mask Register */
typedef struct {
  __REG32 RDRF             : 1;
  __REG32 TDRE             : 1;
  __REG32 MODF             : 1;
  __REG32 OVRES            : 1;
  __REG32 ENDRX            : 1;
  __REG32 ENDTX            : 1;
  __REG32                  :26;
} __spiier_bits;

/* SPI Chip Select Register */
typedef struct {
  __REG32 CPOL             : 1;
  __REG32 NCPHA            : 1;
  __REG32                  : 2;
  __REG32 BITS             : 4;
  __REG32 SCBR             : 8;
  __REG32 DLYBS            : 8;
  __REG32 DLYBCT           : 8;
} __spicsrx_bits;

/* SPI Receive Counter Register */
typedef struct {
  __REG32 RXCTR            :16;
  __REG32                  :16;
} __spircr_bits;

/* SPI Transmit Counter Register */
typedef struct {
  __REG32 TXCTR            :16;
  __REG32                  :16;
} __spitcr_bits;


#endif	/* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/

/***************************************************************************
 **
 ** System Controller (SYSC)
 **
 ***************************************************************************/
__IO_REG32_BIT(SYS_MD,        0xFF000000, __READ_WRITE, __sysmd_bits  );
__IO_REG32(    SYS_ID,        0xFF000004, __READ                      );
__IO_REG32_BIT(SYS_CLKF,      0xFF00000C, __READ      , __sysclkf_bits);

/***************************************************************************
 **
 ** Static Memory Controller (SMC)
 **
 ***************************************************************************/
__IO_REG32_BIT(SMC_CSR0,      0xFF004000, __READ_WRITE, __smccsrx_bits     );
__IO_REG32_BIT(SMC_CSR1,      0xFF004004, __READ_WRITE, __smccsrx_bits     );
__IO_REG32_BIT(SMC_CSR2,      0xFF004008, __READ_WRITE, __smccsrx_bits     );
__IO_REG32_BIT(SMC_CSR3,      0xFF00400C, __READ_WRITE, __smccsrx_bits     );
__IO_REG32_BIT(SMC_MCR,       0xFF004024, __READ_WRITE, __smcmcr_bits      );

/***************************************************************************
 **
 ** SDRAM Controller (SDRAMC)
 **
 ***************************************************************************/
__IO_REG32_BIT(SDRAMC_MR,     0xFF008000, __READ_WRITE, __sdramcmr_bits    );
__IO_REG32_BIT(SDRAMC_TR,     0xFF008004, __READ_WRITE, __sdramctr_bits    );
__IO_REG32_BIT(SDRAMC_CR,     0xFF008008, __READ_WRITE, __sdramccr_bits    );
__IO_REG32(    SDRAM_16BIT,   0xFF00800C, __READ_WRITE                     );
__IO_REG32_BIT(SDRAMC_ADDR,   0xFF008010, __READ_WRITE, __sdramcaddr_bits  );

/***************************************************************************
 **
 ** Parallel I/O Controller A (PIOA)
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOA_PER,       0xFF00C000, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_PDR,       0xFF00C004, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_PSR,       0xFF00C008, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOA_OER,       0xFF00C010, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_ODR,       0xFF00C014, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_OSR,       0xFF00C018, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOA_SODR,      0xFF00C030, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_CODR,      0xFF00C034, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_ODSR,      0xFF00C038, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOA_PDSR,      0xFF00C03C, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOA_IER,       0xFF00C040, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_IDR,       0xFF00C044, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOA_IMR,       0xFF00C048, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOA_ISR,       0xFF00C04C, __READ      , __pioper_bits);

/***************************************************************************
 **
 ** Parallel I/O Controller B (PIOB)
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOB_PER,       0xFF010000, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_PDR,       0xFF010004, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_PSR,       0xFF010008, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOB_OER,       0xFF010010, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_ODR,       0xFF010014, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_OSR,       0xFF010018, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOB_SODR,      0xFF010030, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_CODR,      0xFF010034, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_ODSR,      0xFF010038, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOB_PDSR,      0xFF01003C, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOB_IER,       0xFF010040, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_IDR,       0xFF010044, __WRITE     , __pioper_bits);
__IO_REG32_BIT(PIOB_IMR,       0xFF010048, __READ      , __pioper_bits);
__IO_REG32_BIT(PIOB_ISR,       0xFF01004C, __READ      , __pioper_bits);

/***************************************************************************
 **
 ** Timer / Counter (TC)
 **
 ***************************************************************************/
__IO_REG32_BIT(TC_CCR_0,       0xFF014000, __WRITE     , __tcccr_bits);
__IO_REG32_BIT(TC_CMR_0,       0xFF014004, __READ_WRITE, __tccmr_bits);
__IO_REG32_BIT(TC_CVR_0,       0xFF014010, __READ_WRITE, __tccvr_bits);
__IO_REG32_BIT(TC_RA_0,        0xFF014014, __READ_WRITE, __tcra_bits );
__IO_REG32_BIT(TC_RB_0,        0xFF014018, __READ_WRITE, __tcrb_bits );
__IO_REG32_BIT(TC_RC_0,        0xFF01401C, __READ_WRITE, __tcrc_bits );
__IO_REG32_BIT(TC_SR_0,        0xFF014020, __READ      , __tcsr_bits );
__IO_REG32_BIT(TC_IER_0,       0xFF014024, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_IDR_0,       0xFF014028, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_IMR_0,       0xFF01402C, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_CCR_1,       0xFF014040, __WRITE     , __tcccr_bits);
__IO_REG32_BIT(TC_CMR_1,       0xFF014044, __READ_WRITE, __tccmr_bits);
__IO_REG32_BIT(TC_CVR_1,       0xFF014050, __READ_WRITE, __tccvr_bits);
__IO_REG32_BIT(TC_RA_1,        0xFF014054, __READ_WRITE, __tcra_bits );
__IO_REG32_BIT(TC_RB_1,        0xFF014058, __READ_WRITE, __tcrb_bits );
__IO_REG32_BIT(TC_RC_1,        0xFF01405C, __READ_WRITE, __tcrc_bits );
__IO_REG32_BIT(TC_SR_1,        0xFF014060, __READ      , __tcsr_bits );
__IO_REG32_BIT(TC_IER_1,       0xFF014064, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_IDR_1,       0xFF014068, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_IMR_1,       0xFF01406C, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_CCR_2,       0xFF014080, __WRITE     , __tcccr_bits);
__IO_REG32_BIT(TC_CMR_2,       0xFF014084, __READ_WRITE, __tccmr_bits);
__IO_REG32_BIT(TC_CVR_2,       0xFF014090, __READ_WRITE, __tccvr_bits);
__IO_REG32_BIT(TC_RA_2,        0xFF014094, __READ_WRITE, __tcra_bits );
__IO_REG32_BIT(TC_RB_2,        0xFF014098, __READ_WRITE, __tcrb_bits );
__IO_REG32_BIT(TC_RC_2,        0xFF01409C, __READ_WRITE, __tcrc_bits );
__IO_REG32_BIT(TC_SR_2,        0xFF0140A0, __READ      , __tcsr_bits );
__IO_REG32_BIT(TC_IER_2,       0xFF0140A4, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_IDR_2,       0xFF0140A8, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_IMR_2,       0xFF0140AC, __WRITE     , __tcier_bits);
__IO_REG32_BIT(TC_BCR,         0xFF0140C0, __WRITE     , __tcbcr_bits);
__IO_REG32_BIT(TC_BMR,         0xFF0140C4, __READ_WRITE, __tcbmr_bits);

/***************************************************************************
 **
 ** Universal Asynchronous Receiver Transmitter A (UARTA)
 **
 ***************************************************************************/
__IO_REG32_BIT(US_CR_A,        0xFF018000, __WRITE     , __uscr_bits  );
__IO_REG32_BIT(US_MR_A,        0xFF018004, __READ_WRITE, __usmr_bits  );
__IO_REG32_BIT(US_IER_A,       0xFF018008, __WRITE     , __usier_bits );
__IO_REG32_BIT(US_IDR_A,       0xFF01800C, __WRITE     , __usier_bits );
__IO_REG32_BIT(US_IMR_A,       0xFF018010, __READ      , __usimr_bits );
__IO_REG32_BIT(US_CSR_A,       0xFF018014, __READ      , __usier_bits );
__IO_REG32_BIT(US_RHR_A,       0xFF018018, __READ      , __usrhr_bits );
__IO_REG32_BIT(US_THR_A,       0xFF01801C, __WRITE     , __usthr_bits );
__IO_REG32_BIT(US_BRGR_A,      0xFF018020, __READ_WRITE, __usbrgr_bits);
__IO_REG32(    US_RTOR_A,      0xFF018024, __READ_WRITE               );
__IO_REG32(    US_TTGR_A,      0xFF018028, __READ_WRITE               );
__IO_REG32(    US_RPR_A,       0xFF018030, __READ_WRITE               );
__IO_REG32_BIT(US_RCR_A,       0xFF018034, __READ_WRITE, __usrcr_bits );
__IO_REG32(    US_TPR_A,       0xFF018038, __READ_WRITE               );
__IO_REG32_BIT(US_TCR_A,       0xFF01803C, __READ_WRITE, __ustcr_bits);
__IO_REG32_BIT(US_MC_A,        0xFF018040, __WRITE     , __usmc_bits  );
__IO_REG32_BIT(US_MS_A,        0xFF018044, __READ      , __usms_bits  );

/***************************************************************************
 **
 ** Universal Asynchronous Receiver Transmitter B (UARTB)
 **
 ***************************************************************************/
__IO_REG32_BIT(US_CR_B,        0xFF01C000, __WRITE     , __uscr_bits  );
__IO_REG32_BIT(US_MR_B,        0xFF01C004, __READ_WRITE, __usmr_bits  );
__IO_REG32_BIT(US_IER_B,       0xFF01C008, __WRITE     , __usier_bits );
__IO_REG32_BIT(US_IDR_B,       0xFF01C00C, __WRITE     , __usier_bits );
__IO_REG32_BIT(US_IMR_B,       0xFF01C010, __READ      , __usimr_bits );
__IO_REG32_BIT(US_CSR_B,       0xFF01C014, __READ      , __usier_bits );
__IO_REG32_BIT(US_RHR_B,       0xFF01C018, __READ      , __usrhr_bits );
__IO_REG32_BIT(US_THR_B,       0xFF01C01C, __WRITE     , __usthr_bits );
__IO_REG32_BIT(US_BRGR_B,      0xFF01C020, __READ_WRITE, __usbrgr_bits);
__IO_REG32(    US_RTOR_B,      0xFF01C024, __READ_WRITE               );
__IO_REG32(    US_TTGR_B,      0xFF01C028, __READ_WRITE               );

__IO_REG32(    US_RPR_B,       0xFF01C030, __READ_WRITE               );
__IO_REG32_BIT(US_RCR_B,       0xFF01C034, __READ_WRITE, __usrcr_bits );
__IO_REG32(    US_TPR_B,       0xFF01C038, __READ_WRITE               );
__IO_REG32_BIT(US_TCR_B,       0xFF01C03C, __READ_WRITE, __ustcr_bits);
__IO_REG32_BIT(US_MC_B,        0xFF01C040, __WRITE     , __usmc_bits  );
__IO_REG32_BIT(US_MS_B,        0xFF01C044, __READ      , __usms_bits  );

/***************************************************************************
 **
 ** Serial Peripheral Interface (SPI)
 **
 ***************************************************************************/
__IO_REG32_BIT(SPI_CR,         0xFF020000, __WRITE     , __spicr_bits  );
__IO_REG32_BIT(SPI_MR,         0xFF020004, __READ_WRITE, __spimr_bits  );
__IO_REG32_BIT(SPI_RDR,        0xFF020008, __READ      , __spirdr_bits );
__IO_REG32_BIT(SPI_TDR,        0xFF02000C, __WRITE     , __spitdr_bits );
__IO_REG32_BIT(SPI_SR,         0xFF020010, __READ      , __spisr_bits  );
__IO_REG32_BIT(SPI_IER,        0xFF020014, __WRITE     , __spiier_bits );
__IO_REG32_BIT(SPI_IDR,        0xFF020018, __WRITE     , __spiier_bits );
__IO_REG32_BIT(SPI_IMR,        0xFF02001C, __READ      , __spiier_bits );
__IO_REG32(    SPI_RPR,        0xFF020020, __READ_WRITE                );
__IO_REG32_BIT(SPI_RCR,        0xFF020024, __READ_WRITE, __spircr_bits );
__IO_REG32(    SPI_TPR,        0xFF020028, __READ_WRITE                );
__IO_REG32_BIT(SPI_TCR,        0xFF02002C, __READ_WRITE, __spitcr_bits );
__IO_REG32_BIT(SPI_CSR0,       0xFF020030, __READ_WRITE, __spicsrx_bits);
__IO_REG32_BIT(SPI_CSR1,       0xFF020034, __READ_WRITE, __spicsrx_bits);
__IO_REG32_BIT(SPI_CSR2,       0xFF020038, __READ_WRITE, __spicsrx_bits);
__IO_REG32_BIT(SPI_CSR3,       0xFF02003C, __READ_WRITE, __spicsrx_bits);

/***************************************************************************
 **
 ** Advanced Interrupt Controller (AIC)
 **
 ***************************************************************************/
__IO_REG32_BIT(AIC_SMR0,      0xFF030000, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR1,      0xFF030004, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR2,      0xFF030008, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR3,      0xFF03000C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR4,      0xFF030010, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR5,      0xFF030014, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR6,      0xFF030018, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR7,      0xFF03001C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR8,      0xFF030020, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR9,      0xFF030024, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR10,     0xFF030028, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR11,     0xFF03002C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR12,     0xFF030030, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR13,     0xFF030034, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR14,     0xFF030038, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR15,     0xFF03003C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR16,     0xFF030040, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR17,     0xFF030044, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR18,     0xFF030048, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR19,     0xFF03004C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR20,     0xFF030050, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR21,     0xFF030054, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR22,     0xFF030058, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR23,     0xFF03005C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR24,     0xFF030060, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR25,     0xFF030064, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR26,     0xFF030068, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR27,     0xFF03006C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR28,     0xFF030070, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR29,     0xFF030074, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR30,     0xFF030078, __READ_WRITE, __aicsmrx_bits);
__IO_REG32_BIT(AIC_SMR31,     0xFF03007C, __READ_WRITE, __aicsmrx_bits);
__IO_REG32(    AIC_SVR0,      0xFF030080, __READ_WRITE                );
__IO_REG32(    AIC_SVR1,      0xFF030084, __READ_WRITE                );
__IO_REG32(    AIC_SVR2,      0xFF030088, __READ_WRITE                );
__IO_REG32(    AIC_SVR3,      0xFF03008C, __READ_WRITE                );
__IO_REG32(    AIC_SVR4,      0xFF030090, __READ_WRITE                );
__IO_REG32(    AIC_SVR5,      0xFF030094, __READ_WRITE                );
__IO_REG32(    AIC_SVR6,      0xFF030098, __READ_WRITE                );
__IO_REG32(    AIC_SVR7,      0xFF03009C, __READ_WRITE                );
__IO_REG32(    AIC_SVR8,      0xFF0300A0, __READ_WRITE                );
__IO_REG32(    AIC_SVR9,      0xFF0300A4, __READ_WRITE                );
__IO_REG32(    AIC_SVR10,     0xFF0300A8, __READ_WRITE                );
__IO_REG32(    AIC_SVR11,     0xFF0300AC, __READ_WRITE                );
__IO_REG32(    AIC_SVR12,     0xFF0300B0, __READ_WRITE                );
__IO_REG32(    AIC_SVR13,     0xFF0300B4, __READ_WRITE                );
__IO_REG32(    AIC_SVR14,     0xFF0300B8, __READ_WRITE                );
__IO_REG32(    AIC_SVR15,     0xFF0300BC, __READ_WRITE                );
__IO_REG32(    AIC_SVR16,     0xFF0300C0, __READ_WRITE                );
__IO_REG32(    AIC_SVR17,     0xFF0300C4, __READ_WRITE                );
__IO_REG32(    AIC_SVR18,     0xFF0300C8, __READ_WRITE                );
__IO_REG32(    AIC_SVR19,     0xFF0300CC, __READ_WRITE                );
__IO_REG32(    AIC_SVR20,     0xFF0300D0, __READ_WRITE                );
__IO_REG32(    AIC_SVR21,     0xFF0300D4, __READ_WRITE                );
__IO_REG32(    AIC_SVR22,     0xFF0300D8, __READ_WRITE                );
__IO_REG32(    AIC_SVR23,     0xFF0300DC, __READ_WRITE                );
__IO_REG32(    AIC_SVR24,     0xFF0300E0, __READ_WRITE                );
__IO_REG32(    AIC_SVR25,     0xFF0300E4, __READ_WRITE                );
__IO_REG32(    AIC_SVR26,     0xFF0300E8, __READ_WRITE                );
__IO_REG32(    AIC_SVR27,     0xFF0300EC, __READ_WRITE                );
__IO_REG32(    AIC_SVR28,     0xFF0300F0, __READ_WRITE                );
__IO_REG32(    AIC_SVR29,     0xFF0300F4, __READ_WRITE                );
__IO_REG32(    AIC_SVR30,     0xFF0300F8, __READ_WRITE                );
__IO_REG32(    AIC_SVR31,     0xFF0300FC, __READ_WRITE                );
__IO_REG32(    AIC_IVR,       0xFF030100, __READ                      );
__IO_REG32(    AIC_FVR,       0xFF030104, __READ                      );
__IO_REG32_BIT(AIC_ISR,       0xFF030108, __READ      , __aicisr_bits );
__IO_REG32_BIT(AIC_IPR,       0xFF03010C, __READ      , __aicipr_bits );
__IO_REG32_BIT(AIC_IMR,       0xFF030110, __READ      , __aicipr_bits );
__IO_REG32_BIT(AIC_CISR,      0xFF030114, __READ      , __aiccisr_bits);
__IO_REG32_BIT(AIC_IECR,      0xFF030120, __WRITE     , __aicipr_bits );
__IO_REG32_BIT(AIC_IDCR,      0xFF030124, __WRITE     , __aicipr_bits );
__IO_REG32_BIT(AIC_ICCR,      0xFF030128, __WRITE     , __aicipr_bits );
__IO_REG32_BIT(AIC_ISCR,      0xFF03012C, __WRITE     , __aicipr_bits );
__IO_REG32(    AIC_EOICR,     0xFF030130, __WRITE                     );
__IO_REG32(    AIC_SPU,       0xFF030134, __READ_WRITE                );

/***************************************************************************
 **
 ** Ethernet MAC A (EMAC)
 **
 ***************************************************************************/
__IO_REG32_BIT(ETH_CTL_A,     0xFF034000, __READ_WRITE, __ethctl_bits );
__IO_REG32_BIT(ETH_CFG_A,     0xFF034004, __READ_WRITE, __ethcfg_bits );
__IO_REG32_BIT(ETH_SR_A,      0xFF034008, __READ      , __ethsr_bits  );
__IO_REG32(    ETH_TAR_A,     0xFF03400C, __READ_WRITE                );
__IO_REG32_BIT(ETH_TCR_A,     0xFF034010, __READ_WRITE, __ethtcr_bits );
__IO_REG32_BIT(ETH_TSR_A,     0xFF034014, __READ_WRITE, __ethtsr_bits );
__IO_REG32(    ETH_RBQP_A,    0xFF034018, __READ_WRITE                );
__IO_REG32_BIT(ETH_RSR_A,     0xFF034020, __READ_WRITE, __ethrsr_bits );
__IO_REG32_BIT(ETH_ISR_A,     0xFF034024, __READ_WRITE, __ethisr_bits );
__IO_REG32_BIT(ETH_IER_A,     0xFF034028, __WRITE     , __ethisr_bits );
__IO_REG32_BIT(ETH_IDR_A,     0xFF03402C, __WRITE     , __ethisr_bits );
__IO_REG32_BIT(ETH_IMR_A,     0xFF034030, __READ      , __ethisr_bits );
__IO_REG32_BIT(ETH_MAN_A,     0xFF034034, __READ_WRITE, __ethman_bits );
__IO_REG32(    ETH_FRA_A,     0xFF034040, __READ_WRITE                );
__IO_REG32(    ETH_SCOL_A,    0xFF034044, __READ_WRITE                );
__IO_REG32(    ETH_MCOL_A,    0xFF034048, __READ_WRITE                );
__IO_REG32(    ETH_OK_A,      0xFF03404C, __READ_WRITE                );
__IO_REG32(    ETH_SEQE_A,    0xFF034050, __READ_WRITE                );
__IO_REG32(    ETH_ALE_A,     0xFF034054, __READ_WRITE                );
__IO_REG32(    ETH_DTE_A,     0xFF034058, __READ_WRITE                );
__IO_REG32(    ETH_LCOL_A,    0xFF03405C, __READ_WRITE                );
__IO_REG32(    ETH_ECOL_A,    0xFF034060, __READ_WRITE                );
__IO_REG32(    ETH_CSE_A,     0xFF034064, __READ_WRITE                );
__IO_REG32(    ETH_TUE_A,     0xFF034068, __READ_WRITE                );
__IO_REG32(    ETH_CDE_A,     0xFF03406C, __READ_WRITE                );
__IO_REG32(    ETH_ELR_A,     0xFF034070, __READ_WRITE                );
__IO_REG32(    ETH_RJB_A,     0xFF034074, __READ_WRITE                );
__IO_REG32(    ETH_USF_A,     0xFF034078, __READ_WRITE                );
__IO_REG32(    ETH_SQEE_A,    0xFF03407C, __READ_WRITE                );
__IO_REG32(    ETH_DRFC_A,    0xFF034080, __READ_WRITE                );
__IO_REG32(    ETH_HSH_A,     0xFF034090, __READ_WRITE                );
__IO_REG32(    ETH_HSL_A,     0xFF034094, __READ_WRITE                );
__IO_REG32_BIT(ETH_SA1L_A,    0xFF034098, __READ_WRITE, __ethsaxl_bits);
__IO_REG32_BIT(ETH_SA1H_A,    0xFF03409C, __READ_WRITE, __ethsaxh_bits);
__IO_REG32_BIT(ETH_SA2L_A,    0xFF0340A0, __READ_WRITE, __ethsaxl_bits);
__IO_REG32_BIT(ETH_SA2H_A,    0xFF0340A4, __READ_WRITE, __ethsaxh_bits);
__IO_REG32_BIT(ETH_SA3L_A,    0xFF0340A8, __READ_WRITE, __ethsaxl_bits);
__IO_REG32_BIT(ETH_SA3H_A,    0xFF0340AC, __READ_WRITE, __ethsaxh_bits);
__IO_REG32_BIT(ETH_SA4L_A,    0xFF0340B0, __READ_WRITE, __ethsaxl_bits);
__IO_REG32_BIT(ETH_SA4H_A,    0xFF0340B4, __READ_WRITE, __ethsaxh_bits);

/***************************************************************************
 **
 ** Ethernet MAC B (EMAC)
 **
 ***************************************************************************/
__IO_REG32_BIT(ETH_CTL_B,     0xFF038000, __READ_WRITE, __ethctl_bits);
__IO_REG32_BIT(ETH_CFG_B,     0xFF038004, __READ_WRITE, __ethcfg_bits);
__IO_REG32_BIT(ETH_SR_B,      0xFF038008, __READ      , __ethsr_bits );
__IO_REG32(    ETH_TAR_B,     0xFF03800C, __READ_WRITE               );
__IO_REG32_BIT(ETH_TCR_B,     0xFF038010, __READ_WRITE, __ethtcr_bits);
__IO_REG32_BIT(ETH_TSR_B,     0xFF038014, __READ_WRITE, __ethtsr_bits);
__IO_REG32(    ETH_RBQP_B,    0xFF038018, __READ_WRITE               );
__IO_REG32_BIT(ETH_RSR_B,     0xFF038020, __READ_WRITE, __ethrsr_bits);
__IO_REG32_BIT(ETH_ISR_B,     0xFF038024, __READ_WRITE, __ethisr_bits);
__IO_REG32_BIT(ETH_IER_B,     0xFF038028, __WRITE     , __ethisr_bits);
__IO_REG32_BIT(ETH_IDR_B,     0xFF03802C, __WRITE     , __ethisr_bits);
__IO_REG32_BIT(ETH_IMR_B,     0xFF038030, __READ      , __ethisr_bits);
__IO_REG32_BIT(ETH_MAN_B,     0xFF038034, __READ_WRITE, __ethman_bits);
__IO_REG32(    ETH_FRA_B,     0xFF038040, __READ_WRITE               );
__IO_REG32(    ETH_SCOL_B,    0xFF038044, __READ_WRITE               );
__IO_REG32(    ETH_MCOL_B,    0xFF038048, __READ_WRITE               );
__IO_REG32(    ETH_OK_B,      0xFF03804C, __READ_WRITE               );
__IO_REG32(    ETH_SEQE_B,    0xFF038050, __READ_WRITE               );
__IO_REG32(    ETH_ALE_B,     0xFF038054, __READ_WRITE               );
__IO_REG32(    ETH_DTE_B,     0xFF038058, __READ_WRITE               );
__IO_REG32(    ETH_LCOL_B,    0xFF03805C, __READ_WRITE               );
__IO_REG32(    ETH_ECOL_B,    0xFF038060, __READ_WRITE               );
__IO_REG32(    ETH_CSE_B,     0xFF038064, __READ_WRITE               );
__IO_REG32(    ETH_TUE_B,     0xFF038068, __READ_WRITE               );
__IO_REG32(    ETH_CDE_B,     0xFF03806C, __READ_WRITE               );
__IO_REG32(    ETH_ELR_B,     0xFF038070, __READ_WRITE               );
__IO_REG32(    ETH_RJB_B,     0xFF038074, __READ_WRITE               );
__IO_REG32(    ETH_USF_B,     0xFF038078, __READ_WRITE               );
__IO_REG32(    ETH_SQEE_B,    0xFF03807C, __READ_WRITE               );
__IO_REG32(    ETH_DRFC_B,    0xFF038080, __READ_WRITE               );
__IO_REG32(    ETH_HSH_B,     0xFF038090, __READ_WRITE               );
__IO_REG32(    ETH_HSL_B,     0xFF038094, __READ_WRITE               );
__IO_REG32(    ETH_SA1L_B,    0xFF038098, __READ_WRITE               );
__IO_REG32(    ETH_SA1H_B,    0xFF03809C, __READ_WRITE               );
__IO_REG32(    ETH_SA2L_B,    0xFF0380A0, __READ_WRITE               );
__IO_REG32(    ETH_SA2H_B,    0xFF0380A4, __READ_WRITE               );
__IO_REG32(    ETH_SA3L_B,    0xFF0380A8, __READ_WRITE               );
__IO_REG32(    ETH_SA3H_B,    0xFF0380AC, __READ_WRITE               );
__IO_REG32(    ETH_SA4L_B,    0xFF0380B0, __READ_WRITE               );
__IO_REG32(    ETH_SA4H_B,    0xFF0380B4, __READ_WRITE               );

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 ** AT91C140 Interrupt Codes
 **
 ***************************************************************************/
#define INO_FIQ        0
#define INO_SWI        2
#define INO_UARTA      3
#define INO_TC0        4
#define INO_TC1        5
#define INO_TC2        6
#define INO_PIOA       7
#define INO_MACA       8
#define INO_SPI        9
#define INO_IRQ0      10
#define INO_IRQ1      11
#define INO_MACB      13
#define INO_UARTB     14
#define INO_PIOB      15


#endif	/* __IOAT91C140_H */



