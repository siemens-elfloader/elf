#include "../inc/swilib.h"
#include "main.h"
#include "clist_util.h"
#include "history.h"
#include "message_list.h"
#include "message_cmds.h"
#include "jabber_util.h"
#include "string_util.h"
#include "serial_dbg.h"
#include "lang.h"
#include "../inc/pnglist.h"
#include "smiles.h"
#include "color.h"
#include "rect_patcher.h"

#define MSG_START_X 1    //X-координата начала рисования строки сообщения

int flag2;
int flag1;
extern const unsigned int DEF_SKR;
extern int MESSAGEWIN_FONT;
extern const int pod_mess;
extern int Is_Smiles_Enabled;
extern const int KBD_LAYOUT;

char MsgList_Quit_Required = 0;

TRESOURCE* Resource_Ex = NULL;


int Message_gui_ID;
int edmessage_id;

void CharsToSmiles(WSHDR *ws, const char *s)
{
  S_SMILES *t;
  S_SMILES *t_root=(S_SMILES *)s_top;
  STXT_SMILES *st;
  unsigned int wchar;
  unsigned int ulb=s[0]+(s[1]<<8)+(s[2]<<16)+(s[3]<<24);
  CutWSTR(ws, 0);
  while(wchar=*s)
  {
    t=t_root;
    while(t)
    {
      st=t->lines;
      while(st)
      {
	if ((ulb&st->mask)==st->key)
	{
	  if (!strncmp(s,st->text,strlen(st->text))) goto L1;
	}
	st=st->next;
      }
      t=t->next;
    }
  L1:
    if (t)
    {
      wchar=t->uni_smile;
      s+=strlen(st->text);
      ulb=s[0]+(s[1]<<8)+(s[2]<<16)+(s[3]<<24);
    }
    else
    {
      wchar=char8to16(wchar);
      s++;
      ulb>>=8;
      ulb+=s[3]<<24;
    }
    //if (wchar!=10)
     wsAppendChar(ws,wchar);
  }
  /*int i=ws->wsbody[0];
  while(i>1)
  {
    if (ws->wsbody[i--]!=10) break;
    ws->wsbody[0]=i;
  }*/
}

void SmilesToChars(WSHDR *ws)
{
  S_SMILES *t;
  int c;
  int len=0;
  int scur;
  char * msg_buf=NULL;
  unsigned short *wsbody=ws->wsbody;
  int wslen=wsbody[0];
  if (wslen)
  {
    for (int i=0; i<wslen; i++) // Посчитаем общую длину будущей строки
    {
      c=wsbody[i+1];
      if (c>=0xE100)
      {
        t=FindSmileByUni(c);
        if (t)
        {
          if (t->lines)
          {
            len+=strlen(t->lines->text);
          }
        }
        else  len++;
      }
      else  len++;
    }

    msg_buf = malloc(len+1);
    scur=0;
    for (int wcur=0; wcur<wslen && scur<len; wcur++)
    {
      c=wsbody[wcur+1];
      if (c==10) c=13;
      if (c>=0xE100)
      {
        t=FindSmileByUni(c);
        if (t)
        {
          int w;
          char *s;
          if (t->lines)
          {
            s=t->lines->text;
            while ((w=*s++) && scur<len)
            {
              msg_buf[scur]=w;
              scur++;
            }
          }
        }
        else
        {
          msg_buf[scur]=char16to8(c);
          scur++;
        }
      }
      else
      {
        msg_buf[scur]=char16to8(c);
        scur++;
      }
    }
    msg_buf[scur] = 0;
    ascii2ws(ws, msg_buf);
    mfree(msg_buf);
  }
}

//---------------------------------------------------------------------------
// Test edit dialog
//---------------------------------------------------------------------------


EDITCONTROL ec_message;
GUI *ed_message_gui;

void DispSelectMenu();
char Mess_was_sent = 0;

