#ifndef _EXTS_H
#define _EXTS_H

#ifndef _SWILIB
#include "..\inc\swilib.h"
#define _SWILIB
#endif
#include "..\inc\pnglist.h"

//#define MAX_PATH		0x80
#define MAX_PATH		0x100
#define MAX_EXT			8

typedef struct
{
	char* ext;
	int crc;
	char* fname;
	int ico;
	void* next; 
} EXTINF;

typedef struct
{
  DYNPNGICONLIST dpl;
  unsigned int uni_n;
  char* fname;
  int crc;
} DYNPNG_EXT;

extern DYNPNG_EXT* ext_pnglist;

int str_get_crc(char* str);
void LoadExts();
void FreeExt();
EXTINF* GetExt(char* fname, int fattr);
char* GetImagePath(char* sfile);

#endif
