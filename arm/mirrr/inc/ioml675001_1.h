/***************************************************************************
 **                        
 **    This file defines the Special Function Registers for
 **    Oki Semiconductors ML675001
 **
 **    Used with ICCARM and AARM.
 **                                
 **    (c) Copyright IAR Systems 2003
 **                                
 **    $Revision: 1.7 $
 **                                
 ***************************************************************************/

#ifndef __ML675001_H
#define __ML675001_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x7f = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **                            
 **    ML675001 SPECIAL FUNCTION REGISTERS
 **                            
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* Remap control register */
typedef struct {
  __REG32 RMPM    :4;
  __REG32         :28;
} __rmpcon_bits;

/* ROM select register */
typedef struct {
  __REG16   RSEL    :1;
  __REG16   BSELM   :1;
  __REG16           :14;
} __romsel_bits;


/* Block control register */
typedef struct {
  __REG16 BCKCTL0      :1;
  __REG16 BCKCTL1      :1;
  __REG16 BCKCTL2      :1;
  __REG16 BCKCTL3      :1;
  __REG16 BCKCTL4      :1;
  __REG16 BCKCTL5      :1;
  __REG16 BCKCTL6      :1;
  __REG16 BCKCTL7      :1;
  __REG16 BCKCTL8      :1;
  __REG16 BCKCTL9      :1;
  __REG16 BCKCTL10     :1;
  __REG16 BCKCTL11     :1;
  __REG16 BCKCTL12     :1;
  __REG16              :3;
} __bckctl_bits;

/* Clock stop register */
typedef struct {
  __REG32 SIO   :1;
  __REG32 TIC   :1;
  __REG32 HALT  :1;
  __REG32       :4;
  __REG32 STBY  :1;
  __REG32       :24;
} __clkstp_bits;

/* Clock gear control register */
typedef struct {
  __REG32 HCLKSEL :3;
  __REG32         :1;
  __REG32 CCLKSEL :3;
  __REG32         :25;
} __cgbcnt0_bits;

/* Clock wait register */
typedef struct {
  __REG32 CKWT    :4;
  __REG32         :28;
} __ckwt_bits;


/* IRQ register */
typedef struct {
  __REG32 IRQ0  :1;
  __REG32 IRQ1  :1;
  __REG32 IRQ2  :1;
  __REG32 IRQ3  :1;
  __REG32 IRQ4  :1;
  __REG32 IRQ5  :1;
  __REG32 IRQ6  :1;
  __REG32 IRQ7  :1;
  __REG32 IRQ8  :1;
  __REG32 IRQ9  :1;
  __REG32 IRQ10 :1;
  __REG32 IRQ11 :1;
  __REG32 IRQ12 :1;
  __REG32 IRQ13 :1;
  __REG32 IRQ14 :1;
  __REG32 IRQ15 :1;
  __REG32       :16;
} __irq_bits;

/* Software interrupt register, IRQS */
typedef struct {
  __REG32       :1;
  __REG32 IRQS  :1;
  __REG32       :30;
} __irqs_bits;

/* FIQ register */
typedef struct {
  __REG32 FIQ   :1;
  __REG32       :31;
} __fiq_bits;

/* FIQRAW register */
typedef struct {
  __REG32 FIQRAW :1;
  __REG32        :31;
} __fiqraw_bits;

/* FIQ enable register */
typedef struct {
  __REG32 FIQEN :1;
  __REG32       :31;
} __fiqen_bits;

/* IRQ number register */
typedef struct {
  __REG32 IRN   :7;
  __REG32       :25;
} __irn_bits;

/* Current interrupt level register */
typedef struct {
  __REG32       :1;
  __REG32 CIL1  :1;
  __REG32 CIL2  :1;
  __REG32 CIL3  :1;
  __REG32 CIL4  :1;
  __REG32 CIL5  :1;
  __REG32 CIL6  :1;
  __REG32 CIL7  :1;
  __REG32       :24;
} __cil_bits;

/* Interrupt level control register 0*/
typedef struct {
  __REG32 ILR0  :3;
  __REG32       :1;
  __REG32 ILR1  :3;
  __REG32       :9;
  __REG32 ILR4  :3;
  __REG32       :5;
  __REG32 ILR6  :3;
  __REG32       :5;
} __ilc0_bits;

/* Interrupt level control register 1*/
typedef struct {
  __REG32 ILR8  :3;
  __REG32       :1;
  __REG32 ILR9  :3;
  __REG32       :1;
  __REG32 ILR10 :3;
  __REG32       :1;
  __REG32 ILR11 :3;
  __REG32       :1;
  __REG32 ILR12 :3;
  __REG32       :1;
  __REG32 ILR13 :3;
  __REG32       :1;
  __REG32 ILR14 :3;
  __REG32       :1;
  __REG32 ILR15 :3;
  __REG32       :1;
} __ilc1_bits;

/* Current interrupt level encode register */
typedef struct {
  __REG32 CILE  :3;
  __REG32       :29;
} __cile_bits;

/* IRQ clear register */
typedef struct {
  __REG32 IRCL0 :1;
  __REG32 IRCL1 :1;
  __REG32 IRCL2 :1;
  __REG32 IRCL3 :1;
  __REG32 IRCL4 :1;
  __REG32 IRCL5 :1;
  __REG32 IRCL6 :1;
  __REG32       :25;
} __ircl_bits;

/* IRQA register */
typedef struct {
  __REG32 IRQ16 :1;
  __REG32 IRQ17 :1;
  __REG32 IRQ18 :1;
  __REG32 IRQ19 :1;
  __REG32 IRQ20 :1;
  __REG32 IRQ21 :1;
  __REG32 IRQ22 :1;
  __REG32 IRQ23 :1;
  __REG32 IRQ24 :1;
  __REG32 IRQ25 :1;
  __REG32 IRQ26 :1;
  __REG32 IRQ27 :1;
  __REG32 IRQ28 :1;
  __REG32 IRQ29 :1;
  __REG32 IRQ30 :1;
  __REG32 IRQ31 :1;
  __REG32       :16;
} __irqa_bits;

/* IDM register */
typedef struct {
  __REG32        :6;
  __REG32 IDM22  :1;
  __REG32 IDMP22 :1;
  __REG32        :2;
  __REG32 IDM26  :1;
  __REG32 IDMP26 :1;
  __REG32 IDM28  :1;
  __REG32 IDMP28 :1;
  __REG32 IDM30  :1;
  __REG32 IDMP30 :1;
  __REG32        :16;
} __idm_bits;

/* Interrupt level control register, ILC */
typedef struct {
  __REG32 ILC16 :3;
  __REG32       :1;
  __REG32 ILC18 :3;
  __REG32       :1;
  __REG32 ILC20 :3;
  __REG32       :1;
  __REG32 ILC22 :3;
  __REG32       :1;
  __REG32 ILC24 :3;
  __REG32       :1;
  __REG32 ILC26 :3;
  __REG32       :1;
  __REG32 ILC28 :3;
  __REG32       :1;
  __REG32 ILC30 :3;
  __REG32       :1;
} __ilc_bits;


