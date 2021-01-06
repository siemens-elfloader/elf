#include "../inc/swilib.h"
#include "../inc/pnglist.h"
#include "conf_loader.h"
#include "code.h"
//===============================================================================================
// ELKA Compatibility
#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

#define wslen(ws) ws->wsbody[0]
//===============================================================================================

volatile int main_menu_id;
extern void kill_data(void *p, void (*func_p)(void *));
char g_fname[32];
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strncmp_nocase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}


//types:
//1 - menu;
//2 - edit;
typedef struct
{
  void *next;
  int type;
  char file[32];
  char name[64];
}MMENU;

typedef struct
{
  DYNPNGICONLIST dpl;
  char *fname;
  int uni_n;
}DYNPNGILIST_MY;

char m_header[32];

int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


void ed1_locret(void){}
int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  return (0);
}

void ed1_ghook(GUI *data, int cmd)
{
  DYNPNGILIST_MY *t=EDIT_GetUserPointer(data);
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==3)
  {
    while (t)
    {
      DYNPNGILIST_MY *d;
      d=t;
      t=t->dpl.next;
      mfree(d->dpl.img->bitmap);
      mfree(d->dpl.img);
      mfree(d->fname);
      mfree(d);
    }    
  }
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    pltop->dyn_pltop=(DYNPNGICONLIST *)t;
    DisableIDLETMR();
  }
}

char ed_header[128];
HEADER_DESC ed1_hdr={0,0,0,0,NULL,(int)ed_header,LGP_NULL};


INPUTDIA_DESC ed1_desc =
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правом?краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверс? знакомес?  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слов?  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поме?ть местам?софт-кнопки
  0x40000000 | 0x2
};



int AddPicIfNotExist(DYNPNGILIST_MY **top, char *fname)
{
  DYNPNGILIST_MY *t, *p;
  IMGHDR *img;
  int n=0;
  t=(DYNPNGILIST_MY *)top;
  while((p=t->dpl.next))
  {
    t=p;
    if (!strcmp_nocase(t->fname, fname)) return t->uni_n;
    n++;
  }
  // Не нашл??кэше, пробуе?добавить
  img=CreateIMGHDRFromPngFile(fname,0);
  if (!img) return (-1);
  // Получилось создат?картинку
  n+=FIRST_UCS2_BITMAP;
  t=t->dpl.next=malloc(sizeof(DYNPNGILIST_MY));
  t->uni_n=n;
  t->dpl.next=0;
  t->dpl.icon=GetPicNByUnicodeSymbol(n);
  t->dpl.img=img;
  t->fname=malloc(strlen(fname)+1);
  strcpy(t->fname,fname);
  return (n);
}


int create_ed(char *l_fname)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  char fname[128];
  int f;
  unsigned int err;
  char *buf, *s, *d;
  unsigned int fsize;
  unsigned int c,c2;
  int pic_n;
  DYNPNGILIST_MY *top=0;
  WSHDR *ews=AllocWS(512);

  strcpy(fname, g_fname);
  strcat(fname, l_fname);
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return (0);
  fsize=lseek(f,0,S_END,&err,&err);
  if (fsize<=0)
  {
    fclose(f,&err);
    return (0);
  }
  lseek(f,0,S_SET,&err,&err);
  buf=malloc(fsize+1);
  fread(f,buf,fsize,&err);
  buf[fsize]=0;
  fclose(f,&err);
  s=buf;
   
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  if (*s=='t')
  {
    if(*(s+1)=='~')
    {
      int i=0;
      s+=2;
      d=ed_header;
      while((c=*s++)!='&' && i<(sizeof(ed_header)-1))
      {
        *d++=c;
        i++;
      }
      *d=0;
    }
  }
  while(*s=='\r' || *s=='\n') s++;
  while ((c=*s++))
  {
    if (*s++!='~')  break;
    switch(c)
    {
    case 'p':
      strcpy(fname,g_fname);
      d=strrchr(fname,'\\');
      while((c=*s++)!='&')
      {
        *d++=(c=='/')?'\\':c;
      }
      *d=0;
      pic_n=AddPicIfNotExist(&top,fname);
      if (pic_n!=-1)
      {
        CutWSTR(ews,0);
        wsAppendChar(ews,pic_n);
        ConstructEditControl(&ec,3,0x40,ews,wslen(ews));
        AddEditControlToEditQend(eq,&ec,ma);
      }
      break;
        
    case 't':
      CutWSTR(ews,0);
      while((c=*s++)!='&')
      {
      extern unsigned short *codemap;
      if(codemap == 0)
      {
      wsprintf(ews, "%t", s);
      } 
        
      if(c <= 128)
      wsAppendChar(ews,c);
      else
      {
      c2=*s++;
      if(c2 < 128)
        wsAppendChar(ews, c2);
      else
        wsAppendChar(ews, codemap[(c-129)*127+(c2-128)]);
      }
      }
      ConstructEditControl(&ec,4,0x40,ews,wslen(ews));
      AddEditControlToEditQend(eq,&ec,ma);
      break;
    }
    while(*s=='&' || *s=='\r' || *s=='\n') s++;
  }
  
  FreeWS(ews);
  mfree(buf);

  patch_header(&ed1_hdr);
  patch_input(&ed1_desc);
  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,top);
}


