#include "c:\arm\inc\swilib.h"
extern char IMG_F[128];
extern char IMG_M_C[128];
extern char IMG_G_C[128];
extern char IMG_L[128];
extern char IMG_X[128];
extern char IMG_O[128];
extern char IMG_T[128];
extern int img_count;
#ifdef NEWSGOLD
#define FONT 11
#define FONT_ATR 32
char IMG_ROOT[128]="4:\\ZBin\\E X-O\\img\\";
char IMG_F[128]="4:\\ZBin\\E X-O\\img\\fon.png";
char IMG_M_C[128]="4:\\ZBin\\E X-O\\img\\menu_cursor.png";
char IMG_G_C[128]="4:\\ZBin\\E X-O\\img\\game_cursor.png";
char IMG_L[128]="4:\\ZBin\\E X-O\\img\\logo.png";
char IMG_X[128]="4:\\ZBin\\E X-O\\img\\x.png";
char IMG_O[128]="4:\\ZBin\\E X-O\\img\\o.png";
char IMG_T[128]="4:\\ZBin\\E X-O\\img\\table.png";
#else
#define FONT 7
#define FONT_ATR 32
char IMG_ROOT[128]="0:\\ZBin\\E X-O\\img\\";
char IMG_F[128]="0:\\ZBin\\E X-O\\img\\fon.png";
char IMG_M_C[128]="0:\\ZBin\\E X-O\\img\\menu_cursor.png";
char IMG_G_C[128]="0:\\ZBin\\E X-O\\img\\game_cursor.png";
char IMG_L[128]="0:\\ZBin\\E X-O\\img\\logo.png";
char IMG_X[128]="0:\\ZBin\\E X-O\\img\\x.png";
char IMG_O[128]="0:\\ZBin\\E X-O\\img\\";
char IMG_T[128]="0:\\ZBin\\E X-O\\img\\table.png";
#endif


volatile int total_img;

IMGHDR *fon;
IMGHDR *menu_cursor;
IMGHDR *game_cursor;
IMGHDR *logo;
IMGHDR *draw_x;
IMGHDR *draw_o;
IMGHDR *table;

extern const char PIC_DIR[128];
const char per_s_s[]="%s%s";
int _done[8]={23,23,23,23,23,23,23,23};
int error_count;
//int done_1=0;
void Load_IMG(int flag)
{
  //FSTATS stat;
  unsigned int ul;
  int f;
  switch(flag)
  {
    case 1:
   // GetFileStats(IMG_O,&stat,&ul);
  sprintf(IMG_O,per_s_s,PIC_DIR,"o.png");
    
  if ((f=fopen(IMG_O,A_ReadOnly,P_READ,&ul))!=-1)
  {
    //if(stat.size>0)
    //{
    fclose(f,&ul);
    _done[1]=1;
    //ShowMSG(1,(int)"Существует");
    //done_1=1;
    draw_o=CreateIMGHDRFromPngFile( IMG_O , 0); 
     //

    }
    else
    {//ShowMSG(1,(int)"не Существует");
     _done[1]=0;error_count++;
      //done_1=0;
    }
    break;
    case 2:
    //GetFileStats(IMG_X,&stat,&ul);
    if ((f=fopen(IMG_X,A_ReadOnly,P_READ,&ul))!=-1)//if(stat.size>0)
    {
    fclose(f,&ul);  
    _done[2]=1;
    draw_x=CreateIMGHDRFromPngFile( IMG_X , 0); 
    //fclose(f,&ul);
    }
    else
    {
    _done[2]=0;error_count++;
    }
    break;
    case 3:
    //GetFileStats(IMG_G_C,&stat,&ul);
    if ((f=fopen(IMG_G_C,A_ReadOnly,P_READ,&ul))!=-1)//if(stat.size>0)
    {
      fclose(f,&ul);
    _done[3]=1;
    game_cursor=CreateIMGHDRFromPngFile( IMG_G_C , 0); 
    //fclose(f,&ul);
    }
    else
    {
     _done[3]=0;error_count++;
    }
    break;
    
    case 4:
      //GetFileStats(IMG_M_C,&stat,&ul);
      if ((f=fopen(IMG_M_C,A_ReadOnly,P_READ,&ul))!=-1)//if(stat.size>0)
    {
      fclose(f,&ul);
    _done[4]=1;
            menu_cursor=CreateIMGHDRFromPngFile( IMG_M_C , 0);
           // fclose(f,&ul);
    }
    else
    {
    _done[4]=0;error_count++;
    }
      
    break;
    case 5: 
     //GetFileStats(IMG_L,&stat,&ul);
       if ((f=fopen(IMG_L,A_ReadOnly,P_READ,&ul))!=-1)//if(stat.size>0)
    {
      fclose(f,&ul);
    _done[5]=1;
    logo=CreateIMGHDRFromPngFile( IMG_L , 0); 
    //fclose(f,&ul);
    }
    else
    {
    _done[5]=0;  error_count++;
    }
    break;
    case 6:
      //GetFileStats(IMG_T,&stat,&ul);
     if ((f=fopen(IMG_T,A_ReadOnly,P_READ,&ul))!=-1)//if(stat.size>0)
    {
      fclose(f,&ul);
    _done[6]=1;  
    table=CreateIMGHDRFromPngFile( IMG_T , 0); 
    //fclose(f,&ul);
    }
    else
    {
    _done[6]=0;  error_count++;
    }
    break;
    case 7:
       ///GetFileStats(IMG_F,&stat,&ul);
     if ((f=fopen(IMG_F,A_ReadOnly,P_READ,&ul))!=-1)//if(stat.size>0)
    {
      fclose(f,&ul);
    _done[7]=1;   
    fon=CreateIMGHDRFromPngFile( IMG_F , 0);
   // fclose(f,&ul);
    }else
    {
      _done[7]=0;  error_count++;
    }
     
    break;
  }
  
   
}


void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}


