;SWI dispatcher v1.0 (C)2006 by Rst7/CBSIE
;CX75sw23
;xcl:
;-carm
;-Z(CODE)CODE=A0FD8000-A0FD80FF
;-Z(CODE)PATCH1=A0092BE4-A0092BE7	//00000134+A0092AB0-00000137+A0092AB0
;-Z(CODE)PATCH2=A0092BA4-A0092BAB	//000000F4+A0092AB0-000000FB+A0092AB0
;-Z(CODE)LIBR=A0FD4000-A0FD7FFF
;
;S75sw40
;xcl:
;-carm
;-Z(CODE)CODE=A0078000-A00780FF
;-Z(CODE)PATCH1=A13A1374-A13A1377	//000002A4+A13A10D0
;-Z(CODE)PATCH2=A13A1288-A13A128B	//000001B8+A13A10D0
;-Z(CODE)LIBR=A0074000-A0077FFF
;
;	NAME	main

	RSEG	PATCH1:CODE
	CODE32

	LDR	PC,main_jumper

	RSEG	PATCH2:DATA(2)

main_jumper:
	DC32	main

	RSEG	CODE:CODE
	CODE32
nullsub:
	BX	LR
main:
	LDR	R1,[SP,#0]		; ����� CPSR
	TST	R1, #0x20		; ��������� �� �����
	ADREQ	R2,arm_jumper		; ����� ����� ��������
	BEQ	arm_mode
	CMP	R0,#199			; ��������� SWI ��� ������� ����������
	LDREQH	R0,[LR],#2		; ��������� ������ ����� (������� �����) c ��������� DW
        STREQ   LR,[SP,#0x14]           ; ��������� �������� ����� �������� (���� ������� ������)
	ADD	LR,LR,#1		; ������������� ��� 0, ���� �����
	ADR	R2,thumb_jumper		; ����� ����� ��������
arm_mode
	LDR	R1,=Library		; ��������� �� ������� �������
	BIC	R3,R0,#0x8000
        CMP	R3,#4096
        BHI	exit
	TST	R0,#0x8000		; � �� ����� ��� ���� ��������?
	STMEQFD	SP!,{LR}		; �������� ����� �������� �� LR_svc ������ ���� ����� �������
	LDMEQFD	SP!,{LR}^		; � LR_usr, �� ����� ����������� ���������� ��������
	LDR	R12,[R1,R3,LSL#2]	; ����� ����� �������
	STRNE	R12,[SP,#4]		; ����� ����� � R0(����)
	STREQ	R2,[SP,#0x14]		; ����� ����� �������� ��� �������� � ����� (PC)
exit:
	LDMFD	SP!,{R0}
	MSR	SPSR_cf,R0
	LDMFD	SP!,{R0-R3,PC}^
arm_jumper:
	BX	R12
	CODE16
thumb_jumper:
	BX	R12
	CODE32
;
; ���������� ����������
;
	RSEG    LIBR:DATA(2)
Library:
	DC32	nullsub
	DC32	nullsub
	DC32	nullsub
	DC32	nullsub
	DC32	nullsub
; � �.�.
	END     ;main
