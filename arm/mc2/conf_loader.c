#include "..\inc\cfg_items.h"
#include "inc\conf_loader.h"
#include "inc\mc.h"
#include "inc\config.h"
#include "inc\gui.h"

char successed_config_filename[MAX_PATH] = "";

#pragma segment="CONFIG_C"
int SaveConfigData(const char *fname)
{
	int f;
	unsigned int ul;
	int result = -1;
	unsigned int len =(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

	if ((f = fopen(fname, A_ReadWrite+A_Create+A_Truncate+A_BIN, P_READ+P_WRITE, &ul)) != -1)
	{
		if (fwrite(f, __segment_begin("CONFIG_C"), len, &ul) == len) result = 0;
		fclose(f, &ul);
	}

	return(result);
}

#pragma segment="CONFIG_C"
int LoadConfigData(const char *fname)
{
	int f;
	unsigned int ul;
	char *buf;
	int result=0;
	void *cfg;
	unsigned int rlen, end;

	cfg=(char *)__segment_begin("CONFIG_C");
	unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");

	if (!(buf=malloc(len))) return -1;
	if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		rlen=fread(f,buf,len,&ul);
		end=lseek(f,0,S_END,&ul,&ul);
		fclose(f,&ul);
		if (rlen!=end || rlen!=len) goto L_SAVENEWCFG;
		memcpy(cfg,buf,len);
	}
	else
	{
L_SAVENEWCFG:
		// Прописываем дефолтный путь для mcconfig.cfg в папку mc
		strcpy((char*)CONFIG_MCCONFIG_PATH, mcpath);

		// Сохраняем
		result = SaveConfigData(fname);
	}
	mfree(buf);
	return(result);
}

void InitTempDir()
{
	if (!CONFIG_TEMP_PATH[0])
		strcpy((char*)CONFIG_TEMP_PATH, DEFAULT_DISK":\\Temp");

	int pathLen = strlen(CONFIG_TEMP_PATH);
	if (pathLen > 0 && ((char*)CONFIG_TEMP_PATH)[pathLen - 1] == '\\')
		((char*)CONFIG_TEMP_PATH)[pathLen - 1] = 0;

	mktree((char*)CONFIG_TEMP_PATH);
}

void InitConfig()
{
	sprintf(successed_config_filename, _s_s, etc_path, cfg_file);
	// Сначала пробуем взять информацию с того диска с которого запускаемся
	successed_config_filename[0] = mcpath[0];
	if (LoadConfigData(successed_config_filename) < 0)
	{
		// Пробуем с 4:
		successed_config_filename[0] = '4';
		if (mcpath[0] == '4' || LoadConfigData(successed_config_filename) < 0)
		{
			// Пробуем с 0:
			successed_config_filename[0] = '0';
			LoadConfigData(successed_config_filename);
		}
	}

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
	show_hiddrv = CONFIG_SHOW_SYSDRV;
}
