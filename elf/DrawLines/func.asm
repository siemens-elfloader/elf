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
        PUBLIC GetAccessoryType
GetAccessoryType:
 swi 0x80d0
 ldr r0,[r0]
 ldr r0,[r0,#4]
 bx lr



;
defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

;        defadr  GBS_WaitForMsg,0xA00925C4
;        defadr  RegisterCepidForSocketWork,0xA09915E5
;        defadr  RequestLMANConnect,0xA09926F5
;	defadr	PrepareEditControl,0xA0A0B3F4+1
;	defadr	AllocEQueue,0xA0A0BFB6+1
;	defadr	ConstructEditControl,0xA0A0B704+1
;	defadr	AddEditControlToEditQend,0xA0A0C152+1
;	defadr	CreateInputTextDialog,0xA0A08D7C+1
;	defadr	SetSoftKey,0xA0A1205A+1
;	defadr	ExtractEditControl,0xA0A11FF0+1
;	defadr	StoreEditControl,0xA0A11FFC+1
;	defadr	unlink,0xA02510B8

	END