int inp_onkey(GUI *gui, GUI_MSG *msg)
{
  if(msg->gbsmsg->submess==GREEN_BUTTON)
  {
    extern const char sndMsgSend[];
    EDITCONTROL ec;
    ExtractEditControl(gui, 1, &ec);
    if(ec.pWS->wsbody[0])
    {
      WSHDR * ws = AllocWS(MAX_MSG_LEN);
      wstrcpy(ws, ec.pWS);
      if (Is_Smiles_Enabled && SmilesImgList)
        SmilesToChars(ws);
      int res_len;
      char * body = malloc(MAX_MSG_LEN);
      ws_2utf8(ws, body, &res_len, MAX_MSG_LEN);

      body = realloc(body, res_len + 1);
      body[res_len] = '\0';
      
      char is_gchat = Resource_Ex->entry_type== T_CONF_ROOT ? 1: 0;
      char part_str[]="/part";

      if(!is_gchat)
      {
        CList_AddMessage(Resource_Ex->full_name, MSG_ME, body);
      }
      else
      {
        if(strstr(body, part_str)==body)  // Ключ в начале
        {
          CLIST* room=CList_FindContactByJID(CList_GetActiveContact()->full_name);
          Send_Leave_Conference(room->JID);
          Mess_was_sent = 1;
          mfree(body);
          FreeWS(ws);
          return 0;
        }
      }
      IPC_MESSAGE_S *mess = malloc(sizeof(IPC_MESSAGE_S));
      mess->IsGroupChat = is_gchat;
      mess->body = Mask_Special_Syms(body);
      mfree(body);
      SUBPROC((void*)SendMessage,Resource_Ex->full_name, mess);
      Mess_was_sent = 1;
      SUBPROC((void *)Play, sndMsgSend);
      FreeWS(ws);
      return 1;
    }
    else MsgBoxError(1,(int)LG_NOSENDNULLMESS);
  }

  if (msg->keys==0x18)
  {
    DispSelectMenu();
  }

#ifndef NEWSGOLD
  if (msg->keys==0x0FF0) //Левый софт СГОЛД
  {
    return(1);
  }
#endif

  return(0); //Do standart keys

}

void inp_redraw(void *data)
{
}

void inp_ghook(GUI *gui, int cmd)
{
  static SOFTKEY_DESC sk={0x0018, 0x0000,(int)LG_MENU};
#ifndef NEWSGOLD
  static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LG_CLOSE};
#endif

  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }

  if (cmd == TI_CMD_REDRAW)
  {
    EDITCONTROL ec;
    ExtractEditControl(gui, 1, &ec);
#ifdef NEWSGOLD
    SetSoftKey(gui, &sk,0);
#else
   SetSoftKey(gui, &sk, 1);
   if (ec.pWS->wsbody[0]==0)
      SetSoftKey(gui,&sk_cancel,SET_SOFT_KEY_N==0?1:0);
#endif
  }

  if(cmd == TI_CMD_FOCUS)
  {
    pltop->dyn_pltop=SmilesImgList;
    DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }
  if(cmd == TI_CMD_DESTROY)
  {
    //Send composing CANCELATION
    if(!Mess_was_sent)SUBPROC((void*)CancelComposing,Resource_Ex->full_name);
    Mess_was_sent = 0;
  }
}

void inp_locret(void){}

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

