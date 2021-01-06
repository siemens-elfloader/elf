//DH.asm - Draw Handler


                    
                    
                    CODE16  // Врубаем режим THUMB
                    
                    EXTERN dhs
                    EXTERN DHS_drawItems
                    
                    
                    
                    RSEG PATCH_DRAWHANDLER:CODE

                    BLX      dhandler_j32

                    
                    CODE32  // Врубаем режим ARM
                    

                    RSEG PATCH_DRAWHANDLER_J32:CODE
                    
      dhandler_j32:      
                    B        dhandler


       
                    RSEG     CODE
                    
                    PUBLIC   dhandler
                    
         dhandler:

                    PUSH    {R0-R3, LR}
                    
                    //R0 = LCDLAYER
                    
                    BLX      DHS_drawItems 
                    
                    POP     {R0-R3, LR}

                    LDRH     R0, [R0, #0x0C]
                    CMP      R0, #0
                    

                    BX       LR
                    
                    END