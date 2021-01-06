#ifndef ELKA
        RTMODEL "ARMv4M", "USED"
        RTMODEL "ARMv4T", "USED"
        RTMODEL "ARMv5T", "USED"
        RTMODEL "StackAlign4", "USED"
        RTMODEL "__cpu_mode", "__pcs__interwork"
        RTMODEL "__data_model", "absolute"
        RTMODEL "__dlib_file_descriptor", "0"
        RTMODEL "__endian", "little"
        RTMODEL "__rt_version", "6"

        RSEG CODE:CODE:NOROOT(2)

;===================================================================
#pragma data_alignment=2

        EXTERN  main
        CODE16
        // конвертация тега
		RSEG    PATCHV1:CODE:ROOT(2)
        ldr r0,=main_v1
		BX  r0

		RSEG    PATCHV2:CODE:ROOT(2)
		ldr r0,= main_v2
		BX  r0
		
		CODE32
		RSEG    CODE:CODE:ROOT(2)
		main_v1:
			;          LSL     R2, R3, #0x10
            LSR     R2, R2, #0x10
            ADD     R1, R5, #0
            ADD     R0, R4, #0
        BL     0xA066028C
			mov	r0,r4
		Bl	main
			MOV     R0, #0
			STRB    R0, [R6]
		POP     {R3-R7,PC}
		main_v2:
			;           LSL     R2, R3, #0x10
			;                LSR     R2, R2, #0x10
			;                ADD     R1, R5, #0
            ADD     R0, R4, #0
        BL     0xA066028C
			push {r0}
			mov	r0,r4
		Bl	main
			POP	{R0}
        POP     {R1-R7,PC}
#endif
	END


