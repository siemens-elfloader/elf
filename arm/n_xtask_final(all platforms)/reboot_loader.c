#include "..\inc\swilib.h"

void undo_file()
{
  volatile int hFile2;
  unsigned int io_error2 = 0;
  unsigned int ul2;
  FSTATS stat2;
  GetFileStats("0:\\system\\data.bin",&stat2,&ul2);
  hFile2 = fopen("0:\\system\\data.bin",A_ReadWrite+A_Create+A_Truncate+ A_BIN,P_READ+P_WRITE, &io_error2);
  if(hFile2!=-1)
  {
    fwrite(hFile2, "00", 2, &io_error2);
    fclose(hFile2, &io_error2);
  }
}

int zet;
char soft_list[2000];
extern char soft_list_path[128];

void preload_soft_list()
{
    int f;
    int fsize;
    FSTATS stat;
    unsigned int ul;
    GetFileStats(soft_list_path,&stat,&ul);
    if(stat.size>0)
    {
      f=fopen(soft_list_path,A_ReadOnly+A_BIN,P_READ,&ul);
      fsize=stat.size;
      char *p=malloc(fsize);
      p[fread(f,p,fsize,&ul)];
      fclose(f,&ul);
      strcpy(soft_list, p);
      mfree(p);
    }
}

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

void Searchit(char *filename)
{
  char buffer[128];
  //ws_2str(ramed, buffer, 64);
  strcpy(buffer, filename);
  if(strstr(buffer, "NATICQ")>0) strcpy(buffer, "NATICQ");
  if(strstr(buffer, "SieJC")>0) strcpy(buffer, "SieJC");
  if(strstr(buffer, "MC:")>0) strcpy(buffer, "MC");
  if(strstr(buffer, "BM:")>0) strcpy(buffer, "BM:");
  char p2[]="||";
  char *s,*s1,*s2;
  int len;
  if((s1=strstr(soft_list,buffer))>0)
  {
    s1+=strlen(buffer);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1-4;
      s=malloc(len+1);
      strncpy(s,s1+4,len);
      s[len]='\0';
      if(s1[2]=='F')
      {
      WSHDR *elfname=AllocWS(256);
      wsprintf(elfname, s);
      ExecuteFile(elfname,NULL,NULL);
      FreeWS(elfname);
      }
      else
        if(s1[2]=='E')
      {
        typedef void (*voidfunc)(); 
        unsigned int addr=strtoul( (char*)s, 0, 16 );
        voidfunc pp=(voidfunc)addr;
        SUBPROC((void*)pp);
      }
      mfree(s);
    }
  }
}

void load_reboot_list()
{
    preload_soft_list();
    int fu;
    int fsizeu;
    FSTATS statu;
    unsigned int ulu;
    GetFileStats("0:\\system\\data.bin",&statu,&ulu);
    if(statu.size>0)
    {
      fu=fopen("0:\\system\\data.bin",A_ReadOnly+A_BIN,P_READ,&ulu);
      fsizeu=statu.size;
      char *pu=malloc(fsizeu);
      pu[fread(fu,pu,fsizeu,&ulu)];
      fclose(fu,&ulu);
      zet=2;
      while(zet<fsizeu-2)
      {
        int tr=0;
        char *run1=malloc(128);
        while(pu[zet]!='|') {run1[tr]=pu[zet]; tr++; zet++;}
        run1[tr]='\0';
        Searchit(run1);
        mfree(run1);
        zet++;
      }
      mfree(pu);
    }
    undo_file();
}
