/***************************************************************************
 **
 **    This file defines the Special Function Registers for the
 **    Motorola MAC7100 microcontroller family
 **    (MAC7101 MAC7106 MAC7111 MAC7112 MAC7116 MAC7121)
 **    (MAC7122 MAC7126 MAC7131 MAC7136 MAC7141 MAC7142)
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.8 $
 **
 **    Some registers / registergroups not available on 71x2 devices
 ***************************************************************************/

#ifndef __IOMAC7100_H
#define __IOMAC7100_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ARM IAR compiler and assembler
#endif


#include "io_macros.h"
/***************************************************************************
 ***************************************************************************
 **
 **    MAC7100 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/
#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* AIPS - Master Protection Register */
typedef struct{
__REG32       :24;
__REG32 MPL1  : 1;
__REG32 MTW1  : 1;
__REG32 MTR1  : 1;
__REG32       : 1;
__REG32 MPL0  : 1;
__REG32 MTW0  : 1;
__REG32 MTR0  : 1;
__REG32       : 1;
} __mpra_bits;

/* AIPS - Peripheral Access Control Register A */
typedef struct{
__REG32      :20;
__REG32 TP2  : 1;
__REG32 WP2  : 1;
__REG32 SP2  : 1;
__REG32      : 1;
__REG32 TP1  : 1;
__REG32 WP1  : 1;
__REG32 SP1  : 1;
__REG32      : 1;
__REG32 TP0  : 1;
__REG32 WP0  : 1;
__REG32 SP0  : 1;
__REG32      : 1;
} __pacra_bits;

/* AIPS - Peripheral Access Control Register C */
typedef struct{
__REG32       :20;
__REG32 TP18  : 1;
__REG32 WP18  : 1;
__REG32 SP18  : 1;
__REG32       : 1;
__REG32 TP17  : 1;
__REG32 WP17  : 1;
__REG32 SP17  : 1;
__REG32       : 1;
__REG32 TP16  : 1;
__REG32 WP16  : 1;
__REG32 SP16  : 1;
__REG32       : 1;
} __pacrc_bits;

/* AIPS - Off-Platform Peripheral Access Control Register A */
typedef struct{
__REG32 TP7  : 1;
__REG32 WP7  : 1;
__REG32 SP7  : 1;
__REG32      : 1;
__REG32 TP6  : 1;
__REG32 WP6  : 1;
__REG32 SP6  : 1;
__REG32      : 1;
__REG32 TP5  : 1;
__REG32 WP5  : 1;
__REG32 SP5  : 1;
__REG32      : 1;
__REG32 TP4  : 1;
__REG32 WP4  : 1;
__REG32 SP4  : 1;
__REG32      : 1;
__REG32 TP3  : 1;
__REG32 WP3  : 1;
__REG32 SP3  : 1;
__REG32      : 1;
__REG32 TP2  : 1;
__REG32 WP2  : 1;
__REG32 SP2  : 1;
__REG32      : 1;
__REG32 TP1  : 1;
__REG32 WP1  : 1;
__REG32 SP1  : 1;
__REG32      : 1;
__REG32 TP0  : 1;
__REG32 WP0  : 1;
__REG32 SP0  : 1;
__REG32      : 1;
} __opacra_bits;

/* AIPS - Off-Platform Peripheral Access Control Register B */
typedef struct{
__REG32       : 4;
__REG32 TP14  : 1;
__REG32 WP14  : 1;
__REG32 SP14  : 1;
__REG32       : 1;
__REG32 TP13  : 1;
__REG32 WP13  : 1;
__REG32 SP13  : 1;
__REG32       : 1;
__REG32       : 4;
__REG32 TP11  : 1;
__REG32 WP11  : 1;
__REG32 SP11  : 1;
__REG32       : 1;
__REG32       : 8;
__REG32 TP8   : 1;
__REG32 WP8   : 1;
__REG32 SP8   : 1;
__REG32       : 1;
} __opacrb_bits;

/* AIPS - Off-Platform Peripheral Access Control Register C */
typedef struct{
__REG32 TP23  : 1;
__REG32 WP23  : 1;
__REG32 SP23  : 1;
__REG32       : 1;
__REG32       : 8;
__REG32 TP20  : 1;
__REG32 WP20  : 1;
__REG32 SP20  : 1;
__REG32       : 1;
__REG32 TP19  : 1;
__REG32 WP19  : 1;
__REG32 SP19  : 1;
__REG32       : 1;
__REG32 TP18  : 1;
__REG32 WP18  : 1;
__REG32 SP18  : 1;
__REG32       : 1;
__REG32 TP17  : 1;
__REG32 WP17  : 1;
__REG32 SP17  : 1;
__REG32       : 1;
__REG32       : 4;
} __opacrc_bits;

/* AIPS - Off-Platform Peripheral Access Control Register D */
typedef struct{
__REG32       :12;
__REG32 TP28  : 1;
__REG32 WP28  : 1;
__REG32 SP28  : 1;
__REG32       : 1;
__REG32       : 4;
__REG32 TP26  : 1;
__REG32 WP26  : 1;
__REG32 SP26  : 1;
__REG32       : 1;
__REG32 TP25  : 1;
__REG32 WP25  : 1;
__REG32 SP25  : 1;
__REG32       : 1;
__REG32 TP24  : 1;
__REG32 WP24  : 1;
__REG32 SP24  : 1;
__REG32       : 1;
} __opacrd_bits;

/* AIPS - Off-Platform Peripheral Access Control Register E */
typedef struct{
__REG32       :24;
__REG32 TP33  : 1;
__REG32 WP33  : 1;
__REG32 SP33  : 1;
__REG32       : 1;
__REG32 TP32  : 1;
__REG32 WP32  : 1;
__REG32 SP32  : 1;
__REG32       : 1;
} __opacre_bits;

/* XBS - Priority Registers */
typedef struct{
__REG32 CORE_MSTR  : 1;
__REG32            : 3;
__REG32 DMA_MSTR   : 1;
__REG32            :27;
} __prport_bits;

/* XBS - Control Registers */
typedef struct{
__REG32 PARK  : 1;
__REG32       : 3;
__REG32 PCTL  : 2;
__REG32       : 2;
__REG32 ARB   : 2;
__REG32       :20;
__REG32 HLP   : 1;
__REG32 RO    : 1;
} __crport_bits;

#ifndef MAC71X2 /* Registers not available on 71x2 devices */
/* EIM - Chip Select Mask Registers */
typedef struct{
__REG32 V    : 1;
__REG32 UD   : 1;
__REG32 UC   : 1;
__REG32 SD   : 1;
__REG32 SC   : 1;
__REG32 C_I  : 1;
__REG32 AM   : 1;
__REG32      : 1;
__REG32 WP   : 1;
__REG32      : 7;
__REG32 BAM  :16;
} __csmrn_bits;

/* EIM - Chip Select Control Register */
typedef struct{
__REG16       : 3;
__REG16 BSTW  : 1;
__REG16 BSTR  : 1;
__REG16 BEM   : 1;
__REG16 PS    : 2;
__REG16 AA    : 1;
__REG16       : 1;
__REG16 WS    : 4;
__REG16       : 2;
} __cscrn_bits;
#endif /*mac71x2*/

/* MCM - Device Revision Register */
typedef struct{
__REG16 MSKMIN  : 4;
__REG16 MSKMAJ  : 4;
__REG16 FAMMIN  : 4;
__REG16 FAMMAJ  : 4;
} __rev_bits;

/* MCM - XBS Master Configuration Register */
typedef struct{
__REG8  XMC0  : 1;
__REG8  XMC1  : 1;
__REG8  XMC2  : 1;
__REG8  XMC3  : 1;
__REG8  XMC4  : 1;
__REG8  XMC5  : 1;
__REG8  XMC6  : 1;
__REG8  XMC7  : 1;
} __amc_bits;

/* MCM - XBS Slave Configuration Register */
typedef struct{
__REG8  XSC0  : 1;
__REG8  XSC1  : 1;
__REG8  XSC2  : 1;
__REG8  XSC3  : 1;
__REG8  XSC4  : 1;
__REG8  XSC5  : 1;
__REG8  XSC6  : 1;
__REG8  XSC7  : 1;
} __asc_bits;

/* MCM - IPS On-Platform Module Configuration Register */
typedef struct{
__REG32 PMC0   : 1;
__REG32 PMC1   : 1;
__REG32 PMC2   : 1;
__REG32 PMC3   : 1;
__REG32 PMC4   : 1;
__REG32 PMC5   : 1;
__REG32 PMC6   : 1;
__REG32 PMC7   : 1;
__REG32 PMC8   : 1;
__REG32 PMC9   : 1;
__REG32 PMC10  : 1;
__REG32 PMC11  : 1;
__REG32 PMC12  : 1;
__REG32 PMC13  : 1;
__REG32 PMC14  : 1;
__REG32 PMC15  : 1;
__REG32 PMC16  : 1;
__REG32 PMC17  : 1;
__REG32 PMC18  : 1;
__REG32 PMC19  : 1;
__REG32 PMC20  : 1;
__REG32 PMC21  : 1;
__REG32 PMC22  : 1;
__REG32 PMC23  : 1;
__REG32 PMC24  : 1;
__REG32 PMC25  : 1;
__REG32 PMC26  : 1;
__REG32 PMC27  : 1;
__REG32 PMC28  : 1;
__REG32 PMC29  : 1;
__REG32 PMC30  : 1;
__REG32 PMC31  : 1;
} __iopmc_bits;

/* MCM - Reset Status Register */
typedef struct{
__REG8        : 5;
__REG8  SWTR  : 1;
__REG8  DIR   : 1;
__REG8  POR   : 1;
} __mrsr_bits;

/* MCM - Wake-up Control Register */
typedef struct{
__REG8  PRILVL  : 4;
__REG8          : 3;
__REG8  ENBWCR  : 1;
} __mwcr_bits;

/* MCM - Software Watchdog Timer Control Register */
typedef struct{
__REG16 SWT      : 5;
__REG16 SWRI     : 2;
__REG16 SWE      : 1;
__REG16 SWRWH    : 1;
__REG16 SWCIN16  : 1;
__REG16          : 5;
__REG16 RO       : 1;
} __mswtcr_bits;

/* MCM - SWT Timer Interrupt Register */
typedef struct{
__REG8  SWTIC  : 1;
__REG8         : 7;
} __mswtir_bits;

/* MCM - XBS Address Map Register */
typedef struct{
__REG32 A0Slave  : 3;
__REG32 EA0      : 1;
__REG32 A1Slave  : 3;
__REG32 EA1      : 1;
__REG32 A2Slave  : 3;
__REG32 EA2      : 1;
__REG32 A3Slave  : 3;
__REG32 EA3      : 1;
__REG32 A4Slave  : 3;
__REG32 EA4      : 1;
__REG32 A5Slave  : 3;
__REG32 EA5      : 1;
__REG32 A6Slave  : 3;
__REG32 EA6      : 1;
__REG32 A7Slave  : 3;
__REG32 EA7      : 1;
} __aamr_bits;

/* MCM - Core Fault Location Register */
typedef struct{
__REG8            : 7;
__REG8  LocalErr  : 1;
} __cfloc_bits;

/* MCM - Core Fault Attributes Register */
typedef struct{
__REG8  PROT0  : 1;
__REG8  PROT1  : 1;
__REG8  PROT2  : 1;
__REG8  PROT3  : 1;
__REG8  SIZE   : 3;
__REG8  WRITE  : 1;
} __cfatr_bits;

/* eDMA - Control Register */
typedef struct{
__REG32       : 2;
__REG32 ERCA  : 1;
__REG32       :29;
} __dmacr_bits;

/* eDMA - Error Status Register */
typedef struct{
__REG32 DBE     : 1;
__REG32 SBE     : 1;
__REG32 SGE     : 1;
__REG32 NCE     : 1;
__REG32 DOE     : 1;
__REG32 DAE     : 1;
__REG32 SOE     : 1;
__REG32 SAE     : 1;
__REG32 ERRCHN  : 4;
__REG32         : 2;
__REG32 CPE     : 1;
__REG32         :16;
__REG32 VLD     : 1;
} __dmaes_bits;

/* eDMA - Enable Request Register */
typedef struct{
__REG16 ERQ0   : 1;
__REG16 ERQ1   : 1;
__REG16 ERQ2   : 1;
__REG16 ERQ3   : 1;
__REG16 ERQ4   : 1;
__REG16 ERQ5   : 1;
__REG16 ERQ6   : 1;
__REG16 ERQ7   : 1;
__REG16 ERQ8   : 1;
__REG16 ERQ9   : 1;
__REG16 ERQ10  : 1;
__REG16 ERQ11  : 1;
__REG16 ERQ12  : 1;
__REG16 ERQ13  : 1;
__REG16 ERQ14  : 1;
__REG16 ERQ15  : 1;
} __dmaerq_bits;


/* eDMA - Enable Error Interrupt Register */
typedef struct{
__REG16 EEI0   : 1;
__REG16 EEI1   : 1;
__REG16 EEI2   : 1;
__REG16 EEI3   : 1;
__REG16 EEI4   : 1;
__REG16 EEI5   : 1;
__REG16 EEI6   : 1;
__REG16 EEI7   : 1;
__REG16 EEI8   : 1;
__REG16 EEI9   : 1;
__REG16 EEI10  : 1;
__REG16 EEI11  : 1;
__REG16 EEI12  : 1;
__REG16 EEI13  : 1;
__REG16 EEI14  : 1;
__REG16 EEI15  : 1;
} __dmaeei_bits;

/* eDMA - Set Enable Request Register */
typedef struct{
__REG8  SERQ  : 4;
__REG8        : 2;
__REG8  SAER  : 1;
__REG8        : 1;
} __dmaserq_bits;

/* eDMA - Clear Enable Request Register */
typedef struct{
__REG8  CERQ  : 4;
__REG8        : 2;
__REG8  CAER  : 1;
__REG8        : 1;
} __dmacerq_bits;

/* eDMA - Set Enable Error Interrupt Register */
typedef struct{
__REG8  SEEI  : 4;
__REG8        : 2;
__REG8  SAEE  : 1;
__REG8        : 1;
} __dmaseei_bits;

/* eDMA - Clear Enable Error Interrupt Register */
typedef struct{
__REG8  CEEI  : 4;
__REG8        : 2;
__REG8  CAEE  : 1;
__REG8        : 1;
} __dmaceei_bits;

/* eDMA - Clear Interrupt Request Register */
typedef struct{
__REG8  CINT  : 4;
__REG8        : 2;
__REG8  CAIR  : 1;
__REG8        : 1;
} __dmacint_bits;

/* eDMA - Clear Error Register */
typedef struct{
__REG8  CERR  : 4;
__REG8        : 2;
__REG8  CAER  : 1;
__REG8        : 1;
} __dmacerr_bits;

/* eDMA - Set START Bit Register */
typedef struct{
__REG8  SSRT  : 4;
__REG8        : 2;
__REG8  SAST  : 1;
__REG8        : 1;
} __dmassrt_bits;

/* eDMA - Clear Done Status Register */
typedef struct{
__REG8  CDNE  : 4;
__REG8        : 2;
__REG8  CADN  : 1;
__REG8        : 1;
} __dmacdne_bits;

/* eDMA - Interrupt Request Register */
typedef struct{
__REG16 INT0   : 1;
__REG16 INT1   : 1;
__REG16 INT2   : 1;
__REG16 INT3   : 1;
__REG16 INT4   : 1;
__REG16 INT5   : 1;
__REG16 INT6   : 1;
__REG16 INT7   : 1;
__REG16 INT8   : 1;
__REG16 INT9   : 1;
__REG16 INT10  : 1;
__REG16 INT11  : 1;
__REG16 INT12  : 1;
__REG16 INT13  : 1;
__REG16 INT14  : 1;
__REG16 INT15  : 1;
} __dmaint_bits;

/* eDMA - Error Register */
typedef struct{
__REG16 ERR0   : 1;
__REG16 ERR1   : 1;
__REG16 ERR2   : 1;
__REG16 ERR3   : 1;
__REG16 ERR4   : 1;
__REG16 ERR5   : 1;
__REG16 ERR6   : 1;
__REG16 ERR7   : 1;
__REG16 ERR8   : 1;
__REG16 ERR9   : 1;
__REG16 ERR10  : 1;
__REG16 ERR11  : 1;
__REG16 ERR12  : 1;
__REG16 ERR13  : 1;
__REG16 ERR14  : 1;
__REG16 ERR15  : 1;
} __dmaerr_bits;

/* eDMA - Channel Priority Registers */
typedef struct{
__REG8  CHPRI  : 4;
__REG8         : 3;
__REG8  ECP    : 1;
} __dchprin_bits;

/* eDMA - Transfer Control Descriptor Word 0 (SADDR) */
typedef struct{
__REG32 SADDR  :32;
} __tcdw0_bits;

/* eDMA - Transfer Control Descriptor Word 1 (SMOD, SSIZE, DMOD, DSIZE, SOFF) */
typedef struct{
__REG32 SOFF   :16;
__REG32 DSIZE  : 3;
__REG32 DMOD   : 5;
__REG32 SSIZE  : 3;
__REG32 SMOD   : 5;
} __tcdw1_bits;

/* eDMA - Transfer Control Descriptor Word 2 (NBYTES) */
typedef struct{
__REG32 NBYTES  :32;
} __tcdw2_bits;

/* eDMA - Transfer Control Descriptor Word 3 (SLAST) */
typedef struct{
__REG32 SLAST  :32;
} __tcdw3_bits;

/* eDMA - Transfer Control Descriptor Word 4 (DADDR) */
typedef struct{
__REG32 DADDR  :32;
} __tcdw4_bits;

/* eDMA - Transfer Control Descriptor Word 5 (CITER, DOFF) */
typedef union{
  //TCDx
  struct {
__REG32 DOFF          :16;
__REG32 CITER         :15;
__REG32 CITER_E_LINK  : 1;
  };
  //TCDx
  struct {
__REG32               :25;
__REG32 CITER_LINKCH  : 6;
__REG32               : 1;
  };
} __tcdw5_bits;

/* eDMA - Transfer Control Descriptor Word 6 (DLAST_SGA) */
typedef struct{
__REG32 DLAST_SGA  :32;
} __tcdw6_bits;

/* eDMA - Transfer Control Descriptor Word 7 (BITER and Control/Status) */
typedef union{
  //TCDx
  struct {
__REG32 START         : 1;
__REG32 INT_MAJ       : 1;
__REG32 INT_HALF      : 1;
__REG32 D_REQ         : 1;
__REG32 E_SG          : 1;
__REG32 MAJOR_W_LINK  : 1;
__REG32 ACTIVE        : 1;
__REG32 DONE          : 1;
__REG32 MAJOR_LINKCH  : 6;
__REG32 BWC           : 2;
__REG32 BITER         :15;
__REG32 BITER_E_LINK  : 1;
  };
  //TCDx
  struct {
__REG32               :25;
__REG32 BITER_LINKCH  : 6;
__REG32               : 1;
  };
} __tcdw7_bits;

