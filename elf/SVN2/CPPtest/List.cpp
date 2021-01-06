#include "..//inc//swilib.h"
#include "List.h"

void CList::add(LIST_STRUCT* item)
{
  if(!toplist) toplist = item;
  else
    toplist->next = item;
}

void CList::free()
{
  LIST_STRUCT *t = toplist;
  toplist = NULL;
  
  while(t)
  {
    LIST_STRUCT *tt = t;
    mfree(tt);
    t = (LIST_STRUCT*)t->next;
  }
}

CList::CList()
{
  free();
}

CList::~CList()
{
  free();
}


LIST_STRUCT* CList::getByItem(int curitem)
{
  LIST_STRUCT* t = toplist;
  int i = 0;
  while(t)
  {
    if(i++ == curitem) return t;
    t = (LIST_STRUCT*)t->next;
  }
  return 0;
}
/*
LIST_STRUCT* CList::gettop()
{
  return toplist;
}*/
