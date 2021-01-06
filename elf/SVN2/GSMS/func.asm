	PUBLIC	ELF_BEGIN
	RSEG	ELFBEGIN:DATA
ELF_BEGIN

	RSEG	CODE:CODE
	PUBLIC	kill_data
	CODE32
kill_data
	BX	R1


defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

	defadr	gethostbyname,0xA0A4ACA6+1
	defadr	async_gethostbyname,0xA0A4AA20+1
	defadr	str2ip,0xA099B364+1
//        defadr  GBS_WaitForMsg,0xA00925C4
//        defadr  RegisterCepidForSocketWork,0xA09915E5
//        defadr  RequestLMANConnect,0xA09926F5

	END
	