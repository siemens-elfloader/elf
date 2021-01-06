        THUMB
        CODE16
        
	RSEG	PATCH_ENTER1:CODE(1)
        MOV     R1,#0
        LDR     R0, f_addr
        BLX     R0
        
	RSEG	PATCH_ENTER2:DATA:ROOT(2)
        //компилятор ниасилил укоротить функцию, ну и хорошо :)


/*                                ДО
seg004:A0326D70 B0 B5                       PUSH    {R4,R5,R7,LR}
seg004:A0326D72 0C 1C                       ADDS    R4, R1, #0
seg004:A0326D74 15 1C                       ADDS    R5, R2, #0
seg004:A0326D76 FF F7 C9 FF                 BL      sub_A0326D0C
seg004:A0326D7A 43 1C                       ADDS    R3, R0, #1
seg004:A0326D7C 27 D0                       BEQ     loc_A0326DCE
seg004:A0326D7E 61 49                       LDR     R1, =aCklk_ck_mainmn
seg004:A0326D80 06 2C                       CMP     R4, #6          ; switch 6 cases
seg004:A0326D82 1F D2                       BCS     loc_A0326DC4    ; default
seg004:A0326D82                                                     ; jumptable A0326D8A case 1
seg004:A0326D84 01 A3                       ADR     R3, jpt_A0326D8A
seg004:A0326D86 1B 5D                       LDRB    R3, [R3,R4]
seg004:A0326D88 5B 00                       LSLS    R3, R3, #1
seg004:A0326D8A 9F 44                       ADD     PC, R3          ; switch jump
seg004:A0326D8A             ; ---------------------------------------------------------------------------
seg004:A0326D8C 02          jpt_A0326D8A    DCB 2                   ; DATA XREF: seg004:A0326D84o
seg004:A0326D8C                                                     ; jump table for switch statement
seg004:A0326D8D 1B                          DCB 0x1B
seg004:A0326D8E 07                          DCB 7
seg004:A0326D8F 0C                          DCB 0xC
seg004:A0326D90 11                          DCB 0x11
seg004:A0326D91 16                          DCB 0x16
seg004:A0326D92             ; ---------------------------------------------------------------------------
seg004:A0326D92
seg004:A0326D92             loc_A0326D92                            ; CODE XREF: seg004:A0326D8Aj
seg004:A0326D92 34 23                       MOVS    R3, #0x34 ; '4' ; jumptable A0326D8A case 0
seg004:A0326D94 58 43                       MULS    R0, R3
seg004:A0326D96 40 18                       ADDS    R0, R0, R1
seg004:A0326D98 80 6A                       LDR     R0, [R0,#0x28]
seg004:A0326D9A B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326D9C             ; ---------------------------------------------------------------------------
seg004:A0326D9C
seg004:A0326D9C             loc_A0326D9C                            ; CODE XREF: seg004:A0326D8Aj
seg004:A0326D9C 34 23                       MOVS    R3, #0x34 ; '4' ; jumptable A0326D8A case 2
seg004:A0326D9E 58 43                       MULS    R0, R3
seg004:A0326DA0 40 18                       ADDS    R0, R0, R1
seg004:A0326DA2 00 6A                       LDR     R0, [R0,#0x20]
seg004:A0326DA4 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DA6             ; ---------------------------------------------------------------------------
seg004:A0326DA6
seg004:A0326DA6             loc_A0326DA6                            ; CODE XREF: seg004:A0326D8Aj
seg004:A0326DA6 34 23                       MOVS    R3, #0x34 ; '4' ; jumptable A0326D8A case 3
seg004:A0326DA8 58 43                       MULS    R0, R3
seg004:A0326DAA 40 18                       ADDS    R0, R0, R1
seg004:A0326DAC 40 6A                       LDR     R0, [R0,#0x24]
seg004:A0326DAE B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DB0             ; ---------------------------------------------------------------------------
seg004:A0326DB0
seg004:A0326DB0             loc_A0326DB0                            ; CODE XREF: seg004:A0326D8Aj
seg004:A0326DB0 34 23                       MOVS    R3, #0x34 ; '4' ; jumptable A0326D8A case 4
seg004:A0326DB2 58 43                       MULS    R0, R3
seg004:A0326DB4 40 18                       ADDS    R0, R0, R1
seg004:A0326DB6 C0 6A                       LDR     R0, [R0,#0x2C]
seg004:A0326DB8 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DBA             ; ---------------------------------------------------------------------------
seg004:A0326DBA
seg004:A0326DBA             loc_A0326DBA                            ; CODE XREF: seg004:A0326D8Aj
seg004:A0326DBA 34 23                       MOVS    R3, #0x34 ; '4' ; jumptable A0326D8A case 5
seg004:A0326DBC 58 43                       MULS    R0, R3
seg004:A0326DBE 40 18                       ADDS    R0, R0, R1
seg004:A0326DC0 00 6B                       LDR     R0, [R0,#0x30]
seg004:A0326DC2 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DC4             ; ---------------------------------------------------------------------------
seg004:A0326DC4
seg004:A0326DC4             loc_A0326DC4                            ; CODE XREF: seg004:A0326D82j
seg004:A0326DC4                                                     ; seg004:A0326D8Aj
seg004:A0326DC4 34 23                       MOVS    R3, #0x34 ; '4' ; default
seg004:A0326DC4                                                     ; jumptable A0326D8A case 1
seg004:A0326DC6 58 43                       MULS    R0, R3
seg004:A0326DC8 40 18                       ADDS    R0, R0, R1
seg004:A0326DCA C0 69                       LDR     R0, [R0,#0x1C]
seg004:A0326DCC B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DCE             ; ---------------------------------------------------------------------------
seg004:A0326DCE
seg004:A0326DCE             loc_A0326DCE                            ; CODE XREF: seg004:A0326D7Cj
seg004:A0326DCE 28 1C                       ADDS    R0, R5, #0
seg004:A0326DD0 B0 BD                       POP     {R4,R5,R7,PC}
*/


