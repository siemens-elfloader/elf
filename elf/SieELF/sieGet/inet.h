/*
  ������ SieGet Downloader
                          */

//inet.h
//��������������� ������� ��� ��������� ������ ������ ������� �� ������ �������

#ifndef _INET_H_
#define _INET_H_

#include "include.h"
#include "mem.h"
#include "socket.h"
#include "http.h"
#include "dns.h"
#include "url.h"
#include "log.h"

enum HTTP_STATE   // ������ HTTP
{
  HTTP_IDLE,      // �������
  HTTP_RESOLVE,   // ��������� IP
  HTTP_REDIRECT,  // ��������
  HTTP_HEADER,    // ��������� ���������
  HTTP_STREAM,    // ��������� ������
};

enum DOWNLOAD_STATE   // ������ �������
{
  DOWNLOAD_WAITING,   // ��������
  DOWNLOAD_ERROR,     // ������
  DOWNLOAD_CONNECT,   // ����������
  DOWNLOAD_GET_INFO,  // ��������� ���������
  DOWNLOAD_DATA,      // ��������� �����
  DOWNLOAD_COMPLETE,  // ������� ���������
  DOWNLOAD_STOPPED    // �����������
};

enum ACCEPT_RANGES_STATE
{
  ACCEPT_RANGES_UNKNOWN,  // ����������
  ACCEPT_RANGES_OK,       // ������ ������������ �������
  ACCEPT_RANGES_NO        // ������ �� ������������ �������
};

// ������, ������������ ���������� ������ �������
#define ACTIVE_DOWNLOAD_STATE(x) ((x) == DOWNLOAD_WAITING      \
                                  || (x) == DOWNLOAD_CONNECT   \
                                  || (x) == DOWNLOAD_GET_INFO  \
                                  || (x) == DOWNLOAD_DATA)

class HttpAbstract;

class HttpDNR: public DNR
{
public:
  virtual void onResolve(DNR_RESULT_MSG result_msg, int value);
  void Bind(HttpAbstract * sock);
  HttpDNR();
private:
  HttpAbstract * Callback;
};

class HttpAbstract: public Socket
{
public:
  virtual void onCreate(); // �������� ������
  virtual void onDataRead(); // ��������� ������
  virtual void onConnected(); // ����������
  virtual void onClose(); // �������� ������
  virtual void onRemoteClose(); // ��������� ��������
  virtual void onError(SOCK_ERROR err); // ���������� ������

  virtual void onHTTPConnect() = 0; // ���������� ��� ����������
  virtual int onHTTPHeaders() = 0; // ��������� ��������� HTTP
  virtual void onHTTPData(char * data, int size) = 0; // ��������� ��������� ������ (���������� � ����)
  virtual void onHTTPRedirect() = 0; // �������������
  virtual void onHTTPStopped() = 0; // ���������
  virtual void onHTTPFinish() = 0; // ��������� �������
  
  void onResolve(DNR_RESULT_MSG result_msg, int value);
  
  void Start(int ip, short port); // ���������� �� IP
  void Start(const char * host, short port); // ���������� �� ����� �����
  
  void doConnect();
  
  HttpAbstract();
  ~HttpAbstract();
  
  HTTP_Request * HTTPRequest; // ������
  HTTP_Response * HTTPResponse; // �����
  HTTP_STATE http_state; // ��������� HTTP
  DOWNLOAD_STATE download_state; // ��������� �������
  Buffer * req_buf; // ����� �������
  
private:
  int ip; // IP
  short port; // ����
  Buffer * recv_buf; // ����� ������
  HttpDNR * Resolver; // ��������
};

class Download: public HttpAbstract
{
  virtual void onHTTPConnect() {}; // ��� ���� ������ �������������
  virtual int onHTTPHeaders(); // ��������� ���������� HTTP
  virtual void onHTTPData(char * data, int size); // ��������� ������
  virtual void onHTTPRedirect(); // �������������
  virtual void onHTTPStopped(); // ��������� �������
  virtual void onHTTPFinish(); // ����� �������
public:
  Download();
  ~Download();

  static Download * Top; // ������� �������
  Download * next;
  
  void StartDownload();
  void StopDownload();
  
  ACCEPT_RANGES_STATE AcceptRangesState; // ��������� �������� �������
  
  char * url;             // URL
  char * file_name;       // ��� �����
  int is_const_file_name; // ����, �����������, ��� ��� ����� ������� ������ � ��� �� ������� ������
  char * full_file_name;  // ������ ��� �����
  char * file_path;       // ����� ����������
  int file_size;          // ������ ������ �����
  int file_loaded_size;   // ������ ���������� �����
private:
  int hFile; // ������� �����
};

void _start_download(Download * download);

class DownloadHandler
{
public:
  DownloadHandler();
  ~DownloadHandler();
  
  // �������� �������
  void CreateDownload(Download * download);
  //������� �������
  void DeleteDownload(Download * download);
  //�������� ����� ������� �� ID ������
  Download * GetDownloadbyID(int socket_id);
  //�������� ����� ������� �� �� ������� � ������
  Download * GetDownloadbyN(int n);
  // �������� ����� ������� � ������������ ��������
  int GetNumOfDownloadsByState(DOWNLOAD_STATE state);
  //�������� ������� �� �������
  Download * GetDownloadByState(DOWNLOAD_STATE state);

  int IsAnyDownloadActive();
  // �������� ����� ���� ������� � �������
  int GetNumOfDownloads();
  
  static DownloadHandler * Top;
  
  void SaveQueue();
  void LoadQueue();

private:
  // ���������� ������� �������
  struct DownloadQ
  {
    Download * download;
    DownloadQ * next;
  };
  DownloadQ * queue;
};

void _load_queue(DownloadHandler * dh);
void _save_queue(DownloadHandler * dh);

#endif
