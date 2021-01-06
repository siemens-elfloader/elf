#include "..\inc\swilib.h"
#include "urlstack.h"

static const int DMonth[]={0,31,59,90,120,151,181,212,243,273,304,334,365};

unsigned long PageSTACK[PageSTACK_SIZE];

extern char OMSCACHE_PATH[];

static int stack_top;

static char *pagename(int n)
{
  char *s=malloc(300);
  sprintf(s,"%s%d.oms",OMSCACHE_PATH,PageSTACK[n]);
  return s;
}

static void killpage(int n)
{
  unsigned int err;
  char *fn=pagename(n);
  unlink(fn,&err);
  PageSTACK[n]=0;
  mfree(fn);
}

char *PushPageToStack(void)
{
  unsigned long iday;
  TTime tt;
  TDate dd;
  int i;
  GetDateTime(&dd,&tt);
  dd.year=dd.year%100;
  iday=365*dd.year+DMonth[dd.month-1]+(dd.day - 1);
  iday=iday+(dd.year>>2);
  if (dd.month>2||(dd.year&3)>0)
    iday++;
  iday=(tt.sec+60*(tt.min+60*(tt.hour+24* iday)));
  
  if (stack_top==PageSTACK_SIZE)
  {
    //Убиваем лишнее
    killpage(0);
    memcpy(PageSTACK,PageSTACK+1,(PageSTACK_SIZE-1)*sizeof(int));
    PageSTACK[--stack_top]=0;
  }
  i=stack_top;
  //Убираем возможность пойти вперед ;)
  while(i!=PageSTACK_SIZE)
  {
    if (PageSTACK[i]!=0)
    {
      killpage(i);
    }
    i++;
  }
  PageSTACK[stack_top]=iday;
  return pagename(stack_top++);
}

char *PopPageFromStack(void)
{
  if (!stack_top) return NULL;
  return pagename(--stack_top);
}

char *ForwardPageFromStack(void)
{
  if (stack_top==PageSTACK_SIZE) return NULL;
  if (!PageSTACK[stack_top]) return NULL;
  return pagename(stack_top++);
}

void FreePageStack(void)
{
  int i=0;
  while(i!=PageSTACK_SIZE)
  {
    if (PageSTACK[i]!=0)
    {
      killpage(i);
    }
    i++;
  }  
}

void UpPageStack(void)
{
  if (stack_top==PageSTACK_SIZE) return;
  stack_top++;
}
