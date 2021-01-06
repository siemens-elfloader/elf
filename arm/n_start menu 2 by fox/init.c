#include "..\inc\swilib.h"

extern const char path[128];
char temp[128];
char LinkCounters[10];

void InitUnderlinks_count()
{
  int f;
  int fsize;
  FSTATS stat;
  unsigned int ul;
  sprintf(temp, "%slinkcounters.fx", path);
  GetFileStats(temp,&stat,&ul);
  if(stat.size>0)
  {
    f=fopen(temp,A_ReadOnly+A_BIN,P_READ,&ul);
    fsize=stat.size;
    char *p=malloc(fsize);
    p[fread(f,p,fsize,&ul)];
    fclose(f,&ul);
    strcpy(LinkCounters, p);
    LinkCounters[fsize]='\0';
    mfree(p);
  }
}

void InitFiles()
{
  InitUnderlinks_count();
}
