#include "../inc/swilib.h"
#include "main.h"
#include "jabber_util.h"
#include "bookmarks.h"
#include "MUC_Enter_UI.h"
#include "lang.h"
#include "rect_patcher.h"
#include "xml_gen.h"

BM_ITEM *BM_ROOT  = NULL;
int reqbook = 0; //флаг запроса закладок

void KillBMList()
{
  LockSched();
  BM_ITEM* cl=BM_ROOT;
  BM_ROOT=NULL;
  while(cl)
  {
    BM_ITEM *p;
    mfree(cl->bmname);
    if(cl->mucname)mfree(cl->mucname);
    if(cl->nick)mfree(cl->nick);
    if(cl->pass)mfree(cl->pass);
    p=cl;
    cl=(BM_ITEM*)(cl->next);
    mfree(p);
    p=NULL;
  }
  reqbook = 0;
  UnlockSched();
}

void Process_Bookmarks_Storage(XMLNode* nodeEx)
{
  XMLNode *elem = nodeEx->subnode;
  XMLNode *tmpnode;
  extern const char conference_t[];
  extern const int MUC_AUTOJOIN;
  char jid[] = "jid";
  char ajoin=0;
  char *bm_name = NULL;
  char *n_name = NULL;
  char *c_name=NULL;
  char *c_nick=NULL;
  char *c_pass=NULL;
  char *c_ajoin = NULL;

  while(elem)
  {
    n_name = elem->name;
    if(!n_name)return;
     if(!strcmp(n_name, conference_t)) // Элемент конференции
    {
      c_name = XML_Get_Attr_Value(jid,elem->attr);
      bm_name = XML_Get_Attr_Value("name",elem->attr);
      if(!bm_name) 
        if(!c_name) bm_name = "Error bookmark!";
         else bm_name = c_name;

      c_ajoin = XML_Get_Attr_Value("autojoin",elem->attr);
 
      tmpnode = XML_Get_Child_Node_By_Name(elem, "nick");
      if(tmpnode)
      {
        c_nick = tmpnode->value;
      }else c_nick=NULL;

      tmpnode = XML_Get_Child_Node_By_Name(elem, "password");
      if(tmpnode)
      {
        c_pass = tmpnode->value;
      }else c_pass = NULL;

      BM_ITEM *bmitem = malloc(sizeof(BM_ITEM));

      bmitem->bmname = malloc(strlen(bm_name)+1);
      strcpy(bmitem->bmname, bm_name);
  
      bmitem->mucname = malloc(strlen(c_name)+1);
      strcpy(bmitem->mucname, c_name);
      if(c_nick)
      {
        bmitem->nick = malloc(strlen(c_nick)+1);
        strcpy(bmitem->nick, c_nick);
      }
      else bmitem->nick = NULL;
      if(c_pass)
      {
        bmitem->pass = malloc(strlen(c_pass)+1);
        strcpy(bmitem->pass, c_pass);
      }
      else bmitem->pass = NULL;

      // Создаём очередной элемент списка
      //если нет имени конфы такая закладка нам ненужна
      if(bmitem->mucname)
      {
      if(MUC_AUTOJOIN && c_ajoin && (bmitem->nick))
      {
      if((!strcmp(c_ajoin, "true"))||(!strcmp(c_ajoin, "1")))
        {
          ajoin=1;
          extern const unsigned int DEFAULT_MUC_MSGCOUNT;
          Enter_Conference(bmitem->mucname, bmitem->nick, bmitem->pass, DEFAULT_MUC_MSGCOUNT);
        }
      }
      bmitem->next = NULL;

      BM_ITEM *tmp=BM_ROOT;
      if(tmp)
        while(tmp->next)tmp = tmp->next;
      if(tmp)
      {
        tmp->next = bmitem;
      }
      else BM_ROOT = bmitem;
      }
    }
    elem = elem->next;
  }
  if (!(MUC_AUTOJOIN&&ajoin))Disp_BM_Menu();
}

