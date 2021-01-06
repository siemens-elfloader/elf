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

#define MSG_START_X 1    //X-координата начала рисования строки сообщения

int flag2;int flag1;
//-------------Цвета. Много цветов :)
extern const unsigned int DEF_SKR;
extern RGBA MESSAGEWIN_BGCOLOR ; // Общий фон
extern RGBA MESSAGEWIN_TITLE_BGCOLOR ; // Фон заголовка
extern RGBA MESSAGEWIN_TITLE_FONT ; // Цвет шрифта заголовка
extern RGBA MESSAGEWIN_MY_BGCOLOR ; // Цвет фона исходящих сообщений
extern RGBA MESSAGEWIN_CH_BGCOLOR ; // Цвет фона приватных сообщений
extern RGBA MESSAGEWIN_CURSOR_BGCOLOR; // Цвет фона курсора
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_1 ; // Чередование: Цвет фона сообщений конференции 1
extern RGBA MESSAGEWIN_GCHAT_BGCOLOR_2 ; // Чередование: Цвет фона сообщений конференции 2
extern RGBA MESSAGEWIN_SYS_BGCOLOR ; // Цвет фона сообщений уведомлений
extern RGBA MESSAGEWIN_STATUS_BGCOLOR; // Цвет фона сообщений смены статуса
extern RGBA MESSAGEWIN_CHAT_FONT; // Цвет шрифта сообщений
extern int MESSAGEWIN_FONT;
extern RGBA CURSOR_BORDER;
extern const int pod_mess;
//------------------

extern const int KBD_LAYOUT;

char MsgList_Quit_Required = 0;

TRESOURCE* Resource_Ex = NULL;


int Message_gui_ID;
int edmessage_id;

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


WSHDR* ws_eddata = NULL;
int Terminate=0;
//---------------------------------------------------------------------------
// Test edit dialog
//---------------------------------------------------------------------------


EDITCONTROL ec_message;
GUI *ed_message_gui;

void DispSelectMenu();

