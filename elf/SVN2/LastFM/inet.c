#include "..\inc\swilib.h"
#include "inet.h"
#include "urlwork.h"
#include "md5.h"

//#define NEEDINETLOG

static const char _CRLF_[]="\r\n";
static const char PERCENT_U[]="%u";
static const char PERCENT_D[]="%d";
static const char _OK_[]="OK";


extern char *strtok(char *s1, const char *s2);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

extern const char TEMP_FILE[];
extern const char USERNAME[];
extern const char PASSWORD[];

GBSTMR reconnect_tmr;

#define TMR_SECOND 216

static int enable_connect=0;

static int is_gprs_online=0;

static int is_handshaked=0;

static int DNR_ID=0;
static int DNR_TRIES=3;

static int connect_state=0;

static int sock=-1;
static int remote_closed=0;

static int sendq_l=0; //Длинна очереди для send
static char *sendq_p=NULL; //указатель очереди

static int recvq_l=0;
static char *recvq_p=NULL;

static const char HANDSHAKE_HOST[]="post.audioscrobbler.com";
static const int HANDSHAKE_PORT=80;
static char POST_HOST[256]="";
static unsigned short POST_PORT=0;

static char POST_URL[256]="";

#ifdef NEEDINETLOG
static void INETLOG(int do_mfree, const char *s)
{
  unsigned int ul;
  int f=fopen("4:\\LastFM_INET.log",A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,s,strlen(s),&ul);
    fclose(f,&ul);
  }
  if (do_mfree) mfree((void*)s);
}
#endif

static char SESSION_ID[33];
static char AUTHDATA[33];
static char PROCESSED_PWD[33];
static char TIMESTMP[33];

void genSessionKey(void)
{
  md5_state_t md5state;
  unsigned char md5pword[16];
  char clear[256];
  char *key=AUTHDATA;
  int j;
  strcpy(clear,PROCESSED_PWD);
  strcat(clear,TIMESTMP);
  md5_init(&md5state);
  md5_append(&md5state, (unsigned const char *)clear, (int)strlen(clear));
  md5_finish(&md5state, md5pword);
  memset(key,0,33);
  for (j = 0;j < 16;j++)
  {
    char a[3];
    sprintf(a, "%02x", md5pword[j]);
    key[2*j] = a[0];
    key[2*j+1] = a[1];
  }
}

static void setPassword(const char *pass)
{
  char *tmp;
  int j;
  md5_state_t md5state;
  unsigned char md5pword[16];
  md5_init(&md5state);
  md5_append(&md5state, (unsigned const char *)pass, (int)strlen(pass));
  md5_finish(&md5state, md5pword);
  if (!strlen(pass)) return;
  tmp=PROCESSED_PWD;
  memset(tmp,0,33);
  for (j = 0;j < 16;j++)
  {
    char a[3];
    sprintf(a, "%02x", md5pword[j]);
    tmp[2*j] = a[0];
    tmp[2*j+1] = a[1];
  }
  genSessionKey();
}

static void do_reconnect(void)
{
  void create_connect(void);
#ifdef NEEDINETLOG
  SUBPROC((void*)INETLOG,0,"do_reconnect()\r\n");
#endif
  if (is_gprs_online&&enable_connect)
  {
    DNR_TRIES=3;
    SUBPROC((void*)create_connect);
  }
}

