#include "..\inc\swilib.h"

#pragma swi_number=0x0A4
__swi	__arm	WSHDR * AllocWS_2 (int len);

#pragma swi_number=0x0A5
__swi	__arm	void  FreeWS_2 (WSHDR *wshdr);

#pragma swi_number=0x0A0
__swi	__arm	int wsprintf_2 (WSHDR *,const char *format,...);

void main()
{
  char path[]="4:\\ZBin\\etc\\start_elf.bcfg";
  unsigned int err;
  int f;
  
  if((f=fopen(path,A_ReadOnly+A_BIN,P_READ,&err))==-1)
  {
    MsgBoxError(1,(int)"can't open config file!");
    return;
  }
  char* buf=malloc(64);
  lseek(f,44,0,&err,&err);
  fread(f,buf,64,&err);
  fclose(f,&err);  
  WSHDR *ws=AllocWS_2(128);
  wsprintf_2(ws,"%t",buf);
  ExecuteFile(ws,0,0);
  FreeWS_2(ws);
  mfree(buf);
}

#pragma diag_suppress=Pe177
__root static const int PATCH_START_ELF @ "PATCH_START_ELF" = (int)main;
#pragma diag_default=Pe177

