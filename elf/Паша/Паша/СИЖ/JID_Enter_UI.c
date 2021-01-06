#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "jabber_util.h"
#include "groups_util.h"
#include "JID_Enter_UI.h"
#include "lang.h"
//===============================================================================================
// ELKA Compatibility
#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}
//===============================================================================================

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
    }
  }
  return 0;
}

void jed1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  static SOFTKEY_DESC mmmmsk={0x0018, 0x0000,(int)LG_OK};
 
  if (cmd==7)
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
  
  if(cmd==0x0A)   // �������������
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
  char answer[400];
  char* di = "roster3";
  if((jid_set.jid_del)&&(jid_set.jid_add))
  {
     sprintf(answer, "<item jid='%s' subscription='remove'/>", Mask_Special_Syms(jid_jid));
  }
  else
  {
    sprintf(answer, "<item jid='%s'", Mask_Special_Syms(jid_jid));
    if(jid_name)
      {
      sprintf(answer,"%s name='%s'",answer, Mask_Special_Syms(jid_name));
      }
    if(jid_group)
    {
      sprintf(answer,"%s><group>%s</group></item>",answer, Mask_Special_Syms(jid_group));
    }
    else 
    {
      strcat(answer,"/>");
    }
  }

  SendIq(NULL, IQTYPE_SET, di, IQ_ROSTER, answer);
  if(!jid_set.jid_add)
  {
    if(jid_set.jid_ask)
    {
      Send_ShortPresence(jid_jid,8);//�������� ������ �����������
    }
  }
      if(jid_name) mfree(jid_name);
      if(jid_jid) mfree(jid_jid);
      if(jid_group) mfree(jid_group);
 } else ShowMSG(1,(int)LG_JENOJID);
 //end if(jid_jid)
 }

  if(cmd==0x03)     // onDestroy
  {
    FreeWS(jews);
  }
}

extern void dummy(GUI *data);

HEADER_DESC jed1_hdr={0,0,131,21,NULL,(int)"�������",LGP_NULL};

INPUTDIA_DESC jed1_desc=
{
  1,
  jed1_onkey,
  jed1_ghook,
  (void *)dummy,
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
  group = GetGroupNameByID(ClEx->group);
  }
  else
  {
  jid_set.jid_add=NULL;    
  }
  
  void *ma=malloc_adr();
  extern const char percent_t[];

  void *eq;
  EDITCONTROL ec;
  jews=AllocWS(256);
  eq=AllocEQueue(ma,mfree_adr());
  
  PrepareEditControl(&ec);
  wsprintf(jews,percent_t,"JID:");
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  PrepareEditControl(&ec);
  utf8_2ws(jews, jid, 64);
  if(jid_set.jid_add)ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,128);//2 ���� ������ ������� ��� ������ ��������
   else ConstructEditControl(&ec,3,ECF_APPEND_EOL,jews,128);//2
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  wsprintf(jews,percent_t,LG_NICK);
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  utf8_2ws(jews, name, 64);
  ConstructEditControl(&ec,3,ECF_APPEND_EOL,jews,80);     // 4
  AddEditControlToEditQend(eq,&ec,ma);  
  
  PrepareEditControl(&ec);
  wsprintf(jews,percent_t,LG_JEGROUP);
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);      
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  utf8_2ws(jews, group, 64);
  ConstructEditControl(&ec,3,ECF_APPEND_EOL,jews,80);    //6
  AddEditControlToEditQend(eq,&ec,ma);

  PrepareEditControl(&ec);
  if (!jid_set.jid_add)
    {
    wsprintf(jews,percent_t,LG_JEASK);
    ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);      
    AddEditControlToEditQend(eq,&ec,ma);

  PrepareEditControl(&ec);
  CutWSTR(jews, 0);
  wsAppendChar(jews, jid_set.jid_ask?CBOX_CHECKED:CBOX_UNCHECKED);
  ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,jews,jews->wsbody[0]); //8
    }
  else
  {
    wsprintf(jews,percent_t,LG_JEDELCONTACT);
    ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);      
    AddEditControlToEditQend(eq,&ec,ma);

  PrepareEditControl(&ec);
  CutWSTR(jews, 0);
  wsAppendChar(jews, jid_set.jid_del?CBOX_CHECKED:CBOX_UNCHECKED);
  ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,jews,jews->wsbody[0]); //8
  }
  AddEditControlToEditQend(eq,&ec,ma); 
  
  patch_input(&jed1_desc);
  patch_header(&jed1_hdr);
  CreateInputTextDialog(&jed1_desc,&jed1_hdr,eq,1,0);
}
