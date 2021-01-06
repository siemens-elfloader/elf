#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "strings.h"
#include "main.h"
#include "items_menu.h"

int sock;
int encoding=0;
int connect_state;
int is_gprs_online;
int DNR_TRIES;
int DNR_ID;

int ALLTOTALRECEIVED;
int ALLTOTALSENDED;

char logmsg[256];
GBSTMR mytmr;

const char _percent_t[]="%t";
const char _empty_str[]="";



typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
}MAIN_GUI;

int maingui_id;

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


void SMART_REDRAW(void)
{
  int f;
  LockSched();
  f=IsGuiOnTop(maingui_id);
  UnlockSched();
  if (f) REDRAW();
}

 char *buffer;
 int buffer_len=0;

 

int get_path_from_url(char *dest, const char *source)
{
  char *s1;
  int c;
  int len=0;
  const char *s2=source;
  while((s1=strchr(s2, '/')))
  {
    s2=s1;
    if (*(s2+1)!='/') break;
    s2+=2;
  }   
  while((c=*s2++))
  {
    *dest++=c;
    len++;
  }
  *dest=0;
  return (len);   
}
char HOST[99]="http://vkontakte.ru/index.php?act=login&email=dan-korekovcev@ya.ru&pass=1gy8NbPP";
//char HOST[256]="http://login.vk.com/index.php?act=login&q=1&al_frame=1&expire=&captcha_sid=&captcha_key=&from_host=vk.com&email=dan-korekovcev@ya.ru&pass=1gy8NbPP";
int get_host_from_url(char *dest, const char *source)
{
  char *s1;
  int len=0;
  int c;
  const char *s2=source;
  if ((s1=strchr(s2, ':')))
  {
    if (*(s1+1)=='/' && *(s1+2)=='/')
    {
      s2=s1+3;
    }
  }
  while((c=*s2++))
  {
    if (c=='/' || c==':') break;
    *dest++=c;
    len++;
  }
  *dest=0;
  return (len); 
}




void create_connect()
{
  char rss_host[256];
  unsigned int rss_port=80;
  int ***p_res=NULL;
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state = 0;
  int err;
  unsigned int ip;
  if (!IsGPRSEnabled())
  {
    is_gprs_online=0;
    return;
  }
  DNR_ID=0;
  *socklasterr()=0;
  
  get_host_from_url(rss_host,HOST);

  sprintf(logmsg, "Connect to: %s Using port: %d", rss_host, rss_port);
  SMART_REDRAW();
  ip=str2ip(rss_host);
  if (ip!=0xFFFFFFFF)
  {
    sa.ip=ip;
    goto L_CONNECT;
  }
  err=async_gethostbyname(rss_host,&p_res,&DNR_ID); //03461351 3<70<19<81
  if (err)
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (DNR_ID)
      {
        strcpy(logmsg, "Wait DNR");
        SMART_REDRAW();
	return; //Ждем готовности DNR
      }
    }
    else
    {
      snprintf(logmsg,255,"DNR error %d",err);
      SMART_REDRAW();
      return;
    }
  }
  if (p_res)
  {
    if (p_res[3])
    {
      strcpy(logmsg,"DNR ok!");
      REDRAW();
      DNR_TRIES=0;
      sa.ip=p_res[3][0][0];
    L_CONNECT:
      sock=socket(1,1,0);
      if (sock!=-1)
      {
	sa.family=1;
	sa.port=htons(rss_port);
	if (connect(sock,&sa,sizeof(sa))!=-1)
	{
	  connect_state=1;
	}
	else
	{
	  closesocket(sock);
	  sock=-1;
          snprintf(logmsg,255,"Connect fault");
          SMART_REDRAW();
	}
      }
      else
      {
        snprintf(logmsg,255,"Error Create Socket");
        SMART_REDRAW();
      }
    }
  }
  else
  {
    DNR_TRIES--;
  }
}


char *recv_buf=NULL;
int recv_buf_len=0;

char *send_buf=NULL;
int send_buf_len=0;


void free_recv_buf(void)
{
  char *p=recv_buf;
  recv_buf_len=0;
  recv_buf=NULL;
  mfree(p);
}

