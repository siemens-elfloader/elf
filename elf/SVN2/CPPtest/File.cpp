//#include "include.h"
#include "..\inc\swilib.h"
#include "File.h"

CFile::CFile(char *fname)
{
  SetFileName(fname);
}

CFile::~CFile()
{
}

void CFile::SetFileName(const char* path)
{
  if(hFile != -1) fclose(hFile,&ferr);
  zeromem(fname,128);
  strcpy(fname,path);
}

void CFile::Close()
{
  fclose(hFile, &ferr);
  hFile = NULL;
}

int CFile::Open(unsigned int iFileFlags)
{
  return (hFile = fopen(fname, iFileFlags,P_READ+P_WRITE, &ferr));
}

int CFile::Read(void *cBuffer, int iByteCount)
{
  return (retval = fread(hFile, cBuffer, iByteCount, &ferr));
}

char* CFile::ReadBuf(int iByteCount)
{
  char *buf = (char*)malloc(iByteCount);
  retval = fread(hFile, buf, iByteCount, &ferr);
  return buf;
}

int CFile::Write(void const * cBuffer, int iByteCount)
{
  return (retval = fwrite(hFile, cBuffer, iByteCount, &ferr));
}

int CFile::Size()
{
  return GetSize(fname);
}


int CFile::Seek(unsigned int offset, unsigned int origin)
{
  return (lseek(hFile, offset, origin, &ferr, &ferr));
}



//--------------------------------------------------------//



int CFile::FOpen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode)
{
  return (fopen(cFileName, iFileFlags, iFileMode, &ferr));
}
/*
//создаем файл,но ниче не пишем в него
int CFile::Create(const char* FileName)
{
  int f = -1;
  int file;
  file = fopen(FileName,A_Create,P_WRITE,&ferr);
  if(file!=-1) f = file;  
  fclose(file);
  return f;
}

//если необходимо перезаписать файл
int CFile::OverWtite(const char* FileName,const char* buf)
{
  int f = -1;
  int i;
  f = fopen(FileName,A_Create + A_Truncate,P_WRITE,&ferr);
  if(f!=-1) i = fwrite(f, buf, strlen(buf), &ferr)
  fclose(f);
  return i;
}
*/
int CFile::FRead(int FileHandler, void *cBuffer, int iByteCount)
{
  return (fread(FileHandler, cBuffer, iByteCount, &ferr));
}

int CFile::FWrite(int FileHandler, void const * cBuffer, int iByteCount)
{
  return (fwrite(FileHandler, cBuffer, iByteCount, &ferr));
}

void CFile::FClose(int FileHandler)
{
  fclose(FileHandler, &ferr);
}


int CFile::LSeek(int FileHandler, unsigned int offset, unsigned int origin)
{
  return (lseek(FileHandler, offset, origin, &ferr, &ferr));
}

int CFile::MkDir(const char * cFileName)
{
  return (mkdir(cFileName, &ferr));
}

int CFile::IsDir(const char * cDirectory)
{
  return (isdir(cDirectory, &ferr));
}

int CFile::FindFirstFile(DIR_ENTRY *DIRENTRY,char *mask)
{
  return (::FindFirstFile(DIRENTRY, mask, &ferr));
}

int CFile::FindNextFile(DIR_ENTRY *DIRENTRY)
{
  return (::FindNextFile(DIRENTRY, &ferr));
}

int CFile::FindClose(DIR_ENTRY *DIRENTRY)
{
  return (::FindClose(DIRENTRY, &ferr));
}

int CFile::IsFileExist(const char *filepath)
{
  FSTATS fst;
  if(GetFileStats(filepath, &fst, &ferr)==-1)
    return 0;
  else
    return 1;
}

int CFile::GetSize(const char *filepath)
{
  FSTATS fst;
  if(GetFileStats(filepath, &fst, &ferr)!=-1)
    return fst.size;  
  else
    return 0;
}

int CFile::FDelete(const char * cFileName)
{
  return (unlink(cFileName, &ferr));
}

int CFile::FMove(const char * SourceFileName, const char * DestFileName)
{
  return (fmove(SourceFileName, DestFileName, &ferr));
}


