#include "../inc/swilib.h"
#include "../inc/cfg_items.h"
#include "..\inc\zlib.h"
#include "history.h"
#include "conf_loader.h"
#include "main.h"
#include "message_list.h"
#include "xml_parser.h"
#include "bookmarks.h"
#include "adv_login.h"
#include "jabber.h"
#include "string_util.h"
#include "jabber_util.h"
#include "groups_util.h"
#include "clist_util.h"
#include "roster_icons.h"
#include "mainmenu.h"
#include "serial_dbg.h"
#include "../inc/xtask_ipc.h"
#include "lang.h"
#include "smiles.h"
#include "vCard.h"
#include "siejc_ipc.h"
#include "color.h"
#include "rect_patcher.h"

/*
(c) Kibab
(r) Rst7, MasterMind, AD, Borman99
*/

extern int status_keyhook(int submsg, int msg);
extern void AutoStatus(void);
int autostatus_time;
int as;
int CLIST_FONT;
int MESSAGEWIN_FONT;
FSTATS fs;

extern const char color_PATH[];

extern const int AUTOSTATUS_ENABLED;
extern const unsigned int AUTOSTATUS_TIME;
extern const char DEFTEX_AUTOSTATUS[];

extern const int ROSTER_FONT;
extern const int MESSAGES_FONT;

// ============= Учетные данные =============

extern const char JABBER_HOST[];
extern const unsigned int JABBER_PORT;
extern const char USERNAME[];
extern const char JABBER_SERVER[128];
extern const char DEFAULT_MUC_NICK[];
extern const char PATH_TO_PIC[];
extern const int IS_IP;
extern const int USE_SASL;
extern const int USE_ZLIB;
extern const unsigned int DEF_SKR;
extern const int IDLE_ICON;
extern const unsigned int IDLE_ICON_X;
extern const unsigned int IDLE_ICON_Y;

const char VERSION_NAME[]= "Siemens Native Jabber Client";  // НЕ МЕНЯТЬ!
const char VERSION_VERS[] = "3.0.0-Z";
const char CMP_DATE[] = __DATE__;
#define TMR_SECOND 216
const unsigned long PING_INTERVAL = 3*60*TMR_SECOND; // 3 минуты
#ifdef NEWSGOLD
#ifdef ELKA
const char OS[] = "NewSGOLD_ELKA_ELF-Platform";
#else
const char OS[] = "NewSGOLD_ELF-Platform";
#endif
#else
const char OS[] = "SGOLD_ELF-Platform";
#define SEND_TIMER
#endif

//IPC
const char ipc_my_name[32]=IPC_SIEJC_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;

int Is_Sounds_Enabled;
int Is_Vibra_Enabled;
int Is_Autostatus_Enabled;
int Is_Playerstatus_Enabled;
int Is_Smiles_Enabled;
char *exename2;
char elf_path[256];

char Is_Compression_Enabled = 0;

const char percent_s[]="%s";
const char empty_t[]="";
const char conference_t[]="conference";
const char png_t[]=".png";
char empty_str[]="";
char logmsg[512];

JABBER_STATE Jabber_state = JS_NOT_CONNECTED;
char My_Presence = PRESENCE_OFFLINE;

// Флаг необходимости завершить работу
char Quit_Required = 0;

int connect_state=0;
/*
0 = OffLine
1 = Socket Connected
2 = нормальный режим работы, получен ответ от сервера
*/

int sock=-1;

volatile int is_gprs_online=1;


/*int IB_NEWMESSAGE;
int IB_ONLINE;
int IB_CHAT;
int IB_AWAY;
int IB_XA;
int IB_DND;
int IB_INVISIBLE;
int IB_OFFLINE;*/ // IconBar

GBSTMR TMR_Send_Presence; // Посылка презенса
GBSTMR reconnect_tmr;
GBSTMR Ping_Timer;
GBSTMR autostatus_tmr;

/*
{
  {  0,   0, 127, 100},   // Online
  {  0, 255,   0, 100},   // Chat
  {  0,   0, 255, 100},   // Away
  {  0, 127,   0, 100},   // XA
  {255,   0,   0, 100},   // DND
  {127, 127, 127, 100},   // Invisible
  {170, 170, 170, 100},   // Offline
  {127, 127, 127, 100},   // Error
  {170, 170, 170, 100},   // Subscribe
  {170, 170, 170, 100},   // Subscribed
  {170, 170, 170, 100},   // Unsubscribe
  {170, 170, 170, 100}    // Unsubscribed
};
*/

/*void addIconBar(short* num)
{
  #pragma swi_number=0x27 
  __swi __arm void AddIconToIconBar(int pic, short *num);
  int icon_num;
  
  if (CList_GetUnreadMessages()>0)
  {
    icon_num = IB_NEWMESSAGE;
  }
  else
  {
    switch (My_Presence)
    {
    case PRESENCE_ONLINE:
      {
        icon_num = IB_ONLINE;
        break;
      }
    case PRESENCE_CHAT:
      {
        icon_num = IB_CHAT;
      break;
    }
    case PRESENCE_AWAY:
      {
        icon_num = IB_AWAY;
        break;
      }
    case PRESENCE_XA:
      {
        icon_num = IB_XA;
        break;
      }
    case PRESENCE_DND:
      {
        icon_num = IB_DND;
        break;
      }
    case PRESENCE_INVISIBLE:
      {
        icon_num = IB_INVISIBLE;
        break;
      }
    case PRESENCE_OFFLINE:
      {
        icon_num = IB_OFFLINE;
        break;
      }
    }
  }
  AddIconToIconBar(icon_num, num);
}*/ // IconBar

int writefile(char *color_PATH, char *colorshem_PATH, char *buf)
{
 unsigned int err=0;
 int f=0;  
 char path[128];
  
 strcpy(path, color_PATH);
 strcat(path, colorshem_PATH);
 

 /*if((*/f=fopen(path,1+A_BIN+A_Create,P_WRITE,&err);//)==-1)
 fs.size=40;
     fwrite(f,buf,fs.size,&err);
  fclose(f,&err);
return err;
}

//================================================

extern void kill_data(void *p, void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

extern int Message_gui_ID;
int maingui_id;
int maincsm_id;

void SMART_REDRAW(void)
{
  int f;
  LockSched();
  f=IsGuiOnTop(maingui_id)||IsGuiOnTop(Message_gui_ID);
  UnlockSched();
  if (f) REDRAW();
}

//===================================================================
extern const unsigned int sndVolume;

void Play(const char *fname)
{
  if ((!IsCalling())&&Is_Sounds_Enabled)
  {
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);

      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=sndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
  }
}

//===================================================================

GBSTMR tmr_vibra;
volatile int Vibra_Count;

