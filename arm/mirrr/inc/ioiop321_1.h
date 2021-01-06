/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    Intel XScale IOP321 (80321)
 **
 **    Used with ICCARM and AARM.
 **
 **    (c) Copyright IAR Systems 2003
 **
 **    $Revision: 1.10 $
 **
 ***************************************************************************/

#ifndef __IOIOP321_H
#define __IOIOP321_H


#if (((__TID__ >> 8) & 0x7F) != 0x4F)     /* 0x4F = 79 dec */
#error This file should only be compiled by ICCARM/AARM
#endif


#include "io_macros.h"

/***************************************************************************
 ***************************************************************************
 **
 **    IOP321 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C specific declarations  ************************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* ATU command register */
typedef struct {
  __REG16 iose   :1;
  __REG16 me     :1;
  __REG16 bme    :1;
  __REG16 sce    :1;
  __REG16 mwie   :1;
  __REG16 vgapse :1;
  __REG16 per    :1;
  __REG16 adse   :1;
  __REG16 serre  :1;
  __REG16 fbtbe  :1;
  __REG16        :6;
} __atucmd_bits;

/* ATU status register */
typedef struct {
  __REG16         :4;
  __REG16 caps    :1;
  __REG16 cap66   :1;
  __REG16 udfs    :1;
  __REG16 fbtb    :1;
  __REG16 mpe     :1;
  __REG16 devselt :2;
  __REG16 tat     :1;
  __REG16 tam     :1;
  __REG16 ma      :1;
  __REG16 serra   :1;
  __REG16 dpe     :1;
} __atusr_bits;

/* ATU Latency timer register */
typedef struct {
  __REG8 ltg      :3;
  __REG8 plt      :5;
} __atult_bits;

/* ATU Header type register */
typedef struct {
  __REG8 pciht    :7;
  __REG8 sfd      :1;
} __atuhtr_bits;

/* ATU BIST register */
typedef struct {
  __REG8 bcc      :4;
  __REG8          :2;
  __REG8 startb   :1;
  __REG8 bcap     :1;
} __atubistr_bits;

/* ATU Inbound ATU base address register */
typedef struct {
  __REG32 msi     :1;
  __REG32 ti      :2;
  __REG32 pi      :1;
  __REG32         :8;
  __REG32 tba     :20;
} __atuiabar_bits;

/* ATU expansion rom address register */
typedef struct {
  __REG32 ade     :1;
  __REG32         :11;
  __REG32 erba    :20;
} __atuerbar_bits;

/* Inbound ATU limit register */
typedef struct {
  __REG32         :12;
  __REG32 itl     :20;
} __atuialr_bits;

/* Inbound ATU translate value register */
typedef struct {
  __REG32         :12;
  __REG32 iatv    :20;
} __atuiatvr_bits;

/* ATU expansion ROM limit register */
typedef struct {
  __REG32         :12;
  __REG32 erl     :20;
} __atuerlr_bits;

/* ATU expansion ROM limit register */
typedef struct {
  __REG32         :12;
  __REG32 ertv    :20;
} __atuertvr_bits;

/* ATU outbound I/O window translate value register */
typedef struct {
  __REG32         :15;
  __REG32 oiowtv  :17;
} __atuoiowtvr_bits;

/* ATU outbound memory window translate value register */
typedef struct {
  __REG32 bo      :2;
  __REG32         :24;
  __REG32 omwv    :6;
} __atuomwtvr_bits;

/* ATU configuration register */
typedef struct {
  __REG32         :1;
  __REG32 oae     :1;
  __REG32         :1;
  __REG32 abie    :1;
  __REG32         :4;
  __REG32 dae     :1;
  __REG32 pdie    :1;
  __REG32         :5;
  __REG32 adts    :1;
  __REG32 pma     :1;
  __REG32         :1;
  __REG32 dau2gte :1;
  __REG32 ada     :1;
  __REG32         :12;
} __atucr_bits;

/* ATU PCI configuration and status register */
typedef struct {
  __REG32         :1;
  __REG32 cpr     :1;
  __REG32 ccr     :1;
  __REG32         :1;
  __REG32 rpb     :1;
  __REG32 rib     :1;
  __REG32         :1;
  __REG32         :1;
  __REG32 pb64c   :1;
  __REG32         :1;
  __REG32 bo66    :1;
  __REG32         :1;
  __REG32 dtv     :1;
  __REG32         :1;
  __REG32 itqb    :1;
  __REG32 otqb    :1;
  __REG32 pxm     :2;
  __REG32 daape   :1;
  __REG32         :13;
} __atupcsr_bits;

/* ATU Interrupt status register */
typedef struct {
  __REG32 pmpe    :1;
  __REG32 ptat    :1;
  __REG32 ptam    :1;
  __REG32 pma     :1;
  __REG32 psd     :1;
  __REG32         :2;
  __REG32 ibma    :1;
  __REG32 abi     :1;
  __REG32 dpe     :1;
  __REG32 pa      :1;
  __REG32 pst     :1;
  __REG32 rscem   :1;
  __REG32 iscem   :1;
  __REG32 aimw1bu :1;
  __REG32         :17;
} __atuisr_bits;

/* ATU Interrupt status register */
typedef struct {
  __REG32 aetae   :1;   /* ATU ECC Target Abort Enable */
  __REG32 aiese   :1;   /* ATU Inbound Error SERR# Enable */
  __REG32 apmpeim :1;   /* ATU PCI Master Parity Error Interrupt Mask */
  __REG32 aptatim :1;   /* ATU PCI Target Abort (Target) Interrupt Mask */
  __REG32 aptamim :1;   /* ATU PCI Target Abort (Master) Interrupt Mask */
  __REG32 apmaim  :1;   /* ATU PCI Master Abort Interrupt Mask */
  __REG32 asaim   :1;   /* ATU SERR# Asserted Interrupt Mask */
  __REG32 adpeim  :1;   /* ATU Detected Parity Error Interrupt Mask */
  __REG32 pstim   :1;   /* Power State Transition Interrupt Mask */
  __REG32 rscemim :1;   /* Received Split Completion Error Message Interrupt
                           Mask */
  __REG32 iscemim :1;   /* Initiated Split Completion Error Message Interrupt
                           Mask */
  __REG32 aimw1bum:1;   /* ATU Inbound Memory Window 1 Base Updated Mask */
  __REG32         :20;
} __atuimr_bits;

/* ATU PCI bus drive strength control register */
typedef struct {
  __REG32 puds    :6;
  __REG32 pdds    :6;
  __REG32 src     :4;
  __REG32 pbsr    :1;
  __REG32         :15;
} __atupdscr_bits;


/* ATU power management capabilities register */
typedef struct {
  __REG16 ver     :3;
  __REG16 pmec    :1;
  __REG16         :1;
  __REG16 dsi     :1;
  __REG16 auxc    :3;
  __REG16 d1s     :1;
  __REG16 d2s     :1;
  __REG16 pmes    :5;
} __atuapmcr_bits;