/* Cache lock control register CON */
typedef struct {
  __REG32        :25;
  __REG32 LCK    :2;
  __REG32 F      :1;
  __REG32 BNK    :2;
  __REG32        :2;
} __con_bits;

/* Cacheable register CACHE */
typedef struct {
  __REG32 C8     :1;
  __REG32 C9     :1;
  __REG32 C10    :1;
  __REG32 C11    :1;
  __REG32 C12    :1;
  __REG32 C13    :1;
  __REG32 C14    :1;
  __REG32 C15    :1;
  __REG32 C24    :1;
  __REG32 C25    :1;
  __REG32 C26    :1;
  __REG32 C27    :1;
  __REG32 C28    :1;
  __REG32 C29    :1;
  __REG32 C30    :1;
  __REG32 C31    :1;
  __REG32 C0     :1;
  __REG32        :15;
} __cache_bits;


/* Bus width control register */
typedef struct {
  __REG32        :2;
  __REG32 ROMBW  :2;
  __REG32 RAMBW  :2;
  __REG32 IO01BW :2;
  __REG32        :2;
  __REG32        :22;
} __bwc_bits;

/* External I/O bank 2/3 Bus Width Control Register */
typedef struct {
  __REG32        :6;
  __REG32 IO23BW :2;
  __REG32        :24;
} __io23bw_bits;

/* External ROM access control register */
typedef struct {
  __REG32 ROMTYPE :3;
  __REG32         :1;
  __REG32 ROMBRST :1;
  __REG32         :27;
} __romac_bits;

/* External RAM access control register */
typedef struct {
  __REG32 RAMTYPE :3;
  __REG32         :1;
  __REG32 RAMBRST :1;
  __REG32         :27;
} __ramac_bits;

/* External I/O bank 0/1 access control register */
typedef struct {
  __REG32 IO01TYPE :3;
  __REG32          :29;
} __io01ac_bits;

/* External I/O bank 2/3 access control register */
typedef struct {
  __REG32 IO23TYPE :3;
  __REG32          :29;
} __io23ac_bits;

/* DRAM bus width control register */
typedef struct {
  __REG32 BWDRAM   :2;
  __REG32          :30;
} __dbwc_bits;

/* DRAM control register */
typedef struct {
  __REG32 AMUX     :2;
  __REG32 ARCH     :1;
  __REG32          :1;
  __REG32 PRELAT   :1;
  __REG32          :1;
  __REG32 PDWN     :1;
  __REG32 RFRSH    :1;
  __REG32          :24;
} __drmc_bits;

/* DRAM characteristics control register */
typedef struct {
  __REG32 DRAMSPEC :4;
  __REG32          :28;
} __drpc_bits;

/* SDRAM mode register */
typedef struct {
  __REG32 LTMODE   :1;
  __REG32          :6;
  __REG32 MODEWR   :1;
  __REG32          :24;
} __sdmd_bits;

/* DRAM command register */
typedef struct {
  __REG32 DRCMD    :3;
  __REG32          :29;
} __dcmd_bits;

/* DRAM refresh cycle control register 0 */
typedef struct {
  __REG32 RCCON    :1;
  __REG32          :31;
} __rfsh0_bits;

/* DRAM refresh cycle control register 1 */
typedef struct {
  __REG32 RFSEL    :11;
  __REG32          :21;
} __rfsh1_bits;

/* DRAM power down control register */
typedef struct {
  __REG32 PDCNT    :4;
  __REG32          :28;
} __rdwc_bits;


/* DMA mode register */
typedef struct {
  __REG32 PRI      :1;
  __REG32          :31;
} __dmamod_bits;

/* DMA status register */
typedef struct {
  __REG32 STA0     :1;
  __REG32 STA1     :1;
  __REG32          :30;
} __dmasta_bits;

/* DMA transfer complete status register */
typedef struct {
  __REG32 IREQ0    :1;
  __REG32 IREQ1    :1;
  __REG32          :6;
  __REG32 ISTA0    :1;
  __REG32 ISTA1    :1;
  __REG32          :6;
  __REG32 ISTP0    :1;
  __REG32 ISTP1    :1;
  __REG32          :14;
} __dmaint_bits;

/* DMA channel mask register */
typedef struct {
  __REG32 MSK      :1;
  __REG32          :31;
} __dmacmsk_bits;

/* DMA transfer mode register */
typedef struct {
  __REG32 ARQ      :1;
  __REG32 TSIZ     :2;
  __REG32 SDP      :1;
  __REG32 DDP      :1;
  __REG32 BRQ      :1;
  __REG32 IMK      :1;
  __REG32          :25;
} __dmactmod_bits;

/* DMA transfer count register */
typedef struct {
  __REG32 CSIZ     :17;
  __REG32          :15;
} __dmacsiz_bits;



/* GPIO port A output registers */
typedef struct {
  __REG16 GPPOA0     :1;
  __REG16 GPPOA1     :1;
  __REG16 GPPOA2     :1;
  __REG16 GPPOA3     :1;
  __REG16 GPPOA4     :1;
  __REG16 GPPOA5     :1;
  __REG16 GPPOA6     :1;
  __REG16 GPPOA7     :1;
  __REG16            :8;
} __gppoa_bits;

/* GPIO port A input registers */
typedef struct {
  __REG16 GPPIA0     :1;
  __REG16 GPPIA1     :1;
  __REG16 GPPIA2     :1;
  __REG16 GPPIA3     :1;
  __REG16 GPPIA4     :1;
  __REG16 GPPIA5     :1;
  __REG16 GPPIA6     :1;
  __REG16 GPPIA7     :1;
  __REG16            :8;
} __gppia_bits;

/* GPIO port A mode registers */
typedef struct {
  __REG16 GPPMA0     :1;
  __REG16 GPPMA1     :1;
  __REG16 GPPMA2     :1;
  __REG16 GPPMA3     :1;
  __REG16 GPPMA4     :1;
  __REG16 GPPMA5     :1;
  __REG16 GPPMA6     :1;
  __REG16 GPPMA7     :1;
  __REG16            :8;
} __gppma_bits;

/* GPIO port A interrupt enable registers */
typedef struct {
  __REG16 GPIEA0     :1;
  __REG16 GPIEA1     :1;
  __REG16 GPIEA2     :1;
  __REG16 GPIEA3     :1;
  __REG16 GPIEA4     :1;
  __REG16 GPIEA5     :1;
  __REG16 GPIEA6     :1;
  __REG16 GPIEA7     :1;
  __REG16            :8;
} __gpiea_bits;

/* GPIO port A interrupt polarity registers */
typedef struct {
  __REG16 GPIPA0     :1;
  __REG16 GPIPA1     :1;
  __REG16 GPIPA2     :1;
  __REG16 GPIPA3     :1;
  __REG16 GPIPA4     :1;
  __REG16 GPIPA5     :1;
  __REG16 GPIPA6     :1;
  __REG16 GPIPA7     :1;
  __REG16            :8;
} __gpipa_bits;

