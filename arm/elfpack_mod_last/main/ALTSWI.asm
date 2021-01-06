//Альтернативный запуск SWI ф-ии из "запасной" библиотеки
//(C)Dimadze 2010

/**********************************************************************************************************/
//int RunSWIFromCashe(void *R0, ...)
/**********************************************************************************************************/
//Отыскивает по SWI номеру в кеше, адрес в запасной библиотеке,
//если всё в порядке, адрес есть, a SWI номер не есть 0x8XXX, то вызывается
//процедура с соответствующими параметрами. А также перед вызовом данной ф-ии
//надо занести нужный SWI номер в кеш 

/*

SetSWIHookInRAMState();

SetSWINumInCashe(148); // int ExecuteFile(WSHDR *filepath, WSHDR *mimetype, void *param);

WSHDR *file_path = AllocWS(256);
wsprintf(file_path, "0:\\execute.elf");

RunSWIFromCashe((void *)file_path, 0, ""); // <--

FreeWS(file_path);

*/

//Обязательным условием работы этих ф-ий является
//RAM SWI HOOK, который устанавливается загрузкой blib 
//или специальной ф-ей SetSWIHookInRAMState(), хотя бы один раз за запуск телефона

//Допустим ф-ия, которая мы хотим вызвать не имеет параметров,
//а в этой RunSWIFromCashe есть один обязательный параметр (R0), тогда что делать?
//Ответ прост, подставляем ноль и ничего страшного не будет:

/*

SetSWIHookInRAMState();
SetSWINumInCashe(0x93); // номер SWI RebootPhone()
RunSWIFromCashe(0);     // -> Будет перезагрузка

*/

/* ------- 0x8XXX ------- */

/*

SetSWIHookInRAMState();
  
//Поместим номер SWI ф-ии (RamScreenBuffer) в кеш (вплоть до следуещего вызова данной ф-ии)
SetSWINumInCashe(0x80E0);
//Т.к. SWI номер через 0x8XXX, то возвращается адрес
int addr = RunSWIFromCashe(0);

*/

//Если ф-ия возвращает:
//0xBB000000 - то отсутвует запасная RAM библиотека (pLIB_TOP_backup)
//0xСC000000 - то это реверсивный запуск этой ф-ии

                             CODE32
                            
                             EXTERN  pLIB_TOP_backup
                             EXTERN  pLIB_TOP_cashe
                             EXTERN  FUNC_ABORT

                             RSEG    CODE
                             
                             //Используемые регистры: R4,R5,R6,R7
                             
                             PUBLIC  RunSWIFromCashe_ep
                           
          RunSWIFromCashe_ep:
                             
                             //Возьмём адрес запасной библиотеки
                             LDR     R4, =pLIB_TOP_backup
                             LDR     R4, [R4, #0x00]
                             
                             //Проверка на существование этой библиотеки
                             CMP     R4,  #0x00
                             MOVEQ   R0,  #0xBB000000
                             BXEQ    LR
                             
                             //Возьмём номер SWI ф-ии из кеша
                             LDR     R5, =pLIB_TOP_cashe
                             LDRH    R5, [R5, #0x00]
                             
                             //Проверка на тип ф-ии 0x8XXX
                             BIC     R6,  R5, #0x0FF0
                             BIC     R6,  R6, #0x000F
                             CMP     R6,  #0x8000
                             BIC     R5,  R5, #0x8000
                             
                             //Вычисление адреса по SWI номеру из кеша
                             MOV     R6,  #0x04
                             MUL     R7,  R5, R6
                             
                             LDR     R6, [R4, R7]
                             
                             //Возвращение адреса запрошенной ф-ии, если ф-ия типа 0x8XXX
                             MOVEQ   R0,  R6
                             BXEQ    LR
                             
                             //Проверка на существование запрошенной ф-ии
                             CMP     R6,  #0xFFFFFFFF
                             LDREQ   R6, =FUNC_ABORT
                             MOVEQ   R0,  R5
                             MOVEQ   R1,  LR
                             BXEQ    R6
                             
                             //Проверка на реверсивный запуск этой ф-ии
                             LDR     R5,  =RunSWIFromCashe_ep
                             CMP     R6,  R5
                             MOVEQ   R0,  #0xCC000000
                             BXEQ    LR
                             
                             //Запуск запрошенной ф-ии
                             BX      R6
                             
                             END
                             
                             
                             
                             



             










                