MMENU *ParseMenuFile(char *file)
{
  MMENU *top=0;
  MMENU *bot=(MMENU *)(&top);
  int f;
  char name[256];
  char *buf, *s, *d;
  int c;
  int fsize;
  int i;
  unsigned int err;
  strcpy(name,g_fname);
  strcat(name,file);
  if ((f=fopen(name,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
  fsize=lseek(f,0,S_END,&err,&err);
  if (fsize<=0)
  {
    fclose(f,&err);
    return (0);
  }
  lseek(f,0,S_SET,&err,&err);
  buf=malloc(fsize+1);
  fread(f,buf,fsize,&err);
  buf[fsize]=0;
  fclose(f,&err);
  s=buf;
  while((c=*s))
  {
    s++;
    switch(c)
    {
    case '\r':
    case '\n':
      break;
      
    case 'H':
      d=m_header;
      i=0;
      LockSched();
      while(*s!='\r' && *s!='\n' && *s && i<(sizeof(m_header)-1))  
      {
        *d++=*s++;
        i++;
      }
      *d=0;
      UnlockSched();
      break;
      
    case 'M':
    case 'E':
      bot=bot->next=malloc(sizeof(MMENU));
      bot->type=(c=='M')?1:2;
      while(*s==' ') s++;  // Пропускаем пробел?      
      d=bot->file;
      i=0;
      while(*s!=' ' && *s && i<(sizeof(bot->file)-1))
      {
        *d++=*s++;
        i++;
      }
      *d=0;      
      while(*s==' ') s++;  // Пропускаем пробел?      
      d=bot->name;
      i=0;
      while(*s!='\r' && *s!='\n' && *s && i<(sizeof(bot->name)-1))
      {
        *d++=*s++;
        i++;
      }
      *d=0;        
      bot->next=0;
      break;
    default:
      break;
      
    }
  }
  mfree(buf);
  return top;
}



HEADER_DESC mainmenu_HDR={0,0,0,0,NULL,(int)m_header,LGP_NULL};



void main_menu_ghook(void *data, int cmd)
{
  MMENU *top=MenuGetUserPointer(data);
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==3)
  {
    while(top)
    {
      MMENU *s;
      s=top;
      top=top->next;
      mfree(s);
    }
  }
}

MENU_DESC mainmenu_STRUCT;

int main_menu_onkey(void *data, GUI_MSG *msg)
{
  MMENU *top, *s, *t;
  int i;
  int d=0;
  top=MenuGetUserPointer(data);
  if (msg->keys==0x18 || msg->keys==0x3D)
  {
    i=GetCurMenuItem(data);
    while(top && d!=i)  {top=top->next; d++;}
    if (!top) return (-1);
    switch (top->type)
    {
    case 1:
      s=t=ParseMenuFile(top->file);
      d=0;
      while(s)
      {
        d++;
        s=s->next;
      }  
      patch_header(&mainmenu_HDR);
      CreateMenu(0,0,&mainmenu_STRUCT,&mainmenu_HDR,0,d,t,0);
      break;
      
    case 2:
      create_ed(top->file);
      break;
    }  
    return(-1);
  }
  return(0);
}

void main_menu_iconhndl(void *data, int curitem, void *user_pointer)
{
  WSHDR *ws;
  char *s;
  MMENU *top=user_pointer;
  void *item=AllocMenuItem(data);
  int i=0;
  while(top && i!=curitem) {top=top->next; i++;}
  s=top?top->name:"іцґн";
  ws=AllocMenuWS(data,strlen(s));
  ascii2ws(ws,s,0);
  SetMenuItemText(data,item,ws,curitem);
}



MENU_DESC mainmenu_STRUCT=
{
  8,main_menu_onkey,main_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x10,
  main_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};




void maincsm_oncreate(CSM_RAM *data)
{
  MMENU *top, *s;
  int i=0;
  MAIN_CSM *csm=(MAIN_CSM*)data;
  
  s=top=ParseMenuFile("main.txt");
  while(s)
  {
    i++;
    s=s->next;
  }    
  patch_header(&mainmenu_HDR);
  csm->gui_id=main_menu_id=CreateMenu(0,0,&mainmenu_STRUCT,&mainmenu_HDR,0,i,top,0);
}

void maincsm_onclose(CSM_RAM *csm)
{
  free_font_lib();
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
  }
  return(1);
}

const int minus11=-11;
unsigned short maincsm_name_body[20];

const struct
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
    19
  }
};


void UpdateCSMname(void)
{
  ascii2ws((WSHDR *)(&MAINCSM.maincsm_name), "Physics",0);
}

int main(char *filename)
{
  init_font_lib();
  char *s;
  int len;
  MAIN_CSM csm;
  s=strrchr(filename,'\\');
  len=(s-filename)+1;
  strncpy(g_fname,filename,len);
  g_fname[len]=0;
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,&csm,0);
  UnlockSched();
  return 0;
}