/* GPIO port A interrupt status registers */
typedef struct {
  __REG16 GPISA0     :1;
  __REG16 GPISA1     :1;
  __REG16 GPISA2     :1;
  __REG16 GPISA3     :1;
  __REG16 GPISA4     :1;
  __REG16 GPISA5     :1;
  __REG16 GPISA6     :1;
  __REG16 GPISA7     :1;
  __REG16            :8;
} __gpisa_bits;

/* GPIO port B output registers */
typedef struct {
  __REG16 GPPOB0     :1;
  __REG16 GPPOB1     :1;
  __REG16 GPPOB2     :1;
  __REG16 GPPOB3     :1;
  __REG16 GPPOB4     :1;
  __REG16 GPPOB5     :1;
  __REG16 GPPOB6     :1;
  __REG16 GPPOB7     :1;
  __REG16            :8;
} __gppob_bits;

/* GPIO port B input registers */
typedef struct {
  __REG16 GPPIB0     :1;
  __REG16 GPPIB1     :1;
  __REG16 GPPIB2     :1;
  __REG16 GPPIB3     :1;
  __REG16 GPPIB4     :1;
  __REG16 GPPIB5     :1;
  __REG16 GPPIB6     :1;
  __REG16 GPPIB7     :1;
  __REG16            :8;
} __gppib_bits;

/* GPIO port B mode registers */
typedef struct {
  __REG16 GPPMB0     :1;
  __REG16 GPPMB1     :1;
  __REG16 GPPMB2     :1;
  __REG16 GPPMB3     :1;
  __REG16 GPPMB4     :1;
  __REG16 GPPMB5     :1;
  __REG16 GPPMB6     :1;
  __REG16 GPPMB7     :1;
  __REG16            :8;
} __gppmb_bits;

/* GPIO port B interrupt enable registers */
typedef struct {
  __REG16 GPIEB0     :1;
  __REG16 GPIEB1     :1;
  __REG16 GPIEB2     :1;
  __REG16 GPIEB3     :1;
  __REG16 GPIEB4     :1;
  __REG16 GPIEB5     :1;
  __REG16 GPIEB6     :1;
  __REG16 GPIEB7     :1;
  __REG16            :8;
} __gpieb_bits;

/* GPIO port B interrupt polarity registers */
typedef struct {
  __REG16 GPIPB0     :1;
  __REG16 GPIPB1     :1;
  __REG16 GPIPB2     :1;
  __REG16 GPIPB3     :1;
  __REG16 GPIPB4     :1;
  __REG16 GPIPB5     :1;
  __REG16 GPIPB6     :1;
  __REG16 GPIPB7     :1;
  __REG16            :8;
} __gpipb_bits;

/* GPIO port B interrupt status registers */
typedef struct {
  __REG16 GPISB0     :1;
  __REG16 GPISB1     :1;
  __REG16 GPISB2     :1;
  __REG16 GPISB3     :1;
  __REG16 GPISB4     :1;
  __REG16 GPISB5     :1;
  __REG16 GPISB6     :1;
  __REG16 GPISB7     :1;
  __REG16            :8;
} __gpisb_bits;

/* GPIO port C output registers */
typedef struct {
  __REG16 GPPOC0     :1;
  __REG16 GPPOC1     :1;
  __REG16 GPPOC2     :1;
  __REG16 GPPOC3     :1;
  __REG16 GPPOC4     :1;
  __REG16 GPPOC5     :1;
  __REG16 GPPOC6     :1;
  __REG16 GPPOC7     :1;
  __REG16            :8;
} __gppoc_bits;

/* GPIO port C input registers */
typedef struct {
  __REG16 GPPIC0     :1;
  __REG16 GPPIC1     :1;
  __REG16 GPPIC2     :1;
  __REG16 GPPIC3     :1;
  __REG16 GPPIC4     :1;
  __REG16 GPPIC5     :1;
  __REG16 GPPIC6     :1;
  __REG16 GPPIC7     :1;
  __REG16            :8;
} __gppic_bits;

/* GPIO port C mode registers */
typedef struct {
  __REG16 GPPMC0     :1;
  __REG16 GPPMC1     :1;
  __REG16 GPPMC2     :1;
  __REG16 GPPMC3     :1;
  __REG16 GPPMC4     :1;
  __REG16 GPPMC5     :1;
  __REG16 GPPMC6     :1;
  __REG16 GPPMC7     :1;
  __REG16            :8;
} __gppmc_bits;

/* GPIO port C interrupt enable registers */
typedef struct {
  __REG16 GPIEC0     :1;
  __REG16 GPIEC1     :1;
  __REG16 GPIEC2     :1;
  __REG16 GPIEC3     :1;
  __REG16 GPIEC4     :1;
  __REG16 GPIEC5     :1;
  __REG16 GPIEC6     :1;
  __REG16 GPIEC7     :1;
  __REG16            :8;
} __gpiec_bits;

/* GPIO port C interrupt polarity registers */
typedef struct {
  __REG16 GPIPC0     :1;
  __REG16 GPIPC1     :1;
  __REG16 GPIPC2     :1;
  __REG16 GPIPC3     :1;
  __REG16 GPIPC4     :1;
  __REG16 GPIPC5     :1;
  __REG16 GPIPC6     :1;
  __REG16 GPIPC7     :1;
  __REG16            :8;
} __gpipc_bits;

/* GPIO port C interrupt status registers */
typedef struct {
  __REG16 GPISC0     :1;
  __REG16 GPISC1     :1;
  __REG16 GPISC2     :1;
  __REG16 GPISC3     :1;
  __REG16 GPISC4     :1;
  __REG16 GPISC5     :1;
  __REG16 GPISC6     :1;
  __REG16 GPISC7     :1;
  __REG16            :8;
} __gpisc_bits;

/* GPIO port D output registers */
typedef struct {
  __REG16 GPPOD0     :1;
  __REG16 GPPOD1     :1;
  __REG16 GPPOD2     :1;
  __REG16 GPPOD3     :1;
  __REG16 GPPOD4     :1;
  __REG16 GPPOD5     :1;
  __REG16 GPPOD6     :1;
  __REG16 GPPOD7     :1;
  __REG16            :8;
} __gppod_bits;

/* GPIO port D input registers */
typedef struct {
  __REG16 GPPID0     :1;
  __REG16 GPPID1     :1;
  __REG16 GPPID2     :1;
  __REG16 GPPID3     :1;
  __REG16 GPPID4     :1;
  __REG16 GPPID5     :1;
  __REG16 GPPID6     :1;
  __REG16 GPPID7     :1;
  __REG16            :8;
} __gppid_bits;

/* GPIO port D mode registers */
typedef struct {
  __REG16 GPPMD0     :1;
  __REG16 GPPMD1     :1;
  __REG16 GPPMD2     :1;
  __REG16 GPPMD3     :1;
  __REG16 GPPMD4     :1;
  __REG16 GPPMD5     :1;
  __REG16 GPPMD6     :1;
  __REG16 GPPMD7     :1;
  __REG16            :8;
} __gppmd_bits;