/* ATU power management control/status register */
typedef struct {
  __REG16 ps      :2;
  __REG16         :6;
  __REG16 pmeen   :1;
  __REG16         :6;
  __REG16 pmes    :1;
} __atuapmcsr_bits;

/* ATU PCI-X command register */
typedef struct {
  __REG16 dpere   :1;
  __REG16 ero     :1;
  __REG16 mmrbc   :2;
  __REG16 most    :3;
  __REG16         :9;
} __atupcixcmd_bits;

/* ATU PCI-X status register */
typedef struct {
  __REG32 fn      :3;
  __REG32 dn      :5;
  __REG32 bn      :8;
  __REG32 pci64   :1;
  __REG32 cap133  :1;
  __REG32 scd     :1;
  __REG32 usc     :1;
  __REG32 cplxdev :1;
  __REG32 dmmrbc  :2;
  __REG32 dmost   :3;
  __REG32 dmcrs   :3;
  __REG32 rscem   :1;
  __REG32         :2;
} __atupcixsr_bits;


/* MU message control register */
typedef struct {
  __REG16 me      :1;
  __REG16 mmc     :3;
  __REG16 mme     :3;
  __REG16 as64    :1;
  __REG16         :8;
} __mumsgctrl_bits;

/* MU message address register */
typedef struct {
  __REG32         :2;
  __REG32 addr    :30;
} __mumsgaddr_bits;

/* MU inbound doorbell register */
typedef struct {
  __REG32 no0     :1;
  __REG32 no1     :1;
  __REG32 no2     :1;
  __REG32 no3     :1;
  __REG32 no4     :1;
  __REG32 no5     :1;
  __REG32 no6     :1;
  __REG32 no7     :1;
  __REG32 no8     :1;
  __REG32 no9     :1;
  __REG32 no10    :1;
  __REG32 no11    :1;
  __REG32 no12    :1;
  __REG32 no13    :1;
  __REG32 no14    :1;
  __REG32 no15    :1;
  __REG32 no16    :1;
  __REG32 no17    :1;
  __REG32 no18    :1;
  __REG32 no19    :1;
  __REG32 no20    :1;
  __REG32 no21    :1;
  __REG32 no22    :1;
  __REG32 no23    :1;
  __REG32 no24    :1;
  __REG32 no25    :1;
  __REG32 no26    :1;
  __REG32 no27    :1;
  __REG32 no28    :1;
  __REG32 no29    :1;
  __REG32 no30    :1;
  __REG32 ei      :1;
} __muidr_bits;

/* MU inbound interrupt status/mask register */
typedef struct {
  __REG32 im0     :1;
  __REG32 im1     :1;
  __REG32 idr     :1;
  __REG32 edr     :1;
  __REG32 ipq     :1;
  __REG32 ofq     :1;
  __REG32 ir      :1;
  __REG32         :25;
} __muiismr_bits;

/* MSI outbound doorbell register */
typedef struct {
  __REG32 no0     :1;
  __REG32 no1     :1;
  __REG32 no2     :1;
  __REG32 no3     :1;
  __REG32 no4     :1;
  __REG32 no5     :1;
  __REG32 no6     :1;
  __REG32 no7     :1;
  __REG32 no8     :1;
  __REG32 no9     :1;
  __REG32 no10    :1;
  __REG32 no11    :1;
  __REG32 no12    :1;
  __REG32 no13    :1;
  __REG32 no14    :1;
  __REG32 no15    :1;
  __REG32 no16    :1;
  __REG32 no17    :1;
  __REG32 no18    :1;
  __REG32 no19    :1;
  __REG32 no20    :1;
  __REG32 no21    :1;
  __REG32 no22    :1;
  __REG32 no23    :1;
  __REG32 no24    :1;
  __REG32 no25    :1;
  __REG32 no26    :1;
  __REG32 no27    :1;
  __REG32 no28    :1;
  __REG32         :3;
} __muodr_bits;

/* MU outbound interrupt status/mask register */
typedef struct {
  __REG32 om0     :1;
  __REG32 om1     :1;
  __REG32 odi     :1;
  __REG32 opq     :1;
  __REG32 opia    :1;
  __REG32         :27;
} __muoismr_bits;

/* MU configuration register */
typedef struct {
  __REG32 cqe     :1;
  __REG32 cqs     :5;
  __REG32         :26;
} __mumucr_bits;

/* MU queue base address register */
typedef struct {
  __REG32         :20;
  __REG32 qba     :12;
} __muqbar_bits;

/* MU Inbound  free head/free tail/post head/post tail registers.
   MU Outbound free head/free tail/post head/post tail registers. */
typedef struct {
  __REG32         :2;
  __REG32 ptr     :18;
  __REG32 qba     :12;
} __muptr_bits;

/* MU index address register */
typedef struct {
  __REG32         :2;
  __REG32 ia      :10;
  __REG32         :20;
} __muiar_bits;

/* DMA channel control register */
typedef struct {
  __REG32 ce      :1;
  __REG32 cr      :1;
  __REG32         :30;
} __dmaccr_bits;

/* DMA channel status register */
typedef struct {
  __REG32         :1;
  __REG32 upste   :1;
  __REG32 ptaf    :1;
  __REG32 pmaf    :1;
  __REG32         :1;
  __REG32 ibmaf   :1;
  __REG32         :2;
  __REG32 eocif   :1;
  __REG32 eotif   :1;
  __REG32 caf     :1;
  __REG32         :21;
} __dmacsr_bits;

/* DMA descriptor address register */
typedef struct {
  __REG32         :5;
  __REG32 nda     :27;
} __dmadar_bits;

/* DMA byte count register */
typedef struct {
  __REG32 bc      :24;
  __REG32         :8;
} __dmabcr_bits;

/* DMA descriptor control register */
typedef struct {
  __REG32 pt      :4;
  __REG32 ie      :1;
  __REG32 dace    :1;
  __REG32 mtmte   :1;
  __REG32         :25;
} __dmadcr_bits;

/* MC DDR SDRAM initialization register */
typedef struct {
  __REG32 sdsc    :4;
  __REG32         :28;
} __mcsdir_bits;

/* MC DDR SDRAM control register */
typedef struct {
  __REG32         :1;
  __REG32 dt      :1;
  __REG32 dbw     :1;
  __REG32         :29;
} __mcsdcr_bits;

/* MC SDRAM base register */
typedef struct {
  __REG32         :25;
  __REG32 ba      :7;
} __mcsdbr_bits;

/* MC SDRAM boundary register */
typedef struct {
  __REG32 sb      :6;
  __REG32         :25;
  __REG32 st      :1;
} __mcsbr_bits;

/* MC ECCR control register */
typedef struct {
  __REG32 sbere   :1;
  __REG32 mbere   :1;
  __REG32 sbece   :1;
  __REG32 ee      :1;
  __REG32         :28;
} __mceccr_bits;


