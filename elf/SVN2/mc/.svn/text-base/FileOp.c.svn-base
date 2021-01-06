#include "inc\mc.h"
#include "inc\mui.h"
#include "inc\zslib.h"

void ShowErr1(int lgind, char* str)
{
	sprintf(msgbuf, muitxt(lgind), str);
	MsgBoxError(1, (int) msgbuf);
}

void CB_WaitMsgBoxYesNo(int id)
{
	MsgBoxResult = id;
}

int ShowWaitMsgBoxYesNo()
{
	MsgBoxResult = -1;
	MsgBoxYesNo(1, (int)msgbuf , CB_WaitMsgBoxYesNo);
	while (MsgBoxResult < 0)
	{
		// Do nothing
		GetCPUClock();
	}
	return MsgBoxResult;
}

int MsgBoxYesNoWithParam(int lgind, char* str)
{
	sprintf(msgbuf, muitxt(lgind), str);
	return ShowWaitMsgBoxYesNo();
}

int isDir(int tab, char* dname)
{
	if (IsZipOpened(tab))
		return 1; // зипы рассматриваем как директорию
	else
		return isdir(dname, &err);
}

int cd(int tab, char *dname)
{
	unsigned int drv;
	if (IsZipOpened(tab))
	{
		drv = _CurDrv;
	}
	else
	{
		if (!isDir(tab, dname))
		{
			char buf[MAX_PATH];
			sprintf(buf, "%t\\", dname);
			if (!isdir(buf, &err))
			{
				ShowErr1(ind_err_badname_t, dname);
				return 0;
			}
		}
		drv = dname[0] - '0';
		if (drv == 4) drv = 3;
		if (drv >= MAX_DRV)
		{
			ShowErr1(ind_err_baddrv_t, dname);
			return 0;
		}
	}

	_cd_tab(tab, drv, dname);
	int res = SetTabDrv(tab, drv);
	if (!res) SetTabIndex(tab, 0, 0);
	
	return res;
}

int cdsys(char *dname)
{
	if (pathbuf2)
	{
		if (cd(systab, dname))
		{
			back_tab = curtab;
			curtab = systab;
			return 1;
		}
	}
	return 0;
}

int _DirSize(DIR_ENTRY *de, int param)
{
	if (param)
	{
		CHKDS_PARAM* p = (CHKDS_PARAM*)param;
		p->gsize += de->file_size;
		return 1;
	} 
	return 0;
}

int _ZipDirSize(FILEINF *file, int param)
{
	if (param)
	{
		CHKDS_PARAM* p = (CHKDS_PARAM*)param;
		p->gsize += file->size;
		p->gcsize += file->csize;
		return 1;
	} 
	return 0;
}

int M_DirSize(FILEINF *file, int param)
{
	if (file && pathbuf && strlen(file->sname))
	{
		CHKDS_PARAM* p = (CHKDS_PARAM*)param;
		CurFullPath(file->sname);
		switch (file->ftype)
		{
			case TYPE_COMMON_FILE:
				p->gsize += file->size;
				p->count++;
				break;
			case TYPE_COMMON_DIR:
				p->count += EnumFiles(pathbuf, _DirSize, (int)p) + 0x10000;
				break;
			case TYPE_ZIP_FILE:
				p->gsize += file->size;
				p->gcsize += file->csize;
				p->count++;
				break;
			case TYPE_ZIP_DIR:
				p->count += EnumZipFiles(_CurTab->zipInfo, pathbuf, _ZipDirSize, (int)p) + 0x10000;
				break;
			default:
				break;
		}
		return 1;
	} 
	return 0;
}

int _SetAttr(DIR_ENTRY *de, int param)
{
	if (pathbuf2)
	{
		sprintf(pathbuf2, _s_s, de->folder_name, de->file_name);
		SetFileAttrib(pathbuf2, param, &err);
		return 1;
	}  
	return 0;
}

int M_SetAttr(FILEINF *file, int param)
{
	if (file && pathbuf && strlen(file->sname))
	{
		CurFullPath(file->sname);
		SetFileAttrib(pathbuf, fa_attr, &err);
		if (fa_sb)
			EnumFiles(pathbuf, _SetAttr, fa_attr);
		return 1;
	}
	return 0;
}

