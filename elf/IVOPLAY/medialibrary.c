#include "../inc/swilib.h"
#include "conf_loader.h"
#include "main.h"

char nname[256];
extern const char format_1[4],format_2[4],format_3[4],format_4[4];

void BEER(char *foldeer)
{
  DIR_ENTRY de;
  unsigned int err;
  char path[128],ddd[320];
  sprintf(path,"%s\\*",foldeer);
  path[0]='0';
  FSTATS stat;
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      if (!IsFile(de.file_name))
      {
        sprintf(ddd,"%s\\%s",de.folder_name,de.file_name);
        BEER(ddd);
        rmdir(ddd,&err);
      }
      else
      {
        sprintf(ddd,"%s\\%s",de.folder_name,de.file_name);
        ddd[0]='4';
        char extension[3];
        sprintf(extension,"%c%c%c",de.file_name[strlen(de.file_name)-3],de.file_name[strlen(de.file_name)-2],de.file_name[strlen(de.file_name)-1]);
        if (strcmp_nocase(extension,"imy")==0)
        {
          ddd[strlen(ddd)-4]=0;
          if (GetFileStats(ddd, &stat, &err))
            {
              ddd[0]='0';
              sprintf(ddd,"%s.imy",ddd);
              unlink(ddd,&err);
            }
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}

int CreateMediaLibrary(char *foldeer)
{
  DIR_ENTRY de;
  unsigned int err;
  int f;
  char path[128],ddd[320];
  sprintf(path,"%s%c",foldeer,'\\');
  strcpy(nname,path);
  strcat(nname,"*");
  if (FindFirstFile(&de,nname,&err))
  {
    do
    {
      if (!IsFile(de.file_name))
      {
        sprintf(ddd,"%s\\%s",de.folder_name,de.file_name);
        ddd[0]='0';
        mkdir(ddd,&err);
        ddd[0]='4';
        CreateMediaLibrary(ddd);
      }
      else
      {
      char extension[3];
      sprintf(extension,"%c%c%c",de.file_name[strlen(de.file_name)-3],de.file_name[strlen(de.file_name)-2],de.file_name[strlen(de.file_name)-1]);
      if ((strcmp_nocase(extension,format_1)==0)||(strcmp_nocase(extension,format_2)==0)||(strcmp_nocase(extension,format_3)==0)||(strcmp_nocase(extension,format_4)==0))
        {
          sprintf(ddd,"%s\\%s.imy",de.folder_name,de.file_name);
          ddd[0]='0';
          f=fopen(ddd, A_WriteOnly+A_Create, P_WRITE, & err );
          fclose(f,&err);
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return(0);
}