/* GPIO port D interrupt enable registers */
typedef struct {
  __REG16 GPIED0     :1;
  __REG16 GPIED1     :1;
  __REG16 GPIED2     :1;
  __REG16 GPIED3     :1;
  __REG16 GPIED4     :1;
  __REG16 GPIED5     :1;
  __REG16 GPIED6     :1;
  __REG16 GPIED7     :1;
  __REG16            :8;
} __gpied_bits;

/* GPIO port D interrupt polarity registers */
typedef struct {
  __REG16 GPIPD0     :1;
  __REG16 GPIPD1     :1;
  __REG16 GPIPD2     :1;
  __REG16 GPIPD3     :1;
  __REG16 GPIPD4     :1;
  __REG16 GPIPD5     :1;
  __REG16 GPIPD6     :1;
  __REG16 GPIPD7     :1;
  __REG16            :8;
} __gpipd_bits;

/* GPIO port D interrupt status registers */
typedef struct {
  __REG16 GPISD0     :1;
  __REG16 GPISD1     :1;
  __REG16 GPISD2     :1;
  __REG16 GPISD3     :1;
  __REG16 GPISD4     :1;
  __REG16 GPISD5     :1;
  __REG16 GPISD6     :1;
  __REG16 GPISD7     :1;
  __REG16            :8;
} __gpisd_bits;

/* GPIO port E output register */
typedef struct {
  __REG16 GPPOE0     :1;
  __REG16 GPPOE1     :1;
  __REG16 GPPOE2     :1;
  __REG16 GPPOE3     :1;
  __REG16 GPPOE4     :1;
  __REG16 GPPOE5     :1;
  __REG16 GPPOE6     :1;
  __REG16 GPPOE7     :1;
  __REG16 GPPOE8     :1;
  __REG16 GPPOE9     :1;
  __REG16            :6;
} __gppoe_bits;

/* GPIO port E input register */
typedef struct {
  __REG16 GPPIE0     :1;
  __REG16 GPPIE1     :1;
  __REG16 GPPIE2     :1;
  __REG16 GPPIE3     :1;
  __REG16 GPPIE4     :1;
  __REG16 GPPIE5     :1;
  __REG16 GPPIE6     :1;
  __REG16 GPPIE7     :1;
  __REG16 GPPIE8     :1;
  __REG16 GPPIE9     :1;
  __REG16            :6;
} __gppie_bits;

/* GPIO port E mode register */
typedef struct {
  __REG16 GPPME0     :1;
  __REG16 GPPME1     :1;
  __REG16 GPPME2     :1;
  __REG16 GPPME3     :1;
  __REG16 GPPME4     :1;
  __REG16 GPPME5     :1;
  __REG16 GPPME6     :1;
  __REG16 GPPME7     :1;
  __REG16 GPPME8     :1;
  __REG16 GPPME9     :1;
  __REG16            :6;
} __gppme_bits;

/* GPIO port E interrupt enable register */
typedef struct {
  __REG16 GPIEE0     :1;
  __REG16 GPIEE1     :1;
  __REG16 GPIEE2     :1;
  __REG16 GPIEE3     :1;
  __REG16 GPIEE4     :1;
  __REG16 GPIEE5     :1;
  __REG16 GPIEE6     :1;
  __REG16 GPIEE7     :1;
  __REG16 GPIEE8     :1;
  __REG16 GPIEE9     :1;
  __REG16            :6;
} __gpiee_bits;

/* GPIO port E interrupt polarity register */
typedef struct {
  __REG16 GPIPE0     :1;
  __REG16 GPIPE1     :1;
  __REG16 GPIPE2     :1;
  __REG16 GPIPE3     :1;
  __REG16 GPIPE4     :1;
  __REG16 GPIPE5     :1;
  __REG16 GPIPE6     :1;
  __REG16 GPIPE7     :1;
  __REG16 GPIPE8     :1;
  __REG16 GPIPE9     :1;
  __REG16            :6;
} __gpipe_bits;

/* GPIO port E interrupt status register */
typedef struct {
  __REG16 GPISE0     :1;
  __REG16 GPISE1     :1;
  __REG16 GPISE2     :1;
  __REG16 GPISE3     :1;
  __REG16 GPISE4     :1;
  __REG16 GPISE5     :1;
  __REG16 GPISE6     :1;
  __REG16 GPISE7     :1;
  __REG16 GPISE8     :1;
  __REG16 GPISE9     :1;
  __REG16            :6;
} __gpise_bits;

/* GPIO port function select register */
typedef struct {
  __REG16 GPCTL0      :1;
  __REG16 GPCTL1      :1;
  __REG16 GPCTL2      :1;
  __REG16 GPCTL3      :1;
  __REG16 GPCTL4      :1;
  __REG16 GPCTL5      :1;
  __REG16 GPCTL6      :1;
  __REG16 GPCTL7      :1;
  __REG16 GPCTL8      :1;
  __REG16 GPCTL9      :1;
  __REG16 GPCTL10     :1;
  __REG16 GPCTL11     :1;
  __REG16 GPCTL12     :1;
  __REG16 GPCTL13     :1;
  __REG16 GPCTL14     :1;
  __REG16             :1;
} __gpctl_bits;


/* WDT time base counter control register */
typedef struct {
  __REG8 WDCLK     :2;
  __REG8           :1;
  __REG8 ITM       :1;
  __REG8 ITEN      :1;
  __REG8           :1;
  __REG8 OFINTMODE :1;
  __REG8 WDHLT     :1;
} __wdtbcon_bits;

/* WDT status register */
typedef struct {
  __REG8 RSTSTATUS :1;
  __REG8           :3;
  __REG8 WDTIST    :1;
  __REG8 IVTIST    :1;
  __REG8           :2;
} __wdstat_bits;


/* System timer enable register */
typedef struct {
  __REG32 TCEN     :1;
  __REG32          :31;
} __tmen_bits;

/* System timer reload register */
typedef struct {
  __REG32 TMRLR    :16;
  __REG32          :16;
} __tmrlr_bits;

/* System timer overflow register */
typedef struct {
  __REG32 OVF      :1;
  __REG32          :31;
} __tmovfr_bits;

/* Timer control register */
typedef struct {
  __REG16 MODE     :1;
  __REG16          :2;
  __REG16 START    :1;
  __REG16 IE       :1;
  __REG16 CLKSEL   :3;
  __REG16          :8;
} __timecntl_bits;

/* Timer status register */
typedef struct {
  __REG16 STATUS   :1;
  __REG16          :15;
} __timestat_bits;


/* PWM0 control register */
typedef struct {
  __REG16 PW0R     :1;
  __REG16 PWCK0    :2;
  __REG16          :3;
  __REG16 INTIE0   :1;
  __REG16 PWC0OV   :1;
  __REG16          :8;
} __pwcon0_bits;

/* PWM1 control register */
typedef struct {
  __REG16 PW1R     :1;
  __REG16 PWCK1    :2;
  __REG16          :3;
  __REG16 INTIE1   :1;
  __REG16 PWC1OV   :1;
  __REG16          :8;
} __pwcon1_bits;