int M_FileProp(FILEINF *file, int param)
{
	_FileProp(file);
	return 0; //Only first :)))
}

void MC_DrvInf(void)
{
	DoDrvInf();
	//  GeneralFuncF1(1);
}

void _NewDir(WSHDR *wsname)
{
	if (pathbuf && pathbuf2)
	{
		ws_2str(wsname, pathbuf2, MAX_PATH);
		strcpy(szLastNewDir, pathbuf2);	// Сохраняем введенное имя
		CurFullPath(pathbuf2);
		
		if (!mkdir(pathbuf, &err))
			MsgBoxError(1, (int) muitxt(ind_err_makedir));
		else
		{
			DoRefresh();
			//Ищим папку которую создали
			int ind = GetCurTabFileIndex(pathbuf2);
			SetCurTabIndex(ind, 0);
		} 
	}
	GeneralFuncF1(1);
}

void MC_NewDir(void)
{
	DoNewDir();
	CloseAllMenu();
}

void CB_NewFile(int id)
{
	if (id==IDYES || id==-1 || id==-2)
	{
		int f;
		if ((f=fopen(pathbuf,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err))!=-1)
		{
			fclose(f, &err);
			DoRefresh();
			//Ищем новый файл
			int ind = GetCurTabFileIndex(pathbuf2);
			SetCurTabIndex(ind, 0);
		}
		else
		{
			MsgBoxError(1, (int) muitxt(ind_err_makefile));
		}
	}
}

void _NewFile(WSHDR *wsname)
{
	if (pathbuf && pathbuf2)
	{
		ws_2str(wsname, pathbuf2, MAX_PATH);
		strcpy(szLastNewFile, pathbuf2); // Сохраняем введенное имя
		CurFullPath(pathbuf2);

		if (CONFIG_CONFIRM_REPLACE && fexists(pathbuf))
			MsgBoxYesNo(1, (int) muitxt(ind_pmt_exists), CB_NewFile);
		else
			CB_NewFile(IDYES);
	}
	GeneralFuncF1(1);
}

void MC_NewFile(void)
{
	DoNewFile();
	CloseAllMenu();
}

void CB_RenEx(int id)
{
	if (id==IDYES || id==-1 || id==-2)
	{
		char src[MAX_PATH];
		FILEINF *file = _CurFile();
		sprintf(src, _s_s, _CurPath, file->sname);
		if (id==IDYES) unlink(pathbuf, &err);
		int res;
		if (id==-2)
		{
			char tmpBuf[MAX_PATH];
			TmpFullPath2(tmpBuf, file->sname);
			res = fmove(src, tmpBuf, &err) && fmove(tmpBuf, pathbuf, &err);
		}
		else
			res = fmove(src, pathbuf, &err);

		DoRefresh();
		if (res)
		{
			//Ищем
			int ind = GetCurTabFileIndex(pathbuf2);
			SetCurTabIndex(ind, 0);
		} 
		else
			MsgBoxError(1, (int) muitxt(ind_err_rename));
	}
}

void _Rename(WSHDR *wsname)
{
	if (pathbuf && pathbuf2)
	{
		ws_2str(wsname, pathbuf2, MAX_PATH);
		CurFullPath(pathbuf2);

		if (wstrcmpi(wsname, _CurFile()->ws_name))
		{
			if (fexists(pathbuf))
			{
				if (CONFIG_CONFIRM_REPLACE)
					MsgBoxYesNo(1, (int) muitxt(ind_pmt_exists), CB_RenEx);
				else
					CB_RenEx(IDYES);
			}
			else
			{
				CB_RenEx(-1);
			}
		}
		else
			CB_RenEx(-2);
	} 
}

void MC_Rename(void)
{
	DoRen();
	CloseAllMenu();
}

