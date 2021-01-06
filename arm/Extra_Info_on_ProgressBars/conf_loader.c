#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"

const extern CFG_HDR cfghdr0;
#pragma segment="CONFIG_DATA_C"
__arm char* LoadConfigData (const char *fname)
{
  void *ff_cfg=(void *)&cfghdr0;
  unsigned int len=(char *)__segment_end("CONFIG_DATA_C")-(char *)__segment_begin("CONFIG_DATA_C");
  char* cfg = malloc(len+1);
  
  int f;
  unsigned int ul, rlen, end;
  
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    rlen=fread(f,cfg,len,&ul);
    end=lseek(f,0,S_END,&ul,&ul);
    fclose(f,&ul);
    if (rlen!=end || rlen!=len)  goto L_SAVENEWCFG;
  }
  else
  {
  L_SAVENEWCFG:
    memcpy(cfg,ff_cfg,len);
    if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
    {
      if (fwrite(f,cfg,len,&ul)!=len){
        mfree(cfg);
        cfg=0;
      }
      fclose(f,&ul);
    }
    else{
      mfree(cfg);
      cfg=0;
    }
  }
  return (cfg);
}
