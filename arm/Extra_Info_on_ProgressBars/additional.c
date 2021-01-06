#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"

extern void(*OldDraw)(void *);
extern char* LoadConfigData(const char *fn);
void PrintProgress(void **data);

#ifndef ELKA
#define DEFAULT_DISK "0"
extern void(*OldEnter1)(void *, int param);
void enter1(void* data, int param)
{
  OldEnter1(data,param);
  if (param==3)
  {
    ((int*)FreeRAM())[0x20]=0;
  }
}
#else
#define DEFAULT_DISK "4"
#endif

void MyDraw(void *data)
{
  OldDraw(data);
  PrintProgress(data);
}

extern const CFG_HDR cfghdr0;
extern const unsigned int enable;
extern const char str_f[16];
extern const char str_color[4];
extern const char str_bgcolor[4];
extern const char percent_color[4];
extern const char percent_bgcolor[4];

void PrintProgress(void **data)
{
  if (!*((int*)data))
    return;
  int** param=(int**)FreeRAM()+0x20;
  if (!param[1]){
    param[1] = (int*)LoadConfigData(DEFAULT_DISK":\\ZBin\\etc\\Extra_Info.bcfg");
    if (!param[1])
      return;
  }
  char* cfg = (char*)param[1];
  int cfg_begin = (int)&cfghdr0;
  if (!cfg[(int)&enable-cfg_begin])
    return;
  cfg -= cfg_begin;
  
  RECT* coord = *data;
#ifndef ELKA
  int current = ((int*)data)[0x30/4];
  int all = ((int*)data)[0x2C/4];
#else
  int current = ((int*)data)[0x34/4];
  int all = ((int*)data)[0x30/4];
#endif
  
#ifndef ELKA
  int type = (int)param[0];
  char* format_str=0;
  switch (type){
  case 0x52:
    format_str=cfg+(int)&str_f;
    current <<= 1;
    all <<= 1;
    break;
  case 0x53:
    format_str=cfg+(int)&str_f;
    current >>= 10;
    all >>= 10;
    break;
  case 0:
  default:
    format_str="%d/%d";
  }
#endif
  
  WSHDR* ws = AllocWS(32);
#ifndef ELKA
  wsprintf(ws,format_str,current,all);//сюда можно засунуть еще какие-нибудь навороты типа имени передаваемого файла
#else
  wsprintf(ws,"%d/%d",current,all);
#endif
  int offset = GetFontYSIZE(FONT_SMALL)+2;
  DrawString(ws,
             coord->x,coord->y-offset,coord->x2,coord->y,
             FONT_SMALL,TEXT_ALIGNMIDDLE,
             cfg+(int)&str_color,
             cfg+(int)&str_bgcolor);
  wsprintf(ws,"%d%",udiv(all,current*100));
  DrawString(ws,
             coord->x,coord->y+1,coord->x2,coord->y2,
             FONT_SMALL,TEXT_ALIGNMIDDLE,
             cfg+(int)&percent_color,
             cfg+(int)&percent_bgcolor);
  FreeWS(ws);
}
