/*
  ������ SieGet Downloader
                          */
#include "include.h"
#include "socket.h"
#include "inet.h"
#include "mem.h"
#include "log.h"
#include "dialog.h"
#include "url_utils.h"
#include "file_works.h"

extern "C"
{
  extern unsigned long strtoul(const char *, char **, int);
};

DownloadHandler * DownloadHandler::Top = NULL;

//��������� ������� (������ ������ � �������)
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

void HttpDNR::onResolve(DNR_RESULT_MSG result_msg, int value)
{
  if (Callback)
    Callback->onResolve(result_msg, value);
}

//---------------------------------------------------------------

HttpAbstract::HttpAbstract()
{
  ip = 0;
  port = 0;
  req_buf = NULL;
  recv_buf = NULL;

  http_state = HTTP_IDLE;
  HTTPResponse = NULL;
  HTTPRequest = NULL;
  Resolver = new HttpDNR();
  Resolver->Bind(this);
}

HttpAbstract::~HttpAbstract()
{
  _safe_delete(HTTPResponse);
  _safe_delete(HTTPRequest);
  _safe_delete(recv_buf);
  _safe_delete(req_buf);
  _safe_delete(Resolver);
}

void HttpAbstract::Start(int _ip, short _port)
{
  if (http_state!=HTTP_IDLE && http_state!=HTTP_REDIRECT)
    return;
  if (!IsGPRSEnabled())
  {
    log->Print(LangPack::Active->data[LGP_EnableGPRSFirst], CLR_Red);
    onError(SOCK_ERROR_CONNECTING);
    return;
  }
  _safe_delete(HTTPResponse);
  _safe_delete(recv_buf);

  HTTPResponse = new HTTP_Response(log);
  recv_buf = new Buffer();
  ip = _ip;
  port = _port;
  http_state = HTTP_HEADER;
  doConnect();
}

