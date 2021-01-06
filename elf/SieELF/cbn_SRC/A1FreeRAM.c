
// FreeRAM - ������ � ������� (����������.)
// ������ ������������ �������� ������ �� S75!!!
//#define FREERAM
#ifdef FREERAM

unsigned char a11=0;//������ �������� �� ������ 0 ��������
// ������ ZERO ��������
extern unsigned int randseed;
extern const void *ZEROSTART; //=&randseed;
#ifdef SNES
const int ZEROSIZE=0x3c27d;    // ������ ZERO ��������
#elif GBA             //����������!!! ��. � map �����!
const int ZEROSIZE=0x82ae9;
const void *ZEROSTART=&randseed;//a11; 
#else
extern const int ZEROSIZE;
#endif
#include "swilib.h"
#include "random.h"

extern int screensize;
extern unsigned char USERAM, SGOLD2;

//#define NEWSGOLD
#define pagesize 4096
#define pagemask 4095
#define pageshift 12
#define ramstart (char*)0xA8000000
#define ramsize 0x800000 // � �� S75 0x1000000
#define rampages (ramsize>>pageshift)
//int rampages; //������� ����� (���������)
//#define maxrampages rampages//0x1000000/pagesize

char freeram[rampages];//, *freeramend=freeram+rampages; 
char useram[rampages];

#define defmaxblock 1024  //more?
unsigned int maxblock=0; //����� ������ ����
unsigned char blockcnt[defmaxblock]; //���-�� ������ � ������ -1
unsigned int blockalloc[defmaxblock]; //���������� ������ ������ //���� short

#define masknozero 1      // �� ��������
#define maskmap 2         // ������ ������� (���� � map)
#define maskelfzero 3     // ZERO ������� �����
#define maskramscreen 4   // ������� ������
#define maskbegin 5       // malloc()++

inline void getnextmask(){ if(++a11<maskbegin) a11=maskbegin;}

inline unsigned int howfreerampages(unsigned int size){
  return (size>>pageshift)+((size&pagemask)?1:0);}
  
int freeramblocks(){ //������� 4 �� ������ ��������
  if(!USERAM) return (GetFreeRamAvail()>>pageshift);
  int i,j;
  for(i=j=0;i<rampages;i++)
    if(!freeram[i]) ++j;
  return j;
}
/*
void ramfree(char **mem, int n){ //���������� ������ �� N ������
  if(!USERAM){ //mfreeh(mem); 
    return;}
  *--mem;//?
  do{
    if(*++mem)
      freeram[((*mem)-ramstart)>>pageshift]=0;
  }while(--n>0);
}

int ramalloc(char **mem, unsigned int n){ //�������� ���� ������ �� N 4�� ������
  unsigned int i, ii, size=1, k;//2?
  char *s;  
  if(!USERAM){
    if(!(s=(char*)malloch(n<<pageshift))) return 0;
    do{
      *mem++=s;
      s+=pagesize;
    }while(--n>0);
    return 1;
  }
  if(freeramblocks()-4<n) return 0;
  getnextmask();
  do{
    i=0;
    do{
      k=0; ii=i;
      while(!freeram[i++]) ++k;
      if(k>0 && k<=size){ 
        do{
          *mem++=ramstart+(ii<<pageshift);
          freeram[ii++]=a11;
          if(!--n) return 1;
        }while(--k>0);
      }
    }while(i<rampages);
  }while((size<<=1)<(1<<23));
  return 0;
}
*/
void *malloc(unsigned int size){ //�������� ���� ������
  if(!USERAM){ //S75
#ifdef BLOCKRAM    
    void *ret;
    if(!size || maxblock>=defmaxblock || !(ret=malloch(size))) return 0;
    blockalloc[maxblock++]=(unsigned int)ret;
    return ret;
#else    
    return malloch(size);
#endif    
  }
  if(!size || size>=(1<<20)) return 0;
  size=howfreerampages(size);
  //����� ���������� �� ��������� ������ ������� size
  unsigned int i=0, ii, mi=0, mk=(unsigned)-1, k;
  do{
    k=0; ii=i;
    while(!freeram[i++]) ++k;
    if(k>=size && k<mk){ 
      mi=ii; if((mk=k)==size) break;
    }
  }while(i<rampages);
  if(!mi) return 0;//no memory!
  //������� � ����.
  if(--size){
    if(maxblock>=defmaxblock) return 0;
    blockcnt[maxblock]=size;
    blockalloc[maxblock++]=mi;
  }
  getnextmask();
  for(i=0;i<size+1;i++)
    freeram[mi+i]=a11;
  return ramstart+(mi<<pageshift);
}


void mfree(void *mem){ //���������� ������
  int n;
  unsigned int i, ptr;
  if(!mem) return;
  if(!USERAM){ //S75
    if(!mem) return;
#ifdef BLOCKRAM    
    for(i=n=0;i<maxblock;i++)
      if(blockalloc[i]==(unsigned int)mem) break;
    if(i<maxblock){
      blockalloc[i]=blockalloc[--maxblock];
      mfreeh(mem); 
    } 
#else
    mfreeh(mem); 
#endif    
    return;
  }
  ptr=(((char*)mem)-ramstart)>>pageshift;//&mem??
  if(ptr>=rampages) return;//
  for(i=n=0;i<maxblock;i++)
    if(blockalloc[i]==ptr) break;
  if(i<maxblock){ //found
    n=blockcnt[i];
    blockalloc[i]=blockalloc[--maxblock];
    blockcnt[i]=blockcnt[maxblock];
  }
  do{
    freeram[ptr++]=0;
  }while(--n>=0);
}

