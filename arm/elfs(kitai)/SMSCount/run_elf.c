#include "..\inc\swilib.h"

#pragma swi_number=0x0A4
__swi	__arm	WSHDR * AllocWS_2 (int len);

#pragma swi_number=0x0A5
__swi	__arm	void  FreeWS_2 (WSHDR *wshdr);

#pragma swi_number=0x0A0
__swi	__arm	int wsprintf_2 (WSHDR *,const char *format,...);

void start_elf()
{
	char fpath[]="0:\\ZBin\\utilities\\SMSCountReader.elf";
	FSTATS fstats;
	unsigned int err;
	if (GetFileStats(fpath,&fstats,&err)==-1)
	{
		fpath[0]='4';
		if (GetFileStats(fpath,&fstats,&err)==-1)
		{
	  		MsgBoxError(1, (int)"Can't find SMSCountReader.elf");
	  		return;
		}
	}
	WSHDR *ws=AllocWS_2(128);
	wsprintf_2(ws,"%s",fpath);
	ExecuteFile(ws,0,0);
	FreeWS_2(ws);
}

#pragma diag_suppress=Pe177
__root static const int HookShow @ "HookShow" = (int)start_elf;
#pragma diag_default=Pe177


