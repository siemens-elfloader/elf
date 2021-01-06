/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Texas Instruments OMAP5910
 **    
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2000
 **                                
 **    $Revision: 1.3 $
 **                                
 ***************************************************************************/

#ifndef __OMAP5910_H
#define __OMAP5910_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ICCARM/AARM
#endif

#if (((__TID__ >> 4) & 0x0F) != 0x2)
#error This file should only be compiled with "ARM9TDMI" processor variant
#endif

#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    OMAP5910 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/


/* MPU Private Peripheral Registers */

/***************************************************************************
 **
 **  MPU Timer 1 Registers 
 **
***************************************************************************/
__IO_REG32(MPU_CNTL_TIMER_1,0xFFFEC500,__READ_WRITE);                  /* MPU Timer 1 Control Timer Register, ResetValue = 00000000h */
__IO_REG32(MPU_LOAD_TIM_1,0xFFFEC504,__WRITE);                         /* MPU Timer 1 Load Timer Register, ResetValue = undef */
__IO_REG32(MPU_READ_TIM_1,0xFFFEC508,__READ);                          /* MPU Timer 1 Read Timer Register, ResetValue = undef */

/***************************************************************************
 **
 **  MPU Timer 2 Registers 
 **
***************************************************************************/
__IO_REG32(MPU_CNTL_TIMER_2,0xFFFEC600,__READ_WRITE);                  /* MPU Timer 2 Control Timer Register, ResetValue = 00000000h */
__IO_REG32(MPU_LOAD_TIM_2,0xFFFEC604,__WRITE);                         /* MPU Timer 2 Load Timer Register, ResetValue = undef */
__IO_REG32(MPU_READ_TIM_2,0xFFFEC608,__READ);                          /* MPU Timer 2 Read Timer Register, ResetValue = undef */

/***************************************************************************
 **
 **  MPU Timer 3 Registers 
 **
***************************************************************************/
__IO_REG32(MPU_CNTL_TIMER_3,0xFFFEC700,__READ_WRITE);                  /* MPU Timer 3 Control Timer Register, ResetValue = 00000000h */
__IO_REG32(MPU_LOAD_TIM_3,0xFFFEC704,__WRITE);                         /* MPU Timer 3 Load Timer Register, ResetValue = undef */
__IO_REG32(MPU_READ_TIM_3,0xFFFEC708,__READ);                          /* MPU Timer 3 Read Timer Register, ResetValue = undef */

/***************************************************************************
 **
 **  MPU Watchdog Timer Registers 
 **
***************************************************************************/
__IO_REG32(MPU_CNTL_TIMER_WD,0xFFFEC800,__READ_WRITE);                 /* MPU WDT Control Timer Register, ResetValue = 0002h */
__IO_REG32(MPU_LOAD_TIM_WD,0xFFFEC804,__WRITE);                        /* MPU WDT Load Timer Register, ResetValue = FFFFh */
__IO_REG32(MPU_READ_TIM_WD,0xFFFEC808,__READ);                         /* MPU WDT Read Timer Register, ResetValue = FFFFh */
__IO_REG32(MPU_TIMER_MODE_WD,0xFFFEC80C,__READ_WRITE);                 /* MPU WDT Timer Mode Register, ResetValue = 8000h */

/***************************************************************************
 **
 **  MPU Level 1 Interrupt Handler Registers 
 **
***************************************************************************/
__IO_REG32(MPU_L1_ITR,0xFFFECB00,__READ_WRITE);                        /* Interrupt Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_MIR,0xFFFECB04,__READ_WRITE);                        /* Mask Interrupt Register, ResetValue = FFFFFFFFh */
__IO_REG32(MPU_L1_SIR_IRQ_CODE,0xFFFECB10,__READ);                     /* IRQ Interrupt Encoded Source Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_SIR_FIQ_CODE,0xFFFECB14,__READ);                     /* FIQ Interrupt Encoded Source Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_CONTROL_REG,0xFFFECB18,__READ_WRITE);                /* Interrupt Control Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR0,0xFFFECB1C,__READ_WRITE);                       /* Interrupt 0 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR1,0xFFFECB20,__READ_WRITE);                       /* Interrupt 1 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR2,0xFFFECB24,__READ_WRITE);                       /* Interrupt 2 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR3,0xFFFECB28,__READ_WRITE);                       /* Interrupt 3 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR4,0xFFFECB2C,__READ_WRITE);                       /* Interrupt 4 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR5,0xFFFECB30,__READ_WRITE);                       /* Interrupt 5 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR6,0xFFFECB34,__READ_WRITE);                       /* Interrupt 6 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR7,0xFFFECB38,__READ_WRITE);                       /* Interrupt 7 Priority Level Register, ResetValue = 00000000h */
__IO_REG8(MPU_L1_ILR8,0xFFFECB3C,__READ_WRITE);                        /* Interrupt Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR9,0xFFFECB40,__READ_WRITE);                       /* Interrupt 9 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR10,0xFFFECB44,__READ_WRITE);                      /* Interrupt 10 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR11,0xFFFECB48,__READ_WRITE);                      /* Interrupt 11 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR12,0xFFFECB4C,__READ_WRITE);                      /* Interrupt 12 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR13,0xFFFECB50,__READ_WRITE);                      /* Interrupt 13 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR14,0xFFFECB54,__READ_WRITE);                      /* Interrupt 14 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR15,0xFFFECB58,__READ_WRITE);                      /* Interrupt 15 Priority Level Register, ResetValue = 00000000h */
__IO_REG16(MPU_L1_ILR16,0xFFFECB5C,__READ_WRITE);                      /* Interrupt Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR17,0xFFFECB60,__READ_WRITE);                      /* Interrupt 17 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR18,0xFFFECB64,__READ_WRITE);                      /* Interrupt 18 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR19,0xFFFECB68,__READ_WRITE);                      /* Interrupt 19 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR20,0xFFFECB6C,__READ_WRITE);                      /* Interrupt 20 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR21,0xFFFECB70,__READ_WRITE);                      /* Interrupt 21 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR22,0xFFFECB74,__READ_WRITE);                      /* Interrupt 22 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR23,0xFFFECB78,__READ_WRITE);                      /* Interrupt 23 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR24,0xFFFECB7C,__READ_WRITE);                      /* Interrupt 24 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR25,0xFFFECB80,__READ_WRITE);                      /* Interrupt 25 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR26,0xFFFECB84,__READ_WRITE);                      /* Interrupt 26 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR27,0xFFFECB88,__READ_WRITE);                      /* Interrupt 27 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR28,0xFFFECB8C,__READ_WRITE);                      /* Interrupt 28 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR29,0xFFFECB90,__READ_WRITE);                      /* Interrupt 29 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR30,0xFFFECB94,__READ_WRITE);                      /* Interrupt 30 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ILR31,0xFFFECB98,__READ_WRITE);                      /* Interrupt 31 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L1_ISR,0xFFFECB9C,__READ_WRITE);                        /* Software Interrupt Set Register, ResetValue = 00000000h */

/***************************************************************************
 **
 **  MPU Level 2 Interrupt Handler Registers 
 **
***************************************************************************/
__IO_REG32(MPU_L2_ITR,0xFFFE0000,__READ_WRITE);                        /* Interrupt Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_MIR,0xFFFE0004,__READ_WRITE);                        /* Mask Interrupt Register, ResetValue = FFFFFFFFh */
__IO_REG32(MPU_L2_SIR_IRQ_CODE,0xFFFE0010,__READ);                     /* IRQ Interrupt Encoded Source Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_SIR_FIQ_CODE,0xFFFE0014,__READ);                     /* FIQ Interrupt Encoded Source Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_CONTROL_REG,0xFFFE0018,__READ_WRITE);                /* Interrupt Control Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR0,0xFFFE001C,__READ_WRITE);                       /* Interrupt 0 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR1,0xFFFE0020,__READ_WRITE);                       /* Interrupt 1 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR2,0xFFFE0024,__READ_WRITE);                       /* Interrupt 2 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR3,0xFFFE0028,__READ_WRITE);                       /* Interrupt 3 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR4,0xFFFE002C,__READ_WRITE);                       /* Interrupt 4 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR5,0xFFFE0030,__READ_WRITE);                       /* Interrupt 5 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR6,0xFFFE0034,__READ_WRITE);                       /* Interrupt 6 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR7,0xFFFE0038,__READ_WRITE);                       /* Interrupt 7 Priority Level Register, ResetValue = 00000000h */
__IO_REG8(MPU_L2_ILR8,0xFFFE003C,__READ_WRITE);                        /* Interrupt Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR9,0xFFFE0040,__READ_WRITE);                       /* Interrupt 9 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR10,0xFFFE0044,__READ_WRITE);                      /* Interrupt 10 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR11,0xFFFE0048,__READ_WRITE);                      /* Interrupt 11 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR12,0xFFFE004C,__READ_WRITE);                      /* Interrupt 12 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR13,0xFFFE0050,__READ_WRITE);                      /* Interrupt 13 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR14,0xFFFE0054,__READ_WRITE);                      /* Interrupt 14 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR15,0xFFFE0058,__READ_WRITE);                      /* Interrupt 15 Priority Level Register, ResetValue = 00000000h */
__IO_REG16(MPU_L2_ILR16,0xFFFE005C,__READ_WRITE);                      /* Interrupt Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR17,0xFFFE0060,__READ_WRITE);                      /* Interrupt 17 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR18,0xFFFE0064,__READ_WRITE);                      /* Interrupt 18 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR19,0xFFFE0068,__READ_WRITE);                      /* Interrupt 19 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR20,0xFFFE006C,__READ_WRITE);                      /* Interrupt 20 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR21,0xFFFE0070,__READ_WRITE);                      /* Interrupt 21 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR22,0xFFFE0074,__READ_WRITE);                      /* Interrupt 22 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR23,0xFFFE0078,__READ_WRITE);                      /* Interrupt 23 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR24,0xFFFE007C,__READ_WRITE);                      /* Interrupt 24 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR25,0xFFFE0080,__READ_WRITE);                      /* Interrupt 25 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR26,0xFFFE0084,__READ_WRITE);                      /* Interrupt 26 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR27,0xFFFE0088,__READ_WRITE);                      /* Interrupt 27 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR28,0xFFFE008C,__READ_WRITE);                      /* Interrupt 28 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR29,0xFFFE0090,__READ_WRITE);                      /* Interrupt 29 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR30,0xFFFE0094,__READ_WRITE);                      /* Interrupt 30 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ILR31,0xFFFE0098,__READ_WRITE);                      /* Interrupt 31 Priority Level Register, ResetValue = 00000000h */
__IO_REG32(MPU_L2_ISR,0xFFFE009C,__READ_WRITE);                        /* Software Interrupt Set Register, ResetValue = 00000000h */


/***************************************************************************
 **
 ** System DMA Controller Registers
 **
 ***************************************************************************/

