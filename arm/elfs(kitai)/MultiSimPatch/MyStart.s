#pragma data_alignment=2


//#include ADRASM
#include "adr_asm.inc"

;  PUBLIC  RAM_F14
;  PUBLIC  RAM_SPN
;  PUBLIC  RAM_IMSI
;  PUBLIC  RAM_LOCI
;  PUBLIC  RAM_FPLMN
;  PUBLIC  LAST_SIM_BUF_POINTER
;  PUBLIC  LAST_LGP_BUF
#ifndef NEWSGOLD       
  PUBLIC  RAM_STBY
#endif

  CODE32
  rseg Menu_Hook  
  EXTERN ShowMenu

;  DCB "ELSE_DEVICE_MAN"

  DCD ShowMenu

  CODE16 
   rseg PATCH_BODY
       EXTERN  CODE16 SIM_Cmd_Hook
       IMPORT SIM_Rsp_Hook
       IMPORT LgpHook
       IMPORT MultisimINIT
#ifndef NEWSGOLD       
    IMPORT SaveHTTPProfile
    IMPORT SaveSMSProfile    
#endif
	   
;org PATCH_BASE	   
MsgDispatchRpl:
				push	{LR}
				push	{R0-R7}
				LDR		r4,=SIM_Rsp_Hook
                                BLX		r4
				pop		{R0-R7}
#ifndef NEWSGOLD
	LDR     R3, =GSM_ALGHORITM_BUFFER
	LDR     R6, =off_A84F6208
	LDRH    R1, [R3,#0x2]
	SUB     R6, #0x28
	MOV     R5, #1
	LSL     R2, R1, #0x18
#else
				LDR		R1, =GSM_ALGHORITM_BUFFER
				LDR		R6, =off_A84F6208
				LDR     R2, [R1,#4]
				MOV     R4, #4
				LSL     R2, R2, #0x18
                                LSR     R2, R2, #0x18

#endif
  pop     {PC}


Cmd_Hook1:
				mov		r6,lr
				LDR     R2, [SP,#0x1C]
				LDR     R1, [SP,#0x20]
				MOV     R0, #0
				STR     R4, [SP,#0xC]
        			LDR		r4,=SIM_Cmd_Hook
        			blx		r4
				mov		pc,r6

Cmd_Hook2:
				mov		r6,lr
                                STR     R1, [SP,#4]
                                LDR     R1, [SP,#0x20]
				LDR     R2, [SP,#0x1C]
				MOV     R0, #0
				STR     R4, [SP,#0x14]
        			LDR		r4,=SIM_Cmd_Hook
        			blx		r4
				mov		pc,r6

#ifndef NEWSGOLD

        CODE32
SetHTTPProfilel:
                                MOV     R3, #0
                                STRH    R0, [R1]
#ifdef SGOLD75
	STMEA   SP, {R2,R3}
#else
                                STR     R3, [SP]
                                STR     R3, [SP,#4]
#endif
                                STMFD   SP!, {R0-R7,LR}
        			LDR		r4,=SaveHTTPProfile
        			blx		r4
                                LDMFD   SP!, {R0-R7,PC}
#endif

       CODE16
  rseg  csa1
call_sim_access1:
				LDR     R2, =Cmd_Hook1
				BLX     r2
				b		csa1_e

  rseg  csa1_1:CODE(1)
csa1_e:

  rseg  csa2
call_sim_access2:
				LDR     R2, =Cmd_Hook2
				BLX     r2
				b		csa2_e

  rseg  csa2_1:CODE(1)
csa2_e:
 
  rseg Msg_dispatch:CODE(1)

MyMsgDispatch:
  CODE16
#ifndef NEWSGOLD
#else
                                push	{R4-R6,LR}

#endif
				LDR    r4,=MsgDispatchRpl
                                BLX r4
				b		Msg_dispatch_e
                                
  rseg Msg_dispatch_1:CODE(1)
Msg_dispatch_e:
#ifndef NEWSGOLD
;  rseg  GetLgp
;GetLgp_l1:
;                                LDR     R3, =LgpHook
;				BLX     r3
;				pop     {r4,pc}


  rseg SetHTTPProfile:CODE(2)
  CODE32

				LDR    r3,=SetHTTPProfilel
                                BLX r3
				b		SetHTTPProfile_e
                                
  rseg SetHTTPProfile_1:CODE(2)
SetHTTPProfile_e:
  CODE16
  rseg SetSMSProfile:CODE(1)
	push	{r7,lr}
	ldr	r7,=SaveSMSProfile
	blx	r7
	pop	{r7,pc}
  #endif
  END


