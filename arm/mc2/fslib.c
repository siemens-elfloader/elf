#include "inc\mc.h"
#include "inc\mui.h"


//File Name
char* GetFileExt(char* fname)
{
  char *s1, *s2;
  s1=strrchr(fname,'.');
  if (s1)
  {
    int i=0;
    s2=++s1;       
    while(*s2++) i++;
    if (i>MAX_EXT) s1=0;
  }
  return (s1);
}

char* GetFileName(char* fname)
{
	int len = strlen(fname);
	int ii;
	for(ii = len-1; ii >= 0; ii--) {
		if (fname[ii] == '\\' || fname[ii] == '/') break;
	}
	if (ii>=0) return fname+ii+1;
	return fname;
}

char* GetFileDir(char* fname, char* buf)
{
	int ii;
	int len = strlen(fname);

	for(ii = len-2; ii > 0; ii--)
		if (fname[ii] == '\\' || fname[ii] == '/') break;
	len = ii;

	if (buf)
	{
		for(ii=0; ii<len; ii++) 
			buf[ii] = fname[ii];
		buf[len] = 0;
	}
	return buf;
}

const short badchars[] = {'?', '*', '"', ':', '<', '>', '/', '\\', '|', '\n', '\r'};

int _IsBadChar(short wch)
{
	for(int cc = 0; cc < sizeof(badchars)/sizeof(short); cc++)
		if (badchars[cc] == wch) return 1;
	return 0;  
}

int TestFileName(WSHDR* wsname)
{
	int cc=wsname->wsbody[0];
	if (!cc)return 0;
	short wchar;
	for(int ii=1;ii<=cc;ii++)
	{
		wchar = wsname->wsbody[ii];
		if (_IsBadChar(wchar)) return 0;
	}   
	return 1;
}

void CorFileName(WSHDR* wsname)
{
	int cc=wsname->wsbody[0];
	int pp=0;
	short wchar;
	for(int ii=1;ii<=cc;ii++)
	{
		wchar = wsname->wsbody[ii];
		if (!_IsBadChar(wchar)) 
			wsname->wsbody[++pp]=wsname->wsbody[ii];
	}   
	wsname->wsbody[0]=pp;
}

int GetFilesCnt(char* path)
{
	int res=1;
	if (isdir(path, &err))
	{
		int sub = EnumFiles(path, NULL, 0);
		res += (sub>>16) + (sub & 0xffff);
	}  
	return res;
}











//FS op
int fexists(char* fname)
{
	FSTATS fs;
	return (GetFileStats(fname,&fs,&err)!=-1);
}

int _EmptyEFP(DIR_ENTRY *de, int param)
{
	return 1;
}

int EnumFilesInDir(char* dname, ENUM_FILES_PROC enumproc, unsigned int param, int recursive, int enumDirs)
{
	unsigned int ccFiles   = 0;
	unsigned int ccSubDirs = 0;

	char path[MAX_PATH];
	DIR_ENTRY* pde = malloc(sizeof(DIR_ENTRY));
	if (path && pde)
	{
		sprintf(path, _s_stars, dname);
		if (FindFirstFile(pde, path, &err))
		{
			do
			{
				if (pde->file_attr & FA_DIRECTORY && enumDirs)
				{
					ccSubDirs++;
					sprintf(path, _s_s, dname, pde->file_name);
					int tmp = 0;
					if (recursive) tmp = EnumFiles(path, enumproc, param);

					ccSubDirs += tmp >> 16;
					ccFiles += tmp & 0xffff;
					if (enumproc)
						if (enumproc(pde, param)==0)
							break;
				}
				else
				{
					ccFiles++;
					if (enumproc)
						if (enumproc(pde, param)==0)
							break;
				}
			}
			while(FindNextFile(pde, &err));
#ifdef NEWSGOLD
			FindClose(pde, &err);
#endif
		}
#ifndef NEWSGOLD
		FindClose(pde, &err);
#endif
	}
	if (pde) mfree(pde);
	if (ccSubDirs > 0xffff) ccSubDirs = 0xffff;
	if (ccFiles > 0xffff)   ccFiles = 0xffff;
	
	return (ccSubDirs << 16 | ccFiles);
}

