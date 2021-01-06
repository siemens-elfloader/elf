#include <swilib.h>



/*
typedef signed char	CHAR;
typedef unsigned char	BYTE;
typedef short		SHORT;
typedef unsigned short	WORD;
typedef int		INT;
typedef unsigned int	UINT;
typedef long		LONG;
typedef unsigned long	DWORD;
typedef struct 
{
	DWORD size,
    zero_res,
	offbits;
} BMP_HEAD;
typedef struct 
{ 
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER;

typedef struct
{
  BMP_HEAD bmp;
  BITMAPINFOHEADER img;
} BMP_HDR;


static const BMP_HDR Def_BMP=
{
	{
		0,
		0,
		54	
	},
	{
		40,
		0,
		0,
		1,
		16,
		0,
		0,
		0xB40,
		0xB40,
		0,
		0
	}
};


BMP_HDR BMP;
unsigned const short BMP_id = 0x4d42;


extern void Tlog(char *string);

int WriteBMP(char *fname,char *data,int w,int h,char bpp)
{
  int f = fopenA(fname,A_ReadWrite+A_Create+A_Truncate,P_WRITE,0);
  if(f==-1) {return 0;}
  
  BMP = Def_BMP;
  BMP.img.biWidth=w;
  BMP.img.biHeight=h;
  BMP.img.biClrUsed=0;
  BMP.img.biClrImportant=0;
  if(bpp==16)
  {
    BMP.bmp.size=w*h*2+54;
    BMP.img.biBitCount=16;
  }
  else if(bpp==24)
  {
    BMP.bmp.size=w*h*3+54;
    BMP.img.biBitCount=24;
  }
  else if(bpp==32)
  {
    BMP.bmp.size=w*h*4+54;
    BMP.img.biBitCount=32;
  }
  
  fwrite(f,&BMP_id,2,0);
  fwrite(f,&BMP,52,0);
  
  int i;
  int size = w*(BMP.img.biBitCount/8);
  i = size%4;
  if(i) size+=4-i;
  char *buf = malloc(size);
  if(!buf) {fclose(f,0);return 0;}
  zeromem(buf,size);
  
  Tlog("write data...");
  for(i=h-1;i>=0;i--)
  {
    if(bpp==16) memcpy(buf,data+((w*2)*i),w*2);
    fwrite(f,buf,size,0);
  }
  Tlog("data writed");
  
  mfree(buf);
  fclose(f,0);
  return 1;
}
*/


#define BI_RGB  0L
typedef struct _BITMAPFILEHEADER
{
    unsigned short bfType;
    unsigned short bfSize;
    char null1;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned short bfOffBits;
    char null2;
} BITMAPFILEHEADER;//?????????? ?????

typedef struct _BITMAPINFOHEADER
{
    unsigned long biSize;
    long biWidth;
    long biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned long biCompression;
    unsigned long biSizeImage;
    long biXPelsPerMeter;
    long biYPelsPerMeter;
    unsigned long biClrUsed;
    unsigned long biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;//?????????? ???????????




static void Write16(int fp,char *data,int rowsize,int w,int h)
{
  char *dst = malloc(rowsize+100);
  for(int y=0;y<h;y++)
  {
    short *src = (short*)data+(h-1-y)*2*w;
    for(int x=0;x<w;x++)
    {
      *(dst+x*2) = *src++;
    }
    fwrite(fp, dst, rowsize,0);
  }
  mfree(dst);
}




int WriteBMP(const char *filename, unsigned char *pImgData, unsigned int iImgW, unsigned int iImgH,char bpp)
{
    BITMAPFILEHEADER BMFileHdr;
    BITMAPINFOHEADER BMInfoHdr;
    unsigned char *pSrc;//??????? ?????
    unsigned char *pDst;//???????? ?????
    unsigned int x, y, iRowSize;
    int bOK= 0;
    int bp;
    
    if(bpp==16) bp = 2;
    else if(bpp==24) bp = 3;
    else if(bpp==32) bp = 4;
    iRowSize = bp*iImgW;
    if(iRowSize%4) iRowSize+=4-(iRowSize%4);
    
    memset(&BMFileHdr, 0, sizeof(BITMAPFILEHEADER));//????????? ?????????? BMP ?????
    BMFileHdr.bfType= 0x4D42;
    BMFileHdr.bfSize= iRowSize *iImgH+ sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER);
    BMFileHdr.bfOffBits= sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER);

    memset(&BMInfoHdr, 0, sizeof(BITMAPINFOHEADER));//????????? ?????????? BMP ???????????
    BMInfoHdr.biSize= sizeof(BITMAPINFOHEADER);
    BMInfoHdr.biWidth= iImgW;
    BMInfoHdr.biHeight= iImgH;
    BMInfoHdr.biPlanes= 1;
    BMInfoHdr.biBitCount= bpp;
    BMInfoHdr.biCompression= BI_RGB;

    //pDst=(unsigned char *)malloc(iRowSize+100); //????? ??? ????? ??????? ???????????
    
    int fp = fopenA(filename,A_ReadWrite+A_Create,P_WRITE,0);
    
    
    fwrite(fp,&BMFileHdr, sizeof(BITMAPFILEHEADER),0);//=14
    fwrite(fp,&BMInfoHdr, sizeof(BITMAPINFOHEADER),0);
    Tlog("writing header completed");
    
    Write16(fp,pImgData,iRowSize,iImgW,iImgH);
    /*for(y= 0; y< iImgH; y++)
    {
        pSrc = pImgData+(iImgH-1-y)*bp*iImgW;
        for(x=0; x< iImgW; x++)
        {
            *(pDst+ x* bp+ 2)= *pSrc++;
            *(pDst+ x* bp+ 1)= *pSrc++;
            *(pDst+ x* bp+ 0)= *pSrc++;
        }
        fwrite(fp, pDst, iRowSize,0);
    }
    
    Tlog("writing bitmap completed");
    */
    
    
    fclose(fp,0);
    
    //mfree(pDst);
    
    bOK= 1;
    return bOK;
}








