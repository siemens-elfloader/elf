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
	DCD	0xA0320AF4+1
	
	PUBLIC	OldOnCreate
OldOnCreate:
	DCD	0xA03208EA+1
        
	PUBLIC	ESIOld
ESIOld:
	DCD	0xA0715A7A+1
        
        PUBLIC	PITgetN
PITgetN:
	DCD	0xA07F7002+1
	
	PUBLIC	PITret
PITret:
	DCD	0xA07F7018+1
        
        PUBLIC	KEYBret
KEYBret:
	DCD	0xA087172A+1  
        
        PUBLIC	KEYBfunc
KEYBfunc:
	DCD	0xA07FBCFC+1          
        
	PUBLIC	FReadOld
FReadOld:
	DCD	0xA0990C58
        
        PUBLIC	FWriteOld
FWriteOld:
	DCD	0xA0990D40       
        
        defadr	StoreErrInfoAndAbort,0xA0991790 //F0 4D 2D E9 00 40 A0 E1 90 02 9F E5 00 80 A0 E3
	defadr	StoreErrString,0xA09915B4 //0A 10 A0 E3 E9 FF FF EA 10 40 2D E9 F4 10 A0 E3

	END