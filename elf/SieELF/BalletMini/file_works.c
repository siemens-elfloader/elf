#include "../inc/swilib.h"
#include "string_works.h"
#include "file_works.h"

extern char BALLET_PATH[256];

char * getSymbolicPath(const char * cFileName)
{
  int ps = NULL;
  int pp = NULL;
  char * path = (char *)malloc(strlen(BALLET_PATH) + strlen(cFileName) + 32);
  while (ps<strlen(cFileName))
  {
    if (cFileName[ps]=='$')
    {
      ps++;
      switch (cFileName[ps])
      {
      case 'b':
        if (cFileName[ps+1]=='a') // ballet
        {
          strcpy(path + pp, BALLET_PATH);
          pp+=strlen(BALLET_PATH)-1;
          ps+=6;
          continue;
        }
        if (cFileName[ps+1]=='o') // bookmakrs
        {
          strcpy(path+pp,BALLET_PATH);
          pp+=strlen(BALLET_PATH);
          strcpy(path+pp,"Bookmarks");
          pp+=9;
          ps+=9;
          continue;
        }
      case 'd': // date
        {
          TDate d;
          GetDateTime(&d,NULL);
          char c[9];
          sprintf(c,"%.4d%.2d%.2d",d.year,d.month,d.day);
          strcpy(path+pp,c);
          pp+=8;
          ps+=4;
          continue;
        }
      case 'o': // omscache
        {
          strcpy(path+pp,BALLET_PATH);
          pp+=strlen(BALLET_PATH);
          strcpy(path+pp,"OmsCache");
          pp+=8;
          ps+=8;
          continue;
        }
      case 'r':
        if (cFileName[ps+1]=='e') // resources
        {
          strcpy(path+pp,BALLET_PATH);
          pp+=strlen(BALLET_PATH);
//          strcpy(path+pp,"Resouces");
//          pp+=9;
          ps+=9;
          strcpy(path+pp,"img");
          pp+=3;
          continue;
        }
        if (cFileName[ps+1]=='o') // root
        {
          memcpy(path+pp,BALLET_PATH,2);
          pp+=2;
          ps+=4;
          continue;
        }
      case 's': // search
        {
          strcpy(path + pp, BALLET_PATH);
          pp+=strlen(BALLET_PATH);
          strcpy(path+pp,"Search");
          pp+=6;
          ps+=6;
          continue;
        }
      case 'u': // urlcache
        {
          strcpy(path+pp,BALLET_PATH);
          pp+=strlen(BALLET_PATH);
          strcpy(path+pp,"UrlCache");
          pp+=8;
          ps+=8;
          continue;
        }
      case 't': // time
        {
          TTime t;
          GetDateTime(NULL,&t);
          char c[7];
          sprintf(c,"%.2d%.2d%.2d",t.hour,t.min,t.sec);
          strcpy(path+pp,c);
          pp+=6;
          ps+=4;
          continue;
        }
      default:
        path[pp++]='$';
      }
    }
    else
    {
      path[pp++]=cFileName[ps++];
    }
  }
  path[pp]=0;
  make_dirs(path);
  return path;
}

int ballet_fexists(const char * cFileName)
{
  char * path = getSymbolicPath(cFileName);
  FSTATS fs;
  unsigned int ul;
  int res = (GetFileStats(path, &fs, &ul)!=-1);
  mfree(path);
  return res;
}

int make_dirs(const char * path)
{
  int c, i = 0;
  unsigned int io_error;
  char tmp[256], * s;
  strcpy(tmp, path);
  s = tmp;
  while((s = strchr(s, '\\')))
  {
    s++;
    c = *s;
    *s = 0;
    i += mkdir(tmp, &io_error);
    *s = c;
  }
  return (i);
}
