#include "inc\mc.h"

#define ICO_CHECK	1382
#define ICO_UNKNOWN	1033
#define ICO_FOLDER	1208

unsigned int ccExt=0;
EXTINF ext_dir;
EXTINF ext_chk;
EXTINF ext_unk={"",ICO_UNKNOWN,&ext_chk};
EXTINF ext_chk={"",ICO_CHECK,  &ext_dir};
EXTINF ext_dir={"",ICO_FOLDER, &ext_unk};
EXTINF *ext_first_s=&ext_unk;
EXTINF *ext_last_s=&ext_dir;

void ExtProc(char* name, char* value)
{
	int  ico;
	EXTINF *ext;
	int inj;

	strtolower(name, name, -1);
	ico=strtol(value,0,10);
	inj=0;
	if (strcmp(name,"<*>")==0) ext = &ext_unk; 
	else
		if (strcmp(name,"<c>")==0) ext = &ext_chk; 
		else
			if (strcmp(name,"<d>")==0) ext = &ext_dir; 
			else
			{
				ext = malloc(sizeof(EXTINF));
				ccExt++;
				inj=1;
			}
			ext->ico = ico;
			strcpy(ext->ext, name);

			if (inj)
			{
				LockSched();
				ext->next  = ext_last_s->next;
				ext_last_s->next = ext;
				UnlockSched();
			} 
}

void LoadExts()
{
	if (CONFIG_LOAD_ICONS)
	{
		if (ccExt)FreeExt();
		EnumIni(1, (char*)&ext_file, ExtProc);
	}  
}

void FreeExt()
{
	if (ccExt)
	{
		LockSched();
		while(ext_last_s->next!=ext_first_s)
		{
			EXTINF *ext = ext_last_s->next;
			ext_last_s->next = ext->next;
			mfree(ext);
			ccExt--;
		}
		UnlockSched();
	}
}

EXTINF *GetExt(char* fname, int fattr)
{
	if (fattr & FA_DIRECTORY) return &ext_dir;

	char* sz = GetFileExt(fname);
	if ((int) sz) 
	{
		char szext[MAX_EXT];
		strtolower(sz, szext, MAX_EXT);

		EXTINF* ext=ext_last_s->next;
		while(ext!=ext_first_s)
		{
			if (!strncmp(szext, ext->ext, MAX_EXT)) return ext;
			ext = ext->next;
		}
	}
	return &ext_unk;
}

