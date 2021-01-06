#include "..\inc\swilib.h"


typedef void P_PGET_PATH(void *unk, int index, WSHDR *wsp);

#ifdef	ELKA
#define	P_MODE	__arm //奇怪,...E71使用THUMB模式调用一些SWILIB函数会死机!!!

P_MODE void doFolderIconChange(void *unk, int *icon, int index, char *pathbuf) @ "OWM_FOLDER_ICON_BODY"
{

#ifdef E71Csw41
#define	FUNC1_adr 0xA06B15D4
#endif

P_PGET_PATH  *const PGET_PATH=(P_PGET_PATH*)(FUNC1_adr);

	unsigned int err;
	FSTATS statBuffer;
	WSHDR *wsfolder;
	if(!(*icon)) //0,一般为复制,移动选择列表的状况
		return;
	wsfolder=AllocWS(128);
	PGET_PATH(unk, index, wsfolder);
	ws_2str(wsfolder, pathbuf, 128);
	if(strlen(pathbuf)<=3)
		goto back;
	strcat(pathbuf, "\\icon.png");
	if(GetFileStats(pathbuf, &statBuffer, &err)!=-1)
	{
		*icon=(int)pathbuf;
	}
back:
	FreeWS(wsfolder);
}

#endif

#ifdef	NEWSGOLD
#define	P_MODE	__thumb


P_MODE void doFolderIconChange(void *unk, int *icon, int index, char *pathbuf) @ "OWM_FOLDER_ICON_BODY"
{
#pragma swi_number=0xA4
__swi	__arm	WSHDR * AllocWS_2 (int len);
#pragma swi_number=0xA5
__swi	__arm	void  FreeWS_2 (WSHDR *wshdr);

#ifdef S68Csw51
#define	FUNC1_adr 0xA03081BC+1
#endif

P_PGET_PATH  *const PGET_PATH=(P_PGET_PATH*)(FUNC1_adr);

	unsigned int err;
	FSTATS statBuffer;
	WSHDR *wsfolder;
	if(!(*icon)) //0,一般为复制,移动选择列表的状况
		return;
	wsfolder=AllocWS_2(128);
	PGET_PATH(unk, index, wsfolder);
	ws_2str(wsfolder, pathbuf, 128);
	if(strlen(pathbuf)<=3)
		goto back;
	strcat(pathbuf, "\\icon.png");
	if(GetFileStats(pathbuf, &statBuffer, &err)!=-1)
	{
		*icon=(int)pathbuf;
	}
back:
	FreeWS_2(wsfolder);
}


#endif


