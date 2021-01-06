#include "..\inc\swilib.h"
#include "strlib.h"

// ѕреобразование в нижний регистр
char* str2lower(char *st)
{
  unsigned int len = strlen(st);
  for(int i=0;i<len;i++)
  {
    char sym = *(st+i);
    if(sym<0x80)
    {
      if(st[i]>='A' && st[i]<='Z') st[i] += ('a' - 'A');
      continue;
    }
    if(sym<0xe0)
    {
      i++;
      if(st[i] >= 0x90 && st[i]<=0xAF) st[i]+= (0xB0 - 0x90);
    }
  }
  return st;
}

// јналог strcmp, но без чувствительности к регистру
int stricmp(char *str1, char *str2)
{
  if(!str1 || !str2)return NULL;
  char *i_str1 = malloc(strlen(str1)+1);
  char *i_str2 = malloc(strlen(str2)+1);
  strcpy(i_str1, str1);
  strcpy(i_str2, str2);
  str2lower(i_str1);
  str2lower(i_str2);
  // —равниваем уже строки в нижнем регистре
  int res= strcmp(i_str1, i_str2);
  mfree(i_str1);
  mfree(i_str2);
  return res;
}

// јналог strstr, но без чувствительности к регистру
char *stristr(char *haystack, char *needle)
{
  if(!haystack || !needle)return NULL;
  char *i_haystack = malloc(strlen(haystack)+1);
  char *i_needle = malloc(strlen(needle)+1);
  strcpy(i_haystack, haystack);
  strcpy(i_needle, needle);
  str2lower(i_haystack);
  str2lower(i_needle);
  // —равниваем уже строки в нижнем регистре и считаем смещение
  char *q = strstr(i_haystack, i_needle);
  mfree(i_haystack);
  mfree(i_needle);
  if(!q)  // «начит, нет подстроки
  {
    return NULL;
  }
  int delta = q - i_haystack;
  return haystack + delta;  // ≈сть подстрока, очевидно, по тому же смещению
}

//EOL,EOF
