/*
  Проект SieGet Downloader
                          */

#include "include.h"
#include "socket.h"
#include "log.h"

#ifdef SOCK_SEND_TIMER
  Socket * Socket::Top = NULL;
#endif

int Socket::GlobalTx = 0;
int Socket::GlobalRx = 0;

//Проверить процесс (сокеты только в хелпере)
inline int CheckCepId()
{
  if (GBS_GetCurCepid()==MMI_CEPID) return 1;
  return 0;
}

//---------------------------------------------------

//Соединить сокет по ip и порту
void Socket::Connect(int ip, short port)
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if(socket_id < 0)
  {
    onError(SOCK_ERROR_INVALID_SOCKET);
    return;
  }
  
  SOCK_ADDR sa;
  sa.family=1;
  sa.port=htons(port);
  sa.ip=ip;
  if (connect(socket_id, &sa, sizeof(sa))==-1)
  {
    onError(SOCK_ERROR_CONNECTING);
    return;
  }
  socket_state = SOCK_CREATED;
}


#ifdef SOCK_SEND_TIMER
void sock_resend(Socket * sock)
{
  sock->Send(NULL, NULL);
}

static void _resend(void)
{
  SUBPROC((void *)sock_resend, Socket::Top, NULL, NULL);
}
#endif


//Отправить данные
void Socket::Send(const char * data, int size)
{
  int send_size = NULL;
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if (data)
  {
    if (send_q) // Есть очередь
    {
      send_q = (char *)realloc(send_q, send_q_size + size);
      memcpy(send_q + send_q_size, data, size);
      send_q_size += size;
#ifdef SOCK_SEND_TIMER
      SUBPROC((void *)sock_resend, this);
#endif
      return;
    }
    send_q = new char[size + 1];
    memcpy(send_q, data, size);
    send_q_size = size;
  }
  while((send_size = send_q_size) != 0)
  {
    if (send_size > 0x400)
      send_size = 0x400;
    int send_res = send(socket_id, send_q, send_size, 0);
    if (send_res < 0)
    {
      int err = * socklasterr();
      if (err == 0xC9 || err == 0xD6)
      {
	return; //Видимо, надо ждать сообщения ENIP_BUFFER_FREE
      }
      else
      {
        onError(SOCK_ERROR_SENDING);
	return;
      }
    }
    GlobalTx += send_res;
    Tx += send_res;
    send_q_size -= send_res;

    memcpy(send_q, send_q + send_res, send_q_size); //Удалили переданное
    if (send_res < send_size)
    {
      //Передали меньше чем заказывали
#ifdef SOCK_SEND_TIMER
      Top = this;
      GBS_StartTimerProc(&send_tmr, _tmr_second(5), _resend);
#endif
      return; //Ждем сообщения ENIP_BUFFER_FREE1
    }
  }

}

//Принять данные
int Socket::Recv(char * data, int size)
{
  int nrecv = recv(socket_id, (char *)data, size, 0);
  if(nrecv)
  {
    GlobalRx += nrecv;
    Rx += nrecv;
    return nrecv;
  }
  return 0;
}

//Закрыть сокет
void Socket::Close()
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if(socket_id < 0)
  {
    onError(SOCK_ERROR_INVALID_SOCKET);
    return;
  }
  shutdown(socket_id, 2);
  closesocket(socket_id);
  socket_state = SOCK_UNDEF;
#ifdef SOCK_SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

//Создать сокет
void Socket::Create()
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }
  socket_id = socket(1,1,0);
  if(socket_id<0)
  {
    onError(SOCK_ERROR_CREATING);
    return;
  }

  socket_state = SOCK_CREATED;
  onCreate();
}

// Создание сокета
Socket::Socket()
{
  socket_state = SOCK_UNDEF;
  socket_id = -1;

  Tx = 0;
  Rx = 0;
  
  log = new Log;
  send_q = NULL;
  send_q_size = NULL;
}

// Уничтожение сокета
Socket::~Socket()
{
  delete log;
  _safe_delete(send_q);
}