int EnumFiles(char* dname, ENUM_FILES_PROC enumproc, unsigned int param)
{
	// Рекурсивно пробегаем и по подкаталогам тоже
	return EnumFilesInDir( dname, enumproc, param, 1, 1);
}

//Files
#define BUF_SIZE 0x4000
int fcopy(char* src, char* dst)
{
	int fi=-1, fo=-1;
	char* buff=0;
	int cb, left;
	int res = 0;
	int attr=0;

	if (CONFIG_CONFIRM_REPLACE && fexists(dst))
	{
		if (MsgBoxYesNoWithParam(ind_pmt_exists, 0) != IDYES)
			return 1; // Все хорошо, если не стали перезаписывать
	}

	fi = fopen(src, A_ReadOnly + A_BIN, P_READ, &err);
	if (fi != -1) 
	{
		fo = fopen(dst, A_ReadWrite+A_BIN+A_Create+A_Truncate, P_READ+P_WRITE, &err);
		if (fo != -1) 
		{

			left = lseek(fi, 0, S_END, &err, &err);
			lseek(fi, 0, S_SET, &err, &err);
			if (left)
			{
				buff = malloc(BUF_SIZE);
				if (!buff) goto L_EXIT;
				progrsp_max = left;
				incprogrsp(0);
			}
			while (left) 
			{
				cb = left < BUF_SIZE ? left : BUF_SIZE;
				left -= cb;
				incprogrsp(cb);

				if (fread(fi, buff, cb, &err) != cb) goto L_EXIT;
				if (fwrite(fo, buff, cb, &err) != cb) goto L_EXIT;
			}
			endprogrsp();
			res = 1;
			GetFileAttrib(src, (unsigned char*)&attr, &err);
			SetFileAttrib(dst, attr, &err);
		}
	}
L_EXIT:
	if (buff) mfree(buff);
	if (fo != -1) fclose(fo, &err);
	if (fi !=- 1) fclose(fi, &err);
	return res;
}



//Tree
int mktree(char* path)
{
	if (isdir(path, &err)) return 1;
	int len = strlen(path);
	char c;
	char buf[MAX_PATH];

	for(int ii=0;ii<len;ii++)
	{
		c = path[ii];
		if (c=='\\')
		{
			buf[ii]=0;
			mkdir(buf, &err);
		}  
		buf[ii]=c;
	}
	return mkdir(path, &err);
}

int rmtree(char* path, int ip)
{
	FN_LIST fnlist;
	fn_zero(&fnlist);
	fn_fill(&fnlist, path);
	fn_rev(&fnlist);

	int res = 1;
	FN_ITM *itm = fnlist.items;
	while(itm && !progr_stop)
	{
		switch (itm->ftype)
		{
			case TYPE_COMMON_DIR:
				res &= rmdir(itm->full, &err);
				break;
			case TYPE_COMMON_FILE:
				res &= unlink(itm->full, &err);
				break;
			case TYPE_ZIP_DIR:
			case TYPE_ZIP_FILE:
			default:
				break;
		}
		itm=itm->next;
		if (ip) incprogr(1);
	}
	fn_free(&fnlist);
	return res;
}

