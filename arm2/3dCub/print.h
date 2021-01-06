
extern void* canvasdata;
  
void PrintLibInit(int maxPngFontNum);
void PrintLibFree();
void FontPathInit(char* path, int isFullSet);

void PrintPic( int x, int y, int pic ); 
void ClearPic( int x, int y);

void ReserveRect( int x, int y, int width, int height);

void PrintField( int x, int y, char *str, int align, int font, int space);

void PrintText( int x, int y, char *str, int align, int font, int space, int lineSpace, int isScroll, short fixSize, int maxLen);

int FontH(int font);

void ClearScreen();

void ClearData();

void PrintTest(char *str);

void SetScrollEdgeDelay(int delay);

short GetNLines(int x, int y);

short GetWidth(int x, int y);

void SetFontColor(char* fontColor, char* bgrColor, char isOutline);

void SetCanvasFlag(int flag);

