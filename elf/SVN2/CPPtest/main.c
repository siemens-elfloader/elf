#include "include.h"
//#include "csm.h"
//#include "gui.h"
#include "File.h"
#include <stdarg.h>

const char _d[]="%d";
const char per_s[]="%s";
const char empty_str[]="";

typedef struct
{
  char *name;
  void* next;
}STRUCTT;

STRUCTT *top;

void Add(char *s)
{
  STRUCTT *t=(STRUCTT*)malloc(sizeof(STRUCTT));
  t->name = s;
  t->next = 0;

  if(!top) top = t;
  else
    top->next = t;
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


int main(char *exename, char *fname)
{
 // Mess("text");
//  Mess(123);

/*  Add("first");
  Add("second");

  STRUCTT *t=top;
  Message((void*)t->name,CHAR);
  t=(STRUCTT*)t->next;
  Message((void*)t->name,CHAR);
  mfree(top);*/
/*  CString mess("test");
  mess.add((void*)"\n=)",CHAR);
  mess.add((void*)12123,INT);
  Message((void*)mess.get(),CHAR);*/
 /* int i = 123;
  Message((void*)i,2);
  Message((void*)"text",CHAR);
  CFile file("4:\\test.txt"); 
  char s[6];
  
  file.Open(A_Create + A_ReadWrite);
  file.Write("test",4);
  file.Close();
  
  file.SetFileName("4:\\test2.txt");
  file.Open(A_Create + A_ReadWrite);
  file.Write("test2",5);
  file.Close();
  
  file.Open(A_ReadOnly);
  //file.Read(s,4);
//  ShowMSG(1,(int)s);
  //char *p = file.ReadBuf(file.Size());
//  ShowMSG(1,(int)p);
  //sprintf(s,"%d",file.Size());
//  ShowMSG(1,(int)s);
  file.Close();*/
  //mfree(p);
  return 0;
}
