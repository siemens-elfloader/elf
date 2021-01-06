#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "../inc/cfg_items.h"
#include "conf_loader.h"
#include "dialogs.c"
#include "constants.c"
#include "fnt.c"
//#include "debug.c"

//typedef char const* color;

#define TMR_SECOND 261
#define kadrCLK 6 // ������ �������� ������ � �������

#ifdef ELKA
#define screenW 240
#define screenH 320
#else
#define screenW 132
#define screenH 176
#endif

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

//-----------------------------------------------------//
//�� �������� ����������,�� ��� ����� � ����� ������� :)
const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

//��������� ���������� �� �������
extern const int font;
//----------------------------------//
int kadrnum=1 ;   // ������� ���� �������� ���������
int mapx = 0, mapy = 0; // ������� ����� �� x � y
int sm=0; // �������� � ������ �� ������ ��� ������ ����� ����� �� ������ ������ ������ ��������
#ifdef ELKA
int sizeSP=20; //������ ������
#else
int sizeSP=16; //������ ������
#endif
#ifdef ELKA
int sizeX=11;  // ������� ����� �������� �� ����� �� �
int sizeY=14;  // ������� ����� �������� �� ����� �� Y
#else
int sizeX=8;  // ������� ����� �������� �� ����� �� �
int sizeY=9;  // ������� ����� �������� �� ����� �� Y
#endif
int scrX=0; //���������� ������ ������������ ������ �����
int scrY=0;
int cursorX=0; //���������� ������� � �����
int cursorY=0;
int Xscr=2;  // ������� ���������� � ������ 
              // ������ ���������� � ������� ��������� ����� 
GBSTMR timerredraw;

int countM2=3; // ������� ����� ����
const int counCOLM=8; // �������� ������� ����
int sizeF=15;  // ������ ������ ������ ������
int gold=15000;  //������
int wood=15000;  //������
int Yscr=2;
int i;
int y;
int x;
int p;
int DelayVAR;
int tpic=1;  // ������� ��������
int maxpic=105;// ������������ ����� �������� ��� ����
int minpic=1;
int scrCURx;
int typeGUI;
int scrCURy;
int typeGUI=0;// ����� �������� ������:0-����� 1-���� 2-����� ��������
int scr_w, scr_h;//������ � ������ ������

#define earth 0x01;

static const char* const tagids[] = {
  "MSX", //������ �� X
  "MSY", //������ �� Y
  "GLD", //������
  "WOD", //���
  "MDT", //������ �������
  "BLD",}; //������ ������

const char NULLS[4]=
{
  0x00,0x00,0x00,0x00,
};

#include "textfield.c"
#include "cb.c"

void printmap(); // ������� ������ �����
void printminimap(); // ������� ������ ���������
void printGW(); // ������� ������/������
int npic (int x,int y); // ������� ���������� ����� ��������
void printpic (int x,int y,int numer); // ������ ��������
void printCUR (); // ������ ������
void vverh ();
void vniz ();
void vpravo ();
void vlevo ();
void vibor ();
void printM1 ();
void drawSBy ();
void drawSBx ();
int REDRAW2 ();
void sss();

char *map;
char *builds;

int FindTag(int tagid, char *dat, int maxlen, int tseek)
{
  int post;
  for(post = tseek; post < (maxlen-3); post++)
  {
    if ((dat[post]==tagids[tagid][0])&&(dat[post+1]==tagids[tagid][1])&&(dat[post+2]==tagids[tagid][2]))
    {
      return (post+3); //���� ����� ������ ������� ������� = ���������
    }
  }
  return -1;
}

int getInt32(char* dat, int ps)
{
  int nm = 0;
  nm = dat[ps + 0] * 0x200000 + dat[ps + 1] * 0x4000 + dat[ps + 2] * 0x80 + dat[ps + 3];
  return nm;
}

