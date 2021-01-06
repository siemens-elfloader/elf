#ifndef _MAIN_H_
  #define _MAIN_H_


extern const unsigned  int Rows;
extern const unsigned  int Columns;
extern const unsigned int OffsetX;
extern const unsigned int OffsetY;
extern const char MENU_PATH[128];
extern const char CURSOR_PATH[128];



typedef struct{
  
  char Text[32];
  char Description[128];
  char IconBig[128];
  char IconSmall[128];
  char Run[128];

} TMenuPoint;



#endif
