#include "inc\mc.h"

void fn_zero(FN_LIST *list)
{
	zeromem(list, sizeof(FN_LIST));
}

void fn_free(FN_LIST *list)
{
	if (list==NULL) return;
	if (list->count)
	{
		LockSched();
		while(list->items)
		{
			FN_ITM *itm = list->items;
			list->items = itm->next;

			if (itm->full) mfree(itm->full);
			if (itm->zipPath) mfree(itm->zipPath);
			mfree(itm);

			list->count--;
		}
		UnlockSched();
	}
}

void fn_rev(FN_LIST *list)
{
	if (list==NULL) return;

	if (list->count)
	{
		LockSched();
		FN_ITM *itm = list->items;
		FN_ITM *next = itm->next;
		while(next)
		{
			itm->next=next->next;
			next->next=list->items;
			list->items = next;
			next = itm->next;
		}
		UnlockSched();
	}
}

int fn_inlist(FN_LIST *list, char *full)
{
	if (list==NULL || !list->count) return 0;

	FN_ITM *itm = list->items;
	while(itm)
	{
		if (!strcmp(itm->full, full)) return 1;  
		itm=itm->next;
	}
	return 0;
}

void fn_add(FN_LIST* list, int type, int ftype, int pname, char* full, char* zipPath)
{
	if (list==NULL) return;

	if (type!=list->type)
	{ 
		if (list->count) fn_free(list);
		list->type = type;
	}

	if (!fn_inlist(list, full))
	{
		FN_ITM *itm = malloc(sizeof(FN_ITM));

		itm->ftype = ftype;
		itm->pname = pname;
		itm->full = malloc(strlen(full)+1);
		strcpy(itm->full, full);
		if (zipPath != NULL)
		{
			itm->zipPath = malloc(strlen(zipPath)+1);
			strcpy(itm->zipPath, zipPath);
		}
		else
		{
			itm->zipPath = NULL;
		}

		LockSched();
		itm->next  = list->items;
		list->items = itm;
		list->count++;
		UnlockSched();
	}  
}

int _fn_fill(DIR_ENTRY *de, int param)
{
	if (pathbuf_fn)
	{
		int ftype = de->file_attr & FA_DIRECTORY ? TYPE_COMMON_DIR : TYPE_COMMON_FILE;
		FN_LIST *list = (FN_LIST *) param;
		sprintf(pathbuf_fn, _s_s, de->folder_name, de->file_name);
		fn_add(list, FNT_NONE, ftype, 0, pathbuf_fn, NULL);
		return 1;
	}  
	return 0;
}

void fn_fill(FN_LIST *list, char *path)
{
	if (list==NULL) return;

	int ftype = isdir(path, &err) ? TYPE_COMMON_DIR : TYPE_COMMON_FILE;
	if (ftype == TYPE_COMMON_DIR)
		EnumFiles(path, _fn_fill, (int)list);
	fn_add(list, FNT_NONE, ftype, 0, path, NULL);
}

#ifdef LOG
void fn_log(FN_LIST *list)
{
	FN_ITM *itm = list->items;
	while(itm)
	{
		_WriteLog(itm->full);
		itm=itm->next;
	}
}
#endif
