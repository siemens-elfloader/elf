
#ifndef	NEW

	EXTERN	AddTheName
	CODE16
	RSEG	HOOK
	LDR	R2, =CODE_
	BLX	R2


	CODE16
	RSEG	CODE
#ifdef NEWSGOLD
CODE_
	STR	R0, [SP,#4] //LGP
	LDR	R1, [SP,#8] //WS
	PUSH	{R0-R7, LR}
	MOV	R6, R0
	MOV	R7, R1
	SWI	0x89
	LDR	R5, =0xAC5
	CMP	R6, R5
	BNE	exit
	MOV	R0, R7
	BLX	AddTheName
#else //SGOLD by DaiKangaroo
CODE_
#ifdef CX7Csw50//�ر���,hookλ�ñ�������������2���ֽڣ��Դﵽ4�ֽڶ���
        //ԭ��Hookλ�ô���
	//MOV R1, R5
        //MOV R0, R4
        //BLX Sub ��������:ADD R0, #0x80  STR R1, [R0, #4]
        //����Ϊ
        MOV     R0, R4
        ADD 	R0, #0x80
	STR 	R5, [R0, #4]
#else
        //ԭ��Hookλ�ô���
	//MOV R0, R4
        //BLX Sub ��������:ADD R0, #0x80  STR R1, [R0, #4]
        //MOV R1, R6
        //����Ϊ
	MOV	R0, R4
	ADD 	R0, #0x80
	STR 	R1, [R0, #4]
        MOV     R1, R6	
#endif
	PUSH	{R0-R7, LR}
	LDR	R2, =0x272 //�յ��µ���ϢLGP
#ifdef CX7Csw50 //�ر���[SP,#0xC]���LGP_ID
        LDR     R7,[SP,#0xC]
#endif        
	CMP	R7, R2
	BNE	exit
	MOV	R0, R5 //WS
	BLX	AddTheName
#endif
exit
	POP	{R0-R7}
	POP	{R0}
	ADD	R0, R0, #4
	BX	R0
#endif

#ifdef	NEW
	RSEG	HOOK_NEW
	CODE16
	LDR	R0, =CODE_NEW
	BLX	R0
	
	RSEG	CODE
	DATA
PERCENT_T
	DCD	"%t"
PSTR_NORMAL
	DCD	"����Ϣ!\n����:\n"
PSTR_REPORT
	DCD	"״̬����!\n����:\n"
	
	CODE16
CODE_NEW

	EXTERN	GetNumFromIncomingPDU
	EXTERN	AddTheName_N
	PUSH	{R0-R7, LR}
	SUB	SP, #0x28
	MOV	R0, #0
	STR	R0, [SP, #0x24] //����Ĭ��Ϊ0
	STR	R0, [SP, #0x20] //����Ĭ��Ϊ0
	LDR	R7, =0xAC5
	MOV	R6, R2
	CMP	R2, R7 //�Ƚ�LGP
	BNE	PRINTWS
	MOV	R0, SP
	MOV	R1, R0
	ADD	R1, #0x20
	BL	GetNumFromIncomingPDU
	CMP	R0, #0
	BEQ	PRINTWS
	STR	R0, [SP, #0x24] //�洢��־
	LDR	R0, [SP, #0x20]
	CMP	R0, #0
	BNE	PSTR_RE
	LDR	R5, =PSTR_NORMAL
	B	PRINTWS
PSTR_RE
	LDR	R5, =PSTR_REPORT
PRINTWS
	MOV	R2, R6
	LDR	R1, =PERCENT_T
	MOV	R0, R4
	SWI	0xA0 //;  A0: wsprintf(WSHDR *,const char *format,...)
	LDR	R2, [SP, #0x24]
	CMP	R2, #0
	BEQ	EXPBACK
	MOV	R0, R4
	MOV	R1, SP
	MOV	R3, R5
	BLX	AddTheName_N
EXPBACK
	ADD	SP, #0x28
	POP	{R0-R7}
	POP	{R3}
	ADD	R3, #4
	BX	R3
#endif
	END