/*                                ПОСЛЕ
seg004:A0326D70             loc_A0326D70                            ; CODE XREF: seg004:A0326DD6j
seg004:A0326D70 B0 B5                       PUSH    {R4,R5,R7,LR}
seg004:A0326D72 0C 1C                       ADDS    R4, R1, #0
seg004:A0326D74 15 1C                       ADDS    R5, R2, #0
seg004:A0326D76 FF F7 C9 FF                 BL      sub_A0326D0C
seg004:A0326D7A 47 1C                       ADDS    R7, R0, #1
seg004:A0326D7C 19 D0                       BEQ     loc_A0326DB2
seg004:A0326D7E 01 21                       MOVS    R1, #1
seg004:A0326D80 60 4B                       LDR     R3, =aCklk_ck_mainmn
seg004:A0326D82 98 47                       BLX     R3              ; "CKLK_CK_MAINMNU"
seg004:A0326D84 40 18                       ADDS    R0, R0, R1
seg004:A0326D86 3B 1C                       ADDS    R3, R7, #0
seg004:A0326D88 06 2C                       CMP     R4, #6          ; switch 6 cases
seg004:A0326D8A 10 D2                       BCS     loc_A0326DAE    ; default
seg004:A0326D8A                                                     ; jumptable A0326D92 case 1
seg004:A0326D8C
seg004:A0326D8C             jpt_A0326D8A
seg004:A0326D8C 01 A3                       ADR     R3, jpt_A0326D92
seg004:A0326D8E 1B 5D                       LDRB    R3, [R3,R4]
seg004:A0326D90 5B 00                       LSLS    R3, R3, #1
seg004:A0326D92 9F 44                       ADD     PC, R3          ; switch jump
seg004:A0326D92             ; ---------------------------------------------------------------------------
seg004:A0326D94 02          jpt_A0326D92    DCB 2                   ; DATA XREF: seg004:jpt_A0326D8Ao
seg004:A0326D94                                                     ; jump table for switch statement
seg004:A0326D95 0C                          DCB 0xC
seg004:A0326D96 04                          DCB 4
seg004:A0326D97 06                          DCB 6
seg004:A0326D98 08                          DCB 8
seg004:A0326D99 0A                          DCB 0xA
seg004:A0326D9A             ; ---------------------------------------------------------------------------
seg004:A0326D9A
seg004:A0326D9A             loc_A0326D9A                            ; CODE XREF: seg004:A0326D92j
seg004:A0326D9A 80 6A                       LDR     R0, [R0,#0x28]  ; jumptable A0326D92 case 0
seg004:A0326D9C B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326D9E             ; ---------------------------------------------------------------------------
seg004:A0326D9E
seg004:A0326D9E             loc_A0326D9E                            ; CODE XREF: seg004:A0326D92j
seg004:A0326D9E 00 6A                       LDR     R0, [R0,#0x20]  ; jumptable A0326D92 case 2
seg004:A0326DA0 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DA2             ; ---------------------------------------------------------------------------
seg004:A0326DA2
seg004:A0326DA2             loc_A0326DA2                            ; CODE XREF: seg004:A0326D92j
seg004:A0326DA2 40 6A                       LDR     R0, [R0,#0x24]  ; jumptable A0326D92 case 3
seg004:A0326DA4 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DA6             ; ---------------------------------------------------------------------------
seg004:A0326DA6
seg004:A0326DA6             loc_A0326DA6                            ; CODE XREF: seg004:A0326D92j
seg004:A0326DA6 C0 6A                       LDR     R0, [R0,#0x2C]  ; jumptable A0326D92 case 4
seg004:A0326DA8 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DAA             ; ---------------------------------------------------------------------------
seg004:A0326DAA
seg004:A0326DAA             loc_A0326DAA                            ; CODE XREF: seg004:A0326D92j
seg004:A0326DAA 00 6B                       LDR     R0, [R0,#0x30]  ; jumptable A0326D92 case 5
seg004:A0326DAC B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DAE             ; ---------------------------------------------------------------------------
seg004:A0326DAE
seg004:A0326DAE             loc_A0326DAE                            ; CODE XREF: seg004:A0326D8Aj
seg004:A0326DAE                                                     ; seg004:A0326D92j
seg004:A0326DAE C0 69                       LDR     R0, [R0,#0x1C]  ; default
seg004:A0326DAE                                                     ; jumptable A0326D92 case 1
seg004:A0326DB0 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DB2             ; ---------------------------------------------------------------------------
seg004:A0326DB2
seg004:A0326DB2             loc_A0326DB2                            ; CODE XREF: seg004:A0326D7Cj
seg004:A0326DB2 28 1C                       ADDS    R0, R5, #0
seg004:A0326DB4 B0 BD                       POP     {R4,R5,R7,PC}
seg004:A0326DB4             ; ---------------------------------------------------------------------------
seg004:A0326DB6 FF                          DCB 0xFF
seg004:A0326DB7 FF                          DCB 0xFF
seg004:A0326DB8 FF                          DCB 0xFF
seg004:A0326DB9 FF                          DCB 0xFF
seg004:A0326DBA FF                          DCB 0xFF
seg004:A0326DBB FF                          DCB 0xFF
seg004:A0326DBC FF                          DCB 0xFF
seg004:A0326DBD FF                          DCB 0xFF
seg004:A0326DBE FF                          DCB 0xFF
seg004:A0326DBF FF                          DCB 0xFF
seg004:A0326DC0 FF                          DCB 0xFF
seg004:A0326DC1 FF                          DCB 0xFF
seg004:A0326DC2 FF                          DCB 0xFF
seg004:A0326DC3 FF                          DCB 0xFF
seg004:A0326DC4 FF                          DCB 0xFF
seg004:A0326DC5 FF                          DCB 0xFF
seg004:A0326DC6 FF                          DCB 0xFF
seg004:A0326DC7 FF                          DCB 0xFF
seg004:A0326DC8 FF                          DCB 0xFF
seg004:A0326DC9 FF                          DCB 0xFF
seg004:A0326DCA FF                          DCB 0xFF
seg004:A0326DCB FF                          DCB 0xFF
seg004:A0326DCC FF                          DCB 0xFF
seg004:A0326DCD FF                          DCB 0xFF
seg004:A0326DCE FF                          DCB 0xFF
seg004:A0326DCF FF                          DCB 0xFF
seg004:A0326DD0 FF                          DCB 0xFF
seg004:A0326DD1 FF                          DCB 0xFF
*/
        //дальше не знаю как ^^^ перевести в код для iar, поэтому записываю бинарником :(
        //если кто знает - намыльте мне плиз, или сюда запишите ;-)
        DCD     0x1C0CB5B0
        DCD     0xF7FF1C15
        DCD     0x1C47FFC9
        DCD     0x2101D019
        DCD     0x47984B60
        DCD     0x1C3B1840
        DCD     0xD2102C06
        DCD     0x5D1BA301
        DCD     0x449F005B
        DCD     0x06040C02
        DCD     0x6A800A08
        DCD     0x6A00BDB0
        DCD     0x6A40BDB0
        DCD     0x6AC0BDB0
        DCD     0x6B00BDB0
        DCD     0x69C0BDB0
        DCD     0x1C28BDB0
        DCD     0xFFFFBDB0
        /*DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCD     0xFFFFFFFF
        DCB     0xFF
        DCB     0xFF*/
        EXTERN  OldShCutCheck
        //на освобожденное место запишем функцию сохранения имени шортката для последующего определения пути к эльфу
