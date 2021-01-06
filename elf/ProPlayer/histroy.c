#include "C:\ARM_ALL\inc\swilib.h"

extern unsigned int sndVolume;
extern char procfile[128];
extern char list_path[128];
extern const char History_folder[128];
extern int play_mode;
char his_file[128];

/*
00://vol
01://list_file
02://procfile
03://playmode
*/

int load_history(void) //return: 0:load fail, 1:load succ...
{
  int res;
  char *p;
  int his_size;
  unsigned int err;
  FSTATS fstats;
  strncpy(his_file,History_folder,strlen(History_folder));
  strcat(his_file,"\\History.cfg\0");
  int f=fopen(his_file,A_ReadOnly+A_BIN,P_READ,&err);
  if(f==-1)
    return 0;
  char *buf=malloc(512);
  int i=0;
  char ss[128];
  int c;
  his_size=fread(f,buf,512,&err);
  if (his_size>=0) buf[his_size]=0;
  p=buf;
  while(*p)
  {
    if((*p=='0')&&(*(p+1)=='0')&&(*(p+2)==':'))
    {
      p=p+3;
      sndVolume=*p-'0';
    }
    if((*p=='0')&&(*(p+1)=='1')&&(*(p+2)==':'))
    {
      p=p+3;
      while(*p!='\n')
      {
        c=*p;
        if(c>=0x1F)
        {
          if (i<(sizeof(ss)-1)) ss[i]=c;
          i++;
        }
        p++;
      }
      ss[i]='\0';
      i=0;
      if (GetFileStats(ss,&fstats,&err)!=-1)
        strcpy(list_path,ss);
    }
    if((*p=='0')&&(*(p+1)=='2')&&(*(p+2)==':'))
    {
      p=p+3;
      while(*p!='\n')
      {
        c=*p;
        if(c>=0x1F)
        {
          if (i<(sizeof(ss)-1)) ss[i]=c;
          i++;
        }
        p++;
      }
      ss[i]='\0';
      i=0;
      if (GetFileStats(ss,&fstats,&err)!=-1)
      {
        strcpy(procfile,ss);
        res=1;
      }
      else res=0;
    }
    if((*p=='0')&&(*(p+1)=='3')&&(*(p+2)==':'))
    {
      p=p+3;
      play_mode=*p-'0';
    }
    p++;
  }
  fclose(f,&err);
  mfree(buf);
  return res;
}
  
void save_his(void)
{
  unsigned int err;
  FSTATS fstats;
  if (GetFileStats(his_file,&fstats,&err)!=-1)
  {
    unlink(his_file, &err);
  }
  int f=fopen(his_file,A_WriteOnly+A_Create,P_WRITE+P_READ,&err);
  char *buf=malloc(512);
  sprintf(buf,"00:%d\n01:%s\n02:%s\n03:%d\n\0",sndVolume,list_path,procfile,play_mode);
  fwrite(f, buf, strlen(buf), &err);
  fclose(f,&err);
  mfree(buf);
}



