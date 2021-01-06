	RSEG	PATCH1:CODE
	CODE16

RegSharpHandler:
	push {r1, lr}

	LDR	R1,=handler
	STR   R0, [R1, #0]

	pop {r1, pc}

run:
	push {r0-r1,lr}

	LDR	R1,=handler
	LDR   R0, [R1, #0]
   cmp r0, #0
   beq end
	blx r0
end:
	pop {r0-r1, pc}


   RSEG    HNDL:DATA(2)
handler:
  DC32	0

  RSEG	PATCH2:CODE
  CODE16

  bl run

  END
