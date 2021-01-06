#include "../inc/swilib.h"
#include "inet.h"
#include "local_ipc.h"
#include "string_works.h"
#include "view.h"
#include "history.h"
#include "lang.h"

#ifndef NEWSGOLD
#define SEND_TIMER
#endif

#define TMR_SECOND(A) (1300*A/6)

extern WSHDR *ws_console;

extern volatile int TERMINATED;
extern volatile int STOPPED;

volatile static int is_gprs_online=1;

static int DNR_ID=0;
static int DNR_TRIES=3;

int connect_state=0;

static int sock=-1;

static int sendq_l=0; 
static char *sendq_p=NULL;

static int recvq_l=0;
static char *recvq_p=NULL;

char OM_POST_HOST[32];
unsigned int OM_POST_PORT;

extern const int IP_CHOOSE;
extern const char OM_POST_HOST1[32];
extern const unsigned int OM_POST_PORT1;
extern const char OM_POST_HOST2[32];
extern const unsigned int OM_POST_PORT2;
extern const char OM_POST_HOST3[32];
extern const unsigned int OM_POST_PORT3;
extern const char OM_POST_HOST4[32];
extern const unsigned int OM_POST_PORT4;

void clooseip()
{
switch(IP_CHOOSE)
{
case 0:
  strncpy(OM_POST_HOST,OM_POST_HOST1,32);
  OM_POST_PORT=OM_POST_PORT1;
  break;
case 1:
  strncpy(OM_POST_HOST,OM_POST_HOST2,32);
  OM_POST_PORT=OM_POST_PORT2;
  break;
case 2:
  strncpy(OM_POST_HOST,OM_POST_HOST3,32);
  OM_POST_PORT=OM_POST_PORT3;
  break;
case 3:
  strncpy(OM_POST_HOST,OM_POST_HOST4,32);
  OM_POST_PORT=OM_POST_PORT4;
  break;
}
}

static int receive_mode;

static char *URL;
static char *FNCACHE;

void SmartREDRAW(void)
{
  extern int ENABLE_REDRAW;
  if (ENABLE_REDRAW) REDRAW();
}

static void create_connect(void)
{
  int ***p_res=NULL;
  void do_reconnect(void);
  const char *hostname;
  unsigned int ip;
  int err;
  clooseip();
  SOCK_ADDR sa;
  connect_state = 0;
  receive_mode=0;
  if (!IsGPRSEnabled())
  {
    is_gprs_online=0;
    return;
  }
  DNR_ID=0;
  *socklasterr()=0;
  hostname=OM_POST_HOST;
  ip=str2ip(hostname);
  if (ip!=0xFFFFFFFF)  
  {
    sa.ip=ip;
    LockSched();
    ascii2ws(ws_console,lgpData[LGP_IpConnect]);
    UnlockSched();
    SmartREDRAW();
    goto L_CONNECT;
  }  
  LockSched();
  ascii2ws(ws_console,lgpData[LGP_GetHostByName]);
  UnlockSched();
  SmartREDRAW();
  err=async_gethostbyname(hostname,&p_res,&DNR_ID); //03461351 3<70<19<81
  if (err)
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (DNR_ID)
      {
        LockSched();
        ascii2ws(ws_console,lgpData[LGP_WaitDNR]);
        UnlockSched();
        SmartREDRAW();
        return; 
            }
          }
          else
          {
            LockSched();
            ascii2ws(ws_console,lgpData[LGP_FaultDNR]);
            ShowMSG(1,(int)lgpData[LGP_FaultDNR]);
            UnlockSched();
            return;
          }
        }
        if (p_res)
        {
          if (p_res[3])
          {
            LockSched();
            ascii2ws(ws_console,lgpData[LGP_OkDNR]);
            UnlockSched();
            SmartREDRAW();
            DNR_TRIES=0;
            sa.ip=p_res[3][0][0];
          L_CONNECT:
            LockSched();
            ascii2ws(ws_console,lgpData[LGP_OpenSocket]);
            UnlockSched();
            SmartREDRAW();
            sock=socket(1,1,0);
            if (sock!=-1)
            {
        sa.family=1;
        sa.port=htons(OM_POST_PORT);
        if (connect(sock,&sa,sizeof(sa))!=-1)
        {
          connect_state=1;
        }
        else
        {
          int s=sock;
          sock=-1;
          closesocket(s);
          LockSched();
          ascii2ws(ws_console,lgpData[LGP_ConnectFault]);
          ShowMSG(1,(int)lgpData[LGP_ConnectFault]);
          UnlockSched();
        }
      }
      else
      {
        GPRS_OnOff(0,1);
       }
    }	
  }
  else
  {
    DNR_TRIES--;
  }
}

#ifdef SEND_TIMER
static GBSTMR send_tmr;
#endif

