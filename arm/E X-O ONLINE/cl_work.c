#include "c:/arm/inc/swilib.h"
#include "NatICQ.h"
#include "strings.h"
#include "main.h"
#include "cl_work.h"


extern volatile CLIST *cltop;
extern const unsigned int UIN;


//”ничтожить список
void FreeCLIST(void)
{
  CLIST *cl=(CLIST*)cltop;
  cltop=0;
  while(cl)
  {
    CLIST *p;
    if (cl->log) FreeLOGQ(&cl->log);
    if (cl->answer) mfree(cl->answer);
    if (cl->xtext) mfree(cl->xtext);
    p=cl;
    cl=(CLIST*)(cl->next);
    mfree(p);
  }
}

CLIST *FindContactByUin(unsigned int uin)
{
  CLIST *t;
  t=(CLIST *)cltop;
  while(t)
  {
    if ((t->uin==uin)&&(!t->isgroup)) break;
    t=t->next;
  }
  return(t);
}
