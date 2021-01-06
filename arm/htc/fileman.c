#include "swilib.h"
extern char *loadfile(char *filename);
extern char *txtfile;
extern void ascii2ws(WSHDR *ws, const char *s);
extern IMGHDR *SetIco[50];
extern DrwPngImg(IMGHDR *img, int x, int y);
	const char co136m[4]={240,240,240,255};
	const char co23zm[4]={215,215,215,50};
	const char co23xm[4]={235,235,235,30};

char _percent_t[]="%t";
char header[128];
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
	inp->rc.x=0;
	inp->rc.y=HeaderH()+1+YDISP;
	inp->rc.x2=ScreenW()-1;
	inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}
//====================================================================================================================================

//====================================================================================================================================

int size;
volatile FLIST *fltop;
volatile FLIST *fltop2;

void Free_FLIST(int numberx)
{
  LockSched();
  FLIST *fl;
  if(numberx==0) fl=(FLIST *)fltop;
  if(numberx==1) fl=(FLIST *)fltop2;

  if(numberx==0) fltop=0; if(numberx==1) fltop2=0;
  UnlockSched();
  while(fl)
  {
    FLIST *fl_prev;
    fl_prev=fl;
    fl=fl->next;
    mfree(fl_prev->fullname);
    mfree(fl_prev->name);
    mfree(fl_prev);
  }
}


#define IS_FOLDER 1
#define IS_FILE 0

const char back[]="..";
/*
int GetFListN()
{
  int i=0;
  FLIST *fl=(FLIST*)&fltop;
  while((fl=fl->next)) i++;
  return (i);
}
int GetFListN2()
{
  int i=0;
  FLIST *fl=(FLIST*)&fltop2;
  while((fl=fl->next)) i++;
  return (i);
}
*/

int GetFoldersLevel(char *name)
{
  int i=0;
  char *s=name;
  while(*s++)
  {
    if (*s=='\\' &&*(s+1)!=0) i++;
  }
  return (i);
}

