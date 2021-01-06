#include "..\swilib.h"
#include "zlib\zlib.h"

#define byte unsigned char
extern int loadfilesize;

int dounzip(Byte *compr, uLong comprLen, Byte *uncompr, uLong  uncomprLen){
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
//    if(!loadfilenomsg)
//      MessageBox(NULL,"Ошибка распаковки файла!",0,MB_OK); 
      return err;
    }
    d_stream.next_out = uncompr;            /* discard the output */
    d_stream.avail_out = (uInt)uncomprLen;
    err = inflate(&d_stream, 2);
    if(err<0) goto unerr;
    err = inflateEnd(&d_stream);
    if(err<0) goto unerr;
    return 0;
}

int getint4(unsigned char *ptr){
  return ptr[0]|(ptr[1]<<8)|((ptr[2])<<16)|((ptr[3])<<24);
}

char *unzip(char *buf){
  int packsize=1, unpacksize=2, filenamesize=3;
  char *file=buf, *outbuf=0;
  do{
      if(loadfilesize<30) break;
      packsize=getint4((byte*)file+18);
      unpacksize=getint4((byte*)file+22);
      filenamesize=getint4((byte*)file+26);
      //fread(in,file,filenamesize,&err);
      //file[filenamesize]=0;
      file+=30+filenamesize;
      if(file[-1]!='/'){
        if(packsize==unpacksize) memcpy(outbuf=buf,file,loadfilesize=unpacksize); 
        else{
          if(!(outbuf=(char*)malloc(unpacksize))) break;
          dounzip((Byte*)file,packsize,(Byte*)outbuf,loadfilesize=unpacksize);
        }
      }
  }while(0);
  if(buf!=outbuf) mfree(buf);
  return outbuf;
}

