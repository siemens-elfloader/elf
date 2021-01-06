/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Cirrus Logic EP9312
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2003
 **
 **    $Revision: 1.19.2.1 $
 **
 **    Note: Only little endian addressing of 8 bit registers.
 ***************************************************************************/

#ifndef __IOEP9312_H
#define __IOEP9312_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    IOEP9312 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* DMA channel arbitration register */
typedef struct{
__REG32 CHARB  : 1;
__REG32        :31;
} __dmacharb_bits;

/* DMA global interrupt register */
typedef struct{
__REG32 D0   : 1;
__REG32 D1   : 1;
__REG32 D2   : 1;
__REG32 D3   : 1;
__REG32 D4   : 1;
__REG32 D5   : 1;
__REG32 D6   : 1;
__REG32 D7   : 1;
__REG32 D8   : 1;
__REG32 D9   : 1;
__REG32 D10  : 1;
__REG32 D11  : 1;
__REG32      :20;
} __dmaglint_bits;

/* DMA channel control register */
typedef struct{
__REG32 STALLIntEn    : 1;
__REG32 NFBIntEn      : 1;
__REG32               : 1;
__REG32 ChErrorIntEn  : 1;
__REG32 ENABLE        : 1;
__REG32 ABORT         : 1;
__REG32 ICE           : 1;
__REG32               :25;
} __m2pcontrol_bits;

/* DMA peripheral port allocation register */
typedef struct{
__REG32 PPALLOC  : 4;
__REG32          :28;
} __ppalloc_bits;

/* DMA interrupt register */
typedef struct{
__REG32 STALLInt    : 1;
__REG32 NFBint      : 1;
__REG32             : 1;
__REG32 ChErrorInt  : 1;
__REG32             :28;
} __m2pinterrupt_bits;

/* DMA M2P status register */
typedef struct{
__REG32 STALL         : 1;
__REG32 NFB           : 1;
__REG32               : 1;
__REG32 ChError       : 1;
__REG32 CurrentState  : 2;
__REG32 NextBuffer    : 1;
__REG32 BYTES         : 5;
__REG32               :20;
} __m2pstatus_bits;

/* DMA channel bytes remaining register */
typedef struct{
__REG32 REMAIN  :16;
__REG32         :16;
} __remain_bits;

/* DMA max byte count register */
typedef struct{
__REG32 MAXCNT  :16;
__REG32         :16;
} __maxcnt_bits;

/* DMA M2M channel control register */
typedef struct{
__REG32 STALLIntEn  : 1;
__REG32 SCT         : 1;
__REG32 DONEIntEn   : 1;
__REG32 ENABLE      : 1;
__REG32 START       : 1;
__REG32 BWC         : 4;
__REG32 PW          : 2;
__REG32 DAH         : 1;
__REG32 SAH         : 1;
__REG32 TM          : 2;
__REG32 ETDP        : 2;
__REG32 DACKP       : 1;
__REG32             : 1;
__REG32 DREQP       : 1;
__REG32             : 1;
__REG32 NFBIntEn    : 1;
__REG32 RSS         : 2;
__REG32 NO_HDSK     : 1;
__REG32 PWSC        : 7;
} __m2mcontrol_bits;

/* DMA M2M interrupt register */
typedef struct{
__REG32 STALLInt  : 1;
__REG32 DONEint   : 1;
__REG32 NFBint    : 1;
__REG32           :29;
} __m2minterrupt_bits;

/* DMA M2M status register */
typedef struct{
__REG32 STALL         : 1;
__REG32 CurrentState  : 5;
__REG32 DONE          : 1;
__REG32 TCS           : 2;
__REG32 EOTS          : 2;
__REG32 NFB           : 1;
__REG32 NB            : 1;
__REG32 DREQS         : 1;
__REG32               :18;
} __m2mstatus_bits;

/* DMA BCRx register */
typedef struct{
__REG32 BCR  :16;
__REG32      :16;
} __bcrx_bits;


/* Power/State control register */
typedef struct{
__REG32 RTCDIV         : 6;
__REG32 PLL1_LOCK      : 1;
__REG32 PLL1_LOCK_REG  : 1;
__REG32 PLL2_LOCK      : 1;
__REG32 PLL2_LOCK_REG  : 1;
__REG32 SW_RESET       : 1;
__REG32 RSTFLG         : 1;
__REG32 TEST_RESET     : 1;
__REG32 CLDFLG         : 1;
__REG32                : 1;
__REG32 WDTFLG         : 1;
__REG32 CHIPID         : 8;
__REG32 CHIPMAN        : 8;
} __pwrsts_bits;

/* Clock/Debug control register */
typedef struct{
__REG32              :16;
__REG32 DMA_M2P_CH1  : 1;
__REG32 DMA_M2P_CH0  : 1;
__REG32 DMA_M2P_CH3  : 1;
__REG32 DMA_M2P_CH2  : 1;
__REG32 DMA_M2P_CH5  : 1;
__REG32 DMA_M2P_CH4  : 1;
__REG32 DMA_M2P_CH7  : 1;
__REG32 DMA_M2P_CH6  : 1;
__REG32 DMA_M2P_CH9  : 1;
__REG32 DMA_M2P_CH8  : 1;
__REG32 DMA_M2M_CH0  : 1;
__REG32 DMA_M2M_CH1  : 1;
__REG32 USH_EN       : 1;
__REG32 UART_BAUD    : 1;
__REG32              : 1;
__REG32 FIR_EN       : 1;
} __pwrcnt_bits;

/* ClkSet1 system control register */
typedef struct{
__REG32 PLL1X2IPD   : 5;
__REG32 PLL1X2FBD2  : 6;
__REG32 PLL1X1FBD1  : 5;
__REG32 PLL1_PS     : 2;
__REG32 PCLK_DIV    : 2;
__REG32 HCLK_DIV    : 3;
__REG32 nBYP1       : 1;
__REG32 SMCROM      : 1;
__REG32 FCLK_DIV    : 3;
__REG32             : 4;
} __clkset1_bits;

/* ClkSet2 system control register */
typedef struct{
__REG32 PLL2X2IPD   : 5;
__REG32 PLL2X2FB02  : 6;
__REG32 PLL2X1FBD1  : 5;
__REG32 PLL2_PS     : 2;
__REG32 PLL2_EN     : 1;
__REG32 nBYP2       : 1;
__REG32             : 8;
__REG32 USB_DIV     : 4;
} __clkset2_bits;

/* APBWait register */
typedef struct{
__REG32 NO_WRITE_WAIT  : 1;
__REG32                :31;
} __apbwait_bits;

/* Bus master arbitration register */
typedef struct{
__REG32 PRI_ORD    : 2;
__REG32            : 1;
__REG32 PRI_CORE   : 1;
__REG32 DMA_ENIRQ  : 1;
__REG32 DMA_ENFIQ  : 1;
__REG32 USH_ENIRQ  : 1;
__REG32 USH_ENFIQ  : 1;
__REG32 MAC_ENIRQ  : 1;
__REG32 MAC_ENFIQ  : 1;
__REG32            :22;
} __busmstrarb_bits;

/* Device config register */
typedef struct{
__REG32 SHena      : 1;
__REG32 KEYS       : 1;
__REG32 ADCPD      : 1;
__REG32 RAS        : 1;
__REG32 RASOnP3    : 1;
__REG32            : 1;
__REG32 I2SonAC97  : 1;
__REG32 I2SonSSP   : 1;
__REG32 EonIDE     : 1;
__REG32 PonG       : 1;
__REG32 GonIDE     : 1;
__REG32 HonIDE     : 1;
__REG32 HC1EN      : 1;
__REG32 HC1IN      : 1;
__REG32 HC3EN      : 1;
__REG32 HC3IN      : 1;
__REG32            : 1;
__REG32 TIN        : 1;
__REG32 U1EN       : 1;
__REG32 EXVC       : 1;
__REG32 U2EN       : 1;
__REG32 A1onG      : 1;
__REG32 A2onG      : 1;
__REG32 CPENA      : 1;
__REG32 U3EN       : 1;
__REG32 MonG       : 1;
__REG32 TonG       : 1;
__REG32 GonK       : 1;
__REG32 IonU2      : 1;
__REG32 D0onG      : 1;
__REG32 D1onG      : 1;
__REG32 SWRST      : 1;
} __devicecfg_bits;

/* Video clock config register */
typedef struct{
__REG32 VDIV  : 7;
__REG32       : 1;
__REG32 PDIV  : 2;
__REG32       : 3;
__REG32 PSEL  : 1;
__REG32 ESEL  : 1;
__REG32 VENA  : 1;
__REG32       :16;
} __vidclkdiv_bits;

/* MIR clock config register */
typedef struct{
__REG32 MDIV  : 7;
__REG32       : 1;
__REG32 PDIV  : 2;
__REG32       : 3;
__REG32 PSEL  : 1;
__REG32 ESEL  : 1;
__REG32 MENA  : 1;
__REG32       :16;
} __mirclkdiv_bits;

/* I2S clock config register */
typedef struct{
__REG32 MDIV   : 7;
__REG32        : 1;
__REG32 PDIV   : 2;
__REG32        : 3;
__REG32 PSEL   : 1;
__REG32 ESEL   : 1;
__REG32 MENA   : 1;
__REG32 SDIV   : 1;
__REG32 LRDIV  : 2;
__REG32 SPOL   : 1;
__REG32 DROP   : 1;
__REG32        : 8;
__REG32 ORIDE  : 1;
__REG32 SLAVE  : 1;
__REG32 SENA   : 1;
} __i2sclkdiv_bits;

/* Key matrix, touch screen and adc clock config register */
typedef struct{
__REG32 KDIV  : 1;
__REG32       :14;
__REG32 KEN   : 1;
__REG32 ADIV  : 1;
__REG32       :14;
__REG32 TSEN  : 1;
} __keytchclkdiv_bits;

/* Chip id register */
typedef struct{
__REG32 ID    :16;
__REG32 PKID  : 1;
__REG32       : 1;
__REG32 BND   : 1;
__REG32       : 9;
__REG32 REV   : 4;
} __chipid_bits;

/* System config register */
typedef struct{
__REG32 LCSn1   : 1;
__REG32 LCSn2   : 1;
__REG32         : 1;
__REG32 LEECLK  : 1;
__REG32 LEEDA   : 1;
__REG32 LASD0   : 1;
__REG32 LCSn6   : 1;
__REG32 LCSn7   : 1;
__REG32 SBOOT   : 1;
__REG32         :19;
__REG32 REV     : 4;
} __syscfg_bits;

/* System software lock register */
typedef struct{
__REG32 LOCK  : 8;
__REG32       :24;
} __sysswlock_bits;


/* VIC Interrupt registers 0-31 */
typedef struct{
__REG32 int0   : 1;
__REG32 int1   : 1;
__REG32 int2   : 1;
__REG32 int3   : 1;
__REG32 int4   : 1;
__REG32 int5   : 1;
__REG32 int6   : 1;
__REG32 int7   : 1;
__REG32 int8   : 1;
__REG32 int9   : 1;
__REG32 int10  : 1;
__REG32 int11  : 1;
__REG32 int12  : 1;
__REG32 int13  : 1;
__REG32 int14  : 1;
__REG32 int15  : 1;
__REG32 int16  : 1;
__REG32 int17  : 1;
__REG32 int18  : 1;
__REG32 int19  : 1;
__REG32 int20  : 1;
__REG32 int21  : 1;
__REG32 int22  : 1;
__REG32 int23  : 1;
__REG32 int24  : 1;
__REG32 int25  : 1;
__REG32 int26  : 1;
__REG32 int27  : 1;
__REG32 int28  : 1;
__REG32 int29  : 1;
__REG32 int30  : 1;
__REG32 int31  : 1;
} __vic1int_bits;

/* VIC Interrupt registers 32-63 */
typedef struct{
__REG32 int32  : 1;
__REG32 int33  : 1;
__REG32 int34  : 1;
__REG32 int35  : 1;
__REG32 int36  : 1;
__REG32 int37  : 1;
__REG32 int38  : 1;
__REG32 int39  : 1;
__REG32 int40  : 1;
__REG32 int41  : 1;
__REG32 int42  : 1;
__REG32 int43  : 1;
__REG32 int44  : 1;
__REG32 int45  : 1;
__REG32 int46  : 1;
__REG32 int47  : 1;
__REG32 int48  : 1;
__REG32 int49  : 1;
__REG32 int50  : 1;
__REG32 int51  : 1;
__REG32 int52  : 1;
__REG32 int53  : 1;
__REG32 int54  : 1;
__REG32 int55  : 1;
__REG32 int56  : 1;
__REG32 int57  : 1;
__REG32 int58  : 1;
__REG32 int59  : 1;
__REG32 int60  : 1;
__REG32 int61  : 1;
__REG32 int62  : 1;
__REG32 int63  : 1;
} __vic2int_bits;

/* VIC protection enable register */
typedef struct{
__REG32 Protection  : 1;
__REG32             :31;
} __vicprotection_bits;

/* VIC vector control register */
typedef struct{
__REG32 IntSource  : 5;
__REG32 E          : 1;
__REG32            :26;
} __vicvectcntl_bits;


/* Raster engine total register */
typedef struct{
__REG32 TOTAL  :11;
__REG32        :21;
} __total_bits;

/* Raster engine start stop register */
typedef struct{
__REG32 STRT  :11;
__REG32       : 5;
__REG32 STOP  :11;
__REG32       : 5;
} __strtstop_bits;

/* Raster engine brightness register */
typedef struct{
__REG32 CNT  : 8;
__REG32 CMP  : 8;
__REG32      :16;
} __brightness_bits;

/* Raster engine video attribs register */
typedef struct{
__REG32 EN      : 1;
__REG32 PCLKEN  : 1;
__REG32 SYNCEN  : 1;
__REG32 DATEN   : 1;
__REG32 CSYNC   : 1;
__REG32 VCPOL   : 1;
__REG32 HSPOL   : 1;
__REG32 BLKPOL  : 1;
__REG32 INVCLK  : 1;
__REG32 ACEN    : 1;
__REG32 LCDEN   : 1;
__REG32         : 1;
__REG32 CCIREN  : 1;
__REG32 PIFEN   : 1;
__REG32 INTEN   : 1;
__REG32 INT     : 1;
__REG32 INTRLC  : 1;
__REG32 EQUSER  : 1;
__REG32 DHORZ   : 1;
__REG32 DVERT   : 1;
__REG32 BKPXD   : 1;
__REG32         :11;
} __videoattribs_bits;

/* Raster engine scrnpage register */
typedef struct{
__REG32 PAGE  :28;
__REG32       : 4;
} __scrnpage_bits;

/* Raster engine scrnlines register */
typedef struct{
__REG32 LINES  :11;
__REG32        :21;
} __scrnlines_bits;

/* Raster engine line length register */
typedef struct{
__REG32 LEN  :11;
__REG32      :21;
} __linelength_bits;

/* Raster engine step size register */
typedef struct{
__REG32 STEP  :12;
__REG32       :20;
} __step_bits;

/* Raster engine line carry register */
typedef struct{
__REG32 LCARY  :11;
__REG32        :21;
} __carry_bits;

/* Raster engine offset register */
typedef struct{
__REG32 OFFSET  :16;
__REG32         :16;
} __offset_bits;

/* Raster engine swlock register */
typedef struct{
__REG32 SWLCK  : 8;
__REG32        :24;
} __swlock_bits;

/* Raster engine AC rate register */
typedef struct{
__REG32 RATE  :11;
__REG32       :21;
} __acrate_bits;

/* Raster engine FIFO level register */
typedef struct{
__REG32 LEVEL  : 6;
__REG32        :26;
} __fifolevel_bits;

/* Raster engine pixel mode register */
typedef struct{
__REG32 P      : 3;
__REG32 S      : 3;
__REG32 M      : 4;
__REG32 C      : 4;
__REG32 DSCAN  : 1;
__REG32 TRBSW  : 1;
__REG32        :16;
} __pixelmode_bits;

/* Raster engine parallell interface output control register */
typedef struct{
__REG32 DAT  : 8;
__REG32 RD   : 1;
__REG32      :23;
} __parllifout_bits;

/* Raster engine parallell interface inout control register */
typedef struct{
__REG32 DAT    : 8;
__REG32        : 8;
__REG32 CNT    : 4;
__REG32 ESTRT  : 4;
__REG32        : 8;
} __parllifin_bits;

/* Raster engine blink rate register */
typedef struct{
__REG32 RATE  : 8;
__REG32       :24;
} __blinkrate_bits;

/* Raster engine blink mask register */
typedef struct{
__REG32 MASK  :24;
__REG32       : 8;
} __blinkmask_bits;

/* Raster engine blink pattern register */
typedef struct{
__REG32 PATRN  :24;
__REG32        : 8;
} __blinkpattrn_bits;

/* Raster engine pattern mask register */
typedef struct{
__REG32 PMASK  :24;
__REG32        : 8;
} __pattrnmask_bits;

/* Raster engine background color/blink offset register */
typedef struct{
__REG32 BGOFF  :24;
__REG32        : 8;
} __bkgrndoffset_bits;

/* Raster engine cursor size register */
typedef struct{
__REG32 CWID   : 2;
__REG32 CLINS  : 6;
__REG32 CSTEP  : 2;
__REG32 DLNS   : 6;
__REG32        :16;
} __cursorsize_bits;

/* Raster engine cursor color registers */
typedef struct{
__REG32 COLOR  :24;
__REG32        : 8;
} __cursorcolor_bits;

