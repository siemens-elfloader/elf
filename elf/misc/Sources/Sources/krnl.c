#include "inc\mc.h"
#include "inc\mui.h"
#include "inc\lng.h"
#include "inc\ColorMap.h"
#include "inc\config.h"
#include "inc\zslib.h"

char in_open_path[MAX_PATH];
char mcpath[MAX_PATH];
int back_tab;

int progr_stop  = 0;
int progr_act   = 0;

int progr_max   = 0;
int progr_cur   = 0;
int progr_start = 0;

int progrsp_max = 0;
int progrsp_cur = 0;
int progrsp_start = 0;

int show_hidden = 0;
int show_system = 0;

volatile int AutoExitCounter=0;

DRVINFO Drives[MAX_DRV] = {
	{0, "0:", psz_drv_0, 1},
	{1, "1:", psz_drv_1, 1},
	{2, "2:", psz_drv_2, 1},
	{4, "4:", psz_drv_4, 1}
};

int curtab=0;
TABINFO* tabs[MAX_TABS+1];
FILEINF* FileListBase[MAX_TABS+1];

const char ext_file[] = "mcfileico.cfg";
const char keys_file[] = "mckeys.cfg";
const char cfg_file[] = "mc.bcfg";
char etc_path[] = DEFAULT_DISK":\\ZBin\\etc";

const char* def_filter = "*.*";
const char* def_new_file = "";

const char zip_ext[]="zip";

char* str_empty = "";

GBSTMR offtm;

void SetTabIndex(int tab, int num, int slide)
{
	TABINFO *tmp = tabs[tab];

	if (tmp->ccFiles == 0)
	{
		num = -1;
	}
	else 
	{
		if (slide)
		{
			if ( num >= tmp->ccFiles) num = 0;
			else if (num < 0) num = tmp->ccFiles - 1;
		}
		else
		{
			if (num >= tmp->ccFiles) num = tmp->ccFiles - 1;
			else if (num < 0) num = 0;
		}
	}
	tmp->iIndex[tmp->CurDrv] = num;
}

void SetCurTabIndex(int num, int slide)
{
	SetTabIndex(curtab, num, slide);
}

int GetTabIndex(int tab)
{
	return tabs[tab]->iIndex[ tabs[tab]->CurDrv ];
}

char* GetTabPath(int tab)
{
	if (IsZipOpened(tab))
		return tabs[tab]->zipInfo->szCurDir;
	else
		return (char*)&tabs[tab]->szDirs[tabs[tab]->CurDrv];
}

void FullInit(FILEINF *file)
{
	if (!file || file->inited) return;

	char buf[128];
	if (!file->ws_short)
	{
		file->uccnt = getLVC(&file->ws_name->wsbody[1], file->ws_name->wsbody[0], BoldFont);
		if (file->uccnt)
		{
			file->ws_short = AllocWS(file->uccnt+1);
			cutname(file->ws_name, file->ws_short, file->uccnt);
		}
	}
	if (!file->ws_attr)
	{
		attr2s(file->attr, buf);
		file->ws_attr = AllocWS(strlen(buf)+1);
		str_2ws(file->ws_attr, buf, 64);
	}
	if (!file->ws_size)
	{
		sz2s(file->size, buf);
		file->ws_size = AllocWS(strlen(buf)+1);
		wsprintf(file->ws_size, _t, buf);
	}
	if (!file->ws_time)
	{
		fdt2s(file->time, buf);
		file->ws_time = AllocWS(strlen(buf)+1);
		str_2ws(file->ws_time, buf, 64);
	}
	if (!file->ext)
	{
		file->ext = GetExt(file->sname, file->attr);
	}
	if (file->ftype == TYPE_ZIP_FILE && !file->ws_ratio)
	{
		if (file->size != 0 && file->csize != 0)
		{
			float ratio = (float)file->csize * (float)100 / (float)file->size;
			sprintf(buf, "%.0f%%", ratio); // без цифр после точки
			file->ws_ratio = AllocWS(strlen(buf) + 1);
			str_2ws(file->ws_ratio, buf, 64);
		}
	}
	file->inited = 1;
}