/* INTC - Interrupt Pending Register High */
typedef struct{
__REG32 IPR32  : 1;
__REG32 IPR33  : 1;
__REG32 IPR34  : 1;
__REG32 IPR35  : 1;
__REG32 IPR36  : 1;
__REG32 IPR37  : 1;
__REG32 IPR38  : 1;
__REG32 IPR39  : 1;
__REG32 IPR40  : 1;
__REG32 IPR41  : 1;
__REG32 IPR42  : 1;
__REG32 IPR43  : 1;
__REG32 IPR44  : 1;
__REG32 IPR45  : 1;
__REG32 IPR46  : 1;
__REG32 IPR47  : 1;
__REG32 IPR48  : 1;
__REG32 IPR49  : 1;
__REG32 IPR50  : 1;
__REG32 IPR51  : 1;
__REG32 IPR52  : 1;
__REG32 IPR53  : 1;
__REG32 IPR54  : 1;
__REG32 IPR55  : 1;
__REG32 IPR56  : 1;
__REG32 IPR57  : 1;
__REG32 IPR58  : 1;
__REG32 IPR59  : 1;
__REG32 IPR60  : 1;
__REG32 IPR61  : 1;
__REG32 IPR62  : 1;
__REG32 IPR63  : 1;
} __iprh_bits;

/* INTC - Interrupt Pending Register Low */
typedef struct{
__REG32 IPR0   : 1;
__REG32 IPR1   : 1;
__REG32 IPR2   : 1;
__REG32 IPR3   : 1;
__REG32 IPR4   : 1;
__REG32 IPR5   : 1;
__REG32 IPR6   : 1;
__REG32 IPR7   : 1;
__REG32 IPR8   : 1;
__REG32 IPR9   : 1;
__REG32 IPR10  : 1;
__REG32 IPR11  : 1;
__REG32 IPR12  : 1;
__REG32 IPR13  : 1;
__REG32 IPR14  : 1;
__REG32 IPR15  : 1;
__REG32 IPR16  : 1;
__REG32 IPR17  : 1;
__REG32 IPR18  : 1;
__REG32 IPR19  : 1;
__REG32 IPR20  : 1;
__REG32 IPR21  : 1;
__REG32 IPR22  : 1;
__REG32 IPR23  : 1;
__REG32 IPR24  : 1;
__REG32 IPR25  : 1;
__REG32 IPR26  : 1;
__REG32 IPR27  : 1;
__REG32 IPR28  : 1;
__REG32 IPR29  : 1;
__REG32 IPR30  : 1;
__REG32 IPR31  : 1;
} __iprl_bits;

/* INTC - Interrupt Mask Register High */
typedef struct{
__REG32 IMR32  : 1;
__REG32 IMR33  : 1;
__REG32 IMR34  : 1;
__REG32 IMR35  : 1;
__REG32 IMR36  : 1;
__REG32 IMR37  : 1;
__REG32 IMR38  : 1;
__REG32 IMR39  : 1;
__REG32 IMR40  : 1;
__REG32 IMR41  : 1;
__REG32 IMR42  : 1;
__REG32 IMR43  : 1;
__REG32 IMR44  : 1;
__REG32 IMR45  : 1;
__REG32 IMR46  : 1;
__REG32 IMR47  : 1;
__REG32 IMR48  : 1;
__REG32 IMR49  : 1;
__REG32 IMR50  : 1;
__REG32 IMR51  : 1;
__REG32 IMR52  : 1;
__REG32 IMR53  : 1;
__REG32 IMR54  : 1;
__REG32 IMR55  : 1;
__REG32 IMR56  : 1;
__REG32 IMR57  : 1;
__REG32 IMR58  : 1;
__REG32 IMR59  : 1;
__REG32 IMR60  : 1;
__REG32 IMR61  : 1;
__REG32 IMR62  : 1;
__REG32 IMR63  : 1;
} __imrh_bits;

/* INTC - Interrupt Mask Register Low */
typedef struct{
__REG32 IMR0   : 1;
__REG32 IMR1   : 1;
__REG32 IMR2   : 1;
__REG32 IMR3   : 1;
__REG32 IMR4   : 1;
__REG32 IMR5   : 1;
__REG32 IMR6   : 1;
__REG32 IMR7   : 1;
__REG32 IMR8   : 1;
__REG32 IMR9   : 1;
__REG32 IMR10  : 1;
__REG32 IMR11  : 1;
__REG32 IMR12  : 1;
__REG32 IMR13  : 1;
__REG32 IMR14  : 1;
__REG32 IMR15  : 1;
__REG32 IMR16  : 1;
__REG32 IMR17  : 1;
__REG32 IMR18  : 1;
__REG32 IMR19  : 1;
__REG32 IMR20  : 1;
__REG32 IMR21  : 1;
__REG32 IMR22  : 1;
__REG32 IMR23  : 1;
__REG32 IMR24  : 1;
__REG32 IMR25  : 1;
__REG32 IMR26  : 1;
__REG32 IMR27  : 1;
__REG32 IMR28  : 1;
__REG32 IMR29  : 1;
__REG32 IMR30  : 1;
__REG32 IMR31  : 1;
} __imrl_bits;

/* INTC - Force Interrupt Register High */
typedef struct{
__REG32 IFRC32  : 1;
__REG32 IFRC33  : 1;
__REG32 IFRC34  : 1;
__REG32 IFRC35  : 1;
__REG32 IFRC36  : 1;
__REG32 IFRC37  : 1;
__REG32 IFRC38  : 1;
__REG32 IFRC39  : 1;
__REG32 IFRC40  : 1;
__REG32 IFRC41  : 1;
__REG32 IFRC42  : 1;
__REG32 IFRC43  : 1;
__REG32 IFRC44  : 1;
__REG32 IFRC45  : 1;
__REG32 IFRC46  : 1;
__REG32 IFRC47  : 1;
__REG32 IFRC48  : 1;
__REG32 IFRC49  : 1;
__REG32 IFRC50  : 1;
__REG32 IFRC51  : 1;
__REG32 IFRC52  : 1;
__REG32 IFRC53  : 1;
__REG32 IFRC54  : 1;
__REG32 IFRC55  : 1;
__REG32 IFRC56  : 1;
__REG32 IFRC57  : 1;
__REG32 IFRC58  : 1;
__REG32 IFRC59  : 1;
__REG32 IFRC60  : 1;
__REG32 IFRC61  : 1;
__REG32 IFRC62  : 1;
__REG32 IFRC63  : 1;
} __intfrch_bits;

/* INTC - Force Interrupt Register Low */
typedef struct{
__REG32 IFRC0   : 1;
__REG32 IFRC1   : 1;
__REG32 IFRC2   : 1;
__REG32 IFRC3   : 1;
__REG32 IFRC4   : 1;
__REG32 IFRC5   : 1;
__REG32 IFRC6   : 1;
__REG32 IFRC7   : 1;
__REG32 IFRC8   : 1;
__REG32 IFRC9   : 1;
__REG32 IFRC10  : 1;
__REG32 IFRC11  : 1;
__REG32 IFRC12  : 1;
__REG32 IFRC13  : 1;
__REG32 IFRC14  : 1;
__REG32 IFRC15  : 1;
__REG32 IFRC16  : 1;
__REG32 IFRC17  : 1;
__REG32 IFRC18  : 1;
__REG32 IFRC19  : 1;
__REG32 IFRC20  : 1;
__REG32 IFRC21  : 1;
__REG32 IFRC22  : 1;
__REG32 IFRC23  : 1;
__REG32 IFRC24  : 1;
__REG32 IFRC25  : 1;
__REG32 IFRC26  : 1;
__REG32 IFRC27  : 1;
__REG32 IFRC28  : 1;
__REG32 IFRC29  : 1;
__REG32 IFRC30  : 1;
__REG32 IFRC31  : 1;
} __intfrcl_bits;

/* INTC - Interrupt Configuration Register */
typedef struct{
__REG8  FIQDEF  : 5;
__REG8  EMASK   : 1;
__REG8          : 2;
} __iconfig_bits;

/* INTC - Set Interrupt Mask Register */
typedef struct{
__REG8  SIMR  : 7;
__REG8        : 1;
} __simr_bits;

/* INTC - Clear Interrupt Mask Register */
typedef struct{
__REG8  CIMR  : 7;
__REG8        : 1;
} __cimr_bits;

/* INTC - Current Level Mask Register */
typedef struct{
__REG8  CLMASK  : 5;
__REG8          : 3;
} __clmask_bits;

/* INTC - Saved Level Mask Register */
typedef struct{
__REG8  SLMASK  : 5;
__REG8          : 3;
} __slmask_bits;

/* INTC - Interrupt Control Registers */
typedef struct{
__REG8  LEVEL  : 4;
__REG8         : 4;
} __icrn_bits;

/* SSM - Current System Status Register */
typedef struct{
__REG16 DMAACTCH  : 4;
__REG16 DMAIDLE   : 1;
__REG16 MODE      : 2;
__REG16 SEC       : 1;
__REG16 EIM_SIZE  : 2;
__REG16 EIM_ACK   : 1;
__REG16 NEXUS     : 2;
__REG16           : 3;
} __status_bits;

/* SSM - System Memory Configuration Register */
typedef struct{
__REG16 DFLASHVALID  : 1;
__REG16 DFLASHSIZE   : 4;
__REG16 PFLASHVALID  : 1;
__REG16 PFLASHSIZE   : 4;
__REG16 SRAMVALID    : 1;
__REG16 SRAMSIZE     : 4;
__REG16 SRHOLE       : 1;
} __memconfig_bits;

/* SSM - Wake-up Source Register */
typedef union{
  //WAKEUP
  struct {
__REG32 SOURCE  :14;
__REG32         :18;
  };
  //ERROR
  struct {
__REG32         :16;
__REG32 BABORT  : 1;
__REG32         :15;
  };
} __wakeup_bits;

/* SSM - Port Select Register */
typedef struct{
__REG16 PORTHSEL  : 1;
__REG16           :15;
} __portsel_bits;

/* SSM - Debug Status Port Control Register */
typedef struct{
__REG16 DEBUG_MODE  : 3;
__REG16             :13;
} __debugport_bits;

/* DMAMux - Channel Configuration Registers */
typedef struct{
__REG8  SOURCE  : 6;
__REG8  TRIG    : 1;
__REG8  ENBL    : 1;
} __chconfign_bits;

/* CRG - Synthesizer Register */
typedef struct{
__REG8  SYN  : 6;
__REG8       : 2;
} __synr_bits;

/* CRG - Reference Divider Register */
typedef struct{
__REG8  REFDV  : 4;
__REG8         : 4;
} __refdv_bits;

/* CRG - Flags Register */
typedef struct{
__REG8  SCM     : 1;
__REG8  SCMIF   : 1;
__REG8  TRACK   : 1;
__REG8  LOCK    : 1;
__REG8  LOCKIF  : 1;
__REG8  LVRF    : 1;
__REG8  PORF    : 1;
__REG8  STPEF   : 1;
} __crgflg_bits;

/* CRG - Interrupt Enable Register */
typedef struct{
__REG8          : 1;
__REG8  SCMIE   : 1;
__REG8          : 2;
__REG8  LOCKIE  : 1;
__REG8          : 3;
} __crgint_bits;

/* CRG - Clock Select Register */
typedef struct{
__REG8  SWTDOZE  : 1;
__REG8  RTIDOZE  : 1;
__REG8           : 1;
__REG8  PLLDOZE  : 1;
__REG8           : 2;
__REG8  PSTP     : 1;
__REG8  PLLSEL   : 1;
} __clksel_bits;

/* CRG - PLL Control Register */
typedef struct{
__REG8  SCME    : 1;
__REG8  PWE     : 1;
__REG8  PRE     : 1;
__REG8  FSTWKP  : 1;
__REG8  ACQ     : 1;
__REG8  AUTO    : 1;
__REG8  PLLON   : 1;
__REG8  CME     : 1;
} __pllctl_bits;

/* CRG - Stop/Doze Control Register */
typedef struct{
__REG8  STOP  : 1;
__REG8  DOZE  : 1;
__REG8        : 6;
} __sdmctl_bits;

/* CRG - BDM Control Register */
typedef struct{
__REG8         : 6;
__REG8  RSBCK  : 1;
__REG8         : 1;
} __bdmctl_bits;

/* PIT - RTI / Timer Load Value Registers */
typedef struct{
__REG32 TSV  :24;
__REG32      : 8;
} __tlvaln_bits;

/* PIT - RTI / Timer Current Value Registers */
typedef struct{
__REG32 TVL  :24;
__REG32      : 8;
} __tvaln_bits;

/* PIT - Interrupt Flags Register */
typedef struct{
__REG32 RTIF  : 1;
__REG32 TIF1  : 1;
__REG32 TIF2  : 1;
__REG32 TIF3  : 1;
__REG32 TIF4  : 1;
__REG32       :27;
} __pitflg_bits;

/* PIT - Interrupt Enable Register */
typedef struct{
__REG32 RTIE  : 1;
__REG32 TIE1  : 1;
__REG32 TIE2  : 1;
__REG32 TIE3  : 1;
__REG32 TIE4  : 1;
__REG32       :27;
} __pitinten_bits;

/* PIT - Interrupt/DMA Select Register */
typedef struct{
__REG32        : 1;
__REG32 ISEL1  : 1;
__REG32 ISEL2  : 1;
__REG32 ISEL3  : 1;
__REG32 ISEL4  : 1;
__REG32        :27;
} __pitintsel_bits;

/* PIT - Timer Enable Register */
typedef struct{
__REG32 RTIEN  : 1;
__REG32 PEN1   : 1;
__REG32 PEN2   : 1;
__REG32 PEN3   : 1;
__REG32 PEN4   : 1;
__REG32 PEN5   : 1;
__REG32 PEN6   : 1;
__REG32 PEN7   : 1;
__REG32 PEN8   : 1;
__REG32 PEN9   : 1;
__REG32 PEN10  : 1;
__REG32        :21;
} __piten_bits;

/* PIT - Control Register */
typedef struct{
__REG32       :24;
__REG32 MDIS  : 1;
__REG32 DOZE  : 1;
__REG32       : 6;
} __pitctrl_bits;

/* VREG - High Temperature Control Register */
typedef struct{
__REG8        : 4;
__REG8  VAE   : 1;
__REG8  VSEL  : 1;
__REG8        : 2;
} __vreghtcl_bits;

/* VREG - Low Temperature Control Register */
typedef struct{
__REG8  LVIF  : 1;
__REG8  LVIE  : 1;
__REG8  LVDS  : 1;
__REG8        : 5;
} __vregctrl_bits;

/* VREG - Autonomous Periodic Interrupt Control Register */
typedef struct{
__REG8  APIF    : 1;
__REG8  APIE    : 1;
__REG8  APIFE   : 1;
__REG8  APIR    : 4;
__REG8  APICLK  : 1;
} __vregapicl_bits;

/* VREG - Autonomous Periodic Interrupt Trimming Register */
typedef struct{
__REG8         : 1;
__REG8         : 1;
__REG8  APITR  : 6;
} __vregapitr_bits;

/* FlexCAN - Module Configuration Register */
typedef struct{
__REG32 MAXMB     : 6;
__REG32           :12;
__REG32 DOZE      : 1;
__REG32 WAK_SRC   : 1;
__REG32 LPM_ACK   : 1;
__REG32           : 1;
__REG32 SLF_WAK   : 1;
__REG32 SUPV      : 1;
__REG32 FRZ_ACK   : 1;
__REG32 SOFT_RST  : 1;
__REG32 WAK_MSK   : 1;
__REG32 NOT_RDY   : 1;
__REG32 HALT      : 1;
__REG32           : 1;
__REG32 FRZ       : 1;
__REG32 MDIS      : 1;
} __mcrn_bits;

/* FlexCAN - Control Register */
typedef struct{
__REG32 PROPSEG   : 3;
__REG32 LOM       : 1;
__REG32 LBUF      : 1;
__REG32 TSYN      : 1;
__REG32 BOFF_REC  : 1;
__REG32 SMP       : 1;
__REG32           : 4;
__REG32 LPB       : 1;
__REG32 CLK_SRC   : 1;
__REG32 ERR_MSK   : 1;
__REG32 BOFF_MSK  : 1;
__REG32 PSEG2     : 3;
__REG32 PSEG1     : 3;
__REG32 RJW       : 2;
__REG32 PRESDIV   : 8;
} __ctrl_bits;

/* FlexCAN - Timer Register */
typedef struct{
__REG32 TIMER  :16;
__REG32        :16;
} __timer_bits;

/* FlexCAN - Rx Global Mask Register */
typedef struct{
__REG32 MI  :29;
__REG32     : 3;
} __rxgmask_bits;

/* FlexCAN - Error Counter Register */
typedef struct{
__REG32 TX_ERR_COUNTER  : 8;
__REG32 RX_ERR_COUNTER  : 8;
__REG32                 :16;
} __ecr_bits;

/* FlexCAN - Error and Status Register */
typedef struct{
__REG32 WAK_INT   : 1;
__REG32 ERR_INT   : 1;
__REG32 BOFF_INT  : 1;
__REG32           : 1;
__REG32 FLT_CONF  : 2;
__REG32 TXRX      : 1;
__REG32 IDLE      : 1;
__REG32 RX_WRN    : 1;
__REG32 TX_WRN    : 1;
__REG32 STF_ERR   : 1;
__REG32 FRM_ERR   : 1;
__REG32 CRC_ERR   : 1;
__REG32 ACK_ERR   : 1;
__REG32 BIT0_ERR  : 1;
__REG32 BIT1_ERR  : 1;
__REG32           :16;
} __esr_bits;

/* FlexCAN - Interrupt Mask Register */
typedef struct{
__REG32 BUF0M   : 1;
__REG32 BUF1M   : 1;
__REG32 BUF2M   : 1;
__REG32 BUF3M   : 1;
__REG32 BUF4M   : 1;
__REG32 BUF5M   : 1;
__REG32 BUF6M   : 1;
__REG32 BUF7M   : 1;
__REG32 BUF8M   : 1;
__REG32 BUF9M   : 1;
__REG32 BUF10M  : 1;
__REG32 BUF11M  : 1;
__REG32 BUF12M  : 1;
__REG32 BUF13M  : 1;
__REG32 BUF14M  : 1;
__REG32 BUF15M  : 1;
__REG32 BUF16M  : 1;
__REG32 BUF17M  : 1;
__REG32 BUF18M  : 1;
__REG32 BUF19M  : 1;
__REG32 BUF20M  : 1;
__REG32 BUF21M  : 1;
__REG32 BUF22M  : 1;
__REG32 BUF23M  : 1;
__REG32 BUF24M  : 1;
__REG32 BUF25M  : 1;
__REG32 BUF26M  : 1;
__REG32 BUF27M  : 1;
__REG32 BUF28M  : 1;
__REG32 BUF29M  : 1;
__REG32 BUF30M  : 1;
__REG32 BUF31M  : 1;
} __imask_bits;

