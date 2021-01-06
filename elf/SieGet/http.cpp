#include "include.h"
#include "http.h"

int HTTP_Response::Parse(char *buf, int maxlen)
{
  if (headers)
    delete headers; // Нафиг нам старые заголовки, тем более что неизвестно что там
  headers = new HTTP_Response_Headers(); // Создаем новое хранилище заголовков

  int l_len = 2; // Длина текущей строки (учитывая CRLF)
  char l_buf[512]; // Буфер текущей строки
  int hlen = 0; // Длина всех заголовков

  while (!(buf[l_len-1]=='\n'&&buf[l_len-2]=='\r') && (l_len<maxlen))
    l_len++;
  if (!(buf[l_len-1]=='\n'&&buf[l_len-2]=='\r'))
    return 0;
  strncpy(l_buf, buf, l_len-2);
  l_buf[l_len-2] = 0;
  if (sscanf(l_buf, "HTTP/%d.%d %d", &http_ver_major, &http_ver_minor, &resp_code)<3)
    return 0;
  if (strlen(l_buf)>13)
  {
    resp_msg = new char[strlen(l_buf)-13+1];
    strcpy(resp_msg, l_buf+13);
  }
  buf += l_len;
  maxlen -= l_len;
  hlen+= l_len;

  do
  {
    l_len = 2;
    while (!(buf[l_len-1]=='\n'&&buf[l_len-2]=='\r') && (l_len<maxlen))
      l_len++;
    if (!(buf[l_len-1]=='\n'&&buf[l_len-2]=='\r'))
      return 0;
    if (l_len==2)
    {
      hlen += 2;
      break;
    }
    strncpy(l_buf, buf, l_len-2);
    l_buf[l_len-2] = 0;

    if (!headers->Add(l_buf))
      return 0;

    buf += l_len;
    maxlen -= l_len;
    hlen += l_len;
  } while (l_len>2);
  return hlen;
}

HTTP_Response::HTTP_Response()
{
  headers = NULL;
  resp_msg = NULL;
}

HTTP_Response::~HTTP_Response()
{
  if (resp_msg)
    delete resp_msg;
  if (headers)
    delete headers;
}
