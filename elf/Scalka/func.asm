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

//        defadr  GBS_WaitForMsg,0xA00925C4
//        defadr  RegisterCepidForSocketWork,0xA09915E5
//        defadr  RequestLMANConnect,0xA09926F5
//        defadr  RefreshGUI,0xA097851D
//        defadr  EDIT_SetFocus,0xA0A118D9

	END
	