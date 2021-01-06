#define NOLOAD
// LZMA decoder
// Не менять!!!
#undef _LZMA_IN_CB 
#undef _LZMA_OUT_READ 

#include "E:\ARM\swilib.h"
#include "LzmaDecode.h"

extern int loadfilesize;

#define byte unsigned char
#define true 1
#define false 0

const int waitEOS = 1; 
// waitEOS = 1, if there is no uncompressed size in headers, 
// so decoder will wait EOS (End of Stream Marker) in compressed stream 
const int maxdirsize=4096;//32 kb
const unsigned int hsize=0x20;//, bufSize=64*(1<<10);

unsigned char properties[]={0x5d,0,0,0x80,0};
CLzmaDecoderState state;  // it's about 24-80 bytes structure, if int is 32-bit 
unsigned int getpos=0;
SizeT outProcessed=0; //Сколько распаковалось
char filename2[256];


//int getint(unsigned char *ptr){
//  return ptr[0]|(ptr[1]<<8)|((ptr[2])<<16)|((ptr[3])<<24);
//}

void prepname(char *file){
  unsigned int err;
  do{
    while(*++file && *file!='/');
    if(!*file) break;
    *file=0;
    mkdir(filename2,&err);
    *file='\\';
  }while(1);
}

int strcmp2(char *s, int p1, int p2, int size){
	while(--size>=0)
	  if(s[p1++]!=s[p2++]) return false;
	return true;
}

int getempty(byte *buf, int pos, int cnt){
	int i,k,rez=0;
	do{
	  k=buf[pos++]&0xff;
	  for(i=0;i<8;i++){
	    if((k&0x80)==0) return rez;
	    k<<=1;
	    ++rez;
	  }
	}while(true);
}

unsigned char *goun7z(char *inStream, UInt32 compressedSize, UInt32 outSize){ //* на буфер с распак. данными
//  int res;                                            //outProcessed = сколько распаковалось
  SizeT inProcessed;
//  unsigned char *inStream;
  unsigned char *outStream=0;

  if(compressedSize && outSize){ //&& inFile!=-1
//    if(!(inStream = (unsigned char *)malloc(compressedSize))) return 0;
   do{
//    if(fread32(inFile,(char*)inStream,compressedSize,&err)!=compressedSize)  break;
    if(!(outStream =(unsigned char *)malloc(outSize))) break;
    if (LzmaDecodeProperties(&state.Properties, properties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK){ mfree(outStream); outStream=0; break;}
    state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb));
    LzmaDecode(&state, (unsigned char*)inStream, compressedSize, &inProcessed, outStream, outSize, &outProcessed);
    mfree(state.Probs);
   }while(0); 
//    mfree(inStream);
  }
  return outStream;
}

//SevenZip
      int get8b(byte *b){	//перекодировка 8байт
		int i=0,v;
		byte bb=b[getpos];
		while(bb&0x80){ bb<<=1; ++i;}
		v=bb>>i;
		switch(i){
		  case 1: v=(v<<8)|(b[++getpos]&0xff); break;
		  case 2: v=(v<<16)|(b[++getpos]&0xff)|((b[++getpos]&0xff)<<8); break;
		  case 3: v=(v<<24)|(b[++getpos]&0xff)|((b[++getpos]&0xff)<<8)|((b[++getpos]&0xff)<<16); break;
		}
		++getpos;
		return v;
	}

/////// Вынесены наружу
int *filesize=0, *fileunsize, *filepos;
int cnt=0,maxcnt=0,pos=0;
char *gbuf=0;

