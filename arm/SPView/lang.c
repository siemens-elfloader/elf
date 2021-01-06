#include <swilib.h>
#include "lang.h"

char *lang[LGP_TOTAL];
int lang_loaded;

int InitLangpack()
{
  extern char NSTOPWATCH_PATH[128];
  char fname[128];
  sprintf(fname, "%slang.txt", NSTOPWATCH_PATH);
  FSTATS fs;
  unsigned int err;
  if(GetFileStats(fname, &fs, &err)==-1) return -1;//если lang не найден
  int fp=fopen(fname, A_ReadOnly + A_BIN, P_READ, &err);
  if(fp==-1) return -1;                            //невозможно открыть ленг
  char *buf=malloc(fs.size+1);
  fread(fp, buf, fs.size, &err);
  fclose(fp, &err);
  char temp[128];
  int line_size=0;
  int id=0;
  int buf_pos=0;
  while(buf[buf_pos] && id<LGP_TOTAL && buf_pos<fs.size)//частично подсмотрел в баллетмини
  {
    if(buf[buf_pos]=='\n' || buf[buf_pos]=='\r')
    {
      lang[id]=malloc(line_size+1);
      memcpy(lang[id], temp, line_size);
      lang[id][line_size]=0;
      id++;
      line_size=0;
    }
    else
    {
      if(buf[buf_pos]=='|') buf[buf_pos]='\n';//символы новой строки нам тоже как-то надо получать
      temp[line_size++]=buf[buf_pos];
    }
    buf_pos++;
  }
  if(line_size > 0 && id < LGP_TOTAL)
  {
    lang[id]=malloc(line_size+1);
    memcpy(lang[id], temp, line_size);
    lang[id][line_size] = 0;
    id++;
    line_size = 0;
  }
  mfree(buf);
  lang_loaded=1;
  return 1;
}

void DefaultInitLang()
{
  const char *lgp[]={"Loading...\nPlease wait", "Stopwatch",
  "Can't open file!", "Nothing to save!", "Error occured while saving!", "Saving",
  "NstopWatch configuration updated", "Exit?"};
  for(int i=0; i<LGP_TOTAL; i++)
    lang[i]=(char*)lgp[i];
}

void FreeLangPack()
{
  if(lang_loaded)
    for(int i=0; i<LGP_TOTAL; i++)
      if(lang[i])
        mfree(lang[i]);
}