/* Raster engine cursor XYLoc register */
typedef struct{
__REG32 XLOC  :11;
__REG32       : 4;
__REG32 CEN   : 1;
__REG32 YLOC  :11;
__REG32       : 5;
} __cursorxyloc_bits;

/* Raster engine cursor DScanLHYLoc register */
typedef struct{
__REG32 YLOC   :11;
__REG32        : 4;
__REG32 CLHEN  : 1;
__REG32        :16;
} __cursordscanlhyloc_bits;

/* Raster engine cursor blink rate control register */
typedef struct{
__REG32 RATE  : 8;
__REG32 EN    : 1;
__REG32       :23;
} __cursorblinkratectrl_bits;

/* Raster engine GrySclLUTR, GrySclLUTG, GrySclLUTB registers */
typedef struct{
__REG32 D      :16;
__REG32 HORZ   : 1;
__REG32 VERT   : 1;
__REG32 FRAME  : 1;
__REG32        :13;
} __gryscllut_bits;

/* Raster engine LUT switching control register */
typedef struct{
__REG32 SWTCH  : 1;
__REG32 SSTAT  : 1;
__REG32        :30;
} __lutswctrl_bits;

/* Raster engine color LUT register */
typedef struct{
__REG32 B  : 8;
__REG32 G  : 8;
__REG32 R  : 8;
__REG32    : 8;
} __colorlut_bits;

/* Raster video output signature result value register */
typedef struct{
__REG32 SIGVAL  :16;
__REG32         :16;
} __vidsigrsltval_bits;

/* Raster video signature control register */
typedef struct{
__REG32 PEN     :24;
__REG32 VSYNC   : 1;
__REG32 HSYNC   : 1;
__REG32 BLANK   : 1;
__REG32 CLKEN   : 1;
__REG32 BRIGHT  : 1;
__REG32 SPCLK   : 1;
__REG32         : 1;
__REG32 EN      : 1;
} __vidsigctrl_bits;

/* Raster engine clear and store register */
typedef struct{
__REG32 HCLR  :11;
__REG32       : 5;
__REG32 VCLR  :11;
__REG32       : 5;
} __sigclrstr_bits;


/* MAC self control register */
typedef struct{
__REG32 RESET   : 1;
__REG32         : 1;
__REG32 MIIL    : 1;
__REG32 PDWE    : 1;
__REG32 PUWE    : 1;
__REG32 GPO0    : 1;
__REG32         : 1;
__REG32 RWP     : 1;
__REG32 PSPRS   : 1;
__REG32 MDCDIV  : 6;
__REG32         :17;
} __selfctl_bits;

/* MAC diag addr register */
typedef struct{
__REG32 ADDR  : 8;
__REG32       :24;
} __diagad_bits;

/* MAC Receiver Control Register */
typedef struct{
__REG32 IA0     : 1;
__REG32 IA1     : 1;
__REG32 IA2     : 1;
__REG32 IA3     : 1;
__REG32         : 4;
__REG32 IAHA    : 1;
__REG32 MA      : 1;
__REG32 BA      : 1;
__REG32 PA      : 1;
__REG32 RA      : 1;
__REG32 RCRCA   : 1;
__REG32         : 2;
__REG32 SRxON   : 1;
__REG32 BCRC    : 1;
__REG32 RxFCE0  : 1;
__REG32 RxFCE1  : 1;
__REG32 PauseA  : 1;
__REG32         :11;
} __rxctl_bits;

/* MAC Transmitter Control Register */
typedef struct{
__REG32 STxON   : 1;
__REG32 PB      : 1;
__REG32 SP      : 1;
__REG32 OColl   : 1;
__REG32 TxPD    : 1;
__REG32 ICRC    : 1;
__REG32 MBE     : 1;
__REG32 DefDls  : 1;
__REG32         :24;
} __txctl_bits;

/* MAC Test Control Register */
typedef struct{
__REG32       : 5;
__REG32 DB    : 1;
__REG32 MFDX  : 1;
__REG32 MACF  : 1;
__REG32       :24;
} __testctl_bits;

/* MAC MII Command Register */
typedef struct{
__REG32 REGAD  : 5;
__REG32 PHYAD  : 5;
__REG32        : 4;
__REG32 OP     : 2;
__REG32        :16;
} __miicmd_bits;

/* MAC MII Data Register */
typedef struct{
__REG32 MIIData  :16;
__REG32          :16;
} __miidata_bits;

/* MAC MII Status Register */
typedef struct{
__REG32 BUSY  : 1;
__REG32       :31;
} __miists_bits;

/* MAC Interrupt Enable Register */
typedef struct{
__REG32 RHDRIE  : 1;
__REG32 REOBIE  : 1;
__REG32 REOFIE  : 1;
__REG32 TSQIE   : 1;
__REG32         : 4;
__REG32 SWIE    : 1;
__REG32         : 1;
__REG32 TIE     : 1;
__REG32 PHYSIE  : 1;
__REG32 MIIE    : 1;
__REG32         : 3;
__REG32 RxROIE  : 1;
__REG32 TxCOIE  : 1;
__REG32 MOIE    : 1;
__REG32         : 5;
__REG32 TxUHIE  : 1;
__REG32 ECIE    : 1;
__REG32 TXLEIE  : 1;
__REG32 RxSQIE  : 1;
__REG32 RxBIE   : 1;
__REG32 RxMIE   : 1;
__REG32         : 2;
} __inten_bits;

/* MAC Interrupt Status Register */
typedef struct{
__REG32        : 2;
__REG32 RxSQ   : 1;
__REG32 TxSQ   : 1;
__REG32 OTHER  : 1;
__REG32        : 3;
__REG32 SWI    : 1;
__REG32 AHBE   : 1;
__REG32 TI     : 1;
__REG32 PHYSI  : 1;
__REG32 MIII   : 1;
__REG32        : 3;
__REG32 RxROI  : 1;
__REG32 TxCOI  : 1;
__REG32 MOI    : 1;
__REG32        : 5;
__REG32 TxUHI  : 1;
__REG32 ECI    : 1;
__REG32 TxLEI  : 1;
__REG32 RxSQI  : 1;
__REG32 RxBI   : 1;
__REG32 RxMI   : 1;
__REG32 RWI    : 1;
__REG32        : 1;
} __intstspc_bits;

/* MAC General Timer Register */
typedef struct{
__REG32 GTP  :16;
__REG32 GTC  :16;
} __gt_bits;

/* MAC Flow Control Timer Register */
typedef struct{
__REG32 FCT  :24;
__REG32      : 8;
} __fct_bits;

/* MAC Flow Control Format Register */
typedef struct{
__REG32 TPT    :16;
__REG32 MACCT  :16;
} __fcf_bits;

/* MAC Address Filter Pointer Register */
typedef struct{
__REG32 AFP  : 3;
__REG32      :29;
} __afp_bits;

/* MAC Global Interrupt Status Register */
typedef struct{
__REG32      :15;
__REG32 INT  : 1;
__REG32      :16;
} __intsts_bits;

/* MAC Transmit Collision Count Register */
typedef struct{
__REG32 TXC  :16;
__REG32      :16;
} __txcollcnt_bits;

/* MAC Receive Miss Count Register */
typedef struct{
__REG32 RMC  :16;
__REG32      :16;
} __rxmisscnt_bits;

/* MAC Receive Runt Count Register */
typedef struct{
__REG32 RRC  :16;
__REG32      :16;
} __rxruntcnt_bits;

/* MAC Bus Master Control Register */
typedef struct{
__REG32 RxEn   : 1;
__REG32 RxDis  : 1;
__REG32 RxChR  : 1;
__REG32        : 1;
__REG32 EEOB   : 1;
__REG32 EH1    : 1;
__REG32 EH2    : 1;
__REG32        : 1;
__REG32 TxEn   : 1;
__REG32 TxDis  : 1;
__REG32 TxChR  : 1;
__REG32 UnH    : 1;
__REG32 TT     : 1;
__REG32 MT     : 1;
__REG32        :18;
} __bmctl_bits;

/* MAC Bus Master Status Register */
typedef struct{
__REG32 QID    : 3;
__REG32 RxAct  : 1;
__REG32 TP     : 1;
__REG32        : 2;
__REG32 TxAct  : 1;
__REG32        :24;
} __bmsts_bits;

/* MAC Receive Descriptor Enqueue Register */
typedef struct{
__REG32 RDI  : 8;
__REG32      : 8;
__REG32 RDV  :16;
} __rxdenq_bits;

/* MAC Receive Status Enqueue Register */
typedef struct{
__REG32 RSI  : 8;
__REG32      : 8;
__REG32 RSV  :16;
} __rxstsenq_bits;

/* MAC Transmit Descriptor Enqueue Register */
typedef struct{
__REG32 TDI  : 8;
__REG32      : 8;
__REG32 TDV  :16;
} __txdenq_bits;

/* MAC Receive Buffer Threshold Register */
typedef struct{
__REG32       : 2;
__REG32 RDST  : 8;
__REG32       : 8;
__REG32 RDHT  : 8;
__REG32       : 6;
} __rxbufthrshld_bits;

/* MAC Transmit Buffer Threshold Register */
typedef struct{
__REG32       : 2;
__REG32 TDST  : 8;
__REG32       : 8;
__REG32 TDHT  : 8;
__REG32       : 6;
} __txbufthrshld_bits;

/* MAC Receive Status Threshold Register */
typedef struct{
__REG32       : 2;
__REG32 RSST  : 4;
__REG32       :12;
__REG32 RSHT  : 4;
__REG32       :10;
} __rxststhrshld_bits;

/* MAC Transmit Status Threshold Register */
typedef struct{
__REG32       : 2;
__REG32 TSST  : 4;
__REG32       :12;
__REG32 TSHT  : 4;
__REG32       :10;
} __txststhrshld_bits;

/* MAC Receive Descriptor Threshold Register */
typedef struct{
__REG32       : 2;
__REG32 RDST  : 4;
__REG32       :12;
__REG32 RDHT  : 4;
__REG32       :10;
} __rxdthrshld_bits;

/* MAC Transmit Descriptor Threshold Register */
typedef struct{
__REG32       : 2;
__REG32 TDST  : 4;
__REG32       :12;
__REG32 TDHT  : 4;
__REG32       :10;
} __txdthrshld_bits;

/* MAC Maximum Frame Length Register */
typedef struct{
__REG32 TST  :11;
__REG32      : 5;
__REG32 MFL  :11;
__REG32      : 5;
} __maxfrmlen_bits;

/* MAC Receive Header Length Register */
typedef struct{
__REG32 RHL1  :10;
__REG32       : 6;
__REG32 RHL2  :11;
__REG32       : 5;
} __rxhdrlen_bits;


/* USB hc revision register */
typedef struct{
__REG32 REV  : 8;
__REG32      :24;
} __hcrevision_bits;

/* USB control register */
typedef struct{
__REG32 CBSR  : 2;
__REG32 PLE   : 1;
__REG32 IE    : 1;
__REG32 CLE   : 1;
__REG32 BLE   : 1;
__REG32 HCFS  : 2;
__REG32 IR    : 1;
__REG32 RWC   : 1;
__REG32 RWE   : 1;
__REG32       :21;
} __hccontrol_bits;

/* USB command status register */
typedef struct{
__REG32 HCR  : 1;
__REG32 CLF  : 1;
__REG32 BLF  : 1;
__REG32 OCR  : 1;
__REG32      :12;
__REG32 SOC  : 1;
__REG32      :15;
} __hccommandstatus_bits;

/* USB interrupt status register */
typedef struct{
__REG32 SO    : 1;
__REG32 WDH   : 1;
__REG32 SF    : 1;
__REG32 RD    : 1;
__REG32 UE    : 1;
__REG32 FNO   : 1;
__REG32 RHSC  : 1;
__REG32       :23;
__REG32 OC    : 1;
__REG32       : 1;
} __hcinterruptstatus_bits;

/* USB interrupt enable register */
typedef struct{
__REG32 SO    : 1;
__REG32 WDH   : 1;
__REG32 SF    : 1;
__REG32 RD    : 1;
__REG32 UE    : 1;
__REG32 FNO   : 1;
__REG32 RHSC  : 1;
__REG32       :23;
__REG32 OC    : 1;
__REG32 MIE   : 1;
} __hcinterruptenable_bits;

/* USB HcHCCA register */
typedef struct{
__REG32     : 8;
__REG32 AD  :24;
} __hchcca_bits;

/* USB register */
typedef struct{
__REG32     : 4;
__REG32 AD  :28;
} __currented_bits;

/* USB HcFmInterval register */
typedef struct{
__REG32 FI     :14;
__REG32        : 2;
__REG32 FSMPS  :15;
__REG32 FIT    : 1;
} __hcfminterval_bits;

/* USB HcFmRemaining register */
typedef struct{
__REG32 FR   :14;
__REG32      :17;
__REG32 FRT  : 1;
} __hcfmremaining_bits;

/* USB HcFmNumber register */
typedef struct{
__REG32 FN  :16;
__REG32     :16;
} __hcfmnumber_bits;

/* USB HcPeriodicStart register */
typedef struct{
__REG32 PS  :14;
__REG32     :18;
} __hcperiodicstart_bits;

/* USB HcLsThreshold register */
typedef struct{
__REG32 LST  :12;
__REG32      :20;
} __hclsthreshold_bits;

/* USB HcRhDescriptorA register */
typedef struct{
__REG32 NDP   : 8;
__REG32 PSM   : 1;
__REG32 NPS   : 1;
__REG32 DT    : 1;
__REG32 OCPM  : 1;
__REG32 NOCP  : 1;
__REG32       :11;
__REG32 P     : 8;
} __hcrhdescriptora_bits;

/* USB HcRhDescriptorB register */
typedef struct{
__REG32 DR    : 4;
__REG32       :12;
__REG32 PPCM  : 4;
__REG32       :12;
} __hcrhdescriptorb_bits;

/* USB HcRhStatus register */
typedef struct{
__REG32 LPS   : 1;
__REG32 OCI   : 1;
__REG32       :13;
__REG32 DRWE  : 1;
__REG32 LPSC  : 1;
__REG32 CCIC  : 1;
__REG32       :13;
__REG32 CRWE  : 1;
} __hcrhstatus_bits;

/* USB HcRhPortStatus register */
typedef struct{
__REG32 CCS   : 1;
__REG32 PES   : 1;
__REG32 PSS   : 1;
__REG32 POCI  : 1;
__REG32 PRS   : 1;
__REG32       : 3;
__REG32 PPS   : 1;
__REG32 LSDA  : 1;
__REG32       : 6;
__REG32 CSC   : 1;
__REG32 PESC  : 1;
__REG32 PSSC  : 1;
__REG32 OCIC  : 1;
__REG32 PRSC  : 1;
__REG32       :11;
} __hcrhportstatus_bits;

/* USB USBCfgCtrl register */
typedef struct{
__REG32       : 1;
__REG32 TPOC  : 3;
__REG32 TRCS  : 1;
__REG32       :27;
} __usbcfgctrl_bits;

/* USB USBHCISts register */
typedef struct{
__REG32 MBA  : 1;
__REG32 MSN  : 1;
__REG32 RWU  : 1;
__REG32      :29;
} __usbhcists_bits;


/* SDRAM GICONFIG register */
typedef struct{
__REG32 Initialize   : 1;
__REG32 MRS          : 1;
__REG32              : 3;
__REG32 SMEMBust     : 1;
__REG32 LCR          : 1;
__REG32 ReArbEn      : 1;
__REG32              :22;
__REG32 ClkShutdown  : 1;
__REG32 CKE          : 1;
} __giconfig_bits;

/* SDRAM BOOTSTS register */
typedef struct{
__REG32 Width          : 2;
__REG32 LatchedMedchg  : 1;
__REG32                :29;
} __bootsts_bits;

/* SDRAM SDRAMDEVCfgx register */
typedef struct{
__REG32                   : 2;
__REG32 ExternalBusWidth  : 1;
__REG32 BankCount         : 1;
__REG32 SROM512           : 1;
__REG32 SRMLL             : 1;
__REG32 _2KPAGE           : 1;
__REG32 SFConfigAddr      : 1;
__REG32                   : 8;
__REG32 CasLat            : 3;
__REG32 WBL               : 1;
__REG32 RasToCas          : 2;
__REG32                   : 2;
__REG32 AutoPrecharce     : 1;
__REG32                   : 7;
} __sdramdevcfgx_bits;


/* SMC SMCBCRX register */
typedef struct{
__REG32 IBCY       : 4;
__REG32            : 1;
__REG32 WST1       : 5;
__REG32 RBLE       : 1;
__REG32 WST2       : 5;
__REG32            : 9;
__REG32 WPERR      : 1;
__REG32 WP         : 1;
__REG32 PME        : 1;
__REG32 MW         : 2;
__REG32 EBIBRKDIS  : 1;
__REG32            : 1;
} __smcbcrx_bits;


/* IDE IDECtrl register */
typedef struct{
__REG32 CS0n   : 1;     // Chip select 0 pin output control
__REG32 CS1n   : 1;     // Chip select 1 pin output control
__REG32 DA     : 3;     // Device address output control
__REG32 DIORn  : 1;     // DIORn pin output control
__REG32 DIOWn  : 1;     // DIOWn pin output control
__REG32 DASPn  : 1;     // DASPn pin input sta. Signal comes
                                     // in on EGPIO[15]. Read only
__REG32 DMARQ  : 1;     // DMARQ pin input state. Signal comes
                                     // in on the EGPIo[2]. Read only.
__REG32 INTRQ  : 1;     // INTRQ pin input state. Input comes
                                     // from teh INT[3] input pin
__REG32 IORDY  : 1;     // IORDY pin input state
__REG32        :21;
} __idectrl_bits;

