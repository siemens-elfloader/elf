#include "SpriteLoader.h"


////////////////////////////////////////////////
extern void DrwImg(IMGHDR *img, int x, int y);//
extern void ifree(IMGHDR *img);/////////////////
extern char *pwd;//////////////
/////////////////
extern void log(char *string);


static int tolower(int toLower)
{
    if ((toLower >= 'A') && (toLower <= 'Z')) return (toLower + 0x20);
    return toLower;
}
static IMGHDR* CreateImgHdrByAnyFile (char * name,short width, short height, int rot,int scale,int origin_size)
{
  WSHDR *path=AllocWS(256);
  str_2ws(path,name,256);
  unsigned int err=0;
  int msz,uid;
  IMGHDR *tmpimg,*myimg=NULL;  
  WSHDR *ext;
  HObj  mypicObj;
  short pos;
  int len;
  if (!path)goto exit0;
  len=wstrlen(path); 
  pos= wstrrchr(path,len,'.');
  if (!pos)goto exit0;

  ext=AllocWS(len-pos);
  wstrcpybypos(ext,path,pos+1,len-pos);
  char e_ext[8];
  ws_2str(ext,e_ext,wstrlen(ext));
  for(int tl=0;tl<strlen(e_ext);tl++)
  {
    e_ext[tl] = tolower(e_ext[tl]);
  }
  str_2ws(ext,e_ext,strlen(e_ext));
  
  uid=GetExtUid_ws(ext);      
  FreeWS(ext);
  
  mypicObj=Obs_CreateObject(uid,0x2d,0x02,0x80A8,1,1,&err);    
    if (err)  return 0;
  err=Obs_SetInput_File(mypicObj,0,path);
  FreeWS(path);
    if (err)  goto exit1;
    
  if (width!=0){ 
    short w=width;  
    short h=height;      
    if(origin_size)
    {
      err=Obs_GetInfo(mypicObj,0);    
      if (err)  goto exit1;  
      err=Obs_GetInputImageSize(mypicObj,&w,&h);    
      if (err)  goto exit1;
    }
    err=Obs_SetOutputImageSize(mypicObj,w,h);
      if (err)  goto exit1;
    if (rot){  
      err= Obs_SetRotation(mypicObj,rot);
        if (err)  goto exit1;
    }
    err=Obs_SetScaling(mypicObj,scale);
      if (err)  goto exit1;
  }
  err=Obs_Start(mypicObj);
    if (err)  goto exit1;
  err=Obs_Output_GetPictstruct(mypicObj,&tmpimg);
  if (err)  {myimg=NULL;goto exit1;}
  msz=CalcBitmapSize (tmpimg->w,tmpimg->h,tmpimg->bpnum);
  myimg=malloc(sizeof(IMGHDR));
  myimg->w=tmpimg->w;
  myimg->h=tmpimg->h;
  myimg->bpnum=tmpimg->bpnum;
  myimg->bitmap=malloc(msz);
  memcpy(myimg->bitmap,tmpimg->bitmap,msz);
exit1:
  Obs_DestroyObject(mypicObj);
exit0:  
  return myimg;
}


static IMGHDR **LoadSprites(char *path,char num_sprites,char horz)
{
  IMGHDR *sprite = CreateImgHdrByAnyFile(path,0,0,0,0,1);
  if(sprite==NULL) return NULL;
  IMGHDR **ret = malloc(sizeof(IMGHDR)*num_sprites);
  
  if(horz) //вертикаль влом делать)
  {
    short width = sprite->w/num_sprites;
    for(int i=0;i<num_sprites;i++)
    {
      ret[i] = malloc(sizeof(IMGHDR));
      ret[i]->w = width;
      ret[i]->h = sprite->h;
      ret[i]->bpnum = 8;
      ret[i]->bitmap = malloc(width*ret[i]->h*2); //only 16bpp!
      short *dest = (short*)ret[i]->bitmap;
      short *src = (short*)sprite->bitmap+width*i;
      for(int y=0;y<sprite->h;y++)
      {
        for(int x=0;x<width;x++)
        {
          dest[y*width+x] = src[y*width*num_sprites+x];
        }
      }
    }
  }
 /* else
  {
    short height = sprite->h/num_sprites;
    for(int i=0;i<num_sprites;i++)
    {
      ret[i] = malloc(sizeof(IMGHDR));
      ret[i]->w = width;
      ret[i]->h = sprite->h;
      ret[i]->bpnum = 8;
      ret[i]->bitmap = malloc(width*ret[i]->h*2); //only 16bpp!
      short *dest = (short*)ret[i]->bitmap;
      short *src = (short*)sprite->bitmap+width*i;
      for(int y=0;y<sprite->h;y++)
      {
        for(int x=0;x<width;x++)
        {
          dest[y*width+x] = src[y*width*num_sprites+x];
        }
      }
    }
  }*/
  
  mfree(sprite);
  return ret;
}

