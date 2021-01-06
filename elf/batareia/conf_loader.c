#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

const char *successed_config_filename="";

#pragma segment="CONFIG_C"
int SaveConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  int result=-1;
  unsigned int wlen;
  unsigned int len=(char *)__segment_end("CONFIG_C")-(char *)__segment_begin("CONFIG_C");

  if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&ul))!=-1)
  {
    wlen=fwrite(f,__segment_begin("CONFIG_C"),len,&ul);
    fclose(f,&ul);
    if (wlen==len) result=0;
  }
  return(result);
}


#pragma segment="CONFIG_C"
int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;
  unsigned int rlen, end;

  extern const CFG_HDR cfghdr0; //first var in CONFIG
  cfg=(void*)&cfghdr0;

  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    rlen=fread(f,buf,len,&ul);
    end=lseek(f,0,S_END,&ul,&ul);
    fclose(f,&ul);
    if (rlen!=end || rlen!=len)  goto L_SAVENEWCFG;
    memcpy(cfg,buf,len);
  }
  else
  {
  L_SAVENEWCFG:
    result=SaveConfigData(fname);
  }
  mfree(buf);
  if (result>=0) successed_config_filename=fname;
  return(result);
}

void InitConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\batareia.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\batareia.bcfg");
  }
}