/* IDE IDECfg register */
typedef struct{
__REG32 IDEEN  : 1;     // IDE master enable
__REG32 PIO    : 1;     // Polled IO operation selection
__REG32 MDMA   : 1;     // Multiword DMA operation selection
__REG32 UDMA   : 1;     // Ultra DMA operation selection
__REG32 MODE   : 4;     // Speed mode number (0 - 4 for PIO,
                                     // 0 - 2 for MDMA, 0 - 4 for UDMA)
__REG32 WST    : 2;     // Wait State for Turn.  Number of
                                     // HCLK cycles to hold the data bus after
                                     // PIO write operation
__REG32        :22;
} __idecfg_bits;


/* IDE IDEMDMAOP register */
typedef struct{
__REG32 MEN   : 1;     // Enable Multiword DMA operation.
                                     // 1 - start mdma, 0 - terminate
                                     // mdma operation by host.
__REG32 RWOP  : 1;     // Read or write operation selection:
                                     // 0 = read, 1 = write.
__REG32       :30;
} __idemdmaop_bits;

/* IDE IDEUDMAOP register */
typedef struct{
__REG32 UEN   : 1;     // Enable Ultra DMA operation.
                                     // 1 - start udma, 0 - terminate
                                     // udma operation by host.
__REG32 RWOP  : 1;     // Read or write operation selection:
                                     // 0 = read, 1 = write.
__REG32       :30;
} __ideudmaop_bits;

/* IDE IDEUDMASts register */
typedef struct{
__REG32 CS0n    : 1;     // Chip select pin 0 status. Should
                                      // be driven to 1 (deasserted) in UDMA
__REG32 CS1n    : 1;     // Chip select pin 1 status. Should
                                      // be driven to 1 (deasserted) in UDMA
__REG32 DA      : 3;     // Device address status, should be
                                      // driven to 0 (deasserted) in UDMA
__REG32 HSHD    : 1;     // HSTROBE (during data out) status,
                                      // HDMARDYn (during data in) status,
                                      // driven by UDMA state machine.
__REG32 STOP    : 1;     // STOP (during data out) status, driven
                                      // by UDMA state machine.
__REG32 DM      : 1;     // DMACKn status, driven by UDMA state
                                      // machine.
                                      // in on EGPIO[15]. Read only
__REG32 DDOE    : 1;     // DD bus output enable as controlled
                                      // by UDMA state machine.
__REG32 DMARQ   : 1;     // Synchronized version of DMARQ input
                                      // from device.
__REG32 DSDD    : 1;     // DSTROBE (during data in) and DDMARDYn
                                      // (during data out) status from device.
__REG32         : 5;     // reserved, always zero
__REG32 DMAide  : 1;     // DMA request signal from UDMA state
                                      // machine.
__REG32 INTide  : 1;     // INT line generated by UDMA state
                                      // machine.
__REG32 SBUSY   : 1;     // UDMA state machine busy, not in idle
                                      // state.
__REG32         : 5;     // Reserved, always zero.
__REG32 NDO     : 1;     // Error for data out not completed
__REG32 NDI     : 1;     // Error for data in not completed
__REG32 N4X     : 1;     // Error for data transferred not
                                      // multiples of 4 32 bit words.
__REG32         : 5;
} __ideudmasts_bits;

/* IDE IDEUDMADEBUG register */
typedef struct{
__REG32 RWOE   : 1;     // Reset UDMA write data out error.
__REG32 RWPTR  : 1;     // Reset UDMA write buffer ptr to 0.
__REG32 RWDR   : 1;     // Reset UDMA write DMA request.
__REG32 RROE   : 1;     // Reset UDMA read data in error.
__REG32 RRPTR  : 1;     // Reset UDMA read buffer ptr to 0.
__REG32 RRDR   : 1;     // Reset UDMA read DMA request.

__REG32        :26;
} __ideudmadebug_bits;

/* IDE IDEUDMAWrBufSts register */
typedef struct{
__REG32 HPTR   : 4;     // Head pointer in the write buffer
__REG32 TPTR   : 4;     // Tail pointer in the write buffer
__REG32 EMPTY  : 1;     // Write buffer empty status
__REG32 HOM    : 1;     // Half or more entries in write buffer
                                      // filled status
__REG32 NFULL  : 1;     // Write buffer near full status
__REG32 FULL   : 1;     // Write buffer full status
__REG32        : 4;     // Reserved, always zero
__REG32 CRC    :16;     // CRC result for data operation
} __ideudmawrbufsts_bits;

/* IDE IDEUDMARdBufSts register */
typedef struct{
__REG32 HPTR   : 4;     // Head pointer in the read buffer
__REG32 TPTR   : 4;     // Tail pointer in the read buffer
__REG32 EMPTY  : 1;     // Read buffer empty status
__REG32 HOM    : 1;     // Half or more entries in read buffer
                                      // filled status
__REG32 NFULL  : 1;     // Read buffer near full status
__REG32 FULL   : 1;     // Read buffer full status
__REG32        : 4;     // Reserved, always zero
__REG32 CRC    :16;     // CRC result for data operation
} __ideudmardbufsts_bits;


/* TIMER TIMERXCONTROL register */
typedef struct{
__REG32         : 3;     // 000
__REG32 CLKSEL  : 1;     // 0 = 2KHz ; 1 = 508Khz
__REG32         : 2;     // 00
__REG32 MODE    : 1;     // 0 = free running ; 1 = periodic
__REG32 ENABLE  : 1;     // 1 = enabled
__REG32         :24;
} __timerxcontrol_bits;


/* I2S I2STXCLKCFG register */
typedef struct{
__REG32 i2s_tlrs     : 1;     // Lrckt polarity
__REG32 i2s_tckp     : 1;     // Tx bitclk polarity
__REG32 i2s_trel     : 1;     // Lrckt timing
__REG32 i2s_mstr     : 1;     // Tx audio clocks master/slave mode
__REG32 i2s_tx_nbcg  : 1;     //
__REG32 i2s_tx_bcr   : 2;     // Tx bit clock rate
__REG32              :25;
} __i2stxclkcfg_bits;

/* I2S I2SRXCLKCFG register */
typedef struct{
__REG32 i2s_rlrs     : 1;     // Lrckt polarity
__REG32 i2s_rckp     : 1;     // Rx bitclk polarity
__REG32 i2s_rrel     : 1;     // Lrckt timing
__REG32 i2s_mstr     : 1;     // Tx audio clocks master/slave mode
__REG32 i2s_rx_nbcg  : 1;     //
__REG32 i2s_rx_bcr   : 2;     // Tx bit clock rate
__REG32              :25;
} __i2srxclkcfg_bits;

/* I2S I2SGISts register */
typedef struct{
__REG32 Tx0_underflow        : 1;
__REG32 Tx1_underflow        : 1;
__REG32 Tx2_underflow        : 1;

__REG32 Rx0_overflow         : 1;
__REG32 Rx1_overflow         : 1;
__REG32 Rx2_overflow         : 1;

__REG32 Tx0_overflow         : 1;
__REG32 Tx1_overflow         : 1;
__REG32 Tx2_overflow         : 1;

__REG32 Rx0_underflow        : 1;
__REG32 Rx1_underflow        : 1;
__REG32 Rx2_underflow        : 1;

__REG32 Tx0_fifo_full        : 1;
__REG32 Tx0_fifo_empty       : 1;
__REG32 Tx0_fifo_half_empty  : 1;

__REG32 Rx0_fifo_full        : 1;
__REG32 Rx0_fifo_empty       : 1;
__REG32 Rx0_fifo_half_full   : 1;

__REG32 Tx1_fifo_full        : 1;
__REG32 Tx1_fifo_empty       : 1;
__REG32 Tx1_fifo_half_empty  : 1;

__REG32 Rx1_fifo_full        : 1;
__REG32 Rx1_fifo_empty       : 1;
__REG32 Rx1_fifo_half_full   : 1;

__REG32 Tx2_fifo_full        : 1;
__REG32 Tx2_fifo_empty       : 1;
__REG32 Tx2_fifo_half_empty  : 1;

__REG32 Rx2_fifo_full        : 1;
__REG32 Rx2_fifo_empty       : 1;
__REG32 Rx2_fifo_half_full   : 1;

__REG32                      : 2;
} __i2sglsts_bits;

/* I2S I2SGICtrl register */
typedef struct{
__REG32 i2s_ife       : 1;     // 1=Pclk is on for SAI rx/tx
__REG32 i2s_loopback  : 1;
__REG32               :30;
} __i2sglctrl_bits;

/* I2S I2STXLINCTRLDATA register */
typedef struct{
__REG32 TXDIR               : 1;     // 0=MSB first; 1=LSB first.
__REG32 TXUF_REPEAT_SAMPLE  : 1;     // Tx underflow functionality.
__REG32 Left_Right_Justify  : 1;     // Tx Justify: 0=Left; 1=Right.
__REG32                     :29;
} __i2stxlinctrldata_bits;


/* I2S I2STXCTRL register */
typedef struct{
__REG32 TXEMPTY_int_level  : 1;     // 0=irq on empty; 1=irq on half empty.
__REG32 TXUFIE             : 1;     // Tx data underflow irq enable
__REG32                    :30;
} __i2stxctrl_bits;

/* I2S I2STXWRDLEN register */
typedef struct{
__REG32 WL  : 2;     // 00=16; 01=24; 10=32 bits
__REG32     :30;
} __i2stxwrdlen_bits;

/* I2S I2STXxEN register */
typedef struct{
__REG32 i2s_txx_EN  : 1;
__REG32             :31;
} __i2stxxen_bits;

/* I2S I2SRXLINCTRLDATA register */
typedef struct{
__REG32 RXDIR               : 1;     // 0=MSB first; 1=LSB first.
__REG32 Left_Right_Justify  : 1;     // Rx Justify: 0=Left; 1=Right.
__REG32                     :30;
} __i2srxlinctrldata_bits;

/* I2S I2SRXCTRL register */
typedef struct{
__REG32 RXFull_int_level  : 1;
__REG32 ROFLIE            : 1;
__REG32                   :30;
} __i2srxctrl_bits;

/* I2S I2SRXWRDLEN register */
typedef struct{
__REG32 WL  : 2;     // 00=16; 01=24; 10=32 bits
__REG32     :30;
} __i2srxwrdlen_bits;

/* I2S I2SRXxEN register */
typedef struct{
__REG32 i2s_rxx_en  : 1;
__REG32             :31;
} __i2srxxen_bits;


/* GPIO PxDR register */
typedef struct{
__REG32 PxDATA0  : 1;
__REG32 PxDATA1  : 1;
__REG32 PxDATA2  : 1;
__REG32 PxDATA3  : 1;
__REG32 PxDATA4  : 1;
__REG32 PxDATA5  : 1;
__REG32 PxDATA6  : 1;
__REG32 PxDATA7  : 1;
__REG32          :24;
} __pxdr_bits;

/* GPIO PxDDR register */
typedef struct{
__REG32 PxDIR0  : 1;
__REG32 PxDIR1  : 1;
__REG32 PxDIR2  : 1;
__REG32 PxDIR3  : 1;
__REG32 PxDIR4  : 1;
__REG32 PxDIR5  : 1;
__REG32 PxDIR6  : 1;
__REG32 PxDIR7  : 1;
__REG32         :24;
} __pxddr_bits;

/* GPIO GPIOxINTEN register */
typedef struct{
__REG32 PxINT0  : 1;
__REG32 PxINT1  : 1;
__REG32 PxINT2  : 1;
__REG32 PxINT3  : 1;
__REG32 PxINT4  : 1;
__REG32 PxINT5  : 1;
__REG32 PxINT6  : 1;
__REG32 PxINT7  : 1;
__REG32         :24;
} __gpioxinten_bits;

/* GPIO GPIOxINTTYPE1 register */
typedef struct{
__REG32 PxINTE0  : 1;
__REG32 PxINTE1  : 1;
__REG32 PxINTE2  : 1;
__REG32 PxINTE3  : 1;
__REG32 PxINTE4  : 1;
__REG32 PxINTE5  : 1;
__REG32 PxINTE6  : 1;
__REG32 PxINTE7  : 1;
__REG32          :24;
} __gpioxinttype1_bits;

/* GPIO GPIOxINTTYPE2 register */
typedef struct{
__REG32 PxINTR0  : 1;
__REG32 PxINTR1  : 1;
__REG32 PxINTR2  : 1;
__REG32 PxINTR3  : 1;
__REG32 PxINTR4  : 1;
__REG32 PxINTR5  : 1;
__REG32 PxINTR6  : 1;
__REG32 PxINTR7  : 1;
__REG32          :24;
} __gpioxinttype2_bits;

/* GPIO GPIOxEOI register */
typedef struct{
__REG32 PxINTC0  : 1;
__REG32 PxINTC1  : 1;
__REG32 PxINTC2  : 1;
__REG32 PxINTC3  : 1;
__REG32 PxINTC4  : 1;
__REG32 PxINTC5  : 1;
__REG32 PxINTC6  : 1;
__REG32 PxINTC7  : 1;
__REG32          :24;
} __gpioxeoi_bits;

/* GPIO INTSTSx register */
typedef struct{
__REG32 PxINTS0  : 1;
__REG32 PxINTS1  : 1;
__REG32 PxINTS2  : 1;
__REG32 PxINTS3  : 1;
__REG32 PxINTS4  : 1;
__REG32 PxINTS5  : 1;
__REG32 PxINTS6  : 1;
__REG32 PxINTS7  : 1;
__REG32          :24;
} __intstsx_bits;

/* GPIO RAWINTSTSx register */
typedef struct{
__REG32 PxINTRS0  : 1;
__REG32 PxINTRS1  : 1;
__REG32 PxINTRS2  : 1;
__REG32 PxINTRS3  : 1;
__REG32 PxINTRS4  : 1;
__REG32 PxINTRS5  : 1;
__REG32 PxINTRS6  : 1;
__REG32 PxINTRS7  : 1;
__REG32           :24;
} __rawintstsx_bits;

/* GPIO GPIOxDB register */
typedef struct{
__REG32 PxINTDB0  : 1;
__REG32 PxINTDB1  : 1;
__REG32 PxINTDB2  : 1;
__REG32 PxINTDB3  : 1;
__REG32 PxINTDB4  : 1;
__REG32 PxINTDB5  : 1;
__REG32 PxINTDB6  : 1;
__REG32 PxINTDB7  : 1;
__REG32           :24;
} __gpioxdb_bits;

/* GPIO EEDRIVE register */
typedef struct{
__REG32 CLKOD  : 1;
__REG32 DATOD  : 1;
__REG32        :30;
} __eedrive_bits;


/* AC97 RXCRX register */
typedef struct{
__REG32 REN    : 1;
__REG32 RX1    : 1;
__REG32 RX2    : 1;
__REG32 RX3    : 1;
__REG32 RX4    : 1;
__REG32 RX5    : 1;
__REG32 RX6    : 1;
__REG32 RX7    : 1;
__REG32 RX8    : 1;
__REG32 RX9    : 1;
__REG32 RX10   : 1;
__REG32 RX11   : 1;
__REG32 RX12   : 1;
__REG32 RSIZE  : 2;
__REG32 CM     : 1;
__REG32 FDIS   : 1;
__REG32 TOC    :12;
__REG32        : 3;
} __ac97rxcrx_bits;


/* AC97 TXCRX register */
typedef struct{
__REG32 TEN    : 1;
__REG32 TX1    : 1;
__REG32 TX2    : 1;
__REG32 TX3    : 1;
__REG32 TX4    : 1;
__REG32 TX5    : 1;
__REG32 TX6    : 1;
__REG32 TX7    : 1;
__REG32 TX8    : 1;
__REG32 TX9    : 1;
__REG32 TX10   : 1;
__REG32 TX11   : 1;
__REG32 TX12   : 1;
__REG32 TSIZE  : 2;
__REG32 CM     : 1;
__REG32 FDIS   : 1;
__REG32        :15;
} __ac97txcrx_bits;

/* AC97 SRX register */
typedef struct{
__REG32 RXFE    : 1;
__REG32 TXFE    : 1;
__REG32 RXFF    : 1;
__REG32 TXFF    : 1;
__REG32 TXBUSY  : 1;
__REG32 RXOE    : 1;
__REG32 TXUE    : 1;
__REG32         :25;
} __ac97srx_bits;

/* AC97 RISRX register */
typedef struct{
__REG32 TCIS  : 1;
__REG32 RTIS  : 1;
__REG32 TIS   : 1;
__REG32 RIS   : 1;
__REG32       :28;
} __ac97risrx_bits;

/* AC97 ISRX register */
typedef struct{
__REG32 TCIS  : 1;
__REG32 RTIS  : 1;
__REG32 TIS   : 1;
__REG32 RIS   : 1;
__REG32       :28;
} __ac97isrx_bits;

/* AC97 IEX register */
typedef struct{
__REG32 TCIE  : 1;
__REG32 RTIE  : 1;
__REG32 TIE   : 1;
__REG32 RIE   : 1;
__REG32       :28;
} __ac97iex_bits;