void _start_vibra()
{
  void _stop_vibra(void);
  if(Is_Vibra_Enabled)
  {
    SetVibration(VIBRA_POWER);
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,_stop_vibra);
  }
}

void _stop_vibra(void)
{
  SetVibration(0);
  if (--Vibra_Count)
  {
    GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,_start_vibra);
  }
}

void Vibrate(int Req_Vibra_Count)
{
  if(!Is_Vibra_Enabled)
  {
    Vibra_Count=0;
    return;
  }
  if(Vibra_Count)return;
  Vibra_Count = Req_Vibra_Count;
  if (!IsCalling()) _start_vibra();
}

//===============================================================================================
char My_JID[128];
char My_JID_full[128];

int DNR_ID=0;
int DNR_TRIES=3;

void create_connect(void)
{
  int ***p_res=NULL;
  void do_reconnect(void);
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  int can_connect=0;
  GBS_DelTimer(&reconnect_tmr);
  DNR_ID=0;
  if(!IS_IP)
  {
    snprintf(logmsg,255,"Send DNR...");
    SMART_REDRAW();
    *socklasterr()=0;
    int err=async_gethostbyname(JABBER_HOST,&p_res,&DNR_ID); //03461351 3<70<19<81
    if (err)
    {
      if ((err==0xC9)||(err==0xD6))
      {
        if (DNR_ID)
        {
          return; //Ждем готовности DNR
        }
      }
      else
      {
        snprintf(logmsg,255,"DNR ERROR %d!",err);
        SMART_REDRAW();
        GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
        return;
      }
    }
    if(p_res)
    {
      if(p_res[3])
      {
        snprintf(logmsg,255,"DNR Ok, connecting...");
        SMART_REDRAW();
        DNR_TRIES=0;
        sa.ip=p_res[3][0][0];
        can_connect = 1;
      }
    }
    else
    {
      DNR_TRIES--;
      LockSched();
      ShowMSG(1,(int)"Host not found!");
      UnlockSched();
      return;
    }
  }// Если DNS
  else
  {
    snprintf(logmsg,255,"Using IP address...");
    can_connect = 1;
    sa.ip = str2ip(JABBER_HOST);
    SMART_REDRAW();
  }


  if(can_connect)
  {
    sock=socket(1,1,0);
    if (sock!=-1)
    {
      sa.family=1;
      sa.port=htons(JABBER_PORT);
      if (connect(sock,&sa,sizeof(sa))!=-1)
      {
        connect_state=1;
        SMART_REDRAW();
      }
      else
      {
        closesocket(sock);
        sock=-1;
        LockSched();
        ShowMSG(1,(int)"Can't connect!");
        UnlockSched();
        GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
      }
    }
    else
    {
      LockSched();
      ShowMSG(1,(int)"Can't create socket, GPRS restarted!");
      UnlockSched();
      //Не осилили создания сокета, закрываем GPRS-сессию
      GPRS_OnOff(0,1);
    }
  }	
}

#ifdef SEND_TIMER
GBSTMR send_tmr;
#endif

static void POPUP(const char *msg)
{
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

unsigned int virt_buffer_len = 0; // Виртуальная длина принятого потока
z_stream d_stream;                // Поток для ZLib
char ZLib_Stream_Init=0;          // Признак того, что инициализирован поток сжатия
unsigned int out_bytes_count = 0; // Количество отправленных данных
char *Rstream_p;                  // Указатель на собираемый пакет
int Rstream_n;                    // Количество байт

// Функции-заглушки для ZLib
void* zcalloc(int unk,size_t nelem, size_t elsize)
{
  return (malloc(nelem*elsize));
}

void zcfree(int unk, void* ptr)
{
  mfree(ptr);
}

//Context:HELPER
void get_answer(void)
{
  char rb[1024];
  int i=recv(sock,rb,sizeof(rb),0);
  int j;
  int err;
  char *p;
  int c;
  if (i<=0) return; //Сделаем, как в Натасе, по-простому; пускай нах при ошибке само закрывает

  virt_buffer_len = virt_buffer_len + i;  // Виртуальная длина потока увеличилась

  if (Is_Compression_Enabled)
  {


    if(!ZLib_Stream_Init)
    {
      ZLib_Stream_Init=1;
      d_stream.zalloc = (alloc_func)zcalloc;
      d_stream.zfree = (free_func)zcfree;
      d_stream.opaque = (voidpf)0;
      err = inflateInit2(&d_stream,MAX_WBITS/*-MAX_WBITS*/);
      if(err!=Z_OK)
      {
        char s[32];
        sprintf(s,"inflateInit2 err %d",err);
        POPUP(s);
        return;
      }
    }

    //Используем ZLib для переноса данных в собираемый пакет
    d_stream.next_in  = (Byte*)rb;
    d_stream.avail_in = (uInt)i;
    do
    {
      d_stream.next_out = (Byte*)((Rstream_p=realloc(Rstream_p,Rstream_n+i+1))+Rstream_n); //Новый размер собираемого пакета
      d_stream.avail_out = (uInt)i;
      err = inflate(&d_stream, /*Z_NO_FLUSH*/Z_SYNC_FLUSH);
      switch (err)
      {
      case Z_NEED_DICT:
        //ret = Z_DATA_ERROR;     /* and fall through */
      case Z_DATA_ERROR:
      case Z_MEM_ERROR:
        //(void)inflateEnd(&strm);
        {
          char s[32];
          sprintf(s,"ZLib Err %d",err);
          POPUP(s);
        }
        end_socket();
        return;
      }
      Rstream_n+=(i-d_stream.avail_out);
    }
    while(d_stream.avail_out==0);

  }
  else
  {
    memcpy((Rstream_p=realloc(Rstream_p,Rstream_n+i+1))+Rstream_n,rb,i);
    Rstream_n+=i;
  }
  //Теперь считаем теги
  Rstream_p[Rstream_n]=0; //Ограничим строку \0 для упрощения

  i=0; //Баланс тегов
  j=0; //Баланс скобок
  p=Rstream_p;
  while((p=strstr(p,"<?xml version='1.0'?>"))) {i--; p++;} //Костыль - пропуск заголовков xml, для них нет закрывающих
  p=Rstream_p;
  while((p=strstr(p,"<stream:stream"))) {i--; p++;} //Костыль - пропуск тегов stream, для них нет закрывающих (fuckin' XMPP)

  p=Rstream_p;

  while((c=*p++))
  {
    if (c=='<')
    {
      j++;
      if (*p!='/') i++; else i--;
    }

    // Поправка на короткие теги: <tag/>
    if(c=='>' && (char) *(p-2) == '/')
    {
      i--;
      goto L_END;
    }

    if (c=='>')
    {
    L_END:
      j--;
      if ((!i)&&(!j))
      {
        //Сошелся баланс, отдаем на обработку
        int bytecount=p-Rstream_p;
        IPC_BUFFER* tmp_buffer=malloc(sizeof(IPC_BUFFER)); // Сама структура
        memcpy(tmp_buffer->xml_buffer=malloc(bytecount),Rstream_p,tmp_buffer->buf_size=bytecount); // Буфер в структуре
        memcpy(p=Rstream_p,Rstream_p+bytecount,(Rstream_n-=bytecount)+1); //Обработаные в начало и заодно \0
        GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,tmp_buffer,sock); //Обработаем готовый блок
      }
    }
  }
}