void HttpAbstract::Start(const char * host, short _port)
{
  if (http_state!=HTTP_IDLE && http_state!=HTTP_REDIRECT)
    return;
  if (!IsGPRSEnabled())
  {
    log->Print(LangPack::Active->data[LGP_EnableGPRSFirst], CLR_Red);
    onError(SOCK_ERROR_CONNECTING);
    return;
  }
  _safe_delete(HTTPResponse);
  _safe_delete(recv_buf);

  HTTPResponse = new HTTP_Response(log);
  recv_buf = new Buffer();
  ip = 0;
  port = _port;
  http_state = HTTP_RESOLVE;
  download_state = DOWNLOAD_CONNECT;
  log->Print("Resolving host...", CLR_Green);
  Resolver->Start(host, 3);
  if (SieGetDialog::Active)
    SieGetDialog::Active->RefreshList();
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

void HttpAbstract::onResolve(DNR_RESULT_MSG result_msg, int value)
{
  char * msg = new char[64];
  sprintf(msg, "HttpAbstract::onResolve(%d, 0x%X)", result_msg, value);
  log->Print(msg, CLR_Yellow);

  switch(result_msg)
  {
  case DNR_RESULT_OK:
    ip = value;
    http_state = HTTP_HEADER;
    download_state = DOWNLOAD_CONNECT;
    if (SieGetDialog::Active)
      SieGetDialog::Active->RefreshList();
    doConnect();
    break;
  case DNR_RESULT_ERROR:
    sprintf(msg, "DNR Error %d", value);
    log->Print(msg, CLR_Red);
    onError(SOCK_ERROR_CONNECTING);
    break;
  case DNR_RESULT_OUT_OF_TRIES:
    log->Print("DNR out of tries!", CLR_Red);
    onError(SOCK_ERROR_CONNECTING);
    break;
  }
  delete msg;
}

void HttpAbstract::onCreate()
{
  char * msg=new char[128];
  sprintf(msg, "Connecting to IP %d.%d.%d.%d, port %d", ip&0xff, (ip>>8)&0xff, (ip>>16)&0xff, (ip>>24)&0xff, port);
  log->Print(msg, CLR_Green);
  delete msg;
  download_state = DOWNLOAD_CONNECT;
  if (SieGetDialog::Active)
    SieGetDialog::Active->RefreshList();
  Connect(ip, port);
}

void HttpAbstract::onConnected()
{
  Send(req_buf->data, req_buf->size);
  _safe_delete(req_buf);
  onHTTPConnect();
}

void HttpAbstract::onDataRead()
{
  char * tmp_buf = new char[CFG_DOWNLOAD_BUFFER_SIZE];
  int nrecv = Recv(tmp_buf, CFG_DOWNLOAD_BUFFER_SIZE); // �������� �����
  int hsize;

  switch(http_state)
  {
  case HTTP_HEADER: // ��������� ��������� HTTP
    download_state = DOWNLOAD_GET_INFO;
    recv_buf->Write(tmp_buf, nrecv);

    if(hsize = HTTPResponse->Parse(recv_buf->data, recv_buf->size)) // ���������� ���� ���������
    {
      char * tmp_msg = new char[128];
      sprintf(tmp_msg, "HTTP Parser returned %d (data size %d)", hsize, recv_buf->size);
      log->Print(tmp_msg, CLR_Green);
      delete tmp_msg;
      if(!onHTTPHeaders()) return;
      if (hsize < recv_buf->size) // ���� ���� ������ ������ ���������
        onHTTPData(recv_buf->data+hsize, recv_buf->size - hsize);
      http_state = HTTP_STREAM;
      if (SieGetDialog::Active)
        SieGetDialog::Active->RefreshList();
    }
    break;
  case HTTP_STREAM: // ��������� ������
    if(nrecv) onHTTPData(tmp_buf, nrecv);
    break;
  }
  delete tmp_buf;
}

void HttpAbstract::onClose()
{
  if(download_state!=DOWNLOAD_STOPPED && download_state!=DOWNLOAD_ERROR && http_state!=HTTP_REDIRECT)
    onHTTPFinish();
  http_state = HTTP_IDLE;
  SUBPROC((void *)_save_queue, DownloadHandler::Top);
}

void HttpAbstract::onRemoteClose()
{
  Close();
}

void HttpAbstract::onError(SOCK_ERROR err)
{
  switch(err)
  {
  case SOCK_ERROR_CREATING:
    log->Print(LangPack::Active->data[LGP_SocketCreateError], CLR_Red);
    break;
  case SOCK_ERROR_CONNECTING:
    log->Print(LangPack::Active->data[LGP_SocketConnectError], CLR_Red);
    break;
  case SOCK_ERROR_SENDING:
    log->Print(LangPack::Active->data[LGP_SocketSendError], CLR_Red);
    break;
  case SOCK_ERROR_CLOSING:
    log->Print(LangPack::Active->data[LGP_SocketCloseError], CLR_Red);
    break;
  case SOCK_ERROR_INVALID_SOCKET:
    log->Print(LangPack::Active->data[LGP_InvalidSocket], CLR_Red);
    break;
  }
  http_state = HTTP_IDLE;
  if(download_state != DOWNLOAD_STOPPED)
  {
    download_state = DOWNLOAD_ERROR;
    StartVibra(2);
    Play_Sound("$sounds\\error.wav");
  }
  if (SieGetDialog::Active)
    SieGetDialog::Active->RefreshList();
  SUBPROC((void *)_save_queue, DownloadHandler::Top);
}

//---------------------------------------------------------------

int Download::onHTTPHeaders()
{
  char * tmp_msg = new char[256];
  sprintf(tmp_msg, "Got response %d", HTTPResponse->resp_code);
  log->Print(tmp_msg, CLR_Green);
  
  if (HTTPResponse->resp_msg)
    sprintf(tmp_msg, "Reason: %s", HTTPResponse->resp_msg);
  else
    sprintf(tmp_msg, "Reason: %s", "[No reason specified]");
  log->Print(tmp_msg, CLR_Green);
  delete tmp_msg;
  
  if(RESP_CODE_CLIENT_ERROR(HTTPResponse->resp_code)) // ������ �������
  {
    onError(SOCK_ERROR_CLIENT);
    return 0;
  }
  if(RESP_CODE_SERVER_ERROR(HTTPResponse->resp_code)) // ������ �������
  {
    onError(SOCK_ERROR_SERVER);
    return 0;
  }
  if(RESP_CODE_REDIRECTED(HTTPResponse->resp_code)) // ��������
  {
    onHTTPRedirect();
    return 0;
  }
  /* ������ Content-Disposition */
  if(char * content_disposition_str = HTTPResponse->headers->GetValue("Content-Disposition"))
  {
    if (!is_const_file_name) // ���� ��� �� ������� ������
    {
      _safe_delete(file_name);
      char * new_fname = Get_Param_Value(content_disposition_str, "filename", 1); // �������� ��� �� ���������
      remove_bad_chars(new_fname); // ������� �� ����� ������������ �������, ���� �������� ������ ����� ���� �� ������ :)
      file_name = utf82filename(new_fname); // utf8 � ��� �����
      delete new_fname;
      
      _safe_delete(full_file_name);
      full_file_name = new char[strlen(file_path) + strlen(file_name) + 2];
      sprintf(full_file_name, "%s%s", file_path, file_name);
      log->ChangeFileName(file_name);
    }
  }
  /* ������ Content-Length */
  if(char * content_length_str = HTTPResponse->headers->GetValue("Content-Length")) // �������� ������ ����� �� ���������
  {
    file_size = NULL;
    file_size = strtoul(content_length_str, 0, 10);
    if (RESP_CODE_PARTIAL(HTTPResponse->resp_code)) // ���� �������
    {
      AcceptRangesState = ACCEPT_RANGES_OK; // ������ ������ ������������ ������� ;)
      file_size += file_loaded_size;        // ��������� ������ ����, ��� ��� ��������
    }
    else // ���� ������ ������� �� ������
    {
      file_loaded_size = NULL; // ������ ����� = 0
      unsigned int io_error;
      unlink(full_file_name, &io_error); // ������� ����, ���� �� ����
    }
  }
  if (!RESP_CODE_PARTIAL(HTTPResponse->resp_code)) // Partial Content
  {
    if (HTTPResponse->headers->GetValue("Accept-Ranges")) // ���� ���� ��������� "Accept-Ranges"
      AcceptRangesState = ACCEPT_RANGES_OK; // ������ ������ ������ �������
    else
      AcceptRangesState = ACCEPT_RANGES_NO; // ����� �� ������
  }
  if (SieGetDialog::Active)
    SieGetDialog::Active->RefreshList(); // �������������� ������
  return 1;
}

void Download::onHTTPData(char * data, int size) // ������ ������ � ����
{
  unsigned int io_error;
  
  download_state = DOWNLOAD_DATA; // ������ ������� - �������� ������
  
  if (hFile == -1) // ���� ���� �� ������, ��������� ���
    hFile = fopen(full_file_name, A_WriteOnly + A_Create + A_Append + A_BIN, P_WRITE, &io_error);

  fwrite(hFile, data, size, &io_error); // ���������� �������� ������ � ����
  file_loaded_size += size; // ��������� ������ ������������ �����
  if (SieGetDialog::Active)
    SieGetDialog::Active->RefreshList();
}

void Download::onHTTPRedirect() // �������������
{
  http_state = HTTP_REDIRECT;
   // � ��������� "Location" ����������� �������� ��������������� �����
  if (char * Location = HTTPResponse->headers->GetValue("Location"))
  {
    if (strstr(Location, "http://")) // ���� � ��������� URL
    {
      _safe_delete(HTTPRequest); // ������� ������
      _safe_delete(url); // ������� URL
      url = new char[strlen(Location) + 1]; // ������� ����� URL
      strcpy(url, Location);
    }
    else
    {
      _safe_delete(HTTPRequest->Path);
      HTTPRequest->Path = new char[strlen(Location) + 1];
      strcpy(HTTPRequest->Path, Location);
      
      if (!is_const_file_name)
      {
        _safe_delete(file_name);
        file_name = get_fname_from_path(HTTPRequest->Path);
      
        _safe_delete(full_file_name);
        full_file_name = new char[strlen(file_path) + strlen(file_name) + 2];
        sprintf(full_file_name, "%s%s", file_path, file_name);
        
        log->ChangeFileName(file_name);
      }
      file_loaded_size = NULL;
      file_size = NULL;
    }
    
    StartDownload();
  }
}

void Download::onHTTPStopped()
{
  unsigned int io_error;
  
  download_state=DOWNLOAD_STOPPED;
  Close();
  
  if (hFile != -1)
    fclose(hFile, &io_error);
  hFile = -1;
  
  SUBPROC((void *)_save_queue, DownloadHandler::Top);
}

void Download::onHTTPFinish()
{
  unsigned int io_error;
  
  if (hFile != -1)
    fclose(hFile, &io_error);
  hFile = -1;
  
  download_state = DOWNLOAD_COMPLETE;
  http_state = HTTP_IDLE;
  if (SieGetDialog::Active)
    SieGetDialog::Active->RefreshList();
  SUBPROC((void *)_save_queue, DownloadHandler::Top);
  StartVibra(1);
  Play_Sound("$sounds\\complete.wav");
}

void _start_download(Download * download)
{
  download->StartDownload();
}

void Download::StartDownload()
{
  download_state=DOWNLOAD_WAITING;
  if (!HTTPRequest)
  {
    URL_unescape(url); // �� ������ ������ ������������ url � ������� ���
    
    URL * tmp_url = new URL; // ������� ����� URL
    tmp_url->Parse(url); // ������

    if (!is_const_file_name)
    {
      _safe_delete(file_name);
      char * new_fname = get_fname_from_path(tmp_url->path); // �������� ��� �� url->path
      remove_bad_chars(new_fname); // ������� �� ����� ������������ �������
      file_name = utf82filename(new_fname); // utf8 � ��� �����
      delete new_fname;
    }
    
    _safe_delete(full_file_name);
    full_file_name = new char[strlen(file_path) + strlen(file_name) + 2];
    sprintf(full_file_name, "%s%s", file_path, file_name); // ������ ��� �����

    log->ChangeFileName(file_name); // ������� ��� ����� ����

    char * encoded_url = URL_reencode_escapes(url); // ������������ URL � Web ������
    delete url;
    url = encoded_url;

    tmp_url->Parse(url);
    //tmp_url->Print(log);
    
    HTTPRequest = new HTTP_Request; // ������� ����� ������
    // Host. ����� �� URL
    HTTPRequest->Host = new char[strlen(tmp_url->host)+1];
    strcpy(HTTPRequest->Host, tmp_url->host);
    // Path. ����� �� URL
    if(tmp_url->param) 
    {
      if(tmp_url->fragment)
      {
        HTTPRequest->Path = new char[strlen(tmp_url->path)+strlen(tmp_url->param)+strlen(tmp_url->fragment)+3];
        sprintf(HTTPRequest->Path, "%s?%s#%s", tmp_url->path, tmp_url->param, tmp_url->fragment);
      }
      else
      {
        HTTPRequest->Path = new char[strlen(tmp_url->path)+strlen(tmp_url->param)+2];
        sprintf(HTTPRequest->Path, "%s?%s", tmp_url->path, tmp_url->param);
      }
    }
    else 
    {
      HTTPRequest->Path = new char[strlen(tmp_url->path)+1];
      strcpy(HTTPRequest->Path, tmp_url->path);
    }
    // Port. ����� �� URL
    HTTPRequest->Port = tmp_url->port;
    // Referer. ������ URL
    HTTPRequest->Referer = new char[strlen(url) + 1];
    strcpy(HTTPRequest->Referer, url);
    URL_unescape(url); // ������������ URL �� Web ������� � ������� ���
    delete tmp_url;
  }
  if(!strlen(HTTPRequest->Host))
  {
    MsgBoxError(1, (int)"No host!");
    delete this;
    return;
  }
  _safe_delete(req_buf); //������� ������ ����� �������. ���� �� ��� ��� ;)
  req_buf = new Buffer; // ������� ����� �����
  int req_len = 0; // ����� ����� ������ �������
  char * req_str = new char[512]; // ������ ������
  
  req_len=snprintf(req_str, 511, "GET /%s HTTP/1.1\r\n", HTTPRequest->Path); // ��������� ������
  req_buf->Write(req_str, req_len); // ����� ������ � �����
  log->Print(req_str, CLR_Blue);
  // Host
  req_len=snprintf(req_str, 511, "Host: %s\r\n", HTTPRequest->Host);
  req_buf->Write(req_str, req_len);
  log->Print(req_str, CLR_Blue);
  // Range. ��� ��� �������
  if (is_file_exists(full_file_name)) // ���� ���� ��� ����
  {
    if(int size = get_file_size(full_file_name)) // � ����� ����� != 0
    {
      req_len=snprintf(req_str, 511, "Range: bytes=%u-\r\n", size);
      req_buf->Write(req_str, req_len);
      log->Print(req_str, CLR_Blue);
      file_loaded_size = size;
    }
  }
  // Referer
  req_len=snprintf(req_str, 511, "Referer: %s\r\n", HTTPRequest->Referer);
  req_buf->Write(req_str, req_len);
  log->Print(req_str, CLR_Blue);
  // User-Agent
  req_len=snprintf(req_str, 511, "User-Agent: %s\r\n", HTTPRequest->User_Agent);
  req_buf->Write(req_str, req_len);
  log->Print(req_str, CLR_Blue);
  // Connection
  req_len=snprintf(req_str, 511, "Connection: close\r\n");
  req_buf->Write(req_str, req_len);
  log->Print(req_str, CLR_Blue);
  // CRLF
  req_len=snprintf(req_str, 511, "\r\n");
  req_buf->Write(req_str, req_len);
  
  Start(HTTPRequest->Host, HTTPRequest->Port);
  
  SUBPROC((void *)_save_queue, DownloadHandler::Top);
  delete req_str;
}

void Download::StopDownload()
{
  onHTTPStopped();
}

Download::Download()
{
  AcceptRangesState = ACCEPT_RANGES_UNKNOWN;
  url = NULL;
  file_name = NULL;
  is_const_file_name = NULL;
  full_file_name = NULL;
  file_path = NULL;
  file_size = NULL;
  file_loaded_size = NULL;
  
  hFile = -1;
  if (DownloadHandler::Top)
    DownloadHandler::Top->CreateDownload(this);
}

Download::~Download()
{
  _safe_delete(url);
  _safe_delete(file_name);
  _safe_delete(full_file_name);
  _safe_delete(file_path);
  
  unsigned int io_error;
  if (hFile != -1)
    fclose(hFile, &io_error);
  hFile = -1;
  
  if (DownloadHandler::Top)
    DownloadHandler::Top->DeleteDownload(this);
}

/*******************************************************************************
  DownloadHandler
  ���������� �������
*******************************************************************************/

void DownloadHandler::CreateDownload(Download * download)
{
  DownloadQ * tmp = new DownloadQ;
  tmp->download = download;
  tmp->next = queue;
  queue = tmp;
}

void DownloadHandler::DeleteDownload(Download * download)
{
  DownloadQ *tmp = queue;
  if (queue->download==download)
  {
    queue = queue->next;
    delete tmp;
  }
  else
  {
    DownloadQ *prev_download = queue;
    tmp = queue->next;
    while (tmp)
    {
      if (tmp->download==download)
      {
        prev_download->next = tmp->next;
        delete tmp;
      }
      prev_download = tmp;
      tmp = tmp->next;
    }
  }
  SaveQueue();
}

Download * DownloadHandler::GetDownloadbyID(int socket_id)
{
  DownloadQ * tmp = queue;
  while(tmp)
  {
    if (tmp->download->socket_id==socket_id)
      return tmp->download;// �����!
    tmp = tmp->next;
  }
  return 0; // �� �����...
}

Download * DownloadHandler::GetDownloadbyN(int n)
{
  DownloadQ * tmp = queue;
  for (int i=0; i!=n && tmp; i++)
    tmp = tmp->next;
  if(tmp)
    return tmp->download;
  return NULL;
}

int DownloadHandler::GetNumOfDownloadsByState(DOWNLOAD_STATE state)
{
  int n = 0;
  DownloadQ * tmp = queue;
  while(tmp)
  {
    if (tmp->download->download_state==state)
      n++;
    tmp = tmp->next;
  }
  return n;
}

Download * DownloadHandler::GetDownloadByState(DOWNLOAD_STATE state)
{
  DownloadQ *tmp = queue;
  while(tmp)
  {
    if (tmp->download->download_state==state)
      return tmp->download;
    tmp = tmp->next;
  }
  return NULL;
}

int DownloadHandler::IsAnyDownloadActive()
{
  DownloadQ *tmp = queue;
  while(tmp)
  {
    if (ACTIVE_DOWNLOAD_STATE(tmp->download->download_state))
      return 1;
    tmp = tmp->next;
  }
  return 0;
}

int DownloadHandler::GetNumOfDownloads()
{
  int n = 0;
  DownloadQ *tmp = queue;
  while(tmp)
  {
    n++;
    tmp = tmp->next;
  }
  return n;
}

char QL_List[]="SieGet downloads list";
char QL_GeneratedDateTime[]="GeneratedDateTime=";
char QL_Total_downloads[]="TotalDownloads=";
char QL_Download[]="Download";
char QL_FileName[]="FileName=";
char QL_FullName[]="FullName=";
char QL_SaveTo[]="SaveTo=";
char QL_URL[]="URL=";
char QL_State[]="State=";
char QL_Size[]="Size=";
char QL_Downloaded[]="Downloaded=";

void _load_queue(DownloadHandler * dh)
{
  dh->LoadQueue();
}

void DownloadHandler::LoadQueue()
{
  volatile int hFile;
  unsigned int io_error = 0;
  char * buf; // ����� ��� ����
  char line[256]; // ������� ������
  int line_size = 0; // ����� ������� ������
  int buf_pos = 0; // ������� � ������
  Download * top_download;
  FSTATS fstat;
  char list_file[256];
  getSymbolicPath(list_file, "$sieget\\List.txt");
  if (GetFileStats(list_file, &fstat, &io_error)!=-1) // �������� ������ �����
  {
    if((hFile=fopen(list_file, A_ReadOnly + A_BIN, P_READ, &io_error))!=-1) // ��������� ���� ��� ������
    {
      if (buf = new char[fstat.size+1]) // �������� ������ ��� �����
      {
        buf[fread(hFile, buf, fstat.size, &io_error)]=0; // ������ ���� � �����
        while(buf[buf_pos]!=0 && buf_pos < fstat.size) // ���� �� ����� �����
        {
          if (buf[buf_pos]=='\r' && buf[buf_pos + 1]=='\n') // R���� ������
          {
            if (line_size > 0)
            {
              line[line_size] = NULL;
              if(strstr(line, QL_FileName))
              {
                top_download->file_name = new char[line_size - sizeof(QL_FileName) + 1];
                strcpy(top_download->file_name, line + sizeof(QL_FileName));
                goto end_of_loop; // ������ ��������� ��� ������ �� �����. ���� � ����� �����
              }
              if(strstr(line, QL_FullName))
              {
                top_download->full_file_name = new char[line_size - sizeof(QL_FullName) + 1];
                strcpy(top_download->full_file_name, line + sizeof(QL_FullName));
                goto end_of_loop;
              }
              if(strstr(line, QL_SaveTo))
              {
                top_download->file_path = new char[line_size - sizeof(QL_SaveTo) + 1];
                strcpy(top_download->file_path, line + sizeof(QL_SaveTo));
                goto end_of_loop;
              }
              if(strstr(line, QL_URL))
              {
                top_download->url = new char[line_size - sizeof(QL_URL) + 1];
                strcpy(top_download->url, line + sizeof(QL_URL));
                goto end_of_loop;
              }
              if(strstr(line, QL_State))
              {
                top_download->download_state = (DOWNLOAD_STATE)strtoul(line + sizeof(QL_State), 0, 10);
                goto end_of_loop;
              }
              if(strstr(line, QL_Size))
              {
                top_download->file_size = (DOWNLOAD_STATE)strtoul(line + sizeof(QL_Size), 0, 10);
                goto end_of_loop;
              }
              if(strstr(line, QL_Downloaded))
              {
                top_download->file_loaded_size = (DOWNLOAD_STATE)strtoul(line + sizeof(QL_Downloaded), 0, 10);
                goto end_of_loop;
              }
            end_of_loop: // ����� �����
              if (buf[buf_pos + 2]=='\r' && buf[buf_pos + 3]=='\n' && buf[buf_pos + 4]!=NULL)
              {
                Download * new_download = new Download;
                top_download = new_download;
              }
              line_size=0;
            }
          }
          else
            line[line_size++]=buf[buf_pos]; // ��������� � ������ ������� �� ������, ���� �� ����� �����
          buf_pos++;
        }
        delete buf; // ������� �����. �� ��� ��� �� �����������
        
        DownloadQ *tmp = queue;
        while(tmp)
        {
          tmp->download->log->ChangeFileName(tmp->download->file_name); // �������� ��� ����� ����
          if (ACTIVE_DOWNLOAD_STATE(tmp->download->download_state))
            tmp->download->download_state = DOWNLOAD_STOPPED;
          tmp = tmp->next;
        }
        if (SieGetDialog::Active)
          SieGetDialog::Active->RefreshList();
      }
      fclose(hFile, &io_error);
    }
  }
}

void _save_queue(DownloadHandler * dh)
{
  dh->SaveQueue();
}

void DownloadHandler::SaveQueue()
{
  volatile int hFile;
  unsigned int io_error = 0;
  int download_n = 0; // ����� ������� �������
  char list_file[256]; // ��� �����
  char * tmp_str = new char[512]; // ��������� ������
  int tmp_str_len = 0; // ����� ��������� ������
  Buffer * tmp_buf = new Buffer; // ����� ������
  
  getSymbolicPath(list_file, "$sieget\\List.txt"); // ...\Sieget\List.txt
  
  unlink(list_file, &io_error); // ������� ������ ����
  
  hFile = fopen(list_file, A_ReadWrite + A_Create + A_Append + A_BIN, P_READ + P_WRITE, &io_error); // ��������� ���� ��� ������
  if(!io_error)
  {
    DownloadQ * tmp = queue; // ������� �������
    tmp_str_len = snprintf(tmp_str, 511, "SieGet downloads list\r\n");
    tmp_buf->Write(tmp_str, tmp_str_len);
    // ��������� � ����� ���� � ����� ��������� �����
    TTime time; TDate date;
    GetDateTime(&date, &time); // �������� ������� ���� � �����
    tmp_str_len = snprintf(tmp_str, 511, "%s%02d.%02d.%02d %02d:%02d:%02d\r\n", QL_GeneratedDateTime, date.day, date.month, date.year, time.hour, time.min, time.sec);
    tmp_buf->Write(tmp_str, tmp_str_len);
    // ��������� � ����� ����� ������� � �������
    tmp_str_len = snprintf(tmp_str, 511, "%s%d\r\n\r\n", QL_Total_downloads, GetNumOfDownloads());
    tmp_buf->Write(tmp_str, tmp_str_len);
    while(tmp) // ����� ������ � ����� ��� ������ �������
    {
      // ��������� � ����� ����� ������� ����������� �������
      tmp_str_len = snprintf(tmp_str, 511, "%s %d:\r\n", QL_Download, download_n + 1);
      tmp_buf->Write(tmp_str, tmp_str_len);
      // ��������� � ����� ��� ������������� �����
      tmp_str_len = snprintf(tmp_str, 511, "%s%s\r\n", QL_FileName, tmp->download->file_name);
      tmp_buf->Write(tmp_str, tmp_str_len);
      // ��������� � ����� ��� ������������� �����
      tmp_str_len = snprintf(tmp_str, 511, "%s%s\r\n", QL_FullName, tmp->download->full_file_name);
      tmp_buf->Write(tmp_str, tmp_str_len);
      // ��������� � ����� �����, ���� ����������� ����
      tmp_str_len = snprintf(tmp_str, 511, "%s%s\r\n", QL_SaveTo, tmp->download->file_path);
      tmp_buf->Write(tmp_str, tmp_str_len);
      // ��������� � ����� URL, �� �������� ������������� �������
      tmp_str_len = snprintf(tmp_str, 511, "%s%s\r\n", QL_URL, tmp->download->url);
      tmp_buf->Write(tmp_str, tmp_str_len);
      // ��������� � ����� ��������� �������
      tmp_str_len = snprintf(tmp_str, 511, "%s%d\r\n", QL_State, tmp->download->download_state);
      tmp_buf->Write(tmp_str, tmp_str_len);
      // ��������� � ����� ������ ������������� �����
      tmp_str_len = snprintf(tmp_str, 511, "%s%u\r\n", QL_Size, tmp->download->file_size);
      tmp_buf->Write(tmp_str, tmp_str_len);
      // ��������� � ����� ����� ���������� ���� �����
      tmp_str_len = snprintf(tmp_str, 511, "%s%u\r\n\r\n", QL_Downloaded, tmp->download->file_loaded_size);
      tmp_buf->Write(tmp_str, tmp_str_len);
      
      download_n++;
      tmp = tmp->next;
    }
    // ����� ���� ����� � ����
    fwrite(hFile, tmp_buf->data, tmp_buf->size, &io_error);
    fclose(hFile, &io_error);
  }
  delete tmp_str;
  delete tmp_buf;
}

DownloadHandler::DownloadHandler()
{
  Top = this;
  queue = NULL;
  SUBPROC((void *)_load_queue, this);
}

DownloadHandler::~DownloadHandler()
{
  SaveQueue();
  DownloadQ * tmp;
  while (tmp = queue)
  {
    queue = queue->next;
    delete tmp;
  }
}