void AddFile_Full(int tab, int findex, char* fname, WSHDR *fwsname, unsigned int fsize, short fattr,
				  unsigned int ftime, int fcsize, int ftype)
{
	FILEINF* file	= malloc(sizeof(FILEINF));
	file->id		= findex;
	file->sname		= fname;
	file->attr		= fattr;
	file->size		= fsize;
	file->time		= ftime;
	file->ext		= 0;
	file->inited	= 0;
	file->ws_name	= fwsname;
	file->uccnt		= 0;
	file->ws_short	= 0;
	file->ws_attr	= 0;
	file->ws_size	= 0;
	file->ws_time	= 0;
	
	file->csize		= fcsize;
	file->ws_ratio	= 0;
	file->ftype		= ftype;

	LockSched();

	file->next = FileListBase[tab]->next;
	FileListBase[tab]->next = file;

	UnlockSched();
}

void AddFile(int tab, int findex, char* fnameOriginal, unsigned int fsize, short fattr,
			 unsigned int ftime, int fcsize, int ftype)
{
	int len = strlen(fnameOriginal);
	char* fname = malloc(len + 1);
	WSHDR* wsname = AllocWS(len + 1);
	str_2ws(wsname, fnameOriginal, len);
	strcpy(fname, fnameOriginal);

	AddFile_Full(tab, findex, fname, wsname, fsize, fattr, ftime, fcsize, ftype);
}

void AddFileFromDE(int tab, int findex, DIR_ENTRY* pde)
{
	AddFile(tab, findex, pde->file_name, pde->file_size, pde->file_attr, pde->create_date_time, 0, (pde->file_attr & FA_DIRECTORY) ? TYPE_COMMON_DIR : TYPE_COMMON_FILE);
}

void DelFiles(int tab)
{
	if (tabs[tab]->ccFiles)
	{
		LockSched();
		scfile=NULL;
		while(FileListBase[tab]->next!=FileListBase[tab])
		{
			FILEINF *file = FileListBase[tab]->next;	// Второй элемент
			FileListBase[tab]->next = file->next;		// Следующий у FileListBase - на третий
			if (file)
			{
				if (file->ws_ratio)	FreeWS(file->ws_ratio);
				if (file->ws_time)	FreeWS(file->ws_time);
				if (file->ws_size)	FreeWS(file->ws_size);
				if (file->ws_attr)	FreeWS(file->ws_attr);
				if (file->ws_short)	FreeWS(file->ws_short);
				mfree(file);
				if (file->ws_name)	FreeWS(file->ws_name); 
				if (file->sname)	mfree(file->sname);
			} 
			tabs[tab]->ccFiles--;
		}
		UnlockSched();
	}
}


int FillRealPathFiles(int tab, char* dname)
{
	DIR_ENTRY de;
	int num = 0;

	if (pathbuf)
	{
		sprintf(pathbuf, _s_stars, dname);
		//   ShowMSG(1, (int) pathbuf);

		if (FindFirstFile(&de, pathbuf, &err))
		{
			do
			{
				if (!tabs[tab]->szFilter[0] || de.file_attr & FA_DIRECTORY)
				{
					if ( (show_hidden || !(de.file_attr & FA_HIDDEN))
						&& (show_system || !(de.file_attr & FA_SYSTEM)) )
						AddFileFromDE(tab, num++, &de);
				} 
			}
			while (FindNextFile(&de, &err));
		}
		FindClose(&de, &err);


		if (tabs[tab]->szFilter[0])
		{
			sprintf(pathbuf, _s_s, dname, tabs[tab]->szFilter);
			if (FindFirstFile(&de, pathbuf, &err))
			{
				do
				{
					if (!(de.file_attr & FA_DIRECTORY))
					{
						if ( (show_hidden || !(de.file_attr & FA_HIDDEN))
							&& (show_system || !(de.file_attr & FA_SYSTEM)) )
							AddFileFromDE(tab, num++, &de);
					} 
				}
				while (FindNextFile(&de, &err));
			}
			FindClose(&de,&err);
		}
	}

	return num;
}

// Заполняет список файлов текущей директории
int FillFiles(int tab, char* dname)
{
	if (tabs[tab]->ccFiles) DelFiles(tab);
	if (IsZipOpened(tab))
		tabs[tab]->ccFiles = FillZipFiles(tab, dname);
	else
		tabs[tab]->ccFiles = FillRealPathFiles(tab, dname);
	SortFiles(tab);
	return tabs[tab]->ccFiles;
}

