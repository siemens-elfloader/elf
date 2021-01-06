#include "..\inc\swilib.h"

int get_cfg(int num)
{
    switch(num)
    {
      case 0: return 44;
      case 1: return 48;
      case 2: return 96;
      case 3: return 100;
      case 4: return 148;
      case 5: return 152;
      case 6: return 204;
      default: return 0;
    }
}

int getoldpos(int num)
{
    switch(num)
    {
      case 0: return 2;// net_icons x
      case 1: return 3;// net_icons y
      case 2: return 0x63;// acc_icons x
      case 3: return 2;// acc_icons y
      case 4: return 0x21;// iconbar x
      case 5: return 2;// iconbar y
      case 6: return 0xA1;// timedate y
      default: return 0;
    }
}

int get_icons(int num)
{
  unsigned int err;
  int f;
  char path[]="0:\\ZBin\\etc\\mpos.bcfg";  
  if((f=fopen(path,A_ReadOnly+A_BIN,P_READ,&err))==-1)
  {
    return getoldpos(num);
  }
  char* buf=malloc(211);
  fread(f,buf,210,&err);
  fclose(f,&err);
  mfree(buf);
  return buf[get_cfg(num)];
}