static void create_connect(void)
{
  int ***p_res=NULL;
  void do_reconnect(void);
  const char *hostname;
  unsigned int ip;
  int err;

  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state = 0;
  remote_closed=0;	  
  GBS_DelTimer(&reconnect_tmr);
  if (!IsGPRSEnabled())
  {
    is_gprs_online=0;
    return;
  }
  {
    //Проверяем, а если что передать вообще
    unsigned int err;
    FSTATS stat;
    if (GetFileStats(TEMP_FILE,&stat,&err)==-1) return; //Нечего делать
    if (stat.size<=0) return;
  }
  DNR_ID=0;
  *socklasterr()=0;
  hostname=is_handshaked?POST_HOST:HANDSHAKE_HOST;
  ip=str2ip(hostname);
  if (ip!=0xFFFFFFFF)  
  {
    sa.ip=ip;
#ifdef NEEDINETLOG
    INETLOG(0,"IP_CONNECT\r\n");
#endif
    goto L_CONNECT;
  }  
#ifdef NEEDINETLOG
  INETLOG(0,"gethostbyname\r\n");
#endif
  err=async_gethostbyname(hostname,&p_res,&DNR_ID); //03461351 3<70<19<81
  if (err)
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (DNR_ID)
      {
#ifdef NEEDINETLOG
	INETLOG(0,"wait dnr...\r\n");
#endif
	return; //Ждем готовности DNR
      }
    }
    else
    {
#ifdef NEEDINETLOG
      INETLOG(0,"DNR fault!\r\n");
#endif
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
      return;
    }
  }
  if (p_res)
  {
    if (p_res[3])
    {
#ifdef NEEDINETLOG
      INETLOG(0,"DNR ok!\r\n");
#endif
      DNR_TRIES=0;
      sa.ip=p_res[3][0][0];
    L_CONNECT:
#ifdef NEEDINETLOG
      INETLOG(0,"Start socket...\r\n");
#endif
      sock=socket(1,1,0);
      if (sock!=-1)
      {
	sa.family=1;
	sa.port=htons(is_handshaked?POST_PORT:HANDSHAKE_PORT);
	if (connect(sock,&sa,sizeof(sa))!=-1)
	{
	  connect_state=1;
	}
	else
	{
	  remote_closed=1;
	  closesocket(sock);
	  sock=-1;
	  GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
	}
      }
      else
      {
	//Не осилили создания сокета, закрываем GPRS-сессию
	GPRS_OnOff(0,1);
      }
    }	
  }
  else
  {
    DNR_TRIES--;
  }
}

void ClearSendQ(void)
{
  mfree(sendq_p);
  sendq_p=NULL;
  sendq_l=NULL;
}

void ClearRecvQ(void)
{
  mfree(recvq_p);
  recvq_p=NULL;
  recvq_l=NULL;
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
}

//Буферизированая посылка в сокет, c последующим освобождением указателя
static void bsend(int len, void *p)
{
  int i;
  int j;
  if (connect_state<2)
  {
    mfree(p);
    return;
  }
  if (p)
  {
    //Проверяем, не надо ли добавить в очередь
    if (sendq_p)
    {
      //Есть очередь, добавляем в нее
      memcpy((sendq_p=realloc(sendq_p,sendq_l+len))+sendq_l,p,len);
      mfree(p);
      sendq_l+=len;
      return;
    }
    sendq_p=p;
    sendq_l=len;
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
      return; //Ждем сообщения ENIP_BUFFER_FREE1
    }
  }
  mfree(sendq_p);
  sendq_p=NULL;
}

static void get_answer(void)
{
  char rb[1024];
  int i=recv(sock,rb,sizeof(rb),0);
  if (i<=0) return;
  memcpy((recvq_p=realloc(recvq_p,recvq_l+i+1))+recvq_l,rb,i);
  recvq_l+=i;
}

static void SendHandShake()
{
  char *hst=malloc(1024);
  extern unsigned long TimeDate2Long(void);
  unsigned long tt=TimeDate2Long();
  
  extern const int TIMEZONESIGN;
  extern const unsigned int TIMEZONE;
  
  sprintf(TIMESTMP,PERCENT_U,(TIMEZONESIGN?tt-3600*TIMEZONE:tt+3600*TIMEZONE)+946684800L);
  setPassword(PASSWORD);
  strcpy(hst,"GET /?hs=true&p=1.2&c=lmd&v=1.1&u=");
  urlcat(hst,USERNAME);
  strcat(hst,"&t=");
  strcat(hst,TIMESTMP);
  strcat(hst,"&a=");
  strcat(hst,AUTHDATA);
  strcat(hst,"\r\nHost: post.audioscrobbler.com\r\n\r\n");
#ifdef NEEDINETLOG
  INETLOG(0,hst);
#endif
  bsend(strlen(hst),hst);
}