int SetTabDrv(int tab, int num)
{
	if (num >= MAX_DRV) num = 0;
	else if (num < 0) num = MAX_DRV - 1;
	tabs[tab]->CurDrv = num;
	UpdateCSMname();
	return FillFiles(tab, GetTabPath(tab));
}

int SetCurTabDrv(int num)
{
	return SetTabDrv(curtab, num);
}

int RefreshTab(int tab)
{
	FILEINF *cfile = _CurTabFile(tab);
	char* lpname;
	if (cfile)
	{
		lpname = malloc(strlen(cfile->sname) + 1);
		strcpy(lpname, cfile->sname);
	} 

	int res = FillFiles(tab, GetTabPath(tab));

	int ind;
	if (cfile)
	{
		ind = GetFileIndex(tab, lpname);
		mfree(lpname);
	}
	else
		ind = 0;

	SetTabIndex(tab, ind, 0);
	return res;
}

int DoRefresh()
{
	return RefreshTab(curtab);
}

void UpdateAll()
{
	for(int ii=0; ii < MAX_TABS + 1; ii++)
		RefreshTab(ii);
}

void _cd_tab(int tab, int drv, char* dname)
{
	if (IsZipOpened(tab))
	{
		if (strcmp(tabs[tab]->zipInfo->szCurDir, dname))
		{
			tabs[tab]->iBase[drv] = 0;
			tabs[tab]->iIndex[drv] = 0;
			strcpy(tabs[tab]->zipInfo->szCurDir, dname);
		}
	}
	else
	{
		if (strcmp(tabs[tab]->szDirs[drv], dname))
		{
			tabs[tab]->iBase[drv] = 0;
			tabs[tab]->iIndex[drv] = 0;
			strcpy(tabs[tab]->szDirs[drv], dname);
		}
	}
}

int InitTab(int tab)
{
	tabs[tab] = malloc(sizeof(TABINFO));
	{
		tabs[tab]->sort = ST_FIRST;
		tabs[tab]->szFilter[0]=0;
	} 

	tabs[tab]->zipInfo = malloc(sizeof(ZIPINF));
	{
		zeromem(tabs[tab]->zipInfo, sizeof(ZIPINF));
	}

	FileListBase[tab] = malloc(sizeof(FILEINF));
	{
		zeromem(FileListBase[tab], sizeof(FILEINF));
		FileListBase[tab]->id = -1;
		FileListBase[tab]->sname = psz_errfile;
		FileListBase[tab]->next = FileListBase[tab];
	}

	// strcpy(tabs[tab]->szFilter, "a*.*");
	for(int num = 0; num < 4; num++)
	{
		_cd_tab(tab, num, Drives[num].path);
	}
	return SetTabDrv(tab, 0);
}

void FreeTab(int tab)
{
	mfree(FileListBase[tab]);
	CloseTabZip(tab);
	mfree(tabs[tab]->zipInfo);
	mfree(tabs[tab]);
}

void CB_CS(int id)
{
	if ((id==IDYES) && pathbuf) 
		if (!LoadCS(pathbuf))
			MsgBoxError(1, (int) muitxt(ind_err_badformat));
		else
			SaveCS(NULL);
}

void CB_LG(int id)
{
	if ((id==IDYES) && pathbuf) 
		if (!LoadMUI(pathbuf))
			MsgBoxError(1, (int) muitxt(ind_err_badformat));
		else
		{
			SaveMUI(NULL);
			sprintf(msgbuf, _ss, muitxt(ind_lng), muitxt(ind_lngname));
			ShowMSG(1, (int) msgbuf);
		}  
}
//####### Commands #######

void S_ZipOpen(void)
{
	int err = OpenTabZip(curtab, pathbuf);
	if (err == UNZ_OK)
	{
		cd(curtab, str_empty);
		SetTabIndex(curtab, 0, 0);
	}
	else if (err != -1) // ignore propr_stop
	{
		sprintf(msgbuf, "OpenZip error %i", err);
		MsgBoxError(1, (int)msgbuf);
	}
	
	if (IsGuiOnTop(MAINGUI_ID)) REDRAW();
}

