	THUMB
	RSEG	TYPE_SAVE:CODE(2)
save_type:
	push	{r4, lr}
	swi	0xC7
	strh	r4, [r4, #6]	;не команда, а замена DB 0x80E4
	pop	{r4}
	str	r4, [r0, #0x7C]
	adds	r0, r4, #0
	pop	{pc}
; ---------------------------------------------------------------------------
	ARM

	RSEG	TYPE_ENTRY:CODE(2)
	blx	save_type
; ---------------------------------------------------------------------------
	EXTERN	main
	RSEG	PATCH_ENTRY:CODE(2)
	bl	main
; ---------------------------------------------------------------------------
	RSEG	ADDR_DB_FNAME:CODE(2)
	PUBLIC	db_fname
db_fname:
; ---------------------------------------------------------------------------
	END