run_shcut:
        PUSH    {R1-R6,LR}
        MOV     R7,R0
        BL      OldShCutCheck
        POP     {R1-R6,PC}
        
        RSEG	PATCH_SHORTCUT_RUN:CODE(2)
        BL      run_shcut+1
        
        
        
        //точки входа
	RSEG	PATCH_ENTER3:CODE(1)
        MOV     R1,#1
        LDR     R3, f_addr
        BLX     R3
        
	RSEG	PATCH_ENTER4:CODE(1)
        MOV     R1,#1
        LDR     R3, f_addr
        BLX     R3
        
	RSEG	PATCH_ENTER5:CODE(1)
        MOV     R1,#1
        LDR     R3, f_addr
        BLX     R3
        
	RSEG	PATCH_ENTER6:CODE(1)
        MOV     R1,#1
        LDR     R3, f_addr
        BLX     R3
        
	RSEG	PATCH_ENTER7:CODE(1)
        MOV     R1,#1
        LDR     R3, f_addr
        BLX     R3
        
	RSEG	PATCH_TABLE_ADDR:DATA:ROOT(2)
f_addr  DCD	start




//таблица шорткатов для запуска с горячих клавиш
	RSEG	PATCH_ENTER_FAST_RUN:CODE(1)
        NOP
        LDR     R1, f_table_addr
        BLX     R1
        
	RSEG	PATCH_FAST_TABLE_ADDR:DATA:ROOT(2)