void DoOpen()
{
	if (_CurIndex<0) return;

	FILEINF *file = _CurFile();
	if (file && pathbuf && strlen(file->sname))
	{
		CurFullPath(file->sname);
		if (file->attr & FA_DIRECTORY) 
			cd(curtab, pathbuf);
		else
		{
			char* sz = GetFileExt(file->sname);
			if ((int) sz) 
			{
				char szext[MAX_EXT];
				strtolower(sz, szext, MAX_EXT);

				if (!strncmp(szext, mcbm_ext, MAX_EXT))
				{
					UseBM(pathbuf);
					return;
				}
				else if (CONFIG_ZIP_ENABLE && !strncmp(szext, zip_ext, MAX_EXT))
				{
					if (!IsInZip())
						SUBPROC((void*)S_ZipOpen);
					return;
				}
				else if (!strncmp(szext, mccs_ext, MAX_EXT))
				{
					MsgBoxYesNo(1, (int) muitxt(ind_pmt_impcs), CB_CS);
					return;
				}
				else if (!strncmp(szext, mclg_ext, MAX_EXT))
				{
					MsgBoxYesNo(1, (int) muitxt(ind_pmt_implg), CB_LG);
					return;
				}
			}

			if (wsbuf)
			{
				if (IsInZip())
				{
					// Берем имя временного файла
					char szTempFilePath[MAX_PATH];
					sprintf(szTempFilePath, _s_s, CONFIG_TEMP_PATH, GetFileName(pathbuf));

					// Грохаем если он там есть
					if (fexists(szTempFilePath))
						fsrm(szTempFilePath, 0);

					// Извлекаем наш файл или выходим
					int res = ExtractFileByID(tabs[curtab]->zipInfo, file->id,
						(char*)CONFIG_TEMP_PATH, 0);
					
					if (res == UNZ_OK)
						str_2ws(wsbuf, szTempFilePath, MAX_PATH);
					else
						return;
				}
				else
				{
					str_2ws(wsbuf, pathbuf, MAX_PATH);
				}
				ExecuteFile(wsbuf,0,0);
			}
		}  
	}
}

void CB_Exit(int id)
{
	if (id == IDYES)
	{
		// Выходим из зипа на текущем табе с восстановлением позиции
		ExitFromZip();
	
		// Закрываем остальные зипы при выходе
		for (int i = 0; i < MAX_TABS; i++)
			if (i != curtab && IsZipOpened(i)) CloseTabZip(i);
			
		Terminate = progr_stop = 1;
		if (!Busy) GeneralFuncF1(1);
	}
}

void DoExit()
{
	if (CONFIG_CONFIRM_EXIT)
		MsgBoxYesNo(1, (int) muitxt(ind_pmt_exit), CB_Exit);
	else
		CB_Exit(IDYES);
}

void ExitFromZip()
{
	if (IsInZip())
	{
		//Сохраняем имя тек. зипа
		char lpname[MAX_PATH];
		strcpy(lpname, GetFileName(_CurTab->zipInfo->szZipPath));

		CloseTabZip(curtab);
		RefreshTab(curtab);

		//Ищем файл из которого вышли
		int ind = GetFileIndex(curtab, lpname);
		SetTabIndex(curtab, ind, 0);
	}
}

int DoBack()
{
	int res = 0;
	if (pathbuf)
	{
		if (curtab < MAX_TABS)
		{
			char lpname[MAX_PATH];
			char* path = IsInZip() ? _CurTab->zipInfo->szCurDir : _CurPath;
			// Читаем родительскуюя папку в pathbuf
			GetFileDir(path, pathbuf);
			// Проверка на корень
			int goOut = IsInZip() ? *path == '\0' : *pathbuf == '\0';
			
			if (!goOut)
			{
				//Сохраняем имя тек. папки
				strcpy(lpname, GetFileName(path));

				res = cd(curtab, pathbuf);

				//Ищем папку из которой вышли
				int ind = GetFileIndex(curtab, lpname);
				SetTabIndex(curtab, ind, 0);
			}
			else if (IsInZip()) ExitFromZip();
			else if (CONFIG_BACK_EXIT) DoExit();
		}
		else
		{
			curtab = back_tab < MAX_TABS ? back_tab : 0;
		}  
	}  
	return res;
}

