#include "../inc/swilib.h"
#include "bmplib.h"
//#include "..\mylib.h"

void log(char*str)
{
  int f = fopen("0:\\patches.txt",A_WriteOnly+A_TXT+A_Create,P_WRITE,0);
  lseek(f,0,S_END,0,0);
  fwrite(f,str,strlen(str),0);
  fclose(f,0);
}
//char buff[256];

int SaveBMP(const char *fname, const char *rastrum, const int width, const int height,  char *palette,
                      const unsigned int palette_size, const unsigned int bit_count, const unsigned int compression)
{
  if(rastrum==NULL || !width || !height || bit_count>32)
    return -1;  
    
  unsigned int err;
  int fp=fopen(fname, A_ReadWrite+A_Create, P_WRITE, &err);
  if(fp==-1) return -1;
  const unsigned int bitsize=width*height*bit_count/8;
  const unsigned int headsize=sizeof(BITMAPFILEHEADER);
  const unsigned int infosize=sizeof(BITMAPINFOHEADER);

   
 
  //head
  BITMAPFILEHEADER header;
  zeromem(&header, headsize);
  header.bfType=BF_TYPE;
  //header.bfReserved1=0;
  //header.bfReserved2=0;
  header.bfOffBits=headsize+infosize+palette_size;
  header.bfSize=header.bfOffBits+bitsize;
  int i=fwrite(fp, &header, headsize, &err);    
  //headinfo 
  BITMAPINFOHEADER info;
  zeromem(&info, infosize);
  info.biSize=infosize;
  info.biWidth=width;
  info.biHeight=-height;
  //if(width%4)info.biWidth++;
  //if(height%4)info.biHeight++;
  if ( width % 4 != 0 ) {
info.biWidth = 4 * ( width / 4 + 1 );
}
  info.biPlanes=1;
  info.biBitCount=bit_count;
  info.biCompression=compression;
  info.biClrUsed=0;
  info.biClrImportant=0;
 
  /*
  info.biSizeImage=0;//if bi.compression==0
   info.biXPelsPerMeter=0xB40;
   info.biYPelsPerMeter=0xB40;
   
   info.biClrImportant=0;*/
   
  fwrite(fp, &info, infosize, &err);
  fwrite(fp, palette, palette_size, &err);
  fwrite(fp, rastrum, bitsize, &err);
  fclose(fp, &err);
  
  char s[64];
  sprintf(s, "bfsize: %d\n offbits: %d\n bitsize: %d", header.bfSize, header.bfOffBits, bitsize);
  ShowMSG(1, (int)s);
  return 1;
}

char *SieRastrDecoder(const char *rastrum, const int permission)
{
    char *bitmap=NULL;
    char str[128];
    if(rastrum!=NULL)
    {
        unsigned int rlen=0, wlen=0, offset;
        const int mlen=permission*2;
        bitmap=malloc(mlen+1);
        while(wlen<mlen)
        {
            if(rastrum[rlen]<0x7F)             //0x7F  (0xFF,0xFF) число повторений следующих 2-х байт
            {
                for(int i=0; i<rastrum[rlen]; i++, wlen+=2)
                {
                    //bitmap=realloc(bitmap, wlen+3); //на глаз заметно, что скорость обработки уменьшается
                    memcpy(bitmap+wlen, rastrum+rlen+1, 2);
          
                }
                rlen+=3;
            }
            else                                            //0x80 0xFF,0xFF,0xFF...(0x80) количество несжатых последующих байт
            {
                offset=(0xFF-rastrum[rlen])*2+2;
                //bitmap=realloc(bitmap, wlen+offset+1); //на глаз заметно, что скорость обработки уменьшается
                memcpy(bitmap+wlen, rastrum+rlen+1, offset);
                wlen+=offset;
                rlen+=offset+1;
   
            }
        }
   
       sprintf(str, "mlen: %d\nrlen: %d\nwlen: %d", mlen, rlen, wlen);
        ShowMSG(1,(int) str);
    }
    return bitmap;
}