int inp_onkey(GUI *gui, GUI_MSG *msg)
{
  if(msg->gbsmsg->submess==GREEN_BUTTON)
  {
    Terminate = 1;
    extern const char sndMsgSend[];
    //Play(sndMsgSend);
    SUBPROC((void *)Play, sndMsgSend);
    return 1;
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

char Mess_was_sent = 0;

void inp_ghook(GUI *gui, int cmd)
{
  static SOFTKEY_DESC sk={0x0018, 0x0000,(int)LG_MENU};
#ifndef NEWSGOLD
  static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LG_CLOSE};
#endif

  PNGTOP_DESC *pltop=PNG_TOP();
  extern S_SMILES *s_top;
  extern DYNPNGICONLIST *SmilesImgList;

  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }

  EDITCONTROL ec;
  if (cmd==2)
  {
    //Called after onCreate
  }
  if (cmd==7)
  {
    ExtractEditControl(gui,1,&ec);
    wstrcpy(ws_eddata,ec.pWS);
#ifdef NEWSGOLD
    SetSoftKey(gui,&sk,0);
#else
   SetSoftKey(gui,&sk,1);
   if (ec.pWS->wsbody[0]==0)
      SetSoftKey(gui,&sk_cancel,SET_SOFT_KEY_N==0?1:0);
#endif
  }

  if(cmd==0x0A)
  {
    pltop->dyn_pltop=SmilesImgList;
    DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }

  if(Terminate)
  {
    ExtractEditControl(gui,1,&ec);
    wstrcpy(ws_eddata,ec.pWS);
    //size_t xz = wstrlen(ws_eddata)*2;
    if(wstrlen(ws_eddata))
    {
      //char* body =  utf16_to_utf8((char**)ws_eddata,&xz);
      //body[xz]='\0';
      int res_len;
      char* body = malloc(wstrlen(ws_eddata)*2+1);
      //ExtractAnswer(ws_eddata);
      ws_2utf8(ws_eddata, body, &res_len, wstrlen(ws_eddata)*2+1);

      body = realloc(body, res_len+1);
      body[res_len]='\0';
      char is_gchat = Resource_Ex->entry_type== T_CONF_ROOT ? 1: 0;
      char part_str[]="/part";

      if(!is_gchat)
      {
        CList_AddMessage(Resource_Ex->full_name, MSG_ME, body);
      }
      else
        if(strstr(body, part_str)==body)  // Ключ в начале
        {
          CLIST* room=CList_FindContactByJID(CList_GetActiveContact()->full_name);
          Send_Leave_Conference(room->JID);
          Terminate = 0;
          Mess_was_sent = 1;
          mfree(body);
          return;
        }
      IPC_MESSAGE_S *mess = malloc(sizeof(IPC_MESSAGE_S));
      mess->IsGroupChat = is_gchat;
      mess->body = Mask_Special_Syms(body);
      mfree(body);
      SUBPROC((void*)SendMessage,Resource_Ex->full_name, mess);
      REDRAW();
      Mess_was_sent = 1;
    }
    else MsgBoxError(1,(int)LG_NOSENDNULLMESS);
    Terminate = 0;
  }

  if(cmd==0x03)     // onDestroy
  {
    FreeWS(ws_eddata);
    ws_eddata = NULL;
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
  ws_eddata = AllocWS(MAX_MSG_LEN);
  if(init_text)
  {
    //char *str = convUTF8_to_ANSI_STR(init_text);
    //ParseAnswer(ws_eddata, init_text);
    utf8_2ws(ws_eddata, init_text, MAX_MSG_LEN);
  }
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,ws_eddata,MAX_MSG_LEN);
  AddEditControlToEditQend(eq,&ec,ma);
  edmessage_id=CreateInputTextDialog(&inp_desc,&inp_hdr,eq,1,0);
}
////////////////////////////////////////////////////////////////////////////////
DISP_MESSAGE* MessagesList = NULL;      // Корень списка
unsigned int DispMessList_Count = 0;        // Количество сообщений
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

