	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1

  
  
        PUBLIC  myf ; r0 - x0, r1 - j 
myf
        push  {r1-r2, lr}
        sub   r1, r1, r0
        asr   r1, r1, r2
        add   r0, r0, r1        
        pop   {r1-r2, pc}
        
        
        PUBLIC  cpyscr  ; r0 - src, r1 - dst;;;r3 - i, r4 - j        
cpyscr
        push   {r1-r5, lr}
        mov   r3, #0      
cpyscr1
        mov   r4, #0
cpyscr2
        ldrsh  r5, [r0],#2
        strh  r5, [r1],#2
        
        add   r4, r4, #1
        cmp   r4, #132
        bne   cpyscr2
        
        add   r3, r3, #1
        cmp   r3, #176
        bne   cpyscr1
        
        pop   {r1-r5, pc}

        
        PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA        

ELF_BEGIN



 
 
	END
	