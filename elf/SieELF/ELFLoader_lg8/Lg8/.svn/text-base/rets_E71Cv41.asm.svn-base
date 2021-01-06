	RSEG	DATA_N
	RSEG	SWILIB_FUNC1B8_1BB:CODE
	EXTERN	EXT2_AREA
	EXTERN	pngtop
	EXTERN	pLIB_TOP
	DCD	EXT2_AREA
	DCD	pngtop
	DCD	pLIB_TOP
	DCD	SFE(DATA_N)

defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM

        RSEG	CODE:CODE
	PUBLIC	OldOnClose
OldOnClose:
	DCD	0xA0685A00+1  //?? B5 04 1C ???????? ????20 1C FF 30 09 30
	
	PUBLIC	OldOnCreate
OldOnCreate:
	DCD	0xA06857C0+1 // F0 B5 F1 4D ???????? 04 1C FF 30
	
	PUBLIC	OldShowMsg
OldShowMsg:
	DCD	0xA0974FBA+1 //86 4A E0 32 C3 07 00

	PUBLIC	PITgetN
PITgetN:
	DCD	0xA0A5D454  //54 00 9F E5 1E FF 2F E1 10
	
	PUBLIC	PITret
PITret:
	DCD	0xA0973824+1 //01 D9 20 1C 11 E0 D9 49 
	
	defadr	StoreErrInfoAndAbort,0xA04E23A4 //38 40 2D E9 D0 44 9F E5 
	defadr	StoreErrString,0xA04E2270 //0A 10 A0 E3 E9 FF FF EA 
	
	END        