void redraw_1(void)
{

  if(Resource_Ex->total_msg_count!=OLD_MessList_Count)
  {
    //KillDisp(MessagesList);
    ParseMessagesIntoList(Resource_Ex);
    OLD_MessList_Count = Resource_Ex->total_msg_count;
  }

  Terminate = 0;
  // Расчёт количества строк на одной странице

  Calc_Pages_Data();
  // Заголовок окна
  DrawRectangle(0,SCR_START,ScreenW()-1,SCR_START+FontSize*2+1,0,
                   0,
                   color(MESSAGEWIN_TITLE_BGCOLOR));

  DrawRectangle(0,SCR_START+FontSize+2,ScreenW()-1,ScreenH()-1,0,
                   0,
                   color(MESSAGEWIN_BGCOLOR));

  // Делаем типо название окошка... :)
  WSHDR* ws_title = AllocWS(256);
  utf8_2ws(ws_title, Resource_Ex->full_name, 256);

  DrawString(ws_title,1,SCR_START+1,ScreenW()-1,SCR_START+FontSize+1,MESSAGEWIN_FONT,0,color(MESSAGEWIN_TITLE_FONT),0);

  DISP_MESSAGE* ml = MessagesList;
  int i_ctrl=1;
  int kur;
  int i = 0;
  RGBA MsgBgColor;
  RGBA MsgBg2Color;
  CurrentMessage_Lines = 0;
  
  while(ml)
  {
    if((i_ctrl>(CurrentPage-1)*lines_on_page) && (i_ctrl<=CurrentPage*lines_on_page))
    {

      switch(ml->mtype)
      {
      case MSG_ME:      {MsgBgColor=MESSAGEWIN_MY_BGCOLOR;break;}
      case MSG_CHAT:    {MsgBgColor=MESSAGEWIN_CH_BGCOLOR;break;}
      case MSG_SYSTEM:  {MsgBgColor=MESSAGEWIN_SYS_BGCOLOR;break;}
      case MSG_STATUS:  {MsgBgColor=MESSAGEWIN_STATUS_BGCOLOR;break;}
      case MSG_GCHAT:
        {
          MsgBgColor=ml->log_mess_number %2==0? MESSAGEWIN_GCHAT_BGCOLOR_1 : MESSAGEWIN_GCHAT_BGCOLOR_2;
          break;
        }
      }
      MsgBg2Color=MsgBgColor;
      if(CurrentMessage==ml->log_mess_number)
      {
        Cursor_Pos=i_ctrl;
      }
      kur=0;
      if(Cursor_Pos==i_ctrl)
      {kur=1;
        MsgBgColor = MESSAGEWIN_CURSOR_BGCOLOR;
          if(pod_mess){
        MsgBg2Color= CURSOR_BORDER;
          } else  {
        MsgBg2Color=MESSAGEWIN_CURSOR_BGCOLOR;
          }
        DISP_MESSAGE *mln = ml->next;
        if(mln)
          if(CurrentMessage==mln->log_mess_number) Cursor_Pos++;                    // Обновляем позицию курсора
        CurrentMessage_Lines++;
      }

      DrawRectangle(0,SCR_START+FontSize+2+i*FontSize,ScreenW()-1,SCR_START+FontSize+2+(i+1)*FontSize-kur,0,
                       color(MsgBg2Color),
                       color(MsgBgColor));

      DrawString(ml->mess, MSG_START_X,SCR_START+FontSize+2+i*FontSize,ScreenW()-1,SCR_START+FontSize+2+(i+1)*FontSize*2,MESSAGEWIN_FONT,0,color(MESSAGEWIN_CHAT_FONT),0);
      i++;
    }
    ml = ml->next;
    i_ctrl++;
  }
  FreeWS(ws_title);
  Resource_Ex->has_unread_msg =0; // Непрочитанных сообщений больше нет
}
void mGUI_onRedraw(GUI *data)
{
redraw_1();
}

void mGUI_onCreate(GUI *data, void *(*malloc_adr)(int))
{
  data->state=1;
  MsgList_Quit_Required=0;
}

void mGUI_onClose(GUI *data, void (*mfree_adr)(void *))
{
  KillDisp(MessagesList);
  data->state=0;
}