//Context:HELPER
void _getbookmarkslist()
{
  static char priv_id[]="SieJC_priv_req";
  char storage_t[]="storage";
  char xmlns_t[]="xmlns";
  XMLNode *xml_bookmark = XML_CreateNode(storage_t, NULL);
  XML_Set_Attr_Value(xml_bookmark, xmlns_t, JABBER_STORAGE_BOOKMARKS);
  char gget[]=IQTYPE_GET;
  char iqv[]=IQ_PRIVATE;
  SendIq(NULL, gget, priv_id, iqv, xml_bookmark);
}

void Get_Bookmarks_List()
{
  if((!BM_ROOT)&&(reqbook==0))
  {
      SUBPROC((void*)_getbookmarkslist);
      reqbook=1;
  }
  else 
    if(BM_ROOT) Disp_BM_Menu();
}

int BM_MenuID;
int Req_Close_BM_Menu=0;
extern BM_ITEM *BM_ROOT;

const char bmmenu_header[]=LG_MENUBOOKMARK;
int bmmenusoftkeys[]={0,1,2};
HEADER_DESC bm_menuhdr={0,0,0,0,NULL,(int)bmmenu_header,LGP_NULL};
SOFTKEY_DESC bmmenu_sk[]=
{
  {0x0018,0x0000,(int)LG_EDIT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB bmmenu_skt=
{
  bmmenu_sk,0
};

void bm_menu_ghook(void *data, int cmd);
int bm_menu_onkey(void *data, GUI_MSG *msg);
void bm_menu_iconhndl(void *data, int curitem, void *unk);

MENU_DESC bm_menu=
{
  8,bm_menu_onkey,bm_menu_ghook,NULL,
  bmmenusoftkeys,
  &bmmenu_skt,
  0x11,
  bm_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void bm_menu_ghook(void *data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)  // onFocus
  {
    DisableIDLETMR();
    if(Req_Close_BM_Menu)
    {
      Req_Close_BM_Menu=0;
      GeneralFunc_flag1(BM_MenuID,1);
    }
  }
}

/*
  Обработчик нажатий клавиш меню. Отсюда следует вызывать необходимые действия

*/
int bm_menu_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    char s=0;
    BM_ITEM *it = BM_ROOT;
    while(s!=i && it)
    {
      s++;
      it=it->next;
    };
    if(it->mucname && it->nick && (msg->keys == 0x3D)) //Нажат центральный джой
    {
      extern const unsigned int DEFAULT_MUC_MSGCOUNT;
      Enter_Conference(it->mucname, it->nick, it->pass, DEFAULT_MUC_MSGCOUNT);
    } else Disp_MUC_Enter_Dialog(it->mucname, it->nick, it->pass);
    return 1;
  }
return 0;
}

int BM_ICON[2];
char ICON_MUC[128];

/*
  Обработчик появления пунктов динамического меню
  Тут мы сами создаём каждый пункт, указывая для него иконку и текст.
*/
void bm_menu_iconhndl(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  extern const char percent_t[], empty_t[];
  char test_str[48];
  void *item=AllocMenuItem(data);
  strcpy(test_str,empty_t);
  char s=0;
  BM_ITEM *it = BM_ROOT;
  while(s!=curitem && it)
  {
    s++;
    it=it->next;    
  };
  
  ws=AllocMenuWS(data,strlen(it->bmname));
//  wsprintf(ws,percent_t,it->bmname);
  utf8_2ws(ws,it->bmname,strlen(it->bmname));
  SetMenuItemIconArray(data,item,BM_ICON+1);
  SetMenuItemText(data,item,ws,curitem);
  //SetMenuItemIcon(data,curitem,1);  // 0 = индекс иконки
};

extern const char PATH_TO_PIC[128];

void Init_bm_Icon_array()
{
  strcpy(ICON_MUC, PATH_TO_PIC);strcat(ICON_MUC, "conference.png");
  BM_ICON[1]=(int)ICON_MUC;    
}

void Disp_BM_Menu()
{
  if(BM_ROOT)
  {
    Init_bm_Icon_array();
    int n_items=0;
    BM_ITEM *i = BM_ROOT;
    n_items=1;
    while(i->next)
    {
      n_items++;
      i = i->next;
    }
    patch_rect(&bm_menuhdr.rc,0,YDISP,ScreenW()-1,HeaderH()+YDISP);
    BM_MenuID=CreateMenu(0,0,&bm_menu,&bm_menuhdr,0,n_items,0,0);
  }
}
//EOL,EOF
