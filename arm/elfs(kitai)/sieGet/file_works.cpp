#include "include.h"
#include "string_util.h"
#include "file_works.h"

void getSymbolicPath(char * path, const char * cFileName)
{
  int ps = NULL;
  int pp = NULL;
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
          make_dir(path);
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
          make_dir(path);
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
          make_dir(path);
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
          make_dir(path);
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
}

int Is_URL_File(const char *s)
{
  int len=strlen(s);
  if(s && len)
  {
    if(s[len-4]=='.' &&
       (s[len-3]=='u' || s[len-3]=='U')&&
       (s[len-2]=='r' || s[len-2]=='R')&&
       (s[len-1]=='l' || s[len-1]=='L'))
    return (1);
  }
  return (0);
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

int make_dir(const char * dir_fname)
{
  unsigned int io_error;
  if (!isdir(dir_fname, &io_error))
  {
    mkdir(dir_fname, &io_error);
    return 1;
  }
  return 0;
}
