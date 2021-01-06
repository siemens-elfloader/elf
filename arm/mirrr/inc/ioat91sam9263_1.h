// - ----------------------------------------------------------------------------
// -          ATMEL Microcontroller Software Support  -  ROUSSET  -
// - ----------------------------------------------------------------------------
// -  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
// -  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// -  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
// -  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
// -  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// -  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// -  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// -  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// -  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// -  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// - ----------------------------------------------------------------------------
// - File Name           : AT91SAM9263.h
// - Object              : AT91SAM9263 definitions
// - Generated           : AT91 SW Application Group  12/07/2006 (13:13:31)
// - 
// - CVS Reference       : /AT91SAM9263.pl/1.2/Fri Nov 10 12:56:00 2006//
// - CVS Reference       : /SYS_SAM9262.pl/1.4/Tue Jan 18 17:06:33 2005//
// - CVS Reference       : /HMATRIX1_SAM9262.pl/1.10/Thu Oct 13 12:44:26 2005//
// - CVS Reference       : /CCR_SAM9262.pl/1.7/Fri Nov 10 13:23:00 2006//
// - CVS Reference       : /PMC_SAM9262.pl/1.4/Mon Mar  7 18:03:13 2005//
// - CVS Reference       : /HSDRAMC1_6100A.pl/1.2/Mon Aug  9 10:52:25 2004//
// - CVS Reference       : /HSMC3_6105A.pl/1.4/Tue Nov 16 09:16:23 2004//
// - CVS Reference       : /AIC_6075B.pl/1.3/Fri May 20 14:21:42 2005//
// - CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 09:02:11 2005//
// - CVS Reference       : /DBGU_6059D.pl/1.1/Mon Jan 31 13:54:41 2005//
// - CVS Reference       : /PIO_6057A.pl/1.2/Thu Feb  3 10:29:42 2005//
// - CVS Reference       : /RSTC_6098A.pl/1.3/Thu Nov  4 13:57:00 2004//
// - CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct  6 14:16:58 2004//
// - CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov  4 13:57:22 2004//
// - CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov  4 13:56:22 2004//
// - CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov  4 13:58:52 2004//
// - CVS Reference       : /TC_6082A.pl/1.7/Wed Mar  9 16:31:51 2005//
// - CVS Reference       : /MCI_6101E.pl/1.1/Fri Jun  3 13:20:23 2005//
// - CVS Reference       : /TWI_6061A.pl/1.2/Wed Oct 25 15:03:34 2006//
// - CVS Reference       : /US_6089C.pl/1.1/Mon Jan 31 13:56:02 2005//
// - CVS Reference       : /SSC_6078B.pl/1.1/Wed Jul 13 15:25:46 2005//
// - CVS Reference       : /SPI_6088D.pl/1.3/Fri May 20 14:23:02 2005//
// - CVS Reference       : /AC97C_XXXX.pl/1.3/Tue Feb 22 17:08:27 2005//
// - CVS Reference       : /CAN_6019B.pl/1.1/Mon Jan 31 13:54:30 2005//
// - CVS Reference       : /PWM_6044D.pl/1.2/Tue May 10 12:39:09 2005//
// - CVS Reference       : /LCDC_6063A.pl/1.3/Fri Dec  9 10:59:26 2005//
// - CVS Reference       : /EMACB_6119A.pl/1.6/Wed Jul 13 15:25:00 2005//
// - CVS Reference       : /DMA_XXXX.pl/1.6/Tue Jan 11 09:40:44 2005//
// - CVS Reference       : /UDP_6ept_puon.pl/1.1/Wed Aug 30 14:20:53 2006//
// - CVS Reference       : /UHP_6127A.pl/1.1/Wed Feb 23 16:03:17 2005//
// - CVS Reference       : /TBOX_XXXX.pl/1.15/Thu Jun  9 07:05:57 2005//
// - CVS Reference       : /EBI_nadia2.pl/1.1/Wed Dec 29 11:28:03 2004//
// - CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb  9 17:16:57 2005//
// - CVS Reference       : /ISI_xxxxx.pl/1.3/Thu Mar  3 11:11:48 2005//
// - ----------------------------------------------------------------------------

#ifndef AT91SAM9263_H
#define AT91SAM9263_H

#ifdef __IAR_SYSTEMS_ICC__

typedef volatile unsigned int AT91_REG;// Hardware register definition

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR System Peripherals
// *****************************************************************************
typedef struct _AT91S_SYS {
	AT91_REG	 SYS_ECC0; 	// ECC 0
	AT91_REG	 Reserved0[127]; 	// 
	AT91_REG	 SYS_SDRAMC0_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SYS_SDRAMC0_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SYS_SDRAMC0_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SYS_SDRAMC0_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SYS_SDRAMC0_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SYS_SDRAMC0_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SYS_SDRAMC0_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SYS_SDRAMC0_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC0_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC0_MDR; 	// SDRAM Memory Device Register
	AT91_REG	 Reserved1[118]; 	// 
	AT91_REG	 SYS_SMC0_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SYS_SMC0_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SYS_SMC0_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SYS_SMC0_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SYS_SMC0_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SYS_SMC0_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SYS_SMC0_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SYS_SMC0_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SYS_SMC0_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SYS_SMC0_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SYS_SMC0_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SYS_SMC0_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SYS_SMC0_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SYS_SMC0_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SYS_SMC0_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SYS_SMC0_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SYS_SMC0_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SYS_SMC0_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SYS_SMC0_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SYS_SMC0_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SYS_SMC0_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SYS_SMC0_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SYS_SMC0_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SYS_SMC0_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SYS_SMC0_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SYS_SMC0_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SYS_SMC0_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SYS_SMC0_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SYS_SMC0_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SYS_SMC0_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SYS_SMC0_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SYS_SMC0_CTRL7; 	//  Control Register for CS 7
	AT91_REG	 Reserved2[96]; 	// 
	AT91_REG	 SYS_ECC1; 	// ECC 0
	AT91_REG	 Reserved3[127]; 	// 
	AT91_REG	 SYS_SDRAMC1_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SYS_SDRAMC1_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SYS_SDRAMC1_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SYS_SDRAMC1_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SYS_SDRAMC1_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SYS_SDRAMC1_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SYS_SDRAMC1_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SYS_SDRAMC1_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC1_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SYS_SDRAMC1_MDR; 	// SDRAM Memory Device Register
	AT91_REG	 Reserved4[118]; 	// 
	AT91_REG	 SYS_SMC1_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SYS_SMC1_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SYS_SMC1_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SYS_SMC1_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SYS_SMC1_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SYS_SMC1_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SYS_SMC1_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SYS_SMC1_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SYS_SMC1_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SYS_SMC1_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SYS_SMC1_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SYS_SMC1_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SYS_SMC1_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SYS_SMC1_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SYS_SMC1_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SYS_SMC1_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SYS_SMC1_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SYS_SMC1_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SYS_SMC1_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SYS_SMC1_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SYS_SMC1_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SYS_SMC1_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SYS_SMC1_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SYS_SMC1_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SYS_SMC1_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SYS_SMC1_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SYS_SMC1_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SYS_SMC1_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SYS_SMC1_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SYS_SMC1_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SYS_SMC1_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SYS_SMC1_CTRL7; 	//  Control Register for CS 7
	AT91_REG	 Reserved5[96]; 	// 
	AT91_REG	 SYS_MATRIX_MCFG0; 	//  Master Configuration Register 0 
	AT91_REG	 SYS_MATRIX_MCFG1; 	//  Master Configuration Register 1 
	AT91_REG	 SYS_MATRIX_MCFG2; 	//  Master Configuration Register 2 
	AT91_REG	 SYS_MATRIX_MCFG3; 	//  Master Configuration Register 3 
	AT91_REG	 SYS_MATRIX_MCFG4; 	//  Master Configuration Register 4 
	AT91_REG	 SYS_MATRIX_MCFG5; 	//  Master Configuration Register 5 
	AT91_REG	 SYS_MATRIX_MCFG6; 	//  Master Configuration Register 6 
	AT91_REG	 SYS_MATRIX_MCFG7; 	//  Master Configuration Register 7 
	AT91_REG	 SYS_MATRIX_MCFG8; 	//  Master Configuration Register 8 
	AT91_REG	 Reserved6[7]; 	// 
	AT91_REG	 SYS_MATRIX_SCFG0; 	//  Slave Configuration Register 0
	AT91_REG	 SYS_MATRIX_SCFG1; 	//  Slave Configuration Register 1
	AT91_REG	 SYS_MATRIX_SCFG2; 	//  Slave Configuration Register 2
	AT91_REG	 SYS_MATRIX_SCFG3; 	//  Slave Configuration Register 3
	AT91_REG	 SYS_MATRIX_SCFG4; 	//  Slave Configuration Register 4
	AT91_REG	 SYS_MATRIX_SCFG5; 	//  Slave Configuration Register 5
	AT91_REG	 SYS_MATRIX_SCFG6; 	//  Slave Configuration Register 6
	AT91_REG	 SYS_MATRIX_SCFG7; 	//  Slave Configuration Register 7
	AT91_REG	 Reserved7[8]; 	// 
	AT91_REG	 SYS_MATRIX_PRAS0; 	//  PRAS0
	AT91_REG	 SYS_MATRIX_PRBS0; 	//  PRBS0
	AT91_REG	 SYS_MATRIX_PRAS1; 	//  PRAS1
	AT91_REG	 SYS_MATRIX_PRBS1; 	//  PRBS1
	AT91_REG	 SYS_MATRIX_PRAS2; 	//  PRAS2
	AT91_REG	 SYS_MATRIX_PRBS2; 	//  PRBS2
	AT91_REG	 SYS_MATRIX_PRAS3; 	//  PRAS3
	AT91_REG	 SYS_MATRIX_PRBS3; 	//  PRBS3
	AT91_REG	 SYS_MATRIX_PRAS4; 	//  PRAS4
	AT91_REG	 SYS_MATRIX_PRBS4; 	//  PRBS4
	AT91_REG	 SYS_MATRIX_PRAS5; 	//  PRAS5
	AT91_REG	 SYS_MATRIX_PRBS5; 	//  PRBS5
	AT91_REG	 SYS_MATRIX_PRAS6; 	//  PRAS6
	AT91_REG	 SYS_MATRIX_PRBS6; 	//  PRBS6
	AT91_REG	 SYS_MATRIX_PRAS7; 	//  PRAS7
	AT91_REG	 SYS_MATRIX_PRBS7; 	//  PRBS7
	AT91_REG	 Reserved8[16]; 	// 
	AT91_REG	 SYS_MATRIX_MRCR; 	//  Master Remp Control Register 
	AT91_REG	 Reserved9[63]; 	// 
	AT91_REG	 SYS_DBGU_CR; 	// Control Register
	AT91_REG	 SYS_DBGU_MR; 	// Mode Register
	AT91_REG	 SYS_DBGU_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_DBGU_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_DBGU_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_DBGU_CSR; 	// Channel Status Register
	AT91_REG	 SYS_DBGU_RHR; 	// Receiver Holding Register
	AT91_REG	 SYS_DBGU_THR; 	// Transmitter Holding Register
	AT91_REG	 SYS_DBGU_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 Reserved10[7]; 	// 
	AT91_REG	 SYS_DBGU_CIDR; 	// Chip ID Register
	AT91_REG	 SYS_DBGU_EXID; 	// Chip ID Extension Register
	AT91_REG	 SYS_DBGU_FNTR; 	// Force NTRST Register
	AT91_REG	 Reserved11[45]; 	// 
	AT91_REG	 SYS_DBGU_RPR; 	// Receive Pointer Register
	AT91_REG	 SYS_DBGU_RCR; 	// Receive Counter Register
	AT91_REG	 SYS_DBGU_TPR; 	// Transmit Pointer Register
	AT91_REG	 SYS_DBGU_TCR; 	// Transmit Counter Register
	AT91_REG	 SYS_DBGU_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 SYS_DBGU_RNCR; 	// Receive Next Counter Register
	AT91_REG	 SYS_DBGU_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 SYS_DBGU_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 SYS_DBGU_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 SYS_DBGU_PTSR; 	// PDC Transfer Status Register
	AT91_REG	 Reserved12[54]; 	// 
	AT91_REG	 SYS_AIC_SMR[32]; 	// Source Mode Register
	AT91_REG	 SYS_AIC_SVR[32]; 	// Source Vector Register
	AT91_REG	 SYS_AIC_IVR; 	// IRQ Vector Register
	AT91_REG	 SYS_AIC_FVR; 	// FIQ Vector Register
	AT91_REG	 SYS_AIC_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_AIC_IPR; 	// Interrupt Pending Register
	AT91_REG	 SYS_AIC_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_AIC_CISR; 	// Core Interrupt Status Register
	AT91_REG	 Reserved13[2]; 	// 
	AT91_REG	 SYS_AIC_IECR; 	// Interrupt Enable Command Register
	AT91_REG	 SYS_AIC_IDCR; 	// Interrupt Disable Command Register
	AT91_REG	 SYS_AIC_ICCR; 	// Interrupt Clear Command Register
	AT91_REG	 SYS_AIC_ISCR; 	// Interrupt Set Command Register
	AT91_REG	 SYS_AIC_EOICR; 	// End of Interrupt Command Register
	AT91_REG	 SYS_AIC_SPU; 	// Spurious Vector Register
	AT91_REG	 SYS_AIC_DCR; 	// Debug Control Register (Protect)
	AT91_REG	 Reserved14[1]; 	// 
	AT91_REG	 SYS_AIC_FFER; 	// Fast Forcing Enable Register
	AT91_REG	 SYS_AIC_FFDR; 	// Fast Forcing Disable Register
	AT91_REG	 SYS_AIC_FFSR; 	// Fast Forcing Status Register
	AT91_REG	 Reserved15[45]; 	// 
	AT91_REG	 SYS_PIOA_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOA_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOA_PSR; 	// PIO Status Register
	AT91_REG	 Reserved16[1]; 	// 
	AT91_REG	 SYS_PIOA_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOA_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOA_OSR; 	// Output Status Register
	AT91_REG	 Reserved17[1]; 	// 
	AT91_REG	 SYS_PIOA_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOA_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOA_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved18[1]; 	// 
	AT91_REG	 SYS_PIOA_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOA_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOA_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOA_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOA_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOA_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOA_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOA_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOA_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOA_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOA_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved19[1]; 	// 
	AT91_REG	 SYS_PIOA_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOA_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOA_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved20[1]; 	// 
	AT91_REG	 SYS_PIOA_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOA_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOA_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved21[9]; 	// 
	AT91_REG	 SYS_PIOA_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOA_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOA_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved22[85]; 	// 
	AT91_REG	 SYS_PIOB_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOB_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOB_PSR; 	// PIO Status Register
	AT91_REG	 Reserved23[1]; 	// 
	AT91_REG	 SYS_PIOB_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOB_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOB_OSR; 	// Output Status Register
	AT91_REG	 Reserved24[1]; 	// 
	AT91_REG	 SYS_PIOB_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOB_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOB_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved25[1]; 	// 
	AT91_REG	 SYS_PIOB_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOB_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOB_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOB_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOB_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOB_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOB_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOB_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOB_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOB_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOB_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved26[1]; 	// 
	AT91_REG	 SYS_PIOB_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOB_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOB_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved27[1]; 	// 
	AT91_REG	 SYS_PIOB_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOB_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOB_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved28[9]; 	// 
	AT91_REG	 SYS_PIOB_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOB_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOB_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved29[85]; 	// 
	AT91_REG	 SYS_PIOC_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOC_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOC_PSR; 	// PIO Status Register
	AT91_REG	 Reserved30[1]; 	// 
	AT91_REG	 SYS_PIOC_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOC_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOC_OSR; 	// Output Status Register
	AT91_REG	 Reserved31[1]; 	// 
	AT91_REG	 SYS_PIOC_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOC_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOC_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved32[1]; 	// 
	AT91_REG	 SYS_PIOC_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOC_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOC_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOC_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOC_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOC_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOC_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOC_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOC_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOC_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOC_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved33[1]; 	// 
	AT91_REG	 SYS_PIOC_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOC_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOC_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved34[1]; 	// 
	AT91_REG	 SYS_PIOC_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOC_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOC_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved35[9]; 	// 
	AT91_REG	 SYS_PIOC_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOC_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOC_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved36[85]; 	// 
	AT91_REG	 SYS_PIOD_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOD_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOD_PSR; 	// PIO Status Register
	AT91_REG	 Reserved37[1]; 	// 
	AT91_REG	 SYS_PIOD_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOD_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOD_OSR; 	// Output Status Register
	AT91_REG	 Reserved38[1]; 	// 
	AT91_REG	 SYS_PIOD_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOD_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOD_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved39[1]; 	// 
	AT91_REG	 SYS_PIOD_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOD_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOD_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOD_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOD_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOD_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOD_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOD_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOD_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOD_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOD_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved40[1]; 	// 
	AT91_REG	 SYS_PIOD_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOD_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOD_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved41[1]; 	// 
	AT91_REG	 SYS_PIOD_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOD_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOD_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved42[9]; 	// 
	AT91_REG	 SYS_PIOD_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOD_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOD_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved43[85]; 	// 
	AT91_REG	 SYS_PIOE_PER; 	// PIO Enable Register
	AT91_REG	 SYS_PIOE_PDR; 	// PIO Disable Register
	AT91_REG	 SYS_PIOE_PSR; 	// PIO Status Register
	AT91_REG	 Reserved44[1]; 	// 
	AT91_REG	 SYS_PIOE_OER; 	// Output Enable Register
	AT91_REG	 SYS_PIOE_ODR; 	// Output Disable Registerr
	AT91_REG	 SYS_PIOE_OSR; 	// Output Status Register
	AT91_REG	 Reserved45[1]; 	// 
	AT91_REG	 SYS_PIOE_IFER; 	// Input Filter Enable Register
	AT91_REG	 SYS_PIOE_IFDR; 	// Input Filter Disable Register
	AT91_REG	 SYS_PIOE_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved46[1]; 	// 
	AT91_REG	 SYS_PIOE_SODR; 	// Set Output Data Register
	AT91_REG	 SYS_PIOE_CODR; 	// Clear Output Data Register
	AT91_REG	 SYS_PIOE_ODSR; 	// Output Data Status Register
	AT91_REG	 SYS_PIOE_PDSR; 	// Pin Data Status Register
	AT91_REG	 SYS_PIOE_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PIOE_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PIOE_IMR; 	// Interrupt Mask Register
	AT91_REG	 SYS_PIOE_ISR; 	// Interrupt Status Register
	AT91_REG	 SYS_PIOE_MDER; 	// Multi-driver Enable Register
	AT91_REG	 SYS_PIOE_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 SYS_PIOE_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved47[1]; 	// 
	AT91_REG	 SYS_PIOE_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 SYS_PIOE_PPUER; 	// Pull-up Enable Register
	AT91_REG	 SYS_PIOE_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved48[1]; 	// 
	AT91_REG	 SYS_PIOE_ASR; 	// Select A Register
	AT91_REG	 SYS_PIOE_BSR; 	// Select B Register
	AT91_REG	 SYS_PIOE_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved49[9]; 	// 
	AT91_REG	 SYS_PIOE_OWER; 	// Output Write Enable Register
	AT91_REG	 SYS_PIOE_OWDR; 	// Output Write Disable Register
	AT91_REG	 SYS_PIOE_OWSR; 	// Output Write Status Register
	AT91_REG	 Reserved50[85]; 	// 
	AT91_REG	 SYS_PMC_SCER; 	// System Clock Enable Register
	AT91_REG	 SYS_PMC_SCDR; 	// System Clock Disable Register
	AT91_REG	 SYS_PMC_SCSR; 	// System Clock Status Register
	AT91_REG	 Reserved51[1]; 	// 
	AT91_REG	 SYS_PMC_PCER; 	// Peripheral Clock Enable Register
	AT91_REG	 SYS_PMC_PCDR; 	// Peripheral Clock Disable Register
	AT91_REG	 SYS_PMC_PCSR; 	// Peripheral Clock Status Register
	AT91_REG	 Reserved52[1]; 	// 
	AT91_REG	 SYS_PMC_MOR; 	// Main Oscillator Register
	AT91_REG	 SYS_PMC_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 SYS_PMC_PLLAR; 	// PLL A Register
	AT91_REG	 SYS_PMC_PLLBR; 	// PLL B Register
	AT91_REG	 SYS_PMC_MCKR; 	// Master Clock Register
	AT91_REG	 Reserved53[3]; 	// 
	AT91_REG	 SYS_PMC_PCKR[8]; 	// Programmable Clock Register
	AT91_REG	 SYS_PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 SYS_PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 SYS_PMC_SR; 	// Status Register
	AT91_REG	 SYS_PMC_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved54[36]; 	// 
	AT91_REG	 SYS_RSTC_RCR; 	// Reset Control Register
	AT91_REG	 SYS_RSTC_RSR; 	// Reset Status Register
	AT91_REG	 SYS_RSTC_RMR; 	// Reset Mode Register
	AT91_REG	 Reserved55[1]; 	// 
	AT91_REG	 SYS_SHDWC_SHCR; 	// Shut Down Control Register
	AT91_REG	 SYS_SHDWC_SHMR; 	// Shut Down Mode Register
	AT91_REG	 SYS_SHDWC_SHSR; 	// Shut Down Status Register
	AT91_REG	 Reserved56[1]; 	// 
	AT91_REG	 SYS_RTTC0_RTMR; 	// Real-time Mode Register
	AT91_REG	 SYS_RTTC0_RTAR; 	// Real-time Alarm Register
	AT91_REG	 SYS_RTTC0_RTVR; 	// Real-time Value Register
	AT91_REG	 SYS_RTTC0_RTSR; 	// Real-time Status Register
	AT91_REG	 SYS_PITC_PIMR; 	// Period Interval Mode Register
	AT91_REG	 SYS_PITC_PISR; 	// Period Interval Status Register
	AT91_REG	 SYS_PITC_PIVR; 	// Period Interval Value Register
	AT91_REG	 SYS_PITC_PIIR; 	// Period Interval Image Register
	AT91_REG	 SYS_WDTC_WDCR; 	// Watchdog Control Register
	AT91_REG	 SYS_WDTC_WDMR; 	// Watchdog Mode Register
	AT91_REG	 SYS_WDTC_WDSR; 	// Watchdog Status Register
	AT91_REG	 Reserved57[1]; 	// 
	AT91_REG	 SYS_RTTC1_RTMR; 	// Real-time Mode Register
	AT91_REG	 SYS_RTTC1_RTAR; 	// Real-time Alarm Register
	AT91_REG	 SYS_RTTC1_RTVR; 	// Real-time Value Register
	AT91_REG	 SYS_RTTC1_RTSR; 	// Real-time Status Register
	AT91_REG	 SYS_GPBR[20]; 	// General Purpose Register
} AT91S_SYS, *AT91PS_SYS;

// -------- GPBR : (SYS Offset: 0x1d60) GPBR General Purpose Register -------- 
#define AT91C_GPBR_GPRV       ((unsigned int) 0x0 <<  0) // (SYS) General Purpose Register Value

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR External Bus Interface 0
// *****************************************************************************
typedef struct _AT91S_EBI0 {
	AT91_REG	 EBI0_DUMMY; 	// Dummy register - Do not use
} AT91S_EBI0, *AT91PS_EBI0;


// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR SDRAM Controller Interface
// *****************************************************************************
typedef struct _AT91S_SDRAMC {
	AT91_REG	 SDRAMC_MR; 	// SDRAM Controller Mode Register
	AT91_REG	 SDRAMC_TR; 	// SDRAM Controller Refresh Timer Register
	AT91_REG	 SDRAMC_CR; 	// SDRAM Controller Configuration Register
	AT91_REG	 SDRAMC_HSR; 	// SDRAM Controller High Speed Register
	AT91_REG	 SDRAMC_LPR; 	// SDRAM Controller Low Power Register
	AT91_REG	 SDRAMC_IER; 	// SDRAM Controller Interrupt Enable Register
	AT91_REG	 SDRAMC_IDR; 	// SDRAM Controller Interrupt Disable Register
	AT91_REG	 SDRAMC_IMR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_ISR; 	// SDRAM Controller Interrupt Mask Register
	AT91_REG	 SDRAMC_MDR; 	// SDRAM Memory Device Register
} AT91S_SDRAMC, *AT91PS_SDRAMC;

// -------- SDRAMC_MR : (SDRAMC Offset: 0x0) SDRAM Controller Mode Register -------- 
#define AT91C_SDRAMC_MODE     ((unsigned int) 0xF <<  0) // (SDRAMC) Mode
#define 	AT91C_SDRAMC_MODE_NORMAL_CMD           ((unsigned int) 0x0) // (SDRAMC) Normal Mode
#define 	AT91C_SDRAMC_MODE_NOP_CMD              ((unsigned int) 0x1) // (SDRAMC) Issue a NOP Command at every access
#define 	AT91C_SDRAMC_MODE_PRCGALL_CMD          ((unsigned int) 0x2) // (SDRAMC) Issue a All Banks Precharge Command at every access
#define 	AT91C_SDRAMC_MODE_LMR_CMD              ((unsigned int) 0x3) // (SDRAMC) Issue a Load Mode Register at every access
#define 	AT91C_SDRAMC_MODE_RFSH_CMD             ((unsigned int) 0x4) // (SDRAMC) Issue a Refresh
#define 	AT91C_SDRAMC_MODE_EXT_LMR_CMD          ((unsigned int) 0x5) // (SDRAMC) Issue an Extended Load Mode Register
#define 	AT91C_SDRAMC_MODE_DEEP_CMD             ((unsigned int) 0x6) // (SDRAMC) Enter Deep Power Mode
// -------- SDRAMC_TR : (SDRAMC Offset: 0x4) SDRAMC Refresh Timer Register -------- 
#define AT91C_SDRAMC_COUNT    ((unsigned int) 0xFFF <<  0) // (SDRAMC) Refresh Counter
// -------- SDRAMC_CR : (SDRAMC Offset: 0x8) SDRAM Configuration Register -------- 
#define AT91C_SDRAMC_NC       ((unsigned int) 0x3 <<  0) // (SDRAMC) Number of Column Bits
#define 	AT91C_SDRAMC_NC_8                    ((unsigned int) 0x0) // (SDRAMC) 8 Bits
#define 	AT91C_SDRAMC_NC_9                    ((unsigned int) 0x1) // (SDRAMC) 9 Bits
#define 	AT91C_SDRAMC_NC_10                   ((unsigned int) 0x2) // (SDRAMC) 10 Bits
#define 	AT91C_SDRAMC_NC_11                   ((unsigned int) 0x3) // (SDRAMC) 11 Bits
#define AT91C_SDRAMC_NR       ((unsigned int) 0x3 <<  2) // (SDRAMC) Number of Row Bits
#define 	AT91C_SDRAMC_NR_11                   ((unsigned int) 0x0 <<  2) // (SDRAMC) 11 Bits
#define 	AT91C_SDRAMC_NR_12                   ((unsigned int) 0x1 <<  2) // (SDRAMC) 12 Bits
#define 	AT91C_SDRAMC_NR_13                   ((unsigned int) 0x2 <<  2) // (SDRAMC) 13 Bits
#define AT91C_SDRAMC_NB       ((unsigned int) 0x1 <<  4) // (SDRAMC) Number of Banks
#define 	AT91C_SDRAMC_NB_2_BANKS              ((unsigned int) 0x0 <<  4) // (SDRAMC) 2 banks
#define 	AT91C_SDRAMC_NB_4_BANKS              ((unsigned int) 0x1 <<  4) // (SDRAMC) 4 banks
#define AT91C_SDRAMC_CAS      ((unsigned int) 0x3 <<  5) // (SDRAMC) CAS Latency
#define 	AT91C_SDRAMC_CAS_2                    ((unsigned int) 0x2 <<  5) // (SDRAMC) 2 cycles
#define 	AT91C_SDRAMC_CAS_3                    ((unsigned int) 0x3 <<  5) // (SDRAMC) 3 cycles
#define AT91C_SDRAMC_DBW      ((unsigned int) 0x1 <<  7) // (SDRAMC) Data Bus Width
#define 	AT91C_SDRAMC_DBW_32_BITS              ((unsigned int) 0x0 <<  7) // (SDRAMC) 32 Bits datas bus
#define 	AT91C_SDRAMC_DBW_16_BITS              ((unsigned int) 0x1 <<  7) // (SDRAMC) 16 Bits datas bus
#define AT91C_SDRAMC_TWR      ((unsigned int) 0xF <<  8) // (SDRAMC) Number of Write Recovery Time Cycles
#define 	AT91C_SDRAMC_TWR_0                    ((unsigned int) 0x0 <<  8) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TWR_1                    ((unsigned int) 0x1 <<  8) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TWR_2                    ((unsigned int) 0x2 <<  8) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TWR_3                    ((unsigned int) 0x3 <<  8) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TWR_4                    ((unsigned int) 0x4 <<  8) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TWR_5                    ((unsigned int) 0x5 <<  8) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TWR_6                    ((unsigned int) 0x6 <<  8) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TWR_7                    ((unsigned int) 0x7 <<  8) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TWR_8                    ((unsigned int) 0x8 <<  8) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TWR_9                    ((unsigned int) 0x9 <<  8) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TWR_10                   ((unsigned int) 0xA <<  8) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TWR_11                   ((unsigned int) 0xB <<  8) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TWR_12                   ((unsigned int) 0xC <<  8) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TWR_13                   ((unsigned int) 0xD <<  8) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TWR_14                   ((unsigned int) 0xE <<  8) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TWR_15                   ((unsigned int) 0xF <<  8) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRC      ((unsigned int) 0xF << 12) // (SDRAMC) Number of RAS Cycle Time Cycles
#define 	AT91C_SDRAMC_TRC_0                    ((unsigned int) 0x0 << 12) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRC_1                    ((unsigned int) 0x1 << 12) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRC_2                    ((unsigned int) 0x2 << 12) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRC_3                    ((unsigned int) 0x3 << 12) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRC_4                    ((unsigned int) 0x4 << 12) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRC_5                    ((unsigned int) 0x5 << 12) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRC_6                    ((unsigned int) 0x6 << 12) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRC_7                    ((unsigned int) 0x7 << 12) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRC_8                    ((unsigned int) 0x8 << 12) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRC_9                    ((unsigned int) 0x9 << 12) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRC_10                   ((unsigned int) 0xA << 12) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRC_11                   ((unsigned int) 0xB << 12) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRC_12                   ((unsigned int) 0xC << 12) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRC_13                   ((unsigned int) 0xD << 12) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRC_14                   ((unsigned int) 0xE << 12) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRC_15                   ((unsigned int) 0xF << 12) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRP      ((unsigned int) 0xF << 16) // (SDRAMC) Number of RAS Precharge Time Cycles
#define 	AT91C_SDRAMC_TRP_0                    ((unsigned int) 0x0 << 16) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRP_1                    ((unsigned int) 0x1 << 16) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRP_2                    ((unsigned int) 0x2 << 16) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRP_3                    ((unsigned int) 0x3 << 16) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRP_4                    ((unsigned int) 0x4 << 16) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRP_5                    ((unsigned int) 0x5 << 16) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRP_6                    ((unsigned int) 0x6 << 16) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRP_7                    ((unsigned int) 0x7 << 16) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRP_8                    ((unsigned int) 0x8 << 16) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRP_9                    ((unsigned int) 0x9 << 16) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRP_10                   ((unsigned int) 0xA << 16) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRP_11                   ((unsigned int) 0xB << 16) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRP_12                   ((unsigned int) 0xC << 16) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRP_13                   ((unsigned int) 0xD << 16) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRP_14                   ((unsigned int) 0xE << 16) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRP_15                   ((unsigned int) 0xF << 16) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRCD     ((unsigned int) 0xF << 20) // (SDRAMC) Number of RAS to CAS Delay Cycles
#define 	AT91C_SDRAMC_TRCD_0                    ((unsigned int) 0x0 << 20) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRCD_1                    ((unsigned int) 0x1 << 20) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRCD_2                    ((unsigned int) 0x2 << 20) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRCD_3                    ((unsigned int) 0x3 << 20) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRCD_4                    ((unsigned int) 0x4 << 20) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRCD_5                    ((unsigned int) 0x5 << 20) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRCD_6                    ((unsigned int) 0x6 << 20) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRCD_7                    ((unsigned int) 0x7 << 20) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRCD_8                    ((unsigned int) 0x8 << 20) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRCD_9                    ((unsigned int) 0x9 << 20) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRCD_10                   ((unsigned int) 0xA << 20) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRCD_11                   ((unsigned int) 0xB << 20) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRCD_12                   ((unsigned int) 0xC << 20) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRCD_13                   ((unsigned int) 0xD << 20) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRCD_14                   ((unsigned int) 0xE << 20) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRCD_15                   ((unsigned int) 0xF << 20) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TRAS     ((unsigned int) 0xF << 24) // (SDRAMC) Number of RAS Active Time Cycles
#define 	AT91C_SDRAMC_TRAS_0                    ((unsigned int) 0x0 << 24) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TRAS_1                    ((unsigned int) 0x1 << 24) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TRAS_2                    ((unsigned int) 0x2 << 24) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TRAS_3                    ((unsigned int) 0x3 << 24) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TRAS_4                    ((unsigned int) 0x4 << 24) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TRAS_5                    ((unsigned int) 0x5 << 24) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TRAS_6                    ((unsigned int) 0x6 << 24) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TRAS_7                    ((unsigned int) 0x7 << 24) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TRAS_8                    ((unsigned int) 0x8 << 24) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TRAS_9                    ((unsigned int) 0x9 << 24) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TRAS_10                   ((unsigned int) 0xA << 24) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TRAS_11                   ((unsigned int) 0xB << 24) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TRAS_12                   ((unsigned int) 0xC << 24) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TRAS_13                   ((unsigned int) 0xD << 24) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TRAS_14                   ((unsigned int) 0xE << 24) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TRAS_15                   ((unsigned int) 0xF << 24) // (SDRAMC) Value : 15
#define AT91C_SDRAMC_TXSR     ((unsigned int) 0xF << 28) // (SDRAMC) Number of Command Recovery Time Cycles
#define 	AT91C_SDRAMC_TXSR_0                    ((unsigned int) 0x0 << 28) // (SDRAMC) Value :  0
#define 	AT91C_SDRAMC_TXSR_1                    ((unsigned int) 0x1 << 28) // (SDRAMC) Value :  1
#define 	AT91C_SDRAMC_TXSR_2                    ((unsigned int) 0x2 << 28) // (SDRAMC) Value :  2
#define 	AT91C_SDRAMC_TXSR_3                    ((unsigned int) 0x3 << 28) // (SDRAMC) Value :  3
#define 	AT91C_SDRAMC_TXSR_4                    ((unsigned int) 0x4 << 28) // (SDRAMC) Value :  4
#define 	AT91C_SDRAMC_TXSR_5                    ((unsigned int) 0x5 << 28) // (SDRAMC) Value :  5
#define 	AT91C_SDRAMC_TXSR_6                    ((unsigned int) 0x6 << 28) // (SDRAMC) Value :  6
#define 	AT91C_SDRAMC_TXSR_7                    ((unsigned int) 0x7 << 28) // (SDRAMC) Value :  7
#define 	AT91C_SDRAMC_TXSR_8                    ((unsigned int) 0x8 << 28) // (SDRAMC) Value :  8
#define 	AT91C_SDRAMC_TXSR_9                    ((unsigned int) 0x9 << 28) // (SDRAMC) Value :  9
#define 	AT91C_SDRAMC_TXSR_10                   ((unsigned int) 0xA << 28) // (SDRAMC) Value : 10
#define 	AT91C_SDRAMC_TXSR_11                   ((unsigned int) 0xB << 28) // (SDRAMC) Value : 11
#define 	AT91C_SDRAMC_TXSR_12                   ((unsigned int) 0xC << 28) // (SDRAMC) Value : 12
#define 	AT91C_SDRAMC_TXSR_13                   ((unsigned int) 0xD << 28) // (SDRAMC) Value : 13
#define 	AT91C_SDRAMC_TXSR_14                   ((unsigned int) 0xE << 28) // (SDRAMC) Value : 14
#define 	AT91C_SDRAMC_TXSR_15                   ((unsigned int) 0xF << 28) // (SDRAMC) Value : 15
// -------- SDRAMC_HSR : (SDRAMC Offset: 0xc) SDRAM Controller High Speed Register -------- 
#define AT91C_SDRAMC_DA       ((unsigned int) 0x1 <<  0) // (SDRAMC) Decode Cycle Enable Bit
#define 	AT91C_SDRAMC_DA_DISABLE              ((unsigned int) 0x0) // (SDRAMC) Disable Decode Cycle
#define 	AT91C_SDRAMC_DA_ENABLE               ((unsigned int) 0x1) // (SDRAMC) Enable Decode Cycle
// -------- SDRAMC_LPR : (SDRAMC Offset: 0x10) SDRAM Controller Low-power Register -------- 
#define AT91C_SDRAMC_LPCB     ((unsigned int) 0x3 <<  0) // (SDRAMC) Low-power Configurations
#define 	AT91C_SDRAMC_LPCB_DISABLE              ((unsigned int) 0x0) // (SDRAMC) Disable Low Power Features
#define 	AT91C_SDRAMC_LPCB_SELF_REFRESH         ((unsigned int) 0x1) // (SDRAMC) Enable SELF_REFRESH
#define 	AT91C_SDRAMC_LPCB_POWER_DOWN           ((unsigned int) 0x2) // (SDRAMC) Enable POWER_DOWN
#define 	AT91C_SDRAMC_LPCB_DEEP_POWER_DOWN      ((unsigned int) 0x3) // (SDRAMC) Enable DEEP_POWER_DOWN
#define AT91C_SDRAMC_PASR     ((unsigned int) 0x7 <<  4) // (SDRAMC) Partial Array Self Refresh (only for Low Power SDRAM)
#define AT91C_SDRAMC_TCSR     ((unsigned int) 0x3 <<  8) // (SDRAMC) Temperature Compensated Self Refresh (only for Low Power SDRAM)
#define AT91C_SDRAMC_DS       ((unsigned int) 0x3 << 10) // (SDRAMC) Drive Strenght (only for Low Power SDRAM)
#define AT91C_SDRAMC_TIMEOUT  ((unsigned int) 0x3 << 12) // (SDRAMC) Time to define when Low Power Mode is enabled
#define 	AT91C_SDRAMC_TIMEOUT_0_CLK_CYCLES         ((unsigned int) 0x0 << 12) // (SDRAMC) Activate SDRAM Low Power Mode Immediately
#define 	AT91C_SDRAMC_TIMEOUT_64_CLK_CYCLES        ((unsigned int) 0x1 << 12) // (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
#define 	AT91C_SDRAMC_TIMEOUT_128_CLK_CYCLES       ((unsigned int) 0x2 << 12) // (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
// -------- SDRAMC_IER : (SDRAMC Offset: 0x14) SDRAM Controller Interrupt Enable Register -------- 
#define AT91C_SDRAMC_RES      ((unsigned int) 0x1 <<  0) // (SDRAMC) Refresh Error Status
// -------- SDRAMC_IDR : (SDRAMC Offset: 0x18) SDRAM Controller Interrupt Disable Register -------- 
// -------- SDRAMC_IMR : (SDRAMC Offset: 0x1c) SDRAM Controller Interrupt Mask Register -------- 
// -------- SDRAMC_ISR : (SDRAMC Offset: 0x20) SDRAM Controller Interrupt Status Register -------- 
// -------- SDRAMC_MDR : (SDRAMC Offset: 0x24) SDRAM Controller Memory Device Register -------- 
#define AT91C_SDRAMC_MD       ((unsigned int) 0x3 <<  0) // (SDRAMC) Memory Device Type
#define 	AT91C_SDRAMC_MD_SDRAM                ((unsigned int) 0x0) // (SDRAMC) SDRAM Mode
#define 	AT91C_SDRAMC_MD_LOW_POWER_SDRAM      ((unsigned int) 0x1) // (SDRAMC) SDRAM Low Power Mode

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Static Memory Controller Interface
// *****************************************************************************
typedef struct _AT91S_SMC {
	AT91_REG	 SMC_SETUP0; 	//  Setup Register for CS 0
	AT91_REG	 SMC_PULSE0; 	//  Pulse Register for CS 0
	AT91_REG	 SMC_CYCLE0; 	//  Cycle Register for CS 0
	AT91_REG	 SMC_CTRL0; 	//  Control Register for CS 0
	AT91_REG	 SMC_SETUP1; 	//  Setup Register for CS 1
	AT91_REG	 SMC_PULSE1; 	//  Pulse Register for CS 1
	AT91_REG	 SMC_CYCLE1; 	//  Cycle Register for CS 1
	AT91_REG	 SMC_CTRL1; 	//  Control Register for CS 1
	AT91_REG	 SMC_SETUP2; 	//  Setup Register for CS 2
	AT91_REG	 SMC_PULSE2; 	//  Pulse Register for CS 2
	AT91_REG	 SMC_CYCLE2; 	//  Cycle Register for CS 2
	AT91_REG	 SMC_CTRL2; 	//  Control Register for CS 2
	AT91_REG	 SMC_SETUP3; 	//  Setup Register for CS 3
	AT91_REG	 SMC_PULSE3; 	//  Pulse Register for CS 3
	AT91_REG	 SMC_CYCLE3; 	//  Cycle Register for CS 3
	AT91_REG	 SMC_CTRL3; 	//  Control Register for CS 3
	AT91_REG	 SMC_SETUP4; 	//  Setup Register for CS 4
	AT91_REG	 SMC_PULSE4; 	//  Pulse Register for CS 4
	AT91_REG	 SMC_CYCLE4; 	//  Cycle Register for CS 4
	AT91_REG	 SMC_CTRL4; 	//  Control Register for CS 4
	AT91_REG	 SMC_SETUP5; 	//  Setup Register for CS 5
	AT91_REG	 SMC_PULSE5; 	//  Pulse Register for CS 5
	AT91_REG	 SMC_CYCLE5; 	//  Cycle Register for CS 5
	AT91_REG	 SMC_CTRL5; 	//  Control Register for CS 5
	AT91_REG	 SMC_SETUP6; 	//  Setup Register for CS 6
	AT91_REG	 SMC_PULSE6; 	//  Pulse Register for CS 6
	AT91_REG	 SMC_CYCLE6; 	//  Cycle Register for CS 6
	AT91_REG	 SMC_CTRL6; 	//  Control Register for CS 6
	AT91_REG	 SMC_SETUP7; 	//  Setup Register for CS 7
	AT91_REG	 SMC_PULSE7; 	//  Pulse Register for CS 7
	AT91_REG	 SMC_CYCLE7; 	//  Cycle Register for CS 7
	AT91_REG	 SMC_CTRL7; 	//  Control Register for CS 7
} AT91S_SMC, *AT91PS_SMC;

// -------- SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x -------- 
#define AT91C_SMC_NWESETUP    ((unsigned int) 0x3F <<  0) // (SMC) NWE Setup Length
#define AT91C_SMC_NCSSETUPWR  ((unsigned int) 0x3F <<  8) // (SMC) NCS Setup Length in WRite Access
#define AT91C_SMC_NRDSETUP    ((unsigned int) 0x3F << 16) // (SMC) NRD Setup Length
#define AT91C_SMC_NCSSETUPRD  ((unsigned int) 0x3F << 24) // (SMC) NCS Setup Length in ReaD Access
// -------- SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x -------- 
#define AT91C_SMC_NWEPULSE    ((unsigned int) 0x7F <<  0) // (SMC) NWE Pulse Length
#define AT91C_SMC_NCSPULSEWR  ((unsigned int) 0x7F <<  8) // (SMC) NCS Pulse Length in WRite Access
#define AT91C_SMC_NRDPULSE    ((unsigned int) 0x7F << 16) // (SMC) NRD Pulse Length
#define AT91C_SMC_NCSPULSERD  ((unsigned int) 0x7F << 24) // (SMC) NCS Pulse Length in ReaD Access
// -------- SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x -------- 
#define AT91C_SMC_NWECYCLE    ((unsigned int) 0x1FF <<  0) // (SMC) Total Write Cycle Length
#define AT91C_SMC_NRDCYCLE    ((unsigned int) 0x1FF << 16) // (SMC) Total Read Cycle Length
// -------- SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x -------- 
#define AT91C_SMC_READMODE    ((unsigned int) 0x1 <<  0) // (SMC) Read Mode
#define AT91C_SMC_WRITEMODE   ((unsigned int) 0x1 <<  1) // (SMC) Write Mode
#define AT91C_SMC_NWAITM      ((unsigned int) 0x3 <<  5) // (SMC) NWAIT Mode
#define 	AT91C_SMC_NWAITM_NWAIT_DISABLE        ((unsigned int) 0x0 <<  5) // (SMC) External NWAIT disabled.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  ((unsigned int) 0x2 <<  5) // (SMC) External NWAIT enabled in frozen mode.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   ((unsigned int) 0x3 <<  5) // (SMC) External NWAIT enabled in ready mode.
#define AT91C_SMC_BAT         ((unsigned int) 0x1 <<  8) // (SMC) Byte Access Type
#define 	AT91C_SMC_BAT_BYTE_SELECT          ((unsigned int) 0x0 <<  8) // (SMC) Write controled by ncs, nbs0, nbs1, nbs2, nbs3. Read controled by ncs, nrd, nbs0, nbs1, nbs2, nbs3.
#define 	AT91C_SMC_BAT_BYTE_WRITE           ((unsigned int) 0x1 <<  8) // (SMC) Write controled by ncs, nwe0, nwe1, nwe2, nwe3. Read controled by ncs and nrd.
#define AT91C_SMC_DBW         ((unsigned int) 0x3 << 12) // (SMC) Data Bus Width
#define 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     ((unsigned int) 0x0 << 12) // (SMC) 8 bits.
#define 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   ((unsigned int) 0x1 << 12) // (SMC) 16 bits.
#define 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS ((unsigned int) 0x2 << 12) // (SMC) 32 bits.
#define AT91C_SMC_TDF         ((unsigned int) 0xF << 16) // (SMC) Data Float Time.
#define AT91C_SMC_TDFEN       ((unsigned int) 0x1 << 20) // (SMC) TDF Enabled.
#define AT91C_SMC_PMEN        ((unsigned int) 0x1 << 24) // (SMC) Page Mode Enabled.
#define AT91C_SMC_PS          ((unsigned int) 0x3 << 28) // (SMC) Page Size
#define 	AT91C_SMC_PS_SIZE_FOUR_BYTES      ((unsigned int) 0x0 << 28) // (SMC) 4 bytes.
#define 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     ((unsigned int) 0x1 << 28) // (SMC) 8 bytes.
#define 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   ((unsigned int) 0x2 << 28) // (SMC) 16 bytes.
#define 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES ((unsigned int) 0x3 << 28) // (SMC) 32 bytes.
// -------- SMC_SETUP : (SMC Offset: 0x10) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x14) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x18) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x1c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x20) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x24) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x28) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x2c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x30) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x34) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x38) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x3c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x40) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x44) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x48) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x4c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x50) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x54) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x58) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x5c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x60) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x64) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x68) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x6c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x70) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x74) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x78) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x7c) Control Register for CS x -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR External Bus Interface 1
// *****************************************************************************
typedef struct _AT91S_EBI1 {
	AT91_REG	 EBI1_DUMMY; 	// Dummy register - Do not use
} AT91S_EBI1, *AT91PS_EBI1;


// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AHB Matrix Interface
// *****************************************************************************
typedef struct _AT91S_MATRIX {
	AT91_REG	 MATRIX_MCFG0; 	//  Master Configuration Register 0 
	AT91_REG	 MATRIX_MCFG1; 	//  Master Configuration Register 1 
	AT91_REG	 MATRIX_MCFG2; 	//  Master Configuration Register 2 
	AT91_REG	 MATRIX_MCFG3; 	//  Master Configuration Register 3 
	AT91_REG	 MATRIX_MCFG4; 	//  Master Configuration Register 4 
	AT91_REG	 MATRIX_MCFG5; 	//  Master Configuration Register 5 
	AT91_REG	 MATRIX_MCFG6; 	//  Master Configuration Register 6 
	AT91_REG	 MATRIX_MCFG7; 	//  Master Configuration Register 7 
	AT91_REG	 MATRIX_MCFG8; 	//  Master Configuration Register 8 
	AT91_REG	 Reserved0[7]; 	// 
	AT91_REG	 MATRIX_SCFG0; 	//  Slave Configuration Register 0
	AT91_REG	 MATRIX_SCFG1; 	//  Slave Configuration Register 1
	AT91_REG	 MATRIX_SCFG2; 	//  Slave Configuration Register 2
	AT91_REG	 MATRIX_SCFG3; 	//  Slave Configuration Register 3
	AT91_REG	 MATRIX_SCFG4; 	//  Slave Configuration Register 4
	AT91_REG	 MATRIX_SCFG5; 	//  Slave Configuration Register 5
	AT91_REG	 MATRIX_SCFG6; 	//  Slave Configuration Register 6
	AT91_REG	 MATRIX_SCFG7; 	//  Slave Configuration Register 7
	AT91_REG	 Reserved1[8]; 	// 
	AT91_REG	 MATRIX_PRAS0; 	//  PRAS0
	AT91_REG	 MATRIX_PRBS0; 	//  PRBS0
	AT91_REG	 MATRIX_PRAS1; 	//  PRAS1
	AT91_REG	 MATRIX_PRBS1; 	//  PRBS1
	AT91_REG	 MATRIX_PRAS2; 	//  PRAS2
	AT91_REG	 MATRIX_PRBS2; 	//  PRBS2
	AT91_REG	 MATRIX_PRAS3; 	//  PRAS3
	AT91_REG	 MATRIX_PRBS3; 	//  PRBS3
	AT91_REG	 MATRIX_PRAS4; 	//  PRAS4
	AT91_REG	 MATRIX_PRBS4; 	//  PRBS4
	AT91_REG	 MATRIX_PRAS5; 	//  PRAS5
	AT91_REG	 MATRIX_PRBS5; 	//  PRBS5
	AT91_REG	 MATRIX_PRAS6; 	//  PRAS6
	AT91_REG	 MATRIX_PRBS6; 	//  PRBS6
	AT91_REG	 MATRIX_PRAS7; 	//  PRAS7
	AT91_REG	 MATRIX_PRBS7; 	//  PRBS7
	AT91_REG	 Reserved2[16]; 	// 
	AT91_REG	 MATRIX_MRCR; 	//  Master Remp Control Register 
} AT91S_MATRIX, *AT91PS_MATRIX;

// -------- MATRIX_MCFG0 : (MATRIX Offset: 0x0) Master Configuration Register rom -------- 
#define AT91C_MATRIX_ULBT     ((unsigned int) 0x7 <<  0) // (MATRIX) Undefined Length Burst Type
// -------- MATRIX_MCFG1 : (MATRIX Offset: 0x4) Master Configuration Register htcm -------- 
// -------- MATRIX_MCFG2 : (MATRIX Offset: 0x8) Master Configuration Register gps_tcm -------- 
// -------- MATRIX_MCFG3 : (MATRIX Offset: 0xc) Master Configuration Register hperiphs -------- 
// -------- MATRIX_MCFG4 : (MATRIX Offset: 0x10) Master Configuration Register ebi0 -------- 
// -------- MATRIX_MCFG5 : (MATRIX Offset: 0x14) Master Configuration Register ebi1 -------- 
// -------- MATRIX_MCFG6 : (MATRIX Offset: 0x18) Master Configuration Register bridge -------- 
// -------- MATRIX_MCFG7 : (MATRIX Offset: 0x1c) Master Configuration Register gps -------- 
// -------- MATRIX_MCFG8 : (MATRIX Offset: 0x20) Master Configuration Register gps -------- 
// -------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 -------- 
#define AT91C_MATRIX_SLOT_CYCLE ((unsigned int) 0xFF <<  0) // (MATRIX) Maximum Number of Allowed Cycles for a Burst
#define AT91C_MATRIX_DEFMSTR_TYPE ((unsigned int) 0x3 << 16) // (MATRIX) Default Master Type
#define 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           ((unsigned int) 0x0 << 16) // (MATRIX) No Default Master. At the end of current slave access, if no other master request is pending, the slave is deconnected from all masters. This results in having a one cycle latency for the first transfer of a burst.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         ((unsigned int) 0x1 << 16) // (MATRIX) Last Default Master. At the end of current slave access, if no other master request is pending, the slave stay connected with the last master having accessed it. This results in not having the one cycle latency when the last master re-trying access on the slave.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        ((unsigned int) 0x2 << 16) // (MATRIX) Fixed Default Master. At the end of current slave access, if no other master request is pending, the slave connects with fixed which number is in FIXED_DEFMSTR field. This results in not having the one cycle latency when the fixed master re-trying access on the slave.
#define AT91C_MATRIX_FIXED_DEFMSTR0 ((unsigned int) 0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_PDC                  ((unsigned int) 0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_2DGC                 ((unsigned int) 0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ISI                  ((unsigned int) 0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_EMAC                 ((unsigned int) 0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_USB                  ((unsigned int) 0x8 << 18) // (MATRIX) USB Master is Default Master
#define AT91C_MATRIX_ARBT     ((unsigned int) 0x3 << 24) // (MATRIX) Arbitration Type
// -------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR1 ((unsigned int) 0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_PDC                  ((unsigned int) 0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_2DGC                 ((unsigned int) 0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ISI                  ((unsigned int) 0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_EMAC                 ((unsigned int) 0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_USB                  ((unsigned int) 0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR2 ((unsigned int) 0x1 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
// -------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR3 ((unsigned int) 0x7 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_PDC                  ((unsigned int) 0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_2DGC                 ((unsigned int) 0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ISI                  ((unsigned int) 0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_EMAC                 ((unsigned int) 0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_USB                  ((unsigned int) 0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR4 ((unsigned int) 0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
// -------- MATRIX_SCFG5 : (MATRIX Offset: 0x54) Slave Configuration Register 5 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR5 ((unsigned int) 0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_PDC                  ((unsigned int) 0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_2DGC                 ((unsigned int) 0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_ISI                  ((unsigned int) 0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_EMAC                 ((unsigned int) 0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_USB                  ((unsigned int) 0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG6 : (MATRIX Offset: 0x58) Slave Configuration Register 6 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR6 ((unsigned int) 0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_PDC                  ((unsigned int) 0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_LCDC                 ((unsigned int) 0x3 << 18) // (MATRIX) LCDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_2DGC                 ((unsigned int) 0x4 << 18) // (MATRIX) 2DGC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_ISI                  ((unsigned int) 0x5 << 18) // (MATRIX) ISI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_EMAC                 ((unsigned int) 0x7 << 18) // (MATRIX) EMAC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_USB                  ((unsigned int) 0x8 << 18) // (MATRIX) USB Master is Default Master
// -------- MATRIX_SCFG7 : (MATRIX Offset: 0x5c) Slave Configuration Register 7 -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR7 ((unsigned int) 0x3 << 18) // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926I              ((unsigned int) 0x0 << 18) // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_ARM926D              ((unsigned int) 0x1 << 18) // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_PDC                  ((unsigned int) 0x2 << 18) // (MATRIX) PDC Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_DMA                  ((unsigned int) 0x6 << 18) // (MATRIX) DMA Controller Master is Default Master
// -------- MATRIX_PRAS0 : (MATRIX Offset: 0x80) PRAS0 Register -------- 
#define AT91C_MATRIX_M0PR     ((unsigned int) 0x3 <<  0) // (MATRIX) ARM926EJ-S Instruction priority
#define AT91C_MATRIX_M1PR     ((unsigned int) 0x3 <<  4) // (MATRIX) ARM926EJ-S Data priority
#define AT91C_MATRIX_M2PR     ((unsigned int) 0x3 <<  8) // (MATRIX) PDC priority
#define AT91C_MATRIX_M3PR     ((unsigned int) 0x3 << 12) // (MATRIX) LCDC priority
#define AT91C_MATRIX_M4PR     ((unsigned int) 0x3 << 16) // (MATRIX) 2DGC priority
#define AT91C_MATRIX_M5PR     ((unsigned int) 0x3 << 20) // (MATRIX) ISI priority
#define AT91C_MATRIX_M6PR     ((unsigned int) 0x3 << 24) // (MATRIX) DMA priority
#define AT91C_MATRIX_M7PR     ((unsigned int) 0x3 << 28) // (MATRIX) EMAC priority
// -------- MATRIX_PRBS0 : (MATRIX Offset: 0x84) PRBS0 Register -------- 
#define AT91C_MATRIX_M8PR     ((unsigned int) 0x3 <<  0) // (MATRIX) USB priority
// -------- MATRIX_PRAS1 : (MATRIX Offset: 0x88) PRAS1 Register -------- 
// -------- MATRIX_PRBS1 : (MATRIX Offset: 0x8c) PRBS1 Register -------- 
// -------- MATRIX_PRAS2 : (MATRIX Offset: 0x90) PRAS2 Register -------- 
// -------- MATRIX_PRBS2 : (MATRIX Offset: 0x94) PRBS2 Register -------- 
// -------- MATRIX_PRAS3 : (MATRIX Offset: 0x98) PRAS3 Register -------- 
// -------- MATRIX_PRBS3 : (MATRIX Offset: 0x9c) PRBS3 Register -------- 
// -------- MATRIX_PRAS4 : (MATRIX Offset: 0xa0) PRAS4 Register -------- 
// -------- MATRIX_PRBS4 : (MATRIX Offset: 0xa4) PRBS4 Register -------- 
// -------- MATRIX_PRAS5 : (MATRIX Offset: 0xa8) PRAS5 Register -------- 
// -------- MATRIX_PRBS5 : (MATRIX Offset: 0xac) PRBS5 Register -------- 
// -------- MATRIX_PRAS6 : (MATRIX Offset: 0xb0) PRAS6 Register -------- 
// -------- MATRIX_PRBS6 : (MATRIX Offset: 0xb4) PRBS6 Register -------- 
// -------- MATRIX_PRAS7 : (MATRIX Offset: 0xb8) PRAS7 Register -------- 
// -------- MATRIX_PRBS7 : (MATRIX Offset: 0xbc) PRBS7 Register -------- 
// -------- MATRIX_MRCR : (MATRIX Offset: 0x100) MRCR Register -------- 
#define AT91C_MATRIX_RCA926I  ((unsigned int) 0x1 <<  0) // (MATRIX) Remap Command Bit for ARM926EJ-S Instruction
#define AT91C_MATRIX_RCA926D  ((unsigned int) 0x1 <<  1) // (MATRIX) Remap Command Bit for ARM926EJ-S Data
#define AT91C_MATRIX_RCB2     ((unsigned int) 0x1 <<  2) // (MATRIX) Remap Command Bit for PDC
#define AT91C_MATRIX_RCB3     ((unsigned int) 0x1 <<  3) // (MATRIX) Remap Command Bit for LCD
#define AT91C_MATRIX_RCB4     ((unsigned int) 0x1 <<  4) // (MATRIX) Remap Command Bit for 2DGC
#define AT91C_MATRIX_RCB5     ((unsigned int) 0x1 <<  5) // (MATRIX) Remap Command Bit for ISI
#define AT91C_MATRIX_RCB6     ((unsigned int) 0x1 <<  6) // (MATRIX) Remap Command Bit for DMA
#define AT91C_MATRIX_RCB7     ((unsigned int) 0x1 <<  7) // (MATRIX) Remap Command Bit for EMAC
#define AT91C_MATRIX_RCB8     ((unsigned int) 0x1 <<  8) // (MATRIX) Remap Command Bit for USB

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
// *****************************************************************************
typedef struct _AT91S_CCFG {
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 CCFG_TCMR; 	//  TCM configuration
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 CCFG_EBI0CSA; 	//  EBI0 Chip Select Assignement Register
	AT91_REG	 CCFG_EBI1CSA; 	//  EBI1 Chip Select Assignement Register
	AT91_REG	 Reserved2[53]; 	// 
	AT91_REG	 CCFG_MATRIXVERSION; 	//  Version Register
} AT91S_CCFG, *AT91PS_CCFG;

// -------- CCFG_TCMR : (CCFG Offset: 0x4) TCM Configuration -------- 
#define AT91C_CCFG_ITCM_SIZE  ((unsigned int) 0xF <<  0) // (CCFG) Size of ITCM enabled memory block
#define 	AT91C_CCFG_ITCM_SIZE_0KB                  ((unsigned int) 0x0) // (CCFG) 0 KB (No ITCM Memory)
#define 	AT91C_CCFG_ITCM_SIZE_16KB                 ((unsigned int) 0x5) // (CCFG) 16 KB
#define 	AT91C_CCFG_ITCM_SIZE_32KB                 ((unsigned int) 0x6) // (CCFG) 32 KB
#define AT91C_CCFG_DTCM_SIZE  ((unsigned int) 0xF <<  4) // (CCFG) Size of DTCM enabled memory block
#define 	AT91C_CCFG_DTCM_SIZE_0KB                  ((unsigned int) 0x0 <<  4) // (CCFG) 0 KB (No DTCM Memory)
#define 	AT91C_CCFG_DTCM_SIZE_16KB                 ((unsigned int) 0x5 <<  4) // (CCFG) 16 KB
#define 	AT91C_CCFG_DTCM_SIZE_32KB                 ((unsigned int) 0x6 <<  4) // (CCFG) 32 KB
#define AT91C_CCFG_RM         ((unsigned int) 0xF <<  8) // (CCFG) Read Margin registers
// -------- CCFG_EBI0CSA : (CCFG Offset: 0x10) EBI0 Chip Select Assignment Register -------- 
#define AT91C_EBI_CS1A        ((unsigned int) 0x1 <<  1) // (CCFG) Chip Select 1 Assignment
#define 	AT91C_EBI_CS1A_SMC                  ((unsigned int) 0x0 <<  1) // (CCFG) Chip Select 1 is assigned to the Static Memory Controller.
#define 	AT91C_EBI_CS1A_SDRAMC               ((unsigned int) 0x1 <<  1) // (CCFG) Chip Select 1 is assigned to the SDRAM Controller.
#define AT91C_EBI_CS3A        ((unsigned int) 0x1 <<  3) // (CCFG) Chip Select 3 Assignment
#define 	AT91C_EBI_CS3A_SMC                  ((unsigned int) 0x0 <<  3) // (CCFG) Chip Select 3 is only assigned to the Static Memory Controller and NCS3 behaves as defined by the SMC.
#define 	AT91C_EBI_CS3A_SM                   ((unsigned int) 0x1 <<  3) // (CCFG) Chip Select 3 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.
#define AT91C_EBI_CS4A        ((unsigned int) 0x1 <<  4) // (CCFG) Chip Select 4 Assignment
#define 	AT91C_EBI_CS4A_SMC                  ((unsigned int) 0x0 <<  4) // (CCFG) Chip Select 4 is only assigned to the Static Memory Controller and NCS4 behaves as defined by the SMC.
#define 	AT91C_EBI_CS4A_CF                   ((unsigned int) 0x1 <<  4) // (CCFG) Chip Select 4 is assigned to the Static Memory Controller and the CompactFlash Logic (first slot) is activated.
#define AT91C_EBI_CS5A        ((unsigned int) 0x1 <<  5) // (CCFG) Chip Select 5 Assignment
#define 	AT91C_EBI_CS5A_SMC                  ((unsigned int) 0x0 <<  5) // (CCFG) Chip Select 5 is only assigned to the Static Memory Controller and NCS5 behaves as defined by the SMC
#define 	AT91C_EBI_CS5A_CF                   ((unsigned int) 0x1 <<  5) // (CCFG) Chip Select 5 is assigned to the Static Memory Controller and the CompactFlash Logic (second slot) is activated.
#define AT91C_EBI_DBPUC       ((unsigned int) 0x1 <<  8) // (CCFG) Data Bus Pull-up Configuration
// -------- CCFG_EBI1CSA : (CCFG Offset: 0x14) EBI1 Chip Select Assignement Register -------- 
#define AT91C_EBI_CS2A        ((unsigned int) 0x1 <<  3) // (CCFG) EBI1 Chip Select 2 Assignment
#define 	AT91C_EBI_CS2A_SMC                  ((unsigned int) 0x0 <<  3) // (CCFG) Chip Select 2 is assigned to the Static Memory Controller.
#define 	AT91C_EBI_CS2A_SM                   ((unsigned int) 0x1 <<  3) // (CCFG) Chip Select 2 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller
// *****************************************************************************
typedef struct _AT91S_PDC {
	AT91_REG	 PDC_RPR; 	// Receive Pointer Register
	AT91_REG	 PDC_RCR; 	// Receive Counter Register
	AT91_REG	 PDC_TPR; 	// Transmit Pointer Register
	AT91_REG	 PDC_TCR; 	// Transmit Counter Register
	AT91_REG	 PDC_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 PDC_RNCR; 	// Receive Next Counter Register
	AT91_REG	 PDC_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 PDC_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 PDC_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 PDC_PTSR; 	// PDC Transfer Status Register
} AT91S_PDC, *AT91PS_PDC;

// -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- 
#define AT91C_PDC_RXTEN       ((unsigned int) 0x1 <<  0) // (PDC) Receiver Transfer Enable
#define AT91C_PDC_RXTDIS      ((unsigned int) 0x1 <<  1) // (PDC) Receiver Transfer Disable
#define AT91C_PDC_TXTEN       ((unsigned int) 0x1 <<  8) // (PDC) Transmitter Transfer Enable
#define AT91C_PDC_TXTDIS      ((unsigned int) 0x1 <<  9) // (PDC) Transmitter Transfer Disable
// -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Debug Unit
// *****************************************************************************
typedef struct _AT91S_DBGU {
	AT91_REG	 DBGU_CR; 	// Control Register
	AT91_REG	 DBGU_MR; 	// Mode Register
	AT91_REG	 DBGU_IER; 	// Interrupt Enable Register
	AT91_REG	 DBGU_IDR; 	// Interrupt Disable Register
	AT91_REG	 DBGU_IMR; 	// Interrupt Mask Register
	AT91_REG	 DBGU_CSR; 	// Channel Status Register
	AT91_REG	 DBGU_RHR; 	// Receiver Holding Register
	AT91_REG	 DBGU_THR; 	// Transmitter Holding Register
	AT91_REG	 DBGU_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 Reserved0[7]; 	// 
	AT91_REG	 DBGU_CIDR; 	// Chip ID Register
	AT91_REG	 DBGU_EXID; 	// Chip ID Extension Register
	AT91_REG	 DBGU_FNTR; 	// Force NTRST Register
	AT91_REG	 Reserved1[45]; 	// 
	AT91_REG	 DBGU_RPR; 	// Receive Pointer Register
	AT91_REG	 DBGU_RCR; 	// Receive Counter Register
	AT91_REG	 DBGU_TPR; 	// Transmit Pointer Register
	AT91_REG	 DBGU_TCR; 	// Transmit Counter Register
	AT91_REG	 DBGU_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 DBGU_RNCR; 	// Receive Next Counter Register
	AT91_REG	 DBGU_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 DBGU_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 DBGU_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 DBGU_PTSR; 	// PDC Transfer Status Register
} AT91S_DBGU, *AT91PS_DBGU;

// -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_US_RSTRX        ((unsigned int) 0x1 <<  2) // (DBGU) Reset Receiver
#define AT91C_US_RSTTX        ((unsigned int) 0x1 <<  3) // (DBGU) Reset Transmitter
#define AT91C_US_RXEN         ((unsigned int) 0x1 <<  4) // (DBGU) Receiver Enable
#define AT91C_US_RXDIS        ((unsigned int) 0x1 <<  5) // (DBGU) Receiver Disable
#define AT91C_US_TXEN         ((unsigned int) 0x1 <<  6) // (DBGU) Transmitter Enable
#define AT91C_US_TXDIS        ((unsigned int) 0x1 <<  7) // (DBGU) Transmitter Disable
#define AT91C_US_RSTSTA       ((unsigned int) 0x1 <<  8) // (DBGU) Reset Status Bits
// -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_US_PAR          ((unsigned int) 0x7 <<  9) // (DBGU) Parity type
#define 	AT91C_US_PAR_EVEN                 ((unsigned int) 0x0 <<  9) // (DBGU) Even Parity
#define 	AT91C_US_PAR_ODD                  ((unsigned int) 0x1 <<  9) // (DBGU) Odd Parity
#define 	AT91C_US_PAR_SPACE                ((unsigned int) 0x2 <<  9) // (DBGU) Parity forced to 0 (Space)
#define 	AT91C_US_PAR_MARK                 ((unsigned int) 0x3 <<  9) // (DBGU) Parity forced to 1 (Mark)
#define 	AT91C_US_PAR_NONE                 ((unsigned int) 0x4 <<  9) // (DBGU) No Parity
#define 	AT91C_US_PAR_MULTI_DROP           ((unsigned int) 0x6 <<  9) // (DBGU) Multi-drop mode
#define AT91C_US_CHMODE       ((unsigned int) 0x3 << 14) // (DBGU) Channel Mode
#define 	AT91C_US_CHMODE_NORMAL               ((unsigned int) 0x0 << 14) // (DBGU) Normal Mode: The USART channel operates as an RX/TX USART.
#define 	AT91C_US_CHMODE_AUTO                 ((unsigned int) 0x1 << 14) // (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin.
#define 	AT91C_US_CHMODE_LOCAL                ((unsigned int) 0x2 << 14) // (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
#define 	AT91C_US_CHMODE_REMOTE               ((unsigned int) 0x3 << 14) // (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin.
// -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_US_RXRDY        ((unsigned int) 0x1 <<  0) // (DBGU) RXRDY Interrupt
#define AT91C_US_TXRDY        ((unsigned int) 0x1 <<  1) // (DBGU) TXRDY Interrupt
#define AT91C_US_ENDRX        ((unsigned int) 0x1 <<  3) // (DBGU) End of Receive Transfer Interrupt
#define AT91C_US_ENDTX        ((unsigned int) 0x1 <<  4) // (DBGU) End of Transmit Interrupt
#define AT91C_US_OVRE         ((unsigned int) 0x1 <<  5) // (DBGU) Overrun Interrupt
#define AT91C_US_FRAME        ((unsigned int) 0x1 <<  6) // (DBGU) Framing Error Interrupt
#define AT91C_US_PARE         ((unsigned int) 0x1 <<  7) // (DBGU) Parity Error Interrupt
#define AT91C_US_TXEMPTY      ((unsigned int) 0x1 <<  9) // (DBGU) TXEMPTY Interrupt
#define AT91C_US_TXBUFE       ((unsigned int) 0x1 << 11) // (DBGU) TXBUFE Interrupt
#define AT91C_US_RXBUFF       ((unsigned int) 0x1 << 12) // (DBGU) RXBUFF Interrupt
#define AT91C_US_COMM_TX      ((unsigned int) 0x1 << 30) // (DBGU) COMM_TX Interrupt
#define AT91C_US_COMM_RX      ((unsigned int) 0x1 << 31) // (DBGU) COMM_RX Interrupt
// -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
// -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
#define AT91C_US_FORCE_NTRST  ((unsigned int) 0x1 <<  0) // (DBGU) Force NTRST in JTAG

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
// *****************************************************************************
typedef struct _AT91S_AIC {
	AT91_REG	 AIC_SMR[32]; 	// Source Mode Register
	AT91_REG	 AIC_SVR[32]; 	// Source Vector Register
	AT91_REG	 AIC_IVR; 	// IRQ Vector Register
	AT91_REG	 AIC_FVR; 	// FIQ Vector Register
	AT91_REG	 AIC_ISR; 	// Interrupt Status Register
	AT91_REG	 AIC_IPR; 	// Interrupt Pending Register
	AT91_REG	 AIC_IMR; 	// Interrupt Mask Register
	AT91_REG	 AIC_CISR; 	// Core Interrupt Status Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 AIC_IECR; 	// Interrupt Enable Command Register
	AT91_REG	 AIC_IDCR; 	// Interrupt Disable Command Register
	AT91_REG	 AIC_ICCR; 	// Interrupt Clear Command Register
	AT91_REG	 AIC_ISCR; 	// Interrupt Set Command Register
	AT91_REG	 AIC_EOICR; 	// End of Interrupt Command Register
	AT91_REG	 AIC_SPU; 	// Spurious Vector Register
	AT91_REG	 AIC_DCR; 	// Debug Control Register (Protect)
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 AIC_FFER; 	// Fast Forcing Enable Register
	AT91_REG	 AIC_FFDR; 	// Fast Forcing Disable Register
	AT91_REG	 AIC_FFSR; 	// Fast Forcing Status Register
} AT91S_AIC, *AT91PS_AIC;

// -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
#define AT91C_AIC_PRIOR       ((unsigned int) 0x7 <<  0) // (AIC) Priority Level
#define 	AT91C_AIC_PRIOR_LOWEST               ((unsigned int) 0x0) // (AIC) Lowest priority level
#define 	AT91C_AIC_PRIOR_HIGHEST              ((unsigned int) 0x7) // (AIC) Highest priority level
#define AT91C_AIC_SRCTYPE     ((unsigned int) 0x3 <<  5) // (AIC) Interrupt Source Type
#define 	AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE  ((unsigned int) 0x0 <<  5) // (AIC) Internal Sources Code Label Level Sensitive
#define 	AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED   ((unsigned int) 0x1 <<  5) // (AIC) Internal Sources Code Label Edge triggered
#define 	AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL       ((unsigned int) 0x2 <<  5) // (AIC) External Sources Code Label High-level Sensitive
#define 	AT91C_AIC_SRCTYPE_EXT_POSITIVE_EDGE    ((unsigned int) 0x3 <<  5) // (AIC) External Sources Code Label Positive Edge triggered
// -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
#define AT91C_AIC_NFIQ        ((unsigned int) 0x1 <<  0) // (AIC) NFIQ Status
#define AT91C_AIC_NIRQ        ((unsigned int) 0x1 <<  1) // (AIC) NIRQ Status
// -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
#define AT91C_AIC_DCR_PROT    ((unsigned int) 0x1 <<  0) // (AIC) Protection Mode
#define AT91C_AIC_DCR_GMSK    ((unsigned int) 0x1 <<  1) // (AIC) General Mask

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
// *****************************************************************************
typedef struct _AT91S_PIO {
	AT91_REG	 PIO_PER; 	// PIO Enable Register
	AT91_REG	 PIO_PDR; 	// PIO Disable Register
	AT91_REG	 PIO_PSR; 	// PIO Status Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PIO_OER; 	// Output Enable Register
	AT91_REG	 PIO_ODR; 	// Output Disable Registerr
	AT91_REG	 PIO_OSR; 	// Output Status Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PIO_IFER; 	// Input Filter Enable Register
	AT91_REG	 PIO_IFDR; 	// Input Filter Disable Register
	AT91_REG	 PIO_IFSR; 	// Input Filter Status Register
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 PIO_SODR; 	// Set Output Data Register
	AT91_REG	 PIO_CODR; 	// Clear Output Data Register
	AT91_REG	 PIO_ODSR; 	// Output Data Status Register
	AT91_REG	 PIO_PDSR; 	// Pin Data Status Register
	AT91_REG	 PIO_IER; 	// Interrupt Enable Register
	AT91_REG	 PIO_IDR; 	// Interrupt Disable Register
	AT91_REG	 PIO_IMR; 	// Interrupt Mask Register
	AT91_REG	 PIO_ISR; 	// Interrupt Status Register
	AT91_REG	 PIO_MDER; 	// Multi-driver Enable Register
	AT91_REG	 PIO_MDDR; 	// Multi-driver Disable Register
	AT91_REG	 PIO_MDSR; 	// Multi-driver Status Register
	AT91_REG	 Reserved3[1]; 	// 
	AT91_REG	 PIO_PPUDR; 	// Pull-up Disable Register
	AT91_REG	 PIO_PPUER; 	// Pull-up Enable Register
	AT91_REG	 PIO_PPUSR; 	// Pull-up Status Register
	AT91_REG	 Reserved4[1]; 	// 
	AT91_REG	 PIO_ASR; 	// Select A Register
	AT91_REG	 PIO_BSR; 	// Select B Register
	AT91_REG	 PIO_ABSR; 	// AB Select Status Register
	AT91_REG	 Reserved5[9]; 	// 
	AT91_REG	 PIO_OWER; 	// Output Write Enable Register
	AT91_REG	 PIO_OWDR; 	// Output Write Disable Register
	AT91_REG	 PIO_OWSR; 	// Output Write Status Register
} AT91S_PIO, *AT91PS_PIO;


// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Clock Generator Controler
// *****************************************************************************
typedef struct _AT91S_CKGR {
	AT91_REG	 CKGR_MOR; 	// Main Oscillator Register
	AT91_REG	 CKGR_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 CKGR_PLLAR; 	// PLL A Register
	AT91_REG	 CKGR_PLLBR; 	// PLL B Register
} AT91S_CKGR, *AT91PS_CKGR;

// -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- 
#define AT91C_CKGR_MOSCEN     ((unsigned int) 0x1 <<  0) // (CKGR) Main Oscillator Enable
#define AT91C_CKGR_OSCBYPASS  ((unsigned int) 0x1 <<  1) // (CKGR) Main Oscillator Bypass
#define AT91C_CKGR_OSCOUNT    ((unsigned int) 0xFF <<  8) // (CKGR) Main Oscillator Start-up Time
// -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
#define AT91C_CKGR_MAINF      ((unsigned int) 0xFFFF <<  0) // (CKGR) Main Clock Frequency
#define AT91C_CKGR_MAINRDY    ((unsigned int) 0x1 << 16) // (CKGR) Main Clock Ready
// -------- CKGR_PLLAR : (CKGR Offset: 0x8) PLL A Register -------- 
#define AT91C_CKGR_DIVA       ((unsigned int) 0xFF <<  0) // (CKGR) Divider A Selected
#define 	AT91C_CKGR_DIVA_0                    ((unsigned int) 0x0) // (CKGR) Divider A output is 0
#define 	AT91C_CKGR_DIVA_BYPASS               ((unsigned int) 0x1) // (CKGR) Divider A is bypassed
#define AT91C_CKGR_PLLACOUNT  ((unsigned int) 0x3F <<  8) // (CKGR) PLL A Counter
#define AT91C_CKGR_OUTA       ((unsigned int) 0x3 << 14) // (CKGR) PLL A Output Frequency Range
#define 	AT91C_CKGR_OUTA_0                    ((unsigned int) 0x0 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_1                    ((unsigned int) 0x1 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_2                    ((unsigned int) 0x2 << 14) // (CKGR) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_3                    ((unsigned int) 0x3 << 14) // (CKGR) Please refer to the PLLA datasheet
#define AT91C_CKGR_MULA       ((unsigned int) 0x7FF << 16) // (CKGR) PLL A Multiplier
#define AT91C_CKGR_SRCA       ((unsigned int) 0x1 << 29) // (CKGR) 
// -------- CKGR_PLLBR : (CKGR Offset: 0xc) PLL B Register -------- 
#define AT91C_CKGR_DIVB       ((unsigned int) 0xFF <<  0) // (CKGR) Divider B Selected
#define 	AT91C_CKGR_DIVB_0                    ((unsigned int) 0x0) // (CKGR) Divider B output is 0
#define 	AT91C_CKGR_DIVB_BYPASS               ((unsigned int) 0x1) // (CKGR) Divider B is bypassed
#define AT91C_CKGR_PLLBCOUNT  ((unsigned int) 0x3F <<  8) // (CKGR) PLL B Counter
#define AT91C_CKGR_OUTB       ((unsigned int) 0x3 << 14) // (CKGR) PLL B Output Frequency Range
#define 	AT91C_CKGR_OUTB_0                    ((unsigned int) 0x0 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_1                    ((unsigned int) 0x1 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_2                    ((unsigned int) 0x2 << 14) // (CKGR) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_3                    ((unsigned int) 0x3 << 14) // (CKGR) Please refer to the PLLB datasheet
#define AT91C_CKGR_MULB       ((unsigned int) 0x7FF << 16) // (CKGR) PLL B Multiplier
#define AT91C_CKGR_USBDIV     ((unsigned int) 0x3 << 28) // (CKGR) Divider for USB Clocks
#define 	AT91C_CKGR_USBDIV_0                    ((unsigned int) 0x0 << 28) // (CKGR) Divider output is PLL clock output
#define 	AT91C_CKGR_USBDIV_1                    ((unsigned int) 0x1 << 28) // (CKGR) Divider output is PLL clock output divided by 2
#define 	AT91C_CKGR_USBDIV_2                    ((unsigned int) 0x2 << 28) // (CKGR) Divider output is PLL clock output divided by 4

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Power Management Controler
// *****************************************************************************
typedef struct _AT91S_PMC {
	AT91_REG	 PMC_SCER; 	// System Clock Enable Register
	AT91_REG	 PMC_SCDR; 	// System Clock Disable Register
	AT91_REG	 PMC_SCSR; 	// System Clock Status Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 PMC_PCER; 	// Peripheral Clock Enable Register
	AT91_REG	 PMC_PCDR; 	// Peripheral Clock Disable Register
	AT91_REG	 PMC_PCSR; 	// Peripheral Clock Status Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 PMC_MOR; 	// Main Oscillator Register
	AT91_REG	 PMC_MCFR; 	// Main Clock  Frequency Register
	AT91_REG	 PMC_PLLAR; 	// PLL A Register
	AT91_REG	 PMC_PLLBR; 	// PLL B Register
	AT91_REG	 PMC_MCKR; 	// Master Clock Register
	AT91_REG	 Reserved2[3]; 	// 
	AT91_REG	 PMC_PCKR[8]; 	// Programmable Clock Register
	AT91_REG	 PMC_IER; 	// Interrupt Enable Register
	AT91_REG	 PMC_IDR; 	// Interrupt Disable Register
	AT91_REG	 PMC_SR; 	// Status Register
	AT91_REG	 PMC_IMR; 	// Interrupt Mask Register
} AT91S_PMC, *AT91PS_PMC;

// -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
#define AT91C_PMC_PCK         ((unsigned int) 0x1 <<  0) // (PMC) Processor Clock
#define AT91C_PMC_OTG         ((unsigned int) 0x1 <<  5) // (PMC) USB OTG Clock
#define AT91C_PMC_UHP         ((unsigned int) 0x1 <<  6) // (PMC) USB Host Port Clock
#define AT91C_PMC_UDP         ((unsigned int) 0x1 <<  7) // (PMC) USB Device Port Clock
#define AT91C_PMC_PCK0        ((unsigned int) 0x1 <<  8) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK1        ((unsigned int) 0x1 <<  9) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK2        ((unsigned int) 0x1 << 10) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK3        ((unsigned int) 0x1 << 11) // (PMC) Programmable Clock Output
// -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
// -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
// -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
// -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
// -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
// -------- CKGR_PLLBR : (PMC Offset: 0x2c) PLL B Register -------- 
// -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
#define AT91C_PMC_CSS         ((unsigned int) 0x3 <<  0) // (PMC) Programmable Clock Selection
#define 	AT91C_PMC_CSS_SLOW_CLK             ((unsigned int) 0x0) // (PMC) Slow Clock is selected
#define 	AT91C_PMC_CSS_MAIN_CLK             ((unsigned int) 0x1) // (PMC) Main Clock is selected
#define 	AT91C_PMC_CSS_PLLA_CLK             ((unsigned int) 0x2) // (PMC) Clock from PLL A is selected
#define 	AT91C_PMC_CSS_PLLB_CLK             ((unsigned int) 0x3) // (PMC) Clock from PLL B is selected
#define AT91C_PMC_PRES        ((unsigned int) 0x7 <<  2) // (PMC) Programmable Clock Prescaler
#define 	AT91C_PMC_PRES_CLK                  ((unsigned int) 0x0 <<  2) // (PMC) Selected clock
#define 	AT91C_PMC_PRES_CLK_2                ((unsigned int) 0x1 <<  2) // (PMC) Selected clock divided by 2
#define 	AT91C_PMC_PRES_CLK_4                ((unsigned int) 0x2 <<  2) // (PMC) Selected clock divided by 4
#define 	AT91C_PMC_PRES_CLK_8                ((unsigned int) 0x3 <<  2) // (PMC) Selected clock divided by 8
#define 	AT91C_PMC_PRES_CLK_16               ((unsigned int) 0x4 <<  2) // (PMC) Selected clock divided by 16
#define 	AT91C_PMC_PRES_CLK_32               ((unsigned int) 0x5 <<  2) // (PMC) Selected clock divided by 32
#define 	AT91C_PMC_PRES_CLK_64               ((unsigned int) 0x6 <<  2) // (PMC) Selected clock divided by 64
#define AT91C_PMC_MDIV        ((unsigned int) 0x3 <<  8) // (PMC) Master Clock Division
#define 	AT91C_PMC_MDIV_1                    ((unsigned int) 0x0 <<  8) // (PMC) The master clock and the processor clock are the same
#define 	AT91C_PMC_MDIV_2                    ((unsigned int) 0x1 <<  8) // (PMC) The processor clock is twice as fast as the master clock
#define 	AT91C_PMC_MDIV_3                    ((unsigned int) 0x2 <<  8) // (PMC) The processor clock is four times faster than the master clock
// -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
// -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
#define AT91C_PMC_MOSCS       ((unsigned int) 0x1 <<  0) // (PMC) MOSC Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKA       ((unsigned int) 0x1 <<  1) // (PMC) PLL A Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKB       ((unsigned int) 0x1 <<  2) // (PMC) PLL B Status/Enable/Disable/Mask
#define AT91C_PMC_MCKRDY      ((unsigned int) 0x1 <<  3) // (PMC) Master Clock Status/Enable/Disable/Mask
#define AT91C_PMC_PCK0RDY     ((unsigned int) 0x1 <<  8) // (PMC) PCK0_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK1RDY     ((unsigned int) 0x1 <<  9) // (PMC) PCK1_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK2RDY     ((unsigned int) 0x1 << 10) // (PMC) PCK2_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCK3RDY     ((unsigned int) 0x1 << 11) // (PMC) PCK3_RDY Status/Enable/Disable/Mask
// -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
// -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
// -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Reset Controller Interface
// *****************************************************************************
typedef struct _AT91S_RSTC {
	AT91_REG	 RSTC_RCR; 	// Reset Control Register
	AT91_REG	 RSTC_RSR; 	// Reset Status Register
	AT91_REG	 RSTC_RMR; 	// Reset Mode Register
} AT91S_RSTC, *AT91PS_RSTC;

// -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- 
#define AT91C_RSTC_PROCRST    ((unsigned int) 0x1 <<  0) // (RSTC) Processor Reset
#define AT91C_RSTC_ICERST     ((unsigned int) 0x1 <<  1) // (RSTC) ICE Interface Reset
#define AT91C_RSTC_PERRST     ((unsigned int) 0x1 <<  2) // (RSTC) Peripheral Reset
#define AT91C_RSTC_EXTRST     ((unsigned int) 0x1 <<  3) // (RSTC) External Reset
#define AT91C_RSTC_KEY        ((unsigned int) 0xFF << 24) // (RSTC) Password
// -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- 
#define AT91C_RSTC_URSTS      ((unsigned int) 0x1 <<  0) // (RSTC) User Reset Status
#define AT91C_RSTC_RSTTYP     ((unsigned int) 0x7 <<  8) // (RSTC) Reset Type
#define 	AT91C_RSTC_RSTTYP_GENERAL              ((unsigned int) 0x0 <<  8) // (RSTC) General reset. Both VDDCORE and VDDBU rising.
#define 	AT91C_RSTC_RSTTYP_WAKEUP               ((unsigned int) 0x1 <<  8) // (RSTC) WakeUp Reset. VDDCORE rising.
#define 	AT91C_RSTC_RSTTYP_WATCHDOG             ((unsigned int) 0x2 <<  8) // (RSTC) Watchdog Reset. Watchdog overflow occured.
#define 	AT91C_RSTC_RSTTYP_SOFTWARE             ((unsigned int) 0x3 <<  8) // (RSTC) Software Reset. Processor reset required by the software.
#define 	AT91C_RSTC_RSTTYP_USER                 ((unsigned int) 0x4 <<  8) // (RSTC) User Reset. NRST pin detected low.
#define AT91C_RSTC_NRSTL      ((unsigned int) 0x1 << 16) // (RSTC) NRST pin level
#define AT91C_RSTC_SRCMP      ((unsigned int) 0x1 << 17) // (RSTC) Software Reset Command in Progress.
// -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
#define AT91C_RSTC_URSTEN     ((unsigned int) 0x1 <<  0) // (RSTC) User Reset Enable
#define AT91C_RSTC_URSTIEN    ((unsigned int) 0x1 <<  4) // (RSTC) User Reset Interrupt Enable
#define AT91C_RSTC_ERSTL      ((unsigned int) 0xF <<  8) // (RSTC) User Reset Enable

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Shut Down Controller Interface
// *****************************************************************************
typedef struct _AT91S_SHDWC {
	AT91_REG	 SHDWC_SHCR; 	// Shut Down Control Register
	AT91_REG	 SHDWC_SHMR; 	// Shut Down Mode Register
	AT91_REG	 SHDWC_SHSR; 	// Shut Down Status Register
} AT91S_SHDWC, *AT91PS_SHDWC;

// -------- SHDWC_SHCR : (SHDWC Offset: 0x0) Shut Down Control Register -------- 
#define AT91C_SHDWC_SHDW      ((unsigned int) 0x1 <<  0) // (SHDWC) Processor Reset
#define AT91C_SHDWC_KEY       ((unsigned int) 0xFF << 24) // (SHDWC) Shut down KEY Password
// -------- SHDWC_SHMR : (SHDWC Offset: 0x4) Shut Down Mode Register -------- 
#define AT91C_SHDWC_WKMODE0   ((unsigned int) 0x3 <<  0) // (SHDWC) Wake Up 0 Mode Selection
#define 	AT91C_SHDWC_WKMODE0_NONE                 ((unsigned int) 0x0) // (SHDWC) None. No detection is performed on the wake up input.
#define 	AT91C_SHDWC_WKMODE0_HIGH                 ((unsigned int) 0x1) // (SHDWC) High Level.
#define 	AT91C_SHDWC_WKMODE0_LOW                  ((unsigned int) 0x2) // (SHDWC) Low Level.
#define 	AT91C_SHDWC_WKMODE0_ANYLEVEL             ((unsigned int) 0x3) // (SHDWC) Any level change.
#define AT91C_SHDWC_CPTWK0    ((unsigned int) 0xF <<  4) // (SHDWC) Counter On Wake Up 0
#define AT91C_SHDWC_RTTWKEN   ((unsigned int) 0x1 << 16) // (SHDWC) Real Time Timer Wake Up Enable
// -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
#define AT91C_SHDWC_WAKEUP0   ((unsigned int) 0x1 <<  0) // (SHDWC) Wake Up 0 Status
#define AT91C_SHDWC_RTTWK     ((unsigned int) 0x1 << 16) // (SHDWC) Real Time Timer wake Up

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
// *****************************************************************************
typedef struct _AT91S_RTTC {
	AT91_REG	 RTTC_RTMR; 	// Real-time Mode Register
	AT91_REG	 RTTC_RTAR; 	// Real-time Alarm Register
	AT91_REG	 RTTC_RTVR; 	// Real-time Value Register
	AT91_REG	 RTTC_RTSR; 	// Real-time Status Register
} AT91S_RTTC, *AT91PS_RTTC;

// -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
#define AT91C_RTTC_RTPRES     ((unsigned int) 0xFFFF <<  0) // (RTTC) Real-time Timer Prescaler Value
#define AT91C_RTTC_ALMIEN     ((unsigned int) 0x1 << 16) // (RTTC) Alarm Interrupt Enable
#define AT91C_RTTC_RTTINCIEN  ((unsigned int) 0x1 << 17) // (RTTC) Real Time Timer Increment Interrupt Enable
#define AT91C_RTTC_RTTRST     ((unsigned int) 0x1 << 18) // (RTTC) Real Time Timer Restart
// -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
#define AT91C_RTTC_ALMV       ((unsigned int) 0x0 <<  0) // (RTTC) Alarm Value
// -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
#define AT91C_RTTC_CRTV       ((unsigned int) 0x0 <<  0) // (RTTC) Current Real-time Value
// -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
#define AT91C_RTTC_ALMS       ((unsigned int) 0x1 <<  0) // (RTTC) Real-time Alarm Status
#define AT91C_RTTC_RTTINC     ((unsigned int) 0x1 <<  1) // (RTTC) Real-time Timer Increment

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface
// *****************************************************************************
typedef struct _AT91S_PITC {
	AT91_REG	 PITC_PIMR; 	// Period Interval Mode Register
	AT91_REG	 PITC_PISR; 	// Period Interval Status Register
	AT91_REG	 PITC_PIVR; 	// Period Interval Value Register
	AT91_REG	 PITC_PIIR; 	// Period Interval Image Register
} AT91S_PITC, *AT91PS_PITC;

// -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- 
#define AT91C_PITC_PIV        ((unsigned int) 0xFFFFF <<  0) // (PITC) Periodic Interval Value
#define AT91C_PITC_PITEN      ((unsigned int) 0x1 << 24) // (PITC) Periodic Interval Timer Enabled
#define AT91C_PITC_PITIEN     ((unsigned int) 0x1 << 25) // (PITC) Periodic Interval Timer Interrupt Enable
// -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- 
#define AT91C_PITC_PITS       ((unsigned int) 0x1 <<  0) // (PITC) Periodic Interval Timer Status
// -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- 
#define AT91C_PITC_CPIV       ((unsigned int) 0xFFFFF <<  0) // (PITC) Current Periodic Interval Value
#define AT91C_PITC_PICNT      ((unsigned int) 0xFFF << 20) // (PITC) Periodic Interval Counter
// -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
// *****************************************************************************
typedef struct _AT91S_WDTC {
	AT91_REG	 WDTC_WDCR; 	// Watchdog Control Register
	AT91_REG	 WDTC_WDMR; 	// Watchdog Mode Register
	AT91_REG	 WDTC_WDSR; 	// Watchdog Status Register
} AT91S_WDTC, *AT91PS_WDTC;

// -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- 
#define AT91C_WDTC_WDRSTT     ((unsigned int) 0x1 <<  0) // (WDTC) Watchdog Restart
#define AT91C_WDTC_KEY        ((unsigned int) 0xFF << 24) // (WDTC) Watchdog KEY Password
// -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- 
#define AT91C_WDTC_WDV        ((unsigned int) 0xFFF <<  0) // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDFIEN     ((unsigned int) 0x1 << 12) // (WDTC) Watchdog Fault Interrupt Enable
#define AT91C_WDTC_WDRSTEN    ((unsigned int) 0x1 << 13) // (WDTC) Watchdog Reset Enable
#define AT91C_WDTC_WDRPROC    ((unsigned int) 0x1 << 14) // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDDIS      ((unsigned int) 0x1 << 15) // (WDTC) Watchdog Disable
#define AT91C_WDTC_WDD        ((unsigned int) 0xFFF << 16) // (WDTC) Watchdog Delta Value
#define AT91C_WDTC_WDDBGHLT   ((unsigned int) 0x1 << 28) // (WDTC) Watchdog Debug Halt
#define AT91C_WDTC_WDIDLEHLT  ((unsigned int) 0x1 << 29) // (WDTC) Watchdog Idle Halt
// -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- 
#define AT91C_WDTC_WDUNF      ((unsigned int) 0x1 <<  0) // (WDTC) Watchdog Underflow
#define AT91C_WDTC_WDERR      ((unsigned int) 0x1 <<  1) // (WDTC) Watchdog Error

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
// *****************************************************************************
typedef struct _AT91S_TC {
	AT91_REG	 TC_CCR; 	// Channel Control Register
	AT91_REG	 TC_CMR; 	// Channel Mode Register (Capture Mode / Waveform Mode)
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 TC_CV; 	// Counter Value
	AT91_REG	 TC_RA; 	// Register A
	AT91_REG	 TC_RB; 	// Register B
	AT91_REG	 TC_RC; 	// Register C
	AT91_REG	 TC_SR; 	// Status Register
	AT91_REG	 TC_IER; 	// Interrupt Enable Register
	AT91_REG	 TC_IDR; 	// Interrupt Disable Register
	AT91_REG	 TC_IMR; 	// Interrupt Mask Register
} AT91S_TC, *AT91PS_TC;

// -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
#define AT91C_TC_CLKEN        ((unsigned int) 0x1 <<  0) // (TC) Counter Clock Enable Command
#define AT91C_TC_CLKDIS       ((unsigned int) 0x1 <<  1) // (TC) Counter Clock Disable Command
#define AT91C_TC_SWTRG        ((unsigned int) 0x1 <<  2) // (TC) Software Trigger Command
// -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
#define AT91C_TC_CLKS         ((unsigned int) 0x7 <<  0) // (TC) Clock Selection
#define 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     ((unsigned int) 0x0) // (TC) Clock selected: TIMER_DIV1_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     ((unsigned int) 0x1) // (TC) Clock selected: TIMER_DIV2_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     ((unsigned int) 0x2) // (TC) Clock selected: TIMER_DIV3_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     ((unsigned int) 0x3) // (TC) Clock selected: TIMER_DIV4_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     ((unsigned int) 0x4) // (TC) Clock selected: TIMER_DIV5_CLOCK
#define 	AT91C_TC_CLKS_XC0                  ((unsigned int) 0x5) // (TC) Clock selected: XC0
#define 	AT91C_TC_CLKS_XC1                  ((unsigned int) 0x6) // (TC) Clock selected: XC1
#define 	AT91C_TC_CLKS_XC2                  ((unsigned int) 0x7) // (TC) Clock selected: XC2
#define AT91C_TC_CLKI         ((unsigned int) 0x1 <<  3) // (TC) Clock Invert
#define AT91C_TC_BURST        ((unsigned int) 0x3 <<  4) // (TC) Burst Signal Selection
#define 	AT91C_TC_BURST_NONE                 ((unsigned int) 0x0 <<  4) // (TC) The clock is not gated by an external signal
#define 	AT91C_TC_BURST_XC0                  ((unsigned int) 0x1 <<  4) // (TC) XC0 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC1                  ((unsigned int) 0x2 <<  4) // (TC) XC1 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC2                  ((unsigned int) 0x3 <<  4) // (TC) XC2 is ANDed with the selected clock
#define AT91C_TC_CPCSTOP      ((unsigned int) 0x1 <<  6) // (TC) Counter Clock Stopped with RC Compare
#define AT91C_TC_LDBSTOP      ((unsigned int) 0x1 <<  6) // (TC) Counter Clock Stopped with RB Loading
#define AT91C_TC_CPCDIS       ((unsigned int) 0x1 <<  7) // (TC) Counter Clock Disable with RC Compare
#define AT91C_TC_LDBDIS       ((unsigned int) 0x1 <<  7) // (TC) Counter Clock Disabled with RB Loading
#define AT91C_TC_ETRGEDG      ((unsigned int) 0x3 <<  8) // (TC) External Trigger Edge Selection
#define 	AT91C_TC_ETRGEDG_NONE                 ((unsigned int) 0x0 <<  8) // (TC) Edge: None
#define 	AT91C_TC_ETRGEDG_RISING               ((unsigned int) 0x1 <<  8) // (TC) Edge: rising edge
#define 	AT91C_TC_ETRGEDG_FALLING              ((unsigned int) 0x2 <<  8) // (TC) Edge: falling edge
#define 	AT91C_TC_ETRGEDG_BOTH                 ((unsigned int) 0x3 <<  8) // (TC) Edge: each edge
#define AT91C_TC_EEVTEDG      ((unsigned int) 0x3 <<  8) // (TC) External Event Edge Selection
#define 	AT91C_TC_EEVTEDG_NONE                 ((unsigned int) 0x0 <<  8) // (TC) Edge: None
#define 	AT91C_TC_EEVTEDG_RISING               ((unsigned int) 0x1 <<  8) // (TC) Edge: rising edge
#define 	AT91C_TC_EEVTEDG_FALLING              ((unsigned int) 0x2 <<  8) // (TC) Edge: falling edge
#define 	AT91C_TC_EEVTEDG_BOTH                 ((unsigned int) 0x3 <<  8) // (TC) Edge: each edge
#define AT91C_TC_EEVT         ((unsigned int) 0x3 << 10) // (TC) External Event  Selection
#define 	AT91C_TC_EEVT_TIOB                 ((unsigned int) 0x0 << 10) // (TC) Signal selected as external event: TIOB TIOB direction: input
#define 	AT91C_TC_EEVT_XC0                  ((unsigned int) 0x1 << 10) // (TC) Signal selected as external event: XC0 TIOB direction: output
#define 	AT91C_TC_EEVT_XC1                  ((unsigned int) 0x2 << 10) // (TC) Signal selected as external event: XC1 TIOB direction: output
#define 	AT91C_TC_EEVT_XC2                  ((unsigned int) 0x3 << 10) // (TC) Signal selected as external event: XC2 TIOB direction: output
#define AT91C_TC_ABETRG       ((unsigned int) 0x1 << 10) // (TC) TIOA or TIOB External Trigger Selection
#define AT91C_TC_ENETRG       ((unsigned int) 0x1 << 12) // (TC) External Event Trigger enable
#define AT91C_TC_WAVESEL      ((unsigned int) 0x3 << 13) // (TC) Waveform  Selection
#define 	AT91C_TC_WAVESEL_UP                   ((unsigned int) 0x0 << 13) // (TC) UP mode without atomatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN               ((unsigned int) 0x1 << 13) // (TC) UPDOWN mode without automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UP_AUTO              ((unsigned int) 0x2 << 13) // (TC) UP mode with automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN_AUTO          ((unsigned int) 0x3 << 13) // (TC) UPDOWN mode with automatic trigger on RC Compare
#define AT91C_TC_CPCTRG       ((unsigned int) 0x1 << 14) // (TC) RC Compare Trigger Enable
#define AT91C_TC_WAVE         ((unsigned int) 0x1 << 15) // (TC) 
#define AT91C_TC_ACPA         ((unsigned int) 0x3 << 16) // (TC) RA Compare Effect on TIOA
#define 	AT91C_TC_ACPA_NONE                 ((unsigned int) 0x0 << 16) // (TC) Effect: none
#define 	AT91C_TC_ACPA_SET                  ((unsigned int) 0x1 << 16) // (TC) Effect: set
#define 	AT91C_TC_ACPA_CLEAR                ((unsigned int) 0x2 << 16) // (TC) Effect: clear
#define 	AT91C_TC_ACPA_TOGGLE               ((unsigned int) 0x3 << 16) // (TC) Effect: toggle
#define AT91C_TC_LDRA         ((unsigned int) 0x3 << 16) // (TC) RA Loading Selection
#define 	AT91C_TC_LDRA_NONE                 ((unsigned int) 0x0 << 16) // (TC) Edge: None
#define 	AT91C_TC_LDRA_RISING               ((unsigned int) 0x1 << 16) // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRA_FALLING              ((unsigned int) 0x2 << 16) // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRA_BOTH                 ((unsigned int) 0x3 << 16) // (TC) Edge: each edge of TIOA
#define AT91C_TC_ACPC         ((unsigned int) 0x3 << 18) // (TC) RC Compare Effect on TIOA
#define 	AT91C_TC_ACPC_NONE                 ((unsigned int) 0x0 << 18) // (TC) Effect: none
#define 	AT91C_TC_ACPC_SET                  ((unsigned int) 0x1 << 18) // (TC) Effect: set
#define 	AT91C_TC_ACPC_CLEAR                ((unsigned int) 0x2 << 18) // (TC) Effect: clear
#define 	AT91C_TC_ACPC_TOGGLE               ((unsigned int) 0x3 << 18) // (TC) Effect: toggle
#define AT91C_TC_LDRB         ((unsigned int) 0x3 << 18) // (TC) RB Loading Selection
#define 	AT91C_TC_LDRB_NONE                 ((unsigned int) 0x0 << 18) // (TC) Edge: None
#define 	AT91C_TC_LDRB_RISING               ((unsigned int) 0x1 << 18) // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRB_FALLING              ((unsigned int) 0x2 << 18) // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRB_BOTH                 ((unsigned int) 0x3 << 18) // (TC) Edge: each edge of TIOA
#define AT91C_TC_AEEVT        ((unsigned int) 0x3 << 20) // (TC) External Event Effect on TIOA
#define 	AT91C_TC_AEEVT_NONE                 ((unsigned int) 0x0 << 20) // (TC) Effect: none
#define 	AT91C_TC_AEEVT_SET                  ((unsigned int) 0x1 << 20) // (TC) Effect: set
#define 	AT91C_TC_AEEVT_CLEAR                ((unsigned int) 0x2 << 20) // (TC) Effect: clear
#define 	AT91C_TC_AEEVT_TOGGLE               ((unsigned int) 0x3 << 20) // (TC) Effect: toggle
#define AT91C_TC_ASWTRG       ((unsigned int) 0x3 << 22) // (TC) Software Trigger Effect on TIOA
#define 	AT91C_TC_ASWTRG_NONE                 ((unsigned int) 0x0 << 22) // (TC) Effect: none
#define 	AT91C_TC_ASWTRG_SET                  ((unsigned int) 0x1 << 22) // (TC) Effect: set
#define 	AT91C_TC_ASWTRG_CLEAR                ((unsigned int) 0x2 << 22) // (TC) Effect: clear
#define 	AT91C_TC_ASWTRG_TOGGLE               ((unsigned int) 0x3 << 22) // (TC) Effect: toggle
#define AT91C_TC_BCPB         ((unsigned int) 0x3 << 24) // (TC) RB Compare Effect on TIOB
#define 	AT91C_TC_BCPB_NONE                 ((unsigned int) 0x0 << 24) // (TC) Effect: none
#define 	AT91C_TC_BCPB_SET                  ((unsigned int) 0x1 << 24) // (TC) Effect: set
#define 	AT91C_TC_BCPB_CLEAR                ((unsigned int) 0x2 << 24) // (TC) Effect: clear
#define 	AT91C_TC_BCPB_TOGGLE               ((unsigned int) 0x3 << 24) // (TC) Effect: toggle
#define AT91C_TC_BCPC         ((unsigned int) 0x3 << 26) // (TC) RC Compare Effect on TIOB
#define 	AT91C_TC_BCPC_NONE                 ((unsigned int) 0x0 << 26) // (TC) Effect: none
#define 	AT91C_TC_BCPC_SET                  ((unsigned int) 0x1 << 26) // (TC) Effect: set
#define 	AT91C_TC_BCPC_CLEAR                ((unsigned int) 0x2 << 26) // (TC) Effect: clear
#define 	AT91C_TC_BCPC_TOGGLE               ((unsigned int) 0x3 << 26) // (TC) Effect: toggle
#define AT91C_TC_BEEVT        ((unsigned int) 0x3 << 28) // (TC) External Event Effect on TIOB
#define 	AT91C_TC_BEEVT_NONE                 ((unsigned int) 0x0 << 28) // (TC) Effect: none
#define 	AT91C_TC_BEEVT_SET                  ((unsigned int) 0x1 << 28) // (TC) Effect: set
#define 	AT91C_TC_BEEVT_CLEAR                ((unsigned int) 0x2 << 28) // (TC) Effect: clear
#define 	AT91C_TC_BEEVT_TOGGLE               ((unsigned int) 0x3 << 28) // (TC) Effect: toggle
#define AT91C_TC_BSWTRG       ((unsigned int) 0x3 << 30) // (TC) Software Trigger Effect on TIOB
#define 	AT91C_TC_BSWTRG_NONE                 ((unsigned int) 0x0 << 30) // (TC) Effect: none
#define 	AT91C_TC_BSWTRG_SET                  ((unsigned int) 0x1 << 30) // (TC) Effect: set
#define 	AT91C_TC_BSWTRG_CLEAR                ((unsigned int) 0x2 << 30) // (TC) Effect: clear
#define 	AT91C_TC_BSWTRG_TOGGLE               ((unsigned int) 0x3 << 30) // (TC) Effect: toggle
// -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
#define AT91C_TC_COVFS        ((unsigned int) 0x1 <<  0) // (TC) Counter Overflow
#define AT91C_TC_LOVRS        ((unsigned int) 0x1 <<  1) // (TC) Load Overrun
#define AT91C_TC_CPAS         ((unsigned int) 0x1 <<  2) // (TC) RA Compare
#define AT91C_TC_CPBS         ((unsigned int) 0x1 <<  3) // (TC) RB Compare
#define AT91C_TC_CPCS         ((unsigned int) 0x1 <<  4) // (TC) RC Compare
#define AT91C_TC_LDRAS        ((unsigned int) 0x1 <<  5) // (TC) RA Loading
#define AT91C_TC_LDRBS        ((unsigned int) 0x1 <<  6) // (TC) RB Loading
#define AT91C_TC_ETRGS        ((unsigned int) 0x1 <<  7) // (TC) External Trigger
#define AT91C_TC_CLKSTA       ((unsigned int) 0x1 << 16) // (TC) Clock Enabling
#define AT91C_TC_MTIOA        ((unsigned int) 0x1 << 17) // (TC) TIOA Mirror
#define AT91C_TC_MTIOB        ((unsigned int) 0x1 << 18) // (TC) TIOA Mirror
// -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
// -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
// -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Interface
// *****************************************************************************
typedef struct _AT91S_TCB {
	AT91S_TC	 TCB_TC0; 	// TC Channel 0
	AT91_REG	 Reserved0[4]; 	// 
	AT91S_TC	 TCB_TC1; 	// TC Channel 1
	AT91_REG	 Reserved1[4]; 	// 
	AT91S_TC	 TCB_TC2; 	// TC Channel 2
	AT91_REG	 Reserved2[4]; 	// 
	AT91_REG	 TCB_BCR; 	// TC Block Control Register
	AT91_REG	 TCB_BMR; 	// TC Block Mode Register
} AT91S_TCB, *AT91PS_TCB;

// -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
#define AT91C_TCB_SYNC        ((unsigned int) 0x1 <<  0) // (TCB) Synchro Command
// -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
#define AT91C_TCB_TC0XC0S     ((unsigned int) 0x3 <<  0) // (TCB) External Clock Signal 0 Selection
#define 	AT91C_TCB_TC0XC0S_TCLK0                ((unsigned int) 0x0) // (TCB) TCLK0 connected to XC0
#define 	AT91C_TCB_TC0XC0S_NONE                 ((unsigned int) 0x1) // (TCB) None signal connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA1                ((unsigned int) 0x2) // (TCB) TIOA1 connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA2                ((unsigned int) 0x3) // (TCB) TIOA2 connected to XC0
#define AT91C_TCB_TC1XC1S     ((unsigned int) 0x3 <<  2) // (TCB) External Clock Signal 1 Selection
#define 	AT91C_TCB_TC1XC1S_TCLK1                ((unsigned int) 0x0 <<  2) // (TCB) TCLK1 connected to XC1
#define 	AT91C_TCB_TC1XC1S_NONE                 ((unsigned int) 0x1 <<  2) // (TCB) None signal connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA0                ((unsigned int) 0x2 <<  2) // (TCB) TIOA0 connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA2                ((unsigned int) 0x3 <<  2) // (TCB) TIOA2 connected to XC1
#define AT91C_TCB_TC2XC2S     ((unsigned int) 0x3 <<  4) // (TCB) External Clock Signal 2 Selection
#define 	AT91C_TCB_TC2XC2S_TCLK2                ((unsigned int) 0x0 <<  4) // (TCB) TCLK2 connected to XC2
#define 	AT91C_TCB_TC2XC2S_NONE                 ((unsigned int) 0x1 <<  4) // (TCB) None signal connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA0                ((unsigned int) 0x2 <<  4) // (TCB) TIOA0 connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA1                ((unsigned int) 0x3 <<  4) // (TCB) TIOA2 connected to XC2

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Multimedia Card Interface
// *****************************************************************************
typedef struct _AT91S_MCI {
	AT91_REG	 MCI_CR; 	// MCI Control Register
	AT91_REG	 MCI_MR; 	// MCI Mode Register
	AT91_REG	 MCI_DTOR; 	// MCI Data Timeout Register
	AT91_REG	 MCI_SDCR; 	// MCI SD Card Register
	AT91_REG	 MCI_ARGR; 	// MCI Argument Register
	AT91_REG	 MCI_CMDR; 	// MCI Command Register
	AT91_REG	 MCI_BLKR; 	// MCI Block Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 MCI_RSPR[4]; 	// MCI Response Register
	AT91_REG	 MCI_RDR; 	// MCI Receive Data Register
	AT91_REG	 MCI_TDR; 	// MCI Transmit Data Register
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 MCI_SR; 	// MCI Status Register
	AT91_REG	 MCI_IER; 	// MCI Interrupt Enable Register
	AT91_REG	 MCI_IDR; 	// MCI Interrupt Disable Register
	AT91_REG	 MCI_IMR; 	// MCI Interrupt Mask Register
	AT91_REG	 Reserved2[43]; 	// 
	AT91_REG	 MCI_VR; 	// MCI Version Register
	AT91_REG	 MCI_RPR; 	// Receive Pointer Register
	AT91_REG	 MCI_RCR; 	// Receive Counter Register
	AT91_REG	 MCI_TPR; 	// Transmit Pointer Register
	AT91_REG	 MCI_TCR; 	// Transmit Counter Register
	AT91_REG	 MCI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 MCI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 MCI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 MCI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 MCI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 MCI_PTSR; 	// PDC Transfer Status Register
} AT91S_MCI, *AT91PS_MCI;

// -------- MCI_CR : (MCI Offset: 0x0) MCI Control Register -------- 
#define AT91C_MCI_MCIEN       ((unsigned int) 0x1 <<  0) // (MCI) Multimedia Interface Enable
#define AT91C_MCI_MCIDIS      ((unsigned int) 0x1 <<  1) // (MCI) Multimedia Interface Disable
#define AT91C_MCI_PWSEN       ((unsigned int) 0x1 <<  2) // (MCI) Power Save Mode Enable
#define AT91C_MCI_PWSDIS      ((unsigned int) 0x1 <<  3) // (MCI) Power Save Mode Disable
#define AT91C_MCI_SWRST       ((unsigned int) 0x1 <<  7) // (MCI) MCI Software reset
// -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
#define AT91C_MCI_CLKDIV      ((unsigned int) 0xFF <<  0) // (MCI) Clock Divider
#define AT91C_MCI_PWSDIV      ((unsigned int) 0x7 <<  8) // (MCI) Power Saving Divider
#define AT91C_MCI_RDPROOF     ((unsigned int) 0x1 << 11) // (MCI) Read Proof Enable
#define AT91C_MCI_WRPROOF     ((unsigned int) 0x1 << 12) // (MCI) Write Proof Enable
#define AT91C_MCI_PDCFBYTE    ((unsigned int) 0x1 << 13) // (MCI) PDC Force Byte Transfer
#define AT91C_MCI_PDCPADV     ((unsigned int) 0x1 << 14) // (MCI) PDC Padding Value
#define AT91C_MCI_PDCMODE     ((unsigned int) 0x1 << 15) // (MCI) PDC Oriented Mode
#define AT91C_MCI_BLKLEN      ((unsigned int) 0xFFFF << 16) // (MCI) Data Block Length
// -------- MCI_DTOR : (MCI Offset: 0x8) MCI Data Timeout Register -------- 
#define AT91C_MCI_DTOCYC      ((unsigned int) 0xF <<  0) // (MCI) Data Timeout Cycle Number
#define AT91C_MCI_DTOMUL      ((unsigned int) 0x7 <<  4) // (MCI) Data Timeout Multiplier
#define 	AT91C_MCI_DTOMUL_1                    ((unsigned int) 0x0 <<  4) // (MCI) DTOCYC x 1
#define 	AT91C_MCI_DTOMUL_16                   ((unsigned int) 0x1 <<  4) // (MCI) DTOCYC x 16
#define 	AT91C_MCI_DTOMUL_128                  ((unsigned int) 0x2 <<  4) // (MCI) DTOCYC x 128
#define 	AT91C_MCI_DTOMUL_256                  ((unsigned int) 0x3 <<  4) // (MCI) DTOCYC x 256
#define 	AT91C_MCI_DTOMUL_1024                 ((unsigned int) 0x4 <<  4) // (MCI) DTOCYC x 1024
#define 	AT91C_MCI_DTOMUL_4096                 ((unsigned int) 0x5 <<  4) // (MCI) DTOCYC x 4096
#define 	AT91C_MCI_DTOMUL_65536                ((unsigned int) 0x6 <<  4) // (MCI) DTOCYC x 65536
#define 	AT91C_MCI_DTOMUL_1048576              ((unsigned int) 0x7 <<  4) // (MCI) DTOCYC x 1048576
// -------- MCI_SDCR : (MCI Offset: 0xc) MCI SD Card Register -------- 
#define AT91C_MCI_SCDSEL      ((unsigned int) 0x3 <<  0) // (MCI) SD Card Selector
#define AT91C_MCI_SCDBUS      ((unsigned int) 0x1 <<  7) // (MCI) SDCard/SDIO Bus Width
// -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
#define AT91C_MCI_CMDNB       ((unsigned int) 0x3F <<  0) // (MCI) Command Number
#define AT91C_MCI_RSPTYP      ((unsigned int) 0x3 <<  6) // (MCI) Response Type
#define 	AT91C_MCI_RSPTYP_NO                   ((unsigned int) 0x0 <<  6) // (MCI) No response
#define 	AT91C_MCI_RSPTYP_48                   ((unsigned int) 0x1 <<  6) // (MCI) 48-bit response
#define 	AT91C_MCI_RSPTYP_136                  ((unsigned int) 0x2 <<  6) // (MCI) 136-bit response
#define AT91C_MCI_SPCMD       ((unsigned int) 0x7 <<  8) // (MCI) Special CMD
#define 	AT91C_MCI_SPCMD_NONE                 ((unsigned int) 0x0 <<  8) // (MCI) Not a special CMD
#define 	AT91C_MCI_SPCMD_INIT                 ((unsigned int) 0x1 <<  8) // (MCI) Initialization CMD
#define 	AT91C_MCI_SPCMD_SYNC                 ((unsigned int) 0x2 <<  8) // (MCI) Synchronized CMD
#define 	AT91C_MCI_SPCMD_IT_CMD               ((unsigned int) 0x4 <<  8) // (MCI) Interrupt command
#define 	AT91C_MCI_SPCMD_IT_REP               ((unsigned int) 0x5 <<  8) // (MCI) Interrupt response
#define AT91C_MCI_OPDCMD      ((unsigned int) 0x1 << 11) // (MCI) Open Drain Command
#define AT91C_MCI_MAXLAT      ((unsigned int) 0x1 << 12) // (MCI) Maximum Latency for Command to respond
#define AT91C_MCI_TRCMD       ((unsigned int) 0x3 << 16) // (MCI) Transfer CMD
#define 	AT91C_MCI_TRCMD_NO                   ((unsigned int) 0x0 << 16) // (MCI) No transfer
#define 	AT91C_MCI_TRCMD_START                ((unsigned int) 0x1 << 16) // (MCI) Start transfer
#define 	AT91C_MCI_TRCMD_STOP                 ((unsigned int) 0x2 << 16) // (MCI) Stop transfer
#define AT91C_MCI_TRDIR       ((unsigned int) 0x1 << 18) // (MCI) Transfer Direction
#define AT91C_MCI_TRTYP       ((unsigned int) 0x7 << 19) // (MCI) Transfer Type
#define 	AT91C_MCI_TRTYP_BLOCK                ((unsigned int) 0x0 << 19) // (MCI) MMC/SDCard Single Block Transfer type
#define 	AT91C_MCI_TRTYP_MULTIPLE             ((unsigned int) 0x1 << 19) // (MCI) MMC/SDCard Multiple Block transfer type
#define 	AT91C_MCI_TRTYP_STREAM               ((unsigned int) 0x2 << 19) // (MCI) MMC Stream transfer type
#define 	AT91C_MCI_TRTYP_SDIO_BYTE            ((unsigned int) 0x4 << 19) // (MCI) SDIO Byte transfer type
#define 	AT91C_MCI_TRTYP_SDIO_BLOCK           ((unsigned int) 0x5 << 19) // (MCI) SDIO Block transfer type
#define AT91C_MCI_IOSPCMD     ((unsigned int) 0x3 << 24) // (MCI) SDIO Special Command
#define 	AT91C_MCI_IOSPCMD_NONE                 ((unsigned int) 0x0 << 24) // (MCI) NOT a special command
#define 	AT91C_MCI_IOSPCMD_SUSPEND              ((unsigned int) 0x1 << 24) // (MCI) SDIO Suspend Command
#define 	AT91C_MCI_IOSPCMD_RESUME               ((unsigned int) 0x2 << 24) // (MCI) SDIO Resume Command
// -------- MCI_BLKR : (MCI Offset: 0x18) MCI Block Register -------- 
#define AT91C_MCI_BCNT        ((unsigned int) 0xFFFF <<  0) // (MCI) MMC/SDIO Block Count / SDIO Byte Count
// -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
#define AT91C_MCI_CMDRDY      ((unsigned int) 0x1 <<  0) // (MCI) Command Ready flag
#define AT91C_MCI_RXRDY       ((unsigned int) 0x1 <<  1) // (MCI) RX Ready flag
#define AT91C_MCI_TXRDY       ((unsigned int) 0x1 <<  2) // (MCI) TX Ready flag
#define AT91C_MCI_BLKE        ((unsigned int) 0x1 <<  3) // (MCI) Data Block Transfer Ended flag
#define AT91C_MCI_DTIP        ((unsigned int) 0x1 <<  4) // (MCI) Data Transfer in Progress flag
#define AT91C_MCI_NOTBUSY     ((unsigned int) 0x1 <<  5) // (MCI) Data Line Not Busy flag
#define AT91C_MCI_ENDRX       ((unsigned int) 0x1 <<  6) // (MCI) End of RX Buffer flag
#define AT91C_MCI_ENDTX       ((unsigned int) 0x1 <<  7) // (MCI) End of TX Buffer flag
#define AT91C_MCI_SDIOIRQA    ((unsigned int) 0x1 <<  8) // (MCI) SDIO Interrupt for Slot A
#define AT91C_MCI_SDIOIRQB    ((unsigned int) 0x1 <<  9) // (MCI) SDIO Interrupt for Slot B
#define AT91C_MCI_SDIOIRQC    ((unsigned int) 0x1 << 10) // (MCI) SDIO Interrupt for Slot C
#define AT91C_MCI_SDIOIRQD    ((unsigned int) 0x1 << 11) // (MCI) SDIO Interrupt for Slot D
#define AT91C_MCI_RXBUFF      ((unsigned int) 0x1 << 14) // (MCI) RX Buffer Full flag
#define AT91C_MCI_TXBUFE      ((unsigned int) 0x1 << 15) // (MCI) TX Buffer Empty flag
#define AT91C_MCI_RINDE       ((unsigned int) 0x1 << 16) // (MCI) Response Index Error flag
#define AT91C_MCI_RDIRE       ((unsigned int) 0x1 << 17) // (MCI) Response Direction Error flag
#define AT91C_MCI_RCRCE       ((unsigned int) 0x1 << 18) // (MCI) Response CRC Error flag
#define AT91C_MCI_RENDE       ((unsigned int) 0x1 << 19) // (MCI) Response End Bit Error flag
#define AT91C_MCI_RTOE        ((unsigned int) 0x1 << 20) // (MCI) Response Time-out Error flag
#define AT91C_MCI_DCRCE       ((unsigned int) 0x1 << 21) // (MCI) data CRC Error flag
#define AT91C_MCI_DTOE        ((unsigned int) 0x1 << 22) // (MCI) Data timeout Error flag
#define AT91C_MCI_OVRE        ((unsigned int) 0x1 << 30) // (MCI) Overrun flag
#define AT91C_MCI_UNRE        ((unsigned int) 0x1 << 31) // (MCI) Underrun flag
// -------- MCI_IER : (MCI Offset: 0x44) MCI Interrupt Enable Register -------- 
// -------- MCI_IDR : (MCI Offset: 0x48) MCI Interrupt Disable Register -------- 
// -------- MCI_IMR : (MCI Offset: 0x4c) MCI Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Two-wire Interface
// *****************************************************************************
typedef struct _AT91S_TWI {
	AT91_REG	 TWI_CR; 	// Control Register
	AT91_REG	 TWI_MMR; 	// Master Mode Register
	AT91_REG	 TWI_SMR; 	// Slave Mode Register
	AT91_REG	 TWI_IADR; 	// Internal Address Register
	AT91_REG	 TWI_CWGR; 	// Clock Waveform Generator Register
	AT91_REG	 Reserved0[3]; 	// 
	AT91_REG	 TWI_SR; 	// Status Register
	AT91_REG	 TWI_IER; 	// Interrupt Enable Register
	AT91_REG	 TWI_IDR; 	// Interrupt Disable Register
	AT91_REG	 TWI_IMR; 	// Interrupt Mask Register
	AT91_REG	 TWI_RHR; 	// Receive Holding Register
	AT91_REG	 TWI_THR; 	// Transmit Holding Register
	AT91_REG	 Reserved1[50]; 	// 
	AT91_REG	 TWI_RPR; 	// Receive Pointer Register
	AT91_REG	 TWI_RCR; 	// Receive Counter Register
	AT91_REG	 TWI_TPR; 	// Transmit Pointer Register
	AT91_REG	 TWI_TCR; 	// Transmit Counter Register
	AT91_REG	 TWI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 TWI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 TWI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 TWI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 TWI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 TWI_PTSR; 	// PDC Transfer Status Register
} AT91S_TWI, *AT91PS_TWI;

// -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- 
#define AT91C_TWI_START       ((unsigned int) 0x1 <<  0) // (TWI) Send a START Condition
#define AT91C_TWI_STOP        ((unsigned int) 0x1 <<  1) // (TWI) Send a STOP Condition
#define AT91C_TWI_MSEN        ((unsigned int) 0x1 <<  2) // (TWI) TWI Master Transfer Enabled
#define AT91C_TWI_MSDIS       ((unsigned int) 0x1 <<  3) // (TWI) TWI Master Transfer Disabled
#define AT91C_TWI_SVEN        ((unsigned int) 0x1 <<  4) // (TWI) TWI Slave mode Enabled
#define AT91C_TWI_SVDIS       ((unsigned int) 0x1 <<  5) // (TWI) TWI Slave mode Disabled
#define AT91C_TWI_SWRST       ((unsigned int) 0x1 <<  7) // (TWI) Software Reset
// -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
#define AT91C_TWI_IADRSZ      ((unsigned int) 0x3 <<  8) // (TWI) Internal Device Address Size
#define 	AT91C_TWI_IADRSZ_NO                   ((unsigned int) 0x0 <<  8) // (TWI) No internal device address
#define 	AT91C_TWI_IADRSZ_1_BYTE               ((unsigned int) 0x1 <<  8) // (TWI) One-byte internal device address
#define 	AT91C_TWI_IADRSZ_2_BYTE               ((unsigned int) 0x2 <<  8) // (TWI) Two-byte internal device address
#define 	AT91C_TWI_IADRSZ_3_BYTE               ((unsigned int) 0x3 <<  8) // (TWI) Three-byte internal device address
#define AT91C_TWI_MREAD       ((unsigned int) 0x1 << 12) // (TWI) Master Read Direction
#define AT91C_TWI_DADR        ((unsigned int) 0x7F << 16) // (TWI) Device Address
// -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- 
#define AT91C_TWI_SADR        ((unsigned int) 0x7F << 16) // (TWI) Slave Address
// -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
#define AT91C_TWI_CLDIV       ((unsigned int) 0xFF <<  0) // (TWI) Clock Low Divider
#define AT91C_TWI_CHDIV       ((unsigned int) 0xFF <<  8) // (TWI) Clock High Divider
#define AT91C_TWI_CKDIV       ((unsigned int) 0x7 << 16) // (TWI) Clock Divider
// -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
#define AT91C_TWI_TXCOMP_SLAVE ((unsigned int) 0x1 <<  0) // (TWI) Transmission Completed
#define AT91C_TWI_TXCOMP_MASTER ((unsigned int) 0x1 <<  0) // (TWI) Transmission Completed
#define AT91C_TWI_RXRDY       ((unsigned int) 0x1 <<  1) // (TWI) Receive holding register ReaDY
#define AT91C_TWI_TXRDY_MASTER ((unsigned int) 0x1 <<  2) // (TWI) Transmit holding register ReaDY
#define AT91C_TWI_TXRDY_SLAVE ((unsigned int) 0x1 <<  2) // (TWI) Transmit holding register ReaDY
#define AT91C_TWI_SVREAD      ((unsigned int) 0x1 <<  3) // (TWI) Slave READ (used only in Slave mode)
#define AT91C_TWI_SVACC       ((unsigned int) 0x1 <<  4) // (TWI) Slave ACCess (used only in Slave mode)
#define AT91C_TWI_GACC        ((unsigned int) 0x1 <<  5) // (TWI) General Call ACcess (used only in Slave mode)
#define AT91C_TWI_OVRE        ((unsigned int) 0x1 <<  6) // (TWI) Overrun Error (used only in Master and Multi-master mode)
#define AT91C_TWI_NACK_SLAVE  ((unsigned int) 0x1 <<  8) // (TWI) Not Acknowledged
#define AT91C_TWI_NACK_MASTER ((unsigned int) 0x1 <<  8) // (TWI) Not Acknowledged
#define AT91C_TWI_ARBLST_MULTI_MASTER ((unsigned int) 0x1 <<  9) // (TWI) Arbitration Lost (used only in Multimaster mode)
#define AT91C_TWI_SCLWS       ((unsigned int) 0x1 << 10) // (TWI) Clock Wait State (used only in Slave mode)
#define AT91C_TWI_EOSACC      ((unsigned int) 0x1 << 11) // (TWI) End Of Slave ACCess (used only in Slave mode)
#define AT91C_TWI_ENDRX       ((unsigned int) 0x1 << 12) // (TWI) End of Receiver Transfer
#define AT91C_TWI_ENDTX       ((unsigned int) 0x1 << 13) // (TWI) End of Receiver Transfer
#define AT91C_TWI_RXBUFF      ((unsigned int) 0x1 << 14) // (TWI) RXBUFF Interrupt
#define AT91C_TWI_TXBUFE      ((unsigned int) 0x1 << 15) // (TWI) TXBUFE Interrupt
// -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
// -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
// -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Usart
// *****************************************************************************
typedef struct _AT91S_USART {
	AT91_REG	 US_CR; 	// Control Register
	AT91_REG	 US_MR; 	// Mode Register
	AT91_REG	 US_IER; 	// Interrupt Enable Register
	AT91_REG	 US_IDR; 	// Interrupt Disable Register
	AT91_REG	 US_IMR; 	// Interrupt Mask Register
	AT91_REG	 US_CSR; 	// Channel Status Register
	AT91_REG	 US_RHR; 	// Receiver Holding Register
	AT91_REG	 US_THR; 	// Transmitter Holding Register
	AT91_REG	 US_BRGR; 	// Baud Rate Generator Register
	AT91_REG	 US_RTOR; 	// Receiver Time-out Register
	AT91_REG	 US_TTGR; 	// Transmitter Time-guard Register
	AT91_REG	 Reserved0[5]; 	// 
	AT91_REG	 US_FIDI; 	// FI_DI_Ratio Register
	AT91_REG	 US_NER; 	// Nb Errors Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 US_IF; 	// IRDA_FILTER Register
	AT91_REG	 Reserved2[44]; 	// 
	AT91_REG	 US_RPR; 	// Receive Pointer Register
	AT91_REG	 US_RCR; 	// Receive Counter Register
	AT91_REG	 US_TPR; 	// Transmit Pointer Register
	AT91_REG	 US_TCR; 	// Transmit Counter Register
	AT91_REG	 US_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 US_RNCR; 	// Receive Next Counter Register
	AT91_REG	 US_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 US_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 US_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 US_PTSR; 	// PDC Transfer Status Register
} AT91S_USART, *AT91PS_USART;

// -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_US_STTBRK       ((unsigned int) 0x1 <<  9) // (USART) Start Break
#define AT91C_US_STPBRK       ((unsigned int) 0x1 << 10) // (USART) Stop Break
#define AT91C_US_STTTO        ((unsigned int) 0x1 << 11) // (USART) Start Time-out
#define AT91C_US_SENDA        ((unsigned int) 0x1 << 12) // (USART) Send Address
#define AT91C_US_RSTIT        ((unsigned int) 0x1 << 13) // (USART) Reset Iterations
#define AT91C_US_RSTNACK      ((unsigned int) 0x1 << 14) // (USART) Reset Non Acknowledge
#define AT91C_US_RETTO        ((unsigned int) 0x1 << 15) // (USART) Rearm Time-out
#define AT91C_US_DTREN        ((unsigned int) 0x1 << 16) // (USART) Data Terminal ready Enable
#define AT91C_US_DTRDIS       ((unsigned int) 0x1 << 17) // (USART) Data Terminal ready Disable
#define AT91C_US_RTSEN        ((unsigned int) 0x1 << 18) // (USART) Request to Send enable
#define AT91C_US_RTSDIS       ((unsigned int) 0x1 << 19) // (USART) Request to Send Disable
// -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_US_USMODE       ((unsigned int) 0xF <<  0) // (USART) Usart mode
#define 	AT91C_US_USMODE_NORMAL               ((unsigned int) 0x0) // (USART) Normal
#define 	AT91C_US_USMODE_RS485                ((unsigned int) 0x1) // (USART) RS485
#define 	AT91C_US_USMODE_HWHSH                ((unsigned int) 0x2) // (USART) Hardware Handshaking
#define 	AT91C_US_USMODE_MODEM                ((unsigned int) 0x3) // (USART) Modem
#define 	AT91C_US_USMODE_ISO7816_0            ((unsigned int) 0x4) // (USART) ISO7816 protocol: T = 0
#define 	AT91C_US_USMODE_ISO7816_1            ((unsigned int) 0x6) // (USART) ISO7816 protocol: T = 1
#define 	AT91C_US_USMODE_IRDA                 ((unsigned int) 0x8) // (USART) IrDA
#define 	AT91C_US_USMODE_SWHSH                ((unsigned int) 0xC) // (USART) Software Handshaking
#define AT91C_US_CLKS         ((unsigned int) 0x3 <<  4) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CLKS_CLOCK                ((unsigned int) 0x0 <<  4) // (USART) Clock
#define 	AT91C_US_CLKS_FDIV1                ((unsigned int) 0x1 <<  4) // (USART) fdiv1
#define 	AT91C_US_CLKS_SLOW                 ((unsigned int) 0x2 <<  4) // (USART) slow_clock (ARM)
#define 	AT91C_US_CLKS_EXT                  ((unsigned int) 0x3 <<  4) // (USART) External (SCK)
#define AT91C_US_CHRL         ((unsigned int) 0x3 <<  6) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CHRL_5_BITS               ((unsigned int) 0x0 <<  6) // (USART) Character Length: 5 bits
#define 	AT91C_US_CHRL_6_BITS               ((unsigned int) 0x1 <<  6) // (USART) Character Length: 6 bits
#define 	AT91C_US_CHRL_7_BITS               ((unsigned int) 0x2 <<  6) // (USART) Character Length: 7 bits
#define 	AT91C_US_CHRL_8_BITS               ((unsigned int) 0x3 <<  6) // (USART) Character Length: 8 bits
#define AT91C_US_SYNC         ((unsigned int) 0x1 <<  8) // (USART) Synchronous Mode Select
#define AT91C_US_NBSTOP       ((unsigned int) 0x3 << 12) // (USART) Number of Stop bits
#define 	AT91C_US_NBSTOP_1_BIT                ((unsigned int) 0x0 << 12) // (USART) 1 stop bit
#define 	AT91C_US_NBSTOP_15_BIT               ((unsigned int) 0x1 << 12) // (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits
#define 	AT91C_US_NBSTOP_2_BIT                ((unsigned int) 0x2 << 12) // (USART) 2 stop bits
#define AT91C_US_MSBF         ((unsigned int) 0x1 << 16) // (USART) Bit Order
#define AT91C_US_MODE9        ((unsigned int) 0x1 << 17) // (USART) 9-bit Character length
#define AT91C_US_CKLO         ((unsigned int) 0x1 << 18) // (USART) Clock Output Select
#define AT91C_US_OVER         ((unsigned int) 0x1 << 19) // (USART) Over Sampling Mode
#define AT91C_US_INACK        ((unsigned int) 0x1 << 20) // (USART) Inhibit Non Acknowledge
#define AT91C_US_DSNACK       ((unsigned int) 0x1 << 21) // (USART) Disable Successive NACK
#define AT91C_US_MAX_ITER     ((unsigned int) 0x1 << 24) // (USART) Number of Repetitions
#define AT91C_US_FILTER       ((unsigned int) 0x1 << 28) // (USART) Receive Line Filter
// -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_US_RXBRK        ((unsigned int) 0x1 <<  2) // (USART) Break Received/End of Break
#define AT91C_US_TIMEOUT      ((unsigned int) 0x1 <<  8) // (USART) Receiver Time-out
#define AT91C_US_ITERATION    ((unsigned int) 0x1 << 10) // (USART) Max number of Repetitions Reached
#define AT91C_US_NACK         ((unsigned int) 0x1 << 13) // (USART) Non Acknowledge
#define AT91C_US_RIIC         ((unsigned int) 0x1 << 16) // (USART) Ring INdicator Input Change Flag
#define AT91C_US_DSRIC        ((unsigned int) 0x1 << 17) // (USART) Data Set Ready Input Change Flag
#define AT91C_US_DCDIC        ((unsigned int) 0x1 << 18) // (USART) Data Carrier Flag
#define AT91C_US_CTSIC        ((unsigned int) 0x1 << 19) // (USART) Clear To Send Input Change Flag
// -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- 
#define AT91C_US_RI           ((unsigned int) 0x1 << 20) // (USART) Image of RI Input
#define AT91C_US_DSR          ((unsigned int) 0x1 << 21) // (USART) Image of DSR Input
#define AT91C_US_DCD          ((unsigned int) 0x1 << 22) // (USART) Image of DCD Input
#define AT91C_US_CTS          ((unsigned int) 0x1 << 23) // (USART) Image of CTS Input

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
// *****************************************************************************
typedef struct _AT91S_SSC {
	AT91_REG	 SSC_CR; 	// Control Register
	AT91_REG	 SSC_CMR; 	// Clock Mode Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 SSC_RCMR; 	// Receive Clock ModeRegister
	AT91_REG	 SSC_RFMR; 	// Receive Frame Mode Register
	AT91_REG	 SSC_TCMR; 	// Transmit Clock Mode Register
	AT91_REG	 SSC_TFMR; 	// Transmit Frame Mode Register
	AT91_REG	 SSC_RHR; 	// Receive Holding Register
	AT91_REG	 SSC_THR; 	// Transmit Holding Register
	AT91_REG	 Reserved1[2]; 	// 
	AT91_REG	 SSC_RSHR; 	// Receive Sync Holding Register
	AT91_REG	 SSC_TSHR; 	// Transmit Sync Holding Register
	AT91_REG	 Reserved2[2]; 	// 
	AT91_REG	 SSC_SR; 	// Status Register
	AT91_REG	 SSC_IER; 	// Interrupt Enable Register
	AT91_REG	 SSC_IDR; 	// Interrupt Disable Register
	AT91_REG	 SSC_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved3[44]; 	// 
	AT91_REG	 SSC_RPR; 	// Receive Pointer Register
	AT91_REG	 SSC_RCR; 	// Receive Counter Register
	AT91_REG	 SSC_TPR; 	// Transmit Pointer Register
	AT91_REG	 SSC_TCR; 	// Transmit Counter Register
	AT91_REG	 SSC_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 SSC_RNCR; 	// Receive Next Counter Register
	AT91_REG	 SSC_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 SSC_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 SSC_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 SSC_PTSR; 	// PDC Transfer Status Register
} AT91S_SSC, *AT91PS_SSC;

// -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- 
#define AT91C_SSC_RXEN        ((unsigned int) 0x1 <<  0) // (SSC) Receive Enable
#define AT91C_SSC_RXDIS       ((unsigned int) 0x1 <<  1) // (SSC) Receive Disable
#define AT91C_SSC_TXEN        ((unsigned int) 0x1 <<  8) // (SSC) Transmit Enable
#define AT91C_SSC_TXDIS       ((unsigned int) 0x1 <<  9) // (SSC) Transmit Disable
#define AT91C_SSC_SWRST       ((unsigned int) 0x1 << 15) // (SSC) Software Reset
// -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- 
#define AT91C_SSC_CKS         ((unsigned int) 0x3 <<  0) // (SSC) Receive/Transmit Clock Selection
#define 	AT91C_SSC_CKS_DIV                  ((unsigned int) 0x0) // (SSC) Divided Clock
#define 	AT91C_SSC_CKS_TK                   ((unsigned int) 0x1) // (SSC) TK Clock signal
#define 	AT91C_SSC_CKS_RK                   ((unsigned int) 0x2) // (SSC) RK pin
#define AT91C_SSC_CKO         ((unsigned int) 0x7 <<  2) // (SSC) Receive/Transmit Clock Output Mode Selection
#define 	AT91C_SSC_CKO_NONE                 ((unsigned int) 0x0 <<  2) // (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only
#define 	AT91C_SSC_CKO_CONTINOUS            ((unsigned int) 0x1 <<  2) // (SSC) Continuous Receive/Transmit Clock RK pin: Output
#define 	AT91C_SSC_CKO_DATA_TX              ((unsigned int) 0x2 <<  2) // (SSC) Receive/Transmit Clock only during data transfers RK pin: Output
#define AT91C_SSC_CKI         ((unsigned int) 0x1 <<  5) // (SSC) Receive/Transmit Clock Inversion
#define AT91C_SSC_CKG         ((unsigned int) 0x3 <<  6) // (SSC) Receive/Transmit Clock Gating Selection
#define 	AT91C_SSC_CKG_NONE                 ((unsigned int) 0x0 <<  6) // (SSC) Receive/Transmit Clock Gating: None, continuous clock
#define 	AT91C_SSC_CKG_LOW                  ((unsigned int) 0x1 <<  6) // (SSC) Receive/Transmit Clock enabled only if RF Low
#define 	AT91C_SSC_CKG_HIGH                 ((unsigned int) 0x2 <<  6) // (SSC) Receive/Transmit Clock enabled only if RF High
#define AT91C_SSC_START       ((unsigned int) 0xF <<  8) // (SSC) Receive/Transmit Start Selection
#define 	AT91C_SSC_START_CONTINOUS            ((unsigned int) 0x0 <<  8) // (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data.
#define 	AT91C_SSC_START_TX                   ((unsigned int) 0x1 <<  8) // (SSC) Transmit/Receive start
#define 	AT91C_SSC_START_LOW_RF               ((unsigned int) 0x2 <<  8) // (SSC) Detection of a low level on RF input
#define 	AT91C_SSC_START_HIGH_RF              ((unsigned int) 0x3 <<  8) // (SSC) Detection of a high level on RF input
#define 	AT91C_SSC_START_FALL_RF              ((unsigned int) 0x4 <<  8) // (SSC) Detection of a falling edge on RF input
#define 	AT91C_SSC_START_RISE_RF              ((unsigned int) 0x5 <<  8) // (SSC) Detection of a rising edge on RF input
#define 	AT91C_SSC_START_LEVEL_RF             ((unsigned int) 0x6 <<  8) // (SSC) Detection of any level change on RF input
#define 	AT91C_SSC_START_EDGE_RF              ((unsigned int) 0x7 <<  8) // (SSC) Detection of any edge on RF input
#define 	AT91C_SSC_START_0                    ((unsigned int) 0x8 <<  8) // (SSC) Compare 0
#define AT91C_SSC_STOP        ((unsigned int) 0x1 << 12) // (SSC) Receive Stop Selection
#define AT91C_SSC_STTDLY      ((unsigned int) 0xFF << 16) // (SSC) Receive/Transmit Start Delay
#define AT91C_SSC_PERIOD      ((unsigned int) 0xFF << 24) // (SSC) Receive/Transmit Period Divider Selection
// -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- 
#define AT91C_SSC_DATLEN      ((unsigned int) 0x1F <<  0) // (SSC) Data Length
#define AT91C_SSC_LOOP        ((unsigned int) 0x1 <<  5) // (SSC) Loop Mode
#define AT91C_SSC_MSBF        ((unsigned int) 0x1 <<  7) // (SSC) Most Significant Bit First
#define AT91C_SSC_DATNB       ((unsigned int) 0xF <<  8) // (SSC) Data Number per Frame
#define AT91C_SSC_FSLEN       ((unsigned int) 0xF << 16) // (SSC) Receive/Transmit Frame Sync length
#define AT91C_SSC_FSOS        ((unsigned int) 0x7 << 20) // (SSC) Receive/Transmit Frame Sync Output Selection
#define 	AT91C_SSC_FSOS_NONE                 ((unsigned int) 0x0 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only
#define 	AT91C_SSC_FSOS_NEGATIVE             ((unsigned int) 0x1 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse
#define 	AT91C_SSC_FSOS_POSITIVE             ((unsigned int) 0x2 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse
#define 	AT91C_SSC_FSOS_LOW                  ((unsigned int) 0x3 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer
#define 	AT91C_SSC_FSOS_HIGH                 ((unsigned int) 0x4 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer
#define 	AT91C_SSC_FSOS_TOGGLE               ((unsigned int) 0x5 << 20) // (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer
#define AT91C_SSC_FSEDGE      ((unsigned int) 0x1 << 24) // (SSC) Frame Sync Edge Detection
// -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- 
// -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- 
#define AT91C_SSC_DATDEF      ((unsigned int) 0x1 <<  5) // (SSC) Data Default Value
#define AT91C_SSC_FSDEN       ((unsigned int) 0x1 << 23) // (SSC) Frame Sync Data Enable
// -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- 
#define AT91C_SSC_TXRDY       ((unsigned int) 0x1 <<  0) // (SSC) Transmit Ready
#define AT91C_SSC_TXEMPTY     ((unsigned int) 0x1 <<  1) // (SSC) Transmit Empty
#define AT91C_SSC_ENDTX       ((unsigned int) 0x1 <<  2) // (SSC) End Of Transmission
#define AT91C_SSC_TXBUFE      ((unsigned int) 0x1 <<  3) // (SSC) Transmit Buffer Empty
#define AT91C_SSC_RXRDY       ((unsigned int) 0x1 <<  4) // (SSC) Receive Ready
#define AT91C_SSC_OVRUN       ((unsigned int) 0x1 <<  5) // (SSC) Receive Overrun
#define AT91C_SSC_ENDRX       ((unsigned int) 0x1 <<  6) // (SSC) End of Reception
#define AT91C_SSC_RXBUFF      ((unsigned int) 0x1 <<  7) // (SSC) Receive Buffer Full
#define AT91C_SSC_CP0         ((unsigned int) 0x1 <<  8) // (SSC) Compare 0
#define AT91C_SSC_CP1         ((unsigned int) 0x1 <<  9) // (SSC) Compare 1
#define AT91C_SSC_TXSYN       ((unsigned int) 0x1 << 10) // (SSC) Transmit Sync
#define AT91C_SSC_RXSYN       ((unsigned int) 0x1 << 11) // (SSC) Receive Sync
#define AT91C_SSC_TXENA       ((unsigned int) 0x1 << 16) // (SSC) Transmit Enable
#define AT91C_SSC_RXENA       ((unsigned int) 0x1 << 17) // (SSC) Receive Enable
// -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- 
// -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- 
// -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AC97 Controller Interface
// *****************************************************************************
typedef struct _AT91S_AC97C {
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 AC97C_MR; 	// Mode Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 AC97C_ICA; 	// Input Channel AssignementRegister
	AT91_REG	 AC97C_OCA; 	// Output Channel Assignement Register
	AT91_REG	 Reserved2[2]; 	// 
	AT91_REG	 AC97C_CARHR; 	// Channel A Receive Holding Register
	AT91_REG	 AC97C_CATHR; 	// Channel A Transmit Holding Register
	AT91_REG	 AC97C_CASR; 	// Channel A Status Register
	AT91_REG	 AC97C_CAMR; 	// Channel A Mode Register
	AT91_REG	 AC97C_CBRHR; 	// Channel B Receive Holding Register (optional)
	AT91_REG	 AC97C_CBTHR; 	// Channel B Transmit Holding Register (optional)
	AT91_REG	 AC97C_CBSR; 	// Channel B Status Register
	AT91_REG	 AC97C_CBMR; 	// Channel B Mode Register
	AT91_REG	 AC97C_CORHR; 	// COdec Transmit Holding Register
	AT91_REG	 AC97C_COTHR; 	// COdec Transmit Holding Register
	AT91_REG	 AC97C_COSR; 	// CODEC Status Register
	AT91_REG	 AC97C_COMR; 	// CODEC Mask Status Register
	AT91_REG	 AC97C_SR; 	// Status Register
	AT91_REG	 AC97C_IER; 	// Interrupt Enable Register
	AT91_REG	 AC97C_IDR; 	// Interrupt Disable Register
	AT91_REG	 AC97C_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved3[39]; 	// 
	AT91_REG	 AC97C_VERSION; 	// Version Register
	AT91_REG	 AC97C_RPR; 	// Receive Pointer Register
	AT91_REG	 AC97C_RCR; 	// Receive Counter Register
	AT91_REG	 AC97C_TPR; 	// Transmit Pointer Register
	AT91_REG	 AC97C_TCR; 	// Transmit Counter Register
	AT91_REG	 AC97C_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 AC97C_RNCR; 	// Receive Next Counter Register
	AT91_REG	 AC97C_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 AC97C_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 AC97C_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 AC97C_PTSR; 	// PDC Transfer Status Register
} AT91S_AC97C, *AT91PS_AC97C;

// -------- AC97C_MR : (AC97C Offset: 0x8) AC97C Mode Register -------- 
#define AT91C_AC97C_ENA       ((unsigned int) 0x1 <<  0) // (AC97C) AC97 Controller Global Enable
#define AT91C_AC97C_WRST      ((unsigned int) 0x1 <<  1) // (AC97C) Warm Reset
#define AT91C_AC97C_VRA       ((unsigned int) 0x1 <<  2) // (AC97C) Variable RAte (for Data Slots)
// -------- AC97C_ICA : (AC97C Offset: 0x10) AC97C Input Channel Assignement Register -------- 
#define AT91C_AC97C_CHID3     ((unsigned int) 0x7 <<  0) // (AC97C) Channel Id for the input slot 3
#define 	AT91C_AC97C_CHID3_NONE                 ((unsigned int) 0x0) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID3_CA                   ((unsigned int) 0x1) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID3_CB                   ((unsigned int) 0x2) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID3_CC                   ((unsigned int) 0x3) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID4     ((unsigned int) 0x7 <<  3) // (AC97C) Channel Id for the input slot 4
#define 	AT91C_AC97C_CHID4_NONE                 ((unsigned int) 0x0 <<  3) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID4_CA                   ((unsigned int) 0x1 <<  3) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID4_CB                   ((unsigned int) 0x2 <<  3) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID4_CC                   ((unsigned int) 0x3 <<  3) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID5     ((unsigned int) 0x7 <<  6) // (AC97C) Channel Id for the input slot 5
#define 	AT91C_AC97C_CHID5_NONE                 ((unsigned int) 0x0 <<  6) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID5_CA                   ((unsigned int) 0x1 <<  6) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID5_CB                   ((unsigned int) 0x2 <<  6) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID5_CC                   ((unsigned int) 0x3 <<  6) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID6     ((unsigned int) 0x7 <<  9) // (AC97C) Channel Id for the input slot 6
#define 	AT91C_AC97C_CHID6_NONE                 ((unsigned int) 0x0 <<  9) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID6_CA                   ((unsigned int) 0x1 <<  9) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID6_CB                   ((unsigned int) 0x2 <<  9) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID6_CC                   ((unsigned int) 0x3 <<  9) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID7     ((unsigned int) 0x7 << 12) // (AC97C) Channel Id for the input slot 7
#define 	AT91C_AC97C_CHID7_NONE                 ((unsigned int) 0x0 << 12) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID7_CA                   ((unsigned int) 0x1 << 12) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID7_CB                   ((unsigned int) 0x2 << 12) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID7_CC                   ((unsigned int) 0x3 << 12) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID8     ((unsigned int) 0x7 << 15) // (AC97C) Channel Id for the input slot 8
#define 	AT91C_AC97C_CHID8_NONE                 ((unsigned int) 0x0 << 15) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID8_CA                   ((unsigned int) 0x1 << 15) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID8_CB                   ((unsigned int) 0x2 << 15) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID8_CC                   ((unsigned int) 0x3 << 15) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID9     ((unsigned int) 0x7 << 18) // (AC97C) Channel Id for the input slot 9
#define 	AT91C_AC97C_CHID9_NONE                 ((unsigned int) 0x0 << 18) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID9_CA                   ((unsigned int) 0x1 << 18) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID9_CB                   ((unsigned int) 0x2 << 18) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID9_CC                   ((unsigned int) 0x3 << 18) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID10    ((unsigned int) 0x7 << 21) // (AC97C) Channel Id for the input slot 10
#define 	AT91C_AC97C_CHID10_NONE                 ((unsigned int) 0x0 << 21) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID10_CA                   ((unsigned int) 0x1 << 21) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID10_CB                   ((unsigned int) 0x2 << 21) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID10_CC                   ((unsigned int) 0x3 << 21) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID11    ((unsigned int) 0x7 << 24) // (AC97C) Channel Id for the input slot 11
#define 	AT91C_AC97C_CHID11_NONE                 ((unsigned int) 0x0 << 24) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID11_CA                   ((unsigned int) 0x1 << 24) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID11_CB                   ((unsigned int) 0x2 << 24) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID11_CC                   ((unsigned int) 0x3 << 24) // (AC97C) Channel C data will be transmitted during this slot
#define AT91C_AC97C_CHID12    ((unsigned int) 0x7 << 27) // (AC97C) Channel Id for the input slot 12
#define 	AT91C_AC97C_CHID12_NONE                 ((unsigned int) 0x0 << 27) // (AC97C) No data will be transmitted during this slot
#define 	AT91C_AC97C_CHID12_CA                   ((unsigned int) 0x1 << 27) // (AC97C) Channel A data will be transmitted during this slot
#define 	AT91C_AC97C_CHID12_CB                   ((unsigned int) 0x2 << 27) // (AC97C) Channel B data will be transmitted during this slot
#define 	AT91C_AC97C_CHID12_CC                   ((unsigned int) 0x3 << 27) // (AC97C) Channel C data will be transmitted during this slot
// -------- AC97C_OCA : (AC97C Offset: 0x14) AC97C Output Channel Assignement Register -------- 
// -------- AC97C_CARHR : (AC97C Offset: 0x20) AC97C Channel A Receive Holding Register -------- 
#define AT91C_AC97C_RDATA     ((unsigned int) 0xFFFFF <<  0) // (AC97C) Receive data
// -------- AC97C_CATHR : (AC97C Offset: 0x24) AC97C Channel A Transmit Holding Register -------- 
#define AT91C_AC97C_TDATA     ((unsigned int) 0xFFFFF <<  0) // (AC97C) Transmit data
// -------- AC97C_CASR : (AC97C Offset: 0x28) AC97C Channel A Status Register -------- 
#define AT91C_AC97C_TXRDY     ((unsigned int) 0x1 <<  0) // (AC97C) 
#define AT91C_AC97C_TXEMPTY   ((unsigned int) 0x1 <<  1) // (AC97C) 
#define AT91C_AC97C_UNRUN     ((unsigned int) 0x1 <<  2) // (AC97C) 
#define AT91C_AC97C_RXRDY     ((unsigned int) 0x1 <<  4) // (AC97C) 
#define AT91C_AC97C_OVRUN     ((unsigned int) 0x1 <<  5) // (AC97C) 
#define AT91C_AC97C_ENDTX     ((unsigned int) 0x1 << 10) // (AC97C) 
#define AT91C_AC97C_TXBUFE    ((unsigned int) 0x1 << 11) // (AC97C) 
#define AT91C_AC97C_ENDRX     ((unsigned int) 0x1 << 14) // (AC97C) 
#define AT91C_AC97C_RXBUFF    ((unsigned int) 0x1 << 15) // (AC97C) 
// -------- AC97C_CAMR : (AC97C Offset: 0x2c) AC97C Channel A Mode Register -------- 
#define AT91C_AC97C_SIZE      ((unsigned int) 0x3 << 16) // (AC97C) 
#define 	AT91C_AC97C_SIZE_20_BITS              ((unsigned int) 0x0 << 16) // (AC97C) Data size is 20 bits
#define 	AT91C_AC97C_SIZE_18_BITS              ((unsigned int) 0x1 << 16) // (AC97C) Data size is 18 bits
#define 	AT91C_AC97C_SIZE_16_BITS              ((unsigned int) 0x2 << 16) // (AC97C) Data size is 16 bits
#define 	AT91C_AC97C_SIZE_10_BITS              ((unsigned int) 0x3 << 16) // (AC97C) Data size is 10 bits
#define AT91C_AC97C_CEM       ((unsigned int) 0x1 << 18) // (AC97C) 
#define AT91C_AC97C_CEN       ((unsigned int) 0x1 << 21) // (AC97C) 
#define AT91C_AC97C_PDCEN     ((unsigned int) 0x1 << 22) // (AC97C) 
// -------- AC97C_CBRHR : (AC97C Offset: 0x30) AC97C Channel B Receive Holding Register -------- 
// -------- AC97C_CBTHR : (AC97C Offset: 0x34) AC97C Channel B Transmit Holding Register -------- 
// -------- AC97C_CBSR : (AC97C Offset: 0x38) AC97C Channel B Status Register -------- 
// -------- AC97C_CBMR : (AC97C Offset: 0x3c) AC97C Channel B Mode Register -------- 
// -------- AC97C_CORHR : (AC97C Offset: 0x40) AC97C Codec Channel Receive Holding Register -------- 
#define AT91C_AC97C_SDATA     ((unsigned int) 0xFFFF <<  0) // (AC97C) Status Data
// -------- AC97C_COTHR : (AC97C Offset: 0x44) AC97C Codec Channel Transmit Holding Register -------- 
#define AT91C_AC97C_CDATA     ((unsigned int) 0xFFFF <<  0) // (AC97C) Command Data
#define AT91C_AC97C_CADDR     ((unsigned int) 0x7F << 16) // (AC97C) COdec control register index
#define AT91C_AC97C_READ      ((unsigned int) 0x1 << 23) // (AC97C) Read/Write command
// -------- AC97C_COSR : (AC97C Offset: 0x48) AC97C CODEC Status Register -------- 
// -------- AC97C_COMR : (AC97C Offset: 0x4c) AC97C CODEC Mode Register -------- 
// -------- AC97C_SR : (AC97C Offset: 0x50) AC97C Status Register -------- 
#define AT91C_AC97C_SOF       ((unsigned int) 0x1 <<  0) // (AC97C) 
#define AT91C_AC97C_WKUP      ((unsigned int) 0x1 <<  1) // (AC97C) 
#define AT91C_AC97C_COEVT     ((unsigned int) 0x1 <<  2) // (AC97C) 
#define AT91C_AC97C_CAEVT     ((unsigned int) 0x1 <<  3) // (AC97C) 
#define AT91C_AC97C_CBEVT     ((unsigned int) 0x1 <<  4) // (AC97C) 
// -------- AC97C_IER : (AC97C Offset: 0x54) AC97C Interrupt Enable Register -------- 
// -------- AC97C_IDR : (AC97C Offset: 0x58) AC97C Interrupt Disable Register -------- 
// -------- AC97C_IMR : (AC97C Offset: 0x5c) AC97C Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
// *****************************************************************************
typedef struct _AT91S_SPI {
	AT91_REG	 SPI_CR; 	// Control Register
	AT91_REG	 SPI_MR; 	// Mode Register
	AT91_REG	 SPI_RDR; 	// Receive Data Register
	AT91_REG	 SPI_TDR; 	// Transmit Data Register
	AT91_REG	 SPI_SR; 	// Status Register
	AT91_REG	 SPI_IER; 	// Interrupt Enable Register
	AT91_REG	 SPI_IDR; 	// Interrupt Disable Register
	AT91_REG	 SPI_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved0[4]; 	// 
	AT91_REG	 SPI_CSR[4]; 	// Chip Select Register
	AT91_REG	 Reserved1[48]; 	// 
	AT91_REG	 SPI_RPR; 	// Receive Pointer Register
	AT91_REG	 SPI_RCR; 	// Receive Counter Register
	AT91_REG	 SPI_TPR; 	// Transmit Pointer Register
	AT91_REG	 SPI_TCR; 	// Transmit Counter Register
	AT91_REG	 SPI_RNPR; 	// Receive Next Pointer Register
	AT91_REG	 SPI_RNCR; 	// Receive Next Counter Register
	AT91_REG	 SPI_TNPR; 	// Transmit Next Pointer Register
	AT91_REG	 SPI_TNCR; 	// Transmit Next Counter Register
	AT91_REG	 SPI_PTCR; 	// PDC Transfer Control Register
	AT91_REG	 SPI_PTSR; 	// PDC Transfer Status Register
} AT91S_SPI, *AT91PS_SPI;

// -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
#define AT91C_SPI_SPIEN       ((unsigned int) 0x1 <<  0) // (SPI) SPI Enable
#define AT91C_SPI_SPIDIS      ((unsigned int) 0x1 <<  1) // (SPI) SPI Disable
#define AT91C_SPI_SWRST       ((unsigned int) 0x1 <<  7) // (SPI) SPI Software reset
#define AT91C_SPI_LASTXFER    ((unsigned int) 0x1 << 24) // (SPI) SPI Last Transfer
// -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
#define AT91C_SPI_MSTR        ((unsigned int) 0x1 <<  0) // (SPI) Master/Slave Mode
#define AT91C_SPI_PS          ((unsigned int) 0x1 <<  1) // (SPI) Peripheral Select
#define 	AT91C_SPI_PS_FIXED                ((unsigned int) 0x0 <<  1) // (SPI) Fixed Peripheral Select
#define 	AT91C_SPI_PS_VARIABLE             ((unsigned int) 0x1 <<  1) // (SPI) Variable Peripheral Select
#define AT91C_SPI_PCSDEC      ((unsigned int) 0x1 <<  2) // (SPI) Chip Select Decode
#define AT91C_SPI_FDIV        ((unsigned int) 0x1 <<  3) // (SPI) Clock Selection
#define AT91C_SPI_MODFDIS     ((unsigned int) 0x1 <<  4) // (SPI) Mode Fault Detection
#define AT91C_SPI_LLB         ((unsigned int) 0x1 <<  7) // (SPI) Clock Selection
#define AT91C_SPI_PCS         ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select
#define AT91C_SPI_DLYBCS      ((unsigned int) 0xFF << 24) // (SPI) Delay Between Chip Selects
// -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
#define AT91C_SPI_RD          ((unsigned int) 0xFFFF <<  0) // (SPI) Receive Data
#define AT91C_SPI_RPCS        ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
#define AT91C_SPI_TD          ((unsigned int) 0xFFFF <<  0) // (SPI) Transmit Data
#define AT91C_SPI_TPCS        ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
#define AT91C_SPI_RDRF        ((unsigned int) 0x1 <<  0) // (SPI) Receive Data Register Full
#define AT91C_SPI_TDRE        ((unsigned int) 0x1 <<  1) // (SPI) Transmit Data Register Empty
#define AT91C_SPI_MODF        ((unsigned int) 0x1 <<  2) // (SPI) Mode Fault Error
#define AT91C_SPI_OVRES       ((unsigned int) 0x1 <<  3) // (SPI) Overrun Error Status
#define AT91C_SPI_ENDRX       ((unsigned int) 0x1 <<  4) // (SPI) End of Receiver Transfer
#define AT91C_SPI_ENDTX       ((unsigned int) 0x1 <<  5) // (SPI) End of Receiver Transfer
#define AT91C_SPI_RXBUFF      ((unsigned int) 0x1 <<  6) // (SPI) RXBUFF Interrupt
#define AT91C_SPI_TXBUFE      ((unsigned int) 0x1 <<  7) // (SPI) TXBUFE Interrupt
#define AT91C_SPI_NSSR        ((unsigned int) 0x1 <<  8) // (SPI) NSSR Interrupt
#define AT91C_SPI_TXEMPTY     ((unsigned int) 0x1 <<  9) // (SPI) TXEMPTY Interrupt
#define AT91C_SPI_SPIENS      ((unsigned int) 0x1 << 16) // (SPI) Enable Status
// -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
// -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
// -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
// -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
#define AT91C_SPI_CPOL        ((unsigned int) 0x1 <<  0) // (SPI) Clock Polarity
#define AT91C_SPI_NCPHA       ((unsigned int) 0x1 <<  1) // (SPI) Clock Phase
#define AT91C_SPI_CSAAT       ((unsigned int) 0x1 <<  3) // (SPI) Chip Select Active After Transfer
#define AT91C_SPI_BITS        ((unsigned int) 0xF <<  4) // (SPI) Bits Per Transfer
#define 	AT91C_SPI_BITS_8                    ((unsigned int) 0x0 <<  4) // (SPI) 8 Bits Per transfer
#define 	AT91C_SPI_BITS_9                    ((unsigned int) 0x1 <<  4) // (SPI) 9 Bits Per transfer
#define 	AT91C_SPI_BITS_10                   ((unsigned int) 0x2 <<  4) // (SPI) 10 Bits Per transfer
#define 	AT91C_SPI_BITS_11                   ((unsigned int) 0x3 <<  4) // (SPI) 11 Bits Per transfer
#define 	AT91C_SPI_BITS_12                   ((unsigned int) 0x4 <<  4) // (SPI) 12 Bits Per transfer
#define 	AT91C_SPI_BITS_13                   ((unsigned int) 0x5 <<  4) // (SPI) 13 Bits Per transfer
#define 	AT91C_SPI_BITS_14                   ((unsigned int) 0x6 <<  4) // (SPI) 14 Bits Per transfer
#define 	AT91C_SPI_BITS_15                   ((unsigned int) 0x7 <<  4) // (SPI) 15 Bits Per transfer
#define 	AT91C_SPI_BITS_16                   ((unsigned int) 0x8 <<  4) // (SPI) 16 Bits Per transfer
#define AT91C_SPI_SCBR        ((unsigned int) 0xFF <<  8) // (SPI) Serial Clock Baud Rate
#define AT91C_SPI_DLYBS       ((unsigned int) 0xFF << 16) // (SPI) Delay Before SPCK
#define AT91C_SPI_DLYBCT      ((unsigned int) 0xFF << 24) // (SPI) Delay Between Consecutive Transfers

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface
// *****************************************************************************
typedef struct _AT91S_CAN_MB {
	AT91_REG	 CAN_MB_MMR; 	// MailBox Mode Register
	AT91_REG	 CAN_MB_MAM; 	// MailBox Acceptance Mask Register
	AT91_REG	 CAN_MB_MID; 	// MailBox ID Register
	AT91_REG	 CAN_MB_MFID; 	// MailBox Family ID Register
	AT91_REG	 CAN_MB_MSR; 	// MailBox Status Register
	AT91_REG	 CAN_MB_MDL; 	// MailBox Data Low Register
	AT91_REG	 CAN_MB_MDH; 	// MailBox Data High Register
	AT91_REG	 CAN_MB_MCR; 	// MailBox Control Register
} AT91S_CAN_MB, *AT91PS_CAN_MB;

// -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- 
#define AT91C_CAN_MTIMEMARK   ((unsigned int) 0xFFFF <<  0) // (CAN_MB) Mailbox Timemark
#define AT91C_CAN_PRIOR       ((unsigned int) 0xF << 16) // (CAN_MB) Mailbox Priority
#define AT91C_CAN_MOT         ((unsigned int) 0x7 << 24) // (CAN_MB) Mailbox Object Type
#define 	AT91C_CAN_MOT_DIS                  ((unsigned int) 0x0 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_RX                   ((unsigned int) 0x1 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_RXOVERWRITE          ((unsigned int) 0x2 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_TX                   ((unsigned int) 0x3 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_CONSUMER             ((unsigned int) 0x4 << 24) // (CAN_MB) 
#define 	AT91C_CAN_MOT_PRODUCER             ((unsigned int) 0x5 << 24) // (CAN_MB) 
// -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- 
#define AT91C_CAN_MIDvB       ((unsigned int) 0x3FFFF <<  0) // (CAN_MB) Complementary bits for identifier in extended mode
#define AT91C_CAN_MIDvA       ((unsigned int) 0x7FF << 18) // (CAN_MB) Identifier for standard frame mode
#define AT91C_CAN_MIDE        ((unsigned int) 0x1 << 29) // (CAN_MB) Identifier Version
// -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- 
// -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- 
// -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- 
#define AT91C_CAN_MTIMESTAMP  ((unsigned int) 0xFFFF <<  0) // (CAN_MB) Timer Value
#define AT91C_CAN_MDLC        ((unsigned int) 0xF << 16) // (CAN_MB) Mailbox Data Length Code
#define AT91C_CAN_MRTR        ((unsigned int) 0x1 << 20) // (CAN_MB) Mailbox Remote Transmission Request
#define AT91C_CAN_MABT        ((unsigned int) 0x1 << 22) // (CAN_MB) Mailbox Message Abort
#define AT91C_CAN_MRDY        ((unsigned int) 0x1 << 23) // (CAN_MB) Mailbox Ready
#define AT91C_CAN_MMI         ((unsigned int) 0x1 << 24) // (CAN_MB) Mailbox Message Ignored
// -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- 
// -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- 
// -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- 
#define AT91C_CAN_MACR        ((unsigned int) 0x1 << 22) // (CAN_MB) Abort Request for Mailbox
#define AT91C_CAN_MTCR        ((unsigned int) 0x1 << 23) // (CAN_MB) Mailbox Transfer Command

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Control Area Network Interface
// *****************************************************************************
typedef struct _AT91S_CAN {
	AT91_REG	 CAN_MR; 	// Mode Register
	AT91_REG	 CAN_IER; 	// Interrupt Enable Register
	AT91_REG	 CAN_IDR; 	// Interrupt Disable Register
	AT91_REG	 CAN_IMR; 	// Interrupt Mask Register
	AT91_REG	 CAN_SR; 	// Status Register
	AT91_REG	 CAN_BR; 	// Baudrate Register
	AT91_REG	 CAN_TIM; 	// Timer Register
	AT91_REG	 CAN_TIMESTP; 	// Time Stamp Register
	AT91_REG	 CAN_ECR; 	// Error Counter Register
	AT91_REG	 CAN_TCR; 	// Transfer Command Register
	AT91_REG	 CAN_ACR; 	// Abort Command Register
	AT91_REG	 Reserved0[52]; 	// 
	AT91_REG	 CAN_VR; 	// Version Register
	AT91_REG	 Reserved1[64]; 	// 
	AT91S_CAN_MB	 CAN_MB0; 	// CAN Mailbox 0
	AT91S_CAN_MB	 CAN_MB1; 	// CAN Mailbox 1
	AT91S_CAN_MB	 CAN_MB2; 	// CAN Mailbox 2
	AT91S_CAN_MB	 CAN_MB3; 	// CAN Mailbox 3
	AT91S_CAN_MB	 CAN_MB4; 	// CAN Mailbox 4
	AT91S_CAN_MB	 CAN_MB5; 	// CAN Mailbox 5
	AT91S_CAN_MB	 CAN_MB6; 	// CAN Mailbox 6
	AT91S_CAN_MB	 CAN_MB7; 	// CAN Mailbox 7
	AT91S_CAN_MB	 CAN_MB8; 	// CAN Mailbox 8
	AT91S_CAN_MB	 CAN_MB9; 	// CAN Mailbox 9
	AT91S_CAN_MB	 CAN_MB10; 	// CAN Mailbox 10
	AT91S_CAN_MB	 CAN_MB11; 	// CAN Mailbox 11
	AT91S_CAN_MB	 CAN_MB12; 	// CAN Mailbox 12
	AT91S_CAN_MB	 CAN_MB13; 	// CAN Mailbox 13
	AT91S_CAN_MB	 CAN_MB14; 	// CAN Mailbox 14
	AT91S_CAN_MB	 CAN_MB15; 	// CAN Mailbox 15
} AT91S_CAN, *AT91PS_CAN;

// -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- 
#define AT91C_CAN_CANEN       ((unsigned int) 0x1 <<  0) // (CAN) CAN Controller Enable
#define AT91C_CAN_LPM         ((unsigned int) 0x1 <<  1) // (CAN) Disable/Enable Low Power Mode
#define AT91C_CAN_ABM         ((unsigned int) 0x1 <<  2) // (CAN) Disable/Enable Autobaud/Listen Mode
#define AT91C_CAN_OVL         ((unsigned int) 0x1 <<  3) // (CAN) Disable/Enable Overload Frame
#define AT91C_CAN_TEOF        ((unsigned int) 0x1 <<  4) // (CAN) Time Stamp messages at each end of Frame
#define AT91C_CAN_TTM         ((unsigned int) 0x1 <<  5) // (CAN) Disable/Enable Time Trigger Mode
#define AT91C_CAN_TIMFRZ      ((unsigned int) 0x1 <<  6) // (CAN) Enable Timer Freeze
#define AT91C_CAN_DRPT        ((unsigned int) 0x1 <<  7) // (CAN) Disable Repeat
// -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- 
#define AT91C_CAN_MB0         ((unsigned int) 0x1 <<  0) // (CAN) Mailbox 0 Flag
#define AT91C_CAN_MB1         ((unsigned int) 0x1 <<  1) // (CAN) Mailbox 1 Flag
#define AT91C_CAN_MB2         ((unsigned int) 0x1 <<  2) // (CAN) Mailbox 2 Flag
#define AT91C_CAN_MB3         ((unsigned int) 0x1 <<  3) // (CAN) Mailbox 3 Flag
#define AT91C_CAN_MB4         ((unsigned int) 0x1 <<  4) // (CAN) Mailbox 4 Flag
#define AT91C_CAN_MB5         ((unsigned int) 0x1 <<  5) // (CAN) Mailbox 5 Flag
#define AT91C_CAN_MB6         ((unsigned int) 0x1 <<  6) // (CAN) Mailbox 6 Flag
#define AT91C_CAN_MB7         ((unsigned int) 0x1 <<  7) // (CAN) Mailbox 7 Flag
#define AT91C_CAN_MB8         ((unsigned int) 0x1 <<  8) // (CAN) Mailbox 8 Flag
#define AT91C_CAN_MB9         ((unsigned int) 0x1 <<  9) // (CAN) Mailbox 9 Flag
#define AT91C_CAN_MB10        ((unsigned int) 0x1 << 10) // (CAN) Mailbox 10 Flag
#define AT91C_CAN_MB11        ((unsigned int) 0x1 << 11) // (CAN) Mailbox 11 Flag
#define AT91C_CAN_MB12        ((unsigned int) 0x1 << 12) // (CAN) Mailbox 12 Flag
#define AT91C_CAN_MB13        ((unsigned int) 0x1 << 13) // (CAN) Mailbox 13 Flag
#define AT91C_CAN_MB14        ((unsigned int) 0x1 << 14) // (CAN) Mailbox 14 Flag
#define AT91C_CAN_MB15        ((unsigned int) 0x1 << 15) // (CAN) Mailbox 15 Flag
#define AT91C_CAN_ERRA        ((unsigned int) 0x1 << 16) // (CAN) Error Active Mode Flag
#define AT91C_CAN_WARN        ((unsigned int) 0x1 << 17) // (CAN) Warning Limit Flag
#define AT91C_CAN_ERRP        ((unsigned int) 0x1 << 18) // (CAN) Error Passive Mode Flag
#define AT91C_CAN_BOFF        ((unsigned int) 0x1 << 19) // (CAN) Bus Off Mode Flag
#define AT91C_CAN_SLEEP       ((unsigned int) 0x1 << 20) // (CAN) Sleep Flag
#define AT91C_CAN_WAKEUP      ((unsigned int) 0x1 << 21) // (CAN) Wakeup Flag
#define AT91C_CAN_TOVF        ((unsigned int) 0x1 << 22) // (CAN) Timer Overflow Flag
#define AT91C_CAN_TSTP        ((unsigned int) 0x1 << 23) // (CAN) Timestamp Flag
#define AT91C_CAN_CERR        ((unsigned int) 0x1 << 24) // (CAN) CRC Error
#define AT91C_CAN_SERR        ((unsigned int) 0x1 << 25) // (CAN) Stuffing Error
#define AT91C_CAN_AERR        ((unsigned int) 0x1 << 26) // (CAN) Acknowledgment Error
#define AT91C_CAN_FERR        ((unsigned int) 0x1 << 27) // (CAN) Form Error
#define AT91C_CAN_BERR        ((unsigned int) 0x1 << 28) // (CAN) Bit Error
// -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- 
// -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- 
// -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- 
#define AT91C_CAN_RBSY        ((unsigned int) 0x1 << 29) // (CAN) Receiver Busy
#define AT91C_CAN_TBSY        ((unsigned int) 0x1 << 30) // (CAN) Transmitter Busy
#define AT91C_CAN_OVLY        ((unsigned int) 0x1 << 31) // (CAN) Overload Busy
// -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- 
#define AT91C_CAN_PHASE2      ((unsigned int) 0x7 <<  0) // (CAN) Phase 2 segment
#define AT91C_CAN_PHASE1      ((unsigned int) 0x7 <<  4) // (CAN) Phase 1 segment
#define AT91C_CAN_PROPAG      ((unsigned int) 0x7 <<  8) // (CAN) Programmation time segment
#define AT91C_CAN_SYNC        ((unsigned int) 0x3 << 12) // (CAN) Re-synchronization jump width segment
#define AT91C_CAN_BRP         ((unsigned int) 0x7F << 16) // (CAN) Baudrate Prescaler
#define AT91C_CAN_SMP         ((unsigned int) 0x1 << 24) // (CAN) Sampling mode
// -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- 
#define AT91C_CAN_TIMER       ((unsigned int) 0xFFFF <<  0) // (CAN) Timer field
// -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- 
// -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- 
#define AT91C_CAN_REC         ((unsigned int) 0xFF <<  0) // (CAN) Receive Error Counter
#define AT91C_CAN_TEC         ((unsigned int) 0xFF << 16) // (CAN) Transmit Error Counter
// -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- 
#define AT91C_CAN_TIMRST      ((unsigned int) 0x1 << 31) // (CAN) Timer Reset Field
// -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR PWMC Channel Interface
// *****************************************************************************
typedef struct _AT91S_PWMC_CH {
	AT91_REG	 PWMC_CMR; 	// Channel Mode Register
	AT91_REG	 PWMC_CDTYR; 	// Channel Duty Cycle Register
	AT91_REG	 PWMC_CPRDR; 	// Channel Period Register
	AT91_REG	 PWMC_CCNTR; 	// Channel Counter Register
	AT91_REG	 PWMC_CUPDR; 	// Channel Update Register
	AT91_REG	 PWMC_Reserved[3]; 	// Reserved
} AT91S_PWMC_CH, *AT91PS_PWMC_CH;

// -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- 
#define AT91C_PWMC_CPRE       ((unsigned int) 0xF <<  0) // (PWMC_CH) Channel Pre-scaler : PWMC_CLKx
#define 	AT91C_PWMC_CPRE_MCK                  ((unsigned int) 0x0) // (PWMC_CH) 
#define 	AT91C_PWMC_CPRE_MCKA                 ((unsigned int) 0xB) // (PWMC_CH) 
#define 	AT91C_PWMC_CPRE_MCKB                 ((unsigned int) 0xC) // (PWMC_CH) 
#define AT91C_PWMC_CALG       ((unsigned int) 0x1 <<  8) // (PWMC_CH) Channel Alignment
#define AT91C_PWMC_CPOL       ((unsigned int) 0x1 <<  9) // (PWMC_CH) Channel Polarity
#define AT91C_PWMC_CPD        ((unsigned int) 0x1 << 10) // (PWMC_CH) Channel Update Period
// -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- 
#define AT91C_PWMC_CDTY       ((unsigned int) 0x0 <<  0) // (PWMC_CH) Channel Duty Cycle
// -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- 
#define AT91C_PWMC_CPRD       ((unsigned int) 0x0 <<  0) // (PWMC_CH) Channel Period
// -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- 
#define AT91C_PWMC_CCNT       ((unsigned int) 0x0 <<  0) // (PWMC_CH) Channel Counter
// -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- 
#define AT91C_PWMC_CUPD       ((unsigned int) 0x0 <<  0) // (PWMC_CH) Channel Update

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
// *****************************************************************************
typedef struct _AT91S_PWMC {
	AT91_REG	 PWMC_MR; 	// PWMC Mode Register
	AT91_REG	 PWMC_ENA; 	// PWMC Enable Register
	AT91_REG	 PWMC_DIS; 	// PWMC Disable Register
	AT91_REG	 PWMC_SR; 	// PWMC Status Register
	AT91_REG	 PWMC_IER; 	// PWMC Interrupt Enable Register
	AT91_REG	 PWMC_IDR; 	// PWMC Interrupt Disable Register
	AT91_REG	 PWMC_IMR; 	// PWMC Interrupt Mask Register
	AT91_REG	 PWMC_ISR; 	// PWMC Interrupt Status Register
	AT91_REG	 Reserved0[55]; 	// 
	AT91_REG	 PWMC_VR; 	// PWMC Version Register
	AT91_REG	 Reserved1[64]; 	// 
	AT91S_PWMC_CH	 PWMC_CH[32]; 	// PWMC Channel
} AT91S_PWMC, *AT91PS_PWMC;

// -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- 
#define AT91C_PWMC_DIVA       ((unsigned int) 0xFF <<  0) // (PWMC) CLKA divide factor.
#define AT91C_PWMC_PREA       ((unsigned int) 0xF <<  8) // (PWMC) Divider Input Clock Prescaler A
#define 	AT91C_PWMC_PREA_MCK                  ((unsigned int) 0x0 <<  8) // (PWMC) 
#define AT91C_PWMC_DIVB       ((unsigned int) 0xFF << 16) // (PWMC) CLKB divide factor.
#define AT91C_PWMC_PREB       ((unsigned int) 0xF << 24) // (PWMC) Divider Input Clock Prescaler B
#define 	AT91C_PWMC_PREB_MCK                  ((unsigned int) 0x0 << 24) // (PWMC) 
// -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- 
#define AT91C_PWMC_CHID0      ((unsigned int) 0x1 <<  0) // (PWMC) Channel ID 0
#define AT91C_PWMC_CHID1      ((unsigned int) 0x1 <<  1) // (PWMC) Channel ID 1
#define AT91C_PWMC_CHID2      ((unsigned int) 0x1 <<  2) // (PWMC) Channel ID 2
#define AT91C_PWMC_CHID3      ((unsigned int) 0x1 <<  3) // (PWMC) Channel ID 3
#define AT91C_PWMC_CHID4      ((unsigned int) 0x1 <<  4) // (PWMC) Channel ID 4
#define AT91C_PWMC_CHID5      ((unsigned int) 0x1 <<  5) // (PWMC) Channel ID 5
#define AT91C_PWMC_CHID6      ((unsigned int) 0x1 <<  6) // (PWMC) Channel ID 6
#define AT91C_PWMC_CHID7      ((unsigned int) 0x1 <<  7) // (PWMC) Channel ID 7
// -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
// -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
// -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
// -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
// -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
// -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100
// *****************************************************************************
typedef struct _AT91S_EMAC {
	AT91_REG	 EMAC_NCR; 	// Network Control Register
	AT91_REG	 EMAC_NCFGR; 	// Network Configuration Register
	AT91_REG	 EMAC_NSR; 	// Network Status Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 EMAC_TSR; 	// Transmit Status Register
	AT91_REG	 EMAC_RBQP; 	// Receive Buffer Queue Pointer
	AT91_REG	 EMAC_TBQP; 	// Transmit Buffer Queue Pointer
	AT91_REG	 EMAC_RSR; 	// Receive Status Register
	AT91_REG	 EMAC_ISR; 	// Interrupt Status Register
	AT91_REG	 EMAC_IER; 	// Interrupt Enable Register
	AT91_REG	 EMAC_IDR; 	// Interrupt Disable Register
	AT91_REG	 EMAC_IMR; 	// Interrupt Mask Register
	AT91_REG	 EMAC_MAN; 	// PHY Maintenance Register
	AT91_REG	 EMAC_PTR; 	// Pause Time Register
	AT91_REG	 EMAC_PFR; 	// Pause Frames received Register
	AT91_REG	 EMAC_FTO; 	// Frames Transmitted OK Register
	AT91_REG	 EMAC_SCF; 	// Single Collision Frame Register
	AT91_REG	 EMAC_MCF; 	// Multiple Collision Frame Register
	AT91_REG	 EMAC_FRO; 	// Frames Received OK Register
	AT91_REG	 EMAC_FCSE; 	// Frame Check Sequence Error Register
	AT91_REG	 EMAC_ALE; 	// Alignment Error Register
	AT91_REG	 EMAC_DTF; 	// Deferred Transmission Frame Register
	AT91_REG	 EMAC_LCOL; 	// Late Collision Register
	AT91_REG	 EMAC_ECOL; 	// Excessive Collision Register
	AT91_REG	 EMAC_TUND; 	// Transmit Underrun Error Register
	AT91_REG	 EMAC_CSE; 	// Carrier Sense Error Register
	AT91_REG	 EMAC_RRE; 	// Receive Ressource Error Register
	AT91_REG	 EMAC_ROV; 	// Receive Overrun Errors Register
	AT91_REG	 EMAC_RSE; 	// Receive Symbol Errors Register
	AT91_REG	 EMAC_ELE; 	// Excessive Length Errors Register
	AT91_REG	 EMAC_RJA; 	// Receive Jabbers Register
	AT91_REG	 EMAC_USF; 	// Undersize Frames Register
	AT91_REG	 EMAC_STE; 	// SQE Test Error Register
	AT91_REG	 EMAC_RLE; 	// Receive Length Field Mismatch Register
	AT91_REG	 EMAC_TPF; 	// Transmitted Pause Frames Register
	AT91_REG	 EMAC_HRB; 	// Hash Address Bottom[31:0]
	AT91_REG	 EMAC_HRT; 	// Hash Address Top[63:32]
	AT91_REG	 EMAC_SA1L; 	// Specific Address 1 Bottom, First 4 bytes
	AT91_REG	 EMAC_SA1H; 	// Specific Address 1 Top, Last 2 bytes
	AT91_REG	 EMAC_SA2L; 	// Specific Address 2 Bottom, First 4 bytes
	AT91_REG	 EMAC_SA2H; 	// Specific Address 2 Top, Last 2 bytes
	AT91_REG	 EMAC_SA3L; 	// Specific Address 3 Bottom, First 4 bytes
	AT91_REG	 EMAC_SA3H; 	// Specific Address 3 Top, Last 2 bytes
	AT91_REG	 EMAC_SA4L; 	// Specific Address 4 Bottom, First 4 bytes
	AT91_REG	 EMAC_SA4H; 	// Specific Address 4 Top, Last 2 bytes
	AT91_REG	 EMAC_TID; 	// Type ID Checking Register
	AT91_REG	 EMAC_TPQ; 	// Transmit Pause Quantum Register
	AT91_REG	 EMAC_USRIO; 	// USER Input/Output Register
	AT91_REG	 EMAC_WOL; 	// Wake On LAN Register
	AT91_REG	 Reserved1[13]; 	// 
	AT91_REG	 EMAC_REV; 	// Revision Register
} AT91S_EMAC, *AT91PS_EMAC;

// -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- 
#define AT91C_EMAC_LB         ((unsigned int) 0x1 <<  0) // (EMAC) Loopback. Optional. When set, loopback signal is at high level.
#define AT91C_EMAC_LLB        ((unsigned int) 0x1 <<  1) // (EMAC) Loopback local. 
#define AT91C_EMAC_RE         ((unsigned int) 0x1 <<  2) // (EMAC) Receive enable. 
#define AT91C_EMAC_TE         ((unsigned int) 0x1 <<  3) // (EMAC) Transmit enable. 
#define AT91C_EMAC_MPE        ((unsigned int) 0x1 <<  4) // (EMAC) Management port enable. 
#define AT91C_EMAC_CLRSTAT    ((unsigned int) 0x1 <<  5) // (EMAC) Clear statistics registers. 
#define AT91C_EMAC_INCSTAT    ((unsigned int) 0x1 <<  6) // (EMAC) Increment statistics registers. 
#define AT91C_EMAC_WESTAT     ((unsigned int) 0x1 <<  7) // (EMAC) Write enable for statistics registers. 
#define AT91C_EMAC_BP         ((unsigned int) 0x1 <<  8) // (EMAC) Back pressure. 
#define AT91C_EMAC_TSTART     ((unsigned int) 0x1 <<  9) // (EMAC) Start Transmission. 
#define AT91C_EMAC_THALT      ((unsigned int) 0x1 << 10) // (EMAC) Transmission Halt. 
#define AT91C_EMAC_TPFR       ((unsigned int) 0x1 << 11) // (EMAC) Transmit pause frame 
#define AT91C_EMAC_TZQ        ((unsigned int) 0x1 << 12) // (EMAC) Transmit zero quantum pause frame
// -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- 
#define AT91C_EMAC_SPD        ((unsigned int) 0x1 <<  0) // (EMAC) Speed. 
#define AT91C_EMAC_FD         ((unsigned int) 0x1 <<  1) // (EMAC) Full duplex. 
#define AT91C_EMAC_JFRAME     ((unsigned int) 0x1 <<  3) // (EMAC) Jumbo Frames. 
#define AT91C_EMAC_CAF        ((unsigned int) 0x1 <<  4) // (EMAC) Copy all frames. 
#define AT91C_EMAC_NBC        ((unsigned int) 0x1 <<  5) // (EMAC) No broadcast. 
#define AT91C_EMAC_MTI        ((unsigned int) 0x1 <<  6) // (EMAC) Multicast hash event enable
#define AT91C_EMAC_UNI        ((unsigned int) 0x1 <<  7) // (EMAC) Unicast hash enable. 
#define AT91C_EMAC_BIG        ((unsigned int) 0x1 <<  8) // (EMAC) Receive 1522 bytes. 
#define AT91C_EMAC_EAE        ((unsigned int) 0x1 <<  9) // (EMAC) External address match enable. 
#define AT91C_EMAC_CLK        ((unsigned int) 0x3 << 10) // (EMAC) 
#define 	AT91C_EMAC_CLK_HCLK_8               ((unsigned int) 0x0 << 10) // (EMAC) HCLK divided by 8
#define 	AT91C_EMAC_CLK_HCLK_16              ((unsigned int) 0x1 << 10) // (EMAC) HCLK divided by 16
#define 	AT91C_EMAC_CLK_HCLK_32              ((unsigned int) 0x2 << 10) // (EMAC) HCLK divided by 32
#define 	AT91C_EMAC_CLK_HCLK_64              ((unsigned int) 0x3 << 10) // (EMAC) HCLK divided by 64
#define AT91C_EMAC_RTY        ((unsigned int) 0x1 << 12) // (EMAC) 
#define AT91C_EMAC_PAE        ((unsigned int) 0x1 << 13) // (EMAC) 
#define AT91C_EMAC_RBOF       ((unsigned int) 0x3 << 14) // (EMAC) 
#define 	AT91C_EMAC_RBOF_OFFSET_0             ((unsigned int) 0x0 << 14) // (EMAC) no offset from start of receive buffer
#define 	AT91C_EMAC_RBOF_OFFSET_1             ((unsigned int) 0x1 << 14) // (EMAC) one byte offset from start of receive buffer
#define 	AT91C_EMAC_RBOF_OFFSET_2             ((unsigned int) 0x2 << 14) // (EMAC) two bytes offset from start of receive buffer
#define 	AT91C_EMAC_RBOF_OFFSET_3             ((unsigned int) 0x3 << 14) // (EMAC) three bytes offset from start of receive buffer
#define AT91C_EMAC_RLCE       ((unsigned int) 0x1 << 16) // (EMAC) Receive Length field Checking Enable
#define AT91C_EMAC_DRFCS      ((unsigned int) 0x1 << 17) // (EMAC) Discard Receive FCS
#define AT91C_EMAC_EFRHD      ((unsigned int) 0x1 << 18) // (EMAC) 
#define AT91C_EMAC_IRXFCS     ((unsigned int) 0x1 << 19) // (EMAC) Ignore RX FCS
// -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- 
#define AT91C_EMAC_LINKR      ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_MDIO       ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_IDLE       ((unsigned int) 0x1 <<  2) // (EMAC) 
// -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- 
#define AT91C_EMAC_UBR        ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_COL        ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_RLES       ((unsigned int) 0x1 <<  2) // (EMAC) 
#define AT91C_EMAC_TGO        ((unsigned int) 0x1 <<  3) // (EMAC) Transmit Go
#define AT91C_EMAC_BEX        ((unsigned int) 0x1 <<  4) // (EMAC) Buffers exhausted mid frame
#define AT91C_EMAC_COMP       ((unsigned int) 0x1 <<  5) // (EMAC) 
#define AT91C_EMAC_UND        ((unsigned int) 0x1 <<  6) // (EMAC) 
// -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- 
#define AT91C_EMAC_BNA        ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_REC        ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_OVR        ((unsigned int) 0x1 <<  2) // (EMAC) 
// -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- 
#define AT91C_EMAC_MFD        ((unsigned int) 0x1 <<  0) // (EMAC) 
#define AT91C_EMAC_RCOMP      ((unsigned int) 0x1 <<  1) // (EMAC) 
#define AT91C_EMAC_RXUBR      ((unsigned int) 0x1 <<  2) // (EMAC) 
#define AT91C_EMAC_TXUBR      ((unsigned int) 0x1 <<  3) // (EMAC) 
#define AT91C_EMAC_TUNDR      ((unsigned int) 0x1 <<  4) // (EMAC) 
#define AT91C_EMAC_RLEX       ((unsigned int) 0x1 <<  5) // (EMAC) 
#define AT91C_EMAC_TXERR      ((unsigned int) 0x1 <<  6) // (EMAC) 
#define AT91C_EMAC_TCOMP      ((unsigned int) 0x1 <<  7) // (EMAC) 
#define AT91C_EMAC_LINK       ((unsigned int) 0x1 <<  9) // (EMAC) 
#define AT91C_EMAC_ROVR       ((unsigned int) 0x1 << 10) // (EMAC) 
#define AT91C_EMAC_HRESP      ((unsigned int) 0x1 << 11) // (EMAC) 
#define AT91C_EMAC_PFRE       ((unsigned int) 0x1 << 12) // (EMAC) 
#define AT91C_EMAC_PTZ        ((unsigned int) 0x1 << 13) // (EMAC) 
// -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- 
// -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- 
// -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- 
// -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- 
#define AT91C_EMAC_DATA       ((unsigned int) 0xFFFF <<  0) // (EMAC) 
#define AT91C_EMAC_CODE       ((unsigned int) 0x3 << 16) // (EMAC) 
#define AT91C_EMAC_REGA       ((unsigned int) 0x1F << 18) // (EMAC) 
#define AT91C_EMAC_PHYA       ((unsigned int) 0x1F << 23) // (EMAC) 
#define AT91C_EMAC_RW         ((unsigned int) 0x3 << 28) // (EMAC) 
#define AT91C_EMAC_SOF        ((unsigned int) 0x3 << 30) // (EMAC) 
// -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- 
#define AT91C_EMAC_RMII       ((unsigned int) 0x1 <<  0) // (EMAC) Reduce MII
#define AT91C_EMAC_CLKEN      ((unsigned int) 0x1 <<  1) // (EMAC) Clock Enable
// -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- 
#define AT91C_EMAC_IP         ((unsigned int) 0xFFFF <<  0) // (EMAC) ARP request IP address
#define AT91C_EMAC_MAG        ((unsigned int) 0x1 << 16) // (EMAC) Magic packet event enable
#define AT91C_EMAC_ARP        ((unsigned int) 0x1 << 17) // (EMAC) ARP request event enable
#define AT91C_EMAC_SA1        ((unsigned int) 0x1 << 18) // (EMAC) Specific address register 1 event enable
// -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- 
#define AT91C_EMAC_REVREF     ((unsigned int) 0xFFFF <<  0) // (EMAC) 
#define AT91C_EMAC_PARTREF    ((unsigned int) 0xFFFF << 16) // (EMAC) 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR LCD Controller
// *****************************************************************************
typedef struct _AT91S_LCDC {
	AT91_REG	 LCDC_BA1; 	// DMA Base Address Register 1
	AT91_REG	 LCDC_BA2; 	// DMA Base Address Register 2
	AT91_REG	 LCDC_FRMP1; 	// DMA Frame Pointer Register 1
	AT91_REG	 LCDC_FRMP2; 	// DMA Frame Pointer Register 2
	AT91_REG	 LCDC_FRMA1; 	// DMA Frame Address Register 1
	AT91_REG	 LCDC_FRMA2; 	// DMA Frame Address Register 2
	AT91_REG	 LCDC_FRMCFG; 	// DMA Frame Configuration Register
	AT91_REG	 LCDC_DMACON; 	// DMA Control Register
	AT91_REG	 LCDC_DMA2DCFG; 	// DMA 2D addressing configuration
	AT91_REG	 Reserved0[503]; 	// 
	AT91_REG	 LCDC_LCDCON1; 	// LCD Control 1 Register
	AT91_REG	 LCDC_LCDCON2; 	// LCD Control 2 Register
	AT91_REG	 LCDC_TIM1; 	// LCD Timing Config 1 Register
	AT91_REG	 LCDC_TIM2; 	// LCD Timing Config 2 Register
	AT91_REG	 LCDC_LCDFRCFG; 	// LCD Frame Config Register
	AT91_REG	 LCDC_FIFO; 	// LCD FIFO Register
	AT91_REG	 LCDC_MVAL; 	// LCD Mode Toggle Rate Value Register
	AT91_REG	 LCDC_DP1_2; 	// Dithering Pattern DP1_2 Register
	AT91_REG	 LCDC_DP4_7; 	// Dithering Pattern DP4_7 Register
	AT91_REG	 LCDC_DP3_5; 	// Dithering Pattern DP3_5 Register
	AT91_REG	 LCDC_DP2_3; 	// Dithering Pattern DP2_3 Register
	AT91_REG	 LCDC_DP5_7; 	// Dithering Pattern DP5_7 Register
	AT91_REG	 LCDC_DP3_4; 	// Dithering Pattern DP3_4 Register
	AT91_REG	 LCDC_DP4_5; 	// Dithering Pattern DP4_5 Register
	AT91_REG	 LCDC_DP6_7; 	// Dithering Pattern DP6_7 Register
	AT91_REG	 LCDC_PWRCON; 	// Power Control Register
	AT91_REG	 LCDC_CTRSTCON; 	// Contrast Control Register
	AT91_REG	 LCDC_CTRSTVAL; 	// Contrast Value Register
	AT91_REG	 LCDC_IER; 	// Interrupt Enable Register
	AT91_REG	 LCDC_IDR; 	// Interrupt Disable Register
	AT91_REG	 LCDC_IMR; 	// Interrupt Mask Register
	AT91_REG	 LCDC_ISR; 	// Interrupt Enable Register
	AT91_REG	 LCDC_ICR; 	// Interrupt Clear Register
	AT91_REG	 LCDC_GPR; 	// General Purpose Register
	AT91_REG	 LCDC_ITR; 	// Interrupts Test Register
	AT91_REG	 LCDC_IRR; 	// Interrupts Raw Status Register
	AT91_REG	 Reserved1[230]; 	// 
	AT91_REG	 LCDC_LUT_ENTRY[256]; 	// LUT Entries Register
} AT91S_LCDC, *AT91PS_LCDC;

// -------- LCDC_FRMP1 : (LCDC Offset: 0x8) DMA Frame Pointer 1 Register -------- 
#define AT91C_LCDC_FRMPT1     ((unsigned int) 0x3FFFFF <<  0) // (LCDC) Frame Pointer Address 1
// -------- LCDC_FRMP2 : (LCDC Offset: 0xc) DMA Frame Pointer 2 Register -------- 
#define AT91C_LCDC_FRMPT2     ((unsigned int) 0x1FFFFF <<  0) // (LCDC) Frame Pointer Address 2
// -------- LCDC_FRMCFG : (LCDC Offset: 0x18) DMA Frame Config Register -------- 
#define AT91C_LCDC_FRSIZE     ((unsigned int) 0x3FFFFF <<  0) // (LCDC) FRAME SIZE
#define AT91C_LCDC_BLENGTH    ((unsigned int) 0xF << 24) // (LCDC) BURST LENGTH
// -------- LCDC_DMACON : (LCDC Offset: 0x1c) DMA Control Register -------- 
#define AT91C_LCDC_DMAEN      ((unsigned int) 0x1 <<  0) // (LCDC) DAM Enable
#define AT91C_LCDC_DMARST     ((unsigned int) 0x1 <<  1) // (LCDC) DMA Reset (WO)
#define AT91C_LCDC_DMABUSY    ((unsigned int) 0x1 <<  2) // (LCDC) DMA Reset (WO)
#define AT91C_LCDC_DMAUPDT    ((unsigned int) 0x1 <<  3) // (LCDC) DMA Configuration Update
#define AT91C_LCDC_DMA2DEN    ((unsigned int) 0x1 <<  4) // (LCDC) 2D Addressing Enable
// -------- LCDC_DMA2DCFG : (LCDC Offset: 0x20) DMA 2D addressing configuration Register -------- 
#define AT91C_LCDC_ADDRINC    ((unsigned int) 0xFFFF <<  0) // (LCDC) Number of 32b words that the DMA must jump when going to the next line
#define AT91C_LCDC_PIXELOFF   ((unsigned int) 0x1F << 24) // (LCDC) Offset (in bits) of the first pixel of the screen in the memory word which contain it
// -------- LCDC_LCDCON1 : (LCDC Offset: 0x800) LCD Control 1 Register -------- 
#define AT91C_LCDC_BYPASS     ((unsigned int) 0x1 <<  0) // (LCDC) Bypass lcd_pccklk divider
#define AT91C_LCDC_CLKVAL     ((unsigned int) 0x1FF << 12) // (LCDC) 9-bit Divider for pixel clock frequency
#define AT91C_LCDC_LINCNT     ((unsigned int) 0x7FF << 21) // (LCDC) Line Counter (RO)
// -------- LCDC_LCDCON2 : (LCDC Offset: 0x804) LCD Control 2 Register -------- 
#define AT91C_LCDC_DISTYPE    ((unsigned int) 0x3 <<  0) // (LCDC) Display Type
#define 	AT91C_LCDC_DISTYPE_STNMONO              ((unsigned int) 0x0) // (LCDC) STN Mono
#define 	AT91C_LCDC_DISTYPE_STNCOLOR             ((unsigned int) 0x1) // (LCDC) STN Color
#define 	AT91C_LCDC_DISTYPE_TFT                  ((unsigned int) 0x2) // (LCDC) TFT
#define AT91C_LCDC_SCANMOD    ((unsigned int) 0x1 <<  2) // (LCDC) Scan Mode
#define 	AT91C_LCDC_SCANMOD_SINGLESCAN           ((unsigned int) 0x0 <<  2) // (LCDC) Single Scan
#define 	AT91C_LCDC_SCANMOD_DUALSCAN             ((unsigned int) 0x1 <<  2) // (LCDC) Dual Scan
#define AT91C_LCDC_IFWIDTH    ((unsigned int) 0x3 <<  3) // (LCDC) Interface Width
#define 	AT91C_LCDC_IFWIDTH_FOURBITSWIDTH        ((unsigned int) 0x0 <<  3) // (LCDC) 4 Bits
#define 	AT91C_LCDC_IFWIDTH_EIGTHBITSWIDTH       ((unsigned int) 0x1 <<  3) // (LCDC) 8 Bits
#define 	AT91C_LCDC_IFWIDTH_SIXTEENBITSWIDTH     ((unsigned int) 0x2 <<  3) // (LCDC) 16 Bits
#define AT91C_LCDC_PIXELSIZE  ((unsigned int) 0x7 <<  5) // (LCDC) Bits per pixel
#define 	AT91C_LCDC_PIXELSIZE_ONEBITSPERPIXEL      ((unsigned int) 0x0 <<  5) // (LCDC) 1 Bits
#define 	AT91C_LCDC_PIXELSIZE_TWOBITSPERPIXEL      ((unsigned int) 0x1 <<  5) // (LCDC) 2 Bits
#define 	AT91C_LCDC_PIXELSIZE_FOURBITSPERPIXEL     ((unsigned int) 0x2 <<  5) // (LCDC) 4 Bits
#define 	AT91C_LCDC_PIXELSIZE_EIGTHBITSPERPIXEL    ((unsigned int) 0x3 <<  5) // (LCDC) 8 Bits
#define 	AT91C_LCDC_PIXELSIZE_SIXTEENBITSPERPIXEL  ((unsigned int) 0x4 <<  5) // (LCDC) 16 Bits
#define 	AT91C_LCDC_PIXELSIZE_TWENTYFOURBITSPERPIXEL ((unsigned int) 0x5 <<  5) // (LCDC) 24 Bits
#define AT91C_LCDC_INVVD      ((unsigned int) 0x1 <<  8) // (LCDC) lcd datas polarity
#define 	AT91C_LCDC_INVVD_NORMALPOL            ((unsigned int) 0x0 <<  8) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVVD_INVERTEDPOL          ((unsigned int) 0x1 <<  8) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVFRAME   ((unsigned int) 0x1 <<  9) // (LCDC) lcd vsync polarity
#define 	AT91C_LCDC_INVFRAME_NORMALPOL            ((unsigned int) 0x0 <<  9) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVFRAME_INVERTEDPOL          ((unsigned int) 0x1 <<  9) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVLINE    ((unsigned int) 0x1 << 10) // (LCDC) lcd hsync polarity
#define 	AT91C_LCDC_INVLINE_NORMALPOL            ((unsigned int) 0x0 << 10) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVLINE_INVERTEDPOL          ((unsigned int) 0x1 << 10) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVCLK     ((unsigned int) 0x1 << 11) // (LCDC) lcd pclk polarity
#define 	AT91C_LCDC_INVCLK_NORMALPOL            ((unsigned int) 0x0 << 11) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVCLK_INVERTEDPOL          ((unsigned int) 0x1 << 11) // (LCDC) Inverted Polarity
#define AT91C_LCDC_INVDVAL    ((unsigned int) 0x1 << 12) // (LCDC) lcd dval polarity
#define 	AT91C_LCDC_INVDVAL_NORMALPOL            ((unsigned int) 0x0 << 12) // (LCDC) Normal Polarity
#define 	AT91C_LCDC_INVDVAL_INVERTEDPOL          ((unsigned int) 0x1 << 12) // (LCDC) Inverted Polarity
#define AT91C_LCDC_CLKMOD     ((unsigned int) 0x1 << 15) // (LCDC) lcd pclk Mode
#define 	AT91C_LCDC_CLKMOD_ACTIVEONLYDISP       ((unsigned int) 0x0 << 15) // (LCDC) Active during display period
#define 	AT91C_LCDC_CLKMOD_ALWAYSACTIVE         ((unsigned int) 0x1 << 15) // (LCDC) Always Active
#define AT91C_LCDC_MEMOR      ((unsigned int) 0x1 << 31) // (LCDC) lcd pclk Mode
#define 	AT91C_LCDC_MEMOR_BIGIND               ((unsigned int) 0x0 << 31) // (LCDC) Big Endian
#define 	AT91C_LCDC_MEMOR_LITTLEIND            ((unsigned int) 0x1 << 31) // (LCDC) Little Endian
// -------- LCDC_TIM1 : (LCDC Offset: 0x808) LCDC Timing Config 1 Register -------- 
#define AT91C_LCDC_VFP        ((unsigned int) 0xFF <<  0) // (LCDC) Vertical Front Porch
#define AT91C_LCDC_VBP        ((unsigned int) 0xFF <<  8) // (LCDC) Vertical Back Porch
#define AT91C_LCDC_VPW        ((unsigned int) 0x3F << 16) // (LCDC) Vertical Synchronization Pulse Width
#define AT91C_LCDC_VHDLY      ((unsigned int) 0xF << 24) // (LCDC) Vertical to Horizontal Delay
// -------- LCDC_TIM2 : (LCDC Offset: 0x80c) LCDC Timing Config 2 Register -------- 
#define AT91C_LCDC_HBP        ((unsigned int) 0xFF <<  0) // (LCDC) Horizontal Back Porch
#define AT91C_LCDC_HPW        ((unsigned int) 0x3F <<  8) // (LCDC) Horizontal Synchronization Pulse Width
#define AT91C_LCDC_HFP        ((unsigned int) 0x3FF << 22) // (LCDC) Horizontal Front Porch
// -------- LCDC_LCDFRCFG : (LCDC Offset: 0x810) LCD Frame Config Register -------- 
#define AT91C_LCDC_LINEVAL    ((unsigned int) 0x7FF <<  0) // (LCDC) Vertical Size of LCD Module
#define AT91C_LCDC_HOZVAL     ((unsigned int) 0x7FF << 21) // (LCDC) Horizontal Size of LCD Module
// -------- LCDC_FIFO : (LCDC Offset: 0x814) LCD FIFO Register -------- 
#define AT91C_LCDC_FIFOTH     ((unsigned int) 0xFFFF <<  0) // (LCDC) FIFO Threshold
// -------- LCDC_MVAL : (LCDC Offset: 0x818) LCD Mode Toggle Rate Value Register -------- 
#define AT91C_LCDC_MVALUE     ((unsigned int) 0xFF <<  0) // (LCDC) Toggle Rate Value
#define AT91C_LCDC_MMODE      ((unsigned int) 0x1 << 31) // (LCDC) Toggle Rate Sel
#define 	AT91C_LCDC_MMODE_EACHFRAME            ((unsigned int) 0x0 << 31) // (LCDC) Each Frame
#define 	AT91C_LCDC_MMODE_MVALDEFINED          ((unsigned int) 0x1 << 31) // (LCDC) Defined by MVAL
// -------- LCDC_DP1_2 : (LCDC Offset: 0x81c) Dithering Pattern 1/2 -------- 
#define AT91C_LCDC_DP1_2_FIELD ((unsigned int) 0xFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP4_7 : (LCDC Offset: 0x820) Dithering Pattern 4/7 -------- 
#define AT91C_LCDC_DP4_7_FIELD ((unsigned int) 0xFFFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP3_5 : (LCDC Offset: 0x824) Dithering Pattern 3/5 -------- 
#define AT91C_LCDC_DP3_5_FIELD ((unsigned int) 0xFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP2_3 : (LCDC Offset: 0x828) Dithering Pattern 2/3 -------- 
#define AT91C_LCDC_DP2_3_FIELD ((unsigned int) 0xFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP5_7 : (LCDC Offset: 0x82c) Dithering Pattern 5/7 -------- 
#define AT91C_LCDC_DP5_7_FIELD ((unsigned int) 0xFFFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP3_4 : (LCDC Offset: 0x830) Dithering Pattern 3/4 -------- 
#define AT91C_LCDC_DP3_4_FIELD ((unsigned int) 0xFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP4_5 : (LCDC Offset: 0x834) Dithering Pattern 4/5 -------- 
#define AT91C_LCDC_DP4_5_FIELD ((unsigned int) 0xFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_DP6_7 : (LCDC Offset: 0x838) Dithering Pattern 6/7 -------- 
#define AT91C_LCDC_DP6_7_FIELD ((unsigned int) 0xFFFFFFF <<  0) // (LCDC) Ratio
// -------- LCDC_PWRCON : (LCDC Offset: 0x83c) LCDC Power Control Register -------- 
#define AT91C_LCDC_PWR        ((unsigned int) 0x1 <<  0) // (LCDC) LCD Module Power Control
#define AT91C_LCDC_GUARDT     ((unsigned int) 0x7F <<  1) // (LCDC) Delay in Frame Period
#define AT91C_LCDC_BUSY       ((unsigned int) 0x1 << 31) // (LCDC) Read Only : 1 indicates that LCDC is busy
#define 	AT91C_LCDC_BUSY_LCDNOTBUSY           ((unsigned int) 0x0 << 31) // (LCDC) LCD is Not Busy
#define 	AT91C_LCDC_BUSY_LCDBUSY              ((unsigned int) 0x1 << 31) // (LCDC) LCD is Busy
// -------- LCDC_CTRSTCON : (LCDC Offset: 0x840) LCDC Contrast Control Register -------- 
#define AT91C_LCDC_PS         ((unsigned int) 0x3 <<  0) // (LCDC) LCD Contrast Counter Prescaler
#define 	AT91C_LCDC_PS_NOTDIVIDED           ((unsigned int) 0x0) // (LCDC) Counter Freq is System Freq.
#define 	AT91C_LCDC_PS_DIVIDEDBYTWO         ((unsigned int) 0x1) // (LCDC) Counter Freq is System Freq divided by 2.
#define 	AT91C_LCDC_PS_DIVIDEDBYFOUR        ((unsigned int) 0x2) // (LCDC) Counter Freq is System Freq divided by 4.
#define 	AT91C_LCDC_PS_DIVIDEDBYEIGHT       ((unsigned int) 0x3) // (LCDC) Counter Freq is System Freq divided by 8.
#define AT91C_LCDC_POL        ((unsigned int) 0x1 <<  2) // (LCDC) Polarity of output Pulse
#define 	AT91C_LCDC_POL_NEGATIVEPULSE        ((unsigned int) 0x0 <<  2) // (LCDC) Negative Pulse
#define 	AT91C_LCDC_POL_POSITIVEPULSE        ((unsigned int) 0x1 <<  2) // (LCDC) Positive Pulse
#define AT91C_LCDC_ENA        ((unsigned int) 0x1 <<  3) // (LCDC) PWM generator Control
#define 	AT91C_LCDC_ENA_PWMGEMDISABLED       ((unsigned int) 0x0 <<  3) // (LCDC) PWM Generator Disabled
#define 	AT91C_LCDC_ENA_PWMGEMENABLED        ((unsigned int) 0x1 <<  3) // (LCDC) PWM Generator Disabled
// -------- LCDC_CTRSTVAL : (LCDC Offset: 0x844) Contrast Value Register -------- 
#define AT91C_LCDC_CVAL       ((unsigned int) 0xFF <<  0) // (LCDC) PWM Compare Value
// -------- LCDC_IER : (LCDC Offset: 0x848) LCDC Interrupt Enable Register -------- 
#define AT91C_LCDC_LNI        ((unsigned int) 0x1 <<  0) // (LCDC) Line Interrupt
#define AT91C_LCDC_LSTLNI     ((unsigned int) 0x1 <<  1) // (LCDC) Last Line Interrupt
#define AT91C_LCDC_EOFI       ((unsigned int) 0x1 <<  2) // (LCDC) End Of Frame Interrupt
#define AT91C_LCDC_UFLWI      ((unsigned int) 0x1 <<  4) // (LCDC) FIFO Underflow Interrupt
#define AT91C_LCDC_OWRI       ((unsigned int) 0x1 <<  5) // (LCDC) Over Write Interrupt
#define AT91C_LCDC_MERI       ((unsigned int) 0x1 <<  6) // (LCDC) Memory Error  Interrupt
// -------- LCDC_IDR : (LCDC Offset: 0x84c) LCDC Interrupt Disable Register -------- 
// -------- LCDC_IMR : (LCDC Offset: 0x850) LCDC Interrupt Mask Register -------- 
// -------- LCDC_ISR : (LCDC Offset: 0x854) LCDC Interrupt Status Register -------- 
// -------- LCDC_ICR : (LCDC Offset: 0x858) LCDC Interrupt Clear Register -------- 
// -------- LCDC_GPR : (LCDC Offset: 0x85c) LCDC General Purpose Register -------- 
#define AT91C_LCDC_GPRBUS     ((unsigned int) 0xFF <<  0) // (LCDC) 8 bits available
// -------- LCDC_ITR : (LCDC Offset: 0x860) Interrupts Test Register -------- 
// -------- LCDC_IRR : (LCDC Offset: 0x864) Interrupts Raw Status Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR DMA controller from Synopsys
// *****************************************************************************
typedef struct _AT91S_DMA {
	AT91_REG	 DMA_SAR0; 	// Source Address Register for channel 0
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 DMA_DAR0; 	// Destination Address Register for channel 0
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 DMA_LLP0; 	// Linked List Pointer Register for channel 0
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 DMA_CTL0l; 	// Control Register for channel 0 - low
	AT91_REG	 DMA_CTL0h; 	// Control Register for channel 0 - high
	AT91_REG	 DMA_SSTAT0; 	// Source Status Register for channel 0
	AT91_REG	 Reserved3[1]; 	// 
	AT91_REG	 DMA_DSTAT0; 	// Destination Status Register for channel 0
	AT91_REG	 Reserved4[1]; 	// 
	AT91_REG	 DMA_SSTATAR0; 	// Source Status Adress Register for channel 0
	AT91_REG	 Reserved5[1]; 	// 
	AT91_REG	 DMA_DSTATAR0; 	// Destination Status Adress Register for channel 0
	AT91_REG	 Reserved6[1]; 	// 
	AT91_REG	 DMA_CFG0l; 	// Configuration Register for channel 0 - low
	AT91_REG	 DMA_CFG0h; 	// Configuration Register for channel 0 - high
	AT91_REG	 DMA_SGR0; 	// Source Gather Register for channel 0
	AT91_REG	 Reserved7[1]; 	// 
	AT91_REG	 DMA_DSR0; 	// Destination Scatter Register for channel 0
	AT91_REG	 Reserved8[1]; 	// 
	AT91_REG	 DMA_SAR1; 	// Source Address Register for channel 1
	AT91_REG	 Reserved9[1]; 	// 
	AT91_REG	 DMA_DAR1; 	// Destination Address Register for channel 1
	AT91_REG	 Reserved10[1]; 	// 
	AT91_REG	 DMA_LLP1; 	// Linked List Pointer Register for channel 1
	AT91_REG	 Reserved11[1]; 	// 
	AT91_REG	 DMA_CTL1l; 	// Control Register for channel 1 - low
	AT91_REG	 DMA_CTL1h; 	// Control Register for channel 1 - high
	AT91_REG	 DMA_SSTAT1; 	// Source Status Register for channel 1
	AT91_REG	 Reserved12[1]; 	// 
	AT91_REG	 DMA_DSTAT1; 	// Destination Status Register for channel 1
	AT91_REG	 Reserved13[1]; 	// 
	AT91_REG	 DMA_SSTATAR1; 	// Source Status Adress Register for channel 1
	AT91_REG	 Reserved14[1]; 	// 
	AT91_REG	 DMA_DSTATAR1; 	// Destination Status Adress Register for channel 1
	AT91_REG	 Reserved15[1]; 	// 
	AT91_REG	 DMA_CFG1l; 	// Configuration Register for channel 1 - low
	AT91_REG	 DMA_CFG1h; 	// Configuration Register for channel 1 - high
	AT91_REG	 DMA_SGR1; 	// Source Gather Register for channel 1
	AT91_REG	 Reserved16[1]; 	// 
	AT91_REG	 DMA_DSR1; 	// Destination Scatter Register for channel 1
	AT91_REG	 Reserved17[133]; 	// 
	AT91_REG	 DMA_RAWTFR; 	// Raw Status for IntTfr Interrupt
	AT91_REG	 Reserved18[1]; 	// 
	AT91_REG	 DMA_RAWBLOCK; 	// Raw Status for IntBlock Interrupt
	AT91_REG	 Reserved19[1]; 	// 
	AT91_REG	 DMA_RAWSRCTRAN; 	// Raw Status for IntSrcTran Interrupt
	AT91_REG	 Reserved20[1]; 	// 
	AT91_REG	 DMA_RAWDSTTRAN; 	// Raw Status for IntDstTran Interrupt
	AT91_REG	 Reserved21[1]; 	// 
	AT91_REG	 DMA_RAWERR; 	// Raw Status for IntErr Interrupt
	AT91_REG	 Reserved22[1]; 	// 
	AT91_REG	 DMA_STATUSTFR; 	// Status for IntTfr Interrupt
	AT91_REG	 Reserved23[1]; 	// 
	AT91_REG	 DMA_STATUSBLOCK; 	// Status for IntBlock Interrupt
	AT91_REG	 Reserved24[1]; 	// 
	AT91_REG	 DMA_STATUSSRCTRAN; 	// Status for IntSrcTran Interrupt
	AT91_REG	 Reserved25[1]; 	// 
	AT91_REG	 DMA_STATUSDSTTRAN; 	// Status for IntDstTran IInterrupt
	AT91_REG	 Reserved26[1]; 	// 
	AT91_REG	 DMA_STATUSERR; 	// Status for IntErr IInterrupt
	AT91_REG	 Reserved27[1]; 	// 
	AT91_REG	 DMA_MASKTFR; 	// Mask for IntTfr Interrupt
	AT91_REG	 Reserved28[1]; 	// 
	AT91_REG	 DMA_MASKBLOCK; 	// Mask for IntBlock Interrupt
	AT91_REG	 Reserved29[1]; 	// 
	AT91_REG	 DMA_MASKSRCTRAN; 	// Mask for IntSrcTran Interrupt
	AT91_REG	 Reserved30[1]; 	// 
	AT91_REG	 DMA_MASKDSTTRAN; 	// Mask for IntDstTran Interrupt
	AT91_REG	 Reserved31[1]; 	// 
	AT91_REG	 DMA_MASKERR; 	// Mask for IntErr Interrupt
	AT91_REG	 Reserved32[1]; 	// 
	AT91_REG	 DMA_CLEARTFR; 	// Clear for IntTfr Interrupt
	AT91_REG	 Reserved33[1]; 	// 
	AT91_REG	 DMA_CLEARBLOCK; 	// Clear for IntBlock Interrupt
	AT91_REG	 Reserved34[1]; 	// 
	AT91_REG	 DMA_CLEARSRCTRAN; 	// Clear for IntSrcTran Interrupt
	AT91_REG	 Reserved35[1]; 	// 
	AT91_REG	 DMA_CLEARDSTTRAN; 	// Clear for IntDstTran IInterrupt
	AT91_REG	 Reserved36[1]; 	// 
	AT91_REG	 DMA_CLEARERR; 	// Clear for IntErr Interrupt
	AT91_REG	 Reserved37[1]; 	// 
	AT91_REG	 DMA_STATUSINT; 	// Status for each Interrupt Type
	AT91_REG	 Reserved38[1]; 	// 
	AT91_REG	 DMA_REQSRCREG; 	// Source Software Transaction Request Register
	AT91_REG	 Reserved39[1]; 	// 
	AT91_REG	 DMA_REQDSTREG; 	// Destination Software Transaction Request Register
	AT91_REG	 Reserved40[1]; 	// 
	AT91_REG	 DMA_SGLREQSRCREG; 	// Single Source Software Transaction Request Register
	AT91_REG	 Reserved41[1]; 	// 
	AT91_REG	 DMA_SGLREQDSTREG; 	// Single Destination Software Transaction Request Register
	AT91_REG	 Reserved42[1]; 	// 
	AT91_REG	 DMA_LSTREQSRCREG; 	// Last Source Software Transaction Request Register
	AT91_REG	 Reserved43[1]; 	// 
	AT91_REG	 DMA_LSTREQDSTREG; 	// Last Destination Software Transaction Request Register
	AT91_REG	 Reserved44[1]; 	// 
	AT91_REG	 DMA_DMACFGREG; 	// DW_ahb_dmac Configuration Register
	AT91_REG	 Reserved45[1]; 	// 
	AT91_REG	 DMA_CHENREG; 	// DW_ahb_dmac Channel Enable Register
	AT91_REG	 Reserved46[1]; 	// 
	AT91_REG	 DMA_DMAIDREG; 	// DW_ahb_dmac ID Register
	AT91_REG	 Reserved47[1]; 	// 
	AT91_REG	 DMA_DMATESTREG; 	// DW_ahb_dmac Test Register
	AT91_REG	 Reserved48[1]; 	// 
	AT91_REG	 DMA_VERSIONID; 	// DW_ahb_dmac Version ID Register
} AT91S_DMA, *AT91PS_DMA;

// -------- DMA_SAR : (DMA Offset: 0x0)  -------- 
#define AT91C_DMA_SADD        ((unsigned int) 0x0 <<  0) // (DMA) Source Address of DMA Transfer
// -------- DMA_DAR : (DMA Offset: 0x8)  -------- 
#define AT91C_DMA_DADD        ((unsigned int) 0x0 <<  0) // (DMA) Destination Address of DMA Transfer
// -------- DMA_LLP : (DMA Offset: 0x10)  -------- 
#define AT91C_DMA_LOC         ((unsigned int) 0x0 <<  0) // (DMA) Address of the Next LLI
// -------- DMA_CTLl : (DMA Offset: 0x18)  -------- 
#define AT91C_DMA_INT_EN      ((unsigned int) 0x1 <<  0) // (DMA) Interrupt Enable Bit
#define AT91C_DMA_DST_TR_WIDTH ((unsigned int) 0x7 <<  1) // (DMA) Destination Transfer Width
#define AT91C_DMA_SRC_TR_WIDTH ((unsigned int) 0x7 <<  4) // (DMA) Source Transfer Width
#define AT91C_DMA_DINC        ((unsigned int) 0x3 <<  7) // (DMA) Destination Address Increment
#define AT91C_DMA_SINC        ((unsigned int) 0x3 <<  9) // (DMA) Source Address Increment
#define AT91C_DMA_DEST_MSIZE  ((unsigned int) 0x7 << 11) // (DMA) Destination Burst Transaction Length
#define AT91C_DMA_SRC_MSIZE   ((unsigned int) 0x7 << 14) // (DMA) Source Burst Transaction Length
#define AT91C_DMA_S_GATH_EN   ((unsigned int) 0x1 << 17) // (DMA) Source Gather Enable Bit
#define AT91C_DMA_D_SCAT_EN   ((unsigned int) 0x1 << 18) // (DMA) Destination Scatter Enable Bit
#define AT91C_DMA_TT_FC       ((unsigned int) 0x7 << 20) // (DMA) Transfer Type and Flow Control
#define AT91C_DMA_DMS         ((unsigned int) 0x3 << 23) // (DMA) Destination Master Select
#define AT91C_DMA_SMS         ((unsigned int) 0x3 << 25) // (DMA) Source Master Select
#define AT91C_DMA_LLP_D_EN    ((unsigned int) 0x1 << 27) // (DMA) Destination Block Chaining Enable
#define AT91C_DMA_LLP_S_EN    ((unsigned int) 0x1 << 28) // (DMA) Source Block Chaining Enable
// -------- DMA_CTLh : (DMA Offset: 0x1c)  -------- 
#define AT91C_DMA_BLOCK_TS    ((unsigned int) 0xFFF <<  0) // (DMA) Block Transfer Size
#define AT91C_DMA_DONE        ((unsigned int) 0x1 << 12) // (DMA) Done bit
// -------- DMA_CFGl : (DMA Offset: 0x40)  -------- 
#define AT91C_DMA_CH_PRIOR    ((unsigned int) 0x7 <<  5) // (DMA) Channel Priority
#define AT91C_DMA_CH_SUSP     ((unsigned int) 0x1 <<  8) // (DMA) Channel Suspend
#define AT91C_DMA_FIFO_EMPT   ((unsigned int) 0x1 <<  9) // (DMA) Fifo Empty
#define AT91C_DMA_HS_SEL_DS   ((unsigned int) 0x1 << 10) // (DMA) Destination Software or Hardware Handshaking Select
#define AT91C_DMA_HS_SEL_SR   ((unsigned int) 0x1 << 11) // (DMA) Source Software or Hardware Handshaking Select
#define AT91C_DMA_LOCK_CH_L   ((unsigned int) 0x3 << 12) // (DMA) Channel Lock Level
#define AT91C_DMA_LOCK_B_L    ((unsigned int) 0x3 << 14) // (DMA) Bus Lock Level
#define AT91C_DMA_LOCK_CH     ((unsigned int) 0x1 << 16) // (DMA) Channel Lock Bit
#define AT91C_DMA_LOCK_B      ((unsigned int) 0x1 << 17) // (DMA) Bus Lock Bit
#define AT91C_DMA_DS_HS_POL   ((unsigned int) 0x1 << 18) // (DMA) Destination Handshaking Interface Polarity
#define AT91C_DMA_SR_HS_POL   ((unsigned int) 0x1 << 19) // (DMA) Source Handshaking Interface Polarity
#define AT91C_DMA_MAX_ABRST   ((unsigned int) 0x3FF << 20) // (DMA) Maximum AMBA Burst Length
#define AT91C_DMA_RELOAD_SR   ((unsigned int) 0x1 << 30) // (DMA) Automatic Source Reload
#define AT91C_DMA_RELOAD_DS   ((unsigned int) 0x1 << 31) // (DMA) Automatic Destination Reload
// -------- DMA_CFGh : (DMA Offset: 0x44)  -------- 
#define AT91C_DMA_FCMODE      ((unsigned int) 0x1 <<  0) // (DMA) Flow Control Mode
#define AT91C_DMA_FIFO_MODE   ((unsigned int) 0x1 <<  1) // (DMA) Fifo Mode Select
#define AT91C_DMA_PROTCTL     ((unsigned int) 0x7 <<  2) // (DMA) Protection Control
#define AT91C_DMA_DS_UPD_EN   ((unsigned int) 0x1 <<  5) // (DMA) Destination Status Update Enable
#define AT91C_DMA_SS_UPD_EN   ((unsigned int) 0x1 <<  6) // (DMA) Source Status Update Enable
#define AT91C_DMA_SRC_PER     ((unsigned int) 0xF <<  7) // (DMA) Source Hardware Handshaking Interface
#define AT91C_DMA_DEST_PER    ((unsigned int) 0xF << 11) // (DMA) Destination Hardware Handshaking Interface
// -------- DMA_SGR : (DMA Offset: 0x48)  -------- 
#define AT91C_DMA_SGI         ((unsigned int) 0xFFFFF <<  0) // (DMA) Source Gather Interval
#define AT91C_DMA_SGC         ((unsigned int) 0xFFF << 20) // (DMA) Source Gather Count
// -------- DMA_DSR : (DMA Offset: 0x50)  -------- 
#define AT91C_DMA_DSI         ((unsigned int) 0xFFFFF <<  0) // (DMA) Destination Scatter Interval
#define AT91C_DMA_DSC         ((unsigned int) 0xFFF << 20) // (DMA) Destination Scatter Count
// -------- DMA_SAR : (DMA Offset: 0x58)  -------- 
// -------- DMA_DAR : (DMA Offset: 0x60)  -------- 
// -------- DMA_LLP : (DMA Offset: 0x68)  -------- 
// -------- DMA_CTLl : (DMA Offset: 0x70)  -------- 
// -------- DMA_CTLh : (DMA Offset: 0x74)  -------- 
// -------- DMA_CFGl : (DMA Offset: 0x98)  -------- 
// -------- DMA_CFGh : (DMA Offset: 0x9c)  -------- 
// -------- DMA_SGR : (DMA Offset: 0xa0)  -------- 
// -------- DMA_DSR : (DMA Offset: 0xa8)  -------- 
// -------- DMA_RAWTFR : (DMA Offset: 0x2c0)  -------- 
#define AT91C_DMA_RAW         ((unsigned int) 0x7 <<  0) // (DMA) Raw Interrupt for each Channel
// -------- DMA_RAWBLOCK : (DMA Offset: 0x2c8)  -------- 
// -------- DMA_RAWSRCTRAN : (DMA Offset: 0x2d0)  -------- 
// -------- DMA_RAWDSTTRAN : (DMA Offset: 0x2d8)  -------- 
// -------- DMA_RAWERR : (DMA Offset: 0x2e0)  -------- 
// -------- DMA_STATUSTFR : (DMA Offset: 0x2e8)  -------- 
#define AT91C_DMA_STATUS      ((unsigned int) 0x7 <<  0) // (DMA) Interrupt for each Channel
// -------- DMA_STATUSBLOCK : (DMA Offset: 0x2f0)  -------- 
// -------- DMA_STATUSSRCTRAN : (DMA Offset: 0x2f8)  -------- 
// -------- DMA_STATUSDSTTRAN : (DMA Offset: 0x300)  -------- 
// -------- DMA_STATUSERR : (DMA Offset: 0x308)  -------- 
// -------- DMA_MASKTFR : (DMA Offset: 0x310)  -------- 
#define AT91C_DMA_INT_MASK    ((unsigned int) 0x7 <<  0) // (DMA) Interrupt Mask for each Channel
#define AT91C_DMA_INT_M_WE    ((unsigned int) 0x7 <<  8) // (DMA) Interrupt Mask Write Enable for each Channel
// -------- DMA_MASKBLOCK : (DMA Offset: 0x318)  -------- 
// -------- DMA_MASKSRCTRAN : (DMA Offset: 0x320)  -------- 
// -------- DMA_MASKDSTTRAN : (DMA Offset: 0x328)  -------- 
// -------- DMA_MASKERR : (DMA Offset: 0x330)  -------- 
// -------- DMA_CLEARTFR : (DMA Offset: 0x338)  -------- 
#define AT91C_DMA_CLEAR       ((unsigned int) 0x7 <<  0) // (DMA) Interrupt Clear for each Channel
// -------- DMA_CLEARBLOCK : (DMA Offset: 0x340)  -------- 
// -------- DMA_CLEARSRCTRAN : (DMA Offset: 0x348)  -------- 
// -------- DMA_CLEARDSTTRAN : (DMA Offset: 0x350)  -------- 
// -------- DMA_CLEARERR : (DMA Offset: 0x358)  -------- 
// -------- DMA_STATUSINT : (DMA Offset: 0x360)  -------- 
#define AT91C_DMA_TFR         ((unsigned int) 0x1 <<  0) // (DMA) OR of the content of StatusTfr Register
#define AT91C_DMA_BLOCK       ((unsigned int) 0x1 <<  1) // (DMA) OR of the content of StatusBlock Register
#define AT91C_DMA_SRCT        ((unsigned int) 0x1 <<  2) // (DMA) OR of the content of StatusSrcTran Register
#define AT91C_DMA_DSTT        ((unsigned int) 0x1 <<  3) // (DMA) OR of the content of StatusDstTran Register
#define AT91C_DMA_ERR         ((unsigned int) 0x1 <<  4) // (DMA) OR of the content of StatusErr Register
// -------- DMA_REQSRCREG : (DMA Offset: 0x368)  -------- 
#define AT91C_DMA_SRC_REQ     ((unsigned int) 0x7 <<  0) // (DMA) Source Request
#define AT91C_DMA_REQ_WE      ((unsigned int) 0x7 <<  8) // (DMA) Request Write Enable
// -------- DMA_REQDSTREG : (DMA Offset: 0x370)  -------- 
#define AT91C_DMA_DST_REQ     ((unsigned int) 0x7 <<  0) // (DMA) Destination Request
// -------- DMA_SGLREQSRCREG : (DMA Offset: 0x378)  -------- 
#define AT91C_DMA_S_SG_REQ    ((unsigned int) 0x7 <<  0) // (DMA) Source Single Request
// -------- DMA_SGLREQDSTREG : (DMA Offset: 0x380)  -------- 
#define AT91C_DMA_D_SG_REQ    ((unsigned int) 0x7 <<  0) // (DMA) Destination Single Request
// -------- DMA_LSTREQSRCREG : (DMA Offset: 0x388)  -------- 
#define AT91C_DMA_LSTSRC      ((unsigned int) 0x7 <<  0) // (DMA) Source Last Transaction Request
#define AT91C_DMA_LSTSR_WE    ((unsigned int) 0x7 <<  8) // (DMA) Source Last Transaction Request Write Enable
// -------- DMA_LSTREQDSTREG : (DMA Offset: 0x390)  -------- 
#define AT91C_DMA_LSTDST      ((unsigned int) 0x7 <<  0) // (DMA) Destination Last Transaction Request
#define AT91C_DMA_LSTDS_WE    ((unsigned int) 0x7 <<  8) // (DMA) Destination Last Transaction Request Write Enable
// -------- DMA_DMACFGREG : (DMA Offset: 0x398)  -------- 
#define AT91C_DMA_DMA_EN      ((unsigned int) 0x7 <<  0) // (DMA) Controller Enable
// -------- DMA_CHENREG : (DMA Offset: 0x3a0)  -------- 
#define AT91C_DMA_CH_EN       ((unsigned int) 0x7 <<  0) // (DMA) Channel Enable
#define AT91C_DMA_CH_EN_WE    ((unsigned int) 0x7 <<  8) // (DMA) Channel Enable Write Enable
// -------- DMA_DMATESTREG : (DMA Offset: 0x3b0)  -------- 
#define AT91C_DMA_TEST_SLV_IF ((unsigned int) 0x1 <<  0) // (DMA) Test Mode for Slave Interface

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR USB Device Interface
// *****************************************************************************
typedef struct _AT91S_UDP {
	AT91_REG	 UDP_NUM; 	// Frame Number Register
	AT91_REG	 UDP_GLBSTATE; 	// Global State Register
	AT91_REG	 UDP_FADDR; 	// Function Address Register
	AT91_REG	 Reserved0[1]; 	// 
	AT91_REG	 UDP_IER; 	// Interrupt Enable Register
	AT91_REG	 UDP_IDR; 	// Interrupt Disable Register
	AT91_REG	 UDP_IMR; 	// Interrupt Mask Register
	AT91_REG	 UDP_ISR; 	// Interrupt Status Register
	AT91_REG	 UDP_ICR; 	// Interrupt Clear Register
	AT91_REG	 Reserved1[1]; 	// 
	AT91_REG	 UDP_RSTEP; 	// Reset Endpoint Register
	AT91_REG	 Reserved2[1]; 	// 
	AT91_REG	 UDP_CSR[6]; 	// Endpoint Control and Status Register
	AT91_REG	 Reserved3[2]; 	// 
	AT91_REG	 UDP_FDR[6]; 	// Endpoint FIFO Data Register
	AT91_REG	 Reserved4[3]; 	// 
	AT91_REG	 UDP_TXVC; 	// Transceiver Control Register
} AT91S_UDP, *AT91PS_UDP;

// -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- 
#define AT91C_UDP_FRM_NUM     ((unsigned int) 0x7FF <<  0) // (UDP) Frame Number as Defined in the Packet Field Formats
#define AT91C_UDP_FRM_ERR     ((unsigned int) 0x1 << 16) // (UDP) Frame Error
#define AT91C_UDP_FRM_OK      ((unsigned int) 0x1 << 17) // (UDP) Frame OK
// -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- 
#define AT91C_UDP_FADDEN      ((unsigned int) 0x1 <<  0) // (UDP) Function Address Enable
#define AT91C_UDP_CONFG       ((unsigned int) 0x1 <<  1) // (UDP) Configured
#define AT91C_UDP_ESR         ((unsigned int) 0x1 <<  2) // (UDP) Enable Send Resume
#define AT91C_UDP_RSMINPR     ((unsigned int) 0x1 <<  3) // (UDP) A Resume Has Been Sent to the Host
#define AT91C_UDP_RMWUPE      ((unsigned int) 0x1 <<  4) // (UDP) Remote Wake Up Enable
// -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- 
#define AT91C_UDP_FADD        ((unsigned int) 0xFF <<  0) // (UDP) Function Address Value
#define AT91C_UDP_FEN         ((unsigned int) 0x1 <<  8) // (UDP) Function Enable
// -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- 
#define AT91C_UDP_EPINT0      ((unsigned int) 0x1 <<  0) // (UDP) Endpoint 0 Interrupt
#define AT91C_UDP_EPINT1      ((unsigned int) 0x1 <<  1) // (UDP) Endpoint 0 Interrupt
#define AT91C_UDP_EPINT2      ((unsigned int) 0x1 <<  2) // (UDP) Endpoint 2 Interrupt
#define AT91C_UDP_EPINT3      ((unsigned int) 0x1 <<  3) // (UDP) Endpoint 3 Interrupt
#define AT91C_UDP_EPINT4      ((unsigned int) 0x1 <<  4) // (UDP) Endpoint 4 Interrupt
#define AT91C_UDP_EPINT5      ((unsigned int) 0x1 <<  5) // (UDP) Endpoint 5 Interrupt
#define AT91C_UDP_RXSUSP      ((unsigned int) 0x1 <<  8) // (UDP) USB Suspend Interrupt
#define AT91C_UDP_RXRSM       ((unsigned int) 0x1 <<  9) // (UDP) USB Resume Interrupt
#define AT91C_UDP_EXTRSM      ((unsigned int) 0x1 << 10) // (UDP) USB External Resume Interrupt
#define AT91C_UDP_SOFINT      ((unsigned int) 0x1 << 11) // (UDP) USB Start Of frame Interrupt
#define AT91C_UDP_WAKEUP      ((unsigned int) 0x1 << 13) // (UDP) USB Resume Interrupt
// -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- 
// -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- 
// -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- 
#define AT91C_UDP_ENDBUSRES   ((unsigned int) 0x1 << 12) // (UDP) USB End Of Bus Reset Interrupt
// -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- 
// -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- 
#define AT91C_UDP_EP0         ((unsigned int) 0x1 <<  0) // (UDP) Reset Endpoint 0
#define AT91C_UDP_EP1         ((unsigned int) 0x1 <<  1) // (UDP) Reset Endpoint 1
#define AT91C_UDP_EP2         ((unsigned int) 0x1 <<  2) // (UDP) Reset Endpoint 2
#define AT91C_UDP_EP3         ((unsigned int) 0x1 <<  3) // (UDP) Reset Endpoint 3
#define AT91C_UDP_EP4         ((unsigned int) 0x1 <<  4) // (UDP) Reset Endpoint 4
#define AT91C_UDP_EP5         ((unsigned int) 0x1 <<  5) // (UDP) Reset Endpoint 5
// -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- 
#define AT91C_UDP_TXCOMP      ((unsigned int) 0x1 <<  0) // (UDP) Generates an IN packet with data previously written in the DPR
#define AT91C_UDP_RX_DATA_BK0 ((unsigned int) 0x1 <<  1) // (UDP) Receive Data Bank 0
#define AT91C_UDP_RXSETUP     ((unsigned int) 0x1 <<  2) // (UDP) Sends STALL to the Host (Control endpoints)
#define AT91C_UDP_ISOERROR    ((unsigned int) 0x1 <<  3) // (UDP) Isochronous error (Isochronous endpoints)
#define AT91C_UDP_STALLSENT   ((unsigned int) 0x1 <<  3) // (UDP) Stall sent (Control, bulk, interrupt endpoints)
#define AT91C_UDP_TXPKTRDY    ((unsigned int) 0x1 <<  4) // (UDP) Transmit Packet Ready
#define AT91C_UDP_FORCESTALL  ((unsigned int) 0x1 <<  5) // (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints).
#define AT91C_UDP_RX_DATA_BK1 ((unsigned int) 0x1 <<  6) // (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes).
#define AT91C_UDP_DIR         ((unsigned int) 0x1 <<  7) // (UDP) Transfer Direction
#define AT91C_UDP_EPTYPE      ((unsigned int) 0x7 <<  8) // (UDP) Endpoint type
#define 	AT91C_UDP_EPTYPE_CTRL                 ((unsigned int) 0x0 <<  8) // (UDP) Control
#define 	AT91C_UDP_EPTYPE_ISO_OUT              ((unsigned int) 0x1 <<  8) // (UDP) Isochronous OUT
#define 	AT91C_UDP_EPTYPE_BULK_OUT             ((unsigned int) 0x2 <<  8) // (UDP) Bulk OUT
#define 	AT91C_UDP_EPTYPE_INT_OUT              ((unsigned int) 0x3 <<  8) // (UDP) Interrupt OUT
#define 	AT91C_UDP_EPTYPE_ISO_IN               ((unsigned int) 0x5 <<  8) // (UDP) Isochronous IN
#define 	AT91C_UDP_EPTYPE_BULK_IN              ((unsigned int) 0x6 <<  8) // (UDP) Bulk IN
#define 	AT91C_UDP_EPTYPE_INT_IN               ((unsigned int) 0x7 <<  8) // (UDP) Interrupt IN
#define AT91C_UDP_DTGLE       ((unsigned int) 0x1 << 11) // (UDP) Data Toggle
#define AT91C_UDP_EPEDS       ((unsigned int) 0x1 << 15) // (UDP) Endpoint Enable Disable
#define AT91C_UDP_RXBYTECNT   ((unsigned int) 0x7FF << 16) // (UDP) Number Of Bytes Available in the FIFO
// -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- 
#define AT91C_UDP_TXVDIS      ((unsigned int) 0x1 <<  8) // (UDP) 
#define AT91C_UDP_PUON        ((unsigned int) 0x1 <<  9) // (UDP) Pull-up ON

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR USB Host Interface
// *****************************************************************************
typedef struct _AT91S_UHP {
	AT91_REG	 UHP_HcRevision; 	// Revision
	AT91_REG	 UHP_HcControl; 	// Operating modes for the Host Controller
	AT91_REG	 UHP_HcCommandStatus; 	// Command & status Register
	AT91_REG	 UHP_HcInterruptStatus; 	// Interrupt Status Register
	AT91_REG	 UHP_HcInterruptEnable; 	// Interrupt Enable Register
	AT91_REG	 UHP_HcInterruptDisable; 	// Interrupt Disable Register
	AT91_REG	 UHP_HcHCCA; 	// Pointer to the Host Controller Communication Area
	AT91_REG	 UHP_HcPeriodCurrentED; 	// Current Isochronous or Interrupt Endpoint Descriptor
	AT91_REG	 UHP_HcControlHeadED; 	// First Endpoint Descriptor of the Control list
	AT91_REG	 UHP_HcControlCurrentED; 	// Endpoint Control and Status Register
	AT91_REG	 UHP_HcBulkHeadED; 	// First endpoint register of the Bulk list
	AT91_REG	 UHP_HcBulkCurrentED; 	// Current endpoint of the Bulk list
	AT91_REG	 UHP_HcBulkDoneHead; 	// Last completed transfer descriptor
	AT91_REG	 UHP_HcFmInterval; 	// Bit time between 2 consecutive SOFs
	AT91_REG	 UHP_HcFmRemaining; 	// Bit time remaining in the current Frame
	AT91_REG	 UHP_HcFmNumber; 	// Frame number
	AT91_REG	 UHP_HcPeriodicStart; 	// Periodic Start
	AT91_REG	 UHP_HcLSThreshold; 	// LS Threshold
	AT91_REG	 UHP_HcRhDescriptorA; 	// Root Hub characteristics A
	AT91_REG	 UHP_HcRhDescriptorB; 	// Root Hub characteristics B
	AT91_REG	 UHP_HcRhStatus; 	// Root Hub Status register
	AT91_REG	 UHP_HcRhPortStatus[2]; 	// Root Hub Port Status Register
} AT91S_UHP, *AT91PS_UHP;


// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Trickbox (external) / SIMULATION ONLY
// *****************************************************************************
typedef struct _AT91S_TBOX {
	AT91_REG	 TBOX_SHMCTRL; 	// SHM Probe Control: 0-> shm probe stopped, 1: shm probe started
	AT91_REG	 Reserved0[515]; 	// 
	AT91_REG	 TBOX_DMAEXTREQ; 	// DMA External request lines 3 to 0
	AT91_REG	 Reserved1[59]; 	// 
	AT91_REG	 TBOX_PIOAPUN; 	// Spy on PIO PUN inputs
	AT91_REG	 TBOX_PIOBPUN; 	// Spy on PIO PUN inputs
	AT91_REG	 TBOX_PIOCPUN; 	// Spy on PIO PUN inputs
	AT91_REG	 TBOX_PIODPUN; 	// Spy on PIO PUN inputs
	AT91_REG	 TBOX_PIOEPUN; 	// Spy on PIO PUN inputs
	AT91_REG	 TBOX_PIOAENABLEFORCE; 	// If each bit is 1, the corresponding bit of PIOA is controlled by TBOX_PIOAFORCEVALUE
	AT91_REG	 TBOX_PIOAFORCEVALUE; 	// Value to force on PIOA when bits TBOX_PIOAENABLEFORCE are 1
	AT91_REG	 TBOX_PIOBENABLEFORCE; 	// If each bit is 1, the corresponding bit of PIOB is controlled by TBOX_PIOBFORCEVALUE
	AT91_REG	 TBOX_PIOBFORCEVALUE; 	// Value to force on PIOA when bits TBOX_PIOBENABLEFORCE are 1
	AT91_REG	 TBOX_PIOCENABLEFORCE; 	// If each bit is 1, the corresponding bit of PIOC is controlled by TBOX_PIOCFORCEVALUE
	AT91_REG	 TBOX_PIOCFORCEVALUE; 	// Value to force on PIOA when bits TBOX_PIOCENABLEFORCE are 1
	AT91_REG	 TBOX_PIODENABLEFORCE; 	// If each bit is 1, the corresponding bit of PIOD is controlled by TBOX_PIODFORCEVALUE
	AT91_REG	 TBOX_PIODFORCEVALUE; 	// Value to force on PIOA when bits TBOX_PIODENABLEFORCE are 1
	AT91_REG	 TBOX_PIOEENABLEFORCE; 	// If each bit is 1, the corresponding bit of PIOE is controlled by TBOX_PIOEFORCEVALUE
	AT91_REG	 TBOX_PIOEFORCEVALUE; 	// Value to force on PIOA when bits TBOX_PIOEENABLEFORCE are 1
	AT91_REG	 TBOX_PIOA; 	// Value Of PIOA
	AT91_REG	 TBOX_PIOB; 	// Value Of PIOB
	AT91_REG	 TBOX_PIOC; 	// Value Of PIOC
	AT91_REG	 TBOX_PIOD; 	// Value Of PIOD
	AT91_REG	 TBOX_PIOE; 	// Value Of PIOE
	AT91_REG	 Reserved2[44]; 	// 
	AT91_REG	 TBOX_AC97START; 	// Start of AC97 test: swith PIO mux to connect PIOs to audio codec model.
	AT91_REG	 TBOX_PWMSTART; 	// Start of PWM test: Start to count edges on PWM IOs
	AT91_REG	 TBOX_PWM1; 	// PWM1[4:0]=nb pulses on pb7, PWM1[9:5]=nb pulses on pc28, PWM1[20:16]=nb pulses on pb8, PWM1[25:21]=nb pulses on pc3
	AT91_REG	 TBOX_PWM2; 	// PWM2[3:0]=nb pulses on pb27, PWM2[7:4]=nb pulses on pc29, PWM2[19:16]=nb pulses on pb29, PWM2[23:20]=nb pulses on pe10
	AT91_REG	 TBOX_MAC; 	// MAC testbench : bit 0 = rxtrig, bit 1 = clkofftester, bit 2 = err_sig_loops
	AT91_REG	 TBOX_USBDEV; 	// USB device testbench : bit 0 = flag0, bit 1 = flag1
	AT91_REG	 TBOX_KBD; 	// Keyboard testbench : bit 0 = keypressed; bits[7:6] = key column; bits[5:4] = key row;
	AT91_REG	 TBOX_STOPAPBSPY; 	// When 1, no more APB SPY messages
	AT91_REG	 Reserved3[56]; 	// 
	AT91_REG	 TBOX_GPSSYNCHRO; 	// GPS synchronization (Stimulus)
	AT91_REG	 TBOX_GPSRAND; 	// GPS random data for correlator (Stimulus - Internal Node)
	AT91_REG	 TBOX_GPSACQSTATUS; 	// GPS acquisition status (Probe - Internal Node)
	AT91_REG	 TBOX_GPSACQDATA; 	// GPS acquisition data (Probe - Internal Node)
	AT91_REG	 Reserved4[36]; 	// 
	AT91_REG	 TBOX_GPSSIGFILE; 	// GPS RFIN/DRFIN driven from files/Samples_GPS.data
	AT91_REG	 TBOX_GPSSIGIA; 	// GPS DRFIN[1:0] aka SIGI_A (Stimulus)
	AT91_REG	 TBOX_GPSSIGQA; 	// GPS DRFIN[3:2] aka SIGQ_A (Stimulus)
	AT91_REG	 Reserved5[1]; 	// 
	AT91_REG	 TBOX_GPSSIGIB; 	// GPS DRFIN[5:4] aka SIGI_B (Stimulus)
	AT91_REG	 TBOX_GPSSIGQB; 	// GPS DRFIN[7:6] aka SIGQ_B (Stimulus)
	AT91_REG	 Reserved6[2]; 	// 
	AT91_REG	 TBOX_GPSDUMPRES; 	// GPS Dump results and errors
} AT91S_TBOX, *AT91PS_TBOX;

// -------- TBOX_DMAEXTREQ : (TBOX Offset: 0x810)  -------- 
#define AT91C_TBOX_DMAEXTREQ0 ((unsigned int) 0x1 <<  0) // (TBOX) DMA external request 0
#define AT91C_TBOX_DMAEXTREQ1 ((unsigned int) 0x1 <<  1) // (TBOX) DMA external request 1
#define AT91C_TBOX_DMAEXTREQ2 ((unsigned int) 0x1 <<  2) // (TBOX) DMA external request 2
#define AT91C_TBOX_DMAEXTREQ3 ((unsigned int) 0x1 <<  3) // (TBOX) DMA external request 3

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Error Correction Code controller
// *****************************************************************************
typedef struct _AT91S_ECC {
	AT91_REG	 ECC_CR; 	//  ECC reset register
	AT91_REG	 ECC_MR; 	//  ECC Page size register
	AT91_REG	 ECC_SR; 	//  ECC Status register
	AT91_REG	 ECC_PR; 	//  ECC Parity register
	AT91_REG	 ECC_NPR; 	//  ECC Parity N register
	AT91_REG	 Reserved0[58]; 	// 
	AT91_REG	 ECC_VR; 	//  ECC Version register
} AT91S_ECC, *AT91PS_ECC;

// -------- ECC_CR : (ECC Offset: 0x0) ECC reset register -------- 
#define AT91C_ECC_RST         ((unsigned int) 0x1 <<  0) // (ECC) ECC reset parity
// -------- ECC_MR : (ECC Offset: 0x4) ECC page size register -------- 
#define AT91C_ECC_PAGE_SIZE   ((unsigned int) 0x3 <<  0) // (ECC) Nand Flash page size
// -------- ECC_SR : (ECC Offset: 0x8) ECC status register -------- 
#define AT91C_ECC_RECERR      ((unsigned int) 0x1 <<  0) // (ECC) ECC error
#define AT91C_ECC_ECCERR      ((unsigned int) 0x1 <<  1) // (ECC) ECC single error
#define AT91C_ECC_MULERR      ((unsigned int) 0x1 <<  2) // (ECC) ECC_MULERR
// -------- ECC_PR : (ECC Offset: 0xc) ECC parity register -------- 
#define AT91C_ECC_BITADDR     ((unsigned int) 0xF <<  0) // (ECC) Bit address error
#define AT91C_ECC_WORDADDR    ((unsigned int) 0xFFF <<  4) // (ECC) address of the failing bit
// -------- ECC_NPR : (ECC Offset: 0x10) ECC N parity register -------- 
#define AT91C_ECC_NPARITY     ((unsigned int) 0xFFFF <<  0) // (ECC) ECC parity N 
// -------- ECC_VR : (ECC Offset: 0xfc) ECC version register -------- 
#define AT91C_ECC_VR          ((unsigned int) 0xF <<  0) // (ECC) ECC version register

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Image Sensor Interface
// *****************************************************************************
typedef struct _AT91S_ISI {
	AT91_REG	 ISI_CR1; 	// Control Register 1
	AT91_REG	 ISI_CR2; 	// Control Register 2
	AT91_REG	 ISI_SR; 	// Status Register
	AT91_REG	 ISI_IER; 	// Interrupt Enable Register
	AT91_REG	 ISI_IDR; 	// Interrupt Disable Register
	AT91_REG	 ISI_IMR; 	// Interrupt Mask Register
	AT91_REG	 Reserved0[2]; 	// 
	AT91_REG	 ISI_PSIZE; 	// Preview Size Register
	AT91_REG	 ISI_PDECF; 	// Preview Decimation Factor Register
	AT91_REG	 ISI_PFBD; 	// Preview Frame Buffer Address Register
	AT91_REG	 ISI_CDBA; 	// Codec Dma Address Register
	AT91_REG	 ISI_Y2RSET0; 	// Color Space Conversion Register
	AT91_REG	 ISI_Y2RSET1; 	// Color Space Conversion Register
	AT91_REG	 ISI_R2YSET0; 	// Color Space Conversion Register
	AT91_REG	 ISI_R2YSET1; 	// Color Space Conversion Register
	AT91_REG	 ISI_R2YSET2; 	// Color Space Conversion Register
} AT91S_ISI, *AT91PS_ISI;

// -------- ISI_CR1 : (ISI Offset: 0x0) ISI Control Register 1 -------- 
#define AT91C_ISI_RST         ((unsigned int) 0x1 <<  0) // (ISI) Image sensor interface reset
#define AT91C_ISI_DISABLE     ((unsigned int) 0x1 <<  1) // (ISI) image sensor disable.
#define AT91C_ISI_HSYNC_POL   ((unsigned int) 0x1 <<  2) // (ISI) Horizontal synchronisation polarity
#define AT91C_ISI_PIXCLK_POL  ((unsigned int) 0x1 <<  4) // (ISI) Pixel Clock Polarity
#define AT91C_ISI_EMB_SYNC    ((unsigned int) 0x1 <<  6) // (ISI) Embedded synchronisation
#define AT91C_ISI_CRC_SYNC    ((unsigned int) 0x1 <<  7) // (ISI) CRC correction
#define AT91C_ISI_FULL        ((unsigned int) 0x1 << 12) // (ISI) Full mode is allowed
#define AT91C_ISI_THMASK      ((unsigned int) 0x3 << 13) // (ISI) DMA Burst Mask
#define 	AT91C_ISI_THMASK_4_8_16_BURST         ((unsigned int) 0x0 << 13) // (ISI) 4,8 and 16 AHB burst are allowed
#define 	AT91C_ISI_THMASK_8_16_BURST           ((unsigned int) 0x1 << 13) // (ISI) 8 and 16 AHB burst are allowed
#define 	AT91C_ISI_THMASK_16_BURST             ((unsigned int) 0x2 << 13) // (ISI) Only 16 AHB burst are allowed
#define AT91C_ISI_CODEC_ON    ((unsigned int) 0x1 << 15) // (ISI) Enable the codec path
#define AT91C_ISI_SLD         ((unsigned int) 0xFF << 16) // (ISI) Start of Line Delay
#define AT91C_ISI_SFD         ((unsigned int) 0xFF << 24) // (ISI) Start of frame Delay
// -------- ISI_CR2 : (ISI Offset: 0x4) ISI Control Register 2 -------- 
#define AT91C_ISI_IM_VSIZE    ((unsigned int) 0x7FF <<  0) // (ISI) Vertical size of the Image sensor [0..2047]
#define AT91C_ISI_GS_MODE     ((unsigned int) 0x1 << 11) // (ISI) Grayscale Memory Mode
#define AT91C_ISI_RGB_MODE    ((unsigned int) 0x3 << 12) // (ISI) RGB mode
#define 	AT91C_ISI_RGB_MODE_RGB_888              ((unsigned int) 0x0 << 12) // (ISI) RGB 8:8:8 24 bits
#define 	AT91C_ISI_RGB_MODE_RGB_565              ((unsigned int) 0x1 << 12) // (ISI) RGB 5:6:5 16 bits
#define 	AT91C_ISI_RGB_MODE_RGB_555              ((unsigned int) 0x2 << 12) // (ISI) RGB 5:5:5 16 bits
#define AT91C_ISI_GRAYSCALE   ((unsigned int) 0x1 << 13) // (ISI) Grayscale Mode
#define AT91C_ISI_RGB_SWAP    ((unsigned int) 0x1 << 14) // (ISI) RGB Swap
#define AT91C_ISI_COL_SPACE   ((unsigned int) 0x1 << 15) // (ISI) Color space for the image data
#define AT91C_ISI_IM_HSIZE    ((unsigned int) 0x7FF << 16) // (ISI) Horizontal size of the Image sensor [0..2047]
#define 	AT91C_ISI_RGB_MODE_YCC_DEF              ((unsigned int) 0x0 << 28) // (ISI) Cb(i) Y(i) Cr(i) Y(i+1)
#define 	AT91C_ISI_RGB_MODE_YCC_MOD1             ((unsigned int) 0x1 << 28) // (ISI) Cr(i) Y(i) Cb(i) Y(i+1)
#define 	AT91C_ISI_RGB_MODE_YCC_MOD2             ((unsigned int) 0x2 << 28) // (ISI) Y(i) Cb(i) Y(i+1) Cr(i)
#define 	AT91C_ISI_RGB_MODE_YCC_MOD3             ((unsigned int) 0x3 << 28) // (ISI) Y(i) Cr(i) Y(i+1) Cb(i)
#define AT91C_ISI_RGB_CFG     ((unsigned int) 0x3 << 30) // (ISI) RGB configuration
#define 	AT91C_ISI_RGB_CFG_RGB_DEF              ((unsigned int) 0x0 << 30) // (ISI) R/G(MSB)  G(LSB)/B  R/G(MSB)  G(LSB)/B
#define 	AT91C_ISI_RGB_CFG_RGB_MOD1             ((unsigned int) 0x1 << 30) // (ISI) B/G(MSB)  G(LSB)/R  B/G(MSB)  G(LSB)/R
#define 	AT91C_ISI_RGB_CFG_RGB_MOD2             ((unsigned int) 0x2 << 30) // (ISI) G(LSB)/R  B/G(MSB)  G(LSB)/R  B/G(MSB)
#define 	AT91C_ISI_RGB_CFG_RGB_MOD3             ((unsigned int) 0x3 << 30) // (ISI) G(LSB)/B  R/G(MSB)  G(LSB)/B  R/G(MSB)
// -------- ISI_SR : (ISI Offset: 0x8) ISI Status Register -------- 
#define AT91C_ISI_SOF         ((unsigned int) 0x1 <<  0) // (ISI) Start of Frame
#define AT91C_ISI_DIS         ((unsigned int) 0x1 <<  1) // (ISI) Image Sensor Interface disable
#define AT91C_ISI_SOFTRST     ((unsigned int) 0x1 <<  2) // (ISI) Software Reset
#define AT91C_ISI_CRC_ERR     ((unsigned int) 0x1 <<  4) // (ISI) CRC synchronisation error
#define AT91C_ISI_FO_C_OVF    ((unsigned int) 0x1 <<  5) // (ISI) Fifo Codec Overflow 
#define AT91C_ISI_FO_P_OVF    ((unsigned int) 0x1 <<  6) // (ISI) Fifo Preview Overflow 
#define AT91C_ISI_FO_P_EMP    ((unsigned int) 0x1 <<  7) // (ISI) Fifo Preview Empty
#define AT91C_ISI_FO_C_EMP    ((unsigned int) 0x1 <<  8) // (ISI) Fifo Codec Empty
#define AT91C_ISI_FR_OVR      ((unsigned int) 0x1 <<  9) // (ISI) Frame rate overun
// -------- ISI_IER : (ISI Offset: 0xc) ISI Interrupt Enable Register -------- 
// -------- ISI_IDR : (ISI Offset: 0x10) ISI Interrupt Disable Register -------- 
// -------- ISI_IMR : (ISI Offset: 0x14) ISI Interrupt Mask Register -------- 
// -------- ISI_PSIZE : (ISI Offset: 0x20) ISI Preview Register -------- 
#define AT91C_ISI_PREV_VSIZE  ((unsigned int) 0x3FF <<  0) // (ISI) Vertical size for the preview path
#define AT91C_ISI_PREV_HSIZE  ((unsigned int) 0x3FF << 16) // (ISI) Horizontal size for the preview path
// -------- ISI_Y2R_SET0 : (ISI Offset: 0x30) Color Space Conversion YCrCb to RGB Register -------- 
#define AT91C_ISI_Y2R_C0      ((unsigned int) 0xFF <<  0) // (ISI) Color Space Conversion Matrix Coefficient C0
#define AT91C_ISI_Y2R_C1      ((unsigned int) 0xFF <<  8) // (ISI) Color Space Conversion Matrix Coefficient C1
#define AT91C_ISI_Y2R_C2      ((unsigned int) 0xFF << 16) // (ISI) Color Space Conversion Matrix Coefficient C2
#define AT91C_ISI_Y2R_C3      ((unsigned int) 0xFF << 24) // (ISI) Color Space Conversion Matrix Coefficient C3
// -------- ISI_Y2R_SET1 : (ISI Offset: 0x34) ISI Color Space Conversion YCrCb to RGB set 1 Register -------- 
#define AT91C_ISI_Y2R_C4      ((unsigned int) 0x1FF <<  0) // (ISI) Color Space Conversion Matrix Coefficient C4
#define AT91C_ISI_Y2R_YOFF    ((unsigned int) 0xFF << 12) // (ISI) Color Space Conversion Luninance default offset
#define AT91C_ISI_Y2R_CROFF   ((unsigned int) 0xFF << 13) // (ISI) Color Space Conversion Red Chrominance default offset
#define AT91C_ISI_Y2R_CBFF    ((unsigned int) 0xFF << 14) // (ISI) Color Space Conversion Luninance default offset
// -------- ISI_R2Y_SET0 : (ISI Offset: 0x38) Color Space Conversion RGB to YCrCb set 0 register -------- 
#define AT91C_ISI_R2Y_C0      ((unsigned int) 0x7F <<  0) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C0
#define AT91C_ISI_R2Y_C1      ((unsigned int) 0x7F <<  1) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C1
#define AT91C_ISI_R2Y_C2      ((unsigned int) 0x7F <<  3) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C2
#define AT91C_ISI_R2Y_ROFF    ((unsigned int) 0x1 <<  4) // (ISI) Color Space Conversion Red component offset
// -------- ISI_R2Y_SET1 : (ISI Offset: 0x3c) Color Space Conversion RGB to YCrCb set 1 register -------- 
#define AT91C_ISI_R2Y_C3      ((unsigned int) 0x7F <<  0) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C3
#define AT91C_ISI_R2Y_C4      ((unsigned int) 0x7F <<  1) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C4
#define AT91C_ISI_R2Y_C5      ((unsigned int) 0x7F <<  3) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C5
#define AT91C_ISI_R2Y_GOFF    ((unsigned int) 0x1 <<  4) // (ISI) Color Space Conversion Green component offset
// -------- ISI_R2Y_SET2 : (ISI Offset: 0x40) Color Space Conversion RGB to YCrCb set 2 register -------- 
#define AT91C_ISI_R2Y_C6      ((unsigned int) 0x7F <<  0) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C6
#define AT91C_ISI_R2Y_C7      ((unsigned int) 0x7F <<  1) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C7
#define AT91C_ISI_R2Y_C8      ((unsigned int) 0x7F <<  3) // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C8
#define AT91C_ISI_R2Y_BOFF    ((unsigned int) 0x1 <<  4) // (ISI) Color Space Conversion Blue component offset

// *****************************************************************************
//               REGISTER ADDRESS DEFINITION FOR AT91SAM9263
// *****************************************************************************
// ========== Register definition for SYS peripheral ========== 
#define AT91C_SYS_ECC1  ((AT91_REG *) 	0xFFFFE600) // (SYS) ECC 0
#define AT91C_SYS_ECC0  ((AT91_REG *) 	0xFFFFE000) // (SYS) ECC 0
#define AT91C_SYS_GPBR  ((AT91_REG *) 	0xFFFFFD60) // (SYS) General Purpose Register
// ========== Register definition for EBI0 peripheral ========== 
#define AT91C_EBI0_DUMMY ((AT91_REG *) 	0xFFFFE200) // (EBI0) Dummy register - Do not use
// ========== Register definition for SDRAMC0 peripheral ========== 
#define AT91C_SDRAMC0_MDR ((AT91_REG *) 	0xFFFFE224) // (SDRAMC0) SDRAM Memory Device Register
#define AT91C_SDRAMC0_IDR ((AT91_REG *) 	0xFFFFE218) // (SDRAMC0) SDRAM Controller Interrupt Disable Register
#define AT91C_SDRAMC0_IMR ((AT91_REG *) 	0xFFFFE21C) // (SDRAMC0) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC0_ISR ((AT91_REG *) 	0xFFFFE220) // (SDRAMC0) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC0_HSR ((AT91_REG *) 	0xFFFFE20C) // (SDRAMC0) SDRAM Controller High Speed Register
#define AT91C_SDRAMC0_TR ((AT91_REG *) 	0xFFFFE204) // (SDRAMC0) SDRAM Controller Refresh Timer Register
#define AT91C_SDRAMC0_CR ((AT91_REG *) 	0xFFFFE208) // (SDRAMC0) SDRAM Controller Configuration Register
#define AT91C_SDRAMC0_MR ((AT91_REG *) 	0xFFFFE200) // (SDRAMC0) SDRAM Controller Mode Register
#define AT91C_SDRAMC0_LPR ((AT91_REG *) 	0xFFFFE210) // (SDRAMC0) SDRAM Controller Low Power Register
#define AT91C_SDRAMC0_IER ((AT91_REG *) 	0xFFFFE214) // (SDRAMC0) SDRAM Controller Interrupt Enable Register
// ========== Register definition for SMC0 peripheral ========== 
#define AT91C_SMC0_CYCLE6 ((AT91_REG *) 	0xFFFFE468) // (SMC0)  Cycle Register for CS 6
#define AT91C_SMC0_SETUP6 ((AT91_REG *) 	0xFFFFE460) // (SMC0)  Setup Register for CS 6
#define AT91C_SMC0_PULSE3 ((AT91_REG *) 	0xFFFFE434) // (SMC0)  Pulse Register for CS 3
#define AT91C_SMC0_CYCLE1 ((AT91_REG *) 	0xFFFFE418) // (SMC0)  Cycle Register for CS 1
#define AT91C_SMC0_SETUP5 ((AT91_REG *) 	0xFFFFE450) // (SMC0)  Setup Register for CS 5
#define AT91C_SMC0_CYCLE7 ((AT91_REG *) 	0xFFFFE478) // (SMC0)  Cycle Register for CS 7
#define AT91C_SMC0_PULSE0 ((AT91_REG *) 	0xFFFFE404) // (SMC0)  Pulse Register for CS 0
#define AT91C_SMC0_CYCLE5 ((AT91_REG *) 	0xFFFFE458) // (SMC0)  Cycle Register for CS 5
#define AT91C_SMC0_CTRL0 ((AT91_REG *) 	0xFFFFE40C) // (SMC0)  Control Register for CS 0
#define AT91C_SMC0_SETUP7 ((AT91_REG *) 	0xFFFFE470) // (SMC0)  Setup Register for CS 7
#define AT91C_SMC0_CTRL4 ((AT91_REG *) 	0xFFFFE44C) // (SMC0)  Control Register for CS 4
#define AT91C_SMC0_CTRL1 ((AT91_REG *) 	0xFFFFE41C) // (SMC0)  Control Register for CS 1
#define AT91C_SMC0_CYCLE2 ((AT91_REG *) 	0xFFFFE428) // (SMC0)  Cycle Register for CS 2
#define AT91C_SMC0_PULSE7 ((AT91_REG *) 	0xFFFFE474) // (SMC0)  Pulse Register for CS 7
#define AT91C_SMC0_PULSE6 ((AT91_REG *) 	0xFFFFE464) // (SMC0)  Pulse Register for CS 6
#define AT91C_SMC0_CYCLE4 ((AT91_REG *) 	0xFFFFE448) // (SMC0)  Cycle Register for CS 4
#define AT91C_SMC0_CYCLE0 ((AT91_REG *) 	0xFFFFE408) // (SMC0)  Cycle Register for CS 0
#define AT91C_SMC0_CTRL6 ((AT91_REG *) 	0xFFFFE46C) // (SMC0)  Control Register for CS 6
#define AT91C_SMC0_CTRL5 ((AT91_REG *) 	0xFFFFE45C) // (SMC0)  Control Register for CS 5
#define AT91C_SMC0_SETUP0 ((AT91_REG *) 	0xFFFFE400) // (SMC0)  Setup Register for CS 0
#define AT91C_SMC0_SETUP4 ((AT91_REG *) 	0xFFFFE440) // (SMC0)  Setup Register for CS 4
#define AT91C_SMC0_PULSE1 ((AT91_REG *) 	0xFFFFE414) // (SMC0)  Pulse Register for CS 1
#define AT91C_SMC0_CTRL2 ((AT91_REG *) 	0xFFFFE42C) // (SMC0)  Control Register for CS 2
#define AT91C_SMC0_SETUP2 ((AT91_REG *) 	0xFFFFE420) // (SMC0)  Setup Register for CS 2
#define AT91C_SMC0_CTRL3 ((AT91_REG *) 	0xFFFFE43C) // (SMC0)  Control Register for CS 3
#define AT91C_SMC0_SETUP3 ((AT91_REG *) 	0xFFFFE430) // (SMC0)  Setup Register for CS 3
#define AT91C_SMC0_CTRL7 ((AT91_REG *) 	0xFFFFE47C) // (SMC0)  Control Register for CS 7
#define AT91C_SMC0_PULSE5 ((AT91_REG *) 	0xFFFFE454) // (SMC0)  Pulse Register for CS 5
#define AT91C_SMC0_PULSE4 ((AT91_REG *) 	0xFFFFE444) // (SMC0)  Pulse Register for CS 4
#define AT91C_SMC0_PULSE2 ((AT91_REG *) 	0xFFFFE424) // (SMC0)  Pulse Register for CS 2
#define AT91C_SMC0_CYCLE3 ((AT91_REG *) 	0xFFFFE438) // (SMC0)  Cycle Register for CS 3
#define AT91C_SMC0_SETUP1 ((AT91_REG *) 	0xFFFFE410) // (SMC0)  Setup Register for CS 1
// ========== Register definition for EBI1 peripheral ========== 
#define AT91C_EBI1_DUMMY ((AT91_REG *) 	0xFFFFE800) // (EBI1) Dummy register - Do not use
// ========== Register definition for SDRAMC1 peripheral ========== 
#define AT91C_SDRAMC1_IMR ((AT91_REG *) 	0xFFFFE81C) // (SDRAMC1) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC1_LPR ((AT91_REG *) 	0xFFFFE810) // (SDRAMC1) SDRAM Controller Low Power Register
#define AT91C_SDRAMC1_CR ((AT91_REG *) 	0xFFFFE808) // (SDRAMC1) SDRAM Controller Configuration Register
#define AT91C_SDRAMC1_HSR ((AT91_REG *) 	0xFFFFE80C) // (SDRAMC1) SDRAM Controller High Speed Register
#define AT91C_SDRAMC1_MDR ((AT91_REG *) 	0xFFFFE824) // (SDRAMC1) SDRAM Memory Device Register
#define AT91C_SDRAMC1_MR ((AT91_REG *) 	0xFFFFE800) // (SDRAMC1) SDRAM Controller Mode Register
#define AT91C_SDRAMC1_ISR ((AT91_REG *) 	0xFFFFE820) // (SDRAMC1) SDRAM Controller Interrupt Mask Register
#define AT91C_SDRAMC1_IDR ((AT91_REG *) 	0xFFFFE818) // (SDRAMC1) SDRAM Controller Interrupt Disable Register
#define AT91C_SDRAMC1_IER ((AT91_REG *) 	0xFFFFE814) // (SDRAMC1) SDRAM Controller Interrupt Enable Register
#define AT91C_SDRAMC1_TR ((AT91_REG *) 	0xFFFFE804) // (SDRAMC1) SDRAM Controller Refresh Timer Register
// ========== Register definition for SMC1 peripheral ========== 
#define AT91C_SMC1_PULSE4 ((AT91_REG *) 	0xFFFFEA44) // (SMC1)  Pulse Register for CS 4
#define AT91C_SMC1_SETUP2 ((AT91_REG *) 	0xFFFFEA20) // (SMC1)  Setup Register for CS 2
#define AT91C_SMC1_CYCLE0 ((AT91_REG *) 	0xFFFFEA08) // (SMC1)  Cycle Register for CS 0
#define AT91C_SMC1_SETUP7 ((AT91_REG *) 	0xFFFFEA70) // (SMC1)  Setup Register for CS 7
#define AT91C_SMC1_PULSE7 ((AT91_REG *) 	0xFFFFEA74) // (SMC1)  Pulse Register for CS 7
#define AT91C_SMC1_CTRL0 ((AT91_REG *) 	0xFFFFEA0C) // (SMC1)  Control Register for CS 0
#define AT91C_SMC1_SETUP3 ((AT91_REG *) 	0xFFFFEA30) // (SMC1)  Setup Register for CS 3
#define AT91C_SMC1_SETUP4 ((AT91_REG *) 	0xFFFFEA40) // (SMC1)  Setup Register for CS 4
#define AT91C_SMC1_CYCLE6 ((AT91_REG *) 	0xFFFFEA68) // (SMC1)  Cycle Register for CS 6
#define AT91C_SMC1_CTRL1 ((AT91_REG *) 	0xFFFFEA1C) // (SMC1)  Control Register for CS 1
#define AT91C_SMC1_CYCLE3 ((AT91_REG *) 	0xFFFFEA38) // (SMC1)  Cycle Register for CS 3
#define AT91C_SMC1_CTRL5 ((AT91_REG *) 	0xFFFFEA5C) // (SMC1)  Control Register for CS 5
#define AT91C_SMC1_CTRL3 ((AT91_REG *) 	0xFFFFEA3C) // (SMC1)  Control Register for CS 3
#define AT91C_SMC1_CYCLE4 ((AT91_REG *) 	0xFFFFEA48) // (SMC1)  Cycle Register for CS 4
#define AT91C_SMC1_SETUP6 ((AT91_REG *) 	0xFFFFEA60) // (SMC1)  Setup Register for CS 6
#define AT91C_SMC1_PULSE3 ((AT91_REG *) 	0xFFFFEA34) // (SMC1)  Pulse Register for CS 3
#define AT91C_SMC1_CTRL7 ((AT91_REG *) 	0xFFFFEA7C) // (SMC1)  Control Register for CS 7
#define AT91C_SMC1_SETUP1 ((AT91_REG *) 	0xFFFFEA10) // (SMC1)  Setup Register for CS 1
#define AT91C_SMC1_PULSE5 ((AT91_REG *) 	0xFFFFEA54) // (SMC1)  Pulse Register for CS 5
#define AT91C_SMC1_PULSE0 ((AT91_REG *) 	0xFFFFEA04) // (SMC1)  Pulse Register for CS 0
#define AT91C_SMC1_CYCLE5 ((AT91_REG *) 	0xFFFFEA58) // (SMC1)  Cycle Register for CS 5
#define AT91C_SMC1_PULSE6 ((AT91_REG *) 	0xFFFFEA64) // (SMC1)  Pulse Register for CS 6
#define AT91C_SMC1_SETUP5 ((AT91_REG *) 	0xFFFFEA50) // (SMC1)  Setup Register for CS 5
#define AT91C_SMC1_CTRL6 ((AT91_REG *) 	0xFFFFEA6C) // (SMC1)  Control Register for CS 6
#define AT91C_SMC1_CTRL2 ((AT91_REG *) 	0xFFFFEA2C) // (SMC1)  Control Register for CS 2
#define AT91C_SMC1_SETUP0 ((AT91_REG *) 	0xFFFFEA00) // (SMC1)  Setup Register for CS 0
#define AT91C_SMC1_CYCLE7 ((AT91_REG *) 	0xFFFFEA78) // (SMC1)  Cycle Register for CS 7
#define AT91C_SMC1_CYCLE1 ((AT91_REG *) 	0xFFFFEA18) // (SMC1)  Cycle Register for CS 1
#define AT91C_SMC1_PULSE2 ((AT91_REG *) 	0xFFFFEA24) // (SMC1)  Pulse Register for CS 2
#define AT91C_SMC1_PULSE1 ((AT91_REG *) 	0xFFFFEA14) // (SMC1)  Pulse Register for CS 1
#define AT91C_SMC1_CYCLE2 ((AT91_REG *) 	0xFFFFEA28) // (SMC1)  Cycle Register for CS 2
#define AT91C_SMC1_CTRL4 ((AT91_REG *) 	0xFFFFEA4C) // (SMC1)  Control Register for CS 4
// ========== Register definition for MATRIX peripheral ========== 
#define AT91C_MATRIX_MCFG7 ((AT91_REG *) 	0xFFFFEC1C) // (MATRIX)  Master Configuration Register 7 
#define AT91C_MATRIX_MRCR ((AT91_REG *) 	0xFFFFED00) // (MATRIX)  Master Remp Control Register 
#define AT91C_MATRIX_PRBS5 ((AT91_REG *) 	0xFFFFECAC) // (MATRIX)  PRBS5
#define AT91C_MATRIX_SCFG6 ((AT91_REG *) 	0xFFFFEC58) // (MATRIX)  Slave Configuration Register 6
#define AT91C_MATRIX_MCFG3 ((AT91_REG *) 	0xFFFFEC0C) // (MATRIX)  Master Configuration Register 3 
#define AT91C_MATRIX_SCFG5 ((AT91_REG *) 	0xFFFFEC54) // (MATRIX)  Slave Configuration Register 5
#define AT91C_MATRIX_MCFG1 ((AT91_REG *) 	0xFFFFEC04) // (MATRIX)  Master Configuration Register 1 
#define AT91C_MATRIX_SCFG3 ((AT91_REG *) 	0xFFFFEC4C) // (MATRIX)  Slave Configuration Register 3
#define AT91C_MATRIX_MCFG4 ((AT91_REG *) 	0xFFFFEC10) // (MATRIX)  Master Configuration Register 4 
#define AT91C_MATRIX_MCFG2 ((AT91_REG *) 	0xFFFFEC08) // (MATRIX)  Master Configuration Register 2 
#define AT91C_MATRIX_PRBS6 ((AT91_REG *) 	0xFFFFECB4) // (MATRIX)  PRBS6
#define AT91C_MATRIX_SCFG4 ((AT91_REG *) 	0xFFFFEC50) // (MATRIX)  Slave Configuration Register 4
#define AT91C_MATRIX_MCFG8 ((AT91_REG *) 	0xFFFFEC20) // (MATRIX)  Master Configuration Register 8 
#define AT91C_MATRIX_PRAS3 ((AT91_REG *) 	0xFFFFEC98) // (MATRIX)  PRAS3
#define AT91C_MATRIX_PRAS4 ((AT91_REG *) 	0xFFFFECA0) // (MATRIX)  PRAS4
#define AT91C_MATRIX_PRAS1 ((AT91_REG *) 	0xFFFFEC88) // (MATRIX)  PRAS1
#define AT91C_MATRIX_PRAS0 ((AT91_REG *) 	0xFFFFEC80) // (MATRIX)  PRAS0
#define AT91C_MATRIX_SCFG0 ((AT91_REG *) 	0xFFFFEC40) // (MATRIX)  Slave Configuration Register 0
#define AT91C_MATRIX_PRBS7 ((AT91_REG *) 	0xFFFFECBC) // (MATRIX)  PRBS7
#define AT91C_MATRIX_PRBS4 ((AT91_REG *) 	0xFFFFECA4) // (MATRIX)  PRBS4
#define AT91C_MATRIX_PRBS2 ((AT91_REG *) 	0xFFFFEC94) // (MATRIX)  PRBS2
#define AT91C_MATRIX_MCFG5 ((AT91_REG *) 	0xFFFFEC14) // (MATRIX)  Master Configuration Register 5 
#define AT91C_MATRIX_SCFG7 ((AT91_REG *) 	0xFFFFEC5C) // (MATRIX)  Slave Configuration Register 7
#define AT91C_MATRIX_PRBS1 ((AT91_REG *) 	0xFFFFEC8C) // (MATRIX)  PRBS1
#define AT91C_MATRIX_MCFG6 ((AT91_REG *) 	0xFFFFEC18) // (MATRIX)  Master Configuration Register 6 
#define AT91C_MATRIX_PRBS0 ((AT91_REG *) 	0xFFFFEC84) // (MATRIX)  PRBS0
#define AT91C_MATRIX_MCFG0 ((AT91_REG *) 	0xFFFFEC00) // (MATRIX)  Master Configuration Register 0 
#define AT91C_MATRIX_PRAS5 ((AT91_REG *) 	0xFFFFECA8) // (MATRIX)  PRAS5
#define AT91C_MATRIX_SCFG1 ((AT91_REG *) 	0xFFFFEC44) // (MATRIX)  Slave Configuration Register 1
#define AT91C_MATRIX_PRAS7 ((AT91_REG *) 	0xFFFFECB8) // (MATRIX)  PRAS7
#define AT91C_MATRIX_PRAS2 ((AT91_REG *) 	0xFFFFEC90) // (MATRIX)  PRAS2
#define AT91C_MATRIX_PRAS6 ((AT91_REG *) 	0xFFFFECB0) // (MATRIX)  PRAS6
#define AT91C_MATRIX_SCFG2 ((AT91_REG *) 	0xFFFFEC48) // (MATRIX)  Slave Configuration Register 2
#define AT91C_MATRIX_PRBS3 ((AT91_REG *) 	0xFFFFEC9C) // (MATRIX)  PRBS3
// ========== Register definition for CCFG peripheral ========== 
#define AT91C_CCFG_MATRIXVERSION ((AT91_REG *) 	0xFFFFEDFC) // (CCFG)  Version Register
#define AT91C_CCFG_TCMR ((AT91_REG *) 	0xFFFFED14) // (CCFG)  TCM configuration
#define AT91C_CCFG_EBI0CSA ((AT91_REG *) 	0xFFFFED20) // (CCFG)  EBI0 Chip Select Assignement Register
#define AT91C_CCFG_EBI1CSA ((AT91_REG *) 	0xFFFFED24) // (CCFG)  EBI1 Chip Select Assignement Register
// ========== Register definition for PDC_DBGU peripheral ========== 
#define AT91C_DBGU_PTCR ((AT91_REG *) 	0xFFFFEF20) // (PDC_DBGU) PDC Transfer Control Register
#define AT91C_DBGU_RCR  ((AT91_REG *) 	0xFFFFEF04) // (PDC_DBGU) Receive Counter Register
#define AT91C_DBGU_TCR  ((AT91_REG *) 	0xFFFFEF0C) // (PDC_DBGU) Transmit Counter Register
#define AT91C_DBGU_RNCR ((AT91_REG *) 	0xFFFFEF14) // (PDC_DBGU) Receive Next Counter Register
#define AT91C_DBGU_TNPR ((AT91_REG *) 	0xFFFFEF18) // (PDC_DBGU) Transmit Next Pointer Register
#define AT91C_DBGU_RNPR ((AT91_REG *) 	0xFFFFEF10) // (PDC_DBGU) Receive Next Pointer Register
#define AT91C_DBGU_PTSR ((AT91_REG *) 	0xFFFFEF24) // (PDC_DBGU) PDC Transfer Status Register
#define AT91C_DBGU_RPR  ((AT91_REG *) 	0xFFFFEF00) // (PDC_DBGU) Receive Pointer Register
#define AT91C_DBGU_TPR  ((AT91_REG *) 	0xFFFFEF08) // (PDC_DBGU) Transmit Pointer Register
#define AT91C_DBGU_TNCR ((AT91_REG *) 	0xFFFFEF1C) // (PDC_DBGU) Transmit Next Counter Register
// ========== Register definition for DBGU peripheral ========== 
#define AT91C_DBGU_BRGR ((AT91_REG *) 	0xFFFFEE20) // (DBGU) Baud Rate Generator Register
#define AT91C_DBGU_CR   ((AT91_REG *) 	0xFFFFEE00) // (DBGU) Control Register
#define AT91C_DBGU_THR  ((AT91_REG *) 	0xFFFFEE1C) // (DBGU) Transmitter Holding Register
#define AT91C_DBGU_IDR  ((AT91_REG *) 	0xFFFFEE0C) // (DBGU) Interrupt Disable Register
#define AT91C_DBGU_EXID ((AT91_REG *) 	0xFFFFEE44) // (DBGU) Chip ID Extension Register
#define AT91C_DBGU_IMR  ((AT91_REG *) 	0xFFFFEE10) // (DBGU) Interrupt Mask Register
#define AT91C_DBGU_FNTR ((AT91_REG *) 	0xFFFFEE48) // (DBGU) Force NTRST Register
#define AT91C_DBGU_IER  ((AT91_REG *) 	0xFFFFEE08) // (DBGU) Interrupt Enable Register
#define AT91C_DBGU_CSR  ((AT91_REG *) 	0xFFFFEE14) // (DBGU) Channel Status Register
#define AT91C_DBGU_MR   ((AT91_REG *) 	0xFFFFEE04) // (DBGU) Mode Register
#define AT91C_DBGU_RHR  ((AT91_REG *) 	0xFFFFEE18) // (DBGU) Receiver Holding Register
#define AT91C_DBGU_CIDR ((AT91_REG *) 	0xFFFFEE40) // (DBGU) Chip ID Register
// ========== Register definition for AIC peripheral ========== 
#define AT91C_AIC_IVR   ((AT91_REG *) 	0xFFFFF100) // (AIC) IRQ Vector Register
#define AT91C_AIC_SMR   ((AT91_REG *) 	0xFFFFF000) // (AIC) Source Mode Register
#define AT91C_AIC_FVR   ((AT91_REG *) 	0xFFFFF104) // (AIC) FIQ Vector Register
#define AT91C_AIC_DCR   ((AT91_REG *) 	0xFFFFF138) // (AIC) Debug Control Register (Protect)
#define AT91C_AIC_EOICR ((AT91_REG *) 	0xFFFFF130) // (AIC) End of Interrupt Command Register
#define AT91C_AIC_SVR   ((AT91_REG *) 	0xFFFFF080) // (AIC) Source Vector Register
#define AT91C_AIC_FFSR  ((AT91_REG *) 	0xFFFFF148) // (AIC) Fast Forcing Status Register
#define AT91C_AIC_ICCR  ((AT91_REG *) 	0xFFFFF128) // (AIC) Interrupt Clear Command Register
#define AT91C_AIC_ISR   ((AT91_REG *) 	0xFFFFF108) // (AIC) Interrupt Status Register
#define AT91C_AIC_IMR   ((AT91_REG *) 	0xFFFFF110) // (AIC) Interrupt Mask Register
#define AT91C_AIC_IPR   ((AT91_REG *) 	0xFFFFF10C) // (AIC) Interrupt Pending Register
#define AT91C_AIC_FFER  ((AT91_REG *) 	0xFFFFF140) // (AIC) Fast Forcing Enable Register
#define AT91C_AIC_IECR  ((AT91_REG *) 	0xFFFFF120) // (AIC) Interrupt Enable Command Register
#define AT91C_AIC_ISCR  ((AT91_REG *) 	0xFFFFF12C) // (AIC) Interrupt Set Command Register
#define AT91C_AIC_FFDR  ((AT91_REG *) 	0xFFFFF144) // (AIC) Fast Forcing Disable Register
#define AT91C_AIC_CISR  ((AT91_REG *) 	0xFFFFF114) // (AIC) Core Interrupt Status Register
#define AT91C_AIC_IDCR  ((AT91_REG *) 	0xFFFFF124) // (AIC) Interrupt Disable Command Register
#define AT91C_AIC_SPU   ((AT91_REG *) 	0xFFFFF134) // (AIC) Spurious Vector Register
// ========== Register definition for PIOA peripheral ========== 
#define AT91C_PIOA_OWDR ((AT91_REG *) 	0xFFFFF2A4) // (PIOA) Output Write Disable Register
#define AT91C_PIOA_MDDR ((AT91_REG *) 	0xFFFFF254) // (PIOA) Multi-driver Disable Register
#define AT91C_PIOA_IFSR ((AT91_REG *) 	0xFFFFF228) // (PIOA) Input Filter Status Register
#define AT91C_PIOA_ISR  ((AT91_REG *) 	0xFFFFF24C) // (PIOA) Interrupt Status Register
#define AT91C_PIOA_CODR ((AT91_REG *) 	0xFFFFF234) // (PIOA) Clear Output Data Register
#define AT91C_PIOA_PDR  ((AT91_REG *) 	0xFFFFF204) // (PIOA) PIO Disable Register
#define AT91C_PIOA_OWSR ((AT91_REG *) 	0xFFFFF2A8) // (PIOA) Output Write Status Register
#define AT91C_PIOA_ASR  ((AT91_REG *) 	0xFFFFF270) // (PIOA) Select A Register
#define AT91C_PIOA_PPUSR ((AT91_REG *) 	0xFFFFF268) // (PIOA) Pull-up Status Register
#define AT91C_PIOA_IMR  ((AT91_REG *) 	0xFFFFF248) // (PIOA) Interrupt Mask Register
#define AT91C_PIOA_OSR  ((AT91_REG *) 	0xFFFFF218) // (PIOA) Output Status Register
#define AT91C_PIOA_ABSR ((AT91_REG *) 	0xFFFFF278) // (PIOA) AB Select Status Register
#define AT91C_PIOA_MDER ((AT91_REG *) 	0xFFFFF250) // (PIOA) Multi-driver Enable Register
#define AT91C_PIOA_IFDR ((AT91_REG *) 	0xFFFFF224) // (PIOA) Input Filter Disable Register
#define AT91C_PIOA_PDSR ((AT91_REG *) 	0xFFFFF23C) // (PIOA) Pin Data Status Register
#define AT91C_PIOA_SODR ((AT91_REG *) 	0xFFFFF230) // (PIOA) Set Output Data Register
#define AT91C_PIOA_BSR  ((AT91_REG *) 	0xFFFFF274) // (PIOA) Select B Register
#define AT91C_PIOA_OWER ((AT91_REG *) 	0xFFFFF2A0) // (PIOA) Output Write Enable Register
#define AT91C_PIOA_IFER ((AT91_REG *) 	0xFFFFF220) // (PIOA) Input Filter Enable Register
#define AT91C_PIOA_IDR  ((AT91_REG *) 	0xFFFFF244) // (PIOA) Interrupt Disable Register
#define AT91C_PIOA_ODR  ((AT91_REG *) 	0xFFFFF214) // (PIOA) Output Disable Registerr
#define AT91C_PIOA_IER  ((AT91_REG *) 	0xFFFFF240) // (PIOA) Interrupt Enable Register
#define AT91C_PIOA_PPUER ((AT91_REG *) 	0xFFFFF264) // (PIOA) Pull-up Enable Register
#define AT91C_PIOA_MDSR ((AT91_REG *) 	0xFFFFF258) // (PIOA) Multi-driver Status Register
#define AT91C_PIOA_OER  ((AT91_REG *) 	0xFFFFF210) // (PIOA) Output Enable Register
#define AT91C_PIOA_PER  ((AT91_REG *) 	0xFFFFF200) // (PIOA) PIO Enable Register
#define AT91C_PIOA_PPUDR ((AT91_REG *) 	0xFFFFF260) // (PIOA) Pull-up Disable Register
#define AT91C_PIOA_ODSR ((AT91_REG *) 	0xFFFFF238) // (PIOA) Output Data Status Register
#define AT91C_PIOA_PSR  ((AT91_REG *) 	0xFFFFF208) // (PIOA) PIO Status Register
// ========== Register definition for PIOB peripheral ========== 
#define AT91C_PIOB_ODR  ((AT91_REG *) 	0xFFFFF414) // (PIOB) Output Disable Registerr
#define AT91C_PIOB_SODR ((AT91_REG *) 	0xFFFFF430) // (PIOB) Set Output Data Register
#define AT91C_PIOB_ISR  ((AT91_REG *) 	0xFFFFF44C) // (PIOB) Interrupt Status Register
#define AT91C_PIOB_ABSR ((AT91_REG *) 	0xFFFFF478) // (PIOB) AB Select Status Register
#define AT91C_PIOB_IER  ((AT91_REG *) 	0xFFFFF440) // (PIOB) Interrupt Enable Register
#define AT91C_PIOB_PPUDR ((AT91_REG *) 	0xFFFFF460) // (PIOB) Pull-up Disable Register
#define AT91C_PIOB_IMR  ((AT91_REG *) 	0xFFFFF448) // (PIOB) Interrupt Mask Register
#define AT91C_PIOB_PER  ((AT91_REG *) 	0xFFFFF400) // (PIOB) PIO Enable Register
#define AT91C_PIOB_IFDR ((AT91_REG *) 	0xFFFFF424) // (PIOB) Input Filter Disable Register
#define AT91C_PIOB_OWDR ((AT91_REG *) 	0xFFFFF4A4) // (PIOB) Output Write Disable Register
#define AT91C_PIOB_MDSR ((AT91_REG *) 	0xFFFFF458) // (PIOB) Multi-driver Status Register
#define AT91C_PIOB_IDR  ((AT91_REG *) 	0xFFFFF444) // (PIOB) Interrupt Disable Register
#define AT91C_PIOB_ODSR ((AT91_REG *) 	0xFFFFF438) // (PIOB) Output Data Status Register
#define AT91C_PIOB_PPUSR ((AT91_REG *) 	0xFFFFF468) // (PIOB) Pull-up Status Register
#define AT91C_PIOB_OWSR ((AT91_REG *) 	0xFFFFF4A8) // (PIOB) Output Write Status Register
#define AT91C_PIOB_BSR  ((AT91_REG *) 	0xFFFFF474) // (PIOB) Select B Register
#define AT91C_PIOB_OWER ((AT91_REG *) 	0xFFFFF4A0) // (PIOB) Output Write Enable Register
#define AT91C_PIOB_IFER ((AT91_REG *) 	0xFFFFF420) // (PIOB) Input Filter Enable Register
#define AT91C_PIOB_PDSR ((AT91_REG *) 	0xFFFFF43C) // (PIOB) Pin Data Status Register
#define AT91C_PIOB_PPUER ((AT91_REG *) 	0xFFFFF464) // (PIOB) Pull-up Enable Register
#define AT91C_PIOB_OSR  ((AT91_REG *) 	0xFFFFF418) // (PIOB) Output Status Register
#define AT91C_PIOB_ASR  ((AT91_REG *) 	0xFFFFF470) // (PIOB) Select A Register
#define AT91C_PIOB_MDDR ((AT91_REG *) 	0xFFFFF454) // (PIOB) Multi-driver Disable Register
#define AT91C_PIOB_CODR ((AT91_REG *) 	0xFFFFF434) // (PIOB) Clear Output Data Register
#define AT91C_PIOB_MDER ((AT91_REG *) 	0xFFFFF450) // (PIOB) Multi-driver Enable Register
#define AT91C_PIOB_PDR  ((AT91_REG *) 	0xFFFFF404) // (PIOB) PIO Disable Register
#define AT91C_PIOB_IFSR ((AT91_REG *) 	0xFFFFF428) // (PIOB) Input Filter Status Register
#define AT91C_PIOB_OER  ((AT91_REG *) 	0xFFFFF410) // (PIOB) Output Enable Register
#define AT91C_PIOB_PSR  ((AT91_REG *) 	0xFFFFF408) // (PIOB) PIO Status Register
// ========== Register definition for PIOC peripheral ========== 
#define AT91C_PIOC_OWDR ((AT91_REG *) 	0xFFFFF6A4) // (PIOC) Output Write Disable Register
#define AT91C_PIOC_MDER ((AT91_REG *) 	0xFFFFF650) // (PIOC) Multi-driver Enable Register
#define AT91C_PIOC_PPUSR ((AT91_REG *) 	0xFFFFF668) // (PIOC) Pull-up Status Register
#define AT91C_PIOC_IMR  ((AT91_REG *) 	0xFFFFF648) // (PIOC) Interrupt Mask Register
#define AT91C_PIOC_ASR  ((AT91_REG *) 	0xFFFFF670) // (PIOC) Select A Register
#define AT91C_PIOC_PPUDR ((AT91_REG *) 	0xFFFFF660) // (PIOC) Pull-up Disable Register
#define AT91C_PIOC_PSR  ((AT91_REG *) 	0xFFFFF608) // (PIOC) PIO Status Register
#define AT91C_PIOC_IER  ((AT91_REG *) 	0xFFFFF640) // (PIOC) Interrupt Enable Register
#define AT91C_PIOC_CODR ((AT91_REG *) 	0xFFFFF634) // (PIOC) Clear Output Data Register
#define AT91C_PIOC_OWER ((AT91_REG *) 	0xFFFFF6A0) // (PIOC) Output Write Enable Register
#define AT91C_PIOC_ABSR ((AT91_REG *) 	0xFFFFF678) // (PIOC) AB Select Status Register
#define AT91C_PIOC_IFDR ((AT91_REG *) 	0xFFFFF624) // (PIOC) Input Filter Disable Register
#define AT91C_PIOC_PDSR ((AT91_REG *) 	0xFFFFF63C) // (PIOC) Pin Data Status Register
#define AT91C_PIOC_IDR  ((AT91_REG *) 	0xFFFFF644) // (PIOC) Interrupt Disable Register
#define AT91C_PIOC_OWSR ((AT91_REG *) 	0xFFFFF6A8) // (PIOC) Output Write Status Register
#define AT91C_PIOC_PDR  ((AT91_REG *) 	0xFFFFF604) // (PIOC) PIO Disable Register
#define AT91C_PIOC_ODR  ((AT91_REG *) 	0xFFFFF614) // (PIOC) Output Disable Registerr
#define AT91C_PIOC_IFSR ((AT91_REG *) 	0xFFFFF628) // (PIOC) Input Filter Status Register
#define AT91C_PIOC_PPUER ((AT91_REG *) 	0xFFFFF664) // (PIOC) Pull-up Enable Register
#define AT91C_PIOC_SODR ((AT91_REG *) 	0xFFFFF630) // (PIOC) Set Output Data Register
#define AT91C_PIOC_ISR  ((AT91_REG *) 	0xFFFFF64C) // (PIOC) Interrupt Status Register
#define AT91C_PIOC_ODSR ((AT91_REG *) 	0xFFFFF638) // (PIOC) Output Data Status Register
#define AT91C_PIOC_OSR  ((AT91_REG *) 	0xFFFFF618) // (PIOC) Output Status Register
#define AT91C_PIOC_MDSR ((AT91_REG *) 	0xFFFFF658) // (PIOC) Multi-driver Status Register
#define AT91C_PIOC_IFER ((AT91_REG *) 	0xFFFFF620) // (PIOC) Input Filter Enable Register
#define AT91C_PIOC_BSR  ((AT91_REG *) 	0xFFFFF674) // (PIOC) Select B Register
#define AT91C_PIOC_MDDR ((AT91_REG *) 	0xFFFFF654) // (PIOC) Multi-driver Disable Register
#define AT91C_PIOC_OER  ((AT91_REG *) 	0xFFFFF610) // (PIOC) Output Enable Register
#define AT91C_PIOC_PER  ((AT91_REG *) 	0xFFFFF600) // (PIOC) PIO Enable Register
// ========== Register definition for PIOD peripheral ========== 
#define AT91C_PIOD_OWDR ((AT91_REG *) 	0xFFFFF8A4) // (PIOD) Output Write Disable Register
#define AT91C_PIOD_SODR ((AT91_REG *) 	0xFFFFF830) // (PIOD) Set Output Data Register
#define AT91C_PIOD_PPUER ((AT91_REG *) 	0xFFFFF864) // (PIOD) Pull-up Enable Register
#define AT91C_PIOD_CODR ((AT91_REG *) 	0xFFFFF834) // (PIOD) Clear Output Data Register
#define AT91C_PIOD_PSR  ((AT91_REG *) 	0xFFFFF808) // (PIOD) PIO Status Register
#define AT91C_PIOD_PDR  ((AT91_REG *) 	0xFFFFF804) // (PIOD) PIO Disable Register
#define AT91C_PIOD_ODR  ((AT91_REG *) 	0xFFFFF814) // (PIOD) Output Disable Registerr
#define AT91C_PIOD_PPUSR ((AT91_REG *) 	0xFFFFF868) // (PIOD) Pull-up Status Register
#define AT91C_PIOD_ABSR ((AT91_REG *) 	0xFFFFF878) // (PIOD) AB Select Status Register
#define AT91C_PIOD_IFSR ((AT91_REG *) 	0xFFFFF828) // (PIOD) Input Filter Status Register
#define AT91C_PIOD_OER  ((AT91_REG *) 	0xFFFFF810) // (PIOD) Output Enable Register
#define AT91C_PIOD_IMR  ((AT91_REG *) 	0xFFFFF848) // (PIOD) Interrupt Mask Register
#define AT91C_PIOD_ASR  ((AT91_REG *) 	0xFFFFF870) // (PIOD) Select A Register
#define AT91C_PIOD_MDDR ((AT91_REG *) 	0xFFFFF854) // (PIOD) Multi-driver Disable Register
#define AT91C_PIOD_OWSR ((AT91_REG *) 	0xFFFFF8A8) // (PIOD) Output Write Status Register
#define AT91C_PIOD_PER  ((AT91_REG *) 	0xFFFFF800) // (PIOD) PIO Enable Register
#define AT91C_PIOD_IDR  ((AT91_REG *) 	0xFFFFF844) // (PIOD) Interrupt Disable Register
#define AT91C_PIOD_MDER ((AT91_REG *) 	0xFFFFF850) // (PIOD) Multi-driver Enable Register
#define AT91C_PIOD_PDSR ((AT91_REG *) 	0xFFFFF83C) // (PIOD) Pin Data Status Register
#define AT91C_PIOD_MDSR ((AT91_REG *) 	0xFFFFF858) // (PIOD) Multi-driver Status Register
#define AT91C_PIOD_OWER ((AT91_REG *) 	0xFFFFF8A0) // (PIOD) Output Write Enable Register
#define AT91C_PIOD_BSR  ((AT91_REG *) 	0xFFFFF874) // (PIOD) Select B Register
#define AT91C_PIOD_PPUDR ((AT91_REG *) 	0xFFFFF860) // (PIOD) Pull-up Disable Register
#define AT91C_PIOD_IFDR ((AT91_REG *) 	0xFFFFF824) // (PIOD) Input Filter Disable Register
#define AT91C_PIOD_IER  ((AT91_REG *) 	0xFFFFF840) // (PIOD) Interrupt Enable Register
#define AT91C_PIOD_OSR  ((AT91_REG *) 	0xFFFFF818) // (PIOD) Output Status Register
#define AT91C_PIOD_ODSR ((AT91_REG *) 	0xFFFFF838) // (PIOD) Output Data Status Register
#define AT91C_PIOD_ISR  ((AT91_REG *) 	0xFFFFF84C) // (PIOD) Interrupt Status Register
#define AT91C_PIOD_IFER ((AT91_REG *) 	0xFFFFF820) // (PIOD) Input Filter Enable Register
// ========== Register definition for PIOE peripheral ========== 
#define AT91C_PIOE_ODSR ((AT91_REG *) 	0xFFFFFA38) // (PIOE) Output Data Status Register
#define AT91C_PIOE_ABSR ((AT91_REG *) 	0xFFFFFA78) // (PIOE) AB Select Status Register
#define AT91C_PIOE_PSR  ((AT91_REG *) 	0xFFFFFA08) // (PIOE) PIO Status Register
#define AT91C_PIOE_PPUDR ((AT91_REG *) 	0xFFFFFA60) // (PIOE) Pull-up Disable Register
#define AT91C_PIOE_OER  ((AT91_REG *) 	0xFFFFFA10) // (PIOE) Output Enable Register
#define AT91C_PIOE_OWDR ((AT91_REG *) 	0xFFFFFAA4) // (PIOE) Output Write Disable Register
#define AT91C_PIOE_PER  ((AT91_REG *) 	0xFFFFFA00) // (PIOE) PIO Enable Register
#define AT91C_PIOE_IFSR ((AT91_REG *) 	0xFFFFFA28) // (PIOE) Input Filter Status Register
#define AT91C_PIOE_IFER ((AT91_REG *) 	0xFFFFFA20) // (PIOE) Input Filter Enable Register
#define AT91C_PIOE_ODR  ((AT91_REG *) 	0xFFFFFA14) // (PIOE) Output Disable Registerr
#define AT91C_PIOE_PPUSR ((AT91_REG *) 	0xFFFFFA68) // (PIOE) Pull-up Status Register
#define AT91C_PIOE_IFDR ((AT91_REG *) 	0xFFFFFA24) // (PIOE) Input Filter Disable Register
#define AT91C_PIOE_PDSR ((AT91_REG *) 	0xFFFFFA3C) // (PIOE) Pin Data Status Register
#define AT91C_PIOE_PPUER ((AT91_REG *) 	0xFFFFFA64) // (PIOE) Pull-up Enable Register
#define AT91C_PIOE_IDR  ((AT91_REG *) 	0xFFFFFA44) // (PIOE) Interrupt Disable Register
#define AT91C_PIOE_MDDR ((AT91_REG *) 	0xFFFFFA54) // (PIOE) Multi-driver Disable Register
#define AT91C_PIOE_ISR  ((AT91_REG *) 	0xFFFFFA4C) // (PIOE) Interrupt Status Register
#define AT91C_PIOE_OSR  ((AT91_REG *) 	0xFFFFFA18) // (PIOE) Output Status Register
#define AT91C_PIOE_CODR ((AT91_REG *) 	0xFFFFFA34) // (PIOE) Clear Output Data Register
#define AT91C_PIOE_MDSR ((AT91_REG *) 	0xFFFFFA58) // (PIOE) Multi-driver Status Register
#define AT91C_PIOE_PDR  ((AT91_REG *) 	0xFFFFFA04) // (PIOE) PIO Disable Register
#define AT91C_PIOE_IER  ((AT91_REG *) 	0xFFFFFA40) // (PIOE) Interrupt Enable Register
#define AT91C_PIOE_OWSR ((AT91_REG *) 	0xFFFFFAA8) // (PIOE) Output Write Status Register
#define AT91C_PIOE_BSR  ((AT91_REG *) 	0xFFFFFA74) // (PIOE) Select B Register
#define AT91C_PIOE_ASR  ((AT91_REG *) 	0xFFFFFA70) // (PIOE) Select A Register
#define AT91C_PIOE_SODR ((AT91_REG *) 	0xFFFFFA30) // (PIOE) Set Output Data Register
#define AT91C_PIOE_IMR  ((AT91_REG *) 	0xFFFFFA48) // (PIOE) Interrupt Mask Register
#define AT91C_PIOE_OWER ((AT91_REG *) 	0xFFFFFAA0) // (PIOE) Output Write Enable Register
#define AT91C_PIOE_MDER ((AT91_REG *) 	0xFFFFFA50) // (PIOE) Multi-driver Enable Register
// ========== Register definition for CKGR peripheral ========== 
#define AT91C_CKGR_MOR  ((AT91_REG *) 	0xFFFFFC20) // (CKGR) Main Oscillator Register
#define AT91C_CKGR_PLLBR ((AT91_REG *) 	0xFFFFFC2C) // (CKGR) PLL B Register
#define AT91C_CKGR_MCFR ((AT91_REG *) 	0xFFFFFC24) // (CKGR) Main Clock  Frequency Register
#define AT91C_CKGR_PLLAR ((AT91_REG *) 	0xFFFFFC28) // (CKGR) PLL A Register
// ========== Register definition for PMC peripheral ========== 
#define AT91C_PMC_PCER  ((AT91_REG *) 	0xFFFFFC10) // (PMC) Peripheral Clock Enable Register
#define AT91C_PMC_PCKR  ((AT91_REG *) 	0xFFFFFC40) // (PMC) Programmable Clock Register
#define AT91C_PMC_MCKR  ((AT91_REG *) 	0xFFFFFC30) // (PMC) Master Clock Register
#define AT91C_PMC_PLLAR ((AT91_REG *) 	0xFFFFFC28) // (PMC) PLL A Register
#define AT91C_PMC_PCDR  ((AT91_REG *) 	0xFFFFFC14) // (PMC) Peripheral Clock Disable Register
#define AT91C_PMC_SCSR  ((AT91_REG *) 	0xFFFFFC08) // (PMC) System Clock Status Register
#define AT91C_PMC_MCFR  ((AT91_REG *) 	0xFFFFFC24) // (PMC) Main Clock  Frequency Register
#define AT91C_PMC_IMR   ((AT91_REG *) 	0xFFFFFC6C) // (PMC) Interrupt Mask Register
#define AT91C_PMC_IER   ((AT91_REG *) 	0xFFFFFC60) // (PMC) Interrupt Enable Register
#define AT91C_PMC_MOR   ((AT91_REG *) 	0xFFFFFC20) // (PMC) Main Oscillator Register
#define AT91C_PMC_IDR   ((AT91_REG *) 	0xFFFFFC64) // (PMC) Interrupt Disable Register
#define AT91C_PMC_PLLBR ((AT91_REG *) 	0xFFFFFC2C) // (PMC) PLL B Register
#define AT91C_PMC_SCDR  ((AT91_REG *) 	0xFFFFFC04) // (PMC) System Clock Disable Register
#define AT91C_PMC_PCSR  ((AT91_REG *) 	0xFFFFFC18) // (PMC) Peripheral Clock Status Register
#define AT91C_PMC_SCER  ((AT91_REG *) 	0xFFFFFC00) // (PMC) System Clock Enable Register
#define AT91C_PMC_SR    ((AT91_REG *) 	0xFFFFFC68) // (PMC) Status Register
// ========== Register definition for RSTC peripheral ========== 
#define AT91C_RSTC_RCR  ((AT91_REG *) 	0xFFFFFD00) // (RSTC) Reset Control Register
#define AT91C_RSTC_RMR  ((AT91_REG *) 	0xFFFFFD08) // (RSTC) Reset Mode Register
#define AT91C_RSTC_RSR  ((AT91_REG *) 	0xFFFFFD04) // (RSTC) Reset Status Register
// ========== Register definition for SHDWC peripheral ========== 
#define AT91C_SHDWC_SHSR ((AT91_REG *) 	0xFFFFFD18) // (SHDWC) Shut Down Status Register
#define AT91C_SHDWC_SHMR ((AT91_REG *) 	0xFFFFFD14) // (SHDWC) Shut Down Mode Register
#define AT91C_SHDWC_SHCR ((AT91_REG *) 	0xFFFFFD10) // (SHDWC) Shut Down Control Register
// ========== Register definition for RTTC0 peripheral ========== 
#define AT91C_RTTC0_RTSR ((AT91_REG *) 	0xFFFFFD2C) // (RTTC0) Real-time Status Register
#define AT91C_RTTC0_RTMR ((AT91_REG *) 	0xFFFFFD20) // (RTTC0) Real-time Mode Register
#define AT91C_RTTC0_RTVR ((AT91_REG *) 	0xFFFFFD28) // (RTTC0) Real-time Value Register
#define AT91C_RTTC0_RTAR ((AT91_REG *) 	0xFFFFFD24) // (RTTC0) Real-time Alarm Register
// ========== Register definition for RTTC1 peripheral ========== 
#define AT91C_RTTC1_RTAR ((AT91_REG *) 	0xFFFFFD54) // (RTTC1) Real-time Alarm Register
#define AT91C_RTTC1_RTSR ((AT91_REG *) 	0xFFFFFD5C) // (RTTC1) Real-time Status Register
#define AT91C_RTTC1_RTVR ((AT91_REG *) 	0xFFFFFD58) // (RTTC1) Real-time Value Register
#define AT91C_RTTC1_RTMR ((AT91_REG *) 	0xFFFFFD50) // (RTTC1) Real-time Mode Register
// ========== Register definition for PITC peripheral ========== 
#define AT91C_PITC_PIVR ((AT91_REG *) 	0xFFFFFD38) // (PITC) Period Interval Value Register
#define AT91C_PITC_PISR ((AT91_REG *) 	0xFFFFFD34) // (PITC) Period Interval Status Register
#define AT91C_PITC_PIIR ((AT91_REG *) 	0xFFFFFD3C) // (PITC) Period Interval Image Register
#define AT91C_PITC_PIMR ((AT91_REG *) 	0xFFFFFD30) // (PITC) Period Interval Mode Register
// ========== Register definition for WDTC peripheral ========== 
#define AT91C_WDTC_WDCR ((AT91_REG *) 	0xFFFFFD40) // (WDTC) Watchdog Control Register
#define AT91C_WDTC_WDSR ((AT91_REG *) 	0xFFFFFD48) // (WDTC) Watchdog Status Register
#define AT91C_WDTC_WDMR ((AT91_REG *) 	0xFFFFFD44) // (WDTC) Watchdog Mode Register
// ========== Register definition for TC0 peripheral ========== 
#define AT91C_TC0_IER   ((AT91_REG *) 	0xFFF7C024) // (TC0) Interrupt Enable Register
#define AT91C_TC0_IMR   ((AT91_REG *) 	0xFFF7C02C) // (TC0) Interrupt Mask Register
#define AT91C_TC0_CCR   ((AT91_REG *) 	0xFFF7C000) // (TC0) Channel Control Register
#define AT91C_TC0_RB    ((AT91_REG *) 	0xFFF7C018) // (TC0) Register B
#define AT91C_TC0_CV    ((AT91_REG *) 	0xFFF7C010) // (TC0) Counter Value
#define AT91C_TC0_SR    ((AT91_REG *) 	0xFFF7C020) // (TC0) Status Register
#define AT91C_TC0_CMR   ((AT91_REG *) 	0xFFF7C004) // (TC0) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC0_RA    ((AT91_REG *) 	0xFFF7C014) // (TC0) Register A
#define AT91C_TC0_RC    ((AT91_REG *) 	0xFFF7C01C) // (TC0) Register C
#define AT91C_TC0_IDR   ((AT91_REG *) 	0xFFF7C028) // (TC0) Interrupt Disable Register
// ========== Register definition for TC1 peripheral ========== 
#define AT91C_TC1_IER   ((AT91_REG *) 	0xFFF7C064) // (TC1) Interrupt Enable Register
#define AT91C_TC1_SR    ((AT91_REG *) 	0xFFF7C060) // (TC1) Status Register
#define AT91C_TC1_RC    ((AT91_REG *) 	0xFFF7C05C) // (TC1) Register C
#define AT91C_TC1_CV    ((AT91_REG *) 	0xFFF7C050) // (TC1) Counter Value
#define AT91C_TC1_RA    ((AT91_REG *) 	0xFFF7C054) // (TC1) Register A
#define AT91C_TC1_CMR   ((AT91_REG *) 	0xFFF7C044) // (TC1) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC1_IDR   ((AT91_REG *) 	0xFFF7C068) // (TC1) Interrupt Disable Register
#define AT91C_TC1_RB    ((AT91_REG *) 	0xFFF7C058) // (TC1) Register B
#define AT91C_TC1_IMR   ((AT91_REG *) 	0xFFF7C06C) // (TC1) Interrupt Mask Register
#define AT91C_TC1_CCR   ((AT91_REG *) 	0xFFF7C040) // (TC1) Channel Control Register
// ========== Register definition for TC2 peripheral ========== 
#define AT91C_TC2_SR    ((AT91_REG *) 	0xFFF7C0A0) // (TC2) Status Register
#define AT91C_TC2_IMR   ((AT91_REG *) 	0xFFF7C0AC) // (TC2) Interrupt Mask Register
#define AT91C_TC2_IER   ((AT91_REG *) 	0xFFF7C0A4) // (TC2) Interrupt Enable Register
#define AT91C_TC2_CV    ((AT91_REG *) 	0xFFF7C090) // (TC2) Counter Value
#define AT91C_TC2_RB    ((AT91_REG *) 	0xFFF7C098) // (TC2) Register B
#define AT91C_TC2_CCR   ((AT91_REG *) 	0xFFF7C080) // (TC2) Channel Control Register
#define AT91C_TC2_CMR   ((AT91_REG *) 	0xFFF7C084) // (TC2) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC2_RA    ((AT91_REG *) 	0xFFF7C094) // (TC2) Register A
#define AT91C_TC2_IDR   ((AT91_REG *) 	0xFFF7C0A8) // (TC2) Interrupt Disable Register
#define AT91C_TC2_RC    ((AT91_REG *) 	0xFFF7C09C) // (TC2) Register C
// ========== Register definition for TCB0 peripheral ========== 
#define AT91C_TCB0_BCR  ((AT91_REG *) 	0xFFF7C0C0) // (TCB0) TC Block Control Register
#define AT91C_TCB0_BMR  ((AT91_REG *) 	0xFFF7C0C4) // (TCB0) TC Block Mode Register
// ========== Register definition for TCB1 peripheral ========== 
#define AT91C_TCB1_BMR  ((AT91_REG *) 	0xFFF7C104) // (TCB1) TC Block Mode Register
#define AT91C_TCB1_BCR  ((AT91_REG *) 	0xFFF7C100) // (TCB1) TC Block Control Register
// ========== Register definition for TCB2 peripheral ========== 
#define AT91C_TCB2_BCR  ((AT91_REG *) 	0xFFF7C140) // (TCB2) TC Block Control Register
#define AT91C_TCB2_BMR  ((AT91_REG *) 	0xFFF7C144) // (TCB2) TC Block Mode Register
// ========== Register definition for PDC_MCI0 peripheral ========== 
#define AT91C_MCI0_TCR  ((AT91_REG *) 	0xFFF8010C) // (PDC_MCI0) Transmit Counter Register
#define AT91C_MCI0_TNCR ((AT91_REG *) 	0xFFF8011C) // (PDC_MCI0) Transmit Next Counter Register
#define AT91C_MCI0_RNPR ((AT91_REG *) 	0xFFF80110) // (PDC_MCI0) Receive Next Pointer Register
#define AT91C_MCI0_TPR  ((AT91_REG *) 	0xFFF80108) // (PDC_MCI0) Transmit Pointer Register
#define AT91C_MCI0_TNPR ((AT91_REG *) 	0xFFF80118) // (PDC_MCI0) Transmit Next Pointer Register
#define AT91C_MCI0_PTSR ((AT91_REG *) 	0xFFF80124) // (PDC_MCI0) PDC Transfer Status Register
#define AT91C_MCI0_RCR  ((AT91_REG *) 	0xFFF80104) // (PDC_MCI0) Receive Counter Register
#define AT91C_MCI0_PTCR ((AT91_REG *) 	0xFFF80120) // (PDC_MCI0) PDC Transfer Control Register
#define AT91C_MCI0_RPR  ((AT91_REG *) 	0xFFF80100) // (PDC_MCI0) Receive Pointer Register
#define AT91C_MCI0_RNCR ((AT91_REG *) 	0xFFF80114) // (PDC_MCI0) Receive Next Counter Register
// ========== Register definition for MCI0 peripheral ========== 
#define AT91C_MCI0_CMDR ((AT91_REG *) 	0xFFF80014) // (MCI0) MCI Command Register
#define AT91C_MCI0_IMR  ((AT91_REG *) 	0xFFF8004C) // (MCI0) MCI Interrupt Mask Register
#define AT91C_MCI0_MR   ((AT91_REG *) 	0xFFF80004) // (MCI0) MCI Mode Register
#define AT91C_MCI0_CR   ((AT91_REG *) 	0xFFF80000) // (MCI0) MCI Control Register
#define AT91C_MCI0_IER  ((AT91_REG *) 	0xFFF80044) // (MCI0) MCI Interrupt Enable Register
#define AT91C_MCI0_RDR  ((AT91_REG *) 	0xFFF80030) // (MCI0) MCI Receive Data Register
#define AT91C_MCI0_SR   ((AT91_REG *) 	0xFFF80040) // (MCI0) MCI Status Register
#define AT91C_MCI0_DTOR ((AT91_REG *) 	0xFFF80008) // (MCI0) MCI Data Timeout Register
#define AT91C_MCI0_SDCR ((AT91_REG *) 	0xFFF8000C) // (MCI0) MCI SD Card Register
#define AT91C_MCI0_BLKR ((AT91_REG *) 	0xFFF80018) // (MCI0) MCI Block Register
#define AT91C_MCI0_VR   ((AT91_REG *) 	0xFFF800FC) // (MCI0) MCI Version Register
#define AT91C_MCI0_TDR  ((AT91_REG *) 	0xFFF80034) // (MCI0) MCI Transmit Data Register
#define AT91C_MCI0_ARGR ((AT91_REG *) 	0xFFF80010) // (MCI0) MCI Argument Register
#define AT91C_MCI0_RSPR ((AT91_REG *) 	0xFFF80020) // (MCI0) MCI Response Register
#define AT91C_MCI0_IDR  ((AT91_REG *) 	0xFFF80048) // (MCI0) MCI Interrupt Disable Register
// ========== Register definition for PDC_MCI1 peripheral ========== 
#define AT91C_MCI1_PTCR ((AT91_REG *) 	0xFFF84120) // (PDC_MCI1) PDC Transfer Control Register
#define AT91C_MCI1_PTSR ((AT91_REG *) 	0xFFF84124) // (PDC_MCI1) PDC Transfer Status Register
#define AT91C_MCI1_TPR  ((AT91_REG *) 	0xFFF84108) // (PDC_MCI1) Transmit Pointer Register
#define AT91C_MCI1_RPR  ((AT91_REG *) 	0xFFF84100) // (PDC_MCI1) Receive Pointer Register
#define AT91C_MCI1_TNCR ((AT91_REG *) 	0xFFF8411C) // (PDC_MCI1) Transmit Next Counter Register
#define AT91C_MCI1_RCR  ((AT91_REG *) 	0xFFF84104) // (PDC_MCI1) Receive Counter Register
#define AT91C_MCI1_TNPR ((AT91_REG *) 	0xFFF84118) // (PDC_MCI1) Transmit Next Pointer Register
#define AT91C_MCI1_TCR  ((AT91_REG *) 	0xFFF8410C) // (PDC_MCI1) Transmit Counter Register
#define AT91C_MCI1_RNPR ((AT91_REG *) 	0xFFF84110) // (PDC_MCI1) Receive Next Pointer Register
#define AT91C_MCI1_RNCR ((AT91_REG *) 	0xFFF84114) // (PDC_MCI1) Receive Next Counter Register
// ========== Register definition for MCI1 peripheral ========== 
#define AT91C_MCI1_SR   ((AT91_REG *) 	0xFFF84040) // (MCI1) MCI Status Register
#define AT91C_MCI1_RDR  ((AT91_REG *) 	0xFFF84030) // (MCI1) MCI Receive Data Register
#define AT91C_MCI1_RSPR ((AT91_REG *) 	0xFFF84020) // (MCI1) MCI Response Register
#define AT91C_MCI1_CMDR ((AT91_REG *) 	0xFFF84014) // (MCI1) MCI Command Register
#define AT91C_MCI1_IMR  ((AT91_REG *) 	0xFFF8404C) // (MCI1) MCI Interrupt Mask Register
#define AT91C_MCI1_DTOR ((AT91_REG *) 	0xFFF84008) // (MCI1) MCI Data Timeout Register
#define AT91C_MCI1_SDCR ((AT91_REG *) 	0xFFF8400C) // (MCI1) MCI SD Card Register
#define AT91C_MCI1_IDR  ((AT91_REG *) 	0xFFF84048) // (MCI1) MCI Interrupt Disable Register
#define AT91C_MCI1_ARGR ((AT91_REG *) 	0xFFF84010) // (MCI1) MCI Argument Register
#define AT91C_MCI1_TDR  ((AT91_REG *) 	0xFFF84034) // (MCI1) MCI Transmit Data Register
#define AT91C_MCI1_BLKR ((AT91_REG *) 	0xFFF84018) // (MCI1) MCI Block Register
#define AT91C_MCI1_VR   ((AT91_REG *) 	0xFFF840FC) // (MCI1) MCI Version Register
#define AT91C_MCI1_CR   ((AT91_REG *) 	0xFFF84000) // (MCI1) MCI Control Register
#define AT91C_MCI1_MR   ((AT91_REG *) 	0xFFF84004) // (MCI1) MCI Mode Register
#define AT91C_MCI1_IER  ((AT91_REG *) 	0xFFF84044) // (MCI1) MCI Interrupt Enable Register
// ========== Register definition for TWI peripheral ========== 
#define AT91C_TWI_IDR   ((AT91_REG *) 	0xFFF88028) // (TWI) Interrupt Disable Register
#define AT91C_TWI_RHR   ((AT91_REG *) 	0xFFF88030) // (TWI) Receive Holding Register
#define AT91C_TWI_IMR   ((AT91_REG *) 	0xFFF8802C) // (TWI) Interrupt Mask Register
#define AT91C_TWI_THR   ((AT91_REG *) 	0xFFF88034) // (TWI) Transmit Holding Register
#define AT91C_TWI_IER   ((AT91_REG *) 	0xFFF88024) // (TWI) Interrupt Enable Register
#define AT91C_TWI_IADR  ((AT91_REG *) 	0xFFF8800C) // (TWI) Internal Address Register
#define AT91C_TWI_SMR   ((AT91_REG *) 	0xFFF88008) // (TWI) Slave Mode Register
#define AT91C_TWI_MMR   ((AT91_REG *) 	0xFFF88004) // (TWI) Master Mode Register
#define AT91C_TWI_CR    ((AT91_REG *) 	0xFFF88000) // (TWI) Control Register
#define AT91C_TWI_SR    ((AT91_REG *) 	0xFFF88020) // (TWI) Status Register
#define AT91C_TWI_CWGR  ((AT91_REG *) 	0xFFF88010) // (TWI) Clock Waveform Generator Register
// ========== Register definition for PDC_US0 peripheral ========== 
#define AT91C_US0_TNPR  ((AT91_REG *) 	0xFFF8C118) // (PDC_US0) Transmit Next Pointer Register
#define AT91C_US0_PTSR  ((AT91_REG *) 	0xFFF8C124) // (PDC_US0) PDC Transfer Status Register
#define AT91C_US0_PTCR  ((AT91_REG *) 	0xFFF8C120) // (PDC_US0) PDC Transfer Control Register
#define AT91C_US0_RNCR  ((AT91_REG *) 	0xFFF8C114) // (PDC_US0) Receive Next Counter Register
#define AT91C_US0_RCR   ((AT91_REG *) 	0xFFF8C104) // (PDC_US0) Receive Counter Register
#define AT91C_US0_TNCR  ((AT91_REG *) 	0xFFF8C11C) // (PDC_US0) Transmit Next Counter Register
#define AT91C_US0_TCR   ((AT91_REG *) 	0xFFF8C10C) // (PDC_US0) Transmit Counter Register
#define AT91C_US0_RNPR  ((AT91_REG *) 	0xFFF8C110) // (PDC_US0) Receive Next Pointer Register
#define AT91C_US0_RPR   ((AT91_REG *) 	0xFFF8C100) // (PDC_US0) Receive Pointer Register
#define AT91C_US0_TPR   ((AT91_REG *) 	0xFFF8C108) // (PDC_US0) Transmit Pointer Register
// ========== Register definition for US0 peripheral ========== 
#define AT91C_US0_RTOR  ((AT91_REG *) 	0xFFF8C024) // (US0) Receiver Time-out Register
#define AT91C_US0_NER   ((AT91_REG *) 	0xFFF8C044) // (US0) Nb Errors Register
#define AT91C_US0_THR   ((AT91_REG *) 	0xFFF8C01C) // (US0) Transmitter Holding Register
#define AT91C_US0_MR    ((AT91_REG *) 	0xFFF8C004) // (US0) Mode Register
#define AT91C_US0_RHR   ((AT91_REG *) 	0xFFF8C018) // (US0) Receiver Holding Register
#define AT91C_US0_CSR   ((AT91_REG *) 	0xFFF8C014) // (US0) Channel Status Register
#define AT91C_US0_IMR   ((AT91_REG *) 	0xFFF8C010) // (US0) Interrupt Mask Register
#define AT91C_US0_IDR   ((AT91_REG *) 	0xFFF8C00C) // (US0) Interrupt Disable Register
#define AT91C_US0_FIDI  ((AT91_REG *) 	0xFFF8C040) // (US0) FI_DI_Ratio Register
#define AT91C_US0_CR    ((AT91_REG *) 	0xFFF8C000) // (US0) Control Register
#define AT91C_US0_IER   ((AT91_REG *) 	0xFFF8C008) // (US0) Interrupt Enable Register
#define AT91C_US0_TTGR  ((AT91_REG *) 	0xFFF8C028) // (US0) Transmitter Time-guard Register
#define AT91C_US0_BRGR  ((AT91_REG *) 	0xFFF8C020) // (US0) Baud Rate Generator Register
#define AT91C_US0_IF    ((AT91_REG *) 	0xFFF8C04C) // (US0) IRDA_FILTER Register
// ========== Register definition for PDC_US1 peripheral ========== 
#define AT91C_US1_PTCR  ((AT91_REG *) 	0xFFF90120) // (PDC_US1) PDC Transfer Control Register
#define AT91C_US1_TNCR  ((AT91_REG *) 	0xFFF9011C) // (PDC_US1) Transmit Next Counter Register
#define AT91C_US1_RCR   ((AT91_REG *) 	0xFFF90104) // (PDC_US1) Receive Counter Register
#define AT91C_US1_RPR   ((AT91_REG *) 	0xFFF90100) // (PDC_US1) Receive Pointer Register
#define AT91C_US1_TPR   ((AT91_REG *) 	0xFFF90108) // (PDC_US1) Transmit Pointer Register
#define AT91C_US1_TCR   ((AT91_REG *) 	0xFFF9010C) // (PDC_US1) Transmit Counter Register
#define AT91C_US1_RNPR  ((AT91_REG *) 	0xFFF90110) // (PDC_US1) Receive Next Pointer Register
#define AT91C_US1_TNPR  ((AT91_REG *) 	0xFFF90118) // (PDC_US1) Transmit Next Pointer Register
#define AT91C_US1_RNCR  ((AT91_REG *) 	0xFFF90114) // (PDC_US1) Receive Next Counter Register
#define AT91C_US1_PTSR  ((AT91_REG *) 	0xFFF90124) // (PDC_US1) PDC Transfer Status Register
// ========== Register definition for US1 peripheral ========== 
#define AT91C_US1_NER   ((AT91_REG *) 	0xFFF90044) // (US1) Nb Errors Register
#define AT91C_US1_RHR   ((AT91_REG *) 	0xFFF90018) // (US1) Receiver Holding Register
#define AT91C_US1_RTOR  ((AT91_REG *) 	0xFFF90024) // (US1) Receiver Time-out Register
#define AT91C_US1_IER   ((AT91_REG *) 	0xFFF90008) // (US1) Interrupt Enable Register
#define AT91C_US1_IF    ((AT91_REG *) 	0xFFF9004C) // (US1) IRDA_FILTER Register
#define AT91C_US1_CR    ((AT91_REG *) 	0xFFF90000) // (US1) Control Register
#define AT91C_US1_IMR   ((AT91_REG *) 	0xFFF90010) // (US1) Interrupt Mask Register
#define AT91C_US1_TTGR  ((AT91_REG *) 	0xFFF90028) // (US1) Transmitter Time-guard Register
#define AT91C_US1_MR    ((AT91_REG *) 	0xFFF90004) // (US1) Mode Register
#define AT91C_US1_IDR   ((AT91_REG *) 	0xFFF9000C) // (US1) Interrupt Disable Register
#define AT91C_US1_FIDI  ((AT91_REG *) 	0xFFF90040) // (US1) FI_DI_Ratio Register
#define AT91C_US1_CSR   ((AT91_REG *) 	0xFFF90014) // (US1) Channel Status Register
#define AT91C_US1_THR   ((AT91_REG *) 	0xFFF9001C) // (US1) Transmitter Holding Register
#define AT91C_US1_BRGR  ((AT91_REG *) 	0xFFF90020) // (US1) Baud Rate Generator Register
// ========== Register definition for PDC_US2 peripheral ========== 
#define AT91C_US2_RNCR  ((AT91_REG *) 	0xFFF94114) // (PDC_US2) Receive Next Counter Register
#define AT91C_US2_PTCR  ((AT91_REG *) 	0xFFF94120) // (PDC_US2) PDC Transfer Control Register
#define AT91C_US2_TNPR  ((AT91_REG *) 	0xFFF94118) // (PDC_US2) Transmit Next Pointer Register
#define AT91C_US2_TNCR  ((AT91_REG *) 	0xFFF9411C) // (PDC_US2) Transmit Next Counter Register
#define AT91C_US2_TPR   ((AT91_REG *) 	0xFFF94108) // (PDC_US2) Transmit Pointer Register
#define AT91C_US2_RCR   ((AT91_REG *) 	0xFFF94104) // (PDC_US2) Receive Counter Register
#define AT91C_US2_PTSR  ((AT91_REG *) 	0xFFF94124) // (PDC_US2) PDC Transfer Status Register
#define AT91C_US2_TCR   ((AT91_REG *) 	0xFFF9410C) // (PDC_US2) Transmit Counter Register
#define AT91C_US2_RPR   ((AT91_REG *) 	0xFFF94100) // (PDC_US2) Receive Pointer Register
#define AT91C_US2_RNPR  ((AT91_REG *) 	0xFFF94110) // (PDC_US2) Receive Next Pointer Register
// ========== Register definition for US2 peripheral ========== 
#define AT91C_US2_TTGR  ((AT91_REG *) 	0xFFF94028) // (US2) Transmitter Time-guard Register
#define AT91C_US2_RHR   ((AT91_REG *) 	0xFFF94018) // (US2) Receiver Holding Register
#define AT91C_US2_IMR   ((AT91_REG *) 	0xFFF94010) // (US2) Interrupt Mask Register
#define AT91C_US2_IER   ((AT91_REG *) 	0xFFF94008) // (US2) Interrupt Enable Register
#define AT91C_US2_NER   ((AT91_REG *) 	0xFFF94044) // (US2) Nb Errors Register
#define AT91C_US2_CR    ((AT91_REG *) 	0xFFF94000) // (US2) Control Register
#define AT91C_US2_FIDI  ((AT91_REG *) 	0xFFF94040) // (US2) FI_DI_Ratio Register
#define AT91C_US2_MR    ((AT91_REG *) 	0xFFF94004) // (US2) Mode Register
#define AT91C_US2_IDR   ((AT91_REG *) 	0xFFF9400C) // (US2) Interrupt Disable Register
#define AT91C_US2_THR   ((AT91_REG *) 	0xFFF9401C) // (US2) Transmitter Holding Register
#define AT91C_US2_IF    ((AT91_REG *) 	0xFFF9404C) // (US2) IRDA_FILTER Register
#define AT91C_US2_BRGR  ((AT91_REG *) 	0xFFF94020) // (US2) Baud Rate Generator Register
#define AT91C_US2_CSR   ((AT91_REG *) 	0xFFF94014) // (US2) Channel Status Register
#define AT91C_US2_RTOR  ((AT91_REG *) 	0xFFF94024) // (US2) Receiver Time-out Register
// ========== Register definition for PDC_SSC0 peripheral ========== 
#define AT91C_SSC0_PTSR ((AT91_REG *) 	0xFFF98124) // (PDC_SSC0) PDC Transfer Status Register
#define AT91C_SSC0_TCR  ((AT91_REG *) 	0xFFF9810C) // (PDC_SSC0) Transmit Counter Register
#define AT91C_SSC0_RNPR ((AT91_REG *) 	0xFFF98110) // (PDC_SSC0) Receive Next Pointer Register
#define AT91C_SSC0_RNCR ((AT91_REG *) 	0xFFF98114) // (PDC_SSC0) Receive Next Counter Register
#define AT91C_SSC0_TNPR ((AT91_REG *) 	0xFFF98118) // (PDC_SSC0) Transmit Next Pointer Register
#define AT91C_SSC0_RPR  ((AT91_REG *) 	0xFFF98100) // (PDC_SSC0) Receive Pointer Register
#define AT91C_SSC0_TPR  ((AT91_REG *) 	0xFFF98108) // (PDC_SSC0) Transmit Pointer Register
#define AT91C_SSC0_RCR  ((AT91_REG *) 	0xFFF98104) // (PDC_SSC0) Receive Counter Register
#define AT91C_SSC0_TNCR ((AT91_REG *) 	0xFFF9811C) // (PDC_SSC0) Transmit Next Counter Register
#define AT91C_SSC0_PTCR ((AT91_REG *) 	0xFFF98120) // (PDC_SSC0) PDC Transfer Control Register
// ========== Register definition for SSC0 peripheral ========== 
#define AT91C_SSC0_RFMR ((AT91_REG *) 	0xFFF98014) // (SSC0) Receive Frame Mode Register
#define AT91C_SSC0_RHR  ((AT91_REG *) 	0xFFF98020) // (SSC0) Receive Holding Register
#define AT91C_SSC0_THR  ((AT91_REG *) 	0xFFF98024) // (SSC0) Transmit Holding Register
#define AT91C_SSC0_CMR  ((AT91_REG *) 	0xFFF98004) // (SSC0) Clock Mode Register
#define AT91C_SSC0_IMR  ((AT91_REG *) 	0xFFF9804C) // (SSC0) Interrupt Mask Register
#define AT91C_SSC0_IDR  ((AT91_REG *) 	0xFFF98048) // (SSC0) Interrupt Disable Register
#define AT91C_SSC0_IER  ((AT91_REG *) 	0xFFF98044) // (SSC0) Interrupt Enable Register
#define AT91C_SSC0_TSHR ((AT91_REG *) 	0xFFF98034) // (SSC0) Transmit Sync Holding Register
#define AT91C_SSC0_SR   ((AT91_REG *) 	0xFFF98040) // (SSC0) Status Register
#define AT91C_SSC0_CR   ((AT91_REG *) 	0xFFF98000) // (SSC0) Control Register
#define AT91C_SSC0_RCMR ((AT91_REG *) 	0xFFF98010) // (SSC0) Receive Clock ModeRegister
#define AT91C_SSC0_TFMR ((AT91_REG *) 	0xFFF9801C) // (SSC0) Transmit Frame Mode Register
#define AT91C_SSC0_RSHR ((AT91_REG *) 	0xFFF98030) // (SSC0) Receive Sync Holding Register
#define AT91C_SSC0_TCMR ((AT91_REG *) 	0xFFF98018) // (SSC0) Transmit Clock Mode Register
// ========== Register definition for PDC_SSC1 peripheral ========== 
#define AT91C_SSC1_TNPR ((AT91_REG *) 	0xFFF9C118) // (PDC_SSC1) Transmit Next Pointer Register
#define AT91C_SSC1_PTSR ((AT91_REG *) 	0xFFF9C124) // (PDC_SSC1) PDC Transfer Status Register
#define AT91C_SSC1_TNCR ((AT91_REG *) 	0xFFF9C11C) // (PDC_SSC1) Transmit Next Counter Register
#define AT91C_SSC1_RNCR ((AT91_REG *) 	0xFFF9C114) // (PDC_SSC1) Receive Next Counter Register
#define AT91C_SSC1_TPR  ((AT91_REG *) 	0xFFF9C108) // (PDC_SSC1) Transmit Pointer Register
#define AT91C_SSC1_RCR  ((AT91_REG *) 	0xFFF9C104) // (PDC_SSC1) Receive Counter Register
#define AT91C_SSC1_PTCR ((AT91_REG *) 	0xFFF9C120) // (PDC_SSC1) PDC Transfer Control Register
#define AT91C_SSC1_RNPR ((AT91_REG *) 	0xFFF9C110) // (PDC_SSC1) Receive Next Pointer Register
#define AT91C_SSC1_TCR  ((AT91_REG *) 	0xFFF9C10C) // (PDC_SSC1) Transmit Counter Register
#define AT91C_SSC1_RPR  ((AT91_REG *) 	0xFFF9C100) // (PDC_SSC1) Receive Pointer Register
// ========== Register definition for SSC1 peripheral ========== 
#define AT91C_SSC1_CMR  ((AT91_REG *) 	0xFFF9C004) // (SSC1) Clock Mode Register
#define AT91C_SSC1_SR   ((AT91_REG *) 	0xFFF9C040) // (SSC1) Status Register
#define AT91C_SSC1_TSHR ((AT91_REG *) 	0xFFF9C034) // (SSC1) Transmit Sync Holding Register
#define AT91C_SSC1_TCMR ((AT91_REG *) 	0xFFF9C018) // (SSC1) Transmit Clock Mode Register
#define AT91C_SSC1_IMR  ((AT91_REG *) 	0xFFF9C04C) // (SSC1) Interrupt Mask Register
#define AT91C_SSC1_IDR  ((AT91_REG *) 	0xFFF9C048) // (SSC1) Interrupt Disable Register
#define AT91C_SSC1_RCMR ((AT91_REG *) 	0xFFF9C010) // (SSC1) Receive Clock ModeRegister
#define AT91C_SSC1_IER  ((AT91_REG *) 	0xFFF9C044) // (SSC1) Interrupt Enable Register
#define AT91C_SSC1_RSHR ((AT91_REG *) 	0xFFF9C030) // (SSC1) Receive Sync Holding Register
#define AT91C_SSC1_CR   ((AT91_REG *) 	0xFFF9C000) // (SSC1) Control Register
#define AT91C_SSC1_RHR  ((AT91_REG *) 	0xFFF9C020) // (SSC1) Receive Holding Register
#define AT91C_SSC1_THR  ((AT91_REG *) 	0xFFF9C024) // (SSC1) Transmit Holding Register
#define AT91C_SSC1_RFMR ((AT91_REG *) 	0xFFF9C014) // (SSC1) Receive Frame Mode Register
#define AT91C_SSC1_TFMR ((AT91_REG *) 	0xFFF9C01C) // (SSC1) Transmit Frame Mode Register
// ========== Register definition for PDC_AC97C peripheral ========== 
#define AT91C_AC97C_RNPR ((AT91_REG *) 	0xFFFA0110) // (PDC_AC97C) Receive Next Pointer Register
#define AT91C_AC97C_TCR ((AT91_REG *) 	0xFFFA010C) // (PDC_AC97C) Transmit Counter Register
#define AT91C_AC97C_TNCR ((AT91_REG *) 	0xFFFA011C) // (PDC_AC97C) Transmit Next Counter Register
#define AT91C_AC97C_RCR ((AT91_REG *) 	0xFFFA0104) // (PDC_AC97C) Receive Counter Register
#define AT91C_AC97C_RNCR ((AT91_REG *) 	0xFFFA0114) // (PDC_AC97C) Receive Next Counter Register
#define AT91C_AC97C_PTCR ((AT91_REG *) 	0xFFFA0120) // (PDC_AC97C) PDC Transfer Control Register
#define AT91C_AC97C_TPR ((AT91_REG *) 	0xFFFA0108) // (PDC_AC97C) Transmit Pointer Register
#define AT91C_AC97C_RPR ((AT91_REG *) 	0xFFFA0100) // (PDC_AC97C) Receive Pointer Register
#define AT91C_AC97C_PTSR ((AT91_REG *) 	0xFFFA0124) // (PDC_AC97C) PDC Transfer Status Register
#define AT91C_AC97C_TNPR ((AT91_REG *) 	0xFFFA0118) // (PDC_AC97C) Transmit Next Pointer Register
// ========== Register definition for AC97C peripheral ========== 
#define AT91C_AC97C_CORHR ((AT91_REG *) 	0xFFFA0040) // (AC97C) COdec Transmit Holding Register
#define AT91C_AC97C_MR  ((AT91_REG *) 	0xFFFA0008) // (AC97C) Mode Register
#define AT91C_AC97C_CATHR ((AT91_REG *) 	0xFFFA0024) // (AC97C) Channel A Transmit Holding Register
#define AT91C_AC97C_IER ((AT91_REG *) 	0xFFFA0054) // (AC97C) Interrupt Enable Register
#define AT91C_AC97C_CASR ((AT91_REG *) 	0xFFFA0028) // (AC97C) Channel A Status Register
#define AT91C_AC97C_CBTHR ((AT91_REG *) 	0xFFFA0034) // (AC97C) Channel B Transmit Holding Register (optional)
#define AT91C_AC97C_ICA ((AT91_REG *) 	0xFFFA0010) // (AC97C) Input Channel AssignementRegister
#define AT91C_AC97C_IMR ((AT91_REG *) 	0xFFFA005C) // (AC97C) Interrupt Mask Register
#define AT91C_AC97C_IDR ((AT91_REG *) 	0xFFFA0058) // (AC97C) Interrupt Disable Register
#define AT91C_AC97C_CARHR ((AT91_REG *) 	0xFFFA0020) // (AC97C) Channel A Receive Holding Register
#define AT91C_AC97C_VERSION ((AT91_REG *) 	0xFFFA00FC) // (AC97C) Version Register
#define AT91C_AC97C_CBRHR ((AT91_REG *) 	0xFFFA0030) // (AC97C) Channel B Receive Holding Register (optional)
#define AT91C_AC97C_COTHR ((AT91_REG *) 	0xFFFA0044) // (AC97C) COdec Transmit Holding Register
#define AT91C_AC97C_OCA ((AT91_REG *) 	0xFFFA0014) // (AC97C) Output Channel Assignement Register
#define AT91C_AC97C_CBMR ((AT91_REG *) 	0xFFFA003C) // (AC97C) Channel B Mode Register
#define AT91C_AC97C_COMR ((AT91_REG *) 	0xFFFA004C) // (AC97C) CODEC Mask Status Register
#define AT91C_AC97C_CBSR ((AT91_REG *) 	0xFFFA0038) // (AC97C) Channel B Status Register
#define AT91C_AC97C_COSR ((AT91_REG *) 	0xFFFA0048) // (AC97C) CODEC Status Register
#define AT91C_AC97C_CAMR ((AT91_REG *) 	0xFFFA002C) // (AC97C) Channel A Mode Register
#define AT91C_AC97C_SR  ((AT91_REG *) 	0xFFFA0050) // (AC97C) Status Register
// ========== Register definition for PDC_SPI0 peripheral ========== 
#define AT91C_SPI0_TPR  ((AT91_REG *) 	0xFFFA4108) // (PDC_SPI0) Transmit Pointer Register
#define AT91C_SPI0_PTCR ((AT91_REG *) 	0xFFFA4120) // (PDC_SPI0) PDC Transfer Control Register
#define AT91C_SPI0_RNPR ((AT91_REG *) 	0xFFFA4110) // (PDC_SPI0) Receive Next Pointer Register
#define AT91C_SPI0_TNCR ((AT91_REG *) 	0xFFFA411C) // (PDC_SPI0) Transmit Next Counter Register
#define AT91C_SPI0_TCR  ((AT91_REG *) 	0xFFFA410C) // (PDC_SPI0) Transmit Counter Register
#define AT91C_SPI0_RCR  ((AT91_REG *) 	0xFFFA4104) // (PDC_SPI0) Receive Counter Register
#define AT91C_SPI0_RNCR ((AT91_REG *) 	0xFFFA4114) // (PDC_SPI0) Receive Next Counter Register
#define AT91C_SPI0_TNPR ((AT91_REG *) 	0xFFFA4118) // (PDC_SPI0) Transmit Next Pointer Register
#define AT91C_SPI0_RPR  ((AT91_REG *) 	0xFFFA4100) // (PDC_SPI0) Receive Pointer Register
#define AT91C_SPI0_PTSR ((AT91_REG *) 	0xFFFA4124) // (PDC_SPI0) PDC Transfer Status Register
// ========== Register definition for SPI0 peripheral ========== 
#define AT91C_SPI0_MR   ((AT91_REG *) 	0xFFFA4004) // (SPI0) Mode Register
#define AT91C_SPI0_RDR  ((AT91_REG *) 	0xFFFA4008) // (SPI0) Receive Data Register
#define AT91C_SPI0_CR   ((AT91_REG *) 	0xFFFA4000) // (SPI0) Control Register
#define AT91C_SPI0_IER  ((AT91_REG *) 	0xFFFA4014) // (SPI0) Interrupt Enable Register
#define AT91C_SPI0_TDR  ((AT91_REG *) 	0xFFFA400C) // (SPI0) Transmit Data Register
#define AT91C_SPI0_IDR  ((AT91_REG *) 	0xFFFA4018) // (SPI0) Interrupt Disable Register
#define AT91C_SPI0_CSR  ((AT91_REG *) 	0xFFFA4030) // (SPI0) Chip Select Register
#define AT91C_SPI0_SR   ((AT91_REG *) 	0xFFFA4010) // (SPI0) Status Register
#define AT91C_SPI0_IMR  ((AT91_REG *) 	0xFFFA401C) // (SPI0) Interrupt Mask Register
// ========== Register definition for PDC_SPI1 peripheral ========== 
#define AT91C_SPI1_RNCR ((AT91_REG *) 	0xFFFA8114) // (PDC_SPI1) Receive Next Counter Register
#define AT91C_SPI1_TCR  ((AT91_REG *) 	0xFFFA810C) // (PDC_SPI1) Transmit Counter Register
#define AT91C_SPI1_RCR  ((AT91_REG *) 	0xFFFA8104) // (PDC_SPI1) Receive Counter Register
#define AT91C_SPI1_TNPR ((AT91_REG *) 	0xFFFA8118) // (PDC_SPI1) Transmit Next Pointer Register
#define AT91C_SPI1_RNPR ((AT91_REG *) 	0xFFFA8110) // (PDC_SPI1) Receive Next Pointer Register
#define AT91C_SPI1_RPR  ((AT91_REG *) 	0xFFFA8100) // (PDC_SPI1) Receive Pointer Register
#define AT91C_SPI1_TNCR ((AT91_REG *) 	0xFFFA811C) // (PDC_SPI1) Transmit Next Counter Register
#define AT91C_SPI1_TPR  ((AT91_REG *) 	0xFFFA8108) // (PDC_SPI1) Transmit Pointer Register
#define AT91C_SPI1_PTSR ((AT91_REG *) 	0xFFFA8124) // (PDC_SPI1) PDC Transfer Status Register
#define AT91C_SPI1_PTCR ((AT91_REG *) 	0xFFFA8120) // (PDC_SPI1) PDC Transfer Control Register
// ========== Register definition for SPI1 peripheral ========== 
#define AT91C_SPI1_CSR  ((AT91_REG *) 	0xFFFA8030) // (SPI1) Chip Select Register
#define AT91C_SPI1_IER  ((AT91_REG *) 	0xFFFA8014) // (SPI1) Interrupt Enable Register
#define AT91C_SPI1_RDR  ((AT91_REG *) 	0xFFFA8008) // (SPI1) Receive Data Register
#define AT91C_SPI1_IDR  ((AT91_REG *) 	0xFFFA8018) // (SPI1) Interrupt Disable Register
#define AT91C_SPI1_MR   ((AT91_REG *) 	0xFFFA8004) // (SPI1) Mode Register
#define AT91C_SPI1_CR   ((AT91_REG *) 	0xFFFA8000) // (SPI1) Control Register
#define AT91C_SPI1_SR   ((AT91_REG *) 	0xFFFA8010) // (SPI1) Status Register
#define AT91C_SPI1_TDR  ((AT91_REG *) 	0xFFFA800C) // (SPI1) Transmit Data Register
#define AT91C_SPI1_IMR  ((AT91_REG *) 	0xFFFA801C) // (SPI1) Interrupt Mask Register
// ========== Register definition for CAN_MB0 peripheral ========== 
#define AT91C_CAN_MB0_MID ((AT91_REG *) 	0xFFFAC208) // (CAN_MB0) MailBox ID Register
#define AT91C_CAN_MB0_MFID ((AT91_REG *) 	0xFFFAC20C) // (CAN_MB0) MailBox Family ID Register
#define AT91C_CAN_MB0_MAM ((AT91_REG *) 	0xFFFAC204) // (CAN_MB0) MailBox Acceptance Mask Register
#define AT91C_CAN_MB0_MCR ((AT91_REG *) 	0xFFFAC21C) // (CAN_MB0) MailBox Control Register
#define AT91C_CAN_MB0_MMR ((AT91_REG *) 	0xFFFAC200) // (CAN_MB0) MailBox Mode Register
#define AT91C_CAN_MB0_MDL ((AT91_REG *) 	0xFFFAC214) // (CAN_MB0) MailBox Data Low Register
#define AT91C_CAN_MB0_MDH ((AT91_REG *) 	0xFFFAC218) // (CAN_MB0) MailBox Data High Register
#define AT91C_CAN_MB0_MSR ((AT91_REG *) 	0xFFFAC210) // (CAN_MB0) MailBox Status Register
// ========== Register definition for CAN_MB1 peripheral ========== 
#define AT91C_CAN_MB1_MDL ((AT91_REG *) 	0xFFFAC234) // (CAN_MB1) MailBox Data Low Register
#define AT91C_CAN_MB1_MAM ((AT91_REG *) 	0xFFFAC224) // (CAN_MB1) MailBox Acceptance Mask Register
#define AT91C_CAN_MB1_MID ((AT91_REG *) 	0xFFFAC228) // (CAN_MB1) MailBox ID Register
#define AT91C_CAN_MB1_MMR ((AT91_REG *) 	0xFFFAC220) // (CAN_MB1) MailBox Mode Register
#define AT91C_CAN_MB1_MCR ((AT91_REG *) 	0xFFFAC23C) // (CAN_MB1) MailBox Control Register
#define AT91C_CAN_MB1_MFID ((AT91_REG *) 	0xFFFAC22C) // (CAN_MB1) MailBox Family ID Register
#define AT91C_CAN_MB1_MSR ((AT91_REG *) 	0xFFFAC230) // (CAN_MB1) MailBox Status Register
#define AT91C_CAN_MB1_MDH ((AT91_REG *) 	0xFFFAC238) // (CAN_MB1) MailBox Data High Register
// ========== Register definition for CAN_MB2 peripheral ========== 
#define AT91C_CAN_MB2_MID ((AT91_REG *) 	0xFFFAC248) // (CAN_MB2) MailBox ID Register
#define AT91C_CAN_MB2_MSR ((AT91_REG *) 	0xFFFAC250) // (CAN_MB2) MailBox Status Register
#define AT91C_CAN_MB2_MDL ((AT91_REG *) 	0xFFFAC254) // (CAN_MB2) MailBox Data Low Register
#define AT91C_CAN_MB2_MCR ((AT91_REG *) 	0xFFFAC25C) // (CAN_MB2) MailBox Control Register
#define AT91C_CAN_MB2_MDH ((AT91_REG *) 	0xFFFAC258) // (CAN_MB2) MailBox Data High Register
#define AT91C_CAN_MB2_MAM ((AT91_REG *) 	0xFFFAC244) // (CAN_MB2) MailBox Acceptance Mask Register
#define AT91C_CAN_MB2_MMR ((AT91_REG *) 	0xFFFAC240) // (CAN_MB2) MailBox Mode Register
#define AT91C_CAN_MB2_MFID ((AT91_REG *) 	0xFFFAC24C) // (CAN_MB2) MailBox Family ID Register
// ========== Register definition for CAN_MB3 peripheral ========== 
#define AT91C_CAN_MB3_MDL ((AT91_REG *) 	0xFFFAC274) // (CAN_MB3) MailBox Data Low Register
#define AT91C_CAN_MB3_MFID ((AT91_REG *) 	0xFFFAC26C) // (CAN_MB3) MailBox Family ID Register
#define AT91C_CAN_MB3_MID ((AT91_REG *) 	0xFFFAC268) // (CAN_MB3) MailBox ID Register
#define AT91C_CAN_MB3_MDH ((AT91_REG *) 	0xFFFAC278) // (CAN_MB3) MailBox Data High Register
#define AT91C_CAN_MB3_MAM ((AT91_REG *) 	0xFFFAC264) // (CAN_MB3) MailBox Acceptance Mask Register
#define AT91C_CAN_MB3_MMR ((AT91_REG *) 	0xFFFAC260) // (CAN_MB3) MailBox Mode Register
#define AT91C_CAN_MB3_MCR ((AT91_REG *) 	0xFFFAC27C) // (CAN_MB3) MailBox Control Register
#define AT91C_CAN_MB3_MSR ((AT91_REG *) 	0xFFFAC270) // (CAN_MB3) MailBox Status Register
// ========== Register definition for CAN_MB4 peripheral ========== 
#define AT91C_CAN_MB4_MCR ((AT91_REG *) 	0xFFFAC29C) // (CAN_MB4) MailBox Control Register
#define AT91C_CAN_MB4_MDH ((AT91_REG *) 	0xFFFAC298) // (CAN_MB4) MailBox Data High Register
#define AT91C_CAN_MB4_MID ((AT91_REG *) 	0xFFFAC288) // (CAN_MB4) MailBox ID Register
#define AT91C_CAN_MB4_MMR ((AT91_REG *) 	0xFFFAC280) // (CAN_MB4) MailBox Mode Register
#define AT91C_CAN_MB4_MSR ((AT91_REG *) 	0xFFFAC290) // (CAN_MB4) MailBox Status Register
#define AT91C_CAN_MB4_MFID ((AT91_REG *) 	0xFFFAC28C) // (CAN_MB4) MailBox Family ID Register
#define AT91C_CAN_MB4_MAM ((AT91_REG *) 	0xFFFAC284) // (CAN_MB4) MailBox Acceptance Mask Register
#define AT91C_CAN_MB4_MDL ((AT91_REG *) 	0xFFFAC294) // (CAN_MB4) MailBox Data Low Register
// ========== Register definition for CAN_MB5 peripheral ========== 
#define AT91C_CAN_MB5_MDH ((AT91_REG *) 	0xFFFAC2B8) // (CAN_MB5) MailBox Data High Register
#define AT91C_CAN_MB5_MID ((AT91_REG *) 	0xFFFAC2A8) // (CAN_MB5) MailBox ID Register
#define AT91C_CAN_MB5_MCR ((AT91_REG *) 	0xFFFAC2BC) // (CAN_MB5) MailBox Control Register
#define AT91C_CAN_MB5_MSR ((AT91_REG *) 	0xFFFAC2B0) // (CAN_MB5) MailBox Status Register
#define AT91C_CAN_MB5_MDL ((AT91_REG *) 	0xFFFAC2B4) // (CAN_MB5) MailBox Data Low Register
#define AT91C_CAN_MB5_MMR ((AT91_REG *) 	0xFFFAC2A0) // (CAN_MB5) MailBox Mode Register
#define AT91C_CAN_MB5_MAM ((AT91_REG *) 	0xFFFAC2A4) // (CAN_MB5) MailBox Acceptance Mask Register
#define AT91C_CAN_MB5_MFID ((AT91_REG *) 	0xFFFAC2AC) // (CAN_MB5) MailBox Family ID Register
// ========== Register definition for CAN_MB6 peripheral ========== 
#define AT91C_CAN_MB6_MSR ((AT91_REG *) 	0xFFFAC2D0) // (CAN_MB6) MailBox Status Register
#define AT91C_CAN_MB6_MMR ((AT91_REG *) 	0xFFFAC2C0) // (CAN_MB6) MailBox Mode Register
#define AT91C_CAN_MB6_MFID ((AT91_REG *) 	0xFFFAC2CC) // (CAN_MB6) MailBox Family ID Register
#define AT91C_CAN_MB6_MDL ((AT91_REG *) 	0xFFFAC2D4) // (CAN_MB6) MailBox Data Low Register
#define AT91C_CAN_MB6_MID ((AT91_REG *) 	0xFFFAC2C8) // (CAN_MB6) MailBox ID Register
#define AT91C_CAN_MB6_MCR ((AT91_REG *) 	0xFFFAC2DC) // (CAN_MB6) MailBox Control Register
#define AT91C_CAN_MB6_MAM ((AT91_REG *) 	0xFFFAC2C4) // (CAN_MB6) MailBox Acceptance Mask Register
#define AT91C_CAN_MB6_MDH ((AT91_REG *) 	0xFFFAC2D8) // (CAN_MB6) MailBox Data High Register
// ========== Register definition for CAN_MB7 peripheral ========== 
#define AT91C_CAN_MB7_MAM ((AT91_REG *) 	0xFFFAC2E4) // (CAN_MB7) MailBox Acceptance Mask Register
#define AT91C_CAN_MB7_MDH ((AT91_REG *) 	0xFFFAC2F8) // (CAN_MB7) MailBox Data High Register
#define AT91C_CAN_MB7_MID ((AT91_REG *) 	0xFFFAC2E8) // (CAN_MB7) MailBox ID Register
#define AT91C_CAN_MB7_MSR ((AT91_REG *) 	0xFFFAC2F0) // (CAN_MB7) MailBox Status Register
#define AT91C_CAN_MB7_MMR ((AT91_REG *) 	0xFFFAC2E0) // (CAN_MB7) MailBox Mode Register
#define AT91C_CAN_MB7_MCR ((AT91_REG *) 	0xFFFAC2FC) // (CAN_MB7) MailBox Control Register
#define AT91C_CAN_MB7_MFID ((AT91_REG *) 	0xFFFAC2EC) // (CAN_MB7) MailBox Family ID Register
#define AT91C_CAN_MB7_MDL ((AT91_REG *) 	0xFFFAC2F4) // (CAN_MB7) MailBox Data Low Register
// ========== Register definition for CAN_MB8 peripheral ========== 
#define AT91C_CAN_MB8_MDH ((AT91_REG *) 	0xFFFAC318) // (CAN_MB8) MailBox Data High Register
#define AT91C_CAN_MB8_MMR ((AT91_REG *) 	0xFFFAC300) // (CAN_MB8) MailBox Mode Register
#define AT91C_CAN_MB8_MCR ((AT91_REG *) 	0xFFFAC31C) // (CAN_MB8) MailBox Control Register
#define AT91C_CAN_MB8_MSR ((AT91_REG *) 	0xFFFAC310) // (CAN_MB8) MailBox Status Register
#define AT91C_CAN_MB8_MAM ((AT91_REG *) 	0xFFFAC304) // (CAN_MB8) MailBox Acceptance Mask Register
#define AT91C_CAN_MB8_MFID ((AT91_REG *) 	0xFFFAC30C) // (CAN_MB8) MailBox Family ID Register
#define AT91C_CAN_MB8_MID ((AT91_REG *) 	0xFFFAC308) // (CAN_MB8) MailBox ID Register
#define AT91C_CAN_MB8_MDL ((AT91_REG *) 	0xFFFAC314) // (CAN_MB8) MailBox Data Low Register
// ========== Register definition for CAN_MB9 peripheral ========== 
#define AT91C_CAN_MB9_MID ((AT91_REG *) 	0xFFFAC328) // (CAN_MB9) MailBox ID Register
#define AT91C_CAN_MB9_MMR ((AT91_REG *) 	0xFFFAC320) // (CAN_MB9) MailBox Mode Register
#define AT91C_CAN_MB9_MDH ((AT91_REG *) 	0xFFFAC338) // (CAN_MB9) MailBox Data High Register
#define AT91C_CAN_MB9_MSR ((AT91_REG *) 	0xFFFAC330) // (CAN_MB9) MailBox Status Register
#define AT91C_CAN_MB9_MAM ((AT91_REG *) 	0xFFFAC324) // (CAN_MB9) MailBox Acceptance Mask Register
#define AT91C_CAN_MB9_MDL ((AT91_REG *) 	0xFFFAC334) // (CAN_MB9) MailBox Data Low Register
#define AT91C_CAN_MB9_MFID ((AT91_REG *) 	0xFFFAC32C) // (CAN_MB9) MailBox Family ID Register
#define AT91C_CAN_MB9_MCR ((AT91_REG *) 	0xFFFAC33C) // (CAN_MB9) MailBox Control Register
// ========== Register definition for CAN_MB10 peripheral ========== 
#define AT91C_CAN_MB10_MCR ((AT91_REG *) 	0xFFFAC35C) // (CAN_MB10) MailBox Control Register
#define AT91C_CAN_MB10_MDH ((AT91_REG *) 	0xFFFAC358) // (CAN_MB10) MailBox Data High Register
#define AT91C_CAN_MB10_MAM ((AT91_REG *) 	0xFFFAC344) // (CAN_MB10) MailBox Acceptance Mask Register
#define AT91C_CAN_MB10_MID ((AT91_REG *) 	0xFFFAC348) // (CAN_MB10) MailBox ID Register
#define AT91C_CAN_MB10_MDL ((AT91_REG *) 	0xFFFAC354) // (CAN_MB10) MailBox Data Low Register
#define AT91C_CAN_MB10_MSR ((AT91_REG *) 	0xFFFAC350) // (CAN_MB10) MailBox Status Register
#define AT91C_CAN_MB10_MMR ((AT91_REG *) 	0xFFFAC340) // (CAN_MB10) MailBox Mode Register
#define AT91C_CAN_MB10_MFID ((AT91_REG *) 	0xFFFAC34C) // (CAN_MB10) MailBox Family ID Register
// ========== Register definition for CAN_MB11 peripheral ========== 
#define AT91C_CAN_MB11_MSR ((AT91_REG *) 	0xFFFAC370) // (CAN_MB11) MailBox Status Register
#define AT91C_CAN_MB11_MFID ((AT91_REG *) 	0xFFFAC36C) // (CAN_MB11) MailBox Family ID Register
#define AT91C_CAN_MB11_MDL ((AT91_REG *) 	0xFFFAC374) // (CAN_MB11) MailBox Data Low Register
#define AT91C_CAN_MB11_MDH ((AT91_REG *) 	0xFFFAC378) // (CAN_MB11) MailBox Data High Register
#define AT91C_CAN_MB11_MID ((AT91_REG *) 	0xFFFAC368) // (CAN_MB11) MailBox ID Register
#define AT91C_CAN_MB11_MCR ((AT91_REG *) 	0xFFFAC37C) // (CAN_MB11) MailBox Control Register
#define AT91C_CAN_MB11_MMR ((AT91_REG *) 	0xFFFAC360) // (CAN_MB11) MailBox Mode Register
#define AT91C_CAN_MB11_MAM ((AT91_REG *) 	0xFFFAC364) // (CAN_MB11) MailBox Acceptance Mask Register
// ========== Register definition for CAN_MB12 peripheral ========== 
#define AT91C_CAN_MB12_MAM ((AT91_REG *) 	0xFFFAC384) // (CAN_MB12) MailBox Acceptance Mask Register
#define AT91C_CAN_MB12_MDH ((AT91_REG *) 	0xFFFAC398) // (CAN_MB12) MailBox Data High Register
#define AT91C_CAN_MB12_MMR ((AT91_REG *) 	0xFFFAC380) // (CAN_MB12) MailBox Mode Register
#define AT91C_CAN_MB12_MSR ((AT91_REG *) 	0xFFFAC390) // (CAN_MB12) MailBox Status Register
#define AT91C_CAN_MB12_MFID ((AT91_REG *) 	0xFFFAC38C) // (CAN_MB12) MailBox Family ID Register
#define AT91C_CAN_MB12_MID ((AT91_REG *) 	0xFFFAC388) // (CAN_MB12) MailBox ID Register
#define AT91C_CAN_MB12_MCR ((AT91_REG *) 	0xFFFAC39C) // (CAN_MB12) MailBox Control Register
#define AT91C_CAN_MB12_MDL ((AT91_REG *) 	0xFFFAC394) // (CAN_MB12) MailBox Data Low Register
// ========== Register definition for CAN_MB13 peripheral ========== 
#define AT91C_CAN_MB13_MDH ((AT91_REG *) 	0xFFFAC3B8) // (CAN_MB13) MailBox Data High Register
#define AT91C_CAN_MB13_MFID ((AT91_REG *) 	0xFFFAC3AC) // (CAN_MB13) MailBox Family ID Register
#define AT91C_CAN_MB13_MSR ((AT91_REG *) 	0xFFFAC3B0) // (CAN_MB13) MailBox Status Register
#define AT91C_CAN_MB13_MID ((AT91_REG *) 	0xFFFAC3A8) // (CAN_MB13) MailBox ID Register
#define AT91C_CAN_MB13_MAM ((AT91_REG *) 	0xFFFAC3A4) // (CAN_MB13) MailBox Acceptance Mask Register
#define AT91C_CAN_MB13_MMR ((AT91_REG *) 	0xFFFAC3A0) // (CAN_MB13) MailBox Mode Register
#define AT91C_CAN_MB13_MCR ((AT91_REG *) 	0xFFFAC3BC) // (CAN_MB13) MailBox Control Register
#define AT91C_CAN_MB13_MDL ((AT91_REG *) 	0xFFFAC3B4) // (CAN_MB13) MailBox Data Low Register
// ========== Register definition for CAN_MB14 peripheral ========== 
#define AT91C_CAN_MB14_MDL ((AT91_REG *) 	0xFFFAC3D4) // (CAN_MB14) MailBox Data Low Register
#define AT91C_CAN_MB14_MMR ((AT91_REG *) 	0xFFFAC3C0) // (CAN_MB14) MailBox Mode Register
#define AT91C_CAN_MB14_MFID ((AT91_REG *) 	0xFFFAC3CC) // (CAN_MB14) MailBox Family ID Register
#define AT91C_CAN_MB14_MCR ((AT91_REG *) 	0xFFFAC3DC) // (CAN_MB14) MailBox Control Register
#define AT91C_CAN_MB14_MID ((AT91_REG *) 	0xFFFAC3C8) // (CAN_MB14) MailBox ID Register
#define AT91C_CAN_MB14_MDH ((AT91_REG *) 	0xFFFAC3D8) // (CAN_MB14) MailBox Data High Register
#define AT91C_CAN_MB14_MSR ((AT91_REG *) 	0xFFFAC3D0) // (CAN_MB14) MailBox Status Register
#define AT91C_CAN_MB14_MAM ((AT91_REG *) 	0xFFFAC3C4) // (CAN_MB14) MailBox Acceptance Mask Register
// ========== Register definition for CAN_MB15 peripheral ========== 
#define AT91C_CAN_MB15_MDL ((AT91_REG *) 	0xFFFAC3F4) // (CAN_MB15) MailBox Data Low Register
#define AT91C_CAN_MB15_MSR ((AT91_REG *) 	0xFFFAC3F0) // (CAN_MB15) MailBox Status Register
#define AT91C_CAN_MB15_MID ((AT91_REG *) 	0xFFFAC3E8) // (CAN_MB15) MailBox ID Register
#define AT91C_CAN_MB15_MAM ((AT91_REG *) 	0xFFFAC3E4) // (CAN_MB15) MailBox Acceptance Mask Register
#define AT91C_CAN_MB15_MCR ((AT91_REG *) 	0xFFFAC3FC) // (CAN_MB15) MailBox Control Register
#define AT91C_CAN_MB15_MFID ((AT91_REG *) 	0xFFFAC3EC) // (CAN_MB15) MailBox Family ID Register
#define AT91C_CAN_MB15_MMR ((AT91_REG *) 	0xFFFAC3E0) // (CAN_MB15) MailBox Mode Register
#define AT91C_CAN_MB15_MDH ((AT91_REG *) 	0xFFFAC3F8) // (CAN_MB15) MailBox Data High Register
// ========== Register definition for CAN peripheral ========== 
#define AT91C_CAN_ACR   ((AT91_REG *) 	0xFFFAC028) // (CAN) Abort Command Register
#define AT91C_CAN_BR    ((AT91_REG *) 	0xFFFAC014) // (CAN) Baudrate Register
#define AT91C_CAN_IDR   ((AT91_REG *) 	0xFFFAC008) // (CAN) Interrupt Disable Register
#define AT91C_CAN_TIMESTP ((AT91_REG *) 	0xFFFAC01C) // (CAN) Time Stamp Register
#define AT91C_CAN_SR    ((AT91_REG *) 	0xFFFAC010) // (CAN) Status Register
#define AT91C_CAN_IMR   ((AT91_REG *) 	0xFFFAC00C) // (CAN) Interrupt Mask Register
#define AT91C_CAN_TCR   ((AT91_REG *) 	0xFFFAC024) // (CAN) Transfer Command Register
#define AT91C_CAN_TIM   ((AT91_REG *) 	0xFFFAC018) // (CAN) Timer Register
#define AT91C_CAN_IER   ((AT91_REG *) 	0xFFFAC004) // (CAN) Interrupt Enable Register
#define AT91C_CAN_ECR   ((AT91_REG *) 	0xFFFAC020) // (CAN) Error Counter Register
#define AT91C_CAN_VR    ((AT91_REG *) 	0xFFFAC0FC) // (CAN) Version Register
#define AT91C_CAN_MR    ((AT91_REG *) 	0xFFFAC000) // (CAN) Mode Register
// ========== Register definition for PWMC_CH0 peripheral ========== 
#define AT91C_PWMC_CH0_CCNTR ((AT91_REG *) 	0xFFFB820C) // (PWMC_CH0) Channel Counter Register
#define AT91C_PWMC_CH0_CPRDR ((AT91_REG *) 	0xFFFB8208) // (PWMC_CH0) Channel Period Register
#define AT91C_PWMC_CH0_CUPDR ((AT91_REG *) 	0xFFFB8210) // (PWMC_CH0) Channel Update Register
#define AT91C_PWMC_CH0_CDTYR ((AT91_REG *) 	0xFFFB8204) // (PWMC_CH0) Channel Duty Cycle Register
#define AT91C_PWMC_CH0_CMR ((AT91_REG *) 	0xFFFB8200) // (PWMC_CH0) Channel Mode Register
#define AT91C_PWMC_CH0_Reserved ((AT91_REG *) 	0xFFFB8214) // (PWMC_CH0) Reserved
// ========== Register definition for PWMC_CH1 peripheral ========== 
#define AT91C_PWMC_CH1_CCNTR ((AT91_REG *) 	0xFFFB822C) // (PWMC_CH1) Channel Counter Register
#define AT91C_PWMC_CH1_CDTYR ((AT91_REG *) 	0xFFFB8224) // (PWMC_CH1) Channel Duty Cycle Register
#define AT91C_PWMC_CH1_CMR ((AT91_REG *) 	0xFFFB8220) // (PWMC_CH1) Channel Mode Register
#define AT91C_PWMC_CH1_CPRDR ((AT91_REG *) 	0xFFFB8228) // (PWMC_CH1) Channel Period Register
#define AT91C_PWMC_CH1_Reserved ((AT91_REG *) 	0xFFFB8234) // (PWMC_CH1) Reserved
#define AT91C_PWMC_CH1_CUPDR ((AT91_REG *) 	0xFFFB8230) // (PWMC_CH1) Channel Update Register
// ========== Register definition for PWMC_CH2 peripheral ========== 
#define AT91C_PWMC_CH2_CUPDR ((AT91_REG *) 	0xFFFB8250) // (PWMC_CH2) Channel Update Register
#define AT91C_PWMC_CH2_CMR ((AT91_REG *) 	0xFFFB8240) // (PWMC_CH2) Channel Mode Register
#define AT91C_PWMC_CH2_Reserved ((AT91_REG *) 	0xFFFB8254) // (PWMC_CH2) Reserved
#define AT91C_PWMC_CH2_CPRDR ((AT91_REG *) 	0xFFFB8248) // (PWMC_CH2) Channel Period Register
#define AT91C_PWMC_CH2_CDTYR ((AT91_REG *) 	0xFFFB8244) // (PWMC_CH2) Channel Duty Cycle Register
#define AT91C_PWMC_CH2_CCNTR ((AT91_REG *) 	0xFFFB824C) // (PWMC_CH2) Channel Counter Register
// ========== Register definition for PWMC_CH3 peripheral ========== 
#define AT91C_PWMC_CH3_CPRDR ((AT91_REG *) 	0xFFFB8268) // (PWMC_CH3) Channel Period Register
#define AT91C_PWMC_CH3_Reserved ((AT91_REG *) 	0xFFFB8274) // (PWMC_CH3) Reserved
#define AT91C_PWMC_CH3_CUPDR ((AT91_REG *) 	0xFFFB8270) // (PWMC_CH3) Channel Update Register
#define AT91C_PWMC_CH3_CDTYR ((AT91_REG *) 	0xFFFB8264) // (PWMC_CH3) Channel Duty Cycle Register
#define AT91C_PWMC_CH3_CCNTR ((AT91_REG *) 	0xFFFB826C) // (PWMC_CH3) Channel Counter Register
#define AT91C_PWMC_CH3_CMR ((AT91_REG *) 	0xFFFB8260) // (PWMC_CH3) Channel Mode Register
// ========== Register definition for PWMC peripheral ========== 
#define AT91C_PWMC_IDR  ((AT91_REG *) 	0xFFFB8014) // (PWMC) PWMC Interrupt Disable Register
#define AT91C_PWMC_MR   ((AT91_REG *) 	0xFFFB8000) // (PWMC) PWMC Mode Register
#define AT91C_PWMC_VR   ((AT91_REG *) 	0xFFFB80FC) // (PWMC) PWMC Version Register
#define AT91C_PWMC_IMR  ((AT91_REG *) 	0xFFFB8018) // (PWMC) PWMC Interrupt Mask Register
#define AT91C_PWMC_SR   ((AT91_REG *) 	0xFFFB800C) // (PWMC) PWMC Status Register
#define AT91C_PWMC_ISR  ((AT91_REG *) 	0xFFFB801C) // (PWMC) PWMC Interrupt Status Register
#define AT91C_PWMC_ENA  ((AT91_REG *) 	0xFFFB8004) // (PWMC) PWMC Enable Register
#define AT91C_PWMC_IER  ((AT91_REG *) 	0xFFFB8010) // (PWMC) PWMC Interrupt Enable Register
#define AT91C_PWMC_DIS  ((AT91_REG *) 	0xFFFB8008) // (PWMC) PWMC Disable Register
// ========== Register definition for MACB peripheral ========== 
#define AT91C_MACB_ALE  ((AT91_REG *) 	0xFFFBC054) // (MACB) Alignment Error Register
#define AT91C_MACB_RRE  ((AT91_REG *) 	0xFFFBC06C) // (MACB) Receive Ressource Error Register
#define AT91C_MACB_SA4H ((AT91_REG *) 	0xFFFBC0B4) // (MACB) Specific Address 4 Top, Last 2 bytes
#define AT91C_MACB_TPQ  ((AT91_REG *) 	0xFFFBC0BC) // (MACB) Transmit Pause Quantum Register
#define AT91C_MACB_RJA  ((AT91_REG *) 	0xFFFBC07C) // (MACB) Receive Jabbers Register
#define AT91C_MACB_SA2H ((AT91_REG *) 	0xFFFBC0A4) // (MACB) Specific Address 2 Top, Last 2 bytes
#define AT91C_MACB_TPF  ((AT91_REG *) 	0xFFFBC08C) // (MACB) Transmitted Pause Frames Register
#define AT91C_MACB_ROV  ((AT91_REG *) 	0xFFFBC070) // (MACB) Receive Overrun Errors Register
#define AT91C_MACB_SA4L ((AT91_REG *) 	0xFFFBC0B0) // (MACB) Specific Address 4 Bottom, First 4 bytes
#define AT91C_MACB_MAN  ((AT91_REG *) 	0xFFFBC034) // (MACB) PHY Maintenance Register
#define AT91C_MACB_TID  ((AT91_REG *) 	0xFFFBC0B8) // (MACB) Type ID Checking Register
#define AT91C_MACB_TBQP ((AT91_REG *) 	0xFFFBC01C) // (MACB) Transmit Buffer Queue Pointer
#define AT91C_MACB_SA3L ((AT91_REG *) 	0xFFFBC0A8) // (MACB) Specific Address 3 Bottom, First 4 bytes
#define AT91C_MACB_DTF  ((AT91_REG *) 	0xFFFBC058) // (MACB) Deferred Transmission Frame Register
#define AT91C_MACB_PTR  ((AT91_REG *) 	0xFFFBC038) // (MACB) Pause Time Register
#define AT91C_MACB_CSE  ((AT91_REG *) 	0xFFFBC068) // (MACB) Carrier Sense Error Register
#define AT91C_MACB_ECOL ((AT91_REG *) 	0xFFFBC060) // (MACB) Excessive Collision Register
#define AT91C_MACB_STE  ((AT91_REG *) 	0xFFFBC084) // (MACB) SQE Test Error Register
#define AT91C_MACB_MCF  ((AT91_REG *) 	0xFFFBC048) // (MACB) Multiple Collision Frame Register
#define AT91C_MACB_IER  ((AT91_REG *) 	0xFFFBC028) // (MACB) Interrupt Enable Register
#define AT91C_MACB_ELE  ((AT91_REG *) 	0xFFFBC078) // (MACB) Excessive Length Errors Register
#define AT91C_MACB_USRIO ((AT91_REG *) 	0xFFFBC0C0) // (MACB) USER Input/Output Register
#define AT91C_MACB_PFR  ((AT91_REG *) 	0xFFFBC03C) // (MACB) Pause Frames received Register
#define AT91C_MACB_FCSE ((AT91_REG *) 	0xFFFBC050) // (MACB) Frame Check Sequence Error Register
#define AT91C_MACB_SA1L ((AT91_REG *) 	0xFFFBC098) // (MACB) Specific Address 1 Bottom, First 4 bytes
#define AT91C_MACB_NCR  ((AT91_REG *) 	0xFFFBC000) // (MACB) Network Control Register
#define AT91C_MACB_HRT  ((AT91_REG *) 	0xFFFBC094) // (MACB) Hash Address Top[63:32]
#define AT91C_MACB_NCFGR ((AT91_REG *) 	0xFFFBC004) // (MACB) Network Configuration Register
#define AT91C_MACB_SCF  ((AT91_REG *) 	0xFFFBC044) // (MACB) Single Collision Frame Register
#define AT91C_MACB_LCOL ((AT91_REG *) 	0xFFFBC05C) // (MACB) Late Collision Register
#define AT91C_MACB_SA3H ((AT91_REG *) 	0xFFFBC0AC) // (MACB) Specific Address 3 Top, Last 2 bytes
#define AT91C_MACB_HRB  ((AT91_REG *) 	0xFFFBC090) // (MACB) Hash Address Bottom[31:0]
#define AT91C_MACB_ISR  ((AT91_REG *) 	0xFFFBC024) // (MACB) Interrupt Status Register
#define AT91C_MACB_IMR  ((AT91_REG *) 	0xFFFBC030) // (MACB) Interrupt Mask Register
#define AT91C_MACB_WOL  ((AT91_REG *) 	0xFFFBC0C4) // (MACB) Wake On LAN Register
#define AT91C_MACB_USF  ((AT91_REG *) 	0xFFFBC080) // (MACB) Undersize Frames Register
#define AT91C_MACB_TSR  ((AT91_REG *) 	0xFFFBC014) // (MACB) Transmit Status Register
#define AT91C_MACB_FRO  ((AT91_REG *) 	0xFFFBC04C) // (MACB) Frames Received OK Register
#define AT91C_MACB_IDR  ((AT91_REG *) 	0xFFFBC02C) // (MACB) Interrupt Disable Register
#define AT91C_MACB_SA1H ((AT91_REG *) 	0xFFFBC09C) // (MACB) Specific Address 1 Top, Last 2 bytes
#define AT91C_MACB_RLE  ((AT91_REG *) 	0xFFFBC088) // (MACB) Receive Length Field Mismatch Register
#define AT91C_MACB_TUND ((AT91_REG *) 	0xFFFBC064) // (MACB) Transmit Underrun Error Register
#define AT91C_MACB_RSR  ((AT91_REG *) 	0xFFFBC020) // (MACB) Receive Status Register
#define AT91C_MACB_SA2L ((AT91_REG *) 	0xFFFBC0A0) // (MACB) Specific Address 2 Bottom, First 4 bytes
#define AT91C_MACB_FTO  ((AT91_REG *) 	0xFFFBC040) // (MACB) Frames Transmitted OK Register
#define AT91C_MACB_RSE  ((AT91_REG *) 	0xFFFBC074) // (MACB) Receive Symbol Errors Register
#define AT91C_MACB_NSR  ((AT91_REG *) 	0xFFFBC008) // (MACB) Network Status Register
#define AT91C_MACB_RBQP ((AT91_REG *) 	0xFFFBC018) // (MACB) Receive Buffer Queue Pointer
#define AT91C_MACB_REV  ((AT91_REG *) 	0xFFFBC0FC) // (MACB) Revision Register
// ========== Register definition for LCDC peripheral ========== 
#define AT91C_LCDC_BA2  ((AT91_REG *) 	0x00700004) // (LCDC) DMA Base Address Register 2
#define AT91C_LCDC_DP3_4 ((AT91_REG *) 	0x00700830) // (LCDC) Dithering Pattern DP3_4 Register
#define AT91C_LCDC_FRMA2 ((AT91_REG *) 	0x00700014) // (LCDC) DMA Frame Address Register 2
#define AT91C_LCDC_TIM1 ((AT91_REG *) 	0x00700808) // (LCDC) LCD Timing Config 1 Register
#define AT91C_LCDC_FIFO ((AT91_REG *) 	0x00700814) // (LCDC) LCD FIFO Register
#define AT91C_LCDC_TIM2 ((AT91_REG *) 	0x0070080C) // (LCDC) LCD Timing Config 2 Register
#define AT91C_LCDC_DP5_7 ((AT91_REG *) 	0x0070082C) // (LCDC) Dithering Pattern DP5_7 Register
#define AT91C_LCDC_IER  ((AT91_REG *) 	0x00700848) // (LCDC) Interrupt Enable Register
#define AT91C_LCDC_FRMCFG ((AT91_REG *) 	0x00700018) // (LCDC) DMA Frame Configuration Register
#define AT91C_LCDC_FRMA1 ((AT91_REG *) 	0x00700010) // (LCDC) DMA Frame Address Register 1
#define AT91C_LCDC_DP3_5 ((AT91_REG *) 	0x00700824) // (LCDC) Dithering Pattern DP3_5 Register
#define AT91C_LCDC_PWRCON ((AT91_REG *) 	0x0070083C) // (LCDC) Power Control Register
#define AT91C_LCDC_IMR  ((AT91_REG *) 	0x00700850) // (LCDC) Interrupt Mask Register
#define AT91C_LCDC_LUT_ENTRY ((AT91_REG *) 	0x00700C00) // (LCDC) LUT Entries Register
#define AT91C_LCDC_IRR  ((AT91_REG *) 	0x00700864) // (LCDC) Interrupts Raw Status Register
#define AT91C_LCDC_FRMP2 ((AT91_REG *) 	0x0070000C) // (LCDC) DMA Frame Pointer Register 2
#define AT91C_LCDC_ICR  ((AT91_REG *) 	0x00700858) // (LCDC) Interrupt Clear Register
#define AT91C_LCDC_DP1_2 ((AT91_REG *) 	0x0070081C) // (LCDC) Dithering Pattern DP1_2 Register
#define AT91C_LCDC_DMACON ((AT91_REG *) 	0x0070001C) // (LCDC) DMA Control Register
#define AT91C_LCDC_LCDFRCFG ((AT91_REG *) 	0x00700810) // (LCDC) LCD Frame Config Register
#define AT91C_LCDC_DP2_3 ((AT91_REG *) 	0x00700828) // (LCDC) Dithering Pattern DP2_3 Register
#define AT91C_LCDC_DP6_7 ((AT91_REG *) 	0x00700838) // (LCDC) Dithering Pattern DP6_7 Register
#define AT91C_LCDC_LCDCON1 ((AT91_REG *) 	0x00700800) // (LCDC) LCD Control 1 Register
#define AT91C_LCDC_DMA2DCFG ((AT91_REG *) 	0x00700020) // (LCDC) DMA 2D addressing configuration
#define AT91C_LCDC_GPR  ((AT91_REG *) 	0x0070085C) // (LCDC) General Purpose Register
#define AT91C_LCDC_BA1  ((AT91_REG *) 	0x00700000) // (LCDC) DMA Base Address Register 1
#define AT91C_LCDC_CTRSTCON ((AT91_REG *) 	0x00700840) // (LCDC) Contrast Control Register
#define AT91C_LCDC_CTRSTVAL ((AT91_REG *) 	0x00700844) // (LCDC) Contrast Value Register
#define AT91C_LCDC_LCDCON2 ((AT91_REG *) 	0x00700804) // (LCDC) LCD Control 2 Register
#define AT91C_LCDC_IDR  ((AT91_REG *) 	0x0070084C) // (LCDC) Interrupt Disable Register
#define AT91C_LCDC_ISR  ((AT91_REG *) 	0x00700854) // (LCDC) Interrupt Enable Register
#define AT91C_LCDC_ITR  ((AT91_REG *) 	0x00700860) // (LCDC) Interrupts Test Register
#define AT91C_LCDC_DP4_7 ((AT91_REG *) 	0x00700820) // (LCDC) Dithering Pattern DP4_7 Register
#define AT91C_LCDC_MVAL ((AT91_REG *) 	0x00700818) // (LCDC) LCD Mode Toggle Rate Value Register
#define AT91C_LCDC_DP4_5 ((AT91_REG *) 	0x00700834) // (LCDC) Dithering Pattern DP4_5 Register
#define AT91C_LCDC_FRMP1 ((AT91_REG *) 	0x00700008) // (LCDC) DMA Frame Pointer Register 1
// ========== Register definition for DMA peripheral ========== 
#define AT91C_DMA_RAWSRCTRAN ((AT91_REG *) 	0x008002D0) // (DMA) Raw Status for IntSrcTran Interrupt
#define AT91C_DMA_SGR0  ((AT91_REG *) 	0x00800048) // (DMA) Source Gather Register for channel 0
#define AT91C_DMA_REQSRCREG ((AT91_REG *) 	0x00800368) // (DMA) Source Software Transaction Request Register
#define AT91C_DMA_STATUSERR ((AT91_REG *) 	0x00800308) // (DMA) Status for IntErr IInterrupt
#define AT91C_DMA_SAR1  ((AT91_REG *) 	0x00800058) // (DMA) Source Address Register for channel 1
#define AT91C_DMA_CLEARDSTTRAN ((AT91_REG *) 	0x00800350) // (DMA) Clear for IntDstTran IInterrupt
#define AT91C_DMA_STATUSSRCTRAN ((AT91_REG *) 	0x008002F8) // (DMA) Status for IntSrcTran Interrupt
#define AT91C_DMA_REQDSTREG ((AT91_REG *) 	0x00800370) // (DMA) Destination Software Transaction Request Register
#define AT91C_DMA_DSTATAR0 ((AT91_REG *) 	0x00800038) // (DMA) Destination Status Adress Register for channel 0
#define AT91C_DMA_LSTREQDSTREG ((AT91_REG *) 	0x00800390) // (DMA) Last Destination Software Transaction Request Register
#define AT91C_DMA_SGLREQDSTREG ((AT91_REG *) 	0x00800380) // (DMA) Single Destination Software Transaction Request Register
#define AT91C_DMA_CTL1h ((AT91_REG *) 	0x00800074) // (DMA) Control Register for channel 1 - high
#define AT91C_DMA_CLEARERR ((AT91_REG *) 	0x00800358) // (DMA) Clear for IntErr Interrupt
#define AT91C_DMA_DSR0  ((AT91_REG *) 	0x00800050) // (DMA) Destination Scatter Register for channel 0
#define AT91C_DMA_DMATESTREG ((AT91_REG *) 	0x008003B0) // (DMA) DW_ahb_dmac Test Register
#define AT91C_DMA_DSR1  ((AT91_REG *) 	0x008000A8) // (DMA) Destination Scatter Register for channel 1
#define AT91C_DMA_CTL0l ((AT91_REG *) 	0x00800018) // (DMA) Control Register for channel 0 - low
#define AT91C_DMA_STATUSBLOCK ((AT91_REG *) 	0x008002F0) // (DMA) Status for IntBlock Interrupt
#define AT91C_DMA_SAR0  ((AT91_REG *) 	0x00800000) // (DMA) Source Address Register for channel 0
#define AT91C_DMA_LLP0  ((AT91_REG *) 	0x00800010) // (DMA) Linked List Pointer Register for channel 0
#define AT91C_DMA_CTL1l ((AT91_REG *) 	0x00800070) // (DMA) Control Register for channel 1 - low
#define AT91C_DMA_SGR1  ((AT91_REG *) 	0x008000A0) // (DMA) Source Gather Register for channel 1
#define AT91C_DMA_CFG0l ((AT91_REG *) 	0x00800040) // (DMA) Configuration Register for channel 0 - low
#define AT91C_DMA_CFG0h ((AT91_REG *) 	0x00800044) // (DMA) Configuration Register for channel 0 - high
#define AT91C_DMA_STATUSTFR ((AT91_REG *) 	0x008002E8) // (DMA) Status for IntTfr Interrupt
#define AT91C_DMA_MASKBLOCK ((AT91_REG *) 	0x00800318) // (DMA) Mask for IntBlock Interrupt
#define AT91C_DMA_RAWBLOCK ((AT91_REG *) 	0x008002C8) // (DMA) Raw Status for IntBlock Interrupt
#define AT91C_DMA_CHENREG ((AT91_REG *) 	0x008003A0) // (DMA) DW_ahb_dmac Channel Enable Register
#define AT91C_DMA_DSTAT0 ((AT91_REG *) 	0x00800028) // (DMA) Destination Status Register for channel 0
#define AT91C_DMA_CLEARSRCTRAN ((AT91_REG *) 	0x00800348) // (DMA) Clear for IntSrcTran Interrupt
#define AT91C_DMA_DAR1  ((AT91_REG *) 	0x00800060) // (DMA) Destination Address Register for channel 1
#define AT91C_DMA_CLEARBLOCK ((AT91_REG *) 	0x00800340) // (DMA) Clear for IntBlock Interrupt
#define AT91C_DMA_CFG1h ((AT91_REG *) 	0x0080009C) // (DMA) Configuration Register for channel 1 - high
#define AT91C_DMA_DSTATAR1 ((AT91_REG *) 	0x00800090) // (DMA) Destination Status Adress Register for channel 1
#define AT91C_DMA_RAWERR ((AT91_REG *) 	0x008002E0) // (DMA) Raw Status for IntErr Interrupt
#define AT91C_DMA_CTL0h ((AT91_REG *) 	0x0080001C) // (DMA) Control Register for channel 0 - high
#define AT91C_DMA_SGLREQSRCREG ((AT91_REG *) 	0x00800378) // (DMA) Single Source Software Transaction Request Register
#define AT91C_DMA_LLP1  ((AT91_REG *) 	0x00800068) // (DMA) Linked List Pointer Register for channel 1
#define AT91C_DMA_MASKDSTTRAN ((AT91_REG *) 	0x00800328) // (DMA) Mask for IntDstTran Interrupt
#define AT91C_DMA_MASKSRCTRAN ((AT91_REG *) 	0x00800320) // (DMA) Mask for IntSrcTran Interrupt
#define AT91C_DMA_LSTREQSRCREG ((AT91_REG *) 	0x00800388) // (DMA) Last Source Software Transaction Request Register
#define AT91C_DMA_CLEARTFR ((AT91_REG *) 	0x00800338) // (DMA) Clear for IntTfr Interrupt
#define AT91C_DMA_SSTATAR1 ((AT91_REG *) 	0x00800088) // (DMA) Source Status Adress Register for channel 1
#define AT91C_DMA_DAR0  ((AT91_REG *) 	0x00800008) // (DMA) Destination Address Register for channel 0
#define AT91C_DMA_SSTAT0 ((AT91_REG *) 	0x00800020) // (DMA) Source Status Register for channel 0
#define AT91C_DMA_DMAIDREG ((AT91_REG *) 	0x008003A8) // (DMA) DW_ahb_dmac ID Register
#define AT91C_DMA_DSTAT1 ((AT91_REG *) 	0x00800080) // (DMA) Destination Status Register for channel 1
#define AT91C_DMA_RAWTFR ((AT91_REG *) 	0x008002C0) // (DMA) Raw Status for IntTfr Interrupt
#define AT91C_DMA_VERSIONID ((AT91_REG *) 	0x008003B8) // (DMA) DW_ahb_dmac Version ID Register
#define AT91C_DMA_STATUSDSTTRAN ((AT91_REG *) 	0x00800300) // (DMA) Status for IntDstTran IInterrupt
#define AT91C_DMA_MASKERR ((AT91_REG *) 	0x00800330) // (DMA) Mask for IntErr Interrupt
#define AT91C_DMA_SSTATAR0 ((AT91_REG *) 	0x00800030) // (DMA) Source Status Adress Register for channel 0
#define AT91C_DMA_MASKTFR ((AT91_REG *) 	0x00800310) // (DMA) Mask for IntTfr Interrupt
#define AT91C_DMA_SSTAT1 ((AT91_REG *) 	0x00800078) // (DMA) Source Status Register for channel 1
#define AT91C_DMA_STATUSINT ((AT91_REG *) 	0x00800360) // (DMA) Status for each Interrupt Type
#define AT91C_DMA_DMACFGREG ((AT91_REG *) 	0x00800398) // (DMA) DW_ahb_dmac Configuration Register
#define AT91C_DMA_RAWDSTTRAN ((AT91_REG *) 	0x008002D8) // (DMA) Raw Status for IntDstTran Interrupt
#define AT91C_DMA_CFG1l ((AT91_REG *) 	0x00800098) // (DMA) Configuration Register for channel 1 - low
// ========== Register definition for UDP peripheral ========== 
#define AT91C_UDP_FDR   ((AT91_REG *) 	0xFFF78050) // (UDP) Endpoint FIFO Data Register
#define AT91C_UDP_IER   ((AT91_REG *) 	0xFFF78010) // (UDP) Interrupt Enable Register
#define AT91C_UDP_CSR   ((AT91_REG *) 	0xFFF78030) // (UDP) Endpoint Control and Status Register
#define AT91C_UDP_RSTEP ((AT91_REG *) 	0xFFF78028) // (UDP) Reset Endpoint Register
#define AT91C_UDP_GLBSTATE ((AT91_REG *) 	0xFFF78004) // (UDP) Global State Register
#define AT91C_UDP_TXVC  ((AT91_REG *) 	0xFFF78074) // (UDP) Transceiver Control Register
#define AT91C_UDP_IDR   ((AT91_REG *) 	0xFFF78014) // (UDP) Interrupt Disable Register
#define AT91C_UDP_ISR   ((AT91_REG *) 	0xFFF7801C) // (UDP) Interrupt Status Register
#define AT91C_UDP_IMR   ((AT91_REG *) 	0xFFF78018) // (UDP) Interrupt Mask Register
#define AT91C_UDP_FADDR ((AT91_REG *) 	0xFFF78008) // (UDP) Function Address Register
#define AT91C_UDP_NUM   ((AT91_REG *) 	0xFFF78000) // (UDP) Frame Number Register
#define AT91C_UDP_ICR   ((AT91_REG *) 	0xFFF78020) // (UDP) Interrupt Clear Register
// ========== Register definition for UHP peripheral ========== 
#define AT91C_UHP_HcRhDescriptorA ((AT91_REG *) 	0x00A00048) // (UHP) Root Hub characteristics A
#define AT91C_UHP_HcInterruptStatus ((AT91_REG *) 	0x00A0000C) // (UHP) Interrupt Status Register
#define AT91C_UHP_HcLSThreshold ((AT91_REG *) 	0x00A00044) // (UHP) LS Threshold
#define AT91C_UHP_HcBulkDoneHead ((AT91_REG *) 	0x00A00030) // (UHP) Last completed transfer descriptor
#define AT91C_UHP_HcInterruptDisable ((AT91_REG *) 	0x00A00014) // (UHP) Interrupt Disable Register
#define AT91C_UHP_HcRhPortStatus ((AT91_REG *) 	0x00A00054) // (UHP) Root Hub Port Status Register
#define AT91C_UHP_HcControl ((AT91_REG *) 	0x00A00004) // (UHP) Operating modes for the Host Controller
#define AT91C_UHP_HcPeriodCurrentED ((AT91_REG *) 	0x00A0001C) // (UHP) Current Isochronous or Interrupt Endpoint Descriptor
#define AT91C_UHP_HcControlHeadED ((AT91_REG *) 	0x00A00020) // (UHP) First Endpoint Descriptor of the Control list
#define AT91C_UHP_HcCommandStatus ((AT91_REG *) 	0x00A00008) // (UHP) Command & status Register
#define AT91C_UHP_HcFmNumber ((AT91_REG *) 	0x00A0003C) // (UHP) Frame number
#define AT91C_UHP_HcRhDescriptorB ((AT91_REG *) 	0x00A0004C) // (UHP) Root Hub characteristics B
#define AT91C_UHP_HcBulkHeadED ((AT91_REG *) 	0x00A00028) // (UHP) First endpoint register of the Bulk list
#define AT91C_UHP_HcFmRemaining ((AT91_REG *) 	0x00A00038) // (UHP) Bit time remaining in the current Frame
#define AT91C_UHP_HcRevision ((AT91_REG *) 	0x00A00000) // (UHP) Revision
#define AT91C_UHP_HcInterruptEnable ((AT91_REG *) 	0x00A00010) // (UHP) Interrupt Enable Register
#define AT91C_UHP_HcControlCurrentED ((AT91_REG *) 	0x00A00024) // (UHP) Endpoint Control and Status Register
#define AT91C_UHP_HcBulkCurrentED ((AT91_REG *) 	0x00A0002C) // (UHP) Current endpoint of the Bulk list
#define AT91C_UHP_HcHCCA ((AT91_REG *) 	0x00A00018) // (UHP) Pointer to the Host Controller Communication Area
#define AT91C_UHP_HcPeriodicStart ((AT91_REG *) 	0x00A00040) // (UHP) Periodic Start
#define AT91C_UHP_HcRhStatus ((AT91_REG *) 	0x00A00050) // (UHP) Root Hub Status register
#define AT91C_UHP_HcFmInterval ((AT91_REG *) 	0x00A00034) // (UHP) Bit time between 2 consecutive SOFs
// ========== Register definition for TBOX peripheral ========== 
#define AT91C_TBOX_GPSSIGFILE ((AT91_REG *) 	0x70000BA0) // (TBOX) GPS RFIN/DRFIN driven from files/Samples_GPS.data
#define AT91C_TBOX_PIOA ((AT91_REG *) 	0x7000093C) // (TBOX) Value Of PIOA
#define AT91C_TBOX_PWM1 ((AT91_REG *) 	0x70000A08) // (TBOX) PWM1[4:0]=nb pulses on pb7, PWM1[9:5]=nb pulses on pc28, PWM1[20:16]=nb pulses on pb8, PWM1[25:21]=nb pulses on pc3
#define AT91C_TBOX_PIODENABLEFORCE ((AT91_REG *) 	0x7000092C) // (TBOX) If each bit is 1, the corresponding bit of PIOD is controlled by TBOX_PIODFORCEVALUE
#define AT91C_TBOX_PIODPUN ((AT91_REG *) 	0x7000090C) // (TBOX) Spy on PIO PUN inputs
#define AT91C_TBOX_PIOAENABLEFORCE ((AT91_REG *) 	0x70000914) // (TBOX) If each bit is 1, the corresponding bit of PIOA is controlled by TBOX_PIOAFORCEVALUE
#define AT91C_TBOX_PIOD ((AT91_REG *) 	0x70000948) // (TBOX) Value Of PIOD
#define AT91C_TBOX_STOPAPBSPY ((AT91_REG *) 	0x70000A1C) // (TBOX) When 1, no more APB SPY messages
#define AT91C_TBOX_PIOEENABLEFORCE ((AT91_REG *) 	0x70000934) // (TBOX) If each bit is 1, the corresponding bit of PIOE is controlled by TBOX_PIOEFORCEVALUE
#define AT91C_TBOX_PIOBPUN ((AT91_REG *) 	0x70000904) // (TBOX) Spy on PIO PUN inputs
#define AT91C_TBOX_USBDEV ((AT91_REG *) 	0x70000A14) // (TBOX) USB device testbench : bit 0 = flag0, bit 1 = flag1
#define AT91C_TBOX_GPSRAND ((AT91_REG *) 	0x70000B04) // (TBOX) GPS random data for correlator (Stimulus - Internal Node)
#define AT91C_TBOX_KBD  ((AT91_REG *) 	0x70000A18) // (TBOX) Keyboard testbench : bit 0 = keypressed; bits[7:6] = key column; bits[5:4] = key row;
#define AT91C_TBOX_PIOEFORCEVALUE ((AT91_REG *) 	0x70000938) // (TBOX) Value to force on PIOA when bits TBOX_PIOEENABLEFORCE are 1
#define AT91C_TBOX_AC97START ((AT91_REG *) 	0x70000A00) // (TBOX) Start of AC97 test: swith PIO mux to connect PIOs to audio codec model.
#define AT91C_TBOX_PIOAPUN ((AT91_REG *) 	0x70000900) // (TBOX) Spy on PIO PUN inputs
#define AT91C_TBOX_GPSACQSTATUS ((AT91_REG *) 	0x70000B08) // (TBOX) GPS acquisition status (Probe - Internal Node)
#define AT91C_TBOX_PIOEPUN ((AT91_REG *) 	0x70000910) // (TBOX) Spy on PIO PUN inputs
#define AT91C_TBOX_PIOE ((AT91_REG *) 	0x7000094C) // (TBOX) Value Of PIOE
#define AT91C_TBOX_PIODFORCEVALUE ((AT91_REG *) 	0x70000930) // (TBOX) Value to force on PIOA when bits TBOX_PIODENABLEFORCE are 1
#define AT91C_TBOX_PWMSTART ((AT91_REG *) 	0x70000A04) // (TBOX) Start of PWM test: Start to count edges on PWM IOs
#define AT91C_TBOX_GPSSIGIB ((AT91_REG *) 	0x70000BB0) // (TBOX) GPS DRFIN[5:4] aka SIGI_B (Stimulus)
#define AT91C_TBOX_GPSSYNCHRO ((AT91_REG *) 	0x70000B00) // (TBOX) GPS synchronization (Stimulus)
#define AT91C_TBOX_PIOAFORCEVALUE ((AT91_REG *) 	0x70000918) // (TBOX) Value to force on PIOA when bits TBOX_PIOAENABLEFORCE are 1
#define AT91C_TBOX_GPSACQDATA ((AT91_REG *) 	0x70000B0C) // (TBOX) GPS acquisition data (Probe - Internal Node)
#define AT91C_TBOX_SHMCTRL ((AT91_REG *) 	0x70000000) // (TBOX) SHM Probe Control: 0-> shm probe stopped, 1: shm probe started
#define AT91C_TBOX_MAC  ((AT91_REG *) 	0x70000A10) // (TBOX) MAC testbench : bit 0 = rxtrig, bit 1 = clkofftester, bit 2 = err_sig_loops
#define AT91C_TBOX_GPSSIGIA ((AT91_REG *) 	0x70000BA4) // (TBOX) GPS DRFIN[1:0] aka SIGI_A (Stimulus)
#define AT91C_TBOX_PIOBFORCEVALUE ((AT91_REG *) 	0x70000920) // (TBOX) Value to force on PIOA when bits TBOX_PIOBENABLEFORCE are 1
#define AT91C_TBOX_PIOCPUN ((AT91_REG *) 	0x70000908) // (TBOX) Spy on PIO PUN inputs
#define AT91C_TBOX_PIOCFORCEVALUE ((AT91_REG *) 	0x70000928) // (TBOX) Value to force on PIOA when bits TBOX_PIOCENABLEFORCE are 1
#define AT91C_TBOX_PIOC ((AT91_REG *) 	0x70000944) // (TBOX) Value Of PIOC
#define AT91C_TBOX_DMAEXTREQ ((AT91_REG *) 	0x70000810) // (TBOX) DMA External request lines 3 to 0
#define AT91C_TBOX_GPSDUMPRES ((AT91_REG *) 	0x70000BC0) // (TBOX) GPS Dump results and errors
#define AT91C_TBOX_PIOCENABLEFORCE ((AT91_REG *) 	0x70000924) // (TBOX) If each bit is 1, the corresponding bit of PIOC is controlled by TBOX_PIOCFORCEVALUE
#define AT91C_TBOX_PWM2 ((AT91_REG *) 	0x70000A0C) // (TBOX) PWM2[3:0]=nb pulses on pb27, PWM2[7:4]=nb pulses on pc29, PWM2[19:16]=nb pulses on pb29, PWM2[23:20]=nb pulses on pe10
#define AT91C_TBOX_GPSSIGQA ((AT91_REG *) 	0x70000BA8) // (TBOX) GPS DRFIN[3:2] aka SIGQ_A (Stimulus)
#define AT91C_TBOX_PIOB ((AT91_REG *) 	0x70000940) // (TBOX) Value Of PIOB
#define AT91C_TBOX_PIOBENABLEFORCE ((AT91_REG *) 	0x7000091C) // (TBOX) If each bit is 1, the corresponding bit of PIOB is controlled by TBOX_PIOBFORCEVALUE
#define AT91C_TBOX_GPSSIGQB ((AT91_REG *) 	0x70000BB4) // (TBOX) GPS DRFIN[7:6] aka SIGQ_B (Stimulus)
// ========== Register definition for HECC0 peripheral ========== 
#define AT91C_HECC0_SR  ((AT91_REG *) 	0xFFFFE008) // (HECC0)  ECC Status register
#define AT91C_HECC0_VR  ((AT91_REG *) 	0xFFFFE0FC) // (HECC0)  ECC Version register
#define AT91C_HECC0_CR  ((AT91_REG *) 	0xFFFFE000) // (HECC0)  ECC reset register
#define AT91C_HECC0_PR  ((AT91_REG *) 	0xFFFFE00C) // (HECC0)  ECC Parity register
#define AT91C_HECC0_MR  ((AT91_REG *) 	0xFFFFE004) // (HECC0)  ECC Page size register
#define AT91C_HECC0_NPR ((AT91_REG *) 	0xFFFFE010) // (HECC0)  ECC Parity N register
// ========== Register definition for HECC1 peripheral ========== 
#define AT91C_HECC1_MR  ((AT91_REG *) 	0xFFFFE604) // (HECC1)  ECC Page size register
#define AT91C_HECC1_VR  ((AT91_REG *) 	0xFFFFE6FC) // (HECC1)  ECC Version register
#define AT91C_HECC1_PR  ((AT91_REG *) 	0xFFFFE60C) // (HECC1)  ECC Parity register
#define AT91C_HECC1_CR  ((AT91_REG *) 	0xFFFFE600) // (HECC1)  ECC reset register
#define AT91C_HECC1_NPR ((AT91_REG *) 	0xFFFFE610) // (HECC1)  ECC Parity N register
#define AT91C_HECC1_SR  ((AT91_REG *) 	0xFFFFE608) // (HECC1)  ECC Status register
// ========== Register definition for HISI peripheral ========== 
#define AT91C_HISI_CDBA ((AT91_REG *) 	0xFFFC402C) // (HISI) Codec Dma Address Register
#define AT91C_HISI_PDECF ((AT91_REG *) 	0xFFFC4024) // (HISI) Preview Decimation Factor Register
#define AT91C_HISI_IMR  ((AT91_REG *) 	0xFFFC4014) // (HISI) Interrupt Mask Register
#define AT91C_HISI_IER  ((AT91_REG *) 	0xFFFC400C) // (HISI) Interrupt Enable Register
#define AT91C_HISI_SR   ((AT91_REG *) 	0xFFFC4008) // (HISI) Status Register
#define AT91C_HISI_Y2RSET0 ((AT91_REG *) 	0xFFFC4030) // (HISI) Color Space Conversion Register
#define AT91C_HISI_PFBD ((AT91_REG *) 	0xFFFC4028) // (HISI) Preview Frame Buffer Address Register
#define AT91C_HISI_PSIZE ((AT91_REG *) 	0xFFFC4020) // (HISI) Preview Size Register
#define AT91C_HISI_IDR  ((AT91_REG *) 	0xFFFC4010) // (HISI) Interrupt Disable Register
#define AT91C_HISI_R2YSET2 ((AT91_REG *) 	0xFFFC4040) // (HISI) Color Space Conversion Register
#define AT91C_HISI_R2YSET0 ((AT91_REG *) 	0xFFFC4038) // (HISI) Color Space Conversion Register
#define AT91C_HISI_CR1  ((AT91_REG *) 	0xFFFC4000) // (HISI) Control Register 1
#define AT91C_HISI_CR2  ((AT91_REG *) 	0xFFFC4004) // (HISI) Control Register 2
#define AT91C_HISI_Y2RSET1 ((AT91_REG *) 	0xFFFC4034) // (HISI) Color Space Conversion Register
#define AT91C_HISI_R2YSET1 ((AT91_REG *) 	0xFFFC403C) // (HISI) Color Space Conversion Register

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
#define AT91C_PIO_PA0        ((unsigned int) 1 <<  0) // Pin Controlled by PA0
#define AT91C_PA0_MCI0_DA0 ((unsigned int) AT91C_PIO_PA0) //  
#define AT91C_PA0_SPI0_MISO ((unsigned int) AT91C_PIO_PA0) //  
#define AT91C_PIO_PA1        ((unsigned int) 1 <<  1) // Pin Controlled by PA1
#define AT91C_PA1_MCI0_CDA ((unsigned int) AT91C_PIO_PA1) //  
#define AT91C_PA1_SPI0_MOSI ((unsigned int) AT91C_PIO_PA1) //  
#define AT91C_PIO_PA10       ((unsigned int) 1 << 10) // Pin Controlled by PA10
#define AT91C_PA10_MCI1_DA2 ((unsigned int) AT91C_PIO_PA10) //  
#define AT91C_PIO_PA11       ((unsigned int) 1 << 11) // Pin Controlled by PA11
#define AT91C_PA11_MCI1_DA3 ((unsigned int) AT91C_PIO_PA11) //  
#define AT91C_PIO_PA12       ((unsigned int) 1 << 12) // Pin Controlled by PA12
#define AT91C_PA12_MCI0_CK  ((unsigned int) AT91C_PIO_PA12) //  
#define AT91C_PIO_PA13       ((unsigned int) 1 << 13) // Pin Controlled by PA13
#define AT91C_PA13_CANTX    ((unsigned int) AT91C_PIO_PA13) //  
#define AT91C_PA13_PCK0     ((unsigned int) AT91C_PIO_PA13) //  
#define AT91C_PIO_PA14       ((unsigned int) 1 << 14) // Pin Controlled by PA14
#define AT91C_PA14_CANRX    ((unsigned int) AT91C_PIO_PA14) //  
#define AT91C_PA14_IRQ0     ((unsigned int) AT91C_PIO_PA14) //  
#define AT91C_PIO_PA15       ((unsigned int) 1 << 15) // Pin Controlled by PA15
#define AT91C_PA15_TCLK2    ((unsigned int) AT91C_PIO_PA15) //  
#define AT91C_PA15_IRQ1     ((unsigned int) AT91C_PIO_PA15) //  
#define AT91C_PIO_PA16       ((unsigned int) 1 << 16) // Pin Controlled by PA16
#define AT91C_PA16_MCI0_CDB ((unsigned int) AT91C_PIO_PA16) //  
#define AT91C_PA16_EBI1_D16 ((unsigned int) AT91C_PIO_PA16) //  
#define AT91C_PIO_PA17       ((unsigned int) 1 << 17) // Pin Controlled by PA17
#define AT91C_PA17_MCI0_DB0 ((unsigned int) AT91C_PIO_PA17) //  
#define AT91C_PA17_EBI1_D17 ((unsigned int) AT91C_PIO_PA17) //  
#define AT91C_PIO_PA18       ((unsigned int) 1 << 18) // Pin Controlled by PA18
#define AT91C_PA18_MCI0_DB1 ((unsigned int) AT91C_PIO_PA18) //  
#define AT91C_PA18_EBI1_D18 ((unsigned int) AT91C_PIO_PA18) //  
#define AT91C_PIO_PA19       ((unsigned int) 1 << 19) // Pin Controlled by PA19
#define AT91C_PA19_MCI0_DB2 ((unsigned int) AT91C_PIO_PA19) //  
#define AT91C_PA19_EBI1_D19 ((unsigned int) AT91C_PIO_PA19) //  
#define AT91C_PIO_PA2        ((unsigned int) 1 <<  2) // Pin Controlled by PA2
#define AT91C_PA2_UNCONNECTED_PA2_A ((unsigned int) AT91C_PIO_PA2) //  
#define AT91C_PA2_SPI0_SPCK ((unsigned int) AT91C_PIO_PA2) //  
#define AT91C_PIO_PA20       ((unsigned int) 1 << 20) // Pin Controlled by PA20
#define AT91C_PA20_MCI0_DB3 ((unsigned int) AT91C_PIO_PA20) //  
#define AT91C_PA20_EBI1_D20 ((unsigned int) AT91C_PIO_PA20) //  
#define AT91C_PIO_PA21       ((unsigned int) 1 << 21) // Pin Controlled by PA21
#define AT91C_PA21_MCI1_CDB ((unsigned int) AT91C_PIO_PA21) //  
#define AT91C_PA21_EBI1_D21 ((unsigned int) AT91C_PIO_PA21) //  
#define AT91C_PIO_PA22       ((unsigned int) 1 << 22) // Pin Controlled by PA22
#define AT91C_PA22_MCI1_DB0 ((unsigned int) AT91C_PIO_PA22) //  
#define AT91C_PA22_EBI1_D22 ((unsigned int) AT91C_PIO_PA22) //  
#define AT91C_PIO_PA23       ((unsigned int) 1 << 23) // Pin Controlled by PA23
#define AT91C_PA23_MCI1_DB1 ((unsigned int) AT91C_PIO_PA23) //  
#define AT91C_PA23_EBI1_D23 ((unsigned int) AT91C_PIO_PA23) //  
#define AT91C_PIO_PA24       ((unsigned int) 1 << 24) // Pin Controlled by PA24
#define AT91C_PA24_MCI1_DB2 ((unsigned int) AT91C_PIO_PA24) //  
#define AT91C_PA24_EBI1_D24 ((unsigned int) AT91C_PIO_PA24) //  
#define AT91C_PIO_PA25       ((unsigned int) 1 << 25) // Pin Controlled by PA25
#define AT91C_PA25_MCI1_DB3 ((unsigned int) AT91C_PIO_PA25) //  
#define AT91C_PA25_EBI1_D25 ((unsigned int) AT91C_PIO_PA25) //  
#define AT91C_PIO_PA26       ((unsigned int) 1 << 26) // Pin Controlled by PA26
#define AT91C_PA26_TXD0     ((unsigned int) AT91C_PIO_PA26) //  
#define AT91C_PA26_EBI1_D26 ((unsigned int) AT91C_PIO_PA26) //  
#define AT91C_PIO_PA27       ((unsigned int) 1 << 27) // Pin Controlled by PA27
#define AT91C_PA27_RXD0     ((unsigned int) AT91C_PIO_PA27) //  
#define AT91C_PA27_EBI1_D27 ((unsigned int) AT91C_PIO_PA27) //  
#define AT91C_PIO_PA28       ((unsigned int) 1 << 28) // Pin Controlled by PA28
#define AT91C_PA28_RTS0     ((unsigned int) AT91C_PIO_PA28) //  
#define AT91C_PA28_EBI1_D28 ((unsigned int) AT91C_PIO_PA28) //  
#define AT91C_PIO_PA29       ((unsigned int) 1 << 29) // Pin Controlled by PA29
#define AT91C_PA29_CTS0     ((unsigned int) AT91C_PIO_PA29) //  
#define AT91C_PA29_EBI1_D29 ((unsigned int) AT91C_PIO_PA29) //  
#define AT91C_PIO_PA3        ((unsigned int) 1 <<  3) // Pin Controlled by PA3
#define AT91C_PA3_MCI0_DA1 ((unsigned int) AT91C_PIO_PA3) //  
#define AT91C_PA3_SPI0_NPCS1 ((unsigned int) AT91C_PIO_PA3) //  
#define AT91C_PIO_PA30       ((unsigned int) 1 << 30) // Pin Controlled by PA30
#define AT91C_PA30_SCK0     ((unsigned int) AT91C_PIO_PA30) //  
#define AT91C_PA30_EBI1_D30 ((unsigned int) AT91C_PIO_PA30) //  
#define AT91C_PIO_PA31       ((unsigned int) 1 << 31) // Pin Controlled by PA31
#define AT91C_PA31_DMARQ0   ((unsigned int) AT91C_PIO_PA31) //  
#define AT91C_PA31_EBI1_D31 ((unsigned int) AT91C_PIO_PA31) //  
#define AT91C_PIO_PA4        ((unsigned int) 1 <<  4) // Pin Controlled by PA4
#define AT91C_PA4_MCI0_DA2 ((unsigned int) AT91C_PIO_PA4) //  
#define AT91C_PA4_SPI0_NPCS2A ((unsigned int) AT91C_PIO_PA4) //  
#define AT91C_PIO_PA5        ((unsigned int) 1 <<  5) // Pin Controlled by PA5
#define AT91C_PA5_MCI0_DA3 ((unsigned int) AT91C_PIO_PA5) //  
#define AT91C_PA5_SPI0_NPCS0 ((unsigned int) AT91C_PIO_PA5) //  
#define AT91C_PIO_PA6        ((unsigned int) 1 <<  6) // Pin Controlled by PA6
#define AT91C_PA6_MCI1_CK  ((unsigned int) AT91C_PIO_PA6) //  
#define AT91C_PA6_PCK2     ((unsigned int) AT91C_PIO_PA6) //  
#define AT91C_PIO_PA7        ((unsigned int) 1 <<  7) // Pin Controlled by PA7
#define AT91C_PA7_MCI1_CDA ((unsigned int) AT91C_PIO_PA7) //  
#define AT91C_PIO_PA8        ((unsigned int) 1 <<  8) // Pin Controlled by PA8
#define AT91C_PA8_MCI1_DA0 ((unsigned int) AT91C_PIO_PA8) //  
#define AT91C_PIO_PA9        ((unsigned int) 1 <<  9) // Pin Controlled by PA9
#define AT91C_PA9_MCI1_DA1 ((unsigned int) AT91C_PIO_PA9) //  
#define AT91C_PIO_PB0        ((unsigned int) 1 <<  0) // Pin Controlled by PB0
#define AT91C_PB0_AC97FS   ((unsigned int) AT91C_PIO_PB0) //  
#define AT91C_PB0_TF0      ((unsigned int) AT91C_PIO_PB0) //  
#define AT91C_PIO_PB1        ((unsigned int) 1 <<  1) // Pin Controlled by PB1
#define AT91C_PB1_AC97CK   ((unsigned int) AT91C_PIO_PB1) //  
#define AT91C_PB1_TK0      ((unsigned int) AT91C_PIO_PB1) //  
#define AT91C_PIO_PB10       ((unsigned int) 1 << 10) // Pin Controlled by PB10
#define AT91C_PB10_RK1      ((unsigned int) AT91C_PIO_PB10) //  
#define AT91C_PB10_PCK1     ((unsigned int) AT91C_PIO_PB10) //  
#define AT91C_PIO_PB11       ((unsigned int) 1 << 11) // Pin Controlled by PB11
#define AT91C_PB11_RF1      ((unsigned int) AT91C_PIO_PB11) //  
#define AT91C_PB11_SPI0_NPCS3B ((unsigned int) AT91C_PIO_PB11) //  
#define AT91C_PIO_PB12       ((unsigned int) 1 << 12) // Pin Controlled by PB12
#define AT91C_PB12_SPI1_MISO ((unsigned int) AT91C_PIO_PB12) //  
#define AT91C_PIO_PB13       ((unsigned int) 1 << 13) // Pin Controlled by PB13
#define AT91C_PB13_SPI1_MOSI ((unsigned int) AT91C_PIO_PB13) //  
#define AT91C_PIO_PB14       ((unsigned int) 1 << 14) // Pin Controlled by PB14
#define AT91C_PB14_SPI1_SPCK ((unsigned int) AT91C_PIO_PB14) //  
#define AT91C_PIO_PB15       ((unsigned int) 1 << 15) // Pin Controlled by PB15
#define AT91C_PB15_SPI1_NPCS0 ((unsigned int) AT91C_PIO_PB15) //  
#define AT91C_PIO_PB16       ((unsigned int) 1 << 16) // Pin Controlled by PB16
#define AT91C_PB16_SPI1_NPCS1 ((unsigned int) AT91C_PIO_PB16) //  
#define AT91C_PB16_PCK1     ((unsigned int) AT91C_PIO_PB16) //  
#define AT91C_PIO_PB17       ((unsigned int) 1 << 17) // Pin Controlled by PB17
#define AT91C_PB17_SPI1_NPCS2B ((unsigned int) AT91C_PIO_PB17) //  
#define AT91C_PB17_TIOA2    ((unsigned int) AT91C_PIO_PB17) //  
#define AT91C_PIO_PB18       ((unsigned int) 1 << 18) // Pin Controlled by PB18
#define AT91C_PB18_SPI1_NPCS3B ((unsigned int) AT91C_PIO_PB18) //  
#define AT91C_PB18_TIOB2    ((unsigned int) AT91C_PIO_PB18) //  
#define AT91C_PIO_PB19       ((unsigned int) 1 << 19) // Pin Controlled by PB19
#define AT91C_PIO_PB2        ((unsigned int) 1 <<  2) // Pin Controlled by PB2
#define AT91C_PB2_AC97TX   ((unsigned int) AT91C_PIO_PB2) //  
#define AT91C_PB2_TD0      ((unsigned int) AT91C_PIO_PB2) //  
#define AT91C_PIO_PB20       ((unsigned int) 1 << 20) // Pin Controlled by PB20
#define AT91C_PIO_PB21       ((unsigned int) 1 << 21) // Pin Controlled by PB21
#define AT91C_PIO_PB22       ((unsigned int) 1 << 22) // Pin Controlled by PB22
#define AT91C_PIO_PB23       ((unsigned int) 1 << 23) // Pin Controlled by PB23
#define AT91C_PIO_PB24       ((unsigned int) 1 << 24) // Pin Controlled by PB24
#define AT91C_PB24_UNCONNECTED_PB24_A ((unsigned int) AT91C_PIO_PB24) //  
#define AT91C_PB24_DMARQ3   ((unsigned int) AT91C_PIO_PB24) //  
#define AT91C_PIO_PB25       ((unsigned int) 1 << 25) // Pin Controlled by PB25
#define AT91C_PIO_PB26       ((unsigned int) 1 << 26) // Pin Controlled by PB26
#define AT91C_PIO_PB27       ((unsigned int) 1 << 27) // Pin Controlled by PB27
#define AT91C_PB27_UNCONNECTED_PB27_A ((unsigned int) AT91C_PIO_PB27) //  
#define AT91C_PB27_PWM2     ((unsigned int) AT91C_PIO_PB27) //  
#define AT91C_PIO_PB28       ((unsigned int) 1 << 28) // Pin Controlled by PB28
#define AT91C_PB28_UNCONNECTED_PB28_A ((unsigned int) AT91C_PIO_PB28) //  
#define AT91C_PB28_TCLK0    ((unsigned int) AT91C_PIO_PB28) //  
#define AT91C_PIO_PB29       ((unsigned int) 1 << 29) // Pin Controlled by PB29
#define AT91C_PB29_UNCONNECTED_PB29_A ((unsigned int) AT91C_PIO_PB29) //  
#define AT91C_PB29_PWM3     ((unsigned int) AT91C_PIO_PB29) //  
#define AT91C_PIO_PB3        ((unsigned int) 1 <<  3) // Pin Controlled by PB3
#define AT91C_PB3_AC97RX   ((unsigned int) AT91C_PIO_PB3) //  
#define AT91C_PB3_RD0      ((unsigned int) AT91C_PIO_PB3) //  
#define AT91C_PIO_PB30       ((unsigned int) 1 << 30) // Pin Controlled by PB30
#define AT91C_PIO_PB31       ((unsigned int) 1 << 31) // Pin Controlled by PB31
#define AT91C_PIO_PB4        ((unsigned int) 1 <<  4) // Pin Controlled by PB4
#define AT91C_PB4_TWD      ((unsigned int) AT91C_PIO_PB4) //  
#define AT91C_PB4_RK0      ((unsigned int) AT91C_PIO_PB4) //  
#define AT91C_PIO_PB5        ((unsigned int) 1 <<  5) // Pin Controlled by PB5
#define AT91C_PB5_TWCK     ((unsigned int) AT91C_PIO_PB5) //  
#define AT91C_PB5_RF0      ((unsigned int) AT91C_PIO_PB5) //  
#define AT91C_PIO_PB6        ((unsigned int) 1 <<  6) // Pin Controlled by PB6
#define AT91C_PB6_TF1      ((unsigned int) AT91C_PIO_PB6) //  
#define AT91C_PB6_DMARQ1   ((unsigned int) AT91C_PIO_PB6) //  
#define AT91C_PIO_PB7        ((unsigned int) 1 <<  7) // Pin Controlled by PB7
#define AT91C_PB7_TK1      ((unsigned int) AT91C_PIO_PB7) //  
#define AT91C_PB7_PWM0     ((unsigned int) AT91C_PIO_PB7) //  
#define AT91C_PIO_PB8        ((unsigned int) 1 <<  8) // Pin Controlled by PB8
#define AT91C_PB8_TD1      ((unsigned int) AT91C_PIO_PB8) //  
#define AT91C_PB8_PWM1     ((unsigned int) AT91C_PIO_PB8) //  
#define AT91C_PIO_PB9        ((unsigned int) 1 <<  9) // Pin Controlled by PB9
#define AT91C_PB9_RD1      ((unsigned int) AT91C_PIO_PB9) //  
#define AT91C_PB9_LCDCC    ((unsigned int) AT91C_PIO_PB9) //  
#define AT91C_PIO_PC0        ((unsigned int) 1 <<  0) // Pin Controlled by PC0
#define AT91C_PC0_LCDVSYNC ((unsigned int) AT91C_PIO_PC0) //  
#define AT91C_PIO_PC1        ((unsigned int) 1 <<  1) // Pin Controlled by PC1
#define AT91C_PC1_LCDHSYNC ((unsigned int) AT91C_PIO_PC1) //  
#define AT91C_PIO_PC10       ((unsigned int) 1 << 10) // Pin Controlled by PC10
#define AT91C_PC10_LCDD6    ((unsigned int) AT91C_PIO_PC10) //  
#define AT91C_PC10_LCDD11B  ((unsigned int) AT91C_PIO_PC10) //  
#define AT91C_PIO_PC11       ((unsigned int) 1 << 11) // Pin Controlled by PC11
#define AT91C_PC11_LCDD7    ((unsigned int) AT91C_PIO_PC11) //  
#define AT91C_PC11_LCDD12B  ((unsigned int) AT91C_PIO_PC11) //  
#define AT91C_PIO_PC12       ((unsigned int) 1 << 12) // Pin Controlled by PC12
#define AT91C_PC12_LCDD8    ((unsigned int) AT91C_PIO_PC12) //  
#define AT91C_PC12_LCDD13B  ((unsigned int) AT91C_PIO_PC12) //  
#define AT91C_PIO_PC13       ((unsigned int) 1 << 13) // Pin Controlled by PC13
#define AT91C_PC13_LCDD9    ((unsigned int) AT91C_PIO_PC13) //  
#define AT91C_PC13_LCDD14B  ((unsigned int) AT91C_PIO_PC13) //  
#define AT91C_PIO_PC14       ((unsigned int) 1 << 14) // Pin Controlled by PC14
#define AT91C_PC14_LCDD10   ((unsigned int) AT91C_PIO_PC14) //  
#define AT91C_PC14_LCDD15B  ((unsigned int) AT91C_PIO_PC14) //  
#define AT91C_PIO_PC15       ((unsigned int) 1 << 15) // Pin Controlled by PC15
#define AT91C_PC15_LCDD11   ((unsigned int) AT91C_PIO_PC15) //  
#define AT91C_PC15_LCDD19B  ((unsigned int) AT91C_PIO_PC15) //  
#define AT91C_PIO_PC16       ((unsigned int) 1 << 16) // Pin Controlled by PC16
#define AT91C_PC16_LCDD12   ((unsigned int) AT91C_PIO_PC16) //  
#define AT91C_PC16_LCDD20B  ((unsigned int) AT91C_PIO_PC16) //  
#define AT91C_PIO_PC17       ((unsigned int) 1 << 17) // Pin Controlled by PC17
#define AT91C_PC17_LCDD13   ((unsigned int) AT91C_PIO_PC17) //  
#define AT91C_PC17_LCDD21B  ((unsigned int) AT91C_PIO_PC17) //  
#define AT91C_PIO_PC18       ((unsigned int) 1 << 18) // Pin Controlled by PC18
#define AT91C_PC18_LCDD14   ((unsigned int) AT91C_PIO_PC18) //  
#define AT91C_PC18_LCDD22B  ((unsigned int) AT91C_PIO_PC18) //  
#define AT91C_PIO_PC19       ((unsigned int) 1 << 19) // Pin Controlled by PC19
#define AT91C_PC19_LCDD15   ((unsigned int) AT91C_PIO_PC19) //  
#define AT91C_PC19_LCDD23B  ((unsigned int) AT91C_PIO_PC19) //  
#define AT91C_PIO_PC2        ((unsigned int) 1 <<  2) // Pin Controlled by PC2
#define AT91C_PC2_LCDDOTCK ((unsigned int) AT91C_PIO_PC2) //  
#define AT91C_PIO_PC20       ((unsigned int) 1 << 20) // Pin Controlled by PC20
#define AT91C_PC20_LCDD16   ((unsigned int) AT91C_PIO_PC20) //  
#define AT91C_PC20_ETX2     ((unsigned int) AT91C_PIO_PC20) //  
#define AT91C_PIO_PC21       ((unsigned int) 1 << 21) // Pin Controlled by PC21
#define AT91C_PC21_LCDD17   ((unsigned int) AT91C_PIO_PC21) //  
#define AT91C_PC21_ETX3     ((unsigned int) AT91C_PIO_PC21) //  
#define AT91C_PIO_PC22       ((unsigned int) 1 << 22) // Pin Controlled by PC22
#define AT91C_PC22_LCDD18   ((unsigned int) AT91C_PIO_PC22) //  
#define AT91C_PC22_ERX2     ((unsigned int) AT91C_PIO_PC22) //  
#define AT91C_PIO_PC23       ((unsigned int) 1 << 23) // Pin Controlled by PC23
#define AT91C_PC23_LCDD19   ((unsigned int) AT91C_PIO_PC23) //  
#define AT91C_PC23_ERX3     ((unsigned int) AT91C_PIO_PC23) //  
#define AT91C_PIO_PC24       ((unsigned int) 1 << 24) // Pin Controlled by PC24
#define AT91C_PC24_LCDD20   ((unsigned int) AT91C_PIO_PC24) //  
#define AT91C_PC24_ETXER    ((unsigned int) AT91C_PIO_PC24) //  
#define AT91C_PIO_PC25       ((unsigned int) 1 << 25) // Pin Controlled by PC25
#define AT91C_PC25_LCDD21   ((unsigned int) AT91C_PIO_PC25) //  
#define AT91C_PC25_ERXDV    ((unsigned int) AT91C_PIO_PC25) //  
#define AT91C_PIO_PC26       ((unsigned int) 1 << 26) // Pin Controlled by PC26
#define AT91C_PC26_LCDD22   ((unsigned int) AT91C_PIO_PC26) //  
#define AT91C_PC26_ECOL     ((unsigned int) AT91C_PIO_PC26) //  
#define AT91C_PIO_PC27       ((unsigned int) 1 << 27) // Pin Controlled by PC27
#define AT91C_PC27_LCDD23   ((unsigned int) AT91C_PIO_PC27) //  
#define AT91C_PC27_ERXCK    ((unsigned int) AT91C_PIO_PC27) //  
#define AT91C_PIO_PC28       ((unsigned int) 1 << 28) // Pin Controlled by PC28
#define AT91C_PC28_PWM0     ((unsigned int) AT91C_PIO_PC28) //  
#define AT91C_PC28_TCLK1    ((unsigned int) AT91C_PIO_PC28) //  
#define AT91C_PIO_PC29       ((unsigned int) 1 << 29) // Pin Controlled by PC29
#define AT91C_PC29_PCK0     ((unsigned int) AT91C_PIO_PC29) //  
#define AT91C_PC29_PWM2     ((unsigned int) AT91C_PIO_PC29) //  
#define AT91C_PIO_PC3        ((unsigned int) 1 <<  3) // Pin Controlled by PC3
#define AT91C_PC3_LCDEN    ((unsigned int) AT91C_PIO_PC3) //  
#define AT91C_PC3_PWM1     ((unsigned int) AT91C_PIO_PC3) //  
#define AT91C_PIO_PC30       ((unsigned int) 1 << 30) // Pin Controlled by PC30
#define AT91C_PC30_DRXD     ((unsigned int) AT91C_PIO_PC30) //  
#define AT91C_PIO_PC31       ((unsigned int) 1 << 31) // Pin Controlled by PC31
#define AT91C_PC31_DTXD     ((unsigned int) AT91C_PIO_PC31) //  
#define AT91C_PIO_PC4        ((unsigned int) 1 <<  4) // Pin Controlled by PC4
#define AT91C_PC4_LCDD0    ((unsigned int) AT91C_PIO_PC4) //  
#define AT91C_PC4_LCDD3B   ((unsigned int) AT91C_PIO_PC4) //  
#define AT91C_PIO_PC5        ((unsigned int) 1 <<  5) // Pin Controlled by PC5
#define AT91C_PC5_LCDD1    ((unsigned int) AT91C_PIO_PC5) //  
#define AT91C_PC5_LCDD4B   ((unsigned int) AT91C_PIO_PC5) //  
#define AT91C_PIO_PC6        ((unsigned int) 1 <<  6) // Pin Controlled by PC6
#define AT91C_PC6_LCDD2    ((unsigned int) AT91C_PIO_PC6) //  
#define AT91C_PC6_LCDD5B   ((unsigned int) AT91C_PIO_PC6) //  
#define AT91C_PIO_PC7        ((unsigned int) 1 <<  7) // Pin Controlled by PC7
#define AT91C_PC7_LCDD3    ((unsigned int) AT91C_PIO_PC7) //  
#define AT91C_PC7_LCDD6B   ((unsigned int) AT91C_PIO_PC7) //  
#define AT91C_PIO_PC8        ((unsigned int) 1 <<  8) // Pin Controlled by PC8
#define AT91C_PC8_LCDD4    ((unsigned int) AT91C_PIO_PC8) //  
#define AT91C_PC8_LCDD7B   ((unsigned int) AT91C_PIO_PC8) //  
#define AT91C_PIO_PC9        ((unsigned int) 1 <<  9) // Pin Controlled by PC9
#define AT91C_PC9_LCDD5    ((unsigned int) AT91C_PIO_PC9) //  
#define AT91C_PC9_LCDD10B  ((unsigned int) AT91C_PIO_PC9) //  
#define AT91C_PIO_PD0        ((unsigned int) 1 <<  0) // Pin Controlled by PD0
#define AT91C_PD0_TXD1     ((unsigned int) AT91C_PIO_PD0) //  
#define AT91C_PD0_SPI0_NPCS2D ((unsigned int) AT91C_PIO_PD0) //  
#define AT91C_PIO_PD1        ((unsigned int) 1 <<  1) // Pin Controlled by PD1
#define AT91C_PD1_RXD1     ((unsigned int) AT91C_PIO_PD1) //  
#define AT91C_PD1_SPI0_NPCS3D ((unsigned int) AT91C_PIO_PD1) //  
#define AT91C_PIO_PD10       ((unsigned int) 1 << 10) // Pin Controlled by PD10
#define AT91C_PD10_UNCONNECTED_PD10_A ((unsigned int) AT91C_PIO_PD10) //  
#define AT91C_PD10_SCK1     ((unsigned int) AT91C_PIO_PD10) //  
#define AT91C_PIO_PD11       ((unsigned int) 1 << 11) // Pin Controlled by PD11
#define AT91C_PD11_EBI0_NCS2 ((unsigned int) AT91C_PIO_PD11) //  
#define AT91C_PD11_TSYNC    ((unsigned int) AT91C_PIO_PD11) //  
#define AT91C_PIO_PD12       ((unsigned int) 1 << 12) // Pin Controlled by PD12
#define AT91C_PD12_EBI0_A23 ((unsigned int) AT91C_PIO_PD12) //  
#define AT91C_PD12_TCLK     ((unsigned int) AT91C_PIO_PD12) //  
#define AT91C_PIO_PD13       ((unsigned int) 1 << 13) // Pin Controlled by PD13
#define AT91C_PD13_EBI0_A24 ((unsigned int) AT91C_PIO_PD13) //  
#define AT91C_PD13_TPS0     ((unsigned int) AT91C_PIO_PD13) //  
#define AT91C_PIO_PD14       ((unsigned int) 1 << 14) // Pin Controlled by PD14
#define AT91C_PD14_EBI0_A25_CFNRW ((unsigned int) AT91C_PIO_PD14) //  
#define AT91C_PD14_TPS1     ((unsigned int) AT91C_PIO_PD14) //  
#define AT91C_PIO_PD15       ((unsigned int) 1 << 15) // Pin Controlled by PD15
#define AT91C_PD15_EBI0_NCS3_NANDCS ((unsigned int) AT91C_PIO_PD15) //  
#define AT91C_PD15_TPS2     ((unsigned int) AT91C_PIO_PD15) //  
#define AT91C_PIO_PD16       ((unsigned int) 1 << 16) // Pin Controlled by PD16
#define AT91C_PD16_EBI0_D16 ((unsigned int) AT91C_PIO_PD16) //  
#define AT91C_PD16_TPK0     ((unsigned int) AT91C_PIO_PD16) //  
#define AT91C_PIO_PD17       ((unsigned int) 1 << 17) // Pin Controlled by PD17
#define AT91C_PD17_EBI0_D17 ((unsigned int) AT91C_PIO_PD17) //  
#define AT91C_PD17_TPK1     ((unsigned int) AT91C_PIO_PD17) //  
#define AT91C_PIO_PD18       ((unsigned int) 1 << 18) // Pin Controlled by PD18
#define AT91C_PD18_EBI0_D18 ((unsigned int) AT91C_PIO_PD18) //  
#define AT91C_PD18_TPK2     ((unsigned int) AT91C_PIO_PD18) //  
#define AT91C_PIO_PD19       ((unsigned int) 1 << 19) // Pin Controlled by PD19
#define AT91C_PD19_EBI0_D19 ((unsigned int) AT91C_PIO_PD19) //  
#define AT91C_PD19_TPK3     ((unsigned int) AT91C_PIO_PD19) //  
#define AT91C_PIO_PD2        ((unsigned int) 1 <<  2) // Pin Controlled by PD2
#define AT91C_PD2_TXD2     ((unsigned int) AT91C_PIO_PD2) //  
#define AT91C_PD2_SPI1_NPCS2D ((unsigned int) AT91C_PIO_PD2) //  
#define AT91C_PIO_PD20       ((unsigned int) 1 << 20) // Pin Controlled by PD20
#define AT91C_PD20_EBI0_D20 ((unsigned int) AT91C_PIO_PD20) //  
#define AT91C_PD20_TPK4     ((unsigned int) AT91C_PIO_PD20) //  
#define AT91C_PIO_PD21       ((unsigned int) 1 << 21) // Pin Controlled by PD21
#define AT91C_PD21_EBI0_D21 ((unsigned int) AT91C_PIO_PD21) //  
#define AT91C_PD21_TPK5     ((unsigned int) AT91C_PIO_PD21) //  
#define AT91C_PIO_PD22       ((unsigned int) 1 << 22) // Pin Controlled by PD22
#define AT91C_PD22_EBI0_D22 ((unsigned int) AT91C_PIO_PD22) //  
#define AT91C_PD22_TPK6     ((unsigned int) AT91C_PIO_PD22) //  
#define AT91C_PIO_PD23       ((unsigned int) 1 << 23) // Pin Controlled by PD23
#define AT91C_PD23_EBI0_D23 ((unsigned int) AT91C_PIO_PD23) //  
#define AT91C_PD23_TPK7     ((unsigned int) AT91C_PIO_PD23) //  
#define AT91C_PIO_PD24       ((unsigned int) 1 << 24) // Pin Controlled by PD24
#define AT91C_PD24_EBI0_D24 ((unsigned int) AT91C_PIO_PD24) //  
#define AT91C_PD24_TPK8     ((unsigned int) AT91C_PIO_PD24) //  
#define AT91C_PIO_PD25       ((unsigned int) 1 << 25) // Pin Controlled by PD25
#define AT91C_PD25_EBI0_D25 ((unsigned int) AT91C_PIO_PD25) //  
#define AT91C_PD25_TPK9     ((unsigned int) AT91C_PIO_PD25) //  
#define AT91C_PIO_PD26       ((unsigned int) 1 << 26) // Pin Controlled by PD26
#define AT91C_PD26_EBI0_D26 ((unsigned int) AT91C_PIO_PD26) //  
#define AT91C_PD26_TPK10    ((unsigned int) AT91C_PIO_PD26) //  
#define AT91C_PIO_PD27       ((unsigned int) 1 << 27) // Pin Controlled by PD27
#define AT91C_PD27_EBI0_D27 ((unsigned int) AT91C_PIO_PD27) //  
#define AT91C_PD27_TPK11    ((unsigned int) AT91C_PIO_PD27) //  
#define AT91C_PIO_PD28       ((unsigned int) 1 << 28) // Pin Controlled by PD28
#define AT91C_PD28_EBI0_D28 ((unsigned int) AT91C_PIO_PD28) //  
#define AT91C_PD28_TPK12    ((unsigned int) AT91C_PIO_PD28) //  
#define AT91C_PIO_PD29       ((unsigned int) 1 << 29) // Pin Controlled by PD29
#define AT91C_PD29_EBI0_D29 ((unsigned int) AT91C_PIO_PD29) //  
#define AT91C_PD29_TPK13    ((unsigned int) AT91C_PIO_PD29) //  
#define AT91C_PIO_PD3        ((unsigned int) 1 <<  3) // Pin Controlled by PD3
#define AT91C_PD3_RXD2     ((unsigned int) AT91C_PIO_PD3) //  
#define AT91C_PD3_SPI1_NPCS3D ((unsigned int) AT91C_PIO_PD3) //  
#define AT91C_PIO_PD30       ((unsigned int) 1 << 30) // Pin Controlled by PD30
#define AT91C_PD30_EBI0_D30 ((unsigned int) AT91C_PIO_PD30) //  
#define AT91C_PD30_TPK14    ((unsigned int) AT91C_PIO_PD30) //  
#define AT91C_PIO_PD31       ((unsigned int) 1 << 31) // Pin Controlled by PD31
#define AT91C_PD31_EBI0_D31 ((unsigned int) AT91C_PIO_PD31) //  
#define AT91C_PD31_TPK15    ((unsigned int) AT91C_PIO_PD31) //  
#define AT91C_PIO_PD4        ((unsigned int) 1 <<  4) // Pin Controlled by PD4
#define AT91C_PD4_FIQ      ((unsigned int) AT91C_PIO_PD4) //  
#define AT91C_PD4_DMARQ2   ((unsigned int) AT91C_PIO_PD4) //  
#define AT91C_PIO_PD5        ((unsigned int) 1 <<  5) // Pin Controlled by PD5
#define AT91C_PD5_EBI0_NWAIT ((unsigned int) AT91C_PIO_PD5) //  
#define AT91C_PD5_RTS2     ((unsigned int) AT91C_PIO_PD5) //  
#define AT91C_PIO_PD6        ((unsigned int) 1 <<  6) // Pin Controlled by PD6
#define AT91C_PD6_EBI0_NCS4_CFCS0 ((unsigned int) AT91C_PIO_PD6) //  
#define AT91C_PD6_CTS2     ((unsigned int) AT91C_PIO_PD6) //  
#define AT91C_PIO_PD7        ((unsigned int) 1 <<  7) // Pin Controlled by PD7
#define AT91C_PD7_EBI0_NCS5_CFCS1 ((unsigned int) AT91C_PIO_PD7) //  
#define AT91C_PD7_RTS1     ((unsigned int) AT91C_PIO_PD7) //  
#define AT91C_PIO_PD8        ((unsigned int) 1 <<  8) // Pin Controlled by PD8
#define AT91C_PD8_EBI0_CFCE1 ((unsigned int) AT91C_PIO_PD8) //  
#define AT91C_PD8_CTS1     ((unsigned int) AT91C_PIO_PD8) //  
#define AT91C_PIO_PD9        ((unsigned int) 1 <<  9) // Pin Controlled by PD9
#define AT91C_PD9_EBI0_CFCE2 ((unsigned int) AT91C_PIO_PD9) //  
#define AT91C_PD9_SCK2     ((unsigned int) AT91C_PIO_PD9) //  
#define AT91C_PIO_PE0        ((unsigned int) 1 <<  0) // Pin Controlled by PE0
#define AT91C_PE0_ISI_D0   ((unsigned int) AT91C_PIO_PE0) //  
#define AT91C_PIO_PE1        ((unsigned int) 1 <<  1) // Pin Controlled by PE1
#define AT91C_PE1_ISI_D1   ((unsigned int) AT91C_PIO_PE1) //  
#define AT91C_PIO_PE10       ((unsigned int) 1 << 10) // Pin Controlled by PE10
#define AT91C_PE10_ISI_VSYNC ((unsigned int) AT91C_PIO_PE10) //  
#define AT91C_PE10_PWM3     ((unsigned int) AT91C_PIO_PE10) //  
#define AT91C_PIO_PE11       ((unsigned int) 1 << 11) // Pin Controlled by PE11
#define AT91C_PE11_ISI_MCK  ((unsigned int) AT91C_PIO_PE11) //  
#define AT91C_PE11_PCK3     ((unsigned int) AT91C_PIO_PE11) //  
#define AT91C_PIO_PE12       ((unsigned int) 1 << 12) // Pin Controlled by PE12
#define AT91C_PE12_KBDR0    ((unsigned int) AT91C_PIO_PE12) //  
#define AT91C_PE12_ISI_D8   ((unsigned int) AT91C_PIO_PE12) //  
#define AT91C_PIO_PE13       ((unsigned int) 1 << 13) // Pin Controlled by PE13
#define AT91C_PE13_KBDR1    ((unsigned int) AT91C_PIO_PE13) //  
#define AT91C_PE13_ISI_D9   ((unsigned int) AT91C_PIO_PE13) //  
#define AT91C_PIO_PE14       ((unsigned int) 1 << 14) // Pin Controlled by PE14
#define AT91C_PE14_KBDR2    ((unsigned int) AT91C_PIO_PE14) //  
#define AT91C_PE14_ISI_D10  ((unsigned int) AT91C_PIO_PE14) //  
#define AT91C_PIO_PE15       ((unsigned int) 1 << 15) // Pin Controlled by PE15
#define AT91C_PE15_KBDR3    ((unsigned int) AT91C_PIO_PE15) //  
#define AT91C_PE15_ISI_D11  ((unsigned int) AT91C_PIO_PE15) //  
#define AT91C_PIO_PE16       ((unsigned int) 1 << 16) // Pin Controlled by PE16
#define AT91C_PE16_KBDR4    ((unsigned int) AT91C_PIO_PE16) //  
#define AT91C_PIO_PE17       ((unsigned int) 1 << 17) // Pin Controlled by PE17
#define AT91C_PE17_KBDC0    ((unsigned int) AT91C_PIO_PE17) //  
#define AT91C_PIO_PE18       ((unsigned int) 1 << 18) // Pin Controlled by PE18
#define AT91C_PE18_KBDC1    ((unsigned int) AT91C_PIO_PE18) //  
#define AT91C_PE18_TIOA0    ((unsigned int) AT91C_PIO_PE18) //  
#define AT91C_PIO_PE19       ((unsigned int) 1 << 19) // Pin Controlled by PE19
#define AT91C_PE19_KBDC2    ((unsigned int) AT91C_PIO_PE19) //  
#define AT91C_PE19_TIOB0    ((unsigned int) AT91C_PIO_PE19) //  
#define AT91C_PIO_PE2        ((unsigned int) 1 <<  2) // Pin Controlled by PE2
#define AT91C_PE2_ISI_D2   ((unsigned int) AT91C_PIO_PE2) //  
#define AT91C_PIO_PE20       ((unsigned int) 1 << 20) // Pin Controlled by PE20
#define AT91C_PE20_KBDC3    ((unsigned int) AT91C_PIO_PE20) //  
#define AT91C_PE20_EBI1_NWAIT ((unsigned int) AT91C_PIO_PE20) //  
#define AT91C_PIO_PE21       ((unsigned int) 1 << 21) // Pin Controlled by PE21
#define AT91C_PE21_ETXCK    ((unsigned int) AT91C_PIO_PE21) //  
#define AT91C_PE21_EBI1_NANDWE ((unsigned int) AT91C_PIO_PE21) //  
#define AT91C_PIO_PE22       ((unsigned int) 1 << 22) // Pin Controlled by PE22
#define AT91C_PE22_ECRS     ((unsigned int) AT91C_PIO_PE22) //  
#define AT91C_PE22_EBI1_NCS2_NANDCS ((unsigned int) AT91C_PIO_PE22) //  
#define AT91C_PIO_PE23       ((unsigned int) 1 << 23) // Pin Controlled by PE23
#define AT91C_PE23_ETX0     ((unsigned int) AT91C_PIO_PE23) //  
#define AT91C_PE23_EBI1_NANDOE ((unsigned int) AT91C_PIO_PE23) //  
#define AT91C_PIO_PE24       ((unsigned int) 1 << 24) // Pin Controlled by PE24
#define AT91C_PE24_ETX1     ((unsigned int) AT91C_PIO_PE24) //  
#define AT91C_PE24_EBI1_NWR3_NBS3 ((unsigned int) AT91C_PIO_PE24) //  
#define AT91C_PIO_PE25       ((unsigned int) 1 << 25) // Pin Controlled by PE25
#define AT91C_PE25_ERX0     ((unsigned int) AT91C_PIO_PE25) //  
#define AT91C_PE25_EBI1_NCS1_SDCS ((unsigned int) AT91C_PIO_PE25) //  
#define AT91C_PIO_PE26       ((unsigned int) 1 << 26) // Pin Controlled by PE26
#define AT91C_PE26_ERX1     ((unsigned int) AT91C_PIO_PE26) //  
#define AT91C_PIO_PE27       ((unsigned int) 1 << 27) // Pin Controlled by PE27
#define AT91C_PE27_ERXER    ((unsigned int) AT91C_PIO_PE27) //  
#define AT91C_PE27_EBI1_SDCKE ((unsigned int) AT91C_PIO_PE27) //  
#define AT91C_PIO_PE28       ((unsigned int) 1 << 28) // Pin Controlled by PE28
#define AT91C_PE28_ETXEN    ((unsigned int) AT91C_PIO_PE28) //  
#define AT91C_PE28_EBI1_RAS ((unsigned int) AT91C_PIO_PE28) //  
#define AT91C_PIO_PE29       ((unsigned int) 1 << 29) // Pin Controlled by PE29
#define AT91C_PE29_EMDC     ((unsigned int) AT91C_PIO_PE29) //  
#define AT91C_PE29_EBI1_CAS ((unsigned int) AT91C_PIO_PE29) //  
#define AT91C_PIO_PE3        ((unsigned int) 1 <<  3) // Pin Controlled by PE3
#define AT91C_PE3_ISI_D3   ((unsigned int) AT91C_PIO_PE3) //  
#define AT91C_PIO_PE30       ((unsigned int) 1 << 30) // Pin Controlled by PE30
#define AT91C_PE30_EMDIO    ((unsigned int) AT91C_PIO_PE30) //  
#define AT91C_PE30_EBI1_SDWE ((unsigned int) AT91C_PIO_PE30) //  
#define AT91C_PIO_PE31       ((unsigned int) 1 << 31) // Pin Controlled by PE31
#define AT91C_PE31_EF100    ((unsigned int) AT91C_PIO_PE31) //  
#define AT91C_PE31_EBI1_SDA10 ((unsigned int) AT91C_PIO_PE31) //  
#define AT91C_PIO_PE4        ((unsigned int) 1 <<  4) // Pin Controlled by PE4
#define AT91C_PE4_ISI_D4   ((unsigned int) AT91C_PIO_PE4) //  
#define AT91C_PIO_PE5        ((unsigned int) 1 <<  5) // Pin Controlled by PE5
#define AT91C_PE5_ISI_D5   ((unsigned int) AT91C_PIO_PE5) //  
#define AT91C_PIO_PE6        ((unsigned int) 1 <<  6) // Pin Controlled by PE6
#define AT91C_PE6_ISI_D6   ((unsigned int) AT91C_PIO_PE6) //  
#define AT91C_PIO_PE7        ((unsigned int) 1 <<  7) // Pin Controlled by PE7
#define AT91C_PE7_ISI_D7   ((unsigned int) AT91C_PIO_PE7) //  
#define AT91C_PIO_PE8        ((unsigned int) 1 <<  8) // Pin Controlled by PE8
#define AT91C_PE8_ISI_PCK  ((unsigned int) AT91C_PIO_PE8) //  
#define AT91C_PE8_TIOA1    ((unsigned int) AT91C_PIO_PE8) //  
#define AT91C_PIO_PE9        ((unsigned int) 1 <<  9) // Pin Controlled by PE9
#define AT91C_PE9_ISI_HSYNC ((unsigned int) AT91C_PIO_PE9) //  
#define AT91C_PE9_TIOB1    ((unsigned int) AT91C_PIO_PE9) //  

// *****************************************************************************
//               PERIPHERAL ID DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
#define AT91C_ID_FIQ    ((unsigned int)  0) // Advanced Interrupt Controller (FIQ)
#define AT91C_ID_SYS    ((unsigned int)  1) // System Controller
#define AT91C_ID_PIOA   ((unsigned int)  2) // Parallel IO Controller A
#define AT91C_ID_PIOB   ((unsigned int)  3) // Parallel IO Controller B
#define AT91C_ID_PIOCDE ((unsigned int)  4) // Parallel IO Controller C, Parallel IO Controller D, Parallel IO Controller E
#define AT91C_ID_US0    ((unsigned int)  7) // USART 0
#define AT91C_ID_US1    ((unsigned int)  8) // USART 1
#define AT91C_ID_US2    ((unsigned int)  9) // USART 2
#define AT91C_ID_MCI0   ((unsigned int) 10) // Multimedia Card Interface 0
#define AT91C_ID_MCI1   ((unsigned int) 11) // Multimedia Card Interface 1
#define AT91C_ID_CAN    ((unsigned int) 12) // CAN Controller
#define AT91C_ID_TWI    ((unsigned int) 13) // Two-Wire Interface
#define AT91C_ID_SPI0   ((unsigned int) 14) // Serial Peripheral Interface 0
#define AT91C_ID_SPI1   ((unsigned int) 15) // Serial Peripheral Interface 1
#define AT91C_ID_SSC0   ((unsigned int) 16) // Serial Synchronous Controller 0
#define AT91C_ID_SSC1   ((unsigned int) 17) // Serial Synchronous Controller 1
#define AT91C_ID_AC97C  ((unsigned int) 18) // AC97 Controller
#define AT91C_ID_TC012  ((unsigned int) 19) // Timer Counter 0, Timer Counter 1, Timer Counter 2
#define AT91C_ID_PWMC   ((unsigned int) 20) // PWM Controller
#define AT91C_ID_EMAC   ((unsigned int) 21) // Ethernet Mac
#define AT91C_ID_UDP    ((unsigned int) 24) // USB Device Port
#define AT91C_ID_HISI   ((unsigned int) 25) // Image Sensor Interface
#define AT91C_ID_LCDC   ((unsigned int) 26) // LCD Controller
#define AT91C_ID_DMA    ((unsigned int) 27) // DMA Controller
#define AT91C_ID_UHP    ((unsigned int) 29) // USB Host Port
#define AT91C_ID_IRQ0   ((unsigned int) 30) // Advanced Interrupt Controller (IRQ0)
#define AT91C_ID_IRQ1   ((unsigned int) 31) // Advanced Interrupt Controller (IRQ1)
#define AT91C_ALL_INT   ((unsigned int) 0xEF3FFF9F) // ALL VALID INTERRUPTS

// *****************************************************************************
//               BASE ADDRESS DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
#define AT91C_BASE_SYS       ((AT91PS_SYS) 	0xFFFFE000) // (SYS) Base Address
#define AT91C_BASE_EBI0      ((AT91PS_EBI0) 	0xFFFFE200) // (EBI0) Base Address
#define AT91C_BASE_SDRAMC0   ((AT91PS_SDRAMC) 	0xFFFFE200) // (SDRAMC0) Base Address
#define AT91C_BASE_SMC0      ((AT91PS_SMC) 	0xFFFFE400) // (SMC0) Base Address
#define AT91C_BASE_EBI1      ((AT91PS_EBI1) 	0xFFFFE800) // (EBI1) Base Address
#define AT91C_BASE_SDRAMC1   ((AT91PS_SDRAMC) 	0xFFFFE800) // (SDRAMC1) Base Address
#define AT91C_BASE_SMC1      ((AT91PS_SMC) 	0xFFFFEA00) // (SMC1) Base Address
#define AT91C_BASE_MATRIX    ((AT91PS_MATRIX) 	0xFFFFEC00) // (MATRIX) Base Address
#define AT91C_BASE_CCFG      ((AT91PS_CCFG) 	0xFFFFED10) // (CCFG) Base Address
#define AT91C_BASE_PDC_DBGU  ((AT91PS_PDC) 	0xFFFFEF00) // (PDC_DBGU) Base Address
#define AT91C_BASE_DBGU      ((AT91PS_DBGU) 	0xFFFFEE00) // (DBGU) Base Address
#define AT91C_BASE_AIC       ((AT91PS_AIC) 	0xFFFFF000) // (AIC) Base Address
#define AT91C_BASE_PIOA      ((AT91PS_PIO) 	0xFFFFF200) // (PIOA) Base Address
#define AT91C_BASE_PIOB      ((AT91PS_PIO) 	0xFFFFF400) // (PIOB) Base Address
#define AT91C_BASE_PIOC      ((AT91PS_PIO) 	0xFFFFF600) // (PIOC) Base Address
#define AT91C_BASE_PIOD      ((AT91PS_PIO) 	0xFFFFF800) // (PIOD) Base Address
#define AT91C_BASE_PIOE      ((AT91PS_PIO) 	0xFFFFFA00) // (PIOE) Base Address
#define AT91C_BASE_CKGR      ((AT91PS_CKGR) 	0xFFFFFC20) // (CKGR) Base Address
#define AT91C_BASE_PMC       ((AT91PS_PMC) 	0xFFFFFC00) // (PMC) Base Address
#define AT91C_BASE_RSTC      ((AT91PS_RSTC) 	0xFFFFFD00) // (RSTC) Base Address
#define AT91C_BASE_SHDWC     ((AT91PS_SHDWC) 	0xFFFFFD10) // (SHDWC) Base Address
#define AT91C_BASE_RTTC0     ((AT91PS_RTTC) 	0xFFFFFD20) // (RTTC0) Base Address
#define AT91C_BASE_RTTC1     ((AT91PS_RTTC) 	0xFFFFFD50) // (RTTC1) Base Address
#define AT91C_BASE_PITC      ((AT91PS_PITC) 	0xFFFFFD30) // (PITC) Base Address
#define AT91C_BASE_WDTC      ((AT91PS_WDTC) 	0xFFFFFD40) // (WDTC) Base Address
#define AT91C_BASE_TC0       ((AT91PS_TC) 	0xFFF7C000) // (TC0) Base Address
#define AT91C_BASE_TC1       ((AT91PS_TC) 	0xFFF7C040) // (TC1) Base Address
#define AT91C_BASE_TC2       ((AT91PS_TC) 	0xFFF7C080) // (TC2) Base Address
#define AT91C_BASE_TCB0      ((AT91PS_TCB) 	0xFFF7C000) // (TCB0) Base Address
#define AT91C_BASE_TCB1      ((AT91PS_TCB) 	0xFFF7C040) // (TCB1) Base Address
#define AT91C_BASE_TCB2      ((AT91PS_TCB) 	0xFFF7C080) // (TCB2) Base Address
#define AT91C_BASE_PDC_MCI0  ((AT91PS_PDC) 	0xFFF80100) // (PDC_MCI0) Base Address
#define AT91C_BASE_MCI0      ((AT91PS_MCI) 	0xFFF80000) // (MCI0) Base Address
#define AT91C_BASE_PDC_MCI1  ((AT91PS_PDC) 	0xFFF84100) // (PDC_MCI1) Base Address
#define AT91C_BASE_MCI1      ((AT91PS_MCI) 	0xFFF84000) // (MCI1) Base Address
#define AT91C_BASE_TWI       ((AT91PS_TWI) 	0xFFF88000) // (TWI) Base Address
#define AT91C_BASE_PDC_US0   ((AT91PS_PDC) 	0xFFF8C100) // (PDC_US0) Base Address
#define AT91C_BASE_US0       ((AT91PS_USART) 	0xFFF8C000) // (US0) Base Address
#define AT91C_BASE_PDC_US1   ((AT91PS_PDC) 	0xFFF90100) // (PDC_US1) Base Address
#define AT91C_BASE_US1       ((AT91PS_USART) 	0xFFF90000) // (US1) Base Address
#define AT91C_BASE_PDC_US2   ((AT91PS_PDC) 	0xFFF94100) // (PDC_US2) Base Address
#define AT91C_BASE_US2       ((AT91PS_USART) 	0xFFF94000) // (US2) Base Address
#define AT91C_BASE_PDC_SSC0  ((AT91PS_PDC) 	0xFFF98100) // (PDC_SSC0) Base Address
#define AT91C_BASE_SSC0      ((AT91PS_SSC) 	0xFFF98000) // (SSC0) Base Address
#define AT91C_BASE_PDC_SSC1  ((AT91PS_PDC) 	0xFFF9C100) // (PDC_SSC1) Base Address
#define AT91C_BASE_SSC1      ((AT91PS_SSC) 	0xFFF9C000) // (SSC1) Base Address
#define AT91C_BASE_PDC_AC97C ((AT91PS_PDC) 	0xFFFA0100) // (PDC_AC97C) Base Address
#define AT91C_BASE_AC97C     ((AT91PS_AC97C) 	0xFFFA0000) // (AC97C) Base Address
#define AT91C_BASE_PDC_SPI0  ((AT91PS_PDC) 	0xFFFA4100) // (PDC_SPI0) Base Address
#define AT91C_BASE_SPI0      ((AT91PS_SPI) 	0xFFFA4000) // (SPI0) Base Address
#define AT91C_BASE_PDC_SPI1  ((AT91PS_PDC) 	0xFFFA8100) // (PDC_SPI1) Base Address
#define AT91C_BASE_SPI1      ((AT91PS_SPI) 	0xFFFA8000) // (SPI1) Base Address
#define AT91C_BASE_CAN_MB0   ((AT91PS_CAN_MB) 	0xFFFAC200) // (CAN_MB0) Base Address
#define AT91C_BASE_CAN_MB1   ((AT91PS_CAN_MB) 	0xFFFAC220) // (CAN_MB1) Base Address
#define AT91C_BASE_CAN_MB2   ((AT91PS_CAN_MB) 	0xFFFAC240) // (CAN_MB2) Base Address
#define AT91C_BASE_CAN_MB3   ((AT91PS_CAN_MB) 	0xFFFAC260) // (CAN_MB3) Base Address
#define AT91C_BASE_CAN_MB4   ((AT91PS_CAN_MB) 	0xFFFAC280) // (CAN_MB4) Base Address
#define AT91C_BASE_CAN_MB5   ((AT91PS_CAN_MB) 	0xFFFAC2A0) // (CAN_MB5) Base Address
#define AT91C_BASE_CAN_MB6   ((AT91PS_CAN_MB) 	0xFFFAC2C0) // (CAN_MB6) Base Address
#define AT91C_BASE_CAN_MB7   ((AT91PS_CAN_MB) 	0xFFFAC2E0) // (CAN_MB7) Base Address
#define AT91C_BASE_CAN_MB8   ((AT91PS_CAN_MB) 	0xFFFAC300) // (CAN_MB8) Base Address
#define AT91C_BASE_CAN_MB9   ((AT91PS_CAN_MB) 	0xFFFAC320) // (CAN_MB9) Base Address
#define AT91C_BASE_CAN_MB10  ((AT91PS_CAN_MB) 	0xFFFAC340) // (CAN_MB10) Base Address
#define AT91C_BASE_CAN_MB11  ((AT91PS_CAN_MB) 	0xFFFAC360) // (CAN_MB11) Base Address
#define AT91C_BASE_CAN_MB12  ((AT91PS_CAN_MB) 	0xFFFAC380) // (CAN_MB12) Base Address
#define AT91C_BASE_CAN_MB13  ((AT91PS_CAN_MB) 	0xFFFAC3A0) // (CAN_MB13) Base Address
#define AT91C_BASE_CAN_MB14  ((AT91PS_CAN_MB) 	0xFFFAC3C0) // (CAN_MB14) Base Address
#define AT91C_BASE_CAN_MB15  ((AT91PS_CAN_MB) 	0xFFFAC3E0) // (CAN_MB15) Base Address
#define AT91C_BASE_CAN       ((AT91PS_CAN) 	0xFFFAC000) // (CAN) Base Address
#define AT91C_BASE_PWMC_CH0  ((AT91PS_PWMC_CH) 	0xFFFB8200) // (PWMC_CH0) Base Address
#define AT91C_BASE_PWMC_CH1  ((AT91PS_PWMC_CH) 	0xFFFB8220) // (PWMC_CH1) Base Address
#define AT91C_BASE_PWMC_CH2  ((AT91PS_PWMC_CH) 	0xFFFB8240) // (PWMC_CH2) Base Address
#define AT91C_BASE_PWMC_CH3  ((AT91PS_PWMC_CH) 	0xFFFB8260) // (PWMC_CH3) Base Address
#define AT91C_BASE_PWMC      ((AT91PS_PWMC) 	0xFFFB8000) // (PWMC) Base Address
#define AT91C_BASE_MACB      ((AT91PS_EMAC) 	0xFFFBC000) // (MACB) Base Address
#define AT91C_BASE_LCDC      ((AT91PS_LCDC) 	0x00700000) // (LCDC) Base Address
#define AT91C_BASE_DMA       ((AT91PS_DMA) 	0x00800000) // (DMA) Base Address
#define AT91C_BASE_UDP       ((AT91PS_UDP) 	0xFFF78000) // (UDP) Base Address
#define AT91C_BASE_UHP       ((AT91PS_UHP) 	0x00A00000) // (UHP) Base Address
#define AT91C_BASE_TBOX      ((AT91PS_TBOX) 	0x70000000) // (TBOX) Base Address
#define AT91C_BASE_HECC0     ((AT91PS_ECC) 	0xFFFFE000) // (HECC0) Base Address
#define AT91C_BASE_HECC1     ((AT91PS_ECC) 	0xFFFFE600) // (HECC1) Base Address
#define AT91C_BASE_HISI      ((AT91PS_ISI) 	0xFFFC4000) // (HISI) Base Address

// *****************************************************************************
//               MEMORY MAPPING DEFINITIONS FOR AT91SAM9263
// *****************************************************************************
// ITCM
#define AT91C_ITCM 	 ((char *) 	0x00100000) // Maximum ITCM Area base address
#define AT91C_ITCM_SIZE	 ((unsigned int) 0x00010000) // Maximum ITCM Area size in byte (64 Kbytes)
// DTCM
#define AT91C_DTCM 	 ((char *) 	0x00200000) // Maximum DTCM Area base address
#define AT91C_DTCM_SIZE	 ((unsigned int) 0x00010000) // Maximum DTCM Area size in byte (64 Kbytes)
// IRAM
#define AT91C_IRAM 	 ((char *) 	0x00300000) // Maximum Internal SRAM base address
#define AT91C_IRAM_SIZE	 ((unsigned int) 0x00014000) // Maximum Internal SRAM size in byte (80 Kbytes)
// IRAM_MIN
#define AT91C_IRAM_MIN	 ((char *) 	0x00300000) // Minimum Internal RAM base address
#define AT91C_IRAM_MIN_SIZE	 ((unsigned int) 0x00004000) // Minimum Internal RAM size in byte (16 Kbytes)
// IROM
#define AT91C_IROM 	 ((char *) 	0x00400000) // Internal ROM base address
#define AT91C_IROM_SIZE	 ((unsigned int) 0x00020000) // Internal ROM size in byte (128 Kbytes)
// IRAM2
#define AT91C_IRAM2	 ((char *) 	0x00500000) // IRAM2 base address
#define AT91C_IRAM2_SIZE	 ((unsigned int) 0x00004000) // IRAM2 size in byte (16 Kbytes)
// EBI0_CS0
#define AT91C_EBI0_CS0	 ((char *) 	0x10000000) // EBI0 Chip Select 0 base address
#define AT91C_EBI0_CS0_SIZE	 ((unsigned int) 0x10000000) // EBI0 Chip Select 0 size in byte (262144 Kbytes)
// EBI0_CS1
#define AT91C_EBI0_CS1	 ((char *) 	0x20000000) // EBI0 Chip Select 1 base address
#define AT91C_EBI0_CS1_SIZE	 ((unsigned int) 0x10000000) // EBI0 Chip Select 1 size in byte (262144 Kbytes)
// EBI0_SDRAM
#define AT91C_EBI0_SDRAM	 ((char *) 	0x20000000) // SDRAM on EBI0 Chip Select 1 base address
#define AT91C_EBI0_SDRAM_SIZE	 ((unsigned int) 0x10000000) // SDRAM on EBI0 Chip Select 1 size in byte (262144 Kbytes)
// EBI0_SDRAM_16BIT
#define AT91C_EBI0_SDRAM_16BIT	 ((char *) 	0x20000000) // SDRAM on EBI0 Chip Select 1 base address
#define AT91C_EBI0_SDRAM_16BIT_SIZE	 ((unsigned int) 0x02000000) // SDRAM on EBI0 Chip Select 1 size in byte (32768 Kbytes)
// EBI0_SDRAM_32BIT
#define AT91C_EBI0_SDRAM_32BIT	 ((char *) 	0x20000000) // SDRAM on EBI0 Chip Select 1 base address
#define AT91C_EBI0_SDRAM_32BIT_SIZE	 ((unsigned int) 0x04000000) // SDRAM on EBI0 Chip Select 1 size in byte (65536 Kbytes)
// EBI0_CS2
#define AT91C_EBI0_CS2	 ((char *) 	0x30000000) // EBI0 Chip Select 2 base address
#define AT91C_EBI0_CS2_SIZE	 ((unsigned int) 0x10000000) // EBI0 Chip Select 2 size in byte (262144 Kbytes)
// EBI0_CS3
#define AT91C_EBI0_CS3	 ((char *) 	0x40000000) // EBI0 Chip Select 3 base address
#define AT91C_EBI0_CS3_SIZE	 ((unsigned int) 0x10000000) // EBI0 Chip Select 3 size in byte (262144 Kbytes)
// EBI0_SM
#define AT91C_EBI0_SM	 ((char *) 	0x40000000) // SmartMedia on EBI0 Chip Select 3 base address
#define AT91C_EBI0_SM_SIZE	 ((unsigned int) 0x10000000) // SmartMedia on EBI0 Chip Select 3 size in byte (262144 Kbytes)
// EBI0_CS4
#define AT91C_EBI0_CS4	 ((char *) 	0x50000000) // EBI0 Chip Select 4 base address
#define AT91C_EBI0_CS4_SIZE	 ((unsigned int) 0x10000000) // EBI0 Chip Select 4 size in byte (262144 Kbytes)
// EBI0_CF0
#define AT91C_EBI0_CF0	 ((char *) 	0x50000000) // CompactFlash 0 on EBI0 Chip Select 4 base address
#define AT91C_EBI0_CF0_SIZE	 ((unsigned int) 0x10000000) // CompactFlash 0 on EBI0 Chip Select 4 size in byte (262144 Kbytes)
// EBI0_CS5
#define AT91C_EBI0_CS5	 ((char *) 	0x60000000) // EBI0 Chip Select 5 base address
#define AT91C_EBI0_CS5_SIZE	 ((unsigned int) 0x10000000) // EBI0 Chip Select 5 size in byte (262144 Kbytes)
// EBI0_CF1
#define AT91C_EBI0_CF1	 ((char *) 	0x60000000) // CompactFlash 1 on EBI0Chip Select 5 base address
#define AT91C_EBI0_CF1_SIZE	 ((unsigned int) 0x10000000) // CompactFlash 1 on EBI0Chip Select 5 size in byte (262144 Kbytes)
// EBI1_CS0
#define AT91C_EBI1_CS0	 ((char *) 	0x70000000) // EBI1 Chip Select 0 base address
#define AT91C_EBI1_CS0_SIZE	 ((unsigned int) 0x10000000) // EBI1 Chip Select 0 size in byte (262144 Kbytes)
// EBI1_CS1
#define AT91C_EBI1_CS1	 ((char *) 	0x80000000) // EBI1 Chip Select 1 base address
#define AT91C_EBI1_CS1_SIZE	 ((unsigned int) 0x10000000) // EBI1 Chip Select 1 size in byte (262144 Kbytes)
// EBI1_SDRAM_16BIT
#define AT91C_EBI1_SDRAM_16BIT	 ((char *) 	0x80000000) // SDRAM on EBI1 Chip Select 1 base address
#define AT91C_EBI1_SDRAM_16BIT_SIZE	 ((unsigned int) 0x02000000) // SDRAM on EBI1 Chip Select 1 size in byte (32768 Kbytes)
// EBI1_SDRAM_32BIT
#define AT91C_EBI1_SDRAM_32BIT	 ((char *) 	0x80000000) // SDRAM on EBI1 Chip Select 1 base address
#define AT91C_EBI1_SDRAM_32BIT_SIZE	 ((unsigned int) 0x04000000) // SDRAM on EBI1 Chip Select 1 size in byte (65536 Kbytes)
// EBI1_CS2
#define AT91C_EBI1_CS2	 ((char *) 	0x90000000) // EBI1 Chip Select 2 base address
#define AT91C_EBI1_CS2_SIZE	 ((unsigned int) 0x10000000) // EBI1 Chip Select 2 size in byte (262144 Kbytes)
// EBI1_SM
#define AT91C_EBI1_SM	 ((char *) 	0x90000000) // SmartMedia on EBI1 Chip Select 2 base address
#define AT91C_EBI1_SM_SIZE	 ((unsigned int) 0x10000000) // SmartMedia on EBI1 Chip Select 2 size in byte (262144 Kbytes)
#endif /* __IAR_SYSTEMS_ICC__ */

#ifdef __IAR_SYSTEMS_ASM__

// - Hardware register definition

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR System Peripherals
// - *****************************************************************************
// - -------- GPBR : (SYS Offset: 0x1d60) GPBR General Purpose Register -------- 
AT91C_GPBR_GPRV           EQU (0x0 <<  0) ;- (SYS) General Purpose Register Value

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR External Bus Interface 0
// - *****************************************************************************

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR SDRAM Controller Interface
// - *****************************************************************************
// - -------- SDRAMC_MR : (SDRAMC Offset: 0x0) SDRAM Controller Mode Register -------- 
AT91C_SDRAMC_MODE         EQU (0xF <<  0) ;- (SDRAMC) Mode
AT91C_SDRAMC_MODE_NORMAL_CMD EQU (0x0) ;- (SDRAMC) Normal Mode
AT91C_SDRAMC_MODE_NOP_CMD EQU (0x1) ;- (SDRAMC) Issue a NOP Command at every access
AT91C_SDRAMC_MODE_PRCGALL_CMD EQU (0x2) ;- (SDRAMC) Issue a All Banks Precharge Command at every access
AT91C_SDRAMC_MODE_LMR_CMD EQU (0x3) ;- (SDRAMC) Issue a Load Mode Register at every access
AT91C_SDRAMC_MODE_RFSH_CMD EQU (0x4) ;- (SDRAMC) Issue a Refresh
AT91C_SDRAMC_MODE_EXT_LMR_CMD EQU (0x5) ;- (SDRAMC) Issue an Extended Load Mode Register
AT91C_SDRAMC_MODE_DEEP_CMD EQU (0x6) ;- (SDRAMC) Enter Deep Power Mode
// - -------- SDRAMC_TR : (SDRAMC Offset: 0x4) SDRAMC Refresh Timer Register -------- 
AT91C_SDRAMC_COUNT        EQU (0xFFF <<  0) ;- (SDRAMC) Refresh Counter
// - -------- SDRAMC_CR : (SDRAMC Offset: 0x8) SDRAM Configuration Register -------- 
AT91C_SDRAMC_NC           EQU (0x3 <<  0) ;- (SDRAMC) Number of Column Bits
AT91C_SDRAMC_NC_8         EQU (0x0) ;- (SDRAMC) 8 Bits
AT91C_SDRAMC_NC_9         EQU (0x1) ;- (SDRAMC) 9 Bits
AT91C_SDRAMC_NC_10        EQU (0x2) ;- (SDRAMC) 10 Bits
AT91C_SDRAMC_NC_11        EQU (0x3) ;- (SDRAMC) 11 Bits
AT91C_SDRAMC_NR           EQU (0x3 <<  2) ;- (SDRAMC) Number of Row Bits
AT91C_SDRAMC_NR_11        EQU (0x0 <<  2) ;- (SDRAMC) 11 Bits
AT91C_SDRAMC_NR_12        EQU (0x1 <<  2) ;- (SDRAMC) 12 Bits
AT91C_SDRAMC_NR_13        EQU (0x2 <<  2) ;- (SDRAMC) 13 Bits
AT91C_SDRAMC_NB           EQU (0x1 <<  4) ;- (SDRAMC) Number of Banks
AT91C_SDRAMC_NB_2_BANKS   EQU (0x0 <<  4) ;- (SDRAMC) 2 banks
AT91C_SDRAMC_NB_4_BANKS   EQU (0x1 <<  4) ;- (SDRAMC) 4 banks
AT91C_SDRAMC_CAS          EQU (0x3 <<  5) ;- (SDRAMC) CAS Latency
AT91C_SDRAMC_CAS_2        EQU (0x2 <<  5) ;- (SDRAMC) 2 cycles
AT91C_SDRAMC_CAS_3        EQU (0x3 <<  5) ;- (SDRAMC) 3 cycles
AT91C_SDRAMC_DBW          EQU (0x1 <<  7) ;- (SDRAMC) Data Bus Width
AT91C_SDRAMC_DBW_32_BITS  EQU (0x0 <<  7) ;- (SDRAMC) 32 Bits datas bus
AT91C_SDRAMC_DBW_16_BITS  EQU (0x1 <<  7) ;- (SDRAMC) 16 Bits datas bus
AT91C_SDRAMC_TWR          EQU (0xF <<  8) ;- (SDRAMC) Number of Write Recovery Time Cycles
AT91C_SDRAMC_TWR_0        EQU (0x0 <<  8) ;- (SDRAMC) Value :  0
AT91C_SDRAMC_TWR_1        EQU (0x1 <<  8) ;- (SDRAMC) Value :  1
AT91C_SDRAMC_TWR_2        EQU (0x2 <<  8) ;- (SDRAMC) Value :  2
AT91C_SDRAMC_TWR_3        EQU (0x3 <<  8) ;- (SDRAMC) Value :  3
AT91C_SDRAMC_TWR_4        EQU (0x4 <<  8) ;- (SDRAMC) Value :  4
AT91C_SDRAMC_TWR_5        EQU (0x5 <<  8) ;- (SDRAMC) Value :  5
AT91C_SDRAMC_TWR_6        EQU (0x6 <<  8) ;- (SDRAMC) Value :  6
AT91C_SDRAMC_TWR_7        EQU (0x7 <<  8) ;- (SDRAMC) Value :  7
AT91C_SDRAMC_TWR_8        EQU (0x8 <<  8) ;- (SDRAMC) Value :  8
AT91C_SDRAMC_TWR_9        EQU (0x9 <<  8) ;- (SDRAMC) Value :  9
AT91C_SDRAMC_TWR_10       EQU (0xA <<  8) ;- (SDRAMC) Value : 10
AT91C_SDRAMC_TWR_11       EQU (0xB <<  8) ;- (SDRAMC) Value : 11
AT91C_SDRAMC_TWR_12       EQU (0xC <<  8) ;- (SDRAMC) Value : 12
AT91C_SDRAMC_TWR_13       EQU (0xD <<  8) ;- (SDRAMC) Value : 13
AT91C_SDRAMC_TWR_14       EQU (0xE <<  8) ;- (SDRAMC) Value : 14
AT91C_SDRAMC_TWR_15       EQU (0xF <<  8) ;- (SDRAMC) Value : 15
AT91C_SDRAMC_TRC          EQU (0xF << 12) ;- (SDRAMC) Number of RAS Cycle Time Cycles
AT91C_SDRAMC_TRC_0        EQU (0x0 << 12) ;- (SDRAMC) Value :  0
AT91C_SDRAMC_TRC_1        EQU (0x1 << 12) ;- (SDRAMC) Value :  1
AT91C_SDRAMC_TRC_2        EQU (0x2 << 12) ;- (SDRAMC) Value :  2
AT91C_SDRAMC_TRC_3        EQU (0x3 << 12) ;- (SDRAMC) Value :  3
AT91C_SDRAMC_TRC_4        EQU (0x4 << 12) ;- (SDRAMC) Value :  4
AT91C_SDRAMC_TRC_5        EQU (0x5 << 12) ;- (SDRAMC) Value :  5
AT91C_SDRAMC_TRC_6        EQU (0x6 << 12) ;- (SDRAMC) Value :  6
AT91C_SDRAMC_TRC_7        EQU (0x7 << 12) ;- (SDRAMC) Value :  7
AT91C_SDRAMC_TRC_8        EQU (0x8 << 12) ;- (SDRAMC) Value :  8
AT91C_SDRAMC_TRC_9        EQU (0x9 << 12) ;- (SDRAMC) Value :  9
AT91C_SDRAMC_TRC_10       EQU (0xA << 12) ;- (SDRAMC) Value : 10
AT91C_SDRAMC_TRC_11       EQU (0xB << 12) ;- (SDRAMC) Value : 11
AT91C_SDRAMC_TRC_12       EQU (0xC << 12) ;- (SDRAMC) Value : 12
AT91C_SDRAMC_TRC_13       EQU (0xD << 12) ;- (SDRAMC) Value : 13
AT91C_SDRAMC_TRC_14       EQU (0xE << 12) ;- (SDRAMC) Value : 14
AT91C_SDRAMC_TRC_15       EQU (0xF << 12) ;- (SDRAMC) Value : 15
AT91C_SDRAMC_TRP          EQU (0xF << 16) ;- (SDRAMC) Number of RAS Precharge Time Cycles
AT91C_SDRAMC_TRP_0        EQU (0x0 << 16) ;- (SDRAMC) Value :  0
AT91C_SDRAMC_TRP_1        EQU (0x1 << 16) ;- (SDRAMC) Value :  1
AT91C_SDRAMC_TRP_2        EQU (0x2 << 16) ;- (SDRAMC) Value :  2
AT91C_SDRAMC_TRP_3        EQU (0x3 << 16) ;- (SDRAMC) Value :  3
AT91C_SDRAMC_TRP_4        EQU (0x4 << 16) ;- (SDRAMC) Value :  4
AT91C_SDRAMC_TRP_5        EQU (0x5 << 16) ;- (SDRAMC) Value :  5
AT91C_SDRAMC_TRP_6        EQU (0x6 << 16) ;- (SDRAMC) Value :  6
AT91C_SDRAMC_TRP_7        EQU (0x7 << 16) ;- (SDRAMC) Value :  7
AT91C_SDRAMC_TRP_8        EQU (0x8 << 16) ;- (SDRAMC) Value :  8
AT91C_SDRAMC_TRP_9        EQU (0x9 << 16) ;- (SDRAMC) Value :  9
AT91C_SDRAMC_TRP_10       EQU (0xA << 16) ;- (SDRAMC) Value : 10
AT91C_SDRAMC_TRP_11       EQU (0xB << 16) ;- (SDRAMC) Value : 11
AT91C_SDRAMC_TRP_12       EQU (0xC << 16) ;- (SDRAMC) Value : 12
AT91C_SDRAMC_TRP_13       EQU (0xD << 16) ;- (SDRAMC) Value : 13
AT91C_SDRAMC_TRP_14       EQU (0xE << 16) ;- (SDRAMC) Value : 14
AT91C_SDRAMC_TRP_15       EQU (0xF << 16) ;- (SDRAMC) Value : 15
AT91C_SDRAMC_TRCD         EQU (0xF << 20) ;- (SDRAMC) Number of RAS to CAS Delay Cycles
AT91C_SDRAMC_TRCD_0       EQU (0x0 << 20) ;- (SDRAMC) Value :  0
AT91C_SDRAMC_TRCD_1       EQU (0x1 << 20) ;- (SDRAMC) Value :  1
AT91C_SDRAMC_TRCD_2       EQU (0x2 << 20) ;- (SDRAMC) Value :  2
AT91C_SDRAMC_TRCD_3       EQU (0x3 << 20) ;- (SDRAMC) Value :  3
AT91C_SDRAMC_TRCD_4       EQU (0x4 << 20) ;- (SDRAMC) Value :  4
AT91C_SDRAMC_TRCD_5       EQU (0x5 << 20) ;- (SDRAMC) Value :  5
AT91C_SDRAMC_TRCD_6       EQU (0x6 << 20) ;- (SDRAMC) Value :  6
AT91C_SDRAMC_TRCD_7       EQU (0x7 << 20) ;- (SDRAMC) Value :  7
AT91C_SDRAMC_TRCD_8       EQU (0x8 << 20) ;- (SDRAMC) Value :  8
AT91C_SDRAMC_TRCD_9       EQU (0x9 << 20) ;- (SDRAMC) Value :  9
AT91C_SDRAMC_TRCD_10      EQU (0xA << 20) ;- (SDRAMC) Value : 10
AT91C_SDRAMC_TRCD_11      EQU (0xB << 20) ;- (SDRAMC) Value : 11
AT91C_SDRAMC_TRCD_12      EQU (0xC << 20) ;- (SDRAMC) Value : 12
AT91C_SDRAMC_TRCD_13      EQU (0xD << 20) ;- (SDRAMC) Value : 13
AT91C_SDRAMC_TRCD_14      EQU (0xE << 20) ;- (SDRAMC) Value : 14
AT91C_SDRAMC_TRCD_15      EQU (0xF << 20) ;- (SDRAMC) Value : 15
AT91C_SDRAMC_TRAS         EQU (0xF << 24) ;- (SDRAMC) Number of RAS Active Time Cycles
AT91C_SDRAMC_TRAS_0       EQU (0x0 << 24) ;- (SDRAMC) Value :  0
AT91C_SDRAMC_TRAS_1       EQU (0x1 << 24) ;- (SDRAMC) Value :  1
AT91C_SDRAMC_TRAS_2       EQU (0x2 << 24) ;- (SDRAMC) Value :  2
AT91C_SDRAMC_TRAS_3       EQU (0x3 << 24) ;- (SDRAMC) Value :  3
AT91C_SDRAMC_TRAS_4       EQU (0x4 << 24) ;- (SDRAMC) Value :  4
AT91C_SDRAMC_TRAS_5       EQU (0x5 << 24) ;- (SDRAMC) Value :  5
AT91C_SDRAMC_TRAS_6       EQU (0x6 << 24) ;- (SDRAMC) Value :  6
AT91C_SDRAMC_TRAS_7       EQU (0x7 << 24) ;- (SDRAMC) Value :  7
AT91C_SDRAMC_TRAS_8       EQU (0x8 << 24) ;- (SDRAMC) Value :  8
AT91C_SDRAMC_TRAS_9       EQU (0x9 << 24) ;- (SDRAMC) Value :  9
AT91C_SDRAMC_TRAS_10      EQU (0xA << 24) ;- (SDRAMC) Value : 10
AT91C_SDRAMC_TRAS_11      EQU (0xB << 24) ;- (SDRAMC) Value : 11
AT91C_SDRAMC_TRAS_12      EQU (0xC << 24) ;- (SDRAMC) Value : 12
AT91C_SDRAMC_TRAS_13      EQU (0xD << 24) ;- (SDRAMC) Value : 13
AT91C_SDRAMC_TRAS_14      EQU (0xE << 24) ;- (SDRAMC) Value : 14
AT91C_SDRAMC_TRAS_15      EQU (0xF << 24) ;- (SDRAMC) Value : 15
AT91C_SDRAMC_TXSR         EQU (0xF << 28) ;- (SDRAMC) Number of Command Recovery Time Cycles
AT91C_SDRAMC_TXSR_0       EQU (0x0 << 28) ;- (SDRAMC) Value :  0
AT91C_SDRAMC_TXSR_1       EQU (0x1 << 28) ;- (SDRAMC) Value :  1
AT91C_SDRAMC_TXSR_2       EQU (0x2 << 28) ;- (SDRAMC) Value :  2
AT91C_SDRAMC_TXSR_3       EQU (0x3 << 28) ;- (SDRAMC) Value :  3
AT91C_SDRAMC_TXSR_4       EQU (0x4 << 28) ;- (SDRAMC) Value :  4
AT91C_SDRAMC_TXSR_5       EQU (0x5 << 28) ;- (SDRAMC) Value :  5
AT91C_SDRAMC_TXSR_6       EQU (0x6 << 28) ;- (SDRAMC) Value :  6
AT91C_SDRAMC_TXSR_7       EQU (0x7 << 28) ;- (SDRAMC) Value :  7
AT91C_SDRAMC_TXSR_8       EQU (0x8 << 28) ;- (SDRAMC) Value :  8
AT91C_SDRAMC_TXSR_9       EQU (0x9 << 28) ;- (SDRAMC) Value :  9
AT91C_SDRAMC_TXSR_10      EQU (0xA << 28) ;- (SDRAMC) Value : 10
AT91C_SDRAMC_TXSR_11      EQU (0xB << 28) ;- (SDRAMC) Value : 11
AT91C_SDRAMC_TXSR_12      EQU (0xC << 28) ;- (SDRAMC) Value : 12
AT91C_SDRAMC_TXSR_13      EQU (0xD << 28) ;- (SDRAMC) Value : 13
AT91C_SDRAMC_TXSR_14      EQU (0xE << 28) ;- (SDRAMC) Value : 14
AT91C_SDRAMC_TXSR_15      EQU (0xF << 28) ;- (SDRAMC) Value : 15
// - -------- SDRAMC_HSR : (SDRAMC Offset: 0xc) SDRAM Controller High Speed Register -------- 
AT91C_SDRAMC_DA           EQU (0x1 <<  0) ;- (SDRAMC) Decode Cycle Enable Bit
AT91C_SDRAMC_DA_DISABLE   EQU (0x0) ;- (SDRAMC) Disable Decode Cycle
AT91C_SDRAMC_DA_ENABLE    EQU (0x1) ;- (SDRAMC) Enable Decode Cycle
// - -------- SDRAMC_LPR : (SDRAMC Offset: 0x10) SDRAM Controller Low-power Register -------- 
AT91C_SDRAMC_LPCB         EQU (0x3 <<  0) ;- (SDRAMC) Low-power Configurations
AT91C_SDRAMC_LPCB_DISABLE EQU (0x0) ;- (SDRAMC) Disable Low Power Features
AT91C_SDRAMC_LPCB_SELF_REFRESH EQU (0x1) ;- (SDRAMC) Enable SELF_REFRESH
AT91C_SDRAMC_LPCB_POWER_DOWN EQU (0x2) ;- (SDRAMC) Enable POWER_DOWN
AT91C_SDRAMC_LPCB_DEEP_POWER_DOWN EQU (0x3) ;- (SDRAMC) Enable DEEP_POWER_DOWN
AT91C_SDRAMC_PASR         EQU (0x7 <<  4) ;- (SDRAMC) Partial Array Self Refresh (only for Low Power SDRAM)
AT91C_SDRAMC_TCSR         EQU (0x3 <<  8) ;- (SDRAMC) Temperature Compensated Self Refresh (only for Low Power SDRAM)
AT91C_SDRAMC_DS           EQU (0x3 << 10) ;- (SDRAMC) Drive Strenght (only for Low Power SDRAM)
AT91C_SDRAMC_TIMEOUT      EQU (0x3 << 12) ;- (SDRAMC) Time to define when Low Power Mode is enabled
AT91C_SDRAMC_TIMEOUT_0_CLK_CYCLES EQU (0x0 << 12) ;- (SDRAMC) Activate SDRAM Low Power Mode Immediately
AT91C_SDRAMC_TIMEOUT_64_CLK_CYCLES EQU (0x1 << 12) ;- (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
AT91C_SDRAMC_TIMEOUT_128_CLK_CYCLES EQU (0x2 << 12) ;- (SDRAMC) Activate SDRAM Low Power Mode after 64 clock cycles after the end of the last transfer
// - -------- SDRAMC_IER : (SDRAMC Offset: 0x14) SDRAM Controller Interrupt Enable Register -------- 
AT91C_SDRAMC_RES          EQU (0x1 <<  0) ;- (SDRAMC) Refresh Error Status
// - -------- SDRAMC_IDR : (SDRAMC Offset: 0x18) SDRAM Controller Interrupt Disable Register -------- 
// - -------- SDRAMC_IMR : (SDRAMC Offset: 0x1c) SDRAM Controller Interrupt Mask Register -------- 
// - -------- SDRAMC_ISR : (SDRAMC Offset: 0x20) SDRAM Controller Interrupt Status Register -------- 
// - -------- SDRAMC_MDR : (SDRAMC Offset: 0x24) SDRAM Controller Memory Device Register -------- 
AT91C_SDRAMC_MD           EQU (0x3 <<  0) ;- (SDRAMC) Memory Device Type
AT91C_SDRAMC_MD_SDRAM     EQU (0x0) ;- (SDRAMC) SDRAM Mode
AT91C_SDRAMC_MD_LOW_POWER_SDRAM EQU (0x1) ;- (SDRAMC) SDRAM Low Power Mode

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Static Memory Controller Interface
// - *****************************************************************************
// - -------- SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x -------- 
AT91C_SMC_NWESETUP        EQU (0x3F <<  0) ;- (SMC) NWE Setup Length
AT91C_SMC_NCSSETUPWR      EQU (0x3F <<  8) ;- (SMC) NCS Setup Length in WRite Access
AT91C_SMC_NRDSETUP        EQU (0x3F << 16) ;- (SMC) NRD Setup Length
AT91C_SMC_NCSSETUPRD      EQU (0x3F << 24) ;- (SMC) NCS Setup Length in ReaD Access
// - -------- SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x -------- 
AT91C_SMC_NWEPULSE        EQU (0x7F <<  0) ;- (SMC) NWE Pulse Length
AT91C_SMC_NCSPULSEWR      EQU (0x7F <<  8) ;- (SMC) NCS Pulse Length in WRite Access
AT91C_SMC_NRDPULSE        EQU (0x7F << 16) ;- (SMC) NRD Pulse Length
AT91C_SMC_NCSPULSERD      EQU (0x7F << 24) ;- (SMC) NCS Pulse Length in ReaD Access
// - -------- SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x -------- 
AT91C_SMC_NWECYCLE        EQU (0x1FF <<  0) ;- (SMC) Total Write Cycle Length
AT91C_SMC_NRDCYCLE        EQU (0x1FF << 16) ;- (SMC) Total Read Cycle Length
// - -------- SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x -------- 
AT91C_SMC_READMODE        EQU (0x1 <<  0) ;- (SMC) Read Mode
AT91C_SMC_WRITEMODE       EQU (0x1 <<  1) ;- (SMC) Write Mode
AT91C_SMC_NWAITM          EQU (0x3 <<  5) ;- (SMC) NWAIT Mode
AT91C_SMC_NWAITM_NWAIT_DISABLE EQU (0x0 <<  5) ;- (SMC) External NWAIT disabled.
AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN EQU (0x2 <<  5) ;- (SMC) External NWAIT enabled in frozen mode.
AT91C_SMC_NWAITM_NWAIT_ENABLE_READY EQU (0x3 <<  5) ;- (SMC) External NWAIT enabled in ready mode.
AT91C_SMC_BAT             EQU (0x1 <<  8) ;- (SMC) Byte Access Type
AT91C_SMC_BAT_BYTE_SELECT EQU (0x0 <<  8) ;- (SMC) Write controled by ncs, nbs0, nbs1, nbs2, nbs3. Read controled by ncs, nrd, nbs0, nbs1, nbs2, nbs3.
AT91C_SMC_BAT_BYTE_WRITE  EQU (0x1 <<  8) ;- (SMC) Write controled by ncs, nwe0, nwe1, nwe2, nwe3. Read controled by ncs and nrd.
AT91C_SMC_DBW             EQU (0x3 << 12) ;- (SMC) Data Bus Width
AT91C_SMC_DBW_WIDTH_EIGTH_BITS EQU (0x0 << 12) ;- (SMC) 8 bits.
AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS EQU (0x1 << 12) ;- (SMC) 16 bits.
AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS EQU (0x2 << 12) ;- (SMC) 32 bits.
AT91C_SMC_TDF             EQU (0xF << 16) ;- (SMC) Data Float Time.
AT91C_SMC_TDFEN           EQU (0x1 << 20) ;- (SMC) TDF Enabled.
AT91C_SMC_PMEN            EQU (0x1 << 24) ;- (SMC) Page Mode Enabled.
AT91C_SMC_PS              EQU (0x3 << 28) ;- (SMC) Page Size
AT91C_SMC_PS_SIZE_FOUR_BYTES EQU (0x0 << 28) ;- (SMC) 4 bytes.
AT91C_SMC_PS_SIZE_EIGHT_BYTES EQU (0x1 << 28) ;- (SMC) 8 bytes.
AT91C_SMC_PS_SIZE_SIXTEEN_BYTES EQU (0x2 << 28) ;- (SMC) 16 bytes.
AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES EQU (0x3 << 28) ;- (SMC) 32 bytes.
// - -------- SMC_SETUP : (SMC Offset: 0x10) Setup Register for CS x -------- 
// - -------- SMC_PULSE : (SMC Offset: 0x14) Pulse Register for CS x -------- 
// - -------- SMC_CYC : (SMC Offset: 0x18) Cycle Register for CS x -------- 
// - -------- SMC_CTRL : (SMC Offset: 0x1c) Control Register for CS x -------- 
// - -------- SMC_SETUP : (SMC Offset: 0x20) Setup Register for CS x -------- 
// - -------- SMC_PULSE : (SMC Offset: 0x24) Pulse Register for CS x -------- 
// - -------- SMC_CYC : (SMC Offset: 0x28) Cycle Register for CS x -------- 
// - -------- SMC_CTRL : (SMC Offset: 0x2c) Control Register for CS x -------- 
// - -------- SMC_SETUP : (SMC Offset: 0x30) Setup Register for CS x -------- 
// - -------- SMC_PULSE : (SMC Offset: 0x34) Pulse Register for CS x -------- 
// - -------- SMC_CYC : (SMC Offset: 0x38) Cycle Register for CS x -------- 
// - -------- SMC_CTRL : (SMC Offset: 0x3c) Control Register for CS x -------- 
// - -------- SMC_SETUP : (SMC Offset: 0x40) Setup Register for CS x -------- 
// - -------- SMC_PULSE : (SMC Offset: 0x44) Pulse Register for CS x -------- 
// - -------- SMC_CYC : (SMC Offset: 0x48) Cycle Register for CS x -------- 
// - -------- SMC_CTRL : (SMC Offset: 0x4c) Control Register for CS x -------- 
// - -------- SMC_SETUP : (SMC Offset: 0x50) Setup Register for CS x -------- 
// - -------- SMC_PULSE : (SMC Offset: 0x54) Pulse Register for CS x -------- 
// - -------- SMC_CYC : (SMC Offset: 0x58) Cycle Register for CS x -------- 
// - -------- SMC_CTRL : (SMC Offset: 0x5c) Control Register for CS x -------- 
// - -------- SMC_SETUP : (SMC Offset: 0x60) Setup Register for CS x -------- 
// - -------- SMC_PULSE : (SMC Offset: 0x64) Pulse Register for CS x -------- 
// - -------- SMC_CYC : (SMC Offset: 0x68) Cycle Register for CS x -------- 
// - -------- SMC_CTRL : (SMC Offset: 0x6c) Control Register for CS x -------- 
// - -------- SMC_SETUP : (SMC Offset: 0x70) Setup Register for CS x -------- 
// - -------- SMC_PULSE : (SMC Offset: 0x74) Pulse Register for CS x -------- 
// - -------- SMC_CYC : (SMC Offset: 0x78) Cycle Register for CS x -------- 
// - -------- SMC_CTRL : (SMC Offset: 0x7c) Control Register for CS x -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR External Bus Interface 1
// - *****************************************************************************

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR AHB Matrix Interface
// - *****************************************************************************
// - -------- MATRIX_MCFG0 : (MATRIX Offset: 0x0) Master Configuration Register rom -------- 
AT91C_MATRIX_ULBT         EQU (0x7 <<  0) ;- (MATRIX) Undefined Length Burst Type
// - -------- MATRIX_MCFG1 : (MATRIX Offset: 0x4) Master Configuration Register htcm -------- 
// - -------- MATRIX_MCFG2 : (MATRIX Offset: 0x8) Master Configuration Register gps_tcm -------- 
// - -------- MATRIX_MCFG3 : (MATRIX Offset: 0xc) Master Configuration Register hperiphs -------- 
// - -------- MATRIX_MCFG4 : (MATRIX Offset: 0x10) Master Configuration Register ebi0 -------- 
// - -------- MATRIX_MCFG5 : (MATRIX Offset: 0x14) Master Configuration Register ebi1 -------- 
// - -------- MATRIX_MCFG6 : (MATRIX Offset: 0x18) Master Configuration Register bridge -------- 
// - -------- MATRIX_MCFG7 : (MATRIX Offset: 0x1c) Master Configuration Register gps -------- 
// - -------- MATRIX_MCFG8 : (MATRIX Offset: 0x20) Master Configuration Register gps -------- 
// - -------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 -------- 
AT91C_MATRIX_SLOT_CYCLE   EQU (0xFF <<  0) ;- (MATRIX) Maximum Number of Allowed Cycles for a Burst
AT91C_MATRIX_DEFMSTR_TYPE EQU (0x3 << 16) ;- (MATRIX) Default Master Type
AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR EQU (0x0 << 16) ;- (MATRIX) No Default Master. At the end of current slave access, if no other master request is pending, the slave is deconnected from all masters. This results in having a one cycle latency for the first transfer of a burst.
AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR EQU (0x1 << 16) ;- (MATRIX) Last Default Master. At the end of current slave access, if no other master request is pending, the slave stay connected with the last master having accessed it. This results in not having the one cycle latency when the last master re-trying access on the slave.
AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR EQU (0x2 << 16) ;- (MATRIX) Fixed Default Master. At the end of current slave access, if no other master request is pending, the slave connects with fixed which number is in FIXED_DEFMSTR field. This results in not having the one cycle latency when the fixed master re-trying access on the slave.
AT91C_MATRIX_FIXED_DEFMSTR0 EQU (0x7 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_PDC EQU (0x2 << 18) ;- (MATRIX) PDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_LCDC EQU (0x3 << 18) ;- (MATRIX) LCDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_2DGC EQU (0x4 << 18) ;- (MATRIX) 2DGC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_ISI EQU (0x5 << 18) ;- (MATRIX) ISI Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_EMAC EQU (0x7 << 18) ;- (MATRIX) EMAC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR0_USB EQU (0x8 << 18) ;- (MATRIX) USB Master is Default Master
AT91C_MATRIX_ARBT         EQU (0x3 << 24) ;- (MATRIX) Arbitration Type
// - -------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 -------- 
AT91C_MATRIX_FIXED_DEFMSTR1 EQU (0x7 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_PDC EQU (0x2 << 18) ;- (MATRIX) PDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_LCDC EQU (0x3 << 18) ;- (MATRIX) LCDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_2DGC EQU (0x4 << 18) ;- (MATRIX) 2DGC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_ISI EQU (0x5 << 18) ;- (MATRIX) ISI Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_EMAC EQU (0x7 << 18) ;- (MATRIX) EMAC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR1_USB EQU (0x8 << 18) ;- (MATRIX) USB Master is Default Master
// - -------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 -------- 
AT91C_MATRIX_FIXED_DEFMSTR2 EQU (0x1 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR2_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
// - -------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 -------- 
AT91C_MATRIX_FIXED_DEFMSTR3 EQU (0x7 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_PDC EQU (0x2 << 18) ;- (MATRIX) PDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_LCDC EQU (0x3 << 18) ;- (MATRIX) LCDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_2DGC EQU (0x4 << 18) ;- (MATRIX) 2DGC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_ISI EQU (0x5 << 18) ;- (MATRIX) ISI Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_EMAC EQU (0x7 << 18) ;- (MATRIX) EMAC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR3_USB EQU (0x8 << 18) ;- (MATRIX) USB Master is Default Master
// - -------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 -------- 
AT91C_MATRIX_FIXED_DEFMSTR4 EQU (0x3 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR4_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
// - -------- MATRIX_SCFG5 : (MATRIX Offset: 0x54) Slave Configuration Register 5 -------- 
AT91C_MATRIX_FIXED_DEFMSTR5 EQU (0x3 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_PDC EQU (0x2 << 18) ;- (MATRIX) PDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_LCDC EQU (0x3 << 18) ;- (MATRIX) LCDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_2DGC EQU (0x4 << 18) ;- (MATRIX) 2DGC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_ISI EQU (0x5 << 18) ;- (MATRIX) ISI Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_EMAC EQU (0x7 << 18) ;- (MATRIX) EMAC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR5_USB EQU (0x8 << 18) ;- (MATRIX) USB Master is Default Master
// - -------- MATRIX_SCFG6 : (MATRIX Offset: 0x58) Slave Configuration Register 6 -------- 
AT91C_MATRIX_FIXED_DEFMSTR6 EQU (0x3 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_PDC EQU (0x2 << 18) ;- (MATRIX) PDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_LCDC EQU (0x3 << 18) ;- (MATRIX) LCDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_2DGC EQU (0x4 << 18) ;- (MATRIX) 2DGC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_ISI EQU (0x5 << 18) ;- (MATRIX) ISI Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_EMAC EQU (0x7 << 18) ;- (MATRIX) EMAC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR6_USB EQU (0x8 << 18) ;- (MATRIX) USB Master is Default Master
// - -------- MATRIX_SCFG7 : (MATRIX Offset: 0x5c) Slave Configuration Register 7 -------- 
AT91C_MATRIX_FIXED_DEFMSTR7 EQU (0x3 << 18) ;- (MATRIX) Fixed Index of Default Master
AT91C_MATRIX_FIXED_DEFMSTR7_ARM926I EQU (0x0 << 18) ;- (MATRIX) ARM926EJ-S Instruction Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR7_ARM926D EQU (0x1 << 18) ;- (MATRIX) ARM926EJ-S Data Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR7_PDC EQU (0x2 << 18) ;- (MATRIX) PDC Master is Default Master
AT91C_MATRIX_FIXED_DEFMSTR7_DMA EQU (0x6 << 18) ;- (MATRIX) DMA Controller Master is Default Master
// - -------- MATRIX_PRAS0 : (MATRIX Offset: 0x80) PRAS0 Register -------- 
AT91C_MATRIX_M0PR         EQU (0x3 <<  0) ;- (MATRIX) ARM926EJ-S Instruction priority
AT91C_MATRIX_M1PR         EQU (0x3 <<  4) ;- (MATRIX) ARM926EJ-S Data priority
AT91C_MATRIX_M2PR         EQU (0x3 <<  8) ;- (MATRIX) PDC priority
AT91C_MATRIX_M3PR         EQU (0x3 << 12) ;- (MATRIX) LCDC priority
AT91C_MATRIX_M4PR         EQU (0x3 << 16) ;- (MATRIX) 2DGC priority
AT91C_MATRIX_M5PR         EQU (0x3 << 20) ;- (MATRIX) ISI priority
AT91C_MATRIX_M6PR         EQU (0x3 << 24) ;- (MATRIX) DMA priority
AT91C_MATRIX_M7PR         EQU (0x3 << 28) ;- (MATRIX) EMAC priority
// - -------- MATRIX_PRBS0 : (MATRIX Offset: 0x84) PRBS0 Register -------- 
AT91C_MATRIX_M8PR         EQU (0x3 <<  0) ;- (MATRIX) USB priority
// - -------- MATRIX_PRAS1 : (MATRIX Offset: 0x88) PRAS1 Register -------- 
// - -------- MATRIX_PRBS1 : (MATRIX Offset: 0x8c) PRBS1 Register -------- 
// - -------- MATRIX_PRAS2 : (MATRIX Offset: 0x90) PRAS2 Register -------- 
// - -------- MATRIX_PRBS2 : (MATRIX Offset: 0x94) PRBS2 Register -------- 
// - -------- MATRIX_PRAS3 : (MATRIX Offset: 0x98) PRAS3 Register -------- 
// - -------- MATRIX_PRBS3 : (MATRIX Offset: 0x9c) PRBS3 Register -------- 
// - -------- MATRIX_PRAS4 : (MATRIX Offset: 0xa0) PRAS4 Register -------- 
// - -------- MATRIX_PRBS4 : (MATRIX Offset: 0xa4) PRBS4 Register -------- 
// - -------- MATRIX_PRAS5 : (MATRIX Offset: 0xa8) PRAS5 Register -------- 
// - -------- MATRIX_PRBS5 : (MATRIX Offset: 0xac) PRBS5 Register -------- 
// - -------- MATRIX_PRAS6 : (MATRIX Offset: 0xb0) PRAS6 Register -------- 
// - -------- MATRIX_PRBS6 : (MATRIX Offset: 0xb4) PRBS6 Register -------- 
// - -------- MATRIX_PRAS7 : (MATRIX Offset: 0xb8) PRAS7 Register -------- 
// - -------- MATRIX_PRBS7 : (MATRIX Offset: 0xbc) PRBS7 Register -------- 
// - -------- MATRIX_MRCR : (MATRIX Offset: 0x100) MRCR Register -------- 
AT91C_MATRIX_RCA926I      EQU (0x1 <<  0) ;- (MATRIX) Remap Command Bit for ARM926EJ-S Instruction
AT91C_MATRIX_RCA926D      EQU (0x1 <<  1) ;- (MATRIX) Remap Command Bit for ARM926EJ-S Data
AT91C_MATRIX_RCB2         EQU (0x1 <<  2) ;- (MATRIX) Remap Command Bit for PDC
AT91C_MATRIX_RCB3         EQU (0x1 <<  3) ;- (MATRIX) Remap Command Bit for LCD
AT91C_MATRIX_RCB4         EQU (0x1 <<  4) ;- (MATRIX) Remap Command Bit for 2DGC
AT91C_MATRIX_RCB5         EQU (0x1 <<  5) ;- (MATRIX) Remap Command Bit for ISI
AT91C_MATRIX_RCB6         EQU (0x1 <<  6) ;- (MATRIX) Remap Command Bit for DMA
AT91C_MATRIX_RCB7         EQU (0x1 <<  7) ;- (MATRIX) Remap Command Bit for EMAC
AT91C_MATRIX_RCB8         EQU (0x1 <<  8) ;- (MATRIX) Remap Command Bit for USB

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
// - *****************************************************************************
// - -------- CCFG_TCMR : (CCFG Offset: 0x4) TCM Configuration -------- 
AT91C_CCFG_ITCM_SIZE      EQU (0xF <<  0) ;- (CCFG) Size of ITCM enabled memory block
AT91C_CCFG_ITCM_SIZE_0KB  EQU (0x0) ;- (CCFG) 0 KB (No ITCM Memory)
AT91C_CCFG_ITCM_SIZE_16KB EQU (0x5) ;- (CCFG) 16 KB
AT91C_CCFG_ITCM_SIZE_32KB EQU (0x6) ;- (CCFG) 32 KB
AT91C_CCFG_DTCM_SIZE      EQU (0xF <<  4) ;- (CCFG) Size of DTCM enabled memory block
AT91C_CCFG_DTCM_SIZE_0KB  EQU (0x0 <<  4) ;- (CCFG) 0 KB (No DTCM Memory)
AT91C_CCFG_DTCM_SIZE_16KB EQU (0x5 <<  4) ;- (CCFG) 16 KB
AT91C_CCFG_DTCM_SIZE_32KB EQU (0x6 <<  4) ;- (CCFG) 32 KB
AT91C_CCFG_RM             EQU (0xF <<  8) ;- (CCFG) Read Margin registers
// - -------- CCFG_EBI0CSA : (CCFG Offset: 0x10) EBI0 Chip Select Assignment Register -------- 
AT91C_EBI_CS1A            EQU (0x1 <<  1) ;- (CCFG) Chip Select 1 Assignment
AT91C_EBI_CS1A_SMC        EQU (0x0 <<  1) ;- (CCFG) Chip Select 1 is assigned to the Static Memory Controller.
AT91C_EBI_CS1A_SDRAMC     EQU (0x1 <<  1) ;- (CCFG) Chip Select 1 is assigned to the SDRAM Controller.
AT91C_EBI_CS3A            EQU (0x1 <<  3) ;- (CCFG) Chip Select 3 Assignment
AT91C_EBI_CS3A_SMC        EQU (0x0 <<  3) ;- (CCFG) Chip Select 3 is only assigned to the Static Memory Controller and NCS3 behaves as defined by the SMC.
AT91C_EBI_CS3A_SM         EQU (0x1 <<  3) ;- (CCFG) Chip Select 3 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.
AT91C_EBI_CS4A            EQU (0x1 <<  4) ;- (CCFG) Chip Select 4 Assignment
AT91C_EBI_CS4A_SMC        EQU (0x0 <<  4) ;- (CCFG) Chip Select 4 is only assigned to the Static Memory Controller and NCS4 behaves as defined by the SMC.
AT91C_EBI_CS4A_CF         EQU (0x1 <<  4) ;- (CCFG) Chip Select 4 is assigned to the Static Memory Controller and the CompactFlash Logic (first slot) is activated.
AT91C_EBI_CS5A            EQU (0x1 <<  5) ;- (CCFG) Chip Select 5 Assignment
AT91C_EBI_CS5A_SMC        EQU (0x0 <<  5) ;- (CCFG) Chip Select 5 is only assigned to the Static Memory Controller and NCS5 behaves as defined by the SMC
AT91C_EBI_CS5A_CF         EQU (0x1 <<  5) ;- (CCFG) Chip Select 5 is assigned to the Static Memory Controller and the CompactFlash Logic (second slot) is activated.
AT91C_EBI_DBPUC           EQU (0x1 <<  8) ;- (CCFG) Data Bus Pull-up Configuration
// - -------- CCFG_EBI1CSA : (CCFG Offset: 0x14) EBI1 Chip Select Assignement Register -------- 
AT91C_EBI_CS2A            EQU (0x1 <<  3) ;- (CCFG) EBI1 Chip Select 2 Assignment
AT91C_EBI_CS2A_SMC        EQU (0x0 <<  3) ;- (CCFG) Chip Select 2 is assigned to the Static Memory Controller.
AT91C_EBI_CS2A_SM         EQU (0x1 <<  3) ;- (CCFG) Chip Select 2 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller
// - *****************************************************************************
// - -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- 
AT91C_PDC_RXTEN           EQU (0x1 <<  0) ;- (PDC) Receiver Transfer Enable
AT91C_PDC_RXTDIS          EQU (0x1 <<  1) ;- (PDC) Receiver Transfer Disable
AT91C_PDC_TXTEN           EQU (0x1 <<  8) ;- (PDC) Transmitter Transfer Enable
AT91C_PDC_TXTDIS          EQU (0x1 <<  9) ;- (PDC) Transmitter Transfer Disable
// - -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Debug Unit
// - *****************************************************************************
// - -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
AT91C_US_RSTRX            EQU (0x1 <<  2) ;- (DBGU) Reset Receiver
AT91C_US_RSTTX            EQU (0x1 <<  3) ;- (DBGU) Reset Transmitter
AT91C_US_RXEN             EQU (0x1 <<  4) ;- (DBGU) Receiver Enable
AT91C_US_RXDIS            EQU (0x1 <<  5) ;- (DBGU) Receiver Disable
AT91C_US_TXEN             EQU (0x1 <<  6) ;- (DBGU) Transmitter Enable
AT91C_US_TXDIS            EQU (0x1 <<  7) ;- (DBGU) Transmitter Disable
AT91C_US_RSTSTA           EQU (0x1 <<  8) ;- (DBGU) Reset Status Bits
// - -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
AT91C_US_PAR              EQU (0x7 <<  9) ;- (DBGU) Parity type
AT91C_US_PAR_EVEN         EQU (0x0 <<  9) ;- (DBGU) Even Parity
AT91C_US_PAR_ODD          EQU (0x1 <<  9) ;- (DBGU) Odd Parity
AT91C_US_PAR_SPACE        EQU (0x2 <<  9) ;- (DBGU) Parity forced to 0 (Space)
AT91C_US_PAR_MARK         EQU (0x3 <<  9) ;- (DBGU) Parity forced to 1 (Mark)
AT91C_US_PAR_NONE         EQU (0x4 <<  9) ;- (DBGU) No Parity
AT91C_US_PAR_MULTI_DROP   EQU (0x6 <<  9) ;- (DBGU) Multi-drop mode
AT91C_US_CHMODE           EQU (0x3 << 14) ;- (DBGU) Channel Mode
AT91C_US_CHMODE_NORMAL    EQU (0x0 << 14) ;- (DBGU) Normal Mode: The USART channel operates as an RX/TX USART.
AT91C_US_CHMODE_AUTO      EQU (0x1 << 14) ;- (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin.
AT91C_US_CHMODE_LOCAL     EQU (0x2 << 14) ;- (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
AT91C_US_CHMODE_REMOTE    EQU (0x3 << 14) ;- (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin.
// - -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
AT91C_US_RXRDY            EQU (0x1 <<  0) ;- (DBGU) RXRDY Interrupt
AT91C_US_TXRDY            EQU (0x1 <<  1) ;- (DBGU) TXRDY Interrupt
AT91C_US_ENDRX            EQU (0x1 <<  3) ;- (DBGU) End of Receive Transfer Interrupt
AT91C_US_ENDTX            EQU (0x1 <<  4) ;- (DBGU) End of Transmit Interrupt
AT91C_US_OVRE             EQU (0x1 <<  5) ;- (DBGU) Overrun Interrupt
AT91C_US_FRAME            EQU (0x1 <<  6) ;- (DBGU) Framing Error Interrupt
AT91C_US_PARE             EQU (0x1 <<  7) ;- (DBGU) Parity Error Interrupt
AT91C_US_TXEMPTY          EQU (0x1 <<  9) ;- (DBGU) TXEMPTY Interrupt
AT91C_US_TXBUFE           EQU (0x1 << 11) ;- (DBGU) TXBUFE Interrupt
AT91C_US_RXBUFF           EQU (0x1 << 12) ;- (DBGU) RXBUFF Interrupt
AT91C_US_COMM_TX          EQU (0x1 << 30) ;- (DBGU) COMM_TX Interrupt
AT91C_US_COMM_RX          EQU (0x1 << 31) ;- (DBGU) COMM_RX Interrupt
// - -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// - -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// - -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
// - -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
AT91C_US_FORCE_NTRST      EQU (0x1 <<  0) ;- (DBGU) Force NTRST in JTAG

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
// - *****************************************************************************
// - -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
AT91C_AIC_PRIOR           EQU (0x7 <<  0) ;- (AIC) Priority Level
AT91C_AIC_PRIOR_LOWEST    EQU (0x0) ;- (AIC) Lowest priority level
AT91C_AIC_PRIOR_HIGHEST   EQU (0x7) ;- (AIC) Highest priority level
AT91C_AIC_SRCTYPE         EQU (0x3 <<  5) ;- (AIC) Interrupt Source Type
AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE EQU (0x0 <<  5) ;- (AIC) Internal Sources Code Label Level Sensitive
AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED EQU (0x1 <<  5) ;- (AIC) Internal Sources Code Label Edge triggered
AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL EQU (0x2 <<  5) ;- (AIC) External Sources Code Label High-level Sensitive
AT91C_AIC_SRCTYPE_EXT_POSITIVE_EDGE EQU (0x3 <<  5) ;- (AIC) External Sources Code Label Positive Edge triggered
// - -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
AT91C_AIC_NFIQ            EQU (0x1 <<  0) ;- (AIC) NFIQ Status
AT91C_AIC_NIRQ            EQU (0x1 <<  1) ;- (AIC) NIRQ Status
// - -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
AT91C_AIC_DCR_PROT        EQU (0x1 <<  0) ;- (AIC) Protection Mode
AT91C_AIC_DCR_GMSK        EQU (0x1 <<  1) ;- (AIC) General Mask

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
// - *****************************************************************************

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Clock Generator Controler
// - *****************************************************************************
// - -------- CKGR_MOR : (CKGR Offset: 0x0) Main Oscillator Register -------- 
AT91C_CKGR_MOSCEN         EQU (0x1 <<  0) ;- (CKGR) Main Oscillator Enable
AT91C_CKGR_OSCBYPASS      EQU (0x1 <<  1) ;- (CKGR) Main Oscillator Bypass
AT91C_CKGR_OSCOUNT        EQU (0xFF <<  8) ;- (CKGR) Main Oscillator Start-up Time
// - -------- CKGR_MCFR : (CKGR Offset: 0x4) Main Clock Frequency Register -------- 
AT91C_CKGR_MAINF          EQU (0xFFFF <<  0) ;- (CKGR) Main Clock Frequency
AT91C_CKGR_MAINRDY        EQU (0x1 << 16) ;- (CKGR) Main Clock Ready
// - -------- CKGR_PLLAR : (CKGR Offset: 0x8) PLL A Register -------- 
AT91C_CKGR_DIVA           EQU (0xFF <<  0) ;- (CKGR) Divider A Selected
AT91C_CKGR_DIVA_0         EQU (0x0) ;- (CKGR) Divider A output is 0
AT91C_CKGR_DIVA_BYPASS    EQU (0x1) ;- (CKGR) Divider A is bypassed
AT91C_CKGR_PLLACOUNT      EQU (0x3F <<  8) ;- (CKGR) PLL A Counter
AT91C_CKGR_OUTA           EQU (0x3 << 14) ;- (CKGR) PLL A Output Frequency Range
AT91C_CKGR_OUTA_0         EQU (0x0 << 14) ;- (CKGR) Please refer to the PLLA datasheet
AT91C_CKGR_OUTA_1         EQU (0x1 << 14) ;- (CKGR) Please refer to the PLLA datasheet
AT91C_CKGR_OUTA_2         EQU (0x2 << 14) ;- (CKGR) Please refer to the PLLA datasheet
AT91C_CKGR_OUTA_3         EQU (0x3 << 14) ;- (CKGR) Please refer to the PLLA datasheet
AT91C_CKGR_MULA           EQU (0x7FF << 16) ;- (CKGR) PLL A Multiplier
AT91C_CKGR_SRCA           EQU (0x1 << 29) ;- (CKGR) 
// - -------- CKGR_PLLBR : (CKGR Offset: 0xc) PLL B Register -------- 
AT91C_CKGR_DIVB           EQU (0xFF <<  0) ;- (CKGR) Divider B Selected
AT91C_CKGR_DIVB_0         EQU (0x0) ;- (CKGR) Divider B output is 0
AT91C_CKGR_DIVB_BYPASS    EQU (0x1) ;- (CKGR) Divider B is bypassed
AT91C_CKGR_PLLBCOUNT      EQU (0x3F <<  8) ;- (CKGR) PLL B Counter
AT91C_CKGR_OUTB           EQU (0x3 << 14) ;- (CKGR) PLL B Output Frequency Range
AT91C_CKGR_OUTB_0         EQU (0x0 << 14) ;- (CKGR) Please refer to the PLLB datasheet
AT91C_CKGR_OUTB_1         EQU (0x1 << 14) ;- (CKGR) Please refer to the PLLB datasheet
AT91C_CKGR_OUTB_2         EQU (0x2 << 14) ;- (CKGR) Please refer to the PLLB datasheet
AT91C_CKGR_OUTB_3         EQU (0x3 << 14) ;- (CKGR) Please refer to the PLLB datasheet
AT91C_CKGR_MULB           EQU (0x7FF << 16) ;- (CKGR) PLL B Multiplier
AT91C_CKGR_USBDIV         EQU (0x3 << 28) ;- (CKGR) Divider for USB Clocks
AT91C_CKGR_USBDIV_0       EQU (0x0 << 28) ;- (CKGR) Divider output is PLL clock output
AT91C_CKGR_USBDIV_1       EQU (0x1 << 28) ;- (CKGR) Divider output is PLL clock output divided by 2
AT91C_CKGR_USBDIV_2       EQU (0x2 << 28) ;- (CKGR) Divider output is PLL clock output divided by 4

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Power Management Controler
// - *****************************************************************************
// - -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
AT91C_PMC_PCK             EQU (0x1 <<  0) ;- (PMC) Processor Clock
AT91C_PMC_OTG             EQU (0x1 <<  5) ;- (PMC) USB OTG Clock
AT91C_PMC_UHP             EQU (0x1 <<  6) ;- (PMC) USB Host Port Clock
AT91C_PMC_UDP             EQU (0x1 <<  7) ;- (PMC) USB Device Port Clock
AT91C_PMC_PCK0            EQU (0x1 <<  8) ;- (PMC) Programmable Clock Output
AT91C_PMC_PCK1            EQU (0x1 <<  9) ;- (PMC) Programmable Clock Output
AT91C_PMC_PCK2            EQU (0x1 << 10) ;- (PMC) Programmable Clock Output
AT91C_PMC_PCK3            EQU (0x1 << 11) ;- (PMC) Programmable Clock Output
// - -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
// - -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
// - -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
// - -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
// - -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
// - -------- CKGR_PLLBR : (PMC Offset: 0x2c) PLL B Register -------- 
// - -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
AT91C_PMC_CSS             EQU (0x3 <<  0) ;- (PMC) Programmable Clock Selection
AT91C_PMC_CSS_SLOW_CLK    EQU (0x0) ;- (PMC) Slow Clock is selected
AT91C_PMC_CSS_MAIN_CLK    EQU (0x1) ;- (PMC) Main Clock is selected
AT91C_PMC_CSS_PLLA_CLK    EQU (0x2) ;- (PMC) Clock from PLL A is selected
AT91C_PMC_CSS_PLLB_CLK    EQU (0x3) ;- (PMC) Clock from PLL B is selected
AT91C_PMC_PRES            EQU (0x7 <<  2) ;- (PMC) Programmable Clock Prescaler
AT91C_PMC_PRES_CLK        EQU (0x0 <<  2) ;- (PMC) Selected clock
AT91C_PMC_PRES_CLK_2      EQU (0x1 <<  2) ;- (PMC) Selected clock divided by 2
AT91C_PMC_PRES_CLK_4      EQU (0x2 <<  2) ;- (PMC) Selected clock divided by 4
AT91C_PMC_PRES_CLK_8      EQU (0x3 <<  2) ;- (PMC) Selected clock divided by 8
AT91C_PMC_PRES_CLK_16     EQU (0x4 <<  2) ;- (PMC) Selected clock divided by 16
AT91C_PMC_PRES_CLK_32     EQU (0x5 <<  2) ;- (PMC) Selected clock divided by 32
AT91C_PMC_PRES_CLK_64     EQU (0x6 <<  2) ;- (PMC) Selected clock divided by 64
AT91C_PMC_MDIV            EQU (0x3 <<  8) ;- (PMC) Master Clock Division
AT91C_PMC_MDIV_1          EQU (0x0 <<  8) ;- (PMC) The master clock and the processor clock are the same
AT91C_PMC_MDIV_2          EQU (0x1 <<  8) ;- (PMC) The processor clock is twice as fast as the master clock
AT91C_PMC_MDIV_3          EQU (0x2 <<  8) ;- (PMC) The processor clock is four times faster than the master clock
// - -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
// - -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
AT91C_PMC_MOSCS           EQU (0x1 <<  0) ;- (PMC) MOSC Status/Enable/Disable/Mask
AT91C_PMC_LOCKA           EQU (0x1 <<  1) ;- (PMC) PLL A Status/Enable/Disable/Mask
AT91C_PMC_LOCKB           EQU (0x1 <<  2) ;- (PMC) PLL B Status/Enable/Disable/Mask
AT91C_PMC_MCKRDY          EQU (0x1 <<  3) ;- (PMC) Master Clock Status/Enable/Disable/Mask
AT91C_PMC_PCK0RDY         EQU (0x1 <<  8) ;- (PMC) PCK0_RDY Status/Enable/Disable/Mask
AT91C_PMC_PCK1RDY         EQU (0x1 <<  9) ;- (PMC) PCK1_RDY Status/Enable/Disable/Mask
AT91C_PMC_PCK2RDY         EQU (0x1 << 10) ;- (PMC) PCK2_RDY Status/Enable/Disable/Mask
AT91C_PMC_PCK3RDY         EQU (0x1 << 11) ;- (PMC) PCK3_RDY Status/Enable/Disable/Mask
// - -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
// - -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
// - -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Reset Controller Interface
// - *****************************************************************************
// - -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- 
AT91C_RSTC_PROCRST        EQU (0x1 <<  0) ;- (RSTC) Processor Reset
AT91C_RSTC_ICERST         EQU (0x1 <<  1) ;- (RSTC) ICE Interface Reset
AT91C_RSTC_PERRST         EQU (0x1 <<  2) ;- (RSTC) Peripheral Reset
AT91C_RSTC_EXTRST         EQU (0x1 <<  3) ;- (RSTC) External Reset
AT91C_RSTC_KEY            EQU (0xFF << 24) ;- (RSTC) Password
// - -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- 
AT91C_RSTC_URSTS          EQU (0x1 <<  0) ;- (RSTC) User Reset Status
AT91C_RSTC_RSTTYP         EQU (0x7 <<  8) ;- (RSTC) Reset Type
AT91C_RSTC_RSTTYP_GENERAL EQU (0x0 <<  8) ;- (RSTC) General reset. Both VDDCORE and VDDBU rising.
AT91C_RSTC_RSTTYP_WAKEUP  EQU (0x1 <<  8) ;- (RSTC) WakeUp Reset. VDDCORE rising.
AT91C_RSTC_RSTTYP_WATCHDOG EQU (0x2 <<  8) ;- (RSTC) Watchdog Reset. Watchdog overflow occured.
AT91C_RSTC_RSTTYP_SOFTWARE EQU (0x3 <<  8) ;- (RSTC) Software Reset. Processor reset required by the software.
AT91C_RSTC_RSTTYP_USER    EQU (0x4 <<  8) ;- (RSTC) User Reset. NRST pin detected low.
AT91C_RSTC_NRSTL          EQU (0x1 << 16) ;- (RSTC) NRST pin level
AT91C_RSTC_SRCMP          EQU (0x1 << 17) ;- (RSTC) Software Reset Command in Progress.
// - -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
AT91C_RSTC_URSTEN         EQU (0x1 <<  0) ;- (RSTC) User Reset Enable
AT91C_RSTC_URSTIEN        EQU (0x1 <<  4) ;- (RSTC) User Reset Interrupt Enable
AT91C_RSTC_ERSTL          EQU (0xF <<  8) ;- (RSTC) User Reset Enable

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Shut Down Controller Interface
// - *****************************************************************************
// - -------- SHDWC_SHCR : (SHDWC Offset: 0x0) Shut Down Control Register -------- 
AT91C_SHDWC_SHDW          EQU (0x1 <<  0) ;- (SHDWC) Processor Reset
AT91C_SHDWC_KEY           EQU (0xFF << 24) ;- (SHDWC) Shut down KEY Password
// - -------- SHDWC_SHMR : (SHDWC Offset: 0x4) Shut Down Mode Register -------- 
AT91C_SHDWC_WKMODE0       EQU (0x3 <<  0) ;- (SHDWC) Wake Up 0 Mode Selection
AT91C_SHDWC_WKMODE0_NONE  EQU (0x0) ;- (SHDWC) None. No detection is performed on the wake up input.
AT91C_SHDWC_WKMODE0_HIGH  EQU (0x1) ;- (SHDWC) High Level.
AT91C_SHDWC_WKMODE0_LOW   EQU (0x2) ;- (SHDWC) Low Level.
AT91C_SHDWC_WKMODE0_ANYLEVEL EQU (0x3) ;- (SHDWC) Any level change.
AT91C_SHDWC_CPTWK0        EQU (0xF <<  4) ;- (SHDWC) Counter On Wake Up 0
AT91C_SHDWC_RTTWKEN       EQU (0x1 << 16) ;- (SHDWC) Real Time Timer Wake Up Enable
// - -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
AT91C_SHDWC_WAKEUP0       EQU (0x1 <<  0) ;- (SHDWC) Wake Up 0 Status
AT91C_SHDWC_RTTWK         EQU (0x1 << 16) ;- (SHDWC) Real Time Timer wake Up

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
// - *****************************************************************************
// - -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
AT91C_RTTC_RTPRES         EQU (0xFFFF <<  0) ;- (RTTC) Real-time Timer Prescaler Value
AT91C_RTTC_ALMIEN         EQU (0x1 << 16) ;- (RTTC) Alarm Interrupt Enable
AT91C_RTTC_RTTINCIEN      EQU (0x1 << 17) ;- (RTTC) Real Time Timer Increment Interrupt Enable
AT91C_RTTC_RTTRST         EQU (0x1 << 18) ;- (RTTC) Real Time Timer Restart
// - -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
AT91C_RTTC_ALMV           EQU (0x0 <<  0) ;- (RTTC) Alarm Value
// - -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
AT91C_RTTC_CRTV           EQU (0x0 <<  0) ;- (RTTC) Current Real-time Value
// - -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
AT91C_RTTC_ALMS           EQU (0x1 <<  0) ;- (RTTC) Real-time Alarm Status
AT91C_RTTC_RTTINC         EQU (0x1 <<  1) ;- (RTTC) Real-time Timer Increment

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface
// - *****************************************************************************
// - -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- 
AT91C_PITC_PIV            EQU (0xFFFFF <<  0) ;- (PITC) Periodic Interval Value
AT91C_PITC_PITEN          EQU (0x1 << 24) ;- (PITC) Periodic Interval Timer Enabled
AT91C_PITC_PITIEN         EQU (0x1 << 25) ;- (PITC) Periodic Interval Timer Interrupt Enable
// - -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- 
AT91C_PITC_PITS           EQU (0x1 <<  0) ;- (PITC) Periodic Interval Timer Status
// - -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- 
AT91C_PITC_CPIV           EQU (0xFFFFF <<  0) ;- (PITC) Current Periodic Interval Value
AT91C_PITC_PICNT          EQU (0xFFF << 20) ;- (PITC) Periodic Interval Counter
// - -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
// - *****************************************************************************
// - -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- 
AT91C_WDTC_WDRSTT         EQU (0x1 <<  0) ;- (WDTC) Watchdog Restart
AT91C_WDTC_KEY            EQU (0xFF << 24) ;- (WDTC) Watchdog KEY Password
// - -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- 
AT91C_WDTC_WDV            EQU (0xFFF <<  0) ;- (WDTC) Watchdog Timer Restart
AT91C_WDTC_WDFIEN         EQU (0x1 << 12) ;- (WDTC) Watchdog Fault Interrupt Enable
AT91C_WDTC_WDRSTEN        EQU (0x1 << 13) ;- (WDTC) Watchdog Reset Enable
AT91C_WDTC_WDRPROC        EQU (0x1 << 14) ;- (WDTC) Watchdog Timer Restart
AT91C_WDTC_WDDIS          EQU (0x1 << 15) ;- (WDTC) Watchdog Disable
AT91C_WDTC_WDD            EQU (0xFFF << 16) ;- (WDTC) Watchdog Delta Value
AT91C_WDTC_WDDBGHLT       EQU (0x1 << 28) ;- (WDTC) Watchdog Debug Halt
AT91C_WDTC_WDIDLEHLT      EQU (0x1 << 29) ;- (WDTC) Watchdog Idle Halt
// - -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- 
AT91C_WDTC_WDUNF          EQU (0x1 <<  0) ;- (WDTC) Watchdog Underflow
AT91C_WDTC_WDERR          EQU (0x1 <<  1) ;- (WDTC) Watchdog Error

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
// - *****************************************************************************
// - -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
AT91C_TC_CLKEN            EQU (0x1 <<  0) ;- (TC) Counter Clock Enable Command
AT91C_TC_CLKDIS           EQU (0x1 <<  1) ;- (TC) Counter Clock Disable Command
AT91C_TC_SWTRG            EQU (0x1 <<  2) ;- (TC) Software Trigger Command
// - -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
AT91C_TC_CLKS             EQU (0x7 <<  0) ;- (TC) Clock Selection
AT91C_TC_CLKS_TIMER_DIV1_CLOCK EQU (0x0) ;- (TC) Clock selected: TIMER_DIV1_CLOCK
AT91C_TC_CLKS_TIMER_DIV2_CLOCK EQU (0x1) ;- (TC) Clock selected: TIMER_DIV2_CLOCK
AT91C_TC_CLKS_TIMER_DIV3_CLOCK EQU (0x2) ;- (TC) Clock selected: TIMER_DIV3_CLOCK
AT91C_TC_CLKS_TIMER_DIV4_CLOCK EQU (0x3) ;- (TC) Clock selected: TIMER_DIV4_CLOCK
AT91C_TC_CLKS_TIMER_DIV5_CLOCK EQU (0x4) ;- (TC) Clock selected: TIMER_DIV5_CLOCK
AT91C_TC_CLKS_XC0         EQU (0x5) ;- (TC) Clock selected: XC0
AT91C_TC_CLKS_XC1         EQU (0x6) ;- (TC) Clock selected: XC1
AT91C_TC_CLKS_XC2         EQU (0x7) ;- (TC) Clock selected: XC2
AT91C_TC_CLKI             EQU (0x1 <<  3) ;- (TC) Clock Invert
AT91C_TC_BURST            EQU (0x3 <<  4) ;- (TC) Burst Signal Selection
AT91C_TC_BURST_NONE       EQU (0x0 <<  4) ;- (TC) The clock is not gated by an external signal
AT91C_TC_BURST_XC0        EQU (0x1 <<  4) ;- (TC) XC0 is ANDed with the selected clock
AT91C_TC_BURST_XC1        EQU (0x2 <<  4) ;- (TC) XC1 is ANDed with the selected clock
AT91C_TC_BURST_XC2        EQU (0x3 <<  4) ;- (TC) XC2 is ANDed with the selected clock
AT91C_TC_CPCSTOP          EQU (0x1 <<  6) ;- (TC) Counter Clock Stopped with RC Compare
AT91C_TC_LDBSTOP          EQU (0x1 <<  6) ;- (TC) Counter Clock Stopped with RB Loading
AT91C_TC_CPCDIS           EQU (0x1 <<  7) ;- (TC) Counter Clock Disable with RC Compare
AT91C_TC_LDBDIS           EQU (0x1 <<  7) ;- (TC) Counter Clock Disabled with RB Loading
AT91C_TC_ETRGEDG          EQU (0x3 <<  8) ;- (TC) External Trigger Edge Selection
AT91C_TC_ETRGEDG_NONE     EQU (0x0 <<  8) ;- (TC) Edge: None
AT91C_TC_ETRGEDG_RISING   EQU (0x1 <<  8) ;- (TC) Edge: rising edge
AT91C_TC_ETRGEDG_FALLING  EQU (0x2 <<  8) ;- (TC) Edge: falling edge
AT91C_TC_ETRGEDG_BOTH     EQU (0x3 <<  8) ;- (TC) Edge: each edge
AT91C_TC_EEVTEDG          EQU (0x3 <<  8) ;- (TC) External Event Edge Selection
AT91C_TC_EEVTEDG_NONE     EQU (0x0 <<  8) ;- (TC) Edge: None
AT91C_TC_EEVTEDG_RISING   EQU (0x1 <<  8) ;- (TC) Edge: rising edge
AT91C_TC_EEVTEDG_FALLING  EQU (0x2 <<  8) ;- (TC) Edge: falling edge
AT91C_TC_EEVTEDG_BOTH     EQU (0x3 <<  8) ;- (TC) Edge: each edge
AT91C_TC_EEVT             EQU (0x3 << 10) ;- (TC) External Event  Selection
AT91C_TC_EEVT_TIOB        EQU (0x0 << 10) ;- (TC) Signal selected as external event: TIOB TIOB direction: input
AT91C_TC_EEVT_XC0         EQU (0x1 << 10) ;- (TC) Signal selected as external event: XC0 TIOB direction: output
AT91C_TC_EEVT_XC1         EQU (0x2 << 10) ;- (TC) Signal selected as external event: XC1 TIOB direction: output
AT91C_TC_EEVT_XC2         EQU (0x3 << 10) ;- (TC) Signal selected as external event: XC2 TIOB direction: output
AT91C_TC_ABETRG           EQU (0x1 << 10) ;- (TC) TIOA or TIOB External Trigger Selection
AT91C_TC_ENETRG           EQU (0x1 << 12) ;- (TC) External Event Trigger enable
AT91C_TC_WAVESEL          EQU (0x3 << 13) ;- (TC) Waveform  Selection
AT91C_TC_WAVESEL_UP       EQU (0x0 << 13) ;- (TC) UP mode without atomatic trigger on RC Compare
AT91C_TC_WAVESEL_UPDOWN   EQU (0x1 << 13) ;- (TC) UPDOWN mode without automatic trigger on RC Compare
AT91C_TC_WAVESEL_UP_AUTO  EQU (0x2 << 13) ;- (TC) UP mode with automatic trigger on RC Compare
AT91C_TC_WAVESEL_UPDOWN_AUTO EQU (0x3 << 13) ;- (TC) UPDOWN mode with automatic trigger on RC Compare
AT91C_TC_CPCTRG           EQU (0x1 << 14) ;- (TC) RC Compare Trigger Enable
AT91C_TC_WAVE             EQU (0x1 << 15) ;- (TC) 
AT91C_TC_ACPA             EQU (0x3 << 16) ;- (TC) RA Compare Effect on TIOA
AT91C_TC_ACPA_NONE        EQU (0x0 << 16) ;- (TC) Effect: none
AT91C_TC_ACPA_SET         EQU (0x1 << 16) ;- (TC) Effect: set
AT91C_TC_ACPA_CLEAR       EQU (0x2 << 16) ;- (TC) Effect: clear
AT91C_TC_ACPA_TOGGLE      EQU (0x3 << 16) ;- (TC) Effect: toggle
AT91C_TC_LDRA             EQU (0x3 << 16) ;- (TC) RA Loading Selection
AT91C_TC_LDRA_NONE        EQU (0x0 << 16) ;- (TC) Edge: None
AT91C_TC_LDRA_RISING      EQU (0x1 << 16) ;- (TC) Edge: rising edge of TIOA
AT91C_TC_LDRA_FALLING     EQU (0x2 << 16) ;- (TC) Edge: falling edge of TIOA
AT91C_TC_LDRA_BOTH        EQU (0x3 << 16) ;- (TC) Edge: each edge of TIOA
AT91C_TC_ACPC             EQU (0x3 << 18) ;- (TC) RC Compare Effect on TIOA
AT91C_TC_ACPC_NONE        EQU (0x0 << 18) ;- (TC) Effect: none
AT91C_TC_ACPC_SET         EQU (0x1 << 18) ;- (TC) Effect: set
AT91C_TC_ACPC_CLEAR       EQU (0x2 << 18) ;- (TC) Effect: clear
AT91C_TC_ACPC_TOGGLE      EQU (0x3 << 18) ;- (TC) Effect: toggle
AT91C_TC_LDRB             EQU (0x3 << 18) ;- (TC) RB Loading Selection
AT91C_TC_LDRB_NONE        EQU (0x0 << 18) ;- (TC) Edge: None
AT91C_TC_LDRB_RISING      EQU (0x1 << 18) ;- (TC) Edge: rising edge of TIOA
AT91C_TC_LDRB_FALLING     EQU (0x2 << 18) ;- (TC) Edge: falling edge of TIOA
AT91C_TC_LDRB_BOTH        EQU (0x3 << 18) ;- (TC) Edge: each edge of TIOA
AT91C_TC_AEEVT            EQU (0x3 << 20) ;- (TC) External Event Effect on TIOA
AT91C_TC_AEEVT_NONE       EQU (0x0 << 20) ;- (TC) Effect: none
AT91C_TC_AEEVT_SET        EQU (0x1 << 20) ;- (TC) Effect: set
AT91C_TC_AEEVT_CLEAR      EQU (0x2 << 20) ;- (TC) Effect: clear
AT91C_TC_AEEVT_TOGGLE     EQU (0x3 << 20) ;- (TC) Effect: toggle
AT91C_TC_ASWTRG           EQU (0x3 << 22) ;- (TC) Software Trigger Effect on TIOA
AT91C_TC_ASWTRG_NONE      EQU (0x0 << 22) ;- (TC) Effect: none
AT91C_TC_ASWTRG_SET       EQU (0x1 << 22) ;- (TC) Effect: set
AT91C_TC_ASWTRG_CLEAR     EQU (0x2 << 22) ;- (TC) Effect: clear
AT91C_TC_ASWTRG_TOGGLE    EQU (0x3 << 22) ;- (TC) Effect: toggle
AT91C_TC_BCPB             EQU (0x3 << 24) ;- (TC) RB Compare Effect on TIOB
AT91C_TC_BCPB_NONE        EQU (0x0 << 24) ;- (TC) Effect: none
AT91C_TC_BCPB_SET         EQU (0x1 << 24) ;- (TC) Effect: set
AT91C_TC_BCPB_CLEAR       EQU (0x2 << 24) ;- (TC) Effect: clear
AT91C_TC_BCPB_TOGGLE      EQU (0x3 << 24) ;- (TC) Effect: toggle
AT91C_TC_BCPC             EQU (0x3 << 26) ;- (TC) RC Compare Effect on TIOB
AT91C_TC_BCPC_NONE        EQU (0x0 << 26) ;- (TC) Effect: none
AT91C_TC_BCPC_SET         EQU (0x1 << 26) ;- (TC) Effect: set
AT91C_TC_BCPC_CLEAR       EQU (0x2 << 26) ;- (TC) Effect: clear
AT91C_TC_BCPC_TOGGLE      EQU (0x3 << 26) ;- (TC) Effect: toggle
AT91C_TC_BEEVT            EQU (0x3 << 28) ;- (TC) External Event Effect on TIOB
AT91C_TC_BEEVT_NONE       EQU (0x0 << 28) ;- (TC) Effect: none
AT91C_TC_BEEVT_SET        EQU (0x1 << 28) ;- (TC) Effect: set
AT91C_TC_BEEVT_CLEAR      EQU (0x2 << 28) ;- (TC) Effect: clear
AT91C_TC_BEEVT_TOGGLE     EQU (0x3 << 28) ;- (TC) Effect: toggle
AT91C_TC_BSWTRG           EQU (0x3 << 30) ;- (TC) Software Trigger Effect on TIOB
AT91C_TC_BSWTRG_NONE      EQU (0x0 << 30) ;- (TC) Effect: none
AT91C_TC_BSWTRG_SET       EQU (0x1 << 30) ;- (TC) Effect: set
AT91C_TC_BSWTRG_CLEAR     EQU (0x2 << 30) ;- (TC) Effect: clear
AT91C_TC_BSWTRG_TOGGLE    EQU (0x3 << 30) ;- (TC) Effect: toggle
// - -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
AT91C_TC_COVFS            EQU (0x1 <<  0) ;- (TC) Counter Overflow
AT91C_TC_LOVRS            EQU (0x1 <<  1) ;- (TC) Load Overrun
AT91C_TC_CPAS             EQU (0x1 <<  2) ;- (TC) RA Compare
AT91C_TC_CPBS             EQU (0x1 <<  3) ;- (TC) RB Compare
AT91C_TC_CPCS             EQU (0x1 <<  4) ;- (TC) RC Compare
AT91C_TC_LDRAS            EQU (0x1 <<  5) ;- (TC) RA Loading
AT91C_TC_LDRBS            EQU (0x1 <<  6) ;- (TC) RB Loading
AT91C_TC_ETRGS            EQU (0x1 <<  7) ;- (TC) External Trigger
AT91C_TC_CLKSTA           EQU (0x1 << 16) ;- (TC) Clock Enabling
AT91C_TC_MTIOA            EQU (0x1 << 17) ;- (TC) TIOA Mirror
AT91C_TC_MTIOB            EQU (0x1 << 18) ;- (TC) TIOA Mirror
// - -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
// - -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
// - -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Timer Counter Interface
// - *****************************************************************************
// - -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
AT91C_TCB_SYNC            EQU (0x1 <<  0) ;- (TCB) Synchro Command
// - -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
AT91C_TCB_TC0XC0S         EQU (0x3 <<  0) ;- (TCB) External Clock Signal 0 Selection
AT91C_TCB_TC0XC0S_TCLK0   EQU (0x0) ;- (TCB) TCLK0 connected to XC0
AT91C_TCB_TC0XC0S_NONE    EQU (0x1) ;- (TCB) None signal connected to XC0
AT91C_TCB_TC0XC0S_TIOA1   EQU (0x2) ;- (TCB) TIOA1 connected to XC0
AT91C_TCB_TC0XC0S_TIOA2   EQU (0x3) ;- (TCB) TIOA2 connected to XC0
AT91C_TCB_TC1XC1S         EQU (0x3 <<  2) ;- (TCB) External Clock Signal 1 Selection
AT91C_TCB_TC1XC1S_TCLK1   EQU (0x0 <<  2) ;- (TCB) TCLK1 connected to XC1
AT91C_TCB_TC1XC1S_NONE    EQU (0x1 <<  2) ;- (TCB) None signal connected to XC1
AT91C_TCB_TC1XC1S_TIOA0   EQU (0x2 <<  2) ;- (TCB) TIOA0 connected to XC1
AT91C_TCB_TC1XC1S_TIOA2   EQU (0x3 <<  2) ;- (TCB) TIOA2 connected to XC1
AT91C_TCB_TC2XC2S         EQU (0x3 <<  4) ;- (TCB) External Clock Signal 2 Selection
AT91C_TCB_TC2XC2S_TCLK2   EQU (0x0 <<  4) ;- (TCB) TCLK2 connected to XC2
AT91C_TCB_TC2XC2S_NONE    EQU (0x1 <<  4) ;- (TCB) None signal connected to XC2
AT91C_TCB_TC2XC2S_TIOA0   EQU (0x2 <<  4) ;- (TCB) TIOA0 connected to XC2
AT91C_TCB_TC2XC2S_TIOA1   EQU (0x3 <<  4) ;- (TCB) TIOA2 connected to XC2

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Multimedia Card Interface
// - *****************************************************************************
// - -------- MCI_CR : (MCI Offset: 0x0) MCI Control Register -------- 
AT91C_MCI_MCIEN           EQU (0x1 <<  0) ;- (MCI) Multimedia Interface Enable
AT91C_MCI_MCIDIS          EQU (0x1 <<  1) ;- (MCI) Multimedia Interface Disable
AT91C_MCI_PWSEN           EQU (0x1 <<  2) ;- (MCI) Power Save Mode Enable
AT91C_MCI_PWSDIS          EQU (0x1 <<  3) ;- (MCI) Power Save Mode Disable
AT91C_MCI_SWRST           EQU (0x1 <<  7) ;- (MCI) MCI Software reset
// - -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
AT91C_MCI_CLKDIV          EQU (0xFF <<  0) ;- (MCI) Clock Divider
AT91C_MCI_PWSDIV          EQU (0x7 <<  8) ;- (MCI) Power Saving Divider
AT91C_MCI_RDPROOF         EQU (0x1 << 11) ;- (MCI) Read Proof Enable
AT91C_MCI_WRPROOF         EQU (0x1 << 12) ;- (MCI) Write Proof Enable
AT91C_MCI_PDCFBYTE        EQU (0x1 << 13) ;- (MCI) PDC Force Byte Transfer
AT91C_MCI_PDCPADV         EQU (0x1 << 14) ;- (MCI) PDC Padding Value
AT91C_MCI_PDCMODE         EQU (0x1 << 15) ;- (MCI) PDC Oriented Mode
AT91C_MCI_BLKLEN          EQU (0xFFFF << 16) ;- (MCI) Data Block Length
// - -------- MCI_DTOR : (MCI Offset: 0x8) MCI Data Timeout Register -------- 
AT91C_MCI_DTOCYC          EQU (0xF <<  0) ;- (MCI) Data Timeout Cycle Number
AT91C_MCI_DTOMUL          EQU (0x7 <<  4) ;- (MCI) Data Timeout Multiplier
AT91C_MCI_DTOMUL_1        EQU (0x0 <<  4) ;- (MCI) DTOCYC x 1
AT91C_MCI_DTOMUL_16       EQU (0x1 <<  4) ;- (MCI) DTOCYC x 16
AT91C_MCI_DTOMUL_128      EQU (0x2 <<  4) ;- (MCI) DTOCYC x 128
AT91C_MCI_DTOMUL_256      EQU (0x3 <<  4) ;- (MCI) DTOCYC x 256
AT91C_MCI_DTOMUL_1024     EQU (0x4 <<  4) ;- (MCI) DTOCYC x 1024
AT91C_MCI_DTOMUL_4096     EQU (0x5 <<  4) ;- (MCI) DTOCYC x 4096
AT91C_MCI_DTOMUL_65536    EQU (0x6 <<  4) ;- (MCI) DTOCYC x 65536
AT91C_MCI_DTOMUL_1048576  EQU (0x7 <<  4) ;- (MCI) DTOCYC x 1048576
// - -------- MCI_SDCR : (MCI Offset: 0xc) MCI SD Card Register -------- 
AT91C_MCI_SCDSEL          EQU (0x3 <<  0) ;- (MCI) SD Card Selector
AT91C_MCI_SCDBUS          EQU (0x1 <<  7) ;- (MCI) SDCard/SDIO Bus Width
// - -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
AT91C_MCI_CMDNB           EQU (0x3F <<  0) ;- (MCI) Command Number
AT91C_MCI_RSPTYP          EQU (0x3 <<  6) ;- (MCI) Response Type
AT91C_MCI_RSPTYP_NO       EQU (0x0 <<  6) ;- (MCI) No response
AT91C_MCI_RSPTYP_48       EQU (0x1 <<  6) ;- (MCI) 48-bit response
AT91C_MCI_RSPTYP_136      EQU (0x2 <<  6) ;- (MCI) 136-bit response
AT91C_MCI_SPCMD           EQU (0x7 <<  8) ;- (MCI) Special CMD
AT91C_MCI_SPCMD_NONE      EQU (0x0 <<  8) ;- (MCI) Not a special CMD
AT91C_MCI_SPCMD_INIT      EQU (0x1 <<  8) ;- (MCI) Initialization CMD
AT91C_MCI_SPCMD_SYNC      EQU (0x2 <<  8) ;- (MCI) Synchronized CMD
AT91C_MCI_SPCMD_IT_CMD    EQU (0x4 <<  8) ;- (MCI) Interrupt command
AT91C_MCI_SPCMD_IT_REP    EQU (0x5 <<  8) ;- (MCI) Interrupt response
AT91C_MCI_OPDCMD          EQU (0x1 << 11) ;- (MCI) Open Drain Command
AT91C_MCI_MAXLAT          EQU (0x1 << 12) ;- (MCI) Maximum Latency for Command to respond
AT91C_MCI_TRCMD           EQU (0x3 << 16) ;- (MCI) Transfer CMD
AT91C_MCI_TRCMD_NO        EQU (0x0 << 16) ;- (MCI) No transfer
AT91C_MCI_TRCMD_START     EQU (0x1 << 16) ;- (MCI) Start transfer
AT91C_MCI_TRCMD_STOP      EQU (0x2 << 16) ;- (MCI) Stop transfer
AT91C_MCI_TRDIR           EQU (0x1 << 18) ;- (MCI) Transfer Direction
AT91C_MCI_TRTYP           EQU (0x7 << 19) ;- (MCI) Transfer Type
AT91C_MCI_TRTYP_BLOCK     EQU (0x0 << 19) ;- (MCI) MMC/SDCard Single Block Transfer type
AT91C_MCI_TRTYP_MULTIPLE  EQU (0x1 << 19) ;- (MCI) MMC/SDCard Multiple Block transfer type
AT91C_MCI_TRTYP_STREAM    EQU (0x2 << 19) ;- (MCI) MMC Stream transfer type
AT91C_MCI_TRTYP_SDIO_BYTE EQU (0x4 << 19) ;- (MCI) SDIO Byte transfer type
AT91C_MCI_TRTYP_SDIO_BLOCK EQU (0x5 << 19) ;- (MCI) SDIO Block transfer type
AT91C_MCI_IOSPCMD         EQU (0x3 << 24) ;- (MCI) SDIO Special Command
AT91C_MCI_IOSPCMD_NONE    EQU (0x0 << 24) ;- (MCI) NOT a special command
AT91C_MCI_IOSPCMD_SUSPEND EQU (0x1 << 24) ;- (MCI) SDIO Suspend Command
AT91C_MCI_IOSPCMD_RESUME  EQU (0x2 << 24) ;- (MCI) SDIO Resume Command
// - -------- MCI_BLKR : (MCI Offset: 0x18) MCI Block Register -------- 
AT91C_MCI_BCNT            EQU (0xFFFF <<  0) ;- (MCI) MMC/SDIO Block Count / SDIO Byte Count
// - -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
AT91C_MCI_CMDRDY          EQU (0x1 <<  0) ;- (MCI) Command Ready flag
AT91C_MCI_RXRDY           EQU (0x1 <<  1) ;- (MCI) RX Ready flag
AT91C_MCI_TXRDY           EQU (0x1 <<  2) ;- (MCI) TX Ready flag
AT91C_MCI_BLKE            EQU (0x1 <<  3) ;- (MCI) Data Block Transfer Ended flag
AT91C_MCI_DTIP            EQU (0x1 <<  4) ;- (MCI) Data Transfer in Progress flag
AT91C_MCI_NOTBUSY         EQU (0x1 <<  5) ;- (MCI) Data Line Not Busy flag
AT91C_MCI_ENDRX           EQU (0x1 <<  6) ;- (MCI) End of RX Buffer flag
AT91C_MCI_ENDTX           EQU (0x1 <<  7) ;- (MCI) End of TX Buffer flag
AT91C_MCI_SDIOIRQA        EQU (0x1 <<  8) ;- (MCI) SDIO Interrupt for Slot A
AT91C_MCI_SDIOIRQB        EQU (0x1 <<  9) ;- (MCI) SDIO Interrupt for Slot B
AT91C_MCI_SDIOIRQC        EQU (0x1 << 10) ;- (MCI) SDIO Interrupt for Slot C
AT91C_MCI_SDIOIRQD        EQU (0x1 << 11) ;- (MCI) SDIO Interrupt for Slot D
AT91C_MCI_RXBUFF          EQU (0x1 << 14) ;- (MCI) RX Buffer Full flag
AT91C_MCI_TXBUFE          EQU (0x1 << 15) ;- (MCI) TX Buffer Empty flag
AT91C_MCI_RINDE           EQU (0x1 << 16) ;- (MCI) Response Index Error flag
AT91C_MCI_RDIRE           EQU (0x1 << 17) ;- (MCI) Response Direction Error flag
AT91C_MCI_RCRCE           EQU (0x1 << 18) ;- (MCI) Response CRC Error flag
AT91C_MCI_RENDE           EQU (0x1 << 19) ;- (MCI) Response End Bit Error flag
AT91C_MCI_RTOE            EQU (0x1 << 20) ;- (MCI) Response Time-out Error flag
AT91C_MCI_DCRCE           EQU (0x1 << 21) ;- (MCI) data CRC Error flag
AT91C_MCI_DTOE            EQU (0x1 << 22) ;- (MCI) Data timeout Error flag
AT91C_MCI_OVRE            EQU (0x1 << 30) ;- (MCI) Overrun flag
AT91C_MCI_UNRE            EQU (0x1 << 31) ;- (MCI) Underrun flag
// - -------- MCI_IER : (MCI Offset: 0x44) MCI Interrupt Enable Register -------- 
// - -------- MCI_IDR : (MCI Offset: 0x48) MCI Interrupt Disable Register -------- 
// - -------- MCI_IMR : (MCI Offset: 0x4c) MCI Interrupt Mask Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Two-wire Interface
// - *****************************************************************************
// - -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- 
AT91C_TWI_START           EQU (0x1 <<  0) ;- (TWI) Send a START Condition
AT91C_TWI_STOP            EQU (0x1 <<  1) ;- (TWI) Send a STOP Condition
AT91C_TWI_MSEN            EQU (0x1 <<  2) ;- (TWI) TWI Master Transfer Enabled
AT91C_TWI_MSDIS           EQU (0x1 <<  3) ;- (TWI) TWI Master Transfer Disabled
AT91C_TWI_SVEN            EQU (0x1 <<  4) ;- (TWI) TWI Slave mode Enabled
AT91C_TWI_SVDIS           EQU (0x1 <<  5) ;- (TWI) TWI Slave mode Disabled
AT91C_TWI_SWRST           EQU (0x1 <<  7) ;- (TWI) Software Reset
// - -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
AT91C_TWI_IADRSZ          EQU (0x3 <<  8) ;- (TWI) Internal Device Address Size
AT91C_TWI_IADRSZ_NO       EQU (0x0 <<  8) ;- (TWI) No internal device address
AT91C_TWI_IADRSZ_1_BYTE   EQU (0x1 <<  8) ;- (TWI) One-byte internal device address
AT91C_TWI_IADRSZ_2_BYTE   EQU (0x2 <<  8) ;- (TWI) Two-byte internal device address
AT91C_TWI_IADRSZ_3_BYTE   EQU (0x3 <<  8) ;- (TWI) Three-byte internal device address
AT91C_TWI_MREAD           EQU (0x1 << 12) ;- (TWI) Master Read Direction
AT91C_TWI_DADR            EQU (0x7F << 16) ;- (TWI) Device Address
// - -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- 
AT91C_TWI_SADR            EQU (0x7F << 16) ;- (TWI) Slave Address
// - -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
AT91C_TWI_CLDIV           EQU (0xFF <<  0) ;- (TWI) Clock Low Divider
AT91C_TWI_CHDIV           EQU (0xFF <<  8) ;- (TWI) Clock High Divider
AT91C_TWI_CKDIV           EQU (0x7 << 16) ;- (TWI) Clock Divider
// - -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
AT91C_TWI_TXCOMP_SLAVE    EQU (0x1 <<  0) ;- (TWI) Transmission Completed
AT91C_TWI_TXCOMP_MASTER   EQU (0x1 <<  0) ;- (TWI) Transmission Completed
AT91C_TWI_RXRDY           EQU (0x1 <<  1) ;- (TWI) Receive holding register ReaDY
AT91C_TWI_TXRDY_MASTER    EQU (0x1 <<  2) ;- (TWI) Transmit holding register ReaDY
AT91C_TWI_TXRDY_SLAVE     EQU (0x1 <<  2) ;- (TWI) Transmit holding register ReaDY
AT91C_TWI_SVREAD          EQU (0x1 <<  3) ;- (TWI) Slave READ (used only in Slave mode)
AT91C_TWI_SVACC           EQU (0x1 <<  4) ;- (TWI) Slave ACCess (used only in Slave mode)
AT91C_TWI_GACC            EQU (0x1 <<  5) ;- (TWI) General Call ACcess (used only in Slave mode)
AT91C_TWI_OVRE            EQU (0x1 <<  6) ;- (TWI) Overrun Error (used only in Master and Multi-master mode)
AT91C_TWI_NACK_SLAVE      EQU (0x1 <<  8) ;- (TWI) Not Acknowledged
AT91C_TWI_NACK_MASTER     EQU (0x1 <<  8) ;- (TWI) Not Acknowledged
AT91C_TWI_ARBLST_MULTI_MASTER EQU (0x1 <<  9) ;- (TWI) Arbitration Lost (used only in Multimaster mode)
AT91C_TWI_SCLWS           EQU (0x1 << 10) ;- (TWI) Clock Wait State (used only in Slave mode)
AT91C_TWI_EOSACC          EQU (0x1 << 11) ;- (TWI) End Of Slave ACCess (used only in Slave mode)
AT91C_TWI_ENDRX           EQU (0x1 << 12) ;- (TWI) End of Receiver Transfer
AT91C_TWI_ENDTX           EQU (0x1 << 13) ;- (TWI) End of Receiver Transfer
AT91C_TWI_RXBUFF          EQU (0x1 << 14) ;- (TWI) RXBUFF Interrupt
AT91C_TWI_TXBUFE          EQU (0x1 << 15) ;- (TWI) TXBUFE Interrupt
// - -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
// - -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
// - -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Usart
// - *****************************************************************************
// - -------- US_CR : (USART Offset: 0x0) Debug Unit Control Register -------- 
AT91C_US_STTBRK           EQU (0x1 <<  9) ;- (USART) Start Break
AT91C_US_STPBRK           EQU (0x1 << 10) ;- (USART) Stop Break
AT91C_US_STTTO            EQU (0x1 << 11) ;- (USART) Start Time-out
AT91C_US_SENDA            EQU (0x1 << 12) ;- (USART) Send Address
AT91C_US_RSTIT            EQU (0x1 << 13) ;- (USART) Reset Iterations
AT91C_US_RSTNACK          EQU (0x1 << 14) ;- (USART) Reset Non Acknowledge
AT91C_US_RETTO            EQU (0x1 << 15) ;- (USART) Rearm Time-out
AT91C_US_DTREN            EQU (0x1 << 16) ;- (USART) Data Terminal ready Enable
AT91C_US_DTRDIS           EQU (0x1 << 17) ;- (USART) Data Terminal ready Disable
AT91C_US_RTSEN            EQU (0x1 << 18) ;- (USART) Request to Send enable
AT91C_US_RTSDIS           EQU (0x1 << 19) ;- (USART) Request to Send Disable
// - -------- US_MR : (USART Offset: 0x4) Debug Unit Mode Register -------- 
AT91C_US_USMODE           EQU (0xF <<  0) ;- (USART) Usart mode
AT91C_US_USMODE_NORMAL    EQU (0x0) ;- (USART) Normal
AT91C_US_USMODE_RS485     EQU (0x1) ;- (USART) RS485
AT91C_US_USMODE_HWHSH     EQU (0x2) ;- (USART) Hardware Handshaking
AT91C_US_USMODE_MODEM     EQU (0x3) ;- (USART) Modem
AT91C_US_USMODE_ISO7816_0 EQU (0x4) ;- (USART) ISO7816 protocol: T = 0
AT91C_US_USMODE_ISO7816_1 EQU (0x6) ;- (USART) ISO7816 protocol: T = 1
AT91C_US_USMODE_IRDA      EQU (0x8) ;- (USART) IrDA
AT91C_US_USMODE_SWHSH     EQU (0xC) ;- (USART) Software Handshaking
AT91C_US_CLKS             EQU (0x3 <<  4) ;- (USART) Clock Selection (Baud Rate generator Input Clock
AT91C_US_CLKS_CLOCK       EQU (0x0 <<  4) ;- (USART) Clock
AT91C_US_CLKS_FDIV1       EQU (0x1 <<  4) ;- (USART) fdiv1
AT91C_US_CLKS_SLOW        EQU (0x2 <<  4) ;- (USART) slow_clock (ARM)
AT91C_US_CLKS_EXT         EQU (0x3 <<  4) ;- (USART) External (SCK)
AT91C_US_CHRL             EQU (0x3 <<  6) ;- (USART) Clock Selection (Baud Rate generator Input Clock
AT91C_US_CHRL_5_BITS      EQU (0x0 <<  6) ;- (USART) Character Length: 5 bits
AT91C_US_CHRL_6_BITS      EQU (0x1 <<  6) ;- (USART) Character Length: 6 bits
AT91C_US_CHRL_7_BITS      EQU (0x2 <<  6) ;- (USART) Character Length: 7 bits
AT91C_US_CHRL_8_BITS      EQU (0x3 <<  6) ;- (USART) Character Length: 8 bits
AT91C_US_SYNC             EQU (0x1 <<  8) ;- (USART) Synchronous Mode Select
AT91C_US_NBSTOP           EQU (0x3 << 12) ;- (USART) Number of Stop bits
AT91C_US_NBSTOP_1_BIT     EQU (0x0 << 12) ;- (USART) 1 stop bit
AT91C_US_NBSTOP_15_BIT    EQU (0x1 << 12) ;- (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits
AT91C_US_NBSTOP_2_BIT     EQU (0x2 << 12) ;- (USART) 2 stop bits
AT91C_US_MSBF             EQU (0x1 << 16) ;- (USART) Bit Order
AT91C_US_MODE9            EQU (0x1 << 17) ;- (USART) 9-bit Character length
AT91C_US_CKLO             EQU (0x1 << 18) ;- (USART) Clock Output Select
AT91C_US_OVER             EQU (0x1 << 19) ;- (USART) Over Sampling Mode
AT91C_US_INACK            EQU (0x1 << 20) ;- (USART) Inhibit Non Acknowledge
AT91C_US_DSNACK           EQU (0x1 << 21) ;- (USART) Disable Successive NACK
AT91C_US_MAX_ITER         EQU (0x1 << 24) ;- (USART) Number of Repetitions
AT91C_US_FILTER           EQU (0x1 << 28) ;- (USART) Receive Line Filter
// - -------- US_IER : (USART Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
AT91C_US_RXBRK            EQU (0x1 <<  2) ;- (USART) Break Received/End of Break
AT91C_US_TIMEOUT          EQU (0x1 <<  8) ;- (USART) Receiver Time-out
AT91C_US_ITERATION        EQU (0x1 << 10) ;- (USART) Max number of Repetitions Reached
AT91C_US_NACK             EQU (0x1 << 13) ;- (USART) Non Acknowledge
AT91C_US_RIIC             EQU (0x1 << 16) ;- (USART) Ring INdicator Input Change Flag
AT91C_US_DSRIC            EQU (0x1 << 17) ;- (USART) Data Set Ready Input Change Flag
AT91C_US_DCDIC            EQU (0x1 << 18) ;- (USART) Data Carrier Flag
AT91C_US_CTSIC            EQU (0x1 << 19) ;- (USART) Clear To Send Input Change Flag
// - -------- US_IDR : (USART Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// - -------- US_IMR : (USART Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// - -------- US_CSR : (USART Offset: 0x14) Debug Unit Channel Status Register -------- 
AT91C_US_RI               EQU (0x1 << 20) ;- (USART) Image of RI Input
AT91C_US_DSR              EQU (0x1 << 21) ;- (USART) Image of DSR Input
AT91C_US_DCD              EQU (0x1 << 22) ;- (USART) Image of DCD Input
AT91C_US_CTS              EQU (0x1 << 23) ;- (USART) Image of CTS Input

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
// - *****************************************************************************
// - -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- 
AT91C_SSC_RXEN            EQU (0x1 <<  0) ;- (SSC) Receive Enable
AT91C_SSC_RXDIS           EQU (0x1 <<  1) ;- (SSC) Receive Disable
AT91C_SSC_TXEN            EQU (0x1 <<  8) ;- (SSC) Transmit Enable
AT91C_SSC_TXDIS           EQU (0x1 <<  9) ;- (SSC) Transmit Disable
AT91C_SSC_SWRST           EQU (0x1 << 15) ;- (SSC) Software Reset
// - -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- 
AT91C_SSC_CKS             EQU (0x3 <<  0) ;- (SSC) Receive/Transmit Clock Selection
AT91C_SSC_CKS_DIV         EQU (0x0) ;- (SSC) Divided Clock
AT91C_SSC_CKS_TK          EQU (0x1) ;- (SSC) TK Clock signal
AT91C_SSC_CKS_RK          EQU (0x2) ;- (SSC) RK pin
AT91C_SSC_CKO             EQU (0x7 <<  2) ;- (SSC) Receive/Transmit Clock Output Mode Selection
AT91C_SSC_CKO_NONE        EQU (0x0 <<  2) ;- (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only
AT91C_SSC_CKO_CONTINOUS   EQU (0x1 <<  2) ;- (SSC) Continuous Receive/Transmit Clock RK pin: Output
AT91C_SSC_CKO_DATA_TX     EQU (0x2 <<  2) ;- (SSC) Receive/Transmit Clock only during data transfers RK pin: Output
AT91C_SSC_CKI             EQU (0x1 <<  5) ;- (SSC) Receive/Transmit Clock Inversion
AT91C_SSC_CKG             EQU (0x3 <<  6) ;- (SSC) Receive/Transmit Clock Gating Selection
AT91C_SSC_CKG_NONE        EQU (0x0 <<  6) ;- (SSC) Receive/Transmit Clock Gating: None, continuous clock
AT91C_SSC_CKG_LOW         EQU (0x1 <<  6) ;- (SSC) Receive/Transmit Clock enabled only if RF Low
AT91C_SSC_CKG_HIGH        EQU (0x2 <<  6) ;- (SSC) Receive/Transmit Clock enabled only if RF High
AT91C_SSC_START           EQU (0xF <<  8) ;- (SSC) Receive/Transmit Start Selection
AT91C_SSC_START_CONTINOUS EQU (0x0 <<  8) ;- (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data.
AT91C_SSC_START_TX        EQU (0x1 <<  8) ;- (SSC) Transmit/Receive start
AT91C_SSC_START_LOW_RF    EQU (0x2 <<  8) ;- (SSC) Detection of a low level on RF input
AT91C_SSC_START_HIGH_RF   EQU (0x3 <<  8) ;- (SSC) Detection of a high level on RF input
AT91C_SSC_START_FALL_RF   EQU (0x4 <<  8) ;- (SSC) Detection of a falling edge on RF input
AT91C_SSC_START_RISE_RF   EQU (0x5 <<  8) ;- (SSC) Detection of a rising edge on RF input
AT91C_SSC_START_LEVEL_RF  EQU (0x6 <<  8) ;- (SSC) Detection of any level change on RF input
AT91C_SSC_START_EDGE_RF   EQU (0x7 <<  8) ;- (SSC) Detection of any edge on RF input
AT91C_SSC_START_0         EQU (0x8 <<  8) ;- (SSC) Compare 0
AT91C_SSC_STOP            EQU (0x1 << 12) ;- (SSC) Receive Stop Selection
AT91C_SSC_STTDLY          EQU (0xFF << 16) ;- (SSC) Receive/Transmit Start Delay
AT91C_SSC_PERIOD          EQU (0xFF << 24) ;- (SSC) Receive/Transmit Period Divider Selection
// - -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- 
AT91C_SSC_DATLEN          EQU (0x1F <<  0) ;- (SSC) Data Length
AT91C_SSC_LOOP            EQU (0x1 <<  5) ;- (SSC) Loop Mode
AT91C_SSC_MSBF            EQU (0x1 <<  7) ;- (SSC) Most Significant Bit First
AT91C_SSC_DATNB           EQU (0xF <<  8) ;- (SSC) Data Number per Frame
AT91C_SSC_FSLEN           EQU (0xF << 16) ;- (SSC) Receive/Transmit Frame Sync length
AT91C_SSC_FSOS            EQU (0x7 << 20) ;- (SSC) Receive/Transmit Frame Sync Output Selection
AT91C_SSC_FSOS_NONE       EQU (0x0 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only
AT91C_SSC_FSOS_NEGATIVE   EQU (0x1 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse
AT91C_SSC_FSOS_POSITIVE   EQU (0x2 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse
AT91C_SSC_FSOS_LOW        EQU (0x3 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer
AT91C_SSC_FSOS_HIGH       EQU (0x4 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer
AT91C_SSC_FSOS_TOGGLE     EQU (0x5 << 20) ;- (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer
AT91C_SSC_FSEDGE          EQU (0x1 << 24) ;- (SSC) Frame Sync Edge Detection
// - -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- 
// - -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- 
AT91C_SSC_DATDEF          EQU (0x1 <<  5) ;- (SSC) Data Default Value
AT91C_SSC_FSDEN           EQU (0x1 << 23) ;- (SSC) Frame Sync Data Enable
// - -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- 
AT91C_SSC_TXRDY           EQU (0x1 <<  0) ;- (SSC) Transmit Ready
AT91C_SSC_TXEMPTY         EQU (0x1 <<  1) ;- (SSC) Transmit Empty
AT91C_SSC_ENDTX           EQU (0x1 <<  2) ;- (SSC) End Of Transmission
AT91C_SSC_TXBUFE          EQU (0x1 <<  3) ;- (SSC) Transmit Buffer Empty
AT91C_SSC_RXRDY           EQU (0x1 <<  4) ;- (SSC) Receive Ready
AT91C_SSC_OVRUN           EQU (0x1 <<  5) ;- (SSC) Receive Overrun
AT91C_SSC_ENDRX           EQU (0x1 <<  6) ;- (SSC) End of Reception
AT91C_SSC_RXBUFF          EQU (0x1 <<  7) ;- (SSC) Receive Buffer Full
AT91C_SSC_CP0             EQU (0x1 <<  8) ;- (SSC) Compare 0
AT91C_SSC_CP1             EQU (0x1 <<  9) ;- (SSC) Compare 1
AT91C_SSC_TXSYN           EQU (0x1 << 10) ;- (SSC) Transmit Sync
AT91C_SSC_RXSYN           EQU (0x1 << 11) ;- (SSC) Receive Sync
AT91C_SSC_TXENA           EQU (0x1 << 16) ;- (SSC) Transmit Enable
AT91C_SSC_RXENA           EQU (0x1 << 17) ;- (SSC) Receive Enable
// - -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- 
// - -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- 
// - -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR AC97 Controller Interface
// - *****************************************************************************
// - -------- AC97C_MR : (AC97C Offset: 0x8) AC97C Mode Register -------- 
AT91C_AC97C_ENA           EQU (0x1 <<  0) ;- (AC97C) AC97 Controller Global Enable
AT91C_AC97C_WRST          EQU (0x1 <<  1) ;- (AC97C) Warm Reset
AT91C_AC97C_VRA           EQU (0x1 <<  2) ;- (AC97C) Variable RAte (for Data Slots)
// - -------- AC97C_ICA : (AC97C Offset: 0x10) AC97C Input Channel Assignement Register -------- 
AT91C_AC97C_CHID3         EQU (0x7 <<  0) ;- (AC97C) Channel Id for the input slot 3
AT91C_AC97C_CHID3_NONE    EQU (0x0) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID3_CA      EQU (0x1) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID3_CB      EQU (0x2) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID3_CC      EQU (0x3) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID4         EQU (0x7 <<  3) ;- (AC97C) Channel Id for the input slot 4
AT91C_AC97C_CHID4_NONE    EQU (0x0 <<  3) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID4_CA      EQU (0x1 <<  3) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID4_CB      EQU (0x2 <<  3) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID4_CC      EQU (0x3 <<  3) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID5         EQU (0x7 <<  6) ;- (AC97C) Channel Id for the input slot 5
AT91C_AC97C_CHID5_NONE    EQU (0x0 <<  6) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID5_CA      EQU (0x1 <<  6) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID5_CB      EQU (0x2 <<  6) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID5_CC      EQU (0x3 <<  6) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID6         EQU (0x7 <<  9) ;- (AC97C) Channel Id for the input slot 6
AT91C_AC97C_CHID6_NONE    EQU (0x0 <<  9) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID6_CA      EQU (0x1 <<  9) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID6_CB      EQU (0x2 <<  9) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID6_CC      EQU (0x3 <<  9) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID7         EQU (0x7 << 12) ;- (AC97C) Channel Id for the input slot 7
AT91C_AC97C_CHID7_NONE    EQU (0x0 << 12) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID7_CA      EQU (0x1 << 12) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID7_CB      EQU (0x2 << 12) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID7_CC      EQU (0x3 << 12) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID8         EQU (0x7 << 15) ;- (AC97C) Channel Id for the input slot 8
AT91C_AC97C_CHID8_NONE    EQU (0x0 << 15) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID8_CA      EQU (0x1 << 15) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID8_CB      EQU (0x2 << 15) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID8_CC      EQU (0x3 << 15) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID9         EQU (0x7 << 18) ;- (AC97C) Channel Id for the input slot 9
AT91C_AC97C_CHID9_NONE    EQU (0x0 << 18) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID9_CA      EQU (0x1 << 18) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID9_CB      EQU (0x2 << 18) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID9_CC      EQU (0x3 << 18) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID10        EQU (0x7 << 21) ;- (AC97C) Channel Id for the input slot 10
AT91C_AC97C_CHID10_NONE   EQU (0x0 << 21) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID10_CA     EQU (0x1 << 21) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID10_CB     EQU (0x2 << 21) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID10_CC     EQU (0x3 << 21) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID11        EQU (0x7 << 24) ;- (AC97C) Channel Id for the input slot 11
AT91C_AC97C_CHID11_NONE   EQU (0x0 << 24) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID11_CA     EQU (0x1 << 24) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID11_CB     EQU (0x2 << 24) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID11_CC     EQU (0x3 << 24) ;- (AC97C) Channel C data will be transmitted during this slot
AT91C_AC97C_CHID12        EQU (0x7 << 27) ;- (AC97C) Channel Id for the input slot 12
AT91C_AC97C_CHID12_NONE   EQU (0x0 << 27) ;- (AC97C) No data will be transmitted during this slot
AT91C_AC97C_CHID12_CA     EQU (0x1 << 27) ;- (AC97C) Channel A data will be transmitted during this slot
AT91C_AC97C_CHID12_CB     EQU (0x2 << 27) ;- (AC97C) Channel B data will be transmitted during this slot
AT91C_AC97C_CHID12_CC     EQU (0x3 << 27) ;- (AC97C) Channel C data will be transmitted during this slot
// - -------- AC97C_OCA : (AC97C Offset: 0x14) AC97C Output Channel Assignement Register -------- 
// - -------- AC97C_CARHR : (AC97C Offset: 0x20) AC97C Channel A Receive Holding Register -------- 
AT91C_AC97C_RDATA         EQU (0xFFFFF <<  0) ;- (AC97C) Receive data
// - -------- AC97C_CATHR : (AC97C Offset: 0x24) AC97C Channel A Transmit Holding Register -------- 
AT91C_AC97C_TDATA         EQU (0xFFFFF <<  0) ;- (AC97C) Transmit data
// - -------- AC97C_CASR : (AC97C Offset: 0x28) AC97C Channel A Status Register -------- 
AT91C_AC97C_TXRDY         EQU (0x1 <<  0) ;- (AC97C) 
AT91C_AC97C_TXEMPTY       EQU (0x1 <<  1) ;- (AC97C) 
AT91C_AC97C_UNRUN         EQU (0x1 <<  2) ;- (AC97C) 
AT91C_AC97C_RXRDY         EQU (0x1 <<  4) ;- (AC97C) 
AT91C_AC97C_OVRUN         EQU (0x1 <<  5) ;- (AC97C) 
AT91C_AC97C_ENDTX         EQU (0x1 << 10) ;- (AC97C) 
AT91C_AC97C_TXBUFE        EQU (0x1 << 11) ;- (AC97C) 
AT91C_AC97C_ENDRX         EQU (0x1 << 14) ;- (AC97C) 
AT91C_AC97C_RXBUFF        EQU (0x1 << 15) ;- (AC97C) 
// - -------- AC97C_CAMR : (AC97C Offset: 0x2c) AC97C Channel A Mode Register -------- 
AT91C_AC97C_SIZE          EQU (0x3 << 16) ;- (AC97C) 
AT91C_AC97C_SIZE_20_BITS  EQU (0x0 << 16) ;- (AC97C) Data size is 20 bits
AT91C_AC97C_SIZE_18_BITS  EQU (0x1 << 16) ;- (AC97C) Data size is 18 bits
AT91C_AC97C_SIZE_16_BITS  EQU (0x2 << 16) ;- (AC97C) Data size is 16 bits
AT91C_AC97C_SIZE_10_BITS  EQU (0x3 << 16) ;- (AC97C) Data size is 10 bits
AT91C_AC97C_CEM           EQU (0x1 << 18) ;- (AC97C) 
AT91C_AC97C_CEN           EQU (0x1 << 21) ;- (AC97C) 
AT91C_AC97C_PDCEN         EQU (0x1 << 22) ;- (AC97C) 
// - -------- AC97C_CBRHR : (AC97C Offset: 0x30) AC97C Channel B Receive Holding Register -------- 
// - -------- AC97C_CBTHR : (AC97C Offset: 0x34) AC97C Channel B Transmit Holding Register -------- 
// - -------- AC97C_CBSR : (AC97C Offset: 0x38) AC97C Channel B Status Register -------- 
// - -------- AC97C_CBMR : (AC97C Offset: 0x3c) AC97C Channel B Mode Register -------- 
// - -------- AC97C_CORHR : (AC97C Offset: 0x40) AC97C Codec Channel Receive Holding Register -------- 
AT91C_AC97C_SDATA         EQU (0xFFFF <<  0) ;- (AC97C) Status Data
// - -------- AC97C_COTHR : (AC97C Offset: 0x44) AC97C Codec Channel Transmit Holding Register -------- 
AT91C_AC97C_CDATA         EQU (0xFFFF <<  0) ;- (AC97C) Command Data
AT91C_AC97C_CADDR         EQU (0x7F << 16) ;- (AC97C) COdec control register index
AT91C_AC97C_READ          EQU (0x1 << 23) ;- (AC97C) Read/Write command
// - -------- AC97C_COSR : (AC97C Offset: 0x48) AC97C CODEC Status Register -------- 
// - -------- AC97C_COMR : (AC97C Offset: 0x4c) AC97C CODEC Mode Register -------- 
// - -------- AC97C_SR : (AC97C Offset: 0x50) AC97C Status Register -------- 
AT91C_AC97C_SOF           EQU (0x1 <<  0) ;- (AC97C) 
AT91C_AC97C_WKUP          EQU (0x1 <<  1) ;- (AC97C) 
AT91C_AC97C_COEVT         EQU (0x1 <<  2) ;- (AC97C) 
AT91C_AC97C_CAEVT         EQU (0x1 <<  3) ;- (AC97C) 
AT91C_AC97C_CBEVT         EQU (0x1 <<  4) ;- (AC97C) 
// - -------- AC97C_IER : (AC97C Offset: 0x54) AC97C Interrupt Enable Register -------- 
// - -------- AC97C_IDR : (AC97C Offset: 0x58) AC97C Interrupt Disable Register -------- 
// - -------- AC97C_IMR : (AC97C Offset: 0x5c) AC97C Interrupt Mask Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
// - *****************************************************************************
// - -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
AT91C_SPI_SPIEN           EQU (0x1 <<  0) ;- (SPI) SPI Enable
AT91C_SPI_SPIDIS          EQU (0x1 <<  1) ;- (SPI) SPI Disable
AT91C_SPI_SWRST           EQU (0x1 <<  7) ;- (SPI) SPI Software reset
AT91C_SPI_LASTXFER        EQU (0x1 << 24) ;- (SPI) SPI Last Transfer
// - -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
AT91C_SPI_MSTR            EQU (0x1 <<  0) ;- (SPI) Master/Slave Mode
AT91C_SPI_PS              EQU (0x1 <<  1) ;- (SPI) Peripheral Select
AT91C_SPI_PS_FIXED        EQU (0x0 <<  1) ;- (SPI) Fixed Peripheral Select
AT91C_SPI_PS_VARIABLE     EQU (0x1 <<  1) ;- (SPI) Variable Peripheral Select
AT91C_SPI_PCSDEC          EQU (0x1 <<  2) ;- (SPI) Chip Select Decode
AT91C_SPI_FDIV            EQU (0x1 <<  3) ;- (SPI) Clock Selection
AT91C_SPI_MODFDIS         EQU (0x1 <<  4) ;- (SPI) Mode Fault Detection
AT91C_SPI_LLB             EQU (0x1 <<  7) ;- (SPI) Clock Selection
AT91C_SPI_PCS             EQU (0xF << 16) ;- (SPI) Peripheral Chip Select
AT91C_SPI_DLYBCS          EQU (0xFF << 24) ;- (SPI) Delay Between Chip Selects
// - -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
AT91C_SPI_RD              EQU (0xFFFF <<  0) ;- (SPI) Receive Data
AT91C_SPI_RPCS            EQU (0xF << 16) ;- (SPI) Peripheral Chip Select Status
// - -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
AT91C_SPI_TD              EQU (0xFFFF <<  0) ;- (SPI) Transmit Data
AT91C_SPI_TPCS            EQU (0xF << 16) ;- (SPI) Peripheral Chip Select Status
// - -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
AT91C_SPI_RDRF            EQU (0x1 <<  0) ;- (SPI) Receive Data Register Full
AT91C_SPI_TDRE            EQU (0x1 <<  1) ;- (SPI) Transmit Data Register Empty
AT91C_SPI_MODF            EQU (0x1 <<  2) ;- (SPI) Mode Fault Error
AT91C_SPI_OVRES           EQU (0x1 <<  3) ;- (SPI) Overrun Error Status
AT91C_SPI_ENDRX           EQU (0x1 <<  4) ;- (SPI) End of Receiver Transfer
AT91C_SPI_ENDTX           EQU (0x1 <<  5) ;- (SPI) End of Receiver Transfer
AT91C_SPI_RXBUFF          EQU (0x1 <<  6) ;- (SPI) RXBUFF Interrupt
AT91C_SPI_TXBUFE          EQU (0x1 <<  7) ;- (SPI) TXBUFE Interrupt
AT91C_SPI_NSSR            EQU (0x1 <<  8) ;- (SPI) NSSR Interrupt
AT91C_SPI_TXEMPTY         EQU (0x1 <<  9) ;- (SPI) TXEMPTY Interrupt
AT91C_SPI_SPIENS          EQU (0x1 << 16) ;- (SPI) Enable Status
// - -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
// - -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
// - -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
// - -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
AT91C_SPI_CPOL            EQU (0x1 <<  0) ;- (SPI) Clock Polarity
AT91C_SPI_NCPHA           EQU (0x1 <<  1) ;- (SPI) Clock Phase
AT91C_SPI_CSAAT           EQU (0x1 <<  3) ;- (SPI) Chip Select Active After Transfer
AT91C_SPI_BITS            EQU (0xF <<  4) ;- (SPI) Bits Per Transfer
AT91C_SPI_BITS_8          EQU (0x0 <<  4) ;- (SPI) 8 Bits Per transfer
AT91C_SPI_BITS_9          EQU (0x1 <<  4) ;- (SPI) 9 Bits Per transfer
AT91C_SPI_BITS_10         EQU (0x2 <<  4) ;- (SPI) 10 Bits Per transfer
AT91C_SPI_BITS_11         EQU (0x3 <<  4) ;- (SPI) 11 Bits Per transfer
AT91C_SPI_BITS_12         EQU (0x4 <<  4) ;- (SPI) 12 Bits Per transfer
AT91C_SPI_BITS_13         EQU (0x5 <<  4) ;- (SPI) 13 Bits Per transfer
AT91C_SPI_BITS_14         EQU (0x6 <<  4) ;- (SPI) 14 Bits Per transfer
AT91C_SPI_BITS_15         EQU (0x7 <<  4) ;- (SPI) 15 Bits Per transfer
AT91C_SPI_BITS_16         EQU (0x8 <<  4) ;- (SPI) 16 Bits Per transfer
AT91C_SPI_SCBR            EQU (0xFF <<  8) ;- (SPI) Serial Clock Baud Rate
AT91C_SPI_DLYBS           EQU (0xFF << 16) ;- (SPI) Delay Before SPCK
AT91C_SPI_DLYBCT          EQU (0xFF << 24) ;- (SPI) Delay Between Consecutive Transfers

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface
// - *****************************************************************************
// - -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- 
AT91C_CAN_MTIMEMARK       EQU (0xFFFF <<  0) ;- (CAN_MB) Mailbox Timemark
AT91C_CAN_PRIOR           EQU (0xF << 16) ;- (CAN_MB) Mailbox Priority
AT91C_CAN_MOT             EQU (0x7 << 24) ;- (CAN_MB) Mailbox Object Type
AT91C_CAN_MOT_DIS         EQU (0x0 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_RX          EQU (0x1 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_RXOVERWRITE EQU (0x2 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_TX          EQU (0x3 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_CONSUMER    EQU (0x4 << 24) ;- (CAN_MB) 
AT91C_CAN_MOT_PRODUCER    EQU (0x5 << 24) ;- (CAN_MB) 
// - -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- 
AT91C_CAN_MIDvB           EQU (0x3FFFF <<  0) ;- (CAN_MB) Complementary bits for identifier in extended mode
AT91C_CAN_MIDvA           EQU (0x7FF << 18) ;- (CAN_MB) Identifier for standard frame mode
AT91C_CAN_MIDE            EQU (0x1 << 29) ;- (CAN_MB) Identifier Version
// - -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- 
// - -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- 
// - -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- 
AT91C_CAN_MTIMESTAMP      EQU (0xFFFF <<  0) ;- (CAN_MB) Timer Value
AT91C_CAN_MDLC            EQU (0xF << 16) ;- (CAN_MB) Mailbox Data Length Code
AT91C_CAN_MRTR            EQU (0x1 << 20) ;- (CAN_MB) Mailbox Remote Transmission Request
AT91C_CAN_MABT            EQU (0x1 << 22) ;- (CAN_MB) Mailbox Message Abort
AT91C_CAN_MRDY            EQU (0x1 << 23) ;- (CAN_MB) Mailbox Ready
AT91C_CAN_MMI             EQU (0x1 << 24) ;- (CAN_MB) Mailbox Message Ignored
// - -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- 
// - -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- 
// - -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- 
AT91C_CAN_MACR            EQU (0x1 << 22) ;- (CAN_MB) Abort Request for Mailbox
AT91C_CAN_MTCR            EQU (0x1 << 23) ;- (CAN_MB) Mailbox Transfer Command

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Control Area Network Interface
// - *****************************************************************************
// - -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- 
AT91C_CAN_CANEN           EQU (0x1 <<  0) ;- (CAN) CAN Controller Enable
AT91C_CAN_LPM             EQU (0x1 <<  1) ;- (CAN) Disable/Enable Low Power Mode
AT91C_CAN_ABM             EQU (0x1 <<  2) ;- (CAN) Disable/Enable Autobaud/Listen Mode
AT91C_CAN_OVL             EQU (0x1 <<  3) ;- (CAN) Disable/Enable Overload Frame
AT91C_CAN_TEOF            EQU (0x1 <<  4) ;- (CAN) Time Stamp messages at each end of Frame
AT91C_CAN_TTM             EQU (0x1 <<  5) ;- (CAN) Disable/Enable Time Trigger Mode
AT91C_CAN_TIMFRZ          EQU (0x1 <<  6) ;- (CAN) Enable Timer Freeze
AT91C_CAN_DRPT            EQU (0x1 <<  7) ;- (CAN) Disable Repeat
// - -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- 
AT91C_CAN_MB0             EQU (0x1 <<  0) ;- (CAN) Mailbox 0 Flag
AT91C_CAN_MB1             EQU (0x1 <<  1) ;- (CAN) Mailbox 1 Flag
AT91C_CAN_MB2             EQU (0x1 <<  2) ;- (CAN) Mailbox 2 Flag
AT91C_CAN_MB3             EQU (0x1 <<  3) ;- (CAN) Mailbox 3 Flag
AT91C_CAN_MB4             EQU (0x1 <<  4) ;- (CAN) Mailbox 4 Flag
AT91C_CAN_MB5             EQU (0x1 <<  5) ;- (CAN) Mailbox 5 Flag
AT91C_CAN_MB6             EQU (0x1 <<  6) ;- (CAN) Mailbox 6 Flag
AT91C_CAN_MB7             EQU (0x1 <<  7) ;- (CAN) Mailbox 7 Flag
AT91C_CAN_MB8             EQU (0x1 <<  8) ;- (CAN) Mailbox 8 Flag
AT91C_CAN_MB9             EQU (0x1 <<  9) ;- (CAN) Mailbox 9 Flag
AT91C_CAN_MB10            EQU (0x1 << 10) ;- (CAN) Mailbox 10 Flag
AT91C_CAN_MB11            EQU (0x1 << 11) ;- (CAN) Mailbox 11 Flag
AT91C_CAN_MB12            EQU (0x1 << 12) ;- (CAN) Mailbox 12 Flag
AT91C_CAN_MB13            EQU (0x1 << 13) ;- (CAN) Mailbox 13 Flag
AT91C_CAN_MB14            EQU (0x1 << 14) ;- (CAN) Mailbox 14 Flag
AT91C_CAN_MB15            EQU (0x1 << 15) ;- (CAN) Mailbox 15 Flag
AT91C_CAN_ERRA            EQU (0x1 << 16) ;- (CAN) Error Active Mode Flag
AT91C_CAN_WARN            EQU (0x1 << 17) ;- (CAN) Warning Limit Flag
AT91C_CAN_ERRP            EQU (0x1 << 18) ;- (CAN) Error Passive Mode Flag
AT91C_CAN_BOFF            EQU (0x1 << 19) ;- (CAN) Bus Off Mode Flag
AT91C_CAN_SLEEP           EQU (0x1 << 20) ;- (CAN) Sleep Flag
AT91C_CAN_WAKEUP          EQU (0x1 << 21) ;- (CAN) Wakeup Flag
AT91C_CAN_TOVF            EQU (0x1 << 22) ;- (CAN) Timer Overflow Flag
AT91C_CAN_TSTP            EQU (0x1 << 23) ;- (CAN) Timestamp Flag
AT91C_CAN_CERR            EQU (0x1 << 24) ;- (CAN) CRC Error
AT91C_CAN_SERR            EQU (0x1 << 25) ;- (CAN) Stuffing Error
AT91C_CAN_AERR            EQU (0x1 << 26) ;- (CAN) Acknowledgment Error
AT91C_CAN_FERR            EQU (0x1 << 27) ;- (CAN) Form Error
AT91C_CAN_BERR            EQU (0x1 << 28) ;- (CAN) Bit Error
// - -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- 
// - -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- 
// - -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- 
AT91C_CAN_RBSY            EQU (0x1 << 29) ;- (CAN) Receiver Busy
AT91C_CAN_TBSY            EQU (0x1 << 30) ;- (CAN) Transmitter Busy
AT91C_CAN_OVLY            EQU (0x1 << 31) ;- (CAN) Overload Busy
// - -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- 
AT91C_CAN_PHASE2          EQU (0x7 <<  0) ;- (CAN) Phase 2 segment
AT91C_CAN_PHASE1          EQU (0x7 <<  4) ;- (CAN) Phase 1 segment
AT91C_CAN_PROPAG          EQU (0x7 <<  8) ;- (CAN) Programmation time segment
AT91C_CAN_SYNC            EQU (0x3 << 12) ;- (CAN) Re-synchronization jump width segment
AT91C_CAN_BRP             EQU (0x7F << 16) ;- (CAN) Baudrate Prescaler
AT91C_CAN_SMP             EQU (0x1 << 24) ;- (CAN) Sampling mode
// - -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- 
AT91C_CAN_TIMER           EQU (0xFFFF <<  0) ;- (CAN) Timer field
// - -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- 
// - -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- 
AT91C_CAN_REC             EQU (0xFF <<  0) ;- (CAN) Receive Error Counter
AT91C_CAN_TEC             EQU (0xFF << 16) ;- (CAN) Transmit Error Counter
// - -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- 
AT91C_CAN_TIMRST          EQU (0x1 << 31) ;- (CAN) Timer Reset Field
// - -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR PWMC Channel Interface
// - *****************************************************************************
// - -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- 
AT91C_PWMC_CPRE           EQU (0xF <<  0) ;- (PWMC_CH) Channel Pre-scaler : PWMC_CLKx
AT91C_PWMC_CPRE_MCK       EQU (0x0) ;- (PWMC_CH) 
AT91C_PWMC_CPRE_MCKA      EQU (0xB) ;- (PWMC_CH) 
AT91C_PWMC_CPRE_MCKB      EQU (0xC) ;- (PWMC_CH) 
AT91C_PWMC_CALG           EQU (0x1 <<  8) ;- (PWMC_CH) Channel Alignment
AT91C_PWMC_CPOL           EQU (0x1 <<  9) ;- (PWMC_CH) Channel Polarity
AT91C_PWMC_CPD            EQU (0x1 << 10) ;- (PWMC_CH) Channel Update Period
// - -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- 
AT91C_PWMC_CDTY           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Duty Cycle
// - -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- 
AT91C_PWMC_CPRD           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Period
// - -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- 
AT91C_PWMC_CCNT           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Counter
// - -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- 
AT91C_PWMC_CUPD           EQU (0x0 <<  0) ;- (PWMC_CH) Channel Update

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
// - *****************************************************************************
// - -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- 
AT91C_PWMC_DIVA           EQU (0xFF <<  0) ;- (PWMC) CLKA divide factor.
AT91C_PWMC_PREA           EQU (0xF <<  8) ;- (PWMC) Divider Input Clock Prescaler A
AT91C_PWMC_PREA_MCK       EQU (0x0 <<  8) ;- (PWMC) 
AT91C_PWMC_DIVB           EQU (0xFF << 16) ;- (PWMC) CLKB divide factor.
AT91C_PWMC_PREB           EQU (0xF << 24) ;- (PWMC) Divider Input Clock Prescaler B
AT91C_PWMC_PREB_MCK       EQU (0x0 << 24) ;- (PWMC) 
// - -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- 
AT91C_PWMC_CHID0          EQU (0x1 <<  0) ;- (PWMC) Channel ID 0
AT91C_PWMC_CHID1          EQU (0x1 <<  1) ;- (PWMC) Channel ID 1
AT91C_PWMC_CHID2          EQU (0x1 <<  2) ;- (PWMC) Channel ID 2
AT91C_PWMC_CHID3          EQU (0x1 <<  3) ;- (PWMC) Channel ID 3
AT91C_PWMC_CHID4          EQU (0x1 <<  4) ;- (PWMC) Channel ID 4
AT91C_PWMC_CHID5          EQU (0x1 <<  5) ;- (PWMC) Channel ID 5
AT91C_PWMC_CHID6          EQU (0x1 <<  6) ;- (PWMC) Channel ID 6
AT91C_PWMC_CHID7          EQU (0x1 <<  7) ;- (PWMC) Channel ID 7
// - -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
// - -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
// - -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
// - -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
// - -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
// - -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100
// - *****************************************************************************
// - -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- 
AT91C_EMAC_LB             EQU (0x1 <<  0) ;- (EMAC) Loopback. Optional. When set, loopback signal is at high level.
AT91C_EMAC_LLB            EQU (0x1 <<  1) ;- (EMAC) Loopback local. 
AT91C_EMAC_RE             EQU (0x1 <<  2) ;- (EMAC) Receive enable. 
AT91C_EMAC_TE             EQU (0x1 <<  3) ;- (EMAC) Transmit enable. 
AT91C_EMAC_MPE            EQU (0x1 <<  4) ;- (EMAC) Management port enable. 
AT91C_EMAC_CLRSTAT        EQU (0x1 <<  5) ;- (EMAC) Clear statistics registers. 
AT91C_EMAC_INCSTAT        EQU (0x1 <<  6) ;- (EMAC) Increment statistics registers. 
AT91C_EMAC_WESTAT         EQU (0x1 <<  7) ;- (EMAC) Write enable for statistics registers. 
AT91C_EMAC_BP             EQU (0x1 <<  8) ;- (EMAC) Back pressure. 
AT91C_EMAC_TSTART         EQU (0x1 <<  9) ;- (EMAC) Start Transmission. 
AT91C_EMAC_THALT          EQU (0x1 << 10) ;- (EMAC) Transmission Halt. 
AT91C_EMAC_TPFR           EQU (0x1 << 11) ;- (EMAC) Transmit pause frame 
AT91C_EMAC_TZQ            EQU (0x1 << 12) ;- (EMAC) Transmit zero quantum pause frame
// - -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- 
AT91C_EMAC_SPD            EQU (0x1 <<  0) ;- (EMAC) Speed. 
AT91C_EMAC_FD             EQU (0x1 <<  1) ;- (EMAC) Full duplex. 
AT91C_EMAC_JFRAME         EQU (0x1 <<  3) ;- (EMAC) Jumbo Frames. 
AT91C_EMAC_CAF            EQU (0x1 <<  4) ;- (EMAC) Copy all frames. 
AT91C_EMAC_NBC            EQU (0x1 <<  5) ;- (EMAC) No broadcast. 
AT91C_EMAC_MTI            EQU (0x1 <<  6) ;- (EMAC) Multicast hash event enable
AT91C_EMAC_UNI            EQU (0x1 <<  7) ;- (EMAC) Unicast hash enable. 
AT91C_EMAC_BIG            EQU (0x1 <<  8) ;- (EMAC) Receive 1522 bytes. 
AT91C_EMAC_EAE            EQU (0x1 <<  9) ;- (EMAC) External address match enable. 
AT91C_EMAC_CLK            EQU (0x3 << 10) ;- (EMAC) 
AT91C_EMAC_CLK_HCLK_8     EQU (0x0 << 10) ;- (EMAC) HCLK divided by 8
AT91C_EMAC_CLK_HCLK_16    EQU (0x1 << 10) ;- (EMAC) HCLK divided by 16
AT91C_EMAC_CLK_HCLK_32    EQU (0x2 << 10) ;- (EMAC) HCLK divided by 32
AT91C_EMAC_CLK_HCLK_64    EQU (0x3 << 10) ;- (EMAC) HCLK divided by 64
AT91C_EMAC_RTY            EQU (0x1 << 12) ;- (EMAC) 
AT91C_EMAC_PAE            EQU (0x1 << 13) ;- (EMAC) 
AT91C_EMAC_RBOF           EQU (0x3 << 14) ;- (EMAC) 
AT91C_EMAC_RBOF_OFFSET_0  EQU (0x0 << 14) ;- (EMAC) no offset from start of receive buffer
AT91C_EMAC_RBOF_OFFSET_1  EQU (0x1 << 14) ;- (EMAC) one byte offset from start of receive buffer
AT91C_EMAC_RBOF_OFFSET_2  EQU (0x2 << 14) ;- (EMAC) two bytes offset from start of receive buffer
AT91C_EMAC_RBOF_OFFSET_3  EQU (0x3 << 14) ;- (EMAC) three bytes offset from start of receive buffer
AT91C_EMAC_RLCE           EQU (0x1 << 16) ;- (EMAC) Receive Length field Checking Enable
AT91C_EMAC_DRFCS          EQU (0x1 << 17) ;- (EMAC) Discard Receive FCS
AT91C_EMAC_EFRHD          EQU (0x1 << 18) ;- (EMAC) 
AT91C_EMAC_IRXFCS         EQU (0x1 << 19) ;- (EMAC) Ignore RX FCS
// - -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- 
AT91C_EMAC_LINKR          EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_MDIO           EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_IDLE           EQU (0x1 <<  2) ;- (EMAC) 
// - -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- 
AT91C_EMAC_UBR            EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_COL            EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_RLES           EQU (0x1 <<  2) ;- (EMAC) 
AT91C_EMAC_TGO            EQU (0x1 <<  3) ;- (EMAC) Transmit Go
AT91C_EMAC_BEX            EQU (0x1 <<  4) ;- (EMAC) Buffers exhausted mid frame
AT91C_EMAC_COMP           EQU (0x1 <<  5) ;- (EMAC) 
AT91C_EMAC_UND            EQU (0x1 <<  6) ;- (EMAC) 
// - -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- 
AT91C_EMAC_BNA            EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_REC            EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_OVR            EQU (0x1 <<  2) ;- (EMAC) 
// - -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- 
AT91C_EMAC_MFD            EQU (0x1 <<  0) ;- (EMAC) 
AT91C_EMAC_RCOMP          EQU (0x1 <<  1) ;- (EMAC) 
AT91C_EMAC_RXUBR          EQU (0x1 <<  2) ;- (EMAC) 
AT91C_EMAC_TXUBR          EQU (0x1 <<  3) ;- (EMAC) 
AT91C_EMAC_TUNDR          EQU (0x1 <<  4) ;- (EMAC) 
AT91C_EMAC_RLEX           EQU (0x1 <<  5) ;- (EMAC) 
AT91C_EMAC_TXERR          EQU (0x1 <<  6) ;- (EMAC) 
AT91C_EMAC_TCOMP          EQU (0x1 <<  7) ;- (EMAC) 
AT91C_EMAC_LINK           EQU (0x1 <<  9) ;- (EMAC) 
AT91C_EMAC_ROVR           EQU (0x1 << 10) ;- (EMAC) 
AT91C_EMAC_HRESP          EQU (0x1 << 11) ;- (EMAC) 
AT91C_EMAC_PFRE           EQU (0x1 << 12) ;- (EMAC) 
AT91C_EMAC_PTZ            EQU (0x1 << 13) ;- (EMAC) 
// - -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- 
// - -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- 
// - -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- 
// - -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- 
AT91C_EMAC_DATA           EQU (0xFFFF <<  0) ;- (EMAC) 
AT91C_EMAC_CODE           EQU (0x3 << 16) ;- (EMAC) 
AT91C_EMAC_REGA           EQU (0x1F << 18) ;- (EMAC) 
AT91C_EMAC_PHYA           EQU (0x1F << 23) ;- (EMAC) 
AT91C_EMAC_RW             EQU (0x3 << 28) ;- (EMAC) 
AT91C_EMAC_SOF            EQU (0x3 << 30) ;- (EMAC) 
// - -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- 
AT91C_EMAC_RMII           EQU (0x1 <<  0) ;- (EMAC) Reduce MII
AT91C_EMAC_CLKEN          EQU (0x1 <<  1) ;- (EMAC) Clock Enable
// - -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- 
AT91C_EMAC_IP             EQU (0xFFFF <<  0) ;- (EMAC) ARP request IP address
AT91C_EMAC_MAG            EQU (0x1 << 16) ;- (EMAC) Magic packet event enable
AT91C_EMAC_ARP            EQU (0x1 << 17) ;- (EMAC) ARP request event enable
AT91C_EMAC_SA1            EQU (0x1 << 18) ;- (EMAC) Specific address register 1 event enable
// - -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- 
AT91C_EMAC_REVREF         EQU (0xFFFF <<  0) ;- (EMAC) 
AT91C_EMAC_PARTREF        EQU (0xFFFF << 16) ;- (EMAC) 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR LCD Controller
// - *****************************************************************************
// - -------- LCDC_FRMP1 : (LCDC Offset: 0x8) DMA Frame Pointer 1 Register -------- 
AT91C_LCDC_FRMPT1         EQU (0x3FFFFF <<  0) ;- (LCDC) Frame Pointer Address 1
// - -------- LCDC_FRMP2 : (LCDC Offset: 0xc) DMA Frame Pointer 2 Register -------- 
AT91C_LCDC_FRMPT2         EQU (0x1FFFFF <<  0) ;- (LCDC) Frame Pointer Address 2
// - -------- LCDC_FRMCFG : (LCDC Offset: 0x18) DMA Frame Config Register -------- 
AT91C_LCDC_FRSIZE         EQU (0x3FFFFF <<  0) ;- (LCDC) FRAME SIZE
AT91C_LCDC_BLENGTH        EQU (0xF << 24) ;- (LCDC) BURST LENGTH
// - -------- LCDC_DMACON : (LCDC Offset: 0x1c) DMA Control Register -------- 
AT91C_LCDC_DMAEN          EQU (0x1 <<  0) ;- (LCDC) DAM Enable
AT91C_LCDC_DMARST         EQU (0x1 <<  1) ;- (LCDC) DMA Reset (WO)
AT91C_LCDC_DMABUSY        EQU (0x1 <<  2) ;- (LCDC) DMA Reset (WO)
AT91C_LCDC_DMAUPDT        EQU (0x1 <<  3) ;- (LCDC) DMA Configuration Update
AT91C_LCDC_DMA2DEN        EQU (0x1 <<  4) ;- (LCDC) 2D Addressing Enable
// - -------- LCDC_DMA2DCFG : (LCDC Offset: 0x20) DMA 2D addressing configuration Register -------- 
AT91C_LCDC_ADDRINC        EQU (0xFFFF <<  0) ;- (LCDC) Number of 32b words that the DMA must jump when going to the next line
AT91C_LCDC_PIXELOFF       EQU (0x1F << 24) ;- (LCDC) Offset (in bits) of the first pixel of the screen in the memory word which contain it
// - -------- LCDC_LCDCON1 : (LCDC Offset: 0x800) LCD Control 1 Register -------- 
AT91C_LCDC_BYPASS         EQU (0x1 <<  0) ;- (LCDC) Bypass lcd_pccklk divider
AT91C_LCDC_CLKVAL         EQU (0x1FF << 12) ;- (LCDC) 9-bit Divider for pixel clock frequency
AT91C_LCDC_LINCNT         EQU (0x7FF << 21) ;- (LCDC) Line Counter (RO)
// - -------- LCDC_LCDCON2 : (LCDC Offset: 0x804) LCD Control 2 Register -------- 
AT91C_LCDC_DISTYPE        EQU (0x3 <<  0) ;- (LCDC) Display Type
AT91C_LCDC_DISTYPE_STNMONO EQU (0x0) ;- (LCDC) STN Mono
AT91C_LCDC_DISTYPE_STNCOLOR EQU (0x1) ;- (LCDC) STN Color
AT91C_LCDC_DISTYPE_TFT    EQU (0x2) ;- (LCDC) TFT
AT91C_LCDC_SCANMOD        EQU (0x1 <<  2) ;- (LCDC) Scan Mode
AT91C_LCDC_SCANMOD_SINGLESCAN EQU (0x0 <<  2) ;- (LCDC) Single Scan
AT91C_LCDC_SCANMOD_DUALSCAN EQU (0x1 <<  2) ;- (LCDC) Dual Scan
AT91C_LCDC_IFWIDTH        EQU (0x3 <<  3) ;- (LCDC) Interface Width
AT91C_LCDC_IFWIDTH_FOURBITSWIDTH EQU (0x0 <<  3) ;- (LCDC) 4 Bits
AT91C_LCDC_IFWIDTH_EIGTHBITSWIDTH EQU (0x1 <<  3) ;- (LCDC) 8 Bits
AT91C_LCDC_IFWIDTH_SIXTEENBITSWIDTH EQU (0x2 <<  3) ;- (LCDC) 16 Bits
AT91C_LCDC_PIXELSIZE      EQU (0x7 <<  5) ;- (LCDC) Bits per pixel
AT91C_LCDC_PIXELSIZE_ONEBITSPERPIXEL EQU (0x0 <<  5) ;- (LCDC) 1 Bits
AT91C_LCDC_PIXELSIZE_TWOBITSPERPIXEL EQU (0x1 <<  5) ;- (LCDC) 2 Bits
AT91C_LCDC_PIXELSIZE_FOURBITSPERPIXEL EQU (0x2 <<  5) ;- (LCDC) 4 Bits
AT91C_LCDC_PIXELSIZE_EIGTHBITSPERPIXEL EQU (0x3 <<  5) ;- (LCDC) 8 Bits
AT91C_LCDC_PIXELSIZE_SIXTEENBITSPERPIXEL EQU (0x4 <<  5) ;- (LCDC) 16 Bits
AT91C_LCDC_PIXELSIZE_TWENTYFOURBITSPERPIXEL EQU (0x5 <<  5) ;- (LCDC) 24 Bits
AT91C_LCDC_INVVD          EQU (0x1 <<  8) ;- (LCDC) lcd datas polarity
AT91C_LCDC_INVVD_NORMALPOL EQU (0x0 <<  8) ;- (LCDC) Normal Polarity
AT91C_LCDC_INVVD_INVERTEDPOL EQU (0x1 <<  8) ;- (LCDC) Inverted Polarity
AT91C_LCDC_INVFRAME       EQU (0x1 <<  9) ;- (LCDC) lcd vsync polarity
AT91C_LCDC_INVFRAME_NORMALPOL EQU (0x0 <<  9) ;- (LCDC) Normal Polarity
AT91C_LCDC_INVFRAME_INVERTEDPOL EQU (0x1 <<  9) ;- (LCDC) Inverted Polarity
AT91C_LCDC_INVLINE        EQU (0x1 << 10) ;- (LCDC) lcd hsync polarity
AT91C_LCDC_INVLINE_NORMALPOL EQU (0x0 << 10) ;- (LCDC) Normal Polarity
AT91C_LCDC_INVLINE_INVERTEDPOL EQU (0x1 << 10) ;- (LCDC) Inverted Polarity
AT91C_LCDC_INVCLK         EQU (0x1 << 11) ;- (LCDC) lcd pclk polarity
AT91C_LCDC_INVCLK_NORMALPOL EQU (0x0 << 11) ;- (LCDC) Normal Polarity
AT91C_LCDC_INVCLK_INVERTEDPOL EQU (0x1 << 11) ;- (LCDC) Inverted Polarity
AT91C_LCDC_INVDVAL        EQU (0x1 << 12) ;- (LCDC) lcd dval polarity
AT91C_LCDC_INVDVAL_NORMALPOL EQU (0x0 << 12) ;- (LCDC) Normal Polarity
AT91C_LCDC_INVDVAL_INVERTEDPOL EQU (0x1 << 12) ;- (LCDC) Inverted Polarity
AT91C_LCDC_CLKMOD         EQU (0x1 << 15) ;- (LCDC) lcd pclk Mode
AT91C_LCDC_CLKMOD_ACTIVEONLYDISP EQU (0x0 << 15) ;- (LCDC) Active during display period
AT91C_LCDC_CLKMOD_ALWAYSACTIVE EQU (0x1 << 15) ;- (LCDC) Always Active
AT91C_LCDC_MEMOR          EQU (0x1 << 31) ;- (LCDC) lcd pclk Mode
AT91C_LCDC_MEMOR_BIGIND   EQU (0x0 << 31) ;- (LCDC) Big Endian
AT91C_LCDC_MEMOR_LITTLEIND EQU (0x1 << 31) ;- (LCDC) Little Endian
// - -------- LCDC_TIM1 : (LCDC Offset: 0x808) LCDC Timing Config 1 Register -------- 
AT91C_LCDC_VFP            EQU (0xFF <<  0) ;- (LCDC) Vertical Front Porch
AT91C_LCDC_VBP            EQU (0xFF <<  8) ;- (LCDC) Vertical Back Porch
AT91C_LCDC_VPW            EQU (0x3F << 16) ;- (LCDC) Vertical Synchronization Pulse Width
AT91C_LCDC_VHDLY          EQU (0xF << 24) ;- (LCDC) Vertical to Horizontal Delay
// - -------- LCDC_TIM2 : (LCDC Offset: 0x80c) LCDC Timing Config 2 Register -------- 
AT91C_LCDC_HBP            EQU (0xFF <<  0) ;- (LCDC) Horizontal Back Porch
AT91C_LCDC_HPW            EQU (0x3F <<  8) ;- (LCDC) Horizontal Synchronization Pulse Width
AT91C_LCDC_HFP            EQU (0x3FF << 22) ;- (LCDC) Horizontal Front Porch
// - -------- LCDC_LCDFRCFG : (LCDC Offset: 0x810) LCD Frame Config Register -------- 
AT91C_LCDC_LINEVAL        EQU (0x7FF <<  0) ;- (LCDC) Vertical Size of LCD Module
AT91C_LCDC_HOZVAL         EQU (0x7FF << 21) ;- (LCDC) Horizontal Size of LCD Module
// - -------- LCDC_FIFO : (LCDC Offset: 0x814) LCD FIFO Register -------- 
AT91C_LCDC_FIFOTH         EQU (0xFFFF <<  0) ;- (LCDC) FIFO Threshold
// - -------- LCDC_MVAL : (LCDC Offset: 0x818) LCD Mode Toggle Rate Value Register -------- 
AT91C_LCDC_MVALUE         EQU (0xFF <<  0) ;- (LCDC) Toggle Rate Value
AT91C_LCDC_MMODE          EQU (0x1 << 31) ;- (LCDC) Toggle Rate Sel
AT91C_LCDC_MMODE_EACHFRAME EQU (0x0 << 31) ;- (LCDC) Each Frame
AT91C_LCDC_MMODE_MVALDEFINED EQU (0x1 << 31) ;- (LCDC) Defined by MVAL
// - -------- LCDC_DP1_2 : (LCDC Offset: 0x81c) Dithering Pattern 1/2 -------- 
AT91C_LCDC_DP1_2_FIELD    EQU (0xFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_DP4_7 : (LCDC Offset: 0x820) Dithering Pattern 4/7 -------- 
AT91C_LCDC_DP4_7_FIELD    EQU (0xFFFFFFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_DP3_5 : (LCDC Offset: 0x824) Dithering Pattern 3/5 -------- 
AT91C_LCDC_DP3_5_FIELD    EQU (0xFFFFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_DP2_3 : (LCDC Offset: 0x828) Dithering Pattern 2/3 -------- 
AT91C_LCDC_DP2_3_FIELD    EQU (0xFFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_DP5_7 : (LCDC Offset: 0x82c) Dithering Pattern 5/7 -------- 
AT91C_LCDC_DP5_7_FIELD    EQU (0xFFFFFFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_DP3_4 : (LCDC Offset: 0x830) Dithering Pattern 3/4 -------- 
AT91C_LCDC_DP3_4_FIELD    EQU (0xFFFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_DP4_5 : (LCDC Offset: 0x834) Dithering Pattern 4/5 -------- 
AT91C_LCDC_DP4_5_FIELD    EQU (0xFFFFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_DP6_7 : (LCDC Offset: 0x838) Dithering Pattern 6/7 -------- 
AT91C_LCDC_DP6_7_FIELD    EQU (0xFFFFFFF <<  0) ;- (LCDC) Ratio
// - -------- LCDC_PWRCON : (LCDC Offset: 0x83c) LCDC Power Control Register -------- 
AT91C_LCDC_PWR            EQU (0x1 <<  0) ;- (LCDC) LCD Module Power Control
AT91C_LCDC_GUARDT         EQU (0x7F <<  1) ;- (LCDC) Delay in Frame Period
AT91C_LCDC_BUSY           EQU (0x1 << 31) ;- (LCDC) Read Only : 1 indicates that LCDC is busy
AT91C_LCDC_BUSY_LCDNOTBUSY EQU (0x0 << 31) ;- (LCDC) LCD is Not Busy
AT91C_LCDC_BUSY_LCDBUSY   EQU (0x1 << 31) ;- (LCDC) LCD is Busy
// - -------- LCDC_CTRSTCON : (LCDC Offset: 0x840) LCDC Contrast Control Register -------- 
AT91C_LCDC_PS             EQU (0x3 <<  0) ;- (LCDC) LCD Contrast Counter Prescaler
AT91C_LCDC_PS_NOTDIVIDED  EQU (0x0) ;- (LCDC) Counter Freq is System Freq.
AT91C_LCDC_PS_DIVIDEDBYTWO EQU (0x1) ;- (LCDC) Counter Freq is System Freq divided by 2.
AT91C_LCDC_PS_DIVIDEDBYFOUR EQU (0x2) ;- (LCDC) Counter Freq is System Freq divided by 4.
AT91C_LCDC_PS_DIVIDEDBYEIGHT EQU (0x3) ;- (LCDC) Counter Freq is System Freq divided by 8.
AT91C_LCDC_POL            EQU (0x1 <<  2) ;- (LCDC) Polarity of output Pulse
AT91C_LCDC_POL_NEGATIVEPULSE EQU (0x0 <<  2) ;- (LCDC) Negative Pulse
AT91C_LCDC_POL_POSITIVEPULSE EQU (0x1 <<  2) ;- (LCDC) Positive Pulse
AT91C_LCDC_ENA            EQU (0x1 <<  3) ;- (LCDC) PWM generator Control
AT91C_LCDC_ENA_PWMGEMDISABLED EQU (0x0 <<  3) ;- (LCDC) PWM Generator Disabled
AT91C_LCDC_ENA_PWMGEMENABLED EQU (0x1 <<  3) ;- (LCDC) PWM Generator Disabled
// - -------- LCDC_CTRSTVAL : (LCDC Offset: 0x844) Contrast Value Register -------- 
AT91C_LCDC_CVAL           EQU (0xFF <<  0) ;- (LCDC) PWM Compare Value
// - -------- LCDC_IER : (LCDC Offset: 0x848) LCDC Interrupt Enable Register -------- 
AT91C_LCDC_LNI            EQU (0x1 <<  0) ;- (LCDC) Line Interrupt
AT91C_LCDC_LSTLNI         EQU (0x1 <<  1) ;- (LCDC) Last Line Interrupt
AT91C_LCDC_EOFI           EQU (0x1 <<  2) ;- (LCDC) End Of Frame Interrupt
AT91C_LCDC_UFLWI          EQU (0x1 <<  4) ;- (LCDC) FIFO Underflow Interrupt
AT91C_LCDC_OWRI           EQU (0x1 <<  5) ;- (LCDC) Over Write Interrupt
AT91C_LCDC_MERI           EQU (0x1 <<  6) ;- (LCDC) Memory Error  Interrupt
// - -------- LCDC_IDR : (LCDC Offset: 0x84c) LCDC Interrupt Disable Register -------- 
// - -------- LCDC_IMR : (LCDC Offset: 0x850) LCDC Interrupt Mask Register -------- 
// - -------- LCDC_ISR : (LCDC Offset: 0x854) LCDC Interrupt Status Register -------- 
// - -------- LCDC_ICR : (LCDC Offset: 0x858) LCDC Interrupt Clear Register -------- 
// - -------- LCDC_GPR : (LCDC Offset: 0x85c) LCDC General Purpose Register -------- 
AT91C_LCDC_GPRBUS         EQU (0xFF <<  0) ;- (LCDC) 8 bits available
// - -------- LCDC_ITR : (LCDC Offset: 0x860) Interrupts Test Register -------- 
// - -------- LCDC_IRR : (LCDC Offset: 0x864) Interrupts Raw Status Register -------- 

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR DMA controller from Synopsys
// - *****************************************************************************
// - -------- DMA_SAR : (DMA Offset: 0x0)  -------- 
AT91C_DMA_SADD            EQU (0x0 <<  0) ;- (DMA) Source Address of DMA Transfer
// - -------- DMA_DAR : (DMA Offset: 0x8)  -------- 
AT91C_DMA_DADD            EQU (0x0 <<  0) ;- (DMA) Destination Address of DMA Transfer
// - -------- DMA_LLP : (DMA Offset: 0x10)  -------- 
AT91C_DMA_LOC             EQU (0x0 <<  0) ;- (DMA) Address of the Next LLI
// - -------- DMA_CTLl : (DMA Offset: 0x18)  -------- 
AT91C_DMA_INT_EN          EQU (0x1 <<  0) ;- (DMA) Interrupt Enable Bit
AT91C_DMA_DST_TR_WIDTH    EQU (0x7 <<  1) ;- (DMA) Destination Transfer Width
AT91C_DMA_SRC_TR_WIDTH    EQU (0x7 <<  4) ;- (DMA) Source Transfer Width
AT91C_DMA_DINC            EQU (0x3 <<  7) ;- (DMA) Destination Address Increment
AT91C_DMA_SINC            EQU (0x3 <<  9) ;- (DMA) Source Address Increment
AT91C_DMA_DEST_MSIZE      EQU (0x7 << 11) ;- (DMA) Destination Burst Transaction Length
AT91C_DMA_SRC_MSIZE       EQU (0x7 << 14) ;- (DMA) Source Burst Transaction Length
AT91C_DMA_S_GATH_EN       EQU (0x1 << 17) ;- (DMA) Source Gather Enable Bit
AT91C_DMA_D_SCAT_EN       EQU (0x1 << 18) ;- (DMA) Destination Scatter Enable Bit
AT91C_DMA_TT_FC           EQU (0x7 << 20) ;- (DMA) Transfer Type and Flow Control
AT91C_DMA_DMS             EQU (0x3 << 23) ;- (DMA) Destination Master Select
AT91C_DMA_SMS             EQU (0x3 << 25) ;- (DMA) Source Master Select
AT91C_DMA_LLP_D_EN        EQU (0x1 << 27) ;- (DMA) Destination Block Chaining Enable
AT91C_DMA_LLP_S_EN        EQU (0x1 << 28) ;- (DMA) Source Block Chaining Enable
// - -------- DMA_CTLh : (DMA Offset: 0x1c)  -------- 
AT91C_DMA_BLOCK_TS        EQU (0xFFF <<  0) ;- (DMA) Block Transfer Size
AT91C_DMA_DONE            EQU (0x1 << 12) ;- (DMA) Done bit
// - -------- DMA_CFGl : (DMA Offset: 0x40)  -------- 
AT91C_DMA_CH_PRIOR        EQU (0x7 <<  5) ;- (DMA) Channel Priority
AT91C_DMA_CH_SUSP         EQU (0x1 <<  8) ;- (DMA) Channel Suspend
AT91C_DMA_FIFO_EMPT       EQU (0x1 <<  9) ;- (DMA) Fifo Empty
AT91C_DMA_HS_SEL_DS       EQU (0x1 << 10) ;- (DMA) Destination Software or Hardware Handshaking Select
AT91C_DMA_HS_SEL_SR       EQU (0x1 << 11) ;- (DMA) Source Software or Hardware Handshaking Select
AT91C_DMA_LOCK_CH_L       EQU (0x3 << 12) ;- (DMA) Channel Lock Level
AT91C_DMA_LOCK_B_L        EQU (0x3 << 14) ;- (DMA) Bus Lock Level
AT91C_DMA_LOCK_CH         EQU (0x1 << 16) ;- (DMA) Channel Lock Bit
AT91C_DMA_LOCK_B          EQU (0x1 << 17) ;- (DMA) Bus Lock Bit
AT91C_DMA_DS_HS_POL       EQU (0x1 << 18) ;- (DMA) Destination Handshaking Interface Polarity
AT91C_DMA_SR_HS_POL       EQU (0x1 << 19) ;- (DMA) Source Handshaking Interface Polarity
AT91C_DMA_MAX_ABRST       EQU (0x3FF << 20) ;- (DMA) Maximum AMBA Burst Length
AT91C_DMA_RELOAD_SR       EQU (0x1 << 30) ;- (DMA) Automatic Source Reload
AT91C_DMA_RELOAD_DS       EQU (0x1 << 31) ;- (DMA) Automatic Destination Reload
// - -------- DMA_CFGh : (DMA Offset: 0x44)  -------- 
AT91C_DMA_FCMODE          EQU (0x1 <<  0) ;- (DMA) Flow Control Mode
AT91C_DMA_FIFO_MODE       EQU (0x1 <<  1) ;- (DMA) Fifo Mode Select
AT91C_DMA_PROTCTL         EQU (0x7 <<  2) ;- (DMA) Protection Control
AT91C_DMA_DS_UPD_EN       EQU (0x1 <<  5) ;- (DMA) Destination Status Update Enable
AT91C_DMA_SS_UPD_EN       EQU (0x1 <<  6) ;- (DMA) Source Status Update Enable
AT91C_DMA_SRC_PER         EQU (0xF <<  7) ;- (DMA) Source Hardware Handshaking Interface
AT91C_DMA_DEST_PER        EQU (0xF << 11) ;- (DMA) Destination Hardware Handshaking Interface
// - -------- DMA_SGR : (DMA Offset: 0x48)  -------- 
AT91C_DMA_SGI             EQU (0xFFFFF <<  0) ;- (DMA) Source Gather Interval
AT91C_DMA_SGC             EQU (0xFFF << 20) ;- (DMA) Source Gather Count
// - -------- DMA_DSR : (DMA Offset: 0x50)  -------- 
AT91C_DMA_DSI             EQU (0xFFFFF <<  0) ;- (DMA) Destination Scatter Interval
AT91C_DMA_DSC             EQU (0xFFF << 20) ;- (DMA) Destination Scatter Count
// - -------- DMA_SAR : (DMA Offset: 0x58)  -------- 
// - -------- DMA_DAR : (DMA Offset: 0x60)  -------- 
// - -------- DMA_LLP : (DMA Offset: 0x68)  -------- 
// - -------- DMA_CTLl : (DMA Offset: 0x70)  -------- 
// - -------- DMA_CTLh : (DMA Offset: 0x74)  -------- 
// - -------- DMA_CFGl : (DMA Offset: 0x98)  -------- 
// - -------- DMA_CFGh : (DMA Offset: 0x9c)  -------- 
// - -------- DMA_SGR : (DMA Offset: 0xa0)  -------- 
// - -------- DMA_DSR : (DMA Offset: 0xa8)  -------- 
// - -------- DMA_RAWTFR : (DMA Offset: 0x2c0)  -------- 
AT91C_DMA_RAW             EQU (0x7 <<  0) ;- (DMA) Raw Interrupt for each Channel
// - -------- DMA_RAWBLOCK : (DMA Offset: 0x2c8)  -------- 
// - -------- DMA_RAWSRCTRAN : (DMA Offset: 0x2d0)  -------- 
// - -------- DMA_RAWDSTTRAN : (DMA Offset: 0x2d8)  -------- 
// - -------- DMA_RAWERR : (DMA Offset: 0x2e0)  -------- 
// - -------- DMA_STATUSTFR : (DMA Offset: 0x2e8)  -------- 
AT91C_DMA_STATUS          EQU (0x7 <<  0) ;- (DMA) Interrupt for each Channel
// - -------- DMA_STATUSBLOCK : (DMA Offset: 0x2f0)  -------- 
// - -------- DMA_STATUSSRCTRAN : (DMA Offset: 0x2f8)  -------- 
// - -------- DMA_STATUSDSTTRAN : (DMA Offset: 0x300)  -------- 
// - -------- DMA_STATUSERR : (DMA Offset: 0x308)  -------- 
// - -------- DMA_MASKTFR : (DMA Offset: 0x310)  -------- 
AT91C_DMA_INT_MASK        EQU (0x7 <<  0) ;- (DMA) Interrupt Mask for each Channel
AT91C_DMA_INT_M_WE        EQU (0x7 <<  8) ;- (DMA) Interrupt Mask Write Enable for each Channel
// - -------- DMA_MASKBLOCK : (DMA Offset: 0x318)  -------- 
// - -------- DMA_MASKSRCTRAN : (DMA Offset: 0x320)  -------- 
// - -------- DMA_MASKDSTTRAN : (DMA Offset: 0x328)  -------- 
// - -------- DMA_MASKERR : (DMA Offset: 0x330)  -------- 
// - -------- DMA_CLEARTFR : (DMA Offset: 0x338)  -------- 
AT91C_DMA_CLEAR           EQU (0x7 <<  0) ;- (DMA) Interrupt Clear for each Channel
// - -------- DMA_CLEARBLOCK : (DMA Offset: 0x340)  -------- 
// - -------- DMA_CLEARSRCTRAN : (DMA Offset: 0x348)  -------- 
// - -------- DMA_CLEARDSTTRAN : (DMA Offset: 0x350)  -------- 
// - -------- DMA_CLEARERR : (DMA Offset: 0x358)  -------- 
// - -------- DMA_STATUSINT : (DMA Offset: 0x360)  -------- 
AT91C_DMA_TFR             EQU (0x1 <<  0) ;- (DMA) OR of the content of StatusTfr Register
AT91C_DMA_BLOCK           EQU (0x1 <<  1) ;- (DMA) OR of the content of StatusBlock Register
AT91C_DMA_SRCT            EQU (0x1 <<  2) ;- (DMA) OR of the content of StatusSrcTran Register
AT91C_DMA_DSTT            EQU (0x1 <<  3) ;- (DMA) OR of the content of StatusDstTran Register
AT91C_DMA_ERR             EQU (0x1 <<  4) ;- (DMA) OR of the content of StatusErr Register
// - -------- DMA_REQSRCREG : (DMA Offset: 0x368)  -------- 
AT91C_DMA_SRC_REQ         EQU (0x7 <<  0) ;- (DMA) Source Request
AT91C_DMA_REQ_WE          EQU (0x7 <<  8) ;- (DMA) Request Write Enable
// - -------- DMA_REQDSTREG : (DMA Offset: 0x370)  -------- 
AT91C_DMA_DST_REQ         EQU (0x7 <<  0) ;- (DMA) Destination Request
// - -------- DMA_SGLREQSRCREG : (DMA Offset: 0x378)  -------- 
AT91C_DMA_S_SG_REQ        EQU (0x7 <<  0) ;- (DMA) Source Single Request
// - -------- DMA_SGLREQDSTREG : (DMA Offset: 0x380)  -------- 
AT91C_DMA_D_SG_REQ        EQU (0x7 <<  0) ;- (DMA) Destination Single Request
// - -------- DMA_LSTREQSRCREG : (DMA Offset: 0x388)  -------- 
AT91C_DMA_LSTSRC          EQU (0x7 <<  0) ;- (DMA) Source Last Transaction Request
AT91C_DMA_LSTSR_WE        EQU (0x7 <<  8) ;- (DMA) Source Last Transaction Request Write Enable
// - -------- DMA_LSTREQDSTREG : (DMA Offset: 0x390)  -------- 
AT91C_DMA_LSTDST          EQU (0x7 <<  0) ;- (DMA) Destination Last Transaction Request
AT91C_DMA_LSTDS_WE        EQU (0x7 <<  8) ;- (DMA) Destination Last Transaction Request Write Enable
// - -------- DMA_DMACFGREG : (DMA Offset: 0x398)  -------- 
AT91C_DMA_DMA_EN          EQU (0x7 <<  0) ;- (DMA) Controller Enable
// - -------- DMA_CHENREG : (DMA Offset: 0x3a0)  -------- 
AT91C_DMA_CH_EN           EQU (0x7 <<  0) ;- (DMA) Channel Enable
AT91C_DMA_CH_EN_WE        EQU (0x7 <<  8) ;- (DMA) Channel Enable Write Enable
// - -------- DMA_DMATESTREG : (DMA Offset: 0x3b0)  -------- 
AT91C_DMA_TEST_SLV_IF     EQU (0x1 <<  0) ;- (DMA) Test Mode for Slave Interface

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR USB Device Interface
// - *****************************************************************************
// - -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- 
AT91C_UDP_FRM_NUM         EQU (0x7FF <<  0) ;- (UDP) Frame Number as Defined in the Packet Field Formats
AT91C_UDP_FRM_ERR         EQU (0x1 << 16) ;- (UDP) Frame Error
AT91C_UDP_FRM_OK          EQU (0x1 << 17) ;- (UDP) Frame OK
// - -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- 
AT91C_UDP_FADDEN          EQU (0x1 <<  0) ;- (UDP) Function Address Enable
AT91C_UDP_CONFG           EQU (0x1 <<  1) ;- (UDP) Configured
AT91C_UDP_ESR             EQU (0x1 <<  2) ;- (UDP) Enable Send Resume
AT91C_UDP_RSMINPR         EQU (0x1 <<  3) ;- (UDP) A Resume Has Been Sent to the Host
AT91C_UDP_RMWUPE          EQU (0x1 <<  4) ;- (UDP) Remote Wake Up Enable
// - -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- 
AT91C_UDP_FADD            EQU (0xFF <<  0) ;- (UDP) Function Address Value
AT91C_UDP_FEN             EQU (0x1 <<  8) ;- (UDP) Function Enable
// - -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- 
AT91C_UDP_EPINT0          EQU (0x1 <<  0) ;- (UDP) Endpoint 0 Interrupt
AT91C_UDP_EPINT1          EQU (0x1 <<  1) ;- (UDP) Endpoint 0 Interrupt
AT91C_UDP_EPINT2          EQU (0x1 <<  2) ;- (UDP) Endpoint 2 Interrupt
AT91C_UDP_EPINT3          EQU (0x1 <<  3) ;- (UDP) Endpoint 3 Interrupt
AT91C_UDP_EPINT4          EQU (0x1 <<  4) ;- (UDP) Endpoint 4 Interrupt
AT91C_UDP_EPINT5          EQU (0x1 <<  5) ;- (UDP) Endpoint 5 Interrupt
AT91C_UDP_RXSUSP          EQU (0x1 <<  8) ;- (UDP) USB Suspend Interrupt
AT91C_UDP_RXRSM           EQU (0x1 <<  9) ;- (UDP) USB Resume Interrupt
AT91C_UDP_EXTRSM          EQU (0x1 << 10) ;- (UDP) USB External Resume Interrupt
AT91C_UDP_SOFINT          EQU (0x1 << 11) ;- (UDP) USB Start Of frame Interrupt
AT91C_UDP_WAKEUP          EQU (0x1 << 13) ;- (UDP) USB Resume Interrupt
// - -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- 
// - -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- 
// - -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- 
AT91C_UDP_ENDBUSRES       EQU (0x1 << 12) ;- (UDP) USB End Of Bus Reset Interrupt
// - -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- 
// - -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- 
AT91C_UDP_EP0             EQU (0x1 <<  0) ;- (UDP) Reset Endpoint 0
AT91C_UDP_EP1             EQU (0x1 <<  1) ;- (UDP) Reset Endpoint 1
AT91C_UDP_EP2             EQU (0x1 <<  2) ;- (UDP) Reset Endpoint 2
AT91C_UDP_EP3             EQU (0x1 <<  3) ;- (UDP) Reset Endpoint 3
AT91C_UDP_EP4             EQU (0x1 <<  4) ;- (UDP) Reset Endpoint 4
AT91C_UDP_EP5             EQU (0x1 <<  5) ;- (UDP) Reset Endpoint 5
// - -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- 
AT91C_UDP_TXCOMP          EQU (0x1 <<  0) ;- (UDP) Generates an IN packet with data previously written in the DPR
AT91C_UDP_RX_DATA_BK0     EQU (0x1 <<  1) ;- (UDP) Receive Data Bank 0
AT91C_UDP_RXSETUP         EQU (0x1 <<  2) ;- (UDP) Sends STALL to the Host (Control endpoints)
AT91C_UDP_ISOERROR        EQU (0x1 <<  3) ;- (UDP) Isochronous error (Isochronous endpoints)
AT91C_UDP_STALLSENT       EQU (0x1 <<  3) ;- (UDP) Stall sent (Control, bulk, interrupt endpoints)
AT91C_UDP_TXPKTRDY        EQU (0x1 <<  4) ;- (UDP) Transmit Packet Ready
AT91C_UDP_FORCESTALL      EQU (0x1 <<  5) ;- (UDP) Force Stall (used by Control, Bulk and Isochronous endpoints).
AT91C_UDP_RX_DATA_BK1     EQU (0x1 <<  6) ;- (UDP) Receive Data Bank 1 (only used by endpoints with ping-pong attributes).
AT91C_UDP_DIR             EQU (0x1 <<  7) ;- (UDP) Transfer Direction
AT91C_UDP_EPTYPE          EQU (0x7 <<  8) ;- (UDP) Endpoint type
AT91C_UDP_EPTYPE_CTRL     EQU (0x0 <<  8) ;- (UDP) Control
AT91C_UDP_EPTYPE_ISO_OUT  EQU (0x1 <<  8) ;- (UDP) Isochronous OUT
AT91C_UDP_EPTYPE_BULK_OUT EQU (0x2 <<  8) ;- (UDP) Bulk OUT
AT91C_UDP_EPTYPE_INT_OUT  EQU (0x3 <<  8) ;- (UDP) Interrupt OUT
AT91C_UDP_EPTYPE_ISO_IN   EQU (0x5 <<  8) ;- (UDP) Isochronous IN
AT91C_UDP_EPTYPE_BULK_IN  EQU (0x6 <<  8) ;- (UDP) Bulk IN
AT91C_UDP_EPTYPE_INT_IN   EQU (0x7 <<  8) ;- (UDP) Interrupt IN
AT91C_UDP_DTGLE           EQU (0x1 << 11) ;- (UDP) Data Toggle
AT91C_UDP_EPEDS           EQU (0x1 << 15) ;- (UDP) Endpoint Enable Disable
AT91C_UDP_RXBYTECNT       EQU (0x7FF << 16) ;- (UDP) Number Of Bytes Available in the FIFO
// - -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- 
AT91C_UDP_TXVDIS          EQU (0x1 <<  8) ;- (UDP) 
AT91C_UDP_PUON            EQU (0x1 <<  9) ;- (UDP) Pull-up ON

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR USB Host Interface
// - *****************************************************************************

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Trickbox (external) / SIMULATION ONLY
// - *****************************************************************************
// - -------- TBOX_DMAEXTREQ : (TBOX Offset: 0x810)  -------- 
AT91C_TBOX_DMAEXTREQ0     EQU (0x1 <<  0) ;- (TBOX) DMA external request 0
AT91C_TBOX_DMAEXTREQ1     EQU (0x1 <<  1) ;- (TBOX) DMA external request 1
AT91C_TBOX_DMAEXTREQ2     EQU (0x1 <<  2) ;- (TBOX) DMA external request 2
AT91C_TBOX_DMAEXTREQ3     EQU (0x1 <<  3) ;- (TBOX) DMA external request 3

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Error Correction Code controller
// - *****************************************************************************
// - -------- ECC_CR : (ECC Offset: 0x0) ECC reset register -------- 
AT91C_ECC_RST             EQU (0x1 <<  0) ;- (ECC) ECC reset parity
// - -------- ECC_MR : (ECC Offset: 0x4) ECC page size register -------- 
AT91C_ECC_PAGE_SIZE       EQU (0x3 <<  0) ;- (ECC) Nand Flash page size
// - -------- ECC_SR : (ECC Offset: 0x8) ECC status register -------- 
AT91C_ECC_RECERR          EQU (0x1 <<  0) ;- (ECC) ECC error
AT91C_ECC_ECCERR          EQU (0x1 <<  1) ;- (ECC) ECC single error
AT91C_ECC_MULERR          EQU (0x1 <<  2) ;- (ECC) ECC_MULERR
// - -------- ECC_PR : (ECC Offset: 0xc) ECC parity register -------- 
AT91C_ECC_BITADDR         EQU (0xF <<  0) ;- (ECC) Bit address error
AT91C_ECC_WORDADDR        EQU (0xFFF <<  4) ;- (ECC) address of the failing bit
// - -------- ECC_NPR : (ECC Offset: 0x10) ECC N parity register -------- 
AT91C_ECC_NPARITY         EQU (0xFFFF <<  0) ;- (ECC) ECC parity N 
// - -------- ECC_VR : (ECC Offset: 0xfc) ECC version register -------- 
AT91C_ECC_VR              EQU (0xF <<  0) ;- (ECC) ECC version register

// - *****************************************************************************
// -              SOFTWARE API DEFINITION  FOR Image Sensor Interface
// - *****************************************************************************
// - -------- ISI_CR1 : (ISI Offset: 0x0) ISI Control Register 1 -------- 
AT91C_ISI_RST             EQU (0x1 <<  0) ;- (ISI) Image sensor interface reset
AT91C_ISI_DISABLE         EQU (0x1 <<  1) ;- (ISI) image sensor disable.
AT91C_ISI_HSYNC_POL       EQU (0x1 <<  2) ;- (ISI) Horizontal synchronisation polarity
AT91C_ISI_PIXCLK_POL      EQU (0x1 <<  4) ;- (ISI) Pixel Clock Polarity
AT91C_ISI_EMB_SYNC        EQU (0x1 <<  6) ;- (ISI) Embedded synchronisation
AT91C_ISI_CRC_SYNC        EQU (0x1 <<  7) ;- (ISI) CRC correction
AT91C_ISI_FULL            EQU (0x1 << 12) ;- (ISI) Full mode is allowed
AT91C_ISI_THMASK          EQU (0x3 << 13) ;- (ISI) DMA Burst Mask
AT91C_ISI_THMASK_4_8_16_BURST EQU (0x0 << 13) ;- (ISI) 4,8 and 16 AHB burst are allowed
AT91C_ISI_THMASK_8_16_BURST EQU (0x1 << 13) ;- (ISI) 8 and 16 AHB burst are allowed
AT91C_ISI_THMASK_16_BURST EQU (0x2 << 13) ;- (ISI) Only 16 AHB burst are allowed
AT91C_ISI_CODEC_ON        EQU (0x1 << 15) ;- (ISI) Enable the codec path
AT91C_ISI_SLD             EQU (0xFF << 16) ;- (ISI) Start of Line Delay
AT91C_ISI_SFD             EQU (0xFF << 24) ;- (ISI) Start of frame Delay
// - -------- ISI_CR2 : (ISI Offset: 0x4) ISI Control Register 2 -------- 
AT91C_ISI_IM_VSIZE        EQU (0x7FF <<  0) ;- (ISI) Vertical size of the Image sensor [0..2047]
AT91C_ISI_GS_MODE         EQU (0x1 << 11) ;- (ISI) Grayscale Memory Mode
AT91C_ISI_RGB_MODE        EQU (0x3 << 12) ;- (ISI) RGB mode
AT91C_ISI_RGB_MODE_RGB_888 EQU (0x0 << 12) ;- (ISI) RGB 8:8:8 24 bits
AT91C_ISI_RGB_MODE_RGB_565 EQU (0x1 << 12) ;- (ISI) RGB 5:6:5 16 bits
AT91C_ISI_RGB_MODE_RGB_555 EQU (0x2 << 12) ;- (ISI) RGB 5:5:5 16 bits
AT91C_ISI_GRAYSCALE       EQU (0x1 << 13) ;- (ISI) Grayscale Mode
AT91C_ISI_RGB_SWAP        EQU (0x1 << 14) ;- (ISI) RGB Swap
AT91C_ISI_COL_SPACE       EQU (0x1 << 15) ;- (ISI) Color space for the image data
AT91C_ISI_IM_HSIZE        EQU (0x7FF << 16) ;- (ISI) Horizontal size of the Image sensor [0..2047]
AT91C_ISI_RGB_MODE_YCC_DEF EQU (0x0 << 28) ;- (ISI) Cb(i) Y(i) Cr(i) Y(i+1)
AT91C_ISI_RGB_MODE_YCC_MOD1 EQU (0x1 << 28) ;- (ISI) Cr(i) Y(i) Cb(i) Y(i+1)
AT91C_ISI_RGB_MODE_YCC_MOD2 EQU (0x2 << 28) ;- (ISI) Y(i) Cb(i) Y(i+1) Cr(i)
AT91C_ISI_RGB_MODE_YCC_MOD3 EQU (0x3 << 28) ;- (ISI) Y(i) Cr(i) Y(i+1) Cb(i)
AT91C_ISI_RGB_CFG         EQU (0x3 << 30) ;- (ISI) RGB configuration
AT91C_ISI_RGB_CFG_RGB_DEF EQU (0x0 << 30) ;- (ISI) R/G(MSB)  G(LSB)/B  R/G(MSB)  G(LSB)/B
AT91C_ISI_RGB_CFG_RGB_MOD1 EQU (0x1 << 30) ;- (ISI) B/G(MSB)  G(LSB)/R  B/G(MSB)  G(LSB)/R
AT91C_ISI_RGB_CFG_RGB_MOD2 EQU (0x2 << 30) ;- (ISI) G(LSB)/R  B/G(MSB)  G(LSB)/R  B/G(MSB)
AT91C_ISI_RGB_CFG_RGB_MOD3 EQU (0x3 << 30) ;- (ISI) G(LSB)/B  R/G(MSB)  G(LSB)/B  R/G(MSB)
// - -------- ISI_SR : (ISI Offset: 0x8) ISI Status Register -------- 
AT91C_ISI_SOF             EQU (0x1 <<  0) ;- (ISI) Start of Frame
AT91C_ISI_DIS             EQU (0x1 <<  1) ;- (ISI) Image Sensor Interface disable
AT91C_ISI_SOFTRST         EQU (0x1 <<  2) ;- (ISI) Software Reset
AT91C_ISI_CRC_ERR         EQU (0x1 <<  4) ;- (ISI) CRC synchronisation error
AT91C_ISI_FO_C_OVF        EQU (0x1 <<  5) ;- (ISI) Fifo Codec Overflow 
AT91C_ISI_FO_P_OVF        EQU (0x1 <<  6) ;- (ISI) Fifo Preview Overflow 
AT91C_ISI_FO_P_EMP        EQU (0x1 <<  7) ;- (ISI) Fifo Preview Empty
AT91C_ISI_FO_C_EMP        EQU (0x1 <<  8) ;- (ISI) Fifo Codec Empty
AT91C_ISI_FR_OVR          EQU (0x1 <<  9) ;- (ISI) Frame rate overun
// - -------- ISI_IER : (ISI Offset: 0xc) ISI Interrupt Enable Register -------- 
// - -------- ISI_IDR : (ISI Offset: 0x10) ISI Interrupt Disable Register -------- 
// - -------- ISI_IMR : (ISI Offset: 0x14) ISI Interrupt Mask Register -------- 
// - -------- ISI_PSIZE : (ISI Offset: 0x20) ISI Preview Register -------- 
AT91C_ISI_PREV_VSIZE      EQU (0x3FF <<  0) ;- (ISI) Vertical size for the preview path
AT91C_ISI_PREV_HSIZE      EQU (0x3FF << 16) ;- (ISI) Horizontal size for the preview path
// - -------- ISI_Y2R_SET0 : (ISI Offset: 0x30) Color Space Conversion YCrCb to RGB Register -------- 
AT91C_ISI_Y2R_C0          EQU (0xFF <<  0) ;- (ISI) Color Space Conversion Matrix Coefficient C0
AT91C_ISI_Y2R_C1          EQU (0xFF <<  8) ;- (ISI) Color Space Conversion Matrix Coefficient C1
AT91C_ISI_Y2R_C2          EQU (0xFF << 16) ;- (ISI) Color Space Conversion Matrix Coefficient C2
AT91C_ISI_Y2R_C3          EQU (0xFF << 24) ;- (ISI) Color Space Conversion Matrix Coefficient C3
// - -------- ISI_Y2R_SET1 : (ISI Offset: 0x34) ISI Color Space Conversion YCrCb to RGB set 1 Register -------- 
AT91C_ISI_Y2R_C4          EQU (0x1FF <<  0) ;- (ISI) Color Space Conversion Matrix Coefficient C4
AT91C_ISI_Y2R_YOFF        EQU (0xFF << 12) ;- (ISI) Color Space Conversion Luninance default offset
AT91C_ISI_Y2R_CROFF       EQU (0xFF << 13) ;- (ISI) Color Space Conversion Red Chrominance default offset
AT91C_ISI_Y2R_CBFF        EQU (0xFF << 14) ;- (ISI) Color Space Conversion Luninance default offset
// - -------- ISI_R2Y_SET0 : (ISI Offset: 0x38) Color Space Conversion RGB to YCrCb set 0 register -------- 
AT91C_ISI_R2Y_C0          EQU (0x7F <<  0) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C0
AT91C_ISI_R2Y_C1          EQU (0x7F <<  1) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C1
AT91C_ISI_R2Y_C2          EQU (0x7F <<  3) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C2
AT91C_ISI_R2Y_ROFF        EQU (0x1 <<  4) ;- (ISI) Color Space Conversion Red component offset
// - -------- ISI_R2Y_SET1 : (ISI Offset: 0x3c) Color Space Conversion RGB to YCrCb set 1 register -------- 
AT91C_ISI_R2Y_C3          EQU (0x7F <<  0) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C3
AT91C_ISI_R2Y_C4          EQU (0x7F <<  1) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C4
AT91C_ISI_R2Y_C5          EQU (0x7F <<  3) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C5
AT91C_ISI_R2Y_GOFF        EQU (0x1 <<  4) ;- (ISI) Color Space Conversion Green component offset
// - -------- ISI_R2Y_SET2 : (ISI Offset: 0x40) Color Space Conversion RGB to YCrCb set 2 register -------- 
AT91C_ISI_R2Y_C6          EQU (0x7F <<  0) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C6
AT91C_ISI_R2Y_C7          EQU (0x7F <<  1) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C7
AT91C_ISI_R2Y_C8          EQU (0x7F <<  3) ;- (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C8
AT91C_ISI_R2Y_BOFF        EQU (0x1 <<  4) ;- (ISI) Color Space Conversion Blue component offset

// - *****************************************************************************
// -               REGISTER ADDRESS DEFINITION FOR AT91SAM9263
// - *****************************************************************************
// - ========== Register definition for SYS peripheral ========== 
AT91C_SYS_ECC1            EQU (0xFFFFE600) ;- (SYS) ECC 0
AT91C_SYS_ECC0            EQU (0xFFFFE000) ;- (SYS) ECC 0
AT91C_SYS_GPBR            EQU (0xFFFFFD60) ;- (SYS) General Purpose Register
// - ========== Register definition for EBI0 peripheral ========== 
AT91C_EBI0_DUMMY          EQU (0xFFFFE200) ;- (EBI0) Dummy register - Do not use
// - ========== Register definition for SDRAMC0 peripheral ========== 
AT91C_SDRAMC0_MDR         EQU (0xFFFFE224) ;- (SDRAMC0) SDRAM Memory Device Register
AT91C_SDRAMC0_IDR         EQU (0xFFFFE218) ;- (SDRAMC0) SDRAM Controller Interrupt Disable Register
AT91C_SDRAMC0_IMR         EQU (0xFFFFE21C) ;- (SDRAMC0) SDRAM Controller Interrupt Mask Register
AT91C_SDRAMC0_ISR         EQU (0xFFFFE220) ;- (SDRAMC0) SDRAM Controller Interrupt Mask Register
AT91C_SDRAMC0_HSR         EQU (0xFFFFE20C) ;- (SDRAMC0) SDRAM Controller High Speed Register
AT91C_SDRAMC0_TR          EQU (0xFFFFE204) ;- (SDRAMC0) SDRAM Controller Refresh Timer Register
AT91C_SDRAMC0_CR          EQU (0xFFFFE208) ;- (SDRAMC0) SDRAM Controller Configuration Register
AT91C_SDRAMC0_MR          EQU (0xFFFFE200) ;- (SDRAMC0) SDRAM Controller Mode Register
AT91C_SDRAMC0_LPR         EQU (0xFFFFE210) ;- (SDRAMC0) SDRAM Controller Low Power Register
AT91C_SDRAMC0_IER         EQU (0xFFFFE214) ;- (SDRAMC0) SDRAM Controller Interrupt Enable Register
// - ========== Register definition for SMC0 peripheral ========== 
AT91C_SMC0_CYCLE6         EQU (0xFFFFE468) ;- (SMC0)  Cycle Register for CS 6
AT91C_SMC0_SETUP6         EQU (0xFFFFE460) ;- (SMC0)  Setup Register for CS 6
AT91C_SMC0_PULSE3         EQU (0xFFFFE434) ;- (SMC0)  Pulse Register for CS 3
AT91C_SMC0_CYCLE1         EQU (0xFFFFE418) ;- (SMC0)  Cycle Register for CS 1
AT91C_SMC0_SETUP5         EQU (0xFFFFE450) ;- (SMC0)  Setup Register for CS 5
AT91C_SMC0_CYCLE7         EQU (0xFFFFE478) ;- (SMC0)  Cycle Register for CS 7
AT91C_SMC0_PULSE0         EQU (0xFFFFE404) ;- (SMC0)  Pulse Register for CS 0
AT91C_SMC0_CYCLE5         EQU (0xFFFFE458) ;- (SMC0)  Cycle Register for CS 5
AT91C_SMC0_CTRL0          EQU (0xFFFFE40C) ;- (SMC0)  Control Register for CS 0
AT91C_SMC0_SETUP7         EQU (0xFFFFE470) ;- (SMC0)  Setup Register for CS 7
AT91C_SMC0_CTRL4          EQU (0xFFFFE44C) ;- (SMC0)  Control Register for CS 4
AT91C_SMC0_CTRL1          EQU (0xFFFFE41C) ;- (SMC0)  Control Register for CS 1
AT91C_SMC0_CYCLE2         EQU (0xFFFFE428) ;- (SMC0)  Cycle Register for CS 2
AT91C_SMC0_PULSE7         EQU (0xFFFFE474) ;- (SMC0)  Pulse Register for CS 7
AT91C_SMC0_PULSE6         EQU (0xFFFFE464) ;- (SMC0)  Pulse Register for CS 6
AT91C_SMC0_CYCLE4         EQU (0xFFFFE448) ;- (SMC0)  Cycle Register for CS 4
AT91C_SMC0_CYCLE0         EQU (0xFFFFE408) ;- (SMC0)  Cycle Register for CS 0
AT91C_SMC0_CTRL6          EQU (0xFFFFE46C) ;- (SMC0)  Control Register for CS 6
AT91C_SMC0_CTRL5          EQU (0xFFFFE45C) ;- (SMC0)  Control Register for CS 5
AT91C_SMC0_SETUP0         EQU (0xFFFFE400) ;- (SMC0)  Setup Register for CS 0
AT91C_SMC0_SETUP4         EQU (0xFFFFE440) ;- (SMC0)  Setup Register for CS 4
AT91C_SMC0_PULSE1         EQU (0xFFFFE414) ;- (SMC0)  Pulse Register for CS 1
AT91C_SMC0_CTRL2          EQU (0xFFFFE42C) ;- (SMC0)  Control Register for CS 2
AT91C_SMC0_SETUP2         EQU (0xFFFFE420) ;- (SMC0)  Setup Register for CS 2
AT91C_SMC0_CTRL3          EQU (0xFFFFE43C) ;- (SMC0)  Control Register for CS 3
AT91C_SMC0_SETUP3         EQU (0xFFFFE430) ;- (SMC0)  Setup Register for CS 3
AT91C_SMC0_CTRL7          EQU (0xFFFFE47C) ;- (SMC0)  Control Register for CS 7
AT91C_SMC0_PULSE5         EQU (0xFFFFE454) ;- (SMC0)  Pulse Register for CS 5
AT91C_SMC0_PULSE4         EQU (0xFFFFE444) ;- (SMC0)  Pulse Register for CS 4
AT91C_SMC0_PULSE2         EQU (0xFFFFE424) ;- (SMC0)  Pulse Register for CS 2
AT91C_SMC0_CYCLE3         EQU (0xFFFFE438) ;- (SMC0)  Cycle Register for CS 3
AT91C_SMC0_SETUP1         EQU (0xFFFFE410) ;- (SMC0)  Setup Register for CS 1
// - ========== Register definition for EBI1 peripheral ========== 
AT91C_EBI1_DUMMY          EQU (0xFFFFE800) ;- (EBI1) Dummy register - Do not use
// - ========== Register definition for SDRAMC1 peripheral ========== 
AT91C_SDRAMC1_IMR         EQU (0xFFFFE81C) ;- (SDRAMC1) SDRAM Controller Interrupt Mask Register
AT91C_SDRAMC1_LPR         EQU (0xFFFFE810) ;- (SDRAMC1) SDRAM Controller Low Power Register
AT91C_SDRAMC1_CR          EQU (0xFFFFE808) ;- (SDRAMC1) SDRAM Controller Configuration Register
AT91C_SDRAMC1_HSR         EQU (0xFFFFE80C) ;- (SDRAMC1) SDRAM Controller High Speed Register
AT91C_SDRAMC1_MDR         EQU (0xFFFFE824) ;- (SDRAMC1) SDRAM Memory Device Register
AT91C_SDRAMC1_MR          EQU (0xFFFFE800) ;- (SDRAMC1) SDRAM Controller Mode Register
AT91C_SDRAMC1_ISR         EQU (0xFFFFE820) ;- (SDRAMC1) SDRAM Controller Interrupt Mask Register
AT91C_SDRAMC1_IDR         EQU (0xFFFFE818) ;- (SDRAMC1) SDRAM Controller Interrupt Disable Register
AT91C_SDRAMC1_IER         EQU (0xFFFFE814) ;- (SDRAMC1) SDRAM Controller Interrupt Enable Register
AT91C_SDRAMC1_TR          EQU (0xFFFFE804) ;- (SDRAMC1) SDRAM Controller Refresh Timer Register
// - ========== Register definition for SMC1 peripheral ========== 
AT91C_SMC1_PULSE4         EQU (0xFFFFEA44) ;- (SMC1)  Pulse Register for CS 4
AT91C_SMC1_SETUP2         EQU (0xFFFFEA20) ;- (SMC1)  Setup Register for CS 2
AT91C_SMC1_CYCLE0         EQU (0xFFFFEA08) ;- (SMC1)  Cycle Register for CS 0
AT91C_SMC1_SETUP7         EQU (0xFFFFEA70) ;- (SMC1)  Setup Register for CS 7
AT91C_SMC1_PULSE7         EQU (0xFFFFEA74) ;- (SMC1)  Pulse Register for CS 7
AT91C_SMC1_CTRL0          EQU (0xFFFFEA0C) ;- (SMC1)  Control Register for CS 0
AT91C_SMC1_SETUP3         EQU (0xFFFFEA30) ;- (SMC1)  Setup Register for CS 3
AT91C_SMC1_SETUP4         EQU (0xFFFFEA40) ;- (SMC1)  Setup Register for CS 4
AT91C_SMC1_CYCLE6         EQU (0xFFFFEA68) ;- (SMC1)  Cycle Register for CS 6
AT91C_SMC1_CTRL1          EQU (0xFFFFEA1C) ;- (SMC1)  Control Register for CS 1
AT91C_SMC1_CYCLE3         EQU (0xFFFFEA38) ;- (SMC1)  Cycle Register for CS 3
AT91C_SMC1_CTRL5          EQU (0xFFFFEA5C) ;- (SMC1)  Control Register for CS 5
AT91C_SMC1_CTRL3          EQU (0xFFFFEA3C) ;- (SMC1)  Control Register for CS 3
AT91C_SMC1_CYCLE4         EQU (0xFFFFEA48) ;- (SMC1)  Cycle Register for CS 4
AT91C_SMC1_SETUP6         EQU (0xFFFFEA60) ;- (SMC1)  Setup Register for CS 6
AT91C_SMC1_PULSE3         EQU (0xFFFFEA34) ;- (SMC1)  Pulse Register for CS 3
AT91C_SMC1_CTRL7          EQU (0xFFFFEA7C) ;- (SMC1)  Control Register for CS 7
AT91C_SMC1_SETUP1         EQU (0xFFFFEA10) ;- (SMC1)  Setup Register for CS 1
AT91C_SMC1_PULSE5         EQU (0xFFFFEA54) ;- (SMC1)  Pulse Register for CS 5
AT91C_SMC1_PULSE0         EQU (0xFFFFEA04) ;- (SMC1)  Pulse Register for CS 0
AT91C_SMC1_CYCLE5         EQU (0xFFFFEA58) ;- (SMC1)  Cycle Register for CS 5
AT91C_SMC1_PULSE6         EQU (0xFFFFEA64) ;- (SMC1)  Pulse Register for CS 6
AT91C_SMC1_SETUP5         EQU (0xFFFFEA50) ;- (SMC1)  Setup Register for CS 5
AT91C_SMC1_CTRL6          EQU (0xFFFFEA6C) ;- (SMC1)  Control Register for CS 6
AT91C_SMC1_CTRL2          EQU (0xFFFFEA2C) ;- (SMC1)  Control Register for CS 2
AT91C_SMC1_SETUP0         EQU (0xFFFFEA00) ;- (SMC1)  Setup Register for CS 0
AT91C_SMC1_CYCLE7         EQU (0xFFFFEA78) ;- (SMC1)  Cycle Register for CS 7
AT91C_SMC1_CYCLE1         EQU (0xFFFFEA18) ;- (SMC1)  Cycle Register for CS 1
AT91C_SMC1_PULSE2         EQU (0xFFFFEA24) ;- (SMC1)  Pulse Register for CS 2
AT91C_SMC1_PULSE1         EQU (0xFFFFEA14) ;- (SMC1)  Pulse Register for CS 1
AT91C_SMC1_CYCLE2         EQU (0xFFFFEA28) ;- (SMC1)  Cycle Register for CS 2
AT91C_SMC1_CTRL4          EQU (0xFFFFEA4C) ;- (SMC1)  Control Register for CS 4
// - ========== Register definition for MATRIX peripheral ========== 
AT91C_MATRIX_MCFG7        EQU (0xFFFFEC1C) ;- (MATRIX)  Master Configuration Register 7 
AT91C_MATRIX_MRCR         EQU (0xFFFFED00) ;- (MATRIX)  Master Remp Control Register 
AT91C_MATRIX_PRBS5        EQU (0xFFFFECAC) ;- (MATRIX)  PRBS5
AT91C_MATRIX_SCFG6        EQU (0xFFFFEC58) ;- (MATRIX)  Slave Configuration Register 6
AT91C_MATRIX_MCFG3        EQU (0xFFFFEC0C) ;- (MATRIX)  Master Configuration Register 3 
AT91C_MATRIX_SCFG5        EQU (0xFFFFEC54) ;- (MATRIX)  Slave Configuration Register 5
AT91C_MATRIX_MCFG1        EQU (0xFFFFEC04) ;- (MATRIX)  Master Configuration Register 1 
AT91C_MATRIX_SCFG3        EQU (0xFFFFEC4C) ;- (MATRIX)  Slave Configuration Register 3
AT91C_MATRIX_MCFG4        EQU (0xFFFFEC10) ;- (MATRIX)  Master Configuration Register 4 
AT91C_MATRIX_MCFG2        EQU (0xFFFFEC08) ;- (MATRIX)  Master Configuration Register 2 
AT91C_MATRIX_PRBS6        EQU (0xFFFFECB4) ;- (MATRIX)  PRBS6
AT91C_MATRIX_SCFG4        EQU (0xFFFFEC50) ;- (MATRIX)  Slave Configuration Register 4
AT91C_MATRIX_MCFG8        EQU (0xFFFFEC20) ;- (MATRIX)  Master Configuration Register 8 
AT91C_MATRIX_PRAS3        EQU (0xFFFFEC98) ;- (MATRIX)  PRAS3
AT91C_MATRIX_PRAS4        EQU (0xFFFFECA0) ;- (MATRIX)  PRAS4
AT91C_MATRIX_PRAS1        EQU (0xFFFFEC88) ;- (MATRIX)  PRAS1
AT91C_MATRIX_PRAS0        EQU (0xFFFFEC80) ;- (MATRIX)  PRAS0
AT91C_MATRIX_SCFG0        EQU (0xFFFFEC40) ;- (MATRIX)  Slave Configuration Register 0
AT91C_MATRIX_PRBS7        EQU (0xFFFFECBC) ;- (MATRIX)  PRBS7
AT91C_MATRIX_PRBS4        EQU (0xFFFFECA4) ;- (MATRIX)  PRBS4
AT91C_MATRIX_PRBS2        EQU (0xFFFFEC94) ;- (MATRIX)  PRBS2
AT91C_MATRIX_MCFG5        EQU (0xFFFFEC14) ;- (MATRIX)  Master Configuration Register 5 
AT91C_MATRIX_SCFG7        EQU (0xFFFFEC5C) ;- (MATRIX)  Slave Configuration Register 7
AT91C_MATRIX_PRBS1        EQU (0xFFFFEC8C) ;- (MATRIX)  PRBS1
AT91C_MATRIX_MCFG6        EQU (0xFFFFEC18) ;- (MATRIX)  Master Configuration Register 6 
AT91C_MATRIX_PRBS0        EQU (0xFFFFEC84) ;- (MATRIX)  PRBS0
AT91C_MATRIX_MCFG0        EQU (0xFFFFEC00) ;- (MATRIX)  Master Configuration Register 0 
AT91C_MATRIX_PRAS5        EQU (0xFFFFECA8) ;- (MATRIX)  PRAS5
AT91C_MATRIX_SCFG1        EQU (0xFFFFEC44) ;- (MATRIX)  Slave Configuration Register 1
AT91C_MATRIX_PRAS7        EQU (0xFFFFECB8) ;- (MATRIX)  PRAS7
AT91C_MATRIX_PRAS2        EQU (0xFFFFEC90) ;- (MATRIX)  PRAS2
AT91C_MATRIX_PRAS6        EQU (0xFFFFECB0) ;- (MATRIX)  PRAS6
AT91C_MATRIX_SCFG2        EQU (0xFFFFEC48) ;- (MATRIX)  Slave Configuration Register 2
AT91C_MATRIX_PRBS3        EQU (0xFFFFEC9C) ;- (MATRIX)  PRBS3
// - ========== Register definition for CCFG peripheral ========== 
AT91C_CCFG_MATRIXVERSION  EQU (0xFFFFEDFC) ;- (CCFG)  Version Register
AT91C_CCFG_TCMR           EQU (0xFFFFED14) ;- (CCFG)  TCM configuration
AT91C_CCFG_EBI0CSA        EQU (0xFFFFED20) ;- (CCFG)  EBI0 Chip Select Assignement Register
AT91C_CCFG_EBI1CSA        EQU (0xFFFFED24) ;- (CCFG)  EBI1 Chip Select Assignement Register
// - ========== Register definition for PDC_DBGU peripheral ========== 
AT91C_DBGU_PTCR           EQU (0xFFFFEF20) ;- (PDC_DBGU) PDC Transfer Control Register
AT91C_DBGU_RCR            EQU (0xFFFFEF04) ;- (PDC_DBGU) Receive Counter Register
AT91C_DBGU_TCR            EQU (0xFFFFEF0C) ;- (PDC_DBGU) Transmit Counter Register
AT91C_DBGU_RNCR           EQU (0xFFFFEF14) ;- (PDC_DBGU) Receive Next Counter Register
AT91C_DBGU_TNPR           EQU (0xFFFFEF18) ;- (PDC_DBGU) Transmit Next Pointer Register
AT91C_DBGU_RNPR           EQU (0xFFFFEF10) ;- (PDC_DBGU) Receive Next Pointer Register
AT91C_DBGU_PTSR           EQU (0xFFFFEF24) ;- (PDC_DBGU) PDC Transfer Status Register
AT91C_DBGU_RPR            EQU (0xFFFFEF00) ;- (PDC_DBGU) Receive Pointer Register
AT91C_DBGU_TPR            EQU (0xFFFFEF08) ;- (PDC_DBGU) Transmit Pointer Register
AT91C_DBGU_TNCR           EQU (0xFFFFEF1C) ;- (PDC_DBGU) Transmit Next Counter Register
// - ========== Register definition for DBGU peripheral ========== 
AT91C_DBGU_BRGR           EQU (0xFFFFEE20) ;- (DBGU) Baud Rate Generator Register
AT91C_DBGU_CR             EQU (0xFFFFEE00) ;- (DBGU) Control Register
AT91C_DBGU_THR            EQU (0xFFFFEE1C) ;- (DBGU) Transmitter Holding Register
AT91C_DBGU_IDR            EQU (0xFFFFEE0C) ;- (DBGU) Interrupt Disable Register
AT91C_DBGU_EXID           EQU (0xFFFFEE44) ;- (DBGU) Chip ID Extension Register
AT91C_DBGU_IMR            EQU (0xFFFFEE10) ;- (DBGU) Interrupt Mask Register
AT91C_DBGU_FNTR           EQU (0xFFFFEE48) ;- (DBGU) Force NTRST Register
AT91C_DBGU_IER            EQU (0xFFFFEE08) ;- (DBGU) Interrupt Enable Register
AT91C_DBGU_CSR            EQU (0xFFFFEE14) ;- (DBGU) Channel Status Register
AT91C_DBGU_MR             EQU (0xFFFFEE04) ;- (DBGU) Mode Register
AT91C_DBGU_RHR            EQU (0xFFFFEE18) ;- (DBGU) Receiver Holding Register
AT91C_DBGU_CIDR           EQU (0xFFFFEE40) ;- (DBGU) Chip ID Register
// - ========== Register definition for AIC peripheral ========== 
AT91C_AIC_IVR             EQU (0xFFFFF100) ;- (AIC) IRQ Vector Register
AT91C_AIC_SMR             EQU (0xFFFFF000) ;- (AIC) Source Mode Register
AT91C_AIC_FVR             EQU (0xFFFFF104) ;- (AIC) FIQ Vector Register
AT91C_AIC_DCR             EQU (0xFFFFF138) ;- (AIC) Debug Control Register (Protect)
AT91C_AIC_EOICR           EQU (0xFFFFF130) ;- (AIC) End of Interrupt Command Register
AT91C_AIC_SVR             EQU (0xFFFFF080) ;- (AIC) Source Vector Register
AT91C_AIC_FFSR            EQU (0xFFFFF148) ;- (AIC) Fast Forcing Status Register
AT91C_AIC_ICCR            EQU (0xFFFFF128) ;- (AIC) Interrupt Clear Command Register
AT91C_AIC_ISR             EQU (0xFFFFF108) ;- (AIC) Interrupt Status Register
AT91C_AIC_IMR             EQU (0xFFFFF110) ;- (AIC) Interrupt Mask Register
AT91C_AIC_IPR             EQU (0xFFFFF10C) ;- (AIC) Interrupt Pending Register
AT91C_AIC_FFER            EQU (0xFFFFF140) ;- (AIC) Fast Forcing Enable Register
AT91C_AIC_IECR            EQU (0xFFFFF120) ;- (AIC) Interrupt Enable Command Register
AT91C_AIC_ISCR            EQU (0xFFFFF12C) ;- (AIC) Interrupt Set Command Register
AT91C_AIC_FFDR            EQU (0xFFFFF144) ;- (AIC) Fast Forcing Disable Register
AT91C_AIC_CISR            EQU (0xFFFFF114) ;- (AIC) Core Interrupt Status Register
AT91C_AIC_IDCR            EQU (0xFFFFF124) ;- (AIC) Interrupt Disable Command Register
AT91C_AIC_SPU             EQU (0xFFFFF134) ;- (AIC) Spurious Vector Register
// - ========== Register definition for PIOA peripheral ========== 
AT91C_PIOA_OWDR           EQU (0xFFFFF2A4) ;- (PIOA) Output Write Disable Register
AT91C_PIOA_MDDR           EQU (0xFFFFF254) ;- (PIOA) Multi-driver Disable Register
AT91C_PIOA_IFSR           EQU (0xFFFFF228) ;- (PIOA) Input Filter Status Register
AT91C_PIOA_ISR            EQU (0xFFFFF24C) ;- (PIOA) Interrupt Status Register
AT91C_PIOA_CODR           EQU (0xFFFFF234) ;- (PIOA) Clear Output Data Register
AT91C_PIOA_PDR            EQU (0xFFFFF204) ;- (PIOA) PIO Disable Register
AT91C_PIOA_OWSR           EQU (0xFFFFF2A8) ;- (PIOA) Output Write Status Register
AT91C_PIOA_ASR            EQU (0xFFFFF270) ;- (PIOA) Select A Register
AT91C_PIOA_PPUSR          EQU (0xFFFFF268) ;- (PIOA) Pull-up Status Register
AT91C_PIOA_IMR            EQU (0xFFFFF248) ;- (PIOA) Interrupt Mask Register
AT91C_PIOA_OSR            EQU (0xFFFFF218) ;- (PIOA) Output Status Register
AT91C_PIOA_ABSR           EQU (0xFFFFF278) ;- (PIOA) AB Select Status Register
AT91C_PIOA_MDER           EQU (0xFFFFF250) ;- (PIOA) Multi-driver Enable Register
AT91C_PIOA_IFDR           EQU (0xFFFFF224) ;- (PIOA) Input Filter Disable Register
AT91C_PIOA_PDSR           EQU (0xFFFFF23C) ;- (PIOA) Pin Data Status Register
AT91C_PIOA_SODR           EQU (0xFFFFF230) ;- (PIOA) Set Output Data Register
AT91C_PIOA_BSR            EQU (0xFFFFF274) ;- (PIOA) Select B Register
AT91C_PIOA_OWER           EQU (0xFFFFF2A0) ;- (PIOA) Output Write Enable Register
AT91C_PIOA_IFER           EQU (0xFFFFF220) ;- (PIOA) Input Filter Enable Register
AT91C_PIOA_IDR            EQU (0xFFFFF244) ;- (PIOA) Interrupt Disable Register
AT91C_PIOA_ODR            EQU (0xFFFFF214) ;- (PIOA) Output Disable Registerr
AT91C_PIOA_IER            EQU (0xFFFFF240) ;- (PIOA) Interrupt Enable Register
AT91C_PIOA_PPUER          EQU (0xFFFFF264) ;- (PIOA) Pull-up Enable Register
AT91C_PIOA_MDSR           EQU (0xFFFFF258) ;- (PIOA) Multi-driver Status Register
AT91C_PIOA_OER            EQU (0xFFFFF210) ;- (PIOA) Output Enable Register
AT91C_PIOA_PER            EQU (0xFFFFF200) ;- (PIOA) PIO Enable Register
AT91C_PIOA_PPUDR          EQU (0xFFFFF260) ;- (PIOA) Pull-up Disable Register
AT91C_PIOA_ODSR           EQU (0xFFFFF238) ;- (PIOA) Output Data Status Register
AT91C_PIOA_PSR            EQU (0xFFFFF208) ;- (PIOA) PIO Status Register
// - ========== Register definition for PIOB peripheral ========== 
AT91C_PIOB_ODR            EQU (0xFFFFF414) ;- (PIOB) Output Disable Registerr
AT91C_PIOB_SODR           EQU (0xFFFFF430) ;- (PIOB) Set Output Data Register
AT91C_PIOB_ISR            EQU (0xFFFFF44C) ;- (PIOB) Interrupt Status Register
AT91C_PIOB_ABSR           EQU (0xFFFFF478) ;- (PIOB) AB Select Status Register
AT91C_PIOB_IER            EQU (0xFFFFF440) ;- (PIOB) Interrupt Enable Register
AT91C_PIOB_PPUDR          EQU (0xFFFFF460) ;- (PIOB) Pull-up Disable Register
AT91C_PIOB_IMR            EQU (0xFFFFF448) ;- (PIOB) Interrupt Mask Register
AT91C_PIOB_PER            EQU (0xFFFFF400) ;- (PIOB) PIO Enable Register
AT91C_PIOB_IFDR           EQU (0xFFFFF424) ;- (PIOB) Input Filter Disable Register
AT91C_PIOB_OWDR           EQU (0xFFFFF4A4) ;- (PIOB) Output Write Disable Register
AT91C_PIOB_MDSR           EQU (0xFFFFF458) ;- (PIOB) Multi-driver Status Register
AT91C_PIOB_IDR            EQU (0xFFFFF444) ;- (PIOB) Interrupt Disable Register
AT91C_PIOB_ODSR           EQU (0xFFFFF438) ;- (PIOB) Output Data Status Register
AT91C_PIOB_PPUSR          EQU (0xFFFFF468) ;- (PIOB) Pull-up Status Register
AT91C_PIOB_OWSR           EQU (0xFFFFF4A8) ;- (PIOB) Output Write Status Register
AT91C_PIOB_BSR            EQU (0xFFFFF474) ;- (PIOB) Select B Register
AT91C_PIOB_OWER           EQU (0xFFFFF4A0) ;- (PIOB) Output Write Enable Register
AT91C_PIOB_IFER           EQU (0xFFFFF420) ;- (PIOB) Input Filter Enable Register
AT91C_PIOB_PDSR           EQU (0xFFFFF43C) ;- (PIOB) Pin Data Status Register
AT91C_PIOB_PPUER          EQU (0xFFFFF464) ;- (PIOB) Pull-up Enable Register
AT91C_PIOB_OSR            EQU (0xFFFFF418) ;- (PIOB) Output Status Register
AT91C_PIOB_ASR            EQU (0xFFFFF470) ;- (PIOB) Select A Register
AT91C_PIOB_MDDR           EQU (0xFFFFF454) ;- (PIOB) Multi-driver Disable Register
AT91C_PIOB_CODR           EQU (0xFFFFF434) ;- (PIOB) Clear Output Data Register
AT91C_PIOB_MDER           EQU (0xFFFFF450) ;- (PIOB) Multi-driver Enable Register
AT91C_PIOB_PDR            EQU (0xFFFFF404) ;- (PIOB) PIO Disable Register
AT91C_PIOB_IFSR           EQU (0xFFFFF428) ;- (PIOB) Input Filter Status Register
AT91C_PIOB_OER            EQU (0xFFFFF410) ;- (PIOB) Output Enable Register
AT91C_PIOB_PSR            EQU (0xFFFFF408) ;- (PIOB) PIO Status Register
// - ========== Register definition for PIOC peripheral ========== 
AT91C_PIOC_OWDR           EQU (0xFFFFF6A4) ;- (PIOC) Output Write Disable Register
AT91C_PIOC_MDER           EQU (0xFFFFF650) ;- (PIOC) Multi-driver Enable Register
AT91C_PIOC_PPUSR          EQU (0xFFFFF668) ;- (PIOC) Pull-up Status Register
AT91C_PIOC_IMR            EQU (0xFFFFF648) ;- (PIOC) Interrupt Mask Register
AT91C_PIOC_ASR            EQU (0xFFFFF670) ;- (PIOC) Select A Register
AT91C_PIOC_PPUDR          EQU (0xFFFFF660) ;- (PIOC) Pull-up Disable Register
AT91C_PIOC_PSR            EQU (0xFFFFF608) ;- (PIOC) PIO Status Register
AT91C_PIOC_IER            EQU (0xFFFFF640) ;- (PIOC) Interrupt Enable Register
AT91C_PIOC_CODR           EQU (0xFFFFF634) ;- (PIOC) Clear Output Data Register
AT91C_PIOC_OWER           EQU (0xFFFFF6A0) ;- (PIOC) Output Write Enable Register
AT91C_PIOC_ABSR           EQU (0xFFFFF678) ;- (PIOC) AB Select Status Register
AT91C_PIOC_IFDR           EQU (0xFFFFF624) ;- (PIOC) Input Filter Disable Register
AT91C_PIOC_PDSR           EQU (0xFFFFF63C) ;- (PIOC) Pin Data Status Register
AT91C_PIOC_IDR            EQU (0xFFFFF644) ;- (PIOC) Interrupt Disable Register
AT91C_PIOC_OWSR           EQU (0xFFFFF6A8) ;- (PIOC) Output Write Status Register
AT91C_PIOC_PDR            EQU (0xFFFFF604) ;- (PIOC) PIO Disable Register
AT91C_PIOC_ODR            EQU (0xFFFFF614) ;- (PIOC) Output Disable Registerr
AT91C_PIOC_IFSR           EQU (0xFFFFF628) ;- (PIOC) Input Filter Status Register
AT91C_PIOC_PPUER          EQU (0xFFFFF664) ;- (PIOC) Pull-up Enable Register
AT91C_PIOC_SODR           EQU (0xFFFFF630) ;- (PIOC) Set Output Data Register
AT91C_PIOC_ISR            EQU (0xFFFFF64C) ;- (PIOC) Interrupt Status Register
AT91C_PIOC_ODSR           EQU (0xFFFFF638) ;- (PIOC) Output Data Status Register
AT91C_PIOC_OSR            EQU (0xFFFFF618) ;- (PIOC) Output Status Register
AT91C_PIOC_MDSR           EQU (0xFFFFF658) ;- (PIOC) Multi-driver Status Register
AT91C_PIOC_IFER           EQU (0xFFFFF620) ;- (PIOC) Input Filter Enable Register
AT91C_PIOC_BSR            EQU (0xFFFFF674) ;- (PIOC) Select B Register
AT91C_PIOC_MDDR           EQU (0xFFFFF654) ;- (PIOC) Multi-driver Disable Register
AT91C_PIOC_OER            EQU (0xFFFFF610) ;- (PIOC) Output Enable Register
AT91C_PIOC_PER            EQU (0xFFFFF600) ;- (PIOC) PIO Enable Register
// - ========== Register definition for PIOD peripheral ========== 
AT91C_PIOD_OWDR           EQU (0xFFFFF8A4) ;- (PIOD) Output Write Disable Register
AT91C_PIOD_SODR           EQU (0xFFFFF830) ;- (PIOD) Set Output Data Register
AT91C_PIOD_PPUER          EQU (0xFFFFF864) ;- (PIOD) Pull-up Enable Register
AT91C_PIOD_CODR           EQU (0xFFFFF834) ;- (PIOD) Clear Output Data Register
AT91C_PIOD_PSR            EQU (0xFFFFF808) ;- (PIOD) PIO Status Register
AT91C_PIOD_PDR            EQU (0xFFFFF804) ;- (PIOD) PIO Disable Register
AT91C_PIOD_ODR            EQU (0xFFFFF814) ;- (PIOD) Output Disable Registerr
AT91C_PIOD_PPUSR          EQU (0xFFFFF868) ;- (PIOD) Pull-up Status Register
AT91C_PIOD_ABSR           EQU (0xFFFFF878) ;- (PIOD) AB Select Status Register
AT91C_PIOD_IFSR           EQU (0xFFFFF828) ;- (PIOD) Input Filter Status Register
AT91C_PIOD_OER            EQU (0xFFFFF810) ;- (PIOD) Output Enable Register
AT91C_PIOD_IMR            EQU (0xFFFFF848) ;- (PIOD) Interrupt Mask Register
AT91C_PIOD_ASR            EQU (0xFFFFF870) ;- (PIOD) Select A Register
AT91C_PIOD_MDDR           EQU (0xFFFFF854) ;- (PIOD) Multi-driver Disable Register
AT91C_PIOD_OWSR           EQU (0xFFFFF8A8) ;- (PIOD) Output Write Status Register
AT91C_PIOD_PER            EQU (0xFFFFF800) ;- (PIOD) PIO Enable Register
AT91C_PIOD_IDR            EQU (0xFFFFF844) ;- (PIOD) Interrupt Disable Register
AT91C_PIOD_MDER           EQU (0xFFFFF850) ;- (PIOD) Multi-driver Enable Register
AT91C_PIOD_PDSR           EQU (0xFFFFF83C) ;- (PIOD) Pin Data Status Register
AT91C_PIOD_MDSR           EQU (0xFFFFF858) ;- (PIOD) Multi-driver Status Register
AT91C_PIOD_OWER           EQU (0xFFFFF8A0) ;- (PIOD) Output Write Enable Register
AT91C_PIOD_BSR            EQU (0xFFFFF874) ;- (PIOD) Select B Register
AT91C_PIOD_PPUDR          EQU (0xFFFFF860) ;- (PIOD) Pull-up Disable Register
AT91C_PIOD_IFDR           EQU (0xFFFFF824) ;- (PIOD) Input Filter Disable Register
AT91C_PIOD_IER            EQU (0xFFFFF840) ;- (PIOD) Interrupt Enable Register
AT91C_PIOD_OSR            EQU (0xFFFFF818) ;- (PIOD) Output Status Register
AT91C_PIOD_ODSR           EQU (0xFFFFF838) ;- (PIOD) Output Data Status Register
AT91C_PIOD_ISR            EQU (0xFFFFF84C) ;- (PIOD) Interrupt Status Register
AT91C_PIOD_IFER           EQU (0xFFFFF820) ;- (PIOD) Input Filter Enable Register
// - ========== Register definition for PIOE peripheral ========== 
AT91C_PIOE_ODSR           EQU (0xFFFFFA38) ;- (PIOE) Output Data Status Register
AT91C_PIOE_ABSR           EQU (0xFFFFFA78) ;- (PIOE) AB Select Status Register
AT91C_PIOE_PSR            EQU (0xFFFFFA08) ;- (PIOE) PIO Status Register
AT91C_PIOE_PPUDR          EQU (0xFFFFFA60) ;- (PIOE) Pull-up Disable Register
AT91C_PIOE_OER            EQU (0xFFFFFA10) ;- (PIOE) Output Enable Register
AT91C_PIOE_OWDR           EQU (0xFFFFFAA4) ;- (PIOE) Output Write Disable Register
AT91C_PIOE_PER            EQU (0xFFFFFA00) ;- (PIOE) PIO Enable Register
AT91C_PIOE_IFSR           EQU (0xFFFFFA28) ;- (PIOE) Input Filter Status Register
AT91C_PIOE_IFER           EQU (0xFFFFFA20) ;- (PIOE) Input Filter Enable Register
AT91C_PIOE_ODR            EQU (0xFFFFFA14) ;- (PIOE) Output Disable Registerr
AT91C_PIOE_PPUSR          EQU (0xFFFFFA68) ;- (PIOE) Pull-up Status Register
AT91C_PIOE_IFDR           EQU (0xFFFFFA24) ;- (PIOE) Input Filter Disable Register
AT91C_PIOE_PDSR           EQU (0xFFFFFA3C) ;- (PIOE) Pin Data Status Register
AT91C_PIOE_PPUER          EQU (0xFFFFFA64) ;- (PIOE) Pull-up Enable Register
AT91C_PIOE_IDR            EQU (0xFFFFFA44) ;- (PIOE) Interrupt Disable Register
AT91C_PIOE_MDDR           EQU (0xFFFFFA54) ;- (PIOE) Multi-driver Disable Register
AT91C_PIOE_ISR            EQU (0xFFFFFA4C) ;- (PIOE) Interrupt Status Register
AT91C_PIOE_OSR            EQU (0xFFFFFA18) ;- (PIOE) Output Status Register
AT91C_PIOE_CODR           EQU (0xFFFFFA34) ;- (PIOE) Clear Output Data Register
AT91C_PIOE_MDSR           EQU (0xFFFFFA58) ;- (PIOE) Multi-driver Status Register
AT91C_PIOE_PDR            EQU (0xFFFFFA04) ;- (PIOE) PIO Disable Register
AT91C_PIOE_IER            EQU (0xFFFFFA40) ;- (PIOE) Interrupt Enable Register
AT91C_PIOE_OWSR           EQU (0xFFFFFAA8) ;- (PIOE) Output Write Status Register
AT91C_PIOE_BSR            EQU (0xFFFFFA74) ;- (PIOE) Select B Register
AT91C_PIOE_ASR            EQU (0xFFFFFA70) ;- (PIOE) Select A Register
AT91C_PIOE_SODR           EQU (0xFFFFFA30) ;- (PIOE) Set Output Data Register
AT91C_PIOE_IMR            EQU (0xFFFFFA48) ;- (PIOE) Interrupt Mask Register
AT91C_PIOE_OWER           EQU (0xFFFFFAA0) ;- (PIOE) Output Write Enable Register
AT91C_PIOE_MDER           EQU (0xFFFFFA50) ;- (PIOE) Multi-driver Enable Register
// - ========== Register definition for CKGR peripheral ========== 
AT91C_CKGR_MOR            EQU (0xFFFFFC20) ;- (CKGR) Main Oscillator Register
AT91C_CKGR_PLLBR          EQU (0xFFFFFC2C) ;- (CKGR) PLL B Register
AT91C_CKGR_MCFR           EQU (0xFFFFFC24) ;- (CKGR) Main Clock  Frequency Register
AT91C_CKGR_PLLAR          EQU (0xFFFFFC28) ;- (CKGR) PLL A Register
// - ========== Register definition for PMC peripheral ========== 
AT91C_PMC_PCER            EQU (0xFFFFFC10) ;- (PMC) Peripheral Clock Enable Register
AT91C_PMC_PCKR            EQU (0xFFFFFC40) ;- (PMC) Programmable Clock Register
AT91C_PMC_MCKR            EQU (0xFFFFFC30) ;- (PMC) Master Clock Register
AT91C_PMC_PLLAR           EQU (0xFFFFFC28) ;- (PMC) PLL A Register
AT91C_PMC_PCDR            EQU (0xFFFFFC14) ;- (PMC) Peripheral Clock Disable Register
AT91C_PMC_SCSR            EQU (0xFFFFFC08) ;- (PMC) System Clock Status Register
AT91C_PMC_MCFR            EQU (0xFFFFFC24) ;- (PMC) Main Clock  Frequency Register
AT91C_PMC_IMR             EQU (0xFFFFFC6C) ;- (PMC) Interrupt Mask Register
AT91C_PMC_IER             EQU (0xFFFFFC60) ;- (PMC) Interrupt Enable Register
AT91C_PMC_MOR             EQU (0xFFFFFC20) ;- (PMC) Main Oscillator Register
AT91C_PMC_IDR             EQU (0xFFFFFC64) ;- (PMC) Interrupt Disable Register
AT91C_PMC_PLLBR           EQU (0xFFFFFC2C) ;- (PMC) PLL B Register
AT91C_PMC_SCDR            EQU (0xFFFFFC04) ;- (PMC) System Clock Disable Register
AT91C_PMC_PCSR            EQU (0xFFFFFC18) ;- (PMC) Peripheral Clock Status Register
AT91C_PMC_SCER            EQU (0xFFFFFC00) ;- (PMC) System Clock Enable Register
AT91C_PMC_SR              EQU (0xFFFFFC68) ;- (PMC) Status Register
// - ========== Register definition for RSTC peripheral ========== 
AT91C_RSTC_RCR            EQU (0xFFFFFD00) ;- (RSTC) Reset Control Register
AT91C_RSTC_RMR            EQU (0xFFFFFD08) ;- (RSTC) Reset Mode Register
AT91C_RSTC_RSR            EQU (0xFFFFFD04) ;- (RSTC) Reset Status Register
// - ========== Register definition for SHDWC peripheral ========== 
AT91C_SHDWC_SHSR          EQU (0xFFFFFD18) ;- (SHDWC) Shut Down Status Register
AT91C_SHDWC_SHMR          EQU (0xFFFFFD14) ;- (SHDWC) Shut Down Mode Register
AT91C_SHDWC_SHCR          EQU (0xFFFFFD10) ;- (SHDWC) Shut Down Control Register
// - ========== Register definition for RTTC0 peripheral ========== 
AT91C_RTTC0_RTSR          EQU (0xFFFFFD2C) ;- (RTTC0) Real-time Status Register
AT91C_RTTC0_RTMR          EQU (0xFFFFFD20) ;- (RTTC0) Real-time Mode Register
AT91C_RTTC0_RTVR          EQU (0xFFFFFD28) ;- (RTTC0) Real-time Value Register
AT91C_RTTC0_RTAR          EQU (0xFFFFFD24) ;- (RTTC0) Real-time Alarm Register
// - ========== Register definition for RTTC1 peripheral ========== 
AT91C_RTTC1_RTAR          EQU (0xFFFFFD54) ;- (RTTC1) Real-time Alarm Register
AT91C_RTTC1_RTSR          EQU (0xFFFFFD5C) ;- (RTTC1) Real-time Status Register
AT91C_RTTC1_RTVR          EQU (0xFFFFFD58) ;- (RTTC1) Real-time Value Register
AT91C_RTTC1_RTMR          EQU (0xFFFFFD50) ;- (RTTC1) Real-time Mode Register
// - ========== Register definition for PITC peripheral ========== 
AT91C_PITC_PIVR           EQU (0xFFFFFD38) ;- (PITC) Period Interval Value Register
AT91C_PITC_PISR           EQU (0xFFFFFD34) ;- (PITC) Period Interval Status Register
AT91C_PITC_PIIR           EQU (0xFFFFFD3C) ;- (PITC) Period Interval Image Register
AT91C_PITC_PIMR           EQU (0xFFFFFD30) ;- (PITC) Period Interval Mode Register
// - ========== Register definition for WDTC peripheral ========== 
AT91C_WDTC_WDCR           EQU (0xFFFFFD40) ;- (WDTC) Watchdog Control Register
AT91C_WDTC_WDSR           EQU (0xFFFFFD48) ;- (WDTC) Watchdog Status Register
AT91C_WDTC_WDMR           EQU (0xFFFFFD44) ;- (WDTC) Watchdog Mode Register
// - ========== Register definition for TC0 peripheral ========== 
AT91C_TC0_IER             EQU (0xFFF7C024) ;- (TC0) Interrupt Enable Register
AT91C_TC0_IMR             EQU (0xFFF7C02C) ;- (TC0) Interrupt Mask Register
AT91C_TC0_CCR             EQU (0xFFF7C000) ;- (TC0) Channel Control Register
AT91C_TC0_RB              EQU (0xFFF7C018) ;- (TC0) Register B
AT91C_TC0_CV              EQU (0xFFF7C010) ;- (TC0) Counter Value
AT91C_TC0_SR              EQU (0xFFF7C020) ;- (TC0) Status Register
AT91C_TC0_CMR             EQU (0xFFF7C004) ;- (TC0) Channel Mode Register (Capture Mode / Waveform Mode)
AT91C_TC0_RA              EQU (0xFFF7C014) ;- (TC0) Register A
AT91C_TC0_RC              EQU (0xFFF7C01C) ;- (TC0) Register C
AT91C_TC0_IDR             EQU (0xFFF7C028) ;- (TC0) Interrupt Disable Register
// - ========== Register definition for TC1 peripheral ========== 
AT91C_TC1_IER             EQU (0xFFF7C064) ;- (TC1) Interrupt Enable Register
AT91C_TC1_SR              EQU (0xFFF7C060) ;- (TC1) Status Register
AT91C_TC1_RC              EQU (0xFFF7C05C) ;- (TC1) Register C
AT91C_TC1_CV              EQU (0xFFF7C050) ;- (TC1) Counter Value
AT91C_TC1_RA              EQU (0xFFF7C054) ;- (TC1) Register A
AT91C_TC1_CMR             EQU (0xFFF7C044) ;- (TC1) Channel Mode Register (Capture Mode / Waveform Mode)
AT91C_TC1_IDR             EQU (0xFFF7C068) ;- (TC1) Interrupt Disable Register
AT91C_TC1_RB              EQU (0xFFF7C058) ;- (TC1) Register B
AT91C_TC1_IMR             EQU (0xFFF7C06C) ;- (TC1) Interrupt Mask Register
AT91C_TC1_CCR             EQU (0xFFF7C040) ;- (TC1) Channel Control Register
// - ========== Register definition for TC2 peripheral ========== 
AT91C_TC2_SR              EQU (0xFFF7C0A0) ;- (TC2) Status Register
AT91C_TC2_IMR             EQU (0xFFF7C0AC) ;- (TC2) Interrupt Mask Register
AT91C_TC2_IER             EQU (0xFFF7C0A4) ;- (TC2) Interrupt Enable Register
AT91C_TC2_CV              EQU (0xFFF7C090) ;- (TC2) Counter Value
AT91C_TC2_RB              EQU (0xFFF7C098) ;- (TC2) Register B
AT91C_TC2_CCR             EQU (0xFFF7C080) ;- (TC2) Channel Control Register
AT91C_TC2_CMR             EQU (0xFFF7C084) ;- (TC2) Channel Mode Register (Capture Mode / Waveform Mode)
AT91C_TC2_RA              EQU (0xFFF7C094) ;- (TC2) Register A
AT91C_TC2_IDR             EQU (0xFFF7C0A8) ;- (TC2) Interrupt Disable Register
AT91C_TC2_RC              EQU (0xFFF7C09C) ;- (TC2) Register C
// - ========== Register definition for TCB0 peripheral ========== 
AT91C_TCB0_BCR            EQU (0xFFF7C0C0) ;- (TCB0) TC Block Control Register
AT91C_TCB0_BMR            EQU (0xFFF7C0C4) ;- (TCB0) TC Block Mode Register
// - ========== Register definition for TCB1 peripheral ========== 
AT91C_TCB1_BMR            EQU (0xFFF7C104) ;- (TCB1) TC Block Mode Register
AT91C_TCB1_BCR            EQU (0xFFF7C100) ;- (TCB1) TC Block Control Register
// - ========== Register definition for TCB2 peripheral ========== 
AT91C_TCB2_BCR            EQU (0xFFF7C140) ;- (TCB2) TC Block Control Register
AT91C_TCB2_BMR            EQU (0xFFF7C144) ;- (TCB2) TC Block Mode Register
// - ========== Register definition for PDC_MCI0 peripheral ========== 
AT91C_MCI0_TCR            EQU (0xFFF8010C) ;- (PDC_MCI0) Transmit Counter Register
AT91C_MCI0_TNCR           EQU (0xFFF8011C) ;- (PDC_MCI0) Transmit Next Counter Register
AT91C_MCI0_RNPR           EQU (0xFFF80110) ;- (PDC_MCI0) Receive Next Pointer Register
AT91C_MCI0_TPR            EQU (0xFFF80108) ;- (PDC_MCI0) Transmit Pointer Register
AT91C_MCI0_TNPR           EQU (0xFFF80118) ;- (PDC_MCI0) Transmit Next Pointer Register
AT91C_MCI0_PTSR           EQU (0xFFF80124) ;- (PDC_MCI0) PDC Transfer Status Register
AT91C_MCI0_RCR            EQU (0xFFF80104) ;- (PDC_MCI0) Receive Counter Register
AT91C_MCI0_PTCR           EQU (0xFFF80120) ;- (PDC_MCI0) PDC Transfer Control Register
AT91C_MCI0_RPR            EQU (0xFFF80100) ;- (PDC_MCI0) Receive Pointer Register
AT91C_MCI0_RNCR           EQU (0xFFF80114) ;- (PDC_MCI0) Receive Next Counter Register
// - ========== Register definition for MCI0 peripheral ========== 
AT91C_MCI0_CMDR           EQU (0xFFF80014) ;- (MCI0) MCI Command Register
AT91C_MCI0_IMR            EQU (0xFFF8004C) ;- (MCI0) MCI Interrupt Mask Register
AT91C_MCI0_MR             EQU (0xFFF80004) ;- (MCI0) MCI Mode Register
AT91C_MCI0_CR             EQU (0xFFF80000) ;- (MCI0) MCI Control Register
AT91C_MCI0_IER            EQU (0xFFF80044) ;- (MCI0) MCI Interrupt Enable Register
AT91C_MCI0_RDR            EQU (0xFFF80030) ;- (MCI0) MCI Receive Data Register
AT91C_MCI0_SR             EQU (0xFFF80040) ;- (MCI0) MCI Status Register
AT91C_MCI0_DTOR           EQU (0xFFF80008) ;- (MCI0) MCI Data Timeout Register
AT91C_MCI0_SDCR           EQU (0xFFF8000C) ;- (MCI0) MCI SD Card Register
AT91C_MCI0_BLKR           EQU (0xFFF80018) ;- (MCI0) MCI Block Register
AT91C_MCI0_VR             EQU (0xFFF800FC) ;- (MCI0) MCI Version Register
AT91C_MCI0_TDR            EQU (0xFFF80034) ;- (MCI0) MCI Transmit Data Register
AT91C_MCI0_ARGR           EQU (0xFFF80010) ;- (MCI0) MCI Argument Register
AT91C_MCI0_RSPR           EQU (0xFFF80020) ;- (MCI0) MCI Response Register
AT91C_MCI0_IDR            EQU (0xFFF80048) ;- (MCI0) MCI Interrupt Disable Register
// - ========== Register definition for PDC_MCI1 peripheral ========== 
AT91C_MCI1_PTCR           EQU (0xFFF84120) ;- (PDC_MCI1) PDC Transfer Control Register
AT91C_MCI1_PTSR           EQU (0xFFF84124) ;- (PDC_MCI1) PDC Transfer Status Register
AT91C_MCI1_TPR            EQU (0xFFF84108) ;- (PDC_MCI1) Transmit Pointer Register
AT91C_MCI1_RPR            EQU (0xFFF84100) ;- (PDC_MCI1) Receive Pointer Register
AT91C_MCI1_TNCR           EQU (0xFFF8411C) ;- (PDC_MCI1) Transmit Next Counter Register
AT91C_MCI1_RCR            EQU (0xFFF84104) ;- (PDC_MCI1) Receive Counter Register
AT91C_MCI1_TNPR           EQU (0xFFF84118) ;- (PDC_MCI1) Transmit Next Pointer Register
AT91C_MCI1_TCR            EQU (0xFFF8410C) ;- (PDC_MCI1) Transmit Counter Register
AT91C_MCI1_RNPR           EQU (0xFFF84110) ;- (PDC_MCI1) Receive Next Pointer Register
AT91C_MCI1_RNCR           EQU (0xFFF84114) ;- (PDC_MCI1) Receive Next Counter Register
// - ========== Register definition for MCI1 peripheral ========== 
AT91C_MCI1_SR             EQU (0xFFF84040) ;- (MCI1) MCI Status Register
AT91C_MCI1_RDR            EQU (0xFFF84030) ;- (MCI1) MCI Receive Data Register
AT91C_MCI1_RSPR           EQU (0xFFF84020) ;- (MCI1) MCI Response Register
AT91C_MCI1_CMDR           EQU (0xFFF84014) ;- (MCI1) MCI Command Register
AT91C_MCI1_IMR            EQU (0xFFF8404C) ;- (MCI1) MCI Interrupt Mask Register
AT91C_MCI1_DTOR           EQU (0xFFF84008) ;- (MCI1) MCI Data Timeout Register
AT91C_MCI1_SDCR           EQU (0xFFF8400C) ;- (MCI1) MCI SD Card Register
AT91C_MCI1_IDR            EQU (0xFFF84048) ;- (MCI1) MCI Interrupt Disable Register
AT91C_MCI1_ARGR           EQU (0xFFF84010) ;- (MCI1) MCI Argument Register
AT91C_MCI1_TDR            EQU (0xFFF84034) ;- (MCI1) MCI Transmit Data Register
AT91C_MCI1_BLKR           EQU (0xFFF84018) ;- (MCI1) MCI Block Register
AT91C_MCI1_VR             EQU (0xFFF840FC) ;- (MCI1) MCI Version Register
AT91C_MCI1_CR             EQU (0xFFF84000) ;- (MCI1) MCI Control Register
AT91C_MCI1_MR             EQU (0xFFF84004) ;- (MCI1) MCI Mode Register
AT91C_MCI1_IER            EQU (0xFFF84044) ;- (MCI1) MCI Interrupt Enable Register
// - ========== Register definition for TWI peripheral ========== 
AT91C_TWI_IDR             EQU (0xFFF88028) ;- (TWI) Interrupt Disable Register
AT91C_TWI_RHR             EQU (0xFFF88030) ;- (TWI) Receive Holding Register
AT91C_TWI_IMR             EQU (0xFFF8802C) ;- (TWI) Interrupt Mask Register
AT91C_TWI_THR             EQU (0xFFF88034) ;- (TWI) Transmit Holding Register
AT91C_TWI_IER             EQU (0xFFF88024) ;- (TWI) Interrupt Enable Register
AT91C_TWI_IADR            EQU (0xFFF8800C) ;- (TWI) Internal Address Register
AT91C_TWI_SMR             EQU (0xFFF88008) ;- (TWI) Slave Mode Register
AT91C_TWI_MMR             EQU (0xFFF88004) ;- (TWI) Master Mode Register
AT91C_TWI_CR              EQU (0xFFF88000) ;- (TWI) Control Register
AT91C_TWI_SR              EQU (0xFFF88020) ;- (TWI) Status Register
AT91C_TWI_CWGR            EQU (0xFFF88010) ;- (TWI) Clock Waveform Generator Register
// - ========== Register definition for PDC_US0 peripheral ========== 
AT91C_US0_TNPR            EQU (0xFFF8C118) ;- (PDC_US0) Transmit Next Pointer Register
AT91C_US0_PTSR            EQU (0xFFF8C124) ;- (PDC_US0) PDC Transfer Status Register
AT91C_US0_PTCR            EQU (0xFFF8C120) ;- (PDC_US0) PDC Transfer Control Register
AT91C_US0_RNCR            EQU (0xFFF8C114) ;- (PDC_US0) Receive Next Counter Register
AT91C_US0_RCR             EQU (0xFFF8C104) ;- (PDC_US0) Receive Counter Register
AT91C_US0_TNCR            EQU (0xFFF8C11C) ;- (PDC_US0) Transmit Next Counter Register
AT91C_US0_TCR             EQU (0xFFF8C10C) ;- (PDC_US0) Transmit Counter Register
AT91C_US0_RNPR            EQU (0xFFF8C110) ;- (PDC_US0) Receive Next Pointer Register
AT91C_US0_RPR             EQU (0xFFF8C100) ;- (PDC_US0) Receive Pointer Register
AT91C_US0_TPR             EQU (0xFFF8C108) ;- (PDC_US0) Transmit Pointer Register
// - ========== Register definition for US0 peripheral ========== 
AT91C_US0_RTOR            EQU (0xFFF8C024) ;- (US0) Receiver Time-out Register
AT91C_US0_NER             EQU (0xFFF8C044) ;- (US0) Nb Errors Register
AT91C_US0_THR             EQU (0xFFF8C01C) ;- (US0) Transmitter Holding Register
AT91C_US0_MR              EQU (0xFFF8C004) ;- (US0) Mode Register
AT91C_US0_RHR             EQU (0xFFF8C018) ;- (US0) Receiver Holding Register
AT91C_US0_CSR             EQU (0xFFF8C014) ;- (US0) Channel Status Register
AT91C_US0_IMR             EQU (0xFFF8C010) ;- (US0) Interrupt Mask Register
AT91C_US0_IDR             EQU (0xFFF8C00C) ;- (US0) Interrupt Disable Register
AT91C_US0_FIDI            EQU (0xFFF8C040) ;- (US0) FI_DI_Ratio Register
AT91C_US0_CR              EQU (0xFFF8C000) ;- (US0) Control Register
AT91C_US0_IER             EQU (0xFFF8C008) ;- (US0) Interrupt Enable Register
AT91C_US0_TTGR            EQU (0xFFF8C028) ;- (US0) Transmitter Time-guard Register
AT91C_US0_BRGR            EQU (0xFFF8C020) ;- (US0) Baud Rate Generator Register
AT91C_US0_IF              EQU (0xFFF8C04C) ;- (US0) IRDA_FILTER Register
// - ========== Register definition for PDC_US1 peripheral ========== 
AT91C_US1_PTCR            EQU (0xFFF90120) ;- (PDC_US1) PDC Transfer Control Register
AT91C_US1_TNCR            EQU (0xFFF9011C) ;- (PDC_US1) Transmit Next Counter Register
AT91C_US1_RCR             EQU (0xFFF90104) ;- (PDC_US1) Receive Counter Register
AT91C_US1_RPR             EQU (0xFFF90100) ;- (PDC_US1) Receive Pointer Register
AT91C_US1_TPR             EQU (0xFFF90108) ;- (PDC_US1) Transmit Pointer Register
AT91C_US1_TCR             EQU (0xFFF9010C) ;- (PDC_US1) Transmit Counter Register
AT91C_US1_RNPR            EQU (0xFFF90110) ;- (PDC_US1) Receive Next Pointer Register
AT91C_US1_TNPR            EQU (0xFFF90118) ;- (PDC_US1) Transmit Next Pointer Register
AT91C_US1_RNCR            EQU (0xFFF90114) ;- (PDC_US1) Receive Next Counter Register
AT91C_US1_PTSR            EQU (0xFFF90124) ;- (PDC_US1) PDC Transfer Status Register
// - ========== Register definition for US1 peripheral ========== 
AT91C_US1_NER             EQU (0xFFF90044) ;- (US1) Nb Errors Register
AT91C_US1_RHR             EQU (0xFFF90018) ;- (US1) Receiver Holding Register
AT91C_US1_RTOR            EQU (0xFFF90024) ;- (US1) Receiver Time-out Register
AT91C_US1_IER             EQU (0xFFF90008) ;- (US1) Interrupt Enable Register
AT91C_US1_IF              EQU (0xFFF9004C) ;- (US1) IRDA_FILTER Register
AT91C_US1_CR              EQU (0xFFF90000) ;- (US1) Control Register
AT91C_US1_IMR             EQU (0xFFF90010) ;- (US1) Interrupt Mask Register
AT91C_US1_TTGR            EQU (0xFFF90028) ;- (US1) Transmitter Time-guard Register
AT91C_US1_MR              EQU (0xFFF90004) ;- (US1) Mode Register
AT91C_US1_IDR             EQU (0xFFF9000C) ;- (US1) Interrupt Disable Register
AT91C_US1_FIDI            EQU (0xFFF90040) ;- (US1) FI_DI_Ratio Register
AT91C_US1_CSR             EQU (0xFFF90014) ;- (US1) Channel Status Register
AT91C_US1_THR             EQU (0xFFF9001C) ;- (US1) Transmitter Holding Register
AT91C_US1_BRGR            EQU (0xFFF90020) ;- (US1) Baud Rate Generator Register
// - ========== Register definition for PDC_US2 peripheral ========== 
AT91C_US2_RNCR            EQU (0xFFF94114) ;- (PDC_US2) Receive Next Counter Register
AT91C_US2_PTCR            EQU (0xFFF94120) ;- (PDC_US2) PDC Transfer Control Register
AT91C_US2_TNPR            EQU (0xFFF94118) ;- (PDC_US2) Transmit Next Pointer Register
AT91C_US2_TNCR            EQU (0xFFF9411C) ;- (PDC_US2) Transmit Next Counter Register
AT91C_US2_TPR             EQU (0xFFF94108) ;- (PDC_US2) Transmit Pointer Register
AT91C_US2_RCR             EQU (0xFFF94104) ;- (PDC_US2) Receive Counter Register
AT91C_US2_PTSR            EQU (0xFFF94124) ;- (PDC_US2) PDC Transfer Status Register
AT91C_US2_TCR             EQU (0xFFF9410C) ;- (PDC_US2) Transmit Counter Register
AT91C_US2_RPR             EQU (0xFFF94100) ;- (PDC_US2) Receive Pointer Register
AT91C_US2_RNPR            EQU (0xFFF94110) ;- (PDC_US2) Receive Next Pointer Register
// - ========== Register definition for US2 peripheral ========== 
AT91C_US2_TTGR            EQU (0xFFF94028) ;- (US2) Transmitter Time-guard Register
AT91C_US2_RHR             EQU (0xFFF94018) ;- (US2) Receiver Holding Register
AT91C_US2_IMR             EQU (0xFFF94010) ;- (US2) Interrupt Mask Register
AT91C_US2_IER             EQU (0xFFF94008) ;- (US2) Interrupt Enable Register
AT91C_US2_NER             EQU (0xFFF94044) ;- (US2) Nb Errors Register
AT91C_US2_CR              EQU (0xFFF94000) ;- (US2) Control Register
AT91C_US2_FIDI            EQU (0xFFF94040) ;- (US2) FI_DI_Ratio Register
AT91C_US2_MR              EQU (0xFFF94004) ;- (US2) Mode Register
AT91C_US2_IDR             EQU (0xFFF9400C) ;- (US2) Interrupt Disable Register
AT91C_US2_THR             EQU (0xFFF9401C) ;- (US2) Transmitter Holding Register
AT91C_US2_IF              EQU (0xFFF9404C) ;- (US2) IRDA_FILTER Register
AT91C_US2_BRGR            EQU (0xFFF94020) ;- (US2) Baud Rate Generator Register
AT91C_US2_CSR             EQU (0xFFF94014) ;- (US2) Channel Status Register
AT91C_US2_RTOR            EQU (0xFFF94024) ;- (US2) Receiver Time-out Register
// - ========== Register definition for PDC_SSC0 peripheral ========== 
AT91C_SSC0_PTSR           EQU (0xFFF98124) ;- (PDC_SSC0) PDC Transfer Status Register
AT91C_SSC0_TCR            EQU (0xFFF9810C) ;- (PDC_SSC0) Transmit Counter Register
AT91C_SSC0_RNPR           EQU (0xFFF98110) ;- (PDC_SSC0) Receive Next Pointer Register
AT91C_SSC0_RNCR           EQU (0xFFF98114) ;- (PDC_SSC0) Receive Next Counter Register
AT91C_SSC0_TNPR           EQU (0xFFF98118) ;- (PDC_SSC0) Transmit Next Pointer Register
AT91C_SSC0_RPR            EQU (0xFFF98100) ;- (PDC_SSC0) Receive Pointer Register
AT91C_SSC0_TPR            EQU (0xFFF98108) ;- (PDC_SSC0) Transmit Pointer Register
AT91C_SSC0_RCR            EQU (0xFFF98104) ;- (PDC_SSC0) Receive Counter Register
AT91C_SSC0_TNCR           EQU (0xFFF9811C) ;- (PDC_SSC0) Transmit Next Counter Register
AT91C_SSC0_PTCR           EQU (0xFFF98120) ;- (PDC_SSC0) PDC Transfer Control Register
// - ========== Register definition for SSC0 peripheral ========== 
AT91C_SSC0_RFMR           EQU (0xFFF98014) ;- (SSC0) Receive Frame Mode Register
AT91C_SSC0_RHR            EQU (0xFFF98020) ;- (SSC0) Receive Holding Register
AT91C_SSC0_THR            EQU (0xFFF98024) ;- (SSC0) Transmit Holding Register
AT91C_SSC0_CMR            EQU (0xFFF98004) ;- (SSC0) Clock Mode Register
AT91C_SSC0_IMR            EQU (0xFFF9804C) ;- (SSC0) Interrupt Mask Register
AT91C_SSC0_IDR            EQU (0xFFF98048) ;- (SSC0) Interrupt Disable Register
AT91C_SSC0_IER            EQU (0xFFF98044) ;- (SSC0) Interrupt Enable Register
AT91C_SSC0_TSHR           EQU (0xFFF98034) ;- (SSC0) Transmit Sync Holding Register
AT91C_SSC0_SR             EQU (0xFFF98040) ;- (SSC0) Status Register
AT91C_SSC0_CR             EQU (0xFFF98000) ;- (SSC0) Control Register
AT91C_SSC0_RCMR           EQU (0xFFF98010) ;- (SSC0) Receive Clock ModeRegister
AT91C_SSC0_TFMR           EQU (0xFFF9801C) ;- (SSC0) Transmit Frame Mode Register
AT91C_SSC0_RSHR           EQU (0xFFF98030) ;- (SSC0) Receive Sync Holding Register
AT91C_SSC0_TCMR           EQU (0xFFF98018) ;- (SSC0) Transmit Clock Mode Register
// - ========== Register definition for PDC_SSC1 peripheral ========== 
AT91C_SSC1_TNPR           EQU (0xFFF9C118) ;- (PDC_SSC1) Transmit Next Pointer Register
AT91C_SSC1_PTSR           EQU (0xFFF9C124) ;- (PDC_SSC1) PDC Transfer Status Register
AT91C_SSC1_TNCR           EQU (0xFFF9C11C) ;- (PDC_SSC1) Transmit Next Counter Register
AT91C_SSC1_RNCR           EQU (0xFFF9C114) ;- (PDC_SSC1) Receive Next Counter Register
AT91C_SSC1_TPR            EQU (0xFFF9C108) ;- (PDC_SSC1) Transmit Pointer Register
AT91C_SSC1_RCR            EQU (0xFFF9C104) ;- (PDC_SSC1) Receive Counter Register
AT91C_SSC1_PTCR           EQU (0xFFF9C120) ;- (PDC_SSC1) PDC Transfer Control Register
AT91C_SSC1_RNPR           EQU (0xFFF9C110) ;- (PDC_SSC1) Receive Next Pointer Register
AT91C_SSC1_TCR            EQU (0xFFF9C10C) ;- (PDC_SSC1) Transmit Counter Register
AT91C_SSC1_RPR            EQU (0xFFF9C100) ;- (PDC_SSC1) Receive Pointer Register
// - ========== Register definition for SSC1 peripheral ========== 
AT91C_SSC1_CMR            EQU (0xFFF9C004) ;- (SSC1) Clock Mode Register
AT91C_SSC1_SR             EQU (0xFFF9C040) ;- (SSC1) Status Register
AT91C_SSC1_TSHR           EQU (0xFFF9C034) ;- (SSC1) Transmit Sync Holding Register
AT91C_SSC1_TCMR           EQU (0xFFF9C018) ;- (SSC1) Transmit Clock Mode Register
AT91C_SSC1_IMR            EQU (0xFFF9C04C) ;- (SSC1) Interrupt Mask Register
AT91C_SSC1_IDR            EQU (0xFFF9C048) ;- (SSC1) Interrupt Disable Register
AT91C_SSC1_RCMR           EQU (0xFFF9C010) ;- (SSC1) Receive Clock ModeRegister
AT91C_SSC1_IER            EQU (0xFFF9C044) ;- (SSC1) Interrupt Enable Register
AT91C_SSC1_RSHR           EQU (0xFFF9C030) ;- (SSC1) Receive Sync Holding Register
AT91C_SSC1_CR             EQU (0xFFF9C000) ;- (SSC1) Control Register
AT91C_SSC1_RHR            EQU (0xFFF9C020) ;- (SSC1) Receive Holding Register
AT91C_SSC1_THR            EQU (0xFFF9C024) ;- (SSC1) Transmit Holding Register
AT91C_SSC1_RFMR           EQU (0xFFF9C014) ;- (SSC1) Receive Frame Mode Register
AT91C_SSC1_TFMR           EQU (0xFFF9C01C) ;- (SSC1) Transmit Frame Mode Register
// - ========== Register definition for PDC_AC97C peripheral ========== 
AT91C_AC97C_RNPR          EQU (0xFFFA0110) ;- (PDC_AC97C) Receive Next Pointer Register
AT91C_AC97C_TCR           EQU (0xFFFA010C) ;- (PDC_AC97C) Transmit Counter Register
AT91C_AC97C_TNCR          EQU (0xFFFA011C) ;- (PDC_AC97C) Transmit Next Counter Register
AT91C_AC97C_RCR           EQU (0xFFFA0104) ;- (PDC_AC97C) Receive Counter Register
AT91C_AC97C_RNCR          EQU (0xFFFA0114) ;- (PDC_AC97C) Receive Next Counter Register
AT91C_AC97C_PTCR          EQU (0xFFFA0120) ;- (PDC_AC97C) PDC Transfer Control Register
AT91C_AC97C_TPR           EQU (0xFFFA0108) ;- (PDC_AC97C) Transmit Pointer Register
AT91C_AC97C_RPR           EQU (0xFFFA0100) ;- (PDC_AC97C) Receive Pointer Register
AT91C_AC97C_PTSR          EQU (0xFFFA0124) ;- (PDC_AC97C) PDC Transfer Status Register
AT91C_AC97C_TNPR          EQU (0xFFFA0118) ;- (PDC_AC97C) Transmit Next Pointer Register
// - ========== Register definition for AC97C peripheral ========== 
AT91C_AC97C_CORHR         EQU (0xFFFA0040) ;- (AC97C) COdec Transmit Holding Register
AT91C_AC97C_MR            EQU (0xFFFA0008) ;- (AC97C) Mode Register
AT91C_AC97C_CATHR         EQU (0xFFFA0024) ;- (AC97C) Channel A Transmit Holding Register
AT91C_AC97C_IER           EQU (0xFFFA0054) ;- (AC97C) Interrupt Enable Register
AT91C_AC97C_CASR          EQU (0xFFFA0028) ;- (AC97C) Channel A Status Register
AT91C_AC97C_CBTHR         EQU (0xFFFA0034) ;- (AC97C) Channel B Transmit Holding Register (optional)
AT91C_AC97C_ICA           EQU (0xFFFA0010) ;- (AC97C) Input Channel AssignementRegister
AT91C_AC97C_IMR           EQU (0xFFFA005C) ;- (AC97C) Interrupt Mask Register
AT91C_AC97C_IDR           EQU (0xFFFA0058) ;- (AC97C) Interrupt Disable Register
AT91C_AC97C_CARHR         EQU (0xFFFA0020) ;- (AC97C) Channel A Receive Holding Register
AT91C_AC97C_VERSION       EQU (0xFFFA00FC) ;- (AC97C) Version Register
AT91C_AC97C_CBRHR         EQU (0xFFFA0030) ;- (AC97C) Channel B Receive Holding Register (optional)
AT91C_AC97C_COTHR         EQU (0xFFFA0044) ;- (AC97C) COdec Transmit Holding Register
AT91C_AC97C_OCA           EQU (0xFFFA0014) ;- (AC97C) Output Channel Assignement Register
AT91C_AC97C_CBMR          EQU (0xFFFA003C) ;- (AC97C) Channel B Mode Register
AT91C_AC97C_COMR          EQU (0xFFFA004C) ;- (AC97C) CODEC Mask Status Register
AT91C_AC97C_CBSR          EQU (0xFFFA0038) ;- (AC97C) Channel B Status Register
AT91C_AC97C_COSR          EQU (0xFFFA0048) ;- (AC97C) CODEC Status Register
AT91C_AC97C_CAMR          EQU (0xFFFA002C) ;- (AC97C) Channel A Mode Register
AT91C_AC97C_SR            EQU (0xFFFA0050) ;- (AC97C) Status Register
// - ========== Register definition for PDC_SPI0 peripheral ========== 
AT91C_SPI0_TPR            EQU (0xFFFA4108) ;- (PDC_SPI0) Transmit Pointer Register
AT91C_SPI0_PTCR           EQU (0xFFFA4120) ;- (PDC_SPI0) PDC Transfer Control Register
AT91C_SPI0_RNPR           EQU (0xFFFA4110) ;- (PDC_SPI0) Receive Next Pointer Register
AT91C_SPI0_TNCR           EQU (0xFFFA411C) ;- (PDC_SPI0) Transmit Next Counter Register
AT91C_SPI0_TCR            EQU (0xFFFA410C) ;- (PDC_SPI0) Transmit Counter Register
AT91C_SPI0_RCR            EQU (0xFFFA4104) ;- (PDC_SPI0) Receive Counter Register
AT91C_SPI0_RNCR           EQU (0xFFFA4114) ;- (PDC_SPI0) Receive Next Counter Register
AT91C_SPI0_TNPR           EQU (0xFFFA4118) ;- (PDC_SPI0) Transmit Next Pointer Register
AT91C_SPI0_RPR            EQU (0xFFFA4100) ;- (PDC_SPI0) Receive Pointer Register
AT91C_SPI0_PTSR           EQU (0xFFFA4124) ;- (PDC_SPI0) PDC Transfer Status Register
// - ========== Register definition for SPI0 peripheral ========== 
AT91C_SPI0_MR             EQU (0xFFFA4004) ;- (SPI0) Mode Register
AT91C_SPI0_RDR            EQU (0xFFFA4008) ;- (SPI0) Receive Data Register
AT91C_SPI0_CR             EQU (0xFFFA4000) ;- (SPI0) Control Register
AT91C_SPI0_IER            EQU (0xFFFA4014) ;- (SPI0) Interrupt Enable Register
AT91C_SPI0_TDR            EQU (0xFFFA400C) ;- (SPI0) Transmit Data Register
AT91C_SPI0_IDR            EQU (0xFFFA4018) ;- (SPI0) Interrupt Disable Register
AT91C_SPI0_CSR            EQU (0xFFFA4030) ;- (SPI0) Chip Select Register
AT91C_SPI0_SR             EQU (0xFFFA4010) ;- (SPI0) Status Register
AT91C_SPI0_IMR            EQU (0xFFFA401C) ;- (SPI0) Interrupt Mask Register
// - ========== Register definition for PDC_SPI1 peripheral ========== 
AT91C_SPI1_RNCR           EQU (0xFFFA8114) ;- (PDC_SPI1) Receive Next Counter Register
AT91C_SPI1_TCR            EQU (0xFFFA810C) ;- (PDC_SPI1) Transmit Counter Register
AT91C_SPI1_RCR            EQU (0xFFFA8104) ;- (PDC_SPI1) Receive Counter Register
AT91C_SPI1_TNPR           EQU (0xFFFA8118) ;- (PDC_SPI1) Transmit Next Pointer Register
AT91C_SPI1_RNPR           EQU (0xFFFA8110) ;- (PDC_SPI1) Receive Next Pointer Register
AT91C_SPI1_RPR            EQU (0xFFFA8100) ;- (PDC_SPI1) Receive Pointer Register
AT91C_SPI1_TNCR           EQU (0xFFFA811C) ;- (PDC_SPI1) Transmit Next Counter Register
AT91C_SPI1_TPR            EQU (0xFFFA8108) ;- (PDC_SPI1) Transmit Pointer Register
AT91C_SPI1_PTSR           EQU (0xFFFA8124) ;- (PDC_SPI1) PDC Transfer Status Register
AT91C_SPI1_PTCR           EQU (0xFFFA8120) ;- (PDC_SPI1) PDC Transfer Control Register
// - ========== Register definition for SPI1 peripheral ========== 
AT91C_SPI1_CSR            EQU (0xFFFA8030) ;- (SPI1) Chip Select Register
AT91C_SPI1_IER            EQU (0xFFFA8014) ;- (SPI1) Interrupt Enable Register
AT91C_SPI1_RDR            EQU (0xFFFA8008) ;- (SPI1) Receive Data Register
AT91C_SPI1_IDR            EQU (0xFFFA8018) ;- (SPI1) Interrupt Disable Register
AT91C_SPI1_MR             EQU (0xFFFA8004) ;- (SPI1) Mode Register
AT91C_SPI1_CR             EQU (0xFFFA8000) ;- (SPI1) Control Register
AT91C_SPI1_SR             EQU (0xFFFA8010) ;- (SPI1) Status Register
AT91C_SPI1_TDR            EQU (0xFFFA800C) ;- (SPI1) Transmit Data Register
AT91C_SPI1_IMR            EQU (0xFFFA801C) ;- (SPI1) Interrupt Mask Register
// - ========== Register definition for CAN_MB0 peripheral ========== 
AT91C_CAN_MB0_MID         EQU (0xFFFAC208) ;- (CAN_MB0) MailBox ID Register
AT91C_CAN_MB0_MFID        EQU (0xFFFAC20C) ;- (CAN_MB0) MailBox Family ID Register
AT91C_CAN_MB0_MAM         EQU (0xFFFAC204) ;- (CAN_MB0) MailBox Acceptance Mask Register
AT91C_CAN_MB0_MCR         EQU (0xFFFAC21C) ;- (CAN_MB0) MailBox Control Register
AT91C_CAN_MB0_MMR         EQU (0xFFFAC200) ;- (CAN_MB0) MailBox Mode Register
AT91C_CAN_MB0_MDL         EQU (0xFFFAC214) ;- (CAN_MB0) MailBox Data Low Register
AT91C_CAN_MB0_MDH         EQU (0xFFFAC218) ;- (CAN_MB0) MailBox Data High Register
AT91C_CAN_MB0_MSR         EQU (0xFFFAC210) ;- (CAN_MB0) MailBox Status Register
// - ========== Register definition for CAN_MB1 peripheral ========== 
AT91C_CAN_MB1_MDL         EQU (0xFFFAC234) ;- (CAN_MB1) MailBox Data Low Register
AT91C_CAN_MB1_MAM         EQU (0xFFFAC224) ;- (CAN_MB1) MailBox Acceptance Mask Register
AT91C_CAN_MB1_MID         EQU (0xFFFAC228) ;- (CAN_MB1) MailBox ID Register
AT91C_CAN_MB1_MMR         EQU (0xFFFAC220) ;- (CAN_MB1) MailBox Mode Register
AT91C_CAN_MB1_MCR         EQU (0xFFFAC23C) ;- (CAN_MB1) MailBox Control Register
AT91C_CAN_MB1_MFID        EQU (0xFFFAC22C) ;- (CAN_MB1) MailBox Family ID Register
AT91C_CAN_MB1_MSR         EQU (0xFFFAC230) ;- (CAN_MB1) MailBox Status Register
AT91C_CAN_MB1_MDH         EQU (0xFFFAC238) ;- (CAN_MB1) MailBox Data High Register
// - ========== Register definition for CAN_MB2 peripheral ========== 
AT91C_CAN_MB2_MID         EQU (0xFFFAC248) ;- (CAN_MB2) MailBox ID Register
AT91C_CAN_MB2_MSR         EQU (0xFFFAC250) ;- (CAN_MB2) MailBox Status Register
AT91C_CAN_MB2_MDL         EQU (0xFFFAC254) ;- (CAN_MB2) MailBox Data Low Register
AT91C_CAN_MB2_MCR         EQU (0xFFFAC25C) ;- (CAN_MB2) MailBox Control Register
AT91C_CAN_MB2_MDH         EQU (0xFFFAC258) ;- (CAN_MB2) MailBox Data High Register
AT91C_CAN_MB2_MAM         EQU (0xFFFAC244) ;- (CAN_MB2) MailBox Acceptance Mask Register
AT91C_CAN_MB2_MMR         EQU (0xFFFAC240) ;- (CAN_MB2) MailBox Mode Register
AT91C_CAN_MB2_MFID        EQU (0xFFFAC24C) ;- (CAN_MB2) MailBox Family ID Register
// - ========== Register definition for CAN_MB3 peripheral ========== 
AT91C_CAN_MB3_MDL         EQU (0xFFFAC274) ;- (CAN_MB3) MailBox Data Low Register
AT91C_CAN_MB3_MFID        EQU (0xFFFAC26C) ;- (CAN_MB3) MailBox Family ID Register
AT91C_CAN_MB3_MID         EQU (0xFFFAC268) ;- (CAN_MB3) MailBox ID Register
AT91C_CAN_MB3_MDH         EQU (0xFFFAC278) ;- (CAN_MB3) MailBox Data High Register
AT91C_CAN_MB3_MAM         EQU (0xFFFAC264) ;- (CAN_MB3) MailBox Acceptance Mask Register
AT91C_CAN_MB3_MMR         EQU (0xFFFAC260) ;- (CAN_MB3) MailBox Mode Register
AT91C_CAN_MB3_MCR         EQU (0xFFFAC27C) ;- (CAN_MB3) MailBox Control Register
AT91C_CAN_MB3_MSR         EQU (0xFFFAC270) ;- (CAN_MB3) MailBox Status Register
// - ========== Register definition for CAN_MB4 peripheral ========== 
AT91C_CAN_MB4_MCR         EQU (0xFFFAC29C) ;- (CAN_MB4) MailBox Control Register
AT91C_CAN_MB4_MDH         EQU (0xFFFAC298) ;- (CAN_MB4) MailBox Data High Register
AT91C_CAN_MB4_MID         EQU (0xFFFAC288) ;- (CAN_MB4) MailBox ID Register
AT91C_CAN_MB4_MMR         EQU (0xFFFAC280) ;- (CAN_MB4) MailBox Mode Register
AT91C_CAN_MB4_MSR         EQU (0xFFFAC290) ;- (CAN_MB4) MailBox Status Register
AT91C_CAN_MB4_MFID        EQU (0xFFFAC28C) ;- (CAN_MB4) MailBox Family ID Register
AT91C_CAN_MB4_MAM         EQU (0xFFFAC284) ;- (CAN_MB4) MailBox Acceptance Mask Register
AT91C_CAN_MB4_MDL         EQU (0xFFFAC294) ;- (CAN_MB4) MailBox Data Low Register
// - ========== Register definition for CAN_MB5 peripheral ========== 
AT91C_CAN_MB5_MDH         EQU (0xFFFAC2B8) ;- (CAN_MB5) MailBox Data High Register
AT91C_CAN_MB5_MID         EQU (0xFFFAC2A8) ;- (CAN_MB5) MailBox ID Register
AT91C_CAN_MB5_MCR         EQU (0xFFFAC2BC) ;- (CAN_MB5) MailBox Control Register
AT91C_CAN_MB5_MSR         EQU (0xFFFAC2B0) ;- (CAN_MB5) MailBox Status Register
AT91C_CAN_MB5_MDL         EQU (0xFFFAC2B4) ;- (CAN_MB5) MailBox Data Low Register
AT91C_CAN_MB5_MMR         EQU (0xFFFAC2A0) ;- (CAN_MB5) MailBox Mode Register
AT91C_CAN_MB5_MAM         EQU (0xFFFAC2A4) ;- (CAN_MB5) MailBox Acceptance Mask Register
AT91C_CAN_MB5_MFID        EQU (0xFFFAC2AC) ;- (CAN_MB5) MailBox Family ID Register
// - ========== Register definition for CAN_MB6 peripheral ========== 
AT91C_CAN_MB6_MSR         EQU (0xFFFAC2D0) ;- (CAN_MB6) MailBox Status Register
AT91C_CAN_MB6_MMR         EQU (0xFFFAC2C0) ;- (CAN_MB6) MailBox Mode Register
AT91C_CAN_MB6_MFID        EQU (0xFFFAC2CC) ;- (CAN_MB6) MailBox Family ID Register
AT91C_CAN_MB6_MDL         EQU (0xFFFAC2D4) ;- (CAN_MB6) MailBox Data Low Register
AT91C_CAN_MB6_MID         EQU (0xFFFAC2C8) ;- (CAN_MB6) MailBox ID Register
AT91C_CAN_MB6_MCR         EQU (0xFFFAC2DC) ;- (CAN_MB6) MailBox Control Register
AT91C_CAN_MB6_MAM         EQU (0xFFFAC2C4) ;- (CAN_MB6) MailBox Acceptance Mask Register
AT91C_CAN_MB6_MDH         EQU (0xFFFAC2D8) ;- (CAN_MB6) MailBox Data High Register
// - ========== Register definition for CAN_MB7 peripheral ========== 
AT91C_CAN_MB7_MAM         EQU (0xFFFAC2E4) ;- (CAN_MB7) MailBox Acceptance Mask Register
AT91C_CAN_MB7_MDH         EQU (0xFFFAC2F8) ;- (CAN_MB7) MailBox Data High Register
AT91C_CAN_MB7_MID         EQU (0xFFFAC2E8) ;- (CAN_MB7) MailBox ID Register
AT91C_CAN_MB7_MSR         EQU (0xFFFAC2F0) ;- (CAN_MB7) MailBox Status Register
AT91C_CAN_MB7_MMR         EQU (0xFFFAC2E0) ;- (CAN_MB7) MailBox Mode Register
AT91C_CAN_MB7_MCR         EQU (0xFFFAC2FC) ;- (CAN_MB7) MailBox Control Register
AT91C_CAN_MB7_MFID        EQU (0xFFFAC2EC) ;- (CAN_MB7) MailBox Family ID Register
AT91C_CAN_MB7_MDL         EQU (0xFFFAC2F4) ;- (CAN_MB7) MailBox Data Low Register
// - ========== Register definition for CAN_MB8 peripheral ========== 
AT91C_CAN_MB8_MDH         EQU (0xFFFAC318) ;- (CAN_MB8) MailBox Data High Register
AT91C_CAN_MB8_MMR         EQU (0xFFFAC300) ;- (CAN_MB8) MailBox Mode Register
AT91C_CAN_MB8_MCR         EQU (0xFFFAC31C) ;- (CAN_MB8) MailBox Control Register
AT91C_CAN_MB8_MSR         EQU (0xFFFAC310) ;- (CAN_MB8) MailBox Status Register
AT91C_CAN_MB8_MAM         EQU (0xFFFAC304) ;- (CAN_MB8) MailBox Acceptance Mask Register
AT91C_CAN_MB8_MFID        EQU (0xFFFAC30C) ;- (CAN_MB8) MailBox Family ID Register
AT91C_CAN_MB8_MID         EQU (0xFFFAC308) ;- (CAN_MB8) MailBox ID Register
AT91C_CAN_MB8_MDL         EQU (0xFFFAC314) ;- (CAN_MB8) MailBox Data Low Register
// - ========== Register definition for CAN_MB9 peripheral ========== 
AT91C_CAN_MB9_MID         EQU (0xFFFAC328) ;- (CAN_MB9) MailBox ID Register
AT91C_CAN_MB9_MMR         EQU (0xFFFAC320) ;- (CAN_MB9) MailBox Mode Register
AT91C_CAN_MB9_MDH         EQU (0xFFFAC338) ;- (CAN_MB9) MailBox Data High Register
AT91C_CAN_MB9_MSR         EQU (0xFFFAC330) ;- (CAN_MB9) MailBox Status Register
AT91C_CAN_MB9_MAM         EQU (0xFFFAC324) ;- (CAN_MB9) MailBox Acceptance Mask Register
AT91C_CAN_MB9_MDL         EQU (0xFFFAC334) ;- (CAN_MB9) MailBox Data Low Register
AT91C_CAN_MB9_MFID        EQU (0xFFFAC32C) ;- (CAN_MB9) MailBox Family ID Register
AT91C_CAN_MB9_MCR         EQU (0xFFFAC33C) ;- (CAN_MB9) MailBox Control Register
// - ========== Register definition for CAN_MB10 peripheral ========== 
AT91C_CAN_MB10_MCR        EQU (0xFFFAC35C) ;- (CAN_MB10) MailBox Control Register
AT91C_CAN_MB10_MDH        EQU (0xFFFAC358) ;- (CAN_MB10) MailBox Data High Register
AT91C_CAN_MB10_MAM        EQU (0xFFFAC344) ;- (CAN_MB10) MailBox Acceptance Mask Register
AT91C_CAN_MB10_MID        EQU (0xFFFAC348) ;- (CAN_MB10) MailBox ID Register
AT91C_CAN_MB10_MDL        EQU (0xFFFAC354) ;- (CAN_MB10) MailBox Data Low Register
AT91C_CAN_MB10_MSR        EQU (0xFFFAC350) ;- (CAN_MB10) MailBox Status Register
AT91C_CAN_MB10_MMR        EQU (0xFFFAC340) ;- (CAN_MB10) MailBox Mode Register
AT91C_CAN_MB10_MFID       EQU (0xFFFAC34C) ;- (CAN_MB10) MailBox Family ID Register
// - ========== Register definition for CAN_MB11 peripheral ========== 
AT91C_CAN_MB11_MSR        EQU (0xFFFAC370) ;- (CAN_MB11) MailBox Status Register
AT91C_CAN_MB11_MFID       EQU (0xFFFAC36C) ;- (CAN_MB11) MailBox Family ID Register
AT91C_CAN_MB11_MDL        EQU (0xFFFAC374) ;- (CAN_MB11) MailBox Data Low Register
AT91C_CAN_MB11_MDH        EQU (0xFFFAC378) ;- (CAN_MB11) MailBox Data High Register
AT91C_CAN_MB11_MID        EQU (0xFFFAC368) ;- (CAN_MB11) MailBox ID Register
AT91C_CAN_MB11_MCR        EQU (0xFFFAC37C) ;- (CAN_MB11) MailBox Control Register
AT91C_CAN_MB11_MMR        EQU (0xFFFAC360) ;- (CAN_MB11) MailBox Mode Register
AT91C_CAN_MB11_MAM        EQU (0xFFFAC364) ;- (CAN_MB11) MailBox Acceptance Mask Register
// - ========== Register definition for CAN_MB12 peripheral ========== 
AT91C_CAN_MB12_MAM        EQU (0xFFFAC384) ;- (CAN_MB12) MailBox Acceptance Mask Register
AT91C_CAN_MB12_MDH        EQU (0xFFFAC398) ;- (CAN_MB12) MailBox Data High Register
AT91C_CAN_MB12_MMR        EQU (0xFFFAC380) ;- (CAN_MB12) MailBox Mode Register
AT91C_CAN_MB12_MSR        EQU (0xFFFAC390) ;- (CAN_MB12) MailBox Status Register
AT91C_CAN_MB12_MFID       EQU (0xFFFAC38C) ;- (CAN_MB12) MailBox Family ID Register
AT91C_CAN_MB12_MID        EQU (0xFFFAC388) ;- (CAN_MB12) MailBox ID Register
AT91C_CAN_MB12_MCR        EQU (0xFFFAC39C) ;- (CAN_MB12) MailBox Control Register
AT91C_CAN_MB12_MDL        EQU (0xFFFAC394) ;- (CAN_MB12) MailBox Data Low Register
// - ========== Register definition for CAN_MB13 peripheral ========== 
AT91C_CAN_MB13_MDH        EQU (0xFFFAC3B8) ;- (CAN_MB13) MailBox Data High Register
AT91C_CAN_MB13_MFID       EQU (0xFFFAC3AC) ;- (CAN_MB13) MailBox Family ID Register
AT91C_CAN_MB13_MSR        EQU (0xFFFAC3B0) ;- (CAN_MB13) MailBox Status Register
AT91C_CAN_MB13_MID        EQU (0xFFFAC3A8) ;- (CAN_MB13) MailBox ID Register
AT91C_CAN_MB13_MAM        EQU (0xFFFAC3A4) ;- (CAN_MB13) MailBox Acceptance Mask Register
AT91C_CAN_MB13_MMR        EQU (0xFFFAC3A0) ;- (CAN_MB13) MailBox Mode Register
AT91C_CAN_MB13_MCR        EQU (0xFFFAC3BC) ;- (CAN_MB13) MailBox Control Register
AT91C_CAN_MB13_MDL        EQU (0xFFFAC3B4) ;- (CAN_MB13) MailBox Data Low Register
// - ========== Register definition for CAN_MB14 peripheral ========== 
AT91C_CAN_MB14_MDL        EQU (0xFFFAC3D4) ;- (CAN_MB14) MailBox Data Low Register
AT91C_CAN_MB14_MMR        EQU (0xFFFAC3C0) ;- (CAN_MB14) MailBox Mode Register
AT91C_CAN_MB14_MFID       EQU (0xFFFAC3CC) ;- (CAN_MB14) MailBox Family ID Register
AT91C_CAN_MB14_MCR        EQU (0xFFFAC3DC) ;- (CAN_MB14) MailBox Control Register
AT91C_CAN_MB14_MID        EQU (0xFFFAC3C8) ;- (CAN_MB14) MailBox ID Register
AT91C_CAN_MB14_MDH        EQU (0xFFFAC3D8) ;- (CAN_MB14) MailBox Data High Register
AT91C_CAN_MB14_MSR        EQU (0xFFFAC3D0) ;- (CAN_MB14) MailBox Status Register
AT91C_CAN_MB14_MAM        EQU (0xFFFAC3C4) ;- (CAN_MB14) MailBox Acceptance Mask Register
// - ========== Register definition for CAN_MB15 peripheral ========== 
AT91C_CAN_MB15_MDL        EQU (0xFFFAC3F4) ;- (CAN_MB15) MailBox Data Low Register
AT91C_CAN_MB15_MSR        EQU (0xFFFAC3F0) ;- (CAN_MB15) MailBox Status Register
AT91C_CAN_MB15_MID        EQU (0xFFFAC3E8) ;- (CAN_MB15) MailBox ID Register
AT91C_CAN_MB15_MAM        EQU (0xFFFAC3E4) ;- (CAN_MB15) MailBox Acceptance Mask Register
AT91C_CAN_MB15_MCR        EQU (0xFFFAC3FC) ;- (CAN_MB15) MailBox Control Register
AT91C_CAN_MB15_MFID       EQU (0xFFFAC3EC) ;- (CAN_MB15) MailBox Family ID Register
AT91C_CAN_MB15_MMR        EQU (0xFFFAC3E0) ;- (CAN_MB15) MailBox Mode Register
AT91C_CAN_MB15_MDH        EQU (0xFFFAC3F8) ;- (CAN_MB15) MailBox Data High Register
// - ========== Register definition for CAN peripheral ========== 
AT91C_CAN_ACR             EQU (0xFFFAC028) ;- (CAN) Abort Command Register
AT91C_CAN_BR              EQU (0xFFFAC014) ;- (CAN) Baudrate Register
AT91C_CAN_IDR             EQU (0xFFFAC008) ;- (CAN) Interrupt Disable Register
AT91C_CAN_TIMESTP         EQU (0xFFFAC01C) ;- (CAN) Time Stamp Register
AT91C_CAN_SR              EQU (0xFFFAC010) ;- (CAN) Status Register
AT91C_CAN_IMR             EQU (0xFFFAC00C) ;- (CAN) Interrupt Mask Register
AT91C_CAN_TCR             EQU (0xFFFAC024) ;- (CAN) Transfer Command Register
AT91C_CAN_TIM             EQU (0xFFFAC018) ;- (CAN) Timer Register
AT91C_CAN_IER             EQU (0xFFFAC004) ;- (CAN) Interrupt Enable Register
AT91C_CAN_ECR             EQU (0xFFFAC020) ;- (CAN) Error Counter Register
AT91C_CAN_VR              EQU (0xFFFAC0FC) ;- (CAN) Version Register
AT91C_CAN_MR              EQU (0xFFFAC000) ;- (CAN) Mode Register
// - ========== Register definition for PWMC_CH0 peripheral ========== 
AT91C_PWMC_CH0_CCNTR      EQU (0xFFFB820C) ;- (PWMC_CH0) Channel Counter Register
AT91C_PWMC_CH0_CPRDR      EQU (0xFFFB8208) ;- (PWMC_CH0) Channel Period Register
AT91C_PWMC_CH0_CUPDR      EQU (0xFFFB8210) ;- (PWMC_CH0) Channel Update Register
AT91C_PWMC_CH0_CDTYR      EQU (0xFFFB8204) ;- (PWMC_CH0) Channel Duty Cycle Register
AT91C_PWMC_CH0_CMR        EQU (0xFFFB8200) ;- (PWMC_CH0) Channel Mode Register
AT91C_PWMC_CH0_Reserved   EQU (0xFFFB8214) ;- (PWMC_CH0) Reserved
// - ========== Register definition for PWMC_CH1 peripheral ========== 
AT91C_PWMC_CH1_CCNTR      EQU (0xFFFB822C) ;- (PWMC_CH1) Channel Counter Register
AT91C_PWMC_CH1_CDTYR      EQU (0xFFFB8224) ;- (PWMC_CH1) Channel Duty Cycle Register
AT91C_PWMC_CH1_CMR        EQU (0xFFFB8220) ;- (PWMC_CH1) Channel Mode Register
AT91C_PWMC_CH1_CPRDR      EQU (0xFFFB8228) ;- (PWMC_CH1) Channel Period Register
AT91C_PWMC_CH1_Reserved   EQU (0xFFFB8234) ;- (PWMC_CH1) Reserved
AT91C_PWMC_CH1_CUPDR      EQU (0xFFFB8230) ;- (PWMC_CH1) Channel Update Register
// - ========== Register definition for PWMC_CH2 peripheral ========== 
AT91C_PWMC_CH2_CUPDR      EQU (0xFFFB8250) ;- (PWMC_CH2) Channel Update Register
AT91C_PWMC_CH2_CMR        EQU (0xFFFB8240) ;- (PWMC_CH2) Channel Mode Register
AT91C_PWMC_CH2_Reserved   EQU (0xFFFB8254) ;- (PWMC_CH2) Reserved
AT91C_PWMC_CH2_CPRDR      EQU (0xFFFB8248) ;- (PWMC_CH2) Channel Period Register
AT91C_PWMC_CH2_CDTYR      EQU (0xFFFB8244) ;- (PWMC_CH2) Channel Duty Cycle Register
AT91C_PWMC_CH2_CCNTR      EQU (0xFFFB824C) ;- (PWMC_CH2) Channel Counter Register
// - ========== Register definition for PWMC_CH3 peripheral ========== 
AT91C_PWMC_CH3_CPRDR      EQU (0xFFFB8268) ;- (PWMC_CH3) Channel Period Register
AT91C_PWMC_CH3_Reserved   EQU (0xFFFB8274) ;- (PWMC_CH3) Reserved
AT91C_PWMC_CH3_CUPDR      EQU (0xFFFB8270) ;- (PWMC_CH3) Channel Update Register
AT91C_PWMC_CH3_CDTYR      EQU (0xFFFB8264) ;- (PWMC_CH3) Channel Duty Cycle Register
AT91C_PWMC_CH3_CCNTR      EQU (0xFFFB826C) ;- (PWMC_CH3) Channel Counter Register
AT91C_PWMC_CH3_CMR        EQU (0xFFFB8260) ;- (PWMC_CH3) Channel Mode Register
// - ========== Register definition for PWMC peripheral ========== 
AT91C_PWMC_IDR            EQU (0xFFFB8014) ;- (PWMC) PWMC Interrupt Disable Register
AT91C_PWMC_MR             EQU (0xFFFB8000) ;- (PWMC) PWMC Mode Register
AT91C_PWMC_VR             EQU (0xFFFB80FC) ;- (PWMC) PWMC Version Register
AT91C_PWMC_IMR            EQU (0xFFFB8018) ;- (PWMC) PWMC Interrupt Mask Register
AT91C_PWMC_SR             EQU (0xFFFB800C) ;- (PWMC) PWMC Status Register
AT91C_PWMC_ISR            EQU (0xFFFB801C) ;- (PWMC) PWMC Interrupt Status Register
AT91C_PWMC_ENA            EQU (0xFFFB8004) ;- (PWMC) PWMC Enable Register
AT91C_PWMC_IER            EQU (0xFFFB8010) ;- (PWMC) PWMC Interrupt Enable Register
AT91C_PWMC_DIS            EQU (0xFFFB8008) ;- (PWMC) PWMC Disable Register
// - ========== Register definition for MACB peripheral ========== 
AT91C_MACB_ALE            EQU (0xFFFBC054) ;- (MACB) Alignment Error Register
AT91C_MACB_RRE            EQU (0xFFFBC06C) ;- (MACB) Receive Ressource Error Register
AT91C_MACB_SA4H           EQU (0xFFFBC0B4) ;- (MACB) Specific Address 4 Top, Last 2 bytes
AT91C_MACB_TPQ            EQU (0xFFFBC0BC) ;- (MACB) Transmit Pause Quantum Register
AT91C_MACB_RJA            EQU (0xFFFBC07C) ;- (MACB) Receive Jabbers Register
AT91C_MACB_SA2H           EQU (0xFFFBC0A4) ;- (MACB) Specific Address 2 Top, Last 2 bytes
AT91C_MACB_TPF            EQU (0xFFFBC08C) ;- (MACB) Transmitted Pause Frames Register
AT91C_MACB_ROV            EQU (0xFFFBC070) ;- (MACB) Receive Overrun Errors Register
AT91C_MACB_SA4L           EQU (0xFFFBC0B0) ;- (MACB) Specific Address 4 Bottom, First 4 bytes
AT91C_MACB_MAN            EQU (0xFFFBC034) ;- (MACB) PHY Maintenance Register
AT91C_MACB_TID            EQU (0xFFFBC0B8) ;- (MACB) Type ID Checking Register
AT91C_MACB_TBQP           EQU (0xFFFBC01C) ;- (MACB) Transmit Buffer Queue Pointer
AT91C_MACB_SA3L           EQU (0xFFFBC0A8) ;- (MACB) Specific Address 3 Bottom, First 4 bytes
AT91C_MACB_DTF            EQU (0xFFFBC058) ;- (MACB) Deferred Transmission Frame Register
AT91C_MACB_PTR            EQU (0xFFFBC038) ;- (MACB) Pause Time Register
AT91C_MACB_CSE            EQU (0xFFFBC068) ;- (MACB) Carrier Sense Error Register
AT91C_MACB_ECOL           EQU (0xFFFBC060) ;- (MACB) Excessive Collision Register
AT91C_MACB_STE            EQU (0xFFFBC084) ;- (MACB) SQE Test Error Register
AT91C_MACB_MCF            EQU (0xFFFBC048) ;- (MACB) Multiple Collision Frame Register
AT91C_MACB_IER            EQU (0xFFFBC028) ;- (MACB) Interrupt Enable Register
AT91C_MACB_ELE            EQU (0xFFFBC078) ;- (MACB) Excessive Length Errors Register
AT91C_MACB_USRIO          EQU (0xFFFBC0C0) ;- (MACB) USER Input/Output Register
AT91C_MACB_PFR            EQU (0xFFFBC03C) ;- (MACB) Pause Frames received Register
AT91C_MACB_FCSE           EQU (0xFFFBC050) ;- (MACB) Frame Check Sequence Error Register
AT91C_MACB_SA1L           EQU (0xFFFBC098) ;- (MACB) Specific Address 1 Bottom, First 4 bytes
AT91C_MACB_NCR            EQU (0xFFFBC000) ;- (MACB) Network Control Register
AT91C_MACB_HRT            EQU (0xFFFBC094) ;- (MACB) Hash Address Top[63:32]
AT91C_MACB_NCFGR          EQU (0xFFFBC004) ;- (MACB) Network Configuration Register
AT91C_MACB_SCF            EQU (0xFFFBC044) ;- (MACB) Single Collision Frame Register
AT91C_MACB_LCOL           EQU (0xFFFBC05C) ;- (MACB) Late Collision Register
AT91C_MACB_SA3H           EQU (0xFFFBC0AC) ;- (MACB) Specific Address 3 Top, Last 2 bytes
AT91C_MACB_HRB            EQU (0xFFFBC090) ;- (MACB) Hash Address Bottom[31:0]
AT91C_MACB_ISR            EQU (0xFFFBC024) ;- (MACB) Interrupt Status Register
AT91C_MACB_IMR            EQU (0xFFFBC030) ;- (MACB) Interrupt Mask Register
AT91C_MACB_WOL            EQU (0xFFFBC0C4) ;- (MACB) Wake On LAN Register
AT91C_MACB_USF            EQU (0xFFFBC080) ;- (MACB) Undersize Frames Register
AT91C_MACB_TSR            EQU (0xFFFBC014) ;- (MACB) Transmit Status Register
AT91C_MACB_FRO            EQU (0xFFFBC04C) ;- (MACB) Frames Received OK Register
AT91C_MACB_IDR            EQU (0xFFFBC02C) ;- (MACB) Interrupt Disable Register
AT91C_MACB_SA1H           EQU (0xFFFBC09C) ;- (MACB) Specific Address 1 Top, Last 2 bytes
AT91C_MACB_RLE            EQU (0xFFFBC088) ;- (MACB) Receive Length Field Mismatch Register
AT91C_MACB_TUND           EQU (0xFFFBC064) ;- (MACB) Transmit Underrun Error Register
AT91C_MACB_RSR            EQU (0xFFFBC020) ;- (MACB) Receive Status Register
AT91C_MACB_SA2L           EQU (0xFFFBC0A0) ;- (MACB) Specific Address 2 Bottom, First 4 bytes
AT91C_MACB_FTO            EQU (0xFFFBC040) ;- (MACB) Frames Transmitted OK Register
AT91C_MACB_RSE            EQU (0xFFFBC074) ;- (MACB) Receive Symbol Errors Register
AT91C_MACB_NSR            EQU (0xFFFBC008) ;- (MACB) Network Status Register
AT91C_MACB_RBQP           EQU (0xFFFBC018) ;- (MACB) Receive Buffer Queue Pointer
AT91C_MACB_REV            EQU (0xFFFBC0FC) ;- (MACB) Revision Register
// - ========== Register definition for LCDC peripheral ========== 
AT91C_LCDC_BA2            EQU (0x00700004) ;- (LCDC) DMA Base Address Register 2
AT91C_LCDC_DP3_4          EQU (0x00700830) ;- (LCDC) Dithering Pattern DP3_4 Register
AT91C_LCDC_FRMA2          EQU (0x00700014) ;- (LCDC) DMA Frame Address Register 2
AT91C_LCDC_TIM1           EQU (0x00700808) ;- (LCDC) LCD Timing Config 1 Register
AT91C_LCDC_FIFO           EQU (0x00700814) ;- (LCDC) LCD FIFO Register
AT91C_LCDC_TIM2           EQU (0x0070080C) ;- (LCDC) LCD Timing Config 2 Register
AT91C_LCDC_DP5_7          EQU (0x0070082C) ;- (LCDC) Dithering Pattern DP5_7 Register
AT91C_LCDC_IER            EQU (0x00700848) ;- (LCDC) Interrupt Enable Register
AT91C_LCDC_FRMCFG         EQU (0x00700018) ;- (LCDC) DMA Frame Configuration Register
AT91C_LCDC_FRMA1          EQU (0x00700010) ;- (LCDC) DMA Frame Address Register 1
AT91C_LCDC_DP3_5          EQU (0x00700824) ;- (LCDC) Dithering Pattern DP3_5 Register
AT91C_LCDC_PWRCON         EQU (0x0070083C) ;- (LCDC) Power Control Register
AT91C_LCDC_IMR            EQU (0x00700850) ;- (LCDC) Interrupt Mask Register
AT91C_LCDC_LUT_ENTRY      EQU (0x00700C00) ;- (LCDC) LUT Entries Register
AT91C_LCDC_IRR            EQU (0x00700864) ;- (LCDC) Interrupts Raw Status Register
AT91C_LCDC_FRMP2          EQU (0x0070000C) ;- (LCDC) DMA Frame Pointer Register 2
AT91C_LCDC_ICR            EQU (0x00700858) ;- (LCDC) Interrupt Clear Register
AT91C_LCDC_DP1_2          EQU (0x0070081C) ;- (LCDC) Dithering Pattern DP1_2 Register
AT91C_LCDC_DMACON         EQU (0x0070001C) ;- (LCDC) DMA Control Register
AT91C_LCDC_LCDFRCFG       EQU (0x00700810) ;- (LCDC) LCD Frame Config Register
AT91C_LCDC_DP2_3          EQU (0x00700828) ;- (LCDC) Dithering Pattern DP2_3 Register
AT91C_LCDC_DP6_7          EQU (0x00700838) ;- (LCDC) Dithering Pattern DP6_7 Register
AT91C_LCDC_LCDCON1        EQU (0x00700800) ;- (LCDC) LCD Control 1 Register
AT91C_LCDC_DMA2DCFG       EQU (0x00700020) ;- (LCDC) DMA 2D addressing configuration
AT91C_LCDC_GPR            EQU (0x0070085C) ;- (LCDC) General Purpose Register
AT91C_LCDC_BA1            EQU (0x00700000) ;- (LCDC) DMA Base Address Register 1
AT91C_LCDC_CTRSTCON       EQU (0x00700840) ;- (LCDC) Contrast Control Register
AT91C_LCDC_CTRSTVAL       EQU (0x00700844) ;- (LCDC) Contrast Value Register
AT91C_LCDC_LCDCON2        EQU (0x00700804) ;- (LCDC) LCD Control 2 Register
AT91C_LCDC_IDR            EQU (0x0070084C) ;- (LCDC) Interrupt Disable Register
AT91C_LCDC_ISR            EQU (0x00700854) ;- (LCDC) Interrupt Enable Register
AT91C_LCDC_ITR            EQU (0x00700860) ;- (LCDC) Interrupts Test Register
AT91C_LCDC_DP4_7          EQU (0x00700820) ;- (LCDC) Dithering Pattern DP4_7 Register
AT91C_LCDC_MVAL           EQU (0x00700818) ;- (LCDC) LCD Mode Toggle Rate Value Register
AT91C_LCDC_DP4_5          EQU (0x00700834) ;- (LCDC) Dithering Pattern DP4_5 Register
AT91C_LCDC_FRMP1          EQU (0x00700008) ;- (LCDC) DMA Frame Pointer Register 1
// - ========== Register definition for DMA peripheral ========== 
AT91C_DMA_RAWSRCTRAN      EQU (0x008002D0) ;- (DMA) Raw Status for IntSrcTran Interrupt
AT91C_DMA_SGR0            EQU (0x00800048) ;- (DMA) Source Gather Register for channel 0
AT91C_DMA_REQSRCREG       EQU (0x00800368) ;- (DMA) Source Software Transaction Request Register
AT91C_DMA_STATUSERR       EQU (0x00800308) ;- (DMA) Status for IntErr IInterrupt
AT91C_DMA_SAR1            EQU (0x00800058) ;- (DMA) Source Address Register for channel 1
AT91C_DMA_CLEARDSTTRAN    EQU (0x00800350) ;- (DMA) Clear for IntDstTran IInterrupt
AT91C_DMA_STATUSSRCTRAN   EQU (0x008002F8) ;- (DMA) Status for IntSrcTran Interrupt
AT91C_DMA_REQDSTREG       EQU (0x00800370) ;- (DMA) Destination Software Transaction Request Register
AT91C_DMA_DSTATAR0        EQU (0x00800038) ;- (DMA) Destination Status Adress Register for channel 0
AT91C_DMA_LSTREQDSTREG    EQU (0x00800390) ;- (DMA) Last Destination Software Transaction Request Register
AT91C_DMA_SGLREQDSTREG    EQU (0x00800380) ;- (DMA) Single Destination Software Transaction Request Register
AT91C_DMA_CTL1h           EQU (0x00800074) ;- (DMA) Control Register for channel 1 - high
AT91C_DMA_CLEARERR        EQU (0x00800358) ;- (DMA) Clear for IntErr Interrupt
AT91C_DMA_DSR0            EQU (0x00800050) ;- (DMA) Destination Scatter Register for channel 0
AT91C_DMA_DMATESTREG      EQU (0x008003B0) ;- (DMA) DW_ahb_dmac Test Register
AT91C_DMA_DSR1            EQU (0x008000A8) ;- (DMA) Destination Scatter Register for channel 1
AT91C_DMA_CTL0l           EQU (0x00800018) ;- (DMA) Control Register for channel 0 - low
AT91C_DMA_STATUSBLOCK     EQU (0x008002F0) ;- (DMA) Status for IntBlock Interrupt
AT91C_DMA_SAR0            EQU (0x00800000) ;- (DMA) Source Address Register for channel 0
AT91C_DMA_LLP0            EQU (0x00800010) ;- (DMA) Linked List Pointer Register for channel 0
AT91C_DMA_CTL1l           EQU (0x00800070) ;- (DMA) Control Register for channel 1 - low
AT91C_DMA_SGR1            EQU (0x008000A0) ;- (DMA) Source Gather Register for channel 1
AT91C_DMA_CFG0l           EQU (0x00800040) ;- (DMA) Configuration Register for channel 0 - low
AT91C_DMA_CFG0h           EQU (0x00800044) ;- (DMA) Configuration Register for channel 0 - high
AT91C_DMA_STATUSTFR       EQU (0x008002E8) ;- (DMA) Status for IntTfr Interrupt
AT91C_DMA_MASKBLOCK       EQU (0x00800318) ;- (DMA) Mask for IntBlock Interrupt
AT91C_DMA_RAWBLOCK        EQU (0x008002C8) ;- (DMA) Raw Status for IntBlock Interrupt
AT91C_DMA_CHENREG         EQU (0x008003A0) ;- (DMA) DW_ahb_dmac Channel Enable Register
AT91C_DMA_DSTAT0          EQU (0x00800028) ;- (DMA) Destination Status Register for channel 0
AT91C_DMA_CLEARSRCTRAN    EQU (0x00800348) ;- (DMA) Clear for IntSrcTran Interrupt
AT91C_DMA_DAR1            EQU (0x00800060) ;- (DMA) Destination Address Register for channel 1
AT91C_DMA_CLEARBLOCK      EQU (0x00800340) ;- (DMA) Clear for IntBlock Interrupt
AT91C_DMA_CFG1h           EQU (0x0080009C) ;- (DMA) Configuration Register for channel 1 - high
AT91C_DMA_DSTATAR1        EQU (0x00800090) ;- (DMA) Destination Status Adress Register for channel 1
AT91C_DMA_RAWERR          EQU (0x008002E0) ;- (DMA) Raw Status for IntErr Interrupt
AT91C_DMA_CTL0h           EQU (0x0080001C) ;- (DMA) Control Register for channel 0 - high
AT91C_DMA_SGLREQSRCREG    EQU (0x00800378) ;- (DMA) Single Source Software Transaction Request Register
AT91C_DMA_LLP1            EQU (0x00800068) ;- (DMA) Linked List Pointer Register for channel 1
AT91C_DMA_MASKDSTTRAN     EQU (0x00800328) ;- (DMA) Mask for IntDstTran Interrupt
AT91C_DMA_MASKSRCTRAN     EQU (0x00800320) ;- (DMA) Mask for IntSrcTran Interrupt
AT91C_DMA_LSTREQSRCREG    EQU (0x00800388) ;- (DMA) Last Source Software Transaction Request Register
AT91C_DMA_CLEARTFR        EQU (0x00800338) ;- (DMA) Clear for IntTfr Interrupt
AT91C_DMA_SSTATAR1        EQU (0x00800088) ;- (DMA) Source Status Adress Register for channel 1
AT91C_DMA_DAR0            EQU (0x00800008) ;- (DMA) Destination Address Register for channel 0
AT91C_DMA_SSTAT0          EQU (0x00800020) ;- (DMA) Source Status Register for channel 0
AT91C_DMA_DMAIDREG        EQU (0x008003A8) ;- (DMA) DW_ahb_dmac ID Register
AT91C_DMA_DSTAT1          EQU (0x00800080) ;- (DMA) Destination Status Register for channel 1
AT91C_DMA_RAWTFR          EQU (0x008002C0) ;- (DMA) Raw Status for IntTfr Interrupt
AT91C_DMA_VERSIONID       EQU (0x008003B8) ;- (DMA) DW_ahb_dmac Version ID Register
AT91C_DMA_STATUSDSTTRAN   EQU (0x00800300) ;- (DMA) Status for IntDstTran IInterrupt
AT91C_DMA_MASKERR         EQU (0x00800330) ;- (DMA) Mask for IntErr Interrupt
AT91C_DMA_SSTATAR0        EQU (0x00800030) ;- (DMA) Source Status Adress Register for channel 0
AT91C_DMA_MASKTFR         EQU (0x00800310) ;- (DMA) Mask for IntTfr Interrupt
AT91C_DMA_SSTAT1          EQU (0x00800078) ;- (DMA) Source Status Register for channel 1
AT91C_DMA_STATUSINT       EQU (0x00800360) ;- (DMA) Status for each Interrupt Type
AT91C_DMA_DMACFGREG       EQU (0x00800398) ;- (DMA) DW_ahb_dmac Configuration Register
AT91C_DMA_RAWDSTTRAN      EQU (0x008002D8) ;- (DMA) Raw Status for IntDstTran Interrupt
AT91C_DMA_CFG1l           EQU (0x00800098) ;- (DMA) Configuration Register for channel 1 - low
// - ========== Register definition for UDP peripheral ========== 
AT91C_UDP_FDR             EQU (0xFFF78050) ;- (UDP) Endpoint FIFO Data Register
AT91C_UDP_IER             EQU (0xFFF78010) ;- (UDP) Interrupt Enable Register
AT91C_UDP_CSR             EQU (0xFFF78030) ;- (UDP) Endpoint Control and Status Register
AT91C_UDP_RSTEP           EQU (0xFFF78028) ;- (UDP) Reset Endpoint Register
AT91C_UDP_GLBSTATE        EQU (0xFFF78004) ;- (UDP) Global State Register
AT91C_UDP_TXVC            EQU (0xFFF78074) ;- (UDP) Transceiver Control Register
AT91C_UDP_IDR             EQU (0xFFF78014) ;- (UDP) Interrupt Disable Register
AT91C_UDP_ISR             EQU (0xFFF7801C) ;- (UDP) Interrupt Status Register
AT91C_UDP_IMR             EQU (0xFFF78018) ;- (UDP) Interrupt Mask Register
AT91C_UDP_FADDR           EQU (0xFFF78008) ;- (UDP) Function Address Register
AT91C_UDP_NUM             EQU (0xFFF78000) ;- (UDP) Frame Number Register
AT91C_UDP_ICR             EQU (0xFFF78020) ;- (UDP) Interrupt Clear Register
// - ========== Register definition for UHP peripheral ========== 
AT91C_UHP_HcRhDescriptorA EQU (0x00A00048) ;- (UHP) Root Hub characteristics A
AT91C_UHP_HcInterruptStatus EQU (0x00A0000C) ;- (UHP) Interrupt Status Register
AT91C_UHP_HcLSThreshold   EQU (0x00A00044) ;- (UHP) LS Threshold
AT91C_UHP_HcBulkDoneHead  EQU (0x00A00030) ;- (UHP) Last completed transfer descriptor
AT91C_UHP_HcInterruptDisable EQU (0x00A00014) ;- (UHP) Interrupt Disable Register
AT91C_UHP_HcRhPortStatus  EQU (0x00A00054) ;- (UHP) Root Hub Port Status Register
AT91C_UHP_HcControl       EQU (0x00A00004) ;- (UHP) Operating modes for the Host Controller
AT91C_UHP_HcPeriodCurrentED EQU (0x00A0001C) ;- (UHP) Current Isochronous or Interrupt Endpoint Descriptor
AT91C_UHP_HcControlHeadED EQU (0x00A00020) ;- (UHP) First Endpoint Descriptor of the Control list
AT91C_UHP_HcCommandStatus EQU (0x00A00008) ;- (UHP) Command & status Register
AT91C_UHP_HcFmNumber      EQU (0x00A0003C) ;- (UHP) Frame number
AT91C_UHP_HcRhDescriptorB EQU (0x00A0004C) ;- (UHP) Root Hub characteristics B
AT91C_UHP_HcBulkHeadED    EQU (0x00A00028) ;- (UHP) First endpoint register of the Bulk list
AT91C_UHP_HcFmRemaining   EQU (0x00A00038) ;- (UHP) Bit time remaining in the current Frame
AT91C_UHP_HcRevision      EQU (0x00A00000) ;- (UHP) Revision
AT91C_UHP_HcInterruptEnable EQU (0x00A00010) ;- (UHP) Interrupt Enable Register
AT91C_UHP_HcControlCurrentED EQU (0x00A00024) ;- (UHP) Endpoint Control and Status Register
AT91C_UHP_HcBulkCurrentED EQU (0x00A0002C) ;- (UHP) Current endpoint of the Bulk list
AT91C_UHP_HcHCCA          EQU (0x00A00018) ;- (UHP) Pointer to the Host Controller Communication Area
AT91C_UHP_HcPeriodicStart EQU (0x00A00040) ;- (UHP) Periodic Start
AT91C_UHP_HcRhStatus      EQU (0x00A00050) ;- (UHP) Root Hub Status register
AT91C_UHP_HcFmInterval    EQU (0x00A00034) ;- (UHP) Bit time between 2 consecutive SOFs
// - ========== Register definition for TBOX peripheral ========== 
AT91C_TBOX_GPSSIGFILE     EQU (0x70000BA0) ;- (TBOX) GPS RFIN/DRFIN driven from files/Samples_GPS.data
AT91C_TBOX_PIOA           EQU (0x7000093C) ;- (TBOX) Value Of PIOA
AT91C_TBOX_PWM1           EQU (0x70000A08) ;- (TBOX) PWM1[4:0]=nb pulses on pb7, PWM1[9:5]=nb pulses on pc28, PWM1[20:16]=nb pulses on pb8, PWM1[25:21]=nb pulses on pc3
AT91C_TBOX_PIODENABLEFORCE EQU (0x7000092C) ;- (TBOX) If each bit is 1, the corresponding bit of PIOD is controlled by TBOX_PIODFORCEVALUE
AT91C_TBOX_PIODPUN        EQU (0x7000090C) ;- (TBOX) Spy on PIO PUN inputs
AT91C_TBOX_PIOAENABLEFORCE EQU (0x70000914) ;- (TBOX) If each bit is 1, the corresponding bit of PIOA is controlled by TBOX_PIOAFORCEVALUE
AT91C_TBOX_PIOD           EQU (0x70000948) ;- (TBOX) Value Of PIOD
AT91C_TBOX_STOPAPBSPY     EQU (0x70000A1C) ;- (TBOX) When 1, no more APB SPY messages
AT91C_TBOX_PIOEENABLEFORCE EQU (0x70000934) ;- (TBOX) If each bit is 1, the corresponding bit of PIOE is controlled by TBOX_PIOEFORCEVALUE
AT91C_TBOX_PIOBPUN        EQU (0x70000904) ;- (TBOX) Spy on PIO PUN inputs
AT91C_TBOX_USBDEV         EQU (0x70000A14) ;- (TBOX) USB device testbench : bit 0 = flag0, bit 1 = flag1
AT91C_TBOX_GPSRAND        EQU (0x70000B04) ;- (TBOX) GPS random data for correlator (Stimulus - Internal Node)
AT91C_TBOX_KBD            EQU (0x70000A18) ;- (TBOX) Keyboard testbench : bit 0 = keypressed; bits[7:6] = key column; bits[5:4] = key row;
AT91C_TBOX_PIOEFORCEVALUE EQU (0x70000938) ;- (TBOX) Value to force on PIOA when bits TBOX_PIOEENABLEFORCE are 1
AT91C_TBOX_AC97START      EQU (0x70000A00) ;- (TBOX) Start of AC97 test: swith PIO mux to connect PIOs to audio codec model.
AT91C_TBOX_PIOAPUN        EQU (0x70000900) ;- (TBOX) Spy on PIO PUN inputs
AT91C_TBOX_GPSACQSTATUS   EQU (0x70000B08) ;- (TBOX) GPS acquisition status (Probe - Internal Node)
AT91C_TBOX_PIOEPUN        EQU (0x70000910) ;- (TBOX) Spy on PIO PUN inputs
AT91C_TBOX_PIOE           EQU (0x7000094C) ;- (TBOX) Value Of PIOE
AT91C_TBOX_PIODFORCEVALUE EQU (0x70000930) ;- (TBOX) Value to force on PIOA when bits TBOX_PIODENABLEFORCE are 1
AT91C_TBOX_PWMSTART       EQU (0x70000A04) ;- (TBOX) Start of PWM test: Start to count edges on PWM IOs
AT91C_TBOX_GPSSIGIB       EQU (0x70000BB0) ;- (TBOX) GPS DRFIN[5:4] aka SIGI_B (Stimulus)
AT91C_TBOX_GPSSYNCHRO     EQU (0x70000B00) ;- (TBOX) GPS synchronization (Stimulus)
AT91C_TBOX_PIOAFORCEVALUE EQU (0x70000918) ;- (TBOX) Value to force on PIOA when bits TBOX_PIOAENABLEFORCE are 1
AT91C_TBOX_GPSACQDATA     EQU (0x70000B0C) ;- (TBOX) GPS acquisition data (Probe - Internal Node)
AT91C_TBOX_SHMCTRL        EQU (0x70000000) ;- (TBOX) SHM Probe Control: 0-> shm probe stopped, 1: shm probe started
AT91C_TBOX_MAC            EQU (0x70000A10) ;- (TBOX) MAC testbench : bit 0 = rxtrig, bit 1 = clkofftester, bit 2 = err_sig_loops
AT91C_TBOX_GPSSIGIA       EQU (0x70000BA4) ;- (TBOX) GPS DRFIN[1:0] aka SIGI_A (Stimulus)
AT91C_TBOX_PIOBFORCEVALUE EQU (0x70000920) ;- (TBOX) Value to force on PIOA when bits TBOX_PIOBENABLEFORCE are 1
AT91C_TBOX_PIOCPUN        EQU (0x70000908) ;- (TBOX) Spy on PIO PUN inputs
AT91C_TBOX_PIOCFORCEVALUE EQU (0x70000928) ;- (TBOX) Value to force on PIOA when bits TBOX_PIOCENABLEFORCE are 1
AT91C_TBOX_PIOC           EQU (0x70000944) ;- (TBOX) Value Of PIOC
AT91C_TBOX_DMAEXTREQ      EQU (0x70000810) ;- (TBOX) DMA External request lines 3 to 0
AT91C_TBOX_GPSDUMPRES     EQU (0x70000BC0) ;- (TBOX) GPS Dump results and errors
AT91C_TBOX_PIOCENABLEFORCE EQU (0x70000924) ;- (TBOX) If each bit is 1, the corresponding bit of PIOC is controlled by TBOX_PIOCFORCEVALUE
AT91C_TBOX_PWM2           EQU (0x70000A0C) ;- (TBOX) PWM2[3:0]=nb pulses on pb27, PWM2[7:4]=nb pulses on pc29, PWM2[19:16]=nb pulses on pb29, PWM2[23:20]=nb pulses on pe10
AT91C_TBOX_GPSSIGQA       EQU (0x70000BA8) ;- (TBOX) GPS DRFIN[3:2] aka SIGQ_A (Stimulus)
AT91C_TBOX_PIOB           EQU (0x70000940) ;- (TBOX) Value Of PIOB
AT91C_TBOX_PIOBENABLEFORCE EQU (0x7000091C) ;- (TBOX) If each bit is 1, the corresponding bit of PIOB is controlled by TBOX_PIOBFORCEVALUE
AT91C_TBOX_GPSSIGQB       EQU (0x70000BB4) ;- (TBOX) GPS DRFIN[7:6] aka SIGQ_B (Stimulus)
// - ========== Register definition for HECC0 peripheral ========== 
AT91C_HECC0_SR            EQU (0xFFFFE008) ;- (HECC0)  ECC Status register
AT91C_HECC0_VR            EQU (0xFFFFE0FC) ;- (HECC0)  ECC Version register
AT91C_HECC0_CR            EQU (0xFFFFE000) ;- (HECC0)  ECC reset register
AT91C_HECC0_PR            EQU (0xFFFFE00C) ;- (HECC0)  ECC Parity register
AT91C_HECC0_MR            EQU (0xFFFFE004) ;- (HECC0)  ECC Page size register
AT91C_HECC0_NPR           EQU (0xFFFFE010) ;- (HECC0)  ECC Parity N register
// - ========== Register definition for HECC1 peripheral ========== 
AT91C_HECC1_MR            EQU (0xFFFFE604) ;- (HECC1)  ECC Page size register
AT91C_HECC1_VR            EQU (0xFFFFE6FC) ;- (HECC1)  ECC Version register
AT91C_HECC1_PR            EQU (0xFFFFE60C) ;- (HECC1)  ECC Parity register
AT91C_HECC1_CR            EQU (0xFFFFE600) ;- (HECC1)  ECC reset register
AT91C_HECC1_NPR           EQU (0xFFFFE610) ;- (HECC1)  ECC Parity N register
AT91C_HECC1_SR            EQU (0xFFFFE608) ;- (HECC1)  ECC Status register
// - ========== Register definition for HISI peripheral ========== 
AT91C_HISI_CDBA           EQU (0xFFFC402C) ;- (HISI) Codec Dma Address Register
AT91C_HISI_PDECF          EQU (0xFFFC4024) ;- (HISI) Preview Decimation Factor Register
AT91C_HISI_IMR            EQU (0xFFFC4014) ;- (HISI) Interrupt Mask Register
AT91C_HISI_IER            EQU (0xFFFC400C) ;- (HISI) Interrupt Enable Register
AT91C_HISI_SR             EQU (0xFFFC4008) ;- (HISI) Status Register
AT91C_HISI_Y2RSET0        EQU (0xFFFC4030) ;- (HISI) Color Space Conversion Register
AT91C_HISI_PFBD           EQU (0xFFFC4028) ;- (HISI) Preview Frame Buffer Address Register
AT91C_HISI_PSIZE          EQU (0xFFFC4020) ;- (HISI) Preview Size Register
AT91C_HISI_IDR            EQU (0xFFFC4010) ;- (HISI) Interrupt Disable Register
AT91C_HISI_R2YSET2        EQU (0xFFFC4040) ;- (HISI) Color Space Conversion Register
AT91C_HISI_R2YSET0        EQU (0xFFFC4038) ;- (HISI) Color Space Conversion Register
AT91C_HISI_CR1            EQU (0xFFFC4000) ;- (HISI) Control Register 1
AT91C_HISI_CR2            EQU (0xFFFC4004) ;- (HISI) Control Register 2
AT91C_HISI_Y2RSET1        EQU (0xFFFC4034) ;- (HISI) Color Space Conversion Register
AT91C_HISI_R2YSET1        EQU (0xFFFC403C) ;- (HISI) Color Space Conversion Register

// - *****************************************************************************
// -               PIO DEFINITIONS FOR AT91SAM9263
// - *****************************************************************************
AT91C_PIO_PA0             EQU (1 <<  0) ;- Pin Controlled by PA0
AT91C_PA0_MCI0_DA0        EQU (AT91C_PIO_PA0) ;-  
AT91C_PA0_SPI0_MISO       EQU (AT91C_PIO_PA0) ;-  
AT91C_PIO_PA1             EQU (1 <<  1) ;- Pin Controlled by PA1
AT91C_PA1_MCI0_CDA        EQU (AT91C_PIO_PA1) ;-  
AT91C_PA1_SPI0_MOSI       EQU (AT91C_PIO_PA1) ;-  
AT91C_PIO_PA10            EQU (1 << 10) ;- Pin Controlled by PA10
AT91C_PA10_MCI1_DA2       EQU (AT91C_PIO_PA10) ;-  
AT91C_PIO_PA11            EQU (1 << 11) ;- Pin Controlled by PA11
AT91C_PA11_MCI1_DA3       EQU (AT91C_PIO_PA11) ;-  
AT91C_PIO_PA12            EQU (1 << 12) ;- Pin Controlled by PA12
AT91C_PA12_MCI0_CK        EQU (AT91C_PIO_PA12) ;-  
AT91C_PIO_PA13            EQU (1 << 13) ;- Pin Controlled by PA13
AT91C_PA13_CANTX          EQU (AT91C_PIO_PA13) ;-  
AT91C_PA13_PCK0           EQU (AT91C_PIO_PA13) ;-  
AT91C_PIO_PA14            EQU (1 << 14) ;- Pin Controlled by PA14
AT91C_PA14_CANRX          EQU (AT91C_PIO_PA14) ;-  
AT91C_PA14_IRQ0           EQU (AT91C_PIO_PA14) ;-  
AT91C_PIO_PA15            EQU (1 << 15) ;- Pin Controlled by PA15
AT91C_PA15_TCLK2          EQU (AT91C_PIO_PA15) ;-  
AT91C_PA15_IRQ1           EQU (AT91C_PIO_PA15) ;-  
AT91C_PIO_PA16            EQU (1 << 16) ;- Pin Controlled by PA16
AT91C_PA16_MCI0_CDB       EQU (AT91C_PIO_PA16) ;-  
AT91C_PA16_EBI1_D16       EQU (AT91C_PIO_PA16) ;-  
AT91C_PIO_PA17            EQU (1 << 17) ;- Pin Controlled by PA17
AT91C_PA17_MCI0_DB0       EQU (AT91C_PIO_PA17) ;-  
AT91C_PA17_EBI1_D17       EQU (AT91C_PIO_PA17) ;-  
AT91C_PIO_PA18            EQU (1 << 18) ;- Pin Controlled by PA18
AT91C_PA18_MCI0_DB1       EQU (AT91C_PIO_PA18) ;-  
AT91C_PA18_EBI1_D18       EQU (AT91C_PIO_PA18) ;-  
AT91C_PIO_PA19            EQU (1 << 19) ;- Pin Controlled by PA19
AT91C_PA19_MCI0_DB2       EQU (AT91C_PIO_PA19) ;-  
AT91C_PA19_EBI1_D19       EQU (AT91C_PIO_PA19) ;-  
AT91C_PIO_PA2             EQU (1 <<  2) ;- Pin Controlled by PA2
AT91C_PA2_UNCONNECTED_PA2_A EQU (AT91C_PIO_PA2) ;-  
AT91C_PA2_SPI0_SPCK       EQU (AT91C_PIO_PA2) ;-  
AT91C_PIO_PA20            EQU (1 << 20) ;- Pin Controlled by PA20
AT91C_PA20_MCI0_DB3       EQU (AT91C_PIO_PA20) ;-  
AT91C_PA20_EBI1_D20       EQU (AT91C_PIO_PA20) ;-  
AT91C_PIO_PA21            EQU (1 << 21) ;- Pin Controlled by PA21
AT91C_PA21_MCI1_CDB       EQU (AT91C_PIO_PA21) ;-  
AT91C_PA21_EBI1_D21       EQU (AT91C_PIO_PA21) ;-  
AT91C_PIO_PA22            EQU (1 << 22) ;- Pin Controlled by PA22
AT91C_PA22_MCI1_DB0       EQU (AT91C_PIO_PA22) ;-  
AT91C_PA22_EBI1_D22       EQU (AT91C_PIO_PA22) ;-  
AT91C_PIO_PA23            EQU (1 << 23) ;- Pin Controlled by PA23
AT91C_PA23_MCI1_DB1       EQU (AT91C_PIO_PA23) ;-  
AT91C_PA23_EBI1_D23       EQU (AT91C_PIO_PA23) ;-  
AT91C_PIO_PA24            EQU (1 << 24) ;- Pin Controlled by PA24
AT91C_PA24_MCI1_DB2       EQU (AT91C_PIO_PA24) ;-  
AT91C_PA24_EBI1_D24       EQU (AT91C_PIO_PA24) ;-  
AT91C_PIO_PA25            EQU (1 << 25) ;- Pin Controlled by PA25
AT91C_PA25_MCI1_DB3       EQU (AT91C_PIO_PA25) ;-  
AT91C_PA25_EBI1_D25       EQU (AT91C_PIO_PA25) ;-  
AT91C_PIO_PA26            EQU (1 << 26) ;- Pin Controlled by PA26
AT91C_PA26_TXD0           EQU (AT91C_PIO_PA26) ;-  
AT91C_PA26_EBI1_D26       EQU (AT91C_PIO_PA26) ;-  
AT91C_PIO_PA27            EQU (1 << 27) ;- Pin Controlled by PA27
AT91C_PA27_RXD0           EQU (AT91C_PIO_PA27) ;-  
AT91C_PA27_EBI1_D27       EQU (AT91C_PIO_PA27) ;-  
AT91C_PIO_PA28            EQU (1 << 28) ;- Pin Controlled by PA28
AT91C_PA28_RTS0           EQU (AT91C_PIO_PA28) ;-  
AT91C_PA28_EBI1_D28       EQU (AT91C_PIO_PA28) ;-  
AT91C_PIO_PA29            EQU (1 << 29) ;- Pin Controlled by PA29
AT91C_PA29_CTS0           EQU (AT91C_PIO_PA29) ;-  
AT91C_PA29_EBI1_D29       EQU (AT91C_PIO_PA29) ;-  
AT91C_PIO_PA3             EQU (1 <<  3) ;- Pin Controlled by PA3
AT91C_PA3_MCI0_DA1        EQU (AT91C_PIO_PA3) ;-  
AT91C_PA3_SPI0_NPCS1      EQU (AT91C_PIO_PA3) ;-  
AT91C_PIO_PA30            EQU (1 << 30) ;- Pin Controlled by PA30
AT91C_PA30_SCK0           EQU (AT91C_PIO_PA30) ;-  
AT91C_PA30_EBI1_D30       EQU (AT91C_PIO_PA30) ;-  
AT91C_PIO_PA31            EQU (1 << 31) ;- Pin Controlled by PA31
AT91C_PA31_DMARQ0         EQU (AT91C_PIO_PA31) ;-  
AT91C_PA31_EBI1_D31       EQU (AT91C_PIO_PA31) ;-  
AT91C_PIO_PA4             EQU (1 <<  4) ;- Pin Controlled by PA4
AT91C_PA4_MCI0_DA2        EQU (AT91C_PIO_PA4) ;-  
AT91C_PA4_SPI0_NPCS2A     EQU (AT91C_PIO_PA4) ;-  
AT91C_PIO_PA5             EQU (1 <<  5) ;- Pin Controlled by PA5
AT91C_PA5_MCI0_DA3        EQU (AT91C_PIO_PA5) ;-  
AT91C_PA5_SPI0_NPCS0      EQU (AT91C_PIO_PA5) ;-  
AT91C_PIO_PA6             EQU (1 <<  6) ;- Pin Controlled by PA6
AT91C_PA6_MCI1_CK         EQU (AT91C_PIO_PA6) ;-  
AT91C_PA6_PCK2            EQU (AT91C_PIO_PA6) ;-  
AT91C_PIO_PA7             EQU (1 <<  7) ;- Pin Controlled by PA7
AT91C_PA7_MCI1_CDA        EQU (AT91C_PIO_PA7) ;-  
AT91C_PIO_PA8             EQU (1 <<  8) ;- Pin Controlled by PA8
AT91C_PA8_MCI1_DA0        EQU (AT91C_PIO_PA8) ;-  
AT91C_PIO_PA9             EQU (1 <<  9) ;- Pin Controlled by PA9
AT91C_PA9_MCI1_DA1        EQU (AT91C_PIO_PA9) ;-  
AT91C_PIO_PB0             EQU (1 <<  0) ;- Pin Controlled by PB0
AT91C_PB0_AC97FS          EQU (AT91C_PIO_PB0) ;-  
AT91C_PB0_TF0             EQU (AT91C_PIO_PB0) ;-  
AT91C_PIO_PB1             EQU (1 <<  1) ;- Pin Controlled by PB1
AT91C_PB1_AC97CK          EQU (AT91C_PIO_PB1) ;-  
AT91C_PB1_TK0             EQU (AT91C_PIO_PB1) ;-  
AT91C_PIO_PB10            EQU (1 << 10) ;- Pin Controlled by PB10
AT91C_PB10_RK1            EQU (AT91C_PIO_PB10) ;-  
AT91C_PB10_PCK1           EQU (AT91C_PIO_PB10) ;-  
AT91C_PIO_PB11            EQU (1 << 11) ;- Pin Controlled by PB11
AT91C_PB11_RF1            EQU (AT91C_PIO_PB11) ;-  
AT91C_PB11_SPI0_NPCS3B    EQU (AT91C_PIO_PB11) ;-  
AT91C_PIO_PB12            EQU (1 << 12) ;- Pin Controlled by PB12
AT91C_PB12_SPI1_MISO      EQU (AT91C_PIO_PB12) ;-  
AT91C_PIO_PB13            EQU (1 << 13) ;- Pin Controlled by PB13
AT91C_PB13_SPI1_MOSI      EQU (AT91C_PIO_PB13) ;-  
AT91C_PIO_PB14            EQU (1 << 14) ;- Pin Controlled by PB14
AT91C_PB14_SPI1_SPCK      EQU (AT91C_PIO_PB14) ;-  
AT91C_PIO_PB15            EQU (1 << 15) ;- Pin Controlled by PB15
AT91C_PB15_SPI1_NPCS0     EQU (AT91C_PIO_PB15) ;-  
AT91C_PIO_PB16            EQU (1 << 16) ;- Pin Controlled by PB16
AT91C_PB16_SPI1_NPCS1     EQU (AT91C_PIO_PB16) ;-  
AT91C_PB16_PCK1           EQU (AT91C_PIO_PB16) ;-  
AT91C_PIO_PB17            EQU (1 << 17) ;- Pin Controlled by PB17
AT91C_PB17_SPI1_NPCS2B    EQU (AT91C_PIO_PB17) ;-  
AT91C_PB17_TIOA2          EQU (AT91C_PIO_PB17) ;-  
AT91C_PIO_PB18            EQU (1 << 18) ;- Pin Controlled by PB18
AT91C_PB18_SPI1_NPCS3B    EQU (AT91C_PIO_PB18) ;-  
AT91C_PB18_TIOB2          EQU (AT91C_PIO_PB18) ;-  
AT91C_PIO_PB19            EQU (1 << 19) ;- Pin Controlled by PB19
AT91C_PIO_PB2             EQU (1 <<  2) ;- Pin Controlled by PB2
AT91C_PB2_AC97TX          EQU (AT91C_PIO_PB2) ;-  
AT91C_PB2_TD0             EQU (AT91C_PIO_PB2) ;-  
AT91C_PIO_PB20            EQU (1 << 20) ;- Pin Controlled by PB20
AT91C_PIO_PB21            EQU (1 << 21) ;- Pin Controlled by PB21
AT91C_PIO_PB22            EQU (1 << 22) ;- Pin Controlled by PB22
AT91C_PIO_PB23            EQU (1 << 23) ;- Pin Controlled by PB23
AT91C_PIO_PB24            EQU (1 << 24) ;- Pin Controlled by PB24
AT91C_PB24_UNCONNECTED_PB24_A EQU (AT91C_PIO_PB24) ;-  
AT91C_PB24_DMARQ3         EQU (AT91C_PIO_PB24) ;-  
AT91C_PIO_PB25            EQU (1 << 25) ;- Pin Controlled by PB25
AT91C_PIO_PB26            EQU (1 << 26) ;- Pin Controlled by PB26
AT91C_PIO_PB27            EQU (1 << 27) ;- Pin Controlled by PB27
AT91C_PB27_UNCONNECTED_PB27_A EQU (AT91C_PIO_PB27) ;-  
AT91C_PB27_PWM2           EQU (AT91C_PIO_PB27) ;-  
AT91C_PIO_PB28            EQU (1 << 28) ;- Pin Controlled by PB28
AT91C_PB28_UNCONNECTED_PB28_A EQU (AT91C_PIO_PB28) ;-  
AT91C_PB28_TCLK0          EQU (AT91C_PIO_PB28) ;-  
AT91C_PIO_PB29            EQU (1 << 29) ;- Pin Controlled by PB29
AT91C_PB29_UNCONNECTED_PB29_A EQU (AT91C_PIO_PB29) ;-  
AT91C_PB29_PWM3           EQU (AT91C_PIO_PB29) ;-  
AT91C_PIO_PB3             EQU (1 <<  3) ;- Pin Controlled by PB3
AT91C_PB3_AC97RX          EQU (AT91C_PIO_PB3) ;-  
AT91C_PB3_RD0             EQU (AT91C_PIO_PB3) ;-  
AT91C_PIO_PB30            EQU (1 << 30) ;- Pin Controlled by PB30
AT91C_PIO_PB31            EQU (1 << 31) ;- Pin Controlled by PB31
AT91C_PIO_PB4             EQU (1 <<  4) ;- Pin Controlled by PB4
AT91C_PB4_TWD             EQU (AT91C_PIO_PB4) ;-  
AT91C_PB4_RK0             EQU (AT91C_PIO_PB4) ;-  
AT91C_PIO_PB5             EQU (1 <<  5) ;- Pin Controlled by PB5
AT91C_PB5_TWCK            EQU (AT91C_PIO_PB5) ;-  
AT91C_PB5_RF0             EQU (AT91C_PIO_PB5) ;-  
AT91C_PIO_PB6             EQU (1 <<  6) ;- Pin Controlled by PB6
AT91C_PB6_TF1             EQU (AT91C_PIO_PB6) ;-  
AT91C_PB6_DMARQ1          EQU (AT91C_PIO_PB6) ;-  
AT91C_PIO_PB7             EQU (1 <<  7) ;- Pin Controlled by PB7
AT91C_PB7_TK1             EQU (AT91C_PIO_PB7) ;-  
AT91C_PB7_PWM0            EQU (AT91C_PIO_PB7) ;-  
AT91C_PIO_PB8             EQU (1 <<  8) ;- Pin Controlled by PB8
AT91C_PB8_TD1             EQU (AT91C_PIO_PB8) ;-  
AT91C_PB8_PWM1            EQU (AT91C_PIO_PB8) ;-  
AT91C_PIO_PB9             EQU (1 <<  9) ;- Pin Controlled by PB9
AT91C_PB9_RD1             EQU (AT91C_PIO_PB9) ;-  
AT91C_PB9_LCDCC           EQU (AT91C_PIO_PB9) ;-  
AT91C_PIO_PC0             EQU (1 <<  0) ;- Pin Controlled by PC0
AT91C_PC0_LCDVSYNC        EQU (AT91C_PIO_PC0) ;-  
AT91C_PIO_PC1             EQU (1 <<  1) ;- Pin Controlled by PC1
AT91C_PC1_LCDHSYNC        EQU (AT91C_PIO_PC1) ;-  
AT91C_PIO_PC10            EQU (1 << 10) ;- Pin Controlled by PC10
AT91C_PC10_LCDD6          EQU (AT91C_PIO_PC10) ;-  
AT91C_PC10_LCDD11B        EQU (AT91C_PIO_PC10) ;-  
AT91C_PIO_PC11            EQU (1 << 11) ;- Pin Controlled by PC11
AT91C_PC11_LCDD7          EQU (AT91C_PIO_PC11) ;-  
AT91C_PC11_LCDD12B        EQU (AT91C_PIO_PC11) ;-  
AT91C_PIO_PC12            EQU (1 << 12) ;- Pin Controlled by PC12
AT91C_PC12_LCDD8          EQU (AT91C_PIO_PC12) ;-  
AT91C_PC12_LCDD13B        EQU (AT91C_PIO_PC12) ;-  
AT91C_PIO_PC13            EQU (1 << 13) ;- Pin Controlled by PC13
AT91C_PC13_LCDD9          EQU (AT91C_PIO_PC13) ;-  
AT91C_PC13_LCDD14B        EQU (AT91C_PIO_PC13) ;-  
AT91C_PIO_PC14            EQU (1 << 14) ;- Pin Controlled by PC14
AT91C_PC14_LCDD10         EQU (AT91C_PIO_PC14) ;-  
AT91C_PC14_LCDD15B        EQU (AT91C_PIO_PC14) ;-  
AT91C_PIO_PC15            EQU (1 << 15) ;- Pin Controlled by PC15
AT91C_PC15_LCDD11         EQU (AT91C_PIO_PC15) ;-  
AT91C_PC15_LCDD19B        EQU (AT91C_PIO_PC15) ;-  
AT91C_PIO_PC16            EQU (1 << 16) ;- Pin Controlled by PC16
AT91C_PC16_LCDD12         EQU (AT91C_PIO_PC16) ;-  
AT91C_PC16_LCDD20B        EQU (AT91C_PIO_PC16) ;-  
AT91C_PIO_PC17            EQU (1 << 17) ;- Pin Controlled by PC17
AT91C_PC17_LCDD13         EQU (AT91C_PIO_PC17) ;-  
AT91C_PC17_LCDD21B        EQU (AT91C_PIO_PC17) ;-  
AT91C_PIO_PC18            EQU (1 << 18) ;- Pin Controlled by PC18
AT91C_PC18_LCDD14         EQU (AT91C_PIO_PC18) ;-  
AT91C_PC18_LCDD22B        EQU (AT91C_PIO_PC18) ;-  
AT91C_PIO_PC19            EQU (1 << 19) ;- Pin Controlled by PC19
AT91C_PC19_LCDD15         EQU (AT91C_PIO_PC19) ;-  
AT91C_PC19_LCDD23B        EQU (AT91C_PIO_PC19) ;-  
AT91C_PIO_PC2             EQU (1 <<  2) ;- Pin Controlled by PC2
AT91C_PC2_LCDDOTCK        EQU (AT91C_PIO_PC2) ;-  
AT91C_PIO_PC20            EQU (1 << 20) ;- Pin Controlled by PC20
AT91C_PC20_LCDD16         EQU (AT91C_PIO_PC20) ;-  
AT91C_PC20_ETX2           EQU (AT91C_PIO_PC20) ;-  
AT91C_PIO_PC21            EQU (1 << 21) ;- Pin Controlled by PC21
AT91C_PC21_LCDD17         EQU (AT91C_PIO_PC21) ;-  
AT91C_PC21_ETX3           EQU (AT91C_PIO_PC21) ;-  
AT91C_PIO_PC22            EQU (1 << 22) ;- Pin Controlled by PC22
AT91C_PC22_LCDD18         EQU (AT91C_PIO_PC22) ;-  
AT91C_PC22_ERX2           EQU (AT91C_PIO_PC22) ;-  
AT91C_PIO_PC23            EQU (1 << 23) ;- Pin Controlled by PC23
AT91C_PC23_LCDD19         EQU (AT91C_PIO_PC23) ;-  
AT91C_PC23_ERX3           EQU (AT91C_PIO_PC23) ;-  
AT91C_PIO_PC24            EQU (1 << 24) ;- Pin Controlled by PC24
AT91C_PC24_LCDD20         EQU (AT91C_PIO_PC24) ;-  
AT91C_PC24_ETXER          EQU (AT91C_PIO_PC24) ;-  
AT91C_PIO_PC25            EQU (1 << 25) ;- Pin Controlled by PC25
AT91C_PC25_LCDD21         EQU (AT91C_PIO_PC25) ;-  
AT91C_PC25_ERXDV          EQU (AT91C_PIO_PC25) ;-  
AT91C_PIO_PC26            EQU (1 << 26) ;- Pin Controlled by PC26
AT91C_PC26_LCDD22         EQU (AT91C_PIO_PC26) ;-  
AT91C_PC26_ECOL           EQU (AT91C_PIO_PC26) ;-  
AT91C_PIO_PC27            EQU (1 << 27) ;- Pin Controlled by PC27
AT91C_PC27_LCDD23         EQU (AT91C_PIO_PC27) ;-  
AT91C_PC27_ERXCK          EQU (AT91C_PIO_PC27) ;-  
AT91C_PIO_PC28            EQU (1 << 28) ;- Pin Controlled by PC28
AT91C_PC28_PWM0           EQU (AT91C_PIO_PC28) ;-  
AT91C_PC28_TCLK1          EQU (AT91C_PIO_PC28) ;-  
AT91C_PIO_PC29            EQU (1 << 29) ;- Pin Controlled by PC29
AT91C_PC29_PCK0           EQU (AT91C_PIO_PC29) ;-  
AT91C_PC29_PWM2           EQU (AT91C_PIO_PC29) ;-  
AT91C_PIO_PC3             EQU (1 <<  3) ;- Pin Controlled by PC3
AT91C_PC3_LCDEN           EQU (AT91C_PIO_PC3) ;-  
AT91C_PC3_PWM1            EQU (AT91C_PIO_PC3) ;-  
AT91C_PIO_PC30            EQU (1 << 30) ;- Pin Controlled by PC30
AT91C_PC30_DRXD           EQU (AT91C_PIO_PC30) ;-  
AT91C_PIO_PC31            EQU (1 << 31) ;- Pin Controlled by PC31
AT91C_PC31_DTXD           EQU (AT91C_PIO_PC31) ;-  
AT91C_PIO_PC4             EQU (1 <<  4) ;- Pin Controlled by PC4
AT91C_PC4_LCDD0           EQU (AT91C_PIO_PC4) ;-  
AT91C_PC4_LCDD3B          EQU (AT91C_PIO_PC4) ;-  
AT91C_PIO_PC5             EQU (1 <<  5) ;- Pin Controlled by PC5
AT91C_PC5_LCDD1           EQU (AT91C_PIO_PC5) ;-  
AT91C_PC5_LCDD4B          EQU (AT91C_PIO_PC5) ;-  
AT91C_PIO_PC6             EQU (1 <<  6) ;- Pin Controlled by PC6
AT91C_PC6_LCDD2           EQU (AT91C_PIO_PC6) ;-  
AT91C_PC6_LCDD5B          EQU (AT91C_PIO_PC6) ;-  
AT91C_PIO_PC7             EQU (1 <<  7) ;- Pin Controlled by PC7
AT91C_PC7_LCDD3           EQU (AT91C_PIO_PC7) ;-  
AT91C_PC7_LCDD6B          EQU (AT91C_PIO_PC7) ;-  
AT91C_PIO_PC8             EQU (1 <<  8) ;- Pin Controlled by PC8
AT91C_PC8_LCDD4           EQU (AT91C_PIO_PC8) ;-  
AT91C_PC8_LCDD7B          EQU (AT91C_PIO_PC8) ;-  
AT91C_PIO_PC9             EQU (1 <<  9) ;- Pin Controlled by PC9
AT91C_PC9_LCDD5           EQU (AT91C_PIO_PC9) ;-  
AT91C_PC9_LCDD10B         EQU (AT91C_PIO_PC9) ;-  
AT91C_PIO_PD0             EQU (1 <<  0) ;- Pin Controlled by PD0
AT91C_PD0_TXD1            EQU (AT91C_PIO_PD0) ;-  
AT91C_PD0_SPI0_NPCS2D     EQU (AT91C_PIO_PD0) ;-  
AT91C_PIO_PD1             EQU (1 <<  1) ;- Pin Controlled by PD1
AT91C_PD1_RXD1            EQU (AT91C_PIO_PD1) ;-  
AT91C_PD1_SPI0_NPCS3D     EQU (AT91C_PIO_PD1) ;-  
AT91C_PIO_PD10            EQU (1 << 10) ;- Pin Controlled by PD10
AT91C_PD10_UNCONNECTED_PD10_A EQU (AT91C_PIO_PD10) ;-  
AT91C_PD10_SCK1           EQU (AT91C_PIO_PD10) ;-  
AT91C_PIO_PD11            EQU (1 << 11) ;- Pin Controlled by PD11
AT91C_PD11_EBI0_NCS2      EQU (AT91C_PIO_PD11) ;-  
AT91C_PD11_TSYNC          EQU (AT91C_PIO_PD11) ;-  
AT91C_PIO_PD12            EQU (1 << 12) ;- Pin Controlled by PD12
AT91C_PD12_EBI0_A23       EQU (AT91C_PIO_PD12) ;-  
AT91C_PD12_TCLK           EQU (AT91C_PIO_PD12) ;-  
AT91C_PIO_PD13            EQU (1 << 13) ;- Pin Controlled by PD13
AT91C_PD13_EBI0_A24       EQU (AT91C_PIO_PD13) ;-  
AT91C_PD13_TPS0           EQU (AT91C_PIO_PD13) ;-  
AT91C_PIO_PD14            EQU (1 << 14) ;- Pin Controlled by PD14
AT91C_PD14_EBI0_A25_CFNRW EQU (AT91C_PIO_PD14) ;-  
AT91C_PD14_TPS1           EQU (AT91C_PIO_PD14) ;-  
AT91C_PIO_PD15            EQU (1 << 15) ;- Pin Controlled by PD15
AT91C_PD15_EBI0_NCS3_NANDCS EQU (AT91C_PIO_PD15) ;-  
AT91C_PD15_TPS2           EQU (AT91C_PIO_PD15) ;-  
AT91C_PIO_PD16            EQU (1 << 16) ;- Pin Controlled by PD16
AT91C_PD16_EBI0_D16       EQU (AT91C_PIO_PD16) ;-  
AT91C_PD16_TPK0           EQU (AT91C_PIO_PD16) ;-  
AT91C_PIO_PD17            EQU (1 << 17) ;- Pin Controlled by PD17
AT91C_PD17_EBI0_D17       EQU (AT91C_PIO_PD17) ;-  
AT91C_PD17_TPK1           EQU (AT91C_PIO_PD17) ;-  
AT91C_PIO_PD18            EQU (1 << 18) ;- Pin Controlled by PD18
AT91C_PD18_EBI0_D18       EQU (AT91C_PIO_PD18) ;-  
AT91C_PD18_TPK2           EQU (AT91C_PIO_PD18) ;-  
AT91C_PIO_PD19            EQU (1 << 19) ;- Pin Controlled by PD19
AT91C_PD19_EBI0_D19       EQU (AT91C_PIO_PD19) ;-  
AT91C_PD19_TPK3           EQU (AT91C_PIO_PD19) ;-  
AT91C_PIO_PD2             EQU (1 <<  2) ;- Pin Controlled by PD2
AT91C_PD2_TXD2            EQU (AT91C_PIO_PD2) ;-  
AT91C_PD2_SPI1_NPCS2D     EQU (AT91C_PIO_PD2) ;-  
AT91C_PIO_PD20            EQU (1 << 20) ;- Pin Controlled by PD20
AT91C_PD20_EBI0_D20       EQU (AT91C_PIO_PD20) ;-  
AT91C_PD20_TPK4           EQU (AT91C_PIO_PD20) ;-  
AT91C_PIO_PD21            EQU (1 << 21) ;- Pin Controlled by PD21
AT91C_PD21_EBI0_D21       EQU (AT91C_PIO_PD21) ;-  
AT91C_PD21_TPK5           EQU (AT91C_PIO_PD21) ;-  
AT91C_PIO_PD22            EQU (1 << 22) ;- Pin Controlled by PD22
AT91C_PD22_EBI0_D22       EQU (AT91C_PIO_PD22) ;-  
AT91C_PD22_TPK6           EQU (AT91C_PIO_PD22) ;-  
AT91C_PIO_PD23            EQU (1 << 23) ;- Pin Controlled by PD23
AT91C_PD23_EBI0_D23       EQU (AT91C_PIO_PD23) ;-  
AT91C_PD23_TPK7           EQU (AT91C_PIO_PD23) ;-  
AT91C_PIO_PD24            EQU (1 << 24) ;- Pin Controlled by PD24
AT91C_PD24_EBI0_D24       EQU (AT91C_PIO_PD24) ;-  
AT91C_PD24_TPK8           EQU (AT91C_PIO_PD24) ;-  
AT91C_PIO_PD25            EQU (1 << 25) ;- Pin Controlled by PD25
AT91C_PD25_EBI0_D25       EQU (AT91C_PIO_PD25) ;-  
AT91C_PD25_TPK9           EQU (AT91C_PIO_PD25) ;-  
AT91C_PIO_PD26            EQU (1 << 26) ;- Pin Controlled by PD26
AT91C_PD26_EBI0_D26       EQU (AT91C_PIO_PD26) ;-  
AT91C_PD26_TPK10          EQU (AT91C_PIO_PD26) ;-  
AT91C_PIO_PD27            EQU (1 << 27) ;- Pin Controlled by PD27
AT91C_PD27_EBI0_D27       EQU (AT91C_PIO_PD27) ;-  
AT91C_PD27_TPK11          EQU (AT91C_PIO_PD27) ;-  
AT91C_PIO_PD28            EQU (1 << 28) ;- Pin Controlled by PD28
AT91C_PD28_EBI0_D28       EQU (AT91C_PIO_PD28) ;-  
AT91C_PD28_TPK12          EQU (AT91C_PIO_PD28) ;-  
AT91C_PIO_PD29            EQU (1 << 29) ;- Pin Controlled by PD29
AT91C_PD29_EBI0_D29       EQU (AT91C_PIO_PD29) ;-  
AT91C_PD29_TPK13          EQU (AT91C_PIO_PD29) ;-  
AT91C_PIO_PD3             EQU (1 <<  3) ;- Pin Controlled by PD3
AT91C_PD3_RXD2            EQU (AT91C_PIO_PD3) ;-  
AT91C_PD3_SPI1_NPCS3D     EQU (AT91C_PIO_PD3) ;-  
AT91C_PIO_PD30            EQU (1 << 30) ;- Pin Controlled by PD30
AT91C_PD30_EBI0_D30       EQU (AT91C_PIO_PD30) ;-  
AT91C_PD30_TPK14          EQU (AT91C_PIO_PD30) ;-  
AT91C_PIO_PD31            EQU (1 << 31) ;- Pin Controlled by PD31
AT91C_PD31_EBI0_D31       EQU (AT91C_PIO_PD31) ;-  
AT91C_PD31_TPK15          EQU (AT91C_PIO_PD31) ;-  
AT91C_PIO_PD4             EQU (1 <<  4) ;- Pin Controlled by PD4
AT91C_PD4_FIQ             EQU (AT91C_PIO_PD4) ;-  
AT91C_PD4_DMARQ2          EQU (AT91C_PIO_PD4) ;-  
AT91C_PIO_PD5             EQU (1 <<  5) ;- Pin Controlled by PD5
AT91C_PD5_EBI0_NWAIT      EQU (AT91C_PIO_PD5) ;-  
AT91C_PD5_RTS2            EQU (AT91C_PIO_PD5) ;-  
AT91C_PIO_PD6             EQU (1 <<  6) ;- Pin Controlled by PD6
AT91C_PD6_EBI0_NCS4_CFCS0 EQU (AT91C_PIO_PD6) ;-  
AT91C_PD6_CTS2            EQU (AT91C_PIO_PD6) ;-  
AT91C_PIO_PD7             EQU (1 <<  7) ;- Pin Controlled by PD7
AT91C_PD7_EBI0_NCS5_CFCS1 EQU (AT91C_PIO_PD7) ;-  
AT91C_PD7_RTS1            EQU (AT91C_PIO_PD7) ;-  
AT91C_PIO_PD8             EQU (1 <<  8) ;- Pin Controlled by PD8
AT91C_PD8_EBI0_CFCE1      EQU (AT91C_PIO_PD8) ;-  
AT91C_PD8_CTS1            EQU (AT91C_PIO_PD8) ;-  
AT91C_PIO_PD9             EQU (1 <<  9) ;- Pin Controlled by PD9
AT91C_PD9_EBI0_CFCE2      EQU (AT91C_PIO_PD9) ;-  
AT91C_PD9_SCK2            EQU (AT91C_PIO_PD9) ;-  
AT91C_PIO_PE0             EQU (1 <<  0) ;- Pin Controlled by PE0
AT91C_PE0_ISI_D0          EQU (AT91C_PIO_PE0) ;-  
AT91C_PIO_PE1             EQU (1 <<  1) ;- Pin Controlled by PE1
AT91C_PE1_ISI_D1          EQU (AT91C_PIO_PE1) ;-  
AT91C_PIO_PE10            EQU (1 << 10) ;- Pin Controlled by PE10
AT91C_PE10_ISI_VSYNC      EQU (AT91C_PIO_PE10) ;-  
AT91C_PE10_PWM3           EQU (AT91C_PIO_PE10) ;-  
AT91C_PIO_PE11            EQU (1 << 11) ;- Pin Controlled by PE11
AT91C_PE11_ISI_MCK        EQU (AT91C_PIO_PE11) ;-  
AT91C_PE11_PCK3           EQU (AT91C_PIO_PE11) ;-  
AT91C_PIO_PE12            EQU (1 << 12) ;- Pin Controlled by PE12
AT91C_PE12_KBDR0          EQU (AT91C_PIO_PE12) ;-  
AT91C_PE12_ISI_D8         EQU (AT91C_PIO_PE12) ;-  
AT91C_PIO_PE13            EQU (1 << 13) ;- Pin Controlled by PE13
AT91C_PE13_KBDR1          EQU (AT91C_PIO_PE13) ;-  
AT91C_PE13_ISI_D9         EQU (AT91C_PIO_PE13) ;-  
AT91C_PIO_PE14            EQU (1 << 14) ;- Pin Controlled by PE14
AT91C_PE14_KBDR2          EQU (AT91C_PIO_PE14) ;-  
AT91C_PE14_ISI_D10        EQU (AT91C_PIO_PE14) ;-  
AT91C_PIO_PE15            EQU (1 << 15) ;- Pin Controlled by PE15
AT91C_PE15_KBDR3          EQU (AT91C_PIO_PE15) ;-  
AT91C_PE15_ISI_D11        EQU (AT91C_PIO_PE15) ;-  
AT91C_PIO_PE16            EQU (1 << 16) ;- Pin Controlled by PE16
AT91C_PE16_KBDR4          EQU (AT91C_PIO_PE16) ;-  
AT91C_PIO_PE17            EQU (1 << 17) ;- Pin Controlled by PE17
AT91C_PE17_KBDC0          EQU (AT91C_PIO_PE17) ;-  
AT91C_PIO_PE18            EQU (1 << 18) ;- Pin Controlled by PE18
AT91C_PE18_KBDC1          EQU (AT91C_PIO_PE18) ;-  
AT91C_PE18_TIOA0          EQU (AT91C_PIO_PE18) ;-  
AT91C_PIO_PE19            EQU (1 << 19) ;- Pin Controlled by PE19
AT91C_PE19_KBDC2          EQU (AT91C_PIO_PE19) ;-  
AT91C_PE19_TIOB0          EQU (AT91C_PIO_PE19) ;-  
AT91C_PIO_PE2             EQU (1 <<  2) ;- Pin Controlled by PE2
AT91C_PE2_ISI_D2          EQU (AT91C_PIO_PE2) ;-  
AT91C_PIO_PE20            EQU (1 << 20) ;- Pin Controlled by PE20
AT91C_PE20_KBDC3          EQU (AT91C_PIO_PE20) ;-  
AT91C_PE20_EBI1_NWAIT     EQU (AT91C_PIO_PE20) ;-  
AT91C_PIO_PE21            EQU (1 << 21) ;- Pin Controlled by PE21
AT91C_PE21_ETXCK          EQU (AT91C_PIO_PE21) ;-  
AT91C_PE21_EBI1_NANDWE    EQU (AT91C_PIO_PE21) ;-  
AT91C_PIO_PE22            EQU (1 << 22) ;- Pin Controlled by PE22
AT91C_PE22_ECRS           EQU (AT91C_PIO_PE22) ;-  
AT91C_PE22_EBI1_NCS2_NANDCS EQU (AT91C_PIO_PE22) ;-  
AT91C_PIO_PE23            EQU (1 << 23) ;- Pin Controlled by PE23
AT91C_PE23_ETX0           EQU (AT91C_PIO_PE23) ;-  
AT91C_PE23_EBI1_NANDOE    EQU (AT91C_PIO_PE23) ;-  
AT91C_PIO_PE24            EQU (1 << 24) ;- Pin Controlled by PE24
AT91C_PE24_ETX1           EQU (AT91C_PIO_PE24) ;-  
AT91C_PE24_EBI1_NWR3_NBS3 EQU (AT91C_PIO_PE24) ;-  
AT91C_PIO_PE25            EQU (1 << 25) ;- Pin Controlled by PE25
AT91C_PE25_ERX0           EQU (AT91C_PIO_PE25) ;-  
AT91C_PE25_EBI1_NCS1_SDCS EQU (AT91C_PIO_PE25) ;-  
AT91C_PIO_PE26            EQU (1 << 26) ;- Pin Controlled by PE26
AT91C_PE26_ERX1           EQU (AT91C_PIO_PE26) ;-  
AT91C_PIO_PE27            EQU (1 << 27) ;- Pin Controlled by PE27
AT91C_PE27_ERXER          EQU (AT91C_PIO_PE27) ;-  
AT91C_PE27_EBI1_SDCKE     EQU (AT91C_PIO_PE27) ;-  
AT91C_PIO_PE28            EQU (1 << 28) ;- Pin Controlled by PE28
AT91C_PE28_ETXEN          EQU (AT91C_PIO_PE28) ;-  
AT91C_PE28_EBI1_RAS       EQU (AT91C_PIO_PE28) ;-  
AT91C_PIO_PE29            EQU (1 << 29) ;- Pin Controlled by PE29
AT91C_PE29_EMDC           EQU (AT91C_PIO_PE29) ;-  
AT91C_PE29_EBI1_CAS       EQU (AT91C_PIO_PE29) ;-  
AT91C_PIO_PE3             EQU (1 <<  3) ;- Pin Controlled by PE3
AT91C_PE3_ISI_D3          EQU (AT91C_PIO_PE3) ;-  
AT91C_PIO_PE30            EQU (1 << 30) ;- Pin Controlled by PE30
AT91C_PE30_EMDIO          EQU (AT91C_PIO_PE30) ;-  
AT91C_PE30_EBI1_SDWE      EQU (AT91C_PIO_PE30) ;-  
AT91C_PIO_PE31            EQU (1 << 31) ;- Pin Controlled by PE31
AT91C_PE31_EF100          EQU (AT91C_PIO_PE31) ;-  
AT91C_PE31_EBI1_SDA10     EQU (AT91C_PIO_PE31) ;-  
AT91C_PIO_PE4             EQU (1 <<  4) ;- Pin Controlled by PE4
AT91C_PE4_ISI_D4          EQU (AT91C_PIO_PE4) ;-  
AT91C_PIO_PE5             EQU (1 <<  5) ;- Pin Controlled by PE5
AT91C_PE5_ISI_D5          EQU (AT91C_PIO_PE5) ;-  
AT91C_PIO_PE6             EQU (1 <<  6) ;- Pin Controlled by PE6
AT91C_PE6_ISI_D6          EQU (AT91C_PIO_PE6) ;-  
AT91C_PIO_PE7             EQU (1 <<  7) ;- Pin Controlled by PE7
AT91C_PE7_ISI_D7          EQU (AT91C_PIO_PE7) ;-  
AT91C_PIO_PE8             EQU (1 <<  8) ;- Pin Controlled by PE8
AT91C_PE8_ISI_PCK         EQU (AT91C_PIO_PE8) ;-  
AT91C_PE8_TIOA1           EQU (AT91C_PIO_PE8) ;-  
AT91C_PIO_PE9             EQU (1 <<  9) ;- Pin Controlled by PE9
AT91C_PE9_ISI_HSYNC       EQU (AT91C_PIO_PE9) ;-  
AT91C_PE9_TIOB1           EQU (AT91C_PIO_PE9) ;-  

// - *****************************************************************************
// -               PERIPHERAL ID DEFINITIONS FOR AT91SAM9263
// - *****************************************************************************
AT91C_ID_FIQ              EQU ( 0) ;- Advanced Interrupt Controller (FIQ)
AT91C_ID_SYS              EQU ( 1) ;- System Controller
AT91C_ID_PIOA             EQU ( 2) ;- Parallel IO Controller A
AT91C_ID_PIOB             EQU ( 3) ;- Parallel IO Controller B
AT91C_ID_PIOCDE           EQU ( 4) ;- Parallel IO Controller C, Parallel IO Controller D, Parallel IO Controller E
AT91C_ID_US0              EQU ( 7) ;- USART 0
AT91C_ID_US1              EQU ( 8) ;- USART 1
AT91C_ID_US2              EQU ( 9) ;- USART 2
AT91C_ID_MCI0             EQU (10) ;- Multimedia Card Interface 0
AT91C_ID_MCI1             EQU (11) ;- Multimedia Card Interface 1
AT91C_ID_CAN              EQU (12) ;- CAN Controller
AT91C_ID_TWI              EQU (13) ;- Two-Wire Interface
AT91C_ID_SPI0             EQU (14) ;- Serial Peripheral Interface 0
AT91C_ID_SPI1             EQU (15) ;- Serial Peripheral Interface 1
AT91C_ID_SSC0             EQU (16) ;- Serial Synchronous Controller 0
AT91C_ID_SSC1             EQU (17) ;- Serial Synchronous Controller 1
AT91C_ID_AC97C            EQU (18) ;- AC97 Controller
AT91C_ID_TC012            EQU (19) ;- Timer Counter 0, Timer Counter 1, Timer Counter 2
AT91C_ID_PWMC             EQU (20) ;- PWM Controller
AT91C_ID_EMAC             EQU (21) ;- Ethernet Mac
AT91C_ID_UDP              EQU (24) ;- USB Device Port
AT91C_ID_HISI             EQU (25) ;- Image Sensor Interface
AT91C_ID_LCDC             EQU (26) ;- LCD Controller
AT91C_ID_DMA              EQU (27) ;- DMA Controller
AT91C_ID_UHP              EQU (29) ;- USB Host Port
AT91C_ID_IRQ0             EQU (30) ;- Advanced Interrupt Controller (IRQ0)
AT91C_ID_IRQ1             EQU (31) ;- Advanced Interrupt Controller (IRQ1)
AT91C_ALL_INT             EQU (0xEF3FFF9F) ;- ALL VALID INTERRUPTS

// - *****************************************************************************
// -               BASE ADDRESS DEFINITIONS FOR AT91SAM9263
// - *****************************************************************************
AT91C_BASE_SYS            EQU (0xFFFFE000) ;- (SYS) Base Address
AT91C_BASE_EBI0           EQU (0xFFFFE200) ;- (EBI0) Base Address
AT91C_BASE_SDRAMC0        EQU (0xFFFFE200) ;- (SDRAMC0) Base Address
AT91C_BASE_SMC0           EQU (0xFFFFE400) ;- (SMC0) Base Address
AT91C_BASE_EBI1           EQU (0xFFFFE800) ;- (EBI1) Base Address
AT91C_BASE_SDRAMC1        EQU (0xFFFFE800) ;- (SDRAMC1) Base Address
AT91C_BASE_SMC1           EQU (0xFFFFEA00) ;- (SMC1) Base Address
AT91C_BASE_MATRIX         EQU (0xFFFFEC00) ;- (MATRIX) Base Address
AT91C_BASE_CCFG           EQU (0xFFFFED10) ;- (CCFG) Base Address
AT91C_BASE_PDC_DBGU       EQU (0xFFFFEF00) ;- (PDC_DBGU) Base Address
AT91C_BASE_DBGU           EQU (0xFFFFEE00) ;- (DBGU) Base Address
AT91C_BASE_AIC            EQU (0xFFFFF000) ;- (AIC) Base Address
AT91C_BASE_PIOA           EQU (0xFFFFF200) ;- (PIOA) Base Address
AT91C_BASE_PIOB           EQU (0xFFFFF400) ;- (PIOB) Base Address
AT91C_BASE_PIOC           EQU (0xFFFFF600) ;- (PIOC) Base Address
AT91C_BASE_PIOD           EQU (0xFFFFF800) ;- (PIOD) Base Address
AT91C_BASE_PIOE           EQU (0xFFFFFA00) ;- (PIOE) Base Address
AT91C_BASE_CKGR           EQU (0xFFFFFC20) ;- (CKGR) Base Address
AT91C_BASE_PMC            EQU (0xFFFFFC00) ;- (PMC) Base Address
AT91C_BASE_RSTC           EQU (0xFFFFFD00) ;- (RSTC) Base Address
AT91C_BASE_SHDWC          EQU (0xFFFFFD10) ;- (SHDWC) Base Address
AT91C_BASE_RTTC0          EQU (0xFFFFFD20) ;- (RTTC0) Base Address
AT91C_BASE_RTTC1          EQU (0xFFFFFD50) ;- (RTTC1) Base Address
AT91C_BASE_PITC           EQU (0xFFFFFD30) ;- (PITC) Base Address
AT91C_BASE_WDTC           EQU (0xFFFFFD40) ;- (WDTC) Base Address
AT91C_BASE_TC0            EQU (0xFFF7C000) ;- (TC0) Base Address
AT91C_BASE_TC1            EQU (0xFFF7C040) ;- (TC1) Base Address
AT91C_BASE_TC2            EQU (0xFFF7C080) ;- (TC2) Base Address
AT91C_BASE_TCB0           EQU (0xFFF7C000) ;- (TCB0) Base Address
AT91C_BASE_TCB1           EQU (0xFFF7C040) ;- (TCB1) Base Address
AT91C_BASE_TCB2           EQU (0xFFF7C080) ;- (TCB2) Base Address
AT91C_BASE_PDC_MCI0       EQU (0xFFF80100) ;- (PDC_MCI0) Base Address
AT91C_BASE_MCI0           EQU (0xFFF80000) ;- (MCI0) Base Address
AT91C_BASE_PDC_MCI1       EQU (0xFFF84100) ;- (PDC_MCI1) Base Address
AT91C_BASE_MCI1           EQU (0xFFF84000) ;- (MCI1) Base Address
AT91C_BASE_TWI            EQU (0xFFF88000) ;- (TWI) Base Address
AT91C_BASE_PDC_US0        EQU (0xFFF8C100) ;- (PDC_US0) Base Address
AT91C_BASE_US0            EQU (0xFFF8C000) ;- (US0) Base Address
AT91C_BASE_PDC_US1        EQU (0xFFF90100) ;- (PDC_US1) Base Address
AT91C_BASE_US1            EQU (0xFFF90000) ;- (US1) Base Address
AT91C_BASE_PDC_US2        EQU (0xFFF94100) ;- (PDC_US2) Base Address
AT91C_BASE_US2            EQU (0xFFF94000) ;- (US2) Base Address
AT91C_BASE_PDC_SSC0       EQU (0xFFF98100) ;- (PDC_SSC0) Base Address
AT91C_BASE_SSC0           EQU (0xFFF98000) ;- (SSC0) Base Address
AT91C_BASE_PDC_SSC1       EQU (0xFFF9C100) ;- (PDC_SSC1) Base Address
AT91C_BASE_SSC1           EQU (0xFFF9C000) ;- (SSC1) Base Address
AT91C_BASE_PDC_AC97C      EQU (0xFFFA0100) ;- (PDC_AC97C) Base Address
AT91C_BASE_AC97C          EQU (0xFFFA0000) ;- (AC97C) Base Address
AT91C_BASE_PDC_SPI0       EQU (0xFFFA4100) ;- (PDC_SPI0) Base Address
AT91C_BASE_SPI0           EQU (0xFFFA4000) ;- (SPI0) Base Address
AT91C_BASE_PDC_SPI1       EQU (0xFFFA8100) ;- (PDC_SPI1) Base Address
AT91C_BASE_SPI1           EQU (0xFFFA8000) ;- (SPI1) Base Address
AT91C_BASE_CAN_MB0        EQU (0xFFFAC200) ;- (CAN_MB0) Base Address
AT91C_BASE_CAN_MB1        EQU (0xFFFAC220) ;- (CAN_MB1) Base Address
AT91C_BASE_CAN_MB2        EQU (0xFFFAC240) ;- (CAN_MB2) Base Address
AT91C_BASE_CAN_MB3        EQU (0xFFFAC260) ;- (CAN_MB3) Base Address
AT91C_BASE_CAN_MB4        EQU (0xFFFAC280) ;- (CAN_MB4) Base Address
AT91C_BASE_CAN_MB5        EQU (0xFFFAC2A0) ;- (CAN_MB5) Base Address
AT91C_BASE_CAN_MB6        EQU (0xFFFAC2C0) ;- (CAN_MB6) Base Address
AT91C_BASE_CAN_MB7        EQU (0xFFFAC2E0) ;- (CAN_MB7) Base Address
AT91C_BASE_CAN_MB8        EQU (0xFFFAC300) ;- (CAN_MB8) Base Address
AT91C_BASE_CAN_MB9        EQU (0xFFFAC320) ;- (CAN_MB9) Base Address
AT91C_BASE_CAN_MB10       EQU (0xFFFAC340) ;- (CAN_MB10) Base Address
AT91C_BASE_CAN_MB11       EQU (0xFFFAC360) ;- (CAN_MB11) Base Address
AT91C_BASE_CAN_MB12       EQU (0xFFFAC380) ;- (CAN_MB12) Base Address
AT91C_BASE_CAN_MB13       EQU (0xFFFAC3A0) ;- (CAN_MB13) Base Address
AT91C_BASE_CAN_MB14       EQU (0xFFFAC3C0) ;- (CAN_MB14) Base Address
AT91C_BASE_CAN_MB15       EQU (0xFFFAC3E0) ;- (CAN_MB15) Base Address
AT91C_BASE_CAN            EQU (0xFFFAC000) ;- (CAN) Base Address
AT91C_BASE_PWMC_CH0       EQU (0xFFFB8200) ;- (PWMC_CH0) Base Address
AT91C_BASE_PWMC_CH1       EQU (0xFFFB8220) ;- (PWMC_CH1) Base Address
AT91C_BASE_PWMC_CH2       EQU (0xFFFB8240) ;- (PWMC_CH2) Base Address
AT91C_BASE_PWMC_CH3       EQU (0xFFFB8260) ;- (PWMC_CH3) Base Address
AT91C_BASE_PWMC           EQU (0xFFFB8000) ;- (PWMC) Base Address
AT91C_BASE_MACB           EQU (0xFFFBC000) ;- (MACB) Base Address
AT91C_BASE_LCDC           EQU (0x00700000) ;- (LCDC) Base Address
AT91C_BASE_DMA            EQU (0x00800000) ;- (DMA) Base Address
AT91C_BASE_UDP            EQU (0xFFF78000) ;- (UDP) Base Address
AT91C_BASE_UHP            EQU (0x00A00000) ;- (UHP) Base Address
AT91C_BASE_TBOX           EQU (0x70000000) ;- (TBOX) Base Address
AT91C_BASE_HECC0          EQU (0xFFFFE000) ;- (HECC0) Base Address
AT91C_BASE_HECC1          EQU (0xFFFFE600) ;- (HECC1) Base Address
AT91C_BASE_HISI           EQU (0xFFFC4000) ;- (HISI) Base Address

// - *****************************************************************************
// -               MEMORY MAPPING DEFINITIONS FOR AT91SAM9263
// - *****************************************************************************
// - ITCM
AT91C_ITCM                EQU (0x00100000) ;- Maximum ITCM Area base address
AT91C_ITCM_SIZE           EQU (0x00010000) ;- Maximum ITCM Area size in byte (64 Kbytes)
// - DTCM
AT91C_DTCM                EQU (0x00200000) ;- Maximum DTCM Area base address
AT91C_DTCM_SIZE           EQU (0x00010000) ;- Maximum DTCM Area size in byte (64 Kbytes)
// - IRAM
AT91C_IRAM                EQU (0x00300000) ;- Maximum Internal SRAM base address
AT91C_IRAM_SIZE           EQU (0x00014000) ;- Maximum Internal SRAM size in byte (80 Kbytes)
// - IRAM_MIN
AT91C_IRAM_MIN            EQU (0x00300000) ;- Minimum Internal RAM base address
AT91C_IRAM_MIN_SIZE       EQU (0x00004000) ;- Minimum Internal RAM size in byte (16 Kbytes)
// - IROM
AT91C_IROM                EQU (0x00400000) ;- Internal ROM base address
AT91C_IROM_SIZE           EQU (0x00020000) ;- Internal ROM size in byte (128 Kbytes)
// - IRAM2
AT91C_IRAM2               EQU (0x00500000) ;- IRAM2 base address
AT91C_IRAM2_SIZE          EQU (0x00004000) ;- IRAM2 size in byte (16 Kbytes)
// - EBI0_CS0
AT91C_EBI0_CS0            EQU (0x10000000) ;- EBI0 Chip Select 0 base address
AT91C_EBI0_CS0_SIZE       EQU (0x10000000) ;- EBI0 Chip Select 0 size in byte (262144 Kbytes)
// - EBI0_CS1
AT91C_EBI0_CS1            EQU (0x20000000) ;- EBI0 Chip Select 1 base address
AT91C_EBI0_CS1_SIZE       EQU (0x10000000) ;- EBI0 Chip Select 1 size in byte (262144 Kbytes)
// - EBI0_SDRAM
AT91C_EBI0_SDRAM          EQU (0x20000000) ;- SDRAM on EBI0 Chip Select 1 base address
AT91C_EBI0_SDRAM_SIZE     EQU (0x10000000) ;- SDRAM on EBI0 Chip Select 1 size in byte (262144 Kbytes)
// - EBI0_SDRAM_16BIT
AT91C_EBI0_SDRAM_16BIT    EQU (0x20000000) ;- SDRAM on EBI0 Chip Select 1 base address
AT91C_EBI0_SDRAM_16BIT_SIZE EQU (0x02000000) ;- SDRAM on EBI0 Chip Select 1 size in byte (32768 Kbytes)
// - EBI0_SDRAM_32BIT
AT91C_EBI0_SDRAM_32BIT    EQU (0x20000000) ;- SDRAM on EBI0 Chip Select 1 base address
AT91C_EBI0_SDRAM_32BIT_SIZE EQU (0x04000000) ;- SDRAM on EBI0 Chip Select 1 size in byte (65536 Kbytes)
// - EBI0_CS2
AT91C_EBI0_CS2            EQU (0x30000000) ;- EBI0 Chip Select 2 base address
AT91C_EBI0_CS2_SIZE       EQU (0x10000000) ;- EBI0 Chip Select 2 size in byte (262144 Kbytes)
// - EBI0_CS3
AT91C_EBI0_CS3            EQU (0x40000000) ;- EBI0 Chip Select 3 base address
AT91C_EBI0_CS3_SIZE       EQU (0x10000000) ;- EBI0 Chip Select 3 size in byte (262144 Kbytes)
// - EBI0_SM
AT91C_EBI0_SM             EQU (0x40000000) ;- SmartMedia on EBI0 Chip Select 3 base address
AT91C_EBI0_SM_SIZE        EQU (0x10000000) ;- SmartMedia on EBI0 Chip Select 3 size in byte (262144 Kbytes)
// - EBI0_CS4
AT91C_EBI0_CS4            EQU (0x50000000) ;- EBI0 Chip Select 4 base address
AT91C_EBI0_CS4_SIZE       EQU (0x10000000) ;- EBI0 Chip Select 4 size in byte (262144 Kbytes)
// - EBI0_CF0
AT91C_EBI0_CF0            EQU (0x50000000) ;- CompactFlash 0 on EBI0 Chip Select 4 base address
AT91C_EBI0_CF0_SIZE       EQU (0x10000000) ;- CompactFlash 0 on EBI0 Chip Select 4 size in byte (262144 Kbytes)
// - EBI0_CS5
AT91C_EBI0_CS5            EQU (0x60000000) ;- EBI0 Chip Select 5 base address
AT91C_EBI0_CS5_SIZE       EQU (0x10000000) ;- EBI0 Chip Select 5 size in byte (262144 Kbytes)
// - EBI0_CF1
AT91C_EBI0_CF1            EQU (0x60000000) ;- CompactFlash 1 on EBI0Chip Select 5 base address
AT91C_EBI0_CF1_SIZE       EQU (0x10000000) ;- CompactFlash 1 on EBI0Chip Select 5 size in byte (262144 Kbytes)
// - EBI1_CS0
AT91C_EBI1_CS0            EQU (0x70000000) ;- EBI1 Chip Select 0 base address
AT91C_EBI1_CS0_SIZE       EQU (0x10000000) ;- EBI1 Chip Select 0 size in byte (262144 Kbytes)
// - EBI1_CS1
AT91C_EBI1_CS1            EQU (0x80000000) ;- EBI1 Chip Select 1 base address
AT91C_EBI1_CS1_SIZE       EQU (0x10000000) ;- EBI1 Chip Select 1 size in byte (262144 Kbytes)
// - EBI1_SDRAM_16BIT
AT91C_EBI1_SDRAM_16BIT    EQU (0x80000000) ;- SDRAM on EBI1 Chip Select 1 base address
AT91C_EBI1_SDRAM_16BIT_SIZE EQU (0x02000000) ;- SDRAM on EBI1 Chip Select 1 size in byte (32768 Kbytes)
// - EBI1_SDRAM_32BIT
AT91C_EBI1_SDRAM_32BIT    EQU (0x80000000) ;- SDRAM on EBI1 Chip Select 1 base address
AT91C_EBI1_SDRAM_32BIT_SIZE EQU (0x04000000) ;- SDRAM on EBI1 Chip Select 1 size in byte (65536 Kbytes)
// - EBI1_CS2
AT91C_EBI1_CS2            EQU (0x90000000) ;- EBI1 Chip Select 2 base address
AT91C_EBI1_CS2_SIZE       EQU (0x10000000) ;- EBI1 Chip Select 2 size in byte (262144 Kbytes)
// - EBI1_SM
AT91C_EBI1_SM             EQU (0x90000000) ;- SmartMedia on EBI1 Chip Select 2 base address
AT91C_EBI1_SM_SIZE        EQU (0x10000000) ;- SmartMedia on EBI1 Chip Select 2 size in byte (262144 Kbytes)
#endif /* __IAR_SYSTEMS_ASM__ */


#endif /* AT91SAM9263_H */