/* PWM interrupt status register */
typedef struct {
  __REG16 INT0CLR  :1;
  __REG16 INT1CLR  :1;
  __REG16          :6;
  __REG16 INT0S    :1;
  __REG16 INT1S    :1;
  __REG16          :6;
} __pwintsts_bits;


/* SIO transfer buffer register */
typedef struct {
  __REG32 SIOBUF   :8;
  __REG32          :24;
} __siobuf_bits;

/* SIO status register */
typedef struct {
  __REG32 FERR     :1;
  __REG32 OERR     :1;
  __REG32 PERR     :1;
  __REG32          :1;
  __REG32 RVIRQ    :1;
  __REG32 TRIRQ    :1;
  __REG32          :26;
} __siosta_bits;

/* SIO control register */
typedef struct {
  __REG32 LN       :1;
  __REG32 PEN      :1;
  __REG32 EVN      :1;
  __REG32 TSTB     :1;
  __REG32          :28;
} __siocon_bits;

/* SIO baud rate control register */
typedef struct {
  __REG32          :4;
  __REG32 BGRUN    :1;
  __REG32          :27;
} __siobcn_bits;

/* SIO baud rate timer register */
typedef struct {
  __REG32 SIOBT    :8;
  __REG32          :24;
} __siobt_bits;

/* SIO baud rate timer register */
typedef struct {
  __REG32 MFERR    :1;
  __REG32 WPERR    :1;
  __REG32          :5;
  __REG32 LBTST    :1;
  __REG32          :24;
} __siotcn_bits;


/* UART interrupt enable register */
typedef struct {
  __REG8 IER0      :1;
  __REG8 IER1      :1;
  __REG8 IER2      :1;
  __REG8 IER3      :1;
  __REG8           :4;
} __uartier_bits;

/* UART interrupt identification register and fifo control register */
typedef union {
  //UARTIIR
  struct {
    __REG8 IIR0      :1;
    __REG8 IIR31     :3;
    __REG8           :2;
    __REG8 IIR76     :2;
  };
  //UARTFCR
  struct {
    __REG8 FCR0      :1;
    __REG8 FCR1      :1;
    __REG8 FCR2      :1;
    __REG8 FCR3      :1;
    __REG8           :2;
    __REG8 FCR76     :2;
  };
} __uartfcriir_bits;

/* UART line control register */
typedef struct {
  __REG8 LCR10     :2;
  __REG8 LCR2      :1;
  __REG8 LCR3      :1;
  __REG8 LCR4      :1;
  __REG8 LCR5      :1;
  __REG8 LCR6      :1;
  __REG8 LCR7      :1;
} __uartlcr_bits;

/* UART modem control register */
typedef struct {
  __REG8 MCR0      :1;
  __REG8 MCR1      :1;
  __REG8           :2;
  __REG8 MCR4      :1;
  __REG8           :3;
} __uartmcr_bits;

/* UART line status register */
typedef struct {
  __REG8 LSR0      :1;
  __REG8 LSR1      :1;
  __REG8 LSR2      :1;
  __REG8 LSR3      :1;
  __REG8 LSR4      :1;
  __REG8 LSR5      :1;
  __REG8 LSR6      :1;
  __REG8 LSR7      :1;
} __uartlsr_bits;

/* UART modem status register */
typedef union {
  //UARTMSR
  struct {
  __REG8 DCTS      :1;
  __REG8 DDSR      :1;
  __REG8 TERI      :1;
  __REG8 DDCD      :1;
  __REG8 CTS       :1;
  __REG8 DSR       :1;
  __REG8 RI        :1;
  __REG8 DCD       :1;
  };
  //UARTMSR
  struct {
  __REG8 MSR0      :1;
  __REG8 MSR1      :1;
  __REG8 MSR2      :1;
  __REG8 MSR3      :1;
  __REG8 MSR4      :1;
  __REG8 MSR5      :1;
  __REG8 MSR6      :1;
  __REG8 MSR7      :1;
  };
} __uartmsr_bits;


/* Synchronous SIO status register */
typedef struct {
  __REG8 BUSY      :1;
  __REG8 OERR      :1;
  __REG8           :3;
  __REG8 SFTCT     :3;
} __ssiost_bits;

/* Synchronous SIO interrupt request register */
typedef struct {
  __REG8 TXCMP     :1;
  __REG8 RXCMP     :1;
  __REG8 TREMP     :1;
  __REG8           :5;
} __ssioint_bits;

/* Synchronous SIO interrupt enable register */
typedef struct {
  __REG8 TXCMPEN   :1;
  __REG8 RXCMPEN   :1;
  __REG8 TREMPEN   :1;
  __REG8           :5;
} __ssiointen_bits;

/* Synchronous SIO control register */
typedef struct {
  __REG8 SFTCLK    :2;
  __REG8           :2;
  __REG8 SFTSLV    :1;
  __REG8 SLMSB     :1;
  __REG8           :2;
} __ssiocon_bits;

/* Synchronous SIO test control register */
typedef struct {
  __REG8           :7;
  __REG8 LBTST     :1;
} __ssiotscon_bits;


/* I2C bus control register */
typedef struct {
  __REG8   I2CEN   :1;
  __REG8   I2COC   :1;
  __REG8   STCM    :1;
  __REG8   RESTR   :1;
  __REG8   START   :1;
  __REG8           :3;
} __i2ccon_bits;

/* I2C bus slave address mode register */
typedef struct {
  __REG8   I2CRW   :1;
  __REG8           :7;
} __i2csad_bits;

/* I2C bus transfer speed register */
typedef struct {
  __REG8   I2CMD   :1;
  __REG8   SAD     :7;
} __i2cclr_bits;

/* I2C bus status register */
typedef struct {
  __REG8   I2CDAK  :1;
  __REG8   I2CAAK  :1;
  __REG8           :6;
} __i2csr_bits;

/* I2C bus interrupt request register */
typedef struct {
  __REG8   I2CIR   :1;
  __REG8           :7;
} __i2cir_bits;

/* I2C bus interrupt mask register */
typedef struct {
  __REG8   I2CMF   :1;
  __REG8           :7;
} __i2cimr_bits;

/* I2C bus transfer speed counter register */
typedef struct {
  __REG8   I2CBC   :7;
  __REG8           :1;
} __i2cbc_bits;


/* ADC control register 0 */
typedef struct {
  __REG16 ADSNM    :2;
  __REG16          :2;
  __REG16 ADRUN    :1;
  __REG16          :1;
  __REG16 SCNC     :1;
  __REG16          :9;
} __adcon0_bits;

/* ADC control register 1 */
typedef struct {
  __REG16 ADSTM    :2;
  __REG16          :2;
  __REG16 STS      :1;
  __REG16          :11;
} __adcon1_bits;

/* ADC control register 2 */
typedef struct {
  __REG16 ACKSEL   :2;
  __REG16          :14;
} __adcon2_bits;

