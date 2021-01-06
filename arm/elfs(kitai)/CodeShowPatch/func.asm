#include "addr.h"

	//RSEG	CODE
//#ifdef SK6Cv50 //原来空间不够
        RSEG	CODE_X
//#endif
	CODE16
	
	PUBLIC	strlen
strlen:
	PUSH	{R4, LR} 
	LDR	R4, =ADDR_strlen
	BLX	R4
	POP	{R4, PC}
	
	PUBLIC	memcmp
memcmp:
	PUSH	{R4, LR} 
	LDR	R4, =ADDR_memcmp
	BLX	R4
	POP	{R4, PC}
	
	PUBLIC	atou
atou:
	PUSH	{R4, LR} 
	LDR	R4, =ADDR_atou
	BLX	R4
	POP	{R4, PC}
	
	PUBLIC	WS_InitByZero
WS_InitByZero:
	PUSH	{R4, LR} 
	LDR	R4, =ADDR_WS_InitByZero
	BLX	R4
	POP	{R4, PC}
	
	PUBLIC	GetCalleeNumber
GetCalleeNumber:
	PUSH	{R4, LR} 
	LDR	R4, =ADDR_GetCalleeNumber
	BLX	R4
	POP	{R4, PC}
	
	PUBLIC	UpdateWndItem
UpdateWndItem:
	PUSH	{R4, LR} 
	LDR	R4, =ADDR_UpdateWndItem
	BLX	R4
	POP	{R4, PC}
	
/*
	PUBLIC		AddNewLine
AddNewLine:
	PUSH	{R0-R7, LR}
	MOV	R1, #0xD
	LDR	R2, =ADDR_wsAppendChar
	BLX	R2
	POP	{R0-R7, PC}

	
	PUBLIC	AllocMenuWS
AllocMenuWS
	LDR	R3, =AllocMenuWS_adr
	BX	R3
	
	PUBLIC	SetMLMenuItemText
SetMLMenuItemText
	PUSH	{R3}
	LDR	R3, =SetMLMenuItemText_adr
	MOV	R12, R3
	POP	{R3}
	BX	R12
	*/
	END