void mGUI_onFocus(GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  data->state=2;
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
  
 
  if(MsgList_Quit_Required)return 1; //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI

  //DirectRedrawGUI();
  if (KBD_LAYOUT)
  {
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
      switch(msg->gbsmsg->submess)
      {
      case '0':
        {
          // Убить список сообщений
          //KillDisp(MessagesList);
          KillMsgList(Resource_Ex->log);
          Resource_Ex->log = NULL;
          Resource_Ex->has_unread_msg=0;
          Resource_Ex->total_msg_count=0;
          return 1;
        }
#ifndef NEWSGOLD
      case RED_BUTTON:
#endif
      case RIGHT_SOFT:
        {
          return 1;
        }

      case LEFT_SOFT:
        {
          break;
        }
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
          break;
        }
      case '2':
      case UP_BUTTON:
        {
          Calc_Pages_Data_1();
          CurrentMessage_Lines = 0;
          if(Cursor_Pos>1)Cursor_Pos--;
          if(CurrentMessage>1)CurrentMessage--;
        
          REDRAW();
          break;
        }
      case LEFT_BUTTON:
      //страница вверх
        {
          if (CurrentPage>1)
          {
            int cp=CurrentPage;
            for(;;)
            {
              CurrentMessage_Lines = 0;
              Cursor_Pos--;
              CurrentMessage--;
              Calc_Pages_Data_1();redraw_1();
              if (CurrentPage+1==cp)
              {
                break;
              }
              if (CurrentPage<1)break;
            }
          }
          redraw_1();  REDRAW();
          Cursor_Pos=DispMessList_Count;
          break; 
        } 
      case '8':
      case DOWN_BUTTON:
        {
          CurrentMessage_Lines = 0;
          if(Cursor_Pos<DispMessList_Count)Cursor_Pos++;
          if(CurrentMessage<Resource_Ex->total_msg_count)CurrentMessage++;
          Calc_Pages_Data_2();
          REDRAW();
          break;
        }
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
              Calc_Pages_Data_2();redraw_1();
              if (CurrentPage-1==cp) break;
              if (CurrentPage>=MaxPages)break;
            }
          }
          REDRAW(); break;
        }
      case '1'://в начало списка сообщений
        {
          CurrentMessage_Lines = 0;
          Cursor_Pos=1;
          CurrentMessage=1;
          CurrentPage=1;
          REDRAW();
          break;
        }
      case '9'://в конец списка сообщений
        {
          CurrentMessage_Lines = 0;
          Cursor_Pos=DispMessList_Count;
          CurrentMessage=Resource_Ex->total_msg_count;
          CurrentPage=MaxPages;
          REDRAW();
          break;
        }
      case '#':
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
          break;
        }
      case GREEN_BUTTON:
        {
          Init_Message(Resource_Ex, NULL);
          break;
        }
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
        {
          KillMsgList(Resource_Ex->log);
          Resource_Ex->log = NULL;
          Resource_Ex->has_unread_msg=0;
          Resource_Ex->total_msg_count=0;
          return 1;
        }
#ifndef NEWSGOLD
      case RED_BUTTON:
#endif
      case RIGHT_SOFT:
        {
          return 1;
        }

      case LEFT_SOFT:
        {
          break;
        }
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
          break;
        }
      case '2':
      case UP_BUTTON:
        {
          Calc_Pages_Data_1();
          CurrentMessage_Lines = 0;
          if(Cursor_Pos>1)Cursor_Pos--;
          if(CurrentMessage>1)CurrentMessage--;
        
          REDRAW();
          break;
        }
      case '4':
      //страница вверх
        {
          if (CurrentPage>1)
          {
            int cp=CurrentPage;
            for(;;)
            {
              CurrentMessage_Lines = 0;
              Cursor_Pos--;
              CurrentMessage--;
              Calc_Pages_Data_1();redraw_1();
              if (CurrentPage+1==cp)
              {
                break;
              }
              if (CurrentPage<1)break;
            }
          }
          redraw_1();  REDRAW();
          Cursor_Pos=DispMessList_Count;
          break; 
        } 
      case '8':
      case DOWN_BUTTON:
        {
          CurrentMessage_Lines = 0;
          if(Cursor_Pos<DispMessList_Count)Cursor_Pos++;
          if(CurrentMessage<Resource_Ex->total_msg_count)CurrentMessage++;
          Calc_Pages_Data_2();
          REDRAW();
          break;
        }
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
              Calc_Pages_Data_2();redraw_1();
              if (CurrentPage-1==cp) break;
              if (CurrentPage>=MaxPages)break;
            }
          }
          REDRAW(); break;
        }
      case '1'://в начало списка сообщений
        {
          CurrentMessage_Lines = 0;
          Cursor_Pos=1;
          CurrentMessage=1;
          CurrentPage=1;
          REDRAW();
          break;
        }
      case '9'://в конец списка сообщений
        {
          CurrentMessage_Lines = 0;
          Cursor_Pos=DispMessList_Count;
          CurrentMessage=Resource_Ex->total_msg_count;
          CurrentPage=MaxPages;
          REDRAW();
          break;
        }
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
          break;
        }
      case GREEN_BUTTON:
        {
          Init_Message(Resource_Ex, NULL);
          break;
        }
      }
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    switch (msg->gbsmsg->submess)
    {
    case '2':
    case UP_BUTTON:
      {
        Calc_Pages_Data_1();
        CurrentMessage_Lines = 0;
        if(Cursor_Pos>1)Cursor_Pos--;
        if(CurrentMessage>1)CurrentMessage--;
        REDRAW();
        break;
      }
    case '8':
    case DOWN_BUTTON:
      {
        CurrentMessage_Lines = 0;
        if(Cursor_Pos<DispMessList_Count)Cursor_Pos++;
        if(CurrentMessage<Resource_Ex->total_msg_count)CurrentMessage++;
        Calc_Pages_Data_2();
        REDRAW();
        break;
      }
    }
  }
  return(0);
}


