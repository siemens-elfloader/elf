      RSEG CODE:CODE
      CODE32

      PUBLIC redraw ;R0 TO, R1 FROM, ;R2=176, R3=264, R4=?
redraw      
      PUSH {R2-R4,LR}
      MOV R2,#176
LAB1
      MOV R3,#66
LAB2
      LDR R4,[R1],#4
      STR R4,[R0],#4
      SUBS R3,R3,#1
      BNE LAB2
      
      ADD R1,R1,#248
      SUBS R2,R2,#1
      BNE LAB1

      POP {R2-R4,PC}
      ;BX LR

      PUBLIC redraw2 ;R0 TO, R1 FROM, ;R2=176, R3=264, R4=? ;со сжатием
redraw2      
      PUSH {R2-R4,LR}
      MOV R2,#176
LAB21
      MOV R3,#26
LAB22
      LDRH R4,[R1],#2
      STRH R4,[R0],#2
      LDRH R4,[R1],#2
      STRH R4,[R0],#2
      LDRH R4,[R1],#2
      STRH R4,[R0],#2
      LDRH R4,[R1],#2
      STRH R4,[R0],#2
      LDRH R4,[R1],#4
      STRH R4,[R0],#2
            
      SUBS R3,R3,#1
      BNE LAB22
      
      ADD R0,R0,#4
      ADD R1,R1,#200
      SUBS R2,R2,#1
      BNE LAB21

      POP {R2-R4,PC}
      ;BX LR


      PUBLIC rotate ;R0 Buf, R1 size
rotate
      PUSH {R2-R4,LR}
      ADD R2,R0,R1
      LSR R1,R1,#2 ;3
rot1
      LDRH R3,[R0]
      LDRH R4,[R2,#-2]!
      STRH R4,[R0],#2
      STRH R3,[R2]
     
      SUBS R1,R1,#1
      BNE rot1
      POP {R2-R4,PC}


      PUBLIC redraw3 ;R0 TO, R1 FROM, ;R2=176, R3=264, R4=? ;поворот
redraw3
      PUSH {R2-R5,LR}
      MOV R2,#132
LAB31
      MOV R3,#176
      MOV R5,R0
LAB32
      LDRH R4,[R1],#2
      STRH R4,[R0],#8
      ADD R0,R0,#256

      SUBS R3,R3,#1
      BNE LAB32
      
      ADD R1,R1,#160
      SUB R0,R5,#2

      SUBS R2,R2,#1
      BNE LAB31
      POP {R2-R5,PC}


      PUBLIC redraw4 ;R0 TO, R1 FROM, ;R2=176, R3=264, R4=? ;for EL71
redraw4
      PUSH {R2-R5,LR}
      MOV R2,#145
LAB41
      MOV R5,#2
LAB42
      MOV R3,#80
LAB43
      LDR R4,[R1],#4
      STR R4,[R0],#4
      SUBS R3,R3,#1
      BNE LAB43

      SUBS R5,R5,#1
      ADD R0,R0,#160
      SUBNE R1,R1,#320
      BNE LAB42
      
      ADD R1,R1,#192
      SUBS R2,R2,#1
      BNE LAB41
      POP {R2-R5,PC}


      PUBLIC redraw5 ;R0 TO, R1 FROM, ;R2=176, R3=264, R4=? ;for EL71 крупно
redraw5
      PUSH {R2-R6,LR}
      MOV R2,#145
LAB51
      MOV R5,#2
LAB52
      MOV R3,#160
LAB53
      LDRH R4,[R1],#2
      STRH R4,[R0],#2
      ORRS R6,R3,#1
      STRHNE R4,[R0],#2
      SUBS R3,R3,#1
      BNE LAB53

      SUBS R5,R5,#1
      ;ADD R0,R0,#160
      SUBNE R1,R1,#320
      BNE LAB52
      
      ADD R1,R1,#192
      SUBS R2,R2,#1
      BNE LAB51
      POP {R2-R6,PC}



  END

