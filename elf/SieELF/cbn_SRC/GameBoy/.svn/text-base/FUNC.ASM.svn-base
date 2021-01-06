      RSEG CODE:CODE
      CODE32

      PUBLIC  refresh_2 ;(un16 *dest, byte *src, un16 *pal, int cnt) //refresh_2!!!
      ;//while (cnt--) *(dest++) = pal[*(src++)];
refresh_2
      PUSH {R4-R5,LR}
refrgo 
      LDRB R5,[R1],#1
      ADD R4,R2,R5, LSL #1
      LDRH R4,[R4]
      STRH R4,[R0],#2
      SUBS R3,R3,#1
      BNE refrgo
      POP {R4-R5,PC}


      PUBLIC redraw ;R0 TO, R1 FROM  ;, R2 FLAG, R4=I, R5=J, R6=K
redraw      
      PUSH {R2-R4,LR}
      MOV R4,#144  
red1      
      MOV R3,#66
red2
      LDR R2,[R1],#4
      STR R2,[R0],#4
      SUBS R3,R3,#1
      BNE  red2
      ADD R1,R1,#56
      SUBS R4,R4,#1
      BNE red1
      POP {R2-R4,PC}


      PUBLIC redraw2 ;R0 S TO, R1 B FROM  ;, R2 FLAG, R4=I, R5=J, R6=K
redraw2      
      PUSH {R3-R5,LR}
      
      MOV R5,#144
LAB1
      MOV R4,#26
LAB2      
      LDRH R3,[R1],#2
      STRH R3,[R0],#2

      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      
      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      
      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      
      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      
      ADD R1,R1,#2
      SUBS R4,R4,#1
      BNE LAB2
      
      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      
      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      
      ADD R1,R1,#4
      SUBS R5,R5,#1
      BNE LAB1
     
      POP {R3-R5,PC}


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

     
      PUBLIC redraw5 ;R0 TO, R1 FROM  ;//for EL
redraw5
      PUSH {R2-R4,LR}
      MOV R4,#144  
red51
      MOV R3,#80
red52
      LDR R2,[R1],#4
      STR R2,[R0],#4
      SUBS R3,R3,#1
      BNE  red52
      ADD R0,R0,#160
      SUBS R4,R4,#1
      BNE red51
      POP {R2-R4,PC}


      PUBLIC redraw6 ;R0 S TO, R1 B FROM  ; //EL double size
redraw6
      PUSH {R2-R5,LR}
      MOV R5,#144
red61
      MOV R2,#1 ;double flag
red62
      MOV R4,#80
red63     
      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      STRH R3,[R0],#2
      
      LDRH R3,[R1],#2
      STRH R3,[R0],#2
      
      SUBS R4,R4,#1
      BNE red63
      
      SUBS R2,R2,#1
      SUBEQ R1,R1,#320
      BEQ red62
      
      SUBS R5,R5,#1
      BNE red61
     
      POP {R2-R5,PC}


      PUBLIC redraw3 ;R0 S TO, R1 B FROM  ; //поворот 176
redraw3
      PUSH {R2-R5,LR}
      MOV R2,R0
      MOV R5,#132
red31
      MOV R4,#160
      SUB R2,R2,#2
      MOV R0,R2
red32 
      ADD R0,R0,#264
      LDRH R3,[R1],#2
      STRH R3,[R0]

      SUBS R4,R4,#1
      BNE red32
      
      SUBS R5,R5,#1
      BNE red31
     
      POP {R2-R5,PC}

   END