/* FlexCAN - Interrupt Flags Register */
typedef struct{
__REG32 BUF0I   : 1;
__REG32 BUF1I   : 1;
__REG32 BUF2I   : 1;
__REG32 BUF3I   : 1;
__REG32 BUF4I   : 1;
__REG32 BUF5I   : 1;
__REG32 BUF6I   : 1;
__REG32 BUF7I   : 1;
__REG32 BUF8I   : 1;
__REG32 BUF9I   : 1;
__REG32 BUF10I  : 1;
__REG32 BUF11I  : 1;
__REG32 BUF12I  : 1;
__REG32 BUF13I  : 1;
__REG32 BUF14I  : 1;
__REG32 BUF15I  : 1;
__REG32 BUF16I  : 1;
__REG32 BUF17I  : 1;
__REG32 BUF18I  : 1;
__REG32 BUF19I  : 1;
__REG32 BUF20I  : 1;
__REG32 BUF21I  : 1;
__REG32 BUF22I  : 1;
__REG32 BUF23I  : 1;
__REG32 BUF24I  : 1;
__REG32 BUF25I  : 1;
__REG32 BUF26I  : 1;
__REG32 BUF27I  : 1;
__REG32 BUF28I  : 1;
__REG32 BUF29I  : 1;
__REG32 BUF30I  : 1;
__REG32 BUF31I  : 1;
} __iflag_bits;

/* FlexCAN - Message Buffer Word 0 */
typedef struct{
__REG32 TIME_STAMP  :16;
__REG32 LENGTH      : 4;
__REG32 RTR         : 1;
__REG32 IDE         : 1;
__REG32 SRR         : 1;
__REG32             : 1;
__REG32 CODE        : 4;
__REG32             : 4;
} __mbw0_bits;

/* FlexCAN - Message Buffer Word 1 */
typedef struct{
__REG32 ID  :30;
__REG32     : 2;
} __mbw1_bits;

/* FlexCAN - Message Buffer Word 2 */
typedef struct{
__REG32 DATA3  : 8;
__REG32 DATA2  : 8;
__REG32 DATA1  : 8;
__REG32 DATA0  : 8;
} __mbw2_bits;

/* FlexCAN - Message Buffer Word 3 */
typedef struct{
__REG32 DATA7  : 8;
__REG32 DATA6  : 8;
__REG32 DATA5  : 8;
__REG32 DATA4  : 8;
} __mbw3_bits;

/* I2C - Bus Address Register */
typedef struct{
__REG8       : 1;
__REG8  ADR  : 7;
} __ibad_bits;

/* I2C - Bus Frequency Divider Register */
typedef struct{
__REG8  IBC02  : 3;
__REG8  IBC53  : 3;
__REG8  IBC76  : 2;
} __ibfd_bits;

/* I2C - Bus Control Register */
typedef struct{
__REG8  IBDOZE  : 1;
__REG8  DMAEN   : 1;
__REG8  RSTA    : 1;
__REG8  TXAK    : 1;
__REG8  Tx_Rx   : 1;
__REG8  MS_SL   : 1;
__REG8  IBIE    : 1;
__REG8  IBDIS   : 1;
} __ibcr_bits;

/* I2C - Bus Status Register */
typedef struct{
__REG8  RXAK  : 1;
__REG8  IBIF  : 1;
__REG8  SRW   : 1;
__REG8        : 1;
__REG8  IBAL  : 1;
__REG8  IBB   : 1;
__REG8  IAAS  : 1;
__REG8  TCF   : 1;
} __ibsr_bits;

/* DSPI - Module Configuration Register */
typedef struct{
__REG32 HALT       : 1;
__REG32            : 7;
__REG32 SMPL_PT    : 2;
__REG32 CLR_RXF    : 1;
__REG32 CLR_TXF    : 1;
__REG32 DIS_RXF    : 1;
__REG32 DIS_TXF    : 1;
__REG32 MDIS       : 1;
__REG32 DOZE       : 1;
__REG32 PCSIS0     : 1;
__REG32 PCSIS1     : 1;
__REG32 PCSIS2     : 1;
__REG32 PCSIS3     : 1;     /* available on 7136 only, otherwise reserved */
__REG32 PCSIS4     : 1;     /* available on 7136 only, otherwise reserved */
__REG32 PCSIS5     : 1;
__REG32 PCSIS6     : 1;     /* available on 7136 only, otherwise reserved */
__REG32 PCSIS7     : 1;     /* available on 7136 only, otherwise reserved */
__REG32 ROOE       : 1;
__REG32 PCSSE      : 1;
__REG32 MTFE       : 1;
__REG32 FRZ        : 1;
__REG32 DCONF      : 2;
__REG32 CONT_SCKE  : 1;
__REG32 MSTR       : 1;
} __dspix_mcr_bits;

/* DSPI - Transfer Count Register */
typedef struct{
__REG32           :16;
__REG32 SPI_TCNT  :16;
} __dspix_tcr_bits;

/* DSPI - Clock and Transfer Attributes Register */
typedef struct{
__REG32 BR      : 4;
__REG32 DT      : 4;
__REG32 ASC     : 4;
__REG32 CSSCK   : 4;
__REG32 PBR     : 2;
__REG32 PDT     : 2;
__REG32 PASC    : 2;
__REG32 PCSSCK  : 2;
__REG32 LSBFE   : 1;
__REG32 CPHA    : 1;
__REG32 CPOL    : 1;
__REG32 FMSZ    : 4;
__REG32 DBR     : 1;     /* Reserved on mask sets L49P and L47W devices */
} __dspix_ctarn_bits;

/* DSPI - Status Register */
typedef struct{
__REG32 POPNXTPTR  : 4;
__REG32 RXCTR      : 4;
__REG32 TXNXTPTR   : 4;
__REG32 TXCTR      : 4;
__REG32            : 1;
__REG32 RFDF       : 1;
__REG32            : 1;
__REG32 RFOF       : 1;
__REG32            : 5;
__REG32 TFFF       : 1;
__REG32            : 1;
__REG32 TFUF       : 1;
__REG32 EOQF       : 1;
__REG32            : 1;
__REG32 TXRXS      : 1;
__REG32 TCF        : 1;
} __dspix_sr_bits;

/* DSPI - DMA/Interrupt Request Select and Enable Register */
typedef struct{
__REG32            :16;
__REG32 RFDF_DIRS  : 1;
__REG32 RFDF_RE    : 1;
__REG32            : 1;
__REG32 RFOF_RE    : 1;
__REG32            : 4;
__REG32 TFFF_DIRS  : 1;
__REG32 TFFF_RE    : 1;
__REG32            : 1;
__REG32 TFUF_RE    : 1;
__REG32 EOQF_RE    : 1;
__REG32            : 2;
__REG32 TCF_RE     : 1;
} __dspix_rser_bits;

/* DSPI - PUSH TX FIFO Register */
typedef struct{
__REG32 TXDATA  :16;
__REG32 PCS0    : 1;
__REG32 PCS1    : 1;
__REG32 PCS2    : 1;
__REG32 PCS3    : 1;     /* available on 7136 only, reserved otherwise */
__REG32 PCS4    : 1;     /* available on 7136 only, reserved otherwise */
__REG32 PCS5    : 1;
__REG32 PCS6    : 1;     /* available on 7136 only, reserved otherwise */
__REG32 PCS7    : 1;     /* available on 7136 only, reserved otherwise */
__REG32         : 2;
__REG32 CTCNT   : 1;
__REG32 EOQ     : 1;
__REG32 CTAS    : 3;
__REG32 CONT    : 1;
} __dspix_pushr_bits;

/* DSPI - POP RX FIFO Register */
typedef struct{
__REG32 RXDATA  :16;
__REG32         :16;
} __dspix_popr_bits;

/* DSPI - Transmit FIFO Register */
typedef struct{
__REG32 TXDATA  :16;
__REG32 TXCMD   :16;
} __dspix_txfrn_bits;

/* DSPI - Recieve FIFO Register */
typedef struct{
__REG32 RXDATA  :16;
__REG32         :16;
} __dspix_rxfrn_bits;

/* eSCI - Baud Register High */
typedef struct{
__REG8  SBR  : 5;
__REG8       : 3;
} __escibdh_bits;

/* eSCI - Baud Register Low */
typedef struct{
__REG8  SBR  : 8;
} __escibdl_bits;

/* eSCI - Control Register 1 */
typedef struct{
__REG8  PT       : 1;
__REG8  PE       : 1;
__REG8  ILT      : 1;
__REG8  WAKE     : 1;
__REG8  M        : 1;
__REG8  RSRC     : 1;
__REG8  SCISDOZ  : 1;
__REG8  LOOPS    : 1;
} __escicr1_bits;

/* eSCI - Control Register 2 */
typedef struct{
__REG8  SBK   : 1;
__REG8  RWU   : 1;
__REG8  RE    : 1;
__REG8  TE    : 1;
__REG8  ILIE  : 1;
__REG8  RIE   : 1;
__REG8  TCIE  : 1;
__REG8  TIE   : 1;
} __escicr2_bits;

/* eSCI - Control Register 3 */
typedef struct{
__REG8  TXDIR   : 1;
__REG8  BRK13   : 1;
__REG8  TXDMA   : 1;
__REG8  RXDMA   : 1;
__REG8  IEBERR  : 1;
__REG8  BSTP    : 1;
__REG8  FBR     : 1;     /* not implemented on mask set L49P */
__REG8  MDIS    : 1;
} __escicr3_bits;

/* eSCI - Control Register 4 */
typedef struct{
__REG8  PFIE    : 1;
__REG8  FEIE    : 1;
__REG8  NFIE    : 1;
__REG8  ORIE    : 1;
__REG8          : 2;
__REG8  SBSTP   : 1;     /* not implemented on mask set L49P */
__REG8  BESM13  : 1;     /* not implemented on mask set L49P */
} __escicr4_bits;

/* eSCI - Data Register High */
typedef struct{
__REG8      : 6;
__REG8  T8  : 1;
__REG8  R8  : 1;
} __escidrh_bits;

/* eSCI - Status Register 1 */
typedef struct{
__REG8  PF    : 1;
__REG8  FE    : 1;
__REG8  NF    : 1;
__REG8  OR    : 1;
__REG8  IDLE  : 1;
__REG8  RDRF  : 1;
__REG8  TC    : 1;
__REG8  TDRE  : 1;
} __escisr1_bits;

/* eSCI - Status Register 2 */
typedef struct{
__REG8  RAF   : 1;
__REG8        : 3;
__REG8  BERR  : 1;
__REG8        : 3;
} __escisr2_bits;

/* eSCI - LIN Status Register 1 */
typedef struct{
__REG8  FRC    : 1;
__REG8  CKERR  : 1;
__REG8  CERR   : 1;
__REG8  PBERR  : 1;
__REG8  STO    : 1;
__REG8  LWAKE  : 1;
__REG8  TXRDY  : 1;
__REG8  RXRDY  : 1;
} __linstat1_bits;

/* eSCI - LIN Status Register 2 */
typedef struct{
__REG8  OVFL  : 1;
__REG8        : 7;
} __linstat2_bits;

/* eSCI - LIN Control Register 1 */
typedef struct{
__REG8  LIN   : 1;
__REG8  PRTY  : 1;
__REG8  DSF   : 1;
__REG8  LDBG  : 1;
__REG8  WUD0  : 1;
__REG8  WUD1  : 1;
__REG8  WU    : 1;
__REG8  LRES  : 1;
} __linctrl1_bits;

/* eSCI - LIN Control Register 2 */
typedef struct{
__REG8  FCIE  : 1;
__REG8  CKIE  : 1;
__REG8  CIE   : 1;
__REG8  PBIE  : 1;
__REG8  STIE  : 1;
__REG8  WUIE  : 1;
__REG8  TXIE  : 1;
__REG8  RXIE  : 1;
} __linctrl2_bits;

/* eSCI - LIN Control Register 3 */
typedef struct{
__REG8  OFIE  : 1;
__REG8        : 7;
} __linctrl3_bits;

/* eSCI - LIN TX Register */
typedef union{
  //LINTX
  struct {
__REG8  D      : 8;
  };
  //LINTX
  struct {
__REG8  T      : 8;
  };
  //LINTX
  struct {
__REG8  T118   : 4;
__REG8  TX     : 1;
__REG8  CRC    : 1;
__REG8  CSUM   : 1;
__REG8  HDCHK  : 1;
  };
  //LINTX
  struct {
__REG8  L      : 8;
  };
  //LINTX
  struct {
__REG8  ID     : 6;
__REG8  P      : 2;
  };
} __lintx_bits;

/* eMIOS - Module Configuration Register */
typedef struct{
__REG32         : 8;
__REG32 GPRE    : 8;
__REG32         :10;
__REG32 GPREN   : 1;
__REG32         : 2;
__REG32 FRZ     : 1;
__REG32 MDIS    : 1;
__REG32 DOZEEN  : 1;
} __mcr0_bits;

/* eMIOS - Global Flag Register */
typedef struct{
__REG32 F0   : 1;
__REG32 F1   : 1;
__REG32 F2   : 1;
__REG32 F3   : 1;
__REG32 F4   : 1;
__REG32 F5   : 1;
__REG32 F6   : 1;
__REG32 F7   : 1;
__REG32 F8   : 1;
__REG32 F9   : 1;
__REG32 F10  : 1;
__REG32 F11  : 1;
__REG32 F12  : 1;
__REG32 F13  : 1;
__REG32 F14  : 1;
__REG32 F15  : 1;
__REG32      :16;
} __gflag_bits;

/* eMIOS - Output Update Disable Register */
typedef struct{
__REG32 OU0   : 1;
__REG32 OU1   : 1;
__REG32 OU2   : 1;
__REG32 OU3   : 1;
__REG32 OU4   : 1;
__REG32 OU5   : 1;
__REG32 OU6   : 1;
__REG32 OU7   : 1;
__REG32 OU8   : 1;
__REG32 OU9   : 1;
__REG32 OU10  : 1;
__REG32 OU11  : 1;
__REG32 OU12  : 1;
__REG32 OU13  : 1;
__REG32 OU14  : 1;
__REG32 OU15  : 1;
__REG32       :16;
} __oudis_bits;

/* eMIOS - Channel Disable Register */
typedef struct{
__REG32 UCDIS0   : 1;
__REG32 UCDIS1   : 1;
__REG32 UCDIS2   : 1;
__REG32 UCDIS3   : 1;
__REG32 UCDIS4   : 1;
__REG32 UCDIS5   : 1;
__REG32 UCDIS6   : 1;
__REG32 UCDIS7   : 1;
__REG32 UCDIS8   : 1;
__REG32 UCDIS9   : 1;
__REG32 UCDIS10  : 1;
__REG32 UCDIS11  : 1;
__REG32 UCDIS12  : 1;
__REG32 UCDIS13  : 1;
__REG32 UCDIS14  : 1;
__REG32 UCDIS15  : 1;
__REG32          :16;
} __ucdis_bits;

/* eMIOS - Channel A Data Registers */
typedef struct{
__REG32 UCAn  :16;
__REG32       :16;
} __ucan_bits;

/* eMIOS - Channel B Data Registers */
typedef struct{
__REG32 UCBn  :16;
__REG32       :16;
} __ucbn_bits;

/* eMIOS - Channel Counter Registers */
typedef struct{
__REG32 Counter  :16;
__REG32          :16;
} __uccntn_bits;

/* eMIOS  - Channel Control Registers */
typedef struct{
__REG32 MODE    : 7;
__REG32 EDPOL   : 1;
__REG32 EDSEL   : 1;
__REG32 BSL     : 2;
__REG32         : 1;
__REG32 FORCMB  : 1;
__REG32 FORCMA  : 1;
__REG32         : 3;
__REG32 FEN     : 1;
__REG32 FCK     : 1;
__REG32 IF      : 4;
__REG32         : 1;
__REG32 DMA     : 1;
__REG32 UCPREN  : 1;
__REG32 UCPRE   : 2;
__REG32 ODISSL  : 2;
__REG32 ODIS    : 1;
__REG32 FREN    : 1;
} __uccrn_bits;

/* eMIOS - Cgannel Status Registers */
typedef struct{
__REG32 FLAG   : 1;
__REG32 UCOUT  : 1;
__REG32 UCIN   : 1;
__REG32        :12;
__REG32 OVFL   : 1;
__REG32        :15;
__REG32 OVR    : 1;
} __ucsrn_bits;

/* ATD - Trigger Control Register */
typedef struct{
__REG8  TRIGLE   : 1;
__REG8  TRIGP    : 1;
__REG8  TRIGSEL  : 2;
__REG8           : 4;
} __atdtrigctl_bits;

/* ATD - External Trigger Channel Register */
typedef struct{
__REG8  ETRIGCH  : 4;
__REG8           : 4;
} __atdetrigch_bits;

/* ATD - Prescaler Register */
typedef struct{
__REG8  PRES  : 7;
__REG8        : 1;
} __atdpre_bits;

/* ATD - Operating Mode Register */
typedef struct{
__REG8         : 4;
__REG8  DEBUG  : 2;
__REG8  DOZE   : 1;
__REG8  MDIS   : 1;
} __atdmode_bits;

/* ATD - Interrupt Register */
typedef struct{
__REG8  CCIE   : 1;
__REG8  CPIE   : 1;
__REG8  ETOIE  : 1;
__REG8  CRLIE  : 1;
__REG8  CQEIE  : 1;
__REG8  CQFIE  : 1;
__REG8         : 2;
} __atdint_bits;

/* ATD - Flag Register */
typedef struct{
__REG8  CC   : 1;
__REG8  CP   : 1;
__REG8  ETO  : 1;
__REG8  CRL  : 1;
__REG8  CQE  : 1;
__REG8  CQF  : 1;
__REG8       : 2;
} __atdflag_bits;

/* ATD - Command Word Register */
typedef struct{
__REG32       :16;
__REG32 CWCH  : 4;
__REG32       : 1;
__REG32 CWNF  : 2;
__REG32 CW8   : 1;
__REG32 CWSB  : 1;
__REG32 CWSL  : 2;
__REG32 CWCM  : 2;
__REG32 CWGI  : 1;
__REG32 CWSC  : 1;
__REG32       : 1;
} __atdcw_bits;

/* ATD - Result Register */
typedef struct{
__REG32 RRCR  :16;
__REG32 RRCH  : 4;
__REG32       : 1;
__REG32 RRNF  : 2;
__REG32 RR8   : 1;
__REG32 RRSB  : 1;
__REG32 RRSL  : 2;
__REG32 RRCM  : 2;
__REG32 RRGI  : 1;
__REG32 RRSC  : 1;
__REG32       : 1;
} __atdrr_bits;

/* PIM - Global Interrupt Status Register */
typedef struct{
__REG16 GPIFA  : 1;
__REG16 GPIFB  : 1;
__REG16 GPIFC  : 1;
__REG16 GPIFD  : 1;
__REG16 GPIFE  : 1;
__REG16 GPIFF  : 1;
__REG16 GPIFG  : 1;
__REG16 GPIFH  : 1;
__REG16        : 8;
} __glbint_bits;

