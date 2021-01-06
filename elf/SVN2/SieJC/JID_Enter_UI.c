#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "jabber_util.h"
#include "groups_util.h"
#include "JID_Enter_UI.h"
#include "lang.h"
#include "rect_patcher.h"
#include "xml_gen.h"

typedef struct {
  char jid_ask;
  char jid_del;
  char jid_add;
} JIDENTER_SETTINGS;

SOFTKEY_DESC jid_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB jid_menu_skt=
{
  jid_menu_sk,0
};

JIDENTER_SETTINGS jid_set;

WSHDR* jews;
char jTerminate=0;

typedef struct
{
  GUI *ed_grgui;
  int count;
}GRLIST_STRUCT;

void ed_grouplist_handler(USR_MENU_ITEM *item)
{
  GRLIST_STRUCT *gr_str=item->user_pointer;
  int i=item->cur_item;
  if (item->type==0)
  {
      if (i<gr_str->count) utf8_2ws(item->ws,GetGroupNameByID(i+1),80);//���������� "No group"
  }
  if (item->type==1)
  {
      if (i<gr_str->count)
      {
	char *p=GetGroupNameByID(i+1); //���������� "No group"
	WSHDR *ed_ws=AllocWS(strlen(p)*2);
        utf8_2ws(ed_ws,p,strlen(p)*2);
        EDIT_SetTextToEditControl(gr_str->ed_grgui,6,ed_ws);
	FreeWS(ed_ws);
      }
  }
}

int jed1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
  //1: close
  // ���� ������ ������ ���� ������ ������, ������� �� �������� � cmd=7
  if(msg->gbsmsg->submess==GREEN_BUTTON || msg->keys==0x18)
  {
    jTerminate = 1;
    return 1;
  }
  
  if (msg->keys==0x0FF0) //����� ���� �����
  {
    return(1);
  }
if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (msg->gbsmsg->submess==ENTER_BUTTON)
    {
      if (EDIT_GetFocus(data)==8)
      {
    jid_set.jid_ask=!jid_set.jid_ask;  //8 ����� ��� ���������� �������� "������ �����������",
    jid_set.jid_del=!jid_set.jid_del;  // � ��� �������� "�������"
    CutWSTR(jews,0);
    wsAppendChar(jews, jid_set.jid_del?CBOX_CHECKED:CBOX_UNCHECKED);
    EDIT_SetTextToFocused(data,jews);
    return (-1);
      }

      if ((EDIT_GetFocus(data)==6)&&(!EDIT_IsMarkModeActive(data)))
      {
        GRLIST_STRUCT *gr_str=EDIT_GetUserPointer(data);
        int i=gr_str->count=GetGroupCount();
        EDIT_OpenOptionMenuWithUserItems(data,ed_grouplist_handler,gr_str,i);
        return (-1);
      }
    }
  }
  return 0;
}

void jed1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  static SOFTKEY_DESC mmmmsk={0x0018, 0x0000,(int)LG_OK};
  if (cmd==TI_CMD_CREATE)
  {
      GRLIST_STRUCT *gr_str=EDIT_GetUserPointer(data);
      gr_str->ed_grgui=data;
  }
  if (cmd==TI_CMD_REDRAW)
  {
    //OnRun
    ExtractEditControl(data,2,&ec);    
    wstrcpy(jews,ec.pWS);
#ifndef NEWSGOLD
  static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LG_CLOSE};
#endif
#ifdef NEWSGOLD    
    SetSoftKey(data,&mmmmsk,0);
#else
    SetSoftKey(data,&mmmmsk,1);
    if (ec.pWS->wsbody[0]==0)
      SetSoftKey(data,&sk_cancel,SET_SOFT_KEY_N==0?1:0);    
