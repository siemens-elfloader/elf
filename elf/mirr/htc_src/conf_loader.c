#include "swilib.h"
#define CFG_UINT 1
#define CFG_STR_UTF8 2
#define CFG_INT 3
#define CFG_STR_WIN1251 4
#define CFG_CBOX 5
#define CFG_STR_PASS 6
#define CFG_COORDINATES 7
#define CFG_COLOR 8
#define CFG_LEVEL 9
#define CFG_UTF8_STRING 10
#define CFG_CHECKBOX 11
#define CFG_TIME 12   
#define CFG_DATE 13  
#define CFG_RECT 14  
typedef struct
{
  int type;
  char name[32];
  unsigned int min;
  unsigned int max;
}CFG_HDR;
typedef struct
{
  char cbox_text[32];
}CFG_CBOX_ITEM;
void InitConfig();
extern int DISK_d;
const char *successed_config_filename="";
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

void InitConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\MD_TouchFLO.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\MD_TouchFLO.bcfg");
    DISK_d = 0;
  }
  else DISK_d = 4;





}
