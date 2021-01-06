#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

char * successed_config_filename = NULL;

#pragma segment="CONFIG_C"

int SaveConfigData(const char * fname)   // result 0 - конфига не создан, 1 - cоздан
{
  int f;
  unsigned int ul;
  int result=0;
  unsigned int wlen;
  unsigned int len=(char *)__segment_end("CONFIG_C")-(char *)__segment_begin("CONFIG_C");

  if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&ul))!=-1)
  {
    wlen=fwrite(f,__segment_begin("CONFIG_C"),len,&ul);
    fclose(f,&ul);
    if (wlen==len) result=1;
  }
  return(result);
}

int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  extern const CFG_HDR cfghdr_CONNECT_LEVEL; //first var in CONFIG
  cfg=(void*)&cfghdr_CONNECT_LEVEL;

  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    if (fread(f,buf,len,&ul)==len)
    {
      memcpy(cfg,buf,len);
      fclose(f,&ul);
    }
    else
    {
      fclose(f,&ul);
      goto L_SAVENEWCFG;
    }
  }
  else
  {
  L_SAVENEWCFG:
    if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
    {
      if (fwrite(f,cfg,len,&ul)!=len) result=-1;
      fclose(f,&ul);
    }
    else
      result=-1;
  }
  mfree(buf);
  if (result >= 0)
  {
    if (successed_config_filename)
      mfree(successed_config_filename);
    successed_config_filename = malloc(strlen(fname) + 1);
    strcpy(successed_config_filename, fname);
  }
  return(result);
}

void InitConfig(char* fname)
{
#ifdef NEWSGOLD
  if(!fname)
#else
  if(LoadConfigData(fname)<0)
#endif
  {
    if (LoadConfigData("4:\\ZBin\\etc\\SieJC.bcfg")<0)
    {
      LoadConfigData("0:\\ZBin\\etc\\SieJC.bcfg");
    }
  }
  #ifdef NEWSGOLD
  else LoadConfigData(fname);

#endif
  
}
