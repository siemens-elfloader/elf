#include "inc\mc.h"
#include "inc\mui.h"
#include "inc\sort.h"
#include "inc\encode.h"

typedef struct {
	char* name;
	char* ext;
	FILEINF* dataPointer;
} FileSortInfo;

char* fn_prepare(char* src, char* dst)
{
	// Копируем
	strcpy(dst, src);
	
	// Преобразуем кодировку в Win
	utf82win(dst);
	
	// В нижний регистр и убиваем откуда-то взявшиеся 0x1f символы
	int len = strlen(dst);
	int jj = 0;
	for(int ii = 0; ii < len; ii++)
	{
		int ch = dst[ii];
		if (ch >= 'A' && ch <= 'Z') ch = ch-'A'+'a';
		else if (ch == 0x1F) continue;
		dst[jj++] = ch;
	}
	dst[jj] = 0;
	return dst;
}

// Сравнение имен файлов, если различие только в последних символах и они являются цифрами,
// то цифры обрабатываются как числа
int filenamecmp(FileSortInfo* fs1, FileSortInfo* fs2)
{
	char* str1 = fs1->name;
	char* str2 = fs2->name;
	unsigned char c1 = 0;
	unsigned char c2 = 0;

	while (1)
	{
		c1 = *str1;
		c2 = *str2;

		if (c1 != c2) break;
		if (c1 == 0 && c2 == 0) return 0;

		str1++; str2++;
	}

	// Если попали сюда, то строки не равны
	if (stricmp(fs1->ext, fs2->ext) == 0 && isNumericStr(str1) && isNumericStr(str2))
	{
		// Если расширения одинаковые и неравные подстроки - цифры...
	
		// если длина меньше, то заведомо и число меньше
		// если одинаковая, то идем дальше, т.к. достаточно сравнить только найденные отличающиеся цифры
		int ls1 = strlen(str1);
		int ls2 = strlen(str2);
		if (ls1 != ls2) return (ls1 < ls2 ? -1 : +1);
	}

	return (c1 < c2 ? -1 : +1);
}


int isNameGreater(void* a, void* b)
{
	FileSortInfo* fa = (FileSortInfo*)a;
	FileSortInfo* fb = (FileSortInfo*)b;
	int res = filenamecmp(fa, fb);
	if (res == 0)
		res = stricmp(fa->ext, fb->ext); // если имена равны то сравниваем расширения
	return res > 0;
}

int isExtGreater(void* a, void* b)
{
	FileSortInfo* fa = (FileSortInfo*)a;
	FileSortInfo* fb = (FileSortInfo*)b;
	int res = stricmp(fa->ext, fb->ext);
	if (res == 0)
		res = filenamecmp(fa, fb); // если расширения равны то сравниваем имена
	return  res > 0;
}

int isSizeGreater(void* a, void* b)
{
	FILEINF* fa = (FILEINF*)a;
	FILEINF* fb = (FILEINF*)b;
	int res = fa->size - fb->size;
	if (res == 0)
		return stricmp(a, b) > 0;
	else
		return res > 0;
}

int isDateGreater(void* a, void* b)
{
	FILEINF* fa = (FILEINF*)a;
	FILEINF* fb = (FILEINF*)b;
	int res = fa->time - fb->time;
	if (res == 0)
		return stricmp(a, b) > 0;
	else
		return res > 0;
}