/* ADC interrupt control register */
typedef struct {
  __REG16 INTSN    :1;
  __REG16 INTST    :1;
  __REG16 ADSNIE   :1;
  __REG16 ADSTIE   :1;
  __REG16          :12;
} __adint_bits;

/* ADC forced interrupt register */
typedef struct {
  __REG16 ADFAS    :1;
  __REG16          :15;
} __adfint_bits;

/* ADC result register */
typedef struct {
  __REG16 DT0      :10;
  __REG16          :6;
} __adr0_bits;

typedef struct {
  __REG16 DT1      :10;
  __REG16          :6;
} __adr1_bits;

typedef struct {
  __REG16 DT2      :10;
  __REG16          :6;
} __adr2_bits;

typedef struct {
  __REG16 DT3      :10;
  __REG16          :6;
} __adr3_bits;



#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/

/***************************************************************************
 **
 **  Address mapping
 **
 ***************************************************************************/
__IO_REG16_BIT(ROMSEL, 0xB700000C,__READ_WRITE,__romsel_bits);
__IO_REG32_BIT(RMPCON, 0xB8000010,__READ_WRITE,__rmpcon_bits);


/***************************************************************************
 **
 **  Power management
 **
 ***************************************************************************/
__IO_REG16_BIT(BCKCTL, 0xB7000004,__READ_WRITE,__bckctl_bits);
__IO_REG32_BIT(CLKSTP, 0xB8000004,__READ_WRITE,__clkstp_bits);
__IO_REG32_BIT(CGBCNT0, 0xB8000008,__READ_WRITE,__cgbcnt0_bits);
__IO_REG32_BIT(CKWT, 0xB800000C,__READ_WRITE,__ckwt_bits);


/***************************************************************************
 **
 **  Interrupt controller
 **
 ***************************************************************************/
__IO_REG32_BIT(IRQ, 0x78000000,__READ,__irq_bits);
__IO_REG32_BIT(IRQS, 0x78000004,__READ_WRITE,__irqs_bits);
__IO_REG32_BIT(FIQ, 0x78000008,__READ,__fiq_bits);
__IO_REG32_BIT(FIQRAW, 0x7800000C,__READ,__fiqraw_bits);
__IO_REG32_BIT(FIQEN, 0x78000010,__READ_WRITE,__fiqen_bits);
__IO_REG32_BIT(IRN, 0x78000014,__READ,__irn_bits);
__IO_REG32_BIT(CIL, 0x78000018,__READ_WRITE,__cil_bits);
__IO_REG32_BIT(ILC0, 0x78000020,__READ_WRITE,__ilc0_bits);
__IO_REG32_BIT(ILC1, 0x78000024,__READ_WRITE,__ilc1_bits);
__IO_REG32(CILCL, 0x78000028,__WRITE);
__IO_REG32_BIT(CILE, 0x7800002C,__READ,__cile_bits);
__IO_REG32_BIT(IRCL, 0x7BF00004,__WRITE,__ircl_bits);
__IO_REG32_BIT(IRQA, 0x7BF00010,__READ_WRITE,__irqa_bits);
__IO_REG32_BIT(IDM, 0x7BF00014,__READ_WRITE,__idm_bits);
__IO_REG32_BIT(ILC, 0x7BF00018,__READ_WRITE,__ilc_bits);


/***************************************************************************
 **
 **  Cache memory
 **
 ***************************************************************************/
__IO_REG32_BIT(CON,   0x78200004,__READ_WRITE,__con_bits);
__IO_REG32_BIT(CACHE, 0x78200008,__READ_WRITE,__cache_bits);
__IO_REG32(FLUSH,     0x7820001c,__WRITE);


/***************************************************************************
 **
 **  External memory controller
 **
 ***************************************************************************/
__IO_REG32_BIT(BWC, 0x78100000,__READ_WRITE,__bwc_bits);
__IO_REG32_BIT(IO23BWC, 0x78300000,__READ_WRITE,__io23bw_bits);
__IO_REG32_BIT(ROMAC, 0x78100004,__READ_WRITE,__romac_bits);
__IO_REG32_BIT(RAMAC, 0x78100008,__READ_WRITE,__ramac_bits);
__IO_REG32_BIT(IO01AC, 0x7810000C,__READ_WRITE,__io01ac_bits);
__IO_REG32_BIT(IO23ACY, 0x7830000c,__READ_WRITE,__io23ac_bits);
__IO_REG32_BIT(DBWC, 0x78180000,__READ_WRITE,__dbwc_bits);
__IO_REG32_BIT(DRMC, 0x78180004,__READ_WRITE,__drmc_bits);
__IO_REG32_BIT(DRPC, 0x78180008,__READ_WRITE,__drpc_bits);
__IO_REG32_BIT(SDMD, 0x7818000C,__READ_WRITE,__sdmd_bits);
__IO_REG32_BIT(DCMD, 0x78180010,__READ_WRITE,__dcmd_bits);
__IO_REG32_BIT(RFSH0, 0x78180014,__READ_WRITE,__rfsh0_bits);
__IO_REG32_BIT(RDWC, 0x78180018,__WRITE,__rdwc_bits);
__IO_REG32_BIT(RFSH1, 0x7818001C,__READ_WRITE,__rfsh1_bits);


/***************************************************************************
 **
 **  Direct memory access controller (DMAC)
 **
 ***************************************************************************/
__IO_REG32_BIT(DMAMOD, 0x7BE00000,__READ_WRITE,__dmamod_bits);
__IO_REG32_BIT(DMASTA, 0x7BE00004,__READ,__dmasta_bits);
__IO_REG32_BIT(DMAINT, 0x7BE00008,__READ,__dmaint_bits);
__IO_REG32_BIT(DMACMSK0, 0x7BE00100,__READ_WRITE,__dmacmsk_bits);
__IO_REG32_BIT(DMACTMOD0, 0x7BE00104,__READ_WRITE,__dmactmod_bits);
__IO_REG32(DMACSAD0, 0x7BE00108,__READ_WRITE);
__IO_REG32(DMACDAD0, 0x7BE0010C,__READ_WRITE);
__IO_REG32_BIT(DMACSIZ0, 0x7BE00110,__READ_WRITE,__dmacsiz_bits);
__IO_REG32(DMACCINT0, 0x7BE00114,__WRITE);
__IO_REG32_BIT(DMACMSK1, 0x7BE00200,__READ_WRITE,__dmacmsk_bits);
__IO_REG32_BIT(DMACTMOD1, 0x7BE00204,__READ_WRITE,__dmactmod_bits);
__IO_REG32(DMACSAD1, 0x7BE00208,__READ_WRITE);
__IO_REG32(DMACDAD1, 0x7BE0020C,__READ_WRITE);
__IO_REG32_BIT(DMACSIZ1, 0x7BE00210,__READ_WRITE,__dmacsiz_bits);
__IO_REG32(DMACCINT1, 0x7BE00214,__WRITE);


/***************************************************************************
 **
 **  GPIO
 **
 ***************************************************************************/
__IO_REG16_BIT(GPCTL, 0xB7000000,__READ_WRITE,__gpctl_bits);

