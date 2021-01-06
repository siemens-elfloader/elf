#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

const char *successed_config_filename="";




#pragma segment="CONFIG_C"
int SaveConfigData(const char *fname)   // result 0 - конфига не создан, 1 - cоздан
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


#pragma segment="CONFIG_C"
int LoadConfigData(const char *fname)  // result 0 - конфига нет и не создан, 1 - нет и создан, 2 - есть
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  unsigned int rlen, end;


  unsigned int len=(char *)__segment_end("CONFIG_C")-(char *)__segment_begin("CONFIG_C");

  if ((buf=malloc(len)))
  {
    if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
    {
      rlen=fread(f,buf,len,&ul);
      end=lseek(f,0,S_END,&ul,&ul);
      fclose(f,&ul);
      if (rlen!=end || rlen!=len)  goto L_SAVENEWCFG;
      memcpy(__segment_begin("CONFIG_C"),buf,len);
      result=2;
    }
    else
    {
    L_SAVENEWCFG:
      result=SaveConfigData(fname);
    }
    mfree(buf);
  }
  if (result>0) successed_config_filename=fname;
  return(result);
}

int InitConfig() 
{
  int i;
  if (!(i=LoadConfigData("4:\\ZBin\\etc\\XTask.bcfg")))
  {
    i=LoadConfigData("0:\\ZBin\\etc\\XTask.bcfg");
  }
  return i;
}