/* AC97 RGIS register */
typedef struct{
__REG32 SLOT1TXCOMPLETE  : 1;
__REG32 SLOT2RXVALID     : 1;
__REG32 GPIOTXCOMPLETE   : 1;
__REG32 GPIOINT          : 1;
__REG32 WINT             : 1;
__REG32 CODECREADY       : 1;
__REG32 SLOT2TXCOMPLETE  : 1;
__REG32                  :25;
} __ac97rgis_bits;

/* AC97 GIS register */
typedef struct{
__REG32 SLOT1TXCOMPLETE  : 1;
__REG32 SLOT2RXVALID     : 1;
__REG32 GPIOTXCOMPLETE   : 1;
__REG32 GPIOINT          : 1;
__REG32 WINT             : 1;
__REG32 CODECREADY       : 1;
__REG32 SLOT2TXCOMPLETE  : 1;
__REG32                  :25;
} __ac97gis_bits;

/* AC97 IM register */
typedef struct{
__REG32 SLOT1TXCOMPLETE  : 1;
__REG32 SLOT2RXVALID     : 1;
__REG32 GPIOTXCOMPLETE   : 1;
__REG32 GPIOINT          : 1;
__REG32 WINT             : 1;
__REG32 CODECREADY       : 1;
__REG32 SLOT2TXCOMPLETE  : 1;
__REG32                  :25;
} __ac97im_bits;

/* AC97 EOI register */
typedef struct{
__REG32 WINT        : 1;
__REG32 CODECREADY  : 1;
__REG32             :30;
} __ac97eoi_bits;

/* AC97 GCR register */
typedef struct{
__REG32 AC97IFE      : 1;
__REG32 LOOP         : 1;
__REG32 OCODECReady  : 1;
__REG32              :29;
} __ac97gcr_bits;

/* AC97 RESET register */
typedef struct{
__REG32 TIMEDRESET   : 1;
__REG32 FORCEDRESET  : 1;
__REG32 EFORCER      : 1;
__REG32              :29;
} __ac97reset_bits;

/* AC97 SYNC register */
typedef struct{
__REG32 TIMEDSYNC   : 1;
__REG32 FORCEDSYNC  : 1;
__REG32 EFORCES     : 1;
__REG32             :29;
} __ac97sync_bits;

/* AC97 GCIS register */
typedef struct{
__REG32 AC97ISR1  : 4;
__REG32 AC97ISR2  : 4;
__REG32 AC97ISR3  : 4;
__REG32 AC97ISR4  : 4;
__REG32 AC97GIS   : 7;
__REG32           : 9;
} __ac97gcis_bits;


/* SSP SSPCR0 register */
typedef struct{
__REG32 DSS  : 4;     // Data size select: 0011 - 1111 (0000-0010 Reserved)
__REG32 FRF  : 2;     // Frame format: 00-10 (11 Reserved)
__REG32 SPO  : 1;     // SCLKOUT Polarity (Motorola SPI only)
__REG32 SPH  : 1;     // SCLKOUT phase (Motorola SPI only)
__REG32 SCR  : 8;     // Serial clock rate, secondary divide: 0-255
__REG32      :16;     //
} __sspcr0_bits;

/* SSP SSPCR1 register */
typedef struct{
__REG32 RIE    : 1;     // Receive FIFO interrupt enable
__REG32 TIE    : 1;     // Transmit FIFO interrupt enable
__REG32 RORIE  : 1;     // Receive FIFO overrun interrupt enable
__REG32 LBM    : 1;     // Loopback mode
__REG32 SSE    : 1;     // Synchronous serial port enable
__REG32 MS     : 1;     // Master(0)/Slave(1) select. NOTE: SSE must be 0 to modify.
__REG32 SOD    : 1;     // Slave mode output disable. NOTE: MS must be 1.
__REG32        :25;     //
} __sspcr1_bits;

/* SSP SSPSR register */
typedef struct{
__REG32 TFE  : 1;     // Transmit FIFO empty (read-only). NOTE: *FIFO* empty, not necessarily shift register
__REG32 TNF  : 1;     // Transmit FIFO not full (read-only)
__REG32 RNE  : 1;     // Receive FIFO not empty (read-only)
__REG32 RFF  : 1;     // Receive FIFO full (read-only)
__REG32 BSY  : 1;     // SSP busy flag (read-only) (TXFIFO is !empty || TX in progress || RX in progress)
__REG32      :27;     //
} __sspsr_bits;

/* SSP SSPCPCR register */
typedef struct{
__REG32 CPSDVSR  : 8;     // Clock prescale divisior. Even number 2-254. Reset to x04
__REG32          :24;     //
} __sspcpcr_bits;

/* SSP SSPIIR register */
typedef struct{
__REG32 RIS    : 1;     // Read: SSP RX FIFO service request intrpt status
__REG32 TIS    : 1;     // Read: SSP TX FIFO service request intrpt status
__REG32 RORIS  : 1;     // Read: SSP RX FIFO overrun intrpt status
__REG32        :29;     // Read:
} __sspiir_bits;


/* IRDA IRENABLE register */
typedef struct{
__REG32 EN   : 2;
__REG32 LBM  : 1;
__REG32 MD   : 1;
__REG32 FD   : 1;
__REG32      :27;
} __irenable_bits;

/* IRDA IRCTRL register */
typedef struct{
__REG32 MUX  : 1;
__REG32 BRD  : 1;
__REG32 TUS  : 1;
__REG32 TXE  : 1;
__REG32 RXE  : 1;
__REG32 TXP  : 1;
__REG32 RXP  : 1;
__REG32 AME  : 1;
__REG32      :24;
} __irctrl_bits;

/* IRDA IRADRMATCHVAL register */
typedef struct{
__REG32 AMV  : 8;
__REG32      :24;
} __iradrmatchval_bits;

/* IRDA IRFLAG register */
typedef struct{
__REG32 RAB  : 1;
__REG32 CRE  : 1;
__REG32 ROR  : 1;
__REG32 FRE  : 1;
__REG32 WST  : 2;
__REG32 E0F  : 1;     // 'EOF' is taken but 'E0F' is ok.
__REG32 RSY  : 1;
__REG32 RIF  : 1;
__REG32 TBY  : 1;
__REG32      :22;
} __irflag_bits;

/* IRDA IRRIB register */
typedef struct{
__REG32 BRAB  : 1;
__REG32 BCRE  : 1;
__REG32 BROR  : 1;
__REG32 BFRE  : 1;
__REG32 BC    :11;
__REG32       :17;
} __irrib_bits;

/* IRDA IRTR0 register */
typedef struct{
__REG32 BC  :11;
__REG32     :21;
} __irtr0_bits;

/* IRDA IRDMACR register */
typedef struct{
__REG32 RXDMAE  : 1;
__REG32 TXDMAE  : 1;
__REG32 DMAERR  : 1;
__REG32         :29;
} __irdmacr_bits;

/* IRDA SIRTR0 register */
typedef struct{
__REG32 TSIRC   : 1;
__REG32 S16CLK  : 1;
__REG32 SIRIN   : 1;
__REG32 SIRT    : 1;
__REG32 RXD     : 1;
__REG32 TXD     : 1;
__REG32 SIROUT  : 1;
__REG32 SIREN   : 1;
__REG32         :24;
} __sirtr0_bits;

/* IRDA MISR register */
typedef struct{
__REG32 TFS  : 1;
__REG32 TFC  : 1;
__REG32 TAB  : 1;
__REG32 RFS  : 1;
__REG32 RFC  : 1;
__REG32 RIL  : 1;
__REG32 RFL  : 1;
__REG32      :25;
} __misr_bits;

/* IRDA MIMR register */
typedef struct{
__REG32 TFS  : 1;
__REG32 TFC  : 1;
__REG32 TAB  : 1;
__REG32 RFS  : 1;
__REG32 RFC  : 1;
__REG32 RIL  : 1;
__REG32 RFL  : 1;
__REG32      :25;
} __mimr_bits;

/* IRDA MIIR register */
typedef struct{
__REG32 TFS  : 1;
__REG32 TFC  : 1;
__REG32 TAB  : 1;
__REG32 RFS  : 1;
__REG32 RFC  : 1;
__REG32 RIL  : 1;
__REG32 RFL  : 1;
__REG32      :25;
} __miir_bits;


/* UART UARTXRXSTS register */
typedef struct{
__REG32 FE  : 1;
__REG32 PE  : 1;
__REG32 BE  : 1;
__REG32 OE  : 1;
__REG32     :28;
} __uartxrxsts_bits;

/* UART UARTXLINCTRLHIGH register */
typedef struct{
__REG32 BRK   : 1;
__REG32 PEN   : 1;
__REG32 EPS   : 1;
__REG32 STP2  : 1;
__REG32 FEN   : 1;
__REG32 WLEN  : 2;
__REG32       :25;
} __uartxlinctrlhigh_bits;

/* UART UARTXLINCTRLMID register */
typedef struct{
__REG32 BR  : 8;
__REG32     :24;
} __uartxlinctrlmid_bits;

/* UART UARTXLINCTRLLOW register */
typedef struct{
__REG32 BR  : 8;
__REG32     :24;
} __uartxlinctrllow_bits;

/* UART UARTXCTRL register */
typedef struct{
__REG32 UARTE  : 1;
__REG32 SIREN  : 1;
__REG32 SIRLP  : 1;
__REG32 MSIE   : 1;
__REG32 RIE    : 1;
__REG32 TIE    : 1;
__REG32 RTIE   : 1;
__REG32 LBE    : 1;
__REG32        :24;
} __uartxctrl_bits;

/* UART UARTXFLAG register */
typedef struct{
__REG32 CTS   : 1;
__REG32 DSR   : 1;
__REG32 DCD   : 1;
__REG32 BUSY  : 1;
__REG32 RXFE  : 1;
__REG32 TXFF  : 1;
__REG32 RXFF  : 1;
__REG32 TXFE  : 1;
__REG32       :24;
} __uartxflag_bits;

/* UART UARTXINTIDINTCLR register */
typedef struct{
__REG32 MIS   : 1;
__REG32 RIS   : 1;
__REG32 TIS   : 1;
__REG32 RTIS  : 1;
__REG32       :28;
} __uartxintidintclr_bits;

/* UART UART2IRLOWPWRCNTR register */
typedef struct{
__REG32 ILPDW  : 8;
__REG32        :24;
} __uart2irlowpwrcntr_bits;

/* UART UARTXDMACTRL register */
typedef struct{
__REG32 RXDMAE  : 1;
__REG32 TXDMAE  : 1;
__REG32 DMAERR  : 1;
__REG32         :29;
} __uartxdmactrl_bits;

/* UART UARTXMODEMCTRL register */
typedef struct{
__REG32 DTR   : 1;
__REG32 RTS   : 1;
__REG32 OUT1  : 1;
__REG32 OUT2  : 1;
__REG32 LOOP  : 1;
__REG32       :27;
} __uartxmodemctrl_bits;

/* UART UARTXMODEMSTS register */
typedef struct{
__REG32 DCTS  : 1;
__REG32 DDSR  : 1;
__REG32 TERI  : 1;
__REG32 DDCD  : 1;
__REG32 CTS   : 1;
__REG32 DSR   : 1;
__REG32 RI    : 1;
__REG32 DCD   : 1;
__REG32       :24;
} __uartxmodemsts_bits;

/* UART UARTXHDLCCTRL register */
typedef struct{
__REG32 CRCS    : 1;     // CRC size: 0=CRC-f16, 1=CRC-32
__REG32 CRCE    : 1;     // CRC Enable for both Tx and Rx.
__REG32 TUS     : 1;     // Tx Underrun Select: 1=abort packet, 0=terminate packet.
__REG32 TXE     : 1;     // HDLC Tx Enable: 1=HDLC mode, 0=normal UART mode
__REG32 RXE     : 1;     // HDLC Rx Enable: 1=HDLC mode, 0=normal UART mode
__REG32 CRCZ    : 1;
__REG32 IDLSpc  : 1;
__REG32 AME     : 2;     // Address match enable:
                                   // 00 = No addr matching
                                   // 01 = 4 x 1 byte matching
                                   // 10 = 2 x 2 byte matching

__REG32 IDLE    : 1;     // Tx Idle mode: 1=tx continuous flags, 0=hold tx pin high.
__REG32 CRCApd  : 1;     // CRC pass thru: 1=Pass recieved CRC to the host.
__REG32 CRCN    : 1;     // CRC tx polarity: 1=CRC transmitted inverted.
__REG32 FLAG    : 4;     // Add 1 to get minimum # of opening/closing flag
                                   // for HDLC TX.

                                   // Interrupt enables:
__REG32 RTOEN   : 1;     // Rx Time Out Irq Enable
__REG32 RFLEN   : 1;     // Rx Frame Lost Irq Enable
__REG32 RILEN   : 1;     // Rx Information Lost Irq Enable
__REG32 RFCEN   : 1;     // Rx Frame Complete Irq Enable
__REG32 TABEN   : 1;     // Tx Frame Abort Irq Enable
__REG32 TFCEN   : 1;     // Tx Frame Complete Irq Enable

                                   // Sync and clock modes:
__REG32 SYNC    : 1;     // 1=synchronous HDLC for both tx and rx; 0=async.
__REG32 RXENC   : 1;     // Rx Encode Method: 1=Manchester, 0=NRZ (only if SYNC=1)
__REG32 TXENC   : 1;     // Tx Encode Method: 1=Manchester, 0=NRZ (only if SYNC=1)
__REG32 RXCM    : 1;     // Rx Clock Mode: 1=Ext, 0=Int (only if in Sync NRZ mode)
__REG32 TXCM    : 1;     // Tx Clock Mode: 1=Ext, 0=Int (only if in Sync NRZ mode)
__REG32 CMAS    : 1;     // Clock Master for both tx and rx (1=int, 0=ext)
__REG32         : 4;
} __uartxhdlcctrl_bits;

/* UART UARTXHDLCRXINFOBUF register */
typedef struct{
__REG32 BRAB   : 1;     // Buffered Reciever Abort
__REG32 BCRE   : 1;     // Buffered CRC Error
__REG32 BROR   : 1;     // Buffered Rx FIFO Overrun
__REG32 BFRE   : 1;     // Buffered Framing Error
__REG32 BC     :11;     // Recieved Frame Byte Count
__REG32        : 2;
__REG32 BPLLE  : 1;     // Buffered Digital PLL Error (Manchester only)
__REG32        :14;
} __uartxhdlcrxinfobuf_bits;

/* UART UARTXHDLCSTS register */
typedef struct{
__REG32 TFS     : 1;     // Tx FIFO Service Request
__REG32 TFC     : 1;     // Tx Frame Complete
__REG32 TAB     : 1;     // Tx Frame Aborted
__REG32 RFS     : 1;     // Rx FIFO Service Request
__REG32 RFC     : 1;     // Rx Frame Complete
__REG32 RIL     : 1;     // Rx Information Lost
__REG32 RFL     : 1;     // Rx Frame Complete
__REG32 E0F     : 1;     // End of Frame - Rx ('EOF' is taken but 'E0F' is ok).
__REG32 RTO     : 1;     // Rx Timeout
__REG32 RAB     : 1;     // Rx Abort
__REG32         : 1;
__REG32 RIF     : 1;     // Rx is in a frame
__REG32 TBY     : 1;     // Tx Busy: 1=Tx is transmitting a frame right now.
__REG32 ROR     : 1;     // Rx FIFO Overrun
__REG32 CRE     : 1;     // CRC error (rx)
__REG32 LNKIDL  : 1;
__REG32 PLLCS   : 1;     // DPLL Carrier Sense
__REG32 PLLE    : 1;     // DPLL error
__REG32         :14;
} __uartxhdlcsts_bits;


/* KEYPAD KEYSCANINIT register */
typedef struct{
__REG32 PRSCL   :12;     // Row/Column counter pre-scaler load
__REG32 TEST    : 1;     // Test mode bit
__REG32 BACK    : 1;     // Key scan back driving enable
__REG32 DIAG    : 1;     // Key scan diagnostic mode enable
__REG32 DIS3KY  : 1;     // Disable 3 key reset
__REG32 DBNC    : 8;     // Debounce start count
__REG32         : 8;     // Reserved
} __keyscaninit_bits;

/* KEYPAD KEYDIAGNOSTIC register */
typedef struct{
__REG32 DIAG  : 6;     // Diagnostic key value.
__REG32       :26;     // Reserved
} __keydiagnostic_bits;

/* KEYPAD KEYREGISTER register */
typedef struct{
__REG32 KEY1    : 6;     // Row/Column single key press value
__REG32 KEY2    : 6;     // Row/Column double key press, second value
__REG32 _1KEY   : 1;     // Indicates that at least 1 key has been detected
__REG32 _2KEYS  : 1;     // Indicates that 2 keys have been detected
__REG32 INT     : 1;     // Key interrupt
__REG32 K       : 1;     // output of key array column multiplexer. For
                                        // diagnostic testing only.
__REG32         :16;     // Reserved
} __keyregister_bits;


/* TOUCHSCREEN TSSETUP register */
typedef struct{
__REG32 SDLY   :10;
__REG32 NSMP   : 2;
__REG32 DEV    : 3;
__REG32 EN     : 1;
__REG32 DLY    :10;
__REG32        : 5;
__REG32 TDTCT  : 1;
} __tssetup_bits;

/* TOUCHSCREEN TSXYMAXMIN register */
typedef struct{
__REG32 XMIN  : 8;
__REG32 YMIN  : 8;
__REG32 XMAX  : 8;
__REG32 YMAX  : 8;
} __tsxymaxmin_bits;

