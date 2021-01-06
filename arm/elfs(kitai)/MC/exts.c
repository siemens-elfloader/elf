#include "inc\exts.h"
#include "inc\mc.h"

#define ICO_CHECK	1382
#define ICO_UNKNOWN	1033
#define ICO_FOLDER	1208

unsigned int ccExt = 0;
EXTINF ext_dir;
EXTINF ext_chk;
EXTINF ext_unk = {0, 0, 0, ICO_UNKNOWN, &ext_chk};
EXTINF ext_chk = {0, 0, 0, ICO_CHECK, &ext_dir};
EXTINF ext_dir = {0, 0, 0, ICO_FOLDER, &ext_unk};
EXTINF* ext_first_s = &ext_unk;
EXTINF* ext_last_s = &ext_dir;

DYNPNG_EXT* ext_pnglist = NULL;

int loadPngLater = 1;

int str_get_crc(char* str)
{
  int crc = 0;
  for (int ii = 0,c; c=*str++; ii++)
    crc += c* (ii + 1);
  return crc;
}

int AddIconToPngCache(char* fname)
{
	char* imgname = fname;
	if (!strstr(imgname, ":")) // Если не полное имя, то ищем в Images
		imgname = GetImagePath(imgname);
	if (!fexists(imgname)) return -1;
	
	// Пробуем для начала найти в кэше
	DYNPNG_EXT* png = ext_pnglist;
	DYNPNG_EXT* png_top = ext_pnglist;
	int png_n = FIRST_UCS2_BITMAP;
	int crc = str_get_crc(imgname);
	while (png)
	{
		if (png->crc == crc && stricmp(png->fname, imgname) == 0)
		{
#ifdef LOG
			sprintf(msgbuf, "AddIconToPngCache: Icon in cache %s, %i", imgname, png->dpl.icon);
			_WriteLog(msgbuf);
#endif
			return png->dpl.icon;
		}
		png_top = png;
		png = png->dpl.next;
		png_n++;
	}
	
	// В кэше нет, добавляем
	IMGHDR* img = CreateIMGHDRFromPngFile(imgname, 0);
	if (!img) return (-1);
	
	// Получилось создать картинку, добавляем ее в список
	png = malloc(sizeof(DYNPNG_EXT));
	png->uni_n = png_n;
	png->dpl.next = 0;
	png->dpl.icon = GetPicNByUnicodeSymbol(png_n);
	png->dpl.img = img;
	png->fname = malloc(strlen(imgname) + 1);
	png->crc = crc;
	strcpy(png->fname, imgname);
	if (png_top) png_top->dpl.next = png;
	else
	{
		ext_pnglist = png;
		PNGTOP_DESC* pltop = PNG_TOP();
		pltop->dyn_pltop = &ext_pnglist->dpl;
	}

#ifdef LOG
	sprintf(msgbuf, "AddIconToPngCache: new icon %s, %i", imgname, png->dpl.icon);
	_WriteLog(msgbuf);
#endif
	
	return png->dpl.icon;
}

char* GetImagePath(char* sfile)
{
	if (pathbuf)
		sprintf(pathbuf, "%s\\Images\\%s", mcpath, sfile);
	return pathbuf;
}

void FreePngCache()
{
	DYNPNG_EXT* png = ext_pnglist;
	DYNPNG_EXT* fpng;
	while (png)
	{
		fpng = png;
		png = png->dpl.next;
		
		mfree(fpng->fname);
		mfree(fpng->dpl.img->bitmap);
		mfree(fpng->dpl.img);
		mfree(fpng);		
	}
}

