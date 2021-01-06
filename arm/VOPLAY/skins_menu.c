#include "../inc/swilib.h"
#include "language.h"
#include "main.h"
#include "mainmenu.h"
#include "conf_loader.h"
#include "../inc/cfg_items.h"
#include "rect_patcher.h"
void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush);
extern const char playerfolder[128];
extern int curskin;
char SkinsName[100][20];
int SkinsIcons[100];
char SkinsSize[100][20];
char SkinsFName[100][128];
int mnu_icon[1];
char mnu_fold[256];
int flag;
int selskin_menu_onkey(void *gui, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    flag=1;
    RefreshGUI();
  }
  if (msg->gbsmsg->msg==KEY_UP)
  {
    flag=0;
    RefreshGUI();
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    flag=1;
  }
  if (msg->keys==0x3D || msg->keys==0x18)
  {
      int i=GetCurMenuItem(gui);
      delImghdr();
      curskin=i;
      readskinparamsfromfile();
      rereadskin();
      crtIMGHDR();
      return (1);
  }
  return (0);
}

void selskin_menu_ghook(void *gui, int cmd)
{
  //RefreshGUI();
  if (cmd==3)
  {
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

int selskin_softkeys[]={0,1,2};
SOFTKEY_DESC selskin_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB selskin_skt=
{
  selskin_sk,0
};

//int mnu_icon[1];
//char mnu_fold[256];
void selskin_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  int i=GetCurMenuItem(gui);
  WSHDR *ws2,*ws4;
  
  WSHDR ws1loc, *ws1;
  unsigned short num[128];
  ws1=CreateLocalWS(&ws1loc,num,128);
  WSHDR ws3loc, *ws3;
  unsigned short num3[128];
  ws3=CreateLocalWS(&ws3loc,num3,128);
  
  int len,len2;
  void *item=AllocMLMenuItem(gui);
  
  len=strlen(SkinsName[cur_item]);
  utf8_2ws(ws1,SkinsName[cur_item],320);
  ws2=AllocMenuWS(gui,len+4);
  wstrcpy(ws2,ws1);
  
  if(flag==0)
  {    
    wsprintf(ws3,"            %s kb",SkinsSize[cur_item]); //хй знает как по-другому чтоб на иконку не залезало
    len2=wstrlen(ws3);
  }
  else
  {
    wsprintf(ws3,"%s kb",SkinsSize[cur_item]);
    len2=wstrlen(ws3);    
  }
  ws4=AllocMenuWS(gui,len2+4);
  wstrcpy(ws4,ws3);
  if(flag==1)
  SetMenuItemIconArray(gui, item, mnu_icon);
  else{
  if(cur_item==i)
    SetMenuItemIconArray(gui, item, SkinsIcons+i);
  else
    SetMenuItemIconArray(gui, item, mnu_icon);}
  SetMLMenuItemText(gui, item, ws2, ws4, cur_item);
}

ML_MENU_DESC selskin_STRUCT=
{
  0,selskin_menu_onkey,selskin_menu_ghook,NULL,
  selskin_softkeys,
  &selskin_skt,
  0x11,
  selskin_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1
};

HEADER_DESC selskin_HDR={0,0,0,0,NULL,(int)LG_SELECT_SKIN,LGP_NULL};


void GetSkinsSize(unsigned int number)
{
  DIR_ENTRY dee;
  double size; 
  char skp[128];
  unsigned int err;
  char d[16];
  for(int i=0;i<number;i++)
  {
    sprintf(skp,"%s\\*.*",SkinsFName[i]);
    if (FindFirstFile(&dee,skp,&err))
    {
      do
      {
        if(!(dee.file_attr&FA_DIRECTORY))
        {
          size+=dee.file_size;
        }
      }
      while(FindNextFile(&dee,&err));
    }
    double tot_skin_s=size/1024;
    sprintf(d,"%.02f",tot_skin_s);
    sprintf(SkinsSize[i],d);
    size=0;
    FindClose(&dee,&err);
  }
}

int CreateMenuSkins()
{
  IMGHDR *preview;
  char icon_name[128]="preview.png";
  CloseMAINMENU();
  char name[128];
  unsigned int err;
  DIR_ENTRY de;
  char iconame[128];
  char e[256];
  sprintf(e,"%sskins",playerfolder);
  const char *s=e;
  int n_skin=0/*,n_size=0*/;
  char str[128];
  char ipath[128];
  strcpy(str,s);
  strcat(str,"\\*");
  if (FindFirstFile(&de,str,&err))
  {
    do
    {
      if((de.file_attr&FA_DIRECTORY))
      {
        sprintf(ipath,"%s\\%s",e,de.file_name);
        sprintf(SkinsFName[n_skin],ipath);
        sprintf(iconame,"%s\\%s",ipath,icon_name);
       /* if (GetFileStats(iconame,&stat,&err)==-1)
          flag=1;
        else
        {
          flag=0;*/
          //SkinsIcons[n_skin] = (int)MakeGlobalString(ipath,'\\',icon_name);
        sprintf(name,"%s\\%s",ipath,icon_name);
        preview=CreateIMGHDRFromPngFile(name, 3);
        DrwImg(preview,20,130,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
      //  }
        sprintf(SkinsName[n_skin],de.file_name);   
        n_skin++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  ////mfree(sb);
  sprintf(mnu_fold,"%smenu",playerfolder);
  mnu_icon[0]=(int)MakeGlobalString(mnu_fold,'\\',"skins.png");
  FindClose(&de,&err);
  GetSkinsSize(n_skin);
  patch_header(&selskin_HDR);
  return CreateMultiLinesMenu(0,0,&selskin_STRUCT,&selskin_HDR,curskin,n_skin);
}
