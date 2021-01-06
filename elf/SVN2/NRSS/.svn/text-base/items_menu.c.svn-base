#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "items_menu.h"
#include "view_item.h"
#include "main.h"
#include "strings.h"

static const HEADER_DESC items_menu_hdr = {0, 0, 0, 0, NULL, (int)"RSS2.0 Reader", LGP_NULL};

static const int items_menu_softkeys[] = {0,1,2};

static const SOFTKEY_DESC items_menu_sk[]=
{
  {0x0018, 0x0000, (int)"View"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB items_menu_skt =
{
  items_menu_sk, 0
};

static int items_menu_onkey(void *data, GUI_MSG *msg)
{
  int i;
  RSS_ITEM *p=rss_first;
  i=GetCurMenuItem(data);
  for (int n=0; p && n!=i; n++)
  {
    p=p->next;    
  }
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    if (p)
    {
      create_view_item(p);
    }
    return(-1);
  }
  return (0); 
}

static void items_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  } 
}

static void items_menu_iconhndl(void *data, int curitem, void *user_pointer)
{
  RSS_ITEM *p=rss_first;
  void *item=AllocMLMenuItem(data);
  
  WSHDR *ws2;
  WSHDR *ws4;

  WSHDR ws1loc, *ws1;
  unsigned short num[128];
  ws1=CreateLocalWS(&ws1loc,num,128);

  WSHDR ws3loc, *ws3;
  unsigned short num3[128];
  ws3=CreateLocalWS(&ws3loc,num3,128);
  
  for (int i=0; p && i!=curitem; i++)
  {
    p=p->next;    
  }
  if (p)
  {
    if (p->title)
    {
      ascii2ws(ws1, p->title);
    }
    else
    {
      ascii2ws(ws1, "Unknown title");
    }
    
    
    if (p->description)
    {
      ascii2ws(ws3, p->description);
    }
    else
    {
      ascii2ws(ws3, "No description");
    }
  }
  else
  {
    ascii2ws(ws1, "Error!");
  }

  ws2=AllocMenuWS(data,ws1->wsbody[0]);
  wstrcpy(ws2,ws1);
  
  ws4=AllocMenuWS(data,ws3->wsbody[0]);
  wstrcpy(ws4,ws3);
  
  SetMLMenuItemText(data, item, ws2, ws4, curitem);
}


static const ML_MENU_DESC items_menu_desc=
{
  8,items_menu_onkey,items_menu_ghook,NULL,
  items_menu_softkeys,
  &items_menu_skt,
  0x10, //+0x400
  items_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1 //Добавочных строк  
};

int create_rssitems_menu(void)
{
  int i=0;
  RSS_ITEM *p=(RSS_ITEM *)&rss_first;
  while((p=p->next)) i++;
  patch_header(&items_menu_hdr);
  return CreateMultiLinesMenu(0,0,&items_menu_desc,&items_menu_hdr,0,i);
}





