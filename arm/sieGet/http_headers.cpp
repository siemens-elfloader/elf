#include "include.h"
#include "http_headers.h"
#include "log.h"

/*******************************************************************************
  HTTP Response Headers
*******************************************************************************/

typedef struct
{
  HTTP_RESP_HEADERS id;
  char * name;
} HTTP_RESP_HEADER_DESC;

HTTP_RESP_HEADER_DESC resp_headers[N_HTTP_RESP_HEADERS] =
{
  {RESP_Accept_Ranges       , "Accept-Ranges"},
  {RESP_Age                 , "Age"},
  {RESP_Cache_Control       , "Cache-Control"},
  {RESP_Connection          , "Connection"},
  {RESP_Content_Disposition , "Content-Disposition"},
  {RESP_Content_Encoding    , "Content-Encoding"},
  {RESP_Content_Language    , "Content-Language"},
  {RESP_Content_Length      , "Content-Length"},
  {RESP_Content_Location    , "Content-Location"},
  {RESP_Content_MD5         , "Content-MD5"},
  {RESP_Content_Range       , "Content-Range"},
  {RESP_Content_Type        , "Content-Type"},
  {RESP_Date                , "Date"},
  {RESP_ETag                , "ETag"},
  {RESP_Expires             , "Expires"},
  {RESP_Last_Modified       , "Last-Modified"},
  {RESP_Location            , "Location"},
  {RESP_Pragma              , "Pragma"},
  {RESP_Proxy_Authenticate  , "Proxy-Authenticate"},
  {RESP_Retry_After         , "Retry-After"},
  {RESP_Server              , "Server"},
  {RESP_Set_Cookie          , "Set-Cookie"},
  {RESP_Trailer             , "Trailer"},
  {RESP_Transfer_Encoding   , "Transfer-Encoding"},
  {RESP_Upgrade             , "Upgrade"},
  {RESP_Vary                , "Vary"},
  {RESP_Via                 , "Via"},
  {RESP_WWW_Authenticate    , "WWW-Authenticate"},
  {RESP_Warning             , "Warning"}
};

int HTTP_Response_Headers::GetHeaderId(char * header_name)
{
  int l = 0;
  int r = N_HTTP_RESP_HEADERS-1;
  while (l<=r)
  {
    int m = (l+r)>>1;
    int cmp_res = stricmp(resp_headers[m].name, header_name);
    if (cmp_res==0) return resp_headers[m].id;
    if (cmp_res>0)
      r = m-1;
    else
      l = m+1;
  }
  return -1;
}

int HTTP_Response_Headers::SplitHeader(char *header, char *name, char *value)
{
  int len = strlen(header);
  int delim_pos = strchr(header, ':')-header;
  if (delim_pos!=0 && delim_pos<len-1)
  {
    strncpy(name, header, delim_pos);
    name[delim_pos] = 0;
    int vstart_pos = delim_pos+1;
    while (vstart_pos<len && header[vstart_pos]==' ')
      vstart_pos++;
    strncpy(value, header+vstart_pos, len-vstart_pos+1);
    return 1;
  }
  else
    return 0;
}

int HTTP_Response_Headers::Add(char *str)
{
  char *h_name = new char[strlen(str)];
  char *h_value = new char[strlen(str)];
  int id;
  if (SplitHeader(str, h_name, h_value))
  {
    id = GetHeaderId(h_name);
    if (id!=-1)
    {
      headers[id] = h_value;
      log->Print(str, CLR_DarkBlue);
      delete h_name;
      return 1;
    }
    log->Print(str, CLR_LightBlue);
    delete h_name;
    delete h_value;
    return 1;
  }
  delete h_name;
  delete h_value;
  return 0;
}

char * HTTP_Response_Headers::GetValue(char * name)
{
  int id = GetHeaderId(name);
  if (id!=-1)
    return headers[id];
  else
    return NULL;
}

HTTP_Response_Headers::HTTP_Response_Headers(Log * _log)
{
  log = _log;
  for (int i=0; i<N_HTTP_RESP_HEADERS; i++)
    headers[i] = NULL;
}

HTTP_Response_Headers::~HTTP_Response_Headers()
{
  for (int i=0; i<N_HTTP_RESP_HEADERS; i++)
    _safe_delete(headers[i]);
}
