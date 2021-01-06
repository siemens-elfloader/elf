/***************************************************************************
 **
 **    This file defines the Special Function Registers for
 **    NetSilicon NS9360
 **
 **    Used with ARM IAR c/c++ Compiler and Assembler
 **
 **    (c) Copyright IAR Systems 2005
 **
 **    $Revision: 1.4 $
 **
 ***************************************************************************/

#ifndef __IONS9360_H
#define __IONS9360_H

#if (((__TID__ >> 8) & 0x7F) != 0x4F)
#error This file should only be compiled by ARM IAR compiler and assembler
#endif

#include "io_macros.h"


/***************************************************************************
 ***************************************************************************
 **
 **    NS9360 SPECIAL FUNCTION REGISTERS
 **
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/

/* C-compiler specific declarations  ***************************************/

#ifdef __IAR_SYSTEMS_ICC__

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

/* AHB Arbiter Gen Configuration register */
typedef struct {
	__REG32	EXMA	: 1;
	__REG32		:31;
} __ahbconf_bits;

/* BRCx registers */
typedef struct {
	__REG32	HMSTR_CH3	: 4;
	__REG32	BRF_CH3	: 2;
	__REG32		: 1;
	__REG32	CEB_CH3	: 1;
	__REG32	HMSTR_CH2	: 4;
	__REG32	BRF_CH2	: 2;
	__REG32		: 1;
	__REG32	CEB_CH2	: 1;
	__REG32	HMSTR_CH1	: 4;
	__REG32	BRF_CH1	: 2;
	__REG32		: 1;
	__REG32	CEB_CH1	: 1;
	__REG32	HMSTR_CH0	: 4;
	__REG32	BRF_CH0	: 2;
	__REG32		: 1;
	__REG32	CEB_CH0	: 1;
} __brc0_bits;
	
typedef struct {
	__REG32	HMSTR_CH7	: 4;
	__REG32	BRF_CH7	: 2;
	__REG32		: 1;
	__REG32	CEB_CH7	: 1;
	__REG32	HMSTR_CH6	: 4;
	__REG32	BRF_CH6	: 2;
	__REG32		: 1;
	__REG32	CEB_CH6	: 1;
	__REG32	HMSTR_CH5	: 4;
	__REG32	BRF_CH5	: 2;
	__REG32		: 1;
	__REG32	CEB_CH5	: 1;
	__REG32	HMSTR_CH4	: 4;
	__REG32	BRF_CH4	: 2;
	__REG32		: 1;
	__REG32	CEB_CH4	: 1;
} __brc1_bits;

typedef struct {
	__REG32	HMSTR_CH11	: 4;
	__REG32	BRF_CH11	: 2;
	__REG32		: 1;
	__REG32	CEB_CH11	: 1;
	__REG32	HMSTR_CH10	: 4;
	__REG32	BRF_CH10	: 2;
	__REG32		: 1;
	__REG32	CEB_CH10	: 1;
	__REG32	HMSTR_CH9	: 4;
	__REG32	BRF_CH9	: 2;
	__REG32		: 1;
	__REG32	CEB_CH9	: 1;
	__REG32	HMSTR_CH8	: 4;
	__REG32	BRF_CH8	: 2;
	__REG32		: 1;
	__REG32	CEB_CH8	: 1;
} __brc2_bits;

typedef struct {
	__REG32	HMSTR_CH15	: 4;
	__REG32	BRF_CH15	: 2;
	__REG32		: 1;
	__REG32	CEB_CH15	: 1;
	__REG32	HMSTR_CH14	: 4;
	__REG32	BRF_CH14	: 2;
	__REG32		: 1;
	__REG32	CEB_CH14	: 1;
	__REG32	HMSTR_CH13	: 4;
	__REG32	BRF_CH13	: 2;
	__REG32		: 1;
	__REG32	CEB_CH13	: 1;
	__REG32	HMSTR_CH12	: 4;
	__REG32	BRF_CH12	: 2;
	__REG32		: 1;
	__REG32	CEB_CH12	: 1;
} __brc3_bits;



/* Interrupt Config Register Level 0-3 */
typedef struct {
	__REG32	ISD_3	: 5;
	__REG32	IT_3	: 1;
	__REG32	INV_3	: 1;
	__REG32	IE_3	: 1;
	__REG32	ISD_2	: 5;
	__REG32	IT_2	: 1;
	__REG32	INV_2	: 1;
	__REG32	IE_2	: 1;
	__REG32	ISD_1	: 5;
	__REG32	IT_1	: 1;
	__REG32	INV_1	: 1;
	__REG32	IE_1	: 1;
	__REG32	ISD_0	: 5;
	__REG32	IT_0	: 1;
	__REG32	INV_0	: 1;
	__REG32	IE_0	: 1;
} __intconfig0_bits;

/* Interrupt Config Register Level 4-7 */
typedef struct {
	__REG32	ISD_7	: 5;
	__REG32	IT_7	: 1;
	__REG32	INV_7	: 1;
	__REG32	IE_7	: 1;
	__REG32	ISD_6	: 5;
	__REG32	IT_6	: 1;
	__REG32	INV_6	: 1;
	__REG32	IE_6	: 1;
	__REG32	ISD_5	: 5;
	__REG32	IT_5	: 1;
	__REG32	INV_5	: 1;
	__REG32	IE_5	: 1;
	__REG32	ISD_4	: 5;
	__REG32	IT_4	: 1;
	__REG32	INV_4	: 1;
	__REG32	IE_4	: 1;
} __intconfig1_bits;

/* Interrupt Config Register Level 8-11 */
typedef struct {
	__REG32	ISD_11	: 5;
	__REG32	IT_11	: 1;
	__REG32	INV_11	: 1;
	__REG32	IE_11	: 1;
	__REG32	ISD_10	: 5;
	__REG32	IT_10	: 1;
	__REG32	INV_10	: 1;
	__REG32	IE_10	: 1;
	__REG32	ISD_9	: 5;
	__REG32	IT_9	: 1;
	__REG32	INV_9	: 1;
	__REG32	IE_9	: 1;
	__REG32	ISD_8	: 5;
	__REG32	IT_8	: 1;
	__REG32	INV_8	: 1;
	__REG32	IE_8	: 1;
} __intconfig2_bits;

/* Interrupt Config Register Level 12-15 */
typedef struct {
	__REG32	ISD_15	: 5;
	__REG32	IT_15	: 1;
	__REG32	INV_15	: 1;
	__REG32	IE_15	: 1;
	__REG32	ISD_14	: 5;
	__REG32	IT_14	: 1;
	__REG32	INV_14	: 1;
	__REG32	IE_14	: 1;
	__REG32	ISD_13	: 5;
	__REG32	IT_13	: 1;
	__REG32	INV_13	: 1;
	__REG32	IE_13	: 1;
	__REG32	ISD_12	: 5;
	__REG32	IT_12	: 1;
	__REG32	INV_12	: 1;
	__REG32	IE_12	: 1;
} __intconfig3_bits;

/* Interrupt Config Register Level 16-19 */
typedef struct {
	__REG32	ISD_19	: 5;
	__REG32	IT_19	: 1;
	__REG32	INV_19	: 1;
	__REG32	IE_19	: 1;
	__REG32	ISD_18	: 5;
	__REG32	IT_18	: 1;
	__REG32	INV_18	: 1;
	__REG32	IE_18	: 1;
	__REG32	ISD_17	: 5;
	__REG32	IT_17	: 1;
	__REG32	INV_17	: 1;
	__REG32	IE_17	: 1;
	__REG32	ISD_16	: 5;
	__REG32	IT_16	: 1;
	__REG32	INV_16	: 1;
	__REG32	IE_16	: 1;
} __intconfig4_bits;

/* Interrupt Config Register Level 20-23 */
typedef struct {
	__REG32	ISD_23	: 5;
	__REG32	IT_23	: 1;
	__REG32	INV_23	: 1;
	__REG32	IE_23	: 1;
	__REG32	ISD_22	: 5;
	__REG32	IT_22	: 1;
	__REG32	INV_22	: 1;
	__REG32	IE_22	: 1;
	__REG32	ISD_21	: 5;
	__REG32	IT_21	: 1;
	__REG32	INV_21	: 1;
	__REG32	IE_21	: 1;
	__REG32	ISD_20	: 5;
	__REG32	IT_20	: 1;
	__REG32	INV_20	: 1;
	__REG32	IE_20	: 1;
} __intconfig5_bits;

/* Interrupt Config Register Level 24-27 */
typedef struct {
	__REG32	ISD_27	: 5;
	__REG32	IT_27	: 1;
	__REG32	INV_27	: 1;
	__REG32	IE_27	: 1;
	__REG32	ISD_26	: 5;
	__REG32	IT_26	: 1;
	__REG32	INV_26	: 1;
	__REG32	IE_26	: 1;
	__REG32	ISD_25	: 5;
	__REG32	IT_25	: 1;
	__REG32	INV_25	: 1;
	__REG32	IE_25	: 1;
	__REG32	ISD_24	: 5;
	__REG32	IT_24	: 1;
	__REG32	INV_24	: 1;
	__REG32	IE_24	: 1;
} __intconfig6_bits;

/* Interrupt Config Register Level 28-31 */
typedef struct {
	__REG32	ISD_31	: 5;
	__REG32	IT_31	: 1;
	__REG32	INV_31	: 1;
	__REG32	IE_31	: 1;
	__REG32	ISD_30	: 5;
	__REG32	IT_30	: 1;
	__REG32	INV_30	: 1;
	__REG32	IE_30	: 1;
	__REG32	ISD_29	: 5;
	__REG32	IT_29	: 1;
	__REG32	INV_29	: 1;
	__REG32	IE_29	: 1;
	__REG32	ISD_28	: 5;
	__REG32	IT_28	: 1;
	__REG32	INV_28	: 1;
	__REG32	IE_28	: 1;
} __intconfig7_bits;

/* Timer Interrupt Status register */
typedef struct {
	__REG32	TIS	:16;
	__REG32		:16;
} __timintstatus_bits;

/* Software Watchdog Configuration register */
typedef struct {
	__REG32	SWTCS	: 3;
	__REG32		: 1;
	__REG32	SWWIC	: 1;
	__REG32	SWWI	: 1;
	__REG32		: 1;
	__REG32	SWWE	: 1;
	__REG32	SDBG	: 1;
	__REG32		:23;
} __swwdconfig_bits;

/* Clock Configuration register */
typedef struct {
	__REG32	MACC	: 1;
	__REG32		: 3;
	__REG32	MCC	: 1;
	__REG32	LCC	: 1;
	__REG32	BBC	: 1;
	__REG32	LPCS	: 3;
	__REG32	I2C	: 1;
	__REG32	RTC	: 1;
	__REG32	SERAB	: 1;
	__REG32	SERCD	: 1;
	__REG32	USBH	: 1;
	__REG32	USBD	: 1;
	__REG32	_1284	: 1;
	__REG32	BBDMA	: 1;
	__REG32	MC0	: 1;
	__REG32		:13;
} __clockconfig_bits;

/* Reset and Sleep Control register */
typedef struct {
	__REG32	MACM	: 1;
	__REG32		: 3;
	__REG32	MEMC	: 1;
	__REG32	LCDC	: 1;
	__REG32	BBT	: 1;
	__REG32		: 9;
	__REG32	EI0WE	: 1;
	__REG32	EWE	: 1;
	__REG32	SMWE	: 1;
	__REG32	CSE	: 1;
	__REG32	I2CW	: 1;
	__REG32	BBW	: 1;
	__REG32		: 2;
	__REG32	RSTAT	: 3;
	__REG32		: 5;
} __rsslctrl_bits;

/* Misc Sys Config, Status register */
typedef struct {
	__REG32	IRAM0	: 1;
	__REG32		: 2;
	__REG32	ENDM	: 1;
	__REG32		: 1;
	__REG32	CS1P	: 1;
	__REG32		: 2;
	__REG32	CS1DW	: 2;
	__REG32	CS1DB	: 1;
	__REG32	BMM	: 1;
	__REG32		: 4;
	__REG32	ID	: 8;
	__REG32	REV	: 8;
} __miscsysstatus_bits;

/* PLL Configuration register */
typedef struct {
	__REG32	NDSW	: 5;
	__REG32		: 2;
	__REG32	FSEL	: 2;
	__REG32	PLLBW	: 1;
	__REG32		: 5;
	__REG32	PLLSW	: 1;
	__REG32	PLLND	: 5;
	__REG32		: 2;
	__REG32	PLLFS	: 2;
	__REG32		: 7;
} __pllconfig_bits;

/* Active Interrupt Level Status register */
typedef struct {
	__REG32	INITD	: 6;
	__REG32		: 26;
} __activeintlvlstatus_bits;

/* Timer Control registers */
typedef struct {
	__REG32	REN	: 1;
	__REG32	TSZ	: 1;
	__REG32	UDS	: 1;
	__REG32	INTS	: 1;
	__REG32	TM	: 2;
	__REG32	TLCS	: 3;
	__REG32	INTC	: 1;
	__REG32	TDBG	: 1;
	__REG32		: 4;
	__REG32	TEN	: 1;
	__REG32		: 16;
} __timercontrol_bits;

/* System Memory Chip Select 0 Dynamic/Static Memory Base registers */
typedef struct {
	__REG32		:12;
	__REG32	CS0B	:20;
} __systemmemselect0base_bits;

/* System Memory Chip Select 0 Dynamic/Static Memory Mask registers */
typedef struct {
	__REG32	CSE0	: 1;
	__REG32		:11;
	__REG32	CS0M	:20;
} __systemmemselect0mask_bits;

/* System Memory Chip Select 1 Dynamic/Static Memory Base registers */
typedef struct {
	__REG32		:12;
	__REG32	CS1B	:20;
} __systemmemselect1base_bits;

/* System Memory Chip Select 1 Dynamic/Static Memory Mask registers */
typedef struct {
	__REG32	CSE1	: 1;
	__REG32		:11;
	__REG32	CS1M	:20;
} __systemmemselect1mask_bits;

/* System Memory Chip Select 2 Dynamic/Static Memory Base registers */
typedef struct {
	__REG32		:12;
	__REG32	CS2B	:20;
} __systemmemselect2base_bits;

/* System Memory Chip Select 2 Dynamic/Static Memory Mask registers */
typedef struct {
	__REG32	CSE2	: 1;
	__REG32		:11;
	__REG32	CS2M	:20;
} __systemmemselect2mask_bits;

/* System Memory Chip Select 3 Dynamic/Static Memory Base registers */
typedef struct {
	__REG32		:12;
	__REG32	CS3B	:20;
} __systemmemselect3base_bits;

/* System Memory Chip Select 3 Dynamic/Static Memory Mask registers */
typedef struct {
	__REG32	CSE3	: 1;
	__REG32		:11;
	__REG32	CS3M	:20;
} __systemmemselect3mask_bits;

/* External interrupt control register */
typedef struct {
	__REG32	LVEDG	: 1;
	__REG32	PLTY	: 1;
	__REG32	CLR	: 1;
	__REG32	STS	: 1;
	__REG32		:28;
} __extinterruptcontrol_bits;

/* Control Register */
typedef struct {
	__REG32	MCEN	: 1;
	__REG32	ADDM	: 1;
	__REG32	LPM	: 1;
	__REG32		:29;
} __controlregister_bits;

/* Status Register */
typedef struct {
	__REG32	BUSY	: 1;
	__REG32	WBS	: 1;
	__REG32	SA	: 1;
	__REG32		:29;
} __statusregister_bits;

/* Configuration register */
typedef struct {
	__REG32	END	: 1;
	__REG32		:31;
} __configurationregister_bits;

/* Dynamic Memory Control Register */
typedef struct {
	__REG32	CE	: 1;
	__REG32		: 1;
	__REG32	SR	: 1;
	__REG32		: 4;
	__REG32	SDRAMInit	: 2;
	__REG32		: 5;
	__REG32	nRP	: 1;
	__REG32		:17;
} __dynamicmemorycontrol_bits;

/* Dynamic Memory Refresh Timer register */
typedef struct {
	__REG32	REFRESH	:11;
	__REG32		:21;
} __dynamicmemoryrefresh_bits;

/* Dynamic Memory Read Config register */
typedef struct {
	__REG32	RD	: 2;
	__REG32		:30;
} __dynamicmemoryreadconfig_bits;

/* Dynamic Memory Precharge Command Period register */
typedef struct {
	__REG32	RP	: 2;
	__REG32		:30;
} __dynamicmemoryprecharge_bits;

/* Dynamic Memory Active to Precharge Command Period register */
typedef struct {
	__REG32	RAS	: 4;
	__REG32		:28;
} __dynamicmemoryras_bits;

/* Dynamic Memory Self-refresh Exit Time register */
typedef struct {
	__REG32	SREX	: 4;
	__REG32		:28;
} __dynamicmemorysrex_bits;

/* Dynamic Memory Last Data out to Active Time register */
typedef struct {
	__REG32	APR	: 4;
	__REG32		:28;
} __dynamicmemoryapr_bits;

/* Dynamic Memory Data-in to Active Command Time register */
typedef struct {
	__REG32	DAL	: 4;
	__REG32		:28;
} __dynamicmemorydal_bits;

/* Dynamic Memory Write Recovery Time register */
typedef struct {
	__REG32	WR	: 4;
	__REG32		:28;
} __dynamicmemorywr_bits;

/* Dynamic Memory Active to active Command persiod register */
typedef struct {
	__REG32	RC	: 4;
	__REG32		:28;
} __dynamicmemoryrc_bits;

/* Dynamic Memory Auto Refresh Period register */
typedef struct {
	__REG32	RFC	: 5;
	__REG32		:27;
} __dynamicmemoryrfc_bits;

/* Dynamic Memory Exit Self-refresh register */
typedef struct {
	__REG32	XSR	: 5;
	__REG32		:27;
} __dynamicmemoryxsr_bits;

/* Dynamic Memory Active Bank A to Active Bank B time register */
typedef struct {
	__REG32	RRD	: 4;
	__REG32		:28;
} __dynamicmemoryrrd_bits;

/* Dynamic Memory Load Mode register to Active Command Time register */
typedef struct {
	__REG32	MRD	: 4;
	__REG32		:28;
} __dynamicmemorymrd_bits;

/* Static Memory Extended Wait register */
typedef struct {
	__REG32	EXTW	:10;
	__REG32		:22;
} __staticmemoryext_bits;

/* Dynamic Memory Configuration registers */
typedef struct {
	__REG32		: 3;
	__REG32	MD	: 2;
	__REG32		: 2;
	__REG32	AM1	: 6;
	__REG32		: 1;
	__REG32	AM	: 1;
	__REG32		: 4;
	__REG32	BDMC	: 1;
	__REG32	Protect	: 1;
	__REG32		:11;
} __dynamicmemoryconfig_bits;

/* Dynamic Memory RAS and CAS delay registers */
typedef struct {
	__REG32	RAS	: 2;
	__REG32		: 6;
	__REG32	CAS	: 2;
	__REG32		:22;
} __dynamicmemoryrascas_bits;

/* Static Memory Configuration registers */
typedef struct {
	__REG32	MW	: 2;
	__REG32		: 1;
	__REG32	PM	: 1;
	__REG32		: 2;
	__REG32	PC	: 1;
	__REG32	PB	: 1;
	__REG32	EW	: 1;
	__REG32		:10;
	__REG32	BSMC	: 1;
	__REG32	PSMC	: 1;
	__REG32		:11;
} __staticmemoryconfig_bits;

/* Static Memory Write Enable Delay registers */
typedef struct {
	__REG32	WWEN	: 4;
	__REG32		:28;
} __staticmemorywriteen_bits;

/* Static Memory Output Enable Delay registers */
typedef struct {
	__REG32	WOEN	: 4;
	__REG32		:28;
} __staticmemoryoen_bits;

/* Static Memory Read Delay */
typedef struct {
	__REG32	WTRD	: 5;
	__REG32		:27;
} __staticmemoryread_bits;

/* Static Memory Page Mode Read Delay */
typedef struct {
	__REG32	WTPG	: 5;
	__REG32		:27;
} __staticmemorypage_bits;

/* Static Memory Write Delay */
typedef struct {
	__REG32	WTWR	: 5;
	__REG32		:27;
} __staticmemorywrite_bits;

/* Static Memory Turn Round Delay */
typedef struct {
	__REG32	WTTN	: 4;
	__REG32		:28;
} __staticmemoryturn_bits;

