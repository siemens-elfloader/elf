#ifndef _SWILIB_C
#define _SWILIB_C

#include "..\htc\readimg.h"
 void DisIconbar(int r){
#ifdef ELKA
  DisableIconBar(r);
#else
  //null
#endif
}
#define scrtype short

#include "swilib.h"


#ifdef INPUT_OK
#include "string_works.c"
#include "mainmenu.c"
#endif

#define true 1
#define false 0
#define null 0
#define HIGHCOLOR // 16-битный режим
#define GRAPH  // Графика
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

//#define UNPACK // Распаковка архивов
//#define NO7Z   // Кроме 7z
//#define NOZIP  // Кроме zip
//#define NORAR  // Кроме rar
//#define NOLOAD // in loadgraph data loaded allready
extern short *screen; // Экран 240*320*2
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
extern IMGHDR *read_pngimg(const char *buf);
extern IMGHDR *read_jpgimg(const char *buf, int mod);
extern HEADER_DESC input_hdr;

//extern int CreateInput();
int x_char (char liter, int font);
int y_char (int font);
int lenta=0;
char loggerCWILIB[512];
char RecTxt (char rec);
int intlog;// записуем нужное значение в лог
int plott(char liter, int font, int x, int y, int fcolor); //рисуем символ шрифта
    char nite=255;
    char fastfon=0; //картинка загрузилась в память но не расчитаны координаты шрифтов:)


    int tmpfnt=0;   //временное хранилище шрифта поумолчанию  0..n-1 /где n - кол-во шрифтов
   //                      //Буфер в который полностью грузится файл картинки
    char *regfile=0;                    //Буфер в который полностью грузится файл реестра

    WSHDR *wsbuf;
    char *fon=0;
    char *curImg=0;
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------

 int curcolor=0x1f, maskcolor=0xFf, bkcolor=-8192, frcolor=0; //последние два цвета - фона и фронта соответственно
 int menucolor=0xffff,  movecolor=0;
 int menubkcolor=0;//-8192;//-8192;
 char belex[]={0,0,0,60};
 //char bkcolor[]={0,0,0,60};
#ifdef ELKA
  #define width 240
  #define height 320
#else
  #define width 132
  #define height 176
#endif
//extern int width, height;

unsigned int err=0;
int loadfilesize=0;


int bufan2=0;
int bufan=0;

#ifndef NEWSGOLD
#define NEWSGOLD // Для S75
#endif
int strh2int(char *str){
int n,c=0;
while (*str!='\0')
{
if(*str>='a') n=*str-('A'-('9'+1))-('a'-'A');
else if (*str>='A') n=*str-('A'-('9'+1));
else n=*str;
c=c*16+(n-'0');
str++;


}return c;
}

void RunEntry(char *entry){
typedef int (*func)(void);
func ff;
ff=(func)strh2int(entry);
if (ff!=NULL) SUBPROC((void *)(*ff));
}


#ifndef NEWSGOLD
int fread32(int fh, void *buf, int len, unsigned int *err){
  int clen, rlen, total=0;
  while(len){
  if (len>16384) clen=16384; else clen=len;
  total+=(rlen=fread(fh, buf, clen, err));
  if (rlen!=clen) break;
  buf=(char*)buf+rlen;
  len-=clen;
  }return(total);
}


int fwrite32(int fh, void *buf, int len, unsigned int *err){
  int clen, rlen, total=0;
  while(len){
  if (len>16384) clen=16384; else clen=len;
  total+=(rlen=fwrite(fh, buf, clen, err));
  if (rlen!=clen) break;
  buf=(char*)buf+rlen;
  len-=clen;
  }return(total);
}
#endif

int min(int a, int b){ return (a<b)?a:b;}
int max(int a, int b) { return (a>b)?a:b;}
//int abs(int a){ return (a<0)?-a:a;}

int fgets(char *buf,int size,int fh){ return 0;} //fake!!!
void printf(char *s,...){}  //fake!!!
char *strdup(char *s){ return s;}