/* PIM - Global Configuration Register */
typedef struct{
__REG16 PORTHSEL  : 1;
__REG16 EIMCLKEN  : 1;
__REG16           :14;
} __pimconfig_bits;

/* PIM - Configure TDI Pin Register */
/* PIM - Configure TMS Pin Register */
/* PIM - Configure TCK Pin Register */
typedef struct{
__REG16       : 2;
__REG16 PULL  : 2;
__REG16       : 2;
__REG16 DD    : 1;
__REG16       : 9;
} __configdiv_bits;

/* PIM - Configure TDO Pin Register */
typedef struct{
__REG16      : 4;
__REG16 RDS  : 1;
__REG16      : 1;
__REG16 DD   : 1;
__REG16      : 9;
} __configtdo_bits;

/* PIM - Configure TA/AS Pin Register */
typedef struct{
__REG16       : 2;
__REG16 PULL  : 2;
__REG16 RDS   : 1;
__REG16 ODE   : 1;
__REG16 DD    : 1;
__REG16       : 9;
} __configta_bits;


/* PIM  - Port x Pin Configuration Registers */
typedef struct{
__REG16 PIF   : 1;
__REG16 PIE   : 1;
__REG16 PULL  : 2;
__REG16 RDS   : 1;
__REG16 ODE   : 1;
__REG16 DD    : 1;
__REG16 MODE  : 1;
__REG16       : 8;
} __confignx_bits;

/* PIM - Port x Interrupt Flag Register */
typedef struct{
__REG16 PIF0   : 1;
__REG16 PIF1   : 1;
__REG16 PIF2   : 1;
__REG16 PIF3   : 1;
__REG16 PIF4   : 1;
__REG16 PIF5   : 1;
__REG16 PIF6   : 1;
__REG16 PIF7   : 1;
__REG16 PIF8   : 1;
__REG16 PIF9   : 1;
__REG16 PIF10  : 1;
__REG16 PIF11  : 1;
__REG16 PIF12  : 1;
__REG16 PIF13  : 1;
__REG16 PIF14  : 1;
__REG16 PIF15  : 1;
} __portifrx_bits;

/* PIM - Port x Pin Data Registers */
typedef struct{
__REG8  DATA  : 1;
__REG8        : 7;
} __pindatanx_bits;

/* CFM - Module Configuration Register */
typedef struct{
__REG16         : 5;
__REG16 KEYACC  : 1;
__REG16 CCIE    : 1;
__REG16 CBEIE   : 1;
__REG16 AEIE    : 1;
__REG16 PVIE    : 1;
__REG16 LOCK    : 1;
__REG16 MRDS    : 2;
__REG16         : 3;
} __cfmmcr_bits;

/* CFM - Clock Divider Register */
typedef struct{
__REG8  DIV     : 6;
__REG8  PRDIV8  : 1;
__REG8  DIVLD   : 1;
} __cfmclkd_bits;

/* CFM - Security Register */
typedef struct{
__REG32 SEC      : 2;
__REG32 NV       :14;
__REG32          :13;     /* Must be 0 */
__REG32 SECSTAT  : 1;
__REG32 KEYEN    : 2;
} __cfmsec_bits;

/* CFM - Program Flash Protection Register */
typedef struct{
__REG32 PROTECT0   : 1;
__REG32 PROTECT1   : 1;
__REG32 PROTECT2   : 1;
__REG32 PROTECT3   : 1;
__REG32 PROTECT4   : 1;
__REG32 PROTECT5   : 1;
__REG32 PROTECT6   : 1;
__REG32 PROTECT7   : 1;
__REG32 PROTECT8   : 1;
__REG32 PROTECT9   : 1;
__REG32 PROTECT10  : 1;
__REG32 PROTECT11  : 1;
__REG32 PROTECT12  : 1;
__REG32 PROTECT13  : 1;
__REG32 PROTECT14  : 1;
__REG32 PROTECT15  : 1;
__REG32 PROTECT16  : 1;
__REG32 PROTECT17  : 1;
__REG32 PROTECT18  : 1;
__REG32 PROTECT19  : 1;
__REG32 PROTECT20  : 1;
__REG32 PROTECT21  : 1;
__REG32 PROTECT22  : 1;
__REG32 PROTECT23  : 1;
__REG32 PROTECT24  : 1;
__REG32 PROTECT25  : 1;
__REG32 PROTECT26  : 1;
__REG32 PROTECT27  : 1;
__REG32 PROTECT28  : 1;
__REG32 PROTECT29  : 1;
__REG32 PROTECT30  : 1;
__REG32 PROTECT31  : 1;
} __cfmprot_bits;

/* CFM - Program Flash Supervisor Access Register */
typedef struct{
__REG32 SUPV0   : 1;
__REG32 SUPV1   : 1;
__REG32 SUPV2   : 1;
__REG32 SUPV3   : 1;
__REG32 SUPV4   : 1;
__REG32 SUPV5   : 1;
__REG32 SUPV6   : 1;
__REG32 SUPV7   : 1;
__REG32 SUPV8   : 1;
__REG32 SUPV9   : 1;
__REG32 SUPV10  : 1;
__REG32 SUPV11  : 1;
__REG32 SUPV12  : 1;
__REG32 SUPV13  : 1;
__REG32 SUPV14  : 1;
__REG32 SUPV15  : 1;
__REG32 SUPV16  : 1;
__REG32 SUPV17  : 1;
__REG32 SUPV18  : 1;
__REG32 SUPV19  : 1;
__REG32 SUPV20  : 1;
__REG32 SUPV21  : 1;
__REG32 SUPV22  : 1;
__REG32 SUPV23  : 1;
__REG32 SUPV24  : 1;
__REG32 SUPV25  : 1;
__REG32 SUPV26  : 1;
__REG32 SUPV27  : 1;
__REG32 SUPV28  : 1;
__REG32 SUPV29  : 1;
__REG32 SUPV30  : 1;
__REG32 SUPV31  : 1;
} __cfmsacc_bits;

/* CFM - Program Flash Data Access Register */
typedef struct{
__REG32 DACC0   : 1;
__REG32 DACC1   : 1;
__REG32 DACC2   : 1;
__REG32 DACC3   : 1;
__REG32 DACC4   : 1;
__REG32 DACC5   : 1;
__REG32 DACC6   : 1;
__REG32 DACC7   : 1;
__REG32 DACC8   : 1;
__REG32 DACC9   : 1;
__REG32 DACC10  : 1;
__REG32 DACC11  : 1;
__REG32 DACC12  : 1;
__REG32 DACC13  : 1;
__REG32 DACC14  : 1;
__REG32 DACC15  : 1;
__REG32 DACC16  : 1;
__REG32 DACC17  : 1;
__REG32 DACC18  : 1;
__REG32 DACC19  : 1;
__REG32 DACC20  : 1;
__REG32 DACC21  : 1;
__REG32 DACC22  : 1;
__REG32 DACC23  : 1;
__REG32 DACC24  : 1;
__REG32 DACC25  : 1;
__REG32 DACC26  : 1;
__REG32 DACC27  : 1;
__REG32 DACC28  : 1;
__REG32 DACC29  : 1;
__REG32 DACC30  : 1;
__REG32 DACC31  : 1;
} __cfmdacc_bits;

/* CFM - User Status Register */
typedef struct{
__REG8          : 2;
__REG8  BLANK   : 1;
__REG8          : 1;
__REG8  ACCERR  : 1;
__REG8  PVIOL   : 1;
__REG8  CCIF    : 1;
__REG8  CBEIF   : 1;
} __cfmustat_bits;

/* CFM - Command Register */
typedef struct{
__REG8  CMD  : 7;
__REG8       : 1;
} __cfmcmd_bits;

/* CFM - Data Flash Protection Register */
typedef struct{
__REG8  PROTECT_DF0  : 1;
__REG8  PROTECT_DF1  : 1;
__REG8  PROTECT_DF2  : 1;
__REG8  PROTECT_DF3  : 1;
__REG8  PROTECT_DF4  : 1;
__REG8  PROTECT_DF5  : 1;
__REG8  PROTECT_DF6  : 1;
__REG8  PROTECT_DF7  : 1;
} __cfmdfprot_bits;

/* CFM - Data Flash Supervisor Access Register */
typedef struct{
__REG8  SUPV_DF0  : 1;
__REG8  SUPV_DF1  : 1;
__REG8  SUPV_DF2  : 1;
__REG8  SUPV_DF3  : 1;
__REG8  SUPV_DF4  : 1;
__REG8  SUPV_DF5  : 1;
__REG8  SUPV_DF6  : 1;
__REG8  SUPV_DF7  : 1;
} __cfmdfsacc_bits;

/* CFM - Data Flash Data Access Register */
typedef struct{
__REG8  DACC_DF0  : 1;
__REG8  DACC_DF1  : 1;
__REG8  DACC_DF2  : 1;
__REG8  DACC_DF3  : 1;
__REG8  DACC_DF4  : 1;
__REG8  DACC_DF5  : 1;
__REG8  DACC_DF6  : 1;
__REG8  DACC_DF7  : 1;
} __cfmdfdacc_bits;


/* CFM - Clock Select Register */
typedef struct{
__REG16 CLKSEL  : 2;
__REG16         :14;
} __cfmclksel_bits;



#endif    /* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler **************************/

/***************************************************************************
 **
 ** AIPS
 **
 ***************************************************************************/
__IO_REG32_BIT(MPRA,         0xfc000000,__READ_WRITE,__mpra_bits);
__IO_REG32_BIT(PACRA,        0xfc000020,__READ_WRITE,__pacra_bits);
__IO_REG32_BIT(PACRC,        0xfc000028,__READ_WRITE,__pacrc_bits);
__IO_REG32_BIT(OPACRA,       0xfc000040,__READ_WRITE,__opacra_bits);
__IO_REG32_BIT(OPACRB,       0xfc000044,__READ_WRITE,__opacrb_bits);
__IO_REG32_BIT(OPACRC,       0xfc000048,__READ_WRITE,__opacrc_bits);
__IO_REG32_BIT(OPACRD,       0xfc00004c,__READ_WRITE,__opacrd_bits);
__IO_REG32_BIT(OPACRE,       0xfc000050,__READ_WRITE,__opacre_bits);

/***************************************************************************
 **
 ** XBS
 **
 ***************************************************************************/
#ifndef MAC71X2  /* Registers not available on 71x2 devices */
__IO_REG32_BIT(PR_EIM,       0xfc004100,__READ_WRITE,__prport_bits);
__IO_REG32_BIT(CR_EIM,       0xfc004110,__READ_WRITE,__crport_bits);
#endif /* mac71x2 */

__IO_REG32_BIT(PR_SRAM,      0xfc004300,__READ_WRITE,__prport_bits);
__IO_REG32_BIT(CR_SRAM,      0xfc004310,__READ_WRITE,__crport_bits);
__IO_REG32_BIT(PR_PC,        0xfc004700,__READ_WRITE,__prport_bits);
__IO_REG32_BIT(CR_PC,        0xfc004710,__READ_WRITE,__crport_bits);


#ifndef MAC71X2 /* Registers not available on 71x2 devices */
/***************************************************************************
 **
 ** EIM
 **
 ***************************************************************************/
__IO_REG16(    CSAR0,        0xfc008080,__READ_WRITE);
__IO_REG32_BIT(CSMR0,        0xFC008084,__READ_WRITE,__csmrn_bits);
__IO_REG16_BIT(CSCR0,        0xFC00808A,__READ_WRITE,__cscrn_bits);
__IO_REG16(    CSAR1,        0xFC00808C,__READ_WRITE);
__IO_REG32_BIT(CSMR1,        0xFC008090,__READ_WRITE,__csmrn_bits);
__IO_REG16_BIT(CSCR1,        0xFC008096,__READ_WRITE,__cscrn_bits);
__IO_REG16(    CSAR2,        0xFC008098,__READ_WRITE);
__IO_REG32_BIT(CSMR2,        0xFC00809C,__READ_WRITE,__csmrn_bits);
__IO_REG16_BIT(CSCR2,        0xFC0080A2,__READ_WRITE,__cscrn_bits);
#endif /*mac71x2*/

/***************************************************************************
 **
 ** MCM
 **
 ***************************************************************************/
__IO_REG16(    PCT,          0xFC040000,__READ      );
/* Register REV is called _REV. REV would collide with instruction REV in
   assembler. */
__IO_REG16_BIT(_REV,         0xFC040002,__READ      ,__rev_bits);
__IO_REG8_BIT( AMC,          0xFC040004,__READ      ,__amc_bits);
__IO_REG8_BIT( ASC,          0xFC040006,__READ      ,__asc_bits);
__IO_REG32_BIT(IOPMC,        0xFC040008,__READ      ,__iopmc_bits);
__IO_REG8_BIT( MRSR,         0xFC04000F,__READ      ,__mrsr_bits);
__IO_REG8_BIT( MWCR,         0xFC040013,__READ_WRITE,__mwcr_bits);
__IO_REG16_BIT(MSWTCR,       0xFC040016,__READ_WRITE,__mswtcr_bits);
__IO_REG8(     MSWTSR,       0xFC04001B,__READ_WRITE);
__IO_REG8_BIT( MSWTIR,       0xFC04001F,__READ_WRITE,__mswtir_bits);
__IO_REG32_BIT(AAMR,         0xFC040020,__READ_WRITE,__aamr_bits);
__IO_REG32(    CFADR,        0xFC040070,__READ      );
__IO_REG8_BIT( CFLOC,        0xFC040076,__READ      ,__cfloc_bits);
__IO_REG8_BIT( CFATR,        0xFC040077,__READ      ,__cfatr_bits);
__IO_REG32(    CFDTR,        0xFC04007C,__READ      );


/***************************************************************************
 **
 ** eDMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DMACR,        0xFC044000,__READ_WRITE,__dmacr_bits);
__IO_REG32_BIT(DMAES,        0xFC044004,__READ_WRITE,__dmaes_bits);
__IO_REG16_BIT(DMAERQ,       0xFC04400E,__READ_WRITE,__dmaerq_bits);
__IO_REG16_BIT(DMAEEI,       0xFC044016,__READ_WRITE,__dmaeei_bits);
__IO_REG8_BIT( DMASERQ,      0xFC044018,__READ_WRITE,__dmaserq_bits);
__IO_REG8_BIT( DMACERQ,      0xFC044019,__READ_WRITE,__dmacerq_bits);
__IO_REG8_BIT( DMASEEI,      0xFC04401A,__READ_WRITE,__dmaseei_bits);
__IO_REG8_BIT( IDMACEEI,     0xFC04401B,__READ_WRITE,__dmaceei_bits);
__IO_REG8_BIT( DMACINT,      0xFC04401C,__READ_WRITE,__dmacint_bits);
__IO_REG8_BIT( DMACERR,      0xFC04401D,__READ_WRITE,__dmacerr_bits);
__IO_REG8_BIT( DMASSRT,      0xFC04401E,__READ_WRITE,__dmassrt_bits);
__IO_REG8_BIT( DMACDNE,      0xFC04401F,__READ_WRITE,__dmacdne_bits);
__IO_REG16_BIT(DMAINT,       0xFC044026,__READ_WRITE,__dmaint_bits);
__IO_REG16_BIT(DMAERR,       0xFC04402E,__READ_WRITE,__dmaerr_bits);
__IO_REG8_BIT( DCHPRI0,      0xFC044100,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI1,      0xFC044101,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI2,      0xFC044102,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI3,      0xFC044103,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI4,      0xFC044104,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI5,      0xFC044105,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI6,      0xFC044106,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI7,      0xFC044107,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI8,      0xFC044108,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI9,      0xFC044109,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI10,     0xFC04410a,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI11,     0xFC04410b,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI12,     0xFC04410c,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI13,     0xFC04410d,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI14,     0xFC04410e,__READ_WRITE,__dchprin_bits);
__IO_REG8_BIT( DCHPRI15,     0xFC04410f,__READ_WRITE,__dchprin_bits);

/* TCD0-15*/
__IO_REG32_BIT(TCD0_W0,      0xfc045000,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD0_W1,      0xfc045004,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD0_W2,      0xfc045008,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD0_W3,      0xfc04500c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD0_W4,      0xfc045010,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD0_W5,      0xfc045014,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD0_W6,      0xfc045018,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD0_W7,      0xfc04501c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD1_W0,      0xfc045020,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD1_W1,      0xfc045024,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD1_W2,      0xfc045028,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD1_W3,      0xfc04502c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD1_W4,      0xfc045030,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD1_W5,      0xfc045034,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD1_W6,      0xfc045038,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD1_W7,      0xfc04503c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD2_W0,      0xfc045040,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD2_W1,      0xfc045044,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD2_W2,      0xfc045048,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD2_W3,      0xfc04504c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD2_W4,      0xfc045050,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD2_W5,      0xfc045054,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD2_W6,      0xfc045058,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD2_W7,      0xfc04505c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD3_W0,      0xfc045060,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD3_W1,      0xfc045064,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD3_W2,      0xfc045068,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD3_W3,      0xfc04506c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD3_W4,      0xfc045070,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD3_W5,      0xfc045074,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD3_W6,      0xfc045078,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD3_W7,      0xfc04507c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD4_W0,      0xfc045080,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD4_W1,      0xfc045084,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD4_W2,      0xfc045088,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD4_W3,      0xfc04508c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD4_W4,      0xfc045090,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD4_W5,      0xfc045094,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD4_W6,      0xfc045098,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD4_W7,      0xfc04509c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD5_W0,      0xfc0450a0,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD5_W1,      0xfc0450a4,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD5_W2,      0xfc0450a8,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD5_W3,      0xfc0450ac,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD5_W4,      0xfc0450b0,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD5_W5,      0xfc0450b4,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD5_W6,      0xfc0450b8,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD5_W7,      0xfc0450bc,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD6_W0,      0xfc0450c0,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD6_W1,      0xfc0450c4,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD6_W2,      0xfc0450c8,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD6_W3,      0xfc0450cc,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD6_W4,      0xfc0450d0,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD6_W5,      0xfc0450d4,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD6_W6,      0xfc0450d8,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD6_W7,      0xfc0450dc,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD7_W0,      0xfc0450e0,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD7_W1,      0xfc0450e4,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD7_W2,      0xfc0450e8,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD7_W3,      0xfc0450ec,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD7_W4,      0xfc0450f0,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD7_W5,      0xfc0450f4,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD7_W6,      0xfc0450f8,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD7_W7,      0xfc0450fc,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD8_W0,      0xfc045100,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD8_W1,      0xfc045104,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD8_W2,      0xfc045108,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD8_W3,      0xfc04510c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD8_W4,      0xfc045110,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD8_W5,      0xfc045114,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD8_W6,      0xfc045118,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD8_W7,      0xfc04511c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD9_W0,      0xfc045120,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD9_W1,      0xfc045124,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD9_W2,      0xfc045128,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD9_W3,      0xfc04512c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD9_W4,      0xfc045130,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD9_W5,      0xfc045134,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD9_W6,      0xfc045138,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD9_W7,      0xfc04513c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD10_W0,     0xfc045140,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD10_W1,     0xfc045144,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD10_W2,     0xfc045148,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD10_W3,     0xfc04514c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD10_W4,     0xfc045150,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD10_W5,     0xfc045154,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD10_W6,     0xfc045158,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD10_W7,     0xfc04515c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD11_W0,     0xfc045160,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD11_W1,     0xfc045164,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD11_W2,     0xfc045168,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD11_W3,     0xfc04516c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD11_W4,     0xfc045170,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD11_W5,     0xfc045174,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD11_W6,     0xfc045178,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD11_W7,     0xfc04517c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD12_W0,     0xfc045180,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD12_W1,     0xfc045184,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD12_W2,     0xfc045188,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD12_W3,     0xfc04518c,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD12_W4,     0xfc045190,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD12_W5,     0xfc045194,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD12_W6,     0xfc045198,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD12_W7,     0xfc04519c,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD13_W0,     0xfc0451a0,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD13_W1,     0xfc0451a4,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD13_W2,     0xfc0451a8,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD13_W3,     0xfc0451ac,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD13_W4,     0xfc0451b0,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD13_W5,     0xfc0451b4,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD13_W6,     0xfc0451b8,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD13_W7,     0xfc0451bc,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD14_W0,     0xfc0451c0,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD14_W1,     0xfc0451c4,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD14_W2,     0xfc0451c8,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD14_W3,     0xfc0451cc,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD14_W4,     0xfc0451d0,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD14_W5,     0xfc0451d4,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD14_W6,     0xfc0451d8,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD14_W7,     0xfc0451dc,__READ_WRITE,__tcdw7_bits);