/* Ethernet General Control Register 1 */
typedef struct {
	__REG32		: 8;
	__REG32	ITXA	: 1;
	__REG32	MAC_HRST	: 1;
	__REG32	RXALIGN	: 1;
	__REG32		: 3;
	__REG32	PHY_MODE	: 2;
	__REG32		: 3;
	__REG32	ERXINIT	: 1;
	__REG32		: 2;
	__REG32	ETXDMA	: 1;
	__REG32	ETX	: 1;
	__REG32		: 4;
	__REG32	ERXSHT	: 1;
	__REG32		: 1;
	__REG32	ERXDMA	: 1;
	__REG32	ERX	: 1;
} __ethgenctrl1_bits;

/* Ethernet General Control Register 2 */
typedef struct {
	__REG32	STEN	: 1;
	__REG32	CLRCNT	: 1;
	__REG32	AUTOZ	: 1;
	__REG32	TCLER	: 1;
	__REG32		:28;
} __ethgenctrl2_bits;

/* Ethernet General Status */
typedef struct {
	__REG32		:20;
	__REG32	RXINIT	: 1;
	__REG32		:11;
} __ethgenstatus_bits;

/* Ethernet Transmit status */
typedef struct {
	__REG32	TXCOLC	: 4;
	__REG32		: 1;
	__REG32	TXCRC	: 1;
	__REG32	TXDEF	: 1;
	__REG32		: 1;
	__REG32	TXAJ	: 1;
	__REG32	TXAUR	: 1;
	__REG32	TXAEC	: 1;
	__REG32	TXAED	: 1;
	__REG32	TXAL	: 1;
	__REG32	TXMC	: 1;
	__REG32	TXBR	: 1;
	__REG32	TXOK	: 1;
	__REG32		:16;
} __ethtransmitstatus_bits;

/* Ethernet Receive Status */
typedef struct {
	__REG32		: 6;
	__REG32	RXSHT	: 1;
	__REG32		: 2;
	__REG32	RXDR	: 1;
	__REG32		: 1;
	__REG32	RXMC	: 1;
	__REG32	RXBR	: 1;
	__REG32	RXOK	: 1;
	__REG32	RXDV	: 1;
	__REG32	RXCE	: 1;
	__REG32	RXSIZE	:11;
	__REG32		: 5;
} __ethreceivestatus_bits;

/* MAC Configuration 1 */
typedef struct {
	__REG32	RXEN	: 1;
	__REG32		: 3;
	__REG32	LOOPBK	: 1;
	__REG32		: 3;
	__REG32	RPETFUN	: 1;
	__REG32	RPEMCST	: 1;
	__REG32	RPERFUN	: 1;
	__REG32		: 4;
	__REG32	SRST	: 1;
	__REG32		:16;
} __ethmacconf1_bits;

/* MAC Configuration 2 */
typedef struct {
	__REG32	FULLD	: 1;
	__REG32		: 1;
	__REG32	HUGE	: 1;
	__REG32		: 1;
	__REG32	CRCEN	: 1;
	__REG32	PADEN	: 1;
	__REG32	VLANP	: 1;
	__REG32	AUTOP	: 1;
	__REG32	PUREP	: 1;
	__REG32	LONGP	: 1;
	__REG32		: 2;
	__REG32	NOBO	: 1;
	__REG32		: 1;
	__REG32	EDEFER	: 1;
	__REG32		:17;
} __ethmacconf2_bits;

/* Back-to-Back Inter-Packet-gap */
typedef struct {
	__REG32	IPGT	: 7;
	__REG32		:25;
} __ethipgt_bits;

/* Non Back-to-Back Inter-Packet-Gap */
typedef struct {
	__REG32	IPGR2	: 7;
	__REG32		: 1;
	__REG32	IPGR1	: 7;
	__REG32		:17;
} __ethipgr_bits;

/* Collision Window/Retry */
typedef struct {
	__REG32	RETX	: 4;
	__REG32		: 4;
	__REG32	CWIN	: 6;
	__REG32		:18;
} __ethcollision_bits;

/* Maximum Frame Register */
typedef struct {
	__REG32	MAXF	:16;
	__REG32		:16;
} __ethmaxframe_bits;

/* PHY Support Register */
typedef struct {
	__REG32		: 8;
	__REG32	SPEED	: 1;
	__REG32		: 6;
	__REG32	RPERMII	: 1;
	__REG32		:16;
} __ethphysupport_bits;

/* MII Management Configuration */
typedef struct {
	__REG32		: 1;
	__REG32	SPRE	: 1;
	__REG32	CLKS	: 3;
	__REG32		:10;
	__REG32	RMIM	: 1;
	__REG32		:16;
} __ethmiiconfig_bits;

/* MII Management Command */
typedef struct {
	__REG32	READ	: 1;
	__REG32	SCAN	: 1;
	__REG32		:30;
} __ethmiicommand_bits;

/* MII Management Addres */
typedef struct {
	__REG32	RADR	: 5;
	__REG32		: 3;
	__REG32	DADR	: 5;
	__REG32		:19;
} __ethmiiaddress_bits;

/* MII Management Write Data */
typedef struct {
	__REG32	MWTD	:16;
	__REG32		:16;
} __ethmiiwritedata_bits;

/* MII Management Read Data */
typedef struct {
	__REG32	MRDD	:16;
	__REG32		:16;
} __ethmiireaddata_bits;

/* MII Management Indicators */
typedef struct {
	__REG32	BUSY	: 1;
	__REG32 SCAN	: 1;
	__REG32	NVALID	: 1;
	__REG32	MIILF	: 1;
	__REG32		:28;
} __ethmiiindicators_bits;

/* Station Address registers */
typedef struct {
	__REG32	OCTET2	: 8;
	__REG32	OCTET1	: 8;
	__REG32		:16;
} __ethsa1_bits;

typedef struct {
	__REG32	OCTET4	: 8;
	__REG32	OCTET3	: 8;
	__REG32		:16;
} __ethsa2_bits;

typedef struct {
	__REG32	OCTET6	: 8;
	__REG32	OCTET5	: 8;
	__REG32		:16;
} __ethsa3_bits;

/* Station Address Filter */
typedef struct {
	__REG32	BROAD	: 1;
	__REG32	PRA	: 1;
	__REG32	PRM	: 1;
	__REG32	PRO	: 1;
	__REG32		:28;
} __ethsafilter_bits;

/* Carry Register 1 */
typedef struct {
	__REG32		: 1;
	__REG32	C1RJB	: 1;
	__REG32	C1RFR	: 1;
	__REG32	C1ROV	: 1;
	__REG32	C1RUN	: 1;
	__REG32	C1RCS	: 1;
	__REG32	C1RCD	: 1;
	__REG32		: 1;
	__REG32	C1RAL	: 1;
	__REG32	C1RXU	: 1;
	__REG32	C1RXP	: 1;
	__REG32	C1RXC	: 1;
	__REG32	C1RBC	: 1;
	__REG32	C1RMC	: 1;
	__REG32	C1RFC	: 1;
	__REG32	C1RPK	: 1;
	__REG32	C1RBY	: 1;
	__REG32		: 8;
	__REG32	C1MGV	: 1;
	__REG32	C1MAX	: 1;
	__REG32	C11K	: 1;
	__REG32	C1511	: 1;
	__REG32	C1255	: 1;
	__REG32	C1127	: 1;
	__REG32	C164	: 1;
} __ethcarry1_bits;

/* Carry Register 2 */
typedef struct {
	__REG32		: 2;
	__REG32	C2TNC	: 1;
	__REG32	C2TXC	: 1;
	__REG32	C2TLC	: 1;
	__REG32	C2TMA	: 1;
	__REG32	C2TSC	: 1;
	__REG32	C2TED	: 1;
	__REG32	C2TDF	: 1;
	__REG32		: 1;
	__REG32	C2TBC	: 1;
	__REG32	C2TMC	: 1;
	__REG32	C2TPK	: 1;
	__REG32	C2TBY	: 1;
	__REG32	C2TFG	: 1;
	__REG32	C2TUN	: 1;
	__REG32	C2TOV	: 1;
	__REG32		: 1;
	__REG32	C2TFC	: 1;
	__REG32	C2JTB	: 1;
	__REG32		:12;
} __ethcarry2_bits;

/* Carry Register 1 Mask */
typedef struct {
	__REG32		: 1;
	__REG32	M1RJB	: 1;
	__REG32	M1RFR	: 1;
	__REG32	M1ROV	: 1;
	__REG32	M1RUN	: 1;
	__REG32	M1RCS	: 1;
	__REG32	M1RCD	: 1;
	__REG32		: 1;
	__REG32	M1RAL	: 1;
	__REG32	M1RXU	: 1;
	__REG32	M1RXP	: 1;
	__REG32	M1RXC	: 1;
	__REG32	M1RBC	: 1;
	__REG32	M1RMC	: 1;
	__REG32	M1RFC	: 1;
	__REG32	M1RPK	: 1;
	__REG32	M1RBY	: 1;
	__REG32		: 8;
	__REG32	M1MGV	: 1;
	__REG32	M1MAX	: 1;
	__REG32	MC11K	: 1;
	__REG32	M1511	: 1;
	__REG32	M1255	: 1;
	__REG32	M1127	: 1;
	__REG32	M164	: 1;
} __ethcarrymask1_bits;

/* Carry Register 2 Mask */
typedef struct {
	__REG32		: 2;
	__REG32	M2TNC	: 1;
	__REG32	M2TXC	: 1;
	__REG32	M2TLC	: 1;
	__REG32	M2TMA	: 1;
	__REG32	M2TSC	: 1;
	__REG32	M2TED	: 1;
	__REG32	M2TDF	: 1;
	__REG32		: 1;
	__REG32	M2TBC	: 1;
	__REG32	M2TMC	: 1;
	__REG32	M2TPK	: 1;
	__REG32	M2TBY	: 1;
	__REG32	M2TFG	: 1;
	__REG32	M2TUN	: 1;
	__REG32	M2TOV	: 1;
	__REG32		: 1;
	__REG32	M2TFC	: 1;
	__REG32	M2JTB	: 1;
	__REG32		:12;
} __ethcarrymask2_bits;

/* Ethernet Interrupt Status */
typedef struct {
	__REG32	TXIDLE	: 1;
	__REG32	TXERR	: 1;
	__REG32	TXDONE	: 1;
	__REG32	TXBUFNR	: 1;
	__REG32	TXBUFC	: 1;
	__REG32		: 1;
	__REG32	STOVFL	: 1;
	__REG32		: 9;
	__REG32	RXBR	: 1;
	__REG32	RXBUFFUL	: 1;
	__REG32	RXNOBUF	: 1;
	__REG32	RXDONED	: 1;
	__REG32	RXDONEC	: 1;
	__REG32	RXDONEB	: 1;
	__REG32	RXDONEA	: 1;
	__REG32	RXBUFC	: 1;
	__REG32	RXOVFL_STAT	: 1;
	__REG32	RXOVFL_DATA	: 1;
	__REG32		: 6;
} __ethintstatus_bits;

/* Ethernet Interrupt Enable */
typedef struct {
	__REG32	EN_TXIDLE	: 1;
	__REG32	EN_TXERR	: 1;
	__REG32	EN_TXDONE	: 1;
	__REG32	EN_TXBUFNR	: 1;
	__REG32	EN_TXBUFC	: 1;
	__REG32		: 1;
	__REG32	EN_STOVFL	: 1;
	__REG32		: 9;
	__REG32	EN_RXBR	: 1;
	__REG32	EN_RXBUFFUL	: 1;
	__REG32	EN_RXNOBUF	: 1;
	__REG32	EN_RXDONED	: 1;
	__REG32	EN_RXDONEC	: 1;
	__REG32	EN_RXDONEB	: 1;
	__REG32	EN_RXDONEA	: 1;
	__REG32	EN_RXBUFC	: 1;
	__REG32	EN_RXOVFL_STAT	: 1;
	__REG32	EN_RXOVFL_DATA	: 1;
	__REG32		: 6;
} __ethintenable_bits;


/* Combined transmit and receive statistics counters */
typedef struct {
	__REG32	TR64	:18;
	__REG32		:14;
} __tr64_bits;

typedef struct {
	__REG32	TR127	:18;
	__REG32		:14;
} __tr127_bits;

typedef struct {
	__REG32	TR255	:18;
	__REG32		:14;
} __tr255_bits;

typedef struct {
	__REG32	TR511	:18;
	__REG32		:14;
} __tr511_bits;

typedef struct {
	__REG32	TR1K	:18;
	__REG32		:14;
} __tr1k_bits;

typedef struct {
	__REG32	TRMAX	:18;
	__REG32		:14;
} __trmax_bits;

typedef struct {
	__REG32	TRMGV	:18;
	__REG32		:14;
} __trmgv_bits;

/* Receive byte counter */
typedef struct {
	__REG32	RBYT	:24;
	__REG32		: 8;
} __rbyt_bits;

/* Receive packet counter */
typedef struct {
	__REG32	RPKT	:18;
	__REG32		:14;
} __rpkt_bits;

/* Receive FCS error counter */
typedef struct {
	__REG32	RFCS	:12;
	__REG32		:20;
} __rfcs_bits;

/* Receive multicast packet counter */
typedef struct {
	__REG32	RMCA	:18;
	__REG32		:14;
} __rmca_bits;

/* Receive broadcast packet counter */
typedef struct {
	__REG32	RBCA	:18;
	__REG32		:14;
} __rbca_bits;

/* Receive control frame packet counter */
typedef struct {
	__REG32	RXCF	:12;
	__REG32		:20;
} __rxcf_bits;

/* Receive PAUSE frame packet counter */
typedef struct {
	__REG32	RXPF	:12;
	__REG32		:20;
} __rxpf_bits;

/* Receive unknown OPCODE counter */
typedef struct {
	__REG32	RXUO	:12;
	__REG32		:20;
} __rxuo_bits;

/* Receive alignment error counter */
typedef struct {
	__REG32	RALN	:12;
	__REG32		:20;
} __raln_bits;

/* Receive code error counter */
typedef struct {
	__REG32	RCDE	:12;
	__REG32		:20;
} __rcde_bits;

/* Receive carrier sense error counter */
typedef struct {
	__REG32	RCSE	:12;
	__REG32		:20;
} __rcse_bits;

/* Receive undersize packet counter */
typedef struct {
	__REG32	RUND	:12;
	__REG32		:20;
} __rund_bits;

/* Receive oversize packet counter */
typedef struct {
	__REG32	ROVR	:12;
	__REG32		:20;
} __rovr_bits;

/* Receive fragments counter */
typedef struct {
	__REG32	RFRG	:12;
	__REG32		:20;
} __rfrg_bits;

/* Receive jabber counter */
typedef struct {
	__REG32	RJBR	:12;
	__REG32		:20;
} __rjbr_bits;

/* Transmit byte counter */
typedef struct {
	__REG32	TBYT	:24;
	__REG32		: 8;
} __tbyt_bits;

/* Transmit packet counter */
typedef struct {
	__REG32	TPKT	:18;
	__REG32		:14;
} __tpkt_bits;

/* Transmit multicast packet counter */
typedef struct {
	__REG32	TMCA	:18;
	__REG32		:14;
} __tmca_bits;

/* Transmit broadcast packet counter */
typedef struct {
	__REG32	TBCA	:18;
	__REG32		:14;
} __tbca_bits;

/* Transmit deferral packet counter */
typedef struct {
	__REG32	TDFR	:12;
	__REG32		:20;
} __tdfr_bits;

/* Transmit excessive deferral packer counter */
typedef struct {
	__REG32	TEDF	:12;
	__REG32		:20;
} __tedf_bits;

/* Transmit single collision packet counter */
typedef struct {
	__REG32	TSCL	:12;
	__REG32		:20;
} __tscl_bits;

/* Transmit multiple collision packet counter */
typedef struct {
	__REG32	TMCL	:12;
	__REG32		:20;
} __tmcl_bits;

/* Transmit late collision packet counter */
typedef struct {
	__REG32	TLCL	:12;
	__REG32		:20;
} __tlcl_bits;

/* Transmit excessive collision packet counter */
typedef struct {
	__REG32	TXCL	:12;
	__REG32		:20;
} __txcl_bits;

/* Transmit total collision packet counter */
typedef struct {
	__REG32	TNCL	:12;
	__REG32		:20;
} __tncl_bits;

/* Transmit jabber frame counter */
typedef struct {
	__REG32	TJBR	:12;
	__REG32		:20;
} __tjbr_bits;

/* Transmit FCS error counter */
typedef struct {
	__REG32	TFCS	:12;
	__REG32		:20;
} __tfcs_bits;

/* Transmit oversize frame counter */
typedef struct {
	__REG32	TOVR	:12;
	__REG32		:20;
} __tovr_bits;

/* Transmit undersize frame counter */
typedef struct {
	__REG32	TUND	:12;
	__REG32		:20;
} __tund_bits;

/* Tramsmit fragment counter */
typedef struct {
	__REG32	TFRG	:12;
	__REG32		:20;
} __tfrg_bits;

/* TX Buffer descriptor pointer */
typedef struct {
	__REG32	TXPTR	: 8;
	__REG32		:24;
} __txptr_bits;

/* Transmit recover buffer descriptor pointer */
typedef struct {
	__REG32	TXRPTR	: 8;
	__REG32		:24;
} __txrptr_bits;

/* TX error buffer descriptor pointer */
typedef struct {
	__REG32	TXERBD	: 8;
	__REG32		:24;
} __txerbd_bits;

/* TX stall buffer descriptor pointer */
typedef struct {
	__REG32	TXSPTR	: 8;
	__REG32		:24;
} __txsptr_bits;

/* RX_A buffer descriptor pointer offset */
typedef struct {
	__REG32	RXAOFF	:11;
	__REG32		:21;
} __rxaoff_bits;

/* RX_B buffer descriptor pointer offset */
typedef struct {
	__REG32	RXBOFF	:11;
	__REG32		:21;
} __rxboff_bits;

/* RX_C buffer descriptor pointer offset */
typedef struct {
	__REG32	RXCOFF	:11;
	__REG32		:21;
} __rxcoff_bits;

/* RX_D buffer descriptor pointer offset */
typedef struct {
	__REG32	RXDOFF	:11;
	__REG32		:21;
} __rxdoff_bits;

/* Transmit buffer descriptor pointer offset */
typedef struct {
	__REG32	TXOFF	:10;
	__REG32		:22;
} __txoff_bits;

/* RX free buffer */
typedef struct {
	__REG32	RXFREEA	: 1;
	__REG32	RXFREEB	: 1;
	__REG32	RXFREEC	: 1;
	__REG32	RXFREED	: 1;
	__REG32		:28;
} __rxfree_bits;

/* DMA Channel x control */
typedef struct {
	__REG32	INDEX	:10;
	__REG32	STATE	: 6;
	__REG32	RST	: 1;
	__REG32	MODE	: 1;
	__REG32	POL	: 1;
	__REG32	DINC_N	: 1;
	__REG32	SINC_N	: 1;
	__REG32	DB	: 2;
	__REG32	SB	: 2;
	__REG32		: 4;
	__REG32	CG	: 1;
	__REG32	CA	: 1;
	__REG32	CE	: 1;
} __dmactrl_bits;

/* DMA Status and interrupt enable */
typedef struct {
	__REG32	BLEN	:16;
	__REG32	FULL	: 1;
	__REG32	LAST	: 1;
	__REG32	IDONE	: 1;
	__REG32	WRAP	: 1;
	__REG32	PCIE	: 1;
	__REG32	CAIE	: 1;
	__REG32	NRIE	: 1;
	__REG32	ECIE	: 1;
	__REG32	NCIE	: 1;
	__REG32		: 2;
	__REG32	PCIP	: 1;
	__REG32	CAIP	: 1;
	__REG32	NRIP	: 1;
	__REG32	ECIP	: 1;
	__REG32	NCIP	: 1;
} __dmaint_bits;

/* DMA Peripheral Chip Select */
typedef struct {
	__REG32	SEL	: 2;
	__REG32		: 1;
	__REG32	POL	: 1;
	__REG32		:28;
} __dmaper_bits;

/* Bbus Bridge interrupt status */
typedef struct {
	__REG32	BBUS_DMA	: 1;
	__REG32		: 1;
	__REG32	SER_B_RX	: 1;
	__REG32	SER_B_TX	: 1;
	__REG32	SER_A_RX	: 1;
	__REG32	SER_A_TX	: 1;
	__REG32	SER_C_RX	: 1;
	__REG32	SER_C_TX	: 1;
	__REG32	SER_D_RX	: 1;
	__REG32	SER_D_TX	: 1;
	__REG32	I2C	: 1;
	__REG32	_1284	: 1;
	__REG32	UTIL	: 1;
	__REG32	RTC	: 1;
	__REG32	USBHST	: 1;
	__REG32	USBDEV	: 1;
	__REG32		: 8;
	__REG32	AHB_DMA1	: 1;
	__REG32	AHB_DMA2	: 1;
	__REG32		: 6;
} __bbusint_bits;

