        CODE16
	
	EXTERN	Patch_GlobalScan
	EXTERN	Patch_WorkScan
	
        RSEG    PATCH_GLOBAL_SCAN:CODE:ROOT(1)
	
	LDR	R2,_Patch_GlobalScan
	BX	R2
;
pws_j:
	PUSH	{R0,LR}
	LDR	R0,_Patch_WorkScan
	BLX	R0
	CMP	R7,#0x26
	POP	{R0,PC}
	
        RSEG    PATCH_WORK_SCAN:CODE:ROOT(1)
	
	BL	pws_j
	
	
	RSEG	PATCH_J:CODE:NOROOT(2)
	
	DATA
_Patch_GlobalScan:
	DC32	Patch_GlobalScan
_Patch_WorkScan:
	DC32	Patch_WorkScan

	END

	





