/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Atmel Semiconductors AT91RM3400
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.3 $
 **
 ***************************************************************************/ 

#ifndef __IOAT91RM3400_H
#define __IOAT91RM3400_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    AT91RM3400 PERIPHERAL MEMORY MAP
 **
 ***************************************************************************
 ***************************************************************************/

#define AIC_base        0xFFFFF000      /* Advanced Interrupt Controller                      */
#define DBGU_base       0xFFFFF200      /* Debug Unit                                         */
#define PIOA_base       0xFFFFF400      /* PIO Controller A                                   */
#define PIOB_base       0xFFFFF600      /* PIO Controller B                                   */
#define PMC_base        0xFFFFFC00      /* Power Management Controller                        */
#define ST_base         0xFFFFFD00      /* System Timer                                       */
#define RTC_base        0xFFFFFD00      /* Real Time Clock                                    */
#define MC_base         0xFFFFFF00      /* Memory Controller                                  */
#define TC012_base      0xFFFA0000      /* Timer Counter 0 1 2                                */
#define TC0_base        0xFFFA0000      /* Timer Counter 0                                    */
#define TC1_base        0xFFFA0040      /* Timer Counter 1                                    */
#define TC2_base        0xFFFA0080      /* Timer Counter 2                                    */
#define TC345_base      0xFFFA4000      /* Timer Counter 3 4 5                                */
#define TC3_base        0xFFFA4000      /* Timer Counter 3                                    */
#define TC4_base        0xFFFA4040      /* Timer Counter 4                                    */
#define TC5_base        0xFFFA4080      /* Timer Counter 5                                    */
#define USB_base        0xFFFB0000      /* USB Device Port                                    */
#define MCI_base        0xFFFB4000      /* Multimedia Card Interface                          */
#define TWI_base        0xFFFB8000      /* Two-Wire Interface                                 */
#define US0_base        0xFFFC0000      /* Universal Syn Assyn Receive Transmitter 0          */
#define US1_base        0xFFFC4000      /* Universal Syn Assyn Receive Transmitter 1          */
#define US2_base        0xFFFC8000      /* Universal Syn Assyn Receive Transmitter 2          */
#define US3_base        0xFFFCC000      /* Universal Syn Assyn Receive Transmitter 3          */
#define SSC0_base       0xFFFD0000      /* Serial Synchronous Controller 0                    */
#define SSC1_base       0xFFFD4000      /* Serial Synchronous Controller 1                    */
#define SSC2_base       0xFFFD8000      /* Serial Synchronous Controller 2                    */
#define SPI_base        0xFFFE0000      /* Serial Peripheral Interface                        */

