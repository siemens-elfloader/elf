;AcesseoryMon (c)vGamBIT
          NAME ADIT
          PUBLIC GetAccNum
          RSEG CODE:CODE
          ARM
  GetAccNum: ; ���������� ����� �������
          PUSH {LR}
          SWI 0x80D0
          LDR R0,[R0,#8] ;���� �����
          LDRB R0,[R0,#4]
          POP {PC}
          
          PUBLIC GetAccName
          RSEG CODE:CODE
          ARM
  GetAccName:  ; ���������� ��� �������
          SWI 0x80D0
          LDR R0,[R0,#8] ;���� �����
          LDR R1,=0xA0000000 ;��������� ����� �� ��� �����?!
          TST R0,R1
          LDRNE R0,[R0,#12] ;���� ����� �� ���������
          ADREQ R0,ERR   ;���� ��� �� ����� ���� �������� :) 
          BX LR
          DATA
          ERR: DC8 "No device"
         
          END
          
;extern char * GetAccName();
;extern int GetAccNum();