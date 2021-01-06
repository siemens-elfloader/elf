#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "../inc/cfg_items.h"
#include "conf_loader.h"
#include "dialogs.c"
#include "constants.c"
#include "fnt.c"
#include "missions.h"
//#include "debug.c"

//typedef char const* color;

#define TMR_SECOND 261
#define kadrCLK 6 // период анимации кадров в секунду
#define DEFAULT_DISK "4"

//-----------------------------------------------------//
//Эт стремные переменные,но они нужны в любом проекте :)
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

//Объявляем переменные из конфига
extern const int font;
//----------------------------------//




#define earth 0x01;

static const char* const tagids[] = {
  "MSX", //Размер по X
  "MSY", //Размер по Y
  "GLD", //Золото
  "WOD", //Лес
  "MDT", //Массив графики
  "BLD",}; //Массив зданий

const char NULLS[4]=
{
  0x00,0x00,0x00,0x00,
};

#include "textfield.c"
#include "cb.c"

void printmap(); // функция рисует карту
void printminimap(); // функция рисует миникарту
void printGW(); // выводит золото/дерево

void printpic (int x,int y,int numer); // рисует картинку
void printCUR (); // рисует курсор
void vverh ();
void vniz ();
void vpravo ();
void vlevo ();
void vibor ();
void printM1 ();
void drawSBy ();
void drawSBx ();
int REDRAW2 ();
void kadrs();
void printHeroy();
char *map;
char *builds;