void DoSwapTab()
{
	curtab++;
	if (curtab>=MAX_TABS) curtab=0;
	UpdateCSMname();
}

int cordrv(int num, int inc)
{
	do
	{
		num = (MAX_DRV + num + inc) % MAX_DRV;
	}
	while (!Drives[num].enabled);

	return num;
}

void DoPrvDrv()
{
	if (curtab < MAX_TABS && !IsInZip())
		SetCurTabDrv(cordrv(_CurDrv, -1));
}

void DoNxtDrv()
{
	if (curtab < MAX_TABS && !IsInZip())
		SetCurTabDrv(cordrv(_CurDrv, +1));
}

void DoUp()
{
	SetCurTabIndex(--_CurIndex, 1);
}

void DoDwn()
{
	SetCurTabIndex(++_CurIndex, 1);
}

void DoPgUp()
{
	_CurIndex-=LONG_SCRL;
	if (_CurIndex<0) _CurIndex=0;		
	SetCurTabIndex(_CurIndex, 0);
}

void DoPgDwn()
{
	_CurIndex+=LONG_SCRL;
	_CurBase  = _CurIndex;
	if (_CurIndex>=_CurCount)_CurIndex=_CurCount-1;
	SetCurTabIndex(_CurIndex, 0);
}

void DoBegin()
{
	SetCurTabIndex(0, 0);
}

void DoChk()
{
	ChkFile(_CurFile());
	if (CONFIG_CUR_DOWN_ON_CHECK) SetCurTabIndex(++_CurIndex, 1);
}

void DoChkAll()
{
	ChkAll(1);
}

void DoUnCAll()
{
	ChkAll(0);
}

void DoInvChk()
{
	ChkAll(-1);
}

int DoFileProp()
{
	if (_CurIndex<0) return 0;
	EnumSel(M_FileProp, 0);
	return 1;
}

void DoNewDir()
{
	if (IsInZip()) return; // Пока не обрабатывается
	
	if (wsbuf)
	{
		if (*szLastNewDir)
			wsprintf(wsbuf, szLastNewDir);
		else
			wsprintf(wsbuf, def_new_dir);

		TextInput(muitxt(ind_newdir), muitxt(ind_name), 1, wsbuf, _NewDir);
	} 
}

void DoNewFile()
{
	if (IsInZip()) return; // Пока не обрабатывается
	
	if (wsbuf)
	{
		if (*szLastNewFile)
			wsprintf(wsbuf, szLastNewFile);
		else
			wsprintf(wsbuf, def_new_file);

		TextInput(muitxt(ind_newfile), muitxt(ind_name), 1, wsbuf, _NewFile);
	} 
}

void DoShowHid()
{
	show_hidden = !show_hidden;
	DoRefresh();
}

void DoShowSys()
{
	show_system = !show_system;
	DoRefresh();
}

void DoShowHidSys()
{
	show_hidden = !show_hidden;
	show_system = show_hidden;
	DoRefresh();
}

void _Filter(WSHDR *wsname)
{
	ws_2str(wsname, _CurTab->szFilter, MAX_PATH);
	if (strcmp(_CurTab->szFilter, def_filter) == 0)
		_CurTab->szFilter[0] = 0;

	DoRefresh();
	GeneralFuncF1(1);
}

void DoFilter()
{
	if (wsbuf)
	{
		if (_CurTab->szFilter[0])
			str_2ws(wsbuf, _CurTab->szFilter, MAX_PATH);
		else
			str_2ws(wsbuf, def_filter, MAX_PATH);

		TextInput(muitxt(ind_filter), muitxt(ind_name), 0, wsbuf, _Filter);
	} 
}

void DoRen()
{
	if (IsInZip()) return; // Пока не обрабатывается
	
	FILEINF *cfile = _CurFile();
	if (cfile)
		TextInput(muitxt(ind_rename), muitxt(ind_name), 1, cfile->ws_name, _Rename);
}

void CB_Past(int id)
{
	if (id == IDYES) SUBPROC((void *)S_Past);
}

