#define MAXFONTNUM 10 //�ܧ�ݧڧ�֧��ӧ� �ڧ���ݧ�٧�֧ާ�� ��ڧ��ӧѧߧߧ�� ���ߧ���

extern void* canvasdata;


void FontPathFree(); //!!!�ӧ�٧�ӧѧ�� ���� �ӧ���է� �ڧ� ��ݧ��� �ڧݧ� �֧�ݧ� �ߧѧէ� ���� ��֧ܧ�ߧ�ڧԧ��ѧ�ڧ� 

void FontPathInit(int num, char* path, int isFullSet ); // !!!���� ���ѧ��� ��ݧ��� �ڧݧ� �֧�ݧ� �էݧ� ���ߧܧ�ڧ� �ڧ���ݧ�٧����� �էѧߧߧ�� �ڧ� �ܧ�ߧ�ڧԧ� ��� ���� ��֧ܧ�ߧ�ڧԧ��ѧ�ڧ�

void PrintPic( int x, int y, int pic ); //�ӧ�ӧ�� �ܧѧ��ڧߧܧ�

void PrintField( int x, int y, char *str, int align, int font, int space); //�ӧ�ӧ�� �����ܧ�

void PrintText( int x, int y, char *str, int align, int font, int space, int lineSpace, int isScroll, short fixSize, int maxLen); //�ӧ�ӧ�� ��֧ܧ���

void ClearScreen(); //���ڧ��ڧ�� �ӧ�� ���� �ҧ�ݧ� �ߧѧ�ڧ��ӧѧߧ� ���ߧܧ�ڧ�ާ� Print***
