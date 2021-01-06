#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

const char *successed_config_filename="";

#pragma segment="CONFIG_C"
#ifdef ELKA
inline int SaveConfigDataSub(const char *fname)
{
  int f;
  unsigned int ul;


//  extern const CFG_HDR ch0; //first var in CONFIG
//  cfg=(void*)&ch0;

//  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");
  unsigned int len=(char *)__segment_end("CONFIG_C")-(char *)__segment_begin("CONFIG_C");

    if ((f=fopen(fname,A_WriteOnly+A_Create+A_BIN+A_Truncate,P_WRITE,&ul))!=-1)
    {
      if (fwrite(f,__segment_begin("CONFIG_C"),len,&ul)!=len)return -1;
      fclose(f,&ul);
    }
    else
      return -1;
  

  return 0;
}

void SaveConfig(void){

    SaveConfigDataSub(successed_config_filename);
}
#endif
int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  extern const CFG_HDR ch0; //first var in CONFIG
  cfg=(void*)&ch0;

  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if (!(buf=(char*)malloc(len))) return -1;
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
  if (result>=0) successed_config_filename=fname;
  return(result);
}

void InitConfig(void)
{
  if (LoadConfigData("4:\\ZBin\\etc\\SndDemon.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\SndDemon.bcfg");
  }
}