/* TOUCHSCREEN TSXYRESULT register */
typedef struct{
__REG32 AD_X  :12;     // 12 bit X calculated reading
__REG32 AD    : 4;
__REG32 Y     :12;     // 12 bit Y calculated reading
__REG32       : 3;
__REG32 SDR   : 1;
} __tsxyresult_bits;

/* TOUCHSCREEN TS_BITS register */
typedef struct{
__REG32 SCTL    :29;
__REG32 SCTL29  : 1;
__REG32         : 2;
} __ts_bits;

/* TOUCHSCREEN TSSWLOCK register */
typedef struct{
__REG32 SWLCK  : 8;
__REG32        :24;
} __tsswlock_bits;

/* TOUCHSCREEN TSSETUP2 register */
typedef struct{
__REG32 TINT    : 1;
__REG32 NICOR   : 1;
__REG32 PINT    : 1;
__REG32 PENSTS  : 1;
__REG32 PINTEN  : 1;
__REG32 DEVINT  : 1;
__REG32 DINTEN  : 1;
__REG32 DTMEN   : 1;
__REG32 DISDEV  : 1;
__REG32 NSIGND  : 1;
__REG32 S28EN   : 1;
__REG32 RINTEN  : 1;
__REG32         :20;
} __tssetup2_bits;


/* PWM PWMXEN register */
typedef struct{
__REG32 EN  : 1;
__REG32     :31;
} __pwmxen_bits;

/* PWM PWMXINVERT register */
typedef struct{
__REG32 INV  : 1;
__REG32      :31;
} __pwmxinvert_bits;


/* RTC RTCSTS register */
typedef struct{
__REG32 INTR  : 1;
__REG32       :31;
} __rtcsts_bits;

/* RTC RTCCTRL register */
typedef struct{
__REG32 MIE  : 1;
__REG32      :31;
} __rtcctrl_bits;

/* RTC RTCSWCOMP register */
typedef struct{
__REG32 INT  :16;
__REG32 DEL  : 5;
__REG32      :11;
} __rtcswcomp_bits;


/* WATCHDOG TIMER WATCHDOG register */
typedef struct{
__REG32 WD      : 1;
__REG32 _3KRST  : 1;
__REG32 URST    : 1;
__REG32 HWDIS   : 1;
__REG32 SWDIS   : 1;
__REG32 OVRID   : 1;
__REG32 PLSDSN  : 1;
__REG32 CTL     : 9;
__REG32         :16;
} __watchdog_bits;

/* WATCHDOG TIMER WDSTATUS register */
typedef struct{
__REG32 STAT  : 7;
__REG32       :25;
} __wdstatus_bits;



#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 ** DMA
 **
 ***************************************************************************/
__IO_REG32_BIT(DMAChArb,                     0x80000380,__READ_WRITE,__dmacharb_bits);
__IO_REG32_BIT(DMAGlInt,                     0x800003c0,__READ_WRITE,__dmaglint_bits);

__IO_REG32_BIT(M2P0_CONTROL,                 0x80000000,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P0_INTERRUPT,               0x80000004,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P0_PPALLOC,                 0x80000008,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P0_STATUS,                  0x8000000C,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P0_REMAIN,                  0x80000014,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P0_MAXCNT0,                 0x80000020,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P0_BASE0,                   0x80000024,__READ_WRITE);
__IO_REG32(    M2P0_CURRENT0,                0x80000028,__READ      );
__IO_REG32_BIT(M2P0_MAXCNT1,                 0x80000030,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P0_BASE1,                   0x80000034,__READ_WRITE);
__IO_REG32(    M2P0_CURRENT1,                0x80000038,__READ      );

__IO_REG32_BIT(M2P1_CONTROL,                 0x80000040,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P1_INTERRUPT,               0x80000044,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P1_PPALLOC,                 0x80000048,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P1_STATUS,                  0x8000004c,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P1_REMAIN,                  0x80000054,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P1_MAXCNT0,                 0x80000060,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P1_BASE0,                   0x80000064,__READ_WRITE);
__IO_REG32(    M2P1_CURRENT0,                0x80000068,__READ      );
__IO_REG32_BIT(M2P1_MAXCNT1,                 0x80000070,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P1_BASE1,                   0x80000074,__READ_WRITE);
__IO_REG32(    M2P1_CURRENT1,                0x80000078,__READ      );

__IO_REG32_BIT(M2P2_CONTROL,                 0x80000080,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P2_INTERRUPT,               0x80000084,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P2_PPALLOC,                 0x80000088,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P2_STATUS,                  0x8000008c,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P2_REMAIN,                  0x80000094,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P2_MAXCNT0,                 0x800000a0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P2_BASE0,                   0x800000a4,__READ_WRITE);
__IO_REG32(    M2P2_CURRENT0,                0x800000a8,__READ      );
__IO_REG32_BIT(M2P2_MAXCNT1,                 0x800000b0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P2_BASE1,                   0x800000b4,__READ_WRITE);
__IO_REG32(    M2P2_CURRENT1,                0x800000b8,__READ      );

__IO_REG32_BIT(M2P3_CONTROL,                 0x800000c0,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P3_INTERRUPT,               0x800000c4,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P3_PPALLOC,                 0x800000c8,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P3_STATUS,                  0x800000cc,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P3_REMAIN,                  0x800000d4,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P3_MAXCNT0,                 0x800000e0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P3_BASE0,                   0x800000e4,__READ_WRITE);
__IO_REG32(    M2P3_CURRENT0,                0x800000e8,__READ      );
__IO_REG32_BIT(M2P3_MAXCNT1,                 0x800000f0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P3_BASE1,                   0x800000f4,__READ_WRITE);
__IO_REG32(    M2P3_CURRENT1,                0x800000f8,__READ      );

__IO_REG32_BIT(M2P4_CONTROL,                 0x80000240,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P4_INTERRUPT,               0x80000244,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P4_PPALLOC,                 0x80000248,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P4_STATUS,                  0x8000024c,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P4_REMAIN,                  0x80000254,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P4_MAXCNT0,                 0x80000260,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P4_BASE0,                   0x80000264,__READ_WRITE);
__IO_REG32(    M2P4_CURRENT0,                0x80000268,__READ      );
__IO_REG32_BIT(M2P4_MAXCNT1,                 0x80000270,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P4_BASE1,                   0x80000274,__READ_WRITE);
__IO_REG32(    M2P4_CURRENT1,                0x80000278,__READ      );

__IO_REG32_BIT(M2P5_CONTROL,                 0x80000200,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P5_INTERRUPT,               0x80000204,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P5_PPALLOC,                 0x80000208,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P5_STATUS,                  0x8000020c,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P5_REMAIN,                  0x80000214,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P5_MAXCNT0,                 0x80000220,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P5_BASE0,                   0x80000224,__READ_WRITE);
__IO_REG32(    M2P5_CURRENT0,                0x80000228,__READ      );
__IO_REG32_BIT(M2P5_MAXCNT1,                 0x80000230,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P5_BASE1,                   0x80000234,__READ_WRITE);
__IO_REG32(    M2P5_CURRENT1,                0x80000238,__READ      );

__IO_REG32_BIT(M2P6_CONTROL,                 0x800002c0,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P6_INTERRUPT,               0x800002c4,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P6_PPALLOC,                 0x800002c8,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P6_STATUS,                  0x800002cc,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P6_REMAIN,                  0x800002d4,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P6_MAXCNT0,                 0x800002e0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P6_BASE0,                   0x800002e4,__READ_WRITE);
__IO_REG32(    M2P6_CURRENT0,                0x800002e8,__READ      );
__IO_REG32_BIT(M2P6_MAXCNT1,                 0x800002f0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P6_BASE1,                   0x800002f4,__READ_WRITE);
__IO_REG32(    M2P6_CURRENT1,                0x800002f8,__READ      );

__IO_REG32_BIT(M2P7_CONTROL,                 0x80000280,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P7_INTERRUPT,               0x80000284,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P7_PPALLOC,                 0x80000288,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P7_STATUS,                  0x8000028c,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P7_REMAIN,                  0x80000294,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P7_MAXCNT0,                 0x800002a0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P7_BASE0,                   0x800002a4,__READ_WRITE);
__IO_REG32(    M2P7_CURRENT0,                0x800002a8,__READ      );
__IO_REG32_BIT(M2P7_MAXCNT1,                 0x800002b0,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P7_BASE1,                   0x800002b4,__READ_WRITE);
__IO_REG32(    M2P7_CURRENT1,                0x800002b8,__READ      );

__IO_REG32_BIT(M2P8_CONTROL,                 0x80000340,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P8_INTERRUPT,               0x80000344,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P8_PPALLOC,                 0x80000348,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P8_STATUS,                  0x8000034c,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P8_REMAIN,                  0x80000354,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P8_MAXCNT0,                 0x80000360,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P8_BASE0,                   0x80000364,__READ_WRITE);
__IO_REG32(    M2P8_CURRENT0,                0x80000368,__READ      );
__IO_REG32_BIT(M2P8_MAXCNT1,                 0x80000370,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P8_BASE1,                   0x80000374,__READ_WRITE);
__IO_REG32(    M2P8_CURRENT1,                0x80000378,__READ      );

__IO_REG32_BIT(M2P9_CONTROL,                 0x80000300,__READ_WRITE,__m2pcontrol_bits);
__IO_REG32_BIT(M2P9_INTERRUPT,               0x80000304,__READ_WRITE,__m2pinterrupt_bits);
__IO_REG32_BIT(M2P9_PPALLOC,                 0x80000308,__READ_WRITE,__ppalloc_bits);
__IO_REG32_BIT(M2P9_STATUS,                  0x8000030c,__READ      ,__m2pstatus_bits);
__IO_REG32_BIT(M2P9_REMAIN,                  0x80000314,__READ      ,__remain_bits);
__IO_REG32_BIT(M2P9_MAXCNT0,                 0x80000320,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P9_BASE0,                   0x80000324,__READ_WRITE);
__IO_REG32(    M2P9_CURRENT0,                0x80000328,__READ      );
__IO_REG32_BIT(M2P9_MAXCNT1,                 0x80000330,__READ_WRITE,__maxcnt_bits);
__IO_REG32(    M2P9_BASE1,                   0x80000334,__READ_WRITE);
__IO_REG32(    M2P9_CURRENT1,                0x80000338,__READ      );

__IO_REG32_BIT(M2M0_CONTROL,                 0x80000100,__READ_WRITE,__m2mcontrol_bits);
__IO_REG32_BIT(M2M0_INTERRUPT,               0x80000104,__READ_WRITE,__m2minterrupt_bits);
__IO_REG32_BIT(M2M0_STATUS,                  0x8000010c,__READ      ,__m2mstatus_bits);
__IO_REG32_BIT(M2M0_BCR0,                    0x80000110,__READ_WRITE,__bcrx_bits);
__IO_REG32_BIT(M2M0_BCR1,                    0x80000114,__READ_WRITE,__bcrx_bits);
__IO_REG32(    M2M0_SAR_BASE0,               0x80000118,__READ_WRITE);
__IO_REG32(    M2M0_SAR_BASE1,               0x8000011C,__READ_WRITE);
__IO_REG32(    M2M0_SAR_CURRENT0,            0x80000124,__READ);
__IO_REG32(    M2M0_SAR_CURRENT1,            0x80000128,__READ);
__IO_REG32(    M2M0_DAR_BASE0,               0x8000012C,__READ_WRITE);
__IO_REG32(    M2M0_DAR_BASE1,               0x80000130,__READ_WRITE);
__IO_REG32(    M2M0_DAR_CURRENT0,            0x80000134,__READ);
__IO_REG32(    M2M0_DAR_CURRENT1,            0x8000013C,__READ);

__IO_REG32_BIT(M2M1_CONTROL,                 0x80000140,__READ_WRITE,__m2mcontrol_bits);
__IO_REG32_BIT(M2M1_INTERRUPT,               0x80000144,__READ_WRITE,__m2minterrupt_bits);
__IO_REG32_BIT(M2M1_STATUS,                  0x8000014c,__READ      ,__m2mstatus_bits);
__IO_REG32_BIT(M2M1_BCR0,                    0x80000150,__READ_WRITE,__bcrx_bits);
__IO_REG32_BIT(M2M1_BCR1,                    0x80000154,__READ_WRITE,__bcrx_bits);
__IO_REG32(    M2M1_SAR_BASE0,               0x80000158,__READ_WRITE);
__IO_REG32(    M2M1_SAR_BASE1,               0x8000015C,__READ_WRITE);
__IO_REG32(    M2M1_SAR_CURRENT0,            0x80000164,__READ);
__IO_REG32(    M2M1_SAR_CURRENT1,            0x80000168,__READ);
__IO_REG32(    M2M1_DAR_BASE0,               0x8000016C,__READ_WRITE);
__IO_REG32(    M2M1_DAR_BASE1,               0x80000170,__READ_WRITE);
__IO_REG32(    M2M1_DAR_CURRENT0,            0x80000174,__READ);
__IO_REG32(    M2M1_DAR_CURRENT1,            0x8000017C,__READ);


/***************************************************************************
 **
 ** Ethernet controller
 **
 ***************************************************************************/
__IO_REG32_BIT(RXCtl,                        0x80010000,__READ_WRITE,__rxctl_bits);
__IO_REG32_BIT(TXCtl,                        0x80010004,__READ_WRITE,__txctl_bits);
__IO_REG32_BIT(TestCtl,                      0x80010008,__READ_WRITE,__testctl_bits);
__IO_REG32_BIT(MIICmd,                       0x80010010,__READ_WRITE,__miicmd_bits);
__IO_REG32_BIT(MIIData,                      0x80010014,__READ_WRITE,__miidata_bits);
__IO_REG32_BIT(MIISts,                       0x80010018,__READ_WRITE,__miists_bits);
__IO_REG32_BIT(SelfCtl,                      0x80010020,__READ_WRITE,__selfctl_bits);
__IO_REG32_BIT(IntEn,                        0x80010024,__READ_WRITE,__inten_bits);
__IO_REG32_BIT(IntStsP,                      0x80010028,__READ_WRITE,__intstspc_bits);
__IO_REG32_BIT(IntStsC,                      0x8001002C,__READ      ,__intstspc_bits);
__IO_REG32_BIT(DiagAd,                       0x80010038,__READ_WRITE,__diagad_bits);
__IO_REG32(    DiagDa,                       0x8001003C,__READ_WRITE);
__IO_REG32_BIT(GT,                           0x80010040,__READ_WRITE,__gt_bits);
__IO_REG32_BIT(FCT,                          0x80010044,__READ_WRITE,__fct_bits);
__IO_REG32_BIT(FCF,                          0x80010048,__READ_WRITE,__fcf_bits);
__IO_REG32_BIT(AFP,                          0x8001004C,__READ_WRITE,__afp_bits);
__IO_REG32_BIT(GlIntSts,                     0x80010060,__READ_WRITE,__intsts_bits);
__IO_REG32_BIT(GlIntMsk,                     0x80010064,__READ_WRITE,__intsts_bits);
__IO_REG32_BIT(GlIntROSts,                   0x80010068,__READ_WRITE,__intsts_bits);
__IO_REG32_BIT(GlIntFrc,                     0x8001006C,__READ_WRITE,__intsts_bits);
__IO_REG32_BIT(TXCollCnt,                    0x80010070,__READ_WRITE,__txcollcnt_bits);
__IO_REG32_BIT(RXMissCnt,                    0x80010074,__READ_WRITE,__rxmisscnt_bits);
__IO_REG32_BIT(RXRuntCnt,                    0x80010078,__READ_WRITE,__rxruntcnt_bits);
__IO_REG32_BIT(BMCtl,                        0x80010080,__READ_WRITE,__bmctl_bits);
__IO_REG32_BIT(BMSts,                        0x80010084,__READ_WRITE,__bmsts_bits);
__IO_REG32(    RXBCA,                        0x80010088,__READ_WRITE);
__IO_REG32(    RXDQBAdd,                     0x80010090,__READ_WRITE);
__IO_REG16(    RXDQBLen,                     0x80010094,__READ_WRITE);
__IO_REG16(    RXDQCurLen,                   0x80010096,__READ_WRITE);
__IO_REG32(    RXDCurAdd,                    0x80010098,__READ_WRITE);
__IO_REG32_BIT(RXDEnq,                       0x8001009C,__READ_WRITE,__rxdenq_bits);
__IO_REG32(    RXStsQBAdd,                   0x800100A0,__READ_WRITE);
__IO_REG16(    RXStsQBLen,                   0x800100A4,__READ_WRITE);
__IO_REG16(    RXStsQCurLen,                 0x800100A6,__READ_WRITE);
__IO_REG32(    RXStsQCurAdd,                 0x800100A8,__READ_WRITE);
__IO_REG32_BIT(RXStsEnq,                     0x800100AC,__READ_WRITE,__rxstsenq_bits);
__IO_REG32(    TXDQBAdd,                     0x800100B0,__READ_WRITE);
__IO_REG16(    TXDQBLen,                     0x800100B4,__READ_WRITE);
__IO_REG16(    TXDQCurLen,                   0x800100B6,__READ_WRITE);
__IO_REG32(    TXDQCurAdd,                   0x800100B8,__READ_WRITE);
__IO_REG32_BIT(TXDEnq,                       0x800100BC,__READ_WRITE,__txdenq_bits);
__IO_REG32(    TXStsQBAdd,                   0x800100C0,__READ_WRITE);
__IO_REG16(    TXStsQBLen,                   0x800100C4,__READ_WRITE);
__IO_REG16(    TXStsQCurLen,                 0x800100C6,__READ_WRITE);
__IO_REG32(    TXStsQCurAdd,                 0x800100C8,__READ_WRITE);
__IO_REG32_BIT(RXBufThrshld,                 0x800100D0,__READ_WRITE,__rxbufthrshld_bits);
__IO_REG32_BIT(TXBufThrshld,                 0x800100D4,__READ_WRITE,__txbufthrshld_bits);
__IO_REG32_BIT(RXStsThrshld,                 0x800100D8,__READ_WRITE,__rxststhrshld_bits);
__IO_REG32_BIT(TXStsThrshld,                 0x800100DC,__READ_WRITE,__txststhrshld_bits);
__IO_REG32_BIT(RXDThrshld,                   0x800100E0,__READ_WRITE,__rxdthrshld_bits);
__IO_REG32_BIT(TXDThrshld,                   0x800100E4,__READ_WRITE,__txdthrshld_bits);
__IO_REG32_BIT(MaxFrmLen,                    0x800100E8,__READ_WRITE,__maxfrmlen_bits);
__IO_REG32_BIT(RXHdrLen,                     0x800100EC,__READ_WRITE,__rxhdrlen_bits);
__IO_REG32(    MACCfg0,                      0x80010100,__READ_WRITE);
__IO_REG32(    MACCfg1,                      0x80010104,__READ_WRITE);
__IO_REG32(    MACCfg2,                      0x80010108,__READ_WRITE);
__IO_REG32(    MACCfg3,                      0x8001010C,__READ_WRITE);