/* BBus bridge interrupt enable */
typedef struct {
	__REG32	DMA	: 1;
	__REG32		: 1;
	__REG32	SER_B_RX	: 1;
	__REG32	SER_B_TX	: 1;
	__REG32	SER_A_RX	: 1;
	__REG32	SER_A_TX	: 1;
	__REG32	SER_C_RX	: 1;
	__REG32	SER_C_TX	: 1;
	__REG32	SER_D_RX	: 1;
	__REG32	SER_D_TX	: 1;
	__REG32	I2C	: 1;
	__REG32	_1284	: 1;
	__REG32	UTIL	: 1;
	__REG32	RTC	: 1;
	__REG32	USBHST	: 1;
	__REG32	USBDEV	: 1;
	__REG32		: 8;
	__REG32	DMA1	: 1;
	__REG32	DMA2	: 1;
	__REG32		: 5;
	__REG32	GLBL	: 1;
} __bbusinten_bits;

/* BBus Bridge prefetch (Burst-8) buffer enable */
typedef struct {
	__REG32	ENABLE	: 3;
	__REG32		: 29;
} __bbusprefetch_bits;

/* DMA Control */
typedef struct {
	__REG32	INDEX	:10;
	__REG32	STATE	: 6;
	__REG32		: 2;
	__REG32	RST	: 1;
	__REG32		: 3;
	__REG32	BDR	: 1;
	__REG32		: 1;
	__REG32	BTE	: 2;
	__REG32	MODE	: 2;
	__REG32		: 2;
	__REG32	CA	: 1;
	__REG32	CE	: 1;
} __dmachctrl_bits;

/* Master Reset register */
typedef struct {
	__REG32	DMA	: 1;
	__REG32		: 1;
	__REG32	SerB	: 1;
	__REG32	SerA	: 1;
	__REG32	SerC	: 1;
	__REG32	SerD	: 1;
	__REG32	_1284	: 1;
	__REG32	I2C	: 1;
	__REG32		: 1;
	__REG32	RTC1	: 1;
	__REG32	RTC2	: 1;
	__REG32	USBHST	: 1;
	__REG32	USBDEV	: 1;
	__REG32		:19;
} __bbusmr_bits;

/* BBus Utility Interrupt status */
typedef struct {
	__REG32	INT	: 1;
	__REG32		:31;
} __bbusutint_bits;

/* GPIO Configuration #10 */
typedef struct {
	__REG32	GPIO72_FUNC	: 2;
	__REG32	GPIO72_INV	: 1;
	__REG32	GPIO72_DIR	: 1;
	__REG32		:28;
} __gpio10_bits;

/* GPIO Configuration #9 */
typedef struct {
	__REG32	GPIO64_FUNC	: 2;
	__REG32	GPIO64_INV	: 1;
	__REG32	GPIO64_DIR	: 1;
	__REG32	GPIO65_FUNC	: 2;
	__REG32	GPIO65_INV	: 1;
	__REG32	GPIO65_DIR	: 1;
	__REG32	GPIO66_FUNC	: 2;
	__REG32	GPIO66_INV	: 1;
	__REG32	GPIO66_DIR	: 1;
	__REG32	GPIO67_FUNC	: 2;
	__REG32	GPIO67_INV	: 1;
	__REG32	GPIO67_DIR	: 1;
	__REG32	GPIO68_FUNC	: 2;
	__REG32	GPIO68_INV	: 1;
	__REG32	GPIO68_DIR	: 1;
	__REG32	GPIO69_FUNC	: 2;
	__REG32	GPIO69_INV	: 1;
	__REG32	GPIO69_DIR	: 1;
	__REG32	GPIO70_FUNC	: 2;
	__REG32	GPIO70_INV	: 1;
	__REG32	GPIO70_DIR	: 1;
	__REG32	GPIO71_FUNC	: 2;
	__REG32	GPIO71_INV	: 1;
	__REG32	GPIO71_DIR	: 1;
} __gpio9_bits;

/* GPIO Configuration #8 */
typedef struct {
	__REG32	GPIO56_FUNC	: 2;
	__REG32	GPIO56_INV	: 1;
	__REG32	GPIO56_DIR	: 1;
	__REG32	GPIO57_FUNC	: 2;
	__REG32	GPIO57_INV	: 1;
	__REG32	GPIO57_DIR	: 1;
	__REG32	GPIO58_FUNC	: 2;
	__REG32	GPIO58_INV	: 1;
	__REG32	GPIO58_DIR	: 1;
	__REG32	GPIO59_FUNC	: 2;
	__REG32	GPIO59_INV	: 1;
	__REG32	GPIO59_DIR	: 1;
	__REG32	GPIO60_FUNC	: 2;
	__REG32	GPIO60_INV	: 1;
	__REG32	GPIO60_DIR	: 1;
	__REG32	GPIO61_FUNC	: 2;
	__REG32	GPIO61_INV	: 1;
	__REG32	GPIO61_DIR	: 1;
	__REG32	GPIO62_FUNC	: 2;
	__REG32	GPIO62_INV	: 1;
	__REG32	GPIO62_DIR	: 1;
	__REG32	GPIO63_FUNC	: 2;
	__REG32	GPIO63_INV	: 1;
	__REG32	GPIO63_DIR	: 1;
} __gpio8_bits;

/* GPIO Configuration #7 */
typedef struct {
	__REG32	GPIO48_FUNC	: 2;
	__REG32	GPIO48_INV	: 1;
	__REG32	GPIO48_DIR	: 1;
	__REG32	GPIO49_FUNC	: 2;
	__REG32	GPIO49_INV	: 1;
	__REG32	GPIO49_DIR	: 1;
	__REG32	GPIO50_FUNC	: 2;
	__REG32	GPIO50_INV	: 1;
	__REG32	GPIO50_DIR	: 1;
	__REG32	GPIO51_FUNC	: 2;
	__REG32	GPIO51_INV	: 1;
	__REG32	GPIO51_DIR	: 1;
	__REG32	GPIO52_FUNC	: 2;
	__REG32	GPIO52_INV	: 1;
	__REG32	GPIO52_DIR	: 1;
	__REG32	GPIO53_FUNC	: 2;
	__REG32	GPIO53_INV	: 1;
	__REG32	GPIO53_DIR	: 1;
	__REG32	GPIO54_FUNC	: 2;
	__REG32	GPIO54_INV	: 1;
	__REG32	GPIO54_DIR	: 1;
	__REG32	GPIO55_FUNC	: 2;
	__REG32	GPIO55_INV	: 1;
	__REG32	GPIO55_DIR	: 1;
} __gpio7_bits;

/* GPIO Configuration #6 */
typedef struct {
	__REG32	GPIO40_FUNC	: 2;
	__REG32	GPIO40_INV	: 1;
	__REG32	GPIO40_DIR	: 1;
	__REG32	GPIO41_FUNC	: 2;
	__REG32	GPIO41_INV	: 1;
	__REG32	GPIO41_DIR	: 1;
	__REG32	GPIO42_FUNC	: 2;
	__REG32	GPIO42_INV	: 1;
	__REG32	GPIO42_DIR	: 1;
	__REG32	GPIO43_FUNC	: 2;
	__REG32	GPIO43_INV	: 1;
	__REG32	GPIO43_DIR	: 1;
	__REG32	GPIO44_FUNC	: 2;
	__REG32	GPIO44_INV	: 1;
	__REG32	GPIO44_DIR	: 1;
	__REG32	GPIO45_FUNC	: 2;
	__REG32	GPIO45_INV	: 1;
	__REG32	GPIO45_DIR	: 1;
	__REG32	GPIO46_FUNC	: 2;
	__REG32	GPIO46_INV	: 1;
	__REG32	GPIO46_DIR	: 1;
	__REG32	GPIO47_FUNC	: 2;
	__REG32	GPIO47_INV	: 1;
	__REG32	GPIO47_DIR	: 1;
} __gpio6_bits;

/* GPIO Configuration #5 */
typedef struct {
	__REG32	GPIO32_FUNC	: 2;
	__REG32	GPIO32_INV	: 1;
	__REG32	GPIO32_DIR	: 1;
	__REG32	GPIO33_FUNC	: 2;
	__REG32	GPIO33_INV	: 1;
	__REG32	GPIO33_DIR	: 1;
	__REG32	GPIO34_FUNC	: 2;
	__REG32	GPIO34_INV	: 1;
	__REG32	GPIO34_DIR	: 1;
	__REG32	GPIO35_FUNC	: 2;
	__REG32	GPIO35_INV	: 1;
	__REG32	GPIO35_DIR	: 1;
	__REG32	GPIO36_FUNC	: 2;
	__REG32	GPIO36_INV	: 1;
	__REG32	GPIO36_DIR	: 1;
	__REG32	GPIO37_FUNC	: 2;
	__REG32	GPIO37_INV	: 1;
	__REG32	GPIO37_DIR	: 1;
	__REG32	GPIO38_FUNC	: 2;
	__REG32	GPIO38_INV	: 1;
	__REG32	GPIO38_DIR	: 1;
	__REG32	GPIO39_FUNC	: 2;
	__REG32	GPIO39_INV	: 1;
	__REG32	GPIO39_DIR	: 1;
} __gpio5_bits;

/* GPIO Configuration #4 */
typedef struct {
	__REG32	GPIO24_FUNC	: 2;
	__REG32	GPIO24_INV	: 1;
	__REG32	GPIO24_DIR	: 1;
	__REG32	GPIO25_FUNC	: 2;
	__REG32	GPIO25_INV	: 1;
	__REG32	GPIO25_DIR	: 1;
	__REG32	GPIO26_FUNC	: 2;
	__REG32	GPIO26_INV	: 1;
	__REG32	GPIO26_DIR	: 1;
	__REG32	GPIO27_FUNC	: 2;
	__REG32	GPIO27_INV	: 1;
	__REG32	GPIO27_DIR	: 1;
	__REG32	GPIO28_FUNC	: 2;
	__REG32	GPIO28_INV	: 1;
	__REG32	GPIO28_DIR	: 1;
	__REG32	GPIO29_FUNC	: 2;
	__REG32	GPIO29_INV	: 1;
	__REG32	GPIO29_DIR	: 1;
	__REG32	GPIO30_FUNC	: 2;
	__REG32	GPIO30_INV	: 1;
	__REG32	GPIO30_DIR	: 1;
	__REG32	GPIO31_FUNC	: 2;
	__REG32	GPIO31_INV	: 1;
	__REG32	GPIO31_DIR	: 1;
} __gpio4_bits;

/* GPIO Configuration #3 */
typedef struct {
	__REG32	GPIO16_FUNC	: 2;
	__REG32	GPIO16_INV	: 1;
	__REG32	GPIO16_DIR	: 1;
	__REG32	GPIO17_FUNC	: 2;
	__REG32	GPIO17_INV	: 1;
	__REG32	GPIO17_DIR	: 1;
	__REG32	GPIO18_FUNC	: 2;
	__REG32	GPIO18_INV	: 1;
	__REG32	GPIO18_DIR	: 1;
	__REG32	GPIO19_FUNC	: 2;
	__REG32	GPIO19_INV	: 1;
	__REG32	GPIO19_DIR	: 1;
	__REG32	GPIO20_FUNC	: 2;
	__REG32	GPIO20_INV	: 1;
	__REG32	GPIO20_DIR	: 1;
	__REG32	GPIO21_FUNC	: 2;
	__REG32	GPIO21_INV	: 1;
	__REG32	GPIO21_DIR	: 1;
	__REG32	GPIO22_FUNC	: 2;
	__REG32	GPIO22_INV	: 1;
	__REG32	GPIO22_DIR	: 1;
	__REG32	GPIO23_FUNC	: 2;
	__REG32	GPIO23_INV	: 1;
	__REG32	GPIO23_DIR	: 1;
} __gpio3_bits;

/* GPIO Configuration #2 */
typedef struct {
	__REG32	GPIO8_FUNC	: 2;
	__REG32	GPIO8_INV	: 1;
	__REG32	GPIO8_DIR	: 1;
	__REG32	GPIO9_FUNC	: 2;
	__REG32	GPIO9_INV	: 1;
	__REG32	GPIO9_DIR	: 1;
	__REG32	GPIO10_FUNC	: 2;
	__REG32	GPIO10_INV	: 1;
	__REG32	GPIO10_DIR	: 1;
	__REG32	GPIO11_FUNC	: 2;
	__REG32	GPIO11_INV	: 1;
	__REG32	GPIO11_DIR	: 1;
	__REG32	GPIO12_FUNC	: 2;
	__REG32	GPIO12_INV	: 1;
	__REG32	GPIO12_DIR	: 1;
	__REG32	GPIO13_FUNC	: 2;
	__REG32	GPIO13_INV	: 1;
	__REG32	GPIO13_DIR	: 1;
	__REG32	GPIO14_FUNC	: 2;
	__REG32	GPIO14_INV	: 1;
	__REG32	GPIO14_DIR	: 1;
	__REG32	GPIO15_FUNC	: 2;
	__REG32	GPIO15_INV	: 1;
	__REG32	GPIO15_DIR	: 1;
} __gpio2_bits;

/* GPIO Configuration #1 */
typedef struct {
	__REG32	GPIO0_FUNC	: 2;
	__REG32	GPIO0_INV	: 1;
	__REG32	GPIO0_DIR	: 1;
	__REG32	GPIO1_FUNC	: 2;
	__REG32	GPIO1_INV	: 1;
	__REG32	GPIO1_DIR	: 1;
	__REG32	GPIO2_FUNC	: 2;
	__REG32	GPIO2_INV	: 1;
	__REG32	GPIO2_DIR	: 1;
	__REG32	GPIO3_FUNC	: 2;
	__REG32	GPIO3_INV	: 1;
	__REG32	GPIO3_DIR	: 1;
	__REG32	GPIO4_FUNC	: 2;
	__REG32	GPIO4_INV	: 1;
	__REG32	GPIO4_DIR	: 1;
	__REG32	GPIO5_FUNC	: 2;
	__REG32	GPIO5_INV	: 1;
	__REG32	GPIO5_DIR	: 1;
	__REG32	GPIO6_FUNC	: 2;
	__REG32	GPIO6_INV	: 1;
	__REG32	GPIO6_DIR	: 1;
	__REG32	GPIO7_FUNC	: 2;
	__REG32	GPIO7_INV	: 1;
	__REG32	GPIO7_DIR	: 1;
} __gpio1_bits;

/* GPIO Control register #3 */
typedef struct {
	__REG32	gpio64	: 1;
	__REG32	gpio65	: 1;
	__REG32	gpio66	: 1;
	__REG32	gpio67	: 1;
	__REG32	gpio68	: 1;
	__REG32	gpio69	: 1;
	__REG32	gpio70	: 1;
	__REG32	gpio71	: 1;
	__REG32	gpio72	: 1;
	__REG32		:23;
} __gpioctrl3_bits;

/* GPIO Control register #2 */
typedef struct {
	__REG32	gpio32	: 1;
	__REG32	gpio33	: 1;
	__REG32	gpio34	: 1;
	__REG32	gpio35	: 1;
	__REG32	gpio36	: 1;
	__REG32	gpio37	: 1;
	__REG32	gpio38	: 1;
	__REG32	gpio39	: 1;
	__REG32	gpio40	: 1;
	__REG32	gpio41	: 1;
	__REG32	gpio42	: 1;
	__REG32	gpio43	: 1;
	__REG32	gpio44	: 1;
	__REG32	gpio45	: 1;
	__REG32	gpio46	: 1;
	__REG32	gpio47	: 1;
	__REG32	gpio48	: 1;
	__REG32	gpio49	: 1;
	__REG32	gpio50	: 1;
	__REG32	gpio51	: 1;
	__REG32	gpio52	: 1;
	__REG32	gpio53	: 1;
	__REG32	gpio54	: 1;
	__REG32	gpio55	: 1;
	__REG32	gpio56	: 1;
	__REG32	gpio57	: 1;
	__REG32	gpio58	: 1;
	__REG32	gpio59	: 1;
	__REG32	gpio60	: 1;
	__REG32	gpio61	: 1;
	__REG32	gpio62	: 1;
	__REG32	gpio63	: 1;
} __gpioctrl2_bits;

/* GPIO Control register #1 */
typedef struct {
	__REG32	gpio0	: 1;
	__REG32	gpio1	: 1;
	__REG32	gpio2	: 1;
	__REG32	gpio3	: 1;
	__REG32	gpio4	: 1;
	__REG32	gpio5	: 1;
	__REG32	gpio6	: 1;
	__REG32	gpio7	: 1;
	__REG32	gpio8	: 1;
	__REG32	gpio9	: 1;
	__REG32	gpio10	: 1;
	__REG32	gpio11	: 1;
	__REG32	gpio12	: 1;
	__REG32	gpio13	: 1;
	__REG32	gpio14	: 1;
	__REG32	gpio15	: 1;
	__REG32	gpio16	: 1;
	__REG32	gpio17	: 1;
	__REG32	gpio18	: 1;
	__REG32	gpio19	: 1;
	__REG32	gpio20	: 1;
	__REG32	gpio21	: 1;
	__REG32	gpio22	: 1;
	__REG32	gpio23	: 1;
	__REG32	gpio24	: 1;
	__REG32	gpio25	: 1;
	__REG32	gpio26	: 1;
	__REG32	gpio27	: 1;
	__REG32	gpio28	: 1;
	__REG32	gpio29	: 1;
	__REG32	gpio30	: 1;
	__REG32	gpio31	: 1;
} __gpioctrl1_bits;

/* BBus Timeout */
typedef struct {
	__REG32	COUNT	:16;
	__REG32		:15;
	__REG32	EN	: 1;
} __bbustimeout_bits;

/* BBus DMA interrupt status */
typedef struct {
	__REG32	BINT1	: 1;
	__REG32	BINT2	: 1;
	__REG32	BINT3	: 1;
	__REG32	BINT4	: 1;
	__REG32	BINT5	: 1;
	__REG32	BINT6	: 1;
	__REG32	BINT7	: 1;
	__REG32	BINT8	: 1;
	__REG32	BINT9	: 1;
	__REG32	BINT10	: 1;
	__REG32	BINT11	: 1;
	__REG32	BINT12	: 1;
	__REG32	BINT13	: 1;
	__REG32	BINT14	: 1;
	__REG32	BINT15	: 1;
	__REG32	BINT16	: 1;
	__REG32		:16;
} __bbusdmaint_bits;

/* BBus DMA Interrupt Enable */
typedef struct {
	__REG32	BINT_EN1	: 1;
	__REG32	BINT_EN2	: 1;
	__REG32	BINT_EN3	: 1;
	__REG32	BINT_EN4	: 1;
	__REG32	BINT_EN5	: 1;
	__REG32	BINT_EN6	: 1;
	__REG32	BINT_EN7	: 1;
	__REG32	BINT_EN8	: 1;
	__REG32	BINT_EN9	: 1;
	__REG32	BINT_EN10	: 1;
	__REG32	BINT_EN11	: 1;
	__REG32	BINT_EN12	: 1;
	__REG32	BINT_EN13	: 1;
	__REG32	BINT_EN14	: 1;
	__REG32	BINT_EN15	: 1;
	__REG32	BINT_EN16	: 1;
	__REG32		:16;
} __bbusdmainten_bits;

/* USB Configuration */
typedef struct {
	__REG32		: 2;
	__REG32	SPEED	: 1;
	__REG32		: 1;
	__REG32	INT_PHY	: 1;
	__REG32	EXT_PHY	: 1;
	__REG32		:26;
} __usbconf_bits;

/* Endian configuration */
typedef struct {
	__REG32	DMA	: 1;
	__REG32		: 1;
	__REG32	SerB	: 1;
	__REG32	SerA	: 1;
	__REG32	SerC	: 1;
	__REG32	SerD	: 1;
	__REG32		: 3;
	__REG32	USBHST	: 1;
	__REG32		: 2;
	__REG32	AHBM	: 1;
	__REG32		:19;
} __endianconf_bits;

/* RTC general control */
typedef struct {
	__REG32	Time	: 1;
	__REG32	Cal	: 1;
	__REG32		:30;
} __rtcgen_bits;

/* 12/24 Hour */
typedef struct {
	__REG32	_12_24	: 1;
	__REG32		:31;
} __1224_bits;

/* Time register */
typedef struct {
	__REG32	H_U	: 4;
	__REG32	H_T	: 4;
	__REG32	S_U	: 4;
	__REG32	S_T	: 3;
	__REG32		: 1;
	__REG32	M_U	: 4;
	__REG32	M_T	: 3;
	__REG32		: 1;
	__REG32	HR_U	: 4;
	__REG32	HR_T	: 2;
	__REG32	PM	: 1;
	__REG32		: 1;
} __time_bits;

