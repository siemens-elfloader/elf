#include "C:\ARM\inc\swilib.h"
#include "C:\ARM\inc\zlib.h"
unsigned int err;

int unzip(Byte *compr, uLong comprLen, Byte *uncompr, uLong  uncomprLen){
    int err;
    z_stream d_stream; /* decompression stream */
    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;
    d_stream.next_in  = compr;
    d_stream.avail_in = (uInt)comprLen;
    err = inflateInit2(&d_stream,-MAX_WBITS);
    if(err!=Z_OK){ 
   unerr:
      return err;
    }
    d_stream.next_out = uncompr;            /* discard the output */
    d_stream.avail_out = (uInt)uncomprLen;
    err = inflate(&d_stream, Z_NO_FLUSH);//2
    if(err<0) goto unerr;
    err = inflateEnd(&d_stream);
    if(err<0) goto unerr;
    return 0;
}



int getint(unsigned char *ptr){
  return ptr[0]|(ptr[1]<<8)|((ptr[2])<<16)|((ptr[3])<<24);
}


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

typedef struct
{
  int packsize;
  int unpacksize;
  int namesize;
  int number;
  int to_this;
  char *fname;
}INZIP_FILE;
INZIP_FILE **FILES;
int NumFiles=0;

int GetNumOfFiles(char *fname)
{
  int in;
  int num=0,filenamesize=3,size=2;char *file=filename;
  if((in=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
    strcpy(filename,fname);
    file=filename+strlen(filename);
    while(--file>filename && *file!='.');
    *file=0;*file++='\\';
    START:
   if(fread(in,file,30,&err)!=30)goto END;
   if(getint((unsigned char*)file)!=0x4034b50)goto END;
   filenamesize=getint((unsigned char*)file+26);
   size=getint((unsigned char*)file+18);
   fread(in,file,filenamesize,&err);
   file[filenamesize]=0;
   lseek(in,size,S_CUR,&err,&err);
   num++; 
   goto START;
  END:
  fclose(in,&err);
  return num;
 }
 return 0;
}

void GetFiles(char *fname)
{
  NumFiles=GetNumOfFiles(fname);
  FILES=(INZIP_FILE**)malloc(sizeof(INZIP_FILE));
  int all_pack=0;
  int Num=0,
  packsize=1, unpacksize=2, filenamesize=3,in;
  char *file=filename;
  if((in=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
    strcpy(filename,fname);
    file=filename+strlen(filename);
    while(--file>filename && *file!='.');
    *file=0;
    *file++='\\';
    START:
      if(fread(in,file,30,&err)!=30)goto END;
      if(getint((unsigned char*)file)!=0x4034b50)goto END;
      packsize=getint((unsigned char*)file+18);
      unpacksize=getint((unsigned char*)file+22);
      filenamesize=getint((unsigned char*)file+26);
      fread(in,file,filenamesize,&err);
      dos2ascii(file,file);
      file[filenamesize]=0;
      FILES[Num]=malloc(sizeof(INZIP_FILE));
      FILES[Num]->fname=(char*)malloc(256);
      FILES[Num]->packsize=packsize;
      FILES[Num]->unpacksize=unpacksize;
      FILES[Num]->namesize=filenamesize;
      FILES[Num]->number=Num;
      FILES[Num]->to_this=all_pack;
      strcpy(FILES[Num]->fname,file);
      lseek(in,packsize,S_CUR,&err,&err);
      all_pack+=packsize+30+filenamesize;
      Num++;
      goto START;
  END:
fclose(in,&err);
 }
}

void UnZipFile(char *fname,INZIP_FILE *FILE)
{
WSHDR *ws=AllocWS(256);
int in,out;
char *buf;
char *file=filename;
DrawRectangle(0,0,239,319,1,GetPaletteAdrByColorIndex(21),GetPaletteAdrByColorIndex(21));
if((in=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
    strcpy(filename,fname);
    file=filename+strlen(filename);
    while(--file>filename && *file!='.');
    *file=0;
    mkdir(filename,&err);
    *file++='\\';
      if(FILE->to_this>0)lseek(in,FILE->to_this,S_SET,&err,&err);
      if(fread(in,file,30,&err)!=30)goto END;
      if(getint((unsigned char*)file)!=0x4034b50)goto END;
      fread(in,file,FILE->namesize,&err);
      dos2ascii(file,file);
      file[FILE->namesize]=0;
      if(file[FILE->namesize-1]!='/')
      {
        if((buf=(char*)malloc((FILE->packsize==FILE->unpacksize)?FILE->packsize:(FILE->packsize+FILE->unpacksize)))!=NULL)
        {
         fread(in,buf,FILE->packsize,&err);
         prepname(file);
        if((out=fopen(filename,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))!=-1)
          {
          if(FILE->packsize==FILE->unpacksize)fwrite(out,buf,FILE->packsize,&err);
            else{
              
              if(unzip((Byte*)buf,FILE->packsize,(Byte*)(buf+FILE->packsize),FILE->unpacksize)==Z_MEM_ERROR)ShowMSG(1,(int)"Опять нехватает(");
                 fwrite(out,buf+FILE->packsize,FILE->unpacksize,&err);
            }
            fclose(out,&err);
        }
        }
      wsprintf(ws,"Файл: %s",file);
      DrawString(ws,0,1,239,319,8,2,GetPaletteAdrByColorIndex(4),0);
        mfree(buf);
      }
  END:
    fclose(in,&err);
  }

 FreeWS(ws);
}







int UnZIP(char *fname)
{
  GetFiles(fname);

  for(int i=0;i<NumFiles;i++){UnZipFile(fname,FILES[i]);mfree(FILES[i]->fname);mfree(FILES[i]);}
 return (0);
}
