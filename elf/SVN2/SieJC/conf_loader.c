#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "color.h"

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
  unsigned int rlen, end;

  extern const CFG_HDR cfghdr_CONNECT_LEVEL; //first var in CONFIG
  cfg=(void*)&cfghdr_CONNECT_LEVEL;

  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    rlen=fread(f,buf,len,&ul);
    end=lseek(f,0,S_END,&ul,&ul);
    fclose(f,&ul);
    if (rlen!=end || rlen!=len)  goto L_SAVENEWCFG;
    memcpy(cfg,buf,len);
    result=1;
  }
  else
  {
  L_SAVENEWCFG:
    result=SaveConfigData(fname);
  }
  mfree(buf);
  if (result>0)
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
  if(LoadConfigData(fname)<=0)
#endif
  {
    if (LoadConfigData("4:\\ZBin\\etc\\SieJC.bcfg")<=0)
    {
      LoadConfigData("0:\\ZBin\\etc\\SieJC.bcfg");
    }
  }
#ifdef NEWSGOLD
  else LoadConfigData(fname);
#endif  
}

#ifdef ICONBAR
#pragma segment="CONFIG_IB_C"
int SaveIconSetData(const char * fname)   // result 0 - конфига не создан, 1 - cоздан
{
  int f;
  unsigned int ul;
  int result=0;
  unsigned int wlen;
  unsigned int len=(char *)__segment_end("CONFIG_IB_C")-(char *)__segment_begin("CONFIG_IB_C");

  if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&ul))!=-1)
  {
    wlen=fwrite(f,__segment_begin("CONFIG_IB_C"),len,&ul);
    fclose(f,&ul);
    if (wlen==len) result=1;
  }
  return(result);
}
#pragma segment="CONFIG_IB_C"
int LoadIconSetData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;
  unsigned int rlen, end;

  extern const CFG_HDR cfghdr_IBI; //first var in CONFIG
  cfg=(void*)&cfghdr_IBI;

  unsigned int len=(int)__segment_end("CONFIG_IB_C")-(int)__segment_begin("CONFIG_IB_C");

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
    result=SaveIconSetData(fname);
  }
  mfree(buf);
  return(result);
}

void InitIconSet()
{
  if (LoadIconSetData("4:\\ZBin\\etc\\SieJCIconSet.bcfg")<=0)
  {
    LoadIconSetData("0:\\ZBin\\etc\\SieJCIconSet.bcfg");
  }  
}
#endif

#pragma segment="CONFIG_COLOR_C"
int SaveColorSetData(const char * fname)   // result 0 - конфиг не создан, 1 - cоздан
{
  int f;
  unsigned int ul;
  int result=0;
  unsigned int wlen;
  unsigned int len=(char *)__segment_end("CONFIG_COLOR_C")-(char *)__segment_begin("CONFIG_COLOR_C");

  if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&ul))!=-1)
  {
    wlen=fwrite(f,__segment_begin("CONFIG_COLOR_C"),len,&ul);
    fclose(f,&ul);
    if (wlen==len) result=1;
  }
  return(result);
}
#pragma segment="CONFIG_COLOR_C"
int LoadColorSetData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=-1;
  void *cfg;
  unsigned int rlen, end;

  extern const CFG_HDR cfgcolor1; //first var in CONFIG
  cfg=(void*)&cfgcolor1;
  unsigned int len=(int)__segment_end("CONFIG_COLOR_C")-(int)__segment_begin("CONFIG_COLOR_C");

  if (!(buf=malloc(len))) return result;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    rlen=fread(f,buf,len,&ul);
    end=lseek(f,0,S_END,&ul,&ul);
    fclose(f,&ul);
    if (rlen!=end || rlen!=len)
    {
      ShowMSG(1,(int)"Error color file.");
      result = 0;
    } else result=1;
    memcpy(cfg,buf,len);
  }
  mfree(buf);
  return(result);
}
// EOL, EOF
