;AcesseoryMon (c)vGamBIT
          NAME ADIT
          PUBLIC GetAccNum
          RSEG CODE:CODE
          ARM
  GetAccNum: ; Возвращает номер девайса
          PUSH {LR}
          SWI 0x80D0
          LDR R0,[R0,#8] ;ищем адрес
          LDRB R0,[R0,#4]
          POP {PC}
          
          PUBLIC GetAccName
          RSEG CODE:CODE
          ARM
  GetAccName:  ; Возвращает имя девайса
          SWI 0x80D0
          LDR R0,[R0,#8] ;ищем адрес
          LDR R1,=0xA0000000 ;проверяем адрес ли это вобше?!
          TST R0,R1
          LDRNE R0,[R0,#12] ;если адрес то оставляем
          ADREQ R0,ERR   ;если нет то пишем наше название :) 
          BX LR
          DATA
          ERR: DC8 "No device"
         
          END
          
;extern char * GetAccName();
;extern int GetAccNum();