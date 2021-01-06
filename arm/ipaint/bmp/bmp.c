#include "C:\arm\inc\swilib.h"
#include "bmp.h"



void IMGHDR_from_bmp8(BMP_HDR hdr)
{
	unsigned int i, j,w=hdr.MAP_HEAD.biwidth,h=hdr.MAP_HEAD.biheight;
        
        hdr.img->w=w;
        hdr.img->h=h;
        hdr.img->bpnum=PNG_8;
	for(i=h; i>0; i--)
	for(j=0; j<w; j++)
	  {
		memcpy(hdr.img->bitmap+((i-1)*w+j)*4, hdr.pallete+hdr.Bitmap[(h-i)*w+j]*4, 3);
                hdr.img->bitmap[((i-1)*w+j)*4+3]=0xFF;
	  }
}




void IMGHDR_from_bmp16(BMP_HDR hdr)
{
	unsigned int i, j,w=hdr.MAP_HEAD.biwidth,h=hdr.MAP_HEAD.biheight;
	unsigned short c2;
	char c32[4]={0,0,0,0xff};
        hdr.img->w=w;
        hdr.img->h=h;
        hdr.img->bpnum=PNG_16;
	for(i=h; i>0; i--)
        for(j=0; j<w; j++)
	  {
		c2=hdr.Bitmap[((h-i)*w+j)*2]+hdr.Bitmap[((h-i)*w+j)*2+1]*0x100;
		c32[2] = (c2 & 0xF800) >> 8;
	        c32[1] = (c2 & 0x07E0) >> 3;
		c32[0] = (c2 & 0x001F) << 3;
		memcpy(hdr.img->bitmap+((i-1)*w+j)*4, c32, 4);
	  }
}

void IMGHDR_from_bmp24(BMP_HDR hdr)
{
	unsigned int i, j,w=hdr.MAP_HEAD.biwidth,h=hdr.MAP_HEAD.biheight;
        
        hdr.img->w=w;
        hdr.img->h=h;
        hdr.img->bpnum=PNG_24;
	for(i=h; i>0; i--)
	for(j=0; j<w; j++)
	  {
		memcpy(hdr.img->bitmap+((i-1)*w+j)*4, hdr.Bitmap+((h-i)*w+j)*3, 3);
                hdr.img->bitmap[((i-1)*w+j)*4+3]=0xFF;
	  }
}


void IMGHDR_from_bmp32(BMP_HDR hdr)
{
	unsigned int i,w=hdr.MAP_HEAD.biwidth,h=hdr.MAP_HEAD.biheight;
        hdr.img->w=w;
        hdr.img->h=h;
        hdr.img->bpnum=PNG_24;
	for(i=0; i<w*h; i++)
	{
		memcpy(hdr.img->bitmap+i*4, hdr.Bitmap+i*4, 3);
		hdr.img->bitmap[i*4+3]=0xff;
	}
}

