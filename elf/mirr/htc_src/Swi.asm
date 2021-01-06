      RSEG CODE:CODE
      PUBLIC kill_data
      CODE32
kill_data
      BX R1
        PUBLIC  seqkill
seqkill
        BX      R3

      PUBLIC ?call_ctors ; ?????
?call_ctors
      BX LR ;R1?

      PUBLIC strlen ;R1 s, R2 temp
strlen
      PUSH {R1-R2,LR} 
      MOV R1,R0
      MVN R0,#0  ;MOV R0,#-1
strlen1
      ADD R0,R0,#1
      LDRB R2,[R1],#1
      CMP R2,#0
      BNE strlen1
      POP {R1-R2,PC}
      ;BX LR

      PUBLIC strchr ;R0 s, R1 chr
strchr
      PUSH {R2,LR} 
      AND R1,R1,#0xFF
      MOV R2,#0
strchr1
      LDRB R2,[R0],#1
      CMP R2,R1
      BEQ strchr2
      CMP R2,#0
      BNE strchr1
      MOV R0,#1
strchr2
      SUB R0,R0,#1
      POP {R2,PC}

      PUBLIC strrchr ;R2 s, R1 chr
strrchr
      PUSH {R2-R3,LR} 
      AND R1,R1,#0xFF
      MOV R3,#0
      MOV R2,R0
strrchr1
      LDRB R3,[R0],#1
      CMP R3,#0
      BNE strrchr1
