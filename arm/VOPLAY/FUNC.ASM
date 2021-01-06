	PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN

	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1
        PUBLIC  seqkill
seqkill
        BX      R3
/*
        PUBLIC GetAccessoryType      // Чтоб на сголд работало   AAA
GetAccessoryType:
        SWI     0x80D0
        LDR     R0,R0,#8]
        CMP     R0, #0
        BX      LR
        LDRB    R0,R0,#4]
        BX      LR
*/

;
defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM
	END