f_table_addr
        DCD	load_fr_table



//таблица со всеми шорткатами, их адресами и их ид лэнгпака
	RSEG	CODE
start:
        PUSH    {R2-R7,LR}
        //проверка входного параметра R1
        CMP     R1,#0
        BEQ     first//если R1=0 -> первая точка входа
        MOV     R3, #0x34
        MUL     R0, R3
        B       getaddr
first:
        MOV     R0, #0x34
        MUL     R0, R4
getaddr:
        PUSH    {R0,R2,R3}
        BLX     return_addr
        MOV     R1,R0
        POP     {R0,R2,R3}
        POP     {R2-R7,PC}
        
load_fr_table:
        PUSH    {R2-R7,LR}
        MOV     R1, #0x2F
        ORR     R0, R1
        PUSH    {R0}
        BLX     load_fast_run_addr
        MOV     R1,R0
        POP     {R0,R2-R7,PC}
        
        EXTERN  run_elf2
        PUBLIC	run_elf
run_elf:
        PUSH    {R0-R7,LR}
        MOV     R0,R7
        BLX     run_elf2
        POP     {R0-R7,PC}
        
        
        
        EXTERN return_addr
        EXTERN load_fast_run_addr
        
        RSEG	PATCH_MAX_COUNT1:CODE(1)
        MOV     R6,#0xFF
        RSEG	PATCH_MAX_COUNT2:CODE(1)
        MOV     R4,#0xFF
        RSEG	PATCH_MAX_COUNT3:CODE(1)
        MOV     R5,#0xFF
        
        RSEG	CODE:DATA:ROOT(2)
        PUBLIC	shortcuts_filename
shortcuts_filename:
	DCB	"0:\\Zbin\\etc\\shortcuts.dat",0
        
        PUBLIC	shortcut_names_filename
shortcut_names_filename:
	DCB	"0:\\Zbin\\etc\\shortcut_names.dat",0
        
        PUBLIC	fast_run_filename
fast_run_filename:
	DCB	"0:\\Zbin\\etc\\fr_shortcuts.dat",0
        
        PUBLIC	shortcuts_last_name
shortcuts_last_name:
	DCB	"XTRA_NO_APPLICA",0
        
        PUBLIC	msg_error
msg_error:
	DCB	"error!",0
        
	END