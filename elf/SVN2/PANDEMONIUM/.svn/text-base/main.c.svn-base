#include "..\inc\swilib.h"

extern void InitConfig();
extern char path[128];

#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

#define mode_disabled  0
#define mode_enanled   1

//==============================================================================
// ELKA Compatibility
#pragma inline
static void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()-1+YDISP;
}
//==============================================================================


char path[128]="4:\\ZBin\\daemons\\";

typedef struct
{
  char name[128];
  int oldmode;
  int newmode;
  int size;
}TDaemon;

TDaemon *daemons=NULL;
int ndaemons=0;
int total=0;

//int icon[]={0x58,0};
const int minus11=-11;

WSHDR *ews;

#define nmeth 24

void * gui_methods[nmeth];
void * old_redraw;

typedef void (*tredraw)(void *data);


static const char RED[4]={255,0,0,100};
static const char BLACK[4]={0,0,0,100};

void new_redraw(void *data)
{
  ((tredraw)old_redraw)(data);
  wsprintf(ews,"total ~%dk",total/1024);
  DrawString(ews,ScreenW()/2,YDISP+2,ScreenW(),YDISP+32,FONT_SMALL+1,TEXT_ALIGNMIDDLE,RED,BLACK);
}

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;


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

void FreeDaemonList()
{
  ndaemons=0;
  mfree(daemons);
  daemons=NULL;
}

int LoadDaemonList()
{   
  DIR_ENTRY de;
  unsigned int err;
  TDaemon * d;
  char name[256];
  FreeDaemonList();
  strcpy(name,path);
  strcat(name,"*.*");
  char *s;
  int len;
  int mode=0;
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY))
      {
        if ((s=strrchr(de.file_name,'.')))
        {
          len=s-de.file_name;
          s++;
          if (strcmp_nocase(s,"elf")==0) mode=mode_enanled+1;
          else if (strcmp_nocase(s,"fakk")==0)  mode=mode_disabled+1;
          else mode=0;
          if (mode)
          {
            d=daemons=realloc(daemons,(ndaemons+1)*sizeof(TDaemon));
            d+=ndaemons;
            strncpy(d->name,de.file_name,len);
            d->name[len]=0;
            d->size=de.file_size;
            total+=d->size;
            d->oldmode=d->newmode=mode-1;
            ndaemons++;
          }
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return ndaemons;
};

int SaveDaemonList()
{
  TDaemon *d=daemons;
  for(int i=0;i<ndaemons;i++)
  {
    char a[256],b[256]; 
    if(d->newmode!=d->oldmode)
    {
      unsigned int err;
      sprintf(a,"%s%s.fakk",path,d->name);
      sprintf(b,"%s%s.elf",path,d->name);
      if(d->newmode==mode_disabled)
        fmove(b,a,&err);
      else
        fmove(a,b,&err);
      if (err) return (err);
    }
    d++;
  }
  return 0;
};

int create_menu(void);

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(128);
  
  if(!LoadDaemonList())
  {
    mfree(daemons);  
    ShowMSG(2,(int)"Cant access Zbin\\Daemons!");
  }
  csm->gui_id=create_menu();  
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  if(SaveDaemonList()) //ошибка
    ShowMSG(2,(int)"Error while saving daemons list!!");
  FreeWS(ews);
  FreeDaemonList();
  SUBPROC((void *)Killer);
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
 /* else
    {
    wsprintf(ews,"total ~%dk",total/1024);
    unsigned int RED=0x640000FF;
    unsigned int BLACK=0x64000000;
    DrawString(ews,ScreenW()/2,2,ScreenW(),32,SMALL_FONT+1,0,(char*)&RED,(char*)&BLACK);  
   };*/
  return(1);
}

unsigned short maincsm_name_body[140];

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
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Pandemonium ||");
}



SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"On/Off"},
  {0x0001,0x0000,(int)"Exit"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


int S_ICONS[3];

HEADER_DESC contactlist_menuhdr={0,0,131,21,NULL,(int)"Autostart:",LGP_NULL};
int menusoftkeys[]={0,1,2};

void contactlist_menu_ghook(void *data, int cmd);
int contactlist_menu_onkey(void *data, GUI_MSG *msg);
void contactlist_menu_iconhndl(void *data, int curitem, void *unk);

MENU_DESC contactlist_menu=
{
  8,contactlist_menu_onkey,contactlist_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x11,
  contactlist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int create_menu(void)
{
  patch_header(&contactlist_menuhdr);
  return CreateMenu(0,0,&contactlist_menu,&contactlist_menuhdr,0,ndaemons,0,0);
}

void contactlist_menu_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data,32);
  str_2ws(ws,daemons[curitem].name,32);
  SetMenuItemIconArray(data,item,S_ICONS);
  SetMenuItemText(data,item,ws,curitem);
  SetMenuItemIcon(data,curitem,daemons[curitem].newmode);
}

void contactlist_menu_ghook(void *data, int cmd)
{
  static int unhooked=1;
  if(unhooked)
  {
     GUI * gui=(GUI*)data;
     memcpy(&gui_methods,gui->methods,nmeth*4);    
     gui->methods=&gui_methods;  
     old_redraw=gui_methods[0];
     gui_methods[0]=(void*)&new_redraw;     
     unhooked=0;
  }
}

int contactlist_menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    if (!ndaemons)
    {
      ShowMSG(1, (int)"There is nothing to choose!");
      return (-1);
    }
    int i=GetCurMenuItem(data);
    daemons[i].newmode=1-daemons[i].newmode;
    total+=((daemons[i].newmode)?1:-1)*(daemons[i].size);
    RefreshGUI();
    return(-1);
  }
  if (msg->keys==0x3D)
  {
    //create_options_menu();
    ShowMSG(2,(int)"PANDEMONIUM\n(c)captain_SISka 2007");
    return(-1);
  }
  return(0);
}

int main()
{
  unsigned int err;  
  
  if (!isdir((path),&err))
  {
    path[0]='0';
  }
  
  S_ICONS[0]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);//icon_disabled;
  S_ICONS[1]=GetPicNByUnicodeSymbol(CBOX_CHECKED);//icon_enabled;
  S_ICONS[2]=0;
  
  char dummy[sizeof(MAIN_CSM)];
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}


