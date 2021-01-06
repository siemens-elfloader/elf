	THUMB
	EXTERN	main
; ---------------------------------------------------------------------------
	RSEG	PATCH_JUMP:CODE(2)	; ������ ����� ��� ���������� � ������� �����
l_patch_jump:
	mov	r1, lr
	adds	r1, #0x06	; r1=����� ����� ��������

	ldrb	r0, [r6]
	cmp	r0, #2		; �����
	beq	l_exit_quiet	; ����
	ldr	r0, [r7, #0x14]	; ��
	lsls	r0, r0, #2	; ��������
	bpl	l_exit		; �� ��� ������ - ����� (BMI �� ���������)

	adds	r0, r7, #0	; r0=r7=����� ������� WSHDR
	push	{r1}
	blx	main
	tst	r0, r0
	pop	{pc}
l_exit_quiet:
	tst	r1, r1		; r1=0xAxxxxxxx, �.�. ������� ��� ������� => ����������� ���. MI
l_exit:
	bx	r1
; ---------------------------------------------------------------------------
	RSEG	PATCH_ENTRY:CODE(2)	; ����� ������!!
	ldr	r1, =l_patch_jump
	blx	r1
; ---------------------------------------------------------------------------
	END
