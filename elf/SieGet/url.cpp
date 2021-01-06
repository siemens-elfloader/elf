#include "include.h"

#include "url.h"
#include "gui.h"
#include "log.h"

extern "C"
{
  extern unsigned long strtoul(const char *, char **, int);
};

extern char percent_t[];

#define ST_ERR -1
#define ST_FINISH 0
#define ST_HOST 1
#define ST_PORT 2
#define ST_PATH 3
#define ST_PARAM 4
#define ST_FRAGMENT 5

char *URL::Print()
{
  return NULL;
}

char host_term[] = ":/?#";
int  host_st[] = {ST_PORT, ST_PATH, ST_PARAM, ST_FRAGMENT};
char port_term[] = ":/?#";
int  port_st[] = {ST_ERR, ST_PATH, ST_PARAM, ST_FRAGMENT};
char path_term[] = "?#";
int  path_st[] = {ST_PARAM, ST_FRAGMENT};
char param_term[] = "#";
int  param_st[] = {ST_FRAGMENT};

int URL::Parse(char *s_url)
{
  char *tmp = s_url;
  char *scheme_delim = strstr(tmp, "://");
  if (scheme_delim)
  {
    int schlen = scheme_delim-tmp;
    this->scheme = new char[schlen+1];
    strncpy(this->scheme, tmp, schlen);
    this->scheme[schlen] = 0;
    tmp += schlen+3;
  }
  else
  {
    this->scheme = new char[5];
    strcpy(this->scheme, "http");
  }
  int st = ST_HOST;
  int len = strlen(tmp);
  int clen = 0;
  while (st>0)
  {
    switch(st)
    {
    case ST_HOST:
      if (strchr(host_term, tmp[clen]) || !tmp[clen])
      {
        if (tmp[clen])
          st = host_st[strchr(host_term, tmp[clen])-host_term];
        else
          st = ST_FINISH;
        this->host = new char[clen+1];
        strncpy(this->host, tmp, clen);
        this->host[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    case ST_PORT:
      this->port = strtoul(tmp, &tmp, 10);
      if (tmp[clen])
        st = port_st[strchr(port_term, *tmp++)-port_term];
      else
        st = ST_FINISH;
      break;
    case ST_PATH:
      if (strchr(path_term, tmp[clen]) || !tmp[clen])
      {
        if (tmp[clen])
          st = path_st[strchr(path_term, tmp[clen])-path_term];
        else
          st = ST_FINISH;
        this->path = new char[clen+1];
        strncpy(this->path, tmp, clen);
        this->path[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    case ST_PARAM:
      if (strchr(param_term, tmp[clen]) || !tmp[clen])
      {
        if (tmp[clen])
          st = param_st[strchr(param_term, tmp[clen])-param_term];
        else
          st = ST_FINISH;
        this->param = new char[clen+1];
        strncpy(this->param, tmp, clen);
        this->param[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    case ST_FRAGMENT:
      if (!tmp[clen])
      {
        st = ST_FINISH;
        this->fragment = new char[clen+1];
        strncpy(this->fragment, tmp, clen);
        this->fragment[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    }
  }
  if (this->port==0)
    this->port = 80;
  return 1;
}

URL::~URL()
{
  if (this->fragment)
    delete this->fragment;
  if (this->host)
    delete this->host;
  if (this->param)
    delete this->param;
  if (this->path)
    delete this->path;
  if (this->scheme)
    delete this->scheme;
}

URL::URL()
{
  fragment = NULL;
  host = NULL;
  param = NULL;
  path = NULL;
  scheme = NULL;
}

//---------------------------------------------------------------

// ELKA Compatibility

inline void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

inline void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

inline void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

//---------------------------------------------------------------

int urlinput_onkey(GUI *gui, GUI_MSG *msg)
{
  URLInput *ui = (URLInput *)EDIT_GetUserPointer(gui);
  return ui->onKey(gui, msg);
}

void urlinput_ghook(GUI *gui, int cmd)
{
  URLInput *ui = (URLInput *)EDIT_GetUserPointer(gui);
  ui->gHook(gui, cmd);
}

void urlinput_locret(void) {};

SOFTKEY_DESC urlinput_sk[]=
{
  {0x0018,0x0000,(int)"Ok"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB urlinput_skt=
{
  urlinput_sk,0
};

HEADER_DESC urlinput_hdr={0,0,0,0,NULL,(int)"Введите URL...",LGP_NULL};

INPUTDIA_DESC urlinput_desc=
{
  1,
  urlinput_onkey,
  urlinput_ghook,
  (void *)urlinput_locret,
  0,
  &urlinput_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// Поменять софт-кнопки
};

int  URLInput::onKey(GUI *gui, GUI_MSG *msg)
{
  if ((msg->gbsmsg->msg==KEY_DOWN && msg->gbsmsg->submess==ENTER_BUTTON && EDIT_GetFocus(gui)==ok_pos) || (msg->keys==0x18))
  {
      result = 1;
      return GUI_RESULT_CLOSE;
  }
  if (msg->gbsmsg->msg==KEY_DOWN && msg->gbsmsg->submess==ENTER_BUTTON && EDIT_GetFocus(gui)==cancel_pos)
      return GUI_RESULT_CLOSE;
  return (GUI_RESULT_OK);
}

void URLInput::gHook(GUI *gui, int cmd)
{
  if (cmd==TI_CMD_DESTROY)
  {
    if (result)
    {
      EDITCONTROL ec;
      ExtractEditControl(gui, url_pos, &ec);
      char url_str[512];
      int new_len;
      ws_2utf8(ec.pWS, url_str, &new_len, 511);
      DEBUG(url_str);
      url->Parse(url_str);
      onFinish();
    }
    else
      onCancel();
    delete this;
  }
}

void URLInput::Show()
{
  result = 0;

  WSHDR *ws = AllocWS(256);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;

  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(ws, percent_t, "http://");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 256);
  url_pos = AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ws, percent_t, "-----");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, 256);
  ok_pos = AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ws, percent_t, "Ok");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_LINK, ECF_APPEND_EOL, ws, 256);
  ok_pos = AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ws, percent_t, "Отмена");
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_LINK, ECF_APPEND_EOL, ws, 256);
  cancel_pos = AddEditControlToEditQend(eq,&ec,ma);

  patch_header(&urlinput_hdr);
  patch_input(&urlinput_desc);
  CreateInputTextDialog(&urlinput_desc,&urlinput_hdr,eq,1,this);
}

void URLInput::onFinish()
{
  DEBUG("URLInput::onFinish()");
  char tmp[512];
  if (url->scheme)
  {
    sprintf(tmp, "Scheme: %s", url->scheme);
    DEBUG(tmp);
  }
  if (url->host)
  {
    sprintf(tmp, "Host: %s", url->host);
    DEBUG(tmp);
  }
  sprintf(tmp, "Port: %d", url->port);
  DEBUG(tmp);
  if (url->path)
  {
    sprintf(tmp, "Path: %s", url->path);
    DEBUG(tmp);
  }
  if (url->param)
  {
    sprintf(tmp, "Params: %s", url->param);
    DEBUG(tmp);
  }
  if (url->fragment)
  {
    sprintf(tmp, "Fragment: %s", url->fragment);
    DEBUG(tmp);
  }
}

void URLInput::onCancel()
{
  DEBUG("URLInput::onCancel()");
}

URLInput::URLInput()
{
  url = new URL();
}

URLInput::~URLInput()
{
  delete url;
}
