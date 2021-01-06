#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "jabber_util.h"
#include "groups_util.h"
#include "JID_Enter_UI.h"
#include "lang.h"
#include "rect_patcher.h"

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
  
  // §¦§ã§Ý§Ú §Ù§Ö§Ý§×§ß§Ñ§ñ §Ü§ß§à§á§Ü§Ñ §Ý§Ú§Ò§à §ß§Ñ§Ø§Ñ§ä§Ñ §Ü§ß§à§á§Ü§Ñ, §Ü§à§ä§à§â§å§ð §Þ§í §á§à§Ó§Ö§ã§Ú§Ý§Ú §Ó cmd=7
  if(msg->gbsmsg->submess==GREEN_BUTTON || msg->keys==0x18)
  {
    jTerminate = 1;
    return 1;
  }
  
  if (msg->keys==0x0FF0) //§­§Ö§Ó§í§Û §ã§à§æ§ä §³§¤§°§­§¥
  {
    return(1);
  }
if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (msg->gbsmsg->submess==ENTER_BUTTON)
    {
      if (EDIT_GetFocus(data)==8)
      {
    jid_set.jid_ask=!jid_set.jid_ask;  //8 §á§å§ß§Ü§ä §á§â§Ú §Õ§à§Ò§Ñ§Ó§Ý§Ö§ß§Ú§Ú §Ü§à§ß§ä§Ñ§Ü§ä§Ñ "§©§Ñ§á§â§à§ã §Ñ§Ó§ä§à§â§Ú§Ù§Ñ§è§Ú§Ú",
    jid_set.jid_del=!jid_set.jid_del;  // §Ñ §á§â§Ú §å§Õ§Ñ§Ý§Ö§ß§Ú§Ú "§µ§Õ§Ñ§Ý§Ú§ä§î"
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
  
  if(cmd==0x0A)   // §¶§à§Ü§å§ã§Ú§â§à§Ó§Ñ§ß§Ú§Ö
  {
     DisableIDLETMR();   // §°§ä§Ü§Ý§ð§é§Ñ§Ö§Þ §ä§Ñ§Û§Þ§Ö§â §Ó§í§ç§à§Õ§Ñ §á§à §ä§Ñ§Û§Þ§Ñ§å§ä§å
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
      Send_ShortPresence(jid_jid,8);//§á§à§ã§í§Ý§Ñ§Ö§Þ §Ù§Ñ§á§â§à§ã §Ñ§Ó§ä§à§â§Ú§Ù§Ñ§è§Ú§Ú
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


HEADER_DESC jed1_hdr={0,0,131,21,NULL,(int)"ÁªÏµÈË",LGP_NULL};

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

//  0x00000001 - §£§í§â§à§Ó§ß§ñ§ä§î §á§à §á§â§Ñ§Ó§à§Þ§å §Ü§â§Ñ§ð
//  0x00000002 - §£§í§â§à§Ó§ß§ñ§ä§î §á§à §è§Ö§ß§ä§â§å
//  0x00000004 - §ª§ß§Ó§Ö§â§ã§Ú§ñ §Ù§ß§Ñ§Ü§à§Þ§Ö§ã§ä
//  0x00000008 - UnderLine
//  0x00000020 - §¯§Ö §á§Ö§â§Ö§ß§à§ã§Ú§ä§î §ã§Ý§à§Ó§Ñ
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - §¯§Ö §Õ§Ó§Ú§Ô§Ñ§Ö§ä§ã§ñ §Ü§å§â§ã§à§â
//  0x40000000 - §±§à§Þ§Ö§ß§ñ§ä§î §Þ§Ö§ã§ä§Ñ§Þ§Ú §ã§à§æ§ä-§Ü§ß§à§á§Ü§Ú
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
  if(jid_set.jid_add)ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,128);//2 §Ö§ã§Ý§Ú §Þ§Ö§ß§ñ§Ö§Þ §Ü§à§ß§ä§Ñ§Ü§ä §¨§ª§¥ §ß§Ö§Õ§Ñ§Ö§Þ §Ú§Ù§Þ§Ö§ß§Ú§ä§î
   else ConstructEditControl(&ec,4,ECF_APPEND_EOL,jews,128);//2
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  ascii2ws(jews, LG_NICK);
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  utf8_2ws(jews, name, 64);
  ConstructEditControl(&ec,4,ECF_APPEND_EOL,jews,80);     // 4
  AddEditControlToEditQend(eq,&ec,ma);  
  
  PrepareEditControl(&ec);
  ascii2ws(jews, LG_JEGROUP);
  ConstructEditControl(&ec,1,ECF_APPEND_EOL,jews,256);      
  AddEditControlToEditQend(eq,&ec,ma);  

  PrepareEditControl(&ec);
  utf8_2ws(jews, group, 64);
  ConstructEditControl(&ec,4,ECF_APPEND_EOL,jews,80);    //6
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
  
  patch_input(&jed1_desc);
  patch_header(&jed1_hdr);
  CreateInputTextDialog(&jed1_desc,&jed1_hdr,eq,1,0);
}