__IO_REG16(SYS_DMA_CSDP_CH0,0xFFFED800,__READ_WRITE);                  /* Channel 0 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH0,0xFFFED802,__READ_WRITE);                   /* Channel 0 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH0,0xFFFED804,__READ_WRITE);                  /* Channel 0 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH0,0xFFFED806,__READ);                         /* Channel 0 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH0,0xFFFED808,__READ_WRITE);                /* Channel 0 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH0,0xFFFED80A,__READ_WRITE);                /* Channel 0 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH0,0xFFFED80C,__READ_WRITE);                /* Channel 0 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH0,0xFFFED80E,__READ_WRITE);                /* Channel 0 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH0,0xFFFED810,__READ_WRITE);                   /* Channel 0 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH0,0xFFFED812,__READ_WRITE);                   /* Channel 0 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH0,0xFFFED814,__READ_WRITE);                   /* Channel 0 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH0,0xFFFED816,__READ_WRITE);                   /* Channel 0 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH0,0xFFFED818,__READ_WRITE);                   /* Channel 0 Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CSDP_CH1,0xFFFED840,__READ_WRITE);                  /* Channel 1 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH1,0xFFFED842,__READ_WRITE);                   /* Channel 1 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH1,0xFFFED844,__READ_WRITE);                  /* Channel 1 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH1,0xFFFED846,__READ);                         /* Channel 1 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH1,0xFFFED848,__READ_WRITE);                /* Channel 1 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH1,0xFFFED84A,__READ_WRITE);                /* Channel 1 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH1,0xFFFED84C,__READ_WRITE);                /* Channel 1 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH1,0xFFFED84E,__READ_WRITE);                /* Channel 1 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH1,0xFFFED850,__READ_WRITE);                   /* Channel 1 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH1,0xFFFED852,__READ_WRITE);                   /* Channel 1 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH1,0xFFFED854,__READ_WRITE);                   /* Channel 1 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH1,0xFFFED856,__READ_WRITE);                   /* Channel 1 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH1,0xFFFED858,__READ_WRITE);                   /* Channel 1 Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CSDP_CH2,0xFFFED880,__READ_WRITE);                  /* Channel 2 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH2,0xFFFED882,__READ_WRITE);                   /* Channel 2 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH2,0xFFFED884,__READ_WRITE);                  /* Channel 2 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH2,0xFFFED886,__READ);                         /* Channel 2 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH2,0xFFFED888,__READ_WRITE);                /* Channel 2 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH2,0xFFFED88A,__READ_WRITE);                /* Channel 2 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH2,0xFFFED88C,__READ_WRITE);                /* Channel 2 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH2,0xFFFED88E,__READ_WRITE);                /* Channel 2 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH2,0xFFFED890,__READ_WRITE);                   /* Channel 2 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH2,0xFFFED892,__READ_WRITE);                   /* Channel 2 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH2,0xFFFED894,__READ_WRITE);                   /* Channel 2 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH2,0xFFFED896,__READ_WRITE);                   /* Channel 2 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH2,0xFFFED898,__READ_WRITE);                   /* Channel 2 Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CSDP_CH3,0xFFFED8C0,__READ_WRITE);                  /* Channel 3 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH3,0xFFFED8C2,__READ_WRITE);                   /* Channel 3 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH3,0xFFFED8C4,__READ_WRITE);                  /* Channel 3 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH3,0xFFFED8C6,__READ);                         /* Channel 3 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH3,0xFFFED8C8,__READ_WRITE);                /* Channel 3 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH3,0xFFFED8CA,__READ_WRITE);                /* Channel 3 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH3,0xFFFED8CC,__READ_WRITE);                /* Channel 3 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH3,0xFFFED8CE,__READ_WRITE);                /* Channel 3 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH3,0xFFFED8D0,__READ_WRITE);                   /* Channel 3 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH3,0xFFFED8D2,__READ_WRITE);                   /* Channel 3 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH3,0xFFFED8D4,__READ_WRITE);                   /* Channel 3 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH3,0xFFFED8D6,__READ_WRITE);                   /* Channel 3 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH3,0xFFFED8D8,__READ_WRITE);                   /* Channel 3 Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CSDP_CH4,0xFFFED900,__READ_WRITE);                  /* Channel 4 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH4,0xFFFED902,__READ_WRITE);                   /* Channel 4 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH4,0xFFFED904,__READ_WRITE);                  /* Channel 4 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH4,0xFFFED906,__READ);                         /* Channel 4 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH4,0xFFFED908,__READ_WRITE);                /* Channel 4 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH4,0xFFFED90A,__READ_WRITE);                /* Channel 4 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH4,0xFFFED90C,__READ_WRITE);                /* Channel 4 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH4,0xFFFED90E,__READ_WRITE);                /* Channel 4 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH4,0xFFFED910,__READ_WRITE);                   /* Channel 4 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH4,0xFFFED912,__READ_WRITE);                   /* Channel 4 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH4,0xFFFED914,__READ_WRITE);                   /* Channel 4 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH4,0xFFFED916,__READ_WRITE);                   /* Channel 4 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH4,0xFFFED918,__READ_WRITE);                   /* Channel 4 Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CSDP_CH5,0xFFFED940,__READ_WRITE);                  /* Channel 5 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH5,0xFFFED942,__READ_WRITE);                   /* Channel 5 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH5,0xFFFED944,__READ_WRITE);                  /* Channel 5 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH5,0xFFFED946,__READ);                         /* Channel 5 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH5,0xFFFED948,__READ_WRITE);                /* Channel 5 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH5,0xFFFED94A,__READ_WRITE);                /* Channel 5 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH5,0xFFFED94C,__READ_WRITE);                /* Channel 5 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH5,0xFFFED94E,__READ_WRITE);                /* Channel 5 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH5,0xFFFED950,__READ_WRITE);                   /* Channel 5 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH5,0xFFFED952,__READ_WRITE);                   /* Channel 5 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH5,0xFFFED954,__READ_WRITE);                   /* Channel 5 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH5,0xFFFED956,__READ_WRITE);                   /* Channel 5 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH5,0xFFFED958,__READ_WRITE);                   /* Channel 5 Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CSDP_CH6,0xFFFED980,__READ_WRITE);                  /* Channel 6 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH6,0xFFFED982,__READ_WRITE);                   /* Channel 6 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH6,0xFFFED984,__READ_WRITE);                  /* Channel 6 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH6,0xFFFED986,__READ);                         /* Channel 6 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH6,0xFFFED988,__READ_WRITE);                /* Channel 6 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH6,0xFFFED98A,__READ_WRITE);                /* Channel 6 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH6,0xFFFED98C,__READ_WRITE);                /* Channel 6 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH6,0xFFFED98E,__READ_WRITE);                /* Channel 6 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH6,0xFFFED990,__READ_WRITE);                   /* Channel 6 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH6,0xFFFED992,__READ_WRITE);                   /* Channel 6 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH6,0xFFFED994,__READ_WRITE);                   /* Channel 6 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH6,0xFFFED996,__READ_WRITE);                   /* Channel 6 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH6,0xFFFED998,__READ_WRITE);                   /* Channel 6 Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CSDP_CH7,0xFFFED9C0,__READ_WRITE);                  /* Channel 7 Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CCR_CH7,0xFFFED9C2,__READ_WRITE);                   /* Channel 7 Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CICR_CH7,0xFFFED9C4,__READ_WRITE);                  /* Channel 7 Interrupt Control Register, ResetValue = 0003h */
__IO_REG16(SYS_DMA_CSR_CH7,0xFFFED9C6,__READ);                         /* Channel 7 Status Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_CSSA_L_CH7,0xFFFED9C8,__READ_WRITE);                /* Channel 7 Source Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CSSA_U_CH7,0xFFFED9CA,__READ_WRITE);                /* Channel 7 Source Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CDSA_L_CH7,0xFFFED9CC,__READ_WRITE);                /* Channel 7 Destination Start Address Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_CDSA_U_CH7,0xFFFED9CE,__READ_WRITE);                /* Channel 7 Destination Start Address Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_CEN_CH7,0xFFFED9D0,__READ_WRITE);                   /* Channel 7 Element Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFN_CH7,0xFFFED9D2,__READ_WRITE);                   /* Channel 7 Frame Number Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CFI_CH7,0xFFFED9D4,__READ_WRITE);                   /* Channel 7 Frame Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CEI_CH7,0xFFFED9D6,__READ_WRITE);                   /* Channel 7 Element Index Register, ResetValue = undef */
__IO_REG16(SYS_DMA_CPC_CH7,0xFFFED9D8,__READ_WRITE);                   /* Channel 7 Progress Counter Register, ResetValue = undef */
__IO_REG8(SYS_DMA_CSDP_CH8,0xFFFEDA00,__READ_WRITE);                   /* Channel Source/Destination Parameters Register, ResetValue = 0000h */
__IO_REG8(SYS_DMA_CCR_CH8,0xFFFEDA02,__READ_WRITE);                    /* Channel Control Register, ResetValue = 0000h */
__IO_REG8(SYS_DMA_CICR_CH8,0xFFFEDA04,__READ_WRITE);                   /* Channel Interrupt Control Register, ResetValue = 0003h */
__IO_REG8(SYS_DMA_CSR_CH8,0xFFFEDA06,__READ);                          /* Channel Status Register, ResetValue = 0000h */
__IO_REG8(SYS_DMA_CSSA_L_CH8,0xFFFEDA08,__READ_WRITE);                 /* Channel Source Start Address Register, ResetValue = LSBundef */
__IO_REG8(SYS_DMA_CSSA_U_CH8,0xFFFEDA0A,__READ_WRITE);                 /* Channel Source Start Address Register, ResetValue = MSBundef */
__IO_REG8(SYS_DMA_CDSA_L_CH8,0xFFFEDA0C,__READ_WRITE);                 /* Channel Destination Start Address Register, ResetValue = LSBundef */
__IO_REG8(SYS_DMA_CDSA_U_CH8,0xFFFEDA0E,__READ_WRITE);                 /* Channel Destination Start Address Register, ResetValue = MSBundef */
__IO_REG8(SYS_DMA_CEN_CH8,0xFFFEDA10,__READ_WRITE);                    /* Channel Element Number Register, ResetValue = undef */
__IO_REG8(SYS_DMA_CFN_CH8,0xFFFEDA12,__READ_WRITE);                    /* Channel Frame Number Register, ResetValue = undef */
__IO_REG8(SYS_DMA_CFI_CH8,0xFFFEDA14,__READ_WRITE);                    /* Channel Frame Index Register, ResetValue = undef */
__IO_REG8(SYS_DMA_CEI_CH8,0xFFFEDA16,__READ_WRITE);                    /* Channel Element Index Register, ResetValue = undef */
__IO_REG8(SYS_DMA_CPC_CH8,0xFFFEDA18,__READ_WRITE);                    /* Channel Progress Counter Register, ResetValue = undef */
__IO_REG16(SYS_DMA_LCD_CTRL,0xFFFEDB00,__READ_WRITE);                  /* LCD Channel Control Register, ResetValue = 0000h */
__IO_REG16(SYS_DMA_LCD_TOP_F1_L,0xFFFEDB02,__READ_WRITE);              /* LCD Channel Top Address Frame Buffer 1 Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_LCD_TOP_F1_U,0xFFFEDB04,__READ_WRITE);              /* LCD Channel Top Address Frame Buffer 1 Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_LCD_BOT_F1_L,0xFFFEDB06,__READ_WRITE);              /* LCD Channel Bottom Address Frame Buffer 1 Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_LCD_BOT_F1_U,0xFFFEDB08,__READ_WRITE);              /* LCD Channel Bottom Address Frame Buffer 1 Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_LCD_TOP_F2_L,0xFFFEDB0A,__READ_WRITE);              /* LCD Channel Top Address Frame Buffer 2 Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_LCD_TOP_F2_U,0xFFFEDB0C,__READ_WRITE);              /* LCD Channel Top Address Frame Buffer 2 Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_LCD_BOT_F2_L,0xFFFEDB0E,__READ_WRITE);              /* LCD Channel Bottom Address Frame Buffer 2 Register, ResetValue = LSBundef */
__IO_REG16(SYS_DMA_LCD_BOT_F2_U,0xFFFEDB10,__READ_WRITE);              /* LCD Channel Bottom Address Frame Buffer 2 Register, ResetValue = MSBundef */
__IO_REG16(SYS_DMA_GCR,0xFFFEDC00,__READ_WRITE);                       /* DMA Global Control Register, ResetValue = 0008h */


/***************************************************************************
 **
 ** LCD Controller Registers
 **
 ***************************************************************************/

__IO_REG32(LCD_CONTROL,0xFFFEC000,__READ_WRITE);                       /* LCD Control Register, ResetValue = 0x00000000 */
__IO_REG32(LCD_TIMING0,0xFFFEC004,__READ_WRITE);                       /* LCD Timing 0 Register, ResetValue = undef */
__IO_REG32(LCD_TIMING1,0xFFFEC008,__READ_WRITE);                       /* LCD Timing 1 Register, ResetValue = 0x00000000 */
__IO_REG32(LCD_TIMING2,0xFFFEC00C,__READ_WRITE);                       /* LCD Timing 2 Register, ResetValue = 0x00000000 */
__IO_REG32(LCD_STATUS,0xFFFEC010,__READ_WRITE);                        /* LCD Status Register, ResetValue = 0x00000000 */
__IO_REG32(LCD_SUBPANEL,0xFFFEC014,__READ_WRITE);                      /* LCD Subpanel Display Register, ResetValue = 0x00000000 */


/* MPU Public Peripheral Registers */


/***************************************************************************
 **
 **  McBSP2 Registers 
 **
***************************************************************************/
__IO_REG16(MCBSP2_DRR2,0xFFFB1000,__READ_WRITE);                       /* McBSP2 Data receive register 2 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_DRR1,0xFFFB1002,__READ_WRITE);                       /* McBSP2 Data receive register 1 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_DXR2,0xFFFB1004,__READ_WRITE);                       /* McBSP2 Data transmit register 2 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_DXR1,0xFFFB1006,__READ_WRITE);                       /* McBSP2 Data transmit register 1 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_SPCR2,0xFFFB1008,__READ_WRITE);                      /* McBSP2 Serial port control register 2 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_SPCR1,0xFFFB100A,__READ_WRITE);                      /* McBSP2 Serial port control register 1 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCR2,0xFFFB100C,__READ_WRITE);                       /* McBSP2 Receive control register 2 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCR1,0xFFFB100E,__READ_WRITE);                       /* McBSP2 Receive control register 1 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCR2,0xFFFB1010,__READ_WRITE);                       /* McBSP2 Transmit control register 2 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCR1,0xFFFB1012,__READ_WRITE);                       /* McBSP2 Transmit control register 1 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_SRGR2,0xFFFB1014,__READ_WRITE);                      /* McBSP2 Sample rate generator register 2 2000h Register, ResetValue =  */
__IO_REG16(MCBSP2_SRGR1,0xFFFB1016,__READ_WRITE);                      /* McBSP2 Sample rate generator register 1 0001h Register, ResetValue =  */
__IO_REG16(MCBSP2_MCR2,0xFFFB1018,__READ_WRITE);                       /* McBSP2 Multichannel register 2 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_MCR1,0xFFFB101A,__READ_WRITE);                       /* McBSP2 Multichannel register 1 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERA,0xFFFB101C,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition A 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERB,0xFFFB101E,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition B 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERA,0xFFFB1020,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition A 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERB,0xFFFB1022,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition B 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_PCR0,0xFFFB1024,__READ_WRITE);                       /* McBSP2 Pin control register 0 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERC,0xFFFB1026,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition C 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERD,0xFFFB1028,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition D 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERC,0xFFFB102A,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition C 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERD,0xFFFB102C,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition D 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERE,0xFFFB102E,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition E 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERF,0xFFFB1030,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition F 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERE,0xFFFB1032,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition E 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERF,0xFFFB1034,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition F 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERG,0xFFFB1036,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition G 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_RCERH,0xFFFB1038,__READ_WRITE);                      /* McBSP2 Receive channel enable register partition H 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERG,0xFFFB103A,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition G 0000h Register, ResetValue =  */
__IO_REG16(MCBSP2_XCERH,0xFFFB103C,__READ_WRITE);                      /* McBSP2 Transmit channel enable register partition H 0000h Register, ResetValue =  */

/***************************************************************************
 **
 **  Microwire Registers 
 **
***************************************************************************/
__IO_REG16(MCWR_TD,0xFFFB3000,__READ_WRITE);                                /* Microwire Transmit Data Register, ResetValue = undef */
#define MCWR_RD MCWR_TD                                                /* Microwire Receive Data Register, ResetValue = undef */
__IO_REG16(MCWR_CSR,0xFFFB3004,__READ_WRITE);                          /* Microwire Control and Status Register, ResetValue = undef */
__IO_REG16(MCWR_SR1,0xFFFB3008,__READ_WRITE);                          /* Microwire Setup Register, ResetValue = 1undef */
__IO_REG16(MCWR_SR2,0xFFFB300C,__READ_WRITE);                          /* Microwire Setup Register, ResetValue = 2undef */
__IO_REG16(MCWR_SR3,0xFFFB3010,__READ_WRITE);                          /* Microwire Setup Register, ResetValue = 30000h */
__IO_REG16(MCWR_SR4,0xFFFB3014,__READ_WRITE);                          /* Microwire Setup Register, ResetValue = 40000h */
__IO_REG16(MCWR_SR5,0xFFFB3018,__READ_WRITE);                          /* Microwire Setup Register, ResetValue = 50000h */

