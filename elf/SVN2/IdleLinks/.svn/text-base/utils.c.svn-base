#include "..\inc\swilib.h"

void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}

void patch_header_small(HEADER_DESC* head)
{
  head->rc.x=3;
#ifndef ELKA
  head->rc.y=YDISP+0x18;
#else
  head->rc.y=YDISP+35;
#endif
  head->rc.x2=ScreenW()-3-1;
#ifndef ELKA
  head->rc.y2=YDISP+0x18+0x13;
#else 
    head->rc.y2=YDISP+35+34;
#endif
}

void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

int file_exists(const char * fname)
{
  int handle;
  unsigned int err;
  handle = fopen(fname, A_ReadOnly, P_READ, &err);
  if (handle == -1)
    return 0;
  fclose(handle, &err);
  return 1;
}

// Удаление расширения из имени файла
void del_ext(char * source)
{
  while(*source)source++;
  while(*source!='.')source--;
  *source=0;
}



#ifdef LOG

int LOG_MESSAGE_COUNT =1;
const char logfile[] = "0:\\IL_log.txt";
char q[40];


void log(char *module, char* description, char *logdata)
{
  volatile int hFile;
  unsigned int io_error = 0;
  char* buffer = malloc(65536);
  zeromem(buffer,65536);
  sprintf(buffer,"[%d] : [%s]: %s (%s)\r\n", LOG_MESSAGE_COUNT, module, description, logdata);
  int buf_len = strlen(buffer);
  // Открываем файл на дозапись и создаём в случае неудачи
  hFile = fopen(logfile,A_ReadWrite +A_Create+ A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  if(!io_error)
  {
    fwrite(hFile, buffer, buf_len-1, &io_error);
    fclose(hFile, &io_error);
  }
  else
  {
    sprintf(q, "Log:[%s] I/O Err #%u", module, io_error);
    LockSched();
    ShowMSG(1,(int)q); 
    UnlockSched();
  }
  mfree(buffer);
  LOG_MESSAGE_COUNT++;
}
#endif

int tolower(int C)
{
//  if ((C>='A' && C<='Z')) C-='A'-'a';
    if(C<0x80)
    {
      if(C>='A' && C<='Z') C += ('a' - 'A');
      return C;
    }
      if(C >= 0x90 && C<=0xAF) C+= (0xB0 - 0x90);
  return(C);
}

// Аналог strcmp, но без чувствительности к регистру
int stricmp(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=tolower(*s++);
    ds=tolower(*d++);
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

extern short *ScreenBuff;

void GetScreenShot()
{
  ScreenBuff = malloc((ScreenH()*ScreenW())*2);
  memcpy(ScreenBuff, RamScreenBuffer(), 2*ScreenW()*ScreenH());

#ifdef LOG  
  log("utils.c", "Create screenshot", (char*)ScreenBuff);
#endif
}