void DoPaste()
{
	if (IsInZip()) return; // Пока не обрабатывается
	
	if (buffer.count)
	{
		if (buffer.type == FNT_MOVE)
		{
			if (CONFIG_CONFIRM_MOVE)
				MsgBoxYesNo(1, (int)muitxt(ind_pmt_move), CB_Past);
			else
				CB_Past(IDYES);
		}
		else if (buffer.type == FNT_COPY)
		{
			if (CONFIG_CONFIRM_COPY)
				MsgBoxYesNo(1, (int)muitxt(ind_pmt_copy), CB_Past);
			else
				CB_Past(IDYES);
		}
	} 
}

void CB_Cancel(int id)
{
	if (id==IDYES)fn_free(&buffer);
}

void DoCancel()
{
	if (buffer.count)
		MsgBoxYesNo(1,(int)muitxt(ind_pmt_cancel), CB_Cancel);
}

void DoCopy()
{
	EnumSel(M_MoveCopy, FNT_COPY);
}

void DoMove()
{
	if (IsInZip()) return; // Пока не обрабатывается
	
	EnumSel(M_MoveCopy, FNT_MOVE);
}

void CB_Del(int id)
{
	if (id==IDYES) SUBPROC((void *)S_Delit);
}

void DoDel()
{
	if (IsInZip()) return; // Пока не обрабатывается
	
	if (CONFIG_CONFIRM_DELETE)
		MsgBoxYesNo(1, (int) muitxt(ind_pmt_del), CB_Del);
	else
		CB_Del(IDYES);
}

void DoRoot()
{
	if (IsInZip()) return; // Пока не обрабатывается
	
	if (curtab < MAX_TABS)
		cd(curtab, Drives[_CurDrv].path);
}

void DoShowPath()
{
	ShowMSG(0, (int) _CurPath);
}

void DoSortN()
{
	_CurTab->sort=(_CurTab->sort & STD_MASK) | ST_NAME;
	DoRefresh();
}

void DoSortE()
{
	_CurTab->sort=(_CurTab->sort & STD_MASK) | ST_EXT;
	DoRefresh();
}

void DoSortS()
{
	_CurTab->sort=(_CurTab->sort & STD_MASK) | ST_SIZE;
	DoRefresh();
}

void DoSortD()
{
	_CurTab->sort=(_CurTab->sort & STD_MASK) | ST_DATE;
	DoRefresh();
}

void DoSetSort()
{
	int srt = (_CurTab->sort & STV_MASK);
	srt=(srt>=ST_LAST)?srt=ST_FIRST:srt+1;
	_CurTab->sort=(_CurTab->sort & STD_MASK) | srt;
	DoRefresh();
}

void DoSortR()
{
	_CurTab->sort=(_CurTab->sort & STV_MASK) | (~_CurTab->sort & STD_MASK);
	DoRefresh();
}

void DoErrKey()
{
	MsgBoxError(1, (int) muitxt(ind_err_badkey));
}

//####### ######## #######


// Zip
void DoZipCopy()
{
	//EnumSel(M_MoveCopy, FNT_COPY);
}














FILEINF *_CurFile()
{
	return _CurTabFile(curtab);
}

FILEINF *_CurTabFile(int tab)
{
	int ind = GetTabIndex(tab);
	if (ind<0) return NULL;

	FILEINF *file = FileListBase[tab];
	for(int ii=0;ii<=ind;ii++) 
		if (file)
			file = file->next;
		else
			return NULL;

	return file;
}

int GetFileIndex(int tab, char* fname)
{
	if (tabs[tab]->ccFiles) 
	{
		int ind=0;
		FILEINF *file = FileListBase[tab]->next;
		while(file != FileListBase[tab])
		{
			if (!strcmp(fname, file->sname)) 
				return ind;
			file = file->next;
			ind++;
		}
	} 
	return -1;
}

int ___IsMultiChk(FILEINF *file, int param){ return 1;}
int IsMultiChk()
{
	return EnumChk(___IsMultiChk, 0);
}

int EnumChk(ENUM_SEL_PROC EnumProc, int param)
{
	int cc=0;
	if (tabs[curtab]->ccFiles) 
	{
		FILEINF *file = FileListBase[curtab]->next;
		while(file!=FileListBase[curtab])
		{
			if (file->attr & FA_CHECK)
			{
				cc++;
				if (EnumProc)
					if (EnumProc(file, param)==0) break;
			}
			file = file->next;
		}
	}
	return cc;
}

