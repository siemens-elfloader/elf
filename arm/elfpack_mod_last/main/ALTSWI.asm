//�������������� ������ SWI �-�� �� "��������" ����������
//(C)Dimadze 2010

/**********************************************************************************************************/
//int RunSWIFromCashe(void *R0, ...)
/**********************************************************************************************************/
//���������� �� SWI ������ � ����, ����� � �������� ����������,
//���� �� � �������, ����� ����, a SWI ����� �� ���� 0x8XXX, �� ����������
//��������� � ���������������� �����������. � ����� ����� ������� ������ �-��
//���� ������� ������ SWI ����� � ��� 

/*

SetSWIHookInRAMState();

SetSWINumInCashe(148); // int ExecuteFile(WSHDR *filepath, WSHDR *mimetype, void *param);

WSHDR *file_path = AllocWS(256);
wsprintf(file_path, "0:\\execute.elf");

RunSWIFromCashe((void *)file_path, 0, ""); // <--

FreeWS(file_path);

*/

//������������ �������� ������ ���� �-�� ��������
//RAM SWI HOOK, ������� ��������������� ��������� blib 
//��� ����������� �-�� SetSWIHookInRAMState(), ���� �� ���� ��� �� ������ ��������

//�������� �-��, ������� �� ����� ������� �� ����� ����������,
//� � ���� RunSWIFromCashe ���� ���� ������������ �������� (R0), ����� ��� ������?
//����� �����, ����������� ���� � ������ ��������� �� �����:

/*

SetSWIHookInRAMState();
SetSWINumInCashe(0x93); // ����� SWI RebootPhone()
RunSWIFromCashe(0);     // -> ����� ������������

*/

/* ------- 0x8XXX ------- */

/*

SetSWIHookInRAMState();
  
//�������� ����� SWI �-�� (RamScreenBuffer) � ��� (������ �� ���������� ������ ������ �-��)
SetSWINumInCashe(0x80E0);
//�.�. SWI ����� ����� 0x8XXX, �� ������������ �����
int addr = RunSWIFromCashe(0);

*/

//���� �-�� ����������:
//0xBB000000 - �� ��������� �������� RAM ���������� (pLIB_TOP_backup)
//0x�C000000 - �� ��� ����������� ������ ���� �-��

                             CODE32
                            
                             EXTERN  pLIB_TOP_backup
                             EXTERN  pLIB_TOP_cashe
                             EXTERN  FUNC_ABORT

                             RSEG    CODE
                             
                             //������������ ��������: R4,R5,R6,R7
                             
                             PUBLIC  RunSWIFromCashe_ep
                           
          RunSWIFromCashe_ep:
                             
                             //������ ����� �������� ����������
                             LDR     R4, =pLIB_TOP_backup
                             LDR     R4, [R4, #0x00]
                             
                             //�������� �� ������������� ���� ����������
                             CMP     R4,  #0x00
                             MOVEQ   R0,  #0xBB000000
                             BXEQ    LR
                             
                             //������ ����� SWI �-�� �� ����
                             LDR     R5, =pLIB_TOP_cashe
                             LDRH    R5, [R5, #0x00]
                             
                             //�������� �� ��� �-�� 0x8XXX
                             BIC     R6,  R5, #0x0FF0
                             BIC     R6,  R6, #0x000F
                             CMP     R6,  #0x8000
                             BIC     R5,  R5, #0x8000
                             
                             //���������� ������ �� SWI ������ �� ����
                             MOV     R6,  #0x04
                             MUL     R7,  R5, R6
                             
                             LDR     R6, [R4, R7]
                             
                             //����������� ������ ����������� �-��, ���� �-�� ���� 0x8XXX
                             MOVEQ   R0,  R6
                             BXEQ    LR
                             
                             //�������� �� ������������� ����������� �-��
                             CMP     R6,  #0xFFFFFFFF
                             LDREQ   R6, =FUNC_ABORT
                             MOVEQ   R0,  R5
                             MOVEQ   R1,  LR
                             BXEQ    R6
                             
                             //�������� �� ����������� ������ ���� �-��
                             LDR     R5,  =RunSWIFromCashe_ep
                             CMP     R6,  R5
                             MOVEQ   R0,  #0xCC000000
                             BXEQ    LR
                             
                             //������ ����������� �-��
                             BX      R6
                             
                             END
                             
                             
                             
                             



             










                