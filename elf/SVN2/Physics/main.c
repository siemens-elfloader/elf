#include "../inc/swilib.h"
#include "../inc/pnglist.h"
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

const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};
const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};

#pragma inline
unsigned int char8to16(int c)
{
  if (c>=128)
  {
    //Win->Dos
    c=wintranslation[c-128];
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}

void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c));
  }
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
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
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
  // Не нашли в кэше, пробуем добавить
  img=CreateIMGHDRFromPngFile(fname,0);
  if (!img) return (-1);
  // Получилось создать картинку
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
  unsigned int c;
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
        wsAppendChar(ews,char8to16(c));
      }
      ConstructEditControl(&ec,3,0x40,ews,wslen(ews));
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
      while(*s==' ') s++;  // Пропускаем пробелы
      
      d=bot->file;
      i=0;
      while(*s!=' ' && *s && i<(sizeof(bot->file)-1))
      {
        *d++=*s++;
        i++;
      }
      *d=0;      
      while(*s==' ') s++;  // Пропускаем пробелы
      
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
  s=top?top->name:"Ошибка";
  ws=AllocMenuWS(data,strlen(s));
  ascii2ws(ws,s);
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
  ascii2ws((WSHDR *)(&MAINCSM.maincsm_name), "Physics");
}

int main(char *filename)
{
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
