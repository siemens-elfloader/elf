
#ifdef NEWSGOLD

	RSEG	OWM_FOLDER_ICON_HOOK
	CODE16
	LDR	R0, =OWM_FOLDER_ICON_
	BLX	R0
	
	EXTERN	doFolderIconChange
	RSEG	OWM_FOLDER_ICON_BODY

	CODE16
OWM_FOLDER_ICON_
	PUSH	{R0-R7, LR}
	SUB	SP, #0x80
	MOV	R0, R6
	MOV	R1, R4
	ADD	R1, #0x10 //int *icon
	LDR	R2, [R4, #0x4]
	MOV	R3, SP
	BL	doFolderIconChange //R0, void *, R1, *ICON, R2, int index, r3,CHAR *PATH
	MOV	R1, R4
	MOV	R0, R6
	LDR	R7, =0xA0363F48+1
	BLX	R7
	ADD	SP, #0x80
	POP	{R0-R7}
	POP	{R1}
	ADD	R1, #4
	BX	R1
	
	
#endif

#ifdef ELKA
	RSEG	OWM_FOLDER_ICON_HOOK
	CODE32
	BLX	OWM_FOLDER_ICON_
	
	EXTERN	doFolderIconChange
	RSEG	OWM_FOLDER_ICON_BODY

	CODE16
OWM_FOLDER_ICON_
	PUSH	{R1-R7, LR}
	SUB	SP, #0x80
	LDR	R1, =0x409 //icon1
	LDR	R0, [R4 ,#0x14] //ICON
	CMP	R1, R0
	BEQ	PGO
	ADD	R1, #0x1B //icon2
	CMP	R1, R0
	BNE	PEXIT	
PGO
	MOV	R0, R6
	MOV	R1, R4
	ADD	R1, #0x14 //int *icon ELKA
	LDR	R2, [R4, #0x4]
	MOV	R3, SP
	BLX	doFolderIconChange //R0, void *, R1, *ICON, R2, int index, r3,CHAR *PATH
PEXIT
	MOV	R0, R6
	ADD	SP, #0x80
	POP	{R1-R7, PC}
#endif

	END