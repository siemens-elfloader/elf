#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "mainmenu.h"
#include "conf_loader.h"

extern const char playerfolder[128];
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

typedef struct
{
  void *next;
  char cfgname[64];
  char fullpath[128];
}SEL_IPL;

int selipl_menu_onkey(void *gui, GUI_MSG *msg)
{
  SEL_IPL *sbtop=MenuGetUserPointer(gui);
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    int i=GetCurMenuItem(gui);
    for (int n=0; n!=i; n++) sbtop=sbtop->next;
    if (sbtop)
    {
      /*
      //Закрываем плеер и запускаем снова с новым плейлистом
      CLOSECURENTCSM();
      WSHDR* ws=AllocWS(128);
      wsprintf(ws,"%sivoplay.elf",playerfolder);
      ExecuteFile(ws,0,sbtop->fullpath);  
      FreeWS(ws);
      //Пока так, а там посмотрим...
      */
      char shliah[255];
      sprintf(shliah,"%sivoplay.elf",playerfolder);
      main(shliah,sbtop->fullpath);
      return (1);
    }
  }
  return (0);
}

void selipl_menu_ghook(void *gui, int cmd)
{
  SEL_IPL *sbtop=MenuGetUserPointer(gui);
  if (cmd==3)
  {
    while(sbtop)
    {
      SEL_IPL *sb=sbtop;
      sbtop=sbtop->next;
      mfree(sb);
    }    
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

int selipl_softkeys[]={0,1,2};
SOFTKEY_DESC selipl_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB selipl_skt=
{
  selipl_sk,0
};

void selipl_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  SEL_IPL *sbtop=user_pointer;
  WSHDR *ws;
  int len;
  for (int n=0; n!=cur_item; n++) sbtop=sbtop->next;
  void *item=AllocMenuItem(gui);
  if (sbtop)
  {
    len=strlen(sbtop->cfgname);
    ws=AllocMenuWS(gui,len+4);
    utf8_2ws(ws,sbtop->cfgname,320);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,pt,LG_ERROR);
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

MENU_DESC selipl_STRUCT=
{
  8,selipl_menu_onkey,selipl_menu_ghook,NULL,
  selipl_softkeys,
  &selipl_skt,
  0x10,
  selipl_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

HEADER_DESC selipl_HDR={0,0,0,0,NULL,(int)LG_SELECT_PLAYLIST,LGP_NULL};


int CreateMenuFindPlaylist()
{
  CloseMAINMENU();
  unsigned int err;
  DIR_ENTRY de;
  char e[256];
  sprintf(e,"%splaylists\\",playerfolder);
  const char *s=e;
  SEL_IPL *sbtop=0;
  SEL_IPL *sb;
  int n_ipl=0;
  char str[128];
  strcpy(str,s);
  strcat(str,"*.*");
  if (FindFirstFile(&de,str,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY))
      {
        extern int strcmp_nocase(const char *s, const char *d);
        sb=malloc(sizeof(SEL_IPL));
        strcpy(sb->fullpath,s);
        strcat(sb->fullpath,de.file_name);
        strcpy(sb->cfgname,de.file_name);
        sb->cfgname[strlen(de.file_name)-4]=0;
        sb->next=0;
        if (sbtop)
        {
          SEL_IPL *sbr, *sbt;
          sbr=(SEL_IPL *)&sbtop;
          sbt=sbtop;
          while(strcmp_nocase(sbt->cfgname,sb->cfgname)<0)
          {
            sbr=sbt;
            sbt=sbt->next;
            if (!sbt) break;
          }
          sb->next=sbt;
          sbr->next=sb;
        }
        else
        {
          sbtop=sb;
        }
        n_ipl++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  patch_header(&selipl_HDR);
  return CreateMenu(0,0,&selipl_STRUCT,&selipl_HDR,0,n_ipl,sbtop,0);
}
