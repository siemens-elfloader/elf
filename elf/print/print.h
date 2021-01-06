#define MAXFONTNUM 10 //количество используемых рисованных фонтов

extern void* canvasdata;

void FontPathFree(); //!!!вызывать при выходе из эльфа или если надо при реконфигурации 

void FontPathInit(int num, char* path, int isFullSet ); // !!!при старте эльфа или если для функции используются данные из конфига то при реконфигурации

void PrintPic( int x, int y, int pic ); //вывод картинки

void PrintField( int x, int y, char *str, int align, int font, int space); //вывод строки

void PrintText( int x, int y, char *str, int align, int font, int space, int lineSpace, int isScroll, short fixSize, int maxLen); //вывод текста

void ClearScreen(); //очистить все что было нарисовано функциями Print***