/***************************************************************************
 **
 **  I 2 C Registers 
 **
***************************************************************************/
__IO_REG16(I2C_REV,0xFFFB3800,__READ_WRITE);                           /* I 2 C Module Version Register, ResetValue = 0011h */
__IO_REG16(I2C_IE,0xFFFB3804,__READ_WRITE);                            /* I 2 C Interrupt Enable Register, ResetValue = 0000h */
__IO_REG16(I2C_STAT,0xFFFB3808,__READ);                                /* I 2 C Status Register, ResetValue = 0000h */
__IO_REG16(I2C_IV,0xFFFB380C,__READ);                                  /* I 2 C Interrupt Vector Register, ResetValue = 0000h */
__IO_REG16(I2C_BUF,0xFFFB3814,__READ_WRITE);                           /* I 2 C Buffer Configuration Register, ResetValue = 0000h */
__IO_REG16(I2C_CNT,0xFFFB3818,__READ_WRITE);                           /* I 2 C Data Counter Register, ResetValue = 0000h */
__IO_REG16(I2C_DATA,0xFFFB381C,__READ_WRITE);                          /* I 2 C Data Access Register, ResetValue = 0000h */
__IO_REG16(I2C_CON,0xFFFB3824,__READ_WRITE);                           /* I 2 C Configuration Register, ResetValue = 0000h */
__IO_REG16(I2C_OA,0xFFFB3828,__READ_WRITE);                            /* I 2 C Own Address Register, ResetValue = 0000h */
__IO_REG16(I2C_SA,0xFFFB382C,__READ_WRITE);                            /* I 2 C Slave Address Register, ResetValue = 03FFh */
__IO_REG16(I2C_PSC,0xFFFB3830,__READ_WRITE);                           /* I 2 C Clock Prescaler Register, ResetValue = 0000h */
__IO_REG16(I2C_SCLL,0xFFFB3834,__READ_WRITE);                          /* I 2 C SCL Low Timer Register, ResetValue = 0000h */
__IO_REG16(I2C_SCLH,0xFFFB3838,__READ_WRITE);                          /* I 2 C SCL High Timer Register, ResetValue = 0000h */
__IO_REG16(I2C_SYSTEST,0xFFFB383C,__READ_WRITE);                       /* I 2 C System Test Register, ResetValue = 0000h */

/***************************************************************************
 **
 **  HDQ/1-Wire Interface Registers 
 **
***************************************************************************/
__IO_REG8(HDQ1W_TXR,0xFFFBC000,__READ_WRITE);                          /* TX Write Data Register, ResetValue = 00h */
__IO_REG8(HDQ1W_RXR,0xFFFBC004,__READ);                                /* RX Receive Buffer Register, ResetValue = undef */
__IO_REG8(HDQ1W_CSR,0xFFFBC008,__READ_WRITE);                          /* Control and Status Register, ResetValue = 00h */
__IO_REG8(HDQ1W_ISR,0xFFFBC00C,__READ_WRITE);                          /* Interrupt Status Register, ResetValue = 00h */

/***************************************************************************
 **
 **  MMC/SD Registers 
 **
***************************************************************************/
__IO_REG16(MMC_CMD,0xFFFB7800,__READ_WRITE);                           /* MMC command 0000h Register, ResetValue =  */
__IO_REG16(MMC_ARGL,0xFFFB7804,__READ_WRITE);                          /* MMC argument low 0000h Register, ResetValue =  */
__IO_REG16(MMC_ARGH,0xFFFB7808,__READ_WRITE);                          /* MMC argument high 0000h Register, ResetValue =  */
__IO_REG16(MMC_CON,0xFFFB780C,__READ_WRITE);                           /* MMC system configuration 0000h Register, ResetValue =  */
__IO_REG16(MMC_STAT,0xFFFB7810,__READ_WRITE);                          /* MMC status 0000h Register, ResetValue =  */
__IO_REG16(MMC_IE,0xFFFB7814,__READ_WRITE);                            /* MMC system interrupt enable 0000h Register, ResetValue =  */
__IO_REG16(MMC_CTO,0xFFFB7818,__READ_WRITE);                           /* MMC command timeout 0000h Register, ResetValue =  */
__IO_REG16(MMC_DTO,0xFFFB781C,__READ_WRITE);                           /* MMC data timeout 0000h Register, ResetValue =  */
__IO_REG16(MMC_DATA,0xFFFB7820,__READ_WRITE);                          /* MMC TX/RX FIFO data 0000h Register, ResetValue =  */
__IO_REG16(MMC_BLEN,0xFFFB7824,__READ_WRITE);                          /* MMC block length 0000h Register, ResetValue =  */
__IO_REG16(MMC_NBLK,0xFFFB7828,__READ_WRITE);                          /* MMC number of blocks 0000h Register, ResetValue =  */
__IO_REG16(MMC_BUF,0xFFFB782C,__READ_WRITE);                           /* MMC buffer configuration 1F00h Register, ResetValue =  */
__IO_REG16(MMC_SPI,0xFFFB7830,__READ_WRITE);                           /* MMC serial port interface 0000h Register, ResetValue =  */
__IO_REG16(MMC_SDIO,0xFFFB7834,__READ_WRITE);                          /* MMC SDIO mode configuration 0000h Register, ResetValue =  */
__IO_REG16(MMC_SYST,0xFFFB7838,__READ_WRITE);                          /* MMC system test 2000h Register, ResetValue =  */
__IO_REG16(MMC_REV,0xFFFB783C,__READ);                                 /* MMC module version . Register, ResetValue =  */
__IO_REG16(MMC_RSP0,0xFFFB7840,__READ);                                /* MMC command response 0 undef Register, ResetValue =  */
__IO_REG16(MMC_RSP1,0xFFFB7844,__READ);                                /* MMC command response 1 undef Register, ResetValue =  */
__IO_REG16(MMC_RSP2,0xFFFB7848,__READ);                                /* MMC command response 2 undef Register, ResetValue =  */
__IO_REG16(MMC_RSP3,0xFFFB784C,__READ);                                /* MMC command response 3 undef Register, ResetValue =  */
__IO_REG16(MMC_RSP4,0xFFFB7850,__READ);                                /* MMC command response 4 undef Register, ResetValue =  */
__IO_REG16(MMC_RSP5,0xFFFB7854,__READ);                                /* MMC command response 5 undef Register, ResetValue =  */
__IO_REG16(MMC_RSP6,0xFFFB7858,__READ);                                /* MMC command response 6 undef Register, ResetValue =  */
__IO_REG16(MMC_RSP7,0xFFFB785C,__READ);                                /* MMC command response 7 undef Register, ResetValue =  */

/***************************************************************************
 **
 **  USB Function Registers 
 **
***************************************************************************/
__IO_REG16(USB_REV,0xFFFB4000,__READ);                                 /* Revision Register, ResetValue = . */
__IO_REG16(USB_EP_NUM,0xFFFB4004,__READ_WRITE);                        /* Endpoint Selection Register, ResetValue = 0000h */
__IO_REG16(USB_DATA,0xFFFB4008,__READ_WRITE);                          /* Data Register, ResetValue = undef */
__IO_REG16(USB_CTRL,0xFFFB400C,__READ_WRITE);                          /* Control Register, ResetValue = 0000h */
__IO_REG16(USB_STAT_FLG,0xFFFB4010,__READ);                            /* Status Flag Register, ResetValue = 0202h */
__IO_REG16(USB_RXFSTAT,0xFFFB4014,__READ);                             /* Receive FIFO Status Register, ResetValue = 0000h */
__IO_REG16(USB_SYSCON1,0xFFFB4018,__READ_WRITE);                       /* System Configuration 1 Register, ResetValue = 0000h */
__IO_REG16(USB_SYSCON2,0xFFFB401C,__READ_WRITE);                       /* System Configuration 2 Register, ResetValue = 0000h */
__IO_REG16(USB_DEVSTAT,0xFFFB4020,__READ);                             /* Device Status Register, ResetValue = undef */
__IO_REG16(USB_SOF,0xFFFB4024,__READ);                                 /* Start of Frame Register, ResetValue = 0000h */
__IO_REG16(USB_IRQ_EN,0xFFFB4028,__READ_WRITE);                        /* Interrupt Enable Register, ResetValue = undef */
__IO_REG16(USB_DMA_IRQ_EN,0xFFFB402C,__READ_WRITE);                    /* DMA Interrupt Enable Register, ResetValue = undef */
__IO_REG16(USB_IRQ_SRC,0xFFFB4030,__READ_WRITE);                       /* Interrupt Source Register, ResetValue = 0000h */
__IO_REG16(USB_EPN_STAT,0xFFFB4034,__READ);                            /* Endpoint Interrupt Status Register, ResetValue = 0000h */
__IO_REG16(USB_DMAN_STAT,0xFFFB4038,__READ);                           /* DMA Endpoint Interrupt Status Register, ResetValue = 0000h */
__IO_REG16(USB_RXDMA_CFG,0xFFFB4040,__READ_WRITE);                     /* Receive Channels DMA Configuration Register, ResetValue = 0000h */
__IO_REG16(USB_TXDMA_CFG,0xFFFB4044,__READ_WRITE);                     /* Transmit Channels DMA Configuration Register, ResetValue = 0000h */
__IO_REG16(USB_DATA_DMA,0xFFFB4048,__READ_WRITE);                      /* DMA FIFO Data Register, ResetValue = undef */
__IO_REG16(USB_TXDMA0,0xFFFB4050,__READ_WRITE);                        /* Transmit DMA Control 0 Register, ResetValue = 0000h */
__IO_REG16(USB_TXDMA1,0xFFFB4054,__READ_WRITE);                        /* Transmit DMA Control 1 Register, ResetValue = 0000h */
__IO_REG16(USB_TXDMA2,0xFFFB4058,__READ_WRITE);                        /* Transmit DMA Control 2 Register, ResetValue = 0000h */
__IO_REG16(USB_RXDMA0,0xFFFB4060,__READ_WRITE);                        /* Receive DMA Control 0 Register, ResetValue = 0000h */
__IO_REG16(USB_RXDMA1,0xFFFB4064,__READ_WRITE);                        /* Receive DMA Control 1 Register, ResetValue = 0000h */
__IO_REG16(USB_RXDMA2,0xFFFB4068,__READ_WRITE);                        /* Receive DMA Control 2 Register, ResetValue = 0000h */
__IO_REG16(USB_EP0,0xFFFB4080,__READ_WRITE);                           /* Endpoint Configuration 0 Register, ResetValue = 0000h */
__IO_REG16(USB_EP1_RX,0xFFFB4084,__READ_WRITE);                        /* Receive Endpoint Configuration 1 Register, ResetValue = undef */
__IO_REG16(USB_EP2_RX,0xFFFB4088,__READ_WRITE);                        /* Receive Endpoint Configuration 2 Register, ResetValue = undef */
__IO_REG16(USB_EP3_RX,0xFFFB408C,__READ_WRITE);                        /* Receive Endpoint Configuration 3 Register, ResetValue = undef */
__IO_REG16(USB_EP4_RX,0xFFFB4090,__READ_WRITE);                        /* Receive Endpoint Configuration 4 Register, ResetValue = undef */
__IO_REG16(USB_EP5_RX,0xFFFB4094,__READ_WRITE);                        /* Receive Endpoint Configuration 5 Register, ResetValue = undef */
__IO_REG16(USB_EP6_RX,0xFFFB4098,__READ_WRITE);                        /* Receive Endpoint Configuration 6 Register, ResetValue = undef */
__IO_REG16(USB_EP7_RX,0xFFFB409C,__READ_WRITE);                        /* Receive Endpoint Configuration 7 Register, ResetValue = undef */
__IO_REG8(USB_EP8_RX,0xFFFB40A0,__READ_WRITE);                         /* Receive Endpoint Configuration Register, ResetValue = undef */
__IO_REG16(USB_EP9_RX,0xFFFB40A4,__READ_WRITE);                        /* Receive Endpoint Configuration 9 Register, ResetValue = undef */
__IO_REG16(USB_EP10_RX,0xFFFB40A8,__READ_WRITE);                       /* Receive Endpoint Configuration 10 Register, ResetValue = undef */
__IO_REG16(USB_EP11_RX,0xFFFB40AC,__READ_WRITE);                       /* Receive Endpoint Configuration 11 Register, ResetValue = undef */
__IO_REG16(USB_EP12_RX,0xFFFB40B0,__READ_WRITE);                       /* Receive Endpoint Configuration 12 Register, ResetValue = undef */
__IO_REG16(USB_EP13_RX,0xFFFB40B4,__READ_WRITE);                       /* Receive Endpoint Configuration 13 Register, ResetValue = undef */
__IO_REG16(USB_EP14_RX,0xFFFB40B8,__READ_WRITE);                       /* Receive Endpoint Configuration 14 Register, ResetValue = undef */
__IO_REG16(USB_EP15_RX,0xFFFB40BC,__READ_WRITE);                       /* Receive Endpoint Configuration 15 Register, ResetValue = undef */
__IO_REG16(USB_EP1_TX,0xFFFB40C4,__READ_WRITE);                        /* Transmit Endpoint Configuration 1 Register, ResetValue = undef */
__IO_REG16(USB_EP2_TX,0xFFFB40C8,__READ_WRITE);                        /* Transmit Endpoint Configuration 2 Register, ResetValue = undef */
__IO_REG16(USB_EP3_TX,0xFFFB40CC,__READ_WRITE);                        /* Transmit Endpoint Configuration 3 Register, ResetValue = undef */
__IO_REG16(USB_EP4_TX,0xFFFB40D0,__READ_WRITE);                        /* Transmit Endpoint Configuration 4 Register, ResetValue = undef */
__IO_REG16(USB_EP5_TX,0xFFFB40D4,__READ_WRITE);                        /* Transmit Endpoint Configuration 5 Register, ResetValue = undef */
__IO_REG16(USB_EP6_TX,0xFFFB40D8,__READ_WRITE);                        /* Transmit Endpoint Configuration 6 Register, ResetValue = undef */
__IO_REG16(USB_EP7_TX,0xFFFB40DC,__READ_WRITE);                        /* Transmit Endpoint Configuration 7 Register, ResetValue = undef */
__IO_REG8(USB_EP8_TX,0xFFFB40E0,__READ_WRITE);                         /* Transmit Endpoint Configuration Register, ResetValue = undef */
__IO_REG16(USB_EP9_TX,0xFFFB40E4,__READ_WRITE);                        /* Transmit Endpoint Configuration 9 Register, ResetValue = undef */
__IO_REG16(USB_EP10_TX,0xFFFB40E8,__READ_WRITE);                       /* Transmit Endpoint Configuration 10 Register, ResetValue = undef */
__IO_REG16(USB_EP11_TX,0xFFFB40EC,__READ_WRITE);                       /* Transmit Endpoint Configuration 11 Register, ResetValue = undef */
__IO_REG16(USB_EP12_TX,0xFFFB40F0,__READ_WRITE);                       /* Transmit Endpoint Configuration 12 Register, ResetValue = undef */
__IO_REG16(USB_EP13_TX,0xFFFB40F4,__READ_WRITE);                       /* Transmit Endpoint Configuration 13 Register, ResetValue = undef */
__IO_REG16(USB_EP14_TX,0xFFFB40F8,__READ_WRITE);                       /* Transmit Endpoint Configuration 14 Register, ResetValue = undef */
__IO_REG16(USB_EP15_TX,0xFFFB40FC,__READ_WRITE);                       /* Transmit Endpoint Configuration 15 Register, ResetValue = undef */

