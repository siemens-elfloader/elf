#define MAXFONTNUM 10 //���������� ������������ ���������� ������

extern void* canvasdata;

void FontPathFree(); //!!!�������� ��� ������ �� ����� ��� ���� ���� ��� �������������� 

void FontPathInit(int num, char* path, int isFullSet ); // !!!��� ������ ����� ��� ���� ��� ������� ������������ ������ �� ������� �� ��� ��������������

void PrintPic( int x, int y, int pic ); //����� ��������

void PrintField( int x, int y, char *str, int align, int font, int space); //����� ������

void PrintText( int x, int y, char *str, int align, int font, int space, int lineSpace, int isScroll, short fixSize, int maxLen); //����� ������

void ClearScreen(); //�������� ��� ��� ���� ���������� ��������� Print***