/* Calendar register */
typedef struct {
	__REG32	Day	: 3;
	__REG32	M_U	: 4;
	__REG32	M_T	: 1;
	__REG32	D_U	: 4;
	__REG32	D_T	: 2;
	__REG32		: 2;
	__REG32	Y_U	: 4;
	__REG32	Y_T	: 4;
	__REG32	C_U	: 4;
	__REG32	C_T	: 2;
	__REG32		: 2;
} __calendar_bits;

/* Calendar alarm */
typedef struct {
	__REG32		: 3;
	__REG32	M_U	: 4;
	__REG32	M_T	: 1;
	__REG32	D_U	: 4;
	__REG32	D_T	: 2;
	__REG32		: 18;
} __calendaralarm_bits;

/* Alarm enable */
typedef struct {
	__REG32	Hsec	: 1;
	__REG32	Sec	: 1;
	__REG32	Min	: 1;
	__REG32	Hour	: 1;
	__REG32	Date	: 1;
	__REG32	Mnth	: 1;
	__REG32		:26;
} __alarmen_bits;

/* Event Flags */
typedef struct {
	__REG32	Hsec_Evnt	: 1;
	__REG32	Sec_Evnt	: 1;
	__REG32	Min_Evnt	: 1;
	__REG32	Hour_Evnt	: 1;
	__REG32	Date_Evnt	: 1;
	__REG32	Mnth_Evnt	: 1;
	__REG32	Alarm	: 1;
	__REG32		:25;
} __eventfl_bits;

/* Interrupt enable */
typedef struct {
	__REG32	Hsec_Int	: 1;
	__REG32	Sec_Int	: 1;
	__REG32	Min_Int	: 1;
	__REG32	Hour_Int	: 1;
	__REG32	Date_Int	: 1;
	__REG32	Mnth_Int	: 1;
	__REG32	Alrm_Int	: 1;
	__REG32		:25;
} __timeinten_bits;

/* Interrupt disable */
typedef struct {
	__REG32	Hsec_Dis	: 1;
	__REG32	Sec_Dis	: 1;
	__REG32	Min_Dis	: 1;
	__REG32	Hour_Dis	: 1;
	__REG32	Date_Dis	: 1;
	__REG32	Mnth_Dis	: 1;
	__REG32	Alrm_Dis	: 1;
	__REG32		:25;
} __timeintdis_bits;

/* Interrupt status */
typedef struct {
	__REG32	Hsec_Stat	: 1;
	__REG32	Sec_Stat	: 1;
	__REG32	Min_Stat	: 1;
	__REG32	Hour_Stat	: 1;
	__REG32	Date_Stat	: 1;
	__REG32	Mnth_Stat	: 1;
	__REG32	Alrm_Stat	: 1;
	__REG32		:25;
} __timeintstat_bits;

/* General Status */
typedef struct {
	__REG32	VTC	: 1;
	__REG32	VCC	: 1;
	__REG32	VTAC	: 1;
	__REG32	VCAC	: 1;
	__REG32		:28;
} __rtcstat_bits;

/* Command Transmit Data */
/* Status Receive Data */
typedef union {
    //NA_I2C_TX_CMD_DATA_REG
    struct {
	__REG32	TXDATA	: 8;
	__REG32	CMD	: 5;
	__REG32	TXVAL	: 1;
	__REG32	DLEN	: 1;
	__REG32	PIPE	: 1;
	__REG32		:16;
    };
    //NA_I2C_RX_STATUS_DATA_REG 
    struct {
	__REG32	RXDATA	: 8;
	__REG32	IRQCD	: 4;
	__REG32	MCMDL	: 1;
	__REG32	SCMDL	: 1;
	__REG32	RDE	: 1;
	__REG32	BSTS	: 1;
	__REG32		:16;
    };
} __i2ctxrx_bits;

/* Master Address */
typedef struct {
	__REG32	MAM	: 1;
	__REG32	MDA	:10;
	__REG32		:21;
} __mda_bits;

/* Slave Address */
typedef struct {
	__REG32	SAM	: 1;
	__REG32	SDA	:10;
	__REG32	GCA	: 1;
	__REG32		:20;
} __sla_bits;

/* I2C Configuration */
typedef struct {
	__REG32	CLREF	: 9;
	__REG32	SFW	: 4;
	__REG32	VSCD	: 1;
	__REG32	TMDE	: 1;
	__REG32	IRQD	: 1;
	__REG32		:16;
} __i2cconf_bits;

/* LCDTiming0 */
typedef struct {
	__REG32		: 2;
	__REG32	PPL	: 6;
	__REG32	HSW	: 8;
	__REG32	HFP	: 8;
	__REG32	HBP	: 8;
} __lcdtm0_bits;

/* LCDTiming1 */
typedef struct {
	__REG32	LPP	:10;
	__REG32	VSW	: 6;
	__REG32	VFP	: 8;
	__REG32	VBP	: 8;
} __lcdtm1_bits;

/* LCDTiming2 */
typedef struct {
	__REG32	PCD	: 5;
	__REG32		: 1;
	__REG32	ACB	: 5;
	__REG32	IVS	: 1;
	__REG32	IHS	: 1;
	__REG32	IPC	: 1;
	__REG32	IOE	: 1;
	__REG32		: 1;
	__REG32	CPL	:10;
	__REG32	BCD	: 1;
	__REG32		: 5;
} __lcdtm2_bits;

/* LCDTiming3 */
typedef struct {
	__REG32	LED	: 7;
	__REG32		: 9;
	__REG32	LEE	: 1;
	__REG32		:15;
} __lcdtm3_bits;

/* Upper panel frame base address */
typedef struct {
	__REG32		: 2;
	__REG32	LCDUPBASE	:30;
} __lcdupbase_bits;

/* Lower panel frame base address */
typedef struct {
	__REG32		: 2;
	__REG32	LCDLPBASE	:30;
} __lcdlpbase_bits;

/* Interrupt enable mask */
typedef struct {
	__REG32		: 2;
	__REG32	LNBUINTRENB	: 1;
	__REG32	VCOMPINTRENB	: 1;
	__REG32	MBERRINTRENB	: 1;
	__REG32		:27;
} __lcdintrenable_bits;

/* LCD panel pixel parameters */
typedef struct {
	__REG32	LcdEn	: 1;
	__REG32	LcdBpp	: 3;
	__REG32	LcdBW	: 1;
	__REG32	LcdTFT	: 1;
	__REG32	LcdMono8	: 1;
	__REG32	LcdDual	: 1;
	__REG32	BGR	: 1;
	__REG32	BEBO	: 1;
	__REG32	BEPO	: 1;
	__REG32	LcdPwr	: 1;
	__REG32	LcdVComp	: 2;
	__REG32		: 2;
	__REG32	WATERMARK	: 1;
	__REG32		:15;
} __lcdctrl_bits;

/* LCD Raw interrupt status */
typedef struct {
	__REG32		: 2;
	__REG32	LNBU	: 1;
	__REG32	VCOMP	: 1;
	__REG32	MBERROR	: 1;
	__REG32		:27;
} __lcdstatus_bits;

/* LCD Final masked interrupts */
typedef struct {
	__REG32		: 2;
	__REG32	LNBUINTR	: 1;
	__REG32	VCOMPINTR	: 1;
	__REG32	MBERRORINTR	: 1;
	__REG32		:27;
} __lcdint_bits;

/* LCD Palette register */
typedef struct {
	__REG32	R1	: 5;
	__REG32	G1	: 5;
	__REG32	B1	: 5;
	__REG32	Int1	: 1;
	__REG32	R0	: 5;
	__REG32	G0	: 5;
	__REG32	B0	: 5;
	__REG32	Int0	: 1;
} __lcdpalette_bits;

/* UART SPI Serial Channel B/A/C/D Control register A */
typedef union {
    //UARTChannelBCtrlA UARTChannelACtrlA UARTChannelCCtrlA UARTChannelDCtrlA
    struct {
	__REG32	ETXDMA	: 1;
	__REG32	TIC	: 4;
	__REG32	RIC	: 3;
	__REG32	ERXDMA	: 1;
	__REG32	RIE	: 3;
	__REG32		: 4;
	__REG32	RTS	: 1;
	__REG32	DTR	: 1;
	__REG32		: 2;
	__REG32	LL	: 1;
	__REG32	RL	: 1;
	__REG32	RTSRX	: 1;
	__REG32	CTSTX	: 1;
	__REG32	WLS	: 2;
	__REG32	STOP	: 1;
	__REG32	PE	: 1;
	__REG32	EPS	: 1;
	__REG32	STICKP	: 1;
	__REG32	BRK	: 1;
	__REG32	CE	: 1;
    };
    //SPIChannelBCtrlA SPIChannelACtrlA SPIChannelCCtrlA SPIChannelDCtrlA
    struct {
	__REG32		: 1; //ETXDMA
	__REG32		: 4; //TIC
	__REG32		: 3;
	__REG32		: 1; //ERXDMA
	__REG32		: 3; //RIE
	__REG32		: 8;
	__REG32		: 1; //LL
	__REG32		: 1; //RL
	__REG32		: 2;
	__REG32		: 2; //WLS
	__REG32		: 5;
	__REG32		: 1; //CE
    };
} __serctrl_bits;

/* UART SPI Serial Channel B/A/C/D Control register B */
typedef union {
    //UARTChannelBCtrlB UARTChannelACtrlB UARTChannelCCtrlB UARTChannelDCtrlB
    struct {
	__REG32		:15;
	__REG32	RTSTX	: 1;
	__REG32		: 3;
	__REG32	BITORDR	: 1;
	__REG32	MODE	: 2;
	__REG32		: 4;
	__REG32	RCGT	: 1;
	__REG32	RBGT	: 1;
	__REG32	RDM	: 4;
    };
    //SPIChannelBCtrlB SPIChannelACtrlB SPIChannelCCtrlB SPIChannelDCtrlB
    struct {
	__REG32		:19;
	__REG32		: 1; //BITORDER
	__REG32		: 2; //MODE
	__REG32		: 3;
	__REG32	CSPOL	: 1; //CSPOL
	__REG32		: 1; //RCGT
	__REG32		: 1; //RBGT
	__REG32		: 4; //RDM
    };
} __serctrl2_bits;

/* UART SPI Serial Channel B/A/C/D Status register A) */
typedef union {
    //UARTChannelBStatusA UARTChannelAStatusA UARTChannelCStatusA UARTChannelDStatusA
    struct {
	__REG32	TEMPTY	: 1;
	__REG32		: 1;
	__REG32	THALF	: 1;
	__REG32	TRDY	: 1;
	__REG32	CTSI	: 1;
	__REG32	DSRI	: 1;
	__REG32	RII	: 1;
	__REG32	DCDI	: 1;
	__REG32	RFS	: 1;
	__REG32	RBC	: 1;
	__REG32	RHALF	: 1;
	__REG32	RRDY	: 1;
	__REG32	ROVER	: 1;
	__REG32	RPE	: 1;
	__REG32	RFE	: 1;
	__REG32	RBRK	: 1;
	__REG32	CTS	: 1;
	__REG32	DSR 	: 1;
	__REG32	RI	: 1;
	__REG32	DCD	: 1;
	__REG32	RXFDB	: 2;
	__REG32	RBCPEND	: 1;
	__REG32		: 3;
	__REG32	CGAP	: 1;
	__REG32	BGAP	: 1;
	__REG32	MATCH	: 4;
    };
    //SPIChannelBStatusA SPIChannelAStatusA SPIChannelCStatusA SPIChannelDStatusA
    struct {
	__REG32		: 1; //TEMPTY
	__REG32		: 1;
	__REG32		: 1; //THALF
	__REG32		: 1; //TRDY
	__REG32		: 4;
	__REG32		: 1; //RFS
	__REG32		: 1; //RBC
	__REG32		: 1; //RHALF
	__REG32		: 1; //RRDY
	__REG32		: 1; //ROVER
	__REG32		: 7;
	__REG32		: 2; //RXFDB
	__REG32		: 1; //RBCPEND
	__REG32		: 3;
	__REG32		: 1; //CGAP
	__REG32		: 1; //BGAP
	__REG32		: 4; //MATCH
    };
} __serstata_bits;

/* UART SPI Serial Channel B/A/C/D Bit-rate */
typedef union {
    //UARTChannelBBitrate UARTChannelABitrate UARTChannelCBitrate UARTChannelDBitrate
    struct {
	__REG32	N	:15;
	__REG32		: 2;
	__REG32	RDCR	: 2;
	__REG32	TDCR	: 2;
	__REG32		: 1;
	__REG32	RXCINV	: 1;
	__REG32	TXCINV	: 1;
	__REG32	CLKMUX	: 2;
	__REG32	TXEXT	: 1;
	__REG32	RXEXT	: 1;
	__REG32	TXSRC	: 1;
	__REG32	RXSRC	: 1;
	__REG32	TMODE	: 1;
	__REG32	EBIT	: 1;
    };
    //SPIChannelBBitrate SPIChannelABitrate SPIChannelCBitrate SPIChannelDBitrate
    struct {
	__REG32		:15; //N
	__REG32	RICS	: 1;
	__REG32	TICS	: 1;
	__REG32		: 2; //RDCR
	__REG32		: 2; //TDCR
	__REG32	SPCPOL	: 1;
	__REG32		: 1; //RXCINV
	__REG32		: 1; //TXCINV
	__REG32		: 2; //CLKMUX
	__REG32		: 1; //TXEXT
	__REG32		: 1; //RXEXT
	__REG32		: 1; //TXSRC
	__REG32		: 1; //RXSRC
	__REG32		: 1; //TMODE
	__REG32		: 1; //EBIT
    };
} __serbitrate_bits;

/* UART SPI Serial Channel B/A/C/D Receive buffer GAP timer */
typedef struct {
	__REG32	BT	:16;
	__REG32		:15;
	__REG32	TRUN	: 1;
} __sergapbfr_bits;

/* UART SPI Serial Channel B/A/C/D Receive character GAP timer */
typedef struct {
	__REG32	CT	:20;
	__REG32		:11;
	__REG32	TRUN	: 1;
} __sergapchr_bits;

/* UART SPI Serial Channel B/A/C/D Receive Match */
typedef struct {
	__REG32	RDMB4	: 8;
	__REG32	RDMB3	: 8;
	__REG32	RDMB2	: 8;
	__REG32	RDMB1	: 8;
} __sermatch_bits;

/* UART SPI Serial Channel B/A/C/D Receive Match Mask */
typedef struct {
	__REG32	RMMB4	: 8;
	__REG32	RMMB3	: 8;
	__REG32	RMMB2	: 8;
	__REG32	RMMB1	: 8;
} __sermatchm_bits;

/* Serial Channel B/A/C/D Flow Control */
typedef struct {
	__REG32	FLOW1	: 2;
	__REG32	FLOW2	: 2;
	__REG32	FLOW3	: 2;
	__REG32	FLOW4	: 2;
	__REG32	FLOW_STATE	: 2;
	__REG32		:22;
} __serflow_bits;

/* Serial Channel B/A/C/D Flow Control Force */
typedef struct {
	__REG32	FORCE_CHAR	: 8;
	__REG32		: 8;
	__REG32	FORCE_EN	: 1;
	__REG32	TX_DIS	: 1;
	__REG32		: 2;
	__REG32	TX_IDLE	: 1;
	__REG32		:11;
} __serflowfrc_bits;

/* IEEE 1284 General Configuration */
typedef struct {
	__REG32	RM	: 1;
	__REG32	FDM	: 1;
	__REG32		: 1;
	__REG32	FCM	: 1;
	__REG32	RRT	: 2;
	__REG32		: 2;
	__REG32	FDRT	: 2;
	__REG32	FCRT	: 2;
	__REG32		: 1;
	__REG32	CPS	: 1;
	__REG32	AFSH	: 1;
	__REG32		:17;
} __1284conf_bits;

/* IEEE 1284 Interrupt Status and Control */
typedef struct {
	__REG32		: 1;
	__REG32	PC1I	: 1;
	__REG32	FCFRI	: 1;
	__REG32	FDFRI	: 1;
	__REG32	FCFMB	: 1;
	__REG32	FDFMB	: 1;
	__REG32	FCFBG	: 1;
	__REG32	FDFBG	: 1;
	__REG32		: 2;
	__REG32	RFRI	: 1;
	__REG32		: 6;
	__REG32	I1M	: 1;
	__REG32	FCRIM	: 1;
	__REG32	FDRIM	: 1;
	__REG32	FCMBM	: 1;
	__REG32	FDMBM	: 1;
	__REG32	FCBGM	: 1;
	__REG32	FDBGM	: 1;
	__REG32		: 2;
	__REG32	RFRIM	: 1;
	__REG32		: 5;
} __1284int_bits;

/* IEEE 1284 FIFO Status */
typedef struct {
	__REG32	RFR	: 1;
	__REG32	RFAF	: 1;
	__REG32	RFF	: 1;
	__REG32	FDFR	: 1;
	__REG32	FDFAE	: 1;
	__REG32	FDFE	: 1;
	__REG32	FDFDR	: 2;
	__REG32		: 3;
	__REG32	FCFR	: 1;
	__REG32	FCFA	: 1;
	__REG32	FCFE	: 1;
	__REG32	FCFDR	: 2;
	__REG32		:16;
} __1284fifo_bits;

/* IEEE 1284 Forward Command DMA Control */
typedef struct {
	__REG32	FwCmdByteGapTimer	:16;
	__REG32	FwCmdMaxBufSize	:16;
} __1284dmacmd_bits;

/* IEEE 1284 Forward Data DMA Control */
typedef struct {
	__REG32	FwDatByteGapTimer	:16;
	__REG32	FwDatMaxBufSize	:16;
} __1284dmadat_bits;

/* IEEE 1284 Printer Data Pins */
typedef struct {
	__REG32	pd	: 8;
	__REG32		:24;
} __1284pd_bits;

/* IEEE 1284 Port Status host */
typedef struct {
	__REG32	N_STROBE	: 1;
	__REG32	N_SLCTIN	: 1;
	__REG32	N_INIT	: 1;
	__REG32	N_AUTOFD	: 1;
	__REG32		:28;
} __1284psr_bits;

/* IEEE 1284 Port Control */
typedef struct {
	__REG32		: 3;
	__REG32	N_FLT	: 1;
	__REG32	SEL	: 1;
	__REG32	PERR	: 1;
	__REG32	N_ACK	: 1;
	__REG32	BUSY	: 1;
	__REG32		:24;
} __1284pcr_bits;

/* IEEE 1284 Feature Control A */
typedef struct {
	__REG32	PPtEn	: 1;
	__REG32		:31;
} __1284fea_bits;

/* IEEE 1284 Interrupt Enable */
typedef struct {
	__REG32	TransferStart	: 1;
	__REG32	NegotiationStart	: 1;
	__REG32		: 2;
	__REG32	ECPChannelAddress	: 1;
	__REG32	PinSelectInterrupt	: 1;
	__REG32		:26;
} __1284fei_bits;

/* IEEE 1284 Master Enable */
typedef struct {
	__REG32		: 2;
	__REG32	AutoNegotiate	: 1;
	__REG32		: 1;
	__REG32	AutoTransfer	: 1;
	__REG32	SPP_PS2	: 1;
	__REG32	ECP	: 1;
	__REG32		:25;
} __1284fem_bits;

/* IEEE 1284 Extensibility Byte Requested by host */
typedef struct {
	__REG32	exr	: 8;
	__REG32		:24;
} __1284exr_bits;

/* IEEE 1284 Extended Control */
typedef struct {
	__REG32		: 6;
	__REG32	EnRevDtTrn	: 1;
	__REG32		:25;
} __1284ecr_bits;

/* IEEE 1284 Interrupt Status */
typedef struct {
	__REG32	TSDI	: 1;
	__REG32	NSDI	: 1;
	__REG32		: 2;
	__REG32	ECPChAddr	: 1;
	__REG32	PSINT	: 1;
	__REG32		:26;
} __1284sti_bits;

/* IEEE 1284 Pin Interrupt Mask */
typedef struct {
	__REG32	n_strobe_level_detect	: 1;
	__REG32	n_selectin_level_detect	: 1;
	__REG32	n_init_level_detect	: 1;
	__REG32	n_autofd_level_detect	: 1;
	__REG32	n_strobe_edge_detect	: 1;
	__REG32	n_selectin_edge_detect	: 1;
	__REG32	n_init_edge_detect	: 1;
	__REG32	n_autofd_edge_detect	: 1;
	__REG32		:24;
} __1284msk_bits;

/* IEEE 1284 Pin Interrupt Control */
typedef struct {
	__REG32	n_strobe_level	: 1;
	__REG32	n_selectin_level	: 1;
	__REG32	n_init_level	: 1;
	__REG32	n_autofd_level	: 1;
	__REG32	n_strobe_edge_detect	: 1;
	__REG32	n_selectin_edge_detect	: 1;
	__REG32	n_init_edge_detect	: 1;
	__REG32	n_autofd_edge_detect	: 1;
	__REG32		:24;
} __1284pit_bits;

