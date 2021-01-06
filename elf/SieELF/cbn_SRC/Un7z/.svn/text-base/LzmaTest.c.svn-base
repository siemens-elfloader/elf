
#include "E:\ARM\swilib.h"
//#include "zlib.h"

// LZMA decoder

// Не менять!!!
#undef _LZMA_IN_CB 
#undef _LZMA_OUT_READ 

#include "LzmaDecode.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#define byte unsigned char
#define true 1
#define false 0

const int waitEOS = 1; 
// waitEOS = 1, if there is no uncompressed size in headers, 
// so decoder will wait EOS (End of Stream Marker) in compressed stream 
const int maxdirsize=32768;
const unsigned int hsize=0x20;//, bufSize=64*(1<<10);

unsigned char properties[]={0x5d,0,0,0x80,0};
CLzmaDecoderState state;  // it's about 24-80 bytes structure, if int is 32-bit 
unsigned int getpos=0;
SizeT outProcessed=0; //Сколько распаковалось
//char newname[128];
char filename[256];
unsigned int err;  

int fread32(int fh, char *buf, int len, unsigned int *err)
{
int clen;
int rlen; 
int total=0;
while(len)
{
if (len>16384) clen=16384; else clen=len;
total+=(rlen=fread(fh, buf, clen, err));
if (rlen!=clen) break;
buf+=rlen;
len-=clen;
}
return(total);
}

int fwrite32(int fh, char *buf, int len, unsigned int *err)
{
int clen;
int rlen; 
int total=0;
while(len)
{
if (len>16384) clen=16384; else clen=len;
total+=(rlen=fwrite(fh, buf, clen, err));
if (rlen!=clen) break;
buf+=rlen;
len-=clen;
}
return(total);
}

