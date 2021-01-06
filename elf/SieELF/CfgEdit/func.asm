	PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN


defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1
        

	END
	