static void ClearSendQ(void)
{
  mfree(sendq_p);
  sendq_p=NULL;
  sendq_l=NULL;
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

static void ClearRecvQ(void)
{
  mfree(recvq_p);
  recvq_p=NULL;
  recvq_l=NULL;
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

static void free_socket(void)
{
  sock=-1;
  connect_state=0;
  ClearSendQ();
  ClearRecvQ();
  freegstr(&URL);
  mfree(FNCACHE);
  FNCACHE=NULL;
  STOPPED=1;
  ws_console->wsbody[0]=0;
  SmartREDRAW();
}

#ifdef SEND_TIMER
static void resend(void)
{
  void bsend(int len, void *p);
  SUBPROC((void*)bsend,0,0);
}
#endif


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
    if (sendq_p)
    {   
    memcpy((sendq_p=realloc(sendq_p,sendq_l+len))+sendq_l,p,len);
      mfree(p);
      sendq_l+=len;
      return;
    }
    sendq_p=p;
    sendq_l=len;
  }
  while((i=sendq_l)!=0)
  {
    if (i>0x400) i=0x400;
    j=send(sock,sendq_p,i,0);
    if (j<0)
    {
      j=*socklasterr();
      if ((j==0xC9)||(j==0xD6))
      {
	      return; 
      }
      else
      {

        //	LockSched();
        //	ShowMSG(1,(int)"BM: Send error!");
        //	UnlockSched();
        //	end_socket();
        return;
      }
    }
    memcpy(sendq_p,sendq_p+j,sendq_l-=j); 
    if (j<i)
    {

#ifdef SEND_TIMER
      GBS_StartTimerProc(&send_tmr,TMR_SECOND(5),resend);
#endif
      return; 
    }
  }
  mfree(sendq_p);
  sendq_p=NULL;
}

static void writecache(void *buf, int len)
{
  unsigned int ul;
  int f;
  if (!FNCACHE) return;
  f=fopen(FNCACHE,A_ReadWrite+A_Create+A_Append+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,buf,len,&ul);
    fclose(f,&ul);
  }
}

static void get_answer(void)
{
  char rb[1024];
  extern const char ipc_my_name[];
  IPC_REQ *sipc;
  int i=recv(sock,rb,sizeof(rb),0);
  if (i<=0) return;
  if (receive_mode)
  {
    writecache(rb,i);
    LockSched();
    if ((!TERMINATED)&&(!STOPPED))
    {
      sipc=malloc(sizeof(IPC_REQ));
      sipc->name_to=ipc_my_name;
      sipc->name_from=ipc_my_name;
      sipc->data=malloc(i+4);
      *((int *)(sipc->data))=i;
      memcpy(((char *)(sipc->data))+4,rb,i);
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_DATA_ARRIVED,sipc);
    }
    UnlockSched();
  }
  else
  {
    char *end_answer;
    memcpy((recvq_p=realloc(recvq_p,recvq_l+i+1))+recvq_l,rb,i);
    recvq_l+=i;
    recvq_p[recvq_l]=0;
    if (!(end_answer=strstr(recvq_p,"\r\n\r\n"))) return;
    receive_mode=1; 
    end_answer+=2;
    *end_answer=0;
    LockSched();
    wsprintf(ws_console,recvq_p);
    UnlockSched();
    SmartREDRAW();
    end_answer+=2; 
    i=recvq_l-(end_answer-recvq_p);
    if (!i) return;
    writecache(end_answer,i);
    LockSched();
    if ((!TERMINATED)&&(!STOPPED))
    {
      sipc=malloc(sizeof(IPC_REQ));
      sipc->name_to=ipc_my_name;
      sipc->name_from=ipc_my_name;
      sipc->data=malloc(i+4);
      *((int *)(sipc->data))=i;
      memcpy(((char *)(sipc->data))+4,end_answer,i);
      GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_DATA_ARRIVED,sipc);
    }
    UnlockSched();
    ClearRecvQ();
  }
}

