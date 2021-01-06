   
	THUMB
	EXTERN	main
; ---------------------------------------------------------------------------
	RSEG	PATCH_JUMP:CODE(2)	; пустое мест?для подготовки ?запуск?патч?
l_patch_jump:
#ifdef NEWSGOLD
	mov	r1, lr
	adds	r1, #0x04	; r1=новы?адре?возврата

	cmp	r0, #2		; кусо?
	beq	l_exit_quiet	; кода
	ldr	r0, [sp, #4]
	ldr	r0, [r0, #0x18]	; из
	lsls	r0, r0, #2	; прошивки
	bpl	l_exit		; не на?случай - выхо?(BMI не сработае?

	ldr	r0, [sp, #4]	; r0=r7=адре?массив?WSHDR
	push	{r1}
	blx	main
	tst	r0, r0
	pop	{pc}
#else
	mov	r1, lr
	adds	r1, #0x42	; r1=новы?адре?возврата

	ldrb	r0, [r0]
	cmp	r0, #2		; кусо?
	beq	l_exit_quiet	; кода
	ldr	r0, [r7, #0x14]	; из
	lsls	r0, r0, #2	; прошивки
	bpl	l_exit		; не на?случай - выхо?(BMI не сработае?

	adds	r0, r7, #0	; r0=r7=адре?массив?WSHDR
	push	{r1}
	blx	main
	tst	r0, r0
	pop	{pc}
#endif
; ---------------------------------------------------------------------------
l_exit_quiet:
	tst	r1, r1		; r1=0xAxxxxxxx, ?? старши?би?включе?=> выполняет? ус? MI
l_exit:
	bx	r1
; ---------------------------------------------------------------------------
	RSEG	PATCH_ENTRY:CODE(2)	; мест?врезки!!
	ldr	r1, =l_patch_jump
	blx	r1
; ---------------------------------------------------------------------------
	END