/***************************************************************************
 ***************************************************************************
 **
 **    AT91RM3400 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

typedef struct {
  __REG32 RCB             : 1;
  __REG32                 :31;
} __mc_rcr_bits;

typedef struct {
  __REG32 UNDADD          : 1;
  __REG32 MISADD          : 1;
  __REG32 MPU             : 1;
  __REG32                 : 5;
  __REG32 ABTSZ           : 2;
  __REG32 ABTTYP          : 2;
  __REG32                 : 4;
  __REG32 MST0            : 1;
  __REG32 MST1            : 1;
  __REG32                 : 6;
  __REG32 SVMST0          : 1;
  __REG32 SVMST1          : 1;
  __REG32                 : 6;
} __mc_asr_bits;

typedef struct {
  __REG32 ABTADD          :32;
} __mc_aasr_bits;

typedef struct {
  __REG32 PROT            : 2;
  __REG32                 : 2;
  __REG32 SIZE            : 4;
  __REG32                 : 2;
  __REG32 BA              :12;
  __REG32                 :10;
} __mc_puia_bits;

typedef struct {
  __REG32 PROT            : 2;
  __REG32                 :30;
} __mc_pup_bits;

typedef struct {
  __REG32 PUEB            : 1;
  __REG32                 :31;
} __mc_puer_bits;

typedef struct {
  __REG32 PRIOR           : 3;
  __REG32                 : 2;
  __REG32 SRCTYPE         : 2;
  __REG32                 :25;
} __aic_smr_bits;

typedef struct {
  __REG32 VECTOR          :32;
} __aic_svr_bits;

typedef struct {
  __REG32 IRQV            :32;
} __aic_ivr_bits;

typedef struct {
  __REG32 FIQV            :32;
} __aic_fvr_bits;

typedef struct {
  __REG32 IRQID           : 5;
  __REG32                 :27;
} __aic_isr_bits;

typedef struct {
  __REG32 FIQ             : 1;
  __REG32 SYS             : 1;
  __REG32 PID2            : 1;
  __REG32 PID3            : 1;
  __REG32 PID4            : 1;
  __REG32 PID5            : 1;
  __REG32 PID6            : 1;
  __REG32 PID7            : 1;
  __REG32 PID8            : 1;
  __REG32 PID9            : 1;
  __REG32 PID10           : 1;
  __REG32 PID11           : 1;
  __REG32 PID12           : 1;
  __REG32 PID13           : 1;
  __REG32 PID14           : 1;
  __REG32 PID15           : 1;
  __REG32 PID16           : 1;
  __REG32 PID17           : 1;
  __REG32 PID18           : 1;
  __REG32 PID19           : 1;
  __REG32 PID20           : 1;
  __REG32 PID21           : 1;
  __REG32 PID22           : 1;
  __REG32 PID23           : 1;
  __REG32 PID24           : 1;
  __REG32 PID25           : 1;
  __REG32 PID26           : 1;
  __REG32 PID27           : 1;
  __REG32 PID28           : 1;
  __REG32 PID29           : 1;
  __REG32 PID30           : 1;
  __REG32 PID31           : 1;
} __aic_ir_bits;

typedef struct {
  __REG32 NIFQ            : 1;
  __REG32 NIRQ            : 1;
  __REG32                 :30;
} __aic_cisr_bits;

typedef struct {
  __REG32 SIQV            :32;
} __aic_spu_bits;

typedef struct {
  __REG32 PROT            : 1;
  __REG32 GMSK            : 1;
  __REG32                 :30;
} __aic_debug_bits;

typedef struct {
  __REG32                 : 1;
  __REG32 SYS             : 1;
  __REG32 PID2            : 1;
  __REG32 PID3            : 1;
  __REG32 PID4            : 1;
  __REG32 PID5            : 1;
  __REG32 PID6            : 1;
  __REG32 PID7            : 1;
  __REG32 PID8            : 1;
  __REG32 PID9            : 1;
  __REG32 PID10           : 1;
  __REG32 PID11           : 1;
  __REG32 PID12           : 1;
  __REG32 PID13           : 1;
  __REG32 PID14           : 1;
  __REG32 PID15           : 1;
  __REG32 PID16           : 1;
  __REG32 PID17           : 1;
  __REG32 PID18           : 1;
  __REG32 PID19           : 1;
  __REG32 PID20           : 1;
  __REG32 PID21           : 1;
  __REG32 PID22           : 1;
  __REG32 PID23           : 1;
  __REG32 PID24           : 1;
  __REG32 PID25           : 1;
  __REG32 PID26           : 1;
  __REG32 PID27           : 1;
  __REG32 PID28           : 1;
  __REG32 PID29           : 1;
  __REG32 PID30           : 1;
  __REG32 PID31           : 1;
} __aic_ffr_bits;

typedef struct {
  __REG32 PCK             : 1;
  __REG32 UDP             : 1;
  __REG32 MCKUDP          : 1;
  __REG32                 : 1;
  __REG32 UHP             : 1;
  __REG32                 : 3;
  __REG32 PCK0            : 1;
  __REG32 PCK1            : 1;
  __REG32 PCK2            : 1;
  __REG32 PCK3            : 1;
  __REG32                 :20;
} __pmc_scr_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 PID2            : 1;
  __REG32 PID3            : 1;
  __REG32 PID4            : 1;
  __REG32 PID5            : 1;
  __REG32 PID6            : 1;
  __REG32 PID7            : 1;
  __REG32 PID8            : 1;
  __REG32 PID9            : 1;
  __REG32 PID10           : 1;
  __REG32 PID11           : 1;
  __REG32 PID12           : 1;
  __REG32 PID13           : 1;
  __REG32 PID14           : 1;
  __REG32 PID15           : 1;
  __REG32 PID16           : 1;
  __REG32 PID17           : 1;
  __REG32 PID18           : 1;
  __REG32 PID19           : 1;
  __REG32 PID20           : 1;
  __REG32 PID21           : 1;
  __REG32 PID22           : 1;
  __REG32 PID23           : 1;
  __REG32 PID24           : 1;
  __REG32 PID25           : 1;
  __REG32 PID26           : 1;
  __REG32 PID27           : 1;
  __REG32 PID28           : 1;
  __REG32 PID29           : 1;
  __REG32 PID30           : 1;
  __REG32 PID31           : 1;
} __pmc_pcr_bits;

typedef struct {
  __REG32 MOSCEN          : 1;
  __REG32                 : 7;
  __REG32 OSCOUNT         : 8;
  __REG32                 :16;
} __pmc_ckgr_mor_bits;

typedef struct {
  __REG32 MAINF           :16;
  __REG32 MAINRDY         : 1;
  __REG32                 :15;
} __pmc_ckgr_mcfr_bits;

typedef struct {
  __REG32 DIVA            : 8;
  __REG32 PLLACOUNT       : 6;
  __REG32 OUTA            : 2;
  __REG32 MULA            :11;
  __REG32                 : 5;
} __pmc_ckgr_pllar_bits;

typedef struct {
  __REG32 DIVB            : 8;
  __REG32 PLLBCOUNT       : 6;
  __REG32 OUTB            : 2;
  __REG32 MULB            :11;
  __REG32                 : 1;
  __REG32 USB_96M         : 1;
  __REG32                 : 3;
} __pmc_ckgr_pllbr_bits;

typedef struct {
  __REG32 CSS             : 2;
  __REG32 PRES            : 3;
  __REG32                 : 3;
  __REG32 MDIV            : 2;
  __REG32                 :22;
} __pmc_mckr_bits;

typedef struct {
  __REG32 CSS             : 2;
  __REG32 PRES            : 3;
  __REG32                 :27;
} __pmc_pck_bits;

typedef struct {
  __REG32 MOSCS           : 1;
  __REG32 LOCKA           : 1;
  __REG32 LOCKB           : 1;
  __REG32 MCKRDY          : 1;
  __REG32                 : 4;
  __REG32 PCK0RDY         : 1;
  __REG32 PCK1RDY         : 1;
  __REG32 PCK2RDY         : 1;
  __REG32 PCK3RDY         : 1;
  __REG32                 :20;
} __pmc_ir_bits;

typedef struct {
  __REG32 WDRST           : 1;
  __REG32                 :31;
} __st_cr_bits;

typedef struct {
  __REG32 PIV             :16;
  __REG32                 :16;
} __st_pimr_bits;

typedef struct {
  __REG32 WDV             :16;
  __REG32 RSTEN           : 1;
  __REG32 EXTEN           : 1;
  __REG32                 :14;
} __st_wdmr_bits;

typedef struct {
  __REG32 RTPRES          :16;
  __REG32                 :16;
} __st_rtmr_bits;

typedef struct {
  __REG32 PITS            : 1;
  __REG32 WDOVF           : 1;
  __REG32 RTTINC          : 1;
  __REG32 ALMS            : 1;
  __REG32                 :28;
} __st_ir_bits;

typedef struct {
  __REG32 ALMV            :20;
  __REG32                 :12;
} __st_rtar_bits;

typedef struct {
  __REG32 CRTV            :20;
  __REG32                 :12;
} __st_crtr_bits;

typedef struct {
  __REG32 UPDTIM          : 1;
  __REG32 UPDCAL          : 1;
  __REG32                 : 6;
  __REG32 TIMEVSEL        : 2;
  __REG32                 : 6;
  __REG32 CALEVSEL        : 2;
  __REG32                 :14;
} __rtc_cr_bits;

typedef struct {
  __REG32 HRMOD           : 1;
  __REG32                 :31;
} __rtc_mr_bits;

typedef struct {
  __REG32 SEC             : 7;
  __REG32                 : 1;
  __REG32 MIN             : 7;
  __REG32                 : 1;
  __REG32 HOUR            : 6;
  __REG32 AMPM            : 1;
  __REG32                 : 9;
} __rtc_timr_bits;

typedef struct {
  __REG32 CENT            : 7;
  __REG32                 : 1;
  __REG32 YEAR            : 8;
  __REG32 MONTH           : 5;
  __REG32 DAY             : 3;
  __REG32 DATE            : 6;
  __REG32                 : 2;
} __rtc_calr_bits;

typedef struct {
  __REG32 SEC             : 7;
  __REG32 SECEN           : 1;
  __REG32 MIN             : 7;
  __REG32 MINEN           : 1;
  __REG32 HOUR            : 6;
  __REG32 AMPM            : 1;
  __REG32 HOUREN          : 1;
  __REG32                 : 8;
} __rtc_timalr_bits;

typedef struct {
  __REG32                 :16;
  __REG32 MONTH           : 5;
  __REG32                 : 2;
  __REG32 MTHEN           : 1;
  __REG32 DATE            : 6;
  __REG32                 : 1;
  __REG32 DATEEN          : 1;
} __rtc_calalr_bits;

typedef struct {
  __REG32 ACKUPD          : 1;
  __REG32 ALARM           : 1;
  __REG32 SEC             : 1;
  __REG32 TIMEV           : 1;
  __REG32 CALEV           : 1;
  __REG32                 :27;
} __rtc_sr_bits;

typedef struct {
  __REG32 ACKEN           : 1;
  __REG32 ALREN           : 1;
  __REG32 SECEN           : 1;
  __REG32 TIMEN           : 1;
  __REG32 CALEN           : 1;
  __REG32                 :27;
} __rtc_ier_bits;

typedef struct {
  __REG32 ACKDIS          : 1;
  __REG32 ALRDIS          : 1;
  __REG32 SECDIS          : 1;
  __REG32 TIMDIS          : 1;
  __REG32 CALDIS          : 1;
  __REG32                 :27;
} __rtc_idr_bits;

typedef struct {
  __REG32 ACK             : 1;
  __REG32 ALR             : 1;
  __REG32 SEC             : 1;
  __REG32 TIM             : 1;
  __REG32 CAL             : 1;
  __REG32                 :27;
} __rtc_imr_bits;

typedef struct {
  __REG32 NVTIM           : 1;
  __REG32 NVCAL           : 1;
  __REG32 NVTIMALR        : 1;
  __REG32 NVCALAR         : 1;
  __REG32                 :28;
} __rtc_ver_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 RSTRX           : 1;
  __REG32 RSTTX           : 1;
  __REG32 RXEN            : 1;
  __REG32 RXDIS           : 1;
  __REG32 TXEN            : 1;
  __REG32 TXDIS           : 1;
  __REG32 RSTSTA          : 1;
  __REG32                 :23;
} __dbgu_cr_bits;

typedef struct {
  __REG32                 : 9;
  __REG32 PAR             : 3;
  __REG32                 : 2;
  __REG32 CHMODE          : 2;
  __REG32                 :16;
} __dbgu_mr_bits;

typedef struct {
  __REG32 RXRDY           : 1;
  __REG32 TXRDY           : 1;
  __REG32                 : 1;
  __REG32 ENDRX           : 1;
  __REG32 ENDTX           : 1;
  __REG32 OVRE            : 1;
  __REG32 FRAME           : 1;
  __REG32 PARE            : 1;
  __REG32                 : 1;
  __REG32 TXEMPTY         : 1;
  __REG32                 : 1;
  __REG32 TXBUFE          : 1;
  __REG32 RXBUFF          : 1;
  __REG32                 :17;
  __REG32 COMMTX          : 1;
  __REG32 COMMRX          : 1;
} __dbgu_ir_bits;

typedef struct {
  __REG32 RXCHR           : 8;
  __REG32                 :24;
} __dbgu_rhr_bits;

typedef struct {
  __REG32 TXCHR           : 8;
  __REG32                 :24;
} __dbgu_thr_bits;

typedef struct {
  __REG32 CD              :16;
  __REG32                 :16;
} __dbgu_brgr_bits;

typedef struct {
  __REG32 VERSION         : 5;
  __REG32 EPROC           : 3;
  __REG32 NVPSIZ          : 4;
  __REG32                 : 4;
  __REG32 SRAMSIZ         : 4;
  __REG32 ARCH            : 8;
  __REG32 NVPTYP          : 3;
  __REG32 EXT             : 1;
} __dbgu_cidr_bits;

typedef struct {
  __REG32 EXID            :32;
} __dbgu_exid_bits;

typedef struct {
  __REG32 FNTRST          : 1;
  __REG32                 :31;
} __dbgu_fnr_bits;

typedef struct {
  __REG32 P0              : 1;
  __REG32 P1              : 1;
  __REG32 P2              : 1;
  __REG32 P3              : 1;
  __REG32 P4              : 1;
  __REG32 P5              : 1;
  __REG32 P6              : 1;
  __REG32 P7              : 1;
  __REG32 P8              : 1;
  __REG32 P9              : 1;
  __REG32 P10             : 1;
  __REG32 P11             : 1;
  __REG32 P12             : 1;
  __REG32 P13             : 1;
  __REG32 P14             : 1;
  __REG32 P15             : 1;
  __REG32 P16             : 1;
  __REG32 P17             : 1;
  __REG32 P18             : 1;
  __REG32 P19             : 1;
  __REG32 P20             : 1;
  __REG32 P21             : 1;
  __REG32 P22             : 1;
  __REG32 P23             : 1;
  __REG32 P24             : 1;
  __REG32 P25             : 1;
  __REG32 P26             : 1;
  __REG32 P27             : 1;
  __REG32 P28             : 1;
  __REG32 P29             : 1;
  __REG32 P30             : 1;
  __REG32 P31             : 1;
} __pio_r_bits;

typedef struct {
  __REG32 SPIEN           : 1;
  __REG32 SPIDIS          : 1;
  __REG32                 :30;
} __spi_cr_bits;

typedef struct {
  __REG32 MSTR            : 1;
  __REG32 PS              : 1;
  __REG32 PCSDEC          : 1;
  __REG32 DIV32           : 1;
  __REG32 MODFDIS         : 1;
  __REG32                 : 2;
  __REG32 LLB             : 1;
  __REG32                 : 8;
  __REG32 PCS             : 4;
  __REG32                 : 4;
  __REG32 DLYBCS          : 8;
} __spi_mr_bits;

typedef struct {
  __REG32 RD              :16;
  __REG32 PCS             : 4;
  __REG32                 :12;
} __spi_rdr_bits;

typedef struct {
  __REG32 TD              :16;
  __REG32 PCS             : 4;
  __REG32                 :12;
} __spi_tdr_bits;

typedef struct {
  __REG32 RDRF            : 1;
  __REG32 TDRE            : 1;
  __REG32 MODF            : 1;
  __REG32 OVRES           : 1;
  __REG32 ENDRX           : 1;
  __REG32 ENDTX           : 1;
  __REG32 RXBUFF          : 1;
  __REG32 TXBUFE          : 1;
  __REG32                 : 8;
  __REG32 SPIENS          : 1;
  __REG32                 :15;
} __spi_sr_bits;

typedef struct {
  __REG32 RDRF            : 1;
  __REG32 TDRE            : 1;
  __REG32 MODF            : 1;
  __REG32 OVRES           : 1;
  __REG32 ENDRX           : 1;
  __REG32 ENDTX           : 1;
  __REG32 RXBUFF          : 1;
  __REG32 TXBUFE          : 1;
  __REG32                 :24;
} __spi_ir_bits;

typedef struct {
  __REG32 CPOL            : 1;
  __REG32 NCPHA           : 1;
  __REG32                 : 2;
  __REG32 BITS            : 4;
  __REG32 SCBR            : 8;
  __REG32 DLYBS           : 8;
  __REG32 DLYBCT          : 8;
} __spi_csr_bits;

typedef struct {
  __REG32 START           : 1;
  __REG32 STOP            : 1;
  __REG32 MSEN            : 1;
  __REG32 MSDIS           : 1;
  __REG32                 : 3;
  __REG32 SWRST           : 1;
  __REG32                 :24;
} __twi_cr_bits;

typedef struct {
  __REG32                 : 8;
  __REG32 IADRSZ          : 2;
  __REG32                 : 2;
  __REG32 MREAD           : 1;
  __REG32                 : 3;
  __REG32 DADR            : 7;
  __REG32                 : 9;
} __twi_mmr_bits;

typedef struct {
  __REG32 IADR            :24;
  __REG32                 : 8;
} __twi_iadr_bits;

typedef struct {
  __REG32 CLDIV           : 8;
  __REG32 CHDIV           : 8;
  __REG32 CKDIV           : 3;
  __REG32                 :13;
} __twi_cwgr_bits;

typedef struct {
  __REG32 TXCOMP          : 1;
  __REG32 RXRDY           : 1;
  __REG32 TXRDY           : 1;
  __REG32                 : 3;
  __REG32 OVRE            : 1;
  __REG32 UNRE            : 1;
  __REG32 NACK            : 1;
  __REG32                 :23;
} __twi_ir_bits;

typedef struct {
  __REG32 RXDATA          : 8;
  __REG32                 :24;
} __twi_rhr_bits;

typedef struct {
  __REG32 TXDATA          : 8;
  __REG32                 :24;
} __twi_thr_bits;

typedef struct {
  __REG32                 : 2;
  __REG32 RSTRX           : 1;
  __REG32 RSTTX           : 1;
  __REG32 RXEN            : 1;
  __REG32 RXDIS           : 1;
  __REG32 TXEN            : 1;
  __REG32 TXDIS           : 1;
  __REG32 RSTSTA          : 1;
  __REG32 STTBRK          : 1;
  __REG32 STPBRK          : 1;
  __REG32 STTTO           : 1;
  __REG32 SENDA           : 1;
  __REG32 RSTIT           : 1;
  __REG32 RSTNACK         : 1;
  __REG32 RETTO           : 1;
  __REG32 DTREN           : 1;
  __REG32 DTRDIS          : 1;
  __REG32 RTSEN           : 1;
  __REG32 RTSDIS          : 1;
  __REG32                 :12;
} __us_cr_bits;

typedef struct {
  __REG32 USART_MODE      : 4;
  __REG32 USCLKS          : 2;
  __REG32 CHRL            : 2;
  __REG32 SYNC            : 1;
  __REG32 PAR             : 3;
  __REG32 NBSTOP          : 2;
  __REG32 CHMODE          : 2;
  __REG32 MSBF            : 1;
  __REG32 MODE9           : 1;
  __REG32 CLKO            : 1;
  __REG32 OVER            : 1;
  __REG32 INACK           : 1;
  __REG32 DSNACK          : 1;
  __REG32                 : 2;
  __REG32 MAX_ITERATION   : 3;
  __REG32                 : 1;
  __REG32 FILTER          : 1;
  __REG32                 : 3;
} __us_mr_bits;

typedef struct {
  __REG32 RXRDY           : 1;
  __REG32 TXRDY           : 1;
  __REG32 RXBRK           : 1;
  __REG32 ENDRX           : 1;
  __REG32 ENDTX           : 1;
  __REG32 OVRE            : 1;
  __REG32 FRAME           : 1;
  __REG32 PARE            : 1;
  __REG32 TIMEOUT         : 1;
  __REG32 TXEMPTY         : 1;
  __REG32 ITERATION       : 1;
  __REG32 TXBUFE          : 1;
  __REG32 RXBUFF          : 1;
  __REG32 NACK            : 1;
  __REG32                 : 2;
  __REG32 RIIC            : 1;
  __REG32 DSRIC           : 1;
  __REG32 DCDIC           : 1;
  __REG32 CTSIC           : 1;
  __REG32                 :12;
} __us_ir_bits;

typedef struct {
  __REG32 RXRDY           : 1;
  __REG32 TXRDY           : 1;
  __REG32 RXBRK           : 1;
  __REG32 ENDRX           : 1;
  __REG32 ENDTX           : 1;
  __REG32 OVRE            : 1;
  __REG32 FRAME           : 1;
  __REG32 PARE            : 1;
  __REG32 TIMEOUT         : 1;
  __REG32 TXEMPTY         : 1;
  __REG32 ITERATION       : 1;
  __REG32 TXBUFE          : 1;
  __REG32 RXBUFF          : 1;
  __REG32 NACK            : 1;
  __REG32                 : 2;
  __REG32 RIIC            : 1;
  __REG32 DSRIC           : 1;
  __REG32 DCDIC           : 1;
  __REG32 CTSIC           : 1;
  __REG32 RI              : 1;
  __REG32 DSR             : 1;
  __REG32 DCD             : 1;
  __REG32 CTS             : 1;
  __REG32                 : 8;
} __us_csr_bits;

typedef struct {
  __REG32 RXCHR           : 9;
  __REG32                 :23;
} __us_rhr_bits;

typedef struct {
  __REG32 TXCHR           : 9;
  __REG32                 :23;
} __us_thr_bits;

typedef struct {
  __REG32 CD              :16;
  __REG32                 :16;
} __us_brgr_bits;

typedef struct {
  __REG32 TO              :16;
  __REG32                 :16;
} __us_rtor_bits;

typedef struct {
  __REG32 TG              : 8;
  __REG32                 :24;
} __us_ttgr_bits;

typedef struct {
  __REG32 FI_DI_RATIO     :11;
  __REG32                 :21;
} __us_fidi_bits;

typedef struct {
  __REG32 NB_ERRORS       : 8;
  __REG32                 :24;
} __us_ner_bits;

typedef struct {
  __REG32 IRDA_FILTER     : 8;
  __REG32                 :24;
} __us_if_bits;

typedef struct {
  __REG32 RXEN            : 1;
  __REG32 RXDIS           : 1;
  __REG32                 : 6;
  __REG32 TXEN            : 1;
  __REG32 TXDIS           : 1;
  __REG32                 : 5;
  __REG32 SWRST           : 1;
  __REG32                 :16;
} __ssc_cr_bits;

typedef struct {
  __REG32 DIV             :12;
  __REG32                 :20;
} __ssc_cmr_bits;

typedef struct {
  __REG32 CKS             : 2;
  __REG32 CKO             : 3;
  __REG32 CKI             : 1;
  __REG32                 : 2;
  __REG32 START           : 4;
  __REG32                 : 4;
  __REG32 STTDLY          : 8;
  __REG32 PERIOD          : 8;
} __ssc_rtcmr_bits;

typedef struct {
  __REG32 DATLEN          : 5;
  __REG32 LOOP            : 1;
  __REG32                 : 1;
  __REG32 MSBF            : 1;
  __REG32 DATNB           : 4;
  __REG32                 : 4;
  __REG32 FSLEN           : 4;
  __REG32 FSOS            : 3;
  __REG32                 : 1;
  __REG32 FSEDGE          : 1;
  __REG32                 : 7;
} __ssc_rfmr_bits;

typedef struct {
  __REG32 DATLEN          : 5;
  __REG32 DATDEF          : 1;
  __REG32                 : 1;
  __REG32 MSBF            : 1;
  __REG32 DATNB           : 4;
  __REG32                 : 4;
  __REG32 FSLEN           : 4;
  __REG32 FSOS            : 3;
  __REG32 FSDEN           : 1;
  __REG32 FSEDGE          : 1;
  __REG32                 : 7;
} __ssc_tfmr_bits;

typedef struct {
  __REG32 RDAT            :32;
} __ssc_rhr_bits;

typedef struct {
  __REG32 TDAT            :32;
} __ssc_thr_bits;

typedef struct {
  __REG32 RSDAT           :16;
  __REG32                 :16;
} __ssc_rshr_bits;

typedef struct {
  __REG32 TSDAT           :16;
  __REG32                 :16;
} __ssc_tshr_bits;

typedef struct {
  __REG32 TXRDY           : 1;
  __REG32 TXEMPTY         : 1;
  __REG32 ENDTX           : 1;
  __REG32 TXBUFE          : 1;
  __REG32 RXRDY           : 1;
  __REG32 OVRUN           : 1;
  __REG32 ENDRX           : 1;
  __REG32 RXBUFF          : 1;
  __REG32                 : 2;
  __REG32 TXSYN           : 1;
  __REG32 RXSYN           : 1;
  __REG32                 : 4;
  __REG32 TXEN            : 1;
  __REG32 RXEN            : 1;
  __REG32                 :14;
} __ssc_sr_bits;

typedef struct {
  __REG32 TXRDY           : 1;
  __REG32 TXEMPTY         : 1;
  __REG32 ENDTX           : 1;
  __REG32 TXBUFE          : 1;
  __REG32 RXRDY           : 1;
  __REG32 OVRUN           : 1;
  __REG32 ENDRX           : 1;
  __REG32 RXBUFF          : 1;
  __REG32                 : 2;
  __REG32 TXSYN           : 1;
  __REG32 RXSYN           : 1;
  __REG32                 :20;
} __ssc_ir_bits;

typedef struct {
  __REG32 CLKEN           : 1;
  __REG32 CLKDIS          : 1;
  __REG32 SWTRG           : 1;
  __REG32                 :29;
} __tc_ccr_bits;

typedef union {
  //WAVEFORM_MODE TC0_CMR TC1_CMR TC2_CMR TC3_CMR TC4_CMR TC5_CMR
  struct{
    __REG32 TCCLKS          : 3;
    __REG32 CLKI            : 1;
    __REG32 BURST           : 2;
    __REG32 CPCSTOP         : 1;
    __REG32 CPCDIS          : 1;
    __REG32 EEVTEDG         : 2;
    __REG32 EEVT            : 2;
    __REG32 ENETRG          : 1;
    __REG32 WAVSEL          : 2;
    __REG32 WAVE            : 1;
    __REG32 ACPA            : 2;
    __REG32 ACPC            : 2;
    __REG32 AEEVT           : 2;
    __REG32 ASWTRG          : 2;
    __REG32 BCPB            : 2;
    __REG32 BCPC            : 2;
    __REG32 BEEVT           : 2;
    __REG32 BSWTRG          : 2;
  };
  //CAPTURE_MODE TC0_CMR TC1_CMR TC2_CMR TC3_CMR TC4_CMR TC5_CMR
  struct{
    __REG32                 : 3; //TCCLKS
    __REG32                 : 1; //CLKI
    __REG32                 : 2; //BURST
    __REG32 LDBSTOP         : 1;
    __REG32 LDBDIS          : 1;
    __REG32 ETRGEDE         : 2;
    __REG32 ABETRG          : 1;
    __REG32                 : 3;
    __REG32 CPCTRG          : 1;
    __REG32                 : 1; //WAVE
    __REG32 LDRA            : 2;
    __REG32 LDRB            : 2;
    __REG32                 :12;
  };
} __tc_cmr_bits;

typedef struct {
  __REG32 CV              :16;
  __REG32                 :16;
} __tc_cv_bits;

typedef struct {
  __REG32 RA              :16;
  __REG32                 :16;
} __tc_ra_bits;

typedef struct {
  __REG32 RB              :16;
  __REG32                 :16;
} __tc_rb_bits;

typedef struct {
  __REG32 RC              :16;
  __REG32                 :16;
} __tc_rc_bits;

typedef struct {
  __REG32 COVFS           : 1;
  __REG32 LOVRS           : 1;
  __REG32 CPAS            : 1;
  __REG32 CPBS            : 1;
  __REG32 CPCS            : 1;
  __REG32 LDRAS           : 1;
  __REG32 LDRBS           : 1;
  __REG32 ETRGS           : 1;
  __REG32                 : 8;
  __REG32 CLKSTA          : 1;
  __REG32 MTIOA           : 1;
  __REG32 MTIOB           : 1;
  __REG32                 :13;
} __tc_sr_bits;

typedef struct {
  __REG32 COVFS           : 1;
  __REG32 LOVRS           : 1;
  __REG32 CPAS            : 1;
  __REG32 CPBS            : 1;
  __REG32 CPCS            : 1;
  __REG32 LDRAS           : 1;
  __REG32 LDRBS           : 1;
  __REG32 ETRGS           : 1;
  __REG32                 :24;
} __tc_ir_bits;

typedef struct {
  __REG32 SYNC            : 1;
  __REG32                 :31;
} __tc_bcr_bits;

typedef struct {
  __REG32 TC0XC0S         : 2;
  __REG32 TC1XC1S         : 2;
  __REG32 TC2XC2S         : 2;
  __REG32                 :26;
} __tc012_bmr_bits;

typedef struct {
  __REG32 TC3XC3S         : 2;
  __REG32 TC4XC4S         : 2;
  __REG32 TC52XC5S        : 2;
  __REG32                 :26;
} __tc345_bmr_bits;

typedef struct {
  __REG32 MCIEN           : 1;
  __REG32 MCIDIS          : 1;
  __REG32 PWSEN           : 1;
  __REG32 PWSDIS          : 1;
  __REG32                 :28;
} __mci_cr_bits;

typedef struct {
  __REG32 CLKDIV          : 8;
  __REG32 PWSDIV          : 3;
  __REG32                 : 3;
  __REG32 PDCPADV         : 1;
  __REG32 PDCMODE         : 1;
  __REG32                 : 2;
  __REG32 BLKEN           :12;
  __REG32                 : 2;
} __mci_mr_bits;

typedef struct {
  __REG32 DTOCYC          : 4;
  __REG32 DTOMUL          : 3;
  __REG32                 :25;
} __mci_dtor_bits;

typedef struct {
  __REG32 SDCSEL          : 4;
  __REG32                 : 3;
  __REG32 SDCBUS          : 1;
  __REG32                 :24;
} __mci_sdcr_bits;

typedef struct {
  __REG32 ARG             :32;
} __mci_argr_bits;

typedef struct {
  __REG32 CMDNB           : 6;
  __REG32 RSPTYP          : 2;
  __REG32 SPCMD           : 3;
  __REG32 OPDCMD          : 1;
  __REG32 MAXLAT          : 1;
  __REG32                 : 3;
  __REG32 TRCMD           : 2;
  __REG32 TRDIR           : 1;
  __REG32 TRTYPE          : 1;
  __REG32                 :12;
} __mci_cmdr_bits;

typedef struct {
  __REG32 RSP             :32;
} __mci_rspr_bits;

typedef struct {
  __REG32 DATA            :32;
} __mci_dr_bits;

typedef struct {
  __REG32 CMDRDY          : 1;
  __REG32 RXRDY           : 1;
  __REG32 TXRDY           : 1;
  __REG32 BLKE            : 1;
  __REG32 DTIP            : 1;
  __REG32 NOTBUSY         : 1;
  __REG32 ENDRX           : 1;
  __REG32 ENDTX           : 1;
  __REG32                 : 6;
  __REG32 RXBUFF          : 1;
  __REG32 TXBUFE          : 1;
  __REG32 RINDE           : 1;
  __REG32 RDIRE           : 1;
  __REG32 RCRCE           : 1;
  __REG32 RENDE           : 1;
  __REG32 RTOE            : 1;
  __REG32 TCRCE           : 1;
  __REG32 DTOE            : 1;
  __REG32                 : 7;
  __REG32 OVRE            : 1;
  __REG32 UNRE            : 1;
} __mci_ir_bits;

typedef struct {
  __REG32 FRM_NUM         :11;
  __REG32                 : 5;
  __REG32 FRM_ERR         : 1;
  __REG32 FRM_OK          : 1;
  __REG32                 :14;
} __usb_frm_num_bits;

typedef struct {
  __REG32 FADDEN          : 1;
  __REG32 CONFG           : 1;
  __REG32 ESR             : 1;
  __REG32 RSMINPR         : 1;
  __REG32 RMWUPE          : 1;
  __REG32                 :27;
} __usb_glb_stat_bits;

typedef struct {
  __REG32 FADD            : 7;
  __REG32                 : 1;
  __REG32 FEN             : 1;
  __REG32                 :23;
} __usb_faddr_bits;

typedef struct {
  __REG32 EP0INT          : 1;
  __REG32 EP1INT          : 1;
  __REG32 EP2INT          : 1;
  __REG32 EP3INT          : 1;
  __REG32 EP4INT          : 1;
  __REG32 EP5INT          : 1;
  __REG32 EP6INT          : 1;
  __REG32 EP7INT          : 1;
  __REG32 RXSUSP          : 1;
  __REG32 RXRSM           : 1;
  __REG32 EXTRSM          : 1;
  __REG32 SOFINT          : 1;
  __REG32                 : 1;
  __REG32 WAKEUP          : 1;
  __REG32                 :18;
} __usb_ir_bits;

typedef struct {
  __REG32 EP0INT          : 1;
  __REG32 EP1INT          : 1;
  __REG32 EP2INT          : 1;
  __REG32 EP3INT          : 1;
  __REG32 EP4INT          : 1;
  __REG32 EP5INT          : 1;
  __REG32 EP6INT          : 1;
  __REG32 EP7INT          : 1;
  __REG32 RXSUSP          : 1;
  __REG32 RXRSM           : 1;
  __REG32 EXTRSM          : 1;
  __REG32 SOFINT          : 1;
  __REG32 ENDBUSRES       : 1;
  __REG32 WAKEUP          : 1;
  __REG32                 :18;
} __usb_isr_bits;

typedef struct {
  __REG32                 : 8;
  __REG32 RXSUSP          : 1;
  __REG32 RXRSM           : 1;
  __REG32 EXTRSM          : 1;
  __REG32 SOFINT          : 1;
  __REG32 ENDBURST        : 1;
  __REG32 WAKEUP          : 1;
  __REG32                 :18;
} __usb_icr_bits;

typedef struct {
  __REG32 EP0             : 1;
  __REG32 EP1             : 1;
  __REG32 EP2             : 1;
  __REG32 EP3             : 1;
  __REG32 EP4             : 1;
  __REG32 EP5             : 1;
  __REG32 EP6             : 1;
  __REG32 EP7             : 1;
  __REG32                 :24;
} __usb_rst_ep_bits;

typedef struct {
  __REG32 TXCOMP          : 1;
  __REG32 RX_DATA_BK0     : 1;
  __REG32 RXSETUP         : 1;
  __REG32 STALLSENT_ISOERROR : 1;
  __REG32 TXPKTRDY        : 1;
  __REG32 FORCESTALL      : 1;
  __REG32 RX_DATA_BK1     : 1;
  __REG32 DIR             : 1;
  __REG32 EPTYPE          : 3;
  __REG32 DTGLE           : 1;
  __REG32                 : 3;
  __REG32 EPEDS           : 1;
  __REG32 RXBYTECNT       :11;
  __REG32                 : 5;
} __usb_csr_bits;

typedef struct {
  __REG32 FIFO_DATA       : 8;
  __REG32                 :24;
} __usb_fdr_bits;

typedef struct {
  __REG32 RXPTR           :32;
} __periph_rpr_bits;

typedef struct {
  __REG32 RXCTR           :16;
  __REG32                 :16;
} __periph_rcr_bits;

typedef struct {
  __REG32 TXPTR           :32;
} __periph_tpr_bits;

typedef struct {
  __REG32 TXCTR           :16;
  __REG32                 :16;
} __periph_tcr_bits;

typedef struct {
  __REG32 RXNPTR          :32;
} __periph_rnpr_bits;

typedef struct {
  __REG32 RXNCR           :16;
  __REG32                 :16;
} __periph_rncr_bits;

typedef struct {
  __REG32 TXNPTR          :32;
} __periph_tnpr_bits;

typedef struct {
  __REG32 TXNCR           :16;
  __REG32                 :16;
} __periph_tncr_bits;

typedef struct {
  __REG32 RXTEN           : 1;
  __REG32 RXTDIS          : 1;
  __REG32                 : 6;
  __REG32 TXTEN           : 1;
  __REG32 TXTDIS          : 1;
  __REG32                 :22;
} __periph_ptcr_bits;

typedef struct {
  __REG32 RXTEN           : 1;
  __REG32                 : 7;
  __REG32 TXTEN           : 1;
  __REG32                 :23;
} __periph_ptsr_bits;


#endif    /* __IAR_SYSTEMS_ICC__ */


