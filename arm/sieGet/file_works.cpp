#include "include.h"
#include "string_util.h"
#include "file_works.h"

char * getSymbolicPath(const char * cFileName)
{
  int ps = NULL;
  int pp = NULL;
  char * path = new char[strlen(CFG_SIEGET_FOLDER) + strlen(cFileName) + 32];
  while (ps < strlen(cFileName))
  {
    if (cFileName[ps] == '$')
    {
      ps++;
      switch (cFileName[ps])
      {
      case 'b':
        if (cFileName[ps + 1] == 'o') // bookmakrs
        {
          strcpy(path + pp, CFG_SIEGET_FOLDER);
          pp += strlen(CFG_SIEGET_FOLDER);
          strcpy(path + pp, "Bookmarks");
          pp += 9;
          ps += 9;
          continue;
        }
      case 'i':
        if (cFileName[ps + 1] == 'm') // img
        {
          strcpy(path + pp, CFG_SIEGET_FOLDER);
          pp += strlen(CFG_SIEGET_FOLDER);
          strcpy(path + pp, "img");
          pp += 3;
          ps += 3;
          continue;
        }
      case 'l':
        if (cFileName[ps + 1] == 'o') // logs
        {
          strcpy(path + pp, CFG_SIEGET_FOLDER);
          pp += strlen(CFG_SIEGET_FOLDER);
          strcpy(path + pp, "Logs");
          pp += 4;
          ps += 4;
          continue;
        }
      case 's':
        if (cFileName[ps + 1] == 'i') // sieget
        {
          strcpy(path + pp, CFG_SIEGET_FOLDER);
          pp += strlen(CFG_SIEGET_FOLDER) - 1;
          ps += 6;
          continue;
        }
        if (cFileName[ps + 1] == 'o') // sounds
        {
          strcpy(path + pp, CFG_SIEGET_FOLDER);
          pp += strlen(CFG_SIEGET_FOLDER);
          strcpy(path + pp, "Sounds");
          pp += 6;
          ps += 6;
          continue;
        }
      default:
        path[pp++]='$';
      }
    }
    else
    {
      path[pp++] = cFileName[ps++];
    }
  }
  path[pp] = NULL;
  make_dirs(path); // Создаем все несуществующие папки в пути
  return path;
}

/*
  Сравнивает расширение файла с указанным в параметре
  fname - имя файла;
  mask - нужное нам расширение;
  Пример: if (is_file("0:\\Music\\1.mp3", "mp3")
*/
int is_file(const char * fname, const char * mask)
{
  int fname_len = strlen(fname);
  int mask_len = strlen(mask);
  
  if (!fname_len && !mask_len)
    return 0;
  
  if (fname[fname_len - mask_len - 1] != '.')
    return 0;
  
  for (int i = fname_len, p = mask_len; i && p; i --, p --)
  {
    if (tolower(fname[i]) != tolower(mask[p]))
      return 0;
  }
  return 1;
}

int is_file_exists(const char * fname)
{
  FSTATS fstat;
  unsigned int io_error;
  return (GetFileStats(fname, &fstat, &io_error)!=-1);
}

int get_file_size(const char * fname)
{
  unsigned int io_error;
  FSTATS fs;
  if (GetFileStats(fname, &fs, &io_error)==-1)
    return 0;
  return (fs.size);
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

