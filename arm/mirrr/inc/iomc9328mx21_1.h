/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Motorola MC9328MX21 Dragonball
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2003
 **
 **    $Revision: 1.5 $
 **
 ***************************************************************************/

#ifndef __MC9328MX21_H
#define __MC9328MX21_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    MC9328MX21 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#if __LITTLE_ENDIAN__ == 0
#error This file should only be compiled in little endian mode
#endif

/* -------------------------------------------------------------------------*/
/*               AITC registers                                             */
/* -------------------------------------------------------------------------*/
typedef struct {        /* Interrupt Control Register (0x10040000) Reset (0x00000000)                   */
__REG32          : 2;     // Bits 0-1     - Reserved
__REG32 POINTER  :10;     // Bits 2-11    - Interrupt Vector Table Pointer
__REG32          : 4;     // Bits 12-15   - Reserved
__REG32 MD       : 1;     // Bit 16       - Interrupt Vector Table Mode
__REG32          : 2;     // Bits 17-18   - Reserved
__REG32 FIAD     : 1;     // Bit 19       - Fast Interrupt Arbiter Disable
__REG32 NIAD     : 1;     // Bit 20       - Normal Interrupt Arbiter Disable
__REG32 FIDIS    : 1;     // Bit 21       - Fast Interrupt Disable
__REG32 NIDIS    : 1;     // Bit 22       - Normal Interrupt Disable
__REG32          : 1;     // Bit 23       - Reserved
__REG32 ABFEN    : 1;     // Bit 24       - ABFLAG Sticky Enable
__REG32 ABFLAG   : 1;     // Bit 25       - Core Arbitration Prioritization Risen Flag
__REG32          : 6;     // Bits 26-31   - Reserved
} __INTCNTL_bits;

typedef struct {        /* Normal Interrupt Mask Register (0x10040004) Reset (0x0000001F)                       */
__REG32 NIMASK  : 5;     // Bits 0-4     - Normal Interrupt Mask (0 = Disable priority level 0 ints, 1 = disable priority 1 and lower... 16+ = disable all interrupts)
__REG32         :27;     // Bits 5-31    - Reserved
} __NIMASK_bits;

typedef struct {        /* Interrupt Enable Number Register (0x10040008) Reset (0x00000000)                     */
__REG32 ENNUM  : 6;     // Bits 0-5     - Interrupt Enable Number - Enables/Disables the interrupt source associated with this value.
__REG32        :26;     // Bits 6-31    - Reserved
} __INTENNUM_bits;

typedef struct {        /* Interrupt Disable Number Register (0x1004000C) Reset (0x00000000)                    */
__REG32 DISNUM  : 6;     // Bits 0-5     - Interrupt Disable Number - Enables/Disables the interrupt source associated with this value.
__REG32         :26;     // Bits 6-31    - Reserved
} __INTDISNUM_bits;

typedef struct {        /* Interrupt Enable Register High (0x10040010) Reset (0x00000000)                       */
__REG32 INTENABLE32  : 1;     // Bit  0           - Interrupt Enable
__REG32 INTENABLE33  : 1;     // Bit  1           - Interrupt Enable
__REG32 INTENABLE34  : 1;     // Bit  2           - Interrupt Enable
__REG32 INTENABLE35  : 1;     // Bit  3           - Interrupt Enable
__REG32 INTENABLE36  : 1;     // Bit  4           - Interrupt Enable
__REG32 INTENABLE37  : 1;     // Bit  5           - Interrupt Enable
__REG32 INTENABLE38  : 1;     // Bit  6           - Interrupt Enable
__REG32 INTENABLE39  : 1;     // Bit  7           - Interrupt Enable
__REG32 INTENABLE40  : 1;     // Bit  8           - Interrupt Enable
__REG32 INTENABLE41  : 1;     // Bit  9           - Interrupt Enable
__REG32 INTENABLE42  : 1;     // Bit  10          - Interrupt Enable
__REG32 INTENABLE43  : 1;     // Bit  11          - Interrupt Enable
__REG32 INTENABLE44  : 1;     // Bit  12          - Interrupt Enable
__REG32 INTENABLE45  : 1;     // Bit  13          - Interrupt Enable
__REG32 INTENABLE46  : 1;     // Bit  14          - Interrupt Enable
__REG32 INTENABLE47  : 1;     // Bit  15          - Interrupt Enable
__REG32 INTENABLE48  : 1;     // Bit  16          - Interrupt Enable
__REG32 INTENABLE49  : 1;     // Bit  17          - Interrupt Enable
__REG32 INTENABLE50  : 1;     // Bit  18          - Interrupt Enable
__REG32 INTENABLE51  : 1;     // Bit  19          - Interrupt Enable
__REG32 INTENABLE52  : 1;     // Bit  20          - Interrupt Enable
__REG32 INTENABLE53  : 1;     // Bit  21          - Interrupt Enable
__REG32 INTENABLE54  : 1;     // Bit  22          - Interrupt Enable
__REG32 INTENABLE55  : 1;     // Bit  23          - Interrupt Enable
__REG32 INTENABLE56  : 1;     // Bit  24          - Interrupt Enable
__REG32 INTENABLE57  : 1;     // Bit  25          - Interrupt Enable
__REG32 INTENABLE58  : 1;     // Bit  26          - Interrupt Enable
__REG32 INTENABLE59  : 1;     // Bit  27          - Interrupt Enable
__REG32 INTENABLE60  : 1;     // Bit  28          - Interrupt Enable
__REG32 INTENABLE61  : 1;     // Bit  29          - Interrupt Enable
__REG32 INTENABLE62  : 1;     // Bit  30          - Interrupt Enable
__REG32 INTENABLE63  : 1;     // Bit  31          - Interrupt Enable
} __INTENABLEH_bits;

typedef struct {        /* Interrupt Enable Register Low (0x10040014) Reset (0x00000000)                        */
__REG32 INTENABLE0   : 1;     // Bit  0           - Interrupt Enable
__REG32 INTENABLE1   : 1;     // Bit  1           - Interrupt Enable
__REG32 INTENABLE2   : 1;     // Bit  2           - Interrupt Enable
__REG32 INTENABLE3   : 1;     // Bit  3           - Interrupt Enable
__REG32 INTENABLE4   : 1;     // Bit  4           - Interrupt Enable
__REG32 INTENABLE5   : 1;     // Bit  5           - Interrupt Enable
__REG32 INTENABLE6   : 1;     // Bit  6           - Interrupt Enable
__REG32 INTENABLE7   : 1;     // Bit  7           - Interrupt Enable
__REG32 INTENABLE8   : 1;     // Bit  8           - Interrupt Enable
__REG32 INTENABLE9   : 1;     // Bit  9           - Interrupt Enable
__REG32 INTENABLE10  : 1;     // Bit  10          - Interrupt Enable
__REG32 INTENABLE11  : 1;     // Bit  11          - Interrupt Enable
__REG32 INTENABLE12  : 1;     // Bit  12          - Interrupt Enable
__REG32 INTENABLE13  : 1;     // Bit  13          - Interrupt Enable
__REG32 INTENABLE14  : 1;     // Bit  14          - Interrupt Enable
__REG32 INTENABLE15  : 1;     // Bit  15          - Interrupt Enable
__REG32 INTENABLE16  : 1;     // Bit  16          - Interrupt Enable
__REG32 INTENABLE17  : 1;     // Bit  17          - Interrupt Enable
__REG32 INTENABLE18  : 1;     // Bit  18          - Interrupt Enable
__REG32 INTENABLE19  : 1;     // Bit  19          - Interrupt Enable
__REG32 INTENABLE20  : 1;     // Bit  20          - Interrupt Enable
__REG32 INTENABLE21  : 1;     // Bit  21          - Interrupt Enable
__REG32 INTENABLE22  : 1;     // Bit  22          - Interrupt Enable
__REG32 INTENABLE23  : 1;     // Bit  23          - Interrupt Enable
__REG32 INTENABLE24  : 1;     // Bit  24          - Interrupt Enable
__REG32 INTENABLE25  : 1;     // Bit  25          - Interrupt Enable
__REG32 INTENABLE26  : 1;     // Bit  26          - Interrupt Enable
__REG32 INTENABLE27  : 1;     // Bit  27          - Interrupt Enable
__REG32 INTENABLE28  : 1;     // Bit  28          - Interrupt Enable
__REG32 INTENABLE29  : 1;     // Bit  29          - Interrupt Enable
__REG32 INTENABLE30  : 1;     // Bit  30          - Interrupt Enable
__REG32 INTENABLE31  : 1;     // Bit  31          - Interrupt Enable
} __INTENABLEL_bits;

typedef struct {        /* Interrupt Type Register High (0x10040018) Reset (0x00000000)                 */
__REG32 INTTYPE32  : 1;     // Bit  0         - Interrupt Enable
__REG32 INTTYPE33  : 1;     // Bit  1         - Interrupt Enable
__REG32 INTTYPE34  : 1;     // Bit  2         - Interrupt Enable
__REG32 INTTYPE35  : 1;     // Bit  3         - Interrupt Enable
__REG32 INTTYPE36  : 1;     // Bit  4         - Interrupt Enable
__REG32 INTTYPE37  : 1;     // Bit  5         - Interrupt Enable
__REG32 INTTYPE38  : 1;     // Bit  6         - Interrupt Enable
__REG32 INTTYPE39  : 1;     // Bit  7         - Interrupt Enable
__REG32 INTTYPE40  : 1;     // Bit  8         - Interrupt Enable
__REG32 INTTYPE41  : 1;     // Bit  9         - Interrupt Enable
__REG32 INTTYPE42  : 1;     // Bit  10        - Interrupt Enable
__REG32 INTTYPE43  : 1;     // Bit  11        - Interrupt Enable
__REG32 INTTYPE44  : 1;     // Bit  12        - Interrupt Enable
__REG32 INTTYPE45  : 1;     // Bit  13        - Interrupt Enable
__REG32 INTTYPE46  : 1;     // Bit  14        - Interrupt Enable
__REG32 INTTYPE47  : 1;     // Bit  15        - Interrupt Enable
__REG32 INTTYPE48  : 1;     // Bit  16        - Interrupt Enable
__REG32 INTTYPE49  : 1;     // Bit  17        - Interrupt Enable
__REG32 INTTYPE50  : 1;     // Bit  18        - Interrupt Enable
__REG32 INTTYPE51  : 1;     // Bit  19        - Interrupt Enable
__REG32 INTTYPE52  : 1;     // Bit  20        - Interrupt Enable
__REG32 INTTYPE53  : 1;     // Bit  21        - Interrupt Enable
__REG32 INTTYPE54  : 1;     // Bit  22        - Interrupt Enable
__REG32 INTTYPE55  : 1;     // Bit  23        - Interrupt Enable
__REG32 INTTYPE56  : 1;     // Bit  24        - Interrupt Enable
__REG32 INTTYPE57  : 1;     // Bit  25        - Interrupt Enable
__REG32 INTTYPE58  : 1;     // Bit  26        - Interrupt Enable
__REG32 INTTYPE59  : 1;     // Bit  27        - Interrupt Enable
__REG32 INTTYPE60  : 1;     // Bit  28        - Interrupt Enable
__REG32 INTTYPE61  : 1;     // Bit  29        - Interrupt Enable
__REG32 INTTYPE62  : 1;     // Bit  30        - Interrupt Enable
__REG32 INTTYPE63  : 1;     // Bit  31        - Interrupt Enable
} __INTTYPEH_bits;

typedef struct {        /* Interrupt Enable Register Low (0x1004001C) Reset (0x00000000)                        */
__REG32 INTTYPE0   : 1;     // Bit  0         - Interrupt Enable
__REG32 INTTYPE1   : 1;     // Bit  1         - Interrupt Enable
__REG32 INTTYPE2   : 1;     // Bit  2         - Interrupt Enable
__REG32 INTTYPE3   : 1;     // Bit  3         - Interrupt Enable
__REG32 INTTYPE4   : 1;     // Bit  4         - Interrupt Enable
__REG32 INTTYPE5   : 1;     // Bit  5         - Interrupt Enable
__REG32 INTTYPE6   : 1;     // Bit  6         - Interrupt Enable
__REG32 INTTYPE7   : 1;     // Bit  7         - Interrupt Enable
__REG32 INTTYPE8   : 1;     // Bit  8         - Interrupt Enable
__REG32 INTTYPE9   : 1;     // Bit  9         - Interrupt Enable
__REG32 INTTYPE10  : 1;     // Bit  10        - Interrupt Enable
__REG32 INTTYPE11  : 1;     // Bit  11        - Interrupt Enable
__REG32 INTTYPE12  : 1;     // Bit  12        - Interrupt Enable
__REG32 INTTYPE13  : 1;     // Bit  13        - Interrupt Enable
__REG32 INTTYPE14  : 1;     // Bit  14        - Interrupt Enable
__REG32 INTTYPE15  : 1;     // Bit  15        - Interrupt Enable
__REG32 INTTYPE16  : 1;     // Bit  16        - Interrupt Enable
__REG32 INTTYPE17  : 1;     // Bit  17        - Interrupt Enable
__REG32 INTTYPE18  : 1;     // Bit  18        - Interrupt Enable
__REG32 INTTYPE19  : 1;     // Bit  19        - Interrupt Enable
__REG32 INTTYPE20  : 1;     // Bit  20        - Interrupt Enable
__REG32 INTTYPE21  : 1;     // Bit  21        - Interrupt Enable
__REG32 INTTYPE22  : 1;     // Bit  22        - Interrupt Enable
__REG32 INTTYPE23  : 1;     // Bit  23        - Interrupt Enable
__REG32 INTTYPE24  : 1;     // Bit  24        - Interrupt Enable
__REG32 INTTYPE25  : 1;     // Bit  25        - Interrupt Enable
__REG32 INTTYPE26  : 1;     // Bit  26        - Interrupt Enable
__REG32 INTTYPE27  : 1;     // Bit  27        - Interrupt Enable
__REG32 INTTYPE28  : 1;     // Bit  28        - Interrupt Enable
__REG32 INTTYPE29  : 1;     // Bit  29        - Interrupt Enable
__REG32 INTTYPE30  : 1;     // Bit  30        - Interrupt Enable
__REG32 INTTYPE31  : 1;     // Bit  31        - Interrupt Enable
} __INTTYPEL_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 7 (0x10040020) Reset (0x00000000)                   */
__REG32 NIPR56  : 4;     // Bits 0-3     - Normal Interrupt Priority Level
__REG32 NIPR57  : 4;     // Bits 4-7     - Normal Interrupt Priority Level
__REG32 NIPR58  : 4;     // Bits 8-11    - Normal Interrupt Priority Level
__REG32 NIPR59  : 4;     // Bits 12-15   - Normal Interrupt Priority Level
__REG32 NIPR60  : 4;     // Bits 16-19   - Normal Interrupt Priority Level
__REG32 NIPR61  : 4;     // Bits 20-23   - Normal Interrupt Priority Level
__REG32 NIPR62  : 4;     // Bits 24-27   - Normal Interrupt Priority Level
__REG32 NIPR63  : 4;     // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY7_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 6 (0x10040024) Reset (0x00000000)                   */
__REG32 NIPR48  : 4;     // Bits 0-3     - Normal Interrupt Priority Level
__REG32 NIPR49  : 4;     // Bits 4-7     - Normal Interrupt Priority Level
__REG32 NIPR50  : 4;     // Bits 8-11    - Normal Interrupt Priority Level
__REG32 NIPR51  : 4;     // Bits 12-15   - Normal Interrupt Priority Level
__REG32 NIPR52  : 4;     // Bits 16-19   - Normal Interrupt Priority Level
__REG32 NIPR53  : 4;     // Bits 20-23   - Normal Interrupt Priority Level
__REG32 NIPR54  : 4;     // Bits 24-27   - Normal Interrupt Priority Level
__REG32 NIPR55  : 4;     // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY6_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 5 (0x10040028) Reset (0x00000000)                   */
__REG32 NIPR40  : 4;     // Bits 0-3     - Normal Interrupt Priority Level
__REG32 NIPR41  : 4;     // Bits 4-7     - Normal Interrupt Priority Level
__REG32 NIPR42  : 4;     // Bits 8-11    - Normal Interrupt Priority Level
__REG32 NIPR43  : 4;     // Bits 12-15   - Normal Interrupt Priority Level
__REG32 NIPR44  : 4;     // Bits 16-19   - Normal Interrupt Priority Level
__REG32 NIPR45  : 4;     // Bits 20-23   - Normal Interrupt Priority Level
__REG32 NIPR46  : 4;     // Bits 24-27   - Normal Interrupt Priority Level
__REG32 NIPR47  : 4;     // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY5_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 4 (0x1004002C) Reset (0x00000000)                   */
__REG32 NIPR32  : 4;     // Bits 0-3     - Normal Interrupt Priority Level
__REG32 NIPR33  : 4;     // Bits 4-7     - Normal Interrupt Priority Level
__REG32 NIPR34  : 4;     // Bits 8-11    - Normal Interrupt Priority Level
__REG32 NIPR35  : 4;     // Bits 12-15   - Normal Interrupt Priority Level
__REG32 NIPR36  : 4;     // Bits 16-19   - Normal Interrupt Priority Level
__REG32 NIPR37  : 4;     // Bits 20-23   - Normal Interrupt Priority Level
__REG32 NIPR38  : 4;     // Bits 24-27   - Normal Interrupt Priority Level
__REG32 NIPR39  : 4;     // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY4_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 3 (0x10040030) Reset (0x00000000)                   */
__REG32 NIPR24  : 4;     // Bits 0-3     - Normal Interrupt Priority Level
__REG32 NIPR25  : 4;     // Bits 4-7     - Normal Interrupt Priority Level
__REG32 NIPR26  : 4;     // Bits 8-11    - Normal Interrupt Priority Level
__REG32 NIPR27  : 4;     // Bits 12-15   - Normal Interrupt Priority Level
__REG32 NIPR28  : 4;     // Bits 16-19   - Normal Interrupt Priority Level
__REG32 NIPR29  : 4;     // Bits 20-23   - Normal Interrupt Priority Level
__REG32 NIPR30  : 4;     // Bits 24-27   - Normal Interrupt Priority Level
__REG32 NIPR31  : 4;     // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY3_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 2 (0x10040034) Reset (0x00000000)                   */
__REG32 NIPR16  : 4;     // Bits 0-3     - Normal Interrupt Priority Level
__REG32 NIPR17  : 4;     // Bits 4-7     - Normal Interrupt Priority Level
__REG32 NIPR18  : 4;     // Bits 8-11    - Normal Interrupt Priority Level
__REG32 NIPR19  : 4;     // Bits 12-15   - Normal Interrupt Priority Level
__REG32 NIPR20  : 4;     // Bits 16-19   - Normal Interrupt Priority Level
__REG32 NIPR21  : 4;     // Bits 20-23   - Normal Interrupt Priority Level
__REG32 NIPR22  : 4;     // Bits 24-27   - Normal Interrupt Priority Level
__REG32 NIPR23  : 4;     // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY2_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 1 (0x10040038) Reset (0x00000000)                   */
__REG32 NIPR8   : 4;     // Bits 0-3     - Normal Interrupt Priority Level
__REG32 NIPR9   : 4;     // Bits 4-7     - Normal Interrupt Priority Level
__REG32 NIPR10  : 4;     // Bits 8-11    - Normal Interrupt Priority Level
__REG32 NIPR11  : 4;     // Bits 12-15   - Normal Interrupt Priority Level
__REG32 NIPR12  : 4;     // Bits 16-19   - Normal Interrupt Priority Level
__REG32 NIPR13  : 4;     // Bits 20-23   - Normal Interrupt Priority Level
__REG32 NIPR14  : 4;     // Bits 24-27   - Normal Interrupt Priority Level
__REG32 NIPR15  : 4;     // Bits 28-31   - Normal Interrupt Priority Level
} __NIPRIORITY1_bits;

typedef struct {        /* Normal Interrupt Priority Level Register 0 (0x1004003C) Reset (0x00000000)                   */
__REG32 NIPR0  : 4;     // Bits 0  - 3  - Normal Interrupt Priority Level
__REG32 NIPR1  : 4;     // Bits 4  - 7  - Normal Interrupt Priority Level
__REG32 NIPR2  : 4;     // Bits 8  - 11 - Normal Interrupt Priority Level
__REG32 NIPR3  : 4;     // Bits 12 - 15 - Normal Interrupt Priority Level
__REG32 NIPR4  : 4;     // Bits 16 - 19 - Normal Interrupt Priority Level
__REG32 NIPR5  : 4;     // Bits 20 - 23 - Normal Interrupt Priority Level
__REG32 NIPR6  : 4;     // Bits 24 - 27 - Normal Interrupt Priority Level
__REG32 NIPR7  : 4;     // Bits 28 - 31 - Normal Interrupt Priority Level
} __NIPRIORITY0_bits;

typedef struct {        /* Normal Interrupt Vector and Status Register (0x10040040) Reset (0xFFFFFFFF)  */
__REG32 NIPRILVL  :16;     // Bits 0  - 15 - Normal Interrupt Priority Level - Indicates the priority level of the highest priority normal interrupt.
__REG32 NIVECTOR  :16;     // Bits 16 - 31 - Normal Interrupt Vector - Indicates vector index for the highest pending normal interrupt.
} __NIVECSR_bits;

typedef struct {        /* Interrupt Source Register High (0x10040048) Reset (0x00000000)       */
__REG32 INTIN32  : 1;     // Bit  0       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN33  : 1;     // Bit  1       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN34  : 1;     // Bit  2       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN35  : 1;     // Bit  3       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN36  : 1;     // Bit  4       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN37  : 1;     // Bit  5       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN38  : 1;     // Bit  6       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN39  : 1;     // Bit  7       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN40  : 1;     // Bit  8       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN41  : 1;     // Bit  9       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN42  : 1;     // Bit  10      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN43  : 1;     // Bit  11      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN44  : 1;     // Bit  12      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN45  : 1;     // Bit  13      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN46  : 1;     // Bit  14      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN47  : 1;     // Bit  15      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN48  : 1;     // Bit  16      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN49  : 1;     // Bit  17      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN50  : 1;     // Bit  18      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN51  : 1;     // Bit  19      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN52  : 1;     // Bit  20      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN53  : 1;     // Bit  21      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN54  : 1;     // Bit  22      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN55  : 1;     // Bit  23      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN56  : 1;     // Bit  24      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN57  : 1;     // Bit  25      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN58  : 1;     // Bit  26      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN59  : 1;     // Bit  27      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN60  : 1;     // Bit  28      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN61  : 1;     // Bit  29      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN62  : 1;     // Bit  30      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN63  : 1;     // Bit  31      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
} __INTSRCH_bits;

typedef struct {        /* Interrupt Source Register Low (0x1004004C) Reset (0x00000000)        */
__REG32 INTIN0   : 1;     // Bit  0       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN1   : 1;     // Bit  1       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN2   : 1;     // Bit  2       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN3   : 1;     // Bit  3       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN4   : 1;     // Bit  4       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN5   : 1;     // Bit  5       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN6   : 1;     // Bit  6       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN7   : 1;     // Bit  7       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN8   : 1;     // Bit  8       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN9   : 1;     // Bit  9       - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN10  : 1;     // Bit  10      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN11  : 1;     // Bit  11      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN12  : 1;     // Bit  12      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN13  : 1;     // Bit  13      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN14  : 1;     // Bit  14      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN15  : 1;     // Bit  15      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN16  : 1;     // Bit  16      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN17  : 1;     // Bit  17      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN18  : 1;     // Bit  18      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN19  : 1;     // Bit  19      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN20  : 1;     // Bit  20      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN21  : 1;     // Bit  21      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN22  : 1;     // Bit  22      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN23  : 1;     // Bit  23      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN24  : 1;     // Bit  24      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN25  : 1;     // Bit  25      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN26  : 1;     // Bit  26      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN27  : 1;     // Bit  27      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN28  : 1;     // Bit  28      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN29  : 1;     // Bit  29      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN30  : 1;     // Bit  30      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
__REG32 INTIN31  : 1;     // Bit  31      - Interrupt Source (0 = Interrupt source negated, 1 = Interrupt source asserted)
} __INTSRCL_bits;

typedef struct {        /* Interrupt Force Register High (0x10040050) Reset (0x00000000)        */
__REG32 FORCE32  : 1;     // Bit  0       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE33  : 1;     // Bit  1       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE34  : 1;     // Bit  2       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE35  : 1;     // Bit  3       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE36  : 1;     // Bit  4       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE37  : 1;     // Bit  5       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE38  : 1;     // Bit  6       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE39  : 1;     // Bit  7       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE40  : 1;     // Bit  8       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE41  : 1;     // Bit  9       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE42  : 1;     // Bit  10      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE43  : 1;     // Bit  11      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE44  : 1;     // Bit  12      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE45  : 1;     // Bit  13      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE46  : 1;     // Bit  14      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE47  : 1;     // Bit  15      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE48  : 1;     // Bit  16      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE49  : 1;     // Bit  17      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE50  : 1;     // Bit  18      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE51  : 1;     // Bit  19      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE52  : 1;     // Bit  20      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE53  : 1;     // Bit  21      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE54  : 1;     // Bit  22      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE55  : 1;     // Bit  23      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE56  : 1;     // Bit  24      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE57  : 1;     // Bit  25      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE58  : 1;     // Bit  26      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE59  : 1;     // Bit  27      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE60  : 1;     // Bit  28      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE61  : 1;     // Bit  29      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE62  : 1;     // Bit  30      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE63  : 1;     // Bit  31      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
} __INTFRCH_bits;

typedef struct {        /* Interrupt Force Register Low (0x10040054) Reset (0x00000000) */
__REG32 FORCE0   : 1;     // Bit  0       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE1   : 1;     // Bit  1       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE2   : 1;     // Bit  2       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE3   : 1;     // Bit  3       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE4   : 1;     // Bit  4       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE5   : 1;     // Bit  5       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE6   : 1;     // Bit  6       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE7   : 1;     // Bit  7       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE8   : 1;     // Bit  8       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE9   : 1;     // Bit  9       - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE10  : 1;     // Bit  10      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE11  : 1;     // Bit  11      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE12  : 1;     // Bit  12      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE13  : 1;     // Bit  13      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE14  : 1;     // Bit  14      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE15  : 1;     // Bit  15      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE16  : 1;     // Bit  16      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE17  : 1;     // Bit  17      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE18  : 1;     // Bit  18      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE19  : 1;     // Bit  19      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE20  : 1;     // Bit  20      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE21  : 1;     // Bit  21      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE22  : 1;     // Bit  22      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE23  : 1;     // Bit  23      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE24  : 1;     // Bit  24      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE25  : 1;     // Bit  25      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE26  : 1;     // Bit  26      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE27  : 1;     // Bit  27      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE28  : 1;     // Bit  28      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE29  : 1;     // Bit  29      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE30  : 1;     // Bit  30      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
__REG32 FORCE31  : 1;     // Bit  31      - Interrupt Source Force Request - Writing a 1 Forces a request for the corresponding interrupt source.
} __INTFRCL_bits;

typedef struct {        /* Normal Interrupt Pending Register High (0x10040058) Reset (0x00000000)       */
__REG32 NIPEND32  : 1;     // Bit  0       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND33  : 1;     // Bit  1       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND34  : 1;     // Bit  2       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND35  : 1;     // Bit  3       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND36  : 1;     // Bit  4       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND37  : 1;     // Bit  5       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND38  : 1;     // Bit  6       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND39  : 1;     // Bit  7       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND40  : 1;     // Bit  8       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND41  : 1;     // Bit  9       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND42  : 1;     // Bit  10      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND43  : 1;     // Bit  11      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND44  : 1;     // Bit  12      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND45  : 1;     // Bit  13      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND46  : 1;     // Bit  14      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND47  : 1;     // Bit  15      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND48  : 1;     // Bit  16      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND49  : 1;     // Bit  17      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND50  : 1;     // Bit  18      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND51  : 1;     // Bit  19      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND52  : 1;     // Bit  20      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND53  : 1;     // Bit  21      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND54  : 1;     // Bit  22      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND55  : 1;     // Bit  23      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND56  : 1;     // Bit  24      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND57  : 1;     // Bit  25      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND58  : 1;     // Bit  26      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND59  : 1;     // Bit  27      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND60  : 1;     // Bit  28      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND61  : 1;     // Bit  29      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND62  : 1;     // Bit  30      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND63  : 1;     // Bit  31      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
} __NIPNDH_bits;

typedef struct {        /* Normal Interrupt Pending Register Low (0x1004005C) Reset (0x00000000)        */
__REG32 NIPEND0   : 1;     // Bit  0       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND1   : 1;     // Bit  1       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND2   : 1;     // Bit  2       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND3   : 1;     // Bit  3       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND4   : 1;     // Bit  4       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND5   : 1;     // Bit  5       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND6   : 1;     // Bit  6       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND7   : 1;     // Bit  7       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND8   : 1;     // Bit  8       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND9   : 1;     // Bit  9       - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND10  : 1;     // Bit  10      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND11  : 1;     // Bit  11      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND12  : 1;     // Bit  12      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND13  : 1;     // Bit  13      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND14  : 1;     // Bit  14      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND15  : 1;     // Bit  15      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND16  : 1;     // Bit  16      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND17  : 1;     // Bit  17      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND18  : 1;     // Bit  18      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND19  : 1;     // Bit  19      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND20  : 1;     // Bit  20      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND21  : 1;     // Bit  21      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND22  : 1;     // Bit  22      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND23  : 1;     // Bit  23      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND24  : 1;     // Bit  24      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND25  : 1;     // Bit  25      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND26  : 1;     // Bit  26      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND27  : 1;     // Bit  27      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND28  : 1;     // Bit  28      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND29  : 1;     // Bit  29      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND30  : 1;     // Bit  30      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
__REG32 NIPEND31  : 1;     // Bit  31      - Normal Interrupt Pending Bit - (0=No int pending, 1 = Normal Interrupt request pending)
} __NIPNDL_bits;

typedef struct {        /* Fast Interrupt Pending Register High (0x10040060) Reset (0x00000000) */
__REG32 FIPEND32  : 1;     // Bit  0       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND33  : 1;     // Bit  1       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND34  : 1;     // Bit  2       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND35  : 1;     // Bit  3       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND36  : 1;     // Bit  4       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND37  : 1;     // Bit  5       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND38  : 1;     // Bit  6       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND39  : 1;     // Bit  7       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND40  : 1;     // Bit  8       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND41  : 1;     // Bit  9       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND42  : 1;     // Bit  10      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND43  : 1;     // Bit  11      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND44  : 1;     // Bit  12      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND45  : 1;     // Bit  13      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND46  : 1;     // Bit  14      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND47  : 1;     // Bit  15      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND48  : 1;     // Bit  16      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND49  : 1;     // Bit  17      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND50  : 1;     // Bit  18      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND51  : 1;     // Bit  19      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND52  : 1;     // Bit  20      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND53  : 1;     // Bit  21      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND54  : 1;     // Bit  22      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND55  : 1;     // Bit  23      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND56  : 1;     // Bit  24      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND57  : 1;     // Bit  25      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND58  : 1;     // Bit  26      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND59  : 1;     // Bit  27      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND60  : 1;     // Bit  28      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND61  : 1;     // Bit  29      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND62  : 1;     // Bit  30      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND63  : 1;     // Bit  31      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
} __FIPNDH_bits;

typedef struct {        /* Fast Interrupt Pending Register Low (0x10040064) Reset (0x00000000)  */
__REG32 FIPEND0   : 1;     // Bit  0       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND1   : 1;     // Bit  1       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND2   : 1;     // Bit  2       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND3   : 1;     // Bit  3       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND4   : 1;     // Bit  4       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND5   : 1;     // Bit  5       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND6   : 1;     // Bit  6       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND7   : 1;     // Bit  7       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND8   : 1;     // Bit  8       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND9   : 1;     // Bit  9       - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND10  : 1;     // Bit  10      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND11  : 1;     // Bit  11      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND12  : 1;     // Bit  12      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND13  : 1;     // Bit  13      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND14  : 1;     // Bit  14      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND15  : 1;     // Bit  15      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND16  : 1;     // Bit  16      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND17  : 1;     // Bit  17      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND18  : 1;     // Bit  18      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND19  : 1;     // Bit  19      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND20  : 1;     // Bit  20      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND21  : 1;     // Bit  21      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND22  : 1;     // Bit  22      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND23  : 1;     // Bit  23      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND24  : 1;     // Bit  24      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND25  : 1;     // Bit  25      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND26  : 1;     // Bit  26      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND27  : 1;     // Bit  27      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND28  : 1;     // Bit  28      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND29  : 1;     // Bit  29      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND30  : 1;     // Bit  30      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
__REG32 FIPEND31  : 1;     // Bit  31      - Fast Interrupt Pending Bit - (0=No int pending, 1 = Fast Interrupt request pending)
} __FIPNDL_bits;

/* -------------------------------------------------------------------------*/
/*      ROMPATCH                                                            */
/* -------------------------------------------------------------------------*/
typedef struct {        /* ROMPATCH Control Register (0x100410F4) Reset (0x00000000)  */
__REG32 DATAFIX  :16;     // Bits 0  - 15 - Data Fix Enable
__REG32          :11;     // Bits 16 - 26 - Reserved
__REG32 RO       : 1;     // Bit  27      - ROMPATCH ROM-only Mode
__REG32          : 1;     // Bit  28      - Reserved
__REG32 DIS      : 1;     // Bit  29      - ROMPATCH Disable
__REG32          : 2;     // Bit  29 - 31 - Reserved
} __ROMPATCHCNTL_bits;

typedef struct {        /* ROMPATCH Enable Register High (0x100410F8) Reset (0x00000000) */
__REG32 ENABLE32  : 1;     // Bit  0       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE33  : 1;     // Bit  1       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE34  : 1;     // Bit  2       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE35  : 1;     // Bit  3       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE36  : 1;     // Bit  4       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE37  : 1;     // Bit  5       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE38  : 1;     // Bit  6       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE39  : 1;     // Bit  7       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE40  : 1;     // Bit  8       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE41  : 1;     // Bit  9       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE42  : 1;     // Bit  10      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE43  : 1;     // Bit  11      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE44  : 1;     // Bit  12      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE45  : 1;     // Bit  13      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE46  : 1;     // Bit  14      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE47  : 1;     // Bit  15      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE48  : 1;     // Bit  16      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE49  : 1;     // Bit  17      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE50  : 1;     // Bit  18      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE51  : 1;     // Bit  19      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE52  : 1;     // Bit  20      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE53  : 1;     // Bit  21      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE54  : 1;     // Bit  22      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE55  : 1;     // Bit  23      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE56  : 1;     // Bit  24      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE57  : 1;     // Bit  25      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE58  : 1;     // Bit  26      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE59  : 1;     // Bit  27      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE60  : 1;     // Bit  28      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE61  : 1;     // Bit  29      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE62  : 1;     // Bit  30      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE63  : 1;     // Bit  31      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
} __ROMPATCH_bits;

typedef struct {        /* ROMPATCH Enable Register Low (0x100410FC) Reset (0x00000000)  */
__REG32 ENABLE0   : 1;     // Bit  0       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE1   : 1;     // Bit  1       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE2   : 1;     // Bit  2       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE3   : 1;     // Bit  3       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE4   : 1;     // Bit  4       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE5   : 1;     // Bit  5       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE6   : 1;     // Bit  6       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE7   : 1;     // Bit  7       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE8   : 1;     // Bit  8       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE9   : 1;     // Bit  9       - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE10  : 1;     // Bit  10      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE11  : 1;     // Bit  11      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE12  : 1;     // Bit  12      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE13  : 1;     // Bit  13      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE14  : 1;     // Bit  14      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE15  : 1;     // Bit  15      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE16  : 1;     // Bit  16      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE17  : 1;     // Bit  17      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE18  : 1;     // Bit  18      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE19  : 1;     // Bit  19      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE20  : 1;     // Bit  20      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE21  : 1;     // Bit  21      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE22  : 1;     // Bit  22      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE23  : 1;     // Bit  23      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE24  : 1;     // Bit  24      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE25  : 1;     // Bit  25      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE26  : 1;     // Bit  26      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE27  : 1;     // Bit  27      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE28  : 1;     // Bit  28      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE29  : 1;     // Bit  29      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE30  : 1;     // Bit  30      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
__REG32 ENABLE31  : 1;     // Bit  31      - Enable Address Comparator (0 = Address comparator disabled, 1 = Address comparator enabled)
} __ROMPATCL_bits;

typedef struct {        /* ROMPATCHAn 0 <= n <= 3 Address Registers (0x10041100) - (0x1004110C) Reset (0x00000000)  */
__REG32        : 1;     // Bit  0       - Reserved
__REG32 ADDRX  :31;     // Bits 1 - 31  - Address Comparator Registers
} __ROMPATCHA0_3_bits;

typedef struct {        /* ROMPATCHAn 4 <= n <= 63 Address Registers (0x10041110) - (0x100411FC) Reset (0x00000000)  */
__REG32        : 1;     // Bit  0       - Reserved
__REG32 ADDRX  :23;     // Bits 1  - 23 - Address Comparator Registers
__REG32        : 8;     // Bits 24 - 31 - Reserved
} __ROMPATCHA_bits;

typedef struct {        /* ROMPATCH Base Address Register (0x10041204) Reset (0x00000000)  */
__REG32           :24;     // Bits  0 - 23 - Reserved
__REG32 BASEADDR  : 8;     // Bits 24 - 31 - ROM Base Address
} __ROMPATCHBASEA_bits;

typedef struct {        /* ROMPATCH Status Register (0x10041208) Reset (0x00000000)  */
__REG32 SOURCE_I  : 6;     // Bits 0  - 5  - ROMPATCH I-AHB Source Number
__REG32           : 2;     // Bits 6  - 7  - Reserved
__REG32 SOURCE_D  : 6;     // Bits 8  - 13 - ROMPATCH D-AHB Source Number
__REG32           : 3;     // Bits 14 - 16 - Reserved
__REG32 ISW       : 1;     // Bit  17      - I-AHB Simultaneous Address Comparisons
__REG32           : 7;     // Bits 18 - 24 - Reserved
__REG32 DSW       : 1;     // Bit  25      - D-AHB Simultaneous Address Comparisons
__REG32           : 6;     // Bits 26 - 31 - Reserved
} __ROMPATCHSR_bits;

typedef struct {        /* ROMPATCH Abort Status Register (0x1004120C) Reset (0x00000000)  */
__REG32 DAB    : 1;     // Bit  0       - ROMPATCH D-AHB Abort Indicator (0 = Normal, 1 = D-AHB cacheable or bufferableabort occurred.)
__REG32        : 7;     // Bits 1  - 7  - Reserved
__REG32 DAGEN  : 1;     // Bit  8       - ROMPATCH D-AHB Abort Cache Override Enable (0 = Cache Abort Override logic disabled for D-Cache, 1 = Cache Abort Override logic enabled for D-Cache.)
__REG32 DA0EN  : 1;     // Bits 9       - ROMPATCH D-AHB Aborted RDATA Override Enable (0 = Aborted RDATA Override logic disabled for D-Cache, 1 = Aborted RDATA Override logic enabled for D-Cache)
__REG32        : 6;     // Bits 10 - 15 - Reserved
__REG32 IAB    : 1;     // Bit  16      - ROMPATCH I-AHB Abort Indicator (0 = Normal, 1 = I-AHB cacheable or bufferable abort occurred.)
__REG32        : 7;     // Bits 17 - 23 - Reserved
__REG32 IAGEN  : 1;     // Bit  24      - ROMPATCH I-AHB Abort Cache Override Enable
__REG32 IAOEN  : 1;     // Bit  25      - ROMPATCH I-AHB Aborted RDATA Override Enable
__REG32        : 6;     // Bits 26 - 31 - Reserved
} __ROMPATCHABSR_bits;

/* -------------------------------------------------------------------------*/
/*      PLL and Clock Controller Module Registers                                                               */
/* -------------------------------------------------------------------------*/
typedef struct {        /* Clock Source Control Register (0x10027000) Reset (0x77180607)  */
__REG32 MPEN           : 1;     // Bit  0       - MPLL Enable
__REG32 SPEN           : 1;     // Bit  1       - Serial Peripheral PLL Enable
__REG32 FPM_EN         : 1;     // Bit  2       - Frequency Premultiplier Enable
__REG32 OSC26M_DIS     : 1;     // Bit  3       - Oscillator Disable
__REG32 OSC26M_DIV1P5  : 1;     // Bit  4       - Oscillator 26M Divide
__REG32                : 4;     // Bits 5  - 8  - Reserved
__REG32 IPDIV          : 1;     // Bit  9       - Peripheral Clock Divider
__REG32 BCLKDIV        : 4;     // Bits 10 - 13 - System Bus Clock Divider
__REG32                : 2;     // Bits 14 - 15 - Reserved
__REG32 MCU_SEL        : 1;     // Bit  16      - MPLL Select
__REG32 SP_SEL         : 1;     // Bit  17      - SPLL Select
__REG32 FIR_SEL        : 1;     // Bit  18      - FIR and MIR Select
__REG32 SSI1_SEL       : 1;     // Bit  19      - SSI1 Baud Source Select
__REG32 SSI2_SEL       : 1;     // Bit  20      - SSI2 Baud Source Select
__REG32 MPLL_RESTART   : 1;     // Bit  21      - MPLL Restart
__REG32 SPLL_RESTART   : 1;     // Bit  22      - SPLL Restart
__REG32                : 1;     // Bit  23      - Reserved
__REG32 SD_CNT         : 2;     // Bits 24 - 25 - Shut-Down Control
__REG32 USB_DIV        : 3;     // Bits 26 - 28 - USB Clock Divider
__REG32 PRESC          : 3;     // Bits 29 - 31 - Prescaler
} __CSCR_bits;

typedef struct { /* MCU & System PLL Control Register 0 (0x10027004) reset (0x00071C07) */
                 /* Serial Peripheral PLL Control Register 0 (0x1002700C) reset (0x807F2065) */
__REG32 MFN   :10;     // Bits 0  - 9  - Multiplication Factor (Numerator)
__REG32 MFI   : 4;     // Bits 10 - 13 - Multiplication Factor (Integer)
__REG32       : 2;     // Bits 14 - 15 - Reserved
__REG32 MFD   :10;     // Bits 16 - 25 - Multiplication Factor (Denominator Part)
__REG32 PD    : 4;     // Bits 26 - 29 - Predivider Factor applied to the PLL input frequency.(0-15)
__REG32       : 1;     // Bit  30      - Reserved
__REG32 CPLM  : 1;     // Bit  31      - Phase Lock Mode
} __MPCTL0_bits;

typedef struct { /* MCU & System PLL Control Register 1 (0x10027008) reset (0x00008000) */
                 /* Serial Peripheral PLL Control Register 1 (0x10027010) reset (0x00008000) */
__REG32       : 6;     // Bits 0  - 5  - Reserved
__REG32 BRMO  : 1;     // Bit  6       - Controls the BRM order.
__REG32       : 8;     // Bits 7 - 14  - Reserved
__REG32 LF    : 1;     // Bit  15      - Lock Flag - Indicates whether the System PLL is locked.
__REG32       :16;     // Bits 16 - 31 - Reserved
} __MPCTL1_bits;

typedef struct { /* Oscillator 26M Control Register (0x10027014) reset (0x00003F00) */
__REG32              : 8;     // Bits 0  - 7  - Reserved
__REG32 AGC          : 6;     // Bits 8  - 13 - Automatic Gain Control
__REG32              : 2;     // Bits 14 - 15 - Reserved
__REG32 OSC26M_PEAK  : 2;     // Bits 16 - 17 - OSC26M_PEAK - the oscillator's amplitude
__REG32              :14;     // Bits 16 - 31   - Reserved
} __OSC26MCTL_bits;

typedef struct { /* Peripheral Clock Divider Register 0 (0x10027018) reset (0x64193007) */
__REG32 FIRI_DIV     : 5;     // Bits 0  - 4  - FIRI Divider
__REG32 CLKO_48MDIV  : 3;     // Bits 5  - 7  - Clock Out 48M Clock Divider 1
__REG32              : 4;     // Bits 8  - 11 - Reserved
__REG32 NFCDIV       : 4;     // Bits 12 - 15 - Nand Flash Controller Clock Divider
__REG32 SSI1DIV      : 6;     // Bits 16 - 21 - SSI1 Baud Clock Divider
__REG32              : 4;     // Bits 22 - 25 - Reserved
__REG32 SSI2DIV      : 6;     // Bits 26 - 31 - SSI2 Baud Clock Divider
} __PCDR0_bits;

typedef struct { /* Peripheral Clock Divider Register 1 (0x1002701C) reset (0x03070F0F) */
__REG32 PCLK_DIV1  : 6;     // Bits 0  - 5  - Peripheral Clock Divider 1
__REG32            : 2;     // Bits 6  - 7  - Reserved
__REG32 PCLK_DIV2  : 6;     // Bits 8  - 13 - Peripheral Clock Divider 2
__REG32            : 2;     // Bits 14 - 15 - Reserved
__REG32 PCLK_DIV3  : 6;     // Bits 16 - 21 - Peripheral Clock Divider 3
__REG32            : 2;     // Bits 22 - 23 - Reserved
__REG32 PCLK_DIV4  : 6;     // Bits 24 - 29 - Peripheral Clock Divider 4
__REG32            : 2;     // Bits 30 - 31 - Reserved
} __PCDR1_bits;

typedef struct { /* Peripheral Clock Control Register 0 (0x10027020) reset (0x31084003) */
__REG32 UART1_EN        : 1;     // Bit  0       - UART1 Clock Enable
__REG32 UART2_EN        : 1;     // Bit  1       - UART2 Clock Enable
__REG32 UART3_EN        : 1;     // Bit  2       - UART3 Clock Enable
__REG32 UART4_EN        : 1;     // Bit  3       - UART4 Clock Enable
__REG32 CSPI1_EN        : 1;     // Bit  4       - CSPI1 Clock Enable
__REG32 CSPI2_EN        : 1;     // Bit  5       - CSPI2 Clock Enable
__REG32 SSI1_EN         : 1;     // Bit  6       - SSI1 Clock Enable
__REG32 SSI2_EN         : 1;     // Bit  7       - SSI2 Clock Enable
__REG32 FIRI_EN         : 1;     // Bit  8       - FIRI Clock Enable
__REG32 SDHC1_EN        : 1;     // Bit  9       - SDHC1 Clock Enable
__REG32 SDHC2_EN        : 1;     // Bit  10      - SDHC2 Clock Enable
__REG32 GPIO_EN         : 1;     // Bit  11      - GPIO Clock Enable
__REG32 I2C_EN          : 1;     // Bit  12      - I2C Clock Enable
__REG32 DMA_EN          : 1;     // Bit  13      - DMA Clock Enable
__REG32 USBOTG_EN       : 1;     // Bit  14      - USB OTG Clock Enable
__REG32 EMMA_EN         : 1;     // Bit  15      - EMMA Clock Enable
__REG32 SSI2_BAUD_EN    : 1;     // Bit  16      - SSI 2 Baud Clock Enable
__REG32 SSI1_BAUD_EN    : 1;     // Bit  17      - SSI 1 Baud Clock Enable
__REG32 PERCLK3_EN      : 1;     // Bit  18      - PERCLK3 Clock Enable
__REG32 NFC_EN          : 1;     // Bit  19      - Nand Flash Controller Clock
__REG32 FIRI_BAUD_EN    : 1;     // Bit  20      - FIRI Baud Clock Enable
__REG32 SLCDC_EN        : 1;     // Bit  21      - SLCDC Clock Enable
__REG32 PERCLK4_EN      : 1;     // Bit  22      - PERCLK4 Clock Enable
__REG32 HCLK_BMI_EN     : 1;     // Bit  23      - BMI Clock Enable
__REG32 HCLK_USBOTG_EN  : 1;     // Bit  24      - USB OTG Clock Enable
__REG32 HCLK_SLCDC_EN   : 1;     // Bit  25      - SLCDC Clock Enable
__REG32 HCLK_LCDC_EN    : 1;     // Bit  26      - LCDC Clock Enable
__REG32 HCLK_EMMA_EN    : 1;     // Bit  27      - EMMA Clock Enable
__REG32 HCLK_BROM_EN    : 1;     // Bit  28      - BROM Clock Enable
__REG32                 : 1;     // Bits 29      - Reserved
__REG32 HCLK_DMA_EN     : 1;     // Bit  30      - DMA Clock Enable
__REG32 HCLK_CSI_EN     : 1;     // Bit  31      - CMOS Sensor Interface Clock Enable
} __PCCR0_bits;

typedef struct { /* Peripheral Clock Control Register 1 (0x10027024) reset (0x00000000) */
__REG32           :21;     // Bits 0  - 20 - Reserved
__REG32 RNGA_EN   : 1;     // Bit  21      - RNGA Clock Enable
__REG32 RTIC_EN   : 1;     // Bit  22      - RTIC Clock Enable
__REG32 CSPI3_EN  : 1;     // Bit  23      - CSPI3 Clock Enable
__REG32 WDT_EN    : 1;     // Bit  24      - WDT Clock Enable
__REG32 GPT1_EN   : 1;     // Bit  25      - GPT1 Clock Enable
__REG32 GPT2_EN   : 1;     // Bit  26      - GPT2 Clock Enable
__REG32 GPT3_EN   : 1;     // Bit  27      - GPT3 Clock Enable
__REG32 PWM_EN    : 1;     // Bit  28      - PWM Clock Enable
__REG32 RTC_EN    : 1;     // Bit  29      - RTC Clock Enable
__REG32 KPP_EN    : 1;     // Bit  30      - KPP Clock Enable
__REG32 OWIRE_EN  : 1;     // Bit  31      - OWIRE Clock Enable
} __PCCR1_bits;

typedef struct { /* Clock Control Status Register (0x10027028) reset (0x00000300) */
__REG32 CLKO_SEL  : 5;     // Bits 1  - 4  - CLKO Select
__REG32           :10;     // Bits 5  - 14 - Reserved
__REG32 _32K_SR   : 1;     // Bit  15      - 32K Status Register
__REG32           :16;     // Bits 16 - 31 - Reserved
} __CCSR_bits;

typedef struct { /* Wakeup Guard Mode Control Register (0x10027034) reset (0x00000000) */
__REG32 WKGD_EN  : 1;     // Bit  0       - Wakeup Guard Mode Enable
__REG32          :31;     // Bits 1  - 31 - Reserved
} __WKGDCTL_bits;

/* -------------------------------------------------------------------------*/
/*      AIPI Registers                                                      */
/* -------------------------------------------------------------------------*/
typedef struct { /* Peripheral Size Register 0 (0x10000000) Reset (0x00040304)*/
                 /* Peripheral Size Register 1 (0x10000004) Reset (0xFFFBFCFB)*/
                 /* Peripheral Access Register (0x10000008) Reset (0xFFFFFFFF)*/
__REG32 AIPI1_CONTROL  : 1;     // Bit  0
__REG32 DMA            : 1;     // Bit  1
__REG32 WDOG           : 1;     // Bit  2
__REG32 GPT1           : 1;     // Bit  3
__REG32 GPT2           : 1;     // Bit  4
__REG32 GPT3           : 1;     // Bit  5
__REG32 PWM            : 1;     // Bit  6
__REG32 RTC            : 1;     // Bit  7
__REG32 KPP            : 1;     // Bit  8
__REG32 OWIRE          : 1;     // Bit  9
__REG32 UART1          : 1;     // Bit  10
__REG32 UART2          : 1;     // Bit  11
__REG32 UART3          : 1;     // Bit  12
__REG32 UART4          : 1;     // Bit  13
__REG32 CSPI1          : 1;     // Bit  14
__REG32 CSPI2          : 1;     // Bit  15
__REG32 SSI1           : 1;     // Bit  16
__REG32 SSI2           : 1;     // Bit  17
__REG32 I2C            : 1;     // Bit  18
__REG32 SDHC1          : 1;     // Bit  19
__REG32 SDHC2          : 1;     // Bit  20
__REG32 GPIO           : 1;     // Bit  21
__REG32 AUDMUX         : 1;     // Bit  22
__REG32 CSPI3          : 1;     // Bit  23
__REG32                : 8;     // Bits 24 - 31
} __AIPI1_bits;

typedef struct { /* Peripheral Size Register 0 (0x10020000) Reset (0x3FFC0000)*/
                 /* Peripheral Size Register 1 (0x10020004) Reset (0xFFFFFFFF)*/
                 /* Peripheral Access Register (0x10020008) Reset (0xFFFFFFFF)*/
__REG32 AIPI2_CONTROL  : 1;     // Bit  0
__REG32 LCDC           : 1;     // Bit  1
__REG32 SLCDC          : 1;     // Bit  2
__REG32 RTIC           : 1;     // Bit  3
__REG32 USB_OTG0       : 1;     // Bit  4
__REG32 USB_OTG1       : 1;     // Bit  5
__REG32 EMMA           : 1;     // Bit  6
__REG32 CRM            : 1;     // Bit  7
__REG32 FIRI           : 1;     // Bit  8
__REG32 RNGA           : 1;     // Bit  9
__REG32                :22;     // Bits 10 - 31
} __AIPI2_bits;

/* -------------------------------------------------------------------------*/
/*               System control registers                                                       */
/* -------------------------------------------------------------------------*/
typedef struct { /* Fuse Register (0x10027810) */
__REG32                :16;     // Bits 0  - 15 - Reserved
__REG32 HAB_TYPE       : 4;     // Bits 16 - 19 - HAB Type Blown
__REG32 HAB_SRS        : 3;     // Bits 20 - 22 - HAB Super Root Code
__REG32 HAB_CUS        : 5;     // Bits 23 - 27 - HAB Customer Code
__REG32 SCC_EN         : 1;     // Bit 28       - SCC Enable
__REG32 JTAG_MODE_SEL  : 1;     // Bit 29       - JTAG-Disable Module Select input
__REG32 BOOT_INT       : 1;     // Bit 30       - Boot from Internal Select
__REG32                : 1;     // Bit 31       - Reserved
} __FUSE_bits;

typedef struct { /* Function Multiplexing Control Register (0x10027814) Reset (0xFFFFFFCB) */
__REG32 SDCS0_SEL      : 1;     // Bit  0       - SDRAM/SyncFlash Chip Select CS2/CSD0
__REG32 SDCS1_SEL      : 1;     // Bit  1       - SDRAM/SyncFlash Chip Select CS3/CS1
__REG32 SLCDC_SEL      : 1;     // Bit  2       - SLCDC Select
__REG32                : 1;     // Bit  3       - Reserved
__REG32 NF_16BIT_SEL   : 1;     // Bit  4       - Nand Flash 16-bit Select
__REG32 NF_FMS         : 1;     // Bit  5       - Flash Memory Select
__REG32                : 6;     // Bit  6  - 11 - Reserved
__REG32 CRM_SPA_SEL    : 1;     // Bit  12      - CRM Set Point Adjust Select
__REG32                : 3;     // Bit  13 - 15 - Reserved
__REG32 KP_ROW6_CTL    : 1;     // Bit  16      - Keypad Row 6 Control
__REG32 KP_ROW7_CTL    : 1;     // Bit  17      - Keypad Row 7 Control
__REG32 KP_COL6_CTL    : 1;     // Bit  18      - Keypad Column 6 Control
__REG32                : 5;     // Bit  19 - 23 - Reserved
__REG32 UART4_RTS_CTL  : 1;     // Bit  24      - UART4 RTS Control
__REG32 UART4_RXD_CTL  : 1;     // Bit  25      - UART4 RXD Control
__REG32                : 6;     // Bits 26 - 31 - Reserved
} __FMCR_bits;

typedef struct { /* Global Peripheral Control Register (0x10027818) Reset (0x0000000C) */
__REG32                  : 3;     // Bits 0  - 2   - Reserved
__REG32 CLOCK_GATING_EN  : 1;     // Bit  3        - Clock Gating Enable
__REG32                  :12;     // Bits 4  - 15  - Reserved
__REG32 BOOT             : 4;     // Bits 16 - 19  - Boot Mode
__REG32                  :12;     // Bits 20 - 31  - Reserved
} __GPCR_bits;

typedef struct { /* Well Bias Control Register (0x1002781C) Reset (0x00000000) */
__REG32 CRM_WBM   : 3;     // Bits 0  - 2   - CRM_WBM—Enables or disables Well Bias System during STOP mode.
__REG32 CRM_WBFA  : 1;     // Bit  3        - Well Bias Frequency Adjust
__REG32           : 2;     // Bits 4  - 5   - Reserved
__REG32 CRM_WBS   : 2;     // Bits 6  - 7   - Well Bias Switching Mode
__REG32           :24;     // Bits 8  - 31  - Reserved
} __WBCR_bits;

typedef struct { /* Driving Strength Control Register 1 (0x10027820) Reset (0x00400000) */
__REG32 DS_SLOW1  : 3;     // Bits 0  - 2   - Driving Strength Slow I/O
__REG32 DS_SLOW2  : 3;     // Bits 3  - 5   - Driving Strength Slow I/O
__REG32 DS_SLOW3  : 3;     // Bits 6  - 8   - Driving Strength Slow I/O
__REG32 DS_SLOW4  : 3;     // Bits 9  - 11  - Driving Strength Slow I/O
__REG32 DS_SLOW5  : 3;     // Bits 12 - 14  - Driving Strength Slow I/O
__REG32           : 1;     // Bit  15       - Reserved
__REG32 DS_SLOW6  : 3;     // Bits 16 - 18  - Driving Strength Slow I/O
__REG32 DS_SLOW7  : 3;     // Bits 19 - 21  - Driving Strength Slow I/O
__REG32 DS_SLOW8  : 3;     // Bits 22 - 24  - Driving Strength Slow I/O
__REG32           : 7;     // Bits 25 - 31  - Reserved
} __DSCR1_bits;

typedef struct { /* Driving Strength Control Register 2 (0x10027824) Reset (0x00000000) */
__REG32 DS_SLOW31  : 3;     // Bits 0  - 2   - Driving Strength Slow I/O
__REG32 DS_SLOW30  : 3;     // Bits 3  - 5   - Driving Strength Slow I/O
__REG32 DS_SLOW29  : 3;     // Bits 6  - 8   - Driving Strength Slow I/O
__REG32 DS_SLOW28  : 3;     // Bits 9  - 11  - Driving Strength Slow I/O
__REG32 DS_SLOW27  : 3;     // Bits 12 - 14  - Driving Strength Slow I/O
__REG32            : 1;     // Bit  15       - Reserved
__REG32 DS_SLOW26  : 3;     // Bits 16 - 18  - Driving Strength Slow I/O
__REG32 DS_SLOW25  : 3;     // Bits 19 - 21  - Driving Strength Slow I/O
__REG32 DS_SLOW24  : 3;     // Bits 22 - 24  - Driving Strength Slow I/O
__REG32 DS_SLOW23  : 3;     // Bits 25 - 27  - Driving Strength Slow I/O
__REG32 DS_SLOW22  : 3;     // Bits 28 - 30  - Driving Strength Slow I/O
__REG32            : 1;     // Bit  31       - Reserved
} __DSCR2_bits;

typedef struct { /* Driving Strength Control Register 3 (0x10027828) Reset (0x00000000) */
__REG32 DS_SLOW21  : 3;     // Bits 0  - 2   - Driving Strength Slow I/O
__REG32 DS_SLOW20  : 3;     // Bits 3  - 5   - Driving Strength Slow I/O
__REG32 DS_SLOW19  : 3;     // Bits 6  - 8   - Driving Strength Slow I/O
__REG32 DS_SLOW18  : 3;     // Bits 9  - 11  - Driving Strength Slow I/O
__REG32 DS_SLOW17  : 3;     // Bits 12 - 14  - Driving Strength Slow I/O
__REG32            : 1;     // Bit  15       - Reserved
__REG32 DS_SLOW16  : 3;     // Bits 16 - 18  - Driving Strength Slow I/O
__REG32 DS_SLOW15  : 3;     // Bits 19 - 21  - Driving Strength Slow I/O
__REG32 DS_SLOW14  : 3;     // Bits 22 - 24  - Driving Strength Slow I/O
__REG32 DS_SLOW13  : 3;     // Bits 25 - 27  - Driving Strength Slow I/O
__REG32 DS_SLOW12  : 3;     // Bits 28 - 30  - Driving Strength Slow I/O
__REG32            : 1;     // Bit  31       - Reserved
} __DSCR3_bits;

typedef struct { /* Driving Strength Control Register 4 (0x1002782C) Reset (0x00000000) */
__REG32 DS_SLOW11  : 3;     // Bits 0  - 2   - Driving Strength Slow I/O
__REG32 DS_SLOW10  : 3;     // Bits 3  - 5   - Driving Strength Slow I/O
__REG32 DS_SLOW9   : 3;     // Bits 6  - 8   - Driving Strength Slow I/O
__REG32 DS_SLOW8   : 3;     // Bits 9  - 11  - Driving Strength Slow I/O
__REG32 DS_SLOW7   : 3;     // Bits 12 - 14  - Driving Strength Slow I/O
__REG32            : 1;     // Bit  15       - Reserved
__REG32 DS_SLOW6   : 3;     // Bits 16 - 18  - Driving Strength Slow I/O
__REG32 DS_SLOW5   : 3;     // Bits 19 - 21  - Driving Strength Slow I/O
__REG32 DS_SLOW4   : 3;     // Bits 22 - 24  - Driving Strength Slow I/O
__REG32 DS_SLOW3   : 3;     // Bits 25 - 27  - Driving Strength Slow I/O
__REG32 DS_SLOW2   : 3;     // Bits 28 - 30  - Driving Strength Slow I/O
__REG32            : 1;     // Bit  31       - Reserved
} __DSCR4_bits;

typedef struct { /* Driving Strength Control Register 5 (0x10027830) Reset (0x00000000) */
__REG32 DS_D1          : 3;     // Bits 0  - 2   - Driving Strength Fast I/O
__REG32 DS_D0          : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_A25_NFIO15  : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32 DS_A24_NFIO14  : 3;     // Bits 9  - 11  - Driving Strength Fast I/O
__REG32 DS_A24_NFIO13  : 3;     // Bits 12 - 14  - Driving Strength Fast I/O
__REG32                : 1;     // Bit  15       - Reserved
__REG32 DS_A24_NFIO12  : 3;     // Bits 16 - 18  - Driving Strength Fast I/O
__REG32 DS_A24_NFIO11  : 3;     // Bits 19 - 21  - Driving Strength Fast I/O
__REG32 DS_A20         : 3;     // Bits 22 - 24  - Driving Strength Fast I/O
__REG32 DS_A19         : 3;     // Bits 25 - 27  - Driving Strength Fast I/O
__REG32 DS_A18         : 3;     // Bits 28 - 30  - Driving Strength Fast I/O
__REG32                : 1;     // Bit  31       - Reserved
} __DSCR5_bits;

typedef struct { /* Driving Strength Control Register 6 (0x10027834) Reset (0x00000000) */
__REG32 DS_A17         : 3;     // Bits 0  - 2   - Driving Strength Fast I/O
__REG32 DS_A16         : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_A15_NFIO10  : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32 DS_A24_NFIO9   : 3;     // Bits 9  - 11  - Driving Strength Fast I/O
__REG32 DS_A24_NFIO8   : 3;     // Bits 12 - 14  - Driving Strength Fast I/O
__REG32                : 1;     // Bit  15       - Reserved
__REG32 DS_A12         : 3;     // Bits 16 - 18  - Driving Strength Fast I/O
__REG32 DS_A11         : 3;     // Bits 19 - 21  - Driving Strength Fast I/O
__REG32 DS_A10         : 3;     // Bits 22 - 24  - Driving Strength Fast I/O
__REG32 DS_A9          : 3;     // Bits 25 - 27  - Driving Strength Fast I/O
__REG32 DS_A8          : 3;     // Bits 28 - 30  - Driving Strength Fast I/O
__REG32                : 1;     // Bit  31       - Reserved
} __DSCR6_bits;

typedef struct { /* Driving Strength Control Register 7 (0x10027838) Reset (0x00000000) */
__REG32 DS_A7    : 3;     // Bits 0  - 2   - Driving Strength Fast I/O
__REG32 DS_A6    : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_A5    : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32 DS_A4    : 3;     // Bits 9  - 11  - Driving Strength Fast I/O
__REG32 DS_A3    : 3;     // Bits 12 - 14  - Driving Strength Fast I/O
__REG32          : 1;     // Bit  15       - Reserved
__REG32 DS_A2    : 3;     // Bits 16 - 18  - Driving Strength Fast I/O
__REG32 DS_A1    : 3;     // Bits 19 - 21  - Driving Strength Fast I/O
__REG32 DS_A0    : 3;     // Bits 22 - 24  - Driving Strength Fast I/O
__REG32 DS_OE_B  : 3;     // Bits 25 - 27  - Driving Strength Fast I/O
__REG32 DS_BCLK  : 3;     // Bits 28 - 30  - Driving Strength Fast I/O
__REG32          : 1;     // Bit  31       - Reserved
} __DSCR7_bits;

typedef struct { /* Driving Strength Control Register 8 (0x1002783C) Reset (0x00000000) */
__REG32 DS_EB0_B  : 3;     // Bits 0  - 2   - Driving Strength Fast I/O
__REG32 DS_EB1_B  : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_EB2_B  : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32 DS_EB3_B  : 3;     // Bits 9  - 11  - Driving Strength Fast I/O
__REG32 DS_CS5_B  : 3;     // Bits 12 - 14  - Driving Strength Fast I/O
__REG32           : 1;     // Bit  15       - Reserved
__REG32 DS_CS4_B  : 3;     // Bits 16 - 18  - Driving Strength Fast I/O
__REG32 DS_CS3_B  : 3;     // Bits 19 - 21  - Driving Strength Fast I/O
__REG32 DS_CS2_B  : 3;     // Bits 22 - 24  - Driving Strength Fast I/O
__REG32 DS_CS1_B  : 3;     // Bits 25 - 27  - Driving Strength Fast I/O
__REG32 DS_CS0_B  : 3;     // Bits 28 - 30  - Driving Strength Fast I/O
__REG32           : 1;     // Bit  31       - Reserved
} __DSCR8_bits;

typedef struct { /* Driving Strength Control Register 9 (0x10027840) Reset (0x00000000) */
__REG32           : 3;     // Bits 0  - 2   - Reserved
__REG32 DS_LBA_B  : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_RW_B   : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32 DS_MA11   : 3;     // Bits 9  - 11  - Driving Strength Fast I/O
__REG32 DS_MA10   : 3;     // Bits 12 - 14  - Driving Strength Fast I/O
__REG32           : 7;     // Bits 15 - 21  - Reserved
__REG32 DS_SDCLK  : 3;     // Bits 22 - 24  - Driving Strength Fast I/O
__REG32 DS_RAS_B  : 3;     // Bits 25 - 27  - Driving Strength Fast I/O
__REG32 DS_CAS_B  : 3;     // Bits 28 - 30  - Driving Strength Fast I/O
__REG32           : 1;     // Bit  31       - Reserved
} __DSCR9_bits;

typedef struct { /* Driving Strength Control Register 10 (0x10027844) Reset (0x00000000) */
__REG32 DS_SDWE_B  : 3;     // Bits 0  - 2   - Driving Strength Fast I/O
__REG32 DS_SDCKE0  : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_SDCKE1  : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32            : 3;     // Bits 9  - 11  - Reserved
__REG32 DS_CLKO    : 3;     // Bits 12 - 14  - Driving Strength Fast I/O
__REG32            : 1;     // Bit  15       - Reserved
__REG32 DS_NFIO7   : 3;     // Bits 16 - 18  - Driving Strength Fast I/O
__REG32 DS_NFIO6   : 3;     // Bits 19 - 21  - Driving Strength Fast I/O
__REG32 DS_NFIO5   : 3;     // Bits 22 - 24  - Driving Strength Fast I/O
__REG32 DS_NFIO4   : 3;     // Bits 25 - 27  - Driving Strength Fast I/O
__REG32 DS_NFIO3   : 3;     // Bits 28 - 30  - Driving Strength Fast I/O
__REG32            : 1;     // Bit  31       - Reserved
} __DSCR10_bits;

typedef struct { /* Driving Strength Control Register 11 (0x10027848) Reset (0x00000000) */
__REG32 DS_NFIO2   : 3;     // Bits 0  - 2   - Driving Strength Fast I/O
__REG32 DS_NFIO1   : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_NFIO0   : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32 DS_NFWE_B  : 3;     // Bits 9  - 11  - Driving Strength Fast I/O
__REG32 DS_NFRE_B  : 3;     // Bits 12 - 14  - Driving Strength Fast I/O
__REG32            : 1;     // Bit  15       - Reserved
__REG32 DS_NFALE   : 3;     // Bits 16 - 18  - Driving Strength Fast I/O
__REG32 DS_NFCLE   : 3;     // Bits 19 - 21  - Driving Strength Fast I/O
__REG32 DS_NFWP_B  : 3;     // Bits 22 - 24  - Driving Strength Fast I/O
__REG32 DS_NFCE_B  : 3;     // Bits 25 - 27  - Driving Strength Fast I/O
__REG32 DS_NFRB    : 3;     // Bits 28 - 30  - Driving Strength Fast I/O
__REG32            : 1;     // Bit  31       - Reserved
} __DSCR11_bits;

typedef struct { /* Driving Strength Control Register 12 (0x1002784C) Reset (0x00000000) */
__REG32 DS_CSI_PIXCLK  : 3;     // Bits 0  - 2   - Driving Strength Fast I/O
__REG32 DS_CSI_MCLK    : 3;     // Bits 3  - 5   - Driving Strength Fast I/O
__REG32 DS_LSCLK       : 3;     // Bits 6  - 8   - Driving Strength Fast I/O
__REG32                :23;     // Bits 9  - 31  - Reserved
} __DSCR12_bits;

typedef struct { /* Priority Control and Select Register Description (0x10027850) Reset (0x00000003) */
__REG32              :16;     // Bits 0  - 15 - Reserved
__REG32 S0_AMPR_SEL  : 1;     // Bit 16       - Slave Alternate Context Priority Select
__REG32 S1_AMPR_SEL  : 1;     // Bit 17       - Slave Alternate Context Priority Select
__REG32 S2_AMPR_SEL  : 1;     // Bit 18       - Slave Alternate Context Priority Select
__REG32 S3_AMPR_SEL  : 1;     // Bit 19       - Slave Alternate Context Priority Select
__REG32              :12;     // Bits 20 - 31 - Reserved
} __PCSR_bits;

/***************************************************************************
 **
 **  Multi-layer AHB Crossbar Switch (MAX)
 **
 ***************************************************************************/
typedef struct { /*           Master Priority Register for Slave Port 0 (0x1003F000) Reset (0x76543210) */
                 /*           Master Priority Register for Slave Port 1 (0x1003F100) Reset (0x76543210) */
                 /*           Master Priority Register for Slave Port 2 (0x1003F200) Reset (0x76543210) */
                 /*           Master Priority Register for Slave Port 3 (0x1003F300) Reset (0x76543210) */
                 /* Alternate Master Priority Register for Slave Port 0 (0x1003F004) Reset (0x76543210) */
                 /* Alternate Master Priority Register for Slave Port 1 (0x1003F104) Reset (0x76543210) */
                 /* Alternate Master Priority Register for Slave Port 2 (0x1003F204) Reset (0x76543210) */
                 /* Alternate Master Priority Register for Slave Port 3 (0x1003F304) Reset (0x76543210) */
__REG32 MSTR_0  : 3;     // Bits 0  - 2  - Master 0 Priority
__REG32         : 1;     // Bit  3       - Reserved
__REG32 MSTR_1  : 3;     // Bits 4  - 6  - Master 1 Priority
__REG32         : 1;     // Bit  7       - Reserved
__REG32 MSTR_2  : 3;     // Bits 8  - 10 - Master 2 Priority
__REG32         : 1;     // Bit  11      - Reserved
__REG32 MSTR_3  : 3;     // Bits 12 - 14 - Master 3 Priority
__REG32         : 1;     // Bit  15      - Reserved
__REG32 MSTR_4  : 3;     // Bits 16 - 18 - Master 4 Priority
__REG32         : 1;     // Bit  19      - Reserved
__REG32 MSTR_5  : 3;     // Bits 20 - 22 - Master 5 Priority
__REG32         : 9;     // Bits 23 - 31 - Reserved
} __MPR_bits;

typedef struct { /* Slave General Purpose Control Register for Slave Port 0 (0x1003F010) Reset (0x00000000) */
                 /* Slave General Purpose Control Register for Slave Port 1 (0x1003F110) Reset (0x00000000) */
                 /* Slave General Purpose Control Register for Slave Port 2 (0x1003F210) Reset (0x00000000) */
                 /* Slave General Purpose Control Register for Slave Port 3 (0x1003F310) Reset (0x00000000) */
__REG32 PARK  : 3;     // Bits 0  - 2  - PARK
__REG32       : 1;     // Bit  3       - Reserved
__REG32 PCTL  : 2;     // Bits 4  - 5  - Parking Control
__REG32       : 2;     // Bits 6  - 7  - Reserved
__REG32 ARB   : 2;     // Bits 8  - 9  - Arbitration Mode
__REG32       :20;     // Bits 10 - 29 - Reserved
__REG32 HLP   : 1;     // Bit  30      - Halt Low Priority
__REG32 RO    : 1;     // Bit  31      - Read Only
} __SGPCR_bits;

typedef struct { /* Alternate Slave General Purpose Control Register for Slave Port 0 (0x1003F014) Reset (0x00000000) */
                 /* Alternate Slave General Purpose Control Register for Slave Port 1 (0x1003F114) Reset (0x00000000) */
                 /* Alternate Slave General Purpose Control Register for Slave Port 2 (0x1003F214) Reset (0x00000000) */
                 /* Alternate Slave General Purpose Control Register for Slave Port 3 (0x1003F314) Reset (0x00000000) */
__REG32 PARK  : 3;     // Bits 0  - 2  - PARK
__REG32       : 1;     // Bit  3       - Reserved
__REG32 PCTL  : 2;     // Bits 4  - 5  - Parking Control
__REG32       : 2;     // Bits 6  - 7  - Reserved
__REG32 ARB   : 2;     // Bits 8  - 9  - Arbitration Mode
__REG32       :20;     // Bits 10 - 29 - Reserved
__REG32 HLP   : 1;     // Bit  30      - Halt Low Priority
__REG32       : 1;     // Bit  31      - Reserved
} __ASGPCR_bits;

typedef struct { /* Master General Purpose Control Register for Master Port 0 (0x1003F800) Reset (0x00000000) */
                 /* Master General Purpose Control Register for Master Port 1 (0x1003F900) Reset (0x00000000) */
                 /* Master General Purpose Control Register for Master Port 2 (0x1003FA00) Reset (0x00000000) */
                 /* Master General Purpose Control Register for Master Port 3 (0x1003FB00) Reset (0x00000000) */
                 /* Master General Purpose Control Register for Master Port 4 (0x1003FC00) Reset (0x00000000) */
                 /* Master General Purpose Control Register for Master Port 5 (0x1003FD00) Reset (0x00000000) */
__REG32 AULB  : 3;     // Bits 0  - 2  - Arbitrate on Undefined Length Bursts
__REG32       :29;     // Bits 3  - 31 - Reserved
} __MGPCR_bits;

/* -------------------------------------------------------------------------*/
/*      Watchdog Registers                                                  */
/* -------------------------------------------------------------------------*/
typedef struct {        // Watchdog Control Register (0x10002000) Reset  (0x00000000)
__REG16 WDZST  : 1;     // Bit  0       - Watchdog Low Power
__REG16 WDBG   : 1;     // Bits 1       - Watchdog DEBUG Enable
__REG16 WDE    : 1;     // Bit  2       - Watchdog Enable
__REG16 WRE    : 1;     // Bit  3       - ~WDOG or ~WDOG_RESET Enable
__REG16 _SRS   : 1;     // Bit  4       - ~Software Reset Signal
__REG16 _WDA   : 1;     // Bit  5       - ~Watchdog Assertion
__REG16        : 2;     // Bits 6 - 7   - Reserved
__REG16 WT     : 8;     // Bits 8 - 15  - Watchdog Time-Out Field
} __WCR_bits;

typedef struct {        // Watchdog Reset Status Register (0x10002004) Reset (*)
__REG32 SFTW  : 1;     // Bit  0       - Software Reset
__REG32 TOUT  : 1;     // Bit  1       - Time-out
__REG32       : 1;     // Bit  2       - Reserved
__REG32 EXT   : 1;     // Bit  3       - External Reset
__REG32 PWR   : 1;     // Bit  4       - Power-On Reset
__REG32       :11;     // Bits 5  - 15 - Reserved
} __WRSR_bits;

/* -------------------------------------------------------------------------*/
/*      RTC Registers                                                       */
/* -------------------------------------------------------------------------*/
/* RTC Days counter register */
typedef struct{
__REG32 DAYS  :16;     
__REG32       :16;     
} __DAYR_bits;

/* RTC hours and minutes counter register */
typedef struct{
__REG32 MINUTES  : 6;     
__REG32          : 2;     
__REG32 HOURS    : 5;     
__REG32          :19;     
} __HOURMIN_bits;

/* RTC seconds counter register */
typedef struct{
__REG32 SECONDS  : 6;     
__REG32          :26;     
} __SECONDS_bits;

/* RTC Day alarm register */
typedef struct{
__REG32 DAYSAL  :16;     
__REG32         :16;     
} __DAYALARM_bits;

/* RTC control register */
typedef struct{
__REG32 SWR  : 1;     
__REG32      : 4;     
__REG32 XTL  : 2;     
__REG32 EN   : 1;     
__REG32      :24;     
} __RCCTL_bits;

/* RTC interrupt status register */
typedef struct{
__REG32 SW    : 1;     
__REG32 MIN   : 1;     
__REG32 ALM   : 1;     
__REG32 DAY   : 1;     
__REG32 _1HZ  : 1;     
__REG32 HR    : 1;     
__REG32       : 1;     
__REG32 _2HZ  : 1;     
__REG32 SAM0  : 1;     
__REG32 SAM1  : 1;     
__REG32 SAM2  : 1;     
__REG32 SAM3  : 1;     
__REG32 SAM4  : 1;     
__REG32 SAM5  : 1;     
__REG32 SAM6  : 1;     
__REG32 SAM7  : 1;     
__REG32       :16;     
} __RTCISR_bits;

/* RTC stopwatch minutes register */
typedef struct{
__REG32 CNT  : 6;     
__REG32      :26;     
} __STPWCH_bits;

/* -------------------------------------------------------------------------*/
/*      General-Purpose Timer                                               */
/* -------------------------------------------------------------------------*/
/* GPT Control Register */
typedef struct{
__REG32 TEN        : 1;     // Bit  0       - Timer Enable1 = Timer is enabled 0 = Timer is disabled (counter reset to 0)
__REG32 CLKSOURCE  : 3;     // Bits 1  - 3  - Clock Source
                                //              - 000 = Stop count (clock disabled)
                                //              - 001 = PERCLK1 to prescaler
                                //              - 010 = PERCLK1 ÷16 to prescaler
                                //              - 011 = TIN to prescaler
                                //              - 1xx = 32 kHz clock to prescaler
__REG32 COMP_EN    : 1;     // Bit  4       - Compare Interrupt Enable—This bit enables the compares interrupt
__REG32 CAPT_EN    : 1;     // Bit  5       - Capture Interrupt Enable—This bit enables the capture interrupt
__REG32 CAP        : 2;     // Bits 6  - 7  - Capture Edge
                                //              - 00 = Disable the capture function
                                //              - 01 = Capture on the rising edge and generate an interrupt
                                //              - 10 = Capture on the falling edge and generate an interrupt
                                //              - 11 = Capture on the rising and falling edges and generate an interrupt
__REG32 FRR        : 1;     // Bit  8       - Free-Run/Restart0 = Restart mode 1 = Free-run mode
__REG32 OM         : 1;     // Bit  9       - Output Mode—This bit controls the output mode of the timer after compare event occurs.
__REG32 CC         : 1;     // Bit  10      - Counter Clear—This bit determines whether the counter is to be cleared when TEN=0 (timer disabled).
__REG32            : 4;     // Bits 11 - 14 - Reserved
__REG32 SWR        : 1;     // Bit  15      - Software Reset0 = No software reset sent
__REG32            :16;     // Bits 16 - 31 - Reserved
} __TCTL_bits;

/* GPT Prescaler Register */
typedef struct{
__REG32 PRESCALER  :11;     // Bits 0  - 10 -
                                //              - 0x00 = Divide by 1
                                //              - 0x01 = Divide by 2
                                //              - ...
                                //              - 0x3FF = Divide by 2048
__REG32            :21;     
} __TPRER_bits;

/* GPT Status Register 1 */
typedef struct{
__REG32 COMP  : 1;     // bit  0  - Compare Event0 = No compare event occurred
__REG32 CAPT  : 1;     // bit  1  - Capture Event0 = No capture event occurred
__REG32       :30;     
} __TSTAT_bits;

/* -------------------------------------------------------------------------*/
/*      PWM Registers                                                       */
/* -------------------------------------------------------------------------*/
/* PWM control register */
typedef struct{
__REG32 CLKSEL     : 2;     
__REG32 REPEAT     : 2;     
__REG32 EN         : 1;     
__REG32 FIFOAV     : 1;     
__REG32 IRQEN      : 1;     
__REG32 IRQ        : 1;     
__REG32 PRESCALER  : 7;     
__REG32 CLKSRC     : 1;     
__REG32 SWR        : 1;     
__REG32 BCTR       : 1;     
__REG32 HCTR       : 1;     
__REG32            :13;     
} __PWMC_bits;

/* PWM sample register */
typedef struct{
__REG32 SAMPLE  :16;     
__REG32         :16;     
} __PWMS_bits;

/* PWM period register */
typedef struct{
__REG32 PERIOD  :16;     
__REG32         :16;     
} __PWMP_bits;

/* PWM counter register */
typedef struct{
__REG32 COUNT  :16;     
__REG32        :16;     
} __PWMCNT_bits;

/* -------------------------------------------------------------------------*/
/*      GPIO Registers                                                      */
/* -------------------------------------------------------------------------*/
typedef struct { /* Structure for GPIO Register Type 1.                                         */
__REG32 PIN0   : 2;     // Bits 1-0
__REG32 PIN1   : 2;     // Bits 3-2
__REG32 PIN2   : 2;     // Bits 5-4
__REG32 PIN3   : 2;     // Bits 7-6
__REG32 PIN4   : 2;     // Bits 9-8
__REG32 PIN5   : 2;     // Bits 11-10
__REG32 PIN6   : 2;     // Bits 13-12
__REG32 PIN7   : 2;     // Bits 15-14
__REG32 PIN8   : 2;     // Bits 17-16
__REG32 PIN9   : 2;     // Bits 19-18
__REG32 PIN10  : 2;     // Bits 21-20
__REG32 PIN11  : 2;     // Bits 23-22
__REG32 PIN12  : 2;     // Bits 25-24
__REG32 PIN13  : 2;     // Bits 27-26
__REG32 PIN14  : 2;     // Bits 29-28
__REG32 PIN15  : 2;     // Bits 31-30
} __PORT_REG_15_0_bits;

typedef struct { /* Structure for GPIO Register Type 2.                                         */
__REG32 PIN16  : 2;     // Bits 1-0
__REG32 PIN17  : 2;     // Bits 3-2
__REG32 PIN18  : 2;     // Bits 5-4
__REG32 PIN19  : 2;     // Bits 7-6
__REG32 PIN20  : 2;     // Bits 9-8
__REG32 PIN21  : 2;     // Bits 11-10
__REG32 PIN22  : 2;     // Bits 13-12
__REG32 PIN23  : 2;     // Bits 15-14
__REG32 PIN24  : 2;     // Bits 17-16
__REG32 PIN25  : 2;     // Bits 19-18
__REG32 PIN26  : 2;     // Bits 21-20
__REG32 PIN27  : 2;     // Bits 23-22
__REG32 PIN28  : 2;     // Bits 25-24
__REG32 PIN29  : 2;     // Bits 27-26
__REG32 PIN30  : 2;     // Bits 29-28
__REG32 PIN31  : 2;     // Bits 31-30           - See table below
} __PORT_REG_31_16_bits;

typedef struct { /* Structure for GPIO Register Type 3.                                         */
__REG32 PIN0   : 1;     // Bit 0
__REG32 PIN1   : 1;     // Bit 1
__REG32 PIN2   : 1;     // Bit 2
__REG32 PIN3   : 1;     // Bit 3
__REG32 PIN4   : 1;     // Bit 4
__REG32 PIN5   : 1;     // Bit 5
__REG32 PIN6   : 1;     // Bit 6
__REG32 PIN7   : 1;     // Bit 7
__REG32 PIN8   : 1;     // Bit 8
__REG32 PIN9   : 1;     // Bit 9
__REG32 PIN10  : 1;     // Bit 10
__REG32 PIN11  : 1;     // Bit 11
__REG32 PIN12  : 1;     // Bit 12
__REG32 PIN13  : 1;     // Bit 13
__REG32 PIN14  : 1;     // Bit 14
__REG32 PIN15  : 1;     // Bit 15
__REG32 PIN16  : 1;     // Bit 16
__REG32 PIN17  : 1;     // Bit 17
__REG32 PIN18  : 1;     // Bit 18
__REG32 PIN19  : 1;     // Bit 19
__REG32 PIN20  : 1;     // Bit 20
__REG32 PIN21  : 1;     // Bit 21
__REG32 PIN22  : 1;     // Bit 22
__REG32 PIN23  : 1;     // Bit 23
__REG32 PIN24  : 1;     // Bit 24
__REG32 PIN25  : 1;     // Bit 25
__REG32 PIN26  : 1;     // Bit 26
__REG32 PIN27  : 1;     // Bit 27
__REG32 PIN28  : 1;     // Bit 28
__REG32 PIN29  : 1;     // Bit 29
__REG32 PIN30  : 1;     // Bit 30
__REG32 PIN31  : 1;     // Bit 31
} __PORT_REG_31_0_bits;

typedef struct { /* GPIO In Use Register A */
__REG32        : 5;     // Bit 0  - 4
__REG32 PIN5   : 1;     // Bit 5
__REG32 PIN6   : 1;     // Bit 6
__REG32 PIN7   : 1;     // Bit 7
__REG32 PIN8   : 1;     // Bit 8
__REG32 PIN9   : 1;     // Bit 9
__REG32 PIN10  : 1;     // Bit 10
__REG32 PIN11  : 1;     // Bit 11
__REG32 PIN12  : 1;     // Bit 12
__REG32 PIN13  : 1;     // Bit 13
__REG32 PIN14  : 1;     // Bit 14
__REG32 PIN15  : 1;     // Bit 15
__REG32 PIN16  : 1;     // Bit 16
__REG32 PIN17  : 1;     // Bit 17
__REG32 PIN18  : 1;     // Bit 18
__REG32 PIN19  : 1;     // Bit 19
__REG32 PIN20  : 1;     // Bit 20
__REG32 PIN21  : 1;     // Bit 21
__REG32 PIN22  : 1;     // Bit 22
__REG32 PIN23  : 1;     // Bit 23
__REG32 PIN24  : 1;     // Bit 24
__REG32 PIN25  : 1;     // Bit 25
__REG32 PIN26  : 1;     // Bit 26
__REG32 PIN27  : 1;     // Bit 27
__REG32 PIN28  : 1;     // Bit 28
__REG32 PIN29  : 1;     // Bit 29
__REG32 PIN30  : 1;     // Bit 30
__REG32 PIN31  : 1;     // Bit 31
} __PTA_GIUS_bits;

typedef struct { /* GPIO In Use Register B */
__REG32        : 4;     // Bit 0  - 3
__REG32 PIN4   : 1;     // Bit 4
__REG32 PIN5   : 1;     // Bit 5
__REG32 PIN6   : 1;     // Bit 6
__REG32 PIN7   : 1;     // Bit 7
__REG32 PIN8   : 1;     // Bit 8
__REG32 PIN9   : 1;     // Bit 9
__REG32 PIN10  : 1;     // Bit 10
__REG32 PIN11  : 1;     // Bit 11
__REG32 PIN12  : 1;     // Bit 12
__REG32 PIN13  : 1;     // Bit 13
__REG32 PIN14  : 1;     // Bit 14
__REG32 PIN15  : 1;     // Bit 15
__REG32 PIN16  : 1;     // Bit 16
__REG32 PIN17  : 1;     // Bit 17
__REG32 PIN18  : 1;     // Bit 18
__REG32 PIN19  : 1;     // Bit 19
__REG32 PIN20  : 1;     // Bit 20
__REG32 PIN21  : 1;     // Bit 21
__REG32 PIN22  : 1;     // Bit 22
__REG32 PIN23  : 1;     // Bit 23
__REG32 PIN24  : 1;     // Bit 24
__REG32 PIN25  : 1;     // Bit 25
__REG32 PIN26  : 1;     // Bit 26
__REG32 PIN27  : 1;     // Bit 27
__REG32 PIN28  : 1;     // Bit 28
__REG32 PIN29  : 1;     // Bit 29
__REG32 PIN30  : 1;     // Bit 30
__REG32 PIN31  : 1;     // Bit 31
} __PTB_GIUS_bits;

typedef struct { /* GPIO In Use Register C */
__REG32        : 5;     // Bit 0  - 4
__REG32 PIN5   : 1;     // Bit 5
__REG32 PIN6   : 1;     // Bit 6
__REG32 PIN7   : 1;     // Bit 7
__REG32 PIN8   : 1;     // Bit 8
__REG32 PIN9   : 1;     // Bit 9
__REG32 PIN10  : 1;     // Bit 10
__REG32 PIN11  : 1;     // Bit 11
__REG32 PIN12  : 1;     // Bit 12
__REG32 PIN13  : 1;     // Bit 13
__REG32 PIN14  : 1;     // Bit 14
__REG32 PIN15  : 1;     // Bit 15
__REG32 PIN16  : 1;     // Bit 16
__REG32 PIN17  : 1;     // Bit 17
__REG32 PIN18  : 1;     // Bit 18
__REG32 PIN19  : 1;     // Bit 19
__REG32 PIN20  : 1;     // Bit 20
__REG32 PIN21  : 1;     // Bit 21
__REG32 PIN22  : 1;     // Bit 22
__REG32 PIN23  : 1;     // Bit 23
__REG32 PIN24  : 1;     // Bit 24
__REG32 PIN25  : 1;     // Bit 25
__REG32 PIN26  : 1;     // Bit 26
__REG32 PIN27  : 1;     // Bit 27
__REG32 PIN28  : 1;     // Bit 28
__REG32 PIN29  : 1;     // Bit 29
__REG32 PIN30  : 1;     // Bit 30
__REG32 PIN31  : 1;     // Bit 31
} __PTC_GIUS_bits;

typedef struct { /* GPIO In Use Register D */
__REG32        :17;     // Bit 0  - 16
__REG32 PIN17  : 1;     // Bit 17
__REG32 PIN18  : 1;     // Bit 18
__REG32 PIN19  : 1;     // Bit 19
__REG32 PIN20  : 1;     // Bit 20
__REG32 PIN21  : 1;     // Bit 21
__REG32 PIN22  : 1;     // Bit 22
__REG32 PIN23  : 1;     // Bit 23
__REG32 PIN24  : 1;     // Bit 24
__REG32 PIN25  : 1;     // Bit 25
__REG32 PIN26  : 1;     // Bit 26
__REG32 PIN27  : 1;     // Bit 27
__REG32 PIN28  : 1;     // Bit 28
__REG32 PIN29  : 1;     // Bit 29
__REG32 PIN30  : 1;     // Bit 30
__REG32 PIN31  : 1;     // Bit 31
} __PTD_GIUS_bits;

typedef struct { /* GPIO In Use Register E */
__REG32 PIN0   : 1;     // Bit 0
__REG32 PIN1   : 1;     // Bit 1
__REG32 PIN2   : 1;     // Bit 2
__REG32 PIN3   : 1;     // Bit 3
__REG32 PIN4   : 1;     // Bit 4
__REG32 PIN5   : 1;     // Bit 5
__REG32 PIN6   : 1;     // Bit 6
__REG32 PIN7   : 1;     // Bit 7
__REG32 PIN8   : 1;     // Bit 8
__REG32 PIN9   : 1;     // Bit 9
__REG32 PIN10  : 1;     // Bit 10
__REG32 PIN11  : 1;     // Bit 11
__REG32 PIN12  : 1;     // Bit 12
__REG32 PIN13  : 1;     // Bit 13
__REG32 PIN14  : 1;     // Bit 14
__REG32 PIN15  : 1;     // Bit 15
__REG32 PIN16  : 1;     // Bit 16
__REG32 PIN17  : 1;     // Bit 17
__REG32 PIN18  : 1;     // Bit 18
__REG32 PIN19  : 1;     // Bit 19
__REG32 PIN20  : 1;     // Bit 20
__REG32 PIN21  : 1;     // Bit 21
__REG32 PIN22  : 1;     // Bit 22
__REG32 PIN23  : 1;     // Bit 23
__REG32        : 8;     // Bit 24 - 31
} __PTE_GIUS_bits;

typedef struct { /* GPIO In Use Register F */
__REG32 PIN0   : 1;     // Bit 0
__REG32 PIN1   : 1;     // Bit 1
__REG32 PIN2   : 1;     // Bit 2
__REG32 PIN3   : 1;     // Bit 3
__REG32 PIN4   : 1;     // Bit 4
__REG32 PIN5   : 1;     // Bit 5
__REG32 PIN6   : 1;     // Bit 6
__REG32 PIN7   : 1;     // Bit 7
__REG32 PIN8   : 1;     // Bit 8
__REG32 PIN9   : 1;     // Bit 9
__REG32 PIN10  : 1;     // Bit 10
__REG32 PIN11  : 1;     // Bit 11
__REG32 PIN12  : 1;     // Bit 12
__REG32 PIN13  : 1;     // Bit 13
__REG32 PIN14  : 1;     // Bit 14
__REG32 PIN15  : 1;     // Bit 15
__REG32        :16;     // Bit 16 - 31
} __PTF_GIUS_bits;

typedef struct{
__REG32 SWR  : 1;     // Bit 0        -   Software Reset (0 = No effect, 1 = GPIO circuitry for Port X Reset)
__REG32      :31;     // Bits 31-1    -   Reserved, should read 0
} __SWR_bits;

/* Port Interrupt Mask Register */
typedef struct{
__REG32 PTA  : 1;     // Bit 0        -  Port A—The bit helps in masking the Port A interrupt. The bit clears during software reset of Port A.
__REG32 PTB  : 1;     // Bit 1        -  Port B—The bit helps in masking the Port B interrupt. The bit clears during software reset of Port B.
__REG32 PTC  : 1;     // Bit 2        -  Port C—The bit helps in masking the Port C interrupt. The bit clears during software reset of Port C.
__REG32 PTD  : 1;     // Bit 3        -  Port D—The bit helps in masking the Port D interrupt. The bit clears during software reset of Port D.
__REG32 PTE  : 1;     // Bit 4        -  Port E—The bit helps in masking the Port E interrupt. The bit clears during software reset of Port E.
__REG32 PTF  : 1;     // Bit 5        -  Port F—The bit helps in masking the Port F interrupt. The bit clears during software reset of Port F.
__REG32      :26;     // Bits 31 - 6  -  Reserved
} __PMASK_bits;

/* -------------------------------------------------------------------------*/
/*      Security Controller                                                 */
/* -------------------------------------------------------------------------*/
/* SCM Red Start Address Register */
typedef struct{
__REG32 RED_START  : 7;     
__REG32            :25;     
} __SCM_RED_START_bits;

/* SCM Black Start Address Register */
typedef struct{
__REG32 BLACK_START  : 7;     
__REG32              :25;     
} __SCM_BLACK_START_bits;

/* SCM Length Register */
typedef struct{
__REG32 LENGTH  : 7;     
__REG32         :25;     
} __SCM_LENGTH_bits;

/* SCM Control Register */
typedef struct{
__REG32 E_D    : 1;     
__REG32 E_C    : 1;     
__REG32 START  : 1;     
__REG32        :29;     
} __SCM_CONTROL_bits;

/* SCM Status Register */
typedef struct{
__REG32 Busy           : 1;     
__REG32 ClrMem         : 1;     
__REG32 Encr           : 1;     
__REG32 BlockAccess    : 1;     
__REG32 ClrFail        : 1;     
__REG32 BadKey         : 1;     
__REG32 InternError    : 1;     
__REG32 SecretKey      : 1;     
__REG32 IntStatus      : 1;     
__REG32 ClrComp        : 1;     
__REG32 EncrComp       : 1;     
__REG32 AccessAllowed  : 1;     
__REG32 EncrFail       : 1;     
__REG32                :19;     
} __SCM_STATUS_bits;

/* SCM Error Status Register */
typedef struct{
__REG32 Busy            : 1;     
__REG32 ClrMem          : 1;     
__REG32 Encr            : 1;     
__REG32 BlockAccess     : 1;     
__REG32 ClrFail         : 1;     
__REG32 BadKey          : 1;     
__REG32 InternError     : 1;     
__REG32 DefaultKey      : 1;     
__REG32 User            : 1;     
__REG32 IllegalAddress  : 1;     
__REG32 Byte            : 1;     
__REG32 Unalign         : 1;     
__REG32 Master          : 1;     
__REG32 Cacheable       : 1;     
__REG32                 :18;     
} __SCM_ERROR_bits;

/* SCM Interrupt Control Register */
typedef struct{
__REG32 IMASK    : 1;     
__REG32 CLR_INT  : 1;     
__REG32 CLR_MEM  : 1;     
__REG32          :29;     
} __SCM_INT_CTRL_bits;

/* SCM Configuration Register */
typedef struct{
__REG32 BLOCK_SIZE  : 7;     
__REG32 RED_SIZE    :10;     
__REG32 BLACK_SIZE  :10;     
__REG32 VERSION     : 5;     
} __SCM_CFG_bits;

/* SMN Status Register */
typedef struct{
__REG32 STATE     : 5;     
__REG32 BI        : 1;     
__REG32 ZF        : 1;     
__REG32 DA        : 1;     
__REG32 SE        : 1;     
__REG32 AE        : 1;     
__REG32 BE        : 1;     
__REG32 PE        : 1;     
__REG32 TE        : 1;     
__REG32 SA        : 1;     
__REG32 I         : 1;     
__REG32 SM        : 1;     
__REG32 VERSION0  : 3;     
__REG32 IA        : 1;     
__REG32 BK        : 1;     
__REG32 DK        : 1;     
__REG32 UM        : 1;     
__REG32 AD        : 1;     
__REG32 BY        : 1;     
__REG32 UA        : 1;     
__REG32 SC        : 1;     
__REG32 BM        : 1;     
__REG32 CA        : 1;     
__REG32 VERSION1  : 3;     
} __SMN_STATUS_bits;

/* SMN Command Register (R/W, Supervisor) */
typedef struct{
__REG32 SA  : 1;     
__REG32 EI  : 1;     
__REG32 CB  : 1;     
__REG32 CI  : 1;     
__REG32     :28;     
} __SMN_COMMAND_bits;

/* SMN Sequence Start Register */
typedef struct{
__REG32 START_VALUE  :16;     
__REG32              :16;     
} __SMN_SSR_bits;

/* SMN Sequence End Register */
typedef struct{
__REG32 END_VALUE  :16;     
__REG32            :16;     
} __SMN_SER_bits;

/* SMN Sequence Check Register */
typedef struct{
__REG32 CHECK_VALUE  :16;     
__REG32              :16;     
} __SMN_SCR_bits;

/* SMN Bit Count Register */
typedef struct{
__REG32 BITCNT  :11;     
__REG32         :21;     
} __SMN_BCR_bits;

/* SMN Increment Size Register */
typedef struct{
__REG32 INC_SIZE  :11;     
__REG32           :21;     
} __SMN_ISR_bits;

/* SMN Bit Bank Decrement Register */
typedef struct{
__REG32 DEC_AMT  :11;     
__REG32          :21;     
} __SMN_BBDR_bits;

/* SMN Compare Size Register */
typedef struct{
__REG32 SIZE  : 6;     
__REG32       :26;     
} __SMN_CSR_bits;

/* SMN Timer Control Register */
typedef struct{
__REG32 ST  : 1;     
__REG32 LD  : 1;     
__REG32     :30;     
} __SMN_TCR_bits;

/* SMN Debug Detector Register */
typedef struct{
__REG32 D1  : 1;     
__REG32 D2  : 1;     
__REG32 D3  : 1;     
__REG32 D4  : 1;     
__REG32 D5  : 1;     
__REG32 D6  : 1;     
__REG32 D7  : 1;     
__REG32 D8  : 1;     
__REG32 D9  : 1;     
__REG32 DA  : 1;     
__REG32 DB  : 1;     
__REG32 DC  : 1;     
__REG32     :20;     
} __SMN_DDR_bits;

/* -------------------------------------------------------------------------*/
/*      Run-Time Integrity Checker (RTIC)                                   */
/* -------------------------------------------------------------------------*/
/* RTIC Status Register */
typedef struct{
__REG32 BUSY            : 1;     
__REG32 HASH_DONE       : 1;     
__REG32 HASH_ERR        : 1;     
__REG32 WD_ERR          : 1;     
__REG32 MEMORY_INT_STA  : 4;     
__REG32 ADDRESS_ERROR   : 4;     
__REG32 LENGTH_ERROR    : 4;     
__REG32 DMAREQ          : 1;     
__REG32 RT_HASH_DONE    : 1;     
__REG32 SAM_STATUS      : 2;     
__REG32 SAM_BUF_LEVEL   : 5;     
__REG32 RTIC_STATE      : 2;     
__REG32 THRTL_START     : 1;     
__REG32 THRTL_DONE      : 1;     
__REG32                 : 3;     
} __RTICSR_bits;

/* RTIC Command Register */
typedef struct{
__REG32 CLR_IRQ       : 1;     
__REG32 SW_RST        : 1;     
__REG32 HASH_ONCE     : 1;     
__REG32 RUN_TIME_CHK  : 1;     
__REG32               :28;     
} __RTICMD_bits;

/* RTIC Control Register */
typedef struct{
__REG32 IRQ_EN            : 1;     
__REG32 DMA_BURST_SIZ     : 3;     
__REG32 HASH_ONCE_MEM_EN  : 4;     
__REG32 RUNTIME_MEM_EN    : 4;     
__REG32                   :20;     
} __RTICCNTLR_bits;

/* RTIC DMA Throttle/Bus Duty Cycle Register */
typedef struct{
__REG32 DELAY  :21;     
__REG32        :11;     
} __RTICTR_bits;

/* RTIC Watchdog Timeout Register */
typedef struct{
__REG32 DMA_WDOG  :21;     
__REG32           :11;     
} __RTICWR_bits;

/* -------------------------------------------------------------------------*/
/*      Random Number Generator Accelerator (RNGA)                          */
/* -------------------------------------------------------------------------*/
/* RNGA Control Register */
typedef struct{
__REG32 GO        : 1;     
__REG32 H_ASSURE  : 1;     
__REG32 INT_MASK  : 1;     
__REG32 CLR_INT   : 1;     
__REG32 SLEEP     : 1;     
__REG32           :27;     
} __RNGACR_bits;

/* RNGA Status Register */
typedef struct{
__REG32 SECURITY        : 1;     
__REG32 LAST_READ       : 1;     
__REG32 FIFO_UNDER      : 1;     
__REG32 ERROR_I         : 1;     
__REG32 SLEEP           : 1;     
__REG32                 : 3;     
__REG32 OUT_FIFO_LEVEL  : 8;     
__REG32 FIFO_SIZE       : 8;     
__REG32                 : 7;     
__REG32 OSC_DEAD        : 1;     
} __RNGASR_bits;

/* RNGA Mode Register */
typedef struct{
__REG32 VERIFY    : 1;     
__REG32 OSC_TEST  : 1;     
__REG32           :30;     
} __RNGAMR_bits;

/* RNGA Verification Control Register */
typedef struct{
__REG32 CLK_OFF       : 1;     
__REG32 FORCE_SYSCLK  : 1;     
__REG32 RST_SHFT      : 1;     
__REG32               :29;     
} __RNGAVCR_bits;

/* RNGA Oscillator Counter Control Register */
typedef struct{
__REG32 REMAINING_CLK_CYC  :18;     
__REG32                    :14;     
} __RNGAOCCR_bits;

/* RNGA Oscillator 1 & 2Counter Register */
typedef struct{
__REG32 COUNTER1  :20;     
__REG32           :12;     
} __RNGAOCR_bits;

/* RNGA Oscillator Counter Status Register */
typedef struct{
__REG32 OSC2  : 1;     
__REG32 OSC1  : 1;     
__REG32       :30;     
} __RNGAOCSR_bits;

/* -------------------------------------------------------------------------*/
/*               SDRAMC registers                                           */
/* -------------------------------------------------------------------------*/
typedef struct {        // SDRAM 0 Control Register (0xDF000000) Reset  (0x0100*0300)
                        // SDRAM 1 Control Register (0xDF000004) Reset  (0x0100*0300)
__REG32 SRC    : 4;     // Bit  0  - 3  - SDRAM Row Cycle Delay
__REG32 SRCD   : 2;     // Bit  4-5     - SDRAM Row-to-Column Delay
__REG32 SRP    : 1;     // Bit  6       - SDRAM Row Precharge Delay
__REG32        : 1;     // Bit  7       - reserved
__REG32 SCL    : 2;     // Bits 8-9     - SDRAM CAS Latency
__REG32 CI     : 2;     // Bits 10-11   - Cache Inhibit
__REG32 PWDT   : 2;     // Bit  12-13   - Power-Down Timeout
__REG32 SREFR  : 2;     // Bit  14-15   - SDRAM Refresh Rate
__REG32 DSIZ   : 2;     // Bits 16-17   - SDRAM Memory Data Width
__REG32        : 1;     // Bit  18      - reserved
__REG32 IAM    : 1;     // Bit  19      - (Bank 1 ) Interleaved Address Mode
__REG32 COL    : 2;     // Bit  20-21   - Column Address Width
__REG32        : 2;     // Bits 22-23   - reserved
__REG32 ROW    : 2;     // Bits 24-25   - Row Address Width
__REG32        : 1;     // Bit  26      - reserved
__REG32 SP     : 1;     // Bits 27      - Supervisor Protect
__REG32 SMODE  : 3;     // Bits 28-30   - SDRAM Controller Operating Mode
__REG32 SDE    : 1;     // Bit  31      - SDRAM Controller Enable
} __SDCTL_bits;

typedef struct {        // SDRAM Reset register (0xDF000018) Reset (0x00000000)
__REG32      :30;     // Bits 0-29    - reserved
__REG32 RST  : 2;     // Bit  30-31   - Software Initiated Local Module Reset Bits
} __SDRST_bits;

typedef struct {        // SDRAM Reset register (0xDF000014) Reset (0x00000000)
__REG32 RMA0  : 1;     // Bit  0       - MA0 Replacement
__REG32       :30;     // Bits 1-30    - reserved
__REG32 OMA   : 1;     // Bit  31      - Multiplexed Address Override
} __MISC_bits;

/* -------------------------------------------------------------------------*/
/*               DMA Registers                                              */
/* -------------------------------------------------------------------------*/
typedef struct {        /* DMA Control Register (0x10001000) Reset (0x0000)                     */
__REG32 DEN   : 1;     // Bit  0       - DMA Enable - Enables/Disables the system clock to the DMA module.
__REG32 DRST  : 1;     // Bit  1       - DMA Reset - Writing "1" Generates a 3-cycle reset pulse that resets the entire DMA module
__REG32 DAM   : 1;     // Bit  2       - DMA Access Mode—Specifies user or privileged access to be performed by DMA.
__REG32       :29;     // Bits 31 - 3  - Reserved
} __DCR_bits;

typedef struct {        /* DMA Register Type                                                                            */
__REG32 CH0   : 1;     // Bit 0        - Channel 0
__REG32 CH1   : 1;     // Bit 1        - Channel 1
__REG32 CH2   : 1;     // Bit 2        - Channel 2
__REG32 CH3   : 1;     // Bit 3        - Channel 3
__REG32 CH4   : 1;     // Bit 4        - Channel 4
__REG32 CH5   : 1;     // Bit 5        - Channel 5
__REG32 CH6   : 1;     // Bit 6        - Channel 6
__REG32 CH7   : 1;     // Bit 7        - Channel 7
__REG32 CH8   : 1;     // Bit 8        - Channel 8
__REG32 CH9   : 1;     // Bit 9        - Channel 9
__REG32 CH10  : 1;     // Bit 10       - Channel 10
__REG32 CH11  : 1;     // Bit 11       - Channel 11
__REG32 CH12  : 1;     // Bit 12       - Channel 12
__REG32 CH13  : 1;     // Bit 13       - Channel 13
__REG32 CH14  : 1;     // Bit 14       - Channel 14
__REG32 CH15  : 1;     // Bit 15       - Channel 15
__REG32       :16;     // Bits 31-16   - Reserved
} __DISR_bits;

typedef struct {        /* DMA Burst Time-Out Control Register (0x1000101C) Reset (0x00000000) */
__REG32 CNT  :15;     // Bits 14 - 0  - Count - Contains the time-out count down value.
__REG32 EN   : 1;     // Bit  15      - Enable - (0 = burst time-out Disabled, 1 = burst time-out Enabled)
__REG32      :16;     // Bits 31 - 16  - Reserved
} __DBTOCR_bits;

typedef struct {        /* W-Size Register */
__REG32 WS  :16;     // Bits 15-0    - W-Size - Contains the number of bytes that make up the display width.
__REG32     :16;     // Bits 31-16   - Reserved
} __WSR_bits;

typedef struct {        /* X-Size Registers */
__REG32 XS  :16;     // Bits 15-0    - X-Size - Contains the number of bytes per row that define the X-Size of the 2D memory.
__REG32     :16;     // Bits 31-16   - Reserved
} __XSR_bits;

typedef struct {        /* Y-Size Registers */
__REG32 YS  :16;     // Bits 15-0    - Y-Size - Contains the number of rows that make up the 2D memory window.
__REG32     :16;     // Bits 31-16   - Reserved
} __YSR_bits;

typedef struct {        /* Channel Source Address Register */
__REG32 SA0  : 1;     
__REG32 SA1  : 1;     
__REG32 SA   :30;     
} __SAR_bits;

typedef struct {        /* Destination Address Registers */
__REG32 DA0  : 1;     
__REG32 DA1  : 1;     
__REG32 DA   :30;     
} __DAR_bits;

typedef struct {        /* DMA Channel Count Register */
__REG32 CNT  :24;     // Bits 23 - 0  - Count - Contains the number of bytes of data to be transferred during a DMA cycle.
__REG32      : 8;     // Bits 31 - 24 - Reserved
} __CNTR_bits;

typedef struct {        /* DMA Channel Control Register */
__REG32 CEN    : 1;     // Bit  0       - DMA Channel Enable (0 = Disables, 1 = Enable)
__REG32 FRC    : 1;     // Bit  1       - Forces a DMA Cycle to occur (0=No Effect, 1=Force DMA cycle)
__REG32 RPT    : 1;     // Bit  2       - Repeat - Enables(1)/Disables(0) the data transfer repeat function.
__REG32 REN    : 1;     // Bit  3       - Request Enable - Enables(1)/Disables(0) the DMA request signal. When REN is set, DMA is started by DMA_REQ[x] signal. When REN is cleared, DMA transfer is initiated by CEN
__REG32 SSIZ   : 2;     // Bits 5  - 4  - Source Size - Selects the source size of data transfer. (00=32 Bit port, 01=8-bit port, 10=16-bit port, 11=reserved)
__REG32 DSIZ   : 2;     // Bits 7  - 6  - Destination Size - Selects the destination size of a data (00=32 Bit port, 01=8-bit port, 10=16-bit port, 11=reserved)
__REG32 MSEL   : 1;     // Bit  8       - Memory Select - Selects the 2D memory register set when either source and/or destination is programmed to 2D memory mode. (0=2D memory register set A, 1=2D mem reg set B)
__REG32 MDIR   : 1;     // Bit  9       - Memory Direction - Selects the memory address direction. (0 = Memory address increment, 1 = Memory address decrement)
__REG32 SMOD   : 2;     // Bits 11 - 10 - Source Mode - Selects the source transfer mode (00=Linear Memory, 01=2D Memory, 10=FIFO, 11=End-of-burst enable FIFO)
__REG32 DMOD   : 2;     // Bits 13 - 12 - Destination Mode - Selects the destination transfer mode. (00=Linear Memory, 01=2D Memory, 10=FIFO, 11=End-of-burst enable FIFO)
__REG32 ACRPT  : 1;     // Bits 14      - Auto Clear RPT—This bit is to be sampled at the end of the transfer along with the RPT bit (0 = Do not modify RPT, 1 = Reset RPT at end of current transfer.)
__REG32        :17;     // Bits 31 - 15 - Reserved
} __CCR_bits;

typedef struct {        /* DMA Channel Request Source Select Register */
__REG32 RSS  : 5;     // Bits 4  - 0  - Request Source Select (0=DMA_REQ[0]....31=DMA_REQ[31])
__REG32      :27;     // Bits 31 - 5  - Reserved
} __RSSR_bits;

typedef struct {        /* DMA Channel Burst Length Register */
__REG32 BL  : 6;     // Bits 6  - 0  - Burst Length - Contains the number of data bytes transferred in a DMA burst. (0=64 bytes, 1=1 byte...63 = 63 bytes)
__REG32     :26;     // Bits 31 - 6  - Reserved
} __BLR_bits;

typedef union{
  //RTORx
  struct{
__REG32 CNT     :13;     // Bits 12 - 0  - Request Time-Out Count - Contains the time-out count down value for the internal counter.
__REG32 PSC     : 1;     // Bit  13      - Prescaler Count (0=/1, 1=/256)
__REG32 CLK     : 1;     // Bit  14      - Clock Source - Selects the counter of input clock source. (0 = HCLK, 1 = 32.768 kHz)
__REG32 EN      : 1;     // Bit  15      - Enable - Enables/Disables the DMA request time-out.
__REG32         :16;     // Bits 31 - 16 - Reserved
  };
  //BUCRx
  struct {
__REG32 BU_CNT  :16;     // Bits 15 - 0  - Clock Count - Sets the number of system clocks that must occur before the memory channel releases the AHB, before the next DMA request for the channel.
__REG32         :16;     // Bits 31 - 16 - Reserved
  };
} __RTOR_bits;

typedef struct {        /* DMA Channel Counter Register */
__REG32 CCNR  :24;     // Bits 23 - 0  - Channel Counter—Indicates the number of bytes transferred for the channel.
__REG32       : 8;     // Bits 31 - 24 - Reserved
} __CCNR_bits;

/* -------------------------------------------------------------------------*/
/*               NAND Flash Memory Controller (NANDFC)                      */
/* -------------------------------------------------------------------------*/
/* Internal SRAM Size */
typedef struct{
__REG16 BUFSIZE  : 4;     
__REG16          :12;     
} __NFC_BUFSIZE_bits;

/* Buffer Number for Page Data Transfer To/From Flash Memory */
typedef struct{
__REG16 RBA  : 2;     
__REG16      :14;     
} __NFC_RBA_bits;

/* NFC Internal Buffer Lock Control */
typedef struct{
__REG16 BLS  : 2;     
__REG16      :14;     
} __NFC_IBLC_bits;

/* NFC Controller Status/Result of Flash Operation */
typedef struct{
__REG16 ERS  : 2;     
__REG16 ERM  : 2;     
__REG16      :12;     
} __ECC_SRR_bits;

/* NFC ECC Error Position of Main Area Data Error */
typedef union{
  //ECC_RSLT_MA 8bit
  struct {
__REG16 ECC8_RESULT2   : 3;     
__REG16 ECC8_RESULT1   : 9;     
__REG16                : 4;     
  };
  //ECC_RSLT_MA 16bit
  struct {
__REG16 ECC16_RESULT2  : 4;     
__REG16 ECC16_RESULT1  : 8;     
__REG16                : 4;     
  };
} __ECC_RSLT_MA_bits;

/* NFC ECC Error Position of Spare Area Data Error */
typedef union{
  //ECC_RSLT_SA 8bit
  struct {
__REG16 ECC8_RESULT3   : 3;     
__REG16 ECC8_RESULT4   : 2;     
__REG16                :11;     
  };
  //ECC_RSLT_SA 16bit
  struct {
__REG16 ECC16_RESULT3  : 4;     
__REG16 ECC16_RESULT4  : 1;     
__REG16                :11;     
  };
} __ECC_RSLT_SA_bits;

/* NFC Nand Flash Write Protection */
typedef struct{
__REG16 WPC  : 3;     
__REG16      :13;     
} __NF_WR_PROT_bits;

/* NFC NAND Flash Write Protection Status */
typedef struct{
__REG16 LTS  : 1;     
__REG16 LS   : 1;     
__REG16 US   : 1;     
__REG16      :13;     
} __NF_WR_PROT_STA_bits;

/* NFC NAND Flash Operation Configuration 1 */
typedef struct{
__REG16           : 2;     
__REG16 SP_EN     : 1;     
__REG16 ECC_EN    : 1;     
__REG16 INT_MASK  : 1;     
__REG16           :11;     
} __NAND_FC1_bits;

/* NFC NAND Flash Operation Configuration 2 */
typedef struct{
__REG16 FCMD  : 1;     
__REG16 FADD  : 1;     
__REG16 FDI   : 1;     
__REG16 FDO   : 3;     
__REG16       : 9;     
__REG16 INT   : 1;     
} __NAND_FC2_bits;

/* -------------------------------------------------------------------------*/
/*               EIM registers                                              */
/* -------------------------------------------------------------------------*/
/* Chip Select 0 - 5 Upper Control Register */
typedef struct{
__REG32 EDC      : 4;     
__REG32 WWS      : 3;     
__REG32 EW       : 1;     
__REG32 WSC      : 6;     
__REG32 CNC      : 2;     
__REG32 DOL_RWN  : 4;     
__REG32 SYNC     : 1;     
__REG32 PME      : 1;     
__REG32 PSZ      : 2;     
__REG32 BCS_RWA  : 4;     
__REG32 BCD_DCT  : 2;     
__REG32 WP       : 1;     
__REG32 SP       : 1;     
} __CSU_bits;

/* Chip Select 0 - 5 Lower Control Register */
typedef struct{
__REG32 CSEN  : 1;     
__REG32 WRAP  : 1;     
__REG32 CRE   : 1;     
__REG32 PSR   : 1;     
__REG32 CSN   : 4;     
__REG32 DSZ   : 3;     
__REG32 EBC   : 1;     
__REG32 CSA   : 4;     
__REG32 WEN   : 4;     
__REG32 WEA   : 4;     
__REG32 OEN   : 4;     
__REG32 OEA   : 4;     
} __CSL_bits;

/* EIM Configuration Register */
typedef struct{
__REG32      : 1;     
__REG32 AGE  : 1;     
__REG32 BCM  : 1;     
__REG32      :29;     
} __EIM_bits;

/* -------------------------------------------------------------------------*/
/*      Bus Master Interface (BMI)                                          */
/* -------------------------------------------------------------------------*/
/* BMI Control Register 1 */
typedef struct{
__REG32 BMI_EN          : 1;     
__REG32 TXFIFO_CLR      : 1;     
__REG32 RXFIFO_CLR      : 1;     
__REG32 _16BIT_SEL      : 1;     
__REG32 READ_REQ_POL    : 1;     
__REG32 CLK_CS_POL      : 1;     
__REG32 MMD_MODE_SEL    : 1;     
__REG32 TXFE_INT_EN     : 1;     
__REG32 RXFF_INT_EN     : 1;     
__REG32 WRDY_INT_EN     : 1;     
__REG32 BRDY_INT_EN     : 1;     
__REG32 RXF_OV_INT_EN   : 1;     
__REG32 MASTER_SEL      : 1;     
__REG32 READ            : 1;     
__REG32 MMD_CLKOUT      : 1;     
__REG32 DATA_LATCH      : 1;     
__REG32 RXF_Water_Mark  : 4;     
__REG32 TXF_Water_Mark  : 4;     
__REG32 DIV             : 2;     
__REG32 WS              : 3;     
__REG32 WAIT            : 1;     
__REG32                 : 2;     
} __BMICTLR1_bits;

/* BMI Control Register 2 */
typedef struct{
__REG32 COUNT  : 6;     
__REG32        :26;     
} __BMICTLR2_bits;

/* BMI Status Register */
typedef struct{
__REG32 BCNT       : 2;     
__REG32 TXF_EMPTY  : 1;     
__REG32 RXF_FULL   : 1;     
__REG32 WRDY       : 1;     
__REG32 BRDY       : 1;     
__REG32 RXF_OV     : 1;     
__REG32 TA         : 1;     
__REG32            :24;     
} __BMISR_bits;

/* -------------------------------------------------------------------------*/
/*               I2C registers                                                  */
/* -------------------------------------------------------------------------*/
typedef struct {        /* I2C Address Register  */
__REG32      : 1;     // Bit  0       - reserved
__REG32 ADR  : 7;     // Bits 1  - 7  - Slave Address - Contains the specific slave address to be used by the I2C module.
__REG32      :24;     // Bits 31 - 8  - Reserved
} __IADR_bits;

typedef struct {        /* I2C Frequency Divider Register (IFDR) */
__REG32 IC  : 6;     // Bits 0  - 5  - I2C Clock Rate Divider - Prescales the clock for bit-rate selection.
__REG32     :26;     // Bits 31 - 6  - Reserved
} __IFDR_bits;

typedef struct {        /* I2C Control Register (I2CR) */
__REG32       : 2;     // Bits 0  - 1  - Reserved
__REG32 RSTA  : 1;     // Bit  2       - Repeated START - Generates a repeated START condition
__REG32 TXAK  : 1;     // Bit  3       - Transmit Acknowledge Enable (0 = Send ACK, 1 = Dont send ACK)
__REG32 MTX   : 1;     // Bit  4       - Transmit/Receive Mode Select (0 = Rx, 1 = Tx)
__REG32 MSTA  : 1;     // Bit  5       - Master/Slave Mode Select (0 = Slave, 1 = Master)
__REG32 IIEN  : 1;     // Bit  6       - I2C Interrupt Enable
__REG32 IEN   : 1;     // Bit  7       - I2C Enable
__REG32       :24;     // Bits 8 - 31  - Reserved
} __I2CR_bits;

typedef struct {        /* I2C Status Register (I2SR) */
__REG32 RXAK  : 1;     // Bit  0       - Received Acknowledge (0 = ACK received, 1 = No ACK received)
__REG32 IIF   : 1;     // Bit  1       - I2C interrupt - (0 = No Int. pending, 1 = Interrupt pending )
__REG32 SRW   : 1;     // Bit  2       - Slave Read/Write - Indicates the value of the R/W command bit
__REG32       : 1;     // Bit  3       - Reserved
__REG32 IAL   : 1;     // Bit  4       - Arbitration Lost
__REG32 IBB   : 1;     // Bit  5       - I2C Bus Busy
__REG32 IAAS  : 1;     // Bit  6       - I2C Addressed As a Slave
__REG32 ICF   : 1;     // Bit  7       - Data Transfer (0=In Progress, 1 = Complete)
__REG32       :24;     // Bits 8  - 31 - Reserved
} __I2SR_bits;

typedef struct {        /* I2C Data I/O Register (I2DR) */
__REG32 DATA  : 8;     // Bits 0  - 7  - I2C Data to be transmitted / last byte received
__REG32       :24;     // Bits 8 - 31  - Reserved
} __I2DR_bits;

/* -------------------------------------------------------------------------*/
/*      SPI Registers                                                       */
/* -------------------------------------------------------------------------*/
/* SPI control registers */
typedef struct{
__REG32 BIT_COUNT   : 5;     
__REG32 POL         : 1;     
__REG32 PHA         : 1;     
__REG32 SSCTL       : 1;     
__REG32 SSPOL       : 1;     
__REG32 XCH         : 1;     
__REG32 SPIEN       : 1;     
__REG32 MODE        : 1;     
__REG32 DRCTL       : 2;     
__REG32 DATARATE    : 5;     
__REG32 CS          : 2;     
__REG32 SWAP        : 1;     
__REG32 SDHC_SPIEN  : 1;     
__REG32 BURST       : 1;     
__REG32             : 8;     
} __CONTROLREG_bits;

/* SPI interrupt control/status registers */
typedef struct{
__REG32 TE       : 1;     
__REG32 TH       : 1;     
__REG32 TF       : 1;     
__REG32 TSHFE    : 1;     
__REG32 RR       : 1;     
__REG32 RH       : 1;     
__REG32 RF       : 1;     
__REG32 RO       : 1;     
__REG32 BO       : 1;     
__REG32 TEEN     : 1;     
__REG32 THEN     : 1;     
__REG32 TFEN     : 1;     
__REG32 TSHFEEN  : 1;     
__REG32 RREN     : 1;     
__REG32 RHEN     : 1;     
__REG32 RFEN     : 1;     
__REG32 ROEN     : 1;     
__REG32 BOEN     : 1;     
__REG32          :14;     
} __INTREG_bits;

/* SPI test registers */
typedef struct{
__REG32 TXCNT      : 4;     
__REG32 RXCNT      : 4;     
__REG32 SSTATUS    : 4;     
__REG32 SS_ASSERT  : 1;     
__REG32 INIT       : 1;     
__REG32 LBC        : 1;     
__REG32            :17;     
} __TESTREG_bits;

/* SPI sample period control registers */
typedef struct{
__REG32 WAIT  :15;     
__REG32 CSRC  : 1;     
__REG32       :16;     
} __PERIODREG_bits;

/* SPI DMA control registers */
typedef struct{
__REG32        : 4;     
__REG32 RHDMA  : 1;     
__REG32 RFDMA  : 1;     
__REG32 TEDMA  : 1;     
__REG32 THDMA  : 1;     
__REG32        : 4;     
__REG32 RHDEN  : 1;     
__REG32 RFDEN  : 1;     
__REG32 TEDEN  : 1;     
__REG32 THDEN  : 1;     
__REG32        :16;     
} __DMAREG_bits;

/* SPI soft reset registers */
typedef struct{
__REG32 START  : 1;     
__REG32        :31;     
} __RESETREG_bits;

/* -------------------------------------------------------------------------*/
/*               SSI registers                                              */
/* -------------------------------------------------------------------------*/
/* SSI Data register */
typedef struct{
__REG32 DATA  :24;     
__REG32       : 8;     
} __SSI_DATA_bits;

/* SSI Control/Status Register */
typedef struct{
__REG32 SSIEN       : 1;     
__REG32 TE          : 1;     
__REG32 RE          : 1;     
__REG32 NET         : 1;     
__REG32 SYN         : 1;     
__REG32 I2S_MODE    : 2;     
__REG32 SYS_CLK_EN  : 1;     
__REG32 TCH_EN      : 1;     
__REG32 CLK_IST     : 1;     
__REG32             :22;     
} __SCSR_bits;

/* SSI Interrupt Status Register */
typedef struct{
__REG32 TFE0   : 1;     
__REG32 TFE1   : 1;     
__REG32 RFF0   : 1;     
__REG32 RFF1   : 1;     
__REG32 RLS    : 1;     
__REG32 TLS    : 1;     
__REG32 RFS    : 1;     
__REG32 TFS    : 1;     
__REG32 TUE0   : 1;     
__REG32 TUE1   : 1;     
__REG32 ROE0   : 1;     
__REG32 ROE1   : 1;     
__REG32 TDE0   : 1;     
__REG32 TDE1   : 1;     
__REG32 RDR0   : 1;     
__REG32 RDR1   : 1;     
__REG32 RXT    : 1;     
__REG32 CMDDU  : 1;     
__REG32 CMDAU  : 1;     
__REG32        :13;     
} __SISR_bits;

/* SSI Interrupt Enable Register */
typedef struct{
__REG32 TFE0_EN   : 1;     
__REG32 TFE1_EN   : 1;     
__REG32 RFF0_EN   : 1;     
__REG32 RFF1_EN   : 1;     
__REG32 RLS_EN    : 1;     
__REG32 TLS_EN    : 1;     
__REG32 RFS_EN    : 1;     
__REG32 TFS_EN    : 1;     
__REG32 TUE0_EN   : 1;     
__REG32 TUE1_EN   : 1;     
__REG32 ROE0_EN   : 1;     
__REG32 ROE1_EN   : 1;     
__REG32 TDE0_EN   : 1;     
__REG32 TDE1_EN   : 1;     
__REG32 RDR0_EN   : 1;     
__REG32 RDR1_EN   : 1;     
__REG32 RXT_EN    : 1;     
__REG32 CMDDU_EN  : 1;     
__REG32 CMDAU_EN  : 1;     
__REG32 TIE       : 1;     
__REG32 TDMAE     : 1;     
__REG32 RIE       : 1;     
__REG32 RDMAE     : 1;     
__REG32           : 9;     
} __SIER_bits;

/* SSI Transmit Configuration Register */
typedef struct{
__REG32 TEFS    : 1;     
__REG32 TFSL    : 1;     
__REG32 TFSI    : 1;     
__REG32 TSCKP   : 1;     
__REG32 TSHFD   : 1;     
__REG32 TXDIR   : 1;     
__REG32 TFDIR   : 1;     
__REG32 TFEN0   : 1;     
__REG32 TFEN1   : 1;     
__REG32 TXBIT0  : 1;     
__REG32         :22;     
} __STCR_bits;

/* SSI Receive Configuration Register */
typedef struct{
__REG32 REFS    : 1;     
__REG32 RFSL    : 1;     
__REG32 RFSI    : 1;     
__REG32 RSCKP   : 1;     
__REG32 RSHFD   : 1;     
__REG32 RXDIR   : 1;     
__REG32 RFDIR   : 1;     
__REG32 RFEN0   : 1;     
__REG32 RFEN1   : 1;     
__REG32 RXBIT0  : 1;     
__REG32         :22;     
} __SRCR_bits;

/* SSI Clock Control Register */
typedef struct{
__REG32 PM    : 8;     
__REG32 DC    : 5;     
__REG32 WL    : 4;     
__REG32 PSR   : 1;     
__REG32 DIV2  : 1;     
__REG32       :13;     
} __SSI_CCR_bits;

/* SSI FIFO Control/Status Register */
typedef struct{
__REG32 TFWM0   : 4;     
__REG32 RFWM0   : 4;     
__REG32 TFCNT0  : 4;     
__REG32 RFCNT0  : 4;     
__REG32 TFWM1   : 4;     
__REG32 RFWM1   : 4;     
__REG32 TFCNT1  : 4;     
__REG32 RFCNT1  : 4;     
} __SSI_SFCSR_bits;

/* SSI Test Register */
typedef struct{
__REG32 TXSTATE  : 5;     
__REG32 TFS2RFS  : 1;     
__REG32 TCK2RCK  : 1;     
__REG32 TXD2RXD  : 1;     
__REG32 RXSTATE  : 5;     
__REG32 RFS2TFS  : 1;     
__REG32 RCK2TCK  : 1;     
__REG32 TEST     : 1;     
__REG32          :16;     
} __SSI_STR_bits;

/* SSI Option Register */
typedef struct{
__REG32 SYNRST  : 1;     
__REG32 WAIT    : 2;     
__REG32 INIT    : 1;     
__REG32 TX_CLR  : 1;     
__REG32 RX_CLR  : 1;     
__REG32 CLKOFF  : 1;     
__REG32         :25;     
} __SSI_SOR_bits;

/* SSI AC97 Control Register */
typedef struct{
__REG32 A97EN  : 1;     
__REG32 FV     : 1;     
__REG32 TIF    : 1;     
__REG32 RD     : 1;     
__REG32 WR     : 1;     
__REG32 FRDIV  : 6;     
__REG32        :21;     
} __SSI_SACNT_bits;

/* SSI AC97 Command Address Register */
typedef struct{
__REG32 SACADD  :19;     
__REG32         :13;     
} __SSI_SACADD_bits;

/* SSI AC97 Command Data Register */
typedef struct{
__REG32 SACDAT  :19;     
__REG32         :13;     
} __SSI_SACDAT_bits;

/* SSI AC97 Tag Register */
typedef struct{
__REG32 SATAG  :16;     
__REG32        :16;     
} __SSI_SATAG_bits;

/* -------------------------------------------------------------------------*/
/*               CSI  registers                                             */
/* -------------------------------------------------------------------------*/
/* CSI Control Register 1 */
typedef struct{
__REG32               : 1;     
__REG32 REDGE         : 1;     
__REG32 INV_PCLK      : 1;     
__REG32 INV_DATA      : 1;     
__REG32 GCLK_MODE     : 1;     
__REG32 CLR_RXFIFO    : 1;     
__REG32 CLR_STATFIFO  : 1;     
__REG32 PACK_DIR      : 1;     
__REG32 FCC           : 1;     
__REG32 MCLKEN        : 1;     
__REG32 CCIR_EN       : 1;     
__REG32 HSYNC_POL     : 1;     
__REG32 MCLKDIV       : 4;     
__REG32 SOF_INTEN     : 1;     
__REG32 SOF_POL       : 1;     
__REG32 RXFF_INTEN    : 1;     
__REG32 RXFF_LEVEL    : 2;     
__REG32 STATFF_INTEN  : 1;     
__REG32 STATFF_LEVEL  : 2;     
__REG32 RF_OR_INTEN   : 1;     
__REG32 SF_OR_INTEN   : 1;     
__REG32 COF_INT_E     : 1;     
__REG32 CCIR_MODE     : 1;     
__REG32 PRP_IF_EN     : 1;     
__REG32 EOF_INT_EN    : 1;     
__REG32 EXT_VSYNC     : 1;     
__REG32 SWAP16_EN     : 1;     
} __CSICR1_bits;

/* CSI Control Register 2 */
typedef struct{
__REG32 HSC   : 8;     
__REG32 VSC   : 8;     
__REG32 LVRM  : 3;     
__REG32 BTS   : 2;     
__REG32       : 2;     
__REG32 SCE   : 1;     
__REG32 AFS   : 2;     
__REG32 DRM   : 1;     
__REG32       : 5;     
} __CSICR2_bits;

/* CSI Control Register 3 */
typedef struct{
__REG32 ECC_AUTO_EN   : 1;     
__REG32 ECC_INT_EN    : 1;     
__REG32 ZERO_PACK_EN  : 1;     
__REG32 CSI_SVR       : 1;     
__REG32               :11;     
__REG32 FRMCNT_RST    : 1;     
__REG32 FRMCNT        :16;     
} __CSICR3_bits;

/* CSI Status Register */
typedef struct{
__REG32 DRDY        : 1;     
__REG32 ECC_INT     : 1;     
__REG32             :11;     
__REG32 COF_INT     : 1;     
__REG32 F1_INT      : 1;     
__REG32 F2_INT      : 1;     
__REG32 SOF_INT     : 1;     
__REG32 EOF_INT     : 1;     
__REG32 RXFF_INT    : 1;     
__REG32             : 2;     
__REG32 STATFF_INT  : 1;     
__REG32             : 2;     
__REG32 RFF_OR_INT  : 1;     
__REG32 SFF_OR_INT  : 1;     
__REG32             : 6;     
} __CSISR_bits;

/* CSI RX Count Register */
typedef struct{
__REG32 RXCNT  :22;     
__REG32        :10;     
} __CSIRXCNT_bits;

/* -------------------------------------------------------------------------*/
/*      LCDC Registers                                                       */
/* -------------------------------------------------------------------------*/
/* LCDC Screen Start Address Register*/
typedef struct{
__REG32      : 2;     
__REG32 SSA  :30;     
} __SSA_bits;

/* LCDC Size Register */
typedef struct{
__REG32 YMAX  :10;     
__REG32       :10;     
__REG32 XMAX  : 6;     
__REG32       : 6;     
} __LSR_bits;

/* LCDC Virtual Page Width Register */
typedef struct{
__REG32 VPW  :10;     
__REG32      :22;     
} __LVPWR_bits;

/* LCDC Panel Configuration Register */
typedef struct{
__REG32 PCD        : 6;     
__REG32 SHARP      : 1;     
__REG32 SCLK_SEL   : 1;     
__REG32 ACD        : 7;     
__REG32 ACD_SEL    : 1;     
__REG32 REV_VS     : 1;     
__REG32 SWAP_SEL   : 1;     
__REG32 END_SEL    : 1;     
__REG32 SCLK_IDLE  : 1;     
__REG32 OE_POL     : 1;     
__REG32 CLK_POL    : 1;     
__REG32 LP_POL     : 1;     
__REG32 FLM_POL    : 1;     
__REG32 PIX_POL    : 1;     
__REG32 BPIX       : 3;     
__REG32 PBSIZ      : 2;     
__REG32 COLOR      : 1;     
__REG32 TFT        : 1;     
} __LPCR_bits;

/* LCDC Horizontal Configuration Register */
typedef struct{
__REG32 H_WAIT_2  : 8;     
__REG32 H_WAIT_1  : 8;     
__REG32           :10;     
__REG32 H_WIDTH   : 6;     
} __LHCR_bits;

/* LCDC Vertical Configuration Register */
typedef struct{
__REG32 V_WAIT_2  : 8;     
__REG32 V_WAIT_1  : 8;     
__REG32           :10;     
__REG32 V_WIDTH   : 6;     
} __LVCR_bits;

/* LCDC Panning Offset Register */
typedef struct{
__REG32 POS  : 5;     
__REG32      :27;     
} __LPOR_bits;

/* LCDC Cursor Position Register */
typedef struct{
__REG32 CYP  :10;     
__REG32      : 6;     
__REG32 CXP  :10;     
__REG32      : 2;     
__REG32 OP   : 1;     
__REG32      : 1;     
__REG32 CC   : 2;     
} __LCPR_bits;

/* LCDC Cursor Width Height and Blink Register */
typedef struct{
__REG32 BD     : 8;     
__REG32        : 8;     
__REG32 CH     : 5;     
__REG32        : 3;     
__REG32 CW     : 5;     
__REG32        : 2;     
__REG32 BK_EN  : 1;     
} __LCWHB_bits;

/* LCDC Color Cursor Mapping Register */
typedef struct{
__REG32 CUR_COL_B  : 6;     
__REG32 CUR_COL_G  : 6;     
__REG32 CUR_COL_R  : 6;     
__REG32            :14;     
} __LCCMR_bits;

/* LCDC Sharp Configuration Register */
typedef struct{
__REG32 GRAY1             : 4;     
__REG32 GRAY2             : 4;     
__REG32 REV_TOGGLE_DELAY  : 4;     
__REG32                   : 4;     
__REG32 CLS_RISE_DELAY    : 8;     
__REG32                   : 2;     
__REG32 PS_RISE_DELAY     : 6;     
} __LSCR_bits;

/* LCDC PWM Contrast Control Register */
typedef struct{
__REG32 PW            : 8;     
__REG32 CC_EN         : 1;     
__REG32 SCR           : 2;     
__REG32               : 4;     
__REG32 LDMSK         : 1;     
__REG32 CLS_HI_WIDTH  : 9;     
__REG32               : 7;     
} __LPCCR_bits;

/* LCDC Refresh Mode Control Register */
typedef struct{
__REG32 SELF_REF  : 1;     
__REG32           :31;     
} __LRMCR_bits;

/* LCDC Graphic Window DMA Control Register */
typedef struct{
__REG32 TM     : 5;     
__REG32        :11;     
__REG32 HM     : 5;     
__REG32        :10;     
__REG32 BURST  : 1;     
} __LDCR_bits;

/* LCDC Interrupt Configuration Register */
typedef struct{
__REG32 INTCON      : 1;     
__REG32             : 1;     
__REG32 INTSYN      : 1;     
__REG32             : 1;     
__REG32 GW_INT_CON  : 1;     
__REG32             :27;     
} __LICR_bits;

/* LCDC Interrupt Configuration Register */
typedef struct{
__REG32 BOF_EN         : 1;     
__REG32 EOF_EN         : 1;     
__REG32 ERR_RES_EN     : 1;     
__REG32 UDR_ERR_EN     : 1;     
__REG32 GW_BOF_EN      : 1;     
__REG32 GW_EOF_EN      : 1;     
__REG32 GW_ERR_RES_EN  : 1;     
__REG32 GW_UDR_ERR_EN  : 1;     
__REG32                :24;     
} __LIER_bits;

/* LCDC Interrupt Status Register */
typedef struct{
__REG32 BOF         : 1;     
__REG32 EOFR        : 1;     
__REG32 ERR_RES     : 1;     
__REG32 UDR_ERR     : 1;     
__REG32 GW_BOF      : 1;     
__REG32 GW_EOF      : 1;     
__REG32 GW_ERR_RES  : 1;     
__REG32 GW_UDR_ERR  : 1;     
__REG32             :24;     
} __LISR_bits;

/* LCDC Graphic Window Start Address Register */
typedef struct{
__REG32       : 2;     
__REG32 GWSA  :30;     
} __LGWSAR_bits;

/* LCDC Graphic Window Size Register */
typedef struct{
__REG32 GWH  :10;     
__REG32      :10;     
__REG32 GWW  : 6;     
__REG32      : 6;     
} __LGWSR_bits;

/* LCDC Graphic Window Virtual Page Width Register */
typedef struct{
__REG32 GWVPW  :10;     
__REG32        :22;     
} __LGWVPWR_bits;

/* LCDC Graphic Window Panning Offset Register */
typedef struct{
__REG32 GWPO  : 5;     
__REG32       :27;     
} __LGWPOR_bits;

/* LCDC Graphic Window Position Register */
typedef struct{
__REG32 GWYP  :10;     
__REG32       : 6;     
__REG32 GWXP  :10;     
__REG32       : 6;     
} __LGWPR_bits;

/* LCDC Graphic Window Control Register */
typedef struct{
__REG32 GWCKB   : 6;     
__REG32 GWCKG   : 6;     
__REG32 GWCKR   : 6;     
__REG32         : 3;     
__REG32 GW_RVS  : 1;     
__REG32 GWE     : 1;     
__REG32 GWCKE   : 1;     
__REG32 GWAV    : 8;     
} __LGWCR_bits;

/* LCDC Graphic Window Graphic Window DMA Control Register */
typedef struct{
__REG32 GWTM  : 5;     
__REG32       :11;     
__REG32 GWHM  : 5;     
__REG32       :10;     
__REG32 GWBT  : 1;     
} __LGWDCR_bits;

/* -------------------------------------------------------------------------*/
/*      Smart Liquid Crystal Display Controller (SLCDC)                     */
/* -------------------------------------------------------------------------*/
/* SLCDC Data Buffer Base Address Register */
typedef struct{
__REG32              : 2;     
__REG32 DATABASEADR  :30;     
} __DATA_BASE_ADDR_bits;

/* SLCDC Data Buffer Size Register */
typedef struct{
__REG32 DATABUFSIZE  :17;     
__REG32              :15;     
} __DATA_BUFF_SIZE_bits;

/* SLCDC Command Buffer Base Address Register */
typedef struct{
__REG32             : 2;     
__REG32 COMBASEADR  :30;     
} __CMD_BASE_ADDR_bits;

/* SLCDC Command Buffer Size Register */
typedef struct{
__REG32 COMBUFSIZE  :17;     
__REG32             :15;     
} __CMD_BUFF_SIZE_bits;

/* SLCDC Command String Size Register */
typedef struct{
__REG32 COMSTRINGSIZ  : 8;     
__REG32               :24;     
} __STRING_SIZE_bits;

/* SLCDC FIFO Configuration Register */
typedef struct{
__REG32 BURST  : 3;     
__REG32        :29;     
} __FIFO_CONFIG_bits;

/* SLCDC LCD Controller Configuration Register */
typedef struct{
__REG32 WORDPPAGE  :13;     
__REG32            :19;     
} __LCD_CONFIG_bits;

/* SLCDC LCD Transfer Configuration Register */
typedef struct{
__REG32 SKCPOL        : 1;     
__REG32 CSPOL         : 1;     
__REG32 XFRMODE       : 1;     
__REG32 WORDDEFCOM    : 1;     
__REG32 WORDDEFDAT    : 1;     
__REG32 WORDDEFWRITE  : 1;     
__REG32               :10;     
__REG32 IMGEND        : 2;     
__REG32               :14;     
} __LCDTRANSCONFIG_bits;

/* SLCDC Control/Status Register */
typedef struct{
__REG32 GO        : 1;     
__REG32 ABORT     : 1;     
__REG32 BUSY      : 1;     
__REG32           : 1;     
__REG32 TEA       : 1;     
__REG32 UNDRFLOW  : 1;     
__REG32 IRQ       : 1;     
__REG32 IRQEN     : 1;     
__REG32 PROT1     : 1;     
__REG32           : 2;     
__REG32 AUTOMODE  : 2;     
__REG32           :19;     
} __DMA_CTRL_STAT_bits;

/* SLCDC LCD Clock Configuration Register */
typedef struct{
__REG32 DIVIDE  : 6;     
__REG32         :26;     
} __LCD_CLK_CONFIG_bits;

/* SLCDC LCD Write Data Register */
typedef struct{
__REG32 LCDDAT  :16;     
__REG32 RS      : 1;     
__REG32         :15;     
} __LCD_WRITE_DATA_bits;

/* -------------------------------------------------------------------------*/
/*      enhanced Multimedia Accelerator (eMMA)                              */
/* -------------------------------------------------------------------------*/
/* PP Control Register */
typedef struct{
__REG32 PP_EN          : 1;     
__REG32 DEBLOCKEN      : 1;     
__REG32 DERINGEN       : 1;     
__REG32                : 1;     
__REG32 CSCEN          : 1;     
__REG32 CSC_TABLE_SEL  : 2;     
__REG32                : 1;     
__REG32 SWRST          : 1;     
__REG32 MB_MODE        : 1;     
__REG32 CSC_OUT        : 2;     
__REG32 BSDI           : 1;     
__REG32                :19;     
} __PP_CNTL_bits;

/* PP Interrupt Control Register */
typedef struct{
__REG32 FRAMECOMPINTREN  : 1;     
__REG32                  : 1;     
__REG32 ERRINTR_EN       : 1;     
__REG32                  :29;     
} __PP_INTRCNTL_bits;

/* PP Interrupt Status Register */
typedef struct{
__REG32 FRAME_COM_INTR  : 1;     
__REG32                 : 1;     
__REG32 ERR_INTR        : 1;     
__REG32                 :29;     
} __PP_INTRSTATUS_bits;

/* PP Process Frame Parameter Register */
typedef struct{
__REG32 PROCESS_FRAME_HEIGHT  :10;     
__REG32                       : 6;     
__REG32 PROCESS_FRAME_WIDTH   :10;     
__REG32                       : 6;     
} __PP_PROCESS_PARA_bits;

/* PP Source Frame Width Register */
typedef struct{
__REG32 Y_INPUT_LINE_STRIDE    :12;     
__REG32                        : 4;     
__REG32 QUANTIZER_FRAME_WIDTH  : 8;     
__REG32                        : 8;     
} __PP_FRAME_WIDTH_bits;

/* PP Destination Display Width Register */
typedef struct{
__REG32 OUTPUT_LINE_STRIDE  :13;     
__REG32                     :19;     
} __PP_DISPLAY_WIDTH_bits;

/* PP Destination Image Size Register */
typedef struct{
__REG32 OUT_IMAGE_HEIGHT  :12;     
__REG32                   : 4;     
__REG32 OUT_IMAGE_WIDTH   :12;     
__REG32                   : 4;     
} __PP_IMAGE_SIZE_bits;

/* PP Destination Frame Format Control Register */
typedef struct{
__REG32 BLUE_WIDTH    : 4;     
__REG32 GREEN_WIDTH   : 4;     
__REG32 RED_WIDTH     : 4;     
__REG32               : 4;     
__REG32 BLUE_OFFSET   : 5;     
__REG32 GREEN_OFFSET  : 5;     
__REG32 RED_OFFSET    : 5;     
__REG32               : 1;     
} __PP_DEST_FRAME_FORMAT_CNTL_bits;

/* PP Resize Table Index Register */
typedef struct{
__REG32 VERT_TBL_END_INDEX    : 6;     
__REG32                       : 2;     
__REG32 VERT_TBL_START_INDEX  : 6;     
__REG32                       : 2;     
__REG32 HORI_TBL_END_INDEX    : 6;     
__REG32                       : 2;     
__REG32 HORI_TBL_START_INDEX  : 6;     
__REG32                       : 2;     
} __PP_RESIZE_INDEX_bits;

/* PP CSC Coefficient_123 Register */
typedef struct{
__REG32 C3  : 8;     
__REG32 C2  : 8;     
__REG32 C1  : 8;     
__REG32 C0  : 8;     
} __PP_CSC_COEF_123_bits;

/* PP CSC Coefficient_4 Register */
typedef struct{
__REG32 C4  : 9;     
__REG32 X0  : 1;     
__REG32     :22;     
} __PP_CSC_COEF_4_bits;

/* PP Resize Coefficient Table */
typedef struct{
__REG32 OP  : 1;     
__REG32 N   : 2;     
__REG32 W   : 5;     
__REG32     :24;     
} __PP_RESIZE_COEF_TBL_bits;

/* PrP Control Register */
typedef struct{
__REG32 CH1EN             : 1;     
__REG32 CH2EN             : 1;     
__REG32 CSIEN             : 1;     
__REG32 DATA_IN_MODE      : 2;     
__REG32 CH1_OUT_MODE      : 2;     
__REG32 CH2_OUT_MODE      : 2;     
__REG32 CH1_LEN           : 1;     
__REG32 CH2_LEN           : 1;     
__REG32 SKIP_FRAME        : 1;     
__REG32 SWRST             : 1;     
__REG32 CLKEN             : 1;     
__REG32 WEN               : 1;     
__REG32 CH1BYP            : 1;     
__REG32 IN_TSKIP          : 3;     
__REG32 CH1_TSKIP         : 3;     
__REG32 CH2_TSKIP         : 3;     
__REG32 INPUT_FIFO_LEVEL  : 2;     
__REG32 RZ_FIFO_LEVEL     : 2;     
__REG32 CH2B1EN           : 1;     
__REG32 CH2B2EN           : 1;     
__REG32 CH2FEN            : 1;     
} __PRP_CNTL_bits;

/* PrP Interrupt Control Register */
typedef struct{
__REG32 RDERRIE    : 1;     
__REG32 CH1WERRIE  : 1;     
__REG32 CH2WERRIE  : 1;     
__REG32 CH1FCIE    : 1;     
__REG32            : 1;     
__REG32 CH2FCIE    : 1;     
__REG32            : 1;     
__REG32 LBOVFIE    : 1;     
__REG32 CH2OVFIE   : 1;     
__REG32            :23;     
} __PRP_INTR_CNTL_bits;

/* PrP Interrupt Status Register */
typedef struct{
__REG32 READERR   : 1;     
__REG32 CH1WRERR  : 1;     
__REG32 CH2WRERR  : 1;     
__REG32 CH2B2CI   : 1;     
__REG32 CH2B1CI   : 1;     
__REG32 CH1B2CI   : 1;     
__REG32 CH1B1CI   : 1;     
__REG32 LBOVF     : 1;     
__REG32 CH2OVF    : 1;     
__REG32           :23;     
} __PRP_INTRSTATUS_bits;

/* PrP Source Frame Size Register */
typedef struct{
__REG32 PICTURE_Y_SIZE  :11;     
__REG32                 : 5;     
__REG32 PICTURE_X_SIZE  :11;     
__REG32                 : 5;     
} __PRP_SRC_FRAME_SIZE_bits;

/* PrP Destination Channel-1 Line Stride Register */
typedef struct{
__REG32 CH1_OUT_LINE_STRIDE  :12;     
__REG32                      :20;     
} __PRP_DEST_CH1_LINE_STRIDE_bits;

/* PrP Source Pixel Format Control Register */
typedef struct{
__REG32 BLUE_WIDTH         : 4;     
__REG32 GREEN_WIDTH        : 4;     
__REG32 RED_WIDTH          : 4;     
__REG32                    : 4;     
__REG32 BLUE_V_CR_OFFSET   : 5;     
__REG32 GREEN_U_CB_OFFSET  : 5;     
__REG32 RED_Y_OFFSET       : 5;     
__REG32                    : 1;     
} __PRP_SRC_PIXEL_FORMAT_CNTL_bits;

/* PrP Channel-1 Pixel Format Control Register */
typedef struct{
__REG32 BLUE_WIDTH    : 4;     
__REG32 GREEN_WIDTH   : 4;     
__REG32 RED_WIDTH     : 4;     
__REG32               : 4;     
__REG32 BLUE_OFFSET   : 5;     
__REG32 GREEN_OFFSET  : 5;     
__REG32 RED_OFFSET    : 5;     
__REG32               : 1;     
} __PRP_CH1_PIXEL_FORMAT_CNTL_bits;

/* PrP Destination Channel-1 Output Image Size Register */
typedef struct{
__REG32 CH1_OUT_IMAGE_HEIGHT  :11;     
__REG32                       : 5;     
__REG32 CH1_OUT_IMAGE_WIDTH   :11;     
__REG32                       : 5;     
} __PRP_CH1_OUT_IMAGE_SIZE_bits;

/* PrP Destination Channel-2 Output Image Size Register */
typedef struct{
__REG32 CH2_OUT_IMAGE_HEIGHT  :11;     
__REG32                       : 5;     
__REG32 CH2_OUT_IMAGE_WIDTH   :11;     
__REG32                       : 5;     
} __PRP_CH2_OUT_IMAGE_SIZE_bits;

/* PrP Source Line Stride Register */
typedef struct{
__REG32 SOURCE_LINE_STRIDE  :13;     
__REG32                     : 3;     
__REG32 CSI_LINE_SKIP       :13;     
__REG32                     : 3;     
} __PRP_SRC_LINE_STRIDE_bits;

/* PrP CSC Coefficient 012 */
typedef struct{
__REG32 C2  : 8;     
__REG32     : 3;     
__REG32 C1  : 8;     
__REG32     : 2;     
__REG32 C0  : 8;     
__REG32     : 3;     
} __PRP_CSC_COEF_012_bits;

/* PrP CSC coefficient 345 */
typedef struct{
__REG32 C5  : 7;     
__REG32     : 4;     
__REG32 C4  : 9;     
__REG32     : 1;     
__REG32 C3  : 8;     
__REG32     : 3;     
} __PRP_CSC_COEF_345_bits;

/* PrP CSC Coefficient 678 */
typedef struct{
__REG32 C8  : 7;     
__REG32     : 4;     
__REG32 C7  : 7;     
__REG32     : 3;     
__REG32 C6  : 7;     
__REG32     : 3;     
__REG32 X0  : 1;     
} __PRP_CSC_COEF_678_bits;

/* PrP Horizontal Resize Coefficient-1 */
typedef struct{
__REG32 HC0  : 3;     
__REG32 HC1  : 3;     
__REG32 HC2  : 3;     
__REG32 HC3  : 3;     
__REG32 HC4  : 3;     
__REG32      : 1;     
__REG32 HC5  : 3;     
__REG32 HC6  : 3;     
__REG32 HC7  : 3;     
__REG32 HC8  : 3;     
__REG32 HC9  : 3;     
__REG32      : 1;     
} __PRP_RZ_HORI_COEF1_bits;

/* PrP Horizontal Resize Coefficient-2 */
typedef struct{
__REG32 HC10  : 3;     
__REG32 HC11  : 3;     
__REG32 HC12  : 3;     
__REG32 HC13  : 3;     
__REG32 HC14  : 3;     
__REG32       : 1;     
__REG32 HC15  : 3;     
__REG32 HC16  : 3;     
__REG32 HC17  : 3;     
__REG32 HC18  : 3;     
__REG32 HC19  : 3;     
__REG32       : 1;     
} __PRP_RZ_HORI_COEF2_bits;

/* PrP Horizontal Resize Valid */
typedef struct{
__REG32 HOV           :20;     
__REG32               : 4;     
__REG32 HORI_TBL_LEN  : 5;     
__REG32               : 2;     
__REG32 AVG_BIL       : 1;     
} __PRP_RZ_HORI_VALID_bits;

/* PrP Vertical Resize Coefficient-1 */
typedef struct{
__REG32 VC0  : 3;     
__REG32 VC1  : 3;     
__REG32 VC2  : 3;     
__REG32 VC3  : 3;     
__REG32 VC4  : 3;     
__REG32      : 1;     
__REG32 VC5  : 3;     
__REG32 VC6  : 3;     
__REG32 VC7  : 3;     
__REG32 VC8  : 3;     
__REG32 VC9  : 3;     
__REG32      : 1;     
} __PRP_RZ_VERT_COEF1_bits;

/* PrP Vertical Resize Coefficient-2 */
typedef struct{
__REG32 VC10  : 3;     
__REG32 VC11  : 3;     
__REG32 VC12  : 3;     
__REG32 VC13  : 3;     
__REG32 VC14  : 3;     
__REG32       : 1;     
__REG32 VC15  : 3;     
__REG32 VC16  : 3;     
__REG32 VC17  : 3;     
__REG32 VC18  : 3;     
__REG32 VC19  : 3;     
__REG32       : 1;     
} __PRP_RZ_VERT_COEF2_bits;

/* PrP CVertical Resize Valid */
typedef struct{
__REG32 VOV           :20;     
__REG32               : 4;     
__REG32 VERT_TBL_LEN  : 5;     
__REG32               : 2;     
__REG32 AVG_BIL       : 1;     
} __PRP_RZ_VERT_VALID_bits;

/* -------------------------------------------------------------------------*/
/*      MMC/SDHC Registers                                                  */
/* -------------------------------------------------------------------------*/
/* MMC/SD Clock Control Register */
typedef struct{
__REG32 STOP_CLK     : 1;     
__REG32 START_CLK    : 1;     
__REG32              : 1;     
__REG32 MMCSD_RESET  : 1;     
__REG32              :28;     
} __STR_STP_CLK_bits;

/* MMC/SD Status Register */
typedef struct{
__REG32 TIME_OUT_READ      : 1;     
__REG32 TIME_OUT_RESP      : 1;     
__REG32 CRC_WRITE_ERR      : 1;     
__REG32 CRC_READ_ERR       : 1;     
__REG32                    : 1;     
__REG32 RESP_CRC_ERR       : 1;     
__REG32 APPL_BUFF_FE       : 1;     
__REG32 APPL_BUFF_FF       : 1;     
__REG32 CARD_BUS_CLK_RUN   : 1;     
__REG32 WR_CRC_ERROR_CODE  : 2;     
__REG32 READ_OP_DONE       : 1;     
__REG32 WRITE_OP_DONE      : 1;     
__REG32 END_CMD_RESP       : 1;     
__REG32 SDIO_INT_ACTIVE    : 1;     
__REG32 CARD_PRESENCE      : 1;     
__REG32                    :16;     
} __SD_STATUS_bits;

/* MMC/SD clock rate register */
typedef struct{
__REG32 CLK_DIVIDER    : 4;     
__REG32 CLK_PRESCALER  :12;     
__REG32                :16;     
} __CLK_RATE_bits;

/* MMC/SD command and data control register */
typedef struct{
__REG32 FORMAT_OF_RESPONSE  : 3;     
__REG32 DATA_ENABLE         : 1;     
__REG32 WRITE_READ          : 1;     
__REG32                     : 2;     
__REG32 INIT                : 1;     
__REG32 BUS_WIDTH           : 2;     
__REG32 START_READ_WAIT     : 1;     
__REG32 STOP_READ_WAIT      : 1;     
__REG32 CMD_RESP_LONG_OFF   : 1;     
__REG32                     : 2;     
__REG32 CMD_RESUME          : 1;     
__REG32                     :16;     
} __CMD_DAT_CONT_bits;

/* MMC/SD response time out register */
typedef struct{
__REG32 RESPONSE_TIME_OUT  : 8;     
__REG32                    :24;     
} __RES_TO_bits;

/* MMC/SD read time out register */
typedef struct{
__REG32 DATA_READ_TIME_OUT  :16;     
__REG32                     :16;     
} __READ_TO_bits;

/* MMC/SD block length register */
typedef struct{
__REG32 BLOCK_LENGTH  :10;     
__REG32               :22;     
} __BLK_LEN_bits;

/* MMC/SD number of blocks register */
typedef struct{
__REG32 NOB  :16;     
__REG32      :16;     
} __NOB_bits;

/* MMC/SD revision number register */
typedef struct{
__REG32 REVISION_NUMBER  :16;     
__REG32                  :16;     
} __REV_NO_bits;

/* MMC/SD Interrupt mask register */
typedef struct{
__REG32 DATA_TRAN        : 1;     
__REG32 WRITE_OP_DONE    : 1;     
__REG32 END_CMD_RES      : 1;     
__REG32 BUF_READY        : 1;     
__REG32 SDIO             : 1;     
__REG32 DAT0_EN          : 1;     
__REG32                  : 8;     
__REG32 SDIO_WAKEUP_EN   : 1;     
__REG32 CARD_DET_IRQ_EN  : 1;     
__REG32                  :16;     
} __MMCSD_INT_CTRL_bits;

/* MMC/SD command number register */
typedef struct{
__REG32 COMMAND_NUMBER  : 6;     
__REG32                 :26;     
} __CMD_bits;

/* MMC/SD higher argument register */
typedef struct{
__REG32 ARGUMENT_HIGH  :16;     
__REG32                :16;     
} __ARGH_bits;

/* MMC/SD lower argument register */
typedef struct{
__REG32 ARGUMENT_LOW  :16;     
__REG32               :16;     
} __ARGL_bits;

/* MMC/SD response FIFO register */
typedef struct{
__REG32 RESPONSE_CONTENT  :16;     
__REG32                   :16;     
} __RES_FIFO_bits;

/* MMC/SD buffer access register */
typedef struct{
__REG32 FIFO_CONTENT  :16;     
__REG32               :16;     
} __BUFFER_ACCESS_bits;

/* -------------------------------------------------------------------------*/
/*      Digital Audio Mux (AUDMUX)                                          */
/* -------------------------------------------------------------------------*/
/* AUDMUX Host Port Configuration Register */
typedef struct{
__REG32 INMMASK  : 8;     
__REG32 INMEN    : 1;     
__REG32          : 1;     
__REG32 TXRXEN   : 1;     
__REG32          : 1;     
__REG32 SYN      : 1;     
__REG32 RXDSEL   : 3;     
__REG32          : 4;     
__REG32 RFCSEL   : 4;     
__REG32 RCLKDIR  : 1;     
__REG32 RFSDIR   : 1;     
__REG32 TFCSEL   : 4;     
__REG32 TCLKDIR  : 1;     
__REG32 TFSDIR   : 1;     
} __HPCR_bits;

/* AUDMUX Peripheral Port Configuration Register */
typedef struct{
__REG32          :10;     
__REG32 TXRXEN   : 1;     
__REG32          : 1;     
__REG32 SYN      : 1;     
__REG32 RXDSEL   : 3;     
__REG32          : 4;     
__REG32 RFCSEL   : 4;     
__REG32 RCLKDIR  : 1;     
__REG32 RFSDIR   : 1;     
__REG32 TFCSEL   : 4;     
__REG32 TCLKDIR  : 1;     
__REG32 TFSDIR   : 1;     
} __PPCR_bits;

/* -------------------------------------------------------------------------*/
/*      UARTs                                                               */
/* -------------------------------------------------------------------------*/
/* UARTs Receiver Register */
typedef struct{
__REG32 RX_DATA  : 8;     // Bits 0-7             - Recieve Data
__REG32          : 2;     // Bits 8-9             - Reserved
__REG32 PRERR    : 1;     // Bit  10              - Receive Parity Error 1=error
__REG32 BRK      : 1;     // Bit  11              - Receive break Caracter detected 1 = detected
__REG32 FRMERR   : 1;     // Bit  12              - Receive Framing Error 1=error
__REG32 OVRRUN   : 1;     // Bit  13              - Receive Over run Error 1=error
__REG32 ERR      : 1;     // Bit  14              - Receive Error Detect (OVR,FRM,BRK,PR 0=error
__REG32 CHARRDY  : 1;     // Bit  15              - Receive Character Ready 1=character valid
__REG32          :16;     // Bits 31-16           - Reserved
} __URXD_bits;

/* UARTs Transmitter Register */
typedef struct{
__REG32 TX_DATA  : 8;     // Bits 7-0             - Transmit Data
__REG32          :24;     // Bits 31-16           - Reserved
} __UTXD_bits;

/* UARTs Control Register 1 */
typedef struct{
__REG32 UARTEN    : 1;     // Bit  0       - UART Enable 1 = Enable the UART
__REG32 DOZE      : 1;     // Bit  1       - DOZE 1 = The UART is disabled when in DOZE state
__REG32           : 1;     // Bit  2
__REG32 TDMAEN    : 1;     // Bit  3       - Transmitter Ready DMA Enable 1 = enable
__REG32 SNDBRK    : 1;     // Bit  4       - Send BREAK 1 = send break char continuous
__REG32 RTSDEN    : 1;     // Bit  5       - RTS Delta Interrupt Enable 1 = enable
__REG32 TXMPTYEN  : 1;     // Bit  6       - Transmitter Empty Interrupt Enable 1 = enable
__REG32 IREN      : 1;     // Bit  7       - Infrared Interface Enable 1 = enable
__REG32 RDMAEN    : 1;     // Bit  8       - Receive Ready DMA Enable 1 = enable
__REG32 RRDYEN    : 1;     // Bit  9       - Receiver Ready Interrupt Enable 1 = Enable
__REG32 ICD       : 2;     // Bit  10-11   - Idle Condition Detect
                                //              - 00 = Idle for more than 4 frames
                                //              - 01 = Idle for more than 8 frames
                                //              - 10 = Idle for more than 16 frames
                                //              - 11 = Idle for more than 32 frames
__REG32 IDEN      : 1;     // Bit  12      - Idle Condition Detected Interrupt en 1=en
__REG32 TRDYEN    : 1;     // Bit  13      - Transmitter Ready Interrupt Enable 1=en
__REG32 ADBR      : 1;     // Bit  14      - AutoBaud Rate Detection enable 1=en
__REG32 ADEN      : 1;     // Bit  15      - AutoBaud Rate Detection Interrupt en 1=en
__REG32           :16;     
} __UCR1_bits;

/* UARTs Control Register 2 */
typedef struct{
__REG32 _SRST  : 1;     // Bit  0       -Software Reset 0 = Reset the tx and rx state machines
__REG32 RXEN   : 1;     // Bit  1       -Receiver Enable 1 = Enable
__REG32 TXEN   : 1;     // Bit  2       -Transmitter Enable 1= enable
__REG32 ATEN   : 1;     // Bit  3       -Aging Timer Enable—This bit is used to mask the aging timer interrupt (triggered with AGTIM)
__REG32 RTSEN  : 1;     // Bit  4       -Request to Send Interrupt Enable 1=enable
__REG32 WS     : 1;     // Bit  5       -Word Size 0 = 7bit, 1= 8 bit
__REG32 STPB   : 1;     // Bit  6       -Stop 0= 1 stop bits, 1= 2 stop bits
__REG32 PROE   : 1;     // Bit  7       -Parity Odd/Even 1=Odd
__REG32 PREN   : 1;     // Bit  8       -Parity Enable 1=enable parity generator
__REG32 RTEC   : 2;     // Bits 9-10    -Request to Send Edge Control
                                //              - 00 = Trigger interrupt on a rising edge
                                //              - 01 = Trigger interrupt on a falling edge
                                //              - 1X = Trigger interrupt on any edge
__REG32 ESCEN  : 1;     // Bit  11      -Escape Enable 1 = Enable escape sequence detection
__REG32 CTS    : 1;     // Bit  12      -Clear to Send 1 = The UARTx_CTS pin is low (active)
__REG32 CTSC   : 1;     // Bit  13      -UARTx_CTS Pin controlled by 1= receiver 0= CTS bit
__REG32 IRTS   : 1;     // Bit  14      -Ignore UARTx_RTS Pin 1=ignore
__REG32 ESCI   : 1;     // Bit  15      -Escape Sequence Interrupt En 1=enable
__REG32        :16;     
} __UCR2_bits;

/* UARTs Control Register 3 */
typedef struct{
__REG32 ACIEN      : 1;     
__REG32 INVT       : 1;     
__REG32 RXDMUXSEL  : 1;     
__REG32            : 1;     
__REG32 AWAKEN     : 1;     
__REG32 AIRINTEN   : 1;     
__REG32 RXDSEN     : 1;     
__REG32 ADNIMP     : 1;     
__REG32 RI         : 1;     
__REG32 DCD        : 1;     
__REG32 DSR        : 1;     
__REG32 FRAERREN   : 1;     
__REG32 PARERREN   : 1;     
__REG32 DTREN      : 1;     
__REG32 DPEC       : 2;     
__REG32            :16;     
} __UCR3_bits;

/* UARTs Control Register 4 */
typedef struct{
__REG32 DREN   : 1;     // Bit  0       -Receive Data Ready Interrupt Enable 1= enable
__REG32 OREN   : 1;     // Bit  1       -Receiver Overrun Interrupt Enable 1= enable
__REG32 BKEN   : 1;     // Bit  2       -BREAK Condition Detected Interrupt en 1= enable
__REG32 TCEN   : 1;     // Bit  3       -Transmit Complete Interrupt Enable1 = Enable
__REG32 LPBYP  : 1;     // Bit  4       -Low Power Bypass—Allows to bypass the low power new features in UART for i.MX21. To use during debug phase.
__REG32 IRSC   : 1;     // Bit  5       -IR Special Case vote logic uses 1= uart ref clk
__REG32        : 1;     // Bit  6       -
__REG32 WKEN   : 1;     // Bit  7       -WAKE Interrupt Enable 1= enable
__REG32 ENIRI  : 1;     // Bit  8       -Serial Infrared Interrupt Enable 1= enable
__REG32 INVR   : 1;     // Bit  9       -Inverted Infrared Reception 1= active high
__REG32 CTSTL  : 6;     // Bits 10-15   -CTS Trigger Level
                                //              000000 = 0 characters received
                                //              000001 = 1 characters in the RxFIFO
                                //              ...
                                //              100000 = 32 characters in the RxFIFO (maximum)
                                //              All Other Settings Reserved
__REG32        :16;     
} __UCR4_bits;

/* UARTs FIFO Control Register */
typedef struct{
__REG32 RXTL    : 6;     // Bits 0-5     -Receiver Trigger Level
                                //              000000 = 0 characters received
                                //              000001 = RxFIFO has 1 character
                                //              ...
                                //              011111 = RxFIFO has 31 characters
                                //              100000 = RxFIFO has 32 characters (maximum)
                                //              All Other Settings Reserved
__REG32 DCEDTE  : 1;     // Bit  6       -
__REG32 RFDIV   : 3;     // Bits 7-9     -Reference Frequency Divider
                                //              000 = Divide input clock by 6
                                //              001 = Divide input clock by 5
                                //              010 = Divide input clock by 4
                                //              011 = Divide input clock by 3
                                //              100 = Divide input clock by 2
                                //              101 = Divide input clock by 1
                                //              110 = Divide input clock by 7
__REG32 TXTL    : 6;     // Bits 10-15   -Transmitter Trigger Level
                                //              000000 = Reserved
                                //              000001 = Reserved
                                //              000010 = TxFIFO has 2 or fewer characters
                                //              ...
                                //              011111 = TxFIFO has 31 or fewer characters
                                //              100000 = TxFIFO has 32 characters (maximum)
                                //              All Other Settings Reserved
__REG32         :16;     
} __UFCR_bits;

/* UARTs Status Register 1 */
typedef struct{
__REG32            : 4;     
__REG32 AWAKE      : 1;     
__REG32 AIRINT     : 1;     
__REG32 RXDS       : 1;     
__REG32            : 1;     
__REG32 AGTIM      : 1;     
__REG32 RRDY       : 1;     
__REG32 FRAMER     : 1;     
__REG32 ESCF       : 1;     
__REG32 RTSD       : 1;     
__REG32 TRDY       : 1;     
__REG32 RTSS       : 1;     
__REG32 PARITYERR  : 1;     
__REG32            :16;     
} __USR1_bits;

/* UARTs Status Register 2 */
typedef struct{
__REG32 RDR      : 1;     
__REG32 ORE      : 1;     
__REG32 BRCD     : 1;     
__REG32 TXDC     : 1;     
__REG32 RTSF     : 1;     
__REG32 DCDIN    : 1;     
__REG32 DCDDELT  : 1;     
__REG32 WAKE     : 1;     
__REG32 IRINT    : 1;     
__REG32 RIIN     : 1;     
__REG32 RIDELT   : 1;     
__REG32 ACST     : 1;     
__REG32 IDLE     : 1;     
__REG32 DTRF     : 1;     
__REG32 TXFE     : 1;     
__REG32 ADET     : 1;     
__REG32          :16;     
} __USR2_bits;

/* UARTs Escape Character Register */
typedef struct{
__REG32 ESC_CHAR  : 8;     // Bits 0-7     -UART Escape Character
__REG32           :24;     
} __UESC_bits;

/* UARTs Escape Timer Register */
typedef struct{
__REG32 TIM  :12;     // Bits 0-11    -UART Escape Timer
__REG32      :20;     
} __UTIM_bits;

/* UARTs BRM Incremental Register */
typedef struct{
__REG32 INC  :16;     // Bits 0-15    -Incremental Numerator
__REG32      :16;     
} __UBIR_bits;

/* UARTs BRM Modulator Register */
typedef struct{
__REG32 MOD  :16;     // Bits 0-15    -Modulator Denominator
__REG32      :16;     
} __UBMR_bits;

/* UARTs Baud Rate Count register */
typedef struct{
__REG32 BCNT  :16;     // Bits 0-15    -Baud Rate Count Register
__REG32       :16;     
} __UBRC_bits;

/* UARTs One Millisecond Registers */
typedef struct{
__REG32 BCNT  :16;     // Bits 0-15    -Baud Rate Count Register
__REG32       :16;     
} __ONEMS_bits;

/* UARTS Test Register 1 */
typedef struct{
__REG32 SOFTRST  : 1;     
__REG32          : 2;     
__REG32 RXFULL   : 1;     
__REG32 TXFULL   : 1;     
__REG32 RXEMPTY  : 1;     
__REG32 TXEMPTY  : 1;     
__REG32          : 2;     
__REG32 RXDBG    : 1;     
__REG32 LOOPIR   : 1;     
__REG32 DBGEN    : 1;     
__REG32 LOOP     : 1;     
__REG32 FRCPERR  : 1;     
__REG32          :18;     
} __UTS_bits;

/* -------------------------------------------------------------------------*/
/*      USB OTG Registers                                                       */
/* -------------------------------------------------------------------------*/

/* USB OTG Hardware Mode Register */
typedef struct{
__REG32 CRECFG    : 2;     
__REG32           : 2;     
__REG32 HOSTXCVR  : 2;     
__REG32 OTGXCVR   : 2;     
__REG32           : 6;     
__REG32 ANASDBEN  : 1;     
__REG32           : 1;     
__REG32 HSTREV    : 8;     
__REG32 FUNCREV   : 8;     
} __HWMODE_bits;

/* USB OTG Interrupt Status Register */
typedef struct{
__REG32 HCINT     : 1;     
__REG32 FCINT     : 1;     
__REG32 HNPINT    : 1;     
__REG32 ASHCINT   : 1;     
__REG32 ASFCINT   : 1;     
__REG32 ASHNPINT  : 1;     
__REG32           :26;     
} __CINT_STAT_bits;

/* USB OTG Interrupt Status Enable Register */
typedef struct{
__REG32 HCINTEN     : 1;     
__REG32 FCINTEN     : 1;     
__REG32 HNPINTEN    : 1;     
__REG32 ASHCINTEN   : 1;     
__REG32 ASFCINTEN   : 1;     
__REG32 ASHNPINTEN  : 1;     
__REG32             :26;     
} __CINT_STEN_bits;

/* USB OTG Module Clock Control Register */
typedef struct{
__REG32 MAINCLK  : 1;     
__REG32 HSTCLK   : 1;     
__REG32 FUNCCLK  : 1;     
__REG32          :29;     
} __CLK_CTRL_bits;

/* USB OTG Reset Control Register */
typedef struct{
__REG32 RSTHC    : 1;     
__REG32 RSTHSIE  : 1;     
__REG32 RSTRH    : 1;     
__REG32 RSTFSKE  : 1;     
__REG32 RSTFC    : 1;     
__REG32 RSTCTRL  : 1;     
__REG32          : 9;     
__REG32 RSTI2C   : 1;     
__REG32          :16;     
} __RST_CTRL_bits;

/* USB OTG Frame Interval Register */
typedef struct{
__REG32 FRMINT     :14;     
__REG32            : 1;     
__REG32 RSTFRM     : 1;     
__REG32 FRMINTPER  :14;     
__REG32            : 2;     
} __FRM_INVTL_bits;

/* USB OTG Frame Remaining Register */
typedef struct{
__REG32          :16;     
__REG32 FRMREMN  :14;     
__REG32          : 2;     
} __FRM_REMAIN_bits;

/* USB OTG HNP Control Status Register */
typedef struct{
__REG32            : 1;     
__REG32 ABBUSREQ   : 1;     
__REG32 ADROPBUS   : 1;     
__REG32 CLRERROR   : 1;     
__REG32 HNPSTATE   : 5;     
__REG32 SWPDDM     : 1;     
__REG32            : 1;     
__REG32 SWPUDP     : 1;     
__REG32 SWAUTORST  : 1;     
__REG32            : 2;     
__REG32 SWVBUSPUL  : 1;     
__REG32            : 1;     
__REG32 ISADEV     : 1;     
__REG32 ISBDEV     : 1;     
__REG32 CMPEN      : 1;     
__REG32 BGEN       : 1;     
__REG32 MASTER     : 1;     
__REG32 SLAVE      : 1;     
__REG32            : 1;     
__REG32 BHNPEN     : 1;     
__REG32 ARMTHNPE   : 1;     
__REG32            : 1;     
__REG32 VBUSGTAVV  : 1;     
__REG32 VBUSABSV   : 1;     
__REG32 VBUSBSE    : 1;     
__REG32 HNPDAT     : 1;     
__REG32            : 1;     
} __HNP_CTRL_bits;

/* USB OTG HNP Timer 1 Register */
typedef struct{
__REG32 AWAITVRISE  : 8;     
__REG32 AWAITCONN   : 8;     
__REG32 AWAITDISC   : 8;     
__REG32 BWAITCONN   : 8;     
} __HNP_TMR1_bits;

/* USB OTG HNP Timer 2 Register */
typedef struct{
__REG32 SRPDPULW  : 5;     
__REG32 SRPVPULW  : 5;     
__REG32           : 6;     
__REG32 BSRPFAIL  :16;     
} __HNP_TMR2_bits;

/* USB OTG HNP Timer 3 Register */
typedef struct{
__REG32                : 3;     
__REG32 USESESSEND     : 1;     
__REG32 VBUSPULSE      : 1;     
__REG32 DATAPULSE      : 1;     
__REG32 INSERTION      : 1;     
__REG32 VBUSDISCHTIMR  : 9;     
__REG32 A_SDB_WIN      : 8;     
__REG32 LNGDBNC        : 8;     
} __HNP_TMR3_bits;

/* USB OTG HNP Interrupt Status Register */
typedef struct{
__REG32 IDCHANGE    : 1;     
__REG32 MASSLVCHG   : 1;     
__REG32 AVBUSVAILD  : 1;     
__REG32 ABSESVAILD  : 1;     
__REG32 VBUSERROR   : 1;     
__REG32 SRPINT      : 1;     
__REG32 SRPSUCFAIL  : 1;     
__REG32 AIDLEBDTO   : 1;     
__REG32 AWAITBTO    : 1;     
__REG32             : 6;     
__REG32 I2COTGINT   : 1;     
__REG32             :16;     
} __HNP_INT_STAT_bits;

/* USB OTG HNP Interrupt Enable Register */
typedef struct{
__REG32 IDCHANGEEN    : 1;     
__REG32 MASSLVCHGEN   : 1;     
__REG32 AVBUSVAILDEN  : 1;     
__REG32 ABSESVAILDEN  : 1;     
__REG32 VBUSERROREN   : 1;     
__REG32 SRPINTEN      : 1;     
__REG32 SRPSUCFAILEN  : 1;     
__REG32 AIDLEBDTON    : 1;     
__REG32 AWAITBTOEN    : 1;     
__REG32               : 6;     
__REG32 I2COTGINTEN   : 1;     
__REG32               :16;     
} __HNP_INT_EN_bits;

/* USB OTG USB Control Register */
typedef struct{
__REG32                   : 1;     
__REG32 HOST1_TXEN_OE     : 1;     
__REG32 USB_BYP           : 1;     
__REG32                   : 1;     
__REG32 HOST2_PWR_MASK    : 1;     
__REG32 HOST1_PWR_MASK    : 1;     
__REG32 OTG_PWR_MASK      : 1;     
__REG32                   : 1;     
__REG32 HOST1_BYP_VAL     : 2;     
__REG32 OTG_BYP_VAL       : 2;     
__REG32 HOST1_BYP_TLL     : 1;     
__REG32 _OTG_RCV_RXDP     : 1;     
__REG32                   : 2;     
__REG32 FNT_WU_INT_EN     : 1;     
__REG32 HOST_WU_INT_EN    : 1;     
__REG32 OTG_WU_INT_EN     : 1;     
__REG32 I2C_WU_INT_EN     : 1;     
__REG32                   : 4;     
__REG32 FNT_WU_INT_STAT   : 1;     
__REG32 HOST_WU_INT_STAT  : 1;     
__REG32 OTG_WU_INT_STAT   : 1;     
__REG32 _12C_WU_INT_STAT  : 1;     
__REG32                   : 4;     
} __USBCTRL_bits;

/* USB OTG Host Endpoint Transfer Descriptor WORD0 Format */
typedef struct{
__REG32 ADDRESS    : 7;     
__REG32 ENDPNT     : 4;     
__REG32 DIRECT     : 2;     
__REG32 SPEED      : 1;     
__REG32 FORMAT     : 2;     
__REG32 MAXPKTSIZ  :10;     
__REG32            : 1;     
__REG32 HALTED     : 1;     
__REG32 TOGCRY     : 1;     
__REG32            : 1;     
__REG32 SNDNAK     : 1;     
__REG32            : 1;     
} __USB_EP_DWORD0_bits;

/* USB OTG Transfer Descriptor Format WORD1 */
typedef struct{
__REG32 XBUFSRTAD  :16;     
__REG32 YBUFSRTAD  :16;     
} __USB_EP_DWORD1_bits;

/* USB OTG Host Endpoint Transfer Descriptor WORD2 Format */
typedef union{
  //USB_EPx_DWORD2
  //USB_EP1x_DWORD2
  //USB_EP2x_DWORD2
  //USB_EP3x_DWORD2
  struct {
__REG32 RTRYDELAY     : 8;     
__REG32 RELPOLPOS     : 8;     
__REG32 DIRPID        : 2;     
__REG32 BUFROUND      : 1;     
__REG32 DELAYINT      : 3;     
__REG32 DATATOGL      : 2;     
__REG32 ERRORCNT      : 4;     
__REG32 COMPCODE      : 4;     
  };
  //USB_EPx_DWORD2 Isochronous
  //USB_EP1x_DWORD2 Isochronous
  //USB_EP2x_DWORD2 Isochronous
  //USB_EP3x_DWORD2 Isochronous
  struct {
__REG32 STARTFRM      :16;     
__REG32               : 3;     
__REG32 DELAYIN       : 3;     
__REG32               : 2;     
__REG32 FRAMECNT      : 1;     
__REG32               : 3;     
__REG32 COMPCODE_ISO  : 4;     
  };
} __USB_EP_DWORD2_bits;

/* USB OTG Host Endpoint Transfer Descriptor WORD3 Format */
typedef union{
  //USB_EPxy_DWORD3
  struct {
__REG32 TOTBYECNT  :21;     
__REG32 BUFSIZE    :11;     
  };
  //USB_EPxy_DWORD3 Isochronous
  struct {
__REG32 PKTLEN0    :10;     
__REG32            : 2;     
__REG32 COMPCODE0  : 4;     
__REG32 PKTLEN1    :10;     
__REG32            : 2;     
__REG32 COMPCODE1  : 4;     
  };
} __USB_EP_DWORD3_bits;

/* USB OTG Host Control Register */
typedef struct{
__REG32 CTLBLKSR  : 2;     
__REG32 HCUSBSTE  : 2;     
__REG32 RMTWUEN   : 1;     
__REG32           :11;     
__REG32 SCHEDOVR  : 1;     
__REG32           :14;     
__REG32 HCRESET   : 1;     
} __HOST_CTRL_bits;

/* USB OTG System Interrupt Status Register */
/* USB OTG System Interrupt Enable Register */
typedef struct{
__REG32 SORINT     : 1;     
__REG32 DONEINT    : 1;     
__REG32 SOFINT     : 1;     
__REG32 RESDETINT  : 1;     
__REG32 HERRINT    : 1;     
__REG32 FMOFINT    : 1;     
__REG32 PSCINT     : 1;     
__REG32            :25;     
} __SYSISR_bits;

/* USB OTG X Buffer Interrupt Status Register */
typedef struct{
__REG32 XBUF0INT   : 1;     
__REG32 XBUF1INT   : 1;     
__REG32 XBUF2INT   : 1;     
__REG32 XBUF3INT   : 1;     
__REG32 XBUF4INT   : 1;     
__REG32 XBUF5INT   : 1;     
__REG32 XBUF6INT   : 1;     
__REG32 XBUF7INT   : 1;     
__REG32 XBUF8INT   : 1;     
__REG32 XBUF9INT   : 1;     
__REG32 XBUF10INT  : 1;     
__REG32 XBUF11INT  : 1;     
__REG32 XBUF12INT  : 1;     
__REG32 XBUF13INT  : 1;     
__REG32 XBUF14INT  : 1;     
__REG32 XBUF15INT  : 1;     
__REG32 XBUF16INT  : 1;     
__REG32 XBUF17INT  : 1;     
__REG32 XBUF18INT  : 1;     
__REG32 XBUF19INT  : 1;     
__REG32 XBUF20INT  : 1;     
__REG32 XBUF21INT  : 1;     
__REG32 XBUF22INT  : 1;     
__REG32 XBUF23INT  : 1;     
__REG32 XBUF24INT  : 1;     
__REG32 XBUF25INT  : 1;     
__REG32 XBUF26INT  : 1;     
__REG32 XBUF27INT  : 1;     
__REG32 XBUF28INT  : 1;     
__REG32 XBUF29INT  : 1;     
__REG32 XBUF30INT  : 1;     
__REG32 XBUF31INT  : 1;     
} __XBUFSTAT_bits;

/* USB OTG Y Buffer Interrupt Status Register */
typedef struct{
__REG32 YBUF0INT   : 1;     
__REG32 YBUF1INT   : 1;     
__REG32 YBUF2INT   : 1;     
__REG32 YBUF3INT   : 1;     
__REG32 YBUF4INT   : 1;     
__REG32 YBUF5INT   : 1;     
__REG32 YBUF6INT   : 1;     
__REG32 YBUF7INT   : 1;     
__REG32 YBUF8INT   : 1;     
__REG32 YBUF9INT   : 1;     
__REG32 YBUF10INT  : 1;     
__REG32 YBUF11INT  : 1;     
__REG32 YBUF12INT  : 1;     
__REG32 YBUF13INT  : 1;     
__REG32 YBUF14INT  : 1;     
__REG32 YBUF15INT  : 1;     
__REG32 YBUF16INT  : 1;     
__REG32 YBUF17INT  : 1;     
__REG32 YBUF18INT  : 1;     
__REG32 YBUF19INT  : 1;     
__REG32 YBUF20INT  : 1;     
__REG32 YBUF21INT  : 1;     
__REG32 YBUF22INT  : 1;     
__REG32 YBUF23INT  : 1;     
__REG32 YBUF24INT  : 1;     
__REG32 YBUF25INT  : 1;     
__REG32 YBUF26INT  : 1;     
__REG32 YBUF27INT  : 1;     
__REG32 YBUF28INT  : 1;     
__REG32 YBUF29INT  : 1;     
__REG32 YBUF30INT  : 1;     
__REG32 YBUF31INT  : 1;     
} __YBUFSTAT_bits;

/* USB OTG XY Interrupt Enable Register */
typedef struct{
__REG32 XY0IEN   : 1;     
__REG32 XY1IEN   : 1;     
__REG32 XY2IEN   : 1;     
__REG32 XY3IEN   : 1;     
__REG32 XY4IEN   : 1;     
__REG32 XY5IEN   : 1;     
__REG32 XY6IEN   : 1;     
__REG32 XY7IEN   : 1;     
__REG32 XY8IEN   : 1;     
__REG32 XY9IEN   : 1;     
__REG32 XY10IEN  : 1;     
__REG32 XY11IEN  : 1;     
__REG32 XY12IEN  : 1;     
__REG32 XY13IEN  : 1;     
__REG32 XY14IEN  : 1;     
__REG32 XY15IEN  : 1;     
__REG32 XY16IEN  : 1;     
__REG32 XY17IEN  : 1;     
__REG32 XY18IEN  : 1;     
__REG32 XY19IEN  : 1;     
__REG32 XY20IEN  : 1;     
__REG32 XY21IEN  : 1;     
__REG32 XY22IEN  : 1;     
__REG32 XY23IEN  : 1;     
__REG32 XY24IEN  : 1;     
__REG32 XY25IEN  : 1;     
__REG32 XY26IEN  : 1;     
__REG32 XY27IEN  : 1;     
__REG32 XY28IEN  : 1;     
__REG32 XY29IEN  : 1;     
__REG32 XY30IEN  : 1;     
__REG32 XY31IEN  : 1;     
} __XYINTEN_bits;

/* USB OTG X Filled Status Register */
typedef struct{
__REG32 XFILL0   : 1;     
__REG32 XFILL1   : 1;     
__REG32 XFILL2   : 1;     
__REG32 XFILL3   : 1;     
__REG32 XFILL4   : 1;     
__REG32 XFILL5   : 1;     
__REG32 XFILL6   : 1;     
__REG32 XFILL7   : 1;     
__REG32 XFILL8   : 1;     
__REG32 XFILL9   : 1;     
__REG32 XFILL10  : 1;     
__REG32 XFILL11  : 1;     
__REG32 XFILL12  : 1;     
__REG32 XFILL13  : 1;     
__REG32 XFILL14  : 1;     
__REG32 XFILL15  : 1;     
__REG32 XFILL16  : 1;     
__REG32 XFILL17  : 1;     
__REG32 XFILL18  : 1;     
__REG32 XFILL19  : 1;     
__REG32 XFILL20  : 1;     
__REG32 XFILL21  : 1;     
__REG32 XFILL22  : 1;     
__REG32 XFILL23  : 1;     
__REG32 XFILL24  : 1;     
__REG32 XFILL25  : 1;     
__REG32 XFILL26  : 1;     
__REG32 XFILL27  : 1;     
__REG32 XFILL28  : 1;     
__REG32 XFILL29  : 1;     
__REG32 XFILL30  : 1;     
__REG32 XFILL31  : 1;     
} __XFILLSTAT_bits;

/* USB OTG Y Filled Status Register */
typedef struct{
__REG32 YFILL0   : 1;     
__REG32 YFILL1   : 1;     
__REG32 YFILL2   : 1;     
__REG32 YFILL3   : 1;     
__REG32 YFILL4   : 1;     
__REG32 YFILL5   : 1;     
__REG32 YFILL6   : 1;     
__REG32 YFILL7   : 1;     
__REG32 YFILL8   : 1;     
__REG32 YFILL9   : 1;     
__REG32 YFILL10  : 1;     
__REG32 YFILL11  : 1;     
__REG32 YFILL12  : 1;     
__REG32 YFILL13  : 1;     
__REG32 YFILL14  : 1;     
__REG32 YFILL15  : 1;     
__REG32 YFILL16  : 1;     
__REG32 YFILL17  : 1;     
__REG32 YFILL18  : 1;     
__REG32 YFILL19  : 1;     
__REG32 YFILL20  : 1;     
__REG32 YFILL21  : 1;     
__REG32 YFILL22  : 1;     
__REG32 YFILL23  : 1;     
__REG32 YFILL24  : 1;     
__REG32 YFILL25  : 1;     
__REG32 YFILL26  : 1;     
__REG32 YFILL27  : 1;     
__REG32 YFILL28  : 1;     
__REG32 YFILL29  : 1;     
__REG32 YFILL30  : 1;     
__REG32 YFILL31  : 1;     
} __YFILLSTAT_bits;

/* USB OTG ETD Enable Set Register */
typedef struct{
__REG32 ETD0SET   : 1;     
__REG32 ETD1SET   : 1;     
__REG32 ETD2SET   : 1;     
__REG32 ETD3SET   : 1;     
__REG32 ETD4SET   : 1;     
__REG32 ETD5SET   : 1;     
__REG32 ETD6SET   : 1;     
__REG32 ETD7SET   : 1;     
__REG32 ETD8SET   : 1;     
__REG32 ETD9SET   : 1;     
__REG32 ETD10SET  : 1;     
__REG32 ETD11SET  : 1;     
__REG32 ETD12SET  : 1;     
__REG32 ETD13SET  : 1;     
__REG32 ETD14SET  : 1;     
__REG32 ETD15SET  : 1;     
__REG32 ETD16SET  : 1;     
__REG32 ETD17SET  : 1;     
__REG32 ETD18SET  : 1;     
__REG32 ETD19SET  : 1;     
__REG32 ETD20SET  : 1;     
__REG32 ETD21SET  : 1;     
__REG32 ETD22SET  : 1;     
__REG32 ETD23SET  : 1;     
__REG32 ETD24SET  : 1;     
__REG32 ETD25SET  : 1;     
__REG32 ETD26SET  : 1;     
__REG32 ETD27SET  : 1;     
__REG32 ETD28SET  : 1;     
__REG32 ETD29SET  : 1;     
__REG32 ETD30SET  : 1;     
__REG32 ETD31SET  : 1;     
} __ETDENSET_bits;

/* USB OTG ETD Enable Clear Register */
typedef struct{
__REG32 ETD0CLR   : 1;     
__REG32 ETD1CLR   : 1;     
__REG32 ETD2CLR   : 1;     
__REG32 ETD3CLR   : 1;     
__REG32 ETD4CLR   : 1;     
__REG32 ETD5CLR   : 1;     
__REG32 ETD6CLR   : 1;     
__REG32 ETD7CLR   : 1;     
__REG32 ETD8CLR   : 1;     
__REG32 ETD9CLR   : 1;     
__REG32 ETD10CLR  : 1;     
__REG32 ETD11CLR  : 1;     
__REG32 ETD12CLR  : 1;     
__REG32 ETD13CLR  : 1;     
__REG32 ETD14CLR  : 1;     
__REG32 ETD15CLR  : 1;     
__REG32 ETD16CLR  : 1;     
__REG32 ETD17CLR  : 1;     
__REG32 ETD18CLR  : 1;     
__REG32 ETD19CLR  : 1;     
__REG32 ETD20CLR  : 1;     
__REG32 ETD21CLR  : 1;     
__REG32 ETD22CLR  : 1;     
__REG32 ETD23CLR  : 1;     
__REG32 ETD24CLR  : 1;     
__REG32 ETD25CLR  : 1;     
__REG32 ETD26CLR  : 1;     
__REG32 ETD27CLR  : 1;     
__REG32 ETD28CLR  : 1;     
__REG32 ETD29CLR  : 1;     
__REG32 ETD30CLR  : 1;     
__REG32 ETD31CLR  : 1;     
} __ETDENCLR_bits;

/* USB OTG Immediate Interrupt Register */
typedef struct{
__REG32 IMMINT0   : 1;     
__REG32 IMMINT1   : 1;     
__REG32 IMMINT2   : 1;     
__REG32 IMMINT3   : 1;     
__REG32 IMMINT4   : 1;     
__REG32 IMMINT5   : 1;     
__REG32 IMMINT6   : 1;     
__REG32 IMMINT7   : 1;     
__REG32 IMMINT8   : 1;     
__REG32 IMMINT9   : 1;     
__REG32 IMMINT10  : 1;     
__REG32 IMMINT11  : 1;     
__REG32 IMMINT12  : 1;     
__REG32 IMMINT13  : 1;     
__REG32 IMMINT14  : 1;     
__REG32 IMMINT15  : 1;     
__REG32 IMMINT16  : 1;     
__REG32 IMMINT17  : 1;     
__REG32 IMMINT18  : 1;     
__REG32 IMMINT19  : 1;     
__REG32 IMMINT20  : 1;     
__REG32 IMMINT21  : 1;     
__REG32 IMMINT22  : 1;     
__REG32 IMMINT23  : 1;     
__REG32 IMMINT24  : 1;     
__REG32 IMMINT25  : 1;     
__REG32 IMMINT26  : 1;     
__REG32 IMMINT27  : 1;     
__REG32 IMMINT28  : 1;     
__REG32 IMMINT29  : 1;     
__REG32 IMMINT30  : 1;     
__REG32 IMMINT31  : 1;     
} __IMMEDINT_bits;

/* USB OTG ETD Done Status Register */
typedef struct{
__REG32 ETD0DONE   : 1;     
__REG32 ETD1DONE   : 1;     
__REG32 ETD2DONE   : 1;     
__REG32 ETD3DONE   : 1;     
__REG32 ETD4DONE   : 1;     
__REG32 ETD5DONE   : 1;     
__REG32 ETD6DONE   : 1;     
__REG32 ETD7DONE   : 1;     
__REG32 ETD8DONE   : 1;     
__REG32 ETD9DONE   : 1;     
__REG32 ETD10DONE  : 1;     
__REG32 ETD11DONE  : 1;     
__REG32 ETD12DONE  : 1;     
__REG32 ETD13DONE  : 1;     
__REG32 ETD14DONE  : 1;     
__REG32 ETD15DONE  : 1;     
__REG32 ETD16DONE  : 1;     
__REG32 ETD17DONE  : 1;     
__REG32 ETD18DONE  : 1;     
__REG32 ETD19DONE  : 1;     
__REG32 ETD20DONE  : 1;     
__REG32 ETD21DONE  : 1;     
__REG32 ETD22DONE  : 1;     
__REG32 ETD23DONE  : 1;     
__REG32 ETD24DONE  : 1;     
__REG32 ETD25DONE  : 1;     
__REG32 ETD26DONE  : 1;     
__REG32 ETD27DONE  : 1;     
__REG32 ETD28DONE  : 1;     
__REG32 ETD29DONE  : 1;     
__REG32 ETD30DONE  : 1;     
__REG32 ETD31DONE  : 1;     
} __ETDDONESTAT_bits;

/* USB OTG ETD Done Enable Register */
typedef struct{
__REG32 ETD0DNEN   : 1;     
__REG32 ETD1DNEN   : 1;     
__REG32 ETD2DNEN   : 1;     
__REG32 ETD3DNEN   : 1;     
__REG32 ETD4DNEN   : 1;     
__REG32 ETD5DNEN   : 1;     
__REG32 ETD6DNEN   : 1;     
__REG32 ETD7DNEN   : 1;     
__REG32 ETD8DNEN   : 1;     
__REG32 ETD9DNEN   : 1;     
__REG32 ETD10DNEN  : 1;     
__REG32 ETD11DNEN  : 1;     
__REG32 ETD12DNEN  : 1;     
__REG32 ETD13DNEN  : 1;     
__REG32 ETD14DNEN  : 1;     
__REG32 ETD15DNEN  : 1;     
__REG32 ETD16DNEN  : 1;     
__REG32 ETD17DNEN  : 1;     
__REG32 ETD18DNEN  : 1;     
__REG32 ETD19DNEN  : 1;     
__REG32 ETD20DNEN  : 1;     
__REG32 ETD21DNEN  : 1;     
__REG32 ETD22DNEN  : 1;     
__REG32 ETD23DNEN  : 1;     
__REG32 ETD24DNEN  : 1;     
__REG32 ETD25DNEN  : 1;     
__REG32 ETD26DNEN  : 1;     
__REG32 ETD27DNEN  : 1;     
__REG32 ETD28DNEN  : 1;     
__REG32 ETD29DNEN  : 1;     
__REG32 ETD30DNEN  : 1;     
__REG32 ETD31DNEN  : 1;     
} __ETDDONEN_bits;

/* USB OTG Frame Number Register */
typedef struct{
__REG32 FRMNUMB  :16;     
__REG32          :16;     
} __FRMNUB_bits;

/* USB OTG Low Speed Threshold Register */
typedef struct{
__REG32 LSTHRESH  :11;     
__REG32           :21;     
} __LSTHRESH_bits;

/* USB OTG Root Hub Descriptor A Register */
typedef struct{
__REG32 NDNSTMPRT  : 8;     
__REG32 NOPWRSWT   : 1;     
__REG32 PWRSWTMD   : 1;     
__REG32 DEVTYPE    : 1;     
__REG32 OVRCURPM   : 1;     
__REG32 NOOVRCURP  : 1;     
__REG32            :11;     
__REG32 PWRTOGOOD  : 8;     
} __ROOTHUBA_bits;

/* USB OTG Root Hub Descriptor B Register */
typedef struct{
__REG32 DEVREMOVE  : 8;     
__REG32            : 8;     
__REG32 PRTPWRCM   : 8;     
__REG32            : 8;     
} __ROOTHUBB_bits;

/* USB OTG Root Hub Status Register */
typedef struct{
__REG32 LOCPWRS    : 1;     
__REG32 OVRCURI    : 1;     
__REG32            :13;     
__REG32 DEVCONWUE  : 1;     
__REG32            : 1;     
__REG32 OVRCURCHG  : 1;     
__REG32            :13;     
__REG32 CLRRMTWUE  : 1;     
} __ROOTSTAT_bits;

/* USB OTG Port Status 1–3 Register */
typedef struct{
__REG32 CURCONST    : 1;     
__REG32 PRTENABST   : 1;     
__REG32 PRTSUSPST   : 1;     
__REG32 PRTOVRCURI  : 1;     
__REG32 PRTRSTST    : 1;     
__REG32             : 3;     
__REG32 PRTPWRST    : 1;     
__REG32 LSDEVCON    : 1;     
__REG32             : 6;     
__REG32 CONNECTSC   : 1;     
__REG32 PRTENBLSC   : 1;     
__REG32 PRTSTATSC   : 1;     
__REG32 OVRCURIC    : 1;     
__REG32 PRTRSTSC    : 1;     
__REG32             :11;     
} __PORTSTAT_bits;

/* OTG Transfer Descriptor Format WORD0 */
typedef struct{
__REG32            :14;     
__REG32 FORMAT     : 2;     
__REG32 MAXPKTSIZ  :10;     
__REG32            : 3;     
__REG32 OVRRUN     : 1;     
__REG32 SETUP      : 1;     
__REG32 STALL      : 1;     
} __OTG_EP_DWORD0_bits;

/* OTG Transfer Descriptor Format WORD1 */
typedef struct{
__REG32 XBUFSRTAD  :16;     
__REG32 YBUFSRTAD  :16;     
} __OTG_EP_DWORD1_bits;

/* OTG Host Endpoint Transfer Descriptor WORD3 Format */
typedef union{
  //OTG_EPx_DWORD3
  //OTG_EP1x_DWORD3
  //OTG_EP2x_DWORD3
  //OTG_EP3x_DWORD3
  struct {
__REG32 TTLBTECNT   :21;     
__REG32 BUFFERSIZE  :11;     
  };
  //OTG_EPx_DWORD3 Isochronous
  //OTG_EP1x_DWORD3 Isochronous
  //OTG_EP2x_DWORD3 Isochronous
  //OTG_EP3x_DWORD3 Isochronous
  struct {
__REG32 PKTLEN0     :10;     
__REG32             : 6;     
__REG32 PKTLEN1     :10;     
__REG32             : 5;     
__REG32 FRAMECNT    : 1;     
  };
} __OTG_EP_DWORD3_bits;

/* OTG Function Command Status Register */
typedef struct{
__REG32 RESETDET   : 1;     
__REG32 RSMINPROG  : 1;     
__REG32 SUSPDET    : 1;     
__REG32 BADISOAP   : 1;     
__REG32            : 3;     
__REG32 SOFTRESET  : 1;     
__REG32            :24;     
} __FUNCOMSTAT_bits;

/* OTG Device Address Register */
typedef struct{
__REG32 DEVADDR  : 7;     
__REG32          :25;     
} __DEVADDR_bits;

/* OTG System Interrupt Status Register */
typedef struct{
__REG32 RESETINT    : 1;     
__REG32 RSMFINNT    : 1;     
__REG32 SUSPDETINT  : 1;     
__REG32 DONEREGINT  : 1;     
__REG32 SOFDETINT   : 1;     
__REG32             :27;     
} __SYSINTSTAT_bits;

/* OTG System Interrupt Enables Register */
typedef struct{
__REG32 RESETIEN    : 1;     
__REG32 RSMFINIEN   : 1;     
__REG32 SUSPDETIEN  : 1;     
__REG32 DONEREGIEN  : 1;     
__REG32 SOFDETIEN   : 1;     
__REG32             :27;     
} __SYSINTEN_bits;

/* OTG X Buffer Interrupt Status Register */
typedef struct{
__REG32 XBUF0OUTINT   : 1;     
__REG32 XBUF0ININT    : 1;     
__REG32 XBUF1OUTINT   : 1;     
__REG32 XBUF1ININT    : 1;     
__REG32 XBUF2OUTINT   : 1;     
__REG32 XBUF2ININT    : 1;     
__REG32 XBUF3OUTINT   : 1;     
__REG32 XBUF3ININT    : 1;     
__REG32 XBUF4OUTINT   : 1;     
__REG32 XBUF4ININT    : 1;     
__REG32 XBUF5OUTINT   : 1;     
__REG32 XBUF5ININT    : 1;     
__REG32 XBUF6OUTINT   : 1;     
__REG32 XBUF6ININT    : 1;     
__REG32 XBUF7OUTINT   : 1;     
__REG32 XBUF7ININT    : 1;     
__REG32 XBUF8OUTINT   : 1;     
__REG32 XBUF8ININT    : 1;     
__REG32 XBUF9OUTINT   : 1;     
__REG32 XBUF9ININT    : 1;     
__REG32 XBUF10OUTINT  : 1;     
__REG32 XBUF10ININT   : 1;     
__REG32 XBUF11OUTINT  : 1;     
__REG32 XBUF11ININT   : 1;     
__REG32 XBUF12OUTINT  : 1;     
__REG32 XBUF12ININT   : 1;     
__REG32 XBUF13OUTINT  : 1;     
__REG32 XBUF13ININT   : 1;     
__REG32 XBUF14OUTINT  : 1;     
__REG32 XBUF14ININT   : 1;     
__REG32 XBUF15OUTINT  : 1;     
__REG32 XBUF15ININT   : 1;     
} __XBUFINTSTAT_bits;

/* OTG Y Buffer Interrupt Status Register */
typedef struct{
__REG32 YBUF0OUTINT   : 1;     
__REG32 YBUF0ININT    : 1;     
__REG32 YBUF1OUTINT   : 1;     
__REG32 YBUF1ININT    : 1;     
__REG32 YBUF2OUTINT   : 1;     
__REG32 YBUF2ININT    : 1;     
__REG32 YBUF3OUTINT   : 1;     
__REG32 YBUF3ININT    : 1;     
__REG32 YBUF4OUTINT   : 1;     
__REG32 YBUF4ININT    : 1;     
__REG32 YBUF5OUTINT   : 1;     
__REG32 YBUF5ININT    : 1;     
__REG32 YBUF6OUTINT   : 1;     
__REG32 YBUF6ININT    : 1;     
__REG32 YBUF7OUTINT   : 1;     
__REG32 YBUF7ININT    : 1;     
__REG32 YBUF8OUTINT   : 1;     
__REG32 YBUF8ININT    : 1;     
__REG32 YBUF9OUTINT   : 1;     
__REG32 YBUF9ININT    : 1;     
__REG32 YBUF10OUTINT  : 1;     
__REG32 YBUF10ININT   : 1;     
__REG32 YBUF11OUTINT  : 1;     
__REG32 YBUF11ININT   : 1;     
__REG32 YBUF12OUTINT  : 1;     
__REG32 YBUF12ININT   : 1;     
__REG32 YBUF13OUTINT  : 1;     
__REG32 YBUF13ININT   : 1;     
__REG32 YBUF14OUTINT  : 1;     
__REG32 YBUF14ININT   : 1;     
__REG32 YBUF15OUTINT  : 1;     
__REG32 YBUF15ININT   : 1;     
} __YBUFINTSTAT_bits;

/* OTG XY Interrupt Enable Register */
typedef struct{
__REG32 XYBUF0OUTINT   : 1;     
__REG32 XYBUF0ININT    : 1;     
__REG32 XYBUF1OUTINT   : 1;     
__REG32 XYBUF1ININT    : 1;     
__REG32 XYBUF2OUTINT   : 1;     
__REG32 XYBUF2ININT    : 1;     
__REG32 XYBUF3OUTINT   : 1;     
__REG32 XYBUF3ININT    : 1;     
__REG32 XYBUF4OUTINT   : 1;     
__REG32 XYBUF4ININT    : 1;     
__REG32 XYBUF5OUTINT   : 1;     
__REG32 XYBUF5ININT    : 1;     
__REG32 XYBUF6OUTINT   : 1;     
__REG32 XYBUF6ININT    : 1;     
__REG32 XYBUF7OUTINT   : 1;     
__REG32 XYBUF7ININT    : 1;     
__REG32 XYBUF8OUTINT   : 1;     
__REG32 XYBUF8ININT    : 1;     
__REG32 XYBUF9OUTINT   : 1;     
__REG32 XYBUF9ININT    : 1;     
__REG32 XYBUF10OUTINT  : 1;     
__REG32 XYBUF10ININT   : 1;     
__REG32 XYBUF11OUTINT  : 1;     
__REG32 XYBUF11ININT   : 1;     
__REG32 XYBUF12OUTINT  : 1;     
__REG32 XYBUF12ININT   : 1;     
__REG32 XYBUF13OUTINT  : 1;     
__REG32 XYBUF13ININT   : 1;     
__REG32 XYBUF14OUTINT  : 1;     
__REG32 XYBUF14ININT   : 1;     
__REG32 XYBUF15OUTINT  : 1;     
__REG32 XYBUF15ININT   : 1;     
} __XYINT_INT_EN_bits;

/* OTG X Filled Status Register */
typedef struct{
__REG32 XFILL0OUT   : 1;     
__REG32 XFILL0IN    : 1;     
__REG32 XFILL1OUT   : 1;     
__REG32 XFILL1IN    : 1;     
__REG32 XFILL2OUT   : 1;     
__REG32 XFILL2IN    : 1;     
__REG32 XFILL3OUT   : 1;     
__REG32 XFILL3IN    : 1;     
__REG32 XFILL4OUT   : 1;     
__REG32 XFILL4IN    : 1;     
__REG32 XFILL5OUT   : 1;     
__REG32 XFILL5IN    : 1;     
__REG32 XFILL6OUT   : 1;     
__REG32 XFILL6IN    : 1;     
__REG32 XFILL7OUT   : 1;     
__REG32 XFILL7IN    : 1;     
__REG32 XFILL8OUT   : 1;     
__REG32 XFILL8IN    : 1;     
__REG32 XFILL9OUT   : 1;     
__REG32 XFILL9IN    : 1;     
__REG32 XFILL10OUT  : 1;     
__REG32 XFILL10IN   : 1;     
__REG32 XFILL11OUT  : 1;     
__REG32 XFILL11IN   : 1;     
__REG32 XFILL12OUT  : 1;     
__REG32 XFILL12IN   : 1;     
__REG32 XFILL13OUT  : 1;     
__REG32 XFILL13IN   : 1;     
__REG32 XFILL14OUT  : 1;     
__REG32 XFILL14IN   : 1;     
__REG32 XFILL15OUT  : 1;     
__REG32 XFILL15IN   : 1;     
} __OTG_XFILLSTAT_bits;

/* OTG Y Filled Status Register */
typedef struct{
__REG32 YFILL0OUT   : 1;     
__REG32 YFILL0IN    : 1;     
__REG32 YFILL1OUT   : 1;     
__REG32 YFILL1IN    : 1;     
__REG32 YFILL2OUT   : 1;     
__REG32 YFILL2IN    : 1;     
__REG32 YFILL3OUT   : 1;     
__REG32 YFILL3IN    : 1;     
__REG32 YFILL4OUT   : 1;     
__REG32 YFILL4IN    : 1;     
__REG32 YFILL5OUT   : 1;     
__REG32 YFILL5IN    : 1;     
__REG32 YFILL6OUT   : 1;     
__REG32 YFILL6IN    : 1;     
__REG32 YFILL7OUT   : 1;     
__REG32 YFILL7IN    : 1;     
__REG32 YFILL8OUT   : 1;     
__REG32 YFILL8IN    : 1;     
__REG32 YFILL9OUT   : 1;     
__REG32 YFILL9IN    : 1;     
__REG32 YFILL10OUT  : 1;     
__REG32 YFILL10IN   : 1;     
__REG32 YFILL11OUT  : 1;     
__REG32 YFILL11IN   : 1;     
__REG32 YFILL12OUT  : 1;     
__REG32 YFILL12IN   : 1;     
__REG32 YFILL13OUT  : 1;     
__REG32 YFILL13IN   : 1;     
__REG32 YFILL14OUT  : 1;     
__REG32 YFILL14IN   : 1;     
__REG32 YFILL15OUT  : 1;     
__REG32 YFILL15IN   : 1;     
} __OTG_YFILLSTAT_bits;

/* OTG Endpoint Enables Register */
typedef struct{
__REG32 EP0OUTEN   : 1;     
__REG32 EP0INEN    : 1;     
__REG32 EP1OUTEN   : 1;     
__REG32 EP1INEN    : 1;     
__REG32 EP2OUTEN   : 1;     
__REG32 EP2INEN    : 1;     
__REG32 EP3OUTEN   : 1;     
__REG32 EP3INEN    : 1;     
__REG32 EP4OUTEN   : 1;     
__REG32 EP4INEN    : 1;     
__REG32 EP5OUTEN   : 1;     
__REG32 EP5INEN    : 1;     
__REG32 EP6OUTEN   : 1;     
__REG32 EP6INEN    : 1;     
__REG32 EP7OUTEN   : 1;     
__REG32 EP7INEN    : 1;     
__REG32 EP8OUTEN   : 1;     
__REG32 EP8INEN    : 1;     
__REG32 EP9OUTEN   : 1;     
__REG32 EP9INEN    : 1;     
__REG32 EP10OUTEN  : 1;     
__REG32 EP10INEN   : 1;     
__REG32 EP11OUTEN  : 1;     
__REG32 EP11INEN   : 1;     
__REG32 EP12OUTEN  : 1;     
__REG32 EP12INEN   : 1;     
__REG32 EP13OUTEN  : 1;     
__REG32 EP13INEN   : 1;     
__REG32 EP14OUTEN  : 1;     
__REG32 EP14INEN   : 1;     
__REG32 EP15OUTEN  : 1;     
__REG32 EP15INEN   : 1;     
} __ENDPNTEN_bits;

/* OTG Endpoint Ready Set Register */
typedef struct{
__REG32 EP0OUTREADY   : 1;     
__REG32 EP0INREADY    : 1;     
__REG32 EP1OUTREADY   : 1;     
__REG32 EP1INREADY    : 1;     
__REG32 EP2OUTREADY   : 1;     
__REG32 EP2INREADY    : 1;     
__REG32 EP3OUTREADY   : 1;     
__REG32 EP3INREADY    : 1;     
__REG32 EP4OUTREADY   : 1;     
__REG32 EP4INREADY    : 1;     
__REG32 EP5OUTREADY   : 1;     
__REG32 EP5INREADY    : 1;     
__REG32 EP6OUTREADY   : 1;     
__REG32 EP6INREADY    : 1;     
__REG32 EP7OUTREADY   : 1;     
__REG32 EP7INREADY    : 1;     
__REG32 EP8OUTREADY   : 1;     
__REG32 EP8INREADY    : 1;     
__REG32 EP9OUTREADY   : 1;     
__REG32 EP9INREADY    : 1;     
__REG32 EP10OUTREADY  : 1;     
__REG32 EP10INREADY   : 1;     
__REG32 EP11OUTREADY  : 1;     
__REG32 EP11INREADY   : 1;     
__REG32 EP12OUTREADY  : 1;     
__REG32 EP12INREADY   : 1;     
__REG32 EP13OUTREADY  : 1;     
__REG32 EP13INREADY   : 1;     
__REG32 EP14OUTREADY  : 1;     
__REG32 EP14INREADY   : 1;     
__REG32 EP15OUTREADY  : 1;     
__REG32 EP15INREADY   : 1;     
} __ENDPNRDY_bits;

/* OTG Immediate Interrupt Register */
typedef struct{
__REG32 IM0OUTINT   : 1;     
__REG32 IM0ININT    : 1;     
__REG32 IM1OUTINT   : 1;     
__REG32 IM1ININT    : 1;     
__REG32 IM2OUTINT   : 1;     
__REG32 IM2ININT    : 1;     
__REG32 IM3OUTINT   : 1;     
__REG32 IM3ININT    : 1;     
__REG32 IM4OUTINT   : 1;     
__REG32 IM4ININT    : 1;     
__REG32 IM5OUTINT   : 1;     
__REG32 IM5ININT    : 1;     
__REG32 IM6OUTINT   : 1;     
__REG32 IM6ININT    : 1;     
__REG32 IM7OUTINT   : 1;     
__REG32 IM7ININT    : 1;     
__REG32 IM8OUTINT   : 1;     
__REG32 IM8ININT    : 1;     
__REG32 IM9OUTINT   : 1;     
__REG32 IM9ININT    : 1;     
__REG32 IM10OUTINT  : 1;     
__REG32 IM10ININT   : 1;     
__REG32 IM11OUTINT  : 1;     
__REG32 IM11ININT   : 1;     
__REG32 IM12OUTINT  : 1;     
__REG32 IM12ININT   : 1;     
__REG32 IM13OUTINT  : 1;     
__REG32 IM13ININT   : 1;     
__REG32 IM14OUTINT  : 1;     
__REG32 IM14ININT   : 1;     
__REG32 IM15OUTINT  : 1;     
__REG32 IM15ININT   : 1;     
} __IMEDINT_bits;

/* OTG Endpoint Done Status Register */
typedef struct{
__REG32 EP0OUTDONE   : 1;     
__REG32 EP0INDONE    : 1;     
__REG32 EP1OUTDONE   : 1;     
__REG32 EP1INDONE    : 1;     
__REG32 EP2OUTDONE   : 1;     
__REG32 EP2INDONE    : 1;     
__REG32 EP3OUTDONE   : 1;     
__REG32 EP3INDONE    : 1;     
__REG32 EP4OUTDONE   : 1;     
__REG32 EP4INDONE    : 1;     
__REG32 EP5OUTDONE   : 1;     
__REG32 EP5INDONE    : 1;     
__REG32 EP6OUTDONE   : 1;     
__REG32 EP6INDONE    : 1;     
__REG32 EP7OUTDONE   : 1;     
__REG32 EP7INDONE    : 1;     
__REG32 EP8OUTDONE   : 1;     
__REG32 EP8INDONE    : 1;     
__REG32 EP9OUTDONE   : 1;     
__REG32 EP9INDONE    : 1;     
__REG32 EP10OUTDONE  : 1;     
__REG32 EP10INDONE   : 1;     
__REG32 EP11OUTDONE  : 1;     
__REG32 EP11INDONE   : 1;     
__REG32 EP12OUTDONE  : 1;     
__REG32 EP12INDONE   : 1;     
__REG32 EP13OUTDONE  : 1;     
__REG32 EP13INDONE   : 1;     
__REG32 EP14OUTDONE  : 1;     
__REG32 EP14INDONE   : 1;     
__REG32 EP15OUTDONE  : 1;     
__REG32 EP15INDONE   : 1;     
} __EPNTDONESTAT_bits;

/* OTG Endpoint Done Enable Register */
typedef struct{
__REG32 EP0OUTDNEN   : 1;     
__REG32 EP0INDNEN    : 1;     
__REG32 EP1OUTDNEN   : 1;     
__REG32 EP1INDNEN    : 1;     
__REG32 EP2OUTDNEN   : 1;     
__REG32 EP2INDNEN    : 1;     
__REG32 EP3OUTDNEN   : 1;     
__REG32 EP3INDNEN    : 1;     
__REG32 EP4OUTDNEN   : 1;     
__REG32 EP4INDNEN    : 1;     
__REG32 EP5OUTDNEN   : 1;     
__REG32 EP5INDNEN    : 1;     
__REG32 EP6OUTDNEN   : 1;     
__REG32 EP6INDNEN    : 1;     
__REG32 EP7OUTDNEN   : 1;     
__REG32 EP7INDNEN    : 1;     
__REG32 EP8OUTDNEN   : 1;     
__REG32 EP8INDNEN    : 1;     
__REG32 EP9OUTDNEN   : 1;     
__REG32 EP9INDNEN    : 1;     
__REG32 EP10OUTDNEN  : 1;     
__REG32 EP10INDNEN   : 1;     
__REG32 EP11OUTDNEN  : 1;     
__REG32 EP11INDNEN   : 1;     
__REG32 EP12OUTDNEN  : 1;     
__REG32 EP12INDNEN   : 1;     
__REG32 EP13OUTDNEN  : 1;     
__REG32 EP13INDNEN   : 1;     
__REG32 EP14OUTDNEN  : 1;     
__REG32 EP14INDNEN   : 1;     
__REG32 EP15OUTDNEN  : 1;     
__REG32 EP15INDNEN   : 1;     
} __EPNTDONEEN_bits;

/* OTG Endpoint Toggle Bits Register */
typedef struct{
__REG32 EP0OUTTOG   : 1;     
__REG32 EP0INTOG    : 1;     
__REG32 EP1OUTTOG   : 1;     
__REG32 EP1INTOG    : 1;     
__REG32 EP2OUTTOG   : 1;     
__REG32 EP2INTOG    : 1;     
__REG32 EP3OUTTOG   : 1;     
__REG32 EP3INTOG    : 1;     
__REG32 EP4OUTTOG   : 1;     
__REG32 EP4INTOG    : 1;     
__REG32 EP5OUTTOG   : 1;     
__REG32 EP5INTOG    : 1;     
__REG32 EP6OUTTOG   : 1;     
__REG32 EP6INTOG    : 1;     
__REG32 EP7OUTTOG   : 1;     
__REG32 EP7INTOG    : 1;     
__REG32 EP8OUTTOG   : 1;     
__REG32 EP8INTOG    : 1;     
__REG32 EP9OUTTOG   : 1;     
__REG32 EP9INTOG    : 1;     
__REG32 EP10OUTTOG  : 1;     
__REG32 EP10INTOG   : 1;     
__REG32 EP11OUTTOG  : 1;     
__REG32 EP11INTOG   : 1;     
__REG32 EP12OUTTOG  : 1;     
__REG32 EP12INTOG   : 1;     
__REG32 EP13OUTTOG  : 1;     
__REG32 EP13INTOG   : 1;     
__REG32 EP14OUTTOG  : 1;     
__REG32 EP14INTOG   : 1;     
__REG32 EP15OUTTOG  : 1;     
__REG32 EP15INTOG   : 1;     
} __EPNTTOGBITS_bits;

/* OTG Frame Number and Endpoint Ready Clear Register */
typedef union{
  //FNEPRDYCLR Write
__REG32 EPRDYCLEAR  :32;     
  //FNEPRDYCLR Read
  struct {
__REG32 FRMNUMB     :11;     
__REG32             :21;     
  };
} __FNEPRDYCLR_bits;

/* USB OTG DMA Revision Register */
typedef struct{
__REG32 REVCODE  : 8;     
__REG32          :24;     
} __DMAREV_bits;

/* USB OTG DMA Interrupt Status Register */
typedef struct{
__REG32 ETDERR  : 1;     
__REG32 EPERR   : 1;     
__REG32         :30;     
} __DMAINTSTAT_bits;

/* USB OTG DMA Interrupt Enable Register */
typedef struct{
__REG32 ETDERRINTEN  : 1;     
__REG32 EPERRINTEN   : 1;     
__REG32              :30;     
} __DMAINTEN_bits;

/* USB OTG Misc Control Register */
typedef struct{
__REG32 FILTCC      : 1;     
__REG32 ARBMODE     : 1;     
__REG32 SKPRTRY     : 1;     
__REG32 ISOPREVFRM  : 1;     
__REG32             :28;     
} __MISCCONTROL_bits;

/* -------------------------------------------------------------------------*/
/*      PCMCIA Registers                                                       */
/* -------------------------------------------------------------------------*/
/* PCMCIA Input Pins Register */
typedef struct{
__REG32 VS       : 2;     
__REG32 WP       : 1;     
__REG32 CD       : 2;     
__REG32 BVD1     : 1;     
__REG32 BVD2     : 1;     
__REG32 RDY      : 1;     
__REG32 POWERON  : 1;     
__REG32          :23;     
} __PIPR_bits;

/* PCMCIA Status Change Register */
typedef struct{
__REG32 VSC1   : 1;     
__REG32 VSC2   : 1;     
__REG32 WPC    : 1;     
__REG32 CDC1   : 1;     
__REG32 CDC2   : 1;     
__REG32 BVDC1  : 1;     
__REG32 BVDC2  : 1;     
__REG32 RDYL   : 1;     
__REG32 RDYH   : 1;     
__REG32 RDYF   : 1;     
__REG32 RDYR   : 1;     
__REG32 POWC   : 1;     
__REG32        :20;     
} __PSCR_bits;

/* PCMCIA Enable Register */
typedef struct{
__REG32 VSE1       : 1;     
__REG32 VSE2       : 1;     
__REG32 WPE        : 1;     
__REG32 CDE1       : 1;     
__REG32 CDE2       : 1;     
__REG32 BVDE1      : 1;     
__REG32 BVDE2      : 1;     
__REG32 RDYLE      : 1;     
__REG32 RDYHE      : 1;     
__REG32 RDYFE      : 1;     
__REG32 RDYRE      : 1;     
__REG32 POWERONEN  : 1;     
__REG32 ERRINTEN   : 1;     
__REG32            :19;     
} __PER_bits;

/* PCMCIA Base Registers */
typedef struct{
__REG32 PBA  :11;     
__REG32      :21;     
} __PBR_bits;

/* PCMCIA Option Registers */
typedef struct{
__REG32 BSIZE  : 4;     
__REG32        : 1;     
__REG32 PSHT   : 6;     
__REG32 PSST   : 6;     
__REG32 PSL    : 7;     
__REG32 PPS    : 1;     
__REG32 PRS    : 2;     
__REG32 WP     : 1;     
__REG32 WPEN   : 1;     
__REG32 PV     : 1;     
__REG32        : 2;     
} __POR_bits;

/* PCMCIA Offset Registers */
typedef struct{
__REG32 POFA  :11;     
__REG32       :21;     
} __POFR_bits;

/* PCMCIA General Control Register */
typedef struct{
__REG32 RESET   : 1;     
__REG32 POE     : 1;     
__REG32 SPKREN  : 1;     
__REG32 LPMEN   : 1;     
__REG32         :28;     
} __PGCR_bits;

/* PCMCIA General Control Register */
typedef struct{
__REG32 WPE    : 1;     
__REG32 CDE    : 1;     
__REG32 SE     : 1;     
__REG32 LPE    : 1;     
__REG32 NWINE  : 1;     
__REG32        :27;     
} __PGSR_bits;

/* -------------------------------------------------------------------------*/
/*      Keypad Port (KPP)                                                   */
/* -------------------------------------------------------------------------*/
/* Keypad Control Register */
typedef struct{
__REG16 KRE  : 8;     
__REG16 KCO  : 8;     
} __KPCR_bits;

/* Keypad Status Register */
typedef struct{
__REG16 KPKD    : 1;     
__REG16 KPKR    : 1;     
__REG16 KDSC    : 1;     
__REG16 KRSS    : 1;     
__REG16         : 4;     
__REG16 KDIE    : 1;     
__REG16 KRIE    : 1;     
__REG16 KPP_EN  : 1;     
__REG16         : 5;     
} __KPSR_bits;

/* Keypad Data Direction Register */
typedef struct{
__REG16 KRDD  : 8;     
__REG16 KCDD  : 8;     
} __KDDR_bits;

/* Keypad Data Direction Register */
typedef struct{
__REG16 KRD  : 8;     
__REG16 KCD  : 8;     
} __KPDR_bits;

/* -------------------------------------------------------------------------*/
/*      Fast InfraRed Interface (FIRI) Module                               */
/* -------------------------------------------------------------------------*/
/* FIRI Control Register */
typedef struct{
__REG32 OSF  : 4;     
__REG32      : 1;     
__REG32 BL   : 7;     
__REG32      :20;     
} __FIRICR_bits;

/* FIRI Transmitter Control Register */
typedef struct{
__REG32 TE     : 1;     
__REG32 TM     : 2;     
__REG32 TPP    : 1;     
__REG32 SIP    : 1;     
__REG32 PC     : 1;     
__REG32 PCF    : 1;     
__REG32 TFUIE  : 1;     
__REG32 TPEIE  : 1;     
__REG32 TCIE   : 1;     
__REG32 TDT    : 3;     
__REG32 SRF    : 2;     
__REG32        : 1;     
__REG32 TPA    : 8;     
__REG32 HAG    : 1;     
__REG32        : 7;     
} __FIRITCR_bits;

/* FIRI Transmitter Count Register */
typedef struct{
__REG32 TPL  :11;     
__REG32      :21;     
} __FIRITCTR_bits;

/* FIRI Receiver Control Register */
typedef struct{
__REG32 RE     : 1;     
__REG32 RM     : 2;     
__REG32 RPP    : 1;     
__REG32 RFOIE  : 1;     
__REG32 PAIE   : 1;     
__REG32 RPEIE  : 1;     
__REG32 RPA    : 1;     
__REG32 RDT    : 3;     
__REG32 RPEDE  : 1;     
__REG32        : 4;     
__REG32 RA     : 8;     
__REG32 RAM    : 1;     
__REG32        : 7;     
} __FIRIRCR_bits;

/* FIRI Transmit Status Register */
typedef struct{
__REG32 TFU   : 1;     
__REG32 TPE   : 1;     
__REG32 SIPE  : 1;     
__REG32 TC    : 1;     
__REG32       : 4;     
__REG32 TFP   : 8;     
__REG32       :16;     
} __FIRITSR_bits;

/* FIRI Receive Status Register */
typedef struct{
__REG32 DDE   : 1;     
__REG32 CRCE  : 1;     
__REG32 BAM   : 1;     
__REG32 RFO   : 1;     
__REG32 RPE   : 1;     
__REG32 PAS   : 1;     
__REG32       : 2;     
__REG32 RFP   : 8;     
__REG32       :16;     
} __FIRIRSR_bits;

/* -------------------------------------------------------------------------*/
/*      One Wire                                                       */
/* -------------------------------------------------------------------------*/
/* O-Wire Control Register */
typedef struct{
__REG16       : 3;     
__REG16 RDST  : 1;     
__REG16 WR1   : 1;     
__REG16 WR0   : 1;     
__REG16 PST   : 1;     
__REG16 RPP   : 1;     
__REG16       : 8;     
} __OW_CONTROL_bits;

/* O-Wire Time Divider Register */
typedef struct{
__REG16 DVDR  : 8;     
__REG16       : 8;     
} __OW_TIME_DIVIDER_bits;


/* O-Wire Reset Register */
typedef struct{
__REG16 RST  : 1;     
__REG16      :15;     
} __OW_RESET_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/
/***************************************************************************
 **
 **  Interrupt Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(INTCNTL,                   0x10040000,__READ_WRITE,__INTCNTL_bits);
__IO_REG32_BIT(NIMASK,                    0x10040004,__READ_WRITE,__NIMASK_bits);
__IO_REG32_BIT(INTENNUM,                  0x10040008,__READ_WRITE,__INTENNUM_bits);
__IO_REG32_BIT(INTDISNUM,                 0x1004000C,__READ_WRITE,__INTDISNUM_bits);
__IO_REG32_BIT(INTENABLEH,                0x10040010,__READ_WRITE,__INTENABLEH_bits);
__IO_REG32_BIT(INTENABLEL,                0x10040014,__READ_WRITE,__INTENABLEL_bits);
__IO_REG32_BIT(INTTYPEH,                  0x10040018,__READ_WRITE,__INTTYPEH_bits);
__IO_REG32_BIT(INTTYPEL,                  0x1004001C,__READ_WRITE,__INTTYPEL_bits);
__IO_REG32_BIT(NIPRIORITY7,               0x10040020,__READ_WRITE,__NIPRIORITY7_bits);
__IO_REG32_BIT(NIPRIORITY6,               0x10040024,__READ_WRITE,__NIPRIORITY6_bits);
__IO_REG32_BIT(NIPRIORITY5,               0x10040028,__READ_WRITE,__NIPRIORITY5_bits);
__IO_REG32_BIT(NIPRIORITY4,               0x1004002C,__READ_WRITE,__NIPRIORITY4_bits);
__IO_REG32_BIT(NIPRIORITY3,               0x10040030,__READ_WRITE,__NIPRIORITY3_bits);
__IO_REG32_BIT(NIPRIORITY2,               0x10040034,__READ_WRITE,__NIPRIORITY2_bits);
__IO_REG32_BIT(NIPRIORITY1,               0x10040038,__READ_WRITE,__NIPRIORITY1_bits);
__IO_REG32_BIT(NIPRIORITY0,               0x1004003C,__READ_WRITE,__NIPRIORITY0_bits);
__IO_REG32_BIT(NIVECSR,                   0x10040040,__READ      ,__NIVECSR_bits);
__IO_REG32(    FIVECSR,                   0x10040044,__READ      );
__IO_REG32_BIT(INTSRCH,                   0x10040048,__READ      ,__INTSRCH_bits);
__IO_REG32_BIT(INTSRCL,                   0x1004004C,__READ      ,__INTSRCL_bits);
__IO_REG32_BIT(INTFRCH,                   0x10040050,__READ_WRITE,__INTFRCH_bits);
__IO_REG32_BIT(INTFRCL,                   0x10040054,__READ_WRITE,__INTFRCL_bits);
__IO_REG32_BIT(NIPNDH,                    0x10040058,__READ      ,__NIPNDH_bits);
__IO_REG32_BIT(NIPNDL,                    0x1004005C,__READ      ,__NIPNDL_bits);
__IO_REG32_BIT(FIPNDH,                    0x10040060,__READ      ,__FIPNDH_bits);
__IO_REG32_BIT(FIPNDL,                    0x10040064,__READ      ,__FIPNDL_bits);

/***************************************************************************
 **
 **  ROMPATCH
 **
 ***************************************************************************/
__IO_REG32(    ROMPATCHD15,               0x100410B4,__READ_WRITE);
__IO_REG32(    ROMPATCHD14,               0x100410B8,__READ_WRITE);
__IO_REG32(    ROMPATCHD13,               0x100410BC,__READ_WRITE);
__IO_REG32(    ROMPATCHD12,               0x100410C0,__READ_WRITE);
__IO_REG32(    ROMPATCHD11,               0x100410C4,__READ_WRITE);
__IO_REG32(    ROMPATCHD10,               0x100410C8,__READ_WRITE);
__IO_REG32(    ROMPATCHD9,                0x100410CC,__READ_WRITE);
__IO_REG32(    ROMPATCHD8,                0x100410D0,__READ_WRITE);
__IO_REG32(    ROMPATCHD7,                0x100410D4,__READ_WRITE);
__IO_REG32(    ROMPATCHD6,                0x100410D8,__READ_WRITE);
__IO_REG32(    ROMPATCHD5,                0x100410DC,__READ_WRITE);
__IO_REG32(    ROMPATCHD4,                0x100410E0,__READ_WRITE);
__IO_REG32(    ROMPATCHD3,                0x100410E4,__READ_WRITE);
__IO_REG32(    ROMPATCHD2,                0x100410E8,__READ_WRITE);
__IO_REG32(    ROMPATCHD1,                0x100410EC,__READ_WRITE);
__IO_REG32(    ROMPATCHD0,                0x100410F0,__READ_WRITE);
__IO_REG32_BIT(ROMPATCHCNTL,              0x100410F4,__READ_WRITE,__ROMPATCHCNTL_bits);
__IO_REG32_BIT(ROMPATCH,                  0x100410F8,__READ_WRITE,__ROMPATCH_bits);
__IO_REG32_BIT(ROMPATCL,                  0x100410FC,__READ_WRITE,__ROMPATCL_bits);
__IO_REG32_BIT(ROMPATCHA0,                0x10041100,__READ_WRITE,__ROMPATCHA0_3_bits);
__IO_REG32_BIT(ROMPATCHA1,                0x10041104,__READ_WRITE,__ROMPATCHA0_3_bits);
__IO_REG32_BIT(ROMPATCHA2,                0x10041108,__READ_WRITE,__ROMPATCHA0_3_bits);
__IO_REG32_BIT(ROMPATCHA3,                0x1004110C,__READ_WRITE,__ROMPATCHA0_3_bits);
__IO_REG32_BIT(ROMPATCHA4,                0x10041110,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA5,                0x10041114,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA6,                0x10041118,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA7,                0x1004111C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA8,                0x10041120,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA9,                0x10041124,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA10,               0x10041128,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA11,               0x1004112C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA12,               0x10041130,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA13,               0x10041134,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA14,               0x10041138,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA15,               0x1004113C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA16,               0x10041140,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA17,               0x10041144,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA18,               0x10041148,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA19,               0x1004114C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA20,               0x10041150,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA21,               0x10041154,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA22,               0x10041158,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA23,               0x1004115C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA24,               0x10041160,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA25,               0x10041164,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA26,               0x10041168,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA27,               0x1004116C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA28,               0x10041170,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA29,               0x10041174,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA30,               0x10041178,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA31,               0x1004117C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA32,               0x10041180,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA33,               0x10041184,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA34,               0x10041188,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA35,               0x1004118C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA36,               0x10041190,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA37,               0x10041194,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA38,               0x10041198,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA39,               0x1004119C,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA40,               0x100411A0,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA41,               0x100411A4,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA42,               0x100411A8,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA43,               0x100411AC,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA44,               0x100411B0,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA45,               0x100411B4,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA46,               0x100411B8,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA47,               0x100411BC,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA48,               0x100411C0,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA49,               0x100411C4,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA50,               0x100411C8,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA51,               0x100411CC,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA52,               0x100411D0,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA53,               0x100411D4,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA54,               0x100411D8,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA55,               0x100411DC,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA56,               0x100411E0,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA57,               0x100411E4,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA58,               0x100411E8,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA59,               0x100411EC,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA60,               0x100411F0,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA61,               0x100411F4,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA62,               0x100411F8,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHA63,               0x100411FC,__READ_WRITE,__ROMPATCHA_bits);
__IO_REG32_BIT(ROMPATCHBASEA,             0x10041204,__READ_WRITE,__ROMPATCHBASEA_bits);
__IO_REG32_BIT(ROMPATCHSR,                0x10041208,__READ      ,__ROMPATCHSR_bits);
__IO_REG32_BIT(ROMPATCHABSR,              0x1004120C,__READ_WRITE,__ROMPATCHABSR_bits);
__IO_REG32(    ROMPATCHDADR,              0x10041210,__READ      );

/***************************************************************************
 **
 **  PLLCLK
 **
 ***************************************************************************/
__IO_REG32_BIT(CSCR,                      0x10027000,__READ_WRITE,__CSCR_bits);
__IO_REG32_BIT(MPCTL0,                    0x10027004,__READ_WRITE,__MPCTL0_bits);
__IO_REG32_BIT(MPCTL1,                    0x10027008,__READ_WRITE,__MPCTL1_bits);
__IO_REG32_BIT(SPCTL0,                    0x1002700C,__READ_WRITE,__MPCTL0_bits);
__IO_REG32_BIT(SPCTL1,                    0x10027010,__READ_WRITE,__MPCTL1_bits);
__IO_REG32_BIT(OSC26MCTL,                 0x10027014,__READ_WRITE,__OSC26MCTL_bits);
__IO_REG32_BIT(PCDR0,                     0x10027018,__READ_WRITE,__PCDR0_bits);
__IO_REG32_BIT(PCDR1,                     0x1002701C,__READ_WRITE,__PCDR1_bits);
__IO_REG32_BIT(PCCR0,                     0x10027020,__READ_WRITE,__PCCR0_bits);
__IO_REG32_BIT(PCCR1,                     0x10027024,__READ_WRITE,__PCCR1_bits);
__IO_REG32_BIT(CCSR,                      0x10027028,__READ_WRITE,__CCSR_bits);
__IO_REG32_BIT(WKGDCTL,                   0x10027034,__READ_WRITE,__WKGDCTL_bits);

/***************************************************************************
 **
 **  AIPI1
 **
 ***************************************************************************/
__IO_REG32_BIT(AIPI1_PSR0,                0x10000000,__READ_WRITE,__AIPI1_bits);
__IO_REG32_BIT(AIPI1_PSR1,                0x10000004,__READ_WRITE,__AIPI1_bits);
__IO_REG32_BIT(AIPI1_PAR,                 0x10000008,__READ_WRITE,__AIPI1_bits);

/***************************************************************************
 **
 **  AIPI2
 **
 ***************************************************************************/
__IO_REG32_BIT(AIPI2_PSR0,                0x10020000,__READ_WRITE,__AIPI2_bits);
__IO_REG32_BIT(AIPI2_PSR1,                0x10020004,__READ_WRITE,__AIPI2_bits);
__IO_REG32_BIT(AIPI2_PAR,                 0x10020008,__READ_WRITE,__AIPI2_bits);

/***************************************************************************
 **
 **  SYS CTRL
 **
 ***************************************************************************/
__IO_REG32(    SUID0,                     0x10027804,__READ      );
__IO_REG32(    SUID1,                     0x10027808,__READ      );
__IO_REG32(    CID,                       0x1002780C,__READ      );
__IO_REG32_BIT(FUSE,                      0x10027810,__READ_WRITE,__FUSE_bits);
__IO_REG32_BIT(FMCR,                      0x10027814,__READ_WRITE,__FMCR_bits);
__IO_REG32_BIT(GPCR,                      0x10027818,__READ_WRITE,__GPCR_bits);
__IO_REG32_BIT(WBCR,                      0x1002781C,__READ_WRITE,__WBCR_bits);
__IO_REG32_BIT(DSCR1,                     0x10027820,__READ_WRITE,__DSCR1_bits);
__IO_REG32_BIT(DSCR2,                     0x10027824,__READ_WRITE,__DSCR2_bits);
__IO_REG32_BIT(DSCR3,                     0x10027828,__READ_WRITE,__DSCR3_bits);
__IO_REG32_BIT(DSCR4,                     0x1002782C,__READ_WRITE,__DSCR4_bits);
__IO_REG32_BIT(DSCR5,                     0x10027830,__READ_WRITE,__DSCR5_bits);
__IO_REG32_BIT(DSCR6,                     0x10027834,__READ_WRITE,__DSCR6_bits);
__IO_REG32_BIT(DSCR7,                     0x10027838,__READ_WRITE,__DSCR7_bits);
__IO_REG32_BIT(DSCR8,                     0x1002783C,__READ_WRITE,__DSCR8_bits);
__IO_REG32_BIT(DSCR9,                     0x10027840,__READ_WRITE,__DSCR9_bits);
__IO_REG32_BIT(DSCR10,                    0x10027844,__READ_WRITE,__DSCR10_bits);
__IO_REG32_BIT(DSCR11,                    0x10027848,__READ_WRITE,__DSCR11_bits);
__IO_REG32_BIT(DSCR12,                    0x1002784C,__READ_WRITE,__DSCR12_bits);
__IO_REG32_BIT(PCSR,                      0x10027850,__READ_WRITE,__PCSR_bits);

/***************************************************************************
 **
 **  Multi-layer AHB Crossbar Switch (MAX)
 **
 ***************************************************************************/
__IO_REG32_BIT(MPR0,                      0x1003F000,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(AMPR0,                     0x1003F004,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(SGPCR0,                    0x1003F010,__READ_WRITE,__SGPCR_bits);
__IO_REG32_BIT(ASGPCR0,                   0x1003F014,__READ_WRITE,__ASGPCR_bits);
__IO_REG32_BIT(MPR1,                      0x1003F100,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(AMPR1,                     0x1003F104,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(SGPCR1,                    0x1003F110,__READ_WRITE,__SGPCR_bits);
__IO_REG32_BIT(ASGPCR1,                   0x1003F114,__READ_WRITE,__ASGPCR_bits);
__IO_REG32_BIT(MPR2,                      0x1003F200,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(AMPR2,                     0x1003F204,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(SGPCR2,                    0x1003F210,__READ_WRITE,__SGPCR_bits);
__IO_REG32_BIT(ASGPCR2,                   0x1003F214,__READ_WRITE,__ASGPCR_bits);
__IO_REG32_BIT(MPR3,                      0x1003F300,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(AMPR3,                     0x1003F304,__READ_WRITE,__MPR_bits);
__IO_REG32_BIT(SGPCR3,                    0x1003F310,__READ_WRITE,__SGPCR_bits);
__IO_REG32_BIT(ASGPCR3,                   0x1003F314,__READ_WRITE,__ASGPCR_bits);
__IO_REG32_BIT(MGPCR0,                    0x1003F800,__READ_WRITE,__MGPCR_bits);
__IO_REG32_BIT(MGPCR1,                    0x1003F900,__READ_WRITE,__MGPCR_bits);
__IO_REG32_BIT(MGPCR2,                    0x1003FA00,__READ_WRITE,__MGPCR_bits);
__IO_REG32_BIT(MGPCR3,                    0x1003FB00,__READ_WRITE,__MGPCR_bits);
__IO_REG32_BIT(MGPCR4,                    0x1003FC00,__READ_WRITE,__MGPCR_bits);
__IO_REG32_BIT(MGPCR5,                    0x1003FD00,__READ_WRITE,__MGPCR_bits);

/***************************************************************************
 **
 **  Watchdog
 **
 ***************************************************************************/
__IO_REG16_BIT(WCR,                       0x10002000,__READ_WRITE,__WCR_bits);
__IO_REG16(    WSR,                       0x10002002,__READ_WRITE);
__IO_REG16_BIT(WRSR,                      0x10002004,__READ      ,__WRSR_bits);

/***************************************************************************
 **
 **  RTC
 **
 ***************************************************************************/
__IO_REG32_BIT(HOURMIN,                   0x10007000,__READ_WRITE,__HOURMIN_bits);
__IO_REG32_BIT(SECONDS,                   0x10007004,__READ_WRITE,__SECONDS_bits);
__IO_REG32_BIT(ALRM_HM,                   0x10007008,__READ_WRITE,__HOURMIN_bits);
__IO_REG32_BIT(ALRM_SEC,                  0x1000700C,__READ_WRITE,__SECONDS_bits);
__IO_REG32_BIT(RCCTL,                     0x10007010,__READ_WRITE,__RCCTL_bits);
__IO_REG32_BIT(RTCISR,                    0x10007014,__READ_WRITE,__RTCISR_bits);
__IO_REG32_BIT(RTCIENR,                   0x10007018,__READ_WRITE,__RTCISR_bits);
__IO_REG32_BIT(STPWCH,                    0x1000701C,__READ_WRITE,__STPWCH_bits);
__IO_REG32_BIT(DAYR,                      0x10007020,__READ_WRITE,__DAYR_bits);
__IO_REG32_BIT(DAYALARM,                  0x10007024,__READ_WRITE,__DAYALARM_bits);

/***************************************************************************
 **
 **  General-Purpose Timer1
 **
 ***************************************************************************/
__IO_REG32_BIT(TCTL1,                     0x10003000,__READ_WRITE,__TCTL_bits);
__IO_REG32_BIT(TPRER1,                    0x10003004,__READ_WRITE,__TPRER_bits);
__IO_REG32(    TCMP1,                     0x10003008,__READ_WRITE);
__IO_REG32(    TCR1,                      0x1000300C,__READ      );
__IO_REG32(    TCN1,                      0x10003010,__READ      );
__IO_REG32_BIT(TSTAT1,                    0x10003014,__READ_WRITE,__TSTAT_bits);


/***************************************************************************
 **
 **  General-Purpose Timer2
 **
 ***************************************************************************/
__IO_REG32_BIT(TCTL2,                     0x10004000,__READ_WRITE,__TCTL_bits);
__IO_REG32_BIT(TPRER2,                    0x10004004,__READ_WRITE,__TPRER_bits);
__IO_REG32(    TCMP2,                     0x10004008,__READ_WRITE);
__IO_REG32(    TCR2,                      0x1000400C,__READ      );
__IO_REG32(    TCN2,                      0x10004010,__READ      );
__IO_REG32_BIT(TSTAT2,                    0x10004014,__READ_WRITE,__TSTAT_bits);

/***************************************************************************
 **
 **  General-Purpose Timer3
 **
 ***************************************************************************/
__IO_REG32_BIT(TCTL3,                     0x10005000,__READ_WRITE,__TCTL_bits);
__IO_REG32_BIT(TPRER3,                    0x10005004,__READ_WRITE,__TPRER_bits);
__IO_REG32(    TCMP3,                     0x10005008,__READ_WRITE);
__IO_REG32(    TCR3,                      0x1000500C,__READ      );
__IO_REG32(    TCN3,                      0x10005010,__READ      );
__IO_REG32_BIT(TSTAT3,                    0x10005014,__READ_WRITE,__TSTAT_bits);

/***************************************************************************
 **
 **  PWM
 **
 ***************************************************************************/
__IO_REG32_BIT(PWMC,                      0x10006000,__READ_WRITE,__PWMC_bits);
__IO_REG32_BIT(PWMS,                      0x10006004,__READ_WRITE,__PWMS_bits);
__IO_REG32_BIT(PWMP,                      0x10006008,__READ_WRITE,__PWMP_bits);
__IO_REG32_BIT(PWMCNT,                    0x1000600C,__READ      ,__PWMCNT_bits);

/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG32_BIT(PMASK,                     0x10015600,__READ_WRITE,__PMASK_bits);

/***************************************************************************
 **
 **  GPIO PORTA
 **
 ***************************************************************************/
__IO_REG32_BIT(PTA_DDIR,                  0x10015000,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTA_OCR1,                  0x10015004,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTA_OCR2,                  0x10015008,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTA_ICONFA1,               0x1001500C,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTA_ICONFA2,               0x10015010,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTA_ICONFB1,               0x10015014,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTA_ICONFB2,               0x10015018,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTA_DR,                    0x1001501C,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTA_GIUS,                  0x10015020,__READ_WRITE,__PTA_GIUS_bits);
__IO_REG32_BIT(PTA_SSR,                   0x10015024,__READ      ,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTA_ICR1,                  0x10015028,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTA_ICR2,                  0x1001502C,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTA_IMR,                   0x10015030,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTA_ISR,                   0x10015034,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTA_GPR,                   0x10015038,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTA_SWR,                   0x1001503C,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PTA_PUEN,                  0x10015040,__READ_WRITE,__PORT_REG_31_0_bits);

/***************************************************************************
 **
 **  GPIO PORTB
 **
 ***************************************************************************/
__IO_REG32_BIT(PTB_DDIR,                  0x10015100,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTB_OCR1,                  0x10015104,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTB_OCR2,                  0x10015108,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTB_ICONFA1,               0x1001510C,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTB_ICONFA2,               0x10015110,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTB_ICONFB1,               0x10015114,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTB_ICONFB2,               0x10015118,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTB_DR,                    0x1001511C,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTB_GIUS,                  0x10015120,__READ_WRITE,__PTB_GIUS_bits);
__IO_REG32_BIT(PTB_SSR,                   0x10015124,__READ      ,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTB_ICR1,                  0x10015128,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTB_ICR2,                  0x1001512C,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTB_IMR,                   0x10015130,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTB_ISR,                   0x10015134,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTB_GPR,                   0x10015138,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTB_SWR,                   0x1001513C,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PTB_PUEN,                  0x10015140,__READ_WRITE,__PORT_REG_31_0_bits);

/***************************************************************************
 **
 **  GPIO PORTC
 **
 ***************************************************************************/
__IO_REG32_BIT(PTC_DDIR,                  0x10015200,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTC_OCR1,                  0x10015204,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTC_OCR2,                  0x10015208,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTC_ICONFA1,               0x1001520C,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTC_ICONFA2,               0x10015210,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTC_ICONFB1,               0x10015214,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTC_ICONFB2,               0x10015218,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTC_DR,                    0x1001521C,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTC_GIUS,                  0x10015220,__READ_WRITE,__PTC_GIUS_bits);
__IO_REG32_BIT(PTC_SSR,                   0x10015224,__READ      ,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTC_ICR1,                  0x10015228,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTC_ICR2,                  0x1001522C,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTC_IMR,                   0x10015230,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTC_ISR,                   0x10015234,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTC_GPR,                   0x10015238,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTC_SWR,                   0x1001523C,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PTC_PUEN,                  0x10015240,__READ_WRITE,__PORT_REG_31_0_bits);

/***************************************************************************
 **
 **  GPIO PORTD
 **
 ***************************************************************************/
__IO_REG32_BIT(PTD_DDIR,                  0x10015300,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTD_OCR1,                  0x10015304,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTD_OCR2,                  0x10015308,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTD_ICONFA1,               0x1001530C,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTD_ICONFA2,               0x10015310,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTD_ICONFB1,               0x10015314,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTD_ICONFB2,               0x10015318,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTD_DR,                    0x1001531C,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTD_GIUS,                  0x10015320,__READ_WRITE,__PTD_GIUS_bits);
__IO_REG32_BIT(PTD_SSR,                   0x10015324,__READ      ,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTD_ICR1,                  0x10015328,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTD_ICR2,                  0x1001532C,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTD_IMR,                   0x10015330,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTD_ISR,                   0x10015334,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTD_GPR,                   0x10015338,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTD_SWR,                   0x1001533C,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PTD_PUEN,                  0x10015340,__READ_WRITE,__PORT_REG_31_0_bits);

/***************************************************************************
 **
 **  GPIO PORTE
 **
 ***************************************************************************/
__IO_REG32_BIT(PTE_DDIR,                  0x10015400,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTE_OCR1,                  0x10015404,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTE_OCR2,                  0x10015408,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTE_ICONFA1,               0x1001540C,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTE_ICONFA2,               0x10015410,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTE_ICONFB1,               0x10015414,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTE_ICONFB2,               0x10015418,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTE_DR,                    0x1001541C,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTE_GIUS,                  0x10015420,__READ_WRITE,__PTE_GIUS_bits);
__IO_REG32_BIT(PTE_SSR,                   0x10015424,__READ      ,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTE_ICR1,                  0x10015428,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTE_ICR2,                  0x1001542C,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTE_IMR,                   0x10015430,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTE_ISR,                   0x10015434,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTE_GPR,                   0x10015438,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTE_SWR,                   0x1001543C,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PTE_PUEN,                  0x10015440,__READ_WRITE,__PORT_REG_31_0_bits);

/***************************************************************************
 **
 **  GPIO PORTF
 **
 ***************************************************************************/
__IO_REG32_BIT(PTF_DDIR,                  0x10015500,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTF_OCR1,                  0x10015504,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTF_OCR2,                  0x10015508,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTF_ICONFA1,               0x1001550C,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTF_ICONFA2,               0x10015510,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTF_ICONFB1,               0x10015514,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTF_ICONFB2,               0x10015518,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTF_DR,                    0x1001551C,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTF_GIUS,                  0x10015520,__READ_WRITE,__PTF_GIUS_bits);
__IO_REG32_BIT(PTF_SSR,                   0x10015524,__READ      ,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTF_ICR1,                  0x10015528,__READ_WRITE,__PORT_REG_15_0_bits);
__IO_REG32_BIT(PTF_ICR2,                  0x1001552C,__READ_WRITE,__PORT_REG_31_16_bits);
__IO_REG32_BIT(PTF_IMR,                   0x10015530,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTF_ISR,                   0x10015534,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTF_GPR,                   0x10015538,__READ_WRITE,__PORT_REG_31_0_bits);
__IO_REG32_BIT(PTF_SWR,                   0x1001553C,__READ_WRITE,__SWR_bits);
__IO_REG32_BIT(PTF_PUEN,                  0x10015540,__READ_WRITE,__PORT_REG_31_0_bits);

/***************************************************************************
 **
 **  Security Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(SCM_RED_START,             0x10043000,__READ_WRITE,__SCM_RED_START_bits);
__IO_REG32_BIT(SCM_BLACK_START,           0x10043004,__READ_WRITE,__SCM_BLACK_START_bits);
__IO_REG32_BIT(SCM_LENGTH,                0x10043008,__READ_WRITE,__SCM_LENGTH_bits);
__IO_REG32_BIT(SCM_CONTROL,               0x1004300C,__READ_WRITE,__SCM_CONTROL_bits);
__IO_REG32_BIT(SCM_STATUS,                0x10043010,__READ      ,__SCM_STATUS_bits);
__IO_REG32_BIT(SCM_ERROR,                 0x10043014,__READ      ,__SCM_ERROR_bits);
__IO_REG32_BIT(SCM_INT_CTRL,              0x10043018,__READ_WRITE,__SCM_INT_CTRL_bits);
__IO_REG32_BIT(SCM_CFG,                   0x1004301C,__READ      ,__SCM_CFG_bits);
__IO_REG32(    SCM_VEC0,                  0x10043020,__READ_WRITE);
__IO_REG32(    SCM_VEC1,                  0x10043024,__READ_WRITE);
__IO_REG32_BIT(SMN_STATUS,                0x10042000,__READ_WRITE,__SMN_STATUS_bits);
__IO_REG32_BIT(SMN_COMMAND,               0x10042004,__READ_WRITE,__SMN_COMMAND_bits);
__IO_REG32_BIT(SMN_SSR,                   0x10042008,__READ_WRITE,__SMN_SSR_bits);
__IO_REG32_BIT(SMN_SER,                   0x1004200C,__READ_WRITE,__SMN_SER_bits);
__IO_REG32_BIT(SMN_SCR,                   0x10042010,__READ_WRITE,__SMN_SCR_bits);
__IO_REG32_BIT(SMN_BCR,                   0x10042014,__READ_WRITE,__SMN_BCR_bits);
__IO_REG32_BIT(SMN_ISR,                   0x10042018,__READ_WRITE,__SMN_ISR_bits);
__IO_REG32_BIT(SMN_BBDR,                  0x1004201C,__WRITE     ,__SMN_BBDR_bits);
__IO_REG32_BIT(SMN_CSR,                   0x10042020,__READ_WRITE,__SMN_CSR_bits);
__IO_REG32(    SMN_PLAINTEXT,             0x10042024,__READ_WRITE);
__IO_REG32(    SMN_CIPHERTEXT,            0x10042028,__READ_WRITE);
__IO_REG32(    SMN_IVR,                   0x1004202C,__READ_WRITE);
__IO_REG32_BIT(SMN_TCR,                   0x10042030,__READ_WRITE,__SMN_TCR_bits);
__IO_REG32_BIT(SMN_DDR,                   0x10042034,__READ_WRITE,__SMN_DDR_bits);
__IO_REG32(    SMN_TR,                    0x10042038,__READ      );

/***************************************************************************
 **
 **  Run-Time Integrity Checker (RTIC)
 **
 ***************************************************************************/
__IO_REG32_BIT(RTICSR,                    0x1002A000,__READ      ,__RTICSR_bits);
__IO_REG32_BIT(RTICMD,                    0x1002A004,__READ      ,__RTICMD_bits);
__IO_REG32_BIT(RTICCNTLR,                 0x1002A008,__READ_WRITE,__RTICCNTLR_bits);
__IO_REG32_BIT(RTICTR,                    0x1002A00C,__READ_WRITE,__RTICTR_bits);
__IO_REG32(    RTICAMSAR1,                0x1002A010,__READ_WRITE);
__IO_REG32(    RTICAMLR1,                 0x1002A014,__READ_WRITE);
__IO_REG32(    RTICAMSAR2,                0x1002A018,__READ_WRITE);
__IO_REG32(    RTICAMLR2,                 0x1002A01C,__READ_WRITE);
__IO_REG32(    RTICBMSAR1,                0x1002A030,__READ_WRITE);
__IO_REG32(    RTICBMLR1,                 0x1002A034,__READ_WRITE);
__IO_REG32(    RTICBMSAR2,                0x1002A038,__READ_WRITE);
__IO_REG32(    RTICBMLR2,                 0x1002A03C,__READ_WRITE);
__IO_REG32(    RTICCMSAR1,                0x1002A050,__READ_WRITE);
__IO_REG32(    RTICCMLR1,                 0x1002A054,__READ_WRITE);
__IO_REG32(    RTICCMSAR2,                0x1002A058,__READ_WRITE);
__IO_REG32(    RTICCMLR2,                 0x1002A05C,__READ_WRITE);
__IO_REG32(    RTICDMSAR1,                0x1002A070,__READ_WRITE);
__IO_REG32(    RTICDMLR1,                 0x1002A074,__READ_WRITE);
__IO_REG32(    RTICDMSAR2,                0x1002A078,__READ_WRITE);
__IO_REG32(    RTICDMLR2,                 0x1002A07C,__READ_WRITE);
__IO_REG32(    RTICFAR,                   0x1002A090,__READ      );
__IO_REG32_BIT(RTICWR,                    0x1002A094,__READ_WRITE,__RTICWR_bits);
__IO_REG32(    RTICAMHR1,                 0x1002A0A0,__READ      );
__IO_REG32(    RTICAMHR2,                 0x1002A0A4,__READ      );
__IO_REG32(    RTICAMHR3,                 0x1002A0A8,__READ      );
__IO_REG32(    RTICAMHR4,                 0x1002A0AC,__READ      );
__IO_REG32(    RTICAMHR5,                 0x1002A0B0,__READ      );
__IO_REG32(    RTICBMHR1,                 0x1002A0C0,__READ      );
__IO_REG32(    RTICBMHR2,                 0x1002A0C4,__READ      );
__IO_REG32(    RTICBMHR3,                 0x1002A0C8,__READ      );
__IO_REG32(    RTICBMHR4,                 0x1002A0CC,__READ      );
__IO_REG32(    RTICBMHR5,                 0x1002A0D0,__READ      );
__IO_REG32(    RTICCMHR1,                 0x1002A0E0,__READ      );
__IO_REG32(    RTICCMHR2,                 0x1002A0E4,__READ      );
__IO_REG32(    RTICCMHR3,                 0x1002A0E8,__READ      );
__IO_REG32(    RTICCMHR4,                 0x1002A0EC,__READ      );
__IO_REG32(    RTICCMHR5,                 0x1002A0F0,__READ      );
__IO_REG32(    RTICDMHR1,                 0x1002A100,__READ      );
__IO_REG32(    RTICDMHR2,                 0x1002A104,__READ      );
__IO_REG32(    RTICDMHR3,                 0x1002A108,__READ      );
__IO_REG32(    RTICDMHR4,                 0x1002A10C,__READ      );
__IO_REG32(    RTICDMHR5,                 0x1002A110,__READ      );

/***************************************************************************
 **
 **  Random Number Generator Accelerator (RNGA)
 **
 ***************************************************************************/
__IO_REG32_BIT(RNGACR,                    0x10029000,__READ_WRITE,__RNGACR_bits);
__IO_REG32_BIT(RNGASR,                    0x10029004,__READ_WRITE,__RNGASR_bits);
__IO_REG32(    RNGAER,                    0x10029008,__READ_WRITE);
__IO_REG32(    RNGAFIFO,                  0x1002900C,__READ_WRITE);
__IO_REG32_BIT(RNGAMR,                    0x10029010,__READ_WRITE,__RNGAMR_bits);
__IO_REG32_BIT(RNGAVCR,                   0x10029014,__READ_WRITE,__RNGAVCR_bits);
__IO_REG32_BIT(RNGAOCCR,                  0x10029018,__READ_WRITE,__RNGAOCCR_bits);
__IO_REG32_BIT(RNGAO1CR,                  0x1002901C,__READ_WRITE,__RNGAOCR_bits);
__IO_REG32_BIT(RNGAO2CR,                  0x10029020,__READ_WRITE,__RNGAOCR_bits);
__IO_REG32_BIT(RNGAOCSR,                  0x10029024,__READ      ,__RNGAOCSR_bits);

/***************************************************************************
 **
 **  SDRAMC
 **
 ***************************************************************************/
__IO_REG32_BIT(SDCTL0,                    0xDF000000,__READ_WRITE,__SDCTL_bits);
__IO_REG32_BIT(SDCTL1,                    0xDF000004,__READ_WRITE,__SDCTL_bits);
__IO_REG32_BIT(MISCELLANEOUS,             0xDF000014,__READ_WRITE,__MISC_bits);
__IO_REG32_BIT(SDRST,                     0xDF000018,__READ_WRITE,__SDRST_bits);

/***************************************************************************
 **
 **  DMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DCR,                       0x10001000,__READ_WRITE,__DCR_bits);
__IO_REG32_BIT(DISR,                      0x10001004,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DIMR,                      0x10001008,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DBTOSR,                    0x1000100C,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DRTOSR,                    0x10001010,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DSESR,                     0x10001014,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DBOSR,                     0x10001018,__READ_WRITE,__DISR_bits);
__IO_REG32_BIT(DBTOCR,                    0x1000101C,__READ_WRITE,__DBTOCR_bits);
__IO_REG32_BIT(WSRA,                      0x10001040,__READ_WRITE,__WSR_bits);
__IO_REG32_BIT(XSRA,                      0x10001044,__READ_WRITE,__XSR_bits);
__IO_REG32_BIT(YSRA,                      0x10001048,__READ_WRITE,__YSR_bits);
__IO_REG32_BIT(WSRB,                      0x1000104C,__READ_WRITE,__WSR_bits);
__IO_REG32_BIT(XSRB,                      0x10001050,__READ_WRITE,__XSR_bits);
__IO_REG32_BIT(YSRB,                      0x10001054,__READ_WRITE,__YSR_bits);
__IO_REG32_BIT(SAR0,                      0x10001080,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR0,                      0x10001084,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR0,                     0x10001088,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR0,                      0x1000108C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR0,                     0x10001090,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR0,                      0x10001094,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR0,                     0x10001098,__READ_WRITE,__RTOR_bits);
#define BUCR0_bit     RTOR0_bit
#define BUCR0         RTOR0
__IO_REG32_BIT(CCNR0,                     0x1000109C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR1,                      0x100010C0,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR1,                      0x100010C4,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR1,                     0x100010C8,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR1,                      0x100010CC,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR1,                     0x100010D0,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR1,                      0x100010D4,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR1,                     0x100010D8,__READ_WRITE,__RTOR_bits);
#define BUCR1_bit     RTOR1_bit
#define BUCR1         RTOR1
__IO_REG32_BIT(CCNR1,                     0x100010DC,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR2,                      0x10001100,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR2,                      0x10001104,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR2,                     0x10001108,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR2,                      0x1000110C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR2,                     0x10001110,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR2,                      0x10001114,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR2,                     0x10001118,__READ_WRITE,__RTOR_bits);
#define BUCR2_bit     RTOR2_bit
#define BUCR2         RTOR2
__IO_REG32_BIT(CCNR2,                     0x1000111C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR3,                      0x10001140,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR3,                      0x10001144,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR3,                     0x10001148,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR3,                      0x1000114C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR3,                     0x10001150,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR3,                      0x10001154,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR3,                     0x10001158,__READ_WRITE,__RTOR_bits);
#define BUCR3_bit     RTOR3_bit
#define BUCR3         RTOR3
__IO_REG32_BIT(CCNR3,                     0x1000115C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR4,                      0x10001180,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR4,                      0x10001184,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR4,                     0x10001188,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR4,                      0x1000118C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR4,                     0x10001190,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR4,                      0x10001194,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR4,                     0x10001198,__READ_WRITE,__RTOR_bits);
#define BUCR4_bit     RTOR4_bit
#define BUCR4         RTOR4
__IO_REG32_BIT(CCNR4,                     0x1000119C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR5,                      0x100011C0,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR5,                      0x100011C4,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR5,                     0x100011C8,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR5,                      0x100011CC,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR5,                     0x100011D0,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR5,                      0x100011D4,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR5,                     0x100011D8,__READ_WRITE,__RTOR_bits);
#define BUCR5_bit     RTOR5_bit
#define BUCR5         RTOR5
__IO_REG32_BIT(CCNR5,                     0x100011DC,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR6,                      0x10001200,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR6,                      0x10001204,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR6,                     0x10001208,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR6,                      0x1000120C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR6,                     0x10001210,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR6,                      0x10001214,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR6,                     0x10001218,__READ_WRITE,__RTOR_bits);
#define BUCR6_bit     RTOR6_bit
#define BUCR6         RTOR6
__IO_REG32_BIT(CCNR6,                     0x1000121C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR7,                      0x10001240,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR7,                      0x10001244,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR7,                     0x10001248,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR7,                      0x1000124C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR7,                     0x10001250,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR7,                      0x10001254,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR7,                     0x10001258,__READ_WRITE,__RTOR_bits);
#define BUCR7_bit     RTOR7_bit
#define BUCR7         RTOR7
__IO_REG32_BIT(CCNR7,                     0x1000125C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR8,                      0x10001280,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR8,                      0x10001284,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR8,                     0x10001288,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR8,                      0x1000128C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR8,                     0x10001290,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR8,                      0x10001294,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR8,                     0x10001298,__READ_WRITE,__RTOR_bits);
#define BUCR8_bit     RTOR8_bit
#define BUCR8         RTOR8
__IO_REG32_BIT(CCNR8,                     0x1000129C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR9,                      0x100012C0,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR9,                      0x100012C4,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR9,                     0x100012C8,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR9,                      0x100012CC,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR9,                     0x100012D0,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR9,                      0x100012D4,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR9,                     0x100012D8,__READ_WRITE,__RTOR_bits);
#define BUCR9_bit     RTOR9_bit
#define BUCR9         RTOR9
__IO_REG32_BIT(CCNR9,                     0x100012DC,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR10,                     0x10001300,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR10,                     0x10001304,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR10,                    0x10001308,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR10,                     0x1000130C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR10,                    0x10001310,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR10,                     0x10001314,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR10,                    0x10001318,__READ_WRITE,__RTOR_bits);
#define BUCR10_bit    RTOR10_bit
#define BUCR10        RTOR10
__IO_REG32_BIT(CCNR10,                    0x1000131C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR11,                     0x10001340,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR11,                     0x10001344,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR11,                    0x10001348,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR11,                     0x1000134C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR11,                    0x10001350,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR11,                     0x10001354,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR11,                    0x10001358,__READ_WRITE,__RTOR_bits);
#define BUCR11_bit    RTOR11_bit
#define BUCR11        RTOR11
__IO_REG32_BIT(CCNR11,                    0x1000135C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR12,                     0x10001380,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR12,                     0x10001384,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR12,                    0x10001388,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR12,                     0x1000138C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR12,                    0x10001390,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR12,                     0x10001394,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR12,                    0x10001398,__READ_WRITE,__RTOR_bits);
#define BUCR12_bit    RTOR12_bit
#define BUCR12        RTOR12
__IO_REG32_BIT(CCNR12,                    0x1000139C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR13,                     0x100013C0,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR13,                     0x100013C4,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR13,                    0x100013C8,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR13,                     0x100013CC,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR13,                    0x100013D0,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR13,                     0x100013D4,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR13,                    0x100013D8,__READ_WRITE,__RTOR_bits);
#define BUCR13_bit    RTOR13_bit
#define BUCR13        RTOR13
__IO_REG32_BIT(CCNR13,                    0x100013DC,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR14,                     0x10001400,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR14,                     0x10001404,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR14,                    0x10001408,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR14,                     0x1000140C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR14,                    0x10001410,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR14,                     0x10001414,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR14,                    0x10001418,__READ_WRITE,__RTOR_bits);
#define BUCR14_bit    RTOR14_bit
#define BUCR14        RTOR14
__IO_REG32_BIT(CCNR14,                    0x1000141C,__READ      ,__CCNR_bits);
__IO_REG32_BIT(SAR15,                     0x10001440,__READ_WRITE,__SAR_bits);
__IO_REG32_BIT(DAR15,                     0x10001444,__READ_WRITE,__DAR_bits);
__IO_REG32_BIT(CNTR15,                    0x10001448,__READ_WRITE,__CNTR_bits);
__IO_REG32_BIT(CCR15,                     0x1000144C,__READ_WRITE,__CCR_bits);
__IO_REG32_BIT(RSSR15,                    0x10001450,__READ_WRITE,__RSSR_bits);
__IO_REG32_BIT(BLR15,                     0x10001454,__READ_WRITE,__BLR_bits);
__IO_REG32_BIT(RTOR15,                    0x10001458,__READ_WRITE,__RTOR_bits);
#define BUCR15_bit    RTOR15_bit
#define BUCR15        RTOR15
__IO_REG32_BIT(CCNR15,                    0x1000145C,__READ      ,__CCNR_bits);

/***************************************************************************
 **
 **  NAND Flash Memory Controller (NANDFC)
 **
 ***************************************************************************/
__IO_REG16_BIT(NFC_BUFSIZE,               0xDF003E00,__READ      ,__NFC_BUFSIZE_bits);
__IO_REG16(    NFC_BAL,                   0xDF003E02,__READ      );
__IO_REG16_BIT(NFC_RBA,                   0xDF003E04,__READ_WRITE,__NFC_RBA_bits);
__IO_REG16(    NAND_FLASH_ADD,            0xDF003E06,__READ_WRITE);
__IO_REG16(    NAND_FLASH_CMD,            0xDF003E08,__READ_WRITE);
__IO_REG16_BIT(NFC_IBLC,                  0xDF003E0A,__READ_WRITE,__NFC_IBLC_bits);
__IO_REG16_BIT(ECC_SRR,                   0xDF003E0C,__READ      ,__ECC_SRR_bits);
__IO_REG16_BIT(ECC_RSLT_MA,               0xDF003E0E,__READ      ,__ECC_RSLT_MA_bits);
__IO_REG16_BIT(ECC_RSLT_SA,               0xDF003E10,__READ      ,__ECC_RSLT_SA_bits);
__IO_REG16_BIT(NF_WR_PROT,                0xDF003E12,__READ_WRITE,__NF_WR_PROT_bits);
__IO_REG16(    NFC_USBA,                  0xDF003E14,__READ_WRITE);
__IO_REG16(    NFC_UEBA,                  0xDF003E16,__READ_WRITE);
__IO_REG16_BIT(NF_WR_PROT_STA,            0xDF003E18,__READ      ,__NF_WR_PROT_STA_bits);
__IO_REG16_BIT(NAND_FC1,                  0xDF003E1A,__READ_WRITE,__NAND_FC1_bits);
__IO_REG16_BIT(NAND_FC2,                  0xDF003E1C,__READ_WRITE,__NAND_FC2_bits);

/***************************************************************************
 **
 **  EIM
 **
 ***************************************************************************/
__IO_REG32_BIT(CS0U,                      0xDF001000,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS0L,                      0xDF001004,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS1U,                      0xDF001008,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS1L,                      0xDF00100C,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS2U,                      0xDF001010,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS2L,                      0xDF001014,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS3U,                      0xDF001018,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS3L,                      0xDF00101C,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS4U,                      0xDF001020,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS4L,                      0xDF001024,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(CS5U,                      0xDF001028,__READ_WRITE,__CSU_bits);
__IO_REG32_BIT(CS5L,                      0xDF00102C,__READ_WRITE,__CSL_bits);
__IO_REG32_BIT(EIM,                       0xDF001030,__READ_WRITE,__EIM_bits);

/***************************************************************************
 **
 **  Bus Master Interface (BMI)
 **
 ***************************************************************************/
__IO_REG32_BIT(BMICTLR1,                  0xA0000000,__READ_WRITE,__BMICTLR1_bits);
__IO_REG32_BIT(BMICTLR2,                  0xA0000004,__READ_WRITE,__BMICTLR2_bits);
__IO_REG32_BIT(BMISTR,                    0xA0000008,__READ      ,__BMISR_bits);
__IO_REG32(    BMIRXD,                    0xA000000C,__READ      );
__IO_REG32(    BMITXD,                    0xA0000010,__WRITE     );

/***************************************************************************
 **
 **  I2C
 **
 ***************************************************************************/
__IO_REG32_BIT(IADR,                      0x10012000,__READ_WRITE,__IADR_bits);
__IO_REG32_BIT(IFDR,                      0x10012004,__READ_WRITE,__IFDR_bits);
__IO_REG32_BIT(I2CR,                      0x10012008,__READ_WRITE,__I2CR_bits);
__IO_REG32_BIT(I2SR,                      0x1001200C,__READ_WRITE,__I2SR_bits);
__IO_REG32_BIT(I2DR,                      0x10012010,__READ_WRITE,__I2DR_bits);

/***************************************************************************
 **
 **  SPI1
 **
 ***************************************************************************/
__IO_REG32(    RXDATAREG1,                0x1000E000,__READ      );
__IO_REG32(    TXDATAREG1,                0x1000E004,__WRITE     );
__IO_REG32_BIT(CONTROLREG1,               0x1000E008,__READ_WRITE,__CONTROLREG_bits);
__IO_REG32_BIT(INTREG1,                   0x1000E00C,__READ_WRITE,__INTREG_bits);
__IO_REG32_BIT(TESTREG1,                  0x1000E010,__READ_WRITE,__TESTREG_bits);
__IO_REG32_BIT(PERIODREG1,                0x1000E014,__READ_WRITE,__PERIODREG_bits);
__IO_REG32_BIT(DMAREG1,                   0x1000E018,__READ_WRITE,__DMAREG_bits);
__IO_REG32_BIT(RESETREG1,                 0x1000E01C,__READ_WRITE,__RESETREG_bits);

/***************************************************************************
 **
 **  SPI2
 **
 ***************************************************************************/
__IO_REG32(    RXDATAREG2,                0x1000F000,__READ      );
__IO_REG32(    TXDATAREG2,                0x1000F004,__WRITE     );
__IO_REG32_BIT(CONTROLREG2,               0x1000F008,__READ_WRITE,__CONTROLREG_bits);
__IO_REG32_BIT(INTREG2,                   0x1000F00C,__READ_WRITE,__INTREG_bits);
__IO_REG32_BIT(TESTREG2,                  0x1000F010,__READ_WRITE,__TESTREG_bits);
__IO_REG32_BIT(PERIODREG2,                0x1000F014,__READ_WRITE,__PERIODREG_bits);
__IO_REG32_BIT(DMAREG2,                   0x1000F018,__READ_WRITE,__DMAREG_bits);
__IO_REG32_BIT(RESETREG2,                 0x1000F01C,__READ_WRITE,__RESETREG_bits);

/***************************************************************************
 **
 **  SPI3
 **
 ***************************************************************************/
__IO_REG32(    RXDATAREG3,                0x10017000,__READ      );
__IO_REG32(    TXDATAREG3,                0x10017004,__WRITE     );
__IO_REG32_BIT(CONTROLREG3,               0x10017008,__READ_WRITE,__CONTROLREG_bits);
__IO_REG32_BIT(INTREG3,                   0x1001700C,__READ_WRITE,__INTREG_bits);
__IO_REG32_BIT(TESTREG3,                  0x10017010,__READ_WRITE,__TESTREG_bits);
__IO_REG32_BIT(PERIODREG3,                0x10017014,__READ_WRITE,__PERIODREG_bits);
__IO_REG32_BIT(DMAREG3,                   0x10017018,__READ_WRITE,__DMAREG_bits);
__IO_REG32_BIT(RESETREG3,                 0x1001701C,__READ_WRITE,__RESETREG_bits);

/***************************************************************************
 **
 **  SSI1
 **
 ***************************************************************************/
__IO_REG32_BIT(SSI1_STX0,                 0x10010000,__READ_WRITE,__SSI_DATA_bits);
__IO_REG32_BIT(SSI1_STX1,                 0x10010004,__READ_WRITE,__SSI_DATA_bits);
__IO_REG32_BIT(SSI1_SRX0,                 0x10010008,__READ      ,__SSI_DATA_bits);
__IO_REG32_BIT(SSI1_SRX1,                 0x1001000C,__READ      ,__SSI_DATA_bits);
__IO_REG32_BIT(SSI1_SCR,                  0x10010010,__READ_WRITE,__SCSR_bits);
__IO_REG32_BIT(SSI1_SISR,                 0x10010014,__READ      ,__SISR_bits);
__IO_REG32_BIT(SSI1_SIER,                 0x10010018,__READ_WRITE,__SIER_bits);
__IO_REG32_BIT(SSI1_STCR,                 0x1001001C,__READ_WRITE,__STCR_bits);
__IO_REG32_BIT(SSI1_SRCR,                 0x10010020,__READ_WRITE,__SRCR_bits);
__IO_REG32_BIT(SSI1_STCCR,                0x10010024,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(SSI1_SRCCR,                0x10010028,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(SSI1_SFCSR,                0x1001002C,__READ_WRITE,__SSI_SFCSR_bits);
__IO_REG32_BIT(SSI1_STR,                  0x10010030,__READ_WRITE,__SSI_STR_bits);
__IO_REG32_BIT(SSI1_SOR,                  0x10010034,__READ_WRITE,__SSI_SOR_bits);
__IO_REG32_BIT(SSI1_SACNT,                0x10010038,__READ_WRITE,__SSI_SACNT_bits);
__IO_REG32_BIT(SSI1_SACADD,               0x1001003C,__READ_WRITE,__SSI_SACADD_bits);
__IO_REG32_BIT(SSI1_SACDAT,               0x10010040,__READ_WRITE,__SSI_SACDAT_bits);
__IO_REG32_BIT(SSI1_SATAG,                0x10010044,__READ_WRITE,__SSI_SATAG_bits);
__IO_REG32(    SSI1_STMSK,                0x10010048,__READ_WRITE);
__IO_REG32(    SSI1_SRMSK,                0x1001004C,__READ_WRITE);

/***************************************************************************
 **
 **  SSI2
 **
 ***************************************************************************/
__IO_REG32_BIT(SSI2_STX0,                 0x10011000,__READ_WRITE,__SSI_DATA_bits);
__IO_REG32_BIT(SSI2_STX1,                 0x10011004,__READ_WRITE,__SSI_DATA_bits);
__IO_REG32_BIT(SSI2_SRX0,                 0x10011008,__READ      ,__SSI_DATA_bits);
__IO_REG32_BIT(SSI2_SRX1,                 0x1001100C,__READ      ,__SSI_DATA_bits);
__IO_REG32_BIT(SSI2_SCR,                  0x10011010,__READ_WRITE,__SCSR_bits);
__IO_REG32_BIT(SSI2_SISR,                 0x10011014,__READ      ,__SISR_bits);
__IO_REG32_BIT(SSI2_SIER,                 0x10011018,__READ_WRITE,__SIER_bits);
__IO_REG32_BIT(SSI2_STCR,                 0x1001101C,__READ_WRITE,__STCR_bits);
__IO_REG32_BIT(SSI2_SRCR,                 0x10011020,__READ_WRITE,__SRCR_bits);
__IO_REG32_BIT(SSI2_STCCR,                0x10011024,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(SSI2_SRCCR,                0x10011028,__READ_WRITE,__SSI_CCR_bits);
__IO_REG32_BIT(SSI2_SFCSR,                0x1001102C,__READ_WRITE,__SSI_SFCSR_bits);
__IO_REG32_BIT(SSI2_STR,                  0x10011030,__READ_WRITE,__SSI_STR_bits);
__IO_REG32_BIT(SSI2_SOR,                  0x10011034,__READ_WRITE,__SSI_SOR_bits);
__IO_REG32_BIT(SSI2_SACNT,                0x10011038,__READ_WRITE,__SSI_SACNT_bits);
__IO_REG32_BIT(SSI2_SACADD,               0x1001103C,__READ_WRITE,__SSI_SACADD_bits);
__IO_REG32_BIT(SSI2_SACDAT,               0x10011040,__READ_WRITE,__SSI_SACDAT_bits);
__IO_REG32_BIT(SSI2_SATAG,                0x10011044,__READ_WRITE,__SSI_SATAG_bits);
__IO_REG32(    SSI2_STMSK,                0x10011048,__READ_WRITE);
__IO_REG32(    SSI2_SRMSK,                0x1001104C,__READ_WRITE);

/***************************************************************************
 **
 **  CSI
 **
 ***************************************************************************/
__IO_REG32_BIT(CSICR1,                    0x80000000,__READ_WRITE,__CSICR1_bits);
__IO_REG32_BIT(CSICR2,                    0x80000004,__READ_WRITE,__CSICR2_bits);
__IO_REG32_BIT(CSISR,                     0x80000008,__READ_WRITE,__CSISR_bits);
__IO_REG32(    CSISTATFIFO,               0x8000000C,__READ      );
__IO_REG32(    CSIRFIFO,                  0x80000010,__READ      );
__IO_REG32_BIT(CSIRXCNT,                  0x80000014,__READ_WRITE,__CSIRXCNT_bits);
__IO_REG32_BIT(CSICR3,                    0x8000001C,__READ_WRITE,__CSICR3_bits);

/***************************************************************************
 **
 **  LCDC
 **
 ***************************************************************************/
__IO_REG32_BIT(LSSAR,                     0x10021000,__READ_WRITE,__SSA_bits);
__IO_REG32_BIT(_LSR,                      0x10021004,__READ_WRITE,__LSR_bits);
__IO_REG32_BIT(LVPWR,                     0x10021008,__READ_WRITE,__LVPWR_bits);
__IO_REG32_BIT(LCPR,                      0x1002100C,__READ_WRITE,__LCPR_bits);
__IO_REG32_BIT(LCWHB,                     0x10021010,__READ_WRITE,__LCWHB_bits);
__IO_REG32_BIT(LCCMR,                     0x10021014,__READ_WRITE,__LCCMR_bits);
__IO_REG32_BIT(LPCR,                      0x10021018,__READ_WRITE,__LPCR_bits);
__IO_REG32_BIT(LHCR,                      0x1002101C,__READ_WRITE,__LHCR_bits);
__IO_REG32_BIT(LVCR,                      0x10021020,__READ_WRITE,__LVCR_bits);
__IO_REG32_BIT(LPOR,                      0x10021024,__READ_WRITE,__LPOR_bits);
__IO_REG32_BIT(LSCR,                      0x10021028,__READ_WRITE,__LSCR_bits);
__IO_REG32_BIT(LPCCR,                     0x1002102C,__READ_WRITE,__LPCCR_bits);
__IO_REG32_BIT(LDCR,                      0x10021030,__READ_WRITE,__LDCR_bits);
__IO_REG32_BIT(LRMCR,                     0x10021034,__READ_WRITE,__LRMCR_bits);
__IO_REG32_BIT(LICR,                      0x10021038,__READ_WRITE,__LICR_bits);
__IO_REG32_BIT(LIER,                      0x1002103C,__READ_WRITE,__LIER_bits);
__IO_REG32_BIT(LISR,                      0x10021040,__READ      ,__LISR_bits);
__IO_REG32_BIT(LGWSAR,                    0x10021050,__READ_WRITE,__LGWSAR_bits);
__IO_REG32_BIT(LGWSR,                     0x10021054,__READ_WRITE,__LGWSR_bits);
__IO_REG32_BIT(LGWVPWR,                   0x10021058,__READ_WRITE,__LGWVPWR_bits);
__IO_REG32_BIT(LGWPOR,                    0x1002105C,__READ_WRITE,__LGWPOR_bits);
__IO_REG32_BIT(LGWPR,                     0x10021060,__READ_WRITE,__LGWPR_bits);
__IO_REG32_BIT(LGWCR,                     0x10021064,__READ_WRITE,__LGWCR_bits);
__IO_REG32_BIT(LGWDCR,                    0x10021068,__READ_WRITE,__LGWDCR_bits);

/***************************************************************************
 **
 **  Smart Liquid Crystal Display Controller (SLCDC)
 **
 ***************************************************************************/
__IO_REG32_BIT(DATA_BASE_ADDR,            0x10022000,__READ_WRITE,__DATA_BASE_ADDR_bits);
__IO_REG32_BIT(ATA_BUFF_SIZE,             0x10022004,__READ_WRITE,__DATA_BUFF_SIZE_bits);
__IO_REG32_BIT(CMD_BASE_ADDR,             0x10022008,__READ_WRITE,__CMD_BASE_ADDR_bits);
__IO_REG32_BIT(CMD_BUFF_SIZE,             0x1002200C,__READ_WRITE,__CMD_BUFF_SIZE_bits);
__IO_REG32_BIT(STRING_SIZE,               0x10022010,__READ_WRITE,__STRING_SIZE_bits);
__IO_REG32_BIT(FIFO_CONFIG,               0x10022014,__READ_WRITE,__FIFO_CONFIG_bits);
__IO_REG32_BIT(LCD_CONFIG,                0x10022018,__READ_WRITE,__LCD_CONFIG_bits);
__IO_REG32_BIT(LCDTRANSCONFIG,            0x1002201C,__READ_WRITE,__LCDTRANSCONFIG_bits);
__IO_REG32_BIT(DMA_CTRL_STAT,             0x10022020,__READ_WRITE,__DMA_CTRL_STAT_bits);
__IO_REG32_BIT(LCD_CLK_CONFIG,            0x10022024,__READ_WRITE,__LCD_CLK_CONFIG_bits);
__IO_REG32_BIT(LCD_WRITE_DATA,            0x10022028,__READ_WRITE,__LCD_WRITE_DATA_bits);

/***************************************************************************
 **
 **  enhanced Multimedia Accelerator (eMMA)
 **
 ***************************************************************************/
__IO_REG32_BIT(PP_CNTL,                   0x10026000,__READ_WRITE,__PP_CNTL_bits);
__IO_REG32_BIT(PP_INTRCNTL,               0x10026004,__READ_WRITE,__PP_INTRCNTL_bits);
__IO_REG32_BIT(PP_INTRSTATUS,             0x10026008,__READ_WRITE,__PP_INTRSTATUS_bits);
__IO_REG32(    PP_SOURCE_Y_PTR,           0x1002600C,__READ_WRITE);
__IO_REG32(    PP_SOURCE_CB_PTR,          0x10026010,__READ_WRITE);
__IO_REG32(    PP_SOURCE_CR_PTR,          0x10026014,__READ_WRITE);
__IO_REG32(    PP_DEST_RGB_PTR,           0x10026018,__READ_WRITE);
__IO_REG32(    PP_QUANTIZER_PTR,          0x1002601C,__READ_WRITE);
__IO_REG32_BIT(PPP_PROCESS_PARA,          0x10026020,__READ_WRITE,__PP_PROCESS_PARA_bits);
__IO_REG32_BIT(PP_FRAME_WIDTH,            0x10026024,__READ_WRITE,__PP_FRAME_WIDTH_bits);
__IO_REG32_BIT(PP_DISPLAY_WIDTH,          0x10026028,__READ_WRITE,__PP_DISPLAY_WIDTH_bits);
__IO_REG32_BIT(PP_IMAGE_SIZE,             0x1002602C,__READ_WRITE,__PP_IMAGE_SIZE_bits);
__IO_REG32_BIT(PP_DEST_FRAME_FMT_CNTL,    0x10026030,__READ_WRITE,__PP_DEST_FRAME_FORMAT_CNTL_bits);
__IO_REG32_BIT(PP_RESIZE_INDEX,           0x10026034,__READ_WRITE,__PP_RESIZE_INDEX_bits);
__IO_REG32_BIT(PP_CSC_COEF_123,           0x10026038,__READ_WRITE,__PP_CSC_COEF_123_bits);
__IO_REG32_BIT(PP_CSC_COEF_4,             0x1002603C,__READ_WRITE,__PP_CSC_COEF_4_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL0,       0x10026100,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL1,       0x10026104,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL2,       0x10026108,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL3,       0x1002610C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL4,       0x10026110,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL5,       0x10026114,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL6,       0x10026118,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL7,       0x1002611C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL8,       0x10026120,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL9,       0x10026124,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL10,      0x10026128,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL11,      0x1002612C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL12,      0x10026130,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL13,      0x10026134,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL14,      0x10026138,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL15,      0x1002613C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL16,      0x10026140,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL17,      0x10026144,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL18,      0x10026148,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL19,      0x1002614C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL20,      0x10026150,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL21,      0x10026154,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL22,      0x10026158,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL23,      0x1002615C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL24,      0x10026160,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL25,      0x10026164,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL26,      0x10026168,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL27,      0x1002616C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL28,      0x10026170,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL29,      0x10026174,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL30,      0x10026178,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PP_RESIZE_COEF_TBL31,      0x1002617C,__WRITE     ,__PP_RESIZE_COEF_TBL_bits);
__IO_REG32_BIT(PRP_CNTL,                  0x10026400,__READ_WRITE,__PRP_CNTL_bits);
__IO_REG32_BIT(PRP_INTR_CNTL,             0x10026404,__READ_WRITE,__PRP_INTR_CNTL_bits);
__IO_REG32_BIT(PRP_INTRSTATUS,            0x10026408,__READ_WRITE,__PRP_INTRSTATUS_bits);
__IO_REG32(    PRP_SOURCE_Y_PTR,          0x1002640C,__READ_WRITE);
__IO_REG32(    PRP_SOURCE_CB_PTR,         0x10026410,__READ_WRITE);
__IO_REG32(    PRP_SOURCE_CR_PTR,         0x10026414,__READ_WRITE);
__IO_REG32(    PRP_DEST_RGB1_PTR,         0x10026418,__READ_WRITE);
__IO_REG32(    PRP_DEST_RGB2_PTR,         0x1002641C,__READ_WRITE);
__IO_REG32(    PRP_DEST_Y_PTR,            0x10026420,__READ_WRITE);
__IO_REG32(    PRP_DEST_CB_PTR,           0x10026424,__READ_WRITE);
__IO_REG32(    PRP_DEST_CR_PTR,           0x10026428,__READ_WRITE);
__IO_REG32_BIT(PRP_SRC_FRAME_SIZE,        0x1002642C,__READ_WRITE,__PRP_SRC_FRAME_SIZE_bits);
__IO_REG32_BIT(PRP_DEST_CH1_LINE_STRIDE,  0x10026430,__READ_WRITE,__PRP_DEST_CH1_LINE_STRIDE_bits);
__IO_REG32_BIT(PRP_SRC_PIXEL_FORMAT_CNTL, 0x10026434,__READ_WRITE,__PRP_SRC_PIXEL_FORMAT_CNTL_bits);
__IO_REG32_BIT(PRP_CH1_PIXEL_FORMAT_CNTL, 0x10026438,__READ_WRITE,__PRP_CH1_PIXEL_FORMAT_CNTL_bits);
__IO_REG32_BIT(PRP_CH1_OUT_IMAGE_SIZE,    0x1002643C,__READ_WRITE,__PRP_CH1_OUT_IMAGE_SIZE_bits);
__IO_REG32_BIT(PRP_CH2_OUT_IMAGE_SIZE,    0x10026440,__READ_WRITE,__PRP_CH2_OUT_IMAGE_SIZE_bits);
__IO_REG32_BIT(PRP_SRC_LINE_STRIDE,       0x10026444,__READ_WRITE,__PRP_SRC_LINE_STRIDE_bits);
__IO_REG32_BIT(PRP_CSC_COEF_012,          0x10026448,__READ_WRITE,__PRP_CSC_COEF_012_bits);
__IO_REG32_BIT(PRP_CSC_COEF_345,          0x1002644C,__READ_WRITE,__PRP_CSC_COEF_345_bits);
__IO_REG32_BIT(PRP_CSC_COEF_678,          0x10026450,__READ_WRITE,__PRP_CSC_COEF_678_bits);
__IO_REG32_BIT(PRP_CH1_RZ_HORI_COEF1,     0x10026454,__READ_WRITE,__PRP_RZ_HORI_COEF1_bits);
__IO_REG32_BIT(PRP_CH1_RZ_HORI_COEF2,     0x10026458,__READ_WRITE,__PRP_RZ_HORI_COEF2_bits);
__IO_REG32_BIT(PRP_CH1_RZ_HORI_VALID,     0x1002645C,__READ_WRITE,__PRP_RZ_HORI_VALID_bits);
__IO_REG32_BIT(PRP_CH1_RZ_VERT_COEF1,     0x10026460,__READ_WRITE,__PRP_RZ_VERT_COEF1_bits);
__IO_REG32_BIT(PRP_CH1_RZ_VERT_COEF2,     0x10026464,__READ_WRITE,__PRP_RZ_VERT_COEF2_bits);
__IO_REG32_BIT(PRP_CH1_RZ_VERT_VALID,     0x10026468,__READ_WRITE,__PRP_RZ_VERT_VALID_bits);
__IO_REG32_BIT(PRP_CH2_RZ_HORI_COEF1,     0x1002646C,__READ_WRITE,__PRP_RZ_HORI_COEF1_bits);
__IO_REG32_BIT(PRP_CH2_RZ_HORI_COEF2,     0x10026470,__READ_WRITE,__PRP_RZ_HORI_COEF2_bits);
__IO_REG32_BIT(PRP_CH2_RZ_HORI_VALID,     0x10026474,__READ_WRITE,__PRP_RZ_HORI_VALID_bits);
__IO_REG32_BIT(PRP_CH2_RZ_VERT_COEF1,     0x10026478,__READ_WRITE,__PRP_RZ_VERT_COEF1_bits);
__IO_REG32_BIT(PRP_CH2_RZ_VERT_COEF2,     0x1002647C,__READ_WRITE,__PRP_RZ_VERT_COEF2_bits);
__IO_REG32_BIT(PRP_CH2_RZ_VERT_VALID,     0x10026480,__READ_WRITE,__PRP_RZ_VERT_VALID_bits);

 /***************************************************************************
 **
 **  MMC/SDHC1
 **
 ***************************************************************************/
__IO_REG32_BIT(SDHC1_STR_STP_CLK,         0x10013000,__READ_WRITE,__STR_STP_CLK_bits);
__IO_REG32_BIT(SDHC1_STATUS,              0x10013004,__READ      ,__SD_STATUS_bits);
__IO_REG32_BIT(SDHC1_CLK_RATE,            0x10013008,__READ_WRITE,__CLK_RATE_bits);
__IO_REG32_BIT(SDHC1_CMD_DAT_CONT,        0x1001300C,__READ_WRITE,__CMD_DAT_CONT_bits);
__IO_REG32_BIT(SDHC1_RES_TO,              0x10013010,__READ_WRITE,__RES_TO_bits);
__IO_REG32_BIT(SDHC1_READ_TO,             0x10013014,__READ_WRITE,__READ_TO_bits);
__IO_REG32_BIT(SDHC1_BLK_LEN,             0x10013018,__READ_WRITE,__BLK_LEN_bits);
__IO_REG32_BIT(SDHC1_NOB,                 0x1001301C,__READ_WRITE,__NOB_bits);
__IO_REG32_BIT(SDHC1_REV_NO,              0x10013020,__READ      ,__REV_NO_bits);
__IO_REG32_BIT(SDHC1_INT_CTRL,            0x10013024,__READ_WRITE,__MMCSD_INT_CTRL_bits);
__IO_REG32_BIT(SDHC1_CMD,                 0x10013028,__READ_WRITE,__CMD_bits);
__IO_REG32_BIT(SDHC1_ARGH,                0x1001302C,__READ_WRITE,__ARGH_bits);
__IO_REG32_BIT(SDHC1_ARGL,                0x10013030,__READ_WRITE,__ARGL_bits);
__IO_REG32_BIT(SDHC1_RES_FIFO,            0x10013034,__READ      ,__RES_FIFO_bits);
__IO_REG32_BIT(SDHC1_BUFFER_ACCESS,       0x10013038,__READ_WRITE,__BUFFER_ACCESS_bits);

 /***************************************************************************
 **
 **  MMC/SDHC2
 **
 ***************************************************************************/
__IO_REG32_BIT(SDHC2_STR_STP_CLK,         0x10014000,__READ_WRITE,__STR_STP_CLK_bits);
__IO_REG32_BIT(SDHC2_STATUS,              0x10014004,__READ      ,__SD_STATUS_bits);
__IO_REG32_BIT(SDHC2_CLK_RATE,            0x10014008,__READ_WRITE,__CLK_RATE_bits);
__IO_REG32_BIT(SDHC2_CMD_DAT_CONT,        0x1001400C,__READ_WRITE,__CMD_DAT_CONT_bits);
__IO_REG32_BIT(SDHC2_RES_TO,              0x10014010,__READ_WRITE,__RES_TO_bits);
__IO_REG32_BIT(SDHC2_READ_TO,             0x10014014,__READ_WRITE,__READ_TO_bits);
__IO_REG32_BIT(SDHC2_BLK_LEN,             0x10014018,__READ_WRITE,__BLK_LEN_bits);
__IO_REG32_BIT(SDHC2_NOB,                 0x1001401C,__READ_WRITE,__NOB_bits);
__IO_REG32_BIT(SDHC2_REV_NO,              0x10014020,__READ      ,__REV_NO_bits);
__IO_REG32_BIT(SDHC2_INT_CTRL,            0x10014024,__READ_WRITE,__MMCSD_INT_CTRL_bits);
__IO_REG32_BIT(SDHC2_CMD,                 0x10014028,__READ_WRITE,__CMD_bits);
__IO_REG32_BIT(SDHC2_ARGH,                0x1001402C,__READ_WRITE,__ARGH_bits);
__IO_REG32_BIT(SDHC2_ARGL,                0x10014030,__READ_WRITE,__ARGL_bits);
__IO_REG32_BIT(SDHC2_RES_FIFO,            0x10014034,__READ      ,__RES_FIFO_bits);
__IO_REG32_BIT(SDHC2_BUFFER_ACCESS,       0x10014038,__READ_WRITE,__BUFFER_ACCESS_bits);

/***************************************************************************
 **
 **  Digital Audio Mux (AUDMUX)
 **
 ***************************************************************************/
__IO_REG32_BIT(HPCR1,                     0x10016000,__READ_WRITE,__HPCR_bits);
__IO_REG32_BIT(HPCR2,                     0x10016004,__READ_WRITE,__HPCR_bits);
__IO_REG32_BIT(HPCR3,                     0x10016008,__READ_WRITE,__HPCR_bits);
__IO_REG32_BIT(PPCR1,                     0x10016010,__READ_WRITE,__PPCR_bits);
__IO_REG32_BIT(PPCR2,                     0x10016014,__READ_WRITE,__PPCR_bits);
__IO_REG32_BIT(PPCR3,                     0x1001601C,__READ_WRITE,__PPCR_bits);

/***************************************************************************
 **
 **  UART1
 **
 ***************************************************************************/
__IO_REG32_BIT(URXD_1,                    0x1000A000,__READ      ,__URXD_bits);
__IO_REG32_BIT(UTXD_1,                    0x1000A040,__WRITE     ,__UTXD_bits);
__IO_REG32_BIT(UCR1_1,                    0x1000A080,__READ_WRITE,__UCR1_bits);
__IO_REG32_BIT(UCR2_1,                    0x1000A084,__READ_WRITE,__UCR2_bits);
__IO_REG32_BIT(UCR3_1,                    0x1000A088,__READ_WRITE,__UCR3_bits);
__IO_REG32_BIT(UCR4_1,                    0x1000A08C,__READ_WRITE,__UCR4_bits);
__IO_REG32_BIT(UFCR_1,                    0x1000A090,__READ_WRITE,__UFCR_bits);
__IO_REG32_BIT(USR1_1,                    0x1000A094,__READ_WRITE,__USR1_bits);
__IO_REG32_BIT(USR2_1,                    0x1000A098,__READ_WRITE,__USR2_bits);
__IO_REG32_BIT(UESC_1,                    0x1000A09C,__READ_WRITE,__UESC_bits);
__IO_REG32_BIT(UTIM_1,                    0x1000A0A0,__READ_WRITE,__UTIM_bits);
__IO_REG32_BIT(UBIR_1,                    0x1000A0A4,__READ_WRITE,__UBIR_bits);
__IO_REG32_BIT(UBMR_1,                    0x1000A0A8,__READ_WRITE,__UBMR_bits);
__IO_REG32_BIT(UBRC_1,                    0x1000A0AC,__READ_WRITE,__UBRC_bits);
__IO_REG32_BIT(ONEMS_1,                   0x1000A0B0,__READ_WRITE,__ONEMS_bits);
__IO_REG32_BIT(UTS_1,                     0x1000A0B4,__READ_WRITE,__UTS_bits);

/***************************************************************************
 **
 **  UART2
 **
 ***************************************************************************/
__IO_REG32_BIT(URXD_2,                    0x1000B000,__READ      ,__URXD_bits);
__IO_REG32_BIT(UTXD_2,                    0x1000B040,__WRITE     ,__UTXD_bits);
__IO_REG32_BIT(UCR1_2,                    0x1000B080,__READ_WRITE,__UCR1_bits);
__IO_REG32_BIT(UCR2_2,                    0x1000B084,__READ_WRITE,__UCR2_bits);
__IO_REG32_BIT(UCR3_2,                    0x1000B088,__READ_WRITE,__UCR3_bits);
__IO_REG32_BIT(UCR4_2,                    0x1000B08C,__READ_WRITE,__UCR4_bits);
__IO_REG32_BIT(UFCR_2,                    0x1000B090,__READ_WRITE,__UFCR_bits);
__IO_REG32_BIT(USR1_2,                    0x1000B094,__READ_WRITE,__USR1_bits);
__IO_REG32_BIT(USR2_2,                    0x1000B098,__READ_WRITE,__USR2_bits);
__IO_REG32_BIT(UESC_2,                    0x1000B09C,__READ_WRITE,__UESC_bits);
__IO_REG32_BIT(UTIM_2,                    0x1000B0A0,__READ_WRITE,__UTIM_bits);
__IO_REG32_BIT(UBIR_2,                    0x1000B0A4,__READ_WRITE,__UBIR_bits);
__IO_REG32_BIT(UBMR_2,                    0x1000B0A8,__READ_WRITE,__UBMR_bits);
__IO_REG32_BIT(UBRC_2,                    0x1000B0AC,__READ_WRITE,__UBRC_bits);
__IO_REG32_BIT(ONEMS_2,                   0x1000B0B0,__READ_WRITE,__ONEMS_bits);
__IO_REG32_BIT(UTS_2,                     0x1000B0B4,__READ_WRITE,__UTS_bits);

/***************************************************************************
 **
 **  UART3
 **
 ***************************************************************************/
__IO_REG32_BIT(URXD_3,                    0x1000C000,__READ      ,__URXD_bits);
__IO_REG32_BIT(UTXD_3,                    0x1000C040,__WRITE     ,__UTXD_bits);
__IO_REG32_BIT(UCR1_3,                    0x1000C080,__READ_WRITE,__UCR1_bits);
__IO_REG32_BIT(UCR2_3,                    0x1000C084,__READ_WRITE,__UCR2_bits);
__IO_REG32_BIT(UCR3_3,                    0x1000C088,__READ_WRITE,__UCR3_bits);
__IO_REG32_BIT(UCR4_3,                    0x1000C08C,__READ_WRITE,__UCR4_bits);
__IO_REG32_BIT(UFCR_3,                    0x1000C090,__READ_WRITE,__UFCR_bits);
__IO_REG32_BIT(USR1_3,                    0x1000C094,__READ_WRITE,__USR1_bits);
__IO_REG32_BIT(USR2_3,                    0x1000C098,__READ_WRITE,__USR2_bits);
__IO_REG32_BIT(UESC_3,                    0x1000C09C,__READ_WRITE,__UESC_bits);
__IO_REG32_BIT(UTIM_3,                    0x1000C0A0,__READ_WRITE,__UTIM_bits);
__IO_REG32_BIT(UBIR_3,                    0x1000C0A4,__READ_WRITE,__UBIR_bits);
__IO_REG32_BIT(UBMR_3,                    0x1000C0A8,__READ_WRITE,__UBMR_bits);
__IO_REG32_BIT(UBRC_3,                    0x1000C0AC,__READ_WRITE,__UBRC_bits);
__IO_REG32_BIT(ONEMS_3,                   0x1000C0B0,__READ_WRITE,__ONEMS_bits);
__IO_REG32_BIT(UTS_3,                     0x1000C0B4,__READ_WRITE,__UTS_bits);

/***************************************************************************
 **
 **  UART4
 **
 ***************************************************************************/
__IO_REG32_BIT(URXD_4,                    0x1000D000,__READ      ,__URXD_bits);
__IO_REG32_BIT(UTXD_4,                    0x1000D040,__WRITE     ,__UTXD_bits);
__IO_REG32_BIT(UCR1_4,                    0x1000D080,__READ_WRITE,__UCR1_bits);
__IO_REG32_BIT(UCR2_4,                    0x1000D084,__READ_WRITE,__UCR2_bits);
__IO_REG32_BIT(UCR3_4,                    0x1000D088,__READ_WRITE,__UCR3_bits);
__IO_REG32_BIT(UCR4_4,                    0x1000D08C,__READ_WRITE,__UCR4_bits);
__IO_REG32_BIT(UFCR_4,                    0x1000D090,__READ_WRITE,__UFCR_bits);
__IO_REG32_BIT(USR1_4,                    0x1000D094,__READ_WRITE,__USR1_bits);
__IO_REG32_BIT(USR2_4,                    0x1000D098,__READ_WRITE,__USR2_bits);
__IO_REG32_BIT(UESC_4,                    0x1000D09C,__READ_WRITE,__UESC_bits);
__IO_REG32_BIT(UTIM_4,                    0x1000D0A0,__READ_WRITE,__UTIM_bits);
__IO_REG32_BIT(UBIR_4,                    0x1000D0A4,__READ_WRITE,__UBIR_bits);
__IO_REG32_BIT(UBMR_4,                    0x1000D0A8,__READ_WRITE,__UBMR_bits);
__IO_REG32_BIT(UBRC_4,                    0x1000D0AC,__READ_WRITE,__UBRC_bits);
__IO_REG32_BIT(ONEMS_4,                   0x1000D0B0,__READ_WRITE,__ONEMS_bits);
__IO_REG32_BIT(UTS_4,                     0x1000D0B4,__READ_WRITE,__UTS_bits);

/***************************************************************************
 **
 **  USB OTG
 **
 ***************************************************************************/
__IO_REG32_BIT(HWMODE,                    0x10024000,__READ_WRITE,__HWMODE_bits);
__IO_REG32_BIT(CINT_STAT,                 0x10024004,__READ_WRITE,__CINT_STAT_bits);
__IO_REG32_BIT(CINT_STEN,                 0x10024008,__READ_WRITE,__CINT_STEN_bits);
__IO_REG32_BIT(CLK_CTRL,                  0x1002400C,__READ_WRITE,__CLK_CTRL_bits);
__IO_REG32_BIT(RST_CTRL,                  0x10024010,__READ_WRITE,__RST_CTRL_bits);
__IO_REG32_BIT(FRM_INVTL,                 0x10024014,__READ_WRITE,__FRM_INVTL_bits);
__IO_REG32_BIT(FRM_REMAIN,                0x10024018,__READ      ,__FRM_REMAIN_bits);
__IO_REG32_BIT(HNP_CTRL,                  0x1002401C,__READ_WRITE,__HNP_CTRL_bits);
__IO_REG32_BIT(HNP_TMR1,                  0x10024020,__READ_WRITE,__HNP_TMR1_bits);
__IO_REG32_BIT(HNP_TMR2,                  0x10024024,__READ_WRITE,__HNP_TMR2_bits);
__IO_REG32_BIT(HNP_TMR3,                  0x10024028,__READ_WRITE,__HNP_TMR3_bits);
__IO_REG32_BIT(HNP_INT_STAT,              0x1002402C,__READ_WRITE,__HNP_INT_STAT_bits);
__IO_REG32_BIT(HNP_INT_EN,                0x10024030,__READ_WRITE,__HNP_INT_EN_bits);
__IO_REG32_BIT(FUNCOMSTAT,                0x10024040,__READ_WRITE,__FUNCOMSTAT_bits);
__IO_REG32_BIT(DEVADDR,                   0x10024044,__READ_WRITE,__DEVADDR_bits);
__IO_REG32_BIT(SYSINTSTAT,                0x10024048,__READ_WRITE,__SYSINTSTAT_bits);
__IO_REG32_BIT(SYSINTEN,                  0x1002404C,__READ_WRITE,__SYSINTEN_bits);
__IO_REG32_BIT(XBUFINTSTAT,               0x10024050,__READ_WRITE,__XBUFINTSTAT_bits);
__IO_REG32_BIT(YBUFINTSTAT,               0x10024054,__READ_WRITE,__YBUFINTSTAT_bits);
__IO_REG32_BIT(XYINT_INT_EN,              0x10024058,__READ_WRITE,__XYINT_INT_EN_bits);
__IO_REG32_BIT(OTG_XFILLSTAT,             0x1002405C,__READ_WRITE,__OTG_XFILLSTAT_bits);
__IO_REG32_BIT(OTG_YFILLSTAT,             0x10024060,__READ_WRITE,__OTG_YFILLSTAT_bits);
__IO_REG32_BIT(ENDPNTEN,                  0x10024064,__READ_WRITE,__ENDPNTEN_bits);
__IO_REG32_BIT(ENDPNRDY,                  0x10024068,__READ_WRITE,__ENDPNRDY_bits);
__IO_REG32_BIT(IMEDINT,                   0x1002406C,__READ_WRITE,__IMEDINT_bits);
__IO_REG32_BIT(EPNTDONESTAT,              0x10024070,__READ_WRITE,__EPNTDONESTAT_bits);
__IO_REG32_BIT(EPNTDONEEN,                0x10024074,__READ_WRITE,__EPNTDONEEN_bits);
__IO_REG32_BIT(EPNTTOGBITS,               0x10024078,__READ_WRITE,__EPNTTOGBITS_bits);
__IO_REG32_BIT(FNEPRDYCLR,                0x1002407C,__READ_WRITE,__FNEPRDYCLR_bits);
__IO_REG32_BIT(HOST_CTRL,                 0x10024080,__READ_WRITE,__HOST_CTRL_bits);
__IO_REG32_BIT(SYSISR,                    0x10024088,__READ_WRITE,__SYSISR_bits);
__IO_REG32_BIT(SYSIEN,                    0x1002408C,__READ_WRITE,__SYSISR_bits);
__IO_REG32_BIT(XBUFSTAT,                  0x10024098,__READ_WRITE,__XBUFSTAT_bits);
__IO_REG32_BIT(YBUFSTAT,                  0x1002409C,__READ_WRITE,__YBUFSTAT_bits);
__IO_REG32_BIT(XYINTEN,                   0x100240A0,__READ_WRITE,__XYINTEN_bits);
__IO_REG32_BIT(XFILLSTAT,                 0x100240A8,__READ_WRITE,__XFILLSTAT_bits);
__IO_REG32_BIT(YFILLSTAT,                 0x100240AC,__READ_WRITE,__YFILLSTAT_bits);
__IO_REG32_BIT(ETDENSET,                  0x100240C0,__READ_WRITE,__ETDENSET_bits);
__IO_REG32_BIT(ETDENCLR,                  0x100240C4,__WRITE     ,__ETDENCLR_bits);
__IO_REG32_BIT(IMMEDINT,                  0x100240CC,__READ_WRITE,__IMMEDINT_bits);
__IO_REG32_BIT(ETDDONESTAT,               0x100240D0,__READ_WRITE,__ETDDONESTAT_bits);
__IO_REG32_BIT(ETDDONEN,                  0x100240D4,__READ_WRITE,__ETDDONEN_bits);
__IO_REG32_BIT(FRMNUB,                    0x100240E0,__READ_WRITE,__FRMNUB_bits);
__IO_REG32_BIT(LSTHRESH,                  0x100240E4,__READ_WRITE,__LSTHRESH_bits);
__IO_REG32_BIT(ROOTHUBA,                  0x100240E8,__READ      ,__ROOTHUBA_bits);
__IO_REG32_BIT(ROOTHUBB,                  0x100240EC,__READ_WRITE,__ROOTHUBB_bits);
__IO_REG32_BIT(ROOTSTAT,                  0x100240F0,__READ_WRITE,__ROOTSTAT_bits);
__IO_REG32_BIT(PORTSTAT1,                 0x100240F4,__READ_WRITE,__PORTSTAT_bits);
__IO_REG32_BIT(PORTSTAT2,                 0x100240F8,__READ_WRITE,__PORTSTAT_bits);
__IO_REG32_BIT(PORTSTAT3,                 0x100240FC,__READ_WRITE,__PORTSTAT_bits);
__IO_REG32_BIT(USB_EP0_DWORD0,            0x10024200,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP0_DWORD1,            0x10024204,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP0_DWORD2,            0x10024208,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP0_DWORD3,            0x1002420C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP1_DWORD0,            0x10024210,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP1_DWORD1,            0x10024214,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP1_DWORD2,            0x10024218,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP1_DWORD3,            0x1002421C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP2_DWORD0,            0x10024220,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP2_DWORD1,            0x10024224,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP2_DWORD2,            0x10024228,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP2_DWORD3,            0x1002422C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP3_DWORD0,            0x10024230,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP3_DWORD1,            0x10024234,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP3_DWORD2,            0x10024238,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP3_DWORD3,            0x1002423C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP4_DWORD0,            0x10024240,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP4_DWORD1,            0x10024244,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP4_DWORD2,            0x10024248,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP4_DWORD3,            0x1002424C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP5_DWORD0,            0x10024250,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP5_DWORD1,            0x10024254,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP5_DWORD2,            0x10024258,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP5_DWORD3,            0x1002425C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP6_DWORD0,            0x10024260,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP6_DWORD1,            0x10024264,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP6_DWORD2,            0x10024268,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP6_DWORD3,            0x1002426C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP7_DWORD0,            0x10024270,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP7_DWORD1,            0x10024274,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP7_DWORD2,            0x10024278,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP7_DWORD3,            0x1002427C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP8_DWORD0,            0x10024280,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP8_DWORD1,            0x10024284,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP8_DWORD2,            0x10024288,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP8_DWORD3,            0x1002428C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP9_DWORD0,            0x10024290,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP9_DWORD1,            0x10024294,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP9_DWORD2,            0x10024298,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP9_DWORD3,            0x1002429C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP10_DWORD0,           0x100242A0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP10_DWORD1,           0x100242A4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP10_DWORD2,           0x100242A8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP10_DWORD3,           0x100242AC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP11_DWORD0,           0x100242B0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP11_DWORD1,           0x100242B4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP11_DWORD2,           0x100242B8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP11_DWORD3,           0x100242BC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP12_DWORD0,           0x100242C0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP12_DWORD1,           0x100242C4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP12_DWORD2,           0x100242C8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP12_DWORD3,           0x100242CC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP13_DWORD0,           0x100242D0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP13_DWORD1,           0x100242D4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP13_DWORD2,           0x100242D8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP13_DWORD3,           0x100242DC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP14_DWORD0,           0x100242E0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP14_DWORD1,           0x100242E4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP14_DWORD2,           0x100242E8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP14_DWORD3,           0x100242EC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP15_DWORD0,           0x100242F0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP15_DWORD1,           0x100242F4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP15_DWORD2,           0x100242F8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP15_DWORD3,           0x100242FC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP16_DWORD0,           0x10024300,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP16_DWORD1,           0x10024304,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP16_DWORD2,           0x10024308,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP16_DWORD3,           0x1002430C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP17_DWORD0,           0x10024310,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP17_DWORD1,           0x10024314,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP17_DWORD2,           0x10024318,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP17_DWORD3,           0x1002431C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP18_DWORD0,           0x10024320,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP18_DWORD1,           0x10024324,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP18_DWORD2,           0x10024328,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP18_DWORD3,           0x1002432C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP19_DWORD0,           0x10024330,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP19_DWORD1,           0x10024334,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP19_DWORD2,           0x10024338,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP19_DWORD3,           0x1002433C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP20_DWORD0,           0x10024340,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP20_DWORD1,           0x10024344,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP20_DWORD2,           0x10024348,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP20_DWORD3,           0x1002434C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP21_DWORD0,           0x10024350,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP21_DWORD1,           0x10024354,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP21_DWORD2,           0x10024358,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP21_DWORD3,           0x1002435C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP22_DWORD0,           0x10024360,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP22_DWORD1,           0x10024364,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP22_DWORD2,           0x10024368,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP22_DWORD3,           0x1002436C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP23_DWORD0,           0x10024370,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP23_DWORD1,           0x10024374,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP23_DWORD2,           0x10024378,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP23_DWORD3,           0x1002437C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP24_DWORD0,           0x10024380,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP24_DWORD1,           0x10024384,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP24_DWORD2,           0x10024388,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP24_DWORD3,           0x1002438C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP25_DWORD0,           0x10024390,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP25_DWORD1,           0x10024394,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP25_DWORD2,           0x10024398,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP25_DWORD3,           0x1002439C,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP26_DWORD0,           0x100243A0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP26_DWORD1,           0x100243A4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP26_DWORD2,           0x100243A8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP26_DWORD3,           0x100243AC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP27_DWORD0,           0x100243B0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP27_DWORD1,           0x100243B4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP27_DWORD2,           0x100243B8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP27_DWORD3,           0x100243BC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP28_DWORD0,           0x100243C0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP28_DWORD1,           0x100243C4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP28_DWORD2,           0x100243C8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP28_DWORD3,           0x100243CC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP29_DWORD0,           0x100243D0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP29_DWORD1,           0x100243D4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP29_DWORD2,           0x100243D8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP29_DWORD3,           0x100243DC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP30_DWORD0,           0x100243E0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP30_DWORD1,           0x100243E4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP30_DWORD2,           0x100243E8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP30_DWORD3,           0x100243EC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(USB_EP31_DWORD0,           0x100243F0,__READ_WRITE,__USB_EP_DWORD0_bits);
__IO_REG32_BIT(USB_EP31_DWORD1,           0x100243F4,__READ_WRITE,__USB_EP_DWORD1_bits);
__IO_REG32_BIT(USB_EP31_DWORD2,           0x100243F8,__READ_WRITE,__USB_EP_DWORD2_bits);
__IO_REG32_BIT(USB_EP31_DWORD3,           0x100243FC,__READ_WRITE,__USB_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP0_DWORD0,            0x10024400,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP0_DWORD1,            0x10024404,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP0_DWORD2,            0x10024408,__READ_WRITE);
__IO_REG32_BIT(OTG_EP0_DWORD3,            0x1002440C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP1_DWORD0,            0x10024410,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP1_DWORD1,            0x10024414,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP1_DWORD2,            0x10024418,__READ_WRITE);
__IO_REG32_BIT(OTG_EP1_DWORD3,            0x1002441C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP2_DWORD0,            0x10024420,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP2_DWORD1,            0x10024424,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP2_DWORD2,            0x10024428,__READ_WRITE);
__IO_REG32_BIT(OTG_EP2_DWORD3,            0x1002442C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP3_DWORD0,            0x10024430,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP3_DWORD1,            0x10024434,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP3_DWORD2,            0x10024438,__READ_WRITE);
__IO_REG32_BIT(OTG_EP3_DWORD3,            0x1002443C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP4_DWORD0,            0x10024440,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP4_DWORD1,            0x10024444,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP4_DWORD2,            0x10024448,__READ_WRITE);
__IO_REG32_BIT(OTG_EP4_DWORD3,            0x1002444C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP5_DWORD0,            0x10024450,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP5_DWORD1,            0x10024454,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP5_DWORD2,            0x10024458,__READ_WRITE);
__IO_REG32_BIT(OTG_EP5_DWORD3,            0x1002445C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP6_DWORD0,            0x10024460,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP6_DWORD1,            0x10024464,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP6_DWORD2,            0x10024468,__READ_WRITE);
__IO_REG32_BIT(OTG_EP6_DWORD3,            0x1002446C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP7_DWORD0,            0x10024470,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP7_DWORD1,            0x10024474,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP7_DWORD2,            0x10024478,__READ_WRITE);
__IO_REG32_BIT(OTG_EP7_DWORD3,            0x1002447C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP8_DWORD0,            0x10024480,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP8_DWORD1,            0x10024484,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP8_DWORD2,            0x10024488,__READ_WRITE);
__IO_REG32_BIT(OTG_EP8_DWORD3,            0x1002448C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP9_DWORD0,            0x10024490,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP9_DWORD1,            0x10024494,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP9_DWORD2,            0x10024498,__READ_WRITE);
__IO_REG32_BIT(OTG_EP9_DWORD3,            0x1002449C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP10_DWORD0,           0x100244A0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP10_DWORD1,           0x100244A4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP10_DWORD2,           0x100244A8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP10_DWORD3,           0x100244AC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP11_DWORD0,           0x100244B0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP11_DWORD1,           0x100244B4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP11_DWORD2,           0x100244B8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP11_DWORD3,           0x100244BC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP12_DWORD0,           0x100244C0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP12_DWORD1,           0x100244C4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP12_DWORD2,           0x100244C8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP12_DWORD3,           0x100244CC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP13_DWORD0,           0x100244D0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP13_DWORD1,           0x100244D4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP13_DWORD2,           0x100244D8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP13_DWORD3,           0x100244DC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP14_DWORD0,           0x100244E0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP14_DWORD1,           0x100244E4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP14_DWORD2,           0x100244E8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP14_DWORD3,           0x100244EC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP15_DWORD0,           0x100244F0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP15_DWORD1,           0x100244F4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP15_DWORD2,           0x100244F8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP15_DWORD3,           0x100244FC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP16_DWORD0,           0x10024500,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP16_DWORD1,           0x10024504,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP16_DWORD2,           0x10024508,__READ_WRITE);
__IO_REG32_BIT(OTG_EP16_DWORD3,           0x1002450C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP17_DWORD0,           0x10024510,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP17_DWORD1,           0x10024514,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP17_DWORD2,           0x10024518,__READ_WRITE);
__IO_REG32_BIT(OTG_EP17_DWORD3,           0x1002451C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP18_DWORD0,           0x10024520,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP18_DWORD1,           0x10024524,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP18_DWORD2,           0x10024528,__READ_WRITE);
__IO_REG32_BIT(OTG_EP18_DWORD3,           0x1002452C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP19_DWORD0,           0x10024530,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP19_DWORD1,           0x10024534,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP19_DWORD2,           0x10024538,__READ_WRITE);
__IO_REG32_BIT(OTG_EP19_DWORD3,           0x1002453C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP20_DWORD0,           0x10024540,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP20_DWORD1,           0x10024544,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP20_DWORD2,           0x10024548,__READ_WRITE);
__IO_REG32_BIT(OTG_EP20_DWORD3,           0x1002454C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP21_DWORD0,           0x10024550,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP21_DWORD1,           0x10024554,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP21_DWORD2,           0x10024558,__READ_WRITE);
__IO_REG32_BIT(OTG_EP21_DWORD3,           0x1002455C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP22_DWORD0,           0x10024560,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP22_DWORD1,           0x10024564,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP22_DWORD2,           0x10024568,__READ_WRITE);
__IO_REG32_BIT(OTG_EP22_DWORD3,           0x1002456C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP23_DWORD0,           0x10024570,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP23_DWORD1,           0x10024574,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP23_DWORD2,           0x10024578,__READ_WRITE);
__IO_REG32_BIT(OTG_EP23_DWORD3,           0x1002457C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP24_DWORD0,           0x10024580,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP24_DWORD1,           0x10024584,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP24_DWORD2,           0x10024588,__READ_WRITE);
__IO_REG32_BIT(OTG_EP24_DWORD3,           0x1002458C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP25_DWORD0,           0x10024590,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP25_DWORD1,           0x10024594,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP25_DWORD2,           0x10024598,__READ_WRITE);
__IO_REG32_BIT(OTG_EP25_DWORD3,           0x1002459C,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP26_DWORD0,           0x100245A0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP26_DWORD1,           0x100245A4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP26_DWORD2,           0x100245A8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP26_DWORD3,           0x100245AC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP27_DWORD0,           0x100245B0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP27_DWORD1,           0x100245B4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP27_DWORD2,           0x100245B8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP27_DWORD3,           0x100245BC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP28_DWORD0,           0x100245C0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP28_DWORD1,           0x100245C4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP28_DWORD2,           0x100245C8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP28_DWORD3,           0x100245CC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP29_DWORD0,           0x100245D0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP29_DWORD1,           0x100245D4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP29_DWORD2,           0x100245D8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP29_DWORD3,           0x100245DC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP30_DWORD0,           0x100245E0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP30_DWORD1,           0x100245E4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP30_DWORD2,           0x100245E8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP30_DWORD3,           0x100245EC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(OTG_EP31_DWORD0,           0x100245F0,__READ_WRITE,__OTG_EP_DWORD0_bits);
__IO_REG32_BIT(OTG_EP31_DWORD1,           0x100245F4,__READ_WRITE,__OTG_EP_DWORD1_bits);
__IO_REG32(    OTG_EP31_DWORD2,           0x100245F8,__READ_WRITE);
__IO_REG32_BIT(OTG_EP31_DWORD3,           0x100245FC,__READ_WRITE,__OTG_EP_DWORD3_bits);
__IO_REG32_BIT(USBCTRL,                   0x10024600,__READ_WRITE,__USBCTRL_bits);
__IO_REG32_BIT(DMAREV,                    0x10024800,__READ      ,__DMAREV_bits);
__IO_REG32_BIT(DMAINTSTAT,                0x10024804,__READ      ,__DMAINTSTAT_bits);
__IO_REG32_BIT(DMAINTEN,                  0x10024808,__READ_WRITE,__DMAINTEN_bits);
__IO_REG32(    ETDDMAERSTAT,              0x1002480C,__READ_WRITE);
__IO_REG32(    EPDMAERSTAT,               0x10024810,__READ_WRITE);
__IO_REG32(    ETDDMAEN,                  0x10024820,__READ_WRITE);
__IO_REG32(    EPDMAEN,                   0x10024824,__READ_WRITE);
__IO_REG32(    ETDDMAXTEN,                0x10024828,__WRITE     );
__IO_REG32(    EPDMAXTEN,                 0x1002482C,__WRITE     );
__IO_REG32(    ETDDMAENXYT,               0x10024830,__WRITE     );
__IO_REG32(    EPDMAENXYT,                0x10024834,__WRITE     );
__IO_REG32(    ETCDMABST4EN,              0x10024838,__READ_WRITE);
__IO_REG32(    EPDMABST4EN,               0x1002483C,__READ_WRITE);
__IO_REG32_BIT(MISCCONTROL,               0x10024840,__READ_WRITE,__MISCCONTROL_bits);
__IO_REG32(    ETDDMACHANLCLR,            0x10024848,__WRITE     );
__IO_REG32(    EPDMACHANLCLR,             0x1002484C,__WRITE     );
__IO_REG32(    ETDSMSA0,                  0x10024900,__READ_WRITE);
__IO_REG32(    ETDSMSA1,                  0x10024904,__READ_WRITE);
__IO_REG32(    ETDSMSA2,                  0x10024908,__READ_WRITE);
__IO_REG32(    ETDSMSA3,                  0x1002490C,__READ_WRITE);
__IO_REG32(    ETDSMSA4,                  0x10024910,__READ_WRITE);
__IO_REG32(    ETDSMSA5,                  0x10024914,__READ_WRITE);
__IO_REG32(    ETDSMSA6,                  0x10024918,__READ_WRITE);
__IO_REG32(    ETDSMSA7,                  0x1002491C,__READ_WRITE);
__IO_REG32(    ETDSMSA8,                  0x10024920,__READ_WRITE);
__IO_REG32(    ETDSMSA9,                  0x10024924,__READ_WRITE);
__IO_REG32(    ETDSMSA10,                 0x10024928,__READ_WRITE);
__IO_REG32(    ETDSMSA11,                 0x1002492C,__READ_WRITE);
__IO_REG32(    ETDSMSA12,                 0x10024930,__READ_WRITE);
__IO_REG32(    ETDSMSA13,                 0x10024934,__READ_WRITE);
__IO_REG32(    ETDSMSA14,                 0x10024938,__READ_WRITE);
__IO_REG32(    ETDSMSA15,                 0x1002493C,__READ_WRITE);
__IO_REG32(    ETDSMSA16,                 0x10024940,__READ_WRITE);
__IO_REG32(    ETDSMSA17,                 0x10024944,__READ_WRITE);
__IO_REG32(    ETDSMSA18,                 0x10024948,__READ_WRITE);
__IO_REG32(    ETDSMSA19,                 0x1002494C,__READ_WRITE);
__IO_REG32(    ETDSMSA20,                 0x10024950,__READ_WRITE);
__IO_REG32(    ETDSMSA21,                 0x10024954,__READ_WRITE);
__IO_REG32(    ETDSMSA22,                 0x10024958,__READ_WRITE);
__IO_REG32(    ETDSMSA23,                 0x1002495C,__READ_WRITE);
__IO_REG32(    ETDSMSA24,                 0x10024960,__READ_WRITE);
__IO_REG32(    ETDSMSA25,                 0x10024964,__READ_WRITE);
__IO_REG32(    ETDSMSA26,                 0x10024968,__READ_WRITE);
__IO_REG32(    ETDSMSA27,                 0x1002496C,__READ_WRITE);
__IO_REG32(    ETDSMSA28,                 0x10024970,__READ_WRITE);
__IO_REG32(    ETDSMSA29,                 0x10024974,__READ_WRITE);
__IO_REG32(    ETDSMSA30,                 0x10024978,__READ_WRITE);
__IO_REG32(    ETDSMSA31,                 0x1002497C,__READ_WRITE);
__IO_REG32(    EPSMSA0,                   0x10024980,__READ_WRITE);
__IO_REG32(    EPSMSA1,                   0x10024984,__READ_WRITE);
__IO_REG32(    EPSMSA2,                   0x10024988,__READ_WRITE);
__IO_REG32(    EPSMSA3,                   0x1002498C,__READ_WRITE);
__IO_REG32(    EPSMSA4,                   0x10024990,__READ_WRITE);
__IO_REG32(    EPSMSA5,                   0x10024994,__READ_WRITE);
__IO_REG32(    EPSMSA6,                   0x10024998,__READ_WRITE);
__IO_REG32(    EPSMSA7,                   0x1002499C,__READ_WRITE);
__IO_REG32(    EPSMSA8,                   0x100249A0,__READ_WRITE);
__IO_REG32(    EPSMSA9,                   0x100249A4,__READ_WRITE);
__IO_REG32(    EPSMSA10,                  0x100249A8,__READ_WRITE);
__IO_REG32(    EPSMSA11,                  0x100249AC,__READ_WRITE);
__IO_REG32(    EPSMSA12,                  0x100249B0,__READ_WRITE);
__IO_REG32(    EPSMSA13,                  0x100249B4,__READ_WRITE);
__IO_REG32(    EPSMSA14,                  0x100249B8,__READ_WRITE);
__IO_REG32(    EPSMSA15,                  0x100249BC,__READ_WRITE);
__IO_REG32(    EPSMSA16,                  0x100249C0,__READ_WRITE);
__IO_REG32(    EPSMSA17,                  0x100249C4,__READ_WRITE);
__IO_REG32(    EPSMSA18,                  0x100249C8,__READ_WRITE);
__IO_REG32(    EPSMSA19,                  0x100249CC,__READ_WRITE);
__IO_REG32(    EPSMSA20,                  0x100249D0,__READ_WRITE);
__IO_REG32(    EPSMSA21,                  0x100249D4,__READ_WRITE);
__IO_REG32(    EPSMSA22,                  0x100249D8,__READ_WRITE);
__IO_REG32(    EPSMSA23,                  0x100249DC,__READ_WRITE);
__IO_REG32(    EPSMSA24,                  0x100249E0,__READ_WRITE);
__IO_REG32(    EPSMSA25,                  0x100249E4,__READ_WRITE);
__IO_REG32(    EPSMSA26,                  0x100249E8,__READ_WRITE);
__IO_REG32(    EPSMSA27,                  0x100249EC,__READ_WRITE);
__IO_REG32(    EPSMSA28,                  0x100249F0,__READ_WRITE);
__IO_REG32(    EPSMSA29,                  0x100249F4,__READ_WRITE);
__IO_REG32(    EPSMSA30,                  0x100249F8,__READ_WRITE);
__IO_REG32(    EPSMSA31,                  0x100249FC,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR0,             0x10024A00,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR1,             0x10024A04,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR2,             0x10024A08,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR3,             0x10024A0C,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR4,             0x10024A10,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR5,             0x10024A14,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR6,             0x10024A18,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR7,             0x10024A1C,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR8,             0x10024A20,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR9,             0x10024A24,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR10,            0x10024A28,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR11,            0x10024A2C,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR12,            0x10024A30,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR13,            0x10024A34,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR14,            0x10024A38,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR15,            0x10024A3C,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR16,            0x10024A40,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR17,            0x10024A44,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR18,            0x10024A48,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR19,            0x10024A4C,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR20,            0x10024A50,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR21,            0x10024A54,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR22,            0x10024A58,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR23,            0x10024A5C,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR24,            0x10024A60,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR25,            0x10024A64,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR26,            0x10024A68,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR27,            0x10024A6C,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR28,            0x10024A70,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR29,            0x10024A74,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR30,            0x10024A78,__READ_WRITE);
__IO_REG32(    ETDDMABUFPTR31,            0x10024A7C,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR0,              0x10024A80,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR1,              0x10024A84,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR2,              0x10024A88,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR3,              0x10024A8C,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR4,              0x10024A90,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR5,              0x10024A94,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR6,              0x10024A98,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR7,              0x10024A9C,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR8,              0x10024AA0,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR9,              0x10024AA4,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR10,             0x10024AA8,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR11,             0x10024AAC,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR12,             0x10024AB0,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR13,             0x10024AB4,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR14,             0x10024AB8,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR15,             0x10024ABC,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR16,             0x10024AC0,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR17,             0x10024AC4,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR18,             0x10024AC8,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR19,             0x10024ACC,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR20,             0x10024AD0,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR21,             0x10024AD4,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR22,             0x10024AD8,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR23,             0x10024ADC,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR24,             0x10024AE0,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR25,             0x10024AE4,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR26,             0x10024AE8,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR27,             0x10024AEC,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR28,             0x10024AF0,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR29,             0x10024AF4,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR30,             0x10024AF8,__READ_WRITE);
__IO_REG32(    EPDMABUFPTR31,             0x10024AFC,__READ_WRITE);

/***************************************************************************
 **
 **  PCMCIA
 **
 ***************************************************************************/
__IO_REG32_BIT(PIPR,                      0xDF002000,__READ      ,__PIPR_bits);
__IO_REG32_BIT(PSCR,                      0xDF002004,__READ      ,__PSCR_bits);
__IO_REG32_BIT(PER,                       0xDF002008,__READ_WRITE,__PER_bits);
__IO_REG32_BIT(PBR0,                      0xDF00200C,__READ_WRITE,__PBR_bits);
__IO_REG32_BIT(PBR1,                      0xDF002010,__READ_WRITE,__PBR_bits);
__IO_REG32_BIT(PBR2,                      0xDF002014,__READ_WRITE,__PBR_bits);
__IO_REG32_BIT(PBR3,                      0xDF002018,__READ_WRITE,__PBR_bits);
__IO_REG32_BIT(PBR4,                      0xDF00201C,__READ_WRITE,__PBR_bits);
__IO_REG32_BIT(POR0,                      0xDF002028,__READ_WRITE,__POR_bits);
__IO_REG32_BIT(POR1,                      0xDF00202C,__READ_WRITE,__POR_bits);
__IO_REG32_BIT(POR2,                      0xDF002030,__READ_WRITE,__POR_bits);
__IO_REG32_BIT(POR3,                      0xDF002034,__READ_WRITE,__POR_bits);
__IO_REG32_BIT(POR4,                      0xDF002038,__READ_WRITE,__POR_bits);
__IO_REG32_BIT(POFR0,                     0xDF002044,__READ_WRITE,__POFR_bits);
__IO_REG32_BIT(POFR1,                     0xDF002048,__READ_WRITE,__POFR_bits);
__IO_REG32_BIT(POFR2,                     0xDF00204C,__READ_WRITE,__POFR_bits);
__IO_REG32_BIT(POFR3,                     0xDF002050,__READ_WRITE,__POFR_bits);
__IO_REG32_BIT(POFR4,                     0xDF002054,__READ_WRITE,__POFR_bits);
__IO_REG32_BIT(PGCR,                      0xDF002060,__READ_WRITE,__PGCR_bits);
__IO_REG32_BIT(PGSR,                      0xDF002064,__READ      ,__PGSR_bits);

/***************************************************************************
 **
 **  Keypad Port (KPP)
 **
 ***************************************************************************/
__IO_REG16_BIT(KPCR,                      0x10008000,__READ_WRITE,__KPCR_bits);
__IO_REG16_BIT(KPSR,                      0x10008002,__READ_WRITE,__KPSR_bits);
__IO_REG16_BIT(KDDR,                      0x10008004,__READ_WRITE,__KDDR_bits);
__IO_REG16_BIT(KPDR,                      0x10008006,__READ_WRITE,__KPDR_bits);

/***************************************************************************
 **
 **  Fast InfraRed Interface (FIRI) Module
 **
 ***************************************************************************/
__IO_REG32_BIT(FIRITCR,                   0x10028000,__READ_WRITE,__FIRITCR_bits);
__IO_REG32_BIT(FIRITCTR,                  0x10028004,__READ_WRITE,__FIRITCTR_bits);
__IO_REG32_BIT(FIRIRCR,                   0x10028008,__READ_WRITE,__FIRIRCR_bits);
__IO_REG32_BIT(FIRITSR,                   0x1002800C,__READ_WRITE,__FIRITSR_bits);
__IO_REG32_BIT(FIRIRSR,                   0x10028010,__READ_WRITE,__FIRIRSR_bits);
__IO_REG32(    FIRITXD,                   0x10028014,__WRITE     );
__IO_REG32(    FIRIRXD,                   0x10028018,__READ      );
__IO_REG32_BIT(FIRICR,                    0x1002801C,__READ_WRITE,__FIRICR_bits);

/***************************************************************************
 **
 **  One Wire
 **
 ***************************************************************************/
__IO_REG16_BIT(OW_CONTROL,                0x10009000,__READ_WRITE,__OW_CONTROL_bits);
__IO_REG16_BIT(OW_TIME_DIVIDER,           0x10009002,__READ_WRITE,__OW_TIME_DIVIDER_bits);
__IO_REG16_BIT(OW_RESET,                  0x10009004,__READ_WRITE,__OW_RESET_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **   MC9328MX21 interrupt sources
 **
 ***************************************************************************/
//#define Unused                0              // Unused
//#define Unused                1              // Unused
//#define Unused                2              // Unused
//#define Unused                3              // Unused
//#define Unused                4              // Unused
//#define Unused                5              // Unused
#define NT_CSPI3               6              // Configurable SPI (CSPI3)
#define INT_SRCL               7              // Random Number Generator Accelerator (RNGA)
#define INT_GPIO               8              // General Purpose Input/Output (GPIO)
#define INT_FIRI               9              // Fast Infra Red Interface (FIRI)
#define INT_SDHC2              10             // Secure Digital Host Controller (SDHC2)
#define INT_SDHC1              11             // Secure Digital Host Controller (SDHC1)
#define INT_I2C                12             // I2C Bus Controller (I2C)
#define INT_SS2                13             // Synchronous Serial Interface 2(SSI2)
#define INT_SSI1               14             // Synchronous Serial Interface 1(SSI1)
#define INT_CSPI2              15             // Configurable SPI (CSPI2)
#define INT_CSPI1              16             // Configurable SPI (CSPI1)
#define INT_UART4              17             // UART4
#define INT_UART3              18             // UART3
#define INT_UART2              19             // UART2
#define INT_UART1              20             // UART1
#define INT_KPP                21             // Key Pad Port (KPP)
#define INT_RTC                22             // Real-Time Clock (RTC)
#define INT_PWM                23             // Pulse Width Modulator (PWM)
#define INT_GPT3               24             // General Purpose Timer (GPT3)
#define INT_GPT2               25             // General Purpose Timer (GPT2)
#define INT_GPT1               26             // General Purpose Timer (GPT1)
#define INT_WDOG               27             // Watchdog (WDOG)
#define INT_PCMCIA             28             // PCMCIA/CF Host Controller (PCMCIA)
#define INT_NFC                29             // Nand Flash Controller (NFC)
#define INT_BMI                30             // Bus Master Interface (BMI)
#define INT_CSI                31             // CMOS Sensor Interface (CSI)
#define INT_DMACH0             32             // DMA Channel 0
#define INT_DMACH1             33             // DMA Channel 1
#define INT_DMACH2             34             // DMA Channel 2
#define INT_DMACH3             35             // DMA Channel 3
#define INT_DMACH4             36             // DMA Channel 4
#define INT_DMACH5             37             // DMA Channel 5
#define INT_DMACH6             38             // DMA Channel 6
#define INT_DMACH7             39             // DMA Channel 7
#define INT_DMACH8             40             // DMA Channel 8
#define INT_DMACH9             41             // DMA Channel 9
#define INT_DMACH10            42             // DMA Channel 10
#define INT_DMACH11            43             // DMA Channel 11
#define INT_DMACH12            44             // DMA Channel 12
#define INT_DMACH13            45             // DMA Channel 13
#define INT_DMACH14            46             // DMA Channel 14
#define INT_DMACH15            47             // DMA Channel 15
//#define Reserved               48             // Unused
#define INT_EMMAENC            49             // eMMA Encoder Interrupt
#define INT_EMMADEC            50             // eMMA Decoder Interrupt
#define INT_EMMAPRP            51             // eMMA Pre Processor Interrupt
#define INT_EMMAPP             52             // eMMA Post Processor Interrupt
#define INT_USBWKUP            53             // USBOTG Wakeup Interrupt
#define INT_USBDMA             54             // USBOTG DMA Interrupt
#define INT_USBHOST            55             // USBOTG Host Interrupt
#define INT_USBFUNC            56             // USBOTG Function Interrupt
#define INT_USBMNP             57             // USBOTG HNP Interrupt
#define INT_USBCTRL            58             // USB OTG Control Interrupt
#define INT_SRCH               59             // Run-Time Integrity Checker (RTIC)
#define INT_SLCDC              60             // Smart LCD Controller (SLCDC)
#define INT_LCDC               61             // LCD Controller (LCDC)
//#define Reserved               62             // Unused
//#define Reserved               63             // Unused

#endif    /* __MC9328MX21_H */
