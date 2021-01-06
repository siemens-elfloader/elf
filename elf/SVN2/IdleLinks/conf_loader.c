#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"

// Загрузка основного конфига

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

  extern const CFG_HDR cfghdr0;
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
  if (LoadConfigData("4:\\ZBin\\etc\\IdleLinks.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\IdleLinks.bcfg");
  }
}

// Загрузка конфига с ярлычком

#pragma segment="CONFIG_LINK_C"
int SaveLink(const char * fname)   // result 0 - конфига не создан, 1 - cоздан
{
  int f;
  unsigned int ul;
  int result=0;
  unsigned int wlen;
  unsigned int len=(char *)__segment_end("CONFIG_LINK_C")-(char *)__segment_begin("CONFIG_LINK_C");

  if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&ul))!=-1)
  {
    wlen=fwrite(f,__segment_begin("CONFIG_LINK_C"),len,&ul);
    fclose(f,&ul);
    if (wlen==len) result=1;
  }
  return(result);
}
#pragma segment="CONFIG_LINK_C"
int LoadLink(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;
  unsigned int rlen, end;

  extern const CFG_HDR cfghdr_lnk0; //first var in CONFIG
  cfg=(void*)&cfghdr_lnk0;

  unsigned int len=(int)__segment_end("CONFIG_LINK_C")-(int)__segment_begin("CONFIG_LINK_C");

  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    rlen=fread(f,buf,len,&ul);
    end=lseek(f,0,S_END,&ul,&ul);
    fclose(f,&ul);
    if (rlen!=end || rlen!=len)  goto L_SAVENEWCFGIB;
    memcpy(cfg,buf,len);
    result=1;
  }
  else
  {
  L_SAVENEWCFGIB:
    result=SaveLink(fname);
  }
  mfree(buf);
  return(result);
}

void InitLink(const char *fname)
{
  LoadLink(fname);
}

