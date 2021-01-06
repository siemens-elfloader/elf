#include "c:\arm\inc\swilib.h"
#include "externs.h"

extern int img_count;
extern const char PICTURES_PATH[128];
static char IMG[128];
IMGHDR *images[7];//={draw_o,draw_x,game_cursor,menu_cursor,logo,table,fon}
const char per_s_s[]="%s%s";

int _done[8]={23,23,23,23,23,23,23,23};
int error_count;

static int IsFile(char *file)
{
  FSTATS fs;
  if (GetFileStats(file,&fs,0)!=-1)
  return 1;
  return 0;
}
void Load_IMG(int flag)
{
  switch(flag)
  {
    case 1:
  sprintf(IMG,per_s_s,PICTURES_PATH,"o.png");    
  if (IsFile(IMG))
  {
    _done[1]=1;
    images[flag-1]=CreateIMGHDRFromPngFile( IMG , 0); 
    }
    else
    {
     _done[1]=0;error_count++;
    }
    break;
    case 2:
    sprintf(IMG,per_s_s,PICTURES_PATH,"x.png");   
    if (IsFile(IMG))
    {
    _done[2]=1;
    images[flag-1]=CreateIMGHDRFromPngFile( IMG , 0); 
    }
    else
    {
    _done[2]=0;error_count++;
    }
    break;
    case 3:
    //GetFileStats(IMG_G_C,&stat,&ul);
    sprintf(IMG,per_s_s,PICTURES_PATH,"game_cursor.png");     
    if (IsFile(IMG))
    {
    _done[3]=1;
    images[flag-1]=CreateIMGHDRFromPngFile( IMG , 0); 
    }
    else
    {
     _done[3]=0;error_count++;
    }
    break;
    
    case 4:
      sprintf(IMG,per_s_s,PICTURES_PATH,"menu_cursor.png");
      X_MENU_CURSOR = ScreenW()/2 - GetImgWidth((int)IMG)/2;
      if (IsFile(IMG))
    {
    
    _done[4]=1;
     images[flag-1]=CreateIMGHDRFromPngFile( IMG , 0); 
    }
    else
    {
    _done[4]=0;error_count++;
    }
      
    break;
    case 5: 
      sprintf(IMG,per_s_s,PICTURES_PATH,"logo.png");
      X_LOGO = ScreenW()/2 - GetImgWidth((int)IMG)/2;
      Y_LOGO = (ScreenH()-YDISP)/2 - GetImgHeight((int)IMG)/2;
      
       if (IsFile(IMG))
    {
    
    _done[5]=1;
    images[flag-1]=CreateIMGHDRFromPngFile( IMG , 0); 
    }
    else
    {
    _done[5]=0;  error_count++;
    }
    break;
    case 6:
    sprintf(IMG,per_s_s,PICTURES_PATH,"table.png");
     if (IsFile(IMG))
    {
    _done[6]=1;  
    images[flag-1]=CreateIMGHDRFromPngFile( IMG , 0); 
    }
    else
    {
    _done[6]=0;  error_count++;
    }
    break;
    case 7:
     sprintf(IMG,per_s_s,PICTURES_PATH,"fon.png"); 
     if (IsFile(IMG))
    {
    
    _done[7]=1;   
    images[flag-1]=CreateIMGHDRFromPngFile( IMG , 0); 
    }else
    {
      _done[7]=0;  error_count++;
    }
     
    break;
  }
  
   
}
	  
void DrwImg(IMGHDR *img, int x, int y)
{
  LockSched();
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,0,0);
  DrawObject(&drwobj);
  UnlockSched();
}