INPUTDIA_DESC inp_desc=
{
  1,
  inp_onkey,
  inp_ghook,
  (void *)inp_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

HEADER_DESC inp_hdr={0,0,0,0,NULL,(int)LG_NEW,LGP_NULL};

// Открыть окно написания нового сообщения

void Init_Message(TRESOURCE* ContEx, char *init_text)
{
  Resource_Ex = ContEx;

  //Send composing
  if((ContEx->entry_type == T_NORMAL)||(ContEx->entry_type == T_CONF_NODE))
  {
    SUBPROC((void*)SendComposing,Resource_Ex->full_name);
  }

  patch_header(&inp_hdr);
  patch_input(&inp_desc);
  WSHDR * ws = AllocWS(MAX_MSG_LEN);
  if(init_text)
  {
    if (Is_Smiles_Enabled && SmilesImgList)
    {
      char * tmp_str = NULL;
      if (tmp_str = convUTF8_to_ANSI_STR(init_text))
      {
        CharsToSmiles(ws, tmp_str);
        mfree(tmp_str);
      }
      else utf8_2ws(ws, init_text, MAX_MSG_LEN);
    }
    else
      utf8_2ws(ws, init_text, MAX_MSG_LEN);
  }
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec, 4, ECF_APPEND_EOL, ws, MAX_MSG_LEN);
  AddEditControlToEditQend(eq,&ec,ma);
  edmessage_id=CreateInputTextDialog(&inp_desc,&inp_hdr,eq,1,0);
  FreeWS(ws);
}
////////////////////////////////////////////////////////////////////////////////
DISP_MESSAGE* MessagesList = NULL;      // Корень списка
unsigned int DispMessList_Count = 0;    // Количество сообщений
unsigned int OLD_MessList_Count = 0;    // Отпарсенное количество сообщений
unsigned int Cursor_Pos = 0;            // Позиция курсора в списке


// Убить список сообщений
void KillDisp(DISP_MESSAGE* messtop)
{
  DISP_MESSAGE* cl=messtop;
  LockSched();
  messtop = NULL;
  int cnt=0;
  while(cl)
  {
    DISP_MESSAGE *p;
    if(cl->mess)FreeWS(cl->mess);
    p=cl;
    cl=cl->next;
    mfree(p);
    cnt++;
  }
  DispMessList_Count = 0;
  OLD_MessList_Count = 0;
  UnlockSched();
}

//===============================================================================================

int CurrentPage=1;
int CurrentMessage = 0;
int CurrentMessage_Lines = 0;
int lines_on_page;
int MaxPages=1;
unsigned short FontSize;
// Обслуживание созданного GUI

// Всякие посторонние расчёты :)
void Calc_Pages_Data()
{
  MaxPages = sdiv(lines_on_page,DispMessList_Count);
  if(lines_on_page*MaxPages<DispMessList_Count)MaxPages++;
}

// Всякие посторонние расчёты :)
void Calc_Pages_Data_1()
{
  if((Cursor_Pos-1-(CurrentMessage_Lines)<=(CurrentPage-1)*lines_on_page) && CurrentPage>1)
  {
    CurrentPage--;
    //Cursor_Pos--;
    //ShowMSG(1,(int)"Q");
    
  }
  else
  {
    //char q[20];
    //sprintf(q,"Cur=%d > %d", Cursor_Pos-1-(CurrentMessage_Lines), (CurrentPage-1)*lines_on_page);
    //ShowMSG(1,(int)q);
  }
}


void Calc_Pages_Data_2()
{
  if(Cursor_Pos+1>CurrentPage*lines_on_page)
  {
    CurrentPage++;
    //Cursor_Pos++;
  }
}

