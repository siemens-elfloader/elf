      
                    CODE32
                    
                    EXTERN empty_func
                    
                    RSEG FIX_COMMAND:CODE
                    
                    MOV R0, #0x00
                   
                    RSEG VREZKA:CODE
                    
                    BL   patch_body
                    
                    
                    
                    RSEG PATCH_BODY:CODE
                    
                    PUBLIC  patch_body

        patch_body:
        
                   PUSH {R0-R2, R4-R12, LR}
                   
                   
                   BL    empty_func
                   
                   MOV   R3, R0
                   
                   POP  {R0-R2, R4-R12, PC}
                   
                   END
                    
                    
                    

                
                   END

                    
                    
                    
