#include "../inc/swilib.h"
#include "string_works.h"
#include "img_works.h"

int AddPicIfNotExist(DYNPNGILIST_MY **top, char *fname)
{
  DYNPNGILIST_MY *t, *p;
  IMGHDR *img;
  int n=0;
  t=(DYNPNGILIST_MY *)top;
  while((p=t->dpl.next))
  {
    t=p;
    if (!strcmp_nocase(t->fname, fname)) return t->uni_n;
    n++;
  }
  // Не нашли в кэше, пробуем добавить
  img=CreateIMGHDRFromPngFile(fname,0);
  if (!img) return (-1);
  // Получилось создать картинку
  n+=FIRST_UCS2_BITMAP;
  t=t->dpl.next=malloc(sizeof(DYNPNGILIST_MY));
  t->uni_n=n;
  t->dpl.next=0;
  t->dpl.icon=GetPicNByUnicodeSymbol(n);
  t->dpl.img=img;
  t->fname=malloc(strlen(fname)+1);
  strcpy(t->fname,fname);
  return (n);
}
