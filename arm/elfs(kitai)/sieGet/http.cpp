#include "include.h"
#include "http.h"
#include "log.h"

/*******************************************************************************
 HTTP_Request
*******************************************************************************/

HTTP_Request::HTTP_Request()
{
  Path = NULL;
  Accept = NULL;
  Accept_Charset = NULL;
  Accept_Encoding = NULL;
  Accept_Language = NULL;
  Authorization = NULL;
  Expect = NULL;
  From = NULL;
  Host = NULL;
  If_Match = NULL;
  If_Modified_Since = NULL;
  If_None_Match = NULL;
  If_Range = NULL;
  If_Unmodified_Since = NULL;
  Max_Forwards = NULL;
  Proxy_Authorization = NULL;
  Range = NULL;
  Referer = NULL;
  TE = NULL;
  User_Agent = "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)";
}

HTTP_Request::~HTTP_Request()
{
  _safe_delete(Path);
  _safe_delete(Accept);
  _safe_delete(Accept_Charset);
  _safe_delete(Accept_Encoding);
  _safe_delete(Accept_Language);
  _safe_delete(Authorization);
  _safe_delete(Expect);
  _safe_delete(From);
  _safe_delete(Host);
  _safe_delete(If_Match);
  _safe_delete(If_Modified_Since);
  _safe_delete(If_None_Match);
  _safe_delete(If_Range);
  _safe_delete(If_Unmodified_Since);
  _safe_delete(Max_Forwards);
  _safe_delete(Proxy_Authorization);
  _safe_delete(Range);
  _safe_delete(Referer);
  _safe_delete(TE);
  //if (User_Agent) delete User_Agent;
}

/*******************************************************************************
 HTTP_Response
*******************************************************************************/
/*
  Парсер HTTP заголовка
  Возвращает длину всего заголовка или 0, если заголовок не полный
                                                                  */
int HTTP_Response::Parse(char * buf, int maxlen)
{
  _safe_delete(headers); // Нафиг нам старые заголовки, тем более что неизвестно что там
  headers = new HTTP_Response_Headers(log); // Создаем новое хранилище заголовков

  int l_len = 0;    // Длина текущей строки
  char l_buf[512];  // Буфер текущей строки
  int n_CR = 0;     // Число CR в конце строки
  int n_LF = 0;     // Число LF в конце строки
  int hlen = 0;     // Длина всего заголовка
  
  /* Читаем строку статуса */
  while (!(buf[l_len]=='\n' || buf[l_len]=='\r') && (l_len<maxlen)) // Считаем длину строки
    l_len++;
  strncpy(l_buf, buf, l_len); // Копируем строку в буфер
  l_buf[l_len] = 0;
  if (sscanf(l_buf, "HTTP/%d.%d %d", &http_ver_major, &http_ver_minor, &resp_code)<3) // Извлекаем из строки статуса версию HTTP и код ответа
    return 0;
  if (strlen(l_buf)>13) // Если есть сообщение статуса
  {
    _safe_delete(resp_msg); // Удаляем старое
    resp_msg = new char[strlen(l_buf)-13+1]; // Создаем новое
    strcpy(resp_msg, l_buf+13); // Копируем из строки
  }
  while(buf[l_len]=='\n' || buf[l_len]=='\r') // Пропускаем CR и LF
  {
    if (buf[l_len]=='\r') n_CR++; // Считаем все CR в конце строки
    if (buf[l_len]=='\n') n_LF++; // Считаем все LF в конце строки
    l_len++;
  }
  buf += l_len; // Переходим к следующей строке
  maxlen -= l_len;
  hlen += l_len;
  
  /* Все последующие строки */
  do
  {
    l_len = 0;
    n_CR = 0;
    n_LF = 0;
    
    while (!(buf[l_len]=='\r' || buf[l_len]=='\n') && (l_len<maxlen)) // Считаем длину строки
      l_len++;
    
    strncpy(l_buf, buf, l_len); // Копируем строку в буфер
    l_buf[l_len] = 0;
    
    while(buf[l_len]=='\n' || buf[l_len]=='\r') // Пропускаем CR и LF
    {
      if (buf[l_len]=='\r') n_CR++; // Считаем все CR в конце строки
      if (buf[l_len]=='\n') n_LF++; // Считаем все LF в конце строки
      l_len++;
    }
    
    if (!headers->Add(l_buf)) return 0;
    
    buf += l_len; // Переходим к следующей строке
    maxlen -= l_len;
    hlen += l_len;
    if (n_CR == 2 || n_LF == 2) break; // Конец заголовка. в основном кончается на \r\n\r\n, но бывают и исключения ;)
  } while (maxlen);
  return hlen;
}

HTTP_Response::HTTP_Response(Log * _log)
{
  log = _log;
  headers = NULL;
  resp_msg = NULL;
}

HTTP_Response::~HTTP_Response()
{
  _safe_delete(resp_msg);
  _safe_delete(headers);
}