__IO_REG16_BIT(GPPOA, 0xB7A01000,__READ_WRITE,__gppoa_bits);
__IO_REG16_BIT(GPPIA, 0xB7A01004,__READ,      __gppia_bits);
__IO_REG16_BIT(GPPMA, 0xB7A01008,__READ_WRITE,__gppma_bits);
__IO_REG16_BIT(GPIEA, 0xB7A0100C,__READ_WRITE,__gpiea_bits);
__IO_REG16_BIT(GPIPA, 0xB7A01010,__READ_WRITE,__gpipa_bits);
__IO_REG16_BIT(GPISA, 0xB7A01014,__READ_WRITE,__gpisa_bits);

__IO_REG16_BIT(GPPOB, 0xB7A01020,__READ_WRITE,__gppob_bits);
__IO_REG16_BIT(GPPIB, 0xB7A01024,__READ,      __gppib_bits);
__IO_REG16_BIT(GPPMB, 0xB7A01028,__READ_WRITE,__gppmb_bits);
__IO_REG16_BIT(GPIEB, 0xB7A0102C,__READ_WRITE,__gpieb_bits);
__IO_REG16_BIT(GPIPB, 0xB7A01030,__READ_WRITE,__gpipb_bits);
__IO_REG16_BIT(GPISB, 0xB7A01034,__READ_WRITE,__gpisb_bits);

__IO_REG16_BIT(GPPOC, 0xB7A01040,__READ_WRITE,__gppoc_bits);
__IO_REG16_BIT(GPPIC, 0xB7A01044,__READ,      __gppic_bits);
__IO_REG16_BIT(GPPMC, 0xB7A01048,__READ_WRITE,__gppmc_bits);
__IO_REG16_BIT(GPIEC, 0xB7A0104C,__READ_WRITE,__gpiec_bits);
__IO_REG16_BIT(GPIPC, 0xB7A01050,__READ_WRITE,__gpipc_bits);
__IO_REG16_BIT(GPISC, 0xB7A01054,__READ_WRITE,__gpisc_bits);

__IO_REG16_BIT(GPPOD, 0xB7A01060,__READ_WRITE,__gppod_bits);
__IO_REG16_BIT(GPPID, 0xB7A01064,__READ,      __gppid_bits);
__IO_REG16_BIT(GPPMD, 0xB7A01068,__READ_WRITE,__gppmd_bits);
__IO_REG16_BIT(GPIED, 0xB7A0106C,__READ_WRITE,__gpied_bits);
__IO_REG16_BIT(GPIPD, 0xB7A01070,__READ_WRITE,__gpipd_bits);
__IO_REG16_BIT(GPISD, 0xB7A01074,__READ_WRITE,__gpisd_bits);

__IO_REG16_BIT(GPPOE, 0xB7A01080,__READ_WRITE,__gppoe_bits);
__IO_REG16_BIT(GPPIE, 0xB7A01084,__READ,      __gppie_bits);
__IO_REG16_BIT(GPPME, 0xB7A01088,__READ_WRITE,__gppme_bits);
__IO_REG16_BIT(GPIEE, 0xB7A0108C,__READ_WRITE,__gpiee_bits);
__IO_REG16_BIT(GPIPE, 0xB7A01090,__READ_WRITE,__gpipe_bits);
__IO_REG16_BIT(GPISE, 0xB7A01094,__READ_WRITE,__gpise_bits);


/***************************************************************************
 **
 **  Watchdog timer (WDT)
 **
 ***************************************************************************/
__IO_REG8(WDTCON, 0xB7E00000,__WRITE);
__IO_REG8_BIT(WDTBCON, 0xB7E00004,__READ_WRITE,__wdtbcon_bits);
__IO_REG8_BIT(WDSTAT, 0xB7E00014,__READ_WRITE,__wdstat_bits);


/***************************************************************************
 **
 **  Timers
 **
 ***************************************************************************/
__IO_REG32_BIT(TMEN, 0xB8001004,__READ_WRITE,__tmen_bits);
__IO_REG32_BIT(TMRLR, 0xB8001008,__READ_WRITE,__tmrlr_bits);
__IO_REG32_BIT(TMOVFR, 0xB8001010,__READ_WRITE,__tmovfr_bits);

__IO_REG16_BIT(TIMECNTL0, 0xB7F00000,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE0, 0xB7F00004,__READ_WRITE);
__IO_REG16(TIMECNT0, 0xB7F00008,__READ);
__IO_REG16(TIMECMP0, 0xB7F0000C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT0, 0xB7F00010,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL1, 0xB7F00020,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE1, 0xB7F00024,__READ_WRITE);
__IO_REG16(TIMECNT1, 0xB7F00028,__READ);
__IO_REG16(TIMECMP1, 0xB7F0002C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT1, 0xB7F00030,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL2, 0xB7F00040,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE2, 0xB7F00044,__READ_WRITE);
__IO_REG16(TIMECNT2, 0xB7F00048,__READ);
__IO_REG16(TIMECMP2, 0xB7F0004C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT2, 0xB7F00050,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL3, 0xB7F00060,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE3, 0xB7F00064,__READ_WRITE);
__IO_REG16(TIMECNT3, 0xB7F00068,__READ);
__IO_REG16(TIMECMP3, 0xB7F0006C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT3, 0xB7F00070,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL4, 0xB7F00080,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE4, 0xB7F00084,__READ_WRITE);
__IO_REG16(TIMECNT4, 0xB7F00088,__READ);
__IO_REG16(TIMECMP4, 0xB7F0008C,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT4, 0xB7F00090,__READ_WRITE,__timestat_bits);

__IO_REG16_BIT(TIMECNTL5, 0xB7F000A0,__READ_WRITE,__timecntl_bits);
__IO_REG16(TIMEBASE5, 0xB7F000A4,__READ_WRITE);
__IO_REG16(TIMECNT5, 0xB7F000A8,__READ);
__IO_REG16(TIMECMP5, 0xB7F000AC,__READ_WRITE);
__IO_REG16_BIT(TIMESTAT5, 0xB7F000B0,__READ_WRITE,__timestat_bits);


/***************************************************************************
 **
 **  PWM generator
 **
 ***************************************************************************/
__IO_REG16(PWR0, 0xB7D00000,__READ_WRITE);
__IO_REG16(PWCY0, 0xB7D00004,__READ_WRITE);
__IO_REG16(PWC0, 0xB7D00008,__READ_WRITE);
__IO_REG16_BIT(PWCON0, 0xB7D0000C,__READ_WRITE,__pwcon0_bits);

__IO_REG16(PWR1, 0xB7D00020,__READ_WRITE);
__IO_REG16(PWCY1, 0xB7D00024,__READ_WRITE);
__IO_REG16(PWC1, 0xB7D00028,__READ_WRITE);
__IO_REG16_BIT(PWCON1, 0xB7D0002C,__READ_WRITE,__pwcon1_bits);

__IO_REG16_BIT(PWINTSTS, 0xB7D0003C,__READ_WRITE,__pwintsts_bits);


/***************************************************************************
 **
 **  SIO
 **
 ***************************************************************************/
