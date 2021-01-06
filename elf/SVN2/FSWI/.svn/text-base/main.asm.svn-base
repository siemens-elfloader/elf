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
	LDR	R1,[SP,#0]		; Берем CPSR
	TST	R1, #0x20		; Проверяем на тумбу
	ADREQ	R2,arm_jumper		; Берем адрес джампера
	BEQ	arm_mode
	CMP	R0,#199			; Служебный SWI для длинной библиотеки
	LDREQH	R0,[LR],#2		; Зацепляем второе слово (длинный номер) c пропуском DW
        STREQ   LR,[SP,#0x14]           ; Сохраняем временно адрес возврата (если захочем данные)
	ADD	LR,LR,#1		; Устанавливаем бит 0, если тумба
	ADR	R2,thumb_jumper		; Берем адрес джампера
arm_mode
	LDR	R1,=Library		; Указатель на таблицу адресов
	BIC	R3,R0,#0x8000
        CMP	R3,#4096
        BHI	exit
	TST	R0,#0x8000		; А не адрес нам надо получить?
	STMEQFD	SP!,{LR}		; Копируем адрес возврата из LR_svc только если вызов функции
	LDMEQFD	SP!,{LR}^		; в LR_usr, он будет использован вызываемой функцией
	LDR	R12,[R1,R3,LSL#2]	; Берем адрес функции
	STRNE	R12,[SP,#4]		; пишем адрес в R0(стек)
	STREQ	R2,[SP,#0x14]		; Пишем адрес джампера для возврата в стеке (PC)
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
; Собственно библиотека
;
	RSEG    LIBR:DATA(2)
Library:
	DC32	nullsub
	DC32	nullsub
	DC32	nullsub
	DC32	nullsub
	DC32	nullsub
; И т.д.
	END     ;main
