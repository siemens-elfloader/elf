#ifdef ELKA
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
;	EXTERN  shift

        CODE32
        // конвертация тега
    RSEG    PATCHV2:CODE:ROOT(2)
	B	main_v2
    RSEG    PATCHV1:CODE:ROOT(2)
	B	main_v1

       RSEG    CODE:CODE:ROOT(2)
main_v2:
	PUSH {R0}	
	mov	r0,r4
	Bl	main
	POP	{R0}
	;BLX 	LR
	LDMFD   SP!, {R2-R8,R10,R11,PC} ; exit	
main_v1:
	PUSH {R0}	
	mov	r0,r5
	Bl	main
	POP	{R0}
	;BLX 	LR
	LDMFD   SP!, {R2-R6,PC} ; exit
	
;        PUSH    {R4-R7,LR}
;        BL	main
;	POP     {R4-R7,PC}


	// символы на долгий '#'
;;        RSEG    PATCHLONGPRESS:DATA:ROOT(1)
;;        DC8	3
	
        // регистр на '*'
;;        RSEG    PATCHSHIFT:CODE:ROOT(1)
;	BL	shift

#endif
	END