FILEINF* SortList(FILEINF* list, int sort)
{
	FILEINF* base = list;
	int i;
	int err = 0;

	int sortType = sort & STV_MASK;
	int isDirectSort = sort & ST_REVERS;

	// Считаем кол-во элементов
	int count = 0;
	FILEINF* cur = base;
	while (cur)
	{
		count++;
		cur = cur->next;
	}

	// Не сортируем если нет смысла
	if (count < 2) return list;

	if (sortType == ST_NAME || sortType == ST_EXT) // Косвенная сортировка по строкам
	{
		char buf[MAX_PATH];
		FileSortInfo** sortInfo = malloc(sizeof(FileSortInfo*) * count);

		if (buf && sortInfo)
		{
			// Готовим массив
			i = 0;
			cur = base;
			while (cur)
			{
				sortInfo[i] = malloc(sizeof(FileSortInfo));
				if (!sortInfo[i])
				{
					err = 1; break;
				}
				sortInfo[i]->dataPointer = cur;
				sortInfo[i]->name = malloc(MAX_PATH);
				if (!sortInfo[i]->name)
				{
					err = 1; break;
				}

				fn_prepare(cur->sname, sortInfo[i]->name);
#ifdef LOG
				_WriteLog(sortInfo[i]->name);
#endif

				// Разбиваем на имя файла и расширение
				sortInfo[i]->ext = GetFileExt(sortInfo[i]->name);
				if (!sortInfo[i]->ext)
					sortInfo[i]->ext = str_empty;
				else
					*(sortInfo[i]->ext-1) = 0; // вместо точки ставим конец строки

				cur = cur->next;
				i++;
			}

			if (!err)
			{
				// Сортируем
				if (sortType == ST_NAME)
					quickSort((void**)sortInfo, count, isNameGreater);
				else if (sortType == ST_EXT)
					quickSort((void**)sortInfo, count, isExtGreater);

				// Переинициируем список и освободим память
				if (isDirectSort)
				{
					base = sortInfo[0]->dataPointer;
					for (i = 0; i < count - 1; i++)
						sortInfo[i]->dataPointer->next = sortInfo[i + 1]->dataPointer;
					sortInfo[count - 1]->dataPointer->next = 0;
				}
				else
				{
					base = sortInfo[count - 1]->dataPointer;
					for (i = count - 1; i > 0; i--)
						sortInfo[i]->dataPointer->next = sortInfo[i - 1]->dataPointer;
					sortInfo[0]->dataPointer->next = 0;
				}
			}
		}
		else
		{
			MsgBoxError(1, (int) muitxt(ind_err_nomemory));
		}

		if (sortInfo)
		{
			for (i = count - 1; i >= 0; i--)
			{
				if (sortInfo[i])
				{
					if (sortInfo[i]->name)
						mfree(sortInfo[i]->name);
					mfree(sortInfo[i]);
				}
			}
			mfree(sortInfo);
		}
	}
	else // Прямая сортировка по числам
	{
		// Готовим массив
		FILEINF** sortInfo = malloc(sizeof(FILEINF*) * count);
		if (sortInfo)
		{
			i = 0;
			cur = base;
			while (cur)
			{
				sortInfo[i] = cur;
				cur = cur->next;
				i++;
			}

			// Сортируем
			if (sortType == ST_DATE)
				quickSort((void**)sortInfo, count, isDateGreater);
			else if (sortType == ST_SIZE)
				quickSort((void**)sortInfo, count, isSizeGreater);

			// Переинициируем список и освободим память
			if (isDirectSort)
			{
				base = sortInfo[0];
				for (i = 0; i < count - 1; i++)
					sortInfo[i]->next = sortInfo[i + 1];
				sortInfo[count - 1]->next = 0;
			}
			else
			{
				base = sortInfo[count - 1];
				for (i = count - 1; i > 0; i--)
					sortInfo[i]->next = sortInfo[i - 1];
				sortInfo[0]->next = 0;
			}
			mfree(sortInfo);
		}
		else
		{
			MsgBoxError(1, (int) muitxt(ind_err_nomemory));
		}
	}
	return base;
}

void SortFiles(int tab)
{
	if (tabs[tab]->ccFiles>1)
	{
		LockSched();
		FILEINF *files=0;
		FILEINF *dirs=0;

		FILEINF *cur = FileListBase[tab]->next;
		FILEINF *next;
		while(cur != FileListBase[tab])
		{
			next = cur->next;
			if (cur->attr & FA_DIRECTORY)
			{
				cur->next = dirs;
				dirs = cur;
			}
			else
			{
				cur->next = files;
				files = cur;
			}
			cur = next;
		}
		FileListBase[tab]->next = FileListBase[tab];

		int srt = tabs[tab]->sort;

		if (srt & STV_MASK == ST_SIZE)
			dirs = SortList(dirs,  srt & STD_MASK); // При сортировке по размеру папки сортируем по имени
		else
			dirs = SortList(dirs,  srt);

		files = SortList(files, srt);

		while(files)
		{
			next = files->next;
			files->next = FileListBase[tab]->next;
			FileListBase[tab]->next = files;
			files = next;
		}
		while(dirs)
		{
			next = dirs->next;
			dirs->next = FileListBase[tab]->next;
			FileListBase[tab]->next = dirs;
			dirs = next;
		}

		UnlockSched();
	}
}