int FindTag(int tagid, char *dat, int maxlen, int tseek)
{
  int post;
  for(post = tseek; post < (maxlen-3); post++)
  {
    if ((dat[post]==tagids[tagid][0])&&(dat[post+1]==tagids[tagid][1])&&(dat[post+2]==tagids[tagid][2]))
    {
      return (post+3); //Если нашли значит текущая позиция = результат
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

void InitMap(char *fname) //Грузит карту
{
  scr_w=ScreenW();//Присваиваем переменным высоту и ширину экрана
  scr_h=ScreenH();
  int f;
  int FSize;
  unsigned int err;
  char *tmap;
  if (strrchr(fname,'brm')) // Если эльф запущен с параметром, то грузим эту карту
  {
    f=fopen(fname, A_ReadOnly+A_BIN, P_READ, &err);
    FSize=lseek(f,0,S_END,&err,&err);
    tmap = malloc(FSize);
    lseek(f,0,0,&err,&err);
    fread( f,tmap, FSize, & err );
    fclose(f,&err);
  }
  else // Иначе грузим дефолтную
  {
    f=fopen(DEFAULT_DISK ":\\zbin\\Black Raven\\maps\\default.brm", A_ReadOnly+A_BIN, P_READ, &err);   
    //if(f==-1) {}    
    FSize=lseek(f,0,S_END,&err,&err);
    tmap = malloc(FSize);
    lseek(f,0,0,&err,&err);
    fread( f,tmap, FSize, & err );
    fclose(f,&err); 
  }
  
  // Ищем "тег" размера карты по горизонтали
  int pos = 0;
  pos = FindTag(0, tmap, FSize, 0);
  mapx = tmap[pos];
  // Ищем "тег" размера карты по вертикали
  pos = FindTag(1, tmap, FSize, pos);
  mapy = tmap[pos];
  // Ищем "тег" золота
  pos = FindTag(2, tmap, FSize, pos);
  gold = getInt32(tmap, pos);
  // Ищем "тег" леса
  pos = FindTag(3, tmap, FSize, pos);
  wood = getInt32(tmap, pos);
  // Ищем "тег" самой карты
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
void showMenu()
{
   WSHDR *wstr2 = AllocWS(64);
  int countM3=0;
  int xm1m=11;
  int ym1m=10;
  countM3++;
  DrawRectangle(xm1m-1,ym1m+countM4*sizeF-3,150,ym1m+countM4*sizeF+sizeF-1,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(15));
  wsprintf (wstr2, percent_t,"Собрать"); //1
  DrawString(wstr2, xm1m, ym1m+countM3*sizeF, 240, ym1m+countM3*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  countM3++;
  wsprintf (wstr2, percent_t,"Построить"); //2
  DrawString(wstr2, xm1m, ym1m+countM3*sizeF, 240, ym1m+countM3*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  
   countM3++;
  wsprintf (wstr2, percent_t,"Снять выделение"); //2
  DrawString(wstr2, xm1m, ym1m+countM3*sizeF, 240, ym1m+countM3*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  
  
  FreeWS(wstr2);
  countM3=1;
}
void printBear();
void RedrawScreen()
{
   if(typeGUI == 0 || typeGUI == 2 || typeGUI == 3|| typeGUI == 4||typeGUI==5)
  {
      mission1();
   printmap ();  // рисуем карту
   printBear();
   printHeroy();
   printCUR ();  // рисуем курсор
   drawSBy ();   //рисуем скролбар
   drawSBx ();
   printGW();    //пишем золото/дерево
  }
  if (typeGUI==2||typeGUI==5)
  {
  printPCUR ();
  }
  if (typeGUI==3)
  {
  printminimap();
  }
  if (typeGUI==1)
   {
   printwin (4,10,180,170);
   printM1 ();
   }
    if (typeGUI==4)
   {
   printwin (4,10,180,170);
  showMenu();
   }
    GBS_StartTimerProc(&tmr,15,RedrawScreen);
}
static void OnRedraw(MAIN_GUI *data)//эта функция нужна для перерисовки экрана,тут рисуем все что нам нужно
{
 
}
// тут наши фунуции процедуры и т д///////////////////////////////////////////////////////////////////
void kadrs()
{
  kadrnum = (kadrnum%4)+1;
    
//  RedrawScreen();
  GBS_StartTimerProc(&timerredraw,TMR_SECOND/kadrCLK,kadrs);
}
void printM1 ()// рисует меню
{
  WSHDR *wstr = AllocWS(64);
  int countM=0;
  int xm1=11;
  int ym1=10;
  int xm1m=xm1;
  int ym1m=ym1;
  countM++;
  DrawRectangle(xm1m-1,ym1m+countM2*sizeF-3,150,ym1m+countM2*sizeF+sizeF-1,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(15));
  wsprintf (wstr, percent_t,"ОТКРЫТЬ"); //1
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"СОХРАНИТЬ"); //2
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"Цель миссии"); //3
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"Возможности уровня"); //4
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"Выход"); //5
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
 /* countM++;
  wsprintf (wstr, percent_t,"Лес"); //6
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );
  countM++;
  wsprintf (wstr, percent_t,"Размер карты"); //7
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2), GetPaletteAdrByColorIndex( 23 ) );
    countM++;
  wsprintf (wstr, percent_t,"Выход"); //8
  DrawString(wstr, xm1m, ym1m+countM*sizeF, 240, ym1m+countM*sizeF+GetFontYSIZE(FONT_SMALL), FONT_SMALL, 1, 
             GetPaletteAdrByColorIndex( 2 ), GetPaletteAdrByColorIndex( 23 ) );*/
  FreeWS(wstr);
  countM=1;
}
int a=0;
inline void MenuEnter()
{
  switch(countM2)
           {
             // Открыть
             case 1: {//CreateBookmarksMenu();break;}// Сохранить
             case 2: {DoEditcontrol(1, "map0", NULL);break;}  
             case 4: break;  // Возможности уровня
             case 3: TextBox(zag,all,cel1,miss1,cel2,miss2,cel3,miss3); break;// Цели миссии
            /* case 5:
             {
               char *mt = malloc(10);
            //   sprintf(mt, percent_d, gold);
           //    DoEditcontrol(2, mt, NULL);
           //    if(mt) mfree(mt);
           //    break;
           //  }
             // Лес
             case 6: 
             {
               char *mt = malloc(10);
               sprintf(mt, percent_d, wood);
               DoEditcontrol(3, mt, NULL);
               if(mt) mfree(mt);
               break;
             }
             // Размер карты
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
             }*/
             // Выход
             case 5: break;
           }
}
}
void select()//мега интер
{
   if(cursorX==heroyX&&cursorY==heroyY)
   {
     heroyX=cursorX;
     heroyY=cursorY;
      hercur=1;
   }
   else
   {
     typeGUI=0;
   }
}
void ashipka(char *ash)
{
  ConfirmBox(ash, "Ok", 0); return;
}
void sbor()
{
 int i;
 if(strcmp(GetTerrainNames[npic (heroyX,heroyY)], "Золото")!=0&&strcmp(GetTerrainNames[npic (heroyX,heroyY)], "Лес")!=0&&strcmp(GetTerrainNames[npic (heroyX,heroyY)], "Растения")!=0)
  {
  ashipka("Нечего брать");
  
  }
 if(strcmp(GetTerrainNames[npic (heroyX,heroyY)], "Лес")==0)
  {
     wood+=100;
     tpic=1; i=npic2save();map[i]=tpic;
  
  }
  if(strcmp(GetTerrainNames[npic (heroyX,heroyY)], "Золото")==0)
  {
    
     gold+=100;
     tpic=1; i=npic2save();map[i]=tpic;
   
  
  }
 if(strcmp(GetTerrainNames[npic (heroyX,heroyY)], "Растения")==0)
  {
   
    if(celdric.life<130)
    {
     celdric.life+=10;
     tpic=1; i=npic2save();map[i]=tpic;
   }
    if(celdric.life>=130){celdric.life=130;ashipka("Здоровье полное");}
  }
  typeGUI=0;
}

void str()
{
  if(gold>=100&&wood>=100)
  {
  if(strncmp(GetTerrainNames[npic (heroyX,heroyY)], "Земля", 2)==0)
  {
  tpic=88;typeGUI=5;
  }
   else
  {
  ashipka("Место занято");
    typeGUI=0;
  }
  }
  else
  {
    if(gold<100&&wood<100){ashipka("Недостаточно золота и дерева!");}
    if(gold<100&&wood>=100){ashipka("Недостаточно золота!");}
    if(wood<100&&gold>=100){ashipka("Недостаточно дерева!");}
  }
}

void sbros()
{
 hercur=0;
 typeGUI=0;
}
inline void MenuEnter2()
{
  
  switch(countM4)
           {
             // Открыть
             case 1: {sbor();break;}
             case 2: {str();break;}
             case 3: {sbros();break;}
}
}

int npic (int x,int y) // функция возвращает номер картинки на входе х и у кординаты
{
  i=1;
  p=1;
  i=sm+x+y*mapx;
  int p=map[i];
  return p;
}

int npic2save () // функция возвращает смещение от начала карты для текущей картинки
{
  i=1;
  y=heroyY;
  x=heroyX;
  i=sm+x+y*mapx;
  return i;
}


void printpic (int x,int y,int numer) //рисует картинку на входе координаты на экране и номер
{
  char path[128];
  
  if (numer>=100)
  {
     sprintf(path, DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\%d_%d.png", numer, kadrnum);
  
  }
  else 
  {
    sprintf(path, DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\%d.png", numer);
  
  }
  DrawImg(x,y,(int)path);
}
void printCUR () // рисует курсор
{
  int scrCURx;
  int scrCURy;
  scrCURx=Xscr+(cursorX-scrX)*sizeSP;
  scrCURy=Yscr+(cursorY-scrY)*sizeSP;
  DrawImg(scrCURx,scrCURy,(int)DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\0.png");
}
void printHeroy()
{
  int scrCURx;
  int scrCURy;
  scrCURx=Xscr+(heroyX-scrX)*sizeSP;
  scrCURy=Yscr+(heroyY-scrY)*sizeSP;
 /* if(strcmp(GetTerrainNames[npic (heroyX,heroyY)],"Огонь")==0||strcmp(GetTerrainNames[npic (heroyX,heroyY)],"Вода")==0)
       {
         celdric.life-=2;
       }
  if(celdric.life<=0)
  {
    celdric.life=0;
    gameover=1;
  }*/
  DrawImg(scrCURx,scrCURy,(int)DEFAULT_DISK ":\\zbin\\Black Raven\\img\\heroys\\0.png");
}
void printBear()
{
  ai();
  int scrCURx;
  int scrCURy;
  scrCURx=Xscr+(bearX-scrX)*sizeSP;
  scrCURy=Yscr+(bearY-scrY)*sizeSP;
  DrawImg(scrCURx,scrCURy,(int)DEFAULT_DISK ":\\zbin\\Black Raven\\img\\heroys\\1.png");
}
void heroyEnter()
{
  typeGUI=4;
}
void printPCUR ()//  рисует картинку текущую по месту курсора
{
  scrCURx=Xscr+(heroyX-scrX)*sizeSP;
  scrCURy=Yscr+(heroyY-scrY)*sizeSP;
  int numer2=tpic;
  char path[128];
  sprintf(path, DEFAULT_DISK ":\\zbin\\Black Raven\\img\\map\\%d.png", numer2);
  DrawImg(scrCURx,scrCURy,(int)path);
}

void drawSBy () // скролбар y
{ 
  int ySB; int lenSB;
  lenSB=297*((sizeSP*100)/(sizeSP*mapy))/100;
  ySB=(lenSB)*cursorY;
  
  DrawLine(233,1,233,291,1,GetPaletteAdrByColorIndex(6));
  DrawRectangle(233,ySB-3,234,ySB+lenSB-3,0,RED,RED);
}

void  drawSBx () // скролбар x
{
  DrawLine(1,283,233,283,1,GetPaletteAdrByColorIndex(6));
  int xSB; int lenSB;
  lenSB=240*((sizeSP*100)/(sizeSP*mapx))/100;
  xSB=lenSB*cursorX;
  DrawRectangle(xSB-3,283,xSB+lenSB-3,284,0,RED,RED);
}

void printwin (int x,int y,int l,int h)  // рисует окно
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

void printmap ()// рисует карту
{
  DrawRectangle(0,0,ScreenW()-1,ScreenH()-1,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));//Рисуем фон
  DrawRectangle(0,0,239,291,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(1));//Рисуем рамку
  x=Xscr;   //координаты начала вывода карты в экране
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
  //когда ж меня отпустит-то... (с)*/
  
  //попытки налепить красивостей(( пока закомментировал
  
  char string[20];
   char slife[20];
  sprintf (string, "%s  %d", "Золото:", gold);
  DrawStrShadowed(string,5,ygw+3,WHITE,BLACK);
  
  sprintf (string, "%s  %d", "Лес:", wood);
  DrawStrShadowed(string,5,ygw+10,WHITE,BLACK);
  
  if (typeGUI==2||typeGUI==5){sprintf (string, "%s  [%d]",GetTerrainNames[tpic],tpic); }  
  else{         
     
     if(hercur==0)
     {
      
      sprintf (string, "%s  [%d]",GetTerrainNames[npic (cursorX,cursorY)],npic (cursorX,cursorY));
           
       
     }
     if(hercur==1){sprintf (string, "%s  [%d]",GetTerrainNames[npic (cursorX,cursorY)],npic (cursorX,cursorY)); }
    
    
    }
   sprintf (slife, "Селдрик life [%d]",celdric.life);
  DrawStrShadowed(string,5,ygw+17,WHITE,BLACK);
  DrawStrShadowed(slife,115,ygw+10,WHITE,BLACK);
  if(hercur==0){
    sprintf (string, "x: %i y: %i",cursorX,cursorY);}
  if(hercur==1){
   sprintf (string, "x: %i y: %i",heroyX,heroyY);}
  DrawStrShadowed(string,115,ygw+3,WHITE,BLACK);
  
  /*
  WSHDR *wstrr = AllocWS(32);
  wsprintf (wstrr, percent_td, "Золото: ", gold); //1
  DrawString(wstrr, 5, (scr_h-2-(GetFontYSIZE(FONT_SMALL)*2)), scr_w-2, scr_h-2-GetFontYSIZE(FONT_SMALL), FONT_SMALL, 0, 
             GetPaletteAdrByColorIndex( 0 ), GetPaletteAdrByColorIndex( 23 ) );
  wsprintf (wstrr, percent_td, "Лес: ", wood); //2
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

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Тут делаем что либо при создании гуи
{
#ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
#endif
celdric.life=100;
  data->ws1=AllocWS(256); //Выделяем память под строку
  data->gui.state=1;
  
}

void ElfKiller(void)//освобождаем все занятое место эльфом в оперативе
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Сдесь делаем что нить при закрытии гуи:)
{
  
  data->gui.state=0;
  FreeWS(data->ws1);//например, освобождаем память
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
   
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
  kadrs();
  RedrawScreen();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
   if (data->gui.state!=2) return;
  data->gui.state=1;
  GBS_DelTimer(&timerredraw);
  GBS_DelTimer(&tmr);
   GBS_DelTimer(&tmr2);
}

//////////////////////////////////////////////////////////////////////////

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)//Ну это кей хук
{
  if (msg->gbsmsg->msg==KEY_DOWN)//Если клавиша нажата
  {
     if (typeGUI==0)  // карта
     { 
 
         switch(msg->gbsmsg->submess)
       { 
         case UP_BUTTON: case '2': // Клавиша вверх
         {
           if(cursorY-scrY==0 && scrY>0) scrY--;
           if(cursorY!=0) cursorY--;
           if(hercur==1)
           {
           if(heroyY-scrY==0 && scrY>0) scrY--;
           if(heroyY!=0) heroyY--;
           }
           return 0;
           
         }
         case DOWN_BUTTON: case '8': // Клавиша вниз
         {
           if(cursorY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(cursorY<mapy-1) cursorY++;
           if(hercur==1)
           {
           if(heroyY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(heroyY<mapy-1) heroyY++;
           }
           return 0;
         }
         case RIGHT_BUTTON: case '6': // Клавиша вправо
         {
           if(cursorX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
           if(cursorX<mapx-1) cursorX++;
           if(hercur==1)
           {
           if(heroyX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
           if(heroyX<mapx-1) heroyX++;
           }
           return 0;
         }
         case LEFT_BUTTON: case '4': // Клавиша влево
         {
           if(cursorX-scrX==0 && scrX>0) scrX--;
           if(cursorX!=0) cursorX--;
            if(hercur==1)
           {
           if(heroyX-scrX==0 && scrX>0) scrX--;
           if(heroyX!=0) heroyX--;
           }
           return 0;
         }
       case '1':
         {
            if(cursorX-scrX==0 && scrX>0) scrX--;
            if(cursorX!=0) cursorX--;
            if(cursorY-scrY==0 && scrY>0) scrY--;
            if(cursorY!=0) cursorY--;
             if(hercur==1)
           {
            if(heroyX-scrX==0 && scrX>0) scrX--;
            if(heroyX!=0) heroyX--;
            if(heroyY-scrY==0 && scrY>0) scrY--;
            if(heroyY!=0) heroyY--;
           }
            return 0;
         }
        case '3':
          {
            if(cursorX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
            if(cursorX<mapx-1) cursorX++;
             if(cursorY-scrY==0 && scrY>0) scrY--;
            if(cursorY!=0) cursorY--;
             if(hercur==1)
           {
            if(heroyX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
            if(heroyX<mapx-1) heroyX++;
            if(heroyY-scrY==0 && scrY>0) scrY--;
            if(heroyY!=0) heroyY--;
           }
             return 0;
         }
         case'7':
           {
           if(cursorX-scrX==0 && scrX>0) scrX--;
           if(cursorX!=0) cursorX--;
           if(cursorY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(cursorY<mapy-1) cursorY++;
            if(hercur==1)
           {
           if(heroyX-scrX==0 && scrX>0) scrX--;
           if(heroyX!=0) heroyX--;
           if(heroyY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(heroyY<mapy-1) heroyY++;
           }
           return 0;
           }
       case '9':
         {
           if(cursorX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
           if(cursorX<mapx-1) cursorX++;
            if(cursorY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(cursorY<mapy-1) cursorY++;
            if(hercur==1)
           {
           if(heroyX-scrX==sizeX-1 && scrX<mapx-sizeX) scrX++;
           if(heroyX<mapx-1) heroyX++;
           if(heroyY-scrY==sizeY-1 && scrY<mapy-sizeY) scrY++;
           if(heroyY<mapy-1) heroyY++;
           }
           return 0;
         }
       
         case '0':
         {
           typeGUI=3;
           return 0;
         }     
         case ENTER_BUTTON: // Клавиша выбор
         {
          if(hercur==0)
           {
           select();
           }
            if(hercur==1)
           {
             heroyEnter();
           }
           return 0;
         }
         case LEFT_SOFT: // Левый софт(меню)
         {
           typeGUI=1;
           return 0;
         }
         case RIGHT_SOFT:case RED_BUTTON: return (1); //Выход
       }
       
     
     }
     if (typeGUI==1)  //  меню
     {
       switch(msg->gbsmsg->submess)
       {
         case UP_BUTTON: case '2': // Вверх
         {
           countM2 = (countM2 == 1 ? counCOLM : countM2-1);
           return 0;
         }
         case DOWN_BUTTON: case '8': // Вниз
         {
           countM2 = (countM2 == counCOLM ? 1 : countM2+1);
           return 0;
         }
         case LEFT_SOFT: // Левый софт(меню)
         {
           typeGUI=0;
           return 0;
         }
         case ENTER_BUTTON:
         {
           MenuEnter();
           if(countM2==5) return 1;
           typeGUI = 0;
           return 0;
          }
          case RIGHT_SOFT: typeGUI=2;  return 0; // Правый софт
          case RED_BUTTON: return (1); // Выход
        }
     }
     if (typeGUI==2)  // замена текущей картинки в карте
     {
       switch(msg->gbsmsg->submess)
       {
        // case RIGHT_BUTTON: case '6': // Вправо
        // { 
       //    if (tpic<maxpic) tpic++;
       //    printPCUR ();
       //    return 0;
      //   }
       //  case LEFT_BUTTON: case '4': // Влево
     //    {
      //     if (tpic > minpic) tpic--;
     //      printPCUR ();
     //      return 0;
       //  }
         
        // case '#':
       //  { 
       //    tpic = (tpic+10)%maxpic;
       //    printPCUR ();
        //   return 0;
      //   }
      //   case '*':
      //   {
      //     tpic = (tpic+maxpic-10)%maxpic;
      //     printPCUR ();
        //   return 0;
       //  }
         
         case ENTER_BUTTON: // Выбор
         { 
         //  gold-=100;
        //   int i;
         //  i=npic2save ();
        //   map[i]=tpic;
          
           
           
           
          typeGUI=4;
          return 0;
         }
         
         case '1': // Выбор
         { 
           int i;
           i=npic2save ();
           map[i]=1;
        
           
           return 0;
         }
         case LEFT_SOFT: typeGUI=1; return 0;
         case RIGHT_SOFT: case RED_BUTTON: return (1);
       }
     }
      if (typeGUI==4)  //  меню в игре
     {
       switch(msg->gbsmsg->submess)
       {
         case UP_BUTTON: case '2': // Вверх
         {
           countM4 = (countM4 == 1 ? counCOLM2 : countM4-1);
           return 0;
         }
         case DOWN_BUTTON: case '8': // Вниз
         {
           countM4 = (countM4 == counCOLM2 ? 1 : countM4+1);
           return 0;
         }
         case LEFT_SOFT: // Левый софт(меню)
         {
           typeGUI=0;
           return 0;
         }
         case ENTER_BUTTON:
         {
           MenuEnter2();
           return 0;
          }
          case RIGHT_SOFT: typeGUI=0;  return 0; // Правый софт
          case RED_BUTTON: return (1); // Выход
        }
     }
     if (typeGUI==5)  //  меню в игре
     {
       switch(msg->gbsmsg->submess)
       {
          case RIGHT_BUTTON: case '6': // Вправо
         { 
          if (tpic<91) tpic++;
           printPCUR ();
           return 0;
         }
         case LEFT_BUTTON: case '4':  //Влево
         {
           if (tpic>88) tpic--;
           printPCUR ();
           return 0;
         }
         
         case LEFT_SOFT: // Левый софт(меню)
         {
           typeGUI=0;
           return 0;
         }
         case ENTER_BUTTON:
         {
             gold-=100;
             wood-=100;
           int i;
           i=npic2save ();
           map[i]=tpic;
           typeGUI = 0;
           return 0;
          }
          case RIGHT_SOFT: typeGUI=0;  return 0; // Правый софт
          case RED_BUTTON: return (1); // Выход
        }
     }
     if (typeGUI==3)  //миникарта
     {
       switch(msg->gbsmsg->submess)
       {
         case DOWN_BUTTON: case '8':
         { 
           zoom--;
       
             
           return 0;
         }
         case UP_BUTTON: case '2':
         {
           zoom++;
      
            
           return 0;
         }
         
       default: typeGUI=0;  return 0;        
       }
     }
     
  }
  
  
  
 
 
 
  return(0);
}

/////////////////////////////////////////////////////////////////////////
extern void kill_data(void *p, void (*func_p)(void *));//Эта функция убивает эльф и освобождает память

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

static void maincsm_oncreate(CSM_RAM *data)//Вызывается при открытии эльфа,делаем что нужно
{
  //тут хитрые махинации для получения ид гуя чтобы мона было с ним манипулировать
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

static void maincsm_onclose(CSM_RAM *csm)//функция закрытия эльфа,тут освобождаем памчть если нужно и т.п.
{
  GBS_DelTimer(&tmr);
   GBS_DelTimer(&tmr2);
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

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)//тут вообщем протекают все сообщения поступаемые из эльфа так сказать:)
{
  //сообщение о реконфигурации например,ипц и т.д. и т.п.
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)//Елси была реконфигурация,то обновляем настройки эльфа
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"BRGame config updated!");
    //  InitConfig();
    }
  }

  return(1);
}


static const struct//это структура цсм,разбираться не надо:)
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

void UpdateCSMname(void)//ну собственно имя эльфа передаваемое хтаску
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"BRGame");
}


int main(char *exename, char *fname)//exename-путь запускаемого эльфа, fname параметр передаваемый эльфу
{
  MAIN_CSM main_csm;
 // InitConfig();//инициируем конфиг,тобишь читаем настройки из него
  LockSched();
  UpdateCSMname();//обновляем имя для хтаска
  map = malloc(16384);
  InitMap(fname);
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);//создаем цсм
  RedrawScreen();
  UnlockSched();
  return 0;
}