void toInt32(int in, char *cint32)
{
  if (in <= 255) 
    {
      cint32[0] = 0x00;
      cint32[1] = 0x00;
      cint32[2] = 0x00;
      cint32[3] = in;
    }
    else if(in <= 32767)
    {
      cint32[0] = 0x00;
      cint32[1] = 0x00;
      cint32[2] = in / 128;
      cint32[3] = in % 128;
    }
    else
    {
      int tm = 0;
      cint32[0] = 0x00;
      tm = in - (in % 16384);
      cint32[1] = tm / 16384;
      tm = in % 16384;
      cint32[2] = tm / 128;
      cint32[3] = tm % 128;
    }
}

void InitMap(char *fname) //������ �����
{
  scr_w=ScreenW();//����������� ���������� ������ � ������ ������
  scr_h=ScreenH();
  int f;
  int FSize;
  unsigned int err;
  char *tmap;
  if (strrchr(fname,'brm')) // ���� ���� ������� � ����������, �� ������ ��� �����
  {
    f=fopen(fname, A_ReadOnly+A_BIN, P_READ, &err);
    FSize=lseek(f,0,S_END,&err,&err);
    tmap = malloc(FSize);
    lseek(f,0,0,&err,&err);
    fread( f,tmap, FSize, & err );
    fclose(f,&err);
  }
  else // ����� ������ ���������
  {
    f=fopen(DEFAULT_DISK ":\\zbin\\Black Raven\\maps\\default.brm", A_ReadOnly+A_BIN, P_READ, &err);   
    //if(f==-1) {ConfirmBox("default.brm not loaded!!", "Ok", 0); return;}    
    FSize=lseek(f,0,S_END,&err,&err);
    tmap = malloc(FSize);
    lseek(f,0,0,&err,&err);
    fread( f,tmap, FSize, & err );
    fclose(f,&err); 
  }
  
  // ���� "���" ������� ����� �� �����������
  int pos = 0;
  pos = FindTag(0, tmap, FSize, 0);
  mapx = tmap[pos];
  // ���� "���" ������� ����� �� ���������
  pos = FindTag(1, tmap, FSize, pos);
  mapy = tmap[pos];
  // ���� "���" ������
  pos = FindTag(2, tmap, FSize, pos);
  gold = getInt32(tmap, pos);
  // ���� "���" ����
  pos = FindTag(3, tmap, FSize, pos);
  wood = getInt32(tmap, pos);
  // ���� "���" ����� �����
  pos = FindTag(4, tmap, FSize, pos);
  memcpy(map,&tmap[pos],(mapx * mapy));
  pos = FindTag(5, tmap, FSize, pos);
  int bldlen = 0;
  bldlen = getInt32(tmap, pos);
  if (bldlen)
  {
    builds = malloc(bldlen);
    memcpy(builds,&tmap[pos],bldlen);
  }
  if (tmap) mfree(tmap);
}

//void canvasdata(void);

void *canvasdata;
int delay (int t);
void printPCUR ();
int npic2save ();
void printwin (int x,int y,int l,int h);

void writemap(char* fname)
{
  unsigned int err;
  char *filename_full = malloc(64);
  sprintf(filename_full, DEFAULT_DISK ":\\zbin\\Black Raven\\maps\\%s.brm", fname);
  int ff;
  if(fopen(filename_full, A_ReadOnly, 0, &err) != -1) unlink(filename_full, &err);
  ff = fopen(filename_full,A_ReadWrite+A_BIN+A_Create+A_Truncate,P_READ+P_WRITE,&err);
  fwrite(ff, "MSX", 3, &err);
  fwrite(ff, &mapx, 1, &err);
  fwrite(ff, "MSY", 3, &err);
  fwrite(ff, &mapy, 1, &err);
  fwrite(ff, "GLD", 3, &err);
  char *cint32 = malloc(4);
  toInt32(gold, cint32);
  fwrite(ff, cint32, 4, &err);
  zeromem(cint32, 4);
  fwrite(ff, "WOD", 3, &err);
  toInt32(wood, cint32);
  fwrite(ff, cint32, 4, &err);
  zeromem(cint32, 4);
  fwrite(ff, "MDT", 3, &err);
  fwrite(ff, map, mapx * mapy, &err);
  fwrite(ff, "BLD", 3, &err);
  if(builds)
  {
    int blen = strlen(builds);
    toInt32(blen, cint32);
    fwrite(ff, cint32, 4, &err);
    zeromem(cint32, 4);
    fwrite(ff, builds, blen, &err);
  }
  else
  {
    fwrite(ff, NULLS, 4, &err);
  }
  fclose(ff, &err);
  if(cint32) mfree(cint32);
  if(filename_full) mfree(filename_full);
}

