#include "addr.h"

/*
        EXTERN  get_month_day
        EXTERN  check_initday
    
        RSEG	CODE   
FilePath:
        DCB	 "2:\\SMSCount.Dat",00
    

        CODE16
        RSEG	CODE

//open file and write in it
main:
	PUSH	{R0-R6, LR}
	SUB	SP, #8
	LDR	R0, =FilePath
	LDR     R1, =0x301
	MOV	R2, #1
	LSL	R2, R2, #0x8
	MOV	R3, SP
	SWI     0x0A
	ADD	R5, R0, #0
	ADD     R3, R0, #1
	CMP	R3, #0
	BEQ	exit
	LDR	R6, =RamSMSNum
	MOV	R0, #2
	LDRB	R2, [R6, #0]
	LDRB	R1, [R6, #2]
	CMP	R1, #0x68
	BNE	CheckNumber
	ADD	R0, #1		//定位第一个数字的位置
	SUB	R2, #2
CheckNumber:
	CMP	R2, #0x0B
	BEQ	CheckChinaMblAndUniCom
        CMP	R2, #0x0E
        BEQ	CheckXLT   //小灵通
	B	CheckOthers
CheckChinaMblAndUniCom:
	LDRB	R1, [R6, R0]	//获得前两个数字
	CMP     R1, #0x51
	BEQ     CheckNewMb
	CMP	R1, #0x31
	BNE	CheckOthers
	ADD	R0, #1
	LDRB	R1, [R6, R0]
	MOV	R3,	#0x0F
	AND	R1, R3
	CMP	R1, #4
	BLT	UniCom
Mb:
	MOV	R3, #8
	B	ModfiyCountAndFile
UniCom:
	MOV	R3, #12
	B	ModfiyCountAndFile
CheckNewMb:
	ADD	R0, #1
	LDRB	R1, [R6, R0]
	MOV	R3, #0x0F
	AND	R1, R3
	CMP     R1, #3
	BEQ     UniCom
	CMP     R1, #6
	BEQ     UniCom
	CMP     R1, #7
	BEQ     Mb
	CMP     R1, #8
	BEQ     Mb
	CMP	R1, #9
	BEQ	Mb
CheckXLT:
        MOV	R3, #20
	B	ModfiyCountAndFile
CheckOthers:
	MOV	R3, #16
ModfiyCountAndFile:			
	LDR     R1, =RamUnuse
	LDR     R2, [R1, #4]
	ADD     R2, #1
	STR    	R2, [R1, #4]
	LDR     R2, [R1, R3]
	ADD     R2, #1
	STR     R2, [R1, R3]
	MOV   	R0, R5
	MOV    	R2, #24
	MOV     R3, SP
        SWI     0x0C
	MOV     R0, R5
	MOV    	R1, SP
	SWI     0x0D
exit:
	ADD	SP, #8
	POP	{R0-R6, R7}
	LDR     R0, [R6,#4]
        LDR     R1, [R0,#0x18]
        LDR     R2, [R0,#0x14]
        ADD     R0, R4, #0
	ADD     R7, #4
	BX      R7
*/
/*************
CheckIfinitRam
*************/
/*
initRam:
	PUSH	{R0-R6,LR}
	SUB	SP, #16
	LDR	R1, =RamUnuse
	LDR	R2, [R1, #0]
	CMP	R2, #0x0
	BEQ	needToInit
	B	CheckIfClean
needToInit:
	LDR	R0, =FilePath
	MOV	R1, #0
	MOV	R2, #0x80
	MOV	R3, SP
        SWI     0x0A
	ADD	R5, R0, #0
	ADD     R3, R0, #1
	CMP	R3, #0
	BEQ	exitinit
	MOV	R0, R5
	LDR	R1, =RamUnuse
	MOV	R2, #24
	MOV	R3, SP
        SWI     0x0B
	MOV	R0, R5
	MOV	R1, SP
        SWI     0x0D

CheckIfClean:
	BL      check_initday
        CMP     R0, #0
	BEQ     exitinit
        CMP     R0, #1
        BNE     exitinit
        
        MOV     R0, #2
        BL      get_month_day
        MOV     R2, R0
        
        LDR     R1, =RamUnuse
        LDR     R0, [R1, #0]
        CMP     R2, R0
        BEQ     exitinit
        STRB	R2, [R1, #0]
	MOV     R2, #0
	STR 	R2, [R1, #4]
	STR     R2, [R1, #8]
	STR     R2, [R1, #12]
	STR     R2, [R1, #16]
        STR     R2, [R1, #20]
SaveInit:
	LDR     R0, =FilePath
        MOV     R1, #1
	MOV    	R2, #1
	LSL    	R2, R2, #8
	MOV   	R3, SP
	SWI     0x0A
	ADD     R5, R0, #0
	ADD     R3, R0, #1
	CMP     R3, #0
	BEQ     exitinit
	LDR     R1, =RamUnuse
	MOV     R0, R5
	MOV    	R2, #20
	MOV    	R3, SP
        SWI     0x0C
	MOV     R0, R5
	MOV     R1, SP
        SWI     0x0D
exitinit:
	ADD	SP, #16
	POP	{R0-R6, R7}
#ifdef ELKA
	ADD     R3, SP
#endif
        STR     R0, [R3,#0x54]
        LDR     R0, =0xA3C
        LDR     R1, =0xA3C
        ADD     R7, #4
#ifdef NEWSGOLD
        SUB     R0, #0x14
#endif
	BX      R7
        
    RSEG SMSHook
    CODE16
    LDR  R2,  =main
    BLX	 R2
		
    RSEG hookwindow
    CODE16
    LDR     R1, =initRam
    BLX     R1*/
    
	EXTERN	check_num
	
	CODE16
	RSEG	CODE
_main
	PUSH	{R0-R6,LR}
	MOV	R0, #0
	BL	check_num
	POP	{R0-R6,R7}
	LDR	R0, [R6,#4]
	LDR	R1, [R0,#0x18]
	LDR	R2, [R0,#0x14]
	ADD	R0, R4, #0
	ADD	R7, R7, #4
	BX	R7

_main_fix
	PUSH	{LR}
	//ADD	R0, R6, #0
#ifdef E71Cv41        
	LDR	R1, =0xA00AD03C+1
#endif
#ifdef S7Cv47
	LDR	R1, =0xA00B1DBC+1
#endif  
#ifdef C81Cv50
	LDR	R1, =0xA00B1DBC+1
#endif       
	BLX	R1
	CMP	R0, #1
	BNE	fix_count
exit
	POP	{PC}
	
fix_count
	PUSH	{R0-R7}
	MOV	R0, #1
	BL	check_num
	POP	{R0-R7}
	B	exit
	
	CODE16        
	RSEG	SMS_COUNT_JMP
_JMP
	LDR	R1, =_main_fix
	BX	R1	
	
	CODE16
	RSEG	SMSHook
	LDR	R0, =_main
	BLX	R0
	
	CODE16
	RSEG	SMS_FIX_HOOK       
	BL	_JMP       
	END
    
    