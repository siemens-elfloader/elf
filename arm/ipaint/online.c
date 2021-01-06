#include "online.h"

void create_connect()
{

  char rss_host[64];
  unsigned int rss_port=80;
  int ***p_res=NULL;
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state = 0;
  unsigned int ip;
  if (!IsGPRSEnabled())
  
    return;
  

  *socklasterr()=0;
  
 // get_host_from_url(rss_host,frss->load_url);


  ip=str2ip(rss_host);
  if (ip!=0xFFFFFFFF)
  {
    sa.ip=ip;
  }else
      sa.ip=p_res[3][0][0];
  
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
	}
      }
     
}

void send_req(int dummy, RSS_FILE *frss)
{
 /* char *p;
  int len;
  char host[64], get_path[64];
  char req_buf[256];
  
  get_path_from_url(get_path, frss->load_url);
  get_host_from_url(host, frss->load_url);

  len=snprintf(req_buf,255,"GET %s"
               " HTTP/1.0\r\nHost: %s\r\n\r\n", get_path, host);
  p=malloc(len+1);
  strcpy(p, req_buf);
  send_answer(p, len);*/
}
