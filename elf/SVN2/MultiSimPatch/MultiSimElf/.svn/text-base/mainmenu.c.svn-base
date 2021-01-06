#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
//#include "pnglist.h"
#include "language.h"
#include "mainmenu.h"


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
/*
#pragma inline
static void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}
*/
//==============================================================================
int MainMenu_ID;
//extern char buf5401[0x30*20];
extern BLOCK5401 block5401[MAX_SIM_CNT];
#define __SVN_REVISION__  1007
int S_ICONS[3];
  int simnum=0;
    int simcnt=0;
static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)LG_SELECT},
  {0x0001, 0x0000, (int)LG_CLOSE},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

extern IPC_REQ gipc2;
extern void ChangeSim( int num);


static void Settings(void)
{
  ShowSetMenu();
}

static void AboutDlg(){
    ShowMSG(2, (int)LG_COPYRIGHT);
}

static const HEADER_DESC menuhdr={0,0,0,0,NULL,(int)LG_MENU,LGP_NULL};

static const int mmenusoftkeys[]={0,1,2};

static const char * const menutexts[]=
{
  LG_MNUABOUT,
  LG_MNUEDCFG,

  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,
  LG_MNUVIRTSIM,


};

static const void *menuprocs[]=
{
  (void *)AboutDlg,
  (void *)Settings,

};
/*
ghook_cmd:
1 - OncreateFirst
2 - OnCreateAfterLLQ
3 - OnClose
4 - OnFocusFirst
5 - OnFocusAfterLLQ
6 - UnFocus
7 - OnRedraw
//8
9 - OnRefreshFirst(OnUnfocus)
10 - OnRefreshSec(OnFocus)
//11
12 - Edit_change_field
13 - Edit_comdo_box_change
14 - MenuDown
15 - MenuUp
//16
//17
//18
*/

void tmenu_ghook(void *data, int cmd)
{
//  simcnt=9;
  if (cmd==9)
  {
 //   Menu_SetItemCountDyn(data,3+simcnt);
//    if (simnum<3+simcnt)      SetCursorToMenuItem(data,2+simnum);
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
    Menu_SetItemCountDyn(data,2+simcnt);
    if (simnum<3+simcnt)      SetCursorToMenuItem(data,2+simnum);
  }
}

static int icon_array[2];

extern unsigned char bp[1024];

static void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);

  const char percent_t[]="%t";
//  extern const char percent_t[];
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws,percent_t,menutexts[curitem]);

  if(curitem<2){
    SetMenuItemIconArray(data,item,S_ICONS+curitem);
  }else{
  if (curitem==simnum+2){
  SetMenuItemIconArray(data,item,icon_array+0);
//  SetCursorToMenuItem(data,curitem);
  }
  else
      SetMenuItemIconArray(data,item,icon_array+1);
  }
  if (curitem<2);

  else{

   ws=AllocMenuWS(data,strlen((const char*)block5401[curitem-2].SPNname));
   wsprintf(ws,percent_t,block5401[curitem-2].SPNname);
//   wsprintf(ws,"%d",curitem-2);
//   ws=AllocMenuWS(data,strlen("sim 924234"));
//   wsprintf(ws,"sim %x %d",strlen((const char*)block5401[curitem-2].SPNname),curitem);
  }
    SetMenuItemText(data, item, ws, curitem);

}

static int tmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    if (GetCurMenuItem(data)<2)
      ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
    else
      ChangeSim(GetCurMenuItem(data)-2);
  }else{
/*      char ss[256];
      sprintf (ss,"%X %X\n%X %X",msg->keys,msg->gbsmsg->submess,msg->gbsmsg->msg);
      ShowMSG(1,(int)ss);
    */
  if ((msg->gbsmsg->submess>='0')&&(msg->gbsmsg->submess<=('0'+simcnt))){

      ChangeSim(msg->gbsmsg->submess-'0');
  }
  }
  return(0);
}


static const MENU_DESC tmenu=
{
  8,tmenu_keyhook,tmenu_ghook,NULL,
  mmenusoftkeys,
  &menu_skt,
  0x11,//MENU_FLAG,
  menuitemhandler,
  NULL,//menuitems,
  NULL,//menuprocs,
  11
};


  char str1[]="4:\\zbin\\img\\ext\\TXT_SMALL.png";
  char str2[]="4:\\zbin\\img\\ext\\BCFG_SMALL.PNG";;
  char str3[]="4:\\zbin\\img\\ext\\BCFG_SMALL.PNG";;
//Õ”∆ÕŒ Õ¿–»—Œ¬¿“‹  ¿–“»Õ » À»¡Œ —Ã≈Õ»“‹ œ”“»
  //char str1[]="4:\\zbin\\img\\multisim\\1.png";;
  //char str2[]="4:\\zbin\\img\\multisim\\2.png";
  //char str3[]="4:\\zbin\\img\\multisim\\3.png";
int ShowMainMenu()
{
    extern const char *successed_config_filename;
  str1[0]=  successed_config_filename[0];
  str2[0]=  successed_config_filename[0];
  str3[0]=  successed_config_filename[0];
  S_ICONS[0]=(int)str1;
  S_ICONS[1]=(int)str2;


  S_ICONS[2]=(int)str3;
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  *((int **)(&menuhdr.icon))=&S_ICONS[2];
  patch_header(&menuhdr);
  MainMenu_ID=CreateMenu(0,0,&tmenu,&menuhdr,0,11,0,0);
  return MainMenu_ID;
}