int M_Delit(FILEINF *file, int param)
{
	if (file && pathbuf && strlen(file->sname))
	{
		CurFullPath(file->sname);

		if (file->attr & FA_READONLY)
		{
			if (!CONFIG_CONFIRM_DELETERO || MsgBoxYesNoWithParam(ind_pmt_rodel, file->sname) == IDYES)
			{
				SetFileAttrib(pathbuf, 0, &err);

				if (!fsrm(pathbuf, 1))
					*(int*)param = 0;;
			}
		}
		else
		{
			if (!fsrm(pathbuf, 1))
				*(int*)param = 0;
		}

		return 1;
	}
	return 0;
}


int M_FileCnt(FILEINF *file, int param)
{
	if (file && pathbuf)
	{
		CurFullPath(file->sname);
		*(int*)param += GetFilesCnt(pathbuf);
		return 1;
	} 
	return 0;
}

void S_Delit(void)
{
	if (_CurIndex < 0) return;
	Busy = 1;
	int res = 1;

	initprogr(ind_deling);
	EnumSel(M_FileCnt, (int)&progr_max);
	incprogr(0);

	// Store current file index
	int ind = _CurIndex;

	EnumSel(M_Delit, (int)&res);

	if (!res)
	{
		MsgBoxError(1, (int) muitxt(ind_err_delete));
	}
	else if (ind < _CurTab->ccFiles) // Только если есть куда идти вниз
	{
		
		// List is not refreshed yet, so move index to the next file if there are no errors
		SetCurTabIndex(ind + 1, 0);
	}

	DoRefresh();

	endprogr();
	Busy = 0;
}

void MC_Open(void)
{
	DoOpen();
	CloseMenu();
}

int M_MoveCopy(FILEINF *file, int param)
{
	if (file && pathbuf && strlen(file->sname))
	{
		int pname = strlen(_CurPath) + 1;
		CurFullPath(file->sname);
		fn_add(&buffer, param, file->ftype, pname, pathbuf, IsInZip() ? _CurTab->zipInfo->szZipPath : NULL);
		return 1;
	}
	return 0;
}

//Buffer
FN_LIST buffer;

void S_Paste(void)
{
	if (buffer.count)
	{
		if (pathbuf)
		{
			int res=1;
			Busy = 1;

			if (buffer.type == FNT_MOVE) progr_act = ind_moveing;
			else if (buffer.type == FNT_COPY) progr_act = ind_copying;

			initprogr(progr_act);

			FN_ITM* itm = buffer.items;
			FN_ITM* last_itm = itm;
			while(itm)
			{
				//	 progr_max+=itm->full[0]!=_CurPath[0] || buffer.type!=FNT_MOVE?GetFilesCnt(itm->full):1;
				if (itm->ftype == TYPE_COMMON_DIR || itm->ftype == TYPE_COMMON_FILE)
					progr_max += GetFilesCnt(itm->full);
				else
					progr_max++; // Для зипа пока заглушка
				last_itm = itm;
				itm = itm->next;
			}
			incprogr(0);

			itm = buffer.items;
			ZipBufferExtractBegin();
			while(itm && !progr_stop)
			{
				if (itm->ftype == TYPE_COMMON_DIR || itm->ftype == TYPE_COMMON_FILE)
				{
					char *sname = itm->full + itm->pname;
					sprintf(pathbuf, _s_s, _CurPath, sname);
					if (buffer.type == FNT_MOVE)
					{
						progr_act = ind_moveing;
						res &= fsmv(itm->full, pathbuf);
					}
					else if (buffer.type == FNT_COPY)
					{
						progr_act = ind_copying;
						res &= fscp(itm->full, pathbuf, 1);
					}
				}
				else
				{
					// Пока обрабатываем только копирование
					if (buffer.type == FNT_COPY)
						res &= (ZipBufferExtract(itm, _CurPath) == UNZ_OK);
				}	  

				itm=itm->next;
			}
			ZipBufferExtractEnd();

			if (!res)
				MsgBoxError(1, (int) muitxt(ind_err_resnok));

			UpdateAll();

			//Ищем первый файл
			int ind = GetCurTabFileIndex(GetFileName(last_itm->full));
			SetCurTabIndex(ind, 0);

			fn_free(&buffer);

			endprogr();
			Busy = 0;
		}
	}
	else
		ShowMSG(1, (int) muitxt(ind_err_nofiles));
}
