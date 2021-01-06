//PCM Audio Stereo Hook (c)ILYA_ZX and fix by Dimadze for CX/M75
//Сорец выковырен из готового патча by Dimadze 

#include "config\config.h"


                        CODE32

                        RSEG PATCH_VREZKA_01:CODE:ROOT
                        
                        LDR     R1, [R0,#0x18]
                        LDR	R0, [PC, #CONST_1] 
                        STR     R1, [R0,#0x64]
                        BL      sub_jump_body_01
                        LDMFD   SP!, {R3,PC}
                        
                        RSEG PATCH_VREZKA_02:CODE:ROOT
                        
                        STR     R1, [R0,#0x68]
                        BL      sub_jump_body_02
                        LDMFD   SP!, {R3,PC}
                        
                        RSEG PATCH_VREZKA_03:CODE:ROOT
                        
                        CMP     LR, LR
#ifndef SGOLD_MP3 
                        LDREQH  R3, [R4,#0x2A]
                        LDREQH  R12, [R2,#8]
                        CMPEQ   LR, LR
                        LDREQH  R3, [R4,#0x1C]
#else
                        LDREQH  R3, [R4,#0x2E]
                        LDREQH  R12, [R2,#8]
                        CMPEQ   LR, LR
                        LDREQH  R3, [R4,#0x20]
#endif

                        LDREQH  R2, [R2]
                        CMPEQ   LR, LR
                        
                        RSEG PATCH_VREZKA_04:CODE:ROOT
                        
                        CMPEQ   R3, R3
                        
                        RSEG PATCH_VREZKA_05:CODE:ROOT
                        
                        BL      sub_jump_body_04
                        NOP
                        
                        RSEG PATCH_VREZKA_06:CODE:ROOT
                        
                        STMFD   SP!, {R3,LR}
                        LDR     R3, =PCM_RAM_OFFSET_1
                        LDRB    R2, [R3]
                        CMP     R2, #0
                        MOVNE   R0, R2
                        MOVNE   R2, #0
                        STRNEB  R2, [R3]
                        B       loc_jump_1
                        
                        RSEG PATCH_VREZKA_07:CODE:ROOT
                        
                        MOV     R12, #0xA0
                        MOV     R1, #0
                        CMP     R1, R12
                        LDRCCB  R2, [R3,R1]
                        ADDCC   LR, R0, R1,LSL#2
                        ADDCC   R1, R1, #1
                        EORCC   R2, R2, #0x80
                        MOVCC   R2, R2,LSL#8
                        STRCC   R2, [LR]
                        
                        RSEG PATCH_VREZKA_08:CODE:ROOT
                        
                        SUB     R1, R1, #0xA0
                        
                        RSEG PATCH_VREZKA_09:CODE:ROOT
                        
                        BL      sub_jump_body_03
                        STR     R1, [R5,#0x20]
#ifndef SGOLD_MP3 
                        LDRH    R1, [R4,#0x34]
#else
                        LDRH    R1, [R4,#0x38]
#endif
                        
                        MOV     R0, #0
                        STR     R1, [R5,#0x2C]
                        STRB    R0, [R6]
                        MOVEQ   R0, #0xA0
                        STR     R0, [R5,#0x24]
                        B       loc_jump_2
                        
                        RSEG PATCH_VREZKA_10:CODE:ROOT
                        
                        B       sub_jump_body_44
                        
       vrezka10_jump_1:
                        
                        RSEG PATCH_VREZKA_11:CODE:ROOT
                        
                        CMP     R1, #0x39
                        LDRNE   R4, =PCM_RAM_OFFSET_2
                        LDRNEB  R5, [R4]
                        CMPNE   R5, #0
                        MOVNE   R1, R5
                        MOVNE   R5, #0
                        STRNEB  R5, [R4]
                        B       loc_jump_3
                        
                        RSEG PATCH_VREZKA_12:CODE:ROOT
                        
                        B       vrezka14_jump_1
                        
                        RSEG PATCH_VREZKA_13:CODE:ROOT
                        
                        MOV     R4, #2
                        
                        RSEG PATCH_VREZKA_14:CODE:ROOT
                        
                        B       vrezka14_jump_2
                        
        vrezka14_jump_1:
                    
                        CMP     R1, #0
                        LDRNE   R3, [PC, #CONST_2] 
                        LDRNEB  R0, [R3]
                        CMPNE   R0, #0
                        BEQ     loc_jump_4
                        MOV     R1, R0
                        STRB    R8, [R3]
                        B       loc_jump_4
                        DC32    PCM_RAM_OFFSET_3
                        
        vrezka14_jump_2:
                     
                     
                     
                     
                        RSEG PATCH_JUMP_01:CODE:ROOT
                        
            loc_jump_1:  
            
                        RSEG PATCH_JUMP_02:CODE:ROOT
                        
            loc_jump_2:  
            
                        RSEG PATCH_JUMP_03:CODE:ROOT
                        
            loc_jump_3:
            
                        RSEG PATCH_JUMP_04:CODE:ROOT
                        
            loc_jump_4:
                        
                        
                        
                        
                        
                        RSEG PATCH_BODY:CODE:ROOT
                        
                        
                        

       sub_jump_body_01:
       
                        STMFD   SP!, {R4,R5,LR}
                        MOV     R4, R0
                        MOV     R5, R1
                        LDRH    R1, [R4,#0x28]
                        ADD     R0, R5, #0xC
                        BL      sub_jump_body_18
                        LDRH    R0, [R4,#0x2C]
                        CMP     R0, #2
                        MOVEQ   R0, #0x294
                        STREQH  R0, [R5,#0x12]
                        LDMFD   SP!, {R4,R5,LR}
                        BX      LR



      sub_jump_body_02:
      
                        STMFD   SP!, {LR}
                        MOV     R2, R1
                        LDRH    R1, [R0,#0x28]
                        ADD     R0, R2, #0xC
                        BL      sub_jump_body_31
                        B       sub_jump_body_06

     sub_jump_body_03:

                        STMFD   SP!, {LR}
                        B       sub_jump_body_05

     sub_jump_body_04:
     
                        STMFD   SP!, {LR}
                        MOV     R0, R1

      sub_jump_body_05:
      
                        BL      sub_jump_body_07

      sub_jump_body_06:
                        
                        LDMFD   SP!, {LR}
                        BX      LR


      sub_jump_body_07:
      
                        LDR	R1, [PC, #CONST_3] 
                        CMP     R0, #0x1F40
                        BEQ     sub_jump_body_08
                        
                   //   MOVL    R2, 0x2B11       
                        MOV     R2, #0x11
                        ORR	R2, R2, #0x2B00
                        
                        CMP     R0, R2
                        BEQ     sub_jump_body_09
                        
                   //   MOVL    R2, 0x2EE0
                        MOV	R2, #0xE0
                        ORR	R2, R2, #0x2E00
                        
                        CMP     R0, R2
                        BEQ     sub_jump_body_11
                        CMP     R0, #0x3E80
                        BEQ     sub_jump_body_12
                        
                   //   MOVL    R2, 0x5622
                        MOV	R2, #0x22
                        ORR     R2, R2, #0x5600
                        
                        CMP     R0, R2
                        BEQ     sub_jump_body_13
                        
                   //   MOVL    R2, 0x5DC0
                        MOV	R2, #0xC0
                        ORR     R2, R2, #0x5D00
                        
                        CMP     R0, R2
                        BEQ     sub_jump_body_14
                        CMP     R0, #0x7D00
                        BEQ     sub_jump_body_15
                        
                   //   MOVL    R2, 0xAC44
                        MOV	R2, #0x44
                        ORR     R2, R2, #0xAC00
                        
                        CMP     R0, R2
                        BEQ     sub_jump_body_16
                        
                   //   MOVL    R2, 0xBB80
                        MOV	R2, #0x80
                        ORR     R2, R2, #0xBB00
                   
                        CMP     R0, R2
                        BEQ     sub_jump_body_17
                        BX      LR

      sub_jump_body_08:
      
                        MOV     R0, #0
                        B       sub_jump_body_10

      sub_jump_body_09:

                        MOV     R0, #1

      sub_jump_body_10:

                        STRB    R0, [R1]
                        BX      LR

      sub_jump_body_11:

                        MOV     R0, #2
                        B       sub_jump_body_10

      sub_jump_body_12:

                        MOV     R0, #3
                        B       sub_jump_body_10

      sub_jump_body_13:

                        MOV     R0, #4
                        B       sub_jump_body_10

      sub_jump_body_14:

                        MOV     R0, #5
                        B       sub_jump_body_10

      sub_jump_body_15:

                        MOV     R0, #6
                        B       sub_jump_body_10

      sub_jump_body_16:
      
                        MOV     R0, #7
                        B       sub_jump_body_10

      sub_jump_body_17:
      
                        MOV     R0, #8
                        B       sub_jump_body_10
                        
                        DC32    PCM_RAM_OFFSET_1
                        


      sub_jump_body_18:
      
                   //   MOVL    R2, 0x3F7A
                        MOV	R2, #0x7A
                        ORR     R2, R2, #0x3F00
                        
                   //   MOVL    R3, 0x659
                        MOV	R3, #0x59
                        ORR     R3, R3, #0x0600
                   
                        CMP     R1, #0x1F40
                        BEQ     sub_jump_body_19
                        
                   //   MOVL    R12, 0x2B11
                        MOV	R12, #0x11
                        ORR     R12, R12, #0x2B00
                        
                        CMP     R1, R12
                        BEQ     sub_jump_body_20
                        
                   //   MOVL    R12, 0x2EE0
                        MOV	R12, #0xE0
                        ORR	R12, R12, #0x2E00
                        
                        CMP     R1, R12
                        BEQ     sub_jump_body_21
                        CMP     R1, #0x3E80
                        BEQ     sub_jump_body_24
                        
                   //   MOVL    R12, 0x5622
                        MOV	R12, #0x22
                        ORR	R12, R12, #0x5600
                        
                        CMP     R1, R12
                        BEQ     sub_jump_body_25
                        
                   //   MOVL    R12, 0x5DC0
                        MOV	R12, #0xC0
                        ORR	R12, R12, #0x5D00
                        
                        CMP     R1, R12
                        BEQ     sub_jump_body_27
                        CMP     R1, #0x7D00
                        BEQ     sub_jump_body_28
                        
                   //   MOVL    R12, 0xAC44
                        MOV	R12, #0x44
                        ORR	R12, R12, #0xAC00
                        
                        CMP     R1, R12
                        BEQ     sub_jump_body_29
                        
                    //  MOVL    R12, 0xBB80
                        MOV	R12, #0x80
                        ORR	R12, R12, #0xBB00
                        
                        CMP     R1, R12
                        BEQ     sub_jump_body_30
                        BX      LR

      sub_jump_body_19:
      
                        MOV     R1, #0x20
                        B       sub_jump_body_22

      sub_jump_body_20:
      
                        ADD     R1, R3, #0xB60
                        B       sub_jump_body_26

      sub_jump_body_21:
      
                        MOV     R1, #0x30

      sub_jump_body_22:
      
                        ORR     R1, R1, #0x1000

      sub_jump_body_23:
      
                        STRH    R1, [R0]
                        STRH    R3, [R0,#2]
                        BX      LR

      sub_jump_body_24:
      
                        MOV     R1, #0x1040
                        B       sub_jump_body_23

      sub_jump_body_25:
      
                    //  MOVL    R1, 0x1372
                        MOV	R1, #0x72
                        ORR	R1, R1, #0x1300
                        
      sub_jump_body_26:
      
                        STRH    R1, [R0]
                        STRH    R2, [R0,#2]
                        BX      LR

      sub_jump_body_27:
      
                        MOV     R1, #0x60
                        B       sub_jump_body_22

      sub_jump_body_28:

                        MOV     R1, #0x1080
                        B       sub_jump_body_23

      sub_jump_body_29:
      
                    //  MOVL    R1, 0x16E4
                        MOV	R1, #0xE4
                        ORR	R1, R1, #0x1600
                        
                        B       sub_jump_body_26

      sub_jump_body_30:
      
                        MOV     R1, #0x10C0
                        B       sub_jump_body_23






      sub_jump_body_31:
      
                        STMFD   SP!, {R4}
                        
                    //  MOVL    R2, 0x11B9
                        MOV	R2, #0xB9
                        ORR	R2, R2, #0x1100
                    
                   //   MOVL    R3, 0x3F7A
                        MOV	R3, #0x7A
                        ORR	R3, R3, #0x3F00
                   
                        SUB     R12, R2, #0xB60
                        CMP     R1, #0x1F40
                        BEQ     sub_jump_body_32
                        
                   //   MOVL    R4, 0x2B11
                        MOV	R4, #0x11
                        ORR	R4, R4, #0x2B00
                        
                        CMP     R1, R4
                        BEQ     sub_jump_body_33
                        
                    //  MOVL    R4, 0x2EE0
                        MOV	R4, #0xE0
                        ORR	R4, R4, #0x2E00
                        
                        
                        CMP     R1, R4
                        BEQ     sub_jump_body_34
                        CMP     R1, #0x3E80
                        BEQ     sub_jump_body_32
                        
                    //  MOVL    R4, 0x5622
                        MOV	R4, #0x22
                        ORR	R4, R4, #0x5600
                        
                        CMP     R1, R4
                        BEQ     sub_jump_body_35
                        
                    //  MOVL    R4, 0x5DC0
                        MOV	R4, #0xC0
                        ORR	R4, R4, #0x5D00
                        
                        CMP     R1, R4
                        BEQ     sub_jump_body_37
                        CMP     R1, #0x7D00
                        BEQ     sub_jump_body_38
                        
                  //    MOVL    R4, 0xAC44
                        MOV	R4, #0x44
                        ORR	R4, R4, #0xAC00
                        
                        CMP     R1, R4
                        BEQ     sub_jump_body_39
                        
                   //   MOVL    R4, 0xBB80
                        MOV	R4, #0x80
                        ORR	R4, R4, #0xBB00
                        
                        CMP     R1, R4
                        BEQ     sub_jump_body_40
                        B       sub_jump_body_43

      sub_jump_body_32:
      
                        MOV     R1, #0x20
                        B       sub_jump_body_41

      sub_jump_body_33:
      
                        STRH    R2, [R0]
                        MOV     R1, R3,LSL#1
                        STRH    R1, [R0,#2]
                        B       sub_jump_body_43

      sub_jump_body_34:
      
                        MOV     R1, #0x18
                        B       sub_jump_body_41

      sub_jump_body_35:
      
                         STRH    R2, [R0]

      sub_jump_body_36:
      
                         STRH    R3, [R0,#2]
                         B       sub_jump_body_43

      sub_jump_body_37:
      
                         MOV     R1, #0x30
                         B       sub_jump_body_41

      sub_jump_body_38:
      
                         MOV     R1, #0x1040
                         B       sub_jump_body_42

      sub_jump_body_39:
      
                     //  MOVL   R1, 0x1372
                         MOV	R1, #0x72
                         ORR	R1, R1, #0x1300
                     
                         STRH    R1, [R0]
                         B       sub_jump_body_36

      sub_jump_body_40:
      
                         MOV     R1, #0x60

      sub_jump_body_41:
      
                         ORR     R1, R1, #0x1000

      sub_jump_body_42:
      
                         STRH    R1, [R0]
                         STRH    R12, [R0,#2]

      sub_jump_body_43:
      
                         LDMFD   SP!, {R4}
                         BX      LR

                         DC32    0xFFFFFFFF

      sub_jump_body_44:
      
                         LDR     R0, [R4,#0x80]
                         CMP     R0, #0
                         BEQ     vrezka10_jump_1
                         LDR     R0, [R0]
                         BLX     R0
                         MOV     R0, #1
                         LDMFD   SP!, {R2-R4,PC}
                         
          
                         END
                        
                        



                        
                        
                        
