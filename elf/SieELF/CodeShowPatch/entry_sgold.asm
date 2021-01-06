
#include "addr.h"

	EXTERN	AppendInfoW
	EXTERN	UpdateLocaleToItem
        EXTERN  AddNewLine
//需要中间跳转
#ifdef S6Cv53
#define Jmp
#elif C6Cv53
#define Jmp
#endif
//需特殊处理SIM电话簿
#ifdef C6Cv53
#define SIM128
#elif SL6Cv50
#define SIM128
#endif
//需特殊处理多号码选择
#ifdef C7Cv22
#define SeleNum
#elif CX7Av25
#define SeleNum
#endif


	RSEG	CODE
#ifdef SK6Cv50 //原来空间不够
        RSEG	CODE_X
#endif

        DATA
MENU_HDR_ICON //多号码选择 标题图标ID
#ifdef CX6Cv50
        DCD	0x307
#endif
#ifdef M6Cv50
        DCD	0x2F2
#endif
#ifdef S6Cv53
        DCD	0x2CD
#endif
#ifdef SK6Cv50
        DCD	0x2E2
#endif
#ifdef CX7Cv50
        DCD	0x30D
#endif
#ifdef CX7Av25
        DCD	0x2E7
#endif
#ifdef SL6Cv50
        DCD	0x2C2
#endif
#ifdef C6Cv53
        DCD	0x2C5
#endif
#ifdef C7Cv22
        DCD	0x374
#endif
	DCD	0
       
	CODE16        
        PUBLIC	GetHeaderPointer
GetHeaderPointer
	LDR	R3, =GetHeaderPointer_addr
	BX	R3
	
	PUBLIC	SetHeaderText
SetHeaderText
	LDR	R3, =SetHeaderText_addr
	BX	R3
       
	PUBLIC	AllocWS
AllocWS:
	LDR		R3, =ADDR_AllocWS
	BX		R3

Hook1:
	PUSH		{R0-R1,R4,LR}
	MOV		R4, R0
	LDR		R2, =ADDR_wstrcat
	BLX		R2
	MOV		R0, R4
	BL		AddNewLine
	POP		{R0-R1,R4}
	BL		AppendInfoW	
	POP		{PC}
Hook2:
	MOV		R0, #0
	MOV		R1, R4
	MOV		R2, R5
	BL		UpdateLocaleToItem
	LDR		R0, =ADDR_CallIN
	BLX		R0		

Hook3:
	LDR		R0, =ADDR_IsCalling
	BLX		R0
	MOV		R1, R0
	MOV		R0, #3
	MOV		R2, R4
	BL		UpdateLocaleToItem
	LDR		R0, =ADDR_CallOUT
	BLX		R0

Hook4:
	PUSH		{LR}
	MOV		R4, R0
	LDR		R2, =ADDR_ADDRBook
	BLX		R2
	MOV		R0, R4
	BL		AddNewLine
	MOV		R0, R4
	MOV		R1, R4
	BL		AppendInfoW
	POP		{PC}
        
