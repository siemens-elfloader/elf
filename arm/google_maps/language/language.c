#include "..\inc\swilib.h"
#include "../include.h"
#include "language.h"
#include "../file_works.h"

char * lgpData[LGP_DATA_NUM];
int lgpLoaded;

void lgpInitLangPack(void)
{
  int hFile;
  unsigned int io_error = NULL;
  
  
  char  lang_file[256];
  sprintf(elf_path,fname);
  if(elf_path[strlen(elf_path)-1]!='\\')elf_path[strlen(elf_path)-1]='\\';
  sprintf(lang_file,"%s%s",elf_path,resource[LANG]);
  for (int i = 0; i < LGP_DATA_NUM; i ++)
    lgpData[i] = NULL;
  lgpLoaded = 0;
  
  char * buf;
  FSTATS fstat;
  
  if (GetFileStats(lang_file, &fstat, &io_error) != -1)
  {
    if((hFile = fopen(lang_file, A_ReadOnly + A_BIN, P_READ, &io_error))!=-1)
    {
      if (buf =(char *)malloc(fstat.size + 1))
      {
        buf[fread(hFile, buf, fstat.size, &io_error)] = NULL;
        fclose(hFile, &io_error);
        
        char line[128];
        int lineSize = NULL;
        int lp_id = NULL;
        int buf_pos = NULL;
        while(buf[buf_pos] && buf_pos < fstat.size && lp_id < LGP_DATA_NUM)
        {
          if (buf[buf_pos]=='\n' || buf[buf_pos]=='\r')
          {
            if (lineSize > 0)
            {
              lgpData[lp_id] = (char *)malloc(lineSize+1);
              memcpy(lgpData[lp_id], line, lineSize);
              lgpData[lp_id][lineSize] = NULL;
              lp_id ++;
              lineSize = NULL;
            }
          }
          else
            line[lineSize ++] = buf[buf_pos];
          buf_pos ++;
        }
        if (lineSize > 0 && lp_id < LGP_DATA_NUM) // eof
        {
          lgpData[lp_id] = (char *)malloc(lineSize+1);
          memcpy(lgpData[lp_id], line, lineSize);
          lgpData[lp_id][lineSize] = NULL;
          lp_id ++;
          lineSize = NULL;
        }
        mfree(buf);
        lgpLoaded = 1;
        
        // old langpack
        if (strlen(lgpData[LGP_LangCode]) > 2)
        {
          mfree(lgpData[LGP_LangCode]);
          lgpData[LGP_LangCode] = (char *)malloc(3);
          strcpy(lgpData[LGP_LangCode],"ru");
        }
        for (int i = 0; i < LGP_DATA_NUM; i ++)
        {
          if (!lgpData[i])
          {
            lgpData[i] = (char *)malloc(32);
            strcpy(lgpData[i], "Error! Update language.lng!");
          }
        }
        return;
      }
      fclose(hFile, &io_error);
    }
  }

  lgpData[LGP_LoadingMap]="Loading map";
  lgpData[LGP_PressAnyKey]="press any key";
  lgpData[LGP_Traffic]="traffic";
  lgpData[LGP_State]="state";
  lgpData[LGP_LoadingCache]="loading cache";
  
  lgpData[LGP_LangCode]=              "en";
}

void lgpFreeLangPack(void)
{
  if (!lgpLoaded) return;
  for (int i = 0; i < LGP_DATA_NUM; i ++)
  {
    if (lgpData[i])
      mfree(lgpData[i]);
  }
}
