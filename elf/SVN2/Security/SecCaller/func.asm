	PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN


	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1
	
	PUBLIC call_sec
call_sec
	PUSH {R1,LR}
	MOV R0,#0
	LDR R1,=0xA006E400+1
	BLX R1
	;BX LR
	POP {R1,PC}

	END
	