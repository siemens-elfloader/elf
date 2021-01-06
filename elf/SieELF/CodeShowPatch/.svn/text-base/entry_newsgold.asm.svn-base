#include "addr.h"

	EXTERN	AppendInfoW
	EXTERN	UpdateLocaleToItem
	EXTERN	AddNewLine	
	EXTERN	GetProvAndCity
	EXTERN	GetNumFromIncomingPDU
	EXTERN	setMenuText
	
	RSEG	CODE
	DATA
MENU_HDR_ICON
	DCD	0x156
	DCD	0
	
	CODE16
RecoedWindow_:
	PUSH	{LR}
	LDRB	R0, [R5, #9]
	CMP	R0, #7
	BCS	EX_PBACK
	LDR	R1, [R5, #4] //ºÅÂë WS ,ÅÐ¶ÏÒþ²ØºÅÂë
	LDR	R0, [R1, #0] //wsbody
	LDRH	R0, [R0, #0] //wslen
	CMP	R0, #0
	BEQ	EX_PBACK
	MOV	R0, R4
	BL	AddNewLine
	MOV	R0, R4
	LDR	R1, [R5, #4]
	BL	AppendInfoW
EX_PBACK
	MOV	R0, R4
	BL	AddNewLine
	MOV	R2, #1
	POP	{R0}
	ADD	R0, #4
	BX	R0

Callinwindow_:
	PUSH	{LR}
	LDR	R0, =ADDR_IsCalling
	BLX	R0
	MOV	R1, R0
	MOV	R0, #0
	MOV	R2, R4
	BL	UpdateLocaleToItem
	LDR	R0, =ADDR_CallIN
	BLX	R0
	CMP	R0, #0	
	POP	{R0}
	BEQ	HOOK1_EQ
	ADD	R0, #4
	BX	R0
HOOK1_EQ
	ADD	R0, #0xC
	BX	R0
	
CallOutWindow_:
	CMP	R0, R6
	BEQ	SHOW_EQ
	MOV	R1, SP
	PUSH	{LR}
	LDR	R2, =ADDR_CallOUT2
	BLX	R2
	POP	{R2}
	ADD	R2, #4
	BX	R2
SHOW_EQ
	PUSH	{LR}
	LDR	R0, =ADDR_IsCalling
	BLX	R0
	MOV	R1, R0
	MOV	R0, #3
	MOV	R2, R4
	BL	UpdateLocaleToItem
	POP	{R0}
	ADD	R0, #0x16
	BX	R0

AddrBookWindow_:
	CMP	R6, #0
	BNE	D_EBACK
	PUSH	{LR}
	MOV	R0, R4
	BL	AddNewLine
	MOV	R0, R4
	MOV	R1, R4
	BL	AppendInfoW
	MOV	R0, #1
	POP	{PC}
D_EBACK
	MOV	R0, #1
	BX	LR

SIMBOOK:
	PUSH	{LR}
	MOV	R0,R4
	BL	AddNewLine
	MOV	R0, R4
	MOV	R1, R4
	BL	AppendInfoW
	MOV	R3, #3
	POP	{PC}

#ifndef WITHOUT_SMS_IN_WIN
SMS_IN
	LDR	R0, [SP, #8]
	LDR	R2, [SP, #4]
	PUSH	{R0-R7, LR}
	MOV	R7, R0
	SUB	SP, #0x20
	LDR	R6, =0xAC5 //LGP ÐÂÐÅÏ¢
	CMP	R6, R2
	BNE	GoBack
	ADD	R0, SP, #0
	BL	GetNumFromIncomingPDU
	CMP	R0, #0
	BEQ	GoBack
	MOV	R0, R7
	BL	AddNewLine
	LDR	R0, [R7, #0]
	ADD	R1, SP, #0
	BL	GetProvAndCity
GoBack
	ADD	SP, #0x20
	POP	{R0-R7}
	POP	{R2}
	LDR	R0, [R0, #0] //WSTRLEN
	LDRH	R0, [R0, #0]
	STR	R0, [SP,#0xD8]
	ADD	R2, R2, #4
	BX	R2

#endif

NUM_SELECT_MENU_PSETTEXT: //R2, WS, 
	MOV	R4, LR
	BL	setMenuText
	BX	R4

	EXTERN	AddDialEQ
	EXTERN	DialGHookRedraw
	CODE32
EDIAL_CREATE
	ADD	LR, LR, #4
	STMFD	SP!,{LR}
	LDR	R0, [SP, #0x64] //EDITQ
	LDR	R1, [SP, #0x34] //ec
	LDR	R2, [SP, #0x20] //ecop
	MOV	R3, R7
	BLX	AddDialEQ
	MOV	R3, R7 //gui
	MOV	R2, #1
	MOV	R0, R4
	LDR	R1, [SP, #0x64] //editq
	LDMFD	SP!,{PC}
	
	CODE32
EDIAL_REDRAW
	ADD	LR, LR, #4
	STMFD	SP!,{LR}
	MOV	R0, R4
	BLX	DialGHookRedraw
	MOV	R2, #1
	MOV	R1, #1
	MOV	R0, R4
	BLX	ADDR_EDIT_UNK_VOID_INT_INT
	LDMFD	SP!,{PC}
	
	EXTERN	IsNum
	EXTERN	AddSpace
	CODE32
ADRBKLST_CATWS
	MOV	R4, LR
	LDR	R0, [R5, #0]
	MOV	R1, #1
	BLX	IsNum
	CMP	R0, #0
	MOVEQ	R0, R5
	BXEQ	R4
	MOV	R0, R5
	BLX	AddNewLine
	MOV	R0, R5
	MOV	R1, #4
	BLX	AddSpace
	LDR	R0, [R5, #0]
	ADD	R1, SP, #0x1C
	BLX	GetProvAndCity
	MOV	R0, R5
	BX	R4
	
	CODE32
ADRBKLST_SIMNUMWS
	STMFD	SP!,{LR}
	LDR	R0, [R8, #0]
	MOV	R1, #0
	BLX	IsNum
	CMP	R0, #0
	MOVEQ	R1, R10
	LDMEQFD	SP!,{PC}
	MOV	R0, R10
	BLX	AddNewLine
	MOV	R0, R10
	MOV	R1, R8
	BLX	AppendInfoW
	MOV	R1, R10
	LDMFD	SP!,{PC}
	
	CODE32
ADRBKLST_CATWS_2
	STMFD	SP!,{LR}
	LDR	R0, [R4, #0]
	MOV	R1, #1
	BLX	IsNum
	CMP	R0, #0
	MOVEQ	R0, R4
	LDMEQFD	SP!,{PC}
	MOV	R0, R4
	BLX	AddNewLine
	MOV	R0, R4
	MOV	R1, #4
	BLX	AddSpace
	LDR	R0, [R4, #0]
	ADD	R1, SP, #4
	BLX	GetProvAndCity
	MOV	R0, R4
	LDMFD	SP!,{PC}
	
	CODE32
ADRBKLST_CATWS_3
	MOV	R4, LR
	LDR	R0, [SP,#0x220]
	LDR	R0, [R0, #0]
	MOV	R1, #1
	BLX	IsNum
	CMP	R0, #0
	LDREQ	R0, [SP,#0x220]
	BXEQ	R4
	LDR	R0, [SP,#0x220]
	BLX	AddNewLine
	LDR	R0, [SP,#0x220]
	MOV	R1, #4
	BLX	AddSpace
	LDR	R0, [SP,#0x220]
	LDR	R0, [R0, #0]
	ADD	R1, SP, #0x1C
	BLX	GetProvAndCity
	LDR	R0, [SP,#0x220]
	BX	R4
	
	RSEG	RecordWindow:CODE(2)
	CODE16
	LDR	R0, =RecoedWindow_
	BLX	R0
	
	RSEG	Callinwindow:CODE(2)
	CODE16
	LDR	R0, =Callinwindow_
	BLX	R0
	
	
	RSEG	CallOutWindow:CODE(2)
	CODE16
	LDR	R1, P_CallOutWindow_
	BLX	R1
	DATA
P_CallOutWindow_
	DCD	CallOutWindow_
	CODE16
	NOP
	
	RSEG	AddrBookWindow2:DATA(1)
	DATA
	DCB	0xFF
	
	RSEG	AddrBookWindow:CODE(2)
	CODE32
	BLX	AddrBookWindow_
	
	
	RSEG	PHONEBOOKHOOK:CODE(2)
	CODE32
	BLX	SIMBOOK
	
#ifndef WITHOUT_SMS_IN_WIN
	RSEG	SMS_IN_HOOK:CODE(2)
	CODE16
	LDR	R0, =SMS_IN
	BLX	R0
#endif
	
	RSEG	NUM_SELECT_MENU_HDR_ICON:DATA(2)
	DATA
	DCD	MENU_HDR_ICON
	
	RSEG	NUM_SELECT_MENU_LINES:DATA(2)
	DATA
	DCD	1
	
	RSEG	NUM_SELECT_MENU_ALITEM:CODE(2)
	CODE32
	BLX	AllocMLMenuItem_adr //void *AllocMLMenuItem(void *data)
	
	RSEG	NUM_SELECT_MENU_TEXT:CODE(2)
	CODE32
	BLX	NUM_SELECT_MENU_PSETTEXT

	RSEG	NUM_SELECT_MENU_GUI:CODE(2)
	CODE32
	BLX	GetMLMenuGUI_adr //ml menu gui
	
	RSEG	EDIAL_CREATE_HOOK
	CODE16
	LDR	R0, =EDIAL_CREATE
	BLX	R0
	
	RSEG	EDIAL_REDRAW_HOOK
	CODE16
	LDR	R0, =EDIAL_REDRAW
	BLX	R0

	RSEG	EDIAL_ATTR_HOOK
	CODE16
	STR	R1, [SP,#8]
	STR	R2, [SP,#4]
	MOV	R2, #1
	LSL	R2, R2, #0x13
	ADD	R2, #0x40
	
	RSEG	ADRBKLST_LINES_HOOK1
	DATA
	DCD	2
	
	RSEG	ADRBKLST_LINES_HOOK2
	DATA
	DCD	2
	
	RSEG	ADRBKLST_LINES_HOOK3
	DATA
	DCD	2
	
	RSEG	ADRBKLST_ALLOCWS_HOOK
	CODE32
	ADD	R0, R0, #0x20
	NOP
	
	RSEG	ADRBKLST_CATWS_HOOK
	CODE32
	BL	ADRBKLST_CATWS
	
	RSEG	ADRBKLST_SIMALLWS_HOOK
	CODE32
	ADD	R1, R0, #0x20
	
	RSEG	ADRBKLST_SIMNUMWS_HOOK
	CODE32
	BL	ADRBKLST_SIMNUMWS
	
	RSEG	ADRBKLST_ALLOCWS_HOOK2
	CODE32
	ADD	R0, R7, #0x20
	
	RSEG	ADRBKLST_CATWS_HOOK2
	CODE32
	BL	ADRBKLST_CATWS_2
	
	RSEG	ADRBKLST_ALLOCWS_HOOK3
	CODE32
	ADD	R0, R0, #0x20
	NOP
	
	RSEG	ADRBKLST_CATWS_HOOK3
	CODE32
	BL	ADRBKLST_CATWS_3
	
	END
