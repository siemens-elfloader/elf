/*********************************************
区号秀号码选择菜单部分(新), 1.8以后版本使用
作者：		BingK(binghelingxi)
最后修改:	2008.08.07
简述：
    改用多行菜单.
***********************************************/
#include "addr.h"
#include "type_.h"
extern WSTRING *AllocMenuWS(void *gui, int len);
extern void AppendInfoW(WSTRING *pWS, WSTRING * pNo);
extern void SetMLMenuItemText(void *data,void *item,WSTRING *ws1,WSTRING *ws2,int n);

extern int IsNum(unsigned short *pstr, int enable_dot);

void AddSpace(WSTRING *ws, int n)
{
  for(int i=0;i<n;i++)
  {
    ((void (*)(WSTRING *,int))ADDR_wsAppendChar)(ws, ' ');
  }
}

void AddNewLine(WSTRING *ws)
{
  ((void (*)(WSTRING *,int))ADDR_wsAppendChar)(ws, 0xD);
}

__thumb int IsNum(unsigned short *pstr, int enable_dot) //...
{
  if(!pstr) return 0;
  int len=pstr[0];
  if(!len) return 0;
  if(pstr[1]=='+')
  {
    pstr++;
    len--;
  }
  if(pstr[len]==0xE400)//...
  {
    if(enable_dot) len--;
    else return 0;
  }
  while(len>0)
  {
    int c=pstr[len];
    if(c>'9' || c<'0')
      return 0;
    len--;
  }
  return 1;
}

void setMenuText(void *gui, void *item, WSTRING *text,int item_n)
{
  WSTRING *ws2=((WSTRING *(*)(void *, int))AllocMenuWS_adr)(gui, 24);
  if(IsNum(text->pstr, 0))
  {
#define N 4
    AddSpace(ws2, N);
    AppendInfoW(ws2, text);
  }
  ((void (*)(void *, void *, WSTRING *, WSTRING *, int))SetMLMenuItemText_adr)(gui, item, text, ws2, item_n);
}