/***************************************************************************
 **
 **  USB Host Controller Registers 
 **
***************************************************************************/
__IO_REG32(USB_HcRevision,0xFFFBA000,__READ);                          /* OHCI Revision Register, ResetValue = 00000010h */
__IO_REG32(USB_HcControl,0xFFFBA004,__READ_WRITE);                     /* Host Controller Operating Mode Register, ResetValue = 00000000h */
__IO_REG32(USB_HcCommandStatus,0xFFFBA008,__READ_WRITE);               /* Host Controller Command and Status Register, ResetValue = 00000000h */
__IO_REG32(USB_HcInterruptStatus,0xFFFBA00C,__READ_WRITE);             /* Host Controller Interrupt Status Register, ResetValue = 00000000h */
__IO_REG32(USB_HcInterruptEnable,0xFFFBA010,__READ_WRITE);             /* Host Controller Interrupt Enable Register, ResetValue = 00000000h */
__IO_REG32(USB_HcInterruptDisable,0xFFFBA014,__READ);                  /* Host Controller Interrupt Disable Register, ResetValue = 00000000h */
__IO_REG32(USB_HcHCCA,0xFFFBA018,__READ_WRITE);                        /* LB Virtual Address HCCA Register, ResetValue = 00000000h */
__IO_REG32(USB_HcPeriodCurrentED,0xFFFBA01C,__READ_WRITE);             /* LB Virtual Address Current Periodic EP Descriptor Register, ResetValue = 00000000h */
__IO_REG32(USB_HcControlHeadED,0xFFFBA020,__READ_WRITE);               /* LB Virtual Address Control EP Descriptor List Head Register, ResetValue = 00000000h */
__IO_REG32(USB_HcControlCurrentED,0xFFFBA024,__READ_WRITE);            /* LB Virtual Address Current Control EP Descriptor Register, ResetValue = 00000000h */
__IO_REG32(USB_HcBulkHeadED,0xFFFBA028,__READ_WRITE);                  /* LB Virtual Address Bulk EP Descriptor List Head Register, ResetValue = 00000000h */
__IO_REG32(USB_HcBulkCurrentED,0xFFFBA02C,__READ_WRITE);               /* LB Virtual Address Current Bulk EP Descriptor Register, ResetValue = 00000000h */
__IO_REG32(USB_HcDoneHead,0xFFFBA030,__READ);                          /* LB Virtual Address Retired Transfer Descriptor List Head Register, ResetValue = undef */
__IO_REG32(USB_HcFmInterval,0xFFFBA034,__READ_WRITE);                  /* Frame Interval Register, ResetValue = 00002EDFh */
__IO_REG32(USB_HcFmRemaining,0xFFFBA038,__READ);                       /* Remaining Frame Time Register, ResetValue = 00000000h */
__IO_REG32(USB_HcFmNumber,0xFFFBA03C,__READ);                          /* Remaining Frame Number Register, ResetValue = 00000000h */
__IO_REG32(USB_HcPeriodicStart,0xFFFBA040,__READ_WRITE);               /* Periodic Start Time Register, ResetValue = 00000000h */
__IO_REG32(USB_HcLSThreshold,0xFFFBA044,__READ_WRITE);                 /* Low Speed Start Threshold Register, ResetValue = 00000628h */
__IO_REG32(USB_HcRhDescriptorA,0xFFFBA048,__READ_WRITE);               /* USB Root Hub Descriptor Register, ResetValue = A0A001203h */
__IO_REG32(USB_HcRhDescriptorB,0xFFFBA04C,__READ_WRITE);               /* USB Root Hub Descriptor Register, ResetValue = B00000000h */
__IO_REG32(USB_HcRhStatus,0xFFFBA050,__READ_WRITE);                    /* USB Root Hub Status Register, ResetValue = 00000000h */
__IO_REG32(USB_HcRhPortStatus1,0xFFFBA054,__READ_WRITE);               /* Port 1 Control and Status Register, ResetValue = 00000100h */
__IO_REG32(USB_HcRhPortStatus2,0xFFFBA058,__READ_WRITE);               /* Port 2 Control and Status Register, ResetValue = 00000100h */
__IO_REG32(USB_HcRhPortStatus3,0xFFFBA05C,__READ_WRITE);               /* Port 3 Control and Status Register, ResetValue = 00000100h */
__IO_REG32(USB_HostUEAddr,0xFFFBA0E0,__READ);                          /* LB Virtual Address Last Unrecoverable Error Register, ResetValue = 00000000h */
__IO_REG32(USB_HostUEStatus,0xFFFBA0E4,__READ);                        /* LB Cycle Type Last Unrecoverable Error Register, ResetValue = 00000000h */
__IO_REG32(USB_HostTimeoutCtrl,0xFFFBA0E8,__READ_WRITE);               /* USB Host Mastered Local Bus Time-out Enable Register, ResetValue = 00000000h */
__IO_REG32(USB_HostRevision,0xFFFBA0EC,__READ);                        /* USB Host Controller Revision Register, ResetValue = . */

/***************************************************************************
 **
 **  Camera Interface Registers 
 **
***************************************************************************/
__IO_REG32(CI_CTRLCLOCK,0xFFFB6800,__READ_WRITE);                      /* Clock Control Register, ResetValue = 00000000h */
__IO_REG32(CI_IT_STATUS,0xFFFB6804,__READ);                            /* Interrupt Status Register, ResetValue = 00000000h */
__IO_REG32(CI_MODE,0xFFFB6808,__READ_WRITE);                           /* Mode Configuration Register, ResetValue = 00000200h */
__IO_REG32(CI_STATUS,0xFFFB680C,__READ);                               /* Status Register, ResetValue = 00000000h */
__IO_REG32(CI_CAMDATA,0xFFFB6810,__READ);                              /* Image Data Register, ResetValue = 00000000h */
__IO_REG32(CI_GPIO,0xFFFB6814,__READ_WRITE);                           /* GPIO Register, ResetValue = 00000000h */
__IO_REG32(CI_PEAK_COUNTER,0xFFFB6818,__READ_WRITE);                   /* Fifo Peak Counter Register, ResetValue = 00000000h */

/***************************************************************************
 **
 **  MPU I/O/Keyboard Registers 
 **
***************************************************************************/
__IO_REG16(INPUT_LATCH,0xFFFB5000,__READ);                             /* Input Register, ResetValue = undef */
__IO_REG16(OUTPUT_REG,0xFFFB5004,__READ_WRITE);                        /* Output Register, ResetValue = undef */
__IO_REG16(IO_CNTL,0xFFFB5008,__READ_WRITE);                           /* Input Output Control Register, ResetValue = FFFFh */
__IO_REG16(KBR_LATCH,0xFFFB5010,__READ);                               /* Keyboard Row Inputs Register, ResetValue = undef */
__IO_REG16(KBC_REG,0xFFFB5014,__READ_WRITE);                           /* Keyboard Column Outputs Register, ResetValue = 0000h */
__IO_REG16(GPIO_EVENT_MODE,0xFFFB5018,__READ_WRITE);                   /* GPIO Event Mode Register, ResetValue = 0000h */
__IO_REG16(GPIO_INT_EDGE,0xFFFB501C,__READ_WRITE);                     /* GPIO Interrupt Edge Register, ResetValue = 0000h */
__IO_REG16(KBD_INT,0xFFFB5020,__READ);                                 /* Keyboard Interrupt Register, ResetValue = 0000h */
__IO_REG16(GPIO_INT,0xFFFB5024,__READ);                                /* GPIO Interrupt Register, ResetValue = 0000h */
__IO_REG16(KBD_MASKIT,0xFFFB5028,__READ_WRITE);                        /* Keyboard Mask Interrupt Register, ResetValue = 0000h */
__IO_REG16(GPIO_MASKIT,0xFFFB502C,__READ_WRITE);                       /* GPIO Mask Interrupt Register, ResetValue = 0000h */
__IO_REG16(GPIO_DEBOUNCING,0xFFFB5030,__READ_WRITE);                   /* GPIO Debouncing Register, ResetValue = 0000h */
__IO_REG16(GPIO_LATCH,0xFFFB5034,__READ);                              /* GPIO Latch Register, ResetValue = 0000h */

/***************************************************************************
 **
 **  PWL Registers 
 **
***************************************************************************/
__IO_REG8(PWL_LEVEL,0xFFFB5800,__READ_WRITE);                          /* PWL Level Register, ResetValue = 0000h */
__IO_REG8(PWL_CTRL,0xFFFB5804,__READ_WRITE);                           /* PWL Control Register, ResetValue = 0000h */

/***************************************************************************
 **
 **  PWT Registers 
 **
***************************************************************************/
__IO_REG8(PWT_FRC,0xFFFB6000,__READ_WRITE);                            /* PWT Frequency Control Register, ResetValue = 0000h */
__IO_REG8(PWT_VCR,0xFFFB6004,__READ_WRITE);                            /* PWT Volume Control Register, ResetValue = 0000h */
__IO_REG8(PWT_GCR,0xFFFB6008,__READ_WRITE);                            /* PWT General Control Register, ResetValue = 0000h */

/***************************************************************************
 **
 **  LED Pulse Generator 1 Registers 
 **
***************************************************************************/
__IO_REG8(LCR_1,0xFFFBD000,__READ_WRITE);                              /* LPG1 Control Register, ResetValue = 00h */
__IO_REG8(PMR_1,0xFFFBD004,__READ_WRITE);                              /* LPG1 Power Management Register, ResetValue = 00h */

/***************************************************************************
 **
 **  LED Pulse Generator 2 Registers 
 **
***************************************************************************/
__IO_REG8(LCR_2,0xFFFBD800,__READ_WRITE);                              /* LPG2 Control Register, ResetValue = 00h */
__IO_REG8(PMR_2,0xFFFBD804,__READ_WRITE);                              /* LPG2 Power Management Register, ResetValue = 00h */

/***************************************************************************
 **
 **  32k Timer Registers 
 **
***************************************************************************/
__IO_REG32(TVR,0xFFFB9000,__READ_WRITE);                               /* Tick Value Register, ResetValue = 00FFFFFFh */
__IO_REG32(TCR,0xFFFB9004,__READ);                                     /* Tick Counter Register, ResetValue = 00FFFFFFh */
__IO_REG32(CR,0xFFFB9008,__READ_WRITE);                                /* Control Register, ResetValue = 00000008h */

/***************************************************************************
 **
 **  Real-Time Clock Registers 
 **
***************************************************************************/
__IO_REG8(SECONDS_REG,0xFFFB4800,__READ_WRITE);                        /* RTC Seconds Register, ResetValue = 00h */
__IO_REG8(MINUTES_REG,0xFFFB4804,__READ_WRITE);                        /* RTC Minutes Register, ResetValue = 00h */
__IO_REG8(HOURS_REG,0xFFFB4808,__READ_WRITE);                          /* RTC Hours Register, ResetValue = 00h */
__IO_REG8(DAYS_REG,0xFFFB480C,__READ_WRITE);                           /* RTC Days Register, ResetValue = 01h */
__IO_REG8(MONTHS_REG,0xFFFB4810,__READ_WRITE);                         /* RTC Months Register, ResetValue = 01h */
__IO_REG8(YEARS_REG,0xFFFB4814,__READ_WRITE);                          /* RTC Years Register, ResetValue = 00h */
__IO_REG8(WEEK_REG,0xFFFB4818,__READ_WRITE);                           /* RTC Weeks Register, ResetValue = 00h */
__IO_REG8(ALARM_SECOND_REG,0xFFFB4820,__READ_WRITE);                   /* RTC Alarm Seconds Register, ResetValue = 00h */
__IO_REG8(ALARM_MINUTES_REG,0xFFFB4824,__READ_WRITE);                  /* RTC Alarm Minutes Register, ResetValue = 00h */
__IO_REG8(ALARM_HOURS_REG,0xFFFB4828,__READ_WRITE);                    /* RTC Alarm Hours Register, ResetValue = 00h */
__IO_REG8(ALARM_DAYS_REG,0xFFFB482C,__READ_WRITE);                     /* RTC Alarm Days Register, ResetValue = 01h */
__IO_REG8(ALARM_MONTHS_REG,0xFFFB4830,__READ_WRITE);                   /* RTC Alarm Months Register, ResetValue = 01h */
__IO_REG8(ALARM_YEARS_REG,0xFFFB4834,__READ_WRITE);                    /* RTC Alarm Years Register, ResetValue = 00h */
__IO_REG8(RTC_CTRL_REG,0xFFFB4840,__READ_WRITE);                       /* RTC Control Register, ResetValue = 00h */
__IO_REG8(RTC_STATUS_REG,0xFFFB4844,__READ_WRITE);                     /* RTC Status Register, ResetValue = 00h */
__IO_REG8(RTC_INTERRUPTS_REG,0xFFFB4848,__READ_WRITE);                 /* RTC Interrupts Register, ResetValue = 00h */
__IO_REG8(RTC_COMP_LSB_REG,0xFFFB484C,__READ_WRITE);                   /* RTC Compensation LSB Register, ResetValue = 00h */
__IO_REG8(RTC_COMP_MSB_REG,0xFFFB4850,__READ_WRITE);                   /* RTC Compensation MSB Register, ResetValue = 00h */

/***************************************************************************
 **
 **  Frame Adjustment Counter Registers 
 **
***************************************************************************/
__IO_REG16(FARC,0xFFFBA800,__READ_WRITE);                              /* Frame Adjustment Reference Count Register, ResetValue = 0000h */
__IO_REG16(FSC,0xFFFBA804,__READ);                                     /* Frame Start Count Register, ResetValue = 0000h */
__IO_REG16(CTRL,0xFFFBA808,__READ_WRITE);                              /* Control and Configuration Register, ResetValue = 0000h */
__IO_REG16(STATUS,0xFFFBA80C,__READ);                                  /* Status Register, ResetValue = 0000h */
__IO_REG16(SYNC_CNT,0xFFFBA810,__READ);                                /* Frame Synchronization Register, ResetValue = undef */
__IO_REG16(START_CNT,0xFFFBA814,__READ);                               /* Frame Start Counter Register, ResetValue = undef */


/* MPU Configuration Registers */


