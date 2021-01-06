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

        EXTERN  main
	EXTERN  shift

        CODE16
        // раскладка клавы на '#'
        RSEG    PATCH:CODE:ROOT(1)
	B	main
;        PUSH    {R4-R7,LR}
;        BL	main
;	POP     {R4-R7,PC}


	// символы на долгий '#'
        RSEG    PATCHLONGPRESS:DATA:ROOT(1)
        DC8	3
	
        // регистр на '*'
        RSEG    PATCHSHIFT:CODE:ROOT(1)
	BL	shift


	END


