#include "..\MySMSYS_ipc.h"

	EXTERN	send_ipc
	EXTERN	inbox_view
	RSEG	MY_SMS_SYS_PBODY

	CODE32
/* -r1173
SMS_SENT_CODE
	//ADD	LR, LR, #4
	MOV	R0, #SMSYS_IPC_OUT
	B	send_ipc

SMS_INBOX_CODE
	//ADD	LR, LR, #4
	MOV	R0, #SMSYS_IPC_IN_ALL
	B	send_ipc
*/
/*
ROM:A0806AD4 3D 30               ADD     R0, #0x3D
ROM:A0806AD6 00 59               LDR     R0, [R0,R4]
ROM:A0806AD8 01 28               CMP     R0, #1
ROM:A0806ADA 03 D1               BNE     loc_A0806AE4
ROM:A0806ADC 80 20               MOV     R0, #0x80
*/
AB_UPDATE_CODE
	ADD	LR, LR, #4
	ADD	R0, R0, #0x3D
	LDR	R0, [R4, R0]
	CMP	R0, #1
	BXEQ	LR
	ADD	LR, LR, #8
	STMFD	SP!,{R0-R7, LR}
	MOV	R0, #SMSYS_IPC_UPDATE_CLIST
	BL	send_ipc
	LDMFD	SP!,{R0-R7, PC}
	
	EXTERN	OpmsgIDSend
