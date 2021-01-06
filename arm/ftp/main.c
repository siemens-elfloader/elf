#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "conf_loader.h"
#include "config_data.h"
#include "strings.h"
#include "main.h"

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
  char host[64]="wen.ru";
  char rss_host[64];
  unsigned int rss_port=21;
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
  
  get_host_from_url(rss_host,host);

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
int recv_len;
char *buffer=0;
void savebuf()
{
  int f = fopen("0:\\log.txt",A_WriteOnly+A_BIN+A_Create,P_WRITE,0);
  lseek(f,0,S_END,0,0);
  fwrite(f,buffer,strlen(buffer),0);
  fclose(f,0);
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
      buffer=realloc(buffer, recv_len+j+1);
      buffer[recv_len+j]=0;
      memcpy(buffer+recv_len, buf, j);
      recv_len+=j;
      ShowMSG(1,(int)"sds");
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
      j=recv_len-(end_answer-recv_buf);
      mfree(buffer);
      buffer=NULL;
      recv_len=0;
      if (!j) return; //Нет данных, нечего посылать
      buffer=malloc(j+1);
      buffer[j]=0;
      memcpy(buffer, end_answer, j);
      recv_len=j;
    }
    savebuf();
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
int ftp_state=0;

void send_req()
{
 
  int len;
  char req_buf[256];
  char command[256];
 
  
    switch(ftp_state)
  {
  case 0: sprintf(command," ");
  case 1: sprintf(command,"USER ftptest\r\n");
  case 2: sprintf(command,"PASS 666666\n\r");
  }
  
 

  len=snprintf(req_buf,255,"%s\r\n",command);
  send_answer(req_buf, len);
}






static void OnRedraw(MAIN_GUI *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  unsigned long RX=ALLTOTALRECEIVED; unsigned long TX=ALLTOTALSENDED;
  DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  wsprintf(data->ws1,
           "State: %d\n"
             "Rx: %db, Tx: %db\n"
               "Queue: %db\n"
                 "%t\n"
                   "%s\n"
                     "ftpstate: %d",connect_state,RX,TX,send_buf_len,logmsg,buffer,ftp_state);
  DrawString(data->ws1,3,3+YDISP,scr_w-4,scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
             FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
 // wsprintf(data->ws1,_percent_t,rss_first?"List":_empty_str);
 // DrawString(data->ws1,3,scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),scr_w>>1,scr_h-4,
          //   FONT_MEDIUM_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
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

    case LEFT_SOFT:
ftp_state++;
send_req();
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

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"NRSS config updated!");
      InitConfig();
    }
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
          sprintf(logmsg,"end");
	  SUBPROC((void*)free_socket);
	  break;
	case 0:
	  break;
	default:
	  connect_state=-1;
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
  InitConfig();
  buffer=malloc(256);
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  return 0;
}
