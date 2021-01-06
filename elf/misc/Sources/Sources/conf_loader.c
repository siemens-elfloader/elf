#include "..\inc\cfg_items.h"
#include "inc\conf_loader.h"
#include "inc\mc.h"
#include "inc\config.h"

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
	}
	else
	{
L_SAVENEWCFG:
		if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate+A_BIN,P_READ+P_WRITE,&ul))!=-1)
		{
			// Прописываем дефолтный путь для mcconfig.cfg в папку mc
			strcpy((char*)CONFIG_MCCONFIG_PATH, mcpath);

			if (fwrite(f,cfg,len,&ul)!=len) result=-1;
			fclose(f,&ul);
		}
		else
			result=-1;
	}
	mfree(buf);
	return(result);
}

void InitTempDir()
{
	if (!CONFIG_TEMP_PATH)
		strcpy((char*)CONFIG_TEMP_PATH, DEFAULT_DISK":\\Temp");

	int pathLen = strlen(CONFIG_TEMP_PATH);
	if (pathLen > 0 && ((char*)CONFIG_TEMP_PATH)[pathLen - 1] == '\\')
		((char*)CONFIG_TEMP_PATH)[pathLen - 1] = 0;

	mktree((char*)CONFIG_TEMP_PATH);
}

void InitConfig()
{
	char buf[MAX_PATH];
	sprintf(buf, _s_s, etc_path, cfg_file);
	LoadConfigData(buf);

	// Setup drives info
	Drives[DRV_IDX_Cache].enabled	= CONFIG_SHOW_SYSDRV;
	Drives[DRV_IDX_Config].enabled	= CONFIG_SHOW_SYSDRV;
	Drives[DRV_IDX_MMC].enabled		= CONFIG_SHOW_MMC;

	// Setup fonts
	NormalFont = CONFIG_USE_BOLD_FONT ? FONT_N : FONT_SMALL;
	BoldFont = CONFIG_USE_BOLD_FONT ? FONT_B : FONT_SMALL;

	// Init temp dir
	InitTempDir();
	
	// Setup hidden/system files visibility
	show_hidden = CONFIG_SHOW_HIDDEN;
	show_system = CONFIG_SHOW_SYSTEM;
}