/***************************************************************************
 **
 ** USB
 **
 ***************************************************************************/

__IO_REG32_BIT(HcRevision,                   0x80020000,__READ_WRITE,__hcrevision_bits);
__IO_REG32_BIT(HcControl,                    0x80020004,__READ_WRITE,__hccontrol_bits);
__IO_REG32_BIT(HcCommandStatus,              0x80020008,__READ_WRITE,__hccommandstatus_bits);
__IO_REG32_BIT(HcInterruptStatus,            0x8002000C,__READ_WRITE,__hcinterruptstatus_bits);
__IO_REG32_BIT(HcInterruptEnable,            0x80020010,__READ_WRITE,__hcinterruptenable_bits);
__IO_REG32_BIT(HcInterruptDis,               0x80020014,__READ_WRITE,__hcinterruptenable_bits);
__IO_REG32_BIT(HcHCCA,                       0x80020018,__READ_WRITE,__hchcca_bits);
__IO_REG32_BIT(HcPeriodCurrentED,            0x8002001C,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcControlHeadED,              0x80020020,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcControlCurrentED,           0x80020024,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcBulkHeadED,                 0x80020028,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcBulkCurrentED,              0x8002002C,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcDoneHead,                   0x80020030,__READ_WRITE,__currented_bits);
__IO_REG32_BIT(HcFmInterval,                 0x80020034,__READ_WRITE,__hcfminterval_bits);
__IO_REG32_BIT(HcFmRemaining,                0x80020038,__READ_WRITE,__hcfmremaining_bits);
__IO_REG32_BIT(HcFmNumber,                   0x8002003C,__READ_WRITE,__hcfmnumber_bits);
__IO_REG32_BIT(HcPeriodicStart,              0x80020040,__READ_WRITE,__hcperiodicstart_bits);
__IO_REG32_BIT(HcLSThreshold,                0x80020044,__READ_WRITE,__hclsthreshold_bits);
__IO_REG32_BIT(HcRhDescriptorA,              0x80020048,__READ_WRITE,__hcrhdescriptora_bits);
__IO_REG32_BIT(HcRhDescriptorB,              0x8002004C,__READ_WRITE,__hcrhdescriptorb_bits);
__IO_REG32_BIT(HcRhStatus,                   0x80020050,__READ_WRITE,__hcrhstatus_bits);
__IO_REG32_BIT(HcRhPortStatus1,              0x80020054,__READ_WRITE,__hcrhportstatus_bits);
__IO_REG32_BIT(HcRhPortStatus2,              0x80020058,__READ_WRITE,__hcrhportstatus_bits);
__IO_REG32_BIT(HcRhPortStatus3,              0x8002005C,__READ_WRITE,__hcrhportstatus_bits);
__IO_REG32_BIT(USBCfgCtrl,                   0x80020080,__READ_WRITE,__usbcfgctrl_bits);
__IO_REG32_BIT(USBHCISts,                    0x80020084,__READ_WRITE,__usbhcists_bits);


/***************************************************************************
 **
 ** Raster engine
 **
 ***************************************************************************/