__IO_REG32_BIT(TCD15_W0,     0xfc0451e0,__READ_WRITE,__tcdw0_bits);
__IO_REG32_BIT(TCD15_W1,     0xfc0451e4,__READ_WRITE,__tcdw1_bits);
__IO_REG32_BIT(TCD15_W2,     0xfc0451e8,__READ_WRITE,__tcdw2_bits);
__IO_REG32_BIT(TCD15_W3,     0xfc0451ec,__READ_WRITE,__tcdw3_bits);
__IO_REG32_BIT(TCD15_W4,     0xfc0451f0,__READ_WRITE,__tcdw4_bits);
__IO_REG32_BIT(TCD15_W5,     0xfc0451f4,__READ_WRITE,__tcdw5_bits);
__IO_REG32_BIT(TCD15_W6,     0xfc0451f8,__READ_WRITE,__tcdw6_bits);
__IO_REG32_BIT(TCD15_W7,     0xfc0451fc,__READ_WRITE,__tcdw7_bits);

/***************************************************************************
 **
 ** INTC
 **
 ***************************************************************************/
__IO_REG32_BIT(IPRH,         0xfc048000,__READ      ,__iprh_bits);
__IO_REG32_BIT(IPRL,         0xfc048004,__READ      ,__iprl_bits);
__IO_REG32_BIT(IMRH,         0xfc048008,__READ_WRITE,__imrh_bits);
__IO_REG32_BIT(IMRL,         0xfc04800c,__READ_WRITE,__imrl_bits);
__IO_REG32_BIT(INTFRCH,      0xfc048010,__READ_WRITE,__intfrch_bits);
__IO_REG32_BIT(INTFRCL,      0xfc048014,__READ_WRITE,__intfrcl_bits);
__IO_REG8_BIT( ICONFIG,      0xFC04801B,__READ_WRITE,__iconfig_bits);
__IO_REG8_BIT( SIMR,         0xFC04801C,__READ_WRITE,__simr_bits);
__IO_REG8_BIT( CIMR,         0xFC04801D,__READ_WRITE,__cimr_bits);
__IO_REG8_BIT( CLMASK,       0xFC04801E,__READ_WRITE,__clmask_bits);
__IO_REG8_BIT( SLMASK,       0xFC04801F,__READ_WRITE,__slmask_bits);
__IO_REG8_BIT( ICR0,         0xfc048040,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR1,         0xfc048041,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR2,         0xfc048042,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR3,         0xfc048043,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR4,         0xfc048044,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR5,         0xfc048045,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR6,         0xfc048046,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR7,         0xfc048047,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR8,         0xfc048048,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR9,         0xfc048049,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR10,        0xfc04804a,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR11,        0xfc04804b,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR12,        0xfc04804c,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR13,        0xfc04804d,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR14,        0xfc04804e,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR15,        0xfc04804f,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR16,        0xfc048050,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR17,        0xfc048051,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR18,        0xfc048052,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR19,        0xfc048053,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR20,        0xfc048054,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR21,        0xfc048055,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR22,        0xfc048056,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR23,        0xfc048057,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR24,        0xfc048058,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR25,        0xfc048059,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR26,        0xfc04805a,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR27,        0xfc04805b,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR28,        0xfc04805c,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR29,        0xfc04805d,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR30,        0xfc04805e,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR31,        0xfc04805f,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR32,        0xfc048060,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR33,        0xfc048061,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR34,        0xfc048062,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR35,        0xfc048063,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR36,        0xfc048064,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR37,        0xfc048065,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR38,        0xfc048066,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR39,        0xfc048067,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR40,        0xfc048068,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR41,        0xfc048069,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR42,        0xfc04806a,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR43,        0xfc04806b,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR44,        0xfc04806c,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR45,        0xfc04806d,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR46,        0xfc04806e,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR47,        0xfc04806f,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR48,        0xfc048070,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR49,        0xfc048071,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR50,        0xfc048072,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR51,        0xfc048073,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR52,        0xfc048074,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR53,        0xfc048075,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR54,        0xfc048076,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR55,        0xfc048077,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR56,        0xfc048078,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR57,        0xfc048079,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR58,        0xfc04807a,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR59,        0xfc04807b,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR60,        0xfc04807c,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR61,        0xfc04807d,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR62,        0xfc04807e,__READ_WRITE,__icrn_bits);
__IO_REG8_BIT( ICR63,        0xfc04807f,__READ_WRITE,__icrn_bits);
__IO_REG8(     IRQIACK,      0xFC0480EC,__READ      );
__IO_REG8(     FIQIACK,      0xFC0480F0,__READ      );


/***************************************************************************
 **
 ** SSM
 **
 ***************************************************************************/
__IO_REG16_BIT(STATUS,       0xfc080002,__READ      ,__status_bits);
__IO_REG16_BIT(MEMCONFIG,    0xFC080004,__READ      ,__memconfig_bits);
__IO_REG32_BIT(WAKEUP,       0xfc080008,__READ_WRITE,__wakeup_bits);
#define ERROR WAKEUP
#define ERROR_bit WAKEUP_bit
__IO_REG16_BIT(PORTSEL,      0xfc08000c,__READ_WRITE,__portsel_bits);
__IO_REG16_BIT(DEBUGPORT,    0xfc08000e,__READ_WRITE,__debugport_bits);

/***************************************************************************
 **
 ** DMAMux
 **
 ***************************************************************************/
__IO_REG8_BIT( CHCONFIG0,    0xfc084000,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG1,    0xfc084001,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG2,    0xfc084002,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG3,    0xfc084003,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG4,    0xfc084004,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG5,    0xfc084005,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG6,    0xfc084006,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG7,    0xfc084007,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG8,    0xfc084008,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG9,    0xfc084009,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG10,   0xfc08400a,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG11,   0xfc08400b,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG12,   0xfc08400c,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG13,   0xfc08400d,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG14,   0xfc08400e,__READ_WRITE,__chconfign_bits);
__IO_REG8_BIT( CHCONFIG15,   0xfc08400f,__READ_WRITE,__chconfign_bits);


/***************************************************************************
 **
 ** CRG
 **
 ***************************************************************************/
__IO_REG8_BIT( SYNR,         0xfc088000,__READ_WRITE,__synr_bits);
__IO_REG8_BIT( REFDV,        0xfc088001,__READ_WRITE,__refdv_bits);
__IO_REG8_BIT( CRGFLG,       0xfc088003,__READ_WRITE,__crgflg_bits);
__IO_REG8_BIT( CRGINT,       0xfc088004,__READ_WRITE,__crgint_bits);
__IO_REG8_BIT( CLKSEL,       0xfc088005,__READ_WRITE,__clksel_bits);
__IO_REG8_BIT( PLLCTL,       0xfc088006,__READ_WRITE,__pllctl_bits);
__IO_REG8_BIT( SDMCTL,       0xfc088007,__READ_WRITE,__sdmctl_bits);
__IO_REG8_BIT( BDMCTL,       0xfc088008,__READ_WRITE,__bdmctl_bits);

/***************************************************************************
 **
 ** PIT
 **
 ***************************************************************************/
__IO_REG32_BIT(TLVAL0,       0xfc08c000,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL1,       0xfc08c004,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL2,       0xfc08c008,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL3,       0xfc08c00c,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL4,       0xfc08c010,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL5,       0xfc08c014,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL6,       0xfc08c018,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL7,       0xfc08c01c,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL8,       0xfc08c020,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL9,       0xfc08c024,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TLVAL10,      0xfc08c028,__READ_WRITE,__tlvaln_bits);
__IO_REG32_BIT(TVAL0,        0xfc08c080,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL1,        0xfc08c084,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL2,        0xfc08c088,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL3,        0xfc08c08c,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL4,        0xfc08c090,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL5,        0xfc08c094,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL6,        0xfc08c098,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL7,        0xfc08c09c,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL8,        0xfc08c0a0,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL9,        0xfc08c0a4,__READ      ,__tvaln_bits);
__IO_REG32_BIT(TVAL10,       0xfc08c0a8,__READ      ,__tvaln_bits);
__IO_REG32_BIT(PITFLG,       0xfc08c100,__READ_WRITE,__pitflg_bits);
__IO_REG32_BIT(PITINTEN,     0xfc08c104,__READ_WRITE,__pitinten_bits);
__IO_REG32_BIT(PITINTSEL,    0xfc08c108,__READ_WRITE,__pitintsel_bits);
__IO_REG32_BIT(PITEN,        0xfc08c10c,__READ_WRITE,__piten_bits);
__IO_REG32_BIT(PITCTRL,      0xfc08c110,__READ_WRITE,__pitctrl_bits);


/***************************************************************************
 **
 ** VREG
 **
 ***************************************************************************/
__IO_REG8_BIT( VREGHTCL,     0xfc090000,__READ_WRITE,__vreghtcl_bits);
__IO_REG8_BIT( VREGCTRL,     0xfc090001,__READ_WRITE,__vregctrl_bits);
__IO_REG8_BIT( VREGAPICL,    0xfc090002,__READ_WRITE,__vregapicl_bits);
__IO_REG8_BIT( VREGAPITR,    0xfc090003,__READ_WRITE,__vregapitr_bits);

/***************************************************************************
 **
 ** FlexCAN A
 **
 ***************************************************************************/
