#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "math.h"

const int minus11=-11;
extern void kill_data(void *p, void (*func_p)(void *));

extern const int ENA_LOCK;
extern const int cfgx;
extern const int cfgy;
extern const char pic_path[];
extern const unsigned int pic_size;
extern const unsigned int pic_op;

IMGHDR *my_pic=0;

#define PI 3.1415926535
#define CTYPE1 10
#define CTYPE2 3

typedef struct {
  int x;
  int y;
}POINT;

typedef struct {
  char R;
  char G;
  char B;
  char A;
}color;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

int sqr(int x)
{
  return x*x;
}

int abs(int x)
{
  return x < 0 ? x*(-1) : x;
}

int max(int x, int y)
{
  return x > y ? x : y;
}

int min(int x, int y)
{
  return x < y ? x : y;
}

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

color RGBA(char R, char G, char B, char A)
{
  color t={R,G,B,A};
  return t;
}


color getcolor(IMGHDR *img, int x, int y)
{
  color *bm=(color*)img->bitmap;
  if(x < img->w && x>=0 && y < img->h && y>=0) 
    return *(bm + x + y*img->w);
  else
    return (color){0,0,0,0};
}


void setcolor(IMGHDR *img, int x, int y, color clr)
{
  color *bm=(color*)img->bitmap;
  if(x < img->w && x>=0 && y < img->h && y>=0)
    *(bm + x + y*img->w)=clr;
}

void bmfree(IMGHDR *img)
{
  int x, y;
  for(y=0; y<img->h; y++)
    for(x=0; x<img->w; x++)
      setcolor(img, x, y, (color){0,0,0,0});
}

IMGHDR *createIMGHDR(int w, int h, int type)
{
  IMGHDR *img=malloc(sizeof(IMGHDR));
  img->w=w; 
  img->h=h; 
  img->bpnum=type;
  img->bitmap=malloc(h*w*sizeof(color));
  bmfree(img);
  return img;
}

void deleteIMGHDR(IMGHDR *img)
{
  mfree(img->bitmap);
  mfree(img); 
}


IMGHDR *alpha(IMGHDR *img, char a, int nw, int del)
{
  int i;
  color *r=(color*)img->bitmap;
  for(i=0;i<img->h*img->w; i++, r++)
    if(r->A>a)
      r->A-=a;
    else
      r->A=0;
    return img;
}


IMGHDR *resample(IMGHDR *img, int px, int py, int fast, int del)
{
  if (px==100 && py==100) return img;
  
  long newx = (img->w*px)/100,
  newy = (img->h*py)/100;
  
  float xScale, yScale, fX, fY;
  xScale = (float)img->w  / (float)newx;
  yScale = (float)img->h / (float)newy;
  
  IMGHDR *img2=createIMGHDR(newx,newy, CTYPE1);
  if (fast) {
    for(long y=0; y<newy; y++){
      fY = y * yScale;
      for(long x=0; x<newx; x++){
        fX = x * xScale;
        setcolor(img2,  x,  y, getcolor(img, (long)fX,(long)fY));
      }
    }
  } else {
    long ifX, ifY, ifX1, ifY1, xmax, ymax;
    float ir1, ir2, ig1, ig2, ib1, ib2, ia1, ia2, dx, dy;
    char r,g,b,a;
    color rgb1, rgb2, rgb3, rgb4;
    xmax = img->w-1;
    ymax = img->h-1;
    for(long y=0; y<newy; y++){
      fY = y * yScale;
      ifY = (int)fY;
      ifY1 = min(ymax, ifY+1);
      dy = fY - ifY;
      for(long x=0; x<newx; x++){
        fX = x * xScale;
        ifX = (int)fX;
        ifX1 = min(xmax, ifX+1);
        dx = fX - ifX;
        rgb1= getcolor(img, ifX,ifY);
        rgb2= getcolor(img, ifX1,ifY);
        rgb3= getcolor(img, ifX,ifY1);
        rgb4= getcolor(img, ifX1,ifY1);
        
        ir1 = rgb1.R   * (1 - dy) + rgb3.R   * dy;
        ig1 = rgb1.G * (1 - dy) + rgb3.G * dy;
        ib1 = rgb1.B  * (1 - dy) + rgb3.B  * dy;
        ia1 = rgb1.A  * (1 - dy) + rgb3.A  * dy;
        ir2 = rgb2.R   * (1 - dy) + rgb4.R   * dy;
        ig2 = rgb2.G * (1 - dy) + rgb4.G * dy;
        ib2 = rgb2.B  * (1 - dy) + rgb4.B  * dy;
        ia2 = rgb2.A  * (1 - dy) + rgb4.A  * dy;
        
        r = (char)(ir1 * (1 - dx) + ir2 * dx);
        g = (char)(ig1 * (1 - dx) + ig2 * dx);
        b = (char)(ib1 * (1 - dx) + ib2 * dx);
        a = (char)(ia1 * (1 - dx) + ia2 * dx);
        
        setcolor(img2, x,y,RGBA(r,g,b,a));
      }
    }
  }
  
  if(del)
    deleteIMGHDR(img);
  return img2;
}


