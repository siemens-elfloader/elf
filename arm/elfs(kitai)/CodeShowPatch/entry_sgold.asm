
#include "addr.h"

	EXTERN	AppendInfoW
	EXTERN	UpdateLocaleToItem
        EXTERN  AddNewLine
//��Ҫ�м���ת
#ifdef S6Cv53
#define Jmp
#elif C6Cv53
#define Jmp
#endif
//�����⴦��SIM�绰��
#ifdef C6Cv53
#define SIM128
#elif SL6Cv50
#define SIM128
#endif
//�����⴦������ѡ��
#ifdef C7Cv22
#define SeleNum
#elif CX7Av25
#define SeleNum
#endif


	RSEG	CODE
#ifdef SK6Cv50 //ԭ���ռ䲻��
        RSEG	CODE_X
#endif

        DATA
MENU_HDR_ICON //�����ѡ�� ����ͼ��ID
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
        
#ifdef 	SIM128 //SIM�绰��,SL6C��C6C�����⴦��
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
#else   //��������     
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

//���ŷ��Ͷ�������,by BingK(binghelingxi)
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
// ͨ����¼�޸�
	RSEG	RecordWindow:CODE(1)
	CODE16
	BL		Hook1

// ���봰���޸ģ�������group xx����ʾλ��
	RSEG	Callinwindow:CODE(1)
	CODE16
	BL		Hook2

// ���������޸ģ�������group xx����ʾλ��
	RSEG	CallOutWindow:CODE(1)
	CODE16
	BL		Hook3

// ͨѶ¼�����޸�
	RSEG 	AddrBookWindow:CODE(1)
	CODE16
	BL		Hook4

	RSEG	AddrBookWindow2:DATA(1)
	DCB		0x21

// �绰�������޸�
	RSEG	PhonebookWindow:CODE(1)
	CODE16
#ifdef	Jmp
	BL		HOOK5_JMP
#else
	BL		Hook5
#endif
//���ŷ��Ͷ�������,by BingK(binghelingxi)	
	CODE16
	RSEG	SMS_SEND_HOOK:CODE(2)
	LDR		R2, pSMS_SEND
	BLX		R2
	
	DATA
pSMS_SEND
	DCD		SMS_SEND_WINDOW
	
	CODE16
	NOP
      
        RSEG	SMS_SEND_FIX:DATA(1) //����ws������
	DCB	        0x25
    
#ifndef WITHOUT_SMS_IN_WIN
//SGold��������ʾ���� By DaiKangaroo
	RSEG	CODE
	EXTERN	GetProvAndCity
	EXTERN	GetNumFromIncomingPDU
	CODE16
        
SMS_IN:
#ifdef CX7Cv50 //�ر���,hookλ�ñ�������������2���ֽڣ��Դﵽ4�ֽڶ���
        //Hook֮ǰһ��ָ�� MOV R0, R4
        //ԭ��Hookλ�ô���
        //BLX Sub ��������:  STR R1, [R0, #78]
        //MOV R1, #0
        //MOV R0, R4
        STR		R1, [R4, #0x78]
        MOV             R1, #0
        MOV             R0, R4
#else //����SGold����
        //ԭ��Hookλ�ô���
	//MOV R0, R4
        //BLX Sub ��������:  STR R1, [R0, #78]
        //MOV R1, #0
        //����Ϊ
	STR		R1, [R4, #0x78]
        MOV             R1, #0
#endif  
	PUSH		{R0-R7, LR}
        SUB		SP, #0x30   //�����ջ��ź���
	LDR		R2, =0x272 //�յ��µ���ϢLGP
#ifdef CX7Cv50 //�ر���[SP,#0xC]���LGP_ID
        LDR             R7,[SP,#0x3C]
#endif
	CMP		R7, R2
	BNE		GoBack
	ADD		R0, SP, #0
	BL		GetNumFromIncomingPDU
	CMP		R0, #0 //����ֵ
	BEQ		GoBack
	MOV		R0, R5 //R5����WSָ��
	BL		AddNewLine //����һ��
	LDR		R0, [R5, #0] //���WS�ַ���
	ADD		R1, SP, #0   //R1Ϊ����
	BL		GetProvAndCity	
GoBack:
        ADD		SP, #0x30
	POP		{R0-R7}
	POP		{R3}
	ADD		R3, #4
	BX		R3
        
//�������޸�
	RSEG	SMS_IN_HOOK:CODE(2)
        CODE16
	LDR		R0, =SMS_IN
	BLX		R0
#endif

//sgold�����ѡ�� ��ֲby DaiKangaroo
        RSEG CODE
        EXTERN	setMenuText
NUM_SELECT_MENU_PSETTEXT: //R2, WS, 
#ifndef SeleNum //C7C��CX7Av25��hookλ��+2���������
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
#ifdef SeleNum //C7C��CX7A��hookλ��+2
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
        
//���������� by Daikangaroo
        EXTERN ChangeHeaderText
        RSEG CODE
        CODE16
ChangeSMSHeaderText:        
        LDR    R0, [SP,#0x10] //gui
        LDR    R1, [R6,#0]
        ADD    R1, #0x2C //����ACSII
        MOV    R2, R4      //malloc_adr
        MOV    R3, R5      //free_adr
        MOV    R7, LR        //����hookλ��
        BL     ChangeHeaderText

        //hookλ��ԭ������
        MOV    R3, R5      //free_adr
        MOV    R2, R4      //malloc_adr
        LDR    R0, [SP,#0x10] //gui
        LDR    R1, [SP,#0xC] //R1Ϊ������������
        
        ADD    R7,#4
        BX     R7
        
        RSEG	SMSHeader_HOOK:CODE(2)
        CODE16
	LDR		R1, =ChangeSMSHeaderText
	BLX		R1        
        
        END