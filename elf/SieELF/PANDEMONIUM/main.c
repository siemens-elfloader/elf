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
char name[256];
char oldmode;
char newmode;
int size;
}
TDaemon;

TDaemon *daemons;
int ndaemons;
int total=0;

//int icon[]={0x58,0};
const int minus11=-11;

WSHDR *ews;

#define nmeth 24

void * gui_methods[nmeth];
void * old_redraw;

typedef void (*tredraw)(void *data);

void new_redraw(void *data)
{
((tredraw)old_redraw)(data);
wsprintf(ews,"%t%dKB","全部： ~",total/1024);
unsigned int RED=0x640000FF;
unsigned int BLACK=0x64000000;
DrawString(ews,ScreenW()/2-20,YDISP,ScreenW(),YDISP+60,FONT_SMALL+1,TEXT_ALIGNMIDDLE,(char*)&RED,(char*)&BLACK);
}

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;


int create_menu(void);

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  csm->gui_id=create_menu();  
}

void Killer(void)
{
  FreeWS(ews);
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int SaveDaemonList();
void maincsm_onclose(CSM_RAM *csm)
{
  if(SaveDaemonList()) //铠栳赅
    ShowMSG(2,(int)"保存开机自动启动ELF出错!!");
  mfree(daemons);  
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

int file_size(char * path)
{
unsigned int err,i;
int handle;
int len;
handle=fopen(path,A_ReadOnly+A_BIN,P_READ,&err);
if(handle==-1) return 0;
len=lseek(handle,8*1024*1024,0,&err,&i);
fclose(handle,&err);
return len;
};

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


void del_ext(char *s)
{
while(*s)s++;  
while(*s!='.')s--;
*s=0;
};

int LoadDaemonList()
{   
  ndaemons=0;
  DIR_ENTRY de;
  unsigned int err;
  TDaemon * d=daemons;
  char name[256];
  char bu[256];
  strcpy(name,path);
  strcat(name,"*.elf");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(d->name,de.file_name);
      sprintf(bu,"%s%s",path,de.file_name);
      d->size=file_size(bu);
      total+=d->size;
      del_ext(d->name);
      d->oldmode=d->newmode=mode_enanled;
      ndaemons++;   
      d++;
      }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);

  strcpy(name,path);
  strcat(name,"*.fakk");
  if (FindFirstFile(&de,name,&err))
  {
    do
    {
      strcpy(d->name,de.file_name);
      sprintf(bu,"%s%s",path,de.file_name);
      d->size=file_size(bu);
      del_ext(d->name);
      d->oldmode=d->newmode=mode_disabled;
      ndaemons++;   
      d++;
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
   };
 d++;  
 };
return 0;
};

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"开/关"},
  {0x0001,0x0000,(int)"退出"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


int S_ICONS[3];

HEADER_DESC contactlist_menuhdr={0,0,131,21,NULL,(int)"开机启动:",0x7FFFFFFF};
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
  WSHDR *ws=AllocMenuWS(data,20);
  //wsprintf(ws,"%s",daemons[curitem].name);
  str_2ws(ws, daemons[curitem].name, 128);
  SetMenuItemIconArray(data,item,S_ICONS);
  SetMenuItemText(data,item,ws,curitem);
  SetMenuItemIcon(data,curitem,daemons[curitem].newmode);
}

void contactlist_menu_ghook(void *data, int cmd)
{
  static int unhooked=1;
  if(unhooked){
     GUI * gui=(GUI*)data;
     memcpy(&gui_methods,gui->methods,nmeth*4);    
     gui->methods=&gui_methods;  
     old_redraw=gui_methods[0];
     gui_methods[0]=(void*)&new_redraw;     
     unhooked=0;
     };
}

int contactlist_menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    int i=GetCurMenuItem(data);
    daemons[i].newmode=1-daemons[i].newmode;
    total+=((daemons[i].newmode)?1:-1)*(daemons[i].size);
    SetMenuItemIcon(data,i,daemons[i].newmode);    
    REDRAW();
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
  FSTATS fstats;
  unsigned int err;  
  
  fstats.file_attr=FA_DIRECTORY;
  if (GetFileStats(path,&fstats,&err)==-1) path[0]='0';
  
  ews=AllocWS(128);
  
  daemons=malloc(sizeof(TDaemon)*64);
  if(!LoadDaemonList())
    {
    mfree(daemons);  
    ShowMSG(2,(int)"找不到Zbin\\Daemons!");
    return 0;
    };
  
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