/* Declarations common to compiler and assembler  **************************/ 

/***************************************************************************
 **
 **  MC : Memory Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(MC_RCR,         0xFFFFFF00, __WRITE,      __mc_rcr_bits        );    /* MC Remap Control Register, init value = 0x00000000 */
__IO_REG32_BIT(MC_ASR,         0xFFFFFF04, __READ,       __mc_asr_bits        );    /* MC Abort Status Register, init value = 0x00000000 */
__IO_REG32_BIT(MC_AASR,        0xFFFFFF08, __READ,       __mc_aasr_bits       );    /* MC Abort Address Status Register, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA0,       0xFFFFFF10, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 0, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA1,       0xFFFFFF14, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 1, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA2,       0xFFFFFF18, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 2, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA3,       0xFFFFFF1C, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 3, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA4,       0xFFFFFF20, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 4, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA5,       0xFFFFFF24, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 5, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA6,       0xFFFFFF28, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 6, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA7,       0xFFFFFF2C, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 7, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA8,       0xFFFFFF30, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 8, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA9,       0xFFFFFF34, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 9, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA10,      0xFFFFFF38, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 10, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA11,      0xFFFFFF3C, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 11, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA12,      0xFFFFFF40, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 12, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA13,      0xFFFFFF44, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 13, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA14,      0xFFFFFF48, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 14, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUIA15,      0xFFFFFF4C, __READ_WRITE, __mc_puia_bits       );    /* MC Protection Unit Area 15, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUP,         0xFFFFFF50, __READ_WRITE, __mc_pup_bits        );    /* MC Protection Unit Peripherals, init value = 0x00000000 */
__IO_REG32_BIT(MC_PUER,        0xFFFFFF54, __READ_WRITE, __mc_puer_bits       );    /* MC Protection Unit Enable Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  AIC : Advanced Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(AIC_SMR0,       0xFFFFF000, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR1,       0xFFFFF004, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR2,       0xFFFFF008, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR3,       0xFFFFF00C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 3, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR4,       0xFFFFF010, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 4, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR5,       0xFFFFF014, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 5, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR6,       0xFFFFF018, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 6, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR7,       0xFFFFF01C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 7, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR8,       0xFFFFF020, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 8, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR9,       0xFFFFF024, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 9, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR10,      0xFFFFF028, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 10, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR11,      0xFFFFF02C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 11, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR12,      0xFFFFF030, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 12, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR13,      0xFFFFF034, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 13, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR14,      0xFFFFF038, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 14, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR15,      0xFFFFF03C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 15, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR16,      0xFFFFF040, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 16, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR17,      0xFFFFF044, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 17, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR18,      0xFFFFF048, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 18, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR19,      0xFFFFF04C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 19, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR20,      0xFFFFF050, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 20, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR21,      0xFFFFF054, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 21, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR22,      0xFFFFF058, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 22, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR23,      0xFFFFF05C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 23, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR24,      0xFFFFF060, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 24, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR25,      0xFFFFF064, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 25, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR26,      0xFFFFF068, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 26, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR27,      0xFFFFF06C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 27, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR28,      0xFFFFF070, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 28, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR29,      0xFFFFF074, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 29, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR30,      0xFFFFF078, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 30, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SMR31,      0xFFFFF07C, __READ_WRITE, __aic_smr_bits       );    /* Source Mode Register 31, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR0,       0xFFFFF080, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 0, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR1,       0xFFFFF084, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 1, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR2,       0xFFFFF088, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 2, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR3,       0xFFFFF08C, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 3, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR4,       0xFFFFF090, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 4, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR5,       0xFFFFF094, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 5, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR6,       0xFFFFF098, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 6, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR7,       0xFFFFF09C, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 7, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR8,       0xFFFFF0A0, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 8, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR9,       0xFFFFF0A4, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 9, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR10,      0xFFFFF0A8, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 10, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR11,      0xFFFFF0AC, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 11, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR12,      0xFFFFF0B0, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 12, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR13,      0xFFFFF0B4, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 13, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR14,      0xFFFFF0B8, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 14, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR15,      0xFFFFF0BC, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 15, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR16,      0xFFFFF0C0, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 16, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR17,      0xFFFFF0C4, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 17, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR18,      0xFFFFF0C8, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 18, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR19,      0xFFFFF0CC, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 19, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR20,      0xFFFFF0D0, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 20, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR21,      0xFFFFF0D4, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 21, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR22,      0xFFFFF0D8, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 22, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR23,      0xFFFFF0DC, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 23, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR24,      0xFFFFF0E0, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 24, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR25,      0xFFFFF0E4, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 25, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR26,      0xFFFFF0E8, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 26, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR27,      0xFFFFF0EC, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 27, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR28,      0xFFFFF0F0, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 28, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR29,      0xFFFFF0F4, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 29, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR30,      0xFFFFF0F8, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 30, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SVR31,      0xFFFFF0FC, __READ_WRITE, __aic_svr_bits       );    /* Source Vector Register 31, init value = 0x00000000 */
__IO_REG32_BIT(AIC_IVR,        0xFFFFF100, __READ,       __aic_ivr_bits       );    /* Interrupt Vector Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_FVR,        0xFFFFF104, __READ,       __aic_fvr_bits       );    /* Fast Interrupt Vector Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_ISR,        0xFFFFF108, __READ,       __aic_isr_bits       );    /* Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_IPR,        0xFFFFF10C, __READ,       __aic_ir_bits        );    /* Interrupt Pending Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_IMR,        0xFFFFF110, __READ,       __aic_ir_bits        );    /* Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_CISR,       0xFFFFF114, __READ,       __aic_cisr_bits      );    /* Core Interrupt Status Registr, init value = 0x00000000 */
__IO_REG32_BIT(AIC_IECR,       0xFFFFF120, __WRITE,      __aic_ir_bits        );    /* Interrupt Enable Command Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_IDCR,       0xFFFFF124, __WRITE,      __aic_ir_bits        );    /* Interrupt Disable Command Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_ICCR,       0xFFFFF128, __WRITE,      __aic_ir_bits        );    /* Interrupt Clear Command Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_ISCR,       0xFFFFF12C, __WRITE,      __aic_ir_bits        );    /* Interrupt Set Command Register, init value = 0x00000000 */
__IO_REG32(    AIC_EOICR,      0xFFFFF130, __WRITE                            );    /* End of Interrupt Command Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_SPU,        0xFFFFF134, __READ_WRITE, __aic_spu_bits       );    /* Spurious Interrupt Vector Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_DEBUG,      0xFFFFF138, __READ_WRITE, __aic_debug_bits     );    /* Debug Control Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_FFER,       0xFFFFF140, __WRITE,      __aic_ffr_bits       );    /* Fast Forcing Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_FFDR,       0xFFFFF144, __WRITE,      __aic_ffr_bits       );    /* Fast Forcing Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(AIC_FFSR,       0xFFFFF148, __READ,       __aic_ffr_bits       );    /* Fast Forcing Status Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  PMC : Power Management Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(PMC_SCER,       0xFFFFFC00, __WRITE,      __pmc_scr_bits       );    /* System Clock Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_SCDR,       0xFFFFFC04, __WRITE,      __pmc_scr_bits       );    /* System Clock Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_SCSR,       0xFFFFFC08, __READ,       __pmc_scr_bits       );    /* System Clock Status Register, init value = 0x00000001 */
__IO_REG32_BIT(PMC_PCER,       0xFFFFFC10, __WRITE,      __pmc_pcr_bits       );    /* Peripheral Clock Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_PCDR,       0xFFFFFC14, __WRITE,      __pmc_pcr_bits       );    /* Peripheral Clock Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_PCSR,       0xFFFFFC18, __READ,       __pmc_pcr_bits       );    /* Peripheral Clock Status Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_CKGR_MOR,   0xFFFFFC20, __READ_WRITE, __pmc_ckgr_mor_bits  );    /* Main Oscillator Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_CKGR_MCFR,  0xFFFFFC24, __READ,       __pmc_ckgr_mcfr_bits );    /* Main Clock Frequency Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_CKGR_PLLAR, 0xFFFFFC28, __READ_WRITE, __pmc_ckgr_pllar_bits );    /* PLL A Register, init value = 0x00003F00 */
__IO_REG32_BIT(PMC_CKGR_PLLBR, 0xFFFFFC2C, __READ_WRITE, __pmc_ckgr_pllbr_bits );    /* PLL B Register, init value = 0x00003F00 */
__IO_REG32_BIT(PMC_MCKR,       0xFFFFFC30, __READ_WRITE, __pmc_mckr_bits      );    /* Master Clock Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_PCK0,       0xFFFFFC40, __READ_WRITE, __pmc_pck_bits       );    /* Programmable Clock 0 Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_PCK1,       0xFFFFFC44, __READ_WRITE, __pmc_pck_bits       );    /* Programmable Clock 1 Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_PCK2,       0xFFFFFC48, __READ_WRITE, __pmc_pck_bits       );    /* Programmable Clock 2 Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_PCK3,       0xFFFFFC4C, __READ_WRITE, __pmc_pck_bits       );    /* Programmable Clock 3 Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_IER,        0xFFFFFC60, __WRITE,      __pmc_ir_bits        );    /* Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_IDR,        0xFFFFFC64, __WRITE,      __pmc_ir_bits        );    /* Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_SR,         0xFFFFFC68, __READ,       __pmc_ir_bits        );    /* Status Register, init value = 0x00000000 */
__IO_REG32_BIT(PMC_IMR,        0xFFFFFC6C, __READ,       __pmc_ir_bits        );    /* Interrupt Mask Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  ST : System Timer
 **
 ***************************************************************************/
