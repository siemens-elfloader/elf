
// VM  mapped files
// подгрузка ромов частями

//#include "..\mylib.h"
#include "neopop.h"
//#include "swilib.h"
//#include "..\random.h"


unsigned int randint( int max );
#define rand randint(0x100000)

//extern unsigned int randseed;
//extern unsigned char USERAM, SGOLD2;

#define pagesize 0x4000
#define pagemask 0x3FFF
#define pageshift 14

/*
struct fmapst{
  FILE* f; //handle
  char **mem; //сюда помещ. рез-т 
  int pages; //всего страниц в файле
  int allocpages; //выделено памяти под страниц в файле
};
*/
struct fmapst fmap;


//extern int fmapopen(char *fname, struct fmapst *fmap, int freepages); //открыть файл и спроецировать на память страниц maxpages
//extern void fmapread(struct fmapst *fmap, int page); // "подгрузить" страницу
//extern void fmapclose(struct fmapst *fmap); //закрыть файл

#ifdef SEGA

unsigned int aa;
uint8 *yy;

uint8 READ_ROM(int a){ 
	//return READ_BYTE(yy,a);
  a=a^1;
  aa = (a>>pageshift);
  if(!fmap.mem[aa])
    fmapread(&fmap,aa);
  return fmap.mem[aa][(a & pagemask)];//rom.bank
  //return READ_BYTE((uint8*)fmap.mem+aa,a & pagemask);
}

uint8 READ2_ROM(int a){ 
	//return READ_BYTE(yy,a);
  //a=a^1;
  aa = (a>>pageshift);
  if(!fmap.mem[aa])
    fmapread(&fmap,aa);
  return fmap.mem[aa][(a & pagemask)];//rom.bank
  //return READ_BYTE((uint8*)fmap.mem+aa,a & pagemask);
}


uint16 READ_WROM(int a){ 
  //return READ_WORD(yy,a);
	return (READ2_ROM(a+1)<<8) | READ2_ROM(a);
}

//#define READ_BYTE(BASE, ADDR) (BASE)[(ADDR)^1]
//#define READ_WORD(BASE, ADDR) (((BASE)[(ADDR)+1]<<8) |          
                              //(BASE)[(ADDR)])

void xswap(char *mem, int length)
{
    int i;
	char temp;
    for(i = 0; i < length; i += 2)
    {
        temp = mem[i+0];
        mem[i+0] = mem[i+1];
        mem[i+1] = temp;
    }
}

#endif

#define ffopen fopen
#define ffread fread
#define llseek lseek
#define ffclose fclose

int fmapopen(char *fname, struct fmapst *fmap, int freepages){ //открыть файл и спроецировать на память, оставить своб. free страниц
  int i, pages;
  int f;
  char **mem;
  if((fmap->f=f=ffopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 2; //no open
  loadfilesize=llseek(f,0,2,&err,&err);
  llseek(f,0,0,&err,&err);
  if(!(pages=fmap->pages=loadfilesize>>pageshift)) return 3; //file empty
  if(!(mem=fmap->mem=(char**)malloc(pages<<2))) return 4; //no mem
  memset(mem,0,pages<<2);
  for(i=0;i<pages;i++)
	  //if(i>7){ *mem++=0; break;} else  ////////test - vary slow!!!
		  if(!(*mem++=(char*)malloc(pagesize))) break;
  if(i<pages)
    while(--freepages>=0){ mfree(*--mem); *mem=0; --i;}
  *mem=0;
  fmap->allocpages=i;
  //cache
  mem=fmap->mem;
  while(--i>=0){
    ffread(f,*mem,pagesize,&err);
#ifdef SEGA
	xswap(*mem,pagesize);//add
#endif
	mem++;
  }
  return 0;
}

void fmapclose(struct fmapst *fmap){ //закрыть файл
  char **mem=fmap->mem;
  int i=fmap->pages;
  while(--i>=0){
    if(*mem) mfree(*mem);
    ++mem;
  }
  mfree(fmap->mem);
  if(fmap->f>0) ffclose(fmap->f,&err);
  memset(&fmap,0,sizeof(struct fmapst));
}

void readfile(int f, char *buf, int n){//читать сектор
  llseek(f,n<<pageshift,0,&err,&err);
  ffread(f,buf,pagesize,&err);
#ifdef SEGA
  xswap(buf,pagesize); //add
#endif
}


//int random(){ return 1;}//FAKE!!! //должен возвр. 2 байта!!!

void fmapread(struct fmapst *fmap, int page){ // "подгрузить" страницу
  int n;
  if(fmap->mem[page]) return;
  char **mem=fmap->mem+1;//+1 резерв!!!
  //получ. СЧ сектор или по частоте n=random/pageees
   n=rand%(fmap->allocpages-1);
  while(n>=0) if(*mem++) --n; //>=0????
  //читать сектор
  readfile(fmap->f, fmap->mem[page]=*--mem, page);
  *mem=0; //освободить место
}


//пример чтения сектора
//  if(!mem[j=i>>pageshift]) fmapread(f,mem,j);
//  return mem[j][i&pagemask];

//проверка границ
//if((i&pagemask)<pagesize-4)

//открытие ф-а
//if((f=fmapopen(fname,getfreeram()*3/4))<0) error
//fmapclose();

//под буфер
//char *mem2[100]; //100 4 кб страниц
//ramalloc(mem2,100);

//////////

//void Killer(void){
//extern void *ELF_BEGIN;
//((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
//}

