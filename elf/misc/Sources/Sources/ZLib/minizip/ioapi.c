/* ioapi.c -- IO base function header for compress/uncompress .zip
   files using zlib + zip or unzip API

   Version 1.01e, February 12th, 2005

   Copyright (C) 1998-2005 Gilles Vollant
*/

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include "..\zlib.h"
#include "ioapi.h"

voidpf fopen_file_func (
   voidpf opaque,
   const char* filename,
   int mode);

uLong fread_file_func (
   voidpf opaque,
   voidpf stream,
   void* buf,
   uLong size);

uLong fwrite_file_func (
   voidpf opaque,
   voidpf stream,
   const void* buf,
   uLong size);

long ftell_file_func (
   voidpf opaque,
   voidpf stream);

long fseek_file_func (
   voidpf opaque,
   voidpf stream,
   uLong offset,
   int origin);

int fclose_file_func (
   voidpf opaque,
   voidpf stream);

int ferror_file_func (
   voidpf opaque,
   voidpf stream);

voidpf fopen_file_func (
   voidpf opaque,
   const char* filename,
   int mode)
{
	FILE* pFile = malloc(sizeof(FILE));
	int flags = 0;
	int fmode = 0;
	if ((mode & ZLIB_FILEFUNC_MODE_READWRITEFILTER)==ZLIB_FILEFUNC_MODE_READ)
	{
		fmode = A_ReadOnly | A_BIN;
		flags = P_READ;
	}
	else if (mode & ZLIB_FILEFUNC_MODE_EXISTING)
	{
		fmode = A_ReadWrite | A_BIN;
		flags = P_READ | P_WRITE;
	}
	else if (mode & ZLIB_FILEFUNC_MODE_CREATE)
	{
		fmode = A_ReadWrite | A_Create | A_Truncate;
		flags = P_READ | P_WRITE;
	}

	if (filename && pFile)
		pFile->handle = fopen(filename, flags, fmode, &pFile->err);

	return (voidpf)pFile;
}

uLong fread_file_func (
   voidpf opaque,
   voidpf stream,
   void* buf,
   uLong size)
{
	uLong ret = 0;
	FILE* pFile = (FILE*)stream;
	if (pFile)
		ret = (uLong)fread(pFile->handle, buf, (size_t)size, &pFile->err);
	return ret;
}

uLong fwrite_file_func (
   voidpf opaque,
   voidpf stream,
   const void* buf,
   uLong size)
{
	uLong ret = 0;
	FILE* pFile = (FILE*)stream;
	if (pFile)
		ret = (uLong)fwrite(pFile->handle, buf, (size_t)size, &pFile->err);
	return ret;
}

long ftell_file_func (
   voidpf opaque,
   voidpf stream)
{
	long ret = -1;
	FILE* pFile = (FILE*)stream;
	if (pFile)
		ret = lseek(pFile->handle, 0, S_CUR, &pFile->err, &pFile->err);
	return ret;
}

long fseek_file_func (
   voidpf opaque,
   voidpf stream,
   uLong offset,
   int origin)
{
	int fseek_origin = 0;
	long ret = -1;
	FILE* pFile = (FILE*)stream;
	if (pFile)
	{
		switch (origin)
		{
		case ZLIB_FILEFUNC_SEEK_CUR :
			fseek_origin = S_CUR;
			break;
		case ZLIB_FILEFUNC_SEEK_END :
			fseek_origin = S_END;
			break;
		case ZLIB_FILEFUNC_SEEK_SET :
			fseek_origin = S_SET;
			break;
		default:
			return -1;
		}
		lseek(pFile->handle, offset, fseek_origin, &pFile->err, &pFile->err);
		ret = 0;
	}
	return ret;
}

int fclose_file_func (
   voidpf opaque,
   voidpf stream)
{
	int ret = -1;
	FILE* pFile = (FILE*)stream;
	if (pFile)
	{
		ret = 0;
		fclose(pFile->handle, &pFile->err);
		mfree(pFile);
	}
	return ret;
}

int ferror_file_func (
   voidpf opaque,
   voidpf stream)
{
	int ret = -1;
	FILE* pFile = (FILE*)stream;
	if (pFile)
		ret = pFile->err;
	return ret;
}

void fill_fopen_filefunc (
  zlib_filefunc_def* pzlib_filefunc_def)
{
	pzlib_filefunc_def->zopen_file = fopen_file_func;
	pzlib_filefunc_def->zread_file = fread_file_func;
	pzlib_filefunc_def->zwrite_file = fwrite_file_func;
	pzlib_filefunc_def->ztell_file = ftell_file_func;
	pzlib_filefunc_def->zseek_file = fseek_file_func;
	pzlib_filefunc_def->zclose_file = fclose_file_func;
	pzlib_filefunc_def->zerror_file = ferror_file_func;
	pzlib_filefunc_def->opaque = NULL;
}