/***************************************************************************
 **
 **  OMAP 5910 Pin Configuration Registers 
 **
***************************************************************************/
__IO_REG32(FUNC_MUX_CTRL_0,0xFFFE1000,__READ_WRITE);                   /* Functional Multiplexing Control 0 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_1,0xFFFE1004,__READ_WRITE);                   /* Functional Multiplexing Control 1 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_2,0xFFFE1008,__READ_WRITE);                   /* Functional Multiplexing Control 2 Register, ResetValue = 00000000h */
__IO_REG32(COMP_MODE_CTRL_0,0xFFFE100C,__READ_WRITE);                  /* Compatibility Mode Control 0 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_3,0xFFFE1010,__READ_WRITE);                   /* Functional Multiplexing Control 3 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_4,0xFFFE1014,__READ_WRITE);                   /* Functional Multiplexing Control 4 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_5,0xFFFE1018,__READ_WRITE);                   /* Functional Multiplexing Control 5 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_6,0xFFFE101C,__READ_WRITE);                   /* Functional Multiplexing Control 6 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_7,0xFFFE1020,__READ_WRITE);                   /* Functional Multiplexing Control 7 Register, ResetValue = 00000000h */
__IO_REG8(FUNC_MUX_CTRL_8,0xFFFE1024,__READ_WRITE);                    /* Functional Multiplexing Control Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_9,0xFFFE1028,__READ_WRITE);                   /* Functional Multiplexing Control 9 Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_A,0xFFFE102C,__READ_WRITE);                   /* Functional Multiplexing Control A Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_B,0xFFFE1030,__READ_WRITE);                   /* Functional Multiplexing Control B Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_C,0xFFFE1034,__READ_WRITE);                   /* Functional Multiplexing Control C Register, ResetValue = 00000000h */
__IO_REG32(FUNC_MUX_CTRL_D,0xFFFE1038,__READ_WRITE);                   /* Functional Multiplexing Control D Register, ResetValue = 00000000h */
__IO_REG32(PULL_DWN_CTRL_0,0xFFFE1040,__READ_WRITE);                   /* Pulldown Control 0 Register, ResetValue = 00000000h */
__IO_REG32(PULL_DWN_CTRL_1,0xFFFE1044,__READ_WRITE);                   /* Pulldown Control 1 Register, ResetValue = 00000000h */
__IO_REG32(PULL_DWN_CTRL_2,0xFFFE1048,__READ_WRITE);                   /* Pulldown Control 2 Register, ResetValue = 00000000h */
__IO_REG32(PULL_DWN_CTRL_3,0xFFFE104C,__READ_WRITE);                   /* Pulldown Control 3 Register, ResetValue = 00000000h */
__IO_REG32(GATE_INH_CTRL_0,0xFFFE1050,__READ_WRITE);                   /* Gate and Inhibit Control 0 Register, ResetValue = 00000000h */
__IO_REG32(VOLTAGE_CTRL_0,0xFFFE1060,__READ_WRITE);                    /* Voltage Control 0 Register, ResetValue = 00000000h */
__IO_REG32(TEST_DBG_CTRL_0,0xFFFE1070,__READ_WRITE);                   /* Test Debug Control 0 Register, ResetValue = 00000000h */
__IO_REG32(MOD_CONF_CTRL_0,0xFFFE1080,__READ_WRITE);                   /* Module Configuration Control 0 Register, ResetValue = 00000000h */

/***************************************************************************
 **
 **  Local Bus Control Registers 
 **
***************************************************************************/
__IO_REG32(LB_MPU_TIMEOUT,0xFFFEC100,__READ_WRITE);                    /* Local bus MPU access TIMEOUT 0000 00FFh Register, ResetValue =  */
__IO_REG32(LB_HOLD_TIMER,0xFFFEC104,__READ_WRITE);                     /* Local bus hold timer 0000 0000h Register, ResetValue =  */
__IO_REG32(LB_PRIORITY_REG,0xFFFEC108,__READ_WRITE);                   /* Local bus MPU access priority 0000 0000h Register, ResetValue =  */
__IO_REG32(LB_CLOCK_DIV,0xFFFEC10C,__READ_WRITE);                      /* Local bus clock divider 0000 00FCh Register, ResetValue =  */
__IO_REG32(LB_ABORT_ADD,0xFFFEC110,__READ);                            /* Local bus address of aborted MPU cycle FFFF FFFFh Register, ResetValue =  */
__IO_REG32(LB_ABORT_DATA,0xFFFEC114,__READ);                           /* Local bus cycle data of aborted MPU write cycle FFFF FFFFh Register, ResetValue =  */
__IO_REG32(LB_ABORT_STATUS,0xFFFEC118,__READ);                         /* Local bus cycle type of aborted MPU write cycle 0000 0000h Register, ResetValue =  */
__IO_REG32(LB_IRQ_OUTPUT,0xFFFEC11C,__READ_WRITE);                     /* Local bus external interrupt output control 0000 0000h Register, ResetValue =  */
__IO_REG32(LB_IRQ_INPUT,0xFFFEC120,__READ_WRITE);                      /* Local bus external interrupt status 0000 0000h Register, ResetValue =  */

/***************************************************************************
 **
 **  Local Bus MMU Registers 
 **
***************************************************************************/
__IO_REG32(LB_MMU_WALKING_ST_REG,0xFFFEC204,__READ_WRITE);             /* Local bus MMU Walking Status 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_CNTL_REG,0xFFFEC208,__READ_WRITE);                   /* Local bus MMU Control 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_FAULT_AD_H_REG,0xFFFEC20C,__READ);                   /* Local bus MMU Fault Address High 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_FAULT_AD_L_REG,0xFFFEC210,__READ);                   /* Local bus MMU Fault Address Low 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_FAULT_ST_REG,0xFFFEC214,__READ);                     /* Local bus MMU Fault Status 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_IT_ACK_REG,0xFFFEC218,__WRITE);                      /* Local bus MMU Interrupt Acknowledge 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_TTB_H_REG,0xFFFEC21C,__READ_WRITE);                  /* Local bus MMU TTB Register, ResetValue = High0000h */
__IO_REG32(LB_MMU_TTB_L_REG,0xFFFEC220,__READ_WRITE);                  /* Local bus MMU TTB Register, ResetValue = Low0000h */
__IO_REG32(LB_MMU_LOCK_REG,0xFFFEC224,__READ_WRITE);                   /* Local bus MMU Lock Counter 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_LD_TLB_REG,0xFFFEC228,__READ_WRITE);                 /* Local bus MMU TLB Load/Read Control 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_CAM_H_REG,0xFFFEC22C,__READ_WRITE);                  /* Local bus MMU CAM Entry High 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_CAM_L_REG,0xFFFEC230,__READ_WRITE);                  /* Local bus MMU CAM Entry Low 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_RAM_H_REG,0xFFFEC234,__READ_WRITE);                  /* Local bus MMU RAM Entry High 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_RAM_L_REG,0xFFFEC238,__READ_WRITE);                  /* Local bus MMU RAM Entry Low 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_GFLUSH_REG,0xFFFEC23C,__READ_WRITE);                 /* Local bus MMU Global Flush Control 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_FLUSH_ENTRY_REG,0xFFFEC240,__READ_WRITE);            /* Local bus MMU Individual Entry Flush Control 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_READ_CAM_H_REG,0xFFFEC244,__READ_WRITE);             /* Local bus MMU CAM Read High 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_READ_CAM_L_REG,0xFFFEC248,__READ_WRITE);             /* Local bus MMU CAM Read Low 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_READ_RAM_H_REG,0xFFFEC24C,__READ_WRITE);             /* Local bus MMU RAM Read High 0000h Register, ResetValue =  */
__IO_REG32(LB_MMU_READ_RAM_L_REG,0xFFFEC250,__READ_WRITE);             /* Local bus MMU RAM Read Low 0000h Register, ResetValue =  */

/***************************************************************************
 **
 **  DSP MMU Registers 
 **
***************************************************************************/
__IO_REG32(DSP_MMU_PREFETCH_REG,0xFFFED200,__READ_WRITE);              /* DSP MMU Prefetch Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_WALKING_ST_REG,0xFFFED204,__READ);                  /* DSP MMU Prefetch Status Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_CNTL_REG,0xFFFED208,__READ_WRITE);                  /* DSP MMU Control Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_FAULT_AD_H_REG,0xFFFED20C,__READ);                  /* DSP MMU Fault Address Register, ResetValue = MSB0000h */
__IO_REG32(DSP_MMU_FAULT_AD_L_REG,0xFFFED210,__READ);                  /* DSP MMU Fault Address Register, ResetValue = LSB0000h */
__IO_REG32(DSP_MMU_F_ST_REG,0xFFFED214,__READ);                        /* DSP MMU Fault Status Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_IT_ACK_REG,0xFFFED218,__WRITE);                     /* DSP MMU IT Acknowledge Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_TTB_H_REG,0xFFFED21C,__READ_WRITE);                 /* DSP MMU TTB Register, ResetValue = MSB0000h */
__IO_REG32(DSP_MMU_TTB_L_REG,0xFFFED220,__READ_WRITE);                 /* DSP MMU TTB Register, ResetValue = LSB0000h */
__IO_REG32(DSP_MMU_LOCK_REG,0xFFFED224,__READ_WRITE);                  /* DSP MMU Lock Counter Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_LD_TLB_REG,0xFFFED228,__READ_WRITE);                /* DSP MMU Load Entry TLB Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_CAM_H_REG,0xFFFED22C,__READ_WRITE);                 /* DSP MMU CAM Entry Register, ResetValue = MSB0000h */
__IO_REG32(DSP_MMU_CAM_L_REG,0xFFFED230,__READ_WRITE);                 /* DSP MMU CAM Entry Register, ResetValue = LSB0000h */
__IO_REG32(DSP_MMU_RAM_H_REG,0xFFFED234,__READ_WRITE);                 /* DSP MMU RAM Entry Register, ResetValue = MSB0000h */
__IO_REG32(DSP_MMU_RAM_L_REG,0xFFFED238,__READ_WRITE);                 /* DSP MMU RAM Entry Register, ResetValue = LSB0000h */
__IO_REG32(DSP_MMU_GFLUSH_REG,0xFFFED23C,__READ_WRITE);                /* DSP MMU Global Flush Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_FLUSH_ENTRY_REG,0xFFFED240,__READ_WRITE);           /* DSP MMU Individual Flush Register, ResetValue = 0000h */
__IO_REG32(DSP_MMU_READ_CAM_H_REG,0xFFFED244,__READ_WRITE);            /* DSP MMU Read CAM Register, ResetValue = MSB0000h */
__IO_REG32(DSP_MMU_READ_CAM_L_REG,0xFFFED248,__READ_WRITE);            /* DSP MMU Read CAM Register, ResetValue = LSB0000h */
__IO_REG32(DSP_MMU_READ_RAM_H_REG,0xFFFED24C,__READ_WRITE);            /* DSP MMU Read RAM Register, ResetValue = MSB0000h */
__IO_REG32(DSP_MMU_READ_RAM_L_REG,0xFFFED250,__READ_WRITE);            /* DSP MMU Read RAM Register, ResetValue = LSB0000h */

/***************************************************************************
 **
 **  MPUI Registers 
 **
***************************************************************************/
__IO_REG32(CTRL_REG,0xFFFEC900,__READ_WRITE);                          /* MPUI Control Register, ResetValue = 0003FF1Bh */
__IO_REG32(DEBUG_ADDR,0xFFFEC904,__READ);                              /* MPUI Debug Address Register, ResetValue = 01FFFFFFh */
__IO_REG32(DEBUG_DATA,0xFFFEC908,__READ);                              /* MPUI Debug Data Register, ResetValue = FFFFFFFFh */
__IO_REG32(DEBUG_FLAG,0xFFFEC90C,__READ);                              /* MPUI Debug Flag Register, ResetValue = 0800h */
__IO_REG32(STATUS_REG,0xFFFEC910,__READ);                              /* MPUI Status Register, ResetValue = 0000h */
__IO_REG32(DSP_STATUS_REG,0xFFFEC914,__READ);                          /* MPUI DSP Status Register, ResetValue = undef */
__IO_REG32(DSP_BOOT_CONFIG,0xFFFEC918,__READ_WRITE);                   /* MPUI Boot Configuration Register, ResetValue = 0000h */
__IO_REG32(DSP_MPUI_CONFIG,0xFFFEC91C,__READ_WRITE);                   /* MPUI DSP MPUI Configuration Register, ResetValue = FFFFh */

/***************************************************************************
 **
 **  TIPB (Private) Bridge 1 Configuration Registers 
 **
***************************************************************************/
__IO_REG32(TIPB_CNTL1,0xFFFECA00,__READ_WRITE);                        /* Private TIPB Control Register, ResetValue = FF11h */
__IO_REG32(TIPB_BUS_ALLOC1,0xFFFECA04,__READ_WRITE);                   /* Private TIPB Bus Allocation Register, ResetValue = 0009h */
__IO_REG32(MPU_TIPB_CNTL1,0xFFFECA08,__READ_WRITE);                    /* Private MPU TIPB Control Register, ResetValue = 0000h */
__IO_REG32(ENHANCED_TIPB_CNTL1,0xFFFECA0C,__READ_WRITE);               /* Private Enhanced TIPB Control Register, ResetValue = 0007h */
__IO_REG32(ADDRESS_DBG1,0xFFFECA10,__READ);                            /* Private Debug Address Register, ResetValue = FFFFh */
__IO_REG32(DATA_DEBUG_LOW1,0xFFFECA14,__READ);                         /* Private Debug Data LSB Register, ResetValue = FFFFh */
__IO_REG32(DATA_DEBUG_HIGH1,0xFFFECA18,__READ);                        /* Private Debug Data MSB Register, ResetValue = FFFFh */
__IO_REG32(DEBUG_CNTR_SIG1,0xFFFECA1C,__READ);                         /* Private Debug Control Signals Register, ResetValue = 00F8h */

/***************************************************************************
 **
 **  TIPB (Public) Bridge 2 Configuration Registers 
 **
***************************************************************************/
__IO_REG16(TIPB_CNTL2,0xFFFED300,__READ_WRITE);                        /* Public TIPB Control Register, ResetValue = FF11h */
__IO_REG16(TIPB_BUS_ALLOC2,0xFFFED304,__READ_WRITE);                   /* Public TIPB Bus Allocation Register, ResetValue = 0009h */
__IO_REG16(MPU_TIPB_CNTL2,0xFFFED308,__READ_WRITE);                    /* Public MPU TIPB Control Register, ResetValue = 0000h */
__IO_REG16(ENHANCED_TIPB_CNTL2,0xFFFED30C,__READ_WRITE);               /* Public Enhanced TIPB Control Register, ResetValue = 0007h */
__IO_REG16(ADDRESS_DBG2,0xFFFED310,__READ);                            /* Public Debug Address Register, ResetValue = FFFFh */
__IO_REG16(DATA_DEBUG_LOW2,0xFFFED314,__READ);                         /* Public Debug Data LSB Register, ResetValue = FFFFh */
__IO_REG16(DATA_DEBUG_HIGH2,0xFFFED318,__READ);                        /* Public Debug Data MSB Register, ResetValue = FFFFh */
__IO_REG16(DEBUG_CNTR_SIG2,0xFFFED31C,__READ);                         /* Public Debug Control Signals Register, ResetValue = 00F8h */