BMP_HDR readBmp(char *fname)
{
  BMP_HDR hdr;
  hdr.fname=malloc(strlen(fname));
  strcpy(hdr.fname,fname);
  int k=0;
  int f = fopen(fname,A_ReadOnly+A_BIN,P_READ,0);
  fread(f,&hdr.HEAD,SIZE_BMP_HEAD,0);
  fread(f,&hdr.MAP_HEAD,SIZE_BITMAP_HEAD,0);
  if(hdr.MAP_HEAD.bicompression!=BI_RGB)goto end;
  switch(hdr.MAP_HEAD.bibitcount)
  {
  case BITS_1:case BITS_2:case BITS_4:case BITS_48:ShowMSG(1,(int)"error 1,2,4 or 48 bit not supported");hdr.last_err=UNK_FRMT_ERR;goto end;
  case BITS_8:

    hdr.Bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight+3);
    hdr.img=(IMGHDR*)malloc(sizeof(IMGHDR));
    hdr.img->bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*4);
    hdr.pallete=malloc(hdr.MAP_HEAD.biclrused*4);
    
    fread(f,hdr.pallete,hdr.MAP_HEAD.biclrused*4,0);
    
    lseek(f,hdr.HEAD.bfoffbits,S_SET,0,0);
    

    
    k=hdr.MAP_HEAD.biwidth;
    if(hdr.MAP_HEAD.biwidth%4) k=k+4-(hdr.MAP_HEAD.biwidth%4);
    for(int i=0; i<hdr.MAP_HEAD.biheight; i++)
    fread(f,hdr.Bitmap+hdr.MAP_HEAD.biwidth*i,k,0);
    IMGHDR_from_bmp8(hdr);
    
    break;
    
    
  case BITS_16:
    hdr.Bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*2+3);
    hdr.img=(IMGHDR*)malloc(sizeof(IMGHDR));
    hdr.img->bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*4);
    lseek(f,hdr.HEAD.bfoffbits,S_SET,0,0);
    k=hdr.MAP_HEAD.biwidth*2;
    if((hdr.MAP_HEAD.biwidth*2)%4)k=k+4-((hdr.MAP_HEAD.biwidth*2)%4);
    for(int i=0; i<hdr.MAP_HEAD.biheight; i++)
    fread(f,hdr.Bitmap+hdr.MAP_HEAD.biwidth*2*i,k,0);
    IMGHDR_from_bmp16(hdr);
    break;
  case BITS_24:
    
    hdr.Bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*3+3);
    hdr.img=(IMGHDR*)malloc(sizeof(IMGHDR));
    hdr.img->bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*4);
    lseek(f,hdr.HEAD.bfoffbits,S_SET,0,0);
    k=hdr.MAP_HEAD.biwidth*3;
    if((hdr.MAP_HEAD.biwidth*3)%4)k=k+4-((hdr.MAP_HEAD.biwidth*3)%4);
    for(int i=0; i<hdr.MAP_HEAD.biheight; i++)
    fread(f,hdr.Bitmap+hdr.MAP_HEAD.biwidth*3*i,k,0);
    IMGHDR_from_bmp24(hdr);
    
    break;
    
  case BITS_32:
    
    hdr.Bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*4);
    hdr.img=(IMGHDR*)malloc(sizeof(IMGHDR));
    hdr.img->bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*4);
    lseek(f,hdr.HEAD.bfoffbits,S_SET,0,0);
    for(int i=hdr.MAP_HEAD.biheight; i>0; i--)
    fread(f,hdr.Bitmap+hdr.MAP_HEAD.biwidth*4*(i-1),hdr.MAP_HEAD.biwidth*4,0);
    IMGHDR_from_bmp32(hdr);
    
    break;    
  }
end:
  fclose(f,0);
  return hdr;
}
void bmp24_from_IMGHDR(IMGHDR *img,BMP_HDR hdr)
{
  memcpy(hdr.Bitmap, img->bitmap, hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*4);
}

int SaveBmp(IMGHDR *img,char *fname)
{
  BMP_HDR hdr;
  int f = fopen(fname,A_WriteOnly+A_BIN+A_Create,P_WRITE,0);
  hdr.HEAD.bftype=0x4D42;
  hdr.MAP_HEAD.bisize=SIZE_BITMAP_HEAD;
  hdr.MAP_HEAD.biwidth=img->w;
  hdr.MAP_HEAD.biheight=img->h;
  hdr.MAP_HEAD.biplanes=1;
  hdr.MAP_HEAD.biclrused=0;
  hdr.MAP_HEAD.biclrimp=0;
  hdr.HEAD.bfoffbits=SIZE_BMP_HEAD+SIZE_BITMAP_HEAD+hdr.MAP_HEAD.biclrused*4;
  switch(img->bpnum)
  {
  case PNG_8:hdr.MAP_HEAD.bibitcount=BITS_8;break;
  case PNG_16:hdr.MAP_HEAD.bibitcount=BITS_16;break;
  case PNG_24:hdr.MAP_HEAD.bibitcount=BITS_24;break;
  }
  hdr.MAP_HEAD.bicompression=BI_RGB;
  fwrite(f,&hdr.HEAD,SIZE_BMP_HEAD,0);
  fwrite(f,&hdr.MAP_HEAD,SIZE_BITMAP_HEAD+hdr.MAP_HEAD.biclrused*4,0);
    switch(hdr.MAP_HEAD.bibitcount)
  {
     case BITS_24:
    hdr.Bitmap=malloc(hdr.MAP_HEAD.biwidth*hdr.MAP_HEAD.biheight*4);
    bmp24_from_IMGHDR(img,hdr);
    int k=hdr.MAP_HEAD.biwidth*3;
    if((hdr.MAP_HEAD.biwidth*3)%4)k=k+4-((hdr.MAP_HEAD.biwidth*3)%4);
    for(int i=0; i<hdr.MAP_HEAD.biheight; i++)
    fwrite(f,hdr.Bitmap+hdr.MAP_HEAD.biwidth*3*i,k,0);
    
    
    break;
  }
  fclose(f,0);
  return 1;
}