POINT canvsize()
{
  POINT sz;
  sz.x=my_pic ? my_pic->w :0 ;
  sz.y=my_pic ? my_pic->h :0 ;
  return sz;
}

void RereadSettings()
{
  InitConfig();
  if(my_pic) deleteIMGHDR(my_pic);
  my_pic=0;
  if(strlen(pic_path))
  {
    FSTATS fstats;
    unsigned int err;     
    if (GetFileStats(pic_path,&fstats,&err)!=-1)
    {
      if(my_pic=CreateIMGHDRFromPngFile(pic_path, CTYPE2)) 
      {                                                    
        my_pic=resample(my_pic, pic_size, pic_size, 0, 1); 
        my_pic=alpha(my_pic, 255-255*pic_op/100, 0, 0);    
      }
    }
    else my_pic=0;
  }
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  CSM_RAM *icsm;
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"Screen Pic config updated!");
      RereadSettings();
    }
  }
  if(ENA_LOCK||IsUnlocked())
  {
    icsm=FindCSMbyID(CSM_root()->idle_id);
    if (icsm)                                                                                                                                                                                                                                                       
    {                                                                                                                                                                                                                                                               
      if (IsGuiOnTop(idlegui_id(icsm)))                                                                                                                                                                                                                          
      {                                                                                                                                                                                                                                                             
        GUI *igui=GetTopGUI();                                                                                                                                                                       
        if (igui)                                                                                                                                                                                                                                                   
        {                                                                                                                                                                                                                                                           
          #ifdef ELKA                                                                                                                                                                                                                                               
          void *canvasdata = BuildCanvas();                                                                                                                                                                                                                         
          {                                                                                                                                                                                                                                                         
          #else                                                                                                                                                                                                                                                     
          void *idata = GetDataOfItemByID(igui, 2);                                                                                                                                                                                                                 
          if (idata)                                                                                                                                                                                                                                                
          {                                                                                                                                                                                                                                                         
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];                                                                                                                                                                                        
          #endif
            POINT sz=canvsize();                                                                    
            DrawCanvas(canvasdata, cfgx, cfgy, cfgx+sz.x, cfgy+sz.y, 1);                                
            if(my_pic)                                                                                  
            {                                                                                           
              DrwImg(my_pic,cfgx,cfgy,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));       
            }                                                                                          
          }                                                                                                                                                                 
        }                                                                                                                                                                                                                                                           
      }
    }
  }                                                                                                                                               
  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
}

static void maincsm_onclose(CSM_RAM *csm)
{
  extern void *ELF_BEGIN;
  if(my_pic) deleteIMGHDR(my_pic);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Screen Pic");
}

int main(void)
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  RereadSettings();
  UpdateCSMname();  
  LockSched();
  
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  
  UnlockSched();  
  return 0;
}

