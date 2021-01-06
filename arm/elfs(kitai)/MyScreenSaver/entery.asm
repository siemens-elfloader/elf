
	EXTERN	main
	EXTERN	new_IsUnlocked
	
	/*
	CODE16
	RSEG	ENTRYPOINT_LONGPRESSLOCK:CODE(1)
	BL	_JMP
	
	CODE16
	RSEG	ENTRYPOINT_AUTOLOCK:CODE(1)
	BL	_JMP
	B	0xA05DA70A+1
	
	CODE16
	RSEG	ENTRYPOINT_AUTOLOCK1:CODE(1)
	BL	_JMP
	NOP
	NOP
	
	CODE16
	RSEG	HOOK_JMP
_JMP
	LDR	R7, =main
	BX	R7 
	
	CODE16
	RSEG	SCREENSAVER_FIX_HOOK
	B	0xA05DA70A+1*/
#ifdef	VKP
	CODE16
	RSEG	KBDLOCK_HOOK:CODE(2)
	LDR	R1, =main
	BX	R1
	
	CODE16
	RSEG	DISABLE_SCREENSAVER_HOOK:CODE(1)
	B	0xA06891D4+1
	
	CODE16
	RSEG	LIGHT_HOOK:CODE(1)
	SWI	0x43
	NOP
	
	//DATA
	RSEG	SWILIB_IsUnlocked:DATA(2)
	DCD	NewIsUnlocked
	
	//DATA
	RSEG	SWILIB_KBDLOCK:DATA(2)
	DCD	NewKeyLock
	
	RSEG	DISABLE_KEYLOCK_MSG_HOOK
	CODE16
	NOP
	NOP
#endif
	
	
#ifdef	VKP	
	RSEG	CODE_G
	CODE32
NewKeyLock
	LDR	R12, main_
	BX	R12
	
NewIsUnlocked
	LDR	R12, new_IsUnlocked_
	BX	R12
	
	PUBLIC	kill_data
kill_data
	BX	R1
#else
	RSEG	CODE
	CODE32
#endif
	PUBLIC	Update_MissedEventsPtr
Update_MissedEventsPtr
	LDR	R12, Update_MissedEventsPtr_
	BX	R12
	
	PUBLIC	OPEN_INBOX
OPEN_INBOX
	LDR	R12, =0xA070783B
	BX	R12
	
	DATA
	
#ifdef VKP
main_
	DCD	main
new_IsUnlocked_
	DCD	new_IsUnlocked
#endif

Update_MissedEventsPtr_
	DCD	Update_MissedEventsPtr_0
//Update_MissedEventsPtr_Func
//	DCD	0xA0685090+1

	CODE16
Update_MissedEventsPtr_0
	PUSH	{R1-R7, LR}
	MOV	R0, #0
	MOV	R1, #0
	MOV	R2, #0
	MOV	R3, #0
	MOV	R4, #0
	LDR	R7, =0xA0685090+1
	BLX	R7
	POP	{R1-R7, PC}
	
	END