/* IEEE 1284 Granularity Count */
typedef struct {
	__REG32	grn	: 8;
	__REG32		:24;
} __1284grn_bits;

/* IEEE 1284 Forward address */
typedef struct {
	__REG32	eca	: 8;
	__REG32		:24;
} __1284eca_bits;

/* IEEE 1284 Core Phase */
typedef struct {
	__REG32	pha	: 8;
	__REG32		:24;
} __1284pha_bits;

/* UHFE Control and Status */
typedef struct {
	__REG32		:11;
	__REG32	HSTRST	: 1;
	__REG32		:20;
} __hstrst_bits;

/* UHFE Interrupt Enable */
typedef struct {
	__REG32		: 1;
	__REG32	OHCI_IRQ	: 1;
	__REG32		:30;
} __uhfeinten_bits;

/* HCRevision */
typedef struct {
	__REG32	REV	: 8;
	__REG32		:24;
} __hcrevision_bits;

/* HCControl */
typedef struct {
	__REG32	CBSR	: 2;
	__REG32	PLE	: 1;
	__REG32	IE	: 1;
	__REG32	CLE	: 1;
	__REG32	BLE	: 1;
	__REG32	HCFS	: 2;
	__REG32	IR	: 1;
	__REG32	RWC	: 1;
	__REG32	RWE	: 1;
	__REG32		:21;
} __hccontrol_bits;

/* HCCommandStatus */
typedef struct {
	__REG32	HCR	: 1;
	__REG32	CLF	: 1;
	__REG32	BLF	: 1;
	__REG32	OCR	: 1;
	__REG32		:12;
	__REG32	SOC	: 2;
	__REG32		:14;
} __hccommand_bits;

/* HCInterrupt Status*/
typedef struct {
	__REG32	SO	: 1;
	__REG32	WDH	: 1;
	__REG32	SF	: 1;
	__REG32	RD	: 1;
	__REG32	UE	: 1;
	__REG32	FNO	: 1;
	__REG32	RHSC	: 1;
	__REG32		:23;
	__REG32	OC	: 1;
	__REG32		: 1;
} __hcint_bits;

/* HCInterrupt Enable */
typedef struct {
	__REG32	SO	: 1;
	__REG32	WDH	: 1;
	__REG32	SF	: 1;
	__REG32	RD	: 1;
	__REG32	UE	: 1;
	__REG32	FNO	: 1;
	__REG32	RHSC	: 1;
	__REG32		:23;
	__REG32	OC	: 1;
	__REG32	MIE	: 1;
} __hcinten_bits;

/* Host Controller Communications Area */
typedef struct {
	__REG32		: 8;
	__REG32	HCCA	:24;
} __hchcca_bits;

/* HcPeriodCurrentED */
typedef struct {
	__REG32		: 4;
	__REG32	PCED	:28;
} __hcpced_bits;

/* HcControlHeadED */
typedef struct {
	__REG32		: 4;
	__REG32	CHED	:28;
} __hcched_bits;

/* HcControlCurrentED */
typedef struct {
	__REG32		: 4;
	__REG32	CCED	:28;
} __hccced_bits;

/* HcBulkHeadED */
typedef struct {
	__REG32		: 4;
	__REG32	BHED	:28;
} __hcbhed_bits;

/* HcBulkCurrentED */
typedef struct {
	__REG32		: 4;
	__REG32	BCED	:28;
} __hcbced_bits;

/* HcDoneHead */
typedef struct {
	__REG32		: 4;
	__REG32	DH	:28;
} __hcdh_bits;

/* HcFmInterval */
typedef struct {
	__REG32	FI	:14;
	__REG32		: 2;
	__REG32	FSMPS	:15;
	__REG32	FIT	: 1;
} __hcfmint_bits;

/* HcFmRemaining */
typedef struct {
	__REG32	FR	:14;
	__REG32		:17;
	__REG32	FRT	: 1;
} __hcfmrem_bits;

/* HcFmNumber */
typedef struct {
	__REG32	FN	:16;
	__REG32		:16;
} __hcfmnum_bits;

/* HcFmPeriodicStart */
typedef struct {
	__REG32	PS	:14;
	__REG32		:18;
} __hcfmper_bits;

/* HcLSTreshold */
typedef struct {
	__REG32	LST	:12;
	__REG32		:20;
} __hclst_bits;

/* HcRhDescriptorA */
typedef struct {
	__REG32	NDP	: 8;
	__REG32	NPS	: 1;
	__REG32	PSM	: 1;
	__REG32	DT	: 1;
	__REG32	OCPM	: 1;
	__REG32	NOCP	: 1;
	__REG32		:11;
	__REG32	POTPGT	: 8;
} __hcrhdesca_bits;

/* HcRhDescriptorB */
typedef struct {
	__REG32	DR	:16;
	__REG32	PPCM	:16;
} __hcrhdescb_bits;

/* HcRhStatus */
typedef struct {
	__REG32	LPS	: 1;
	__REG32	OCI	: 1;
	__REG32		:13;
	__REG32	DRWE	: 1;
	__REG32	LPSC	: 1;
	__REG32	CCIC	: 1;
	__REG32		:13;
	__REG32	CRWE	: 1;
} __hcrhstat_bits;

/* HcRhPortStatus */
typedef struct {
	__REG32	CCS	: 1;
	__REG32	PES	: 1;
	__REG32	PSS	: 1;
	__REG32	POCI	: 1;
	__REG32	PRS	: 1;
	__REG32		: 3;
	__REG32	PPS	: 1;
	__REG32	LSDA	: 1;
	__REG32		: 6;
	__REG32	CSC	: 1;
	__REG32	PESC	: 1;
	__REG32	PSSC	: 1;
	__REG32	OCIC	: 1;
	__REG32	PRSC	: 1;
	__REG32		:11;
} __hcrhportstat_bits;

/* UDFE Control and Status 0 */
typedef struct {
	__REG32		: 2;
	__REG32	WKUP	: 1;
	__REG32		: 2;
	__REG32	SUSP	: 1;
	__REG32		: 3;
	__REG32	DRST	: 2;
	__REG32		:21;
} __udfectrl0_bits;

/* UDFE Control and Status 1 */
typedef struct {
	__REG32	CFG	: 4;
	__REG32	INTF	: 4;
	__REG32	ALT	: 4;
	__REG32	FRAME	:11;
	__REG32		: 4;
	__REG32	SYNC	: 1;
	__REG32		: 1;
	__REG32	SPWR	: 1;
	__REG32		: 1;
	__REG32	RSUM	: 1;
} __udfectrl1_bits;

/* UDFE Interrupt Enable */
typedef struct {
	__REG32		: 7;
	__REG32	SETCFG	: 1;
	__REG32	SETINTF	: 1;
	__REG32	SSPND	: 1;
	__REG32	SOF	: 1;
	__REG32	URST	: 1;
	__REG32	FIFO	: 1;
	__REG32		: 1;
	__REG32	DMA1	: 1;
	__REG32	DMA2	: 1;
	__REG32	DMA3	: 1;
	__REG32	DMA4	: 1;
	__REG32	DMA5	: 1;
	__REG32	DMA6	: 1;
	__REG32	DMA7	: 1;
	__REG32	DMA8	: 1;
	__REG32	DMA9	: 1;
	__REG32	DMA10	: 1;
	__REG32	DMA11	: 1;
	__REG32	DMA12	: 1;
	__REG32		: 1;
	__REG32	GBL_DMA	: 1;
	__REG32		: 3;
	__REG32	GBL_EN	: 1;
} __udfeinten_bits;

/* UDFE Interrupt Status */
typedef struct {
	__REG32		: 7;
	__REG32	SETCFG	: 1;
	__REG32	SETINTF	: 1;
	__REG32	SSPND	: 1;
	__REG32	SOF	: 1;
	__REG32	URST	: 1;
	__REG32	FIFO	: 1;
	__REG32		: 1;
	__REG32	DMA1	: 1;
	__REG32	DMA2	: 1;
	__REG32	DMA3	: 1;
	__REG32	DMA4	: 1;
	__REG32	DMA5	: 1;
	__REG32	DMA6	: 1;
	__REG32	DMA7	: 1;
	__REG32	DMA8	: 1;
	__REG32	DMA9	: 1;
	__REG32	DMA10	: 1;
	__REG32	DMA11	: 1;
	__REG32	DMA12	: 1;
	__REG32		: 1;
	__REG32	GBL_DMA	: 1;
	__REG32		: 4;
} __udfeintstat_bits;

/* UDFE USB Device Controller Programming Control/Status */
typedef struct {
	__REG32	CSRPRG	: 1;
	__REG32	DONECSR	: 1;
	__REG32	SETCSR	: 1;
	__REG32		:29;
} __udfectrlstat_bits;

/* Physical Endpoint Descriptor */
typedef struct {
	__REG32	EP	: 4;
	__REG32	DIR	: 1;
	__REG32	TYPE	: 2;
	__REG32	CONFIG	: 4;
	__REG32	IF	: 4;
	__REG32	ALT	: 4;
	__REG32	MAXSIZE	:10;
	__REG32		: 3;
} __phendx_bits;

/* FIFO Interrupt Status 0 */
typedef struct {
	__REG32		: 5;
	__REG32	ERROR1	: 1;
	__REG32	NAK1	: 1;
	__REG32	ACK1	: 1;
	__REG32		: 5;
	__REG32	ERROR2	: 1;
	__REG32	NAK2	: 1;
	__REG32	ACK2	: 1;
	__REG32		:16;
} __fifointstat0_bits;

/* FIFO Interrupt Status 1 */
typedef struct {
	__REG32		: 5;
	__REG32	ERROR3	: 1;
	__REG32	NAK3	: 1;
	__REG32	ACK3	: 1;
	__REG32		: 5;
	__REG32	ERROR4	: 1;
	__REG32	NAK4	: 1;
	__REG32	ACK4	: 1;
	__REG32		: 5;
	__REG32	ERROR5	: 1;
	__REG32	NAK5	: 1;
	__REG32	ACK5	: 1;
	__REG32		: 5;
	__REG32	ERROR6	: 1;
	__REG32	NAK6	: 1;
	__REG32	ACK6	: 1;
} __fifointstat1_bits;

/* FIFO Interrupt Status 2 */
typedef struct {
	__REG32		: 5;
	__REG32	ERROR7	: 1;
	__REG32	NAK7	: 1;
	__REG32	ACK7	: 1;
	__REG32		: 5;
	__REG32	ERROR8	: 1;
	__REG32	NAK8	: 1;
	__REG32	ACK8	: 1;
	__REG32		: 5;
	__REG32	ERROR9	: 1;
	__REG32	NAK9	: 1;
	__REG32	ACK9	: 1;
	__REG32		: 5;
	__REG32	ERROR10	: 1;
	__REG32	NAK10	: 1;
	__REG32	ACK10	: 1;
} __fifointstat2_bits;

/* FIFO Interrupt Status 3 */
typedef struct {
	__REG32		: 5;
	__REG32	ERROR11	: 1;
	__REG32	NAK11	: 1;
	__REG32	ACK11	: 1;
	__REG32		: 5;
	__REG32	ERROR12	: 1;
	__REG32	NAK12	: 1;
	__REG32	ACK12	: 1;
	__REG32		:16;
} __fifointstat3_bits;

/* FIFO Packet Control */
typedef struct {
	__REG32	COUNT	:16;
	__REG32		: 4;
	__REG32	MAX	:10;
	__REG32		: 2;
} __fifopctrlx_bits;

/* FIFO Status and Control */
typedef struct {
	__REG32	TIMEOUT_CNT	: 4;
	__REG32		: 6;
	__REG32	TIMEOUT	: 1;
	__REG32	OVERFLOW	: 1;
	__REG32	M30	: 1;
	__REG32	M31	: 1;
	__REG32		: 4;
	__REG32	DIR	: 1;
	__REG32	CLR	: 1;
	__REG32	TYPE	: 2;
	__REG32	SEND_STALL	: 1;
	__REG32	STALL_SENT	: 1;
	__REG32		: 8;
} __fifostatctrlx_bits;

#endif	/* __IAR_SYSTEMS_ICC__ */

/* Declarations common to compiler and assembler  **************************/
	
/***************************************************************************
 **
 ** BBus DMA Controller
 **
 ***************************************************************************/
__IO_REG32(    NA_BDCM_DBDP01_REG,              0x90000000, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP02_REG,              0x90000020, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP03_REG,              0x90000040, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP04_REG,              0x90000060, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP05_REG,              0x90000080, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP06_REG,              0x900000A0, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP07_REG,              0x900000C0, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP08_REG,              0x900000E0, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP09_REG,              0x90000100, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP10_REG,              0x90000120, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP11_REG,              0x90000140, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP12_REG,              0x90000160, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP13_REG,              0x90000180, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP14_REG,              0x900001A0, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP15_REG,              0x900001C0, __READ_WRITE                  );
__IO_REG32(    NA_BDCM_DBDP16_REG,              0x900001E0, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_0,         0x90910000, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_1,         0x90910020, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_2,         0x90910040, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_3,         0x90910060, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_4,         0x90910080, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_5,         0x909100A0, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_6,         0x909100C0, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_7,         0x909100E0, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_8,         0x90910100, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_9,         0x90910120, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_10,        0x90910140, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_11,        0x90910160, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_12,        0x90910180, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_13,        0x909101A0, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_14,        0x909101C0, __READ_WRITE                  );
__IO_REG32(    NA_USB_DEVICE_DMA_BDP_15,        0x909101E0, __READ_WRITE                  );
__IO_REG32_BIT(NA_BDCM_DCR01_REG,               0x90000010, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR02_REG,               0x90000030, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR03_REG,               0x90000050, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR04_REG,               0x90000070, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR05_REG,               0x90000090, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR06_REG,               0x900000B0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR07_REG,               0x900000D0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR08_REG,               0x900000F0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR09_REG,               0x90000110, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR10_REG,               0x90000130, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR11_REG,               0x90000150, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR12_REG,               0x90000170, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR13_REG,               0x90000190, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR14_REG,               0x900001B0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR15_REG,               0x900001D0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DCR16_REG,               0x900001F0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_0,         0x90910010, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_1,         0x90910030, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_2,         0x90910050, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_3,         0x90910070, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_4,         0x90910090, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_5,         0x909100B0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_6,         0x909100D0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_7,         0x909100F0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_8,         0x90910110, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_9,         0x90910130, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_10,        0x90910150, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_11,        0x90910170, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_12,        0x90910190, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_13,        0x909101B0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_14,        0x909101D0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_USB_DEVICE_DMA_CCR_15,        0x909101F0, __READ_WRITE, __dmachctrl_bits);
__IO_REG32_BIT(NA_BDCM_DSIER01_REG,             0x90000014, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER02_REG,             0x90000034, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER03_REG,             0x90000054, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER04_REG,             0x90000074, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER05_REG,             0x90000094, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER06_REG,             0x900000B4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER07_REG,             0x900000D4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER08_REG,             0x900000F4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER09_REG,             0x90000114, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER10_REG,             0x90000134, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER11_REG,             0x90000154, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER12_REG,             0x90000174, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER13_REG,             0x90000194, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER14_REG,             0x900001B4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER15_REG,             0x900001D4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_BDCM_DSIER16_REG,             0x900001F4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_0,        0x90910014, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_1,        0x90910034, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_2,        0x90910054, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_3,        0x90910074, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_4,        0x90910094, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_5,        0x909100B4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_6,        0x909100D4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_7,        0x909100F4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_8,        0x90910114, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_9,        0x90910134, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_10,       0x90910154, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_11,       0x90910174, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_12,       0x90910194, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_13,       0x909101B4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_14,       0x909101D4, __READ_WRITE, __dmaint_bits   );
__IO_REG32_BIT(NA_USB_DEVICE_DMA_SIER_15,       0x909101F4, __READ_WRITE, __dmaint_bits   );

/***************************************************************************
 **
 ** UART Module
 **
 ***************************************************************************/
__IO_REG32_BIT(UARTChannelBCtrlA,               0x90200000, __READ_WRITE, __serctrl_bits   );
__IO_REG32_BIT(UARTChannelBCtrlB,               0x90200004, __READ_WRITE, __serctrl2_bits  );
__IO_REG32_BIT(UARTChannelBStatusA,             0x90200008, __READ      , __serstata_bits  );
__IO_REG32_BIT(UARTChannelBBitrate,             0x9020000C, __READ_WRITE, __serbitrate_bits);
__IO_REG32(    UARTChannelBFIFOData,            0x90200010, __READ_WRITE                   );
__IO_REG32_BIT(UARTChannelBBufGAP,              0x90200014, __READ_WRITE, __sergapbfr_bits );
__IO_REG32_BIT(UARTChannelBCharGap,             0x90200018, __READ_WRITE, __sergapchr_bits );
__IO_REG32_BIT(UARTChannelBMatch,               0x9020001C, __READ_WRITE, __sermatch_bits  );
__IO_REG32_BIT(UARTChannelBMatchMsk,            0x90200020, __READ_WRITE, __sermatchm_bits );
__IO_REG32_BIT(UARTChannelBFlowCtrl,            0x90200034, __READ_WRITE, __serflow_bits   );
__IO_REG32_BIT(UARTChannelBFlowForce,           0x90200038, __READ_WRITE, __serflowfrc_bits);
__IO_REG32_BIT(UARTChannelACtrlA,               0x90200040, __READ_WRITE, __serctrl_bits   );
__IO_REG32_BIT(UARTChannelACtrlB,               0x90200044, __READ_WRITE, __serctrl2_bits  );
__IO_REG32_BIT(UARTChannelAStatusA,             0x90200048, __READ      , __serstata_bits  );
__IO_REG32_BIT(UARTChannelABitrate,             0x9020004C, __READ_WRITE, __serbitrate_bits);
__IO_REG32(    UARTChannelAFIFOData,            0x90200050, __READ_WRITE                   );
__IO_REG32_BIT(UARTChannelABufGAP,              0x90200054, __READ_WRITE, __sergapbfr_bits );
__IO_REG32_BIT(UARTChannelACharGap,             0x90200058, __READ_WRITE, __sergapchr_bits );
__IO_REG32_BIT(UARTChannelAMatch,               0x9020005C, __READ_WRITE, __sermatch_bits  );
__IO_REG32_BIT(UARTChannelAMatchMsk,            0x90200060, __READ_WRITE, __sermatchm_bits );
__IO_REG32_BIT(UARTChannelAFlowCtrl,            0x90200074, __READ_WRITE, __serflow_bits   );
__IO_REG32_BIT(UARTChannelAFlowForce,           0x90200078, __READ_WRITE, __serflowfrc_bits);
__IO_REG32_BIT(UARTChannelCCtrlA,               0x90300000, __READ_WRITE, __serctrl_bits   );
__IO_REG32_BIT(UARTChannelCCtrlB,               0x90300004, __READ_WRITE, __serctrl2_bits  );
__IO_REG32_BIT(UARTChannelCStatusA,             0x90300008, __READ      , __serstata_bits  );
__IO_REG32_BIT(UARTChannelCBitrate,             0x9030000C, __READ_WRITE, __serbitrate_bits);
__IO_REG32(    UARTChannelCFIFOData,            0x90300010, __READ_WRITE                   );
__IO_REG32_BIT(UARTChannelCBufGAP,              0x90300014, __READ_WRITE, __sergapbfr_bits );
__IO_REG32_BIT(UARTChannelCCharGap,             0x90300018, __READ_WRITE, __sergapchr_bits );
__IO_REG32_BIT(UARTChannelCMatch,               0x9030001C, __READ_WRITE, __sermatch_bits  );
__IO_REG32_BIT(UARTChannelCMatchMsk,            0x90300020, __READ_WRITE, __sermatchm_bits );
__IO_REG32_BIT(UARTChannelCFlowCtrl,            0x90300034, __READ_WRITE, __serflow_bits   );
__IO_REG32_BIT(UARTChannelCFlowForce,           0x90300038, __READ_WRITE, __serflowfrc_bits);
__IO_REG32_BIT(UARTChannelDCtrlA,               0x90300040, __READ_WRITE, __serctrl_bits   );
__IO_REG32_BIT(UARTChannelDCtrlB,               0x90300044, __READ_WRITE, __serctrl2_bits  );
__IO_REG32_BIT(UARTChannelDStatusA,             0x90300048, __READ      , __serstata_bits  );
__IO_REG32_BIT(UARTChannelDBitrate,             0x9030004C, __READ_WRITE, __serbitrate_bits);
__IO_REG32(    UARTChannelDFIFOData,            0x90300050, __READ_WRITE                   );
__IO_REG32_BIT(UARTChannelDBufGAP,              0x90300054, __READ_WRITE, __sergapbfr_bits );
__IO_REG32_BIT(UARTChannelDCharGap,             0x90300058, __READ_WRITE, __sergapchr_bits );
__IO_REG32_BIT(UARTChannelDMatch,               0x9030005C, __READ_WRITE, __sermatch_bits  );
__IO_REG32_BIT(UARTChannelDMatchMsk,            0x90300060, __READ_WRITE, __sermatchm_bits );
__IO_REG32_BIT(UARTChannelDFlowCtrl,            0x90300074, __READ_WRITE, __serflow_bits   );
__IO_REG32_BIT(UARTChannelDFlowForce,           0x90300078, __READ_WRITE, __serflowfrc_bits);

