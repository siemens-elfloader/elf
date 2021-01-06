
#include "pngext.h"

#define DEFAULT_FOLDER "0:\\Zbin\\img\\"
#define CACHE_PNG 50


#ifdef CX70 
#define OLD_CSM_SIZE 0xC4
#endif

#ifdef SL65
#define OLD_CSM_SIZE 0xEC
#endif

#ifdef M75 
#define OLD_CSM_SIZE 0xCC
#endif

#ifdef NEWSGOLD 
#define OLD_CSM_SIZE 0x118
#endif

typedef struct
{
  void *next;
  char *pngname;
  IMGHDR * img;
}PNGLIST;


typedef struct
{
  CSM_RAM csm;
  char dummy[OLD_CSM_SIZE-sizeof(CSM_RAM)];
  PNGLIST * PNGTop;
}IDLECSM;

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}


int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int is_file_exist(const char* fname)
{
  unsigned int err;
  FSTATS fs;
  return (GetFileStats(fname,&fs,&err));
}

PNGLIST*getpltop(void)
{
  IDLECSM *icsm;
  if (!(icsm=(IDLECSM *)FindCSMbyID(CSM_root()->idle_id))) return 0;
  PNGLIST *pltop=icsm->PNGTop;
  return (pltop);
}

void setpltop(PNGLIST*pltop)
{
  IDLECSM *icsm=(IDLECSM *)FindCSMbyID(CSM_root()->idle_id);
  icsm->PNGTop=pltop;
}
     
                 
void free_png_list(PNGLIST *pl)
{
  mfree(pl->img->bitmap);
  mfree(pl->img);
  mfree(pl->pngname);
  mfree(pl);
}

PNGLIST* find_pic_by_n(int n)
{
  PNGLIST *pl=getpltop();
  int i=0;
  while(i!=n)
  {
    pl=pl->next;
    i++;
  }
  return (pl);
}

int get_number_of_png(PNGLIST *pltop)
{
  PNGLIST *pl=pltop;
  int i=0;
  while (pl&&i<CACHE_PNG)
  {
    pl=pl->next;
    i++;
  }
  return (i); 
}

void add_to_first(const char* fname,IMGHDR* img)   // »спользуетс€ дл€ добавлени€ в начало списка новых пнг, с перемещением старых
{
  PNGLIST *pl_top=getpltop();
  PNGLIST* cur;
  int n;
  n=get_number_of_png(pl_top);
  if ((n+1)==CACHE_PNG)                 // дл€ одной не хватит
  {
    free_png_list(find_pic_by_n(n));
    n--;
    
  }
  cur=malloc(sizeof(PNGLIST));
  cur->pngname=malloc(strlen(fname)+1);
  strcpy(cur->pngname,fname);
  cur->img=img;
  cur->next=pl_top;
  setpltop(cur);
}

// »спользуетс€ дл€ перемещени€ в начало списка старых пнг, с перемещением
// при перемещении нет мороки с вытеснением, так что тут все просто..
void move_to_first(int i)                   
{
  if (!i)  return;
  PNGLIST *pl_top=getpltop();
  PNGLIST *pl_prev=find_pic_by_n(i-1);
  PNGLIST *pl_cur=find_pic_by_n(i);
  pl_prev->next=pl_cur->next;
  pl_cur->next=pl_top;
  setpltop(pl_cur);
}



// »щем пнг в кеше
int find_png_in_cache(const char* fname)
{
  PNGLIST *pl=getpltop();
  int i=0;
  while(pl&&i<CACHE_PNG)
  {
    if (!strcmp_nocase(pl->pngname,fname))
      return i;
    else
    {
      pl=pl->next;
      i++;
    }
  }
  return -1;
}

// ѕытаемс€ создать новую картинку
IMGHDR * try_to_create(const char* fname)
{
  IMGHDR * img;
  if (is_file_exist(fname)==-1) return (0);
  if (!(img=create_imghdr(fname))) return (0);
  return (img);
}



void MyIDLECSMonCreate(IDLECSM *icsm)
{
  icsm->PNGTop=0;
  BX_R1(icsm,OldOnCreate);
  
}

void MyIDLECSMonClose(IDLECSM *icsm)
{
  BX_R1(icsm,OldOnClose);
}

IMGHDR* PatchGetPIT(unsigned int pic)
{
  int i;
  IMGHDR * img;
  int idle_id=CSM_root()->idle_id;
  if (!idle_id) return 0;
  if (!(IDLECSM *)FindCSMbyID(idle_id)) return 0;
  char fname[256];
  if ((pic>>28)==0xA)
  {
    strcpy(fname,(char*)pic);
  }
  else
  {
    sprintf(fname,DEFAULT_FOLDER"%u.png",pic);
  } 
  if ((i=find_png_in_cache(fname))==-1)
  {
    if (!(img=try_to_create(fname))) return 0;
    add_to_first(fname,img);
  }
  else
  {
    move_to_first(i);
  }
  return (getpltop()->img);   
}

//ѕатчи
#pragma diag_suppress=Pe177
__root static const int NEW_ONCREATE @ "PATCH_ONCREATE" = (int)MyIDLECSMonCreate;

__root static const int NEW_ONCLOSE @ "PATCH_ONCLOSE" = (int)MyIDLECSMonClose;

__root static const int NEW_CSMSIZE @ "PATCH_CSMSIZE" = sizeof(IDLECSM);
#pragma diag_default=Pe177