__IO_REG32_BIT(ST_CR,          0xFFFFFD00, __WRITE,      __st_cr_bits         );    /* Control Register, init value = 0x00000000 */
__IO_REG32_BIT(ST_PIMR,        0xFFFFFD04, __READ_WRITE, __st_pimr_bits       );    /* Period Interval Mode Register, init value = 0x00000000 */
__IO_REG32_BIT(ST_WDMR,        0xFFFFFD08, __READ_WRITE, __st_wdmr_bits       );    /* Watchdog Mode Register, init value = 0x00020000 */
__IO_REG32_BIT(ST_RTMR,        0xFFFFFD0C, __READ_WRITE, __st_rtmr_bits       );    /* Real-time Mode Register, init value = 0x00008000 */
__IO_REG32_BIT(ST_SR,          0xFFFFFD10, __READ,       __st_ir_bits         );    /* Status Register, init value = 0x00000000 */
__IO_REG32_BIT(ST_IER,         0xFFFFFD14, __WRITE,      __st_ir_bits         );    /* Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(ST_IDR,         0xFFFFFD18, __WRITE,      __st_ir_bits         );    /* Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(ST_IMR,         0xFFFFFD1C, __WRITE,      __st_ir_bits         );    /* Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(ST_RTAR,        0xFFFFFD20, __READ_WRITE, __st_rtar_bits       );    /* Real-time Alarm Register, init value = 0x00000000 */
__IO_REG32_BIT(ST_CRTR,        0xFFFFFD24, __READ,       __st_crtr_bits       );    /* Current Real-time Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  RTC : Real Time Clock
 **
 ***************************************************************************/