void mGUI_onRedraw(GUI *data)
{
  if(Resource_Ex->total_msg_count!=OLD_MessList_Count)
  {
    //KillDisp(MessagesList);
    ParseMessagesIntoList(Resource_Ex);
    OLD_MessList_Count = Resource_Ex->total_msg_count;
  }
  // Расчёт количества строк на одной странице
  Calc_Pages_Data();
  // Заголовок окна
  DrawRectangle(0,SCR_START,ScreenW()-1,SCR_START+FontSize*2+1,0,
                   0, color(MESSAGEWIN_TITLE_BGCOLOR));

  DrawRectangle(0,SCR_START+FontSize+2,ScreenW()-1,ScreenH()-1,0,
                   0, color(MESSAGEWIN_BGCOLOR));

  // Делаем типо название окошка... :)
  WSHDR* ws_title = AllocWS(256);
  utf8_2ws(ws_title, Resource_Ex->full_name, 256);

  DrawString(ws_title,1,SCR_START+1,ScreenW()-1,SCR_START+FontSize+1,MESSAGEWIN_FONT,0,color(MESSAGEWIN_TITLE_FONT),0);

  DISP_MESSAGE * ml = MessagesList;
  int i_ctrl=1;
  int kur = 0;
  RGBA MsgBgColor;
  RGBA MsgBg2Color;
  CurrentMessage_Lines = 0;
  int Y_pos = NULL; // Стартовая позиция текущей строки
  while(ml)
  {
    if((i_ctrl>(CurrentPage-1)*lines_on_page) && (i_ctrl<=CurrentPage*lines_on_page))
    {
      switch(ml->mtype)
      {
      case MSG_ME:      MsgBgColor=MESSAGEWIN_MY_BGCOLOR; break;
      case MSG_CHAT:    MsgBgColor=MESSAGEWIN_CH_BGCOLOR;break;
      case MSG_SYSTEM:  MsgBgColor=MESSAGEWIN_SYS_BGCOLOR;break;
      case MSG_STATUS:  MsgBgColor=MESSAGEWIN_STATUS_BGCOLOR;break;
      case MSG_GCHAT:   MsgBgColor=ml->log_mess_number %2==0? MESSAGEWIN_GCHAT_BGCOLOR_1 : MESSAGEWIN_GCHAT_BGCOLOR_2; break;
      }
      MsgBg2Color=MsgBgColor;
      
      if(CurrentMessage == ml->log_mess_number)
      {
        Cursor_Pos = i_ctrl;
        kur = 1;
      }
      
      if(Cursor_Pos == i_ctrl)
      {
        MsgBgColor = MESSAGEWIN_CURSOR_BGCOLOR;
        
        if(pod_mess)
          MsgBg2Color= CURSOR_BORDER;
        else
          MsgBg2Color=MESSAGEWIN_CURSOR_BGCOLOR;
        
        DISP_MESSAGE *mln = ml->next;
        if(mln)
          if(CurrentMessage==mln->log_mess_number) Cursor_Pos++;  // Обновляем позицию курсора
        CurrentMessage_Lines++;
      }
      
      DrawRectangle(0, SCR_START + FontSize + 2 + Y_pos, ScreenW() - 1, SCR_START + FontSize + 2 + ml->line_height + Y_pos - kur, 0,
                       color(MsgBg2Color), color(MsgBgColor));

      DrawString(ml->mess, MSG_START_X, SCR_START + FontSize + 2 + Y_pos, ScreenW()-1, SCR_START + FontSize + 2 + ml->line_height + Y_pos, MESSAGEWIN_FONT, 0,
                 color(MESSAGEWIN_CHAT_FONT), 0);

      Y_pos += ml->line_height;
    }
    ml = ml->next;
    i_ctrl++;
  }
  FreeWS(ws_title);
  Resource_Ex->has_unread_msg =0; // Непрочитанных сообщений больше нет
}

void mGUI_onCreate(GUI *data, void *(*malloc_adr)(int))
{
  data->state=1;
  MsgList_Quit_Required=0;
}

void mGUI_onClose(GUI *data, void (*mfree_adr)(void *))
{
  if (Is_Smiles_Enabled && SmilesImgList)
  {
    PNGTOP_DESC * pltop = PNG_TOP();
    pltop->dyn_pltop = NULL;
  }
  KillDisp(MessagesList);
  data->state=0;
}

void mGUI_onFocus(GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  if (Is_Smiles_Enabled && SmilesImgList)
  {
    PNGTOP_DESC * pltop = PNG_TOP();
    pltop->dyn_pltop = SmilesImgList;
  }
  DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  data->state=2;
  REDRAW();
}

void mGUI_onUnfocus(GUI *data, void (*mfree_adr)(void *))
{
  if (data->state!=2) return;
  data->state=1;
}