/* MC ECC log registers */
typedef struct {
  __REG32 syn     :8;
  __REG32 et      :1;
  __REG32         :3;
  __REG32 rw      :1;
  __REG32         :3;
  __REG32 er      :8;
  __REG32         :8;
} __mcelog_bits;

/* MC ECC address registers */
typedef struct {
  __REG32         :2;
  __REG32 ea      :30;
} __mcecar_bits;

/* MC ECC test register */
typedef struct {
  __REG32  em     :8;
  __REG32         :24;
} __mcectst_bits;

/* MC interrupt status register */
typedef struct {
  __REG32  ee0    :1;
  __REG32  ee1    :1;
  __REG32  een    :1;
  __REG32         :29;
} __mcisr_bits;

/* MC refresh frequency register */
typedef struct {
  __REG32  ri     :13;
  __REG32         :19;
} __mcrfr_bits;

/* MC drive strength registers */
typedef struct {
  __REG32  ds     :7;
  __REG32         :25;
} __mcdsr_bits;

/* MC data strobe delay register */
typedef struct {
  __REG32  dsmd   :5;
  __REG32  dssd   :5;
  __REG32         :22;
} __mcdsdr_bits;

/* MC data strobe delay register */
typedef struct {
  __REG32  red    :4;
  __REG32  rempde :1;
  __REG32         :27;
} __mcredr_bits;

/* PBI control register */
typedef struct {
  __REG32  pe     :1;
  __REG32  pfc    :2;
  __REG32  cpbbe  :1;
  __REG32         :28;
} __pbicr_bits;

/* PBI status register */
typedef struct {
  __REG32  bcore  :1;
  __REG32         :31;
} __pbisr_bits;

/* PBI base address registers */
typedef struct {
  __REG32  bw     :2;
  __REG32  adws   :3;
  __REG32         :1;
  __REG32  rcws   :3;
  __REG32  fwe    :1;
  __REG32         :2;
  __REG32  mwba   :20;
} __pbbar_bits;

/* PBI limit registers */
typedef struct {
  __REG32         :12;
  __REG32 mwl     :20;
} __pblr_bits;

/* PBI drive strength control register */
typedef struct {
  __REG32 puds    :6;
  __REG32 pdds    :6;
  __REG32 slc     :4;
  __REG32         :16;
} __pbdscr_bits;

/* PPM global time mode register */
typedef struct {
  __REG32 gtscoie :1;
  __REG32         :1;
  __REG32 gce     :1;
  __REG32         :29;
} __ppmgmtr_bits;

/* PPM event select register */
typedef struct {
  __REG32 mi      :4; /* monitored interface */
  __REG32         :12;
  __REG32 pmie    :1;
  __REG32         :15;
} __ppmesr_bits;

/* PPM event monitoring interrupt status register */
typedef struct {
  __REG32 gts     :1;
  __REG32 pec1    :1;
  __REG32 pec2    :1;
  __REG32 pec3    :1;
  __REG32 pec4    :1;
  __REG32 pec5    :1;
  __REG32 pec6    :1;
  __REG32 pec7    :1;
  __REG32 pec8    :1;
  __REG32 pec9    :1;
  __REG32 pec10   :1;
  __REG32 pec11   :1;
  __REG32 pec12   :1;
  __REG32 pec13   :1;
  __REG32 pec14   :1;
  __REG32         :17;
} __ppmemisr_bits;

/* AU internal arbitration control register */
typedef struct {
  __REG32 amp     :2;
  __REG32         :2;
  __REG32 d0p     :2;
  __REG32 d1p     :2;
  __REG32         :2;
  __REG32 cp      :2;
  __REG32 aap     :2;
  __REG32 pp      :2;
  __REG32         :16;
} __auiacr_bits;

/* AU multi transaction timer register */
typedef struct {
  __REG32 pv      :8;
  __REG32         :24;
} __aumttr_bits;


/* GPIO registers */
typedef struct {
  __REG32 io0     :1;
  __REG32 io1     :1;
  __REG32 io2     :1;
  __REG32 io3     :1;
  __REG32 io4     :1;
  __REG32 io5     :1;
  __REG32 io6     :1;
  __REG32 io7     :1;
  __REG32         :24;
} __gpr_bits;


/* ICU interrupt control register */
typedef struct {
  __REG32 d0eot   :1;
  __REG32 d0eoc   :1;
  __REG32 d1eot   :1;
  __REG32 d1eoc   :1;
  __REG32         :2;
  __REG32 aaeot   :1;
  __REG32 aaeoc   :1;
  __REG32         :1;
  __REG32 t0      :1;
  __REG32 t1      :1;
  __REG32 i2c0    :1;
  __REG32 i2c1    :1;
  __REG32 mu      :1;
  __REG32 asb     :1;
  __REG32 ppm     :1;
  __REG32 cp      :1;
  __REG32 pbiue   :1;
  __REG32 ae      :1;
  __REG32 mcue    :1;
  __REG32 d0e     :1;
  __REG32 d1e     :1;
  __REG32         :1;
  __REG32 aaue    :1;
  __REG32 mue     :1;
  __REG32 sp      :1;
  __REG32 muipq   :1;
  __REG32 x0      :1;
  __REG32 x1      :1;
  __REG32 x2      :1;
  __REG32 x3      :1;
  __REG32         :1;
} __icuintctl_bits;

/* ICU interrupt steering/source registers */
typedef struct {
  __REG32 d0eot   :1;
  __REG32 d0eoc   :1;
  __REG32 d1eot   :1;
  __REG32 d1eoc   :1;
  __REG32         :2;
  __REG32 aaeot   :1;
  __REG32 aaeoc   :1;
  __REG32         :1;
  __REG32 t0      :1;
  __REG32 t1      :1;
  __REG32 i2c0    :1;
  __REG32 i2c1    :1;
  __REG32 mu      :1;
  __REG32 asb     :1;
  __REG32 ppm     :1;
  __REG32 cp      :1;
  __REG32 pbiue   :1;
  __REG32 ae      :1;
  __REG32 mcue    :1;
  __REG32 d0e     :1;
  __REG32 d1e     :1;
  __REG32         :1;
  __REG32 aaue    :1;
  __REG32 mue     :1;
  __REG32 sp      :1;
  __REG32 muipq   :1;
  __REG32 x0      :1;
  __REG32 x1      :1;
  __REG32 x2      :1;
  __REG32 x3      :1;
  __REG32 hpi     :1;
} __icuintsr_bits;


/* ICU interrupt routing select register */
typedef struct {
  __REG32 x0      :1;
  __REG32 x1      :1;
  __REG32 x2      :1;
  __REG32 x3      :1;
  __REG32         :28;
} __icupirsr_bits;

/* TMR timer mode registers */
typedef struct {
  __REG32 tc      :1;
  __REG32 enable  :1;
  __REG32 reload  :1;
  __REG32 pri     :1;
  __REG32 csel    :2;
  __REG32         :26;
} __tmr_bits;

