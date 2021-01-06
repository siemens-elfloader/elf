#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

const char *successed_config_filename="";

#pragma segment="CONFIG_C"
int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;
  unsigned int rlen;

  cfg=(char *)__segment_begin("CONFIG_C");
  unsigned int len=(char *)__segment_end("CONFIG_C")-(char *)__segment_begin("CONFIG_C");

  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    rlen=fread(f,buf,len,&ul);
    if ((rlen==lseek(f,0,S_END,&ul,&ul)) && rlen==len)
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
  if (result>=0) successed_config_filename=fname;
  return(result);
}

void InitConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\MegaDial2.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\MegaDial2.bcfg");
  }
}