int stricmp(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

static void _ParseHandShake()
{
  const char seps[] = " \n\r";
  char *response;
  char *submiturl;
  if (!recvq_l)
  {
#ifdef NEEDINETLOG
    INETLOG(0,"No bytes on handshake recived!");
#endif
    return;
  }
  recvq_p[recvq_l]=0;
#ifdef NEEDINETLOG
  INETLOG(0,recvq_p);
#endif
  response=strstr(recvq_p,"\r\n\r\n");
  if (!response)
  {
    response=strtok(recvq_p,seps);
  }
  else
  {
    response=strtok(response,seps);
  }
  if (stricmp(_OK_,response)!=0) return;
  strncpy(SESSION_ID,strtok(NULL,seps),32);
  strtok(NULL,seps); //Skip NP
  submiturl=strtok(NULL,seps);
  if (strncmp(submiturl,"http://",7)==0) submiturl+=7;
  strncpy(POST_HOST,strtok(submiturl,":"),255);
  POST_PORT=strtoul(strtok(NULL,"/"),NULL,10);
  strncpy(POST_URL,strtok(NULL,""),255);
#ifdef NEEDINETLOG
  INETLOG(0,_CRLF_);
  INETLOG(0,POST_HOST);
  INETLOG(0,POST_URL);
#endif
  is_handshaked=3;
}

static unsigned int STRIP_SIZE;

static int _SendSubmit()
{
  char s2[32];

  int f;
  unsigned int err;
  int fsize;
  char *buf;
  char *outp;
  char *req;
  FSTATS stat;
  int c;

  int sn=0;
  char *PLOG;
  char *SUBMIT_DATA;

  if (GetFileStats(TEMP_FILE,&stat,&err)==-1)
    return 0;

  if ((fsize=stat.size)<=0)
    return 0;
 
  if ((f=fopen(TEMP_FILE,A_ReadOnly+A_BIN,P_READ,&err))==-1)
  return 0;
  
  SUBMIT_DATA=outp=malloc(512+fsize);
  buf=PLOG=malloc(fsize+1);
  
  buf[fread(f,buf,fsize,&err)]=0;
  fclose(f,&err);
  
//  strcpy(outp,"u=");
//  urlcat(outp,USERNAME);
  strcpy(outp,"s=");
  strcat(outp,SESSION_ID);
  outp+=strlen(outp);
  //Теперь все прочитано в буфер
  while(sn<1)
  {
    while((c=*buf++)>=32)
    {
      *outp++=c;
      if (c=='[')
      {
	*outp++=sn+'0';
      }
    }
    sn++;
    if (!c) break;
  }
  *outp=0;
  STRIP_SIZE=buf-PLOG;
  mfree(PLOG);
  
  if (!sn)
  {
    mfree(SUBMIT_DATA);
    return 0;
  }
  req=malloc(strlen(POST_URL)+strlen(POST_HOST)+1024+strlen(SUBMIT_DATA));
  strcpy(req,"POST /");
  strcat(req,POST_URL);
  strcat(req," HTTP/1.1\r\nContent-type: application/x-www-form-urlencoded\r\nHost: ");
  strcat(req,POST_HOST);
//  sprintf(req+strlen(req),":%d",POST_PORT);
  strcat(req,"\r\nUser-Agent: lmd v1.1");
  strcat(req,"\r\nContent-Length: ");
  sprintf(s2,PERCENT_D,strlen(SUBMIT_DATA));
  strcat(req,s2);
//  strcat(req,"\r\nAccept: */*\r\nConnection: Close\r\n\r\n");
  strcat(req,"\r\nCache-Control: no-cache\r\n\r\n");
  strcat(req,SUBMIT_DATA);
  mfree(SUBMIT_DATA);
#ifdef NEEDINETLOG
  INETLOG(0,req);
#endif
  bsend(strlen(req),req);
#ifdef NEEDINETLOG
  INETLOG(0,_CRLF_);
#endif
  return 1;
}

static void SendSubmit(void)
{
  if (!_SendSubmit())
  {
    remote_closed=1; //Потому как нех ;)
    enable_connect=0;
    end_socket();
  }
}

static void StripLog()
{
  //Стрипаем файл лога
  int f;
  unsigned int err;
  int fsize=0;
  char *buf=NULL;
  FSTATS stat;
  if (GetFileStats(TEMP_FILE,&stat,&err)==-1) goto L_REWRITE;
  if (stat.size<=0) goto L_REWRITE;
  fsize=stat.size;
  if ((f=fopen(TEMP_FILE,A_ReadOnly+A_BIN,P_READ,&err))==-1) goto L_REWRITE;
  buf=malloc(fsize);
  fread(f,buf,fsize,&err);
  fclose(f,&err);
L_REWRITE:
  f=fopen(TEMP_FILE,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err);
  if (f!=-1)
  {
    if (buf)
    {
      if ((fsize-=STRIP_SIZE)>0)
      {
	fwrite(f,buf+STRIP_SIZE,fsize,&err);
      }
    }
    fclose(f,&err);
  }
  mfree(buf);
  if (fsize>0)
  {
    is_handshaked=3;
    enable_connect=1;
    GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*20,do_reconnect);    
  }
}