/***************************************************************************
 **
 **  MPU UART TIPB Bus Switch Registers 
 **
***************************************************************************/
__IO_REG16(RHSW_ARM_CNF1,0xFFFBC800,__READ_WRITE);                     /* UART1 TIPB Switch Configuration Register, ResetValue = (MPU)0001h */
__IO_REG16(RHSW_ARM_STA1,0xFFFBC804,__READ);                           /* UART1 TIPB Switch Status Register, ResetValue = (MPU)0001h */
__IO_REG16(RHSW_ARM_CNF2,0xFFFBC840,__READ_WRITE);                     /* UART2 TIPB Switch Configuration Register, ResetValue = (MPU)0001h */
__IO_REG16(RHSW_ARM_STA2,0xFFFBC844,__READ);                           /* UART2 TIPB Switch Status Register, ResetValue = (MPU)0001h */
__IO_REG16(RHSW_ARM_CNF3,0xFFFBC880,__READ_WRITE);                     /* UART3 TIPB Switch Configuration Register, ResetValue = (MPU)0001h */
__IO_REG16(RHSW_ARM_STA3,0xFFFBC884,__READ);                           /* UART3 TIPB Switch Status Register, ResetValue = (MPU)0001h */

/***************************************************************************
 **
 **  Traffic Controller Registers 
 **
***************************************************************************/
__IO_REG32(IMIF_PRIO,0xFFFECC00,__READ_WRITE);                         /* TC IMIF Priority Register, ResetValue = 00000000h */
__IO_REG32(EMIFS_PRIO_REG,0xFFFECC04,__READ_WRITE);                    /* TC EMIFS Priority Register, ResetValue = 00000000h */
__IO_REG32(EMIFF_PRIO_REG,0xFFFECC08,__READ_WRITE);                    /* TC EMIFF Priority Register, ResetValue = 00000000h */
__IO_REG32(EMIFS_CONFIG_REG,0xFFFECC0C,__READ_WRITE);                  /* TC EMIFS Configuration Register, ResetValue =  */
__IO_REG32(EMIFS_CS0_CONFIG,0xFFFECC10,__READ_WRITE);                  /* TC EMIFS CS0 Configuration Register, ResetValue = 0010FFFBh */
__IO_REG32(EMIFS_CS1_CONFIG,0xFFFECC14,__READ_WRITE);                  /* TC EMIFS CS1 Configuration Register, ResetValue = 0010FFFBh */
__IO_REG32(EMIFS_CS2_CONFIG,0xFFFECC18,__READ_WRITE);                  /* TC EMIFS CS2 Configuration Register, ResetValue = 0010FFFBh */
__IO_REG32(EMIFS_CS3_CONFIG,0xFFFECC1C,__READ_WRITE);                  /* TC EMIFS CS3 Configuration Register, ResetValue = 0010FFFBh */
__IO_REG32(EMIFF_SDRAM_CONFIG,0xFFFECC20,__READ_WRITE);                /* TC EMIFF SDRAM Configuration Register, ResetValue = 00618800h */
__IO_REG32(EMIFF_MRS,0xFFFECC24,__READ_WRITE);                         /* TC EMIFF SDRAM MRS Register, ResetValue = 00000037h */
__IO_REG32(TIMEOUT1,0xFFFECC28,__READ_WRITE);                          /* TC Timeout 1 Register, ResetValue = 00000000h */
__IO_REG32(TIMEOUT2,0xFFFECC2C,__READ_WRITE);                          /* TC Timeout 2 Register, ResetValue = 00000000h */
__IO_REG32(TIMEOUT3,0xFFFECC30,__READ_WRITE);                          /* TC Timeout 3 Register, ResetValue = 00000000h */
__IO_REG32(ENDIANISM,0xFFFECC34,__READ_WRITE);                         /* TC Endianism Register, ResetValue = 00000000h */
__IO_REG32(EMIFF_SDRAM_CONFIG_2,0xFFFECC3C,__READ_WRITE);              /* TC EMIFF SDRAM Configuration Register, ResetValue = 200000003h */
__IO_REG32(EMIFS_CFG_DYN_WAIT,0xFFFECC40,__READ_WRITE);                /* TC EMIFS Wait-State Configuration Register, ResetValue = 00000000h */

/***************************************************************************
 **
 **  MPU Clock/Reset/Power Mode Control Registers 
 **
***************************************************************************/
__IO_REG32(ARM_CKCTL,0xFFFECE00,__READ_WRITE);                         /* MPU Clock Control Register, ResetValue = 3000h */
__IO_REG32(ARM_IDLECT1,0xFFFECE04,__READ_WRITE);                       /* MPU Idle Control 1 Register, ResetValue = 0400h */
__IO_REG32(ARM_IDLECT2,0xFFFECE08,__READ_WRITE);                       /* MPU Idle Control 2 Register, ResetValue = 0100h */
__IO_REG32(ARM_EWUPCT,0xFFFECE0C,__READ_WRITE);                        /* MPU External Wakeup Control Register, ResetValue = 003Fh */
__IO_REG32(ARM_RSTCT1,0xFFFECE10,__READ_WRITE);                        /* MPU Reset Control 1 Register, ResetValue = 0000h */
__IO_REG32(ARM_RSTCT2,0xFFFECE14,__READ_WRITE);                        /* MPU Reset Control 2 Register, ResetValue = 0000h */
__IO_REG32(ARM_SYSST,0xFFFECE18,__READ_WRITE);                         /* MPU System Status Register, ResetValue = 0038h */

/***************************************************************************
 **
 **  DPLL1 Register 
 **
***************************************************************************/
__IO_REG32(DPLL1_CTL_REG,0xFFFECF00,__READ_WRITE);                     /* DPLL1 Control Register, ResetValue = 00002002h */

/***************************************************************************
 **
 **  Ultra Low Power Device Module Registers 
 **
***************************************************************************/
__IO_REG16(COUNTER_32_LSB,0xFFFE0800,__READ);                          /* ULPD 32-kHz Counter Register, ResetValue = LSB0001h */
__IO_REG16(COUNTER_32_MSB,0xFFFE0804,__READ);                          /* ULPD 32-kHz Counter Register, ResetValue = MSB0001h */
__IO_REG16(COUNTER_HIGH_FREQ_LSB,0xFFFE0808,__READ);                   /* ULPD High-Frequency Counter LSB Register, ResetValue = 0001h */
__IO_REG16(COUNTER_HIGH_FREQ_MSB,0xFFFE080C,__READ);                   /* ULPD High-Frequency Counter MSB Register, ResetValue = 0000h */
__IO_REG16(GAUGING_CTRL_REG,0xFFFE0810,__READ_WRITE);                  /* ULPD Gauging Control Register, ResetValue = 0000h */
__IO_REG16(IT_STATUS_REG,0xFFFE0814,__READ);                           /* ULPD Interrupt Status Register, ResetValue = 0000h */
__IO_REG16(SETUP_ULPD1_REG,0xFFFE0824,__READ_WRITE);                   /* ULPD Wakeup Time Setup Register, ResetValue = 03FFh */
__IO_REG16(CLOCK_CTRL_REG,0xFFFE0830,__READ_WRITE);                    /* ULPD Clock Control Register, ResetValue = 0000h */
__IO_REG16(SOFT_REQ_REG,0xFFFE0834,__READ_WRITE);                      /* ULPD Soft Clock Request Register, ResetValue = 0000h */
__IO_REG16(COUNTER_32_FIQ_REG,0xFFFE0838,__READ_WRITE);                /* ULPD Modem Shutdown Delay Register, ResetValue = 0001h */
__IO_REG16(DPLL_CTRL_REG,0xFFFE083C,__READ_WRITE);                     /* ULPD USB DPLL Control Register, ResetValue = 2211h */
__IO_REG16(STATUS_REQ_REG,0xFFFE0840,__READ_WRITE);                    /* ULPD Hardware Request Status Register, ResetValue = undef */
__IO_REG16(LOCK_TIME_REG,0xFFFE0848,__READ_WRITE);                     /* ULPD APLL Lock Time Register, ResetValue = 0960h */
__IO_REG16(APLL_CTRL_REG,0xFFFE084C,__READ_WRITE);                     /* ULPD APLL Control Register, ResetValue = undef */
__IO_REG16(POWER_CTRL_REG,0xFFFE0850,__READ_WRITE);                    /* ULPD Power Control Register, ResetValue = 0008h */

/***************************************************************************
 **
 **  Device Die Identification Registers 
 **
***************************************************************************/
__IO_REG32(DIE_ID_LSB,0xFFFE1800,__READ);                              /* Device Die Identification Register, ResetValue = (LSB). */
__IO_REG32(DIE_ID_MSB,0xFFFE1804,__READ);                              /* Device Die Identification Register, ResetValue = (MSB). */

/* JTAG Identification Code Register */
__IO_REG32(JTAG_ID,0xFFFED404,__READ);                                 /* JTAG Identification Code Register, ResetValue = . */

/* DSP Public Peripheral Registers */

/***************************************************************************
 **
 **  McBSP1 Registers 
 **
***************************************************************************/
__IO_REG16(MCBSP1_DRR2,0xE1011800,__READ_WRITE);                       /* McBSP1 data receive register 2, ResetValue = 0000h */
__IO_REG16(MCBSP1_DRR1,0xE1011802,__READ_WRITE);                       /* McBSP1 data receive register 1, ResetValue = 0000h */
__IO_REG16(MCBSP1_DXR2,0xE1011804,__READ_WRITE);                       /* McBSP1 data transmit register 2, ResetValue = 0000h */
__IO_REG16(MCBSP1_DXR1,0xE1011806,__READ_WRITE);                       /* McBSP1 data transmit register 1, ResetValue = 0000h */
__IO_REG16(MCBSP1_SPCR2,0xE1011808,__READ_WRITE);                      /* McBSP1 serial port control register 2, ResetValue = 0000h */
__IO_REG16(MCBSP1_SPCR1,0xE101180A,__READ_WRITE);                      /* McBSP1 serial port control register 1, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCR2,0xE101180C,__READ_WRITE);                       /* McBSP1 receive control register 2, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCR1,0xE101180E,__READ_WRITE);                       /* McBSP1 receive control register 1, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCR2,0xE1011810,__READ_WRITE);                       /* McBSP1 transmit control register 2, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCR1,0xE1011812,__READ_WRITE);                       /* McBSP1 transmit control register 1, ResetValue = 0000h */
__IO_REG16(MCBSP1_SRGR2,0xE1011814,__READ_WRITE);                      /* McBSP1 sample rate generator register 2, ResetValue = 2000h */
__IO_REG16(MCBSP1_SRGR1,0xE1011816,__READ_WRITE);                      /* McBSP1 sample rate generator register 1, ResetValue = 0001h */
__IO_REG16(MCBSP1_MCR2,0xE1011818,__READ_WRITE);                       /* McBSP1 multichannel register 2, ResetValue = 0000h */
__IO_REG16(MCBSP1_MCR1,0xE101181A,__READ_WRITE);                       /* McBSP1 multichannel register 1, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERA,0xE101181C,__READ_WRITE);                      /* McBSP1 receive channel enable register partition A, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERB,0xE101181E,__READ_WRITE);                      /* McBSP1 receive channel enable register partition B, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERA,0xE1011820,__READ_WRITE);                      /* McBSP1 transmit channel enable register partition A, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERB,0xE1011822,__READ_WRITE);                      /* McBSP1 transmit channel enable register partition B, ResetValue = 0000h */
__IO_REG16(MCBSP1_PCR0,0xE1011824,__READ_WRITE);                       /* McBSP1 pin control register 0, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERC,0xE1011826,__READ_WRITE);                      /* McBSP1 receive channel enable register partition C, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERD,0xE1011828,__READ_WRITE);                      /* McBSP1 receive channel enable register partition D, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERC,0xE101182A,__READ_WRITE);                      /* McBSP1 transmit channel enable register partition C, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERD,0xE101182C,__READ_WRITE);                      /* McBSP1 transmit channel enable register partition D, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERE,0xE101182E,__READ_WRITE);                      /* McBSP1 receive channel enable register partition E, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERF,0xE1011830,__READ_WRITE);                      /* McBSP1 receive channel enable register partition F, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERE,0xE1011832,__READ_WRITE);                      /* McBSP1 transmit channel enable register partition E, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERF,0xE1011834,__READ_WRITE);                      /* McBSP1 transmit channel enable register partition F, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERG,0xE1011836,__READ_WRITE);                      /* McBSP1 receive channel enable register partition G, ResetValue = 0000h */
__IO_REG16(MCBSP1_RCERH,0xE1011838,__READ_WRITE);                      /* McBSP1 receive channel enable register partition H, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERG,0xE101183A,__READ_WRITE);                      /* McBSP1 transmit channel enable register partition G, ResetValue = 0000h */
__IO_REG16(MCBSP1_XCERH,0xE101183C,__READ_WRITE);                      /* McBSP1 transmit channel enable register, ResetValue = 0000h */