__IO_REG32_BIT(SIOBUF, 0xB8002000,__READ_WRITE,__siobuf_bits);
__IO_REG32_BIT(SIOSTA, 0xB8002004,__READ_WRITE,__siosta_bits);
__IO_REG32_BIT(SIOCON, 0xB8002008,__READ_WRITE,__siocon_bits);
__IO_REG32_BIT(SIOBCN, 0xB800200C,__READ_WRITE,__siobcn_bits);
__IO_REG32_BIT(SIOBT, 0xB8002014,__READ_WRITE,__siobt_bits);
__IO_REG32_BIT(SIOTCN, 0xB8002018,__READ_WRITE,__siotcn_bits);


/***************************************************************************
 **
 **  UART
 **
 ***************************************************************************/

/* UARTDLL, UARTRBR and UARTTHR share the same address */
__IO_REG8(UARTRBRTHR, 0xB7B00000,__READ_WRITE);
#define UARTDLL UARTRBRTHR
#define UARTRBR UARTRBRTHR
#define UARTTHR UARTRBRTHR

/* UARTDLM and UARTIER share the same address */
__IO_REG8_BIT(UARTIER, 0xB7B00004,__READ_WRITE,__uartier_bits);
#define UARTDLM UARTIER

/* UARTFCR and UARTIIR share the same address */
__IO_REG8_BIT(UARTFCRIIR, 0xB7B00008,__READ_WRITE,__uartfcriir_bits);
#define UARTFCR     UARTFCRIIR
#define UARTFCR_bit UARTFCRIIR_bit
#define UARTIIR     UARTFCRIIR
#define UARTIIR_bit UARTFCRIIR_bit

__IO_REG8_BIT(UARTLCR, 0xB7B0000C,__READ_WRITE,__uartlcr_bits);
__IO_REG8_BIT(UARTMCR, 0xB7B00010,__READ_WRITE,__uartmcr_bits);
__IO_REG8_BIT(UARTLSR, 0xB7B00014,__READ_WRITE,__uartlsr_bits);
__IO_REG8_BIT(UARTMSR, 0xB7B00018,__READ_WRITE,__uartmsr_bits);
__IO_REG8(UARTSCR, 0xB7B0001C,__READ_WRITE);


/***************************************************************************
 **
 **  Synchronous SIO
 **
 ***************************************************************************/
__IO_REG8(SSIOBUF, 0xB7B01000,__READ_WRITE);
__IO_REG8_BIT(SSIOST, 0xB7B01004,__READ_WRITE,__ssiost_bits);
__IO_REG8_BIT(SSIOINT, 0xB7B01008,__READ_WRITE,__ssioint_bits);
__IO_REG8_BIT(SSIOINTEN, 0xB7B0100C,__READ_WRITE,__ssiointen_bits);
__IO_REG8_BIT(SSIOCON, 0xB7B01010,__READ_WRITE,__ssiocon_bits);
__IO_REG8_BIT(SSIOTSCON, 0xB7B01014,__READ_WRITE,__ssiotscon_bits);


/***************************************************************************
 **
 **  I2C
 **
 ***************************************************************************/
__IO_REG8_BIT(I2CCON, 0xB7800000,__READ_WRITE,__i2ccon_bits);
__IO_REG8_BIT(I2CSAD, 0xB7800004,__READ_WRITE,__i2csad_bits);
__IO_REG8_BIT(I2CCLR, 0xB7800008,__READ_WRITE,__i2cclr_bits);
__IO_REG8_BIT(I2CSR, 0xB780000C,__READ,__i2csr_bits);
__IO_REG8_BIT(I2CIR, 0xB7800010,__READ_WRITE,__i2cir_bits);
__IO_REG8_BIT(I2CIMR, 0xB7800014,__READ_WRITE,__i2cimr_bits);
__IO_REG8(I2CDR, 0xB7800018,__READ_WRITE);
__IO_REG8_BIT(I2CBC, 0xB780001C,__READ_WRITE,__i2cbc_bits);


/***************************************************************************
 **
 **  A/D converter
 **
 ***************************************************************************/
__IO_REG16_BIT(ADCON0, 0xB6001000,__READ_WRITE,__adcon0_bits);
__IO_REG16_BIT(ADCON1, 0xB6001004,__READ_WRITE,__adcon1_bits);
__IO_REG16_BIT(ADCON2, 0xB6001008,__READ_WRITE,__adcon2_bits);
__IO_REG16_BIT(ADINT, 0xB600100C,__READ_WRITE,__adint_bits);
__IO_REG16_BIT(ADFINT, 0xB6001010,__READ_WRITE,__adfint_bits);
__IO_REG16_BIT(ADR0, 0xB6001014,__READ_WRITE,__adr0_bits);
__IO_REG16_BIT(ADR1, 0xB6001018,__READ_WRITE,__adr1_bits);
__IO_REG16_BIT(ADR2, 0xB600101C,__READ_WRITE,__adr2_bits);
__IO_REG16_BIT(ADR3, 0xB6001020,__READ_WRITE,__adr3_bits);


/* Assembler specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */




/***************************************************************************
 **
 **   ML675001 interrupt sources
 **  
 ***************************************************************************/
#define SYSTIMINT      0     /*    System timer                            */
#define WDTIMINT       1     /*    Watchdog timer                          */
#define WDITIMINT      2     /*    Watchdog timer interval timer operation */
//                     3     /*    (unused)                                */
#define GPIOAINT       4     /*    GPIOA                                   */
#define GPIOBINT       5     /*    GPIOB                                   */
#define GPIOCINT       6     /*    GPIOC                                   */
#define GPIODEINT      7     /*    GPIOD/GPIOE                             */
#define SWIREQINT      8     /*    Software interrupt requests             */
#define UARTINT        9     /*    UART                                    */
#define SIOINT        10     /*    SIO                                     */
#define ADCINT        11     /*    AD                                      */
#define PWM0INT       12     /*    PWM output 0                            */
#define PWM1INT       13     /*    PWM output 1                            */
#define SSIOINTR      14     /*    SSIO                                    */
#define I2CINT        15     /*    I2C                                     */
#define TIMER0INT     16     /*    Timer 0                                 */
#define TIMER1INT     17     /*    Timer 1                                 */
#define TIMER2INT     18     /*    Timer 2                                 */
#define TIMER3INT     19     /*    Timer 3                                 */
#define TIMER4INT     20     /*    Timer 4                                 */
#define TIMER5INT     21     /*    Timer 5                                 */
#define EXT0INT       22     /*    External interrupt 0                    */
//                    23     /*    (unused)                                */
#define DMA0INT       24     /*    DMA channel 0                           */
#define DMA1INT       25     /*    DMA channel 1                           */
#define EXT1INT       26     /*    External interrupt 1                    */
//                    27     /*    (unused)                                */
#define EXT2INT       28     /*    External interrupt 2                    */
//                    29     /*    (unused)                                */
//                    30     /*    (unused)                                */
#define EXT3INT       31     /*    External interrupt 3                    */

#endif    /* __ML675001_H */

