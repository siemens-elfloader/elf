#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

const char *successed_config_filename="";
char *s_ab_main="0:\\System\\apo\\addr\\main";
#ifdef NEWSGOLD
char *s_ab_entry="0:\\System\\apo\\addr\\data\\%02d\\%02d\\%02d";
#else
char *s_ab_entry="0:\\System\\apo\\addr\\%02x\\%02x";
#endif

#pragma segment="CONFIG_C"
static int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;
  unsigned int rlen, end;

  cfg=(char *)__segment_begin("CONFIG_C");
  unsigned int len=(char *)__segment_end("CONFIG_C")-(char *)__segment_begin("CONFIG_C");

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

unsigned int GetCC_NCfromIMSI(char *imsi)
{
  unsigned int cc, cc2, nc;
  cc=(*(imsi+1)>>4)<<8;
  cc2=*(imsi+2);
  cc2=((cc2&0x0F)<<4)|(cc2>>4);
  cc|=cc2;
  nc=*(imsi+3);
  nc=((nc&0x0F)<<4)|(nc>>4);
  return ((cc<<16)|nc);
}

// Инициализация конфигурации
// Надо вызвать в начале работы для загрузки конфигурации
// Поиск конфиг-файла согласно стандарту
static char config_name[128];


void InitConfig()
{
  extern char cur_imsi[];
  unsigned int cc;
  unsigned int nc;
  char *imsi=RAM_IMSI();
  cc=GetCC_NCfromIMSI(imsi);
  nc=cc&0xFFFF;
  cc>>=16;
  if (cc==0xFFF && nc==0xFF) return; // Если нет сети то ждем пока появится
//  sprintf(config_name,"4:\\ZBin\\etc\\CallCenter_%03X-%02X.bcfg",cc,nc);
  sprintf(config_name,"4:\\ZBin\\etc\\CallCenter%02X-%02X%02X%02X%02X-%03X.bcfg",nc,imsi[5],imsi[6],imsi[7],imsi[8],cc);
  //ShowMSG(1,(int)config_name);
  if(LoadConfigData(config_name)<0)
  {
    config_name[0] = '0';
    LoadConfigData(config_name);
  }

  extern const int AB_DISK;
  if (AB_DISK==1)
   s_ab_entry[0]=s_ab_main[0]='2';
  else
   s_ab_entry[0]=s_ab_main[0]='0';
}