/***************************************************************************
 **
 ** SPI Module
 **
 ***************************************************************************/
#define SPIChannelBCtrlA                        UARTChannelBCtrlA
#define SPIChannelBCtrlA_bit                    UARTChannelBCtrlA_bit
#define SPIChannelACtrlA                        UARTChannelACtrlA
#define SPIChannelACtrlA_bit                    UARTChannelACtrlA_bit
#define SPIChannelCCtrlA                        UARTChannelCCtrlA
#define SPIChannelCCtrlA_bit                    UARTChannelCCtrlA_bit
#define SPIChannelDCtrlA                        UARTChannelDCtrlA
#define SPIChannelDCtrlA_bit                    UARTChannelDCtrlA_bit
#define SPIChannelBCtrlB                        UARTChannelBCtrlB
#define SPIChannelBCtrlB_bit                    UARTChannelBCtrlB_bit
#define SPIChannelACtrlB                        UARTChannelACtrlB
#define SPIChannelACtrlB_bit                    UARTChannelACtrlB_bit
#define SPIChannelCCtrlB                        UARTChannelCCtrlB
#define SPIChannelCCtrlB_bit                    UARTChannelCCtrlB_bit
#define SPIChannelDCtrlB                        UARTChannelDCtrlB
#define SPIChannelDCtrlB_bit                    UARTChannelDCtrlB_bit
#define SPIChannelBStatusA                      UARTChannelBStatusA
#define SPIChannelBStatusA_bit                  UARTChannelBStatusA_bit
#define SPIChannelAStatusA                      UARTChannelAStatusA
#define SPIChannelAStatusA_bit                  UARTChannelAStatusA_bit
#define SPIChannelCStatusA                      UARTChannelCStatusA
#define SPIChannelCStatusA_bit                  UARTChannelCStatusA_bit
#define SPIChannelDStatusA                      UARTChannelDStatusA
#define SPIChannelDStatusA_bit                  UARTChannelDStatusA_bit
#define SPIChannelBBitrate                      UARTChannelBBitrate
#define SPIChannelBBitrate_bit                  UARTChannelBBitrate_bit
#define SPIChannelABitrate                      UARTChannelABitrate
#define SPIChannelABitrate_bit                  UARTChannelABitrate_bit
#define SPIChannelCBitrate                      UARTChannelCBitrate
#define SPIChannelCBitrate_bit                  UARTChannelCBitrate_bit
#define SPIChannelDBitrate                      UARTChannelDBitrate
#define SPIChannelDBitrate_bit                  UARTChannelDBitrate_bit
#define SPIChannelBFIFOData                     UARTChannelBFIFOData
#define SPIChannelAFIFOData                     UARTChannelAFIFOData
#define SPIChannelCFIFOData                     UARTChannelCFIFOData
#define SPIChannelDFIFOData                     UARTChannelDFIFOData
#define SPIChannelBBufGAP                       UARTChannelBBufGAP
#define SPIChannelBBufGAP_bit                   UARTChannelBBufGAP_bit
#define SPIChannelABufGAP                       UARTChannelABufGAP
#define SPIChannelABufGAP_bit                   UARTChannelABufGAP_bit
#define SPIChannelCBufGAP                       UARTChannelCBufGAP
#define SPIChannelCBufGAP_bit                   UARTChannelCBufGAP_bit
#define SPIChannelDBufGAP                       UARTChannelDBufGAP
#define SPIChannelDBufGAP_bit                   UARTChannelDBufGAP_bit
#define SPIChannelBCharGAP                      UARTChannelBCharGAP
#define SPIChannelBCharGAP_bit                  UARTChannelBCharGAP_bit
#define SPIChannelACharGAP                      UARTChannelACharGAP
#define SPIChannelACharGAP_bit                  UARTChannelACharGAP_bit
#define SPIChannelCCharGAP                      UARTChannelCCharGAP
#define SPIChannelCCharGAP_bit                  UARTChannelCCharGAP_bit
#define SPIChannelDCharGAP                      UARTChannelDCharGAP
#define SPIChannelDCharGAP_bit                  UARTChannelDCharGAP_bit
#define SPIChannelBMatch                        UARTChannelBMatch
#define SPIChannelBMatch_bit                    UARTChannelBMatch_bit
#define SPIChannelAMatch                        UARTChannelAMatch
#define SPIChannelAMatch_bit                    UARTChannelAMatch_bit
#define SPIChannelCMatch                        UARTChannelCMatch
#define SPIChannelCMatch_bit                    UARTChannelCMatch_bit
#define SPIChannelDMatch                        UARTChannelDMatch
#define SPIChannelDMatch_bit                    UARTChannelDMatch_bit
#define SPIChannelBMatchMsk                     UARTChannelBMatchMsk
#define SPIChannelBMatchMsk_bit                 UARTChannelBMatchMsk_bit
#define SPIChannelAMatchMsk                     UARTChannelAMatchMsk
#define SPIChannelAMatchMsk_bit                 UARTChannelAMatchMsk_bit
#define SPIChannelCMatchMsk                     UARTChannelCMatchMsk
#define SPIChannelCMatchMsk_bit                 UARTChannelCMatchMsk_bit
#define SPIChannelDMatchMsk                     UARTChannelDMatchMsk
#define SPIChannelDMatchMsk_bit                 UARTChannelDMatchMsk_bit

/***************************************************************************
 **
 ** IEEE 1284 Peripheral Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(NA_PCM_GCR_REG,                  0x90400000, __READ_WRITE, __1284conf_bits  );
__IO_REG32_BIT(NA_PCM_ICSR_REG,                 0x90400004, __READ_WRITE, __1284int_bits   );
__IO_REG32_BIT(NA_PCM_FSR_REG,                  0x90400008, __READ      , __1284fifo_bits  );
__IO_REG32(    NA_PCM_FCFRR_REG,                0x9040000C, __READ                         );
__IO_REG32(    NA_PCM_FDFRR_REG,                0x90400010, __READ                         );
__IO_REG32(    NA_PCM_RDFWR_REG,                0x9040001C, __WRITE                        );
__IO_REG32(    NA_PCM_RDFWLR_REG,               0x90400020, __WRITE                        );
__IO_REG32_BIT(NA_PCM_FCDCR_REG,                0x90400024, __READ_WRITE, __1284dmacmd_bits);
__IO_REG32_BIT(NA_PCM_FDDCR_REG,                0x90400028, __READ_WRITE, __1284dmadat_bits);
__IO_REG32_BIT(NA_PCM_PDPR_REG,                 0x90400100, __READ      , __1284pd_bits    );
__IO_REG32_BIT(NA_PCM_HPSR_REG,                 0x90400104, __READ      , __1284psr_bits   );
__IO_REG32_BIT(NA_PCM_PCR_REG,                  0x90400108, __READ_WRITE, __1284pcr_bits   );
__IO_REG32_BIT(NA_PCM_PPSR_REG,                 0x9040010C, __READ      , __1284pcr_bits   );
__IO_REG32_BIT(NA_PCM_AFCR_REG,                 0x90400114, __READ_WRITE, __1284fea_bits   );
__IO_REG32_BIT(NA_PCM_IER_REG,                  0x9040011c, __READ_WRITE, __1284fei_bits   );
__IO_REG32_BIT(NA_PCM_MER_REG,                  0x90400120, __READ_WRITE, __1284fem_bits   );
__IO_REG32_BIT(NA_PCM_EBRR_REG,                 0x90400124, __READ_WRITE, __1284exr_bits   );
__IO_REG32_BIT(NA_PCM_ECR_REG,                  0x90400128, __READ_WRITE, __1284ecr_bits   );
__IO_REG32_BIT(NA_PCM_ISR_REG,                  0x9040012C, __READ      , __1284sti_bits   );
__IO_REG32_BIT(NA_PCM_PIMR_REG,                 0x90400134, __READ_WRITE, __1284msk_bits   );
__IO_REG32_BIT(NA_PCM_PICR_REG,                 0x90400138, __READ_WRITE, __1284pit_bits   );
__IO_REG32_BIT(NA_PCM_GRCR_REG,                 0x90400168, __READ_WRITE, __1284grn_bits   );
__IO_REG32_BIT(NA_PCM_FAR_REG,                  0x90400174, __READ_WRITE, __1284eca_bits   );
__IO_REG32_BIT(NA_PCM_IPR_REG,                  0x90400178, __READ_WRITE, __1284pha_bits   );

/***************************************************************************
 **
 ** I2C Master/Slave Interface
 **
 ***************************************************************************/
__IO_REG32_BIT(NA_I2C_TX_CMD_DATA_REG,          0x90500000, __READ_WRITE, __i2ctxrx_bits);
#define        NA_I2C_RX_STATUS_DATA_REG        NA_I2C_TX_CMD_DATA_REG
#define        NA_I2C_RX_STATUS_DATA_REG_bit    NA_I2C_TX_CMD_DATA_REG_bit
__IO_REG32_BIT(NA_I2C_MASTER_DEV_REG,           0x90500004, __READ_WRITE, __mda_bits    );
__IO_REG32_BIT(NA_I2C_SLAVE_DEV_REG,            0x90500008, __READ_WRITE, __sla_bits    );
__IO_REG32_BIT(NA_I2C_CONFIG_REG_REG,           0x9050000C, __READ_WRITE, __i2cconf_bits);

/***************************************************************************
 **
 ** BBus Utility Control
 **
 ***************************************************************************/
__IO_REG32_BIT(NA_BUM_MRR_REG,                  0x90600000, __READ_WRITE, __bbusmr_bits      );
__IO_REG32_BIT(NA_BUM_ISR_REG,                  0x90600004, __READ_WRITE, __bbusutint_bits   );
__IO_REG32_BIT(NA_BUM_GCFR01_REG,               0x90600010, __READ_WRITE, __gpio1_bits       );
__IO_REG32_BIT(NA_BUM_GCFR02_REG,               0x90600014, __READ_WRITE, __gpio2_bits       );
__IO_REG32_BIT(NA_BUM_GCFR03_REG,               0x90600018, __READ_WRITE, __gpio3_bits       );
__IO_REG32_BIT(NA_BUM_GCFR04_REG,               0x9060001C, __READ_WRITE, __gpio4_bits       );
__IO_REG32_BIT(NA_BUM_GCFR05_REG,               0x90600020, __READ_WRITE, __gpio5_bits       );
__IO_REG32_BIT(NA_BUM_GCFR06_REG,               0x90600024, __READ_WRITE, __gpio6_bits       );
__IO_REG32_BIT(NA_BUM_GCFR07_REG,               0x90600028, __READ_WRITE, __gpio7_bits       );
__IO_REG32_BIT(NA_BUM_GCR01_REG,                0x90600030, __READ      , __gpioctrl1_bits   );
__IO_REG32_BIT(NA_BUM_GCR02_REG,                0x90600034, __READ      , __gpioctrl2_bits   );
__IO_REG32_BIT(NA_BUM_GSR01_REG,                0x90600040, __READ      , __gpioctrl1_bits   );
__IO_REG32_BIT(NA_BUM_GSR02_REG,                0x90600044, __READ      , __gpioctrl2_bits   );
__IO_REG32_BIT(NA_BUM_BTR_REG,                  0x90600050, __READ_WRITE, __bbustimeout_bits );
__IO_REG32_BIT(NA_BUM_DISR_REG,                 0x90600060, __READ      , __bbusdmaint_bits  );
__IO_REG32_BIT(NA_BUM_DIER_REG,                 0x90600064, __READ_WRITE, __bbusdmainten_bits);
__IO_REG32_BIT(NA_BUM_UCR_REG,                  0x90600070, __READ_WRITE, __usbconf_bits     );
__IO_REG32_BIT(NA_BUM_ECR_REG,                  0x90600080, __READ_WRITE, __endianconf_bits  );
__IO_REG32(    NA_BUM_WAKE_REG,                 0x90600090, __READ_WRITE                     );
__IO_REG32_BIT(NA_BUM_GCFR08_REG,               0x90600100, __READ_WRITE, __gpio8_bits       );
__IO_REG32_BIT(NA_BUM_GCFR09_REG,               0x90600104, __READ_WRITE, __gpio9_bits       );
__IO_REG32_BIT(NA_BUM_GCFR10_REG,               0x90600108, __READ_WRITE, __gpio10_bits      );
__IO_REG32_BIT(NA_BUM_GCR03_REG,                0x90600120, __READ      , __gpioctrl3_bits   );
__IO_REG32_BIT(NA_BUM_GSR03_REG,                0x90600130, __READ      , __gpioctrl3_bits   );

/***************************************************************************
 **
 ** Real Time Clock module
 **
 ***************************************************************************/
__IO_REG32_BIT(RTCGenCtrl,                      0x90700000, __READ_WRITE, __rtcgen_bits       );
__IO_REG32_BIT(_1224Hour,                       0x90700004, __READ_WRITE, __1224_bits         );
__IO_REG32_BIT(Time,                            0x90700008, __READ_WRITE, __time_bits         );
__IO_REG32_BIT(Calendar,                        0x9070000C, __READ_WRITE, __calendar_bits     );
__IO_REG32_BIT(TimeAlarm,                       0x90700010, __READ_WRITE, __time_bits         );
__IO_REG32_BIT(CalendarAlarm,                   0x90700014, __READ_WRITE, __calendaralarm_bits);
__IO_REG32_BIT(AlarmEnable,                     0x90700018, __READ_WRITE, __alarmen_bits      );
__IO_REG32_BIT(EventFlags,                      0x9070001C, __READ      , __eventfl_bits      );
__IO_REG32_BIT(TimeIntEnable,                   0x90700020, __WRITE     , __timeinten_bits    );
__IO_REG32_BIT(TimeIntDisable,                  0x90700024, __WRITE     , __timeintdis_bits   );
__IO_REG32_BIT(TimeIntStatus,                   0x90700028, __READ      , __timeintstat_bits  );
__IO_REG32_BIT(RTCGenStatus,                    0x9070002C, __READ      , __rtcstat_bits      );

/***************************************************************************
 **
 ** USB Host Module
 **
 ***************************************************************************/
__IO_REG32_BIT(UHFECtrlStatus,                  0x90800000, __READ      , __hstrst_bits      );
__IO_REG32_BIT(UHFEIntEnable,                   0x9080000C, __READ_WRITE, __uhfeinten_bits   );
__IO_REG32_BIT(UHFEIntStatus,                   0x90800010, __READ_WRITE, __uhfeinten_bits   );
__IO_REG32_BIT(HcRevision,                      0x90801000, __READ      , __hcrevision_bits  );
__IO_REG32_BIT(HcControl,                       0x90801004, __READ_WRITE, __hccontrol_bits   );
__IO_REG32_BIT(HcCommandStatus,                 0x90801008, __READ_WRITE, __hccommand_bits   );
__IO_REG32_BIT(HcInterruptStatus,               0x9080100C, __READ_WRITE, __hcint_bits       );
__IO_REG32_BIT(HcInterruptEnable,               0x90801010, __READ_WRITE, __hcinten_bits     );
__IO_REG32_BIT(HcInterruptDisable,              0x90801014, __READ_WRITE, __hcinten_bits     );
__IO_REG32_BIT(HcHCCA,                          0x90801018, __READ_WRITE, __hchcca_bits      );
__IO_REG32_BIT(HcPeriodCurrentED,               0x9080101C, __READ      , __hcpced_bits      );
__IO_REG32_BIT(HcControlHeadED,                 0x90801020, __READ_WRITE, __hcched_bits      );
__IO_REG32_BIT(HcControlCurrentED,              0x90801024, __READ_WRITE, __hccced_bits      );
__IO_REG32_BIT(HcBulkHeadED,                    0x90801028, __READ_WRITE, __hcbhed_bits      );
__IO_REG32_BIT(HcBulkCurrentED,                 0x9080102C, __READ_WRITE, __hcbced_bits      );
__IO_REG32_BIT(HcDoneHead,                      0x90801030, __READ      , __hcdh_bits        );
__IO_REG32_BIT(HcFmInterval,                    0x90801034, __READ_WRITE, __hcfmint_bits     );
__IO_REG32_BIT(HcFmRemaining,                   0x90801038, __READ      , __hcfmrem_bits     );
__IO_REG32_BIT(HcFmNumber,                      0x9080103C, __READ      , __hcfmnum_bits     );
__IO_REG32_BIT(HcFmPeriodicStart,               0x90801040, __READ_WRITE, __hcfmper_bits     );
__IO_REG32_BIT(HcLSTreshold,                    0x90801044, __READ_WRITE, __hclst_bits       );
__IO_REG32_BIT(HcRhDescriptorA,                 0x90801048, __READ_WRITE, __hcrhdesca_bits   );
__IO_REG32_BIT(HcRhDescriptorB,                 0x9080104C, __READ_WRITE, __hcrhdescb_bits   );
__IO_REG32_BIT(HcRhStatus,                      0x90801050, __READ_WRITE, __hcrhstat_bits    );
__IO_REG32_BIT(HcRhPortStatus1,                 0x90801054, __READ_WRITE, __hcrhportstat_bits);

/***************************************************************************
 **
 ** USB Device Module
 **
 ***************************************************************************/
__IO_REG32_BIT(NA_USB_GCSR_REG,                 0x90900000, __READ_WRITE, __udfectrl0_bits    );
__IO_REG32_BIT(NA_USB_DCSR_REG,                 0x90900004, __READ_WRITE, __udfectrl1_bits    );
__IO_REG32_BIT(NA_USB_GIE_REG,                  0x9090000C, __READ_WRITE, __udfeinten_bits    );
__IO_REG32_BIT(NA_USB_GIS_REG,                  0x90900010, __READ_WRITE, __udfeintstat_bits  );
__IO_REG32_BIT(UDFEDevCtrlStat,                 0x90900014, __READ_WRITE, __udfectrlstat_bits );
__IO_REG32(    NA_USB_DDSC_REG,                 0x90902000, __READ_WRITE                      );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_0,            0x90902004, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_1,            0x90902008, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_2,            0x9090200C, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_3,            0x90902010, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_4,            0x90902014, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_5,            0x90902018, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_6,            0x9090201C, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_7,            0x90902020, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_8,            0x90902024, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_9,            0x90902028, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_10,           0x9090202C, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_PED_ADDRESS_11,           0x90902030, __READ_WRITE, __phendx_bits       );
__IO_REG32_BIT(NA_USB_FIFOIS_ADDRESS_0,         0x90903000, __READ_WRITE, __fifointstat0_bits );
__IO_REG32_BIT(NA_USB_FIFOIE_ADDRESS_0,         0x90903004, __READ_WRITE, __fifointstat0_bits );
__IO_REG32_BIT(NA_USB_FIFOIS_ADDRESS_1,         0x90903010, __READ_WRITE, __fifointstat1_bits );
__IO_REG32_BIT(NA_USB_FIFOIE_ADDRESS_1,         0x90903014, __READ_WRITE, __fifointstat1_bits );
__IO_REG32_BIT(NA_USB_FIFOIS_ADDRESS_2,         0x90903020, __READ_WRITE, __fifointstat2_bits );
__IO_REG32_BIT(NA_USB_FIFOIE_ADDRESS_2,         0x90903024, __READ_WRITE, __fifointstat2_bits );
__IO_REG32_BIT(NA_USB_FIFOIS_ADDRESS_3,         0x90903030, __READ_WRITE, __fifointstat3_bits );
__IO_REG32_BIT(NA_USB_FIFOIE_ADDRESS_3,         0x90903034, __READ_WRITE, __fifointstat3_bits );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_1,         0x90903080, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_2,         0x90903084, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_3,         0x90903088, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_4,         0x9090308C, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_5,         0x90903090, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_6,         0x90903094, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_7,         0x90903098, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_8,         0x9090309C, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_9,         0x909030A0, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_10,        0x909030A4, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_11,        0x909030A8, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOPC_ADDRESS_12,        0x909030AC, __READ_WRITE, __fifopctrlx_bits   );
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_1,        0x90903100, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_2,        0x90903108, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_3,        0x90903110, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_4,        0x90903118, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_5,        0x90903120, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_6,        0x90903128, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_7,        0x90903130, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_8,        0x90903138, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_9,        0x90903140, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_10,       0x90903148, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_11,       0x90903150, __READ_WRITE, __fifostatctrlx_bits);
__IO_REG32_BIT(NA_USB_FIFOSNC_ADDRESS_12,       0x90903158, __READ_WRITE, __fifostatctrlx_bits);

