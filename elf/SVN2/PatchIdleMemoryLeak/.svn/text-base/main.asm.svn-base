
#define S75sw47

        NAME    main

	RSEG	ICODE:CODE(2)
	CODE32
main:
	MOV	R0,R4
#ifdef	S75sw47
	BLX	0xA04EAA0C+1
#else
	BLX	0xA04EAFF8+1
#endif
	MOV	R0,R4
	BL	0xA0094948	; mfree
	MOV	R0,R5
	LDMFD   SP!,{R1-R7,PC}

	RSEG	PATCH:CODE(2)
	CODE16
	LDR	R0,=main
	BX	R0

#ifdef S75sw40

	RSEG	PATCH_CLOSE_IDLE_GUI:CODE(1)
	CODE16
	NOP
#endif
	
	END
	
	


