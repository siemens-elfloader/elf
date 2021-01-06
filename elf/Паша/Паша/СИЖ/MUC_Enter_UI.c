#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "jabber_util.h"
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

SOFTKEY_DESC m_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB m_menu_skt=
{
  m_menu_sk,0
};

WSHDR* mews;
char mTerminate=0;

int med1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
  //1: close
  
  // ���� ������ ������ ���� ������ ������, ������� �� �������� � cmd=7
  if(msg->gbsmsg->submess==GREEN_BUTTON || msg->keys==0x18)
  {
    mTerminate = 1;
    return 1;
  }
  
  if (msg->keys==0x0FF0) //����� ���� �����
  {
    return(1);
  }  
  return 0;
}

void med1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  static SOFTKEY_DESC mmmmsk={0x0018, 0x0000,(int)LG_OK};
 
  if (cmd==7)
  {
    //OnRun
    ExtractEditControl(data,2,&ec);    
    wstrcpy(mews,ec.pWS);    
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

  if(mTerminate)
 {
//     char q[10];
//     sprintf(q,"N=%d",cmd);
//     ShowMSG(1,(int)q); 
   mTerminate=0;
   int param_ok=0;      // ���� ������������ ���� ����������
   size_t st_len;
// ��� �����

   st_len = wstrlen(mews)*2;
   char* conf_name;
   if(st_len)
   {
      conf_name =  utf16_to_utf8((char**)mews,&st_len);
      conf_name[st_len]='\0';
      param_ok = 1;
      if(conf_name[0]=='@')
      {
        MsgBoxError(1,(int)LG_NONAMECONF);
        param_ok=0;
      }
   }
   else conf_name = NULL;
   
   char* user_name;
   ExtractEditControl(data,4,&ec);    
   wstrcpy(mews,ec.pWS);
   st_len = wstrlen(mews)*2;
   if(st_len)
   {
      user_name =  utf16_to_utf8((char**)mews,&st_len);
      user_name[st_len]='\0';
   }
   else user_name = NULL;
   
   char* pass_name;
   ExtractEditControl(data,6,&ec);
   wstrcpy(mews,ec.pWS);
   st_len = wstrlen(mews)*2;
   if(st_len)
   {
      pass_name =  utf16_to_utf8((char**)mews,&st_len);
      pass_name[st_len]='\0';
   }
   else pass_name = NULL;

    extern long  strtol (const char *nptr,char **endptr,int base);
    ExtractEditControl(data,8,&ec);    // = n_messages
    wstrcpy(mews,ec.pWS);
    char ss[10];
    ws_2str(mews,ss,15);
    int n_messages = strtol (ss,0,10);
    if(user_name && conf_name && param_ok)
    {
      //ShowMSG(1,(int)user_name);
      //ShowMSG(1,(int)conf_name);
      Enter_Conference(conf_name, user_name, pass_name, n_messages);
      mfree(user_name);
      mfree(pass_name);
      mfree(conf_name);
    }
   }
  
    if(cmd==0x03)     // onDestroy
  {
    FreeWS(mews);
  }
}

extern void dummy(GUI *data);

HEADER_DESC med1_hdr={0,0,131,21,NULL,(int)LG_ENTERMUC,LGP_NULL};

INPUTDIA_DESC med1_desc=
{
  1,
  med1_onkey,
  med1_ghook,
  (void *)dummy,
  0,
  &m_menu_skt,
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

void Disp_MUC_Enter_Dialog()
{
  void *ma=malloc_adr();
  extern const char percent_t[];
  extern const char USERNAME[32];
  extern const char DEFAULT_MUC[64];
  extern const char DEFAULT_MUC_NICK[64];
  extern const unsigned int DEFAULT_MUC_MSGCOUNT;
  
  void *eq;
  EDITCONTROL ec;
  mews=AllocWS(256);
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  wsprintf(mews,percent_t,LG_NAMEMUC);
  ConstructEditControl(&ec,1,0x40,mews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  utf8_2ws(mews, (char*)DEFAULT_MUC, 64);
  ConstructEditControl(&ec,3,0x40,mews,128);      //2
  AddEditControlToEditQend(eq,&ec,ma);  

  wsprintf(mews,percent_t,LG_NICK);
  ConstructEditControl(&ec,1,0x40,mews,256);
  AddEditControlToEditQend(eq,&ec,ma);  

  if(strlen(DEFAULT_MUC_NICK))
  {
    //wsprintf(mews,"%s",DEFAULT_MUC_NICK);
    utf8_2ws(mews, (char*)DEFAULT_MUC_NICK, 64);
  }
  else
  {
    wsprintf(mews,percent_t,USERNAME);
  }
  ConstructEditControl(&ec,3,0x40,mews,80);     // 4
  AddEditControlToEditQend(eq,&ec,ma);  

  wsprintf(mews,percent_t,"Password");
  ConstructEditControl(&ec,1,0x40,mews,256);
  AddEditControlToEditQend(eq,&ec,ma);  

  wsprintf(mews,percent_t,"");
  ConstructEditControl(&ec,3,0x40,mews,80);     // 6
  AddEditControlToEditQend(eq,&ec,ma);  

  wsprintf(mews,percent_t,LG_GETMESSAGECOUNT);
  ConstructEditControl(&ec,1,0x40,mews,256);      
  AddEditControlToEditQend(eq,&ec,ma);  

  wsprintf(mews,"%d",DEFAULT_MUC_MSGCOUNT);
  ConstructEditControl(&ec,5,0x40,mews,2);    //8
  AddEditControlToEditQend(eq,&ec,ma);  
  
  patch_input(&med1_desc);
  patch_header(&med1_hdr);
  CreateInputTextDialog(&med1_desc,&med1_hdr,eq,1,0);
}






