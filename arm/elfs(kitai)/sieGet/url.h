#ifndef _URL_H_
#define _URL_H_

#include "include.h"
#include "log.h"

// scheme://host:port/path?param#fragment
class URL
{
public:
  int Parse(char * s_url);
  void Print(Log * log);

  char * scheme;
  char * host;
  short port;
  char * path;
  char * param;
  char * fragment;

  URL();
  ~URL();
};

class URLFile
{
public:
  int Read(char * file);
  int Write(char * file);
  char * url;
  
  URLFile();
  ~URLFile();
};

#endif
