#include "..\inc\swilib.h"

int mode=0;//защита от копий=)
extern void CreateNSD();
  char IsEnabledIconBar()
{
//#ifdef EL71
 // return *(char*)( (*(int*)0xA8E94D88) + 0x18 );
//#else //E71
    return *(char*)( (*(int*)0xA8E9509C) + 0x18 );

//#endif
};
int main()
{
  CreateNSD();
  return 0;
}
/* 1 create A0CD01B0(39,2D,2,8055) [LR=A07928C8]*/

//Obs_MM_SetInput_ProxyURI(obs,1);
//purpose 0x16

//* 23 A0D188D8(AC952294,AD217F14,53,2) [LR=A07969A8]