int un7zinit(char *buf){ // Иниц. un7z
  gbuf=buf;
  byte *b=(unsigned char*)buf;
//  unsigned int err;
  char *buffer=0;// *outbuf=0;
//  int inFile=-1, outFile=-1;
  int headoff,headsize,h2size,p,pp,empty,rez=0;
  char *name;//, *file;
  int ii;
do{
  if(loadfilesize<hsize)  break;
  if(buf[0]!=0x37 || buf[1]!=0x7a) break;
  headoff=(buf[12]&0xff)|((buf[13]&0xff)<<8)|
  ((buf[14]&0xff)<<16)|((buf[15]&0xff)<<24);
  headsize=(buf[20]&0xff)|((buf[21]&0xff)<<8)|
  ((buf[22]&0xff)<<16)|((buf[23]&0xff)<<24);
  //inStream.skip(headoff+0x20);
  //lseek(inFile,headoff+0x20,0,&err,&err);
  //if(fread(inFile,b,hsize,&err)!=hsize)  break;
  b=(byte*)buf+headoff+0x20;
  if (b[0]==1 && b[1]==4 && b[2]==6){ //Распакованный заголовок!!
    buffer=malloc(headsize);//-hsize);
    memcpy(buffer,buf+headoff+0x20,headsize);//-hsize);
    //lseek(inFile,headoff+0x20,0,&err,&err);
    //fread32(inFile,buffer,headsize-hsize,&err);
    h2size=headsize;
  }else{
   	if (b[0]!=0x17 || b[1]!=6) break;
	  for(getpos=2;getpos<hsize-1;getpos++)
	    if(b[getpos]==0 && b[getpos+1]==0xc) break;
	  if(b[++getpos]!=0xc) break;
	  ++getpos;
	  h2size=get8b(b);
  	getpos=2;
    ii=0x20+get8b(b);
    //lseek(inFile,ii,0,&err,&err);
    h2size=headoff+0x20-ii;
   //inStream.skip(0x20+get8b(b));//buf,ii
    if(!(buffer=(char*)goun7z(buf+ii,h2size,maxdirsize))) break;
    h2size=maxdirsize;
  }
	b=(byte*)buffer;
//////////// отладка (табл.симв.)
//  int f;
//  unsigned int err;
//  if((f=fopen("0:\\ZBin\\234",A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))==-1) break;
//  fwrite(f, buffer, headsize, &err);
//  fclose(f,&err);
//////////
	if (b[0]!=1 || b[1]!=4 || b[2]!=6 || b[3]!=0) //Распакованный заголовок!! 00000
          break;
	getpos=4;
	maxcnt=get8b(b);
	if(b[getpos++]!=9) break;
	
        filesize=(int *)malloc(maxcnt*3*sizeof(int));
        fileunsize=filesize+maxcnt;
        filepos=fileunsize+maxcnt;
	for(cnt=0;cnt<maxcnt;cnt++){
	   filesize[cnt]=get8b(b);
        }
	for(;getpos<h2size-1;getpos++)
	  if(b[getpos]==0 && b[getpos+1]==0xc) break;
        if(b[++getpos]!=0xc) break;
	++getpos;
        for(cnt=0;cnt<maxcnt;cnt++){
	   fileunsize[cnt]=get8b(b);
        }
        for(;getpos<h2size-1;getpos++)
	  if(b[getpos]==0 && b[getpos+1]==5) break;
	if(b[++getpos]!=5) break;
        ++getpos;
	get8b(b);
	empty=0;
	if(b[getpos]==0xe){	//Пустые заголовки
	    ++getpos;
	    empty=getempty(b,++getpos,cnt>>3);
	    getpos+=(cnt>>3);//?
	    while(b[++getpos]==0);// ++getpos;
	 }
	 if(b[getpos]==0x11){
	    ++getpos;
	    get8b(b);
         }
      --getpos;
      while(b[++getpos]==0);
      name = malloc(h2size>>1);
      for(p=pp=0;p<(h2size>>1) && pp<cnt;p++){
        name[p]=(char)((b[getpos++]&0xff)+((b[getpos++]&0xff)<<8));
        if(name[p]==0)
        if(empty>0){
          p=pp=0; --p; --empty;
        }else ++pp;
      }
      p=pp=0;
      pos=0x20;
      mfree(buffer);/////(outbuf)!!!!
      buffer=0;     

      if(buffer) mfree(buffer);
//lexit:
    mfree(name);
//    mfree(filesize);
    rez=1;//ALL OK
   for(cnt=0;cnt<maxcnt;cnt++){
     filepos[cnt]=pos;
     pos+=filesize[cnt];
   }
 }while(0);
// if(inFile!=-1) fclose(inFile,&err);
// SUBPROC((void *)ElfKiller);
//  mfree(buf);
   pos=0x20;
   cnt=0;
  return rez; //1=OK
}


void un7zexit(){  // Вызывать при выходе
  if(filesize) mfree(filesize);
  filesize=0;
}

//ret loadfilesize==-1 если конец архива
char *un7znext(){ // Распаковать следующий un7z файл
  char *outbuf;
  if(maxcnt<=0) return 0; 
  if(cnt>=maxcnt){ loadfilesize=-1; return 0;}
  if(!(outbuf=(char*)goun7z(gbuf+pos,filesize[cnt],fileunsize[cnt]))) return 0;
  loadfilesize=fileunsize[cnt];
  pos+=filesize[cnt];
  ++cnt;
  return outbuf;
}

char *un7z(int num){ // Распаковать un7z num файл
  if(num<0 || num>=maxcnt) return 0;
  loadfilesize=fileunsize[num];
  return (char*)goun7z(gbuf+filepos[num],filesize[num],fileunsize[num]);
}