__IO_REG32_BIT(RTC_CR,         0xFFFFFE00, __READ_WRITE, __rtc_cr_bits        );    /* RTC Control Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_MR,         0xFFFFFE04, __READ_WRITE, __rtc_mr_bits        );    /* RTC Mode Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_TIMR,       0xFFFFFE08, __READ_WRITE, __rtc_timr_bits      );    /* RTC Time Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_CALR,       0xFFFFFE0C, __READ_WRITE, __rtc_calr_bits      );    /* RTC Calendar Register, init value = 0x01819819 */
__IO_REG32_BIT(RTC_TIMALR,     0xFFFFFE10, __READ_WRITE, __rtc_timalr_bits    );    /* RTC Time Alarm Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_CALALR,     0xFFFFFE14, __READ_WRITE, __rtc_calalr_bits    );    /* RTC Calendar Alarm Register, init value = 0x01010000 */
__IO_REG32_BIT(RTC_SR,         0xFFFFFE18, __READ,       __rtc_sr_bits        );    /* RTC Status Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_SCCR,       0xFFFFFE1C, __WRITE,      __rtc_sr_bits        );    /* RTC Status Clear Command Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_IER,        0xFFFFFE20, __WRITE,      __rtc_ier_bits       );    /* RTC Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_IDR,        0xFFFFFE24, __WRITE,      __rtc_idr_bits       );    /* RTC Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_IMR,        0xFFFFFE28, __READ,       __rtc_imr_bits       );    /* RTC Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(RTC_VER,        0xFFFFFE2C, __READ,       __rtc_ver_bits       );    /* RTC Valid Entry Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  DBGU : Debug Unit
 **
 ***************************************************************************/
__IO_REG32_BIT(DBGU_CR,        0xFFFFF200, __WRITE,      __dbgu_cr_bits       );    /* Control Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_MR,        0xFFFFF204, __READ_WRITE, __dbgu_mr_bits       );    /* Mode Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_IER,       0xFFFFF208, __WRITE,      __dbgu_ir_bits       );    /* Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_IDR,       0xFFFFF20C, __WRITE,      __dbgu_ir_bits       );    /* Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_IMR,       0xFFFFF210, __READ,       __dbgu_ir_bits       );    /* Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_SR,        0xFFFFF214, __READ,       __dbgu_ir_bits       );    /* Status Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_RHR,       0xFFFFF218, __READ,       __dbgu_rhr_bits      );    /* Receive Holding Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_THR,       0xFFFFF21C, __WRITE,      __dbgu_thr_bits      );    /* Transmit Holding Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_BRGR,      0xFFFFF220, __READ_WRITE, __dbgu_brgr_bits     );    /* Baud Rate Generator Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_CIDR,      0xFFFFF240, __READ,       __dbgu_cidr_bits     );    /* Chip ID Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_EXID,      0xFFFFF244, __READ,       __dbgu_exid_bits     );    /* Chip ID Extension Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_FNR,       0xFFFFF248, __READ_WRITE, __dbgu_fnr_bits      );    /* Force NTRST Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_RPR,       0xFFFFF300, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_RCR,       0xFFFFF304, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_TPR,       0xFFFFF308, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_TCR,       0xFFFFF30C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_RNPR,      0xFFFFF310, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_RNCR,      0xFFFFF314, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Registe, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_TNPR,      0xFFFFF318, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_TNCR,      0xFFFFF31C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_PTCR,      0xFFFFF320, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register, init value = 0x00000000 */
__IO_REG32_BIT(DBGU_PTSR,      0xFFFFF324, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  PIOA : PIO Controller A
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOA_PER,       0xFFFFF400, __WRITE,      __pio_r_bits         );    /* PIO Enable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_PDR,       0xFFFFF404, __WRITE,      __pio_r_bits         );    /* PIO Disable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_PSR,       0xFFFFF408, __READ,       __pio_r_bits         );    /* PIO Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_OER,       0xFFFFF410, __WRITE,      __pio_r_bits         );    /* PIO Output Enable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_ODR,       0xFFFFF414, __WRITE,      __pio_r_bits         );    /* PIO Output Disable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_OSR,       0xFFFFF418, __READ,       __pio_r_bits         );    /* PIO Output Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_IFER,      0xFFFFF420, __WRITE,      __pio_r_bits         );    /* PIO Glitch Input Filter Enable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_IFDR,      0xFFFFF424, __WRITE,      __pio_r_bits         );    /* PIO Glitch Input Filter Disable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_IFSR,      0xFFFFF428, __READ,       __pio_r_bits         );    /* PIO Glitch Input Filter Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_SODR,      0xFFFFF430, __WRITE,      __pio_r_bits         );    /* PIO Set Output Data Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_CODR,      0xFFFFF434, __WRITE,      __pio_r_bits         );    /* PIO Clear Output Data Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_ODSR,      0xFFFFF438, __READ,       __pio_r_bits         );    /* PIO Output Data Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_PDSR,      0xFFFFF43C, __READ,       __pio_r_bits         );    /* PIO Pin Data Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_IER,       0xFFFFF440, __WRITE,      __pio_r_bits         );    /* PIO Interrupt Enable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_IDR,       0xFFFFF444, __WRITE,      __pio_r_bits         );    /* PIO Interrupt Disable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_IMR,       0xFFFFF448, __READ,       __pio_r_bits         );    /* PIO Interrupt Mask Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_ISR,       0xFFFFF44C, __READ,       __pio_r_bits         );    /* PIO Interrupt Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_MDER,      0xFFFFF450, __WRITE,      __pio_r_bits         );    /* PIO Multi-driver Enable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_MDDR,      0xFFFFF454, __WRITE,      __pio_r_bits         );    /* PIO Multi-driver Disable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_MDSR,      0xFFFFF458, __READ,       __pio_r_bits         );    /* PIO Multi-driver Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_PUDR,      0xFFFFF460, __WRITE,      __pio_r_bits         );    /* PIO Pull-up Disable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_PUER,      0xFFFFF464, __WRITE,      __pio_r_bits         );    /* PIO Pull-up Enable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_PUSR,      0xFFFFF468, __READ,       __pio_r_bits         );    /* PIO Pad Pull-up Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_ASR,       0xFFFFF470, __WRITE,      __pio_r_bits         );    /* PIO Peripheral A Select Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_BSR,       0xFFFFF474, __WRITE,      __pio_r_bits         );    /* PIO Peripheral B Select Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_ABSR,      0xFFFFF478, __READ,       __pio_r_bits         );    /* PIO AB Status Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_OWER,      0xFFFFF4A0, __WRITE,      __pio_r_bits         );    /* PIO Output Write Enable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_OWDR,      0xFFFFF4A4, __WRITE,      __pio_r_bits         );    /* PIO Output Write Disable Register A, init value = 0x00000000 */
__IO_REG32_BIT(PIOA_OWSR,      0xFFFFF4A8, __READ,       __pio_r_bits         );    /* PIO Output Write Status Register A, init value = 0x00000000 */


/***************************************************************************
 **
 **  PIOB : PIO Controller B
 **
 ***************************************************************************/
__IO_REG32_BIT(PIOB_PER,       0xFFFFF600, __WRITE,      __pio_r_bits         );    /* PIO Enable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_PDR,       0xFFFFF604, __WRITE,      __pio_r_bits         );    /* PIO Disable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_PSR,       0xFFFFF608, __READ,       __pio_r_bits         );    /* PIO Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_OER,       0xFFFFF610, __WRITE,      __pio_r_bits         );    /* PIO Output Enable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_ODR,       0xFFFFF614, __WRITE,      __pio_r_bits         );    /* PIO Output Disable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_OSR,       0xFFFFF618, __READ,       __pio_r_bits         );    /* PIO Output Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_IFER,      0xFFFFF620, __WRITE,      __pio_r_bits         );    /* PIO Glitch Input Filter Enable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_IFDR,      0xFFFFF624, __WRITE,      __pio_r_bits         );    /* PIO Glitch Input Filter Disable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_IFSR,      0xFFFFF628, __READ,       __pio_r_bits         );    /* PIO Glitch Input Filter Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_SODR,      0xFFFFF630, __WRITE,      __pio_r_bits         );    /* PIO Set Output Data Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_CODR,      0xFFFFF634, __WRITE,      __pio_r_bits         );    /* PIO Clear Output Data Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_ODSR,      0xFFFFF638, __READ,       __pio_r_bits         );    /* PIO Output Data Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_PDSR,      0xFFFFF63C, __READ,       __pio_r_bits         );    /* PIO Pin Data Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_IER,       0xFFFFF640, __WRITE,      __pio_r_bits         );    /* PIO Interrupt Enable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_IDR,       0xFFFFF644, __WRITE,      __pio_r_bits         );    /* PIO Interrupt Disable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_IMR,       0xFFFFF648, __READ,       __pio_r_bits         );    /* PIO Interrupt Mask Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_ISR,       0xFFFFF64C, __READ,       __pio_r_bits         );    /* PIO Interrupt Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_MDER,      0xFFFFF650, __WRITE,      __pio_r_bits         );    /* PIO Multi-driver Enable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_MDDR,      0xFFFFF654, __WRITE,      __pio_r_bits         );    /* PIO Multi-driver Disable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_MDSR,      0xFFFFF658, __READ,       __pio_r_bits         );    /* PIO Multi-driver Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_PUDR,      0xFFFFF660, __WRITE,      __pio_r_bits         );    /* PIO Pull-up Disable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_PUER,      0xFFFFF664, __WRITE,      __pio_r_bits         );    /* PIO Pull-up Enable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_PUSR,      0xFFFFF668, __READ,       __pio_r_bits         );    /* PIO Pad Pull-up Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_ASR,       0xFFFFF670, __WRITE,      __pio_r_bits         );    /* PIO Peripheral A Select Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_BSR,       0xFFFFF674, __WRITE,      __pio_r_bits         );    /* PIO Peripheral B Select Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_ABSR,      0xFFFFF678, __READ,       __pio_r_bits         );    /* PIO AB Status Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_OWER,      0xFFFFF6A0, __WRITE,      __pio_r_bits         );    /* PIO Output Write Enable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_OWDR,      0xFFFFF6A4, __WRITE,      __pio_r_bits         );    /* PIO Output Write Disable Register B, init value = 0x00000000 */
__IO_REG32_BIT(PIOB_OWSR,      0xFFFFF6A8, __READ,       __pio_r_bits         );    /* PIO Output Write Status Register B, init value = 0x00000000 */