int savefile(char *fname, char *buf, int size){
  int f,i;
  if((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
  i=fwrite32(f,buf,size,&err);
  fclose(f,&err);
  return i;
}

//------------------------------------------------------------------------------

char *loadfile(char *filename){ // Загрузить файл, распак-ть
  int f; unsigned int err;  char *buf=0;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(loadfilesize=lseek(f,0,2,&err,&err)){
      lenta=loadfilesize;
      buf=(char*)malloc(loadfilesize);
      lseek(f,0,0,&err,&err);
      if(fread32(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
    } fclose(f,&err);
  } return buf;
}


//------------------------------------------------------------------------------
char *toup(char *str){			// К верхнему регистру
  char *val=str;
  while(*val!=NULL){
         if(*val>='a' && *val<='z')  *val-=' ';
    else if(*val>='а' && *val<='п')  *val-=' ';
    else if(*val>='р' && *val<='я')  *val-= 80;
    ++val;
  }
  return str;
}
//------------------------------------------------------------------------------

char *todown(char *str){		// К нижнему регистру
  char *val=str;
  while(*val!=NULL){
         if(*val>='A' && *val<='Z')  *val+=' ';
    else if(*val>='А' && *val<='П')  *val+=' ';
    else if(*val>='Р' && *val<='Я')  *val+= 80;
    ++val;
  }
  return str;
}
//------------------------------------------------------------------------------

int  isalth (unsigned char sym){	// Алфавитный символ ?
  return ((sym>='A' && sym<='Z') || (sym>=(unsigned char)'А' && sym<=(unsigned char)'П')
    || (sym>=(unsigned char)'Р' && sym<=(unsigned char)'Я'));}

//------------------------------------------------------------------------------

int  isval (char sym){		// Символ является числом ?
  return (sym>='0' && sym<='9');}

//------------------------------------------------------------------------------

int strchrpos(const char *s, int c){	// Позиция символа в строке (1-N, 0=нет)
  char *sptr=strchr(s,c);
  return (sptr)?sptr-s+1:NULL;
}

//------------------------------------------------------------------------------
int emptystr(char *str){		// Пустая ли строка
  while(*str && (*str==' ' || *str==9)) ++str;
  return ((*str)?0:1);
}

//------------------------------------------------------------------------------

int   strcmpsize (const char *s1,const char *s2,int size){ // Сравнить строки длины size
  int i;
  for(i=0;i<size && s1[i]==s2[i];i++);
    return (i==size)?NULL:s1[i]-s2[i];
}







//------------------------------------------------------------------------------

int getint(void *ptr){ // Получить int
  if((int)ptr & 3) return *(unsigned char*)ptr | *((unsigned char*)ptr+1)<<8\
    | *((unsigned char*)ptr+2)<<16 | *((unsigned char*)ptr+3)<<24;
  else return *(int*)ptr;
}

//------------------------------------------------------------------------------

int get3int(void *ptr ){ // Получить 3int
  return *(unsigned char*)ptr | *((unsigned char*)ptr+1)<<8 | *((unsigned char*)ptr+2)<<16;
}

//------------------------------------------------------------------------------

short getshort(void *ptr){ // Получить short
  if((int)ptr & 1) return *(unsigned char*)ptr | *((unsigned char*)ptr+1)<<8;
  else return *(short*)ptr;
}

//------------------------------------------------------------------------------

void putint(void *ptr, int data){ // Записать int
  if((int)ptr & 3){ *(char*)ptr=data; *((char*)ptr+1)=data>>8;
    *((char*)ptr+2)=data>>16; *((char*)ptr+3)=data>>24;
  }else *(int*)ptr=data;

}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ |||||||||||||||||||||||||||||||||||||||||||||||||||||||
//------------------------------------------------------------------------------------------------------------
char *intToChar(int data){ // Записать int
char *buf=0;
buf="               ";
sprintf(buf,"%i ",data);
return buf;
}





//------------------------------------------------------------------------------

void putshort(void *ptr, short data){ // Записать short
  if((int)ptr & 1){ *(char*)ptr=data; *((char*)ptr+1)=data>>8;
  }else *(short*)ptr=data;
}

//------------------------------------------------------------------------------

#ifdef GRAPH
/*-----------------------------
смещ.	размер	имя
00	2	'BM'
02	4	Размер файла в байтах;
06	2	0
08	2	0
10	4	Смещение начала изображения в файле;
14	4	Размер этого заголовка, 40;
18	4	Ширина изображения в пикселях;
22	4	Высота изображения в пикселях;
26	2	Число плоскостей изображения, 1;
28	2	Бит на пиксел: 1,4,8 или 24;
30	4	Тип сжатия;
34	4	Размер сжатого изображения в байтах или 0;
38	4	Горизонтальное разрешение, в пикселях / на метр;
42	4	Вертикальное разрешение, в пикселях / на метр;
46	4	Количество используемых цветов;
50	4	Число "важных" цветов;
54	4*N	Карты цветов BGRР;

BMP	заголовок 54 б + палитра 4*256;*/

inline unsigned char rgb888tobyte(int color){
  return ((color>>6)&3)|((color>>11)&0x1C)|((color>>16)&0xE0); }

inline short rgb888toshort(int color){
  return ((color>>3)&0x1f)|((color>>5)&0x7e0)|((color>>8)&0xf800); }

inline unsigned char rgb565tobyte(short color){
  return ((color>>3)&3)|((color>>6)&0x1C)|((color>>8)&0xE0); }

inline short rgb565toshort(short color){
  return color; }


int loadgraphsize=0;
#ifndef HIGHCOLOR
  const int graphpoints=1;
#else
  const int graphpoints=2;
#endif
// Формат файла 2б х 2б у  далее точки (повернуты как надо, без выравнивания)
char *loadgraph(char *filename){ // Загрузить графику (распаковываем и перекодируем) #define HIGHCOLOR учесть

  unsigned char *bmp=0, *buf=0, *pbuf, *pbmp, *ptr;
  int *pal;
  int sizex, sizey, bytepixel, pitch;
  int i,j;
  do{
    if(!(bmp=(unsigned char*)loadfile(filename))) break;
    if(getshort(bmp)!='MB') break;

    sizex=getint(bmp+18);
    sizey=getint(bmp+22);    bytepixel=getshort(bmp+28)>>3;





    if(sizex<1 || sizey<1 || bytepixel<1 || bytepixel>4) break;

    pitch=sizex*bytepixel; //Размер строки

    if(pitch&3) pitch+=4-(pitch&3); //Выравнивание на 4

    if(!(buf=(unsigned char*)malloc(loadgraphsize=sizex*sizey*graphpoints+4))) break;

    *(short*)buf=sizex; *(short*)(buf+2)=sizey;     //записываются размеры картинки в первые 4 байта



    pbuf=buf+4;
    ptr=bmp+getint(bmp+10)+sizey*pitch;

//------------------------------------------------------------------------------------------------------

    switch(bytepixel){
    case 1: //8 -> 8
      memcpy(pal=(int*)(bmp+52),bmp+54,*(short*)(bmp+50)?(*(short*)(bmp+50)<<2):1024);
    for(j=0;j<sizey;j++){
      pbmp=(ptr-=pitch);
      for(i=0;i<sizex;i++){
        *pbuf++=rgb888tobyte(pal[*pbmp++]);
    }  } break;





    case 2: //16 bit
    for(j=0;j<sizey;j++){
      pbmp=(ptr-=pitch);
      for(i=0;i<sizex;i++){

        *pbuf++=rgb565toshort(*(short*)pbmp);
        *pbuf++;
        pbmp+=4;
    }  } break;




    case 3: //24 bit
    for(j=0;j<sizey;j++){
      pbmp=(ptr-=pitch);
      for(i=0;i<sizex;i++){
        *pbuf++=rgb888tobyte(get3int(pbmp));
        pbmp+=3;
    }  } break;
    case 4: //32 bit
    if((i=getint(bmp+10))&3){ //Выровнять данные на границу 4
      j=i-(i&3);
      memcpy(bmp+j, bmp+i, sizey*pitch);
      ptr=bmp+j+sizey*pitch;
    }
    for(j=0;j<sizey;j++){
      pbmp=(ptr-=pitch);
      for(i=0;i<sizex;i++){
        *pbuf++=rgb888tobyte(*(int*)pbmp);
        pbmp+=4;
    }  } break;
    //------------------------------------------------------------------------------------------------------
    }
    mfree(bmp);
    return (char*)buf;
  }while(0);
  if(bmp) mfree(bmp);
  if(buf) mfree(buf);
  return 0;
}
#endif




//============================================================================== D R A W S Y M S ===============================================

//============================================================================== D R A W S Y M F O N ===========================================

//============================================================================== D R A W S Y M ==================================================



//################################################################################ D R A W I M G ###########################################################
//Рисует область из рисунка в точку (х,y) экрана
int drawim(IMGHDR * onse, int x, int y, int xRect, int yRect,int xxRect, int yyRect ){ //последние параметры - рисуемая область из картинки
if (!onse) return 1;
//--------------------------------------------------------------------------------------------------------------------------------------------
if (yRect<0 || yRect>=onse->h)yRect=0;  if (xRect<0 || xRect>=onse->w)xRect=0;  // область в картинке не должна начинаться за ней:)
if (yyRect==0 || (yRect+yyRect>=onse->h))yyRect=onse->h-yRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
if (xxRect==0 || (xRect+xxRect>=onse->w))xxRect=onse->w-xRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
int *pic=(int*)((char*)onse->bitmap);
int i,j,nsize;
//sprintf(logger,"Размер картинки: %i*%i,Tran:%i=%i\nРазмер экрана: %i",onse->h,onse->w, pic[0],  onse->h*onse->w*bits,screensize);
//-----------------------------------------------
int *sc=0;
IMGHDR FI[12]={xxRect,yyRect,8,0,0,0};
FI->w=xxRect;
FI->h=yyRect;
FI->bpnum=0xA;
FI->bitmap=(char *)(sc=(int*)malloc(nsize=xxRect*yyRect*sizeof(int)));

  memset(sc,0,nsize);
int *scr=(int*)((char*)FI->bitmap);
for (i = xRect; i<xRect+xxRect; i++) for(j = yRect; j<yRect+yyRect; j++){
if (((y+j-yRect)<320) && ((x+i-xRect)<240) && ((y+j-yRect)>=0) && ((x+i-yRect)>=0) &&(i>=xRect)&&(j>=yRect)&&(i<xRect+xxRect)&&(j<yRect+yyRect))
{scr[j*xxRect+i]=pic[(j)*onse->w+i];}}


  RECT rc2;  DRWOBJ dobj; StoreXYWHtoRECT(&rc2,x,y,xxRect,yyRect);
  SetPropTo_Obj5(&dobj,&rc2,0,(IMGHDR*)&FI);
  DrawObject(&dobj);

if(sc) mfree(sc);
 return 0;}

//##########################################################################################################################################################
//Рисует область из рисунка в точку (х,y) экранного буфера.
int drawimb(IMGHDR * onse, int x, int y, int xRect, int yRect,int xxRect, int yyRect){ //последние параметры - рисуемая область из картинки
if (!onse) return 1;
if (yRect<0 || yRect>=onse->h)yRect=0;  if (xRect<0 || xRect>=onse->w)xRect=0;  // область в картинке не должна начинаться за ней:)
if (yyRect==0 || (yRect+yyRect>=onse->h))yyRect=onse->h-yRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
if (xxRect==0 || (xRect+xxRect>=onse->w))xxRect=onse->w-xRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
short *scr=(short*)screen;
char *pic=(char*)onse->bitmap;
int i,j;

for (i = xRect; i<xRect+xxRect; i++)for(j = yRect; j<yRect+yyRect; j++){ //i в диапазоне области ВОП рисунка (от xRect до xRect+xxRect)
                                                                         //j в диапазоне области ВОП рисунка (от yRect до yRect+yyRect)
if (((y+j-yRect)<320) && ((x+i-xRect)<240) && ((y+j-yRect)>=0) && ((x+i-xRect)>=0)
    &&(i>=xRect)&&(j>=yRect)&&(i<xRect+xxRect)&&(j<yRect+yyRect))
 {

 scr[(y+j-yRect)*240+i+x-xRect]=RGB16(pic[((j)*onse->w+i)*4+0],pic[((j)*onse->w+i)*4+1],pic[((j)*onse->w+i)*4+2])  ;

 }}
 return 0;
}
//##########################################################################################################################################################
//Рисует область из 1 рисунка в точку (х,y) второго рисунка.
int drawimg2img(IMGHDR * onse, IMGHDR * timage2, int x, int y, int xRect, int yRect,int xxRect, int yyRect){ //последние параметры - рисуемая область из картинки
if (!onse) return 1;
if (yRect<0 || yRect>=onse->h)yRect=0;  if (xRect<0 || xRect>=onse->w)xRect=0;  // область в картинке не должна начинаться за ней:)
if (yyRect==0 || (yRect+yyRect>=onse->h))yyRect=onse->h-yRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
if (xxRect==0 || (xRect+xxRect>=onse->w))xxRect=onse->w-xRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
int *scr=(int*)((char*)timage2->bitmap), *pic=(int*)((char*)onse->bitmap);
int i,j;

for (i = xRect; i<xRect+xxRect; i++)for(j = yRect; j<yRect+yyRect; j++){ //i в диапазоне области ВОП рисунка (от xRect до xRect+xxRect)
                                                                         //j в диапазоне области ВОП рисунка (от yRect до yRect+yyRect)
if (((y+j-yRect)<timage2->h) && ((x+i-xRect)<timage2->w) && ((y+j-yRect)>=0) && ((x+i-xRect)>=0)
    &&(i>=xRect)&&(j>=yRect)&&(i<xRect+xxRect)&&(j<yRect+yyRect))
 {

 scr[(y+j-yRect)*timage2->w+i+x-xRect]=pic[(j)*onse->w+i];

 }}
 return 0;
}
//##########################################################################################################################################################

int light2img(IMGHDR * timage, int povtor, int shir, int EFFECT_, const char colo_[4]){ //20.29   //25 - 140
if (!timage) return 1;
char *scrchar=timage->bitmap;
int i,j,tt,t1,t2,t3,fg;
if (EFFECT_==0) {
for (fg = 0; fg<povtor; fg++){
for (i = 0; i<timage->w; i++)for(j = 0; j<timage->h; j++){ //i-столбец, j-строка
if (scrchar[((j*timage->w)+i)*4+3]<shir){
  tt = scrchar[((j*timage->w)+i)*4+3];
  if (i>0) tt = tt             + scrchar[((j*timage->w)+(i-1))*4+3];
  if (i<(timage->w-1)) tt = tt + scrchar[((j*timage->w)+(i+1))*4+3];
  if (j>0) tt = tt             + scrchar[(((j-1)*timage->w)+i)*4+3];
  if (j<(timage->h-1)) tt = tt + scrchar[(((j+1)*timage->w)+i)*4+3];

  t1 = colo_[2];
  if (i>0) t1 = t1             + scrchar[((j*timage->w)+(i-1))*4];
  if (i<(timage->w-1)) t1 = t1 + scrchar[((j*timage->w)+(i+1))*4];
  if (j>0) t1 = t1             + scrchar[(((j-1)*timage->w)+i)*4];
  if (j<(timage->h-1)) t1 = t1 + scrchar[(((j+1)*timage->w)+i)*4];

  t2 = colo_[1];
  if (i>0) t2 = t2             + scrchar[((j*timage->w)+(i-1))*4+1];
  if (i<(timage->w-1)) t2 = t2 + scrchar[((j*timage->w)+(i+1))*4+1];
  if (j>0) t2 = t2             + scrchar[(((j-1)*timage->w)+i)*4+1];
  if (j<(timage->h-1)) t2 = t2 + scrchar[(((j+1)*timage->w)+i)*4+1];

  t3 = colo_[0];
  if (i>0) t3 = t3             + scrchar[((j*timage->w)+(i-1))*4+2];
  if (i<(timage->w-1)) t3 = t3 + scrchar[((j*timage->w)+(i+1))*4+2];
  if (j>0) t3 = t3             + scrchar[(((j-1)*timage->w)+i)*4+2];
  if (j<(timage->h-1)) t3 = t3 + scrchar[(((j+1)*timage->w)+i)*4+2];

scrchar[((j*timage->w)+i)*4+3]=tt/4.5;
scrchar[((j*timage->w)+i)*4]=t1/5;
scrchar[((j*timage->w)+i)*4+1]=t2/5;
scrchar[((j*timage->w)+i)*4+2]=t3/5;
}



//====================================================================================  очистка =================================



}

for (i = 0; i<timage->w; i++)for(j = 0; j<timage->h; j++){ //i-столбец, j-строка
if (scrchar[((j*timage->w)+i)*4+3]<125){

  int ded=((scrchar[((j*timage->w)+i)*4+3])*1);
scrchar[((j*timage->w)+i)*4+3]=ded;


}}


}}


//##########################################################################################################################################################

if (EFFECT_==1) {
for (fg = 0; fg<povtor; fg++){
for (i = 0; i<timage->w; i++)for(j = 0; j<timage->h; j++){ //i-столбец, j-строка
if (scrchar[((j*timage->w)+i)*4+3]<shir){
  tt = scrchar[((j*timage->w)+i)*4+3];
  if (i>0) tt = tt             + scrchar[((j*timage->w)+(i-1))*4+3];
  //if (i<(timage->w-1)) tt = tt + scrchar[((j*timage->w)+(i+1))*4+3];
  if (j>0) tt = tt             + scrchar[(((j-1)*timage->w)+i)*4+3];
 // if (j<(timage->h-1)) tt = tt + scrchar[(((j+1)*timage->w)+i)*4+3];

  t1 = colo_[2];
  if (i>0) t1 = t1             + scrchar[((j*timage->w)+(i-1))*4];
  //if (i<(timage->w-1)) t1 = t1 + scrchar[((j*timage->w)+(i+1))*4];
  if (j>0) t1 = t1             + scrchar[(((j-1)*timage->w)+i)*4];
 // if (j<(timage->h-1)) t1 = t1 + scrchar[(((j+1)*timage->w)+i)*4];

  t2 = colo_[1];
  if (i>0) t2 = t2             + scrchar[((j*timage->w)+(i-1))*4+1];
 // if (i<(timage->w-1)) t2 = t2 + scrchar[((j*timage->w)+(i+1))*4+1];
  if (j>0) t2 = t2             + scrchar[(((j-1)*timage->w)+i)*4+1];
 // if (j<(timage->h-1)) t2 = t2 + scrchar[(((j+1)*timage->w)+i)*4+1];

  t3 = colo_[0];
  if (i>0) t3 = t3             + scrchar[((j*timage->w)+(i-1))*4+2];
 // if (i<(timage->w-1)) t3 = t3 + scrchar[((j*timage->w)+(i+1))*4+2];
  if (j>0) t3 = t3             + scrchar[(((j-1)*timage->w)+i)*4+2];
  //if (j<(timage->h-1)) t3 = t3 + scrchar[(((j+1)*timage->w)+i)*4+2];

scrchar[((j*timage->w)+i)*4+3]=tt/3;
scrchar[((j*timage->w)+i)*4]=t1/3;
scrchar[((j*timage->w)+i)*4+1]=t2/3;
scrchar[((j*timage->w)+i)*4+2]=t3/3;
}



//====================================================================================  очистка =================================



}

for (i = 0; i<timage->w; i++)for(j = 0; j<timage->h; j++){ //i-столбец, j-строка
if (scrchar[((j*timage->w)+i)*4+3]<125){

  int ded=((scrchar[((j*timage->w)+i)*4+3])*1);
scrchar[((j*timage->w)+i)*4+3]=ded;


}}


}}
//##########################################################################################################################################################


if (EFFECT_==2) {
for (fg = 0; fg<povtor; fg++){
for (i = 0; i<timage->w; i++)for(j = 0; j<timage->h; j++){ //i-столбец, j-строка
if (scrchar[((j*timage->w)+i)*4+3]<shir){
  tt = scrchar[((j*timage->w)+i)*4+3];
  if (i>0) tt = tt             + scrchar[((j*timage->w)+(i-1))*4+3];
  if (i<(timage->w-1)) tt = tt + scrchar[((j*timage->w)+(i+1))*4+3];
  if (j>0) tt = tt             + scrchar[(((j-1)*timage->w)+i)*4+3];
  if (j<(timage->h-1)) tt = tt + scrchar[(((j+1)*timage->w)+i)*4+3];

  t1 = 0;
  if (i>0) t1 = t1             + scrchar[((j*timage->w)+(i-1))*4];
  if (i<(timage->w-1)) t1 = t1 + scrchar[((j*timage->w)+(i+1))*4];
  if (j>0) t1 = t1             + scrchar[(((j-1)*timage->w)+i)*4];
  if (j<(timage->h-1)) t1 = t1 + scrchar[(((j+1)*timage->w)+i)*4];

  t2 = 0;
  if (i>0) t2 = t2             + scrchar[((j*timage->w)+(i-1))*4+1];
  if (i<(timage->w-1)) t2 = t2 + scrchar[((j*timage->w)+(i+1))*4+1];
  if (j>0) t2 = t2             + scrchar[(((j-1)*timage->w)+i)*4+1];
  if (j<(timage->h-1)) t2 = t2 + scrchar[(((j+1)*timage->w)+i)*4+1];

  t3 = 0;
  if (i>0) t3 = t3             + scrchar[((j*timage->w)+(i-1))*4+2];
  if (i<(timage->w-1)) t3 = t3 + scrchar[((j*timage->w)+(i+1))*4+2];
  if (j>0) t3 = t3             + scrchar[(((j-1)*timage->w)+i)*4+2];
  if (j<(timage->h-1)) t3 = t3 + scrchar[(((j+1)*timage->w)+i)*4+2];

scrchar[((j*timage->w)+i)*4+3]=tt/4;
scrchar[((j*timage->w)+i)*4]=t1/4;
scrchar[((j*timage->w)+i)*4+1]=t2/4;
scrchar[((j*timage->w)+i)*4+2]=t3/4;
}



//====================================================================================  очистка =================================



}

for (i = 0; i<timage->w; i++)for(j = 0; j<timage->h; j++){ //i-столбец, j-строка
if (scrchar[((j*timage->w)+i)*4+3]<125){

  int ded=((scrchar[((j*timage->w)+i)*4+3])*1);
scrchar[((j*timage->w)+i)*4+3]=ded;


}}}}

 return 0;
}
//##########################################################################################################################################################

DrwPngImg(IMGHDR *img, int x, int y)
{
  if (img->bpnum == 10) {
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc, x, y, img->w, img->h);
  SetPropTo_Obj5(&drwobj, &rc, 0, img);
  //SetColor(&drwobj, pen, brush);
  DrawObject(&drwobj);}
}
//##########################################################################################################################################################
//Увеличить рисунок.

IMGHDR *morimg(IMGHDR * onse, int rf, int EFFECT_)
{
  if (!onse) return 0;
IMGHDR *outkasta;
outkasta = CreateImgr((onse->w+rf), (onse->h+rf));
 if (EFFECT_==1) drawimg2img(onse, outkasta, 0, 0, 0, 0,onse->w, onse->h);
 else drawimg2img(onse, outkasta, rf/2, rf/2, 0, 0,onse->w, onse->h);
return (outkasta);}




//##########################################################################################################################################################
/*
                _____________________________________Screen_Elki___
               |   A                             A                 |
               |<--+--------------- 240 ---------+---------------->|
               |   |                             |                 |
               |   |                             |                 |
               |   |                             | x               |
               |   |                             |                 |
               |   |                             |                 |
               |   |                             |                 |
               |   |                             |                 |
               |   |         ,-+-----------------+-----------------+------,
               |   |         | |                 |        IMGHDR * onse   |
               |   |         | yRect             |                 `      |
               |   |         | |                 |                 `      |
               |   |         | V_____<-- xxRect -V----------> ____ `      |
               |  296        |       [[[[[[[[[[[[[[[[[[[[[[[[    A `      |
               |(а жаль)     |       [[[[[[[[[[[[[[[[[[[[[[[[    | `      |
               |   |      onse->h    [[[[[[[[[[[[[[[[[[[[[[[[    | `      |
               |   |         |       [[Выводимый прямоугольн[    | `      |
               |   |         |       [[[[[[[[[[ВОП[[[[[[[[[[[ yyRect      |
               |   |         |<----->[[[[[[[[[[[[[[[[[[[[[[[[    | `      |
               |   |   y     | xRect [[[[[[[[[[[[[[[[[[[[[[[[    | `      |
               |<--+---------+------>[[[[[[[[[[[[[[[[[[[[[[[[____V `      |
               |   |         |                                     `      |
               |   |         '---------------- onse->w ------------+------'
               |   |                                               |
               |   |                                               |
               |   |                                               |
               |   |                                               |
               |   |                                               |
               |   |                                               |
               |___V_______________________________________________|
*/


//################################################################################ D R A W I M G B L A C K #################################################
/*int drawimblack(IMGHDR * onse, int x, int y, int xRect, int yRect,int xxRect, int yyRect, int sColor){ //последние параметры - рисуемая область из картинки
if (!onse) return 1;
//--------------------------------------------------------------------------------------------------------------------------------------------
if (yRect<0 || yRect>=onse->h)yRect=0;  if (xRect<0 || xRect>=onse->w)xRect=0;  // область в картинке не должна начинаться за ней:)
if (yyRect==0 || (yRect+yyRect>=onse->h))yyRect=onse->h-yRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
if (xxRect==0 || (xRect+xxRect>=onse->w))xxRect=onse->w-xRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
short *scr=(short*)screen, *pic=(short*)((char*)onse->bitmap);
int i,j;

for (i = xRect; i<xRect+xxRect; i++)for(j = yRect; j<yRect+yyRect; j++){ //i в диапазоне области ВОП рисунка (от xRect до xRect+xxRect)
                                                                         //j в диапазоне области ВОП рисунка (от yRect до yRect+yyRect)
if (((y+j-yRect)<320) && ((x+i-xRect)<240) && ((y+j-yRect)>=0) && ((x+i-xRect)>=0)
    &&(i>=xRect)&&(j>=yRect)&&(i<xRect+xxRect)&&(j<yRect+yyRect)&&(pic[(j)*onse->w+i]==0))
 {

 if (pic[(j)*onse->w+i]!=0)  scr[(y+j-yRect)*240+i+x-xRect]=pic[(j)*onse->w+i];
 else scr[(y+j-yRect)*240+i+x-xRect]=sColor;
 }}
 return 0;
}*/
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

int drawimblack(IMGHDR * onse, int x, int y, int xRect, int yRect,int xxRect, int yyRect, int sColor){ //последние параметры - рисуемая область из картинки
if (!onse) return 1;
//--------------------------------------------------------------------------------------------------------------------------------------------
if (yRect<0 || yRect>=onse->h)yRect=0;  if (xRect<0 || xRect>=onse->w)xRect=0;  // область в картинке не должна начинаться за ней:)
if (yyRect==0 || (yRect+yyRect>=onse->h))yyRect=onse->h-yRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
if (xxRect==0 || (xRect+xxRect>=onse->w))xxRect=onse->w-xRect; //eсли размер области нулевой или вылазит за картинку, то берем до конца картинки
short *pic=(short*)((char*)onse->bitmap);
int i,j,nsize;
//sprintf(logger,"Размер картинки: %i*%i,Tran:%i=%i\nРазмер экрана: %i",onse->h,onse->w, pic[0],  onse->h*onse->w*bits,screensize);
//-----------------------------------------------
scrtype *sc=0;
IMGHDR FI[12]={xxRect,yyRect,8,0,0,0};
FI->w=xxRect;
FI->h=yyRect;
FI->bpnum=8;
FI->bitmap=(char *)(sc=(scrtype*)malloc(nsize=xxRect*yyRect*sizeof(scrtype)));

  memset(sc,0,nsize);
short *scr=(short*)((char*)FI->bitmap);
for (i = xRect; i<xRect+xxRect; i++) for(j = yRect; j<yRect+yyRect; j++){
if (((y+j-yRect)<320) && ((x+i-xRect)<240) && ((y+j-yRect)>=0) && ((x+i-xRect)>=0)
    &&(i>=xRect)&&(j>=yRect)&&(i<xRect+xxRect)&&(j<yRect+yyRect)&&(pic[(j)*onse->w+i]==0))
scr[j*xxRect+i]=sColor;
else {scr[j*xxRect+i]=pic[(j)*onse->w+i];}


}
  RECT rc2;  DRWOBJ dobj; StoreXYWHtoRECT(&rc2,x,y,xxRect,yyRect);
  SetPropTo_Obj5(&dobj,&rc2,0,(IMGHDR*)&FI);
  DrawObject(&dobj);
//DrawImg(y,x,(int)FI);
if(sc) mfree(sc);
 return 0;}
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww



//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
#ifdef INPUT_OK
char *input(char *text, char *BoxTitle){
strcpy (Text_in_Editor, text);
//HEADER_DESC input_hdr={0,0,0,0,NULL,(int)BoxTitle,LGP_NULL};
 // CreateInput();
return Text_out_Editor;
} //Для балета нужно комментировать :(
#endif





#endif







//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww


/*
DrwImg3(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}


IMGHDR * ScreenShot()
{
  LockSched();
  short *p=malloc((SCREENSIZE-HSIZE)*sizeof(short)), *pp=RamScreenBuffer();
  pp+=HSIZE;
  IMGHDR imgs={ScreenW(),(ScreenH()-YDISP),8,(char *)p};
  for(int i=0;i<SCREENSIZE-HSIZE;i++)*p++=*pp++;
  return &imgs;

}


void ScreenShotPlay(IMGHDR  * imgs)
{
  void *canvasdata=BuildCanvas();
  DrawCanvas(canvasdata, 0, 0, ScreenW()-1,ScreenH()-1, 1 );
  DrwImg3(imgs, 0, YDISP, GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2));
  UnlockSched();
}
)*/



