/*
  Проект SieGet Downloader
                          */

//inet.h
//Высокоуровневые функции для получения потока данных целиком по одному запросу

#ifndef _INET_H_
#define _INET_H_

#include "include.h"
#include "mem.h"
#include "socket.h"
#include "http.h"
#include "dns.h"

#define RECV_RESULT_ERROR 0
#define RECV_RESULT_OK 1

enum HTTP_STATE
{
  HTTP_IDLE,
  HTTP_RESOLVE,
  HTTP_HEADER,
  HTTP_STREAM
};

class HttpAbstract;

class HttpDNR: public DNR
{
public:
  virtual void onResolve(int result, int value);
  void Bind(HttpAbstract *sock);
  HttpDNR();
private:
  HttpAbstract *Callback;
};

class HttpAbstract: public Socket
{
public:
  virtual void onCreate();
  virtual void onDataRead();
  virtual void onConnected();
  virtual void onClose();
  virtual void onRemoteClose();
  virtual void onError(SOCK_ERROR err);

  virtual void onHTTPConnect() = 0;
  virtual void onHTTPHeaders() = 0;
  virtual void onHTTPData(char *data, int size) = 0;
  virtual void onHTTPFinish() = 0;

  void onResolve(int result, int value);
  void Start(const char *req, int ip, short port);
  void Start(const char *req, const char *host, short port);
  void doConnect();

  HttpAbstract();
  ~HttpAbstract();

  HTTP_Response *Headers;
  HTTP_STATE http_state;

private:
  int ip;
  short port;
  char *req;

  Buffer *recvbuf;
  HttpDNR *Resolver;
};

class HttpHead: public HttpAbstract
{
  virtual void onHTTPConnect() {};
  virtual void onHTTPHeaders();
  virtual void onHTTPData(char *data, int size) {};
  virtual void onHTTPFinish() {}; // Требует переопределения
};


#endif
