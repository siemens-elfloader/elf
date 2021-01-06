#include "../include.h"

#include "image.h"
#include "../internet/utils.h"




class image
{
private:
IMGHDR *img;
public:
image();
~image();


image(char *filename)
{
img=CreateIMGHDRFromPngFile(filename,2);
}
~image()
{

}

void DrwImg(int x,int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}



};





















void DrwImg(IMGHDR *img, int x, int y)
{
    image *i=new image("s.png");
    i->DrwImg(1,3);
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}

void FreeImg(IMGHDR *img)
{
  if(img && img->bitmap)
  {
    mfree(img->bitmap);
    img->bitmap=NULL;
  }
  if(img)
  {
    mfree(img);
    img=NULL;
  }
}

void IMGHDR_cpy(IMGHDR *dest, IMGHDR *src)
{
if(!src->bitmap)return;
dest->w = src->w;
dest->h = src->h;
dest->bpnum = src->bpnum;
if(dest->bitmap)dest->bitmap=(unsigned char*)realloc((unsigned char*)dest->bitmap,src->w*src->h*2+1);
else dest->bitmap=(unsigned char*)malloc(src->w*src->h*2);
memcpy(dest->bitmap, src->bitmap, src->w*src->h*2);
}

/*

IMGHDR *IMGHDR_join(IMGHDR *img1,IMGHDR *img2,int mode)
{
  char *buf=0;
  switch(mode)
  {
  case BOTTOM:
  img1->bitmap=realloc(img1->bitmap,img1->w*img1->h*2+img2->w*img2->h*2);
  memcpy(img1->bitmap+img1->w*img1->h*2,img2->bitmap,img2->w*img2->h*2);
  img1->h=img1->h+img2->h;
  break;
  case RIGHT:
  buf=malloc(img1->w*img1->h*2+img2->w*img2->h*2);

   for (int i = 0; i<img1->h; i++)
{
 memcpy(buf+i*img1->w*4,img1->bitmap+i*img1->w*2,img1->w*2);
 memcpy(buf+i*img1->w*4+img1->w*2,img2->bitmap+i*img1->w*2,img1->w*2);
}

mfree(img1->bitmap);
img1->bitmap = buf;
img1->w=img1->w+img2->w;
break;
  }
  return img1;
}



//DrwImg(map[i][j],i*cub,j*cub);

  for(int j=0;j<MAP_Y;j++)
  for(int i=0;i<MAP_X;i++)
  {
  sprintf(filename,"%scache%f_%f\\map_%d_%d_%d_%d.png",fname,Lon,Lat,i,j,zoom,map_type);
  if(GetFileStats(filename,&fs,0)==-1)sprintf(filename,"%simg\\not.png",fname);
  map[i][j]=CreateIMGHDRFromPngFile(filename,2);
  }


void ImgJoin()
{
      for(int i=0;i<MAP_X;i++)
     {
       for(int j=0;j<MAP_Y;j++)
      {
        map[i][j]
      }
     }


}*/

IMGHDR *CreateIMGHDRFromPng(char *file)
{
  sprintf(filename,"%s%s",elf_path,resource[NO_TILE]);
  if(is_file_exists(file))
  return CreateIMGHDRFromPngFile(file,2);
  else return CreateIMGHDRFromPngFile(filename,2);
}