LOG_MESSAGE *GetCurMessage()
{
  unsigned int i=0;
  LOG_MESSAGE* log =Resource_Ex->log;
  while(log)
  {
    i++;
    if(i==CurrentMessage)break;
    log = log->next;
  }
  return log;
}

int mGUI_onKey(GUI *data, GUI_MSG *msg)
{
  if(MsgList_Quit_Required)
    return 1; //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI

  if (KBD_LAYOUT)
  {
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
      switch(msg->gbsmsg->submess)
      {
      case '0':
        // Убить список сообщений
        KillMsgList(Resource_Ex->log);
        Resource_Ex->log = NULL;
        Resource_Ex->has_unread_msg=0;
        Resource_Ex->total_msg_count=0;
        return 1;
        
#ifndef NEWSGOLD
      case RED_BUTTON:
#endif
      case RIGHT_SOFT:
        return 1;

      case LEFT_SOFT:
          break;

      case '5':
      case ENTER_BUTTON:
        {
          LOG_MESSAGE* log =GetCurMessage();
          if(log)
          {
            char *s=log->mess;
            unsigned int l = strlen(s);
            char *init_text = malloc(l+3+1);
            zeromem(init_text,l+3+1);
            init_text[0] = '>';
            init_text[1] = '>';
            strcat(init_text, s);
            init_text[2+ l] = '\n';
            init_text[3+ l] = '\0';
            Init_Message(Resource_Ex, init_text);
            mfree(init_text);
          }
        }
        break;
        
      case '2':
      case UP_BUTTON:
        Calc_Pages_Data_1();
        CurrentMessage_Lines = 0;
        if (Cursor_Pos > 1) Cursor_Pos --;
        if (CurrentMessage > 1) CurrentMessage --;
        REDRAW();
        break;

      case LEFT_BUTTON: //страница вверх
        {
          if (CurrentPage>1)
          {
            int cp=CurrentPage;
            for(;;)
            {
              CurrentMessage_Lines = 0;
              Cursor_Pos--;
              CurrentMessage--;
              Calc_Pages_Data_1();
              if (CurrentPage+1==cp || CurrentPage<1)
                break;
            }
          }
          Cursor_Pos=DispMessList_Count;
          REDRAW();
        }
        break;
        
      case '8':
      case DOWN_BUTTON:
        CurrentMessage_Lines = 0;
        if (Cursor_Pos < DispMessList_Count)
          Cursor_Pos ++;
        if (CurrentMessage < Resource_Ex->total_msg_count)
          CurrentMessage ++;
        Calc_Pages_Data_2();
        REDRAW();
        break;

      case RIGHT_BUTTON:
        {
          if (CurrentPage<MaxPages)
          {
            int cp=CurrentPage;
            for(;;)
            {
              CurrentMessage_Lines = 0;
              Cursor_Pos++;
              CurrentMessage++;
              Calc_Pages_Data_2();
              if (CurrentPage-1==cp || CurrentPage>=MaxPages)
                break;
            }
          }
          REDRAW();
        }
        break;
        
      case '1': // в начало списка сообщений
        CurrentMessage_Lines = 0;
        Cursor_Pos=1;
        CurrentMessage=1;
        CurrentPage=1;
        REDRAW();
        break;

      case '9': // в конец списка сообщений
        CurrentMessage_Lines = 0;
        Cursor_Pos=DispMessList_Count;
        CurrentMessage=Resource_Ex->total_msg_count;
        CurrentPage=MaxPages;
        REDRAW();
        break;

      case '#':
        {
          LOG_MESSAGE *msg = GetCurMessage();
          if(msg)
          {
            if(msg->mtype==MSG_GCHAT)
            {
              unsigned int au_nick_len = strlen(msg->muc_author);
              char *init_text = malloc(au_nick_len+3);
              zeromem(init_text, au_nick_len+3);
              strcpy(init_text, msg->muc_author);
              init_text[au_nick_len]=':';
              init_text[au_nick_len+1]=' ';
              init_text[au_nick_len+2]='\0';
              Init_Message(Resource_Ex, init_text);
              mfree(init_text);
            }
          }
        }
        break;
        
      case GREEN_BUTTON:
        Init_Message(Resource_Ex, NULL);
        break;
      }
    }
  }
  else
  {
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
      switch(msg->gbsmsg->submess)
      {
      case '0':
        KillMsgList(Resource_Ex->log);
        Resource_Ex->log = NULL;
        Resource_Ex->has_unread_msg=0;
        Resource_Ex->total_msg_count=0;
        return 1;

#ifndef NEWSGOLD
      case RED_BUTTON:
#endif
      case RIGHT_SOFT:
        return 1;

      case LEFT_SOFT:
        break;
        
      case '5':
      case ENTER_BUTTON:
        {
          LOG_MESSAGE* log =GetCurMessage();
          if(log)
          {
            char *s=log->mess;
            unsigned int l = strlen(s);
            char *init_text = malloc(l+3+1);
            zeromem(init_text,l+3+1);
            init_text[0] = '>';
            init_text[1] = '>';
            strcat(init_text, s);
            init_text[2+ l] = '\n';
            init_text[3+ l] = '\0';
            Init_Message(Resource_Ex, init_text);
            mfree(init_text);
          }
        }
        break;
        
      case '2':
      case UP_BUTTON:
        Calc_Pages_Data_1();
        CurrentMessage_Lines = 0;
        if (Cursor_Pos > 1) Cursor_Pos --;
        if (CurrentMessage > 1) CurrentMessage --;
        REDRAW();
        break;
        
      case '4': //страница вверх
        {
          if (CurrentPage>1)
          {
            int cp=CurrentPage;
            for(;;)
            {
              CurrentMessage_Lines = 0;
              Cursor_Pos--;
              CurrentMessage--;
              Calc_Pages_Data_1();
              if (CurrentPage+1==cp || CurrentPage<1)
                break;
            }
          }
          Cursor_Pos=DispMessList_Count;
          REDRAW();
        }
        break;
        
      case '8':
      case DOWN_BUTTON:
        CurrentMessage_Lines = 0;
        if (Cursor_Pos < DispMessList_Count) Cursor_Pos ++;
        if (CurrentMessage < Resource_Ex->total_msg_count) CurrentMessage ++;
        Calc_Pages_Data_2();
        REDRAW();
        break;

      case '6':
        {
          if (CurrentPage<MaxPages)
          {
            int cp=CurrentPage;
            for(;;)
            {
              CurrentMessage_Lines = 0;
              Cursor_Pos++;
              CurrentMessage++;
              Calc_Pages_Data_2();
              if (CurrentPage-1==cp || CurrentPage>=MaxPages)
                break;
            }
          }
          REDRAW();
        }
        break;
        
      case '1'://в начало списка сообщений
        CurrentMessage_Lines = 0;
        Cursor_Pos=1;
        CurrentMessage=1;
        CurrentPage=1;
        REDRAW();
        break;

      case '9'://в конец списка сообщений
        CurrentMessage_Lines = 0;
        Cursor_Pos=DispMessList_Count;
        CurrentMessage=Resource_Ex->total_msg_count;
        CurrentPage=MaxPages;
        REDRAW();
        break;

      case RIGHT_BUTTON:
        {
          LOG_MESSAGE *msg = GetCurMessage();
          if(msg)
            if(msg->mtype==MSG_GCHAT)
            {
              unsigned int au_nick_len = strlen(msg->muc_author);
              char *init_text = malloc(au_nick_len+3);
              zeromem(init_text, au_nick_len+3);
              strcpy(init_text, msg->muc_author);
              init_text[au_nick_len]=':';
              init_text[au_nick_len+1]=' ';
              init_text[au_nick_len+2]='\0';
              Init_Message(Resource_Ex, init_text);
              mfree(init_text);
            }
        }
        break;
        
      case GREEN_BUTTON:
        Init_Message(Resource_Ex, NULL);
        break;
      }
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch (msg->gbsmsg->submess)
    {
    case '2':
    case UP_BUTTON:
      Calc_Pages_Data_1();
      CurrentMessage_Lines = 0;
      if (Cursor_Pos > 1) Cursor_Pos --;
      if (CurrentMessage > 1) CurrentMessage --;
      REDRAW();
      break;
      
    case '8':
    case DOWN_BUTTON:
      CurrentMessage_Lines = 0;
      if (Cursor_Pos < DispMessList_Count) Cursor_Pos++;
      if (CurrentMessage < Resource_Ex->total_msg_count) CurrentMessage++;
      Calc_Pages_Data_2();
      REDRAW();
      break;
    }
  }
  return(0);
}