#ifdef 	SIM128 //SIM电话簿,SL6C与C6C需特殊处理
Hook5:
	PUSH		{LR}
	LDR		R0, [SP,#0x178]
	BL		AddNewLine
	LDR		R0, [SP,#0x178]
	LDR		R1, [SP,#0x1D4]
	BL		AppendInfoW
	MOV		R1, #0
	LDR	        R0, [SP, #0x12C]
	POP		{PC}
#else   //其他机型     
Hook5:
	PUSH		{LR}
	LDR		R0, [SP,#0x174]
	BL		AddNewLine
	LDR		R0, [SP,#0x174]
	LDR		R1, [SP,#0x1D0]
	BL		AppendInfoW
	MOV		R1, #0
	ADD		R0, R7, #0
	POP		{PC}	
#endif

//短信发送动画窗口,by BingK(binghelingxi)
	EXTERN		GetProvAndCity
SMS_SEND_WINDOW:
	PUSH		{R4, LR}
	MOV		R2, #0
	ADD		R1, R7, #0
	ADD		R0, R5, #0
	LDR		R3, =ADDR_SMS_SEND
	BLX		R3
	MOV		R0, R5
	BL		AddNewLine
	LDR		R0, [R5, #0]
	POP		{R4}
	MOV		R3, #0xBC
	LDR		R1, [R4, R3]
	BL		GetProvAndCity
	POP		{R0}
	ADD		R0, R0, #4
	BX		R0
      
#ifdef Jmp
	RSEG	JMP_BODY
HOOK5_JMP
	LDR	R0, =Hook5
	BX	R0
#endif

//Hook
// 通话记录修改
	RSEG	RecordWindow:CODE(1)
	CODE16
	BL		Hook1

// 拨入窗口修改，覆盖了group xx的显示位置
	RSEG	Callinwindow:CODE(1)
	CODE16
	BL		Hook2

// 拨出窗口修改，覆盖了group xx的显示位置
	RSEG	CallOutWindow:CODE(1)
	CODE16
	BL		Hook3

// 通讯录窗口修改
	RSEG 	AddrBookWindow:CODE(1)
	CODE16
	BL		Hook4

	RSEG	AddrBookWindow2:DATA(1)
	DCB		0x21

// 电话本窗口修改
	RSEG	PhonebookWindow:CODE(1)
	CODE16
#ifdef	Jmp
	BL		HOOK5_JMP
#else
	BL		Hook5
#endif
//短信发送动画窗口,by BingK(binghelingxi)	
	CODE16
	RSEG	SMS_SEND_HOOK:CODE(2)
	LDR		R2, pSMS_SEND
	BLX		R2
	
	DATA
pSMS_SEND
	DCD		SMS_SEND_WINDOW
	
	CODE16
	NOP
      
        RSEG	SMS_SEND_FIX:DATA(1) //增加ws串长度
	DCB	        0x25
    
#ifndef WITHOUT_SMS_IN_WIN
//SGold来短信显示区号 By DaiKangaroo
	RSEG	CODE
	EXTERN	GetProvAndCity
	EXTERN	GetNumFromIncomingPDU
	CODE16
        
SMS_IN:
#ifdef CX7Cv50 //特别处理,hook位置比其他机型下移2个字节，以达到4字节对齐
        //Hook之前一条指令 MOV R0, R4
        //原来Hook位置代码
        //BLX Sub 函数功能:  STR R1, [R0, #78]
        //MOV R1, #0
        //MOV R0, R4
        STR		R1, [R4, #0x78]
        MOV             R1, #0
        MOV             R0, R4
#else //其他SGold机型
        //原来Hook位置代码
	//MOV R0, R4
        //BLX Sub 函数功能:  STR R1, [R0, #78]
        //MOV R1, #0
        //代替为
	STR		R1, [R4, #0x78]
        MOV             R1, #0
#endif  
	PUSH		{R0-R7, LR}
        SUB		SP, #0x30   //分配堆栈存放号码
	LDR		R2, =0x272 //收到新的信息LGP
#ifdef CX7Cv50 //特别处理，[SP,#0xC]存放LGP_ID
        LDR             R7,[SP,#0x3C]
#endif
	CMP		R7, R2
	BNE		GoBack
	ADD		R0, SP, #0
	BL		GetNumFromIncomingPDU
	CMP		R0, #0 //返回值
	BEQ		GoBack
	MOV		R0, R5 //R5保存WS指针
	BL		AddNewLine //增加一行
	LDR		R0, [R5, #0] //获得WS字符串
	ADD		R1, SP, #0   //R1为号码
	BL		GetProvAndCity	
GoBack:
        ADD		SP, #0x30
	POP		{R0-R7}
	POP		{R3}
	ADD		R3, #4
	BX		R3
        
//来短信修改
	RSEG	SMS_IN_HOOK:CODE(2)
        CODE16
	LDR		R0, =SMS_IN
	BLX		R0
#endif

//sgold多号码选择 移植by DaiKangaroo
        RSEG CODE
        EXTERN	setMenuText
NUM_SELECT_MENU_PSETTEXT: //R2, WS, 
#ifndef SeleNum //C7C和CX7Av25的hook位置+2，跳过这句
	LDR	R0, [SP, #0x208] //GUI
#endif
	LDR	R3, [SP, #0x20C] //item_n
	LDR	R1, [SP, #0] //item
	MOV	R4, LR
	BL	setMenuText
	ADD	R4, #4
	BX	R4
        
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
#ifdef SeleNum //C7C和CX7A的hook位置+2
        LDR	R1, =NUM_SELECT_MENU_PSETTEXT
        BLX	R1
#else
	LDR	R1, P_NUM_SELECT_MENU_PSETTEXT
	BLX	R1
	DATA
P_NUM_SELECT_MENU_PSETTEXT
	DCD	NUM_SELECT_MENU_PSETTEXT
	CODE16
	NOP
#endif
        RSEG	NUM_SELECT_MENU_GUI:CODE(1)
	CODE16
	BLX	GetMLMenuGUI_adr //ml menu gui
        
//短信区号秀 by Daikangaroo
        EXTERN ChangeHeaderText
        RSEG CODE
        CODE16
ChangeSMSHeaderText:        
        LDR    R0, [SP,#0x10] //gui
        LDR    R1, [R6,#0]
        ADD    R1, #0x2C //号码ACSII
        MOV    R2, R4      //malloc_adr
        MOV    R3, R5      //free_adr
        MOV    R7, LR        //保存hook位置
        BL     ChangeHeaderText

        //hook位置原来代码
        MOV    R3, R5      //free_adr
        MOV    R2, R4      //malloc_adr
        LDR    R0, [SP,#0x10] //gui
        LDR    R1, [SP,#0xC] //R1为短信完整内容
        
        ADD    R7,#4
        BX     R7
        
        RSEG	SMSHeader_HOOK:CODE(2)
        CODE16
	LDR		R1, =ChangeSMSHeaderText
	BLX		R1        
        
        END