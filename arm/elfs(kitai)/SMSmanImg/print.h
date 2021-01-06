#define MAXFONTNUM 10 //§Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§à §Ú§ã§á§à§Ý§î§Ù§å§Ö§Þ§í§ç §â§Ú§ã§à§Ó§Ñ§ß§ß§í§ç §æ§à§ß§ä§à§Ó

extern void* canvasdata;


void FontPathFree(); //!!!§Ó§í§Ù§í§Ó§Ñ§ä§î §á§â§Ú §Ó§í§ç§à§Õ§Ö §Ú§Ù §ï§Ý§î§æ§Ñ §Ú§Ý§Ú §Ö§ã§Ý§Ú §ß§Ñ§Õ§à §á§â§Ú §â§Ö§Ü§à§ß§æ§Ú§Ô§å§â§Ñ§è§Ú§Ú 

void FontPathInit(int num, char* path, int isFullSet ); // !!!§á§â§Ú §ã§ä§Ñ§â§ä§Ö §ï§Ý§î§æ§Ñ §Ú§Ý§Ú §Ö§ã§Ý§Ú §Õ§Ý§ñ §æ§å§ß§Ü§è§Ú§Ú §Ú§ã§á§à§Ý§î§Ù§å§ð§ä§ã§ñ §Õ§Ñ§ß§ß§í§Ö §Ú§Ù §Ü§à§ß§æ§Ú§Ô§Ñ §ä§à §á§â§Ú §â§Ö§Ü§à§ß§æ§Ú§Ô§å§â§Ñ§è§Ú§Ú

void PrintPic( int x, int y, int pic ); //§Ó§í§Ó§à§Õ §Ü§Ñ§â§ä§Ú§ß§Ü§Ú

void PrintField( int x, int y, char *str, int align, int font, int space); //§Ó§í§Ó§à§Õ §ã§ä§â§à§Ü§Ú

void PrintText( int x, int y, char *str, int align, int font, int space, int lineSpace, int isScroll, short fixSize, int maxLen); //§Ó§í§Ó§à§Õ §ä§Ö§Ü§ã§ä§Ñ

void ClearScreen(); //§à§é§Ú§ã§ä§Ú§ä§î §Ó§ã§Ö §é§ä§à §Ò§í§Ý§à §ß§Ñ§â§Ú§ã§à§Ó§Ñ§ß§à §æ§å§ß§Ü§è§Ú§ñ§Þ§Ú Print***
