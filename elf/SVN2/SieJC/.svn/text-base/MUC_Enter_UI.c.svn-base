#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "jabber_util.h"
#include "lang.h"
#include "rect_patcher.h"

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

int med1_onkey(GUI *data, GUI_MSG *msg)
{
  // Если зелёная кнопка либо нажата кнопка, которую мы повесили в cmd=7
  if(msg->gbsmsg->submess==GREEN_BUTTON || msg->keys==0x18)
  {
    EDITCONTROL ec;
    int utf8_len = NULL;
    char * conf_name = NULL;
    char * user_name = NULL;
    char * pass_name = NULL;
    // Конференция
    ExtractEditControl(data, 2, &ec);
    if(ec.pWS->wsbody[0])
    {
      
      conf_name = malloc(ec.pWS->wsbody[0] * 2 + 1);
      ws_2utf8(ec.pWS, conf_name, &utf8_len, ec.pWS->wsbody[0] * 2 + 1);
      conf_name = realloc(conf_name, utf8_len + 1);
      conf_name[utf8_len]='\0';
      if(conf_name[0]=='@')
      {
        mfree(conf_name);
        MsgBoxError(1,(int)LG_NONAMECONF);
        return 0;
      }
    }
    // Ник
    ExtractEditControl(data, 4, &ec);    
    if(ec.pWS->wsbody[0])
    {
      user_name = malloc(ec.pWS->wsbody[0] * 2 + 1);
      ws_2utf8(ec.pWS, user_name, &utf8_len, ec.pWS->wsbody[0] * 2 + 1);
      user_name = realloc(user_name, utf8_len + 1);
      user_name[utf8_len]='\0';
    }
    // Пароль
    ExtractEditControl(data, 6, &ec);    
    if(ec.pWS->wsbody[0])
    {
      pass_name = malloc(ec.pWS->wsbody[0] * 2 + 1);
      ws_2utf8(ec.pWS, pass_name, &utf8_len, ec.pWS->wsbody[0] * 2 + 1);
      pass_name = realloc(pass_name, utf8_len + 1);
      pass_name[utf8_len]='\0';
    }
    // Число сообщений
    ExtractEditControl(data, 8, &ec);
    char ss[10];
    extern const char percent_d[];
    ws_2str(ec.pWS, ss, 15);
    int n_messages=0;
    sscanf(ss,percent_d, &n_messages);
    
    if(user_name && conf_name) Enter_Conference(conf_name, user_name, pass_name, n_messages);
    if(user_name) mfree(user_name);
    if(pass_name) mfree(pass_name);
    if(conf_name) mfree(conf_name);
    return 1;
  }
  if (msg->keys==0x0FF0) //Левый софт СГОЛД
  {
    return(1);
  }  
  return 0;
}

void med1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  static SOFTKEY_DESC mmmmsk={0x0018, 0x0000,(int)LG_ENTER};
 
  if (cmd == TI_CMD_REDRAW)
  {
    //OnRun
    ExtractEditControl(data,2,&ec);   
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
  
  if(cmd == TI_CMD_FOCUS)   // Фокусирование
  {
     DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }
}


HEADER_DESC med1_hdr={0,0,131,21,NULL,(int)LG_ENTERMUC,LGP_NULL};

void med1_locret(void){}

INPUTDIA_DESC med1_desc=
{
  1,
  med1_onkey,
  med1_ghook,
  (void *)med1_locret,
  0,
  &m_menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void Disp_MUC_Enter_Dialog(char* muc, char* nick, char* pass)
{
  extern const char USERNAME[32];
  extern const char DEFAULT_MUC[64];
  extern const char DEFAULT_MUC_NICK[64];
  extern const unsigned int DEFAULT_MUC_MSGCOUNT;
  
  EDITCONTROL ec;
  void * ma = malloc_adr();
  void * eq = AllocEQueue(ma,mfree_adr());
  WSHDR * ws = AllocWS(256);
  
  PrepareEditControl(&ec);
  
  ascii2ws(ws, LG_NAMEMUC);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);
 
  if (muc) utf8_2ws(ws, muc, 128);
    else utf8_2ws(ws, (char*)DEFAULT_MUC, 128);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 128);      //2
  AddEditControlToEditQend(eq,&ec,ma);  

  ascii2ws(ws, LG_NICK);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);  
  if(nick) utf8_2ws(ws, nick, 80);
  else
  {
   if(strlen(DEFAULT_MUC_NICK)) utf8_2ws(ws, (char*)DEFAULT_MUC_NICK, 80);
   else utf8_2ws(ws, (char*)USERNAME, 80);
  }
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 80);     // 4
  AddEditControlToEditQend(eq,&ec,ma);  

  ascii2ws(ws, LG_PASSWORD);
  ConstructEditControl(&ec, ECT_HEADER,ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);  
  if(pass) utf8_2ws(ws, pass, 80);
    else ascii2ws(ws, "");
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 80);     // 6
  AddEditControlToEditQend(eq,&ec,ma);  

  ascii2ws(ws, LG_GETMESSAGECOUNT);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);      
  AddEditControlToEditQend(eq,&ec,ma);  

  wsprintf(ws, "%d", DEFAULT_MUC_MSGCOUNT);
  ConstructEditControl(&ec,5,ECF_APPEND_EOL, ws, 2);    //8
  AddEditControlToEditQend(eq,&ec,ma);  
  
  FreeWS(ws);
  patch_input(&med1_desc);
  patch_header(&med1_hdr);
  CreateInputTextDialog(&med1_desc, &med1_hdr,eq, 1, 0);
}

//EOL,EOF
