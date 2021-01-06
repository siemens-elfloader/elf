#ifndef _LIST_H_
#define _LIST_H_

typedef struct _LIST_STRUCT
  {
    char *name;
    _LIST_STRUCT *next;
  }LIST_STRUCT;
  

class CList
{
private:  
  LIST_STRUCT *toplist, *list;
public:
  int add(LIST_STRUCT*);
  LIST_STRUCT* getByItem(int curitem);
  LIST_STRUCT* gettop() {return toplist;};
  int getCount();
  void free();
  
  CList();
  ~CList();
};


#endif

