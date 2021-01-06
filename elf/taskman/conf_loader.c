#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

//pragma segment="CONFIG_C"

__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"CSM list file",3,127};
__root const char csmlist_fname[128]="0:\\ZBin\\etc\\CSMlist.txt";

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Menu file",3,127};
__root const char menu_fname[128]="0:\\ZBin\\xtaskm\\menu.mnu";

__root const CFG_HDR cfghdr2={CFG_CBOX,"Block on keylock",0,2};
__root const int BLOCK_KEYLOCK=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr3={CFG_CBOX,"Enable hello message",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"No","Yes"};

__root const CFG_HDR cfghdr4={CFG_STR_WIN1251,"Hot key",1,10};
__root const char HOT_KEY[10]="2A+23";

__root const CFG_HDR cfghdr5={CFG_STR_WIN1251,"Bookmark 0 name",1,31};
__root const char BM1NAME[32]="";
__root const CFG_HDR cfghdr6={CFG_STR_UTF8,"Bookmark 0 file",3,127};
__root const char BM1FILE[128]="";

__root const CFG_HDR cfghdr7={CFG_STR_WIN1251,"Bookmark 1 name",1,31};
__root const char BM2NAME[32]="";
__root const CFG_HDR cfghdr8={CFG_STR_UTF8,"Bookmark 1 file",3,127};
__root const char BM2FILE[128]="";

__root const CFG_HDR cfghdr9={CFG_STR_WIN1251,"Bookmark 2 name",1,31};
__root const char BM3NAME[32]="";
__root const CFG_HDR cfghdr10={CFG_STR_UTF8,"Bookmark 2 file",3,127};
__root const char BM3FILE[128]="";

__root const CFG_HDR cfghdr11={CFG_STR_WIN1251,"Bookmark 3 name",1,31};
__root const char BM4NAME[32]="";
__root const CFG_HDR cfghdr12={CFG_STR_UTF8,"Bookmark 3 file",3,127};
__root const char BM4FILE[128]="";

__root const CFG_HDR cfghdr13={CFG_STR_WIN1251,"Bookmark 4 name",1,31};
__root const char BM5NAME[32]="";
__root const CFG_HDR cfghdr14={CFG_STR_UTF8,"Bookmark 4 file",3,127};
__root const char BM5FILE[128]="";

__root const CFG_HDR cfghdr15={CFG_STR_WIN1251,"Bookmark 5 name",1,31};
__root const char BM6NAME[32]="";
__root const CFG_HDR cfghdr16={CFG_STR_UTF8,"Bookmark 5 file",3,127};
__root const char BM6FILE[128]="";

__root const CFG_HDR cfghdr17={CFG_STR_WIN1251,"Bookmark 6 name",1,31};
__root const char BM7NAME[32]="";
__root const CFG_HDR cfghdr18={CFG_STR_UTF8,"Bookmark 6 file",3,127};
__root const char BM7FILE[128]="";

__root const CFG_HDR cfghdr19={CFG_STR_WIN1251,"Bookmark 7 name",1,31};
__root const char BM8NAME[32]="";
__root const CFG_HDR cfghdr20={CFG_STR_UTF8,"Bookmark 7 file",3,127};
__root const char BM8FILE[128]="";

__root const CFG_HDR cfghdr21={CFG_STR_WIN1251,"Bookmark 8 name",1,31};
__root const char BM9NAME[32]="";
__root const CFG_HDR cfghdr22={CFG_STR_UTF8,"Bookmark 8 file",3,127};
__root const char BM9FILE[128]="";

__root const CFG_HDR cfghdr23={CFG_STR_WIN1251,"Bookmark 9 name",1,31};
__root const char BMANAME[32]="";
__root const CFG_HDR cfghdr24={CFG_STR_UTF8,"Bookmark 9 file",3,127};
__root const char BMAFILE[128]="";

__root const int endd;


int LoadConfigData(const char *fname, int wr)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;

  cfg=(void*)&cfghdr0;
  
  unsigned int len=0xc20;
  if (!(buf=malloc(len))) return -1;
  if (!wr) {
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
   } else goto L_SAVENEWCFG;
  } else {
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
  return(result);
}

void InitConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\XTaskM.bcfg",0)<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\XTaskM.bcfg",0);
  }
}

void SaveConfig()
{
  if (LoadConfigData("4:\\ZBin\\etc\\XTaskM.bcfg",1)<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\XTaskM.bcfg",1);
  }
}
