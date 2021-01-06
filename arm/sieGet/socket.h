/*
  Проект SieGet Downloader
                          */

//socketapi.h
//Высокоуровневый интерфейс обработки сокетов

#ifndef _SOCKETAPI_H_
#define _SOCKETAPI_H_

#include "log.h"

#define SOCK_SEND_TIMER

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
  SOCK_ERROR_INVALID_CEPID,
  SOCK_ERROR_CLIENT,
  SOCK_ERROR_SERVER
} SOCK_ERROR;

// Класс сокета.
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

  Socket();   // Создать сокет
  ~Socket();  // Удалить сокет
  
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

#ifdef SOCK_SEND_TIMER
  static Socket * Top;
#endif
  
  // Статистика трафика
  int Tx;
  int Rx;
  static int GlobalTx;
  static int GlobalRx;

  Log * log;
  
  // Внутреннее состояние
  int socket_id;
  SOCK_STATE socket_state;
private:
  char * send_q; // Очередь посылки данных
  int send_q_size;
#ifdef SOCK_SEND_TIMER
  GBSTMR send_tmr;
#endif
};

#endif