static void NewActiveCopy(TSPRITE *dst,TSPRITE *src,short x,short y)
{
  //sprintf(lgn,"NewActiveCopy(x: %d,y: %d)...",x,y);log(lgn);
  dst->num = src->num;
  dst->img = malloc(sizeof(IMGHDR)*dst->num);
  for(int i=0;i<dst->num;i++)
  {
    dst->img[i] = malloc(sizeof(IMGHDR));
    dst->img[i]->bpnum = src->img[i]->bpnum;
    dst->img[i]->w = src->img[i]->w;
    dst->img[i]->h = src->img[i]->h;
    dst->img[i]->bitmap = malloc(dst->img[i]->w*dst->img[i]->h*2);
    memcpy(dst->img[i]->bitmap,src->img[i]->bitmap,dst->img[i]->w*dst->img[i]->h*2);
  }
  dst->x = x;
  dst->y = y;
  dst->time = src->time;
  dst->active = 1;
  dst->sw = 0;
  dst->counter = 0;
  //log("NewActiveCopy() ok");
}





void DumpSprite(TSPRITE *sprite)
{
  sprintf(lgn,"N: %d",sprite->N);log(lgn);
  sprintf(lgn,"active: %d",sprite->active);log(lgn);
  sprintf(lgn,"x: %d",sprite->x);log(lgn);
  sprintf(lgn,"y: %d",sprite->y);log(lgn);
  sprintf(lgn,"num: %d",sprite->num);log(lgn);
  sprintf(lgn,"time: %d",sprite->time);log(lgn);
  sprintf(lgn,"sw: %d",sprite->sw);log(lgn);
  sprintf(lgn,"counter: %d",sprite->counter);log(lgn);
  sprintf(lgn,"ovr: %d",sprite->ovr);log(lgn);
  
  sprintf(lgn,"isMoving: %d",sprite->isMoving);log(lgn);
  sprintf(lgn,"ex: %d",sprite->ex);log(lgn);
  sprintf(lgn,"ey: %d",sprite->ey);log(lgn);
  sprintf(lgn,"x_incr: %d",sprite->x_incr);log(lgn);
  sprintf(lgn,"y_incr: %d",sprite->y_incr);log(lgn);
  log("\n");
}





TSPRITE *sprites;




static void DrawSprite(TSPRITE *sprite)
{
  
  if(sprite->active)
  {
    //DumpSprite(sprite);
    DrwImg(sprite->img[sprite->sw],sprite->x,sprite->y);
    if(sprite->isMoving)
    {
      //sprintf(lgn,"Draw moving sprite[n:%d, x:%d, y:%d, ix:%d, iy:%d, ex:%d, ey:%d]",sprite->N,sprite->x,sprite->y,sprite->x_incr,sprite->y_incr,sprite->ex,sprite->ey);
      //log(lgn);
      sprite->x+=sprite->x_incr;
      sprite->y+=sprite->y_incr;
      if(sprite->y_incr==0 && sprite->x_incr==0) {StopSprite(sprite->N);return;}
      
      if(sprite->x_incr>0) {if(sprite->x>sprite->ex) {StopSprite(sprite->N);return;}} //движение вправо,достигли конца,киляем спрайт
      else if(sprite->x_incr<0) {if(sprite->x<sprite->ex) {StopSprite(sprite->N);return;}} //движение влево,достигли конца,киляем спрайт
      
      if(sprite->y_incr>0) {if(sprite->y>sprite->ey) {StopSprite(sprite->N);return;}} //движение вниз,достигли конца,киляем спрайт
      else if(sprite->y_incr<0) {if(sprite->y<sprite->ey) {StopSprite(sprite->N);return;}} //движение вверх,достигли конца,киляем спрайт
      //log("draw ok");
    }
    sprite->counter++;
    if(sprite->counter%sprite->time==0)
    {
      if(sprite->sw<sprite->num-1) sprite->sw++;
      else  //прорисовка спрайта закончена
      {
        if(sprite->ovr<=1) //кол-во повторений <=1
        {
          //log("6");
          FreeSprite(&sprites[sprite->N]); //удаляем копию
        }
        else //если есть еще циклы,то повторяем все это дело
        {
          sprite->sw=0;
          sprite->counter=0;
          sprite->ovr--;
        }
      }
    }
  }
}

static short FindFirstEmptyIndex()
{
  for(short i=0;i<MAX_SPRITES;i++) if(sprites[i].active==0) return i;
  return -1;
}


