void writeinit(int digit, int init)
{
  if(digit > 100000) digit = 100000;
  if (init == 1) gold = digit;
  else wood = digit;
}


void changeSize(int xx, int yy)
{   
  if(mapx != xx || mapy != yy)
  {
     char *tmpmap = malloc(mapx * mapy);
     memcpy(tmpmap,map,(mapx * mapy));
      if (map) mfree(map);
      map=malloc(xx*yy);
      memset(map,1,xx*yy);
    
      for(int ii = 0; ii < mapy; ii++)
      {
        memcpy(map + ii*xx, tmpmap + (mapx * ii), (xx<mapx)?xx:mapx);
      }
      
    mapx = xx;
    mapy = yy;
  }
}

static void OnRedraw(MAIN_GUI *data)//��� ������� ����� ��� ����������� ������,��� ������ ��� ��� ��� �����
{
  if(typeGUI == 0 || typeGUI == 2 || typeGUI == 3)
  {
   printmap ();  // ������ �����
   printCUR ();  // ������ ������
   drawSBy ();   //������ ��������
   drawSBx ();
   printGW();    //����� ������/������
  }
  if (typeGUI==2)
  {
  printPCUR ();
  }
  if (typeGUI==3)
  {
  printminimap();
  }
  if (typeGUI==1)
   {
   printwin (4,10,120,150);
   printM1 ();
   }
}
// ��� ���� ������� ��������� � � �///////////////////////////////////////////////////////////////////
void sss()
{
  kadrnum = (kadrnum%4)+1;
    //if  (kadrnum==4)  kadrnum=1;
    //else kadrnum += 1;
  REDRAW();
  GBS_StartTimerProc(&timerredraw,TMR_SECOND/kadrCLK,sss);
}
void printM1 ()// ������ ����
{
  WSHDR *wstr = AllocWS(64);
  int countM=0;
  int xm1=11;
  int ym1=10;
  int xm1m=xm1;
  int ym1m=ym1;
  countM++;
  DrawRectangle(xm1m-1,ym1m+countM2*sizeF-3,120,ym1m+countM2*sizeF+sizeF-4,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(15));
  wsprintf (wstr, percent_t,"�������"); //1
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"���������"); //2
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"���� ������"); //3
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"����������� ������"); //4
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"������"); //5
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"���"); //6
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"������ �����"); //7
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
    countM++;
  wsprintf (wstr, percent_t,"�����"); //8
  DrawString(wstr, xm1m, ym1m+countM*sizeF, screenW-10, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  FreeWS(wstr);
  countM=1;
}

inline void MenuEnter()
{
  switch(countM2)
           {
             // �������
             case 1: {//CreateBookmarksMenu();break;}// ���������
             case 2: {DoEditcontrol(1, "map0", NULL);break;}  // ���� ������
             case 3: break;  // ����������� ������
             case 4: //TextBox("�������� ����","�� ������ �������� ��������","����� �� ����� ���� ���������� ��������\n ��������� ������-����\n ������ �����"); break;// ������
             case 5:
             {
               char *mt = malloc(10);
               sprintf(mt, percent_d, gold);
               DoEditcontrol(2, mt, NULL);
               if(mt) mfree(mt);
               break;
             }
             // ���
             case 6: 
             {
               char *mt = malloc(10);
               sprintf(mt, percent_d, wood);
               DoEditcontrol(3, mt, NULL);
               if(mt) mfree(mt);
               break;
             }
             // ������ �����
             case 7: 
             {
               char *mx = malloc(10);
               char *my = malloc(10);
               sprintf(mx, percent_d, mapx);
               sprintf(my, percent_d, mapy);
               DoEditcontrol(4, mx, my);
               if(mx) mfree(mx);
               if(my) mfree(my);
               break;
             }
             // �����
             case 8: break;
           }
}
}


int npic (int x,int y) // ������� ���������� ����� �������� �� ����� � � � ���������
{
  i=1;
  p=1;
  i=sm+x+y*mapx;
  int p=map[i];
  return p;
}

