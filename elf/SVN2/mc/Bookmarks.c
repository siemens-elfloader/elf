
#include "inc\mc.h"
#include "inc\mui.h"

const char mcbm_path[] = "Bookmarks";
const char mcbm_ext[] = "mcbm";

void SaveBM(char* name, char* path)
{
	if (pathbuf && name && path)
	{
		MCFilePath(mcbm_path);
		mktree(pathbuf);
		sprintf(pathbuf, _s_s, pathbuf, name);

		int f;
		if ((f=fopen(pathbuf,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err))!=-1)
		{
			fwrite(f,path,strlen(path)+1,&err);
			fclose(f,&err);
		}
	} 
}

void UseBM(char* filename)
{
	if (pathbuf)
	{
		int f;
		if ((f=fopen(pathbuf,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
		{
			if (fread(f, pathbuf, MAX_PATH, &err))
			{
				if (curtab >= MAX_TABS)
					curtab = back_tab < MAX_TABS ? back_tab : 0;

				if (isdir(pathbuf, &err))
					cd(curtab, pathbuf);
				else
					if (wsbuf)
					{
						str_2ws(wsbuf,pathbuf,MAX_PATH);
						ExecuteFile(wsbuf,0,0);
					}
			}
			fclose(f, &err);
		}
	}
}

void _AddBM(WSHDR *wsname)
{
	if (pathbuf && pathbuf2)
	{
		FILEINF *file = _CurFile();
		if (file)
		{
			char buf[MAX_PATH];
			ws_2str(wsname, buf, MAX_PATH);
			sprintf(pathbuf2, "%s.%s", buf, mcbm_ext);

			CurFullPathBM(buf, file->sname);
			SaveBM(pathbuf2, buf);
		} 
	} 
}

void DoBMAdd()
{
	FILEINF *file = _CurFile();
	if (file && wsbuf)
	{
		str_2ws(wsbuf,file->sname,MAX_PATH);
		TextInput(muitxt(ind_bm), muitxt(ind_name), 1, wsbuf, _AddBM);
	} 
}

void DoBMList()
{
	if (pathbuf)
	{
		MCFilePath(mcbm_path);
		mktree(pathbuf);
		cdsys(pathbuf);
	}
}
