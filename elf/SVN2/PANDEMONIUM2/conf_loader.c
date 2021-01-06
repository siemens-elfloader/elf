#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

char *successed_config_filename="";
#pragma segment="CONFIG_C"

extern unsigned int reboot_address;

int LoadConfigData(char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  extern const CFG_HDR cfghdr0; //first var in CONFIG
  cfg=(void*)&cfghdr0;

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

/*static int _hc(char c)
{
  if(c>='0'&&c<='9')
   return c-'0';
  else if(c>='A'&&c<='F')
   return c-'A'+0xA;
  if(c>='a'&&c<='f')
   return c-'a'+0xA;
  return 0;
};

unsigned int Hex2Int(char *s)
{
if(s==0) return 0;
unsigned int a=0;
int i=0;
while(s[i]!=0)
  {
  a=(a<<4)+_hc(s[i++]);
  };
return a;
};*/

void InitConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\PANDEMONUIM.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\PANDEMONUIM.bcfg");
  }
}