__IO_REG32_BIT(VLinesTotal,                  0x80030000,__READ_WRITE,__total_bits);
__IO_REG32_BIT(VSyncStrtStop,                0x80030004,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(VActiveStrtStop,              0x80030008,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(VBlankStrtStop,               0x80030228,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(VClkStrtStop,                 0x8003000c,__READ_WRITE,__strtstop_bits);

__IO_REG32_BIT(HClkTotal,                    0x80030010,__READ_WRITE,__total_bits);
__IO_REG32_BIT(HSyncStrtStop,                0x80030014,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(HActiveStrtStop,              0x80030018,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(HBlankStrtStop,               0x8003022c,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(HClkStrtStop,                 0x8003001c,__READ_WRITE,__strtstop_bits);

__IO_REG32_BIT(Brightness,                   0x80030020,__READ_WRITE,__brightness_bits);

__IO_REG32_BIT(VideoAttribs,                 0x80030024,__READ_WRITE,__videoattribs_bits);
__IO_REG32_BIT(VidScrnPage,                  0x80030028,__READ_WRITE,__scrnpage_bits);
__IO_REG32_BIT(VidScrnHPage,                 0x8003002c,__READ_WRITE,__scrnpage_bits);
__IO_REG32_BIT(ScrnLines,                    0x80030030,__READ_WRITE,__scrnlines_bits);
__IO_REG32_BIT(LineLength,                   0x80030034,__READ_WRITE,__linelength_bits);
__IO_REG32_BIT(VLineStep,                    0x80030038,__READ_WRITE,__step_bits);
__IO_REG32_BIT(LineCarry,                    0x8003003c,__READ_WRITE,__carry_bits);
__IO_REG32_BIT(BlinkRate,                    0x80030040,__READ_WRITE,__blinkrate_bits);
__IO_REG32_BIT(BlinkMask,                    0x80030044,__READ_WRITE,__blinkmask_bits);
__IO_REG32_BIT(BlinkPattrn,                  0x80030048,__READ_WRITE,__blinkpattrn_bits);
__IO_REG32_BIT(PattrnMask,                   0x8003004c,__READ_WRITE,__pattrnmask_bits);
__IO_REG32_BIT(BkgrndOffset,                 0x80030050,__READ_WRITE,__bkgrndoffset_bits);
__IO_REG32_BIT(Pixelmode,                    0x80030054,__READ_WRITE,__pixelmode_bits);
__IO_REG32_BIT(ParllIfOut,                   0x80030058,__READ_WRITE,__parllifout_bits);
__IO_REG32_BIT(ParllIfIn,                    0x8003005c,__READ_WRITE,__parllifin_bits);
__IO_REG32(    CursorAdrStart,               0x80030060,__READ_WRITE);
__IO_REG32(    CursorAdrReset,               0x80030064,__READ_WRITE);
__IO_REG32_BIT(CursorSize,                   0x80030068,__READ_WRITE,__cursorsize_bits);
__IO_REG32_BIT(CursorColor1,                 0x8003006c,__READ_WRITE,__cursorcolor_bits);
__IO_REG32_BIT(CursorColor2,                 0x80030070,__READ_WRITE,__cursorcolor_bits);
__IO_REG32_BIT(CursorXYLoc,                  0x80030074,__READ_WRITE,__cursorxyloc_bits);
__IO_REG32_BIT(CursorDScanLHYLoc,            0x80030078,__READ_WRITE,__cursordscanlhyloc_bits);
__IO_REG32_BIT(CursorBlinkColor1,            0x8003021c,__READ_WRITE,__cursorcolor_bits);
__IO_REG32_BIT(CursorBlinkColor2,            0x80030220,__READ_WRITE,__cursorcolor_bits);
__IO_REG32_BIT(CursorBlinkRateCtrl,          0x80030224,__READ_WRITE,__cursorblinkratectrl_bits);
__IO_REG32_BIT(RasterSWLock,                 0x8003007c,__READ_WRITE,__swlock_bits);
__IO_REG32_BIT(VidSigRsltVal,                0x80030200,__READ_WRITE,__vidsigrsltval_bits);
__IO_REG32_BIT(VidSigCtrl,                   0x80030204,__READ_WRITE,__vidsigctrl_bits);
__IO_REG32_BIT(VSigStrtStop,                 0x80030208,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(HSigStrtStop,                 0x8003020c,__READ_WRITE,__strtstop_bits);
__IO_REG32_BIT(SigClrStr,                    0x80030210,__READ_WRITE,__sigclrstr_bits);
__IO_REG32_BIT(ACRate,                       0x80030214,__READ_WRITE,__acrate_bits);
__IO_REG32_BIT(LUTSwCtrl,                    0x80030218,__READ_WRITE,__lutswctrl_bits);
__IO_REG32_BIT(EOLOffset,                    0x80030230,__READ_WRITE,__offset_bits);
__IO_REG32_BIT(FIFOLevel,                    0x80030234,__READ_WRITE,__fifolevel_bits);
__IO_REG32_BIT(ColorLUT,                     0x80030400,__READ_WRITE,__colorlut_bits);

__IO_REG32_BIT(GrySclLUTR,                   0x80030080,__READ_WRITE,__gryscllut_bits);
__IO_REG32_BIT(GrySclLUTG,                   0x80030280,__READ_WRITE,__gryscllut_bits);
__IO_REG32_BIT(GrySclLUTB,                   0x80030300,__READ_WRITE,__gryscllut_bits);


/***************************************************************************
 **
 ** SDRAM registers
 **
 ***************************************************************************/
__IO_REG32_BIT(GIConfig,                     0x80060004,__READ_WRITE,__giconfig_bits);
__IO_REG32(    RefrshTimr,                   0x80060008,__READ_WRITE);
__IO_REG32_BIT(BootSts,                      0x8006000c,__READ_WRITE,__bootsts_bits);
__IO_REG32_BIT(SDRAMDevCfg0,                 0x80060010,__READ_WRITE,__sdramdevcfgx_bits);
__IO_REG32_BIT(SDRAMDevCfg1,                 0x80060014,__READ_WRITE,__sdramdevcfgx_bits);
__IO_REG32_BIT(SDRAMDevCfg2,                 0x80060018,__READ_WRITE,__sdramdevcfgx_bits);
__IO_REG32_BIT(SDRAMDevCfg3,                 0x8006001c,__READ_WRITE,__sdramdevcfgx_bits);


/***************************************************************************
 **
 ** SMC Control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(SMCBCR0,                      0x80080000,__READ_WRITE,__smcbcrx_bits);
__IO_REG32_BIT(SMCBCR1,                      0x80080004,__READ_WRITE,__smcbcrx_bits);
__IO_REG32_BIT(SMCBCR2,                      0x80080008,__READ_WRITE,__smcbcrx_bits);
__IO_REG32_BIT(SMCBCR3,                      0x8008000c,__READ_WRITE,__smcbcrx_bits);
__IO_REG32_BIT(SMCBCR6,                      0x80080018,__READ_WRITE,__smcbcrx_bits);
__IO_REG32_BIT(SMCBCR7,                      0x8008001c,__READ_WRITE,__smcbcrx_bits);

/***************************************************************************
 **
 ** IDE Control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(IDECtrl,                      0x800A0000,__READ_WRITE,__idectrl_bits);
__IO_REG32_BIT(IDECfg,                       0x800A0004,__READ_WRITE,__idecfg_bits);
__IO_REG32_BIT(IDEMDMAOp,                    0x800A0008,__READ_WRITE,__idemdmaop_bits);
__IO_REG32_BIT(IDEUDMAOp,                    0x800A000c,__READ_WRITE,__ideudmaop_bits);
__IO_REG32(    IDEDataOut,                   0x800A0010,__READ_WRITE);
__IO_REG32(    IDEDataIn,                    0x800A0014,__READ      );
__IO_REG32(    IDEMDMADataOut,               0x800A0018,__WRITE     );
__IO_REG32(    IDEMDMADataIn,                0x800A001c,__READ      );
__IO_REG32(    IDEUDMADataOut,               0x800A0020,__WRITE     );
__IO_REG32(    IDEUDMADataIn,                0x800A0024,__READ      );
__IO_REG32_BIT(IDEUDMASts,                   0x800A0028,__READ_WRITE,__ideudmasts_bits);
__IO_REG32_BIT(IDEUDMADebug,                 0x800A002c,__READ_WRITE,__ideudmadebug_bits);
__IO_REG32_BIT(IDEUDMAWrBufSts,              0x800A0030,__READ      ,__ideudmawrbufsts_bits);
__IO_REG32_BIT(IDEUDMARdBufSts,              0x800A0034,__READ      ,__ideudmardbufsts_bits);


/***************************************************************************
 **
 ** VIC1
 **
 ***************************************************************************/
__IO_REG32_BIT(VIC1IRQStatus,                0x800b0000,__READ      ,__vic1int_bits);
__IO_REG32_BIT(VIC1FIQStatus,                0x800b0004,__READ      ,__vic1int_bits);
__IO_REG32_BIT(VIC1RawIntr,                  0x800b0008,__READ      ,__vic1int_bits);
__IO_REG32_BIT(VIC1IntSelect,                0x800b000c,__READ_WRITE,__vic1int_bits);
__IO_REG32_BIT(VIC1IntEnable,                0x800b0010,__READ_WRITE,__vic1int_bits);
__IO_REG32_BIT(VIC1IntEnClear,               0x800b0014,__WRITE     ,__vic1int_bits);
__IO_REG32_BIT(VIC1SoftInt,                  0x800b0018,__READ_WRITE,__vic1int_bits);
__IO_REG32_BIT(VIC1SoftIntClear,             0x800b001c,__READ_WRITE,__vic1int_bits);
__IO_REG32_BIT(VIC1Protection,               0x800b0020,__READ_WRITE,__vicprotection_bits);
__IO_REG32(    VIC1VectAddr,                 0x800b0030,__READ_WRITE);
__IO_REG32(    VIC1DefVectAddr,              0x800b0034,__READ_WRITE);
__IO_REG32(    VIC1VectAddr0,                0x800b0100,__READ_WRITE);
__IO_REG32(    VIC1VectAddr1,                0x800b0104,__READ_WRITE);
__IO_REG32(    VIC1VectAddr2,                0x800b0108,__READ_WRITE);
__IO_REG32(    VIC1VectAddr3,                0x800b010c,__READ_WRITE);
__IO_REG32(    VIC1VectAddr4,                0x800b0110,__READ_WRITE);
__IO_REG32(    VIC1VectAddr5,                0x800b0114,__READ_WRITE);
__IO_REG32(    VIC1VectAddr6,                0x800b0118,__READ_WRITE);
__IO_REG32(    VIC1VectAddr7,                0x800b011c,__READ_WRITE);
__IO_REG32(    VIC1VectAddr8,                0x800b0120,__READ_WRITE);
__IO_REG32(    VIC1VectAddr9,                0x800b0124,__READ_WRITE);
__IO_REG32(    VIC1VectAddr10,               0x800b0128,__READ_WRITE);
__IO_REG32(    VIC1VectAddr11,               0x800b012c,__READ_WRITE);
__IO_REG32(    VIC1VectAddr12,               0x800b0130,__READ_WRITE);
__IO_REG32(    VIC1VectAddr13,               0x800b0134,__READ_WRITE);
__IO_REG32(    VIC1VectAddr14,               0x800b0138,__READ_WRITE);
__IO_REG32(    VIC1VectAddr15,               0x800b013c,__READ_WRITE);
__IO_REG32_BIT(VIC1VectCntl0,                0x800b0200,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl1,                0x800b0204,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl2,                0x800b0208,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl3,                0x800b020c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl4,                0x800b0210,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl5,                0x800b0214,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl6,                0x800b0218,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl7,                0x800b021c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl8,                0x800b0220,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl9,                0x800b0224,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl10,               0x800b0228,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl11,               0x800b022c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl12,               0x800b0230,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl13,               0x800b0234,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl14,               0x800b0238,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC1VectCntl15,               0x800b023c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32(    VIC1PeriphID0,                0x800b0fe0,__READ      );
__IO_REG32(    VIC1PeriphID1,                0x800b0fe4,__READ      );
__IO_REG32(    VIC1PeriphID2,                0x800b0fe8,__READ      );
__IO_REG32(    VIC1PeriphID3,                0x800b0fec,__READ      );


/***************************************************************************
 **
 ** VIC2
 **
 ***************************************************************************/
__IO_REG32_BIT(VIC2IRQStatus,                0x800c0000,__READ      ,__vic2int_bits);
__IO_REG32_BIT(VIC2FIQStatus,                0x800c0004,__READ      ,__vic2int_bits);
__IO_REG32_BIT(VIC2RawIntr,                  0x800c0008,__READ      ,__vic2int_bits);
__IO_REG32_BIT(VIC2IntSelect,                0x800c000c,__READ_WRITE,__vic2int_bits);
__IO_REG32_BIT(VIC2IntEnable,                0x800c0010,__READ_WRITE,__vic2int_bits);
__IO_REG32_BIT(VIC2IntEnClear,               0x800c0014,__WRITE     ,__vic2int_bits);
__IO_REG32_BIT(VIC2SoftInt,                  0x800c0018,__READ_WRITE,__vic2int_bits);
__IO_REG32_BIT(VIC2SoftIntClear,             0x800c001c,__READ_WRITE,__vic2int_bits);
__IO_REG32_BIT(VIC2Protection,               0x800c0020,__READ_WRITE,__vicprotection_bits);
__IO_REG32(    VIC2VectAddr,                 0x800c0030,__READ_WRITE);
__IO_REG32(    VIC2DEFVectAddr,              0x800c0034,__READ_WRITE);
__IO_REG32(    VIC2VectAddr0,                0x800c0100,__READ_WRITE);
__IO_REG32(    VIC2VectAddr1,                0x800c0104,__READ_WRITE);
__IO_REG32(    VIC2VectAddr2,                0x800c0108,__READ_WRITE);
__IO_REG32(    VIC2VectAddr3,                0x800c010c,__READ_WRITE);
__IO_REG32(    VIC2VectAddr4,                0x800c0110,__READ_WRITE);
__IO_REG32(    VIC2VectAddr5,                0x800c0114,__READ_WRITE);
__IO_REG32(    VIC2VectAddr6,                0x800c0118,__READ_WRITE);
__IO_REG32(    VIC2VectAddr7,                0x800c011c,__READ_WRITE);
__IO_REG32(    VIC2VectAddr8,                0x800c0120,__READ_WRITE);
__IO_REG32(    VIC2VectAddr9,                0x800c0124,__READ_WRITE);
__IO_REG32(    VIC2VectAddr10,               0x800c0128,__READ_WRITE);
__IO_REG32(    VIC2VectAddr11,               0x800c012c,__READ_WRITE);
__IO_REG32(    VIC2VectAddr12,               0x800c0130,__READ_WRITE);
__IO_REG32(    VIC2VectAddr13,               0x800c0134,__READ_WRITE);
__IO_REG32(    VIC2VectAddr14,               0x800c0138,__READ_WRITE);
__IO_REG32(    VIC2VectAddr15,               0x800c013c,__READ_WRITE);
__IO_REG32_BIT(VIC2VectCntl0,                0x800c0200,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl1,                0x800c0204,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl2,                0x800c0208,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl3,                0x800c020c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl4,                0x800c0210,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl5,                0x800c0214,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl6,                0x800c0218,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl7,                0x800c021c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl8,                0x800c0220,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl9,                0x800c0224,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl10,               0x800c0228,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl11,               0x800c022c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl12,               0x800c0230,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl13,               0x800c0234,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl14,               0x800c0238,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32_BIT(VIC2VectCntl15,               0x800c023c,__READ_WRITE,__vicvectcntl_bits);
__IO_REG32(    VIC2PeriphID0,                0x800c0fe0,__READ      );
__IO_REG32(    VIC2PeriphID1,                0x800c0fe4,__READ      );
__IO_REG32(    VIC2PeriphID2,                0x800c0fe8,__READ      );
__IO_REG32(    VIC2PeriphID3,                0x800c0fec,__READ      );


/***************************************************************************
 **
 ** Timer registers
 **
 ***************************************************************************/
__IO_REG32(    Timer1Load,                   0x80810000,__READ_WRITE);
__IO_REG32(    Timer1Value,                  0x80810004,__READ      );
__IO_REG32_BIT(Timer1Control,                0x80810008,__READ_WRITE,__timerxcontrol_bits);
__IO_REG32(    Timer1Clear,                  0x8081000c,__WRITE     );
__IO_REG32(    Timer2Load,                   0x80810020,__READ_WRITE);
__IO_REG32(    Timer2Value,                  0x80810024,__READ      );
__IO_REG32_BIT(Timer2Control,                0x80810028,__READ_WRITE,__timerxcontrol_bits);
__IO_REG32(    Timer2Clear,                  0x8081002c,__WRITE     );
__IO_REG32(    Timer4ValueLow,               0x80810060,__READ      );
__IO_REG32(    Timer4Enable_Timer4ValueHigh, 0x80810064,__READ_WRITE);
#define Timer4Enable    Timer4Enable_Timer4ValueHigh
#define Timer4ValueHigh Timer4Enable_Timer4ValueHigh
__IO_REG32(    Timer3Load,                   0x80810080,__READ_WRITE);
__IO_REG32(    Timer3Value,                  0x80810084,__READ      );
__IO_REG32_BIT(Timer3Control,                0x80810088,__READ_WRITE,__timerxcontrol_bits);
__IO_REG32(    Timer3Clear,                  0x8081008c,__WRITE     );


/***************************************************************************
 **
 ** I2S registers
 **
 ***************************************************************************/
__IO_REG32_BIT(I2STXClkCfg,                  0x80820000,__READ_WRITE,__i2stxclkcfg_bits);
__IO_REG32_BIT(I2SRXClkCfg,                  0x80820004,__READ_WRITE,__i2srxclkcfg_bits);
__IO_REG32_BIT(I2SGlSts,                     0x80820008,__READ_WRITE,__i2sglsts_bits);
__IO_REG32_BIT(I2SGlCtrl,                    0x8082000c,__READ_WRITE,__i2sglctrl_bits);
__IO_REG32(    I2STX0Lft,                    0x80820010,__READ_WRITE);
__IO_REG32(    I2STX0Rt,                     0x80820014,__READ_WRITE);
__IO_REG32(    I2STX1Lft,                    0x80820018,__READ_WRITE);
__IO_REG32(    I2STX1Rt,                     0x8082001c,__READ_WRITE);
__IO_REG32(    I2STX2Lft,                    0x80820020,__READ_WRITE);
__IO_REG32(    I2STX2Rt,                     0x80820024,__READ_WRITE);
__IO_REG32_BIT(I2STXLinCtrlData,             0x80820028,__READ_WRITE,__i2stxlinctrldata_bits);
__IO_REG32_BIT(I2STXCtrl,                    0x8082002c,__READ_WRITE,__i2stxctrl_bits);
__IO_REG32_BIT(I2STXWrdLen,                  0x80820030,__READ_WRITE,__i2stxwrdlen_bits);
__IO_REG32_BIT(I2STX0En,                     0x80820034,__READ_WRITE,__i2stxxen_bits);
__IO_REG32_BIT(I2STX1En,                     0x80820038,__READ_WRITE,__i2stxxen_bits);
__IO_REG32_BIT(I2STX2En,                     0x8082003c,__READ_WRITE,__i2stxxen_bits);
__IO_REG32(    I2SRX0Lft,                    0x80820040,__READ_WRITE);
__IO_REG32(    I2SRX0Rt,                     0x80820044,__READ_WRITE);
__IO_REG32(    I2SRX1Lft,                    0x80820048,__READ_WRITE);
__IO_REG32(    I2SRX1Rt,                     0x8082004c,__READ_WRITE);
__IO_REG32(    I2SRX2Lft,                    0x80820050,__READ_WRITE);
__IO_REG32(    I2SRX2Rt,                     0x80820054,__READ_WRITE);
__IO_REG32_BIT(I2SRXLinCtrlData,             0x80820058,__READ_WRITE,__i2srxlinctrldata_bits);
__IO_REG32_BIT(I2SRXCtrl,                    0x8082005c,__READ_WRITE,__i2srxctrl_bits);
__IO_REG32_BIT(I2SRXWrdLen,                  0x80820060,__READ_WRITE,__i2srxwrdlen_bits);
__IO_REG32_BIT(I2SRX0En,                     0x80820064,__READ_WRITE,__i2srxxen_bits);
__IO_REG32_BIT(I2SRX1En,                     0x80820068,__READ_WRITE,__i2srxxen_bits);
__IO_REG32_BIT(I2SRX2En,                     0x8082006c,__READ_WRITE,__i2srxxen_bits);


/***************************************************************************
 **
 ** GPIO control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(PADR,                         0x80840000,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PBDR,                         0x80840004,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PCDR,                         0x80840008,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PDDR,                         0x8084000c,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PADDR,                        0x80840010,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(PBDDR,                        0x80840014,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(PCDDR,                        0x80840018,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(PDDDR,                        0x8084001c,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(PEDR,                         0x80840020,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PEDDR,                        0x80840024,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(PFDR,                         0x80840030,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PFDDR,                        0x80840034,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(PGDR,                         0x80840038,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PGDDR,                        0x8084003c,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(PHDR,                         0x80840040,__READ_WRITE,__pxdr_bits);
__IO_REG32_BIT(PHDDR,                        0x80840044,__READ_WRITE,__pxddr_bits);
__IO_REG32_BIT(GPIOFIntType1,                0x8084004c,__READ_WRITE,__gpioxinttype1_bits);
__IO_REG32_BIT(GPIOFIntType2,                0x80840050,__READ_WRITE,__gpioxinttype2_bits);
__IO_REG32_BIT(GPIOFEOI,                     0x80840054,__READ_WRITE,__gpioxeoi_bits);
__IO_REG32_BIT(GPIOFIntEn,                   0x80840058,__READ_WRITE,__gpioxinten_bits);
__IO_REG32_BIT(IntStsF,                      0x8084005c,__READ_WRITE,__intstsx_bits);
__IO_REG32_BIT(RawIntStsF,                   0x80840060,__READ_WRITE,__rawintstsx_bits);
__IO_REG32_BIT(GPIOFDB,                      0x80840064,__READ_WRITE,__gpioxdb_bits);
__IO_REG32_BIT(GPIOAIntType1,                0x80840090,__READ_WRITE,__gpioxinttype1_bits);
__IO_REG32_BIT(GPIOAIntType2,                0x80840094,__READ_WRITE,__gpioxinttype2_bits);
__IO_REG32_BIT(GPIOAEOI,                     0x80840098,__READ_WRITE,__gpioxeoi_bits);
__IO_REG32_BIT(GPIOAIntEn,                   0x8084009c,__READ_WRITE,__gpioxinten_bits);
__IO_REG32_BIT(IntStsA,                      0x808400a0,__READ_WRITE,__intstsx_bits);
__IO_REG32_BIT(RAWIntStsA,                   0x808400a4,__READ_WRITE,__rawintstsx_bits);
__IO_REG32_BIT(GPIOADB,                      0x808400a8,__READ_WRITE,__gpioxdb_bits);
__IO_REG32_BIT(GPIOBIntType1,                0x808400ac,__READ_WRITE,__gpioxinttype1_bits);
__IO_REG32_BIT(GPIOBIntType2,                0x808400b0,__READ_WRITE,__gpioxinttype2_bits);
__IO_REG32_BIT(GPIOBEOI,                     0x808400b4,__READ_WRITE,__gpioxeoi_bits);
__IO_REG32_BIT(GPIOBIntEn,                   0x808400b8,__READ_WRITE,__gpioxinten_bits);
__IO_REG32_BIT(IntStsB,                      0x808400bc,__READ_WRITE,__intstsx_bits);
__IO_REG32_BIT(RawIntStsB,                   0x808400c0,__READ_WRITE,__rawintstsx_bits);
__IO_REG32_BIT(GPIOBDB,                      0x808400c4,__READ_WRITE,__gpioxdb_bits);
__IO_REG32_BIT(EEDrive,                      0x808400c8,__READ_WRITE,__eedrive_bits);


/***************************************************************************
 **
 ** AC'97 control registers
 **
 ***************************************************************************/
__IO_REG32(    AC97DR1,                      0x80880000,__READ_WRITE);
__IO_REG32_BIT(AC97RXCR1,                    0x80880004,__READ_WRITE,__ac97rxcrx_bits);
__IO_REG32_BIT(AC97TXCR1,                    0x80880008,__READ_WRITE,__ac97txcrx_bits);
__IO_REG32_BIT(AC97SR1,                      0x8088000c,__READ      ,__ac97srx_bits);
__IO_REG32_BIT(AC97RISR1,                    0x80880010,__READ_WRITE,__ac97risrx_bits);
__IO_REG32_BIT(AC97ISR1,                     0x80880014,__READ      ,__ac97isrx_bits);
__IO_REG32_BIT(AC97IE1,                      0x80880018,__READ_WRITE,__ac97iex_bits);
__IO_REG32(    AC97DR2,                      0x80880020,__READ_WRITE);
__IO_REG32_BIT(AC97RXCR2,                    0x80880024,__READ_WRITE,__ac97rxcrx_bits);
__IO_REG32_BIT(AC97TXCR2,                    0x80880028,__READ_WRITE,__ac97txcrx_bits);
__IO_REG32_BIT(AC97SR2,                      0x8088002c,__READ      ,__ac97srx_bits);
__IO_REG32_BIT(AC97RISR2,                    0x80880030,__READ_WRITE,__ac97risrx_bits);
__IO_REG32_BIT(AC97ISR2,                     0x80880034,__READ      ,__ac97isrx_bits);
__IO_REG32_BIT(AC97IE2,                      0x80880038,__READ_WRITE,__ac97iex_bits);
__IO_REG32(    AC97DR3,                      0x80880040,__READ_WRITE);
__IO_REG32_BIT(AC97RXCR3,                    0x80880044,__READ_WRITE,__ac97rxcrx_bits);
__IO_REG32_BIT(AC97TXCR3,                    0x80880048,__READ_WRITE,__ac97txcrx_bits);
__IO_REG32_BIT(AC97SR3,                      0x8088004c,__READ      ,__ac97srx_bits);
__IO_REG32_BIT(AC97RISR3,                    0x80880050,__READ_WRITE,__ac97risrx_bits);
__IO_REG32_BIT(AC97ISR3,                     0x80880054,__READ      ,__ac97isrx_bits);
__IO_REG32_BIT(AC97IE3,                      0x80880058,__READ_WRITE,__ac97iex_bits);
__IO_REG32(    AC97DR4,                      0x80880060,__READ_WRITE);
__IO_REG32_BIT(AC97RXCR4,                    0x80880064,__READ_WRITE,__ac97rxcrx_bits);
__IO_REG32_BIT(AC97TXCR4,                    0x80880068,__READ_WRITE,__ac97txcrx_bits);
__IO_REG32_BIT(AC97SR4,                      0x8088006c,__READ      ,__ac97srx_bits);
__IO_REG32_BIT(AC97RISR4,                    0x80880070,__READ_WRITE,__ac97risrx_bits);
__IO_REG32_BIT(AC97ISR4,                     0x80880074,__READ      ,__ac97isrx_bits);
__IO_REG32_BIT(AC97IE4,                      0x80880078,__READ_WRITE,__ac97iex_bits);
__IO_REG32(    AC97S1Data,                   0x80880080,__READ_WRITE);
__IO_REG32(    AC97S2Data,                   0x80880084,__READ_WRITE);
__IO_REG32(    AC97S12Data,                  0x80880088,__READ_WRITE);
__IO_REG32_BIT(AC97RGIS,                     0x8088008c,__READ_WRITE,__ac97rgis_bits);
__IO_REG32_BIT(AC97GIS,                      0x80880090,__READ_WRITE,__ac97gis_bits);
__IO_REG32_BIT(AC97IM,                       0x80880094,__READ_WRITE,__ac97im_bits);
__IO_REG32_BIT(AC97EOI,                      0x80880098,__READ_WRITE,__ac97eoi_bits);
__IO_REG32_BIT(AC97GCR,                      0x8088009c,__READ_WRITE,__ac97gcr_bits);
__IO_REG32_BIT(AC97Reset,                    0x808800a0,__READ_WRITE,__ac97reset_bits);
__IO_REG32_BIT(AC97SYNC,                     0x808800a4,__READ_WRITE,__ac97sync_bits);
__IO_REG32_BIT(AC97GCIS,                     0x808800a8,__READ_WRITE,__ac97gcis_bits);


/***************************************************************************
 **
 ** SPI control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(SSPCR0,                       0x808a0000,__READ_WRITE,__sspcr0_bits);
__IO_REG32_BIT(SSPCR1,                       0x808a0004,__READ_WRITE,__sspcr1_bits);
__IO_REG32(    SSPDR,                        0x808a0008,__READ_WRITE);
__IO_REG32_BIT(SSPSR,                        0x808a000c,__READ_WRITE,__sspsr_bits);
__IO_REG32_BIT(SSPCPSR,                      0x808a0010,__READ_WRITE,__sspcpcr_bits);
__IO_REG32_BIT(SSPIIR,                       0x808a0014,__READ_WRITE,__sspiir_bits);


/***************************************************************************
 **
 ** IrDA control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(IrEnable,                     0x808b0000,__READ_WRITE,__irenable_bits);
__IO_REG32_BIT(IrCtrl,                       0x808b0004,__READ_WRITE,__irctrl_bits);
__IO_REG32_BIT(IrAdrMatchVal,                0x808b0008,__READ_WRITE,__iradrmatchval_bits);
__IO_REG32_BIT(IrFlag,                       0x808b000c,__READ      ,__irflag_bits);
__IO_REG32(    IrData,                       0x808b0010,__READ_WRITE);
__IO_REG32(    IrDataTail,                   0x808b0014,__WRITE     );
__IO_REG32_BIT(IrRIB,                        0x808b0020,__READ      ,__irrib_bits);
__IO_REG32_BIT(IrTR0,                        0x808b0024,__READ      ,__irtr0_bits);
__IO_REG32_BIT(IrDMACR,                      0x808b0028,__READ_WRITE,__irdmacr_bits);
__IO_REG32_BIT(SIRTR0,                       0x808b0030,__READ_WRITE,__sirtr0_bits);
__IO_REG32_BIT(MISR,                         0x808b0080,__READ      ,__misr_bits);
__IO_REG32_BIT(MIMR,                         0x808b0084,__READ      ,__mimr_bits);
__IO_REG32_BIT(MIIR,                         0x808b0088,__READ      ,__miir_bits);


/***************************************************************************
 **
 ** UART1 control registers
 **
 ***************************************************************************/
__IO_REG32(    UART1Data,                    0x808c0000,__READ_WRITE);
__IO_REG32_BIT(UART1RXSts,                   0x808c0004,__READ_WRITE,__uartxrxsts_bits);
__IO_REG32_BIT(UART1LinCtrlHigh,             0x808c0008,__READ_WRITE,__uartxlinctrlhigh_bits);
__IO_REG32_BIT(UART1LinCtrlMid,              0x808c000c,__READ_WRITE,__uartxlinctrlmid_bits);
__IO_REG32_BIT(UART1LinCtrlLow,              0x808c0010,__READ_WRITE,__uartxlinctrllow_bits);
__IO_REG32_BIT(UART1Ctrl,                    0x808c0014,__READ_WRITE,__uartxctrl_bits);
__IO_REG32_BIT(UART1Flag,                    0x808c0018,__READ_WRITE,__uartxflag_bits);
__IO_REG32_BIT(UART1IntIDIntCtrl,            0x808c001c,__READ_WRITE,__uartxintidintclr_bits);
__IO_REG32_BIT(UART1DMACtrl,                 0x808c0028,__READ_WRITE,__uartxdmactrl_bits);
__IO_REG32_BIT(UART1ModemCtrl,               0x808c0100,__READ_WRITE,__uartxmodemctrl_bits);
__IO_REG32_BIT(UART1ModemSts,                0x808c0104,__READ      ,__uartxmodemsts_bits);
__IO_REG32_BIT(UART1HDLCCtrl,                0x808c020c,__READ_WRITE,__uartxhdlcctrl_bits);
__IO_REG32(    UART1HDLCAddMtchVal,          0x808c0210,__READ_WRITE);
__IO_REG32(    UART1HDLCAddMask,             0x808c0214,__READ_WRITE);
__IO_REG32_BIT(UART1HDLCRXInfoBuf,           0x808c0218,__READ      ,__uartxhdlcrxinfobuf_bits);
__IO_REG32_BIT(UART1HDLCSts,                 0x808c021c,__READ_WRITE,__uartxhdlcsts_bits);


/***************************************************************************
 **
 ** UART2 control registers
 **
 ***************************************************************************/
__IO_REG32(    UART2Data,                    0x808d0000,__READ_WRITE);
__IO_REG32_BIT(UART2RXSts,                   0x808d0004,__READ_WRITE,__uartxrxsts_bits);
__IO_REG32_BIT(UART2LinCtrlHigh,             0x808d0008,__READ_WRITE,__uartxlinctrlhigh_bits);
__IO_REG32_BIT(UART2LinCtrlMid,              0x808d000c,__READ_WRITE,__uartxlinctrlmid_bits);
__IO_REG32_BIT(UART2LinCtrlLow,              0x808d0010,__READ_WRITE,__uartxlinctrllow_bits);
__IO_REG32_BIT(UART2Ctrl,                    0x808d0014,__READ_WRITE,__uartxctrl_bits);
__IO_REG32_BIT(UART2Flag,                    0x808d0018,__READ_WRITE,__uartxflag_bits);
__IO_REG32_BIT(UART2IntIDIntCtrl,            0x808d001c,__READ_WRITE,__uartxintidintclr_bits);
__IO_REG32_BIT(UART2IrLowPwrCntr,            0x808d0020,__READ_WRITE,__uart2irlowpwrcntr_bits);
__IO_REG32_BIT(UART2DMACtrl,                 0x808d0028,__READ_WRITE,__uartxdmactrl_bits);


/***************************************************************************
 **
 ** UART3 control registers
 **
 ***************************************************************************/
__IO_REG32(    UART3Data,                    0x808e0000,__READ_WRITE);
__IO_REG32_BIT(UART3RXSts,                   0x808e0004,__READ_WRITE,__uartxrxsts_bits);
__IO_REG32_BIT(UART3LinCtrlHigh,             0x808e0008,__READ_WRITE,__uartxlinctrlhigh_bits);
__IO_REG32_BIT(UART3LinCtrlMid,              0x808e000c,__READ_WRITE,__uartxlinctrlmid_bits);
__IO_REG32_BIT(UART3LinCtrlLow,              0x808e0010,__READ_WRITE,__uartxlinctrllow_bits);
__IO_REG32_BIT(UART3Ctrl,                    0x808e0014,__READ_WRITE,__uartxctrl_bits);
__IO_REG32_BIT(UART3Flag,                    0x808e0018,__READ_WRITE,__uartxflag_bits);
__IO_REG32_BIT(UART3IntIdIntCtrl,            0x808e001c,__READ_WRITE,__uartxintidintclr_bits);
__IO_REG32(    UART3IrLowPwrCntr,            0x808e0020,__READ_WRITE);
__IO_REG32_BIT(UART3DMACtrl,                 0x808e0028,__READ_WRITE,__uartxdmactrl_bits);
__IO_REG32_BIT(UART3ModemCtrl,               0x808e0100,__READ_WRITE,__uartxmodemctrl_bits);
__IO_REG32_BIT(UART3ModemSts,                0x808e0104,__READ      ,__uartxmodemsts_bits);
__IO_REG32_BIT(UART3HDLCCtrl,                0x808e020c,__READ_WRITE,__uartxhdlcctrl_bits);
__IO_REG32(    UART3HDLCAddMtchVal,          0x808e0210,__READ_WRITE);
__IO_REG32(    UART3HDLCAddMask,             0x808e0214,__READ_WRITE);
__IO_REG32_BIT(UART3HDLCRXInfoBuf,           0x808e0218,__READ      ,__uartxhdlcrxinfobuf_bits);
__IO_REG32_BIT(UART3HDLCSts,                 0x808e021c,__READ_WRITE,__uartxhdlcsts_bits);


/***************************************************************************
 **
 ** Key matrix control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(KeyScanInit,                  0x808f0000,__READ_WRITE,__keyscaninit_bits);
__IO_REG32_BIT(KeyDiagnostic,                0x808f0004,__READ_WRITE,__keydiagnostic_bits);
__IO_REG32_BIT(KeyRegister,                  0x808f0008,__READ_WRITE,__keyregister_bits);


/***************************************************************************
 **
 ** Touchscreen control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(TSSetup,                      0x80900000,__READ_WRITE,__tssetup_bits);
__IO_REG32_BIT(TSXYMaxMin,                   0x80900004,__READ_WRITE,__tsxymaxmin_bits);
__IO_REG32_BIT(TSXYResult,                   0x80900008,__READ_WRITE,__tsxyresult_bits);
__IO_REG32_BIT(TSDischarge,                  0x8090000c,__READ_WRITE,__ts_bits);
__IO_REG32_BIT(TSXSample,                    0x80900010,__READ_WRITE,__ts_bits);
__IO_REG32_BIT(TSYSample,                    0x80900014,__READ_WRITE,__ts_bits);
__IO_REG32_BIT(TSDirect,                     0x80900018,__READ_WRITE,__ts_bits);
__IO_REG32_BIT(TSDetect,                     0x8090001c,__READ_WRITE,__ts_bits);
__IO_REG32_BIT(TSSWLock,                     0x80900020,__READ_WRITE,__tsswlock_bits);
__IO_REG32_BIT(TSSetup2,                     0x80900024,__READ_WRITE,__tssetup2_bits);


/***************************************************************************
 **
 ** PWM control registers
 **
 ***************************************************************************/
__IO_REG32(    PWM0TermCnt,                  0x80910000,__READ_WRITE);
__IO_REG32(    PWM0DutyCycle,                0x80910004,__READ_WRITE);
__IO_REG32_BIT(PWM0En,                       0x80910008,__READ_WRITE,__pwmxen_bits);
__IO_REG32_BIT(PWM0Invert,                   0x8091000c,__READ_WRITE,__pwmxinvert_bits);
__IO_REG32(    PWM0Sync,                     0x80910010,__READ_WRITE);
__IO_REG32(    PWM1TermCnt,                  0x80910020,__READ_WRITE);
__IO_REG32(    PWM1DutyCycle,                0x80910024,__READ_WRITE);
__IO_REG32_BIT(PWM1En,                       0x80910028,__READ_WRITE,__pwmxen_bits);
__IO_REG32_BIT(PWM1Invert,                   0x8091002c,__READ_WRITE,__pwmxinvert_bits);
__IO_REG32(    PWM1Sync,                     0x80910030,__READ_WRITE);


/***************************************************************************
 **
 ** RTC control registers
 **
 ***************************************************************************/
__IO_REG32(    RTCData,                      0x80920000,__READ      );
__IO_REG32(    RTCMatch,                     0x80920004,__READ_WRITE);
__IO_REG32_BIT(RTCSts,                       0x80920008,__READ_WRITE,__rtcsts_bits);
__IO_REG32(    RTCLoad,                      0x8092000c,__READ_WRITE);
__IO_REG32_BIT(RTCCtrl,                      0x80920010,__READ_WRITE,__rtcctrl_bits);
__IO_REG32_BIT(RTCSWComp,                    0x80920108,__READ_WRITE,__rtcswcomp_bits);


/***************************************************************************
 **
 ** System registers
 **
 ***************************************************************************/
__IO_REG32_BIT(PwrSts,                       0x80930000,__READ      ,__pwrsts_bits);
__IO_REG32_BIT(PwrCnt,                       0x80930004,__READ_WRITE,__pwrcnt_bits);
__IO_REG32(    Halt,                         0x80930008,__READ      );
__IO_REG32(    Standby,                      0x8093000c,__READ      );
__IO_REG32(    TEOI,                         0x80930018,__WRITE     );
__IO_REG32(    STFClr,                       0x8093001c,__WRITE     );
__IO_REG32_BIT(ClkSet1,                      0x80930020,__READ_WRITE,__clkset1_bits);
__IO_REG32_BIT(ClkSet2,                      0x80930024,__READ_WRITE,__clkset2_bits);
__IO_REG32(    ScratchReg0,                  0x80930040,__READ_WRITE);
__IO_REG32(    ScratchReg1,                  0x80930044,__READ_WRITE);
__IO_REG32_BIT(APBWait,                      0x80930050,__READ_WRITE,__apbwait_bits);
__IO_REG32_BIT(BusMstrArb,                   0x80930054,__READ_WRITE,__busmstrarb_bits);
__IO_REG32(    BootModeClr,                  0x80930058,__WRITE     );
__IO_REG32_BIT(DeviceCfg,                    0x80930080,__READ_WRITE,__devicecfg_bits);
__IO_REG32_BIT(VidClkDiv,                    0x80930084,__READ_WRITE,__vidclkdiv_bits);
__IO_REG32_BIT(MIRClkDiv,                    0x80930088,__READ_WRITE,__mirclkdiv_bits);
__IO_REG32_BIT(I2SClkDiv,                    0x8093008c,__READ_WRITE,__i2sclkdiv_bits);
__IO_REG32_BIT(KeyTchClkDiv,                 0x80930090,__READ_WRITE,__keytchclkdiv_bits);
__IO_REG32_BIT(ChipID,                       0x80930094,__READ_WRITE,__chipid_bits);
__IO_REG32_BIT(SysCfg,                       0x8093009c,__READ_WRITE,__syscfg_bits);
__IO_REG32_BIT(SysSWLock,                    0x809300c0,__READ_WRITE,__sysswlock_bits);


/***************************************************************************
 **
 ** Watchdog control registers
 **
 ***************************************************************************/
__IO_REG32_BIT(Watchdog,                     0x80940000,__READ_WRITE,__watchdog_bits);
__IO_REG32_BIT(WDStatus,                     0x80940004,__READ_WRITE,__wdstatus_bits);


/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 **  Interrupt vector table
 **
 ***************************************************************************/
#define RESETV  0x00  /* Reset                           */
#define UNDEFV  0x04  /* Undefined instruction           */
#define SWIV    0x08  /* Software interrupt              */
#define PABORTV 0x0c  /* Prefetch abort                  */
#define DABORTV 0x10  /* Data abort                      */
#define IRQV    0x18  /* Normal interrupt                */
#define FIQV    0x1c  /* Fast interrupt                  */

/***************************************************************************
 **
 **  VIC Interrupt channels
 **
 ***************************************************************************/
#define VIC1_COMMRX          2  /* ARM Communication Rx for Debug             */
#define VIC1_COMMTX          3  /* ARM Communication Tx for Debug             */
#define VIC1_TC1OI           4  /* TC1 underflow interrupt (Timer Counter 1)  */
#define VIC1_TC2OI           5  /* TC2 underflow interrupt (Timer Counter 2)  */
#define VIC1_AACINTR         6  /* Advanced Audio Codec interrupt             */
#define VIC1_DMAM2P0         7  /* DMA Memory to Peripheral Interrupt 0       */
#define VIC1_DMAM2P1         8  /* DMA Memory to Peripheral Interrupt 1       */
#define VIC1_DMAM2P2         9  /* DMA Memory to Peripheral Interrupt 2       */
#define VIC1_DMAM2P3        10  /* DMA Memory to Peripheral Interrupt 3       */
#define VIC1_DMAM2P4        11  /* DMA Memory to Peripheral Interrupt 4       */
#define VIC1_DMAM2P5        12  /* DMA Memory to Peripheral Interrupt 5       */
#define VIC1_DMAM2P6        13  /* DMA Memory to Peripheral Interrupt 6       */
#define VIC1_DMAM2P7        14  /* DMA Memory to Peripheral Interrupt 7       */
#define VIC1_DMAM2P8        15  /* DMA Memory to Peripheral Interrupt 8       */
#define VIC1_DMAM2P9        16  /* DMA Memory to Peripheral Interrupt 9       */
#define VIC1_DMAM2M0        17  /* DMA Memory to Memory Interrupt 0           */
#define VIC1_DMAM2M1        18  /* DMA Memory to Memory Interrupt 1           */
#define VIC1_GPIO0INTR      19  /* GPIO interrupt 0                           */
#define VIC1_GPIO1INTR      20  /* GPIO interrupt 1                           */
#define VIC1_GPIO2INTR      21  /* GPIO interrupt 2                           */
#define VIC1_GPIO3INTR      22  /* GPIO interrupt 3                           */
#define VIC1_UART1RXINTR1   23  /* UART 1 Receive Interrupt                   */
#define VIC1_UART1TXINTR1   24  /* UART 1 Transmit Interrupt                  */
#define VIC1_UART2RXINTR1   25  /* UART 2 Receive Interrupt                   */
#define VIC1_UART2TXINTR1   26  /* UART 2 Transmit Interrupt                  */
#define VIC1_UART3RXINTR1   27  /* UART 3 Receive Interrupt                   */
#define VIC1_UART3TXINTR1   28  /* UART 3 Transmit Interrupt                  */
#define VIC1_INT_KEY        29  /* Keyboard Matrix Interrupt                  */
#define VIC1_INT_TOUCH      30  /* Touch screen Controller Interrupt          */

#define VIC2_INT_EXT0        0  /* External interrupt 0                       */
#define VIC2_INT_EXT1        1  /* External interrupt 1                       */
#define VIC2_INT_EXT2        2  /* External interrupt 2                       */
#define VIC2_TINTR           3  /* 64 Hz tick Interrupt                       */
#define VIC2_WEINT           4  /* Watchdog expired Interrupt                 */
#define VIC2_INT_RTC         5  /* RTC Interrupt                              */
#define VIC2_INT_IRDA        6  /* IrDA Interrupt                             */
#define VIC2_INT_MAC         7  /* Ethernet MAC Interrupt                     */
#define VIC2_INT_EXT3        8  /* External interrupt 3                       */
#define VIC2_INT_PROG        9  /* Raster Programmable Interrupt              */
#define VIC2_CLK1HZ         10  /* 1 Hz Clock Interrupt                       */
#define VIC2_V_SYNC         11  /* Video Sync Interrupt                       */
#define VIC2_INT_VIDEO_FIFO 12  /* Raster Video FIFO Interrupt                */
#define VIC2_INT_SSP1RX     13  /* SSP Receive Interrupt                      */
#define VIC2_INT_SSP1TX     14  /* SSP Transmit Interrupt                     */
#define VIC2_GPIO4INTR      15  /* GPIO interrupt 4                           */
#define VIC2_GPIO5INTR      16  /* GPIO interrupt 5                           */
#define VIC2_GPIO6INTR      17  /* GPIO interrupt 6                           */
#define VIC2_GPIO7INTR      18  /* GPIO interrupt 7                           */
#define VIC2_TC3OI          19  /* TC3 underflow interrupt (Timer Counter 3)  */
#define VIC2_INT_UART1      20  /* UART 1 Interrupt                           */
#define VIC2_SSPINTR        21  /* Synchronous serial port Interrupt          */
#define VIC2_INT_UART2      22  /* UART 2 Interrupt                           */
#define VIC2_INT_UART3      23  /* UART 3 Interrupt                           */
#define VIC2_USHINTR        24  /* USB Host Interrupt                         */
#define VIC2_INT_PME        25  /* Ethernet MAC PME Interrupt                 */
#define VIC2_INT_DSP        26  /* ARM Core Interrupt                         */
#define VIC2_GPIOINTR       27  /* GPIO combined Interrrupt                   */
#define VIC2_SAIINTR        28  /* I2S (SAI) block combined interrupt         */

#endif    /* __IOEP9312_H */