void FreeRamExit(){ //�������� �������. ������ �� ����������
  int i;
  char *ram;
  if(!USERAM){
    //���������� ������ (S75 � ��.)
    while(*blockalloc) mfree((void*)*blockalloc);
  }else{
    //�������� ��������
    for(i=0, ram=ramstart; i<rampages;i++,ram+=pagesize)
      if(!useram[i]) memsetd(ram,0,pagesize>>2);
  }
}

void FreeRamInit(char *exename){ //�������� ��������, �������� �������, �������� �������.
  int i, f;
  if(!USERAM) return; //add
  char *ram=ramstart;
//  rampages=((SGOLD2)?0x1000000:0x800000)>>pageshift;
  a11=1;//fake
  //�������� ��������
  for(i=0;i<rampages;i++,ram+=pagesize)
    freeram[i]=iszero(ram,pagesize>>2)?masknozero:0;
  //������ �����
  memcpy(exename+strlen(exename)-3,"ram",4);
  if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,useram,rampages,&err);
    fclose(f,&err);
    //���������
    for(i=0;i<rampages;i++)
      if(useram[i]) freeram[i]=maskmap;
  }
  //�������� Zero �������!
  i=((char*)ZEROSTART)-ramstart;
  f=howfreerampages(i+ZEROSIZE);
    //(f>>pageshift)+((f&pagemask)?1:0);
  for(i>>=pageshift;i<=f; i++){//???
    freeram[i]=maskelfzero;
  }
  //�������� RamScreenBuffrer! ���� �� ?
//  i=((char*)RamScreenBuffer())-ramstart;
//  f=howfreerampages(i+screensize);
    //(f>>pageshift)+((f&pagemask)?1:0);
//  for(i>>=pageshift;i<=f; i++){//???
//    freeram[i]=maskramscreen;
//  }
  //����������� ��� ��������� ��� ������
  memcpy(useram,freeram,rampages); 
  //�������� use ����
//  memcpy(exename+strlen(exename)-3,"use",4);
//  if((f=fopen(exename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
//    fwrite(f,freeram,rampages,&err); 
//    fclose(f,&err);
//    //ShowMSG(1,(int)"���������");
//  }
  Randomize();
}

void FreeRamDebug(char *exename, char *ext){
  int f;
  strcpy(strrchr(exename,'.')+1,ext);
  if((f=fopen(exename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    fwrite(f,freeram,rampages,&err); 
    fclose(f,&err);
  }
}

////////mapped files
/*
int fmapopen(char *fname, struct fmapst *fmap, int maxpages){ //������� ���� � ������������� �� ������
  int i,f, pages;
  if(!maxpages) return 1;
  if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 2;
  if(!(loadfilesize=lseek(f,0,2,&err,&err))) return 3;
  pages=howfreerampages(loadfilesize);
  if(maxpages>pages) maxpages=pages;
  if(!(fmap->mem=(char**)(!USERAM)?malloch(pages<<2):malloc(pages<<2))) return 4;
  memsetd(fmap->mem,0,pages);
  if(!(ramalloc(fmap->mem,maxpages))) return 5;
  //cache
  for(i=0;i<maxpages;i++)
    fread(f,fmap->mem[i],pagesize,&err);
  fmap->f=f;
  fmap->allocpages=maxpages;
  fmap->pages=pages;
  return 0;
}

void fmapclose(struct fmapst *fmap){ //������� ����
  ramfree(fmap->mem,fmap->pages);
  mfree(fmap->mem);
  fclose(fmap->f,&err);
  memset(&fmap,0,sizeof(struct fmapst));
}

void readfile(int f, char *buf, int n){//������ ������
  lseek(f,n<<pageshift,0,&err,&err);
  fread(f,buf,pagesize,&err);
}


//int random(){ return 1;}//FAKE!!! //������ �����. 2 �����!!!

void fmapread(int page){ // "����������" ��������
  int i,n;
  if(fmap.mem[page]) return;
  //�����. �� ������ ��� �� ������� n=random/pageees
 // n=((fmap.allocpages<256)?Random():(Random()|(Random()<<8)))%fmap.allocpages;
  n=randint(fmap.allocpages);
  for(i=0;n>0;i++)
    if(fmap.mem[i]) --n;
  //������ ������
  readfile(fmap.f, fmap.mem[page]=fmap.mem[i], page);
  fmap.mem[i]=0; //���������� �����
}
*/

//������ ������ �������
//  if(!mem[j=i>>pageshift]) fmapread(f,mem,j);
//  return mem[j][i&pagemask];

//�������� ������
//if((i&pagemask)<pagesize-4)

//�������� �-�
//if((f=fmapopen(fname,getfreeram()*3/4))<0) error
//fmapclose();

//��� �����
//char *mem2[100]; //100 4 �� �������
//ramalloc(mem2,100);

//////////

//void Killer(void){
//extern void *ELF_BEGIN;
//((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
//}
/*
void test(char *fname){
  char *mem[100], *buf1, *buf2;
  ramalloc(mem,100);
  buf1=malloc(20000);
  buf2=malloc(200000);
  mfree(buf1);
  mfree(buf2);
  ramfree(mem,100);
  //part 2
  if((fmapopen(fname, &fmap, freeramblocks()*3/4))) return;
  //������� ��. ���� � ��������� � ���, ����� ���. (���� ���������)
  fmapclose(&fmap);
}

int main2(char *exename, char *fname){ //���� fname �� �������� ��� (����. ������)
  FreeRamInit(exename);
  test(exename);
  FreeRamDebug(exename,"deb");//
  FreeRamExit();
  ShowMSG(1,(int)"���������");
//  SUBPROC((void *)Killer);
  return (0);
}   
*/
#endif
