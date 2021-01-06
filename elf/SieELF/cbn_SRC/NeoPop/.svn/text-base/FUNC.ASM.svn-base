      RSEG CODE:CODE
      CODE32
      
      PUBLIC OADD64 ;r0+r1
OADD64: ADDS R0,R0,R1
      MOVVS R0,#1
      MOVVC R0,#0
      BX LR

      PUBLIC OSUB64 ;r0-r1
OSUB64: SUBS R0,R0,R1
      MOVVS R0,#1
      MOVVC R0,#0
      BX LR


      PUBLIC rgb444to565 ;R0 Buf, R1 size
rgb444to565: 
      PUSH {R2-R4,LR}
      LSR R1,R1,#1
rgb1
      LDRH R2,[R0]
      ;// *s++=((*ss&0xf)<<12)|((*ss&0xf0)<<3)|((*ss&0xf00)>>7);
      AND R3,R2,#0xf
      LSL R3,R3,#12
      AND R4,R2,#0xf0
      LSL R4,R4,#3
      ORR  R3,R3,R4
      AND R4,R2,#0xf00
      LSR R4,R4,#7
      ORR R3,R3,R4
      STRH R3,[R0],#2
     
      SUBS R1,R1,#1
      BNE rgb1
      POP {R2-R4,PC}

	END
	
