#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\file.h"
#include "..\inc\buff.h"
#include "..\inc\history.h"
#include "..\inc\conf_loader.h"

typedef struct
{
  void *prev;
  void *next;
  char *path;
}HLIST;

#define HIS_BUF_SIZE (8*1024)
#define MAX_HN 20
HLIST *hltop=0;
char hisbuf[HIS_BUF_SIZE];


HLIST *AllocHList(void)
{
  HLIST *hl=malloc(sizeof(HLIST));
  zeromem(hl, sizeof(HLIST));
  return hl;
}

void DelHList(HLIST *hl)
{
  HLIST *hln;
  HLIST *hlp;
  if(!hl) return;
  hln=hl->next;
  hlp=hl->prev;
  if(hl==hltop)
  {
    hltop=hln;
    if(hln) hln->prev=0;
    if(hl->path) mfree(hl->path);
    mfree(hl);
  }
  else
  {
    if(hlp) hlp->next=hln;
    if(hln) hln->prev=hlp;
    if(hl->path) mfree(hl->path);
    mfree(hl);
  }
}

void FreeHList(void)
{
  HLIST *hl=hltop;
  HLIST *ht;
  hltop=0;
  while(hl)
  {
    ht=hl->next;
    if(hl->path) mfree(hl->path);
    mfree(hl);
    hl=ht;
  }
}

void AddToHList_END(HLIST *hl)
{
  HLIST *ht;
  if(!hl) return;
  if(!hltop)
  {
    hltop=hl;
    return;
  }
  ht=hltop;
  while(ht->next) ht=ht->next;
  ht->next=hl;
  hl->prev=ht;
}

void AddToHList_FIRST(HLIST *hl)
{
  HLIST *ht;
  if(!hl) return;
  if(!hltop)
  {
    hltop=hl;
    return;
  }
  ht=hltop;
  hltop=hl;
  hl->next=ht;
  if(ht) ht->prev=hl;
}


void CutHList(int n)
{
  int i=0;
  HLIST *hl=hltop;
  HLIST *ht;
  if(!n)
  {
    FreeHList();
    return;
  }
  while(hl)
  {
    i++;
    if(i==n) break;
    hl=hl->next;
  }
  if(hl)
  {
    ht=hl->next;
    hl->next=0;
    while(ht)
    {
      hl=ht->next;
      if(ht->path) mfree(ht->path);
      mfree(ht);
      ht=hl;
    }
  }
}

HLIST *GetHListByN(int n)
{
  int i=0;
  HLIST *hl=hltop;
  while(hl)
  {
    if(i==n) return hl;
    i++;
    hl=hl->next;
  }
  return 0;
}

int GetHListN(void)
{
  int i=0;
  HLIST *hl=hltop;
  while(hl)
  {
    i++;
    hl=hl->next;
  }
  return i;
}

HLIST *GetHListByPath(char *path)
{
  HLIST *hl;
  if(!path) return 0;
  hl=hltop;
  while(hl)
  {
    if(!strcmp(hl->path, path)) return hl;
    hl=hl->next;
  }
  return 0;
}

char *GotoRealPos(char *p)
{
  int c;
  while((c=*p))
  {
    if(c>=0x1F) return p;
    p++;
  }
  return 0;
}

char *GotoLineEnd(char *p)
{
  int c;
  if(!(*p)) return 0;
  while((c=*p))
  {
    if(c=='\n' || c=='\r') return p;
    p++;
  }
  return p;
}

char *GotoNextLine(char *p)
{
  int c;
  while((c=*p))
  {
    if(c=='\n' || c=='\r')
    {
      return (GotoRealPos(p));
    }
    p++;
  }
  return 0;
}

int ReadHistory(void)
{
  char hispath[128];
  int len, lx, n=0;
  int fin;
  unsigned int err;
  char *p, *pp, *pt;
  HLIST *hl;
  strcpy(hispath, apppath);
  if(!(len=strlen(hispath))) return 0;
  //GetCPUClock(); //de
  lx=hispath[len-1];
  if(lx!='\\' && lx!='/')
  {
    hispath[len++]='\\';
    hispath[len]=0;
  }
  strcat(hispath, "history.ini");
  if((fin=fopen(hispath, A_BIN+A_ReadOnly, P_READ, &err))!=-1)
  {
    len=fread(fin, hisbuf, HIS_BUF_SIZE, &err);
    hisbuf[len]=0;
    fclose(fin, &err);
    if(len<3) return 0;
    FreeHList();
    if(!maxhis) return 0;
    p=hisbuf;
    if(p[0]==0xEF && p[1]==0xBB && p[2]==0xBF) p+=3;
    if(!GotoRealPos(p)) return 0;
    do
    {
      //is path
      if(p[0]<'0' || p[0]>'4' || p[1]!=':' || (p[2]!='\\' && p[2]!='/'))
      {
	if(!(p=GotoNextLine(p))) break;
	continue;
      }
      if(!(pp=GotoLineEnd(p))) break;
      pt=malloc(128);
      zeromem(pt, 128);
      strncpy(pt, p, pp-p);
      hl=AllocHList();
      hl->path=pt;
      AddToHList_END(hl);
      n++;
      if(!(p=GotoNextLine(p))) break;
    }while(1);
  }
  if(n>maxhis)
  {
    CutHList(maxhis);
    n=maxhis;
  }
  return n;
}