/* TMR timer interrupt status register */
typedef struct {
  __REG32 t0      :1;
  __REG32 t1      :1;
  __REG32         :30;
} __tmrtisr_bits;

/* AA accelerator control register */
typedef struct {
  __REG32 en      :1;
  __REG32 cr      :1;
  __REG32 be512   :1;
  __REG32         :29;
} __aaacr_bits;

/* AA accelerator status register */
typedef struct {
  __REG32         :5;
  __REG32 ma      :1;
  __REG32         :2;
  __REG32 eoc     :1;
  __REG32 eot     :1;
  __REG32 aa      :1;
  __REG32         :21;
} __aaasr_bits;

/* AA accelerator descriptor address register */
typedef struct {
  __REG32         :5;
  __REG32 addr    :27;
} __aaadar_bits;

/* AA accelerator byte count register */
typedef struct {
  __REG32 bc      :24;
  __REG32         :8;
} __aaabcr_bits;

/* AA accelerator descriptor control register */
typedef struct {
  __REG32 ie      :1;
  __REG32 b1cc    :3;
  __REG32 b2cc    :3;
  __REG32 b3cc    :3;
  __REG32 b4cc    :3;
  __REG32 b5cc    :3;
  __REG32 b6cc    :3;
  __REG32 b7cc    :3;
  __REG32 b8cc    :3;
  __REG32 sbci    :2;
  __REG32         :1;
  __REG32 tc      :1;
  __REG32 perr    :1;
  __REG32 pen     :1;
  __REG32 dwe     :1;
} __aaadcr_bits;

/* AA extended descriptor control register 0 */
typedef struct {
  __REG32         :1;
  __REG32 b9cc    :3;
  __REG32 b10cc   :3;
  __REG32 b11cc   :3;
  __REG32 b12cc   :3;
  __REG32 b13cc   :3;
  __REG32 b14cc   :3;
  __REG32 b15cc   :3;
  __REG32 b16cc   :3;
  __REG32         :7;
} __aaedcr0_bits;

/* AA extended descriptor control register 1 */
typedef struct {
  __REG32         :1;
  __REG32 b17cc   :3;
  __REG32 b18cc   :3;
  __REG32 b19cc   :3;
  __REG32 b20cc   :3;
  __REG32 b21cc   :3;
  __REG32 b22cc   :3;
  __REG32 b23cc   :3;
  __REG32 b24cc   :3;
  __REG32         :7;
} __aaedcr1_bits;

/* AA extended descriptor control register 2 */
typedef struct {
  __REG32         :1;
  __REG32 b25cc   :3;
  __REG32 b26cc   :3;
  __REG32 b27cc   :3;
  __REG32 b28cc   :3;
  __REG32 b29cc   :3;
  __REG32 b30cc   :3;
  __REG32 b31cc   :3;
  __REG32 b32cc   :3;
  __REG32         :7;
} __aaedcr2_bits;

/* SSP SSC control register 0 */
typedef struct {
  __REG32 dss     :4;
  __REG32 frf     :2;
  __REG32 ecs     :1;
  __REG32 sse     :1;
  __REG32 scr     :8;
  __REG32         :16;
} __sspsscr0_bits;

/* SSP SSC control register 1 */
typedef struct {
  __REG32 rie     :1;
  __REG32 tie     :1;
  __REG32 lbm     :1;
  __REG32 spo     :1;
  __REG32 sph     :1;
  __REG32 mwds    :1;
  __REG32 tft     :4;
  __REG32 rft     :4;
  __REG32 efwr    :1;
  __REG32 strf    :1;
  __REG32         :16;
} __sspsscr1_bits;

/* SSP status register */
typedef struct {
  __REG32         :2;
  __REG32 tnf     :1;
  __REG32 rne     :1;
  __REG32 bsy     :1;
  __REG32 tfs     :1;
  __REG32 rfs     :1;
  __REG32 ror     :1;
  __REG32 tfl     :4;
  __REG32 rfl     :4;
  __REG32         :16;
} __sspsssr_bits;

/* SSP interrupt test register */
typedef struct {
  __REG32         :5;
  __REG32 ttfs    :1;
  __REG32 trfs    :1;
  __REG32 tror    :1;
  __REG32         :24;
} __sspssitr_bits;

/* SSP data register */
typedef struct {
  __REG32 data    :16;
  __REG32         :16;
} __sspssdr_bits;

/* I2C control register */
typedef struct {
  __REG32 start   :1;
  __REG32 stop    :1;
  __REG32 acknack :1;
  __REG32 tb      :1;
  __REG32 ma      :1;
  __REG32 scle    :1;
  __REG32 iue     :1;
  __REG32 gcd     :1;
  __REG32 iteie   :1;
  __REG32 irfie   :1;
  __REG32 beie    :1;
  __REG32 ssdie   :1;
  __REG32 aldie   :1;
  __REG32 sadie   :1;
  __REG32 ur      :1;
  __REG32 fm      :1;
  __REG32         :16;
} __i2cicr_bits;

/* I2C status register */
typedef struct {
  __REG32 rwm     :1;
  __REG32 acknack :1;
  __REG32 ub      :1;
  __REG32 ibb     :1;
  __REG32 ssd     :1;
  __REG32 ald     :1;
  __REG32 ite     :1;
  __REG32 irf     :1;
  __REG32 gcad    :1;
  __REG32 sad     :1;
  __REG32 bed     :1;
  __REG32         :21;
} __i2cisr_bits;

/* I2C slave address register */
typedef struct {
  __REG32 isa     :7;
  __REG32         :25;
} __i2csar_bits;

/* I2C data buffer register */
typedef struct {
  __REG32 idb     :8;
  __REG32         :24;
} __i2cidbr_bits;

/* I2C bus monitor register */
typedef struct {
  __REG32 sdas    :1;
  __REG32 scls    :1;
  __REG32         :30;
} __i2cibmr_bits;


// ATU revision id register and class code register
// ATURID(8bit) and ATUCCR(24bit) share the same 32bit word.
typedef union {
  //__ATU_ATURID
  struct {
    __REG32 aturid  :8;
    __REG32 atuccr  :24;
  };

  //__ATU_ATUCCR_
  struct {
    __REG32         :8;
    __REG32 pi      :8;
    __REG32 sc      :8;
    __REG32 bc      :8;
  };
} __atuccr_bits;

#endif    /* __IAR_SYSTEMS_ICC__ */


/* Common declarations  ****************************************************/


/***************************************************************************
 **
 **  ATU - address translation unit
 **
 ***************************************************************************/

__IO_REG16(__ATU_ATUVID,0xffffe100,__READ_WRITE);
__IO_REG16(__ATU_ATUDID,0xffffe102,__READ_WRITE);
__IO_REG16_BIT(__ATU_ATUCMD,0xffffe104,__READ_WRITE,__atucmd_bits);
__IO_REG16_BIT(__ATU_ATUSR, 0xffffe106,__READ_WRITE,__atusr_bits);