__IO_REG32_BIT(MCRA,         0xfc094000,__READ_WRITE,__mcrn_bits);
__IO_REG32_BIT(CTRLA,        0xfc094004,__READ_WRITE,__ctrl_bits);
__IO_REG32_BIT(TIMERA,       0xfc094008,__READ_WRITE,__timer_bits);
__IO_REG32_BIT(RXGMASKA,     0xfc094010,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX14MASKA,    0xfc094014,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX15MASKA,    0xfc094018,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(ECRA,         0xfc09401c,__READ_WRITE,__ecr_bits);
__IO_REG32_BIT(ESRA,         0xfc094020,__READ_WRITE,__esr_bits);
__IO_REG32_BIT(IMASKA,       0xfc094028,__READ_WRITE,__imask_bits);
__IO_REG32_BIT(IFLAGA,       0xfc094030,__READ_WRITE,__iflag_bits);
/* Message Buffer 0-31 */
__IO_REG32_BIT(MB0A_W0,      0xfc094080,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB0A_W1,      0xfc094084,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB0A_W2,      0xfc094088,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB0A_W3,      0xfc09408c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB1A_W0,      0xfc094090,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB1A_W1,      0xfc094094,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB1A_W2,      0xfc094098,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB1A_W3,      0xfc09409c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB2A_W0,      0xfc0940a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB2A_W1,      0xfc0940a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB2A_W2,      0xfc0940a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB2A_W3,      0xfc0940ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB3A_W0,      0xfc0940b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB3A_W1,      0xfc0940b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB3A_W2,      0xfc0940b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB3A_W3,      0xfc0940bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB4A_W0,      0xfc0940c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB4A_W1,      0xfc0940c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB4A_W2,      0xfc0940c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB4A_W3,      0xfc0940cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB5A_W0,      0xfc0940d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB5A_W1,      0xfc0940d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB5A_W2,      0xfc0940d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB5A_W3,      0xfc0940dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB6A_W0,      0xfc0940e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB6A_W1,      0xfc0940e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB6A_W2,      0xfc0940e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB6A_W3,      0xfc0940ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB7A_W0,      0xfc0940f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB7A_W1,      0xfc0940f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB7A_W2,      0xfc0940f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB7A_W3,      0xfc0940fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB8A_W0,      0xfc094100,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB8A_W1,      0xfc094104,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB8A_W2,      0xfc094108,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB8A_W3,      0xfc09410c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB9A_W0,      0xfc094110,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB9A_W1,      0xfc094114,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB9A_W2,      0xfc094118,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB9A_W3,      0xfc09411c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB10A_W0,     0xfc094120,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB10A_W1,     0xfc094124,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB10A_W2,     0xfc094128,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB10A_W3,     0xfc09412c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB11A_W0,     0xfc094130,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB11A_W1,     0xfc094134,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB11A_W2,     0xfc094138,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB11A_W3,     0xfc09413c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB12A_W0,     0xfc094140,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB12A_W1,     0xfc094144,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB12A_W2,     0xfc094148,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB12A_W3,     0xfc09414c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB13A_W0,     0xfc094150,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB13A_W1,     0xfc094154,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB13A_W2,     0xfc094158,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB13A_W3,     0xfc09415c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB14A_W0,     0xfc094160,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB14A_W1,     0xfc094164,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB14A_W2,     0xfc094168,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB14A_W3,     0xfc09416c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB15A_W0,     0xfc094170,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB15A_W1,     0xfc094174,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB15A_W2,     0xfc094178,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB15A_W3,     0xfc09417c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB16A_W0,     0xfc094180,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB16A_W1,     0xfc094184,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB16A_W2,     0xfc094188,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB16A_W3,     0xfc09418c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB17A_W0,     0xfc094190,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB17A_W1,     0xfc094194,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB17A_W2,     0xfc094198,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB17A_W3,     0xfc09419c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB18A_W0,     0xfc0941a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB18A_W1,     0xfc0941a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB18A_W2,     0xfc0941a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB18A_W3,     0xfc0941ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB19A_W0,     0xfc0941b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB19A_W1,     0xfc0941b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB19A_W2,     0xfc0941b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB19A_W3,     0xfc0941bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB20A_W0,     0xfc0941c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB20A_W1,     0xfc0941c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB20A_W2,     0xfc0941c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB20A_W3,     0xfc0941cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB21A_W0,     0xfc0941d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB21A_W1,     0xfc0941d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB21A_W2,     0xfc0941d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB21A_W3,     0xfc0941dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB22A_W0,     0xfc0941e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB22A_W1,     0xfc0941e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB22A_W2,     0xfc0941e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB22A_W3,     0xfc0941ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB23A_W0,     0xfc0941f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB23A_W1,     0xfc0941f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB23A_W2,     0xfc0941f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB23A_W3,     0xfc0941fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB24A_W0,     0xfc094200,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB24A_W1,     0xfc094204,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB24A_W2,     0xfc094208,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB24A_W3,     0xfc09420c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB25A_W0,     0xfc094210,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB25A_W1,     0xfc094214,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB25A_W2,     0xfc094218,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB25A_W3,     0xfc09421c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB26A_W0,     0xfc094220,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB26A_W1,     0xfc094224,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB26A_W2,     0xfc094228,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB26A_W3,     0xfc09422c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB27A_W0,     0xfc094230,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB27A_W1,     0xfc094234,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB27A_W2,     0xfc094238,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB27A_W3,     0xfc09423c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB28A_W0,     0xfc094240,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB28A_W1,     0xfc094244,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB28A_W2,     0xfc094248,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB28A_W3,     0xfc09424c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB29A_W0,     0xfc094250,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB29A_W1,     0xfc094254,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB29A_W2,     0xfc094258,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB29A_W3,     0xfc09425c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB30A_W0,     0xfc094260,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB30A_W1,     0xfc094264,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB30A_W2,     0xfc094268,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB30A_W3,     0xfc09426c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB31A_W0,     0xfc094270,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB31A_W1,     0xfc094274,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB31A_W2,     0xfc094278,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB31A_W3,     0xfc09427c,__READ_WRITE,__mbw3_bits);



/***************************************************************************
 **
 ** FlexCAN B
 **
 ***************************************************************************/
__IO_REG32_BIT(MCRB,         0xfc098000,__READ_WRITE,__mcrn_bits);
__IO_REG32_BIT(CTRLB,        0xfc098004,__READ_WRITE,__ctrl_bits);
__IO_REG32_BIT(TIMERB,       0xfc098008,__READ_WRITE,__timer_bits);
__IO_REG32_BIT(RXGMASKB,     0xfc098010,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX14MASKB,    0xfc098014,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX15MASKB,    0xfc098018,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(ECRB,         0xfc09801c,__READ_WRITE,__ecr_bits);
__IO_REG32_BIT(ESRB,         0xfc098020,__READ_WRITE,__esr_bits);
__IO_REG32_BIT(IMASKB,       0xfc098028,__READ_WRITE,__imask_bits);
__IO_REG32_BIT(IFLAGB,       0xfc098030,__READ_WRITE,__iflag_bits);

/* Message Buffer 0-31 */
__IO_REG32_BIT(MB0B_W0,      0xfc098080,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB0B_W1,      0xfc098084,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB0B_W2,      0xfc098088,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB0B_W3,      0xfc09808c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB1B_W0,      0xfc098090,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB1B_W1,      0xfc098094,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB1B_W2,      0xfc098098,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB1B_W3,      0xfc09809c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB2B_W0,      0xfc0980a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB2B_W1,      0xfc0980a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB2B_W2,      0xfc0980a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB2B_W3,      0xfc0980ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB3B_W0,      0xfc0980b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB3B_W1,      0xfc0980b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB3B_W2,      0xfc0980b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB3B_W3,      0xfc0980bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB4B_W0,      0xfc0980c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB4B_W1,      0xfc0980c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB4B_W2,      0xfc0980c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB4B_W3,      0xfc0980cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB5B_W0,      0xfc0980d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB5B_W1,      0xfc0980d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB5B_W2,      0xfc0980d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB5B_W3,      0xfc0980dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB6B_W0,      0xfc0980e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB6B_W1,      0xfc0980e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB6B_W2,      0xfc0980e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB6B_W3,      0xfc0980ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB7B_W0,      0xfc0980f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB7B_W1,      0xfc0980f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB7B_W2,      0xfc0980f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB7B_W3,      0xfc0980fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB8B_W0,      0xfc098100,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB8B_W1,      0xfc098104,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB8B_W2,      0xfc098108,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB8B_W3,      0xfc09810c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB9B_W0,      0xfc098110,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB9B_W1,      0xfc098114,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB9B_W2,      0xfc098118,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB9B_W3,      0xfc09811c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB10B_W0,     0xfc098120,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB10B_W1,     0xfc098124,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB10B_W2,     0xfc098128,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB10B_W3,     0xfc09812c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB11B_W0,     0xfc098130,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB11B_W1,     0xfc098134,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB11B_W2,     0xfc098138,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB11B_W3,     0xfc09813c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB12B_W0,     0xfc098140,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB12B_W1,     0xfc098144,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB12B_W2,     0xfc098148,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB12B_W3,     0xfc09814c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB13B_W0,     0xfc098150,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB13B_W1,     0xfc098154,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB13B_W2,     0xfc098158,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB13B_W3,     0xfc09815c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB14B_W0,     0xfc098160,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB14B_W1,     0xfc098164,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB14B_W2,     0xfc098168,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB14B_W3,     0xfc09816c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB15B_W0,     0xfc098170,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB15B_W1,     0xfc098174,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB15B_W2,     0xfc098178,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB15B_W3,     0xfc09817c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB16B_W0,     0xfc098180,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB16B_W1,     0xfc098184,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB16B_W2,     0xfc098188,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB16B_W3,     0xfc09818c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB17B_W0,     0xfc098190,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB17B_W1,     0xfc098194,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB17B_W2,     0xfc098198,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB17B_W3,     0xfc09819c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB18B_W0,     0xfc0981a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB18B_W1,     0xfc0981a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB18B_W2,     0xfc0981a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB18B_W3,     0xfc0981ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB19B_W0,     0xfc0981b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB19B_W1,     0xfc0981b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB19B_W2,     0xfc0981b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB19B_W3,     0xfc0981bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB20B_W0,     0xfc0981c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB20B_W1,     0xfc0981c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB20B_W2,     0xfc0981c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB20B_W3,     0xfc0981cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB21B_W0,     0xfc0981d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB21B_W1,     0xfc0981d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB21B_W2,     0xfc0981d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB21B_W3,     0xfc0981dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB22B_W0,     0xfc0981e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB22B_W1,     0xfc0981e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB22B_W2,     0xfc0981e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB22B_W3,     0xfc0981ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB23B_W0,     0xfc0981f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB23B_W1,     0xfc0981f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB23B_W2,     0xfc0981f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB23B_W3,     0xfc0981fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB24B_W0,     0xfc098200,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB24B_W1,     0xfc098204,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB24B_W2,     0xfc098208,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB24B_W3,     0xfc09820c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB25B_W0,     0xfc098210,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB25B_W1,     0xfc098214,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB25B_W2,     0xfc098218,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB25B_W3,     0xfc09821c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB26B_W0,     0xfc098220,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB26B_W1,     0xfc098224,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB26B_W2,     0xfc098228,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB26B_W3,     0xfc09822c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB27B_W0,     0xfc098230,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB27B_W1,     0xfc098234,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB27B_W2,     0xfc098238,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB27B_W3,     0xfc09823c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB28B_W0,     0xfc098240,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB28B_W1,     0xfc098244,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB28B_W2,     0xfc098248,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB28B_W3,     0xfc09824c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB29B_W0,     0xfc098250,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB29B_W1,     0xfc098254,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB29B_W2,     0xfc098258,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB29B_W3,     0xfc09825c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB30B_W0,     0xfc098260,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB30B_W1,     0xfc098264,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB30B_W2,     0xfc098268,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB30B_W3,     0xfc09826c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB31B_W0,     0xfc098270,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB31B_W1,     0xfc098274,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB31B_W2,     0xfc098278,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB31B_W3,     0xfc09827c,__READ_WRITE,__mbw3_bits);



/***************************************************************************
 **
 ** FlexCAN C
 **
 ***************************************************************************/
__IO_REG32_BIT(MCRC,         0xfc09c000,__READ_WRITE,__mcrn_bits);
__IO_REG32_BIT(CTRLC,        0xfc09c004,__READ_WRITE,__ctrl_bits);
__IO_REG32_BIT(TIMERC,       0xfc09c008,__READ_WRITE,__timer_bits);
__IO_REG32_BIT(RXGMASKC,     0xfc09c010,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX14MASKC,    0xfc09c014,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX15MASKC,    0xfc09c018,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(ECRC,         0xfc09c01c,__READ_WRITE,__ecr_bits);
__IO_REG32_BIT(ESRC,         0xfc09c020,__READ_WRITE,__esr_bits);
__IO_REG32_BIT(IMASKC,       0xfc09c028,__READ_WRITE,__imask_bits);
__IO_REG32_BIT(IFLAGC,       0xfc09c030,__READ_WRITE,__iflag_bits);

/* Message Buffer 0-31 */
__IO_REG32_BIT(MB0C_W0,      0xfc09c080,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB0C_W1,      0xfc09c084,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB0C_W2,      0xfc09c088,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB0C_W3,      0xfc09c08c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB1C_W0,      0xfc09c090,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB1C_W1,      0xfc09c094,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB1C_W2,      0xfc09c098,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB1C_W3,      0xfc09c09c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB2C_W0,      0xfc09c0a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB2C_W1,      0xfc09c0a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB2C_W2,      0xfc09c0a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB2C_W3,      0xfc09c0ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB3C_W0,      0xfc09c0b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB3C_W1,      0xfc09c0b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB3C_W2,      0xfc09c0b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB3C_W3,      0xfc09c0bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB4C_W0,      0xfc09c0c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB4C_W1,      0xfc09c0c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB4C_W2,      0xfc09c0c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB4C_W3,      0xfc09c0cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB5C_W0,      0xfc09c0d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB5C_W1,      0xfc09c0d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB5C_W2,      0xfc09c0d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB5C_W3,      0xfc09c0dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB6C_W0,      0xfc09c0e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB6C_W1,      0xfc09c0e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB6C_W2,      0xfc09c0e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB6C_W3,      0xfc09c0ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB7C_W0,      0xfc09c0f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB7C_W1,      0xfc09c0f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB7C_W2,      0xfc09c0f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB7C_W3,      0xfc09c0fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB8C_W0,      0xfc09c100,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB8C_W1,      0xfc09c104,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB8C_W2,      0xfc09c108,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB8C_W3,      0xfc09c10c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB9C_W0,      0xfc09c110,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB9C_W1,      0xfc09c114,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB9C_W2,      0xfc09c118,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB9C_W3,      0xfc09c11c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB10C_W0,     0xfc09c120,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB10C_W1,     0xfc09c124,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB10C_W2,     0xfc09c128,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB10C_W3,     0xfc09c12c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB11C_W0,     0xfc09c130,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB11C_W1,     0xfc09c134,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB11C_W2,     0xfc09c138,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB11C_W3,     0xfc09c13c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB12C_W0,     0xfc09c140,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB12C_W1,     0xfc09c144,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB12C_W2,     0xfc09c148,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB12C_W3,     0xfc09c14c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB13C_W0,     0xfc09c150,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB13C_W1,     0xfc09c154,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB13C_W2,     0xfc09c158,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB13C_W3,     0xfc09c15c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB14C_W0,     0xfc09c160,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB14C_W1,     0xfc09c164,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB14C_W2,     0xfc09c168,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB14C_W3,     0xfc09c16c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB15C_W0,     0xfc09c170,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB15C_W1,     0xfc09c174,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB15C_W2,     0xfc09c178,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB15C_W3,     0xfc09c17c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB16C_W0,     0xfc09c180,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB16C_W1,     0xfc09c184,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB16C_W2,     0xfc09c188,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB16C_W3,     0xfc09c18c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB17C_W0,     0xfc09c190,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB17C_W1,     0xfc09c194,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB17C_W2,     0xfc09c198,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB17C_W3,     0xfc09c19c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB18C_W0,     0xfc09c1a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB18C_W1,     0xfc09c1a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB18C_W2,     0xfc09c1a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB18C_W3,     0xfc09c1ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB19C_W0,     0xfc09c1b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB19C_W1,     0xfc09c1b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB19C_W2,     0xfc09c1b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB19C_W3,     0xfc09c1bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB20C_W0,     0xfc09c1c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB20C_W1,     0xfc09c1c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB20C_W2,     0xfc09c1c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB20C_W3,     0xfc09c1cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB21C_W0,     0xfc09c1d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB21C_W1,     0xfc09c1d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB21C_W2,     0xfc09c1d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB21C_W3,     0xfc09c1dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB22C_W0,     0xfc09c1e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB22C_W1,     0xfc09c1e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB22C_W2,     0xfc09c1e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB22C_W3,     0xfc09c1ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB23C_W0,     0xfc09c1f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB23C_W1,     0xfc09c1f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB23C_W2,     0xfc09c1f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB23C_W3,     0xfc09c1fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB24C_W0,     0xfc09c200,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB24C_W1,     0xfc09c204,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB24C_W2,     0xfc09c208,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB24C_W3,     0xfc09c20c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB25C_W0,     0xfc09c210,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB25C_W1,     0xfc09c214,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB25C_W2,     0xfc09c218,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB25C_W3,     0xfc09c21c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB26C_W0,     0xfc09c220,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB26C_W1,     0xfc09c224,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB26C_W2,     0xfc09c228,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB26C_W3,     0xfc09c22c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB27C_W0,     0xfc09c230,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB27C_W1,     0xfc09c234,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB27C_W2,     0xfc09c238,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB27C_W3,     0xfc09c23c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB28C_W0,     0xfc09c240,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB28C_W1,     0xfc09c244,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB28C_W2,     0xfc09c248,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB28C_W3,     0xfc09c24c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB29C_W0,     0xfc09c250,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB29C_W1,     0xfc09c254,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB29C_W2,     0xfc09c258,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB29C_W3,     0xfc09c25c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB30C_W0,     0xfc09c260,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB30C_W1,     0xfc09c264,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB30C_W2,     0xfc09c268,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB30C_W3,     0xfc09c26c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB31C_W0,     0xfc09c270,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB31C_W1,     0xfc09c274,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB31C_W2,     0xfc09c278,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB31C_W3,     0xfc09c27c,__READ_WRITE,__mbw3_bits);



/***************************************************************************
 **
 ** FlexCAN D
 **
 ***************************************************************************/
__IO_REG32_BIT(MCRD,         0xfc09a000,__READ_WRITE,__mcrn_bits);
__IO_REG32_BIT(CTRLD,        0xfc09a004,__READ_WRITE,__ctrl_bits);
__IO_REG32_BIT(TIMERD,       0xfc09a008,__READ_WRITE,__timer_bits);
__IO_REG32_BIT(RXGMASKD,     0xfc09a010,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX14MASKD,    0xfc09a014,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(RX15MASKD,    0xfc09a018,__READ_WRITE,__rxgmask_bits);
__IO_REG32_BIT(ECRD,         0xfc09a01c,__READ_WRITE,__ecr_bits);
__IO_REG32_BIT(ESRD,         0xfc09a020,__READ_WRITE,__esr_bits);
__IO_REG32_BIT(IMASKD,       0xfc09a028,__READ_WRITE,__imask_bits);
__IO_REG32_BIT(IFLAGD,       0xfc09a030,__READ_WRITE,__iflag_bits);

/* Message Buffer 0-31 */
__IO_REG32_BIT(MB0D_W0,      0xfc0a0080,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB0D_W1,      0xfc0a0084,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB0D_W2,      0xfc0a0088,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB0D_W3,      0xfc0a008c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB1D_W0,      0xfc0a0090,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB1D_W1,      0xfc0a0094,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB1D_W2,      0xfc0a0098,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB1D_W3,      0xfc0a009c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB2D_W0,      0xfc0a00a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB2D_W1,      0xfc0a00a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB2D_W2,      0xfc0a00a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB2D_W3,      0xfc0a00ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB3D_W0,      0xfc0a00b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB3D_W1,      0xfc0a00b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB3D_W2,      0xfc0a00b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB3D_W3,      0xfc0a00bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB4D_W0,      0xfc0a00c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB4D_W1,      0xfc0a00c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB4D_W2,      0xfc0a00c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB4D_W3,      0xfc0a00cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB5D_W0,      0xfc0a00d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB5D_W1,      0xfc0a00d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB5D_W2,      0xfc0a00d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB5D_W3,      0xfc0a00dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB6D_W0,      0xfc0a00e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB6D_W1,      0xfc0a00e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB6D_W2,      0xfc0a00e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB6D_W3,      0xfc0a00ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB7D_W0,      0xfc0a00f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB7D_W1,      0xfc0a00f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB7D_W2,      0xfc0a00f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB7D_W3,      0xfc0a00fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB8D_W0,      0xfc0a0100,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB8D_W1,      0xfc0a0104,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB8D_W2,      0xfc0a0108,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB8D_W3,      0xfc0a010c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB9D_W0,      0xfc0a0110,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB9D_W1,      0xfc0a0114,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB9D_W2,      0xfc0a0118,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB9D_W3,      0xfc0a011c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB10D_W0,     0xfc0a0120,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB10D_W1,     0xfc0a0124,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB10D_W2,     0xfc0a0128,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB10D_W3,     0xfc0a012c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB11D_W0,     0xfc0a0130,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB11D_W1,     0xfc0a0134,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB11D_W2,     0xfc0a0138,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB11D_W3,     0xfc0a013c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB12D_W0,     0xfc0a0140,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB12D_W1,     0xfc0a0144,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB12D_W2,     0xfc0a0148,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB12D_W3,     0xfc0a014c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB13D_W0,     0xfc0a0150,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB13D_W1,     0xfc0a0154,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB13D_W2,     0xfc0a0158,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB13D_W3,     0xfc0a015c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB14D_W0,     0xfc0a0160,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB14D_W1,     0xfc0a0164,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB14D_W2,     0xfc0a0168,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB14D_W3,     0xfc0a016c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB15D_W0,     0xfc0a0170,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB15D_W1,     0xfc0a0174,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB15D_W2,     0xfc0a0178,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB15D_W3,     0xfc0a017c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB16D_W0,     0xfc0a0180,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB16D_W1,     0xfc0a0184,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB16D_W2,     0xfc0a0188,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB16D_W3,     0xfc0a018c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB17D_W0,     0xfc0a0190,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB17D_W1,     0xfc0a0194,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB17D_W2,     0xfc0a0198,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB17D_W3,     0xfc0a019c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB18D_W0,     0xfc0a01a0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB18D_W1,     0xfc0a01a4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB18D_W2,     0xfc0a01a8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB18D_W3,     0xfc0a01ac,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB19D_W0,     0xfc0a01b0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB19D_W1,     0xfc0a01b4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB19D_W2,     0xfc0a01b8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB19D_W3,     0xfc0a01bc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB20D_W0,     0xfc0a01c0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB20D_W1,     0xfc0a01c4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB20D_W2,     0xfc0a01c8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB20D_W3,     0xfc0a01cc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB21D_W0,     0xfc0a01d0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB21D_W1,     0xfc0a01d4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB21D_W2,     0xfc0a01d8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB21D_W3,     0xfc0a01dc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB22D_W0,     0xfc0a01e0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB22D_W1,     0xfc0a01e4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB22D_W2,     0xfc0a01e8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB22D_W3,     0xfc0a01ec,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB23D_W0,     0xfc0a01f0,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB23D_W1,     0xfc0a01f4,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB23D_W2,     0xfc0a01f8,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB23D_W3,     0xfc0a01fc,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB24D_W0,     0xfc0a0200,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB24D_W1,     0xfc0a0204,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB24D_W2,     0xfc0a0208,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB24D_W3,     0xfc0a020c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB25D_W0,     0xfc0a0210,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB25D_W1,     0xfc0a0214,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB25D_W2,     0xfc0a0218,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB25D_W3,     0xfc0a021c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB26D_W0,     0xfc0a0220,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB26D_W1,     0xfc0a0224,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB26D_W2,     0xfc0a0228,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB26D_W3,     0xfc0a022c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB27D_W0,     0xfc0a0230,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB27D_W1,     0xfc0a0234,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB27D_W2,     0xfc0a0238,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB27D_W3,     0xfc0a023c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB28D_W0,     0xfc0a0240,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB28D_W1,     0xfc0a0244,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB28D_W2,     0xfc0a0248,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB28D_W3,     0xfc0a024c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB29D_W0,     0xfc0a0250,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB29D_W1,     0xfc0a0254,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB29D_W2,     0xfc0a0258,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB29D_W3,     0xfc0a025c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB30D_W0,     0xfc0a0260,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB30D_W1,     0xfc0a0264,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB30D_W2,     0xfc0a0268,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB30D_W3,     0xfc0a026c,__READ_WRITE,__mbw3_bits);

__IO_REG32_BIT(MB31D_W0,     0xfc0a0270,__READ_WRITE,__mbw0_bits);
__IO_REG32_BIT(MB31D_W1,     0xfc0a0274,__READ_WRITE,__mbw1_bits);
__IO_REG32_BIT(MB31D_W2,     0xfc0a0278,__READ_WRITE,__mbw2_bits);
__IO_REG32_BIT(MB31D_W3,     0xfc0a027c,__READ_WRITE,__mbw3_bits);




/***************************************************************************
 **
 ** I2C
 **
 ***************************************************************************/
__IO_REG8_BIT( IBAD,         0xfc0a0000,__READ_WRITE,__ibad_bits);
__IO_REG8_BIT( IBFD,         0xfc0a0001,__READ_WRITE,__ibfd_bits);
__IO_REG8_BIT( IBCR,         0xfc0a0002,__READ_WRITE,__ibcr_bits);
__IO_REG8_BIT( IBSR,         0xfc0a0003,__READ_WRITE,__ibsr_bits);
__IO_REG8(     IBDR,         0xfc0a0004,__READ_WRITE);

/***************************************************************************
 **
 ** DSPI A
 **
 ***************************************************************************/
__IO_REG32_BIT(DSPIA_MCR,    0xfc0b4000,__READ_WRITE,__dspix_mcr_bits);
__IO_REG32_BIT(DSPIA_TCR,    0xfc0b4008,__READ_WRITE,__dspix_tcr_bits);
__IO_REG32_BIT(DSPIA_CTAR0,  0xfc0b400c,__READ_WRITE,__dspix_ctarn_bits);
__IO_REG32_BIT(DSPIA_CTAR1,  0xfc0b4010,__READ_WRITE,__dspix_ctarn_bits);
__IO_REG32_BIT(DSPIA_CTAR2,  0xfc0b4014,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIA_CTAR3,  0xfc0b4018,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIA_CTAR4,  0xfc0b401c,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIA_CTAR5,  0xfc0b4020,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIA_SR,     0xfc0b402c,__READ_WRITE,__dspix_sr_bits);
__IO_REG32_BIT(DSPIA_RSER,   0xfc0b4030,__READ_WRITE,__dspix_rser_bits);
__IO_REG32_BIT(DSPIA_PUSHR,  0xfc0b4034,__READ_WRITE,__dspix_pushr_bits);
__IO_REG32_BIT(DSPIA_POPR,   0xfc0b4038,__READ      ,__dspix_popr_bits);
__IO_REG32_BIT(DSPIA_TXFR0,  0xfc0b403c,__READ      ,__dspix_txfrn_bits);
__IO_REG32_BIT(DSPIA_TXFR1,  0xfc0b4040,__READ      ,__dspix_txfrn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIA_TXFR2,  0xfc0b4044,__READ      ,__dspix_txfrn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIA_TXFR3,  0xfc0b4048,__READ      ,__dspix_txfrn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIA_RXFR0,  0xfc0b407c,__READ      ,__dspix_rxfrn_bits);
__IO_REG32_BIT(DSPIA_RXFR1,  0xfc0b4080,__READ      ,__dspix_rxfrn_bits);
__IO_REG32_BIT(DSPIA_RXFR2,  0xfc0b4084,__READ      ,__dspix_rxfrn_bits);
__IO_REG32_BIT(DSPIA_RXFR3,  0xfc0b4088,__READ      ,__dspix_rxfrn_bits);

/***************************************************************************
 **
 ** DSPI B
 **
 ***************************************************************************/
__IO_REG32_BIT(DSPIB_MCR,    0xfc0b8000,__READ_WRITE,__dspix_mcr_bits);
__IO_REG32_BIT(DSPIB_TCR,    0xfc0b8008,__READ_WRITE,__dspix_tcr_bits);
__IO_REG32_BIT(DSPIB_CTAR0,  0xfc0b800c,__READ_WRITE,__dspix_ctarn_bits);
__IO_REG32_BIT(DSPIB_CTAR1,  0xfc0b8010,__READ_WRITE,__dspix_ctarn_bits);
__IO_REG32_BIT(DSPIB_CTAR2,  0xfc0b8014,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIB_CTAR3,  0xfc0b8018,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIB_CTAR4,  0xfc0b801c,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIB_CTAR5,  0xfc0b8020,__READ_WRITE,__dspix_ctarn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIB_SR,     0xfc0b802c,__READ_WRITE,__dspix_sr_bits);
__IO_REG32_BIT(DSPIB_RSER,   0xfc0b8030,__READ_WRITE,__dspix_rser_bits);
__IO_REG32_BIT(DSPIB_PUSHR,  0xfc0b8034,__READ_WRITE,__dspix_pushr_bits);
__IO_REG32_BIT(DSPIB_POPR,   0xfc0b8038,__READ      ,__dspix_popr_bits);
__IO_REG32_BIT(DSPIB_TXFR0,  0xfc0b803c,__READ      ,__dspix_txfrn_bits);
__IO_REG32_BIT(DSPIB_TXFR1,  0xfc0b8040,__READ      ,__dspix_txfrn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIB_TXFR2,  0xfc0b8044,__READ      ,__dspix_txfrn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIB_TXFR3,  0xfc0b8048,__READ      ,__dspix_txfrn_bits);  /* not present on mask set L49P devices */
__IO_REG32_BIT(DSPIB_RXFR0,  0xfc0b807c,__READ      ,__dspix_rxfrn_bits);
__IO_REG32_BIT(DSPIB_RXFR1,  0xfc0b8080,__READ      ,__dspix_rxfrn_bits);
__IO_REG32_BIT(DSPIB_RXFR2,  0xfc0b8084,__READ      ,__dspix_rxfrn_bits);
__IO_REG32_BIT(DSPIB_RXFR3,  0xfc0b8088,__READ      ,__dspix_rxfrn_bits);

/***************************************************************************
 **
 ** eSCI A
 **
 ***************************************************************************/
__IO_REG8_BIT( ESCIBDH_A,    0xFC0C4000,__READ_WRITE,__escibdh_bits);
__IO_REG8_BIT( ESCIBDL_A,    0xFC0C4001,__READ_WRITE,__escibdl_bits);
__IO_REG8_BIT( ESCICR1_A,    0xfc0c4002,__READ_WRITE,__escicr1_bits);
__IO_REG8_BIT( ESCICR2_A,    0xfc0c4003,__READ_WRITE,__escicr2_bits);
__IO_REG8_BIT( ESCICR3_A,    0xfc0c4004,__READ_WRITE,__escicr3_bits);
__IO_REG8_BIT( ESCICR4_A,    0xfc0c4005,__READ_WRITE,__escicr4_bits);
__IO_REG8_BIT( ESCIDRH_A,    0xfc0c4006,__READ_WRITE,__escidrh_bits);
__IO_REG8(     ESCIDRL_A,    0xFC0C4007,__READ_WRITE);
__IO_REG8_BIT( ESCISR1_A,    0xfc0c4008,__READ      ,__escisr1_bits);
__IO_REG8_BIT( ESCISR2_A,    0xfc0c4009,__READ_WRITE,__escisr2_bits);
__IO_REG8_BIT( LINSTAT1_A,   0xfc0c400a,__READ_WRITE,__linstat1_bits);
__IO_REG8_BIT( LINSTAT2_A,   0xfc0c400b,__READ_WRITE,__linstat2_bits);
__IO_REG8_BIT( LINCTRL1_A,   0xfc0c400c,__READ_WRITE,__linctrl1_bits);
__IO_REG8_BIT( LINCTRL2_A,   0xfc0c400d,__READ_WRITE,__linctrl2_bits);
__IO_REG8_BIT( LINCTRL3_A,   0xfc0c400e,__READ_WRITE,__linctrl3_bits);
__IO_REG8_BIT( LINTX_A,      0xfc0c4010,__WRITE     ,__lintx_bits);
__IO_REG8(     LINRX_A,      0xFC0C4014,__READ      );
__IO_REG8(     LINCRCP1_A,   0xFC0C4018,__READ_WRITE);
__IO_REG8(     LINCRCP2_A,   0xFC0C4019,__READ_WRITE);


/***************************************************************************
 **
 ** eSCI B
 **
 ***************************************************************************/
__IO_REG8_BIT( ESCIBDH_B,    0xFC0C8000,__READ_WRITE,__escibdh_bits);
__IO_REG8_BIT( ESCIBDL_B,    0xFC0C8001,__READ_WRITE,__escibdl_bits);
__IO_REG8_BIT( ESCICR1_B,    0xfc0c8002,__READ_WRITE,__escicr1_bits);
__IO_REG8_BIT( ESCICR2_B,    0xfc0c8003,__READ_WRITE,__escicr2_bits);
__IO_REG8_BIT( ESCICR3_B,    0xfc0c8004,__READ_WRITE,__escicr3_bits);
__IO_REG8_BIT( ESCICR4_B,    0xfc0c8005,__READ_WRITE,__escicr4_bits);
__IO_REG8_BIT( ESCIDRH_B,    0xfc0c8006,__READ_WRITE,__escidrh_bits);
__IO_REG8(     ESCIDRL_B,    0xFC0C8007,__READ_WRITE);
__IO_REG8_BIT( ESCISR1_B,    0xfc0c8008,__READ      ,__escisr1_bits);
__IO_REG8_BIT( ESCISR2_B,    0xfc0c8009,__READ_WRITE,__escisr2_bits);
__IO_REG8_BIT( LINSTAT1_B,   0xfc0c800a,__READ_WRITE,__linstat1_bits);
__IO_REG8_BIT( LINSTAT2_B,   0xfc0c800b,__READ_WRITE,__linstat2_bits);
__IO_REG8_BIT( LINCTRL1_B,   0xfc0c800c,__READ_WRITE,__linctrl1_bits);
__IO_REG8_BIT( LINCTRL2_B,   0xfc0c800d,__READ_WRITE,__linctrl2_bits);
__IO_REG8_BIT( LINCTRL3_B,   0xfc0c800e,__READ_WRITE,__linctrl3_bits);
__IO_REG8_BIT( LINTX_B,      0xfc0c8010,__WRITE     ,__lintx_bits);
__IO_REG8(     LINRX_B,      0xFC0C8014,__READ      );
__IO_REG8(     LINCRCP1_B,   0xFC0C8018,__READ_WRITE);
__IO_REG8(     LINCRCP2_B,   0xFC0C8019,__READ_WRITE);



/***************************************************************************
 **
 ** eSCI C
 **
 ***************************************************************************/
__IO_REG8_BIT( ESCIBDH_C,    0xFC0Cc000,__READ_WRITE,__escibdh_bits);
__IO_REG8_BIT( ESCIBDL_C,    0xFC0Cc001,__READ_WRITE,__escibdl_bits);
__IO_REG8_BIT( ESCICR1_C,    0xfc0cc002,__READ_WRITE,__escicr1_bits);
__IO_REG8_BIT( ESCICR2_C,    0xfc0cc003,__READ_WRITE,__escicr2_bits);
__IO_REG8_BIT( ESCICR3_C,    0xfc0cc004,__READ_WRITE,__escicr3_bits);
__IO_REG8_BIT( ESCICR4_C,    0xfc0cc005,__READ_WRITE,__escicr4_bits);
__IO_REG8_BIT( ESCIDRH_C,    0xfc0cc006,__READ_WRITE,__escidrh_bits);
__IO_REG8(     ESCIDRL_C,    0xFC0Cc007,__READ_WRITE);
__IO_REG8_BIT( ESCISR1_C,    0xfc0cc008,__READ      ,__escisr1_bits);
__IO_REG8_BIT( ESCISR2_C,    0xfc0cc009,__READ_WRITE,__escisr2_bits);
__IO_REG8_BIT( LINSTAT1_C,   0xfc0cc00a,__READ_WRITE,__linstat1_bits);
__IO_REG8_BIT( LINSTAT2_C,   0xfc0cc00b,__READ_WRITE,__linstat2_bits);
__IO_REG8_BIT( LINCTRL1_C,   0xfc0cc00c,__READ_WRITE,__linctrl1_bits);
__IO_REG8_BIT( LINCTRL2_C,   0xfc0cc00d,__READ_WRITE,__linctrl2_bits);
__IO_REG8_BIT( LINCTRL3_C,   0xfc0cc00e,__READ_WRITE,__linctrl3_bits);
__IO_REG8_BIT( LINTX_C,      0xfc0cc010,__WRITE     ,__lintx_bits);
__IO_REG8(     LINRX_C,      0xFC0Cc014,__READ      );
__IO_REG8(     LINCRCP1_C,   0xFC0Cc018,__READ_WRITE);
__IO_REG8(     LINCRCP2_C,   0xFC0Cc019,__READ_WRITE);


/***************************************************************************
 **
 ** eSCI D
 **
 ***************************************************************************/
__IO_REG8_BIT( ESCIBDH_D,    0xFC0Cd000,__READ_WRITE,__escibdh_bits);
__IO_REG8_BIT( ESCIBDL_D,    0xFC0Cd001,__READ_WRITE,__escibdl_bits);
__IO_REG8_BIT( ESCICR1_D,    0xfc0cd002,__READ_WRITE,__escicr1_bits);
__IO_REG8_BIT( ESCICR2_D,    0xfc0cd003,__READ_WRITE,__escicr2_bits);
__IO_REG8_BIT( ESCICR3_D,    0xfc0cd004,__READ_WRITE,__escicr3_bits);
__IO_REG8_BIT( ESCICR4_D,    0xfc0cd005,__READ_WRITE,__escicr4_bits);
__IO_REG8_BIT( ESCIDRH_D,    0xfc0cd006,__READ_WRITE,__escidrh_bits);
__IO_REG8(     ESCIDRL_D,    0xFC0Cd007,__READ_WRITE);
__IO_REG8_BIT( ESCISR1_D,    0xfc0cd008,__READ      ,__escisr1_bits);
__IO_REG8_BIT( ESCISR2_D,    0xfc0cd009,__READ_WRITE,__escisr2_bits);
__IO_REG8_BIT( LINSTAT1_D,   0xfc0cd00a,__READ_WRITE,__linstat1_bits);
__IO_REG8_BIT( LINSTAT2_D,   0xfc0cd00b,__READ_WRITE,__linstat2_bits);
__IO_REG8_BIT( LINCTRL1_D,   0xfc0cd00c,__READ_WRITE,__linctrl1_bits);
__IO_REG8_BIT( LINCTRL2_D,   0xfc0cd00d,__READ_WRITE,__linctrl2_bits);
__IO_REG8_BIT( LINCTRL3_D,   0xfc0cd00e,__READ_WRITE,__linctrl3_bits);
__IO_REG8_BIT( LINTX_D,      0xfc0cd010,__WRITE     ,__lintx_bits);
__IO_REG8(     LINRX_D,      0xFC0Cd014,__READ      );
__IO_REG8(     LINCRCP1_D,   0xFC0Cd018,__READ_WRITE);
__IO_REG8(     LINCRCP2_D,   0xFC0Cd019,__READ_WRITE);

/***************************************************************************
 **
 ** eMIOS
 **
 ***************************************************************************/
/* The MCR is named MCR0 to avoid assembler conflict with the MCR ARM instruction. */
__IO_REG32_BIT(MCR0,         0xFC0DC000,__READ_WRITE,__mcr0_bits);
__IO_REG32_BIT(GFLAG,        0xfc0dc004,__READ      ,__gflag_bits);
__IO_REG32_BIT(OUDIS,        0xfc0dc008,__READ_WRITE,__oudis_bits);
__IO_REG32_BIT(UCDIS,        0xfc0dc00c,__READ_WRITE,__ucdis_bits);

__IO_REG32_BIT(UCA0,         0xfc0dc020,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB0,         0xfc0dc024,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT0,       0xfc0dc028,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR0,        0xfc0dc02c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR0,        0xfc0dc030,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA1,         0xfc0dc040,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB1,         0xfc0dc044,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT1,       0xfc0dc048,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR1,        0xfc0dc04c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR1,        0xfc0dc050,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA2,         0xfc0dc060,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB2,         0xfc0dc064,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT2,       0xfc0dc068,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR2,        0xfc0dc06c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR2,        0xfc0dc070,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA3,         0xfc0dc080,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB3,         0xfc0dc084,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT3,       0xfc0dc088,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR3,        0xfc0dc08c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR3,        0xfc0dc090,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA4,         0xfc0dc0a0,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB4,         0xfc0dc0a4,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT4,       0xfc0dc0a8,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR4,        0xfc0dc0ac,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR4,        0xfc0dc0b0,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA5,         0xfc0dc0c0,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB5,         0xfc0dc0c4,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT5,       0xfc0dc0c8,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR5,        0xfc0dc0cc,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR5,        0xfc0dc0d0,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA6,         0xfc0dc0e0,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB6,         0xfc0dc0e4,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT6,       0xfc0dc0e8,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR6,        0xfc0dc0ec,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR6,        0xfc0dc0f0,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA7,         0xfc0dc100,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB7,         0xfc0dc104,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT7,       0xfc0dc108,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR7,        0xfc0dc10c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR7,        0xfc0dc110,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA8,         0xfc0dc120,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB8,         0xfc0dc124,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT8,       0xfc0dc128,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR8,        0xfc0dc12c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR8,        0xfc0dc130,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA9,         0xfc0dc140,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB9,         0xfc0dc144,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT9,       0xfc0dc148,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR9,        0xfc0dc14c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR9,        0xfc0dc150,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA10,        0xfc0dc160,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB10,        0xfc0dc164,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT10,      0xfc0dc168,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR10,       0xfc0dc16c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR10,       0xfc0dc170,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA11,        0xfc0dc180,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB11,        0xfc0dc184,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT11,      0xfc0dc188,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR11,       0xfc0dc18c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR11,       0xfc0dc190,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA12,        0xfc0dc1a0,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB12,        0xfc0dc1a4,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT12,      0xfc0dc1a8,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR12,       0xfc0dc1ac,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR12,       0xfc0dc1b0,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA13,        0xfc0dc1c0,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB13,        0xfc0dc1c4,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT13,      0xfc0dc1c8,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR13,       0xfc0dc1cc,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR13,       0xfc0dc1d0,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA14,        0xfc0dc1e0,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB14,        0xfc0dc1e4,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT14,      0xfc0dc1e8,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR14,       0xfc0dc1ec,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR14,       0xfc0dc1f0,__READ_WRITE,__ucsrn_bits);

__IO_REG32_BIT(UCA15,        0xfc0dc200,__READ_WRITE,__ucan_bits);
__IO_REG32_BIT(UCB15,        0xfc0dc204,__READ_WRITE,__ucbn_bits);
__IO_REG32_BIT(UCCNT15,      0xfc0dc208,__READ_WRITE,__uccntn_bits);
__IO_REG32_BIT(UCCR15,       0xfc0dc20c,__READ_WRITE,__uccrn_bits);
__IO_REG32_BIT(UCSR15,       0xfc0dc210,__READ_WRITE,__ucsrn_bits);


/***************************************************************************
 **
 ** ATD A
 **
 ***************************************************************************/
__IO_REG8_BIT( ATDTRIGCTL_A, 0xfc0e0000,__READ_WRITE,__atdtrigctl_bits);
__IO_REG8_BIT( ATDETRIGCH_A, 0xfc0e0001,__READ_WRITE,__atdetrigch_bits);
__IO_REG8_BIT( ATDPRE_A,     0xfc0e0002,__READ_WRITE,__atdpre_bits);
__IO_REG8_BIT( ATDMODE_A,    0xfc0e0003,__READ_WRITE,__atdmode_bits);
__IO_REG8_BIT( ATDINT_A,     0xfc0e000e,__READ_WRITE,__atdint_bits);
__IO_REG8_BIT( ATDFLAG_A,    0xfc0e000f,__READ_WRITE,__atdflag_bits);
__IO_REG32_BIT(ATDCW_A,      0xfc0e0010,__READ_WRITE,__atdcw_bits);
__IO_REG32_BIT(ATDRR_A,      0xfc0e0014,__READ      ,__atdrr_bits);

/***************************************************************************
 **
 ** ATD B
 **
 ***************************************************************************/
__IO_REG8_BIT( ATDTRIGCTL_B, 0xfc0e4000,__READ_WRITE,__atdtrigctl_bits);
__IO_REG8_BIT( ATDETRIGCH_B, 0xfc0e4001,__READ_WRITE,__atdetrigch_bits);
__IO_REG8_BIT( ATDPRE_B,     0xfc0e4002,__READ_WRITE,__atdpre_bits);
__IO_REG8_BIT( ATDMODE_B,    0xfc0e4003,__READ_WRITE,__atdmode_bits);
__IO_REG8_BIT( ATDINT_B,     0xfc0e400e,__READ_WRITE,__atdint_bits);
__IO_REG8_BIT( ATDFLAG_B,    0xfc0e400f,__READ_WRITE,__atdflag_bits);
__IO_REG32_BIT(ATDCW_B,      0xfc0e4010,__READ_WRITE,__atdcw_bits);
__IO_REG32_BIT(ATDRR_B,      0xfc0e4014,__READ      ,__atdrr_bits);

/***************************************************************************
 **
 ** PIM global registers
 **
 ***************************************************************************/
__IO_REG16_BIT(GLBINT,       0xfc0e83c0,__READ      ,__glbint_bits);
__IO_REG16_BIT(PIMCONFIG,    0xfc0e83c2,__READ_WRITE,__pimconfig_bits);
__IO_REG16_BIT(CONFIG_TDI,   0xfc0e83c4,__READ_WRITE,__configdiv_bits);
__IO_REG16_BIT(CONFIG_TDO,   0xfc0e83c6,__READ_WRITE,__configtdo_bits);
__IO_REG16_BIT(CONFIG_TMS,   0xfc0e83c8,__READ_WRITE,__configdiv_bits);
__IO_REG16_BIT(CONFIG_TCK,   0xfc0e83ca,__READ_WRITE,__configdiv_bits);
__IO_REG16_BIT(CONFIG_TA,    0xfc0e83cc,__READ_WRITE,__configta_bits);
__IO_REG32(    PORT32IR_AB,  0xfc0e83e0,__READ      );
__IO_REG32(    PORT32IR_CD,  0xfc0e83e4,__READ      );
__IO_REG32(    PORT32IR_EF,  0xfc0e83e8,__READ      );
__IO_REG32(    PORT32IR_GH,  0xfc0e83ec,__READ      );
__IO_REG32(    PORT32IR_BC,  0xfc0e83f0,__READ      );
__IO_REG32(    PORT32IR_DE,  0xfc0e83f4,__READ      );
__IO_REG32(    PORT32IR_FG,  0xfc0e83f8,__READ      );
__IO_REG32(    PORT32IR_HI,  0xfc0e83fc,__READ      );


/***************************************************************************
 **
 ** PIM PORT A
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_A,    0xfc0e8000,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_A,    0xfc0e8002,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_A,    0xfc0e8004,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_A,    0xfc0e8006,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_A,    0xfc0e8008,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_A,    0xfc0e800a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_A,    0xfc0e800c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_A,    0xfc0e800e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_A,    0xfc0e8010,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_A,    0xfc0e8012,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_A,   0xfc0e8014,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_A,   0xfc0e8016,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_A,   0xfc0e8018,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_A,   0xfc0e801a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_A,   0xfc0e801c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_A,   0xfc0e801e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_A,    0xfc0e8020,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_A,   0xfc0e8024,__READ_WRITE);
__IO_REG16(    PORTIR_A,     0xfc0e8026,__READ      );
__IO_REG8_BIT( PINDATA0_A,   0xfc0e8028,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_A,   0xfc0e8029,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_A,   0xfc0e802a,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_A,   0xfc0e802b,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_A,   0xfc0e802c,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_A,   0xfc0e802d,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_A,   0xfc0e802e,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_A,   0xfc0e802f,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_A,   0xfc0e8030,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_A,   0xfc0e8031,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_A,  0xfc0e8032,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_A,  0xfc0e8033,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_A,  0xfc0e8034,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_A,  0xfc0e8035,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_A,  0xfc0e8036,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_A,  0xfc0e8037,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT B
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_B,    0xfc0e8040,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_B,    0xfc0e8042,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_B,    0xfc0e8044,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_B,    0xfc0e8046,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_B,    0xfc0e8048,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_B,    0xfc0e804a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_B,    0xfc0e804c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_B,    0xfc0e804e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_B,    0xfc0e8050,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_B,    0xfc0e8052,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_B,   0xfc0e8054,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_B,   0xfc0e8056,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_B,   0xfc0e8058,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_B,   0xfc0e805a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_B,   0xfc0e805c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_B,   0xfc0e805e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_B,    0xfc0e8060,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_B,   0xfc0e8064,__READ_WRITE);
__IO_REG16(    PORTIR_B,     0xfc0e8066,__READ      );
__IO_REG8_BIT( PINDATA0_B,   0xfc0e8068,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_B,   0xfc0e8069,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_B,   0xfc0e806a,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_B,   0xfc0e806b,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_B,   0xfc0e806c,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_B,   0xfc0e806d,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_B,   0xfc0e806e,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_B,   0xfc0e806f,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_B,   0xfc0e8070,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_B,   0xfc0e8071,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_B,  0xfc0e8072,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_B,  0xfc0e8073,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_B,  0xfc0e8074,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_B,  0xfc0e8075,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_B,  0xfc0e8076,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_B,  0xfc0e8077,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT C
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_C,    0xfc0e8080,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_C,    0xfc0e8082,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_C,    0xfc0e8084,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_C,    0xfc0e8086,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_C,    0xfc0e8088,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_C,    0xfc0e808a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_C,    0xfc0e808c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_C,    0xfc0e808e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_C,    0xfc0e8090,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_C,    0xfc0e8092,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_C,   0xfc0e8094,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_C,   0xfc0e8096,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_C,   0xfc0e8098,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_C,   0xfc0e809a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_C,   0xfc0e809c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_C,   0xfc0e809e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_C,    0xfc0e80a0,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_C,   0xfc0e80a4,__READ_WRITE);
__IO_REG16(    PORTIR_C,     0xfc0e80a6,__READ      );
__IO_REG8_BIT( PINDATA0_C,   0xfc0e80a8,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_C,   0xfc0e80a9,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_C,   0xfc0e80aa,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_C,   0xfc0e80ab,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_C,   0xfc0e80ac,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_C,   0xfc0e80ad,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_C,   0xfc0e80ae,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_C,   0xfc0e80af,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_C,   0xfc0e80b0,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_C,   0xfc0e80b1,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_C,  0xfc0e80b2,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_C,  0xfc0e80b3,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_C,  0xfc0e80b4,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_C,  0xfc0e80b5,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_C,  0xfc0e80b6,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_C,  0xfc0e80b7,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT D
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_D,    0xfc0e80c0,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_D,    0xfc0e80c2,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_D,    0xfc0e80c4,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_D,    0xfc0e80c6,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_D,    0xfc0e80c8,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_D,    0xfc0e80ca,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_D,    0xfc0e80cc,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_D,    0xfc0e80ce,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_D,    0xfc0e80d0,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_D,    0xfc0e80d2,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_D,   0xfc0e80d4,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_D,   0xfc0e80d6,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_D,   0xfc0e80d8,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_D,   0xfc0e80da,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_D,   0xfc0e80dc,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_D,   0xfc0e80de,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_D,    0xfc0e80e0,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_D,   0xfc0e80e4,__READ_WRITE);
__IO_REG16(    PORTIR_D,     0xfc0e80e6,__READ      );
__IO_REG8_BIT( PINDATA0_D,   0xfc0e80e8,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_D,   0xfc0e80e9,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_D,   0xfc0e80ea,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_D,   0xfc0e80eb,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_D,   0xfc0e80ec,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_D,   0xfc0e80ed,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_D,   0xfc0e80ee,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_D,   0xfc0e80ef,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_D,   0xfc0e80f0,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_D,   0xfc0e80f1,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_D,  0xfc0e80f2,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_D,  0xfc0e80f3,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_D,  0xfc0e80f4,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_D,  0xfc0e80f5,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_D,  0xfc0e80f6,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_D,  0xfc0e80f7,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT E
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_E,    0xfc0e8100,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_E,    0xfc0e8102,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_E,    0xfc0e8104,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_E,    0xfc0e8106,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_E,    0xfc0e8108,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_E,    0xfc0e810a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_E,    0xfc0e810c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_E,    0xfc0e810e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_E,    0xfc0e8110,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_E,    0xfc0e8112,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_E,   0xfc0e8114,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_E,   0xfc0e8116,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_E,   0xfc0e8118,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_E,   0xfc0e811a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_E,   0xfc0e811c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_E,   0xfc0e811e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_E,    0xfc0e8120,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_E,   0xfc0e8124,__READ_WRITE);
__IO_REG16(    PORTIR_E,     0xfc0e8126,__READ      );
__IO_REG8_BIT( PINDATA0_E,   0xfc0e8128,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_E,   0xfc0e8129,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_E,   0xfc0e812a,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_E,   0xfc0e812b,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_E,   0xfc0e812c,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_E,   0xfc0e812d,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_E,   0xfc0e812e,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_E,   0xfc0e812f,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_E,   0xfc0e8130,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_E,   0xfc0e8131,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_E,  0xfc0e8132,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_E,  0xfc0e8133,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_E,  0xfc0e8134,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_E,  0xfc0e8135,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_E,  0xfc0e8136,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_E,  0xfc0e8137,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT F
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_F,    0xfc0e8140,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_F,    0xfc0e8142,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_F,    0xfc0e8144,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_F,    0xfc0e8146,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_F,    0xfc0e8148,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_F,    0xfc0e814a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_F,    0xfc0e814c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_F,    0xfc0e814e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_F,    0xfc0e8150,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_F,    0xfc0e8152,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_F,   0xfc0e8154,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_F,   0xfc0e8156,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_F,   0xfc0e8158,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_F,   0xfc0e815a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_F,   0xfc0e815c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_F,   0xfc0e815e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_F,    0xfc0e8160,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_F,   0xfc0e8164,__READ_WRITE);
__IO_REG16(    PORTIR_F,     0xfc0e8166,__READ      );
__IO_REG8_BIT( PINDATA0_F,   0xfc0e8168,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_F,   0xfc0e8169,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_F,   0xfc0e816a,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_F,   0xfc0e816b,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_F,   0xfc0e816c,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_F,   0xfc0e816d,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_F,   0xfc0e816e,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_F,   0xfc0e816f,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_F,   0xfc0e8170,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_F,   0xfc0e8171,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_F,  0xfc0e8172,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_F,  0xfc0e8173,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_F,  0xfc0e8174,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_F,  0xfc0e8175,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_F,  0xfc0e8176,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_F,  0xfc0e8177,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT G
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_G,    0xfc0e8180,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_G,    0xfc0e8182,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_G,    0xfc0e8184,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_G,    0xfc0e8186,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_G,    0xfc0e8188,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_G,    0xfc0e818a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_G,    0xfc0e818c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_G,    0xfc0e818e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_G,    0xfc0e8190,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_G,    0xfc0e8192,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_G,   0xfc0e8194,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_G,   0xfc0e8196,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_G,   0xfc0e8198,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_G,   0xfc0e819a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_G,   0xfc0e819c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_G,   0xfc0e819e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_G,    0xfc0e81a0,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_G,   0xfc0e81a4,__READ_WRITE);
__IO_REG16(    PORTIR_G,     0xfc0e81a6,__READ      );
__IO_REG8_BIT( PINDATA0_G,   0xfc0e81a8,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_G,   0xfc0e81a9,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_G,   0xfc0e81aa,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_G,   0xfc0e81ab,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_G,   0xfc0e81ac,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_G,   0xfc0e81ad,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_G,   0xfc0e81ae,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_G,   0xfc0e81af,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_G,   0xfc0e81b0,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_G,   0xfc0e81b1,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_G,  0xfc0e81b2,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_G,  0xfc0e81b3,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_G,  0xfc0e81b4,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_G,  0xfc0e81b5,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_G,  0xfc0e81b6,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_G,  0xfc0e81b7,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT H
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_H,    0xfc0e81c0,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_H,    0xfc0e81c2,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_H,    0xfc0e81c4,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_H,    0xfc0e81c6,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_H,    0xfc0e81c8,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_H,    0xfc0e81ca,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_H,    0xfc0e81cc,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_H,    0xfc0e81ce,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_H,    0xfc0e81d0,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_H,    0xfc0e81d2,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_H,   0xfc0e81d4,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_H,   0xfc0e81d6,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_H,   0xfc0e81d8,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_H,   0xfc0e81da,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_H,   0xfc0e81dc,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_H,   0xfc0e81de,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_H,    0xfc0e81e0,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_H,   0xfc0e81e4,__READ_WRITE);
__IO_REG16(    PORTIR_H,     0xfc0e81e6,__READ      );
__IO_REG8_BIT( PINDATA0_H,   0xfc0e81e8,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_H,   0xfc0e81e9,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_H,   0xfc0e81ea,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_H,   0xfc0e81eb,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_H,   0xfc0e81ec,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_H,   0xfc0e81ed,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_H,   0xfc0e81ee,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_H,   0xfc0e81ef,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_H,   0xfc0e81f0,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_H,   0xfc0e81f1,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_H,  0xfc0e81f2,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_H,  0xfc0e81f3,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_H,  0xfc0e81f4,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_H,  0xfc0e81f5,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_H,  0xfc0e81f6,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_H,  0xfc0e81f7,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** PIM PORT I  - AVAILABLE ONLY ON L38Y DEVICES
 **
 ***************************************************************************/
__IO_REG16_BIT(CONFIG0_I,    0xfc0e8200,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG1_I,    0xfc0e8202,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG2_I,    0xfc0e8204,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG3_I,    0xfc0e8206,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG4_I,    0xfc0e8208,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG5_I,    0xfc0e820a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG6_I,    0xfc0e820c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG7_I,    0xfc0e820e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG8_I,    0xfc0e8210,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG9_I,    0xfc0e8212,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG10_I,   0xfc0e8214,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG11_I,   0xfc0e8216,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG12_I,   0xfc0e8218,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG13_I,   0xfc0e821a,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG14_I,   0xfc0e821c,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(CONFIG15_I,   0xfc0e821e,__READ_WRITE,__confignx_bits);
__IO_REG16_BIT(PORTIFR_I,    0xfc0e8220,__READ      ,__portifrx_bits);
__IO_REG16(    PORTDATA_I,   0xfc0e8224,__READ_WRITE);
__IO_REG16(    PORTIR_I,     0xfc0e8226,__READ      );
__IO_REG8_BIT( PINDATA0_I,   0xfc0e8228,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA1_I,   0xfc0e8229,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA2_I,   0xfc0e822a,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA3_I,   0xfc0e822b,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA4_I,   0xfc0e822c,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA5_I,   0xfc0e822d,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA6_I,   0xfc0e822e,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA7_I,   0xfc0e822f,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA8_I,   0xfc0e8230,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA9_I,   0xfc0e8231,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA10_I,  0xfc0e8232,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA11_I,  0xfc0e8233,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA12_I,  0xfc0e8234,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA13_I,  0xfc0e8235,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA14_I,  0xfc0e8236,__READ_WRITE,__pindatanx_bits);
__IO_REG8_BIT( PINDATA15_I,  0xfc0e8237,__READ_WRITE,__pindatanx_bits);

/***************************************************************************
 **
 ** CFM
 **
 ***************************************************************************/
__IO_REG16_BIT(CFMMCR,       0xfc0f0000,__READ_WRITE,__cfmmcr_bits);
__IO_REG8_BIT( CFMCLKD,      0xfc0f0002,__READ_WRITE,__cfmclkd_bits);
__IO_REG32_BIT(CFMSEC,       0xfc0f0008,__READ      ,__cfmsec_bits);
__IO_REG32_BIT(CFMPROT,      0xfc0f0010,__READ_WRITE,__cfmprot_bits);
__IO_REG32_BIT(CFMSACC,      0xfc0f0014,__READ_WRITE,__cfmsacc_bits);
__IO_REG32_BIT(CFMDACC,      0xfc0f0018,__READ_WRITE,__cfmdacc_bits);
__IO_REG8_BIT( CFMUSTAT,     0xfc0f0020,__READ_WRITE,__cfmustat_bits);
__IO_REG8_BIT( CFMCMD,       0xfc0f0024,__READ_WRITE,__cfmcmd_bits);
__IO_REG32(    CFMDATA0,     0xfc0f0030,__READ      );
__IO_REG32(    CFMDATA1,     0xfc0f0038,__READ      );
__IO_REG16(    CFMDISU,      0xfc0f0042,__READ      );
__IO_REG8_BIT( CFMDFPROT,    0xfc0f0044,__READ_WRITE,__cfmdfprot_bits);
__IO_REG8_BIT( CFMDFSACC,    0xfc0f0045,__READ_WRITE,__cfmdfsacc_bits);
__IO_REG8_BIT( CFMDFDACC,    0xfc0f0046,__READ_WRITE,__cfmdfdacc_bits);
__IO_REG16_BIT(CFMCLKSEL,    0xfc0f004a,__READ      ,__cfmclksel_bits);


/***************************************************************************
 **  Assembler-specific declarations
 ***************************************************************************/
#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **   MAC7100 INTERRUPT VALUES
 **
***************************************************************************/


/***************************************************************************
 **  Interrupt vector table
 ***************************************************************************/
#define RESETV  0x00  /* Reset                           */
#define UNDEFV  0x04  /* Undefined instruction           */
#define SWIV    0x08  /* Software interrupt              */
#define PABORTV 0x0c  /* Prefetch abort                  */
#define DABORTV 0x10  /* Data abort                      */
#define IRQV    0x18  /* Normal interrupt                */
#define FIQV    0x1c  /* Fast interrupt                  */

/***************************************************************************
 **  INTC Interrupt sources
 ***************************************************************************/
#define INTC_eDMA0 	     0
#define INTC_eDMA1 	     1
#define INTC_eDMA2 	     2
#define INTC_eDMA3 	     3
#define INTC_eDMA4 	     4
#define INTC_eDMA5 	     5
#define INTC_eDMA6 	     6
#define INTC_eDMA7 	     7
#define INTC_eDMA8 	     8
#define INTC_eDMA9 	     9
#define INTC_eDMA10	    10
#define INTC_eDMA11	    11
#define INTC_eDMA12	    12
#define INTC_eDMA13	    13
#define INTC_eDMA14	    14
#define INTC_eDMA15	    15
#define INTC_eDMA_Error     16
#define INTC_MCM_SWT        17
#define INTC_CRG  	    18
#define INTC_PIT1 	    19
#define INTC_PIT2 	    20
#define INTC_PIT3 	    21
#define INTC_PIT4_RTI       22
#define INTC_VREG           23
#define INTC_CAN_A_MB       24
#define INTC_CAN_A_MB14     25
#define INTC_CAN_A_Err_WU   26
#define INTC_CAN_B_MB       27
#define INTC_CAN_B_MB14     28
#define INTC_CAN_B_Err_WU2  29
#define INTC_CAN_C_MB       30
#define INTC_CAN_C_MB14     31
#define INTC_CAN_C_Err_WU2  32
#define INTC_CAN_D_MB       33
#define INTC_CAN_D_MB14     34
#define INTC_CAN_D_Err_WU2  35
#define INTC_I2C            36
#define INTC_DSPI_A         37
#define INTC_DSPI_B         38
#define INTC_eSCI_A         39
#define INTC_eSCI_B         40
#define INTC_eSCI_C         41
#define INTC_eSCI_D         42
#define INTC_eMIOS0         43
#define INTC_eMIOS1         44
#define INTC_eMIOS2         45
#define INTC_eMIOS3         46
#define INTC_eMIOS4         47
#define INTC_eMIOS5         48
#define INTC_eMIOS6         49
#define INTC_eMIOS7         50
#define INTC_eMIOS8         51
#define INTC_eMIOS9         52
#define INTC_eMIOS10        53
#define INTC_eMIOS11        54
#define INTC_eMIOS12        55
#define INTC_eMIOS13        56
#define INTC_eMIOS14        57
#define INTC_eMIOS15        58
#define INTC_ATD_A_B        59
#define INTC_CFM            60
#define INTC_PIM            61
#define INTC_IRQ            62
#define INTC_XIRQ           63

#endif    /* __IOMAC7100_H */