int npic2save () // ������� ���������� �������� �� ������ ����� ��� ������� ��������
{
  i=1;
  y=cursorY;
  x=cursorX;
  i=sm+x+y*mapx;
  return i;
}


void printpic (int x,int y,int numer) //������ �������� �� ����� ���������� �� ������ � �����
{
  char *path=malloc(128);
  
  if (numer>=100)
  {
     sprintf(path, DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\%d_%d.png", numer, kadrnum);
  
  }
  else 
  {
    sprintf(path, DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\%d.png", numer);
  
  }
  DrawImg(x,y,(int)path);
  if(path) mfree(path);
}

void printCUR () // ������ ������
{
  int scrCURx;
  int scrCURy;
  scrCURx=Xscr+(cursorX-scrX)*sizeSP;
  scrCURy=Yscr+(cursorY-scrY)*sizeSP;
  DrawImg(scrCURx,scrCURy,(int)DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\0.png");
}

void printPCUR ()//  ������ �������� ������� �� ����� �������
{
  scrCURx=Xscr+(cursorX-scrX)*sizeSP;
  scrCURy=Yscr+(cursorY-scrY)*sizeSP;
  int numer2=tpic;
  char *path=malloc(128);
  sprintf(path, DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\%d.png", numer2);
  DrawImg(scrCURx,scrCURy,(int)path);
  if(path) mfree(path);
}

void drawSBy () // �������� �
{ 
#ifdef ELKA
  int ySB; int lenSB;
  lenSB=297*((sizeSP*100)/(sizeSP*mapy))/100;
  ySB=(lenSB)*cursorY;
  
  DrawLine(233,1,233,291,1,GetPaletteAdrByColorIndex(6));
  DrawRectangle(233,ySB-3,234,ySB+lenSB-3,0,RED,RED);
#else
  int ySB; int lenSB;
  lenSB=159*((sizeSP*100)/(sizeSP*mapy))/100;
  ySB=(lenSB)*cursorY;
  DrawLine(130,1,130,147,1,GetPaletteAdrByColorIndex(6));
  DrawRectangle(129,ySB-3,131,ySB+lenSB-3,0,RED,RED);
#endif
}

void  drawSBx () // �������� �
{
#ifdef ELKA
    DrawLine(1,283,233,283,1,GetPaletteAdrByColorIndex(6));
  int xSB; int lenSB;
  lenSB=240*((sizeSP*100)/(sizeSP*mapx))/100;
  xSB=lenSB*cursorX;
  DrawRectangle(xSB-3,283,xSB+lenSB-3,284,0,RED,RED);
#else
  DrawLine(1,147,130,147,1,GetPaletteAdrByColorIndex(6));
  int xSB; int lenSB;
  lenSB=146*((sizeSP*100)/(sizeSP*mapx))/100;
  xSB=lenSB*cursorX;
  DrawRectangle(xSB-3,146,xSB+lenSB-3,148,0,RED,RED);
  #endif
}

void printwin (int x,int y,int l,int h)  // ������ ����
{
  DrawRoundedFrame(x,y,x+l,y+h,5,5,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(1));
//);
}

int zoom=3; 

void printminimap()
{ 
  int mmx= (ScreenW()-mapx*zoom)/2;
 
  DrawRectangle(-1,-1,ScreenW(),ScreenH(),0,SBLACK,SBLACK);
  
  
  DrawRectangle(mmx-3,mmx-3,mmx+zoom*sizeX+2,mmx+zoom*sizeY+2,0,GOLD,DARKBROWN);
  
  
  DrawRectangle(mmx-3,mmx-3,mmx-1,mmx-1,0,GOLD,DARKBROWN);
  DrawRectangle(mmx-3,mmx+zoom*sizeY+2,mmx-1,mmx+zoom*sizeY,0,GOLD,DARKBROWN);
  DrawRectangle(mmx+zoom*sizeX+2,mmx-3,mmx+zoom*sizeX,mmx-1,0,GOLD,DARKBROWN);
  DrawRectangle(mmx+zoom*sizeX+2,mmx+zoom*sizeY+2,mmx+zoom*sizeX,mmx+zoom*sizeY,0,GOLD,DARKBROWN);
  
  
  int n; 
  for (int o=0;o<sizeY;o++)
  {
    for (int i=0;i<sizeX;i++)
     {
       n=npic(scrX+i,scrY+o);
       DrawRectangle (mmx+zoom*i,mmx+zoom*o,zoom+mmx+zoom*i-1,zoom+mmx+zoom*o-1,0,GetPaletteAdrByColorIndex(n),GetPaletteAdrByColorIndex(n));
     }
  }
}

void printmap ()// ������ �����
{
  DrawRectangle(0,0,ScreenW()-1,ScreenH()-1,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));//������ ���
#ifdef ELKA
  DrawRectangle(0,0,239,291,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(1));//������ �����
#else
    DrawRectangle(0,0,122,152,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));//������ �����
#endif
  x=Xscr;   //���������� ������ ������ ����� � ������
  y=Yscr;
  int i;
  int n;
  int o; 
  for (o=0;o<sizeY;o++)
  {
    for (i=0;i<sizeX;i++)
     {
       n=npic(scrX+i,scrY+o);
       printpic (x+i*sizeSP,y+sizeSP*o,n);
     }
  }
}

void printGW()
{
  int ygw=3+Yscr+sizeY*sizeSP;
  DrawRectangle(0,ygw,ScreenW()-1,ScreenH()-1,0,GOLD,DARKBROWN);
 
  //DrawRoundedFrame(0,ygw,ScreenW(),ScreenH(),0,0,0,DARKGOLD,NULL);
  
  DrawRectangle(0           ,ygw         ,2          ,ygw+2,0,GOLD,DARKBROWN);
  DrawRectangle(ScreenW()-3 ,ygw         ,ScreenW()-1,ygw+2,0,GOLD,DARKBROWN);
  DrawRectangle(0           ,ScreenH()-3 ,2          ,ScreenH()-1,0,GOLD,DARKBROWN);
  DrawRectangle(ScreenW()-3 ,ScreenH()-3 ,ScreenW()-1,ScreenH()-1,0,GOLD,DARKBROWN);
  
   /*
  color blink[5]={NULL,RED,ORANGE,RED,YELLOW};
 
  DrawRoundedFrame(0           ,ygw         ,3          ,ygw+3,2,2,0,GOLD,(char*)&(blink[kadrnum]));
  DrawRoundedFrame(ScreenW()-4 ,ygw         ,ScreenW()-1,ygw+3,2,2,0,GOLD,(char*)&(blink[kadrnum]));
  DrawRoundedFrame(0           ,ScreenH()-4 ,3          ,ScreenH()-1,2,2,0,GOLD,(char*)&(blink[kadrnum]));
  DrawRoundedFrame(ScreenW()-4 ,ScreenH()-4 ,ScreenW()-1,ScreenH()-1,2,2,0,GOLD,(char*)&(blink[kadrnum]));
  //����� � ���� ��������-��... (�)*/
  
  //������� �������� �����������(( ���� ���������������
  
  char string[20];
  sprintf (string, "%s%d", "������: ", gold);
  DrawStrShadowed(string,5,ygw+3,WHITE,BLACK);
  
  sprintf (string, "%s%d", "���: ", wood);
  DrawStrShadowed(string,5,ygw+10,WHITE,BLACK);
  
  if (typeGUI==2){sprintf (string, "%s[%d]",GetTerrainNames[tpic],tpic); }  
  if (typeGUI==0){sprintf (string, "%s[%d]",GetTerrainNames[npic (cursorX,cursorY)],npic (cursorX,cursorY)); }
  DrawStrShadowed(string,5,ygw+17,WHITE,BLACK);
  
  sprintf (string, "%i %i",cursorX,cursorY);
  DrawStrShadowed(string,115,ygw+3,WHITE,BLACK);
  
  /*
  WSHDR *wstrr = AllocWS(32);
  wsprintf (wstrr, percent_td, "������: ", gold); //1
  DrawString(wstrr, 5, (scr_h-2-(GetFontYSIZE(FONT_SMALL)*2)), scr_w-2, scr_h-2-GetFontYSIZE(FONT_SMALL), FONT_SMALL, 0, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  wsprintf (wstrr, percent_td, "���: ", wood); //2
  DrawString(wstrr, 5, scr_h-1-GetFontYSIZE(FONT_SMALL), scr_w-2, scr_h-1, FONT_SMALL, 0, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  
  
  wsprintf (wstrr, "%i %i",cursorX,cursorY); 
  DrawString(wstrr, 15, ygw+2, ScreenW()-5, 999, FONT_NUMERIC_XSMALL, 4, WHITE, NULL );
  
  
  if (typeGUI==2){wsprintf (wstrr, "%t[%d]",GetTerrainNames[tpic],tpic); }  
  if (typeGUI==0){wsprintf (wstrr, "%t[%d]",GetTerrainNames[npic (cursorX,cursorY)],npic (cursorX,cursorY)); }
  
  DrawString(wstrr, 15, scr_h-1-GetFontYSIZE(FONT_SMALL), ScreenW()-5, 999, FONT_SMALL, 4, WHITE, NULL );
  FreeWS(wstrr);
  */
}

//-----------------------------------------------------------------------------------------------------

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //��� ������ ��� ���� ��� �������� ���
{
#ifdef ELKA//���� ����,�� ��������� �������
  DisableIconBar(1);
#endif
  data->ws1=AllocWS(256); //�������� ������ ��� ������
  data->gui.state=1;
  
}

void ElfKiller(void)//����������� ��� ������� ����� ������ � ���������
{
  if(map) mfree(map);
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //����� ������ ��� ���� ��� �������� ���:)
{
  data->gui.state=0;
  FreeWS(data->ws1);//��������, ����������� ������
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//���� ��� �� ����� �� ����� �� ������ ��� �����
{
  data->gui.state=2;
  DisableIDLETMR();//��������� ������,����� ����� 2 ������ ���� ���������
  sss();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//� ���� ��� �� ������,�� ����� ������� ���� ��������:)
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
  GBS_DelTimer(&timerredraw);
}

//////////////////////////////////////////////////////////////////////////

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)//�� ��� ��� ���
{
  //char box[128];
  if (msg->gbsmsg->msg==KEY_DOWN)//���� ������� ������
  {
     if (typeGUI==0)  // �����
     {
       switch(msg->gbsmsg->submess)
       { 
         case UP_BUTTON: case '2': // ������� �����
         {
           if(cursorY-scrY==0 && scrY>0) scrY--;
           if(cursorY!=0) cursorY--;
           return 0;
         }
         case DOWN_BUTTON: case '8': // ������� ����
         {
           if(cursorY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(cursorY<mapy-1) cursorY++;
           return 0;
         }
         case RIGHT_BUTTON: case '6': // ������� ������
         {
           if(cursorX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
           if(cursorX<mapx-1) cursorX++;
           return 0;
         }
         case LEFT_BUTTON: case '4': // ������� �����
         {
           if(cursorX-scrX==0 && scrX>0) scrX--;
           if(cursorX!=0) cursorX--;
           return 0;
         }           
         case '0':
         {
           typeGUI=3;
           return 0;
         }     
         case ENTER_BUTTON: // ������� �����
         {
           typeGUI=2;
           return 0;
         }
         case LEFT_SOFT: // ����� ����(����)
         {
           typeGUI=1;
           return 0;
         }
         case RIGHT_SOFT:case RED_BUTTON: return (1); //�����
       }
     }
     if (typeGUI==1)  //  ����
     {
       switch(msg->gbsmsg->submess)
       {
         case UP_BUTTON: case '2': // �����
         {
           countM2 = (countM2 == 1 ? counCOLM : countM2-1);
           return 0;
         }
         case DOWN_BUTTON: case '8': // ����
         {
           countM2 = (countM2 == counCOLM ? 1 : countM2+1);
           return 0;
         }
         case LEFT_SOFT: // ����� ����(����)
         {
           typeGUI=0;
           return 0;
         }
         case ENTER_BUTTON:
         {
           MenuEnter();
           if(countM2==8) return 1;
           typeGUI = 0;
           return 0;
          }
          case RIGHT_SOFT: typeGUI=2; REDRAW (); return 0; // ������ ����
          case RED_BUTTON: return (1); // �����
        }
      }
     if (typeGUI==2)  // ������ ������� �������� � �����
     {
       switch(msg->gbsmsg->submess)
       {
         case RIGHT_BUTTON: case '6': // ������
         { 
           if (tpic<maxpic) tpic++;
           printPCUR ();
           return 0;
         }
         case LEFT_BUTTON: case '4': // �����
         {
           if (tpic > minpic) tpic--;
           printPCUR ();
           return 0;
         }
         
         case '#':
         { 
           tpic = (tpic+10)%maxpic;
           printPCUR ();
           return 0;
         }
         case '*':
         {
           tpic = (tpic+maxpic-10)%maxpic;
           printPCUR ();
           return 0;
         }
         
         case ENTER_BUTTON: // �����
         { 
           int i;
           i=npic2save ();
           map[i]=tpic;
           REDRAW();
           typeGUI=0;
           return 0;
         }
         
         case '1': // �����
         { 
           int i;
           i=npic2save ();
           map[i]=1;
           REDRAW();
           return 0;
         }
         case LEFT_SOFT: typeGUI=1; return 0;
         case RIGHT_SOFT: case RED_BUTTON: return (1);
       }
     }
     
     if (typeGUI==3)  //���������
     {
       switch(msg->gbsmsg->submess)
       {
         case DOWN_BUTTON: case '8':
         { 
           zoom--;
           REDRAW();
           return 0;
         }
         case UP_BUTTON: case '2':
         {
           zoom++;
           REDRAW();
           return 0;
         }
         
       default: typeGUI=0; REDRAW(); return 0;        
       }
     }
     
  }
  
  
  
  if (msg->gbsmsg->msg==LONG_PRESS)//��� ��������
  {
     if (typeGUI==0)
     {
        switch(msg->gbsmsg->submess)
        {
         case UP_BUTTON: case '2': // ������� �����
         {
           if(cursorY-scrY==0 && scrY>0) scrY--;
           if(cursorY!=0) cursorY--;
           break;
         }
         case DOWN_BUTTON: case '8': // ������� ����
         {
           if(cursorY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(cursorY<mapy-1) cursorY++;
           break;
         }
         case RIGHT_BUTTON: case '6': // ������� ������
         {
           if(cursorX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
           if(cursorX<mapx-1) cursorX++;
           break;
         }
         case LEFT_BUTTON: case '4': // ������� �����
         {
           if(cursorX-scrX==0 && scrX>0) scrX--;
           if(cursorX!=0) cursorX--;
           break;
         }
        case RIGHT_SOFT:case RED_BUTTON: return (1); //�����
        }  
     }
  }
  return(0);
}

/////////////////////////////////////////////////////////////////////////
extern void kill_data(void *p, void (*func_p)(void *));//��� ������� ������� ���� � ����������� ������

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

static void maincsm_oncreate(CSM_RAM *data)//���������� ��� �������� �����,������ ��� �����
{
  //��� ������ ��������� ��� ��������� �� ��� ����� ���� ���� � ��� ��������������
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

static void maincsm_onclose(CSM_RAM *csm)//������� �������� �����,��� ����������� ������ ���� ����� � �.�.
{
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)//��� ������� ��������� ��� ��������� ����������� �� ����� ��� �������:)
{
  //��������� � �������������� ��������,��� � �.�. � �.�.
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)//���� ���� ��������������,�� ��������� ��������� �����
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"BR_MapEditor config updated!");
      InitConfig();
    }
  }

  return(1);
}


static const struct//��� ��������� ���,����������� �� ����:)
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)//�� ���������� ��� ����� ������������ ������
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"BRgame");
}


int main(char *exename, char *fname)//exename-���� ������������ �����, fname �������� ������������ �����
{
  MAIN_CSM main_csm;
  InitConfig();//���������� ������,������ ������ ��������� �� ����
  LockSched();
  UpdateCSMname();//��������� ��� ��� ������
  map = malloc(16384);
  InitMap(fname);
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);//������� ���
  UnlockSched();
  return 0;
}
