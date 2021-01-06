#include "..\inc\swilib.h"
#include "internet.h"
#include "main.h"
extern int gui_mode;
char logmsg[256];

inline void SMART_REDRAW(void){if(gui_mode)DirectRedrawGUI();}
 int sock;
 int connect_state;
 int is_gprs_online;
 int DNR_TRIES;
 int DNR_ID;
 int ALLTOTALRECEIVED;
 int ALLTOTALSENDED;


 char *buffer;
 int buffer_len=0;


 char *recv_buf=NULL;
 int recv_buf_len=0;

 char *send_buf=NULL;
 int send_buf_len=0;

 int receive_mode;
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

 const char HOST[32]="perk11.info/elf/rss.php?count=5";
 const unsigned int PORT=80;
void create_connect()
{
  char host[64];
  unsigned int port=PORT;
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
  
  get_host_from_url(host,HOST);

  sprintf(logmsg, "Connect to: %s Using port: %d", host, port);
  SMART_REDRAW();
  ip=str2ip(host);
  if (ip!=0xFFFFFFFF)
  {
    sa.ip=ip;
    strcpy(logmsg, "connect by ip");
    goto L_CONNECT;
  }
  err=async_gethostbyname(host,&p_res,&DNR_ID); //03461351 3<70<19<81
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
	sa.port=htons(port);
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

void free_recv_buf(void)
{
  char *p=recv_buf;
  recv_buf_len=0;
  recv_buf=NULL;
  mfree(p);
}


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
}

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
      return; //Ждем сообщения ENIP_BUFFER_FREE1
    }
  }
  p=send_buf;
  send_buf=NULL;
  mfree(p);
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
}
void free_buffers(void)
{
  free_recv_buf();
  free_send_buf();
}

void free_socket(void)
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
  char host[64], get_path[64];
  char req_buf[256];
  
  get_path_from_url(get_path, HOST);
  get_host_from_url(host, HOST);

  len=snprintf(req_buf,255,"GET %s"
               " HTTP/1.0\r\nHost: %s\r\n\r\n", get_path, host);
  p=malloc(len+1);
  strcpy(p, req_buf);
  send_answer(p, len);
}
