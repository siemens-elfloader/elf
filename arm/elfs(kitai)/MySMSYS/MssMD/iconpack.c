#include "..\..\inc\swilib.h"
#include "iconpack.h"
#include "config_data.h"
#include "sms_dat.h"

const char *icon_names[]=
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

const int icon_default[]=
{
#ifdef NEWSGOLD
#ifdef ELKA
  0x538,0x538,0x538,0x538,0x538,0x538,0x538,
  0x5B6,0x5B5,0x5B8,0x5B2,
  0x5B3,0x5B4,0x5B4,0x5B4,
  0x2AB,0x2AB,0x2AB,0x5A4,0x2AB,0x598,0x598,
  0x2A5,0x4DB,0x28C,
  0x282,0x52C,
  426,
  0x2AB,
  0,0
#else
#ifdef S68
  //0x574,0x574,0x574,0x574,0x574,0x574,0x574, //blank
  0x3ED,0x5F4,0x5D5,0x5F6,0x5F0,0x5F1,0x6B8, //blank
  0x5F4,0x5F3,0x5F6,0x5F0,
  0x5F1,0x5F2,0x5F2,0x5F2,
  0x5D7,0x5F4,0x5D5,0x5F6,0x5F0,0x5F1,0x5F1,
  0x4CF,0x2BA,0x2D6,
  0x576,0x576,
  0x5FA,
  0x5FA,
  0,0
#else
  0x564,0x564,0x564,0x564,0x564,0x564,0x564, //blank
  0x5E2,0x5E1,0x5E4,0x5DE,
  0x5DF,0x5E0,0x5E0,0x5E0,
  0x5C5,0x29E,0x5C5,0x515,0x5C4,0x5C5,0x5C5,
  0x29A,0x505,0x1A1,
  0x278,0x558,
  467,
  0x5C5,
  0,0
#endif
#endif
#endif
};

ICONPACK ip;

void InitIconPack(void)
{
  //smsList.c
  extern int SL_HDR_ICONS[7][2];
  extern int SL_ICONS[];
  extern int ESL_ICONS[];
  SL_HDR_ICONS[0][0]=ip.hdr_allsms;
  SL_HDR_ICONS[1][0]=ip.hdr_sent;
  SL_HDR_ICONS[2][0]=ip.hdr_inbox;
  SL_HDR_ICONS[3][0]=ip.hdr_smsnew;
  SL_HDR_ICONS[4][0]=ip.hdr_draft;
  SL_HDR_ICONS[5][0]=ip.hdr_inbox;
  //SL_HDR_ICONS[5][0]=0
  SL_ICONS[0]=ip.sms_inread;
  SL_ICONS[1]=ip.sms_sent;
  SL_ICONS[2]=ip.sms_inread;
  SL_ICONS[3]=ip.sms_innew;
  SL_ICONS[4]=ip.sms_draft;
  SL_ICONS[5]=ip.sms_inread;
  //SL_ICONS[6]=0
  ESL_ICONS[0]=ip.ems_inread;
  ESL_ICONS[1]=ip.ems_sent;
  ESL_ICONS[2]=ip.ems_inread;
  ESL_ICONS[3]=ip.ems_innew;
  ESL_ICONS[4]=ip.ems_draft;
  ESL_ICONS[5]=ip.ems_inread;
  //ESL_ICONS[6]=0
  
  //edGui.c
  extern int EDHDRIC_VIEW[];
  extern int EDHDRIC_EDIT[];
  extern int EDHDRIC_ADRBK[];
  EDHDRIC_VIEW[0]=ip.hdr_ed_view;
  EDHDRIC_EDIT[0]=ip.hdr_ed_edit;
  EDHDRIC_ADRBK[0]=ip.hdr_ed_adrbk;
  
  //main.c
  extern int MM_ITEM_ICONS[];
  extern int MM_HDR_ICONS[];
  MM_ITEM_ICONS[0]=ip.mm_crtsms;
  MM_ITEM_ICONS[1]=ip.mm_smsnew; //new in sms
  MM_ITEM_ICONS[2]=ip.mm_inbox;
  MM_ITEM_ICONS[3]=ip.mm_sent;
  MM_ITEM_ICONS[4]=ip.mm_draft;
  //MM_ITEM_ICONS[5]=ip.mm_allsms;
  //MM_ITEM_ICONS[6]=ip.mm_others;
  MM_ITEM_ICONS[5]=ip.mm_others;
  
  //MM_ITEM_ICONS[7]=0;
  //MM_HDR_ICONS[0]=ip.hdr_mmenu;
  MM_HDR_ICONS[0]=ip.icon_mysmsys;
  
  //popGui.c
  extern int pp_incoming_icons[];
  extern int pp_showmsg_icons[];
  pp_incoming_icons[0]=ip.pp_incoming;
  pp_showmsg_icons[0]=ip.pp_showmsg;
  
  //TabGui.c
  extern int TabIcons[5][4];
  int i;
  for(i=0;i<4;i++)
  {
    TabIcons[0][i]=ip.hdr_mmenu;
  }
  for(i=0;i<4;i++)
  {
    TabIcons[1][i]=ip.hdr_inbox;
  }
  for(i=0;i<4;i++)
  {
    TabIcons[2][i]=ip.hdr_sent;
  }
  for(i=0;i<4;i++)
  {
    TabIcons[3][i]=ip.hdr_draft;
  }
  for(i=0;i<4;i++)
  {
    TabIcons[4][i]=ip.hdr_filter;
  }
}

void LoadDefaultIP(void)
{
  memcpy(&ip, icon_default, sizeof(ICONPACK));
}

void ZeroIconPack(void)
{
  zeromem(&ip, sizeof(ICONPACK));
}

void FreeIconPack(void)
{
  int max=sizeof(ICONPACK)/sizeof(int);
  int i, *p, z;
  p=(int *)(&ip);
  for(i=0;i<max;i++)
  {
    z=p[i];
    if(((unsigned int)z>>28)==0xA)
    {
      //GetCPUClock();
      mfree((void *)z);
    }
  }
  LoadDefaultIP();
}

void LoadIconPack(void)
{
  int max=sizeof(ICONPACK)/sizeof(int);
  unsigned int err;
  int len, c, i, *p;
  char folder[128], ftemp[128], *tt;
 //-------------------
 // InitIconPack();
  FreeIconPack();
 //-------------------
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  if(!isdir(folder, &err))
    return;
  strcat(folder, "Img\\");
  if(!isdir(folder, &err))
  {
    mkdir(folder, &err);
    return;
  }
  p=(int *)(&ip);
  for(i=0;i<max;i++)
  {
    strcpy(ftemp, folder);
    if(icon_names[i])
    {
      strcat(ftemp, icon_names[i]);
      if(IsFileExist(ftemp))
      {
	tt=malloc(128);
	strcpy(tt, ftemp);
	p[i]=(int)tt;
      }
    }
  }
  InitIconPack();
}

