// ��� ��������� �� �-�� ���������
typedef int (*IsGreaterFunc)(void*, void*);

void quickSort(void** a, long size, IsGreaterFunc gt);