extern void kill_data(void *p, void (*func_p)(void *));

// ГУЙ
int mGUI_method8(void){return(0);}

int mGUI_method9(void){return(0);}

const void * const mgui_methods[11]={
  (void *)mGUI_onRedraw,  //Redraw
  (void *)mGUI_onCreate,  //Create
  (void *)mGUI_onClose,   //Close
  (void *)mGUI_onFocus,   //Focus
  (void *)mGUI_onUnfocus, //Unfocus
  (void *)mGUI_onKey,     //OnKey
  0,
  (void *)kill_data,      //onDestroy
  (void *)mGUI_method8,
  (void *)mGUI_method9,
  0
};

const RECT mCanvas={0,0,0,0};

// Получить связанную структуру DISP_MESSAGE для отображения на экране
void ParseMessagesIntoList(TRESOURCE* ContEx)
{
  if(!ContEx)return;
  int parsed_counter = 0; // Сколько уже было обработано (=OLD_MessList_Count)
  LOG_MESSAGE* MessEx= ContEx->log;
  int cnt=0;

  // В какую область уложить строку (слева без MSG_START_X, справа без одного пикселя)
  int screen_width = ScreenW() - MSG_START_X - 1 ;

  int line_width = 0; // Ширина текущей строки в пикселях
  int line_height = GetFontYSIZE(MESSAGEWIN_FONT); // Высота текущей строки. Подгоняется под размер смайлов
  int symbol_width = 0;  // Ширина текущего символа в пикселях
  //  int chars;
  DISP_MESSAGE* Disp_Mess_Ex, *tmp;
  if(!MessEx)return;
  LockSched();

  WSHDR *temp_ws_1=NULL;
  WSHDR *temp_ws_2=NULL;

  // Цикл по всем сообщениям
  while(MessEx)
  {
    if(parsed_counter>=OLD_MessList_Count)
    {
      temp_ws_1 = AllocWS(strlen(MessEx->mess)*2);
      if (Is_Smiles_Enabled && SmilesImgList)
      {
        char * tmp_str = NULL;
        if (tmp_str = convUTF8_to_ANSI_STR(MessEx->mess))
        {
          CharsToSmiles(temp_ws_1, tmp_str); // Добавляем иконки смайлов в сообщение
          mfree(tmp_str);
        }
        else utf8_2ws(temp_ws_1, MessEx->mess, strlen(MessEx->mess)*2);
      }
      else
        utf8_2ws(temp_ws_1, MessEx->mess, strlen(MessEx->mess)*2);

      //temp_ws_2 = AllocWS(CHAR_ON_LINE*2); WTF?
      temp_ws_2 = AllocWS(200); //ИМХО, так лучше

      //char q[40];
      //sprintf(q,"UTF_len=%d, WSTR_len=%d", strlen(MessEx->mess),l);
      //ShowMSG(2,(int)q);

      cnt=0;
      for(int i = 1; i <= temp_ws_1->wsbody[0]; i++)
      {
        unsigned int symb = temp_ws_1->wsbody[i];
        if ((symb==0x000A) || (symb==0x000D) || (symb==0x00A0)) //Перевод строки
	{
	L_ADD:
          Disp_Mess_Ex = malloc(sizeof(DISP_MESSAGE));
          Disp_Mess_Ex->mess = AllocWS(cnt);
          wstrcpy(Disp_Mess_Ex->mess, temp_ws_2);
          CutWSTR(temp_ws_2, 0);
          Disp_Mess_Ex->mtype = MessEx->mtype;
          Disp_Mess_Ex->log_mess_number = parsed_counter+1;
          Disp_Mess_Ex->line_height = line_height;
          if(!MessagesList)
          {
            MessagesList = Disp_Mess_Ex;
            Disp_Mess_Ex->next=NULL;
          }
          else
          {
            tmp= MessagesList;
            while(tmp->next)
            {
              tmp = tmp->next;
            }
            tmp->next = Disp_Mess_Ex;
            Disp_Mess_Ex->next=NULL;
          }
          cnt=0;
          DispMessList_Count++;
          line_width = 0;
          line_height = GetFontYSIZE(MESSAGEWIN_FONT);
	}
	else
	{
          symbol_width = GetSymbolWidth(symb,MESSAGEWIN_FONT);
	  line_width += symbol_width;
	  if (line_width > screen_width)
	  {
	    i--; //Повторить с текущим символом, сейчас не лезет
	    goto L_ADD; //Добавить строку
	  }

          if (Is_Smiles_Enabled && SmilesImgList)
          {
            if (symb >= FIRST_UCS2_BITMAP && symb <= FIRST_UCS2_BITMAP + smiles_loaded) // Если код смайла
              if (line_height < symbol_width) // Будем надеяться, что смайлы квадратные ;)
                line_height = symbol_width; // Подгоняем высоту строки под размер смайла
          }
	  wsAppendChar(temp_ws_2, symb);
	  cnt ++;
	  if (i == temp_ws_1->wsbody[0]) goto L_ADD; //Последний символ, добавить и слинять ;)
	  if (line_width == screen_width) goto L_ADD; //Ровненько легли в строку, тоже добавить
	}
      }
      FreeWS(temp_ws_1);
      FreeWS(temp_ws_2);
    }
    MessEx = MessEx->next;
    parsed_counter++;
  }
  UnlockSched();
}