int EnumSel(ENUM_SEL_PROC EnumProc, int param)
{
	int cc=EnumChk(EnumProc, param);
	if (cc==0) 
	{
		if (EnumProc)
		{
			FILEINF *cfile = _CurFile();
			if (cfile)
			{
				EnumProc(cfile, param);
				cc++;
			}  
		}  
	}
	return cc;
}

/*
int IsChkAll()
{
if (tabs[curtab]->ccFiles) 
{
FILEINF *file = FileListBase[curtab]->next;
while(file!=FileListBase[curtab])
{
if (!(file->attr & FA_CHECK)) return 0;
file = file->next;
}
return 1;
}
return 0;
}
*/

int ChkAll(int chk)
{
	if (tabs[curtab]->ccFiles) 
	{
		FILEINF *file = FileListBase[curtab]->next;
		while(file!=FileListBase[curtab])
		{
			if (chk>0 || (chk<0 && !(file->attr & FA_CHECK)))
				file->attr = file->attr | FA_CHECK;
			else
				file->attr = file->attr & ~FA_CHECK;

			file = file->next;
		}
		return 1;
	}
	return 0;
}

void ChkFile(FILEINF *file)
{
	if (file)
	{
		file->attr = file->attr & FA_CHECK ? file->attr & ~FA_CHECK : file->attr | FA_CHECK;
	}   
}




void initprogr(int act)
{
	progr_start = 1;
	progr_max = 0;
	progr_stop = 0;
	progr_act = act; 
}

void incprogr(int inc)
{
	if (inc > 0) progr_cur += inc;
	else if (!inc) progr_cur = 0;
	
	if (IsGuiOnTop(MAINGUI_ID)) REDRAW();
}

void incprogrsp(int inc)
{
	if (inc) progrsp_cur += inc;
	else progrsp_cur = 0;
	
	if (IsGuiOnTop(MAINGUI_ID)) REDRAW();
}

void endprogr()
{
	progr_start = 0;
	if (IsGuiOnTop(MAINGUI_ID)) REDRAW();
}

void endprogrsp()
{
	progrsp_max = progrsp_cur = 0;
	if (IsGuiOnTop(MAINGUI_ID)) REDRAW();
}

//void beginmsg(int msg_index)
//{
//	show_msg_ind = msg_index;
//	if (IsGuiOnTop(MAINGUI_ID)) REDRAW();
//}
//
//void endmsg()
//{
//	show_msg_ind = 0;
//	if (IsGuiOnTop(MAINGUI_ID)) REDRAW();
//}

char* CurFullPath(char* sfile)
{
	if (pathbuf)
	{
		if (IsInZip())
			sprintf(pathbuf, _s_s, _CurTab->zipInfo->szCurDir, sfile);
		else
			sprintf(pathbuf, _s_s, _CurPath, sfile);
	}
	return pathbuf;
}

char* CurFullPathBM(char* buff, char* sfile)
{
	if (buff)
		sprintf(buff, _s_s, _CurPath, sfile);
	return buff;
}

char* TmpFullPath2(char* buff, char* sfile)
{
	if (buff)
	{
		TTime t;
		TDate d;
		GetDateTime(&d,&t);
		sprintf(buff, _s_s_d, _CurPath, sfile, *(int*)&t);
	}  
	return buff;
}

char* MCFilePath(const char* sfile)
{
	if (pathbuf)
		sprintf(pathbuf, _s_s, mcpath, sfile);
	return pathbuf;
}

//this procedure resets counter
void ResetAutoExit() 
{
	AutoExitCounter=0;
}

const int AutExitCheckFrequencySec = 15;
void AutoExitProc()
{
	if (CONFIG_AUTO_EXIT_AFTER_MIN)
		GBS_StartTimerProc(&offtm, 216 * AutExitCheckFrequencySec, AutoExitProc); //sending timer in 5sec period

	if (!Busy && (IsGuiOnTop(MAINGUI_ID) || CONFIG_ENABLE_BACKGROUND_EXIT))
	{
		AutoExitCounter++;

		if(AutoExitCounter * AutExitCheckFrequencySec > CONFIG_AUTO_EXIT_AFTER_MIN * 60)
			CloseCSM(MAINCSM_ID);
	}
}
