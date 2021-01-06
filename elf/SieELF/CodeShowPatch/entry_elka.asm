#include "addr.h"

	EXTERN	AppendInfoW
	EXTERN	UpdateLocaleToItem
	EXTERN	AddNewLine	
	
	RSEG	CODE
	
	DATA
MENU_HDR_ICON
	DCD	0x12E
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
	MOV	R0, #1
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
	MOV	R0, #4
	MOV	R2, R4
	BL	UpdateLocaleToItem
	POP	{R0}
	ADD	R0, #0x14
	BX	R0

AddrBookWindow_:
	MOV	R4, SP
	PUSH	{LR}
	LDR	R2, =ADDR_AllocWS
	BLX	R2
	MOV	R1, R4
	MOV	R4, R0
	LDR	R2, =ADDR_ADDRBook
	BLX	R2
	MOV	R0, R4
	BL	AddNewLine
	MOV	R0, R4
	MOV	R1, R4
	BL	AppendInfoW
	POP	{R0}
	ADD	R0, #4
	BX	R0
	

SIMBOOK:
	PUSH	{LR}
	ADD	R1, R4, #0
	ADD	R0, R6, #0
	LDR	R3, =ADDR_GetPhoneBookNum
	BLX	R3
	MOV	R0,R4
	BL	AddNewLine
	MOV	R0,R4
	MOV	R1,R4
	BL	AppendInfoW
	POP	{R3}
	ADD	R3, #4
	BX	R3

	RSEG	CODE_X
	EXTERN	GetProvAndCity
	EXTERN	GetNumFromIncomingPDU
	CODE16
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

	EXTERN	setMenuText
NUM_SELECT_MENU_PSETTEXT: //R2, WS, 
	LDR	R0, [SP, #0x208] //GUI
	LDR	R3, [SP, #0x20C] //item_n
	LDR	R1, [SP, #0] //item
	MOV	R4, LR
	BL	setMenuText
	ADD	R4, #4
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
	LDR	R1, =CallOutWindow_
	BLX	R1

	RSEG	AddrBookWindow3:CODE(1)
	CODE16
	NOP
	
	RSEG	AddrBookWindow:CODE(2)
	CODE16
	LDR	R1, AddrBookWindow_P
	BLX	R1
	DATA
AddrBookWindow_P
	DCD	AddrBookWindow_
	CODE16
	NOP
	
	CODE16
	RSEG	PHONEBOOKHOOK:CODE(2)
	LDR	R1, =SIMBOOK
	BLX	R1

	
	RSEG	SMS_IN_HOOK
	CODE16
	LDR	R0, =SMS_IN
	BLX	R0
	
	RSEG	NUM_SELECT_MENU_HDR_ICON:DATA(2)
	DATA
	DCD	MENU_HDR_ICON
	
	RSEG	NUM_SELECT_MENU_LINES:DATA(2)
	DATA
	DCD	1
	
	RSEG	NUM_SELECT_MENU_ALITEM:CODE(2)
	CODE16
	BLX	AllocMLMenuItem_adr //void *AllocMLMenuItem(void *data)
	
	RSEG	NUM_SELECT_MENU_TEXT:CODE(2)
	CODE16
	LDR	R1, P_NUM_SELECT_MENU_PSETTEXT
	BLX	R1
	DATA
P_NUM_SELECT_MENU_PSETTEXT
	DCD	NUM_SELECT_MENU_PSETTEXT
	CODE16
	NOP
	
	RSEG	NUM_SELECT_MENU_GUI:CODE(1)
	CODE16
	BLX	GetMLMenuGUI_adr //ml menu gui
	
	END



