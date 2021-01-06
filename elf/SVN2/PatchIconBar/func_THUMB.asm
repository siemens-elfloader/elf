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
ICON_GPRS_RED EQU 0x1EB   ;show
ICON_GPRS_GREY EQU 0x1EC  ;show
ICON_GPRS_ROMB EQU 0x1ED ;show
ICON_GPRS_DOWN EQU 0x1EE
ICON_GPRS_RIGHT EQU 0x1EF ;show
ICON_RIGHT EQU 0x4F7 ;

  EXTERN  main
        CODE16
		RSEG    PATCHV1:CODE:ROOT(1)
        blx j_main
        POP     {r4-r7,PC}

		RSEG    PATCHV1:CODE:ROOT(2)
		CODE32            
j_main:
		//      ldr r12,=main	
		B main
       


  END




