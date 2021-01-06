#ifndef _HTTP_H_
#define _HTTP_H_

#include "include.h"
#include "http_headers.h"
#include "url.h"
#include "mem.h"

class HTTP_Request
{
public:
  HTTP_Request();
  ~HTTP_Request();

  short Port;
  char * Path;
  char * Accept;
  char * Accept_Charset;
  char * Accept_Encoding;
  char * Accept_Language;
  char * Authorization;
  char * Expect;
  char * From;
  char * Host;
  char * If_Match;
  char * If_Modified_Since;
  char * If_None_Match;
  char * If_Range;
  char * If_Unmodified_Since;
  char * Max_Forwards;
  char * Proxy_Authorization;
  char * Range;
  char * Referer;
  char * Cookies;
  char * TE;
  char * User_Agent;
};

class HTTP_Response
{
public:
  int Parse(char * buf, int maxlen);

  HTTP_Response(Log * _log);
  ~HTTP_Response();

  int http_ver_major;
  int http_ver_minor;
  HTTP_RESP_CODES resp_code;
  char * resp_msg;
  HTTP_Response_Headers * headers;
private:
  Log * log;
};

#endif

