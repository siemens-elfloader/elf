//������� "HIGH_PROC" ���������� ����������
#include "..\..\inc\swilib.h"


#define HPROC_ID   0x4409
#define HPROC_NAME "HIGH_PROC"
#define HPROC_PRIO 0x00

#define HPROC_MSG   0x0001 // HIGHPROC
#define HPROC_KILL  0x0002 // Kill HIGHPROC


//�������� GBS �������� "HIGH_PROC"
void Create_HPROC();
//����������� GBS �������� "HIGH_PROC"
void Kill_HPROC();
//����������� GBS �������� "HIGH_PROC"
void Kill_HPROC_MSG(void *killproc);
//����� �-�� � �������� � ���������� �����������
void HIGHPROC(void *f,  void *p1, int p2);



