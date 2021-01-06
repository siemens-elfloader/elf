
/*
//Screen Saver
ROM:A035DED2 26 22                       MOV     R2, #0x26 //wslen
ROM:A035DDC6 C5 F0 B4 EA                 BLX     sub_A0423330    ; void GetProvider(WSHDR *ws, int _0);

subprovider
ROM:A030718E 65 22                       MOV     R2, #0x65

mslen
ROM:A0306DD0 24 22                       MOV     R2, #0x24

03071C4: 00 FF                                           ; S7Cv47 - Subprovider in

0423338: 0xA095E88B 0xA0061601                           ; S7Cv47 - Provider
03071DC: 301CFFF750FDEA79311C 004B9847,0xA0061611,C046   ; S7Cv47 - Subprovider
03071C4: 00 FF                                           ; S7Cv47 - Subprovider in Profile0

ROM:A035E34E D8 48                       LDR     R0, =dword_A0473B80 ; Êý×ÖÊ±ÖÓ
ROM:A035E350 E0 38                       SUB     R0, #0xE0
ROM:A035E352 4D E0                       B       loc_A035E3F0

56+96=152
*/

#define PATCH_ID 0x8800
/*S7Cv47
#pragma enable old_equal_ff
0061B00: 0xB1C2D3E4,0x00008800,0000000000000000,"\
{p=`SP NSG MP` ver=1.0 cp=BingK id=8800}\
{16 u `Provider MS` ml=64}\
{144 u Subprovier ml=64}\
{272 u `Provider SS` ml=64}",00
#pragma disable old_equal_ff
*/
/*ELKA
#pragma enable old_equal_ff
0061600: 0xB1C2D3E4,0x00008800,0000000000000000,"\
{p=`SP NSG MP` ver=1.0 cp=BingK id=8800}\
{16 u `Provider MS` ml=64}\
{144 u Subprovier ml=64}\
{272 u `Provider SS` ml=64}",00
#pragma disable old_equal_ff
*/
	EXTERN	GetRepString
	
	RSEG	CODE
	CODE32
SubProvider_WS_CODE
	ADD	LR, LR, #4
	MOV	R0, R6
	LDRB	R2, [R5,#7]
	MOV	R1, #0x9
	//B	GetRepString
GET_REP_STR
	STMFD	SP!,{R0-R7,LR}
	MOV	R7, R0
	MOV	R6, R1
	MOV	R0, #PATCH_ID
	SWI	0xC4 //void *GetBuffer(int patch_id);
	CMP	R0, #0
	BEQ	EXIT0
	ADD	R5, R0, #0x10
	CMP	R6, #0x9
	ADDEQ	R1, R5, #128
	BEQ	DO_REP
	SWI	0x42 //int IsScreenSaver(void);
	CMP	R0, #0
	MOVEQ	R1, R5
	ADDNE	R1, R5, #256
DO_REP
	MOV	R0, R7
	BL	GetRepString
	LDMFD	SP!,{R0-R7,PC}
EXIT0
	CMP	R6, #0x9
	BNE	EXIT_PRI
	SWI	0xB6
	CMP	R0, #0
	LDMEQFD	SP!,{R0-R7,PC}
	MOV	R0, R7
	SWI	0x8D //GetProfileName
	LDMFD	SP!,{R0-R7,PC}
EXIT_PRI
	MOV	R0, R7
	MOV	R1, #0
	SWI	0x41 //void GetProvider(WSHDR *ws, int _0);
	LDMFD	SP!,{R0-R7,PC}
/*
MS_POS_CODE
	LDRB	R0, [R7, #0]
	CMP	R0, #5
	BCS	MS_POS_ERR
	ADD	LR, LR, #4
	ADD	R3, LR, #7
	CMP	R0, #0
	BXNE	LR
	STMFD	SP!,{RO-R4,R6,R7,LR}
	MOV	R0, #PATCH_ID
	SWI	0xC4 //void *GetBuffer(int patch_id);
	CMP	R0, #0
	BEQ	MS_POS_EX_BACK
	MOV	R6, R0
	ADD	R0, R0, #216 //
	MOV	R7, R0
	MOV	R1, R5
	MOV	R2, #56
	SWI	0x011E //void * memcpy (void *dest,const void *source,int cnt);
	LDR	R1, [R5, #0x20]
	ADD	R0, R7, #56 //size1
	MOV	R4, R0
	MOV	R2, #96 //size2
	SWI	0x011E //void * memcpy (void *dest,const void *source,int cnt);
	LDR	R0, [R6, #208] //
	STR	R0, [R4, #0x10]
	LDR	R0, [R6, #212] //
	STR	R0, [R4, #0x20]
	STR	R4, [R7, #0x20]
	MOV	R5, R7
MS_POS_EX_BACK
	LDMFD	SP!,{RO-R4,R6,R7,LR}
MS_POS_ERR
	ADD	LR, LR, #0x4E
	BX	LR
	*/
	RSEG	Subprovider_PO_HOOK:DATA(1)
	DATA
	DCB	0xFF
	
	RSEG	Provider_WS_HOOK
	DATA
	DCD	GET_REP_STR
	
	RSEG	SubProvider_WS_HOOK
	CODE16
	LDR	R0, =SubProvider_WS_CODE
	BLX	R0

	//RSEG	SS_MAXLEN_HOOK:DATA(1)
	//DATA
	//DCB	0x65
	
	//RSEG	MS_MAXLEN_HOOK:DATA(1)
	//DATA
	//DCB	0x65
	
	//RSEG	MS_POS_HOOK
	//CODE16
	//LDR	R0, =MS_POS_CODE
	//BLX	R0
	//RSEG	HELP_HOOK
	//CODE16
	//BL	0xA03086A6+1
	
	END