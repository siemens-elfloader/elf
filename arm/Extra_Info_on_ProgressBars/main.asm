        EXTERN MyDraw
        EXTERN enter1
        
	RSEG	PATCH_ENTER3:DATA:ROOT(2)
        DCD     MyDraw        
        
#ifndef ELKA
	RSEG	PATCH_ENTER1:DATA:ROOT(2)
        DCD     enter1
        DCD     enter2
	RSEG	PATCH_ENTER2:DATA:ROOT(2)
        DCD     enter3
        DCD     enter4
        
        CODE32
        RSEG	CODE
enter2://разделить на 1024
        PUSH    {R0,R1,LR}
        MOV     R1, #0x53
        B       write_param
enter3://без  б, только цифры
        PUSH    {R0,R1,LR}
        MOV     R1, #0
        B       write_param
enter4://передача файла, умножить на 2
        PUSH    {R0,R1,LR}
        MOV     R1, #0x52
write_param:
        SWI     0x80E4//freeram
        STR     R1,[R0,#0x80]
        POP     {R0,R1,PC}
#endif
        
	END