int receive_mode;
void get_answer()
{
  char buf[2048];
  int j;
  j=recv(sock,buf,sizeof(buf),0);
  if (j>0)
  {
    ALLTOTALRECEIVED+=j;
    SMART_REDRAW();
 if (receive_mode)
    {
      buffer=realloc(buffer, buffer_len+j+1);
      buffer[buffer_len+j]=0;
      memcpy(buffer+buffer_len, buf, j);
      buffer_len+=j;
    }
    else
    {
      char *end_answer;
      recv_buf=realloc(recv_buf, recv_buf_len+j+1);
      recv_buf[recv_buf_len+j]=0;
      memcpy(recv_buf+recv_buf_len, buf, j);
      recv_buf_len+=j;
      if (!(end_answer=strstr(recv_buf, "\r\n\r\n"))) return;
      receive_mode=1; //Остальное транслируем напрямую
      end_answer+=4;
      j=recv_buf_len-(end_answer-recv_buf);
      mfree(buffer);
      buffer=NULL;
      buffer_len=0;
      if (!j) return; //Нет данных, нечего посылать
      buffer=malloc(j+1);
      buffer[j]=0;
      memcpy(buffer, end_answer, j);
      buffer_len=j;
      free_recv_buf();
    }
  }
}

void free_send_buf(void)
{
  char *p=send_buf;
  send_buf_len=0;
  send_buf=NULL;
  mfree(p);
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

#ifdef SEND_TIMER
static void resend(void)
{
  void send_answer(char *buf, int len);
  SUBPROC((void*)send_answer,0,0);
}
#endif

void send_answer(char *buf, int len)
{
  int i, j;
  char *p;
  if (buf)
  {
    if (send_buf)
    {
      send_buf=realloc(send_buf,send_buf_len+len);
      memcpy(send_buf+send_buf_len, buf, len);
      send_buf_len+=len;
      mfree(buf);
      return;
    }
    send_buf=buf;
    send_buf_len=len;
  }
  while((i=send_buf_len)!=0)
  {
    if (i>0x400) i=0x400;
    j=send(sock,send_buf,i,0);
    if (j<0)
    {
      j=*socklasterr();
      if ((j==0xC9)||(j==0xD6))
      {
	return; //Видимо, надо ждать сообщения ENIP_BUFFER_FREE
      }
      else
      {
	return;
      }
    }
    ALLTOTALSENDED+=j;
    send_buf_len-=j;
    SMART_REDRAW();
    memcpy(send_buf,send_buf+j,send_buf_len); //Удалили переданное
    if (j<i)
    {
      //Передали меньше чем заказывали
#ifdef SEND_TIMER
      GBS_StartTimerProc(&send_tmr,TMR_SECOND(5),resend);
#endif
      return; //Ждем сообщения ENIP_BUFFER_FREE1
    }
  }
  p=send_buf;
  send_buf=NULL;
  mfree(p);
}

static void end_socket(void)
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

static void free_buffers(void)
{
  free_recv_buf();
  free_send_buf();
}

static void free_socket(void)
{
  sock=-1;
  connect_state=0;
  free_buffers();
  REDRAW();
}

void send_req()
{
  char *p;
  int len;
  char host[256], get_path[256];
  char req_buf[400];
  
  get_path_from_url(get_path, HOST);
  get_host_from_url(host, HOST);

  len=snprintf(req_buf,400,"GET %s"
               " HTTP/1.0\r\nHost: %s\r\n\r\n", get_path, host);
  p=malloc(len+1);
  strcpy(p, req_buf);
  send_answer(p, len);
}

char *html_decode(char *s)
{
  int l=strlen(s);
  int c;
  char *d, *dest;
  d=dest=malloc(l+1);
  char *tag_strip=NULL;
  while((c=*s++))
  {
  L_START:
    if (c=='<')
    {
      if (!strncmp(s,"br>",3))
      {
        *d++=13;
        s+=3;
        continue;
      }
      if (!strncmp(s,"br />",5))
      {
        *d++=13;
        s+=5;
        continue;
      }
      if (!strncmp(s,"/td>",4))
      {
        *d++=' ';
        s+=4;
        continue;
      }
      if (!strncmp(s,"p>",2))
      {
        *d++=13;
        s+=2;
        continue;
      }
      // Иначе какой то левый тэг, режем нахуй Ж)
      tag_strip=d;
      continue;
    }
    if (c=='>')
    {
      if (tag_strip)
      {
        d=tag_strip;
        tag_strip=NULL;
        continue;
      }      
    }
    if (c=='&')
    {
      if (!strncmp(s,"quot;",5))
      {
        c='\"';
        s+=5;
        goto L_START;
      }
      if (!strncmp(s,"nbsp;",5))
      {
        c='_';
        s+=5;
        goto L_START;
      }
      if (!strncmp(s,"lt;",3))
      {
        c='<';
        s+=3;
        goto L_START;
      }
      if (!strncmp(s,"gt;",3))
      {
        c='>';
        s+=3;
        goto L_START;
      }
      if (!strncmp(s,"amp;",4))
      {
        c='&';
        s+=4;
        goto L_START;
      }
      if (!strncmp(s,"copy;",5))
      {
        c=0xA9;
        s+=5;
        goto L_START;
      }
      if (*s=='#')
      {
        int k;
        s++;
        c=0;
        while((k=*s++)!=';')
        {
          c*=10;
          c+=k-'0';
        }
        c=char16to8(c);
        goto L_START;
      }
    }
    *d++=c;
  }
  *d=0;
  return dest;
}



static void OnRedraw(MAIN_GUI *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  unsigned long RX=ALLTOTALRECEIVED; unsigned long TX=ALLTOTALSENDED;
  int n=0;
  DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  wsprintf(data->ws1,
           "State: %d\n"
             "Rx: %db, Tx: %db\n"
               "Queue: %db\n"
                 "%t\n"
                   "Total items: %d",connect_state,RX,TX,send_buf_len,logmsg,n);
  DrawString(data->ws1,3,3+YDISP,scr_w-4,scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
             FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
 
  wsprintf(data->ws1,_percent_t,"Exit");
  DrawString(data->ws1,scr_w>>1,scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),scr_w-4,scr_h-4,
             FONT_MEDIUM_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
 
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
  FreeWS(data->ws1);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case '1':
      break;

    case GREEN_BUTTON:
      DNR_TRIES=3;
      SUBPROC((void *)create_connect);
      SMART_REDRAW();
      break;



    case RIGHT_SOFT:
      return (1);
    }

  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};

static void maincsm_oncreate(CSM_RAM *data)
{
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm=(MAIN_CSM *)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  maingui_id=csm->gui_id=CreateGUI(main_gui);
}

#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *data)
{
  SUBPROC((void *)free_socket);
  GBS_DelTimer(&mytmr);
  SUBPROC((void *)ElfKiller);
}
int f;
static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
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
      switch((int)msg->data0)
      {
      //Если наш сокет
      case ENIP_SOCK_CONNECTED:
        //Если посылали запрос
        free_buffers();
        if (connect_state==1)
        {
          receive_mode=0;
          connect_state=2;
          SUBPROC((void *)send_req);
        }
        break;

      case ENIP_SOCK_DATA_READ:
        //Если посылали send
        if (connect_state>=2)
        {
          SUBPROC((void *)get_answer);
        }
        break;

      case ENIP_BUFFER_FREE:
      case ENIP_BUFFER_FREE1:
	//Досылаем очередь
	SUBPROC((void *)send_answer,0,0);
	break;

      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        sprintf(logmsg,"Remote closed!");
        goto ENIP_SOCK_CLOSED_ALL;

      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        sprintf(logmsg,"Local closed!");
      ENIP_SOCK_CLOSED_ALL:
        SMART_REDRAW();
	switch(connect_state)
	{
	case -1:
	  connect_state=0;
        
	  SUBPROC((void*)free_socket);
	  break;
	case 0:
	  break;
	default:
	  connect_state=-1;
          f = fopen("0:\\4.log",A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0);
              fwrite(f,buffer,buffer_len,0);
              fclose(f,0);
	  SUBPROC((void*)end_socket);
	  break;
	}
        break;
      }
    }

  }
  return(1);
}

static unsigned short maincsm_name_body[140];
static const int minus11=-11;

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
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
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"NRSS");
}




int main(char *exename, char *fname)
{
  MAIN_CSM main_csm;
  zeromem(&main_csm, sizeof(MAIN_CSM));
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  return 0;
}