/***************************************************************************
 **
 **  SPI : Serial Peripheral Interface
 **
 ***************************************************************************/
__IO_REG32_BIT(SPI_CR,         0xFFFE0000, __WRITE,      __spi_cr_bits        );    /* Control Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_MR,         0xFFFE0004, __READ_WRITE, __spi_mr_bits        );    /* Mode Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_RDR,        0xFFFE0008, __READ,       __spi_rdr_bits       );    /* Receive Data Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_TDR,        0xFFFE000C, __WRITE,      __spi_tdr_bits       );    /* Transmit Data Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_SR,         0xFFFE0010, __READ,       __spi_sr_bits        );    /* Status Register, init value = 0x000000F0 */
__IO_REG32_BIT(SPI_IER,        0xFFFE0014, __WRITE,      __spi_ir_bits        );    /* Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_IDR,        0xFFFE0018, __WRITE,      __spi_ir_bits        );    /* Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_IMR,        0xFFFE001C, __READ,       __spi_ir_bits        );    /* Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_CSR0,       0xFFFE0030, __READ_WRITE, __spi_csr_bits       );    /* Chip Select Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SPI_CSR1,       0xFFFE0034, __READ_WRITE, __spi_csr_bits       );    /* Chip Select Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SPI_CSR2,       0xFFFE0038, __READ_WRITE, __spi_csr_bits       );    /* Chip Select Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SPI_CSR3,       0xFFFE003C, __READ_WRITE, __spi_csr_bits       );    /* Chip Select Register 3, init value = 0x00000000 */
__IO_REG32_BIT(SPI_RPR,        0xFFFE0100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_RCR,        0xFFFE0104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_TPR,        0xFFFE0108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_TCR,        0xFFFE010C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_RNPR,       0xFFFE0110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_RNCR,       0xFFFE0114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_TNPR,       0xFFFE0118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_TNCR,       0xFFFE011C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_PTCR,       0xFFFE0120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register, init value = 0x00000000 */
__IO_REG32_BIT(SPI_PTSR,       0xFFFE0124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  TWI : Two-Wire Interface
 **
 ***************************************************************************/
__IO_REG32_BIT(TWI_CR,         0xFFFB8000, __WRITE,      __twi_cr_bits        );    /* Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_MMR,        0xFFFB8004, __READ_WRITE, __twi_mmr_bits       );    /* Master Mode Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_IADR,       0xFFFB800C, __READ_WRITE, __twi_iadr_bits      );    /* Internal Address Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_CWGR,       0xFFFB8010, __READ_WRITE, __twi_cwgr_bits      );    /* Clock Waveform Generator Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_SR,         0xFFFB8020, __READ,       __twi_ir_bits        );    /* Status Register, init value = 0x00000008 */
__IO_REG32_BIT(TWI_IER,        0xFFFB8024, __WRITE,      __twi_ir_bits        );    /* Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_IDR,        0xFFFB8028, __WRITE,      __twi_ir_bits        );    /* Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_IMR,        0xFFFB802C, __READ,       __twi_ir_bits        );    /* Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_RHR,        0xFFFB8030, __READ,       __twi_rhr_bits       );    /* Receive Holding Register, init value = 0x00000000 */
__IO_REG32_BIT(TWI_THR,        0xFFFB8034, __READ_WRITE, __twi_thr_bits       );    /* Transmit Holding Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  US0 : Universal Syn Assyn Receive Transmitter 0
 **
 ***************************************************************************/
__IO_REG32_BIT(US0_CR,         0xFFFC0000, __WRITE,      __us_cr_bits         );    /* Control Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_MR,         0xFFFC0004, __READ_WRITE, __us_mr_bits         );    /* Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_IER,        0xFFFC0008, __WRITE,      __us_ir_bits         );    /* Interrupt Enable Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_IDR,        0xFFFC000C, __WRITE,      __us_ir_bits         );    /* Interrupt Disable Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_IMR,        0xFFFC0010, __READ,       __us_ir_bits         );    /* Interrupt Mask Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_CSR,        0xFFFC0014, __READ,       __us_csr_bits        );    /* Channel Status Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_RHR,        0xFFFC0018, __READ,       __us_rhr_bits        );    /* Receiver Holding Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_THR,        0xFFFC001C, __WRITE,      __us_thr_bits        );    /* Transmitter Holding Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_BRGR,       0xFFFC0020, __READ_WRITE, __us_brgr_bits       );    /* Baud Rate Generator Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_RTOR,       0xFFFC0024, __READ_WRITE, __us_rtor_bits       );    /* Receiver Time-out Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_TTGR,       0xFFFC0028, __READ_WRITE, __us_ttgr_bits       );    /* Transmitter Timeguard Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_FIDI,       0xFFFC0040, __READ_WRITE, __us_fidi_bits       );    /* FI DI Ratio Register 0, init value = 0x00000174 */
__IO_REG32_BIT(US0_NER,        0xFFFC0044, __READ,       __us_ner_bits        );    /* Number of Errors Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_IF,         0xFFFC004C, __READ_WRITE, __us_if_bits         );    /* IrDA Filter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_RPR,        0xFFFC0100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_RCR,        0xFFFC0104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_TPR,        0xFFFC0108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_TCR,        0xFFFC010C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_RNPR,       0xFFFC0110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_RNCR,       0xFFFC0114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Registe 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_TNPR,       0xFFFC0118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_TNCR,       0xFFFC011C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_PTCR,       0xFFFC0120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register 0, init value = 0x00000000 */
__IO_REG32_BIT(US0_PTSR,       0xFFFC0124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register 0, init value = 0x00000000 */

/***************************************************************************
 **
 **  US1 : Universal Syn Assyn Receive Transmitter 1
 **
 ***************************************************************************/
__IO_REG32_BIT(US1_CR,         0xFFFC4000, __WRITE,      __us_cr_bits         );    /* Control Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_MR,         0xFFFC4004, __READ_WRITE, __us_mr_bits         );    /* Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_IER,        0xFFFC4008, __WRITE,      __us_ir_bits         );    /* Interrupt Enable Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_IDR,        0xFFFC400C, __WRITE,      __us_ir_bits         );    /* Interrupt Disable Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_IMR,        0xFFFC4010, __READ,       __us_ir_bits         );    /* Interrupt Mask Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_CSR,        0xFFFC4014, __READ,       __us_csr_bits        );    /* Channel Status Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_RHR,        0xFFFC4018, __READ,       __us_rhr_bits        );    /* Receiver Holding Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_THR,        0xFFFC401C, __WRITE,      __us_thr_bits        );    /* Transmitter Holding Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_BRGR,       0xFFFC4020, __READ_WRITE, __us_brgr_bits       );    /* Baud Rate Generator Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_RTOR,       0xFFFC4024, __READ_WRITE, __us_rtor_bits       );    /* Receiver Time-out Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_TTGR,       0xFFFC4028, __READ_WRITE, __us_ttgr_bits       );    /* Transmitter Timeguard Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_FIDI,       0xFFFC4040, __READ_WRITE, __us_fidi_bits       );    /* FI DI Ratio Register 1, init value = 0x00000174 */
__IO_REG32_BIT(US1_NER,        0xFFFC4044, __READ,       __us_ner_bits        );    /* Number of Errors Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_IF,         0xFFFC404C, __READ_WRITE, __us_if_bits         );    /* IrDA Filter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_RPR,        0xFFFC4100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_RCR,        0xFFFC4104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_TPR,        0xFFFC4108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_TCR,        0xFFFC410C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_RNPR,       0xFFFC4110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_RNCR,       0xFFFC4114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_TNPR,       0xFFFC4118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_TNCR,       0xFFFC411C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_PTCR,       0xFFFC4120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register 1, init value = 0x00000000 */
__IO_REG32_BIT(US1_PTSR,       0xFFFC4124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register 1, init value = 0x00000000 */

/***************************************************************************
 **
 **  US2 : Universal Syn Assyn Receive Transmitter 2
 **
 ***************************************************************************/
__IO_REG32_BIT(US2_CR,         0xFFFC8000, __WRITE,      __us_cr_bits         );    /* Control Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_MR,         0xFFFC8004, __READ_WRITE, __us_mr_bits         );    /* Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_IER,        0xFFFC8008, __WRITE,      __us_ir_bits         );    /* Interrupt Enable Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_IDR,        0xFFFC800C, __WRITE,      __us_ir_bits         );    /* Interrupt Disable Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_IMR,        0xFFFC8010, __READ,       __us_ir_bits         );    /* Interrupt Mask Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_CSR,        0xFFFC8014, __READ,       __us_csr_bits        );    /* Channel Status Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_RHR,        0xFFFC8018, __READ,       __us_rhr_bits        );    /* Receiver Holding Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_THR,        0xFFFC801C, __WRITE,      __us_thr_bits        );    /* Transmitter Holding Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_BRGR,       0xFFFC8020, __READ_WRITE, __us_brgr_bits       );    /* Baud Rate Generator Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_RTOR,       0xFFFC8024, __READ_WRITE, __us_rtor_bits       );    /* Receiver Time-out Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_TTGR,       0xFFFC8028, __READ_WRITE, __us_ttgr_bits       );    /* Transmitter Timeguard Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_FIDI,       0xFFFC8040, __READ_WRITE, __us_fidi_bits       );    /* FI DI Ratio Register 2, init value = 0x00000174 */
__IO_REG32_BIT(US2_NER,        0xFFFC8044, __READ,       __us_ner_bits        );    /* Number of Errors Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_IF,         0xFFFC804C, __READ_WRITE, __us_if_bits         );    /* IrDA Filter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_RPR,        0xFFFC8100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_RCR,        0xFFFC8104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_TPR,        0xFFFC8108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_TCR,        0xFFFC810C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_RNPR,       0xFFFC8110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_RNCR,       0xFFFC8114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_TNPR,       0xFFFC8118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_TNCR,       0xFFFC811C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_PTCR,       0xFFFC8120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register 2, init value = 0x00000000 */
__IO_REG32_BIT(US2_PTSR,       0xFFFC8124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register 2, init value = 0x00000000 */

/***************************************************************************
 **
 **  US3 : Universal Syn Assyn Receive Transmitter 3
 **
 ***************************************************************************/
__IO_REG32_BIT(US3_CR,         0xFFFCC000, __WRITE,      __us_cr_bits         );    /* Control Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_MR,         0xFFFCC004, __READ_WRITE, __us_mr_bits         );    /* Mode Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_IER,        0xFFFCC008, __WRITE,      __us_ir_bits         );    /* Interrupt Enable Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_IDR,        0xFFFCC00C, __WRITE,      __us_ir_bits         );    /* Interrupt Disable Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_IMR,        0xFFFCC010, __READ,       __us_ir_bits         );    /* Interrupt Mask Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_CSR,        0xFFFCC014, __READ,       __us_csr_bits        );    /* Channel Status Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_RHR,        0xFFFCC018, __READ,       __us_rhr_bits        );    /* Receiver Holding Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_THR,        0xFFFCC01C, __WRITE,      __us_thr_bits        );    /* Transmitter Holding Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_BRGR,       0xFFFCC020, __READ_WRITE, __us_brgr_bits       );    /* Baud Rate Generator Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_RTOR,       0xFFFCC024, __READ_WRITE, __us_rtor_bits       );    /* Receiver Time-out Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_TTGR,       0xFFFCC028, __READ_WRITE, __us_ttgr_bits       );    /* Transmitter Timeguard Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_FIDI,       0xFFFCC040, __READ_WRITE, __us_fidi_bits       );    /* FI DI Ratio Register 3, init value = 0x00000174 */
__IO_REG32_BIT(US3_NER,        0xFFFCC044, __READ,       __us_ner_bits        );    /* Number of Errors Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_IF,         0xFFFCC04C, __READ_WRITE, __us_if_bits         );    /* IrDA Filter Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_RPR,        0xFFFCC100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_RCR,        0xFFFCC104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_TPR,        0xFFFCC108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_TCR,        0xFFFCC10C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_RNPR,       0xFFFCC110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_RNCR,       0xFFFCC114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_TNPR,       0xFFFCC118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_TNCR,       0xFFFCC11C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_PTCR,       0xFFFCC120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register 3, init value = 0x00000000 */
__IO_REG32_BIT(US3_PTSR,       0xFFFCC124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register 3, init value = 0x00000000 */

/***************************************************************************
 **
 **  SSC0 : Serial Synchronous Controller 0
 **
 ***************************************************************************/
__IO_REG32_BIT(SSC0_CR,        0xFFFD0000, __WRITE,      __ssc_cr_bits        );    /* Control Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_CMR,       0xFFFD0004, __READ_WRITE, __ssc_cmr_bits       );    /* Clock Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RCMR,      0xFFFD0010, __READ_WRITE, __ssc_rtcmr_bits     );    /* Receive Clock Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RFMR,      0xFFFD0014, __READ_WRITE, __ssc_rfmr_bits      );    /* Receive Frame Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_TCMR,      0xFFFD0018, __READ_WRITE, __ssc_rtcmr_bits     );    /* Transmit Clock Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_TFMR,      0xFFFD001C, __READ_WRITE, __ssc_tfmr_bits      );    /* Transmit Frame Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RHR,       0xFFFD0020, __READ,       __ssc_rhr_bits       );    /* Receive Holding Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_THR,       0xFFFD0024, __WRITE,      __ssc_thr_bits       );    /* Transmit Holding Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RSHR,      0xFFFD0030, __READ,       __ssc_rshr_bits      );    /* Receive Sync Holding Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_TSHR,      0xFFFD0034, __READ_WRITE, __ssc_tshr_bits      );    /* Transmit Sync Holding Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_SR,        0xFFFD0040, __READ,       __ssc_sr_bits        );    /* Status Register 0, init value = 0x000000CC */
__IO_REG32_BIT(SSC0_IER,       0xFFFD0044, __WRITE,      __ssc_ir_bits        );    /* Interrupt Enable Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_IDR,       0xFFFD0048, __WRITE,      __ssc_ir_bits        );    /* Interrupt Disable Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_IMR,       0xFFFD004C, __READ,       __ssc_ir_bits        );    /* Interrupt Mask Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RPR,       0xFFFD0100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RCR,       0xFFFD0104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_TPR,       0xFFFD0108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_TCR,       0xFFFD010C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RNPR,      0xFFFD0110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_RNCR,      0xFFFD0114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_TNPR,      0xFFFD0118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_TNCR,      0xFFFD011C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_PTCR,      0xFFFD0120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register 0, init value = 0x00000000 */
__IO_REG32_BIT(SSC0_PTSR,      0xFFFD0124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register 0, init value = 0x00000000 */

/***************************************************************************
 **
 **  SSC1 : Serial Synchronous Controller 1
 **
 ***************************************************************************/
__IO_REG32_BIT(SSC1_CR,        0xFFFD4000, __WRITE,      __ssc_cr_bits        );    /* Control Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_CMR,       0xFFFD4004, __READ_WRITE, __ssc_cmr_bits       );    /* Clock Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RCMR,      0xFFFD4010, __READ_WRITE, __ssc_rtcmr_bits     );    /* Receive Clock Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RFMR,      0xFFFD4014, __READ_WRITE, __ssc_rfmr_bits      );    /* Receive Frame Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_TCMR,      0xFFFD4018, __READ_WRITE, __ssc_rtcmr_bits     );    /* Transmit Clock Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_TFMR,      0xFFFD401C, __READ_WRITE, __ssc_tfmr_bits      );    /* Transmit Frame Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RHR,       0xFFFD4020, __READ,       __ssc_rhr_bits       );    /* Receive Holding Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_THR,       0xFFFD4024, __WRITE,      __ssc_thr_bits       );    /* Transmit Holding Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RSHR,      0xFFFD4030, __READ,       __ssc_rshr_bits      );    /* Receive Sync Holding Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_TSHR,      0xFFFD4034, __READ_WRITE, __ssc_tshr_bits      );    /* Transmit Sync Holding Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_SR,        0xFFFD4040, __READ,       __ssc_sr_bits        );    /* Status Register 1, init value = 0x000000CC */
__IO_REG32_BIT(SSC1_IER,       0xFFFD4044, __WRITE,      __ssc_ir_bits        );    /* Interrupt Enable Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_IDR,       0xFFFD4048, __WRITE,      __ssc_ir_bits        );    /* Interrupt Disable Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_IMR,       0xFFFD404C, __READ,       __ssc_ir_bits        );    /* Interrupt Mask Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RPR,       0xFFFD4100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RCR,       0xFFFD4104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_TPR,       0xFFFD4108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_TCR,       0xFFFD410C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RNPR,      0xFFFD4110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_RNCR,      0xFFFD4114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_TNPR,      0xFFFD4118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_TNCR,      0xFFFD411C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_PTCR,      0xFFFD4120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register 1, init value = 0x00000000 */
__IO_REG32_BIT(SSC1_PTSR,      0xFFFD4124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register 1, init value = 0x00000000 */

/***************************************************************************
 **
 **  SSC2 : Serial Synchronous Controller 2
 **
 ***************************************************************************/
__IO_REG32_BIT(SSC2_CR,        0xFFFD8000, __WRITE,      __ssc_cr_bits        );    /* Control Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_CMR,       0xFFFD8004, __READ_WRITE, __ssc_cmr_bits       );    /* Clock Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RCMR,      0xFFFD8010, __READ_WRITE, __ssc_rtcmr_bits     );    /* Receive Clock Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RFMR,      0xFFFD8014, __READ_WRITE, __ssc_rfmr_bits      );    /* Receive Frame Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_TCMR,      0xFFFD8018, __READ_WRITE, __ssc_rtcmr_bits     );    /* Transmit Clock Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_TFMR,      0xFFFD801C, __READ_WRITE, __ssc_tfmr_bits      );    /* Transmit Frame Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RHR,       0xFFFD8020, __READ,       __ssc_rhr_bits       );    /* Receive Holding Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_THR,       0xFFFD8024, __WRITE,      __ssc_thr_bits       );    /* Transmit Holding Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RSHR,      0xFFFD8030, __READ,       __ssc_rshr_bits      );    /* Receive Sync Holding Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_TSHR,      0xFFFD8034, __READ_WRITE, __ssc_tshr_bits      );    /* Transmit Sync Holding Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_SR,        0xFFFD8040, __READ,       __ssc_sr_bits        );    /* Status Register 2, init value = 0x000000CC */
__IO_REG32_BIT(SSC2_IER,       0xFFFD8044, __WRITE,      __ssc_ir_bits        );    /* Interrupt Enable Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_IDR,       0xFFFD8048, __WRITE,      __ssc_ir_bits        );    /* Interrupt Disable Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_IMR,       0xFFFD804C, __READ,       __ssc_ir_bits        );    /* Interrupt Mask Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RPR,       0xFFFD8100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RCR,       0xFFFD8104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_TPR,       0xFFFD8108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_TCR,       0xFFFD810C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RNPR,      0xFFFD8110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_RNCR,      0xFFFD8114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_TNPR,      0xFFFD8118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_TNCR,      0xFFFD811C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_PTCR,      0xFFFD8120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register 2, init value = 0x00000000 */
__IO_REG32_BIT(SSC2_PTSR,      0xFFFD8124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register 2, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC0 : Timer Counter 0
 **
 ***************************************************************************/
__IO_REG32_BIT(TC0_CCR,        0xFFFA0000, __WRITE,      __tc_ccr_bits        );    /* Channel Control Register 0, init value = 0x00000000 */
__IO_REG32_BIT(TC0_CMR,        0xFFFA0004, __READ_WRITE, __tc_cmr_bits        );    /* Channel Mode Register 0, init value = 0x00000000 */
__IO_REG32_BIT(TC0_CV,         0xFFFA0010, __READ,       __tc_cv_bits         );    /* Counter Value, init value = 0x00000000 */
__IO_REG32_BIT(TC0_RA,         0xFFFA0014, __READ_WRITE, __tc_ra_bits         );    /* Register A, init value = 0x00000000 */
__IO_REG32_BIT(TC0_RB,         0xFFFA0018, __READ_WRITE, __tc_rb_bits         );    /* Register B, init value = 0x00000000 */
__IO_REG32_BIT(TC0_RC,         0xFFFA001C, __READ_WRITE, __tc_rc_bits         );    /* Register C, init value = 0x00000000 */
__IO_REG32_BIT(TC0_SR,         0xFFFA0020, __READ,       __tc_sr_bits         );    /* Status Register 0, init value = 0x00000000 */
__IO_REG32_BIT(TC0_IER,        0xFFFA0024, __WRITE,      __tc_ir_bits         );    /* Interrupt Enable Register 0, init value = 0x00000000 */
__IO_REG32_BIT(TC0_IDR,        0xFFFA0028, __WRITE,      __tc_ir_bits         );    /* Interrupt Disable Register 0, init value = 0x00000000 */
__IO_REG32_BIT(TC0_IMR,        0xFFFA002C, __READ,       __tc_ir_bits         );    /* Interrupt Mask Register 0, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC1 : Timer Counter 1
 **
 ***************************************************************************/
__IO_REG32_BIT(TC1_CCR,        0xFFFA0040, __WRITE,      __tc_ccr_bits        );    /* Channel Control Register 1, init value = 0x00000000 */
__IO_REG32_BIT(TC1_CMR,        0xFFFA0044, __READ_WRITE, __tc_cmr_bits        );    /* Channel Mode Register 1, init value = 0x00000000 */
__IO_REG32_BIT(TC1_CV,         0xFFFA0050, __READ,       __tc_cv_bits         );    /* Counter Value, init value = 0x00000000 */
__IO_REG32_BIT(TC1_RA,         0xFFFA0054, __READ_WRITE, __tc_ra_bits         );    /* Register A, init value = 0x00000000 */
__IO_REG32_BIT(TC1_RB,         0xFFFA0058, __READ_WRITE, __tc_rb_bits         );    /* Register B, init value = 0x00000000 */
__IO_REG32_BIT(TC1_RC,         0xFFFA005C, __READ_WRITE, __tc_rc_bits         );    /* Register C, init value = 0x00000000 */
__IO_REG32_BIT(TC1_SR,         0xFFFA0060, __READ,       __tc_sr_bits         );    /* Status Register 1, init value = 0x00000000 */
__IO_REG32_BIT(TC1_IER,        0xFFFA0064, __WRITE,      __tc_ir_bits         );    /* Interrupt Enable Register 1, init value = 0x00000000 */
__IO_REG32_BIT(TC1_IDR,        0xFFFA0068, __WRITE,      __tc_ir_bits         );    /* Interrupt Disable Register 1, init value = 0x00000000 */
__IO_REG32_BIT(TC1_IMR,        0xFFFA006C, __READ,       __tc_ir_bits         );    /* Interrupt Mask Register 1, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC2 : Timer Counter 2
 **
 ***************************************************************************/
__IO_REG32_BIT(TC2_CCR,        0xFFFA0080, __WRITE,      __tc_ccr_bits        );    /* Channel Control Register 2, init value = 0x00000000 */
__IO_REG32_BIT(TC2_CMR,        0xFFFA0084, __READ_WRITE, __tc_cmr_bits        );    /* Channel Mode Register 2, init value = 0x00000000 */
__IO_REG32_BIT(TC2_CV,         0xFFFA0090, __READ,       __tc_cv_bits         );    /* Counter Value, init value = 0x00000000 */
__IO_REG32_BIT(TC2_RA,         0xFFFA0094, __READ_WRITE, __tc_ra_bits         );    /* Register A, init value = 0x00000000 */
__IO_REG32_BIT(TC2_RB,         0xFFFA0098, __READ_WRITE, __tc_rb_bits         );    /* Register B, init value = 0x00000000 */
__IO_REG32_BIT(TC2_RC,         0xFFFA009C, __READ_WRITE, __tc_rc_bits         );    /* Register C, init value = 0x00000000 */
__IO_REG32_BIT(TC2_SR,         0xFFFA00A0, __READ,       __tc_sr_bits         );    /* Status Register 2, init value = 0x00000000 */
__IO_REG32_BIT(TC2_IER,        0xFFFA00A4, __WRITE,      __tc_ir_bits         );    /* Interrupt Enable Register 2, init value = 0x00000000 */
__IO_REG32_BIT(TC2_IDR,        0xFFFA00A8, __WRITE,      __tc_ir_bits         );    /* Interrupt Disable Register 2, init value = 0x00000000 */
__IO_REG32_BIT(TC2_IMR,        0xFFFA00AC, __READ,       __tc_ir_bits         );    /* Interrupt Mask Register 2, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC3 : Timer Counter 3
 **
 ***************************************************************************/
__IO_REG32_BIT(TC3_CCR,        0xFFFA4000, __WRITE,      __tc_ccr_bits        );    /* Channel Control Register 3, init value = 0x00000000 */
__IO_REG32_BIT(TC3_CMR,        0xFFFA4004, __READ_WRITE, __tc_cmr_bits        );    /* Channel Mode Register 3, init value = 0x00000000 */
__IO_REG32_BIT(TC3_CV,         0xFFFA4010, __READ,       __tc_cv_bits         );    /* Counter Value, init value = 0x00000000 */
__IO_REG32_BIT(TC3_RA,         0xFFFA4014, __READ_WRITE, __tc_ra_bits         );    /* Register A, init value = 0x00000000 */
__IO_REG32_BIT(TC3_RB,         0xFFFA4018, __READ_WRITE, __tc_rb_bits         );    /* Register B, init value = 0x00000000 */
__IO_REG32_BIT(TC3_RC,         0xFFFA401C, __READ_WRITE, __tc_rc_bits         );    /* Register C, init value = 0x00000000 */
__IO_REG32_BIT(TC3_SR,         0xFFFA4020, __READ,       __tc_sr_bits         );    /* Status Register 3, init value = 0x00000000 */
__IO_REG32_BIT(TC3_IER,        0xFFFA4024, __WRITE,      __tc_ir_bits         );    /* Interrupt Enable Register 3, init value = 0x00000000 */
__IO_REG32_BIT(TC3_IDR,        0xFFFA4028, __WRITE,      __tc_ir_bits         );    /* Interrupt Disable Register 3, init value = 0x00000000 */
__IO_REG32_BIT(TC3_IMR,        0xFFFA402C, __READ,       __tc_ir_bits         );    /* Interrupt Mask Register 3, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC4 : Timer Counter 4
 **
 ***************************************************************************/
__IO_REG32_BIT(TC4_CCR,        0xFFFA4040, __WRITE,      __tc_ccr_bits        );    /* Channel Control Register 4, init value = 0x00000000 */
__IO_REG32_BIT(TC4_CMR,        0xFFFA4044, __READ_WRITE, __tc_cmr_bits        );    /* Channel Mode Register 4, init value = 0x00000000 */
__IO_REG32_BIT(TC4_CV,         0xFFFA4050, __READ,       __tc_cv_bits         );    /* Counter Value, init value = 0x00000000 */
__IO_REG32_BIT(TC4_RA,         0xFFFA4054, __READ_WRITE, __tc_ra_bits         );    /* Register A, init value = 0x00000000 */
__IO_REG32_BIT(TC4_RB,         0xFFFA4058, __READ_WRITE, __tc_rb_bits         );    /* Register B, init value = 0x00000000 */
__IO_REG32_BIT(TC4_RC,         0xFFFA405C, __READ_WRITE, __tc_rc_bits         );    /* Register C, init value = 0x00000000 */
__IO_REG32_BIT(TC4_SR,         0xFFFA4060, __READ,       __tc_sr_bits         );    /* Status Register 4, init value = 0x00000000 */
__IO_REG32_BIT(TC4_IER,        0xFFFA4064, __WRITE,      __tc_ir_bits         );    /* Interrupt Enable Register 4, init value = 0x00000000 */
__IO_REG32_BIT(TC4_IDR,        0xFFFA4068, __WRITE,      __tc_ir_bits         );    /* Interrupt Disable Register 4, init value = 0x00000000 */
__IO_REG32_BIT(TC4_IMR,        0xFFFA406C, __READ,       __tc_ir_bits         );    /* Interrupt Mask Register 4, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC5 : Timer Counter 5
 **
 ***************************************************************************/
__IO_REG32_BIT(TC5_CCR,        0xFFFA4080, __WRITE,      __tc_ccr_bits        );    /* Channel Control Register 5, init value = 0x00000000 */
__IO_REG32_BIT(TC5_CMR,        0xFFFA4084, __READ_WRITE, __tc_cmr_bits        );    /* Channel Mode Register 5, init value = 0x00000000 */
__IO_REG32_BIT(TC5_CV,         0xFFFA4090, __READ,       __tc_cv_bits         );    /* Counter Value, init value = 0x00000000 */
__IO_REG32_BIT(TC5_RA,         0xFFFA4094, __READ_WRITE, __tc_ra_bits         );    /* Register A, init value = 0x00000000 */
__IO_REG32_BIT(TC5_RB,         0xFFFA4098, __READ_WRITE, __tc_rb_bits         );    /* Register B, init value = 0x00000000 */
__IO_REG32_BIT(TC5_RC,         0xFFFA409C, __READ_WRITE, __tc_rc_bits         );    /* Register C, init value = 0x00000000 */
__IO_REG32_BIT(TC5_SR,         0xFFFA40A0, __READ,       __tc_sr_bits         );    /* Status Register 5, init value = 0x00000000 */
__IO_REG32_BIT(TC5_IER,        0xFFFA40A4, __WRITE,      __tc_ir_bits         );    /* Interrupt Enable Register 5, init value = 0x00000000 */
__IO_REG32_BIT(TC5_IDR,        0xFFFA40A8, __WRITE,      __tc_ir_bits         );    /* Interrupt Disable Register 5, init value = 0x00000000 */
__IO_REG32_BIT(TC5_IMR,        0xFFFA40AC, __READ,       __tc_ir_bits         );    /* Interrupt Mask Register 5, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC012 : Timer Counter 0 1 2
 **
 ***************************************************************************/
__IO_REG32_BIT(TC012_BCR,      0xFFFA00C0, __WRITE,      __tc_bcr_bits        );    /* TC Block Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TC012_BMR,      0xFFFA00C4, __READ_WRITE, __tc012_bmr_bits     );    /* TC Block Mode Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  TC345 : Timer Counter 3 4 5
 **
 ***************************************************************************/
__IO_REG32_BIT(TC345_BCR,      0xFFFA40C0, __WRITE,      __tc_bcr_bits        );    /* TC Block Control Register, init value = 0x00000000 */
__IO_REG32_BIT(TC345_BMR,      0xFFFA40C4, __READ_WRITE, __tc345_bmr_bits     );    /* TC Block Mode Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  MCI : Multimedia Card Interface
 **
 ***************************************************************************/
__IO_REG32_BIT(MCI_CR,         0xFFFB4000, __WRITE,      __mci_cr_bits        );    /* Control Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_MR,         0xFFFB4004, __READ_WRITE, __mci_mr_bits        );    /* Mode Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_DTOR,       0xFFFB4008, __READ_WRITE, __mci_dtor_bits      );    /* Data Timeout Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_SDCR,       0xFFFB400C, __READ_WRITE, __mci_sdcr_bits      );    /* SD Card Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_ARGR,       0xFFFB4010, __READ_WRITE, __mci_argr_bits      );    /* Argument Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_CMDR,       0xFFFB4014, __WRITE,      __mci_cmdr_bits      );    /* Command Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RSPR,       0xFFFB4020, __READ,       __mci_rspr_bits      );    /* Response Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RSPR1,      0xFFFB4024, __READ,       __mci_rspr_bits      );    /* Response Register 1, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RSPR2,      0xFFFB4028, __READ,       __mci_rspr_bits      );    /* Response Register 2, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RSPR3,      0xFFFB402C, __READ,       __mci_rspr_bits      );    /* Response Register 3, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RDR,        0xFFFB4030, __READ,       __mci_dr_bits        );    /* Receive Data Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_TDR,        0xFFFB4034, __WRITE,      __mci_dr_bits        );    /* Transmit Data Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_SR,         0xFFFB4040, __READ,       __mci_ir_bits        );    /* Status Register, init value = 0x0000C0E5 */
__IO_REG32_BIT(MCI_IER,        0xFFFB4044, __WRITE,      __mci_ir_bits        );    /* Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_IDR,        0xFFFB4048, __WRITE,      __mci_ir_bits        );    /* Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_IMR,        0xFFFB404C, __READ,       __mci_ir_bits        );    /* Interrupt Mask Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RPR,        0xFFFB4100, __READ_WRITE, __periph_rpr_bits    );    /* PDC Receive Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RCR,        0xFFFB4104, __READ_WRITE, __periph_rcr_bits    );    /* PDC Receive Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_TPR,        0xFFFB4108, __READ_WRITE, __periph_tpr_bits    );    /* PDC Transmit Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_TCR,        0xFFFB410C, __READ_WRITE, __periph_tcr_bits    );    /* PDC Transmit Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RNPR,       0xFFFB4110, __READ_WRITE, __periph_rnpr_bits   );    /* PDC Receive Next Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_RNCR,       0xFFFB4114, __READ_WRITE, __periph_rncr_bits   );    /* PDC Receive Next Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_TNPR,       0xFFFB4118, __READ_WRITE, __periph_tnpr_bits   );    /* PDC Transmit Next Pointer Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_TNCR,       0xFFFB411C, __READ_WRITE, __periph_tncr_bits   );    /* PDC Transmit Next Counter Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_PTCR,       0xFFFB4120, __WRITE,      __periph_ptcr_bits   );    /* PDC Transfer Control Register, init value = 0x00000000 */
__IO_REG32_BIT(MCI_PTSR,       0xFFFB4124, __READ,       __periph_ptsr_bits   );    /* PDC Transfer Status Register, init value = 0x00000000 */

/***************************************************************************
 **
 **  UDP : USB Device Port
 **
 ***************************************************************************/
__IO_REG32_BIT(USB_FRM_NUM,    0xFFFB0000, __READ,       __usb_frm_num_bits   );    /* Frame Number Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_GLB_STAT,   0xFFFB0004, __READ_WRITE, __usb_glb_stat_bits  );    /* Global State Register, init value = 0x00000010 */
__IO_REG32_BIT(USB_FADDR,      0xFFFB0008, __READ_WRITE, __usb_faddr_bits     );    /* Function Address Register, init value = 0x00000100 */
__IO_REG32_BIT(USB_IER,        0xFFFB0010, __WRITE,      __usb_ir_bits        );    /* Interrupt Enable Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_IDR,        0xFFFB0014, __WRITE,      __usb_ir_bits        );    /* Interrupt Disable Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_IMR,        0xFFFB0018, __READ,       __usb_ir_bits        );    /* Interrupt Mask Register, init value = 0x00001200 */
__IO_REG32_BIT(USB_ISR,        0xFFFB001C, __READ,       __usb_isr_bits       );    /* Interrupt Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_ICR,        0xFFFB0020, __WRITE,      __usb_icr_bits       );    /* Interrupt Clear Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_RST_EP,     0xFFFB0028, __READ_WRITE, __usb_rst_ep_bits    );    /* Reset Endpoint Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR0,       0xFFFB0030, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 0 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR1,       0xFFFB0034, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 1 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR2,       0xFFFB0038, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 2 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR3,       0xFFFB003C, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 3 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR4,       0xFFFB0040, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 4 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR5,       0xFFFB0044, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 5 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR6,       0xFFFB0048, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 6 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_CSR7,       0xFFFB004C, __READ_WRITE, __usb_csr_bits       );    /* Endpoint 7 Control and Status Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR0,       0xFFFB0050, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 0 FIFO Data Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR1,       0xFFFB0054, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 1 FIFO Data Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR2,       0xFFFB0058, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 2 FIFO Data Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR3,       0xFFFB005C, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 3 FIFO Data Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR4,       0xFFFB0060, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 4 FIFO Data Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR5,       0xFFFB0064, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 5 FIFO Data Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR6,       0xFFFB0068, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 6 FIFO Data Register, init value = 0x00000000 */
__IO_REG32_BIT(USB_FDR7,       0xFFFB006C, __READ_WRITE, __usb_fdr_bits       );    /* Endpoint 7 FIFO Data Register, init value = 0x00000000 */

/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  Interrupt sources
 **
 ***************************************************************************/
#define INO_FIQ             0
#define INO_SYSIRQ          1
#define INO_PIOA            2
#define INO_PIOB            3
#define INO_US0             6
#define INO_US1             7
#define INO_US2             8
#define INO_US3             9
#define INO_MCI            10
#define INO_UDP            11
#define INO_TWI            12
#define INO_SPI            13
#define INO_SSC0           14
#define INO_SSC1           15
#define INO_SSC2           16
#define INO_TC0            17
#define INO_TC1            18
#define INO_TC2            19
#define INO_TC3            20
#define INO_TC4            21
#define INO_TC5            22
#define INO_IRQ0           25
#define INO_IRQ1           26
#define INO_IRQ2           27
#define INO_IRQ3           28
#define INO_IRQ4           29
#define INO_IRQ5           30
#define INO_IRQ6           31


#endif    /* __IOAT91RM3400_H */