int sendq_l=0;        // Длинна очереди для send
char *sendq_p=NULL;   // указатель очереди

void ClearSendQ(void)
{
  if(sendq_p)mfree(sendq_p);
  sendq_p=NULL;
  sendq_l=NULL;
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

#ifdef SEND_TIMER
static void resend(void)
{
  void bsend(int len, void *p);
  SUBPROC((void*)bsend,0,0);
}
#endif

//Буферизированая посылка в сокет, c последующим освобождением указателя
void bsend(int len, void *p)
{
  int i;
  int j;
  if (connect_state<1) return;
  if (p)
  {
    //Проверяем, не надо ли добавить в очередь
    if (sendq_p)
    {
      //Есть очередь, добавляем в нее
      memcpy((sendq_p=realloc(sendq_p,sendq_l+len))+sendq_l,p,len);
      //mfree(p);
      sendq_l+=len;
      return;
    }
    //Создаем очередь передачи
    memcpy(sendq_p=malloc(len),p,sendq_l=len);
  }
  //Отправляем уже существующее в очереди
  while((i=sendq_l)!=0)
  {
    if (i>0x400) i=0x400;
    j=send(sock,sendq_p,i,0);
    if (j<0)
    {
      j=*socklasterr();
      if ((j==0xC9)||(j==0xD6))
      {
        return; //Видимо, надо ждать сообщения ENIP_BUFFER_FREE
      }
      else
      {
        //Ошибка
        LockSched();
        ShowMSG(1,(int)"Send error!");
        UnlockSched();
        end_socket();
        return;
      }
    }
    memcpy(sendq_p,sendq_p+j,sendq_l-=j); //Удалили переданное
    if (j<i)
    {
      //Передали меньше чем заказывали
#ifdef SEND_TIMER
      GBS_StartTimerProc(&send_tmr,216*5,resend);
#endif
      return; //Ждем сообщения ENIP_BUFFER_FREE1
    }
  }
  mfree(sendq_p);
  sendq_p=NULL;
}

void SendAnswer(char *str)
{
  unsigned int block_len= strlen(str);
  out_bytes_count += block_len;
  //#ifdef LOG_ALL
  //  Log("OUT->", str);
  //#endif

  if(!Is_Compression_Enabled)
  {
    bsend(block_len,str);
  }
  else
  {
    // Эмуляция компрессии ;)
    // Пишем заголовок "блока"
#pragma pack(1)
    struct
    {
      char zero;
      unsigned short len;
      unsigned short notlen;
    };
#pragma pack()
    zero=0;
    len=block_len;
    notlen=~block_len;
    bsend(5,&zero);
    out_bytes_count+=5;
    // Записали, пишем сам блок
    bsend(block_len,str);
  }
}

void SendPing()
{
  //ShowMSG(1,(int)"Ping:)");
  GBS_StartTimerProc(&Ping_Timer,PING_INTERVAL,SendPing);
  if(Jabber_state!=JS_ONLINE)return;
  if(sendq_l)return;
  static char ping_str[]=" ";
  SUBPROC((void*)SendAnswer,ping_str);
}

char Support_Compression = 0;
char Support_MD5_Auth = 0;
char Support_Plain_Auth = 0;
char Support_Resource_Binding = 0;

void Analyze_Stream_Features(XMLNode *nodeEx)
{
  strcat(logmsg, "\nGetting features...");
  XMLNode *Compr_feature = XML_Get_Child_Node_By_Name(nodeEx, "compression");
  if(Compr_feature)
  {
    Support_Compression = 1;
    strcat(logmsg, "\nCompression:  +");
  }

  XMLNode *Res_Binding_feature = XML_Get_Child_Node_By_Name(nodeEx, "bind");
  if(Res_Binding_feature)
  {
    Support_Resource_Binding = 1;
    strcat(logmsg, "\nResBind:       +");
  }

  XMLNode *Auth_Methods = XML_Get_Child_Node_By_Name(nodeEx, "mechanisms");
  if(Auth_Methods)
  {
    XMLNode *Ch_Node=XML_Get_Child_Node_By_Name(Auth_Methods, "mechanism");
    while(Ch_Node)
    {
      if(!strcmp(Ch_Node->value, "DIGEST-MD5"))
      {
        Support_MD5_Auth = 1;
        strcat(logmsg, "\nDIGEST-MD5:  +");
      }
      if(!strcmp(Ch_Node->value, "PLAIN"))
      {
        Support_Plain_Auth = 1;
        strcat(logmsg, "\nPLAIN:  +");
      }
      Ch_Node = Ch_Node->next;
    }
  }
  SMART_REDRAW();
}

/*
Рекурсивная функция декодирования XML-потока
*/
void Process_Decoded_XML(XMLNode* node)
{
  XMLNode* nodeEx = node;
  while(nodeEx)
  {

    //----------------
    if(!strcmp(nodeEx->name,"stream:features"))
    {
      Analyze_Stream_Features(nodeEx);
      if(USE_ZLIB && Support_Compression && Jabber_state == JS_NOT_CONNECTED)Compression_Ask();
      if(Jabber_state == JS_NOT_CONNECTED || Jabber_state==JS_ZLIB_STREAM_INIT_ACK)
        if(Support_MD5_Auth)
        {
          SUBPROC((void*)Use_Md5_Auth_Report);
        }
        else
          if(Support_Plain_Auth)
          {
            SUBPROC((void*)Use_Plain_Auth_Report);
          }
          else
          {
            strcat(logmsg, "\nERROR:  No supported auth methods!");
          }

      if(Support_Resource_Binding && Jabber_state == JS_SASL_NEW_STREAM_ACK)SASL_Bind_Resource();
    }

    //----------------

    if(!strcmp(nodeEx->name,"compressed") && Jabber_state == JS_ZLIB_INIT_ACK)
    {
      Compression_Init_Stream();
    }

    //----------------
    if(!strcmp(nodeEx->name,"success")&& Jabber_state == JS_SASL_AUTH_ACK)
    {
      SASL_Open_New_Stream();
    }

    //----------------
    if(!strcmp(nodeEx->name,"failure")&& Jabber_state < JS_AUTH_OK)
    {
      SASL_Process_Error(nodeEx);
      SUBPROC((void*)end_socket);
    }

    //----------------
    if(!strcmp(nodeEx->name,"challenge")&& Jabber_state == JS_SASL_NEG_ANS_WAIT)
    {
      Process_Auth_Answer(nodeEx->value);
    }
    //----------------
    if(!strcmp(nodeEx->name,"challenge")&& Jabber_state == JS_SASL_NEGOTIATION)
    {
      Decode_Challenge(nodeEx->value);
      Send_Login_Packet();
    }

    //----------------
    if(!strcmp(nodeEx->name,"message"))
    {
      Process_Incoming_Message(nodeEx);
    }
    //----------------
    if(!strcmp(nodeEx->name,"iq"))
    {
      Process_Iq_Request(nodeEx);
    }
    //----------------
    if(!strcmp(nodeEx->name,"stream:stream"))
    {
      connect_state = 2;
      // Если не используем SASL-авторизацию, можно послать пакет авторизации
      if(!USE_SASL)
      {
        Jabber_state = JS_CONNECTED_STATE;
        SUBPROC((void*)Send_Auth);
      }
      else
        if(nodeEx->subnode)
        {
          Process_Decoded_XML(nodeEx->subnode);
          return;
        }
    }
    //----------------
    if(!strcmp(nodeEx->name,"stream:error"))
    {
      connect_state = 0;
      SMART_REDRAW();
      Jabber_state = JS_ERROR;
      char err[]="Ошибка XML-потока";
      MsgBoxError(1,(int)err);
      sprintf(logmsg, err);
      SUBPROC((void*)end_socket);
    }
    //----------------
    if(!strcmp(nodeEx->name,"presence"))
    {
      Process_Presence_Change(nodeEx);
    }
    //----------------

    //if(nodeEx->subnode) Process_Decoded_XML(nodeEx->subnode);
    nodeEx = nodeEx->next;
  }

}

void __log(char* buffer, int size)
{
  char mess[20];
  sprintf(mess,"RECV:%d",size);
#ifdef LOG_TO_COM_PORT
  tx_str(buffer);
#else
  Log(mess,buffer);
#endif
  mfree(buffer);
}

void Process_XML_Packet(IPC_BUFFER* xmlbuf)
{
  // Сюда попадаем, если от транслятора принят указатель на порцию данных
  LockSched();
  XMLNode *data=XMLDecode(xmlbuf->xml_buffer,xmlbuf->buf_size);
  UnlockSched();

  // Сюда было бы логичнее переставить блок записи, ибо тогда в логе будет идти
  // сначала принятый пакет, а потом предпринятые действия
#ifdef LOG_IN_DATA
  char* tmp_buf=malloc(xmlbuf->buf_size+1);
  zeromem(tmp_buf,xmlbuf->buf_size+1);
  memcpy(tmp_buf,xmlbuf->xml_buffer,xmlbuf->buf_size);
  SUBPROC((void*)__log,tmp_buf, xmlbuf->buf_size);
#endif


  if(data)
  {
#ifdef LOG_XML_TREE
    SaveTree(data);
#endif
    Process_Decoded_XML(data);
    DestroyTree(data);
  }

  // Освобождаем память :)
  mfree(xmlbuf->xml_buffer);
  mfree(xmlbuf);
  SMART_REDRAW();
}


//===============================================================================================
// Всякий стафф с GUI

RECT ConnPopupRC;
RECT ConnLogRC;
RECT ConnHeaderRC;

void onRedraw(MAIN_GUI *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  int font_width = FONT_SMALL;
  
  RGBA font_color, bgr_color;
  if(connect_state<2)
  {
    font_color= MAINFONT_NOT_CONNECTED;
    bgr_color = MAINBG_NOT_CONNECTED;
  }
  if(connect_state==2)
  {
    font_color = MAINFONT_CONNECTED;
    bgr_color = MAINBG_CONNECTED;
  }

  if(Jabber_state==JS_AUTH_ERROR || Jabber_state==JS_ERROR)
  {
    font_color = MAINFONT_ERROR;
    bgr_color  = MAINBG_ERROR;
  }
  DrawRoundedFrame(0,SCR_START,scr_w-1,scr_h-1,0,0,0,
                   0,
                   color(bgr_color));

  CList_RedrawCList();

  LockSched();

  if (CList_GetUnreadMessages()>0) { //100000
                                     //100Kb
    if (virt_buffer_len>99999)wsprintf(data->ws1,"%d(%d/%d)IN:%dKb",CList_GetUnreadMessages(), CList_GetNumberOfOnlineUsers(),CList_GetNumberOfUsers(),virt_buffer_len>>10);
    else wsprintf(data->ws1,"%d(%d/%d)IN:%d",CList_GetUnreadMessages(), CList_GetNumberOfOnlineUsers(),CList_GetNumberOfUsers(),virt_buffer_len);
  } else {
    if(virt_buffer_len>99999)wsprintf(data->ws1,"(%d/%d)IN:%dKb",CList_GetNumberOfOnlineUsers(),CList_GetNumberOfUsers(),virt_buffer_len>>10);
    else wsprintf(data->ws1,"(%d/%d)IN:%d",CList_GetNumberOfOnlineUsers(),CList_GetNumberOfUsers(),virt_buffer_len);
  }
  UnlockSched();

  //рисуем селф-иконку
#ifdef USE_PNG_EXT
  char mypic[128];

  if (CList_GetUnreadMessages()>0)
    Roster_getIconByStatus(mypic,50); //иконка сообщения
  else
    Roster_getIconByStatus(mypic, My_Presence);
  Roster_DrawIcon(1, SCR_START+1, (int)mypic);
  DrawString(data->ws1,Roster_getIconWidth(mypic)+2,SCR_START+3,scr_w-4,scr_h-4-16,font_width,0,color(font_color),0);

#else
  int img_num=0;
  if (CList_GetUnreadMessages()>0)
    img_num=Roster_getIconByStatus(50); //иконка сообщения
  else
    img_num=Roster_getIconByStatus(My_Presence);

  Roster_DrawIcon(1, SCR_START+1, img_num); //иконка сообщения
  DrawString(data->ws1,Roster_getIconWidth(img_num)+2,SCR_START+3,scr_w-4,scr_h-4-16,font_width,0,color(font_color),0);
#endif

  if(Jabber_state!=JS_ONLINE)
  {
    wsprintf(data->ws1, "%t", logmsg);
    if(smiles_max != smiles_loaded)
    {
      DrawRectangle(0, scr_h - 7, scr_w-1, scr_h - 1,0,
                    GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(0));
      int pos_status = ((scr_w-1) * smiles_loaded) / smiles_max;
      DrawRectangle(1, scr_h - 6, pos_status, scr_h - 2, 0,
                    GetPaletteAdrByColorIndex(14), GetPaletteAdrByColorIndex(14));
      
      wstrcatprintf(data->ws1,"\nLoading smiles...");
    }
    
    DrawString(data->ws1,1,SCR_START+3+GetFontYSIZE(font_width)+2,scr_w-4,scr_h-4-16,font_width,0,color(font_color),0);
  }
#ifdef USE_PNG_EXT

  if(connect_state<2)
  {
    char logo_path[128];
    strcpy(logo_path, PATH_TO_PIC);
    strcat(logo_path,"SieJC_logo.png");
    DrawImg(0,70,(int)logo_path);
  }
#endif
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}


void QuitCallbackProc(int decision)
{
  if(!decision)Quit_Required = 1;
}

void DisplayQuitQuery()
{
  MsgBoxYesNo(1,(int)LG_EXITSIEJC,QuitCallbackProc);
}

void Enter_SiepatchDB()
{
  extern const unsigned int DEFAULT_MUC_MSGCOUNT;
  char room[]= "siepatchdb@conference.jabber.ru";
  char nick_t[]="%s_SieJC";
  char nick[100];
  if(strlen(DEFAULT_MUC_NICK))
  {
    sprintf(nick, nick_t, DEFAULT_MUC_NICK);
  }
  else
  {
    sprintf(nick, nick_t,USERNAME);
  }

  char *room_nick =ANSI2UTF8(nick, strlen(nick)*2);
  char* room_name = ANSI2UTF8(room, strlen(room)*2);
  Enter_Conference(room, nick, NULL, DEFAULT_MUC_MSGCOUNT);
  mfree(room_nick);
  mfree(room_name);
}

void Disp_State()
{
  char q[80];
  sprintf(q,"Jabber_state=%d\nOut bytes: %d\nSend query len: %d", Jabber_state, out_bytes_count, sendq_l);
  ShowMSG(0,(int)q);
}

// Переподключение
void Do_Reconnect()
{
  extern TRESOURCE* ActiveContact;
  extern unsigned int NContacts;
  extern unsigned int N_Disp_Contacts;
  extern unsigned int Active_page;
  extern unsigned int N_cont_disp;
  extern unsigned int CursorPos;

  // Уничтожаем все объекты
  ClearSendQ();
  GBS_DelTimer(&Ping_Timer);
  GBS_DelTimer(&TMR_Send_Presence);
/*#ifndef NEWSGOLD
  GBS_DelTimer(&redraw_tmr);
#endif*/
  GBS_DelTimer(&reconnect_tmr);
  SetVibration(0);

  // Ре-Инициализация контакт-листа
  /*
  ActiveContact = NULL;
  NContacts = 0;
  N_Disp_Contacts = 0;
  N_cont_disp=0;
  */
  Active_page = 1;
  CursorPos = 1;

  // Уничтожение списков CL, MUC, закладок, групп, очистка SASL
  LockSched();
  //        CList_Destroy();
  //        KillGroupsList();
  MUCList_Destroy();
  CList_MakeAllContactsOFFLINE();
  KillBMList();
  UnlockSched();

  virt_buffer_len = 0;
  Destroy_SASL_Ctx();

  // Ре-Инициализация сжатия
  if(ZLib_Stream_Init)
  {
    inflateEnd(&d_stream);
    zeromem(&d_stream, sizeof(z_stream));
    virt_buffer_len = 0;
    ZLib_Stream_Init=0;
    Is_Compression_Enabled = 0;
    out_bytes_count = 0; // Количество отправленных данных
    Rstream_n = 0;
    Rstream_p = NULL;
  }

  // Создание головы списка
  //InitGroupsList();


	DNR_TRIES=3;
  SUBPROC((void *)create_connect);
}

int onKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if(Quit_Required)
    return 1; //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI

  if(msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
    case DOWN_BUTTON:
    case '8':
      CList_MoveCursorDown(0);
      break;

    case RIGHT_BUTTON:
      CList_MoveCursorDown(1);
      break;

    case UP_BUTTON:
    case '2':
      CList_MoveCursorUp(0);
      break;
      
    case LEFT_BUTTON:
      CList_MoveCursorUp(1);
      break;

    case '#':
      gipc.name_to=ipc_xtask_name;
      gipc.name_from=ipc_my_name;
      gipc.data=0;
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
      if (IsUnlocked())
        KbdLock();
      return(-1);

    case '*':
      gipc.name_to=ipc_xtask_name;
      gipc.name_from=ipc_my_name;
      gipc.data=0;
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
      Is_Vibra_Enabled=!Is_Vibra_Enabled;
    }
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case '3': // Сворачивание/разворачивание конференции
      {
        LockSched();
        extern CLIST *cltop;
        CLIST* ClEx = cltop;
        CLIST* ActiveContact = NULL;
        char *gjid=CList_GetActiveContact()->full_name;
        while(ClEx)
        {
          if(strcmp(gjid,ClEx->JID) == 0) 
          {
            ActiveContact = ClEx;
            break;
          }
          ClEx = ClEx->next;
        }
        UnlockSched();
        if (ActiveContact)
        {
          if(ActiveContact->res_list->entry_type == T_CONF_ROOT)
          {
            ActiveContact->IsVisible=!ActiveContact->IsVisible;
            SMART_REDRAW();
          }
        }
      }
      break;
      
    case '5':
      CList_Display_Popup_Info(CList_GetActiveContact());
      break;

    case ENTER_BUTTON:
      {
        LockSched();
        extern CLIST *cltop;
        CLIST* ClEx = cltop;
        CLIST* ActiveContact = NULL;
        char *gjid=CList_GetActiveContact()->full_name;
        while(ClEx)
        {
          if(stristr(gjid,ClEx->JID)==gjid) 
          {
            ActiveContact = ClEx;
            break;
          }
          ClEx = ClEx->next;
        }
        UnlockSched();
        if (ActiveContact)
        {
          if(ActiveContact->res_list->entry_type!=T_GROUP)
          {
            Display_Message_List(CList_GetActiveContact());
          }
          else
          {
            CList_ToggleVisibilityForGroup(ActiveContact->group);
            SMART_REDRAW();
          }
        }
      }
      break;

    case LEFT_SOFT:
      MM_Show();
      break;

#ifndef NEWSGOLD
    case RED_BUTTON:
#endif
    case RIGHT_SOFT:
      DisplayQuitQuery();
      break;
    
    case GREEN_BUTTON:
      if (connect_state == 0 && sock == -1)
        Do_Reconnect();
      if(connect_state==2 && Jabber_state==JS_ONLINE && CList_GetActiveContact()->entry_type != T_GROUP)
        Init_Message(CList_GetActiveContact(), NULL);
      break;

    case '1':
      CList_MoveCursorHome();
      break;

    case '4':
      if(Jabber_state == JS_ONLINE)
        Enter_SiepatchDB();
      break;
      
    case '6':
      Disp_State();
      break;

    case '7': // НЕ ЗАНИМАТЬ!!!
      break;

    case DOWN_BUTTON:
    case '8':
      CList_MoveCursorDown(0);
      break;

    case RIGHT_BUTTON:
      CList_MoveCursorDown(1);
      break;

    case UP_BUTTON:
    case '2':
      CList_MoveCursorUp(0);
      break;

    case LEFT_BUTTON:
      CList_MoveCursorUp(1);
      break;

    case '9':
      CList_MoveCursorEnd();
      break;

    case '0':
      CList_ToggleOfflineDisplay();
      break;

    case '*':
      Is_Vibra_Enabled=!(Is_Vibra_Enabled);
      break;

    case '#': //решеткой бегаем между непрочитанными
      nextUnread();
      break;
    }
  }
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)onRedraw,	//SMART_REDRAW
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)onKey,	//OnKey
  0,
  (void *)kill_data, //onDestroy,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{    
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  maingui_id=csm->gui_id=CreateGUI(main_gui);
  DNR_TRIES=3;
  InitGroupsList();
  strcat((char *)ipc_my_name,USERNAME);strcat((char *)ipc_my_name, "@");strcat((char *)ipc_my_name, JABBER_SERVER);
  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
