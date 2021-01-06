#include "..\inc\swilib.h"
#include "List.h"
#include "File.h"

CList *list;

void FillStruct(char *name)
{
  LIST_STRUCT *t = new LIST_STRUCT();
  t->name = name;
  t->next = 0;
  list->add(t);
}

void Message(char *s) 
{
   ShowMSG(1,(int)s);
};

void Message(int i)
{
   const char _d[]="%d";
   char s[32];
   sprintf(s,_d,i);      
   ShowMSG(1,(int)s);
};


int main()
{
  list = new CList;

  FillStruct("First");  
  FillStruct("Second");  
  FillStruct("Three");
  
  CFile file("4:\\list.txt");
  file.open(A_Create+A_Append+A_ReadWrite);
//  Message(list->getCount());
  for(int i=0;i<list->getCount();i++)
  {
    file.write(list->getByItem(i)->name,strlen(list->getByItem(i)->name));
    file.write("\n",1);
  }
  
  ShowMSG(1,(int)"End");
  file.close();
  delete list;
}