// ATU revision id register and class code register
// ATURID(8bit) and ATUCCR(24bit) share the same 32bit word.
__IO_REG32_BIT(__ATU_ATUCCR_, 0xffffe108,__READ_WRITE,__atuccr_bits);
#define   __ATU_ATURID     (__ATU_ATUCCR__bit.aturid)
#define   __ATU_ATUCCR_bit (__ATU_ATUCCR__bit)
#define   __ATU_ATUCCR     (__ATU_ATUCCR__bit.atuccr)

__IO_REG8(__ATU_ATUCLSR, 0xffffe10c,__READ_WRITE);
__IO_REG8_BIT(__ATU_ATULT, 0xffffe10d,__READ_WRITE,__atult_bits);
__IO_REG8_BIT(__ATU_ATHTR, 0xffffe10e,__READ_WRITE,__atuhtr_bits);
__IO_REG8_BIT(__ATU_ATUBISTR, 0xffffe10f,__READ_WRITE,__atubistr_bits);
__IO_REG32_BIT(__ATU_IABAR0, 0xffffe110,__READ_WRITE,__atuiabar_bits);
__IO_REG32(__ATU_IAUBAR0, 0xffffe114,__READ_WRITE);
__IO_REG32_BIT(__ATU_IABAR1, 0xffffe118,__READ_WRITE,__atuiabar_bits);
__IO_REG32(__ATU_IAUBAR1, 0xffffe11c,__READ_WRITE);
__IO_REG32_BIT(__ATU_IABAR2, 0xffffe120,__READ_WRITE,__atuiabar_bits);
__IO_REG32(__ATU_IAUBAR2, 0xffffe124,__READ_WRITE);
/*****RESERVED: 0xffffe128 */
__IO_REG16(__ATU_ASVIR,0xffffe12c,__READ_WRITE);
__IO_REG16(__ATU_ASIR,0xffffe12e,__READ_WRITE);
__IO_REG32_BIT(__ATU_ERBAR, 0xffffe130,__READ_WRITE,__atuerbar_bits);
__IO_REG8(__ATU_CAP_PTR, 0xffffe134,__READ);
/*****RESERVED: 0xffffe135 */
/*****RESERVED: 0xffffe138 */
__IO_REG8(__ATU_ATUILR, 0xffffe13c,__READ_WRITE);
__IO_REG8(__ATU_ATUIPR, 0xffffe13d,__READ_WRITE);
__IO_REG8(__ATU_ATUMGNT, 0xffffe13e,__READ_WRITE);
__IO_REG8(__ATU_ATUMLAT, 0xffffe13f,__READ_WRITE);
__IO_REG32_BIT(__ATU_IALR0, 0xffffe140,__READ_WRITE,__atuialr_bits);
__IO_REG32_BIT(__ATU_IATVR0, 0xffffe144,__READ_WRITE,__atuiatvr_bits);
__IO_REG32_BIT(__ATU_ERLR, 0xffffe148,__READ_WRITE,__atuerlr_bits);
__IO_REG32_BIT(__ATU_ERTVR, 0xffffe14c,__READ_WRITE,__atuertvr_bits);
__IO_REG32_BIT(__ATU_IALR1, 0xffffe150,__READ_WRITE,__atuialr_bits);
__IO_REG32_BIT(__ATU_IALR2, 0xffffe154,__READ_WRITE,__atuialr_bits);
__IO_REG32_BIT(__ATU_IATVR2, 0xffffe158,__READ_WRITE,__atuiatvr_bits);
__IO_REG32_BIT(__ATU_OIOWTVR, 0xffffe15c,__READ_WRITE,__atuoiowtvr_bits);
__IO_REG32_BIT(__ATU_OMWTVR0, 0xffffe160,__READ_WRITE,__atuomwtvr_bits);
__IO_REG32(__ATU_OUMWTVR0, 0xffffe164,__READ_WRITE);
__IO_REG32_BIT(__ATU_OMWTVR1, 0xffffe168,__READ_WRITE,__atuomwtvr_bits);
__IO_REG32(__ATU_OUMWTVR1, 0xffffe16c,__READ_WRITE);
/*****RESERVED: 0xffffe170 */
/*****RESERVED: 0xffffe174 */
__IO_REG32(__ATU_OUDWTVR, 0xffffe178,__READ_WRITE);
__IO_REG32_BIT(__ATU_ATUCR, 0xffffe180,__READ_WRITE,__atucr_bits);
__IO_REG32_BIT(__ATU_PCSR,  0xffffe184,__READ_WRITE,__atupcsr_bits);
__IO_REG32_BIT(__ATU_ATUISR,0xffffe188,__READ_WRITE,__atuisr_bits);
__IO_REG32_BIT(__ATU_ATUIMR,0xffffe18c,__READ_WRITE,__atuimr_bits);
__IO_REG32_BIT(__ATU_IABAR3,0xffffe190,__READ_WRITE,__atuiabar_bits);
__IO_REG32(__ATU_IAUBAR3, 0xffffe194,__READ_WRITE);
__IO_REG32_BIT(__ATU_IALR3,0xffffe198,__READ_WRITE,__atuialr_bits);
__IO_REG32_BIT(__ATU_IATVR3,0xffffe19c,__READ_WRITE,__atuiatvr_bits);
/*****RESERVED: 0xffffe1a0 */
__IO_REG32(__ATU_OCCAR, 0xffffe1a4,__READ_WRITE);
/*****RESERVED: 0xffffe1a8 */
__IO_REG32(__ATU_OCCDR, 0xffffe1ac,__READ_WRITE);
/*****RESERVED: 0xffffe1b0 */
/*****RESERVED: 0xffffe1b4 */
/*****RESERVED: 0xffffe1b8 */
__IO_REG32_BIT(__ATU_PDSCR,0xffffe1bc,__READ_WRITE,__atupdscr_bits);
__IO_REG8(__ATU_PM_CAP_ID, 0xffffe1c0,__READ);
__IO_REG8(__ATU_PM_NEXTPTR, 0xffffe1c1,__READ);
__IO_REG16_BIT(__ATU_APMCR, 0xffffe1c2,__READ,__atuapmcr_bits);
__IO_REG16_BIT(__ATU_APMCSR, 0xffffe1c4,__READ_WRITE,__atuapmcsr_bits);
/*****RESERVED: 0xffffe1c6 */
/*****RESERVED: 0xffffe1c8 */
/*****RESERVED: 0xffffe1cc */

/* Registers in 0xffffe1d0 - 0xffffe1dd defined in MU section below */

/*****RESERVED: 0xffffe1de */
__IO_REG8(__ATU_PCIX_CAP_ID, 0xffffe1e0,__READ);
__IO_REG8(__ATU_PCIX_NEXTPTR, 0xffffe1e1,__READ);
__IO_REG16_BIT(__ATU_PCIXCMD, 0xffffe1e2,__READ_WRITE,__atupcixcmd_bits);
__IO_REG32_BIT(__ATU_PCIXSR,0xffffe1e4,__READ_WRITE,__atupcixsr_bits);
/*****RESERVED: 0xffffe1e8 */