void ExtProc(char* name, char* value)
{
	EXTINF* ext;
	int inj;
	int nlen = strlen(name);
	unsigned int i;
	strtolower(name, name, -1);

#ifdef LOG
	sprintf(msgbuf, "ExtProc(%s,%s)", name, value);
	_WriteLog(msgbuf);
#endif
	
	inj=0;
	if (nlen == 3 && strcmp(name,"<*>") == 0) ext = &ext_unk;
	else if (nlen == 3 && strcmp(name,"<c>") == 0) ext = &ext_chk;
	else if (nlen == 3 && strcmp(name,"<d>") == 0) ext = &ext_dir;
	else
	{
		ext = malloc(sizeof(EXTINF));
		zeromem(ext, sizeof(EXTINF));
		ext->ext = malloc(nlen + 1);
		strcpy(ext->ext, name);
		ext->crc = str_get_crc(name);
		ccExt++;
		inj=1;
	}
	int ico;
        if (((i=(unsigned int)value)>>28) != 0xA)
        {
          ico=i;
        }
	else if (!value[0])
		ico = ext_unk.ico;
	else if (isNumericStr(value))
	{
		ico = strtol(value, 0, 10);
		if (ico <= 0) ico = ext_unk.ico;
	}
	else
	{
		if (!loadPngLater || ext == &ext_unk || ext == &ext_chk || ext == &ext_dir)
			ico = AddIconToPngCache(value); // Инициализируем сразу
		else
			ico = -1; // Проинициализируем когда нужно будет
		ext->fname = malloc(strlen(value) + 1);
		strcpy(ext->fname, value);
	}
	ext->ico = ico;

#ifdef LOG
	sprintf(msgbuf, "ext=%s, crc=%i, fname=%s, ico=%i", ext->ext, ext->crc, ext->fname, ext->ico);
	_WriteLog(msgbuf);
#endif

	if (inj)
	{
		LockSched();
		ext->next = ext_last_s->next;
		ext_last_s->next = ext;
		UnlockSched();
	}
}

void LoadExts()
{
	loadPngLater = 1;
	ext_unk.ext = str_empty;
	ext_dir.ext = str_empty;
	ext_chk.ext = str_empty;
	if (CONFIG_LOAD_ICONS)
	{
		if (ccExt) FreeExt();
		EnumIni(1, (char*)&ext_file, ExtProc);
	}
	loadPngLater = 0;
}

void FreeExt()
{
	if (ccExt)
	{
		LockSched();
		while(ext_last_s->next!=ext_first_s)
		{
			EXTINF* ext = ext_last_s->next;
			ext_last_s->next = ext->next;
			if (ext->fname) mfree(ext->fname);
			if (ext->ext) mfree(ext->ext);
			mfree(ext);
			ccExt--;
		}
		UnlockSched();
		FreePngCache();
	}
}

EXTINF* FindExtByName(char* szext)
{
	int crc = str_get_crc(szext);
	EXTINF* ext = ext_last_s->next;
	while(ext != ext_first_s)
	{
		if (crc == ext->crc && strcmp(szext, ext->ext) == 0)
		{
			if (ext->ico == -1) // не проиницализирована еще иконка
			{
				if (ext->fname)
				{
					ext->ico = AddIconToPngCache(ext->fname);
					mfree(ext->fname);
					ext->fname = 0;
				}
				if (ext->ico == -1)
					ext->ico = ext_unk.ico;
			}
			return ext;
		}
		ext = ext->next;
	}
	return NULL;
}

EXTINF* GetExt(char* fname, int fattr)
{
  char name[MAX_PATH];
  
  strtolower(fname, name, -1);
  int len = strlen(name);
  if (fattr & FA_DIRECTORY && name[len-1] != '\\')
  {
    name[len] = '\\';
    name[len+1] = '\0';
  }
   
  // Пробуем поиск по имени
  EXTINF* ext = FindExtByName(name);
  if (ext != NULL)
    return ext;
  else if (fattr & FA_DIRECTORY)
    return &ext_dir;
  
  // Пробуем поиск по расширению
  char* pext = GetFileExt(name);
  if (pext)
  {
    ext = FindExtByName(pext);
    if (ext != NULL)
      return ext;
    
    // Пробуем найти расширение	в системе
    WSHDR* wsext = AllocWS(256);
    str_2ws(wsext, pext, 255);
    int uid = GetExtUid_ws(wsext);
    FreeWS(wsext);
    if (uid)
    {
      // Добавляем в список
      TREGEXPLEXT* pr = get_regextpnt_by_uid(uid);
      ExtProc(pext, (char*)(*pr->icon1));
      ext = FindExtByName(pext);
      if (ext != NULL)
        return ext;
    }
  }
  return &ext_unk;
}