/***************************************************************************
 **
 ** BBus Bridge
 **
 ***************************************************************************/
__IO_REG32(    NA_BBM_DBDP01,                   0xA0400000, __READ_WRITE                     );
__IO_REG32_BIT(NA_BBM_DCR01,                    0xA0400004, __READ_WRITE, __dmactrl_bits     );
__IO_REG32_BIT(NA_BBM_DSIER01,                  0xA0400008, __READ_WRITE, __dmaint_bits      );
__IO_REG32_BIT(DMAPeripheralCS1,                0xA040000C, __READ_WRITE, __dmaper_bits      );
__IO_REG32(    NA_BBM_DBDP02,                   0xA0400020, __READ_WRITE                     );
__IO_REG32_BIT(NA_BBM_DCR02,                    0xA0400024, __READ_WRITE, __dmactrl_bits     );
__IO_REG32_BIT(NA_BBM_DSIER02,                  0xA0400028, __READ_WRITE, __dmaint_bits      );
__IO_REG32_BIT(DMAPeripheralCS2,                0xA040002C, __READ_WRITE, __dmaper_bits      );
__IO_REG32_BIT(NA_BBM_ISR,                      0xA0401000, __READ      , __bbusint_bits     );
__IO_REG32_BIT(NA_BBM_IER,                      0xA0401004, __READ_WRITE, __bbusinten_bits   );
__IO_REG32_BIT(BBusBridgePrefetch,              0xA0401008, __READ_WRITE, __bbusprefetch_bits);

/***************************************************************************
 **
 ** Ethernet Communication Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(NA_EFE_GCR01_REG,                0xA0600000, __READ_WRITE, __ethgenctrl1_bits      );
__IO_REG32_BIT(NA_EFE_GCR02_REG,                0xA0600004, __READ_WRITE, __ethgenctrl2_bits      );
__IO_REG32_BIT(NA_EFE_GSR_REG,                  0xA0600008, __READ_WRITE, __ethgenstatus_bits     );
__IO_REG32_BIT(NA_EFE_TXSR_REG,                 0xA0600018, __READ      , __ethtransmitstatus_bits);
__IO_REG32_BIT(NA_EFE_RXSR_REG,                 0xA060001C, __READ      , __ethreceivestatus_bits );
__IO_REG32_BIT(NA_EFE_MCR01_REG,                0xA0600400, __READ_WRITE, __ethmacconf1_bits      );
__IO_REG32_BIT(NA_EFE_MCR02_REG,                0xA0600404, __READ_WRITE, __ethmacconf2_bits      );
__IO_REG32_BIT(NA_EFE_BIPGR_REG,                0xA0600408, __READ_WRITE, __ethipgt_bits          );
__IO_REG32_BIT(NA_EFE_NBIPGR_REG,               0xA060040C, __READ_WRITE, __ethipgr_bits          );
__IO_REG32_BIT(NA_EFE_CWRR_REG,                 0xA0600410, __READ_WRITE, __ethcollision_bits     );
__IO_REG32_BIT(NA_EFE_MFR_REG,                  0xA0600414, __READ_WRITE, __ethmaxframe_bits      );
__IO_REG32_BIT(NA_EFE_PSR_REG,                  0xA0600418, __READ_WRITE, __ethphysupport_bits    );
__IO_REG32_BIT(NA_EFE_MMCFGR_REG,               0xA0600420, __READ_WRITE, __ethmiiconfig_bits     );
__IO_REG32_BIT(NA_EFE_MMCMDR_REG,               0xA0600424, __READ_WRITE, __ethmiicommand_bits    );
__IO_REG32_BIT(NA_EFE_MMAR_REG,                 0xA0600428, __READ_WRITE, __ethmiiaddress_bits    );
__IO_REG32_BIT(NA_EFE_MMWDR_REG,                0xA060042C, __READ_WRITE, __ethmiiwritedata_bits  );
__IO_REG32_BIT(NA_EFE_MMRDR_REG,                0xA0600430, __READ      , __ethmiireaddata_bits   );
__IO_REG32_BIT(NA_EFE_MMIR_REG,                 0xA0600434, __READ      , __ethmiiindicators_bits );
__IO_REG32_BIT(NA_EFE_SAR01_REG,                0xA0600440, __READ_WRITE, __ethsa1_bits           );
__IO_REG32_BIT(NA_EFE_SAR02_REG,                0xA0600444, __READ_WRITE, __ethsa2_bits           );
__IO_REG32_BIT(NA_EFE_SAR03_REG,                0xA0600448, __READ_WRITE, __ethsa3_bits           );
__IO_REG32_BIT(NA_EFE_SAFR_REG,                 0xA0600500, __READ_WRITE, __ethsafilter_bits      );
__IO_REG32(NA_EFE_HTR01_REG,                    0xA0600504, __READ_WRITE                          );
__IO_REG32(NA_EFE_HTR02_REG,                    0xA0600508, __READ_WRITE                          );
__IO_REG32_BIT(NA_EFE_TXRX64_REG,               0xA0600680, __READ_WRITE, __tr64_bits             );
__IO_REG32_BIT(NA_EFE_TXRX127_REG,              0xA0600684, __READ_WRITE, __tr127_bits            );
__IO_REG32_BIT(NA_EFE_TXRX255_REG,              0xA0600688, __READ_WRITE, __tr255_bits            );
__IO_REG32_BIT(NA_EFE_TXRX511_REG,              0xA060068C, __READ_WRITE, __tr511_bits            );
__IO_REG32_BIT(NA_EFE_TXRX1023_REG,             0xA0600690, __READ_WRITE, __tr1k_bits             );
__IO_REG32_BIT(NA_EFE_TXRX1518_REG,             0xA0600694, __READ_WRITE, __trmax_bits            );
__IO_REG32_BIT(NA_EFE_TXRX1522_REG,             0xA0600698, __READ_WRITE, __trmgv_bits            );
__IO_REG32_BIT(NA_EFE_RXBC_REG,                 0xA060069C, __READ_WRITE, __rbyt_bits             );
__IO_REG32_BIT(NA_EFE_RXFC_REG,                 0xA06006A0, __READ_WRITE, __rpkt_bits             );
__IO_REG32_BIT(NA_EFE_RXFEC_REG,                0xA06006A4, __READ_WRITE, __rfcs_bits             );
__IO_REG32_BIT(NA_EFE_RXMFC_REG,                0xA06006A8, __READ_WRITE, __rmca_bits             );
__IO_REG32_BIT(NA_EFE_RXBFC_REG,                0xA06006AC, __READ_WRITE, __rbca_bits             );
__IO_REG32_BIT(NA_EFE_RXCFC_REG,                0xA06006B0, __READ_WRITE, __rxcf_bits             );
__IO_REG32_BIT(NA_EFE_RXPFC_REG,                0xA06006B4, __READ_WRITE, __rxpf_bits             );
__IO_REG32_BIT(NA_EFE_RXUOP_REG,                0xA06006B8, __READ_WRITE, __rxuo_bits             );
__IO_REG32_BIT(NA_EFE_RXAEC_REG,                0xA06006BC, __READ_WRITE, __raln_bits             );
__IO_REG32_BIT(NA_EFE_RXCEC_REG,                0xA06006C4, __READ_WRITE, __rcde_bits             );
__IO_REG32_BIT(NA_EFE_RXCSEC_REG,               0xA06006C8, __READ_WRITE, __rcse_bits             );
__IO_REG32_BIT(NA_EFE_RXUFC_REG,                0xA06006CC, __READ_WRITE, __rund_bits             );
__IO_REG32_BIT(NA_EFE_RXOFC_REG,                0xA06006D0, __READ_WRITE, __rovr_bits             );
__IO_REG32_BIT(NA_EFE_RXFFC_REG,                0xA06006D4, __READ_WRITE, __rfrg_bits             );
__IO_REG32_BIT(NA_EFE_RXJFC_REG,                0xA06006D8, __READ_WRITE, __rjbr_bits             );
__IO_REG32_BIT(NA_EFE_TXBC_REG,                 0xA06006E0, __READ_WRITE, __tbyt_bits             );
__IO_REG32_BIT(NA_EFE_TXFC_REG,                 0xA06006E4, __READ_WRITE, __tpkt_bits             );
__IO_REG32_BIT(NA_EFE_TXMFC_REG,                0xA06006E8, __READ_WRITE, __tmca_bits             );
__IO_REG32_BIT(NA_EFE_TXBFC_REG,                0xA06006EC, __READ_WRITE, __tbca_bits             );
__IO_REG32_BIT(NA_EFE_TXDEFC_REG,               0xA06006F4, __READ_WRITE, __tdfr_bits             );
__IO_REG32_BIT(NA_EFE_TXEDFC_REG,               0xA06006F8, __READ_WRITE, __tedf_bits             );
__IO_REG32_BIT(NA_EFE_TXSCFC_REG,               0xA06006FC, __READ_WRITE, __tscl_bits             );
__IO_REG32_BIT(NA_EFE_TXMCFC_REG,               0xA0600700, __READ_WRITE, __tmcl_bits             );
__IO_REG32_BIT(NA_EFE_TXLCFC_REG,               0xA0600704, __READ_WRITE, __tlcl_bits             );
__IO_REG32_BIT(NA_EFE_TXECC_REG,                0xA0600708, __READ_WRITE, __txcl_bits             );
__IO_REG32_BIT(NA_EFE_TXTCC_REG,                0xA060070C, __READ_WRITE, __tncl_bits             );
__IO_REG32_BIT(NA_EFE_TXJFC_REG,                0xA0600718, __READ_WRITE, __tjbr_bits             );
__IO_REG32_BIT(NA_EFE_TXFEC_REG,                0xA060071C, __READ_WRITE, __tfcs_bits             );
__IO_REG32_BIT(NA_EFE_TXOFC_REG,                0xA0600724, __READ_WRITE, __tovr_bits             );
__IO_REG32_BIT(NA_EFE_TXUFC_REG,                0xA0600728, __READ_WRITE, __tund_bits             );
__IO_REG32_BIT(NA_EFE_TXFFC_REG,                0xA060072C, __READ_WRITE, __tfrg_bits             );
__IO_REG32_BIT(CAR1,                            0xA0600730, __READ_WRITE, __ethcarry1_bits        );
__IO_REG32_BIT(CAR2,                            0xA0600734, __READ_WRITE, __ethcarry2_bits        );
__IO_REG32_BIT(CAM1,                            0xA0600738, __READ_WRITE, __ethcarrymask1_bits    );
__IO_REG32_BIT(CAM2,                            0xA060073C, __READ_WRITE, __ethcarrymask2_bits    );
__IO_REG32(RXAPTR,                              0xA0600A00, __READ_WRITE                          );
__IO_REG32(RXBPTR,                              0xA0600A04, __READ_WRITE                          );
__IO_REG32(RXCPTR,                              0xA0600A08, __READ_WRITE                          );
__IO_REG32(RXDPTR,                              0xA0600A0C, __READ_WRITE                          );
__IO_REG32_BIT(EINTR,                           0xA0600A10, __READ_WRITE, __ethintstatus_bits     );
__IO_REG32_BIT(EINTREN,                         0xA0600A14, __READ_WRITE, __ethintenable_bits     );
__IO_REG32_BIT(TXPTR,                           0xA0600A18, __READ_WRITE, __txptr_bits            );
__IO_REG32_BIT(TXRPTR,                          0xA0600A1C, __READ_WRITE, __txrptr_bits           );
__IO_REG32_BIT(TXERBD,                          0xA0600A20, __READ      , __txerbd_bits           );
__IO_REG32_BIT(TXSPTR,                          0xA0600A24, __READ      , __txsptr_bits           );
__IO_REG32_BIT(RXAOFF,                          0xA0600A28, __READ      , __rxaoff_bits           );
__IO_REG32_BIT(RXBOFF,                          0xA0600A2C, __READ      , __rxboff_bits           );
__IO_REG32_BIT(RXCOFF,                          0xA0600A30, __READ      , __rxcoff_bits           );
__IO_REG32_BIT(RXDOFF,                          0xA0600A34, __READ      , __rxdoff_bits           );
__IO_REG32_BIT(TXOFF,                           0xA0600A38, __READ      , __txoff_bits            );
__IO_REG32_BIT(RXFREE,                          0xA0600A3C, __WRITE     , __rxfree_bits           );

/***************************************************************************
 **
 ** Memory Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(NA_MPMCControl_REG,                  0xA0700000, __READ_WRITE, __controlregister_bits        );
__IO_REG32_BIT(NA_MPMCStatus_REG,                   0xA0700004, __READ      , __statusregister_bits         );
__IO_REG32_BIT(NA_MPMCConfig_REG,                   0xA0700008, __READ_WRITE, __configurationregister_bits  );
__IO_REG32_BIT(NA_MPMCDynamicControl_REG,           0xA0700020, __READ_WRITE, __dynamicmemorycontrol_bits   );
__IO_REG32_BIT(NA_MPMCDynamicRefresh_REG,           0xA0700024, __READ_WRITE, __dynamicmemoryrefresh_bits   );
__IO_REG32_BIT(NA_MPMCDynamicReadConfig_REG,        0xA0700028, __READ_WRITE, __dynamicmemoryreadconfig_bits);
__IO_REG32_BIT(NA_MPMCDynamictRP_REG,               0xA0700030, __READ_WRITE, __dynamicmemoryprecharge_bits );
__IO_REG32_BIT(NA_MPMCDynamictRAS_REG,              0xA0700034, __READ_WRITE, __dynamicmemoryras_bits       );
__IO_REG32_BIT(NA_MPMCDynamictSREX_REG,             0xA0700038, __READ_WRITE, __dynamicmemorysrex_bits      );
__IO_REG32_BIT(NA_MPMCDynamictAPR_REG,              0xA070003C, __READ_WRITE, __dynamicmemoryapr_bits       );
__IO_REG32_BIT(NA_MPMCDynamictDAL_REG,              0xA0700040, __READ_WRITE, __dynamicmemorydal_bits       );
__IO_REG32_BIT(NA_MPMCDynamictWR_REG,               0xA0700044, __READ_WRITE, __dynamicmemorywr_bits        );
__IO_REG32_BIT(NA_MPMCDynamictRC_REG,               0xA0700048, __READ_WRITE, __dynamicmemoryrc_bits        );
__IO_REG32_BIT(NA_MPMCDynamictRFC_REG,              0xA070004C, __READ_WRITE, __dynamicmemoryrfc_bits       );
__IO_REG32_BIT(NA_MPMCDynamictXSR_REG,              0xA0700050, __READ_WRITE, __dynamicmemoryxsr_bits       );
__IO_REG32_BIT(NA_MPMCDynamictRRD_REG,              0xA0700054, __READ_WRITE, __dynamicmemoryrrd_bits       );
__IO_REG32_BIT(NA_MPMCDynamictMRD_REG,              0xA0700058, __READ_WRITE, __dynamicmemorymrd_bits       );
__IO_REG32_BIT(NA_MPMCStaticExtendedWait_REG,       0xA0700080, __READ_WRITE, __staticmemoryext_bits        );
__IO_REG32_BIT(NA_MPMCDynamicConfig0_REG,           0xA0700100, __READ_WRITE, __dynamicmemoryconfig_bits    );
__IO_REG32_BIT(NA_MPMCDynamicRasCas0_REG,           0xA0700104, __READ_WRITE, __dynamicmemoryrascas_bits    );
__IO_REG32_BIT(NA_MPMCDynamicConfig1_REG,           0xA0700120, __READ_WRITE, __dynamicmemoryconfig_bits    );
__IO_REG32_BIT(NA_MPMCDynamicRasCas1_REG,           0xA0700124, __READ_WRITE, __dynamicmemoryrascas_bits    );
__IO_REG32_BIT(NA_MPMCDynamicConfig2_REG,           0xA0700140, __READ_WRITE, __dynamicmemoryconfig_bits    );
__IO_REG32_BIT(NA_MPMCDynamicRasCas2_REG,           0xA0700144, __READ_WRITE, __dynamicmemoryrascas_bits    );
__IO_REG32_BIT(NA_MPMCDynamicConfig3_REG,           0xA0700160, __READ_WRITE, __dynamicmemoryconfig_bits    );
__IO_REG32_BIT(NA_MPMCDynamicRasCas3_REG,           0xA0700164, __READ_WRITE, __dynamicmemoryrascas_bits    );
__IO_REG32_BIT(NA_MPMCStaticConfig0_REG,            0xA0700200, __READ_WRITE, __staticmemoryconfig_bits     );
__IO_REG32_BIT(NA_MPMCStaticWaitWen0_REG,           0xA0700204, __READ_WRITE, __staticmemorywriteen_bits    );
__IO_REG32_BIT(NA_MPMCStaticWaitOen0_REG,           0xA0700208, __READ_WRITE, __staticmemoryoen_bits        );
__IO_REG32_BIT(NA_MPMCStaticWaitRd0_REG,            0xA070020C, __READ_WRITE, __staticmemoryread_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitPage0_REG,          0xA0700210, __READ_WRITE, __staticmemorypage_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitWr0_REG,            0xA0700214, __READ_WRITE, __staticmemorywrite_bits      );
__IO_REG32_BIT(NA_MPMCStaticWaitTurn0_REG,          0xA0700218, __READ_WRITE, __staticmemoryturn_bits       );
__IO_REG32_BIT(NA_MPMCStaticConfig1_REG,            0xA0700220, __READ_WRITE, __staticmemoryconfig_bits     );
__IO_REG32_BIT(NA_MPMCStaticWaitWen1_REG,           0xA0700224, __READ_WRITE, __staticmemorywriteen_bits    );
__IO_REG32_BIT(NA_MPMCStaticWaitOen1_REG,           0xA0700228, __READ_WRITE, __staticmemoryoen_bits        );
__IO_REG32_BIT(NA_MPMCStaticWaitRd1_REG,            0xA070022C, __READ_WRITE, __staticmemoryread_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitPage1_REG,          0xA0700230, __READ_WRITE, __staticmemorypage_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitWr1_REG,            0xA0700234, __READ_WRITE, __staticmemorywrite_bits      );
__IO_REG32_BIT(NA_MPMCStaticWaitTurn1_REG,          0xA0700238, __READ_WRITE, __staticmemoryturn_bits       );
__IO_REG32_BIT(NA_MPMCStaticConfig2_REG,            0xA0700240, __READ_WRITE, __staticmemoryconfig_bits     );
__IO_REG32_BIT(NA_MPMCStaticWaitWen2_REG,           0xA0700244, __READ_WRITE, __staticmemorywriteen_bits    );
__IO_REG32_BIT(NA_MPMCStaticWaitOen2_REG,           0xA0700248, __READ_WRITE, __staticmemoryoen_bits        );
__IO_REG32_BIT(NA_MPMCStaticWaitRd2_REG,            0xA070024C, __READ_WRITE, __staticmemoryread_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitPage2_REG,          0xA0700250, __READ_WRITE, __staticmemorypage_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitWr2_REG,            0xA0700254, __READ_WRITE, __staticmemorywrite_bits      );
__IO_REG32_BIT(NA_MPMCStaticWaitTurn2_REG,          0xA0700258, __READ_WRITE, __staticmemoryturn_bits       );
__IO_REG32_BIT(NA_MPMCStaticConfig3_REG,            0xA0700260, __READ_WRITE, __staticmemoryconfig_bits     );
__IO_REG32_BIT(NA_MPMCStaticWaitWen3_REG,           0xA0700264, __READ_WRITE, __staticmemorywriteen_bits    );
__IO_REG32_BIT(NA_MPMCStaticWaitOen3_REG,           0xA0700268, __READ_WRITE, __staticmemoryoen_bits        );
__IO_REG32_BIT(NA_MPMCStaticWaitRd3_REG,            0xA070026C, __READ_WRITE, __staticmemoryread_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitPage3_REG,          0xA0700270, __READ_WRITE, __staticmemorypage_bits       );
__IO_REG32_BIT(NA_MPMCStaticWaitWr3_REG,            0xA0700274, __READ_WRITE, __staticmemorywrite_bits      );
__IO_REG32_BIT(NA_MPMCStaticWaitTurn3_REG,          0xA0700278, __READ_WRITE, __staticmemoryturn_bits       );

/***************************************************************************
 **
 ** LCD Controller
 **
 ***************************************************************************/