#ifdef LOG_ALL
  // Определим адреса некоторых процедур, на случай,
  // если клиент будет падать - там могут быть аборты...
  void* Process_XML_Packet_ADR = (void*)Process_XML_Packet;
  void* Process_Decoded_XML_ADR = (void*) Process_Decoded_XML;
  char msg[80];
  sprintf(msg,"@Process_XML_Packet=0x%X, @Process_Decoded_XML=0x%X\r\n",Process_XML_Packet_ADR, Process_Decoded_XML_ADR);
  Log("SYSTEM", msg);
#endif
}

extern const int DEF_SOUND_STATE;
extern const int DEF_VIBRA_STATE;
extern const int DEF_SHOW_OFFLINE;
extern char Display_Offline;

void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&tmr_vibra);
  GBS_DelTimer(&Ping_Timer);
  GBS_DelTimer(&TMR_Send_Presence);
  GBS_DelTimer(&reconnect_tmr);
  GBS_DelTimer(&autostatus_tmr);
  RemoveKeybMsgHook((void *)status_keyhook);  
  SetVibration(0);

  extern ONLINEINFO OnlineInfo;
  if(OnlineInfo.txt)mfree(OnlineInfo.txt);
  CList_Destroy();
  MUCList_Destroy();
  KillBMList();
  KillGroupsList();
  Destroy_SASL_Ctx();

  if(ZLib_Stream_Init)
  {
    inflateEnd(&d_stream);
  }

  void WriteDefSettings(char *elfpath);
  WriteDefSettings(elf_path);
  
  if (cur_color_name) mfree(cur_color_name);
  
  SUBPROC((void *)FreeSmiles);
  SUBPROC((void *)end_socket);
  SUBPROC((void *)ClearSendQ);
  SUBPROC((void *)ElfKiller);
}

