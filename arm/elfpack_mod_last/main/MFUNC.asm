//Модификаторы процедур прошивки
//Modify firmware functions

                            
//unsigned int mfree(void *data)
//Возвращает 0 - память освобождена или не задан указатель, 1 - память уже была освобождена
//Return 0 - memory free or null pointer, 1 - fail without pickoff

#ifdef ELKA

                             CODE16
                             
                             RSEG    MFREE_MOD
                             
                             MOV     R0, #1
                             POP    {R3-R7, PC}

#else
#ifndef NEWSGOLD

                             CODE32

                             RSEG    MFREE_MOD
                             
                             MOV     R0, #1
                             LDMFD   SP!, {R3-R7, PC}
#else
                             CODE32
                             
                             RSEG    MFREE_MOD

#endif
#endif
                           
                             END
                             
                             
                             
                             



             










                