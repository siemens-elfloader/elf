#include "liblcd.h"
#define RGB16(R, G, B) (((B>>3)&0x1F) | ((G<<3)&0x7E0) | ((R<<8)&0xF800))


unsigned char videoram[240*320*2];
IMGHDR img = {240,320,8,(char*)videoram};


void DrwPx(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc, x, y, img->w, img->h);
  SetPropTo_Obj5(&drwobj, &rc, 0, img);
  DrawObject(&drwobj);
}

void LCD_Redraw(void)
{
  DrwPx(&img,0,0);
}

void LCD_Init(void)
{
  zeromem(videoram,2*240*320);
}

void LCD_DeInit(void)
{
  
}
  
void LCD_PutPixel(int x,int y, int r, int g, int b)
{
  if((y<320)&&(x<240)&&(x>=0)&&(y>=0))
  {
    videoram[y*240+x]=RGB16(r,g,b);
  }
}

void LCD_DrawImage(IMGHDR *img,int x,int y)
{
  if(img->bpnum!=8 || x>240-img->w || x<0 || y>320-img->h || y<0) return;
  unsigned short *p = (unsigned short*)videoram+(y*240+x);
  unsigned short *src = (unsigned short*)img->bitmap;
  
  for(int y=0;y<img->h;y++)
  {
    for(int x=0;x<img->w;x++)
    {
      p[y*240+x] = src[y*img->w+x];
    }
    //p+=240;
  }
}


