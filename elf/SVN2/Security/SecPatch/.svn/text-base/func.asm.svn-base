/*
		RTMODEL "ARMv4M", "USED"
        RTMODEL "ARMv4T", "USED"
        RTMODEL "ARMv5T", "USED"
        RTMODEL "StackAlign4", "USED"
        RTMODEL "__cpu_mode", "__pcs__interwork"
        RTMODEL "__data_model", "absolute"
        RTMODEL "__dlib_file_descriptor", "0"
        RTMODEL "__endian", "little"
        RTMODEL "__rt_version", "6"
*/;===================================
	RSEG PATCH_CODE:CODE:NOROOT(2)
	EXTERN patch
	CODE16
call_patch
	BLX patch
	MOV R0, #0
	STRB    R0, [R7,#2]
	BX LR ;N3PT+4

	RSEG N3PT:CODE:ROOT(1)
n3pt	
	BL call_patch

	END
	