void do_reconnect(void)
{
  if (is_gprs_online)
  {
    DNR_TRIES=3;
    SUBPROC((void*)create_connect);
  }
}

void CheckDoubleRun(void)
{
  int csm_id;
  if ((csm_id=(int)(gipc.data))!=-1)
  {
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)csm_id;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);  
    LockSched();
    CloseCSM(maincsm_id);
    ShowMSG(1,(int)LG_ASTARTED);
    UnlockSched();
  }
  else
  {
    SUBPROC((void *)InitSmiles);
    SUBPROC((void *)create_connect);
    GBS_StartTimerProc(&Ping_Timer,PING_INTERVAL,SendPing);
  }
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  {
    //IPC
    if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
        if (stricmp(ipc->name_to,ipc_my_name)==0)
        {
          switch (msg->submess)
          {
          case IPC_SMILE_PROCESSED:
            //Только собственные смайлы ;)
            if (ipc->name_from==ipc_my_name) SUBPROC((void *)ProcessNextSmile);
            SMART_REDRAW();
            break;
          case IPC_CHECK_DOUBLERUN:
	    //Если приняли свое собственное сообщение, значит запускаем чекер
	    if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
            else ipc->data=(void *)maincsm_id;
	    break;
          }
        }

        if(Is_Playerstatus_Enabled)
        {
          if ((stricmp(ipc->name_to,IPC_FROMMEDIA)==0)&&(Jabber_state == JS_ONLINE))//strcmp_nocase
          {
          extern ONLINEINFO OnlineInfo;
          extern const char DEFTEX_PLAYER[];
          PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
          pr_info->priority=OnlineInfo.priority;
          pr_info->status=OnlineInfo.status;
          char *msg = malloc(256);
          if (ipc->data)
          {
          int len=0;
          WSHDR *ws = AllocWS(256);
          WSHDR *ws2 = AllocWS(256);
          str_2ws(ws2, (char*)(ipc->data), 256);
          wsprintf(ws, "%t%w", DEFTEX_PLAYER, ws2);
          ws_2utf8(ws, msg, &len, wstrlen(ws)*2+1);
          msg=realloc(msg, len+1);
          FreeWS(ws);
          FreeWS(ws2);
          msg[len]='\0';
          pr_info->message= msg ==NULL ? NULL : Mask_Special_Syms(msg);
          } else
          {
            pr_info->message= NULL;
          }
          SUBPROC((void *)Send_Presence,pr_info);
          mfree(msg);
          }
        }
      }
    }

    if (IDLE_ICON)
    {
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
      CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
      if (IsGuiOnTop(idlegui_id))
      {
        GUI *igui=GetTopGUI();
        if (igui) //И он существует
        {
#ifdef ELKA
          {
            void *canvasdata=BuildCanvas();
#else
            void *idata=GetDataOfItemByID(igui,2);
            if (idata)
            {
              void *canvasdata=((void **)idata)[DISPLACE_OF_IDLECANVAS/4];
#endif

#ifdef USE_PNG_EXT
              char mypic[128];

              if (CList_GetUnreadMessages()>0)
                Roster_getIconByStatus(mypic,50); //иконка сообщения
              else
                Roster_getIconByStatus(mypic, My_Presence);
              DrawCanvas(canvasdata,IDLE_ICON_X,IDLE_ICON_Y,IDLE_ICON_X+GetImgWidth((int)mypic)-1,IDLE_ICON_Y+GetImgHeight((int)mypic)-1,1);
              DrawImg(IDLE_ICON_X,IDLE_ICON_Y,(int)mypic);
#else
              int mypic=0;
              if (CList_GetUnreadMessages()>0)
                mypic=Roster_getIconByStatus(50); //иконка сообщения
              else
                mypic=Roster_getIconByStatus(My_Presence);
              DrawCanvas(canvasdata,IDLE_ICON_X,IDLE_ICON_Y,IDLE_ICON_X+GetImgWidth(mypic)-1,IDLE_ICON_Y+GetImgHeight(mypic)-1,1);
              DrawImg(IDLE_ICON_X,IDLE_ICON_Y,mypic);
#endif
            }
          }
        }
      }
    }
    if(Quit_Required)
    {
      csm->csm.state=-3;
    }
    if (msg->msg==MSG_GUI_DESTROYED)
    {
      int id;
      if ((id=((int)msg->data0))==csm->gui_id)
      {
        csm->csm.state=-3;
      }
      if (id==Message_gui_ID) Message_gui_ID=0;
    }
    if (msg->msg==MSG_HELPER_TRANSLATOR)
    {
      switch((int)msg->data0)
      {
      case LMAN_DISCONNECT_IND:
        is_gprs_online=0;
        return(1);
      case LMAN_CONNECT_CNF:
        is_gprs_online=1;
        return(1);
      case ENIP_DNR_HOST_BY_NAME:
        if ((int)msg->data1==DNR_ID)
        {
          if (DNR_TRIES) SUBPROC((void *)create_connect);
        }
        return(1);
      }
      if ((int)msg->data1==sock)
      {
        //Если наш сокет
        if ((((unsigned int)msg->data0)>>28)==0xA)
        {
          //Пакет XML-данных готов к обработке и передаётся на обработку в контексте MMI
          Process_XML_Packet((IPC_BUFFER*)msg->data0);
          return(0);
        }
        switch((int)msg->data0)
        {
        case ENIP_SOCK_CONNECTED:
          if (connect_state==1)
          {
            //Соединение установлено, посылаем пакет Welcome
            SUBPROC((void*)Send_Welcome_Packet);
            SMART_REDRAW();
          }
          else
          {
            ShowMSG(1,(int)"Illegal message ENIP_SOCK_CONNECTED!");
          }
          break;
        case ENIP_SOCK_DATA_READ:
          if (connect_state>=1)
          {
            //Если посылали Welcome, передаём на принятие в контекст HELPER
            SUBPROC((void *)get_answer);
          }
          else
          {
            ShowMSG(1,(int)"Illegal message ENIP_DATA_READ");
          }
          break;
        case ENIP_BUFFER_FREE:
        case ENIP_BUFFER_FREE1:
          //Досылаем очередь
          SUBPROC((void *)bsend,0,0);
          break;
        case ENIP_SOCK_REMOTE_CLOSED:
          //Закрыт со стороны сервера
          if (connect_state) SUBPROC((void *)end_socket);
          break;
        case ENIP_SOCK_CLOSED:
          SUBPROC((void *)ClearSendQ);
          if(ZLib_Stream_Init)
          {
            inflateEnd(&d_stream);
          }
          connect_state=0;
          Jabber_state = JS_NOT_CONNECTED;
          sock=-1;
          Vibrate(4);
          SMART_REDRAW();
          GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,Do_Reconnect);
          break;
        }
      }
    }
    return(1);
  }