/***************************************************************************
 **
 **  MU - messaging unit
 **
 ***************************************************************************/

__IO_REG8(__MSI_CAP_ID, 0xffffe1d0,__READ);
__IO_REG8(__MSI_NEXT_PTR, 0xffffe1d1,__READ);
__IO_REG16_BIT(__MU_MSG_CTRL, 0xffffe1d2,__READ_WRITE,__mumsgctrl_bits);
__IO_REG32_BIT(__MU_MSGADDR,0xffffe1d4,__READ_WRITE,__mumsgaddr_bits);
__IO_REG32_BIT(__MU_MSGUADDR,0xffffe1d8,__READ_WRITE,__mumsgaddr_bits);
__IO_REG16(__MU_MSGDATA,0xffffe1dc,__READ_WRITE);

__IO_REG32(__MU_IMR0, 0xffffe310,__READ_WRITE);
__IO_REG32(__MU_IMR1, 0xffffe314,__READ_WRITE);
__IO_REG32(__MU_OMR0, 0xffffe318,__READ_WRITE);
__IO_REG32(__MU_OMR1, 0xffffe31C,__READ_WRITE);
__IO_REG32_BIT(__MU_IDR, 0xffffe320,__READ_WRITE,__muidr_bits);
__IO_REG32_BIT(__MU_IISR,0xffffe324,__READ_WRITE,__muiismr_bits);
__IO_REG32_BIT(__MU_IIMR,0xffffe328,__READ_WRITE,__muiismr_bits);
__IO_REG32_BIT(__MU_ODR, 0xffffe32c,__READ_WRITE,__muodr_bits);
__IO_REG32_BIT(__MU_OISR, 0xffffe330,__READ_WRITE,__muoismr_bits);
__IO_REG32_BIT(__MU_OIMR, 0xffffe334,__READ_WRITE,__muoismr_bits);

/*****RESERVED: 0xffffe338 - 0xffffe34f */

__IO_REG32_BIT(__MU_MUCR, 0xffffe350,__READ_WRITE,__mumucr_bits);
__IO_REG32_BIT(__MU_QBAR, 0xffffe354,__READ_WRITE,__muqbar_bits);
/*****RESERVED: 0xffffe358 */
/*****RESERVED: 0xffffe35c */
__IO_REG32_BIT(__MU_IFHPR, 0xffffe360,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_IFTPR, 0xffffe364,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_IPHPR, 0xffffe368,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_IPTPR, 0xffffe36c,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_OFHPR, 0xffffe370,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_OFTPR, 0xffffe374,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_OPHPR, 0xffffe378,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_OPTPR, 0xffffe37c,__READ_WRITE,__muptr_bits);
__IO_REG32_BIT(__MU_IAR, 0xffffe380,__READ_WRITE,__muiar_bits);
/*****RESERVED: 0xffffe384 - 0xffffe3ff */


/***************************************************************************
 **
 ** DMA - DMA controller
 **
 ***************************************************************************/
/* DMA channel 0 */
__IO_REG32_BIT(__DMA_CCR0, 0xffffe400,__READ_WRITE,__dmaccr_bits);
__IO_REG32_BIT(__DMA_CSR0, 0xffffe404,__READ_WRITE,__dmacsr_bits);
/*****RESERVED: 0xffffe408 */
__IO_REG32_BIT(__DMA_DAR0, 0xffffe40c,__READ,__dmadar_bits);
__IO_REG32_BIT(__DMA_NDAR0, 0xffffe410,__READ_WRITE,__dmadar_bits);
__IO_REG32(__DMA_PADR0, 0xffffe414,__READ);
__IO_REG32(__DMA_PUADR0, 0xffffe418,__READ);
__IO_REG32(__DMA_LADR0, 0xffffe41c,__READ);
__IO_REG32_BIT(__DMA_BCR0, 0xffffe420,__READ,__dmabcr_bits);
__IO_REG32_BIT(__DMA_DCR0, 0xffffe424,__READ_WRITE,__dmadcr_bits);
/*****RESERVED: 0xffffe428 - 0xffffe43f */

/* DMA channel 1 */
__IO_REG32_BIT(__DMA_CCR1, 0xffffe440,__READ_WRITE,__dmaccr_bits);
__IO_REG32_BIT(__DMA_CSR1, 0xffffe444,__READ_WRITE,__dmacsr_bits);
/*****RESERVED: 0xffffe448 */
__IO_REG32_BIT(__DMA_DAR1, 0xffffe44c,__READ,__dmadar_bits);
__IO_REG32_BIT(__DMA_NDAR1, 0xffffe450,__READ_WRITE,__dmadar_bits);
__IO_REG32(__DMA_PADR1, 0xffffe454,__READ);
__IO_REG32(__DMA_PUADR1, 0xffffe458,__READ);
__IO_REG32(__DMA_PULADR1, 0xffffe45c,__READ);
__IO_REG32_BIT(__DMA_BCR1, 0xffffe460,__READ,__dmabcr_bits);
__IO_REG32_BIT(__DMA_DCR1, 0xffffe464,__READ_WRITE,__dmadcr_bits);
/*****RESERVED: 0xffffe468 - 0xffffe4ff */


/***************************************************************************
 **
 **  MC - memory controller
 **
 ***************************************************************************/
__IO_REG32_BIT(__MC_SDIR, 0xffffe500,__READ_WRITE,__mcsdir_bits);
__IO_REG32_BIT(__MC_SDCR, 0xffffe504,__READ_WRITE,__mcsdcr_bits);
__IO_REG32_BIT(__MC_SDBR, 0xffffe508,__READ_WRITE,__mcsdbr_bits);
__IO_REG32_BIT(__MC_SBR0, 0xffffe50c,__READ_WRITE,__mcsbr_bits);
__IO_REG32_BIT(__MC_SBR1, 0xffffe510,__READ_WRITE,__mcsbr_bits);
/*****RESERVED: 0xffffe514 - 0xffffe533 */

__IO_REG32_BIT(__MC_ECCR, 0xffffe534,__READ_WRITE,__mceccr_bits);
__IO_REG32_BIT(__MC_ELOG0, 0xffffe538,__READ,__mcelog_bits);
__IO_REG32_BIT(__MC_ELOG1, 0xffffe53c,__READ,__mcelog_bits);
__IO_REG32_BIT(__MC_ECAR0, 0xffffe540,__READ,__mcecar_bits);
__IO_REG32_BIT(__MC_ECAR1, 0xffffe544,__READ,__mcecar_bits);
__IO_REG32_BIT(__MC_ECTST, 0xffffe548,__READ_WRITE,__mcectst_bits);
__IO_REG32_BIT(__MC_MCISR, 0xffffe54c,__READ_WRITE,__mcisr_bits);
__IO_REG32_BIT(__MC_RFR, 0xffffe550,__READ_WRITE,__mcrfr_bits);
__IO_REG32_BIT(__MC_DBUDSR, 0xffffe554,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_DBDDSR, 0xffffe558,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_CUDSR, 0xffffe55c,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_CDDSR, 0xffffe560,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_CEUDSR, 0xffffe564,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_CSUDSR, 0xffffe56c,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_CSDDSR, 0xffffe570,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_REUDSR, 0xffffe574,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_REDDSR, 0xffffe578,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_ABUDSR, 0xffffe57c,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_ABDDSR, 0xffffe580,__READ_WRITE,__mcdsr_bits);
__IO_REG32_BIT(__MC_DSDR, 0xffffe584,__READ_WRITE,__mcdsdr_bits);
__IO_REG32_BIT(__MC_REDR, 0xffffe588,__READ_WRITE,__mcredr_bits);
/*****RESERVED: 0xffffe58c - 0xffffe67f */