static void _ParseSubmit()
{
  char *response;
  char *body;
  const char seps[] = " \n\r";
  int is_chunked=0;
  if (!recvq_l)
  {
#ifdef NEEDINETLOG
    INETLOG(0,"No bytes on submit recived!");
#endif
    is_handshaked--;
    return;
  }
  recvq_p[recvq_l]=0;
#ifdef NEEDINETLOG
  INETLOG(0,recvq_p);
#endif
  response=recvq_p;
  body=strstr(response,"\r\n\r\n");
  if (!body)
  {
  L_ERR:
#ifdef NEEDINETLOG
    INETLOG(0,"Incorrect HTTP answer!");
#endif
    is_handshaked--;
    return;
  }
  *body=0;
  body+=4;
  while(response=strtok(response,_CRLF_))
  {
    if (stricmp(response,"Transfer-Encoding: chunked")==0) is_chunked=1;
    response=NULL;
  }
  if (is_chunked)
  {
    //Убираем чанки
    char *p=body;
    char *last=recvq_p+recvq_l;
    char *np;
    int c;
    while((c=*p)!='0')
    {
      if ((c>='0')&&(c<='9'))
      {
	c-='0';
      }
      else
      {
	if ((c>='A')&&(c<='F'))
	{
	  c-=('A'-10);
	}
	else
	{
	  if ((c>='a')&&(c<='f'))
	  {
	    c-=('a'-10);
	  }
	  else goto L_ERR;
	}
      }
      np=strstr(p+1,_CRLF_);
      if (!np) goto L_ERR;
      np+=2;
      memcpy(p,np,(last-np));
      p+=c;
      if (p>last) goto L_ERR;
      np=strstr(p,_CRLF_);
      if (!np) goto L_ERR;
      np+=2;
      memcpy(p,np,(last-np));
    }
#ifdef NEEDINETLOG
    INETLOG(0,body);
#endif
  }
  body=strtok(body,seps);
  if (!stricmp(_OK_,body))
  {
    StripLog();
  }
  else
  {
    enable_connect=0;
  }
}

static void ParseHandShake(void)
{
  _ParseHandShake();
  SUBPROC((void *)ClearSendQ);
  SUBPROC((void *)ClearRecvQ);
  if (enable_connect) GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*(is_handshaked?2:120),do_reconnect);
}

static void ParseSubmit(void)
{
  _ParseSubmit();
  SUBPROC((void *)ClearSendQ);
  SUBPROC((void *)ClearRecvQ);
  if (enable_connect) GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*(is_handshaked?2:120),do_reconnect);
}

static void stop_socket(void)
{
#ifdef NEEDINETLOG
  INETLOG(0,"\r\n!!! Stop socket !!!\r\n");
#endif
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
    sock=-1;
  }
  if (enable_connect) GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*120,do_reconnect);
}

