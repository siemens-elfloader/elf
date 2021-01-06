
#include <swilib.h>
#include <unistd.h>
#include <fcntl.h>
#include <cfg_items.h>
#include <conf_loader.h>

/*
    Переделанный загрузчик конфига под gcc.
    (c) Z.Vova
*/


char *successed_config_filename="";


//__attribute__((section("CONFIG_C")))
int LoadConfigData(const char *fname, CFG_HDR *cfghdr0, int * __config_begin, int * __config_end)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  //extern const int __config_end, __config_begin;
  cfg=(void*)cfghdr0;
  volatile unsigned int _segb = (volatile unsigned int)__config_begin;
  volatile unsigned int _sege = (volatile unsigned int)__config_end;


  unsigned int len = (_sege - _segb)-4;
  if (!(buf=malloc(len))) return -1;
  if ((f=open(fname, O_RDONLY))!=-1)
  {
    if (read(f,buf,len) == (int)len)
    {
      memcpy(cfg,buf,len);
      close(f);
    }
    else
    {
      close(f);
      goto L_SAVENEWCFG;
    }
  }
  else
  {
  L_SAVENEWCFG:
    if ((f=open(fname, O_RDWR | O_CREAT | O_TRUNC))!=-1)
    {
      if (write(f,cfg,len)!= (int)len) result=-1;
      close(f);
    }
    else
      result=-1;
  }

  free(buf);
  if (result>=0) successed_config_filename = (char*)fname;
  return(result);
}


void InitConfig()
{
    __CONFIG_EXTERN(0, cfghdr0);    // нулевой конфиг и первый его элемент cfghdr0
    if(LoadConfigData("4:\\ZBin\\etc\\RadioSi.bcfg", __CONFIG(0, cfghdr0)) < 0)
        LoadConfigData("0:\\ZBin\\etc\\RadioSi.bcfg", __CONFIG(0, cfghdr0));
}


