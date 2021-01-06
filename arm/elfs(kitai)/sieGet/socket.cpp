/*
  ������ SieGet Downloader
                          */

#include "..\inc\swilib.h"
#include "socket.h"
#include "log.h"

int Socket::GlobalTx = 0;
int Socket::GlobalRx = 0;

//��������� ������� (������ ������ � �������)
inline int CheckCepId()
{
  if (GBS_GetCurCepid()==MMI_CEPID) return 1;
  return 0;
}

//---------------------------------------------------

SOCK_STATE Socket::GetState() const
{
  return socket_state;
}

//��������� ����� �� ip � �����
void Socket::Connect(int ip, short port)
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }
  if(socket_id<0)
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

//��������� ������
void Socket::Send(const char * data, int size)
{
  if (CheckCepId())
  {
    onError(SOCK_ERROR_INVALID_CEPID);
    return;
  }

  int send_res = send(socket_id, data, size, 0);
  if (send_res<0)
  {
    onError(SOCK_ERROR_SENDING);
    return;
  }

  GlobalTx += send_res;
  Tx += send_res;

  /*
  if (send_res<size) // ���� �� ���� ���� �������, ���� ���������� ����� �������. ���� ������� �� �����.
  {
  }
  */

}

//������� ������
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

//������� �����
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
}

//������� �����
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

// �������� ������
Socket::Socket()
{
  socket_state = SOCK_UNDEF;
  socket_id = -1;

  Tx = 0;
  Rx = 0;
  
  log = new Log;
}

// ����������� ������
Socket::~Socket()
{
  delete log;
}

