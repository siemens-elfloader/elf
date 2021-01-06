#include "swilib.h"

#define SCREENSIZE ScreenH()*ScreenW()
#define HSIZE YDISP*ScreenW()
   





  
extern int drawimg2img(IMGHDR * onse, IMGHDR * timage2, int x, int y, int xRect, int yRect,int xxRect, int yyRect);

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}


//IMGHDR *out1;


void DrawScreenShot()
{   
  LockSched();
  short *p=(short*)malloc((SCREENSIZE-HSIZE)*sizeof(short)), *pp=(short*)RamScreenBuffer(); 
  pp+=HSIZE; 
  IMGHDR img={ScreenW(),(ScreenH()-YDISP),8,(char *)p};
  
  for(int i=0;i<SCREENSIZE-HSIZE;i++) 
    *p++=*pp++; 

  DrwImg(&img, 0, YDISP, GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2)); 
  mfree(img.bitmap);
  UnlockSched();
}