int cptree(char* src, char* dst, int ip)
{
	FN_LIST fnlist;
	fn_zero(&fnlist);
	fn_fill(&fnlist, src);
	fn_rev(&fnlist);

	char dstfull[MAX_PATH];
	int psrc = strlen(src)+1;
	int res = 1;
	int attr=0;

	int tmp = progr_act;
	progr_act = ind_dirmking;
	incprogr(-1);

	FN_ITM *itm = fnlist.items;
	while(itm && !progr_stop)
	{
		if (itm->ftype == TYPE_COMMON_DIR) // TODO: ZIP_DIR...
		{
			char* pdst;
			if (itm->full[psrc-1])
			{
				char* psrcname = itm->full+psrc;
				sprintf(dstfull, _s_s, dst, psrcname);
				pdst = dstfull;
			}
			else
				pdst = dst;

			res &= mktree(pdst);
			GetFileAttrib(itm->full, (unsigned char*)&attr, &err);
			SetFileAttrib(pdst, attr, &err);
		}
		itm=itm->next;
	}
	progr_act = tmp;

	itm = fnlist.items;
	while(itm && !progr_stop)
	{
		if (itm->ftype == TYPE_COMMON_FILE) // TODO: ZIP_FILE...
		{
			char* psrcname = itm->full+psrc;
			sprintf(dstfull, _s_s, dst, psrcname);
			res &= fcopy(itm->full, dstfull);
		}
		itm=itm->next;
		if (ip) incprogr(1);
	}

	fn_free(&fnlist);
	return res;
}

/*
int mvtree(char* src, char* dst)
{
if (!cptree(src, dst)) return 0;
return rmtree(src);
}
*/


typedef struct
{
	int number;
	char cleanName[MAX_PATH];
	char* cleanExt;
} ParseFileNameStruct;

void parse_name(char* fname, ParseFileNameStruct* pfns)
{
	pfns->number = 0;
	strcpy(pfns->cleanName, fname);
	int fname_len = strlen(fname);
	char* ps = GetFileExt(pfns->cleanName); // Указатель на расширение
	
	if (ps != 0)
	{
		pfns->cleanExt = ps;
		*(--ps) = '\0';	// Разделяем имя и расширение
	}
	else
	{
		// Расширения нет вовсе
		pfns->cleanExt = str_empty;
		ps = pfns->cleanName + fname_len; // Ссылаемся на конец имени
	}
	
	if (ps - pfns->cleanName >= 3) // Должно быть 3 символа как минимум - скобки и число
	{
		if (*--ps == ')')  // Закрывающая скобка есть
		{
			int i = 0;
			int p10 = 1;
			while (--ps >= fname && *ps >= '0' && *ps <= '9' && p10 < 100000)
			{
				i += (*ps - '0') * p10;
				p10 *= 10;
			}
			if (ps >= fname && *ps == '(' && i != 0)
			{
				pfns->number = i;
				*ps = '\0'; // обрубаем чистое имя
			}
		}
	}
}

int find_next_name(ParseFileNameStruct* pfns)
{
	char buf[MAX_PATH];
	for (pfns->number++; pfns->number < 100; pfns->number++)
	{
		sprintf(buf, _s_i_s, pfns->cleanName, pfns->number, pfns->cleanExt);
		if (!fexists(buf))
			return 1; 
	}
	return 0;
}

//Dirs & Files
int fsrm(char* path, int ip)
{
	int res;
	if (isdir(path, &err))
		res = rmtree(path, ip);
	else
	{
		res = unlink(path, &err);
		if (ip) incprogr(1);
	}  
	return res;
}

int fscp(char* src, char* dst, int ip)
{
	progrsp_start = 1;
	int res;
	int isSame = (stricmp(src, dst) == 0);
	if (isdir(src, &err))
	{
		res = cptree(src, dst, ip);
	}
	else
	{
		if (isSame)
		{
			// Генерим новое имя и копируем...
			ParseFileNameStruct fns;
			parse_name(src, &fns);
			// Ищем следующее незанятое имя
			if (find_next_name(&fns))
			{
				char buf[MAX_PATH];
				sprintf(buf, _s_i_s, fns.cleanName, fns.number, fns.cleanExt);
				res = fcopy(src, buf);
			}
			else res = fcopy(src, dst);
		}
		else res = fcopy(src, dst);
		if (ip) incprogr(1);
	}
	progrsp_start = 0;
	return res;
}

int fsmv(char* src, char* dst)
{
	int res = 0;
	if (src[0] == dst[0])
	{
		if (stricmp(src, dst) != 0) // Только для неодинаковых файлов
			res = fmove(src, dst, &err);
		incprogr(GetFilesCnt(dst));
	}
	else
		if (fscp(src, dst, 1)) 
			res = fsrm(src, 0);
	return res;
}