INBOX_VIEW_CODE
#ifdef ELC1v41
	ADD	LR, LR, #4
	LDR	R2, [SP,#0x174]
	LDR	R3, [SP,#0x178]
	LDR	R0, [R6,#0xC]
	LDR	R1, [R6,#0x10]	
#else
	ADD	LR, LR, #6
	//LDR	R2, [SP, #0x178]
	LDR	R3, [SP, #0x178]
	LDR	R0, [R6, #0xC]
	LDR	R1, [R6, #0x10] //r1, opmsg_id
	CMP	R0, #0x4
	CMPNE	R2, #0x4
	BEQ	INBOX_V1
#ifdef E71Cv41
#define IBVIEW_ADR	0xA051A4C7
#endif
#ifdef E71v45
#define IBVIEW_ADR	0xA0504D67 //B430B5C7B006A9
#endif
	LDR	R12, =IBVIEW_ADR
	BX	R12

#endif
INBOX_V
	CMP	R0, #0x4
	CMPNE	R2, #0x4
	BXNE	LR
	ADD	LR, LR, #4
INBOX_V1
	STMFD	SP!,{R1-R7, LR}
	MOV	R0, #SMSYS_IPC_VIEW_OPMSG
	BL	OpmsgIDSend
	LDMFD	SP!,{R1-R7, PC}

INBOX_OPVIEW_CODE
#ifdef ELC1v41
	ADD	LR, LR, #6
	ADD	R0, R0, #0x80
	LDR	R2, [SP,#0x170]
	LDR	R3, [SP,#0x174]
#else
	ADD	LR, LR, #4
	LDR	R2, [SP,#0x16C]
	LDR	R3, [SP,#0x170]
#endif
	LDR	R1, [R0,#0x10]
	LDR	R0, [R0,#0xC]
	B	INBOX_V


INBOX_OTH_CODE
	ADD	LR, LR, #4
	LDR	R0, [R0, #4]
	LDR	R0, [R0, #0]
	LDRB	R2, [R4, R2]
	MOV	R1, R0 //opmsg_id
	CMP	R2, #0xC
	MOVEQ	R0, #SMSYS_IPC_REPLY_OPMSG
	BEQ	OPMSG_SEND
	CMP	R2, #0xE
	MOVEQ	R0, #SMSYS_IPC_QR_OPMSG
	BEQ	OPMSG_SEND
	CMP	R2, #0x12
	BXNE	LR
	MOV	R0, #SMSYS_IPC_QN_OPMSG
OPMSG_SEND
	ADD	LR, LR, #0x1EC  //A05277F0-A0527604
	STMFD	SP!,{R1-R7, LR}
	BL	OpmsgIDSend
	LDMFD	SP!,{R1-R7, PC}

	EXTERN	getFileCount //CMP     R7, #0
COUNT_IN_CODE //R0, [SP,#0x80] ; NEW SMS
	ADD	LR, LR, #4
	ADD	R1, SP, #0x68
	ADD	R0, SP, #0x54
	LDR	R7, [SP,#0x98]
	MOV	R2, #6
	STMFD	SP!,{R0-R6, LR}
	LDR	R1, [SP, #0xA0]
	SWI	0x82B1 //SMS_DATA_ROOT *SmsDataRoot();
	MOV	R2, R0
	CMP	R1, #0
	BNE	COUNT_READ
	LDRH	R0, [R0, #0x1E]
	STR	R0, [SP, #0xA0]
COUNT_READ
	MOV	R0, #5 //TYPE_IN_ALL 	5
	MOV	R1, R7
	BLX	getFileCount
	ADD	R7, R7, R0
	LDMFD	SP!,{R0-R6, PC}
/*
ROM:A0345B48 02 1C                       ADD     R2, R0, #0
ROM:A0345B4A 23 1C                       ADD     R3, R4, #0
ROM:A0345B4C 28 1C                       ADD     R0, R5, #0
ROM:A0345B4E 60 A1                       ADR     R1, s_DD_1      ; "%d/%d"*/
MMENU_INBOX_CNT_CODE
	ADD	LR, LR, #4
	STMFD	SP!, {LR}
	MOV	R7, R0 //CNT NEW OLD
	SWI	0x82B1
	MOV	R2, R0
	CMP	R7, #0
	BNE	CNT_IN_ALL
	LDRH	R7, [R2, #0x1E]
CNT_IN_ALL
	MOV	R0, #5 //TYPE_IN_ALL 	5
	MOV	R1, R4
	BLX	getFileCount
	ADD	R3, R4, R0
	MOV	R2, R7
	MOV	R0, R5
	MOV	R1, #0x7F
	ORR	R1, R1, #0x100
	LDMFD	SP!, {LR}
	ADD	R1, R1, LR
	BX	LR

	EXTERN	getOtherCount
OTHER_COUNT_CODE
	ADD	LR, LR, #4
	MOV	R5, R3
	MOV	R2, #6
	ADD	R1, SP, #0x18
	ADD	R0, SP, #4
	CMP	R6, #2 //DRAFT
	MOVEQ	R3, #4 //TYPE_DRAFT	4
	BEQ	GO
	CMPNE	R6, #3 //SENT
	MOVEQ	R3, #1 //TYPE_OUT	1
	BXNE	LR
GO
	STMFD	SP!, {R0-R4,R6,R7, LR}
       	SWI	0x82B1 //SMS_DATA_ROOT *SmsDataRoot();
	MOV	R2, R0
	MOV	R0, R3
        MOV	R1, R5
	BLX	getFileCount
	ADD	R5, R5, R0
	LDMFD	SP!, {R0-R4,R6,R7, PC}

/*
ROM:A0345BB0 28 1C                       ADD     R0, R5, #0
ROM:A0345BB2 4E A1                       ADR     R1, s_D_16      ; "%d"
ROM:A0345BB4 DC F0 78 EC                 BLX     sub_A04224A8    ; void wsprintf(WSHDR *,const char *format,...)
*/
MMENU_DRAFT_CNT_CODE
	ADD	LR, LR, #4
	STMFD	SP!,{LR}
	MOV	R7, R2
	SWI	0x82B1
	MOV	R2, R0
	MOV	R0, #4
	MOV	R1, R7
	BLX	getFileCount
	ADD	R2, R7, R0
	MOV	R0, R5
	MOV	R1, #0x33
	ORR	R1, R1, #0x100
	LDR	LR, [SP, #0]
	ADD	R1, R1, LR
	SWI	0xA0
	LDMFD	SP!,{PC}

MMENU_SENT_CNT_CODE
	ADD	LR, LR, #6
	STMFD	SP!,{LR}
	MOV	R7, R1
	SWI	0x82B1
	MOV	R2, R0
	MOV	R0, #1
	MOV	R1, R4
	BLX	getFileCount
	ADD	R2, R4, R0
	SUB 	R1, R7, #0x30
	MOV	R0, R5
	SWI	0xA0
	LDMFD	SP!,{PC}
	
NEW_IN_WIN_CODE
	ADD	LR, LR, #4
	LSL	R6, R6, #0x1F
	MOV	R5, R0
	MOV	R7, #0
	MOV	R0, R4
	LDR	R3, [R0, #0x10]
	ASR	R3, R3, #0x10
	LSL	R3, R3, #0x18
	LSR	R3, R3, #0x18
	CMP	R3, #0x20
	BXNE	LR
	//A0302A80-A03029F4
	ADD	LR, LR, #0x8C
	STMFD	SP!,{LR}
	MOV	R0, #SMSYS_IPC_NEW_IN_WIN
	BL	send_ipc
	MOV	R0, #0
	LDMFD	SP!,{PC}
/*-r1173
NMENU_INBOX_CODE
	MOV	R0, #SMSYS_IPC_IN_ALL
	B	send_ipc
	
NMENU_DRAFT_CODE
	MOV	R0, #SMSYS_IPC_DRAFT
	B	send_ipc
	
NMENU_SENT_CODE
	MOV	R0, #SMSYS_IPC_OUT
	B	send_ipc
	
SHORTCUT_NEWMSG_CODE
	//ADD	LR, LR, #4
	MOV	R0, #SMSYS_IPC_NEWSMS
	B	send_ipc
	
NMENU_NEWSMG_CODE
	MOV	R0, #SMSYS_IPC_NEWSMS
	B	send_ipc
*/
/*
ROM:A07815A0 6B 44               ADD     R3, SP
ROM:A07815A2 09 90               STR     R0, [SP,#0x24]
ROM:A07815A4 18 69               LDR     R0, [R3,#0x10]
ROM:A07815A6 00 28               CMP     R0, #0
ROM:A07815A8 01 D0               BEQ     loc_A07815AE
ROM:A07815AA E5 A0               ADR     R0, s_OpwvmsgCcom_9     ; "opwvmsg:CComposeSMS"
ROM:A07815AC 00 E0               B       loc_A07815B0

*/	
	EXTERN	CreateSmsWithNum_2
	EXTERN	CreateSmsWithNum_3
	EXTERN	CreateSmsWithNum
ADRBK_NUM_SMS_CODE
	ADD	LR, LR, #0xA
	ADD	R3, SP, R3
	STR	R0, [SP,#0x24]
	LDR	R0, [R3,#0x10]
	CMP	R0, #0
	BXEQ	LR
	ADD	LR, LR, #0x8
	LDR	R0, [SP, #0x10]
	STMFD	SP!,{R1-R7, LR}
	BL	CreateSmsWithNum_3
	LDMFD	SP!,{R1-R7, PC}
	/*-r1173
SHORTCUT_DRAFT_CODE
	//ADD	LR, LR, #4
	MOV	R0, #SMSYS_IPC_DRAFT
	B	send_ipc
	*/
	EXTERN	OrgSendText
ORG_SEND_CODE
	ADD	LR, LR, #6
	MOV	R0, R5
	B	OrgSendText



REC_SENDSMS_CODE
	ADD	LR, LR, #4
	STR	R7, [SP, #0x14]
	MOV	R3, SP
	STRB	R7, [R3, #0x18]
	LDR	R0, [R6, #8]
	CMP	R0, #0x17
	BXNE	LR
	ADD	LR, LR, #0x16
	STMFD	SP!, {R1-R7, LR}
	MOV	R0, R5
	BL	CreateSmsWithNum_2
	LDMFD	SP!, {R1-R7, PC}

DIAL_SMS_CODE
	ADD	LR, LR, #4
	STMFD	SP!,{R1-R7, LR}
	LDR	R0, [R4, #0]
	BL	CreateSmsWithNum_2
	LDMFD	SP!,{R1-R7, PC}
	
INBOX_REC_CODE
	ADD	LR, LR, #0xA2
	LDRB	R0, [R0,#8]
	CMP	R0, #0x16
	BXNE	LR
	LDR	R0, [SP, #0x54]
	ADD	LR, LR, #0x8
	STMFD	SP!, {R1-R7, LR}
	BL	CreateSmsWithNum_2
	LDMFD	SP!, {R1-R7, PC}
        
//r-1173        
SHORTCUT_SAVED_CODE
	//ADD	LR, LR, #4
NMENU_ARCHIVE_CODE
	MOV	R0, #SMSYS_IPC_ARCHIVE
	B	send_ipc
	

SMS_SENT_CODE
	//ADD	LR, LR, #4
NMENU_SENT_CODE
	MOV	R0, #SMSYS_IPC_OUT
	B	send_ipc

//	MOV	R0, #SMSYS_IPC_OUT
//	B	send_ipc
SMS_INBOX_CODE
	//ADD	LR, LR, #4
NMENU_INBOX_CODE
	MOV	R0, #SMSYS_IPC_IN_ALL
	B	send_ipc
	
//	MOV	R0, #SMSYS_IPC_IN_ALL
//	B	send_ipc
	
SHORTCUT_DRAFT_CODE
	//ADD	LR, LR, #4
NMENU_DRAFT_CODE
	MOV	R0, #SMSYS_IPC_DRAFT
	B	send_ipc
//	MOV	R0, #SMSYS_IPC_DRAFT
//	B	send_ipc
	
	
SHORTCUT_NEWMSG_CODE
	//ADD	LR, LR, #4
NMENU_NEWSMG_CODE
	MOV	R0, #SMSYS_IPC_NEWSMS
	B	send_ipc
	
//	MOV	R0, #SMSYS_IPC_NEWSMS
//	B	send_ipc

//-r1173
	
	RSEG	SMS_SENT_HOOK
	CODE16
	LDR	R0, =SMS_SENT_CODE
	BX	R0
	
	RSEG	SMS_INBOX_HOOK
	CODE16
	LDR	R0, =SMS_INBOX_CODE
	BX	R0
	
	RSEG	AB_UPDATE_HOOK
	CODE16
	LDR	R1, =AB_UPDATE_CODE
	BLX	R1
	
#ifdef ELC1v41     
        RSEG	INBOX_VIEW_HOOK
	CODE16
	LDR	R0, =INBOX_VIEW_CODE
	BLX	R0
#else
        RSEG	INBOX_VIEW_HOOK
	CODE16
	LDR	R0, pINBOX_VIEW_CODE
	BLX	R0
	DATA
pINBOX_VIEW_CODE
	DCD	INBOX_VIEW_CODE
	CODE16
        NOP
#endif
	
	RSEG	COUNT_IN_HOOK
	CODE16
	LDR	R7, =COUNT_IN_CODE
	BLX	R7
	
	RSEG	OTHER_COUNT_HOOK
	CODE16
	LDR	R2, =OTHER_COUNT_CODE
	BLX	R2


	RSEG	NEW_IN_WIN_HOOK
	CODE16
	LDR	R5, =NEW_IN_WIN_CODE
	BLX	R5
	
	RSEG	NMENU_INBOX_HOOK
	CODE16
	LDR	R0, =NMENU_INBOX_CODE
	BX	R0
	
	RSEG	NMENU_DRAFT_HOOK
	CODE16
	LDR	R0, =NMENU_DRAFT_CODE
	BX	R0
	
	RSEG	NMENU_SENT_HOOK
	CODE16
	LDR	R0, =NMENU_SENT_CODE
	BX	R0
	
	RSEG	SHORTCUT_NEWMSG_HOOK
	CODE16
	LDR	R0, =SHORTCUT_NEWMSG_CODE
	BX	R0
	
	RSEG	NMENU_NEWSMG_HOOK
	CODE16
	LDR	R0, =NMENU_NEWSMG_CODE
	BX	R0
	
	RSEG	ADRBK_NUM_SMS_HOOK
	CODE16
	LDR	R1, =ADRBK_NUM_SMS_CODE
	BLX	R1
	
	RSEG	SHORTCUT_DRAFT_HOOK
	CODE16
	LDR	R0, =SHORTCUT_DRAFT_CODE
	BX	R0
	
	RSEG	ORG_SEND_HOOK
	CODE16
	LDR	R0, =ORG_SEND_CODE
	BLX	R0
	
	RSEG	REC_SENDSMS_HOOK
        CODE16
	LDR	R3, =REC_SENDSMS_CODE
	BLX	R3
	
	RSEG	INBOX_OPVIEW_HOOK
        CODE16
	LDR	R2, =INBOX_OPVIEW_CODE
	BLX	R2
	
	RSEG	INBOX_OTH_HOOK
        CODE16
	LDR	R3, =INBOX_OTH_CODE
	BLX	R3
	
	RSEG	DIAL_SMS_HOOK
        CODE16
	LDR	R0, =DIAL_SMS_CODE
	BLX	R0
	
	RSEG	INBOX_REC_HOOK
        CODE16
	LDR	R1, =INBOX_REC_CODE
	BLX	R1
	
	RSEG	SHORTCUT_SAVED_HOOK
	CODE16
	LDR	R0, =SHORTCUT_SAVED_CODE
	BLX	R0
	
	RSEG	NMENU_ARCHIVE_HOOK
	CODE16
	LDR	R0, =NMENU_ARCHIVE_CODE
	BX	R0
	
	RSEG	MMENU_INBOX_CNT_HOOK
	CODE16
	LDR	R2, =MMENU_INBOX_CNT_CODE
	BLX	R2
	
	RSEG	MMENU_DRAFT_CNT_HOOK
	CODE16
	LDR	R0, =MMENU_DRAFT_CNT_CODE
	BLX	R0
	
	RSEG	MMENU_SENT_CNT_HOOK
	CODE16
	LDR	R0, pMMENU_SENT_CNT_CODE
	BLX	R0
	DATA
pMMENU_SENT_CNT_CODE
	DCD	MMENU_SENT_CNT_CODE
	CODE16
	NOP
	END