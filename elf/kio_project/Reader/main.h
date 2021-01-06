#include "..\inc\swilib.h"

#define buffsize 512

class FileBuff
{
private:
  long fpos,next,step;
  int bufflen;
  char eof;
  char buff[buffsize];
  int file;
  unsigned int err;
  char operator [](int pos);
public:
  int FileSet(char *fname);
  void FileCl();
  char Get();
  char Next();
  void NextR();
  void Set(long pos=0);
  long Pos();
  char EOF();
};

#define pagescount 10

struct page
{
  unsigned int strt,len;
  page *next,*prev;
  char prg;
};

class PageBuff
{
private:
  page *pages,*curr,*last;
  void DrawLine(char ln);
  void FPage(page *pg);
  void FormatPage(unsigned int fpos=0);
  page operator [](char num);
public:
  void Init(unsigned long pos);
  void Destroy();
  void DrawPage();
  void Next();
  void Prev();
};
