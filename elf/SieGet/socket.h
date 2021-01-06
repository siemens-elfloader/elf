/*
  ������ SieGet Downloader
                          */

//socketapi.h
//��������������� ��������� ��������� �������

#ifndef _SOCKETAPI_H_
#define _SOCKETAPI_H_

typedef enum
{
  SOCK_UNDEF,
  SOCK_CREATED,
  SOCK_CONNECTED
} SOCK_STATE;

typedef enum
{
  SOCK_ERROR_CREATING,
  SOCK_ERROR_CONNECTING,
  SOCK_ERROR_SENDING,
  SOCK_ERROR_CLOSING,
  SOCK_ERROR_INVALID_SOCKET,
  SOCK_ERROR_INVALID_CEPID
} SOCK_ERROR;

// ����� ������. �����������.
class Socket
{
public:
  // ��������� ������, ������ ���� ���������� ���������
  virtual void onCreate() = 0;
  virtual void onDataRead() = 0;
  virtual void onConnected() = 0;
  virtual void onClose() = 0;
  virtual void onRemoteClose() = 0;
  virtual void onError(SOCK_ERROR err) = 0;

  //------------------------------

  //������� �����
  Socket(); // �� ��������� �����������

  void Create();

  //��������� ����� �� ip � �����
  //ip ������ ����� ������� ������ ���� (htonl)
  void Connect(int ip, short port);

  //��������� ������
  void Send(const char *data, int size);

  //�������� ������
  int Recv(char *data, int size);

  //������� �����
  void Close();

  SOCK_STATE GetState() const;

  ~Socket();

  // ������� �������
  static Socket *TopSocket;
  Socket *PrevSocket;
  Socket *NextSocket;

  // ���������� �������
  int Tx;
  int Rx;
  static int GlobalTx;
  static int GlobalRx;

  // ���������� ���������
  int id;
  char *senq_p;
  int sendq_l;
  SOCK_STATE state;
};

#endif
