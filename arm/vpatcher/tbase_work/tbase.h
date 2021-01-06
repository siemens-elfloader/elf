//tbase.h - ������ � ����� ���������� ��� ���������� ����������� ������
//(C)Dimadze
//v1.2

extern void EnableINT(int fi);
extern int  DisableINT();
extern void CleanCache(void *vaddress);
extern void CleanTLB();
extern int *GetTBaseAddr();
extern void UnLockAccess();


//��������� �������� ����� �� ������
char GetByteFromAddress(void *addr);
//����������� ������ ����� �� ������ (���������� �����)
int  ApplyPatch(void *addr, char new_byte);
//����������� ������ ����� �� ������ (������ �����)
int  UndoPatch(void *addr, char old_byte);

/* ��� ������ ���� ������ ���� ������ */
/* �������� ������ �������� */
/* ���� ��� ������� flash ������� ���� ��� ������ */
/* ������� RAM, ������� ��������� ��� flash �������� */
/* �� ����� ������� ��� ������, ������ ������ */
/* ����� � ��� ������ ���� ���������������� ������ */

