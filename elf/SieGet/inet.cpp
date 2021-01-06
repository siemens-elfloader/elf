/*
  Проект SieGet Downloader
                          */
#include "include.h"
#include "socket.h"
#include "inet.h"
#include "mem.h"
#include "log.h"

//Проверить процесс (сокеты только в хелпере)
inline int CheckCepId()
{
  if (GBS_GetCurCepid()==MMI_CEPID) return 1;
  return 0;
}

//---------------------------------------------------------------

HttpDNR::HttpDNR()
{
  Callback = NULL;
}

void HttpDNR::Bind(HttpAbstract *sock)
{
  Callback = sock;
}

void HttpDNR::onResolve(int result, int value)
{
  if (Callback)
    Callback->onResolve(result, value);
}

//---------------------------------------------------------------

HttpAbstract::HttpAbstract()
{
  ip = 0;
  port = 0;
  recvbuf = NULL;
  req = NULL;

  http_state = HTTP_IDLE;
  Headers = NULL;

  Resolver = new HttpDNR();
  Resolver->Bind(this);
}

HttpAbstract::~HttpAbstract()
{
  if (req)
    delete req;
  if (Headers)
    delete Headers;
  if (recvbuf)
    delete recvbuf;
  if (Resolver)
    delete Resolver;
}

void HttpAbstract::Start(const char *_req, int _ip, short _port)
{
  if (http_state!=HTTP_IDLE)
    return;
  DEBUG("HttpAbstract::Start()");

  if (req)
    delete req;
  if (Headers)
  {
    delete Headers;
  }
  if (recvbuf)
  {
    delete recvbuf;
  }

  req = new char[strlen(_req)+1];
  Headers = new HTTP_Response();
  recvbuf = new Buffer();
  strcpy(req, _req);
  ip = _ip;
  port = _port;
  http_state = HTTP_HEADER;
  doConnect();
}

void HttpAbstract::Start(const char *_req, const char *host, short _port)
{
  if (http_state!=HTTP_IDLE)
    return;
  DEBUG("HttpAbstract::Start()");

  if (req)
    delete req;
  if (Headers)
  {
    delete Headers;
  }
  if (recvbuf)
  {
    delete recvbuf;
  }

  req = new char[strlen(_req)+1];
  Headers = new HTTP_Response();
  recvbuf = new Buffer();
  strcpy(req, _req);
  ip = 0;
  port = _port;
  http_state = HTTP_RESOLVE;
  DEBUG("Resolving host...");
  Resolver->Start(host, 3);
}

void _do_connect(HttpAbstract *obj)
{
  obj->doConnect();
}

void HttpAbstract::doConnect()
{
  if (CheckCepId())
    SUBPROC((void *)_do_connect, this);
  else
    Create();
}

void HttpAbstract::onResolve(int result, int value)
{
  char tmp[256];
  sprintf(tmp, "HttpAbstract::onResolve(%d, 0x%X)", result, value);
  DEBUG(tmp);

  if (result==DNR_RESULT_OK)
  {
    ip = value;
    http_state = HTTP_HEADER;
    doConnect();
  }
  else
  {
    onError(SOCK_ERROR_CONNECTING);
  }
}

void HttpAbstract::onCreate()
{
  char tmp[256];
  sprintf(tmp, "Connecting to IP %d.%d.%d.%d, port %d", ip&0xff, (ip>>8)&0xff, (ip>>16)&0xff, (ip>>24)&0xff, port);
  DEBUG(tmp);

  Connect(ip, port);
}

void HttpAbstract::onConnected()
{
  Send(req, strlen(req));
  delete req;
  req = NULL;

  onHTTPConnect();
}

void HttpAbstract::onDataRead()
{
  DEBUG("HttpAbstract::onDataRead()");
  char tmp[256];

  char tmpbuf[1024];
  int nrecv = Recv(tmpbuf, 1024);
  if (http_state==HTTP_HEADER)
  {
    recvbuf->Write(tmpbuf, nrecv);
    int hsize = Headers->Parse(recvbuf->data, recvbuf->size);

    sprintf(tmp, "HTTP Parser returned %d (data size %d)", hsize, recvbuf->size);
    DEBUG(tmp);

    if (hsize)
    {
      onHTTPHeaders();
      if (hsize<recvbuf->size)
      {
        onHTTPData(recvbuf->data+hsize, recvbuf->size-hsize);
      }
      http_state = HTTP_STREAM;
    }
  }
  else
  {
    onHTTPData(tmpbuf, nrecv);
  }
}

void HttpAbstract::onClose()
{
  DEBUG("HttpAbstract::onClose()");
  onHTTPFinish();
  http_state = HTTP_IDLE;
}

void HttpAbstract::onRemoteClose()
{
  Close();
}

void HttpAbstract::onError(SOCK_ERROR err)
{
  DEBUG("HttpAbstract::onError()");
  http_state = HTTP_IDLE;
}

//---------------------------------------------------------------

void HttpHead::onHTTPHeaders()
{
  DEBUG("HttpHead::onHTTPHeaders()");
  char tmp[512];
  sprintf(tmp, "Got response %d", Headers->resp_code);
  Log::Active->PrintLn(tmp);
  if (Headers->resp_msg)
    sprintf(tmp, "Reason: %s", Headers->resp_msg);
  else
    sprintf(tmp, "Reason: %s", "[No reason specified]");
  Log::Active->PrintLn(tmp);
  Close();
}