extern void kill_data(void *p, void (*func_p)(void *));

// ГУЙ
int mGUI_method8(void){return(0);}

int mGUI_method9(void){return(0);}

const void * const mgui_methods[11]={
  (void *)mGUI_onRedraw,	//Redraw
  (void *)mGUI_onCreate,	//Create
  (void *)mGUI_onClose,	//Close
  (void *)mGUI_onFocus,	//Focus
  (void *)mGUI_onUnfocus,	//Unfocus
  (void *)mGUI_onKey,	//OnKey
  0,
  (void *)kill_data, //onDestroy,	//Destroy
  (void *)mGUI_method8,
  (void *)mGUI_method9,
  0
};
////////////////////////////////////////////////////////////////////////////////
#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


const RECT mCanvas={0,0,0,0};

// Получить связанную структуру DISP_MESSAGE для отображения на экране
void ParseMessagesIntoList(TRESOURCE* ContEx)
{
  if(!ContEx)return;
  int parsed_counter = 0; // Сколько уже было обработано (=OLD_MessList_Count)
  LOG_MESSAGE* MessEx= ContEx->log;
  int cnt=0;

  // В какую область уложить строку (слева без MSG_START_X, справа без одного пикселя)
  int Scr_width = ScreenW() - MSG_START_X - 1 ;

  int Curr_width=0;
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
      utf8_2ws(temp_ws_1, MessEx->mess, strlen(MessEx->mess)*2);

      //temp_ws_2 = AllocWS(CHAR_ON_LINE*2); WTF?
      temp_ws_2 = AllocWS(200); //ИМХО, так лучше
      int l=wstrlen(temp_ws_1);

      //char q[40];
      //sprintf(q,"UTF_len=%d, WSTR_len=%d", strlen(MessEx->mess),l);
      //ShowMSG(2,(int)q);

      int i=0;
      unsigned short *wschar;
      unsigned short symb;
      cnt=0;
      for(i=1;i<=l;i++)
      {
        wschar = temp_ws_1->wsbody+i;
        symb = *wschar;
        if ((symb==0x000A) || (symb==0x000D) || (symb==0x00A0)) //Перевод строки
	{
	L_ADD:
          Disp_Mess_Ex = malloc(sizeof(DISP_MESSAGE));
          Disp_Mess_Ex->mess = AllocWS(cnt);
          wstrcpy(Disp_Mess_Ex->mess, temp_ws_2);
          CutWSTR(temp_ws_2, 0);
          Disp_Mess_Ex->mtype = MessEx->mtype;
          Disp_Mess_Ex->log_mess_number=parsed_counter+1;
          if(!MessagesList){MessagesList =Disp_Mess_Ex;Disp_Mess_Ex->next=NULL;}
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
          Curr_width = 0;
	}
	else
	{
	  Curr_width+=GetSymbolWidth(symb,MESSAGEWIN_FONT);
	  if (Curr_width>Scr_width)
	  {
	    i--; //Повторить с текущим символом, сейчас не лезет
	    goto L_ADD; //Добавить строку
	  }
	  wsAppendChar(temp_ws_2, symb);
	  cnt++;
	  if (i==l) goto L_ADD; //Последний символ, добавить и слинять ;)
	  if (Curr_width==Scr_width) goto L_ADD; //Ровненько легли в строку, тоже добавить
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