strrchr2
      LDRB R3,[R0,#-1]!
      CMP R3,R1
      BEQ strrchr3
      CMP R0,R2
      BHI strrchr2
      MOV R0,#0
strrchr3      
      POP {R2-R3,PC}


      PUBLIC strcpy ; R2 to, R1 from
strcpy
      PUSH {R2-R3,LR}
      MOV R2,R0
strcpy1
      LDRB R3,[R1],#1
      STRB R3,[R2],#1
      CMP R3,#0
      BNE strcpy1
      POP {R2-R3,PC}

      PUBLIC strcat ; R2 to, R1 from
strcat
      PUSH {R2-R3,LR}
      MOV R2,R0
strcat1
      LDRB R3,[R2],#1
      CMP R3,#0
      BNE strcat1
      SUB R2,R2,#1
strcat2      
      LDRB R3,[R1],#1
      STRB R3,[R2],#1
      CMP R3,#0
      BNE strcat2
      POP {R2-R3,PC}

      PUBLIC memcmp ; R3 mem2, R1 mem1, R2 size
memcmp
      PUSH {R3-R4,LR}
      CMP R2,#0
      MOVEQ R0,#0
      BEQ memcmp2
      MOV R3,R0      
memcmp1
      LDRB R0,[R1],#1
      LDRB R4,[R3],#1
      SUBS R0,R0,R4
      BNE memcmp2
      SUBS R2,R2,#1
      BNE memcmp1
memcmp2:      
      POP {R3-R4,PC}

      PUBLIC strcmp ; R3 mem2, R1 mem1
strcmp
      PUSH {R2-R3,LR}
      MOV R3,R0      
strcmp1
      LDRB R0,[R1],#1
      LDRB R2,[R3],#1
      SUBS R0,R0,R2
      BNE strcmp2
      CMP R2,#0
      BNE strcmp1
strcmp2:      
      POP {R2-R3,PC}

      PUBLIC stricmp ; R3 mem2, R1 mem1
stricmp
      PUSH {R2-R3,LR}
      MOV R3,R0      
stricmp1
      LDRB R0,[R1],#1
      LDRB R2,[R3],#1
      ORR R0,R0,#32
      ORR R2,R2,#32
      SUBS R0,R0,R2
      BNE stricmp2
      CMP R2,#0
      BNE stricmp1
stricmp2:      
      POP {R2-R3,PC}

      PUBLIC strncmp ; R3 mem2, R1 mem1
strncmp
      PUSH {R3-R4,LR}
      MOV R3,R0      
      MOV R0,#0
      CMP R2,#0
      BEQ strncmp2
strncmp1
      LDRB R0,[R1],#1
      LDRB R4,[R3],#1
      SUBS R0,R0,R4
      BNE strncmp2
      SUBS R2,R2,#1
      BNE strncmp1
strncmp2:      
      POP {R3-R4,PC}

      PUBLIC strnicmp ; R3 mem2, R1 mem1
strnicmp
      PUSH {R3-R4,LR}
      MOV R3,R0      
      MOV R0,#0
      CMP R2,#0
      BEQ strnicmp2
strnicmp1
      LDRB R0,[R1],#1
      LDRB R4,[R3],#1
      ORR R0,R0,#32
      ORR R4,R4,#32
      SUBS R0,R0,R4
      BNE strnicmp2
      SUBS R2,R2,#1
      BNE strnicmp1
strnicmp2:      
      POP {R3-R4,PC}

      PUBLIC memcpy ; R3 to, R1 from, R2 size MODIFY!!!
memcpy
      PUSH {R3-R5,LR}
      MOV R3,R0      
      ;cmp fast 4b
      ANDS R4,R1,#3
      ANDSEQ R4,R3,#3
      BNE memcpy2
      MOVS R5,R2,LSR #2
      BEQ memcpy2
memcpy1
      LDR R4,[R1],#4
      STR R4,[R3],#4
      SUBS R5,R5,#1
      BNE memcpy1
      AND R2,R2,#3
memcpy2
      CMP R2,#0
      BEQ memcpy3
      LDRB R4,[R1],#1
      STRB R4,[R3],#1
      SUBS R2,R2,#1
      BNE memcpy2
memcpy3:      
      POP {R3-R5,PC}

      PUBLIC movsw ; R3 to, R1 from, R2 size
movsw
      PUSH {R3-R4,LR}
      MOV R3,R0   
movsw1
      LDRH R4,[R1],#2
      STRH R4,[R3],#2
      SUBS R2,R2,#1
      BNE movsw1
      POP {R3-R4,PC}

      PUBLIC movsd ; R3 to, R1 from, R2 size
movsd
      PUSH {R3-R4,LR}
      MOV R3,R0   
movsd1
      LDR R4,[R1],#4
      STR R4,[R3],#4
      SUBS R2,R2,#1
      BNE movsd1
      POP {R3-R4,PC}

      PUBLIC memset ; R3 to, R1 value, R2 size //!!!
memset
      PUSH {R3-R5,LR}
      MOV R3,R0
      ;cmp fast 4b
      ANDS R4,R3,#3
      BNE memset2
      MOVS R4,R2,LSR #2
      BEQ memset2
      ANDS R1,R1,#0xFF
      BEQ memset1
      MOV R5,R1,LSL #8
      ORR R1,R1,R5
      MOV R5,R1,LSL #16
      ORR R1,R1,R5
memset1
      STR R1,[R3],#4
      SUBS R4,R4,#1
      BNE memset1
      AND R2,R2,#3
memset2
      CMP R2,#0
      BEQ memset3
memset21
      STRB R1,[R3],#1
      SUBS R2,R2,#1
      BNE memset21
memset3:      
      POP {R3-R5,PC}


      PUBLIC memsetw ; R3 to, R1 value, R2 size
memsetw
      PUSH {R3,LR}
      CMP R2,#0
      BEQ memsetw2
      MOV R3,R0
memsetw1
      STRH R1,[R3],#2
      SUBS R2,R2,#1
      BNE memsetw1
memsetw2
      POP {R3,PC}

      PUBLIC memsetd ; R3 to, R1 value, R2 size
memsetd
      PUSH {R3,LR}
      CMP R2,#0
      BEQ memsetd2
      MOV R3,R0
memsetd1
      STR R1,[R3],#4
      SUBS R2,R2,#1
      BNE memsetd1
memsetd2
      POP {R3,PC}


      PUBLIC memmov ; R3 to, R1 from, R2 size //инверсия
memmov
      PUSH {R3-R4,LR}
      CMP R2,#0
      BEQ memcpyrev2
      ADD R3,R0,R2
      ADD R1,R1,R2
memcpyrev1
      LDRB R4,[R1,#-1]!
      STRB R4,[R3,#-1]!
      SUBS R2,R2,#1
      BNE memcpyrev1
memcpyrev2
      POP {R3-R4,PC}


       PUBLIC iszero ; R0 = page, R1 = size
iszero
        PUSH {R1-R2,LR}
        MOV R2,R0
isnull1       
        LDR R0,[R2],#4
        CMP R0,#0
        BNE isnull2
        SUBS R1,R1,#1
        BNE isnull1
isnull2 
        POP {R1-R2,PC}


        PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN

	END
	