/***************************************************************************
 **
 **  McBSP3 Registers 
 **
***************************************************************************/
__IO_REG16(MCBSP3_DRR2,0xE1017000,__READ_WRITE);                       /* McBSP3 data receive register 2, ResetValue = 0000h */
__IO_REG16(MCBSP3_DRR1,0xE1017002,__READ_WRITE);                       /* McBSP3 data receive register 1, ResetValue = 0000h */
__IO_REG16(MCBSP3_DXR2,0xE1017004,__READ_WRITE);                       /* McBSP3 data transmit register 2, ResetValue = 0000h */
__IO_REG16(MCBSP3_DXR1,0xE1017006,__READ_WRITE);                       /* McBSP3 data transmit register 1, ResetValue = 0000h */
__IO_REG16(MCBSP3_SPCR2,0xE1017008,__READ_WRITE);                      /* McBSP3 serial port control register 2, ResetValue = 0000h */
__IO_REG16(MCBSP3_SPCR1,0xE101700A,__READ_WRITE);                      /* McBSP3 serial port control register 1, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCR2,0xE101700C,__READ_WRITE);                       /* McBSP3 receive control register 2, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCR1,0xE101700E,__READ_WRITE);                       /* McBSP3 receive control register 1, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCR2,0xE1017010,__READ_WRITE);                       /* McBSP3 transmit control register 2, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCR1,0xE1017012,__READ_WRITE);                       /* McBSP3 transmit control register 1, ResetValue = 0000h */
__IO_REG16(MCBSP3_SRGR2,0xE1017014,__READ_WRITE);                      /* McBSP3 sample rate generator register 2, ResetValue = 2000h */
__IO_REG16(MCBSP3_SRGR1,0xE1017016,__READ_WRITE);                      /* McBSP3 sample rate generator register 1, ResetValue = 0001h */
__IO_REG16(MCBSP3_MCR2,0xE1017018,__READ_WRITE);                       /* McBSP3 multichannel register 2, ResetValue = 0000h */
__IO_REG16(MCBSP3_MCR1,0xE101701A,__READ_WRITE);                       /* McBSP3 multichannel register 1, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERA,0xE101701C,__READ_WRITE);                      /* McBSP3 receive channel enable register partition A, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERB,0xE101701E,__READ_WRITE);                      /* McBSP3 receive channel enable register partition B, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERA,0xE1017020,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition A, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERB,0xE1017022,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition B, ResetValue = 0000h */
__IO_REG16(MCBSP3_PCR0,0xE1017024,__READ_WRITE);                       /* McBSP3 pin control register 0, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERC,0xE1017026,__READ_WRITE);                      /* McBSP3 receive channel enable register partition C, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERD,0xE1017028,__READ_WRITE);                      /* McBSP3 receive channel enable register partition D, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERC,0xE101702A,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition C, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERD,0xE101702C,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition D, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERE,0xE101702E,__READ_WRITE);                      /* McBSP3 receive channel enable register partition E, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERF,0xE1017030,__READ_WRITE);                      /* McBSP3 receive channel enable register partition F, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERE,0xE1017032,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition E, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERF,0xE1017034,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition F, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERG,0xE1017036,__READ_WRITE);                      /* McBSP3 receive channel enable register partition G, ResetValue = 0000h */
__IO_REG16(MCBSP3_RCERH,0xE1017038,__READ_WRITE);                      /* McBSP3 receive channel enable register partition H, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERG,0xE101703A,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition G, ResetValue = 0000h */
__IO_REG16(MCBSP3_XCERH,0xE101703C,__READ_WRITE);                      /* McBSP3 transmit channel enable register partition H, ResetValue = 0000h */

/***************************************************************************
 **
 **  MCSI1 Registers 
 **
***************************************************************************/
__IO_REG16(MCSI1_CONTROL_REG,0xE1012800,__READ_WRITE);                 /* MCSI1 control register, ResetValue = 0000h */
__IO_REG16(MCSI1_MAIN_PARAMETERS_REG,0xE1012802,__READ_WRITE);         /* MCSI1 main parameters register, ResetValue = 0000h */
__IO_REG16(MCSI1_INTERRUPTS_REG,0xE1012804,__READ_WRITE);              /* MCSI1 interrupts register, ResetValue = 0000h */
__IO_REG16(MCSI1_CHANNEL_USED_REG,0xE1012806,__READ_WRITE);            /* MCSI1 channel used register, ResetValue = 0000h */
__IO_REG16(MCSI1_OVER_CLOCK_REG,0xE1012808,__READ_WRITE);              /* MCSI1 over-clock register, ResetValue = 0000h */
__IO_REG16(MCSI1_CLOCK_FREQUENCY_REG,0xE101280A,__READ_WRITE);         /* MCSI1 clock frequency register, ResetValue = 0000h */
__IO_REG16(MCSI1_STATUS_REG,0xE101280C,__READ_WRITE);                  /* MCSI1 status register, ResetValue = 0000h */
__IO_REG16(MCSI1_TX0,0xE1012840,__READ_WRITE);                         /* MCSI1 transmit word register 0, ResetValue = Undefined */
__IO_REG16(MCSI1_TX1,0xE1012842,__READ_WRITE);                         /* MCSI1 transmit word register 1, ResetValue = Undefined */
__IO_REG16(MCSI1_TX2,0xE1012844,__READ_WRITE);                         /* MCSI1 transmit word register 2, ResetValue = Undefined */
__IO_REG16(MCSI1_TX3,0xE1012846,__READ_WRITE);                         /* MCSI1 transmit word register 3, ResetValue = Undefined */
__IO_REG16(MCSI1_TX4,0xE1012848,__READ_WRITE);                         /* MCSI1 transmit word register 4, ResetValue = Undefined */
__IO_REG16(MCSI1_TX5,0xE101284A,__READ_WRITE);                         /* MCSI1 transmit word register 5, ResetValue = Undefined */
__IO_REG16(MCSI1_TX6,0xE101284C,__READ_WRITE);                         /* MCSI1 transmit word register 6, ResetValue = Undefined */
__IO_REG16(MCSI1_TX7,0xE101284E,__READ_WRITE);                         /* MCSI1 transmit word register 7, ResetValue = Undefined */
__IO_REG8(MCSI1_TX8,0xE1012850,__READ_WRITE);                          /* MCSI1 transmit word register, ResetValue = Undefined */
__IO_REG16(MCSI1_TX9,0xE1012852,__READ_WRITE);                         /* MCSI1 transmit word register 9, ResetValue = Undefined */
__IO_REG16(MCSI1_TX10,0xE1012854,__READ_WRITE);                        /* MCSI1 transmit word register 10, ResetValue = Undefined */
__IO_REG16(MCSI1_TX11,0xE1012856,__READ_WRITE);                        /* MCSI1 transmit word register 11, ResetValue = Undefined */
__IO_REG16(MCSI1_TX12,0xE1012858,__READ_WRITE);                        /* MCSI1 transmit word register 12, ResetValue = Undefined */
__IO_REG16(MCSI1_TX13,0xE101285A,__READ_WRITE);                        /* MCSI1 transmit word register 13, ResetValue = Undefined */
__IO_REG16(MCSI1_TX14,0xE101285C,__READ_WRITE);                        /* MCSI1 transmit word register 14, ResetValue = Undefined */
__IO_REG16(MCSI1_TX15,0xE101285E,__READ_WRITE);                        /* MCSI1 transmit word register 15, ResetValue = Undefined */
__IO_REG16(MCSI1_RX0,0xE1012860,__READ);                               /* MCSI1 receive word register 0, ResetValue = Undefined */
__IO_REG16(MCSI1_RX1,0xE1012862,__READ);                               /* MCSI1 receive word register 1, ResetValue = Undefined */
__IO_REG16(MCSI1_RX2,0xE1012864,__READ);                               /* MCSI1 receive word register 2, ResetValue = Undefined */
__IO_REG16(MCSI1_RX3,0xE1012866,__READ);                               /* MCSI1 receive word register 3, ResetValue = Undefined */
__IO_REG16(MCSI1_RX4,0xE1012868,__READ);                               /* MCSI1 receive word register 4, ResetValue = Undefined */
__IO_REG16(MCSI1_RX5,0xE101286A,__READ);                               /* MCSI1 receive word register 5, ResetValue = Undefined */
__IO_REG16(MCSI1_RX6,0xE101286C,__READ);                               /* MCSI1 receive word register 6, ResetValue = Undefined */
__IO_REG16(MCSI1_RX7,0xE101286E,__READ);                               /* MCSI1 receive word register 7, ResetValue = Undefined */
__IO_REG8(MCSI1_RX8,0xE1012870,__READ);                                /* MCSI1 receive word register, ResetValue = Undefined */
__IO_REG16(MCSI1_RX9,0xE1012872,__READ);                               /* MCSI1 receive word register 9, ResetValue = Undefined */
__IO_REG16(MCSI1_RX10,0xE1012874,__READ);                              /* MCSI1 receive word register 10, ResetValue = Undefined */
__IO_REG16(MCSI1_RX11,0xE1012876,__READ);                              /* MCSI1 receive word register 11, ResetValue = Undefined */
__IO_REG16(MCSI1_RX12,0xE1012878,__READ);                              /* MCSI1 receive word register 12, ResetValue = Undefined */
__IO_REG16(MCSI1_RX13,0xE101287A,__READ);                              /* MCSI1 receive word register 13, ResetValue = Undefined */
__IO_REG16(MCSI1_RX14,0xE101287C,__READ);                              /* MCSI1 receive word register 14, ResetValue = Undefined */
__IO_REG16(MCSI1_RX15,0xE101287E,__READ);                              /* MCSI1 receive word register 15, ResetValue = Undefined */

/***************************************************************************
 **
 **  MCSI2 Registers 
 **
***************************************************************************/
__IO_REG16(MCSI2_CONTROL_REG,0xE1012000,__READ_WRITE);                 /* MCSI2 control register, ResetValue = 0000h */
__IO_REG16(MCSI2_MAIN_PARAMETERS_REG,0xE1012002,__READ_WRITE);         /* MCSI2 main parameters register, ResetValue = 0000h */
__IO_REG16(MCSI2_INTERRUPTS_REG,0xE1012004,__READ_WRITE);              /* MCSI2 interrupts register, ResetValue = 0000h */
__IO_REG16(MCSI2_CHANNEL_USED_REG,0xE1012006,__READ_WRITE);            /* MCSI2 channel used register, ResetValue = 0000h */
__IO_REG16(MCSI2_OVER_CLOCK_REG,0xE1012008,__READ_WRITE);              /* MCSI2 over-clock register, ResetValue = 0000h */
__IO_REG16(MCSI2_CLOCK_FREQUENCY_REG,0xE101200A,__READ_WRITE);         /* MCSI2 clock frequency register, ResetValue = 0000h */
__IO_REG16(MCSI2_STATUS_REG,0xE101200C,__READ_WRITE);                  /* MCSI2 status register, ResetValue = 0000h */
__IO_REG16(MCSI2_TX0,0xE1012040,__READ_WRITE);                         /* MCSI2 transmit word register 0, ResetValue = Undefined */
__IO_REG16(MCSI2_TX1,0xE1012042,__READ_WRITE);                         /* MCSI2 transmit word register 1, ResetValue = Undefined */
__IO_REG16(MCSI2_TX2,0xE1012044,__READ_WRITE);                         /* MCSI2 transmit word register 2, ResetValue = Undefined */
__IO_REG16(MCSI2_TX3,0xE1012046,__READ_WRITE);                         /* MCSI2 transmit word register 3, ResetValue = Undefined */
__IO_REG16(MCSI2_TX4,0xE1012048,__READ_WRITE);                         /* MCSI2 transmit word register 4, ResetValue = Undefined */
__IO_REG16(MCSI2_TX5,0xE101204A,__READ_WRITE);                         /* MCSI2 transmit word register 5, ResetValue = Undefined */
__IO_REG16(MCSI2_TX6,0xE101204C,__READ_WRITE);                         /* MCSI2 transmit word register 6, ResetValue = Undefined */
__IO_REG16(MCSI2_TX7,0xE101204E,__READ_WRITE);                         /* MCSI2 transmit word register 7, ResetValue = Undefined */
__IO_REG8(MCSI2_TX8,0xE1012050,__READ_WRITE);                          /* MCSI2 transmit word register, ResetValue = Undefined */
__IO_REG16(MCSI2_TX9,0xE1012052,__READ_WRITE);                         /* MCSI2 transmit word register 9, ResetValue = Undefined */
__IO_REG16(MCSI2_TX10,0xE1012054,__READ_WRITE);                        /* MCSI2 transmit word register 10, ResetValue = Undefined */
__IO_REG16(MCSI2_TX11,0xE1012056,__READ_WRITE);                        /* MCSI2 transmit word register 11, ResetValue = Undefined */
__IO_REG16(MCSI2_TX12,0xE1012058,__READ_WRITE);                        /* MCSI2 transmit word register 12, ResetValue = Undefined */
__IO_REG16(MCSI2_TX13,0xE101205A,__READ_WRITE);                        /* MCSI2 transmit word register 13, ResetValue = Undefined */
__IO_REG16(MCSI2_TX14,0xE101205C,__READ_WRITE);                        /* MCSI2 transmit word register 14, ResetValue = Undefined */
__IO_REG16(MCSI2_TX15,0xE101205E,__READ_WRITE);                        /* MCSI2 transmit word register 15, ResetValue = Undefined */
__IO_REG16(MCSI2_RX0,0xE1012060,__READ);                               /* MCSI2 receive word register 0, ResetValue = Undefined */
__IO_REG16(MCSI2_RX1,0xE1012062,__READ);                               /* MCSI2 receive word register 1, ResetValue = Undefined */
__IO_REG16(MCSI2_RX2,0xE1012064,__READ);                               /* MCSI2 receive word register 2, ResetValue = Undefined */
__IO_REG16(MCSI2_RX3,0xE1012066,__READ);                               /* MCSI2 receive word register 3, ResetValue = Undefined */
__IO_REG16(MCSI2_RX4,0xE1012068,__READ);                               /* MCSI2 receive word register 4, ResetValue = Undefined */
__IO_REG16(MCSI2_RX5,0xE101206A,__READ);                               /* MCSI2 receive word register 5, ResetValue = Undefined */
__IO_REG16(MCSI2_RX6,0xE101206C,__READ);                               /* MCSI2 receive word register 6, ResetValue = Undefined */
__IO_REG16(MCSI2_RX7,0xE101206E,__READ);                               /* MCSI2 receive word register 7, ResetValue = Undefined */
__IO_REG8(MCSI2_RX8,0xE1012070,__READ);                                /* MCSI2 receive word register, ResetValue = Undefined */
__IO_REG16(MCSI2_RX9,0xE1012072,__READ);                               /* MCSI2 receive word register 9, ResetValue = Undefined */
__IO_REG16(MCSI2_RX10,0xE1012074,__READ);                              /* MCSI2 receive word register 10, ResetValue = Undefined */
__IO_REG16(MCSI2_RX11,0xE1012076,__READ);                              /* MCSI2 receive word register 11, ResetValue = Undefined */
__IO_REG16(MCSI2_RX12,0xE1012078,__READ);                              /* MCSI2 receive word register 12, ResetValue = Undefined */
__IO_REG16(MCSI2_RX13,0xE101207A,__READ);                              /* MCSI2 receive word register 13, ResetValue = Undefined */
__IO_REG16(MCSI2_RX14,0xE101207C,__READ);                              /* MCSI2 receive word register 14, ResetValue = Undefined */
__IO_REG16(MCSI2_RX15,0xE101207E,__READ);                              /* MCSI2 receive word register 15, ResetValue = Undefined */


/* DSP Configuration Registers */

/***************************************************************************
 **
 **  DSP Clock Mode Registers 
 **
***************************************************************************/
__IO_REG16(DSP_CKCTL,0xE1008000,__READ_WRITE);                         /* DSP Clock Control Register, ResetValue = 0000h */
__IO_REG16(DSP_IDLECT1,0xE1008004,__READ_WRITE);                       /* DSP Idle Control 1 Register, ResetValue = 0000h */
__IO_REG16(DSP_IDLECT2,0xE1008008,__READ_WRITE);                       /* DSP Idle Control 2 Register, ResetValue = 0000h */
__IO_REG16(DSP_RSTCT2,0xE1008014,__READ_WRITE);                        /* DSP Peripheral Reset Control Register, ResetValue = 0000h */
__IO_REG16(DSP_SYSST,0xE1008018,__READ_WRITE);                         /* DSP System Status Register, ResetValue = 0000h */