void ElfKiller(void)
{
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int getint(unsigned char *ptr){
  return ptr[0]|(ptr[1]<<8)|((ptr[2])<<16)|((ptr[3])<<24);
}

void prepname(char *file){
  unsigned int err;
  do{
    while(*++file && *file!='/');
    if(!*file) break;
    *file=0;
    mkdir(filename,&err);
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



unsigned char *un7z(int inFile, UInt32 compressedSize, UInt32 outSize){ //* на буфер с распак. данными
//  int res;                                            //outProcessed = сколько распаковалось
  SizeT inProcessed;
  unsigned char *inStream;
  unsigned char *outStream=0;

  if(inFile!=-1 && compressedSize && outSize){
    if(!(inStream = (unsigned char *)malloc(compressedSize))) return 0;
   do{
    if(fread32(inFile,(char*)inStream,compressedSize,&err)!=compressedSize)  break;
    if(!(outStream =(unsigned char *)malloc(outSize))) break;

    if (LzmaDecodeProperties(&state.Properties, properties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK){ mfree(outStream); outStream=0; break;}
    state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb));
    LzmaDecode(&state, inStream, compressedSize, &inProcessed, outStream, outSize, &outProcessed);
    mfree(state.Probs);
   }while(0); 
    mfree(inStream);
  }
  return outStream;
}
/* 
int main(int argc, char **argv){
  UInt32 compressedSize=3815;
  UInt32 outSize=16359;
  FILE *inFile = 0;
  FILE *outFile = 0;
  char *outbuff;

  if (argc < 2 || argc > 3){
    printf("\nUsage:  lzmadec file.lzma [outFile]\n");
    return 1;
  }

  inFile = fopen(argv[1], "rb");
  if (inFile == 0) return 2;
  
  outbuff=un7z(inFile, compressedSize, outSize);
  if(outbuff){
    outFile = fopen(argv[2], "wb+");
    if (outFile == 0){ free(outbuff); return 3;}
    fwrite(outbuff, 1, outProcessed, outFile); 
    free(outbuff);
    fclose(outFile);
  }
  fclose(inFile);
  return 0;
}
*/

/////////////////////////////////////////////////////
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

//char *tonewname(char *s, int size){
//  memcpy(newname,s,size);
//  newname[size]=0;
//  return newname;
//}


int main(char *exename, char *fname){
  byte bb[0x20], *b=bb;
  char *buffer=0;
  int inFile=-1, outFile=-1;
  int headoff,headsize,h2size,pos,cnt,maxcnt,p,pp,empty;
  int *filesize, *fileunsize;
  char *name, *file;
  int ii;
  //
do{
  if(!fname || (inFile=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) break;
  strcpy(filename,fname);
  file=filename+strlen(filename);
  while(--file>filename && *file!='.');
  *file=0;
  mkdir(filename,&err);
  *file++='\\';
  //
  if(fread(inFile,b,hsize,&err)!=hsize)  break;
  if(b[0]!=0x37 || b[1]!=0x7a) break;
	headoff=(b[12]&0xff)|((b[13]&0xff)<<8)|
  	((b[14]&0xff)<<16)|((b[15]&0xff)<<24);
	headsize=(b[20]&0xff)|((b[21]&0xff)<<8)|
  	((b[22]&0xff)<<16)|((b[23]&0xff)<<24);

  //inStream.skip(headoff+0x20);
  lseek(inFile,headoff+0x20,0,&err,&err);
  if(fread(inFile,b,hsize,&err)!=hsize)  break;
  //if (LzmaDecodeProperties(&state.Properties, properties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK) return 3;
  //state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb));

  if (b[0]==1 && b[1]==4 && b[2]==6){ //Распакованный заголовок!!
		//System.arraycopy(b,0,decoder.m_OutWindow._buffer,0,hsize);
    buffer=malloc(headsize-hsize);
    lseek(inFile,headoff+0x20,0,&err,&err);
    fread32(inFile,buffer,headsize-hsize,&err);
		//inStream.read(decoder.m_OutWindow._buffer,hsize,headsize-hsize);
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
    lseek(inFile,ii,0,&err,&err);
    h2size=headoff+0x20-ii;
	  //inStream.skip(0x20+get8b(b));
    if(!(buffer=(char*)un7z(inFile,h2size,maxdirsize))) break;
  //if (!decoder.Code(main, main.zipbuf,inStream, main.os, h2size, handle, file))
    h2size=maxdirsize;
  }

	b=(byte*)buffer;
	//////////// отладка (табл.симв.)
//  outFile = fopen("tab", "wb+"); 
//  fwrite(buffer, 1, 20000, outFile); 
//  fclose(outFile);
	///////////
	if (b[0]!=1 || b[1]!=4 || b[2]!=6 || b[3]!=0) //Распакованный заголовок!!
		break;
	getpos=4;
	maxcnt=get8b(b);
	if(b[getpos++]!=9) break;
	
        filesize=(int *)malloc(maxcnt*2*sizeof(int));
        fileunsize=filesize+maxcnt;
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
    for(cnt=0;cnt<maxcnt; cnt++){ // && !main.stop
	while(name[pp]!=0) ++pp;
        ///////
        memcpy(file,name+p,pp-p+1);
        prepname(file);
        outFile=fopen(filename,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err);//tonewname(name+p,pp-p)
	p=++pp;
        lseek(inFile,pos,0,&err,&err);
        mfree(buffer);/////
        if(!(buffer=(char*)un7z(inFile,filesize[cnt],fileunsize[cnt]))){
  	   //free(filesize); fclose(inFile); 
           if(outFile!=-1) fclose(outFile,&err);
           goto lexit;
           //return 11;
        }
	pos+=filesize[cnt];
        if(outFile!=-1){
          fwrite32(outFile,buffer,fileunsize[cnt],&err);
          fclose(outFile,&err);
        }
    }
    mfree(buffer);
lexit:
    mfree(name);
    mfree(filesize);
 }while(0);
 if(inFile!=-1) fclose(inFile,&err);
 SUBPROC((void *)ElfKiller);
 return (0);
}

/*
int main(char *exename, char *fname)
{
  int in,out;
  int packsize=1, unpacksize=2, filenamesize=3;
  unsigned int err;
  char *buf, *file=filename;
////// // char dummy[sizeof(MAIN_CSM)];
  if(fname && (in=fopen(fname,A_ReadOnly+A_BIN,0,&err))!=-1){
    strcpy(filename,fname);
    file=filename+strlen(filename);
    while(file>filename && *file!='\\') --file;
    ++file;
    while(1){
      if(fread(in,file,30,&err)!=30) break;
      if(getint(file)!=0x4034b50) break;
      packsize=getint(file+18);
      unpacksize=getint(file+22);
      filenamesize=getint(file+26);
      fread(in,file,filenamesize,&err);
      file[filenamesize]=0;
      if(file[filenamesize-1]!='/'){
        if((buf=(char*)malloc((packsize==unpacksize)?packsize:(packsize+unpacksize)))!=NULL){
          fread32(in,buf,packsize,&err);
          prepname(file);
          if ((out=fopen(filename,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))!=-1){
            if(packsize==unpacksize){
              fwrite32(out,buf,packsize,&err);
            }else{
              unzip((Byte*)buf,packsize,(Byte*)(buf+packsize),unpacksize);
              fwrite32(out,buf+packsize,unpacksize,&err);
            }
            fclose(out,&err);
          }
          mfree(buf);
        }
      }
    }
////////  CreateCSM(&maincsm,dummy,0);  
  fclose(in,&err);
 }
/////// // FreeWS(ws_filelist);
/////// // ws_filelist=NULL;
 SUBPROC((void *)ElfKiller);
 return (0);
}
*/

//int main(int argc, char **argv){
//  unpack(*++argv);
//  return 0;
//}
