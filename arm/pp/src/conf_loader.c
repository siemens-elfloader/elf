/*
* Ping-Pong 2009 - 2010
* keys
* (c) Danil_e71
*/

#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
//Тут разбираться не надо
const char *successed_config_filename="";

#pragma segment="CONFIG_C"
int LoadConfigData(const char *fname)
{

  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;
  unsigned int rlen, end;

  extern const CFG_HDR cfghdr1;
  cfg=(void*)&cfghdr1;

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
  if (LoadConfigData("0:\\ZBin\\etc\\Ping-PongLE.bcfg")<0)
  {
    LoadConfigData("4:\\ZBin\\etc\\Ping-PongLE.bcfg");
  }
}