/* MPU/DSP Shared Peripheral Register Descriptions */

/***************************************************************************
 **
 **  UART1 Registers 
 **
***************************************************************************/
__IO_REG8(UART1_RHR,0xFFFB0000,__READ_WRITE);                                /* UART1 receive holding register, ResetValue = Undefined */
#define UART1_THR UART1_RHR                                            /* UART1 transmit holding register, ResetValue = Undefined */
#define UART1_DLL UART1_RHR                                            /* UART1 divisor latch low register, ResetValue = 00h */
__IO_REG8(UART1_IER,0xFFFB0004,__READ_WRITE);                          /* UART1 interrupt enable register, ResetValue = 00h */
#define UART1_DLH UART1_IER                                            /* UART1 divisor latch high register, ResetValue = 00h */
__IO_REG8(UART1_IIR,0xFFFB0008,__READ_WRITE);                                /* UART1 interrupt identification register, ResetValue = 01h */
#define UART1_FCR UART1_IIR                                            /* UART1 FIFO control register, ResetValue = 00h */
#define UART1_EFR UART1_IIR                                            /* UART1 enhanced feature register, ResetValue = 00h */
__IO_REG8(UART1_LCR,0xFFFB000C,__READ_WRITE);                          /* UART1 line control register, ResetValue = 00h */
__IO_REG8(UART1_MCR,0xFFFB0010,__READ_WRITE);                          /* UART1 modem control register, ResetValue = 00h */
#define UART1_XON1 UART1_MCR                                           /* UART1 XON1 register, ResetValue = 00h */
__IO_REG8(UART1_LSR,0xFFFB0014,__READ_WRITE);                          /* UART1 mode register, ResetValue = 60h */
#define UART1_XON2 UART1_LSR                                           /* UART1 XON2 register, ResetValue = 00h */
__IO_REG8(UART1_MSR,0xFFFB0018,__READ_WRITE);                          /* UART1 modem status register, ResetValue = Undefined */
#define UART1_TCR UART1_MSR                                            /* UART1 transmission control register, ResetValue = 0Fh */
#define UART1_XOFF1 UART1_MSR                                          /* UART1 XOFF1 register, ResetValue = 00h */
__IO_REG8(UART1_SPR,0xFFFB001C,__READ_WRITE);                          /* UART1 scratchpad register, ResetValue = 00h */
#define UART1_TLR UART1_SPR                                            /* UART1 trigger level register, ResetValue = 00h */
#define UART1_XOFF2 UART1_SPR                                          /* UART1 XOFF2 register, ResetValue = 00h */
__IO_REG8(UART1_MDR1,0xFFFB0020,__READ_WRITE);                         /* UART1 mode definition 1 register, ResetValue = 07h */
__IO_REG8(UART1_UASR,0xFFFB0038,__READ);                               /* UART1 autobauding status register, ResetValue = 00h */
__IO_REG8(UART1_SCR,0xFFFB0040,__READ_WRITE);                          /* UART1 supplementary control register, ResetValue = 00h */
__IO_REG8(UART1_SSR,0xFFFB0044,__READ);                                /* UART1 supplementary status register, ResetValue = 00h */
__IO_REG8(UART1_OSC_12M_SEL,0xFFFB004C,__WRITE);                       /* UART1 12-/13-MHz oscillator select register, ResetValue = 00h */
__IO_REG8(UART1_MVR,0xFFFB0050,__READ);                                /* UART1 module version register, ResetValue = . */

/***************************************************************************
 **
 **  UART2 Registers 
 **
***************************************************************************/
__IO_REG8(UART2_RHR,0xFFFB0800,__READ_WRITE);                          /* UART2 receive holding register, ResetValue = Undefined */
#define UART2_THR UART2_RHR                                            /* UART2 transmit holding register, ResetValue = Undefined */
#define UART2_DLL UART2_RHR                                            /* UART2 divisor latch low register, ResetValue = 00h */
__IO_REG8(UART2_IER,0xFFFB0804,__READ_WRITE);                          /* UART2 interrupt enable register, ResetValue = 00h */
#define UART2_DLH UART2_IER                                            /* UART2 divisor latch high register, ResetValue = 00h */
__IO_REG8(UART2_IIR,0xFFFB0808,__READ_WRITE);                          /* UART2 interrupt identification register, ResetValue = 01h */
#define UART2_FCR UART2_IIR                                            /* UART2 FIFO control register, ResetValue = 00h */
#define UART2_EFR UART2_IIR                                            /* UART2 enhanced feature register, ResetValue = 00h */
__IO_REG8(UART2_LCR,0xFFFB080C,__READ_WRITE);                          /* UART2 line control register, ResetValue = 00h */
__IO_REG8(UART2_MCR,0xFFFB0810,__READ_WRITE);                          /* UART2 modem control register, ResetValue = 00h */
#define UART2_XON1 UART2_MCR                                           /* UART2 XON1 register, ResetValue = 00h */
__IO_REG8(UART2_LSR,0xFFFB0814,__READ_WRITE);                          /* UART2 mode register, ResetValue = 60h */
#define UART2_XON2 UART2_LSR                                           /* UART2 XON2 register, ResetValue = 00h */
__IO_REG8(UART2_MSR,0xFFFB0818,__READ_WRITE);                          /* UART2 modem status register, ResetValue = Undefined */
#define UART2_TCR UART2_MSR                                            /* UART2 transmission control register, ResetValue = 0Fh */
#define UART2_XOFF1 UART2_MSR                                          /* UART2 XOFF1 register, ResetValue = 00h */
__IO_REG8(UART2_SPR,0xFFFB081C,__READ_WRITE);                          /* UART2 scratchpad register, ResetValue = 00h */
#define UART2_TLR UART2_SPR                                            /* UART2 trigger level register, ResetValue = 00h */
#define UART2_XOFF2 UART2_SPR                                          /* UART2 XOFF2 register, ResetValue = 00h */
__IO_REG8(UART2_MDR1,0xFFFB0820,__READ_WRITE);                         /* UART2 mode definition 1 register, ResetValue = 07h */
__IO_REG8(UART2_UASR,0xFFFB0838,__READ);                               /* UART2 autobauding status register, ResetValue = 00h */
__IO_REG8(UART2_SCR,0xFFFB0840,__READ_WRITE);                          /* UART2 supplementary control register, ResetValue = 00h */
__IO_REG8(UART2_SSR,0xFFFB0844,__READ);                                /* UART2 supplementary status register, ResetValue = 00h */
__IO_REG8(UART2_OSC_12M_SELV,0xFFFB084C,__WRITE);                      /* UART2 12-/13-MHz oscillator select register, ResetValue = 00h */
__IO_REG8(UART2_MVR,0xFFFB0850,__READ);                                /* UART2 module version register, ResetValue = . */

/***************************************************************************
 **
 **  UART3/IrDA Registers 
 **
***************************************************************************/
__IO_REG8(UART3_RHR,0xFFFB9800,__READ_WRITE);                                /* UART3 receive holding register, ResetValue = Undefined */
#define UART3_THR UART3_RHR                                            /* UART3 transmit holding register, ResetValue = Undefined */
#define UART3_DLL UART3_RHR                                            /* UART3 divisor latch low register, ResetValue = 00h */
__IO_REG8(UART3_IER,0xFFFB9804,__READ_WRITE);                          /* UART3 interrupt enable register, ResetValue = 00h */
#define UART3_DLH UART3_IER                                            /* UART3 divisor latch high register, ResetValue = 00h */
__IO_REG8(UART3_IIR,0xFFFB9808,__READ_WRITE);                          /* UART3 interrupt identification register, ResetValue = 01h */
#define UART3_FCR UART3_IIR                                            /* UART3 FIFO control register, ResetValue = 00h */
#define UART3_EFR UART3_IIR                                            /* UART3 enhanced feature register, ResetValue = 00h */
__IO_REG8(UART3_LCR,0xFFFB980C,__READ_WRITE);                          /* UART3 line control register, ResetValue = 00h */
__IO_REG8(UART3_MCR,0xFFFB9810,__READ_WRITE);                          /* UART3 modem control register, ResetValue = 00h */
#define UART3_XON1 UART3_MCR                                           /* UART3 XON1 register, ResetValue = 00h */
__IO_REG8(UART3_LSR,0xFFFB9814,__READ_WRITE);                          /* UART3 mode register, ResetValue = 60h */
#define UART3_XON2 UART3_LSR                                           /* UART3 XON2 register, ResetValue = 00h */
__IO_REG8(UART3_MSR,0xFFFB9818,__READ_WRITE);                          /* UART3 modem status register, ResetValue = Undefined */
#define UART3_TCR UART3_MSR                                            /* UART3 transmission control register, ResetValue = 0Fh */
#define UART3_XOFF1 UART3_MSR                                          /* UART3 XOFF1 register, ResetValue = 00h */
__IO_REG8(UART3_SPR,0xFFFB981C,__READ_WRITE);                          /* UART3 scratchpad register, ResetValue = 00h */
#define UART3_TLR UART3_SPR                                            /* UART3 trigger level register, ResetValue = 00h */
#define UART3_XOFF2 UART3_SPR                                          /* UART3 XOFF2 register, ResetValue = 00h */
__IO_REG8(UART3_MDR1,0xFFFB9820,__READ_WRITE);                         /* UART3 mode definition 1 register, ResetValue = 07h */
__IO_REG8(UART3_MDR2,0xFFFB9824,__READ_WRITE);                         /* UART3 mode definition register 2, ResetValue = 00h */
__IO_REG8(UART3_SFLSR,0xFFFB9828,__READ_WRITE);                        /* UART3 status FIFO line status register, ResetValue = 00h */
#define UART3_TXFLL UART3_SFLSR                                        /* UART3 transmit frame length low, ResetValue = 00h */
__IO_REG8(UART3_RESUME,0xFFFB982C,__READ_WRITE);                       /* UART3 resume register, ResetValue = 00h */
#define UART3_TXFLH UART3_RESUME                                       /* UART3 transmit frame length high, ResetValue = 00h */
__IO_REG8(UART3_SFREGL,0xFFFB9830,__READ_WRITE);                       /* UART3 status FIFO low register, ResetValue = Undefined */
#define UART3_RXFLL UART3_SFREGL                                       /* UART3 receive frame length low, ResetValue = 00h */
__IO_REG8(UART3_SFREGH,0xFFFB9834,__READ_WRITE);                       /* UART3 status FIFO high register, ResetValue = Undefined */
#define UART3_RXFLH UART3_SFREGH                                       /* UART3 receive frame length high, ResetValue = 00h */
__IO_REG8(UART3_BLR,0xFFFB9838,__READ_WRITE);                          /* UART3 BOF control register, ResetValue = 40h */
__IO_REG8(UART3_ACREG,0xFFFB983C,__READ_WRITE);                        /* UART3 auxiliary control register, ResetValue = 00h */
#define UART3_DIV16 UART3_ACREG                                        /* UART3 divide 1.6 register, ResetValue = 00h */
__IO_REG8(UART3_SCR,0xFFFB9840,__READ_WRITE);                          /* UART3 supplementary control register, ResetValue = 00h */

/***************************************************************************
 **
 **  MPU/DSP Shared GPIO Registers 
 **
***************************************************************************/
__IO_REG16(DATA_INPUT,0xFFFCE000,__READ);                              /* Data Input Register R, ResetValue = 0000h */
__IO_REG16(DATA_OUTPUT,0xFFFCE004,__READ_WRITE);                       /* Data Output Register RW, ResetValue = FFFFh */
__IO_REG16(DIRECTION_CONTROL,0xFFFCE008,__READ_WRITE);                 /* Direction Control Register RW, ResetValue = FFFFh */
__IO_REG16(INTERRUPT_CONTROL,0xFFFCE00C,__READ_WRITE);                 /* Interrupt Control Register RW, ResetValue = FFFFh */
__IO_REG16(INTERRUPT_MASK,0xFFFCE010,__READ_WRITE);                    /* Interrupt Mask Register RW, ResetValue = FFFFh */
__IO_REG16(INTERRUPT_STATUS,0xFFFCE014,__READ_WRITE);                  /* Interrupt Status Register RW, ResetValue = 0000h */
__IO_REG16(PIN_CONTROL,0xFFFCE018,__READ);                             /* Pin Control Register, ResetValue = FFFFh */

/***************************************************************************
 **
 **  MPU/DSP Shared Mailbox Registers 
 **
***************************************************************************/
__IO_REG16(ARM2DSP1,0xFFFCF000,__READ);                                /* MPU to DSP 1 Data Register, ResetValue = 0000h */
__IO_REG16(ARM2DSP1B,0xFFFCF004,__READ);                               /* MPU to DSP 1 Command Register, ResetValue = 0000h */
__IO_REG16(DSP2ARM1,0xFFFCF008,__READ);                                /* DSP to MPU 1 Data Register, ResetValue = 0000h */
__IO_REG16(DSP2ARM1B,0xFFFCF00C,__READ);                               /* DSP to MPU 1 Command Register, ResetValue = 0000h */
__IO_REG16(DSP2ARM2,0xFFFCF010,__READ);                                /* DSP to MPU 2 Data Register, ResetValue = 0000h */
__IO_REG16(DSP2ARM2B,0xFFFCF014,__READ);                               /* DSP to MPU 2 Command Register, ResetValue = 0000h */
__IO_REG16(ARM2DSP1_FLAG,0xFFFCF018,__READ);                           /* MPU to DSP 1 Flag Register R, ResetValue = undef */
__IO_REG16(DSP2ARM1_FLAG,0xFFFCF01C,__READ);                           /* DSP to MPU 1 Flag Register R, ResetValue = undef */
__IO_REG16(DSP2ARM2_FLAG,0xFFFCF020,__READ);                           /* DSP to MPU 2 Flag Register R, ResetValue = undef */
__IO_REG16(ARM2DSP2,0xFFFCF024,__READ);                                /* MPU to DSP 2 Data Register, ResetValue = 0000h */
__IO_REG16(ARM2DSP2B,0xFFFCF028,__READ);                               /* MPU to DSP 2 Command Register, ResetValue = 0000h */
__IO_REG16(ARM2DSP2_FLAG,0xFFFCF02C,__READ);                           /* MPU to DSP 2 Flag Register R, ResetValue = undef */



#endif    /* __OMAP5910_H */