/***************************************************************************
 **
 **  PBI - peripheral bus interface unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__PBI_PBCR, 0xffffe680,__READ_WRITE,__pbicr_bits);
__IO_REG32_BIT(__PBI_PBSR, 0xffffe684,__READ_WRITE,__pbisr_bits);

__IO_REG32_BIT(__PBI_PBBAR0, 0xffffe688,__READ_WRITE,__pbbar_bits);
__IO_REG32_BIT(__PBI_PBLR0, 0xffffe68c,__READ_WRITE,__pblr_bits);
__IO_REG32_BIT(__PBI_PBBAR1, 0xffffe690,__READ_WRITE,__pbbar_bits);
__IO_REG32_BIT(__PBI_PBLR1, 0xffffe694,__READ_WRITE,__pblr_bits);
__IO_REG32_BIT(__PBI_PBBAR2, 0xffffe698,__READ_WRITE,__pbbar_bits);
__IO_REG32_BIT(__PBI_PBLR2, 0xffffe69c,__READ_WRITE,__pblr_bits);
__IO_REG32_BIT(__PBI_PBBAR3, 0xffffe6a0,__READ_WRITE,__pbbar_bits);
__IO_REG32_BIT(__PBI_PBLR3, 0xffffe6a4,__READ_WRITE,__pblr_bits);
__IO_REG32_BIT(__PBI_PBBAR4, 0xffffe6a8,__READ_WRITE,__pbbar_bits);
__IO_REG32_BIT(__PBI_PBLR4, 0xffffe6ac,__READ_WRITE,__pblr_bits);
__IO_REG32_BIT(__PBI_PBBAR5, 0xffffe6b0,__READ_WRITE,__pbbar_bits);
__IO_REG32_BIT(__PBI_PBLR5, 0xffffe6b4,__READ_WRITE,__pblr_bits);
__IO_REG32_BIT(__PBI_PBDSCR, 0xffffe6b8,__READ_WRITE,__pbdscr_bits);
/*****RESERVED: 0xffffe6bc */

__IO_REG32(__PBI_PMBR0, 0xffffe6c0,__READ_WRITE);
/*****RESERVED: 0xffffe6c4 - 0xffffe6dc */
__IO_REG32(__PBI_PMBR1, 0xffffe6e0,__READ_WRITE);
__IO_REG32(__PBI_PMBR2, 0xffffe6e4,__READ_WRITE);
/*****RESERVED: 0xffffe6e8 */
/*****RESERVED: 0xffffe6ec - 0xffffe6ff */


/***************************************************************************
 **
 **  PPM - peripheral performance monitoring unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__PPM_GMTR, 0xffffe700,__READ_WRITE,__ppmgmtr_bits);
__IO_REG32_BIT(__PPM_ESR, 0xffffe704,__READ_WRITE,__ppmesr_bits);
__IO_REG32_BIT(__PPM_EMISR, 0xffffe708,__READ_WRITE,__ppmemisr_bits);
/*****RESERVED: 0xffffe70c */
__IO_REG32(__PPM_GTSR, 0xffffe710,__READ);
__IO_REG32(__PPM_PECR1, 0xffffe714,__READ);
__IO_REG32(__PPM_PECR2, 0xffffe718,__READ);
__IO_REG32(__PPM_PECR3, 0xffffe71c,__READ);
__IO_REG32(__PPM_PECR4, 0xffffe720,__READ);
__IO_REG32(__PPM_PECR5, 0xffffe724,__READ);
__IO_REG32(__PPM_PECR6, 0xffffe728,__READ);
__IO_REG32(__PPM_PECR7, 0xffffe72c,__READ);
__IO_REG32(__PPM_PECR8, 0xffffe730,__READ);
__IO_REG32(__PPM_PECR9, 0xffffe734,__READ);
__IO_REG32(__PPM_PECR10, 0xffffe738,__READ);
__IO_REG32(__PPM_PECR11, 0xffffe73c,__READ);
__IO_REG32(__PPM_PECR12, 0xffffe740,__READ);
__IO_REG32(__PPM_PECR13, 0xffffe744,__READ);
__IO_REG32(__PPM_PECR14, 0xffffe748,__READ);
/*****RESERVED: 0xffffe74c - 0xffffe77f */


/***************************************************************************
 **
 **  AU - arbitration unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__AU_IACR, 0xffffe780,__READ_WRITE,__auiacr_bits);
__IO_REG32_BIT(__AU_MTTR1, 0xffffe784,__READ_WRITE,__aumttr_bits);
__IO_REG32_BIT(__AU_MTTR2, 0xffffe788,__READ_WRITE,__aumttr_bits);
/*****RESERVED: 0xffffe78c - 0xffffe7bf */


/***************************************************************************
 **
 **  GPIO - general purpose I/O
 **
 ***************************************************************************/
__IO_REG32(__GPIO_DEVID, 0xffffe7c0,__READ);
__IO_REG32_BIT(__GPIO_GPOE, 0xffffe7c4,__READ_WRITE,__gpr_bits);
__IO_REG32_BIT(__GPIO_GPID, 0xffffe7c8,__READ_WRITE,__gpr_bits);
__IO_REG32_BIT(__GPIO_GPOD, 0xffffe7cc,__READ_WRITE,__gpr_bits);


/***************************************************************************
 **
 **  ICU - interrupt controller unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__ICU_PIRSR, 0xffffe1ec,__READ_WRITE,__icupirsr_bits);

//Note: INTCTL, INTSTR, IINTSRC, FINTSRC are read-only from memory mapped
// address space
__IO_REG32_BIT(__ICU_INTCTL, 0xffffe7d0,__READ,__icuintctl_bits);
__IO_REG32_BIT(__ICU_INTSTR, 0xffffe7d4,__READ,__icuintsr_bits);
__IO_REG32_BIT(__ICU_IINTSRC, 0xffffe7d8,__READ,__icuintsr_bits);
__IO_REG32_BIT(__ICU_FINTSRC, 0xffffe7dc,__READ,__icuintsr_bits);

/***************************************************************************
 **
 **  TMR - timers
 **
 ***************************************************************************/
