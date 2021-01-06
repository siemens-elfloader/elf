
// mylib.c

#include "mylib.h"

unsigned int err=0;
int loadfilesize=0;


#define fread32 ffread
#define fwrite32 ffwrite


void *memset(void *mem, int val, int size){
  char *s=(char*)mem;
  while(--size>=0) *s++=(char)val;
  return mem;
}

void *memsetw(void *mem, int val, int size){
  short *s=(short*)mem;
  while(--size>=0) *s++=val;
  return mem;
}

int min(int a, int b){ return (a<b)?a:b;}
int max(int a, int b){ return (a>b)?a:b;}
int abs(int a){ return (a<0)?-a:a;}

int fgets(char *buf,int size,int fh){ return 0;} //fake!!!
void printf(char *s,...){}  //fake!!!
char *strdup(char *s){ return s;}

void *memcpyrev(void *to, void *from, int size){
  char *s=(char*)to+size, *ss=(char*)from+size;
  while(--size>=0)
    *--s=*--ss;
  return to;
}

int savefile(char *fname, char *buf, int size){
  FILE *f;
  int i;
  if((f=ffopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==0) return 0;
  i=fwrite32(f,buf,size,&err); 
  ffclose(f,&err); 
  return i;
}

char *loadfile(char *filename){ // Загрузить файл, распак-ть
  FILE *f; unsigned int err;  char *buf=0;
  if((f=ffopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=0){
    if(loadfilesize=llseek(f,0,2,&err,&err)){
      buf=(char*)malloc(loadfilesize);
      llseek(f,0,0,&err,&err);
      if(fread32(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
    } ffclose(f,&err);
#ifdef UNPACK
    extern char *un7z(char *buf);
    extern char *unrar(char *buf);
    extern char *unzip(char *buf);
    if(buf && loadfilesize>4){
#ifndef NORAR
      if(*(int *)buf=='!raR') buf=unrar(buf); //unrar
      else
#endif      
#ifndef NOZIP
      if(*(int*)buf==0x4034b50) buf=unzip(buf); //unzip
      else
#endif
#ifndef NO7Z      
      if(*(short*)buf=='z7') buf=un7z(buf); //un7z
#endif
     ;      
    }
//#ifdef SAVETEST
//  int out=fopen("0:\\ZBin\\123",A_WriteOnly+A_BIN+A_Create,P_WRITE,&err);
//  fwrite32(out,buf,loadfilesize,&err);
//  fclose(out,&err);
//#endif    
    
#endif      
  } return buf;
}

//void *memset(void *buf, int val, int size){
//  char *b=(char*)buf;
//  while(--size>=0) *b++=val; 
//  return buf;
//}

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

int  isalth (unsigned char sym){	// Алфавитный символ ?
  return ((sym>='A' && sym<='Z') || (sym>=(unsigned char)'А' && sym<=(unsigned char)'П')
    || (sym>=(unsigned char)'Р' && sym<=(unsigned char)'Я'));}

int  isval (char sym){		// Символ является числом ?
  return (sym>='0' && sym<='9');}

int strchrpos(const char *s, int c){	// Позиция символа в строке (1-N, 0=нет)
  char *sptr=strchr(s,c);
  return (sptr)?sptr-s+1:NULL;
}
  
int emptystr(char *str){		// Пустая ли строка
  while(*str && (*str==' ' || *str==9)) ++str;
  return ((*str)?0:1);
}

char  *alltrim (char *str){		// Удалить пробелы по бокам строки
  char *s;
  if(!*str) return str;
  while(*str==' ' || *str==9) ++str;
  s=str;
  while(*s) ++s;
  while(s>str && (*(s-1)==' ' || *(s-1)==9)) --s;
  *s=NULL;
  return str;
}

int   strcmpsize (const char *s1,const char *s2,int size){ // Сравнить строки длины size
  int i;
  for(i=0;i<size && s1[i]==s2[i];i++);
    return (i==size)?NULL:s1[i]-s2[i];
}

int getint(void *ptr){ // Получить int
  if((int)ptr & 3) return *(unsigned char*)ptr | *((unsigned char*)ptr+1)<<8\
    | *((unsigned char*)ptr+2)<<16 | *((unsigned char*)ptr+3)<<24;
  else return *(int*)ptr;
}

int get3int(void *ptr){ // Получить 3int
  return *(unsigned char*)ptr | *((unsigned char*)ptr+1)<<8 | *((unsigned char*)ptr+2)<<16; 
}

short getshort(void *ptr){ // Получить short
  if((int)ptr & 1) return *(unsigned char*)ptr | *((unsigned char*)ptr+1)<<8;
  else return *(short*)ptr;
}

void putint(void *ptr, int data){ // Записать int
  if((int)ptr & 3){ *(char*)ptr=data; *((char*)ptr+1)=data>>8;
    *((char*)ptr+2)=data>>16; *((char*)ptr+3)=data>>24;
  }else *(int*)ptr=data;
  
}
 
//void putshort(void *ptr, short data){ // Записать short
//  if((int)ptr & 1){ *(char*)ptr=data; *((char*)ptr+1)=data>>8;
//  }else *(short*)ptr=data;
//}

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
    if(!(bmp=(unsigned char*)
#ifndef NOLOAD
    loadfile(filename)
#else
    filename
#endif
    )) break;
    if(getshort(bmp)!='MB') break;
    sizex=getint(bmp+18);
    sizey=getint(bmp+22);
    bytepixel=getshort(bmp+28)>>3;
    if(!sizex || !sizey || bytepixel<1 || bytepixel>4) break;
    pitch=sizex*bytepixel;
    if(pitch&3) pitch+=4-(pitch&3);
    if(!(buf=(unsigned char*)malloc(loadgraphsize=sizex*sizey*graphpoints+4))) break;
    *(short*)buf=sizex; *(short*)(buf+2)=sizey; 
    pbuf=buf+4;
    ptr=bmp+getint(bmp+10)+sizey*pitch;
#ifndef HIGHCOLOR //1 byte
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
        *pbuf++=rgb565tobyte(*(short*)pbmp);
        pbmp+=2;
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
 #else    // 2 byte
    switch(bytepixel){
    case 1: //8 -> 16
    memcpy(pal=(int*)(bmp+52),bmp+54,*(short*)(bmp+50)?(*(short*)(bmp+50)<<2):1024);
    for(j=0;j<sizey;j++){
      pbmp=(ptr-=pitch);
      for(i=0;i<sizex;i++){
        *(short*)pbuf=rgb888toshort(pal[*pbmp++]);
        pbuf+=2;
    }  } break;
    case 2: //16 bit
    for(j=0;j<sizey;j++){
      pbmp=(ptr-=pitch);
      for(i=0;i<sizex;i++){
        *(short*)pbuf=rgb565toshort(*(short*)pbmp);
        pbmp+=2;
        pbuf+=2;
    }  } break;
    case 3: //24 bit
    for(j=0;j<sizey;j++){
      pbmp=(ptr-=pitch);
      for(i=0;i<sizex;i++){
        *(short*)pbuf=rgb888toshort(get3int(pbmp));
        pbmp+=3;
        pbuf+=2;
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
        *(short*)pbuf=rgb888toshort(*(int*)pbmp);
        pbmp+=4;
        pbuf+=2;
    }  } break;
#endif    
    }
    mfree(bmp);
    return (char*)buf;
  }while(0);
  if(bmp) mfree(bmp);
  if(buf) mfree(buf);
  return 0;
}
#endif

// Вывести на экран в поз х,у картинку размером sizex,sizey с поз. в bmp х0,у0 и 
// прозрачным цветом (если<>0)  Флаги: 0x40 = всегда
void bitblt(void *screen, void *bmp, int x, int y, int sizex, int sizey, int x0, int y0,  int colormask, int flags){
  int i,j, sizexx, bmpx, bmpy;
  // Проверка на дурака
  if(!screen || !bmp || x>=132 || y>=176) return;
  bmpx=*(short*)bmp; 
  bmpy=*(short*)((char*)bmp+2);
  if(!sizex) sizex=bmpx;
  if(!sizey) sizey=bmpy;
  
  if(x<0){ sizex+=x; x0-=x; x=0;}
  if(y<0){ sizey+=y0; y0-=y; y=0;}
  if(x0<0 || x0>=bmpx || y0<0 || y0>=bmpy || sizex<=0 || sizey<=0) return;
  
  if(x+sizex>=132) sizex=132-x;
  if(x0+sizex>=bmpx) sizex=bmpx-x0;
  if(y+sizey>=176) sizey=176-y;
  if(y0+sizey>=bmpy) sizey=bmpy-y0;
  
#ifndef HIGHCOLOR
  char *scr=(char*)screen, *pic=(char*)bmp+4;
  sizexx=sizex;
#else
  short *scr=(short*)screen, *pic=(short*)((char*)bmp+4);
  sizexx=sizex<<1;
#endif
  scr+=132*y+x;
  pic+=bmpx*y0 + x0;
  if(colormask || (flags&0x40)){
    for(j=0; j<sizey; j++, scr+=132-sizex, pic+=bmpx-sizex)
      for(i=0; i<sizex; i++, scr++, pic++)
        if(*pic!=
#ifndef HIGHCOLOR
  (char)
#else
 (short)             
#endif
   colormask) *scr=*pic;
  }else{
    for(j=0; j<sizey; j++, scr+=132, pic+=bmpx)
      memcpy(scr,pic,sizexx);
  }
}


//void debsave();
//char debarea[10000], *deb=debarea;
////unsigned int err;
//
//void debsave(){
//  int f;
//  if(deb==debarea) return;
//  f=fopen("0:\\ZBin\\nes\\log",A_ReadWrite+A_BIN+A_Create+A_Append,P_READ+P_WRITE,&err);
//  if (f==-1) return;
//  fwrite32(f,(unsigned char*)debarea,deb-debarea,&err);
//  fclose(f,&err);
//  deb=debarea;
//}
//
//void debug(int num, int val){
//  if(deb-debarea<9800){
//  sprintf(deb,"\n%d = %d",num,val);
//  deb+=strlen(deb);
//  }
//}

    void memcpy3(signed char *to, signed char *from, int size){
      to+=size;
      from+=size;
      while(--size>=0){
        *--to=*--from;
      }
    }

    void memcpy4(signed char *to, signed char *from, int size){
      while(--size>=0){
        *to++=*from++;
      }
    }
    
    void memmove(signed char *to, signed char *from, int size){
      if(from<to)
        if(from+size>=to) memcpy3(to,from,size);
        else memcpy4(to,from,size);
      else memcpy4(to,from,size);
    }


char *strcpy2(char *to, char *from){
  char *res=to--;
  do{ *++to=*from++;
  }while(*to);
  return res;
}

char *strcat2(char *to, char *from){
  char *res=to--;
  while(*++to); --to;
  do{ *++to=*from++;
  }while(*to);
  return res;
}


inline FILE *ffopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber){
  return fopen(cFileName,(iFileFlags&1)?"wb":"rb");
}

inline int ffread(FILE *FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber){
  return fread(cBuffer, 1, iByteCount, FileHandler);
}

inline unsigned int ffwrite(FILE *FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber){
  return fwrite(cBuffer, 1, iByteCount, FileHandler);
}

inline void ffclose(FILE *FileHandler, unsigned int *ErrorNumber){
  fclose(FileHandler);
}

inline unsigned int llseek(FILE *FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2){
  //if(origin==2) return ftell(FileHandler);
  fseek(FileHandler,offset,origin);
  return ftell(FileHandler);
}

inline void mfree(void *mem){
  free(mem);
}

//void *malloc(unsigned int size){
//}
      
//#define min(a,b) ((a)<(b))?(a):(b)
//#define max(a,b) ((a)<(b))?(b):(a)

//int min(int a, int b);
//int max(int a, int b);
//void *memset(void *mem, int val, int size);

//#define SUBPROC
//#define REDRAW onredraw