int SaveHistory(void)
{
  char hispath[128];
  char buf[256];
  int len, lx, n=0;
  int fin;
  unsigned int err;
  HLIST *hl=hltop;
  //GetCPUClock(); //de
  strcpy(hispath, apppath);
  if(!(len=strlen(hispath))) return 0;
  lx=hispath[len-1];
  if(lx!='\\' && lx!='/')
  {
    hispath[len++]='\\';
    hispath[len]=0;
  }
  strcat(hispath, "history.ini");
  if((fin=fopen(hispath, A_BIN+A_WriteOnly+A_Create+A_Truncate, P_WRITE, &err))!=-1)
  {
    //utf8
    buf[0]=0xEF;
    buf[1]=0xBB;
    buf[2]=0xBF;
    if(fwrite(fin, buf, 3, &err)!=3)
    {
      fclose(fin, &err);
      return 0;
    }
    while(hl)
    {
      if(hl->path && (len=strlen(hl->path)))
      {
	strcpy(buf, hl->path);
	buf[len++]='\n';
	buf[len]=0;
	n++;
	if(fwrite(fin, buf, len, &err)!=len) break;
      }
      hl=hl->next;
    }
    fclose(fin, &err);
  }
  return n;
}

void AddPathToHList(char *path)
{
  HLIST *hl;
  char *pt;
  if(!path || !maxhis) return;
  if(hltop && hltop->path && !strcmp(path, hltop->path)) //is top
    return;
  //GetCPUClock(); //de
  if((hl=GetHListByPath(path))) DelHList(hl);
  CutHList(maxhis-1);
  hl=AllocHList();
  pt=malloc(128);
  zeromem(pt, 128);
  strcpy(pt, path);
  hl->path=pt;
  AddToHList_FIRST(hl);
}

void SetProcfile(void)
{
  HLIST *hl=hltop;
  //GetCPUClock(); //de
  zeromem(procfile, 128);
  if(!hl || !hl->path) return;
  strcpy(procfile, hl->path);
}

unsigned int CreateSLMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer)
{
  void *ma=malloc_adr();
  void *gui=GetMenuGUI(ma, mfree_adr());
  SetMenuToGUI(gui, menu);
  SetMenuItemCount(gui, n_items);
  MenuSetUserPointer(gui, user_pointer);
  SetCursorToMenuItem(gui, start_item);
  SetHeaderToMenu(gui, hdr, ma);
  return (CreateGUI(gui));
}

HEADER_DESC his_menuhdr={0,0,0,0,NULL,(int)"历史",LGP_NULL};

const int his_menusoftkeys[]={0,1,2};

const SOFTKEY_DESC his_menu_sk[]=
{
  {0x0018,0x0000,(int)"选择"},
  {0x0001,0x0000,(int)"返回"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB his_menu_skt=
{
  his_menu_sk,0
};

int his_menu_onkey(void *data, GUI_MSG *msg)
{
  HLIST *hl;
  int n;
  if(msg->keys==0x1) return 1;
  //GetCPUClock();
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    n=GetCurMenuItem(data);
  DO_N:
    if(!(hl=GetHListByN(n))) return 0;
    if(!hl->path) return 1;
    if(!strcmp(procfile, hl->path)) return 1;
    if(openFile(hl->path))
    {
      strcpy(procfile, hl->path);
      updateCSMname();
      initBuffer();
      getStartOffset();
      setReadPostion();
      DelHList(hl);
      AddPathToHList(procfile);
    }
    else DelHList(hl);
    return 1;
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    n=msg->gbsmsg->submess;
    if(n>='1' && n<='9')
    {
      n-='1';
      goto DO_N;
    }
    if(n=='#')
    {
      int k;
      n=GetCurMenuItem(data);
      if((hl=GetHListByN(n))) DelHList(hl);
      k=GetHListN();
      if(n>=(k-1)) SetCursorToMenuItem(data, (k>1)?1:0);
      Menu_SetItemCountDyn(data, k);
      RefreshGUI();
      return -1;
    }
  }
  return 0;
}

void his_menu_ghook(void *gui, int cmd)
{
}

void his_menu_itemhndl(void *data, int curitem, void *user_pointer)
{
  HLIST *hl;
  char *p;
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  if((hl=GetHListByN(curitem)) && hl->path && strlen(hl->path))
  {
    p=GetFileName(hl->path);
    str_2ws(ws, p, 149);
  }
  else wsprintf(ws, "error!");
  SetMenuItemText(data, item, ws, curitem);
}

const MENU_DESC his_menu=
{
  8,his_menu_onkey,his_menu_ghook,NULL,
  his_menusoftkeys,
  &his_menu_skt,
  0x10,//Right align
  his_menu_itemhndl,
  0,//menuitems,
  0,//menuprocs,
  0
};

int CreateHistoryMenu(void)
{
  int z=GetHListN();
  patch_header(&his_menuhdr);
  return (CreateSLMenu(&his_menu, &his_menuhdr, (z>1)?1:0, z, 0));
}


