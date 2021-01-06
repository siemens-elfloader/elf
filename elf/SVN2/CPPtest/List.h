#ifndef _LIST_H_
#define _LIST_H_

typedef struct
{
  char *name;
  void *next;
}LIST_STRUCT;

class CList
{
private:
  LIST_STRUCT *toplist;
public:
  void add(LIST_STRUCT*);
  LIST_STRUCT* getByItem(int curitem);
  LIST_STRUCT* gettop() {return toplist;};
  void free();
  
  CList();
  ~CList();
};


#endif

