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



;
defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

        defadr wap_browser, 0xA032D89F
        defadr my_stuff, 0xA032DFBB
        defadr develop, 0xA1BC0805
;        defadr  GBS_WaitForMsg,0xA00925C4
;        defadr  RegisterCepidForSocketWork,0xA09915E5
;        defadr  RequestLMANConnect,0xA09926F5

	END
	