__IO_REG32_BIT(LCDTiming0,                          0xA0800000, __READ_WRITE, __lcdtm0_bits       );
__IO_REG32_BIT(LCDTiming1,                          0xA0800004, __READ_WRITE, __lcdtm1_bits       );
__IO_REG32_BIT(LCDTiming2,                          0xA0800008, __READ_WRITE, __lcdtm2_bits       );
__IO_REG32_BIT(LCDTiming3,                          0xA080000C, __READ_WRITE, __lcdtm3_bits       );
__IO_REG32_BIT(LCDUPBASE,                           0xA0800010, __READ_WRITE, __lcdupbase_bits    );
__IO_REG32_BIT(LCDLPBASE,                           0xA0800014, __READ_WRITE, __lcdlpbase_bits    );
__IO_REG32_BIT(LCDINTRENABBLE,                      0xA0800018, __READ_WRITE, __lcdintrenable_bits);
__IO_REG32_BIT(LCDControl,                          0xA080001C, __READ_WRITE, __lcdctrl_bits      );
__IO_REG32_BIT(LCDStatus,                           0xA0800020, __READ_WRITE, __lcdstatus_bits    );
__IO_REG32_BIT(LCDInterrupt,                        0xA0800024, __READ, __lcdint_bits             );
__IO_REG32(    LCDUPCURR,                              0xA0800028, __READ                         );
__IO_REG32(    LCDLPCURR,                              0xA080002C, __READ                         );
__IO_REG32_BIT(LCDPalette0,                         0xA0800200, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette1,                         0xA0800204, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette2,                         0xA0800208, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette3,                         0xA080020C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette4,                         0xA0800210, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette5,                         0xA0800214, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette6,                         0xA0800218, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette7,                         0xA080021C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette8,                         0xA0800220, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette9,                         0xA0800224, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette10,                        0xA0800228, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette11,                        0xA080022C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette12,                        0xA0800230, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette13,                        0xA0800234, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette14,                        0xA0800238, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette15,                        0xA080023C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette16,                        0xA0800240, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette17,                        0xA0800244, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette18,                        0xA0800248, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette19,                        0xA080024C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette20,                        0xA0800250, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette21,                        0xA0800254, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette22,                        0xA0800258, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette23,                        0xA080025C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette24,                        0xA0800260, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette25,                        0xA0800264, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette26,                        0xA0800268, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette27,                        0xA080026C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette28,                        0xA0800270, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette29,                        0xA0800274, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette30,                        0xA0800278, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette31,                        0xA080027C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette32,                        0xA0800280, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette33,                        0xA0800284, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette34,                        0xA0800288, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette35,                        0xA080028C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette36,                        0xA0800290, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette37,                        0xA0800294, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette38,                        0xA0800298, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette39,                        0xA080029C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette40,                        0xA08002A0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette41,                        0xA08002A4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette42,                        0xA08002A8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette43,                        0xA08002AC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette44,                        0xA08002B0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette45,                        0xA08002B4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette46,                        0xA08002B8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette47,                        0xA08002BC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette48,                        0xA08002C0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette49,                        0xA08002C4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette50,                        0xA08002C8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette51,                        0xA08002CC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette52,                        0xA08002D0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette53,                        0xA08002D4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette54,                        0xA08002D8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette55,                        0xA08002DC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette56,                        0xA08002E0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette57,                        0xA08002E4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette58,                        0xA08002E8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette59,                        0xA08002EC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette60,                        0xA08002F0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette61,                        0xA08002F4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette62,                        0xA08002F8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette63,                        0xA08002FC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette64,                        0xA0800300, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette65,                        0xA0800304, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette66,                        0xA0800308, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette67,                        0xA080030C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette68,                        0xA0800310, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette69,                        0xA0800314, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette70,                        0xA0800318, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette71,                        0xA080031C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette72,                        0xA0800320, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette73,                        0xA0800324, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette74,                        0xA0800328, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette75,                        0xA080032C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette76,                        0xA0800330, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette77,                        0xA0800334, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette78,                        0xA0800338, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette79,                        0xA080033C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette80,                        0xA0800340, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette81,                        0xA0800344, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette82,                        0xA0800348, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette83,                        0xA080034C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette84,                        0xA0800350, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette85,                        0xA0800354, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette86,                        0xA0800358, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette87,                        0xA080035C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette88,                        0xA0800360, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette89,                        0xA0800364, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette90,                        0xA0800368, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette91,                        0xA080036C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette92,                        0xA0800370, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette93,                        0xA0800374, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette94,                        0xA0800378, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette95,                        0xA080037C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette96,                        0xA0800380, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette97,                        0xA0800384, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette98,                        0xA0800388, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette99,                        0xA080038C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette100,                       0xA0800390, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette101,                       0xA0800394, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette102,                       0xA0800398, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette103,                       0xA080039C, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette104,                       0xA08003A0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette105,                       0xA08003A4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette106,                       0xA08003A8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette107,                       0xA08003AC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette108,                       0xA08003B0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette109,                       0xA08003B4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette110,                       0xA08003B8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette111,                       0xA08003BC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette112,                       0xA08003C0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette113,                       0xA08003C4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette114,                       0xA08003C8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette115,                       0xA08003CC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette116,                       0xA08003D0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette117,                       0xA08003D4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette118,                       0xA08003D8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette119,                       0xA08003DC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette120,                       0xA08003E0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette121,                       0xA08003E4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette122,                       0xA08003E8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette123,                       0xA08003EC, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette124,                       0xA08003F0, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette125,                       0xA08003F4, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette126,                       0xA08003F8, __READ_WRITE, __lcdpalette_bits   );
__IO_REG32_BIT(LCDPalette127,                       0xA08003FC, __READ_WRITE, __lcdpalette_bits   );

/***************************************************************************
 **
 ** System Control Module
 **
 ***************************************************************************/
__IO_REG32_BIT(NA_SCM_AAGCR_REG,                    0xA0900000, __READ_WRITE, __ahbconf_bits             );
__IO_REG32_BIT(NA_SCM_BRCR0_REG,                    0xA0900004, __READ_WRITE, __brc0_bits                );
__IO_REG32_BIT(NA_SCM_BRCR1_REG,                    0xA0900008, __READ_WRITE, __brc1_bits                );
__IO_REG32_BIT(NA_SCM_BRCR2_REG,                    0xA090000C, __READ_WRITE, __brc2_bits                );
__IO_REG32_BIT(NA_SCM_BRCR3_REG,                    0xA0900010, __READ_WRITE, __brc3_bits                );
__IO_REG32(    NA_SCM_TRCR00_REG,                   0xA0900044, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRCR01_REG,                   0xA0900048, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRCR02_REG,                   0xA090004C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRCR03_REG,                   0xA0900050, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRCR04_REG,                   0xA0900054, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRCR05_REG,                   0xA0900058, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRCR06_REG,                   0xA090005C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRCR07_REG,                   0xA0900060, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR00_REG,                    0xA0900084, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR01_REG,                    0xA0900088, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR02_REG,                    0xA090008C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR03_REG,                    0xA0900090, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR04_REG,                    0xA0900094, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR05_REG,                    0xA0900098, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR06_REG,                    0xA090009C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_TRR07_REG,                    0xA09000A0, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR00_REG,                   0xA09000C4, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR01_REG,                   0xA09000C8, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR02_REG,                   0xA09000CC, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR03_REG,                   0xA09000D0, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR04_REG,                   0xA09000D4, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR05_REG,                   0xA09000D8, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR06_REG,                   0xA09000DC, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR07_REG,                   0xA09000E0, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR08_REG,                   0xA09000E4, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR09_REG,                   0xA09000E8, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR10_REG,                   0xA09000EC, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR11_REG,                   0xA09000F0, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR12_REG,                   0xA09000F4, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR13_REG,                   0xA09000F8, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR14_REG,                   0xA09000FC, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR15_REG,                   0xA0900100, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR16_REG,                   0xA0900104, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR17_REG,                   0xA0900108, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR18_REG,                   0xA090010C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR19_REG,                   0xA0900110, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR20_REG,                   0xA0900114, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR21_REG,                   0xA0900118, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR22_REG,                   0xA090011C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR23_REG,                   0xA0900120, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR24_REG,                   0xA0900124, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR25_REG,                   0xA0900128, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR26_REG,                   0xA090012C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR27_REG,                   0xA0900130, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR28_REG,                   0xA0900134, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR29_REG,                   0xA0900138, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR30_REG,                   0xA090013C, __READ_WRITE                             );
__IO_REG32(    NA_SCM_IVAR31_REG,                   0xA0900140, __READ_WRITE                             );
__IO_REG32_BIT(NA_SCM_ICR00_REG,                    0xA0900144, __READ_WRITE, __intconfig0_bits          );
#define        NA_SCM_ICR01_REG                     NA_SCM_ICR00_REG    
#define        NA_SCM_ICR01_REG_bit                 NA_SCM_ICR00_REG_bit     
#define        NA_SCM_ICR02_REG                     NA_SCM_ICR00_REG    
#define        NA_SCM_ICR02_REG_bit                 NA_SCM_ICR00_REG_bit     
#define        NA_SCM_ICR03_REG                     NA_SCM_ICR00_REG    
#define        NA_SCM_ICR03_REG_bit                 NA_SCM_ICR00_REG_bit     
__IO_REG32_BIT(NA_SCM_ICR04_REG,                    0xA0900148, __READ_WRITE, __intconfig1_bits          );
#define        NA_SCM_ICR05_REG                     NA_SCM_ICR04_REG    
#define        NA_SCM_ICR05_REG_bit                 NA_SCM_ICR04_REG_bit     
#define        NA_SCM_ICR06_REG                     NA_SCM_ICR04_REG    
#define        NA_SCM_ICR06_REG_bit                 NA_SCM_ICR04_REG_bit     
#define        NA_SCM_ICR07_REG                     NA_SCM_ICR04_REG    
#define        NA_SCM_ICR07_REG_bit                 NA_SCM_ICR04_REG_bit     
__IO_REG32_BIT(NA_SCM_ICR08_REG,                    0xA090014C, __READ_WRITE, __intconfig2_bits          );
#define        NA_SCM_ICR09_REG                     NA_SCM_ICR08_REG    
#define        NA_SCM_ICR09_REG_bit                 NA_SCM_ICR08_REG_bit     
#define        NA_SCM_ICR10_REG                     NA_SCM_ICR08_REG    
#define        NA_SCM_ICR10_REG_bit                 NA_SCM_ICR08_REG_bit     
#define        NA_SCM_ICR11_REG                     NA_SCM_ICR08_REG    
#define        NA_SCM_ICR11_REG_bit                 NA_SCM_ICR08_REG_bit     
__IO_REG32_BIT(NA_SCM_ICR12_REG,                    0xA0900150, __READ_WRITE, __intconfig3_bits          );
#define        NA_SCM_ICR13_REG                     NA_SCM_ICR12_REG    
#define        NA_SCM_ICR13_REG_bit                 NA_SCM_ICR12_REG_bit     
#define        NA_SCM_ICR14_REG                     NA_SCM_ICR12_REG    
#define        NA_SCM_ICR14_REG_bit                 NA_SCM_ICR12_REG_bit     
#define        NA_SCM_ICR15_REG                     NA_SCM_ICR12_REG    
#define        NA_SCM_ICR15_REG_bit                 NA_SCM_ICR12_REG_bit     
__IO_REG32_BIT(NA_SCM_ICR16_REG,                    0xA0900154, __READ_WRITE, __intconfig4_bits          );
#define        NA_SCM_ICR17_REG                     NA_SCM_ICR16_REG    
#define        NA_SCM_ICR17_REG_bit                 NA_SCM_ICR16_REG_bit     
#define        NA_SCM_ICR18_REG                     NA_SCM_ICR16_REG    
#define        NA_SCM_ICR18_REG_bit                 NA_SCM_ICR16_REG_bit     
#define        NA_SCM_ICR19_REG                     NA_SCM_ICR16_REG    
#define        NA_SCM_ICR19_REG_bit                 NA_SCM_ICR16_REG_bit     
__IO_REG32_BIT(NA_SCM_ICR20_REG,                    0xA0900158, __READ_WRITE, __intconfig5_bits          );
#define        NA_SCM_ICR21_REG                     NA_SCM_ICR20_REG    
#define        NA_SCM_ICR21_REG_bit                 NA_SCM_ICR20_REG_bit     
#define        NA_SCM_ICR22_REG                     NA_SCM_ICR20_REG    
#define        NA_SCM_ICR22_REG_bit                 NA_SCM_ICR20_REG_bit     
#define        NA_SCM_ICR23_REG                     NA_SCM_ICR20_REG    
#define        NA_SCM_ICR23_REG_bit                 NA_SCM_ICR20_REG_bit     
__IO_REG32_BIT(NA_SCM_ICR24_REG,                    0xA090015C, __READ_WRITE, __intconfig6_bits          );
#define        NA_SCM_ICR25_REG                     NA_SCM_ICR24_REG    
#define        NA_SCM_ICR25_REG_bit                 NA_SCM_ICR24_REG_bit     
#define        NA_SCM_ICR26_REG                     NA_SCM_ICR24_REG    
#define        NA_SCM_ICR26_REG_bit                 NA_SCM_ICR24_REG_bit     
#define        NA_SCM_ICR27_REG                     NA_SCM_ICR24_REG    
#define        NA_SCM_ICR27_REG_bit                 NA_SCM_ICR24_REG_bit     
__IO_REG32_BIT(NA_SCM_ICR28_REG,                    0xA0900160, __READ_WRITE, __intconfig7_bits          );
#define        NA_SCM_ICR29_REG                     NA_SCM_ICR28_REG    
#define        NA_SCM_ICR29_REG_bit                 NA_SCM_ICR28_REG_bit     
#define        NA_SCM_ICR30_REG                     NA_SCM_ICR28_REG    
#define        NA_SCM_ICR30_REG_bit                 NA_SCM_ICR28_REG_bit     
#define        NA_SCM_ICR31_REG                     NA_SCM_ICR28_REG    
#define        NA_SCM_ICR31_REG_bit                 NA_SCM_ICR28_REG_bit     
__IO_REG32(    NA_SCM_ISRR_REG,                     0xA0900164, __READ_WRITE                             );
__IO_REG32(    NA_SCM_ISAR_REG,                     0xA0900168, __READ                                   );
__IO_REG32(    NA_SCM_ISRAWR_REG,                   0xA090016C, __READ                                   );
__IO_REG32_BIT(NA_SCM_TISR_REG,                     0xA0900170, __READ      , __timintstatus_bits        );
__IO_REG32_BIT(NA_SCM_SWCR_REG,                     0xA0900174, __READ_WRITE, __swwdconfig_bits          );
__IO_REG32(    NA_SCM_SWTR_REG,                     0xA0900178, __READ_WRITE                             );
__IO_REG32_BIT(NA_SCM_CCR_REG,                      0xA090017C, __READ_WRITE, __clockconfig_bits         );
__IO_REG32_BIT(NA_SCM_RSR_REG,                      0xA0900180, __READ_WRITE, __rsslctrl_bits            );
__IO_REG32_BIT(NA_SCM_MSCSR_REG,                    0xA0900184, __READ_WRITE, __miscsysstatus_bits       );
__IO_REG32_BIT(NA_SCM_PLL_REG,                      0xA0900188, __READ_WRITE, __pllconfig_bits           );
__IO_REG32_BIT(NA_SCM_ILISR_REG,                    0xA090018C, __READ      , __activeintlvlstatus_bits  );
__IO_REG32_BIT(NA_SCM_TCR00_REG,                    0xA0900190, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_TCR01_REG,                    0xA0900194, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_TCR02_REG,                    0xA0900198, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_TCR03_REG,                    0xA090019C, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_TCR04_REG,                    0xA09001A0, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_TCR05_REG,                    0xA09001A4, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_TCR06_REG,                    0xA09001A8, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_TCR07_REG,                    0xA09001AC, __READ_WRITE, __timercontrol_bits        );
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_BASE_0,      0xA09001D0, __READ_WRITE, __systemmemselect0base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_MASK_0,      0xA09001D4, __READ_WRITE, __systemmemselect0mask_bits);
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_BASE_1,      0xA09001D8, __READ_WRITE, __systemmemselect1base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_MASK_1,      0xA09001DC, __READ_WRITE, __systemmemselect1mask_bits);
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_BASE_2,      0xA09001E0, __READ_WRITE, __systemmemselect2base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_MASK_2,      0xA09001E4, __READ_WRITE, __systemmemselect2mask_bits);
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_BASE_3,      0xA09001E8, __READ_WRITE, __systemmemselect3base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_DYNAMIC_MEM_MASK_3,      0xA09001EC, __READ_WRITE, __systemmemselect3mask_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_BASE_0,       0xA09001F0, __READ_WRITE, __systemmemselect0base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_MASK_0,       0xA09001F4, __READ_WRITE, __systemmemselect0mask_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_BASE_1,       0xA09001F8, __READ_WRITE, __systemmemselect1base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_MASK_1,       0xA09001FC, __READ_WRITE, __systemmemselect1mask_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_BASE_2,       0xA0900200, __READ_WRITE, __systemmemselect2base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_MASK_2,       0xA0900204, __READ_WRITE, __systemmemselect2mask_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_BASE_3,       0xA0900208, __READ_WRITE, __systemmemselect3base_bits);
__IO_REG32_BIT(NA_SCM_SMCS_STATIC_MEM_MASK_3,       0xA090020C, __READ_WRITE, __systemmemselect3mask_bits);
__IO_REG32(    GENID,                               0xA0900210, __READ                                   );
__IO_REG32_BIT(NA_SCM_EICR_0_REG,                   0xA0900214, __READ_WRITE, __extinterruptcontrol_bits );
__IO_REG32_BIT(NA_SCM_EICR_1_REG,                   0xA0900218, __READ_WRITE, __extinterruptcontrol_bits );
__IO_REG32_BIT(NA_SCM_EICR_2_REG,                   0xA090021C, __READ_WRITE, __extinterruptcontrol_bits );
__IO_REG32_BIT(NA_SCM_EICR_3_REG,                   0xA0900220, __READ_WRITE, __extinterruptcontrol_bits );
__IO_REG32(    RTCCLK,                              0xA0900224, __READ_WRITE                             );

/* Assembler-specific declarations  ****************************************/

#ifdef __IAR_SYSTEMS_ASM__

#endif    /* __IAR_SYSTEMS_ASM__ */

/***************************************************************************
 **
 ** NS9360 Interrupt Codes
 **
 ***************************************************************************/
#define SCM_WATCHDOG_INTERRUPT              0
#define SCM_AHB_BUS_ERROR_INTERRUPT         1
#define SCM_BBUS_AGGREGATE_INTERRUPT        2
#define SCM_RESERVED1_INTERRUPT             3
#define SCM_ETH_RECEIVE_INTERRUPT           4
#define SCM_ETH_TRANSMIT_INTERRUPT          5
#define SCM_ETH_PHY_INTERRUPT               6
#define SCM_LCD_INTERRUPT                   7
#define SCM_SER1RX_INTERRUPT                8
#define SCM_SER1TX_INTERRUPT                9
#define SCM_SER2RX_INTERRUPT                10
#define SCM_SER2TX_INTERRUPT                11
#define SCM_SER3RX_INTERRUPT                12
#define SCM_SER3TX_INTERRUPT                13
#define SCM_I2C_INTERRUPT                   14
#define SCM_BBUS_DMA_INTERRUPT              15
#define SCM_TIMER0_INTERRUPT                16
#define SCM_TIMER1_INTERRUPT                17
#define SCM_TIMER2_INTERRUPT                18
#define SCM_TIMER3_INTERRUPT                19
#define SCM_TIMER4_INTERRUPT                20
#define SCM_TIMER5_INTERRUPT                21
#define SCM_TIMER6_INTERRUPT                22
#define SCM_TIMER7_INTERRUPT                23
#define SCM_RTC_INTERRUPT                   24
#define SCM_USB_HOST_INTERRUPT              25
#define SCM_USB_DEVICE_INTERRUPT            26
#define SCM_IEEE_1284_INTERRUPT             27
#define SCM_EXTERNAL0_INTERRUPT             28
#define SCM_EXTERNAL1_INTERRUPT             29
#define SCM_EXTERNAL2_INTERRUPT             30
#define SCM_EXTERNAL3_INTERRUPT             31


#endif	/* __IONS9360_H */