/*typedef struct
{
  char check_name[8];
  int addr;
}ICONBAR_H;*/ // IconBar

const int minus11=-11;

unsigned short maincsm_name_body[140];

struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
  //ICONBAR_H iconbar_handler; // IconBar
}MAINCSM =
{
  {
    maincsm_onmessage,
    maincsm_oncreate,
#ifdef NEWSGOLD
    0,
    0,
    0,
    0,
#endif
    maincsm_onclose,
    sizeof(MAIN_CSM),
    1,
    &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }/*,
  {
    "IconBar"
  }*/ // IconBar
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"SieJC: %s@%s",USERNAME, JABBER_SERVER);
}

// Проверка, что платформа для компиляции выбрана правильно

unsigned short IsGoodPlatform()
{
#ifdef NEWSGOLD
  return  isnewSGold();
#else
  return  !isnewSGold();
#endif
}

void Check_Settings_Cleverness()
{
  if(!USE_SASL && USE_ZLIB)
    ShowMSG(0,(int)LG_ZLIBNOSASL);
}

void ReadDefSettings(char *elfpath)
{
  DEF_SETTINGS def_set;
  int f;
  unsigned int err;
  char str[128];

  strcpy(str, elfpath);  
  strcat(str, USERNAME);

  if ((f=fopen(str,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
    fread(f,&def_set,sizeof(DEF_SETTINGS),&err);
    fclose(f,&err);
    Is_Vibra_Enabled=def_set.vibra_status;
    Is_Sounds_Enabled=def_set.sound_status;
    Display_Offline=def_set.off_contacts;
    Is_Autostatus_Enabled=def_set.auto_status;
    Is_Playerstatus_Enabled=def_set.player_status;
    Is_Smiles_Enabled=def_set.smiles_status;
    if (cur_color_name) mfree(cur_color_name);
    cur_color_name = (char *)malloc(32);
    strcpy(cur_color_name, def_set.color_name);
  }
  else
  {
    Is_Vibra_Enabled=0;
    Is_Sounds_Enabled=0;
    Display_Offline=0;
    Is_Autostatus_Enabled=0;
    Is_Playerstatus_Enabled=0;
    Is_Smiles_Enabled=0;
    if (cur_color_name) mfree(cur_color_name);
    cur_color_name = (char *)malloc(32);
    strcpy(cur_color_name, "default");
  }
}  

void WriteDefSettings(char *elfpath)
{
  DEF_SETTINGS def_set;
  int f;
  unsigned int err;
  char str[128];

  strcpy(str, elfpath);  
  strcat(str, USERNAME);

  if ((f=fopen(str,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1)
  {
    def_set.vibra_status=Is_Vibra_Enabled;
    def_set.sound_status=Is_Sounds_Enabled;
    def_set.off_contacts=Display_Offline;
    strcpy(def_set.color_name, cur_color_name);
    def_set.auto_status=Is_Autostatus_Enabled;
    def_set.player_status=Is_Playerstatus_Enabled;
    def_set.smiles_status=Is_Smiles_Enabled;
    fwrite(f, &def_set, sizeof(DEF_SETTINGS), &err);
    fclose(f, &err);
  }
}

int status_keyhook(int submsg, int msg)
{
  if(Is_Autostatus_Enabled)
  {
    if (as==1)
    {
      if (IsGuiOnTop(maingui_id)||IsGuiOnTop(Message_gui_ID))
      {
        extern const char DEFTEX_ONLINE[256];
        extern ONLINEINFO OnlineInfo;
        PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
        pr_info->priority=OnlineInfo.priority;
        pr_info->status=0;
        char *msg = malloc(256);
        WSHDR *ws = AllocWS(256);
        int len;
        ascii2ws(ws, DEFTEX_ONLINE);
        ws_2utf8(ws, msg, &len, wstrlen(ws)*2+1);
        msg=realloc(msg, len+1);
        msg[len]='\0';
        pr_info->message= msg ==NULL ? NULL : Mask_Special_Syms(msg);
        SUBPROC((void *)Send_Presence,pr_info);
        as = 0;
        FreeWS(ws);
        mfree(msg);
      }
    }
    else
    {
      GBS_DelTimer(&autostatus_tmr);
    }
    GBS_StartTimerProc(&autostatus_tmr, autostatus_time, AutoStatus);
  }
  return KEYHOOK_NEXT;
}


void AutoStatus(void)
{
  if(Is_Autostatus_Enabled)
  {
    if (My_Presence == PRESENCE_ONLINE)
    {
      TDate date;
      TTime time;
      GetDateTime(&date, &time);
      extern ONLINEINFO OnlineInfo;      
      PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
      pr_info->priority=OnlineInfo.priority;
      pr_info->status=3;
      char *msg = malloc(256);
      WSHDR *ws = AllocWS(256);
      int len;
      wsprintf(ws, "%t %02d.%02d.%04d %d:%02d", DEFTEX_AUTOSTATUS, date.day, date.month, date.year, time.hour, time.min);
      ws_2utf8(ws, msg, &len, wstrlen(ws)*2+1);
      msg=realloc(msg, len+1);
      msg[len]='\0';
      pr_info->message =msg == NULL ? NULL : Mask_Special_Syms(msg);
      Send_Presence(pr_info);
      as = 1;
      GBS_DelTimer(&autostatus_tmr);
      FreeWS(ws);    
      mfree(msg);
    }
  }
  else GBS_DelTimer(&autostatus_tmr);
}

/*void LoadIconSet(const char *fname)
{
  int hFile;
  unsigned int err;
  hFile = fopen(fname, A_ReadOnly + A_BIN, P_READ, &err);
  if (hFile == -1) return;
  FSTATS stats;
  if (GetFileStats(fname, &stats, &err)) return;
  int fs = stats.size;
  char *buff = malloc(fs);
  fread(hFile, buff, fs, &err);
  IB_ONLINE = buff[0x2D] * 0x100 + buff[0x2C];
  IB_CHAT = buff[0x5D] * 0x100 + buff[0x5C];
  IB_AWAY = buff[0x8D] * 0x100 + buff[0x8C];
  IB_XA = buff[0xBD] * 0x100 + buff[0xBC];
  IB_DND = buff[0xED] * 0x100 + buff[0xEC];
  IB_INVISIBLE = buff[0x11D] * 0x100 + buff[0x11C];
  IB_OFFLINE = buff[0x14D] * 0x100 + buff[0x14C];
  IB_NEWMESSAGE = buff[0x17D] * 0x100 + buff[0x17C];
  fclose(hFile, &err);
  mfree(buff);
}*/ // IconBar

void OpenSettings(void)
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
}

/*void SetIconBarHandler()
{
  MAINCSM.iconbar_handler.addr = (int)addIconBar;
}*/ // IconBar
  
int main(char *exename, char *fname)
{
  MAIN_CSM main_csm;
    
  char * s=strrchr(exename,'\\');
  int len = (s - exename) + 1;
  strncpy(elf_path, exename, len);
  elf_path[len] = 0;    
    
  exename2 = exename;
  if(!IsGoodPlatform())
  {
    ShowMSG(1,(int)LG_PLATFORMM);
    return 0;
  }
  
  InitConfig(fname);
  ReadDefSettings(elf_path);
    
  if(!ReadColor(cur_color_name))
  {
    MsgBoxError(1,(int)"No color bcfg");
    return 0;
  }
    
  if(!strlen(USERNAME))
  {
    ShowMSG(1,(int)LG_ENTERLOGPAS);
    OpenSettings();
    return 0;
  }
   
  extern TTime intimes;           // инициализация переменных
  extern TDate indates;           // для idle
  GetDateTime(&indates,&intimes); //

  UpdateCSMname();

  LockSched();
  maincsm_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();

  Check_Settings_Cleverness();
  switch (ROSTER_FONT)
  {
  case 0:
    CLIST_FONT=FONT_SMALL;
    break;
  case 1:
    CLIST_FONT=FONT_SMALL_BOLD;
    break;
  case 2:
    CLIST_FONT=FONT_MEDIUM;
    break;
  case 3:
    CLIST_FONT=FONT_MEDIUM_BOLD;
    break;
  case 4:
    CLIST_FONT=FONT_LARGE;
    break;
  case 5:
    CLIST_FONT=FONT_LARGE_BOLD;
    break;
  }
  switch (MESSAGES_FONT)
  {
  case 0:
    MESSAGEWIN_FONT=FONT_SMALL;
    break;
  case 1:
    MESSAGEWIN_FONT=FONT_SMALL_BOLD;
    break;
  case 2:
    MESSAGEWIN_FONT=FONT_MEDIUM;
    break;
  case 3:
    MESSAGEWIN_FONT=FONT_MEDIUM_BOLD;
    break;
  case 4:
    MESSAGEWIN_FONT=FONT_LARGE;
    break;
  case 5:
    MESSAGEWIN_FONT=FONT_LARGE_BOLD;
    break;
  }
  if (AUTOSTATUS_ENABLED)
  {
    if(AUTOSTATUS_TIME < 1) autostatus_time = 15000; //1min (интересный ефект если в конфиг внести 0 :)
    else autostatus_time = 250*60*AUTOSTATUS_TIME;
    AddKeybMsgHook((void *)status_keyhook);
    GBS_StartTimerProc(&autostatus_tmr, autostatus_time, AutoStatus);
    as = 0;
  }
  /*extern const int SHOW_ICONBAR_ICON;
  if (SHOW_ICONBAR_ICON)
  {
    extern const char ICONSET_FILENAME[128];
    LoadIconSet(ICONSET_FILENAME);
    SetIconBarHandler();
  }*/ // IconBar
  return 0;
}
