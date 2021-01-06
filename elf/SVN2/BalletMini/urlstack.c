#include "..\inc\swilib.h"
#include "urlstack.h"
#include "file_works.h"
#include "string_works.h"

extern const unsigned int PageSTACK_SIZE;

static const int DMonth[]={0,31,59,90,120,151,181,212,243,273,304,334,365};

typedef struct
{
  unsigned int ref_id;
  WSHDR* text;
}tUserText;

typedef struct
{
  unsigned int ref_id;
  unsigned int value;
  unsigned int id2;  
}tUserList;


typedef struct
{
  unsigned long id;
  unsigned int  view_line;
  unsigned int  pos_cur_ref;
  unsigned int user_text_counter;
  tUserText* user_text;
  unsigned int user_list_counter;
  tUserList* user_list;
}tPageStack;

tPageStack* PageSTACK;

static int stack_top;

static char * pagename(int n)
{
  char *s=malloc(300);
  char * omscache_path = getSymbolicPath("$omscache\\");
  sprintf(s,"%s%d.oms", omscache_path, PageSTACK[n].id);
  mfree(omscache_path);
  return s;
}

char* getCurrPageName()
{
  return pagename(stack_top-1);
}

void* getPageParams(void)
{
  return &(PageSTACK[stack_top]);
}

void setUserList(unsigned int refid, unsigned int value, unsigned int id2)
{
  for (int i = 0; i < PageSTACK[stack_top-1].user_list_counter; i++)
  {
    if (PageSTACK[stack_top-1].user_list[i].ref_id == refid)
    {
      PageSTACK[stack_top-1].user_list[i].value = value;
      PageSTACK[stack_top-1].user_list[i].id2 = id2;
      return;
    }
  }
  int cntr = PageSTACK[stack_top-1].user_list_counter++;
  PageSTACK[stack_top-1].user_list = realloc(PageSTACK[stack_top-1].user_list, 
                                             sizeof(tUserList)*(cntr+1));
  PageSTACK[stack_top-1].user_list[cntr].ref_id = refid;
  PageSTACK[stack_top-1].user_list[cntr].value = value;
  PageSTACK[stack_top-1].user_list[cntr].id2 = id2;
}

void setUserText(unsigned int refid, WSHDR* text)
{
  for (int i = 0; i < PageSTACK[stack_top-1].user_text_counter; i++)
  {
    if (PageSTACK[stack_top-1].user_text[i].ref_id == refid)
    {
      FreeWS(PageSTACK[stack_top-1].user_text[i].text);
      PageSTACK[stack_top-1].user_text[i].text = AllocWS(wstrlen(text));
      wstrcpy(PageSTACK[stack_top-1].user_text[i].text, text);
      return;
    }
  }
  int cntr = PageSTACK[stack_top-1].user_text_counter++;
  PageSTACK[stack_top-1].user_text = realloc(PageSTACK[stack_top-1].user_text, 
                                             sizeof(tUserText)*(cntr+1));
  PageSTACK[stack_top-1].user_text[cntr].ref_id = refid;
  PageSTACK[stack_top-1].user_text[cntr].text = AllocWS(wstrlen(text));
  wstrcpy(PageSTACK[stack_top-1].user_text[cntr].text, text);
}

void setPageParams(unsigned int view_line, unsigned int pos_cur_ref)
{
  PageSTACK[stack_top-1].view_line = view_line;
  PageSTACK[stack_top-1].pos_cur_ref = pos_cur_ref;
}

WSHDR* getUserTextByRefId(unsigned int refid)
{
  for (int i = 0; i < PageSTACK[stack_top-1].user_text_counter; i++)
  {
    if (PageSTACK[stack_top-1].user_text[i].ref_id == refid)
      return PageSTACK[stack_top-1].user_text[i].text;
  }
  return NULL;   
}

int getUserListByRefId(unsigned int refid , unsigned int *value, unsigned int *id2)
{
  for (int i = 0; i < PageSTACK[stack_top-1].user_list_counter; i++)
  {
    if (PageSTACK[stack_top-1].user_list[i].ref_id == refid)
    {
      *value = PageSTACK[stack_top-1].user_list[i].value;
      *id2 = PageSTACK[stack_top-1].user_list[i].id2;
      return 1;
    }
  }
  return 0;   
}

unsigned int getViewLine(void* data)
{
  return ((tPageStack*)(data))->view_line;
}
unsigned int getPosCurRef(void* data)
{
  return ((tPageStack*)(data))->pos_cur_ref;
}

static void killpage(int n)
{
  unsigned int err;
  char *fn=pagename(n);
  unlink(fn,&err);
  PageSTACK[n].id=0;
  PageSTACK[n].view_line=0;
  for (int i = 0; i < PageSTACK[n].user_text_counter; i++)
  {
    FreeWS(PageSTACK[n].user_text[i].text);
  }
  PageSTACK[n].user_text_counter = 0;
  mfree(PageSTACK[n].user_text);
  PageSTACK[n].user_text = NULL;
  PageSTACK[n].user_list_counter = 0;
  mfree(PageSTACK[n].user_list);
  PageSTACK[n].user_list = NULL;
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
    memmove(PageSTACK,PageSTACK+1,(PageSTACK_SIZE-1)*sizeof(tPageStack));
    stack_top--;
    zeromem(PageSTACK+stack_top, sizeof(tPageStack));
  }
  i=stack_top;
  //Убираем возможность пойти вперед ;)
  while(i!=PageSTACK_SIZE)
  {
    if (PageSTACK[i].id!=0)
    {
      killpage(i);
    }
    i++;
  }
  PageSTACK[stack_top].id=iday;
  return pagename(stack_top++);
}

char *PopPageFromStack(void)
{
  if (!stack_top) return NULL;
  return pagename(--stack_top);
}

int CheckPageStackTop(void)
{
  unsigned long retval = PageSTACK[stack_top].id;
  /*if (retval)
  {
    unsigned int err;
    FSTATS stat;
    char* toppagename = pagename(stack_top);
    if (GetFileStats(toppagename,&stat,&err)==-1) 
      retval = 0;
    mfree(toppagename);
  }*/
  return retval;
}

char *ForwardPageFromStack(void)
{
  if (stack_top==PageSTACK_SIZE) return NULL;
  if (!PageSTACK[stack_top].id) return NULL;
  return pagename(++stack_top);
}

void FreePageStack(void)
{
  int i=0;
  while(i!=PageSTACK_SIZE)
  {
    if (PageSTACK[i].id!=0)
    {
      killpage(i);
    }
    i++;
  }
  mfree(PageSTACK);
}

void UpPageStack(void)
{
  if (stack_top==PageSTACK_SIZE) return;
  stack_top++;
}

void InitUrlStack(void)
{
  stack_top = 0;
  PageSTACK = malloc((PageSTACK_SIZE+1)*sizeof(tPageStack));
  zeromem(PageSTACK, (PageSTACK_SIZE+1)*sizeof(tPageStack));
}