// Отобразить список сообщений
void Display_Message_List(TRESOURCE* ContEx)
{
  if(!ContEx)return;
  // Инициализация
  if (Is_Smiles_Enabled && SmilesImgList)
  {
    /* The_ZeN: Это надо сделать обязательно до вызова парсера мессаг!
       Иначе будет брать размер смайлов из фула */
    PNGTOP_DESC * pltop = PNG_TOP();
    pltop->dyn_pltop = SmilesImgList; 
  }
  OLD_MessList_Count = 0;
  MessagesList = NULL;
  DispMessList_Count = 0;
  Resource_Ex = ContEx;
  FontSize = GetFontYSIZE(MESSAGEWIN_FONT);
  lines_on_page = sdiv(FontSize, ScreenH() - HIST_DISP_OFS - YDISP);
  ParseMessagesIntoList(Resource_Ex);
  Calc_Pages_Data();
  CurrentPage = MaxPages;
  OLD_MessList_Count = Resource_Ex->total_msg_count;
  Cursor_Pos = DispMessList_Count;
  CurrentMessage = OLD_MessList_Count;

  // Замутим гуй
  GUI *mess_gui=malloc(sizeof(GUI));
  zeromem(mess_gui, sizeof(GUI));
  patch_rect((RECT*)&mCanvas,0,0,ScreenW()-1,ScreenH()-1);
  mess_gui->canvas=(void *)(&mCanvas);
  mess_gui->flag30=2;
  mess_gui->methods=(void *)mgui_methods;
  mess_gui->item_ll.data_mfree=(void (*)(void *))mfree_adr();
  Message_gui_ID = CreateGUI(mess_gui);
}
//EOL,EOF
