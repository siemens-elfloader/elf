#define SCREENSIZE ScreenH()*ScreenW()
#define HSIZE YDISP*ScreenW()


DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}


void DrawScreenShot()
{   
  LockSched();
  short *p=malloc((SCREENSIZE-HSIZE)*sizeof(short)), *pp=RamScreenBuffer(); 
  pp+=HSIZE; 
  IMGHDR img={ScreenW(),(ScreenH()-YDISP),8,(char *)p};
  
  for(int i=0;i<SCREENSIZE-HSIZE;i++) 
    *p++=*pp++; 
  void *canvasdata=BuildCanvas();
  DrawCanvas(canvasdata, 0, 0, scrW, scrH, 1 );
  DrwImg(&img, 0, YDISP, GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(2)); 
  mfree(img.bitmap);
  UnlockSched();
}