int ParseSocketMsg(GBS_MSG *msg)
{
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    switch((int)msg->data0)
    {
    case LMAN_DISCONNECT_IND:
#ifdef NEEDINETLOG
      SUBPROC((void*)INETLOG,0,"LMAN_DISCONNECT_IND\r\n");
#endif
      is_handshaked=0;
      is_gprs_online=0;
      return(1);
    case LMAN_CONNECT_CNF:
#ifdef NEEDINETLOG
      SUBPROC((void*)INETLOG,0,"LMAN_CONNECT_CNF\r\n");
#endif
      is_handshaked=0;
      is_gprs_online=1;
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
      return(1);
    case ENIP_DNR_HOST_BY_NAME:
      if ((int)msg->data1==DNR_ID)
      {
#ifdef NEEDINETLOG
	SUBPROC((void*)INETLOG,0,"ENIP_DNR_HOST_BY_NAME\r\n");
#endif
	if (DNR_TRIES) SUBPROC((void *)create_connect);
      }
      return(1);
    }
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
//      if ((((unsigned int)msg->data0)>>28)==0xA)
//      {
//	//Принят пакет
//	ProcessPacket((TPKT *)msg->data0);
//	return(0);
//      }
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
#ifdef NEEDINETLOG
	SUBPROC((void*)INETLOG,0,"ENIP_SOCK_CONNECTED\r\n");
#endif
	if (connect_state==1)
	{
	  connect_state=2;
	  //Соединение установленно, посылаем пакет login
	  if (is_handshaked)
	  {
	    SUBPROC((void*)SendSubmit);
	  }
	  else
	  {
	    SUBPROC((void*)SendHandShake);
	  }
	}
	else
	{
	}
	break;
      case ENIP_SOCK_DATA_READ:
#ifdef NEEDINETLOG
	SUBPROC((void*)INETLOG,0,"ENIP_SOCK_DATA_READ\r\n");
#endif
	if (connect_state>=2)
	{
	  //Если посылали send
	  SUBPROC((void *)get_answer);
	  //REDRAW();
	}
	else
	{
	}
	break;
      case ENIP_BUFFER_FREE:
	if (!sendq_p)
	{
//	  ShowMSG(1,(int)"Illegal ENIP_BUFFER_FREE!");
//	  SUBPROC((void *)end_socket);
	}
	else
	{
	  //Досылаем очередь
	  SUBPROC((void *)bsend,0,0);
	}
	break;
      case ENIP_BUFFER_FREE1:
	if (!sendq_p)
	{
//	  ShowMSG(1,(int)"Illegal ENIP_BUFFER_FREE1!");
//	  SUBPROC((void *)end_socket);
	}
	else
	{
	  //Досылаем очередь
	  SUBPROC((void *)bsend,0,0);
	}
	break;
      case ENIP_SOCK_REMOTE_CLOSED:
	remote_closed=1;
#ifdef NEEDINETLOG
	SUBPROC((void*)INETLOG,0,"ENIP_SOCK_REMOTE_CLOSED\r\n");
#endif
	//Закрыт со стороны сервера
	if (connect_state)
	  SUBPROC((void *)end_socket);
	break;
      case ENIP_SOCK_CLOSED:
#ifdef NEEDINETLOG
	SUBPROC((void*)INETLOG,0,"ENIP_SOCK_CLOSED\r\n");
#endif
	connect_state=0;
	if (remote_closed)
	{
	  sock=-1;
	  if (is_handshaked)
	  {
	    SUBPROC((void*)ParseSubmit);
	  }
	  else
	  {
	    SUBPROC((void*)ParseHandShake);
	  }
	}
	else
	{
	  SUBPROC((void*)stop_socket);
	}
	break;
      }
    }
  }
  return(1);
}

void StartINET(void)
{
  if ((!strlen(USERNAME))||(!strlen(PASSWORD))) return;
  if (!connect_state)
  {
    if (IsGPRSEnabled()) is_gprs_online=1;
    else
    {
      is_gprs_online=0;
      return;
    }
    enable_connect=1;
    do_reconnect();
  }
}
