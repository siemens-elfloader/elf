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

//	defadr	XSendSMS,0xA0534491
//	defadr	CreateMultiLinesMenu,0xA0613E7C+1
//	defadr	SetMLMenuItemText,0xA0980366+1
//	defadr	AllocMLMenuItem,0xA09806A6+1

	END
	