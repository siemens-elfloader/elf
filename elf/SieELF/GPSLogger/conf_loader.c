#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

const char *successed_config_filename="";

#pragma inline
int tolower(int C)
{
  if ((C>='A' && C<='Z')) C-='A'-'a';
  return(C);
}


// ������ strcmp, �� ��� ���������������� � ��������
int stricmp(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=tolower(*s++);
    ds=tolower(*d++);
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}

#pragma segment="CONFIG_C"
int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  extern const CFG_HDR cfghdr0; //first var in CONFIG
  cfg=(void*)&cfghdr0;

  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,0,&ul))!=-1)
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

void InitConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\GPSLogger.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\GPSLogger.bcfg");
  }
}
