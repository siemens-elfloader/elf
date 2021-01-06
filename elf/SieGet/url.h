#ifndef _URL_H_
#define _URL_H_

#include "include.h"

// scheme://host:port/path?param#fragment
class URL
{
public:
  char *Print();
  int Parse(char *s_url);

  char *scheme;
  char *host;
  short port;
  char *path;
  char *param;
  char *fragment;

  URL();
  ~URL();
};

class URLInput
{
public:
  void Show();

  void onFinish();
  void onCancel();

  URLInput();
  ~URLInput();

  URL *url;

  int onKey(GUI *gui, GUI_MSG *msg);
  void gHook(GUI *gui, int cmd);
private:
  int url_pos;
  int ok_pos;
  int cancel_pos;

  int result;
};

#endif