static void SendPost(void)
{
  extern char AUTH_PREFIX[];
  extern char AUTH_CODE[];
  extern char *from_url;
  extern char *goto_params;
  clooseip();
  char *buf;
  int buf_max_sz=1024+strlen(URL);
  if (from_url)
    buf_max_sz+=strlen(from_url);
  if (goto_params)
    buf_max_sz+=strlen(goto_params);
  buf=malloc(buf_max_sz);

  int content_len=0;
  int l;
  int i, j;
  char *content=NULL;
  char *req;
  
  sprintf(buf,"k=image/jpeg");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"o=280");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;
  
  sprintf(buf,"u=/obml/%s",URL);
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"q=%s",lgpData[LGP_LangCode]);
  //sprintf(buf,"q=ru");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"v=Opera Mini/2.0.4509/hifi/woodland/%s",lgpData[LGP_LangCode]);
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;
  
  sprintf(buf,"i=Opera/8.01 (J2ME/MIDP; Opera Mini/2.0.4509/1630; %s; U; ssr)",lgpData[LGP_LangCode]);
  //sprintf(buf,"i-ua=Opera/9.10 (Windows NT 5.1; U; ru)");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"s=-1");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"n=1");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  //sprintf(buf,"A=CLDC-1.0");
  sprintf(buf,"A=CLDC-1.1");//
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"B=MIDP-2.0");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"C=j2me");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"D=%s",lgpData[LGP_LangCode]);
  //sprintf(buf,"D=ru");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"E=GB2312");
  //sprintf(buf,"E=ISO-8859-1");
  //sprintf(buf,"E=ISO8859_1");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;
  
  extern const int PIC_QUALITY;
  switch(PIC_QUALITY)
  {
  case 0:
  default:
    i=2;
    j=0;
    break;
  case 1:
    i=0;
    j=0;
    break;
  case 2:
    i=1;
    j=0;
    break;
  case 3:
    i=1;
    j=1;
    break;
  }
  
  extern const int JAVA_HEAP_SIZE;
  sprintf(buf,"d=w:%d;h:%d;c:65536;m:%d;i:%d;q:%d;f:0;j:0;l:256",ScreenW(),ScreenH(),JAVA_HEAP_SIZE*1024,i,j);
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"c=%s",AUTH_CODE);
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"h=%s",AUTH_PREFIX);
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;
  
  if (from_url)
  {
    sprintf(buf,"f=%s",from_url);
    strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;
    mfree(from_url);
    from_url=0;
  }
  
  sprintf(buf,"g=1");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"b=mod2.04");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  
  sprintf(buf,"y=%s",lgpData[LGP_LangCode]);
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"t=-1");
  //sprintf(buf,"t=2");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"w=1;1");
  //sprintf(buf,"w=1;0");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  sprintf(buf,"e=def");
  strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;

  if (goto_params)
  {
    sprintf(buf,"j=opf=1%s",goto_params);
    strcpy((content=realloc(content,content_len+(l=strlen(buf)+1)))+content_len,buf);content_len+=l;
    mfree(goto_params);
    goto_params=0;
  }
  
  sprintf(buf,
          "POST / HTTP/1.1\r\n"
          "Connection: close\r\n"
	        "Content-Type: application/xml\r\n"
		      "Content-Length: %d\r\n"
		      "Host: %s:%d\r\n"
		      "\r\n",
		      content_len,OM_POST_HOST,OM_POST_PORT);
  req=malloc(l=(i=strlen(buf))+content_len);
  memcpy(req,buf,i);
  memcpy(req+i,content,content_len);
  mfree(content);
  
  //DEBUGV(req,l);
  
  bsend(l,req);
  freegstr(&URL);
  mfree(buf);
}

int ParseSocketMsg(GBS_MSG *msg)
{
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
        ascii2ws(ws_console,lgpData[LGP_AnswerDNR]);
        SmartREDRAW();
        if (DNR_TRIES) SUBPROC((void *)create_connect);
      }
      return(1);
    }
    if ((int)msg->data1==sock)
    {
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        ascii2ws(ws_console,lgpData[LGP_Connected]);
        SmartREDRAW();
        if (connect_state==1)
        {
          connect_state=2;
          SUBPROC((void*)SendPost);
        }
        break;
      case ENIP_SOCK_DATA_READ:
        ascii2ws(ws_console,lgpData[LGP_DataReceived]);
        SmartREDRAW();
        if (connect_state>=2)
        {
          connect_state=3;
          SUBPROC((void *)get_answer);
        }
        break;
      case ENIP_BUFFER_FREE:
      case ENIP_BUFFER_FREE1:
        SUBPROC((void *)bsend,0,0);
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        ascii2ws(ws_console,lgpData[LGP_RemoteClosed]);
        SmartREDRAW();
        goto ENIP_SOCK_CLOSED_ALL;
      case ENIP_SOCK_CLOSED:
        ascii2ws(ws_console,lgpData[LGP_LocalClosed]);
        SmartREDRAW();
      ENIP_SOCK_CLOSED_ALL:
        switch(connect_state)
        {
        case -1:
          connect_state=0;
          SUBPROC((void*)free_socket);
          //ShowMSG(1,(int)"BM: Socket closed");
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

void StartINET(const char *url, char *fncache)
{
  unsigned int err;
  if (connect_state)
  {
    LockSched();
    ShowMSG(1,(int)lgpData[LGP_InetBusy]);
    UnlockSched();
  ERR:
    mfree(fncache);
    return;
  }
  if (!IsGPRSEnabled())
  {
    LockSched();
    ShowMSG(1,(int)lgpData[LGP_EnableGPRS]);
    UnlockSched();
    STOPPED=1;
    goto ERR;
  }
  if (!url)
  {
    STOPPED=1;
    goto ERR;
  }
  AddURLToHistory(url+2);
  URL=globalstr(url);
  if ((FNCACHE=fncache))
  {
    unlink(fncache,&err);
  }
  SUBPROC((void*)create_connect);
}

void StopINET(void)
{
  end_socket();
  free_socket();
}
