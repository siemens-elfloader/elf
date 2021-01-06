#include "c:\arm\inc\swilib.h"
#include "writemsg.h"
#include "externs.h"
#include "strings.h"

void Seng_Msg();

GUI *ggui=0;
#define wslen(ws) ws->wsbody[0]
#define T_SENDMSG 2

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

int elinfo_onkey(GUI *gui, GUI_MSG *msg){if (msg->keys==0x18){return(-1);}return(0);}
void elinfo_ghook(GUI *gui, int cmd)
{
  if(cmd==0xA)
{
  //void SavePassword();
  DisableIDLETMR();
}
  if(cmd==0x03)
  {
    
    //void SavePassword();
   //FreeWS(elws);
   // elws = NULL;
  }
}

void edchat_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC skk={0x0018, 0x0000,(int)"Ok"};
  if (cmd==7)
  SetSoftKey(data,&skk,SET_SOFT_KEY_N); 
}

int itemnum, wd_id;

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  ggui=data;
  
  void create_ed(void);
  
  switch (msg->gbsmsg->submess)
  {
  case GREEN_BUTTON:
      Seng_Msg();
  break;
  }
  if (msg->keys==0x18)
  {
    
   return(-1);
    //MMenu();
  }
  if (msg->keys==0x1)
  {
    
   // CloseCSM(MAINCSM_ID);
  }
  return(0); 
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)"Сообщени:",LGP_NULL};

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  elinfo_ghook,
  //edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
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
  0x40000000
};

//Ввод сообщения----------------------------------------------------------------
void WriteMsg()
{
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());  
  ws=AllocWS(50);
  
  //ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  //AddEditControlToEditQend(eq,&ec,ma); 
  
  ConstructEditControl(&ec,3,0x40,0,10);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  FreeWS(ws);
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,0);
}




  