// Note: The timer registers are read-only from memory mapped
// address space
__IO_REG32_BIT(__TMR_TMR0, 0xffffe7e0,__READ,__tmr_bits);
__IO_REG32_BIT(__TMR_TMR1, 0xffffe7e4,__READ,__tmr_bits);
__IO_REG32(__TMR_TCR0, 0xffffe7e8,__READ);
__IO_REG32(__TMR_TCR1, 0xffffe7ec,__READ);
__IO_REG32(__TMR_TRR0, 0xffffe7f0,__READ);
__IO_REG32(__TMR_TRR1, 0xffffe7f4,__READ);
__IO_REG32_BIT(__TMR_TISR, 0xffffe7f8,__READ,__tmrtisr_bits);
__IO_REG32(__TMR_WDTCR, 0xffffe7fc,__READ);


/***************************************************************************
 **
 **  AA - application accelerator unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__AA_ACR, 0xffffe800,__READ_WRITE,__aaacr_bits);
__IO_REG32_BIT(__AA_ASR, 0xffffe804,__READ_WRITE,__aaasr_bits);
__IO_REG32_BIT(__AA_ADAR, 0xffffe808,__READ,__aaadar_bits);
__IO_REG32_BIT(__AA_ANDAR, 0xffffe80c,__READ_WRITE,__aaadar_bits);
__IO_REG32(__AA_SAR1, 0xffffe810,__READ);
__IO_REG32(__AA_SAR2, 0xffffe814,__READ);
__IO_REG32(__AA_SAR3, 0xffffe818,__READ);
__IO_REG32(__AA_SAR4, 0xffffe81c,__READ);
__IO_REG32(__AA_DAR, 0xffffe820,__READ);
__IO_REG32_BIT(__AA_ABCR, 0xffffe824,__READ,__aaabcr_bits);
__IO_REG32_BIT(__AA_ADCR, 0xffffe828,__READ,__aaadcr_bits);
__IO_REG32(__AA_SAR5, 0xffffe82c,__READ);
__IO_REG32(__AA_SAR6, 0xffffe830,__READ);
__IO_REG32(__AA_SAR7, 0xffffe834,__READ);
__IO_REG32(__AA_SAR8, 0xffffe838,__READ);
__IO_REG32_BIT(__AA_EDCR0, 0xffffe83c,__READ,__aaedcr0_bits);
__IO_REG32(__AA_SAR9, 0xffffe840,__READ);
__IO_REG32(__AA_SAR10, 0xffffe844,__READ);
__IO_REG32(__AA_SAR11, 0xffffe848,__READ);
__IO_REG32(__AA_SAR12, 0xffffe84c,__READ);
__IO_REG32(__AA_SAR13, 0xffffe850,__READ);
__IO_REG32(__AA_SAR14, 0xffffe854,__READ);
__IO_REG32(__AA_SAR15, 0xffffe858,__READ);
__IO_REG32(__AA_SAR16, 0xffffe85c,__READ);
__IO_REG32_BIT(__AA_EDCR1, 0xffffe860 ,__READ,__aaedcr1_bits);
__IO_REG32(__AA_SAR17, 0xffffe864,__READ);
__IO_REG32(__AA_SAR18, 0xffffe868,__READ);
__IO_REG32(__AA_SAR19, 0xffffe86c,__READ);
__IO_REG32(__AA_SAR20, 0xffffe870,__READ);
__IO_REG32(__AA_SAR21, 0xffffe874,__READ);
__IO_REG32(__AA_SAR22, 0xffffe878,__READ);
__IO_REG32(__AA_SAR23, 0xffffe87c,__READ);
__IO_REG32(__AA_SAR24, 0xffffe880,__READ);
__IO_REG32_BIT(__AA_EDCR2, 0xffffe884,__READ,__aaedcr2_bits);
__IO_REG32(__AA_SAR25, 0xffffe888,__READ);
__IO_REG32(__AA_SAR26, 0xffffe88c,__READ);
__IO_REG32(__AA_SAR27, 0xffffe890,__READ);
__IO_REG32(__AA_SAR28, 0xffffe894,__READ);
__IO_REG32(__AA_SAR29, 0xffffe898,__READ);
__IO_REG32(__AA_SAR30, 0xffffe89c,__READ);
__IO_REG32(__AA_SAR31, 0xffffe8a0,__READ);
__IO_REG32(__AA_SAR32, 0xffffe8a4,__READ);
/*****RESERVED: 0xffffe8a8 - 0xffffe8ff */
/*****RESERVED: 0xffffe900 - 0xffffefff */
/*****RESERVED: 0xfffff000 - 0xfffff5ff */

/***************************************************************************
 **
 **  SSP - serial port unit
 **
 ***************************************************************************/
__IO_REG32_BIT(__SSP_SSCR0, 0xfffff600,__READ_WRITE,__sspsscr0_bits);
__IO_REG32_BIT(__SSP_SSCR1, 0xfffff604,__READ_WRITE,__sspsscr1_bits);
__IO_REG32_BIT(__SSP_SSSR, 0xfffff608,__READ_WRITE,__sspsssr_bits);
__IO_REG32_BIT(__SSP_SSITR, 0xfffff60c,__WRITE,__sspssitr_bits);
__IO_REG32_BIT(__SSP_SSDR, 0xfffff610,__READ_WRITE,__sspssdr_bits);
/*****RESERVED: 0xfffff614 - 0xfffff67f */

/***************************************************************************
 **
 **  I2C - I2C bus interface units
 **
 ***************************************************************************/
__IO_REG32_BIT(__I2C_ICR0, 0xfffff680,__READ_WRITE,__i2cicr_bits);
__IO_REG32_BIT(__I2C_ISR0, 0xfffff684,__READ_WRITE,__i2cisr_bits);
__IO_REG32_BIT(__I2C_SAR0, 0xfffff688,__READ_WRITE,__i2csar_bits);
__IO_REG32_BIT(__I2C_IDBR0, 0xfffff68c,__READ_WRITE,__i2cidbr_bits);
/*****RESERVED: 0xfffff690 */
__IO_REG32_BIT(__I2C_IBMR0, 0xfffff694,__READ,__i2cibmr_bits);

__IO_REG32_BIT(__I2C_ICR1, 0xfffff6a0,__READ_WRITE,__i2cicr_bits);
__IO_REG32_BIT(__I2C_ISR1, 0xfffff6a4,__READ_WRITE,__i2cisr_bits);
__IO_REG32_BIT(__I2C_SAR1, 0xfffff6a8,__READ_WRITE,__i2csar_bits);
__IO_REG32_BIT(__I2C_IDBR1, 0xfffff6ac,__READ_WRITE,__i2cidbr_bits);
/*****RESERVED: 0xfffff6b0 */
__IO_REG32_BIT(__I2C_IBMR1, 0xfffff6b4,__READ,__i2cibmr_bits);
/*****RESERVED: 0xfffff6b8 - 0xfffff6ff */


/***************************************************************************
 **  Assembler specific declarations
 ***************************************************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

#endif    /* __IOIOP321_H */
