#include "../inc/swilib.h"
#include "List.h"

int CList::add(LIST_STRUCT* item)
{
  if(!item) return (-1);
  if(!this->toplist) this->toplist = item;
  else
    this->toplist->next = item;  

  return (1);
}

void CList::free()
{
  LockSched(); 
  LIST_STRUCT *t = this->toplist;
  this->toplist = NULL;
  UnlockSched();
  while(t && t->next)
  {
    LIST_STRUCT *t_prev = t;
    t = t->next;
    mfree(t_prev);
  }
}

CList::CList()
{
  this->toplist = 0;
}

CList::~CList()
{
  this->free();
}


LIST_STRUCT* CList::getByItem(int curitem)
{
  LIST_STRUCT* t = this->toplist;
  int i = 0;
  while(t)
  {
    if(i == curitem) return t;
    i++;
    t = (LIST_STRUCT*)t->next;
  }
  return 0;
}

int CList::getCount()
{
  LIST_STRUCT* t = this->toplist;
  int i = 1;
  while((t = (LIST_STRUCT*)t->next)) i++;
  return i;
}
/*
LIST_STRUCT* CList::gettop()
{
  return toplist;
}*/
