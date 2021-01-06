#include "include.h"
#include "File.h"
#include "IconPack.h"

const char *IconNames[]=
{
  //main menu
  "mm_crtsms.png", //create
  "mm_smsnew.png", //new in sms
  "mm_inbox.png", //inbox
  "mm_sent.png",
  "mm_draft.png",
  "mm_allsms.png",
  "mm_others.png",
  
  //sms type
  "sms_innew.png",
  "sms_inread.png",
  "sms_sent.png",
  "sms_draft.png",
  //ems
  "ems_innew.png",
  "ems_inread.png",
  "ems_sent.png",
  "ems_draft.png",
  //headr icon
  //hdr menu
  "hdr_mmenu.png",
  "hdr_smsnew.png",
  "hdr_inbox.png",
  "hdr_sent.png",
  "hdr_draft.png",
  "hdr_allsms.png",
  "hdr_filter.png",
  //hdr edit_gui
  "hdr_ed_view.png",
  "hdr_ed_edit.png",
  "hdr_ed_adrbk.png", //addressbook
  
  //pop-up window icon
  "pp_incoming.png",
  "pp_showmsg.png",
  
  //display
  "dis_smsnew.png", //show in display
  "icon_mysmsys.png"
  "",""
};

const int DefaultIcons[]=
{
  ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK, 
#ifdef NEWSGOLD
#ifdef ELKA
  0x5B6,0x5B5,0x5B8,0x5B2,
  0x5B3,0x5B4,0x5B4,0x5B4,
#else
#ifdef S68
  0x5F4,0x5F3,0x5F6,0x5F0,
  0x5F1,0x5F2,0x5F2,0x5F2,
#else
  0x5E2,0x5E1,0x5E4,0x5DE,
  0x5DF,0x5E0,0x5E0,0x5E0,
#endif
#endif
#endif
  ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,ICON_BLANK,
  ICON_BLANK,ICON_BLANK,ICON_BLANK,
  ICON_BLANK,ICON_BLANK,
  ICON_BLANK,
  ICON_BLANK,
  0,0
};

void IconPack::LoadIconPack(void)
{
  int max=sizeof(ICONPACK)/sizeof(int);
  int /*len, c, */i, *p;
  char folder[128], ftemp[128], *tt;
  strcpy(folder, main_folder);
  //len=strlen(folder);
  //c=folder[len-1];
  //if(c!='\\' && c!='/')
  //{
  //  folder[len]='\\';
  //  folder[len+1]=0;
  //}
  if(!IsDir(folder))
    return;
  strcat(folder, "Img\\");
  if(!IsDir(folder))
  {
    MkDir(folder);
    return;
  }
  p=(int *)(&this->ip);
  for(i=0;i<max;i++)
  {
    strcpy(ftemp, folder);
    if(IconNames[i])
    {
      strcat(ftemp, IconNames[i]);
      if(IsFileExist(ftemp))
      {
	tt=new char[128];
	strcpy(tt, ftemp);
	p[i]=(int)tt;
      }
    }
  }
  InitIconPack();
}

void IconPack::FreeIconPack(void)
{
  int max=sizeof(ICONPACK)/sizeof(int);
  int i, *p, z;
  p=(int *)(&this->ip);
  for(i=0;i<max;i++)
  {
    z=p[i];
    if(((unsigned int)z>>28)==0xA)
    {
      delete (void *)z;
    }
  }
  LoadDefaultIP();
}

void IconPack::LoadDefaultIP(void)
{
  memcpy(&this->ip, DefaultIcons, sizeof(ICONPACK));
}

void IconPack::ZeroIconPack(void)
{
  zeromem(&this->ip, sizeof(ICONPACK));
}

void IconPack::InitIconPack(void)
{
  //TabGUI.cpp
  int i;
  extern int TABICONS[5][4];
  for(i=0;i<4;i++)
  {
    TABICONS[0][i]=ip.hdr_mmenu;
  }
  for(i=0;i<4;i++)
  {
    TABICONS[1][i]=ip.hdr_inbox;
  }
  for(i=0;i<4;i++)
  {
    TABICONS[2][i]=ip.hdr_sent;
  }
  for(i=0;i<4;i++)
  {
    TABICONS[3][i]=ip.hdr_draft;
  }
  for(i=0;i<4;i++)
  {
    TABICONS[4][i]=ip.hdr_filter;
  }
  
  //mainmenu.cpp
  extern int MM_ITEM_ICONS[];
  MM_ITEM_ICONS[0]=ip.mm_crtsms;
  MM_ITEM_ICONS[1]=ip.mm_smsnew; //new in sms
  MM_ITEM_ICONS[2]=ip.mm_inbox;
  MM_ITEM_ICONS[3]=ip.mm_sent;
  MM_ITEM_ICONS[4]=ip.mm_draft;
  MM_ITEM_ICONS[5]=ip.mm_others;
  
  //SmsListMenu.cpp
  extern int SLM_ICONS[];
  SLM_ICONS[0]=ip.sms_inread;
  SLM_ICONS[1]=ip.sms_sent;
  SLM_ICONS[2]=ip.sms_inread;
  SLM_ICONS[3]=ip.sms_innew;
  SLM_ICONS[4]=ip.sms_draft;
  SLM_ICONS[5]=ip.sms_inread;
}

IconPack::IconPack()
{
  LoadDefaultIP();
  LoadIconPack();
}

IconPack::~IconPack()
{
  FreeIconPack();
}

IconPack *IP=NULL;




