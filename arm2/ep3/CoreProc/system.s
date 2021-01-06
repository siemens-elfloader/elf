

                        .global  UnLockAllAccess
                        .global  LockAllAccess
                        .global  EnableInterrupts
                        .global  DisableInterrupts

                        .arm

      UnLockAllAccess:

 	                     STR	  LR, [SP, #-0x04]!
	                     MRS	  R2,  CPSR

                         SWI      0x81B5
                         CMP      R0, #0x00
	                     SWIEQ    0x00
                         SWINE    0x04

	                     MRS      R1, CPSR
	                     ORR      R1, R1,#0xC0
	                     MSR      CPSR_c, R1

                         MOV      R0, #0xFFFFFFFF
                         MCR      p15, 0, R0, c3, c0

                         NOP
	                     NOP
	                     NOP
	                     NOP
                         NOP
	                     NOP
                         NOP
	                     NOP
	                     NOP
	                     NOP
                         NOP
	                     NOP


	                     MSR	  CPSR_c,R2
	                     LDR	  PC,[SP], #+0x04



         LockAllAccess:

 	                     STR	  LR, [SP, #-0x04]!
	                     MRS	  R2,  CPSR

                         SWI      0x81B5
                         CMP      R0, #0x00
	                     SWIEQ    0x00
                         SWINE    0x04

	                     MRS      R1, CPSR
	                     ORR      R1, R1,#0xC0
	                     MSR      CPSR_c, R1

                         MOV      R0, #0x00000001
                         MCR      p15, 0, R0, c3, c0

                         NOP
	                     NOP
	                     NOP
	                     NOP
                         NOP
	                     NOP
                         NOP
	                     NOP
	                     NOP
	                     NOP
                         NOP
	                     NOP


	                     MSR	     CPSR_c,R2
	                     LDR	     PC,[SP], #+0x04



       EnableInterrupts:

                         PUSH   {R1-R2, LR}

                         MRS     R1, CPSR
                         BIC     R1, R1, #0xC0

                         SWI     0x81B5
                         CMP     R0, #0x00
	                     SWIEQ   0x00
                         SWINE   0x04

                         MSR     CPSR_c, R1
                         POP    {R1-R2, PC}


      DisableInterrupts:

                         PUSH   {R1-R2, LR}

                         MRS     R0, CPSR
                         ORR     R1, R0, #0xC0

                         SWI     0x81B5
                         CMP     R0, #0x00
	                     SWIEQ   0x00
                         SWINE   0x04

                         MSR     CPSR_c, R1

                         POP    {R1-R2, PC}






