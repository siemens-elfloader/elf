//#define INPUT_OK
#define HIGHCOLOR  // 16-������ �����
#define GRAPH      // �������
//#define NEWSGOLD
//#define ELKA


#include "swilib.h"
#include "SWILIB.C"
#define paramlength 16
#ifdef ELKA
  #define width 240
  #define height 320
#else
  #define width 132
 #define height 176
#endif

extern  char devka[];
extern int test_dir();
IMGHDR *FImage;

//---------------------------------- ���������� ---------------------------------------------------

char *Title="Hello World!"; //�� ��� ����� � XTask
char *enter="\x0D\x0A";     //������ � ��������� �������
 WSHDR *maks;               //C��� ���������� ����� ����� ������� �� �����


const char *errors[]={
  0,
  "���� �� ��������� ���� ���������!\0",
  "Unknown error!"
};

volatile int running=0; // ������� ��������� ���� � ������� ���� =0



//---------------------------------- ������� ���������� -------------------------------------------

extern short *screen;                          // ����� 240*320*2
extern int screensize;
extern void DrawScreen();                      // ������� ����������� ������
extern IMGHDR *read_pngimg(const char *buf);
extern char loggerCWILIB[512];
extern int s1,s2,s3,s4,s5;
extern int plott(char liter, int font, int x, int y, int fcolor);
extern void EditColors(char *color);
extern FLIST *AddToFList(const char* full_name, const char *name, int is_folder);
extern volatile FLIST *fltop;
extern int FindFiles(char *str, int type);
extern void open_fm();

 //extern int alabama;
void onredraw();
int mode=0; //1-menu, 0-desk
//---------------------------------- ��������� ���������� -----------------------------------------
 int curx=4, cury=1; //���������� ������ ����������

 



//==========================================================================================================
void drawcur(int curx, int cury, int color){
  int i;
  short *scr=screen+((7-cury)*15+6)*width+(7-curx)*15+6;
  memsetw(scr,curcolor,15);
  memsetw(scr+=width,curcolor,15);
  scr+=width;
  for(i=0;i<11;i++,scr+=width){
    *scr=scr[1]=scr[13]=scr[14]=color;
  }
  memsetw(scr,curcolor,15);
  memsetw(scr+width,curcolor,15);
}
//==========================================================================================================
inline void cls(){memsetw(screen,bkcolor,screensize>>1);}//menubkcolor
//================================================================= R E D R A W ===================================== = = = ====================
void onredraw(){ // ����������� ������ // ���������� � Screen, � ������ ����� �����
  DisIconbar(1);
 int i,j;
 cls();  
 
 
 // for(i=0;i<16;i++) for(j=0;j<16;j++) drawcur(curx,cury,curcolor);  

}
//==========================================================================================================

void odraw(){ // ����������� ������ //Screen �� ����� ��� ������ ������ ������ ���� ����

    wsprintf(maks,"Test resource image (c)mirrr, 2008");
    DrawRectangle(0,0,240,24,0, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(1));
    DrawString(maks,15,265,240,320,9,0x20,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
    drawim(FImage,10,10,0,0,0,0);
    //DrawImg(0,0,(int)FImage);
  }


//=================================================================================================================== = = = ====================

// keycode - ��� �������, pressed - ������/��������/������������
int onkey(unsigned char keycode, int pressed){ //  ���������� ������. ������� 0 ��� 1 ��� ������
  switch(pressed){      
  case KEY_UP: return 0;          // ������� ��������
  case LONG_PRESS:                // ������� ������������ ����� (������)
   switch(mode){case 0: default: // 
    switch(keycode){
    case RIGHT_BUTTON: if(--curx<0) curx=7; break;
    case LEFT_BUTTON:  if(++curx>7) curx=0; break;
    case DOWN_BUTTON:  if(--cury<0) cury=7; break;
    case UP_BUTTON:    if(++cury>7) cury=0; break;
    default: return 0;
    }}     
  case KEY_DOWN:                  // ������� ������

      if(keycode==RED_BUTTON) return 1;     
switch(mode){ 
    case 0: default: 
    switch(keycode){ // ��� �������
    case RIGHT_SOFT: return 1; //����� 
    case LEFT_SOFT:   break; 
    case RIGHT_BUTTON: if(--curx<0) curx=7; break;
    case LEFT_BUTTON:  if(++curx>7) curx=0; break;
    case DOWN_BUTTON:  if(--cury<0) cury=7; break;
    case UP_BUTTON:    if(++cury>7) cury=0; break;
    case '9': break;    
    case ENTER_BUTTON:  break;
    case GREEN_BUTTON:  break; 
    default:  return 0;
    }}
    REDRAW();
  }
  return 0;
}





void onclose(){ //��� �������� ����
  running=0; // ������ �� ��������� �������� ��������
} 
 //===========================================================================/
void onexit(){ // ��� ������ // ����������� ������
 // if(fon) mfree(fon); // ����������� ������
 // if(curImg) mfree(curImg); // ����������� ������  
  //	if (wsbuf) FreeWS(wsbuf);
}
 //===========================================================================/
void oncreate(){ // ��� c������� ���� 

}
 //===========================================================================/          
int onstart(char *exename, char *fname){ // ����� ����������. ���������� 0 ��� 1 ��� ������.
 //===========================================================================/
  //test_dir();
  if (isfile ("4:\\Z.txt")) ShowMSG(1,(int)"OK!"); else ShowMSG(1,(int)"File not found!");
   maks=AllocWS(256);
 bkcolor=0x0; frcolor=0x0; //��������� ��� ����� - ���� � ������ ��������������
    FImage=read_jpgimg(devka); 
   
   
 return 0;
}

































