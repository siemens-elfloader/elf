      RSEG CODE:CODE
      CODE32

	
      PUBLIC lddrr ; R3 to, R1 from, R2 size
lddrr
      PUSH {R3-R4,LR}
      MOV R3,R0   
lddrr1
      LDRB R4,[R1],#-1
      STRB R4,[R3],#-1
      SUBS R2,R2,#1
      BNE lddrr1
      POP {R3-R4,PC}

      PUBLIC ldirr ; R3 to, R1 from, R2 size
ldirr
      PUSH {R3-R4,LR}
      MOV R3,R0   
ldirr1
      LDRB R4,[R1],#1
      STRB R4,[R3],#1
      SUBS R2,R2,#1
      BNE ldirr1
      POP {R3-R4,PC}

 
        END