#endif 
  }
  
  if(cmd==TI_CMD_FOCUS)   // �������������
  {
     DisableIDLETMR();   // ��������� ������ ������ �� ��������
  }

  if(jTerminate)
 {
   char* jid_jid = NULL;
   char* jid_name = NULL;
   char* jid_group = NULL;
   jTerminate=0;
   size_t st_len;
   st_len = wstrlen(jews)*2;
   if(st_len)
   {
      jid_jid =  utf16_to_utf8((char**)jews,&st_len);
      jid_jid[st_len]='\0';
   } else jid_jid = NULL;
 
   ExtractEditControl(data,4,&ec);    
   wstrcpy(jews,ec.pWS);
   st_len = wstrlen(jews)*2;
   if(st_len)
   {
      jid_name =  utf16_to_utf8((char**)jews,&st_len);
      jid_name[st_len]='\0';
   }else jid_name=NULL;
  
    ExtractEditControl(data,6,&ec);
    wstrcpy(jews,ec.pWS);
    st_len = wstrlen(jews)*2;
   if(st_len)
   {
      jid_group =  utf16_to_utf8((char**)jews,&st_len);
      jid_group[st_len]='\0';
   } else jid_group =NULL;
   
 if(jid_jid)
 {
  char di[] = "roster3";
  
  XMLNode *xml_item, *xml_group;
  char subscription_t[]="subscription";
  char item_t[]="item";
  char remove_t[]="remove";
  char jid_t[]="jid";
  char name_t[]="name";
  char group_t[]="group";
  xml_item = XML_CreateNode(item_t, NULL);
  XML_Set_Attr_Value(xml_item, jid_t, jid_jid);

  if((jid_set.jid_del)&&(jid_set.jid_add))
  {
    XML_Set_Attr_Value(xml_item, subscription_t, remove_t);
  }
  else
  {
    if(jid_name)
      {
        XML_Set_Attr_Value(xml_item, name_t, jid_name);
      }
    if(jid_group)
    {
      xml_group = XML_CreateNode(group_t, jid_group);
      xml_item->subnode = xml_group;
    }
  }

  SendIq(NULL, IQTYPE_SET, di, IQ_ROSTER, xml_item);
  if((!jid_set.jid_add)&&(jid_set.jid_ask))
    {
      Send_ShortPresence(jid_jid,PRESENCE_SUBSCRIBE);//�������� ������ �����������
    }
 } else ShowMSG(1,(int)LG_JENOJID);
 if(jid_name) mfree(jid_name);
 if(jid_jid) mfree(jid_jid);
 if(jid_group) mfree(jid_group);
 //end if(jid_jid)
 }

  if(cmd==TI_CMD_DESTROY)     // onDestroy
  {
    FreeWS(jews);
  }
}

HEADER_DESC jed1_hdr={0,0,131,21,NULL,(int)LG_JECONTACTHDR,LGP_NULL};

void jed1_locret(void){}

INPUTDIA_DESC jed1_desc=
{
  1,
  jed1_onkey,
  jed1_ghook,
  (void *)jed1_locret,
  0,
  &jid_menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,

//  0x00000001 - ��������� �� ������� ����
//  0x00000002 - ��������� �� ������
//  0x00000004 - �������� ���������
//  0x00000008 - UnderLine
//  0x00000020 - �� ���������� �����
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - �� ��������� ������
//  0x40000000 - �������� ������� ����-������
  0x40000000
};

void Disp_JID_Enter_Dialog(CLIST* ClEx)
{
  //mode 0=edit; 1=add;
  jid_set.jid_del=NULL;
  jid_set.jid_ask=NULL;  
  char *jid = "";
  char *name = "";
  char *group = "";
  if(ClEx)
  {
  jid_set.jid_add=1;
  jid = ClEx->JID;
  name = ClEx->name;
  if(ClEx->group!=0) group = GetGroupNameByID(ClEx->group); //0� ������ �����������, ������������
  }
  else
  {
  jid_set.jid_add=NULL;    
  }
  
  void *ma=malloc_adr();

  void *eq;
  EDITCONTROL ec;
  jews=AllocWS(256);
  eq=AllocEQueue(ma,mfree_adr());
  
  PrepareEditControl(&ec);
  ascii2ws(jews, "JID:");
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  PrepareEditControl(&ec);
  utf8_2ws(jews, jid, 64);
  if(jid_set.jid_add)ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,128);//2 ���� ������ ������� ��� ������ ��������
   else ConstructEditControl(&ec,3,ECF_APPEND_EOL,jews,128);//2
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  ascii2ws(jews, LG_NICK);
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  utf8_2ws(jews, name, 64);
  ConstructEditControl(&ec,3,ECF_APPEND_EOL,jews,80);     // 4
  AddEditControlToEditQend(eq,&ec,ma);  
  
  PrepareEditControl(&ec);
  ascii2ws(jews, LG_JEGROUP);
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);      
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  utf8_2ws(jews, group, 64);
  ConstructEditControl(&ec,3,ECF_APPEND_EOL,jews,80);    //6
  AddEditControlToEditQend(eq,&ec,ma);

  PrepareEditControl(&ec);
  if (!jid_set.jid_add)
  {
    ascii2ws(jews, LG_JEASK);
    ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);      
    AddEditControlToEditQend(eq,&ec,ma);

    PrepareEditControl(&ec);
    CutWSTR(jews, 0);
    wsAppendChar(jews, jid_set.jid_ask?CBOX_CHECKED:CBOX_UNCHECKED);
    ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,jews,jews->wsbody[0]); //8
  }
  else
  {
    ascii2ws(jews, LG_JEDELCONTACT);
    ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);      
    AddEditControlToEditQend(eq,&ec,ma);

  PrepareEditControl(&ec);
  CutWSTR(jews, 0);
  wsAppendChar(jews, jid_set.jid_del?CBOX_CHECKED:CBOX_UNCHECKED);
  ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,jews,jews->wsbody[0]); //8
  }
  AddEditControlToEditQend(eq,&ec,ma); 
  GRLIST_STRUCT *gr_str=malloc(sizeof(GRLIST_STRUCT));
  patch_input(&jed1_desc);
  patch_header(&jed1_hdr);
  CreateInputTextDialog(&jed1_desc,&jed1_hdr,eq,1,gr_str);
}

//EOL,EOF