void LoadSprite(char *name,char num,short time,TSPRITE *sprite)
{
  FSTATS fstats;
  unsigned int err;
  
  char *p = malloc(256);
  sprintf(p,"%s%s",pwd,name);
  if(GetFileStats(p,&fstats,&err)<0) goto exit;
  sprite->num = num;
  sprite->img = LoadSprites(p,num,1);
  sprite->active = 0;
  sprite->time = 2;
  sprite->x = 0;
  sprite->y = 0;
  sprite->sw = 0;
  sprite->counter = 0;
exit:
  mfree(p);
}

void DrawSprites()
{
  for(int i=0;i<MAX_SPRITES;i++)
  {
    DrawSprite(&sprites[i]);
  }
}





short InitSprite(TSPRITE *sprite,short uid,short x,short y,short repeat_num)
{
  
  short n = FindFirstEmptyIndex(); //находим первый пустой слот для спрайта в буфере
  if(n<MAX_SPRITES && n>=0)
  {
    sprites[n].uid = uid;
    sprites[n].N = n; //задаем спрайту его номер :)
    sprites[n].ovr = repeat_num;
    NewActiveCopy(&sprites[n],sprite,x,y); //делаем копию нашего спрайта в общем буфере спрайтов,одновременно присваивая координаты и делая копию активной
    return sprites[n].N;
  }
  return -1;
}


short InitMSprite(TSPRITE *sprite,short uid,short x,short y,signed char x_incr,signed char y_incr,short ex,short ey)
{
  short n = InitSprite(sprite,uid,x,y,10000);
  //sprintf(lgn,"ey: %d",ey);log(lgn);
  if(n<MAX_SPRITES && n>=0)
  {
    sprites[n].ex = ex;
    sprites[n].ey = ey;
    sprites[n].x_incr = x_incr;
    sprites[n].y_incr = y_incr;
    sprites[n].isMoving = 1;
    //sprintf(lgn,"InitMSprite(n: %d,s.ex: %d,s.ey: %d,ex: %d,ey: %d)",n,sprites[n].ex,sprites[n].ey,ex,ey);log(lgn);
  }
  return n;
}









void SetSpriteCoordinaties(short N,short x,short y)
{
  if(N>=0 && N<MAX_SPRITES)
  {
    if(sprites[N].active)
    {
      if(x!=-1) sprites[N].x = x;
      if(y!=-1) sprites[N].y = y;
    }
  }
}

void GetSpriteCoordinaties(short N,short *x,short *y)
{
  if(N>=0 && N<MAX_SPRITES)
  {
    if(sprites[N].active)
    {
      *x = sprites[N].x;
      *y = sprites[N].y;
    }
  }
}


short GetSpriteWidth(short N)
{
  if(N>=0 && N<MAX_SPRITES)
  {
    if(sprites[N].active)
    {
      return sprites[N].img[0]->w;
    }
  }
  return 0;
}

short GetSpriteHeight(short N)
{
  if(N>=0 && N<MAX_SPRITES)
  {
    if(sprites[N].active)
    {
      return sprites[N].img[0]->h;
    }
  }
  return 0;
}



void StopSprite(short N)
{
  if(N>=0 && N<MAX_SPRITES)
  {
    if(sprites[N].active)
    {
      FreeSprite(&sprites[N]);
    }
  }
}



void FreeSprite(TSPRITE *sprite)
{
  for(int i=0;i<sprite->num;i++) ifree(sprite->img[i]);
  mfree(sprite->img);
  sprite->active = 0;
  sprite->ovr = 1;
}



void DeinitSpriteBuffer()
{
  mfree(sprites);
  for(int i=0;i<MAX_SPRITES;i++)
  {
    if(sprites[i].active) FreeSprite(&sprites[i]);
  }
}

void InitSpriteBuffer()
{
  sprites = malloc(sizeof(TSPRITE)*MAX_SPRITES);
  for(int i=0;i<MAX_SPRITES;i++)
  {
    sprites[i].active = 0;
    sprites[i].isMoving = 0;
  }
}




void DumpActiveSprites()
{
  for(int i=0;i<MAX_SPRITES;i++)
  {
    if(sprites[i].active)
    {
      sprintf(lgn,"sprite %d=> N:%d,x:%d,y:%d",i,sprites[i].N,sprites[i].x,sprites[i].y);log(lgn);
    }
  }
}




/////////////////////////////////////////////////////////////////////////////////////////////////////


TSPRITE *GetSprite(short num)
{
  if(num>=0 && num<MAX_SPRITES)
  {
    return (TSPRITE*)&sprites[num];
  }
  else return NULL;
}




