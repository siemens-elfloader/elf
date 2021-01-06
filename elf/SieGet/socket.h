/*
  Проект SieGet Downloader
                          */

//socketapi.h
//Высокоуровневый интерфейс обработки сокетов

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

// Класс сокета. Одноразовый.
class Socket
{
public:
  // Интерфейс сокета, должен быть реализован потомками
  virtual void onCreate() = 0;
  virtual void onDataRead() = 0;
  virtual void onConnected() = 0;
  virtual void onClose() = 0;
  virtual void onRemoteClose() = 0;
  virtual void onError(SOCK_ERROR err) = 0;

  //------------------------------

  //Создать сокет
  Socket(); // Из активного обработчика

  void Create();

  //Соединить сокет по ip и порту
  //ip должен иметь порядок байтов сети (htonl)
  void Connect(int ip, short port);

  //Отправить данные
  void Send(const char *data, int size);

  //Получить данные
  int Recv(char *data, int size);

  //Закрыть сокет
  void Close();

  SOCK_STATE GetState() const;

  ~Socket();

  // Очередь сокетов
  static Socket *TopSocket;
  Socket *PrevSocket;
  Socket *NextSocket;

  // Статистика трафика
  int Tx;
  int Rx;
  static int GlobalTx;
  static int GlobalRx;

  // Внутреннее состояние
  int id;
  char *senq_p;
  int sendq_l;
  SOCK_STATE state;
};

#endif