int strcmp_nocase3(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

FLIST *AddToFList(const char* full_name, const char *name, int is_folder)
{
  FLIST *fl;
  FLIST *pr;
  FLIST *fn=malloc(sizeof(FLIST));
  fn->fullname=malloc(strlen(full_name)+1);
  strcpy(fn->fullname,full_name);

  fn->name=malloc(strlen(name)+1);
  strcpy(fn->name,name);

  fn->is_folder=is_folder;
  fn->next=0;
  fl=(FLIST *)fltop;
  if (fl)
  {
    pr=(FLIST *)&fltop;
    while(strcmp_nocase3(fl->name,fn->name)<0)
    {
      pr=fl;
      fl=fl->next;
      if (!fl) break;
    }
    fn->next=fl;
    pr->next=fn;
  }
  else
  {
    fltop=fn;
  }
  return (fn);
}

FLIST *AddToFList2(const char* full_name, const char *name, int is_folder)
{
  FLIST *fl;
  FLIST *pr;
  FLIST *fn=malloc(sizeof(FLIST));
  fn->fullname=malloc(strlen(full_name)+1);
  strcpy(fn->fullname,full_name);

  fn->name=malloc(strlen(name)+1);
  strcpy(fn->name,name);

  fn->is_folder=is_folder;
  fn->next=0;
  fl=(FLIST *)fltop2;
  if (fl)
  {
    pr=(FLIST *)&fltop2;
    while(strcmp_nocase3(fl->name,fn->name)<0)
    {
      pr=fl;
      fl=fl->next;
      if (!fl) break;
    }
    fn->next=fl;
    pr->next=fn;
  }
  else
  {
    fltop2=fn;
  }
  return (fn);
}


void FindFiles(char *str, int type, int numberx)  // type == 0 SelectFolder, type == 1 SelectFile
{
  DIR_ENTRY de;
  unsigned int err;
  int i, c;
  char name[256];
  char fname[128];

  Free_FLIST(numberx);
  strcpy(name,str);
  strcat(name,"*");

  i=GetFoldersLevel(str);
  if (i==0)
  {
    if(numberx==0) AddToFList("ROOT",back,IS_FOLDER);
	if(numberx==1) AddToFList2("ROOT",back,IS_FOLDER);
  }
  else
  {
    char *s=str;
    char *d=fname;
    for (int k=0; k!=i && *s; )
    {
      c=*s++;
      *d++=c;
      if (c=='\\')  k++;
    }
    *d=0;
    if(numberx==0) AddToFList(fname,back,IS_FOLDER);
    if(numberx==1) AddToFList2(fname,back,IS_FOLDER);
  }

  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(name,de.folder_name);
      strcat(name,"\\");
      strcat(name,de.file_name);
      if (de.file_attr&FA_DIRECTORY)
      {
        strcpy(fname,"\\");
        strcat(fname,de.file_name);
        strcat(name,"\\");
       if(numberx==0)  AddToFList(name,fname,IS_FOLDER);
       if(numberx==1)  AddToFList2(name,fname,IS_FOLDER);
      }
      else
      {
        if (type!=0)
        {
          if(numberx==0)  AddToFList(name,de.file_name,IS_FILE);
          if(numberx==1)  AddToFList2(name,de.file_name,IS_FILE);
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}




/*
FLIST *FindFLISTtByNS(int *i, int si)
{
  FLIST *fl;
  fl=(FLIST *)fltop;
  while(fl)
  {
    if (fl->is_folder==si)
    {
      if (!(*i)) return (fl);
      (*i)--;
    }
    fl=fl->next;
  }
  return fl;
}

FLIST *FindFLISTtByN(int n)
{
  FLIST *fl;
  fl=FindFLISTtByNS(&n,IS_FOLDER); if ((!n)&&(fl)) return(fl);
  fl=FindFLISTtByNS(&n,IS_FILE); if ((!n)&&(fl)) return(fl);
  return fl;
}
int start(char name[128]){return 1;};
*/

int Play6(int sm0, int numberx)
{
	LockSched();
	 WSHDR * ws = AllocWS( 26 );
	FLIST *fl0;


	if(numberx==0)fl0=(FLIST*)fltop;
	if(numberx==1)fl0=(FLIST*)fltop2;



	int fmf = 0;
	for (int i=0; i<sm0; i++) if(fl0) fl0=(FLIST*)(fl0->next);
	UnlockSched();
if(fl0){
     if(fl0->name) ascii2ws(ws, fl0->name);                DrawString( ws, 42,  62,  234, 76, 9, 1, co136m, GetPaletteAdrByColorIndex( 23 ) );
     if(fl0->fullname) ascii2ws(ws, fl0->fullname);        DrawString( ws, 42,  76,  234, 90, 8, 1, co23zm, GetPaletteAdrByColorIndex( 23 ) );
	// number_call[0]=fl0->fullname;
     DrwPngImg(SetIco[18], 8, 60);
     DrawLine(0,95,239,95,1,co23xm);
     fl0=(FLIST*)(fl0->next);
	 fmf++;
}
if(fl0){
     if(fl0->name) ascii2ws(ws, fl0->name);                DrawString( ws, 42,  99,   234, 113, 9, 1, co136m, GetPaletteAdrByColorIndex( 23 ) );
     if(fl0->fullname) ascii2ws(ws, fl0->fullname);        DrawString( ws, 42,  113,  234, 127, 8, 1, co23zm, GetPaletteAdrByColorIndex( 23 ) );
	// number_call[1]=fl0->fullname;
     DrwPngImg(SetIco[18], 8, 97);
     DrawLine(0,132,239,132,1,co23xm);
     fl0=(FLIST*)(fl0->next);
	 fmf++;
}
if(fl0){
     if(fl0->name) ascii2ws(ws, fl0->name);                DrawString( ws, 42,  136,  234, 150, 9, 1, co136m, GetPaletteAdrByColorIndex( 23 ) );
     if(fl0->fullname) ascii2ws(ws, fl0->fullname);        DrawString( ws, 42,  150,  234, 164, 8, 1, co23zm, GetPaletteAdrByColorIndex( 23 ) );
	// number_call[2]=fl0->fullname;
     DrwPngImg(SetIco[18], 8, 134);
     DrawLine(0,169,239,169,1,co23xm);
     fl0=(FLIST*)(fl0->next);
	 fmf++;
}
if(fl0){
     if(fl0->name) ascii2ws(ws, fl0->name);                DrawString( ws, 42,  173,  234, 187, 9, 1, co136m, GetPaletteAdrByColorIndex( 23 ) );
     if(fl0->fullname) ascii2ws(ws, fl0->fullname);        DrawString( ws, 42,  187,  234, 201, 8, 1, co23zm, GetPaletteAdrByColorIndex( 23 ) );
	// number_call[3]=fl0->fullname;
     DrwPngImg(SetIco[18], 8, 171);
     DrawLine(0,206,239,206,1,co23xm);
	 fl0=(FLIST*)(fl0->next);
	 fmf++;
}
if(fl0){

     if(fl0->name) ascii2ws(ws, fl0->name);                DrawString( ws, 42,  210,  234, 224, 9, 1, co136m, GetPaletteAdrByColorIndex( 23 ) );
     if(fl0->fullname) ascii2ws(ws, fl0->fullname);        DrawString( ws, 42,  224,  234, 238, 8, 1, co23zm, GetPaletteAdrByColorIndex( 23 ) );
	// number_call[4]=fl0->fullname;
     DrwPngImg(SetIco[18], 8, 208);
  	 fl0=(FLIST*)(fl0->next);
	 fmf++;
}
if(fl0){
	 fmf++;
}
// DrawString( ws, 50,  50,  230, 240, 9, 1, co126, GetPaletteAdrByColorIndex( 23 ) );
FreeWS(ws);
	return fmf;
}

/*
void CreateRootMenu(int numberx)
{
  Free_FLIST(numberx);
  AddToFList("0:\\","0:\\",IS_FOLDER);
  AddToFList("1:\\","1:\\",IS_FOLDER);
  AddToFList("2:\\","2:\\",IS_FOLDER);
  AddToFList("4:\\","4:\\",IS_FOLDER);
  strcpy(header,"Root");
}
*/

