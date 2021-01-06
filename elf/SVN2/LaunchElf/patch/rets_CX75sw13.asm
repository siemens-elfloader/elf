	RSEG	CODE:DATA:ROOT(2)
        
defadr	MACRO	a,b
	PUBLIC	a
a	EQU	b
	ENDM
        
        
        PUBLIC	OldTable
OldTable:
	DCD	0xA04B09D4
        
        PUBLIC	OldFRTable
OldFRTable:
	DCD	0xA04A6448
        
        defadr	OldShCutCheck,0xA02B74CC+1

	END